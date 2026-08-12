/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * This slice (SKR08) covers the Swift-runtime object-model / ARC / message-
 * dispatch region at 0x3d95cc-0x3e66e4. All names are estimates unless a
 * string/header matches. All functions here return void. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef void (*code_t)(void);
typedef struct { word_t lo, hi; } sk16_t;
#define SKR08_FATAL(a) __builtin_trap()
#define sk_trap(...) ((word_t)0)

/* Unrecovered register-aliased indirect dispatch: target code pointer is
 * invoked; the decompiler could not recover the arg list (register noise). */
static inline word_t sk_dispatch(code_t fn, ...){ if (fn) fn(); return 0; }

/* Ghidra decompiler bit/vector intrinsics (type-check shims). */
static inline word_t SCARRY8(word_t a, word_t b, ...){ (void)a;(void)b; return 0; }
static inline word_t SBORROW8(word_t a, word_t b, ...){ (void)a;(void)b; return 0; }
static inline word_t ZEXT416(word_t x){ return x; }
static inline word_t ZEXT816(word_t x){ return x; }
static inline word_t ZEXT824(word_t x){ return x; }
static inline word_t ZEXT832(word_t x){ return x; }
static inline word_t ZEXT864(word_t x){ return x; }
static inline word_t CONCAT11(word_t h, word_t l){ return ((h&0xff)<<8)|(l&0xff); }
static inline word_t CONCAT12(word_t h, word_t r){ return (h<<16)|r; }
static inline word_t CONCAT13(word_t h, word_t r){ return (h<<24)|r; }
static inline word_t CONCAT14(word_t h, word_t r){ return (h<<32)|r; }
static inline word_t CONCAT16(word_t h, word_t r){ return (h<<48)|r; }
static inline word_t CONCAT72(word_t h, word_t r){ return (h<<64)|r; }

/* External cL4 / Swift-runtime callees (ground-truth FUN_ addresses). */
extern word_t sk_h_00002534();
extern word_t sk_h_0006b6f4();
extern word_t sk_h_0007c028();
extern word_t sk_h_0007c1a4();
extern sk16_t sk_h_0007c1c4();
extern sk16_t sk_h_000839d8();
extern word_t sk_h_000839f8();
extern word_t sk_h_0008409c();
extern word_t sk_h_00084174();
extern word_t sk_h_00084180();
extern word_t sk_h_00084220();
extern word_t sk_h_00084234();
extern word_t sk_h_0008e1ec();
extern word_t sk_h_0008e500();
extern sk16_t sk_h_0008e518();
extern word_t sk_h_000a649c();
extern word_t sk_h_000a6f88();
extern word_t sk_h_000aa4ec();
extern sk16_t sk_h_000dbd0c();
extern word_t sk_h_0011aa70();
extern word_t sk_h_0014ae44();
extern word_t sk_h_0016186c();
extern word_t sk_h_001afa84();
extern word_t sk_h_00310d68();
extern word_t sk_h_00349530();
extern word_t sk_h_0034a210();
extern word_t sk_h_0034b05c();
extern word_t sk_h_0034b0d4();
extern word_t sk_h_0034d004();
extern word_t sk_h_00350404();
extern sk16_t sk_h_00350470();
extern word_t sk_h_003504a0();
extern sk16_t sk_h_003504e8();
extern word_t sk_h_00350500();
extern sk16_t sk_h_0035050c();
extern word_t sk_h_00350518();
extern word_t sk_h_00350548();
extern word_t sk_h_00350560();
extern word_t sk_h_00350618();
extern word_t sk_h_00350624();
extern word_t sk_h_00350720();
extern word_t sk_h_00350744();
extern word_t sk_h_00350750();
extern word_t sk_h_00350798();
extern sk16_t sk_h_003507e0();
extern word_t sk_h_00350968();
extern word_t sk_h_00350974();
extern word_t sk_h_003509c8();
extern word_t sk_h_00350bfc();
extern word_t sk_h_003510a0();
extern word_t sk_h_003510c4();
extern word_t sk_h_0035136c();
extern word_t sk_h_003513b4();
extern word_t sk_h_00351584();
extern word_t sk_h_00351cd0();
extern sk16_t sk_h_00351d24();
extern sk16_t sk_h_00351da8();
extern word_t sk_h_00351f10();
extern word_t sk_h_00352018();
extern sk16_t sk_h_00352700();
extern word_t sk_h_00353080();
extern word_t sk_h_00353930();
extern word_t sk_h_00353c00();
extern sk16_t sk_h_0035a7e8();
extern word_t sk_h_0035ac70();
extern word_t sk_h_00365b6c();
extern word_t sk_h_003698b0();
extern word_t sk_h_0036a940();
extern word_t sk_h_0036b118();
extern word_t sk_h_0036b270();
extern sk16_t sk_h_00377824();
extern word_t sk_h_00377bec();
extern word_t sk_h_00377dcc();
extern word_t sk_h_003e6d08();
extern word_t sk_h_003e9df8();
extern word_t sk_h_003eaf4c();
extern word_t sk_h_003fcc1c();
extern word_t sk_h_003fcc4c();
extern word_t sk_h_003fd0bc();
extern word_t sk_h_00406268();
extern word_t sk_h_00406288();
extern word_t sk_h_004062a8();
extern word_t sk_h_004062c8();
extern word_t sk_h_004062e8();
extern word_t sk_h_00406374();
extern word_t sk_h_00406420();
extern word_t sk_h_0040652c();
extern word_t sk_h_0040654c();
extern word_t sk_h_00406560();
extern word_t sk_h_00406574();
extern word_t sk_h_00406590();
extern word_t sk_h_004065c8();
extern word_t sk_h_004065e8();
extern word_t sk_h_00406608();
extern word_t sk_h_00406624();
extern word_t sk_h_00406704();
extern sk16_t sk_h_0040678c();
extern word_t sk_h_0040679c();
extern word_t sk_h_004067b8();
extern word_t sk_h_004067cc();
extern word_t sk_h_004067f8();
extern word_t sk_h_0040683c();
extern word_t sk_h_0040684c();
extern word_t sk_h_0040686c();
extern sk16_t sk_h_00406894();
extern word_t sk_h_004068bc();
extern word_t sk_h_004068f4();
extern word_t sk_h_00406944();
extern word_t sk_h_0040697c();
extern word_t sk_h_0040698c();
extern word_t sk_h_004069b0();
extern word_t sk_h_004069c4();
extern word_t sk_h_00406a5c();
extern sk16_t sk_h_00406a94();
extern word_t sk_h_00406aa4();
extern word_t sk_h_00406ab4();
extern sk16_t sk_h_00406b24();
extern sk16_t sk_h_00406b84();
extern word_t sk_h_00406bb4();
extern word_t sk_h_00406bd4();
extern word_t sk_h_00406be4();
extern word_t sk_h_00406c1c();
extern word_t sk_h_00406c5c();
extern word_t sk_h_00406c80();
extern word_t sk_h_00406cc8();
extern word_t sk_h_00406ce0();
extern word_t sk_h_00406cf0();
extern word_t sk_h_00406d70();
extern word_t sk_h_00406da8();
extern word_t sk_h_00406db8();
extern word_t sk_h_00406dd0();
extern word_t sk_h_00406e18();
extern word_t sk_h_00406e34();
extern word_t sk_h_00406e48();
extern sk16_t sk_h_00406e64();
extern word_t sk_h_00406e8c();
extern word_t sk_h_00406ee4();
extern word_t sk_h_00406f18();
extern word_t sk_h_00406f2c();
extern word_t sk_h_00406f40();
extern word_t sk_h_00406f50();
extern word_t sk_h_00406f84();
extern word_t sk_h_00406fb0();
extern sk16_t sk_h_00406fd4();
extern word_t sk_h_00406fe0();
extern word_t sk_h_00407000();
extern word_t sk_h_0040700c();
extern word_t sk_h_00407018();
extern word_t sk_h_00407070();
extern word_t sk_h_00407080();
extern word_t sk_h_00407090();
extern word_t sk_h_004070a0();
extern sk16_t sk_h_004070d8();
extern word_t sk_h_004070e4();
extern word_t sk_h_00407100();
extern word_t sk_h_0040711c();
extern word_t sk_h_00407128();
extern word_t sk_h_00407164();
extern word_t sk_h_004071c0();
extern word_t sk_h_00407214();
extern word_t sk_h_00407248();
extern word_t sk_h_00407260();
extern word_t sk_h_0040733c();
extern word_t sk_h_00407374();
extern sk16_t sk_h_0040738c();
extern word_t sk_h_00407400();
extern word_t sk_h_00407450();
extern word_t sk_h_00407478();
extern word_t sk_h_00407484();
extern word_t sk_h_004074c4();
extern word_t sk_h_004074e8();
extern word_t sk_h_00407504();
extern word_t sk_h_0040752c();
extern word_t sk_h_00407594();
extern word_t sk_h_004075a4();
extern word_t sk_h_00407604();
extern word_t sk_h_00407610();
extern word_t sk_h_0040764c();
extern word_t sk_h_00407670();
extern word_t sk_h_004076a8();
extern word_t sk_h_004076c4();
extern word_t sk_h_00407700();
extern word_t sk_h_00407740();
extern word_t sk_h_00407764();
extern word_t sk_h_00407774();
extern word_t sk_h_00407784();
extern word_t sk_h_004077a0();
extern word_t sk_h_004077cc();
extern word_t sk_h_00407814();
extern word_t sk_h_00407824();
extern word_t sk_h_00407830();
extern word_t sk_h_00407840();
extern word_t sk_h_0040785c();
extern word_t sk_h_004078b4();
extern word_t sk_h_004078e8();
extern word_t sk_h_004078f4();
extern word_t sk_h_0040790c();
extern sk16_t sk_h_00407924();
extern word_t sk_h_00407954();
extern word_t sk_h_00407960();
extern word_t sk_h_00407990();
extern word_t sk_h_004079a8();
extern word_t sk_h_004079b4();
extern word_t sk_h_004079cc();
extern word_t sk_h_00407a60();
extern word_t sk_h_00407aa0();
extern word_t sk_h_00407aac();
extern word_t sk_h_00407ab8();
extern sk16_t sk_h_00407ad0();
extern word_t sk_h_00407adc();
extern word_t sk_h_00407b48();
extern word_t sk_h_00407bb8();
extern sk16_t sk_h_00407bf8();
extern word_t sk_h_00407c3c();
extern word_t sk_h_00407c78();
extern word_t sk_h_00407c8c();
extern word_t sk_h_00407ca0();
extern word_t sk_h_00407cc4();
extern word_t sk_h_00407cd4();
extern word_t sk_h_00407ce4();
extern word_t sk_h_00407d14();
extern word_t sk_h_00407d90();
extern word_t sk_h_00407da0();
extern word_t sk_h_00407e58();
extern word_t sk_h_00407e6c();
extern word_t sk_h_00407ea0();
extern word_t sk_h_00407f48();
extern word_t sk_h_00408038();
extern word_t sk_h_00408044();
extern word_t sk_h_00408058();
extern word_t sk_h_0040807c();
extern word_t sk_h_004080cc();
extern word_t sk_h_00408178();
extern word_t sk_h_00408190();
extern word_t sk_h_004081b4();
extern word_t sk_h_004081c0();
extern word_t sk_h_004081d8();
extern word_t sk_h_004081fc();
extern word_t sk_h_00408224();
extern word_t sk_h_00408244();
extern word_t sk_h_0040826c();
extern word_t sk_h_00408280();
extern word_t sk_h_004082a8();
extern word_t sk_h_00408308();
extern word_t sk_h_00408328();
extern word_t sk_h_0040833c();
extern word_t sk_h_00408348();
extern sk16_t sk_h_00408354();
extern word_t sk_h_00408360();
extern word_t sk_h_00408374();
extern word_t sk_h_00408380();
extern word_t sk_h_004083a0();
extern word_t sk_h_004083c0();
extern word_t sk_h_004083cc();
extern word_t sk_h_004083d8();
extern word_t sk_h_004083f0();
extern word_t sk_h_00408404();
extern word_t sk_h_00408410();
extern word_t sk_h_00408440();
extern word_t sk_h_00408454();
extern word_t sk_h_00408460();
extern word_t sk_h_004084a4();
extern word_t sk_h_00408538();
extern word_t sk_h_0040859c();
extern word_t sk_h_004085b4();
extern word_t sk_h_00408db8();
extern word_t sk_h_0040bb18();
extern word_t sk_h_0040bd24();

/* Data / string globals referenced by this slice. */
extern unsigned char DAT_00405fac[1];
extern unsigned char DAT_00405fdc[1];
extern unsigned char DAT_004060bc[1];
extern unsigned char DAT_003fcf24[1];
extern unsigned char DAT_0059ffbc[1];
extern unsigned char DAT_0059ffe4[1];
extern unsigned char DAT_0059fff4[1];
extern unsigned char DAT_005a0004[1];
extern unsigned char DAT_005a0024[1];
extern unsigned char DAT_005a0038[1];
extern unsigned char DAT_005a005c[1];
extern unsigned char DAT_005a0064[1];
extern unsigned char DAT_005a0078[1];
extern unsigned char DAT_005a0088[1];
extern unsigned char DAT_005a009c[1];
extern unsigned char DAT_005a00ac[1];
extern unsigned char DAT_00614890[1];
extern unsigned char DAT_00614a5c[1];
extern unsigned long (*DAT_00658c80)(unsigned long, ...);
extern char s_Can_t_prefix_a_negative_number_o_005dbf40[];

/* Forward declarations of functions defined in this slice. */
void sk_f_003d95cc(void);
void sk_f_003d9600(void);
void sk_f_003d961c(word_t param_1, word_t param_2, word_t param_3);
void sk_f_003d96ac(void);
void sk_f_003d98d8(void);
void sk_f_003d9b94(void);
void sk_f_003d9f0c(word_t param_1, word_t param_2, code_t jt1);
void sk_f_003da178(void);
void sk_f_003da330(void);
void sk_f_003da7f8(word_t param_1, word_t param_2, word_t param_3, long param_4, long param_5, word_t param_6);
void sk_f_003dab54(void);
void sk_f_003dae98(void);
void sk_f_003db300(void);
void sk_f_003db61c(void);
void sk_f_003db7e0(void);
void sk_f_003dc01c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5);
void sk_f_003dc158(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6);
void sk_f_003dc32c(void);
void sk_f_003dc6a0(void);
void sk_f_003dc724(void);
void sk_f_003dc97c(void);
void sk_f_003dcb98(void);
void sk_f_003dcc4c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5, word_t param_6);
void sk_f_003dcf90(void);
void sk_f_003dd1dc(void);
void sk_f_003dd2e0(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5);
void sk_f_003dd418(void);
void sk_f_003dd4c0(long param_1, word_t param_2, word_t param_3);
void sk_f_003dd540(void);
void sk_f_003dd5d0(void);
void sk_f_003dd660(void);
void sk_f_003dd840(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5, word_t param_6);
void sk_f_003dd920(void);
void sk_f_003ddc10(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5);
void sk_f_003ddd44(void);
void sk_f_003dde8c(void);
void sk_f_003ddecc(word_t param_1, word_t param_2, word_t param_3);
void sk_f_003ddf04(void);
void sk_f_003ddfbc(void);
void sk_f_003de17c(void);
void sk_f_003de33c(void);
void sk_f_003de418(word_t param_1, word_t param_2, word_t param_3, long param_4, long param_5, word_t param_6);
void sk_f_003de550(void);
void sk_f_003de74c(void);
void sk_f_003de938(void);
void sk_f_003deb0c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5);
void sk_f_003dec44(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, long param_6, word_t param_7);
void sk_f_003dedd4(void);
void sk_f_003defbc(void);
void sk_f_003df278(void);
void sk_f_003df548(void);
void sk_f_003df748(void);
void sk_f_003df9dc(void);
void sk_f_003dfc60(void);
void sk_f_003dfe08(word_t param_1, word_t param_2, code_t jt0);
void sk_f_003e0028(word_t param_1, word_t param_2, code_t jt0);
void sk_f_003e012c(word_t param_1, word_t param_2, long param_3, word_t param_4, word_t param_5);
void sk_f_003e025c(void);
void sk_f_003e0404(word_t param_1, word_t param_2, code_t jt0);
void sk_f_003e06a0(word_t param_1, word_t param_2, code_t jt0);
void sk_f_003e0848(void);
void sk_f_003e08fc(void);
void sk_f_003e09e4(word_t param_1, int *param_2);
void sk_f_003e0c88(void);
void sk_f_003e0e30(void);
void sk_f_003e117c(void);
void sk_f_003e1330(void);
void sk_f_003e1550(void);
void sk_f_003e17b4(void);
void sk_f_003e1968(void);
void sk_f_003e1c00(void);
void sk_f_003e1da8(word_t param_1, word_t param_2, long param_3);
void sk_f_003e1f00(void);
void sk_f_003e20c4(void);
void sk_f_003e22f8(word_t param_1, word_t param_2, code_t jt1);
void sk_f_003e2558(void);
void sk_f_003e262c(word_t param_1, word_t param_2, long param_3);
void sk_f_003e2784(void);
void sk_f_003e2948(void);
void sk_f_003e2b7c(word_t param_1, word_t param_2, code_t jt1);
void sk_f_003e2ddc(void);
void sk_f_003e3064(void);
void sk_f_003e3160(word_t param_1, word_t param_2, code_t param_3);
void sk_f_003e31e8(void);
void sk_f_003e32e4(void);
void sk_f_003e33d8(void);
void sk_f_003e3454(void);
void sk_f_003e3484(void);
void sk_f_003e34b4(void);
void sk_f_003e35ec(void);
void sk_f_003e37c8(word_t param_1, word_t param_2, code_t jt1);
void sk_f_003e3a14(void);
void sk_f_003e3c80(word_t param_1, word_t param_2, word_t param_3, long param_4, long param_5);
void sk_f_003e3e28(void);
void sk_f_003e4048(word_t param_1, word_t param_2, code_t jt1);
void sk_f_003e42c4(void);
void sk_f_003e462c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5);
void sk_f_003e4700(void);
void sk_f_003e472c(void);
void sk_f_003e4754(void);
void sk_f_003e47d4(void);
void sk_f_003e488c(void);
void sk_f_003e4a78(void);
void sk_f_003e4c70(void);
void sk_f_003e4f34(word_t param_1, word_t param_2, word_t param_3, long param_4, long param_5);
void sk_f_003e5074(void);
void sk_f_003e535c(void);
void sk_f_003e557c(void);
void sk_f_003e5b18(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5);
void sk_f_003e5bec(void);
void sk_f_003e5c18(void);
void sk_f_003e5c30(word_t param_1, long param_2);
void sk_f_003e5d50(void);
void sk_f_003e5e08(void);
void sk_f_003e5fc8(void);
void sk_f_003e61c4(void);
void sk_f_003e62ec(void);
void sk_f_003e63a8(word_t param_1, word_t param_2, word_t param_3, long param_4);
void sk_f_003e64e0(void);
void sk_f_003e66e4(void);

/* ---- function bodies ---- */

extern void sk_lab_003da07c(void);
extern void sk_lab_003da25c(void);
extern void sk_lab_003db214(void);
extern void sk_lab_003db4f8(void);
extern void sk_lab_003db70c(void);
extern void sk_lab_003dc214(void);
extern void sk_lab_003dca9c(void);
extern void sk_lab_003dce40(void);
extern void sk_lab_003dd0b8(void);
extern void sk_lab_003dda40(void);
extern void sk_lab_003de0c0(void);
extern void sk_lab_003de298(void);
extern void sk_lab_003de86c(void);
extern void sk_lab_003df130(void);
extern void sk_lab_003df8b0(void);
extern void sk_lab_003dff30(void);
extern void sk_lab_003e05a8(void);
extern void sk_lab_003e0aa4(void);
extern void sk_lab_003e1460(void);
extern void sk_lab_003e1b10(void);
extern void sk_lab_003e1ff0(void);
extern void sk_lab_003e2458(void);
extern void sk_lab_003e2874(void);
extern void sk_lab_003e2cdc(void);
extern void sk_lab_003e370c(void);
extern void sk_lab_003e3908(void);
extern void sk_lab_003e3f5c(void);
extern void sk_lab_003e4194(void);
extern void sk_lab_003e49bc(void);
extern void sk_lab_003e4b90(void);
extern void sk_lab_003e4dec(void);
extern void sk_lab_003e5494(void);
extern void sk_lab_003e57c0(void);
extern void sk_lab_003e60e4(void);
extern void sk_lab_003e6808(void);
extern void sk_lab_00614a7c(void);

