/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R56: 0x3d95cc-0x3e66e4. This region is the Swift-runtime
 * message/notification dispatch engine: it builds per-message context
 * records (a closure/box record addressed in x22), populates their
 * function-pointer slots, allocates boxed continuation records, and ends in
 * an indirect tail dispatch through a slot or an unrecovered jump table.
 * Ghidra could not recover several register-carried values (extraout_*,
 * in_x*) or indirect jump targets (UNRECOVERED_JUMPTABLE); those are kept as
 * documented artifacts. All names are estimates unless string-matched.
 *
 * Calling-convention note: many helpers are declared with empty-paren
 * prototypes (unspecified arguments); they accept any argument list and
 * return a machine word. The context record is the pointer held in x22.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1). */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* Negative-number error string: s_Can_t_prefix_a_negative_number_o_005dbf40 */
extern char sk_neg_number_str[];

/* Type-metadata / function-pointer globals referenced by the dispatch engine. */
extern unsigned long DAT_0059ffbc, DAT_0059ffe4, DAT_0059fff4, DAT_005a0004,
       DAT_005a0024, DAT_005a005c, DAT_005a0064, DAT_005a009c, DAT_005a00ac;
extern void DAT_003fcf24(void), DAT_00405fac(void), DAT_00405fdc(void),
       DAT_004060bc(void), DAT_005a0038(void), DAT_005a0078(void),
       DAT_005a0088(void), DAT_00614890(void), DAT_00614a5c(void);
extern unsigned long (*DAT_00658c80)();

/* Out-of-range cL4 runtime helpers (owned by other range workers). Empty-paren
 * prototypes accept any arguments and return a machine word. */
extern unsigned long sk_r56_00002534();
extern unsigned long sk_r56_0006b6f4();
extern unsigned long sk_r56_0007c028();
extern unsigned long sk_r56_0007c1a4();
extern unsigned long sk_r56_0007c1c4();
extern unsigned long sk_r56_000839d8();
extern unsigned long sk_r56_000839f8();
extern unsigned long sk_r56_0008409c();
extern unsigned long sk_r56_00084174();
extern unsigned long sk_r56_00084180();
extern unsigned long sk_r56_00084220();
extern unsigned long sk_r56_00084234();
extern unsigned long sk_r56_0008e1ec();
extern unsigned long sk_r56_0008e500();
extern unsigned long sk_r56_0008e518();
extern unsigned long sk_r56_000a649c();
extern unsigned long sk_r56_000a6f88();
extern unsigned long sk_r56_000aa4ec();
extern unsigned long sk_r56_000dbd0c();
extern unsigned long sk_r56_0011aa70();
extern unsigned long sk_r56_0014ae44();
extern unsigned long sk_r56_0016186c();
extern unsigned long sk_r56_001afa84();
extern unsigned long sk_r56_00310d68();
extern unsigned long sk_r56_00349530();
extern unsigned long sk_r56_0034a210();
extern unsigned long sk_r56_0034b05c();
extern unsigned long sk_r56_0034b0d4();
extern unsigned long sk_r56_0034d004();
extern unsigned long sk_r56_00350404();
extern unsigned long sk_r56_00350470();
extern unsigned long sk_r56_003504a0();
extern unsigned long sk_r56_003504e8();
extern unsigned long sk_r56_00350500();
extern unsigned long sk_r56_0035050c();
extern unsigned long sk_r56_00350518();
extern unsigned long sk_r56_00350548();
extern unsigned long sk_r56_00350560();
extern unsigned long sk_r56_00350618();
extern unsigned long sk_r56_00350624();
extern unsigned long sk_r56_00350720();
extern unsigned long sk_r56_00350744();
extern unsigned long sk_r56_00350750();
extern unsigned long sk_r56_00350798();
extern unsigned long sk_r56_003507e0();
extern unsigned long sk_r56_00350968();
extern unsigned long sk_r56_00350974();
extern unsigned long sk_r56_003509c8();
extern unsigned long sk_r56_00350bfc();
extern unsigned long sk_r56_003510a0();
extern unsigned long sk_r56_003510c4();
extern unsigned long sk_r56_0035136c();
extern unsigned long sk_r56_003513b4();
extern unsigned long sk_r56_00351584();
extern unsigned long sk_r56_00351cd0();
extern unsigned long sk_r56_00351d24();
extern unsigned long sk_r56_00351da8();
extern unsigned long sk_r56_00351f10();
extern unsigned long sk_r56_00352018();
extern unsigned long sk_r56_00352700();
extern unsigned long sk_r56_00353080();
extern unsigned long sk_r56_00353930();
extern unsigned long sk_r56_00353c00();
extern unsigned long sk_r56_0035a7e8();
extern unsigned long sk_r56_0035ac70();
extern unsigned long sk_r56_00365b6c();
extern unsigned long sk_r56_003698b0();
extern unsigned long sk_r56_0036a940();
extern unsigned long sk_r56_0036b118();
extern unsigned long sk_r56_0036b270();
extern unsigned long sk_r56_00377824();
extern unsigned long sk_r56_00377bec();
extern unsigned long sk_r56_00377dcc();
extern unsigned long sk_r56_003e6d08();
extern unsigned long sk_r56_003e9df8();
extern unsigned long sk_r56_003eaf4c();
extern unsigned long sk_r56_003fcc1c();
extern unsigned long sk_r56_003fcc4c();
extern unsigned long sk_r56_003fd0bc();
extern unsigned long sk_r56_00406268();
extern unsigned long sk_r56_00406288();
extern unsigned long sk_r56_004062a8();
extern unsigned long sk_r56_004062c8();
extern unsigned long sk_r56_004062e8();
extern unsigned long sk_r56_00406374();
extern unsigned long sk_r56_00406420();
extern unsigned long sk_r56_0040652c();
extern unsigned long sk_r56_0040654c();
extern unsigned long sk_r56_00406560();
extern unsigned long sk_r56_00406574();
extern unsigned long sk_r56_00406590();
extern unsigned long sk_r56_004065c8();
extern unsigned long sk_r56_004065e8();
extern unsigned long sk_r56_00406608();
extern unsigned long sk_r56_00406624();
extern unsigned long sk_r56_00406704();
extern unsigned long sk_r56_0040678c();
extern unsigned long sk_r56_0040679c();
extern unsigned long sk_r56_004067b8();
extern unsigned long sk_r56_004067cc();
extern unsigned long sk_r56_004067f8();
extern unsigned long sk_r56_0040683c();
extern unsigned long sk_r56_0040684c();
extern unsigned long sk_r56_0040686c();
extern unsigned long sk_r56_00406894();
extern unsigned long sk_r56_004068bc();
extern unsigned long sk_r56_004068f4();
extern unsigned long sk_r56_00406944();
extern unsigned long sk_r56_0040697c();
extern unsigned long sk_r56_0040698c();
extern unsigned long sk_r56_004069b0();
extern unsigned long sk_r56_004069c4();
extern unsigned long sk_r56_00406a5c();
extern unsigned long sk_r56_00406a94();
extern unsigned long sk_r56_00406aa4();
extern unsigned long sk_r56_00406ab4();
extern unsigned long sk_r56_00406b24();
extern unsigned long sk_r56_00406b84();
extern unsigned long sk_r56_00406bb4();
extern unsigned long sk_r56_00406bd4();
extern unsigned long sk_r56_00406be4();
extern unsigned long sk_r56_00406c1c();
extern unsigned long sk_r56_00406c5c();
extern unsigned long sk_r56_00406c80();
extern unsigned long sk_r56_00406cc8();
extern unsigned long sk_r56_00406ce0();
extern unsigned long sk_r56_00406cf0();
extern unsigned long sk_r56_00406d70();
extern unsigned long sk_r56_00406da8();
extern unsigned long sk_r56_00406db8();
extern unsigned long sk_r56_00406dd0();
extern unsigned long sk_r56_00406e18();
extern unsigned long sk_r56_00406e34();
extern unsigned long sk_r56_00406e48();
extern unsigned long sk_r56_00406e64();
extern unsigned long sk_r56_00406e8c();
extern unsigned long sk_r56_00406ee4();
extern unsigned long sk_r56_00406f18();
extern unsigned long sk_r56_00406f2c();
extern unsigned long sk_r56_00406f40();
extern unsigned long sk_r56_00406f50();
extern unsigned long sk_r56_00406f84();
extern unsigned long sk_r56_00406fb0();
extern unsigned long sk_r56_00406fd4();
extern unsigned long sk_r56_00406fe0();
extern unsigned long sk_r56_00407000();
extern unsigned long sk_r56_0040700c();
extern unsigned long sk_r56_00407018();
extern unsigned long sk_r56_00407070();
extern unsigned long sk_r56_00407080();
extern unsigned long sk_r56_00407090();
extern unsigned long sk_r56_004070a0();
extern unsigned long sk_r56_004070d8();
extern unsigned long sk_r56_004070e4();
extern unsigned long sk_r56_00407100();
extern unsigned long sk_r56_0040711c();
extern unsigned long sk_r56_00407128();
extern unsigned long sk_r56_00407164();
extern unsigned long sk_r56_004071c0();
extern unsigned long sk_r56_00407214();
extern unsigned long sk_r56_00407248();
extern unsigned long sk_r56_00407260();
extern unsigned long sk_r56_0040733c();
extern unsigned long sk_r56_00407374();
extern unsigned long sk_r56_0040738c();
extern unsigned long sk_r56_00407400();
extern unsigned long sk_r56_00407450();
extern unsigned long sk_r56_00407478();
extern unsigned long sk_r56_00407484();
extern unsigned long sk_r56_004074c4();
extern unsigned long sk_r56_004074e8();
extern unsigned long sk_r56_00407504();
extern unsigned long sk_r56_0040752c();
extern unsigned long sk_r56_00407594();
extern unsigned long sk_r56_004075a4();
extern unsigned long sk_r56_00407604();
extern unsigned long sk_r56_00407610();
extern unsigned long sk_r56_0040764c();
extern unsigned long sk_r56_00407670();
extern unsigned long sk_r56_004076a8();
extern unsigned long sk_r56_004076c4();
extern unsigned long sk_r56_00407700();
extern unsigned long sk_r56_00407740();
extern unsigned long sk_r56_00407764();
extern unsigned long sk_r56_00407774();
extern unsigned long sk_r56_00407784();
extern unsigned long sk_r56_004077a0();
extern unsigned long sk_r56_004077cc();
extern unsigned long sk_r56_00407814();
extern unsigned long sk_r56_00407824();
extern unsigned long sk_r56_00407830();
extern unsigned long sk_r56_00407840();
extern unsigned long sk_r56_0040785c();
extern unsigned long sk_r56_004078b4();
extern unsigned long sk_r56_004078e8();
extern unsigned long sk_r56_004078f4();
extern unsigned long sk_r56_0040790c();
extern unsigned long sk_r56_00407924();
extern unsigned long sk_r56_00407954();
extern unsigned long sk_r56_00407960();
extern unsigned long sk_r56_00407990();
extern unsigned long sk_r56_004079a8();
extern unsigned long sk_r56_004079b4();
extern unsigned long sk_r56_004079cc();
extern unsigned long sk_r56_00407a60();
extern unsigned long sk_r56_00407aa0();
extern unsigned long sk_r56_00407aac();
extern unsigned long sk_r56_00407ab8();
extern unsigned long sk_r56_00407ad0();
extern unsigned long sk_r56_00407adc();
extern unsigned long sk_r56_00407b48();
extern unsigned long sk_r56_00407bb8();
extern unsigned long sk_r56_00407bf8();
extern unsigned long sk_r56_00407c3c();
extern unsigned long sk_r56_00407c78();
extern unsigned long sk_r56_00407c8c();
extern unsigned long sk_r56_00407ca0();
extern unsigned long sk_r56_00407cc4();
extern unsigned long sk_r56_00407cd4();
extern unsigned long sk_r56_00407ce4();
extern unsigned long sk_r56_00407d14();
extern unsigned long sk_r56_00407d90();
extern unsigned long sk_r56_00407da0();
extern unsigned long sk_r56_00407e58();
extern unsigned long sk_r56_00407e6c();
extern unsigned long sk_r56_00407ea0();
extern unsigned long sk_r56_00407f48();
extern unsigned long sk_r56_00408038();
extern unsigned long sk_r56_00408044();
extern unsigned long sk_r56_00408058();
extern unsigned long sk_r56_0040807c();
extern unsigned long sk_r56_004080cc();
extern unsigned long sk_r56_00408178();
extern unsigned long sk_r56_00408190();
extern unsigned long sk_r56_004081b4();
extern unsigned long sk_r56_004081c0();
extern unsigned long sk_r56_004081d8();
extern unsigned long sk_r56_004081fc();
extern unsigned long sk_r56_00408224();
extern unsigned long sk_r56_00408244();
extern unsigned long sk_r56_0040826c();
extern unsigned long sk_r56_00408280();
extern unsigned long sk_r56_004082a8();
extern unsigned long sk_r56_00408308();
extern unsigned long sk_r56_00408328();
extern unsigned long sk_r56_0040833c();
extern unsigned long sk_r56_00408348();
extern unsigned long sk_r56_00408354();
extern unsigned long sk_r56_00408360();
extern unsigned long sk_r56_00408374();
extern unsigned long sk_r56_00408380();
extern unsigned long sk_r56_004083a0();
extern unsigned long sk_r56_004083c0();
extern unsigned long sk_r56_004083cc();
extern unsigned long sk_r56_004083d8();
extern unsigned long sk_r56_004083f0();
extern unsigned long sk_r56_00408404();
extern unsigned long sk_r56_00408410();
extern unsigned long sk_r56_00408440();
extern unsigned long sk_r56_00408454();
extern unsigned long sk_r56_00408460();
extern unsigned long sk_r56_004084a4();
extern unsigned long sk_r56_00408538();
extern unsigned long sk_r56_0040859c();
extern unsigned long sk_r56_004085b4();
extern unsigned long sk_r56_00408db8();
extern unsigned long sk_r56_0040bb18();
extern unsigned long sk_r56_0040bd24();

/* Continuation labels used as Swift closure-record function pointers. */
extern void LAB_003da07c(void);
extern void LAB_003da25c(void);
extern void LAB_003db214(void);
extern void LAB_003db4f8(void);
extern void LAB_003db70c(void);
extern void LAB_003dc214(void);
extern void LAB_003dca9c(void);
extern void LAB_003dce40(void);
extern void LAB_003dd0b8(void);
extern void LAB_003dda40(void);
extern void LAB_003de0c0(void);
extern void LAB_003de298(void);
extern void LAB_003de86c(void);
extern void LAB_003df130(void);
extern void LAB_003df8b0(void);
extern void LAB_003dff30(void);
extern void LAB_003e05a8(void);
extern void LAB_003e0aa4(void);
extern void LAB_003e1460(void);
extern void LAB_003e1b10(void);
extern void LAB_003e1ff0(void);
extern void LAB_003e2458(void);
extern void LAB_003e2874(void);
extern void LAB_003e2cdc(void);
extern void LAB_003e370c(void);
extern void LAB_003e3908(void);
extern void LAB_003e3f5c(void);
extern void LAB_003e4194(void);
extern void LAB_003e49bc(void);
extern void LAB_003e4b90(void);
extern void LAB_003e4dec(void);
extern void LAB_003e5494(void);
extern void LAB_003e57c0(void);
extern void LAB_003e60e4(void);
extern void LAB_003e6808(void);
extern void LAB_00614a7c(void);

/* In-range callees (forward declarations). */
extern void sk_r56_003d9600();
extern void sk_r56_003da7f8();
extern void sk_r56_003dcc4c();
extern void sk_r56_003dd540();
extern void sk_r56_003dd840();
extern void sk_r56_003ddecc();
extern void sk_r56_003de418();
extern void sk_r56_003e012c();
extern void sk_r56_003e08fc();
extern void sk_r56_003e1da8();
extern void sk_r56_003e262c();
extern void sk_r56_003e3484();
extern void sk_r56_003e3c80();
extern void sk_r56_003e472c();
extern void sk_r56_003e4f34();
extern void sk_r56_003e5c18();






