/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 (Apple seL4-derived) microkernel (GL1),
 * "cL4 (679.100.61)". Ground truth: Ghidra FUN_ names + addresses in program
 * cl4_kernel.raw. Slice 06: 0x2cdaf4-0x2df130 obj/string region.
 * All names are estimates unless string/header-matched. Uses cL4/seL4
 * vocabulary; this region is dominated by the embedded Swift runtime:
 * Unicode scalar / UTF-8 / UTF-16 / UTF-32 decode-encode helpers, String
 * grapheme-breaking, numeric (UInt/Int) string parsing, Character/Unicode
 * scalar classification, and UIntBuffer/byte-collection primitives.
 * Confidence: high where a Swift runtime string matches, medium otherwise.
 *
 * NOTE on calling convention: the decompiler shows most of these as
 * `void FUN(void)` because the iterator/`this` (unaff_x20) and other
 * arguments are passed in registers and not modelled as formal parameters.
 * We model `this` as the explicit first parameter `thisp` where the register
 * usage makes it the object whose fields are read/written, and name incoming
 * register values by their role (tag, scalar, length, ...). Ghidra FUN_ names
 * are kept only in comments.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;

#define CL4_FATAL() __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* Forward declarations of functions reconstructed in this file (address-ordered
 * definitions reference both earlier and later entries). */
unsigned int sk_swift_string_next_scalar(long s1, long s2);
unsigned int sk_swift_hexdigit_value(void);
unsigned long sk_swift_string_next_uint16(word_t thisp);
unsigned int sk_swift_string_segment_equal(word_t seg_lo, word_t seg_hi, void *compare);
unsigned long sk_swift_utf8_width_2(unsigned int w);
unsigned long sk_swift_storebytes_raw(word_t lo, word_t hi, word_t flags, word_t size, long vtable);

/* Out-of-range helpers referenced by this slice (reconstructed by sibling workers). */
extern unsigned long FUN_00002534();
extern unsigned long FUN_000026e8();
extern unsigned long FUN_00019858();
extern unsigned long FUN_0001a1c8();
extern unsigned long FUN_0001d4a0();
extern unsigned long FUN_0001df60();
extern unsigned long FUN_00027754();
extern unsigned long FUN_000651bc();
extern unsigned long FUN_0006782c();
extern unsigned long FUN_0006869c();
extern unsigned long FUN_00068e14();
extern unsigned long FUN_0006a414();
extern unsigned long FUN_0006a4c0();
extern unsigned long FUN_0006b2ec();
extern unsigned long FUN_0006b3f4();
extern unsigned long FUN_0006b42c();
extern unsigned long FUN_0006b6f4();
extern unsigned long FUN_0006e778();
extern unsigned long FUN_0006f768();
extern unsigned long FUN_0006f794();
extern unsigned long FUN_0007767c();
extern unsigned long FUN_00077698();
extern unsigned long FUN_00077894();
extern unsigned long FUN_0007c1a4();
extern unsigned long FUN_0007c1c4();
extern unsigned long FUN_000839f8();
extern unsigned long FUN_00084110();
extern unsigned long FUN_00084174();
extern unsigned long FUN_00084180();
extern unsigned long FUN_000863bc();
extern unsigned long FUN_0008e500();
extern unsigned long FUN_0008e518();
extern unsigned long FUN_0008f6f4();
extern unsigned long FUN_0009e234();
extern unsigned long FUN_000a68f4();
extern unsigned long FUN_000a6e14();
extern unsigned long FUN_000a6f88();
extern unsigned long FUN_000aa4ec();
extern unsigned long FUN_000af308();
extern unsigned long FUN_000b4390();
extern unsigned long FUN_000b43d0();
extern unsigned long FUN_000b43e8();
extern unsigned long FUN_000b4594();
extern unsigned long FUN_000b45b0();
extern unsigned long FUN_000dbdf4();
extern unsigned long FUN_000dbedc();
extern unsigned long FUN_000e15d8();
extern unsigned long FUN_00100c38();
extern unsigned long FUN_00100efc();
extern unsigned long FUN_00106e3c();
extern unsigned long FUN_00117cc4();
extern unsigned long FUN_00117d14();
extern unsigned long FUN_0011d7e8();
extern unsigned long FUN_0014ae44();
extern unsigned long FUN_00167404();
extern unsigned long FUN_0016749c();
extern unsigned long FUN_0019c9bc();
extern unsigned long FUN_0019c9c4();
extern unsigned long FUN_0019c9cc();
extern unsigned long FUN_0019e578();
extern unsigned long FUN_0019fcc8();
extern unsigned long FUN_0019fd10();
extern unsigned long FUN_001a0870();
extern unsigned long FUN_001a0e3c();
extern unsigned long FUN_001a7804();
extern unsigned long FUN_001a84f4();
extern unsigned long FUN_001a8564();
extern unsigned long FUN_001a89a8();
extern unsigned long FUN_001afa84();
extern unsigned long FUN_001afe4c();
extern unsigned long FUN_001d97b4();
extern unsigned long FUN_001e23b0();
extern unsigned long FUN_001e2460();
extern unsigned long FUN_001e4cbc();
extern unsigned long FUN_001e9c00();
extern unsigned long FUN_001fcdbc();
extern unsigned long FUN_002298d4();
extern unsigned long FUN_00229a3c();
extern unsigned long FUN_002514f0();
extern unsigned long FUN_00262e9c();
extern unsigned long FUN_00263360();
extern unsigned long FUN_0026398c();
extern unsigned long FUN_00263e20();
extern unsigned long FUN_00264068();
extern unsigned long FUN_002641a8();
extern unsigned long FUN_00267efc();
extern unsigned long FUN_00268038();
extern unsigned long FUN_002680a8();
extern unsigned long FUN_0026e1d8();
extern unsigned long FUN_00271ce4();
extern unsigned long FUN_00271d24();
extern unsigned long FUN_00271fa0();
extern unsigned long FUN_00272fc0();
extern unsigned long FUN_00273168();
extern unsigned long FUN_002734e4();
extern unsigned long FUN_00294a20();
extern unsigned long FUN_00295134();
extern unsigned long FUN_0029bb80();
extern unsigned long FUN_0029d3d8();
extern unsigned long FUN_0029d56c();
extern unsigned long FUN_0029dac0();
extern unsigned long FUN_0029eb58();
extern unsigned long FUN_0029ec2c();
extern unsigned long FUN_002a0d50();
extern unsigned long FUN_002a1278();
extern unsigned long FUN_002a12b4();
extern unsigned long FUN_002a200c();
extern unsigned long FUN_002a218c();
extern unsigned long FUN_002a2698();
extern unsigned long FUN_002a2748();
extern unsigned long FUN_002a49a8();
extern unsigned long FUN_002a4c98();
extern unsigned long FUN_002a9ba8();
extern unsigned long FUN_002ac260();
extern unsigned long FUN_002b275c();
extern unsigned long FUN_002b279c();
extern unsigned long FUN_002b8904();
extern unsigned long FUN_002b9a04();
extern unsigned long FUN_002b9a60();
extern unsigned long FUN_002bb9b8();
extern unsigned long FUN_002bbd30();
extern unsigned long FUN_002bbe54();
extern unsigned long FUN_002bc55c();
extern unsigned long FUN_002c8568();
extern unsigned long FUN_002c868c();
extern unsigned long FUN_002c8df4();
extern unsigned long FUN_00310954();
extern unsigned long FUN_00310984();
extern unsigned long FUN_003109b4();
extern unsigned long FUN_00310a14();
extern unsigned long FUN_00310a44();
extern unsigned long FUN_00310a74();
extern unsigned long FUN_00310aa4();
extern unsigned long FUN_00310ad4();
extern unsigned long FUN_00310b08();
extern unsigned long FUN_00310d68();
extern unsigned long FUN_00319218();
extern unsigned long FUN_00319688();
extern unsigned long FUN_0031dec4();
extern unsigned long FUN_0031e084();
extern unsigned long FUN_0031e0d4();
extern unsigned long FUN_0031e104();
extern unsigned long FUN_0031e258();
extern unsigned long FUN_00321318();
extern unsigned long FUN_003244ec();
extern unsigned long FUN_0032451c();
extern unsigned long FUN_00324534();
extern unsigned long FUN_00324564();
extern unsigned long FUN_00324594();
extern unsigned long FUN_003245c4();
extern unsigned long FUN_003245f4();
extern unsigned long FUN_00324624();
extern unsigned long FUN_00324654();
extern unsigned long FUN_00343b78();
extern unsigned long FUN_00343bcc();
extern unsigned long FUN_0034418c();
extern unsigned long FUN_00347d60();
extern unsigned long FUN_00347da8();
extern unsigned long FUN_00347f74();
extern unsigned long FUN_00348034();
extern unsigned long FUN_00348074();
extern unsigned long FUN_00348194();
extern unsigned long FUN_00348284();
extern unsigned long FUN_003482c4();
extern unsigned long FUN_0034834c();
extern unsigned long FUN_00348404();
extern unsigned long FUN_00348508();
extern unsigned long FUN_003486b8();
extern unsigned long FUN_00348898();
extern unsigned long FUN_003488bc();
extern unsigned long FUN_00348a34();
extern unsigned long FUN_00348bbc();
extern unsigned long FUN_00348c48();
extern unsigned long FUN_00348c84();
extern unsigned long FUN_00348d7c();
extern unsigned long FUN_00348e18();
extern unsigned long FUN_00348e60();
extern unsigned long FUN_00348fb4();
extern unsigned long FUN_003490b8();
extern unsigned long FUN_003493c4();
extern unsigned long FUN_003495a8();
extern unsigned long FUN_00349630();
extern unsigned long FUN_00349644();
extern unsigned long FUN_003496cc();
extern unsigned long FUN_00349720();
extern unsigned long FUN_0034975c();
extern unsigned long FUN_003497c8();
extern unsigned long FUN_00349844();
extern unsigned long FUN_00349890();
extern unsigned long FUN_003499f0();
extern unsigned long FUN_00349a40();
extern unsigned long FUN_00349b00();
extern unsigned long FUN_00349c44();
extern unsigned long FUN_00349c58();
extern unsigned long FUN_00349c70();
extern unsigned long FUN_00349dfc();
extern unsigned long FUN_0034a148();
extern unsigned long FUN_0034a1f8();
extern unsigned long FUN_0034a2f8();
extern unsigned long FUN_0034a414();
extern unsigned long FUN_0034a464();
extern unsigned long FUN_0034a4bc();
extern unsigned long FUN_0034a4e0();
extern unsigned long FUN_0034a760();
extern unsigned long FUN_0034a798();
extern unsigned long FUN_0034a7ac();
extern unsigned long FUN_0034a834();
extern unsigned long FUN_0034a8cc();
extern unsigned long FUN_0034a9ac();
extern unsigned long FUN_0034aa14();
extern unsigned long FUN_0034aa9c();
extern unsigned long FUN_0034ab20();
extern unsigned long FUN_0034abec();
extern unsigned long FUN_0034acf0();
extern unsigned long FUN_0034ad00();
extern unsigned long FUN_0034af04();
extern unsigned long FUN_0034afc0();
extern unsigned long FUN_0034b178();
extern unsigned long FUN_0034b348();
extern unsigned long FUN_0034b384();
extern unsigned long FUN_0034b3f8();
extern unsigned long FUN_0034b540();
extern unsigned long FUN_0034b758();
extern unsigned long FUN_0034b768();
extern unsigned long FUN_0034b7c8();
extern unsigned long FUN_0034b824();
extern unsigned long FUN_0034b86c();
extern unsigned long FUN_0034b87c();
extern unsigned long FUN_0034b8ec();
extern unsigned long FUN_0034b9f8();
extern unsigned long FUN_0034ba28();
extern unsigned long FUN_0034ba68();
extern unsigned long FUN_0034bd90();
extern unsigned long FUN_0034be54();
extern unsigned long FUN_0034bf2c();
extern unsigned long FUN_0034bfb4();
extern unsigned long FUN_0034c034();
extern unsigned long FUN_0034c094();
extern unsigned long FUN_0034c0a4();
extern unsigned long FUN_0034c0b4();
extern unsigned long FUN_0034c2c8();
extern unsigned long FUN_0034c384();
extern unsigned long FUN_0034c3b4();
extern unsigned long FUN_0034c414();
extern unsigned long FUN_0034c5bc();
extern unsigned long FUN_0034c6d4();
extern unsigned long FUN_0034c754();
extern unsigned long FUN_0034c8b8();
extern unsigned long FUN_0034cbb0();
extern unsigned long FUN_0034cd40();
extern unsigned long FUN_0034cd68();
extern unsigned long FUN_0034cea8();
extern unsigned long FUN_0034d234();
extern unsigned long FUN_0034d444();
extern unsigned long FUN_0034d480();
extern unsigned long FUN_0034d620();
extern unsigned long FUN_0034d744();
extern unsigned long FUN_0034d758();
extern unsigned long FUN_0034d970();
extern unsigned long FUN_0034d9cc();
extern unsigned long FUN_0034dac8();
extern unsigned long FUN_0034dbe8();
extern unsigned long FUN_0034ddd8();
extern unsigned long FUN_0034e054();
extern unsigned long FUN_0034e104();
extern unsigned long FUN_0034e1b0();
extern unsigned long FUN_0034e220();
extern unsigned long FUN_0034e53c();
extern unsigned long FUN_0034e784();
extern unsigned long FUN_0034e7f4();
extern unsigned long FUN_0034e9d4();
extern unsigned long FUN_0034ec48();
extern unsigned long FUN_0034ecc8();
extern unsigned long FUN_0034edd8();
extern unsigned long FUN_0034ee68();
extern unsigned long FUN_0034eef8();
extern unsigned long FUN_0034ef68();
extern unsigned long FUN_0034efc8();
extern unsigned long FUN_0034f1fc();
extern unsigned long FUN_0034f2d4();
extern unsigned long FUN_0034f4f4();
extern unsigned long FUN_0034f584();
extern unsigned long FUN_0034f9d8();
extern unsigned long FUN_0034f9fc();
extern unsigned long FUN_0034fb74();
extern unsigned long FUN_0034fb88();
extern unsigned long FUN_0034fbf4();
extern unsigned long FUN_0034fd5c();
extern unsigned long FUN_0034fdf8();
extern unsigned long FUN_0034fed0();
extern unsigned long FUN_0034ff3c();
extern unsigned long FUN_00350038();
extern unsigned long FUN_0035012c();
extern unsigned long FUN_003501d0();
extern unsigned long FUN_003501e4();
extern unsigned long FUN_003502a8();
extern unsigned long FUN_00350410();
extern unsigned long FUN_0035041c();
extern unsigned long FUN_00350428();
extern unsigned long FUN_00350440();
extern unsigned long FUN_00350464();
extern unsigned long FUN_0035047c();
extern unsigned long FUN_00350488();
extern unsigned long FUN_003504ac();
extern unsigned long FUN_003504b8();
extern unsigned long FUN_003504c4();
extern unsigned long FUN_003504d0();
extern unsigned long FUN_003504e8();
extern unsigned long FUN_003504f4();
extern unsigned long FUN_00350518();
extern unsigned long FUN_00350524();
extern unsigned long FUN_00350530();
extern unsigned long FUN_0035053c();
extern unsigned long FUN_00350548();
extern unsigned long FUN_00350560();
extern unsigned long FUN_003505c4();
extern unsigned long FUN_003505d0();
extern unsigned long FUN_0035060c();
extern unsigned long FUN_00350618();
extern unsigned long FUN_00350624();
extern unsigned long FUN_00350630();
extern unsigned long FUN_00350654();
extern unsigned long FUN_00350720();
extern unsigned long FUN_00350774();
extern unsigned long FUN_00350798();
extern unsigned long FUN_003507c8();
extern unsigned long FUN_003507d4();
extern unsigned long FUN_003507e0();
extern unsigned long FUN_0035084c();
extern unsigned long FUN_003508c0();
extern unsigned long FUN_003508f0();
extern unsigned long FUN_003508fc();
extern unsigned long FUN_00350920();
extern unsigned long FUN_00350950();
extern unsigned long FUN_0035098c();
extern unsigned long FUN_003509a4();
extern unsigned long FUN_003509c8();
extern unsigned long FUN_003509d4();
extern unsigned long FUN_003509e0();
extern unsigned long FUN_00350a10();
extern unsigned long FUN_00350a28();
extern unsigned long FUN_00350a64();
extern unsigned long FUN_00350a94();
extern unsigned long FUN_00350ab8();
extern unsigned long FUN_00350ad0();
extern unsigned long FUN_00350af4();
extern unsigned long FUN_00350b00();
extern unsigned long FUN_00350b24();
extern unsigned long FUN_00350b3c();
extern unsigned long FUN_00350b54();
extern unsigned long FUN_00350b78();
extern unsigned long FUN_00350b90();
extern unsigned long FUN_00350b9c();
extern unsigned long FUN_00350bb4();
extern unsigned long FUN_00350bc0();
extern unsigned long FUN_00350bf0();
extern unsigned long FUN_00350c08();
extern unsigned long FUN_00350c38();
extern unsigned long FUN_00350c68();
extern unsigned long FUN_00350c80();
extern unsigned long FUN_00350c8c();
extern unsigned long FUN_00350d94();
extern unsigned long FUN_00350e14();
extern unsigned long FUN_00350f9c();
extern unsigned long FUN_00351094();
extern unsigned long FUN_003510b8();
extern unsigned long FUN_003510c4();
extern unsigned long FUN_003510d0();
extern unsigned long FUN_003510dc();
extern unsigned long FUN_003510e8();
extern unsigned long FUN_00351118();
extern unsigned long FUN_00351148();
extern unsigned long FUN_00351154();
extern unsigned long FUN_003511a8();
extern unsigned long FUN_003511f0();
extern unsigned long FUN_003511fc();
extern unsigned long FUN_0035125c();
extern unsigned long FUN_00351274();
extern unsigned long FUN_00351280();
extern unsigned long FUN_0035128c();
extern unsigned long FUN_003512f4();
extern unsigned long FUN_00351324();
extern unsigned long FUN_0035133c();
extern unsigned long FUN_00351384();
extern unsigned long FUN_00351488();
extern unsigned long FUN_0035151c();
extern unsigned long FUN_00351660();
extern unsigned long FUN_003516a8();
extern unsigned long FUN_003516cc();
extern unsigned long FUN_0035172c();
extern unsigned long FUN_00351790();
extern unsigned long FUN_0035179c();
extern unsigned long FUN_00351930();
extern unsigned long FUN_003519a8();
extern unsigned long FUN_00351a38();
extern unsigned long FUN_00351a50();
extern unsigned long FUN_00351a5c();
extern unsigned long FUN_00351af8();
extern unsigned long FUN_00351bac();
extern unsigned long FUN_00351be0();
extern unsigned long FUN_00351c34();
extern unsigned long FUN_00351cac();
extern unsigned long FUN_00351cb8();
extern unsigned long FUN_00351cd0();
extern unsigned long FUN_00351d18();
extern unsigned long FUN_00351db4();
extern unsigned long FUN_00351de4();
extern unsigned long FUN_00351e08();
extern unsigned long FUN_00351e60();
extern unsigned long FUN_00351e84();
extern unsigned long FUN_00351ecc();
extern unsigned long FUN_00351ef8();
extern unsigned long FUN_00351f10();
extern unsigned long FUN_00351f88();
extern unsigned long FUN_00351fc0();
extern unsigned long FUN_00352134();
extern unsigned long FUN_00352270();
extern unsigned long FUN_003523f0();
extern unsigned long FUN_00352408();
extern unsigned long FUN_00352450();
extern unsigned long FUN_00352480();
extern unsigned long FUN_003524e0();
extern unsigned long FUN_0035256c();
extern unsigned long FUN_00352578();
extern unsigned long FUN_00352698();
extern unsigned long FUN_003526b8();
extern unsigned long FUN_00352840();
extern unsigned long FUN_00352858();
extern unsigned long FUN_00352864();
extern unsigned long FUN_00352894();
extern unsigned long FUN_003528cc();
extern unsigned long FUN_003529b0();
extern unsigned long FUN_00352a58();
extern unsigned long FUN_00352ae4();
extern unsigned long FUN_00352b08();
extern unsigned long FUN_00352c80();
extern unsigned long FUN_00352ca4();
extern unsigned long FUN_00352cbc();
extern unsigned long FUN_00352dd0();
extern unsigned long FUN_00352ddc();
extern unsigned long FUN_00352ee4();
extern unsigned long FUN_00352efc();
extern unsigned long FUN_00352f48();
extern unsigned long FUN_003530a4();
extern unsigned long FUN_003530bc();
extern unsigned long FUN_003530cc();
extern unsigned long FUN_003530d8();
extern unsigned long FUN_00353130();
extern unsigned long FUN_00353160();
extern unsigned long FUN_003531cc();
extern unsigned long FUN_003531f0();
extern unsigned long FUN_003532b8();
extern unsigned long FUN_00353360();
extern unsigned long FUN_0035359c();
extern unsigned long FUN_0035367c();
extern unsigned long FUN_003536bc();
extern unsigned long FUN_0035378c();
extern unsigned long FUN_003537f0();
extern unsigned long FUN_003539f4();
extern unsigned long FUN_00353a0c();
extern unsigned long FUN_00353b40();
extern unsigned long FUN_00353b4c();
extern unsigned long FUN_00353cb4();
extern unsigned long FUN_00353cd8();
extern unsigned long FUN_00353cf0();
extern unsigned long FUN_00353dac();
extern unsigned long FUN_00353e38();
extern unsigned long FUN_00353e44();
extern unsigned long FUN_00354000();
extern unsigned long FUN_00354010();
extern unsigned long FUN_00354040();
extern unsigned long FUN_00354064();
extern unsigned long FUN_00354410();
extern unsigned long FUN_00354474();
extern unsigned long FUN_003544e0();
extern unsigned long FUN_00354570();
extern unsigned long FUN_0035457c();
extern unsigned long FUN_00354618();
extern unsigned long FUN_003546e4();
extern unsigned long FUN_0035481c();
extern unsigned long FUN_00354998();
extern unsigned long FUN_00354a34();
extern unsigned long FUN_00354a4c();
extern unsigned long FUN_00354a58();
extern unsigned long FUN_00354b08();
extern unsigned long FUN_00354b68();
extern unsigned long FUN_00354c9c();
extern unsigned long FUN_00354d94();
extern unsigned long FUN_00354e0c();
extern unsigned long FUN_00354ef8();
extern unsigned long FUN_00354fac();
extern unsigned long FUN_00354fc0();
extern unsigned long FUN_00355394();
extern unsigned long FUN_00355458();
extern unsigned long FUN_003559a8();
extern unsigned long FUN_00355c28();
extern unsigned long FUN_00355cd4();
extern unsigned long FUN_00355d10();
extern unsigned long FUN_00355d1c();
extern unsigned long FUN_00355db4();
extern unsigned long FUN_00355dc0();
extern unsigned long FUN_00355e8c();
extern unsigned long FUN_00355ea4();
extern unsigned long FUN_00356078();
extern unsigned long FUN_0035609c();
extern unsigned long FUN_00356200();
extern unsigned long FUN_00356304();
extern unsigned long FUN_00356334();
extern unsigned long FUN_0035634c();
extern unsigned long FUN_00356364();
extern unsigned long FUN_003564a4();
extern unsigned long FUN_00356524();
extern unsigned long FUN_00356578();
extern unsigned long FUN_00356664();
extern unsigned long FUN_00356798();
extern unsigned long FUN_003567c8();
extern unsigned long FUN_0035681c();
extern unsigned long FUN_003568c8();
extern unsigned long FUN_00356930();
extern unsigned long FUN_00356988();
extern unsigned long FUN_003569c0();
extern unsigned long FUN_003569cc();
extern unsigned long FUN_003569e4();
extern unsigned long FUN_00356a70();
extern unsigned long FUN_00356b98();
extern unsigned long FUN_00356be0();
extern unsigned long FUN_00356e28();
extern unsigned long FUN_00356fd8();
extern unsigned long FUN_00357170();
extern unsigned long FUN_00357274();
extern unsigned long FUN_00357344();
extern unsigned long FUN_003573e8();
extern unsigned long FUN_0035748c();
extern unsigned long FUN_003575f0();
extern unsigned long FUN_003576a0();
extern unsigned long FUN_003577c0();
extern unsigned long FUN_00357884();
extern unsigned long FUN_003578b4();
extern unsigned long FUN_00357be0();
extern unsigned long FUN_00357c74();
extern unsigned long FUN_00357cb4();
extern unsigned long FUN_00357cfc();
extern unsigned long FUN_00357d64();
extern unsigned long FUN_003580a4();
extern unsigned long FUN_003583dc();
extern unsigned long FUN_0035851c();
extern unsigned long FUN_00358528();
extern unsigned long FUN_003585d0();
extern unsigned long FUN_00358690();
extern unsigned long FUN_00358948();
extern unsigned long FUN_00358b0c();
extern unsigned long FUN_00358b18();
extern unsigned long FUN_00358c68();
extern unsigned long FUN_00358d34();
extern unsigned long FUN_00358fa8();
extern unsigned long FUN_003590ac();
extern unsigned long FUN_003592a0();
extern unsigned long FUN_003593d0();
extern unsigned long FUN_0035955c();
extern unsigned long FUN_0035966c();
extern unsigned long FUN_00359974();
extern unsigned long FUN_00359d64();
extern unsigned long FUN_0035a104();
extern unsigned long FUN_0035a16c();
extern unsigned long FUN_0035a3dc();
extern unsigned long FUN_0035a6b4();
extern unsigned long FUN_0035a70c();
extern unsigned long FUN_0035a784();
extern unsigned long FUN_0035a8d0();
extern unsigned long FUN_0035a9b0();
extern unsigned long FUN_0035abd8();
extern unsigned long FUN_0035ac70();
extern unsigned long FUN_0035b7ac();
extern unsigned long FUN_0035b898();
extern unsigned long FUN_00369340();
extern unsigned long FUN_003698b0();
extern unsigned long FUN_0036a940();
extern unsigned long FUN_0036b118();
extern unsigned long FUN_0036b270();
extern unsigned long FUN_00376820();
extern unsigned long FUN_00377824();
extern unsigned long FUN_00377bec();
extern unsigned long FUN_00377dcc();
extern unsigned long FUN_003a25d4();
extern unsigned long FUN_003a261c();
extern unsigned long FUN_003d3470();
extern unsigned long FUN_003d34b8();
extern unsigned long FUN_003d351c();
extern unsigned long FUN_003d3550();
extern unsigned long FUN_003d36b0();
extern unsigned long FUN_003d3740();
extern unsigned long FUN_003d37a4();
extern unsigned long FUN_003d37f0();
extern unsigned long FUN_003d3b30();
extern unsigned long FUN_003d3b98();
extern unsigned long FUN_003d3c1c();
extern unsigned long FUN_005d0b20();
/* Noreturn Swift runtime fatal-error paths. */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */
extern void sk_fatal_unknown_numeric_type(void) __attribute__((noreturn)); /* FUN_001afa84 */
extern void sk_swift_runtime_fail(void) __attribute__((noreturn)); /* FUN_0011d7e8 */
extern void sk_swift_fatal_oom(void) __attribute__((noreturn)); /* FUN_00356578 */

