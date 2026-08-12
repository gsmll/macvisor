/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SK192 slice (0x0041a048-0x0042aec8): cL4 capability/object operation dispatch
 * plus embedded Swift Unicode Script/Block name classifiers. Operation decoding
 * uses 11-word descriptors with a command selector at offset [10].
 *
 * 0x004207b0 / 0x00424280 are the Swift _Unicode Script / Unicode Block name→code
 * lookups (flattened by the decompiler into huge if/else chains, rendered as
 * faithful tag→code tables below).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef void (*code_t)(void);
typedef struct { word_t lo, hi, w2; byte bytes[16]; } sk16_t;
typedef sk16_t sk12_t;
#define SK192_FATAL(a) __builtin_trap()
#define sk_trap(...) ((word_t)0)

/* Shared cL4 / Swift-runtime externs (ground-truth FUN_ addresses). Variadic so the
 * reconstructed call sites type-check under -fsyntax-only. */
extern word_t sk_h_00002534();
extern word_t sk_h_00002818();
extern word_t sk_h_00002874();
extern word_t sk_h_0001d4f4();
extern word_t sk_h_0006a374();
extern word_t sk_h_0006b42c();
extern word_t sk_h_0006b6a0();
extern word_t sk_h_0006b6f4();
extern word_t sk_h_0006e064();
extern word_t sk_h_000722b0();
extern word_t sk_h_00077894();
extern word_t sk_h_0007c1c4();
extern word_t sk_h_0008409c();
extern word_t sk_h_00084180();
extern word_t sk_h_00084220();
extern word_t sk_h_00084234();
extern word_t sk_h_0008e500();
extern word_t sk_h_0008e518();
extern word_t sk_h_0009461c();
extern word_t sk_h_000a6f68();
extern word_t sk_h_000a6fe0();
extern word_t sk_h_000b06a4();
extern word_t sk_h_000b4390();
extern word_t sk_h_000b43d0();
extern word_t sk_h_000b43e8();
extern word_t sk_h_000b4594();
extern word_t sk_h_000b45b0();
extern word_t sk_h_000b4660();
extern word_t sk_h_000bb268();
extern word_t sk_h_000dbd0c();
extern word_t sk_h_000dbed0();
extern word_t sk_h_000e15d8();
extern word_t sk_h_00100c04();
extern word_t sk_h_00100e34();
extern word_t sk_h_00100efc();
extern word_t sk_h_00117cc4();
extern word_t sk_h_001a6a8c();
extern word_t sk_h_001a84f4();
extern word_t sk_h_001a8564();
extern word_t sk_h_001ae8a8();
extern word_t sk_h_001afa84();
extern word_t sk_h_001b28d4();
extern word_t sk_h_001b9084();
extern word_t sk_h_001bc440();
extern word_t sk_h_001ed960();
extern word_t sk_h_00208418();
extern word_t sk_h_002298d4();
extern word_t sk_h_00229a3c();
extern word_t sk_h_00268540();
extern word_t sk_h_0029d3d8();
extern word_t sk_h_0029fb80();
extern word_t sk_h_002a0cf8();
extern word_t sk_h_002a3e64();
extern word_t sk_h_002a4ab4();
extern word_t sk_h_002a9ba8();
extern word_t sk_h_002ab388();
extern word_t sk_h_002abcb0();
extern word_t sk_h_002acbb8();
extern word_t sk_h_002ad78c();
extern word_t sk_h_002b3b50();
extern word_t sk_h_002b3f40();
extern word_t sk_h_002b439c();
extern word_t sk_h_002b5e10();
extern word_t sk_h_002b74c0();
extern word_t sk_h_002bc2dc();
extern word_t sk_h_002cb61c();
extern word_t sk_h_003207d4();
extern word_t sk_h_00349a18();
extern word_t sk_h_0034bd90();
extern word_t sk_h_0034c444();
extern word_t sk_h_0034d868();
extern word_t sk_h_0034ecc8();
extern word_t sk_h_00350470();
extern word_t sk_h_00350518();
extern word_t sk_h_0035053c();
extern word_t sk_h_00350560();
extern word_t sk_h_003505c4();
extern word_t sk_h_003505e8();
extern word_t sk_h_00350624();
extern word_t sk_h_00350738();
extern word_t sk_h_003507e0();
extern word_t sk_h_00350914();
extern word_t sk_h_00350944();
extern word_t sk_h_00350980();
extern word_t sk_h_0035098c();
extern word_t sk_h_003509ec();
extern word_t sk_h_00350a04();
extern word_t sk_h_00350b18();
extern word_t sk_h_00350b54();
extern word_t sk_h_00350c5c();
extern word_t sk_h_00351100();
extern word_t sk_h_003511f0();
extern word_t sk_h_00351274();
extern word_t sk_h_003512c0();
extern word_t sk_h_003514e8();
extern word_t sk_h_00351a5c();
extern word_t sk_h_00351aec();
extern word_t sk_h_00351b38();
extern word_t sk_h_00351b78();
extern word_t sk_h_00351d30();
extern word_t sk_h_00351da8();
extern word_t sk_h_00351db4();
extern word_t sk_h_00351dc0();
extern word_t sk_h_00351e08();
extern word_t sk_h_00351e20();
extern word_t sk_h_003523fc();
extern word_t sk_h_00352498();
extern word_t sk_h_003524a4();
extern word_t sk_h_0035292c();
extern word_t sk_h_003534e0();
extern word_t sk_h_003535a8();
extern word_t sk_h_00353b10();
extern word_t sk_h_00353bc4();
extern word_t sk_h_003544c8();
extern word_t sk_h_00354744();
extern word_t sk_h_00354828();
extern word_t sk_h_003552a0();
extern word_t sk_h_00355a58();
extern word_t sk_h_00355d90();
extern word_t sk_h_003567c8();
extern word_t sk_h_00356c6c();
extern word_t sk_h_00356f80();
extern word_t sk_h_00356f9c();
extern word_t sk_h_003593c0();
extern word_t sk_h_0035aba4();
extern word_t sk_h_0036a940();
extern word_t sk_h_0036b118();
extern word_t sk_h_0036b270();
extern word_t sk_h_003a25d4();
extern word_t sk_h_003a25e0();
extern word_t sk_h_003f8224();
extern word_t sk_h_004080b0();
extern word_t sk_h_0041001c();
extern word_t sk_h_00410414();
extern word_t sk_h_00411290();
extern word_t sk_h_00411308();
extern word_t sk_h_004114fc();
extern word_t sk_h_00412d5c();
extern word_t sk_h_00415430();
extern word_t sk_h_00415b00();
extern word_t sk_h_0042ec68();
extern word_t sk_h_00448fd0();
extern word_t sk_h_0044929c();
extern word_t sk_h_0044bd08();
extern word_t sk_h_0044ca60();
extern word_t sk_h_00455f60();
extern word_t sk_h_004562f0();
extern word_t sk_h_0045636c();
extern word_t sk_h_00456858();
extern word_t sk_h_004578dc();
extern word_t sk_h_00457994();
extern word_t sk_h_00457ae8();
extern word_t sk_h_0045811c();
extern word_t sk_h_00458278();
extern word_t sk_h_00458c98();
extern word_t sk_h_00458cb8();
extern word_t sk_h_00458cd4();
extern word_t sk_h_00458d78();
extern word_t sk_h_00458da0();
extern word_t sk_h_00458e28();
extern word_t sk_h_00458e80();
extern word_t sk_h_0045908c();
extern word_t sk_h_004590e0();
extern word_t sk_h_00460d94();
extern word_t sk_h_00460e78();
extern word_t sk_h_00460f38();
extern word_t sk_h_0046134c();
extern word_t sk_h_004613d4();
extern word_t sk_h_00461430();
extern word_t sk_h_00462728();
extern word_t sk_h_00462898();
extern word_t sk_h_00462928();
extern word_t sk_h_0046299c();
extern word_t sk_h_004629f4();
extern word_t sk_h_00462a70();
extern word_t sk_h_00462adc();
extern word_t sk_h_00462b6c();
extern word_t sk_h_00462bc0();
extern word_t sk_h_00462c18();
extern word_t sk_h_00462c30();
extern word_t sk_h_00462c48();
extern word_t sk_h_00462c58();
extern word_t sk_h_00462c6c();
extern word_t sk_h_00462cc0();
extern word_t sk_h_00462d34();
extern word_t sk_h_00462d5c();
extern word_t sk_h_00462d70();
extern word_t sk_h_00462da8();
extern word_t sk_h_00462dbc();
extern word_t sk_h_00462dd0();
extern word_t sk_h_00462de4();
extern word_t sk_h_00462df8();
extern word_t sk_h_00462e0c();
extern word_t sk_h_00462e1c();
extern word_t sk_h_00462e30();
extern word_t sk_h_00462e74();
extern word_t sk_h_00462e9c();
extern word_t sk_h_00462ec0();
extern word_t sk_h_00462ef8();
extern word_t sk_h_00462fac();
extern word_t sk_h_004630c4();
extern word_t sk_h_004630f4();
extern word_t sk_h_00463108();
extern word_t sk_h_0046311c();
extern word_t sk_h_00463180();
extern word_t sk_h_004631bc();
extern word_t sk_h_004631d0();
extern word_t sk_h_004631e4();
extern word_t sk_h_00463210();
extern word_t sk_h_00463240();
extern word_t sk_h_00463254();
extern word_t sk_h_004632a4();
extern word_t sk_h_004632f4();
extern word_t sk_h_0046330c();
extern word_t sk_h_00463320();
extern word_t sk_h_00463334();
extern word_t sk_h_004633b8();
extern word_t sk_h_004633cc();
extern word_t sk_h_004633f4();
extern word_t sk_h_00463418();
extern word_t sk_h_00463474();
extern word_t sk_h_004634a4();
extern word_t sk_h_004634e4();
extern word_t sk_h_00463514();
extern word_t sk_h_00463540();
extern word_t sk_h_00463558();
extern word_t sk_h_00463570();
extern word_t sk_h_0046357c();
extern word_t sk_h_004635b8();
extern word_t sk_h_00463600();
extern word_t sk_h_00463638();
extern word_t sk_h_00463708();
extern word_t sk_h_0046378c();
extern word_t sk_h_004637a0();
extern word_t sk_h_004637b4();
extern word_t sk_h_004637dc();
extern word_t sk_h_00463858();
extern word_t sk_h_00463878();
extern word_t sk_h_00463998();
extern word_t sk_h_00463a28();
extern word_t sk_h_00463a88();
extern word_t sk_h_00463ab8();
extern word_t sk_h_00463ac8();
extern word_t sk_h_00463af8();
extern word_t sk_h_00463bc8();
extern word_t sk_h_00463dc8();
extern word_t sk_h_00463df8();
extern word_t sk_h_00463f58();
extern word_t sk_h_00463fa0();
extern word_t sk_h_00463fe8();
extern word_t sk_h_00463ff4();
extern word_t sk_h_00464034();
extern word_t sk_h_0046411c();
extern word_t sk_h_00464128();
extern word_t sk_h_00464158();
extern word_t sk_h_00464180();
extern word_t sk_h_004641fc();
extern word_t sk_h_00464258();
extern word_t sk_h_00464280();
extern word_t sk_h_00464308();
extern word_t sk_h_00464318();
extern word_t sk_h_004643b8();
extern word_t sk_h_004643cc();
extern word_t sk_h_00464498();
extern word_t sk_h_004644e8();
extern word_t sk_h_00464550();
extern word_t sk_h_00464594();
extern word_t sk_h_004645ec();
extern word_t sk_h_00464660();
extern word_t sk_h_004647b4();
extern word_t sk_h_00464874();
extern word_t sk_h_004648c4();
extern word_t sk_h_004648fc();
extern word_t sk_h_00464930();
extern word_t sk_h_0046493c();
extern word_t sk_h_00464978();
extern word_t sk_h_0046499c();
extern word_t sk_h_004649d8();
extern word_t sk_h_00464a08();
extern word_t sk_h_00464a38();
extern word_t sk_h_00464a44();
extern word_t sk_h_00464ad0();
extern word_t sk_h_00464bb8();
extern word_t sk_h_00464d0c();
extern word_t sk_h_00464d68();
extern word_t sk_h_00464dd8();
extern word_t sk_h_00464e1c();
extern word_t sk_h_00464e28();
extern word_t sk_h_00464eb0();
extern word_t sk_h_00464eec();
extern word_t sk_h_00464ef8();
extern word_t sk_h_00464f58();
extern word_t sk_h_00465070();
extern word_t sk_h_00465094();
extern word_t sk_h_004650e4();
extern word_t sk_h_0046518c();
extern word_t sk_h_004651a8();
extern word_t sk_h_00465234();
extern word_t sk_h_00465240();
extern word_t sk_h_00465264();
extern word_t sk_h_004652a0();
extern word_t sk_h_004652f4();
extern word_t sk_h_004653c0();
extern word_t sk_h_00465408();
extern word_t sk_h_00465458();
extern word_t sk_h_00465468();
extern word_t sk_h_00465488();
extern word_t sk_h_00465498();
extern word_t sk_h_00465524();
extern word_t sk_h_00465540();
extern word_t sk_h_00465590();
extern word_t sk_h_004655f0();
extern word_t sk_h_00465614();
extern word_t sk_h_0046562c();
extern word_t sk_h_00465698();
extern word_t sk_h_00465710();
extern word_t sk_h_0046574c();
extern word_t sk_h_00465794();
extern word_t sk_h_004657d0();
extern word_t sk_h_004657dc();
extern word_t sk_h_004657e8();
extern word_t sk_h_00465800();
extern word_t sk_h_0046583c();
extern word_t sk_h_00465854();
extern word_t sk_h_0046586c();
extern word_t sk_h_00465884();
extern word_t sk_h_004658a8();
extern word_t sk_h_004658b4();
extern word_t sk_h_004658e4();
extern word_t sk_h_00465944();
extern word_t sk_h_00465968();
extern word_t sk_h_00465a04();
extern word_t sk_h_00465a14();
extern word_t sk_h_00465b58();
extern word_t sk_h_00465bb0();
extern word_t sk_h_00465be0();
extern word_t sk_h_00465c5c();
extern word_t sk_h_00465c74();
extern word_t sk_h_00465cc0();
extern word_t sk_h_00465cd4();
extern word_t sk_h_00465ce8();
extern word_t sk_h_00465cf4();
extern word_t sk_h_00465d1c();
extern word_t sk_h_00465d3c();
extern word_t sk_h_00465d5c();
extern word_t sk_h_00465db0();
extern word_t sk_h_00465df0();
extern word_t sk_h_00465e80();
extern word_t sk_h_00465e8c();
extern word_t sk_h_00465f90();
extern word_t sk_h_00465fb4();
extern word_t sk_h_00465fe0();
extern word_t sk_h_00466000();
extern word_t sk_h_00466080();
extern word_t sk_h_0046608c();
extern word_t sk_h_004660b4();
extern word_t sk_h_004660f8();
extern word_t sk_h_00466110();
extern word_t sk_h_004661cc();
extern word_t sk_h_004661d8();
extern word_t sk_h_004661f0();
extern word_t sk_h_00466208();
extern word_t sk_h_00466214();
extern word_t sk_h_0046622c();
extern word_t sk_h_00466238();
extern word_t sk_h_00466250();
extern word_t sk_h_00466270();
extern word_t sk_h_0046627c();
extern word_t sk_h_004662cc();
extern word_t sk_h_00466328();
extern word_t sk_h_00466368();
extern word_t sk_h_004663a0();
extern word_t sk_h_004663d4();
extern word_t sk_h_004663e0();
extern word_t sk_h_00466440();
extern word_t sk_h_0046647c();
extern word_t sk_h_00466528();
extern word_t sk_h_00466568();
extern word_t sk_h_00466580();
extern word_t sk_h_004665f4();
extern word_t sk_h_00466660();
extern word_t sk_h_004666e4();
extern word_t sk_h_004666f8();
extern word_t sk_h_0067f9a0();
extern word_t sk_h_00684e30();
extern sk16_t sk_h_00458d68();
extern sk16_t sk_h_003504d0();
extern sk16_t sk_h_00369efc();
extern sk16_t sk_h_00205844();
extern sk16_t sk_h_00463e04();
extern sk16_t sk_h_00077888();

/* Ghidra decompiler bit/vector intrinsics (make reconstructed expressions
 * type-check; CONCAT* values are only compared/OR-ed in the source). */
static inline word_t SCARRY8(word_t a, word_t b, ...){ (void)a;(void)b; return 0; }
static inline word_t SBORROW8(word_t a, word_t b, ...){ (void)a;(void)b; return 0; }
static inline word_t SBORROW4(word_t a, word_t b, ...){ (void)a;(void)b; return 0; }
static inline word_t SCARRY4(word_t a, word_t b, ...){ (void)a;(void)b; return 0; }
static inline word_t ZEXT516(word_t x){ return x; }
static inline word_t ZEXT414(word_t x){ return x; }
static inline word_t ZEXT48(word_t x){ return x; }
static inline word_t ZEXT416(word_t x){ return x; }
static inline word_t ZEXT416(word_t x){ return x; }
static inline word_t ZEXT816(word_t x){ return x; }
static inline word_t ZEXT824(word_t x){ return x; }
static inline word_t ZEXT832(word_t x){ return x; }
static inline word_t ZEXT864(word_t x){ return x; }
static inline word_t CONCAT11(word_t h, word_t l){ return ((h&0xff)<<8)|(l&0xff); }
static inline word_t CONCAT12(word_t h, word_t r){ return (h<<16)|r; }
static inline word_t CONCAT13(word_t h, word_t r){ return (h<<24)|r; }
static inline word_t CONCAT14(word_t h, word_t r){ return (h<<32)|r; }
static inline word_t CONCAT15(word_t h, word_t r){ return (h<<40)|r; }
static inline word_t CONCAT16(word_t h, word_t r){ return (h<<48)|r; }
static inline word_t CONCAT17(word_t h, word_t r){ return (h<<56)|r; }
static inline word_t CONCAT18(word_t h, word_t r){ return (h<<64)|r; }
static inline word_t CONCAT71(word_t h, word_t r){ return (h<<56)|r; }
static inline word_t CONCAT72(word_t h, word_t r){ return (h<<64)|r; }
static inline word_t CONCAT81(word_t h, word_t r){ return (h<<8)|r; }
static inline word_t CONCAT82(word_t h, word_t r){ return (h<<16)|r; }
static inline void sk_neon_ext8(byte *r, const byte *a, const byte *b){
    int _k;
    for (_k=0;_k<8;_k++) r[_k]=a[8+_k];
    for (_k=0;_k<8;_k++) r[8+_k]=b[_k];
}