/* sk_r56_003d95cc @ 0x003d95cc   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003d95cc()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_00406574();
    sk_r56_003d9600();
    sk_r56_0036b270();
    return;
}


/* sk_r56_003d9600 @ 0x003d9600   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003d9600()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_003e6d08();
    return;
}


/* sk_r56_003d961c @ 0x003d961c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003d961c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long rx9;
    v1 = sk_r56_0040654c(param_2,param_3,param_3);
    sk_r56_00377824(v1,rx9);
    sk_r56_00350744(param_1);
    sk_r56_000839d8();
    return;
}


/* sk_r56_003d96ac @ 0x003d96ac   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003d96ac()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    long rx1;
    long rx8;
    long rx8_00;
    long rx8_01;
    long rx8_02;
    long rx8_03;
    long rx8_04;
    long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    unsigned long rx16_02;
    unsigned long rx16_03;
    unsigned long rx16_04;
    unsigned long rx16_05;
    unsigned long r24;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    sk_r56_00407214();
    sk_r56_003509c8();
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx16 + 0x40));
    ctx[6] = (unsigned long)(v1);
    ctx[7] = (unsigned long)(*(unsigned long *)((char*)rx1 + 0x20));
    ctx[8] = (unsigned long)(*(unsigned long *)((char*)rx1 + 0x10));
    v1 = sk_r56_0040807c();
    ctx[9] = (unsigned long)(v1);
    sk_r56_00350500();
    v1 = sk_r56_00310d68();
    ctx[10] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[11] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[12] = (unsigned long)(v1);
    sk_r56_00406f50();
    ctx[13] = (unsigned long)(rx16_01);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[14] = (unsigned long)(v1);
    ctx[15] = (unsigned long)(*(unsigned long *)((char*)rx1 + 0x28));
    sk_r56_00350548(0xff);
    v1 = sk_r56_00377824();
    ctx[16] = (unsigned long)(v1);
    sk_r56_00350500();
    v1 = sk_r56_00310d68();
    ctx[17] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[18] = (unsigned long)(rx16_02);
    v1 = sk_r56_004081b4(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[19] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(r24 & 0xfffffffffffffff0);
    ctx[20] = (unsigned long)(v1);
    sk_r56_00406f50();
    ctx[21] = (unsigned long)(rx16_03);
    v2 = *(unsigned long *)((char*)rx8_02 + 0x40) + 0xf;
    v1 = sk_r56_0040bb18(v2 & 0xfffffffffffffff0);
    ctx[22] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v2 & 0xfffffffffffffff0);
    ctx[23] = (unsigned long)(v1);
    sk_r56_00350548(0xff);
    v2 = sk_r56_00377824();
    ctx[24] = (unsigned long)(v2);
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    *(unsigned long *)((char*)ctx + 200) = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[26] = (unsigned long)(rx16_04);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_03 + 0x40));
    ctx[27] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[28] = (unsigned long)(rx16_05);
    v1 = sk_r56_00407b48(*(unsigned long *)((char*)rx8_04 + 0x40));
    ctx[29] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v2 & 0xfffffffffffffff0);
    ctx[30] = (unsigned long)(v1);
    sk_r56_00407594();
    sk_r56_00407c78();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003d98d8 @ 0x003d98d8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003d98d8()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    int i1;
    unsigned long v2;
    unsigned long * p3;
    long l4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long rx8;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx10;
    unsigned long rx10_00;
    unsigned long (*rx11)();
    unsigned long (*rx16)();
    unsigned long (*rx16_00)();
    unsigned long rx17;
    unsigned long rx17_00;
    unsigned long v5;
    cL4_w16_t pair6;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    v2 = sk_r56_00407e6c();
    pair6.lo = sk_r56_00407924(); pair6.hi = 0;  /* x1 half */
    i1 = *((int*)((char*)ctx[3] + 0x3c));
    *((int*)ctx+0x158) = i1;
    if ((*((unsigned char*)((char*)ctx[4] + i1)) & 1) != 0) {
        sk_r56_0040698c();
        sk_r56_0040686c();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24(rx8);
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_004076a8(pair6.lo,pair6.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003d9988. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    *((int*)((char*)ctx + 0x15c)) = *((int*)((char*)ctx[3] + 0x38));
    ctx[31] = (unsigned long)(*(unsigned long *)((char*)ctx[26] + 0x10));
    sk_r56_00408460(pair6.lo,pair6.hi,*(unsigned long *)((char*)ctx + 200));
    (*rx11)();
    sk_r56_00406420();
    if (carry) {
        v5 = ctx[7];
        l4 = ctx[8];
        sk_r56_00353930(ctx[26],ctx[27], *(unsigned long *)((char*)ctx + 200));
        ctx[36] = (unsigned long)((unsigned long)(rx9));
        ctx[37] = (unsigned long)(rx10);
        (*rx9)();
        sk_r56_0040652c();
        sk_r56_00406608();
        sk_r56_004068f4();
        sk_r56_00406268();
        sk_r56_0040bb18(*((int*)((char*)l4 + 4)));
        p3 = (unsigned long *)sk_r56_00406fe0();
        ctx[38] = (unsigned long)(p3);
        *p3 = (unsigned long)(rx17);
        pair6.lo = sk_r56_00406b84(); pair6.hi = 0;  /* x1 half */
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    }
else {
        v5 = ctx[24];
        pair6.lo = sk_r56_00406894(ctx[28],ctx[30], ctx[27]); pair6.hi = 0;  /* x1 half */
        ctx[32] = (unsigned long)((unsigned long)(rx9_00));
        ctx[33] = (unsigned long)(rx10_00);
        (*rx9_00)(pair6.lo,pair6.hi,v5);
        v5 = sk_r56_004067f8();
        sk_r56_003fcc1c();
        l4 = sk_r56_004062c8();
        sk_r56_0040bb18(*((int*)((char*)l4 + 4)));
        p3 = (unsigned long *)sk_r56_00406fe0();
        ctx[34] = (unsigned long)(p3);
        *p3 = (unsigned long)(rx17_00);
        pair6.lo = sk_r56_00406b24(); pair6.hi = 0;  /* x1 half */
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16_00);
    }
    sk_r56_004076a8(pair6.lo,pair6.hi,v5,UNRECOVERED_JUMPTABLE,v2);
    /* WARNING: Could not recover jumptable at 0x003d9ab8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003d9b94 @ 0x003d9b94   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003d9b94()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    unsigned long * p5;
    long l6;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*rx8)();
    unsigned long (*rx8_00)();
    unsigned long (*rx8_01)();
    unsigned long rx8_02;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long rx10_00;
    unsigned long rx17;
    unsigned long rx17_00;
    unsigned long v7;
    long l8;
    long l9;
    unsigned long * p10;
    cL4_w16_t pair11;
    v4 = sk_r56_0040785c();
    sk_r56_00407adc();
    v7 = ctx[20];
    sk_r56_00406be4();
    if (carry) {
        l6 = ctx[18];
        ((unsigned long(*)())(ctx[28] + 8))(ctx[30],ctx[24]);
        sk_r56_003507e0(*(unsigned long *)((char*)l6 + 8));
        (*rx8)();
        sk_r56_00407764();
        (*rx8_00)();
        UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())((unsigned long(*)())ctx[24]);
        sk_r56_00350744(ctx[4] + (long)*((int*)ctx+0x15c));
        pair11.lo = sk_r56_000839d8(); pair11.hi = 0;  /* x1 half */
        sk_r56_00406fb0(ctx[31],pair11.lo,pair11.hi, *(unsigned long *)((char*)ctx + 200));
        (*rx8_01)();
        sk_r56_00406420();
        if (carry) {
            l6 = ctx[8];
            sk_r56_00353930(ctx[26],ctx[27], *(unsigned long *)((char*)ctx + 200));
            ctx[36] = (unsigned long)((unsigned long)(rx9));
            ctx[37] = (unsigned long)(rx10);
            (*rx9)();
            sk_r56_0040652c();
            sk_r56_00406608();
            sk_r56_004068f4();
            sk_r56_00406268();
            sk_r56_0040bb18(*((int*)((char*)l6 + 4)));
            p5 = (unsigned long *)sk_r56_00406fe0();
            ctx[38] = (unsigned long)(p5);
            *p5 = (unsigned long)(rx17);
            sk_r56_00406b84();
        }
    else {
            v4 = ctx[24];
            pair11.lo = sk_r56_00406894(ctx[28],ctx[30], ctx[27]); pair11.hi = 0;  /* x1 half */
            ctx[32] = (unsigned long)((unsigned long)(rx9_01));
            ctx[33] = (unsigned long)(rx10_00);
            (*rx9_01)(pair11.lo,pair11.hi,v4);
            sk_r56_004067f8();
            sk_r56_003fcc1c();
            l6 = sk_r56_004062c8();
            sk_r56_0040bb18(*((int*)((char*)l6 + 4)));
            p5 = (unsigned long *)sk_r56_00406fe0();
            ctx[34] = (unsigned long)(p5);
            *p5 = (unsigned long)(rx17_00);
            sk_r56_00406b24();
        }
        sk_r56_00408404();
        sk_r56_00407504();
        /* WARNING: Could not recover jumptable at 0x003d9e4c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l9 = (long)*((int*)ctx+0x15c);
    v1 = *(unsigned long *)((char*)ctx + 200);
    l6 = ctx[26];
    v2 = ctx[23];
    v3 = ctx[24];
    l8 = ctx[4];
    p10 = (unsigned long *)(ctx[21] + 0x20);
    UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())((unsigned long(*)())*p10);
    sk_r56_00350968(v2);
    (*UNRECOVERED_JUMPTABLE_00)();
    p5 = (unsigned long *)(l6 + 8);
    ((unsigned long(*)())(*p5))(l8 + l9,v1);
    sk_r56_00408440();
    (*rx9_00)();
    sk_r56_00350750(l8 + l9);
    sk_r56_0040764c();
    (*UNRECOVERED_JUMPTABLE_00)();
    sk_r56_0040698c();
    sk_r56_00406cf0();
    sk_r56_0040bd24(v7);
    sk_r56_0040bd24(l8);
    sk_r56_0040bd24(UNRECOVERED_JUMPTABLE_00);
    sk_r56_0040bd24(v3);
    sk_r56_0040bd24(v2);
    sk_r56_0040bd24(l9);
    sk_r56_0040bd24(p5);
    sk_r56_0040bd24(p10);
    sk_r56_0040bd24(rx8_02);
    pair11.lo = sk_r56_0040678c(); pair11.hi = 0;  /* x1 half */
    sk_r56_00407504(pair11.lo,pair11.hi,v4);
    /* WARNING: Could not recover jumptable at 0x003d9dbc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003d9f0c @ 0x003d9f0c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003d9f0c(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    int i2;
    unsigned long v3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long rx8;
    long rx8_00;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx17;
    long l6;
    cL4_w16_t pair7;
    v3 = sk_r56_00407e6c();
    sk_r56_00407924();
    v4 = sk_r56_00406420();
    if (carry) {
        i2 = *((int*)((char*)ctx + 0x158));
        l6 = ctx[4];
        sk_r56_0040711c(ctx[11],v4,ctx[10]);
        (*rx9)();
        *((unsigned char*)((char*)l6 + i2)) = 1;
        sk_r56_0040698c();
        sk_r56_0040686c();
        sk_r56_0040bd24((long)i2);
        sk_r56_0040bd24(1);
        sk_r56_0040bd24(l6);
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24(rx8);
        pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
        sk_r56_004076a8(pair7.lo,pair7.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003d9fdc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l6 = ctx[3];
    l1 = ctx[4];
    sk_r56_00406bd4(ctx[13],ctx[14]);
    (*rx9_00)();
    sk_r56_004062a8(*(unsigned long *)(l1 + *((int*)((char*)l6 + 0x34))));
    sk_r56_0040bb18(*((int*)((char*)rx8_00 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[40] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    p5[1] = (unsigned long)((unsigned long)LAB_003da07c);
    sk_r56_00408380(ctx[6],ctx[14]);
    sk_r56_004076a8();
    /* WARNING: Could not recover jumptable at 0x003da078. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003da178 @ 0x003da178   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003da178()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    unsigned long * p3;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long rx17;
    unsigned long v4;
    unsigned long v5;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    v4 = ctx[24];
    v5 = ctx[15];
    v1 = ctx[5];
    sk_r56_000a649c(v5);
    sk_r56_004081fc();
    (*rx9)();
    sk_r56_004068bc();
    sk_r56_00377bec(v5,v1,v4);
    sk_r56_003fcc1c();
    l2 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l2 + 4)));
    p3 = (unsigned long *)sk_r56_00406fe0();
    ctx[41] = (unsigned long)(p3);
    *p3 = (unsigned long)(rx17);
    p3[1] = (unsigned long)((unsigned long)LAB_003da25c);
    sk_r56_00407814(ctx[19],ctx[24]);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003da258. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003da330 @ 0x003da330   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003da330()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    unsigned long v5;
    unsigned long v6;
    unsigned long * p7;
    long l8;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*rx8)();
    unsigned long (*rx8_00)();
    unsigned long (*rx8_01)();
    unsigned long rx8_02;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx10;
    unsigned long rx10_00;
    unsigned long rx17;
    unsigned long rx17_00;
    unsigned long v9;
    unsigned long (*pcVar10)();
    long l11;
    cL4_w16_t pair12;
    v6 = sk_r56_0040785c();
    sk_r56_00407adc();
    v9 = ctx[19];
    sk_r56_00406be4();
    if (carry) {
        UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())((unsigned long(*)())ctx[36]);
        l8 = ctx[18];
        ((unsigned long(*)())(ctx[28] + 8))(ctx[29],ctx[24]);
        sk_r56_003507e0(*(unsigned long *)((char*)l8 + 8));
        (*rx8)();
        sk_r56_00408410();
        (*UNRECOVERED_JUMPTABLE_00)();
        UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())((unsigned long(*)())ctx[24]);
        sk_r56_00350744(ctx[4] + (long)*((int*)ctx+0x15c));
        pair12.lo = sk_r56_000839d8(); pair12.hi = 0;  /* x1 half */
        sk_r56_00406fb0(ctx[31],pair12.lo,pair12.hi, *(unsigned long *)((char*)ctx + 200));
        (*rx8_00)();
        sk_r56_00406420();
        if (carry) {
            l8 = ctx[8];
            sk_r56_00353930(ctx[26],ctx[27], *(unsigned long *)((char*)ctx + 200));
            ctx[36] = (unsigned long)((unsigned long)(rx9));
            ctx[37] = (unsigned long)(rx10);
            (*rx9)();
            sk_r56_0040652c();
            sk_r56_00406608();
            sk_r56_004068f4();
            sk_r56_00406268();
            sk_r56_0040bb18(*((int*)((char*)l8 + 4)));
            p7 = (unsigned long *)sk_r56_00406fe0();
            ctx[38] = (unsigned long)(p7);
            *p7 = (unsigned long)(rx17);
            sk_r56_00406b84();
        }
    else {
            v6 = ctx[24];
            pair12.lo = sk_r56_00406894(ctx[28],ctx[30], ctx[27]); pair12.hi = 0;  /* x1 half */
            ctx[32] = (unsigned long)((unsigned long)(rx9_00));
            ctx[33] = (unsigned long)(rx10_00);
            (*rx9_00)(pair12.lo,pair12.hi,v6);
            sk_r56_004067f8();
            sk_r56_003fcc1c();
            l8 = sk_r56_004062c8();
            sk_r56_0040bb18(*((int*)((char*)l8 + 4)));
            p7 = (unsigned long *)sk_r56_00406fe0();
            ctx[34] = (unsigned long)(p7);
            *p7 = (unsigned long)(rx17_00);
            sk_r56_00406b24();
        }
        sk_r56_00408404();
        sk_r56_00407504();
        /* WARNING: Could not recover jumptable at 0x003da5d8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())((unsigned long(*)())ctx[36]);
    v3 = ctx[37];
    l8 = (long)*((int*)ctx+0x15c);
    v1 = ctx[28];
    v2 = ctx[24];
    v4 = *(unsigned long *)((char*)ctx + 200);
    v5 = ctx[22];
    l11 = ctx[4];
    p7 = (unsigned long *)(ctx[21] + 0x20);
    pcVar10 = (unsigned long(*)())((unsigned long(*)())*p7);
    sk_r56_00350968(v5);
    (*pcVar10)();
    (*UNRECOVERED_JUMPTABLE_00)(v3,l11 + l8,v4);
    sk_r56_004083f0();
    (*rx8_01)();
    sk_r56_00350750(l11 + l8);
    sk_r56_0040764c();
    (*pcVar10)();
    sk_r56_0040698c();
    sk_r56_00406cf0();
    sk_r56_0040bd24(v9);
    sk_r56_0040bd24(v1);
    sk_r56_0040bd24(pcVar10);
    sk_r56_0040bd24(v2);
    sk_r56_0040bd24(v5);
    sk_r56_0040bd24(l8);
    sk_r56_0040bd24(p7);
    sk_r56_0040bd24(l11);
    sk_r56_0040bd24(rx8_02);
    pair12.lo = sk_r56_0040678c(); pair12.hi = 0;  /* x1 half */
    sk_r56_00407504(pair12.lo,pair12.hi,v6);
    /* WARNING: Could not recover jumptable at 0x003da548. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003da7f8 @ 0x003da7f8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003da7f8()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long param_1; /* Swift-ABI register param */
    unsigned long param_2; /* Swift-ABI register param */
    unsigned long param_3; /* Swift-ABI register param */
    unsigned long param_4; /* Swift-ABI register param */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    long rx1;
    long l4;
    long rx8;
    long rx8_00;
    long rx8_01;
    long rx8_02;
    long rx8_03;
    long rx8_04;
    long rx8_05;
    long rx8_06;
    unsigned long (*rx8_07)();
    unsigned long rx8_08;
    unsigned long rx8_09;
    long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    unsigned long rx16_02;
    unsigned long rx16_03;
    unsigned long rx16_04;
    unsigned long rx16_05;
    unsigned long rx16_06;
    unsigned long rx16_07;
    unsigned long v5;
    unsigned long v6;
    cL4_w16_t pair7;
    sk_r56_00408190();
    sk_r56_004070d8();
    l4 = param_4;
    sk_r56_00406f40();
    v6 = *(unsigned long *)((char*)l4 + 0x18);
    ctx[8] = (unsigned long)(v6);
    sk_r56_003509c8(v6);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx16 + 0x40));
    ctx[9] = (unsigned long)(v1);
    v5 = *(unsigned long *)((char*)param_4 + 0x20);
    ctx[10] = (unsigned long)(v5);
    ctx[11] = (unsigned long)(*(unsigned long *)((char*)param_4 + 0x10));
    sk_r56_004083d8();
    sk_r56_00350798();
    v1 = sk_r56_004085b4();
    ctx[12] = (unsigned long)(v1);
    sk_r56_000a6f88();
    ctx[13] = (unsigned long)(rx16_00);
    v2 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[14] = (unsigned long)(v2);
    sk_r56_00350798();
    v2 = sk_r56_004085b4();
    ctx[15] = (unsigned long)(v2);
    sk_r56_00352018();
    ctx[16] = (unsigned long)(rx16_01);
    v2 = sk_r56_00407b48(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[17] = (unsigned long)(v2);
    v2 = sk_r56_0040bb18(v5 & 0xfffffffffffffff0);
    ctx[18] = (unsigned long)(v2);
    v1 = sk_r56_00310d68(0,v1);
    ctx[19] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[20] = (unsigned long)(rx16_02);
    v1 = sk_r56_00407b48(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[21] = (unsigned long)(v1);
    sk_r56_0040bb18(v5 & 0xfffffffffffffff0);
    sk_r56_00408328();
    pair7.lo = sk_r56_0035050c(); pair7.hi = 0;  /* x1 half */
    v3 = sk_r56_00377824(pair7.lo,pair7.hi,v6);
    ctx[24] = (unsigned long)(v3);
    sk_r56_000a6f88();
    *(unsigned long *)((char*)ctx + 200) = (unsigned long)(rx16_03);
    v5 = *(unsigned long *)((char*)rx8_02 + 0x40) + 0xf;
    v1 = sk_r56_0040bb18(v5 & 0xfffffffffffffff0);
    ctx[26] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v5 & 0xfffffffffffffff0);
    ctx[27] = (unsigned long)(v1);
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[28] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[29] = (unsigned long)(rx16_04);
    v1 = sk_r56_00407b48(*(unsigned long *)((char*)rx8_03 + 0x40));
    ctx[30] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v3 & 0xfffffffffffffff0);
    ctx[31] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v3 & 0xfffffffffffffff0);
    ctx[32] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v3 & 0xfffffffffffffff0);
    ctx[33] = (unsigned long)(v1);
    sk_r56_0035050c();
    v1 = sk_r56_00377824();
    ctx[34] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[35] = (unsigned long)(rx16_05);
    v1 = sk_r56_00407b48(*(unsigned long *)((char*)rx8_04 + 0x40));
    ctx[36] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v3 & 0xfffffffffffffff0);
    ctx[37] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v3 & 0xfffffffffffffff0);
    ctx[38] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v3 & 0xfffffffffffffff0);
    ctx[39] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v3 & 0xfffffffffffffff0);
    ctx[40] = (unsigned long)(v1);
    sk_r56_004083c0();
    sk_r56_003510a0();
    v5 = sk_r56_00377824();
    ctx[41] = (unsigned long)(v5);
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[42] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[43] = (unsigned long)(rx16_06);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_05 + 0x40));
    ctx[44] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[45] = (unsigned long)(rx16_07);
    v1 = sk_r56_00407b48(*(unsigned long *)((char*)rx8_06 + 0x40));
    ctx[46] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(v5 & 0xfffffffffffffff0);
    ctx[47] = (unsigned long)(v1);
    if (rx1 == 0) {
        sk_r56_00407248();
        v1 = rx8_09;
    }