/* Shared float constant used by the float-conversion helpers. */
extern double sk_double_const_4e7cd0;  /* DAT_004e7cd0 *//* Swift runtime metatype/vtable used by the string builders. */
extern unsigned char sk_swift_vtable_657778[];  /* DAT_00657778 */

/*--------------------------------------------------------------------*/
/* FUN_002bd540 @ 0x002bd540   (est. sk_swift_char_flag_check)
 * Ghidra: void FUN_002bd540(void)
 * Reads a scalar/flag word; if non-zero invokes the string-forward helper.
 * Confidence: low (helpers unresolved).
 */
void sk_swift_char_flag_check(void)
{
    if (FUN_003d37f0() != 0) {
        FUN_001e9c00();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002bd6f4 @ 0x002bd6f4   (est. sk_swift_utf8_lead_width)
 * Ghidra: ulong FUN_002bd6f4(uint param_1)
 * For a leading UTF-8 byte (0xc0+), returns bit 3 of a runtime flag word;
 * continuation bytes (<0xc0) yield 0.
 * Confidence: medium.
 */
unsigned long sk_swift_utf8_lead_width(unsigned int byte)
{
    if (byte < 0xc0) {
        return 0;
    }
    return FUN_003d3550() >> 3 & 0x1fffffff;
}

/*--------------------------------------------------------------------*/
/* FUN_002bd724 @ 0x002bd724   (est. sk_swift_numeric_type_width)
 * Ghidra: int FUN_002bd724(void)
 * Returns 2 - t for a small numeric type tag t; otherwise raises an
 * "Unknown numeric type" fatal error (noreturn).
 * Confidence: medium (Swift Integer metatype helper).
 */
int sk_swift_numeric_type_width(void)
{
    int t = (int)FUN_003d3740();
    if ((t + 1U & 0xff) < 4) {
        return 2 - t;
    }
    FUN_0035ac70(0);   /* s_Unknown_numeric_type_005d0a00 */
    FUN_003559a8();
    FUN_00349c58();
    sk_fatal_unknown_numeric_type();  /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_002bd784 @ 0x002bd784   (est. sk_swift_numeric_dispatch)
 * Ghidra: undefined8 FUN_002bd784(undefined8 param_1)
 * Dispatches on a numeric type tag: tags 0-2 delegate to a cast helper,
 * tag 0xff to the default path, otherwise "Unknown numeric type" fatal.
 * Confidence: medium.
 */
unsigned long sk_swift_numeric_dispatch(unsigned long value)
{
    unsigned long t = FUN_003d3740();
    if (t < 3) {
        return FUN_003d37a4(value);
    }
    if (t != 0xff) {
        FUN_0035ac70(0);   /* s_Unknown_numeric_type_005d0a00 */
        FUN_003559a8();
        FUN_00349c58();
        sk_fatal_unknown_numeric_type();  /* FUN_001afa84 */
    }
    return FUN_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_002bd800 @ 0x002bd800   (est. sk_swift_next_scalar)
 * Ghidra: void FUN_002bd800(void)
 * Advances the byte iterator: prepares the buffer and checks a flag;
 * on set, faults with index-out-of-range.
 * Confidence: low (flag semantics inferred).
 */
unsigned int sk_swift_next_scalar(void)
{
    unsigned int byte = (unsigned int)FUN_0016749c();
    if (FUN_0034ecc8() != 0) {
        FUN_00348898(1);
        FUN_0034a2f8();
        sk_fatal_error(0xb, 2, "", 0, 2, "", 0);  /* FUN_001afe4c */
    }
    return byte;
}

/*--------------------------------------------------------------------*/
/* FUN_002bd848 @ 0x002bd848   (est. sk_swift_buffer_decode)
 * Ghidra: bool FUN_002bd848(void)
 * Decodes one character from the current string/buffer iterator: based on
 * tag bits in the incoming words it selects UTF-16 vs UTF-8 vs tagged-scalar
 * paths, consumes the scalar, and returns whether two width words match.
 * Confidence: low (register-decoded iterator state).
 */
bool sk_swift_buffer_decode(void)
{
    word_t tag = 0, state = 0, scalar = 0; /* incoming iterator words */
    unsigned long out_a = 0, out_b = 0, out_c = 0; /* hidden extra-reg outputs */
    FUN_003504d0();
    FUN_00350624(0xf);
    unsigned long s = FUN_00167404();
    if ((tag >> 0x3c & 1) == 0) {
        scalar = s >> 0x10;
        if ((tag >> 0x3d & 1) != 0) {
            FUN_00354fac();
            goto done;
        }
        if ((state >> 0x3c & 1) != 0) {
            FUN_00356364();
            goto done;
        }
    } else {
        FUN_002a49a8();
    }
    FUN_0007c1c4();
    FUN_002a9ba8();
done:
    FUN_0034b3f8();
    FUN_0034cbb0((scalar + out_a & 0xffffffffffff) << 2);
    return out_b == out_c * 4;
}

/*--------------------------------------------------------------------*/
/* FUN_002bd8cc @ 0x002bd8cc   (est. sk_swift_scalar_ascii_a)
 * Ghidra: bool FUN_002bd8cc(void)
 * True when the next decoded scalar is a single ASCII byte (<0x100).
 * Confidence: medium (thin wrapper over FUN_002bd8f0).
 */
bool sk_swift_scalar_ascii_a(void)
{
    return sk_swift_string_next_scalar(0, 0) < 0x100;
}

/*--------------------------------------------------------------------*/
/* FUN_002bd8d0 @ 0x002bd8d0   (est. sk_swift_scalar_ascii_b)
 * Ghidra: bool FUN_002bd8d0(void)
 * Same as sk_swift_scalar_ascii_a (duplicate/alias entry).
 * Confidence: medium.
 */
bool sk_swift_scalar_ascii_b(void)
{
    return sk_swift_string_next_scalar(0, 0) < 0x100;
}

/*--------------------------------------------------------------------*/
/* FUN_002bd8f0 @ 0x002bd8f0   (est. sk_swift_string_next_scalar)
 * Ghidra: uint FUN_002bd8f0(long param_1,long param_2)
 * Parses the next Unicode scalar from a string segment. Fast path for a
 * native/ASCII string (0xa0d / 0xe2..), otherwise decodes via the buffer
 * iterator; packs (scalar | validity<<8).
 * Confidence: low (Swift String.Character iterator internals).
 */
unsigned int sk_swift_string_next_scalar(long s1, long s2)
{
    unsigned long out_a = 0; /* hidden extra-reg output of FUN_0007c1c4 */
    if (s1 == 0xa0d && s2 == (long)-0x1e00000000000000LL) {
        return 10;
    }
    FUN_003504d0();
    if (((out_a ^ (unsigned long)-1) & 0x6000000000000000) != 0) {
        unsigned char buf[16];
        FUN_0007c1c4();
        unsigned long v = FUN_002a0d50(buf[0], buf[8], 0xa0d, 0xe200000000000000, 0);
        if ((v & 1) != 0) {
            return 10;
        }
    }
    FUN_0007c1c4();
    if ((sk_swift_buffer_decode() & 1) != 0) {
        FUN_0007c1c4();
        unsigned int c = sk_swift_next_scalar();
        if (c < 0x80) {
            FUN_0007c1c4();
            c = sk_swift_next_scalar();
            if (c > 0xff) {
                FUN_003583dc();
                FUN_00348194();
                FUN_003523f0();
                sk_fatal_error(0xb, 2, "", 0, 2, "", 0);
            }
            return c;
        }
    }
    return 1 << 8;
}

/*--------------------------------------------------------------------*/
/* FUN_002bd9ac @ 0x002bd9ac   (est. sk_swift_flag_bit_2d)
 * Ghidra: ulong FUN_002bd9ac(void)
 * Advances the iterator then returns bit 0x2d of a runtime flag word.
 * Confidence: low.
 */
unsigned long sk_swift_flag_bit_2d(void)
{
    sk_swift_next_scalar();
    return FUN_003d36b0() >> 0x2d & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bd9cc @ 0x002bd9cc   (est. sk_swift_iter_type_ok)
 * Ghidra: bool FUN_002bd9cc(void)
 * Prepares the iterator and, if the flag is clear, tests a decoded type tag
 * against a small set (10-13, 0x2028-0x2029, 0x85); else faults.
 * Confidence: low.
 */
bool sk_swift_iter_type_ok(void)
{
    FUN_0016749c();
    int t = FUN_0034ecc8();
    if (t == 0) {
        return (unsigned)(t - 10) < 4 || (unsigned)(t - 0x2028) < 2 || t == 0x85;
    }
    FUN_00348898(1);
    FUN_0034a2f8();
    sk_fatal_error(0xb, 2, "", 0, 2, "", 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002bda40 @ 0x002bda40   (est. sk_swift_type_not_three)
 * Ghidra: bool FUN_002bda40(void)
 * Advances the iterator and reports whether the numeric type width != 3.
 * Confidence: low.
 */
bool sk_swift_type_not_three(void)
{
    sk_swift_next_scalar();
    return sk_swift_numeric_type_width() != 3;
}

/*--------------------------------------------------------------------*/
/* FUN_002bda68 @ 0x002bda68   (est. sk_swift_float_convert_a)
 * Ghidra: undefined4 FUN_002bda68(void)
 * Converts the current string segment to a floating-point value: decodes a
 * scalar, builds a double, and returns 0 unless the value was negative and
 * exactly representable as an integer.
 * Confidence: low (Swift FloatingPoint.parse path).
 */
unsigned int sk_swift_float_convert_a(void)
{
    unsigned int extra = 0; /* hidden extra-reg output of FUN_003590ac */
    FUN_003504d0();
    if ((sk_swift_buffer_decode() & 1) != 0) {
        FUN_0007c1c4();
        sk_swift_next_scalar();
        sk_swift_numeric_dispatch(0);
        double d = (double)FUN_00351db4();
        if (FUN_00351db4() == 0) {
            bool neg = d < sk_double_const_4e7cd0;
            double rd = (double)FUN_003590ac(d != sk_double_const_4e7cd0 && !neg);
            unsigned int res = 0;
            if (neg) {
                res = extra;
            }
            if ((double)(long)rd != rd) {
                return 0;
            }
            return res;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdad4 @ 0x002bdad4   (est. sk_swift_float_convert_b)
 * Ghidra: long FUN_002bdad4(void)
 * Converts the current string segment to a floating-point value; returns the
 * rounded double (or 0 on conversion failure / overflow).
 * Confidence: low.
 */
long sk_swift_float_convert_b(void)
{
    unsigned int extra = 0; /* hidden extra-reg output of FUN_003590ac */
    FUN_003504d0();
    if ((sk_swift_buffer_decode() & 1) != 0) {
        FUN_0007c1c4();
        sk_swift_next_scalar();
        sk_swift_numeric_dispatch(0);
        double d = (double)FUN_00351db4();
        if (FUN_00351db4() == 0) {
            bool neg = d < sk_double_const_4e7cd0;
            double rd = (double)FUN_003590ac(d <= sk_double_const_4e7cd0);
            int fail = extra;
            if (!neg) {
                fail = 1;
            }
            if ((double)(long)rd != rd) {
                fail = 1;
            }
            if (fail != 0) {
                return 0;
            }
            return (long)rd;
        }
    }
    return FUN_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_002bdb90 @ 0x002bdb90   (est. sk_swift_digit_present)
 * Ghidra: bool FUN_002bdb90(void)
 * Decodes the next scalar and reports whether a digit-classification flag
 * was clear (non-digit present).
 * Confidence: low.
 */
bool sk_swift_digit_present(void)
{
    sk_swift_hexdigit_value();
    return FUN_00351db4() != 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdbb0 @ 0x002bdbb0   (est. sk_swift_hexdigit_value)
 * Ghidra: uint FUN_002bdbb0(void)
 * Decodes a single hex digit from the iterator: '0'-'9' -> 0-9,
 * 'a'-'f'/'A'-'F' -> 10-15, else 0.
 * Confidence: medium (clean hex-digit decode).
 */
unsigned int sk_swift_hexdigit_value(void)
{
    FUN_003504d0();
    if ((sk_swift_buffer_decode() & 1) == 0) {
        return 0;
    }
    FUN_0007c1c4();
    int c = sk_swift_next_scalar();
    unsigned int v = c - 0x30;
    if (v > 9) {
        if ((unsigned)(c - 0x41) < 6) {
            v = c - 0x37;
        } else {
            unsigned int u = 0;
            if ((unsigned)(c - 0xff47) > 0xfffffff9U) {
                u = c - 0xff37;
            }
            if ((unsigned)(c - 0xff21) < 6) {
                u = c - 0xff17;
            }
            v = c - 0xff10U;
            if (v > 9) {
                v = u;
            }
            if ((unsigned)(c - 0x61) < 6) {
                v = c - 0x57;
            }
        }
    }
    return v;
}
/*--------------------------------------------------------------------*/
/* FUN_002bdc7c @ 0x002bdc7c   (est. sk_swift_flag_bit_07)
 * Ghidra: ulong FUN_002bdc7c(void)
 * Advances the iterator and returns bit 7 of a runtime flag word.
 * Confidence: low.
 */
unsigned long sk_swift_flag_bit_07(void)
{
    sk_swift_next_scalar();
    return FUN_003d36b0() >> 7 & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdca4 @ 0x002bdca4   (est. sk_swift_string_equal_fwd)
 * Ghidra: void FUN_002bdca4(undefined8 param_1,undefined8 param_2)
 * String-equality fast helper using the forward comparator FUN_0029d56c.
 * Confidence: low.
 */
unsigned int sk_swift_string_equal_fwd(void)
{
    return sk_swift_string_segment_equal(0, 0, FUN_0029d56c);
}

/*--------------------------------------------------------------------*/
/* FUN_002bdcbc @ 0x002bdcbc   (est. sk_swift_string_equal_bwd)
 * Ghidra: void FUN_002bdcbc(undefined8 param_1,undefined8 param_2)
 * String-equality helper using the backward comparator FUN_0029d3d8.
 * Confidence: low.
 */
unsigned int sk_swift_string_equal_bwd(void)
{
    return sk_swift_string_segment_equal(0, 0, FUN_0029d3d8);
}

/*--------------------------------------------------------------------*/
/* FUN_002bdcd4 @ 0x002bdcd4   (est. sk_swift_string_segment_equal)
 * Ghidra: uint sk_swift_string_segment_equal(undefined8 param_1,undefined8 param_2,code *param_3)
 * Compares two string segments via a callback comparator: returns 1 when the
 * two incoming 128-bit segment words match, else 0 unless one is a native
 * string and the other a tag - then falls back to a compare helper.
 * Confidence: low (Swift String equality core).
 */
unsigned int sk_swift_string_segment_equal(word_t seg_lo, word_t seg_hi, void *compare)
{
    unsigned long out = 0;
    FUN_0035098c();
    word_t other_hi = 0, other_lo = 0;  /* 16-byte comparator output (lo, hi) */
    if (other_hi == seg_hi && other_lo == seg_lo) {
        return 1;
    }
    if ((((seg_lo ^ (unsigned long)-1) & 0x6000000000000000) == 0) &&
        ((other_hi & 0x6000000000000000) == 0x6000000000000000)) {
        return 0;
    }
    FUN_000b43d0(other_lo, other_hi, other_lo);
    out = FUN_002a0d50();
    return out & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdd60 @ 0x002bdd60   (est. sk_swift_string_less_equal)
 * Ghidra: uint FUN_002bdd60(void)
 * Compares the current string segment against another: reports
 * less-than-or-equal via the equality/ordering helpers.
 * Confidence: low.
 */
unsigned int sk_swift_string_less_equal(void)
{
    FUN_003504d0();
    if ((sk_swift_buffer_decode() & 1) == 0) {
retry:
        FUN_0007c1c4();
        if ((sk_swift_string_equal_fwd() & 1) == 0) {
            return 0;
        }
        FUN_0007c1c4();
        if ((sk_swift_buffer_decode() & 1) != 0) {
            FUN_0007c1c4();
            FUN_0016749c();
            if (FUN_0034ecc8() == 0) {
                if ((FUN_003d36b0() >> 0xb & 1) != 0) goto lab_dd;
            }
        }
        FUN_0007c1c4();
        if ((sk_swift_string_equal_fwd() & 1) != 0) {
            FUN_0007c1c4();
            return (sk_swift_string_equal_bwd() ^ 1) & 1;
        }
    } else {
        FUN_0007c1c4();
        sk_swift_next_scalar();
        if ((FUN_003d36b0() >> 0x2b & 1) == 0) goto retry;
    }
lab_dd:
    return 1 & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bde1c @ 0x002bde1c   (est. sk_swift_string_not_less)
 * Ghidra: uint FUN_002bde1c(void)
 * Compares the current string segment; returns 1 when not strictly less
 * than the other segment.
 * Confidence: low.
 */
unsigned int sk_swift_string_not_less(void)
{
    FUN_003504d0();
    if ((sk_swift_buffer_decode() & 1) == 0) {
retry:
        FUN_0007c1c4();
        if ((sk_swift_string_equal_fwd() & 1) != 0) {
            FUN_0007c1c4();
            return (sk_swift_string_equal_bwd() ^ 1) & 1;
        }
    } else {
        FUN_0007c1c4();
        sk_swift_next_scalar();
        if ((FUN_003d36b0() >> 0xb & 1) == 0) goto retry;
    }
    return 1 & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bde78 @ 0x002bde78   (est. sk_swift_string_less)
 * Ghidra: uint FUN_002bde78(void)
 * Compares the current string segment against another; returns 1 when it is
 * strictly less than the other segment.
 * Confidence: low.
 */
unsigned int sk_swift_string_less(void)
{
    FUN_003504d0();
    if ((sk_swift_buffer_decode() & 1) == 0) {
retry:
        FUN_0007c1c4();
        if ((sk_swift_string_equal_bwd() & 1) == 0) {
            return 0;
        }
        FUN_0007c1c4();
        if ((sk_swift_buffer_decode() & 1) != 0) {
            FUN_0007c1c4();
            FUN_0016749c();
            if (FUN_0034ecc8() == 0) {
                if ((FUN_003d36b0() >> 0xb & 1) != 0) goto lab_de;
            }
        }
        FUN_0007c1c4();
        if ((sk_swift_string_equal_fwd() & 1) != 0) {
            FUN_0007c1c4();
            return (sk_swift_string_equal_bwd() ^ 1) & 1;
        }
    } else {
        FUN_0007c1c4();
        sk_swift_next_scalar();
        if ((FUN_003d36b0() >> 0x20 & 1) == 0) goto retry;
    }
lab_de:
    return 1 & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdf34 @ 0x002bdf34   (est. sk_swift_is_surrogate_a)
 * Ghidra: bool FUN_002bdf34(void)
 * Advances the iterator, reads a scalar-class word, and reports whether its
 * low 8 bits, masked, equal 0x12 (a Unicode property class).
 * Confidence: low.
 */
bool sk_swift_is_surrogate_a(void)
{
    sk_swift_next_scalar();
    int t = FUN_003d3b30();
    FUN_002bc55c();
    return ((unsigned)(t - 0x12) & 0xfc) == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdf6c @ 0x002bdf6c   (est. sk_swift_flag_bit_21_a)
 * Ghidra: ulong FUN_002bdf6c(void)
 * Advances the iterator and returns bit 0x21 of a runtime flag word.
 * Confidence: low.
 */
unsigned long sk_swift_flag_bit_21_a(void)
{
    sk_swift_next_scalar();
    return FUN_003d36b0() >> 0x21 & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdf70 @ 0x002bdf70   (est. sk_swift_flag_bit_21_b)
 * Ghidra: ulong FUN_002bdf70(void)
 * Duplicate of sk_swift_flag_bit_21_a.
 * Confidence: low.
 */
unsigned long sk_swift_flag_bit_21_b(void)
{
    sk_swift_next_scalar();
    return FUN_003d36b0() >> 0x21 & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdf8c @ 0x002bdf8c   (est. sk_swift_is_combining_mark)
 * Ghidra: bool FUN_002bdf8c(void)
 * Advances the iterator and reports whether the scalar class == 0x13.
 * Confidence: low.
 */
bool sk_swift_is_combining_mark(void)
{
    sk_swift_next_scalar();
    int t = FUN_003d3b30();
    FUN_002bc55c();
    return t == 0x13;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdfc0 @ 0x002bdfc0   (est. sk_swift_is_extend_class)
 * Ghidra: bool FUN_002bdfc0(void)
 * Advances the iterator and reports whether the scalar class is 0xb-0x11.
 * Confidence: low.
 */
bool sk_swift_is_extend_class(void)
{
    sk_swift_next_scalar();
    int t = FUN_003d3b30();
    FUN_002bc55c();
    return (unsigned)(t - 0xb) < 7;
}

/*--------------------------------------------------------------------*/
/* FUN_002bdff8 @ 0x002bdff8   (est. sk_swift_elem_transform_word)
 * Ghidra: ulong FUN_002bdff8(void)
 * Runs an element transform on thisp+0x28 and combines the two resulting
 * flag words into a packed result.
 * Confidence: low (Swift element-transform helper).
 */
unsigned long sk_swift_elem_transform_word(word_t thisp)
{
    unsigned long v = FUN_00263360(thisp + 0x28);
    unsigned long hi = 0;
    if ((v & 0xff000000000000) == 0x1000000000000) {
        unsigned long w = FUN_00264068();
        bool diff = (w & 0xff000000000000) != 0x1000000000000;
        unsigned long lo = 0;
        if (diff) {
            lo = w;
        }
        hi = 0x100000000;
        if (diff) {
            hi = 0;
        }
    }
    return hi | (v & 0xffffffff);
}

/*--------------------------------------------------------------------*/
/* FUN_002be05c @ 0x002be05c   (est. sk_swift_elem_word_store)
 * Ghidra: void FUN_002be05c(undefined4 *param_1)
 * Stores the packed element-transform word into the caller's output.
 * Confidence: low.
 */
void sk_swift_elem_word_store(unsigned int *out)
{
    unsigned long v = sk_swift_elem_transform_word(0);
    *out = (unsigned int)v;
    *(unsigned char *)(out + 1) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002be08c @ 0x002be08c   (est. sk_swift_string_make_native)
 * Ghidra: void FUN_002be08c(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Builds a native String value into param_1 from its three words (start,
 * length, storage), retaining the storage; the tag word is set and the
 * layout matches a Swift small/native String.
 * Confidence: medium (Swift String init).
 */
void sk_swift_string_make_native(word_t *out, word_t start, word_t len, word_t st, word_t storage)
{
    out[0] = start;
    out[1] = len;
    out[2] = st;
    out[3] = storage;
    out[4] = start;
    *(unsigned char *)(out + 5) = 1;
    out[6] = (word_t)sk_swift_vtable_657778;  /* DAT_00657778 */
    *(unsigned char *)(out + 7) = 0;
    *(unsigned long *)((char *)out + 0x3c) = 0x1000000000000;
    FUN_0036b270(storage);
}

/*--------------------------------------------------------------------*/
/* FUN_002be0c0 @ 0x002be0c0   (est. sk_swift_string_make_native_store)
 * Ghidra: void FUN_002be0c0(undefined8 param_1)
 * Materializes a native String from the thisp words and copies 0x44 bytes to
 * the destination.
 * Confidence: medium.
 */
void sk_swift_string_make_native_store(word_t param_1, word_t *thisp)
{
    word_t storage = thisp[3];
    unsigned char tmp[72];
    sk_swift_string_make_native((word_t *)tmp, thisp[0], thisp[1], thisp[2], storage);
    FUN_003a25d4(storage);
    FUN_00117cc4(param_1, tmp, 0x44);
}

/*--------------------------------------------------------------------*/
/* FUN_002be12c @ 0x002be12c   (est. sk_swift_string_next_uint16)
 * Ghidra: ulong FUN_002be12c(void)
 * Advances a UTF-16-ish buffer iterator: resolves the next 16-bit unit via
 * lazy helpers, updates the length word, and returns the packed
 * (value | class<<0x20).
 * Confidence: low (Swift _StringGuts / UTF16 buffer).
 */
unsigned long sk_swift_string_next_uint16(word_t thisp)
{
    unsigned long v = 0;
    unsigned int cls = 1;
    bool fwd;
    if ((*(unsigned char *)(thisp + 0x29) & 1) == 0) {
        unsigned char tmp[16];
        if ((*(unsigned char *)(thisp + 0x2a) & 1) == 0) {
            FUN_00263e20(thisp + 0x28, (void *)0x3244e4, tmp);  /* &LAB_003244e4 */
            fwd = (FUN_00263e20(thisp + 0x28, (void *)0x3244e4, tmp) != 0);
        } else {
            FUN_00262e9c();
            fwd = (FUN_00262e9c() != 0);
        }
        unsigned long w = FUN_00359d64();
        if (!fwd) {
            cls = (unsigned int)(w >> 0x20);
            return (w & 0xffffffff) | (unsigned long)(cls & 0xff) << 0x20;
        }
    }
    *(unsigned char *)(thisp + 0x29) = 1;
    cls = 1;
    if ((*(unsigned char *)(thisp + 0x2a) & 1) == 0) {
        FUN_0026398c(thisp + 0x28);
        unsigned long w = FUN_00359d64();
        if (w != 0) {
            unsigned long lo = (unsigned long)*(unsigned int *)(thisp + 0x5c);
            unsigned char b = *(unsigned char *)(thisp + 0x60);
            cls = (unsigned int)b;
            *(int *)(thisp + 0x5c) = (int)w;
            *(unsigned char *)(thisp + 0x60) = 1;
            if (b == 1) {
                unsigned long s = FUN_002641a8();
                cls = (unsigned int)(unsigned short)(s >> 0x30);
            }
        } else {
            cls = (unsigned int)(w >> 0x20);
            v = w;
        }
    } else {
        v = 0;
    }
    return (v & 0xffffffff) | (unsigned long)(cls & 0xff) << 0x20;
}
/*--------------------------------------------------------------------*/
/* FUN_002be20c @ 0x002be20c   (est. sk_swift_next_uint16_store)
 * Ghidra: void FUN_002be20c(undefined4 *param_1)
 * Stores the packed next-UTF-16-unit word into the caller's output.
 * Confidence: low.
 */
void sk_swift_next_uint16_store(unsigned int *out)
{
    unsigned long v = sk_swift_string_next_uint16(0);
    *out = (unsigned int)v;
    *(unsigned char *)(out + 1) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002be23c @ 0x002be23c   (est. sk_swift_string_make_utf16)
 * Ghidra: void FUN_002be23c(undefined8 *param_1,undefined8 param_2,undefined8 param_3,ulong param_4,ulong param_5)
 * Builds a UTF-16 String value into param_1 from its words (start, length,
 * storage), retaining the storage; mirrors the native-string layout.
 * Confidence: medium (Swift String UTF-16 init).
 */
void sk_swift_string_make_utf16(word_t *out, word_t start, word_t len, word_t st, word_t storage)
{
    out[0] = start;
    out[1] = len;
    word_t keep = st;
    if ((storage & 0x2000000000000000) != 0) {
        keep = storage;
    }
    out[2] = st;
    out[3] = storage;
    out[4] = start;
    *(unsigned short *)(out + 5) = 1;
    *(unsigned char *)((char *)out + 0x2a) = (unsigned char)(keep >> 0x3e) & 1;
    *(unsigned char *)(out + 6) = 1;
    out[7] = (word_t)sk_swift_vtable_657778;  /* DAT_00657778 */
    *(unsigned char *)(out + 8) = 0;
    *(unsigned long *)((char *)out + 0x44) = 0x1000000000000;
    out[10] = (word_t)sk_swift_vtable_657778;
    *(unsigned char *)(out + 0xb) = 0;
    *(unsigned int *)((char *)out + 0x5c) = 0;
    *(unsigned char *)(out + 0xc) = 1;
    FUN_0036b270(storage);
}

/*--------------------------------------------------------------------*/
/* FUN_002be294 @ 0x002be294   (est. sk_swift_string_make_utf16_store)
 * Ghidra: void FUN_002be294(undefined8 param_1)
 * Materializes a UTF-16 String from the thisp words and copies 0x61 bytes to
 * the destination.
 * Confidence: medium.
 */
void sk_swift_string_make_utf16_store(word_t param_1, word_t *thisp)
{
    word_t storage = thisp[3];
    unsigned char tmp[104];
    sk_swift_string_make_utf16((word_t *)tmp, thisp[0], thisp[1], thisp[2], storage);
    FUN_003a25d4(storage);
    FUN_00117cc4(param_1, tmp, 0x61);
}

/*--------------------------------------------------------------------*/
/* FUN_002be300 @ 0x002be300   (est. sk_swift_string_flush_8)
 * Ghidra: void FUN_002be300(void)
 * Flushes a small string buffer: two helper calls.
 * Confidence: low.
 */
void sk_swift_string_flush_8(void)
{
    FUN_00358fa8();
    FUN_001d97b4(0xf);
}

/*--------------------------------------------------------------------*/
/* FUN_002be320 @ 0x002be320   (est. sk_swift_runtime_dispatch_a)
 * Ghidra: void FUN_002be320(void)
 * Delegates to the runtime dispatch helper FUN_003d3b98.
 * Confidence: low.
 */
void sk_swift_runtime_dispatch_a(void)
{
    FUN_003d3b98();
}

/*--------------------------------------------------------------------*/
/* FUN_002be324 @ 0x002be324   (est. sk_swift_runtime_dispatch_b)
 * Ghidra: void FUN_002be324(void)
 * Delegates to the runtime dispatch helper FUN_003d3b98.
 * Confidence: low.
 */
void sk_swift_runtime_dispatch_b(void)
{
    FUN_003d3b98();
}

/*--------------------------------------------------------------------*/
/* FUN_002be338 @ 0x002be338   (est. sk_swift_string_build_hash)
 * Ghidra: void FUN_002be338(void)
 * String hash / byte-collection builder: enters an IRQ-save section, resolves
 * a string with a possible conversion fallback (fatal on error), then copies
 * up to 7 bytes into a growable buffer and restores IRQ state.
 * Confidence: low (register-heavy Swift builder).
 */
void sk_swift_string_build_hash(void)
{
    unsigned long saved_flags = FUN_00357cb4();
    unsigned long buf = FUN_0006b2ec();
    unsigned char byte = 0;
    unsigned char *dst = (unsigned char *)FUN_003d3c1c(buf, &byte);
    bool z = false;
    unsigned long str = 0;
    if (dst == (unsigned char *)0) {
        unsigned long s = FUN_00002534(0x64c108, 0x4be910);  /* s___cstring_0064c108 */
        unsigned long grow = FUN_0036a940(s, 0x21, 7);
        *(unsigned long *)(grow + 0x18) = 0x4baeb8;
        *(unsigned long *)(grow + 0x10) = 0x4baeb0;
        *(unsigned char *)(grow + 0x20) = FUN_003d3b98();
    } else {
        FUN_0034fdf8(dst, byte);
        str = FUN_001a0870(0, 0, 0);
        unsigned long n = (unsigned long)byte;
        if (n != 0) {
            do {
                unsigned char c = *dst;
                unsigned long len = *(unsigned long *)(str + 0x10);
                if (*(unsigned long *)(str + 0x18) >> 1 <= len) {
                    unsigned long grow = FUN_0006b42c();
                    FUN_00350774(grow, len + 1);
                    str = FUN_001a0870();
                }
                *(unsigned long *)(str + 0x10) = len + 1;
                *(unsigned char *)(str + len + 0x20) = c;
                n = n - 1;
                dst = dst + 1;
            } while (n != 0);
            z = true;
        }
    }
    FUN_000651bc(0);
    if (z) {
        FUN_00357c74(str, saved_flags);
        return;
    }
    sk_swift_runtime_fail();  /* FUN_0011d7e8 noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_002be668 @ 0x002be668   (est. sk_swift_get_put_word)
 * Ghidra: void FUN_002be668(void)
 * Fetches a word, stores it into the thisp slots, retains, and advances.
 * Confidence: low.
 */
void sk_swift_get_put_word(word_t *thisp, word_t val)
{
    thisp[0] = FUN_00356988();
    thisp[1] = val;
    FUN_0036b270();
    FUN_0007c1c4();
}

/*--------------------------------------------------------------------*/
/* FUN_002be6ac @ 0x002be6ac   (est. sk_swift_release_store)
 * Ghidra: void FUN_002be6ac(undefined8 *param_1)
 * Releases the word at param_1[0] and stores it through the pointer at
 * param_1[1].
 * Confidence: medium.
 */
void sk_swift_release_store(word_t *pair)
{
    word_t v = pair[0];
    word_t *dst = (word_t *)pair[1];
    FUN_0036b118(v);
    *dst = v;
}

/*--------------------------------------------------------------------*/
/* FUN_002be74c @ 0x002be74c   (est. sk_swift_parse_pair_a)
 * Ghidra: void FUN_002be74c(void)
 * Runs the parse helper FUN_00295134 then the default path FUN_00068e14.
 * Confidence: low.
 */
void sk_swift_parse_pair_a(void)
{
    FUN_00295134();
    FUN_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_002be750 @ 0x002be750   (est. sk_swift_parse_pair_b)
 * Ghidra: void FUN_002be750(void)
 * Same as sk_swift_parse_pair_a.
 * Confidence: low.
 */
void sk_swift_parse_pair_b(void)
{
    FUN_00295134();
    FUN_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_002be780 @ 0x002be780   (est. sk_swift_string_build_tag_66ecd0)
 * Ghidra: void FUN_002be780(undefined8 *param_1,undefined8 param_2)
 * Builds a tagged String value into param_1 from param_2 via the string
 * initializer FUN_002680a8 (metatype 0x66ecd0) and copies the 0x30-ish-byte
 * representation out.
 * Confidence: medium (Swift String init / copy).
 */
void sk_swift_string_build_tag_66ecd0(word_t *out, word_t src)
{
    unsigned char tmp[72];
    FUN_002680a8(&tmp, src, 0x66ecd0);
    __builtin_memcpy(out, tmp, 0x30);
}

/*--------------------------------------------------------------------*/
/* FUN_002be7f8 @ 0x002be7f8   (est. sk_swift_indirect_call)
 * Ghidra: void FUN_002be7f8(undefined8 param_1,undefined8 param_2,code *param_3,undefined8 param_4,undefined8 param_5)
 * Invokes the callback param_3 with param_5.
 * Confidence: medium (thin indirect-call wrapper).
 */
void sk_swift_indirect_call(void *a, void *b, void (*cb)(void *), void *d, void *arg)
{
    (void)a; (void)b; (void)d;
    cb(arg);
}

/*--------------------------------------------------------------------*/
/* FUN_002be830 @ 0x002be830   (est. sk_swift_neg_field)
 * Ghidra: long FUN_002be830(void)
 * Returns the negation of a length field at (buf+0x48).
 * Confidence: low.
 */
long sk_swift_neg_field(void)
{
    long buf = 0;  /* extra output of FUN_00351f10 */
    FUN_00351f10();
    return -*(long *)(buf + 0x48);
}

/*--------------------------------------------------------------------*/
/* FUN_002be884 @ 0x002be884   (est. sk_swift_transform_call)
 * Ghidra: void FUN_002be884(undefined8 param_1,undefined8 param_2,code *param_3,undefined8 param_4)
 * Runs a callback then the element-transform helper FUN_00267efc.
 * Confidence: low.
 */
void sk_swift_transform_call(void *a, void *b, void (*cb)(void), void *arg)
{
    (void)a; (void)b;
    FUN_00352ddc();
    cb();
    FUN_00355c28();
    FUN_00267efc(0, 0, arg);
}

/*--------------------------------------------------------------------*/
/* FUN_002be908 @ 0x002be908   (est. sk_swift_divide_checked)
 * Ghidra: void FUN_002be908(void)
 * Signed divide of (divisor-related) words with overflow/divide-by-zero
 * trapping: computes (a - b) / c and stores the quotient, faulting on
 * INT64_MIN / -1 or zero divisor.
 * Confidence: low (Swift integer division helper).
 */
void sk_swift_divide_checked(word_t *thisp)
{
    long out = 0;  /* destination slot */
    long *plVar2 = (long *)FUN_00354010();
    long d = *(long *)(0 + 0x48);
    if (d == 0) {
        FUN_00348074(1);
    } else {
        if (d != -1 || *plVar2 - *thisp != (long)-0x8000000000000000LL) {
            long q = 0;
            if (d != 0) {
                q = (*plVar2 - *thisp) / d;
            }
            *(long *)out = q;
            return;
        }
        FUN_0034834c(1);
    }
    FUN_00351be0();
    sk_fatal_error(0xb, 2, "", 0, 2, "", 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002be9c8 @ 0x002be9c8   (est. sk_swift_string_build_tag_66ed58)
 * Ghidra: void FUN_002be9c8(undefined8 *param_1,undefined8 param_2)
 * Builds a tagged String value into param_1 from param_2 via FUN_002680a8
 * (metatype 0x66ed58) and copies the representation out.
 * Confidence: medium (Swift String init / copy).
 */
void sk_swift_string_build_tag_66ed58(word_t *out, word_t src)
{
    unsigned char tmp[72];
    FUN_002680a8(&tmp, src, 0x66ed58);
    __builtin_memcpy(out, tmp, 0x30);
}
/*--------------------------------------------------------------------*/
/* FUN_002bec40 @ 0x002bec40   (est. sk_swift_string_build_676400)
 * Ghidra: void FUN_002bec40(undefined8 *param_1)
 * Builds a tagged String value into param_1 from the thisp word via
 * FUN_00268038 (metatype 0x676400) and copies the representation out.
 * Confidence: medium (Swift String init / copy).
 */
void sk_swift_string_build_676400(word_t *out, word_t *thisp)
{
    unsigned char tmp[72];
    FUN_00268038(&tmp, thisp[0], 0x676400);
    __builtin_memcpy(out, tmp, 0x30);
}

/*--------------------------------------------------------------------*/
/* FUN_002bece4 @ 0x002bece4   (est. sk_swift_string_build_676480)
 * Ghidra: void FUN_002bece4(undefined8 *param_1)
 * Builds a tagged String value into param_1 from the thisp word via
 * FUN_00268038 (metatype 0x676480) and copies the representation out.
 * Confidence: medium (Swift String init / copy).
 */
void sk_swift_string_build_676480(word_t *out, word_t *thisp)
{
    unsigned char tmp[72];
    FUN_00268038(&tmp, thisp[0], 0x676480);
    __builtin_memcpy(out, tmp, 0x30);
}

/*--------------------------------------------------------------------*/
/* FUN_002bed30 @ 0x002bed30   (est. sk_swift_string_index_checked)
 * Ghidra: ulong FUN_002bed30(undefined8 param_1,ulong param_2,long param_3,ulong param_4,undefined8 param_5)
 * Bounds-checks a string index: for a negative step the index faults into a
 * 0x40-width path; otherwise validates lo <= i < base + size*step and returns
 * the index (or takes the failure path).
 * Confidence: low (Swift String index arithmetic).
 */
unsigned long sk_swift_string_index_checked(word_t a, unsigned long lo, long step, unsigned long idx, word_t b)
{
    if (step < 0) {
        FUN_003488bc(1);
        FUN_0034a834();
        unsigned char v[16];
        FUN_00356524();
        return sk_swift_storebytes_raw(0, 0, 0, 0x40, 0);
    }
    if ((lo <= idx) &&
        (FUN_003509c8(b),
         idx < (unsigned long)(0 + *(long *)(0 + 0x48) * step))) {
        FUN_0035b898(idx);
        return idx;
    }
    FUN_0035b7ac(idx);
    return idx;
}

/*--------------------------------------------------------------------*/
/* FUN_002bedcc @ 0x002bedcc   (est. sk_swift_storebytes_raw)
 * Ghidra: void FUN_002bedcc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,long param_5)
 * storeBytes(to: raw pointer): validates the destination alignment against
 * the value's flags, faults on a misaligned raw pointer, otherwise invokes
 * the store function and runs the copy epilogue.
 * Confidence: low (Swift UnsafeRawPointer.storeBytes core).
 */
unsigned long sk_swift_storebytes_raw(word_t lo, word_t hi, word_t flags, word_t size, long vtable)
{
    long t = *(long *)(vtable + -8);
    FUN_0006b42c();
    if ((*(unsigned int *)(t + 0x50) & (unsigned int)size + (unsigned int)hi & 0xff) != 0) {
        sk_fatal_error(0xb, 2, "storeBytes(to:as:)", 0x12, 2,
                       "Swift.UnsafeRawPointer", 0x16, 2, 0x24, 1);
    }
    (*(void (**)(void))(t + 0x10))();
    FUN_0006b42c();
    FUN_002514f0(0, FUN_0034418c, 0, vtable, 0x674330, 0x67b148, 0x66d208);
    (*(void (**)(void))(t + 8))();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002befb4 @ 0x002befb4   (est. sk_swift_negative_not_representable)
 * Ghidra: void FUN_002befb4(undefined8 param_1,long param_2,long param_3,long param_4)
 * Copies a byte range; if the type's size field is negative (a fixed-width
 * negative value), raises a "negative value is not representable" fatal.
 * Confidence: medium (Swift integer coercion trap).
 */
void sk_swift_negative_not_representable(word_t a, long dst, long size, long vtable)
{
    long sz = *(long *)(*(long *)(vtable + -8) + 0x40);
    if (sz >= 0) {
        FUN_00117cc4(dst + size, a, sz);
        return;
    }
    sk_fatal_error(0xb, 2, "Negative value is not representable", 0x23, 2,
                   "Swift.Integers", 0x14, 2, 0xcf8, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002bfff0 @ 0x002bfff0   (est. sk_swift_fatal_overflow_a)
 * Ghidra: void FUN_002bfff0(void)
 * Overflow/precondition failure: fault unconditionally.
 * Confidence: high (noreturn fatal wrapper).
 */
void sk_swift_fatal_overflow_a(void)
{
    FUN_00348404(1);
    FUN_00351be0();
    sk_fatal_error(0xb, 2, "", 0, 2, "", 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002c002c @ 0x002c002c   (est. sk_swift_fatal_overflow_b)
 * Ghidra: void FUN_002c002c(void)
 * Overflow/precondition failure: fault unconditionally.
 * Confidence: high (noreturn fatal wrapper).
 */
void sk_swift_fatal_overflow_b(void)
{
    FUN_00348074(1);
    FUN_00351be0();
    sk_fatal_error(0xb, 2, "", 0, 2, "", 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002c0054 @ 0x002c0054   (est. sk_swift_lead_bit_not)
 * Ghidra: uint FUN_002c0054(uint param_1)
 * Returns bit 7 of the word inverted (continuation-byte predicate helper).
 * Confidence: medium.
 */
unsigned int sk_swift_lead_bit_not(unsigned int byte)
{
    return (byte >> 7 & 1) ^ 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002c0120 @ 0x002c0120   (est. sk_swift_scalar_decode_utf8)
 * Ghidra: uint FUN_002c0120(void)
 * Decodes the next Unicode scalar from a UTF-8 buffer iterator (5-byte
 * packed form), with identity-cast validation and a fallback callback.
 * Confidence: low (Swift _StringGuts UTF-8 decode).
 */
unsigned int sk_swift_scalar_decode_utf8(void)
{
    unsigned int *pu = (unsigned int *)FUN_003539f4();
    FUN_00354fc0();
    if (FUN_00354fc0() != 0) {
        unsigned long l7 = FUN_00354a58();
        unsigned char a[16];
        FUN_00354a4c();
        FUN_00350530(0, 0, 0x6768d0);
        unsigned long l8 = FUN_00377824();
        if (l8 != l7) {
            goto fatal_cast;
        }
        unsigned int w = *pu;
        unsigned int lo = w & 0xffff;
        if (lo < 0x80) {
            return w + 1 & 0xff;
        }
        unsigned int hi = (w & 0x3f) * 0x100;
        if (lo < 0x800) {
            return hi + (lo >> 6) + 0x81c1;
        }
        if ((w & 0xf800) != 0xd800) {
            return ((hi | lo >> 6 & 0x3f) << 8 | w >> 0xc & 0xf) + 0x8181e1;
        }
    } else {
        unsigned long out_a = FUN_00354040();
        bool eq = (0 == (long)out_a);
        if (eq) {
            unsigned char a[16];
            FUN_00354a4c();
            FUN_00350530(0, 0, 0x676518);
            FUN_00377824();
            FUN_00357d64();
            if (FUN_00357d64() != 0) {
                return *pu;
            }
            goto fatal_cast;
        }
    }
    {
        unsigned long cb = FUN_00319688();
        FUN_0034bfb4(cb);
        unsigned int c = (unsigned int)(*(unsigned long (*)(void))cb)();
        if (c < 0x80) {
            c = c + 1;
        } else {
            bool is800 = c == 0x800;
            if (c < 0x800) {
                FUN_003592a0();
                c = 0 + 0;
            } else {
                FUN_0034b384((c & 0x3f) << 8);
                c = 0;
                if (is800) {
                    c = 0;
                }
            }
        }
        return c;
    }
fatal_cast:
    FUN_003488bc(1);
    FUN_00349844();
    FUN_00350a94();
    sk_fatal_error(0xb, 2, "", 0, 2, "", 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002c03fc @ 0x002c03fc   (est. sk_swift_scalar_decode_utf8_cb)
 * Ghidra: void FUN_002c03fc(uint *param_1,uint *param_2,undefined8 param_3,long param_4,undefined8 param_5)
 * Decodes a Unicode scalar into param_1 from the source param_2, dispatching
 * on the metatype tag param_4 (UTF-8 fast paths vs generic callback).
 * Confidence: low (Swift Character / Unicode scalar decode).
 */
void sk_swift_scalar_decode_utf8_cb(unsigned int *out, unsigned int *src, word_t a, long tag, word_t b)
{
    long thisp_word = 0;  /* incoming thisp */
    unsigned int c;
    if (tag == 0x6768d0) {
        unsigned long l4 = FUN_00002534(0x6560f0, 0x4e7ed8);
        unsigned long l5 = FUN_00377824(0, b, 0x6768d0, 0x612b58, 0x612b90);
        if (l5 != l4) {
            goto fatal_cast;
        }
        unsigned int w = *src;
        unsigned int lo = w & 0xffff;
        if (lo < 0x80) {
            c = w + 1 & 0xff;
            goto out;
        }
        unsigned int hi = (w & 0x3f) * 0x100;
        if (lo < 0x800) {
            c = hi + (lo >> 6) + 0x81c1;
            goto out;
        }
        if ((w & 0xf800) != 0xd800) {
            c = ((hi | lo >> 6 & 0x3f) << 8 | w >> 0xc & 0xf) + 0x8181e1;
            goto out;
        }
    } else if (tag == thisp_word) {
        unsigned long l4 = FUN_00377824(0, b, tag, 0x612b58, 0x612b90);
        if (l4 == 0x676bd0) {
            c = *src;
            goto out;
        }
        goto fatal_cast;
    }
    {
        unsigned int w = (*(unsigned int (*)(void *, long, unsigned long))FUN_00319688(b))(src, tag, b);
        if (w < 0x80) {
            c = w + 1;
        } else {
            unsigned int hi = (w & 0x3f) * 0x100;
            unsigned int v = (hi | w >> 6 & 0x3f) * 0x100;
            unsigned int v3 = ((v | w >> 0xc & 0x3f) << 8 | w >> 0x12) + 0x818181f1;
            if (w >> 0x10 == 0) {
                v3 = (w >> 0xc) + v + 0x8181e1;
            }
            c = (w >> 6) + hi + 0x81c1;
            if (w > 0x7ff) {
                c = v3;
            }
        }
    }
out:
    *out = c;
    *(unsigned char *)(out + 1) = 0;
    return;
fatal_cast:
    sk_fatal_error(0xb, 2, "identityCast to wrong type", 0x1b, 2,
                   "Swift.Builtin", 0x13, 2, 0x6d, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002c06c4 @ 0x002c06c4   (est. sk_swift_utf8_lead_bits)
 * Ghidra: int FUN_002c06c4(ulong param_1)
 * Returns the UTF-8 sequence byte-length (shifted by 0xb) from the leading
 * packed scalar word.
 * Confidence: medium.
 */
int sk_swift_utf8_lead_bits(unsigned long w)
{
    return sk_swift_utf8_width_2((unsigned int)(w & 0xffffffffff)) << 0xb;
}

/*--------------------------------------------------------------------*/
/* FUN_002c0710 @ 0x002c0710   (est. sk_swift_utf8_width_2)
 * Ghidra: ulong FUN_002c0710(uint param_1)
 * Classifies the packed leading scalar and returns its UTF-8 width in
 * units (2/3/4, or 1 for ASCII).
 * Confidence: medium (UTF-8 lead-byte classifier).
 */
unsigned long sk_swift_utf8_width_2(unsigned int w)
{
    if ((w & 0xf0c0) == 0xe080) {
        unsigned int u = 1;
        if ((w & 0xf20) != 0xd20 && (w & 0xf20) != 0) {
            u = 2;
        }
        return u;
    }
    if ((w & 0xf8c0) == 0xf080) {
        if ((unsigned)((w & 0x730) - 1) < 0x400) {
            return 2;
        }
    } else if (((w & 0xf8c0c0) == 0xf08080) && ((unsigned)((w & 0x73000) - 1) < 0x40000)) {
        unsigned long v = FUN_0006f794();
        return v;
    }
    return 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bf038 @ 0x002bf038   (est. sk_swift_integer_parse_string)
 * Ghidra: void FUN_002bf038(undefined8 param_1,long param_2,undefined8 param_3)
 * The Swift integer-from-string parser: validates the sign/step, then drives
 * a per-digit accumulation loop over a byte-iterator with radix/overflow
 * checks, building the result and bailing with a fatal on overflow or a
 * "0x" prefix-style digit-class failure. Large register-heavy loop.
 * Confidence: low (Swift Integer(_:radix:) core).
 */
void sk_swift_integer_parse_string(word_t a, long step, word_t src)
{
    unsigned long v = 0;
    unsigned long acc = 0;
    long pos = 0;
    long lim = 0;
    bool carry = false;
    if (step >= 0) {
        FUN_00117d14(src, a, step);
        return;
    }
    FUN_003488bc(1);
    FUN_0034a834();
    FUN_00356524();
    FUN_0008e518();
    FUN_00355db4();
    FUN_00353160();
    FUN_00351280();
    FUN_00377824();
    FUN_00350518();
    FUN_00352b08();
    FUN_00377bec();
    FUN_00350488();
    FUN_00352b08();
    FUN_00377824();
    FUN_003490b8(0);
    FUN_0007c1a4();
    FUN_0006a414();
    FUN_00350428();
    FUN_003509a4();
    FUN_00351930();
    FUN_00352b08();
    FUN_00377824();
    FUN_00350c80();
    FUN_00351de4();
    FUN_00377bec();
    FUN_00350950();
    FUN_0034be54();
    FUN_00349dfc();
    FUN_00377824(0, 0, v);
    FUN_00349c44(&pos);
    FUN_0007c1a4();
    FUN_0006a414();
    FUN_00350428();
    FUN_0034c754();
    FUN_00319218(0, v);
    FUN_0034ab20();
    FUN_0007c1a4();
    FUN_0006a414();
    FUN_0034aa9c();
    FUN_00350720();
    FUN_00310d68();
    FUN_003490b8(0);
    FUN_0006a414();
    FUN_003493c4();
    FUN_0034acf0();
    FUN_0006a414();
    FUN_0034b87c();
    FUN_00349c70();
    FUN_0006a414();
    FUN_003493c4();
    FUN_0034d444();
    FUN_0006a414();
    FUN_0034abec();
    FUN_0006a414();
    FUN_0034a414();
    FUN_0006a414();
    FUN_0034b540();
    FUN_0006a414();
    FUN_0034a9ac();
    FUN_0006a414();
    FUN_0034c2c8();
    FUN_003244ec(0);
    FUN_00353360(0, 0, 0);
    (*(void (*)(void))0)();
    FUN_00357cfc();
    FUN_00354a4c();
    FUN_00350c80();
    FUN_00377bec(0, 0, v);
    FUN_00350720();
    FUN_0032451c();
    FUN_00349890();
    unsigned long u = FUN_0019fd10();
    if ((u & 1) == 0) {
        FUN_00350920();
        FUN_00377dcc();
        FUN_00354064();
        FUN_000dbedc();
        FUN_00354618(0, 0);
        (*(unsigned long (*)(void))0)();
        FUN_00310a74();
        FUN_000863bc();
        FUN_00350e14();
        FUN_0034f1fc(0, 0);
        FUN_003537f0();
        FUN_00324534();
        FUN_000dbdf4();
        FUN_00350c68();
        (*(unsigned long (*)(void))0)();
        FUN_0009e234();
        if ((u & 1) != 0) {
            FUN_00100c38();
            (*(unsigned long (*)(void))0)();
            FUN_003544e0();
            FUN_00356664(0, 0);
            FUN_0034f1fc();
            FUN_00100c38();
            FUN_003245c4(0);
            FUN_00353cb4();
            FUN_00351118();
            FUN_00354410();
            FUN_0034e220();
            FUN_00376820(0, v);
            FUN_00358c68();
            FUN_00354b08();
            FUN_002734e4(0, v);
            FUN_003508f0();
            FUN_0034c3b4();
            FUN_00350af4(0);
            (*(void (*)(void))0)();
            goto finish;
        }
        FUN_00354b68();
        pos = -1;
    }
    /* Main accumulation loop over the digit bytes. */
    FUN_00356be0();
    FUN_000a68f4();
    FUN_00354570(0);
    FUN_00355dc0(0);
    FUN_00353e44();
    do {
        FUN_00353e38();
        FUN_00355e8c(src, 0);
        (*(void (*)(void))0)();
        FUN_0034e1b0(0);
        if (carry) {
            FUN_00350bc0(0);
            FUN_00357be0(0);
            (*(void (*)(void))0)();
            FUN_00350c38();
            (*(void (*)(void))0)();
            FUN_00357cfc();
            FUN_00349890();
            u = FUN_0019fd10(v);
            if ((u & 1) != 0) goto finish_neg;
            break;
        }
        FUN_003510d0(0);
        FUN_00350c8c(acc);
        (*(void (*)(void))0)();
        FUN_003245c4(0);
        FUN_00353cb4();
        FUN_003516a8();
        (*(void (*)(void))0)();
        FUN_00349890();
        long n = FUN_0019c9cc(v);
        if (n + 1 == (long)(unsigned long)(n + 1)) {
            CL4_FATAL();
        }
        FUN_00350c08();
        lim = FUN_002b9a04();
        if (lim < n + 1) {
            FUN_0034b348();
            FUN_003486b8(0xbe);
            FUN_0034975c();
            goto fatal;
        }
        FUN_00310aa4(0);
        FUN_00352134();
        FUN_00350630();
        (*(void (*)(void))0)();
        FUN_00310a14();
        FUN_0034eef8();
        (*(void (*)(void))0)();
        u = FUN_003585d0();
        if ((u & 1) != 0) {
            FUN_0034ad00();
            FUN_003509e0();
            FUN_00351148(&pos);
            FUN_00377bec();
            FUN_00350654();
            FUN_0035179c(&pos);
            FUN_0034d744();
            FUN_0034e784();
            FUN_003508c0(0, 0);
            (*(void (*)(void))0)();
            FUN_00310ad4();
            FUN_00351ef8();
            FUN_00310954();
            FUN_003505d0();
            FUN_0035256c();
            u = (*(unsigned long (*)(void))0)();
            FUN_00350b3c();
            (*(void (*)(void))0)();
            if ((u & 1) != 0) goto digit_ok;
            goto fatal;
        }
digit_ok:
        pos = (long)(*(unsigned long (*)(void))0)();
        if (pos > 0x1f) {
            FUN_003504f4();
            u = (*(unsigned long (*)(void))0)();
            FUN_003504f4();
            pos = (long)(*(unsigned long (*)(void))0)();
            if ((u & 1) == 0) {
                if (pos < 0x21) {
                    FUN_0034bf2c();
                    FUN_003504f4();
                    (*(void (*)(void))0)();
                } else {
                    FUN_00351c34();
                    FUN_000863bc();
                    FUN_00358c68();
                    FUN_003544e0(0);
                    FUN_0034f1fc();
                    (*(void (*)(void))0)();
                    FUN_00348c84();
                    FUN_000e15d8();
                    FUN_00351de4();
                    FUN_00351e60();
                    FUN_003585d0();
                    (*(void (*)(void))0)();
                    if (pos & 1) goto finish;
                }
            } else {
                if (pos < 0x21) {
                    FUN_0034ad00();
                    FUN_003509e0();
                    FUN_00351148(&pos);
                    FUN_00377bec();
                    FUN_00350654();
                    FUN_0035179c(&pos);
                    FUN_0034d744();
                    FUN_0034e784();
                    FUN_00354d94();
                    FUN_003508c0();
                    FUN_00310ad4();
                    FUN_00352ee4();
                    FUN_00310b08();
                    FUN_0034c8b8();
                    FUN_003569e4();
                    u = (*(unsigned long (*)(void))0)();
                    FUN_003585d0(0);
                    (*(void (*)(void))0)();
                    if ((u & 1) != 0) {
                        FUN_0034bf2c();
                        FUN_003504f4();
                        (*(void (*)(void))0)();
                    }
                } else {
                    FUN_00351c34();
                    FUN_000863bc();
                    FUN_00358c68();
                    FUN_003544e0(0);
                    FUN_0034f1fc();
                    FUN_00310a74();
                    FUN_0034a4bc();
                    FUN_00084174();
                    FUN_003569e4();
                    u = (*(unsigned long (*)(void))0)();
                    FUN_003509e0();
                    (*(void (*)(void))0)();
                    if ((u & 1) == 0) {
                        /* continue */
                    } else goto finish;
                }
            }
        }
        FUN_0034bf2c();
        FUN_003504f4();
        (*(void (*)(void))0)();
        FUN_003507c8();
        (*(void (*)(void))0)();
        FUN_003510d0(0);
        FUN_0035a3dc();
        (*(void (*)(void))0)();
        FUN_003504f4();
        u = (*(unsigned long (*)(void))0)();
        if ((u & 1) != 0) {
            FUN_0034ad00();
            FUN_003507c8();
            FUN_00351148(&pos);
            FUN_00377bec();
            FUN_0034b8ec();
            FUN_00352f48(&pos);
            FUN_00350440();
            FUN_0034b9f8();
            FUN_0034c384();
            FUN_0035481c();
            FUN_00350ad0();
            FUN_0034af04();
            FUN_00310954();
            FUN_0034e054();
            FUN_00351de4();
            u = (*(unsigned long (*)(void))0)();
            FUN_0009e234();
            (*(void (*)(void))0)();
            if ((u & 1) == 0) goto fatal;
        }
        FUN_003504f4();
        pos = (long)(*(unsigned long (*)(void))0)();
        if (pos < 0x20) {
            FUN_0035966c();
            (*(void (*)(void))0)();
        } else {
            FUN_003504f4();
            unsigned long p = (*(unsigned long (*)(void))0)();
            FUN_003504f4();
            pos = (long)(*(unsigned long (*)(void))0)();
            if ((p & 1) == 0) {
                if (pos <= 0x20) {
                    FUN_0035966c();
                    (*(void (*)(void))0)();
                    FUN_003504f4();
                    (*(void (*)(void))0)();
                } else {
                    FUN_00351c34();
                    FUN_000863bc();
                    FUN_00358c68();
                    FUN_003544e0(0);
                    FUN_0034f1fc();
                    (*(void (*)(void))0)();
                    FUN_00348c84();
                    FUN_00350bf0();
                    FUN_00351de4();
                    u = (*(unsigned long (*)(void))0)();
                    FUN_0009e234();
                    (*(void (*)(void))0)();
                    if ((u & 1) != 0) goto finish;
                    FUN_0035966c();
                }
            } else {
                if (pos <= 0x20) {
                    FUN_0035966c();
                    (*(void (*)(void))0)();
                    FUN_0034ad00();
                    FUN_0009e234();
                    FUN_00351148(&pos);
                    FUN_00377bec();
                    FUN_0034b8ec();
                    FUN_0035179c(&pos);
                    FUN_00350440();
                    FUN_0034b9f8();
                    FUN_0034cea8();
                    FUN_003530cc();
                    FUN_00350c08();
                    FUN_0034af04();
                    FUN_00310b08();
                    FUN_0034f4f4();
                    FUN_00351de4();
                    (*(void (*)(void))0)();
                    FUN_0035a104();
                    (*(void (*)(void))0)();
                } else {
                    FUN_00351c34();
                    FUN_000863bc();
                    FUN_00358c68();
                    FUN_003544e0(0);
                    FUN_0034f1fc();
                    (*(void (*)(void))0)();
                    FUN_00348c84();
                    FUN_00350bf0();
                    FUN_00351de4();
                    u = (*(unsigned long (*)(void))0)();
                    FUN_0009e234();
                    (*(void (*)(void))0)();
                    if ((u & 1) != 0) goto finish;
                }
            }
        }
        FUN_003504f4();
        (*(void (*)(void))0)();
        FUN_00350b3c();
        (*(void (*)(void))0)();
        FUN_002b8904(0, v, 0);
        FUN_0034c3b4();
        (*(void (*)(void))0)();
        FUN_00354064();
        FUN_00353dac(0);
        FUN_00357884();
        FUN_00354b68(0, 0);
        (*(void (*)(void))0)();
        FUN_00357cfc();
        FUN_00349890();
        pos = FUN_0019c9cc(v);
        FUN_00350c38();
        (*(void (*)(void))0)();
        FUN_00350c08();
        lim = FUN_002b9a04();
    } while (pos < lim);
    FUN_00324564(0);
    FUN_003511fc();
    FUN_00350c38();
    u = (*(unsigned long (*)(void))0)();
    FUN_00324594(0);
    FUN_0035133c();
    FUN_003516a8(0);
    (*(void (*)(void))0)();
    FUN_00350c38();
    (*(void (*)(void))0)();
    FUN_003245c4(0);
    FUN_00352858(0);
    (*(void (*)(void))0)();
    FUN_00351cac(0);
    FUN_00350ab8();
    (*(void (*)(void))0)();
    FUN_00352858(0);
    (*(void (*)(void))0)();
    FUN_00351cac(0);
    if ((u & 1) == 0) {
        FUN_00357274();
        FUN_00310984();
        FUN_003510e8();
        FUN_0035060c();
        if (FUN_001e23b0() == 0) {
            FUN_00350410();
            FUN_00348074();
            FUN_00351be0();
            goto fatal;
        }
        FUN_0034f9d8(0);
        (*(void (*)(void))0)();
        goto finish;
    }
    FUN_0035748c(0);
    (*(void (*)(void))0)();
    goto finish;
finish_neg:
    FUN_000a68f4(0);
    FUN_00350b24();
    (*(void (*)(void))0)();
    FUN_0034e1b0();
    if (carry) {
        FUN_00350bc0(0);
        FUN_00357be0();
        (*(void (*)(void))0)();
        goto finish2;
    }
    FUN_003508fc();
    (*(void (*)(void))0)();
    FUN_00350920();
    FUN_00377dcc();
    FUN_00324534(0);
    FUN_0035012c();
    u = (*(unsigned long (*)(void))0)();
    if ((u & 1) == 0) {
        FUN_003245c4(0);
        FUN_00353cb4();
        FUN_003516a8();
        (*(void (*)(void))0)();
        FUN_0035abd8();
        FUN_002b9a60(0, v);
        FUN_003509e0(0);
        (*(void (*)(void))0)();
        FUN_0034c3b4();
        (*(void (*)(void))0)();
        FUN_00354b68();
        /* continue main loop */
        goto finish;
    }
    FUN_0007c1c4();
    (*(void (*)(void))0)();
    goto finish;
finish2:
    FUN_00356078();
    FUN_0031dec4();
    FUN_003526b8(0, 0, 0, 0x66f5a8);
    FUN_00351154(0, 0);
    (*(void (*)(void))0)();
finish:
    FUN_00350488();
    FUN_0031e084();
    FUN_00356b98();
    FUN_00369340(0, 0, v);
    FUN_0008e500(0);
    return;
fatal:
    FUN_00350410();
    FUN_00348194();
    FUN_003523f0();
    sk_fatal_error(0xb, 2, "", 0, 2, "", 0);
}
/* Forward declarations for the remaining in-slice cross-referenced functions. */
word_t sk_swift_utf8_decode_scalar(long pos, long base);          /* FUN_002c2384 */
unsigned int sk_swift_utf8_error_check(char kind, long lo, long hi); /* FUN_002c12d0 */
unsigned int sk_swift_utf8_error_payload(unsigned char kind);     /* FUN_002c1540 */
unsigned int sk_swift_utf8_width_3(unsigned int w);               /* FUN_002c0d18 */
unsigned int sk_swift_utf8_byte_combine(unsigned int w, int pad); /* FUN_002c0da0 */
unsigned int sk_swift_utf16_len(unsigned long w);                 /* FUN_002c4e1c */
unsigned long sk_swift_utf16_combine(unsigned int hi, unsigned int lo); /* FUN_002c4e44 */
unsigned int sk_swift_utf16_len_le(unsigned long w);              /* FUN_002c51e4 */
unsigned long sk_swift_utf8_lead_check(unsigned int w);           /* FUN_002c4b04 */
unsigned int sk_swift_scalar_from_utf16(unsigned long w);         /* FUN_002c4b10 */
unsigned long sk_swift_scalar_to_utf16(unsigned int scalar);      /* FUN_002c4b34 */
unsigned long sk_swift_utf16_pack(unsigned int hi, unsigned int lo); /* FUN_002c520c */
unsigned int sk_swift_char_classify(word_t a, word_t b, word_t c);/* FUN_002c5698 */
long sk_swift_unsafebuf_offset(long lo, long hi, long base);      /* FUN_002c1e7c */
void sk_swift_unsafebuf_check(long lo, long hi);                  /* FUN_002c21b8 */
void sk_swift_string_utf8_sync(void);                             /* FUN_002c1d78 */
long sk_swift_utf8_prev_boundary(long pos, long base);            /* FUN_002c2440 */
long sk_swift_utf8_prev_boundary2(long pos, long base);           /* FUN_002c2490 */
void sk_swift_utf8_next_scalar(word_t a, word_t b, word_t base);  /* FUN_002c24c4 */
long sk_swift_grapheme_break_before(long pos, long base);         /* FUN_002c27b4 */
unsigned long sk_swift_string_prev_scalar(void);                  /* FUN_002c2c30 */
unsigned long sk_swift_grapheme_break_core(unsigned long pos);    /* FUN_002c2ea4 */
unsigned long sk_swift_utf8_decode_byte4(unsigned int w);         /* FUN_002c5ad4 */
unsigned long sk_swift_utf8_decode_buffer2(void);                 /* FUN_002c5d18 */
void sk_swift_scalar_encode_utf8(unsigned int scalar, void (*emit)(void *)); /* FUN_002c610c */
void sk_swift_utf8_emit_scalar(void);                             /* FUN_002c5c6c */
void sk_swift_utf16_next_scalar(void);                            /* FUN_002c6228 */

/*--------------------------------------------------------------------*/
/* FUN_002c07c0 @ 0x002c07c0   (est. sk_swift_utf8_decode_buffer)
 * Ghidra: void FUN_002c07c0(ulong *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Decodes a UTF-8 sequence from the 5-byte packed iterator into the caller's
 * output (scalar + validity flag). Accumulates continuation bytes, computes
 * the encoded width, shifts the residual, and reports the scalar or a
 * division-based failure. Mirrors the Swift _StringGuts UTF8 decode.
 * Confidence: low (Swift UIntBuffer UTF-8 decode).
 */
void sk_swift_utf8_decode_buffer(unsigned long *out, word_t a, word_t b, word_t c, word_t d)
{
    unsigned char *thisp = (unsigned char *)0;  /* iterator (this) */
    unsigned char local_80 = 0;
    char local_7f = 0;
    unsigned int w = (unsigned int)*thisp;
    unsigned long acc = (unsigned long)w;
    unsigned char len = *(unsigned char *)((char *)thisp + 4);
    unsigned long n = (unsigned long)len;
    unsigned long f = FUN_0019fcc8((unsigned long)*thisp);
    unsigned char valid = 0;
    if ((f & 1) == 0) {
        if ((w >> 7 & 1) == 0) {
            (*(void (*)(void *, void *))FUN_0006869c(&local_80, d, FUN_00343bcc()))(&local_80, 0);
            FUN_00273168(0);
            *(unsigned int *)out = 0;
            FUN_002c8df4(acc);
            valid = 0;
            goto done;
        }
    } else {
        (*(void (*)(void *, word_t, word_t))FUN_000a68f4(c))(&local_80, b, c);
        if (local_7f == 1) {
            *out = 0;
            valid = 2;
            goto done;
        }
        if ((char)local_80 >= 0) {
            FUN_0001a1c8();
            unsigned int e = FUN_00271d24();
            valid = 0;
            *(unsigned int *)out = e;
            goto done;
        }
        if (len > 0x1f) goto fatal_overflow;
        w = (unsigned int)local_80 << (len & 0x1f) | (unsigned int)(-0xff << (len & 0x1f)) - 1U & w;
        acc = (unsigned long)w;
        *(unsigned int *)thisp = w;
        n = n + 8;
        *(char *)((char *)thisp + 4) = (char)n;
    }
    (*(void (*)(void *, word_t, word_t))FUN_000a68f4(c))(&local_80, b, c);
    unsigned long acc2 = n << 0x20;
    do {
        (*(void (*)(void *, word_t, word_t))FUN_000a68f4(c))(&local_80, b, c);
        w = (unsigned int)acc;
        if (local_7f == 1) {
            acc2 = FUN_0019fcc8(acc2 & 0xff00000000 | acc);
            if ((acc2 & 1) != 0) {
                *out = 0;
                valid = 2;
                goto done;
            }
            break;
        }
        if (n > 0x1f) goto fatal_overflow;
        w = (unsigned int)local_80 << (n & 0x1f) | (unsigned int)(-0xff << (n & 0x1f)) - 1U & w;
        acc = (unsigned long)w;
        *(unsigned int *)thisp = w;
        n = n + 8;
        *(char *)((char *)thisp + 4) = (char)n;
        acc2 = acc2 + 0x800000000;
    } while (FUN_0019c9c4(acc2 + acc) < FUN_000af308(acc2 + acc));
    if ((w & 0xe0c0) == 0xc080) {
        if ((w & 0x1e00) == 0) goto width_fallback;
        acc2 = 0x10;
        goto have_bits;
    } else {
        if ((w & 0xf0c0c0) != 0xe08080) {
            if (((w & 0xf8c0c0c0) != 0xf0808080) || ((w & 0x7300000) - 1 >> 0x1a != 0))
                goto width_fallback;
            acc2 = 0x20;
            goto have_bits;
        }
        if (((w & 0xf2000) != 0) && ((w & 0xf2000) != 0xd2000)) {
            acc2 = 0x18;
            goto have_bits;
        }
width_fallback:;
        unsigned int i = sk_swift_utf8_width_2((unsigned int)(((n & 0xffffffff) << 32 | w) & 0xffffffffff));
        valid = 0;
        acc2 = (unsigned long)(i << 3);
        goto finish;
    }
have_bits:
    valid = 1;
finish:
    *(unsigned int *)thisp = w >> (acc2 & 0x3f);
    *(char *)((char *)thisp + 4) = (char)n - (char)acc2;
    if (valid) {
        w = (w & 0xff00ff00) >> 8 | (w & 0xff00ff) << 8;
        *out = (unsigned long)((w >> 0x10 | w << 0x10) + 0x1010101 >> (0x20 - (unsigned int)acc2 & 0x1f));
    } else {
        unsigned int div = (unsigned int)(acc2 & 0xff);
        unsigned int d8 = (unsigned int)FUN_001e23b0(8);
        if (d8 == 0) {
            sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2, "Swift.IntegerTypes", 0x18, 2, 0x19d, 1);
        }
        unsigned int q = 0;
        if (d8 != 0) {
            q = div / d8;
        }
        *out = (unsigned long)q;
        valid = 1;
    }
done:
    *(unsigned char *)(out + 1) = valid;
    return;
fatal_overflow:
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UIntBuffer", 0x16, 2, 0xbe, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002c0b64 @ 0x002c0b64   (est. sk_swift_utf8_lead_len_a)
 * Ghidra: uint FUN_002c0b64(void)
 * Returns the UTF-8 encoded length (in bits, <<8) plus a validity flag for
 * the packed leading scalar.
 * Confidence: medium.
 */
unsigned int sk_swift_utf8_lead_len_a(void)
{
    unsigned char *thisp = (unsigned char *)0;  /* iterator (this) */
    unsigned int w = (unsigned int)*thisp;
    unsigned int bits;
    if ((w & 0xe0c0) == 0xc080) {
        if ((w & 0x1e00) == 0) goto fallback;
        bits = 0x10;
    } else if ((w & 0xf0c0c0) == 0xe08080) {
        if (((w & 0xf2000) == 0) || ((w & 0xf2000) == 0xd2000)) {
fallback:;
            bits = (unsigned int)sk_swift_utf8_width_2((unsigned long)w) << 3;
            w = 0;
            return w | bits << 8;
        }
        bits = 0x18;
    } else {
        if (((w & 0xf8c0c0c0) != 0xf0808080) || ((w & 0x7300000) - 1 >> 0x1a != 0)) goto fallback;
        bits = 0x20;
    }
    w = 1;
    return w | bits << 8;
}

/*--------------------------------------------------------------------*/
/* FUN_002c0b68 @ 0x002c0b68   (est. sk_swift_utf8_lead_len_b)
 * Ghidra: uint FUN_002c0b68(void)
 * Same as sk_swift_utf8_lead_len_a (duplicate entry).
 * Confidence: medium.
 */
unsigned int sk_swift_utf8_lead_len_b(void)
{
    return sk_swift_utf8_lead_len_a();
}

/*--------------------------------------------------------------------*/
/* FUN_002c0cec @ 0x002c0cec   (est. sk_swift_utf8_lead_bits2_a)
 * Ghidra: int FUN_002c0cec(ulong param_1)
 * Returns the UTF-8 sequence length (shifted by 0xb) from the packed scalar.
 * Confidence: medium.
 */
int sk_swift_utf8_lead_bits2_a(unsigned long w)
{
    return sk_swift_utf8_width_3((unsigned int)(w & 0xffffffffff)) << 0xb;
}

/*--------------------------------------------------------------------*/
/* FUN_002c0cf0 @ 0x002c0cf0   (est. sk_swift_utf8_lead_bits2_b)
 * Ghidra: int FUN_002c0cf0(ulong param_1)
 * Same as sk_swift_utf8_lead_bits2_a (duplicate entry).
 * Confidence: medium.
 */
int sk_swift_utf8_lead_bits2_b(unsigned long w)
{
    return sk_swift_utf8_width_3((unsigned int)(w & 0xffffffffff)) << 0xb;
}

/*--------------------------------------------------------------------*/
/* FUN_002c0d18 @ 0x002c0d18   (est. sk_swift_utf8_width_3)
 * Ghidra: undefined4 FUN_002c0d18(uint param_1)
 * Classifies the packed scalar and returns its UTF-8 width in code points
 * (1-3), validating overlong encodings.
 * Confidence: medium (UTF-8 lead classifier, big-endian form).
 */
unsigned int sk_swift_utf8_width_3(unsigned int w)
{
    if ((w & 0xc0f0) == 0x80e0) {
        unsigned int u = 1;
        if ((w & 0x200f) != 0x200d && (w & 0x200f) != 0) {
            u = 2;
        }
        return u;
    }
    if ((w & 0xc0f8) == 0x80f0) {
        unsigned int u = 1;
        if ((w & 0x3007) != 0) {
            unsigned int v = 2;
            if ((w & 0xc00000) == 0x800000) {
                v = 3;
            }
            u = 1;
            if (((w & 0x3007) >> 8 | (w & 7) << 8) < 0x401) {
                u = v;
            }
        }
        return u;
    }
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002c0da0 @ 0x002c0da0   (est. sk_swift_utf8_byte_combine)
 * Ghidra: uint FUN_002c0da0(uint param_1,int param_2)
 * Combines the residual packed scalar bytes after a shift: produces a mask
 * from the shift width and adds a per-byte bias to param_2.
 * Confidence: medium (UTF-8 residual combination helper).
 */
unsigned int sk_swift_utf8_byte_combine(unsigned int width, int packed)
{
    return ((1U << (width + 1 >> 1 & 0x1f)) << (width >> 1 & 0x1f)) - 1U &
           (unsigned int)(packed + 0x1010101);
}
/*--------------------------------------------------------------------*/
/* FUN_002c0dd0 @ 0x002c0dd0   (est. sk_swift_utf8_decode_buffer_be)
 * Ghidra: void FUN_002c0dd0(ulong *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Big-endian variant of the UTF-8 decode buffer: accumulates continuation
 * bytes from the packed iterator, computes the encoded width, shifts out the
 * residual, and emits (scalar | validity). Mirrors the Swift UIntBuffer.
 * Confidence: low (Swift UTF-8 decode, big-endian form).
 */
void sk_swift_utf8_decode_buffer_be(unsigned long *out, word_t a, word_t b, word_t c, word_t d)
{
    unsigned char *thisp = (unsigned char *)0;  /* iterator (this) */
    unsigned char local_80 = 0;
    char local_7f = 0;
    unsigned int w = (unsigned int)*thisp;
    unsigned long acc = (unsigned long)w;
    unsigned char len = *(unsigned char *)((char *)thisp + 4);
    unsigned long n = (unsigned long)len;
    unsigned long f = FUN_0019fcc8((unsigned long)*thisp);
    unsigned char valid = 0;
    if ((f & 1) == 0) {
        if ((w >> 7 & 1) == 0) {
            (*(void (*)(void *, void *))FUN_0006869c(&local_80, d, FUN_00324654()))(&local_80, 0);
            FUN_00273168(0);
            *(unsigned int *)out = 0;
            FUN_002c8df4(acc);
            valid = 0;
            goto done;
        }
    } else {
        (*(void (*)(void *, word_t, word_t))FUN_000a68f4(c))(&local_80, b, c);
        if (local_7f == 1) {
            *out = 0;
            valid = 2;
            goto done;
        }
        if ((char)local_80 >= 0) {
            FUN_0001a1c8();
            unsigned int e = FUN_00271d24();
            valid = 0;
            *(unsigned int *)out = e;
            goto done;
        }
        if (len > 0x1f) goto fatal_overflow;
        unsigned int nw = (unsigned int)local_80 << (len & 0x1f) | (unsigned int)(-0xff << (len & 0x1f)) - 1U & w;
        acc = (unsigned long)nw;
        *(unsigned int *)thisp = nw;
        n = (unsigned char)len + 8;
        *(char *)((char *)thisp + 4) = (char)n;
    }
    (*(void (*)(void *, word_t, word_t))FUN_000a68f4(c))(&local_80, b, c);
    unsigned long acc2 = n << 0x20;
    unsigned int wv = 0;
    unsigned long pack = 0;
    do {
        wv = (unsigned int)acc;
        (*(void (*)(void *, word_t, word_t))FUN_000a68f4(c))(&local_80, b, c);
        unsigned char nb = local_80;
        acc = acc | (unsigned long)(n & 0xff) << 0x20;
        if (local_7f == 1) {
            acc = FUN_0019fcc8(acc);
            if ((acc & 1) != 0) {
                *out = 0;
                valid = 2;
                goto done;
            }
            break;
        }
        if (n + 1 == (long)(n + 1)) {
            CL4_FATAL();
        }
        if (FUN_000af308(acc) < n + 1) goto fatal_overflow;
        wv = (unsigned int)nb << (n & 0x1f) | (unsigned int)(-0xff << (n & 0x1f)) - 1U & wv;
        acc = (unsigned long)wv;
        *(unsigned int *)thisp = wv;
        unsigned int i = FUN_00084110(((n & 0xffffffff) << 32 | wv) & 0xffffffffff);
        n = i + n;
        *(char *)((char *)thisp + 4) = (char)n;
        pack = ((n & 0xffffffff) << 32 | wv) & 0xffffffffff;
        acc2 = FUN_0019c9c4(pack);
    } while (acc2 < FUN_000af308(pack));
    if ((wv & 0xc0e0) == 0x80c0) {
        if ((wv & 0x1e) == 0) goto width_fallback;
        acc2 = 0x10;
        goto have_bits;
    } else {
        if ((wv & 0xc0c0f0) != 0x8080e0) {
            if ((((wv & 0xc0c0c0f8) != 0x808080f0) || ((wv & 0x3007) == 0)) ||
                (0x400 < ((wv & 0x3007) >> 8 | (wv & 7) << 8))) goto width_fallback;
            acc2 = 0x20;
            goto have_bits;
        }
        if (((wv & 0x200f) != 0) && ((wv & 0x200f) != 0x200d)) {
            acc2 = 0x18;
            goto have_bits;
        }
width_fallback:;
        unsigned int i = sk_swift_utf8_width_3((unsigned int)(((n & 0xffffffff) << 32 | wv) & 0xffffffffff));
        valid = 0;
        acc2 = (unsigned long)(i << 3);
        goto finish;
    }
have_bits:
    valid = 1;
finish:
    *(unsigned int *)thisp = wv >> (acc2 & 0x3f);
    *(char *)((char *)thisp + 4) = (char)n - (char)acc2;
    if (valid) {
        acc2 = sk_swift_utf8_byte_combine((unsigned int)acc2, (int)(((n & 0xffffffff) << 32 | wv) & 0xffffffffff));
        valid = 0;
        *out = acc2 & 0xffffffff;
    } else {
        unsigned int d16 = (unsigned int)FUN_001e23b0(8);
        if (d16 == 0) {
            sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2, "Swift.IntegerTypes", 0x18, 2, 0x19d, 1);
        }
        unsigned int q = 0;
        if (d16 != 0) {
            q = ((unsigned int)acc2 & 0xff) / d16;
        }
        *out = (unsigned long)q;
        valid = 1;
    }
done:
    *(unsigned char *)(out + 1) = valid;
    return;
fatal_overflow:
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UIntBuffer", 0x16, 2, 0xbe, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002c11ac @ 0x002c11ac   (est. sk_swift_utf8_lead_len_be_a)
 * Ghidra: uint FUN_002c11ac(void)
 * Returns the big-endian UTF-8 length (bits <<8) plus a validity flag.
 * Confidence: medium.
 */
unsigned int sk_swift_utf8_lead_len_be_a(void)
{
    unsigned char *thisp = (unsigned char *)0;
    unsigned int w = (unsigned int)*thisp;
    unsigned int bits;
    if ((w & 0xc0e0) == 0x80c0) {
        if ((w & 0x1e) == 0) goto fallback;
        bits = 0x10;
    } else if ((w & 0xc0c0f0) == 0x8080e0) {
        if (((w & 0x200f) == 0) || ((w & 0x200f) == 0x200d)) {
fallback:;
            bits = (unsigned int)sk_swift_utf8_width_3((unsigned long)w) << 3;
            w = 0;
            return w | bits << 8;
        }
        bits = 0x18;
    } else {
        if ((((w & 0xc0c0c0f8) != 0x808080f0) || ((w & 0x3007) == 0)) ||
            (0x400 < ((w & 0x3007) >> 8 | (w & 7) << 8))) goto fallback;
        bits = 0x20;
    }
    w = 1;
    return w | bits << 8;
}

/*--------------------------------------------------------------------*/
/* FUN_002c11b0 @ 0x002c11b0   (est. sk_swift_utf8_lead_len_be_b)
 * Ghidra: uint FUN_002c11b0(void)
 * Same as sk_swift_utf8_lead_len_be_a (duplicate entry).
 * Confidence: medium.
 */
unsigned int sk_swift_utf8_lead_len_be_b(void)
{
    return sk_swift_utf8_lead_len_be_a();
}

/*--------------------------------------------------------------------*/
/* FUN_002c127c @ 0x002c127c   (est. sk_swift_utf8_byte_combine_store)
 * Ghidra: void FUN_002c127c(undefined4 *param_1,undefined4 param_2)
 * Stores the byte-combination of param_2 into the caller's output.
 * Confidence: low.
 */
void sk_swift_utf8_byte_combine_store(unsigned int *out, unsigned int width)
{
    unsigned char *thisp = (unsigned char *)0;
    *out = sk_swift_utf8_byte_combine(width, (int)*thisp);
}

/*--------------------------------------------------------------------*/
/* FUN_002c12b0 @ 0x002c12b0   (est. sk_swift_cpu_membarrier)
 * Ghidra: void FUN_002c12b0(void)
 * Executes a memory barrier / CPU maintenance op.
 * Confidence: low.
 */
void sk_swift_cpu_membarrier(void)
{
    FUN_00106e3c();
}

/*--------------------------------------------------------------------*/
/* FUN_002c12d0 @ 0x002c12d0   (est. sk_swift_utf8_error_check)
 * Ghidra: void FUN_002c12d0(char param_1,long param_2,long param_3)
 * Validates a UTF-8 decode boundary: computes the fatal "code" based on the
 * kind (continuation vs overlong vs surrogate) and the remaining length,
 * faulting via Swift.UTF8EncodingError when the run is malformed; returns
 * (falls through) when the run is acceptable.
 * Confidence: medium (UTF-8 error-code selection).
 */
unsigned int sk_swift_utf8_error_check(char kind, long lo, long hi)
{
    if (lo < 0) {
        sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UTF8EncodingError", 0x1d, 2, 0x76, 1);
    }
    if (kind == 4) {
        if (lo == hi) {
            sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UTF8EncodingError", 0x1d, 2, 0x78, 1);
        }
        if (hi - lo < 4) {
            return 0;
        }
        sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UTF8EncodingError", 0x1d, 2, 0x79, 1);
    } else {
        if (hi - lo == 1) {
            return 0;
        }
        sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UTF8EncodingError", 0x1d, 2, 0x7b, 1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002c13c0 @ 0x002c13c0   (est. sk_swift_string_hash_128)
 * Ghidra: void FUN_002c13c0(void)
 * String hashing helper: computes the 128-bit hash state via the runtime
 * hasher sequence and finalizes.
 * Confidence: low (Swift Hasher internals).
 */
void sk_swift_string_hash_128(void)
{
    FUN_00350a10();
    FUN_003528cc();
    FUN_00229a3c();
    FUN_002298d4();
    FUN_002298d4();
}

/*--------------------------------------------------------------------*/
/* FUN_002c1400 @ 0x002c1400   (est. sk_swift_string_hash_rot)
 * Ghidra: void FUN_002c1400(void)
 * Rotation-based string hash: folds a byte with a key word, then runs the
 * two-step hasher and finalizes with a hash-value helper.
 * Confidence: low.
 */
void sk_swift_string_hash_rot(void)
{
    FUN_00350b54();
    unsigned char b = FUN_00348c48();
    FUN_0034ec48(b, 0x4e7a30 + 0x10, b ^ (unsigned char)0x4e7a30);
    FUN_00229a3c();
    FUN_00355458();
    FUN_002298d4();
    FUN_003567c8();
    FUN_002298d4();
    FUN_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_002c1498 @ 0x002c1498   (est. sk_swift_string_hash_store)
 * Ghidra: void FUN_002c1498(void)
 * Builds the hash-state from the thisp words and finalizes.
 * Confidence: low.
 */
void sk_swift_string_hash_store(void)
{
    word_t a = *(word_t *)(thisp + 8);
    word_t b = *(word_t *)(thisp + 0x10);
    unsigned char k = *(unsigned char *)thisp;
    unsigned char st[72];
    FUN_001a84f4(st);
    FUN_002c13c0();
    FUN_001a8564();
    (void)a; (void)b; (void)k;
}

/*--------------------------------------------------------------------*/
/* FUN_002c1510 @ 0x002c1510   (est. sk_swift_utf16_codeunit)
 * Ghidra: void FUN_002c1510(undefined2 *param_1,undefined1 *param_2)
 * Converts a byte into a UTF-16 code unit via FUN_002b279c and stores it.
 * Confidence: low.
 */
void sk_swift_utf16_codeunit(unsigned short *out, unsigned char *byte)
{
    *out = (unsigned short)FUN_002b279c(*byte);
}

/*--------------------------------------------------------------------*/
/* FUN_002c1540 @ 0x002c1540   (est. sk_swift_utf8_error_payload)
 * Ghidra: undefined1 [16] FUN_002c1540(byte param_1)
 * Returns the 128-bit error payload {code, name-ptr} for a UTF-8 decode
 * failure kind (overlong / truncated / surrogate / continuation), or a
 * generic invalid-encoding payload.
 * Confidence: high (Swift.UTF8EncodingError codes + names).
 */
void sk_swift_utf8_error_payload(unsigned char kind, word_t *out_lo, word_t *out_hi)
{
    if (kind > 4) {
        FUN_00350d94(0xcb);
        FUN_0006f768();
        sk_fatal_unknown_numeric_type();  /* FUN_001afa84 */
    }
    word_t code = 0xd000000000000021;
    word_t name = 0x5d0be0;   /* s__overlongEncodingByte_005d0be0 */
    switch (kind) {
    default:
        name = 0x5d0b60;      /* s_Swift_UTF8EncodingError_swift_005d0b60 */
        code = 0xd00000000000001b;
        break;
    case 1:
        name = 0x5d0ba0;      /* s__truncatedScalar_005d0ba0 */
        code = 0xd000000000000017;
        break;
    case 2:
        break;
    case 3:
        name = 0x5d0bc0;      /* s__surrogateCodePointByte_005d0bc0 */
        code = 0xd000000000000015;
        break;
    case 4:
        name = 0x5d0b80;      /* s__unexpectedContinuationByte_005d0b80 */
        code = 0xd000000000000010;
        break;
    }
    *out_hi = name | 0x8000000000000000;
    *out_lo = code;
}