void sk_f_0041a048(void);
word_t sk_f_0041a068(void);
void sk_f_0041a094(void);
uint sk_f_0041a0dc(long* param_1, long* param_2);
void sk_f_0041a3ec(long* ctx);
void sk_f_0041a5cc(void);
void sk_f_0041a60c(void);
word_t sk_f_0041a64c(void);
void sk_f_0041a6dc(void);
void sk_f_0041a740(void);
void sk_f_0041a7cc(void);
void sk_f_0041a80c(void);
word_t sk_f_0041a868(void);
void sk_f_0041a8f4(void);
void sk_f_0041a92c(void);
void sk_f_0041a96c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6, word_t param_7, word_t param_8, word_t param_9, word_t param_10, word_t param_11);
word_t sk_f_0041a9e4(byte* op);
void sk_f_0041aab4(void);
void sk_f_0041ab70(void);
void sk_f_0041abcc(void);
void sk_f_0041ac6c(word_t param_1, byte param_2, word_t param_3, word_t param_4);
void sk_f_0041acb4(void);
void sk_f_0041ad20(void);
void sk_f_0041adbc(word_t param_1);
bool sk_f_0041ae04(void);
word_t sk_f_0041ae14(byte* op);
void sk_f_0041aee4(void);
void sk_f_0041afc8(word_t* param_1, word_t param_2);
void sk_f_0041aff0(word_t* param_1, word_t param_2);
sk16_t sk_f_0041b01c(word_t a, word_t b, word_t c);
void sk_f_0041b068(void);
void sk_f_0041b06c(void);
sk16_t sk_f_0041b088(void);
void sk_f_0041b1a8(void);
word_t sk_f_0041b1d4(long param_1, word_t param_2, word_t param_3, word_t param_4, long param_5, long param_6, word_t param_7, word_t param_8);
void sk_f_0041b3d4(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5);
void sk_f_0041b58c(void);
word_t sk_f_0041b64c(void);
void sk_f_0041b6ac(word_t param_1);
void sk_f_0041b6f4(void);
void sk_f_0041b760(void);
void sk_f_0041b7b8(void);
word_t sk_f_0041b820(long* param_1, long* param_2);
void sk_f_0041baa4(void);
void sk_f_0041bc58(void);
void sk_f_0041bcb4(void);
word_t sk_f_0041bcf4(void);
void sk_f_0041bd34(byte* param_1, word_t* param_2);
void sk_f_0041bd68(byte (*param_1)[16]);
word_t sk_f_0041bdac(void);
void sk_f_0041be80(void);
void sk_f_0041bf18(void);
void sk_f_0041bf74(void);
sk16_t sk_f_0041bfb4(void);
void sk_f_0041c0c0(void);
void sk_f_0041c190(void);
void sk_f_0041c1c4(word_t* param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, byte param_6, word_t param_7, word_t param_8);
sk16_t sk_f_0041c1d8(word_t param_1, word_t param_2, long param_3);
sk16_t sk_f_0041c25c(void);
bool sk_f_0041c26c(void);
bool sk_f_0041c270(void);
sk16_t sk_f_0041c28c(uint param_1);
long sk_f_0041c29c(long param_1, word_t param_2, long param_3);
sk16_t sk_f_0041c2ac(word_t param_1, word_t param_2, long param_3);
void sk_f_0041c2c8(word_t param_1, word_t param_2, long param_3);
void sk_f_0041c2e4(word_t param_1, word_t param_2, word_t param_3, long param_4, byte param_5);
long sk_f_0041ca38();
sk16_t sk_f_0041cb78(void);
word_t sk_f_0041cb8c(void);
uint sk_f_0041cc48(word_t param_1, word_t* param_2);
sk16_t sk_f_0041cc98(void);
void sk_f_0041cd40(void);
void sk_f_0041cf18(word_t param_1, word_t param_2, long param_3, word_t param_4, long param_5, long param_6, long param_7, word_t param_8);
void sk_f_0041d070(void);
void sk_f_0041d14c(byte param_1, long param_2, long param_3, long param_4);
void sk_f_0041d180(word_t param_1, word_t param_2, long param_3, word_t param_4, uint param_5, word_t param_6, word_t param_7, long* param_8);
void sk_f_0041d3e8(void);
void sk_f_0041d430(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
void sk_f_0041d4a4(long param_1, long param_2, long param_3, long param_4, char param_5);
sk16_t sk_f_0041d778(void);
void sk_f_0041d788(void);
void sk_f_0041d7dc(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6, code_t* param_7);
void sk_f_0041d8f4(long param_1);
void sk_f_0041dae0(void);
char sk_f_0041dbb4();
char sk_f_0041dd0c();
char sk_f_0041de64();
void sk_f_0041dfbc(void);
void sk_f_0041dfc0(void);
sk16_t sk_f_0041dfe4(long param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5);
void sk_f_0041e0a0(word_t param_1, word_t param_2, word_t param_3);
void sk_f_0041e188(long param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5);
sk16_t sk_f_0041e21c(long param_1, long param_2);
void sk_f_0041e28c(void);
void sk_f_0041efc0(void);
void sk_f_0041f074(void);
void sk_f_00420618(byte* param_1, long param_2, long param_3);
word_t sk_f_00420770(void);
void sk_f_004207b0(void);
void sk_f_00424280(void);
void sk_f_00428f4c(word_t* param_1, long param_2, long param_3);
void sk_f_00429020(void);
sk16_t sk_f_004292ac(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6);
sk16_t sk_f_00429398(word_t param_1, word_t param_2, word_t param_3);
void sk_f_00429430(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
void sk_f_00429984(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6, word_t param_7, word_t param_8);
void sk_f_00429ed8(byte (*param_1)[16], byte* param_2, long param_3, word_t param_4, word_t param_5);
uint sk_f_0042a8d0(word_t param_1, word_t param_2);
void sk_f_0042ac28(void);
void sk_f_0042aca4(void);
void sk_f_0042acc4(void);
void sk_f_0042acd4(void);
void sk_f_0042ace4(void);
void sk_f_0042ad04(word_t param_1, word_t param_2, word_t param_3, byte param_4);
void sk_f_0042ad50(word_t param_1, word_t param_2, word_t param_3, byte param_4);
void sk_f_0042ad9c(byte param_1, word_t param_2);
void sk_f_0042ade4(void);
void sk_f_0042ae34(word_t param_1, word_t param_2);
void sk_f_0042ae78(void);
void sk_f_0042aec8(void);

static int sk_smallstr_eq(const char *tag, const char *name) {
    while (*tag && *name && *tag==*name) { tag++; name++; }
    return *tag==*name;
}

/* FUN_0041a048 @ 0x0041a048   (est. sk_f_0041a048)
 * Ghidra: void FUN_0041a048(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a048(void){
  sk_h_004637b4();
  sk_h_0045908c();
  return;
}

/* FUN_0041a068 @ 0x0041a068   (est. sk_f_0041a068)
 * Ghidra: word_t FUN_0041a068(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041a068(void){
  word_t  v1;
  long  ctx;
  
  v1 = *(word_t *)(ctx + 0x68);
  sk_h_0036b270(v1 & 0xfffffffffffffff);
  return v1;
}

/* FUN_0041a094 @ 0x0041a094   (est. sk_f_0041a094)
 * Ghidra: void FUN_0041a094(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a094(void){
  long  out8;
  word_t  r19;
  word_t  ctx;
  sk16_t sv1;
  
  sv1 = (sk16_t){ sk_h_00077888(), 0 };
  sk_h_00117cc4(out8,sv1.lo,0x68);
  *(long  *)(out8 + 0x68) = sv1.hi;
  *(word_t *)(out8 + 0x70) = ctx;
  *(word_t *)(out8 + 0x78) = r19;
  return;
}

/* FUN_0041a0dc @ 0x0041a0dc   (est. sk_f_0041a0dc)
 * Ghidra: uint FUN_0041a0dc(long *param_1,long *param_2)
 * 
 * Confidence: medium
 * Notes:  */
uint sk_f_0041a0dc(long* param_1, long* param_2){
  word_t  v1;
  long  t2;
  long  t3;
  word_t  v4;
  word_t  v5;
  long  t6;
  long  t7;
  long  t8;
  word_t  v9;
  bool  b10;
  uint  v11;
  long  t12;
  word_t  v13;
  long  out1;
  long  *out1_00;
  long  out1_01;
  long  out1_02;
  long  *out1_03;
  long  *out1_04;
  long  *out1_05;
  long  *out1_06;
  long  *out1_07;
  long  *out1_08;
  long  *out1_09;
  long  *out1_10;
  long  *out1_11;
  long  *out1_12;
  long  *pt14;
  long  out8;
  long  out8_00;
  long  out9;
  long  t15;
  long  t16;
  byte  l_80 [80];
  
  t12 = *param_1;
  t16 = param_1[1];
  v5 = param_1[2];
  v1 = param_1[3];
  t6 = param_1[4];
  t2 = param_1[5];
  t7 = param_1[6];
  t3 = param_1[7];
  t8 = param_1[8];
  t15 = param_1[9];
  b10 = (char )param_1[10] == '\x03';
  switch((char )param_1[10]) {
  default:
    if ((char)param_2[10] == '\0') {
      v4 = param_2[2];
      v9 = param_2[3];
      if (t12 == *param_2 && t16 == param_2[1]) {
        if ((v4 ^ v5) >> 0xe == 0) goto LAB_0041a258;
      }
      else {
        v13 = sk_h_00465c5c();
        if (((v13 & 1) != 0) && ((v4 ^ v5) < 0x4000)) {
LAB_0041a258:
          if ((v9 ^ v1) < 0x4000) goto LAB_0041a3b8;
        }
      }
    }
    break;
  case '\x01':
    sk_h_00465fe0();
    if (*(char  *)(out1_01 + 0x50) == '\x01') {
      v11 = sk_f_0041a9e4(l_80);
      goto LAB_0041a3c4;
    }
    break;
  case '\x02':
    sk_h_00465fe0();
    if (*(char  *)(out1 + 0x50) == '\x02') {
      v11 = sk_f_0041ae14(l_80);
      goto LAB_0041a3c4;
    }
    break;
  case '\x03':
    if ((((v5 == 0 && t16 == 0) && (t12 == 0 && v1 == 0)) &&
        ((t6 == 0 && t2 == 0) && t7 == 0)) && ((t3 == 0 && t8 == 0) && t15 == 0))
    {
      sk_h_00463dc8();
      if ((b10) &&
         (t16 = sk_h_00463558(*(word_t *)(out1_02 + 8),
                                *(word_t *)(out1_02 + 0x30),
                                *(word_t *)(out1_02 + 0x40),
                                *(word_t *)(out1_02 + 0x10),
                                *(word_t *)(out1_02 + 0x20)),
         (t16 == 0 && out8 == 0) && out9 == 0)) {
LAB_0041a3b8:
        v11 = 1;
        goto LAB_0041a3c4;
      }
    }
    else {
      b10 = t12 == 1;
      if ((b10) &&
         ((((v5 == 0 && t16 == 0) && v1 == 0) && ((t6 == 0 && t2 == 0) && t7 == 0)
          ) && ((t3 == 0 && t8 == 0) && t15 == 0))) {
        sk_h_00463dc8();
        if ((b10) && (pt14 = out1_00, *out1_00 == 1)) goto LAB_0041a39c;
      }
      else {
        b10 = t12 == 2;
        if ((b10) &&
           ((((v5 == 0 && t16 == 0) && v1 == 0) &&
            ((t6 == 0 && t2 == 0) && t7 == 0)) &&
            ((t3 == 0 && t8 == 0) && t15 == 0))) {
          sk_h_00463dc8();
          if ((b10) && (pt14 = out1_03, *out1_03 == 2)) goto LAB_0041a39c;
        }
        else {
          b10 = t12 == 3;
          if ((b10) &&
             ((((v5 == 0 && t16 == 0) && v1 == 0) &&
              ((t6 == 0 && t2 == 0) && t7 == 0)) &&
              ((t3 == 0 && t8 == 0) && t15 == 0))) {
            sk_h_00463dc8();
            if ((b10) && (pt14 = out1_04, *out1_04 == 3)) goto LAB_0041a39c;
          }
          else {
            b10 = t12 == 4;
            if ((b10) &&
               ((((v5 == 0 && t16 == 0) && v1 == 0) &&
                ((t6 == 0 && t2 == 0) && t7 == 0)) &&
                ((t3 == 0 && t8 == 0) && t15 == 0))) {
              sk_h_00463dc8();
              if ((b10) && (pt14 = out1_05, *out1_05 == 4)) goto LAB_0041a39c;
            }
            else {
              b10 = t12 == 5;
              if ((b10) &&
                 ((((v5 == 0 && t16 == 0) && v1 == 0) &&
                  ((t6 == 0 && t2 == 0) && t7 == 0)) &&
                  ((t3 == 0 && t8 == 0) && t15 == 0))) {
                sk_h_00463dc8();
                if ((b10) && (pt14 = out1_06, *out1_06 == 5)) goto LAB_0041a39c;
              }
              else {
                b10 = t12 == 6;
                if ((b10) &&
                   ((((v5 == 0 && t16 == 0) && v1 == 0) &&
                    ((t6 == 0 && t2 == 0) && t7 == 0)) &&
                    ((t3 == 0 && t8 == 0) && t15 == 0))) {
                  sk_h_00463dc8();
                  if ((b10) && (pt14 = out1_07, *out1_07 == 6))
                  goto LAB_0041a39c;
                }
                else {
                  b10 = t12 == 7;
                  if ((b10) &&
                     ((((v5 == 0 && t16 == 0) && v1 == 0) &&
                      ((t6 == 0 && t2 == 0) && t7 == 0)) &&
                      ((t3 == 0 && t8 == 0) && t15 == 0))) {
                    sk_h_00463dc8();
                    if ((b10) && (pt14 = out1_08, *out1_08 == 7))
                    goto LAB_0041a39c;
                  }
                  else {
                    b10 = t12 == 8;
                    if ((b10) &&
                       ((((v5 == 0 && t16 == 0) && v1 == 0) &&
                        ((t6 == 0 && t2 == 0) && t7 == 0)) &&
                        ((t3 == 0 && t8 == 0) && t15 == 0))) {
                      sk_h_00463dc8();
                      if ((b10) && (pt14 = out1_09, *out1_09 == 8))
                      goto LAB_0041a39c;
                    }
                    else {
                      b10 = t12 == 9;
                      if ((b10) &&
                         ((((v5 == 0 && t16 == 0) && v1 == 0) &&
                          ((t6 == 0 && t2 == 0) && t7 == 0)) &&
                          ((t3 == 0 && t8 == 0) && t15 == 0))) {
                        sk_h_00463dc8();
                        if ((b10) && (pt14 = out1_10, *out1_10 == 9))
                        goto LAB_0041a39c;
                      }
                      else {
                        b10 = t12 == 10;
                        if ((b10) &&
                           ((((v5 == 0 && t16 == 0) && v1 == 0) &&
                            ((t6 == 0 && t2 == 0) && t7 == 0)) &&
                            ((t3 == 0 && t8 == 0) && t15 == 0))) {
                          sk_h_00463dc8();
                          if ((b10) && (pt14 = out1_11, *out1_11 == 10)) {
LAB_0041a39c:
                            t16 = sk_h_00463558(pt14[1],pt14[6],pt14[8],pt14[2],
                                                  pt14[4]);
                            if (t16 == 0 && out8_00 == 0) goto LAB_0041a3b8;
                          }
                        }
                        else {
                          sk_h_00463dc8();
                          if ((b10) && (pt14 = out1_12, *out1_12 == 0xb))
                          goto LAB_0041a39c;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  v11 = 0;
LAB_0041a3c4:
  return v11 & 1;
}

/* FUN_0041a3ec @ 0x0041a3ec   (est. sk_f_0041a3ec)
 * Ghidra: void FUN_0041a3ec(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a3ec(long* ctx){
  long  t1;
  word_t  v2;
  long  t3;
  long  t4;
  long  t5;
  long  t6;
  word_t  v7;
  long  t8;
  long  t9;
  long  t10;
  word_t  v11;
  word_t  out1;
  
  sk_h_004666f8();
  t1 = *ctx;
  t6 = ctx[1];
  v2 = ctx[2];
  v7 = ctx[3];
  t3 = ctx[4];
  t8 = ctx[5];
  t4 = ctx[6];
  t9 = ctx[7];
  t5 = ctx[8];
  t10 = ctx[9];
  switch((char )ctx[10]) {
  default:
    sk_h_00464e1c();
    sk_h_002298d4();
    sk_h_00462e0c();
    sk_h_001b9084();
    sk_h_002298d4(v2 >> 0xe);
    sk_h_002298d4(v7 >> 0xe);
    break;
  case '\x01':
    sk_h_00465fb4();
    sk_h_00465b58();
    sk_h_004650e4();
    sk_f_0041aab4();
    break;
  case '\x02':
    sk_h_00465fb4();
    sk_h_002298d4(0xe);
    sk_h_004650e4();
    sk_f_0041aee4();
    break;
  case '\x03':
    if ((((v2 == 0 && t6 == 0) && (t1 == 0 && v7 == 0)) &&
        ((t3 == 0 && t8 == 0) && t4 == 0)) && ((t9 == 0 && t5 == 0) && t10 == 0))
    {
      v11 = 0;
    }
    else if ((t1 == 1) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 3;
    }
    else if ((t1 == 2) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 4;
    }
    else if ((t1 == 3) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 5;
    }
    else if ((t1 == 4) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 6;
    }
    else if ((t1 == 5) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 7;
    }
    else if ((t1 == 6) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 8;
    }
    else if ((t1 == 7) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 9;
    }
    else if ((t1 == 8) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 10;
    }
    else if ((t1 == 9) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 0xb;
    }
    else if ((t1 == 10) &&
            ((((v2 == 0 && t6 == 0) && v7 == 0) &&
             ((t3 == 0 && t8 == 0) && t4 == 0)) &&
             ((t9 == 0 && t5 == 0) && t10 == 0))) {
      v11 = 0xc;
    }
    else {
      v11 = 0xd;
    }
    sk_h_002298d4(v11);
  }
  sk_h_004666e4(out1);
  return;
}

/* FUN_0041a5cc @ 0x0041a5cc   (est. sk_f_0041a5cc)
 * Ghidra: void FUN_0041a5cc(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a5cc(void){
  byte  l_68 [72];
  
  sk_h_004080b0();
  sk_f_0041a3ec((long*)l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041a60c @ 0x0041a60c   (est. sk_f_0041a60c)
 * Ghidra: void FUN_0041a60c(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a60c(void){
  byte  l_68 [72];
  
  sk_h_001a84f4(l_68);
  sk_f_0041a3ec((long*)l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041a64c @ 0x0041a64c   (est. sk_f_0041a64c)
 * Ghidra: word_t FUN_0041a64c(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041a64c(void){
  byte  in_flags;
  word_t  v1;
  word_t  v2;
  word_t  out8;
  long  out8_00;
  long  out8_01;
  long  out8_02;
  long  r19;
  long  ctx;
  
  sk_h_00350c5c();
  sk_f_0041a0dc((long*,(word_t)0)ctx,(long*)r19);
  v1 = sk_h_00464a08();
  if ((((out8 & 1) != 0) && (v1 = sk_h_00464ad0(), out8_00 == 0)) &&
     (v1 = sk_h_0046622c(), out8_01 == 0)) {
    v2 = sk_h_0041001c(*(word_t *)(r19 + 0x68),*(word_t *)(ctx + 0x68));
    if ((((v2 & 1) == 0) ||
        (sk_h_00464d0c(*(word_t *)(r19 + 0x70)), out8_02 != 0)) ||
       (sk_h_00465264(*(word_t *)(ctx + 0x78)), (bool )in_flags)) {
      v1 = 0;
    }
    else {
      v1 = 1;
    }
  }
  return v1;
}

/* FUN_0041a6dc @ 0x0041a6dc   (est. sk_f_0041a6dc)
 * Ghidra: void FUN_0041a6dc(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a6dc(void){
  word_t  v1;
  long  r19;
  long  ctx;
  
  sk_h_00464a38();
  v1 = *(word_t *)(ctx + 0x60);
  sk_f_0041a3ec((long*)0);
  sk_h_00466660();
  sk_h_002298d4(v1 >> 0xe);
  sk_h_00410414();
  v1 = *(word_t *)(r19 + 0x78);
  sk_h_002298d4(*(word_t *)(r19 + 0x70) >> 0xe);
  sk_h_002298d4(v1 >> 0xe);
  return;
}

/* FUN_0041a740 @ 0x0041a740   (est. sk_f_0041a740)
 * Ghidra: void FUN_0041a740(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a740(void){
  word_t  v1;
  long  r19;
  long  ctx;
  byte  l_78 [72];
  
  sk_h_004644e8();
  v1 = *(word_t *)(ctx + 0x60);
  sk_f_0041a3ec(l_78);
  sk_h_004652a0();
  sk_h_002298d4(v1 >> 0xe);
  sk_h_00410414(l_78,*(word_t *)(r19 + 0x68));
  sk_h_00465234(*(word_t *)(r19 + 0x70));
  sk_h_00464eb0();
  sk_h_001a8564();
  return;
}

/* FUN_0041a7cc @ 0x0041a7cc   (est. sk_f_0041a7cc)
 * Ghidra: void FUN_0041a7cc(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a7cc(void){
  void (*r19)(void *);
  byte  l_68 [72];
  
  sk_h_004653c0();
  (*r19)(l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041a80c @ 0x0041a80c   (est. sk_f_0041a80c)
 * Ghidra: void FUN_0041a80c(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a80c(void){
  long  ctx;
  
  if ((*(char  *)(ctx + 0x50) == '\0') ||
     ((*(char *)(ctx + 0x50) == '\x01' && (*(long *)(ctx + 8) != 0)))) {
    sk_h_0036b270(*(long *)(ctx + 8));
  }
  sk_h_003507e0();
  return;
}

/* FUN_0041a868 @ 0x0041a868   (est. sk_f_0041a868)
 * Ghidra: word_t FUN_0041a868(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041a868(void){
  word_t  v1;
  long  out8;
  long  out9;
  word_t  *ctx;
  long  t2;
  
  if (*(char  *)(ctx + 10) == '\x03') {
    t2 = sk_h_00463558(*ctx,ctx[6],ctx[8],ctx[2],ctx[4]);
    if (out8 == 4 && (t2 == 0 && out9 == 0)) {
      return 0x101;
    }
    if (out8 == 5 && (t2 == 0 && out9 == 0)) {
      v1 = sk_h_0006e064();
      return v1;
    }
    if (out8 == 7 && (t2 == 0 && out9 == 0)) {
      return 0x100;
    }
    if ((out8 == 8) && (t2 == 0 && out9 == 0)) {
      return 0;
    }
  }
  return 2;
}

/* FUN_0041a8f4 @ 0x0041a8f4   (est. sk_f_0041a8f4)
 * Ghidra: void FUN_0041a8f4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a8f4(void){
  long  ctx;
  
  sk_h_0036b270(*(word_t *)(ctx + 0x38));
  sk_h_00462d5c();
  return;
}

/* FUN_0041a92c @ 0x0041a92c   (est. sk_f_0041a92c)
 * Ghidra: void FUN_0041a92c(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a92c(void){
  word_t  r19;
  long  ctx;
  word_t  r21;
  word_t  r22;
  word_t  r23;
  
  sk_h_00349a18();
  sk_h_003a25d4(*(word_t *)(ctx + 0x38));
  *(word_t *)(ctx + 0x30) = r23;
  *(word_t *)(ctx + 0x38) = r22;
  *(word_t *)(ctx + 0x40) = r21;
  *(word_t *)(ctx + 0x48) = r19;
  return;
}

/* FUN_0041a96c @ 0x0041a96c   (est. sk_f_0041a96c)
 * Ghidra: void FUN_0041a96c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,                  undefined8 param_9,undefined8 param_10,undefined8 param_11)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041a96c(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6, word_t param_7, word_t param_8, word_t param_9, word_t param_10, word_t param_11){
  byte  l_110 [80];
  word_t  l_c0;
  word_t  l_b8;
  word_t  l_b0;
  word_t  l_a8;
  word_t  l_a0;
  word_t  l_98;
  word_t  l_90;
  word_t  l_88;
  word_t  l_80;
  word_t  l_78;
  word_t  l_70;
  word_t  l_68;
  word_t  l_60;
  word_t  l_58;
  word_t  l_50;
  word_t  l_48;
  word_t  l_40;
  word_t  l_38;
  word_t  l_30;
  word_t  l_28;
  
  l_80 = param_10;
  l_78 = param_11;
  l_30 = param_10;
  l_28 = param_11;
  l_c0 = param_2;
  l_b8 = param_3;
  l_b0 = param_4;
  l_a8 = param_5;
  l_a0 = param_6;
  l_98 = param_7;
  l_90 = param_8;
  l_88 = param_9;
  l_70 = param_2;
  l_68 = param_3;
  l_60 = param_4;
  l_58 = param_5;
  l_50 = param_6;
  l_48 = param_7;
  l_40 = param_8;
  l_38 = param_9;
  sk_h_00458d68(&l_c0,l_110);
  sk_h_00458d78(&l_70);
  sk_h_00117cc4(param_1,&l_c0,0x50);
  return;
}

/* FUN_0041a9e4 @ 0x0041a9e4   (est. sk_f_0041a9e4)
 * Ghidra: uint FUN_0041a9e4(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041a9e4(byte* op){
  byte  v1;
  byte  v2;
  uint  v3;
  long  t4;
  word_t  v5;
  word_t  v6;
  word_t  out8;
  long  out8_00;
  long  out8_01;
  long  out8_02;
  long  *r19;
  long  *ctx;
  
  t4 = sk_h_003504d0().lo;
  v5 = *(word_t *)(t4 + 8);
  v6 = r19[1];
  if (v5 == 0) {
    if (v6 == 0) {
LAB_0041aa60:
      sk_h_00464d0c(ctx[4]);
      if ((out8_01 == 0) && (sk_h_00464d0c(r19[5]), out8_02 == 0)) {
        v3 = sk_h_00448fd0(ctx[6],ctx[7],ctx[8],ctx[9],r19[6],
                             r19[7],r19[8],r19[9]);
        goto LAB_0041aa9c;
      }
    }
  }
  else if (v6 != 0) {
    v1 = *ctx == *r19 && v6 <= v5;
    if (*ctx == *r19 && v5 == v6) {
      sk_h_00464ad0();
      v2 = v1;
      if (out8_00 != 0) goto LAB_0041aa98;
    }
    else {
      sk_h_002a0cf8();
      v3 = sk_h_00464a08();
      if ((out8 & 1) == 0) goto LAB_0041aa9c;
      v3 = sk_h_00465968();
      v2 = 0;
      if ((bool )v1) goto LAB_0041aa9c;
    }
    sk_h_004658a8();
    if (!(bool )v2) goto LAB_0041aa60;
  }
LAB_0041aa98:
  v3 = 0;
LAB_0041aa9c:
  return v3 & 1;
}

/* FUN_0041aab4 @ 0x0041aab4   (est. sk_f_0041aab4)
 * Ghidra: void FUN_0041aab4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041aab4(void){
  word_t  v1;
  word_t  v2;
  long  r19;
  
  sk_h_00464a44();
  if (*(long  *)(r19 + 8) == 0) {
    sk_h_00229a3c(0);
  }
  else {
    v1 = *(word_t *)(r19 + 0x10);
    v2 = *(word_t *)(r19 + 0x18);
    sk_h_00229a3c(1);
    sk_h_00077894();
    sk_h_001b9084();
    sk_h_002298d4(v1 >> 0xe);
    sk_h_002298d4(v2 >> 0xe);
  }
  v1 = *(word_t *)(r19 + 0x28);
  sk_h_002298d4(*(word_t *)(r19 + 0x20) >> 0xe);
  sk_h_002298d4(v1 >> 0xe);
  v1 = *(word_t *)(r19 + 0x40);
  v2 = *(word_t *)(r19 + 0x48);
  sk_h_001b9084();
  sk_h_002298d4(v1 >> 0xe);
  sk_h_002298d4(v2 >> 0xe);
  return;
}

/* FUN_0041ab70 @ 0x0041ab70   (est. sk_f_0041ab70)
 * Ghidra: void FUN_0041ab70(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041ab70(void){
  void (*r19)(void *);
  byte  l_68 [72];
  
  sk_h_004648fc();
  (*r19)(l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041abcc @ 0x0041abcc   (est. sk_f_0041abcc)
 * Ghidra: void FUN_0041abcc(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041abcc(void){
  void (*r19)(void *);
  byte  l_68 [72];
  
  sk_h_004653c0();
  (*r19)(l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041ac6c @ 0x0041ac6c   (est. sk_f_0041ac6c)
 * Ghidra: void FUN_0041ac6c(undefined8 param_1,undefined1 param_2,ulong param_3,ulong param_4)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041ac6c(word_t param_1, byte param_2, word_t param_3, word_t param_4){
  sk_h_002298d4(param_2);
  sk_h_002298d4(param_3 >> 0xe);
  sk_h_002298d4(param_4 >> 0xe);
  return;
}

/* FUN_0041acb4 @ 0x0041acb4   (est. sk_f_0041acb4)
 * Ghidra: void FUN_0041acb4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041acb4(void){
  byte  v1;
  
  v1 = sk_h_00350b54();
  sk_h_004080b0();
  sk_h_002298d4(v1);
  sk_h_004652a0();
  sk_h_00464eb0();
  sk_h_001a8564();
  return;
}

/* FUN_0041ad20 @ 0x0041ad20   (est. sk_f_0041ad20)
 * Ghidra: void FUN_0041ad20(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041ad20(void){
  word_t  v1;
  word_t  v2;
  byte  v3;
  byte  *ctx;
  byte  l_78 [72];
  
  v1 = *(word_t *)(ctx + 8);
  v2 = *(word_t *)(ctx + 0x10);
  v3 = *ctx;
  sk_h_001a84f4(l_78);
  sk_f_0041ac6c((word_t,(word_t)0,(word_t)0,(word_t)0)l_78,v3,v1,v2);
  sk_h_001a8564();
  return;
}

/* FUN_0041adbc @ 0x0041adbc   (est. sk_f_0041adbc)
 * Ghidra: void FUN_0041adbc(undefined8 param_1)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041adbc(word_t param_1){
  long  ctx;
  
  sk_h_0036b118(*(word_t *)(ctx + 0x38));
  *(word_t *)(ctx + 0x38) = param_1;
  return;
}

/* FUN_0041ae04 @ 0x0041ae04   (est. sk_f_0041ae04)
 * Ghidra: bool FUN_0041ae04(void)
 * 
 * Confidence: medium
 * Notes:  */
bool sk_f_0041ae04(void){
  long  ctx;
  
  return *(char  *)(ctx + 0x10) != '\x01';
}

/* FUN_0041ae14 @ 0x0041ae14   (est. sk_f_0041ae14)
 * Ghidra: word_t FUN_0041ae14(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041ae14(byte* op){
  char  cVar1;
  bool  b2;
  byte  v3;
  word_t  v4;
  word_t  v5;
  long  out8;
  word_t  *r19;
  word_t  *ctx;
  sk16_t sv6;
  
  sv6 = (sk16_t){ sk_h_003504d0(), 0 };
  cVar1 = *(char  *)(sv6.hi + 0x10);
  if (*(char  *)(sv6.lo + 0x10) == '\x01') {
    if (cVar1 != '\x01') {
      return 0;
    }
  }
  else {
    b2 = cVar1 != '\x01';
    if (cVar1 == '\x01' || (*ctx ^ *r19) >> 0xe != 0) {
      return 0;
    }
    sk_h_00465264(r19[1]);
    if (b2) {
      return 0;
    }
  }
  v4 = sk_h_00411290(ctx[3],r19[3]);
  if ((v4 & 1) != 0) {
    cVar1 = (char )r19[6];
    if ((char )ctx[6] == '\x01') {
      if (cVar1 == '\x01') {
LAB_0041aebc:
        v5 = sk_h_00411290(ctx[7],r19[7]);
        return v5;
      }
    }
    else {
      v3 = cVar1 != '\0';
      if (((cVar1 != '\x01') && (sk_h_004637dc(), out8 == 0)) &&
         (sk_h_00465264(r19[5]), !(bool )v3)) goto LAB_0041aebc;
    }
  }
  return 0;
}

/* FUN_0041aee4 @ 0x0041aee4   (est. sk_f_0041aee4)
 * Ghidra: void FUN_0041aee4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041aee4(void){
  word_t  v1;
  word_t  v2;
  word_t  *r19;
  
  sk_h_00464a44();
  if ((char )r19[2] == '\x01') {
    sk_h_00229a3c(0);
  }
  else {
    v1 = *r19;
    v2 = r19[1];
    sk_h_00229a3c(1);
    sk_h_002298d4(v1 >> 0xe);
    sk_h_002298d4(v2 >> 0xe);
  }
  sk_h_00458278();
  if ((char )r19[6] == '\x01') {
    sk_h_00229a3c(0);
  }
  else {
    v1 = r19[4];
    v2 = r19[5];
    sk_h_00229a3c(1);
    sk_h_002298d4(v1 >> 0xe);
    sk_h_002298d4(v2 >> 0xe);
  }
  sk_h_00458278();
  return;
}

/* FUN_0041afc8 @ 0x0041afc8   (est. sk_f_0041afc8)
 * Ghidra: void FUN_0041afc8(undefined8 *param_1,undefined8 param_2)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041afc8(word_t* param_1, word_t param_2){
  *param_1 = 0;
  param_1[1] = 0;
  *(byte  *)(param_1 + 2) = 1;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[3] = param_2;
  *(byte  *)(param_1 + 6) = 1;
  param_1[7] = 0 /*DAT_00657778*/;
  return;
}

/* FUN_0041aff0 @ 0x0041aff0   (est. sk_f_0041aff0)
 * Ghidra: void FUN_0041aff0(undefined8 *param_1,undefined8 param_2)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041aff0(word_t* param_1, word_t param_2){
  *param_1 = 0;
  param_1[1] = 0;
  *(byte  *)(param_1 + 2) = 1;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[3] = 0 /*DAT_00657778*/;
  *(byte  *)(param_1 + 6) = 1;
  param_1[7] = param_2;
  return;
}

sk16_t sk_f_0041b01c(word_t a, word_t b, word_t c){
  sk16_t sv1;
  byte  l_21;
  sk16_t l_20;

  sv1 = (sk16_t){ sk_h_00463e04(), 0 };
  l_21 = (byte)sv1.lo;
  sk_h_00463df8(sv1.lo, sv1.hi, 0x6847e8);
  sk_h_00462728();
  l_20 = sk_h_00205844(&l_21, l_20);
  return l_20;
}/* FUN_0041b068 @ 0x0041b068   (est. sk_f_0041b068)
 * Ghidra: void FUN_0041b068(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b068(void){
  byte  *ctx;
  
  sk_f_0041b01c(*ctx,*(word_t *)(ctx + 8),*(word_t *)(ctx + 0x10));
  return;
}

/* FUN_0041b06c @ 0x0041b06c   (est. sk_f_0041b06c)
 * Ghidra: void FUN_0041b06c(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b06c(void){
  byte  *ctx;
  
  sk_f_0041b01c(*ctx,*(word_t *)(ctx + 8),*(word_t *)(ctx + 0x10));
  return;
}

/* FUN_0041b088 @ 0x0041b088   (est. sk_f_0041b088)
 * Ghidra: sk16_t FUN_0041b088(void)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041b088(void){
  word_t  v1;
  word_t  v2;
  sk16_t sv3;
  bool  b4;
  word_t  out1;
  long  ctx;
  word_t  l_38;
  
  sk_h_00100c04();
  sk_h_002a4ab4(0x32);
  sk_h_003a25d4(l_38);
  sk_h_001a6a8c(*(word_t *)(ctx + 0x18),0x684750 /* "PGh" */);
  sk_h_002acbb8();
  sk_h_003a25d4(out1);
  sk_h_002acbb8(0x69766f6d6572202c /* ", removi" */,0xec000000203a676e);
  sk_h_001a6a8c(*(word_t *)(ctx + 0x38),0x684750 /* "PGh" */);
  sk_h_00465944();
  sk_h_002acbb8();
  sk_h_003a25d4(0x684750 /* "PGh" */);
  sk_h_004643cc(0);
  sk_h_002acbb8(0xd000000000000018);
  b4 = *(char  *)(ctx + 0x10) != '\x01';
  v1 = 0x65736c6166 /* "false" */;
  if (b4) {
    v1 = 0x65757274 /* "true" */;
  }
  v2 = 0xe500000000000000;
  if (b4) {
    v2 = 0xe400000000000000;
  }
  sk_h_00465c74(v1);
  sk_h_003a25d4(v2);
  sv3.hi = 0xe800000000000000;
  sv3.lo = 0x203a676e69646461 /* "adding: " */;
  return sv3;
}

/* FUN_0041b1a8 @ 0x0041b1a8   (est. sk_f_0041b1a8)
 * Ghidra: void FUN_0041b1a8(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b1a8(void){
  sk_h_004632f4();
  sk_f_0041b088();
  return;
}

/* FUN_0041b1d4 @ 0x0041b1d4   (est. sk_f_0041b1d4)
 * Ghidra: word_t FUN_0041b1d4(long param_1,ulong param_2,ulong param_3,ulong param_4,long param_5,long param_6,                   ulong param_7,ulong param_8)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041b1d4(long param_1, word_t param_2, word_t param_3, word_t param_4, long param_5, long param_6, word_t param_7, word_t param_8){
  bool  b1;
  word_t  v2;
  uint  v3;
  
  v3 = (uint )((word_t)param_6 >> 0x20);
  switch(param_2 >> 0x3d) {
  default:
    if (v3 >> 0x1d != 0) {
      return 0;
    }
    break;
  case 1:
    if (v3 >> 0x1d != 1) {
      return 0;
    }
    break;
  case 2:
    if (v3 >> 0x1d != 2) {
      return 0;
    }
    break;
  case 3:
    if (v3 >> 0x1d != 3) {
      return 0;
    }
    goto LAB_0041b230;
  case 4:
    if (-0x6000000000000001 < param_6) {
      return 0;
    }
LAB_0041b230:
    return (word_t)((((uint )param_5 ^ (uint)param_1) & 0xff) == 0);
  case 5:
    if ((param_2 == 0xa000000000000000) && ((param_4 == 0 && param_3 == 0) && param_1 == 0)) {
      if (v3 >> 0x1d != 5 || param_6 != -0x6000000000000000) {
        return 0;
      }
      if ((param_8 != 0 || param_7 != 0) || param_5 != 0) {
        return 0;
      }
      goto LAB_0041b3b8;
    }
    if ((param_2 == 0xa000000000000000 && param_1 == 1) && (param_4 == 0 && param_3 == 0)) {
      b1 = v3 >> 0x1d == 5 && param_5 == 1;
LAB_0041b388:
      if (!b1 || param_6 != -0x6000000000000000) {
        return 0;
      }
    }
    else {
      if ((param_2 == 0xa000000000000000 && param_1 == 2) && (param_4 == 0 && param_3 == 0)) {
        b1 = v3 >> 0x1d == 5 && param_5 == 2;
        goto LAB_0041b388;
      }
      if ((param_2 == 0xa000000000000000 && param_1 == 3) && (param_4 == 0 && param_3 == 0)) {
        b1 = v3 >> 0x1d == 5 && param_5 == 3;
        goto LAB_0041b388;
      }
      if ((param_2 == 0xa000000000000000 && param_1 == 4) && (param_4 == 0 && param_3 == 0)) {
        b1 = v3 >> 0x1d == 5 && param_5 == 4;
        goto LAB_0041b388;
      }
      if ((param_2 == 0xa000000000000000 && param_1 == 5) && (param_4 == 0 && param_3 == 0)) {
        b1 = v3 >> 0x1d == 5 && param_5 == 5;
        goto LAB_0041b388;
      }
      if ((param_2 == 0xa000000000000000 && param_1 == 6) && (param_4 == 0 && param_3 == 0)) {
        b1 = false;
        if (v3 >> 0x1d == 5) {
          b1 = param_5 == 6;
        }
        goto LAB_0041b388;
      }
      if ((v3 >> 0x1d != 5 || param_5 != 7) || param_6 != -0x6000000000000000) {
        return 0;
      }
    }
    if (param_8 != 0 || param_7 != 0) {
      return 0;
    }
    goto LAB_0041b3b8;
  }
  v3 = (uint )param_6 & 0xff;
  if ((param_2 & 0xff) == 1) {
    if (v3 != 1) {
      return 0;
    }
  }
  else if (v3 == 1 || param_1 != param_5) {
    return 0;
  }
  if (((param_7 ^ param_3) >> 0xe != 0) || (0x3fff < (param_8 ^ param_4))) {
    return 0;
  }
LAB_0041b3b8:
  v2 = sk_h_0006e064();
  return v2;
}

/* FUN_0041b3d4 @ 0x0041b3d4   (est. sk_f_0041b3d4)
 * Ghidra: void FUN_0041b3d4(undefined8 param_1,ulong param_2,ulong param_3,ulong param_4,ulong param_5)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b3d4(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5){
  word_t  v1;
  
  switch(param_3 >> 0x3d) {
  default:
    v1 = 0;
    break;
  case 1:
    v1 = 1;
    break;
  case 2:
    v1 = 2;
    break;
  case 3:
    v1 = 0xb;
    goto LAB_0041b440;
  case 4:
    v1 = 0xc;
LAB_0041b440:
    sk_h_002298d4(v1);
    param_2 = param_2 & 0xff;
LAB_0041b448:
    sk_h_002298d4(param_2);
    return;
  case 5:
    if ((param_3 == 0xa000000000000000) && ((param_5 == 0 && param_4 == 0) && param_2 == 0)) {
      param_2 = 3;
    }
    else if ((param_3 == 0xa000000000000000 && param_2 == 1) && (param_5 == 0 && param_4 == 0)) {
      param_2 = 4;
    }
    else if ((param_3 == 0xa000000000000000 && param_2 == 2) && (param_5 == 0 && param_4 == 0)) {
      param_2 = 5;
    }
    else if ((param_3 == 0xa000000000000000 && param_2 == 3) && (param_5 == 0 && param_4 == 0)) {
      param_2 = 6;
    }
    else if ((param_3 == 0xa000000000000000 && param_2 == 4) && (param_5 == 0 && param_4 == 0)) {
      param_2 = 7;
    }
    else if ((param_3 == 0xa000000000000000 && param_2 == 5) && (param_5 == 0 && param_4 == 0)) {
      param_2 = 8;
    }
    else if ((param_3 == 0xa000000000000000 && param_2 == 6) && (param_5 == 0 && param_4 == 0)) {
      param_2 = 9;
    }
    else {
      param_2 = 10;
    }
    goto LAB_0041b448;
  }
  sk_h_002298d4(v1);
  if ((param_3 & 0xff) == 1) {
    sk_h_00229a3c(0);
  }
  else {
    sk_h_00229a3c(1);
    sk_h_002298d4(param_2);
  }
  sk_h_002298d4(param_4 >> 0xe);
  sk_h_002298d4(param_5 >> 0xe);
  return;
}

/* FUN_0041b58c @ 0x0041b58c   (est. sk_f_0041b58c)
 * Ghidra: void FUN_0041b58c(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b58c(void){
  word_t l_sk_stack;
  word_t  v1;
  code_t r19;
  word_t r30;
  word_t stack0x00000008;
  
  sk_h_004666f8();
  sk_h_00351da8();
  v1 = sk_h_00350980();
  sk_h_004080b0();
  sk_h_00351b78((word_t*)l_sk_stack,v1);
  (*r19)();
  v1 = sk_h_001a8564();
  sk_h_004666e4(v1,r30);
  return;
}

/* FUN_0041b64c @ 0x0041b64c   (est. sk_f_0041b64c)
 * Ghidra: word_t FUN_0041b64c(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041b64c(void){
  byte  in_flags;
  word_t  *pv1;
  word_t  v2;
  word_t  v3;
  long  out8;
  long  r19;
  word_t  *ctx;
  
  pv1 = (word_t *)sk_h_00350c5c();
  v2 = sk_f_0041b1d4(*pv1,*(word_t *,(word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0)(r19 + 8),*(word_t *)(r19 + 0x10),
                       *(word_t *)(r19 + 0x18),*ctx,ctx[1],ctx[2],
                       ctx[3]);
  if ((((v2 & 1) == 0) || (sk_h_004637dc(), out8 != 0)) ||
     (sk_h_00465264(ctx[5]), (bool )in_flags)) {
    v3 = 0;
  }
  else {
    v3 = 1;
  }
  return v3;
}

/* FUN_0041b6ac @ 0x0041b6ac   (est. sk_f_0041b6ac)
 * Ghidra: void FUN_0041b6ac(undefined8 param_1)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b6ac(word_t param_1){
  word_t  v1;
  word_t  *ctx;
  
  sk_f_0041b3d4(param_1,*ctx,ctx[1],ctx[2],ctx[3]);
  v1 = ctx[5];
  sk_h_004647b4(ctx[4]);
  sk_h_002298d4();
  sk_h_002298d4(v1 >> 0xe);
  return;
}

/* FUN_0041b6f4 @ 0x0041b6f4   (est. sk_f_0041b6f4)
 * Ghidra: void FUN_0041b6f4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b6f4(void){
  word_t  *ctx;
  byte  l_68 [72];
  
  sk_h_004080b0();
  sk_f_0041b3d4((word_t,(word_t)0,(word_t)0,(word_t)0,(word_t)0)l_68,*ctx,ctx[1],ctx[2],ctx[3]);
  sk_h_00465234(ctx[4]);
  sk_h_00464eb0();
  sk_h_001a8564();
  return;
}

/* FUN_0041b760 @ 0x0041b760   (est. sk_f_0041b760)
 * Ghidra: void FUN_0041b760(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b760(void){
  void (*r19)(void *);
  byte  l_68 [72];
  
  sk_h_004653c0();
  (*r19)(l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041b7b8 @ 0x0041b7b8   (est. sk_f_0041b7b8)
 * Ghidra: void FUN_0041b7b8(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041b7b8(void){
  word_t  v1;
  byte  extraout_w1;
  word_t  in_x4;
  word_t  in_x5;
  word_t  in_x6;
  word_t  in_x7;
  long  out8;
  word_t  out9;
  word_t  r23;
  word_t  unaff_x24;
  
  sk_h_00084220();
  v1 = sk_h_00351dc0();
  sk_h_00117cc4(out8,v1,0x50);
  *(byte  *)(out8 + 0x50) = extraout_w1;
  *(word_t *)(out8 + 0x58) = unaff_x24;
  *(word_t *)(out8 + 0x60) = r23;
  *(word_t *)(out8 + 0x68) = in_x4;
  *(word_t *)(out8 + 0x70) = in_x5;
  *(word_t *)(out8 + 0x78) = in_x6;
  *(word_t *)(out8 + 0x80) = in_x7;
  sk_h_00084234(out9);
  return;
}

/* FUN_0041b820 @ 0x0041b820   (est. sk_f_0041b820)
 * Ghidra: word_t FUN_0041b820(long *param_1,long *param_2)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041b820(long* param_1, long* param_2){
  uint  v1;
  long  t2;
  word_t  v3;
  long  t4;
  word_t  v5;
  word_t  v6;
  word_t  v7;
  word_t  v8;
  sk16_t sv9;
  sk16_t sv10;
  sk16_t sv11;
  word_t  v12;
  word_t  v13;
  byte  b14;
  byte  b15;
  byte  b16;
  byte  b17;
  byte  b18;
  byte  b19;
  byte  b20;
  byte  b21;
  byte  b22;
  byte  b23;
  byte  b24;
  byte  b25;
  byte  b26;
  byte  b27;
  byte  b28;
  byte  b29;
  sk16_t sv30;
  
  t2 = *param_1;
  v6 = param_1[1];
  v3 = param_1[2];
  v13 = param_1[3];
  t4 = param_1[4];
  v7 = param_1[5];
  v5 = param_1[6];
  v8 = param_1[7];
  switch(v7 >> 0x3d) {
  default:
    if ((word_t)param_2[5] >> 0x3d != 0) {
      return 0;
    }
    break;
  case 1:
    if ((word_t)param_2[5] >> 0x3d != 1) {
      return 0;
    }
    break;
  case 2:
    if ((word_t)param_2[5] >> 0x3d != 2) {
      return 0;
    }
    break;
  case 3:
    if ((word_t)param_2[5] >> 0x3d != 3) {
      return 0;
    }
    if ((v6 & 0xff) == 1) {
      if ((char )param_2[1] != '\x01') {
        return 0;
      }
    }
    else if ((char )param_2[1] == '\x01' || t2 != *param_2) {
      return 0;
    }
    param_1 = (long  *)0x0;
    if ((param_2[2] ^ v3) >> 0xe != 0) {
      return 0;
    }
    if ((param_2[3] ^ v13) >> 0xe != 0) {
      return 0;
    }
    v1 = (uint )param_2[5] & 0xff;
    if ((v7 & 0xff) == 1) {
      if (v1 != 1) {
        return 0;
      }
    }
    else if (v1 == 1 || t4 != param_2[4]) {
      return 0;
    }
    if ((param_2[6] ^ v5) >> 0xe != 0) {
      return 0;
    }
    v13 = param_2[7] ^ v8;
    goto LAB_0041b974;
  case 4:
    if (v7 == 0x8000000000000000 &&
        (((v3 == 0 && v6 == 0) && (t2 == 0 && v13 == 0)) &&
        ((t4 == 0 && v5 == 0) && v8 == 0))) {
      if (-0x6000000000000001 < param_2[5]) {
        return 0;
      }
      if (param_2[5] != -0x8000000000000000) {
        return 0;
      }
      t4 = param_2[4];
      t2 = param_2[3];
      b14 = *(byte  *)(param_2 + 1) | (byte)t2;
      b15 = *(byte  *)((long)param_2 + 9) | (byte)((word_t)t2 >> 8);
      b16 = *(byte  *)((long)param_2 + 10) | (byte)((word_t)t2 >> 0x10);
      b17 = *(byte  *)((long)param_2 + 0xb) | (byte)((word_t)t2 >> 0x18);
      b18 = *(byte  *)((long)param_2 + 0xc) | (byte)((word_t)t2 >> 0x20);
      b19 = *(byte  *)((long)param_2 + 0xd) | (byte)((word_t)t2 >> 0x28);
      b20 = *(byte  *)((long)param_2 + 0xe) | (byte)((word_t)t2 >> 0x30);
      b21 = *(byte  *)((long)param_2 + 0xf) | (byte)((word_t)t2 >> 0x38);
      b22 = *(byte  *)(param_2 + 2) | (byte)t4;
      b23 = *(byte  *)((long)param_2 + 0x11) | (byte)((word_t)t4 >> 8);
      b24 = *(byte  *)((long)param_2 + 0x12) | (byte)((word_t)t4 >> 0x10);
      b25 = *(byte  *)((long)param_2 + 0x13) | (byte)((word_t)t4 >> 0x18);
      b26 = *(byte  *)((long)param_2 + 0x14) | (byte)((word_t)t4 >> 0x20);
      b27 = *(byte  *)((long)param_2 + 0x15) | (byte)((word_t)t4 >> 0x28);
      b28 = *(byte  *)((long)param_2 + 0x16) | (byte)((word_t)t4 >> 0x30);
      b29 = *(byte  *)((long)param_2 + 0x17) | (byte)((word_t)t4 >> 0x38);
      sv30.bytes[1] = b15;
      sv30.bytes[0] = b14;
      sv30.bytes[2] = b16;
      sv30.bytes[3] = b17;
      sv30.bytes[4] = b18;
      sv30.bytes[5] = b19;
      sv30.bytes[6] = b20;
      sv30.bytes[7] = b21;
      sv30.bytes[8] = b22;
      sv30.bytes[9] = b23;
      sv30.bytes[10] = b24;
      sv30.bytes[0xb] = b25;
      sv30.bytes[0xc] = b26;
      sv30.bytes[0xd] = b27;
      sv30.bytes[0xe] = b28;
      sv30.bytes[0xf] = b29;
      sv11.bytes[1] = b15;
      sv11.bytes[0] = b14;
      sv11.bytes[2] = b16;
      sv11.bytes[3] = b17;
      sv11.bytes[4] = b18;
      sv11.bytes[5] = b19;
      sv11.bytes[6] = b20;
      sv11.bytes[7] = b21;
      sv11.bytes[8] = b22;
      sv11.bytes[9] = b23;
      sv11.bytes[10] = b24;
      sv11.bytes[0xb] = b25;
      sv11.bytes[0xc] = b26;
      sv11.bytes[0xd] = b27;
      sv11.bytes[0xe] = b28;
      sv11.bytes[0xf] = b29;
      sk_neon_ext8(sv30.bytes,sv30.bytes,sv11.bytes);
      if ((CONCAT17(b21 | sv30.bytes[7],
                    CONCAT16(b20 | sv30.bytes[6],
                             CONCAT15(b19 | sv30.bytes[5],
                                      CONCAT14(b18 | sv30.bytes[4],
                                               CONCAT13(b17 | sv30.bytes[3],
                                                        CONCAT12(b16 | sv30.bytes[2],
                                                                 CONCAT11(b15 | sv30.bytes[1],
                                                                          b14 | sv30.bytes[0])))))))
           != 0 || param_2[6] != 0) || (param_2[7] != 0 || *param_2 != 0)) {
        return 0;
      }
    }
    else {
      if ((v7 == 0x8000000000000000 && t2 == 1) &&
          (((v3 == 0 && v6 == 0) && v13 == 0) && ((t4 == 0 && v5 == 0) && v8 == 0)
          )) {
        if (-0x6000000000000001 < param_2[5]) {
          return 0;
        }
        if (param_2[6] != 0 || param_2[7] != 0) {
          return 0;
        }
        if (param_2[5] != -0x8000000000000000 || *param_2 != 1) {
          return 0;
        }
      }
      else {
        if (-0x6000000000000001 < param_2[5]) {
          return 0;
        }
        if (param_2[6] != 0 || param_2[7] != 0) {
          return 0;
        }
        if (param_2[5] != -0x8000000000000000 || *param_2 != 2) {
          return 0;
        }
      }
      t4 = param_2[4];
      t2 = param_2[3];
      b14 = *(byte  *)(param_2 + 1) | (byte)t2;
      b15 = *(byte  *)((long)param_2 + 9) | (byte)((word_t)t2 >> 8);
      b16 = *(byte  *)((long)param_2 + 10) | (byte)((word_t)t2 >> 0x10);
      b17 = *(byte  *)((long)param_2 + 0xb) | (byte)((word_t)t2 >> 0x18);
      b18 = *(byte  *)((long)param_2 + 0xc) | (byte)((word_t)t2 >> 0x20);
      b19 = *(byte  *)((long)param_2 + 0xd) | (byte)((word_t)t2 >> 0x28);
      b20 = *(byte  *)((long)param_2 + 0xe) | (byte)((word_t)t2 >> 0x30);
      b21 = *(byte  *)((long)param_2 + 0xf) | (byte)((word_t)t2 >> 0x38);
      b22 = *(byte  *)(param_2 + 2) | (byte)t4;
      b23 = *(byte  *)((long)param_2 + 0x11) | (byte)((word_t)t4 >> 8);
      b24 = *(byte  *)((long)param_2 + 0x12) | (byte)((word_t)t4 >> 0x10);
      b25 = *(byte  *)((long)param_2 + 0x13) | (byte)((word_t)t4 >> 0x18);
      b26 = *(byte  *)((long)param_2 + 0x14) | (byte)((word_t)t4 >> 0x20);
      b27 = *(byte  *)((long)param_2 + 0x15) | (byte)((word_t)t4 >> 0x28);
      b28 = *(byte  *)((long)param_2 + 0x16) | (byte)((word_t)t4 >> 0x30);
      b29 = *(byte  *)((long)param_2 + 0x17) | (byte)((word_t)t4 >> 0x38);
      sv9.bytes[1] = b15;
      sv9.bytes[0] = b14;
      sv9.bytes[2] = b16;
      sv9.bytes[3] = b17;
      sv9.bytes[4] = b18;
      sv9.bytes[5] = b19;
      sv9.bytes[6] = b20;
      sv9.bytes[7] = b21;
      sv9.bytes[8] = b22;
      sv9.bytes[9] = b23;
      sv9.bytes[10] = b24;
      sv9.bytes[0xb] = b25;
      sv9.bytes[0xc] = b26;
      sv9.bytes[0xd] = b27;
      sv9.bytes[0xe] = b28;
      sv9.bytes[0xf] = b29;
      sv10.bytes[1] = b15;
      sv10.bytes[0] = b14;
      sv10.bytes[2] = b16;
      sv10.bytes[3] = b17;
      sv10.bytes[4] = b18;
      sv10.bytes[5] = b19;
      sv10.bytes[6] = b20;
      sv10.bytes[7] = b21;
      sv10.bytes[8] = b22;
      sv10.bytes[9] = b23;
      sv10.bytes[10] = b24;
      sv10.bytes[0xb] = b25;
      sv10.bytes[0xc] = b26;
      sv10.bytes[0xd] = b27;
      sv10.bytes[0xe] = b28;
      sv10.bytes[0xf] = b29;
      sk_neon_ext8(sv30.bytes,sv9.bytes,sv10.bytes);
      if (CONCAT17(b21 | sv30.bytes[7],
                   CONCAT16(b20 | sv30.bytes[6],
                            CONCAT15(b19 | sv30.bytes[5],
                                     CONCAT14(b18 | sv30.bytes[4],
                                              CONCAT13(b17 | sv30.bytes[3],
                                                       CONCAT12(b16 | sv30.bytes[2],
                                                                CONCAT11(b15 | sv30.bytes[1],
                                                                         b14 | sv30.bytes[0])))))))
          != 0) {
        return 0;
      }
    }
    goto LAB_0041ba1c;
  }
  if ((v6 & 0xff) == 1) {
    if ((char )param_2[1] != '\x01') {
      return 0;
    }
  }
  else if ((char )param_2[1] == '\x01' || t2 != *param_2) {
    return 0;
  }
  if ((param_2[2] ^ v3) >> 0xe == 0) {
    v13 = param_2[3] ^ v13;
LAB_0041b974:
    if (v13 < 0x4000) {
LAB_0041ba1c:
      v12 = sk_h_0006e064(param_1);
      return v12;
    }
  }
  return 0;
}

/* FUN_0041baa4 @ 0x0041baa4   (est. sk_f_0041baa4)
 * Ghidra: void FUN_0041baa4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041baa4(void){
  long  t1;
  word_t  v2;
  long  t3;
  word_t  v4;
  word_t  v5;
  word_t  v6;
  word_t  v7;
  word_t  v8;
  word_t  v9;
  word_t  out1;
  long  *ctx;
  
  sk_h_0008e518();
  t1 = *ctx;
  v5 = ctx[1];
  v2 = ctx[2];
  v6 = ctx[3];
  t3 = ctx[4];
  v7 = ctx[5];
  v4 = ctx[6];
  v8 = ctx[7];
  switch(v7 >> 0x3d) {
  default:
    v9 = 3;
    break;
  case 1:
    v9 = 4;
    break;
  case 2:
    v9 = 5;
    break;
  case 3:
    sk_h_002298d4(6);
    if ((v5 & 0xff) == 1) {
      sk_h_00229a3c(0);
    }
    else {
      sk_h_00229a3c(1);
      sk_h_002298d4(t1);
    }
    sk_h_002298d4(v2 >> 0xe);
    sk_h_002298d4(v6 >> 0xe);
    if ((v7 & 0xff) == 1) {
      sk_h_00229a3c(0);
    }
    else {
      sk_h_00229a3c(1);
      sk_h_002298d4(t3);
    }
    sk_h_002298d4(v4 >> 0xe);
    goto LAB_0041bc08;
  case 4:
    if (v7 == 0x8000000000000000 &&
        (((v2 == 0 && v5 == 0) && (t1 == 0 && v6 == 0)) &&
        ((t3 == 0 && v4 == 0) && v8 == 0))) {
      v9 = 0;
    }
    else if ((v7 == 0x8000000000000000 && t1 == 1) &&
             (((v2 == 0 && v5 == 0) && v6 == 0) &&
             ((t3 == 0 && v4 == 0) && v8 == 0))) {
      v9 = 1;
    }
    else {
      v9 = 2;
    }
    sk_h_002298d4(v9);
    goto LAB_0041bc18;
  }
  sk_h_002298d4(v9);
  if ((v5 & 0xff) == 1) {
    sk_h_00229a3c(0);
  }
  else {
    sk_h_00229a3c(1);
    sk_h_002298d4(t1);
  }
  sk_h_002298d4(v2 >> 0xe);
  v8 = v6;
LAB_0041bc08:
  sk_h_002298d4(v8 >> 0xe);
LAB_0041bc18:
  sk_h_0008e500(out1);
  return;
}

/* FUN_0041bc58 @ 0x0041bc58   (est. sk_f_0041bc58)
 * Ghidra: void FUN_0041bc58(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041bc58(void){
  void (*r19)(void *);
  byte  l_68 [72];
  
  sk_h_004648fc();
  (*r19)(l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041bcb4 @ 0x0041bcb4   (est. sk_f_0041bcb4)
 * Ghidra: void FUN_0041bcb4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041bcb4(void){
  void (*r19)(void *);
  byte  l_68 [72];
  
  sk_h_004653c0();
  (*r19)(l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041bcf4 @ 0x0041bcf4   (est. sk_f_0041bcf4)
 * Ghidra: word_t FUN_0041bcf4(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041bcf4(void){
  word_t  ctx;
  
  sk_h_00356c6c();
  sk_h_002ad78c(0x67f928);
  sk_h_00465240();
  if (2 < ctx) {
    ctx = 3;
  }
  return ctx;
}

/* FUN_0041bd34 @ 0x0041bd34   (est. sk_f_0041bd34)
 * Ghidra: void FUN_0041bd34(undefined1 *param_1,undefined8 *param_2)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041bd34(byte* param_1, word_t* param_2){
  byte  v1;
  
  v1 = sk_f_0041bcf4(*param_2,param_2[1]);
  *param_1 = v1;
  return;
}

/* FUN_0041bd68 @ 0x0041bd68   (est. sk_f_0041bd68)
 * Ghidra: void FUN_0041bd68(undefined1 (*param_1) [16])
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041bd68(byte (*param_1)[16]){
  byte  *ctx;
  sk16_t sv1;
  
  sv1 = (sk16_t){ sk_h_0044bd08(), 0 };
  *param_1 = sv1;
  return;
}

/* FUN_0041bdac @ 0x0041bdac   (est. sk_f_0041bdac)
 * Ghidra: word_t FUN_0041bdac(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041bdac(void){
  word_t  v1;
  word_t  v2;
  long  out8;
  long  out8_00;
  long  out8_01;
  long  out8_02;
  long  out8_03;
  long  out8_04;
  long  r19;
  long  ctx;
  
  sk_h_003504d0();
  v1 = sk_f_0041b820((word_t)0,(word_t)0);
  if (((((((v1 & 1) != 0) && (sk_h_00464ad0(), out8 == 0)) &&
        (sk_h_0046622c(), out8_00 == 0)) &&
       ((*(char  *)(ctx + 0x50) == *(char *)(r19 + 0x50) &&
        (sk_h_00464d0c(*(word_t *)(r19 + 0x58)), out8_01 == 0)))) &&
      ((sk_h_00464d0c(*(word_t *)(r19 + 0x60)), out8_02 == 0 &&
       ((v1 = sk_h_0041001c(*(word_t *)(ctx + 0x68),*(word_t *)(r19 + 0x68)),
        (v1 & 1) != 0 && (sk_h_00464d0c(*(word_t *)(ctx + 0x70)), out8_03 == 0)))
       ))) && (sk_h_00464d0c(*(word_t *)(r19 + 0x78)), out8_04 == 0)) {
    v2 = sk_h_00411308(*(word_t *)(ctx + 0x80),*(word_t *)(r19 + 0x80));
    return v2;
  }
  return 0;
}

/* FUN_0041be80 @ 0x0041be80   (est. sk_f_0041be80)
 * Ghidra: void FUN_0041be80(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041be80(void){
  word_t  v1;
  long  r19;
  long  ctx;
  
  sk_h_00464a38();
  v1 = *(word_t *)(ctx + 0x48);
  sk_f_0041baa4();
  sk_h_00466660();
  sk_h_002298d4(v1 >> 0xe);
  sk_h_0044929c();
  sk_h_00410414();
  v1 = *(word_t *)(r19 + 0x78);
  sk_h_002298d4(*(word_t *)(r19 + 0x70) >> 0xe);
  sk_h_002298d4(v1 >> 0xe);
  sk_h_0045811c();
  return;
}

/* FUN_0041bf18 @ 0x0041bf18   (est. sk_f_0041bf18)
 * Ghidra: void FUN_0041bf18(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041bf18(void){
  void (*r19)(void *);
  byte  l_68 [72];
  
  sk_h_004648fc();
  (*r19)(l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041bf74 @ 0x0041bf74   (est. sk_f_0041bf74)
 * Ghidra: void FUN_0041bf74(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041bf74(void){
  void (*r19)(void *);
  byte  l_68 [72];
  
  sk_h_004653c0();
  (*r19)(l_68);
  sk_h_001a8564();
  return;
}

/* FUN_0041bfb4 @ 0x0041bfb4   (est. sk_f_0041bfb4)
 * Ghidra: sk16_t FUN_0041bfb4(void)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041bfb4(void){
  word_t  v1;
  byte  (*ctx) [16];
  sk16_t sv2;
  
  v1 = *(word_t *)(ctx[2] + 8);
  switch(v1 >> 0x3d) {
  default:
    return *ctx;
  case 1:
    return *ctx;
  case 2:
    return ZEXT816(0);
  case 3:
    return *ctx;
  case 4:
    break;
  }
  if (v1 == 0x8000000000000000 &&
      (((*(long  *)ctx[2] == 0 && *(long *)(*ctx + 8) == 0) &&
       (*(long *)*ctx == 0 && *(long *)(ctx[3] + 8) == 0)) &&
      ((*(long *)ctx[3] == 0 && *(long *)(ctx[1] + 8) == 0) &&
      *(long *)ctx[1] == 0))) {
    v1 = 0;
  }
  else {
    if ((v1 != 0x8000000000000000 || *(long  *)*ctx != 1) ||
       (((*(long *)ctx[2] != 0 || *(long *)(*ctx + 8) != 0) ||
        *(long *)(ctx[3] + 8) != 0) ||
        ((*(long *)ctx[3] != 0 || *(long *)(ctx[1] + 8) != 0) ||
        *(long *)ctx[1] != 0))) {
      return ZEXT816(0);
    }
    v1 = 1;
  }
  sv2.hi = 0;
  sv2.lo = v1;
  return sv2;
}

/* FUN_0041c0c0 @ 0x0041c0c0   (est. sk_f_0041c0c0)
 * Ghidra: void FUN_0041c0c0(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041c0c0(void){
  word_t l_sk_stack;
  word_t  *pv1;
  long  out8;
  long  t2;
  long  *ctx;
  long  unaff_x25;
  word_t  v3;
  word_t  v4;
  word_t  v5;
  word_t  v6;
  word_t  v7;
  word_t  v8;
  sk16_t sv9;
  
  sv9 = (sk16_t){ sk_h_00466568(), 0 };
  pv1 = sv9.lo;
  sk_h_00458da0(pv1,(word_t*)l_sk_stack);
  sk_h_004578dc(sk_h_00455f60,sk_h_000722b0,sk_h_00456858,sk_h_0045636c);
  sk_h_00463708();
  sk_h_00462b6c();
  sk_h_00457994();
  sk_h_00463ab8();
  t2 = out8 + unaff_x25 * 0x38;
  v4 = pv1[1];
  v3 = *pv1;
  v6 = pv1[3];
  v5 = pv1[2];
  v8 = pv1[5];
  v7 = pv1[4];
  *(byte  *)(t2 + 0x50) = *(byte *)(pv1 + 6);
  *(word_t *)(t2 + 0x38) = v6;
  *(word_t *)(t2 + 0x30) = v5;
  *(word_t *)(t2 + 0x48) = v8;
  *(word_t *)(t2 + 0x40) = v7;
  *(word_t *)(t2 + 0x28) = v4;
  *(word_t *)(t2 + 0x20) = v3;
  *ctx = out8;
  sk_h_00466528(sv9.hi);
  return;
}

/* FUN_0041c190 @ 0x0041c190   (est. sk_f_0041c190)
 * Ghidra: void FUN_0041c190(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041c190(void){
  long  ctx;
  
  sk_h_0036b270(*(word_t *)(ctx + 8));
  sk_h_0009461c();
  return;
}

/* FUN_0041c1c4 @ 0x0041c1c4   (est. sk_f_0041c1c4)
 * Ghidra: void FUN_0041c1c4(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,                  undefined8 param_5,undefined1 param_6,undefined8 param_7,undefined8 param_8)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041c1c4(word_t* param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, byte param_6, word_t param_7, word_t param_8){
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  param_1[4] = param_7;
  param_1[5] = param_8;
  *(byte  *)(param_1 + 6) = param_6;
  return;
}

/* FUN_0041c1d8 @ 0x0041c1d8   (est. sk_f_0041c1d8)
 * Ghidra: sk16_t FUN_0041c1d8(undefined8 param_1,undefined8 param_2,long param_3)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041c1d8(word_t param_1, word_t param_2, long param_3){
  word_t  v1;
  word_t  v2;
  long  t3;
  long  ctx;
  long  r21;
  long  t4;
  long  *pt5;
  sk16_t sv6;
  
  t4 = *(long  *)(param_3 + 0x10);
  if (t4 != 0) {
    sk_h_0035098c();
    t3 = 0;
    pt5 = (long  *)(param_3 + 0x28);
    do {
      if ((*pt5 != 0) &&
         ((pt5[-1] == r21 && *pt5 == ctx ||
          (v1 = sk_h_004633f4(), (v1 & 1) != 0)))) {
        v2 = 0;
        goto LAB_0041c244;
      }
      t3 = t3 + 1;
      pt5 = pt5 + 7;
    } while (t4 != t3);
  }
  t3 = 0;
  v2 = 1;
LAB_0041c244:
  sv6.hi = v2;
  sv6.lo = t3;
  return sv6;
}

/* FUN_0041c25c @ 0x0041c25c   (est. sk_f_0041c25c)
 * Ghidra: sk16_t FUN_0041c25c(void)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041c25c(void){
  return ZEXT416(0x10f800) << 0x40;
}

/* FUN_0041c26c @ 0x0041c26c   (est. sk_f_0041c26c)
 * Ghidra: bool FUN_0041c26c(void)
 * 
 * Confidence: medium
 * Notes:  */
bool sk_f_0041c26c(void){
  byte  in_flags;
  
  sk_f_0041c1d8((word_t)0,(word_t)0,(word_t)0);
  sk_h_00351db4();
  return !(bool )in_flags;
}

/* FUN_0041c270 @ 0x0041c270   (est. sk_f_0041c270)
 * Ghidra: bool FUN_0041c270(void)
 * 
 * Confidence: medium
 * Notes:  */
bool sk_f_0041c270(void){
  byte  in_flags;
  
  sk_f_0041c1d8((word_t)0,(word_t)0,(word_t)0);
  sk_h_00351db4();
  return !(bool )in_flags;
}

/* FUN_0041c28c @ 0x0041c28c   (est. sk_f_0041c28c)
 * Ghidra: sk16_t FUN_0041c28c(uint param_1)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041c28c(uint param_1){
  return ZEXT416(param_1 & 1) << 0x40;
}

/* FUN_0041c29c @ 0x0041c29c   (est. sk_f_0041c29c)
 * Ghidra: long FUN_0041c29c(long param_1,undefined8 param_2,long param_3)
 * 
 * Confidence: medium
 * Notes:  */
long sk_f_0041c29c(long param_1, word_t param_2, long param_3){
  code_t  *pcVar1;
  
  if (!SCARRY8(param_1,param_3)) {
    return param_1 + param_3;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code_t *)sk_trap(1,0x41c2ac);
  (*pcVar1)();
}

/* FUN_0041c2ac @ 0x0041c2ac   (est. sk_f_0041c2ac)
 * Ghidra: sk16_t FUN_0041c2ac(ulong param_1,ulong param_2,long param_3)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041c2ac(word_t param_1, word_t param_2, long param_3){
  code_t  *pcVar1;
  bool  b2;
  sk16_t sv3;
  
  if (((param_2 & 1) != 0) && (b2 = SCARRY8(param_1,param_3), param_1 = param_1 + param_3, b2)
     ) {
                    /* WARNING: Does not return */
    pcVar1 = (code_t *)sk_trap(1,0x41c2c8);
    (*pcVar1)();
  }
  sv3.hi = 0;
  sv3.lo = param_1;
  return sv3;
}

/* FUN_0041c2c8 @ 0x0041c2c8   (est. sk_f_0041c2c8)
 * Ghidra: void FUN_0041c2c8(undefined8 param_1,ulong param_2,long param_3)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041c2c8(word_t param_1, word_t param_2, long param_3){
  code_t  *pcVar1;
  
  if (((param_2 & 1) != 0) && (SCARRY8(param_3,1))) {
                    /* WARNING: Does not return */
    pcVar1 = (code_t *)sk_trap(1,0x41c2d8);
    (*pcVar1)();
  }
  return;
}

/* FUN_0041c2e4 @ 0x0041c2e4   (est. sk_f_0041c2e4)
 * Ghidra: void FUN_0041c2e4(undefined8 param_1,undefined8 param_2,ulong param_3,long param_4,byte param_5)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041c2e4(word_t param_1, word_t param_2, word_t param_3, long param_4, byte param_5){
  word_t  v1;
  code_t  *pcVar2;
  int iVar3;
  word_t  v4;
  word_t  v5;
  long  out8;
  long  out8_00;
  long  out8_01;
  long  out8_02;
  long  out8_03;
  long  out9;
  long  out9_00;
  long  out9_01;
  word_t  v6;
  long  out12;
  long  *ctx;
  uint  v7;
  word_t  v8;
  word_t  v9;
  word_t  v10;
  long  t11;
  long  t12;
  word_t  r30;
  sk16_t sv13;
  word_t  l_118;
  long  lStack_110;
  word_t  l_108;
  word_t  l_f8;
  word_t  l_e8;
  word_t  l_d8;
  char  l_c8;
  byte  l_88 [136];
  
  sv13 = (sk16_t){ sk_h_0008e518(), 0 };
  t11 = sv13.hi;
  v9 = sv13.lo;
  v7 = (uint )param_3;
  switch(v9 >> 0x3c) {
  default:
    v8 = *(word_t *)(v9 + 0x10);
    t11 = *(long  *)(v8 + 0x10);
    if (t11 == 0) break;
    sk_h_0036b270(v8);
    t12 = 0x20;
    do {
      if ((v7 & SCARRY8(param_4,1)) != 0) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41c9e0);
        (*pcVar2)();
      }
      v9 = *(word_t *)(v8 + t12);
      sv13 = (sk16_t){ sk_h_0036b270(), 0 };
      sk_h_00464308(sv13.lo,sv13.hi,v7 & 1);
      sk_f_0041c2e4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
      sk_h_0036b118(v9 & 0xfffffffffffffff);
      t12 = t12 + 8;
      t11 = t11 + -1;
    } while (t11 != 0);
    goto LAB_0041c89c;
  case 1:
    v8 = *(word_t *)((v9 & 0xfffffffffffffff) + 0x10);
    t11 = *(long  *)(v8 + 0x10);
    if (t11 != 0) {
      sk_h_0036b270(v8);
      t12 = 0x20;
      do {
        v9 = *(word_t *)(v8 + t12);
        sv13 = (sk16_t){ sk_h_0036b270(), 0 };
        sk_h_00464308(sv13.lo,sv13.hi,v7 & 1);
        sk_f_0041c2e4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
        sk_h_0036b118(v9 & 0xfffffffffffffff);
        t12 = t12 + 8;
        t11 = t11 + -1;
      } while (t11 != 0);
      goto LAB_0041c89c;
    }
    break;
  case 2:
    sk_h_00117cc4(&l_118,(v9 & 0xfffffffffffffff) + 0x10,0x68);
    v8 = *(word_t *)((v9 & 0xfffffffffffffff) + 0x78);
    if (l_c8 == '\0') {
      if (SCARRY8(t11,param_4)) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41c9f0);
        (*pcVar2)();
      }
      sk_h_00464f58();
      sk_h_00351aec();
      sk_h_0045908c();
      sk_h_00464f58();
      sk_h_00351aec();
      sk_h_0045908c();
      sk_h_0036b270();
      sk_h_004578dc(sk_h_00455f60,sk_h_000722b0,sk_h_00456858,sk_h_0045636c);
      v4 = sk_h_00463708();
      sk_h_00457994(v4,sk_h_00455f60,sk_h_000722b0,sk_h_00456858,sk_h_0045636c);
      sk_h_00465a14();
      sk_h_00463ab8();
      *(word_t *)(out8_01 + 0x13c05da0) = l_118;
      *(long  *)(out8_01 + 0x13c05da8) = lStack_110;
      sk_h_004652f4();
      t11 = out8_02;
      t12 = out9_00;
LAB_0041c9a4:
      *(byte  *)(t12 + 0x50) = param_5 & 1;
      *ctx = t11;
    }
    else {
      if (l_c8 == '\x01') {
        if (SCARRY8(t11,param_4)) {
                    /* WARNING: Does not return */
          pcVar2 = (code_t *)sk_trap(1,0x41c9ec);
          (*pcVar2)();
        }
        v4 = 0;
        if (lStack_110 != 0) {
          v4 = l_118;
        }
        sk_h_004637b4();
        sk_h_00464f58();
        sk_h_0045908c();
        sk_h_0036b270();
        sk_h_0036b270(lStack_110);
        sk_h_004578dc(sk_h_00455f60,sk_h_000722b0,sk_h_00456858,sk_h_0045636c);
        t11 = *(long  *)(*ctx + 0x10);
        sk_h_004632a4();
        sk_h_00457994();
        sk_h_00465a14();
        sk_h_00463ab8();
        t11 = out8 + t11 * 0x38;
        *(word_t *)(t11 + 0x20) = v4;
        *(long  *)(t11 + 0x28) = lStack_110;
        sk_h_004652f4();
        t11 = out8_00;
        t12 = out9;
        goto LAB_0041c9a4;
      }
      if ((l_c8 == '\x03') &&
         (t12 = sk_h_00463558(l_e8,l_d8,l_108,l_f8),
         (t12 == 0 && out12 == 0) && lStack_110 == 0)) {
        if (SCARRY8(t11,param_4)) {
                    /* WARNING: Does not return */
          pcVar2 = (code_t *)sk_trap(1,0x41c9f4);
          (*pcVar2)();
        }
        sk_h_004637b4();
        sk_h_00464f58();
        sk_h_0045908c();
        sk_h_0036b270();
        sk_h_003a25d4(0);
        sk_h_004578dc(sk_h_00455f60,sk_h_000722b0,sk_h_00456858,sk_h_0045636c);
        t12 = *(long  *)(*ctx + 0x10);
        sk_h_00353bc4(t12,sk_h_00455f60,sk_h_000722b0);
        sk_h_00457994();
        t11 = *ctx;
        *(long  *)(t11 + 0x10) = t12 + 1;
        t11 = t11 + t12 * 0x38;
        *(word_t *)(t11 + 0x20) = 0;
        *(word_t *)(t11 + 0x28) = 0;
        sk_h_004652f4();
        t11 = out8_03;
        t12 = out9_01;
        goto LAB_0041c9a4;
      }
      sk_h_0036b270(v8 & 0xfffffffffffffff);
    }
    sk_h_00464d68();
    sk_h_003505e8();
    sk_f_0041c2e4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
    goto LAB_0041c9c0;
  case 3:
    v9 = v9 & 0xfffffffffffffff;
    sk_h_00117cc4(&l_118,v9 + 0x20,0x90);
    v10 = *(word_t *)(v9 + 0xb0);
    v8 = *(word_t *)(v9 + 0xd0);
    sk_h_00117cc4(l_88,v9 + 0x20,0x80);
    iVar3 = sk_h_00458cb8(&l_118);
    if (iVar3 == 3) {
      v4 = sk_h_00458cd4(l_88);
      sk_h_00465884(sk_h_0067f9a0);
      v9 = sk_h_0036a940();
      sk_h_00117cc4(v9 + 0x10,v4,0x80);
      sk_h_00464f58();
      sk_h_00458c98();
      sk_h_00464f58();
      sk_h_00458c98();
      sk_h_0036b270(v8 & 0xfffffffffffffff);
      sk_h_0036b270(v10 & 0xfffffffffffffff);
      v4 = sk_h_00464d68(v9 | 0x2000000000000000);
      sk_f_0041c2e4(v4,t11,(word_t)0,(word_t)0,(word_t)0);
      sk_h_0036b118(v9);
      sk_h_00458e28(&l_118);
      if ((param_3 & 1) != 0) goto LAB_0041c5cc;
LAB_0041c500:
      sk_h_00464308();
    }
    else {
      sk_h_0036b270(v8 & 0xfffffffffffffff);
      sk_h_0036b270(v10 & 0xfffffffffffffff);
      if ((param_3 & 1) == 0) goto LAB_0041c500;
LAB_0041c5cc:
      if (SCARRY8(param_4,1)) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41c9e4);
        (*pcVar2)();
      }
      sk_h_0006b6a0(v10);
    }
    sk_f_0041c2e4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
    sk_h_0036b118(v10 & 0xfffffffffffffff);
    sk_h_00464d68();
    sk_h_003514e8();
    sk_f_0041c2e4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
LAB_0041c9c0:
    sk_h_0036b118(v8 & 0xfffffffffffffff);
    break;
  case 4:
    v9 = v9 & 0xfffffffffffffff;
    v10 = *(word_t *)(v9 + 0x10);
    v1 = *(word_t *)(v9 + 0x18);
    v5 = *(word_t *)(v9 + 0x38);
    v8 = *(word_t *)(v9 + 0x78);
    v6 = 0;
    switch(v5 >> 0x3d) {
    default:
      v6 = v10;
      if ((v1 & 0xff) != 1) goto switchD_0041c59c_caseD_2;
      break;
    case 4:
      if (v5 == 0x8000000000000000 &&
          (((v1 == 0 && v10 == 0) &&
           (*(long  *)(v9 + 0x48) == 0 && *(long *)(v9 + 0x40) == 0)) &&
          ((*(long *)(v9 + 0x30) == 0 && *(long *)(v9 + 0x28) == 0) &&
          *(long *)(v9 + 0x20) == 0))) {
        v6 = 0;
      }
      else {
        v6 = (word_t)((v10 == 1 &&
                        (((*(long  *)(v9 + 0x48) == 0 && v1 == 0) &&
                         (*(long *)(v9 + 0x40) == 0 && *(long *)(v9 + 0x30) == 0)) &&
                        (*(long *)(v9 + 0x28) == 0 && *(long *)(v9 + 0x20) == 0))) &&
                       v5 == 0x8000000000000000);
      }
    case 2:
switchD_0041c59c_caseD_2:
      if (((v6 == 0) && ((param_3 & 1) != 0)) && (SCARRY8(param_4,1))) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41c9e8);
        (*pcVar2)();
      }
    }
    sk_h_0036b270(v8 & 0xfffffffffffffff);
    sk_h_00464d68();
    sk_h_003514e8();
    sk_f_0041c2e4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
    v8 = v8 & 0xfffffffffffffff;