else {
        sk_r56_00407374(param_3);
        sk_r56_00084180();
        (*rx8_07)();
        sk_r56_0008e1ec();
        v1 = rx8_08;
    }
    ctx[48] = (unsigned long)(v1);
    ctx[49] = (unsigned long)(v6);
    sk_r56_00353080();
    sk_r56_00408178();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003dab54 @ 0x003dab54   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dab54()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    int i1;
    unsigned long v2;
    unsigned long * p3;
    long l4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx10;
    unsigned long rx10_00;
    unsigned long (*rx11)();
    unsigned long (*rx16)();
    unsigned long (*rx16_00)();
    unsigned long rx17;
    unsigned long rx17_00;
    cL4_w16_t pair5;
    unsigned long in_stack_00000000;
    unsigned long in_stack_00000008;
    unsigned long in_stack_00000010;
    unsigned long in_stack_00000018;
    unsigned long in_stack_00000020;
    unsigned long in_stack_00000028;
    unsigned long in_stack_00000030;
    unsigned long in_stack_00000038;
    unsigned long in_stack_00000040;
    unsigned long in_stack_00000048;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    v2 = sk_r56_00407840();
    pair5.lo = sk_r56_00407ad0(); pair5.hi = 0;  /* x1 half */
    i1 = *((int*)((char*)ctx[5] + 0x3c));
    *((int*)ctx+0x1e8) = i1;
    if ((*((unsigned char*)((char*)ctx[6] + i1)) & 1) != 0) {
        sk_r56_00406624();
        sk_r56_00350744();
        sk_r56_000839d8();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24(in_stack_00000000);
        sk_r56_0040bd24(in_stack_00000008);
        sk_r56_0040bd24(in_stack_00000010);
        sk_r56_0040bd24(in_stack_00000018);
        sk_r56_0040bd24(in_stack_00000020);
        sk_r56_0040bd24(in_stack_00000028);
        sk_r56_0040bd24(in_stack_00000030);
        sk_r56_0040bd24(in_stack_00000038);
        sk_r56_0040bd24(in_stack_00000040);
        sk_r56_0040bd24(in_stack_00000048);
        sk_r56_0040bd24(UNRECOVERED_JUMPTABLE);
        pair5.lo = sk_r56_0040678c(); pair5.hi = 0;  /* x1 half */
        sk_r56_004074e8(pair5.lo,pair5.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003dac5c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    *((int*)((char*)ctx + 0x1ec)) = *((int*)((char*)ctx[5] + 0x38));
    *(unsigned long *)((char*)ctx + 400) = (unsigned long)(*(unsigned long *)((char*)ctx[43] + 0x10));
    sk_r56_00408460(pair5.lo,pair5.hi,ctx[42]);
    (*rx11)();
    sk_r56_00406420();
    if (carry) {
        l4 = ctx[11];
        sk_r56_00353930(ctx[43],ctx[44], ctx[42]);
        ctx[54] = (unsigned long)((unsigned long)(rx9));
        ctx[55] = (unsigned long)(rx10);
        (*rx9)();
        sk_r56_0040652c();
        v2 = sk_r56_00406608();
        ctx[56] = (unsigned long)(v2);
        v2 = sk_r56_00406e8c();
        ctx[57] = (unsigned long)(v2);
        sk_r56_00406288();
        sk_r56_0040bb18(*((int*)((char*)l4 + 4)));
        p3 = (unsigned long *)sk_r56_00406fe0();
        ctx[58] = (unsigned long)(p3);
        *p3 = (unsigned long)(rx17);
        p3[1] = (unsigned long)((unsigned long)LAB_003db214);
        sk_r56_004067b8(ctx[22]);
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    }
else {
        v2 = ctx[41];
        pair5.lo = sk_r56_00406894(ctx[45],ctx[47], ctx[44]); pair5.hi = 0;  /* x1 half */
        ctx[51] = (unsigned long)((unsigned long)(rx9_00));
        ctx[52] = (unsigned long)(rx10_00);
        (*rx9_00)(pair5.lo,pair5.hi,v2);
        sk_r56_004067f8();
        sk_r56_003fcc4c();
        l4 = sk_r56_00406374();
        sk_r56_0040bb18(*((int*)((char*)l4 + 4)));
        p3 = (unsigned long *)sk_r56_00406fe0();
        ctx[53] = (unsigned long)(p3);
        *p3 = (unsigned long)(rx17_00);
        sk_r56_00406a5c();
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16_00);
    }
    sk_r56_004074e8();
    /* WARNING: Could not recover jumptable at 0x003dadbc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dae98 @ 0x003dae98   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dae98()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*pcVar1)();
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    unsigned long v5;
    unsigned long * p6;
    long l7;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx8)();
    unsigned long (*rx8_00)();
    unsigned long (*rx8_01)();
    unsigned long v8;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long v9;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long rx10_00;
    unsigned long (*rx16)();
    unsigned long (*rx16_00)();
    unsigned long rx17;
    unsigned long rx17_00;
    unsigned long (*pcVar10)();
    unsigned long v11;
    unsigned long v12;
    long l13;
    unsigned long * p14;
    long l15;
    cL4_w16_t pair16;
    unsigned long in_stack_00000000;
    unsigned long in_stack_00000008;
    unsigned long in_stack_00000010;
    unsigned long in_stack_00000018;
    unsigned long in_stack_00000020;
    unsigned long in_stack_00000028;
    unsigned long in_stack_00000030;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    v4 = sk_r56_00407840();
    v5 = sk_r56_00407ad0();
    sk_r56_0040833c(ctx[29],v5,ctx[33], ctx[28]);
    (*rx9)();
    sk_r56_00406420();
    if (carry) {
        l7 = ctx[29];
        ((unsigned long(*)())(ctx[45] + 8))(ctx[47],ctx[41]);
        sk_r56_003507e0(*(unsigned long *)((char*)l7 + 8));
        (*rx8)();
        sk_r56_00407764();
        (*rx8_00)();
        sk_r56_00350744(ctx[6] + (long)*((int*)ctx+0x1ec));
        pair16.lo = sk_r56_000839d8(); pair16.hi = 0;  /* x1 half */
        sk_r56_00406fb0(*(unsigned long *)((char*)ctx + 400),pair16.lo,pair16.hi, ctx[42]);
        (*rx8_01)();
        sk_r56_00406420();
        if (carry) {
            l7 = ctx[11];
            sk_r56_00353930(ctx[43],ctx[44], ctx[42]);
            ctx[54] = (unsigned long)((unsigned long)(rx9_00));
            ctx[55] = (unsigned long)(rx10);
            (*rx9_00)();
            sk_r56_0040652c();
            v4 = sk_r56_00406608();
            ctx[56] = (unsigned long)(v4);
            v4 = sk_r56_00406e8c();
            ctx[57] = (unsigned long)(v4);
            sk_r56_00406288();
            sk_r56_0040bb18(*((int*)((char*)l7 + 4)));
            p6 = (unsigned long *)sk_r56_00406fe0();
            ctx[58] = (unsigned long)(p6);
            *p6 = (unsigned long)(rx17);
            p6[1] = (unsigned long)((unsigned long)LAB_003db214);
            sk_r56_004067b8(ctx[22]);
            UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())(rx16);
        }
    else {
            v4 = ctx[41];
            pair16.lo = sk_r56_00406894(ctx[45],ctx[47], ctx[44]); pair16.hi = 0;  /* x1 half */
            ctx[51] = (unsigned long)((unsigned long)(rx9_01));
            ctx[52] = (unsigned long)(rx10_00);
            (*rx9_01)(pair16.lo,pair16.hi,v4);
            sk_r56_004067f8();
            sk_r56_003fcc4c();
            l7 = sk_r56_00406374();
            sk_r56_0040bb18(*((int*)((char*)l7 + 4)));
            p6 = (unsigned long *)sk_r56_00406fe0();
            ctx[53] = (unsigned long)(p6);
            *p6 = (unsigned long)(rx17_00);
            sk_r56_00406a5c();
            UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())(rx16_00);
        }
        sk_r56_004074e8();
        /* WARNING: Could not recover jumptable at 0x003db210. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    pcVar1 = (unsigned long(*)())((unsigned long(*)())ctx[51]);
    v3 = ctx[52];
    l15 = (long)*((int*)ctx+0x1ec);
    v9 = ctx[47];
    v5 = ctx[42];
    l7 = ctx[43];
    v11 = ctx[41];
    v12 = ctx[27];
    v2 = ctx[24];
    l13 = ctx[6];
    v8 = ctx[2];
    p14 = (unsigned long *)(*(unsigned long *)((char*)ctx + 200) + 0x20);
    pcVar10 = (unsigned long(*)())((unsigned long(*)())*p14);
    (*pcVar10)(v12,ctx[32],v2);
    p6 = (unsigned long *)(l7 + 8);
    ((unsigned long(*)())(*p6))(l13 + l15,v5);
    (*pcVar1)(v3,l13 + l15,v9,v11);
    sk_r56_00350750(l13 + l15);
    sk_r56_000839d8();
    sk_r56_003513b4(v8);
    (*pcVar10)();
    sk_r56_00406624();
    sk_r56_00350750();
    sk_r56_000839d8();
    sk_r56_0040bd24(v5);
    sk_r56_0040bd24(v11);
    sk_r56_0040bd24(v12);
    sk_r56_0040bd24(v2);
    sk_r56_0040bd24(l13);
    sk_r56_0040bd24(p6);
    sk_r56_0040bd24(p14);
    sk_r56_0040bd24(l15);
    sk_r56_0040bd24(pcVar10);
    sk_r56_0040bd24(in_stack_00000000);
    sk_r56_0040bd24(in_stack_00000008);
    sk_r56_0040bd24(in_stack_00000010);
    sk_r56_0040bd24(in_stack_00000018);
    sk_r56_0040bd24(in_stack_00000020);
    sk_r56_0040bd24(in_stack_00000028);
    sk_r56_0040bd24(in_stack_00000030);
    sk_r56_0040bd24(v9);
    sk_r56_0040bd24(v8);
    sk_r56_0040bd24(pcVar1);
    sk_r56_0040bd24(v3);
    pair16.lo = sk_r56_0040678c(); pair16.hi = 0;  /* x1 half */
    sk_r56_004074e8(pair16.lo,pair16.hi,v4);
    /* WARNING: Could not recover jumptable at 0x003db17c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003db300 @ 0x003db300   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003db300()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    int i1;
    unsigned long v2;
    unsigned long v3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*rx16)();
    unsigned long rx17;
    unsigned long v5;
    long l6;
    long l7;
    cL4_w16_t pair8;
    unsigned long in_stack_00000000;
    unsigned long in_stack_00000008;
    unsigned long in_stack_00000010;
    unsigned long in_stack_00000018;
    unsigned long in_stack_00000020;
    unsigned long in_stack_00000028;
    unsigned long in_stack_00000030;
    unsigned long in_stack_00000038;
    unsigned long in_stack_00000040;
    unsigned long in_stack_00000048;
    unsigned long in_stack_00000050;
    v2 = sk_r56_00407840();
    v3 = sk_r56_00407ad0();
    v5 = ctx[12];
    sk_r56_0040833c(ctx[20],v3,ctx[22], ctx[19]);
    (*rx9)();
    pair8.lo = sk_r56_00351d24(); pair8.hi = 0;  /* x1 half */
    i1 = sk_r56_000839f8(pair8.lo,pair8.hi,v5);
    l7 = ctx[6];
    if (i1 == 1) {
        i1 = *((int*)ctx+0x1e8);
        ((unsigned long(*)())(ctx[20] + 8))(ctx[21],ctx[19]);
        *((unsigned char*)((char*)l7 + i1)) = 1;
        sk_r56_00406624();
        sk_r56_00350744();
        sk_r56_000839d8();
        sk_r56_0040bd24((long)i1);
        sk_r56_0040bd24(1);
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24(l7);
        sk_r56_0040bd24(in_stack_00000000);
        sk_r56_0040bd24(in_stack_00000008);
        sk_r56_0040bd24(in_stack_00000010);
        sk_r56_0040bd24(in_stack_00000018);
        sk_r56_0040bd24(in_stack_00000020);
        sk_r56_0040bd24(in_stack_00000028);
        sk_r56_0040bd24(in_stack_00000030);
        sk_r56_0040bd24(in_stack_00000038);
        sk_r56_0040bd24(in_stack_00000040);
        sk_r56_0040bd24(in_stack_00000048);
        sk_r56_0040bd24(in_stack_00000050);
        pair8.lo = sk_r56_0040678c(); pair8.hi = 0;  /* x1 half */
        sk_r56_004074e8(pair8.lo,pair8.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003db44c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l6 = ctx[5];
    ((unsigned long(*)())(ctx[13] + 0x20))(ctx[14],ctx[21], ctx[12]);
    sk_r56_004062a8(*(unsigned long *)(l7 + *((int*)((char*)l6 + 0x34))));
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p4 = (unsigned long *)sk_r56_00406fe0();
    ctx[59] = (unsigned long)(p4);
    *p4 = (unsigned long)(rx17);
    p4[1] = (unsigned long)((unsigned long)LAB_003db4f8);
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_004074e8(ctx[9],ctx[14],rx16, v2);
    /* WARNING: Could not recover jumptable at 0x003db4f4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003db61c @ 0x003db61c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003db61c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    unsigned long * p3;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long rx17;
    unsigned long v4;
    unsigned long v5;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    v4 = ctx[41];
    v5 = ctx[23];
    v1 = ctx[8];
    sk_r56_000a649c(v5);
    sk_r56_004081fc();
    (*rx9)();
    sk_r56_004068bc();
    sk_r56_00377bec(v5,v1,v4);
    sk_r56_003fcc4c();
    l2 = sk_r56_00406374();
    sk_r56_0040bb18(*((int*)((char*)l2 + 4)));
    p3 = (unsigned long *)sk_r56_00406fe0();
    ctx[60] = (unsigned long)(p3);
    *p3 = (unsigned long)(rx17);
    p3[1] = (unsigned long)((unsigned long)LAB_003db70c);
    sk_r56_00407990(ctx[31],ctx[3], ctx[4],ctx[37], ctx[41]);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003db708. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003db7e0 @ 0x003db7e0   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003db7e0()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*pcVar1)();
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    unsigned long v5;
    unsigned long v6;
    unsigned long v7;
    unsigned long * p8;
    long l9;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx8)();
    unsigned long (*rx8_00)();
    unsigned long v10;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long rx10_00;
    unsigned long (*rx16)();
    unsigned long (*rx16_00)();
    unsigned long rx17;
    unsigned long rx17_00;
    unsigned long v11;
    unsigned long * p12;
    long l13;
    unsigned long (*pcVar14)();
    long l15;
    cL4_w16_t pair16;
    unsigned long in_stack_00000000;
    unsigned long in_stack_00000008;
    unsigned long in_stack_00000010;
    unsigned long in_stack_00000018;
    unsigned long in_stack_00000020;
    unsigned long in_stack_00000028;
    unsigned long in_stack_00000030;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    v6 = sk_r56_00407840();
    v7 = sk_r56_00407ad0();
    sk_r56_0040833c(ctx[29],v7,ctx[31], ctx[28]);
    (*rx9)();
    sk_r56_00406420();
    if (carry) {
        pcVar1 = (unsigned long(*)())((unsigned long(*)())ctx[54]);
        l9 = ctx[29];
        ((unsigned long(*)())(ctx[45] + 8))(ctx[46],ctx[41]);
        sk_r56_003507e0(*(unsigned long *)((char*)l9 + 8));
        (*rx8)();
        sk_r56_00408410();
        (*pcVar1)();
        sk_r56_00350744(ctx[6] + (long)*((int*)ctx+0x1ec));
        pair16.lo = sk_r56_000839d8(); pair16.hi = 0;  /* x1 half */
        sk_r56_00406fb0(*(unsigned long *)((char*)ctx + 400),pair16.lo,pair16.hi, ctx[42]);
        (*rx8_00)();
        sk_r56_00406420();
        if (carry) {
            l9 = ctx[11];
            sk_r56_00353930(ctx[43],ctx[44], ctx[42]);
            ctx[54] = (unsigned long)((unsigned long)(rx9_00));
            ctx[55] = (unsigned long)(rx10);
            (*rx9_00)();
            sk_r56_0040652c();
            v6 = sk_r56_00406608();
            ctx[56] = (unsigned long)(v6);
            v6 = sk_r56_00406e8c();
            ctx[57] = (unsigned long)(v6);
            sk_r56_00406288();
            sk_r56_0040bb18(*((int*)((char*)l9 + 4)));
            p8 = (unsigned long *)sk_r56_00406fe0();
            ctx[58] = (unsigned long)(p8);
            *p8 = (unsigned long)(rx17);
            p8[1] = (unsigned long)((unsigned long)LAB_003db214);
            sk_r56_004067b8(ctx[22]);
            UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())(rx16);
        }
    else {
            v6 = ctx[41];
            pair16.lo = sk_r56_00406894(ctx[45],ctx[47], ctx[44]); pair16.hi = 0;  /* x1 half */
            ctx[51] = (unsigned long)((unsigned long)(rx9_01));
            ctx[52] = (unsigned long)(rx10_00);
            (*rx9_01)(pair16.lo,pair16.hi,v6);
            sk_r56_004067f8();
            sk_r56_003fcc4c();
            l9 = sk_r56_00406374();
            sk_r56_0040bb18(*((int*)((char*)l9 + 4)));
            p8 = (unsigned long *)sk_r56_00406fe0();
            ctx[53] = (unsigned long)(p8);
            *p8 = (unsigned long)(rx17_00);
            sk_r56_00406a5c();
            UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())(rx16_00);
        }
        sk_r56_004074e8();
        /* WARNING: Could not recover jumptable at 0x003dbb48. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    pcVar1 = (unsigned long(*)())((unsigned long(*)())ctx[54]);
    v2 = ctx[55];
    l15 = (long)*((int*)ctx+0x1ec);
    l9 = ctx[45];
    v3 = ctx[46];
    v7 = ctx[41];
    v4 = ctx[42];
    v5 = ctx[26];
    v11 = ctx[24];
    l13 = ctx[6];
    v10 = ctx[2];
    p8 = (unsigned long *)(*(unsigned long *)((char*)ctx + 200) + 0x20);
    pcVar14 = (unsigned long(*)())((unsigned long(*)())*p8);
    (*pcVar14)(v5,ctx[30],v11);
    (*pcVar1)(v2,l13 + l15,v4);
    p12 = (unsigned long *)(l9 + 0x20);
    ((unsigned long(*)())(*p12))(l13 + l15,v3,v7);
    sk_r56_00350750(l13 + l15);
    sk_r56_000839d8();
    sk_r56_003513b4(v10);
    (*pcVar14)();
    sk_r56_00406624();
    sk_r56_00350750();
    sk_r56_000839d8();
    sk_r56_0040bd24(v4);
    sk_r56_0040bd24(v7);
    sk_r56_0040bd24(v5);
    sk_r56_0040bd24(v11);
    sk_r56_0040bd24(p12);
    sk_r56_0040bd24(l13);
    sk_r56_0040bd24(pcVar14);
    sk_r56_0040bd24(l15);
    sk_r56_0040bd24(p8);
    sk_r56_0040bd24(in_stack_00000000);
    sk_r56_0040bd24(in_stack_00000008);
    sk_r56_0040bd24(in_stack_00000010);
    sk_r56_0040bd24(in_stack_00000018);
    sk_r56_0040bd24(in_stack_00000020);
    sk_r56_0040bd24(in_stack_00000028);
    sk_r56_0040bd24(in_stack_00000030);
    sk_r56_0040bd24(pcVar1);
    sk_r56_0040bd24(v2);
    sk_r56_0040bd24(v3);
    sk_r56_0040bd24(v10);
    pair16.lo = sk_r56_0040678c(); pair16.hi = 0;  /* x1 half */
    sk_r56_004074e8(pair16.lo,pair16.hi,v6);
    /* WARNING: Could not recover jumptable at 0x003dbab4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dc01c @ 0x003dc01c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dc01c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, long param_5)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    long * pl3;
    ctx[2] = (unsigned long)(param_4);
    l1 = sk_r56_00377824(0,*(unsigned long *)((char*)param_5 + 0x20),*(unsigned long *)((char*)param_5 + 0x10), (unsigned long)DAT_00614a5c,(unsigned long)LAB_00614a7c);
    ctx[3] = (unsigned long)(l1);
    l1 = *(unsigned long *)((char*)l1 + -8);
    ctx[4] = (unsigned long)(l1);
    v2 = sk_r56_0040bb18(*(unsigned long *)((char*)l1 + 0x40) + 0xfU & 0xfffffffffffffff0);
    ctx[5] = (unsigned long)(v2);
    pl3 = (long *)sk_r56_0040bb18(DAT_0059ffbc);
    ctx[6] = (unsigned long)(pl3);
    *pl3 = (unsigned long)(ctx);
    pl3[1] = (unsigned long)((long)(unsigned long)DAT_00405fdc);
    sk_r56_003da7f8(pl3,param_1,param_2,param_3,param_5,v2);
    return;
}


/* sk_r56_003dc158 @ 0x003dc158   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dc158(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long * p2;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    cL4_w16_t pair3;
    sk_r56_00407ca0();
    sk_r56_0040700c();
    pair3.lo = sk_r56_00352700(); pair3.hi = 0;  /* x1 half */
    ctx[6] = (unsigned long)(param_5);
    ctx[7] = (unsigned long)(param_6);
    ctx[4] = (unsigned long)(param_3);
    ctx[5] = (unsigned long)(param_4);
    ctx[3] = (unsigned long)(pair3.hi);
    sk_r56_003fcc1c(param_5);
    l1 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
    p2 = (unsigned long *)sk_r56_00406fe0();
    ctx[8] = (unsigned long)(p2);
    *p2 = (unsigned long)(rx17);
    p2[1] = (unsigned long)((unsigned long)LAB_003dc214);
    sk_r56_00406ab4(pair3.lo);
    /* WARNING: Could not recover jumptable at 0x003dc210. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dc32c @ 0x003dc32c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dc32c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long v4;
    cL4_w16_t pair5;
    v2 = sk_r56_004079cc();
    sk_r56_004070d8();
    v1 = ctx[7];
    v4 = ctx[5];
    ctx[2] = (unsigned long)(ctx[9]);
    sk_r56_0034a210();
    sk_r56_00002534();
    pair5.lo = sk_r56_003504e8(); pair5.hi = 0;  /* x1 half */
    v4 = sk_r56_00377824(pair5.lo,pair5.hi,v4,(unsigned long)DAT_00614890);
    sk_r56_003513b4(v1);
    sk_r56_00365b6c();
    pair5.lo = sk_r56_003507e0(); pair5.hi = 0;  /* x1 half */
    v3 = sk_r56_00377bec(pair5.lo,pair5.hi,v4,(unsigned long)DAT_00614890);
    sk_r56_003698b0(v1,v4,v3);
    pair5.lo = sk_r56_00406a94(); pair5.hi = 0;  /* x1 half */
    sk_r56_004078f4(pair5.lo,pair5.hi,v2);
    /* WARNING: Could not recover jumptable at 0x003dc3ec. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dc6a0 @ 0x003dc6a0   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dc6a0()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long * p1;
    unsigned long v2;
    long l3;
    unsigned long in_x5;
    long rx8;
    long rx16;
    unsigned long (*r19)();
    unsigned long r23;
    unsigned long r24;
    unsigned long r30;
    sk_r56_00084220();
    sk_r56_00407484();
    sk_r56_00407ab8();
    v2 = sk_r56_0040654c();
    sk_r56_00377824(v2,in_x5);
    sk_r56_00349530();
    ((unsigned long(*)())(rx16 + 0x20))(rx8);
    sk_r56_0034d004(0);
    l3 = (*r19)();
    p1 = (unsigned long *)(rx8 + *((int*)((char*)l3 + 0x2c)));
    *p1 = (unsigned long)(r24);
    p1[1] = (unsigned long)(r23);
    sk_r56_00084234(r30);
    return;
}


/* sk_r56_003dc724 @ 0x003dc724   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dc724()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    int * pi3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long rx16;
    unsigned long rx17;
    unsigned long r20;
    unsigned long v5;
    cL4_w16_t pair6;
    sk_r56_0040790c();
    pair6.lo = sk_r56_004070d8(); pair6.hi = 0;  /* x1 half */
    ctx[3] = (unsigned long)(pair6.hi);
    ctx[4] = (unsigned long)(r20);
    ctx[2] = (unsigned long)(pair6.lo);
    v5 = *(unsigned long *)(pair6.hi + 0x20);
    sk_r56_00350bfc(0xff,v5);
    l1 = sk_r56_00377824();
    ctx[5] = (unsigned long)(l1);
    sk_r56_00350720();
    v2 = sk_r56_00310d68();
    ctx[6] = (unsigned long)(v2);
    sk_r56_00352018();
    ctx[7] = (unsigned long)(rx16);
    v2 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[8] = (unsigned long)(v2);
    l1 = *(unsigned long *)((char*)l1 + -8);
    ctx[9] = (unsigned long)(l1);
    v2 = sk_r56_004078e8(*(unsigned long *)((char*)l1 + 0x40));
    ctx[10] = (unsigned long)(v2);
    sk_r56_00350bfc(0xff,v5);
    sk_r56_00377824();
    sk_r56_0035136c(v5);
    sk_r56_00377bec();
    pi3 = (int *)sk_r56_003fcc1c();
    sk_r56_00350720();
    sk_r56_00377dcc();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())((long)pi3 + (long)*pi3));
    sk_r56_0040bb18(pi3[1]);
    p4 = (unsigned long *)sk_r56_00406fe0();
    ctx[11] = (unsigned long)(p4);
    *p4 = (unsigned long)(rx17);
    sk_r56_00407d90();
    sk_r56_003510a0();
    sk_r56_004080cc();
    /* WARNING: Could not recover jumptable at 0x003dc8bc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dc97c @ 0x003dc97c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dc97c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    long l2;
    unsigned long v3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    unsigned long v6;
    cL4_w16_t pair7;
    v3 = sk_r56_00407ca0();
    sk_r56_0040700c();
    v6 = ctx[5];
    v4 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[7],v4,ctx[6]);
        (*rx9)();
        sk_r56_00407954();
        sk_r56_00408374();
        sk_r56_00406c5c();
        sk_r56_0040bd24(v6);
        pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair7.lo,pair7.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003dc9fc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[3];
    l2 = ctx[4];
    sk_r56_00406bd4(ctx[9],ctx[10]);
    (*rx9_00)();
    sk_r56_004062a8(*(unsigned long *)(l2 + *((int*)((char*)l1 + 0x2c))));
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[13] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    p5[1] = (unsigned long)((unsigned long)LAB_003dca9c);
    sk_r56_00407610(p5,ctx[10]);
    /* WARNING: Could not recover jumptable at 0x003dca98. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dcb98 @ 0x003dcb98   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dcb98()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    sk_r56_00407000();
    sk_r56_00407954();
    sk_r56_00408374();
    sk_r56_00406ee4();
    sk_r56_0040bd24();
    sk_r56_0040678c();
    /* WARNING: Could not recover jumptable at 0x003dcbec. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dcc4c @ 0x003dcc4c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dcc4c()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    unsigned long v3;
    int * pi4;
    unsigned long * p5;
    long in_x3;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    long rx8_00;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx17;
    unsigned long v6;
    cL4_w16_t pair7;
    sk_r56_00407e6c();
    sk_r56_00407924();
    sk_r56_00406cc8();
    v6 = *(unsigned long *)((char*)in_x3 + 0x20);
    sk_r56_0035050c();
    sk_r56_00351cd0();
    v1 = sk_r56_00377824();
    ctx[8] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[9] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[10] = (unsigned long)(v1);
    sk_r56_00351cd0(0xff,v6);
    l2 = sk_r56_00377824();
    ctx[11] = (unsigned long)(l2);
    v1 = sk_r56_00310d68(0,l2);
    ctx[12] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[13] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[14] = (unsigned long)(v1);
    l2 = *(unsigned long *)((char*)l2 + -8);
    ctx[15] = (unsigned long)(l2);
    v3 = sk_r56_004078e8(*(unsigned long *)((char*)l2 + 0x40));
    ctx[16] = (unsigned long)(v3);
    sk_r56_00351cd0(0xff,v6);
    v3 = sk_r56_00377824();
    pair7.lo = sk_r56_000dbd0c(); pair7.hi = 0;  /* x1 half */
    sk_r56_00377bec(pair7.lo,pair7.hi,v3,(unsigned long)DAT_00614a5c);
    pi4 = (int *)sk_r56_003fcc4c();
    sk_r56_00377dcc(0,v3);
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())((long)pi4 + (long)*pi4));
    sk_r56_0040bb18(pi4[1]);
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[17] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    p5[1] = (unsigned long)((unsigned long)LAB_003dce40);
    sk_r56_00406ab4(v1);
    sk_r56_004076a8();
    /* WARNING: Could not recover jumptable at 0x003dce3c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dcf90 @ 0x003dcf90   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dcf90()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    long l2;
    unsigned long v3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    unsigned long v6;
    cL4_w16_t pair7;
    v3 = sk_r56_00407ca0();
    sk_r56_0040700c();
    v6 = ctx[11];
    v4 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[13],v4,ctx[12]);
        (*rx9)();
        sk_r56_004077a0();
        sk_r56_004077cc();
        sk_r56_00406c5c();
        sk_r56_0040bd24(v6);
        sk_r56_0040bd24();
        pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair7.lo,pair7.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003dd018. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[5];
    l2 = ctx[6];
    sk_r56_00406bd4(ctx[15],ctx[16]);
    (*rx9_00)();
    sk_r56_004062a8(*(unsigned long *)(l2 + *((int*)((char*)l1 + 0x2c))));
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[20] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    p5[1] = (unsigned long)((unsigned long)LAB_003dd0b8);
    sk_r56_00407610(p5,ctx[16]);
    /* WARNING: Could not recover jumptable at 0x003dd0b4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dd1dc @ 0x003dd1dc   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd1dc()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    sk_r56_00406fd4();
    sk_r56_004077a0();
    sk_r56_004077cc();
    sk_r56_00406ee4();
    sk_r56_0040bd24();
    sk_r56_0040bd24();
    sk_r56_0040678c();
    /* WARNING: Could not recover jumptable at 0x003dd240. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dd2e0 @ 0x003dd2e0   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd2e0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, long param_5)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    long * pl3;
    ctx[2] = (unsigned long)(param_4);
    l1 = sk_r56_00377824(0,*(unsigned long *)((char*)param_5 + 0x20),*(unsigned long *)((char*)param_5 + 0x10), (unsigned long)DAT_00614a5c,(unsigned long)LAB_00614a7c);
    ctx[3] = (unsigned long)(l1);
    l1 = *(unsigned long *)((char*)l1 + -8);
    ctx[4] = (unsigned long)(l1);
    v2 = sk_r56_0040bb18(*(unsigned long *)((char*)l1 + 0x40) + 0xfU & 0xfffffffffffffff0);
    ctx[5] = (unsigned long)(v2);
    pl3 = (long *)sk_r56_0040bb18(DAT_0059ffe4);
    ctx[6] = (unsigned long)(pl3);
    *pl3 = (unsigned long)(ctx);
    pl3[1] = (unsigned long)((long)(unsigned long)DAT_00405fdc);
    sk_r56_003dcc4c(pl3,param_1,param_2,param_3,param_5,v2);
    return;
}


/* sk_r56_003dd418 @ 0x003dd418   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd418()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*rx9)();
    unsigned long (*r19)();
    long r21;
    unsigned long r30;
    sk_r56_00084220();
    sk_r56_0008409c();
    sk_r56_0040654c();
    sk_r56_003513b4();
    sk_r56_00377824();
    sk_r56_00351f10();
    sk_r56_0007c1a4();
    (DAT_00658c80)();
    sk_r56_0034b05c();
    sk_r56_00407100();
    sk_r56_00350518();
    (*rx9)();
    sk_r56_004082a8((long)*((int*)((char*)r21 + 0x2c)));
    sk_r56_00407700();
    (*r19)();
    sk_r56_00084234(r30);
    return;
}


/* sk_r56_003dd4c0 @ 0x003dd4c0   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd4c0(long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    if (-1 < param_1) {
        sk_r56_0035a7e8(param_1,param_2,param_2,param_3);
        sk_r56_003dd540();
        return;
    }
    sk_r56_0035ac70((unsigned long)sk_neg_number_str);
    sk_r56_00406aa4();
    sk_r56_0040697c();
    /* WARNING: Subroutine does not return */ sk_r56_001afa84();
}