/* FUN_003d95cc @ 0x003d95cc   (est. sk_f_003d95cc — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003d95cc(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003d95cc(void)
{
sk_h_00406574();
  sk_f_003d9600();
  sk_h_0036b270();
  return;
}

/* FUN_003d9600 @ 0x003d9600   (est. sk_f_003d9600 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003d9600(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003d9600(void)
{
sk_h_003e6d08();
  return;
}

/* FUN_003d961c @ 0x003d961c   (est. sk_f_003d961c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003d961c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003d961c(word_t param_1, word_t param_2, word_t param_3)
{
word_t u0;
  word_t ex0;
  
  u0 = sk_h_0040654c(param_2,param_3,param_3);
  sk_h_00377824(u0,ex0);
  sk_h_00350744(param_1);
  sk_h_000839d8();
  return;
}

/* FUN_003d96ac @ 0x003d96ac   (est. sk_f_003d96ac — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003d96ac(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003d96ac(void)
{
word_t u0;
  word_t u1;
  long ex11;
  long ex12;
  long ex0;
  long ex1;
  long ex2;
  long ex3;
  long ex4;
  long ex13;
  word_t ex5;
  word_t ex6;
  word_t ex7;
  word_t ex8;
  word_t ex9;
  word_t ex10;
  long ux0;
  word_t ux1;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  sk_h_00407214();
  sk_h_003509c8();
  u0 = sk_h_004078e8(*(word_t *)(ex13 + 0x40));
  *(word_t *)(ux0 + 0x30) = u0;
  *(word_t *)(ux0 + 0x38) = *(word_t *)(ex11 + 0x20);
  *(word_t *)(ux0 + 0x40) = *(word_t *)(ex11 + 0x10);
  u0 = sk_h_0040807c();
  *(word_t *)(ux0 + 0x48) = u0;
  sk_h_00350500();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0x50) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x58) = ex5;
  u0 = sk_h_004078e8(*(word_t *)(ex12 + 0x40));
  *(word_t *)(ux0 + 0x60) = u0;
  sk_h_00406f50();
  *(word_t *)(ux0 + 0x68) = ex6;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux0 + 0x70) = u0;
  *(word_t *)(ux0 + 0x78) = *(word_t *)(ex11 + 0x28);
  sk_h_00350548(0xff);
  u0 = sk_h_00377824().lo;;
  *(word_t *)(ux0 + 0x80) = u0;
  sk_h_00350500();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0x88) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x90) = ex7;
  u0 = sk_h_004081b4(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux0 + 0x98) = u0;
  u0 = sk_h_0040bb18(ux1 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0xa0) = u0;
  sk_h_00406f50();
  *(word_t *)(ux0 + 0xa8) = ex8;
  u1 = *(long *)(ex2 + 0x40) + 0xf;
  u0 = sk_h_0040bb18(u1 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0xb0) = u0;
  u0 = sk_h_0040bb18(u1 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0xb8) = u0;
  sk_h_00350548(0xff);
  u1 = sk_h_00377824().lo;;
  *(word_t *)(ux0 + 0xc0) = u1;
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 200) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0xd0) = ex9;
  u0 = sk_h_004078e8(*(word_t *)(ex3 + 0x40));
  *(word_t *)(ux0 + 0xd8) = u0;
  sk_h_0040683c();
  *(word_t *)(ux0 + 0xe0) = ex10;
  u0 = sk_h_00407b48(*(word_t *)(ex4 + 0x40));
  *(word_t *)(ux0 + 0xe8) = u0;
  u0 = sk_h_0040bb18(u1 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0xf0) = u0;
  sk_h_00407594();
  sk_h_00407c78();
  sk_h_00408db8();
  return;
}

/* FUN_003d98d8 @ 0x003d98d8   (est. sk_f_003d98d8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003d98d8(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003d98d8(void)
{
int i0;
  byte zf;
  word_t u0;
  word_t *p0;
  long l0;
  code_t *jt0;
  word_t ex4;
  code_t *ex5;
  code_t *ex0;
  word_t ex6;
  word_t ex1;
  code_t *ex7;
  code_t *ex8;
  code_t *ex2;
  word_t ex9;
  word_t ex3;
  word_t u2;
  long ux0;
  sk16_t a0;
  code_t *jt1;
  
  u0 = sk_h_00407e6c();
  a0 = sk_h_00407924();
  i0 = *(int *)(*(long *)(ux0 + 0x18) + 0x3c);
  *(int *)(ux0 + 0x158) = i0;
  if ((*(byte *)(*(long *)(ux0 + 0x20) + (long)i0) & 1) != 0) {
    sk_h_0040698c();
    sk_h_0040686c();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24(ex4);
    a0 = sk_h_0040678c();
    sk_h_004076a8(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003d9988. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  *(word_t *)(ux0 + 0x15c) = *(word_t *)(*(long *)(ux0 + 0x18) + 0x38);
  *(word_t *)(ux0 + 0xf8) = *(word_t *)(*(long *)(ux0 + 0xd0) + 0x10);
  sk_h_00408460(a0.lo,a0.hi,*(word_t *)(ux0 + 200));
  sk_dispatch((code_t)ex7);sk_h_00406420();
  if ((bool)zf) {
    u2 = *(word_t *)(ux0 + 0x38);
    l0 = *(long *)(ux0 + 0x40);
    sk_h_00353930(*(word_t *)(ux0 + 0xd0),*(word_t *)(ux0 + 0xd8),
                 *(word_t *)(ux0 + 200));
    *(code_t *)(ux0 + 0x120) = ex5;
    *(word_t *)(ux0 + 0x128) = ex6;
    sk_dispatch((code_t)ex5);sk_h_0040652c();
    sk_h_00406608();
    sk_h_004068f4();
    sk_h_00406268();
    sk_h_0040bb18(*(word_t *)(l0 + 4));
    p0 = (word_t *)sk_h_00406fe0();
    *(word_t **)(ux0 + 0x130) = p0;
    *p0 = ex9;
    a0 = sk_h_00406b84();
    jt1 = ex8;
  }
  else {
    u2 = *(word_t *)(ux0 + 0xc0);
    a0 = sk_h_00406894(*(word_t *)(ux0 + 0xe0),*(word_t *)(ux0 + 0xf0),
                          *(word_t *)(ux0 + 0xd8));
    *(code_t *)(ux0 + 0x100) = ex0;
    *(word_t *)(ux0 + 0x108) = ex1;
    sk_dispatch((code_t)ex0, a0.lo,a0.hi,u2);u2 = sk_h_004067f8();
    sk_h_003fcc1c();
    l0 = sk_h_004062c8();
    sk_h_0040bb18(*(word_t *)(l0 + 4));
    p0 = (word_t *)sk_h_00406fe0();
    *(word_t **)(ux0 + 0x110) = p0;
    *p0 = ex3;
    a0 = sk_h_00406b24();
    jt1 = ex2;
  }
  sk_h_004076a8(a0.lo,a0.hi,u2,jt1,u0);
                    /* WARNING: Could not recover jumptable at 0x003d9ab8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003d9b94 @ 0x003d9b94   (est. sk_f_003d9b94 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003d9b94(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003d9b94(void)
{
word_t u0;
  word_t u1;
  word_t u2;
  byte zf;
  word_t u3;
  word_t *p0;
  long l0;
  code_t *jt1;
  code_t *jt0;
  code_t *ex7;
  code_t *ex0;
  code_t *ex1;
  word_t ex2;
  code_t *ex8;
  code_t *ex3;
  code_t *ex4;
  word_t ex9;
  word_t ex5;
  word_t ex10;
  word_t ex6;
  word_t u5;
  long l1;
  long ux0;
  long l2;
  word_t *p1;
  sk16_t a0;
  
  u3 = sk_h_0040785c();
  sk_h_00407adc();
  u5 = *(word_t *)(ux0 + 0xa0);
  sk_h_00406be4();
  if ((bool)zf) {
    l0 = *(long *)(ux0 + 0x90);
    sk_dispatch(*(code_t *)(*(long *)(ux0 + 0xe0) + 8), *(word_t *)(ux0 + 0xf0),*(word_t *)(ux0 + 0xc0));sk_h_003507e0(*(word_t *)(l0 + 8));
    sk_dispatch((code_t)ex7);sk_h_00407764();
    sk_dispatch((code_t)ex0);jt0 = *(code_t *)(ux0 + 0xc0);
    sk_h_00350744(*(long *)(ux0 + 0x20) + (long)*(int *)(ux0 + 0x15c));
    a0 = sk_h_000839d8();
    sk_h_00406fb0(*(word_t *)(ux0 + 0xf8),a0.lo,a0.hi,
                 *(word_t *)(ux0 + 200));
    sk_dispatch((code_t)ex1);sk_h_00406420();
    if ((bool)zf) {
      l0 = *(long *)(ux0 + 0x40);
      sk_h_00353930(*(word_t *)(ux0 + 0xd0),*(word_t *)(ux0 + 0xd8),
                   *(word_t *)(ux0 + 200));
      *(code_t *)(ux0 + 0x120) = ex8;
      *(word_t *)(ux0 + 0x128) = ex9;
      sk_dispatch((code_t)ex8);sk_h_0040652c();
      sk_h_00406608();
      sk_h_004068f4();
      sk_h_00406268();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x130) = p0;
      *p0 = ex10;
      sk_h_00406b84();
    }
    else {
      u3 = *(word_t *)(ux0 + 0xc0);
      a0 = sk_h_00406894(*(word_t *)(ux0 + 0xe0),*(word_t *)(ux0 + 0xf0),
                             *(word_t *)(ux0 + 0xd8));
      *(code_t *)(ux0 + 0x100) = ex4;
      *(word_t *)(ux0 + 0x108) = ex5;
      sk_dispatch((code_t)ex4, a0.lo,a0.hi,u3);sk_h_004067f8();
      sk_h_003fcc1c();
      l0 = sk_h_004062c8();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x110) = p0;
      *p0 = ex6;
      sk_h_00406b24();
    }
    sk_h_00408404();
    sk_h_00407504();
                    /* WARNING: Could not recover jumptable at 0x003d9e4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l2 = (long)*(int *)(ux0 + 0x15c);
  u0 = *(word_t *)(ux0 + 200);
  l0 = *(long *)(ux0 + 0xd0);
  u1 = *(word_t *)(ux0 + 0xb8);
  u2 = *(word_t *)(ux0 + 0xc0);
  l1 = *(long *)(ux0 + 0x20);
  p1 = (word_t *)(*(long *)(ux0 + 0xa8) + 0x20);
  jt0 = (code_t *)*p1;
  sk_h_00350968(u1);
  sk_dispatch((code_t)jt0);p0 = (word_t *)(l0 + 8);
  sk_dispatch((code_t)*(p0), l1 + l2,u0);sk_h_00408440();
  sk_dispatch((code_t)ex3);sk_h_00350750(l1 + l2);
  sk_h_0040764c();
  sk_dispatch((code_t)jt0);sk_h_0040698c();
  sk_h_00406cf0();
  sk_h_0040bd24(u5);
  sk_h_0040bd24(l1);
  sk_h_0040bd24(jt0);
  sk_h_0040bd24(u2);
  sk_h_0040bd24(u1);
  sk_h_0040bd24(l2);
  sk_h_0040bd24(p0);
  sk_h_0040bd24(p1);
  sk_h_0040bd24(ex2);
  a0 = sk_h_0040678c();
  sk_h_00407504(a0.lo,a0.hi,u3);
                    /* WARNING: Could not recover jumptable at 0x003d9dbc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003d9f0c @ 0x003d9f0c   (est. sk_f_003d9f0c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003d9f0c(undefined8 param_1,undefined8 param_2,code *jt1)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003d9f0c(word_t param_1, word_t param_2, code_t jt1)
{
long l0;
  int i0;
  byte zf;
  word_t u0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  word_t ex2;
  long ex0;
  code_t *ex3;
  code_t *ex1;
  word_t ex4;
  long ux0;
  long l1;
  sk16_t a0;
  
  u0 = sk_h_00407e6c();
  sk_h_00407924();
  u1 = sk_h_00406420();
  if ((bool)zf) {
    i0 = *(int *)(ux0 + 0x158);
    l1 = *(long *)(ux0 + 0x20);
    sk_h_0040711c(*(word_t *)(ux0 + 0x58),u1,*(word_t *)(ux0 + 0x50));
    sk_dispatch((code_t)ex3);*(byte *)(l1 + i0) = 1;
    sk_h_0040698c();
    sk_h_0040686c();
    sk_h_0040bd24((long)i0);
    sk_h_0040bd24(1);
    sk_h_0040bd24(l1);
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24(ex2);
    a0 = sk_h_0040678c();
    sk_h_004076a8(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003d9fdc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x18);
  l0 = *(long *)(ux0 + 0x20);
  sk_h_00406bd4(*(word_t *)(ux0 + 0x68),*(word_t *)(ux0 + 0x70));
  sk_dispatch((code_t)ex1);sk_h_004062a8(*(word_t *)(l0 + *(int *)(l1 + 0x34)));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x140) = p0;
  *p0 = ex4;
  p0[1] = (word_t)&sk_lab_003da07c;
  sk_h_00408380(*(word_t *)(ux0 + 0x30),*(word_t *)(ux0 + 0x70));
  sk_h_004076a8();
                    /* WARNING: Could not recover jumptable at 0x003da078. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003da178 @ 0x003da178   (est. sk_f_003da178 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003da178(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003da178(void)
{
word_t u0;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex0;
  word_t ex1;
  word_t u2;
  word_t u3;
  long ux0;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  u2 = *(word_t *)(ux0 + 0xc0);
  u3 = *(word_t *)(ux0 + 0x78);
  u0 = *(word_t *)(ux0 + 0x28);
  sk_h_000a649c(u3);
  sk_h_004081fc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  sk_h_00377bec(u3,u0,u2);
  sk_h_003fcc1c();
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x148) = p0;
  *p0 = ex1;
  p0[1] = (word_t)&sk_lab_003da25c;
  sk_h_00407814(*(word_t *)(ux0 + 0x98),*(word_t *)(ux0 + 0xc0));
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003da258. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003da330 @ 0x003da330   (est. sk_f_003da330 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003da330(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003da330(void)
{
word_t u0;
  word_t u1;
  word_t u2;
  word_t u3;
  word_t u4;
  byte zf;
  word_t u5;
  word_t *p0;
  long l0;
  code_t *jt1;
  code_t *jt0;
  code_t *ex6;
  code_t *ex0;
  code_t *ex1;
  word_t ex2;
  code_t *ex7;
  code_t *ex3;
  word_t ex8;
  word_t ex4;
  word_t ex9;
  word_t ex5;
  word_t u7;
  long ux0;
  code_t *pc0;
  long l1;
  sk16_t a0;
  
  u5 = sk_h_0040785c();
  sk_h_00407adc();
  u7 = *(word_t *)(ux0 + 0x98);
  sk_h_00406be4();
  if ((bool)zf) {
    jt0 = *(code_t *)(ux0 + 0x120);
    l0 = *(long *)(ux0 + 0x90);
    sk_dispatch(*(code_t *)(*(long *)(ux0 + 0xe0) + 8), *(word_t *)(ux0 + 0xe8),*(word_t *)(ux0 + 0xc0));sk_h_003507e0(*(word_t *)(l0 + 8));
    sk_dispatch((code_t)ex6);sk_h_00408410();
    sk_dispatch((code_t)jt0);jt0 = *(code_t *)(ux0 + 0xc0);
    sk_h_00350744(*(long *)(ux0 + 0x20) + (long)*(int *)(ux0 + 0x15c));
    a0 = sk_h_000839d8();
    sk_h_00406fb0(*(word_t *)(ux0 + 0xf8),a0.lo,a0.hi,
                 *(word_t *)(ux0 + 200));
    sk_dispatch((code_t)ex0);sk_h_00406420();
    if ((bool)zf) {
      l0 = *(long *)(ux0 + 0x40);
      sk_h_00353930(*(word_t *)(ux0 + 0xd0),*(word_t *)(ux0 + 0xd8),
                   *(word_t *)(ux0 + 200));
      *(code_t *)(ux0 + 0x120) = ex7;
      *(word_t *)(ux0 + 0x128) = ex8;
      sk_dispatch((code_t)ex7);sk_h_0040652c();
      sk_h_00406608();
      sk_h_004068f4();
      sk_h_00406268();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x130) = p0;
      *p0 = ex9;
      sk_h_00406b84();
    }
    else {
      u5 = *(word_t *)(ux0 + 0xc0);
      a0 = sk_h_00406894(*(word_t *)(ux0 + 0xe0),*(word_t *)(ux0 + 0xf0),
                             *(word_t *)(ux0 + 0xd8));
      *(code_t *)(ux0 + 0x100) = ex3;
      *(word_t *)(ux0 + 0x108) = ex4;
      sk_dispatch((code_t)ex3, a0.lo,a0.hi,u5);sk_h_004067f8();
      sk_h_003fcc1c();
      l0 = sk_h_004062c8();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x110) = p0;
      *p0 = ex5;
      sk_h_00406b24();
    }
    sk_h_00408404();
    sk_h_00407504();
                    /* WARNING: Could not recover jumptable at 0x003da5d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  jt0 = *(code_t *)(ux0 + 0x120);
  u2 = *(word_t *)(ux0 + 0x128);
  l0 = (long)*(int *)(ux0 + 0x15c);
  u0 = *(word_t *)(ux0 + 0xe0);
  u1 = *(word_t *)(ux0 + 0xc0);
  u3 = *(word_t *)(ux0 + 200);
  u4 = *(word_t *)(ux0 + 0xb0);
  l1 = *(long *)(ux0 + 0x20);
  p0 = (word_t *)(*(long *)(ux0 + 0xa8) + 0x20);
  pc0 = (code_t *)*p0;
  sk_h_00350968(u4);
  sk_dispatch((code_t)pc0);sk_dispatch((code_t)jt0, u2,l1 + l0,u3);sk_h_004083f0();
  sk_dispatch((code_t)ex1);sk_h_00350750(l1 + l0);
  sk_h_0040764c();
  sk_dispatch((code_t)pc0);sk_h_0040698c();
  sk_h_00406cf0();
  sk_h_0040bd24(u7);
  sk_h_0040bd24(u0);
  sk_h_0040bd24(pc0);
  sk_h_0040bd24(u1);
  sk_h_0040bd24(u4);
  sk_h_0040bd24(l0);
  sk_h_0040bd24(p0);
  sk_h_0040bd24(l1);
  sk_h_0040bd24(ex2);
  a0 = sk_h_0040678c();
  sk_h_00407504(a0.lo,a0.hi,u5);
                    /* WARNING: Could not recover jumptable at 0x003da548. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003da7f8 @ 0x003da7f8   (est. sk_f_003da7f8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003da7f8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003da7f8(word_t param_1, word_t param_2, word_t param_3, long param_4, long param_5, word_t param_6)
{
word_t u0;
  word_t u1;
  word_t u2;
  long ex18;
  long l0;
  long ex19;
  long ex0;
  long ex1;
  long ex2;
  long ex3;
  long ex4;
  long ex5;
  long ex6;
  code_t *ex7;
  word_t ex8;
  word_t ex9;
  long ex20;
  word_t ex10;
  word_t ex11;
  word_t ex12;
  word_t ex13;
  word_t ex14;
  word_t ex15;
  word_t ex16;
  word_t ex17;
  word_t u3;
  word_t u4;
  long ux0;
  sk16_t a0;
  
  sk_h_00408190();
  sk_h_004070d8();
  l0 = param_4;
  sk_h_00406f40();
  u4 = *(word_t *)(l0 + 0x18);
  *(word_t *)(ux0 + 0x40) = u4;
  sk_h_003509c8(u4);
  u0 = sk_h_004078e8(*(word_t *)(ex20 + 0x40));
  *(word_t *)(ux0 + 0x48) = u0;
  u3 = *(word_t *)(param_4 + 0x20);
  *(word_t *)(ux0 + 0x50) = u3;
  *(word_t *)(ux0 + 0x58) = *(word_t *)(param_4 + 0x10);
  sk_h_004083d8();
  sk_h_00350798();
  u0 = sk_h_004085b4();
  *(word_t *)(ux0 + 0x60) = u0;
  sk_h_000a6f88();
  *(word_t *)(ux0 + 0x68) = ex10;
  u1 = sk_h_004078e8(*(word_t *)(ex19 + 0x40));
  *(word_t *)(ux0 + 0x70) = u1;
  sk_h_00350798();
  u1 = sk_h_004085b4();
  *(word_t *)(ux0 + 0x78) = u1;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x80) = ex11;
  u1 = sk_h_00407b48(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux0 + 0x88) = u1;
  u1 = sk_h_0040bb18(u3 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x90) = u1;
  u0 = sk_h_00310d68(0,u0);
  *(word_t *)(ux0 + 0x98) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0xa0) = ex12;
  u0 = sk_h_00407b48(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux0 + 0xa8) = u0;
  sk_h_0040bb18(u3 & 0xfffffffffffffff0);
  sk_h_00408328();
  a0 = sk_h_0035050c();
  u2 = sk_h_00377824(a0.lo,a0.hi,u4).lo;
  *(word_t *)(ux0 + 0xc0) = u2;
  sk_h_000a6f88();
  *(word_t *)(ux0 + 200) = ex13;
  u3 = *(long *)(ex2 + 0x40) + 0xf;
  u0 = sk_h_0040bb18(u3 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0xd0) = u0;
  u0 = sk_h_0040bb18(u3 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0xd8) = u0;
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0xe0) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0xe8) = ex14;
  u0 = sk_h_00407b48(*(word_t *)(ex3 + 0x40));
  *(word_t *)(ux0 + 0xf0) = u0;
  u0 = sk_h_0040bb18(u2 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0xf8) = u0;
  u0 = sk_h_0040bb18(u2 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x100) = u0;
  u0 = sk_h_0040bb18(u2 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x108) = u0;
  sk_h_0035050c();
  u0 = sk_h_00377824().lo;;
  *(word_t *)(ux0 + 0x110) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x118) = ex15;
  u0 = sk_h_00407b48(*(word_t *)(ex4 + 0x40));
  *(word_t *)(ux0 + 0x120) = u0;
  u0 = sk_h_0040bb18(u2 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x128) = u0;
  u0 = sk_h_0040bb18(u2 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x130) = u0;
  u0 = sk_h_0040bb18(u2 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x138) = u0;
  u0 = sk_h_0040bb18(u2 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x140) = u0;
  sk_h_004083c0();
  sk_h_003510a0();
  u3 = sk_h_00377824().lo;;
  *(word_t *)(ux0 + 0x148) = u3;
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0x150) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x158) = ex16;
  u0 = sk_h_004078e8(*(word_t *)(ex5 + 0x40));
  *(word_t *)(ux0 + 0x160) = u0;
  sk_h_0040683c();
  *(word_t *)(ux0 + 0x168) = ex17;
  u0 = sk_h_00407b48(*(word_t *)(ex6 + 0x40));
  *(word_t *)(ux0 + 0x170) = u0;
  u0 = sk_h_0040bb18(u3 & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x178) = u0;
  if (ex18 == 0) {
    sk_h_00407248();
    u0 = ex9;
  }
  else {
    sk_h_00407374(param_3);
    sk_h_00084180();
    sk_dispatch((code_t)ex7);sk_h_0008e1ec();
    u0 = ex8;
  }
  *(word_t *)(ux0 + 0x180) = u0;
  *(word_t *)(ux0 + 0x188) = u4;
  sk_h_00353080();
  sk_h_00408178();
  sk_h_00408db8();
  return;
}

/* FUN_003dab54 @ 0x003dab54   (est. sk_f_003dab54 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dab54(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dab54(void)
{
int i0;
  byte zf;
  word_t u0;
  word_t *p0;
  long l0;
  code_t *jt0;
  code_t *ex4;
  code_t *ex0;
  word_t ex5;
  word_t ex1;
  code_t *ex6;
  code_t *ex7;
  code_t *ex2;
  word_t ex8;
  word_t ex3;
  long ux0;
  sk16_t a0;
  word_t sv0;
  word_t sv1;
  word_t sv2;
  word_t sv3;
  word_t sv4;
  word_t sv5;
  word_t sv6;
  word_t sv7;
  word_t sv8;
  word_t sv9;
  code_t *jt1;
  
  u0 = sk_h_00407840();
  a0 = sk_h_00407ad0();
  i0 = *(int *)(*(long *)(ux0 + 0x28) + 0x3c);
  *(int *)(ux0 + 0x1e8) = i0;
  if ((*(byte *)(*(long *)(ux0 + 0x30) + (long)i0) & 1) != 0) {
    sk_h_00406624();
    sk_h_00350744();
    sk_h_000839d8();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24(sv0);
    sk_h_0040bd24(sv1);
    sk_h_0040bd24(sv2);
    sk_h_0040bd24(sv3);
    sk_h_0040bd24(sv4);
    sk_h_0040bd24(sv5);
    sk_h_0040bd24(sv6);
    sk_h_0040bd24(sv7);
    sk_h_0040bd24(sv8);
    sk_h_0040bd24(sv9);
    sk_h_0040bd24(jt1);
    a0 = sk_h_0040678c();
    sk_h_004074e8(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003dac5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  *(word_t *)(ux0 + 0x1ec) = *(word_t *)(*(long *)(ux0 + 0x28) + 0x38);
  *(word_t *)(ux0 + 400) = *(word_t *)(*(long *)(ux0 + 0x158) + 0x10);
  sk_h_00408460(a0.lo,a0.hi,*(word_t *)(ux0 + 0x150));
  sk_dispatch((code_t)ex6);sk_h_00406420();
  if ((bool)zf) {
    l0 = *(long *)(ux0 + 0x58);
    sk_h_00353930(*(word_t *)(ux0 + 0x158),*(word_t *)(ux0 + 0x160),
                 *(word_t *)(ux0 + 0x150));
    *(code_t *)(ux0 + 0x1b0) = ex4;
    *(word_t *)(ux0 + 0x1b8) = ex5;
    sk_dispatch((code_t)ex4);sk_h_0040652c();
    u0 = sk_h_00406608();
    *(word_t *)(ux0 + 0x1c0) = u0;
    u0 = sk_h_00406e8c();
    *(word_t *)(ux0 + 0x1c8) = u0;
    sk_h_00406288();
    sk_h_0040bb18(*(word_t *)(l0 + 4));
    p0 = (word_t *)sk_h_00406fe0();
    *(word_t **)(ux0 + 0x1d0) = p0;
    *p0 = ex8;
    p0[1] = (word_t)&sk_lab_003db214;
    sk_h_004067b8(*(word_t *)(ux0 + 0xb0));
    jt1 = ex7;
  }
  else {
    u0 = *(word_t *)(ux0 + 0x148);
    a0 = sk_h_00406894(*(word_t *)(ux0 + 0x168),*(word_t *)(ux0 + 0x178),
                          *(word_t *)(ux0 + 0x160));
    *(code_t *)(ux0 + 0x198) = ex0;
    *(word_t *)(ux0 + 0x1a0) = ex1;
    sk_dispatch((code_t)ex0, a0.lo,a0.hi,u0);sk_h_004067f8();
    sk_h_003fcc4c();
    l0 = sk_h_00406374();
    sk_h_0040bb18(*(word_t *)(l0 + 4));
    p0 = (word_t *)sk_h_00406fe0();
    *(word_t **)(ux0 + 0x1a8) = p0;
    *p0 = ex3;
    sk_h_00406a5c();
    jt1 = ex2;
  }
  sk_h_004074e8();
                    /* WARNING: Could not recover jumptable at 0x003dadbc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003dae98 @ 0x003dae98   (est. sk_f_003dae98 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dae98(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dae98(void)
{
code_t *pc0;
  word_t u0;
  word_t u1;
  byte zf;
  word_t u2;
  word_t u3;
  word_t *p0;
  long l0;
  code_t *jt1;
  code_t *ex7;
  code_t *ex0;
  code_t *ex1;
  word_t u5;
  code_t *ex8;
  code_t *ex2;
  word_t u6;
  code_t *ex3;
  word_t ex9;
  word_t ex4;
  code_t *ex10;
  code_t *ex5;
  word_t ex11;
  word_t ex6;
  code_t *pc1;
  word_t u7;
  long ux0;
  word_t u8;
  long l1;
  word_t *p1;
  long l2;
  sk16_t a0;
  word_t sv0;
  word_t sv1;
  word_t sv2;
  word_t sv3;
  word_t sv4;
  word_t sv5;
  word_t sv6;
  code_t *jt0;
  
  u2 = sk_h_00407840();
  u3 = sk_h_00407ad0().lo;;
  sk_h_0040833c(*(word_t *)(ux0 + 0xe8),u3,*(word_t *)(ux0 + 0x108),
               *(word_t *)(ux0 + 0xe0));
  sk_dispatch((code_t)ex8);sk_h_00406420();
  if ((bool)zf) {
    l0 = *(long *)(ux0 + 0xe8);
    sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x168) + 8), *(word_t *)(ux0 + 0x178),*(word_t *)(ux0 + 0x148));sk_h_003507e0(*(word_t *)(l0 + 8));
    sk_dispatch((code_t)ex7);sk_h_00407764();
    sk_dispatch((code_t)ex0);sk_h_00350744(*(long *)(ux0 + 0x30) + (long)*(int *)(ux0 + 0x1ec));
    a0 = sk_h_000839d8();
    sk_h_00406fb0(*(word_t *)(ux0 + 400),a0.lo,a0.hi,
                 *(word_t *)(ux0 + 0x150));
    sk_dispatch((code_t)ex1);sk_h_00406420();
    if ((bool)zf) {
      l0 = *(long *)(ux0 + 0x58);
      sk_h_00353930(*(word_t *)(ux0 + 0x158),*(word_t *)(ux0 + 0x160),
                   *(word_t *)(ux0 + 0x150));
      *(code_t *)(ux0 + 0x1b0) = ex2;
      *(word_t *)(ux0 + 0x1b8) = ex9;
      sk_dispatch((code_t)ex2);sk_h_0040652c();
      u2 = sk_h_00406608();
      *(word_t *)(ux0 + 0x1c0) = u2;
      u2 = sk_h_00406e8c();
      *(word_t *)(ux0 + 0x1c8) = u2;
      sk_h_00406288();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x1d0) = p0;
      *p0 = ex11;
      p0[1] = (word_t)&sk_lab_003db214;
      sk_h_004067b8(*(word_t *)(ux0 + 0xb0));
      jt0 = ex10;
    }
    else {
      u2 = *(word_t *)(ux0 + 0x148);
      a0 = sk_h_00406894(*(word_t *)(ux0 + 0x168),*(word_t *)(ux0 + 0x178),
                             *(word_t *)(ux0 + 0x160));
      *(code_t *)(ux0 + 0x198) = ex3;
      *(word_t *)(ux0 + 0x1a0) = ex4;
      sk_dispatch((code_t)ex3, a0.lo,a0.hi,u2);sk_h_004067f8();
      sk_h_003fcc4c();
      l0 = sk_h_00406374();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x1a8) = p0;
      *p0 = ex6;
      sk_h_00406a5c();
      jt0 = ex5;
    }
    sk_h_004074e8();
                    /* WARNING: Could not recover jumptable at 0x003db210. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  pc0 = *(code_t *)(ux0 + 0x198);
  u1 = *(word_t *)(ux0 + 0x1a0);
  l2 = (long)*(int *)(ux0 + 0x1ec);
  u6 = *(word_t *)(ux0 + 0x178);
  u3 = *(word_t *)(ux0 + 0x150);
  l0 = *(long *)(ux0 + 0x158);
  u7 = *(word_t *)(ux0 + 0x148);
  u8 = *(word_t *)(ux0 + 0xd8);
  u0 = *(word_t *)(ux0 + 0xc0);
  l1 = *(long *)(ux0 + 0x30);
  u5 = *(word_t *)(ux0 + 0x10);
  p1 = (word_t *)(*(long *)(ux0 + 200) + 0x20);
  pc1 = (code_t *)*p1;
  sk_dispatch((code_t)pc1, u8,*(word_t *)(ux0 + 0x100),u0);p0 = (word_t *)(l0 + 8);
  sk_dispatch((code_t)*(p0), l1 + l2,u3);sk_dispatch((code_t)pc0, u1,l1 + l2,u6,u7);sk_h_00350750(l1 + l2);
  sk_h_000839d8();
  sk_h_003513b4(u5);
  sk_dispatch((code_t)pc1);sk_h_00406624();
  sk_h_00350750();
  sk_h_000839d8();
  sk_h_0040bd24(u3);
  sk_h_0040bd24(u7);
  sk_h_0040bd24(u8);
  sk_h_0040bd24(u0);
  sk_h_0040bd24(l1);
  sk_h_0040bd24(p0);
  sk_h_0040bd24(p1);
  sk_h_0040bd24(l2);
  sk_h_0040bd24(pc1);
  sk_h_0040bd24(sv0);
  sk_h_0040bd24(sv1);
  sk_h_0040bd24(sv2);
  sk_h_0040bd24(sv3);
  sk_h_0040bd24(sv4);
  sk_h_0040bd24(sv5);
  sk_h_0040bd24(sv6);
  sk_h_0040bd24(u6);
  sk_h_0040bd24(u5);
  sk_h_0040bd24(pc0);
  sk_h_0040bd24(u1);
  a0 = sk_h_0040678c();
  sk_h_004074e8(a0.lo,a0.hi,u2);
                    /* WARNING: Could not recover jumptable at 0x003db17c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003db300 @ 0x003db300   (est. sk_f_003db300 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003db300(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003db300(void)
{
int i0;
  word_t u0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  long ex0;
  code_t *ex1;
  code_t *ex2;
  word_t ex3;
  word_t u3;
  long l0;
  long l1;
  long ux0;
  sk16_t a0;
  word_t sv0;
  word_t sv1;
  word_t sv2;
  word_t sv3;
  word_t sv4;
  word_t sv5;
  word_t sv6;
  word_t sv7;
  word_t sv8;
  word_t sv9;
  word_t sv10;
  
  u0 = sk_h_00407840();
  u1 = sk_h_00407ad0().lo;;
  u3 = *(word_t *)(ux0 + 0x60);
  sk_h_0040833c(*(word_t *)(ux0 + 0xa0),u1,*(word_t *)(ux0 + 0xb0),
               *(word_t *)(ux0 + 0x98));
  sk_dispatch((code_t)ex1);a0 = sk_h_00351d24();
  i0 = sk_h_000839f8(a0.lo,a0.hi,u3);
  l1 = *(long *)(ux0 + 0x30);
  if (i0 == 1) {
    i0 = *(int *)(ux0 + 0x1e8);
    sk_dispatch(*(code_t *)(*(long *)(ux0 + 0xa0) + 8), *(word_t *)(ux0 + 0xa8),*(word_t *)(ux0 + 0x98));*(byte *)(l1 + i0) = 1;
    sk_h_00406624();
    sk_h_00350744();
    sk_h_000839d8();
    sk_h_0040bd24((long)i0);
    sk_h_0040bd24(1);
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24(l1);
    sk_h_0040bd24(sv0);
    sk_h_0040bd24(sv1);
    sk_h_0040bd24(sv2);
    sk_h_0040bd24(sv3);
    sk_h_0040bd24(sv4);
    sk_h_0040bd24(sv5);
    sk_h_0040bd24(sv6);
    sk_h_0040bd24(sv7);
    sk_h_0040bd24(sv8);
    sk_h_0040bd24(sv9);
    sk_h_0040bd24(sv10);
    a0 = sk_h_0040678c();
    sk_h_004074e8(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003db44c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x28);
  sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x68) + 0x20), *(word_t *)(ux0 + 0x70),*(word_t *)(ux0 + 0xa8),
             *(word_t *)(ux0 + 0x60));sk_h_004062a8(*(word_t *)(l1 + *(int *)(l0 + 0x34)));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x1d8) = p0;
  *p0 = ex3;
  p0[1] = (word_t)&sk_lab_003db4f8;
  jt1 = ex2;
  sk_h_004074e8(*(word_t *)(ux0 + 0x48),*(word_t *)(ux0 + 0x70),ex2,
               u0);
                    /* WARNING: Could not recover jumptable at 0x003db4f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003db61c @ 0x003db61c   (est. sk_f_003db61c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003db61c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003db61c(void)
{
word_t u0;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex0;
  word_t ex1;
  word_t u2;
  word_t u3;
  long ux0;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  u2 = *(word_t *)(ux0 + 0x148);
  u3 = *(word_t *)(ux0 + 0xb8);
  u0 = *(word_t *)(ux0 + 0x40);
  sk_h_000a649c(u3);
  sk_h_004081fc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  sk_h_00377bec(u3,u0,u2);
  sk_h_003fcc4c();
  l0 = sk_h_00406374();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x1e0) = p0;
  *p0 = ex1;
  p0[1] = (word_t)&sk_lab_003db70c;
  sk_h_00407990(*(word_t *)(ux0 + 0xf8),*(word_t *)(ux0 + 0x18),
               *(word_t *)(ux0 + 0x20),*(word_t *)(ux0 + 0x128),
               *(word_t *)(ux0 + 0x148));
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003db708. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003db7e0 @ 0x003db7e0   (est. sk_f_003db7e0 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003db7e0(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003db7e0(void)
{
code_t *pc0;
  word_t u0;
  word_t u1;
  word_t u2;
  word_t u3;
  byte zf;
  word_t u4;
  word_t u5;
  word_t *p0;
  long l0;
  code_t *jt1;
  code_t *ex6;
  code_t *ex0;
  word_t u7;
  code_t *ex7;
  code_t *ex1;
  code_t *ex2;
  word_t ex8;
  word_t ex3;
  code_t *ex9;
  code_t *ex4;
  word_t ex10;
  word_t ex5;
  long ux0;
  word_t u8;
  word_t *p1;
  long l1;
  code_t *pc1;
  long l2;
  sk16_t a0;
  word_t sv0;
  word_t sv1;
  word_t sv2;
  word_t sv3;
  word_t sv4;
  word_t sv5;
  word_t sv6;
  code_t *jt0;
  
  u4 = sk_h_00407840();
  u5 = sk_h_00407ad0().lo;;
  sk_h_0040833c(*(word_t *)(ux0 + 0xe8),u5,*(word_t *)(ux0 + 0xf8),
               *(word_t *)(ux0 + 0xe0));
  sk_dispatch((code_t)ex7);sk_h_00406420();
  if ((bool)zf) {
    pc0 = *(code_t *)(ux0 + 0x1b0);
    l0 = *(long *)(ux0 + 0xe8);
    sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x168) + 8), *(word_t *)(ux0 + 0x170),*(word_t *)(ux0 + 0x148));sk_h_003507e0(*(word_t *)(l0 + 8));
    sk_dispatch((code_t)ex6);sk_h_00408410();
    sk_dispatch((code_t)pc0);sk_h_00350744(*(long *)(ux0 + 0x30) + (long)*(int *)(ux0 + 0x1ec));
    a0 = sk_h_000839d8();
    sk_h_00406fb0(*(word_t *)(ux0 + 400),a0.lo,a0.hi,
                 *(word_t *)(ux0 + 0x150));
    sk_dispatch((code_t)ex0);sk_h_00406420();
    if ((bool)zf) {
      l0 = *(long *)(ux0 + 0x58);
      sk_h_00353930(*(word_t *)(ux0 + 0x158),*(word_t *)(ux0 + 0x160),
                   *(word_t *)(ux0 + 0x150));
      *(code_t *)(ux0 + 0x1b0) = ex1;
      *(word_t *)(ux0 + 0x1b8) = ex8;
      sk_dispatch((code_t)ex1);sk_h_0040652c();
      u4 = sk_h_00406608();
      *(word_t *)(ux0 + 0x1c0) = u4;
      u4 = sk_h_00406e8c();
      *(word_t *)(ux0 + 0x1c8) = u4;
      sk_h_00406288();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x1d0) = p0;
      *p0 = ex10;
      p0[1] = (word_t)&sk_lab_003db214;
      sk_h_004067b8(*(word_t *)(ux0 + 0xb0));
      jt0 = ex9;
    }
    else {
      u4 = *(word_t *)(ux0 + 0x148);
      a0 = sk_h_00406894(*(word_t *)(ux0 + 0x168),*(word_t *)(ux0 + 0x178),
                             *(word_t *)(ux0 + 0x160));
      *(code_t *)(ux0 + 0x198) = ex2;
      *(word_t *)(ux0 + 0x1a0) = ex3;
      sk_dispatch((code_t)ex2, a0.lo,a0.hi,u4);sk_h_004067f8();
      sk_h_003fcc4c();
      l0 = sk_h_00406374();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x1a8) = p0;
      *p0 = ex5;
      sk_h_00406a5c();
      jt0 = ex4;
    }
    sk_h_004074e8();
                    /* WARNING: Could not recover jumptable at 0x003dbb48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  pc0 = *(code_t *)(ux0 + 0x1b0);
  u0 = *(word_t *)(ux0 + 0x1b8);
  l2 = (long)*(int *)(ux0 + 0x1ec);
  l0 = *(long *)(ux0 + 0x168);
  u1 = *(word_t *)(ux0 + 0x170);
  u5 = *(word_t *)(ux0 + 0x148);
  u2 = *(word_t *)(ux0 + 0x150);
  u3 = *(word_t *)(ux0 + 0xd0);
  u8 = *(word_t *)(ux0 + 0xc0);
  l1 = *(long *)(ux0 + 0x30);
  u7 = *(word_t *)(ux0 + 0x10);
  p0 = (word_t *)(*(long *)(ux0 + 200) + 0x20);
  pc1 = (code_t *)*p0;
  sk_dispatch((code_t)pc1, u3,*(word_t *)(ux0 + 0xf0),u8);sk_dispatch((code_t)pc0, u0,l1 + l2,u2);p1 = (word_t *)(l0 + 0x20);
  sk_dispatch((code_t)*(p1), l1 + l2,u1,u5);sk_h_00350750(l1 + l2);
  sk_h_000839d8();
  sk_h_003513b4(u7);
  sk_dispatch((code_t)pc1);sk_h_00406624();
  sk_h_00350750();
  sk_h_000839d8();
  sk_h_0040bd24(u2);
  sk_h_0040bd24(u5);
  sk_h_0040bd24(u3);
  sk_h_0040bd24(u8);
  sk_h_0040bd24(p1);
  sk_h_0040bd24(l1);
  sk_h_0040bd24(pc1);
  sk_h_0040bd24(l2);
  sk_h_0040bd24(p0);
  sk_h_0040bd24(sv0);
  sk_h_0040bd24(sv1);
  sk_h_0040bd24(sv2);
  sk_h_0040bd24(sv3);
  sk_h_0040bd24(sv4);
  sk_h_0040bd24(sv5);
  sk_h_0040bd24(sv6);
  sk_h_0040bd24(pc0);
  sk_h_0040bd24(u0);
  sk_h_0040bd24(u1);
  sk_h_0040bd24(u7);
  a0 = sk_h_0040678c();
  sk_h_004074e8(a0.lo,a0.hi,u4);
                    /* WARNING: Could not recover jumptable at 0x003dbab4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003dc01c @ 0x003dc01c   (est. sk_f_003dc01c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dc01c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, long param_5)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dc01c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5)
{
long l0;
  word_t u0;
  long *pl0;
  long ux0;
  
  *(word_t *)(ux0 + 0x10) = param_4;
  l0 = sk_h_00377824(0,*(word_t *)(param_5 + 0x20),*(word_t *)(param_5 + 0x10),
                       &DAT_00614a5c,(word_t)&sk_lab_00614a7c).lo;
  *(long *)(ux0 + 0x18) = l0;
  l0 = *(long *)(l0 + -8);
  *(long *)(ux0 + 0x20) = l0;
  u0 = sk_h_0040bb18(*(long *)(l0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x28) = u0;
  pl0 = (long *)sk_h_0040bb18(DAT_0059ffbc);
  *(long **)(ux0 + 0x30) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)&DAT_00405fdc;
  sk_f_003da7f8((word_t)pl0,param_1,param_2,param_3,param_5,u0);
  return;
}

/* FUN_003dc158 @ 0x003dc158   (est. sk_f_003dc158 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dc158(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dc158(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6)
{
long l0;
  word_t *p0;
  code_t *jt0;
  word_t ex0;
  long ux0;
  sk16_t a0;
  
  sk_h_00407ca0();
  sk_h_0040700c();
  a0 = sk_h_00352700();
  *(word_t *)(ux0 + 0x30) = param_5;
  *(word_t *)(ux0 + 0x38) = param_6;
  *(word_t *)(ux0 + 0x20) = param_3;
  *(word_t *)(ux0 + 0x28) = param_4;
  *(long *)(ux0 + 0x18) = a0.hi;
  sk_h_003fcc1c(param_5);
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x40) = p0;
  *p0 = ex0;
  p0[1] = (word_t)&sk_lab_003dc214;
  sk_h_00406ab4(a0.lo);
                    /* WARNING: Could not recover jumptable at 0x003dc210. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003dc32c @ 0x003dc32c   (est. sk_f_003dc32c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dc32c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dc32c(void)
{
word_t u0;
  word_t u1;
  word_t u2;
  code_t *jt0;
  word_t u3;
  long ux0;
  sk16_t a0;
  
  u1 = sk_h_004079cc();
  sk_h_004070d8();
  u0 = *(word_t *)(ux0 + 0x38);
  u3 = *(word_t *)(ux0 + 0x28);
  *(word_t *)(ux0 + 0x10) = *(word_t *)(ux0 + 0x48);
  sk_h_0034a210();
  sk_h_00002534();
  a0 = sk_h_003504e8();
  u3 = sk_h_00377824(a0.lo,a0.hi,u3,&DAT_00614890).lo;
  sk_h_003513b4(u0);
  sk_h_00365b6c();
  a0 = sk_h_003507e0();
  u2 = sk_h_00377bec(a0.lo,a0.hi,u3,&DAT_00614890);
  sk_h_003698b0(u0,u3,u2);
  a0 = sk_h_00406a94();
  sk_h_004078f4(a0.lo,a0.hi,u1);
                    /* WARNING: Could not recover jumptable at 0x003dc3ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003dc6a0 @ 0x003dc6a0   (est. sk_f_003dc6a0 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dc6a0(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dc6a0(void)
{
word_t *p0;
  word_t u1;
  long l0;
  word_t in_x5;
  long ex0;
  long ex1;
  code_t *ux0;
  word_t ux1;
  word_t ux2;
  word_t ux3;
  
  sk_h_00084220();
  sk_h_00407484();
  sk_h_00407ab8();
  u1 = sk_h_0040654c();
  sk_h_00377824(u1,in_x5);
  sk_h_00349530();
  sk_dispatch(*(code_t *)(ex1 + 0x20), ex0);sk_h_0034d004(0);
  l0 = sk_dispatch((code_t)ux0);p0 = (word_t *)(ex0 + *(int *)(l0 + 0x2c));
  *p0 = ux2;
  p0[1] = ux1;
  sk_h_00084234(ux3);
  return;
}

/* FUN_003dc724 @ 0x003dc724   (est. sk_f_003dc724 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dc724(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dc724(void)
{
long l0;
  word_t u0;
  int *pi0;
  word_t *p0;
  code_t *jt0;
  long ex0;
  word_t ex1;
  word_t ex2;
  word_t ux0;
  word_t u2;
  long ux1;
  sk16_t a0;
  
  sk_h_0040790c();
  a0 = sk_h_004070d8();
  *(long *)(ux1 + 0x18) = a0.hi;
  *(word_t *)(ux1 + 0x20) = ux0;
  *(long *)(ux1 + 0x10) = a0.lo;
  u2 = *(word_t *)(a0.hi + 0x20);
  sk_h_00350bfc(0xff,u2);
  l0 = sk_h_00377824().lo;;
  *(long *)(ux1 + 0x28) = l0;
  sk_h_00350720();
  u0 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x30) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x38) = ex1;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux1 + 0x40) = u0;
  l0 = *(long *)(l0 + -8);
  *(long *)(ux1 + 0x48) = l0;
  u0 = sk_h_004078e8(*(word_t *)(l0 + 0x40));
  *(word_t *)(ux1 + 0x50) = u0;
  sk_h_00350bfc(0xff,u2);
  sk_h_00377824();
  sk_h_0035136c(u2);
  sk_h_00377bec();
  pi0 = (int *)sk_h_003fcc1c();
  sk_h_00350720();
  sk_h_00377dcc();
  jt0 = (code_t *)((long)pi0 + (long)*pi0);
  sk_h_0040bb18(pi0[1]);
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux1 + 0x58) = p0;
  *p0 = ex2;
  sk_h_00407d90();
  sk_h_003510a0();
  sk_h_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003dc8bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003dc97c @ 0x003dc97c   (est. sk_f_003dc97c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dc97c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dc97c(void)
{
long l0;
  long l1;
  byte zf;
  word_t u0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  long ex1;
  code_t *ex2;
  code_t *ex0;
  code_t *jt1;
  word_t ex3;
  word_t u3;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  u3 = *(word_t *)(ux0 + 0x28);
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x38),u1,*(word_t *)(ux0 + 0x30));
    sk_dispatch((code_t)ex2);sk_h_00407954();
    sk_h_00408374();
    sk_h_00406c5c();
    sk_h_0040bd24(u3);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003dc9fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x18);
  l1 = *(long *)(ux0 + 0x20);
  sk_h_00406bd4(*(word_t *)(ux0 + 0x48),*(word_t *)(ux0 + 0x50));
  sk_dispatch((code_t)ex0);sk_h_004062a8(*(word_t *)(l1 + *(int *)(l0 + 0x2c)));
  sk_h_0040bb18(*(word_t *)(ex1 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x68) = p0;
  *p0 = ex3;
  p0[1] = (word_t)&sk_lab_003dca9c;
  sk_h_00407610(p0,*(word_t *)(ux0 + 0x50));
                    /* WARNING: Could not recover jumptable at 0x003dca98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003dcb98 @ 0x003dcb98   (est. sk_f_003dcb98 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dcb98(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dcb98(void)
{
code_t *jt0;
  
  sk_h_00407000();
  sk_h_00407954();
  sk_h_00408374();
  sk_h_00406ee4();
  sk_h_0040bd24();
  sk_h_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003dcbec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003dcc4c @ 0x003dcc4c   (est. sk_f_003dcc4c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dcc4c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dcc4c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5, word_t param_6)
{
word_t u0;
  long l0;
  word_t u1;
  int *pi0;
  word_t *p0;
  long in_x3;
  code_t *jt0;
  long ex2;
  long ex0;
  word_t ex3;
  word_t ex1;
  word_t ex4;
  long ux0;
  word_t u3;
  sk16_t a0;
  
  sk_h_00407e6c();
  sk_h_00407924();
  sk_h_00406cc8();
  u3 = *(word_t *)(in_x3 + 0x20);
  sk_h_0035050c();
  sk_h_00351cd0();
  u0 = sk_h_00377824().lo;;
  *(word_t *)(ux0 + 0x40) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x48) = ex3;
  u0 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux0 + 0x50) = u0;
  sk_h_00351cd0(0xff,u3);
  l0 = sk_h_00377824().lo;;
  *(long *)(ux0 + 0x58) = l0;
  u0 = sk_h_00310d68(0,l0);
  *(word_t *)(ux0 + 0x60) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x68) = ex1;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux0 + 0x70) = u0;
  l0 = *(long *)(l0 + -8);
  *(long *)(ux0 + 0x78) = l0;
  u1 = sk_h_004078e8(*(word_t *)(l0 + 0x40));
  *(word_t *)(ux0 + 0x80) = u1;
  sk_h_00351cd0(0xff,u3);
  u1 = sk_h_00377824().lo;;
  a0 = sk_h_000dbd0c();
  sk_h_00377bec(a0.lo,a0.hi,u1,&DAT_00614a5c);
  pi0 = (int *)sk_h_003fcc4c();
  sk_h_00377dcc(0,u1);
  jt0 = (code_t *)((long)pi0 + (long)*pi0);
  sk_h_0040bb18(pi0[1]);
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x88) = p0;
  *p0 = ex4;
  p0[1] = (word_t)&sk_lab_003dce40;
  sk_h_00406ab4(u0);
  sk_h_004076a8();
                    /* WARNING: Could not recover jumptable at 0x003dce3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003dcf90 @ 0x003dcf90   (est. sk_f_003dcf90 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dcf90(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dcf90(void)
{
long l0;
  long l1;
  byte zf;
  word_t u0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  long ex1;
  code_t *ex2;
  code_t *ex0;
  code_t *jt1;
  word_t ex3;
  word_t u3;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  u3 = *(word_t *)(ux0 + 0x58);
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x68),u1,*(word_t *)(ux0 + 0x60));
    sk_dispatch((code_t)ex2);sk_h_004077a0();
    sk_h_004077cc();
    sk_h_00406c5c();
    sk_h_0040bd24(u3);
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003dd018. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x28);
  l1 = *(long *)(ux0 + 0x30);
  sk_h_00406bd4(*(word_t *)(ux0 + 0x78),*(word_t *)(ux0 + 0x80));
  sk_dispatch((code_t)ex0);sk_h_004062a8(*(word_t *)(l1 + *(int *)(l0 + 0x2c)));
  sk_h_0040bb18(*(word_t *)(ex1 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xa0) = p0;
  *p0 = ex3;
  p0[1] = (word_t)&sk_lab_003dd0b8;
  sk_h_00407610(p0,*(word_t *)(ux0 + 0x80));
                    /* WARNING: Could not recover jumptable at 0x003dd0b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003dd1dc @ 0x003dd1dc   (est. sk_f_003dd1dc — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd1dc(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd1dc(void)
{
code_t *jt0;
  
  sk_h_00406fd4();
  sk_h_004077a0();
  sk_h_004077cc();
  sk_h_00406ee4();
  sk_h_0040bd24();
  sk_h_0040bd24();
  sk_h_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003dd240. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003dd2e0 @ 0x003dd2e0   (est. sk_f_003dd2e0 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd2e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, long param_5)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd2e0(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5)
{
long l0;
  word_t u0;
  long *pl0;
  long ux0;
  
  *(word_t *)(ux0 + 0x10) = param_4;
  l0 = sk_h_00377824(0,*(word_t *)(param_5 + 0x20),*(word_t *)(param_5 + 0x10),
                       &DAT_00614a5c,(word_t)&sk_lab_00614a7c).lo;
  *(long *)(ux0 + 0x18) = l0;
  l0 = *(long *)(l0 + -8);
  *(long *)(ux0 + 0x20) = l0;
  u0 = sk_h_0040bb18(*(long *)(l0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x28) = u0;
  pl0 = (long *)sk_h_0040bb18(DAT_0059ffe4);
  *(long **)(ux0 + 0x30) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)&DAT_00405fdc;
  sk_f_003dcc4c((word_t)pl0,param_1,param_2,param_3,param_5,u0);
  return;
}

/* FUN_003dd418 @ 0x003dd418   (est. sk_f_003dd418 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd418(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd418(void)
{
code_t *ex0;
  code_t *ux0;
  long ux1;
  word_t ux2;
  
  sk_h_00084220();
  sk_h_0008409c();
  sk_h_0040654c();
  sk_h_003513b4();
  sk_h_00377824();
  sk_h_00351f10();
  sk_h_0007c1a4();
  sk_dispatch((code_t)DAT_00658c80);sk_h_0034b05c();
  sk_h_00407100();
  sk_h_00350518();
  sk_dispatch((code_t)ex0);sk_h_004082a8((long)*(int *)(ux1 + 0x2c));
  sk_h_00407700();
  sk_dispatch((code_t)ux0);sk_h_00084234(ux2);
  return;
}

/* FUN_003dd4c0 @ 0x003dd4c0   (est. sk_f_003dd4c0 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd4c0(long param_1,undefined8 param_2,undefined8 param_3)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd4c0(long param_1, word_t param_2, word_t param_3)
{
if (-1 < param_1) {
    sk_h_0035a7e8(param_1,param_2,param_2,param_3);
    sk_f_003dd540();
    return;
  }
  sk_h_0035ac70(s_Can_t_prefix_a_negative_number_o_005dbf40);
  sk_h_00406aa4();
  sk_h_0040697c();
                    /* WARNING: Subroutine does not return */
  sk_h_001afa84();
}