LAB_0041c89c:
    sk_h_0008e500(v8,r30);
    sk_h_0036b118();
    return;
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 0xb:
    break;
  case 10:
    v8 = *(word_t *)((v9 & 0xfffffffffffffff) + 0x38);
    if ((v8 & 6) == 2) {
      sk_h_0036b270(v8 & 0xffffffffffffff9);
      v4 = sk_h_00464d68(v8 & 0xfffffffffffffff9);
      sk_f_0041c2e4(v4,t11,(word_t)0,(word_t)0,(word_t)0);
      v8 = v8 & 0xffffffffffffff9;
      goto LAB_0041c89c;
    }
  }
  sk_h_0008e500(r30);
  return;
}

/* FUN_0041ca38 @ 0x0041ca38   (est. sk_f_0041ca38)
 * Ghidra: long FUN_0041ca38(void)
 * 
 * Confidence: medium
 * Notes:  */
long sk_f_0041ca38(){
  word_t  v1;
  long  t2;
  word_t  v3;
  long  t4;
  
  sk_h_003a25d4(0);
  sk_h_00465488();
  t2 = sk_h_0045636c();
  v1 = *(word_t *)(t2 + 0x10);
  if (*(word_t *)(t2 + 0x18) >> 1 <= v1) {
    v3 = sk_h_0006b42c();
    t2 = sk_h_0045636c(v3,v1 + 1,1);
  }
  *(word_t *)(t2 + 0x10) = v1 + 1;
  t4 = t2 + v1 * 0x38;
  *(word_t *)(t4 + 0x20) = 0;
  *(word_t *)(t4 + 0x28) = 0;
  *(word_t *)(t4 + 0x30) = 0x675c68 /* "h\g" */;
  v3 = 0;
  *(word_t *)(t4 + 0x40) = 0;
  *(word_t *)(t4 + 0x38) = v3;
  *(word_t *)(t4 + 0x48) = 0xf;
  *(byte  *)(t4 + 0x50) = 1;
  v3 = sk_h_003567c8();
  sk_f_0041c2e4(v3,0,0,0,1);
  return t2;
}

/* FUN_0041cb78 @ 0x0041cb78   (est. sk_f_0041cb78)
 * Ghidra: sk16_t FUN_0041cb78(void)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041cb78(void){
  sk16_t sv1;
  
  sv1.hi = 0xf;
  sv1.lo = 0xf;
  return sv1;
}

/* FUN_0041cb8c @ 0x0041cb8c   (est. sk_f_0041cb8c)
 * Ghidra: word_t FUN_0041cb8c(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_0041cb8c(void){
  byte  v1;
  long  t2;
  word_t  v3;
  long  t4;
  long  out8;
  long  *r19;
  long  *ctx;
  
  t2 = sk_h_003504d0().lo;
  t4 = r19[1];
  if (*(long  *)(t2 + 8) == 0) {
    if (t4 != 0) {
      return 0;
    }
    sk_h_003552a0();
    sk_h_00458da0();
  }
  else {
    if (t4 == 0) {
      sk_h_003552a0();
      sk_h_00458da0();
      return 0;
    }
    if ((*ctx != *r19 || *(long  *)(t2 + 8) != t4) &&
       (v3 = sk_h_002a0cf8(), (v3 & 1) == 0)) {
      return 0;
    }
  }
  if ((((ctx[3] == r19[3]) &&
       (v1 = (word_t)r19[2] <= (word_t)ctx[2], ctx[2] == r19[2])) &&
      (sk_h_00464d0c(ctx[4]), out8 == 0)) && (sk_h_00465264(r19[5]), !(bool )v1))
  {
    return 1;
  }
  return 0;
}

/* FUN_0041cc48 @ 0x0041cc48   (est. sk_f_0041cc48)
 * Ghidra: uint FUN_0041cc48(undefined8 param_1,undefined8 *param_2)
 * 
 * Confidence: medium
 * Notes:  */
uint sk_f_0041cc48(word_t param_1, word_t* param_2){
  uint  v1;
  word_t  l_50;
  word_t  l_48;
  word_t  l_40;
  word_t  l_38;
  word_t  l_30;
  word_t  l_28;
  byte  l_20;
  
  l_48 = param_2[1];
  l_50 = *param_2;
  l_38 = param_2[3];
  l_40 = param_2[2];
  l_28 = param_2[5];
  l_30 = param_2[4];
  l_20 = *(byte  *)(param_2 + 6);
  v1 = sk_f_0041cb8c(param_1,&l_50);
  return v1 & 1;
}

/* FUN_0041cc98 @ 0x0041cc98   (est. sk_f_0041cc98)
 * Ghidra: sk16_t FUN_0041cc98(void)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041cc98(void){
  word_t  v1;
  word_t  v2;
  long  ctx;
  sk16_t sv3;
  word_t  l_58;
  word_t  l_50;
  word_t  l_48;
  
  l_48 = *(word_t *)(ctx + 0x10);
  l_58 = 0;
  l_50 = 0xe000000000000000;
  sv3 = (sk16_t){ sk_h_0046647c(), 0 };
  sk_h_00465db0(sv3.lo,sv3.hi,sv3.lo);
  sk_h_0046299c();
  sk_h_00205844(&l_48,&l_58);
  v2 = l_50;
  v1 = l_58;
  sk_h_001ed960(0x3f,0xe100000000000000,*(word_t *)(ctx + 0x18));
  sk_h_000b43e8();
  l_58 = v1;
  l_50 = v2;
  sk_h_0036b270(v2);
  sk_h_000b4390();
  sk_h_002acbb8();
  sk_h_003a25d4(v2);
  sk_h_003a25d4();
  sv3.hi = l_50;
  sv3.lo = l_58;
  return sv3;
}

/* FUN_0041cd40 @ 0x0041cd40   (est. sk_f_0041cd40)
 * Ghidra: void FUN_0041cd40(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041cd40(void){
  word_t l_sk_stack;
  long  t1;
  word_t  out1;
  long  r19;
  word_t  v2;
  long  t3;
  word_t  r22;
  word_t  *pv4;
  sk16_t sv5;
  sk16_t sv6;
  word_t  in_stack_00000018;
  word_t  in_stack_00000020;
  word_t  in_stack_00000028;
  word_t  in_stack_00000030;
  word_t  in_stack_00000038;
  byte  in_stack_00000040;
  
  sv5 = (sk16_t){ sk_h_000b4594(), 0 };
  t3 = *(long  *)(sv5.lo + 0x10);
  t1 = sk_h_000a6fe0();
  if (t3 != 0) {
    sk_h_004651a8();
    pv4 = (word_t *)(t1 + 0x28);
    do {
      in_stack_00000038 = pv4[4];
      in_stack_00000040 = *(byte  *)(pv4 + 5);
      in_stack_00000020 = pv4[1];
      in_stack_00000018 = *pv4;
      in_stack_00000030 = pv4[3];
      in_stack_00000028 = pv4[2];
      v2 = pv4[2];
      sk_h_0036b270(*pv4);
      sv6 = (sk16_t){ sk_h_00002534(), 0 };
      sk_h_0046299c(sv6.lo,sv6.hi,sv6.lo);
      sk_h_00205844((word_t*)l_sk_stack);
      sk_h_001ed960(0x3f,0xe100000000000000,v2);
      sk_h_0036b270(0xe000000000000000);
      sk_h_00350a04();
      sk_h_002acbb8();
      sk_h_003a25d4(0xe000000000000000);
      sk_h_003a25d4(out1);
      sk_h_003a25d4(in_stack_00000018);
      r22 = *(word_t *)(r19 + 0x10);
      if (*(word_t *)(r19 + 0x18) >> 1 <= r22) {
        sk_h_0006a374(1 < *(word_t *)(r19 + 0x18),r22 + 1,1);
      }
      pv4 = pv4 + 7;
      *(word_t *)(r19 + 0x10) = r22 + 1;
      t1 = r19 + r22 * 0x10;
      *(word_t *)(t1 + 0x20) = 0;
      *(word_t *)(t1 + 0x28) = 0xe000000000000000;
      t3 = t3 + -1;
    } while (t3 != 0);
  }
  sk_h_00463210();
  v2 = sk_h_00462898();
  sk_h_001bc440(0x202c,0xe200000000000000,r22,v2);
  sk_h_000b43e8();
  sk_h_0036b118(r19);
  sk_h_00465800(0x28);
  sk_h_000b4390();
  sk_h_002acbb8();
  sk_h_003a25d4(r22);
  sk_h_0036b270(in_stack_00000018);
  sk_h_00100e34();
  sk_h_002acbb8();
  sk_h_003a25d4(in_stack_00000018);
  sk_h_000b45b0(r19,in_stack_00000018,sv5.hi);
  return;
}

/* FUN_0041cf18 @ 0x0041cf18   (est. sk_f_0041cf18)
 * Ghidra: void FUN_0041cf18(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4,long param_5,                  long param_6,long param_7,ulong param_8)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041cf18(word_t param_1, word_t param_2, long param_3, word_t param_4, long param_5, long param_6, long param_7, word_t param_8){
  word_t  v1;
  word_t  v2;
  byte  v3;
  byte  v4;
  uint  v5;
  word_t  v6;
  word_t  out8;
  word_t  v7;
  word_t  v8;
  sk16_t sv9;
  sk16_t sv10;
  
  sv9 = (sk16_t){ sk_h_00084220(), 0 };
  sv10.hi = param_6;
  sv10.lo = param_5;
  if ((param_4 & 0xff) == 0) {
    if ((param_8 & 0xff) == 0) {
      if (sv9.hi == 0) {
        if (param_6 == 0) goto LAB_0041d018;
      }
      else if (param_6 != 0) {
        if (sv9 != sv10) {
          sk_h_00354828();
          v6 = sk_h_002a0cf8();
          if ((v6 & 1) == 0) goto LAB_0041d034;
        }
LAB_0041d018:
        if (param_3 == 0) {
          if (param_7 == 0) goto LAB_0041d028;
        }
        else if ((param_7 != 0) && (param_3 == param_7)) {
LAB_0041d028:
          v5 = 1;
          goto LAB_0041d038;
        }
      }
    }
LAB_0041d034:
    v5 = 0;
  }
  else {
    if (((uint )param_4 & 0xff) == 1) {
      if (((uint)param_8 & 0xff) != 1) goto LAB_0041d034;
      v1 = *(word_t *)(sv9.lo + 0x20);
      v7 = *(word_t *)(param_5 + 0x10);
      v2 = *(word_t *)(param_5 + 0x18);
      v8 = *(word_t *)(param_5 + 0x20);
      v3 = *(byte  *)(param_5 + 0x28);
      v4 = *(byte  *)(sv9.lo + 0x28);
      sk_h_0034d868();
      sk_h_00460d94();
      sv10 = (sk16_t){ sk_h_000b43d0(), 0 };
      v5 = sk_f_0041cf18(sv10.lo,sv10.hi,v1,v4,v7,v2,v8,v3);
      sk_h_0034d868();
      sk_h_00458e80();
    }
    else {
      if (((uint )param_8 & 0xff) != 2) goto LAB_0041d034;
      v7 = *(word_t *)(param_5 + 0x10);
      sk_h_0036b270(v7);
      sk_h_0009461c();
      v5 = sk_h_004114fc();
      sk_h_0036b118(v7);
    }
    v5 = v5 & 1;
  }
LAB_0041d038:
  sk_h_00084234(v5,out8);
  return;
}

/* FUN_0041d070 @ 0x0041d070   (est. sk_f_0041d070)
 * Ghidra: void FUN_0041d070(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d070(void){
  word_t  in_x4;
  uint  v1;
  word_t  in_x5;
  long  unaff_x24;
  word_t  r30;
  sk16_t sv3;
  word_t  v2;
  
  sk_h_00354744();
  v2 = in_x5;
  sk_h_00351dc0();
  v1 = (uint )v2;
  sk_h_003504d0();
  sk_h_0035053c();
  sk_h_002cb61c();
  if (((v1 & 0xff) != 2) || (*(long  *)(*(long *)(unaff_x24 + 0x10) + 0x10) != 0)) {
    sv3 = (sk16_t){ sk_h_00350518(), 0 };
    sk_f_0041d180(sv3.lo,sv3.hi,in_x4,in_x5,1,(word_t)0,(word_t)0,(word_t)0);
  }
  sk_h_0035053c(0,2);
  sk_f_0041d14c((word_t)0,(word_t)0,(word_t)0,(word_t)0);
  sk_h_003544c8(r30);
  return;
}

/* FUN_0041d14c @ 0x0041d14c   (est. sk_f_0041d14c)
 * Ghidra: void FUN_0041d14c(undefined1 param_1,long param_2,long param_3,long param_4)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d14c(byte param_1, long param_2, long param_3, long param_4){
  long  t1;
  code_t  *pcVar2;
  
  if (param_2 < 0) {
                    /* WARNING: Does not return */
    pcVar2 = (code_t *)sk_trap(1,0x41d178);
    (*pcVar2)();
  }
  if (!SCARRY8(param_2,1)) {
    t1 = 0;
    if (param_3 != 0) {
      t1 = param_4 - param_3;
    }
    if (param_2 + 1 <= t1) {
      *(byte  *)(param_3 + param_2) = param_1;
      return;
    }
                    /* WARNING: Does not return */
    pcVar2 = (code_t *)sk_trap(1,0x41d180);
    (*pcVar2)();
  }
                    /* WARNING: Does not return */
  pcVar2 = (code_t *)sk_trap(1,0x41d17c);
  (*pcVar2)();
}