/* sk_r56_003dd540 @ 0x003dd540   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd540()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long param_1; /* Swift-ABI register param */
    unsigned long param_2; /* Swift-ABI register param */
    unsigned long param_3; /* Swift-ABI register param */
    long l1;
    long rx8;
    long rx16;
    unsigned long (*r19)();
    cL4_w16_t pair2;
    pair2.lo = sk_r56_00351da8(); pair2.hi = 0;  /* x1 half */
    sk_r56_003509c8(param_3,pair2.lo,pair2.lo);
    ((unsigned long(*)())(rx16 + 0x20))(rx8);
    sk_r56_00350548(0);
    l1 = (*r19)();
    *(long *)(rx8 + *((int*)((char*)l1 + 0x24))) = pair2.hi;
    return;
}


/* sk_r56_003dd5d0 @ 0x003dd5d0   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd5d0()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    long rx16;
    unsigned long (*r19)();
    long r24;
    sk_r56_0040679c();
    sk_r56_0040654c();
    sk_r56_00377824();
    sk_r56_00349530();
    ((unsigned long(*)())(rx16 + 0x20))();
    sk_r56_00350548(0);
    l1 = (*r19)();
    *(unsigned long *)((char*)r24 + *((int*)((char*)l1 + 0x24))) = (unsigned long)(ctx);
    return;
}


/* sk_r56_003dd660 @ 0x003dd660   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd660()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long l5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long rx17;
    unsigned long v6;
    cL4_w16_t pair7;
    v2 = sk_r56_00407ca0();
    v3 = sk_r56_0040700c();
    l1 = ctx[3];
    l5 = *(long *)(ctx[4] + (long)*((int*)((char*)l1 + 0x24)));
    if (l5 != 0) {
        *(long *)(ctx[4] + (long)*((int*)((char*)l1 + 0x24))) = l5 + -1;
        l1 = *(unsigned long *)((char*)l1 + 0x18);
        sk_r56_00406560();
        sk_r56_00350624();
        sk_r56_00377824();
        sk_r56_0007c1c4();
        sk_r56_00351584();
        sk_r56_00377bec();
        sk_r56_004068f4();
        sk_r56_00406268();
        sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
        p4 = (unsigned long *)sk_r56_00406fe0();
        ctx[5] = (unsigned long)(p4);
        *p4 = (unsigned long)(rx17);
        sk_r56_004071c0();
        sk_r56_00406ab4();
        /* WARNING: Could not recover jumptable at 0x003dd740. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    v6 = ctx[2];
    sk_r56_00406ce0(v3,*(unsigned long *)((char*)l1 + 0x18),*(unsigned long *)((char*)l1 + 0x10));
    sk_r56_00377824(0);
    sk_r56_00350744(v6);
    sk_r56_000839d8();
    pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
    sk_r56_00407e58(pair7.lo,pair7.hi,v2);
    /* WARNING: Could not recover jumptable at 0x003dd788. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dd840 @ 0x003dd840   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd840()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    long in_x3;
    long rx8;
    unsigned long (*rx8_00)();
    unsigned long rx8_01;
    unsigned long rx8_02;
    unsigned long rx16;
    long r21;
    sk_r56_00406fd4();
    sk_r56_00406cc8();
    ctx[8] = (unsigned long)(*(unsigned long *)((char*)in_x3 + 0x18));
    v2 = *(unsigned long *)((char*)in_x3 + 0x10);
    ctx[9] = (unsigned long)(v2);
    v1 = sk_r56_00377824(0);
    ctx[10] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[11] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[12] = (unsigned long)(v1);
    if (r21 == 0) {
        sk_r56_00407248();
        v1 = rx8_02;
    }
else {
        sk_r56_00406590();
        (*rx8_00)();
        sk_r56_0008e1ec();
        v1 = rx8_01;
    }
    ctx[13] = (unsigned long)(v1);
    ctx[14] = (unsigned long)(v2);
    sk_r56_00353080();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003dd920 @ 0x003dd920   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dd920()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long * p3;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long l4;
    long l5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long rx17;
    unsigned long v6;
    cL4_w16_t pair7;
    v2 = sk_r56_00407ca0();
    sk_r56_0040700c();
    l4 = (long)*((int*)((char*)ctx[5] + 0x24));
    l5 = *(unsigned long *)((char*)ctx[6] + l4);
    l1 = ctx[9];
    if (l5 != 0) {
        *(unsigned long *)((char*)ctx[6] + l4) = l5 + -1;
        sk_r56_0040652c();
        sk_r56_00406608();
        sk_r56_00406e8c();
        sk_r56_00406288();
        sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
        p3 = (unsigned long *)sk_r56_00406fe0();
        ctx[15] = (unsigned long)(p3);
        *p3 = (unsigned long)(rx17);
        p3[1] = (unsigned long)((unsigned long)LAB_003dda40);
        sk_r56_00406f2c();
        sk_r56_00406d70();
        /* WARNING: Could not recover jumptable at 0x003dd9ec. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    v6 = ctx[2];
    sk_r56_00406ce0();
    sk_r56_00350968(0);
    sk_r56_00377824();
    sk_r56_00350744(v6);
    sk_r56_000839d8();
    sk_r56_0040bd24(ctx[12]);
    pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
    sk_r56_00407e58(pair7.lo,pair7.hi,v2);
    /* WARNING: Could not recover jumptable at 0x003dda3c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003ddc10 @ 0x003ddc10   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003ddc10(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, long param_5)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    long * pl3;
    ctx[2] = (unsigned long)(param_4);
    l1 = sk_r56_00377824(0,*(unsigned long *)((char*)param_5 + 0x18),*(unsigned long *)((char*)param_5 + 0x10), (unsigned long)DAT_00614a5c,(unsigned long)LAB_00614a7c);
    ctx[3] = (unsigned long)(l1);
    l1 = *(unsigned long *)((char*)l1 + -8);
    ctx[4] = (unsigned long)(l1);
    v2 = sk_r56_0040bb18(*(unsigned long *)((char*)l1 + 0x40) + 0xfU & 0xfffffffffffffff0);
    ctx[5] = (unsigned long)(v2);
    pl3 = (long *)sk_r56_0040bb18(DAT_0059fff4);
    ctx[6] = (unsigned long)(pl3);
    *pl3 = (unsigned long)(ctx);
    pl3[1] = (unsigned long)((long)(unsigned long)DAT_00405fdc);
    sk_r56_003dd840(pl3,param_1,param_2,param_3,param_5,v2);
    return;
}


/* sk_r56_003ddd44 @ 0x003ddd44   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003ddd44()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long (*pcVar3)();
    unsigned long rx8;
    long rx8_00;
    unsigned long (*rx8_01)();
    long rx16;
    long rx16_00;
    unsigned long v4;
    unsigned long v5;
    unsigned long r30;
    cL4_w16_t pair6;
    pair6.lo = sk_r56_0008e518(); pair6.hi = 0;  /* x1 half */
    v4 = *(unsigned long *)(pair6.lo + 0x10);
    sk_r56_0007c028();
    (*DAT_00658c80)(*(unsigned long *)((char*)rx8_00 + 0x40));
    sk_r56_000aa4ec();
    l1 = sk_r56_00407784();
    v5 = *(unsigned long *)((char*)l1 + 0x18);
    v2 = sk_r56_0040654c();
    sk_r56_00377824(v2,v5,v4);
    sk_r56_00351f10();
    sk_r56_0007c1a4();
    (DAT_00658c80)();
    sk_r56_0034b0d4();
    sk_r56_003510a0(*(unsigned long *)((char*)rx16 + 0x10));
    (*rx8_01)();
    pcVar3 = (unsigned long(*)())((unsigned long(*)())sk_r56_000a649c(v5));
    (*pcVar3)(v4,v5);
    sk_r56_003509c8(pair6.lo);
    ((unsigned long(*)())(rx16_00 + 8))();
    sk_r56_003510c4(rx8);
    ((unsigned long(*)())pair6.hi)();
    sk_r56_0008e500(r30);
    return;
}


/* sk_r56_003dde8c @ 0x003dde8c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dde8c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long rx1;
    cL4_w16_t pair1;
    sk_r56_00407478();
    pair1.lo = sk_r56_0035a7e8(); pair1.hi = 0;  /* x1 half */
    sk_r56_003ddecc(pair1.lo,pair1.hi,rx1);
    sk_r56_0036b270(rx1);
    return;
}


/* sk_r56_003ddecc @ 0x003ddecc   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003ddecc()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_003eaf4c();
    return;
}


/* sk_r56_003ddf04 @ 0x003ddf04   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003ddf04()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long rx8;
    long rx8_00;
    unsigned long rx16;
    unsigned long rx16_00;
    sk_r56_00407000();
    sk_r56_00406704();
    sk_r56_004079a8();
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[8] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[9] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[10] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[11] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[12] = (unsigned long)(v1);
    sk_r56_00407594();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003ddfbc @ 0x003ddfbc   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003ddfbc()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long * p3;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx16)();
    unsigned long rx17;
    cL4_w16_t pair4;
    v2 = sk_r56_0040790c();
    sk_r56_004070d8();
    if ((*((unsigned char*)ctx[4]) & 1) != 0) {
        sk_r56_00407604();
        sk_r56_0040686c();
        sk_r56_0040bd24();
        pair4.lo = sk_r56_0040678c(); pair4.hi = 0;  /* x1 half */
        sk_r56_004079b4(pair4.lo,pair4.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003de024. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[6];
    sk_r56_0040652c();
    sk_r56_00406608();
    sk_r56_004068f4();
    sk_r56_00406268();
    sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
    p3 = (unsigned long *)sk_r56_00406fe0();
    ctx[13] = (unsigned long)(p3);
    *p3 = (unsigned long)(rx17);
    p3[1] = (unsigned long)((unsigned long)LAB_003de0c0);
    sk_r56_00406ab4(ctx[10]);
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_004080cc();
    /* WARNING: Could not recover jumptable at 0x003de0bc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003de17c @ 0x003de17c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003de17c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long rx9_00;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long v5;
    cL4_w16_t pair6;
    v2 = sk_r56_00407ca0();
    sk_r56_0040700c();
    v5 = ctx[7];
    v3 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[9],v3,ctx[8]);
        (*rx9)();
        sk_r56_00407604();
        sk_r56_0040686c();
        sk_r56_0040bd24(v5);
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair6.lo,pair6.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003de1fc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[3];
    sk_r56_00406894(ctx[11],ctx[12]);
    ctx[15] = (unsigned long)(rx9_00);
    ctx[16] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_01)();
    sk_r56_004062e8((long)*((int*)((char*)l1 + 0x28)));
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    ctx[17] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003de298);
    sk_r56_00406bb4(ctx[12]);
    /* WARNING: Could not recover jumptable at 0x003de294. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003de33c @ 0x003de33c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003de33c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    cL4_w16_t pair2;
    sk_r56_00407000();
    if (*((char*)ctx+0x90) == '\x01') {
        sk_r56_00407d14(ctx[16]);
        v1 = (*rx9)();
        pair2.hi = 0;
        pair2.lo = v1;
    }
else {
        sk_r56_00408280();
        (*rx9_00)();
        pair2.lo = sk_r56_00408354(); pair2.hi = 0;  /* x1 half */
    }
    sk_r56_004069b0(pair2.lo,pair2.hi);
    sk_r56_004070a0();
    sk_r56_0040bd24();
    sk_r56_0040678c();
    /* WARNING: Could not recover jumptable at 0x003de3c0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003de418 @ 0x003de418   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003de418()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long param_1; /* Swift-ABI register param */
    unsigned long param_2; /* Swift-ABI register param */
    unsigned long param_3; /* Swift-ABI register param */
    unsigned long param_4; /* Swift-ABI register param */
    unsigned long v1;
    long rx8;
    long rx8_00;
    long rx8_01;
    unsigned long (*rx8_02)();
    unsigned long rx8_03;
    unsigned long rx8_04;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    long r21;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    sk_r56_00406cc8();
    sk_r56_00408308();
    ctx[9] = (unsigned long)(*(unsigned long *)((char*)param_4 + 0x10));
    v1 = sk_r56_0040684c();
    ctx[10] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[11] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[12] = (unsigned long)(v1);
    sk_r56_00406dd0();
    sk_r56_00408454();
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[14] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[15] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[16] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[17] = (unsigned long)(rx16_01);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[18] = (unsigned long)(v1);
    if (r21 == 0) {
        sk_r56_00407248();
        v1 = rx8_04;
    }
