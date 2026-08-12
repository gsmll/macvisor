/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 05: 0x2b6ce0-0x2bd4e4 — the object/string Swift-runtime region.
 * All names are estimates unless string/header-matched. Uses seL4/cL4
 * vocabulary where kernel-relevant; the bulk is embedded Swift stdlib
 * (String/Array/UnsafeBufferPointer index arithmetic, Unicode grapheme /
 * general-category tables, UInt buffer bit manipulation) plus a family of
 * heavy object-service dispatch loops (heavy indirect call through method
 * tables, marked sk_object_service_*).
 *
 * Calling convention: most bodies show `void FUN(void)` because every
 * argument (including the Swift `self`/`this` and container pointers) is
 * passed in registers and not modelled as a formal parameter. Where a body
 * consumes such register state we add explicit parameters named by their
 * role (str, buf, index, flags...) so the logic reads in English; Ghidra
 * FUN_ names and unaff_ register aliases are kept in comments only.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;

/* Swift runtime 16-byte (x0:x1) result pair. */
typedef struct sk_pair { uint64_t lo; uint64_t hi; } sk_pair_t;

/* Generic opaque function pointer used for indirect dispatch. */
typedef void (*sk_fn_t)();

#define CL4_FATAL() __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 / Swift-runtime helpers (bodies reconstructed by the
 * range workers that own them). Signatures reflect observed register use.
 * Pair-returning helpers yield a 16-byte (x0:x1) result.
 * ------------------------------------------------------------------ */
extern unsigned long FUN_00002534();
extern unsigned long FUN_00002834();
extern unsigned long FUN_00012568();
extern unsigned long FUN_00019858();
extern unsigned long FUN_0001a1c8();
extern sk_pair_t FUN_0001df60();
extern unsigned long FUN_00027754();
extern unsigned long FUN_000651bc();
extern unsigned long FUN_00068e14();
extern unsigned long FUN_0006b2ec();
extern unsigned long FUN_0006b42c();
extern unsigned long FUN_0006b6f4();
extern unsigned long FUN_0006e778();
extern unsigned long FUN_0006f768();
extern unsigned long FUN_00077894();
extern unsigned long FUN_000778b4();
extern unsigned long FUN_0007c1a4();
extern unsigned long FUN_0007c1c4();
extern unsigned long FUN_000824c4();
extern unsigned long FUN_000839d8();
extern unsigned long FUN_0008412c();
extern sk_pair_t FUN_00084180();
extern sk_pair_t FUN_00084220();
extern unsigned long FUN_00084234();
extern unsigned long FUN_000863bc();
extern unsigned long FUN_0008e388();
extern unsigned long FUN_0008e500();
extern sk_pair_t FUN_0008e518();
extern unsigned long FUN_0008f6c0();
extern sk_pair_t FUN_0008f6f4();
extern unsigned long FUN_0008f728();
extern unsigned long FUN_0008f758();
extern sk_pair_t FUN_0009461c();
extern unsigned long FUN_000a68c4();
extern unsigned long FUN_000a6e14();
extern unsigned long FUN_000a6f68();
extern unsigned long FUN_000a6f88();
extern unsigned long FUN_000aa46c();
extern unsigned long FUN_000aa47c();
extern unsigned long FUN_000b4390();
extern unsigned long FUN_000b43d0();
extern unsigned long FUN_000bd3a4();
extern unsigned long FUN_000dbf08();
extern sk_pair_t FUN_000e15d8();
extern sk_pair_t FUN_000e72b0();
extern unsigned long FUN_00100efc();
extern unsigned long FUN_0011aa70();
extern unsigned long FUN_0011d7e8();
extern unsigned long FUN_0016186c();
extern unsigned long FUN_00167404();
extern unsigned long FUN_001676cc();
extern unsigned long FUN_001679cc();
extern unsigned long FUN_0019c9cc();
extern unsigned long FUN_0019e690();
extern unsigned long FUN_0019fd10();
extern sk_pair_t FUN_001a26e0();
extern unsigned long FUN_001a4b5c();
extern sk_pair_t FUN_001a89a8();
extern unsigned long FUN_001ac288();
extern sk_pair_t FUN_001ac3d8();
extern unsigned long FUN_001afa84();
extern unsigned long FUN_001afe4c();
extern unsigned long FUN_001b5784();
extern unsigned long FUN_001b5a88();
extern unsigned long FUN_001e088c();
extern unsigned long FUN_001e3a28();
extern sk_pair_t FUN_001e3f70();
extern unsigned long FUN_001e4b00();
extern unsigned long FUN_00206770();
extern sk_pair_t FUN_002366a0();
extern unsigned long FUN_00255738();
extern unsigned long FUN_00267820();
extern sk_pair_t FUN_00271778();
extern unsigned long FUN_00271d58();
extern sk_pair_t FUN_00272a98();
extern unsigned long FUN_00272c58();
extern unsigned long FUN_002738f0();
extern sk_pair_t FUN_00274128();
extern unsigned long FUN_00274290();
extern unsigned long FUN_00276514();
extern unsigned long FUN_002765a0();
extern unsigned long FUN_00284424();
extern sk_pair_t FUN_0028ef70();
extern sk_pair_t FUN_00291ee0();
extern unsigned long FUN_0029af30();
extern unsigned long FUN_002a2698();
extern sk_pair_t FUN_002a3e64();
extern sk_pair_t FUN_002a49a8();
extern unsigned long FUN_002a4c98();
extern unsigned long FUN_002a74f8();
extern unsigned long FUN_002a7c00();
extern unsigned long FUN_002a7f58();
extern unsigned long FUN_002a95b4();
extern unsigned long FUN_002a9ba8();
extern unsigned long FUN_002a9f3c();
extern unsigned long FUN_002ab130();
extern unsigned long FUN_002ab4d4();
extern unsigned long FUN_002ab5bc();
extern unsigned long FUN_002ab6a0();
extern sk_pair_t FUN_002ac99c();
extern unsigned long FUN_002ae098();
extern unsigned long FUN_002af340();
extern unsigned long FUN_002b3978();
extern sk_pair_t FUN_002b39b4();
extern unsigned long FUN_002b3b84();
extern unsigned long FUN_002b439c();
extern unsigned long FUN_002b64cc();
extern unsigned long FUN_002b6630();
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
extern unsigned long FUN_00310f34();
extern unsigned long FUN_00319688();
extern unsigned long FUN_00319778();
extern unsigned long FUN_0031b900();
extern unsigned long FUN_0031c964();
extern unsigned long FUN_0031dc0c();
extern unsigned long FUN_0031e084();
extern unsigned long FUN_0031e0d4();
extern unsigned long FUN_0031e104();
extern unsigned long FUN_0031e15c();
extern unsigned long FUN_0031e18c();
extern unsigned long FUN_003244b4();
extern unsigned long FUN_00348074();
extern unsigned long FUN_00348194();
extern unsigned long FUN_003482c4();
extern unsigned long FUN_0034846c();
extern unsigned long FUN_00348614();
extern unsigned long FUN_003486b8();
extern unsigned long FUN_0034883c();
extern unsigned long FUN_00348a18();
extern unsigned long FUN_00348a80();
extern unsigned long FUN_00348a9c();
extern unsigned long FUN_00348c84();
extern unsigned long FUN_00348cd0();
extern unsigned long FUN_00348d64();
extern unsigned long FUN_00348e18();
extern unsigned long FUN_00348f50();
extern unsigned long FUN_00348fb4();
extern unsigned long FUN_003490d0();
extern unsigned long FUN_003490ec();
extern unsigned long FUN_0034911c();
extern unsigned long FUN_003492ac();
extern unsigned long FUN_00349370();
extern unsigned long FUN_003493c4();
extern unsigned long FUN_003494e8();
extern unsigned long FUN_003494fc();
extern unsigned long FUN_003495a8();
extern unsigned long FUN_00349618();
extern unsigned long FUN_003496cc();
extern unsigned long FUN_0034975c();
extern unsigned long FUN_003497b4();
extern unsigned long FUN_003497c8();
extern unsigned long FUN_003497ec();
extern unsigned long FUN_00349830();
extern unsigned long FUN_0034987c();
extern unsigned long FUN_00349890();
extern unsigned long FUN_003498a8();
extern unsigned long FUN_00349944();
extern unsigned long FUN_0034998c();
extern unsigned long FUN_003499f0();
extern unsigned long FUN_00349a18();
extern unsigned long FUN_00349b00();
extern unsigned long FUN_00349dfc();
extern unsigned long FUN_00349fcc();
extern unsigned long FUN_0034a018();
extern unsigned long FUN_0034a1f8();
extern unsigned long FUN_0034a260();
extern unsigned long FUN_0034a390();
extern unsigned long FUN_0034a798();
extern unsigned long FUN_0034a7ac();
extern unsigned long FUN_0034a900();
extern unsigned long FUN_0034aaf4();
extern unsigned long FUN_0034ab20();
extern unsigned long FUN_0034abec();
extern unsigned long FUN_0034ac00();
extern unsigned long FUN_0034ac50();
extern unsigned long FUN_0034ad00();
extern unsigned long FUN_0034ae58();
extern unsigned long FUN_0034ae80();
extern unsigned long FUN_0034aebc();
extern unsigned long FUN_0034aee4();
extern unsigned long FUN_0034aef4();
extern unsigned long FUN_0034af04();
extern unsigned long FUN_0034af20();
extern unsigned long FUN_0034b05c();
extern unsigned long FUN_0034b0b4();
extern unsigned long FUN_0034b0c4();
extern unsigned long FUN_0034b0d4();
extern unsigned long FUN_0034b278();
extern unsigned long FUN_0034b318();
extern unsigned long FUN_0034b348();
extern unsigned long FUN_0034b368();
extern unsigned long FUN_0034b3c8();
extern unsigned long FUN_0034b3d8();
extern unsigned long FUN_0034b3f8();
extern unsigned long FUN_0034b4c0();
extern unsigned long FUN_0034b508();
extern unsigned long FUN_0034b540();
extern unsigned long FUN_0034b6b8();
extern unsigned long FUN_0034b6f4();
extern unsigned long FUN_0034b768();
extern unsigned long FUN_0034b778();
extern unsigned long FUN_0034b848();
extern unsigned long FUN_0034b89c();
extern unsigned long FUN_0034b9f8();
extern unsigned long FUN_0034ba28();
extern unsigned long FUN_0034ba68();
extern unsigned long FUN_0034ba98();
extern unsigned long FUN_0034baa8();
extern unsigned long FUN_0034bc04();
extern unsigned long FUN_0034bc6c();
extern unsigned long FUN_0034bcf0();
extern unsigned long FUN_0034bd90();
extern unsigned long FUN_0034bdcc();
extern unsigned long FUN_0034be54();
extern unsigned long FUN_0034bec4();
extern unsigned long FUN_0034bf1c();
extern unsigned long FUN_0034bf64();
extern unsigned long FUN_0034c034();
extern unsigned long FUN_0034c0a4();
extern unsigned long FUN_0034c1f8();
extern unsigned long FUN_0034c3d4();
extern unsigned long FUN_0034c424();
extern unsigned long FUN_0034c434();
extern unsigned long FUN_0034c4bc();
extern unsigned long FUN_0034c5bc();
extern unsigned long FUN_0034c5cc();
extern unsigned long FUN_0034c61c();
extern unsigned long FUN_0034c694();
extern unsigned long FUN_0034c6b4();
extern unsigned long FUN_0034c6e4();
extern unsigned long FUN_0034c9e8();
extern unsigned long FUN_0034ca28();
extern unsigned long FUN_0034cd90();
extern unsigned long FUN_0034cde8();
extern unsigned long FUN_0034cea8();
extern unsigned long FUN_0034cec4();
extern unsigned long FUN_0034ced8();
extern unsigned long FUN_0034cf74();
extern sk_pair_t FUN_0034d090();
extern unsigned long FUN_0034d150();
extern unsigned long FUN_0034d294();
extern unsigned long FUN_0034d354();
extern unsigned long FUN_0034d558();
extern sk_pair_t FUN_0034d810();
extern unsigned long FUN_0034d8e4();
extern unsigned long FUN_0034d970();
extern unsigned long FUN_0034d98c();
extern unsigned long FUN_0034db38();
extern unsigned long FUN_0034db98();
extern unsigned long FUN_0034dbe8();
extern unsigned long FUN_0034dd74();
extern unsigned long FUN_0034df04();
extern unsigned long FUN_0034df64();
extern unsigned long FUN_0034df94();
extern unsigned long FUN_0034e0e4();
extern unsigned long FUN_0034e1d0();
extern unsigned long FUN_0034e208();
extern unsigned long FUN_0034e238();
extern unsigned long FUN_0034e68c();
extern unsigned long FUN_0034e74c();
extern unsigned long FUN_0034ed58();
extern unsigned long FUN_0034ed98();
extern unsigned long FUN_0034edc8();
extern unsigned long FUN_0034ef08();
extern unsigned long FUN_0034f064();
extern unsigned long FUN_0034f198();
extern unsigned long FUN_0034f2c4();
extern unsigned long FUN_0034f4b4();
extern unsigned long FUN_0034f554();
extern unsigned long FUN_0034f584();
extern unsigned long FUN_0034f8d0();
extern unsigned long FUN_0034f98c();
extern unsigned long FUN_0034fb60();
extern unsigned long FUN_0034fbb0();
extern unsigned long FUN_0034fd4c();
extern unsigned long FUN_0034fdac();
extern unsigned long FUN_00350058();
extern unsigned long FUN_0035013c();
extern unsigned long FUN_00350298();
extern unsigned long FUN_003502d8();
extern unsigned long FUN_00350410();
extern sk_pair_t FUN_0035041c();
extern unsigned long FUN_00350428();
extern unsigned long FUN_0035044c();
extern unsigned long FUN_00350464();
extern unsigned long FUN_003504a0();
extern unsigned long FUN_003504ac();
extern sk_pair_t FUN_003504c4();
extern sk_pair_t FUN_003504f4();
extern unsigned long FUN_00350518();
extern sk_pair_t FUN_00350524();
extern unsigned long FUN_00350560();
extern unsigned long FUN_003505c4();
extern unsigned long FUN_003505dc();
extern unsigned long FUN_003505e8();
extern unsigned long FUN_0035060c();
extern unsigned long FUN_00350630();
extern unsigned long FUN_0035063c();
extern unsigned long FUN_0035066c();
extern unsigned long FUN_00350738();
extern unsigned long FUN_00350744();
extern sk_pair_t FUN_003507bc();
extern unsigned long FUN_003507e0();
extern unsigned long FUN_003508b4();
extern unsigned long FUN_003508cc();
extern sk_pair_t FUN_003508f0();
extern unsigned long FUN_00350908();
extern unsigned long FUN_00350914();
extern unsigned long FUN_00350950();
extern unsigned long FUN_00350968();
extern unsigned long FUN_003509d4();
extern sk_pair_t FUN_003509e0();
extern unsigned long FUN_003509f8();
extern unsigned long FUN_00350a1c();
extern unsigned long FUN_00350a28();
extern unsigned long FUN_00350a4c();
extern unsigned long FUN_00350a7c();
extern unsigned long FUN_00350aac();
extern unsigned long FUN_00350ab8();
extern unsigned long FUN_00350af4();
extern unsigned long FUN_00350b00();
extern unsigned long FUN_00350b24();
extern unsigned long FUN_00350b48();
extern unsigned long FUN_00350b54();
extern unsigned long FUN_00350b6c();
extern unsigned long FUN_00350b84();
extern unsigned long FUN_00350b90();
extern unsigned long FUN_00350bcc();
extern unsigned long FUN_00350bfc();
extern unsigned long FUN_00350c8c();
extern unsigned long FUN_00350d94();
extern unsigned long FUN_00350df4();
extern unsigned long FUN_00350e14();
extern unsigned long FUN_00350ed0();
extern unsigned long FUN_00350edc();
extern unsigned long FUN_00350f0c();
extern unsigned long FUN_0035102c();
extern unsigned long FUN_003510b8();
extern unsigned long FUN_003510c4();
extern unsigned long FUN_003510dc();
extern unsigned long FUN_00351124();
extern unsigned long FUN_00351130();
extern unsigned long FUN_00351154();
extern sk_pair_t FUN_00351160();
extern unsigned long FUN_00351184();
extern unsigned long FUN_00351190();
extern unsigned long FUN_003511c0();
extern unsigned long FUN_0035125c();
extern unsigned long FUN_00351274();
extern unsigned long FUN_003512c0();
extern sk_pair_t FUN_00351324();
extern sk_pair_t FUN_00351330();
extern unsigned long FUN_003513a8();
extern unsigned long FUN_003513e4();
extern unsigned long FUN_00351488();
extern unsigned long FUN_003514b8();
extern unsigned long FUN_00351584();
extern unsigned long FUN_003515fc();
extern unsigned long FUN_0035163c();
extern unsigned long FUN_00351714();
extern unsigned long FUN_003517cc();
extern unsigned long FUN_003518f4();
extern unsigned long FUN_00351918();
extern unsigned long FUN_00351990();
extern unsigned long FUN_003519fc();
extern unsigned long FUN_00351a20();
extern unsigned long FUN_00351a50();
extern unsigned long FUN_00351aec();
extern unsigned long FUN_00351b44();
extern unsigned long FUN_00351b78();
extern unsigned long FUN_00351be0();
extern unsigned long FUN_00351bec();
extern unsigned long FUN_00351c34();
extern unsigned long FUN_00351c58();
extern unsigned long FUN_00351c7c();
extern unsigned long FUN_00351cb8();
extern unsigned long FUN_00351da8();
extern unsigned long FUN_00351e3c();
extern unsigned long FUN_00351ee0();
extern unsigned long FUN_00351f28();
extern unsigned long FUN_00351f70();
extern unsigned long FUN_00351f7c();
extern unsigned long FUN_00352128();
extern unsigned long FUN_00352320();
extern unsigned long FUN_00352340();
extern unsigned long FUN_0035237c();
extern sk_pair_t FUN_0035239c();
extern unsigned long FUN_003523e0();
extern unsigned long FUN_003523f0();
extern unsigned long FUN_00352420();
extern unsigned long FUN_0035272c();
extern unsigned long FUN_00352834();
extern unsigned long FUN_00352894();
extern unsigned long FUN_003528cc();
extern unsigned long FUN_00352980();
extern unsigned long FUN_00352b20();
extern unsigned long FUN_00352c10();
extern unsigned long FUN_00352c28();
extern unsigned long FUN_00352c80();
extern unsigned long FUN_00352d10();
extern unsigned long FUN_00352d4c();
extern unsigned long FUN_00352d70();
extern unsigned long FUN_00352e24();
extern unsigned long FUN_00352e3c();
extern unsigned long FUN_00352e54();
extern unsigned long FUN_00353178();
extern unsigned long FUN_003531e4();
extern unsigned long FUN_003531fc();
extern unsigned long FUN_00353480();
extern unsigned long FUN_003534a4();
extern sk_pair_t FUN_00353510();
extern unsigned long FUN_00353850();
extern unsigned long FUN_00353878();
extern unsigned long FUN_003538b0();
extern unsigned long FUN_00353984();
extern unsigned long FUN_00353a90();
extern unsigned long FUN_00353b10();
extern unsigned long FUN_00353bd0();
extern unsigned long FUN_00353c0c();
extern unsigned long FUN_00353d44();
extern unsigned long FUN_00353d70();
extern unsigned long FUN_00353d7c();
extern unsigned long FUN_00353e08();
extern unsigned long FUN_00353f2c();
extern unsigned long FUN_0035404c();
extern unsigned long FUN_003542dc();
extern unsigned long FUN_003542e8();
extern sk_pair_t FUN_00354410();
extern unsigned long FUN_0035441c();
extern unsigned long FUN_003544c8();
extern unsigned long FUN_0035457c();
extern unsigned long FUN_0035466c();
extern sk_pair_t FUN_00354744();
extern unsigned long FUN_003547f8();
extern unsigned long FUN_003548a0();
extern unsigned long FUN_00354a4c();
extern unsigned long FUN_00354b74();
extern sk_pair_t FUN_00354d20();
extern sk_pair_t FUN_00354e0c();
extern unsigned long FUN_00354f8c();
extern unsigned long FUN_00354fac();
extern unsigned long FUN_00355418();
extern unsigned long FUN_003554e0();
extern unsigned long FUN_00355624();
extern unsigned long FUN_00355754();
extern unsigned long FUN_00355a58();
extern unsigned long FUN_00355c00();
extern unsigned long FUN_00355da8();
extern unsigned long FUN_00355f70();
extern sk_pair_t FUN_00355fa0();
extern unsigned long FUN_00356018();
extern unsigned long FUN_0035620c();
extern unsigned long FUN_003562c8();
extern unsigned long FUN_00356340();
extern unsigned long FUN_00356364();
extern unsigned long FUN_0035646c();
extern unsigned long FUN_003567ec();
extern unsigned long FUN_00356930();
extern unsigned long FUN_00356940();
extern unsigned long FUN_00356a20();
extern unsigned long FUN_00356a7c();
extern unsigned long FUN_00356a88();
extern unsigned long FUN_00356af4();
extern unsigned long FUN_00356b20();
extern unsigned long FUN_00356c78();
extern unsigned long FUN_00356c84();
extern unsigned long FUN_00357044();
extern unsigned long FUN_003577a0();
extern unsigned long FUN_00357904();
extern unsigned long FUN_00357910();
extern unsigned long FUN_00357964();
extern unsigned long FUN_003579d8();
extern unsigned long FUN_003579e8();
extern unsigned long FUN_00357b7c();
extern sk_pair_t FUN_00357fc4();
extern unsigned long FUN_00358004();
extern unsigned long FUN_00358344();
extern unsigned long FUN_00358374();
extern unsigned long FUN_003583dc();
extern unsigned long FUN_0035841c();
extern unsigned long FUN_0035849c();
extern unsigned long FUN_003585e8();
extern unsigned long FUN_003586e4();
extern unsigned long FUN_00358a20();
extern unsigned long FUN_00358ae0();
extern unsigned long FUN_00358ddc();
extern unsigned long FUN_00358f84();
extern unsigned long FUN_003593c0();
extern unsigned long FUN_0035950c();
extern unsigned long FUN_003599c0();
extern unsigned long FUN_00359cd8();
extern unsigned long FUN_0035a250();
extern unsigned long FUN_0035a334();
extern unsigned long FUN_0035a3dc();
extern unsigned long FUN_0035a478();
extern unsigned long FUN_0035a49c();
extern unsigned long FUN_0035a540();
extern unsigned long FUN_0035a70c();
extern unsigned long FUN_0035aafc();
extern unsigned long FUN_0035acfc();
extern unsigned long FUN_00369340();
extern unsigned long FUN_00369584();
extern unsigned long FUN_0036a804();
extern unsigned long FUN_0036a908();
extern unsigned long FUN_0036a940();
extern unsigned long FUN_0036a9a0();
extern unsigned long FUN_0036b118();
extern unsigned long FUN_0036b270();
extern unsigned long FUN_0036b588();
extern unsigned long FUN_0036b6ac();
extern unsigned long FUN_00376820();
extern unsigned long FUN_00377824();
extern unsigned long FUN_00377bec();
extern sk_pair_t FUN_003a25d4();
extern unsigned long FUN_003a261c();
extern unsigned long FUN_003d34b8();
extern unsigned long FUN_003d36b0();
extern unsigned long FUN_003d3838();
extern unsigned long FUN_003d38c4();
extern unsigned long FUN_003d3ac0();
extern unsigned long FUN_003d3b30();
extern unsigned long FUN_0060e3fc();
extern unsigned long FUN_0060e40c();