/* FUN_0041d180 @ 0x0041d180   (est. sk_f_0041d180)
 * Ghidra: void FUN_0041d180(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4,uint param_5,                  undefined8 param_6,undefined8 param_7,long *param_8)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d180(word_t param_1, word_t param_2, long param_3, word_t param_4, uint param_5, word_t param_6, word_t param_7, long* param_8){
  uint  v1;
  code_t  *pcVar2;
  byte  v3;
  long  t4;
  word_t  out8;
  long  out8_00;
  long  out8_01;
  long  out8_02;
  long  out8_03;
  long  t5;
  long  t6;
  byte  *pv7;
  word_t  v8;
  long  t9;
  sk16_t sv10;
  
  sv10 = (sk16_t){ sk_h_00351e20(), 0 };
  v1 = (uint )param_4 & 0xff;
  v3 = 0;
  if ((param_4 & 0xff) == 0) {
    if (param_3 != 0) {
      sk_h_00002874(0);
      sk_h_003593c0();
      sk_h_00002818();
                    /* WARNING: Subroutine does not return */
      sk_h_001afa84();
    }
    if (sv10.hi == 0) {
      sk_h_003523fc(1,*param_8);
      sk_f_0041d14c((word_t)0,(word_t)0,(word_t)0,(word_t)0);
      sk_h_00465d3c();
      t6 = out8_03;
      if ((bool )v3) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41d350);
        (*pcVar2)();
      }
    }
    else {
      sk_h_003523fc(2,*param_8);
      sk_f_0041d14c((word_t)0,(word_t)0,(word_t)0,(word_t)0);
      t6 = *param_8 + 1;
      if (SCARRY8(*param_8,1)) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41d398);
        (*pcVar2)();
      }
      *param_8 = t6;
      sk_h_00350470();
      t9 = sk_h_00268540();
      t5 = *(long  *)(t9 + 0x10);
      if (SCARRY8(t6,t5)) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41d39c);
        (*pcVar2)();
      }
      if (t6 + t5 < t6) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41d3a0);
        (*pcVar2)();
      }
      sk_h_003523fc(t6);
      sv10 = (sk16_t){ sk_h_003207d4(), 0 };
      t6 = 0;
      if (param_3 != 0) {
        t6 = param_3 + sv10.lo;
      }
      t4 = sv10.hi - sv10.lo;
      if (t4 < 0) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41d3a4);
        (*pcVar2)();
      }
      if (t4 == 0) {
        if (t6 != 0) goto LAB_0041d354;
        t4 = 0;
      }
      else {
        if (t6 == 0) {
                    /* WARNING: Does not return */
          pcVar2 = (code_t *)sk_trap(1,0x41d3b0);
          (*pcVar2)();
        }
LAB_0041d354:
        t4 = t6 + t4;
      }
      sk_h_002cb61c(t9 + 0x20,t9 + 0x20 + *(long  *)(t9 + 0x10),t6,t4);
      sk_h_0036b118(t9);
      t6 = *param_8 + t5;
      if (SCARRY8(*param_8,t5)) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41d3a8);
        (*pcVar2)();
      }
    }
  }
  else {
    v3 = SBORROW4(v1,1);
    if (v1 == 1) {
      v8 = *(word_t *)(sv10.lo + 0x10);
      sk_h_00350b18(v8);
      sk_h_00460d94();
      sk_h_00350b18(v8);
      sk_h_00466580();
      sk_h_00350b18(v8);
      sk_h_00458e80();
      sk_h_003523fc(4,*param_8);
      sk_f_0041d14c((word_t)0,(word_t)0,(word_t)0,(word_t)0);
      sk_h_00465d3c();
      t6 = out8_00;
      if ((bool )v3) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41d210);
        (*pcVar2)();
      }
    }
    else {
      t6 = *(long  *)(sv10.lo + 0x10);
      if ((param_5 & 1) == 0) {
        sk_h_003523fc(5,*param_8);
        sk_f_0041d14c((word_t)0,(word_t)0,(word_t)0,(word_t)0);
        sk_h_00465d3c();
        if ((bool )v3) {
                    /* WARNING: Does not return */
          pcVar2 = (code_t *)sk_trap(1,0x41d3ac);
          (*pcVar2)();
        }
        *param_8 = out8_01;
        v3 = false;
      }
      t9 = *(long  *)(t6 + 0x10);
      if (t9 != 0) {
        sk_h_0036b270(t6);
        pv7 = (byte  *)(t6 + 0x38);
        do {
          v8 = *(word_t *)(pv7 + -8);
          v3 = *pv7;
          sv10 = (sk16_t){ sk_h_000dbd0c(), 0 };
          sk_h_00460d94(sv10.lo,sv10.hi,v8,v3);
          sv10 = (sk16_t){ sk_h_000dbd0c(), 0 };
          sk_h_00466580(sv10.lo,sv10.hi,v8,v3);
          sv10 = (sk16_t){ sk_h_000dbd0c(), 0 };
          sk_h_00458e80(sv10.lo,sv10.hi,v8,v3);
          v3 = SBORROW8(t9,1);
          t9 = t9 + -1;
          pv7 = pv7 + 0x20;
        } while (t9 != 0);
        sk_h_0036b118(t6);
      }
      if ((param_5 & 1) != 0) goto LAB_0041d380;
      sk_h_003523fc(6,*param_8);
      sk_f_0041d14c((word_t)0,(word_t)0,(word_t)0,(word_t)0);
      sk_h_00465d3c();
      t6 = out8_02;
      if ((bool )v3) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x41d338);
        (*pcVar2)();
      }
    }
  }
  *param_8 = t6;
LAB_0041d380:
  sk_h_00351d30(out8);
  return;
}

/* FUN_0041d3e8 @ 0x0041d3e8   (est. sk_f_0041d3e8)
 * Ghidra: void FUN_0041d3e8(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d3e8(void){
  code_t  *pcVar1;
  long  t2;
  long  *ctx;
  
  if (*(long  *)(*ctx + 0x10) == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code_t *)sk_trap(1,0x41d430);
    (*pcVar1)();
  }
  t2 = sk_h_004613d4();
  if (t2 != 0) {
    return;
  }
  sk_h_0046134c(*(long  *)(*ctx + 0x10) + -1);
  return;
}

/* FUN_0041d430 @ 0x0041d430   (est. sk_f_0041d430)
 * Ghidra: void FUN_0041d430(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d430(word_t param_1, word_t param_2, word_t param_3, word_t param_4){
  byte  l_88 [32];
  word_t  l_68;
  word_t  l_60;
  word_t  l_58;
  
  sk_h_00463998(param_1,param_1,param_2,param_3,param_4);
  l_60 = 0;
  l_68 = 0;
  l_58 = 0xe000000000000000;
  sk_h_00463600();
  sk_f_0041d4a4(l_88,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
  l_60 = 0;
  l_58 = 0xe000000000000000;
  sk_h_004590e0(l_88);
  sk_h_0009461c();
  return;
}

/* FUN_0041d4a4 @ 0x0041d4a4   (est. sk_f_0041d4a4)
 * Ghidra: void FUN_0041d4a4(long param_1,long param_2,long param_3,long param_4,char param_5)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d4a4(long param_1, long param_2, long param_3, long param_4, char param_5){
  code_t  *pcVar1;
  byte  v2;
  byte  v3;
  word_t  out8;
  word_t  out8_00;
  long  t4;
  word_t  v5;
  long  t6;
  long  t7;
  sk16_t sv8;
  long  l_68 [3];
  
  if (param_5 == '\0') {
    t6 = -0x16ffffffffffffc2;
    t4 = t6;
    if (param_3 != 0) {
      t4 = param_3;
    }
    if (param_4 == 0) {
      sk_h_00460d94(0x64656d616e6e753c /* "<unnamed" */,param_2,param_3,0);
    }
    else {
      l_68[1] = 0;
      l_68[2] = -0x2000000000000000;
      l_68[0] = param_4;
      sk_h_00460d94(param_2,param_3,param_4,0);
      sv8 = (sk16_t){ sk_h_00002534(), 0 };
      sk_h_00465db0(sv8.lo,sv8.hi,sv8.lo);
      sk_h_0046299c();
      sk_h_00205844(l_68,l_68 + 1);
      t6 = l_68[2];
    }
    sk_h_00465800(0x286d6f7441 /* "Atom(" */);
    sk_h_00100efc();
    sk_h_002acbb8();
    sk_h_003a25d4(t4);
    sk_h_002acbb8(0x203a,0xe200000000000000);
    sk_h_00350518();
    sk_h_002acbb8();
    sk_h_003a25d4(t6);
    sk_h_00100e34();
    sk_h_002acbb8();
    t4 = l_68[2];
    sk_h_0044ca60();
    sk_h_0036b270(t4);
    sk_h_000b4390();
    sk_h_002acbb8();
    sk_h_003a25d4(t4);
    sk_h_00463af8();
    sk_h_003a25d4(t4);
  }
  else {
    if (param_5 == '\x01') {
      v5 = *(word_t *)(param_2 + 0x20);
      v3 = *(byte  *)(param_2 + 0x28);
      sv8 = (sk16_t){ sk_h_000b4390(), 0 };
      sk_h_00460d94(sv8.lo,sv8.hi,v5,v3);
      sk_h_0044ca60();
      sk_h_002acbb8(0x6c616e6f6974704f /* "Optional" */,0xea00000000007b20);
      sk_h_00463af8();
      sk_h_004645ec();
      v2 = SCARRY8(*(long  *)(param_1 + 0x40),1);
      if ((bool )v2) {
                    /* WARNING: Does not return */
        pcVar1 = (code_t *)sk_trap(1,0x41d770);
        (*pcVar1)();
      }
      *(long  *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + 1;
      sk_h_0034c444(param_1);
      sk_f_0041d4a4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
      sv8 = (sk16_t){ sk_h_000b4390(), 0 };
      sk_h_00458e80(sv8.lo,sv8.hi,v5,v3);
      sk_h_00465d1c();
      v5 = out8;
      if ((bool )v2) {
                    /* WARNING: Does not return */
        pcVar1 = (code_t *)sk_trap(1,0x41d560);
        (*pcVar1)();
      }
    }
    else {
      t4 = *(long  *)(param_2 + 0x10);
      sk_h_0036b270(t4);
      sk_h_0044ca60();
      sk_h_002acbb8(0x7b20656c707554 /* "Tuple {" */,0xe700000000000000);
      sk_h_00463af8();
      sk_h_004645ec();
      if (SCARRY8(*(long  *)(param_1 + 0x40),1)) {
                    /* WARNING: Does not return */
        pcVar1 = (code_t *)sk_trap(1,0x41d774);
        (*pcVar1)();
      }
      *(long  *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + 1;
      t6 = *(long  *)(t4 + 0x10);
      v3 = false;
      if (t6 != 0) {
        t7 = t4 + 0x38;
        do {
          v5 = *(word_t *)(t7 + -0x18);
          t7 = t7 + 0x20;
          sk_h_003505c4(v5);
          sk_h_00460d94();
          sk_h_0009461c();
          sk_h_003511f0();
          sk_f_0041d4a4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
          sk_h_003505c4(v5);
          sk_h_00458e80();
          v3 = SBORROW8(t6,1);
          t6 = t6 + -1;
        } while (t6 != 0);
      }
      sk_h_0036b118(t4);
      sk_h_00465d1c();
      v5 = out8_00;
      if ((bool )v3) {
                    /* WARNING: Does not return */
        pcVar1 = (code_t *)sk_trap(1,0x41d778);
        (*pcVar1)();
      }
    }
    *(word_t *)(param_1 + 0x40) = v5;
    sk_h_0044ca60();
    sk_h_00463878();
    sk_h_002acbb8();
    sk_h_00463af8();
  }
  sk_h_004645ec();
  return;
}

/* FUN_0041d778 @ 0x0041d778   (est. sk_f_0041d778)
 * Ghidra: sk16_t FUN_0041d778(void)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041d778(void){
  sk16_t sv1;
  long  ctx;
  
  sv1 = *(byte  (*) [16])(ctx + 0x28);
  *(word_t *)(ctx + 0x28) = 0;
  *(word_t *)(ctx + 0x30) = 0xe000000000000000;
  return sv1;
}

/* FUN_0041d788 @ 0x0041d788   (est. sk_f_0041d788)
 * Ghidra: void FUN_0041d788(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d788(void){
  sk_h_003509ec();
  sk_h_0044ca60();
  sk_h_0036b270();
  sk_h_00100efc();
  sk_h_002acbb8();
  sk_h_003a25d4();
  sk_h_00463af8();
  sk_h_004645ec();
  return;
}

/* FUN_0041d7dc @ 0x0041d7dc   (est. sk_f_0041d7dc)
 * Ghidra: void FUN_0041d7dc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,                  undefined8 param_5,undefined8 param_6,code *param_7)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d7dc(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6, code_t* param_7){
  code_t  *pcVar1;
  byte  v2;
  word_t  out1;
  word_t  out8;
  word_t  out8_00;
  long  ctx;
  
  sk_h_00354744();
  sk_h_0036b270(out1);
  sk_h_00463fe8();
  sk_h_002acbb8();
  sk_h_002acbb8(param_3,param_4);
  sk_h_0044ca60();
  sk_h_0036b270(out1);
  sk_h_00350738();
  sk_h_002acbb8();
  sk_h_003a25d4(out1);
  sk_h_00463af8();
  sk_h_003a25d4(out1);
  sk_h_004645ec();
  v2 = SCARRY8(*(long  *)(ctx + 0x40),1);
  if ((bool )v2) {
                    /* WARNING: Does not return */
    pcVar1 = (code_t *)sk_trap(1,0x41d8e0);
    (*pcVar1)();
  }
  *(long  *)(ctx + 0x40) = *(long *)(ctx + 0x40) + 1;
  (*param_7)();
  sk_h_00465d1c();
  if (!(bool )v2) {
    *(word_t *)(ctx + 0x40) = out8_00;
    sk_h_0044ca60();
    sk_h_0036b270(param_6);
    sk_h_00100efc();
    sk_h_002acbb8();
    sk_h_003a25d4(param_6);
    sk_h_00463af8();
    sk_h_004645ec();
    sk_h_003544c8(out8);
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code_t *)sk_trap(1,0x41d8e4);
  (*pcVar1)();
}

/* FUN_0041d8f4 @ 0x0041d8f4   (est. sk_f_0041d8f4)
 * Ghidra: void FUN_0041d8f4(long param_1)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041d8f4(long param_1){
  word_t  v1;
  long  t2;
  long  t3;
  word_t  v4;
  code_t  *pcVar5;
  word_t  v6;
  long  t7;
  word_t  out8;
  long  out8_00;
  long  *pt8;
  long  t9;
  long  t10;
  long  t11;
  long  t12;
  long  l_b0;
  byte  l_a4;
  
  t9 = *(long  *)(param_1 + 0x10);
  if (t9 == 1) {
    sk_f_0041dae0();
  }
  else if (t9 == 0) {
    v6 = sk_h_00466440();
    t9 = sk_h_000a6f68(v6,0,0);
    *(word_t *)(t9 + 0x10) = out8;
  }
  else {
    sk_h_000a6f68();
    sk_h_004562f0(0,t9,0);
    t11 = 0;
    do {
      if (t11 == t9) {
                    /* WARNING: Does not return */
        pcVar5 = (code_t *)sk_trap(1,0x41dadc);
        (*pcVar5)();
      }
      pt8 = (long  *)(param_1 + 0x20 + t11 * 0x38);
      t2 = pt8[3];
      t12 = 0;
      if (pt8[2] != 0x675c68 /* "h\g" */) {
        t12 = pt8[2];
      }
      if (t2 < 0) {
                    /* WARNING: Does not return */
        pcVar5 = (code_t *)sk_trap(1,0x41dae0);
        (*pcVar5)();
      }
      t10 = *pt8;
      t3 = pt8[1];
      if (t2 == 0) {
        l_a4 = 0;
        l_b0 = t3;
      }
      else {
        sk_h_00465ce8(0x685d58 /* "X]h" */);
        t7 = sk_h_0036a940();
        *(long  *)(t7 + 0x10) = t10;
        *(long  *)(t7 + 0x18) = t3;
        *(long  *)(t7 + 0x20) = t12;
        *(byte  *)(t7 + 0x28) = 0;
        t10 = t7;
        while (t2 = t2 + -1, t2 != 0) {
          sk_h_00465ce8(0x685d58 /* "X]h" */);
          t12 = sk_h_0036a940();
          *(word_t *)(t12 + 0x18) = 0;
          *(word_t *)(t12 + 0x20) = 0;
          *(long  *)(t12 + 0x10) = t10;
          *(byte  *)(t12 + 0x28) = 1;
          t10 = t12;
        }
        l_b0 = 0;
        t12 = 0;
        l_a4 = 1;
      }
      v1 = *(word_t *)(out8_00 + 0x10);
      v4 = *(word_t *)(out8_00 + 0x18);
      sk_h_0036b270(t3);
      if (v4 >> 1 <= v1) {
        sk_h_000dbed0(1 < v4);
        sk_h_004562f0();
      }
      t11 = t11 + 1;
      *(word_t *)(out8_00 + 0x10) = v1 + 1;
      t2 = out8_00 + v1 * 0x20;
      *(long  *)(t2 + 0x20) = t10;
      *(long  *)(t2 + 0x28) = l_b0;
      *(long  *)(t2 + 0x30) = t12;
      *(byte  *)(t2 + 0x38) = l_a4;
    } while (t11 != t9);
    t9 = sk_h_00466440();
    *(long  *)(t9 + 0x10) = out8_00;
  }
  return;
}

/* FUN_0041dae0 @ 0x0041dae0   (est. sk_f_0041dae0)
 * Ghidra: void FUN_0041dae0(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041dae0(void){
  long  t1;
  code_t  *pcVar2;
  long  t3;
  long  *ctx;
  byte  v4;
  long  t5;
  long  t6;
  long  t7;
  
  t5 = ctx[3];
  if (-1 < t5) {
    t6 = ctx[1];
    t7 = 0;
    if (ctx[2] != 0x675c68 /* "h\g" */) {
      t7 = ctx[2];
    }
    v4 = 0;
    t1 = *ctx;
    for (; t5 != 0; t5 = t5 + -1) {
      sk_h_00465ce8(0x685d58 /* "X]h" */);
      t3 = sk_h_0036a940();
      *(byte  *)(t3 + 0x28) = v4;
      v4 = 1;
      *(long  *)(t3 + 0x10) = t1;
      *(long  *)(t3 + 0x18) = t6;
      *(long  *)(t3 + 0x20) = t7;
      t6 = 0;
      t7 = 0;
      t1 = t3;
    }
    sk_h_00464e28();
    sk_h_00458da0();
    sk_h_00084180();
    return;
  }
                    /* WARNING: Does not return */
  pcVar2 = (code_t *)sk_trap(1,0x41dbb4);
  (*pcVar2)();
}

/* FUN_0041dbb4 @ 0x0041dbb4   (est. sk_f_0041dbb4)
 * Ghidra: char FUN_0041dbb4(void)
 * 
 * Confidence: medium
 * Notes:  */
char sk_f_0041dbb4(){
  code_t  *pcVar1;
  byte  in_flags;
  word_t  v2;
  long  out1;
  long  r21;
  long  r22;
  long  unaff_x24;
  sk16_t sv3;
  char  l_70 [32];
  word_t  l_50;
  word_t  l_48;
  
  sk_h_00463418();
  sk_h_00464ef8();
  while( true ) {
    sk_h_0029fb80();
    if (out1 == 0) {
      sk_h_003a25d4();
      sk_h_0029d3d8(l_50,l_48);
      sk_h_00351e08();
      sk_h_003a25d4(l_48);
      sk_h_0007c1c4(l_70);
      sk_f_0041e28c();
      if (l_70[0] == '&') {
        sk_h_00464180();
        sk_h_0035053c();
        v2 = sk_h_002abcb0();
        if ((v2 & 1) == 0) {
          sk_h_003a25d4();
          l_70[0] = '&';
        }
        else {
          sk_h_00350624(2);
          sk_h_000b4660();
          sk_h_002a3e64();
          sk_h_0034bd90();
          sk_h_003a25d4();
          sk_h_0006b6f4(l_70);
          sk_f_0041e28c();
          sk_h_003a25d4(0x26);
        }
      }
      else {
        sk_h_003a25d4();
      }
      return l_70[0];
    }
    sk_h_0035aba4();
    sk_h_001ae8a8();
    sk_h_00464eec();
    if ((bool )in_flags) break;
    v2 = sk_h_002bc2dc();
    if (((v2 & 1) == 0) &&
       (in_flags = r22 == 0x5f && r21 == unaff_x24,
       r22 != 0x5f || r21 != unaff_x24)) {
      sk_h_00100efc();
      sk_h_00462fac();
      v2 = sk_h_002a0cf8();
      in_flags = r22 == 0x2d && r21 == unaff_x24;
      if (((v2 & 1) == 0) && (r22 != 0x2d || r21 != unaff_x24)) {
        sv3 = (sk16_t){ sk_h_00100efc(), 0 };
        sk_h_00463540(sv3.lo,sv3.hi,0x2d);
        v2 = sk_h_002a0cf8();
        if ((v2 & 1) == 0) {
          sk_h_00100efc();
          sk_h_002acbb8();
        }
      }
    }
    sk_h_003a25d4();
  }
                    /* WARNING: Does not return */
  pcVar1 = (code_t *)sk_trap(1,0x41dd0c);
  (*pcVar1)();
}

/* FUN_0041dd0c @ 0x0041dd0c   (est. sk_f_0041dd0c)
 * Ghidra: char FUN_0041dd0c(void)
 * 
 * Confidence: medium
 * Notes:  */
char sk_f_0041dd0c(){
  code_t  *pcVar1;
  byte  in_flags;
  word_t  v2;
  long  out1;
  long  r21;
  long  r22;
  long  unaff_x24;
  sk16_t sv3;
  char  l_70 [32];
  word_t  l_50;
  word_t  l_48;
  
  sk_h_00463418();
  sk_h_00464ef8();
  while( true ) {
    sk_h_0029fb80();
    if (out1 == 0) {
      sk_h_003a25d4();
      sk_h_0029d3d8(l_50,l_48);
      sk_h_00351e08();
      sk_h_003a25d4(l_48);
      sk_h_0007c1c4(l_70);
      sk_f_0041f074();
      if (l_70[0] == 'C') {
        sk_h_00464180();
        sk_h_0035053c();
        v2 = sk_h_002abcb0();
        if ((v2 & 1) == 0) {
          sk_h_003a25d4();
          l_70[0] = 'C';
        }
        else {
          sk_h_00350624(2);
          sk_h_000b4660();
          sk_h_002a3e64();
          sk_h_0034bd90();
          sk_h_003a25d4();
          sk_h_0006b6f4(l_70);
          sk_f_0041f074();
          sk_h_003a25d4(0x43);
        }
      }
      else {
        sk_h_003a25d4();
      }
      return l_70[0];
    }
    sk_h_0035aba4();
    sk_h_001ae8a8();
    sk_h_00464eec();
    if ((bool )in_flags) break;
    v2 = sk_h_002bc2dc();
    if (((v2 & 1) == 0) &&
       (in_flags = r22 == 0x5f && r21 == unaff_x24,
       r22 != 0x5f || r21 != unaff_x24)) {
      sk_h_00100efc();
      sk_h_00462fac();
      v2 = sk_h_002a0cf8();
      in_flags = r22 == 0x2d && r21 == unaff_x24;
      if (((v2 & 1) == 0) && (r22 != 0x2d || r21 != unaff_x24)) {
        sv3 = (sk16_t){ sk_h_00100efc(), 0 };
        sk_h_00463540(sv3.lo,sv3.hi,0x2d);
        v2 = sk_h_002a0cf8();
        if ((v2 & 1) == 0) {
          sk_h_00100efc();
          sk_h_002acbb8();
        }
      }
    }
    sk_h_003a25d4();
  }
                    /* WARNING: Does not return */
  pcVar1 = (code_t *)sk_trap(1,0x41de64);
  (*pcVar1)();
}

/* FUN_0041de64 @ 0x0041de64   (est. sk_f_0041de64)
 * Ghidra: char FUN_0041de64(void)
 * 
 * Confidence: medium
 * Notes:  */
char sk_f_0041de64(){
  code_t  *pcVar1;
  byte  in_flags;
  word_t  v2;
  long  out1;
  long  r21;
  long  r22;
  long  unaff_x24;
  sk16_t sv3;
  char  l_70 [32];
  word_t  l_50;
  word_t  l_48;
  
  sk_h_00463418();
  sk_h_00464ef8();
  while( true ) {
    sk_h_0029fb80();
    if (out1 == 0) {
      sk_h_003a25d4();
      sk_h_0029d3d8(l_50,l_48);
      sk_h_00351e08();
      sk_h_003a25d4(l_48);
      sk_h_0007c1c4(l_70);
      sk_f_004207b0();
      if (l_70[0] == -0x54) {
        sk_h_00464180();
        sk_h_0035053c();
        v2 = sk_h_002abcb0();
        if ((v2 & 1) == 0) {
          sk_h_003a25d4();
          l_70[0] = -0x54;
        }
        else {
          sk_h_00350624(2);
          sk_h_000b4660();
          sk_h_002a3e64();
          sk_h_0034bd90();
          sk_h_003a25d4();
          sk_h_0006b6f4(l_70);
          sk_f_004207b0();
          sk_h_003a25d4(0xac);
        }
      }
      else {
        sk_h_003a25d4();
      }
      return l_70[0];
    }
    sk_h_0035aba4();
    sk_h_001ae8a8();
    sk_h_00464eec();
    if ((bool )in_flags) break;
    v2 = sk_h_002bc2dc();
    if (((v2 & 1) == 0) &&
       (in_flags = r22 == 0x5f && r21 == unaff_x24,
       r22 != 0x5f || r21 != unaff_x24)) {
      sk_h_00100efc();
      sk_h_00462fac();
      v2 = sk_h_002a0cf8();
      in_flags = r22 == 0x2d && r21 == unaff_x24;
      if (((v2 & 1) == 0) && (r22 != 0x2d || r21 != unaff_x24)) {
        sv3 = (sk16_t){ sk_h_00100efc(), 0 };
        sk_h_00463540(sv3.lo,sv3.hi,0x2d);
        v2 = sk_h_002a0cf8();
        if ((v2 & 1) == 0) {
          sk_h_00100efc();
          sk_h_002acbb8();
        }
      }
    }
    sk_h_003a25d4();
  }
                    /* WARNING: Does not return */
  pcVar1 = (code_t *)sk_trap(1,0x41dfbc);
  (*pcVar1)();
}

/* FUN_0041dfbc @ 0x0041dfbc   (est. sk_f_0041dfbc)
 * Ghidra: void FUN_0041dfbc(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041dfbc(void){
  code_t  *pcVar1;
  byte  in_flags;
  
  sk_h_001ae8a8();
  sk_h_0034ecc8();
  if (!(bool )in_flags) {
    sk_h_002bc2dc();
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code_t *)sk_trap(1,0x41dfe4);
  (*pcVar1)();
}

/* FUN_0041dfc0 @ 0x0041dfc0   (est. sk_f_0041dfc0)
 * Ghidra: void FUN_0041dfc0(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041dfc0(void){
  code_t  *pcVar1;
  byte  in_flags;
  
  sk_h_001ae8a8();
  sk_h_0034ecc8();
  if (!(bool )in_flags) {
    sk_h_002bc2dc();
    return;
  }
                    /* WARNING: Does not return */
  pcVar1 = (code_t *)sk_trap(1,0x41dfe4);
  (*pcVar1)();
}

/* FUN_0041dfe4 @ 0x0041dfe4   (est. sk_f_0041dfe4)
 * Ghidra: sk16_t FUN_0041dfe4(long param_1,undefined8 param_2,ulong param_3,undefined8 param_4,undefined8 param_5)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041dfe4(long param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5){
  word_t  v1;
  code_t  *pcVar2;
  sk16_t sv3;
  sk12_t sv4;
  
  if (param_1 < 0) {
                    /* WARNING: Does not return */
    pcVar2 = (code_t *)sk_trap(1,0x41e09c);
    (*pcVar2)();
  }
  sv4 = (sk16_t){ sk_h_002b3f40(), 0 };
  v1 = param_3;
  if ((sv4.w2 & 0xff) != 1) {
    v1 = sv4.lo;
  }
  if (v1 >> 0xe <= param_3 >> 0xe) {
    sv3 = (sk16_t){ sk_h_002b74c0(), 0 };
    sk_h_003a25d4(param_5);
    return sv3;
  }
                    /* WARNING: Does not return */
  pcVar2 = (code_t *)sk_trap(1,0x41e0a0);
  (*pcVar2)();
}

/* FUN_0041e0a0 @ 0x0041e0a0   (est. sk_f_0041e0a0)
 * Ghidra: void FUN_0041e0a0(ulong param_1,ulong param_2,ulong param_3)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041e0a0(word_t param_1, word_t param_2, word_t param_3){
  word_t  v1;
  word_t  v2;
  code_t  *pcVar3;
  word_t  v4;
  uint  v5;
  sk12_t sv6;
  
  if ((long )param_1 < 0) {
                    /* WARNING: Does not return */
    pcVar3 = (code_t *)sk_trap(1,0x41e150);
    (*pcVar3)();
  }
  v1 = param_2 & 0xffffffffffff;
  if ((param_3 & 0x2000000000000000) != 0) {
    v1 = param_3 >> 0x38 & 0xf;
  }
  v4 = v1 << 0x10 | 7;
  if ((param_3 >> 0x3c & 1) == 0) {
    if (param_1 <= v1) {
      v4 = param_1 << 0x10 | 4;
    }
  }
  else {
    if ((param_2 & 0x800000000000000) == 0) {
      v4 = v1 << 0x10 | 0xb;
    }
    sv6 = (sk16_t){ sk_h_001b28d4(), 0 };
    if ((sv6.w2 & 0xff) != 1) {
      v4 = sv6.lo;
    }
  }
  if (v1 << 2 < v4 >> 0xe) {
                    /* WARNING: Does not return */
    pcVar3 = (code_t *)sk_trap(1,0x41e188);
    (*pcVar3)();
  }
  v5 = (uint )(param_2 >> 0x3b) & 1;
  if ((param_3 & 0x1000000000000000) == 0) {
    v5 = 1;
  }
  v2 = 7;
  if (v5 == 0) {
    v2 = 0xb;
  }
  sk_h_00460e78(v4,v1 << 0x10 | v2,param_2,param_3);
  return;
}

/* FUN_0041e188 @ 0x0041e188   (est. sk_f_0041e188)
 * Ghidra: void FUN_0041e188(long param_1,undefined8 param_2,ulong param_3,undefined8 param_4,                  undefined8 param_5)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041e188(long param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5){
  word_t  v1;
  code_t  *pcVar2;
  sk12_t sv3;
  
  if (param_1 < 0) {
                    /* WARNING: Does not return */
    pcVar2 = (code_t *)sk_trap(1,0x41e218);
    (*pcVar2)();
  }
  sv3 = (sk16_t){ sk_h_002b5e10(), 0 };
  v1 = param_3;
  if ((sv3.w2 & 0xff) != 1) {
    v1 = sv3.lo;
  }
  if (v1 >> 0xe <= param_3 >> 0xe) {
    sk_h_002ab388(v1,param_3,param_2,param_3,param_4,param_5);
    return;
  }
                    /* WARNING: Does not return */
  pcVar2 = (code_t *)sk_trap(1,0x41e21c);
  (*pcVar2)();
}

/* FUN_0041e21c @ 0x0041e21c   (est. sk_f_0041e21c)
 * Ghidra: sk16_t FUN_0041e21c(long param_1,long param_2)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_0041e21c(long param_1, long param_2){
  long  t1;
  code_t  *pcVar2;
  long  t3;
  sk16_t sv4;
  sk12_t sv5;
  
  if (param_1 < 0) {
                    /* WARNING: Does not return */
    pcVar2 = (code_t *)sk_trap(1,0x41e284);
    (*pcVar2)();
  }
  t3 = *(long  *)(param_2 + 0x10);
  sv5 = (sk16_t){ sk_h_003f8224(), 0 };
  t1 = t3;
  if ((sv5.w2 & 0xff) != 1) {
    t1 = sv5.lo;
  }
  if (t1 <= t3) {
    if (-1 < t1) {
      sv4.hi = param_2 + 0x20;
      sv4.lo = param_2;
      return sv4;
    }
                    /* WARNING: Does not return */
    pcVar2 = (code_t *)sk_trap(1,0x41e28c);
    (*pcVar2)();
  }
                    /* WARNING: Does not return */
  pcVar2 = (code_t *)sk_trap(1,0x41e288);
  (*pcVar2)();
}