else {
        sk_r56_00406590();
        (*rx8_02)();
        sk_r56_0008e1ec();
        v1 = rx8_03;
    }
    ctx[19] = (unsigned long)(v1);
    ctx[20] = (unsigned long)(param_3);
    sk_r56_00353080();
    sk_r56_00407c78();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003de550 @ 0x003de550   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003de550()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    unsigned long v3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx16)();
    unsigned long rx17;
    cL4_w16_t pair5;
    v3 = sk_r56_0040790c();
    sk_r56_004070d8();
    if ((*((unsigned char*)ctx[6]) & 1) != 0) {
        sk_r56_00407bb8();
        v1 = ctx[12];
        sk_r56_0040686c();
        sk_r56_0040bd24();
        sk_r56_0040bd24(v1);
        pair5.lo = sk_r56_0040678c(); pair5.hi = 0;  /* x1 half */
        sk_r56_004079b4(pair5.lo,pair5.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003de5c0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l2 = ctx[9];
    sk_r56_0040652c();
    sk_r56_00406608();
    sk_r56_00406e8c();
    sk_r56_00406288();
    sk_r56_0040bb18(*((int*)((char*)l2 + 4)));
    p4 = (unsigned long *)sk_r56_00406fe0();
    ctx[21] = (unsigned long)(p4);
    *p4 = (unsigned long)(rx17);
    v3 = sk_r56_00407da0();
    sk_r56_00406d70(v3,ctx[3],ctx[4]);
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_004080cc();
    /* WARNING: Could not recover jumptable at 0x003de65c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003de74c @ 0x003de74c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003de74c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long rx9_00;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    cL4_w16_t pair5;
    v2 = sk_r56_00407ca0();
    sk_r56_0040700c();
    sk_r56_00407aac();
    v3 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[15],v3,ctx[14]);
        (*rx9)();
        sk_r56_00407bb8();
        v3 = ctx[12];
        sk_r56_0040686c();
        sk_r56_0040bd24();
        sk_r56_0040bd24(v3);
        pair5.lo = sk_r56_0040678c(); pair5.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair5.lo,pair5.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003de7d0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[5];
    sk_r56_00406894(ctx[17],ctx[18]);
    ctx[22] = (unsigned long)(rx9_00);
    ctx[23] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_01)();
    sk_r56_004062e8((long)*((int*)((char*)l1 + 0x28)));
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    ctx[24] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003de86c);
    sk_r56_00406bb4(ctx[18]);
    /* WARNING: Could not recover jumptable at 0x003de868. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003de938 @ 0x003de938   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003de938()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    cL4_w16_t pair3;
    sk_r56_00406fd4();
    if (*((char*)ctx + 200) == '\x01') {
        v2 = ((unsigned long(*)())ctx[22])(ctx[23],ctx[2], ctx[18],ctx[13]);
        pair3.hi = 0;
        pair3.lo = v2;
    }
else {
        ((unsigned long(*)())(ctx[17] + 8))(ctx[18],ctx[13]);
        pair3.lo = sk_r56_00408354(); pair3.hi = 0;  /* x1 half */
    }
    sk_r56_00407bb8(pair3.lo,pair3.hi);
    v1 = ctx[12];
    sk_r56_004070a0(ctx[2]);
    sk_r56_0040bd24();
    sk_r56_0040bd24(v1);
    sk_r56_0040678c();
    /* WARNING: Could not recover jumptable at 0x003de9e8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003deb0c @ 0x003deb0c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003deb0c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, long param_5)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    long * pl3;
    ctx[2] = (unsigned long)(param_4);
    l1 = sk_r56_00377824(0,*(unsigned long *)((char*)param_5 + 0x18),*(unsigned long *)((char*)param_5 + 0x10), (unsigned long)DAT_00614a5c,(unsigned long)LAB_00614a7c);
    ctx[3] = (unsigned long)(l1);
    l1 = *(unsigned long *)((char*)l1 + -8);
    ctx[4] = (unsigned long)(l1);
    v2 = sk_r56_0040bb18(*(unsigned long *)((char*)l1 + 0x40) + 0xfU & 0xfffffffffffffff0);
    ctx[5] = (unsigned long)(v2);
    pl3 = (long *)sk_r56_0040bb18(DAT_005a0004);
    ctx[6] = (unsigned long)(pl3);
    *pl3 = (unsigned long)(ctx);
    pl3[1] = (unsigned long)((long)(unsigned long)DAT_00405fdc);
    sk_r56_003de418(pl3,param_1,param_2,param_3,param_5,v2);
    return;
}


/* sk_r56_003dec44 @ 0x003dec44   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dec44(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, long param_6, unsigned long param_7)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    long rx8;
    long rx8_00;
    long rx8_01;
    long rx8_02;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    unsigned long rx16_02;
    unsigned long r20;
    cL4_w16_t pair3;
    pair3.lo = sk_r56_00406fd4(); pair3.hi = 0;  /* x1 half */
    ctx[8] = (unsigned long)(param_7);
    ctx[9] = (unsigned long)(r20);
    ctx[6] = (unsigned long)(param_5);
    ctx[7] = (unsigned long)(param_6);
    ctx[4] = (unsigned long)(param_3);
    ctx[5] = (unsigned long)(param_4);
    ctx[2] = (unsigned long)(pair3.lo); ctx[3] = (unsigned long)(pair3.hi);
    l2 = *(unsigned long *)((char*)param_6 + -8);
    ctx[10] = (unsigned long)(l2);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)l2 + 0x40));
    ctx[11] = (unsigned long)(v1);
    sk_r56_00406da8();
    sk_r56_00350974(0xff,param_7);
    v1 = sk_r56_00377824();
    ctx[12] = (unsigned long)(v1);
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[13] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[14] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[15] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[16] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[17] = (unsigned long)(v1);
    sk_r56_0007c028();
    ctx[18] = (unsigned long)(rx16_01);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[19] = (unsigned long)(v1);
    sk_r56_00350500();
    sk_r56_00350974();
    v1 = sk_r56_00377824();
    ctx[20] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[21] = (unsigned long)(rx16_02);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_02 + 0x40));
    ctx[22] = (unsigned long)(v1);
    sk_r56_00407594();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003dedd4 @ 0x003dedd4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dedd4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx8)();
    unsigned long (*rx9)();
    unsigned long rx17;
    long l5;
    cL4_w16_t pair6;
    sk_r56_004079cc();
    sk_r56_004070d8();
    v3 = ctx[19];
    v1 = ctx[20];
    l5 = ctx[18];
    v2 = ctx[8];
    ((unsigned long(*)())(ctx[10] + 0x10))(ctx[2],ctx[3], ctx[7]);
    sk_r56_0035136c(*(unsigned long *)((char*)l5 + 0x10),v3);
    (*rx8)();
    sk_r56_004070e4(v2);
    sk_r56_00350618();
    (*rx9)();
    sk_r56_004068bc();
    pair6.lo = sk_r56_000dbd0c(); pair6.hi = 0;  /* x1 half */
    v3 = sk_r56_00377bec(pair6.lo,pair6.hi,v1);
    ctx[23] = (unsigned long)(v3);
    v3 = sk_r56_003fcc1c();
    ctx[24] = (unsigned long)(v3);
    l5 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l5 + 4)));
    p4 = (unsigned long *)sk_r56_00406fe0();
    *(unsigned long **)(ctx + 200) = p4;
    *p4 = (unsigned long)(rx17);
    sk_r56_00407400();
    sk_r56_004078f4();
    /* WARNING: Could not recover jumptable at 0x003deec4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003defbc @ 0x003defbc   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003defbc()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    long l4;
    unsigned long v5;
    unsigned long v6;
    unsigned long * p7;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx17;
    unsigned long v8;
    int * pi9;
    unsigned long v10;
    unsigned long v11;
    cL4_w16_t pair12;
    v5 = sk_r56_004079cc();
    sk_r56_004070d8();
    v8 = ctx[15];
    v6 = sk_r56_00406420();
    if (carry) {
        v3 = ctx[22];
        v1 = ctx[19];
        v10 = ctx[17];
        v2 = ctx[13];
        l4 = ctx[14];
        v11 = ctx[11];
        sk_r56_00353c00(ctx[21],v6,ctx[20]);
        (*rx9)();
        ((unsigned long(*)())(l4 + 8))(v8,v2);
        sk_r56_0040bd24(v3);
        sk_r56_0040bd24(v1);
        sk_r56_0040bd24(v10);
        sk_r56_0040bd24(v8);
        sk_r56_0040bd24(v11);
        pair12.lo = sk_r56_0040678c(); pair12.hi = 0;  /* x1 half */
        sk_r56_004078f4(pair12.lo,pair12.hi,v5);
        /* WARNING: Could not recover jumptable at 0x003df078. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    pi9 = *(int **)((char*)ctx + 0x20);
    sk_r56_00406bd4(ctx[16],ctx[17]);
    (*rx9_00)();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())((long)pi9 + (long)*pi9));
    sk_r56_0040bb18(pi9[1]);
    p7 = (unsigned long *)sk_r56_00406fe0();
    ctx[27] = (unsigned long)(p7);
    *p7 = (unsigned long)(rx17);
    p7[1] = (unsigned long)((unsigned long)LAB_003df130);
    sk_r56_004078f4(ctx[11],ctx[2], ctx[17],UNRECOVERED_JUMPTABLE,v5);
    /* WARNING: Could not recover jumptable at 0x003df12c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003df278 @ 0x003df278   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003df278()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long * p1;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long rx17;
    sk_r56_00407000();
    ((unsigned long(*)())(ctx[10] + 0x20))(ctx[2],ctx[11], ctx[7]);
    sk_r56_004062a8(ctx[24]);
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p1 = (unsigned long *)sk_r56_00406fe0();
    *(unsigned long **)(ctx + 200) = p1;
    *p1 = (unsigned long)(rx17);
    sk_r56_00407400();
    /* WARNING: Could not recover jumptable at 0x003df308. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003df548 @ 0x003df548   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003df548()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx8_00)();
    unsigned long (*rx9)();
    unsigned long rx16;
    unsigned long rx17;
    long l5;
    cL4_w16_t pair6;
    sk_r56_004079cc();
    sk_r56_004070d8();
    v3 = ctx[17];
    v2 = ctx[18];
    l5 = ctx[16];
    v1 = ctx[8];
    sk_r56_0007c028(ctx[2],ctx[3], ctx[7]);
    ctx[21] = (unsigned long)(rx16);
    ((unsigned long(*)())(rx8 + 0x20))();
    sk_r56_0035136c(*(unsigned long *)((char*)l5 + 0x10),v3);
    (*rx8_00)();
    sk_r56_004070e4(v1);
    sk_r56_00350618();
    (*rx9)();
    sk_r56_004068bc();
    pair6.lo = sk_r56_000dbd0c(); pair6.hi = 0;  /* x1 half */
    v3 = sk_r56_00377bec(pair6.lo,pair6.hi,v2);
    ctx[22] = (unsigned long)(v3);
    v3 = sk_r56_003fcc1c();
    ctx[23] = (unsigned long)(v3);
    l5 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l5 + 4)));
    p4 = (unsigned long *)sk_r56_00406fe0();
    ctx[24] = (unsigned long)(p4);
    *p4 = (unsigned long)(rx17);
    sk_r56_0040733c();
    sk_r56_004078f4();
    /* WARNING: Could not recover jumptable at 0x003df654. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003df748 @ 0x003df748   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003df748()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    long l4;
    unsigned long v5;
    unsigned long v6;
    long * pl7;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long v8;
    int * pi9;
    unsigned long v10;
    cL4_w16_t pair11;
    v5 = sk_r56_0040790c();
    sk_r56_004070d8();
    v8 = ctx[13];
    v6 = sk_r56_00406420();
    if (carry) {
        v3 = ctx[20];
        v1 = ctx[17];
        v10 = ctx[15];
        v2 = ctx[11];
        l4 = ctx[12];
        sk_r56_00353c00(ctx[19],v6,ctx[18]);
        (*rx9)();
        ((unsigned long(*)())(l4 + 8))(v8,v2);
        sk_r56_0040bd24(v3);
        sk_r56_0040bd24(v1);
        sk_r56_0040bd24(v10);
        sk_r56_0040bd24(v8);
        pair11.lo = sk_r56_0040678c(); pair11.hi = 0;  /* x1 half */
        sk_r56_004079b4(pair11.lo,pair11.hi,v5);
        /* WARNING: Could not recover jumptable at 0x003df7f8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    pi9 = *(int **)((char*)ctx + 0x20);
    sk_r56_00406bd4(ctx[14],ctx[15]);
    (*rx9_00)();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())((long)pi9 + (long)*pi9));
    pl7 = (long *)sk_r56_0040bb18(pi9[1]);
    ctx[26] = (unsigned long)(pl7);
    *pl7 = (unsigned long)(ctx);
    pl7[1] = (unsigned long)((long)(unsigned long)LAB_003df8b0);
    sk_r56_004080cc(ctx[2],ctx[15], UNRECOVERED_JUMPTABLE,v5);
    /* WARNING: Could not recover jumptable at 0x003df8ac. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003df9dc @ 0x003df9dc   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003df9dc()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long * p1;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long rx17;
    sk_r56_00407000();
    sk_r56_004062a8(ctx[23]);
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p1 = (unsigned long *)sk_r56_00406fe0();
    ctx[24] = (unsigned long)(p1);
    *p1 = (unsigned long)(rx17);
    sk_r56_0040733c();
    /* WARNING: Could not recover jumptable at 0x003dfa50. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dfc60 @ 0x003dfc60   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dfc60()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    unsigned long * p3;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*rx16)();
    unsigned long rx17;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    v1 = sk_r56_00407cc4();
    sk_r56_00407070(v1,ctx[2]);
    (*rx9)();
    sk_r56_004067cc();
    (*rx9_00)();
    sk_r56_004068bc();
    sk_r56_00350470();
    v1 = sk_r56_00377bec();
    ctx[16] = (unsigned long)(v1);
    v1 = sk_r56_003fcc1c();
    ctx[17] = (unsigned long)(v1);
    l2 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l2 + 4)));
    p3 = (unsigned long *)sk_r56_00406fe0();
    ctx[18] = (unsigned long)(p3);
    *p3 = (unsigned long)(rx17);
    sk_r56_00406944();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003dfd38. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003dfe08 @ 0x003dfe08   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003dfe08(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE_00)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    long l5;
    unsigned long v6;
    sk_r56_00407ca0();
    sk_r56_0040700c();
    v3 = sk_r56_00406db8();
    *((int*)ctx+0xb0) = (int)v3;
    if ((int)v3 == 1) {
        v2 = ctx[15];
        v1 = ctx[12];
        v6 = ctx[9];
        sk_r56_00353c00(ctx[14],v3,ctx[13]);
        (*rx9)();
        sk_r56_0040bd24(v2);
        sk_r56_0040bd24(v1);
        sk_r56_0040bd24();
        sk_r56_0040bd24(v6);
        sk_r56_00406e48();
        sk_r56_00407e58();
        /* WARNING: Could not recover jumptable at 0x003dfe9c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l5 = ctx[3];
    sk_r56_00406bd4(ctx[8],ctx[9]);
    (*rx9_00)();
    sk_r56_004065c8();
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)l5 + 4)));
    ctx[20] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003dff30);
    sk_r56_00406bb4(ctx[9]);
    /* WARNING: Could not recover jumptable at 0x003dff2c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e0028 @ 0x003e0028   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e0028(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE_00)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    unsigned long v5;
    unsigned long * p6;
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    sk_r56_00407ca0();
    v5 = sk_r56_0040700c();
    if ((*((unsigned char*)ctx+0xb4) & 1) != 0) {
        v3 = ctx[15];
        v1 = ctx[12];
        v2 = ctx[9];
        v4 = ctx[10];
        sk_r56_0040711c(ctx[14],v5,ctx[13]);
        (*rx9)();
        sk_r56_0040bd24(v3);
        sk_r56_0040bd24(v1);
        sk_r56_0040bd24(v4);
        sk_r56_0040bd24(v2);
        sk_r56_00406e48();
        sk_r56_00407e58();
        /* WARNING: Could not recover jumptable at 0x003e00b4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    sk_r56_004062a8(ctx[17]);
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p6 = (unsigned long *)sk_r56_00406fe0();
    ctx[18] = (unsigned long)(p6);
    *p6 = (unsigned long)(rx17);
    sk_r56_00406944();
    /* WARNING: Could not recover jumptable at 0x003e0128. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e012c @ 0x003e012c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e012c()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long in_x3;
    long rx8;
    long rx8_00;
    long rx8_01;
    unsigned long rx16;
    long rx16_00;
    unsigned long rx16_01;
    unsigned long rx16_02;
    sk_r56_00406fd4();
    sk_r56_0040752c();
    sk_r56_00406da8();
    sk_r56_00377824(0,in_x3);
    sk_r56_004079a8();
    sk_r56_000a6f88();
    ctx[8] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[9] = (unsigned long)(v1);
    sk_r56_00350798();
    sk_r56_00310d68();
    sk_r56_00351f10();
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx16_00 + 0x40));
    ctx[10] = (unsigned long)(v1);
    sk_r56_0007c028();
    ctx[11] = (unsigned long)(rx16_01);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[12] = (unsigned long)(v1);
    sk_r56_00407090();
    sk_r56_00351584();
    v1 = sk_r56_00377824();
    ctx[13] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[14] = (unsigned long)(rx16_02);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[15] = (unsigned long)(v1);
    sk_r56_00407594();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e025c @ 0x003e025c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e025c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    unsigned long * p3;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*rx16)();
    unsigned long rx17;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    v1 = sk_r56_00407cc4();
    sk_r56_00407070(v1,ctx[6]);
    (*rx9)();
    sk_r56_004067cc();
    (*rx9_00)();
    sk_r56_004068bc();
    sk_r56_00350470();
    v1 = sk_r56_00377bec();
    ctx[16] = (unsigned long)(v1);
    v1 = sk_r56_003fcc1c();
    ctx[17] = (unsigned long)(v1);
    l2 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l2 + 4)));
    p3 = (unsigned long *)sk_r56_00406fe0();
    ctx[18] = (unsigned long)(p3);
    *p3 = (unsigned long)(rx17);
    sk_r56_00406944();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e0334. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e0404 @ 0x003e0404   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e0404(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE_00)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    long l5;
    unsigned long v6;
    sk_r56_00407ca0();
    sk_r56_0040700c();
    v3 = sk_r56_00406db8();
    *((int*)ctx+0xb0) = (int)v3;
    if ((int)v3 == 1) {
        v2 = ctx[15];
        v1 = ctx[12];
        v6 = ctx[9];
        sk_r56_00353c00(ctx[14],v3,ctx[13]);
        (*rx9)();
        sk_r56_0040bd24(v2);
        sk_r56_0040bd24(v1);
        sk_r56_0040bd24();
        sk_r56_0040bd24(v6);
        sk_r56_00406e48();
        sk_r56_00407e58();
        /* WARNING: Could not recover jumptable at 0x003e0498. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l5 = ctx[2];
    sk_r56_00406bd4(ctx[8],ctx[9]);
    (*rx9_00)();
    sk_r56_004065c8();
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)l5 + 4)));
    ctx[20] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003e05a8);
    sk_r56_00406bb4(ctx[9]);
    /* WARNING: Could not recover jumptable at 0x003e0528. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e06a0 @ 0x003e06a0   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e06a0(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE_00)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    unsigned long v5;
    unsigned long * p6;
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    sk_r56_00407ca0();
    v5 = sk_r56_0040700c();
    if ((*((unsigned char*)ctx+0xb4) & 1) != 0) {
        v3 = ctx[15];
        v1 = ctx[12];
        v2 = ctx[9];
        v4 = ctx[10];
        sk_r56_0040711c(ctx[14],v5,ctx[13]);
        (*rx9)();
        sk_r56_0040bd24(v3);
        sk_r56_0040bd24(v1);
        sk_r56_0040bd24(v4);
        sk_r56_0040bd24(v2);
        sk_r56_00406e48();
        sk_r56_00407e58();
        /* WARNING: Could not recover jumptable at 0x003e072c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    sk_r56_004062a8(ctx[17]);
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p6 = (unsigned long *)sk_r56_00406fe0();
    ctx[18] = (unsigned long)(p6);
    *p6 = (unsigned long)(rx17);
    sk_r56_00406944();
    /* WARNING: Could not recover jumptable at 0x003e07a0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e0848 @ 0x003e0848   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e0848()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    long * pl2;
    unsigned long v3;
    unsigned long v4;
    unsigned long v5;
    sk_r56_00407000();
    l1 = sk_r56_0040bb18(0x30);
    ctx[7] = (unsigned long)(l1);
    v5 = ctx[3];
    v4 = ctx[2];
    v3 = ctx[4];
    *(unsigned long *)((char*)l1 + 0x18) = (unsigned long)(ctx[5]);
    *(unsigned long *)((char*)l1 + 0x10) = (unsigned long)(v3);
    *(unsigned long *)((char*)l1 + 0x28) = (unsigned long)(v5);
    *(unsigned long *)((char*)l1 + 0x20) = (unsigned long)(v4);
    pl2 = (long *)sk_r56_0040bb18(DAT_005a0024);
    ctx[8] = (unsigned long)(pl2);
    *pl2 = (unsigned long)(ctx);
    pl2[1] = (unsigned long)((long)sk_r56_003e08fc);
    sk_r56_003e012c(pl2 + 1,(unsigned long)DAT_005a0038,l1,ctx[4], ctx[5]);
    return;
}


/* sk_r56_003e08fc @ 0x003e08fc   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e08fc()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned int v1;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long l2;
    long r20;
    long l3;
    v1 = sk_r56_00406fd4();
    l3 = *ctx;
    l2 = *ctx;
    sk_r56_0040bd24((unsigned long)0xc31a000000000000, *(unsigned long *)((char*)l3 + 0x40));
    sk_r56_0040bd24(*(unsigned long *)((char*)l3 + 0x38));
    if (r20 == 0) {
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())*(unsigned long*)((char*)(l2 + 8)));
        v1 = (v1 ^ 0xffffffff) & 1;
    }
else {
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())*(unsigned long*)((char*)(l2 + 8)));
        v1 = 0;
    }
    /* WARNING: Could not recover jumptable at 0x003e09e0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)(v1);
    return;
}


/* sk_r56_003e09e4 @ 0x003e09e4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e09e4(unsigned long param_1, int *param_2)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    int i1;
    long * pl2;
    i1 = *param_2;
    pl2 = (long *)sk_r56_0040bb18(param_2[1]);
    ctx[2] = (unsigned long)(pl2);
    *pl2 = (unsigned long)(ctx);
    pl2[1] = (unsigned long)((long)(unsigned long)LAB_003e0aa4);
    /* WARNING: Could not recover jumptable at 0x003e0aa0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*(unsigned long(*)())((long)param_2 + (long)i1))(pl2 + 1,param_1);
    return;
}


/* sk_r56_003e0c88 @ 0x003e0c88   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e0c88()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    unsigned long * p3;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*rx16)();
    unsigned long rx17;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    v1 = sk_r56_00407cc4();
    sk_r56_00407070(v1,ctx[6]);
    (*rx9)();
    sk_r56_004067cc();
    (*rx9_00)();
    sk_r56_004068bc();
    sk_r56_00350470();
    v1 = sk_r56_00377bec();
    ctx[16] = (unsigned long)(v1);
    v1 = sk_r56_003fcc1c();
    ctx[17] = (unsigned long)(v1);
    l2 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l2 + 4)));
    p3 = (unsigned long *)sk_r56_00406fe0();
    ctx[18] = (unsigned long)(p3);
    *p3 = (unsigned long)(rx17);
    sk_r56_00406944();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e0d60. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e0e30 @ 0x003e0e30   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e0e30()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    int i3;
    unsigned long v4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long v5;
    unsigned long * p6;
    unsigned long (*rx8)();
    long rx8_00;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*rx16)();
    unsigned long rx17;
    unsigned long v7;
    unsigned long (*pcVar8)();
    unsigned long v9;
    unsigned long v10;
    sk_r56_004079cc();
    sk_r56_004070d8();
    v7 = ctx[10];
    pcVar8 = (unsigned long(*)())((unsigned long(*)())ctx[7]);
    sk_r56_00351d24();
    UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())(pcVar8);
    v4 = sk_r56_000839f8();
    i3 = (int)v4;
    if (i3 != 1) {
        l1 = ctx[8];
        v4 = ctx[9];
        v7 = ctx[5];
        v10 = ctx[2];
        sk_r56_00407ce4();
        sk_r56_003510c4();
        (*rx9)();
        UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())((unsigned long(*)())sk_r56_0014ae44(v7));
        v5 = (*UNRECOVERED_JUMPTABLE_00)(v4,v10,pcVar8,v7);
        sk_r56_00350560(*(unsigned long *)((char*)l1 + 8));
        v4 = (*rx8)();
        if ((v5 & 1) == 0) {
            sk_r56_004062a8(ctx[17]);
            sk_r56_0040bb18(*((int*)((char*)rx8_00 + 4)));
            p6 = (unsigned long *)sk_r56_00406fe0();
            ctx[18] = (unsigned long)(p6);
            *p6 = (unsigned long)(rx17);
            sk_r56_00406944();
            UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())(rx16);
            sk_r56_004078f4();
            /* WARNING: Could not recover jumptable at 0x003e0fc0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
            return;
        }
        v7 = ctx[10];
        UNRECOVERED_JUMPTABLE_00 = (unsigned long(*)())(pcVar8);
    }
    v2 = ctx[15];
    v10 = ctx[12];
    v9 = ctx[9];
    sk_r56_00407f48(ctx[14],v4,ctx[13]);
    (*rx9_00)();
    sk_r56_0040bd24(v2);
    sk_r56_0040bd24(v10);
    sk_r56_0040bd24(v7);
    sk_r56_0040bd24(v9);
    sk_r56_004078b4();
    sk_r56_004078f4(i3 != 1);
    /* WARNING: Could not recover jumptable at 0x003e0f4c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
    return;
}


/* sk_r56_003e117c @ 0x003e117c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e117c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    long l3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx17;
    cL4_w16_t pair5;
    sk_r56_00407c8c();
    v1 = sk_r56_0040700c();
    v2 = ctx[14];
    sk_r56_00407070(ctx[12],v1,ctx[3]);
    (*rx9)();
    sk_r56_004067cc();
    (*rx9_00)();
    sk_r56_004068bc();
    pair5.lo = sk_r56_00350470(); pair5.hi = 0;  /* x1 half */
    v2 = sk_r56_00377bec(pair5.lo,pair5.hi,v2);
    ctx[17] = (unsigned long)(v2);
    v2 = sk_r56_003fcc1c();
    ctx[18] = (unsigned long)(v2);
    l3 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l3 + 4)));
    p4 = (unsigned long *)sk_r56_00406fe0();
    ctx[19] = (unsigned long)(p4);
    *p4 = (unsigned long)(rx17);
    sk_r56_00406e18();
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e1258. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e1330 @ 0x003e1330   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e1330()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long rx9;
    unsigned long (*rx9_00)();
    unsigned long rx10;
    unsigned long v5;
    long l6;
    cL4_w16_t pair7;
    v3 = sk_r56_00407ca0();
    sk_r56_0040700c();
    v5 = ctx[8];
    sk_r56_00406420();
    if (carry) {
        sk_r56_00408348();
        ((unsigned long(*)())(rx8 + 8))();
        sk_r56_00407aac();
        v1 = ctx[10];
        v2 = ctx[11];
        sk_r56_0040686c();
        sk_r56_0040bd24(v5);
        sk_r56_0040bd24(v2);
        sk_r56_0040bd24(v1);
        pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair7.lo,pair7.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003e13c4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l6 = ctx[4];
    sk_r56_00406894(ctx[9],ctx[10]);
    ctx[21] = (unsigned long)(rx9);
    ctx[22] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_00)();
    sk_r56_004065c8();
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)l6 + 4)));
    ctx[23] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003e1460);
    sk_r56_00406bb4(ctx[10]);
    /* WARNING: Could not recover jumptable at 0x003e145c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e1550 @ 0x003e1550   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e1550()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*pcVar1)();
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    long rx8_00;
    unsigned long rx17;
    cL4_w16_t pair6;
    v4 = sk_r56_00407c8c();
    sk_r56_0040700c();
    if (*((char*)ctx + 200) == '\x01') {
        pcVar1 = (unsigned long(*)())((unsigned long(*)())ctx[21]);
        sk_r56_00408348();
        sk_r56_00407954();
        ((unsigned long(*)())(rx8 + 8))();
        sk_r56_0011aa70();
        (*pcVar1)();
        sk_r56_00407aac();
        v2 = ctx[10];
        v3 = ctx[11];
        sk_r56_00406cf0();
        sk_r56_0040bd24();
        sk_r56_0040bd24(v3);
        sk_r56_0040bd24(v2);
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407c78(pair6.lo,pair6.hi,v4);
        /* WARNING: Could not recover jumptable at 0x003e15f4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    ((unsigned long(*)())(*(unsigned long *)(ctx[9] + 8)))(ctx[10],ctx[8]);
    sk_r56_004062a8(ctx[18]);
    sk_r56_0040bb18(*((int*)((char*)rx8_00 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[19] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    sk_r56_00406e18();
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e167c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e17b4 @ 0x003e17b4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e17b4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    long l3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx17;
    cL4_w16_t pair5;
    sk_r56_00407c8c();
    v1 = sk_r56_0040700c();
    v2 = ctx[14];
    sk_r56_00407070(ctx[12],v1,ctx[7]);
    (*rx9)();
    sk_r56_004067cc();
    (*rx9_00)();
    sk_r56_004068bc();
    pair5.lo = sk_r56_00350470(); pair5.hi = 0;  /* x1 half */
    v2 = sk_r56_00377bec(pair5.lo,pair5.hi,v2);
    ctx[17] = (unsigned long)(v2);
    v2 = sk_r56_003fcc1c();
    ctx[18] = (unsigned long)(v2);
    l3 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l3 + 4)));
    p4 = (unsigned long *)sk_r56_00406fe0();
    ctx[19] = (unsigned long)(p4);
    *p4 = (unsigned long)(rx17);
    sk_r56_00406e18();
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e1890. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e1968 @ 0x003e1968   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e1968()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long rx9;
    unsigned long (*rx9_00)();
    unsigned long rx10;
    unsigned long v5;
    long l6;
    cL4_w16_t pair7;
    v3 = sk_r56_00407ca0();
    sk_r56_0040700c();
    v5 = ctx[8];
    sk_r56_00406420();
    if (carry) {
        sk_r56_00408348();
        ((unsigned long(*)())(rx8 + 8))();
        sk_r56_00407aac();
        v1 = ctx[10];
        v2 = ctx[11];
        sk_r56_0040686c();
        sk_r56_0040bd24(v5);
        sk_r56_0040bd24(v2);
        sk_r56_0040bd24(v1);
        pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair7.lo,pair7.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003e19fc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l6 = ctx[3];
    sk_r56_00406894(ctx[9],ctx[10]);
    ctx[21] = (unsigned long)(rx9);
    ctx[22] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_00)();
    sk_r56_004065c8();
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)l6 + 4)));
    ctx[23] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003e1b10);
    sk_r56_00406bb4(ctx[10]);
    /* WARNING: Could not recover jumptable at 0x003e1a94. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e1c00 @ 0x003e1c00   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e1c00()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*pcVar1)();
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    long rx8_00;
    unsigned long rx17;
    cL4_w16_t pair6;
    v4 = sk_r56_00407c8c();
    sk_r56_0040700c();
    if (*((char*)ctx + 200) == '\x01') {
        pcVar1 = (unsigned long(*)())((unsigned long(*)())ctx[21]);
        sk_r56_00408348();
        sk_r56_00407954();
        ((unsigned long(*)())(rx8 + 8))();
        sk_r56_0011aa70();
        (*pcVar1)();
        sk_r56_00407aac();
        v2 = ctx[10];
        v3 = ctx[11];
        sk_r56_00406cf0();
        sk_r56_0040bd24();
        sk_r56_0040bd24(v3);
        sk_r56_0040bd24(v2);
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407c78(pair6.lo,pair6.hi,v4);
        /* WARNING: Could not recover jumptable at 0x003e1ca4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    ((unsigned long(*)())(*(unsigned long *)(ctx[9] + 8)))(ctx[10],ctx[8]);
    sk_r56_004062a8(ctx[18]);
    sk_r56_0040bb18(*((int*)((char*)rx8_00 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[19] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    sk_r56_00406e18();
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e1d2c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e1da8 @ 0x003e1da8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e1da8()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long in_x4;
    long rx8;
    long rx8_00;
    long rx8_01;
    long rx8_02;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    unsigned long rx16_02;
    unsigned long r20;
    unsigned long r24;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    ctx[6] = (unsigned long)(in_x4);
    ctx[7] = (unsigned long)(r20);
    sk_r56_00406c80();
    v1 = sk_r56_00408538();
    ctx[8] = (unsigned long)(v1);
    sk_r56_00350798();
    v2 = sk_r56_00310d68();
    ctx[9] = (unsigned long)(v2);
    sk_r56_00352018();
    ctx[10] = (unsigned long)(rx16);
    v2 = sk_r56_004081b4(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[11] = (unsigned long)(v2);
    v2 = sk_r56_0040bb18(r24 & 0xfffffffffffffff0);
    ctx[12] = (unsigned long)(v2);
    sk_r56_0040683c();
    ctx[13] = (unsigned long)(rx16_00);
    v2 = sk_r56_00407b48(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[14] = (unsigned long)(v2);
    v2 = sk_r56_0040bb18(v1 & 0xfffffffffffffff0);
    ctx[15] = (unsigned long)(v2);
    sk_r56_0007c028();
    ctx[16] = (unsigned long)(rx16_01);
    v2 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[17] = (unsigned long)(v2);
    sk_r56_00407090();
    sk_r56_00351584();
    v2 = sk_r56_00377824();
    ctx[18] = (unsigned long)(v2);
    sk_r56_00352018();
    ctx[19] = (unsigned long)(rx16_02);
    v2 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_02 + 0x40));
    ctx[20] = (unsigned long)(v2);
    sk_r56_00407594();
    sk_r56_00407c78();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e1f00 @ 0x003e1f00   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e1f00()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    long l3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx17;
    cL4_w16_t pair5;
    sk_r56_00407c8c();
    v1 = sk_r56_0040700c();
    v2 = ctx[18];
    sk_r56_00407070(ctx[16],v1,ctx[7]);
    (*rx9)();
    sk_r56_004067cc();
    (*rx9_00)();
    sk_r56_004068bc();
    pair5.lo = sk_r56_00350470(); pair5.hi = 0;  /* x1 half */
    sk_r56_00377bec(pair5.lo,pair5.hi,v2);
    sk_r56_004083cc();
    v2 = sk_r56_003fcc1c();
    ctx[22] = (unsigned long)(v2);
    l3 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l3 + 4)));
    p4 = (unsigned long *)sk_r56_00406fe0();
    ctx[23] = (unsigned long)(p4);
    *p4 = (unsigned long)(rx17);
    p4[1] = (unsigned long)((unsigned long)LAB_003e1ff0);
    sk_r56_00407814(ctx[12],ctx[18]);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e1fec. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e20c4 @ 0x003e20c4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e20c4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long * p2;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx8)();
    long rx8_00;
    unsigned long (*rx9)();
    unsigned long rx9_00;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long (*rx16)();
    unsigned long rx17;
    unsigned long v3;
    long r21;
    cL4_w16_t pair4;
    v1 = sk_r56_0040790c();
    sk_r56_004070d8();
    v3 = ctx[8];
    sk_r56_00406420();
    if (carry) {
        sk_r56_0040826c();
        (*rx9)();
        sk_r56_0007c1c4(*(unsigned long *)((char*)r21 + 8));
        (*rx8)();
        sk_r56_00407080();
        sk_r56_0040686c();
        sk_r56_0040bd24(v3);
        sk_r56_0040bd24((unsigned long *)(r21 + 8));
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        pair4.lo = sk_r56_0040678c(); pair4.hi = 0;  /* x1 half */
        sk_r56_004079b4(pair4.lo,pair4.hi,v1);
        /* WARNING: Could not recover jumptable at 0x003e2178. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    sk_r56_00406894(ctx[13],ctx[15]);
    *(unsigned long *)((char*)ctx + 200) = (unsigned long)(rx9_00);
    ctx[26] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_01)();
    sk_r56_004062a8(ctx[22]);
    sk_r56_0040bb18(*((int*)((char*)rx8_00 + 4)));
    p2 = (unsigned long *)sk_r56_00406fe0();
    ctx[27] = (unsigned long)(p2);
    *p2 = (unsigned long)(rx17);
    sk_r56_00406f84();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_004080cc();
    /* WARNING: Could not recover jumptable at 0x003e220c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e22f8 @ 0x003e22f8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e22f8(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long * pl1;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*rx8)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long v2;
    long l3;
    unsigned long (*r26)();
    long r27;
    sk_r56_004084a4();
    sk_r56_00407924();
    v2 = ctx[11];
    sk_r56_00406be4();
    if (carry) {
        sk_r56_00407a60();
        (*rx9)();
        sk_r56_00084174(*(unsigned long *)((char*)r27 + 8));
        (*rx8)();
        sk_r56_00350548();
        (*r26)();
        sk_r56_00407080();
        sk_r56_00406cf0();
        sk_r56_0040bd24(v2);
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040678c();
        /* WARNING: Could not recover jumptable at 0x003e23c4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l3 = ctx[3];
    sk_r56_00350968(ctx[26],ctx[14]);
    (*rx9_00)();
    sk_r56_00407260();
    pl1 = (long *)sk_r56_0040bb18(*((int*)((char*)l3 + 4)));
    ctx[29] = (unsigned long)(pl1);
    *pl1 = (unsigned long)(ctx);
    pl1[1] = (unsigned long)((long)(unsigned long)LAB_003e2458);
    sk_r56_00408360(ctx[14],pl1,ctx[15]);
    /* WARNING: Could not recover jumptable at 0x003e2454. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e2558 @ 0x003e2558   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e2558()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long * p1;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned int rw10;
    unsigned long (*rx16)();
    unsigned long rx17;
    unsigned long v2;
    cL4_w16_t pair3;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    sk_r56_00408244();
    if ((rw10 & 1) == 0) {
        (*rx9)(ctx[14],ctx[8]);
    }
else {
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())*(unsigned long*)((char*)(ctx + 200)));
        v2 = ctx[8];
        sk_r56_0006b6f4();
        (*rx9_00)();
        pair3.lo = sk_r56_0007c1c4(); pair3.hi = 0;  /* x1 half */
        (*UNRECOVERED_JUMPTABLE)(pair3.lo,pair3.hi,v2);
    }
    sk_r56_004062a8(ctx[22]);
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p1 = (unsigned long *)sk_r56_00406fe0();
    ctx[27] = (unsigned long)(p1);
    *p1 = (unsigned long)(rx17);
    sk_r56_00406f84();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e2628. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e262c @ 0x003e262c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e262c()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned long in_x4;
    long rx8;
    long rx8_00;
    long rx8_01;
    long rx8_02;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    unsigned long rx16_02;
    unsigned long r20;
    unsigned long r24;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    ctx[6] = (unsigned long)(in_x4);
    ctx[7] = (unsigned long)(r20);
    sk_r56_00406c80();
    v1 = sk_r56_00408538();
    ctx[8] = (unsigned long)(v1);
    sk_r56_00350798();
    v2 = sk_r56_00310d68();
    ctx[9] = (unsigned long)(v2);
    sk_r56_00352018();
    ctx[10] = (unsigned long)(rx16);
    v2 = sk_r56_004081b4(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[11] = (unsigned long)(v2);
    v2 = sk_r56_0040bb18(r24 & 0xfffffffffffffff0);
    ctx[12] = (unsigned long)(v2);
    sk_r56_0040683c();
    ctx[13] = (unsigned long)(rx16_00);
    v2 = sk_r56_00407b48(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[14] = (unsigned long)(v2);
    v2 = sk_r56_0040bb18(v1 & 0xfffffffffffffff0);
    ctx[15] = (unsigned long)(v2);
    sk_r56_0007c028();
    ctx[16] = (unsigned long)(rx16_01);
    v2 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[17] = (unsigned long)(v2);
    sk_r56_00407090();
    sk_r56_00351584();
    v2 = sk_r56_00377824();
    ctx[18] = (unsigned long)(v2);
    sk_r56_00352018();
    ctx[19] = (unsigned long)(rx16_02);
    v2 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_02 + 0x40));
    ctx[20] = (unsigned long)(v2);
    sk_r56_00407594();
    sk_r56_00407c78();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e2784 @ 0x003e2784   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e2784()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    long l3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx17;
    cL4_w16_t pair5;
    sk_r56_00407c8c();
    v1 = sk_r56_0040700c();
    v2 = ctx[18];
    sk_r56_00407070(ctx[16],v1,ctx[7]);
    (*rx9)();
    sk_r56_004067cc();
    (*rx9_00)();
    sk_r56_004068bc();
    pair5.lo = sk_r56_00350470(); pair5.hi = 0;  /* x1 half */
    sk_r56_00377bec(pair5.lo,pair5.hi,v2);
    sk_r56_004083cc();
    v2 = sk_r56_003fcc1c();
    ctx[22] = (unsigned long)(v2);
    l3 = sk_r56_004062c8();
    sk_r56_0040bb18(*((int*)((char*)l3 + 4)));
    p4 = (unsigned long *)sk_r56_00406fe0();
    ctx[23] = (unsigned long)(p4);
    *p4 = (unsigned long)(rx17);
    p4[1] = (unsigned long)((unsigned long)LAB_003e2874);
    sk_r56_00407814(ctx[12],ctx[18]);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e2870. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e2948 @ 0x003e2948   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e2948()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long * p2;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx8)();
    long rx8_00;
    unsigned long (*rx9)();
    unsigned long rx9_00;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long (*rx16)();
    unsigned long rx17;
    unsigned long v3;
    long r21;
    cL4_w16_t pair4;
    v1 = sk_r56_0040790c();
    sk_r56_004070d8();
    v3 = ctx[8];
    sk_r56_00406420();
    if (carry) {
        sk_r56_0040826c();
        (*rx9)();
        sk_r56_0007c1c4(*(unsigned long *)((char*)r21 + 8));
        (*rx8)();
        sk_r56_00407080();
        sk_r56_0040686c();
        sk_r56_0040bd24(v3);
        sk_r56_0040bd24((unsigned long *)(r21 + 8));
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        pair4.lo = sk_r56_0040678c(); pair4.hi = 0;  /* x1 half */
        sk_r56_004079b4(pair4.lo,pair4.hi,v1);
        /* WARNING: Could not recover jumptable at 0x003e29fc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    sk_r56_00406894(ctx[13],ctx[15]);
    *(unsigned long *)((char*)ctx + 200) = (unsigned long)(rx9_00);
    ctx[26] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_01)();
    sk_r56_004062a8(ctx[22]);
    sk_r56_0040bb18(*((int*)((char*)rx8_00 + 4)));
    p2 = (unsigned long *)sk_r56_00406fe0();
    ctx[27] = (unsigned long)(p2);
    *p2 = (unsigned long)(rx17);
    sk_r56_00406f84();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_004080cc();
    /* WARNING: Could not recover jumptable at 0x003e2a90. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e2b7c @ 0x003e2b7c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e2b7c(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long * pl1;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*rx8)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long v2;
    long l3;
    unsigned long (*r26)();
    long r27;
    sk_r56_004084a4();
    sk_r56_00407924();
    v2 = ctx[11];
    sk_r56_00406be4();
    if (carry) {
        sk_r56_00407a60();
        (*rx9)();
        sk_r56_00084174(*(unsigned long *)((char*)r27 + 8));
        (*rx8)();
        sk_r56_00350548();
        (*r26)();
        sk_r56_00407080();
        sk_r56_00406cf0();
        sk_r56_0040bd24(v2);
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040678c();
        /* WARNING: Could not recover jumptable at 0x003e2c48. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l3 = ctx[3];
    sk_r56_00350968(ctx[26],ctx[14]);
    (*rx9_00)();
    sk_r56_00407260();
    pl1 = (long *)sk_r56_0040bb18(*((int*)((char*)l3 + 4)));
    ctx[29] = (unsigned long)(pl1);
    *pl1 = (unsigned long)(ctx);
    pl1[1] = (unsigned long)((long)(unsigned long)LAB_003e2cdc);
    sk_r56_00408360(ctx[15],pl1,ctx[14]);
    /* WARNING: Could not recover jumptable at 0x003e2cd8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e2ddc @ 0x003e2ddc   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e2ddc()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long * p1;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned int rw10;
    unsigned long (*rx16)();
    unsigned long rx17;
    unsigned long v2;
    cL4_w16_t pair3;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    sk_r56_00408244();
    if ((rw10 & 1) == 0) {
        (*rx9)(ctx[14],ctx[8]);
    }
else {
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())*(unsigned long*)((char*)(ctx + 200)));
        v2 = ctx[8];
        sk_r56_0006b6f4();
        (*rx9_00)();
        pair3.lo = sk_r56_0007c1c4(); pair3.hi = 0;  /* x1 half */
        (*UNRECOVERED_JUMPTABLE)(pair3.lo,pair3.hi,v2);
    }
    sk_r56_004062a8(ctx[22]);
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p1 = (unsigned long *)sk_r56_00406fe0();
    ctx[27] = (unsigned long)(p1);
    *p1 = (unsigned long)(rx17);
    sk_r56_00406f84();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e2eac. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e3064 @ 0x003e3064   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e3064()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long * p2;
    unsigned long v3;
    unsigned long rx17;
    unsigned long r19;
    sk_r56_004070d8();
    sk_r56_0036a940(0x67d768,0x30,7);
    l1 = sk_r56_00407c3c();
    ctx[8] = (unsigned long)(l1);
    sk_r56_00406ce0(l1,ctx[4]);
    sk_r56_00377824(0);
    sk_r56_00408224();
    *(unsigned long *)((char*)l1 + 0x28) = (unsigned long)((unsigned long)((unsigned long)DAT_00405fac));
    *(unsigned long *)((char*)l1 + 0x30) = (unsigned long)(r19);
    sk_r56_0040bb18(DAT_005a005c);
    p2 = (unsigned long *)sk_r56_00406fe0();
    ctx[9] = (unsigned long)(p2);
    *p2 = (unsigned long)(rx17);
    v3 = sk_r56_004083a0();
    sk_r56_003e1da8(v3,(unsigned long)DAT_005a0078,l1);
    return;
}