/* FUN_003dd540 @ 0x003dd540   (est. sk_f_003dd540 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd540(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd540(void)
{
long l0;
  long ex0;
  long ex1;
  code_t *ux0;
  sk16_t a0;
  word_t param_3;  /* register-ABI artifact */
  
  a0 = sk_h_00351da8();
  sk_h_003509c8(param_3,a0.lo,a0.lo);
  sk_dispatch(*(code_t *)(ex1 + 0x20), ex0);sk_h_00350548(0);
  l0 = sk_dispatch((code_t)ux0);*(long *)(ex0 + *(int *)(l0 + 0x24)) = a0.hi;
  return;
}

/* FUN_003dd5d0 @ 0x003dd5d0   (est. sk_f_003dd5d0 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd5d0(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd5d0(void)
{
long l0;
  long ex0;
  code_t *ux0;
  word_t ux1;
  long ux2;
  
  sk_h_0040679c();
  sk_h_0040654c();
  sk_h_00377824();
  sk_h_00349530();
  sk_dispatch(*(code_t *)(ex0 + 0x20));sk_h_00350548(0);
  l0 = sk_dispatch((code_t)ux0);*(word_t *)(ux2 + *(int *)(l0 + 0x24)) = ux1;
  return;
}

/* FUN_003dd660 @ 0x003dd660   (est. sk_f_003dd660 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd660(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd660(void)
{
long l0;
  word_t u0;
  word_t u1;
  word_t *p0;
  code_t *jt1;
  long l1;
  code_t *jt0;
  word_t ex0;
  word_t u3;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  u1 = sk_h_0040700c();
  l0 = *(long *)(ux0 + 0x18);
  l1 = *(long *)(*(long *)(ux0 + 0x20) + (long)*(int *)(l0 + 0x24));
  if (l1 != 0) {
    *(long *)(*(long *)(ux0 + 0x20) + (long)*(int *)(l0 + 0x24)) = l1 + -1;
    l0 = *(long *)(l0 + 0x18);
    sk_h_00406560();
    sk_h_00350624();
    sk_h_00377824();
    sk_h_0007c1c4();
    sk_h_00351584();
    sk_h_00377bec();
    sk_h_004068f4();
    sk_h_00406268();
    sk_h_0040bb18(*(word_t *)(l0 + 4));
    p0 = (word_t *)sk_h_00406fe0();
    *(word_t **)(ux0 + 0x28) = p0;
    *p0 = ex0;
    sk_h_004071c0();
    sk_h_00406ab4();
                    /* WARNING: Could not recover jumptable at 0x003dd740. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  u3 = *(word_t *)(ux0 + 0x10);
  sk_h_00406ce0(u1,*(word_t *)(l0 + 0x18),*(word_t *)(l0 + 0x10));
  sk_h_00377824(0);
  sk_h_00350744(u3);
  sk_h_000839d8();
  a0 = sk_h_0040678c();
  sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003dd788. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003dd840 @ 0x003dd840   (est. sk_f_003dd840 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd840(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd840(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5, word_t param_6)
{
word_t u0;
  word_t u1;
  long in_x3;
  long ex3;
  code_t *ex0;
  word_t ex1;
  word_t ex2;
  word_t ex4;
  long ux0;
  long ux1;
  
  sk_h_00406fd4();
  sk_h_00406cc8();
  *(word_t *)(ux1 + 0x40) = *(word_t *)(in_x3 + 0x18);
  u1 = *(word_t *)(in_x3 + 0x10);
  *(word_t *)(ux1 + 0x48) = u1;
  u0 = sk_h_00377824(0).lo;
  *(word_t *)(ux1 + 0x50) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x58) = ex4;
  u0 = sk_h_004078e8(*(word_t *)(ex3 + 0x40));
  *(word_t *)(ux1 + 0x60) = u0;
  if (ux0 == 0) {
    sk_h_00407248();
    u0 = ex2;
  }
  else {
    sk_h_00406590();
    sk_dispatch((code_t)ex0);sk_h_0008e1ec();
    u0 = ex1;
  }
  *(word_t *)(ux1 + 0x68) = u0;
  *(word_t *)(ux1 + 0x70) = u1;
  sk_h_00353080();
  sk_h_00408db8();
  return;
}

/* FUN_003dd920 @ 0x003dd920   (est. sk_f_003dd920 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dd920(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dd920(void)
{
long l0;
  word_t u0;
  word_t *p0;
  code_t *jt1;
  long l1;
  long l2;
  code_t *jt0;
  word_t ex0;
  word_t u2;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  l1 = (long)*(int *)(*(long *)(ux0 + 0x28) + 0x24);
  l2 = *(long *)(*(long *)(ux0 + 0x30) + l1);
  l0 = *(long *)(ux0 + 0x48);
  if (l2 != 0) {
    *(long *)(*(long *)(ux0 + 0x30) + l1) = l2 + -1;
    sk_h_0040652c();
    sk_h_00406608();
    sk_h_00406e8c();
    sk_h_00406288();
    sk_h_0040bb18(*(word_t *)(l0 + 4));
    p0 = (word_t *)sk_h_00406fe0();
    *(word_t **)(ux0 + 0x78) = p0;
    *p0 = ex0;
    p0[1] = (word_t)&sk_lab_003dda40;
    sk_h_00406f2c();
    sk_h_00406d70();
                    /* WARNING: Could not recover jumptable at 0x003dd9ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  u2 = *(word_t *)(ux0 + 0x10);
  sk_h_00406ce0();
  sk_h_00350968(0);
  sk_h_00377824();
  sk_h_00350744(u2);
  sk_h_000839d8();
  sk_h_0040bd24(*(word_t *)(ux0 + 0x60));
  a0 = sk_h_0040678c();
  sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003dda3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003ddc10 @ 0x003ddc10   (est. sk_f_003ddc10 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003ddc10(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, long param_5)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003ddc10(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5)
{
long l0;
  word_t u0;
  long *pl0;
  long ux0;
  
  *(word_t *)(ux0 + 0x10) = param_4;
  l0 = sk_h_00377824(0,*(word_t *)(param_5 + 0x18),*(word_t *)(param_5 + 0x10),
                       &DAT_00614a5c,(word_t)&sk_lab_00614a7c).lo;
  *(long *)(ux0 + 0x18) = l0;
  l0 = *(long *)(l0 + -8);
  *(long *)(ux0 + 0x20) = l0;
  u0 = sk_h_0040bb18(*(long *)(l0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x28) = u0;
  pl0 = (long *)sk_h_0040bb18(DAT_0059fff4);
  *(long **)(ux0 + 0x30) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)&DAT_00405fdc;
  sk_f_003dd840((word_t)pl0,param_1,param_2,param_3,param_5,u0);
  return;
}

/* FUN_003ddd44 @ 0x003ddd44   (est. sk_f_003ddd44 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003ddd44(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003ddd44(void)
{
long l0;
  word_t u0;
  code_t *pc0;
  word_t ex3;
  long ex0;
  code_t *ex1;
  long ex4;
  long ex2;
  word_t u1;
  word_t u2;
  word_t ux0;
  sk16_t a0;
  
  a0 = sk_h_0008e518();
  u1 = *(word_t *)(a0.lo + 0x10);
  sk_h_0007c028();
  sk_dispatch((code_t)DAT_00658c80, *(word_t *)(ex0 + 0x40));sk_h_000aa4ec();
  l0 = sk_h_00407784();
  u2 = *(word_t *)(l0 + 0x18);
  u0 = sk_h_0040654c();
  sk_h_00377824(u0,u2,u1);
  sk_h_00351f10();
  sk_h_0007c1a4();
  sk_dispatch((code_t)DAT_00658c80);sk_h_0034b0d4();
  sk_h_003510a0(*(word_t *)(ex4 + 0x10));
  sk_dispatch((code_t)ex1);pc0 = (code_t *)sk_h_000a649c(u2);
  sk_dispatch((code_t)pc0, u1,u2);sk_h_003509c8(a0.lo);
  sk_dispatch(*(code_t *)(ex2 + 8));sk_h_003510c4(ex3);
  ((code_t)a0.hi)();
  sk_h_0008e500(ux0);
  return;
}

/* FUN_003dde8c @ 0x003dde8c   (est. sk_f_003dde8c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dde8c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dde8c(void)
{
word_t ex0;
  sk16_t a0;
  
  sk_h_00407478();
  a0 = sk_h_0035a7e8();
  sk_f_003ddecc(a0.lo,a0.hi,ex0);
  sk_h_0036b270(ex0);
  return;
}

/* FUN_003ddecc @ 0x003ddecc   (est. sk_f_003ddecc — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003ddecc(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003ddecc(word_t param_1, word_t param_2, word_t param_3)
{
sk_h_003eaf4c();
  return;
}

/* FUN_003ddf04 @ 0x003ddf04   (est. sk_f_003ddf04 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003ddf04(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003ddf04(void)
{
word_t u0;
  long ex2;
  long ex0;
  word_t ex3;
  word_t ex1;
  long ux0;
  
  sk_h_00407000();
  sk_h_00406704();
  sk_h_004079a8();
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0x40) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x48) = ex3;
  u0 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux0 + 0x50) = u0;
  sk_h_0040683c();
  *(word_t *)(ux0 + 0x58) = ex1;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux0 + 0x60) = u0;
  sk_h_00407594();
  sk_h_00408db8();
  return;
}

/* FUN_003ddfbc @ 0x003ddfbc   (est. sk_f_003ddfbc — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003ddfbc(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003ddfbc(void)
{
long l0;
  word_t u0;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  code_t *ex0;
  word_t ex1;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_0040790c();
  sk_h_004070d8();
  if ((**(byte **)(ux0 + 0x20) & 1) != 0) {
    sk_h_00407604();
    sk_h_0040686c();
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_004079b4(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003de024. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x30);
  sk_h_0040652c();
  sk_h_00406608();
  sk_h_004068f4();
  sk_h_00406268();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x68) = p0;
  *p0 = ex1;
  p0[1] = (word_t)&sk_lab_003de0c0;
  sk_h_00406ab4(*(word_t *)(ux0 + 0x50));
  jt1 = ex0;
  sk_h_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003de0bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003de17c @ 0x003de17c   (est. sk_f_003de17c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003de17c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003de17c(void)
{
long l0;
  byte zf;
  word_t u0;
  word_t u1;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  long ex2;
  code_t *ex3;
  word_t ex0;
  code_t *ex1;
  word_t ex4;
  word_t u2;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  u2 = *(word_t *)(ux0 + 0x38);
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x48),u1,*(word_t *)(ux0 + 0x40));
    sk_dispatch((code_t)ex3);sk_h_00407604();
    sk_h_0040686c();
    sk_h_0040bd24(u2);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003de1fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x18);
  sk_h_00406894(*(word_t *)(ux0 + 0x58),*(word_t *)(ux0 + 0x60));
  *(word_t *)(ux0 + 0x78) = ex0;
  *(word_t *)(ux0 + 0x80) = ex4;
  sk_h_00350624();
  sk_dispatch((code_t)ex1);sk_h_004062e8((long)*(int *)(l0 + 0x28));
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(ex2 + 4));
  *(long **)(ux0 + 0x88) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003de298;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x60));
                    /* WARNING: Could not recover jumptable at 0x003de294. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003de33c @ 0x003de33c   (est. sk_f_003de33c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003de33c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003de33c(void)
{
word_t u0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  long ux0;
  sk16_t a0;
  
  sk_h_00407000();
  if (*(char *)(ux0 + 0x90) == '\x01') {
    sk_h_00407d14(*(word_t *)(ux0 + 0x80));
    u0 = sk_dispatch((code_t)ex1);a0.hi = 0;
    a0.lo = u0;
  }
  else {
    sk_h_00408280();
    sk_dispatch((code_t)ex0);a0 = sk_h_00408354();
  }
  sk_h_004069b0(a0.lo,a0.hi);
  sk_h_004070a0();
  sk_h_0040bd24();
  sk_h_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003de3c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003de418 @ 0x003de418   (est. sk_f_003de418 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003de418(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003de418(word_t param_1, word_t param_2, word_t param_3, long param_4, long param_5, word_t param_6)
{
word_t u0;
  long ex7;
  long ex0;
  long ex1;
  code_t *ex2;
  word_t ex3;
  word_t ex4;
  word_t ex8;
  word_t ex5;
  word_t ex6;
  long ux0;
  long ux1;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  sk_h_00406cc8();
  sk_h_00408308();
  *(word_t *)(ux1 + 0x48) = *(word_t *)(param_4 + 0x10);
  u0 = sk_h_0040684c();
  *(word_t *)(ux1 + 0x50) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x58) = ex8;
  u0 = sk_h_004078e8(*(word_t *)(ex7 + 0x40));
  *(word_t *)(ux1 + 0x60) = u0;
  sk_h_00406dd0();
  sk_h_00408454();
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x70) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x78) = ex5;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux1 + 0x80) = u0;
  sk_h_0040683c();
  *(word_t *)(ux1 + 0x88) = ex6;
  u0 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux1 + 0x90) = u0;
  if (ux0 == 0) {
    sk_h_00407248();
    u0 = ex4;
  }
  else {
    sk_h_00406590();
    sk_dispatch((code_t)ex2);sk_h_0008e1ec();
    u0 = ex3;
  }
  *(word_t *)(ux1 + 0x98) = u0;
  *(word_t *)(ux1 + 0xa0) = param_3;
  sk_h_00353080();
  sk_h_00407c78();
  sk_h_00408db8();
  return;
}

/* FUN_003de550 @ 0x003de550   (est. sk_f_003de550 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003de550(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003de550(void)
{
word_t u0;
  long l0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  code_t *ex0;
  word_t ex1;
  long ux0;
  sk16_t a0;
  
  u1 = sk_h_0040790c();
  sk_h_004070d8();
  if ((**(byte **)(ux0 + 0x30) & 1) != 0) {
    sk_h_00407bb8();
    u0 = *(word_t *)(ux0 + 0x60);
    sk_h_0040686c();
    sk_h_0040bd24();
    sk_h_0040bd24(u0);
    a0 = sk_h_0040678c();
    sk_h_004079b4(a0.lo,a0.hi,u1);
                    /* WARNING: Could not recover jumptable at 0x003de5c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x48);
  sk_h_0040652c();
  sk_h_00406608();
  sk_h_00406e8c();
  sk_h_00406288();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xa8) = p0;
  *p0 = ex1;
  u1 = sk_h_00407da0();
  sk_h_00406d70(u1,*(word_t *)(ux0 + 0x18),*(word_t *)(ux0 + 0x20));
  jt1 = ex0;
  sk_h_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003de65c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003de74c @ 0x003de74c   (est. sk_f_003de74c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003de74c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003de74c(void)
{
long l0;
  byte zf;
  word_t u0;
  word_t u1;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  long ex2;
  code_t *ex3;
  word_t ex0;
  code_t *ex1;
  word_t ex4;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  sk_h_00407aac();
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x78),u1,*(word_t *)(ux0 + 0x70));
    sk_dispatch((code_t)ex3);sk_h_00407bb8();
    u1 = *(word_t *)(ux0 + 0x60);
    sk_h_0040686c();
    sk_h_0040bd24();
    sk_h_0040bd24(u1);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003de7d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x28);
  sk_h_00406894(*(word_t *)(ux0 + 0x88),*(word_t *)(ux0 + 0x90));
  *(word_t *)(ux0 + 0xb0) = ex0;
  *(word_t *)(ux0 + 0xb8) = ex4;
  sk_h_00350624();
  sk_dispatch((code_t)ex1);sk_h_004062e8((long)*(int *)(l0 + 0x28));
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(ex2 + 4));
  *(long **)(ux0 + 0xc0) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003de86c;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x90));
                    /* WARNING: Could not recover jumptable at 0x003de868. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003de938 @ 0x003de938   (est. sk_f_003de938 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003de938(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003de938(void)
{
word_t u0;
  word_t u1;
  code_t *jt0;
  long ux0;
  sk16_t a0;
  
  sk_h_00406fd4();
  if (*(char *)(ux0 + 200) == '\x01') {
    u1 = sk_dispatch(*(code_t *)(ux0 + 0xb0), *(word_t *)(ux0 + 0xb8),*(word_t *)(ux0 + 0x10),
                       *(word_t *)(ux0 + 0x90),*(word_t *)(ux0 + 0x68));a0.hi = 0;
    a0.lo = u1;
  }
  else {
    sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x88) + 8), *(word_t *)(ux0 + 0x90),*(word_t *)(ux0 + 0x68));a0 = sk_h_00408354();
  }
  sk_h_00407bb8(a0.lo,a0.hi);
  u0 = *(word_t *)(ux0 + 0x60);
  sk_h_004070a0(*(word_t *)(ux0 + 0x10));
  sk_h_0040bd24();
  sk_h_0040bd24(u0);
  sk_h_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003de9e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003deb0c @ 0x003deb0c   (est. sk_f_003deb0c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003deb0c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, long param_5)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003deb0c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, long param_5)
{
long l0;
  word_t u0;
  long *pl0;
  long ux0;
  
  *(word_t *)(ux0 + 0x10) = param_4;
  l0 = sk_h_00377824(0,*(word_t *)(param_5 + 0x18),*(word_t *)(param_5 + 0x10),
                       &DAT_00614a5c,(word_t)&sk_lab_00614a7c).lo;
  *(long *)(ux0 + 0x18) = l0;
  l0 = *(long *)(l0 + -8);
  *(long *)(ux0 + 0x20) = l0;
  u0 = sk_h_0040bb18(*(long *)(l0 + 0x40) + 0xfU & 0xfffffffffffffff0);
  *(word_t *)(ux0 + 0x28) = u0;
  pl0 = (long *)sk_h_0040bb18(DAT_005a0004);
  *(long **)(ux0 + 0x30) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)&DAT_00405fdc;
  sk_f_003de418((word_t)pl0,param_1,param_2,param_3,param_5,u0);
  return;
}

/* FUN_003dec44 @ 0x003dec44   (est. sk_f_003dec44 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dec44(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,long param_6,undefined8 param_7)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dec44(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, long param_6, word_t param_7)
{
word_t u0;
  long l0;
  long ex6;
  long ex0;
  long ex1;
  long ex2;
  word_t ex7;
  word_t ex3;
  word_t ex4;
  word_t ex5;
  word_t ux0;
  long ux1;
  sk16_t a0;
  
  a0 = sk_h_00406fd4();
  *(word_t *)(ux1 + 0x40) = param_7;
  *(word_t *)(ux1 + 0x48) = ux0;
  *(word_t *)(ux1 + 0x30) = param_5;
  *(long *)(ux1 + 0x38) = param_6;
  *(word_t *)(ux1 + 0x20) = param_3;
  *(word_t *)(ux1 + 0x28) = param_4;
  *(sk16_t *)(ux1 + 0x10) = a0;
  l0 = *(long *)(param_6 + -8);
  *(long *)(ux1 + 0x50) = l0;
  u0 = sk_h_004078e8(*(word_t *)(l0 + 0x40));
  *(word_t *)(ux1 + 0x58) = u0;
  sk_h_00406da8();
  sk_h_00350974(0xff,param_7);
  u0 = sk_h_00377824().lo;;
  *(word_t *)(ux1 + 0x60) = u0;
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x68) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x70) = ex7;
  u0 = sk_h_004078e8(*(word_t *)(ex6 + 0x40));
  *(word_t *)(ux1 + 0x78) = u0;
  sk_h_0040683c();
  *(word_t *)(ux1 + 0x80) = ex3;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux1 + 0x88) = u0;
  sk_h_0007c028();
  *(word_t *)(ux1 + 0x90) = ex4;
  u0 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux1 + 0x98) = u0;
  sk_h_00350500();
  sk_h_00350974();
  u0 = sk_h_00377824().lo;;
  *(word_t *)(ux1 + 0xa0) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0xa8) = ex5;
  u0 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux1 + 0xb0) = u0;
  sk_h_00407594();
  sk_h_00408db8();
  return;
}

/* FUN_003dedd4 @ 0x003dedd4   (est. sk_f_003dedd4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dedd4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dedd4(void)
{
word_t u0;
  word_t u1;
  word_t u2;
  word_t *p0;
  code_t *jt0;
  code_t *ex0;
  code_t *ex1;
  word_t ex2;
  long ux0;
  long l0;
  sk16_t a0;
  
  sk_h_004079cc();
  sk_h_004070d8();
  u2 = *(word_t *)(ux0 + 0x98);
  u0 = *(word_t *)(ux0 + 0xa0);
  l0 = *(long *)(ux0 + 0x90);
  u1 = *(word_t *)(ux0 + 0x40);
  sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x50) + 0x10), *(word_t *)(ux0 + 0x10),*(word_t *)(ux0 + 0x18),
             *(word_t *)(ux0 + 0x38));sk_h_0035136c(*(word_t *)(l0 + 0x10),u2);
  sk_dispatch((code_t)ex0);sk_h_004070e4(u1);
  sk_h_00350618();
  sk_dispatch((code_t)ex1);sk_h_004068bc();
  a0 = sk_h_000dbd0c();
  u2 = sk_h_00377bec(a0.lo,a0.hi,u0);
  *(word_t *)(ux0 + 0xb8) = u2;
  u2 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0xc0) = u2;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 200) = p0;
  *p0 = ex2;
  sk_h_00407400();
  sk_h_004078f4();
                    /* WARNING: Could not recover jumptable at 0x003deec4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003defbc @ 0x003defbc   (est. sk_f_003defbc — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003defbc(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003defbc(void)
{
word_t u0;
  word_t u1;
  word_t u2;
  long l0;
  byte zf;
  word_t u3;
  word_t u4;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  code_t *ex1;
  code_t *ex0;
  word_t ex2;
  word_t u6;
  int *pi0;
  long ux0;
  word_t u7;
  word_t u8;
  sk16_t a0;
  
  u3 = sk_h_004079cc();
  sk_h_004070d8();
  u6 = *(word_t *)(ux0 + 0x78);
  u4 = sk_h_00406420();
  if ((bool)zf) {
    u2 = *(word_t *)(ux0 + 0xb0);
    u0 = *(word_t *)(ux0 + 0x98);
    u7 = *(word_t *)(ux0 + 0x88);
    u1 = *(word_t *)(ux0 + 0x68);
    l0 = *(long *)(ux0 + 0x70);
    u8 = *(word_t *)(ux0 + 0x58);
    sk_h_00353c00(*(word_t *)(ux0 + 0xa8),u4,*(word_t *)(ux0 + 0xa0));
    sk_dispatch((code_t)ex1);sk_dispatch(*(code_t *)(l0 + 8), u6,u1);sk_h_0040bd24(u2);
    sk_h_0040bd24(u0);
    sk_h_0040bd24(u7);
    sk_h_0040bd24(u6);
    sk_h_0040bd24(u8);
    a0 = sk_h_0040678c();
    sk_h_004078f4(a0.lo,a0.hi,u3);
                    /* WARNING: Could not recover jumptable at 0x003df078. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  pi0 = *(int **)(ux0 + 0x20);
  sk_h_00406bd4(*(word_t *)(ux0 + 0x80),*(word_t *)(ux0 + 0x88));
  sk_dispatch((code_t)ex0);jt1 = (code_t *)((long)pi0 + (long)*pi0);
  sk_h_0040bb18(pi0[1]);
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xd8) = p0;
  *p0 = ex2;
  p0[1] = (word_t)&sk_lab_003df130;
  sk_h_004078f4(*(word_t *)(ux0 + 0x58),*(word_t *)(ux0 + 0x10),
               *(word_t *)(ux0 + 0x88),jt1,u3);
                    /* WARNING: Could not recover jumptable at 0x003df12c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003df278 @ 0x003df278   (est. sk_f_003df278 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003df278(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003df278(void)
{
word_t *p0;
  code_t *jt0;
  long ex0;
  word_t ex1;
  long ux0;
  
  sk_h_00407000();
  sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x50) + 0x20), *(word_t *)(ux0 + 0x10),*(word_t *)(ux0 + 0x58),
             *(word_t *)(ux0 + 0x38));sk_h_004062a8(*(word_t *)(ux0 + 0xc0));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 200) = p0;
  *p0 = ex1;
  sk_h_00407400();
                    /* WARNING: Could not recover jumptable at 0x003df308. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003df548 @ 0x003df548   (est. sk_f_003df548 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003df548(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003df548(void)
{
word_t u0;
  word_t u1;
  word_t u2;
  word_t *p0;
  code_t *jt0;
  long ex1;
  code_t *ex0;
  code_t *ex2;
  word_t ex3;
  word_t ex4;
  long ux0;
  long l0;
  sk16_t a0;
  
  sk_h_004079cc();
  sk_h_004070d8();
  u2 = *(word_t *)(ux0 + 0x88);
  u1 = *(word_t *)(ux0 + 0x90);
  l0 = *(long *)(ux0 + 0x80);
  u0 = *(word_t *)(ux0 + 0x40);
  sk_h_0007c028(*(word_t *)(ux0 + 0x10),*(word_t *)(ux0 + 0x18),
               *(word_t *)(ux0 + 0x38));
  *(word_t *)(ux0 + 0xa8) = ex3;
  sk_dispatch(*(code_t *)(ex1 + 0x20));sk_h_0035136c(*(word_t *)(l0 + 0x10),u2);
  sk_dispatch((code_t)ex0);sk_h_004070e4(u0);
  sk_h_00350618();
  sk_dispatch((code_t)ex2);sk_h_004068bc();
  a0 = sk_h_000dbd0c();
  u2 = sk_h_00377bec(a0.lo,a0.hi,u1);
  *(word_t *)(ux0 + 0xb0) = u2;
  u2 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0xb8) = u2;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xc0) = p0;
  *p0 = ex4;
  sk_h_0040733c();
  sk_h_004078f4();
                    /* WARNING: Could not recover jumptable at 0x003df654. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003df748 @ 0x003df748   (est. sk_f_003df748 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003df748(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003df748(void)
{
word_t u0;
  word_t u1;
  word_t u2;
  long l0;
  byte zf;
  word_t u3;
  word_t u4;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  code_t *ex1;
  code_t *ex0;
  word_t u5;
  int *pi0;
  long ux0;
  word_t u6;
  sk16_t a0;
  
  u3 = sk_h_0040790c();
  sk_h_004070d8();
  u5 = *(word_t *)(ux0 + 0x68);
  u4 = sk_h_00406420();
  if ((bool)zf) {
    u2 = *(word_t *)(ux0 + 0xa0);
    u0 = *(word_t *)(ux0 + 0x88);
    u6 = *(word_t *)(ux0 + 0x78);
    u1 = *(word_t *)(ux0 + 0x58);
    l0 = *(long *)(ux0 + 0x60);
    sk_h_00353c00(*(word_t *)(ux0 + 0x98),u4,*(word_t *)(ux0 + 0x90));
    sk_dispatch((code_t)ex1);sk_dispatch(*(code_t *)(l0 + 8), u5,u1);sk_h_0040bd24(u2);
    sk_h_0040bd24(u0);
    sk_h_0040bd24(u6);
    sk_h_0040bd24(u5);
    a0 = sk_h_0040678c();
    sk_h_004079b4(a0.lo,a0.hi,u3);
                    /* WARNING: Could not recover jumptable at 0x003df7f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  pi0 = *(int **)(ux0 + 0x20);
  sk_h_00406bd4(*(word_t *)(ux0 + 0x70),*(word_t *)(ux0 + 0x78));
  sk_dispatch((code_t)ex0);jt1 = (code_t *)((long)pi0 + (long)*pi0);
  pl0 = (long *)sk_h_0040bb18(pi0[1]);
  *(long **)(ux0 + 0xd0) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003df8b0;
  sk_h_004080cc(*(word_t *)(ux0 + 0x10),*(word_t *)(ux0 + 0x78),
               jt1,u3);
                    /* WARNING: Could not recover jumptable at 0x003df8ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003df9dc @ 0x003df9dc   (est. sk_f_003df9dc — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003df9dc(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003df9dc(void)
{
word_t *p0;
  code_t *jt0;
  long ex0;
  word_t ex1;
  long ux0;
  
  sk_h_00407000();
  sk_h_004062a8(*(word_t *)(ux0 + 0xb8));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xc0) = p0;
  *p0 = ex1;
  sk_h_0040733c();
                    /* WARNING: Could not recover jumptable at 0x003dfa50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003dfc60 @ 0x003dfc60   (est. sk_f_003dfc60 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dfc60(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dfc60(void)
{
word_t u0;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  code_t *ex2;
  word_t ex3;
  long ux0;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  u0 = sk_h_00407cc4();
  sk_h_00407070(u0,*(word_t *)(ux0 + 0x10));
  sk_dispatch((code_t)ex1);sk_h_004067cc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  sk_h_00350470();
  u0 = sk_h_00377bec();
  *(word_t *)(ux0 + 0x80) = u0;
  u0 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0x88) = u0;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x90) = p0;
  *p0 = ex3;
  sk_h_00406944();
  jt0 = ex2;
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003dfd38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003dfe08 @ 0x003dfe08   (est. sk_f_003dfe08 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003dfe08(undefined8 param_1,undefined8 param_2,code *jt0)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003dfe08(word_t param_1, word_t param_2, code_t jt0)
{
word_t u0;
  word_t u1;
  word_t u2;
  long *pl0;
  code_t *jt1;
  code_t *ex1;
  code_t *ex0;
  long l1;
  long ux0;
  word_t u3;
  
  sk_h_00407ca0();
  sk_h_0040700c();
  u2 = sk_h_00406db8();
  *(int *)(ux0 + 0xb0) = (int)u2;
  if ((int)u2 == 1) {
    u1 = *(word_t *)(ux0 + 0x78);
    u0 = *(word_t *)(ux0 + 0x60);
    u3 = *(word_t *)(ux0 + 0x48);
    sk_h_00353c00(*(word_t *)(ux0 + 0x70),u2,*(word_t *)(ux0 + 0x68));
    sk_dispatch((code_t)ex1);sk_h_0040bd24(u1);
    sk_h_0040bd24(u0);
    sk_h_0040bd24();
    sk_h_0040bd24(u3);
    sk_h_00406e48();
    sk_h_00407e58();
                    /* WARNING: Could not recover jumptable at 0x003dfe9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x18);
  sk_h_00406bd4(*(word_t *)(ux0 + 0x40),*(word_t *)(ux0 + 0x48));
  sk_dispatch((code_t)ex0);sk_h_004065c8();
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(l1 + 4));
  *(long **)(ux0 + 0xa0) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003dff30;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x48));
                    /* WARNING: Could not recover jumptable at 0x003dff2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e0028 @ 0x003e0028   (est. sk_f_003e0028 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e0028(undefined8 param_1,undefined8 param_2,code *jt0)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e0028(word_t param_1, word_t param_2, code_t jt0)
{
word_t u0;
  word_t u1;
  word_t u2;
  word_t u3;
  word_t u4;
  word_t *p0;
  long ex0;
  code_t *ex1;
  code_t *jt1;
  word_t ex2;
  long ux0;
  
  sk_h_00407ca0();
  u4 = sk_h_0040700c();
  if ((*(byte *)(ux0 + 0xb4) & 1) != 0) {
    u2 = *(word_t *)(ux0 + 0x78);
    u0 = *(word_t *)(ux0 + 0x60);
    u1 = *(word_t *)(ux0 + 0x48);
    u3 = *(word_t *)(ux0 + 0x50);
    sk_h_0040711c(*(word_t *)(ux0 + 0x70),u4,*(word_t *)(ux0 + 0x68));
    sk_dispatch((code_t)ex1);sk_h_0040bd24(u2);
    sk_h_0040bd24(u0);
    sk_h_0040bd24(u3);
    sk_h_0040bd24(u1);
    sk_h_00406e48();
    sk_h_00407e58();
                    /* WARNING: Could not recover jumptable at 0x003e00b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  sk_h_004062a8(*(word_t *)(ux0 + 0x88));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x90) = p0;
  *p0 = ex2;
  sk_h_00406944();
                    /* WARNING: Could not recover jumptable at 0x003e0128. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e012c @ 0x003e012c   (est. sk_f_003e012c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e012c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e012c(word_t param_1, word_t param_2, long param_3, word_t param_4, word_t param_5)
{
word_t u0;
  word_t in_x3;
  long ex5;
  long ex0;
  long ex1;
  word_t ex6;
  long ex2;
  word_t ex3;
  word_t ex4;
  long ux0;
  
  sk_h_00406fd4();
  sk_h_0040752c();
  sk_h_00406da8();
  sk_h_00377824(0,in_x3);
  sk_h_004079a8();
  sk_h_000a6f88();
  *(word_t *)(ux0 + 0x40) = ex6;
  u0 = sk_h_004078e8(*(word_t *)(ex5 + 0x40));
  *(word_t *)(ux0 + 0x48) = u0;
  sk_h_00350798();
  sk_h_00310d68();
  sk_h_00351f10();
  u0 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux0 + 0x50) = u0;
  sk_h_0007c028();
  *(word_t *)(ux0 + 0x58) = ex3;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux0 + 0x60) = u0;
  sk_h_00407090();
  sk_h_00351584();
  u0 = sk_h_00377824().lo;;
  *(word_t *)(ux0 + 0x68) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x70) = ex4;
  u0 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux0 + 0x78) = u0;
  sk_h_00407594();
  sk_h_00408db8();
  return;
}

/* FUN_003e025c @ 0x003e025c   (est. sk_f_003e025c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e025c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e025c(void)
{
word_t u0;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  code_t *ex2;
  word_t ex3;
  long ux0;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  u0 = sk_h_00407cc4();
  sk_h_00407070(u0,*(word_t *)(ux0 + 0x30));
  sk_dispatch((code_t)ex1);sk_h_004067cc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  sk_h_00350470();
  u0 = sk_h_00377bec();
  *(word_t *)(ux0 + 0x80) = u0;
  u0 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0x88) = u0;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x90) = p0;
  *p0 = ex3;
  sk_h_00406944();
  jt0 = ex2;
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e0334. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e0404 @ 0x003e0404   (est. sk_f_003e0404 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e0404(undefined8 param_1,undefined8 param_2,code *jt0)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e0404(word_t param_1, word_t param_2, code_t jt0)
{
word_t u0;
  word_t u1;
  word_t u2;
  long *pl0;
  code_t *jt1;
  code_t *ex1;
  code_t *ex0;
  long l1;
  long ux0;
  word_t u3;
  
  sk_h_00407ca0();
  sk_h_0040700c();
  u2 = sk_h_00406db8();
  *(int *)(ux0 + 0xb0) = (int)u2;
  if ((int)u2 == 1) {
    u1 = *(word_t *)(ux0 + 0x78);
    u0 = *(word_t *)(ux0 + 0x60);
    u3 = *(word_t *)(ux0 + 0x48);
    sk_h_00353c00(*(word_t *)(ux0 + 0x70),u2,*(word_t *)(ux0 + 0x68));
    sk_dispatch((code_t)ex1);sk_h_0040bd24(u1);
    sk_h_0040bd24(u0);
    sk_h_0040bd24();
    sk_h_0040bd24(u3);
    sk_h_00406e48();
    sk_h_00407e58();
                    /* WARNING: Could not recover jumptable at 0x003e0498. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x10);
  sk_h_00406bd4(*(word_t *)(ux0 + 0x40),*(word_t *)(ux0 + 0x48));
  sk_dispatch((code_t)ex0);sk_h_004065c8();
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(l1 + 4));
  *(long **)(ux0 + 0xa0) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e05a8;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x48));
                    /* WARNING: Could not recover jumptable at 0x003e0528. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e06a0 @ 0x003e06a0   (est. sk_f_003e06a0 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e06a0(undefined8 param_1,undefined8 param_2,code *jt0)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e06a0(word_t param_1, word_t param_2, code_t jt0)
{
word_t u0;
  word_t u1;
  word_t u2;
  word_t u3;
  word_t u4;
  word_t *p0;
  long ex0;
  code_t *ex1;
  code_t *jt1;
  word_t ex2;
  long ux0;
  
  sk_h_00407ca0();
  u4 = sk_h_0040700c();
  if ((*(byte *)(ux0 + 0xb4) & 1) != 0) {
    u2 = *(word_t *)(ux0 + 0x78);
    u0 = *(word_t *)(ux0 + 0x60);
    u1 = *(word_t *)(ux0 + 0x48);
    u3 = *(word_t *)(ux0 + 0x50);
    sk_h_0040711c(*(word_t *)(ux0 + 0x70),u4,*(word_t *)(ux0 + 0x68));
    sk_dispatch((code_t)ex1);sk_h_0040bd24(u2);
    sk_h_0040bd24(u0);
    sk_h_0040bd24(u3);
    sk_h_0040bd24(u1);
    sk_h_00406e48();
    sk_h_00407e58();
                    /* WARNING: Could not recover jumptable at 0x003e072c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  sk_h_004062a8(*(word_t *)(ux0 + 0x88));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x90) = p0;
  *p0 = ex2;
  sk_h_00406944();
                    /* WARNING: Could not recover jumptable at 0x003e07a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e0848 @ 0x003e0848   (est. sk_f_003e0848 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e0848(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e0848(void)
{
long l0;
  long *pl0;
  long ux0;
  word_t u0;
  word_t u1;
  word_t u2;
  
  sk_h_00407000();
  l0 = sk_h_0040bb18(0x30);
  *(long *)(ux0 + 0x38) = l0;
  u2 = *(word_t *)(ux0 + 0x18);
  u1 = *(word_t *)(ux0 + 0x10);
  u0 = *(word_t *)(ux0 + 0x20);
  *(word_t *)(l0 + 0x18) = *(word_t *)(ux0 + 0x28);
  *(word_t *)(l0 + 0x10) = u0;
  *(word_t *)(l0 + 0x28) = u2;
  *(word_t *)(l0 + 0x20) = u1;
  pl0 = (long *)sk_h_0040bb18(DAT_005a0024);
  *(long **)(ux0 + 0x40) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)sk_f_003e08fc;
  sk_f_003e012c((word_t)(pl0 + 1),(word_t)&DAT_005a0038,l0,*(word_t *)(ux0 + 0x20),
               *(word_t *)(ux0 + 0x28));
  return;
}

/* FUN_003e08fc @ 0x003e08fc   (est. sk_f_003e08fc — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e08fc(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e08fc(void)
{
uint u0;
  code_t *jt0;
  long l0;
  long ux0;
  long *ux1;
  long l1;
  long stack0xffffffffffffffe8;  /* stack slot -0x18 */
  
  u0 = sk_h_00406fd4().lo;;
  l1 = *ux1;
  l0 = *ux1;
  sk_h_0040bd24((word_t)&stack0xffffffffffffffe8 & 0xffffffffffff | 0xc31a000000000000,
               *(word_t *)(l1 + 0x40));
  sk_h_0040bd24(*(word_t *)(l1 + 0x38));
  if (ux0 == 0) {
    jt0 = *(code_t *)(l0 + 8);
    u0 = (u0 ^ 0xffffffff) & 1;
  }
  else {
    jt0 = *(code_t *)(l0 + 8);
    u0 = 0;
  }
                    /* WARNING: Could not recover jumptable at 0x003e09e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0, u0);return;
}

/* FUN_003e09e4 @ 0x003e09e4   (est. sk_f_003e09e4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e09e4(undefined8 param_1,int *param_2)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e09e4(word_t param_1, int *param_2)
{
int i0;
  long *pl0;
  long ux0;
  
  i0 = *param_2;
  pl0 = (long *)sk_h_0040bb18(param_2[1]);
  *(long **)(ux0 + 0x10) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e0aa4;
                    /* WARNING: Could not recover jumptable at 0x003e0aa0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch(*(code_t *)((long)param_2 + (long)i0), pl0 + 1,param_1);
  return;
}

/* FUN_003e0c88 @ 0x003e0c88   (est. sk_f_003e0c88 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e0c88(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e0c88(void)
{
word_t u0;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  code_t *ex2;
  word_t ex3;
  long ux0;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  u0 = sk_h_00407cc4();
  sk_h_00407070(u0,*(word_t *)(ux0 + 0x30));
  sk_dispatch((code_t)ex1);sk_h_004067cc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  sk_h_00350470();
  u0 = sk_h_00377bec();
  *(word_t *)(ux0 + 0x80) = u0;
  u0 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0x88) = u0;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x90) = p0;
  *p0 = ex3;
  sk_h_00406944();
  jt0 = ex2;
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e0d60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e0e30 @ 0x003e0e30   (est. sk_f_003e0e30 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e0e30(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e0e30(void)
{
long l0;
  word_t u0;
  int i0;
  word_t u1;
  code_t *jt0;
  word_t u2;
  word_t *p0;
  code_t *ex2;
  long ex0;
  code_t *ex3;
  code_t *ex1;
  code_t *ex4;
  word_t ex5;
  word_t u4;
  code_t *pc0;
  long ux0;
  word_t u5;
  word_t u6;
  
  sk_h_004079cc();
  sk_h_004070d8();
  u4 = *(word_t *)(ux0 + 0x50);
  pc0 = *(code_t *)(ux0 + 0x38);
  sk_h_00351d24();
  jt0 = pc0;
  u1 = sk_h_000839f8();
  i0 = (int)u1;
  if (i0 != 1) {
    l0 = *(long *)(ux0 + 0x40);
    u1 = *(word_t *)(ux0 + 0x48);
    u4 = *(word_t *)(ux0 + 0x28);
    u6 = *(word_t *)(ux0 + 0x10);
    sk_h_00407ce4();
    sk_h_003510c4();
    sk_dispatch((code_t)ex3);jt0 = (code_t *)sk_h_0014ae44(u4);
    u2 = sk_dispatch((code_t)jt0, u1,u6,pc0,u4);sk_h_00350560(*(word_t *)(l0 + 8));
    u1 = sk_dispatch((code_t)ex2);if ((u2 & 1) == 0) {
      sk_h_004062a8(*(word_t *)(ux0 + 0x88));
      sk_h_0040bb18(*(word_t *)(ex0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x90) = p0;
      *p0 = ex5;
      sk_h_00406944();
      jt0 = ex4;
      sk_h_004078f4();
                    /* WARNING: Could not recover jumptable at 0x003e0fc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      sk_dispatch((code_t)jt0);return;
    }
    u4 = *(word_t *)(ux0 + 0x50);
    jt0 = pc0;
  }
  u0 = *(word_t *)(ux0 + 0x78);
  u6 = *(word_t *)(ux0 + 0x60);
  u5 = *(word_t *)(ux0 + 0x48);
  sk_h_00407f48(*(word_t *)(ux0 + 0x70),u1,*(word_t *)(ux0 + 0x68));
  sk_dispatch((code_t)ex1);sk_h_0040bd24(u0);
  sk_h_0040bd24(u6);
  sk_h_0040bd24(u4);
  sk_h_0040bd24(u5);
  sk_h_004078b4();
  sk_h_004078f4(i0 != 1);
                    /* WARNING: Could not recover jumptable at 0x003e0f4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e117c @ 0x003e117c   (est. sk_f_003e117c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e117c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e117c(void)
{
word_t u0;
  word_t u1;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  word_t ex2;
  long ux0;
  sk16_t a0;
  
  sk_h_00407c8c();
  u0 = sk_h_0040700c();
  u1 = *(word_t *)(ux0 + 0x70);
  sk_h_00407070(*(word_t *)(ux0 + 0x60),u0,*(word_t *)(ux0 + 0x18));
  sk_dispatch((code_t)ex1);sk_h_004067cc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  a0 = sk_h_00350470();
  u1 = sk_h_00377bec(a0.lo,a0.hi,u1);
  *(word_t *)(ux0 + 0x88) = u1;
  u1 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0x90) = u1;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x98) = p0;
  *p0 = ex2;
  sk_h_00406e18();
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e1258. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e1330 @ 0x003e1330   (est. sk_f_003e1330 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e1330(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e1330(void)
{
word_t u0;
  word_t u1;
  byte zf;
  word_t u2;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  long ex1;
  word_t ex2;
  code_t *ex0;
  word_t ex3;
  word_t u3;
  long l1;
  long ux0;
  sk16_t a0;
  
  u2 = sk_h_00407ca0();
  sk_h_0040700c();
  u3 = *(word_t *)(ux0 + 0x40);
  sk_h_00406420();
  if ((bool)zf) {
    sk_h_00408348();
    sk_dispatch(*(code_t *)(ex1 + 8));sk_h_00407aac();
    u0 = *(word_t *)(ux0 + 0x50);
    u1 = *(word_t *)(ux0 + 0x58);
    sk_h_0040686c();
    sk_h_0040bd24(u3);
    sk_h_0040bd24(u1);
    sk_h_0040bd24(u0);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u2);
                    /* WARNING: Could not recover jumptable at 0x003e13c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x20);
  sk_h_00406894(*(word_t *)(ux0 + 0x48),*(word_t *)(ux0 + 0x50));
  *(word_t *)(ux0 + 0xa8) = ex2;
  *(word_t *)(ux0 + 0xb0) = ex3;
  sk_h_00350624();
  sk_dispatch((code_t)ex0);sk_h_004065c8();
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(l1 + 4));
  *(long **)(ux0 + 0xb8) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e1460;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x50));
                    /* WARNING: Could not recover jumptable at 0x003e145c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e1550 @ 0x003e1550   (est. sk_f_003e1550 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e1550(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e1550(void)
{
code_t *pc0;
  word_t u0;
  word_t u1;
  word_t u2;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  long ex1;
  long ex0;
  word_t ex2;
  long ux0;
  sk16_t a0;
  
  u2 = sk_h_00407c8c();
  sk_h_0040700c();
  if (*(char *)(ux0 + 200) == '\x01') {
    pc0 = *(code_t *)(ux0 + 0xa8);
    sk_h_00408348();
    sk_h_00407954();
    sk_dispatch(*(code_t *)(ex1 + 8));sk_h_0011aa70();
    sk_dispatch((code_t)pc0);sk_h_00407aac();
    u0 = *(word_t *)(ux0 + 0x50);
    u1 = *(word_t *)(ux0 + 0x58);
    sk_h_00406cf0();
    sk_h_0040bd24();
    sk_h_0040bd24(u1);
    sk_h_0040bd24(u0);
    a0 = sk_h_0040678c();
    sk_h_00407c78(a0.lo,a0.hi,u2);
                    /* WARNING: Could not recover jumptable at 0x003e15f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x48) + 8), *(word_t *)(ux0 + 0x50),*(word_t *)(ux0 + 0x40));sk_h_004062a8(*(word_t *)(ux0 + 0x90));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x98) = p0;
  *p0 = ex2;
  sk_h_00406e18();
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e167c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e17b4 @ 0x003e17b4   (est. sk_f_003e17b4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e17b4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e17b4(void)
{
word_t u0;
  word_t u1;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  word_t ex2;
  long ux0;
  sk16_t a0;
  
  sk_h_00407c8c();
  u0 = sk_h_0040700c();
  u1 = *(word_t *)(ux0 + 0x70);
  sk_h_00407070(*(word_t *)(ux0 + 0x60),u0,*(word_t *)(ux0 + 0x38));
  sk_dispatch((code_t)ex1);sk_h_004067cc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  a0 = sk_h_00350470();
  u1 = sk_h_00377bec(a0.lo,a0.hi,u1);
  *(word_t *)(ux0 + 0x88) = u1;
  u1 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0x90) = u1;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x98) = p0;
  *p0 = ex2;
  sk_h_00406e18();
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e1890. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e1968 @ 0x003e1968   (est. sk_f_003e1968 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e1968(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e1968(void)
{
word_t u0;
  word_t u1;
  byte zf;
  word_t u2;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  long ex1;
  word_t ex2;
  code_t *ex0;
  word_t ex3;
  word_t u3;
  long l1;
  long ux0;
  sk16_t a0;
  
  u2 = sk_h_00407ca0();
  sk_h_0040700c();
  u3 = *(word_t *)(ux0 + 0x40);
  sk_h_00406420();
  if ((bool)zf) {
    sk_h_00408348();
    sk_dispatch(*(code_t *)(ex1 + 8));sk_h_00407aac();
    u0 = *(word_t *)(ux0 + 0x50);
    u1 = *(word_t *)(ux0 + 0x58);
    sk_h_0040686c();
    sk_h_0040bd24(u3);
    sk_h_0040bd24(u1);
    sk_h_0040bd24(u0);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u2);
                    /* WARNING: Could not recover jumptable at 0x003e19fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x18);
  sk_h_00406894(*(word_t *)(ux0 + 0x48),*(word_t *)(ux0 + 0x50));
  *(word_t *)(ux0 + 0xa8) = ex2;
  *(word_t *)(ux0 + 0xb0) = ex3;
  sk_h_00350624();
  sk_dispatch((code_t)ex0);sk_h_004065c8();
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(l1 + 4));
  *(long **)(ux0 + 0xb8) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e1b10;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x50));
                    /* WARNING: Could not recover jumptable at 0x003e1a94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e1c00 @ 0x003e1c00   (est. sk_f_003e1c00 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e1c00(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e1c00(void)
{
code_t *pc0;
  word_t u0;
  word_t u1;
  word_t u2;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  long ex1;
  long ex0;
  word_t ex2;
  long ux0;
  sk16_t a0;
  
  u2 = sk_h_00407c8c();
  sk_h_0040700c();
  if (*(char *)(ux0 + 200) == '\x01') {
    pc0 = *(code_t *)(ux0 + 0xa8);
    sk_h_00408348();
    sk_h_00407954();
    sk_dispatch(*(code_t *)(ex1 + 8));sk_h_0011aa70();
    sk_dispatch((code_t)pc0);sk_h_00407aac();
    u0 = *(word_t *)(ux0 + 0x50);
    u1 = *(word_t *)(ux0 + 0x58);
    sk_h_00406cf0();
    sk_h_0040bd24();
    sk_h_0040bd24(u1);
    sk_h_0040bd24(u0);
    a0 = sk_h_0040678c();
    sk_h_00407c78(a0.lo,a0.hi,u2);
                    /* WARNING: Could not recover jumptable at 0x003e1ca4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x48) + 8), *(word_t *)(ux0 + 0x50),*(word_t *)(ux0 + 0x40));sk_h_004062a8(*(word_t *)(ux0 + 0x90));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x98) = p0;
  *p0 = ex2;
  sk_h_00406e18();
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e1d2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e1da8 @ 0x003e1da8   (est. sk_f_003e1da8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e1da8(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e1da8(word_t param_1, word_t param_2, long param_3)
{
word_t u0;
  word_t u1;
  word_t in_x4;
  long ex6;
  long ex0;
  long ex1;
  long ex2;
  word_t ex7;
  word_t ex3;
  word_t ex4;
  word_t ex5;
  word_t ux0;
  long ux1;
  word_t ux2;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  *(word_t *)(ux1 + 0x30) = in_x4;
  *(word_t *)(ux1 + 0x38) = ux0;
  sk_h_00406c80();
  u0 = sk_h_00408538();
  *(word_t *)(ux1 + 0x40) = u0;
  sk_h_00350798();
  u1 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x48) = u1;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x50) = ex7;
  u1 = sk_h_004081b4(*(word_t *)(ex6 + 0x40));
  *(word_t *)(ux1 + 0x58) = u1;
  u1 = sk_h_0040bb18(ux2 & 0xfffffffffffffff0);
  *(word_t *)(ux1 + 0x60) = u1;
  sk_h_0040683c();
  *(word_t *)(ux1 + 0x68) = ex3;
  u1 = sk_h_00407b48(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux1 + 0x70) = u1;
  u1 = sk_h_0040bb18(u0 & 0xfffffffffffffff0);
  *(word_t *)(ux1 + 0x78) = u1;
  sk_h_0007c028();
  *(word_t *)(ux1 + 0x80) = ex4;
  u1 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux1 + 0x88) = u1;
  sk_h_00407090();
  sk_h_00351584();
  u1 = sk_h_00377824().lo;;
  *(word_t *)(ux1 + 0x90) = u1;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x98) = ex5;
  u1 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux1 + 0xa0) = u1;
  sk_h_00407594();
  sk_h_00407c78();
  sk_h_00408db8();
  return;
}

/* FUN_003e1f00 @ 0x003e1f00   (est. sk_f_003e1f00 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e1f00(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e1f00(void)
{
word_t u0;
  word_t u1;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  word_t ex2;
  long ux0;
  sk16_t a0;
  
  sk_h_00407c8c();
  u0 = sk_h_0040700c();
  u1 = *(word_t *)(ux0 + 0x90);
  sk_h_00407070(*(word_t *)(ux0 + 0x80),u0,*(word_t *)(ux0 + 0x38));
  sk_dispatch((code_t)ex1);sk_h_004067cc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  a0 = sk_h_00350470();
  sk_h_00377bec(a0.lo,a0.hi,u1);
  sk_h_004083cc();
  u1 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0xb0) = u1;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xb8) = p0;
  *p0 = ex2;
  p0[1] = (word_t)&sk_lab_003e1ff0;
  sk_h_00407814(*(word_t *)(ux0 + 0x60),*(word_t *)(ux0 + 0x90));
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e1fec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e20c4 @ 0x003e20c4   (est. sk_f_003e20c4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e20c4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e20c4(void)
{
byte zf;
  word_t u0;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  code_t *ex3;
  long ex0;
  code_t *ex4;
  word_t ex1;
  code_t *ex2;
  word_t ex5;
  code_t *ex6;
  word_t ex7;
  word_t u2;
  long ux0;
  long ux1;
  sk16_t a0;
  
  u0 = sk_h_0040790c();
  sk_h_004070d8();
  u2 = *(word_t *)(ux1 + 0x40);
  sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040826c();
    sk_dispatch((code_t)ex4);sk_h_0007c1c4(*(word_t *)(ux0 + 8));
    sk_dispatch((code_t)ex3);sk_h_00407080();
    sk_h_0040686c();
    sk_h_0040bd24(u2);
    sk_h_0040bd24((word_t *)(ux0 + 8));
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_004079b4(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e2178. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  sk_h_00406894(*(word_t *)(ux1 + 0x68),*(word_t *)(ux1 + 0x78));
  *(word_t *)(ux1 + 200) = ex1;
  *(word_t *)(ux1 + 0xd0) = ex5;
  sk_h_00350624();
  sk_dispatch((code_t)ex2);sk_h_004062a8(*(word_t *)(ux1 + 0xb0));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux1 + 0xd8) = p0;
  *p0 = ex7;
  sk_h_00406f84();
  jt1 = ex6;
  sk_h_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003e220c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e22f8 @ 0x003e22f8   (est. sk_f_003e22f8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e22f8(undefined8 param_1,undefined8 param_2,code *jt1)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e22f8(word_t param_1, word_t param_2, code_t jt1)
{
byte zf;
  long *pl0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex2;
  code_t *ex0;
  word_t u0;
  long l1;
  long ux0;
  code_t *ux1;
  long ux2;
  
  sk_h_004084a4();
  sk_h_00407924();
  u0 = *(word_t *)(ux0 + 0x58);
  sk_h_00406be4();
  if ((bool)zf) {
    sk_h_00407a60();
    sk_dispatch((code_t)ex2);sk_h_00084174(*(word_t *)(ux2 + 8));
    sk_dispatch((code_t)ex1);sk_h_00350548();
    sk_dispatch((code_t)ux1);sk_h_00407080();
    sk_h_00406cf0();
    sk_h_0040bd24(u0);
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003e23c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x18);
  sk_h_00350968(*(word_t *)(ux0 + 0xd0),*(word_t *)(ux0 + 0x70));
  sk_dispatch((code_t)ex0);sk_h_00407260();
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(l1 + 4));
  *(long **)(ux0 + 0xe8) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e2458;
  sk_h_00408360(*(word_t *)(ux0 + 0x70),pl0,*(word_t *)(ux0 + 0x78));
                    /* WARNING: Could not recover jumptable at 0x003e2454. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e2558 @ 0x003e2558   (est. sk_f_003e2558 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e2558(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e2558(void)
{
word_t *p0;
  code_t *jt0;
  long ex1;
  code_t *ex2;
  code_t *ex0;
  uint ex3;
  code_t *ex4;
  word_t ex5;
  word_t u1;
  long ux0;
  sk16_t a0;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  sk_h_00408244();
  if ((ex3 & 1) == 0) {
    sk_dispatch((code_t)ex2, *(word_t *)(ux0 + 0x70),*(word_t *)(ux0 + 0x40));}
  else {
    jt0 = *(code_t *)(ux0 + 200);
    u1 = *(word_t *)(ux0 + 0x40);
    sk_h_0006b6f4();
    sk_dispatch((code_t)ex0);a0 = sk_h_0007c1c4();
    sk_dispatch((code_t)jt0, a0.lo,a0.hi,u1);}
  sk_h_004062a8(*(word_t *)(ux0 + 0xb0));
  sk_h_0040bb18(*(word_t *)(ex1 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xd8) = p0;
  *p0 = ex5;
  sk_h_00406f84();
  jt0 = ex4;
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e2628. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e262c @ 0x003e262c   (est. sk_f_003e262c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e262c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e262c(word_t param_1, word_t param_2, long param_3)
{
word_t u0;
  word_t u1;
  word_t in_x4;
  long ex6;
  long ex0;
  long ex1;
  long ex2;
  word_t ex7;
  word_t ex3;
  word_t ex4;
  word_t ex5;
  word_t ux0;
  long ux1;
  word_t ux2;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  *(word_t *)(ux1 + 0x30) = in_x4;
  *(word_t *)(ux1 + 0x38) = ux0;
  sk_h_00406c80();
  u0 = sk_h_00408538();
  *(word_t *)(ux1 + 0x40) = u0;
  sk_h_00350798();
  u1 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x48) = u1;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x50) = ex7;
  u1 = sk_h_004081b4(*(word_t *)(ex6 + 0x40));
  *(word_t *)(ux1 + 0x58) = u1;
  u1 = sk_h_0040bb18(ux2 & 0xfffffffffffffff0);
  *(word_t *)(ux1 + 0x60) = u1;
  sk_h_0040683c();
  *(word_t *)(ux1 + 0x68) = ex3;
  u1 = sk_h_00407b48(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux1 + 0x70) = u1;
  u1 = sk_h_0040bb18(u0 & 0xfffffffffffffff0);
  *(word_t *)(ux1 + 0x78) = u1;
  sk_h_0007c028();
  *(word_t *)(ux1 + 0x80) = ex4;
  u1 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux1 + 0x88) = u1;
  sk_h_00407090();
  sk_h_00351584();
  u1 = sk_h_00377824().lo;;
  *(word_t *)(ux1 + 0x90) = u1;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x98) = ex5;
  u1 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux1 + 0xa0) = u1;
  sk_h_00407594();
  sk_h_00407c78();
  sk_h_00408db8();
  return;
}

/* FUN_003e2784 @ 0x003e2784   (est. sk_f_003e2784 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e2784(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e2784(void)
{
word_t u0;
  word_t u1;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  word_t ex2;
  long ux0;
  sk16_t a0;
  
  sk_h_00407c8c();
  u0 = sk_h_0040700c();
  u1 = *(word_t *)(ux0 + 0x90);
  sk_h_00407070(*(word_t *)(ux0 + 0x80),u0,*(word_t *)(ux0 + 0x38));
  sk_dispatch((code_t)ex1);sk_h_004067cc();
  sk_dispatch((code_t)ex0);sk_h_004068bc();
  a0 = sk_h_00350470();
  sk_h_00377bec(a0.lo,a0.hi,u1);
  sk_h_004083cc();
  u1 = sk_h_003fcc1c();
  *(word_t *)(ux0 + 0xb0) = u1;
  l0 = sk_h_004062c8();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xb8) = p0;
  *p0 = ex2;
  p0[1] = (word_t)&sk_lab_003e2874;
  sk_h_00407814(*(word_t *)(ux0 + 0x60),*(word_t *)(ux0 + 0x90));
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e2870. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e2948 @ 0x003e2948   (est. sk_f_003e2948 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e2948(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e2948(void)
{
byte zf;
  word_t u0;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  code_t *ex3;
  long ex0;
  code_t *ex4;
  word_t ex1;
  code_t *ex2;
  word_t ex5;
  code_t *ex6;
  word_t ex7;
  word_t u2;
  long ux0;
  long ux1;
  sk16_t a0;
  
  u0 = sk_h_0040790c();
  sk_h_004070d8();
  u2 = *(word_t *)(ux1 + 0x40);
  sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040826c();
    sk_dispatch((code_t)ex4);sk_h_0007c1c4(*(word_t *)(ux0 + 8));
    sk_dispatch((code_t)ex3);sk_h_00407080();
    sk_h_0040686c();
    sk_h_0040bd24(u2);
    sk_h_0040bd24((word_t *)(ux0 + 8));
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_004079b4(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e29fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  sk_h_00406894(*(word_t *)(ux1 + 0x68),*(word_t *)(ux1 + 0x78));
  *(word_t *)(ux1 + 200) = ex1;
  *(word_t *)(ux1 + 0xd0) = ex5;
  sk_h_00350624();
  sk_dispatch((code_t)ex2);sk_h_004062a8(*(word_t *)(ux1 + 0xb0));
  sk_h_0040bb18(*(word_t *)(ex0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux1 + 0xd8) = p0;
  *p0 = ex7;
  sk_h_00406f84();
  jt1 = ex6;
  sk_h_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003e2a90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e2b7c @ 0x003e2b7c   (est. sk_f_003e2b7c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e2b7c(undefined8 param_1,undefined8 param_2,code *jt1)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e2b7c(word_t param_1, word_t param_2, code_t jt1)
{
byte zf;
  long *pl0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex2;
  code_t *ex0;
  word_t u0;
  long l1;
  long ux0;
  code_t *ux1;
  long ux2;
  
  sk_h_004084a4();
  sk_h_00407924();
  u0 = *(word_t *)(ux0 + 0x58);
  sk_h_00406be4();
  if ((bool)zf) {
    sk_h_00407a60();
    sk_dispatch((code_t)ex2);sk_h_00084174(*(word_t *)(ux2 + 8));
    sk_dispatch((code_t)ex1);sk_h_00350548();
    sk_dispatch((code_t)ux1);sk_h_00407080();
    sk_h_00406cf0();
    sk_h_0040bd24(u0);
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040678c();
                    /* WARNING: Could not recover jumptable at 0x003e2c48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x18);
  sk_h_00350968(*(word_t *)(ux0 + 0xd0),*(word_t *)(ux0 + 0x70));
  sk_dispatch((code_t)ex0);sk_h_00407260();
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(l1 + 4));
  *(long **)(ux0 + 0xe8) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e2cdc;
  sk_h_00408360(*(word_t *)(ux0 + 0x78),pl0,*(word_t *)(ux0 + 0x70));
                    /* WARNING: Could not recover jumptable at 0x003e2cd8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e2ddc @ 0x003e2ddc   (est. sk_f_003e2ddc — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e2ddc(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e2ddc(void)
{
word_t *p0;
  code_t *jt0;
  long ex1;
  code_t *ex2;
  code_t *ex0;
  uint ex3;
  code_t *ex4;
  word_t ex5;
  word_t u1;
  long ux0;
  sk16_t a0;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  sk_h_00408244();
  if ((ex3 & 1) == 0) {
    sk_dispatch((code_t)ex2, *(word_t *)(ux0 + 0x70),*(word_t *)(ux0 + 0x40));}
  else {
    jt0 = *(code_t *)(ux0 + 200);
    u1 = *(word_t *)(ux0 + 0x40);
    sk_h_0006b6f4();
    sk_dispatch((code_t)ex0);a0 = sk_h_0007c1c4();
    sk_dispatch((code_t)jt0, a0.lo,a0.hi,u1);}
  sk_h_004062a8(*(word_t *)(ux0 + 0xb0));
  sk_h_0040bb18(*(word_t *)(ex1 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xd8) = p0;
  *p0 = ex5;
  sk_h_00406f84();
  jt0 = ex4;
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e2eac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e3064 @ 0x003e3064   (est. sk_f_003e3064 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e3064(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e3064(void)
{
long l0;
  word_t *p0;
  word_t u1;
  word_t ex0;
  word_t ux0;
  long ux1;
  
  sk_h_004070d8();
  sk_h_0036a940(0x67d768,0x30,7);
  l0 = sk_h_00407c3c();
  *(long *)(ux1 + 0x40) = l0;
  sk_h_00406ce0(l0,*(word_t *)(ux1 + 0x20));
  sk_h_00377824(0);
  sk_h_00408224();
  *(word_t **)(l0 + 0x28) = &DAT_00405fac;
  *(word_t *)(l0 + 0x30) = ux0;
  sk_h_0040bb18(DAT_005a005c);
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux1 + 0x48) = p0;
  *p0 = ex0;
  u1 = sk_h_004083a0();
  sk_f_003e1da8(u1,(word_t)&DAT_005a0078,l0);
  return;
}

/* FUN_003e3160 @ 0x003e3160   (est. sk_f_003e3160 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e3160(undefined8 param_1,undefined8 param_2,code *param_3)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e3160(word_t param_1, word_t param_2, code_t param_3)
{
uint u0;
  long ux0;
  
  u0 = sk_dispatch((code_t)param_3);/* WARNING: Could not recover jumptable at 0x003e31bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch(*(code_t *)(ux0 + 8), u0 & 1);return;
}

/* FUN_003e31e8 @ 0x003e31e8   (est. sk_f_003e31e8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e31e8(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e31e8(void)
{
long l0;
  word_t *p0;
  word_t u1;
  word_t ex0;
  word_t ux0;
  long ux1;
  
  sk_h_004070d8();
  sk_h_0036a940(0x67d790,0x30,7);
  l0 = sk_h_00407c3c();
  *(long *)(ux1 + 0x40) = l0;
  sk_h_00406ce0(l0,*(word_t *)(ux1 + 0x20));
  sk_h_00377824(0);
  sk_h_00408224();
  *(word_t **)(l0 + 0x28) = &DAT_003fcf24;
  *(word_t *)(l0 + 0x30) = ux0;
  sk_h_0040bb18(DAT_005a0064);
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux1 + 0x48) = p0;
  *p0 = ex0;
  u1 = sk_h_004083a0();
  sk_f_003e262c(u1,(word_t)&DAT_005a0088,l0);
  return;
}

/* FUN_003e32e4 @ 0x003e32e4   (est. sk_f_003e32e4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e32e4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e32e4(void)
{
long ex0;
  word_t u0;
  long *ux0;
  word_t u1;
  long l0;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  sk_h_00407018();
  u0 = *(word_t *)(ex0 + 0x40);
  u1 = *(word_t *)(ex0 + 0x38);
  l0 = *ux0;
  sk_h_0040bd24(*(word_t *)(ex0 + 0x48));
  sk_h_0036b118(u1);
  sk_h_0040bd24(u0);
                    /* WARNING: Could not recover jumptable at 0x003e33d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch(*(code_t *)(l0 + 8));return;
}

/* FUN_003e33d8 @ 0x003e33d8   (est. sk_f_003e33d8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e33d8(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e33d8(void)
{
uint u0;
  code_t *pc0;
  word_t in_x5;
  word_t ux0;
  sk16_t a0;
  
  sk_h_00084220();
  sk_h_00406e34();
  pc0 = (code_t *)sk_h_0016186c(in_x5);
  sk_h_00350798();
  a0 = sk_h_00377824();
  sk_h_00350518(a0.lo,a0.hi,a0.lo);
  u0 = sk_dispatch((code_t)pc0);sk_h_00084234(u0 & 1,ux0);
  return;
}

/* FUN_003e3454 @ 0x003e3454   (est. sk_f_003e3454 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e3454(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e3454(void)
{
sk_h_00406574();
  sk_f_003e3484();
  sk_h_0036b270();
  return;
}

/* FUN_003e3484 @ 0x003e3484   (est. sk_f_003e3484 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e3484(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e3484(void)
{
sk_h_003e9df8();
  return;
}

/* FUN_003e34b4 @ 0x003e34b4   (est. sk_f_003e34b4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e34b4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e34b4(void)
{
word_t u0;
  long ex6;
  long ex7;
  long ex0;
  long ex1;
  long ex2;
  word_t ex8;
  word_t ex3;
  word_t ex4;
  word_t ex5;
  long ux0;
  
  sk_h_00407000();
  sk_h_00407214();
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0x30) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x38) = ex8;
  u0 = sk_h_004078e8(*(word_t *)(ex7 + 0x40));
  *(word_t *)(ux0 + 0x40) = u0;
  sk_h_0040683c();
  *(word_t *)(ux0 + 0x48) = ex3;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux0 + 0x50) = u0;
  *(word_t *)(ux0 + 0x58) = *(word_t *)(ex6 + 0x20);
  *(word_t *)(ux0 + 0x60) = *(word_t *)(ex6 + 0x10);
  sk_h_004069c4();
  sk_h_00377824();
  sk_h_00408454();
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0x70) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x78) = ex4;
  u0 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux0 + 0x80) = u0;
  sk_h_0040683c();
  *(word_t *)(ux0 + 0x88) = ex5;
  u0 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux0 + 0x90) = u0;
  sk_h_00407594();
  sk_h_00408db8();
  return;
}

/* FUN_003e35ec @ 0x003e35ec   (est. sk_f_003e35ec — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e35ec(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e35ec(void)
{
long l0;
  byte b0;
  int i0;
  word_t u0;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  word_t ex0;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  *(long *)(ux0 + 0x98) = ux0;
  i0 = *(int *)(*(long *)(ux0 + 0x18) + 0x30);
  *(int *)(ux0 + 0xc0) = i0;
  b0 = *(byte *)(*(long *)(ux0 + 0x20) + (long)i0);
  *(byte *)(ux0 + 0xc4) = b0;
  if ((b0 & 1) != 0) {
    sk_h_00407774();
    sk_h_0040686c();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e3678. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x60);
  sk_h_0040652c();
  sk_h_00406608();
  sk_h_004068f4();
  sk_h_00406268();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xa0) = p0;
  *p0 = ex0;
  p0[1] = (word_t)&sk_lab_003e370c;
  sk_h_00406ab4(*(word_t *)(ux0 + 0x80));
                    /* WARNING: Could not recover jumptable at 0x003e3708. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e37c8 @ 0x003e37c8   (est. sk_f_003e37c8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e37c8(undefined8 param_1,undefined8 param_2,code *jt1)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e37c8(word_t param_1, word_t param_2, code_t jt1)
{
long l0;
  int i0;
  byte zf;
  word_t u0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  long ex1;
  code_t *ex2;
  code_t *ex0;
  word_t ex3;
  long ux0;
  long l1;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  sk_h_00407aac();
  u1 = sk_h_00406420();
  if ((bool)zf) {
    i0 = *(int *)(ux0 + 0xc0);
    l1 = *(long *)(ux0 + 0x20);
    sk_h_0040711c(*(word_t *)(ux0 + 0x78),u1,*(word_t *)(ux0 + 0x70));
    sk_dispatch((code_t)ex2);*(byte *)(l1 + i0) = 1;
    sk_h_00407774();
    sk_h_0040686c();
    sk_h_0040bd24((long)i0);
    sk_h_0040bd24(1);
    sk_h_0040bd24(l1);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e3868. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x18);
  l0 = *(long *)(ux0 + 0x20);
  sk_h_00406bd4(*(word_t *)(ux0 + 0x88),*(word_t *)(ux0 + 0x90));
  sk_dispatch((code_t)ex0);sk_h_004062a8(*(word_t *)(l0 + *(int *)(l1 + 0x2c)));
  sk_h_0040bb18(*(word_t *)(ex1 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xb0) = p0;
  *p0 = ex3;
  p0[1] = (word_t)&sk_lab_003e3908;
  sk_h_00407824(*(word_t *)(ux0 + 0x40),*(word_t *)(ux0 + 0x90));
                    /* WARNING: Could not recover jumptable at 0x003e3904. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e3a14 @ 0x003e3a14   (est. sk_f_003e3a14 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e3a14(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e3a14(void)
{
long l0;
  byte zf;
  word_t u0;
  word_t u1;
  word_t *p0;
  word_t ex0;
  code_t *jt0;
  code_t *jt1;
  code_t *ex1;
  code_t *ex2;
  word_t ex3;
  word_t u3;
  long ux0;
  word_t u4;
  word_t u5;
  code_t *ux1;
  sk16_t a0;
  
  u0 = sk_h_0040790c();
  sk_h_004070d8();
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x38),u1,*(word_t *)(ux0 + 0x30));
    sk_dispatch((code_t)ex1);if ((*(byte *)(ux0 + 0xc4) & 1) == 0) {
      l0 = *(long *)(ux0 + 0x60);
      sk_h_0040652c();
      sk_h_00406608();
      sk_h_004068f4();
      sk_h_00406268();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0xa0) = p0;
      *p0 = ex3;
      p0[1] = (word_t)&sk_lab_003e370c;
      sk_h_00406ab4(*(word_t *)(ux0 + 0x80));
      jt1 = ex2;
      sk_h_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003e3b88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      sk_dispatch((code_t)jt1);return;
    }
    u1 = 1;
  }
  else {
    sk_h_00407aa0();
    sk_h_0011aa70();
    sk_dispatch((code_t)ux1);sk_h_003504a0();
    sk_dispatch((code_t)ux1);sk_h_00407bf8();
    u1 = ex0;
  }
  u3 = *(word_t *)(ux0 + 0x80);
  u4 = *(word_t *)(ux0 + 0x50);
  u5 = *(word_t *)(ux0 + 0x40);
  sk_h_004075a4(*(word_t *)(ux0 + 0x10),u1);
  sk_h_0040bd24(u3);
  sk_h_0040bd24(u4);
  sk_h_0040bd24(u5);
  a0 = sk_h_00406e64();
  sk_h_004079b4(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e3af8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e3c80 @ 0x003e3c80   (est. sk_f_003e3c80 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e3c80(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e3c80(word_t param_1, word_t param_2, word_t param_3, long param_4, long param_5)
{
word_t u0;
  long ex11;
  long ex0;
  long ex1;
  long ex2;
  long ex3;
  code_t *ex4;
  word_t ex5;
  word_t ex6;
  word_t ex12;
  word_t ex7;
  word_t ex8;
  word_t ex9;
  word_t ex10;
  long ux0;
  long ux1;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  sk_h_00406c1c();
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x40) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x48) = ex12;
  u0 = sk_h_004078e8(*(word_t *)(ex11 + 0x40));
  *(word_t *)(ux1 + 0x50) = u0;
  sk_h_0040683c();
  *(word_t *)(ux1 + 0x58) = ex7;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux1 + 0x60) = u0;
  *(word_t *)(ux1 + 0x68) = *(word_t *)(param_4 + 0x20);
  *(word_t *)(ux1 + 0x70) = *(word_t *)(param_4 + 0x10);
  u0 = sk_h_0040684c();
  *(word_t *)(ux1 + 0x78) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x80) = ex8;
  u0 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux1 + 0x88) = u0;
  u0 = sk_h_00406dd0();
  *(word_t *)(ux1 + 0x90) = u0;
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x98) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0xa0) = ex9;
  u0 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux1 + 0xa8) = u0;
  sk_h_0040683c();
  *(word_t *)(ux1 + 0xb0) = ex10;
  u0 = sk_h_004078e8(*(word_t *)(ex3 + 0x40));
  *(word_t *)(ux1 + 0xb8) = u0;
  if (ux0 == 0) {
    sk_h_00407248();
    u0 = ex6;
  }
  else {
    sk_h_00406590();
    sk_dispatch((code_t)ex4);sk_h_0008e1ec();
    u0 = ex5;
  }
  *(word_t *)(ux1 + 0xc0) = u0;
  *(word_t *)(ux1 + 200) = param_3;
  sk_h_00353080();
  sk_h_00407c78();
  sk_h_00408db8();
  return;
}

/* FUN_003e3e28 @ 0x003e3e28   (est. sk_f_003e3e28 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e3e28(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e3e28(void)
{
long l0;
  byte b0;
  int i0;
  word_t u0;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  word_t ex0;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407c8c();
  sk_h_0040700c();
  *(long *)(ux0 + 0xd0) = ux0;
  i0 = *(int *)(*(long *)(ux0 + 0x28) + 0x30);
  *(int *)(ux0 + 0x100) = i0;
  b0 = *(byte *)(*(long *)(ux0 + 0x30) + (long)i0);
  *(byte *)(ux0 + 0x104) = b0;
  if ((b0 & 1) != 0) {
    sk_h_004076c4();
    sk_h_0040686c();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_00407c78(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e3ebc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x70);
  sk_h_0040652c();
  u0 = sk_h_00406608();
  *(word_t *)(ux0 + 0xd8) = u0;
  u0 = sk_h_00406e8c();
  *(word_t *)(ux0 + 0xe0) = u0;
  sk_h_00406288();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xe8) = p0;
  *p0 = ex0;
  p0[1] = (word_t)&sk_lab_003e3f5c;
  sk_h_004067b8(*(word_t *)(ux0 + 0xa8));
  sk_h_00407990();
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e3f58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e4048 @ 0x003e4048   (est. sk_f_003e4048 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e4048(undefined8 param_1,undefined8 param_2,code *jt1)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e4048(word_t param_1, word_t param_2, code_t jt1)
{
long l0;
  int i0;
  byte zf;
  word_t u0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  long ex1;
  code_t *ex2;
  code_t *ex0;
  word_t ex3;
  long ux0;
  long l1;
  sk16_t a0;
  
  u0 = sk_h_00407c8c();
  sk_h_0040700c();
  u1 = sk_h_00406420();
  if ((bool)zf) {
    i0 = *(int *)(ux0 + 0x100);
    l1 = *(long *)(ux0 + 0x30);
    sk_h_0040711c(*(word_t *)(ux0 + 0xa0),u1,*(word_t *)(ux0 + 0x98));
    sk_dispatch((code_t)ex2);*(byte *)(l1 + i0) = 1;
    sk_h_004076c4();
    sk_h_0040686c();
    sk_h_0040bd24((long)i0);
    sk_h_0040bd24(1);
    sk_h_0040bd24(l1);
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_00407c78(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e40f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l1 = *(long *)(ux0 + 0x28);
  l0 = *(long *)(ux0 + 0x30);
  sk_h_00406bd4(*(word_t *)(ux0 + 0xb0),*(word_t *)(ux0 + 0xb8));
  sk_dispatch((code_t)ex0);sk_h_004062a8(*(word_t *)(l0 + *(int *)(l1 + 0x2c)));
  sk_h_0040bb18(*(word_t *)(ex1 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xf0) = p0;
  *p0 = ex3;
  p0[1] = (word_t)&sk_lab_003e4194;
  sk_h_00408380(*(word_t *)(ux0 + 0x50),*(word_t *)(ux0 + 0xb8));
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e4190. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e42c4 @ 0x003e42c4   (est. sk_f_003e42c4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e42c4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e42c4(void)
{
long l0;
  byte zf;
  word_t u0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  code_t *ex0;
  code_t *ex1;
  word_t ex2;
  long ux0;
  word_t u3;
  word_t u4;
  code_t *ux1;
  word_t u5;
  sk16_t a0;
  
  u0 = sk_h_0040790c();
  sk_h_004070d8();
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x48),u1,*(word_t *)(ux0 + 0x40));
    u1 = sk_dispatch((code_t)ex0);if ((*(byte *)(ux0 + 0x104) & 1) == 0) {
      l0 = *(long *)(ux0 + 0x70);
      sk_h_0040652c();
      u0 = sk_h_00406608();
      *(word_t *)(ux0 + 0xd8) = u0;
      u0 = sk_h_00406e8c();
      *(word_t *)(ux0 + 0xe0) = u0;
      sk_h_00406288();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0xe8) = p0;
      *p0 = ex2;
      p0[1] = (word_t)&sk_lab_003e3f5c;
      sk_h_004067b8(*(word_t *)(ux0 + 0xa8));
      jt1 = ex1;
      sk_h_004080cc();
                    /* WARNING: Could not recover jumptable at 0x003e4450. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      sk_dispatch((code_t)jt1);return;
    }
    a0.hi = 1;
    a0.lo = u1;
  }
  else {
    sk_h_00407aa0();
    sk_h_0011aa70();
    sk_dispatch((code_t)ux1);sk_h_003504a0();
    sk_dispatch((code_t)ux1);a0 = sk_h_00407bf8();
  }
  u1 = *(word_t *)(ux0 + 0xa8);
  u3 = *(word_t *)(ux0 + 0x88);
  u4 = *(word_t *)(ux0 + 0x60);
  u5 = *(word_t *)(ux0 + 0x50);
  sk_h_0040738c(a0.lo,a0.hi);
  sk_h_004075a4();
  sk_h_0040bd24(u1);
  sk_h_0040bd24(u3);
  sk_h_0040bd24(u4);
  sk_h_0040bd24(u5);
  a0 = sk_h_00406e64();
  sk_h_004079b4(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e43b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e462c @ 0x003e462c   (est. sk_f_003e462c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e462c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e462c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5)
{
long *pl0;
  long ux0;
  
  *(word_t *)(ux0 + 0x10) = param_4;
  pl0 = (long *)sk_h_0040bb18(DAT_005a009c);
  *(long **)(ux0 + 0x18) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)&DAT_004060bc;
  sk_f_003e3c80((word_t)pl0,param_1,param_2,param_3,param_5);
  return;
}

/* FUN_003e4700 @ 0x003e4700   (est. sk_f_003e4700 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e4700(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e4700(void)
{
sk_h_00406574();
  sk_f_003e472c();
  sk_h_0036b270();
  return;
}

/* FUN_003e472c @ 0x003e472c   (est. sk_f_003e472c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e472c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e472c(void)
{
sk_h_003eaf4c();
  return;
}

/* FUN_003e4754 @ 0x003e4754   (est. sk_f_003e4754 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e4754(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e4754(void)
{
long l0;
  long ex0;
  long ux0;
  word_t ux1;
  
  sk_h_00084220();
  sk_h_0040679c();
  sk_h_00407450();
  l0 = sk_h_003fd0bc();
  *(byte *)(ux0 + *(int *)(l0 + 0x28)) = 0;
  *(byte *)(ux0 + *(int *)(l0 + 0x2c)) = 0;
  sk_h_0040654c();
  sk_h_00350968();
  sk_h_00377824();
  sk_h_00349530();
  sk_dispatch(*(code_t *)(ex0 + 0x20));sk_h_00407ea0((long)*(int *)(l0 + 0x24));
  sk_h_00084234(ux1);
  return;
}

/* FUN_003e47d4 @ 0x003e47d4   (est. sk_f_003e47d4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e47d4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e47d4(void)
{
word_t u0;
  long ex2;
  long ex0;
  word_t ex3;
  word_t ex1;
  long ux0;
  
  sk_h_00407000();
  sk_h_00406704();
  sk_h_004079a8();
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0x40) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x48) = ex3;
  u0 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux0 + 0x50) = u0;
  sk_h_0040683c();
  *(word_t *)(ux0 + 0x58) = ex1;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux0 + 0x60) = u0;
  sk_h_00407594();
  sk_h_00408db8();
  return;
}

/* FUN_003e488c @ 0x003e488c   (est. sk_f_003e488c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e488c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e488c(void)
{
long l0;
  byte b0;
  int i0;
  word_t u0;
  code_t *jt0;
  code_t *jt1;
  word_t *ex0;
  code_t *ex1;
  word_t ex2;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407c8c();
  sk_h_0040700c();
  *(long *)(ux0 + 0x68) = ux0;
  i0 = *(int *)(*(long *)(ux0 + 0x18) + 0x28);
  *(int *)(ux0 + 0xa8) = i0;
  b0 = *(byte *)(*(long *)(ux0 + 0x20) + (long)i0);
  *(byte *)(ux0 + 0xb0) = b0;
  if ((b0 & 1) != 0) {
    sk_h_00406f18();
    sk_h_004081c0();
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_00407c78(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e4900. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  i0 = *(int *)(*(long *)(ux0 + 0x18) + 0x2c);
  *(int *)(ux0 + 0xac) = i0;
  b0 = *(byte *)(*(long *)(ux0 + 0x20) + (long)i0);
  l0 = *(long *)(ux0 + 0x30);
  sk_h_0040652c();
  sk_h_00406608();
  sk_h_004068f4();
  sk_h_00406268();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  sk_h_00406fe0();
  if ((b0 & 1) == 0) {
    *(word_t **)(ux0 + 0x70) = ex0;
    *ex0 = ex2;
    ex0[1] = (word_t)&sk_lab_003e49bc;
    sk_h_00407740();
  }
  else {
    *(word_t **)(ux0 + 0xa0) = ex0;
    *ex0 = ex2;
    ex0[1] = (word_t)&sk_lab_003e4dec;
    sk_h_00407670();
  }
  sk_h_00406ab4();
  jt1 = ex1;
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e49b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e4a78 @ 0x003e4a78   (est. sk_f_003e4a78 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e4a78(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e4a78(void)
{
long l0;
  byte zf;
  word_t u0;
  word_t u1;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  long ex2;
  code_t *ex3;
  word_t ex0;
  code_t *ex1;
  word_t ex4;
  word_t u2;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  u2 = *(word_t *)(ux0 + 0x50);
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x48),u1,*(word_t *)(ux0 + 0x40));
    sk_dispatch((code_t)ex3);sk_h_00406f18();
    sk_h_004081c0();
    sk_h_0040bd24(u2);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e4af4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x18);
  sk_h_00406894(*(word_t *)(ux0 + 0x58),*(word_t *)(ux0 + 0x60));
  *(word_t *)(ux0 + 0x80) = ex0;
  *(word_t *)(ux0 + 0x88) = ex4;
  sk_h_00350624();
  sk_dispatch((code_t)ex1);sk_h_004062e8((long)*(int *)(l0 + 0x24));
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(ex2 + 4));
  *(long **)(ux0 + 0x90) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e4b90;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x60));
                    /* WARNING: Could not recover jumptable at 0x003e4b8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e4c70 @ 0x003e4c70   (est. sk_f_003e4c70 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e4c70(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e4c70(void)
{
long l0;
  byte b0;
  int i0;
  word_t u0;
  word_t u1;
  word_t u2;
  word_t u3;
  code_t *jt0;
  word_t u4;
  code_t *jt1;
  word_t *ex0;
  code_t *ex1;
  code_t *ex2;
  word_t ex3;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407c8c();
  sk_h_0040700c();
  if ((*(byte *)(ux0 + 0xb1) & 1) == 0) {
    jt1 = *(code_t *)(ux0 + 0x80);
    u1 = *(word_t *)(ux0 + 0x88);
    u3 = *(word_t *)(ux0 + 0x60);
    u4 = *(word_t *)(ux0 + 0x38);
    u2 = *(word_t *)(ux0 + 0x10);
    *(byte *)(*(long *)(ux0 + 0x20) + (long)*(int *)(ux0 + 0xac)) = 1;
    sk_dispatch((code_t)jt1, u1,u2,u3,u4);a0 = sk_h_00407bf8();
  }
  else {
    sk_h_00407cd4();
    u1 = sk_dispatch((code_t)ex1);if ((*(byte *)(ux0 + 0xb0) & 1) == 0) {
      i0 = *(int *)(*(long *)(ux0 + 0x18) + 0x2c);
      *(int *)(ux0 + 0xac) = i0;
      b0 = *(byte *)(*(long *)(ux0 + 0x20) + (long)i0);
      l0 = *(long *)(ux0 + 0x30);
      sk_h_0040652c();
      sk_h_00406608();
      sk_h_004068f4();
      sk_h_00406268();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      sk_h_00406fe0();
      if ((b0 & 1) == 0) {
        *(word_t **)(ux0 + 0x70) = ex0;
        *ex0 = ex3;
        ex0[1] = (word_t)&sk_lab_003e49bc;
        sk_h_00407740();
      }
      else {
        *(word_t **)(ux0 + 0xa0) = ex0;
        *ex0 = ex3;
        ex0[1] = (word_t)&sk_lab_003e4dec;
        sk_h_00407670();
      }
      sk_h_00406ab4();
      jt1 = ex2;
      sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e4de8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      sk_dispatch((code_t)jt1);return;
    }
    a0.hi = 1;
    a0.lo = u1;
  }
  a0 = sk_h_0040738c(a0.lo,a0.hi);
  sk_h_000839d8(a0.lo,a0.hi,1);
  u1 = *(word_t *)(ux0 + 0x50);
  sk_h_0040bd24(*(word_t *)(ux0 + 0x60));
  sk_h_0040bd24(u1);
  a0 = sk_h_00406e64();
  sk_h_00407c78(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e4d2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e4f34 @ 0x003e4f34   (est. sk_f_003e4f34 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e4f34(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e4f34(word_t param_1, word_t param_2, word_t param_3, long param_4, long param_5)
{
word_t u0;
  long ex7;
  long ex0;
  long ex1;
  code_t *ex2;
  word_t ex3;
  word_t ex4;
  word_t ex8;
  word_t ex5;
  word_t ex6;
  long ux0;
  long ux1;
  word_t ux2;
  
  sk_h_00408058();
  sk_h_0040700c();
  sk_h_00406c1c();
  *(word_t *)(ux1 + 0x40) = *(word_t *)(param_4 + 0x10);
  u0 = sk_h_0040684c();
  *(word_t *)(ux1 + 0x48) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x50) = ex8;
  u0 = sk_h_0040859c(*(word_t *)(ex7 + 0x40));
  *(word_t *)(ux1 + 0x58) = u0;
  u0 = sk_h_0040bb18(ux2 & 0xfffffffffffffff0);
  *(word_t *)(ux1 + 0x60) = u0;
  sk_h_00406dd0();
  sk_h_00408454();
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x70) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x78) = ex5;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux1 + 0x80) = u0;
  sk_h_0040683c();
  *(word_t *)(ux1 + 0x88) = ex6;
  u0 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux1 + 0x90) = u0;
  if (ux0 == 0) {
    sk_h_00407248();
    u0 = ex4;
  }
  else {
    sk_h_00406590();
    sk_dispatch((code_t)ex2);sk_h_0008e1ec();
    u0 = ex3;
  }
  *(word_t *)(ux1 + 0x98) = u0;
  *(word_t *)(ux1 + 0xa0) = param_3;
  sk_h_00353080();
  sk_h_00408044();
  sk_h_00408db8();
  return;
}

/* FUN_003e5074 @ 0x003e5074   (est. sk_f_003e5074 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e5074(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e5074(void)
{
word_t u0;
  word_t u1;
  byte b0;
  int i0;
  word_t u2;
  long l0;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  word_t ex1;
  word_t ex0;
  long ux0;
  sk16_t a0;
  
  u2 = sk_h_00407c8c();
  sk_h_0040700c();
  *(long *)(ux0 + 0xa8) = ux0;
  i0 = *(int *)(*(long *)(ux0 + 0x28) + 0x28);
  *(int *)(ux0 + 0x100) = i0;
  b0 = *(byte *)(*(long *)(ux0 + 0x30) + (long)i0);
  *(byte *)(ux0 + 0x108) = b0;
  if ((b0 & 1) != 0) {
    sk_h_00350744(*(word_t *)(ux0 + 0x10));
    sk_h_000839d8();
    sk_h_004081d8();
    u0 = *(word_t *)(ux0 + 0x58);
    u1 = *(word_t *)(ux0 + 0x60);
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24(u1);
    sk_h_0040bd24(u0);
    a0 = sk_h_0040678c();
    sk_h_00407c78(a0.lo,a0.hi,u2);
                    /* WARNING: Could not recover jumptable at 0x003e510c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  i0 = *(int *)(*(long *)(ux0 + 0x28) + 0x2c);
  *(int *)(ux0 + 0x104) = i0;
  b0 = *(byte *)(*(long *)(ux0 + 0x30) + (long)i0);
  u2 = *(word_t *)(ux0 + 0x38);
  sk_h_004083d8();
  sk_h_004083c0();
  sk_h_003504a0();
  sk_h_00377824();
  sk_h_00350968(u2);
  u2 = sk_h_00377bec();
  if ((b0 & 1) == 0) {
    *(word_t *)(ux0 + 0xb0) = u2;
    l0 = sk_h_003fcc4c(u2);
    sk_h_00350798();
    u2 = sk_h_00377dcc();
    *(word_t *)(ux0 + 0xb8) = u2;
    sk_h_004065e8();
    sk_h_0040bb18(*(word_t *)(l0 + 4));
    p0 = (word_t *)sk_h_00406fe0();
    *(word_t **)(ux0 + 0xc0) = p0;
    *p0 = ex0;
    sk_h_00407da0();
    u2 = sk_h_00407164();
  }
  else {
    *(word_t *)(ux0 + 0xe8) = u2;
    l0 = sk_h_003fcc4c(u2);
    sk_h_00350798();
    u2 = sk_h_00377dcc();
    *(word_t *)(ux0 + 0xf0) = u2;
    sk_h_004065e8();
    sk_h_0040bb18(*(word_t *)(l0 + 4));
    p0 = (word_t *)sk_h_00406fe0();
    *(word_t **)(ux0 + 0xf8) = p0;
    *p0 = ex1;
    p0[1] = (word_t)&sk_lab_003e57c0;
    sk_h_00407164();
    u2 = *(word_t *)(ux0 + 0x10);
  }
  sk_h_00407990(u2);
  sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e526c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e535c @ 0x003e535c   (est. sk_f_003e535c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e535c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e535c(void)
{
long l0;
  word_t u0;
  byte zf;
  word_t u1;
  word_t u2;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  long ex2;
  code_t *ex3;
  word_t ex0;
  code_t *ex1;
  word_t ex4;
  long ux0;
  sk16_t a0;
  
  u1 = sk_h_00407ca0();
  sk_h_0040700c();
  sk_h_00407aac();
  u2 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x78),u2,*(word_t *)(ux0 + 0x70));
    sk_dispatch((code_t)ex3);sk_h_00350744(*(word_t *)(ux0 + 0x10));
    sk_h_000839d8();
    sk_h_004081d8();
    u2 = *(word_t *)(ux0 + 0x58);
    u0 = *(word_t *)(ux0 + 0x60);
    sk_h_0040bd24();
    sk_h_0040bd24();
    sk_h_0040bd24(u0);
    sk_h_0040bd24(u2);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u1);
                    /* WARNING: Could not recover jumptable at 0x003e53f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x28);
  sk_h_00406894(*(word_t *)(ux0 + 0x88),*(word_t *)(ux0 + 0x90));
  *(word_t *)(ux0 + 200) = ex0;
  *(word_t *)(ux0 + 0xd0) = ex4;
  sk_h_00350624();
  sk_dispatch((code_t)ex1);sk_h_004062e8((long)*(int *)(l0 + 0x24));
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(ex2 + 4));
  *(long **)(ux0 + 0xd8) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e5494;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x90));
                    /* WARNING: Could not recover jumptable at 0x003e5490. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e557c @ 0x003e557c   (est. sk_f_003e557c — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e557c(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e557c(void)
{
code_t *pc0;
  byte b0;
  int i0;
  word_t u0;
  word_t u1;
  long l0;
  word_t *p0;
  word_t u3;
  word_t ex1;
  code_t *jt0;
  word_t u4;
  code_t *jt1;
  word_t ex2;
  word_t ex0;
  word_t u5;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407c8c();
  sk_h_0040700c();
  if ((*(byte *)(ux0 + 0x109) & 1) == 0) {
    pc0 = *(code_t *)(ux0 + 200);
    u3 = *(word_t *)(ux0 + 0xd0);
    u5 = *(word_t *)(ux0 + 0x90);
    u4 = *(word_t *)(ux0 + 0x68);
    u1 = *(word_t *)(ux0 + 0x10);
    *(byte *)(*(long *)(ux0 + 0x30) + (long)*(int *)(ux0 + 0x104)) = 1;
    sk_dispatch((code_t)pc0, u3,u1,u5,u4);sk_h_00407bf8();
    u3 = ex1;
  }
  else {
    sk_dispatch(*(code_t *)(*(long *)(ux0 + 0x88) + 8), *(word_t *)(ux0 + 0x90),*(word_t *)(ux0 + 0x68));if ((*(byte *)(ux0 + 0x108) & 1) == 0) {
      i0 = *(int *)(*(long *)(ux0 + 0x28) + 0x2c);
      *(int *)(ux0 + 0x104) = i0;
      b0 = *(byte *)(*(long *)(ux0 + 0x30) + (long)i0);
      u0 = *(word_t *)(ux0 + 0x38);
      sk_h_004083d8();
      sk_h_004083c0();
      sk_h_003504a0();
      sk_h_00377824();
      sk_h_00350968(u0);
      u0 = sk_h_00377bec();
      if ((b0 & 1) == 0) {
        *(word_t *)(ux0 + 0xb0) = u0;
        l0 = sk_h_003fcc4c(u0);
        sk_h_00350798();
        u0 = sk_h_00377dcc();
        *(word_t *)(ux0 + 0xb8) = u0;
        sk_h_004065e8();
        sk_h_0040bb18(*(word_t *)(l0 + 4));
        p0 = (word_t *)sk_h_00406fe0();
        *(word_t **)(ux0 + 0xc0) = p0;
        *p0 = ex0;
        sk_h_00407da0();
        u0 = sk_h_00407164();
      }
      else {
        *(word_t *)(ux0 + 0xe8) = u0;
        l0 = sk_h_003fcc4c(u0);
        sk_h_00350798();
        u0 = sk_h_00377dcc();
        *(word_t *)(ux0 + 0xf0) = u0;
        sk_h_004065e8();
        sk_h_0040bb18(*(word_t *)(l0 + 4));
        p0 = (word_t *)sk_h_00406fe0();
        *(word_t **)(ux0 + 0xf8) = p0;
        *p0 = ex2;
        p0[1] = (word_t)&sk_lab_003e57c0;
        sk_h_00407164();
        u0 = *(word_t *)(ux0 + 0x10);
      }
      sk_h_00407990(u0);
      sk_h_00407c78();
                    /* WARNING: Could not recover jumptable at 0x003e57bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      sk_dispatch((code_t)jt1);return;
    }
    u3 = 1;
  }
  sk_h_000839d8(*(word_t *)(ux0 + 0x10),u3,1,*(word_t *)(ux0 + 0x68));
  u5 = *(word_t *)(ux0 + 0x80);
  u3 = *(word_t *)(ux0 + 0x58);
  u1 = *(word_t *)(ux0 + 0x60);
  sk_h_0040bd24(*(word_t *)(ux0 + 0x90));
  sk_h_0040bd24(u5);
  sk_h_0040bd24(u1);
  sk_h_0040bd24(u3);
  a0 = sk_h_00406e64();
  sk_h_00407c78(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e5658. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e5b18 @ 0x003e5b18   (est. sk_f_003e5b18 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e5b18(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e5b18(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5)
{
long *pl0;
  long ux0;
  
  *(word_t *)(ux0 + 0x10) = param_4;
  pl0 = (long *)sk_h_0040bb18(DAT_005a00ac);
  *(long **)(ux0 + 0x18) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)&DAT_004060bc;
  sk_f_003e4f34((word_t)pl0,param_1,param_2,param_3,param_5);
  return;
}

/* FUN_003e5bec @ 0x003e5bec   (est. sk_f_003e5bec — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e5bec(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e5bec(void)
{
sk_h_00406574();
  sk_f_003e5c18();
  sk_h_0036b270();
  return;
}

/* FUN_003e5c18 @ 0x003e5c18   (est. sk_f_003e5c18 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e5c18(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e5c18(void)
{
sk_h_003eaf4c();
  return;
}

/* FUN_003e5c30 @ 0x003e5c30   (est. sk_f_003e5c30 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e5c30(undefined8 param_1,long param_2)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e5c30(word_t param_1, long param_2)
{
long ex0;
  
  sk_h_0040654c(param_2,*(word_t *)(param_2 + 0x18),*(word_t *)(param_2 + 0x10));
  sk_h_00377824();
  sk_h_00350404();
                    /* WARNING: Could not recover jumptable at 0x003e5c80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch(*(code_t *)(ex0 + 0x10), param_1);return;
}

/* FUN_003e5d50 @ 0x003e5d50   (est. sk_f_003e5d50 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e5d50(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e5d50(void)
{
word_t u0;
  long ex2;
  long ex0;
  word_t ex3;
  word_t ex1;
  long ux0;
  
  sk_h_00407000();
  sk_h_00406704();
  sk_h_004079a8();
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux0 + 0x40) = u0;
  sk_h_00352018();
  *(word_t *)(ux0 + 0x48) = ex3;
  u0 = sk_h_004078e8(*(word_t *)(ex2 + 0x40));
  *(word_t *)(ux0 + 0x50) = u0;
  sk_h_0040683c();
  *(word_t *)(ux0 + 0x58) = ex1;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux0 + 0x60) = u0;
  sk_h_00407594();
  sk_h_00408db8();
  return;
}

/* FUN_003e5e08 @ 0x003e5e08   (est. sk_f_003e5e08 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e5e08(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e5e08(void)
{
long l0;
  byte b0;
  int i0;
  word_t u0;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  word_t ex0;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  *(long *)(ux0 + 0x68) = ux0;
  i0 = *(int *)(*(long *)(ux0 + 0x18) + 0x28);
  *(int *)(ux0 + 0xa0) = i0;
  b0 = *(byte *)(*(long *)(ux0 + 0x20) + (long)i0);
  *(byte *)(ux0 + 0xa4) = b0;
  if ((b0 & 1) != 0) {
    sk_h_00407604();
    sk_h_0040686c();
    sk_h_0040bd24();
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e5e80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x30);
  sk_h_0040652c();
  sk_h_00406608();
  sk_h_004068f4();
  sk_h_00406268();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0x70) = p0;
  *p0 = ex0;
  sk_h_004074c4();
  sk_h_00406ab4();
                    /* WARNING: Could not recover jumptable at 0x003e5f08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e5fc8 @ 0x003e5fc8   (est. sk_f_003e5fc8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e5fc8(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e5fc8(void)
{
long l0;
  byte zf;
  word_t u0;
  word_t u1;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  long ex2;
  code_t *ex3;
  word_t ex0;
  code_t *ex1;
  word_t ex4;
  word_t u2;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  u2 = *(word_t *)(ux0 + 0x38);
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x48),u1,*(word_t *)(ux0 + 0x40));
    sk_dispatch((code_t)ex3);sk_h_00407604();
    sk_h_0040686c();
    sk_h_0040bd24(u2);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e6048. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x18);
  sk_h_00406894(*(word_t *)(ux0 + 0x58),*(word_t *)(ux0 + 0x60));
  *(word_t *)(ux0 + 0x80) = ex0;
  *(word_t *)(ux0 + 0x88) = ex4;
  sk_h_00350624();
  sk_dispatch((code_t)ex1);sk_h_004062e8((long)*(int *)(l0 + 0x24));
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(ex2 + 4));
  *(long **)(ux0 + 0x90) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e60e4;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x60));
                    /* WARNING: Could not recover jumptable at 0x003e60e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e61c4 @ 0x003e61c4   (est. sk_f_003e61c4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e61c4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e61c4(void)
{
long l0;
  word_t u0;
  word_t *p0;
  code_t *jt0;
  code_t *ex1;
  code_t *ex0;
  code_t *jt1;
  word_t ex2;
  word_t u2;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  if ((*(byte *)(ux0 + 0xa5) & 1) == 0) {
    sk_h_00407cd4();
    u2 = sk_dispatch((code_t)ex0);if ((*(byte *)(ux0 + 0xa4) & 1) == 0) {
      l0 = *(long *)(ux0 + 0x30);
      sk_h_0040652c();
      sk_h_00406608();
      sk_h_004068f4();
      sk_h_00406268();
      sk_h_0040bb18(*(word_t *)(l0 + 4));
      p0 = (word_t *)sk_h_00406fe0();
      *(word_t **)(ux0 + 0x70) = p0;
      *p0 = ex2;
      sk_h_004074c4();
      sk_h_00406ab4();
                    /* WARNING: Could not recover jumptable at 0x003e62e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      sk_dispatch((code_t)jt1);return;
    }
    a0.hi = 1;
    a0.lo = u2;
  }
  else {
    sk_h_00407d14(*(word_t *)(ux0 + 0x88));
    sk_dispatch((code_t)ex1);a0 = sk_h_00407bf8();
  }
  u2 = *(word_t *)(ux0 + 0x50);
  sk_h_0040738c(a0.lo,a0.hi);
  sk_h_004075a4();
  sk_h_0040bd24(u2);
  a0 = sk_h_00406e64();
  sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e6260. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e62ec @ 0x003e62ec   (est. sk_f_003e62ec — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e62ec(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e62ec(void)
{
code_t *jt0;
  
  sk_h_00407000();
  sk_h_00408038();
  sk_h_0040bd24();
  sk_h_00407128();
                    /* WARNING: Could not recover jumptable at 0x003e633c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt0);return;
}

/* FUN_003e63a8 @ 0x003e63a8   (est. sk_f_003e63a8 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e63a8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e63a8(word_t param_1, word_t param_2, word_t param_3, long param_4)
{
word_t u0;
  long ex7;
  long ex0;
  long ex1;
  code_t *ex2;
  word_t ex3;
  word_t ex4;
  word_t ex8;
  word_t ex5;
  word_t ex6;
  long ux0;
  long ux1;
  
  sk_h_00407c8c();
  sk_h_0040700c();
  sk_h_00406c1c();
  *(word_t *)(ux1 + 0x40) = *(word_t *)(param_4 + 0x10);
  u0 = sk_h_0040684c();
  *(word_t *)(ux1 + 0x48) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x50) = ex8;
  u0 = sk_h_004078e8(*(word_t *)(ex7 + 0x40));
  *(word_t *)(ux1 + 0x58) = u0;
  u0 = sk_h_00406dd0();
  *(word_t *)(ux1 + 0x60) = u0;
  sk_h_00350798();
  u0 = sk_h_00310d68();
  *(word_t *)(ux1 + 0x68) = u0;
  sk_h_00352018();
  *(word_t *)(ux1 + 0x70) = ex5;
  u0 = sk_h_004078e8(*(word_t *)(ex0 + 0x40));
  *(word_t *)(ux1 + 0x78) = u0;
  sk_h_0040683c();
  *(word_t *)(ux1 + 0x80) = ex6;
  u0 = sk_h_004078e8(*(word_t *)(ex1 + 0x40));
  *(word_t *)(ux1 + 0x88) = u0;
  if (ux0 == 0) {
    sk_h_00407248();
    u0 = ex4;
  }
  else {
    sk_h_00406590();
    sk_dispatch((code_t)ex2);sk_h_0008e1ec();
    u0 = ex3;
  }
  *(word_t *)(ux1 + 0x90) = u0;
  *(word_t *)(ux1 + 0x98) = param_3;
  sk_h_00353080();
  sk_h_00407c78();
  sk_h_00408db8();
  return;
}

/* FUN_003e64e0 @ 0x003e64e0   (est. sk_f_003e64e0 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e64e0(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e64e0(void)
{
word_t u0;
  long l0;
  byte b0;
  int i0;
  word_t u1;
  word_t *p0;
  code_t *jt0;
  code_t *jt1;
  word_t ex0;
  long ux0;
  sk16_t a0;
  
  u1 = sk_h_00407ca0();
  sk_h_0040700c();
  *(long *)(ux0 + 0xa0) = ux0;
  i0 = *(int *)(*(long *)(ux0 + 0x28) + 0x28);
  *(int *)(ux0 + 0xe0) = i0;
  b0 = *(byte *)(*(long *)(ux0 + 0x30) + (long)i0);
  *(byte *)(ux0 + 0xe4) = b0;
  if ((b0 & 1) != 0) {
    sk_h_00407960();
    u0 = *(word_t *)(ux0 + 0x58);
    sk_h_0040686c();
    sk_h_0040bd24();
    sk_h_0040bd24(u0);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u1);
                    /* WARNING: Could not recover jumptable at 0x003e6560. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x40);
  sk_h_0040652c();
  sk_h_00406608();
  sk_h_004083cc();
  u1 = sk_h_00406e8c();
  *(word_t *)(ux0 + 0xb0) = u1;
  sk_h_00406288();
  sk_h_0040bb18(*(word_t *)(l0 + 4));
  p0 = (word_t *)sk_h_00406fe0();
  *(word_t **)(ux0 + 0xb8) = p0;
  *p0 = ex0;
  sk_h_00407830();
  sk_h_004067b8();
                    /* WARNING: Could not recover jumptable at 0x003e65f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

/* FUN_003e66e4 @ 0x003e66e4   (est. sk_f_003e66e4 — Swift-runtime object/ARC helper)
 * Ghidra: void FUN_003e66e4(void)
 * Confidence: medium
 * Notes: register-aliased / unrecovered indirect dispatch noise; call
 *   sequence and object-field accesses preserved faithfully. */