/* FUN_0041e28c @ 0x0041e28c   (est. sk_f_0041e28c)
 * Ghidra: void FUN_0041e28c(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041e28c(void){
  byte  v1;
  byte  b2;
  bool  b3;
  bool  b4;
  word_t  v5;
  long  out1;
  long  out1_00;
  long  out1_01;
  long  out1_02;
  long  out1_03;
  long  out1_04;
  byte  v6;
  byte  *out8;
  long  out8_00;
  long  out8_01;
  long  out8_02;
  long  ctx;
  word_t  r21;
  word_t  r30;
  sk16_t sv7;
  sk16_t sv8;
  
  sv8.hi = ctx;
  sv8.lo = r21;
  sv7 = (sk16_t){ sk_h_0008e518(), 0 };
  b3 = sv7.lo == 99;
  b4 = sv7.hi == -0x1f00000000000000;
  v1 = b3 && b4;
  if (!b3 || !b4) {
    sk_h_0035098c();
    v5 = sk_h_00463240(99);
    if ((v5 & 1) == 0) {
      sk_h_0046493c();
      sk_h_004657dc();
      if ((!(bool )v1 || ctx != -0x1b00000000000000) &&
         (v5 = sk_h_00462dd0(), (v5 & 1) == 0)) {
        if ((r21 != 0x6363 || ctx != -0x1e00000000000000) &&
           ((v5 = sk_h_00462e1c(0x6363), (v5 & 1) == 0 &&
            (v1 = r21 == 0x6c6f72746e6f63 /* "control" */ && ctx == -0x1900000000000000,
            r21 != 0x6c6f72746e6f63 /* "control" */ || ctx != -0x1900000000000000)))) {
          sk_h_00462da8();
          v5 = sk_h_00464930();
          v6 = 1;
          if (((v5 & 1) != 0) || ((bool )v1 && ctx == out8_00)) goto LAB_0041e2e8;
          v5 = sk_h_00462dd0(0x6c72746e63 /* "cntrl" */);
          if ((v5 & 1) == 0) {
            if ((((r21 == 0x6663 && ctx == -0x1e00000000000000) ||
                 (v5 = sk_h_00462e1c(0x6663), (v5 & 1) != 0)) ||
                (r21 == 0x74616d726f66 /* "format" */ && ctx == -0x1a00000000000000)) ||
               (v5 = sk_h_00462dbc(), (v5 & 1) != 0)) {
              v6 = 2;
            }
            else if (((r21 == 0x6e63 && ctx == -0x1e00000000000000) ||
                     (v5 = sk_h_00462e1c(0x6e63), (v5 & 1) != 0)) ||
                    ((r21 == 0x6e67697373616e75 /* "unassign" */ && ctx == -0x15ffffffffff9b9b ||
                     (v5 = sk_h_0046311c(0x6e67697373616e75 /* "unassign" */,0x6465), (v5 & 1) != 0)))) {
              v6 = 3;
            }
            else if (((r21 == 0x6f63 && ctx == -0x1e00000000000000) ||
                     (v5 = sk_h_00462e1c(0x6f63), (v5 & 1) != 0)) ||
                    ((r21 == 0x7565746176697270 /* "privateu" */ && ctx == -0x15ffffffffff9a8d ||
                     (v5 = sk_h_004633f4(), (v5 & 1) != 0)))) {
              v6 = 4;
            }
            else if ((((r21 == 0x7363 && ctx == -0x1e00000000000000) ||
                      (v5 = sk_h_00462e1c(0x7363), (v5 & 1) != 0)) ||
                     (r21 == 0x7461676f72727573 /* "surrogat" */ && ctx == -0x16ffffffffffff9b)) ||
                    (v5 = sk_h_00463254(0x7461676f72727573 /* "surrogat" */,0x65), (v5 & 1) != 0)) {
              v6 = 5;
            }
            else {
              v1 = r21 == 0x6c && ctx == -0x1f00000000000000;
              if (r21 != 0x6c || ctx != -0x1f00000000000000) {
                sk_h_00463240(0x6c);
                v5 = sk_h_00463ac8();
                v6 = 6;
                if (((v5 & 1) != 0) || ((bool )v1 && ctx == out8_01))
                goto LAB_0041e2e8;
                v5 = sk_h_00462d70();
                if ((v5 & 1) == 0) {
                  if (r21 != 0x636c || ctx != -0x1e00000000000000) {
                    v5 = sk_h_00462e1c(0x636c);
                    v6 = 7;
                    if (((v5 & 1) != 0) ||
                       (r21 == 0x266c && ctx == -0x1e00000000000000)) goto LAB_0041e2e8;
                    v5 = sk_h_00462e1c(0x266c);
                    if (((v5 & 1) == 0) &&
                       ((r21 != 0x74656c6465736163 /* "casedlet" */ || ctx != -0x14ffffffff8d9a8c &&
                        (v5 = sk_h_004633f4(0x74656c6465736163 /* "casedlet" */,0xeb00000000726574),
                        (v5 & 1) == 0)))) {
                      v1 = r21 == 0x6c6c && ctx == -0x1e00000000000000;
                      if ((r21 == 0x6c6c && ctx == -0x1e00000000000000) ||
                         (((v5 = sk_h_00462e1c(0x6c6c), (v5 & 1) != 0 ||
                           (sk_h_00465590(), (bool )v1 && ctx == -0x108d9a8b8b9a939b)) ||
                          (v5 = sk_h_00463180(), (v5 & 1) != 0)))) {
                        v6 = 8;
                      }
                      else if (((r21 == 0x6d6c && ctx == -0x1e00000000000000) ||
                               (v5 = sk_h_00462e1c(0x6d6c), (v5 & 1) != 0)) ||
                              ((r21 == 0x7265696669646f6d /* "modifier" */ && ctx == -0x11ff8d9a8b8b9a94
                               || (v5 = sk_h_004633b8(), (v5 & 1) != 0)))) {
                        v6 = 9;
                      }
                      else {
                        if (r21 != 0x6f6c || ctx != -0x1e00000000000000) {
                          v5 = sk_h_00462e1c(0x6f6c);
                          v6 = 10;
                          if (((v5 & 1) != 0) ||
                             (r21 == 0x74656c726568746f /* "otherlet" */ && ctx == -0x14ffffffff8d9a8c))
                          goto LAB_0041e2e8;
                          sk_h_00351274();
                          v5 = sk_h_004633f4();
                          if ((v5 & 1) == 0) {
                            b2 = r21 == 0x746c && ctx == -0x1e00000000000000;
                            if (r21 != 0x746c || ctx != -0x1e00000000000000) {
                              sk_h_00462e1c(0x746c);
                              v5 = sk_h_004663d4();
                              v6 = 0xb;
                              if (((v5 & 1) != 0) || ((b2 & 1) != 0)) goto LAB_0041e2e8;
                              v5 = sk_h_00463180(0x736163656c746974 /* "titlecas" */);
                              if ((v5 & 1) == 0) {
                                b2 = r21 == 0x756c && ctx == -0x1e00000000000000;
                                if (r21 != 0x756c || ctx != -0x1e00000000000000) {
                                  sk_h_00462e1c(0x756c);
                                  v5 = sk_h_004663d4();
                                  v6 = 0xc;
                                  if (((v5 & 1) != 0) || ((b2 & 1) != 0)) goto LAB_0041e2e8;
                                  v5 = sk_h_00463180(0x7361637265707075 /* "uppercas" */);
                                  if ((v5 & 1) == 0) {
                                    if ((((r21 == 0x6d && ctx == -0x1f00000000000000) ||
                                         (v5 = sk_h_00463240(0x6d), (v5 & 1) != 0)) ||
                                        (r21 == 0x6b72616d /* "mark" */ && ctx == -0x1c00000000000000
                                        )) || (((v5 = sk_h_00462cc0(0x6b72616d /* "mark" */), (v5 & 1) != 0
                                                || (r21 == 0x6e696e69626d6f63 /* "combinin" */ &&
                                                    ctx == -0x12ffff948d9e9299)) ||
                                               (v5 = sk_h_00463180(), (v5 & 1) != 0)))) {
                                      v6 = 0xd;
                                    }
                                    else if (((r21 == 0x636d &&
                                               ctx == -0x1e00000000000000) ||
                                             (v5 = sk_h_00462e1c(0x636d), (v5 & 1) != 0)) ||
                                            ((r21 == 0x6d676e6963617073 /* "spacingm" */ &&
                                              ctx == -0x14ffffffff948d9f ||
                                             (v5 = sk_h_004633f4(), (v5 & 1) != 0)))) {
                                      v6 = 0xe;
                                    }
                                    else {
                                      b2 = r21 == 0x656d &&
                                              ctx == -0x1e00000000000000;
                                      if (r21 != 0x656d || ctx != -0x1e00000000000000) {
                                        sk_h_00462e1c(0x656d);
                                        v5 = sk_h_004663d4();
                                        v6 = 0xf;
                                        if (((v5 & 1) != 0) || ((b2 & 1) != 0))
                                        goto LAB_0041e2e8;
                                        v5 = sk_h_00463180(0x6e69736f6c636e65 /* "enclosin" */);
                                        if ((v5 & 1) == 0) {
                                          if ((((r21 == 0x6e6d &&
                                                 ctx == -0x1e00000000000000) ||
                                               (v5 = sk_h_00462e1c(0x6e6d), (v5 & 1) != 0)) ||
                                              (r21 == 0x69636170736e6f6e /* "nonspaci" */ &&
                                               ctx == -0x11ff948d9e929892)) ||
                                             (v5 = sk_h_004633f4(), (v5 & 1) != 0)) {
                                            v6 = 0x10;
                                            goto LAB_0041e2e8;
                                          }
                                          if (r21 != 0x6e || ctx != -0x1f00000000000000)
                                          {
                                            v5 = sk_h_00463240(0x6e);
                                            v6 = 0x11;
                                            if (((v5 & 1) != 0) ||
                                               (r21 == 0x7265626d756e /* "number" */ &&
                                                ctx == -0x1a00000000000000))
                                            goto LAB_0041e2e8;
                                            v5 = sk_h_00462dbc(0x7265626d756e /* "number" */);
                                            if ((v5 & 1) == 0) {
                                              if (((r21 != 0x646e ||
                                                    ctx != -0x1e00000000000000) &&
                                                  (v5 = sk_h_00462e1c(0x646e), (v5 & 1) == 0))
                                                 && (r21 != 0x6e6c616d69636564 /* "decimaln" */ ||
                                                     ctx != -0x12ffff8d9a9d928b)) {
                                                v5 = sk_h_004633f4();
                                                v6 = 0x12;
                                                if (((v5 & 1) != 0) ||
                                                   (r21 == 0x7469676964 /* "digit" */ &&
                                                    ctx == -0x1b00000000000000))
                                                goto LAB_0041e2e8;
                                                v5 = sk_h_00462dd0(0x7469676964 /* "digit" */);
                                                if ((v5 & 1) == 0) {
                                                  if ((((r21 == 0x6c6e &&
                                                         ctx == -0x1e00000000000000) ||
                                                       (v5 = sk_h_00462e1c(0x6c6e),
                                                       (v5 & 1) != 0)) ||
                                                      (r21 == 0x756e72657474656c /* "letternu" */ &&
                                                       ctx == -0x13ffffff8d9a9d93)) ||
                                                     (v5 = sk_h_004633f4(), (v5 & 1) != 0)) {
                                                    v6 = 0x13;
                                                  }
                                                  else if (((r21 == 0x6f6e &&
                                                             ctx == -0x1e00000000000000) ||
                                                           (v5 = sk_h_00462e1c(0x6f6e),
                                                           (v5 & 1) != 0)) ||
                                                          ((v5 = sk_h_0046493c(),
                                                           r21 ==
                                                           (v5 & 0xffffffff | 0x6d756e7200000000)
                                                           && ctx == -0x14ffffffff8d9a9e ||
                                                           (v5 = sk_h_004633f4(), (v5 & 1) != 0
                                                           )))) {
                                                    v6 = 0x14;
                                                  }
                                                  else {
                                                    if ((r21 != 0x70 ||
                                                         ctx != -0x1f00000000000000) &&
                                                       (v5 = sk_h_00463240(0x70), (v5 & 1) == 0
                                                       )) {
                                                      sv7 = (sk16_t){ sk_h_00466328(), 0 };
                                                      v1 = sv7 == sv8;
                                                      if (sv7 != sv8) {
                                                        sk_h_004633f4();
                                                        v5 = sk_h_00463f58();
                                                        v6 = 0x15;
                                                        if (((v5 & 1) != 0) ||
                                                           ((bool )v1 &&
                                                            ctx == out8_02))
                                                        goto LAB_0041e2e8;
                                                        v5 = sk_h_00462dd0(0x74636e7570 /* "punct" */);
                                                        if ((v5 & 1) == 0) {
                                                          if ((((r21 == 0x6370 &&
                                                                 ctx == -0x1e00000000000000)
                                                               || (v5 = sk_h_00462e1c(0x6370),
                                                                  (v5 & 1) != 0)) ||
                                                              (sk_h_004643cc(
                                                  0),
                                                  r21 == 0xd000000000000014 &&
                                                  out1 == ctx)) ||
                                                  (v5 = sk_h_004633f4(0xd000000000000014),
                                                  (v5 & 1) != 0)) {
                                                    v6 = 0x16;
                                                  }
                                                  else if (((r21 == 0x6470 &&
                                                             ctx == -0x1e00000000000000) ||
                                                           (v5 = sk_h_00462e1c(0x6470),
                                                           (v5 & 1) != 0)) ||
                                                          ((r21 == 0x636e757068736164 /* "dashpunc" */ &&
                                                            ctx == -0x109190968b9e8a8c ||
                                                           (v5 = sk_h_00463180(), (v5 & 1) != 0
                                                           )))) {
                                                    v6 = 0x17;
                                                  }
                                                  else {
                                                    v1 = r21 == 0x6570 &&
                                                            ctx == -0x1e00000000000000;
                                                    if (((r21 == 0x6570 &&
                                                          ctx == -0x1e00000000000000) ||
                                                        (v5 = sk_h_00462e1c(0x6570),
                                                        (v5 & 1) != 0)) ||
                                                       ((sk_h_00462c48(0),
                                                        (bool )v1 && out1_00 == ctx
                                                        || (v5 = sk_h_00462bc0(), (v5 & 1) != 0
                                                           )))) {
                                                      v6 = 0x18;
                                                    }
                                                    else {
                                                      v1 = r21 == 0x6670 &&
                                                              ctx == -0x1e00000000000000;
                                                      if ((((r21 == 0x6670 &&
                                                             ctx == -0x1e00000000000000) ||
                                                           (v5 = sk_h_00462e1c(0x6670),
                                                           (v5 & 1) != 0)) ||
                                                          (sk_h_00462c48(0)
                                                          , (bool )v1 &&
                                                            out1_01 == ctx)) ||
                                                         (v5 = sk_h_00462bc0(), (v5 & 1) != 0))
                                                      {
                                                        v6 = 0x19;
                                                      }
                                                      else if (((r21 == 0x6970 &&
                                                                 ctx == -0x1e00000000000000)
                                                               || (v5 = sk_h_00462e1c(0x6970),
                                                                  (v5 & 1) != 0)) ||
                                                              ((sk_h_004643cc(
                                                  0),
                                                  r21 == 0xd000000000000012 &&
                                                  out1_02 == ctx ||
                                                  (v5 = sk_h_00462df8(), (v5 & 1) != 0)))) {
                                                    v6 = 0x1a;
                                                  }
                                                  else {
                                                    v1 = r21 == 0x6f70 &&
                                                            ctx == -0x1e00000000000000;
                                                    if (((r21 == 0x6f70 &&
                                                          ctx == -0x1e00000000000000) ||
                                                        (v5 = sk_h_00462e1c(0x6f70),
                                                        (v5 & 1) != 0)) ||
                                                       ((sk_h_00462c48(0),
                                                        (bool )v1 && out1_03 == ctx
                                                        || (v5 = sk_h_00462bc0(), (v5 & 1) != 0
                                                           )))) {
                                                      v6 = 0x1b;
                                                    }
                                                    else {
                                                      b2 = r21 == 0x7370 &&
                                                              ctx == -0x1e00000000000000;
                                                      if (r21 != 0x7370 ||
                                                          ctx != -0x1e00000000000000) {
                                                        sk_h_00462e1c(0x7370);
                                                        v5 = sk_h_004663d4();
                                                        v6 = 0x1c;
                                                        if (((v5 & 1) != 0) || ((b2 & 1) != 0)
                                                           ) goto LAB_0041e2e8;
                                                        v5 = sk_h_00463180(0x636e75706e65706f /* "openpunc" */);
                                                        if ((v5 & 1) == 0) {
                                                          if (r21 != 0x73 ||
                                                              ctx != -0x1f00000000000000) {
                                                            v5 = sk_h_00463240(0x73);
                                                            v6 = 0x1d;
                                                            if (((v5 & 1) != 0) ||
                                                               (r21 == 0x6c6f626d7973 /* "symbol" */ &&
                                                                ctx == -0x1a00000000000000))
                                                            goto LAB_0041e2e8;
                                                            v5 = sk_h_00462dbc(0x6c6f626d7973 /* "symbol" */);
                                                            if ((v5 & 1) == 0) {
                                                              v1 = r21 == 0x6373 &&
                                                                      ctx ==
                                                                      -0x1e00000000000000;
                                                              if ((((r21 == 0x6373 &&
                                                                     ctx ==
                                                                     -0x1e00000000000000) ||
                                                                   (v5 = sk_h_00462e1c(0x6373),
                                                                   (v5 & 1) != 0)) ||
                                                                  (sk_h_004658e4(),
                                                                  (bool )v1 &&
                                                                  ctx == -0x11ff93909d92868d))
                                                                 || (v5 = sk_h_00463180(),
                                                                    (v5 & 1) != 0)) {
                                                                v6 = 0x1e;
                                                                goto LAB_0041e2e8;
                                                              }
                                                              if (r21 != 0x6b73 ||
                                                                  ctx != -0x1e00000000000000)
                                                              {
                                                                v5 = sk_h_00462e1c(0x6b73);
                                                                v6 = 0x1f;
                                                                if (((v5 & 1) != 0) ||
                                                                   (r21 == 0x7265696669646f6d /* "modifier" */
                                                                    && ctx ==
                                                                       -0x11ff93909d92868d))
                                                                goto LAB_0041e2e8;
                                                                v5 = sk_h_00463180(
                                                  0x7265696669646f6d /* "modifier" */);
                                                  if ((v5 & 1) == 0) {
                                                    if (((r21 == 0x6d73 &&
                                                          ctx == -0x1e00000000000000) ||
                                                        (v5 = sk_h_00462e1c(0x6d73),
                                                        (v5 & 1) != 0)) ||
                                                       ((r21 == 0x626d79736874616d /* "mathsymb" */ &&
                                                         ctx == -0x15ffffffffff9391 ||
                                                        (v5 = sk_h_004633f4(), (v5 & 1) != 0)))
                                                       ) {
                                                      v6 = 0x20;
                                                    }
                                                    else if ((((r21 == 0x6f73 &&
                                                                ctx == -0x1e00000000000000) ||
                                                              (v5 = sk_h_00462e1c(0x6f73),
                                                              (v5 & 1) != 0)) ||
                                                             (sv8 = sk_h_0046493c(v5,
                                                  0xeb000000006c6f62),
                                                  r21 ==
                                                  (sv8.lo & 0xffffffff | 0x6d79737200000000)
                                                  && ctx == sv8.hi)) ||
                                                  (v5 = sk_h_004633f4(), (v5 & 1) != 0)) {
                                                    v6 = 0x21;
                                                  }
                                                  else if (((r21 == 0x7a &&
                                                             ctx == -0x1f00000000000000) ||
                                                           (v5 = sk_h_00463240(0x7a),
                                                           (v5 & 1) != 0)) ||
                                                          ((r21 == 0x6f74617261706573 /* "separato" */ &&
                                                            ctx == -0x16ffffffffffff8e ||
                                                           (v5 = sk_h_004633f4(), (v5 & 1) != 0
                                                           )))) {
                                                    v6 = 0x22;
                                                  }
                                                  else if ((((r21 == 0x6c7a &&
                                                              ctx == -0x1e00000000000000) ||
                                                            (v5 = sk_h_00462e1c(0x6c7a),
                                                            (v5 & 1) != 0)) ||
                                                           (r21 == 0x61706573656e696c /* "linesepa" */ &&
                                                            ctx == -0x12ffff8d908b9e8e)) ||
                                                          (v5 = sk_h_004633f4(), (v5 & 1) != 0)
                                                          ) {
                                                    v6 = 0x23;
                                                  }
                                                  else {
                                                    v1 = r21 == 0x707a &&
                                                            ctx == -0x1e00000000000000;
                                                    if ((((r21 == 0x707a &&
                                                           ctx == -0x1e00000000000000) ||
                                                         (v5 = sk_h_00462e1c(0x707a),
                                                         (v5 & 1) != 0)) ||
                                                        (sk_h_00463474(0)
                                                        , (bool )v1 && out1_04 == ctx
                                                        )) || (v5 = sk_h_00463108(),
                                                              (v5 & 1) != 0)) {
                                                      v6 = 0x24;
                                                    }
                                                    else if ((r21 == 0x737a &&
                                                              ctx == -0x1e00000000000000) ||
                                                            (v5 = sk_h_00462e1c(0x737a),
                                                            (v5 & 1) != 0)) {
                                                      v6 = 0x25;
                                                    }
                                                    else {
                                                      v6 = 0x25;
                                                      if (r21 != 0x7065736563617073 /* "spacesep" */ ||
                                                          ctx != -0x11ff8d908b9e8d9f) {
                                                        v5 = sk_h_004633f4();
                                                        v6 = 0x25;
                                                        if ((v5 & 1) == 0) {
                                                          v6 = 0x26;
                                                        }
                                                      }
                                                    }
                                                  }
                                                  goto LAB_0041e2e8;
                                                  }
                                                  }
                                                  v6 = 0x1f;
                                                  goto LAB_0041e2e8;
                                                  }
                                                  }
                                                  v6 = 0x1d;
                                                  goto LAB_0041e2e8;
                                                  }
                                                  }
                                                  v6 = 0x1c;
                                                  }
                                                  }
                                                  }
                                                  }
                                                  goto LAB_0041e2e8;
                                                  }
                                                  }
                                                  }
                                                  v6 = 0x15;
                                                  }
                                                  goto LAB_0041e2e8;
                                                }
                                              }
                                              v6 = 0x12;
                                              goto LAB_0041e2e8;
                                            }
                                          }
                                          v6 = 0x11;
                                          goto LAB_0041e2e8;
                                        }
                                      }
                                      v6 = 0xf;
                                    }
                                    goto LAB_0041e2e8;
                                  }
                                }
                                v6 = 0xc;
                                goto LAB_0041e2e8;
                              }
                            }
                            v6 = 0xb;
                            goto LAB_0041e2e8;
                          }
                        }
                        v6 = 10;
                      }
                      goto LAB_0041e2e8;
                    }
                  }
                  v6 = 7;
                  goto LAB_0041e2e8;
                }
              }
              v6 = 6;
            }
            goto LAB_0041e2e8;
          }
        }
        v6 = 1;
        goto LAB_0041e2e8;
      }
    }
  }
  v6 = 0;
LAB_0041e2e8:
  *out8 = v6;
  sk_h_0008e500(r30);
  return;
}

/* FUN_0041efc0 @ 0x0041efc0   (est. sk_f_0041efc0)
 * Ghidra: void FUN_0041efc0(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041efc0(void){
  word_t  v1;
  long  out1;
  byte  *r19;
  word_t  r21;
  byte  v2;
  
  sk_h_00353b10();
  if ((r21 == 0x6c616d69636564 /* "decimal" */ && out1 == -0x1900000000000000) ||
     (v1 = sk_h_00462da8(), (v1 & 1) != 0)) {
    v2 = 0;
  }
  else if ((r21 == 0x7469676964 /* "digit" */ && out1 == -0x1b00000000000000) ||
          (v1 = sk_h_00462dd0(), (v1 & 1) != 0)) {
    v2 = 1;
  }
  else {
    v1 = sk_h_00465468();
    v2 = 2;
    if (r21 != (v1 & 0xffffffffffff | 0x63000000000000) ||
        out1 != -0x1900000000000000) {
      v1 = sk_h_00462da8();
      v2 = 2;
      if ((v1 & 1) == 0) {
        v2 = 3;
      }
    }
  }
  *r19 = v2;
  return;
}