/* Thunk aliases referenced by this slice. */
extern unsigned long thunk_FUN_00012568();
extern unsigned long thunk_FUN_00284424();
extern unsigned long thunk_FUN_002a2698();
extern unsigned long thunk_FUN_002b3978();
extern unsigned long thunk_FUN_0036b270();

/* Swift runtime global function pointer used for opaque dispatch. */
extern sk_pair_t (*DAT_00658c00)();

/* Swift error/format string data referenced by fatal-error calls. */
extern unsigned char DAT_005be7c0[];
extern unsigned char DAT_004c1010[];
extern unsigned char DAT_00612b58[];
extern unsigned char DAT_00612b90[];
extern unsigned char DAT_00346d1c[];
extern unsigned char DAT_00346d18[];
extern unsigned char DAT_00343ca4[];
extern unsigned char DAT_00343c90[];
extern unsigned char DAT_004c05b0[];
extern unsigned char DAT_005c9984[];
extern unsigned char DAT_005d356a[];
extern unsigned char DAT_005d356c[];
extern unsigned char DAT_005d356e[];
extern unsigned char DAT_005d37c4[];
extern unsigned char DAT_005d37c6[];
extern unsigned char DAT_005d37c9[];
extern unsigned char DAT_005d37cb[];
extern unsigned char DAT_005d37d0[];
extern unsigned char DAT_005d37d2[];
extern unsigned char DAT_005d37d7[];
extern unsigned char DAT_005d37d9[];
extern unsigned char DAT_005d37dc[];
extern unsigned char DAT_005d37e1[];
extern unsigned char DAT_005d37e3[];
extern unsigned char DAT_005d37e5[];
extern unsigned char DAT_005d37e9[];
extern unsigned char DAT_005d37eb[];
extern unsigned char DAT_005d37ed[];
extern unsigned char DAT_005d37f0[];
extern unsigned char DAT_005d37f3[];
extern unsigned char DAT_005d37f7[];
extern unsigned char DAT_005d37fa[];
extern unsigned char DAT_005d37fe[];
extern unsigned char DAT_005d3801[];
extern unsigned char DAT_005d3803[];
extern unsigned char DAT_005d3806[];
extern unsigned char DAT_005d380a[];
extern unsigned char DAT_005d380d[];
extern unsigned char DAT_005d3810[];
extern unsigned char DAT_005d3812[];
extern unsigned char DAT_005d3816[];
extern unsigned char DAT_005d3819[];
extern unsigned char DAT_005d381c[];
extern unsigned char DAT_005d381f[];
extern unsigned char DAT_005d3822[];
extern unsigned char DAT_005d3825[];
extern unsigned char DAT_005d3828[];
extern unsigned char DAT_005d382b[];
extern unsigned char DAT_005d382e[];
extern unsigned char DAT_005d3831[];
extern unsigned char DAT_005d3834[];
extern unsigned char DAT_005d3837[];
extern unsigned char DAT_005d383a[];
extern unsigned char DAT_005d383d[];
extern unsigned char DAT_005d3840[];
extern unsigned char DAT_005d3843[];
extern unsigned char DAT_005d3846[];
extern unsigned char DAT_003471a4[];
extern unsigned char DAT_003471a8[];
extern uint64_t DAT_004e7ba0;
extern uint64_t DAT_004e7ba8;
extern uint64_t DAT_004e7bb0;
extern uint64_t DAT_004e7bb8;
extern uint64_t DAT_004e7bc0;
extern uint64_t DAT_004e7bc8;
extern unsigned int  DAT_004e7bd0;
extern unsigned int  DAT_004e7be0;
extern unsigned long DAT_004e7bf0;
extern unsigned long DAT_004e7c00;
extern void LAB_0060e404(void);
extern void LAB_00612b78(void);

/* Swift runtime fatal-error (noreturn) helper: FUN_001afe4c.
 * message/2, "Swift.Range"/... ; encodes the Swift "Fatal error" trap. */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */

/* Forward declarations of functions reconstructed in this slice. */
unsigned long sk_swift_string_utf8_view_index(void);
unsigned long sk_swift_string_utf16_index(void);
unsigned long sk_swift_string_utf8_index_dist(void);
unsigned long sk_swift_string_index_offset(uint64_t, uint64_t, uint64_t);
void sk_swift_string_shift_right(uint32_t *, uint64_t, uint64_t);
sk_pair_t sk_swift_string_buffer_create_impl(long *, unsigned int, unsigned int,
                                             long, uint64_t);
long sk_swift_stride(uint64_t, uint64_t, uint64_t);
unsigned int sk_swift_unicode_width(unsigned int);
uint8_t sk_swift_grapheme_prop_clamp(uint8_t);
void sk_swift_general_category_validate(uint8_t);
void sk_swift_grapheme_property_table_a(void *);
void sk_swift_grapheme_property_table_b(void);

/*--------------------------------------------------------------------*/
/* FUN_002b6ce0 @ 0x002b6ce0   (est. sk_swift_string_subscript_utf16)
 * Ghidra: undefined1 [16] FUN_002b6ce0(undefined2 *param_1, undefined8 *param_2)
 * Looks up a UTF-16 code unit at the given string argument (register x20),
 * stores it to *out, and returns the 16-byte pair {FUN_0001a1c8(), out}.
 * Confidence: low (thin wrapper; helper resolves the element).
 */