/* sk_r56_003e3160 @ 0x003e3160   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e3160(unsigned long param_1, unsigned long param_2, unsigned long (*param_3)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned int v1;
    v1 = (*param_3)();
    /* WARNING: Could not recover jumptable at 0x003e31bc. Too many branches */ /* WARNING: Treating indirect jump as call */ ((unsigned long(*)())(ctx + 8))(v1 & 1);
    return;
}


/* sk_r56_003e31e8 @ 0x003e31e8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e31e8()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long * p2;
    unsigned long v3;
    unsigned long rx17;
    unsigned long r19;
    sk_r56_004070d8();
    sk_r56_0036a940(0x67d790,0x30,7);
    l1 = sk_r56_00407c3c();
    ctx[8] = (unsigned long)(l1);
    sk_r56_00406ce0(l1,ctx[4]);
    sk_r56_00377824(0);
    sk_r56_00408224();
    *(unsigned long *)((char*)l1 + 0x28) = (unsigned long)((unsigned long)((unsigned long)DAT_003fcf24));
    *(unsigned long *)((char*)l1 + 0x30) = (unsigned long)(r19);
    sk_r56_0040bb18(DAT_005a0064);
    p2 = (unsigned long *)sk_r56_00406fe0();
    ctx[9] = (unsigned long)(p2);
    *p2 = (unsigned long)(rx17);
    v3 = sk_r56_004083a0();
    sk_r56_003e262c(v3,(unsigned long)DAT_005a0088,l1);
    return;
}


/* sk_r56_003e32e4 @ 0x003e32e4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e32e4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long rx8;
    unsigned long v1;
    unsigned long v2;
    long l3;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    sk_r56_00407018();
    v1 = *(unsigned long *)((char*)rx8 + 0x40);
    v2 = *(unsigned long *)((char*)rx8 + 0x38);
    l3 = *ctx;
    sk_r56_0040bd24(*(unsigned long *)((char*)rx8 + 0x48));
    sk_r56_0036b118(v2);
    sk_r56_0040bd24(v1);
    /* WARNING: Could not recover jumptable at 0x003e33d4. Too many branches */ /* WARNING: Treating indirect jump as call */ ((unsigned long(*)())(l3 + 8))();
    return;
}