/* FUN_0041f074 @ 0x0041f074   (est. sk_f_0041f074)
 * Ghidra: void FUN_0041f074(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0041f074(void){
  byte  v1;
  byte  v2;
  bool  b3;
  word_t  v4;
  byte  *pv5;
  word_t  v6;
  long  out1;
  long  out1_00;
  long  out1_01;
  long  out1_02;
  long  out1_03;
  long  out1_04;
  long  out1_05;
  long  out1_06;
  long  out1_07;
  long  out1_08;
  long  out1_09;
  long  out1_10;
  long  out1_11;
  long  out1_12;
  long  out1_13;
  long  out1_14;
  long  out1_15;
  long  out1_16;
  long  out1_17;
  long  out1_18;
  long  out1_19;
  long  out1_20;
  long  out1_21;
  long  out1_22;
  long  out1_23;
  byte  *out8;
  long  out8_00;
  long  out8_01;
  long  out8_02;
  long  ctx;
  byte  *r21;
  word_t  r30;
  sk16_t sv7;
  
  sv7 = (sk16_t){ sk_h_0008e518(), 0 };
  if (sv7.lo != 0x78656861 /* "ahex" */ || sv7.hi != -0x1c00000000000000) {
    sk_h_0035098c();
    v4 = sk_h_00462cc0(0x78656861 /* "ahex" */);
    if ((((v4 & 1) == 0) &&
        (r21 != (byte  *)0x7865686969637361 /* "asciihex" */ || ctx != -0x12ffff8b9698969c)) &&
       (v4 = sk_h_004633f4(), (v4 & 1) == 0)) {
      if ((r21 != (byte *)0x6168706c61 /* "alpha" */ || ctx != -0x1b00000000000000) &&
         (v4 = sk_h_00462dd0(), (v4 & 1) == 0)) {
        pv5 = (byte *)sk_h_00466250(0xea00000000006465);
        b3 = ctx == out8_00 + -0xfc;
        v1 = r21 == pv5 && b3;
        if ((r21 != pv5 || !b3) && (v4 = sk_h_004633f4(), (v4 & 1) == 0)) {
          sk_h_00466238();
          sk_h_004658b4();
          if ((!(bool )v1 || ctx != -0x1b00000000000000) &&
             (v4 = sk_h_00462dd0(), (v4 & 1) == 0)) {
            v4 = sk_h_00466238();
            pv5 = (byte  *)(v4 & 0xffffffff | 0x746e6f6300000000);
            v1 = r21 == pv5 && ctx == -0x14ffffffff93908e;
            if ((r21 != pv5 || ctx != -0x14ffffffff93908e) &&
               (v4 = sk_h_004633f4(pv5,0xeb000000006c6f72), (v4 & 1) == 0)) {
              sk_h_00466238();
              sk_h_0046518c();
              if (((((bool )v1 && ctx == -0x1b00000000000000) ||
                   (v4 = sk_h_00462dd0(), (v4 & 1) != 0)) ||
                  (sv7 = sk_h_00466238(v4,0xec0000006465726f),
                  r21 == (byte *)(sv7.lo & 0xffffffff | 0x7272696d00000000) &&
                  ctx == sv7.hi)) || (v4 = sk_h_004633f4(), (v4 & 1) != 0)) {
                v1 = 3;
              }
              else if ((r21 == (byte  *)0x6465736163 /* "cased" */ && ctx == -0x1b00000000000000)
                      || (v4 = sk_h_00462dd0(), (v4 & 1) != 0)) {
                v1 = 4;
              }
              else if (((r21 == (byte  *)0x6563 && ctx == -0x1e00000000000000) ||
                       (v4 = sk_h_00462e1c(0x6563), (v4 & 1) != 0)) ||
                      ((sk_h_004643cc(0),
                       r21 == (byte *)0xd000000000000014 && out1 == ctx ||
                       (v4 = sk_h_004633cc(), (v4 & 1) != 0)))) {
                v1 = 5;
              }
              else if ((((r21 == (byte  *)0x6963 && ctx == -0x1e00000000000000) ||
                        (v4 = sk_h_00462e1c(0x6963), (v4 & 1) != 0)) ||
                       (r21 == (byte *)0x6f6e676965736163 /* "caseigno" */ &&
                        ctx == -0x12ffff9a939d9e8e)) ||
                      (v4 = sk_h_004633f4(), (v4 & 1) != 0)) {
                v1 = 6;
              }
              else if (((r21 == (byte  *)0x7865706d6f63 /* "compex" */ &&
                         ctx == -0x1a00000000000000) ||
                       (v4 = sk_h_00462dbc(), (v4 & 1) != 0)) ||
                      ((sk_h_004643cc(0),
                       r21 == (byte *)0xd000000000000018 && out1_00 == ctx
                       || (v4 = sk_h_004633f4(), (v4 & 1) != 0)))) {
                v1 = 0x18;
              }
              else {
                v1 = r21 == (byte  *)0x66637763 /* "cwcf" */ && ctx == -0x1c00000000000000;
                if ((((r21 == (byte  *)0x66637763 /* "cwcf" */ && ctx == -0x1c00000000000000) ||
                     (v4 = sk_h_00462cc0(0x66637763 /* "cwcf" */), (v4 & 1) != 0)) ||
                    (sk_h_00462c6c(0),
                    (bool)v1 && out1_01 == ctx)) ||
                   (v4 = sk_h_00462e30(0x15), (v4 & 1) != 0)) {
                  v1 = 7;
                }
                else {
                  v1 = r21 == (byte  *)0x6d637763 /* "cwcm" */ && ctx == -0x1c00000000000000;
                  if ((((r21 == (byte  *)0x6d637763 /* "cwcm" */ && ctx == -0x1c00000000000000)
                       || (v4 = sk_h_00462cc0(0x6d637763 /* "cwcm" */), (v4 & 1) != 0)) ||
                      (sk_h_00462c6c(0),
                      (bool)v1 && out1_02 == ctx)) ||
                     (v4 = sk_h_00462e30(0x15), (v4 & 1) != 0)) {
                    v1 = 8;
                  }
                  else if (((r21 == (byte  *)0x66636b7763 /* "cwkcf" */ &&
                             ctx == -0x1b00000000000000) ||
                           (v4 = sk_h_00462dd0(), (v4 & 1) != 0)) ||
                          ((sk_h_004643cc(0),
                           r21 == (byte *)0xd000000000000019 &&
                           out1_03 == ctx || (v4 = sk_h_00462df8(), (v4 & 1) != 0)
                           ))) {
                    v1 = 9;
                  }
                  else {
                    v1 = r21 == (byte  *)0x6c7763 /* "cwl" */ && ctx == -0x1d00000000000000;
                    if (((r21 == (byte  *)0x6c7763 /* "cwl" */ && ctx == -0x1d00000000000000) ||
                        (v4 = sk_h_00462ef8(0x6c7763 /* "cwl" */), (v4 & 1) != 0)) ||
                       ((sk_h_00462c6c(0),
                        (bool)v1 && out1_04 == ctx ||
                        (v4 = sk_h_00462e30(0x15), (v4 & 1) != 0)))) {
                      v1 = 10;
                    }
                    else {
                      v1 = r21 == (byte  *)0x747763 /* "cwt" */ && ctx == -0x1d00000000000000
                      ;
                      if ((((r21 == (byte  *)0x747763 /* "cwt" */ && ctx == -0x1d00000000000000)
                           || (v4 = sk_h_00462ef8(0x747763 /* "cwt" */), (v4 & 1) != 0)) ||
                          (sk_h_00462c6c(0),
                          (bool)v1 && out1_05 == ctx)) ||
                         (v4 = sk_h_00462e30(0x15), (v4 & 1) != 0)) {
                        v1 = 0xb;
                      }
                      else {
                        v1 = r21 == (byte  *)0x757763 /* "cwu" */ &&
                                ctx == -0x1d00000000000000;
                        if (((r21 == (byte  *)0x757763 /* "cwu" */ && ctx == -0x1d00000000000000
                             ) || (v4 = sk_h_00462ef8(), (v4 & 1) != 0)) ||
                           ((sk_h_00462c6c(0),
                            (bool)v1 && out1_06 == ctx ||
                            (v4 = sk_h_00462e30(0x15), (v4 & 1) != 0)))) {
                          v1 = 0xc;
                        }
                        else if ((r21 == (byte  *)0x68736164 /* "dash" */ &&
                                  ctx == -0x1c00000000000000) ||
                                (v4 = sk_h_00462cc0(0x68736164 /* "dash" */), (v4 & 1) != 0)) {
                          v1 = 0xd;
                        }
                        else if ((((r21 == (byte  *)0x706564 /* "dep" */ &&
                                    ctx == -0x1d00000000000000) ||
                                  (v4 = sk_h_00462ef8(0x706564 /* "dep" */), (v4 & 1) != 0)) ||
                                 (r21 == (byte *)0x7461636572706564 /* "deprecat" */ &&
                                  ctx == -0x15ffffffffff9b9b)) ||
                                (v4 = sk_h_0046311c(0x7461636572706564 /* "deprecat" */,0x6465), (v4 & 1) != 0))
                        {
                          v1 = 0xe;
                        }
                        else {
                          v1 = r21 == (byte  *)0x6964 &&
                                  ctx == -0x1e00000000000000;
                          if (((r21 == (byte  *)0x6964 && ctx == -0x1e00000000000000
                               ) || (v4 = sk_h_00462e1c(0x6964), (v4 & 1) != 0)) ||
                             ((sk_h_00463474(0),
                              (bool)v1 && out1_07 == ctx ||
                              (v4 = sk_h_004633f4(0xd000000000000019), (v4 & 1) != 0)))) {
                            v1 = 0xf;
                          }
                          else if (((r21 == 0 /*DAT_00616964*/ && ctx == -0x1d00000000000000)
                                   || (v4 = sk_h_00462ef8(0 /*DAT_00616964*/), (v4 & 1) != 0)) ||
                                  ((v1 = r21 == (byte  *)0x6974697263616964 /* "diacriti" */ &&
                                            ctx == -0x16ffffffffffff9d,
                                   r21 == (byte *)0x6974697263616964 /* "diacriti" */ &&
                                   ctx == -0x16ffffffffffff9d ||
                                   (v4 = sk_h_004633f4(), (v4 & 1) != 0)))) {
                            v1 = 0x10;
                          }
                          else {
                            sk_h_004661f0(0x73616265 /* "ebas" */);
                            if (((((bool )v1 && ctx == -0x1b00000000000000) ||
                                 (v4 = sk_h_00462dd0(), (v4 & 1) != 0)) ||
                                (sk_h_004643cc(0),
                                r21 == (byte *)0xd000000000000011 &&
                                out1_08 == ctx)) ||
                               (v4 = sk_h_00462df8(), (v4 & 1) != 0)) {
                              v1 = 0x11;
                            }
                            else if (((r21 == (byte  *)0x706d6f6365 /* "ecomp" */ &&
                                       ctx == -0x1b00000000000000) ||
                                     (v4 = sk_h_00462dd0(), (v4 & 1) != 0)) ||
                                    ((r21 == (byte *)0x6d6f63696a6f6d65 /* "emojicom" */ &&
                                      ctx == -0x11ff8b919a919090 ||
                                     (v4 = sk_h_004633f4(), (v4 & 1) != 0)))) {
                              v1 = 0x12;
                            }
                            else if (((r21 == (byte  *)0x646f6d65 /* "emod" */ &&
                                       ctx == -0x1c00000000000000) ||
                                     (v4 = sk_h_00462cc0(0x646f6d65 /* "emod" */), (v4 & 1) != 0)) ||
                                    ((v1 = r21 == (byte *)0x646f6d696a6f6d65 /* "emojimod" */ &&
                                              ctx == -0x12ffff8d9a969997,
                                     r21 == (byte *)0x646f6d696a6f6d65 /* "emojimod" */ &&
                                     ctx == -0x12ffff8d9a969997 ||
                                     (v4 = sk_h_004633f4(), (v4 & 1) != 0)))) {
                              v1 = 0x13;
                            }
                            else {
                              sk_h_004661d8(0x6a6f6d65 /* "emoj" */);
                              if (((bool )v1 && ctx == -0x1b00000000000000) ||
                                 (v4 = sk_h_00462dd0(), (v4 & 1) != 0)) {
                                v1 = 0x14;
                              }
                              else {
                                v1 = r21 == (byte  *)0x7365727065 /* "epres" */ &&
                                        ctx == -0x1b00000000000000;
                                if ((((r21 == (byte  *)0x7365727065 /* "epres" */ &&
                                       ctx == -0x1b00000000000000) ||
                                     (v4 = sk_h_00462dd0(), (v4 & 1) != 0)) ||
                                    (sk_h_00463474(0),
                                    (bool)v1 && out1_09 == ctx)) ||
                                   (v4 = sk_h_00462df8(), (v4 & 1) != 0)) {
                                  v1 = 0x15;
                                }
                                else if (((r21 == (byte  *)0x747865 /* "ext" */ &&
                                           ctx == -0x1d00000000000000) ||
                                         (v4 = sk_h_00462ef8(), (v4 & 1) != 0)) ||
                                        ((v1 = r21 == (byte *)0x7265646e65747865 /* "extender" */ &&
                                                  ctx == -0x1800000000000000,
                                         r21 == (byte *)0x7265646e65747865 /* "extender" */ &&
                                         ctx == -0x1800000000000000 ||
                                         (v4 = sk_h_00462de4(), (v4 & 1) != 0)))) {
                                  v1 = 0x16;
                                }
                                else {
                                  sk_h_004661cc(0x636970747865 /* "extpic" */);
                                  v2 = (bool )v1 && ctx == -0x1900000000000000;
                                  if ((((bool )v1 && ctx == -0x1900000000000000) ||
                                      (v4 = sk_h_00462da8(), (v4 & 1) != 0)) ||
                                     ((sk_h_00463334(0),
                                      (bool)v2 && out1_10 == ctx ||
                                      (v4 = sk_h_004633cc(), (v4 & 1) != 0)))) {
                                    v1 = 0x17;
                                  }
                                  else if ((((r21 == (byte  *)0x657361627267 /* "grbase" */ &&
                                              ctx == -0x1a00000000000000) ||
                                            (v4 = sk_h_00462dbc(), (v4 & 1) != 0)) ||
                                           (r21 == (byte *)0x656d656870617267 /* "grapheme" */ &&
                                            ctx == -0x13ffffff9a8c9e9e)) ||
                                          (v4 = sk_h_004633cc(), (v4 & 1) != 0)) {
                                    v1 = 0x19;
                                  }
                                  else {
                                    if (r21 != (byte  *)0x7478657267 /* "grext" */ ||
                                        ctx != -0x1b00000000000000) {
                                      v4 = sk_h_00462dd0();
                                      v1 = 0x1a;
                                      if (((v4 & 1) != 0) ||
                                         (r21 == (byte  *)0x656d656870617267 /* "grapheme" */ &&
                                          ctx == -0x11ff9b919a8b879b)) goto LAB_0041f0f4;
                                      v4 = sk_h_004633cc();
                                      if ((v4 & 1) == 0) {
                                        if (r21 != (byte  *)0x6b6e696c7267 /* "grlink" */ ||
                                            ctx != -0x1a00000000000000) {
                                          v4 = sk_h_00462dbc();
                                          v1 = 0x1b;
                                          if (((v4 & 1) != 0) ||
                                             (r21 == (byte  *)0x656d656870617267 /* "grapheme" */ &&
                                              ctx == -0x13ffffff94919694)) goto LAB_0041f0f4;
                                          v4 = sk_h_004633cc();
                                          if ((v4 & 1) == 0) {
                                            if (r21 != (byte  *)0x786568 /* "hex" */ ||
                                                ctx != -0x1d00000000000000) {
                                              v4 = sk_h_00462ef8(0x786568 /* "hex" */);
                                              v1 = 0x1c;
                                              if (((v4 & 1) != 0) ||
                                                 (r21 == (byte  *)0x7469676964786568 /* "hexdigit" */ &&
                                                  ctx == -0x1800000000000000))
                                              goto LAB_0041f0f4;
                                              v4 = sk_h_00462de4(0x7469676964786568 /* "hexdigit" */);
                                              if ((v4 & 1) == 0) {
                                                if ((r21 == (byte  *)0x6e6568707968 /* "hyphen" */ &&
                                                     ctx == -0x1a00000000000000) ||
                                                   (v4 = sk_h_00462dbc(), (v4 & 1) != 0)) {
                                                  v1 = 0x1d;
                                                }
                                                else if ((((r21 == 0 /*DAT_00636469*/ &&
                                                            ctx == -0x1d00000000000000) ||
                                                          (v4 = sk_h_00462ef8(0 /*DAT_00636469*/),
                                                          (v4 & 1) != 0)) ||
                                                         (r21 ==
                                                          (byte  *)0x6e69746e6f636469 /* "idcontin" */ &&
                                                          ctx == -0x15ffffffffff9a8b)) ||
                                                        (v4 = sk_h_004633f4(), (v4 & 1) != 0))
                                                {
                                                  v1 = 0x1e;
                                                }
                                                else if (((r21 == (byte  *)0x6f656469 /* "ideo" */ &&
                                                           ctx == -0x1c00000000000000) ||
                                                         (v4 = sk_h_00462cc0(0x6f656469 /* "ideo" */),
                                                         (v4 & 1) != 0)) ||
                                                        ((r21 ==
                                                          (byte *)0x706172676f656469 /* "ideograp" */ &&
                                                          ctx == -0x14ffffffff9c9698 ||
                                                         (v4 = sk_h_004633f4(), (v4 & 1) != 0))
                                                        )) {
                                                  v1 = 0x1f;
                                                }
                                                else {
                                                  if (r21 != (byte  *)0x736469 /* "ids" */ ||
                                                      ctx != -0x1d00000000000000) {
                                                    v4 = sk_h_00462ef8(0x736469 /* "ids" */);
                                                    v1 = 0x20;
                                                    if (((v4 & 1) != 0) ||
                                                       (r21 == (byte  *)0x74726174736469 /* "idstart" */
                                                        && ctx == -0x1900000000000000))
                                                    goto LAB_0041f0f4;
                                                    v4 = sk_h_00462da8(0x74726174736469 /* "idstart" */);
                                                    if ((v4 & 1) == 0) {
                                                      v1 = r21 == (byte  *)0x62736469 /* "idsb" */
                                                              && ctx == -0x1c00000000000000;
                                                      if ((((r21 == (byte  *)0x62736469 /* "idsb" */ &&
                                                             ctx == -0x1c00000000000000) ||
                                                           (v4 = sk_h_00462cc0(0x62736469 /* "idsb" */),
                                                           (v4 & 1) != 0)) ||
                                                          (sk_h_00463474(0
                                                                       ),
                                                          (bool)v1 && out1_11 == ctx
                                                          )) || (v4 = sk_h_00462df8(),
                                                                (v4 & 1) != 0)) {
                                                        v1 = 0x21;
                                                        goto LAB_0041f0f4;
                                                      }
                                                      if ((r21 != (byte  *)0x74736469 /* "idst" */ ||
                                                           ctx != -0x1c00000000000000) &&
                                                         (v4 = sk_h_00462cc0(0x74736469 /* "idst" */),
                                                         (v4 & 1) == 0)) {
                                                        sk_h_004643cc(0);
                                                        v1 = r21 ==
                                                                (byte  *)0xd000000000000012 &&
                                                                out1_12 == ctx;
                                                        if ((r21 !=
                                                             (byte  *)0xd000000000000012 ||
                                                             out1_12 != ctx) &&
                                                           (v4 = sk_h_004633f4(), (v4 & 1) == 0
                                                           )) {
                                                          sk_h_004658b4(0x6e696f6a /* "join" */);
                                                          if (!(bool )v1 ||
                                                              ctx != -0x1b00000000000000) {
                                                            v4 = sk_h_00462dd0();
                                                            v1 = 0x23;
                                                            if (((v4 & 1) != 0) ||
                                                               (r21 ==
                                                                (byte  *)0x746e6f636e696f6a /* "joincont" */ &&
                                                                ctx == -0x14ffffffff93908e))
                                                            goto LAB_0041f0f4;
                                                            v4 = sk_h_004633f4(0x746e6f636e696f6a /* "joincont" */,
                                                                                 0xeb000000006c6f72)
                                                            ;
                                                            if ((v4 & 1) == 0) {
                                                              v1 = r21 ==
                                                                      (byte  *)0x656f6c /* "loe" */ &&
                                                                      ctx ==
                                                                      -0x1d00000000000000;
                                                              if ((r21 !=
                                                                   (byte  *)0x656f6c /* "loe" */ ||
                                                                   ctx != -0x1d00000000000000)
                                                                 && (v4 = sk_h_00462ef8(0x656f6c /* "loe" */),
                                                                    (v4 & 1) == 0)) {
                                                                sk_h_00462c6c(
                                                  0);
                                                  v2 = (bool )v1 && out1_13 == ctx
                                                  ;
                                                  if ((!(bool )v1 || out1_13 != ctx)
                                                     && (v4 = sk_h_00462e30(0x15),
                                                        (v4 & 1) == 0)) {
                                                    sk_h_004657dc(0x65776f6c /* "lowe" */);
                                                    v1 = (bool )v2 &&
                                                            ctx == -0x1b00000000000000;
                                                    if (((((bool )v2 &&
                                                           ctx == -0x1b00000000000000) ||
                                                         (v4 = sk_h_00462dd0(), (v4 & 1) != 0))
                                                        || (v6 = sk_h_00465590(),
                                                           (bool)v1 &&
                                                           ctx == -0x16ffffffffffff9b)) ||
                                                       (v4 = sk_h_00463254(v6,0x65),
                                                       (v4 & 1) != 0)) {
                                                      v1 = 0x25;
                                                    }
                                                    else {
                                                      v1 = r21 == (byte  *)0x6874616d /* "math" */
                                                              && ctx == -0x1c00000000000000;
                                                      if (((bool )v1) ||
                                                         (v4 = sk_h_00462cc0(0x6874616d /* "math" */),
                                                         (v4 & 1) != 0)) {
                                                        v1 = 0x26;
                                                      }
                                                      else {
                                                        sk_h_004657dc(0x6168636e /* "ncha" */);
                                                        v2 = (bool )v1 &&
                                                                ctx == -0x1b00000000000000;
                                                        if ((((bool )v1 &&
                                                              ctx == -0x1b00000000000000) ||
                                                            (v4 = sk_h_00462dd0(),
                                                            (v4 & 1) != 0)) ||
                                                           ((sk_h_00462c6c(
                                                  0),
                                                  (bool)v2 && out1_14 == ctx ||
                                                  (v4 = sk_h_00462e30(0x15), (v4 & 1) != 0))))
                                                  {
                                                    v1 = 0x27;
                                                  }
                                                  else if ((((r21 ==
                                                              (byte  *)0x6168706c616f /* "oalpha" */ &&
                                                              ctx == -0x1a00000000000000) ||
                                                            (v4 = sk_h_00462dbc(),
                                                            (v4 & 1) != 0)) ||
                                                           (sv7 = sk_h_0046493c(v4,
                                                  0xef63697465626168),
                                                  r21 ==
                                                  (byte *)
                                                  (sv7.lo & 0xffffffff | 0x706c617200000000)
                                                  && ctx == sv7.hi)) ||
                                                  (v4 = sk_h_004633f4(), (v4 & 1) != 0)) {
                                                    v1 = 0x28;
                                                  }
                                                  else if (((r21 == 0 /*DAT_0069646f*/ &&
                                                             ctx == -0x1d00000000000000) ||
                                                           (v4 = sk_h_00462ef8(0 /*DAT_0069646f*/),
                                                           (v4 & 1) != 0)) ||
                                                          ((sk_h_004643cc(
                                                  0),
                                                  r21 == (byte  *)0xd00000000000001e &&
                                                  out1_15 == ctx ||
                                                  (v4 = sk_h_004633f4(), (v4 & 1) != 0)))) {
                                                    v1 = 0x29;
                                                  }
                                                  else if ((((r21 ==
                                                              (byte  *)0x74786572676f /* "ogrext" */ &&
                                                              ctx == -0x1a00000000000000) ||
                                                            (v4 = sk_h_00462dbc(),
                                                            (v4 & 1) != 0)) ||
                                                           (sk_h_004643cc(
                                                  0),
                                                  r21 == (byte *)0xd000000000000013 &&
                                                  out1_16 == ctx)) ||
                                                  (v4 = sk_h_004633b8(), (v4 & 1) != 0)) {
                                                    v1 = 0x2a;
                                                  }
                                                  else if ((((r21 == (byte  *)0x6364696f /* "oidc" */
                                                              && ctx == -0x1c00000000000000)
                                                            || (v4 = sk_h_00462cc0(0x6364696f /* "oidc" */),
                                                               (v4 & 1) != 0)) ||
                                                           (sv7 = sk_h_0046493c(v4,
                                                  0xef65756e69746e6f),
                                                  r21 ==
                                                  (byte *)
                                                  (sv7.lo & 0xffffffff | 0x6364697200000000)
                                                  && ctx == sv7.hi)) ||
                                                  (v4 = sk_h_004633f4(), (v4 & 1) != 0)) {
                                                    v1 = 0x2b;
                                                  }
                                                  else if (((r21 == (byte  *)0x7364696f /* "oids" */ &&
                                                             ctx == -0x1c00000000000000) ||
                                                           (v4 = sk_h_00462cc0(0x7364696f /* "oids" */),
                                                           (v4 & 1) != 0)) ||
                                                          ((sv7 = sk_h_0046493c(v4,
                                                  0xec00000074726174),
                                                  r21 ==
                                                  (byte *)
                                                  (sv7.lo & 0xffffffff | 0x7364697200000000)
                                                  && ctx == sv7.hi ||
                                                  (v4 = sk_h_004633f4(), (v4 & 1) != 0)))) {
                                                    v1 = 0x2c;
                                                  }
                                                  else if (((r21 ==
                                                             (byte  *)0x7265776f6c6f /* "olower" */ &&
                                                             ctx == -0x1a00000000000000) ||
                                                           (v4 = sk_h_00462dbc(), (v4 & 1) != 0
                                                           )) || ((v4 = sk_h_0046493c(),
                                                                  r21 ==
                                                                  (byte *)
                                                                  (v4 & 0xffffffff |
                                                                  0x776f6c7200000000) &&
                                                                  ctx == -0x11ff9a8c9e9c8d9b
                                                                  || (v4 = sk_h_00463180(),
                                                                     (v4 & 1) != 0)))) {
                                                    v1 = 0x2d;
                                                  }
                                                  else if ((((r21 == (byte  *)0x6874616d6f /* "omath" */
                                                              && ctx == -0x1b00000000000000)
                                                            || (v4 = sk_h_00462dd0(),
                                                               (v4 & 1) != 0)) ||
                                                           (v4 = sk_h_0046493c(),
                                                           r21 ==
                                                           (byte *)
                                                           (v4 & 0xffffffff | 0x74616d7200000000)
                                                           && ctx == -0x16ffffffffffff98)) ||
                                                          (v4 = sk_h_004633f4(), (v4 & 1) != 0)
                                                          ) {
                                                    v1 = 0x2e;
                                                  }
                                                  else {
                                                    if (r21 != (byte  *)0x72657070756f /* "oupper" */ ||
                                                        ctx != -0x1a00000000000000) {
                                                      v4 = sk_h_00462dbc();
                                                      v1 = 0x2f;
                                                      if (((v4 & 1) != 0) ||
                                                         (r21 ==
                                                          (byte  *)0x707075726568746f /* "otherupp" */ &&
                                                          ctx == -0x11ff9a8c9e9c8d9b))
                                                      goto LAB_0041f0f4;
                                                      v4 = sk_h_00463180(0x707075726568746f /* "otherupp" */);
                                                      if ((v4 & 1) == 0) {
                                                        if (((r21 ==
                                                              (byte  *)0x6e7973746170 /* "patsyn" */ &&
                                                              ctx == -0x1a00000000000000) ||
                                                            (v4 = sk_h_00462dbc(),
                                                            (v4 & 1) != 0)) ||
                                                           ((r21 ==
                                                             (byte *)0x736e726574746170 /* "patterns" */ &&
                                                             ctx == -0x12ffff879e8b9187 ||
                                                            (v4 = sk_h_004633f4(),
                                                            (v4 & 1) != 0)))) {
                                                          v1 = 0x30;
                                                        }
                                                        else {
                                                          v1 = r21 ==
                                                                  (byte  *)0x7377746170 /* "patws" */ &&
                                                                  ctx == -0x1b00000000000000;
                                                          if ((((r21 ==
                                                                 (byte  *)0x7377746170 /* "patws" */ &&
                                                                 ctx == -0x1b00000000000000)
                                                               || (v4 = sk_h_00462dd0(),
                                                                  (v4 & 1) != 0)) ||
                                                              (sk_h_00463474(
                                                  0),
                                                  (bool)v1 && out1_17 == ctx)) ||
                                                  (v4 = sk_h_00462df8(), (v4 & 1) != 0)) {
                                                    v1 = 0x31;
                                                  }
                                                  else if (((r21 == (byte  *)0x6d6370 /* "pcm" */ &&
                                                             ctx == -0x1d00000000000000) ||
                                                           (v4 = sk_h_00462ef8(0x6d6370 /* "pcm" */),
                                                           (v4 & 1) != 0)) ||
                                                          ((sk_h_004643cc(
                                                  0),
                                                  r21 == (byte *)0xd00000000000001a &&
                                                  out1_18 == ctx ||
                                                  (v4 = sk_h_004633f4(), (v4 & 1) != 0)))) {
                                                    v1 = 0x32;
                                                  }
                                                  else if ((((r21 == (byte  *)0x6b72616d71 /* "qmark" */
                                                              && ctx == -0x1b00000000000000)
                                                            || (v4 = sk_h_00462dd0(),
                                                               (v4 & 1) != 0)) ||
                                                           (r21 ==
                                                            (byte *)0x6f697461746f7571 /* "quotatio" */ &&
                                                            ctx == -0x12ffff948d9e9292)) ||
                                                          (v4 = sk_h_004633f4(), (v4 & 1) != 0)
                                                          ) {
                                                    v1 = 0x33;
                                                  }
                                                  else if ((r21 ==
                                                            (byte  *)0x6c616369646172 /* "radical" */ &&
                                                            ctx == -0x1900000000000000) ||
                                                          (v4 = sk_h_00462da8(), (v4 & 1) != 0)
                                                          ) {
                                                    v1 = 0x34;
                                                  }
                                                  else {
                                                    v1 = r21 == (byte  *)0x6972 &&
                                                            ctx == -0x1e00000000000000;
                                                    if ((((r21 == (byte  *)0x6972 &&
                                                           ctx == -0x1e00000000000000) ||
                                                         (v4 = sk_h_00462e1c(0x6972),
                                                         (v4 & 1) != 0)) ||
                                                        (sk_h_00463474(0),
                                                        (bool)v1 && out1_19 == ctx))
                                                       || (v4 = sk_h_00462df8(), (v4 & 1) != 0)
                                                       ) {
                                                      v1 = 0x35;
                                                    }
                                                    else {
                                                      if (r21 != (byte  *)0x6473 ||
                                                          ctx != -0x1e00000000000000) {
                                                        v4 = sk_h_00462e1c(0x6473);
                                                        v2 = r21 ==
                                                                (byte  *)0x74746f6474666f73 /* "softdott" */ &&
                                                                ctx == -0x15ffffffffff9b9b;
                                                        v1 = 0x36;
                                                        if (((v4 & 1) != 0) || ((bool )v2))
                                                        goto LAB_0041f0f4;
                                                        v4 = sk_h_0046311c(0x74746f6474666f73 /* "softdott" */,
                                                                             0x6465);
                                                        if ((v4 & 1) == 0) {
                                                          sk_h_0046518c(0x72657473 /* "ster" */);
                                                          if ((((bool )v2 &&
                                                                ctx == -0x1b00000000000000) ||
                                                              (v4 = sk_h_00462dd0(),
                                                              (v4 & 1) != 0)) ||
                                                             ((sk_h_004643cc(
                                                  0),
                                                  r21 == (byte *)0xd000000000000010 &&
                                                  out1_20 == ctx ||
                                                  (v4 = sk_h_004633cc(), (v4 & 1) != 0)))) {
                                                    v1 = 0x37;
                                                  }
                                                  else if ((((r21 == (byte  *)0x6d726574 /* "term" */
                                                              && ctx == -0x1c00000000000000)
                                                            || (v4 = sk_h_00462cc0(0x6d726574 /* "term" */),
                                                               (v4 & 1) != 0)) ||
                                                           (sk_h_004643cc(
                                                  0),
                                                  r21 == (byte *)0xd000000000000013 &&
                                                  out1_21 == ctx)) ||
                                                  (v4 = sk_h_004633b8(), (v4 & 1) != 0)) {
                                                    v1 = 0x38;
                                                  }
                                                  else {
                                                    v1 = r21 == (byte  *)0x6f65646975 /* "uideo" */
                                                            && ctx == -0x1b00000000000000;
                                                    if ((r21 != (byte  *)0x6f65646975 /* "uideo" */ ||
                                                         ctx != -0x1b00000000000000) &&
                                                       (v4 = sk_h_00462dd0(), (v4 & 1) == 0)) {
                                                      sk_h_00463334(0);
                                                      v2 = (bool )v1 &&
                                                              out1_22 == ctx;
                                                      if ((!(bool )v1 ||
                                                           out1_22 != ctx) &&
                                                         (v4 = sk_h_004633cc(), (v4 & 1) == 0))
                                                      {
                                                        sk_h_004657dc(0x65707075 /* "uppe" */);
                                                        if (!(bool )v2 ||
                                                            ctx != -0x1b00000000000000) {
                                                          v4 = sk_h_00462dd0();
                                                          v1 = 0x3a;
                                                          if (((v4 & 1) != 0) ||
                                                             (r21 ==
                                                              (byte  *)0x7361637265707075 /* "uppercas" */ &&
                                                              ctx == -0x16ffffffffffff9b))
                                                          goto LAB_0041f0f4;
                                                          v4 = sk_h_00463254(0x7361637265707075 /* "uppercas" */,
                                                                               0x65);
                                                          if ((v4 & 1) == 0) {
                                                            v1 = r21 == (byte  *)0x7376
                                                                    && ctx ==
                                                                       -0x1e00000000000000;
                                                            if ((((r21 == (byte  *)0x7376
                                                                   && ctx ==
                                                                      -0x1e00000000000000) ||
                                                                 (v4 = sk_h_00462e1c(0x7376),
                                                                 (v4 & 1) != 0)) ||
                                                                (sk_h_00463474(
                                                  0),
                                                  (bool)v1 && out1_23 == ctx)) ||
                                                  (v4 = sk_h_00462df8(), (v4 & 1) != 0)) {
                                                    v1 = 0x3b;
                                                    goto LAB_0041f0f4;
                                                  }
                                                  if (((r21 != (byte  *)0x656361707377 /* "wspace" */ ||
                                                        ctx != -0x1a00000000000000) &&
                                                      (v4 = sk_h_00462dbc(), (v4 & 1) == 0)) &&
                                                     (v2 = r21 ==
                                                              (byte *)0x6170736574696877 /* "whitespa" */ &&
                                                              ctx == -0x15ffffffffff9a9d,
                                                     r21 != (byte *)0x6170736574696877 /* "whitespa" */ ||
                                                     ctx != -0x15ffffffffff9a9d)) {
                                                    sk_h_004633f4();
                                                    v4 = sk_h_00464930();
                                                    v1 = 0x3c;
                                                    if (((v4 & 1) != 0) ||
                                                       ((bool )v2 && ctx == out8_01))
                                                    goto LAB_0041f0f4;
                                                    v4 = sk_h_00462dd0(0x6563617073 /* "space" */);
                                                    if ((v4 & 1) == 0) {
                                                      if ((((r21 == (byte  *)0x63646978 /* "xidc" */ &&
                                                             ctx == -0x1c00000000000000) ||
                                                           (v4 = sk_h_00462cc0(), (v4 & 1) != 0
                                                           )) || (r21 ==
                                                                  (byte *)0x69746e6f63646978 /* "xidconti" */ &&
                                                                  ctx == -0x14ffffffff9a8a92))
                                                         || (v4 = sk_h_004633f4(),
                                                            (v4 & 1) != 0)) {
                                                        v1 = 0x3d;
                                                        goto LAB_0041f0f4;
                                                      }
                                                      v2 = r21 == (byte  *)0x73646978 /* "xids" */
                                                              && ctx == -0x1c00000000000000;
                                                      if (r21 != (byte  *)0x73646978 /* "xids" */ ||
                                                          ctx != -0x1c00000000000000) {
                                                        sk_h_00462cc0();
                                                        v4 = sk_h_00464034();
                                                        v2 = (bool )v2 &&
                                                                ctx == out8_02;
                                                        v1 = 0x3e;
                                                        if (((v4 & 1) != 0) || ((bool )v2))
                                                        goto LAB_0041f0f4;
                                                        v4 = sk_h_00462de4(0x7472617473646978 /* "xidstart" */);
                                                        if ((v4 & 1) == 0) {
                                                          sk_h_004660b4();
                                                          sk_h_004658b4();
                                                          if ((((bool )v2 &&
                                                                ctx == -0x1b00000000000000) ||
                                                              (v4 = sk_h_00462dd0(),
                                                              (v4 & 1) != 0)) ||
                                                             ((r21 ==
                                                               (byte *)0x6f73646e61707865 /* "expandso" */ &&
                                                               ctx == -0x13ffffff9c999192 ||
                                                              (v4 = sk_h_004633b8(),
                                                              (v4 & 1) != 0)))) {
                                                            v1 = 0x3f;
                                                            goto LAB_0041f0f4;
                                                          }
                                                          v4 = sk_h_004660b4();
                                                          if (r21 !=
                                                              (byte  *)
                                                              (v4 & 0xffff0000ffffffff |
                                                              0x6400000000) ||
                                                              ctx != -0x1b00000000000000) {
                                                            v4 = sk_h_00462dd0();
                                                            v1 = 0x40;
                                                            if (((v4 & 1) != 0) ||
                                                               (r21 ==
                                                                (byte  *)0x6f73646e61707865 /* "expandso" */ &&
                                                                ctx == -0x13ffffff9b999192))
                                                            goto LAB_0041f0f4;
                                                            v4 = sk_h_004633b8();
                                                            if ((v4 & 1) == 0) {
                                                              v4 = sk_h_004660b4();
                                                              if (r21 !=
                                                                  (byte  *)
                                                                  (v4 & 0xffff0000ffffffff |
                                                                  0x636b00000000) ||
                                                                  ctx != -0x1a00000000000000)
                                                              {
                                                                v4 = sk_h_00462dbc();
                                                                v1 = 0x41;
                                                                if (((v4 & 1) != 0) ||
                                                                   (r21 ==
                                                                    (byte  *)0x6f73646e61707865 /* "expandso" */
                                                                    && ctx ==
                                                                       -0x12ffff9c94999192))
                                                                goto LAB_0041f0f4;
                                                                v4 = sk_h_004633b8();
                                                                if ((v4 & 1) == 0) {
                                                                  v4 = sk_h_004660b4();
                                                                  if (r21 ==
                                                                      (byte  *)
                                                                      (v4 & 0xffff0000ffffffff |
                                                                      0x646b00000000) &&
                                                                      ctx ==
                                                                      -0x1a00000000000000) {
                                                                    v1 = 0x42;
                                                                  }
                                                                  else {
                                                                    v4 = sk_h_00462dbc();
                                                                    v1 = 0x42;
                                                                    if (((v4 & 1) == 0) &&
                                                                       (r21 !=
                                                                        (byte  *)
                                                                        0x6f73646e61707865 /* "expandso" */ ||
                                                                        ctx !=
                                                                        -0x12ffff9b94999192)) {
                                                                      v4 = sk_h_004633b8();
                                                                      v1 = 0x42;
                                                                      if ((v4 & 1) == 0) {
                                                                        v1 = 0x43;
                                                                      }
                                                                    }
                                                                  }
                                                                  goto LAB_0041f0f4;
                                                                }
                                                              }
                                                              v1 = 0x41;
                                                              goto LAB_0041f0f4;
                                                            }
                                                          }
                                                          v1 = 0x40;
                                                          goto LAB_0041f0f4;
                                                        }
                                                      }
                                                      v1 = 0x3e;
                                                      goto LAB_0041f0f4;
                                                    }
                                                  }
                                                  v1 = 0x3c;
                                                  goto LAB_0041f0f4;
                                                  }
                                                  }
                                                  v1 = 0x3a;
                                                  goto LAB_0041f0f4;
                                                  }
                                                  }
                                                  v1 = 0x39;
                                                  }
                                                  goto LAB_0041f0f4;
                                                  }
                                                  }
                                                  v1 = 0x36;
                                                  }
                                                  }
                                                  }
                                                  goto LAB_0041f0f4;
                                                  }
                                                  }
                                                  v1 = 0x2f;
                                                  }
                                                  }
                                                  }
                                                  goto LAB_0041f0f4;
                                                  }
                                                  }
                                                  v1 = 0x24;
                                                  goto LAB_0041f0f4;
                                                  }
                                                  }
                                                  v1 = 0x23;
                                                  goto LAB_0041f0f4;
                                                  }
                                                  }
                                                  v1 = 0x22;
                                                  goto LAB_0041f0f4;
                                                  }
                                                  }
                                                  v1 = 0x20;
                                                }
                                                goto LAB_0041f0f4;
                                              }
                                            }
                                            v1 = 0x1c;
                                            goto LAB_0041f0f4;
                                          }
                                        }
                                        v1 = 0x1b;
                                        goto LAB_0041f0f4;
                                      }
                                    }
                                    v1 = 0x1a;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              goto LAB_0041f0f4;
            }
          }
          v1 = 2;
          goto LAB_0041f0f4;
        }
      }
      v1 = 1;
      goto LAB_0041f0f4;
    }
  }
  v1 = 0;
LAB_0041f0f4:
  *out8 = v1;
  sk_h_0008e500(r30);
  return;
}

/* FUN_00420618 @ 0x00420618   (est. sk_f_00420618)
 * Ghidra: void FUN_00420618(undefined1 *param_1,long param_2,long param_3)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_00420618(byte* param_1, long param_2, long param_3){
  byte  v1;
  word_t  v2;
  long  ctx;
  long  r21;
  
  if (param_2 != 0x74 || param_3 != -0x1f00000000000000) {
    sk_h_0035098c();
    v2 = sk_h_00463240(0x74);
    if (((v2 & 1) == 0) && (r21 != 0x65757274 /* "true" */ || ctx != -0x1c00000000000000)) {
      v2 = sk_h_00462cc0(0x65757274 /* "true" */);
      v1 = 1;
      if (((v2 & 1) != 0) || (r21 == 0x79 && ctx == -0x1f00000000000000))
      goto LAB_004206c8;
      v2 = sk_h_00463240(0x79);
      if ((((v2 & 1) == 0) && (r21 != 0x736579 /* "yes" */ || ctx != -0x1d00000000000000)) &&
         (v2 = sk_h_00462ef8(0x736579 /* "yes" */), (v2 & 1) == 0)) {
        v1 = r21 == 0x66 && ctx == -0x1f00000000000000;
        if (((r21 != 0x66 || ctx != -0x1f00000000000000) &&
            (v2 = sk_h_00463240(0x66), (v2 & 1) == 0)) &&
           (sk_h_004661f0(0x736c6166 /* "fals" */), !(bool )v1 || ctx != -0x1b00000000000000)) {
          v2 = sk_h_00462dd0();
          v1 = 0;
          if (((v2 & 1) != 0) || (r21 == 0x6e && ctx == -0x1f00000000000000))
          goto LAB_004206c8;
          v2 = sk_h_00463240(0x6e);
          if (((v2 & 1) == 0) && (r21 != 0x6f6e || ctx != -0x1e00000000000000)) {
            v2 = sk_h_00462e1c(0x6f6e);
            v1 = 0;
            if ((v2 & 1) == 0) {
              v1 = 2;
            }
            goto LAB_004206c8;
          }
        }
        v1 = 0;
        goto LAB_004206c8;
      }
    }
  }
  v1 = 1;
LAB_004206c8:
  *param_1 = v1;
  return;
}

/* FUN_00420770 @ 0x00420770   (est. sk_f_00420770)
 * Ghidra: word_t FUN_00420770(void)
 * 
 * Confidence: medium
 * Notes:  */
word_t sk_f_00420770(void){
  word_t  ctx;
  
  sk_h_00356c6c();
  sk_h_002ad78c(0x67f9b8);
  sk_h_00465240();
  if (5 < ctx) {
    ctx = 6;
  }
  return ctx;
}

/* FUN_00428f4c @ 0x00428f4c   (est. sk_f_00428f4c)
 * Ghidra: void FUN_00428f4c(undefined8 *param_1,long param_2,long param_3)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_00428f4c(word_t* param_1, long param_2, long param_3){
  byte  v1;
  word_t  v2;
  word_t  v3;
  long  ctx;
  long  r21;
  
  if (param_2 == 0x796e61 /* "any" */ && param_3 == -0x1d00000000000000) {
LAB_00428f90:
    param_1[1] = 0;
    *param_1 = 0;
    param_1[3] = 0;
    param_1[2] = 0;
  }
  else {
    sk_h_0035098c();
    v2 = sk_h_00462ef8(0x796e61 /* "any" */);
    if ((v2 & 1) != 0) goto LAB_00428f90;
    v1 = r21 == 0x64656e6769737361 /* "assigned" */ && ctx == -0x1800000000000000;
    if (((bool )v1) || (v2 = sk_h_00462de4(), (v2 & 1) != 0)) {
      v3 = 1;
    }
    else {
      sk_h_004661d8(0x69637361 /* "asci" */);
      if ((!(bool )v1 || ctx != -0x1b00000000000000) &&
         (v2 = sk_h_00462dd0(), (v2 & 1) == 0)) {
        param_1[1] = 0;
        *param_1 = 0;
        param_1[3] = 0;
        param_1[2] = 0;
        v1 = 0xff;
        goto LAB_00428fd4;
      }
      v3 = 2;
    }
    *param_1 = v3;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
  }
  v1 = 0xf;
LAB_00428fd4:
  *(byte  *)(param_1 + 4) = v1;
  return;
}

/* FUN_00429020 @ 0x00429020   (est. sk_f_00429020)
 * Ghidra: void FUN_00429020(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_00429020(void){
  code_t  *pcVar1;
  word_t  v2;
  word_t  v3;
  word_t  v4;
  long  t5;
  word_t  out1;
  word_t  v6;
  word_t  in_x3;
  word_t  ctx;
  word_t  v7;
  word_t  r22;
  word_t  v8;
  word_t  r30;
  sk16_t sv9;
  sk12_t sv10;
  sk12_t sv11;
  
  sv9 = (sk16_t){ sk_h_00351e20(), 0 };
  v4 = sv9.hi;
  sk_h_0001d4f4(0xf,sv9.lo);
  sv9 = (sk16_t){ sk_h_00351a5c(), 0 };
  v8 = sv9.hi >> 0xe;
  v7 = in_x3;
  if (v8 == sv9.lo >> 0xe) {
LAB_00429060:
    v2 = 0x2e;
    v6 = in_x3;
  }
  else {
    sk_h_00463a88();
    sv9 = (sk16_t){ sk_h_002b439c(), 0 };
    t5 = sv9.hi;
    if (sv9.lo == 0x56 && t5 == -0x1f00000000000000) {
      sk_h_003a25d4(t5);
      v6 = v7;
    }
    else {
      v4 = 0x56;
      sk_h_00463540(sv9.lo,t5);
      v3 = sk_h_002a0cf8();
      sk_h_003a25d4(t5);
      v6 = v7;
      if ((v3 & 1) == 0) goto LAB_00429060;
    }
    sk_h_00463a88();
    sk_h_002b439c();
    sk_h_003a25d4(out1);
    sk_h_00463a88();
    v3 = sk_h_002b3b50();
    if (v8 < v3 >> 0xe) {
                    /* WARNING: Does not return */
      pcVar1 = (code_t *)sk_trap(1,0x4292a8);
      (*pcVar1)();
    }
    sk_h_00351100();
    sk_h_002b74c0();
    sk_h_00351a5c();
    v7 = v6;
    sk_h_003a25d4(in_x3);
    v2 = 0x5f;
  }
  sk_h_00351100(v2,0xe100000000000000);
  sv10 = sk_f_004292ac((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
  sk_h_003a25d4(0xe100000000000000);
  if ((sv10.w2 & 0xff) == 1) {
LAB_004291c8:
    sk_h_003a25d4(v6);
  }
  else {
    v8 = sv10.lo >> 0xe;
    if (v8 < ctx >> 0xe) {
                    /* WARNING: Does not return */
      pcVar1 = (code_t *)sk_trap(1,0x429298);
      (*pcVar1)();
    }
    sk_h_003524a4();
    sk_h_00351100();
    sv9 = (sk16_t){ sk_h_002b74c0(), 0 };
    if ((sv9.lo ^ sv9.hi) >> 0xe == 0) {
      sk_h_003a25d4(v7);
      goto LAB_004291c8;
    }
    v2 = v7;
    sv11 = (sk16_t){ sk_h_00460f38(), 0 };
    if ((sv11.w2 & 0xff00) == 0x100) {
      sv9 = (sk16_t){ sk_h_00350944(), 0 };
      v2 = v7;
      sv11 = (sk16_t){ sk_h_00457ae8(), 0 };
    }
    v4 = sv11.lo;
    sk_h_003a25d4(v7);
    if ((sv11.w2 & 0xff) == 1) goto LAB_004291c8;
    if (r22 >> 0xe < v8) {
                    /* WARNING: Does not return */
      pcVar1 = (code_t *)sk_trap(1,0x4292ac);
      (*pcVar1)();
    }
    sk_h_00351100(sv10.lo);
    sk_h_002b74c0();
    sk_h_004630c4();
    sk_h_003a25d4(v6);
    sk_h_00462e9c(1);
    sv9 = sk_f_0041dfe4((word_t)0,(word_t)0,(word_t)0,(word_t)0,(word_t)0);
    v6 = v2;
    if ((sv9.lo ^ sv9.hi) < 0x4000) goto LAB_004291c8;
    sk_h_003535a8();
    sv10 = (sk16_t){ sk_h_00460f38(), 0 };
    if ((sv10.w2 & 0xff00) == 0x100) {
      sk_h_0034d868();
      sv10 = (sk16_t){ sk_h_00457ae8(), 0 };
    }
    v7 = sv10.lo;
    sk_h_003a25d4(v2);
    if ((sv10.w2 & 0xff) != 1) {
      v6 = 0;
      goto LAB_004291dc;
    }
  }
  v4 = 0;
  v7 = 0;
  v6 = 1;
LAB_004291dc:
  sk_h_00351d30(v4,v7,v6,r30);
  return;
}

/* FUN_004292ac @ 0x004292ac   (est. sk_f_004292ac)
 * Ghidra: sk16_t FUN_004292ac(undefined8 param_1,undefined8 param_2,ulong param_3,ulong param_4,undefined8 param_5,             undefined8 param_6)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_004292ac(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6){
  sk16_t sv1;
  word_t  v2;
  word_t  v3;
  word_t  v4;
  sk16_t sv5;
  
  sv1.hi = param_2;
  sv1.lo = param_1;
  v3 = param_3;
  do {
    if ((v3 ^ param_4) < 0x4000) {
      v3 = 0;
      v4 = 1;
LAB_00429378:
      sv5.hi = v4;
      sv5.lo = v3;
      return sv5;
    }
    sv5 = (sk16_t){ sk_h_002b439c(), 0 };
    v4 = sv5.hi;
    if (sv5 == sv1) {
      sk_h_003a25d4(v4);
LAB_00429374:
      v4 = 0;
      goto LAB_00429378;
    }
    v2 = sk_h_002a0cf8(sv5.lo,v4,param_1,param_2,0);
    sk_h_003a25d4(v4);
    if ((v2 & 1) != 0) goto LAB_00429374;
    v3 = sk_h_002b3b50(v3,param_3,param_4,param_5,param_6);
  } while( true );
}

/* FUN_00429398 @ 0x00429398   (est. sk_f_00429398)
 * Ghidra: sk16_t FUN_00429398(ulong param_1,ulong param_2,ulong param_3)
 * 
 * Confidence: medium
 * Notes:  */
sk16_t sk_f_00429398(word_t param_1, word_t param_2, word_t param_3){
  word_t  v1;
  word_t  v2;
  code_t  *pcVar3;
  uint  v4;
  sk16_t sv5;
  
  v1 = param_2 & 0xffffffffffff;
  if ((param_3 & 0x2000000000000000) != 0) {
    v1 = param_3 >> 0x38 & 0xf;
  }
  if (param_1 >> 0xe <= v1 << 2) {
    v4 = (uint )(param_2 >> 0x3b) & 1;
    if ((param_3 & 0x1000000000000000) == 0) {
      v4 = 1;
    }
    v2 = 7;
    if (v4 == 0) {
      v2 = 0xb;
    }
    sv5 = (sk16_t){ sk_h_00460e78(), 0 };
    sk_h_0036b270(param_3);
    return sv5;
  }
                    /* WARNING: Does not return */
  pcVar3 = (code_t *)sk_trap(1,0x429430);
  (*pcVar3)();
}

/* FUN_00429430 @ 0x00429430   (est. sk_f_00429430)
 * Ghidra: void FUN_00429430(undefined8 param_1,undefined8 param_2,ulong param_3,ulong param_4)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_00429430(word_t param_1, word_t param_2, word_t param_3, word_t param_4){
  word_t l_sk_stack;
  code_t  *pcVar1;
  byte  in_flags;
  byte  v2;
  char  cVar3;
  uint  v4;
  word_t  v5;
  word_t  v6;
  word_t  out1;
  long  out1_00;
  long  out1_01;
  long  out1_02;
  word_t  out8;
  word_t  out8_00;
  word_t  out9;
  long  out9_00;
  word_t  *r19;
  word_t  ctx;
  word_t  r21;
  word_t  v7;
  word_t  v8;
  word_t  r23;
  word_t  v9;
  long  unaff_x24;
  long  unaff_x26;
  long  unaff_x27;
  long  unaff_x28;
  word_t  r30;
  sk16_t sv10;
  word_t  in_stack_00000018;
  word_t  in_stack_00000020;
  word_t  in_stack_00000028;
  word_t  in_stack_00000030;
  word_t  in_stack_00000038;
  char  cStack0000000000000040;
  word_t  in_stack_00000048;
  word_t  in_stack_00000050;
  word_t  in_stack_00000070;
  long  in_stack_00000078;
  
  sk_h_00356f9c();
  sk_h_00353b10();
  sk_h_00465cc0();
  if (unaff_x28 == 0) {
    in_stack_00000020 = CONCAT71(in_stack_00000020._1_7_,1);
    sk_h_00462adc(0);
    in_stack_00000048 = 8;
    in_stack_00000050 = 0;
    in_stack_00000028 = out9;
    in_stack_00000030 = out8;
    in_stack_00000038 = param_3;
    l_sk_stack = param_4;
    sk_h_0042ec68((word_t*)l_sk_stack);
    sk_h_00461430((word_t*)l_sk_stack);
    sk_h_0036b270(out1);
  }
  else {
    sk_h_00464550();
    sk_h_00464ef8();
    while( true ) {
      sk_h_0029fb80();
      if (out1_00 == 0) break;
      sk_h_00355a58();
      sk_h_001ae8a8();
      sk_h_00464eec();
      if ((bool )in_flags) {
                    /* WARNING: Does not return */
        pcVar1 = (code_t *)sk_trap(1,0x42997c);
        (*pcVar1)();
      }
      v5 = sk_h_002bc2dc();
      if (((v5 & 1) == 0) &&
         (in_flags = unaff_x27 == 0x5f && unaff_x26 == unaff_x24,
         unaff_x27 != 0x5f || unaff_x26 != unaff_x24)) {
        sk_h_00350914();
        sk_h_00462fac();
        v5 = sk_h_002a0cf8();
        in_flags = unaff_x27 == 0x2d && unaff_x26 == unaff_x24;
        if (((v5 & 1) == 0) && (unaff_x27 != 0x2d || unaff_x26 != unaff_x24)) {
          sv10 = (sk16_t){ sk_h_00350914(), 0 };
          sk_h_00463540(sv10.lo,sv10.hi,0x2d);
          v5 = sk_h_002a0cf8();
          if ((v5 & 1) == 0) {
            sk_h_00350914();
            sk_h_002acbb8();
          }
        }
      }
      sk_h_003a25d4();
    }
    sk_h_003a25d4(out1);
    sk_h_0029d3d8(in_stack_00000070,in_stack_00000078);
    sk_h_00465a04();
    sk_f_00428f4c((word_t*,(word_t)0,(word_t)0)l_sk_stack);
    v5 = l_sk_stack;
    v8 = in_stack_00000038;
    v7 = in_stack_00000030;
    v9 = in_stack_00000028;
    v6 = in_stack_00000020;
    cVar3 = cStack0000000000000040;
    if (cStack0000000000000040 != -1) {
      sk_h_003a25d4((word_t*)l_sk_stack);
      goto LAB_0042977c;
    }
    sk_h_00464180();
    v6 = sk_h_002abcb0();
    if ((v6 & 1) == 0) {
      sk_h_003a25d4((word_t*)l_sk_stack);
    }
    else {
      sk_h_00351b38(2);
      sk_h_000b4660();
      unaff_x26 = sk_h_002a3e64();
      sk_h_00355d90();
      sk_h_003a25d4();
      sk_h_00350a04((word_t*)l_sk_stack);
      sk_f_00428f4c((word_t)0,(word_t)0,(word_t)0);
      sk_h_003a25d4(0xff);
      v7 = in_stack_00000030;
      v8 = in_stack_00000038;
      v9 = in_stack_00000028;
      v6 = in_stack_00000020;
      cVar3 = cStack0000000000000040;
      v5 = l_sk_stack;
      if (cStack0000000000000040 != -1) goto LAB_0042977c;
    }
    v5 = v5 & 0xff;
    sk_h_000b4390();
    cVar3 = sk_f_0041dd0c();
    v9 = r23;
    if (cVar3 != 'C') {
      v5 = sk_h_004634a4();
      v7 = r21;
      v8 = out1;
      v6 = v5 & 0xff | 0x100;
      cVar3 = '\x01';
      goto LAB_0042977c;
    }
    sk_h_000b4390();
    cVar3 = sk_f_0041dbb4();
    if (cVar3 != '&') {
      v5 = sk_h_004634a4();
      v7 = r21;
      v8 = out1;
      v6 = v5 & 0xff;
      cVar3 = '\0';
      goto LAB_0042977c;
    }
    sk_h_000b4390();
    cVar3 = sk_f_0041de64();
    v2 = cVar3 == -0x54;
    if (!(bool )v2) {
      v5 = sk_h_004634a4();
      v7 = r21;
      v8 = out1;
      v6 = v5 & 0xff;
      cVar3 = '\x03';
      goto LAB_0042977c;
    }
    sk_h_00464550();
    sk_h_00464ef8();
    while( true ) {
      sk_h_0029fb80();
      if (out1_01 == 0) break;
      sk_h_00355a58();
      sk_h_001ae8a8();
      sk_h_00464eec();
      if ((bool )v2) {
                    /* WARNING: Does not return */
        pcVar1 = (code_t *)sk_trap(1,0x429980);
        (*pcVar1)();
      }
      v6 = sk_h_002bc2dc();
      if (((v6 & 1) == 0) &&
         (v2 = v5 == 0x5f && unaff_x26 == unaff_x24, v5 != 0x5f || unaff_x26 != unaff_x24))
      {
        sk_h_00350914();
        sk_h_00462fac();
        v6 = sk_h_002a0cf8();
        v2 = v5 == 0x2d && unaff_x26 == unaff_x24;
        if (((v6 & 1) == 0) && (v5 != 0x2d || unaff_x26 != unaff_x24)) {
          sv10 = (sk16_t){ sk_h_00350914(), 0 };
          sk_h_00463540(sv10.lo,sv10.hi,0x2d);
          v6 = sk_h_002a0cf8();
          if ((v6 & 1) == 0) {
            sk_h_00350914();
            sk_h_002acbb8();
          }
        }
      }
      sk_h_003a25d4(unaff_x26);
    }
    sk_h_003a25d4(out1);
    sk_h_0029d3d8(in_stack_00000070,in_stack_00000078);
    sk_h_00465a04();
    sk_h_0036b270((word_t*)l_sk_stack);
    v4 = sk_f_00420770(unaff_x26,(word_t*)l_sk_stack);
    v4 = v4 & 0xff;
    v2 = v4 == 6;
    if (!(bool )v2) {
      sk_h_003a25d4((word_t*)l_sk_stack);
LAB_00429770:
      sk_h_004634a4();
      v7 = r21;
      v8 = out1;
      v6 = (word_t)v4;
      cVar3 = '\v';
      goto LAB_0042977c;
    }
    sv10 = (sk16_t){ sk_h_00464180(), 0 };
    v5 = sk_h_002abcb0(sv10.lo,sv10.hi,unaff_x26,(word_t*)l_sk_stack);
    if ((v5 & 1) == 0) {
      sk_h_003a25d4((word_t*)l_sk_stack);
    }
    else {
      sk_h_00351b38(2);
      sk_h_000b4660();
      unaff_x26 = sk_h_002a3e64();
      sk_h_00355d90();
      sk_h_003a25d4();
      sk_h_00350a04();
      v4 = sk_f_00420770();
      v4 = v4 & 0xff;
      if (v4 != 6) goto LAB_00429770;
      v2 = 1;
    }
    sk_h_00464550();
    sk_h_00464ef8();
    while( true ) {
      sk_h_0029fb80();
      if (out1_02 == 0) break;
      sk_h_00355a58();
      sk_h_001ae8a8();
      sk_h_00464eec();
      if ((bool )v2) {
                    /* WARNING: Does not return */
        pcVar1 = (code_t *)sk_trap(1,0x429984);
        (*pcVar1)();
      }
      v5 = sk_h_002bc2dc();
      if (((v5 & 1) == 0) &&
         (v2 = in_stack_00000078 == 0x5f && unaff_x26 == 6,
         in_stack_00000078 != 0x5f || unaff_x26 != 6)) {
        sk_h_00350914();
        sk_h_00462fac();
        v5 = sk_h_002a0cf8();
        v2 = in_stack_00000078 == 0x2d && unaff_x26 == 6;
        if (((v5 & 1) == 0) && (in_stack_00000078 != 0x2d || unaff_x26 != 6)) {
          sv10 = (sk16_t){ sk_h_00350914(), 0 };
          sk_h_00463540(sv10.lo,sv10.hi,0x2d);
          v5 = sk_h_002a0cf8();
          if ((v5 & 1) == 0) {
            sk_h_00350914();
            sk_h_002acbb8();
          }
        }
      }
      sk_h_003a25d4(unaff_x26);
    }
    sk_h_003a25d4(out1);
    sk_h_0029d3d8(in_stack_00000070,in_stack_00000078);
    sk_h_00465a04();
    v5 = sk_h_002abcb0(0x6e69,0xe200000000000000,unaff_x26,(word_t*)l_sk_stack);
    if ((v5 & 1) == 0) {
      sk_h_003a25d4((word_t*)l_sk_stack);
    }
    else {
      sk_h_00351b38(2);
      sk_h_000b4660();
      sk_h_002a3e64();
      sk_h_00355d90();
      sk_h_003a25d4();
      sk_h_00350a04((long )(word_t*)l_sk_stack + 6);
      sk_f_00424280();
      sk_h_003a25d4(in_stack_00000078);
      if ((word_t)in_stack_00000018._6_2_ != 0x141) {
        sk_h_004634a4();
        v7 = r21;
        v8 = out1;
        v6 = (word_t)in_stack_00000018._6_2_;
        cVar3 = '\n';
        goto LAB_0042977c;
      }
    }
    sk_h_0036b270(out1);
    sk_h_000b4390();
    v4 = sk_h_00415430();
    if ((v4 & 0xff) != 5) {
      sk_h_004634a4();
      v7 = r21;
      v8 = out1;
      v6 = (word_t)(v4 & 0xff);
      cVar3 = '\f';
      goto LAB_0042977c;
    }
    sk_h_0036b270(out1);
    sk_h_000b4390();
    v4 = sk_h_00415b00();
    if ((v4 & 0xff) != 0x12) {
      sk_h_004634a4();
      v7 = r21;
      v8 = out1;
      v6 = (word_t)(v4 & 0xff);
      cVar3 = '\r';
      goto LAB_0042977c;
    }
    sk_h_00462adc(0);
    in_stack_00000020 = out9_00 + 6;
    in_stack_00000028 = out8_00;
    sk_h_003a25e0(out1,2);
    sk_h_000b4390();
    sk_h_002acbb8();
    sk_h_00463514();
    sk_h_002acbb8();
    in_stack_00000030 = in_stack_00000028;
    in_stack_00000028 = in_stack_00000020;
    in_stack_00000020 = CONCAT71(in_stack_00000020._1_7_,1);
    in_stack_00000048 = 0;
    in_stack_00000050 = 0;
    in_stack_00000038 = param_3;
    l_sk_stack = param_4;
    sk_h_0042ec68(ctx,(word_t*)l_sk_stack);
    sk_h_00461430((word_t*)l_sk_stack);
  }
  v7 = r21;
  v8 = out1;
  v9 = 0;
  v6 = 0;
  cVar3 = '\x0e';