sk_pair_t sk_swift_string_subscript_utf16(uint16_t *out, uint64_t *argsw)
{
    uint16_t cu = (uint16_t)FUN_002b64cc(*argsw, argsw[0], argsw[1], argsw[2], argsw[3]);
    *out = cu;
    sk_pair_t r;
    r.hi = (uint64_t)out;
    r.lo = FUN_0001a1c8();
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002b6d48 @ 0x002b6d48   (est. sk_swift_string_subscript)
 * Ghidra: void FUN_002b6d48(undefined8 *param_1, undefined8 *param_2,
 *                           undefined8 param_3, undefined8 param_4)
 * Computes a string element via FUN_002b6630 and stores it to *out.
 * Confidence: low.
 */
void sk_swift_string_subscript(uint64_t *out, uint64_t *argsw, uint64_t p3, uint64_t p4)
{
    uint64_t v = FUN_002b6630(*argsw, p3, p4, *(uint64_t *)(argsw + 2), *(uint64_t *)(argsw + 3));
    *out = v;
}

/*--------------------------------------------------------------------*/
/* FUN_002b6da4 @ 0x002b6da4   (est. sk_swift_grapheme_break_apply)
 * Ghidra: void FUN_002b6da4(void)
 * Applies the grapheme-cluster break state machine to the four-word
 * iterator/state block at x20. Releases the third word, then lazily
 * materializes sub-states (marking lazily-initialized flags with the low
 * bit) and writes the updated state words back.
 * Confidence: low (register state words; helpers are string break procs).
 */
void sk_swift_grapheme_break_apply(void)
{
    word_t *st = (word_t *)0;   /* x20 block (4 words) */
    word_t w0, w1, w2, w3;
    /* x23 = w0 flag, x22 = w1 flag, x21 = w2, x19 = w3 (register-resident) */
    (void)st; (void)w0; (void)w1; (void)w2; (void)w3;
    FUN_00349a18();
    FUN_003a25d4(/*st[3]*/0);
    /* (unaff_x23 & 1) == 0 -> lazy init path */
    if ((0 & 1) == 0) {
        FUN_0034edc8();
        FUN_001676cc();
        FUN_00353850();
        /* w0 = extraout_x8 | 1; */
    }
    if ((0 & 1) == 0) {
        FUN_0034b778();
        FUN_001676cc();
        FUN_0034c1f8();
    }
    /* write-back of the four state words omitted: register-resident */
}

/*--------------------------------------------------------------------*/
/* FUN_002b6e10 @ 0x002b6e10   (est. sk_swift_grapheme_break_apply2)
 * Ghidra: void FUN_002b6e10(void)
 * Second grapheme-break application: lazy sub-state materialization on two
 * register flag words, then a buffer release.
 * Confidence: low.
 */
void sk_swift_grapheme_break_apply2(void)
{
    FUN_00349fcc();
    if ((0 & 1) == 0) {
        FUN_0034ba28();
        FUN_001676cc();
        FUN_0034c1f8();
    }
    if ((0 & 1) == 0) {
        FUN_0011aa70();
        FUN_001676cc();
        FUN_0034fb60();
    }
    FUN_0008412c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b6e64 @ 0x002b6e64   (est. sk_swift_alloc_string_impl)
 * Ghidra: void FUN_002b6e64(void)
 * Allocates a string object: reads a size from FUN_0035a250, allocates
 * tag 0xb962 via the zone allocator, then runs the object setup chain.
 * Confidence: low.
 */
void sk_swift_alloc_string_impl(void)
{
    uint64_t size = FUN_0035a250();
    FUN_0036a908(size, 0xb962);
    FUN_0034cd90();
    thunk_FUN_0036b270();
    FUN_003507e0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b6ed0 @ 0x002b6ed0   (est. sk_swift_string_append)
 * Ghidra: void FUN_002b6ed0(undefined8 param_1, undefined8 param_2, code *param_3)
 * Appends one string to a growable buffer described by the pair returned
 * from FUN_00084220. Either updates the buffer's tail words in place or,
 * when the buffer is shared/non-exclusive, allocates a fresh 16-byte
 * element via the callback (param_3) and relinks it, releasing the old
 * storage.
 * Confidence: low (growable Swift string append; heavy register state).
 */
void sk_swift_string_append(uint64_t p1, uint64_t p2, void (*make)(void))
{
    sk_pair_t blk = FUN_00084220();
    uint64_t *b = (uint64_t *)blk.lo;
    uint64_t w0 = b[0], w1 = b[1], w2 = b[2], w3 = b[3], w5 = b[5];
    if ((blk.hi & 1) == 0) {
        FUN_003a25d4(w5);
        if ((w0 & 1) == 0) {
            FUN_0034b768();
            FUN_001676cc();
            FUN_0034c1f8();
        }
        if ((w1 & 1) == 0) {
            FUN_0034c694();
            FUN_001676cc();
            FUN_00353850();
            w1 = /*extraout_x8 |*/ 1;
        }
        uint64_t *tail = (uint64_t *)b[4];
        tail[0] = w0; tail[1] = w1; tail[2] = w2; tail[3] = w3;
    } else {
        uint8_t *dst = (uint8_t *)b[4];
        thunk_FUN_0036b270(w3);
        FUN_003a25d4(w5);
        FUN_0034c6b4();
        sk_pair_t nb = (*(sk_pair_t (*)(void))make)();
        ((uint64_t *)dst)[0] = nb.lo;
        ((uint64_t *)dst)[1] = nb.hi;
        *(void **)(dst + 16) = make;
        *(uint64_t *)(dst + 24) = w3;
        FUN_003a25d4(b[3]);
    }
    FUN_00084234(b, /*unaff_x30*/ 0);
    thunk_FUN_00012568();
}

/*--------------------------------------------------------------------*/
/* FUN_002b6fac @ 0x002b6fac   (est. sk_swift_string_append_ascii)
 * Ghidra: void FUN_002b6fac(void)
 * Appends ASCII content: retries the append after a sub-state check and,
 * on success, performs the element write via an indirect callback,
 * releasing the temporary buffer word.
 * Confidence: low (indirect call at 0x002b6fd4; not recoverable).
 */
void sk_swift_string_append_ascii(void)
{
    FUN_00349a18();
    FUN_00351488();
    uint64_t ok = FUN_002af340();
    if ((ok & 1) != 0) {
        FUN_0034b778();
        ok = FUN_002af340();
        if ((ok & 1) != 0) {
            FUN_000aa47c();
            (*(void (*)(void))/*in_x4*/0)();
            FUN_002a3e64();
            FUN_00351a50();
            FUN_003a25d4(/*in_x3*/ 0);
            goto done;
        }
    }
    FUN_003a25d4();
done:
    FUN_0009461c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7030 @ 0x002b7030   (est. sk_swift_grapheme_break_apply3)
 * Ghidra: void FUN_002b7030(void)
 * Third grapheme-break state application (lazy sub-state on two flag
 * words) followed by buffer release.
 * Confidence: low.
 */
void sk_swift_grapheme_break_apply3(void)
{
    FUN_0034ed98();
    if ((0 & 1) == 0) {
        FUN_0034ba28();
        FUN_001676cc();
        FUN_0034c1f8();
    }
    if ((0 & 1) == 0) {
        FUN_0011aa70();
        FUN_001676cc();
        FUN_0034fb60();
    }
    FUN_0008412c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7088 @ 0x002b7088   (est. sk_swift_string_utf8_view_index)
 * Ghidra: ulong FUN_002b7088(void)
 * Computes the UTF-8 view index for a string: decodes the string's tag
 * bits (0x3c/0x3d) to pick the storage/encoding path, computes an offset
 * into the buffer, and merges width bits. Raises a Swift fatal error on a
 * non-representable index.
 * Confidence: low (register-decoded string state; unrecovered switch at
 *   0x002b70e8).
 */
unsigned long sk_swift_string_utf8_view_index(void)
{
    FUN_00351da8();
    uint64_t off = FUN_002ab4d4();
    /* register-resident string tag words x19/x20 */
    if ((/*x19*/ 0 >> 0x3c & 1) != 0) {
        FUN_0035646c();
        FUN_0034883c();
        FUN_001afa84();           /* fatal, no return */
    }
    if ((/*x19*/ 0 >> 0x3d & 1) == 0) {
        uint64_t base;
        if ((/*x20*/ 0 >> 0x3c & 1) == 0) {
            FUN_0007c1c4();
            base = FUN_002a9ba8();
        } else {
            base = FUN_00356364();
        }
        uint64_t r = FUN_00355da8(base + (off >> 0x10));
        /* ... switch on error code (unrecovered) returns width-merged value */
        return r;
    }
    return FUN_00355da8(/*stack base*/ 0 + (off >> 0x10));
}

/*--------------------------------------------------------------------*/
/* FUN_002b71c4 @ 0x002b71c4   (est. sk_swift_string_utf16_index)
 * Ghidra: ulong FUN_002b71c4(void)
 * Computes a UTF-16 code-unit index into the string: selects the storage
 * path from the tag bits, adds the unit offset, and packs width bits into
 * the returned word.
 * Confidence: low.
 */
unsigned long sk_swift_string_utf16_index(void)
{
    FUN_00351da8();
    FUN_00353178();
    uint64_t off = FUN_00167404();
    uint64_t acc;
    if ((/*x19*/ 0 >> 0x3c & 1) == 0) {
        acc = off >> 0x10;
        if ((/*x19*/ 0 >> 0x3d & 1) != 0) {
            FUN_00354fac();
            goto finish;
        }
        if ((/*x20*/ 0 >> 0x3c & 1) != 0) {
            FUN_00356364();
            goto finish;
        }
    } else {
        FUN_002a49a8();
    }
    FUN_0007c1c4();
    FUN_002a9ba8();
finish:
    FUN_0034b3f8();
    return (acc + /*extraout_x8*/ 0) * 0x10000 | 5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b723c @ 0x002b723c   (est. sk_swift_string_utf8_index_get)
 * Ghidra: void FUN_002b723c(void)
 * Fetches a UTF-8 index byte: resolves the storage base, reads the byte
 * at the unit offset, and packs width bits into *x19.
 * Confidence: low.
 */
void sk_swift_string_utf8_index_get(void)
{
    FUN_00353d70();
    FUN_00352b20();
    FUN_00353178();
    uint64_t off = FUN_00167404();
    uint8_t byte;
    uint64_t acc;
    if ((/*x20*/ 0 >> 0x3c & 1) == 0) {
        acc = off >> 0x10;
        if ((/*x20*/ 0 >> 0x3d & 1) != 0) {
            byte = ((uint8_t *)/*stack*/0)[acc];
            goto finish;
        }
        if ((/*x21*/ 0 >> 0x3c & 1) == 0) goto linear;
        FUN_003542dc();
    } else {
        FUN_002a49a8();
linear:
        FUN_000b43d0();
        FUN_002a9ba8();
    }
    byte = *(uint8_t *)(/*base*/ 0 + acc);
finish:
    FUN_0034b3f8(byte);
    *(word_t *)0 = (acc + /*extraout_x8*/ 0) * 0x10000 | 5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b72c8 @ 0x002b72c8   (est. sk_swift_string_subscript_proxy)
 * Ghidra: void FUN_002b72c8(undefined8 p1..p6)
 * Thin proxy that forwards a string subscript to FUN_002a9f3c.
 * Confidence: low.
 */
unsigned long sk_swift_string_subscript_proxy(uint64_t p1, uint64_t p2, uint64_t p3,
                                                uint64_t p4, uint64_t p5, uint64_t p6)
{
    return FUN_002a9f3c(p1, p2, p5, p6);
}

/*--------------------------------------------------------------------*/
/* FUN_002b72f0 @ 0x002b72f0   (est. sk_swift_string_utf8_index_dist)
 * Ghidra: ulong FUN_002b72f0(void)
 * Computes the distance (in UTF-8 code units) to a string index: resolves
 * the storage base from the tag bits, scans the scalar at the offset, and
 * returns the index packed with width bits. Traps (fatal) if the index
 * overflows the buffer.
 * Confidence: low (unrecovered loop at 0x002b7370).
 */
unsigned long sk_swift_string_utf8_index_dist(void)
{
    FUN_00353d70();
    FUN_00353178();
    uint64_t off = FUN_002ab130();
    if (off >> 0xe == 0) {
        FUN_00348614(1);
        FUN_0034987c();
        FUN_001afe4c();            /* Fatal error, no return */
    }
    long step;
    if ((/*x20*/ 0 >> 0x3c & 1) == 0) {
        if ((/*x20*/ 0 >> 0x3d & 1) != 0) {
            FUN_00353878();
            uint32_t c = (uint32_t)*(uint8_t *)(/*base*/ 0 + (off >> 0x10) - 1);
            step = (c >= 0xbf && c < 0xc1) ? 1 : 1;
            goto done;
        }
        if ((/*x21*/ 0 >> 0x3c & 1) == 0) goto linear;
        FUN_003542dc();
    } else {
        FUN_0034bf1c();
        FUN_002ae098();
linear:
        FUN_000b43d0();
        FUN_002a9ba8();
    }
    step = -/*extraout_x8*/ 0;
done:
    return off + step * -0x10000 & 0xffffffffffff0000 | 5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b73cc @ 0x002b73cc   (est. sk_swift_string_utf8_index_dist_store)
 * Ghidra: void FUN_002b73cc(void)
 * As sk_swift_string_utf8_index_dist but stores the result word to *x19.
 * Confidence: low.
 */
void sk_swift_string_utf8_index_dist_store(void)
{
    FUN_00352b20();
    FUN_00353178();
    uint64_t off = FUN_002ab130();
    if (off >> 0xe == 0) {
        FUN_00348614(1);
        FUN_0034987c();
        FUN_001afe4c();            /* Fatal error, no return */
    }
    long step;
    if ((/*x4*/ 0 >> 0x3c & 1) == 0) {
        if ((/*x4*/ 0 >> 0x3d & 1) != 0) {
            step = 1;
            goto done;
        }
        if ((/*x3*/ 0 >> 0x3c & 1) == 0) goto linear;
        FUN_003577a0();
    } else {
        FUN_00077894(off);
        FUN_002ae098();
linear:
        FUN_00100efc();
        FUN_002a9ba8();
    }
    step = -/*extraout_x8*/ 0;
done:
    *(word_t *)0 = off + step * -0x10000 & 0xffffffffffff0000 | 5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b74c0 @ 0x002b74c0   (est. sk_swift_string_proc_b)
 * Ghidra: void FUN_002b74c0(void)
 * Calls the string advance helper FUN_002ab5bc through a register-held
 * pointer, then the teardown chain.
 * Confidence: low.
 */
void sk_swift_string_proc_b(void)
{
    void (*adv)(void) = (void (*)(void))FUN_002ab5bc;
    FUN_00352e54();
    adv();
    FUN_003523e0();
    thunk_FUN_0036b270();
    FUN_0034aebc();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7514 @ 0x002b7514   (est. sk_swift_string_subscript_b)
 * Ghidra: void FUN_002b7514(undefined8 *param_1, undefined8 *param_2, ...)
 * Wraps sk_swift_string_utf8_index_dist into *out.
 * Confidence: low.
 */
void sk_swift_string_subscript_b(uint64_t *out, uint64_t *argsw, uint64_t p3, uint64_t p4)
{
    *out = sk_swift_string_utf8_index_dist();
}

/*--------------------------------------------------------------------*/
/* FUN_002b754c @ 0x002b754c   (est. sk_swift_string_index_init)
 * Ghidra: void FUN_002b754c(void)
 * Initializes a string index from the subscript proxy result.
 * Confidence: low.
 */
void sk_swift_string_index_init(void)
{
    FUN_00351124();
    uint64_t v = sk_swift_string_subscript_proxy(0, 0, 0, 0, 0, 0);
    *(uint64_t *)0 = v;   /* x19 out */
}

/*--------------------------------------------------------------------*/
/* FUN_002b75a0 @ 0x002b75a0   (est. sk_swift_string_utf8_view_pair)
 * Ghidra: undefined1 [16] FUN_002b75a0(undefined4 *param_1, undefined8 *param_2)
 * Wraps sk_swift_string_utf8_view_index, storing the u32 result to *out
 * and returning the 16-byte pair {FUN_0001a1c8(), out}.
 * Confidence: low.
 */
sk_pair_t sk_swift_string_utf8_view_pair(uint32_t *out, uint64_t *argsw)
{
    uint32_t v = (uint32_t)sk_swift_string_utf8_view_index();
    *out = v;
    sk_pair_t r;
    r.hi = (uint64_t)out;
    r.lo = FUN_0001a1c8();
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002b7620 @ 0x002b7620   (est. sk_swift_string_proc_c)
 * Ghidra: void FUN_002b7620(void)
 * Builds a pair via FUN_00353510 and forwards it through an indirect
 * callback with the x20 string words.
 * Confidence: low.
 */
void sk_swift_string_proc_c(void)
{
    sk_pair_t p = FUN_00353510();
    (*(void (*)(uint64_t, uint64_t, uint64_t, uint64_t))/*extraout_x9*/0)
        (p.lo, p.hi, *(uint64_t *)((uint64_t)0 + 0x10), *(uint64_t *)((uint64_t)0 + 0x18));
    FUN_003554e0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7660 @ 0x002b7660   (est. sk_swift_string_proc_d)
 * Ghidra: void FUN_002b7660(void)
 * Calls FUN_0034c434 then an indirect callback, then FUN_0035272c.
 * Confidence: low.
 */
void sk_swift_string_proc_d(void)
{
    FUN_0034c434();
    (*(void (*)(void))/*extraout_x9*/0)();
    FUN_0035272c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7694 @ 0x002b7694   (est. sk_swift_string_index_b)
 * Ghidra: void FUN_002b7694(undefined8 *param_1, undefined8 *param_2, ...)
 * Wraps sk_swift_string_utf16_index into *out.
 * Confidence: low.
 */
void sk_swift_string_index_b(uint64_t *out, uint64_t *argsw, uint64_t p3, uint64_t p4)
{
    *out = sk_swift_string_utf16_index();
}

/*--------------------------------------------------------------------*/
/* FUN_002b76f0 @ 0x002b76f0   (est. sk_swift_alloc_string_b)
 * Ghidra: void FUN_002b76f0(void)
 * String allocation variant (tag DAT_0000fce1).
 * Confidence: low.
 */
void sk_swift_alloc_string_b(void)
{
    uint64_t size = FUN_0035a250();
    FUN_0036a908(size, 0xfce1);
    FUN_0034cd90();
    thunk_FUN_0036b270();
    FUN_003507e0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7744 @ 0x002b7744   (est. sk_swift_string_release_proc)
 * Ghidra: void FUN_002b7744(void)
 * Releases string storage through the token-release chain.
 * Confidence: low.
 */
void sk_swift_string_release_proc(void)
{
    FUN_002a3e64();
    FUN_0034bd90();
    FUN_003a25d4();
    FUN_0006b6f4();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7794 @ 0x002b7794   (est. sk_swift_string_proc_e)
 * Ghidra: void FUN_002b7794(void)
 * Builds a string advance pair and forwards it with the x20 words, then
 * releases the temporary storage.
 * Confidence: low.
 */
void sk_swift_string_proc_e(void)
{
    FUN_00358374();
    sk_pair_t p = FUN_0034d090();
    FUN_002ab5bc(p.lo, p.hi, *(uint64_t *)0, *(uint64_t *)(0 + 8),
                 *(uint64_t *)(0 + 16), *(uint64_t *)(0 + 24));
    FUN_00351aec();
    FUN_002a95b4();
    FUN_00358344(/*unaff_x30*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7808 @ 0x002b7808   (est. sk_swift_string_proc_f)
 * Ghidra: void FUN_002b7808(void)
 * Forwards a pair from FUN_0035239c to FUN_002a7f58 with an extra word.
 * Confidence: low.
 */
void sk_swift_string_proc_f(void)
{
    sk_pair_t p = FUN_0035239c();
    FUN_002a7f58(p.lo, p.hi, /*in_x3*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7830 @ 0x002b7830   (est. sk_swift_string_proc_g)
 * Ghidra: void FUN_002b7830(void)
 * Calls FUN_0035239c then FUN_002a7c00.
 * Confidence: low.
 */
void sk_swift_string_proc_g(void)
{
    FUN_0035239c();
    FUN_002a7c00();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7884 @ 0x002b7884   (est. sk_swift_buffer_pointer_init)
 * Ghidra: void FUN_002b7884(undefined1 (*param_1) [16], undefined4 *param_2,
 *                           undefined8 p3, undefined8 p4, undefined8 p5)
 * Initializes a 16-byte UnsafeBufferPointer descriptor: fills the first
 * word pair from FUN_00271778(*param_2) and the trailing words from p4/p5.
 * Confidence: low.
 */
void sk_swift_buffer_pointer_init(sk_pair_t *out, uint32_t *count, uint64_t p3,
                                  uint64_t p4, uint64_t p5)
{
    out[0] = FUN_00271778(*count);
    ((uint64_t *)&out[1])[0] = p4;
    ((uint64_t *)&out[1])[1] = p5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b78c8 @ 0x002b78c8   (est. sk_swift_buffer_count)
 * Ghidra: void FUN_002b78c8(undefined4 *param_1, undefined8 *param_2)
 * Wraps FUN_00272c58 to yield the buffer element count.
 * Confidence: low.
 */
void sk_swift_buffer_count(uint32_t *out, uint64_t *arg)
{
    *out = (uint32_t)FUN_00272c58(*arg);
}

/*--------------------------------------------------------------------*/
/* FUN_002b78f4 @ 0x002b78f4   (est. sk_swift_debug_release_1c)
 * Ghidra: void FUN_002b78f4(undefined8 *param_1)
 * Releases a two-word descriptor with debug tag DAT_00346d1c.
 * Confidence: low.
 */
void sk_swift_debug_release_1c(uint64_t *desc)
{
    FUN_001a4b5c(desc[0], desc[1], &DAT_00346d1c);
}

/*--------------------------------------------------------------------*/
/* FUN_002b78f8 @ 0x002b78f8   (est. sk_swift_debug_release_1c_b)
 * Ghidra: void FUN_002b78f8(undefined8 *param_1)
 * Duplicate entry of sk_swift_debug_release_1c.
 * Confidence: low.
 */
void sk_swift_debug_release_1c_b(uint64_t *desc)
{
    FUN_001a4b5c(desc[0], desc[1], &DAT_00346d1c);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7928 @ 0x002b7928   (est. sk_swift_proc_74290)
 * Ghidra: void FUN_002b7928(undefined4 *param_1)
 * Fills a 5-byte result: u32 from FUN_00274290 plus a trailing byte.
 * Confidence: low.
 */
void sk_swift_proc_74290(uint32_t *out)
{
    *out = (uint32_t)FUN_00274290();
    ((uint8_t *)out)[4] = 0;   /* extraout_var byte */
}

/*--------------------------------------------------------------------*/
/* FUN_002b795c @ 0x002b795c   (est. sk_swift_proc_1ac288)
 * Ghidra: void FUN_002b795c(undefined4 *param_1)
 * Stores the u32 result of FUN_001ac288.
 * Confidence: low.
 */
void sk_swift_proc_1ac288(uint32_t *out)
{
    *out = (uint32_t)FUN_001ac288();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7988 @ 0x002b7988   (est. sk_swift_proc_738f0_a)
 * Ghidra: void FUN_002b7988(undefined8 param_1)
 * Delegates to FUN_002738f0 with string tag DAT_00343ca4.
 * Confidence: low.
 */
void sk_swift_proc_738f0_a(uint64_t p)
{
    FUN_002738f0(p, &DAT_00343ca4);
}

/*--------------------------------------------------------------------*/
/* FUN_002b798c @ 0x002b798c   (est. sk_swift_proc_738f0_a_b)
 * Ghidra: void FUN_002b798c(undefined8 param_1)
 * Duplicate of sk_swift_proc_738f0_a.
 * Confidence: low.
 */
void sk_swift_proc_738f0_a_b(uint64_t p)
{
    FUN_002738f0(p, &DAT_00343ca4);
}

/*--------------------------------------------------------------------*/
/* FUN_002b79b4 @ 0x002b79b4   (est. sk_swift_proc_276514_a)
 * Ghidra: void FUN_002b79b4(void)
 * Delegates to FUN_00276514.
 * Confidence: low.
 */
void sk_swift_proc_276514_a(void)
{
    FUN_00276514();
}

/*--------------------------------------------------------------------*/
/* FUN_002b79b8 @ 0x002b79b8   (est. sk_swift_proc_276514_a_b)
 * Ghidra: void FUN_002b79b8(void)
 * Duplicate of sk_swift_proc_276514_a.
 * Confidence: low.
 */
void sk_swift_proc_276514_a_b(void)
{
    FUN_00276514();
}

/*--------------------------------------------------------------------*/
/* FUN_002b79cc @ 0x002b79cc   (est. sk_swift_string_equal)
 * Ghidra: void FUN_002b79cc(ulong param_1, ulong param_2)
 * Compares two Swift strings (param_1/param_2) for equality. Fast path:
 * when both are small/unique the strings are retained and released; the
 * general path calls the compare helper FUN_00291ee0 and records the
 * result (0xf marker + comparison words) into the x20 result block.
 * Confidence: medium (Swift String == / compare).
 */
void sk_swift_string_equal(uint64_t s1, uint64_t s2)
{
    sk_pair_t r7;
    r7.hi = s2; r7.lo = s1;
    uint64_t res3 = 0, v1, v5;
    v1 = *(uint64_t *)0;                 /* x20[3] */
    v5 = v1;
    sk_pair_t p6 = FUN_002a3e64(/*x20[0]*/0, /*x20[1]*/0);
    uint64_t u3 = p6.hi, u2 = p6.lo;
    FUN_003a25d4(v1);
    v1 = u2 & 0xffffffffffff;
    if ((u3 & 0x2000000000000000) != 0)
        v1 = u3 >> 0x38 & 0xf;
    if (v1 == 0 && (((u2 & (u3 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        thunk_FUN_0036b270(s2);
        FUN_003a25d4(u3);
    } else {
        if ((u3 >> 0x3d & 1) == 0) {
            v5 = s1 & 0xffffffffffff;
            if ((s2 & 0x2000000000000000) != 0)
                v5 = s2 >> 0x38 & 0xf;
        } else if ((s2 >> 0x3d & 1) == 0) {
            v5 = s1 & 0xffffffffffff;
        } else {
            res3 = s1; v5 = s2;
            r7 = FUN_00291ee0(u2, u3);
            if (((uint32_t)res3 & 0xff) != 1) {
                FUN_003a25d4(u3);
                goto out;
            }
            v5 = s2 >> 0x38 & 0xf;
        }
        res3 = 0;
        FUN_002a4c98(s1, s2);
        r7 = p6;
    }
out:
    thunk_FUN_002b3978(r7.lo, r7.hi);
    *(word_t *)0 = 0xf;                    /* x20[0] */
    ((word_t *)0)[1] = /*extraout_x1*/ 0;
    ((word_t *)0)[2] = res3;
    ((word_t *)0)[3] = v5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b7af4 @ 0x002b7af4   (est. sk_swift_string_assign)
 * Ghidra: void FUN_002b7af4(void)
 * Assigns one string into a buffer block: builds the string pair,
 * materializes sub-states, forwards the result through thunk_FUN_002b3978,
 * and writes the 0xf-marker result block.
 * Confidence: low.
 */
void sk_swift_string_assign(void)
{
    FUN_00354744();
    FUN_0034b318();
    uint64_t r2 = ((uint64_t *)0)[2], r3 = ((uint64_t *)0)[3];
    FUN_002a3e64(/*x20[0]*/0, /*x20[1]*/0);
    FUN_00353a90();
    FUN_0034b508();
    FUN_002a74f8();
    thunk_FUN_002b3978(/*x24*/ 0, /*x25*/ 0);
    ((word_t *)0)[0] = 0xf;
    ((word_t *)0)[1] = /*extraout_x1*/ 0;
    ((word_t *)0)[2] = r2;
    ((word_t *)0)[3] = r3;
    FUN_003544c8(/*x30*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7b60 @ 0x002b7b60   (est. sk_swift_buffer_pointer_init_b)
 * Ghidra: void FUN_002b7b60(undefined1 (*param_1) [16], p2..p5)
 * Buffer-descriptor init via FUN_0028ef70.
 * Confidence: low.
 */
void sk_swift_buffer_pointer_init_b(sk_pair_t *out, uint64_t p2, uint64_t p3,
                                    uint64_t p4, uint64_t p5)
{
    out[0] = FUN_0028ef70();
    ((uint64_t *)&out[1])[0] = p4;
    ((uint64_t *)&out[1])[1] = p5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b7ba4 @ 0x002b7ba4   (est. sk_swift_proc_50b54)
 * Ghidra: void FUN_002b7ba4(void)
 * Opaque dispatch: obtains a pointer pair, forwards it, calls an indirect
 * callback, then dispatches through a recovered indirect jump.
 * Confidence: low (unrecovered jumptable at 0x002b7c04).
 */
void sk_swift_proc_50b54(void)
{
    uint64_t *p = (uint64_t *)FUN_00350b54();
    FUN_0035063c(*p, p[1]);
    (*(void (*)(void))/*in_x6*/0)();
    FUN_00350bcc();
    (**(void (**)(void))(/*extraout_x16*/0 + 8))();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7c40 @ 0x002b7c40   (est. sk_swift_buffer_pointer_init_c)
 * Ghidra: void FUN_002b7c40(undefined1 (*param_1) [16], p2..p5)
 * Buffer-descriptor init via FUN_002b39b4.
 * Confidence: low.
 */
void sk_swift_buffer_pointer_init_c(sk_pair_t *out, uint64_t p2, uint64_t p3,
                                    uint64_t p4, uint64_t p5)
{
    out[0] = FUN_002b39b4();
    ((uint64_t *)&out[1])[0] = p4;
    ((uint64_t *)&out[1])[1] = p5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b7c78 @ 0x002b7c78   (est. sk_swift_proc_7c78)
 * Ghidra: void FUN_002b7c78(undefined8 param_1, long param_2)
 * Runs sk_swift_string_assign then dispatches through the object's method
 * table (param_2-8 + 8).
 * Confidence: low.
 */
void sk_swift_proc_7c78(uint64_t p1, long p2)
{
    sk_swift_string_assign();
    (**(void (**)(uint64_t, long))(*(long *)(p2 - 8) + 8))(p1, p2);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7ce4 @ 0x002b7ce4   (est. sk_swift_buffer_pointer_init_d)
 * Ghidra: void FUN_002b7ce4(undefined1 (*param_1) [16], undefined8 *param_2)
 * Buffer-descriptor init via FUN_00272a98.
 * Confidence: low.
 */
void sk_swift_buffer_pointer_init_d(sk_pair_t *out, uint64_t *arg)
{
    out[0] = FUN_00272a98(*arg);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7d10 @ 0x002b7d10   (est. sk_swift_debug_release_18)
 * Ghidra: void FUN_002b7d10(undefined8 *param_1)
 * Releases a two-word descriptor with debug tag DAT_00346d18.
 * Confidence: low.
 */
void sk_swift_debug_release_18(uint64_t *desc)
{
    FUN_001a4b5c(desc[0], desc[1], &DAT_00346d18);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7d14 @ 0x002b7d14   (est. sk_swift_debug_release_18_b)
 * Ghidra: void FUN_002b7d14(undefined8 *param_1)
 * Duplicate of sk_swift_debug_release_18.
 * Confidence: low.
 */
void sk_swift_debug_release_18_b(uint64_t *desc)
{
    FUN_001a4b5c(desc[0], desc[1], &DAT_00346d18);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7d44 @ 0x002b7d44   (est. sk_swift_proc_74128)
 * Ghidra: void FUN_002b7d44(undefined1 (*param_1) [16])
 * Descriptor init via FUN_00274128.
 * Confidence: low.
 */
void sk_swift_proc_74128(sk_pair_t *out)
{
    out[0] = FUN_00274128();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7d70 @ 0x002b7d70   (est. sk_swift_proc_1ac3d8)
 * Ghidra: void FUN_002b7d70(undefined1 (*param_1) [16])
 * Descriptor init via FUN_001ac3d8.
 * Confidence: low.
 */
void sk_swift_proc_1ac3d8(sk_pair_t *out)
{
    out[0] = FUN_001ac3d8();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7d9c @ 0x002b7d9c   (est. sk_swift_proc_738f0_90_a)
 * Ghidra: void FUN_002b7d9c(undefined8 param_1)
 * Delegates to FUN_002738f0 with string tag DAT_00343c90.
 * Confidence: low.
 */
void sk_swift_proc_738f0_90_a(uint64_t p)
{
    FUN_002738f0(p, &DAT_00343c90);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7da0 @ 0x002b7da0   (est. sk_swift_proc_738f0_90_a_b)
 * Ghidra: void FUN_002b7da0(undefined8 param_1)
 * Duplicate of sk_swift_proc_738f0_90_a.
 * Confidence: low.
 */
void sk_swift_proc_738f0_90_a_b(uint64_t p)
{
    FUN_002738f0(p, &DAT_00343c90);
}

/*--------------------------------------------------------------------*/
/* FUN_002b7dc8 @ 0x002b7dc8   (est. sk_swift_proc_2765a0_a)
 * Ghidra: void FUN_002b7dc8(void)
 * Delegates to FUN_002765a0.
 * Confidence: low.
 */
void sk_swift_proc_2765a0_a(void)
{
    FUN_002765a0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7dcc @ 0x002b7dcc   (est. sk_swift_proc_2765a0_a_b)
 * Ghidra: void FUN_002b7dcc(void)
 * Duplicate of sk_swift_proc_2765a0_a.
 * Confidence: low.
 */
void sk_swift_proc_2765a0_a_b(void)
{
    FUN_002765a0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7de0 @ 0x002b7de0   (est. sk_swift_uint_buffer_append)
 * Ghidra: void FUN_002b7de0(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Appends the word param_3 to a UInt buffer: repeatedly decodes the next
 * character chunk until the remaining distance is under 0x4000, then
 * materializes the tail pair and commits. Grows the element storage when
 * the count overflows capacity.
 * Confidence: low (register iterator; indirect per-char callback).
 */
void sk_swift_uint_buffer_append(uint64_t p1, uint64_t p2, uint64_t word)
{
    FUN_0035acfc();
    FUN_003585e8();
    void (*next)(void) = (void (*)(void))FUN_00356c84();
    uint64_t rem = word;
    FUN_000a6f68();
    for (;;) {
        if ((rem ^ /*x24*/ 0) < 0x4000) {
            sk_pair_t tail = FUN_002ac99c(/*extraout_x8*/ 0);
            FUN_0035841c(tail.lo, tail.hi, /*extraout_x1*/ 0);
            return;
        }
        FUN_003510dc();
        FUN_0034ef08();
        FUN_002b439c();
        FUN_00355a58();
        FUN_003510dc();
        FUN_0034ef08();
        uint64_t w2 = FUN_002ab6a0();
        FUN_0034ef08(w2, word);
        rem = FUN_002b3b84();
        FUN_00350914();
        uint64_t ok = ((uint64_t (*)(void))next)();
        if (/*x19*/ 0 != 0) {
            FUN_0036b118(/*extraout_x8*/ 0);
            sk_pair_t tail = FUN_003a25d4();
            FUN_0035841c(tail.lo, tail.hi, /*extraout_x1*/ 0);
            return;
        }
        if ((ok & 1) == 0) {
            FUN_003a25d4();
        } else {
            uint64_t buf = FUN_003a261c(/*extraout_x8*/ 0);
            if ((buf & 1) == 0)
                FUN_000824c4(0, *(long *)(buf + 0x10) + 1, 1);
            uint64_t cnt = *(uint64_t *)(buf + 0x10);
            long n = cnt + 1;
            if (*(uint64_t *)(buf + 0x18) >> 1 <= cnt) {
                uint64_t grow = FUN_0006b42c();
                FUN_000824c4(grow, /*extraout_x11*/ 0, 1);
                cnt = /*extraout_x10*/ 0;
                n = /*extraout_x11*/ 0;
            }
            *(long *)(buf + 0x10) = n;
            long slot = buf + cnt * 0x10;
            *(uint64_t *)(slot + 0x20) = /*x27*/ 0;
            *(uint64_t *)(slot + 0x28) = /*x26*/ 0;
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002b7f34 @ 0x002b7f34   (est. sk_swift_proc_7f34)
 * Ghidra: void FUN_002b7f34(void)
 * Opaque string/buffer service chain ending in an indirect call and a
 * release.
 * Confidence: low.
 */
void sk_swift_proc_7f34(void)
{
    FUN_00356940();
    FUN_003528cc();
    FUN_0034df94();
    FUN_002a3e64();
    FUN_00350f0c();
    FUN_0031b900();
    FUN_0034b6b8();
    (*(void (*)(void))/*extraout_x8*/0)();
    FUN_003a25d4();
}

/*--------------------------------------------------------------------*/
/* FUN_002b7fa4 @ 0x002b7fa4   (est. sk_swift_proc_7fa4)
 * Ghidra: void FUN_002b7fa4(undefined8 p1, undefined8 p2, undefined8 p3, code *param_4)
 * Stores a 4-word result block (0xf marker, callback and args) to x19.
 * Confidence: low.
 */
void sk_swift_proc_7fa4(uint64_t p1, uint64_t p2, uint64_t p3, void (*cb)(void))
{
    FUN_0035237c();
    cb();
    word_t *out = (word_t *)0;   /* x19 */
    out[0] = 0xf;
    out[1] = /*extraout_x1*/ 0;
    out[2] = p3;
    out[3] = (word_t)cb;
}

/*--------------------------------------------------------------------*/
/* FUN_002b800c @ 0x002b800c   (est. sk_swift_unsafe_raw_buffer_init)
 * Ghidra: void FUN_002b800c(undefined8 param_1)
 * UnsafeMutableRawBufferPointer(unsafeUninitializedCapacity:) initializer.
 * Queries the buffer's element-count pair; if the count is negative it
 * raises a Swift "Fatal error" (index out of range), otherwise it invokes
 * the initializer callback over [base, base+count) and tags the result.
 * Confidence: medium (Swift UnsafeMutableRawBufferPointer init).
 */
void sk_swift_unsafe_raw_buffer_init(uint64_t out)
{
    DAT_00658c00(*(uint64_t *)(*(long *)(/*x5*/ 0 - 8) + 0x40));
    sk_pair_t r = DAT_00658c00();
    if ((int64_t)r.hi < 0) {
        sk_fatal_error(0xb, 2,
            "UnsafeMutableRawBufferPointer withUnsafeBytes requires "
            "non-negative count", 0x31, 2,
            "Swift.UnsafeRawBufferPointer", 0x22);
    }
    (*(void (*)(uint64_t, uint64_t, uint64_t, void *))/*x12*/0)
        (out, r.lo, r.lo + r.hi, /*tmp*/0);
    uint64_t v = FUN_0031dc0c(0, /*x4*/ 0, /*x5*/ 0, /*x6*/ 0);
    FUN_00369340(out, v, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b81b4 @ 0x002b81b4   (est. sk_swift_unsafe_mutable_buffer_with_neg)
 * Ghidra: undefined1 [16] FUN_002b81b4(undefined8 param_1, long param_2,
 *                                      code *param_3)
 * UnsafeMutableBufferPointer(unsafeUninitializedCapacity:) body factory.
 * Traps with a Swift fatal error if param_2 (count) is negative, otherwise
 * invokes the initializer and returns its 16-byte pair.
 * Confidence: medium (Swift UnsafeMutableBufferPointer init).
 */
sk_pair_t sk_swift_unsafe_mutable_buffer_with_neg(uint64_t p1, long count, void (*init)(void))
{
    if (count < 0) {
        sk_fatal_error(0xb, 2,
            "UnsafeMutableBufferPointer withUnsafeMutableBufferPointer "
            "requires non-negative count", 0x2e, 2,
            "Swift.UnsafeBufferPointer", 0x1f, 2, 0x4a, 1);
    }
    uint64_t lo = 0, hi = 0;
    ((void (*)(uint64_t *))init)(&lo);
    /* auVar1 = { lo, uStack_40 } */
    sk_pair_t r;
    r.lo = lo;
    r.hi = hi;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002b8254 @ 0x002b8254   (est. sk_swift_unsafe_mutable_buffer_with_neg_8)
 * Ghidra: undefined1 FUN_002b8254(undefined8 param_1, long param_2, code *param_3)
 * Byte-returning variant of sk_swift_unsafe_mutable_buffer_with_neg.
 * Confidence: medium.
 */
uint8_t sk_swift_unsafe_mutable_buffer_with_neg_8(uint64_t p1, long count, void (*init)(void))
{
    if (count < 0) {
        sk_fatal_error(0xb, 2,
            "UnsafeMutableBufferPointer withUnsafeMutableBufferPointer "
            "requires non-negative count", 0x2e, 2,
            "Swift.UnsafeBufferPointer", 0x1f, 2, 0x4a, 1);
    }
    uint8_t lo = 0;
    ((void (*)(uint8_t *))init)(&lo);
    return lo;
}

/*--------------------------------------------------------------------*/
/* FUN_002b82f0 @ 0x002b82f0   (est. sk_swift_unsafe_raw_buffer_init_b)
 * Ghidra: void FUN_002b82f0(undefined8 param_1)
 * UnsafeMutableRawBufferPointer initializer variant: reads the count pair,
 * builds the element pair via FUN_001a26e0, invokes the callback over the
 * buffer, and tags the result.
 * Confidence: medium.
 */
void sk_swift_unsafe_raw_buffer_init_b(uint64_t out)
{
    DAT_00658c00(*(uint64_t *)(*(long *)(/*x7*/ 0 - 8) + 0x40));
    DAT_00658c00();
    sk_pair_t r = FUN_001a26e0();
    (*(void (*)(uint64_t, uint64_t, uint64_t, void *))/*x3*/0)
        (out, r.lo, r.hi, /*tmp*/0);
    uint64_t v = FUN_0031dc0c(0, /*x6*/ 0, /*x7*/ 0, /*stk*/ 0);
    FUN_00369340(out, v, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b8444 @ 0x002b8444   (est. sk_swift_array_alloc)
 * Ghidra: void FUN_002b8444(long param_1, long param_2)
 * Allocates an array of param_1 elements whose stride is the element type
 * size at *(param_2-8)+0x48. Uses a 128-bit multiply to detect overflow;
 * on overflow traps via SoftwareBreakpoint. Element alignment comes from
 * the type descriptor (+0x50).
 * Confidence: high (Swift _allocateUninitializedArray path).
 */
void sk_swift_array_alloc(long count, long type)
{
    long stride = *(long *)(*(long *)(type - 8) + 0x48);
    long bytes = stride * count;
    __int128 full = (__int128)stride * count;
    if ((uint64_t)(full >> 64) == (uint64_t)(bytes >> 63)) {
        uint32_t align = (uint32_t)*(uint8_t *)(*(long *)(type - 8) + 0x50);
        uint32_t log2align = (align > 0xf) ? (align + 1) : 0;
        FUN_0036a804(bytes, (uint64_t)log2align - 1);
        return;
    }
    __builtin_trap();   /* SoftwareBreakpoint(1,0x2b849c) */
}

/*--------------------------------------------------------------------*/
/* FUN_002b84dc @ 0x002b84dc   (est. sk_swift_proc_84dc)
 * Ghidra: ulong FUN_002b84dc(undefined8 param_1, undefined8 param_2,
 *                            undefined8 param_3)
 * Runs two opaque service calls and packs their results: low 32 bits from
 * the first, high byte from the second.
 * Confidence: low.
 */
unsigned long sk_swift_proc_84dc(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_0034c034();
    FUN_0035125c(p3);
    FUN_003109b4();
    FUN_0034d150();
    uint64_t a = (*(uint64_t (*)(void))/*x8*/0)();
    FUN_0034b3c8();
    (**(void (**)(void))(/*x16*/0 + 8))();
    FUN_003534a4();
    FUN_0034d354();
    uint64_t b = (*(uint64_t (*)(void))/*x8_00*/0)();
    return a & 0xffffffff | (b & 0xff) << 0x20;
}

/*--------------------------------------------------------------------*/
/* FUN_002b8564 @ 0x002b8564   (est. sk_swift_string_prepend)
 * Ghidra: void FUN_002b8564(void)
 * Prepends a scalar to a string: builds the string pair, and when the
 * pending flag byte is set performs the character write through an
 * indirect callback then shifts the UTF-8 buffer right; otherwise just
 * records the flag and commits.
 * Confidence: low.
 */
void sk_swift_string_prepend(void)
{
    sk_pair_t p = FUN_00354744();
    if (*(char *)((uint32_t *)0 + 1) != '\0') {
        uint32_t ch = *(uint32_t *)0;       /* x20[0] */
        uint64_t str = *(uint64_t *)(p.lo + 0x18);
        FUN_00352894(str);
        void (*emit)(uint64_t, void *) = (void (*)(uint64_t, void *))FUN_00310a74();
        FUN_000863bc();
        FUN_00350e14();
        emit(/*x8*/ 0, &ch);
        FUN_0034c9e8(/*x8*/ 0);
        FUN_000839d8();
        sk_pair_t q = FUN_0009461c();
        sk_swift_string_shift_right((uint32_t *)q.lo, q.hi, str);
        FUN_003544c8(p.hi);
        return;
    }
    FUN_0034e68c();
    FUN_003544c8();
    FUN_000839d8();
}

/*--------------------------------------------------------------------*/
/* FUN_002b8620 @ 0x002b8620   (est. sk_swift_string_shift_right)
 * Ghidra: void FUN_002b8620(uint *param_1, undefined8 param_2, undefined8 param_3)
 * Shifts the string's code-unit count right: divides *buf by the scalar
 * width at the index offset and subtracts the consumed width from the
 * trailing byte.
 * Confidence: low.
 */
void sk_swift_string_shift_right(uint32_t *buf, uint64_t str, uint64_t flags)
{
    uint32_t lo = *buf;
    uint64_t (*width)(uint64_t, uint64_t) = (uint64_t (*)(uint64_t, uint64_t))FUN_00310984(flags);
    uint64_t shift = width(str, flags);
    *buf = lo >> (uint32_t)(shift & 0x1f);
    uint32_t hi = buf[1];
    char w = (char)sk_swift_string_index_offset(shift, str, flags);
    *(char *)(buf + 1) = (char)hi - w;
}

/*--------------------------------------------------------------------*/
/* FUN_002b8690 @ 0x002b8690   (est. sk_swift_string_shift_left)
 * Ghidra: void FUN_002b8690(undefined8 param_1, long param_2)
 * Shifts the string's code-unit count left by one character: when the
 * pending flag byte is set, encodes the character and shifts the UTF-8
 * buffer right; otherwise records the single-unit shift.
 * Confidence: low.
 */
void sk_swift_string_shift_left(uint64_t p1, long p2)
{
    uint64_t str = *(uint64_t *)(p2 + 0x10);
    if (*(char *)((uint32_t *)0 + 1) != '\0') {
        uint32_t ch = *(uint32_t *)0;       /* x20[0] */
        uint64_t w = FUN_00027754(*(uint64_t *)(p2 + 0x18));
        void (*emit)(uint64_t, void *, uint64_t, uint64_t, uint64_t, uint64_t) =
            (void (*)(uint64_t, void *, uint64_t, uint64_t, uint64_t, uint64_t))FUN_00310a74();
        uint64_t x = FUN_000863bc();
        emit(p1, &ch, 0x6776f0, x, str, w);
        FUN_000839d8(p1, 0, 1, str);
        sk_swift_string_shift_right(0, 0, 0);
        return;
    }
    FUN_000839d8(p1, 1, 1, str);
}

/*--------------------------------------------------------------------*/
/* FUN_002b8784 @ 0x002b8784   (est. sk_swift_proc_1b5a88)
 * Ghidra: void FUN_002b8784(void)
 * Delegates to FUN_001b5a88.
 * Confidence: low.
 */
void sk_swift_proc_1b5a88(void)
{
    FUN_001b5a88();
}

/*--------------------------------------------------------------------*/
/* FUN_002b87c0 @ 0x002b87c0   (est. sk_swift_proc_1b5784)
 * Ghidra: void FUN_002b87c0(void)
 * Delegates to FUN_001b5784.
 * Confidence: low.
 */
void sk_swift_proc_1b5784(void)
{
    FUN_001b5784();
}

/*--------------------------------------------------------------------*/
/* FUN_002b87fc @ 0x002b87fc   (est. sk_swift_proc_284424)
 * Ghidra: void FUN_002b87fc(void)
 * Delegates to thunk_FUN_00284424.
 * Confidence: low.
 */
void sk_swift_proc_284424(void)
{
    thunk_FUN_00284424();
}

/*--------------------------------------------------------------------*/
/* FUN_002b886c @ 0x002b886c   (est. sk_swift_proc_1e088c)
 * Ghidra: void FUN_002b886c(undefined8 param_1)
 * Delegates to FUN_001e088c with a string descriptor tag.
 * Confidence: low.
 */
void sk_swift_proc_1e088c(uint64_t p)
{
    FUN_001e088c(p, 0x66ead8);
}

/*--------------------------------------------------------------------*/
/* FUN_002b88d4 @ 0x002b88d4   (est. sk_swift_index_plus_dist)
 * Ghidra: int FUN_002b88d4(undefined8 param_1, undefined8 param_2,
 *                          undefined8 param_3, undefined8 param_4)
 * Returns index + distance: adds the string's scalar distance (from
 * sk_swift_string_index_offset) to the input index.
 * Confidence: medium (Swift String.Index advanced-by).
 */
int sk_swift_index_plus_dist(uint64_t idx, uint64_t p2, uint64_t str, uint64_t flags)
{
    return (int)sk_swift_string_index_offset(idx, str, flags) + (int)idx;
}

/*--------------------------------------------------------------------*/
/* FUN_002b8904 @ 0x002b8904   (est. sk_swift_string_index_offset)
 * Ghidra: void FUN_002b8904(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Helper: computes the code-unit distance/offset for a string index by
 * invoking the width helper (FUN_00310984) through an indirect call and
 * returning its result.
 * Confidence: low.
 */
unsigned long sk_swift_string_index_offset(uint64_t idx, uint64_t str, uint64_t flags)
{
    FUN_00350a28();
    FUN_00310984(flags);
    FUN_0035013c();
    return (*(uint64_t (*)(void))/*extraout_x8*/0)();
}

/*--------------------------------------------------------------------*/
/* FUN_002b8938 @ 0x002b8938   (est. sk_swift_string_shift_amount)
 * Ghidra: void FUN_002b8938(undefined8 p1, uint param_2, uint param_3,
 *                           undefined8 p4, undefined8 p5)
 * Computes a shifted bit count (param_3 >> param_2) and passes it through
 * an indirect callback with the string argument.
 * Confidence: low.
 */
void sk_swift_string_shift_amount(uint64_t p1, uint32_t shift, uint32_t value,
                                  uint64_t p4, uint64_t p5)
{
    uint32_t local = value >> (shift & 0x1f);
    FUN_00350950(p5);
    FUN_00353d44();
    FUN_000863bc();
    FUN_00350e14();
    (*(void (*)(uint64_t, uint32_t *))/*x22*/0)(p1, &local);
}

/*--------------------------------------------------------------------*/
/* FUN_002b89ac @ 0x002b89ac   (est. sk_swift_string_buffer_create)
 * Ghidra: undefined * FUN_002b89ac(long *param_1, undefined1 *param_2, long param_3)
 * Allocates a 0x28-byte string buffer header (tag 0x4002), runs the
 * buffer-initializer, records the resulting buffer pointer at +0x20, and
 * returns a type-descriptor pointer (DAT_003471a4).
 * Confidence: medium.
 */
void *sk_swift_string_buffer_create(long *out, uint8_t *p2, long p3)
{
    long hdr = FUN_0036a908(0x28, 0x4002);
    *out = hdr;
    uint64_t u = sk_swift_string_buffer_create_impl((long *)hdr, *p2, /*x20*/0,
                    *(uint64_t *)(p3 + 0x10), *(uint64_t *)(p3 + 0x18)).lo;
    *(uint64_t *)(hdr + 0x20) = u;
    return &DAT_003471a4;
}

/*--------------------------------------------------------------------*/
/* FUN_002b8a30 @ 0x002b8a30   (est. sk_swift_string_buffer_create_impl)
 * Ghidra: undefined1 [16] FUN_002b8a30(long *param_1, uint param_2,
 *                                      uint param_3, long param_4, undefined8 param_5)
 * String buffer constructor: stores the string and its type descriptor,
 * allocates the UTF-8 storage (tag 0x3507) sized by the descriptor's
 * element width, records the bit count, and encodes the first scalar via
 * an indirect callback. Returns the 16-byte pair {DAT_003471a8, storage}.
 * Confidence: medium.
 */
sk_pair_t sk_swift_string_buffer_create_impl(long *out, uint32_t width,
                                             uint32_t bits, long str, uint64_t p5)
{
    long desc = *(long *)(str - 8);
    out[0] = str;
    out[1] = desc;
    long storage = FUN_0036a908(*(uint64_t *)(desc + 0x40), 0x3507);
    out[2] = storage;
    *(uint32_t *)(out + 3) = bits >> (width & 0x1f);
    uint64_t w = FUN_00027754(p5);
    void (*enc)(long, void *, uint64_t, uint64_t, long, uint64_t) =
        (void (*)(long, void *, uint64_t, uint64_t, long, uint64_t))FUN_00310a74();
    uint64_t x = FUN_000863bc();
    enc(storage, out + 3, 0x6776f0, x, str, w);
    sk_pair_t r;
    r.lo = (uint64_t)&DAT_003471a8;
    r.hi = (uint64_t)storage;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002b8b28 @ 0x002b8b28   (est. sk_swift_proc_8b28)
 * Ghidra: int FUN_002b8b28(void)
 * Combines a scalar read with an indirect width result.
 * Confidence: low.
 */
int sk_swift_proc_8b28(void)
{
    int a = FUN_00351da8();
    FUN_00310984(/*x4*/ 0);
    FUN_0035013c();
    int b = (*(int (*)(void))/*x8*/0)();
    return a + b * /*extraout_w1*/ 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b8b70 @ 0x002b8b70   (est. sk_swift_utf16_dist)
 * Ghidra: long FUN_002b8b70(byte param_1, ulong param_2, undefined8 p3,
 *                           undefined8 p4, undefined8 p5)
 * Computes the distance between two UTF-16 code units divided by the unit
 * width; traps (fatal) if the width is zero.
 * Confidence: medium.
 */
long sk_swift_utf16_dist(uint8_t lo, uint64_t hi, uint64_t p3, uint64_t p4, uint64_t p5)
{
    FUN_003534a4(p5);
    FUN_00350af4();
    long w = (*(long (*)(void))/*x8*/0)();
    if (w != 0) {
        long d = 0;
        if (w != 0)
            d = (long)((hi & 0xff) - (uint64_t)lo) / w;
        return d;
    }
    FUN_00348074(1);
    FUN_00351be0();
    FUN_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b8be4 @ 0x002b8be4   (est. sk_swift_index_add_char)
 * Ghidra: void FUN_002b8be4(char *param_1, char *param_2, long param_3)
 * Stores *out = *in + distance(in, string) — advance an index by one char.
 * Confidence: medium.
 */
void sk_swift_index_add_char(char *out, char *in, long str)
{
    char c = *in;
    char d = (char)sk_swift_string_index_offset((uint64_t)(intptr_t)in,
                    *(uint64_t *)(str + 0x10), *(uint64_t *)(str + 0x18));
    *out = (char)(c + d);
}

/*--------------------------------------------------------------------*/
/* FUN_002b8c1c @ 0x002b8c1c   (est. sk_swift_index_add_char_inplace)
 * Ghidra: void FUN_002b8c1c(char *param_1, long param_2)
 * In-place variant of sk_swift_index_add_char.
 * Confidence: medium.
 */
void sk_swift_index_add_char_inplace(char *io, long str)
{
    char c = *io;
    char d = (char)sk_swift_string_index_offset((uint64_t)(intptr_t)io,
                    *(uint64_t *)(str + 0x10), *(uint64_t *)(str + 0x18));
    *io = (char)(c + d);
}

/*--------------------------------------------------------------------*/
/* FUN_002b8c54 @ 0x002b8c54   (est. sk_swift_index_minus_dist)
 * Ghidra: int FUN_002b8c54(undefined8 p1, undefined8 p2, undefined8 p3,
 *                          undefined8 p4)
 * Returns index - distance.
 * Confidence: medium.
 */
int sk_swift_index_minus_dist(uint64_t idx, uint64_t p2, uint64_t str, uint64_t flags)
{
    return (int)idx - (int)sk_swift_string_index_offset(idx, str, flags);
}

/*--------------------------------------------------------------------*/
/* FUN_002b8c84 @ 0x002b8c84   (est. sk_swift_index_sub_char)
 * Ghidra: void FUN_002b8c84(char *param_1, char *param_2, long param_3)
 * Stores *out = *in - distance — retreat an index by one char.
 * Confidence: medium.
 */
void sk_swift_index_sub_char(char *out, char *in, long str)
{
    char c = *in;
    char d = (char)sk_swift_string_index_offset((uint64_t)(intptr_t)in,
                    *(uint64_t *)(str + 0x10), *(uint64_t *)(str + 0x18));
    *out = (char)(c - d);
}

/*--------------------------------------------------------------------*/
/* FUN_002b8cbc @ 0x002b8cbc   (est. sk_swift_index_sub_char_inplace)
 * Ghidra: void FUN_002b8cbc(char *param_1, long param_2)
 * In-place variant of sk_swift_index_sub_char.
 * Confidence: medium.
 */
void sk_swift_index_sub_char_inplace(char *io, long str)
{
    char c = *io;
    char d = (char)sk_swift_string_index_offset((uint64_t)(intptr_t)io,
                    *(uint64_t *)(str + 0x10), *(uint64_t *)(str + 0x18));
    *io = (char)(c - d);
}

/*--------------------------------------------------------------------*/
/* FUN_002b8cf8 @ 0x002b8cf8   (est. sk_swift_proc_8cf8)
 * Ghidra: void FUN_002b8cf8(void)
 * String/object teardown chain.
 * Confidence: low.
 */
void sk_swift_proc_8cf8(void)
{
    uint64_t a = FUN_00349944();
    uint64_t b = FUN_0034e238();
    FUN_00376820(b, /*x3*/ 0);
    FUN_003498a8();
    FUN_001e3a28();
}

/*--------------------------------------------------------------------*/
/* FUN_002b8d40 @ 0x002b8d40   (est. sk_swift_index_add_scaled)
 * Ghidra: void FUN_002b8d40(char *param_1, char *param_2, char param_3,
 *                           long param_4)
 * Stores *out = *in + width * scalar — advance by a scaled distance.
 * Confidence: medium.
 */
void sk_swift_index_add_scaled(char *out, char *in, char scalar, long str)
{
    char c = *in;
    FUN_003534a4(*(uint64_t *)(str + 0x18));
    FUN_00350af4();
    char w = (char)(*(long (*)(void))/*x8*/0)();
    *out = (char)(c + w * scalar);
}

/*--------------------------------------------------------------------*/
/* FUN_002b8d98 @ 0x002b8d98   (est. sk_swift_utf8_dist)
 * Ghidra: long FUN_002b8d98(byte *param_1, byte *param_2, long param_3)
 * Computes the UTF-8 code-unit distance between two byte offsets divided
 * by the width; traps (fatal) if the width is zero.
 * Confidence: medium.
 */
long sk_swift_utf8_dist(uint8_t *lo, uint8_t *hi, long str)
{
    uint8_t a = *lo, b = *hi;
    FUN_00310984(*(uint64_t *)(str + 0x18));
    FUN_0035013c();
    long w = (*(long (*)(void))/*x8*/0)();
    if (w != 0) {
        long d = 0;
        if (w != 0)
            d = (long)((uint64_t)b - (uint64_t)a) / w;
        return d;
    }
    FUN_00348074(1);
    FUN_00351be0();
    FUN_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b8e34 @ 0x002b8e34   (est. sk_object_service_01)
 * Ghidra: void FUN_002b8e34(void)
 * Object-service dispatch loop: acquires the current TCB/cpu context,
 * runs a long chain of object/refcount/scheduling helpers, performs
 * indirect method-table dispatches (pc7/pc8 through the vtable), and
 * releases the cpu context. The many intermediate helpers are unresolved;
 * the call order and the indirect dispatch structure are preserved.
 * Confidence: low (opaque object-service; dozens of unresolved helpers).
 */
void sk_object_service_01(void)
{
    uint64_t tcb = FUN_0008e518().lo;         /* current thread/cpu */
    uint64_t u2 = /*x4*/ 0;
    FUN_00352c10();
    u2 = FUN_00027754(u2);
    FUN_0008f6c0();
    FUN_0035a478();
    FUN_0034f8d0();
    FUN_0034df64();
    FUN_00377824();
    FUN_0034ab20();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034b0d4();
    FUN_0034998c();
    DAT_00658c00(*(uint64_t *)(/*x8_00*/ 0 + 0x40));
    FUN_00348a80();
    DAT_00658c00();
    FUN_0034b540();
    DAT_00658c00();
    FUN_00350464();
    FUN_0034911c();
    DAT_00658c00(*(uint64_t *)(/*x8_02*/ 0 + 0x40));
    FUN_003493c4();
    FUN_0034d294();
    DAT_00658c00();
    FUN_0034ae58();
    FUN_00351274();
    FUN_00350aac();
    FUN_00377bec();
    uint64_t u3 = FUN_0034bc04();
    FUN_00352c28(u3, 0x200);
    (*(sk_fn_t)/*x9*/0)();
    FUN_0034d558();
    FUN_0034f4b4();
    (*(sk_fn_t)/*x9_00*/0)();
    FUN_00310f34(/*x4*/ 0);
    FUN_0034db98();
    FUN_00351e3c();
    (*(sk_fn_t)/*x8_03*/0)();
    sk_fn_t pc7 = *(sk_fn_t *)(/*x16*/ 0 + 8);
    FUN_00350518();
    pc7();
    /* local_8 = 1 */
    FUN_00352d4c(u2);
    sk_pair_t p9 = FUN_0001df60();
    u3 = p9.lo;
    FUN_0034aef4(p9.lo, p9.hi, p9.lo);
    FUN_003518f4();
    (*(sk_fn_t)/*x21*/0)();
    sk_fn_t pc4 = (sk_fn_t)FUN_0031c964(/*x4*/ 0);
    FUN_00352e3c();
    FUN_00350b48();
    (*(sk_fn_t)/*x9_01*/0)();
    FUN_00350518();
    pc7();
    pc7();
    FUN_00356af4();
    FUN_00352894();
    sk_fn_t pc5 = (sk_fn_t)FUN_00350a4c();
    FUN_00353bd0();
    sk_pair_t q = FUN_000e72b0();
    FUN_0034bdcc(q.lo, q.hi, u2);
    (*(sk_fn_t)/*x9_02*/0)();
    sk_fn_t pc6 = (sk_fn_t)((uint64_t (*)(uint64_t))/*x5*/0)(/*x4*/ 0);
    FUN_003502d8(/*local_50*/ 0, /*x20*/ 0);
    (*(sk_fn_t)/*x9_03*/0)();
    sk_fn_t pc8 = *(sk_fn_t *)(/*x16_00*/ 0 + 8);
    FUN_00084180();
    pc8();
    /* local_8 = 1 */
    sk_pair_t r = FUN_0035041c(/*&local_8*/ 0);
    FUN_003518f4(r.lo, r.hi, u3);
    (*(sk_fn_t)/*x9_04*/0)();
    FUN_003505c4(/*x8_01*/ 0, tcb);
    pc4();
    FUN_000e15d8();
    pc7((void *)(/*x16*/ 0 + 8));
    sk_pair_t s = FUN_000e72b0();
    FUN_0034bdcc(s.lo, s.hi, u2);
    pc5();
    FUN_003504a0(/*x8*/ 0, /*local_50*/ 0);
    pc6();
    FUN_00084180();
    pc8();
    FUN_003508cc();
    pc8();
    FUN_0008e500(/*x30*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b91d4 @ 0x002b91d4   (est. sk_object_service_02)
 * Ghidra: void FUN_002b91d4(void)
 * Second object-service dispatch loop: analogous to sk_object_service_01
 * with additional lock/refcount acquire-release and vtable dispatches.
 * Confidence: low (opaque object-service).
 */
void sk_object_service_02(void)
{
    uint64_t tcb = FUN_0008e518().lo;         /* current thread/cpu */
    uint64_t u1 = FUN_00352c10();
    FUN_00027754(/*x4*/ 0);
    FUN_0034be54();
    FUN_0034f8d0();
    FUN_00351584();
    uint64_t u2 = FUN_00377824();
    FUN_0034ab20();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_00350428();
    FUN_00349618();
    DAT_00658c00(*(uint64_t *)(/*x8_00*/ 0 + 0x40));
    FUN_00348a18();
    DAT_00658c00();
    FUN_0034abec();
    DAT_00658c00();
    FUN_0034ac50();
    FUN_00351bec(/*x3*/ 0);
    FUN_0008f6c0();
    uint64_t u3 = FUN_0008f6f4().lo;
    FUN_0034d8e4();
    FUN_00377824();
    FUN_0034ab20();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034b0d4();
    FUN_003494e8();
    DAT_00658c00(*(uint64_t *)(/*x8_01*/ 0 + 0x40));
    FUN_003493c4();
    FUN_0034cde8();
    DAT_00658c00();
    FUN_0034baa8();
    DAT_00658c00();
    DAT_00658c00();
    FUN_0034bc6c();
    FUN_00350298(u3);
    FUN_00377bec();
    FUN_00349370();
    FUN_0034ba98();
    (*(sk_fn_t)/*x9*/0)();
    FUN_0034e74c();
    sk_pair_t a = FUN_0034d810();
    (*(sk_fn_t)/*x9_00*/0)(a.lo, a.hi, u3);
    sk_fn_t pc4 = (sk_fn_t)FUN_001679cc();
    FUN_00353984();
    FUN_00350c8c();
    (*(sk_fn_t)/*x9_01*/0)();
    FUN_00352420();
    FUN_003510b8();
    (*(sk_fn_t)/*x8_03*/0)();
    FUN_0034ad00();
    sk_pair_t b = FUN_000e15d8();
    FUN_00377bec(b.lo, b.hi, u2);
    FUN_0034bc04();
    FUN_0035a540();
    FUN_00350aac();
    (*(sk_fn_t)/*x9_02*/0)();
    FUN_0034cea8();
    FUN_00353480();
    FUN_000bd3a4();
    (*(sk_fn_t)/*x9_03*/0)();
    FUN_00356a7c();
    u2 = FUN_00310f34();
    FUN_00351130(u2);
    FUN_00351c58();
    (*(sk_fn_t)/*x8_04*/0)();
    sk_fn_t pc6 = *(sk_fn_t *)(/*x16*/ 0 + 8);
    FUN_000e72b0();
    pc6();
    /* local_10[0] = 1 */
    FUN_0035466c();
    sk_fn_t pc5 = (sk_fn_t)FUN_00310a74();
    sk_pair_t c = FUN_0001df60();
    u2 = c.lo;
    FUN_0035041c(c.lo, c.hi, c.lo);
    FUN_0034c424(/*local_10*/ 0);
    pc5();
    FUN_00358ddc();
    pc5 = (sk_fn_t)FUN_0031c964();
    FUN_0035404c();
    FUN_00351130();
    FUN_00350bfc();
    (*(sk_fn_t)/*x9_04*/0)();
    FUN_000e72b0();
    pc6();
    FUN_0008e388();
    pc6();
    FUN_0034e1d0();
    FUN_00358a20();
    FUN_00351274();
    FUN_0035950c();
    FUN_0034c3d4();
    (*(sk_fn_t)/*x9_05*/0)();
    FUN_00356a88();
    FUN_00319778();
    uint64_t u4 = FUN_0035441c();
    *(uint64_t *)(/*x8_05*/ 0 - 0x100) = u4;
    FUN_00350ab8(/*x22*/ 0);
    FUN_00350a1c();
    (*(sk_fn_t)/*x9_06*/0)();
    FUN_003505e8();
    (*(sk_fn_t)/*x8_02*/0)();
    FUN_003509d4();
    (*(sk_fn_t)/*x8_02*/0)();
    /* local_10[0] = 1 */
    sk_pair_t d = FUN_0035041c(/*local_78*/ 0, /*local_10*/ 0);
    FUN_003518f4(d.lo, d.hi, u2);
    (*(sk_fn_t)/*x9_07*/0)();
    FUN_003513a8(/*local_48*/ 0, u1);
    pc5();
    FUN_0008e388();
    pc6((void *)(/*x16*/ 0 + 8));
    FUN_00350058();
    FUN_003505dc();
    FUN_00355418();
    (*(sk_fn_t)/*x9_08*/0)();
    FUN_00353bd0();
    FUN_00350738();
    FUN_00354b74();
    (*(sk_fn_t)/*x9_09*/0)();
    FUN_003505e8();
    (*(sk_fn_t)/*x8_02*/0)();
    FUN_0035060c();
    (*(sk_fn_t)/*x8_02*/0)();
    sk_pair_t e = FUN_00084180(/*x8*/ 0);
    pc4(e.lo, e.hi, /*x25*/ 0);
    FUN_00084180();
    (*(sk_fn_t)/*x8_02*/0)();
    FUN_0008e500(/*x30*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b96a8 @ 0x002b96a8   (est. sk_object_service_03)
 * Ghidra: void FUN_002b96a8(void)
 * Object-service dispatch with an explicit per-element loop: reads the
 * current cpu/thread context, walks object elements via vtable entries
 * (extraout_x16_00 + 8/0x10/0x20), applies per-element offsets and helper
 * transforms, then releases the context.
 * Confidence: low (register-resident element base x20; indirect vtable).
 */
void sk_object_service_03(void)
{
    sk_pair_t ctx = FUN_0008e518();
    long hi = ctx.hi, lo = ctx.lo;
    uint64_t u7 = *(uint64_t *)(hi + 0x10);
    FUN_0034b0b4();
    long l3 = FUN_003579d8();
    FUN_000a6f88();
    DAT_00658c00(*(uint64_t *)(/*x8*/ 0 + 0x40));
    FUN_003492ac();
    DAT_00658c00();
    FUN_0034b4c0();
    FUN_00349b00();
    DAT_00658c00(*(uint64_t *)(/*x8_00*/ 0 + 0x40));
    FUN_003490d0();
    DAT_00658c00();
    FUN_0034b3d8();
    FUN_0034df04();
    DAT_00658c00(*(uint64_t *)(/*x8_01*/ 0 + 0x40));
    FUN_003497b4();
    FUN_00352128();
    uint64_t u10 = *(uint64_t *)(/*x12*/ 0 + 0x20);
    FUN_00310b08(u10);
    FUN_0034bcf0();
    FUN_003531e4();
    uint64_t u4 = (*(uint64_t (*)(void))/*x8_02*/0)();
    sk_fn_t pc6;
    if ((u4 & 1) == 0) {
        int off = *(int *)(hi + 0x24);
        FUN_0035044c(u10);
        FUN_00350968(/*x20*/ 0 + off);
        u4 = (*(uint64_t (*)(void))/*x8_03*/0)();
        pc6 = *(sk_fn_t *)(/*x16_00*/ 0 + 0x10);
        long sel = lo;
        if ((u4 & 1) != 0)
            sel = /*x20*/ 0 + off;
        FUN_003579e8((uint64_t)(/*x16_00*/ 0 + 0x10) & 0xffffffffffff | 0xe3ba000000000000,
                     u4, sel);
        pc6();
    } else {
        pc6 = *(sk_fn_t *)(/*x16_00*/ 0 + 0x10);
        sk_pair_t a = FUN_003504f4();
        pc6(a.lo, a.hi, u7);
    }
    long hi2 = (long)*(int *)(hi + 0x24);
    FUN_0035044c(u10);
    FUN_003531e4(/*x20*/ 0 + hi2, lo + hi2);
    u4 = (*(uint64_t (*)(void))/*x8_04*/0)();
    if ((u4 & 1) == 0) {
        FUN_003531e4();
        u4 = (*(uint64_t (*)(void))/*x8_02*/0)();
        if ((u4 & 1) != 0)
            FUN_00100efc((uint64_t)(/*x16_00*/ 0 + 0x10) & 0xffffffffffff | 0xe3ba000000000000);
        pc6();
    } else {
        FUN_003548a0(/*x16_00*/ 0 + 0x10, u4, /*x20*/ 0 + hi2);
        pc6();
    }
    pc6 = *(sk_fn_t *)(/*x16_00*/ 0 + 0x20);
    pc6();
    FUN_0035a49c();
    FUN_00351a20();
    pc6();
    FUN_00351990();
    sk_pair_t b = FUN_003504f4();
    (*(sk_fn_t)/*x9*/0)(b.lo, b.hi, l3);
    int off2 = *(int *)(l3 + 0x30);
    sk_pair_t c = FUN_003508f0();
    pc6(c.lo, c.hi, u7);
    sk_fn_t pc9 = *(sk_fn_t *)(/*x16_00*/ 0 + 8);
    pc9(/*local_38*/ 0 + off2, u7);
    sk_pair_t d = FUN_003504f4(*(uint64_t *)(/*x16*/ 0 + 0x20));
    (*(sk_fn_t)/*x8_05*/0)(d.lo, d.hi, l3);
    sk_pair_t e = FUN_00357fc4((long)*(int *)(l3 + 0x30));
    pc6(e.lo, e.hi, u7);
    FUN_003512c0();
    pc9();
    FUN_00206770(/*local_28*/ 0, lo, u7, u10);
    FUN_00352320();
    FUN_003508b4();
    (*(sk_fn_t)/*x8_06*/0)();
    u7 = FUN_00352980();
    FUN_0008e500(u7, /*stk*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b9a04 @ 0x002b9a04   (est. sk_swift_stride)
 * Ghidra: long FUN_002b9a04(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Returns 0x20 / width, where width comes from an indirect helper; traps
 * (fatal) if the width is zero.
 * Confidence: medium.
 */
long sk_swift_stride(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_00350a28();
    FUN_00310984(p3);
    FUN_0035013c();
    long w = (*(long (*)(void))/*x8*/0)();
    if (w != 0) {
        long d = 0;
        if (w != 0)
            d = 0x20 / w;
        return d;
    }
    FUN_00348074(1);
    FUN_00351be0();
    FUN_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b9a60 @ 0x002b9a60   (est. sk_swift_uint_buffer_append_impl)
 * Ghidra: void FUN_002b9a60(void)
 * Core UInt-buffer append/encode loop: consumes characters from the source
 * string, tracking a running bit-count and width, growing storage when
 * needed, and finally packs the accumulated bit pattern into the output
 * uint word pair. Raises a Swift fatal error on capacity underflow.
 * Confidence: low (large register-driven Swift UInt(_, radix:) loop;
 *   indirect per-character decode helpers).
 */
void sk_swift_uint_buffer_append_impl(void)
{
    FUN_0008e518();
    FUN_00356c78();
    uint64_t u12 = *(uint64_t *)(/*x1*/ 0 + 0x18);   /* string flags */
    FUN_003514b8(u12);
    FUN_00351b44();
    uint64_t u11 = *(uint64_t *)(/*x19*/ 0 + 0x10);  /* string words */
    FUN_00349dfc();
    FUN_000dbf08();
    FUN_00377824();
    FUN_0034ab20();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034b6f4();
    FUN_003499f0();
    DAT_00658c00(*(uint64_t *)(/*x8*/ 0 + 0x40));
    FUN_00348a9c();
    DAT_00658c00();
    FUN_0034ac00();
    DAT_00658c00();
    FUN_0034b4c0();
    FUN_00349890();
    long n = FUN_0019c9cc();
    if (n == (long)-1)
        __builtin_trap();                       /* SoftwareBreakpoint(1,0x2ba088) */
    FUN_00350b84();
    long step = sk_swift_stride(0, 0, 0);
    if (step < n + 1) {
        FUN_0034b348();
        FUN_003486b8(0xbe);
        FUN_0034975c();
        goto fatal;
    }
    FUN_00310aa4(u12);
    FUN_00351184();
    FUN_00351160();
    (*(sk_fn_t)/*x9*/0)();
    FUN_00310a14();
    FUN_0034c5cc();
    uint64_t u7 = (*(uint64_t (*)(void))/*x8_00*/0)();
    uint32_t u1, i4, i5, b2 = 0;
    sk_fn_t pc13 = 0, pc9 = 0;
    if ((u7 & 1) == 0) {
        pc9 = (sk_fn_t)FUN_00310a44();
        FUN_0034fdac();
        long d = (*(long (*)(void))pc9)();
        if (d < 0x20) {
            /* consume character; accumulate */
            FUN_0034dbe8();
            FUN_000e15d8();
            i4 = (*(int (*)(void))/*x8_05*/0)();
            pc13 = *(sk_fn_t *)(/*x16*/ 0 + 8);
            FUN_00357904();
            FUN_00350b00();
            pc13();
            b2 = (uint8_t)((uint32_t *)0)[1];
            u1 = *(uint32_t *)0;
            uint64_t u10 = FUN_00353d7c(*(uint64_t *)(/*x16*/ 0 + 0x10));
            (*(sk_fn_t)/*x8_06*/0)(u10, /*x26*/ 0, u11);
            FUN_000e15d8();
            u7 = (*(uint64_t (*)(void))/*x8_00*/0)();
            if ((u7 & 1) != 0) {
                FUN_0034ad00(); FUN_00350630(); FUN_003586e4(); FUN_00377bec();
                FUN_00349370(); FUN_0034ba98(); (*(sk_fn_t)/*x9_07*/0)();
                FUN_0034d558(); FUN_003547f8(); FUN_003517cc(); (*(sk_fn_t)/*x9_08*/0)();
                FUN_0034b368(); FUN_00352d70(); FUN_003509d4(); FUN_00351b78();
                u7 = (*(uint64_t (*)(void))/*x8_07*/0)();
                FUN_003504ac();
                pc13();
                if ((u7 & 1) == 0) goto out_short;
            }
            FUN_0034fdac();
            d = (*(long (*)(void))pc9)();
            if (d < 0x20) goto acc_done;
            FUN_000e15d8();
            u7 = (*(uint64_t (*)(void))/*x8_00*/0)();
            FUN_0034fdac();
            d = (*(long (*)(void))pc9)();
            if ((u7 & 1) == 0) {
                if (d < 0x21) goto acc_done2;
                FUN_00351c34(); FUN_000863bc(); FUN_00350e14();
                FUN_00351918(&(uint32_t){0xffffffff});
                FUN_00351154(); (*(sk_fn_t)pc9)(); FUN_00348c84();
            } else {
                if (d < 0x21) {
                    FUN_0034ad00(); FUN_000b4390(); FUN_003586e4(); FUN_00377bec();
                    FUN_00348fb4(); FUN_0034ae80(); (*(sk_fn_t)/*x9_09*/0)();
                    FUN_0034d98c(/*x27*/ 0); FUN_00077894(/*local_38*/ 0);
                    (*(sk_fn_t)/*x9_10*/0)();
                    FUN_0034af04(); FUN_00351ee0(); FUN_00353d7c(); FUN_0034cf74();
                    u7 = (*(uint64_t (*)(void))/*x8_09*/0)();
                    FUN_00350630();
                    pc13();
                    if ((u7 & 1) == 0) goto acc_done;
                    goto acc_done2;
                }
                FUN_00351c34(); FUN_000863bc(); FUN_00350e14();
                FUN_00351918(&(uint32_t){0xffffffff});
                FUN_00351154(); (*(sk_fn_t)pc9)(); FUN_00348c84();
            }
            FUN_003515fc(pc9, /*local_28*/ 0);
            u7 = (*(uint64_t (*)(void))/*x8_08*/0)();
            FUN_00350630();
            pc13();
            if ((u7 & 1) == 0) {
acc_done:
            FUN_0034fdac();
            i5 = (*(int (*)(void))/*x8_05*/0)();
            FUN_00350b00();
            uint64_t u10 = (*(uint64_t (*)(void))pc13)();
            *(uint32_t *)0 = (uint32_t)(i5 << (b2 & 0x1f)) |
                             u1 & (i4 << (b2 & 0x1f) ^ 0xffffffffU);
            char w = (char)sk_swift_string_index_offset(u10, u11, u12);
            *(uint8_t *)((uint32_t *)0 + 1) = (uint8_t)(w + b2);
            FUN_0008e500(/*x30*/ 0);
            return;
            }
            goto out_short2;
        } else {
            /* long-character path */
            FUN_000e15d8();
            u7 = (*(uint64_t (*)(void))/*x8_00*/0)();
            FUN_0034fdac();
            d = (*(long (*)(void))pc9)();
            if ((u7 & 1) == 0) {
                if (0x20 < d) goto long1;
                goto acc_done2;
            }
            if (d < 0x21) {
                FUN_0034ad00(); FUN_003508b4(); FUN_003586e4(); FUN_00377bec();
                FUN_003494fc(); FUN_0034ed58(/*local_38*/ 0); (*(sk_fn_t)/*x9_03*/0)();
                FUN_0034d970(); FUN_00351cb8(/*local_20*/ 0, /*local_38*/ 0);
                (*(sk_fn_t)/*x9_04*/0)();
                FUN_0034c61c(); FUN_00310b08(); FUN_00350a7c(); FUN_00351190();
                u7 = (*(uint64_t (*)(void))/*x8_02*/0)();
                FUN_00353c0c(); FUN_003504ac(); (*(sk_fn_t)/*x9_05*/0)();
                if ((u7 & 1) != 0) goto acc_done2;
                goto acc_done;
            }
long1:
            FUN_00351c34(); FUN_000863bc(); FUN_00350e14();
            FUN_00351154(/*local_20*/ 0, &(uint32_t){0xffffffff});
            (*(sk_fn_t)FUN_00310a74())();
            FUN_0034c61c(); FUN_0035044c(); FUN_00351324(); FUN_00351f70();
            u7 = (*(uint64_t (*)(void))/*x8_04*/0)();
            FUN_00353c0c(); FUN_003504ac(); (*(sk_fn_t)/*x9_06*/0)();
            if ((u7 & 1) == 0) goto acc_done;
            goto out_short2;
        }
        FUN_00350410();
        FUN_00348194();
        goto out_short2;
    } else {
        FUN_0034ad00(); FUN_003508b4(); FUN_003586e4(); FUN_00377bec();
        FUN_00348fb4(); FUN_00357910(); FUN_0034b9f8(); (*(sk_fn_t)/*x9_00*/0)();
        FUN_0034d970(); FUN_00351918(); FUN_00351cb8(); (*(sk_fn_t)/*x9_01*/0)();
        FUN_0034af04(); FUN_00310954(); FUN_00350a7c(); FUN_0034cf74();
        uint64_t pc8v = ((uint64_t (*)(void))/*x8_01*/0)();
        if ((pc8v & 1) != 0) goto acc_done;
        FUN_00353c0c(); FUN_00350630(); (*(sk_fn_t)/*x9_02*/0)();
        if (((uint64_t)/*pcVar8*/ 0 & 1) != 0) goto acc_done;
        goto out_short2;
    }
out_short:
    /* fall through to the accumulate tail */
    goto acc_done;
acc_done2:
    goto acc_done;
out_short2:
    FUN_003482c4();
    FUN_003523f0();
fatal:
    FUN_001afe4c();     /* Swift fatal error, no return */
}

/*--------------------------------------------------------------------*/
/* FUN_002ba40c @ 0x002ba40c   (est. sk_swift_uint_buffer_replace_range)
 * Ghidra: void FUN_002ba40c(undefined8 p1, undefined8 p2, long param_3,
 *                           undefined8 p4, long param_5, undefined8 p6)
 * Replaces a bit range in a UInt buffer with a new value. Validates the
 * range bounds (fatal "Range requires lowerBound <= upperBound" / UInt
 * buffer overflow), encodes the replacement via FUN_00271d58, then splices
 * the bits using the integer stride (FUN_002b9a04) and updates the output
 * uint word pair. Traps on division by zero.
 * Confidence: low (Swift _FixedArray/UInt bit-range splice).
 */
void sk_swift_uint_buffer_replace_range(uint64_t p1, uint64_t p2, long param_3,
                                        uint64_t p4, long param_5, uint64_t p6)
{
    sk_pair_t src = DAT_00658c00(*(uint64_t *)(*(long *)(param_3 - 8) + 0x40));
    long pad = -(/*extraout_x8*/ 0 + 0xf & 0xfffffffffffffff0);
    uint8_t lo = *(uint8_t *)src.lo;
    uint8_t hi = *(uint8_t *)(src.lo + 1);
    if (hi < lo) {
        sk_fatal_error(0xb, 2, "Range requires lowerBound <= upperBound", 0x27, 2,
                       "Swift.Range", 0x11, 2, 0x11, 1);
    }
    if ((uint8_t)((uint32_t *)0)[1] < hi) {
        sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UIntBuffer", 0x16);
    }
    long e0 = /*extraout_x12*/ 0;
    uint64_t start = (uint64_t)lo;
    (**(void (**)(void *, uint64_t, long))(e0 + 0x10))(/*tmp*/ 0, src.hi, param_3);
    uint64_t w = FUN_00027754(p4);
    long str = param_3;
    FUN_00271d58(&(uint32_t){0}, /*tmp*/ 0, param_5, param_3, p6, w);
    uint64_t s16 = *(uint64_t *)(param_5 + 0x10);
    uint64_t s18 = *(uint64_t *)(param_5 + 0x18);
    long (*width)(uint64_t, uint64_t) = (long (*)(uint64_t, uint64_t))FUN_00310984(s18);
    long w0 = width(s16, s18);
    if (w0 != 0) {
        uint32_t acc = 0;   /* local_68 result */
        long cnt = 0;
        if (w0 != 0)
            cnt = (long)(hi - start) / w0;
        uint64_t src2 = src.hi;
        long tot = FUN_0019c9cc(param_5, 0x66ead8);
        long t1 = tot - cnt;
        long t2 = FUN_0019c9cc(param_5, 0x66ead8);
        if (t2 == (long)-1)
            __builtin_trap();               /* SoftwareBreakpoint(1,0x2ba78c) */
        long stride = sk_swift_stride(t2, s16, s18);
        if (stride < t2 + t1) {
            sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UIntBuffer", 0x16);
        }
        long w1 = width(s16, s18);
        if (w1 != 0) {
            long w2 = width(s16, s18);
            if (w2 != 0) {
                int i4 = 0;
                if (w1 != 0)
                    i4 = (int)((long)start / w1);
                (**(void (**)(uint64_t, long))(e0 + 8))(src2, str);
                int i5 = 0;
                if (w2 != 0)
                    i5 = (int)((long)(uint64_t)hi / w2);
                int i8 = width(s16, s18);
                uint32_t u3 = (uint32_t)i8 * (uint32_t)i4;
                uint32_t *out = (uint32_t *)0;   /* x20 */
                uint32_t shiftin = (uint32_t)(i8 * i5);
                out[0] = (uint32_t)(((uint64_t)(out[0] >> ((uint32_t)(i8 * i5 + 1) >> 1 & 0x1f)) >>
                                     (uint32_t)(shiftin >> 1 & 0x1f)) << (uint32_t)(i8 * (i5 + (int)t1) & 0x1f)) |
                          (acc << (u3 & 0x1f)) |
                          (((1u << ((u3 + 1) >> 1 & 0x1f)) << (u3 >> 1 & 0x1f)) - 1U) & out[0];
                *(char *)(out + 1) = (char)out[1] + (char)i8 * (char)t1;
                return;
            }
        }
    }
    sk_fatal_error(0xb, 2, "Division by zero", 0x10, 2, "Swift.IntegerTypes", 0x18);
}

/*--------------------------------------------------------------------*/
/* FUN_002bb188 @ 0x002bb188   (est. sk_swift_uint_buffer_pop)
 * Ghidra: void FUN_002bb188(undefined8 param_1, long param_2)
 * Pops the most significant bit group from a UInt buffer: computes the
 * scalar width, shifts the stored uint right by the width, and records the
 * new width. Traps (fatal, UIntBuffer) if the buffer underflows.
 * Confidence: low.
 */
void sk_swift_uint_buffer_pop(uint64_t p1, long p2)
{
    uint64_t ok = FUN_0019fd10(p2, 0x66ead8);
    if ((ok & 1) == 0) {
        uint32_t *out = (uint32_t *)0;      /* x20 */
        uint32_t lo = *out;
        uint64_t s16 = *(uint64_t *)(p2 + 0x10);
        uint64_t s18 = *(uint64_t *)(p2 + 0x18);
        uint32_t local = lo;
        uint64_t w = FUN_00027754(s18);
        uint64_t (*enc)(uint64_t, void *, uint64_t, uint64_t, uint64_t, uint64_t) =
            (uint64_t (*)(uint64_t, void *, uint64_t, uint64_t, uint64_t, uint64_t))FUN_00310a74();
        uint64_t x = FUN_000863bc();
        uint64_t r = enc(p1, &local, 0x6776f0, x, s16, w);
        uint32_t hi = out[1];
        uint64_t w0 = sk_swift_string_index_offset(r, s16, s18);
        *(char *)(out + 1) = (char)hi - (char)w0;
        uint64_t w1 = sk_swift_string_index_offset(w0, s16, s18);
        *out = (uint32_t)((lo >> (uint32_t)((w1 + 1) >> 1 & 0x1f)) >> (uint32_t)(w1 >> 1 & 0x1f));
        return;
    }
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UIntBuffer", 0x16, 2, 200, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002bb2bc @ 0x002bb2bc   (est. sk_swift_proc_bb2bc)
 * Ghidra: void FUN_002bb2bc(void)
 * Opaque buffer service: runs a preparation chain, an indirect call, and
 * an unrecovered indirect jump.
 * Confidence: low (unrecovered jumptable at 0x002bb334).
 */
void sk_swift_proc_bb2bc(void)
{
    FUN_00084220();
    FUN_003542e8();
    FUN_003562c8();
    FUN_00319688(/*x5*/ 0);
    FUN_0035066c();
    FUN_003510c4();
    uint64_t v = (*(uint64_t (*)(void))/*x8*/0)();
    sk_fn_t jt = (sk_fn_t)FUN_003244b4();
    FUN_000bd3a4(v);
    FUN_00084234();
    jt();
}

/*--------------------------------------------------------------------*/
/* FUN_002ba7a4 @ 0x002ba7a4   (est. sk_swift_uint_buffer_shift)
 * Ghidra: void FUN_002ba7a4(undefined8 param_1, long param_2)
 * Shifts a UInt buffer left by one character: encodes the source string
 * through the integer conversion pipeline (FUN_00377824/FUN_0008f728/
 * FUN_0008f758), tracking the running bit count and width, and finally
 * packs the result into the output uint word pair. Raises Swift fatal
 * errors on capacity underflow / "Not enough bits" / "Negative value".
 * Confidence: low (large register-driven Swift UInt conversion loop).
 */
void sk_swift_uint_buffer_shift(uint64_t p1, long p2)
{
    uint64_t s18 = *(uint64_t *)(p2 + 0x18);
    uint64_t p1k = p1;
    uint64_t u6 = FUN_00027754(s18);
    FUN_0008f6c0();
    uint64_t f64 = FUN_0008f6f4().lo;
    long s16 = *(long *)(p2 + 0x10);
    long lA = FUN_00377824(0, f64, s16, FUN_0060e3fc, FUN_0060e40c);
    DAT_00658c00(*(long *)(*(long *)(lA - 8) + 0x40) + 0xf & 0xfffffffffffffff0);
    long l19 = *(long *)(s16 - 8);
    void *a8 = /*stack*/ 0 - /*x8*/ 0;
    DAT_00658c00(*(uint64_t *)(l19 + 0x40));
    long l20 = (long)a8 - (/*x8_00*/ 0 + 0xf & 0xfffffffffffffff0);
    DAT_00658c00();
    long l90 = l20 - /*x12*/ 0;
    DAT_00658c00();
    long l22 = l90 - /*x12_00*/ 0;
    long n = FUN_0019c9cc(p2, 0x66ead8);
    if (n == (long)-1)
        __builtin_trap();                       /* SoftwareBreakpoint(1,0x2bb0a0) */
    long stride = sk_swift_stride(n, s16, s18);
    if (stride < n + 1) {
        sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UIntBuffer", 0x16);
    }
    sk_fn_t pc9 = (sk_fn_t)FUN_00310aa4(s18);
    ((sk_fn_t)pc9)(l22, s16, s18);
    pc9 = (sk_fn_t)FUN_00310a14(u6);
    uint64_t u10 = ((uint64_t (*)(long, uint64_t))pc9)(s16, u6);
    uint64_t u13 = f64;
    long l7 = lA;
    uint64_t u24, uVar;
    long l8;
    sk_fn_t pc12, pc14, pc15, local_b0;
    uint32_t u1 = 0, u23 = 0, local_cc = 0, i18, i5;
    uint32_t *x20 = (uint32_t *)0;
    uint64_t local_c0;
    if ((u10 & 1) == 0) {
    loopA:
        pc12 = (sk_fn_t)FUN_00310a44(u6);
        l7 = ((long (*)(long, uint64_t))pc12)(s16, u6);
        if (l7 < 0x20) {
        loopB:
            local_b0 = (sk_fn_t)FUN_003109b4(u6);
            local_c0 = ((uint64_t (*)(long, uint64_t))local_b0)(s16, u6);
            pc14 = *(sk_fn_t *)(l19 + 8);
            ((sk_fn_t)pc14)(l22, s16);
            u23 = (uint32_t)(uint8_t)x20[1];
            u1 = x20[0];
            (**(void (**)(long, uint64_t, long))(l19 + 0x10))(l20, p1k, s16);
            u10 = ((uint64_t (*)(long, uint64_t))pc9)(s16, u6);
            u24 = f64;
            l7 = lA;
            if ((u10 & 1) != 0) {
                sk_fn_t c8 = pc14;
                u13 = FUN_00377bec(f64, s16, lA, FUN_0060e3fc, &LAB_0060e404);
                pc14 = (sk_fn_t)FUN_0008f728();
                local_cc = (uint32_t)(uint8_t)x20[1];
                ((sk_fn_t)pc14)(a8, &DAT_004c1010, 0x100, l7, u13);
                pc14 = (sk_fn_t)FUN_0008f758(u24);
                l7 = l90;
                u23 = local_cc;
                ((sk_fn_t)pc14)(l90, a8, s16, u24);
                FUN_00310ad4(u6);
                u24 = FUN_00027754();
                pc15 = (sk_fn_t)FUN_00310954();
                pc14 = c8;
                u10 = ((uint64_t (*)(long, long, long, uint64_t))pc15)(l20, l7, s16, u24);
                ((sk_fn_t)pc14)(l7, s16);
                if ((u10 & 1) == 0) goto fatal_neg;
            }
            l7 = ((long (*)(long, uint64_t))pc12)(s16, u6);
            if (l7 < 0x20) { ((sk_fn_t)pc14)(p1k, s16); goto acc; }
            u10 = ((uint64_t (*)(long, uint64_t))pc9)(s16, u6);
            l7 = ((long (*)(long, uint64_t))pc12)(s16, u6);
            if ((u10 & 1) == 0) {
                if (0x20 < l7) goto overflow;
                ((sk_fn_t)pc14)(p1k, s16);
            } else {
                if (0x20 < l7) {
                overflow:
                    uint32_t local_64 = 0xffffffff;
                    pc9 = (sk_fn_t)FUN_00310a74(u6);
                    u24 = FUN_000863bc();
                    l7 = l90;
                    ((sk_fn_t)pc9)(l90, &local_64, 0x6776f0, u24, s16, u6);
                    FUN_00310ad4(u6);
                    u24 = FUN_00027754();
                    pc9 = (sk_fn_t)FUN_0016186c();
                    u10 = ((uint64_t (*)(long, long, long, uint64_t))pc9)(l7, l20, s16, u24);
                    ((sk_fn_t)pc14)(l7, s16);
                    if ((u10 & 1) == 0) { ((sk_fn_t)pc14)(p1k, s16); goto acc; }
                    goto fatal_bits;
                }
                ((sk_fn_t)pc14)(p1k, s16);
                u24 = f64;
                l7 = lA;
                u13 = FUN_00377bec(f64, s16, lA, FUN_0060e3fc, &LAB_0060e404);
                pc9 = (sk_fn_t)FUN_0008f728();
                ((sk_fn_t)pc9)(a8, &DAT_004c1010, 0x100, l7, u13);
                pc9 = (sk_fn_t)FUN_0008f758(u24);
                l7 = l90;
                ((sk_fn_t)pc9)(l90, a8, s16, u24);
                FUN_00310ad4(u6);
                u24 = FUN_00027754();
                pc9 = (sk_fn_t)FUN_00310b08();
                u10 = ((uint64_t (*)(long, long, long, uint64_t))pc9)(l20, l7, s16, u24);
                ((sk_fn_t)pc14)(l7, s16);
                if ((u10 & 1) == 0) goto acc;
            }
            ((uint64_t (*)(long, uint64_t))local_b0)(s16, u6);
        acc:
            i18 = (uint32_t)local_c0;
            i5 = ((uint32_t (*)(long, uint64_t))local_b0)(s16, u6);
            uVar = ((uint64_t (*)(long, long))pc14)(l20, s16);
            x20[0] = i5 << (u23 & 0x1f) | u1 & (i18 << (u23 & 0x1f) ^ 0xffffffffU);
            char c4 = (char)sk_swift_string_index_offset(uVar, s16, u24);
            *(char *)(x20 + 1) = (char)(c4 + (char)u23);
            return;
        }
        u10 = ((uint64_t (*)(long, uint64_t))pc9)(s16, u6);
        l8 = ((long (*)(long, uint64_t))pc12)(s16, u6);
        u13 = f64;
        l7 = lA;
        if ((u10 & 1) == 0) {
            if (0x20 < l8) goto long_over;
            goto short_path;
        }
        if (l8 < 0x21) {
            u13 = FUN_00377bec(f64, s16, lA, FUN_0060e3fc, &LAB_0060e404);
            pc14 = (sk_fn_t)FUN_0008f728();
            local_b0 = pc12;
            ((sk_fn_t)pc14)(a8, &DAT_004c1010, 0x100, l7, u13);
            pc14 = (sk_fn_t)FUN_0008f758(u13);
            l7 = l90;
            pc12 = local_b0;
            ((sk_fn_t)pc14)(l90, a8, s16, u13);
            FUN_00310ad4(u6);
            u13 = FUN_00027754();
            pc14 = (sk_fn_t)FUN_00310b08();
            u10 = ((uint64_t (*)(long, long, long, uint64_t))pc14)(l22, l7, s16, u13);
            (**(void (**)(long, long))(l19 + 8))(l7, s16);
            if ((u10 & 1) != 0) goto short_path;
            goto loopB;
        }
    long_over:
        uint32_t local_64b = 0xffffffff;
        pc14 = (sk_fn_t)FUN_00310a74(u6);
        u13 = FUN_000863bc();
        l7 = l90;
        ((sk_fn_t)pc14)(l90, &local_64b, 0x6776f0, u13, s16, u6);
        FUN_00310ad4(u6);
        u13 = FUN_00027754();
        pc14 = (sk_fn_t)FUN_0016186c();
        u10 = ((uint64_t (*)(long, long, long, uint64_t))pc14)(l7, l22, s16, u13);
        (**(void (**)(long, long))(l19 + 8))(l7, s16);
        if ((u10 & 1) == 0) goto loopB;
        goto fatal_bits;
    } else {
        u13 = FUN_00377bec(f64, s16, lA, FUN_0060e3fc, &LAB_0060e404);
        pc12 = (sk_fn_t)FUN_0008f728();
        ((sk_fn_t)pc12)(a8, &DAT_004c1010, 0x100, l7, u13);
        pc12 = (sk_fn_t)FUN_0008f758(u13);
        l7 = l90;
        ((sk_fn_t)pc12)(l90, a8, s16, u13);
        FUN_00310ad4(u6);
        u13 = FUN_00027754();
        pc12 = (sk_fn_t)FUN_00310954();
        u10 = ((uint64_t (*)(long, long, long, uint64_t))pc12)(l22, l7, s16, u13);
        (**(void (**)(long, long))(l19 + 8))(l7, s16);
        if ((u10 & 1) != 0) goto loopA;
        goto fatal_neg;
    }
short_path:
    pc14 = (sk_fn_t)FUN_003109b4(u6);
    ((sk_fn_t)pc14)(s16, u6);
    goto loopB;
fatal_bits:
    sk_fatal_error(0xb, 2, "Not enough bits to represent the passed value", 0x2d, 2,
                   "Swift.Integers", 0x14);
fatal_neg:
    sk_fatal_error(0xb, 2, "Negative value is not representable", 0x23, 2,
                   "Swift.Integers", 0x14);
}

/*--------------------------------------------------------------------*/
/* FUN_002bb470 @ 0x002bb470   (est. sk_object_service_04)
 * Ghidra: void FUN_002bb470(void)
 * Object-service dispatch: acquires the current thread/cpu, runs the
 * lock/refcount chain, builds an object pair and forwards it through an
 * indirect callback, then conditionally releases or dispatches through the
 * vtable (+0x20) based on a flag, and releases the context.
 * Confidence: low.
 */
void sk_object_service_04(void)
{
    FUN_0008e518();
    FUN_00354a4c();
    FUN_003519fc();
    FUN_00377824();
    FUN_0034f554();
    FUN_00310d68();
    FUN_00348d64();
    DAT_00658c00(*(uint64_t *)(/*x8_00*/ 0 + 0x40));
    FUN_00348a18();
    DAT_00658c00();
    FUN_0034ba68();
    FUN_0031e18c(/*x4*/ 0);
    FUN_0035102c();
    sk_pair_t a = FUN_00351324();
    FUN_00356a20(a.lo, a.hi, /*x3*/ 0, /*x5*/ 0);
    (*(sk_fn_t)/*x9*/0)();
    FUN_000aa46c();
    FUN_003511c0();
    (*(sk_fn_t)/*x9_00*/0)();
    FUN_0034c4bc();
    if (/*in_ZR*/ 0) {
        FUN_0031e15c(/*x4*/ 0);
        FUN_00100efc(/*x8*/ 0);
        (*(sk_fn_t)/*x9_01*/0)();
        FUN_000e72b0(*(uint64_t *)(/*x16*/ 0 + 8));
        (*(sk_fn_t)/*x8_01*/0)();
    } else {
        FUN_00352d10();
        (**(void (**)(uint64_t))(/*x16_00*/ 0 + 0x20))(/*x8*/ 0);
    }
    FUN_0008e500(/*x1*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002bb5c0 @ 0x002bb5c0   (est. sk_object_service_05)
 * Ghidra: void FUN_002bb5c0(undefined8 p1..p8)
 * Object-service dispatch loop with an explicit callback (param_3): sets
 * up the object context, then loops dispatching per-element work; on a
 * normal tick it recursively runs sk_object_service_04, on the alternative
 * tick it runs a different transition, and on termination it releases the
 * context and returns.
 * Confidence: low (opaque object-service; callback-driven loop).
 */
void sk_object_service_05(uint64_t p1, uint64_t p2, sk_fn_t tick, uint64_t p4,
                          uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    sk_pair_t ctx = FUN_0008e518();
    FUN_00377824(0, p8, p5, &DAT_00612b58, &DAT_00612b90);
    FUN_000a6f88();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034b05c();
    FUN_0034bec4();
    uint64_t u2 = FUN_00377824();
    FUN_000a6f88(u2, u2);
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_00350428();
    FUN_00350908();
    FUN_0031e084();
    FUN_0034ab20();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034b0c4();
    FUN_003499f0();
    DAT_00658c00(*(uint64_t *)(/*x8_00*/ 0 + 0x40));
    FUN_003497b4();
    FUN_00349830();
    FUN_000bd3a4();
    FUN_00377824();
    FUN_00348cd0();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034af20();
    FUN_0034bec4();
    FUN_00377824();
    FUN_000a6f88();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034aee4();
    u2 = FUN_00377bec(/*stk68*/ 0, p7, /*x12*/ 0, &DAT_00612b58, &LAB_00612b78);
    FUN_0031e0d4();
    FUN_00350b24();
    FUN_00350b6c();
    (*(sk_fn_t)/*x9*/0)();
    uint64_t u3 = FUN_00352e24();
    (*(sk_fn_t)/*x8_01*/0)(u3, ctx.lo, p6);
    FUN_000a68c4(/*stk60*/ 0);
    FUN_00351f7c();
    FUN_000e15d8();
    (*(sk_fn_t)/*x9_00*/0)();
    sk_fn_t pc4 = (sk_fn_t)FUN_0031e104(u2);
    FUN_0034b278();
    FUN_0034db38();
    FUN_00377bec();
    for (;;) {
        FUN_0034ca28(/*x24*/ 0);
        pc4();
        FUN_0035620c();
        int rc = FUN_00369584();
        if (rc == 0) {
            FUN_0035457c();
            sk_pair_t a = FUN_00351160();
            (*(sk_fn_t)/*x8_02*/0)(a.lo, a.hi, /*x1*/ 0);
            sk_pair_t b = FUN_00354d20();
            sk_object_service_04();
            FUN_00354f8c();
            FUN_003510b8();
            (*(sk_fn_t)/*x8_03*/0)();
            p6 = /*x8*/ 0;
        } else {
            if (rc != 1) {
                FUN_00353e08();
                FUN_00084180();
                (*(sk_fn_t)/*x8_05*/0)();
                FUN_00357964();
                FUN_000a6e14();
                (*(sk_fn_t)/*x8_06*/0)();
                FUN_0008e500(ctx.hi);
                return;
            }
            FUN_00356b20();
            FUN_0031e15c();
            FUN_00351184();
            (*(sk_fn_t)/*x9_01*/0)(p5, p6);
        }
        tick();
        FUN_003567ec();
        FUN_0035a3dc();
        (*(sk_fn_t)/*x8_04*/0)();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002bb9b8 @ 0x002bb9b8   (est. sk_swift_unicode_width)
 * Ghidra: uint FUN_002bb9b8(uint param_1)
 * Classifies a Unicode scalar into a grapheme/width bucket: control chars
 * (<0x20) are width 1, ASCII is width 0, and the various East-Asian /
 * combining ranges map to 3/9/10/4/5/7/0xb; unknown scalars fall through
 * to a per-plane table lookup (FUN_003d34b8) returning packed width bits.
 * Confidence: high (Swift grapheme-cluster width classifier, string-matched
 *   ranges like U+200D ZWJ, Hangul Jamo, CJK).
 */
unsigned int sk_swift_unicode_width(unsigned int cp)
{
    if (cp < 0x20)
        return 1;
    if (cp <= 0x7e)
        return 0;
    if (cp == 0x200d)
        return 0xb;
    if (cp - 0x1100 < 0x60 || cp - 0xa960 < 0x1d)
        return 3;                            /* Hangul Jamo leading */
    if (cp - 0x1160 < 0x48 || cp - 0xd7b0 < 0x17)
        return 10;                           /* Hangul Jamo vowel/trailing */
    if (cp - 0x11a8 < 0x58)
        return 9;
    if (cp - 0xd7cb < 0x31)
        return 9;
    if ((cp - 0xac00) >> 2 < 0xae9) {
        if (cp % 0x1c == 0x10)
            return 4;                        /* Hangul syllable L-part */
        return 5;                            /* Hangul syllable */
    }
    if (cp - 0x1f1e6 < 0x1a)
        return 7;                            /* regional indicator */
    if (cp - 0xe01f0 < 0xe10)
        return 1;                            /* variation selectors */
    uint32_t t = (uint32_t)FUN_003d34b8();
    if (t < 4)
        return 0x8060201 >> ((t & 3) << 3);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002bbae8 @ 0x002bbae8   (est. sk_swift_grapheme_prop_clamp)
 * Ghidra: byte FUN_002bbae8(byte param_1)
 * Clamps a grapheme-cluster boundary property tag to at most 0x11.
 * Confidence: high.
 */
uint8_t sk_swift_grapheme_prop_clamp(uint8_t v)
{
    if (0x10 < v)
        v = 0x11;
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_002bbafc @ 0x002bbafc   (est. sk_swift_grapheme_prop_proc)
 * Ghidra: void FUN_002bbafc(undefined1 *param_1)
 * Reads the property tag at *param_1, clamps it, and feeds it into the
 * grapheme-break procedure.
 * Confidence: medium.
 */
void sk_swift_grapheme_prop_proc(uint8_t *tag)
{
    sk_swift_grapheme_prop_clamp(*tag);
    FUN_00357044();
}

/*--------------------------------------------------------------------*/
/* FUN_002bbb64 @ 0x002bbb64   (est. sk_swift_grapheme_backscan)
 * Ghidra: byte FUN_002bbb64(long param_1, undefined8 param_2, long param_3)
 * Scans backwards from an offset for the first byte that is not a UTF-8
 * leading/continuation byte (byte < 0xc0) and returns it.
 * Confidence: medium.
 */
uint8_t sk_swift_grapheme_backscan(long off, uint64_t p2, long base)
{
    long l = base + off + 3;
    uint8_t *pb;
    do {
        pb = (uint8_t *)(l - 4);
        l = l - 1;
    } while (*pb >= 0xc0);
    return *pb;
}

/*--------------------------------------------------------------------*/
/* FUN_002bbbe8 @ 0x002bbbe8   (est. sk_swift_utf8_backscan)
 * Ghidra: ulong FUN_002bbbe8(undefined8 p1, undefined8 p2, long param_3)
 * Scans backwards over the string buffer for a byte that is not a UTF-8
 * continuation byte (char > -0x41), returning the buffer base and storing
 * the scan length. Traps on out-of-range.
 * Confidence: medium.
 */
unsigned long sk_swift_utf8_backscan(uint64_t p1, uint64_t p2, long len)
{
    uint64_t v = FUN_00358ae0();
    if (/*x8*/ 0 == v >> 0x10)
        return v | 1;
    sk_pair_t buf = FUN_002a49a8();
    long n = 1;
    long i = len - 1;
    for (;;) {
        if (i < 0)
            sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UnsafeBufferPointer", 0x1f, 2, 0x75d, 1);
        if (buf.hi <= (uint64_t)(len - 1))
            sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UnsafeBufferPointer", 0x1f, 2, 0x75e, 1);
        int8_t c = *(int8_t *)(buf.lo + i);
        if (c > -0x41) {
            *(long *)0 = n;                 /* extraout_x8_00 */
            return buf.lo;
        }
        i = i - 1;
        long nn = n + 1;
        n = nn;
        if (nn == 0)
            __builtin_trap();               /* SoftwareBreakpoint(1,0x2bbc5c) */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002bbc14 @ 0x002bbc14   (est. sk_swift_utf8_backscan_b)
 * Ghidra: void FUN_002bbc14(long *param_1, long param_2, long param_3, long param_4)
 * Backward scan over a byte buffer (param_2 + [0,param_4)) for the first
 * non-continuation byte; stores the scan length to *param_1. Traps on
 * out-of-range.
 * Confidence: medium.
 */
void sk_swift_utf8_backscan_b(long *out, long buf, long base, long len)
{
    long n = 1;
    long i = len - 1;
    for (;;) {
        if (i < 0)
            sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UnsafeBufferPointer", 0x1f, 2, 0x75d, 1);
        if (base <= len - 1)
            sk_fatal_error(0xb, 2, "", 0, 2, "Swift.UnsafeBufferPointer", 0x1f, 2, 0x75e, 1);
        int8_t c = *(int8_t *)(buf + i);
        if (c > -0x41) {
            *out = n;
            return;
        }
        i = i - 1;
        long nn = n + 1;
        n = nn;
        if (nn == 0)
            __builtin_trap();               /* SoftwareBreakpoint(1,0x2bbc5c) */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002bbcd8 @ 0x002bbcd8   (est. sk_swift_fatal_2)
 * Ghidra: void FUN_002bbcd8(void)
 * Raises a Swift runtime fatal error (noreturn): builds a message pair and
 * calls the unknown-numeric-type trap.
 * Confidence: medium.
 */
void sk_swift_fatal_2(void)
{
    uint64_t v = FUN_0034e208();
    FUN_003593c0(v, v);
    FUN_0006f768();
    FUN_001afa84();      /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_002bbd30 @ 0x002bbd30   (est. sk_object_service_06)
 * Ghidra: void FUN_002bbd30(void)
 * Object-service dispatch: reads the object element list, runs the setup
 * chain, then dispatches either through the vtable (+0x20) or the fallback
 * path based on FUN_00369584, and commits.
 * Confidence: low.
 */
void sk_object_service_06(void)
{
    FUN_00084220();
    FUN_00353b10();
    FUN_000a6f88();
    DAT_00658c00(*(uint64_t *)(/*x8*/ 0 + 0x40));
    long l2 = FUN_003490ec();
    uint64_t u3 = *(uint64_t *)(l2 + 0x10);
    FUN_00349b00();
    DAT_00658c00(*(uint64_t *)(/*x8_00*/ 0 + 0x40));
    FUN_00348f50();
    FUN_00351990();
    FUN_00353f2c();
    (*(sk_fn_t)/*x9*/0)();
    FUN_00350560();
    int rc = FUN_00369584();
    if (rc == 0) {
        sk_fn_t pc4 = *(sk_fn_t *)(/*x16*/ 0 + 0x20);
        FUN_00350edc();
        pc4();
        sk_pair_t a = FUN_003509e0();
        pc4(a.lo, a.hi, u3);
    } else {
        FUN_0034f2c4();
        (*(sk_fn_t)/*x8_01*/0)();
    }
    FUN_00351c7c();
    FUN_000839d8();
    FUN_00084234(/*x1*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002bbe54 @ 0x002bbe54   (est. sk_object_service_07)
 * Ghidra: undefined8 FUN_002bbe54(void)
 * Object-service value getter: returns the element value, choosing between
 * the register-held value and the runtime default based on FUN_00369584.
 * Confidence: low.
 */
uint64_t sk_object_service_07(void)
{
    FUN_00348e18();
    DAT_00658c00(*(uint64_t *)(/*x8*/ 0 + 0x40));
    FUN_0034a1f8();
    FUN_00352834(/*x16*/ 0);
    (*(sk_fn_t)/*x9*/0)();
    FUN_00084180();
    int rc = FUN_00369584();
    if (rc == 1) {
        return *(uint64_t *)0;              /* unaff_x21 */
    }
    FUN_00084180(*(uint64_t *)(/*x16*/ 0 + 8));
    (*(sk_fn_t)/*x8_00*/0)();
    return FUN_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_002bbf08 @ 0x002bbf08   (est. sk_swift_char_flag_7)
 * Ghidra: ulong FUN_002bbf08(void)
 * Returns bit 7 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_7(void)
{
    return FUN_003d36b0() >> 7 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bbf24 @ 0x002bbf24   (est. sk_swift_char_flag_6)
 * Ghidra: ulong FUN_002bbf24(void)
 * Returns bit 6 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_6(void)
{
    return FUN_003d36b0() >> 6 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bbf40 @ 0x002bbf40   (est. sk_swift_char_flag_8)
 * Ghidra: ulong FUN_002bbf40(void)
 * Returns bit 8 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_8(void)
{
    return FUN_003d36b0() >> 8 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bbf5c @ 0x002bbf5c   (est. sk_swift_char_flag_9)
 * Ghidra: ulong FUN_002bbf5c(void)
 * Returns bit 9 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_9(void)
{
    return FUN_003d36b0() >> 9 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bbf78 @ 0x002bbf78   (est. sk_swift_char_flag_12)
 * Ghidra: ulong FUN_002bbf78(void)
 * Returns bit 12 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_12(void)
{
    return FUN_003d36b0() >> 12 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bbf94 @ 0x002bbf94   (est. sk_swift_char_flag_13)
 * Ghidra: ulong FUN_002bbf94(void)
 * Returns bit 13 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_13(void)
{
    return FUN_003d36b0() >> 13 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bbfb0 @ 0x002bbfb0   (est. sk_swift_char_flag_14)
 * Ghidra: ulong FUN_002bbfb0(void)
 * Returns bit 14 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_14(void)
{
    return FUN_003d36b0() >> 14 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bbfcc @ 0x002bbfcc   (est. sk_swift_char_flag_15)
 * Ghidra: ulong FUN_002bbfcc(void)
 * Returns bit 15 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_15(void)
{
    return FUN_003d36b0() >> 15 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bbfe8 @ 0x002bbfe8   (est. sk_swift_char_flag_20)
 * Ghidra: ulong FUN_002bbfe8(void)
 * Returns bit 20 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_20(void)
{
    return FUN_003d36b0() >> 20 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc004 @ 0x002bc004   (est. sk_swift_char_flag_21)
 * Ghidra: ulong FUN_002bc004(void)
 * Returns bit 21 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_21(void)
{
    return FUN_003d36b0() >> 21 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc020 @ 0x002bc020   (est. sk_swift_char_flag_22)
 * Ghidra: ulong FUN_002bc020(void)
 * Returns bit 22 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_22(void)
{
    return FUN_003d36b0() >> 22 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc03c @ 0x002bc03c   (est. sk_swift_char_flag_23)
 * Ghidra: ulong FUN_002bc03c(void)
 * Returns bit 23 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_23(void)
{
    return FUN_003d36b0() >> 23 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc058 @ 0x002bc058   (est. sk_swift_char_flag_24)
 * Ghidra: ulong FUN_002bc058(void)
 * Returns bit 24 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_24(void)
{
    return FUN_003d36b0() >> 24 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc074 @ 0x002bc074   (est. sk_swift_char_flag_25)
 * Ghidra: ulong FUN_002bc074(void)
 * Returns bit 25 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_25(void)
{
    return FUN_003d36b0() >> 25 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc090 @ 0x002bc090   (est. sk_swift_char_flag_28)
 * Ghidra: ulong FUN_002bc090(void)
 * Returns bit 28 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_28(void)
{
    return FUN_003d36b0() >> 28 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc0ac @ 0x002bc0ac   (est. sk_swift_char_flag_29)
 * Ghidra: ulong FUN_002bc0ac(void)
 * Returns bit 29 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_29(void)
{
    return FUN_003d36b0() >> 29 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc0c8 @ 0x002bc0c8   (est. sk_swift_char_flag_26)
 * Ghidra: ulong FUN_002bc0c8(void)
 * Returns bit 26 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_26(void)
{
    return FUN_003d36b0() >> 26 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc0e4 @ 0x002bc0e4   (est. sk_swift_char_flag_27)
 * Ghidra: ulong FUN_002bc0e4(void)
 * Returns bit 27 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_27(void)
{
    return FUN_003d36b0() >> 27 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc100 @ 0x002bc100   (est. sk_swift_char_flag_30)
 * Ghidra: ulong FUN_002bc100(void)
 * Returns bit 30 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_30(void)
{
    return FUN_003d36b0() >> 30 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc11c @ 0x002bc11c   (est. sk_swift_char_flag_31)
 * Ghidra: ulong FUN_002bc11c(void)
 * Returns bit 31 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_31(void)
{
    return FUN_003d36b0() >> 31 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc138 @ 0x002bc138   (est. sk_swift_char_flag_32)
 * Ghidra: ulong FUN_002bc138(void)
 * Returns bit 32 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_32(void)
{
    return FUN_003d36b0() >> 32 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc154 @ 0x002bc154   (est. sk_swift_char_flag_33)
 * Ghidra: ulong FUN_002bc154(void)
 * Returns bit 33 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_33(void)
{
    return FUN_003d36b0() >> 33 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc170 @ 0x002bc170   (est. sk_swift_char_flag_34)
 * Ghidra: ulong FUN_002bc170(void)
 * Returns bit 34 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_34(void)
{
    return FUN_003d36b0() >> 34 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc18c @ 0x002bc18c   (est. sk_swift_char_flag_37)
 * Ghidra: ulong FUN_002bc18c(void)
 * Returns bit 37 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_37(void)
{
    return FUN_003d36b0() >> 37 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc1a8 @ 0x002bc1a8   (est. sk_swift_char_flag_38)
 * Ghidra: ulong FUN_002bc1a8(void)
 * Returns bit 38 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_38(void)
{
    return FUN_003d36b0() >> 38 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc1c4 @ 0x002bc1c4   (est. sk_swift_char_flag_40)
 * Ghidra: ulong FUN_002bc1c4(void)
 * Returns bit 40 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_40(void)
{
    return FUN_003d36b0() >> 40 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc1e0 @ 0x002bc1e0   (est. sk_swift_char_flag_41)
 * Ghidra: ulong FUN_002bc1e0(void)
 * Returns bit 41 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_41(void)
{
    return FUN_003d36b0() >> 41 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc1fc @ 0x002bc1fc   (est. sk_swift_char_flag_42)
 * Ghidra: ulong FUN_002bc1fc(void)
 * Returns bit 42 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_42(void)
{
    return FUN_003d36b0() >> 42 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc218 @ 0x002bc218   (est. sk_swift_char_flag_43)
 * Ghidra: ulong FUN_002bc218(void)
 * Returns bit 43 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_43(void)
{
    return FUN_003d36b0() >> 43 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc234 @ 0x002bc234   (est. sk_swift_char_flag_45)
 * Ghidra: ulong FUN_002bc234(void)
 * Returns bit 45 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_45(void)
{
    return FUN_003d36b0() >> 45 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc250 @ 0x002bc250   (est. sk_swift_char_flag_46)
 * Ghidra: ulong FUN_002bc250(void)
 * Returns bit 46 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_46(void)
{
    return FUN_003d36b0() >> 46 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc26c @ 0x002bc26c   (est. sk_swift_char_flag_47)
 * Ghidra: ulong FUN_002bc26c(void)
 * Returns bit 47 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_47(void)
{
    return FUN_003d36b0() >> 47 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc288 @ 0x002bc288   (est. sk_swift_char_flag_39)
 * Ghidra: ulong FUN_002bc288(void)
 * Returns bit 39 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_39(void)
{
    return FUN_003d36b0() >> 39 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc2a4 @ 0x002bc2a4   (est. sk_swift_char_flag_44)
 * Ghidra: ulong FUN_002bc2a4(void)
 * Returns bit 44 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_44(void)
{
    return FUN_003d36b0() >> 44 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc2c0 @ 0x002bc2c0   (est. sk_swift_char_flag_35)
 * Ghidra: ulong FUN_002bc2c0(void)
 * Returns bit 35 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_35(void)
{
    return FUN_003d36b0() >> 35 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc2dc @ 0x002bc2dc   (est. sk_swift_char_flag_36)
 * Ghidra: ulong FUN_002bc2dc(void)
 * Returns bit 36 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_36(void)
{
    return FUN_003d36b0() >> 36 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc2f8 @ 0x002bc2f8   (est. sk_swift_char_flag_11)
 * Ghidra: ulong FUN_002bc2f8(void)
 * Returns bit 11 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_11(void)
{
    return FUN_003d36b0() >> 11 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc314 @ 0x002bc314   (est. sk_swift_char_flag_10)
 * Ghidra: ulong FUN_002bc314(void)
 * Returns bit 10 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_10(void)
{
    return FUN_003d36b0() >> 10 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc330 @ 0x002bc330   (est. sk_swift_char_flag_2)
 * Ghidra: ulong FUN_002bc330(void)
 * Returns bit 2 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_2(void)
{
    return FUN_003d36b0() >> 2 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc34c @ 0x002bc34c   (est. sk_swift_char_flag_5)
 * Ghidra: ulong FUN_002bc34c(void)
 * Returns bit 5 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_5(void)
{
    return FUN_003d36b0() >> 5 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc368 @ 0x002bc368   (est. sk_swift_char_flag_4)
 * Ghidra: ulong FUN_002bc368(void)
 * Returns bit 4 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_4(void)
{
    return FUN_003d36b0() >> 4 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc384 @ 0x002bc384   (est. sk_swift_char_flag_0)
 * Ghidra: ulong FUN_002bc384(void)
 * Returns bit 0 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_0(void)
{
    return FUN_003d36b0() >> 0 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc3a0 @ 0x002bc3a0   (est. sk_swift_char_flag_1)
 * Ghidra: ulong FUN_002bc3a0(void)
 * Returns bit 1 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_1(void)
{
    return FUN_003d36b0() >> 1 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc3bc @ 0x002bc3bc   (est. sk_swift_char_flag_3)
 * Ghidra: ulong FUN_002bc3bc(void)
 * Returns bit 3 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_3(void)
{
    return FUN_003d36b0() >> 3 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc3d8 @ 0x002bc3d8   (est. sk_swift_char_flag_16)
 * Ghidra: ulong FUN_002bc3d8(void)
 * Returns bit 16 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_16(void)
{
    return FUN_003d36b0() >> 16 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc3f4 @ 0x002bc3f4   (est. sk_swift_char_flag_19)
 * Ghidra: ulong FUN_002bc3f4(void)
 * Returns bit 19 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_19(void)
{
    return FUN_003d36b0() >> 19 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc410 @ 0x002bc410   (est. sk_swift_char_flag_17)
 * Ghidra: ulong FUN_002bc410(void)
 * Returns bit 17 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_17(void)
{
    return FUN_003d36b0() >> 17 & 1;
}
/*--------------------------------------------------------------------*/
/* FUN_002bc42c @ 0x002bc42c   (est. sk_swift_char_flag_18)
 * Ghidra: ulong FUN_002bc42c(void)
 * Returns bit 18 of the shared Unicode character-flags word
 * (FUN_003d36b0). Swift unicode-scalar property predicate.
 * Confidence: high (mechanical bit extract).
 */
unsigned long sk_swift_char_flag_18(void)
{
    return FUN_003d36b0() >> 18 & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002bc448 @ 0x002bc448   (est. sk_swift_parse_int)
 * Ghidra: void FUN_002bc448(undefined1 param_1, ulong param_2)
 * Parses an integer from a string (Swift Int(_:radix:)): resolves the
 * first digit via FUN_003d38c4 / FUN_003d3838, accumulates the value
 * (thunk_FUN_002a2698), and traps on overflow / unknown-character fatal.
 * Confidence: medium (Swift integer-from-string parser).
 */
void sk_swift_parse_int(uint8_t radix, uint64_t str)
{
    bool ovf = false;
    uint64_t c0 = FUN_0006b2ec();
    uint64_t acc = 0;
    uint64_t aux = /*x8*/ 0;
    long d = FUN_003d38c4(str, c0, &acc);
    if (d == 0 || acc == 0) {
        int v = FUN_003d3838(str, radix);
        if (v != 0) {
            str = (long)v + (str & 0xffffffff);
            ovf = (str == 0);
            if ((long)str < 0) {
                FUN_003482c4();
                FUN_003523f0();
                FUN_001afe4c();      /* fatal, no return */
            }
            if (str >> 0x20 != 0) {
                FUN_003583dc();
                FUN_00348194();
                FUN_003523f0();
                FUN_001afe4c();      /* fatal, no return */
            }
        }
        FUN_00255738(str);
    } else {
        if ((long)acc < 0) {
            FUN_0034846c();
            FUN_001afe4c();          /* fatal, no return */
        }
        thunk_FUN_002a2698(d, acc, 0);
    }
    FUN_000651bc(aux);
    if (!ovf)
        FUN_0011d7e8();              /* Swift runtime failure, no return */
}

/*--------------------------------------------------------------------*/
/* FUN_002bc524 @ 0x002bc524   (est. sk_swift_general_category)
 * Ghidra: uint FUN_002bc524(void)
 * Returns the low byte of the current Unicode general-category word,
 * or 0 when the word is the 0xffff sentinel.
 * Confidence: high.
 */
unsigned int sk_swift_general_category(void)
{
    uint32_t v = (uint32_t)FUN_003d3ac0();
    return (v != 0xffff) ? (v & 0xff) : 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002bc55c @ 0x002bc55c   (est. sk_swift_general_category_validate)
 * Ghidra: void FUN_002bc55c(byte param_1)
 * Validates a general-category tag (< 0x1e); otherwise raises the
 * "Unknown general category" fatal error.
 * Confidence: medium.
 */
void sk_swift_general_category_validate(uint8_t cat)
{
    if (cat < 0x1e)
        return;
    FUN_001a89a8("Unknown general category", 0x18, 1);
    FUN_00355c00();
    FUN_00350d94(0x45e);
    FUN_0006f768();
    FUN_001afa84();      /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_002bc5bc @ 0x002bc5bc   (est. sk_swift_general_category_next)
 * Ghidra: void FUN_002bc5bc(void)
 * Advances to the next general category and validates it.
 * Confidence: medium.
 */
void sk_swift_general_category_next(void)
{
    FUN_003d3b30();
    sk_swift_general_category_validate(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002bc5d8 @ 0x002bc5d8   (est. sk_swift_grapheme_property_table_a)
 * Ghidra: void FUN_002bc5d8(void)
 * Builds the grapheme-cluster property tables (three lookup tables filled
 * with per-property 16-byte entries keyed by Unicode strings), then merges
 * the Hangul syllable decomposition: selects the Jamo leading/vowel/trailing
 * table rows for the current code point, combines them through the shared
 * Swift string-builder helpers, and commits the result pair.
 * Confidence: low (large data-table builder; property strings resolved by
 *   address only, e.g. s_HANGUL_SYLLABLE_005d3850).
 */
void sk_swift_grapheme_property_table_a(void *p8)
{
    /* NOTE: register-resident code point (x19) and table bases (x20..x23)
     * feed the merging tail; modeled with placeholder scalars. */
    uint64_t cp = /*x19*/ 0;
    uint64_t u6 = FUN_00002534(0x64e110, &DAT_004c05b0);
    /* Table A (Hangul Jamo leading) */
    uint8_t *tA = (uint8_t *)FUN_0036a9a0(u6, /*stack*/ 0);
    uint64_t a0 = DAT_004e7ba0;
    *(uint64_t *)(tA + 0x18) = DAT_004e7ba8;
    *(uint64_t *)(tA + 0x10) = a0;
    *(uint64_t *)(tA + 0x20) = 0x47;
    *(uint64_t *)(tA + 0x28) = 0xe100000000000000;
    *(uint64_t *)(tA + 0x30) = 0x4747;
    *(uint64_t *)(tA + 0x38) = 0xe200000000000000;
#define TA_ENTRY(off) \
    do { FUN_00350744(&DAT_005d37c9); *(sk_pair_t *)(tA + (off)) = FUN_001a89a8(); } while (0)
    TA_ENTRY(0x40); TA_ENTRY(0x50); TA_ENTRY(0x60); TA_ENTRY(0x70); TA_ENTRY(0x80);
    TA_ENTRY(0x90); TA_ENTRY(0xa0); TA_ENTRY(0xb0); TA_ENTRY(0xc0); TA_ENTRY(0xd0);
    TA_ENTRY(0xe0); TA_ENTRY(0xf0); TA_ENTRY(0x100); TA_ENTRY(0x110); TA_ENTRY(0x120);
    TA_ENTRY(0x130); TA_ENTRY(0x140);
#undef TA_ENTRY

    /* Table B (Hangul Jamo vowel/trailing) */
    uint8_t *tB = (uint8_t *)FUN_0036a9a0(u6, /*stack2*/ 0);
    uint64_t b0 = DAT_004e7bb0;
    *(uint64_t *)(tB + 0x18) = DAT_004e7bb8;
    *(uint64_t *)(tB + 0x10) = b0;
    FUN_00350744(&DAT_005d37eb);
    *(sk_pair_t *)(tB + 0x20) = FUN_001a89a8();
    *(sk_pair_t *)(tB + 0x30) = FUN_00355fa0(&DAT_005d37ed);
    *(sk_pair_t *)(tB + 0x40) = FUN_00355fa0(&DAT_005d37f0);
    FUN_003538b0(&DAT_005d37f3);
    *(sk_pair_t *)(tB + 0x50) = FUN_001a89a8();
    *(sk_pair_t *)(tB + 0x60) = FUN_00355fa0(&DAT_005d37f7);
    FUN_00350744(&DAT_005d356c);
    *(sk_pair_t *)(tB + 0x70) = FUN_001a89a8();
    FUN_003538b0(&DAT_005d37fa);
    *(sk_pair_t *)(tB + 0x80) = FUN_001a89a8();
    *(sk_pair_t *)(tB + 0x90) = FUN_00355fa0(&DAT_005d37fe);
    FUN_00350744(&DAT_005d3801);
    *(sk_pair_t *)(tB + 0xa0) = FUN_001a89a8();
    *(sk_pair_t *)(tB + 0xb0) = FUN_00355fa0(&DAT_005d3803);
    FUN_003538b0(&DAT_005d3806);
    *(sk_pair_t *)(tB + 0xc0) = FUN_001a89a8();
    *(sk_pair_t *)(tB + 0xd0) = FUN_00355fa0(&DAT_005d380a);
    *(sk_pair_t *)(tB + 0xe0) = FUN_00355fa0(&DAT_005d380d);
    FUN_00350744(&DAT_005d3810);
    *(sk_pair_t *)(tB + 0xf0) = FUN_001a89a8();
    FUN_003538b0(&DAT_005d3812);
    *(sk_pair_t *)(tB + 0x100) = FUN_001a89a8();
    *(sk_pair_t *)(tB + 0x110) = FUN_00355fa0(&DAT_005d3816);
    *(sk_pair_t *)(tB + 0x120) = FUN_00355fa0(&DAT_005d3819);
    *(sk_pair_t *)(tB + 0x130) = FUN_00355fa0(&DAT_005d381c);
    *(sk_pair_t *)(tB + 0x140) = FUN_00355fa0(&DAT_005d381f);
    *(sk_pair_t *)(tB + 0x150) = FUN_00355fa0(&DAT_005d3822);
    FUN_00350744(&DAT_005d356a);
    *(sk_pair_t *)(tB + 0x160) = FUN_001a89a8();

    /* Table C (Hangul syllable trailing Jamo) */
    uint8_t *tC = (uint8_t *)FUN_0036a940(u6, 0x1e0, 7);
    uint64_t c0 = DAT_004e7bc0;
    *(uint64_t *)(tC + 0x18) = DAT_004e7bc8;
    *(uint64_t *)(tC + 0x10) = c0;
    FUN_003509f8(&DAT_005be7c0);
    *(sk_pair_t *)(tC + 0x20) = FUN_001a89a8();
    FUN_00350744(&DAT_005d37c4);
    *(sk_pair_t *)(tC + 0x30) = FUN_001a89a8();
    *(sk_pair_t *)(tC + 0x40) = FUN_00355fa0(&DAT_005d37c6);
    *(sk_pair_t *)(tC + 0x50) = FUN_00355fa0(&DAT_005d3825);
    FUN_00350744(&DAT_005d37c9);
    *(sk_pair_t *)(tC + 0x60) = FUN_001a89a8();
    *(sk_pair_t *)(tC + 0x70) = FUN_00355fa0(&DAT_005d3828);
    *(sk_pair_t *)(tC + 0x80) = FUN_00355fa0(&DAT_005d382b);
    FUN_00350744(&DAT_005d37cb);
    *(sk_pair_t *)(tC + 0x90) = FUN_001a89a8();
    FUN_00350744(&DAT_005d356e);
    *(sk_pair_t *)(tC + 0xa0) = FUN_001a89a8();
    *(sk_pair_t *)(tC + 0xb0) = FUN_00355fa0(&DAT_005d382e);
    *(sk_pair_t *)(tC + 0xc0) = FUN_00355fa0(&DAT_005d3831);
    *(sk_pair_t *)(tC + 0xd0) = FUN_00355fa0(&DAT_005d3834);
    *(sk_pair_t *)(tC + 0xe0) = FUN_00355fa0(&DAT_005d3837);
    *(sk_pair_t *)(tC + 0xf0) = FUN_00355fa0(&DAT_005d383a);
    *(sk_pair_t *)(tC + 0x100) = FUN_00355fa0(&DAT_005d383d);
    *(sk_pair_t *)(tC + 0x110) = FUN_00355fa0(&DAT_005d3840);
    FUN_00350744(&DAT_005d37d0);
    *(sk_pair_t *)(tC + 0x120) = FUN_001a89a8();
    FUN_00350744(&DAT_005d37d2);
    *(sk_pair_t *)(tC + 0x130) = FUN_001a89a8();
    *(sk_pair_t *)(tC + 0x140) = FUN_00355fa0(&DAT_005d3843);
    FUN_00350744(&DAT_005d37d7);
    *(sk_pair_t *)(tC + 0x150) = FUN_001a89a8();
    *(sk_pair_t *)(tC + 0x160) = FUN_00355fa0(&DAT_005d37d9);
    *(sk_pair_t *)(tC + 0x170) = FUN_00355fa0(&DAT_005d3846);
    FUN_00350744(&DAT_005d37dc);
    *(sk_pair_t *)(tC + 0x180) = FUN_001a89a8();
    FUN_00350744(&DAT_005d37e1);
    *(sk_pair_t *)(tC + 0x190) = FUN_001a89a8();
    FUN_00350744(&DAT_005d37e3);
    *(sk_pair_t *)(tC + 0x1a0) = FUN_001a89a8();
    FUN_00350744(&DAT_005d37e5);
    *(sk_pair_t *)(tC + 0x1b0) = FUN_001a89a8();
    FUN_00350744(&DAT_005c9984);
    *(sk_pair_t *)(tC + 0x1c0) = FUN_001a89a8();
    FUN_00350744(&DAT_005d37e9);
    *(sk_pair_t *)(tC + 0x1d0) = FUN_001a89a8();

    /* Hangul syllable decomposition for the current code point. */
    uint32_t d = (uint32_t)(cp - 0xac00);
    uint64_t vIdx = (uint64_t)((d % 0x24c) / 0x1c);
    FUN_0035163c(d / 0x24c);
    FUN_0019e690();
    uint64_t *leadRow = (uint64_t *)(tA + 0x20) + (d / 0x24c) * 2;
    uint64_t u11 = leadRow[0], u10 = leadRow[1];
    FUN_0036b588(tA);
    thunk_FUN_0036b270(u10);
    FUN_001e4b00();
    FUN_00002834();
    FUN_0036b6ac();
    FUN_003513e4(vIdx);
    FUN_0019e690();
    uint64_t u3 = *(uint64_t *)(((sk_pair_t *)(tB + 0x20))[vIdx].lo + 8);
    FUN_0036b588(tB);
    thunk_FUN_0036b270(u3);
    FUN_001e4b00();
    FUN_00002834();
    FUN_0036b6ac();
    FUN_0034fd4c();
    sk_pair_t a15 = FUN_001e3f70();
    FUN_003a25d4(u10);
    FUN_003a25d4(u3);
    sk_pair_t a14 = FUN_00351330();
    FUN_0019e690(a14.lo, a14.hi, tC);
    uint64_t tc0 = *(uint64_t *)(((sk_pair_t *)(tC + 0x20))[d % 0x1c].lo);
    sk_pair_t a4;
    a4.hi = tc0; a4.lo = a15.lo;
    uint64_t v12 = *(uint64_t *)(((sk_pair_t *)(tC + 0x20))[d % 0x1c].lo + 8);
    a14.hi = v12; a14.lo = a15.hi;
    FUN_0036b588(tC);
    thunk_FUN_0036b270(v12);
    FUN_001e4b00();
    FUN_00002834();
    FUN_0036b6ac();
    FUN_0008e388();
    FUN_00350a1c();
    FUN_001e3f70();
    FUN_00352c80();
    FUN_003a25d4(a15.hi);
    FUN_003a25d4(v12);
    FUN_0006e778(0x12);
    sk_pair_t result = FUN_00354410();
    FUN_00355754("HANGUL_SYLLABLE");
    FUN_001a89a8();
    FUN_0034aaf4();
    /* merge leading/trailing into the result (three-stage union) */
    if (/*x8*/ 0 == 0 && (((u11 & ((uint64_t)tC ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(tC);
        result = a14;
    } else {
        if (((uint64_t)tC >> 0x3d & 1) == 0) {
            FUN_0034a7ac();
        } else if ((v12 >> 0x3d & 1) != 0) {
            FUN_00351714();
            FUN_003497c8();
            if (!(bool)0) {
                FUN_00353a90();
                FUN_003a25d4(v12);
                result.lo = u11;
                result.hi = u3;
                FUN_0035849c();
                goto merge2;
            }
        }
        tC = (uint8_t *)result.lo;
        FUN_0034c5bc();
        FUN_002a4c98();
        FUN_003a25d4(v12);
        a14 = result;
    }
merge2:
    uint64_t u11b = a14.hi;
    FUN_0034a900();
    if (/*x8_00*/ 0 == 0 && (((a14.lo & (u11b ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(u11b);
        result = a4;
    } else {
        if ((u11b >> 0x3d & 1) == 0) {
            FUN_0034a798();
        } else if ((tc0 >> 0x3d & 1) != 0) {
            FUN_003504c4();
            FUN_003495a8();
            if (!(bool)0) {
                FUN_0034f198();
                FUN_003a25d4();
                FUN_003a25d4(tc0);
                result.lo = (uint64_t)tC;
                result.hi = a14.lo;
                FUN_00355f70();
                goto merge3;
            }
        }
        FUN_0034c0a4();
        FUN_002a4c98();
        FUN_003a25d4(tc0);
        a4 = result;
    }
merge3:
    uint64_t u10b = a4.hi;
    FUN_003497ec();
    FUN_001a89a8();
    FUN_003496cc();
    if (/*x8_01*/ 0 == 0 && (((a4.lo & (u10b ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(u10b);
    } else {
        if ((u10b >> 0x3d & 1) == 0) {
            FUN_0034a7ac();
        } else if ((u11b >> 0x3d & 1) != 0) {
            FUN_00084180();
            FUN_003497c8();
            if (!(bool)0) {
                FUN_0034bd90();
                FUN_003a25d4();
                FUN_003a25d4(u11b);
                FUN_0035a70c();
                goto done;
            }
        }
        FUN_0034c5bc();
        FUN_002a4c98();
        FUN_003a25d4(u11b);
    }
done:
    sk_pair_t r = FUN_003504c4();
    FUN_0008e500(r.lo, r.hi, /*x1*/ 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002bcdf8 @ 0x002bcdf8   (est. sk_swift_grapheme_property_table_b)
 * Ghidra: void FUN_002bcdf8(void)
 * Grapheme-cluster property classifier for the current scalar: Hangul
 * syllables defer to sk_swift_grapheme_property_table_a; variation
 * selectors, CJK unified/compatibility ideographs, Tangut, Khitan, Nushu
 * and Egyptian hieroglyphs are each matched against their Unicode ranges
 * and their property strings are combined through the shared Swift string
 * builders. The result pair is committed at the end.
 * Confidence: low (data-table classifier; property strings resolved by
 *   address only, e.g. s_VARIATION_SELECTOR__005d37b0).
 */
void sk_swift_grapheme_property_table_b(void)
{
    sk_pair_t v10 = FUN_00354744();
    uint8_t *p8 = (uint8_t *)v10.lo;
    sk_pair_t v11 = FUN_002366a0(0x10, 1, p8);
    uint8_t *p5 = (uint8_t *)v11.hi;
    uint32_t cp = v10.lo & 0xffffffff;
    bool vs_flag;
    if ((cp - 0xac00) >> 2 < 0xae9) {
        FUN_003a25d4(p5);
        sk_swift_grapheme_property_table_a(p8);
        FUN_00351f28();
        goto commit;
    }
    vs_flag = (cp - 0xe0100 == 0xef);
    if (cp - 0xe0100 < 0xf0) {
        /* Variation selectors */
        FUN_003a25d4(p5);
        FUN_0006e778(0x15);
        sk_pair_t v12 = FUN_00354e0c();
        FUN_001a89a8("VARIATION_SELECTOR_", 0x13, 1);
        FUN_00358f84();
        FUN_0034a260();
        uint8_t *p3;
        if (/*x8*/ 0 == 0 && ((((uint64_t)/*x21*/ 0 & ((uint64_t)/*x20*/ 0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            v11 = FUN_003a25d4();
            /* stk0 = x23, stk1 = p5 */
        } else {
            if (((uint64_t)/*x20*/ 0 >> 0x3d & 1) == 0)
                FUN_0034c6e4((uint64_t)/*x23*/ 0 & 0xffffffffffff);
            else if (((uint64_t)p5 >> 0x3d & 1) != 0) {
                FUN_00350ed0();
                p3 = (uint8_t *)FUN_0034a390();
                if (!vs_flag) {
                    FUN_003531fc();
                    FUN_003a25d4();
                    v11 = FUN_003a25d4();
                    goto vs_cont;
                }
            }
            v11 = FUN_00350524();
            FUN_002a4c98(v11.lo, v11.hi, 0);
            v11 = FUN_003a25d4(p5);
        }
vs_cont:
        p3 = /*stk1*/ p5;
        p5 = /*stk0*/ 0;
        FUN_00356340(v11.lo, v11.hi, cp - 0xe00ef);
        FUN_002366a0();
        FUN_00357b7c();
        FUN_0034bf64((uint64_t)p5 & 0xffffffffffff);
        /* merge stage */
        if (/*x8_02*/ 0 == 0 && ((((uint64_t)p5 & ((uint64_t)p3 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_003a25d4(p3);
        } else {
            if (((uint64_t)p3 >> 0x3d & 1) == 0)
                FUN_0034ced8((uint64_t)/*x24*/ 0 & 0xffffffffffff);
            else if (((uint64_t)/*x21*/ 0 >> 0x3d & 1) != 0) {
                FUN_00350524();
                FUN_0034b89c();
                if (!vs_flag) {
                    FUN_0034f584();
                    FUN_003a25d4();
                    FUN_003a25d4(p3);
                    goto vs_cont2;
                }
            }
            v11 = FUN_003507bc();
            FUN_002a4c98(v11.lo, v11.hi, 0);
            FUN_003a25d4(/*x21*/ 0);
        }
vs_cont2:
        p5 = /*stk1*/ p3;
        p3 = /*stk0*/ 0;
        FUN_003497ec();
        FUN_001a89a8();
        FUN_0034e0e4();
        FUN_0034f98c();
        if (/*x8_03*/ 0 != 0 ||
            ((((uint64_t)p3 & ((uint64_t)p5 ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0)) {
            if (((uint64_t)p5 >> 0x3d & 1) == 0) {
                FUN_0034a7ac();
            } else if (((uint64_t)p8 >> 0x3d & 1) != 0) {
                FUN_003507bc();
                FUN_003497c8();
                if (!vs_flag) {
                    FUN_00350df4();
                    FUN_003a25d4();
                    FUN_003a25d4(p5);
                    FUN_0035aafc();
                    goto commit;
                }
            }
            FUN_0034c5bc();
            FUN_002a4c98();
            FUN_003a25d4(p8);
            goto commit;
        }
    } else {
        uint64_t u9 = FUN_0035a334(cp + (int)DAT_004e7be0, /*concat*/ 0,
                                   DAT_004e7bf0, DAT_004e7c00);
        sk_pair_t v12 = v11;
        vs_flag = (cp - 0x31350 == 0x2129);
        if ((u9 & 1) != 0 || cp - 0x31350 < 0x212a) {
            /* CJK unified ideograph */
            FUN_0006e778(0x18);
            FUN_00352340();
            FUN_001a89a8("CJK_UNIFIED_IDEOGRAPH_", 0x16, 1);
            FUN_0034aaf4();
            if (/*x8_00*/ 0 == 0 &&
                ((((uint64_t)/*x24*/ 0 & ((uint64_t)/*x20*/ 0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4();
            } else {
                if (((uint64_t)/*x20*/ 0 >> 0x3d & 1) == 0)
                    FUN_0034a7ac();
                else if (((uint64_t)p8 >> 0x3d & 1) != 0) {
                    FUN_00351714();
                    FUN_003497c8();
                    if (!vs_flag) {
                        FUN_000778b4();
                        FUN_003a25d4(p8);
                        FUN_003a25d4();
                        FUN_0035849c();
                        goto cjk2;
                    }
                }
                FUN_0034c5bc();
                FUN_002a4c98();
                FUN_003a25d4(p8);
            }
cjk2:
            FUN_0034a900();
            if (/*x8_04*/ 0 == 0 &&
                ((((uint64_t)/*x23*/ 0 & ((uint64_t)p8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4(p8);
            } else {
                if (((uint64_t)p8 >> 0x3d & 1) == 0)
                    FUN_0034a798();
                else if (((uint64_t)p5 >> 0x3d & 1) != 0) {
                    FUN_003504c4();
                    FUN_003495a8();
                    if (!vs_flag) {
                        FUN_0034f198();
                        FUN_003a25d4();
                        FUN_003a25d4(p5);
                        FUN_00355f70();
                        goto cjk3;
                    }
                }
                FUN_0034c0a4();
                FUN_002a4c98();
                FUN_003a25d4(p5);
                v11.lo = /*stk0*/ 0;
                v11.hi = /*stk1*/ 0;
                v12 = v11;
            }
cjk3:
            p5 = (uint8_t *)v11.hi;
            FUN_003497ec();
            FUN_001a89a8();
            FUN_003496cc();
            if (/*x8_05*/ 0 != 0 ||
                (((v11.lo & ((uint64_t)p5 ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0)) {
                if (((uint64_t)p5 >> 0x3d & 1) == 0) {
                    FUN_0034a7ac();
                } else if (((uint64_t)p8 >> 0x3d & 1) != 0) {
                    FUN_00084180();
                    FUN_003497c8();
                    if (!vs_flag) {
                        FUN_00350b90();
                        FUN_003a25d4(p8);
                        FUN_003a25d4(p5);
                        FUN_00356018();
                        goto commit;
                    }
                }
                FUN_0034c5bc();
                FUN_002a4c98();
                FUN_003a25d4(p8);
                goto commit;
            }
            goto done;
        }
        vs_flag = (cp - 0xf900 == 0x16e);
        if ((cp - 0xf900 < 0x16e) || (vs_flag = (cp - 0xfa70 == 0x6a), cp - 0xfa70 < 0x6a) ||
            (vs_flag = (cp - 0x2f800 == 0x21d), cp - 0x2f800 < 0x21e)) {
            /* CJK compatibility ideograph */
            FUN_0006e778(0x1e);
            FUN_00352340();
            FUN_001a89a8("CJK_COMPATIBILITY_IDEOGRAPH_", 0x1c, 1);
            FUN_0034aaf4();
            if (/*x8_01*/ 0 == 0 &&
                ((((uint64_t)/*x24*/ 0 & ((uint64_t)/*x20*/ 0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4();
            } else {
                if (((uint64_t)/*x20*/ 0 >> 0x3d & 1) == 0) {
                    FUN_0034a7ac();
                    FUN_0034c5bc();
                    FUN_002a4c98();
                } else if (((uint64_t)p8 >> 0x3d & 1) != 0) {
                    FUN_00351714();
                    FUN_003497c8();
                    if (vs_flag) {
                        FUN_0034c5bc();
                        FUN_002a4c98();
                    } else {
                        FUN_000778b4();
                        FUN_003a25d4(p8);
                        FUN_003a25d4();
                        FUN_0035849c();
                    }
                } else {
                    FUN_0034c5bc();
                    FUN_002a4c98();
                }
            }
            FUN_0034a900();
            if (/*x8_07*/ 0 != 0 ||
                ((((uint64_t)/*x23*/ 0 & ((uint64_t)p8 ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0)) {
                if (((uint64_t)p8 >> 0x3d & 1) == 0) {
                    FUN_0034a798();
                } else if (((uint64_t)p5 >> 0x3d & 1) != 0) {
                    FUN_003504c4();
                    FUN_003495a8();
                    if (!vs_flag) {
                        FUN_0034f198();
                        FUN_003a25d4();
                        FUN_003a25d4(p5);
                        FUN_00355f70();
                        goto cjk3b;
                    }
                }
                FUN_0034c0a4();
                FUN_002a4c98();
                FUN_003a25d4(p5);
                goto done2;
            }
            FUN_003a25d4(p8);
        } else {
            bool b1 = 2 < (cp - 0x17000) >> 0xb;
            vs_flag = b1 && (cp - 0x18d00 == 0x1e);
            if (!b1 || cp - 0x18d00 < 0x1f) {
                /* Tangut ideograph */
                FUN_0006e778(0x13);
                FUN_00352340();
                FUN_001a89a8("TANGUT_IDEOGRAPH_", 0x11, 1);
                FUN_0034aaf4();
                if (/*x8_06*/ 0 == 0 &&
                    ((((uint64_t)/*x24*/ 0 & ((uint64_t)/*x20*/ 0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                    FUN_003a25d4();
                } else {
                    FUN_0034dd74();
                    FUN_00267820();
                    FUN_003a25d4(p8);
                }
                FUN_0034a900();
                if (/*x8_07*/ 0 == 0 &&
                    ((((uint64_t)/*x23*/ 0 & ((uint64_t)p8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
                    goto done_tang;
                FUN_0034a798();
                goto done2;
            }
            vs_flag = (cp - 0x18b00 == 0x1d5);
            if (cp - 0x18b00 < 0x1d6) {
                FUN_0006e778(0x20);
                FUN_00352340();
                FUN_001a89a8("KHITAN_SMALL_SCRIPT_CHARACTER_", 0x1e, 1);
                FUN_0034aaf4();
                goto tangut_common;
            }
            vs_flag = (cp - 0x1b170 == 0x18b);
            if (cp - 0x1b170 < 0x18c) {
                FUN_0006e778(0x12);
                FUN_00352340();
                FUN_001a89a8("NUSHU_CHARACTER_", 0x10, 1);
                FUN_0034aaf4();
                goto tangut_common;
            }
            if ((cp >> 5 < 0x9a3) || (0x143fa < cp)) {
                FUN_003a25d4(p5);
                FUN_003599c0();
                goto commit;
            }
            FUN_0006e778(0x16);
            FUN_00352340();
            FUN_00359cd8("EGYPTIAN_HIEROGLYPH_");
            FUN_001a89a8();
            FUN_0034aaf4();
            if (/*x8_09*/ 0 == 0 &&
                ((((uint64_t)/*x24*/ 0 & ((uint64_t)/*x20*/ 0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4();
            } else {
                FUN_0034dd74();
                FUN_00267820();
                FUN_003a25d4(p8);
            }
            p8 = /*stk1*/ 0;
            FUN_0034a900();
            if (/*x8_10*/ 0 == 0 &&
                ((((uint64_t)/*stk0*/ 0 & ((uint64_t)p8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
                goto done_tang;
            FUN_00084180();
            FUN_00267820();
            goto done2;
tangut_common:
            FUN_0034aaf4();
            if (/*x8_06*/ 0 == 0 &&
                ((((uint64_t)/*x24*/ 0 & ((uint64_t)/*x20*/ 0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4();
            } else {
                FUN_0034dd74();
                FUN_00267820();
                FUN_003a25d4(p8);
            }
            p8 = /*stk1*/ 0;
            FUN_0034a900();
            if (/*x8_07*/ 0 != 0 ||
                ((((uint64_t)/*stk0*/ 0 & ((uint64_t)p8 ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0)) {
                FUN_00084180();
                FUN_00267820();
                goto done2;
            }
done_tang:
            FUN_003a25d4(p8);
        }
cjk3b:
        p5 = (uint8_t *)v11.hi;
        FUN_003497ec();
        FUN_001a89a8();
        FUN_003496cc();
        if (/*x8_08*/ 0 != 0 ||
            (((v11.lo & ((uint64_t)p5 ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0)) {
            FUN_0034dd74();
            FUN_00267820();
            FUN_003a25d4(p8);
            goto commit;
        }
done2:
        ;
    }
done:
    FUN_003a25d4(p5);
commit:
    sk_pair_t r = FUN_003504c4();
    FUN_003544c8(r.lo, r.hi, v10.hi);
}

/*--------------------------------------------------------------------*/
/* FUN_002bd4e4 @ 0x002bd4e4   (est. sk_swift_grapheme_property_lookup)
 * Ghidra: void FUN_002bd4e4(undefined8 param_1)
 * Runs sk_swift_grapheme_property_table_b and, on a zero return, performs
 * the default string allocation/fill and release path.
 * Confidence: low.
 */
void sk_swift_grapheme_property_lookup(uint64_t p1)
{
    sk_swift_grapheme_property_table_b();
    if (/*x1*/ 0 == 0) {
        FUN_0029af30(0x58, p1);
        FUN_0034f064();
        if (/*x8*/ 0 == 0) {
            FUN_003a25d4(/*x1_00*/ 0);
            FUN_00019858();
        }
    }
}