void sk_f_003e66e4(void)
{
long l0;
  byte zf;
  word_t u0;
  word_t u1;
  long *pl0;
  code_t *jt0;
  code_t *jt1;
  long ex2;
  code_t *ex3;
  word_t ex0;
  code_t *ex1;
  word_t ex4;
  word_t u2;
  long ux0;
  sk16_t a0;
  
  u0 = sk_h_00407ca0();
  sk_h_0040700c();
  u2 = *(word_t *)(ux0 + 0x60);
  u1 = sk_h_00406420();
  if ((bool)zf) {
    sk_h_0040711c(*(word_t *)(ux0 + 0x70),u1,*(word_t *)(ux0 + 0x68));
    sk_dispatch((code_t)ex3);sk_h_00407960();
    u1 = *(word_t *)(ux0 + 0x58);
    sk_h_0040686c();
    sk_h_0040bd24(u2);
    sk_h_0040bd24(u1);
    a0 = sk_h_0040678c();
    sk_h_00407e58(a0.lo,a0.hi,u0);
                    /* WARNING: Could not recover jumptable at 0x003e676c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    sk_dispatch((code_t)jt0);return;
  }
  l0 = *(long *)(ux0 + 0x28);
  sk_h_00406894(*(word_t *)(ux0 + 0x80),*(word_t *)(ux0 + 0x88));
  *(word_t *)(ux0 + 0xc0) = ex0;
  *(word_t *)(ux0 + 200) = ex4;
  sk_h_00350624();
  sk_dispatch((code_t)ex1);sk_h_004062e8((long)*(int *)(l0 + 0x24));
  pl0 = (long *)sk_h_0040bb18(*(word_t *)(ex2 + 4));
  *(long **)(ux0 + 0xd0) = pl0;
  *pl0 = ux0;
  pl0[1] = (long)(word_t)&sk_lab_003e6808;
  sk_h_00406bb4(*(word_t *)(ux0 + 0x88));
                    /* WARNING: Could not recover jumptable at 0x003e6804. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sk_dispatch((code_t)jt1);return;
}