LAB_0042977c:
  *r19 = v6;
  r19[1] = v9;
  r19[2] = v7;
  r19[3] = v8;
  *(char  *)(r19 + 4) = cVar3;
  sk_h_00356f80(r30);
  return;
}

/* FUN_00429984 @ 0x00429984   (est. sk_f_00429984)
 * Ghidra: void FUN_00429984(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,                  ulong param_5,ulong param_6,undefined8 param_7,undefined8 param_8)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_00429984(word_t param_1, word_t param_2, word_t param_3, word_t param_4, word_t param_5, word_t param_6, word_t param_7, word_t param_8){
  word_t l_sk_stack;
  char  cVar1;
  code_t  *pcVar2;
  char  cVar3;
  word_t  v4;
  word_t  v5;
  word_t  v6;
  word_t  v7;
  long  out1;
  word_t  v8;
  long  out1_00;
  word_t  v9;
  word_t  v10;
  byte  (*out8) [16];
  word_t  out8_00;
  word_t  out8_01;
  word_t  out8_02;
  word_t  out9;
  long  out9_00;
  long  out9_01;
  long  out9_02;
  word_t  ctx;
  word_t  v11;
  long  unaff_x26;
  word_t  unaff_x28;
  sk16_t sv12;
  sk16_t sv13;
  char  cStack0000000000000048;
  byte l_sk_stack;
  word_t  in_stack_00000050;
  word_t  in_stack_00000058;
  char  in_stack_00000068;
  word_t  in_stack_00000098;
  long  in_stack_000000a0;
  
  sv12 = (sk16_t){ sk_h_00465540(), 0 };
  v7 = sv12.hi;
  v4 = sv12.lo;
  sk_h_00465cc0();
  if (unaff_x28 == 0) {
    l_sk_stack = CONCAT71(l_sk_stack,1);
    sk_h_00462adc(0);
    in_stack_00000050 = out9_00;
    in_stack_00000058 = out8_00;
LAB_00429bc4:
    sk_h_00465df0(8);
    sk_h_0036b270(v7);
    sk_h_0036b270(param_6);
    sk_h_0042ec68((word_t*)l_sk_stack);
    sk_h_00461430((word_t*)l_sk_stack);
  }
  else {
    v6 = param_5 & 0xffffffffffff;
    if ((param_6 & 0x2000000000000000) != 0) {
      v6 = param_6 >> 0x38 & 0xf;
    }
    if (v6 == 0) {
      l_sk_stack = CONCAT71(l_sk_stack,1);
      sk_h_00462adc(0);
      in_stack_00000050 = out9_01;
      in_stack_00000058 = out8_01;
      goto LAB_00429bc4;
    }
    sk_h_0036b270(v7);
    sk_h_0036b270(param_6);
    cVar3 = sk_f_0041dd0c(v4,v7);
    v6 = param_5;
    if (cVar3 != 'C') {
      sk_h_004657d0();
      in_stack_00000058 = 0;
      l_sk_stack = param_5;
      in_stack_00000050 = param_6;
      sk_h_0036b270(param_6);
      while (sk_h_0029fb80(), out1_00 != 0) {
        sk_h_003534e0();
        v6 = sk_h_001ae8a8();
        if ((v6 & 0xff00000000) == 0x100000000) {
                    /* WARNING: Does not return */
          pcVar2 = (code_t *)sk_trap(1,0x429ed8);
          (*pcVar2)();
        }
        v6 = sk_h_002bc2dc();
        if (((v6 & 1) == 0) && (param_5 != 0x5f || unaff_x26 != -0x1f00000000000000)) {
          sk_h_00350738();
          sk_h_00462fac();
          v6 = sk_h_002a0cf8();
          if (((v6 & 1) == 0) && (param_5 != 0x2d || unaff_x26 != -0x1f00000000000000)) {
            sv13 = (sk16_t){ sk_h_00350738(), 0 };
            sk_h_00463540(sv13.lo,sv13.hi,0x2d);
            v6 = sk_h_002a0cf8();
            if ((v6 & 1) == 0) {
              sk_h_00350738();
              sk_h_002acbb8();
            }
          }
        }
        sk_h_003a25d4();
      }
      sk_h_003a25d4(param_6);
      sv13 = (sk16_t){ sk_h_0029d3d8(), 0 };
      v11 = sv13.hi;
      v6 = sv13.lo;
      sk_h_003a25d4(in_stack_000000a0);
      sk_h_003512c0((word_t*)l_sk_stack);
      sk_f_00420618((word_t)0,(word_t)0,(word_t)0);
      cVar1 = cStack0000000000000048;
      if (cStack0000000000000048 != '\x02') {
        sk_h_003a25d4(v11);
LAB_00429d88:
        sk_h_003a25d4(v7);
        sk_h_003a25d4(param_6);
        sk_h_004655f0();
        sv13 = ZEXT516((uint)CONCAT11(cVar1,cVar3) & 0x1ff);
        in_stack_00000068 = '\x01';
        goto LAB_00429c04;
      }
      sv13 = (sk16_t){ sk_h_00464180(), 0 };
      v10 = v11;
      v5 = sk_h_002abcb0(sv13.lo,sv13.hi,v6,v11);
      unaff_x26 = in_stack_000000a0;
      if ((v5 & 1) == 0) {
        sk_h_003a25d4(v11);
      }
      else {
        sk_h_000b4660(2,v6,v11);
        sk_h_002a3e64();
        sk_h_003534e0();
        sk_h_003a25d4(v10);
        sk_h_00350738((word_t*)l_sk_stack);
        sk_f_00420618((word_t)0,(word_t)0,(word_t)0);
        sk_h_003a25d4(in_stack_000000a0);
        cVar1 = cStack0000000000000048;
        if (cStack0000000000000048 != '\x02') goto LAB_00429d88;
      }
    }
    sk_h_003a25e0(param_6,2);
    sk_h_0036b270(v7);
    sk_h_004657d0();
    in_stack_00000058 = 0;
    l_sk_stack = sv12.lo;
    sk_h_0036b270();
    while( true ) {
      sk_h_0029fb80();
      if (out1 == 0) break;
      sk_h_003534e0();
      v5 = sk_h_001ae8a8();
      if ((v5 & 0xff00000000) == 0x100000000) {
                    /* WARNING: Does not return */
        pcVar2 = (code_t *)sk_trap(1,0x429ed4);
        (*pcVar2)();
      }
      v5 = sk_h_002bc2dc();
      if (((v5 & 1) == 0) && (v6 != 0x5f || unaff_x26 != -0x1f00000000000000)) {
        sk_h_00350738();
        sk_h_00462fac();
        v5 = sk_h_002a0cf8();
        if (((v5 & 1) == 0) && (v6 != 0x2d || unaff_x26 != -0x1f00000000000000)) {
          sv13 = (sk16_t){ sk_h_00350738(), 0 };
          sk_h_00463540(sv13.lo,sv13.hi,0x2d);
          v5 = sk_h_002a0cf8();
          if ((v5 & 1) == 0) {
            sk_h_00350738();
            sk_h_002acbb8();
          }
        }
      }
      sk_h_003a25d4(unaff_x26);
    }
    sk_h_003a25d4(v7);
    sv13 = (sk16_t){ sk_h_0029d3d8(), 0 };
    v8 = sv13.hi;
    v6 = sv13.lo;
    sk_h_003a25d4(in_stack_000000a0);
    sv13 = (sk16_t){ sk_h_003512c0(), 0 };
    sk_f_00429ed8(sv13.lo,sv13.hi,param_5,param_6,ctx,param_7,param_8,v4);
    v5 = in_stack_00000058;
    v10 = in_stack_00000050;
    v11 = l_sk_stack;
    if (in_stack_00000068 == -1) {
      sv13 = (sk16_t){ sk_h_00464180(), 0 };
      v9 = v8;
      v5 = sk_h_002abcb0(sv13.lo,sv13.hi,v6,v8);
      v11 = param_8;
      v10 = ctx;
      if ((v5 & 1) == 0) {
        sk_h_003a25d4(v8);
        sk_h_003a25d4(param_6);
        sk_h_00465cf4();
        in_stack_00000068 = -1;
      }
      else {
        sk_h_000b4660(2,v6,v8);
        sk_h_002a3e64();
        sk_h_003534e0();
        sk_h_003a25d4(v9);
        sv13 = (sk16_t){ sk_h_00350738(), 0 };
        sk_f_00429ed8(sv13.lo,sv13.hi,param_5,param_6,ctx,param_7,param_8,v4);
        sk_h_003a25d4(0xff);
        in_stack_00000068 = -1;
        sk_h_003a25d4(param_6);
        sk_h_00465cf4();
      }
    }
    else {
      sk_h_003a25d4(v8);
      sk_h_003a25d4(param_6);
      v6 = unaff_x28;
      unaff_x28 = v5;
    }
    sv13.hi = v10;
    sv13.lo = v11;
    sk_h_003a25d4(param_6);
    sk_h_003a25d4(v7);
    if (in_stack_00000068 != -1) {
      sk_h_003a25d4(v7);
      sk_h_003a25d4(param_6);
      goto LAB_00429c04;
    }
    sk_h_00412d5c(param_7,param_8,param_3,param_4);
    sk_h_003534e0();
    sk_h_00462adc(0);
    l_sk_stack = out9_02 + 6;
    in_stack_00000050 = out8_02;
    sk_h_0036b270(v7);
    sk_h_0036b270(param_6);
    sk_h_002acbb8(v4,v7);
    sk_h_00463bc8();
    sk_h_002acbb8();
    sk_h_002acbb8(param_5,param_6);
    sk_h_00463514();
    sk_h_002acbb8();
    in_stack_00000058 = in_stack_00000050;
    in_stack_00000050 = l_sk_stack;
    l_sk_stack = CONCAT71(l_sk_stack,1);
    sk_h_0042ec68(ctx,(word_t*)l_sk_stack);
    sk_h_00461430((word_t*)l_sk_stack);
  }
  in_stack_00000068 = '\x0e';
  v6 = param_6;
  unaff_x28 = param_5;
  sv13 = sv12;
LAB_00429c04:
  *out8 = sv13;
  *(word_t *)out8[1] = unaff_x28;
  *(word_t *)(out8[1] + 8) = v6;
  out8[2][0] = in_stack_00000068;
  sk_h_00465524(out9);
  return;
}

/* FUN_00429ed8 @ 0x00429ed8   (est. sk_f_00429ed8)
 * Ghidra: void FUN_00429ed8(undefined1 (*param_1) [16],undefined *param_2,long param_3,undefined8 param_4,                  undefined8 param_5)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_00429ed8(byte (*param_1)[16], byte* param_2, long param_3, word_t param_4, word_t param_5){
  code_t  *pcVar1;
  byte  v2;
  bool  b3;
  bool  b4;
  char  cVar5;
  word_t  v6;
  word_t  v7;
  long  t8;
  long  out1;
  long  out1_00;
  long  out1_01;
  long  out1_02;
  long  out1_03;
  long  t9;
  word_t  in_x7;
  byte  *out8;
  byte  *out8_00;
  byte  *out8_01;
  long  out8_02;
  long  out9;
  sk16_t sv10;
  word_t  in_stack_00000000;
  word_t  l_d0;
  word_t  l_c0 [9];
  byte  l_78;
  word_t  l_70;
  word_t  l_68;
  
  if ((((param_2 == (byte  *)0x747069726373 /* "script" */ && param_3 == -0x1a00000000000000) ||
       (v6 = sk_h_004635b8(0x747069726373 /* "script" */,0xe600000000000000), (v6 & 1) != 0)) ||
      (param_2 == (byte *)0x6373 && param_3 == -0x1e00000000000000)) ||
     (v6 = sk_h_004635b8(0x6373,0xe200000000000000), (v6 & 1) != 0)) {
    sk_h_00350560();
    cVar5 = sk_f_0041de64();
    if (cVar5 != -0x54) {
      sk_h_00464258();
      v2 = 2;
      goto LAB_00429ffc;
    }
  }
  else {
    sk_h_004643cc(0);
    if (((param_2 != (byte  *)(out9 + -6) || out1 != param_3) &&
        (v6 = sk_h_004635b8(), (v6 & 1) == 0)) &&
       ((param_2 != (byte *)0x786373 /* "scx" */ || param_3 != -0x1d00000000000000 &&
        (v6 = sk_h_0046357c(0x786373 /* "scx" */), (v6 & 1) == 0)))) {
      if (((param_2 == (byte *)0x6367 && param_3 == -0x1e00000000000000) ||
          (v6 = sk_h_004635b8(0x6367,0xe200000000000000), (v6 & 1) != 0)) ||
         ((param_2 == (byte *)0x636c6172656e6567 /* "generalc" */ && param_3 == -0x10868d90989a8b9f ||
          (v6 = sk_h_004635b8(), (v6 & 1) != 0)))) {
        sk_h_00350560();
        cVar5 = sk_f_0041dbb4();
        if (cVar5 != '&') {
          sk_h_00464258();
          param_1[2][0] = 0;
          return;
        }
        sk_h_00462adc(0);
        sk_h_00465bb0();
        sk_h_00350560();
        sk_h_002acbb8();
        sk_h_00463514();
        sk_h_002acbb8();
        sk_h_00462928();
        l_78 = 0x14;
        goto LAB_00429fb8;
      }
      v2 = param_2 == (byte  *)0x656761 /* "age" */ && param_3 == -0x1d00000000000000;
      if ((param_2 == (byte  *)0x656761 /* "age" */ && param_3 == -0x1d00000000000000) ||
         (v6 = sk_h_0046357c(0x656761 /* "age" */), (v6 & 1) != 0)) {
        sk_h_00350560();
        sk_f_00429020();
        sv10 = (sk16_t){ sk_h_0035292c(), 0 };
        if (!(bool )v2) {
          *param_1 = sv10;
          *(word_t *)param_1[1] = 0;
          *(word_t *)(param_1[1] + 8) = 0;
          v2 = 9;
          goto LAB_00429ffc;
        }
        sk_h_00463e04();
        sk_h_0036b270(param_5);
        sk_h_002a4ab4(0x39);
        sk_h_002acbb8(0xd000000000000018,0x80000000005df900);
        sk_h_00350560();
        sk_h_002acbb8();
        sk_h_002acbb8(0xd00000000000001f,0x80000000005df920);
        sk_h_00462928();
        l_78 = 0x16;
        goto LAB_00429fb8;
      }
      if (param_2 != (byte  *)0x656d616e /* "name" */ || param_3 != -0x1c00000000000000) {
        v6 = sk_h_004635b8(0x656d616e /* "name" */,0xe400000000000000);
        if ((((v6 & 1) == 0) &&
            (param_2 != (byte  *)0x616e || param_3 != -0x1e00000000000000)) &&
           (v6 = sk_h_004635b8(0x616e,0xe200000000000000), (v6 & 1) == 0)) {
          sv10 = (sk16_t){ sk_h_00465468(), 0 };
          b3 = param_2 == (byte  *)(sv10.lo & 0xffffffffffff | 0x7663000000000000);
          b4 = param_3 == sv10.hi;
          v2 = b3 && b4;
          if (!b3 || !b4) {
            v6 = sk_h_004635b8();
            v2 = param_2 == (byte  *)0x766e && param_3 == -0x1e00000000000000;
            if ((((v6 & 1) == 0) &&
                (param_2 != (byte  *)0x766e || param_3 != -0x1e00000000000000)) &&
               (v6 = sk_h_004635b8(0x766e,0xe200000000000000), (v6 & 1) == 0)) {
              sv10 = (sk16_t){ sk_h_00465468(), 0 };
              b3 = param_2 == (byte  *)(sv10.lo & 0xffffffffffff | 0x7463000000000000);
              b4 = param_3 == sv10.hi;
              v2 = b3 && b4;
              if (!b3 || !b4) {
                v6 = sk_h_004635b8();
                v2 = param_2 == (byte  *)0x746e && param_3 == -0x1e00000000000000;
                if ((((v6 & 1) == 0) &&
                    (param_2 != (byte  *)0x746e || param_3 != -0x1e00000000000000)) &&
                   (v6 = sk_h_004635b8(0x746e,0xe200000000000000), (v6 & 1) == 0)) {
                  if ((((param_2 == 0 /*DAT_00636c73*/ && param_3 == -0x1d00000000000000) ||
                       (v6 = sk_h_0046357c(), (v6 & 1) != 0)) ||
                      (sk_h_0046378c(0),
                      param_2 == out8 && out1_00 == param_3)) ||
                     (v6 = sk_h_004635b8(0xd000000000000016), (v6 & 1) != 0)) {
                    *(word_t *)*param_1 = 0;
                  }
                  else {
                    if (((param_2 == 0 /*DAT_00637573*/ && param_3 == -0x1d00000000000000) ||
                        (v6 = sk_h_0046357c(0 /*DAT_00637573*/), (v6 & 1) != 0)) ||
                       ((sk_h_0046378c(0),
                        param_2 == out8_00 && out1_01 == param_3 ||
                        (v6 = sk_h_004635b8(0xd000000000000016), (v6 & 1) != 0)))) {
                      v7 = 1;
                    }
                    else {
                      if (((param_2 != 0 /*DAT_00637473*/ || param_3 != -0x1d00000000000000) &&
                          (v6 = sk_h_0046357c(0 /*DAT_00637473*/), (v6 & 1) == 0)) &&
                         ((sk_h_0046378c(0),
                          param_2 != out8_01 || out1_02 != param_3 &&
                          (v6 = sk_h_004635b8(0xd000000000000016), (v6 & 1) == 0)))) {
                        v2 = param_2 == 0 /*DAT_00636363*/ && param_3 == -0x1d00000000000000;
                        if ((param_2 != 0 /*DAT_00636363*/ || param_3 != -0x1d00000000000000) &&
                           (v6 = sk_h_0046357c(0 /*DAT_00636363*/), (v6 & 1) == 0)) {
                          sk_h_0046378c(0);
                          b3 = param_2 == (byte  *)(out8_02 + 1);
                          v2 = b3 && out1_03 == param_3;
                          if ((!b3 || out1_03 != param_3) &&
                             (v6 = sk_h_004635b8(), (v6 & 1) == 0)) {
                            v2 = param_2 == (byte  *)0x6b6c62 /* "blk" */ &&
                                    param_3 == -0x1d00000000000000;
                            if ((((param_2 != (byte  *)0x6b6c62 /* "blk" */ ||
                                   param_3 != -0x1d00000000000000) &&
                                 (v6 = sk_h_0046357c(0x6b6c62 /* "blk" */), (v6 & 1) == 0)) &&
                                (v2 = param_2 == (byte *)0x6b636f6c62 /* "block" */ &&
                                         param_3 == -0x1b00000000000000,
                                param_2 != (byte *)0x6b636f6c62 /* "block" */ ||
                                param_3 != -0x1b00000000000000)) &&
                               (v6 = sk_h_004635b8(0x6b636f6c62 /* "block" */,0xe500000000000000),
                               (v6 & 1) == 0)) {
                              *(word_t *)(*param_1 + 8) = 0;
                              *(word_t *)*param_1 = 0;
                              *(word_t *)(param_1[1] + 8) = 0;
                              *(word_t *)param_1[1] = 0;
                              v2 = 0xff;
                              goto LAB_00429ffc;
                            }
                            sk_h_00464bb8();
                            while( true ) {
                              sv10 = (sk16_t){ sk_h_0029fb80(), 0 };
                              t9 = sv10.hi;
                              t8 = sv10.lo;
                              if (t9 == 0) break;
                              sk_h_001ae8a8(t8);
                              sk_h_0034ecc8();
                              if ((bool )v2) {
                    /* WARNING: Does not return */
                                pcVar1 = (code_t *)sk_trap(1,0x42a8d0);
                                (*pcVar1)();
                              }
                              v6 = sk_h_002bc2dc();
                              if (((v6 & 1) == 0) &&
                                 (v2 = t8 == 0x5f && t9 == -0x1f00000000000000,
                                 t8 != 0x5f || t9 != -0x1f00000000000000)) {
                                sk_h_00352498();
                                sk_h_00462fac();
                                v6 = sk_h_002a0cf8();
                                v2 = t8 == 0x2d && t9 == -0x1f00000000000000;
                                if (((v6 & 1) == 0) &&
                                   (t8 != 0x2d || t9 != -0x1f00000000000000)) {
                                  sv10 = (sk16_t){ sk_h_00465070(), 0 };
                                  sk_h_00463540(sv10.lo,sv10.hi,0x2d);
                                  v6 = sk_h_002a0cf8();
                                  if ((v6 & 1) == 0) {
                                    sk_h_00465070();
                                    sk_h_002acbb8();
                                  }
                                }
                              }
                              sk_h_003a25d4(t9);
                            }
                            sk_h_003a25d4(param_5);
                            v7 = sk_h_0029d3d8(l_70,l_68);
                            sk_h_003a25d4(l_68);
                            sk_h_0046562c();
                            sk_f_00424280();
                            if ((short)l_c0[0] == 0x141) {
                              sv10 = (sk16_t){ sk_h_00464180(), 0 };
                              v6 = sk_h_002abcb0(sv10.lo,sv10.hi,l_d0,v7);
                              if ((v6 & 1) == 0) {
                                sk_h_003a25d4(v7);
                              }
                              else {
                                sk_h_000b4660(2,l_d0,v7);
                                sk_h_002a3e64();
                                sk_h_004665f4();
                                sk_h_00465070(l_c0);
                                sk_f_00424280();
                                sk_h_003a25d4(0x141);
                                if ((short)l_c0[0] != 0x141) goto LAB_0042a868;
                              }
                              sk_h_00462adc(0);
                              sk_h_00465bb0();
                              sk_h_00350560();
                              sk_h_002acbb8();
                              sk_h_00463514();
                              sk_h_002acbb8();
                              sk_h_00462928();
                              l_78 = 0x15;
                              goto LAB_00429fb8;
                            }
                            sk_h_003a25d4(v7);
LAB_0042a868:
                            *(word_t *)*param_1 = l_c0[0] & 0xffff;
                            *(word_t *)(*param_1 + 8) = 0;
                            *(word_t *)param_1[1] = 0;
                            *(word_t *)(param_1[1] + 8) = 0;
                            v2 = 10;
                            goto LAB_00429ffc;
                          }
                        }
                        sk_h_0036b270(param_5);
                        sk_h_00350560();
                        sk_f_0042a8d0((word_t)0,(word_t)0);
                        cVar5 = sk_h_00466214();
                        if (((bool )v2) || (cVar5 == -1)) {
                          sk_h_00462adc(0);
                          sk_h_00465bb0();
                          sk_h_00350560();
                          sk_h_002acbb8();
                          sk_h_00463514();
                          sk_h_002acbb8();
                          sk_h_00462928();
                          l_78 = 0x19;
                          goto LAB_00429fb8;
                        }
                        sk_h_00464258();
                        v2 = 8;
                        goto LAB_00429ffc;
                      }
                      v7 = 2;
                    }
                    *(word_t *)*param_1 = v7;
                  }
                  *(word_t *)(*param_1 + 8) = param_4;
                  *(word_t *)param_1[1] = param_5;
                  *(word_t *)(param_1[1] + 8) = 0;
                  v2 = 7;
                  goto LAB_0042a264;
                }
              }
              sk_h_00464bb8();
              while( true ) {
                sv10 = (sk16_t){ sk_h_0029fb80(), 0 };
                t9 = sv10.hi;
                t8 = sv10.lo;
                if (t9 == 0) break;
                sk_h_001ae8a8(t8);
                sk_h_0034ecc8();
                if ((bool )v2) {
                    /* WARNING: Does not return */
                  pcVar1 = (code_t *)sk_trap(1,0x42a6b0);
                  (*pcVar1)();
                }
                v6 = sk_h_002bc2dc();
                if (((v6 & 1) == 0) &&
                   (v2 = t8 == 0x5f && t9 == -0x1f00000000000000,
                   t8 != 0x5f || t9 != -0x1f00000000000000)) {
                  sk_h_00352498();
                  sk_h_00462fac();
                  v6 = sk_h_002a0cf8();
                  v2 = t8 == 0x2d && t9 == -0x1f00000000000000;
                  if (((v6 & 1) == 0) && (t8 != 0x2d || t9 != -0x1f00000000000000)) {
                    sv10 = (sk16_t){ sk_h_00465070(), 0 };
                    sk_h_00463540(sv10.lo,sv10.hi,0x2d);
                    v6 = sk_h_002a0cf8();
                    if ((v6 & 1) == 0) {
                      sk_h_00465070();
                      sk_h_002acbb8();
                    }
                  }
                }
                sk_h_003a25d4(t9);
              }
              sk_h_003a25d4(param_5);
              v7 = sk_h_0029d3d8(l_70,l_68);
              sk_h_003a25d4(l_68);
              sk_h_0046562c();
              sk_f_0041efc0();
              if ((char )l_c0[0] == '\x03') {
                sv10 = (sk16_t){ sk_h_00464180(), 0 };
                v6 = sk_h_002abcb0(sv10.lo,sv10.hi,l_d0,v7);
                if ((v6 & 1) == 0) {
                  sk_h_003a25d4(v7);
                }
                else {
                  sk_h_000b4660(2,l_d0,v7);
                  sk_h_002a3e64();
                  sk_h_004665f4();
                  sk_h_00465070(l_c0);
                  sk_f_0041efc0();
                  sk_h_003a25d4(3);
                  if ((char )l_c0[0] != '\x03') goto LAB_0042a4c0;
                }
                sk_h_00462adc(0);
                sk_h_00465bb0();
                sk_h_00350560();
                sk_h_002acbb8();
                sk_h_00463514();
                sk_h_002acbb8();
                sk_h_00462928();
                l_78 = 0x18;
                goto LAB_00429fb8;
              }
              sk_h_003a25d4(v7);
LAB_0042a4c0:
              *(word_t *)*param_1 = l_c0[0] & 0xff;
              *(word_t *)(*param_1 + 8) = 0;
              *(word_t *)param_1[1] = 0;
              *(word_t *)(param_1[1] + 8) = 0;
              v2 = 5;
              goto LAB_00429ffc;
            }
          }
          sk_h_0036b270(param_5);
          sk_h_00350560();
          sk_h_000bb268();
          v7 = sk_h_00351db4();
          if (!(bool )v2) {
            *(word_t *)*param_1 = v7;
            *(word_t *)(*param_1 + 8) = 0;
            *(word_t *)param_1[1] = 0;
            *(word_t *)(param_1[1] + 8) = 0;
            v2 = 6;
LAB_00429ffc:
            param_1[2][0] = v2;
            return;
          }
          sk_h_00462adc(0);
          sk_h_00465bb0();
          sk_h_00350560();
          sk_h_002acbb8();
          sk_h_00463514();
          sk_h_002acbb8();
          sk_h_00462928();
          l_78 = 0x17;
          goto LAB_00429fb8;
        }
      }
      *(word_t *)*param_1 = param_4;
      *(word_t *)(*param_1 + 8) = param_5;
      *(word_t *)param_1[1] = 0;
      *(word_t *)(param_1[1] + 8) = 0;
      v2 = 4;
LAB_0042a264:
      param_1[2][0] = v2;
      sk_h_0036b270(param_5);
      return;
    }
    sk_h_00350560();
    cVar5 = sk_f_0041de64();
    if (cVar5 != -0x54) {
      sk_h_00464258();
      v2 = 3;
      goto LAB_00429ffc;
    }
  }
  sk_h_00462adc(0);
  sk_h_00465bb0();
  sk_h_00350560();
  sk_h_002acbb8();
  sk_h_00463514();
  sk_h_002acbb8();
  sk_h_00462928();
  l_78 = 0x13;