/* sk_r56_003e33d8 @ 0x003e33d8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e33d8()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned int v1;
    unsigned long (*pcVar2)();
    unsigned long in_x5;
    unsigned long r30;
    cL4_w16_t pair3;
    sk_r56_00084220();
    sk_r56_00406e34();
    pcVar2 = (unsigned long(*)())((unsigned long(*)())sk_r56_0016186c(in_x5));
    sk_r56_00350798();
    pair3.lo = sk_r56_00377824(); pair3.hi = 0;  /* x1 half */
    sk_r56_00350518(pair3.lo,pair3.hi,pair3.lo);
    v1 = (*pcVar2)();
    sk_r56_00084234(v1 & 1,r30);
    return;
}


/* sk_r56_003e3454 @ 0x003e3454   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e3454()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_00406574();
    sk_r56_003e3484();
    sk_r56_0036b270();
    return;
}


/* sk_r56_003e3484 @ 0x003e3484   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e3484()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_003e9df8();
    return;
}


/* sk_r56_003e34b4 @ 0x003e34b4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e34b4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long rx1;
    long rx8;
    long rx8_00;
    long rx8_01;
    long rx8_02;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    unsigned long rx16_02;
    sk_r56_00407000();
    sk_r56_00407214();
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[6] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[7] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[8] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[9] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[10] = (unsigned long)(v1);
    ctx[11] = (unsigned long)(*(unsigned long *)((char*)rx1 + 0x20));
    ctx[12] = (unsigned long)(*(unsigned long *)((char*)rx1 + 0x10));
    sk_r56_004069c4();
    sk_r56_00377824();
    sk_r56_00408454();
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[14] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[15] = (unsigned long)(rx16_01);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[16] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[17] = (unsigned long)(rx16_02);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_02 + 0x40));
    ctx[18] = (unsigned long)(v1);
    sk_r56_00407594();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e35ec @ 0x003e35ec   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e35ec()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned char b2;
    int i3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    cL4_w16_t pair6;
    v4 = sk_r56_00407ca0();
    sk_r56_0040700c();
    ctx[19] = (unsigned long)(ctx);
    i3 = *((int*)((char*)ctx[3] + 0x30));
    *((int*)ctx+0xc0) = i3;
    b2 = *((unsigned char*)((char*)ctx[4] + i3));
    *((unsigned char*)ctx+0xc4) = b2;
    if ((b2 & 1) != 0) {
        sk_r56_00407774();
        sk_r56_0040686c();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair6.lo,pair6.hi,v4);
        /* WARNING: Could not recover jumptable at 0x003e3678. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[12];
    sk_r56_0040652c();
    sk_r56_00406608();
    sk_r56_004068f4();
    sk_r56_00406268();
    sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[20] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    p5[1] = (unsigned long)((unsigned long)LAB_003e370c);
    sk_r56_00406ab4(ctx[16]);
    /* WARNING: Could not recover jumptable at 0x003e3708. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e37c8 @ 0x003e37c8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e37c8(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    int i2;
    unsigned long v3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx17;
    long l6;
    cL4_w16_t pair7;
    v3 = sk_r56_00407ca0();
    sk_r56_0040700c();
    sk_r56_00407aac();
    v4 = sk_r56_00406420();
    if (carry) {
        i2 = *((int*)((char*)ctx + 0xc0));
        l6 = ctx[4];
        sk_r56_0040711c(ctx[15],v4,ctx[14]);
        (*rx9)();
        *((unsigned char*)((char*)l6 + i2)) = 1;
        sk_r56_00407774();
        sk_r56_0040686c();
        sk_r56_0040bd24((long)i2);
        sk_r56_0040bd24(1);
        sk_r56_0040bd24(l6);
        pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair7.lo,pair7.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003e3868. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l6 = ctx[3];
    l1 = ctx[4];
    sk_r56_00406bd4(ctx[17],ctx[18]);
    (*rx9_00)();
    sk_r56_004062a8(*(unsigned long *)(l1 + *((int*)((char*)l6 + 0x2c))));
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[22] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    p5[1] = (unsigned long)((unsigned long)LAB_003e3908);
    sk_r56_00407824(ctx[8],ctx[18]);
    /* WARNING: Could not recover jumptable at 0x003e3904. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e3a14 @ 0x003e3a14   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e3a14()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    unsigned long * p4;
    unsigned long rx1;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx16)();
    unsigned long rx17;
    unsigned long v5;
    unsigned long v6;
    unsigned long v7;
    unsigned long (*r25)();
    cL4_w16_t pair8;
    v2 = sk_r56_0040790c();
    sk_r56_004070d8();
    v3 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[7],v3,ctx[6]);
        (*rx9)();
        if ((*((unsigned char*)ctx+0xc4) & 1) == 0) {
            l1 = ctx[12];
            sk_r56_0040652c();
            sk_r56_00406608();
            sk_r56_004068f4();
            sk_r56_00406268();
            sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
            p4 = (unsigned long *)sk_r56_00406fe0();
            ctx[20] = (unsigned long)(p4);
            *p4 = (unsigned long)(rx17);
            p4[1] = (unsigned long)((unsigned long)LAB_003e370c);
            sk_r56_00406ab4(ctx[16]);
            UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
            sk_r56_004080cc();
            /* WARNING: Could not recover jumptable at 0x003e3b88. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
            return;
        }
        v3 = 1;
    }
else {
        sk_r56_00407aa0();
        sk_r56_0011aa70();
        (*r25)();
        sk_r56_003504a0();
        (*r25)();
        sk_r56_00407bf8();
        v3 = rx1;
    }
    v5 = ctx[16];
    v6 = ctx[10];
    v7 = ctx[8];
    sk_r56_004075a4(ctx[2],v3);
    sk_r56_0040bd24(v5);
    sk_r56_0040bd24(v6);
    sk_r56_0040bd24(v7);
    pair8.lo = sk_r56_00406e64(); pair8.hi = 0;  /* x1 half */
    sk_r56_004079b4(pair8.lo,pair8.hi,v2);
    /* WARNING: Could not recover jumptable at 0x003e3af8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
    return;
}


/* sk_r56_003e3c80 @ 0x003e3c80   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e3c80()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long param_1; /* Swift-ABI register param */
    unsigned long param_2; /* Swift-ABI register param */
    unsigned long param_3; /* Swift-ABI register param */
    unsigned long param_4; /* Swift-ABI register param */
    unsigned long v1;
    long rx8;
    long rx8_00;
    long rx8_01;
    long rx8_02;
    long rx8_03;
    unsigned long (*rx8_04)();
    unsigned long rx8_05;
    unsigned long rx8_06;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    unsigned long rx16_02;
    unsigned long rx16_03;
    long r21;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    sk_r56_00406c1c();
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[8] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[9] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[10] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[11] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[12] = (unsigned long)(v1);
    ctx[13] = (unsigned long)(*(unsigned long *)((char*)param_4 + 0x20));
    ctx[14] = (unsigned long)(*(unsigned long *)((char*)param_4 + 0x10));
    v1 = sk_r56_0040684c();
    ctx[15] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[16] = (unsigned long)(rx16_01);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[17] = (unsigned long)(v1);
    v1 = sk_r56_00406dd0();
    ctx[18] = (unsigned long)(v1);
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[19] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[20] = (unsigned long)(rx16_02);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_02 + 0x40));
    ctx[21] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[22] = (unsigned long)(rx16_03);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_03 + 0x40));
    ctx[23] = (unsigned long)(v1);
    if (r21 == 0) {
        sk_r56_00407248();
        v1 = rx8_06;
    }
else {
        sk_r56_00406590();
        (*rx8_04)();
        sk_r56_0008e1ec();
        v1 = rx8_05;
    }
    ctx[24] = (unsigned long)(v1);
    *(unsigned long *)((char*)ctx + 200) = (unsigned long)(param_3);
    sk_r56_00353080();
    sk_r56_00407c78();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e3e28 @ 0x003e3e28   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e3e28()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned char b2;
    int i3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    cL4_w16_t pair6;
    v4 = sk_r56_00407c8c();
    sk_r56_0040700c();
    ctx[26] = (unsigned long)(ctx);
    i3 = *((int*)((char*)ctx[5] + 0x30));
    *((int*)((char*)ctx + 0x100)) = i3;
    b2 = *((unsigned char*)((char*)ctx[6] + i3));
    *((unsigned char*)ctx+0x104) = b2;
    if ((b2 & 1) != 0) {
        sk_r56_004076c4();
        sk_r56_0040686c();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407c78(pair6.lo,pair6.hi,v4);
        /* WARNING: Could not recover jumptable at 0x003e3ebc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[14];
    sk_r56_0040652c();
    v4 = sk_r56_00406608();
    ctx[27] = (unsigned long)(v4);
    v4 = sk_r56_00406e8c();
    ctx[28] = (unsigned long)(v4);
    sk_r56_00406288();
    sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[29] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    p5[1] = (unsigned long)((unsigned long)LAB_003e3f5c);
    sk_r56_004067b8(ctx[21]);
    sk_r56_00407990();
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e3f58. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e4048 @ 0x003e4048   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e4048(unsigned long param_1, unsigned long param_2, unsigned long (*UNRECOVERED_JUMPTABLE)())
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    int i2;
    unsigned long v3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long rx17;
    long l6;
    cL4_w16_t pair7;
    v3 = sk_r56_00407c8c();
    sk_r56_0040700c();
    v4 = sk_r56_00406420();
    if (carry) {
        i2 = *((int*)((char*)ctx + 0x100));
        l6 = ctx[6];
        sk_r56_0040711c(ctx[20],v4,ctx[19]);
        (*rx9)();
        *((unsigned char*)((char*)l6 + i2)) = 1;
        sk_r56_004076c4();
        sk_r56_0040686c();
        sk_r56_0040bd24((long)i2);
        sk_r56_0040bd24(1);
        sk_r56_0040bd24(l6);
        sk_r56_0040bd24();
        pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
        sk_r56_00407c78(pair7.lo,pair7.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003e40f4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l6 = ctx[5];
    l1 = ctx[6];
    sk_r56_00406bd4(ctx[22],ctx[23]);
    (*rx9_00)();
    sk_r56_004062a8(*(unsigned long *)(l1 + *((int*)((char*)l6 + 0x2c))));
    sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[30] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    p5[1] = (unsigned long)((unsigned long)LAB_003e4194);
    sk_r56_00408380(ctx[10],ctx[23]);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e4190. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e42c4 @ 0x003e42c4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e42c4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    unsigned long * p4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long (*rx9)();
    unsigned long (*rx16)();
    unsigned long rx17;
    unsigned long v5;
    unsigned long v6;
    unsigned long (*r25)();
    unsigned long v7;
    cL4_w16_t pair8;
    v2 = sk_r56_0040790c();
    sk_r56_004070d8();
    v3 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[9],v3,ctx[8]);
        v3 = (*rx9)();
        if ((*((unsigned char*)ctx+0x104) & 1) == 0) {
            l1 = ctx[14];
            sk_r56_0040652c();
            v2 = sk_r56_00406608();
            ctx[27] = (unsigned long)(v2);
            v2 = sk_r56_00406e8c();
            ctx[28] = (unsigned long)(v2);
            sk_r56_00406288();
            sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
            p4 = (unsigned long *)sk_r56_00406fe0();
            ctx[29] = (unsigned long)(p4);
            *p4 = (unsigned long)(rx17);
            p4[1] = (unsigned long)((unsigned long)LAB_003e3f5c);
            sk_r56_004067b8(ctx[21]);
            UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
            sk_r56_004080cc();
            /* WARNING: Could not recover jumptable at 0x003e4450. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
            return;
        }
        pair8.hi = 1;
        pair8.lo = v3;
    }
else {
        sk_r56_00407aa0();
        sk_r56_0011aa70();
        (*r25)();
        sk_r56_003504a0();
        (*r25)();
        pair8.lo = sk_r56_00407bf8(); pair8.hi = 0;  /* x1 half */
    }
    v3 = ctx[21];
    v5 = ctx[17];
    v6 = ctx[12];
    v7 = ctx[10];
    sk_r56_0040738c(pair8.lo,pair8.hi);
    sk_r56_004075a4();
    sk_r56_0040bd24(v3);
    sk_r56_0040bd24(v5);
    sk_r56_0040bd24(v6);
    sk_r56_0040bd24(v7);
    pair8.lo = sk_r56_00406e64(); pair8.hi = 0;  /* x1 half */
    sk_r56_004079b4(pair8.lo,pair8.hi,v2);
    /* WARNING: Could not recover jumptable at 0x003e43b0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
    return;
}


/* sk_r56_003e462c @ 0x003e462c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e462c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long * pl1;
    ctx[2] = (unsigned long)(param_4);
    pl1 = (long *)sk_r56_0040bb18(DAT_005a009c);
    ctx[3] = (unsigned long)(pl1);
    *pl1 = (unsigned long)(ctx);
    pl1[1] = (unsigned long)((long)(unsigned long)DAT_004060bc);
    sk_r56_003e3c80(pl1,param_1,param_2,param_3,param_5);
    return;
}


/* sk_r56_003e4700 @ 0x003e4700   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e4700()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_00406574();
    sk_r56_003e472c();
    sk_r56_0036b270();
    return;
}


/* sk_r56_003e472c @ 0x003e472c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e472c()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_003eaf4c();
    return;
}


/* sk_r56_003e4754 @ 0x003e4754   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e4754()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    long rx16;
    long r24;
    unsigned long r30;
    sk_r56_00084220();
    sk_r56_0040679c();
    sk_r56_00407450();
    l1 = sk_r56_003fd0bc();
    *((unsigned char*)((char*)r24 + *((int*)((char*)l1 + 0x28)))) = (unsigned char)(0);
    *((unsigned char*)((char*)r24 + *((int*)((char*)l1 + 0x2c)))) = (unsigned char)(0);
    sk_r56_0040654c();
    sk_r56_00350968();
    sk_r56_00377824();
    sk_r56_00349530();
    ((unsigned long(*)())(rx16 + 0x20))();
    sk_r56_00407ea0((long)*((int*)((char*)l1 + 0x24)));
    sk_r56_00084234(r30);
    return;
}


/* sk_r56_003e47d4 @ 0x003e47d4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e47d4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long rx8;
    long rx8_00;
    unsigned long rx16;
    unsigned long rx16_00;
    sk_r56_00407000();
    sk_r56_00406704();
    sk_r56_004079a8();
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[8] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[9] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[10] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[11] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[12] = (unsigned long)(v1);
    sk_r56_00407594();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e488c @ 0x003e488c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e488c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned char b2;
    int i3;
    unsigned long v4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long * rx8;
    unsigned long (*rx16)();
    unsigned long rx17;
    cL4_w16_t pair5;
    v4 = sk_r56_00407c8c();
    sk_r56_0040700c();
    ctx[13] = (unsigned long)(ctx);
    i3 = *((int*)((char*)ctx[3] + 0x28));
    *((int*)((char*)ctx + 0xa8)) = i3;
    b2 = *((unsigned char*)((char*)ctx[4] + i3));
    *((unsigned char*)ctx+0xb0) = b2;
    if ((b2 & 1) != 0) {
        sk_r56_00406f18();
        sk_r56_004081c0();
        sk_r56_0040bd24();
        pair5.lo = sk_r56_0040678c(); pair5.hi = 0;  /* x1 half */
        sk_r56_00407c78(pair5.lo,pair5.hi,v4);
        /* WARNING: Could not recover jumptable at 0x003e4900. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    i3 = *((int*)((char*)ctx[3] + 0x2c));
    *((int*)((char*)ctx + 0xac)) = i3;
    b2 = *((unsigned char*)((char*)ctx[4] + i3));
    l1 = ctx[6];
    sk_r56_0040652c();
    sk_r56_00406608();
    sk_r56_004068f4();
    sk_r56_00406268();
    sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
    sk_r56_00406fe0();
    if ((b2 & 1) == 0) {
        ctx[14] = (unsigned long)(rx8);
        *rx8 = (unsigned long)(rx17);
        rx8[1] = (unsigned long)((unsigned long)LAB_003e49bc);
        sk_r56_00407740();
    }
else {
        ctx[20] = (unsigned long)(rx8);
        *rx8 = (unsigned long)(rx17);
        rx8[1] = (unsigned long)((unsigned long)LAB_003e4dec);
        sk_r56_00407670();
    }
    sk_r56_00406ab4();
    UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e49b8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e4a78 @ 0x003e4a78   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e4a78()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long rx9_00;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long v5;
    cL4_w16_t pair6;
    v2 = sk_r56_00407ca0();
    sk_r56_0040700c();
    v5 = ctx[10];
    v3 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[9],v3,ctx[8]);
        (*rx9)();
        sk_r56_00406f18();
        sk_r56_004081c0();
        sk_r56_0040bd24(v5);
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair6.lo,pair6.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003e4af4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[3];
    sk_r56_00406894(ctx[11],ctx[12]);
    ctx[16] = (unsigned long)(rx9_00);
    ctx[17] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_01)();
    sk_r56_004062e8((long)*((int*)((char*)l1 + 0x24)));
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    ctx[18] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003e4b90);
    sk_r56_00406bb4(ctx[12]);
    /* WARNING: Could not recover jumptable at 0x003e4b8c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e4c70 @ 0x003e4c70   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e4c70()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned char b2;
    int i3;
    unsigned long v4;
    unsigned long v5;
    unsigned long v6;
    unsigned long v7;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long v8;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long * rx8;
    unsigned long (*rx9)();
    unsigned long (*rx16)();
    unsigned long rx17;
    cL4_w16_t pair9;
    v4 = sk_r56_00407c8c();
    sk_r56_0040700c();
    if ((*((unsigned char*)ctx+0xb1) & 1) == 0) {
        UNRECOVERED_JUMPTABLE = (unsigned long(*)())((unsigned long(*)())ctx[16]);
        v5 = ctx[17];
        v7 = ctx[12];
        v8 = ctx[7];
        v6 = ctx[2];
        *((unsigned char*)((char*)ctx[4] + (long)*((int*)ctx+0xac))) = (unsigned char)(1);
        (*UNRECOVERED_JUMPTABLE)(v5,v6,v7,v8);
        pair9.lo = sk_r56_00407bf8(); pair9.hi = 0;  /* x1 half */
    }