LAB_00429fb8:
  sk_h_0042ec68(l_c0);
  sk_h_00461430(l_c0);
  *(word_t *)*param_1 = in_x7;
  *(word_t *)(*param_1 + 8) = in_stack_00000000;
  *(word_t *)param_1[1] = param_4;
  *(word_t *)(param_1[1] + 8) = param_5;
  param_1[2][0] = 0xe;
  sk_h_0036b270(param_5);
  sk_h_0036b270(in_stack_00000000);
  return;
}

/* FUN_0042a8d0 @ 0x0042a8d0   (est. sk_f_0042a8d0)
 * Ghidra: uint FUN_0042a8d0(ulong param_1,ulong param_2)
 * 
 * Confidence: medium
 * Notes:  */
uint sk_f_0042a8d0(word_t param_1, word_t param_2){
  int iVar1;
  word_t  v2;
  code_t  *pcVar3;
  uint  v4;
  long  t5;
  uint  v6;
  word_t  v7;
  byte  *pbVar8;
  word_t  *pv9;
  uint  v10;
  sk16_t sv11;
  word_t  l_40;
  word_t  l_38;
  
  v7 = param_2 >> 0x38 & 0xf;
  v2 = param_1 & 0xffffffffffff;
  if ((param_2 & 0x2000000000000000) != 0) {
    v2 = v7;
  }
  if (v2 == 0) {
    sk_h_003a25d4(param_2);
    v10 = 1;
    v6 = 0;
    goto LAB_0042aba4;
  }
  if ((param_2 >> 0x3c & 1) == 0) {
    if ((param_2 >> 0x3d & 1) == 0) {
      if ((param_1 >> 0x3c & 1) == 0) {
        sv11 = (sk16_t){ sk_h_002a9ba8(), 0 };
      }
      else {
        sv11.hi = param_1 & 0xffffffffffff;
        sv11.lo = (param_2 & 0xfffffffffffffff) + 0x20;
      }
      t5 = sv11.hi;
      pbVar8 = sv11.lo;
      if (t5 < 1) {
                    /* WARNING: Does not return */
        pcVar3 = (code_t *)sk_trap(1,0x42ac10);
        (*pcVar3)();
      }
      if (*pbVar8 == 0x2b) {
        t5 = t5 + -1;
        if ((t5 != 0) && (pbVar8 == (byte  *)0x0)) {
                    /* WARNING: Does not return */
          pcVar3 = (code_t *)sk_trap(1,0x42ac1c);
          (*pcVar3)();
        }
        v4 = 0;
        v10 = (uint )(t5 == 0);
        if ((t5 == 0) || (pbVar8 == (byte  *)0x0)) goto LAB_0042ab94;
        v4 = 0;
        do {
          pbVar8 = pbVar8 + 1;
          if (((9 < *pbVar8 - 0x30) ||
              (iVar1 = (v4 & 0xff) * 4 + (v4 & 0xff), (iVar1 * 2 & 0xf00U) != 0)) ||
             (v4 = (iVar1 * 2 & 0xffU) + (*pbVar8 - 0x30 & 0xff), (v4 & 0xffffff00) != 0))
          goto LAB_0042ab8c;
          t5 = t5 + -1;
        } while (t5 != 0);
        goto LAB_0042ab84;
      }
      if (*pbVar8 == 0x2d) {
        t5 = t5 + -1;
        if ((t5 != 0) && (pbVar8 == (byte  *)0x0)) {
                    /* WARNING: Does not return */
          pcVar3 = (code_t *)sk_trap(1,0x42ac18);
          (*pcVar3)();
        }
        v4 = 0;
        v10 = (uint )(t5 == 0);
        if ((t5 != 0) && (pbVar8 != (byte  *)0x0)) {
          v4 = 0;
          do {
            pbVar8 = pbVar8 + 1;
            if (((9 < *pbVar8 - 0x30) ||
                (iVar1 = (v4 & 0xff) * 4 + (v4 & 0xff), (iVar1 * 2 & 0xf00U) != 0)) ||
               (v4 = (iVar1 * 2 & 0xffU) - (*pbVar8 - 0x30 & 0xff), (v4 & 0xffffff00) != 0))
            goto LAB_0042ab8c;
            t5 = t5 + -1;
          } while (t5 != 0);
          goto LAB_0042ab84;
        }
      }
      else {
        if (pbVar8 != (byte  *)0x0) {
          v4 = 0;
          do {
            pbVar8 = sv11.lo;
            v10 = *pbVar8 - 0x30;
            if (((9 < v10) ||
                (iVar1 = (v4 & 0xff) * 4 + (v4 & 0xff), (iVar1 * 2 & 0xf00U) != 0)) ||
               (v4 = (iVar1 * 2 & 0xffU) + (v10 & 0xff), (v4 & 0xffffff00) != 0))
            goto LAB_0042ab8c;
            t5 = sv11.hi + -1;
            sv11.hi = t5;
            sv11.lo = pbVar8 + 1;
          } while (t5 != 0);
          goto LAB_0042ab84;
        }
        v10 = 0;
        v4 = 0;
      }
    }
    else {
      l_40 = param_1;
      l_38 = param_2 & 0xffffffffffffff;
      if (v7 == 0) {
                    /* WARNING: Does not return */
        pcVar3 = (code_t *)sk_trap(1,0x42ac14);
        (*pcVar3)();
      }
      v10 = (uint )param_1 & 0xff;
      if (v10 == 0x2b) {
        t5 = v7 - 1;
        if (t5 == 0) {
LAB_0042ab8c:
          v4 = 0;
          v10 = 1;
          goto LAB_0042ab94;
        }
        v4 = 0;
        pbVar8 = (byte  *)((word_t)&l_40 | 1);
        do {
          if (((9 < *pbVar8 - 0x30) ||
              (iVar1 = (v4 & 0xff) * 4 + (v4 & 0xff), (iVar1 * 2 & 0xf00U) != 0)) ||
             (v4 = (iVar1 * 2 & 0xffU) + (*pbVar8 - 0x30 & 0xff), (v4 & 0xffffff00) != 0))
          goto LAB_0042ab8c;
          t5 = t5 + -1;
          pbVar8 = pbVar8 + 1;
        } while (t5 != 0);
      }
      else if (v10 == 0x2d) {
        t5 = v7 - 1;
        if (t5 == 0) goto LAB_0042ab8c;
        v4 = 0;
        pbVar8 = (byte  *)((word_t)&l_40 | 1);
        do {
          if (((9 < *pbVar8 - 0x30) ||
              (iVar1 = (v4 & 0xff) * 4 + (v4 & 0xff), (iVar1 * 2 & 0xf00U) != 0)) ||
             (v4 = (iVar1 * 2 & 0xffU) - (*pbVar8 - 0x30 & 0xff), (v4 & 0xffffff00) != 0))
          goto LAB_0042ab8c;
          t5 = t5 + -1;
          pbVar8 = pbVar8 + 1;
        } while (t5 != 0);
      }
      else {
        v4 = 0;
        pv9 = &l_40;
        do {
          if (((9 < *(byte  *)pv9 - 0x30) ||
              (iVar1 = (v4 & 0xff) * 4 + (v4 & 0xff), (iVar1 * 2 & 0xf00U) != 0)) ||
             (v4 = (iVar1 * 2 & 0xffU) + (*(byte *)pv9 - 0x30 & 0xff),
             (v4 & 0xffffff00) != 0)) goto LAB_0042ab8c;
          v7 = v7 - 1;
          pv9 = (word_t *)((long )pv9 + 1);
        } while (v7 != 0);
      }
LAB_0042ab84:
      v10 = 0;
    }
LAB_0042ab94:
    sk_h_003a25d4(param_2);
  }
  else {
    v4 = sk_h_000b06a4(param_1,param_2,10);
    sk_h_003a25d4(param_2);
    v10 = v4 >> 8 & 0xff;
  }
  v6 = 0;
  if (v10 != 1) {
    v6 = v4;
  }
LAB_0042aba4:
  return v6 & 0xff | v10 << 8;
}

/* FUN_0042ac28 @ 0x0042ac28   (est. sk_f_0042ac28)
 * Ghidra: void FUN_0042ac28(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042ac28(void){
  word_t  r19;
  long  ctx;
  word_t  r21;
  
  sk_h_0008409c();
  sk_h_003a25d4(*(word_t *)(ctx + 0x10));
  *(word_t *)(ctx + 8) = r21;
  *(word_t *)(ctx + 0x10) = r19;
  return;
}

/* FUN_0042aca4 @ 0x0042aca4   (est. sk_f_0042aca4)
 * Ghidra: void FUN_0042aca4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042aca4(void){
  sk_h_00208418(0x685988,1);
  return;
}

/* FUN_0042acc4 @ 0x0042acc4   (est. sk_f_0042acc4)
 * Ghidra: void FUN_0042acc4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042acc4(void){
  sk_h_00208418(0x685e00,1);
  return;
}

/* FUN_0042acd4 @ 0x0042acd4   (est. sk_f_0042acd4)
 * Ghidra: void FUN_0042acd4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042acd4(void){
  sk_h_00208418(0x6854f0,1);
  return;
}

/* FUN_0042ace4 @ 0x0042ace4   (est. sk_f_0042ace4)
 * Ghidra: void FUN_0042ace4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042ace4(void){
  sk_h_00208418(0x685578 /* "xUh" */,1);
  return;
}

/* FUN_0042ad04 @ 0x0042ad04   (est. sk_f_0042ad04)
 * Ghidra: void FUN_0042ad04(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined1 param_4)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042ad04(word_t param_1, word_t param_2, word_t param_3, byte param_4){
  word_t  l_30;
  word_t  l_28;
  word_t  l_20;
  byte  l_18;
  
  l_30 = param_1;
  l_28 = param_2;
  l_20 = param_3;
  l_18 = param_4;
  sk_h_00369efc(&l_30,sk_h_00684e30,0x682558 /* "X%h" */);
  return;
}

/* FUN_0042ad50 @ 0x0042ad50   (est. sk_f_0042ad50)
 * Ghidra: void FUN_0042ad50(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined1 param_4)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042ad50(word_t param_1, word_t param_2, word_t param_3, byte param_4){
  word_t  l_30;
  word_t  l_28;
  word_t  l_20;
  byte  l_18;
  
  l_30 = param_1;
  l_28 = param_2;
  l_20 = param_3;
  l_18 = param_4;
  sk_h_00369efc(&l_30,0x684eb8,0x682568 /* "h%h" */);
  return;
}

/* FUN_0042ad9c @ 0x0042ad9c   (est. sk_f_0042ad9c)
 * Ghidra: void FUN_0042ad9c(undefined1 param_1,undefined8 param_2)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042ad9c(byte param_1, word_t param_2){
  byte  l_20 [8];
  word_t  l_18;
  
  l_20[0] = param_1;
  l_18 = param_2;
  sk_h_00369efc(l_20,0x684fb8,0x6825b8);
  return;
}

/* FUN_0042ade4 @ 0x0042ade4   (est. sk_f_0042ade4)
 * Ghidra: void FUN_0042ade4(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042ade4(void){
  word_t  *ctx;
  word_t  l_40;
  word_t  l_38;
  word_t  l_30;
  word_t  l_28;
  byte  l_20;
  
  l_38 = ctx[1];
  l_40 = *ctx;
  l_28 = ctx[3];
  l_30 = ctx[2];
  l_20 = *(byte  *)(ctx + 4);
  sk_h_00369efc(&l_40,0x685988,0 /*DAT_005a34c8*/);
  return;
}

/* FUN_0042ae34 @ 0x0042ae34   (est. sk_f_0042ae34)
 * Ghidra: void FUN_0042ae34(undefined8 param_1,undefined8 param_2)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042ae34(word_t param_1, word_t param_2){
  word_t  l_20;
  word_t  l_18;
  
  l_20 = param_1;
  l_18 = param_2;
  sk_h_00369efc(&l_20,0x685f28 /* "(_h" */,0 /*DAT_005a37a8*/);
  return;
}

/* FUN_0042ae78 @ 0x0042ae78   (est. sk_f_0042ae78)
 * Ghidra: void FUN_0042ae78(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042ae78(void){
  byte  l_60 [80];
  
  sk_h_00117cc4(l_60);
  sk_h_00369efc(l_60,0x685e00,0 /*DAT_005a3820*/);
  return;
}

/* FUN_0042aec8 @ 0x0042aec8   (est. sk_f_0042aec8)
 * Ghidra: void FUN_0042aec8(void)
 * 
 * Confidence: medium
 * Notes:  */
void sk_f_0042aec8(void){
  word_t  *ctx;
  word_t  l_40;
  word_t  l_38;
  word_t  l_30;
  word_t  l_28;
  word_t  l_20;
  
  l_38 = ctx[1];
  l_40 = *ctx;
  l_28 = ctx[3];
  l_30 = ctx[2];
  l_20 = ctx[4];
  sk_h_00369efc(&l_40,0x6854f0,0x682b70 /* "p+h" */);
  return;
}

/* FUN_004207b0 @ 0x004207b0   (est. sk_unicode_script_code_of)
 * Ghidra: void FUN_004207b0(void) — reads the current Swift small-string tag from
 * registers and returns its numeric code via a flat if/else chain.
 * The decompiler flattened a large string-tag→code lookup; reconstructed
 * faithfully below (priority order preserved).
 * Confidence: low
 * Notes: 153 recognized tags; helper calls (FUN_00462cc0/FUN_004633f4/
 *   FUN_00462dbc...) implement the same small-string equality the direct
 *   comparisons test. */
word_t sk_f_004207b0(const char *tag)
{
    if (sk_smallstr_eq(tag, "adlm")) return 0x0;
    if (sk_smallstr_eq(tag, "ahom")) return 0x1;
    if (sk_smallstr_eq(tag, "hluw")) return 0x2;
    if (sk_smallstr_eq(tag, "arab")) return 0x3;
    if (sk_smallstr_eq(tag, "armn")) return 0x4;
    if (sk_smallstr_eq(tag, "avst")) return 0x5;
    if (sk_smallstr_eq(tag, "bali")) return 0x6;
    if (sk_smallstr_eq(tag, "bamu")) return 0x7;
    if (sk_smallstr_eq(tag, "bass")) return 0x8;
    if (sk_smallstr_eq(tag, "batk")) return 0x9;
    if (sk_smallstr_eq(tag, "beng")) return 0xa;
    if (sk_smallstr_eq(tag, "bopo")) return 0xc;
    if (sk_smallstr_eq(tag, "brah")) return 0xd;
    if (sk_smallstr_eq(tag, "brai")) return 0xe;
    if (sk_smallstr_eq(tag, "bugi")) return 0xf;
    if (sk_smallstr_eq(tag, "buhd")) return 0x10;
    if (sk_smallstr_eq(tag, "cans")) return 0x11;
    if (sk_smallstr_eq(tag, "cari")) return 0x12;
    if (sk_smallstr_eq(tag, "aghb")) return 0x13;
    if (sk_smallstr_eq(tag, "cakm")) return 0x14;
    if (sk_smallstr_eq(tag, "cham")) return 0x15;
    if (sk_smallstr_eq(tag, "cher")) return 0x16;
    if (sk_smallstr_eq(tag, "zyyy")) return 0x18;
    if (sk_smallstr_eq(tag, "copt")) return 0x19;
    if (sk_smallstr_eq(tag, "oldpersi")) return 0x1a;
    if (sk_smallstr_eq(tag, "cprt")) return 0x1b;
    if (sk_smallstr_eq(tag, "cyrl")) return 0x1c;
    if (sk_smallstr_eq(tag, "dsrt")) return 0x1e;
    if (sk_smallstr_eq(tag, "diak")) return 0x20;
    if (sk_smallstr_eq(tag, "dogr")) return 0x21;
    if (sk_smallstr_eq(tag, "dupl")) return 0x22;
    if (sk_smallstr_eq(tag, "egyp")) return 0x23;
    if (sk_smallstr_eq(tag, "elba")) return 0x24;
    if (sk_smallstr_eq(tag, "elym")) return 0x25;
    if (sk_smallstr_eq(tag, "ethi")) return 0x26;
    if (sk_smallstr_eq(tag, "gara")) return 0x27;
    if (sk_smallstr_eq(tag, "geor")) return 0x28;
    if (sk_smallstr_eq(tag, "glag")) return 0x29;
    if (sk_smallstr_eq(tag, "goth")) return 0x2a;
    if (sk_smallstr_eq(tag, "gran")) return 0x2b;
    if (sk_smallstr_eq(tag, "grek")) return 0x2c;
    if (sk_smallstr_eq(tag, "gujr")) return 0x2d;
    if (sk_smallstr_eq(tag, "gong")) return 0x2e;
    if (sk_smallstr_eq(tag, "guru")) return 0x2f;
    if (sk_smallstr_eq(tag, "gurungkh")) return 0x30;
    if (sk_smallstr_eq(tag, "han")) return 0x31;
    if (sk_smallstr_eq(tag, "hang")) return 0x32;
    if (sk_smallstr_eq(tag, "rohg")) return 0x33;
    if (sk_smallstr_eq(tag, "hano")) return 0x34;
    if (sk_smallstr_eq(tag, "hatr")) return 0x35;
    if (sk_smallstr_eq(tag, "hebr")) return 0x36;
    if (sk_smallstr_eq(tag, "armi")) return 0x38;
    if (sk_smallstr_eq(tag, "phli")) return 0x3a;
    if (sk_smallstr_eq(tag, "prti")) return 0x3b;
    if (sk_smallstr_eq(tag, "java")) return 0x3c;
    if (sk_smallstr_eq(tag, "kthi")) return 0x3d;
    if (sk_smallstr_eq(tag, "knda")) return 0x3e;
    if (sk_smallstr_eq(tag, "kana")) return 0x3f;
    if (sk_smallstr_eq(tag, "hrkt")) return 0x40;
    if (sk_smallstr_eq(tag, "kawi")) return 0x41;
    if (sk_smallstr_eq(tag, "kali")) return 0x42;
    if (sk_smallstr_eq(tag, "kits")) return 0x44;
    if (sk_smallstr_eq(tag, "khmr")) return 0x45;
    if (sk_smallstr_eq(tag, "khoj")) return 0x46;
    if (sk_smallstr_eq(tag, "laoo")) return 0x48;
    if (sk_smallstr_eq(tag, "lao")) return 0x49;
    if (sk_smallstr_eq(tag, "lepc")) return 0x4a;
    if (sk_smallstr_eq(tag, "limb")) return 0x4b;
    if (sk_smallstr_eq(tag, "lina")) return 0x4c;
    if (sk_smallstr_eq(tag, "linb")) return 0x4d;
    if (sk_smallstr_eq(tag, "lisu")) return 0x4e;
    if (sk_smallstr_eq(tag, "lyci")) return 0x4f;
    if (sk_smallstr_eq(tag, "lycian")) return 0x50;
    if (sk_smallstr_eq(tag, "krai")) return 0x51;
    if (sk_smallstr_eq(tag, "mahj")) return 0x52;
    if (sk_smallstr_eq(tag, "maka")) return 0x53;
    if (sk_smallstr_eq(tag, "mand")) return 0x55;
    if (sk_smallstr_eq(tag, "marc")) return 0x57;
    if (sk_smallstr_eq(tag, "gonm")) return 0x58;
    if (sk_smallstr_eq(tag, "medf")) return 0x59;
    if (sk_smallstr_eq(tag, "meeteima")) return 0x5a;
    if (sk_smallstr_eq(tag, "merc")) return 0x5c;
    if (sk_smallstr_eq(tag, "mero")) return 0x5d;
    if (sk_smallstr_eq(tag, "phoenici")) return 0x5e;
    if (sk_smallstr_eq(tag, "modi")) return 0x5f;
    if (sk_smallstr_eq(tag, "mroo")) return 0x61;
    if (sk_smallstr_eq(tag, "mult")) return 0x62;
    if (sk_smallstr_eq(tag, "mymr")) return 0x63;
    if (sk_smallstr_eq(tag, "nbat")) return 0x64;
    if (sk_smallstr_eq(tag, "nagm")) return 0x65;
    if (sk_smallstr_eq(tag, "newa")) return 0x67;
    if (sk_smallstr_eq(tag, "talu")) return 0x68;
    if (sk_smallstr_eq(tag, "nshu")) return 0x6a;
    if (sk_smallstr_eq(tag, "hmnp")) return 0x6b;
    if (sk_smallstr_eq(tag, "ogam")) return 0x6c;
    if (sk_smallstr_eq(tag, "olck")) return 0x6d;
    if (sk_smallstr_eq(tag, "hung")) return 0x6e;
    if (sk_smallstr_eq(tag, "ital")) return 0x6f;
    if (sk_smallstr_eq(tag, "narb")) return 0x70;
    if (sk_smallstr_eq(tag, "perm")) return 0x71;
    if (sk_smallstr_eq(tag, "xpeo")) return 0x72;
    if (sk_smallstr_eq(tag, "sogo")) return 0x73;
    if (sk_smallstr_eq(tag, "orkh")) return 0x75;
    if (sk_smallstr_eq(tag, "ougr")) return 0x76;
    if (sk_smallstr_eq(tag, "orya")) return 0x78;
    if (sk_smallstr_eq(tag, "osge")) return 0x79;
    if (sk_smallstr_eq(tag, "osma")) return 0x7a;
    if (sk_smallstr_eq(tag, "hmng")) return 0x7b;
    if (sk_smallstr_eq(tag, "pauc")) return 0x7d;
    if (sk_smallstr_eq(tag, "phag")) return 0x7e;
    if (sk_smallstr_eq(tag, "phnx")) return 0x7f;
    if (sk_smallstr_eq(tag, "phlp")) return 0x80;
    if (sk_smallstr_eq(tag, "rjng")) return 0x81;
    if (sk_smallstr_eq(tag, "runr")) return 0x82;
    if (sk_smallstr_eq(tag, "samr")) return 0x83;
    if (sk_smallstr_eq(tag, "shrd")) return 0x85;
    if (sk_smallstr_eq(tag, "shaw")) return 0x86;
    if (sk_smallstr_eq(tag, "sidd")) return 0x87;
    if (sk_smallstr_eq(tag, "signwrit")) return 0x88;
    if (sk_smallstr_eq(tag, "sinh")) return 0x89;
    if (sk_smallstr_eq(tag, "sogd")) return 0x8a;
    if (sk_smallstr_eq(tag, "oldsogdi")) return 0x8b;
    if (sk_smallstr_eq(tag, "soyo")) return 0x8c;
    if (sk_smallstr_eq(tag, "sund")) return 0x8d;
    if (sk_smallstr_eq(tag, "sunu")) return 0x8e;
    if (sk_smallstr_eq(tag, "sylo")) return 0x8f;
    if (sk_smallstr_eq(tag, "syrc")) return 0x90;
    if (sk_smallstr_eq(tag, "tglg")) return 0x91;
    if (sk_smallstr_eq(tag, "tagb")) return 0x92;
    if (sk_smallstr_eq(tag, "tale")) return 0x93;
    if (sk_smallstr_eq(tag, "lana")) return 0x94;
    if (sk_smallstr_eq(tag, "tavt")) return 0x95;
    if (sk_smallstr_eq(tag, "takr")) return 0x96;
    if (sk_smallstr_eq(tag, "taml")) return 0x97;
    if (sk_smallstr_eq(tag, "tnsa")) return 0x98;
    if (sk_smallstr_eq(tag, "tang")) return 0x99;
    if (sk_smallstr_eq(tag, "telu")) return 0x9a;
    if (sk_smallstr_eq(tag, "thaa")) return 0x9b;
    if (sk_smallstr_eq(tag, "thai")) return 0x9c;
    if (sk_smallstr_eq(tag, "tibt")) return 0x9d;
    if (sk_smallstr_eq(tag, "tfng")) return 0x9e;
    if (sk_smallstr_eq(tag, "tirh")) return 0x9f;
    if (sk_smallstr_eq(tag, "todr")) return 0xa0;
    if (sk_smallstr_eq(tag, "toto")) return 0xa1;
    if (sk_smallstr_eq(tag, "tulutiga")) return 0xa2;
    if (sk_smallstr_eq(tag, "ugar")) return 0xa3;
    if (sk_smallstr_eq(tag, "zzzz")) return 0xa4;
    if (sk_smallstr_eq(tag, "vaii")) return 0xa5;
    if (sk_smallstr_eq(tag, "vith")) return 0xa6;
    if (sk_smallstr_eq(tag, "wcho")) return 0xa7;
    if (sk_smallstr_eq(tag, "yezi")) return 0xa9;
    if (sk_smallstr_eq(tag, "yi")) return 0xaa;
    if (sk_smallstr_eq(tag, "zanb")) return 0xab;
    return 0;
}

/* FUN_00424280 @ 0x00424280   (est. sk_unicode_block_code_of)
 * Ghidra: void FUN_00424280(void) — reads the current Swift small-string tag from
 * registers and returns its numeric code via a flat if/else chain.
 * The decompiler flattened a large string-tag→code lookup; reconstructed
 * faithfully below (priority order preserved).
 * Confidence: low
 * Notes: 129 recognized tags; helper calls (FUN_00462cc0/FUN_004633f4/
 *   FUN_00462dbc...) implement the same small-string equality the direct
 *   comparisons test. */
word_t sk_f_00424280(const char *tag)
{
    if (sk_smallstr_eq(tag, "basiclat")) return 0x0;
    if (sk_smallstr_eq(tag, "ipaext")) return 0x4;
    if (sk_smallstr_eq(tag, "diacriti")) return 0x6;
    if (sk_smallstr_eq(tag, "greekand")) return 0x7;
    if (sk_smallstr_eq(tag, "cjkcompa")) return 0x8;
    if (sk_smallstr_eq(tag, "hebrew")) return 0xb;
    if (sk_smallstr_eq(tag, "syriac")) return 0xd;
    if (sk_smallstr_eq(tag, "thaana")) return 0xf;
    if (sk_smallstr_eq(tag, "mandaic")) return 0x12;
    if (sk_smallstr_eq(tag, "arabicex")) return 0x15;
    if (sk_smallstr_eq(tag, "devanaga")) return 0x16;
    if (sk_smallstr_eq(tag, "gurmukhi")) return 0x18;
    if (sk_smallstr_eq(tag, "gujarati")) return 0x19;
    if (sk_smallstr_eq(tag, "oriya")) return 0x1a;
    if (sk_smallstr_eq(tag, "tamil")) return 0x1b;
    if (sk_smallstr_eq(tag, "telugu")) return 0x1c;
    if (sk_smallstr_eq(tag, "thai")) return 0x20;
    if (sk_smallstr_eq(tag, "myanmar")) return 0x23;
    if (sk_smallstr_eq(tag, "georgian")) return 0x24;
    if (sk_smallstr_eq(tag, "jamo")) return 0x25;
    if (sk_smallstr_eq(tag, "hangulja")) return 0x25;
    if (sk_smallstr_eq(tag, "ethiopic")) return 0x26;
    if (sk_smallstr_eq(tag, "cherokee")) return 0x28;
    if (sk_smallstr_eq(tag, "ocr")) return 0x2a;
    if (sk_smallstr_eq(tag, "rumi")) return 0x2b;
    if (sk_smallstr_eq(tag, "tagalog")) return 0x2c;
    if (sk_smallstr_eq(tag, "hanunoo")) return 0x2d;
    if (sk_smallstr_eq(tag, "buhid")) return 0x2e;
    if (sk_smallstr_eq(tag, "tagbanwa")) return 0x2f;
    if (sk_smallstr_eq(tag, "limbu")) return 0x33;
    if (sk_smallstr_eq(tag, "khmersym")) return 0x36;
    if (sk_smallstr_eq(tag, "taitham")) return 0x38;
    if (sk_smallstr_eq(tag, "batak")) return 0x3c;
    if (sk_smallstr_eq(tag, "lepcha")) return 0x3d;
    if (sk_smallstr_eq(tag, "sundanes")) return 0x41;
    if (sk_smallstr_eq(tag, "vedicext")) return 0x42;
    if (sk_smallstr_eq(tag, "phonetic")) return 0x44;
    if (sk_smallstr_eq(tag, "greekext")) return 0x47;
    if (sk_smallstr_eq(tag, "arrows")) return 0x4e;
    if (sk_smallstr_eq(tag, "controlp")) return 0x51;
    if (sk_smallstr_eq(tag, "boxdrawi")) return 0x54;
    if (sk_smallstr_eq(tag, "geometri")) return 0x56;
    if (sk_smallstr_eq(tag, "dingbats")) return 0x58;
    if (sk_smallstr_eq(tag, "suparrow")) return 0x5a;
    if (sk_smallstr_eq(tag, "braillep")) return 0x5b;
    if (sk_smallstr_eq(tag, "glagolit")) return 0x60;
    if (sk_smallstr_eq(tag, "latinext")) return 0x61;
    if (sk_smallstr_eq(tag, "coptic")) return 0x62;
    if (sk_smallstr_eq(tag, "cjkradic")) return 0x68;
    if (sk_smallstr_eq(tag, "kangxira")) return 0x69;
    if (sk_smallstr_eq(tag, "cjksymbo")) return 0x6b;
    if (sk_smallstr_eq(tag, "hiragana")) return 0x6c;
    if (sk_smallstr_eq(tag, "katakana")) return 0x6d;
    if (sk_smallstr_eq(tag, "bopomofo")) return 0x6e;
    if (sk_smallstr_eq(tag, "compatja")) return 0x6f;
    if (sk_smallstr_eq(tag, "kanbun")) return 0x70;
    if (sk_smallstr_eq(tag, "cjk")) return 0x78;
    if (sk_smallstr_eq(tag, "yisyllab")) return 0x79;
    if (sk_smallstr_eq(tag, "yiradica")) return 0x7a;
    if (sk_smallstr_eq(tag, "lisu")) return 0x7b;
    if (sk_smallstr_eq(tag, "modifier")) return 0x7f;
    if (sk_smallstr_eq(tag, "rejang")) return 0x87;
    if (sk_smallstr_eq(tag, "jamoextb")) return 0x89;
    if (sk_smallstr_eq(tag, "cham")) return 0x8b;
    if (sk_smallstr_eq(tag, "myanmare")) return 0x8c;
    if (sk_smallstr_eq(tag, "meeteima")) return 0x92;
    if (sk_smallstr_eq(tag, "hangulsy")) return 0x93;
    if (sk_smallstr_eq(tag, "highsurr")) return 0x95;
    if (sk_smallstr_eq(tag, "privateu")) return 0x98;
    if (sk_smallstr_eq(tag, "vs")) return 0x9c;
    if (sk_smallstr_eq(tag, "specials")) return 0xa3;
    if (sk_smallstr_eq(tag, "ancients")) return 0xa8;
    if (sk_smallstr_eq(tag, "phaistos")) return 0xa9;
    if (sk_smallstr_eq(tag, "lycian")) return 0xaa;
    if (sk_smallstr_eq(tag, "carian")) return 0xab;
    if (sk_smallstr_eq(tag, "gothic")) return 0xae;
    if (sk_smallstr_eq(tag, "ugaritic")) return 0xb0;
    if (sk_smallstr_eq(tag, "vithkuqi")) return 0xb8;
    if (sk_smallstr_eq(tag, "hatran")) return 0xbf;
    if (sk_smallstr_eq(tag, "phoenici")) return 0xc0;
    if (sk_smallstr_eq(tag, "lydian")) return 0xc1;
    if (sk_smallstr_eq(tag, "manichae")) return 0xc7;
    if (sk_smallstr_eq(tag, "yezidi")) return 0xd0;
    if (sk_smallstr_eq(tag, "smallkan")) return 0xd2;
    if (sk_smallstr_eq(tag, "elymaic")) return 0xd5;
    if (sk_smallstr_eq(tag, "brahmi")) return 0xd6;
    if (sk_smallstr_eq(tag, "kaithi")) return 0xd7;
    if (sk_smallstr_eq(tag, "chakma")) return 0xd9;
    if (sk_smallstr_eq(tag, "mahajani")) return 0xda;
    if (sk_smallstr_eq(tag, "khojki")) return 0xdd;
    if (sk_smallstr_eq(tag, "newa")) return 0xe1;
    if (sk_smallstr_eq(tag, "siddham")) return 0xe3;
    if (sk_smallstr_eq(tag, "modi")) return 0xe4;
    if (sk_smallstr_eq(tag, "mongolia")) return 0xe5;
    if (sk_smallstr_eq(tag, "ahom")) return 0xe7;
    if (sk_smallstr_eq(tag, "dogra")) return 0xe8;
    if (sk_smallstr_eq(tag, "yijing")) return 0xec;
    if (sk_smallstr_eq(tag, "soyombo")) return 0xed;
    if (sk_smallstr_eq(tag, "ucas")) return 0xee;
    if (sk_smallstr_eq(tag, "makasar")) return 0xf4;
    if (sk_smallstr_eq(tag, "lisusup")) return 0xf5;
    if (sk_smallstr_eq(tag, "tamilsup")) return 0xf6;
    if (sk_smallstr_eq(tag, "mro")) return 0xff;
    if (sk_smallstr_eq(tag, "tangsa")) return 0x100;
    if (sk_smallstr_eq(tag, "bassavah")) return 0x101;
    if (sk_smallstr_eq(tag, "miao")) return 0x104;
    if (sk_smallstr_eq(tag, "tangut")) return 0x106;
    if (sk_smallstr_eq(tag, "kanaexte")) return 0x10c;
    if (sk_smallstr_eq(tag, "nushu")) return 0x10e;
    if (sk_smallstr_eq(tag, "duployan")) return 0x10f;
    if (sk_smallstr_eq(tag, "znamenny")) return 0x111;
    if (sk_smallstr_eq(tag, "byzantin")) return 0x112;
    if (sk_smallstr_eq(tag, "counting")) return 0x117;
    if (sk_smallstr_eq(tag, "mathalph")) return 0x118;
    if (sk_smallstr_eq(tag, "superand")) return 0x119;
    if (sk_smallstr_eq(tag, "toto")) return 0x11d;
    if (sk_smallstr_eq(tag, "wancho")) return 0x11e;
    if (sk_smallstr_eq(tag, "mahjongt")) return 0x125;
    if (sk_smallstr_eq(tag, "domino")) return 0x126;
    if (sk_smallstr_eq(tag, "playingc")) return 0x127;
    if (sk_smallstr_eq(tag, "enclosed")) return 0x129;
    if (sk_smallstr_eq(tag, "transpor")) return 0x12d;
    if (sk_smallstr_eq(tag, "alchemic")) return 0x12e;
    if (sk_smallstr_eq(tag, "suppunct")) return 0x131;
    if (sk_smallstr_eq(tag, "chesssym")) return 0x132;
    if (sk_smallstr_eq(tag, "tags")) return 0x13c;
    if (sk_smallstr_eq(tag, "vssup")) return 0x13d;
    if (sk_smallstr_eq(tag, "suppuab")) return 0x13f;
    if (sk_smallstr_eq(tag, "nb")) return 0x140;
    return 0;
}