else {
        sk_r56_00407cd4();
        v5 = (*rx9)();
        if ((*((unsigned char*)ctx+0xb0) & 1) == 0) {
            i3 = *((int*)((char*)ctx[3] + 0x2c));
            *((int*)ctx+0xac) = i3;
            b2 = *((unsigned char*)((char*)ctx[4] + i3));
            l1 = ctx[6];
            sk_r56_0040652c();
            sk_r56_00406608();
            sk_r56_004068f4();
            sk_r56_00406268();
            sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
            sk_r56_00406fe0();
            if ((b2 & 1) == 0) {
                ctx[14] = (unsigned long)(rx8);
                *rx8 = (unsigned long)(rx17);
                rx8[1] = (unsigned long)((unsigned long)LAB_003e49bc);
                sk_r56_00407740();
            }
        else {
                ctx[20] = (unsigned long)(rx8);
                *rx8 = (unsigned long)(rx17);
                rx8[1] = (unsigned long)((unsigned long)LAB_003e4dec);
                sk_r56_00407670();
            }
            sk_r56_00406ab4();
            UNRECOVERED_JUMPTABLE = (unsigned long(*)())(rx16);
            sk_r56_00407c78();
            /* WARNING: Could not recover jumptable at 0x003e4de8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
            return;
        }
        pair9.hi = 1;
        pair9.lo = v5;
    }
    pair9.lo = sk_r56_0040738c(pair9.lo,pair9.hi); pair9.hi = 0;  /* x1 half */
    sk_r56_000839d8(pair9.lo,pair9.hi,1);
    v5 = ctx[10];
    sk_r56_0040bd24(ctx[12]);
    sk_r56_0040bd24(v5);
    pair9.lo = sk_r56_00406e64(); pair9.hi = 0;  /* x1 half */
    sk_r56_00407c78(pair9.lo,pair9.hi,v4);
    /* WARNING: Could not recover jumptable at 0x003e4d2c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
    return;
}


/* sk_r56_003e4f34 @ 0x003e4f34   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e4f34()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long param_1; /* Swift-ABI register param */
    unsigned long param_2; /* Swift-ABI register param */
    unsigned long param_3; /* Swift-ABI register param */
    unsigned long param_4; /* Swift-ABI register param */
    unsigned long v1;
    long rx8;
    long rx8_00;
    long rx8_01;
    unsigned long (*rx8_02)();
    unsigned long rx8_03;
    unsigned long rx8_04;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    long r21;
    unsigned long r25;
    sk_r56_00408058();
    sk_r56_0040700c();
    sk_r56_00406c1c();
    ctx[8] = (unsigned long)(*(unsigned long *)((char*)param_4 + 0x10));
    v1 = sk_r56_0040684c();
    ctx[9] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[10] = (unsigned long)(rx16);
    v1 = sk_r56_0040859c(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[11] = (unsigned long)(v1);
    v1 = sk_r56_0040bb18(r25 & 0xfffffffffffffff0);
    ctx[12] = (unsigned long)(v1);
    sk_r56_00406dd0();
    sk_r56_00408454();
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[14] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[15] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[16] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[17] = (unsigned long)(rx16_01);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[18] = (unsigned long)(v1);
    if (r21 == 0) {
        sk_r56_00407248();
        v1 = rx8_04;
    }
else {
        sk_r56_00406590();
        (*rx8_02)();
        sk_r56_0008e1ec();
        v1 = rx8_03;
    }
    ctx[19] = (unsigned long)(v1);
    ctx[20] = (unsigned long)(param_3);
    sk_r56_00353080();
    sk_r56_00408044();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e5074 @ 0x003e5074   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e5074()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    unsigned long v2;
    unsigned char b3;
    int i4;
    unsigned long v5;
    long l6;
    unsigned long * p7;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    unsigned long rx17_00;
    cL4_w16_t pair8;
    v5 = sk_r56_00407c8c();
    sk_r56_0040700c();
    ctx[21] = (unsigned long)(ctx);
    i4 = *((int*)((char*)ctx[5] + 0x28));
    *((int*)ctx+0x100) = i4;
    b3 = *((unsigned char*)((char*)ctx[6] + i4));
    *((unsigned char*)ctx+0x108) = b3;
    if ((b3 & 1) != 0) {
        sk_r56_00350744(ctx[2]);
        sk_r56_000839d8();
        sk_r56_004081d8();
        v1 = ctx[11];
        v2 = ctx[12];
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24(v2);
        sk_r56_0040bd24(v1);
        pair8.lo = sk_r56_0040678c(); pair8.hi = 0;  /* x1 half */
        sk_r56_00407c78(pair8.lo,pair8.hi,v5);
        /* WARNING: Could not recover jumptable at 0x003e510c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    i4 = *((int*)((char*)ctx[5] + 0x2c));
    *((int*)ctx+0x104) = i4;
    b3 = *((unsigned char*)((char*)ctx[6] + i4));
    v5 = ctx[7];
    sk_r56_004083d8();
    sk_r56_004083c0();
    sk_r56_003504a0();
    sk_r56_00377824();
    sk_r56_00350968(v5);
    v5 = sk_r56_00377bec();
    if ((b3 & 1) == 0) {
        ctx[22] = (unsigned long)(v5);
        l6 = sk_r56_003fcc4c(v5);
        sk_r56_00350798();
        v5 = sk_r56_00377dcc();
        ctx[23] = (unsigned long)(v5);
        sk_r56_004065e8();
        sk_r56_0040bb18(*((int*)((char*)l6 + 4)));
        p7 = (unsigned long *)sk_r56_00406fe0();
        ctx[24] = (unsigned long)(p7);
        *p7 = (unsigned long)(rx17_00);
        sk_r56_00407da0();
        v5 = sk_r56_00407164();
    }
else {
        ctx[29] = (unsigned long)(v5);
        l6 = sk_r56_003fcc4c(v5);
        sk_r56_00350798();
        v5 = sk_r56_00377dcc();
        ctx[30] = (unsigned long)(v5);
        sk_r56_004065e8();
        sk_r56_0040bb18(*((int*)((char*)l6 + 4)));
        p7 = (unsigned long *)sk_r56_00406fe0();
        ctx[31] = (unsigned long)(p7);
        *p7 = (unsigned long)(rx17);
        p7[1] = (unsigned long)((unsigned long)LAB_003e57c0);
        sk_r56_00407164();
        v5 = ctx[2];
    }
    sk_r56_00407990(v5);
    sk_r56_00407c78();
    /* WARNING: Could not recover jumptable at 0x003e526c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e535c @ 0x003e535c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e535c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    unsigned long v4;
    long * pl5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long rx9_00;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    cL4_w16_t pair6;
    v3 = sk_r56_00407ca0();
    sk_r56_0040700c();
    sk_r56_00407aac();
    v4 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[15],v4,ctx[14]);
        (*rx9)();
        sk_r56_00350744(ctx[2]);
        sk_r56_000839d8();
        sk_r56_004081d8();
        v4 = ctx[11];
        v2 = ctx[12];
        sk_r56_0040bd24();
        sk_r56_0040bd24();
        sk_r56_0040bd24(v2);
        sk_r56_0040bd24(v4);
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair6.lo,pair6.hi,v3);
        /* WARNING: Could not recover jumptable at 0x003e53f8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[5];
    sk_r56_00406894(ctx[17],ctx[18]);
    *(unsigned long *)((char*)ctx + 200) = (unsigned long)(rx9_00);
    ctx[26] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_01)();
    sk_r56_004062e8((long)*((int*)((char*)l1 + 0x24)));
    pl5 = (long *)sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    ctx[27] = (unsigned long)(pl5);
    *pl5 = (unsigned long)(ctx);
    pl5[1] = (unsigned long)((long)(unsigned long)LAB_003e5494);
    sk_r56_00406bb4(ctx[18]);
    /* WARNING: Could not recover jumptable at 0x003e5490. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e557c @ 0x003e557c   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e557c()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*pcVar1)();
    unsigned char b2;
    int i3;
    unsigned long v4;
    unsigned long v5;
    long l6;
    unsigned long * p7;
    unsigned long v8;
    unsigned long rx1;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long v9;
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    unsigned long rx17_00;
    unsigned long v10;
    cL4_w16_t pair11;
    v4 = sk_r56_00407c8c();
    sk_r56_0040700c();
    if ((*((unsigned char*)ctx+0x109) & 1) == 0) {
        pcVar1 = (unsigned long(*)())((unsigned long(*)())*(unsigned long*)((char*)(ctx + 200)));
        v8 = ctx[26];
        v10 = ctx[18];
        v9 = ctx[13];
        v5 = ctx[2];
        *((unsigned char*)((char*)ctx[6] + (long)*((int*)ctx+0x104))) = (unsigned char)(1);
        (*pcVar1)(v8,v5,v10,v9);
        sk_r56_00407bf8();
        v8 = rx1;
    }
else {
        ((unsigned long(*)())(ctx[17] + 8))(ctx[18],ctx[13]);
        if ((*((unsigned char*)ctx+0x108) & 1) == 0) {
            i3 = *((int*)((char*)ctx[5] + 0x2c));
            *((int*)ctx+0x104) = i3;
            b2 = *((unsigned char*)((char*)ctx[6] + i3));
            v4 = ctx[7];
            sk_r56_004083d8();
            sk_r56_004083c0();
            sk_r56_003504a0();
            sk_r56_00377824();
            sk_r56_00350968(v4);
            v4 = sk_r56_00377bec();
            if ((b2 & 1) == 0) {
                ctx[22] = (unsigned long)(v4);
                l6 = sk_r56_003fcc4c(v4);
                sk_r56_00350798();
                v4 = sk_r56_00377dcc();
                ctx[23] = (unsigned long)(v4);
                sk_r56_004065e8();
                sk_r56_0040bb18(*((int*)((char*)l6 + 4)));
                p7 = (unsigned long *)sk_r56_00406fe0();
                ctx[24] = (unsigned long)(p7);
                *p7 = (unsigned long)(rx17_00);
                sk_r56_00407da0();
                v4 = sk_r56_00407164();
            }
        else {
                ctx[29] = (unsigned long)(v4);
                l6 = sk_r56_003fcc4c(v4);
                sk_r56_00350798();
                v4 = sk_r56_00377dcc();
                ctx[30] = (unsigned long)(v4);
                sk_r56_004065e8();
                sk_r56_0040bb18(*((int*)((char*)l6 + 4)));
                p7 = (unsigned long *)sk_r56_00406fe0();
                ctx[31] = (unsigned long)(p7);
                *p7 = (unsigned long)(rx17);
                p7[1] = (unsigned long)((unsigned long)LAB_003e57c0);
                sk_r56_00407164();
                v4 = ctx[2];
            }
            sk_r56_00407990(v4);
            sk_r56_00407c78();
            /* WARNING: Could not recover jumptable at 0x003e57bc. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
            return;
        }
        v8 = 1;
    }
    sk_r56_000839d8(ctx[2],v8,1,ctx[13]);
    v10 = ctx[16];
    v8 = ctx[11];
    v5 = ctx[12];
    sk_r56_0040bd24(ctx[18]);
    sk_r56_0040bd24(v10);
    sk_r56_0040bd24(v5);
    sk_r56_0040bd24(v8);
    pair11.lo = sk_r56_00406e64(); pair11.hi = 0;  /* x1 half */
    sk_r56_00407c78(pair11.lo,pair11.hi,v4);
    /* WARNING: Could not recover jumptable at 0x003e5658. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
    return;
}


/* sk_r56_003e5b18 @ 0x003e5b18   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e5b18(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long * pl1;
    ctx[2] = (unsigned long)(param_4);
    pl1 = (long *)sk_r56_0040bb18(DAT_005a00ac);
    ctx[3] = (unsigned long)(pl1);
    *pl1 = (unsigned long)(ctx);
    pl1[1] = (unsigned long)((long)(unsigned long)DAT_004060bc);
    sk_r56_003e4f34(pl1,param_1,param_2,param_3,param_5);
    return;
}


/* sk_r56_003e5bec @ 0x003e5bec   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e5bec()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_00406574();
    sk_r56_003e5c18();
    sk_r56_0036b270();
    return;
}


/* sk_r56_003e5c18 @ 0x003e5c18   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e5c18()  /* unspecified-params: Swift-ABI callee, args/arity from call sites */
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    sk_r56_003eaf4c();
    return;
}


/* sk_r56_003e5c30 @ 0x003e5c30   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e5c30(unsigned long param_1, long param_2)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long rx16;
    sk_r56_0040654c(param_2,*(unsigned long *)((char*)param_2 + 0x18),*(unsigned long *)((char*)param_2 + 0x10));
    sk_r56_00377824();
    sk_r56_00350404();
    /* WARNING: Could not recover jumptable at 0x003e5c80. Too many branches */ /* WARNING: Treating indirect jump as call */ ((unsigned long(*)())(rx16 + 0x10))(param_1);
    return;
}


/* sk_r56_003e5d50 @ 0x003e5d50   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e5d50()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long rx8;
    long rx8_00;
    unsigned long rx16;
    unsigned long rx16_00;
    sk_r56_00407000();
    sk_r56_00406704();
    sk_r56_004079a8();
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[8] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[9] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[10] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[11] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[12] = (unsigned long)(v1);
    sk_r56_00407594();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e5e08 @ 0x003e5e08   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e5e08()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned char b2;
    int i3;
    unsigned long v4;
    unsigned long * p5;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    cL4_w16_t pair6;
    v4 = sk_r56_00407ca0();
    sk_r56_0040700c();
    ctx[13] = (unsigned long)(ctx);
    i3 = *((int*)((char*)ctx[3] + 0x28));
    *((int*)ctx+0xa0) = i3;
    b2 = *((unsigned char*)((char*)ctx[4] + i3));
    *((unsigned char*)ctx+0xa4) = b2;
    if ((b2 & 1) != 0) {
        sk_r56_00407604();
        sk_r56_0040686c();
        sk_r56_0040bd24();
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair6.lo,pair6.hi,v4);
        /* WARNING: Could not recover jumptable at 0x003e5e80. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[6];
    sk_r56_0040652c();
    sk_r56_00406608();
    sk_r56_004068f4();
    sk_r56_00406268();
    sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
    p5 = (unsigned long *)sk_r56_00406fe0();
    ctx[14] = (unsigned long)(p5);
    *p5 = (unsigned long)(rx17);
    sk_r56_004074c4();
    sk_r56_00406ab4();
    /* WARNING: Could not recover jumptable at 0x003e5f08. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e5fc8 @ 0x003e5fc8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e5fc8()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long rx9_00;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long v5;
    cL4_w16_t pair6;
    v2 = sk_r56_00407ca0();
    sk_r56_0040700c();
    v5 = ctx[7];
    v3 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[9],v3,ctx[8]);
        (*rx9)();
        sk_r56_00407604();
        sk_r56_0040686c();
        sk_r56_0040bd24(v5);
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair6.lo,pair6.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003e6048. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[3];
    sk_r56_00406894(ctx[11],ctx[12]);
    ctx[16] = (unsigned long)(rx9_00);
    ctx[17] = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_01)();
    sk_r56_004062e8((long)*((int*)((char*)l1 + 0x24)));
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    ctx[18] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003e60e4);
    sk_r56_00406bb4(ctx[12]);
    /* WARNING: Could not recover jumptable at 0x003e60e0. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e61c4 @ 0x003e61c4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e61c4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long * p3;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*rx9)();
    unsigned long (*rx9_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    unsigned long v4;
    cL4_w16_t pair5;
    v2 = sk_r56_00407ca0();
    sk_r56_0040700c();
    if ((*((unsigned char*)ctx+0xa5) & 1) == 0) {
        sk_r56_00407cd4();
        v4 = (*rx9_00)();
        if ((*((unsigned char*)ctx+0xa4) & 1) == 0) {
            l1 = ctx[6];
            sk_r56_0040652c();
            sk_r56_00406608();
            sk_r56_004068f4();
            sk_r56_00406268();
            sk_r56_0040bb18(*((int*)((char*)l1 + 4)));
            p3 = (unsigned long *)sk_r56_00406fe0();
            ctx[14] = (unsigned long)(p3);
            *p3 = (unsigned long)(rx17);
            sk_r56_004074c4();
            sk_r56_00406ab4();
            /* WARNING: Could not recover jumptable at 0x003e62e8. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
            return;
        }
        pair5.hi = 1;
        pair5.lo = v4;
    }
else {
        sk_r56_00407d14(ctx[17]);
        (*rx9)();
        pair5.lo = sk_r56_00407bf8(); pair5.hi = 0;  /* x1 half */
    }
    v4 = ctx[10];
    sk_r56_0040738c(pair5.lo,pair5.hi);
    sk_r56_004075a4();
    sk_r56_0040bd24(v4);
    pair5.lo = sk_r56_00406e64(); pair5.hi = 0;  /* x1 half */
    sk_r56_00407e58(pair5.lo,pair5.hi,v2);
    /* WARNING: Could not recover jumptable at 0x003e6260. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
    return;
}


/* sk_r56_003e62ec @ 0x003e62ec   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e62ec()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    sk_r56_00407000();
    sk_r56_00408038();
    sk_r56_0040bd24();
    sk_r56_00407128();
    /* WARNING: Could not recover jumptable at 0x003e633c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e63a8 @ 0x003e63a8   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e63a8(unsigned long param_1, unsigned long param_2, unsigned long param_3, long param_4)
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long rx8;
    long rx8_00;
    long rx8_01;
    unsigned long (*rx8_02)();
    unsigned long rx8_03;
    unsigned long rx8_04;
    unsigned long rx16;
    unsigned long rx16_00;
    unsigned long rx16_01;
    long r21;
    sk_r56_00407c8c();
    sk_r56_0040700c();
    sk_r56_00406c1c();
    ctx[8] = (unsigned long)(*(unsigned long *)((char*)param_4 + 0x10));
    v1 = sk_r56_0040684c();
    ctx[9] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[10] = (unsigned long)(rx16);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8 + 0x40));
    ctx[11] = (unsigned long)(v1);
    v1 = sk_r56_00406dd0();
    ctx[12] = (unsigned long)(v1);
    sk_r56_00350798();
    v1 = sk_r56_00310d68();
    ctx[13] = (unsigned long)(v1);
    sk_r56_00352018();
    ctx[14] = (unsigned long)(rx16_00);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_00 + 0x40));
    ctx[15] = (unsigned long)(v1);
    sk_r56_0040683c();
    ctx[16] = (unsigned long)(rx16_01);
    v1 = sk_r56_004078e8(*(unsigned long *)((char*)rx8_01 + 0x40));
    ctx[17] = (unsigned long)(v1);
    if (r21 == 0) {
        sk_r56_00407248();
        v1 = rx8_04;
    }
else {
        sk_r56_00406590();
        (*rx8_02)();
        sk_r56_0008e1ec();
        v1 = rx8_03;
    }
    ctx[18] = (unsigned long)(v1);
    ctx[19] = (unsigned long)(param_3);
    sk_r56_00353080();
    sk_r56_00407c78();
    sk_r56_00408db8();
    return;
}


/* sk_r56_003e64e0 @ 0x003e64e0   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e64e0()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    unsigned long v1;
    long l2;
    unsigned char b3;
    int i4;
    unsigned long v5;
    unsigned long * p6;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    unsigned long rx17;
    cL4_w16_t pair7;
    v5 = sk_r56_00407ca0();
    sk_r56_0040700c();
    ctx[20] = (unsigned long)(ctx);
    i4 = *((int*)((char*)ctx[5] + 0x28));
    *((int*)((char*)ctx + 0xe0)) = i4;
    b3 = *((unsigned char*)((char*)ctx[6] + i4));
    *((unsigned char*)ctx+0xe4) = b3;
    if ((b3 & 1) != 0) {
        sk_r56_00407960();
        v1 = ctx[11];
        sk_r56_0040686c();
        sk_r56_0040bd24();
        sk_r56_0040bd24(v1);
        pair7.lo = sk_r56_0040678c(); pair7.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair7.lo,pair7.hi,v5);
        /* WARNING: Could not recover jumptable at 0x003e6560. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l2 = ctx[8];
    sk_r56_0040652c();
    sk_r56_00406608();
    sk_r56_004083cc();
    v5 = sk_r56_00406e8c();
    ctx[22] = (unsigned long)(v5);
    sk_r56_00406288();
    sk_r56_0040bb18(*((int*)((char*)l2 + 4)));
    p6 = (unsigned long *)sk_r56_00406fe0();
    ctx[23] = (unsigned long)(p6);
    *p6 = (unsigned long)(rx17);
    sk_r56_00407830();
    sk_r56_004067b8();
    /* WARNING: Could not recover jumptable at 0x003e65f4. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}


/* sk_r56_003e66e4 @ 0x003e66e4   (est. Swift-runtime message/notification dispatch helper)
 * Reconstructs the determinable call/store sequence; register-carried values
 * (extraout_*, in_x*) and unrecovered indirect jump targets are documented artifacts.
 * Confidence: low (decompiler degraded register/indirect-dispatch reconstruction). */
void sk_r56_003e66e4()
{
    unsigned long *ctx; /* per-message context record (x22) */
    int carry = 0;  /* NZCV carry flag result of preceding test */
    long l1;
    unsigned long v2;
    unsigned long v3;
    long * pl4;
    unsigned long (*UNRECOVERED_JUMPTABLE_00)();
    unsigned long (*UNRECOVERED_JUMPTABLE)();
    long rx8;
    unsigned long (*rx9)();
    unsigned long rx9_00;
    unsigned long (*rx9_01)();
    unsigned long rx10;
    unsigned long v5;
    cL4_w16_t pair6;
    v2 = sk_r56_00407ca0();
    sk_r56_0040700c();
    v5 = ctx[12];
    v3 = sk_r56_00406420();
    if (carry) {
        sk_r56_0040711c(ctx[14],v3,ctx[13]);
        (*rx9)();
        sk_r56_00407960();
        v3 = ctx[11];
        sk_r56_0040686c();
        sk_r56_0040bd24(v5);
        sk_r56_0040bd24(v3);
        pair6.lo = sk_r56_0040678c(); pair6.hi = 0;  /* x1 half */
        sk_r56_00407e58(pair6.lo,pair6.hi,v2);
        /* WARNING: Could not recover jumptable at 0x003e676c. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE_00)();
        return;
    }
    l1 = ctx[5];
    sk_r56_00406894(ctx[16],ctx[17]);
    ctx[24] = (unsigned long)(rx9_00);
    *(unsigned long *)((char*)ctx + 200) = (unsigned long)(rx10);
    sk_r56_00350624();
    (*rx9_01)();
    sk_r56_004062e8((long)*((int*)((char*)l1 + 0x24)));
    pl4 = (long *)sk_r56_0040bb18(*((int*)((char*)rx8 + 4)));
    ctx[26] = (unsigned long)(pl4);
    *pl4 = (unsigned long)(ctx);
    pl4[1] = (unsigned long)((long)(unsigned long)LAB_003e6808);
    sk_r56_00406bb4(ctx[17]);
    /* WARNING: Could not recover jumptable at 0x003e6804. Too many branches */ /* WARNING: Treating indirect jump as call */ (*UNRECOVERED_JUMPTABLE)();
    return;
}
