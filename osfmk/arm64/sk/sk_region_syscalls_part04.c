/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 04: 0x31d518-0x322450 syscall/exception-entry region.
 * All names are estimates unless string/header matched.
 * Uses seL4/cL4 vocabulary; the large functions in this range are Swift
 * runtime buffer/COW/refcount helpers pulled into the kernel's syscall path
 * (UnsafeBufferPointer, _fatalError preconditions). */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* ------------------------------------------------------------------ *
 * Generic calling-convention helpers (recreated from Ghidra artifacts).
 * ------------------------------------------------------------------ */
/* Unspecified-argument function pointer (K&R empty-paren): allows calls
 * with any number of arguments, matching the register-aliased helpers. */
typedef uint64_t (*sk_fn_t)();

/* Ghidra SBORROW8(a,b): signed underflow of (a - b). */
#define SBORROW8(a,b)  ((((uint64_t)(a) ^ (uint64_t)(b)) &                           ((uint64_t)(a) ^ ((uint64_t)(a)-(uint64_t)(b)))) >> 63)
/* Ghidra SCARRY8(a,b): signed overflow of (a + b). */
#define SCARRY8(a,b)   ((((uint64_t)(a) ^ (uint64_t)(b)) &                           ((uint64_t)(a) ^ ((uint64_t)(a)+(uint64_t)(b)))) >> 63)

/* Ghidra SoftwareBreakpoint(n, addr): kernel debug trap. */
#define SK_TRAP() __builtin_trap()
/* Ghidra SUB168(x,n): low n bits. SEXT816(x): sign-extend 16-bit. */
#define SUB168(x,n) ((uint64_t)(x) & ((1ull<<(n))-1ull))
#define SEXT816(x)  ((int64_t)(int16_t)(uint16_t)(x))

/* ------------------------------------------------------------------ *
 * Data symbols (strings / globals referenced by these functions).
 * ------------------------------------------------------------------ */
extern sk_fn_t  DAT_00658c00;                 /* function-pointer global (Swift retain/task hook) */
extern uint64_t DAT_00613644, DAT_0061368c;   /* static string arguments */
extern uint64_t DAT_004ea4dc, DAT_004edcd0;
extern uint64_t DAT_004edd08, DAT_004edd94;
extern uint64_t DAT_0000d019;
extern uint64_t DAT_005be7c0;                 /* generic failure descriptor */
extern uint64_t DAT_003207d0, DAT_003471a4, DAT_003471a8;
extern uint64_t DAT_00656270;                 /* uRam0000000000656270 global write target */

extern const char s_Fatal_error_005accd0[];
extern const char s_Swift_UnsafeBufferPointer_swift_005cdc10[];
extern const char s_UnsafeMutableBufferPointer_withC_005d3350[];
extern const char s_UnsafeMutableRawBufferPointer_co_005d1070[];
extern const char s_Swift_UnsafeRawBufferPointer_swi_005cde40[];
extern const char s_Swift_UnsafeRawPointer_swift_005cf1b0[];
extern const char s_UnsafeMutableRawBufferPointer_wi_005d31e0[];
extern const char s_buffer_cannot_contain_every_elem_005d0570[];
extern const char s_unsafelyUnwrapped_of_nil_optiona_005ce1c0[];
extern const char s_Swift_Optional_swift_005ce1f0[];
extern const char s_UnsafeMutablePointer_update_with_005cf3f0[];
extern const char s_Unexpectedly_found_nil_while_unw_005cd7d0[];
extern const char s__start__005d2d87[];
extern const char FUN_005d0b20[];             /* string constant used as pointer arg */

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a note; their
 * bodies are reconstructed by the range worker that owns them).
 * Ghidra thunk_* names map to their underlying FUN_ addresses.
 * ------------------------------------------------------------------ */
extern uint64_t thunk_FUN_00012568();
extern uint64_t thunk_FUN_0028c754();
extern uint64_t thunk_FUN_00359208();
extern uint64_t thunk_FUN_0036b270();
extern uint64_t FUN_00000000(); /* out of slice */
extern uint64_t FUN_00002534(); /* out of slice */
extern uint64_t FUN_00012568(); /* out of slice */
extern uint64_t FUN_00019858(); /* out of slice */
extern uint64_t FUN_0001a1c8(); /* out of slice */
extern uint64_t FUN_00021480(); /* out of slice */
extern uint64_t FUN_00027788(); /* out of slice */
extern uint64_t FUN_00041138(); /* out of slice */
extern uint64_t FUN_00068e14(); /* out of slice */
extern uint64_t FUN_0006b6f4(); /* out of slice */
extern uint64_t FUN_0006e778(); /* out of slice */
extern uint64_t FUN_0007c028(); /* out of slice */
extern uint64_t FUN_000839d8(); /* out of slice */
extern uint64_t FUN_0008412c(); /* out of slice */
extern uint64_t FUN_00084180(); /* out of slice */
extern uint64_t FUN_00084220(); /* out of slice */
extern uint64_t FUN_00084234(); /* out of slice */
extern uint64_t FUN_0008e500(); /* out of slice */
extern uint64_t FUN_0008e518(); /* out of slice */
extern uint64_t FUN_0009461c(); /* out of slice */
extern uint64_t FUN_000a6e14(); /* out of slice */
extern uint64_t FUN_000dbde8(); /* out of slice */
extern uint64_t FUN_00100c38(); /* out of slice */
extern uint64_t FUN_00100efc(); /* out of slice */
extern uint64_t FUN_00117d14(); /* out of slice */
extern uint64_t FUN_0014ae44(); /* out of slice */
extern uint64_t FUN_0016186c(); /* out of slice */
extern uint64_t FUN_0019c9cc(); /* out of slice */
extern uint64_t FUN_0019ce60(); /* out of slice */
extern uint64_t FUN_0019dadc(); /* out of slice */
extern uint64_t FUN_0019f148(); /* out of slice */
extern uint64_t FUN_0019f1ec(); /* out of slice */
extern uint64_t FUN_0019fd10(); /* out of slice */
extern uint64_t FUN_0019fe7c(); /* out of slice */
extern uint64_t FUN_001a0158(); /* out of slice */
extern uint64_t FUN_001a0194(); /* out of slice */
extern uint64_t FUN_001a89a8(); /* out of slice */
extern uint64_t FUN_001afe4c(); /* out of slice */
extern uint64_t FUN_001d88fc(); /* out of slice */
extern uint64_t FUN_001dff60(); /* out of slice */
extern uint64_t FUN_001e088c(); /* out of slice */
extern uint64_t FUN_001e3048(); /* out of slice */
extern uint64_t FUN_001e3968(); /* out of slice */
extern uint64_t FUN_001e3f70(); /* out of slice */
extern uint64_t FUN_001e6608(); /* out of slice */
extern uint64_t FUN_001e6b6c(); /* out of slice */
extern uint64_t FUN_001e6ff8(); /* out of slice */
extern uint64_t FUN_001e762c(); /* out of slice */
extern uint64_t FUN_00205844(); /* out of slice */
extern uint64_t FUN_0021867c(); /* out of slice */
extern uint64_t FUN_0022b21c(); /* out of slice */
extern uint64_t FUN_0022b26c(); /* out of slice */
extern uint64_t FUN_002364dc(); /* out of slice */
extern uint64_t FUN_0024c0d0(); /* out of slice */
extern uint64_t FUN_002514f0(); /* out of slice */
extern uint64_t FUN_0027b204(); /* out of slice */
extern uint64_t FUN_0027ffd8(); /* out of slice */
extern uint64_t FUN_00286b94(); /* out of slice */
extern uint64_t FUN_00286e80(); /* out of slice */
extern uint64_t FUN_0028b6cc(); /* out of slice */
extern uint64_t FUN_0028c754(); /* out of slice */
extern uint64_t FUN_0028e8fc(); /* out of slice */
extern uint64_t FUN_0029200c(); /* out of slice */
extern uint64_t FUN_00292204(); /* out of slice */
extern uint64_t FUN_002922b0(); /* out of slice */
extern uint64_t FUN_00293fc8(); /* out of slice */
extern uint64_t FUN_00298cb8(); /* out of slice */
extern uint64_t FUN_002993a4(); /* out of slice */
extern uint64_t FUN_00299c38(); /* out of slice */
extern uint64_t FUN_0029aa14(); /* out of slice */
extern uint64_t FUN_0029b264(); /* out of slice */
extern uint64_t FUN_002a4c98(); /* out of slice */
extern uint64_t FUN_002bedcc(); /* out of slice */
extern uint64_t FUN_002bf038(); /* out of slice */
extern uint64_t FUN_00310954(); /* out of slice */
extern uint64_t FUN_00310b08(); /* out of slice */
extern uint64_t FUN_00310d04(); /* out of slice */
extern uint64_t FUN_00310d68(); /* out of slice */
extern uint64_t FUN_00310e08(); /* out of slice */
extern uint64_t FUN_0031b080(); /* out of slice */
extern uint64_t FUN_00344cf4(); /* out of slice */
extern uint64_t FUN_00347de8(); /* out of slice */
extern uint64_t FUN_00348074(); /* out of slice */
extern uint64_t FUN_003480ac(); /* out of slice */
extern uint64_t FUN_00348160(); /* out of slice */
extern uint64_t FUN_00348194(); /* out of slice */
extern uint64_t FUN_00348284(); /* out of slice */
extern uint64_t FUN_003482c4(); /* out of slice */
extern uint64_t FUN_0034834c(); /* out of slice */
extern uint64_t FUN_00348404(); /* out of slice */
extern uint64_t FUN_003486b8(); /* out of slice */
extern uint64_t FUN_0034878c(); /* out of slice */
extern uint64_t FUN_00348898(); /* out of slice */
extern uint64_t FUN_003488bc(); /* out of slice */
extern uint64_t FUN_003488d8(); /* out of slice */
extern uint64_t FUN_0034895c(); /* out of slice */
extern uint64_t FUN_00348a80(); /* out of slice */
extern uint64_t FUN_00348abc(); /* out of slice */
extern uint64_t FUN_00348b7c(); /* out of slice */
extern uint64_t FUN_00348bbc(); /* out of slice */
extern uint64_t FUN_00348e18(); /* out of slice */
extern uint64_t FUN_00348f50(); /* out of slice */
extern uint64_t FUN_00349098(); /* out of slice */
extern uint64_t FUN_00349644(); /* out of slice */
extern uint64_t FUN_003497c8(); /* out of slice */
extern uint64_t FUN_003498c4(); /* out of slice */
extern uint64_t FUN_00349a04(); /* out of slice */
extern uint64_t FUN_00349c98(); /* out of slice */
extern uint64_t FUN_00349cbc(); /* out of slice */
extern uint64_t FUN_0034a1f8(); /* out of slice */
extern uint64_t FUN_0034a210(); /* out of slice */
extern uint64_t FUN_0034a618(); /* out of slice */
extern uint64_t FUN_0034a7ac(); /* out of slice */
extern uint64_t FUN_0034a900(); /* out of slice */
extern uint64_t FUN_0034aa3c(); /* out of slice */
extern uint64_t FUN_0034b13c(); /* out of slice */
extern uint64_t FUN_0034b178(); /* out of slice */
extern uint64_t FUN_0034b18c(); /* out of slice */
extern uint64_t FUN_0034b1a0(); /* out of slice */
extern uint64_t FUN_0034b348(); /* out of slice */
extern uint64_t FUN_0034b3c8(); /* out of slice */
extern uint64_t FUN_0034b3d8(); /* out of slice */
extern uint64_t FUN_0034b3e8(); /* out of slice */
extern uint64_t FUN_0034b508(); /* out of slice */
extern uint64_t FUN_0034b518(); /* out of slice */
extern uint64_t FUN_0034b528(); /* out of slice */
extern uint64_t FUN_0034b5e8(); /* out of slice */
extern uint64_t FUN_0034b668(); /* out of slice */
extern uint64_t FUN_0034b7c8(); /* out of slice */
extern uint64_t FUN_0034b824(); /* out of slice */
extern uint64_t FUN_0034b87c(); /* out of slice */
extern uint64_t FUN_0034b89c(); /* out of slice */
extern uint64_t FUN_0034b8bc(); /* out of slice */
extern uint64_t FUN_0034bc94(); /* out of slice */
extern uint64_t FUN_0034bd90(); /* out of slice */
extern uint64_t FUN_0034bddc(); /* out of slice */
extern uint64_t FUN_0034c434(); /* out of slice */
extern uint64_t FUN_0034c4fc(); /* out of slice */
extern uint64_t FUN_0034c55c(); /* out of slice */
extern uint64_t FUN_0034c5bc(); /* out of slice */
extern uint64_t FUN_0034c5dc(); /* out of slice */
extern uint64_t FUN_0034c664(); /* out of slice */
extern uint64_t FUN_0034c8b8(); /* out of slice */
extern uint64_t FUN_0034c9c8(); /* out of slice */
extern uint64_t FUN_0034ca08(); /* out of slice */
extern uint64_t FUN_0034ce78(); /* out of slice */
extern uint64_t FUN_0034cf14(); /* out of slice */
extern uint64_t FUN_0034d044(); /* out of slice */
extern uint64_t FUN_0034d130(); /* out of slice */
extern uint64_t FUN_0034d140(); /* out of slice */
extern uint64_t FUN_0034d180(); /* out of slice */
extern uint64_t FUN_0034d384(); /* out of slice */
extern uint64_t FUN_0034d3e4(); /* out of slice */
extern uint64_t FUN_0034dab8(); /* out of slice */
extern uint64_t FUN_0034dae8(); /* out of slice */
extern uint64_t FUN_0034dd64(); /* out of slice */
extern uint64_t FUN_0034de14(); /* out of slice */
extern uint64_t FUN_0034def4(); /* out of slice */
extern uint64_t FUN_0034e374(); /* out of slice */
extern uint64_t FUN_0034e424(); /* out of slice */
extern uint64_t FUN_0034e5fc(); /* out of slice */
extern uint64_t FUN_0034edc8(); /* out of slice */
extern uint64_t FUN_0034ee38(); /* out of slice */
extern uint64_t FUN_0034f078(); /* out of slice */
extern uint64_t FUN_0034f454(); /* out of slice */
extern uint64_t FUN_0034f584(); /* out of slice */
extern uint64_t FUN_0034f98c(); /* out of slice */
extern uint64_t FUN_00350258(); /* out of slice */
extern uint64_t FUN_00350328(); /* out of slice */
extern uint64_t FUN_00350410(); /* out of slice */
extern uint64_t FUN_00350470(); /* out of slice */
extern uint64_t FUN_0035047c(); /* out of slice */
extern uint64_t FUN_003504f4(); /* out of slice */
extern uint64_t FUN_0035050c(); /* out of slice */
extern uint64_t FUN_00350524(); /* out of slice */
extern uint64_t FUN_00350560(); /* out of slice */
extern uint64_t FUN_003505e8(); /* out of slice */
extern uint64_t FUN_0035060c(); /* out of slice */
extern uint64_t FUN_00350720(); /* out of slice */
extern uint64_t FUN_003508c0(); /* out of slice */
extern uint64_t FUN_003508e4(); /* out of slice */
extern uint64_t FUN_003508f0(); /* out of slice */
extern uint64_t FUN_003509b0(); /* out of slice */
extern uint64_t FUN_003509c8(); /* out of slice */
extern uint64_t FUN_00350aa0(); /* out of slice */
extern uint64_t FUN_00350aac(); /* out of slice */
extern uint64_t FUN_00350adc(); /* out of slice */
extern uint64_t FUN_00350b0c(); /* out of slice */
extern uint64_t FUN_00350b90(); /* out of slice */
extern uint64_t FUN_00350bfc(); /* out of slice */
extern uint64_t FUN_00350cb4(); /* out of slice */
extern uint64_t FUN_00351094(); /* out of slice */
extern uint64_t FUN_00351100(); /* out of slice */
extern uint64_t FUN_00351124(); /* out of slice */
extern uint64_t FUN_00351178(); /* out of slice */
extern uint64_t FUN_003512c0(); /* out of slice */
extern uint64_t FUN_003512cc(); /* out of slice */
extern uint64_t FUN_00351378(); /* out of slice */
extern uint64_t FUN_00351488(); /* out of slice */
extern uint64_t FUN_003514e8(); /* out of slice */
extern uint64_t FUN_00351500(); /* out of slice */
extern uint64_t FUN_00351584(); /* out of slice */
extern uint64_t FUN_003515b4(); /* out of slice */
extern uint64_t FUN_003515fc(); /* out of slice */
extern uint64_t FUN_003516d8(); /* out of slice */
extern uint64_t FUN_00351774(); /* out of slice */
extern uint64_t FUN_00351790(); /* out of slice */
extern uint64_t FUN_0035193c(); /* out of slice */
extern uint64_t FUN_00351a50(); /* out of slice */
extern uint64_t FUN_00351a5c(); /* out of slice */
extern uint64_t FUN_00351be0(); /* out of slice */
extern uint64_t FUN_00351bec(); /* out of slice */
extern uint64_t FUN_00351c64(); /* out of slice */
extern uint64_t FUN_00351dcc(); /* out of slice */
extern uint64_t FUN_00351e08(); /* out of slice */
extern uint64_t FUN_00351e90(); /* out of slice */
extern uint64_t FUN_00351f28(); /* out of slice */
extern uint64_t FUN_003523f0(); /* out of slice */
extern uint64_t FUN_003524c8(); /* out of slice */
extern uint64_t FUN_00352720(); /* out of slice */
extern uint64_t FUN_0035272c(); /* out of slice */
extern uint64_t FUN_00352870(); /* out of slice */
extern uint64_t FUN_00352980(); /* out of slice */
extern uint64_t FUN_00352c34(); /* out of slice */
extern uint64_t FUN_00352c74(); /* out of slice */
extern uint64_t FUN_00352c80(); /* out of slice */
extern uint64_t FUN_00352d1c(); /* out of slice */
extern uint64_t FUN_00352e60(); /* out of slice */
extern uint64_t FUN_00352e84(); /* out of slice */
extern uint64_t FUN_00352ea8(); /* out of slice */
extern uint64_t FUN_00352efc(); /* out of slice */
extern uint64_t FUN_00353098(); /* out of slice */
extern uint64_t FUN_003534d4(); /* out of slice */
extern uint64_t FUN_00353510(); /* out of slice */
extern uint64_t FUN_0035351c(); /* out of slice */
extern uint64_t FUN_0035370c(); /* out of slice */
extern uint64_t FUN_00353830(); /* out of slice */
extern uint64_t FUN_0035396c(); /* out of slice */
extern uint64_t FUN_00353978(); /* out of slice */
extern uint64_t FUN_00353b40(); /* out of slice */
extern uint64_t FUN_00353b94(); /* out of slice */
extern uint64_t FUN_00353c54(); /* out of slice */
extern uint64_t FUN_00353d64(); /* out of slice */
extern uint64_t FUN_00353ef0(); /* out of slice */
extern uint64_t FUN_0035401c(); /* out of slice */
extern uint64_t FUN_003542b8(); /* out of slice */
extern uint64_t FUN_003542c4(); /* out of slice */
extern uint64_t FUN_0035448c(); /* out of slice */
extern uint64_t FUN_003546fc(); /* out of slice */
extern uint64_t FUN_00354708(); /* out of slice */
extern uint64_t FUN_00354720(); /* out of slice */
extern uint64_t FUN_003548dc(); /* out of slice */
extern uint64_t FUN_00354a34(); /* out of slice */
extern uint64_t FUN_00354b98(); /* out of slice */
extern uint64_t FUN_00354d08(); /* out of slice */
extern uint64_t FUN_00354ddc(); /* out of slice */
extern uint64_t FUN_00354e00(); /* out of slice */
extern uint64_t FUN_00354ef8(); /* out of slice */
extern uint64_t FUN_00355190(); /* out of slice */
extern uint64_t FUN_003554e0(); /* out of slice */
extern uint64_t FUN_00355968(); /* out of slice */
extern uint64_t FUN_003559d8(); /* out of slice */
extern uint64_t FUN_00355b68(); /* out of slice */
extern uint64_t FUN_00355c78(); /* out of slice */
extern uint64_t FUN_00355d10(); /* out of slice */
extern uint64_t FUN_00355d6c(); /* out of slice */
extern uint64_t FUN_00355f4c(); /* out of slice */
extern uint64_t FUN_00355f7c(); /* out of slice */
extern uint64_t FUN_00356188(); /* out of slice */
extern uint64_t FUN_003562f8(); /* out of slice */
extern uint64_t FUN_00356340(); /* out of slice */
extern uint64_t FUN_0035662c(); /* out of slice */
extern uint64_t FUN_00356ad0(); /* out of slice */
extern uint64_t FUN_00356ae8(); /* out of slice */
extern uint64_t FUN_00356c84(); /* out of slice */
extern uint64_t FUN_00356d20(); /* out of slice */
extern uint64_t FUN_00356f80(); /* out of slice */
extern uint64_t FUN_00356f9c(); /* out of slice */
extern uint64_t FUN_003571f8(); /* out of slice */
extern uint64_t FUN_00357228(); /* out of slice */
extern uint64_t FUN_00357640(); /* out of slice */
extern uint64_t FUN_00357694(); /* out of slice */
extern uint64_t FUN_003578cc(); /* out of slice */
extern uint64_t FUN_00357b3c(); /* out of slice */
extern uint64_t FUN_003583dc(); /* out of slice */
extern uint64_t FUN_0035847c(); /* out of slice */
extern uint64_t FUN_003585c4(); /* out of slice */
extern uint64_t FUN_0035860c(); /* out of slice */
extern uint64_t FUN_00358840(); /* out of slice */
extern uint64_t FUN_00358b24(); /* out of slice */
extern uint64_t FUN_00358d70(); /* out of slice */
extern uint64_t FUN_00358f84(); /* out of slice */
extern uint64_t FUN_00358fb4(); /* out of slice */
extern uint64_t FUN_00358fc8(); /* out of slice */
extern uint64_t FUN_00359208(); /* out of slice */
extern uint64_t FUN_0035940c(); /* out of slice */
extern uint64_t FUN_00359424(); /* out of slice */
extern uint64_t FUN_0035946c(); /* out of slice */
extern uint64_t FUN_003599ac(); /* out of slice */
extern uint64_t FUN_00359abc(); /* out of slice */
extern uint64_t FUN_00359b0c(); /* out of slice */
extern uint64_t FUN_0035a028(); /* out of slice */
extern uint64_t FUN_0035a158(); /* out of slice */
extern uint64_t FUN_0035a184(); /* out of slice */
extern uint64_t FUN_0035a238(); /* out of slice */
extern uint64_t FUN_0035a354(); /* out of slice */
extern uint64_t FUN_0035a36c(); /* out of slice */
extern uint64_t FUN_0035a640(); /* out of slice */
extern uint64_t FUN_0035a8a8(); /* out of slice */
extern uint64_t FUN_0035aa40(); /* out of slice */
extern uint64_t FUN_0035aad8(); /* out of slice */
extern uint64_t FUN_0035ac1c(); /* out of slice */
extern uint64_t FUN_0036a908(); /* out of slice */
extern uint64_t FUN_0036b118(); /* out of slice */
extern uint64_t FUN_0036b270(); /* out of slice */
extern uint64_t FUN_0036ffc0(); /* out of slice */
extern uint64_t FUN_003722e4(); /* out of slice */
extern uint64_t FUN_0037233c(); /* out of slice */
extern uint64_t FUN_00376820(); /* out of slice */
extern uint64_t FUN_003a25d4(); /* out of slice */
extern uint64_t FUN_003a2610(); /* out of slice */


/* ------------------------------------------------------------------ *
 * Forward declarations for in-range helpers (bodies below, address order).
 * ------------------------------------------------------------------ */
int64_t sk_decode_ptr_4c(uint64_t p);
int64_t sk_decode_ptr_54(uint64_t p);
void sk_hook_21480_a8(void);
void sk_hook_21480_c0(void);
void sk_hook_21480_d8(void);
void sk_cond_call_36b118(int64_t cond, uint64_t arg);
void sk_hook_21480_600(void);
int64_t sk_decode_ptr_14_630(uint64_t p);
void sk_hook_21480_660(void);
int64_t sk_decode_ptr_24_678(uint64_t p);
int64_t sk_decode_ptr_28(uint64_t p);
int64_t sk_decode_ptr_38(uint64_t p);
int64_t sk_decode_ptr_30(uint64_t p);
int64_t sk_decode_ptr_3c(uint64_t p);
int64_t sk_decode_ptr_14_768(uint64_t p);
void sk_hook_21480_798(void);
void sk_syscall_swift_deinit_7b0(void);
void sk_syscall_context_call_804(void);
void sk_syscall_dispatch_848(void);
void sk_hook_21480_8b0(void);
void sk_hook_21480_8c8(void);
void sk_syscall_put_user_8e0(uint64_t arg);
void sk_report_error_910(uint64_t a, uint64_t b);
void sk_report_error_928(uint64_t a, uint64_t b);
void sk_syscall_6arg_940(uint64_t a);
void sk_syscall_6arg_944(uint64_t a);
void sk_syscall_byte_964(void);
void sk_syscall_byte_9e8(void);
int64_t sk_decode_ptr_20_6c(uint64_t p);
int64_t sk_decode_ptr_40(uint64_t p);
int64_t sk_decode_ptr_10_cc(uint64_t p);
int64_t sk_decode_ptr_24_fc(uint64_t p);
int64_t sk_decode_ptr_50(uint64_t p);
void sk_bounds_pair_call_db5c(void);
void sk_hook_21480_c0c(void);
void sk_tls_two_call_dc24(void);
void sk_tls_two_call_dc28(void);
void sk_hook_21480_c40(void);
void sk_hook_21480_c70(void);
void sk_ctx_callback_cc88(void);
uint32_t sk_syscall_bool_2dcbc(uint64_t a);
uint32_t sk_syscall_bool_2dce0(uint64_t a, uint64_t b);
uint32_t sk_syscall_bool_8arg_dd04(uint64_t a, uint64_t b, uint64_t c);
uint32_t sk_syscall_bool_dd3c(uint64_t a, uint64_t b);
uint32_t sk_syscall_bool_dd40(uint64_t a, uint64_t b);
void sk_ctx_callback_dd6c(void);
void sk_hook_21480_dd98(void);
void sk_hook_21480_ddb0(void);
void sk_tls_two_call_ddc8(void);
int64_t sk_capacity_index_ddfc(void);
void sk_hook_21480_de7c(void);
int64_t sk_decode_ptr_18(uint64_t p);
int64_t sk_decode_ptr_1c(uint64_t p);
int64_t sk_decode_ptr_2c(uint64_t p);
uint32_t sk_syscall_bool_7arg_df24(uint64_t a, uint64_t b);
uint32_t sk_syscall_bool_7arg_df28(uint64_t a, uint64_t b);
void sk_syscall_store_df4c(uint64_t a, uint64_t b);
void sk_syscall_store_df50(uint64_t a, uint64_t b);
int64_t sk_decode_ptr_20_df70(uint64_t p);
int64_t sk_decode_ptr_80(uint64_t p);
void sk_hook_21480_dfd0(void);
void sk_hook_21480_e000(void);
int64_t sk_decode_ptr_or_14_e030(uint64_t p);
void sk_syscall_5arg_e064(uint64_t a, uint64_t b);
void sk_hook_21480_e084(void);
void sk_store16_e09c(void);
int64_t sk_decode_ptr_c(uint64_t p);
int64_t sk_decode_ptr_10_e104(uint64_t p);
void sk_hook_21480_e134(void);
int64_t sk_decode_ptr_28_e15c(uint64_t p);
int64_t sk_decode_ptr_34(uint64_t p);
void sk_syscall_5arg_e1bc(uint64_t a, uint64_t b);
void sk_syscall_5arg_e1c0(uint64_t a, uint64_t b);
void sk_syscall_9arg_e1dc(uint64_t a, uint64_t b);
int64_t sk_decode_ptr_40_e210(uint64_t p);
void sk_single_call_e240(void);
void sk_write_global_e258(void);
void sk_ctx_callback_e2ac(void);
void sk_hook_21480_e2e0(void);
void sk_init_with_dt_e310(uint64_t a);
void sk_capture_retain_e388(uint64_t a, sk_fn_t fn, uint64_t b, uint64_t c);
void sk_swift_fatal_noerr_e410(void);
void sk_swift_fatal_noerr_e448(void);
void sk_swift_fatal_noerr_e478(void);
void sk_swift_fatal_noerr_e4b0(void);
void sk_swift_fatal_entry_e4d4(void);
void sk_swap_bytes_e4e0(uint64_t a, uint64_t b, int64_t base, int64_t len);
void sk_swap_buffer_e5c8(uint64_t a, uint64_t b, int64_t base, int64_t len);
void sk_buffer_copy_e6dc(void);
void sk_swift_fatal_noerr_e848(void);
void sk_buffer_batch_e874(void);
void sk_capture_state_ea14(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
void sk_thunk_e294(void);
void sk_cond_retain_eac4(uint64_t a);
void sk_cond_retain_eb18(void);
void sk_with_c_str_eb94(uint64_t a, uint64_t b, uint64_t *p, uint64_t c);
void *sk_make_buf_ec98(int64_t *out, uint64_t *p, int64_t meta);
cl4_result_t sk_make_buf_init_ed10(int64_t *slot, int64_t idx, int64_t base, int64_t len, int64_t meta);
void sk_swift_fatal_de(void);
void sk_swift_fatal_ec(void);
void sk_buf_index_ef54(uint64_t a, uint64_t b, int64_t meta);
void sk_swift_fatal_23e(void);
cl4_result_t sk_buf_slice_f0c0(uint64_t a, int64_t *p, int64_t meta);
void sk_buf_batch_f180(uint64_t *a, uint64_t *b, int64_t meta);
cl4_result_t sk_make_buf2_f1c4(int64_t *out, uint64_t *p, int64_t meta);
void sk_init_with_dt_f258(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e);
void sk_retain_capture_f2f0(void);
void sk_retain_capture_f2f4(void);
void sk_with_unwrapped_f30c(uint64_t a, sk_fn_t fn, uint64_t b, uint64_t c);
void sk_swift_fatal_fa(void);
void sk_swift_fatal_108(void);
void sk_swift_fatal_noerr_f48c(void);
void sk_fatal_chain_f4b0(void);
int64_t sk_update_with_pointer_f4e4(int64_t a, int64_t b, int64_t c, int64_t len);
void sk_swift_fatal_entry_f5d8(void);
void sk_cond_retain_f668(void);
void sk_cond_retain_f680(void);
void sk_apply_f6ec(cl4_result_t *out, int64_t meta, uint64_t a, sk_fn_t fn);
void sk_init_with_dt_f728(uint64_t a);
void sk_init_with_meta_f788(uint64_t a, uint64_t b, uint64_t c);
uint64_t sk_apply5_f7ec(cl4_result_t *out, uint64_t a, uint64_t b, int64_t meta, uint64_t c, sk_fn_t fn);
void sk_capture_retain_f834(uint64_t a, sk_fn_t fn, uint64_t b, uint64_t c);
void sk_swift_fatal_noerr_f8a4(void);
void sk_swift_fatal_noerr_f8dc(void);
void sk_swift_fatal_noerr_f90c(void);
void sk_swift_fatal_noerr_f944(void);
void sk_swift_fatal_noerr_f974(void);
void sk_bounds_check_f998(int64_t a, uint64_t n, int64_t end);
void sk_swift_fatal_entry_fa08(void);
void sk_bounds_check_fa14(int64_t a, uint64_t n, int64_t end);
void sk_swift_fatal_noerr_fa94(void);
void sk_range_check_faf8(int64_t a, int64_t b, int64_t c);
void sk_swift_fatal_entry_fb40(void);
void sk_range_check_fb6c(int64_t a, int64_t b, int64_t c, int64_t d);
void *sk_make_buf_fbb0(int64_t *out, uint64_t *p, int64_t meta);
void sk_buf_release_fc28(int64_t *p);
cl4_result_t sk_make_buf_init_fc64(int64_t *slot, int64_t idx, int64_t base, int64_t len, int64_t meta);
void sk_apply4_fdac(uint64_t *a, int64_t meta, uint64_t b, sk_fn_t fn);
void sk_count_range_fdf0(uint64_t *out);
void sk_swift_fatal_63e(void);
void sk_swift_fatal_64c(void);
void sk_swift_fatal_65a(void);
void sk_swift_fatal_668(void);
void sk_swift_fatal_noerr_20020(void);
void sk_fatal_chain_20044(void);
void sk_cond_call_20078(int64_t cond);
void sk_swift_fatal_entry_20084(void);
void sk_swift_checked_slice_200c8(void);
cl4_result_t sk_copy_overlapping_206bc(uint64_t a, int64_t n, uint64_t src, uint64_t end);
void sk_cond_retain_20744(void);
void sk_cond_retain_20748(void);
void sk_apply7_20770(void);
void *sk_make_buf3_2077c(uint64_t *out, uint64_t a, uint64_t b, uint64_t c);
void sk_cond_retain_207d4(void);
void sk_copy_replace_207e0(uint64_t a, uint64_t b, int64_t base, uint64_t c, int64_t lo, int64_t hi, int64_t slo, int64_t shi);
void sk_alloc_ctx_20950(void);
void sk_buf_finalize_209c4(uint64_t *p);
void sk_swap2_209fc(uint64_t a, uint64_t b, int64_t base, int64_t len);
void *sk_make_buf4_20aa8(uint64_t *out, uint64_t *p);
cl4_result_t sk_make_buf5_20b18(int64_t *out, uint64_t *p);
void sk_maybe_store_20b98(uint64_t *out);
void sk_bounds_call_20bd4(uint64_t a, uint64_t b, uint64_t c);
cl4_result_t sk_make_sub_20c28(uint8_t *out, uint64_t *p);
void sk_store64_20c8c(void);
void sk_tls_call_20ccc(void);
void sk_tls_call_20cd0(void);
void sk_copy_checked_20cfc(uint64_t a, int64_t n, uint64_t b, int64_t base, int64_t len, uint64_t c);
void sk_raw_copy_20dbc(int64_t a, int64_t b, uint64_t c, int64_t base, int64_t len, uint64_t d, uint64_t e, uint64_t f);
void sk_apply_then_verify_20f20(uint64_t a, uint64_t b, uint64_t c, sk_fn_t fn, uint64_t d, uint64_t e, int64_t *out);
void sk_verify_buf_20fc8(int64_t base, int64_t len, int64_t *p);
uint32_t sk_read_byte_advance_21084(void);
void sk_read_byte_210c8(uint16_t *out);
cl4_result_t sk_copy_partial_2113c(uint64_t a, int64_t n, uint64_t src, uint64_t end);
uint64_t sk_apply3_211d8(cl4_result_t *out, uint64_t a, uint64_t b, uint64_t c, uint64_t d, sk_fn_t fn);
void sk_apply_cond_21218(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, sk_fn_t fn);
cl4_result_t sk_count_range_212a4(int64_t base, int64_t end);
void sk_cond_retain_212b8(void);
uint8_t sk_buf_subscript_212c4(uint64_t idx, int64_t base, int64_t len);
void sk_cond_retain_21318(void);
void sk_bounds_ensure_21324(int64_t idx, int64_t n, int64_t base, int64_t len);
void sk_store64_2137c(void);
cl4_result_t sk_make_sub2_213a4(uint8_t *out, uint64_t *p);
void sk_call2_21408(void);
void sk_count_21440(void);
void sk_extend_21470(void);
void sk_extend_in_2149c(uint64_t *p);
void sk_append_214cc(void);
void sk_append_in_214f8(uint64_t *p);
void sk_fatal_chain_21528(void);
void sk_cond_retain_2156c(uint64_t a, uint64_t b, sk_fn_t fn);
void sk_swift_retain_copy_215b8(void);
void sk_cond_retain_2197c(void);
void sk_cond_retain_21980(void);
void sk_cond_retain_219ac(void);
void sk_cond_retain_219b0(void);
void sk_swift_trampoline_219dc(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e);
void sk_swift_iter_21a70(void);
void sk_swift_dispatch_21ac8(void);
uint32_t sk_swift_bool_21c68(void);
void sk_swift_dispatch2_21ca0(void);
void sk_swift_dispatch3_21e64(void);
void sk_swift_dispatch4_22010(void);
uint32_t sk_swift_bool_221bc(void);
void sk_swift_dispatch5_2220c(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h, uint64_t i, uint64_t j);
uint32_t sk_swift_bool_22450(void);


/* ------------------------------------------------------------------ *
 * Bodies (address order).  Ghidra identifiers kept only in comments;
 * `ctx` denotes Ghidra's callee-saved x20 (the syscall register-save
 * frame / preserved context, not representable as a C parameter).
 * ------------------------------------------------------------------ */

/* FUN_0031d518 @ 0x0031d518 (est. sk_decode_ptr_4c)
 * Tagged-pointer relative decode: if bit0 of `p` is set, dereference the
 * tagged pointer (clear bit0) to get the real object base. Returns the
 * object pointer advanced by the signed int32 stored at base+0x4c.
 * Confidence: medium. Notes: reads *(int32*)(base+0x4c). */
int64_t sk_decode_ptr_4c(uint64_t p)
{
    if (p & 1) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x4c) + (int64_t)*(int32_t *)(p + 0x4c);
}

/* FUN_0031d548 @ 0x0031d548 (est. sk_decode_ptr_54) — same relative-decode
 * pattern at offset 0x54. Confidence: medium. */
int64_t sk_decode_ptr_54(uint64_t p)
{
    if (p & 1) {
        p = *(uint64_t *)(p & ~1ull);
    }
    return (int64_t)(p + 0x54) + (int64_t)*(int32_t *)(p + 0x54);
}

/* FUN_0031d5a8 @ 0x0031d5a8 (est. sk_hook_21480_a8)
 * Thin forwarder to the out-of-range hook FUN_00021480 (no-op / hint).
 * Confidence: medium. */
void sk_hook_21480_a8(void) { FUN_00021480(); }

/* FUN_0031d5c0 @ 0x0031d5c0 (est. sk_hook_21480_c0) — forwarder to 0x21480. */
void sk_hook_21480_c0(void) { FUN_00021480(); }

/* FUN_0031d5d8 @ 0x0031d5d8 (est. sk_hook_21480_d8) — forwarder to 0x21480.
 * Called from 11+ sites (0x25f910..0x28beec). Confidence: medium. */
void sk_hook_21480_d8(void) { FUN_00021480(); }

/* FUN_0031d5f0 @ 0x0031d5f0 (est. sk_cond_call_36b118)
 * If `cond` is nonzero, forward `arg` to the out-of-range helper 0x36b118.
 * Confidence: medium. */
void sk_cond_call_36b118(int64_t cond, uint64_t arg)
{
    if (cond != 0) {
        FUN_0036b118(arg);
    }
}

/* FUN_0031d600 @ 0x0031d600 (est. sk_hook_21480_600) — forwarder to 0x21480. */
void sk_hook_21480_600(void) { FUN_00021480(); }

/* FUN_0031d630 @ 0x0031d630 (est. sk_decode_ptr_14_630) — decode at +0x14. */
int64_t sk_decode_ptr_14_630(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_0031d660 @ 0x0031d660 (est. sk_hook_21480_660) — forwarder to 0x21480. */
void sk_hook_21480_660(void) { FUN_00021480(); }

/* FUN_0031d678 @ 0x0031d678 (est. sk_decode_ptr_24_678) — decode at +0x24. */
int64_t sk_decode_ptr_24_678(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x24) + (int64_t)*(int32_t *)(p + 0x24);
}

/* FUN_0031d6a8 @ 0x0031d6a8 (est. sk_decode_ptr_28) — decode at +0x28. */
int64_t sk_decode_ptr_28(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x28) + (int64_t)*(int32_t *)(p + 0x28);
}

/* FUN_0031d6d8 @ 0x0031d6d8 (est. sk_decode_ptr_38) — decode at +0x38. */
int64_t sk_decode_ptr_38(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x38) + (int64_t)*(int32_t *)(p + 0x38);
}

/* FUN_0031d708 @ 0x0031d708 (est. sk_decode_ptr_30) — decode at +0x30. */
int64_t sk_decode_ptr_30(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x30) + (int64_t)*(int32_t *)(p + 0x30);
}

/* FUN_0031d738 @ 0x0031d738 (est. sk_decode_ptr_3c) — decode at +0x3c. */
int64_t sk_decode_ptr_3c(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x3c) + (int64_t)*(int32_t *)(p + 0x3c);
}

/* FUN_0031d768 @ 0x0031d768 (est. sk_decode_ptr_14_768) — decode at +0x14. */
int64_t sk_decode_ptr_14_768(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_0031d798 @ 0x0031d798 (est. sk_hook_21480_798) — forwarder to 0x21480. */
void sk_hook_21480_798(void) { FUN_00021480(); }

/* FUN_0031d7b0 @ 0x0031d7b0 (est. sk_syscall_swift_deinit_7b0)
 * Syscall-entry deinit: drains the preserved context (x20) through a series
 * of out-of-range helpers and a tail-called indirect hook.
 * Confidence: low. Notes: `ctx`=unaff_x20; reads *(ctx+0x18); indirect
 * (*extraout_x8)() tail call. */
void sk_syscall_swift_deinit_7b0(void)
{
    uint64_t *ctx = NULL; /* = unaff_x20 (preserved syscall context) */
    sk_fn_t tail = NULL;  /* = extraout_x8 (indirect tail hook) */
    FUN_0034cf14();
    FUN_0016186c(*(uint64_t *)(ctx + 0x18));
    FUN_0034c8b8();
    FUN_003512cc();
    if (tail) tail();
    FUN_0035396c();
}

/* FUN_0031d804 @ 0x0031d804 (est. sk_syscall_context_call_804)
 * Syscall-entry trampoline: calls the dispatcher with two args read from the
 * preserved context, then the return/cleanup helpers.
 * Confidence: low. Notes: ctx=unaff_x20; reads *(ctx+0x10),*(ctx+0x18). */
void sk_syscall_context_call_804(void)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_0035662c();
    FUN_00310e08(0, *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18));
    FUN_001e3048();
    FUN_00356d20();
}

/* FUN_0031d848 @ 0x0031d848 (est. sk_syscall_dispatch_848)
 * Syscall-entry dispatch: resolves an index from the dispatcher result and
 * forwards a capability/argument to a per-type handler. 
 * Confidence: low. Notes: ctx=unaff_x20, frame=unaff_x22; reads
 * *(ctx+0x18); index from *(res+0x24). */
void sk_syscall_dispatch_848(void)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    int64_t *frame = NULL; /* = unaff_x22 */
    sk_fn_t tail = NULL;  /* = extraout_x8 */
    uint64_t arg = *(uint64_t *)(ctx + 0x18);
    int64_t res;
    int idx;
    FUN_0035662c();
    FUN_0034d3e4();
    res = FUN_00310e08();
    idx = *(int32_t *)(res + 0x24);
    arg = FUN_00310b08(arg);
    FUN_00356ad0(arg, (uint64_t)frame + idx);
    FUN_00350bfc();
    if (tail) tail();
    FUN_0035396c();
}

/* FUN_0031d8b0 @ 0x0031d8b0 (est. sk_hook_21480_8b0) — forwarder to 0x21480. */
void sk_hook_21480_8b0(void) { FUN_00021480(); }

/* FUN_0031d8c8 @ 0x0031d8c8 (est. sk_hook_21480_8c8) — forwarder to 0x21480. */
void sk_hook_21480_8c8(void) { FUN_00021480(); }

/* FUN_0031d8e0 @ 0x0031d8e0 (est. sk_syscall_put_user_8e0)
 * Syscall exit helper: forwards an argument and three saved context fields
 * (cap ptr + two message words) to the out-of-range user-return path.
 * Confidence: low. Notes: ctx=unaff_x20; reads *(ctx+0x20/0x10/0x18). */
void sk_syscall_put_user_8e0(uint64_t arg)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_0027b204(arg, *(uint64_t *)(ctx + 0x20),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18));
    FUN_0035396c();
}

/* FUN_0031d910 @ 0x0031d910 (est. sk_report_error_910)
 * Report an error pair through the common reporter, tagged by string
 * DAT_00613644. Confidence: medium. */
void sk_report_error_910(uint64_t a, uint64_t b)
{
    FUN_0036ffc0(a, b, (uint64_t)&DAT_00613644);
}

/* FUN_0031d928 @ 0x0031d928 (est. sk_report_error_928)
 * Report an error pair, tagged by string DAT_0061368c. Confidence: medium. */
void sk_report_error_928(uint64_t a, uint64_t b)
{
    FUN_0036ffc0(a, b, (uint64_t)&DAT_0061368c);
}

/* FUN_0031d940 @ 0x0031d940 (est. sk_syscall_6arg_940)
 * 6-argument syscall trampoline: forwards `a` plus five context fields to
 * the shared dispatcher 0x2922b0. Confidence: low. ctx=unaff_x20. */
void sk_syscall_6arg_940(uint64_t a)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_002922b0(a, *(uint64_t *)(ctx + 0x28), *(uint64_t *)(ctx + 0x30),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20));
}

/* FUN_0031d944 @ 0x0031d944 (est. sk_syscall_6arg_944) — duplicate of 940. */
void sk_syscall_6arg_944(uint64_t a)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_002922b0(a, *(uint64_t *)(ctx + 0x28), *(uint64_t *)(ctx + 0x30),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20));
}

/* FUN_0031d964 @ 0x0031d964 (est. sk_syscall_byte_964)
 * Byte-oriented syscall trampoline: picks the per-type capability decoder
 * based on a tag byte in the context, then invokes the byte handler.
 * Confidence: low. Notes: ctx=unaff_x20; tag=*(char*)(ctx+0x20);
 * out=unaff_x22 (16-byte dest). */
void sk_syscall_byte_964(void)
{
    uint64_t *ctx = NULL;    /* = unaff_x20 */
    uint8_t *out = NULL;     /* = auVar6 (16-byte destination) */
    cl4_result_t tagstate = {0,0}; /* = FUN_00358fb4() result */
    uint64_t arg = *(uint64_t *)(ctx + 0x18);
    char tag = *(char *)(ctx + 0x20);
    uint64_t extra = *(uint64_t *)(ctx + 0x28);
    cl4_result_t src = {0,0}; /* = FUN_00350720() result */
    int64_t res;
    int idx;
    sk_fn_t tail = NULL; /* = extraout_x8 */
    FUN_00358fb4();
    src.lo = FUN_00350720();
    res = FUN_00310e08(src.lo, src.hi, arg);
    idx = *(int32_t *)(res + 0x24);
    if (tag == 0x01) {
        arg = FUN_00310954();
    } else {
        arg = FUN_00310b08(arg);
    }
    FUN_00350cb4(arg, (uint64_t)out + idx, extra);
    if (tail) tail();
    FUN_00358fc8(FUN_0035396c(), tagstate.hi);
}


/* FUN_0031d9e8 @ 0x0031d9e8 (est. sk_syscall_byte_9e8)
 * Byte-oriented syscall trampoline (word variant): picks a capability
 * decoder from a tag byte and invokes the word handler on the context.
 * Confidence: low. Notes: ctx=unaff_x20; tag=*(char*)(ctx+0x20);
 * base=*(long*)(ctx+0x28). */
void sk_syscall_byte_9e8(void)
{
    uint64_t *ctx = NULL;  /* = unaff_x20 */
    uint8_t *out = NULL;   /* = auVar6 (16-byte dest) */
    int64_t base = *(int64_t *)(ctx + 0x28);
    uint64_t arg = *(uint64_t *)(ctx + 0x18);
    char tag = *(char *)(ctx + 0x20);
    cl4_result_t src = {0,0}; /* = FUN_0035050c() result */
    int64_t res;
    int idx;
    sk_fn_t tail = NULL; /* = extraout_x8 */
    FUN_00358fb4();
    src.lo = FUN_0035050c();
    res = FUN_00310e08(src.lo, src.hi, arg);
    idx = *(int32_t *)(res + 0x24);
    if (tag == 0x01) {
        arg = FUN_00310b08();
    } else {
        arg = FUN_00310954(arg);
    }
    FUN_0034e5fc(arg, out, base + idx);
    if (tail) tail();
    FUN_00358fc8(FUN_0035396c(), src.hi);
}

/* FUN_0031da6c @ 0x0031da6c (est. sk_decode_ptr_20_6c) — decode at +0x20. */
int64_t sk_decode_ptr_20_6c(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x20) + (int64_t)*(int32_t *)(p + 0x20);
}

/* FUN_0031da9c @ 0x0031da9c (est. sk_decode_ptr_40) — decode at +0x40. */
int64_t sk_decode_ptr_40(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x40) + (int64_t)*(int32_t *)(p + 0x40);
}

/* FUN_0031dacc @ 0x0031dacc (est. sk_decode_ptr_10_cc) — decode at +0x10. */
int64_t sk_decode_ptr_10_cc(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_0031dafc @ 0x0031dafc (est. sk_decode_ptr_24_fc) — decode at +0x24. */
int64_t sk_decode_ptr_24_fc(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x24) + (int64_t)*(int32_t *)(p + 0x24);
}

/* FUN_0031db2c @ 0x0031db2c (est. sk_decode_ptr_50) — decode at +0x50. */
int64_t sk_decode_ptr_50(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x50) + (int64_t)*(int32_t *)(p + 0x50);
}

/* FUN_0031db5c @ 0x0031db5c (est. sk_bounds_pair_call_db5c)
 * Bounds-checked two-range operation: underflows to a debug trap, checks the
 * two ranges fit in 32-bit, performs the operation, else a fatal error.
 * Confidence: low. Notes: reads *(ctx+0x20)=uVar3, *(ctx+0x10)=count-8;
 * uses SoftwareBreakpoint(1,0x31dc0c); fatal tail 0x1afe4c. */
void sk_bounds_pair_call_db5c(void)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    uint64_t extra = *(uint64_t *)(ctx + 0x20);
    int64_t count = *(int64_t *)(ctx + 0x10);
    uint64_t d = (uint64_t)FUN_00041138();
    int64_t uVar1 = count - 8;
    if (SBORROW8(count, 8)) {
        /* WARNING: does not return */
        SK_TRAP(); /* SoftwareBreakpoint(1,0x31dc0c) */
    }
    if (uVar1 < 0) {
        FUN_003482c4();
    } else {
        if ((uVar1 >> 0x20) == 0) {
            FUN_00355190();
            FUN_00351790();
            FUN_0024c0d0((uint32_t)uVar1 | 0xa0000000, 0);
            FUN_00355190();
            if ((int64_t)extra < 0) { FUN_003482c4(); }
            else if ((extra >> 0x20) == 0) {
                FUN_0035aa40((uint64_t)&d);
                FUN_0035847c(0);
                return;
            }
        }
        FUN_003583dc();
        FUN_00348194();
    }
    FUN_003523f0();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0031dc0c @ 0x0031dc0c (est. sk_hook_21480_c0c) — forwarder to 0x21480. */
void sk_hook_21480_c0c(void) { FUN_00021480(); }

/* FUN_0031dc24 @ 0x0031dc24 (est. sk_tls_two_call_dc24)
 * Two TLS helper calls (0x357640 then 0x27ffd8). Confidence: low. */
void sk_tls_two_call_dc24(void) { FUN_00357640(); FUN_0027ffd8(); }

/* FUN_0031dc28 @ 0x0031dc28 (est. sk_tls_two_call_dc28) — duplicate of dc24. */
void sk_tls_two_call_dc28(void) { FUN_00357640(); FUN_0027ffd8(); }

/* FUN_0031dc40 @ 0x0031dc40 (est. sk_hook_21480_c40) — forwarder to 0x21480. */
void sk_hook_21480_c40(void) { FUN_00021480(); }

/* FUN_0031dc70 @ 0x0031dc70 (est. sk_hook_21480_c70) — forwarder to 0x21480. */
void sk_hook_21480_c70(void) { FUN_00021480(); }

/* FUN_0031dc88 @ 0x0031dc88 (est. sk_ctx_callback_cc88)
 * Invokes a function pointer stored at ctx+0x28; if a preserved frame
 * pointer is nonzero, runs the unwind/cleanup helper.
 * Confidence: low. Notes: ctx=unaff_x20, saved=unaff_x21. */
void sk_ctx_callback_cc88(void)
{
    uint64_t *ctx = NULL;  /* = unaff_x20 */
    uint64_t saved = 0;    /* = unaff_x21 */
    (*(sk_fn_t)(*(uint64_t *)(ctx + 0x28)))();
    if (saved != 0) {
        FUN_00354720();
    }
}

/* FUN_0031dcbc @ 0x0031dcbc (est. sk_syscall_bool_2dcbc)
 * Boolean syscall predicate: calls the checker with four context fields and
 * returns result & 1. Confidence: low. ctx=unaff_x20. */
uint32_t sk_syscall_bool_2dcbc(uint64_t a)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    uint32_t r = (uint32_t)FUN_00286e80(a, *(uint64_t *)(ctx + 0x28),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20));
    return r & 1;
}

/* FUN_0031dce0 @ 0x0031dce0 (est. sk_syscall_bool_2dce0) — bool predicate. */
uint32_t sk_syscall_bool_2dce0(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    uint32_t r = (uint32_t)FUN_0029200c(a, b, *(uint64_t *)(ctx + 0x28),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20));
    return r & 1;
}

/* FUN_0031dd04 @ 0x0031dd04 (est. sk_syscall_bool_8arg_dd04)
 * 8-argument boolean syscall trampoline. Confidence: low. ctx=unaff_x20. */
uint32_t sk_syscall_bool_8arg_dd04(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    uint32_t r = (uint32_t)FUN_00286b94(a, b, *(uint64_t *)(ctx + 0x38),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28),
                 *(uint64_t *)(ctx + 0x30), c);
    return r & 1;
}

/* FUN_0031dd3c @ 0x0031dd3c (est. sk_syscall_bool_dd3c) — bool trampoline
 * using FUN_0016186c as the completion callback. Confidence: low. */
uint32_t sk_syscall_bool_dd3c(uint64_t a, uint64_t b)
{
    uint32_t r = sk_syscall_bool_8arg_dd04(a, b, (uint64_t)FUN_0016186c);
    return r & 1;
}

/* FUN_0031dd40 @ 0x0031dd40 (est. sk_syscall_bool_dd40) — duplicate of dd3c. */
uint32_t sk_syscall_bool_dd40(uint64_t a, uint64_t b)
{
    uint32_t r = sk_syscall_bool_8arg_dd04(a, b, (uint64_t)FUN_0016186c);
    return r & 1;
}

/* FUN_0031dd6c @ 0x0031dd6c (est. sk_ctx_callback_dd6c)
 * Invokes the callback at ctx+0x20 then the return helper.
 * Confidence: low. Notes: ctx=unaff_x20. */
void sk_ctx_callback_dd6c(void)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    (*(sk_fn_t)(*(uint64_t *)(ctx + 0x20)))();
    FUN_00356d20();
}

/* FUN_0031dd98 @ 0x0031dd98 (est. sk_hook_21480_dd98) — forwarder to 0x21480. */
void sk_hook_21480_dd98(void) { FUN_00021480(); }

/* FUN_0031ddb0 @ 0x0031ddb0 (est. sk_hook_21480_ddb0) — forwarder to 0x21480. */
void sk_hook_21480_ddb0(void) { FUN_00021480(); }

/* FUN_0031ddc8 @ 0x0031ddc8 (est. sk_tls_two_call_ddc8)
 * Two helper calls (0x357640 then 0x28b6cc). Confidence: low. */
void sk_tls_two_call_ddc8(void) { FUN_00357640(); FUN_0028b6cc(); }

/* FUN_0031ddfc @ 0x0031ddfc (est. sk_capacity_index_ddfc)
 * Computes a scaled element pointer: bounds the running index against a
 * capacity, then indexes into a per-element stride structure.
 * Confidence: low. Notes: reads in_x3/in_x4/in_x5 (incoming regs),
 * unaff_x19 (index), unaff_x22 (base); stride *(*(in_x4-8)+0x48). */
int64_t sk_capacity_index_ddfc(void)
{
    int64_t in_x3 = 0, in_x4 = 0;
    sk_fn_t in_x5 = NULL;
    int64_t unaff_x19 = 0, unaff_x22 = 0;
    cl4_result_t v = {0,0}; /* = FUN_00352c34() */
    int64_t lVar1;
    v.hi = FUN_00352c34();
    lVar1 = v.hi;
    if (in_x3 == 0 || lVar1 == 0) {
        FUN_0034d180();
        lVar1 = in_x5 ? in_x5() : 0;
    } else {
        if (lVar1 <= unaff_x19) { unaff_x19 = lVar1; }
        FUN_00100efc(v.lo, lVar1, v.lo);
        FUN_0019dadc();
        lVar1 = unaff_x22 + *(int64_t *)(*(int64_t *)(in_x4 - 8) + 0x48) * unaff_x19;
    }
    return lVar1;
}

/* FUN_0031de7c @ 0x0031de7c (est. sk_hook_21480_de7c) — forwarder to 0x21480. */
void sk_hook_21480_de7c(void) { FUN_00021480(); }

/* FUN_0031de94 @ 0x0031de94 (est. sk_decode_ptr_18) — decode at +0x18. */
int64_t sk_decode_ptr_18(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x18) + (int64_t)*(int32_t *)(p + 0x18);
}

/* FUN_0031dec4 @ 0x0031dec4 (est. sk_decode_ptr_1c) — decode at +0x1c. */
int64_t sk_decode_ptr_1c(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x1c) + (int64_t)*(int32_t *)(p + 0x1c);
}

/* FUN_0031def4 @ 0x0031def4 (est. sk_decode_ptr_2c) — decode at +0x2c. */
int64_t sk_decode_ptr_2c(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x2c) + (int64_t)*(int32_t *)(p + 0x2c);
}

/* FUN_0031df24 @ 0x0031df24 (est. sk_syscall_bool_7arg_df24)
 * 7-argument boolean syscall trampoline. Confidence: low. ctx=unaff_x20. */
uint32_t sk_syscall_bool_7arg_df24(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    uint32_t r = (uint32_t)FUN_00292204(a, b, *(uint64_t *)(ctx + 0x30),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28));
    return r & 1;
}

/* FUN_0031df28 @ 0x0031df28 (est. sk_syscall_bool_7arg_df28) — duplicate. */
uint32_t sk_syscall_bool_7arg_df28(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    uint32_t r = (uint32_t)FUN_00292204(a, b, *(uint64_t *)(ctx + 0x30),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28));
    return r & 1;
}

/* FUN_0031df4c @ 0x0031df4c (est. sk_syscall_store_df4c)
 * Store trampoline: forwards two args plus a context field to the store
 * helper, then the completion. Confidence: low. ctx=unaff_x20. */
void sk_syscall_store_df4c(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_00359abc(a, b, *(uint64_t *)(ctx + 0x18));
    FUN_00293fc8();
}

/* FUN_0031df50 @ 0x0031df50 (est. sk_syscall_store_df50) — duplicate. */
void sk_syscall_store_df50(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_00359abc(a, b, *(uint64_t *)(ctx + 0x18));
    FUN_00293fc8();
}

/* FUN_0031df70 @ 0x0031df70 (est. sk_decode_ptr_20_df70) — decode at +0x20. */
int64_t sk_decode_ptr_20_df70(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x20) + (int64_t)*(int32_t *)(p + 0x20);
}

/* FUN_0031dfa0 @ 0x0031dfa0 (est. sk_decode_ptr_80) — decode at +0x80. */
int64_t sk_decode_ptr_80(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x80) + (int64_t)*(int32_t *)(p + 0x80);
}

/* FUN_0031dfd0 @ 0x0031dfd0 (est. sk_hook_21480_dfd0) — forwarder. */
void sk_hook_21480_dfd0(void) { FUN_00021480(); }

/* FUN_0031e000 @ 0x0031e000 (est. sk_hook_21480_e000) — forwarder. */
void sk_hook_21480_e000(void) { FUN_00021480(); }

/* FUN_0031e030 @ 0x0031e030 (est. sk_decode_ptr_or_14_e030)
 * Tagged decode with an alternate branch: untagged returns the relative
 * pointer at +0x14; tagged dereferences and returns *(base+0x28).
 * Confidence: medium. */
int64_t sk_decode_ptr_or_14_e030(uint64_t p)
{
    if ((p & 1) == 0) {
        return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
    }
    return *(int64_t *)((p & ~1ull) + 0x28);
}

/* FUN_0031e064 @ 0x0031e064 (est. sk_syscall_5arg_e064)
 * 5-argument syscall trampoline. Confidence: low. ctx=unaff_x20. */
void sk_syscall_5arg_e064(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_002993a4(a, b, *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28));
}

/* FUN_0031e084 @ 0x0031e084 (est. sk_hook_21480_e084) — forwarder. */
void sk_hook_21480_e084(void) { FUN_00021480(); }

/* FUN_0031e09c @ 0x0031e09c (est. sk_store16_e09c)
 * Runs the range helper and stores its 16-byte result at the destination.
 * Confidence: low. Notes: dest=unaff_x22. */
void sk_store16_e09c(void)
{
    uint8_t (*dest)[16] = NULL; /* = unaff_x22 */
    cl4_result_t v = {0,0};     /* = FUN_00299c38() */
    FUN_0035860c();
    v.lo = FUN_00299c38();
    *((cl4_result_t *)dest) = v;
}

/* FUN_0031e0d4 @ 0x0031e0d4 (est. sk_decode_ptr_c) — decode at +0xc. */
int64_t sk_decode_ptr_c(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_0031e104 @ 0x0031e104 (est. sk_decode_ptr_10_e104) — decode at +0x10.
 * Called from 20+ sites. Confidence: medium. */
int64_t sk_decode_ptr_10_e104(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_0031e134 @ 0x0031e134 (est. sk_hook_21480_e134) — forwarder. */
void sk_hook_21480_e134(void) { FUN_00021480(); }

/* FUN_0031e15c @ 0x0031e15c (est. sk_decode_ptr_28_e15c) — decode at +0x28. */
int64_t sk_decode_ptr_28_e15c(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x28) + (int64_t)*(int32_t *)(p + 0x28);
}

/* FUN_0031e18c @ 0x0031e18c (est. sk_decode_ptr_34) — decode at +0x34. */
int64_t sk_decode_ptr_34(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x34) + (int64_t)*(int32_t *)(p + 0x34);
}

/* FUN_0031e1bc @ 0x0031e1bc (est. sk_syscall_5arg_e1bc) — 5-arg trampoline. */
void sk_syscall_5arg_e1bc(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_0029aa14(a, b, *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28));
}

/* FUN_0031e1c0 @ 0x0031e1c0 (est. sk_syscall_5arg_e1c0) — duplicate. */
void sk_syscall_5arg_e1c0(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_0029aa14(a, b, *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28));
}


/* FUN_0031e1dc @ 0x0031e1dc (est. sk_syscall_9arg_e1dc)
 * 9-argument syscall trampoline. Confidence: low. ctx=unaff_x20. */
void sk_syscall_9arg_e1dc(uint64_t a, uint64_t b)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    FUN_0029b264(a, b, *(uint64_t *)(ctx + 0x28), *(uint64_t *)(ctx + 0x30),
                 *(uint64_t *)(ctx + 0x40), *(uint64_t *)(ctx + 0x48),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20));
}

/* FUN_0031e210 @ 0x0031e210 (est. sk_decode_ptr_40_e210) — decode at +0x40. */
int64_t sk_decode_ptr_40_e210(uint64_t p)
{
    if (p & 1) { p = *(uint64_t *)(p & ~1ull); }
    return (int64_t)(p + 0x40) + (int64_t)*(int32_t *)(p + 0x40);
}

/* FUN_0031e240 @ 0x0031e240 (est. sk_single_call_e240)
 * Single helper call (0x344cf4). Confidence: low. */
void sk_single_call_e240(void) { FUN_00344cf4(); }

/* FUN_0031e258 @ 0x0031e258 (est. sk_write_global_e258)
 * Writes a fixed 64-bit constant to the global at 0x656270 (a per-cpu or
 * state seed). Confidence: low. Notes: uRam0000000000656270.
 * Ghidra: "Removing unreachable block (ram,0x0031e26c)". */
void sk_write_global_e258(void)
{
    DAT_00656270 = 0xdac10230d28557d1ull;
}

/* FUN_0031e2ac @ 0x0031e2ac (est. sk_ctx_callback_e2ac)
 * Invokes callback at ctx+0x18; if a preserved frame pointer is nonzero
 * runs the unwind helper. Confidence: low. ctx=unaff_x20, saved=unaff_x21. */
void sk_ctx_callback_e2ac(void)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    uint64_t saved = 0;   /* = unaff_x21 */
    (*(sk_fn_t)(*(uint64_t *)(ctx + 0x18)))();
    if (saved != 0) {
        FUN_00354720();
    }
}

/* FUN_0031e2e0 @ 0x0031e2e0 (est. sk_hook_21480_e2e0) — forwarder. */
void sk_hook_21480_e2e0(void) { FUN_00021480(); }

/* FUN_0031e310 @ 0x0031e310 (est. sk_init_with_dt_e310)
 * Initializes from a descriptor table: looks up `a` in DAT_004edcd0 and
 * passes the result onward. Confidence: low. */
void sk_init_with_dt_e310(uint64_t a)
{
    uint64_t v = FUN_00376820((uint64_t)&DAT_004edcd0, a);
    FUN_001a0194(a, v);
}

/* FUN_0031e388 @ 0x0031e388 (est. sk_capture_retain_e388)
 * Captures two values from the context, runs a callback with `a`, and if the
 * preserved frame is null delivers a completion. 
 * Confidence: low. Notes: unaff_x20 (pair source), unaff_x21 (flag). */
void sk_capture_retain_e388(uint64_t a, sk_fn_t fn, uint64_t b, uint64_t c)
{
    uint64_t *src = NULL; /* = unaff_x20 */
    uint64_t flag = 0;    /* = unaff_x21 */
    FUN_0001a1c8(*src, src[1]);
    if (fn) fn(a);
    if (flag == 0) {
        FUN_000839d8(a, 0, 1, c);
    }
}

/* FUN_0031e410 @ 0x0031e410 (est. sk_swift_fatal_noerr_e410)
 * Swift-runtime fatal-error stub: no-argument precondition failure.
 * Confidence: low. Notes: runs 0x35047c + 0x3480ac then noreturn 0x1afe4c. */
void sk_swift_fatal_noerr_e410(void)
{
    FUN_0035047c();
    FUN_003480ac();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0031e448 @ 0x0031e448 (est. sk_swift_fatal_noerr_e448) — duplicate. */
void sk_swift_fatal_noerr_e448(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031e478 @ 0x0031e478 (est. sk_swift_fatal_noerr_e478) — duplicate. */
void sk_swift_fatal_noerr_e478(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031e4b0 @ 0x0031e4b0 (est. sk_swift_fatal_noerr_e4b0) — duplicate. */
void sk_swift_fatal_noerr_e4b0(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031e4d4 @ 0x0031e4d4 (est. sk_swift_fatal_entry_e4d4)
 * Fatal-error entry: forwards to the bounds-check fatal helper 0x31fa14.
 * Confidence: low. */
void sk_swift_fatal_entry_e4d4(void) { sk_bounds_check_fa14(0, 0, 0); }

/* FUN_0031e4e0 @ 0x0031e4e0 (est. sk_swap_bytes_e4e0)
 * Swaps two bytes in a buffer with full bounds validation; on any violation
 * raises a Swift _fatalError (0x1afe4c). Errors: 0x18f (nil base),
 * 0x190 (index out of range), 0x191 (unexpected nil). 
 * Confidence: low. Notes: fatal string s_Unexpectedly_found_nil_while_unw_005cd7d0. */
void sk_swap_bytes_e4e0(uint64_t a, uint64_t b, int64_t base, int64_t len)
{
    uint64_t err;
    const char *where;
    if (a == b) return;
    if ((int64_t)(b | a) < 0) {
        err = 0x18f;
        where = (const char *)&DAT_005be7c0;
    } else {
        if ((int64_t)a < len && (int64_t)b < len) {
            if (base != 0) {
                uint8_t t = *(uint8_t *)(base + a);
                *(uint8_t *)(base + a) = *(uint8_t *)(base + b);
                *(uint8_t *)(base + b) = t;
                return;
            }
            err = 0x191;
            where = s_Unexpectedly_found_nil_while_unw_005cd7d0;
            FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)where, 0x39, 2,
                         (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, err, 1);
        }
        err = 0x190;
        where = (const char *)&DAT_005be7c0;
    }
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)where, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, err, 1);
}

/* FUN_0031e5c8 @ 0x0031e5c8 (est. sk_swap_buffer_e5c8)
 * Swaps two elements (of the buffer's element stride) in place, validating
 * the element pointers; raises a Swift fatal error on violation.
 * Confidence: low. Notes: stride=*(ctx+0x48) element size; fatal codes 0x18f/0x190. */
void sk_swap_buffer_e5c8(uint64_t a, uint64_t b, int64_t base, int64_t len)
{
    int64_t ctx = 0; /* extraout_x16 base context */
    cl4_result_t v = {0,0}; /* = FUN_0034a1f8() */
    FUN_0007c028();
    DAT_00658c00(*(uint64_t *)(ctx + 0x40));
    v.lo = FUN_0034a1f8();
    if (v.lo == v.hi) return;
    if (v.lo < 0 || v.hi < 0) {
        FUN_0034b348();
        FUN_00348160(0x18f);
    } else if (v.lo < len && v.hi < len) {
        if (base != 0) {
            sk_fn_t cb = (sk_fn_t)(ctx + 0x20);
            int64_t stride = *(int64_t *)(ctx + 0x48);
            FUN_0034ce78();
            if (cb) cb();
            FUN_003515fc(base + stride * v.hi, 1);
            FUN_0019ce60();
            FUN_0034edc8();
            if (cb) cb();
            return;
        }
        FUN_00350410();
        FUN_00348898();
        FUN_00349a04();
        FUN_003524c8();
        /* WARNING: does not return */
        FUN_001afe4c();
    } else {
        FUN_0034b348();
        FUN_00348160(0x190);
    }
    FUN_003524c8();
    FUN_001afe4c();
}

/* FUN_0031e6dc @ 0x0031e6dc (est. sk_buffer_copy_e6dc)
 * Element-copy helper: validates an element index against the count, copies
 * the element via the stride, else fatal. Confidence: low.
 * Notes: ctx=unaff_x20 (element base), unaff_x21 (index); stride
 * *(ctx+0x48); fatal on OOB. */
void sk_buffer_copy_e6dc(void)
{
    uint64_t *ctx = NULL; /* = unaff_x20 */
    int64_t idx = 0;      /* = unaff_x21 */
    int64_t count = 0;    /* = in_x3 */
    uint64_t in_x4 = 0;
    uint64_t lim = 0;     /* = unaff_x30 */
    sk_fn_t cb = NULL, cb2 = NULL;
    int64_t cbctx = 0;    /* = extraout_x16 */
    FUN_00084220();
    FUN_00350b0c();
    FUN_0007c028();
    DAT_00658c00(*(uint64_t *)(cbctx + 0x40));
    FUN_00348f50();
    FUN_0034d384();
    if (cb) cb();
    if (idx < 0) {
        FUN_0034b348();
    } else if (idx < count) {
        FUN_00352870();
        FUN_00350524();
        if (cb2) cb2();
        FUN_003508c0(*(uint64_t *)(cbctx + 0x28),
                     (uint64_t)ctx + *(int64_t *)(cbctx + 0x48) * idx);
        if (cb) cb();
        FUN_00084234(lim);
        return;
    } else {
        FUN_0034b348();
    }
    FUN_003480ac();
    /* WARNING: does not return */
    FUN_001afe4c();
}


/* FUN_0031e848 @ 0x0031e848 (est. sk_swift_fatal_noerr_e848)
 * Swift-runtime fatal-error stub. Confidence: low. */
void sk_swift_fatal_noerr_e848(void)
{
    /* Ghidra: FUN_0031e848 -> FUN_0031fb6c() forwarder */
    sk_range_check_fb6c(0, 0, 0, 0);
}

/* FUN_0031e874 @ 0x0031e874 (est. sk_buffer_batch_e874)
 * Batch element copy with overlap validation. Validates range bounds
 * (0x299/0x29a/0x29b errors) and copies elements honoring a destination
 * stride; an element predicate gate decides the fast/slow path.
 * Confidence: low. Notes: in_x4..in_x7 ranges; stride *(ctx+0x48);
 * fatal tail 0x1afe4c. */
void sk_buffer_batch_e874(void)
{
    int64_t in_x4 = 0, in_x5 = 0, in_x6 = 0, in_x7 = 0;
    uint64_t extra = 0; /* extraout_x8 */
    int64_t ctx = 0;    /* extraout_x16 */
    uint64_t stk50 = 0, stk28 = 0, stke0 = 0;
    uint64_t err;
    FUN_00356f9c();
    if (in_x4 < 0) {
        FUN_0035047c();
        err = 0x299;
    } else if (in_x7 < in_x5) {
        FUN_0035047c();
        err = 0x29a;
    } else {
        if (SBORROW8(in_x5, in_x4)) {
            /* WARNING: does not return */
            SK_TRAP(); /* SoftwareBreakpoint(1,0x31e9dc) */
        }
        FUN_0034b668();
        FUN_003542b8();
        sk_hook_21480_de7c();
        FUN_00376820(FUN_0034b528(), 0);
        FUN_0034c55c();
        FUN_0031b080();
        FUN_0034878c();
        if (in_x5 - in_x4 == FUN_0019c9cc()) {
            FUN_00376820(FUN_0034b528(), 0);
            FUN_0034c55c();
            FUN_0031b080();
            FUN_0034878c();
            if ((FUN_0019fd10() & 1) != 0) {
                FUN_00356f80(extra);
                return;
            }
            if (in_x6 != 0) {
                thunk_FUN_0028c754((uint64_t)&stk50, 0);
                if (stk50 != 0) {
                    FUN_0034b3e8();
                    FUN_0021867c((uint64_t)&stk28, 0);
                    FUN_0034878c();
                    FUN_0019c9cc();
                    FUN_0022b26c(stk50 + stk28 * *(int64_t *)(ctx + 0x48), 0,
                                 in_x6 + *(int64_t *)(ctx + 0x48) * in_x4, stke0);
                    FUN_00356f80(extra);
                    return;
                }
            }
            FUN_00348898(1);
            FUN_00349a04();
        } else {
            FUN_0035047c();
            err = 0x29b;
        }
        FUN_00348160(err);
    }
    FUN_003524c8();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0031ea14 @ 0x0031ea14 (est. sk_capture_state_ea14)
 * Captures several preserved-register values into a freshly allocated
 * 0x48-byte record, fills its callback/state fields, and returns the record
 * (as a closure pair). Confidence: low.
 * Notes: alloc tag 0x1d51; reads unaff_x19..x23 and param_3/param_4. */
void sk_capture_state_ea14(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t unaff_x19 = 0, unaff_x20 = 0, unaff_x21 = 0, unaff_x22 = 0, unaff_x23 = 0;
    uint64_t unaff_x30 = 0;
    cl4_result_t v = {0,0}; /* = FUN_0028e8fc() */
    cl4_result_t out = {0,0}; /* = FUN_00353978() */
    uint64_t *rec;
    FUN_00084220();
    rec = (uint64_t *)FUN_0036a908(0x48, 0x1d51);
    *(uint64_t **)FUN_0034aa3c() = rec;
    rec[6] = unaff_x20;   /* +0x30 */
    rec[7] = unaff_x19;   /* +0x38 */
    rec[5] = unaff_x22;   /* +0x28 */
    rec[6] = unaff_x21;   /* +0x30 (overwritten as in decompile) */
    rec[4] = unaff_x23;   /* +0x20 */
    FUN_0034b508();
    FUN_00351c64();
    v.lo = FUN_0028e8fc();
    *((cl4_result_t *)rec) = v;
    rec[1] = c;           /* +0x08 */
    rec[1] = d;           /* +0x08 (see decompile: *(pauVar2[1]+8)=param_4) */
    out.lo = FUN_00353978();
    FUN_00084234(out.lo, out.hi, unaff_x30);
}

/* FUN_0031ea94 @ 0x0031ea94 (est. sk_thunk_e294)
 * Runs the TLS teardown helper then the thunk 0x12568. Confidence: low. */
void sk_thunk_e294(void)
{
    FUN_003571f8();
    thunk_FUN_00012568();
}

/* FUN_0031eac4 @ 0x0031eac4 (est. sk_cond_retain_eac4)
 * Runs a callback; if the preserved flag is zero, performs the retain-into
 * context and completion. Confidence: low. ctx=unaff_x21 (flag). */
void sk_cond_retain_eac4(uint64_t a)
{
    sk_fn_t cb = NULL;  /* extraout_x9 */
    uint64_t flag = 0;  /* unaff_x21 */
    FUN_003562f8();
    if (cb) cb();
    if (flag == 0) {
        FUN_0034bc94(a);
        FUN_000839d8();
    }
}

/* FUN_0031eb18 @ 0x0031eb18 (est. sk_cond_retain_eb18)
 * Retain-with-completion wrapper; on success path also runs the inner
 * buffer operation and finalizer. Confidence: low. ctx=unaff_x21. */
void sk_cond_retain_eb18(void)
{
    sk_fn_t cb = NULL;  /* extraout_x9 */
    uint64_t flag = 0;  /* unaff_x21 */
    uint64_t arg = 0;   /* extraout_x8 */
    uint64_t unaff_x30 = 0;
    FUN_00358fb4();
    FUN_003562f8();
    if (cb) cb();
    if (flag == 0) {
        FUN_0034bc94(arg);
        FUN_000839d8();
    }
    FUN_00350470();
    sk_with_c_str_eb94(0, 0, NULL, 0);
    FUN_00358fc8(unaff_x30);
}

/* FUN_0031eb94 @ 0x0031eb94 (est. sk_with_c_str_eb94)
 * withCString-style helper: captures a buffer range and descriptor, resolves
 * a closure pair, and runs the collector; on failure raises a fatal error
 * (code 0x2b8). Confidence: low.
 * Notes: fatal string s_UnsafeMutableBufferPointer_withC_005d3350. */
void sk_with_c_str_eb94(uint64_t a, uint64_t b, uint64_t *p, uint64_t c)
{
    uint64_t uStack_38 = *p;
    uint64_t local_40 = p[1];
    uint64_t local_30 = b;
    uint64_t uStack_28 = a;
    uint64_t local_48 = 0x66ed78;
    uint64_t v, r;
    v = FUN_00310d04(0xff, c);
    v = FUN_00310d68(0, v);
    v = FUN_00376820((uint64_t)&DAT_004ea4dc, v, (uint64_t)&local_48);
    r = FUN_00298cb8((uint64_t)&uStack_28, (uint64_t)&local_30,
                     (uint64_t)&uStack_38, (uint64_t)&local_40, v, 0x677880,
                     FUN_00376820((uint64_t)&DAT_004ea4dc, v, (uint64_t)&local_48), 0x672168);
    if ((r & 1) != 0) return;
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2,
                 s_UnsafeMutableBufferPointer_withC_005d3350, 0x67, 2,
                 s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x2b8, 1);
}

/* FUN_0031ec98 @ 0x0031ec98 (est. sk_make_buf_ec98)
 * Allocates a 0x28-byte buffer record (tag 0x1160), initializes it via
 * 0x31ed10, stores the returned value at +0x20, returns the descriptor.
 * Confidence: low. Notes: unaff_x20 pair source; returns &DAT_003471a4. */
void *sk_make_buf_ec98(int64_t *out, uint64_t *p, int64_t meta)
{
    uint64_t *src = NULL; /* = unaff_x20 */
    int64_t rec = (int64_t)FUN_0036a908(0x28, 0x1160);
    cl4_result_t v;
    *out = rec;
    v = sk_make_buf_init_ed10((int64_t *)rec, *p, (int64_t)*src, (int64_t)src[1],
                              *(int64_t *)(meta + 0x10));
    *(uint64_t *)(rec + 0x20) = v.lo;
    return (void *)&DAT_003471a4;
}

/* FUN_0031ed10 @ 0x0031ed10 (est. sk_make_buf_init_ed10)
 * Initializes a buffer record: sets the element base/stride, allocates the
 * backing storage, and bounds-checks the start index before materializing
 * the element pointer. Errors 0x237/0x238 on index OOB.
 * Confidence: low. Notes: stride=*(slot_meta-8+0x48); alloc tag &DAT_0000d019. */
cl4_result_t sk_make_buf_init_ed10(int64_t *slot, int64_t idx, int64_t base, int64_t len, int64_t meta)
{
    int64_t meta2 = *(int64_t *)(meta - 8);
    int64_t alloc;
    uint64_t err;
    cl4_result_t out = {0,0};
    *slot = meta;
    slot[1] = meta2;
    alloc = (int64_t)FUN_0036a908(*(uint64_t *)(meta2 + 0x40), (uint64_t)&DAT_0000d019);
    slot[2] = alloc;
    if (idx < 0) {
        err = 0x237;
    } else if (idx < len) {
        (*(sk_fn_t)(*(uint64_t *)(meta2 + 0x10)))(alloc, base + *(int64_t *)(meta2 + 0x48) * idx, meta);
        out.hi = (uint64_t)alloc;
        out.lo = (uint64_t)&DAT_003471a8;
        return out;
    } else {
        err = 0x238;
    }
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, err, 1);
}

/* FUN_0031ee90 @ 0x0031ee90 (est. sk_swift_fatal_de)
 * Swift fatal error with fixed code 0xde. Confidence: low. */
void sk_swift_fatal_de(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0xde, 1);
}

/* FUN_0031eefc @ 0x0031eefc (est. sk_swift_fatal_ec)
 * Swift fatal error with fixed code 0xec. Confidence: low. */
void sk_swift_fatal_ec(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0xec, 1);
}

/* FUN_0031ef54 @ 0x0031ef54 (est. sk_buf_index_ef54)
 * Buffer element accessor with bounds check: resolves the element metadata,
 * validates the index against the count, and materializes the element
 * pointer. Errors 0x23e/0x23f. Confidence: low. */
void sk_buf_index_ef54(uint64_t a, uint64_t b, int64_t meta)
{
    int64_t metaobj = *(int64_t *)(meta + 0x10);
    int64_t meta2 = *(int64_t *)(metaobj - 8);
    uint64_t *src = NULL; /* = unaff_x20 */
    int64_t elem;
    uint64_t err;
    DAT_00658c00(*(uint64_t *)(meta2 + 0x40));
    elem = *src;
    (*(sk_fn_t)(*(uint64_t *)(meta2 + 0x10)))((uint64_t)&a, a, metaobj);
    if (elem < 0) {
        err = 0x23e;
    } else if (elem < (int64_t)src[1]) {
        (*(sk_fn_t)(*(uint64_t *)(meta2 + 8)))(a, metaobj);
        (*(sk_fn_t)(*(uint64_t *)(meta2 + 0x28)))
            (src[0] + *(int64_t *)(meta2 + 0x48) * elem, (uint64_t)&a, metaobj);
        return;
    } else {
        err = 0x23f;
    }
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, err, 1);
}

/* FUN_0031f05c @ 0x0031f05c (est. sk_swift_fatal_23e)
 * Swift fatal error with fixed code 0x23e. Confidence: low. */
void sk_swift_fatal_23e(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x23e, 1);
}

/* FUN_0031f0c0 @ 0x0031f0c0 (est. sk_buf_slice_f0c0)
 * Buffer slice materializer: validates the start index against the count and
 * returns an (owner, element-pointer) closure pair. Errors 0x23e/0x23f.
 * Confidence: low. Notes: stride=*(*(meta+0x10)-8+0x48). */
cl4_result_t sk_buf_slice_f0c0(uint64_t a, int64_t *p, int64_t meta)
{
    int64_t start = *p;
    uint64_t err;
    cl4_result_t out = {0,0};
    if (start < 0) {
        err = 0x23e;
    } else if (start < p[1]) {
        out.hi = p[0] + *(int64_t *)(*(int64_t *)(*(int64_t *)(meta + 0x10) - 8) + 0x48) * start;
        out.lo = (uint64_t)FUN_0001a1c8;
        return out;
    } else {
        err = 0x23f;
    }
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, err, 1);
}

/* FUN_0031f180 @ 0x0031f180 (est. sk_buf_batch_f180)
 * Batch buffer copy forwarder: reads 8 values from the two pointer args and
 * the element stride, dispatches to 0x31e874. Confidence: low. */
void sk_buf_batch_f180(uint64_t *a, uint64_t *b, int64_t meta)
{
    uint64_t *src = NULL; /* = unaff_x20 */
    sk_buffer_batch_e874();
}

/* FUN_0031f1c4 @ 0x0031f1c4 (est. sk_make_buf2_f1c4)
 * Allocates a 0x48-byte buffer record (tag 0x7a9), captures the two buffer
 * ranges and element metadata, returns a closure pair (owner=FUN_0031ea94).
 * Confidence: low. Notes: alloc tag 0x7a9. */
cl4_result_t sk_make_buf2_f1c4(int64_t *out, uint64_t *p, int64_t meta)
{
    cl4_result_t v = {0,0}; /* = FUN_0028e8fc() */
    cl4_result_t res = {0,0};
    uint64_t *rec = (uint64_t *)FUN_0036a908(0x48, 0x7a9);
    uint64_t a2, b2;
    *out = (int64_t)rec;
    a2 = p[1];
    rec[2] = *p;
    rec[2] = a2;   /* +0x10..0x18 (see decompile) */
    a2 = 0;        /* *unaff_x20 */
    rec[3] = a2;
    b2 = 0;        /* unaff_x20[1] */
    rec[3] = b2;   /* +0x18..0x20 */
    rec[4] = *(uint64_t *)(meta + 0x10); /* +0x20 */
    v.lo = FUN_0028e8fc();
    *((cl4_result_t *)rec) = v;
    rec[1] = a2;
    rec[1] = b2;
    res.hi = (uint64_t)rec;
    res.lo = (uint64_t)sk_thunk_e294;
    return res;
}


/* FUN_0031f258 @ 0x0031f258 (est. sk_init_with_dt_f258)
 * Lookup-in-descriptor init: resolves `d` against DAT_004edd08 then forwards
 * all args to the out-of-range initializer 0x19f1ec. Confidence: low. */
void sk_init_with_dt_f258(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t v = FUN_00376820((uint64_t)&DAT_004edd08, d);
    FUN_0019f1ec(a, b, c, d, v, e);
}

/* FUN_0031f2f0 @ 0x0031f2f0 (est. sk_retain_capture_f2f0)
 * Forwarder to the retain-capture helper 0x31eac4. Confidence: low. */
void sk_retain_capture_f2f0(void) { sk_cond_retain_eac4(0); }

/* FUN_0031f2f4 @ 0x0031f2f4 (est. sk_retain_capture_f2f4) — duplicate. */
void sk_retain_capture_f2f4(void) { sk_cond_retain_eac4(0); }

/* FUN_0031f30c @ 0x0031f30c (est. sk_with_unwrapped_f30c)
 * Runs a callback, then on the null-flag path performs completion and the
 * withCString closure. Confidence: low. unaff_x20 pair, unaff_x21 flag. */
void sk_with_unwrapped_f30c(uint64_t a, sk_fn_t fn, uint64_t b, uint64_t c)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    uint64_t flag = 0;       /* = unaff_x21 */
    if (fn) fn();
    if (flag == 0) {
        FUN_000839d8(a, 0, 1, c);
    }
    sk_with_c_str_eb94(u1, u2, NULL, 0);
}

/* FUN_0031f3b4 @ 0x0031f3b4 (est. sk_swift_fatal_fa)
 * Swift fatal error with fixed code 0xfa. Confidence: low. */
void sk_swift_fatal_fa(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0xfa, 1);
}

/* FUN_0031f420 @ 0x0031f420 (est. sk_swift_fatal_108)
 * Swift fatal error with fixed code 0x108. Confidence: low. */
void sk_swift_fatal_108(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x108, 1);
}

/* FUN_0031f48c @ 0x0031f48c (est. sk_swift_fatal_noerr_f48c) — fatal stub. */
void sk_swift_fatal_noerr_f48c(void)
{
    FUN_0035047c();
    FUN_003480ac();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0031f4b0 @ 0x0031f4b0 (est. sk_fatal_chain_f4b0)
 * Runs the fatal prelude, the bounds-check helper 0x31e4d4, then the
 * finalizer. Confidence: low. */
void sk_fatal_chain_f4b0(void)
{
    FUN_0034c434();
    sk_swift_fatal_entry_e4d4();
    FUN_0035272c();
}

/* FUN_0031f4e4 @ 0x0031f4e4 (est. sk_update_with_pointer_f4e4)
 * Swift UnsafeMutablePointer.update(...) helper: validates the buffer can
 * hold the element count (code 0x3d1) and the pointer is non-nil (0x179),
 * then performs the update. Confidence: low.
 * Notes: fatal strings s_buffer_cannot_contain_every_elem_005d0570 /
 * s_unsafelyUnwrapped_of_nil_optiona_005ce1c0 / s_Swift_Optional_swift_005ce1f0. */
int64_t sk_update_with_pointer_f4e4(int64_t a, int64_t b, int64_t c, int64_t len)
{
    if (a == 0) {
        b = 0;
    } else {
        if (len < b) {
            /* WARNING: does not return */
            FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2,
                         s_buffer_cannot_contain_every_elem_005d0570, 0x30, 2,
                         s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x3d1, 1);
        }
        if (c == 0) {
            /* WARNING: does not return */
            FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2,
                         s_unsafelyUnwrapped_of_nil_optiona_005ce1c0, 0x21, 2,
                         s_Swift_Optional_swift_005ce1f0, 0x14, 2, 0x179, 1);
        }
        FUN_0022b21c(a, b, c, (uint64_t)s_UnsafeMutablePointer_update_with_005cf3f0, 0x2f, 0x3ed);
    }
    return b;
}

/* FUN_0031f5d8 @ 0x0031f5d8 (est. sk_swift_fatal_entry_f5d8)
 * Fatal-entry forwarder to 0x3200c8. Confidence: low. */
void sk_swift_fatal_entry_f5d8(void) { sk_swift_checked_slice_200c8(); }

/* FUN_0031f668 @ 0x0031f668 (est. sk_cond_retain_f668)
 * Forwarder to 0x31f680. Confidence: low. */
void sk_cond_retain_f668(void) { sk_cond_retain_f680(); }

/* FUN_0031f680 @ 0x0031f680 (est. sk_cond_retain_f680)
 * Runs a callback and, on the null-flag path, performs the retain-into and
 * completion. Confidence: low. Notes: unaff_x21 flag; reads in_x3. */
void sk_cond_retain_f680(void)
{
    sk_fn_t cb = NULL;  /* extraout_x9 */
    uint64_t flag = 0;  /* unaff_x21 */
    uint64_t in_x3 = 0;
    FUN_0035a184();
    FUN_00354e00();
    if (cb) cb();
    if (flag == 0) {
        FUN_0034bc94();
        FUN_000839d8();
    }
}

/* FUN_0031f6ec @ 0x0031f6ec (est. sk_apply_f6ec)
 * Applies a callback to the context pair + element metadata and stores the
 * returned 16-byte value at *out. Confidence: low. Notes: unaff_x20 pair. */
void sk_apply_f6ec(cl4_result_t *out, int64_t meta, uint64_t a, sk_fn_t fn)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    cl4_result_t v = {0,0};
    v.lo = (uint64_t)fn(u1, u2, *(uint64_t *)(meta + 0x10)); v.hi = 0;
    *out = v;
}

/* FUN_0031f728 @ 0x0031f728 (est. sk_init_with_dt_f728)
 * Lookup-in-descriptor init against DAT_004edd94. Confidence: low. */
void sk_init_with_dt_f728(uint64_t a)
{
    uint64_t v = FUN_00376820((uint64_t)&DAT_004edd94, a);
    FUN_001a0194(a, v);
}

/* FUN_0031f788 @ 0x0031f788 (est. sk_init_with_meta_f788)
 * Resolves metadata via FUN_00376820 then forwards to 0x1e088c.
 * Confidence: low. */
void sk_init_with_meta_f788(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t v = FUN_00376820(c, a);
    FUN_001e088c(a, v);
}

/* FUN_0031f7ec @ 0x0031f7ec (est. sk_apply5_f7ec)
 * Applies a 5-argument callback to the context and element metadata, stores
 * the returned 16-byte value, and returns the first context word.
 * Confidence: low. Notes: unaff_x20 pair. */
uint64_t sk_apply5_f7ec(cl4_result_t *out, uint64_t a, uint64_t b, int64_t meta, uint64_t c, sk_fn_t fn)
{
    uint64_t u1 = 0; /* = unaff_x20 */
    cl4_result_t v = {0,0};
    u1 = 0;
    v.lo = (uint64_t)fn(a, b, u1, 0, *(uint64_t *)(meta + 0x10)); v.hi = 0;
    *out = v;
    return u1;
}

/* FUN_0031f834 @ 0x0031f834 (est. sk_capture_retain_f834)
 * Runs the callback on the context pair; on the null-flag path delivers a
 * completion. Confidence: low. Notes: unaff_x20 pair, unaff_x21 flag. */
void sk_capture_retain_f834(uint64_t a, sk_fn_t fn, uint64_t b, uint64_t c)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    uint64_t flag = 0;       /* = unaff_x21 */
    if (fn) fn(u1, u2);
    if (flag == 0) {
        FUN_000839d8(a, 0, 1, c);
    }
}

/* FUN_0031f8a4 @ 0x0031f8a4 (est. sk_swift_fatal_noerr_f8a4) — fatal stub. */
void sk_swift_fatal_noerr_f8a4(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031f8dc @ 0x0031f8dc (est. sk_swift_fatal_noerr_f8dc) — fatal stub. */
void sk_swift_fatal_noerr_f8dc(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031f90c @ 0x0031f90c (est. sk_swift_fatal_noerr_f90c) — fatal stub. */
void sk_swift_fatal_noerr_f90c(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031f944 @ 0x0031f944 (est. sk_swift_fatal_noerr_f944) — fatal stub. */
void sk_swift_fatal_noerr_f944(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031f974 @ 0x0031f974 (est. sk_swift_fatal_noerr_f974) — fatal stub. */
void sk_swift_fatal_noerr_f974(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031f998 @ 0x0031f998 (est. sk_bounds_check_f998)
 * Precondition bounds check: verifies [a, a+n) lies within [.. end). On any
 * violation calls the fatal/overflow handlers. Confidence: low.
 * Notes: uses SCARRY8(a,n) overflow check. */
void sk_bounds_check_f998(int64_t a, uint64_t n, int64_t end)
{
    uint64_t uVar1 = (uint64_t)end - (uint64_t)a;
    if (SBORROW8(end, a)) {
        FUN_0034def4();
    } else {
        if ((int64_t)n < 1) {
            if ((int64_t)uVar1 < 1 && (int64_t)n < (int64_t)uVar1) {
                FUN_00068e14();
                return;
            }
        } else if (-1 < (int64_t)uVar1 && uVar1 < n) {
            FUN_00068e14();
            return;
        }
        if (!SCARRY8(a, n)) return;
        FUN_0035047c((uint64_t)a + n);
    }
    FUN_003480ac();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0031fa08 @ 0x0031fa08 (est. sk_swift_fatal_entry_fa08)
 * Fatal-entry forwarder to 0x31fa14. Confidence: low. */
void sk_swift_fatal_entry_fa08(void) { sk_bounds_check_fa14(0, 0, 0); }


/* FUN_0031fa14 @ 0x0031fa14 (est. sk_bounds_check_fa14)
 * Precondition bounds check (variant of 0x31f998): verifies [a, a+n) lies
 * within [.. end), calling fatal/overflow handlers on violation.
 * Confidence: low. */
void sk_bounds_check_fa14(int64_t a, uint64_t n, int64_t end)
{
    uint64_t uVar1 = (uint64_t)end - (uint64_t)a;
    if (SBORROW8(end, a)) {
        FUN_0035047c();
    } else {
        if ((int64_t)n < 1) {
            if ((int64_t)uVar1 < 1 && (int64_t)n < (int64_t)uVar1) {
                FUN_00068e14();
                return;
            }
        } else if (-1 < (int64_t)uVar1 && uVar1 < n) {
            FUN_00068e14();
            return;
        }
        if (!SCARRY8(a, n)) return;
        FUN_0035047c((uint64_t)a + n);
    }
    FUN_003480ac();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0031fa94 @ 0x0031fa94 (est. sk_swift_fatal_noerr_fa94) — fatal stub. */
void sk_swift_fatal_noerr_fa94(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_0031faf8 @ 0x0031faf8 (est. sk_range_check_faf8)
 * Range precondition: requires a in [b, c); else fatal. Confidence: low. */
void sk_range_check_faf8(int64_t a, int64_t b, int64_t c)
{
    if (a < b) {
        FUN_0035047c();
    } else {
        if (a < c) return;
        FUN_0035047c();
    }
    FUN_003480ac();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0031fb40 @ 0x0031fb40 (est. sk_swift_fatal_entry_fb40)
 * Fatal-entry forwarder to 0x31fb6c. Confidence: low. */
void sk_swift_fatal_entry_fb40(void) { sk_range_check_fb6c(0, 0, 0, 0); }

/* FUN_0031fb6c @ 0x0031fb6c (est. sk_range_check_fb6c)
 * Range precondition: requires a >= c and b <= d; else fatal.
 * Confidence: low. */
void sk_range_check_fb6c(int64_t a, int64_t b, int64_t c, int64_t d)
{
    if (a < c) {
        FUN_0035047c();
    } else {
        if (b <= d) return;
        FUN_0035a158();
    }
    FUN_003480ac();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0031fbb0 @ 0x0031fbb0 (est. sk_make_buf_fbb0)
 * Allocates a 0x28-byte buffer record (tag 0x6008), initializes it via
 * 0x31fc64, stores the value at +0x20, returns the descriptor.
 * Confidence: low. Notes: unaff_x20 pair source; returns &DAT_003471a4. */
void *sk_make_buf_fbb0(int64_t *out, uint64_t *p, int64_t meta)
{
    uint64_t *src = NULL; /* = unaff_x20 */
    int64_t rec = (int64_t)FUN_0036a908(0x28, 0x6008);
    cl4_result_t v;
    *out = rec;
    v = sk_make_buf_init_fc64((int64_t *)rec, (int64_t)*p, (int64_t)*src, (int64_t)src[1],
                              *(int64_t *)(meta + 0x10));
    *(uint64_t *)(rec + 0x20) = v.lo;
    return (void *)&DAT_003471a4;
}

/* FUN_0031fc28 @ 0x0031fc28 (est. sk_buf_release_fc28)
 * Buffer release: calls the element deallocator at +0x20 then the TLS
 * teardown thunk. Confidence: low. */
void sk_buf_release_fc28(int64_t *p)
{
    int64_t rec = *p;
    (*(sk_fn_t)(*(uint64_t *)(rec + 0x20)))(rec);
    thunk_FUN_00012568(rec);
}

/* FUN_0031fc64 @ 0x0031fc64 (est. sk_make_buf_init_fc64)
 * Initializes a buffer record (variant of 0x31ed10): sets element base /
 * stride, allocates backing storage, bounds-checks the start index, and
 * materializes the element pointer. Errors 0x75d/0x75e. Confidence: low.
 * Notes: alloc tag 0xaa1a. */
cl4_result_t sk_make_buf_init_fc64(int64_t *slot, int64_t idx, int64_t base, int64_t len, int64_t meta)
{
    int64_t meta2 = *(int64_t *)(meta - 8);
    int64_t alloc;
    uint64_t err;
    cl4_result_t out = {0,0};
    *slot = meta;
    slot[1] = meta2;
    alloc = (int64_t)FUN_0036a908(*(uint64_t *)(meta2 + 0x40), 0xaa1a);
    slot[2] = alloc;
    if (idx < 0) {
        err = 0x75d;
    } else if (idx < len) {
        (*(sk_fn_t)(*(uint64_t *)(meta2 + 0x10)))(alloc, base + *(int64_t *)(meta2 + 0x48) * idx, meta);
        out.hi = (uint64_t)alloc;
        out.lo = (uint64_t)&DAT_003471a8;
        return out;
    } else {
        err = 0x75e;
    }
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, err, 1);
}

/* FUN_0031fdac @ 0x0031fdac (est. sk_apply4_fdac)
 * Applies a 5-argument callback to the buffer pair + metadata, then runs the
 * completion helper. Confidence: low. Notes: unaff_x20 pair. */
void sk_apply4_fdac(uint64_t *a, int64_t meta, uint64_t b, sk_fn_t fn)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    if (fn) fn(*a, a[1], u1, u2, *(uint64_t *)(meta + 0x10));
    FUN_003554e0();
}

/* FUN_0031fdf0 @ 0x0031fdf0 (est. sk_count_range_fdf0)
 * Returns the buffer count into *out; if the stored count is negative it
 * traps (precondition). Confidence: low. Notes: reads *(ctx+8). */
void sk_count_range_fdf0(uint64_t *out)
{
    int64_t *ctx = NULL; /* = unaff_x20 */
    int64_t count = *(int64_t *)(ctx + 1);
    if (-1 < count) {
        *out = 0;
        out[1] = (uint64_t)count;
        return;
    }
    FUN_00347de8(1);
    /* WARNING: does not return */
    FUN_001afe4c();
}


/* FUN_0031fe70 @ 0x0031fe70 (est. sk_swift_fatal_63e)
 * Swift fatal error with fixed code 0x63e. Confidence: low. */
void sk_swift_fatal_63e(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x63e, 1);
}

/* FUN_0031fedc @ 0x0031fedc (est. sk_swift_fatal_64c)
 * Swift fatal error with fixed code 0x64c. Confidence: low. */
void sk_swift_fatal_64c(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x64c, 1);
}

/* FUN_0031ff48 @ 0x0031ff48 (est. sk_swift_fatal_65a)
 * Swift fatal error with fixed code 0x65a. Confidence: low. */
void sk_swift_fatal_65a(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x65a, 1);
}

/* FUN_0031ffb4 @ 0x0031ffb4 (est. sk_swift_fatal_668)
 * Swift fatal error with fixed code 0x668. Confidence: low. */
void sk_swift_fatal_668(void)
{
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)&DAT_005be7c0, 0, 2,
                 (uint64_t)s_Swift_UnsafeBufferPointer_swift_005cdc10, 0x1f, 2, 0x668, 1);
}

/* FUN_00320020 @ 0x00320020 (est. sk_swift_fatal_noerr_20020) — fatal stub. */
void sk_swift_fatal_noerr_20020(void)
{
    FUN_0035047c();
    FUN_003480ac();
    FUN_001afe4c();
}

/* FUN_00320044 @ 0x00320044 (est. sk_fatal_chain_20044)
 * Fatal chain: prelude, bounds-check helper 0x31fa08, finalizer.
 * Confidence: low. */
void sk_fatal_chain_20044(void)
{
    FUN_0034c434();
    sk_swift_fatal_entry_fa08();
    FUN_0035272c();
}

/* FUN_00320078 @ 0x00320078 (est. sk_cond_call_20078)
 * If `cond` is nonzero, runs the thunk 0x359208. Confidence: low. */
void sk_cond_call_20078(int64_t cond)
{
    if (cond != 0) {
        thunk_FUN_00359208();
    }
}

/* FUN_00320084 @ 0x00320084 (est. sk_swift_fatal_entry_20084)
 * Fatal-entry forwarder to 0x3200c8. Confidence: low. */
void sk_swift_fatal_entry_20084(void) { sk_swift_checked_slice_200c8(); }

/* FUN_003200c8 @ 0x003200c8 (est. sk_swift_checked_slice_200c8)
 * Swift checked-slice helper: resolves two array element layouts, validates
 * that the two ranges share an element size (or computes their GCD of
 * strides), then performs the element-wise slice. On mismatch it raises a
 * fatal error. Confidence: low. Notes: stride = *(*(in_x6-8)+0x50/0x48);
 * uses SoftwareBreakpoint(1,0x3201f8); fatal tail 0x1afe4c. */
void sk_swift_checked_slice_200c8(void)
{
    int64_t in_x3 = 0, in_x4 = 0, in_x5 = 0, in_x6 = 0;
    uint64_t stk08 = 0, stk10 = 0, stk18 = 0;
    sk_fn_t unaff_x22 = NULL;
    uint64_t extra = 0; /* extraout_x8 */
    int64_t stride_a, stride_b;
    int64_t g;
    FUN_003534d4();
    if (in_x3 == 0) {
        FUN_00019858(extra);
    } else {
        if ((*(uint32_t *)(*(int64_t *)(in_x6 - 8) + 0x50) & (uint32_t)in_x3 & 0xff) != 0) {
            FUN_00348b7c(stk08);
            FUN_00349a04();
            FUN_003524c8();
            /* WARNING: does not return */
            FUN_001afe4c();
        }
        stride_a = *(int64_t *)(*(int64_t *)(in_x6 - 8) + 0x48);
        stride_b = *(int64_t *)(*(int64_t *)(in_x5 - 8) + 0x48);
        if (stride_a != stride_b) {
            if (SUB168(SEXT816(in_x4) * SEXT816(stride_b), 8) != in_x4 * stride_b >> 0x3f) {
                /* WARNING: does not return */
                SK_TRAP(); /* SoftwareBreakpoint(1,0x3201f8) */
            }
            if (stride_a == 0) {
                FUN_00348074(1);
                FUN_00351be0();
                FUN_001afe4c();
            }
            if (in_x4 * stride_b == -0x8000000000000000 && stride_a == -1) {
                FUN_0034834c(1);
                FUN_00351be0();
                FUN_001afe4c();
            }
            if (stride_b < stride_a) {
                if (stride_b == 0) {
                    FUN_00348404(1);
                    FUN_00351be0();
                    FUN_001afe4c();
                }
                g = 0;
                if (stride_b != 0) { g = stride_a / stride_b; }
                stride_a = stride_a - g * stride_b;
            } else {
                if (stride_b == -0x8000000000000000 && stride_a == -1) {
                    FUN_003488bc(1);
                    FUN_00349098();
                    FUN_00351be0();
                    FUN_001afe4c();
                }
                g = 0;
                if (stride_a != 0) { g = stride_b / stride_a; }
                stride_a = stride_b - g * stride_a;
            }
            if (stride_a != 0) {
                FUN_00348b7c(stk18);
                FUN_00349a04();
                FUN_003524c8();
                FUN_001afe4c();
            }
        }
        FUN_00355b68(stk10);
        if (unaff_x22) unaff_x22();
    }
    if (unaff_x22) unaff_x22();
}


/* FUN_003202a0 @ 0x003202a0 (est. sk_swift_cow_retain_202a0)
 * Large Swift-runtime COW/refcount + capability-store routine. Performs a
 * multi-stage object retain/release dance with heap metadata: allocates a
 * working record, pushes/pops it through a TLS task registry, applies an
 * injected callback, and resolves a descriptor pair, masking off the
 * pointer-tag bits (>>0x3d) at each stage. Heavily register-aliased by the
 * decompiler; each `extraout_x8_N`/`pcVar_N`/`in_ZR` is a decompiler artifact
 * of a preserved register.
 * Confidence: low. Notes: alloc tags 0x16/0x...; task register via
 * FUN_0006e778(0x16); fatal tail 0x1afe4c; string s__start__005d2d87. */
void sk_swift_cow_retain_202a0(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                               uint64_t e, sk_fn_t fn)
{
    uint64_t unaff_x19 = 0, unaff_x20 = 0, unaff_x23 = 0;
    uint64_t unaff_x27 = 0, unaff_x28 = 0, unaff_x30 = 0;
    uint64_t extra0 = 0, extra1 = 0, extra2 = 0, extra3 = 0; /* extraout_x8_N */
    bool in_ZR = false;
    cl4_result_t r8 = {0,0}, r7 = {0,0}, r6 = {0,0};
    cl4_result_t local_40 = {0,0}, local_48 = {0,0};
    uint64_t local_60 = 0;
    uint8_t auStack_50[8] = {0};
    uint64_t uStack_70 = 0, local_28 = 0, local_20 = 0, local_18 = 0;
    uint64_t pcVar9 = 0, pcVar10 = 0, pcVar5 = 0, pcVar4 = 0, pcVar3 = 0;
    sk_fn_t param_6_keep = fn;
    uint64_t v;

    r8.hi = unaff_x27; r8.lo = unaff_x28;
    r7.hi = unaff_x19; r7.lo = unaff_x23;
    r6.lo = FUN_0008e518();
    local_48.lo = r6.hi;
    pcVar9 = r6.lo;
    r6.lo = FUN_00355b68();
    local_40.lo = FUN_001a89a8(r6.lo, r6.hi, 1);
    FUN_0006e778(0x16);
    r6.lo = FUN_003548dc();
    FUN_0035940c((uint64_t)s__start__005d2d87);
    FUN_003578cc();
    FUN_0034b5e8();

    if (extra0 == 0 &&
        (((uint64_t)unaff_x23 & (unaff_x20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0) {
        FUN_003a25d4();
    } else {
        if ((unaff_x20 >> 0x3d & 1) == 0) {
            in_ZR = (unaff_x27 & 0x2000000000000000) == 0;
        } else if ((unaff_x27 >> 0x3d & 1) != 0) {
            FUN_00350aa0();
            FUN_00351dcc();
            FUN_0034b7c8();
            if (!in_ZR) {
                FUN_00358f84();
                FUN_003a25d4();
                FUN_003a25d4();
                r8 = r7;
                goto L_2035c;
            }
        }
        FUN_003509b0();
        FUN_0035370c();
        FUN_002a4c98();
        FUN_003a25d4();
        r8 = r6;
    }
L_2035c:
    pcVar10 = r8.hi;
    local_28 = pcVar9;
    DAT_00658c00();
    local_60 = c;
    FUN_00352720();
    if (param_6_keep) param_6_keep();
    FUN_00352efc();
    r7.lo = FUN_00310d68();
    FUN_0035401c(r7.lo, r7.hi, r7.lo);
    FUN_00084180((uint64_t)&local_20);
    FUN_001d88fc();
    r6.hi = local_18;
    r6.lo = local_20;
    if (local_18 == 0) {
        r6.lo = FUN_00353830();
    }
    pcVar4 = r6.hi;
    pcVar5 = r6.lo;
    v = FUN_00349cbc(r8.lo);
    pcVar3 = pcVar10;
    if (extra1 == 0 && (((v & ((uint64_t)pcVar10 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(pcVar10);
    } else {
        param_6_keep = (sk_fn_t)((uint64_t)pcVar4 >> 0x38 & 0xf);
        if (((uint64_t)pcVar10 >> 0x3d & 1) == 0) {
            in_ZR = ((uint64_t)pcVar4 & 0x2000000000000000) == 0;
            pcVar5 = (uint64_t)pcVar5 & 0xffffffffffff;
            if (!in_ZR) { pcVar5 = (uint64_t)param_6_keep; }
        } else if (((uint64_t)pcVar4 >> 0x3d & 1) == 0) {
            pcVar5 = (uint64_t)pcVar5 & 0xffffffffffff;
        } else {
            FUN_00353098();
            FUN_0034b89c();
            pcVar5 = (uint64_t)param_6_keep;
            if (!in_ZR) {
                FUN_0034f078();
                FUN_003a25d4();
                FUN_003a25d4(pcVar4);
                pcVar5 = (uint64_t)auStack_50;
                pcVar4 = unaff_x23;
                goto L_20458;
            }
        }
        thunk_FUN_0036b270(pcVar4);
        FUN_003504f4();
        FUN_00353b40();
        FUN_002a4c98();
        FUN_0035ac1c();
        pcVar3 = (uint64_t)auStack_50;
        param_6_keep = (sk_fn_t)pcVar5;
        pcVar5 = r8.lo;
        pcVar4 = pcVar10;
    }
L_20458:
    FUN_0035a8a8();
    FUN_00355c78();
    FUN_0034f98c((uint64_t)pcVar5 & 0xffffffffffff);
    if (extra2 == 0 &&
        ((((uint64_t)pcVar5 & ((uint64_t)pcVar4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(pcVar4);
    } else {
        if (((uint64_t)pcVar4 >> 0x3d & 1) == 0) {
            FUN_0034dd64();
        } else if (((uint64_t)param_6_keep >> 0x3d & 1) != 0) {
            r8.lo = (uint64_t)FUN_003504f4(); r8.hi = 0;
            FUN_0034b1a0(r8.lo, r8.hi, pcVar9);
            if (!in_ZR) {
                FUN_0034f584();
                FUN_003a25d4();
                FUN_003a25d4((uint64_t)param_6_keep);
                pcVar9 = pcVar3;
                param_6_keep = (sk_fn_t)auStack_50;
                goto L_204bc;
            }
        }
        FUN_0034ee38();
        FUN_002a4c98();
        FUN_003a25d4((uint64_t)param_6_keep);
        pcVar9 = pcVar5;
        param_6_keep = (sk_fn_t)pcVar4;
    }
L_204bc:
    r8.lo = (uint64_t)FUN_00356340(); r8.hi = 0;
    FUN_002364dc(r8.lo, r8.hi, local_48.lo);
    FUN_00352c74();
    FUN_0034d044((uint64_t)pcVar9 & 0xffffffffffff);
    if (extra3 == 0 &&
        ((((uint64_t)pcVar9 & ((uint64_t)param_6_keep ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4((uint64_t)param_6_keep);
        pcVar9 = pcVar4;
    } else {
        if (((uint64_t)param_6_keep >> 0x3d & 1) == 0) {
            FUN_0034a618();
        } else if (((uint64_t)pcVar4 >> 0x3d & 1) != 0) {
            FUN_00100c38();
            FUN_00349c98();
            if (!in_ZR) {
                FUN_00351a5c();
                FUN_003a25d4((uint64_t)param_6_keep);
                FUN_003a25d4(pcVar4);
                FUN_00355f7c();
                pcVar9 = (uint64_t)auStack_50;
                goto L_20520;
            }
        }
        FUN_0034c9c8();
        FUN_002a4c98();
        FUN_003a25d4(pcVar4);
        pcVar4 = (uint64_t)param_6_keep;
        unaff_x23 = pcVar9;
        pcVar9 = (uint64_t)param_6_keep;
    }
L_20520:
    FUN_0034b178();
    FUN_001a89a8();
    FUN_00354ddc();
    FUN_0034b18c();
    if (extra0 == 0 &&
        ((((uint64_t)unaff_x23 & ((uint64_t)pcVar4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(pcVar4);
    } else {
        if (((uint64_t)pcVar4 >> 0x3d & 1) == 0) {
            FUN_0034e374((uint64_t)pcVar5 & 0xffffffffffff);
        } else if (((uint64_t)param_6_keep >> 0x3d & 1) != 0) {
            r8.lo = (uint64_t)FUN_00350560(); r8.hi = 0;
            FUN_0034b1a0(r8.lo, r8.hi, pcVar5);
            if (!in_ZR) {
                FUN_00351e08();
                FUN_003a25d4(pcVar4);
                FUN_003a25d4((uint64_t)param_6_keep);
                param_6_keep = (sk_fn_t)auStack_50;
                goto L_20584;
            }
        }
        FUN_0034f454();
        FUN_002a4c98();
        FUN_003a25d4((uint64_t)param_6_keep);
        param_6_keep = (sk_fn_t)pcVar9;
    }
L_20584:
    v = local_40.hi;
    FUN_00351178(local_40.lo);
    FUN_001e3f70();
    FUN_00351a50();
    FUN_003a25d4(v);
    FUN_003a25d4((uint64_t)param_6_keep);
    r8.lo = (uint64_t)FUN_0009461c(); r8.hi = 0;
    FUN_0008e500(r8.lo, r8.hi, unaff_x30);
}


/* FUN_003206bc @ 0x003206bc (est. sk_copy_overlapping_206bc)
 * Partially copies up to `n` bytes from [src, end) to `dst`, advancing src;
 * returns the (src, end) pair. Only copies when ranges are non-empty.
 * Confidence: low. Notes: element copy via FUN_002bf038. */
cl4_result_t sk_copy_overlapping_206bc(uint64_t a, int64_t n, uint64_t src, uint64_t end)
{
    int64_t l;
    cl4_result_t out = {0,0};
    if (src != 0 && (l = (int64_t)(end - src), src <= end && l != 0) && n != 0) {
        if (n <= l) { l = n; }
        FUN_002bf038(src, l, a);
        src = src + (uint64_t)l;
    }
    out.hi = end;
    out.lo = src;
    return out;
}

/* FUN_00320744 @ 0x00320744 (est. sk_cond_retain_20744)
 * Forwarder to the apply-cond helper 0x321218. Confidence: low. */
void sk_cond_retain_20744(void) { sk_apply_cond_21218(0,0,0,0,0,0,NULL); }

/* FUN_00320748 @ 0x00320748 (est. sk_cond_retain_20748) — duplicate. */
void sk_cond_retain_20748(void) { sk_apply_cond_21218(0,0,0,0,0,0,NULL); }

/* FUN_00320770 @ 0x00320770 (est. sk_apply7_20770)
 * Forwarder to the subscript helper 0x3212c4. Confidence: low. */
void sk_apply7_20770(void) { sk_buf_subscript_212c4(0, 0, 0); }

/* FUN_0032077c @ 0x0032077c (est. sk_make_buf3_2077c)
 * Builds a 4-word buffer record, runs the subscript, stores the tag byte at
 * +0x18, returns the descriptor &DAT_003207d0. Confidence: low. */
void *sk_make_buf3_2077c(uint64_t *out, uint64_t a, uint64_t b, uint64_t c)
{
    uint8_t tag;
    out[1] = b;
    out[2] = c;
    *out = a;
    FUN_00351488(a);
    tag = sk_buf_subscript_212c4(0, 0, 0);
    *(uint8_t *)(out + 3) = tag;
    return (void *)&DAT_003207d0;
}

/* FUN_003207d4 @ 0x003207d4 (est. sk_cond_retain_207d4)
 * Forwarder to the bounds-ensure helper 0x321324. Confidence: low. */
void sk_cond_retain_207d4(void) { sk_bounds_ensure_21324(0, 0, 0, 0); }

/* FUN_003207e0 @ 0x003207e0 (est. sk_copy_replace_207e0)
 * Replace-subrange copy helper: validates the source range, performs the
 * element-wise copy/overwrite via the buffer callbacks, else fatal.
 * Errors 0xea/0xeb/0xec. Confidence: low.
 * Notes: uses SoftwareBreakpoint(1,0x32090c/0x320910); fatal tail 0x1afe4c. */
void sk_copy_replace_207e0(uint64_t a, uint64_t b, int64_t base, uint64_t c, int64_t lo,
                           int64_t hi, int64_t slo, int64_t shi)
{
    uint64_t unaff_x22 = 0, unaff_x23 = 0;
    int64_t lVar2 = shi;
    uint64_t err;
    FUN_00354a34();
    if (lo < 0) {
        FUN_0035047c();
        err = 0xea;
    } else {
        FUN_00354708();
        if (lVar2 == 0) {
            if (0 < hi) goto L_208f0;
        } else if (shi - slo < hi) {
L_208f0:
            FUN_0035047c();
            err = 0xeb;
            goto L_20918;
        }
        if (SBORROW8(hi, lo)) {
            /* WARNING: does not return */
            SK_TRAP(); /* SoftwareBreakpoint(1,0x32090c) */
        }
        FUN_003508e4();
        FUN_001dff60();
        FUN_00351790();
        FUN_00351488();
        FUN_0019fe7c();
        FUN_003508e4();
        FUN_001dff60();
        FUN_00351790();
        FUN_00351488();
        FUN_0019fe7c();
        if (SBORROW8(unaff_x23, unaff_x22)) {
            /* WARNING: does not return */
            SK_TRAP(); /* SoftwareBreakpoint(1,0x320910) */
        }
        if (hi - lo == unaff_x23 - unaff_x22) {
            if (unaff_x22 == unaff_x23) {
                FUN_00354ef8(0);
                return;
            }
            if (slo != 0 && base != 0) {
                FUN_00350720();
                FUN_001dff60();
                FUN_00351790();
                FUN_00351488();
                FUN_0019fe7c();
                FUN_00350720();
                FUN_001dff60();
                FUN_00351790();
                FUN_00351488();
                FUN_0019fe7c();
                FUN_00354ef8((uint64_t)base + unaff_x22, hi - lo, slo + lo, 0);
                FUN_002bf038();
                return;
            }
            FUN_00348898(1);
            FUN_00349644();
            goto L_20924;
        }
        FUN_0035047c();
        err = 0xec;
    }
L_20918:
    FUN_003486b8(err);
    FUN_00349644();
L_20924:
    FUN_00351094();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_00320950 @ 0x00320950 (est. sk_alloc_ctx_20950)
 * Allocates a 0x40-byte context record (tag 0xc7ac), fills four state slots
 * from preserved registers, then runs the init/finalize helpers.
 * Confidence: low. Notes: alloc tag 0xc7ac; reads unaff_x19..x22. */
void sk_alloc_ctx_20950(void)
{
    uint64_t unaff_x19 = 0, unaff_x20 = 0, unaff_x21 = 0, unaff_x22 = 0;
    uint64_t *rec;
    rec = (uint64_t *)FUN_0036a908(0x40, 0xc7ac);
    *(uint64_t **)FUN_0034b13c() = rec;
    rec[0x30/8] = unaff_x20;
    rec[0x38/8] = unaff_x19;
    rec[0x20/8] = unaff_x22;
    rec[0x28/8] = unaff_x21;
    FUN_0008412c();
    sk_cond_retain_207d4();
    FUN_00357694();
    FUN_00353c54();
}

/* FUN_003209c4 @ 0x003209c4 (est. sk_buf_finalize_209c4)
 * Finalizes the buffer: runs the replace helper then TLS teardown.
 * Confidence: low. */
void sk_buf_finalize_209c4(uint64_t *p)
{
    uint64_t v = *p;
    FUN_00357228();
    sk_copy_replace_207e0(0,0,0,0,0,0,0,0);
    thunk_FUN_00012568(v);
}

/* FUN_003209fc @ 0x003209fc (est. sk_swap2_209fc)
 * Swaps two bytes in a buffer with bounds validation; fatal on violation.
 * Errors 0x105/0x106. Confidence: low. */
void sk_swap2_209fc(uint64_t a, uint64_t b, int64_t base, int64_t len)
{
    int64_t l;
    uint64_t err;
    uint8_t t;
    if (a == b) return;
    if ((int64_t)(b | a) < 0) {
        FUN_0035047c();
        err = 0x105;
    } else {
        l = 0;
        if (base != 0) { l = len - base; }
        if ((int64_t)a < l && (int64_t)b < l) {
            if (base != 0) {
                t = *(uint8_t *)(base + a);
                *(uint8_t *)(base + a) = *(uint8_t *)(base + b);
                *(uint8_t *)(base + b) = t;
                return;
            }
            FUN_00348898(1);
            FUN_00349644();
            goto L_20a60;
        }
        FUN_0035047c();
        err = 0x106;
    }
    FUN_003486b8(err);
    FUN_00349644();
L_20a60:
    FUN_00351094();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_00320aa8 @ 0x00320aa8 (est. sk_make_buf4_20aa8)
 * Builds a buffer record from two ranges, stores the subscript tag byte,
 * returns the descriptor &DAT_003207d0. Confidence: low.
 * Notes: unaff_x20 pair source. */
void *sk_make_buf4_20aa8(uint64_t *out, uint64_t *p)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    uint8_t tag;
    u1 = 0; u2 = 0;
    *out = *p;
    out[1] = u1;
    out[2] = u2;
    tag = sk_buf_subscript_212c4(0, 0, 0);
    *(uint8_t *)(out + 3) = tag;
    return (void *)&DAT_003207d0;
}

/* FUN_00320b18 @ 0x00320b18 (est. sk_make_buf5_20b18)
 * Allocates a 0x40-byte buffer record (tag 0x8f81), captures two ranges,
 * runs the bounds-ensure helper, and returns a closure pair.
 * Confidence: low. Notes: alloc tag 0x8f81; owner=FUN_003209c4. */
cl4_result_t sk_make_buf5_20b18(int64_t *out, uint64_t *p)
{
    uint64_t u1 = 0, u2 = 0, a2, b2; /* = unaff_x20 pair */
    cl4_result_t v = {0,0}, res = {0,0}; /* = FUN_003207d4() */
    uint64_t *rec = (uint64_t *)FUN_0036a908(0x40, 0x8f81);
    a2 = p[1];
    *out = (int64_t)rec;
    rec[2] = *p;
    rec[2] = a2;
    u1 = 0; u2 = 0;
    rec[3] = u1;
    rec[3] = u2;
    sk_cond_retain_207d4(); v.lo = 0; v.hi = 0;
    *((cl4_result_t *)rec) = v;
    rec[1] = u1;
    rec[1] = u2;
    res.hi = (uint64_t)rec;
    res.lo = (uint64_t)sk_buf_finalize_209c4;
    return res;
}

/* FUN_00320b98 @ 0x00320b98 (est. sk_maybe_store_20b98)
 * Resolves a value and, if the preserved flag is zero, stores it at *out.
 * Confidence: low. Notes: unaff_x21 flag. */
void sk_maybe_store_20b98(uint64_t *out)
{
    uint64_t flag = 0; /* = unaff_x21 */
    uint64_t v = FUN_0019f148();
    if (flag == 0) {
        *out = v;
    }
}

/* FUN_00320bd4 @ 0x00320bd4 (est. sk_bounds_call_20bd4)
 * Computes the buffer range length and forwards to the apply-then-verify
 * helper. Confidence: low. Notes: unaff_x20 pair. */
void sk_bounds_call_20bd4(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t *src = NULL; /* = unaff_x20 */
    int64_t base = (int64_t)*src, len = 0;
    if (*src != 0) { len = (int64_t)src[1] - (int64_t)*src; }
    sk_apply_then_verify_20f20((uint64_t)base, (uint64_t)len, a, NULL, b, c, NULL);
}

/* FUN_00320c28 @ 0x00320c28 (est. sk_make_sub_20c28)
 * Runs the subscript on the buffer pair and stores the byte; returns a
 * closure pair with owner FUN_0001a1c8. Confidence: low.
 * Notes: unaff_x20 pair. */
cl4_result_t sk_make_sub_20c28(uint8_t *out, uint64_t *p)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    cl4_result_t res = {0,0};
    uint8_t t = sk_buf_subscript_212c4(*p, (int64_t)u1, (int64_t)u2);
    *out = t;
    res.hi = (uint64_t)out;
    res.lo = (uint64_t)FUN_0001a1c8;
    return res;
}

/* FUN_00320c8c @ 0x00320c8c (est. sk_store64_20c8c)
 * Resolves a 64-bit value and stores it at the preserved dest.
 * Confidence: low. Notes: dest=unaff_x19. */
void sk_store64_20c8c(void)
{
    uint64_t *dest = NULL; /* = unaff_x19 */
    FUN_00350258();
    *dest = FUN_001e6608();
}

/* FUN_00320ccc @ 0x00320ccc (est. sk_tls_call_20ccc)
 * Two TLS helper calls (0x359424 then 0x1e6b6c). Confidence: low. */
void sk_tls_call_20ccc(void) { FUN_00359424(); FUN_001e6b6c(); }

/* FUN_00320cd0 @ 0x00320cd0 (est. sk_tls_call_20cd0) — duplicate. */
void sk_tls_call_20cd0(void) { FUN_00359424(); FUN_001e6b6c(); }

/* FUN_00320cfc @ 0x00320cfc (est. sk_copy_checked_20cfc)
 * Checked element copy: validates the copy length against the destination
 * range, performs the copy, else fatal. Confidence: low.
 * Notes: uses SCARRY8 length check; fatal tail 0x1afe4c. */
void sk_copy_checked_20cfc(uint64_t a, int64_t n, uint64_t b, int64_t base, int64_t len, uint64_t c)
{
    cl4_result_t v = {0,0}; /* = FUN_003509c8(c) */
    int64_t l, dl;
    v.lo = FUN_003509c8(c);
    dl = (int64_t)v.hi;
    if (SCARRY8(dl, 0)) {
        /* WARNING: does not return */
        SK_TRAP(); /* SoftwareBreakpoint(1,0x320d80) */
    }
    l = 0;
    if (base != 0) { l = len - base; }
    if (l < dl + 0) {
        FUN_003488bc(1);
        FUN_00349644();
    } else {
        if (base != 0) {
            FUN_002bedcc(v.lo, dl, c);
            return;
        }
        FUN_00348898(1);
        FUN_00349644();
    }
    FUN_00351094();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_00320dbc @ 0x00320dbc (est. sk_raw_copy_20dbc)
 * Raw-pointer copy: resolves the count via a function pointer, validates the
 * destination range, then copies. Fatal on range violation (0x21d) or
 * negative pointer offset (0x603). Confidence: low.
 * Notes: fatal strings s_UnsafeMutableRawBufferPointer_co_005d1070 /
 * s_Swift_UnsafeRawPointer_swift_005cf1b0. */
void sk_raw_copy_20dbc(int64_t a, int64_t b, uint64_t c, int64_t base, int64_t len,
                       uint64_t d, uint64_t e, uint64_t f)
{
    sk_fn_t resolve = (sk_fn_t)FUN_00027788(f);
    int64_t n = (int64_t)resolve(e, f);
    int64_t l = 0;
    if (base != 0) { l = len - base; }
    if (l < n) {
        /* WARNING: does not return */
        FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2,
                     s_UnsafeMutableRawBufferPointer_co_005d1070, 0x44, 2,
                     s_Swift_UnsafeRawBufferPointer_swi_005cde40, 0x22, 2, 0x21d, 1);
    }
    if (a == 0) return;
    if (-1 < b) {
        FUN_00117d14(d, a, b);
        return;
    }
    /* WARNING: does not return */
    FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2, (uint64_t)FUN_005d0b20, 0x36, 2,
                 (uint64_t)s_Swift_UnsafeRawPointer_swift_005cf1b0, 0x1c, 2, 0x603, 1);
}

/* FUN_00320f20 @ 0x00320f20 (est. sk_apply_then_verify_20f20)
 * Applies a callback to a range, then either verifies the buffer identity
 * (null flag) or stores the preserved frame pointer into *out.
 * Confidence: low. Notes: unaff_x21 flag. */
void sk_apply_then_verify_20f20(uint64_t a, uint64_t b, uint64_t c, sk_fn_t fn,
                                uint64_t d, uint64_t e, int64_t *out)
{
    uint64_t flag = 0;  /* = unaff_x21 */
    uint64_t local_50 = b, uStack_48 = c;
    if (fn) fn((uint64_t)&local_50);
    if (flag == 0) {
        FUN_000839d8(a, 0, 1, e);
        sk_verify_buf_20fc8((int64_t)b, (int64_t)c, (int64_t *)&local_50);
    } else {
        sk_verify_buf_20fc8((int64_t)b, (int64_t)c, (int64_t *)&local_50);
        *out = (int64_t)flag;
    }
}

/* FUN_00320fc8 @ 0x00320fc8 (est. sk_verify_buf_20fc8)
 * Verifies a buffer's identity (base + length) matches the recorded range;
 * raises a fatal error on mismatch (0x41c). Confidence: low.
 * Notes: fatal string s_UnsafeMutableRawBufferPointer_wi_005d31e0. */
void sk_verify_buf_20fc8(int64_t base, int64_t len, int64_t *p)
{
    bool match = (base == 0) ? (*p == 0) : (base == *p);
    if (!match || len != p[1]) {
        /* WARNING: does not return */
        FUN_001afe4c(s_Fatal_error_005accd0, 0xb, 2,
                     s_UnsafeMutableRawBufferPointer_wi_005d31e0, 0x6a, 2,
                     s_Swift_UnsafeRawBufferPointer_swi_005cde40, 0x22, 2, 0x41c, 1);
    }
}


/* FUN_00321084 @ 0x00321084 (est. sk_read_byte_advance_21084)
 * Reads one byte from a buffer and advances the pointer; the returned value
 * packs the byte in bits 0-7 and a "more available" flag in bit 8. Traps if
 * the buffer is empty or the pointers are reversed. Confidence: low.
 * Notes: unaff_x20 = {base, end}; fatal codes 0x4f9/0x4fc. */
uint32_t sk_read_byte_advance_21084(void)
{
    uint64_t **ctx = NULL; /* = unaff_x20 */
    uint8_t *base = (uint8_t *)*ctx;
    uint8_t *end;
    uint32_t val;
    int more = 0;
    if (base != NULL) {
        end = (uint8_t *)ctx[1];
        if (end == NULL) {
            FUN_0035047c();
            FUN_003486b8(0x4f9);
            FUN_00349644();
            FUN_000dbde8();
            /* WARNING: does not return */
            FUN_001afe4c();
        }
        if (base != end) {
            if (end <= base) {
                FUN_0035047c();
                FUN_003486b8(0x4fc);
                FUN_00349644();
                FUN_000dbde8();
                FUN_001afe4c();
            }
            more = 0;
            val = (uint32_t)*base;
            *ctx = (uint64_t *)(base + 1);
            return val | (more << 8);
        }
    }
    val = 0;
    more = 1;
    return val | (more << 8);
}

/* FUN_00321100 @ 0x00321100 (est. sk_read_byte_210c8)
 * Reads a byte (as 16-bit) into *out via the advance helper.
 * Confidence: low. */
void sk_read_byte_210c8(uint16_t *out)
{
    uint32_t v = sk_read_byte_advance_21084();
    *out = (uint16_t)v;
}

/* FUN_0032113c @ 0x0032113c (est. sk_copy_partial_2113c)
 * Copies up to `n` bytes from [src, end) to `dst`, advancing src; returns the
 * (src, end) pair. Requires both ranges non-empty. Confidence: low. */
cl4_result_t sk_copy_partial_2113c(uint64_t a, int64_t n, uint64_t src, uint64_t end)
{
    int64_t l;
    cl4_result_t out = {0,0};
    if (src != 0 && end != 0 && (l = (int64_t)(end - src), src <= end && l != 0) && n != 0) {
        if (n <= l) { l = n; }
        FUN_002bf038(src, l, a);
        src = src + (uint64_t)l;
    }
    out.hi = end;
    out.lo = src;
    return out;
}

/* FUN_003211d8 @ 0x003211d8 (est. sk_apply3_211d8)
 * Applies a 4-argument callback to the context pair, stores the returned
 * 16-byte value, and returns the first context word. Confidence: low.
 * Notes: unaff_x20 pair. */
uint64_t sk_apply3_211d8(cl4_result_t *out, uint64_t a, uint64_t b, uint64_t c, uint64_t d, sk_fn_t fn)
{
    uint64_t u1 = 0; /* = unaff_x20 */
    cl4_result_t v = {0,0};
    u1 = 0;
    v.lo = (uint64_t)fn(a, b, u1, 0); v.hi = 0;
    *out = v;
    return u1;
}

/* FUN_00321218 @ 0x00321218 (est. sk_apply_cond_21218)
 * Computes the buffer range length and applies a 7-argument callback; on the
 * null-flag path performs the retain-into + completion. Confidence: low.
 * Notes: unaff_x20 pair, unaff_x21 flag. */
void sk_apply_cond_21218(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, sk_fn_t fn)
{
    uint64_t *src = NULL; /* = unaff_x20 */
    uint64_t flag = 0;    /* = unaff_x21 */
    int64_t base = (int64_t)*src, len = 0;
    uint64_t local_28 = 0;
    if (*src != 0) { len = (int64_t)src[1] - (int64_t)*src; }
    if (fn) fn(a, (uint64_t)base, (uint64_t)len, b, c, d, (uint64_t)&local_28);
    if (flag == 0) {
        FUN_0034bc94(a);
        FUN_000839d8();
    }
}

/* FUN_003212a4 @ 0x003212a4 (est. sk_count_range_212a4)
 * Returns a (0, length) pair; the 16-byte value is shifted left 64 (the
 * decompiler packs it oddly). Confidence: low. */
cl4_result_t sk_count_range_212a4(int64_t base, int64_t end)
{
    uint64_t l = 0;
    cl4_result_t out = {0,0};
    if (base != 0) { l = (uint64_t)(end - base); }
    out.hi = 0;
    out.lo = l;
    return out;
}

/* FUN_003212b8 @ 0x003212b8 (est. sk_cond_retain_212b8)
 * Forwarder to the subscript helper 0x3212c4. Confidence: low. */
void sk_cond_retain_212b8(void) { sk_buf_subscript_212c4(0, 0, 0); }

/* FUN_003212c4 @ 0x003212c4 (est. sk_buf_subscript_212c4)
 * Buffer subscript with bounds check: returns the byte at base+idx if idx is
 * in [0, end-base); otherwise traps (precondition). Confidence: low.
 * Notes: fatal tail 0x1afe4c. */
uint8_t sk_buf_subscript_212c4(uint64_t idx, int64_t base, int64_t len)
{
    if ((int64_t)idx < 0) {
        FUN_0034e424();
    } else {
        if (base != 0 && idx < (uint64_t)(len - base)) {
            return *(uint8_t *)(base + (int64_t)idx);
        }
        FUN_0034dab8();
    }
    FUN_003488d8();
    FUN_00349644();
    FUN_000dbde8();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_00321318 @ 0x00321318 (est. sk_cond_retain_21318)
 * Forwarder to the bounds-ensure helper 0x321324. Confidence: low. */
void sk_cond_retain_21318(void) { sk_bounds_ensure_21324(0, 0, 0, 0); }

/* FUN_00321324 @ 0x00321324 (est. sk_bounds_ensure_21324)
 * Buffer bounds precondition: requires idx in [0, end-base] (or base==0 with
 * count < 1); else traps. Confidence: low. */
void sk_bounds_ensure_21324(int64_t idx, int64_t n, int64_t base, int64_t len)
{
    if (idx < 0) {
        FUN_0034dab8();
    } else {
        if (base == 0) {
            if (n < 1) return;
        } else if (n <= len - base) {
            return;
        }
        FUN_0034def4();
    }
    FUN_003488d8();
    FUN_00349644();
    FUN_000dbde8();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_0032137c @ 0x0032137c (est. sk_store64_2137c)
 * Resolves a 64-bit value and stores it at the preserved dest.
 * Confidence: low. Notes: dest=unaff_x19. */
void sk_store64_2137c(void)
{
    uint64_t *dest = NULL; /* = unaff_x19 */
    FUN_00353510();
    *dest = FUN_001a0158();
}

/* FUN_003213a4 @ 0x003213a4 (est. sk_make_sub2_213a4)
 * Runs the subscript on the buffer pair, stores the byte, returns a closure
 * pair with owner FUN_0001a1c8. Confidence: low. Notes: unaff_x20 pair. */
cl4_result_t sk_make_sub2_213a4(uint8_t *out, uint64_t *p)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    cl4_result_t res = {0,0};
    uint8_t t = sk_buf_subscript_212c4(*p, (int64_t)u1, (int64_t)u2);
    *out = t;
    res.hi = (uint64_t)out;
    res.lo = (uint64_t)FUN_0001a1c8;
    return res;
}

/* FUN_00321408 @ 0x00321408 (est. sk_call2_21408)
 * Calls a callback with the context pair then the completion helper.
 * Confidence: low. Notes: unaff_x20 pair. */
void sk_call2_21408(void)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    sk_fn_t cb = NULL;       /* extraout_x9 */
    FUN_00352e84();
    if (cb) cb(0, 0, u1, u2);
    FUN_003554e0();
}

/* FUN_00321440 @ 0x00321440 (est. sk_count_21440)
 * Stores a (0, count) range pair into the preserved dest. Confidence: low.
 * Notes: dest=unaff_x19. */
void sk_count_21440(void)
{
    uint64_t *dest = NULL; /* = unaff_x19 */
    cl4_result_t v = sk_count_range_212a4(0, 0);
    FUN_00353510();
    dest[0] = 0;
    dest[1] = v.hi;
}

/* FUN_00321470 @ 0x00321470 (est. sk_extend_21470)
 * Computes an extended range and stores it at the preserved dest.
 * Confidence: low. Notes: dest=unaff_x19; unaff_x20 pair. */
void sk_extend_21470(void)
{
    uint64_t *dest = NULL; /* = unaff_x19 */
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    uint64_t v = FUN_00351124();
    *dest = FUN_001e762c(v, u1, u2);
}

/* FUN_0032149c @ 0x0032149c (est. sk_extend_in_2149c)
 * In-place extension of the range at *p. Confidence: low.
 * Notes: unaff_x20 pair. */
void sk_extend_in_2149c(uint64_t *p)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    *p = FUN_001e762c(*p, u1, u2);
}

/* FUN_003214cc @ 0x003214cc (est. sk_append_214cc)
 * Appends a range and stores at the preserved dest. Confidence: low.
 * Notes: dest=unaff_x19; unaff_x20 pair. */
void sk_append_214cc(void)
{
    uint64_t *dest = NULL; /* = unaff_x19 */
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    uint64_t v = FUN_00351124();
    *dest = FUN_001e6ff8(v, u1, u2);
}

/* FUN_003214f8 @ 0x003214f8 (est. sk_append_in_214f8)
 * In-place append to the range at *p. Confidence: low. Notes: unaff_x20. */
void sk_append_in_214f8(uint64_t *p)
{
    uint64_t u1 = 0, u2 = 0; /* = unaff_x20 pair */
    *p = FUN_001e6ff8(*p, u1, u2);
}

/* FUN_00321528 @ 0x00321528 (est. sk_fatal_chain_21528)
 * Fatal chain: prelude, helper 0x1e3968, finalizer. Confidence: low. */
void sk_fatal_chain_21528(void)
{
    FUN_0034c434();
    FUN_001e3968();
    FUN_0035272c();
}

/* FUN_0032156c @ 0x0032156c (est. sk_cond_retain_2156c)
 * Runs a callback; if the preserved frame pointer is nonzero runs the unwind
 * helper. Confidence: low. Notes: unaff_x21 flag. */
void sk_cond_retain_2156c(uint64_t a, uint64_t b, sk_fn_t fn)
{
    uint64_t flag = 0; /* = unaff_x21 */
    if (fn) fn();
    if (flag != 0) {
        FUN_00354720();
    }
}


/* FUN_003215b8 @ 0x003215b8 (est. sk_swift_retain_copy_215b8)
 * Large Swift-runtime retain/copy routine (sibling of 0x3202a0): performs a
 * multi-stage buffer retain / element-copy dance with a TLS task registry and
 * a destination-buffer pair, masking pointer-tag bits at each stage. Heavily
 * register-aliased by the decompiler; each extraout_x8_N / unaff_xNN / in_ZR
 * is a preserved-register artifact.
 * Confidence: low. Notes: string s__start__005d2d87; thunk 0x36b270;
 * fatal tail 0x1afe4c. */
void sk_swift_retain_copy_215b8(void)
{
    uint64_t unaff_x20 = 0, unaff_x22 = 0, unaff_x23 = 0, unaff_x25 = 0;
    uint64_t unaff_x26 = 0, unaff_x27 = 0, unaff_x28 = 0, unaff_x30 = 0;
    uint64_t extra0 = 0, extra1 = 0, extra2 = 0, extra3 = 0, extra4 = 0; /* extraout_x8_N */
    uint64_t in_x4 = 0;
    bool in_ZR = false, uVar3 = false;
    cl4_result_t r8 = {0,0}, r9 = {0,0};
    uint64_t stk08 = 0, stk10 = 0, stk18 = 0, stk20 = 0, stk28 = 0;
    uint64_t puVar4 = 0, puVar6 = 0, puVar7 = 0;
    uint64_t puVar2 = 0;
    uint64_t v, lVar1;

    FUN_0035193c();
    FUN_00354708();
    r8.lo = FUN_00355968();
    FUN_001a89a8(r8.lo, r8.hi, 1);
    FUN_00352c80();
    FUN_0006e778(0x16);
    r9.lo = FUN_0035a354();
    FUN_0035940c((uint64_t)s__start__005d2d87);
    FUN_00357b3c();
    FUN_0034b824(unaff_x28 & 0xffffffffffff);

    if (extra0 == 0 &&
        ((((uint64_t)unaff_x28 & ((uint64_t)unaff_x20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4();
        stk20 = unaff_x26;
        stk28 = unaff_x25;
    } else {
        unaff_x27 = (unaff_x25 >> 0x38 & 0xf);
        if (((unaff_x20 >> 0x3d & 1) == 0)) {
            FUN_00358840(unaff_x26 & 0xffffffffffff);
        } else if (((unaff_x25 >> 0x3d & 1) == 0)) {
            unaff_x27 = unaff_x26 & 0xffffffffffff;
        } else {
            FUN_00351e90();
            FUN_00352ea8();
            puVar4 = FUN_0034b7c8();
            if (!in_ZR) {
                FUN_003562f8();
                FUN_003a25d4();
                FUN_003a25d4();
                unaff_x28 = puVar4;
                stk20 = puVar4;
                stk28 = unaff_x20;
                goto L_21664;
            }
        }
        FUN_000a6e14();
        FUN_00354b98();
        FUN_002a4c98();
        FUN_003a25d4();
    }
L_21664:
    if (unaff_x22 == 0) {
        FUN_00353830();
        FUN_00355c78();
    } else {
        stk08 = 0;
        stk10 = 0xe000000000000000;
        stk18 = unaff_x22;
        FUN_00353d64();
        FUN_0034895c();
        FUN_00205844((uint64_t)&stk18, (uint64_t)&stk08, in_x4);
        in_x4 = stk10;
        unaff_x26 = stk08;
    }
    puVar4 = stk28;
    v = FUN_00349cbc(stk20);
    if (extra1 == 0 && (((v & ((uint64_t)puVar4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(puVar4);
        stk20 = unaff_x26;
        stk28 = in_x4;
    } else {
        unaff_x25 = (in_x4 >> 0x38 & 0xf);
        if (((puVar4 >> 0x3d & 1) == 0)) {
            FUN_0035946c();
            puVar7 = 0; /* extraout_x8_01 */
            if (!in_ZR) { puVar7 = unaff_x25; }
        } else if (((in_x4 >> 0x3d & 1) == 0)) {
            puVar7 = unaff_x26 & 0xffffffffffff;
        } else {
            FUN_00352d1c();
            puVar6 = FUN_0034b1a0();
            puVar7 = unaff_x25;
            if (!in_ZR) {
                FUN_003542c4();
                FUN_003a25d4();
                FUN_003a25d4(in_x4);
                unaff_x27 = puVar6;
                stk20 = puVar6;
                stk28 = unaff_x28;
                goto L_21704;
            }
        }
        thunk_FUN_0036b270(in_x4);
        puVar4 = (uint64_t)&stk20;
        FUN_0034ee38();
        FUN_002a4c98();
        FUN_003a2610(in_x4, 2);
        unaff_x25 = puVar7;
    }
L_21704:
    puVar6 = stk28;
    puVar7 = stk20;
    FUN_0035a8a8();
    FUN_00358d70();
    FUN_0034d044(puVar7 & 0xffffffffffff);
    if (extra2 == 0 &&
        ((((uint64_t)puVar7 & ((uint64_t)puVar6 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        r8.lo = (uint64_t)FUN_003a25d4(puVar6); r8.hi = 0;
        stk20 = unaff_x27;
        stk28 = unaff_x25;
    } else {
        if (((puVar6 >> 0x3d & 1) == 0)) {
            FUN_00351500(unaff_x27 & 0xffffffffffff);
        } else if (((unaff_x25 >> 0x3d & 1) != 0)) {
            FUN_00100c38();
            FUN_00353ef0();
            FUN_0034b7c8();
            if (!in_ZR) {
                FUN_0035351c();
                FUN_003a25d4(puVar6);
                r8.lo = (uint64_t)FUN_003a25d4(unaff_x25); r8.hi = 0;
                stk20 = puVar4;
                stk28 = puVar7;
                goto L_2176c;
            }
        }
        puVar4 = (uint64_t)&stk20;
        r8.lo = (uint64_t)FUN_003508f0(); r8.hi = 0;
        FUN_002a4c98(r8.lo, r8.hi, 0);
        r8.lo = (uint64_t)FUN_003a25d4(unaff_x25); r8.hi = 0;
    }
L_2176c:
    puVar2 = stk28;
    puVar7 = stk20;
    uVar3 = (unaff_x22 == 0);
    lVar1 = 0;
    if (!uVar3) { lVar1 = unaff_x23 - unaff_x22; }
    FUN_00356340(r8.lo, r8.hi, lVar1);
    FUN_002364dc();
    FUN_00351f28();
    FUN_0034de14(puVar7 & 0xffffffffffff);
    if (extra3 == 0 &&
        ((((uint64_t)puVar7 & ((uint64_t)puVar2 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(puVar2);
        stk20 = unaff_x23;
        stk28 = unaff_x22;
    } else {
        if (((puVar2 >> 0x3d & 1) == 0)) {
            FUN_0034a7ac();
        } else if (((unaff_x22 >> 0x3d & 1) != 0)) {
            FUN_003508f0();
            FUN_003497c8();
            if (!uVar3) {
                FUN_00355d6c();
                FUN_003a25d4(puVar2);
                FUN_003a25d4();
                stk20 = puVar4;
                stk28 = puVar6;
                goto L_217d8;
            }
        }
        FUN_0034c5bc();
        FUN_002a4c98();
        FUN_003a25d4();
    }
L_217d8:
    puVar7 = stk28;
    puVar4 = stk20;
    FUN_0034b178();
    FUN_001a89a8();
    FUN_00354ddc();
    FUN_0034a900();
    if (extra4 == 0 &&
        ((((uint64_t)puVar4 & ((uint64_t)puVar7 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(puVar7);
    } else {
        if (((puVar7 >> 0x3d & 1) == 0)) {
            FUN_0034e374(puVar2 & 0xffffffffffff);
        } else if (((puVar6 >> 0x3d & 1) != 0)) {
            FUN_0034d130();
            FUN_0034b1a0();
            if (!uVar3) {
                FUN_00350b90();
                FUN_003a25d4(puVar7);
                FUN_003a25d4(puVar6);
                FUN_0035a238();
                goto L_21848;
            }
        }
        FUN_0034f454();
        FUN_002a4c98();
        FUN_003a25d4(puVar6);
        puVar6 = stk28;
    }
L_21848:
    FUN_00084180();
    FUN_003516d8();
    FUN_001e3f70();
    FUN_0034bd90();
    FUN_003a25d4();
    FUN_003a25d4(puVar6);
    r8.lo = (uint64_t)FUN_0006b6f4(); r8.hi = 0;
    FUN_00351774(r8.lo, r8.hi, unaff_x30);
}

/* FUN_0032197c @ 0x0032197c (est. sk_cond_retain_2197c)
 * Forwarder to the trampoline 0x3219dc. Confidence: low. */
void sk_cond_retain_2197c(void) { sk_swift_trampoline_219dc(0,0,0,0,0); }

/* FUN_00321980 @ 0x00321980 (est. sk_cond_retain_21980) — duplicate. */
void sk_cond_retain_21980(void) { sk_swift_trampoline_219dc(0,0,0,0,0); }

/* FUN_003219ac @ 0x003219ac (est. sk_cond_retain_219ac) — duplicate. */
void sk_cond_retain_219ac(void) { sk_swift_trampoline_219dc(0,0,0,0,0); }

/* FUN_003219b0 @ 0x003219b0 (est. sk_cond_retain_219b0) — duplicate. */
void sk_cond_retain_219b0(void) { sk_swift_trampoline_219dc(0,0,0,0,0); }

/* FUN_003219dc @ 0x003219dc (est. sk_swift_trampoline_219dc)
 * Swift trampoline: captures five incoming values, runs the prelude and
 * range helpers, and invokes the traversal callback. Confidence: low. */
void sk_swift_trampoline_219dc(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t extra_x1 = 0, extra_x8 = 0;
    uint64_t local_58 = c;
    uint64_t local_70 = d, uStack_68 = e, local_60 = extra_x1;
    cl4_result_t v = {0,0}; /* = FUN_003498c4() */
    cl4_result_t out = {0,0};
    FUN_00356188();
    FUN_00356c84();
    FUN_0034a210();
    FUN_00002534();
    v.lo = FUN_003498c4();
    FUN_003512c0(extra_x8, v.lo, v.hi, (uint64_t)&out);
    FUN_002514f0();
}

/* FUN_00321a70 @ 0x00321a70 (est. sk_swift_iter_21a70)
 * Iterates an element range: if the count is nonnegative calls the iterator
 * closure on [base, base+count); else traps. Confidence: low.
 * Notes: count=*(ctx+0x40). */
void sk_swift_iter_21a70(void)
{
    int64_t ctx = 0; /* = extraout_x16 */
    cl4_result_t v = {0,0}; /* = FUN_0035a028() */
    sk_fn_t iter;
    v.lo = FUN_0035a028();
    if (-1 < *(int64_t *)(ctx + 0x40)) {
        iter = (sk_fn_t)v.hi;
        if (iter) iter(v.lo, v.lo + *(int64_t *)(ctx + 0x40));
        return;
    }
    FUN_00348284();
    FUN_00351094();
    /* WARNING: does not return */
    FUN_001afe4c();
}

/* FUN_00321ac8 @ 0x00321ac8 (est. sk_swift_dispatch_21ac8)
 * Swift dispatch helper: runs two closure callbacks (element copy + verify)
 * with a trailing error check; on the error flag branch performs the copy
 * else the fallback. Confidence: low. Notes: unaff_x19/x25/x26 offsets;
 * indirect callbacks via *(ctx+0x10)/(ctx+8). */
void sk_swift_dispatch_21ac8(void)
{
    int64_t ctx0 = 0, ctx1 = 0, ctx2 = 0; /* extraout_x16_N */
    int64_t unaff_x19 = 0, unaff_x25 = 0, unaff_x26 = 0;
    uint64_t in_x5 = 0, extra_x1 = 0, extra_x9 = 0;
    uint64_t stk28 = 0;
    sk_fn_t cbA = NULL, cbB = NULL;
    uint64_t r;
    FUN_0008e518();
    FUN_00350328();
    FUN_003515b4();
    FUN_003722e4();
    FUN_00348e18();
    DAT_00658c00(*(uint64_t *)(ctx0 + 0x40));
    FUN_00348abc();
    DAT_00658c00();
    FUN_0034b87c();
    FUN_0034b518();
    cbA = (sk_fn_t)(ctx1 + 0x10);
    if (cbA) cbA();
    FUN_0034c664();
    cbB = (sk_fn_t)(ctx2 + 0x10);
    if (cbB) cbB((uint64_t)(unaff_x26 + extra_x9), extra_x1, in_x5);
    if (cbA) cbA();
    FUN_003546fc(unaff_x25 + *(int32_t *)(unaff_x19 + 0x30));
    if (cbB) cbB();
    FUN_003559d8();
    FUN_0014ae44();
    FUN_0034c5dc();
    FUN_00350aac();
    r = FUN_00352980();
    if ((r & 1) != 0) {
        FUN_00354d08();
        FUN_00350adc();
        FUN_00351584(unaff_x26 + extra_x9, unaff_x25 + *(int32_t *)(unaff_x19 + 0x30));
    }
    cbA = (sk_fn_t)(ctx0 + 8);
    FUN_0035060c();
    if (cbA) cbA();
    FUN_003505e8();
    if (cbA) cbA();
    FUN_00352980();
    FUN_0008e500(r, stk28);
}

/* FUN_00321c68 @ 0x00321c68 (est. sk_swift_bool_21c68)
 * Returns the low bit of the dispatch2 helper result. Confidence: low. */
uint32_t sk_swift_bool_21c68(void)
{
    uint32_t r;
    sk_swift_dispatch2_21ca0();   /* Ghidra: uVar1 = FUN_00321ca0(); status in reg */
    r = 0;
    return r & 1;
}

/* FUN_00321ca0 @ 0x00321ca0 (est. sk_swift_dispatch2_21ca0)
 * Swift dispatch helper (sibling of 0x321ac8): runs two closures with an
 * error-checked branch between element copy and fallback. Confidence: low.
 * Notes: indirect callbacks via *(ctx+0x10); unaff_x19/x25/x26 offsets. */
void sk_swift_dispatch2_21ca0(void)
{
    int64_t ctx0 = 0, ctx1 = 0; /* extraout_x16_N */
    int64_t unaff_x19 = 0, unaff_x25 = 0, unaff_x26 = 0;
    uint64_t in_x3 = 0, in_x4 = 0, in_x5 = 0;
    sk_fn_t in_x7 = NULL;
    sk_fn_t cbA = NULL, cbB = NULL, cbX = NULL;
    cl4_result_t v = {0,0}; /* = FUN_00356ae8() */
    uint64_t stk18 = 0;
    sk_fn_t stk60 = NULL;
    uint64_t r, u3;
    FUN_0008e518();
    FUN_00350328();
    FUN_003515b4();
    FUN_003722e4();
    FUN_00348e18();
    DAT_00658c00(*(uint64_t *)(ctx0 + 0x40));
    FUN_00348abc();
    DAT_00658c00();
    FUN_0034b87c();
    FUN_0034b518();
    cbA = (sk_fn_t)(ctx0 + 0x10);
    if (cbA) cbA();
    FUN_0034d140();
    cbB = (sk_fn_t)(ctx1 + 0x10);
    if (cbB) cbB(unaff_x26 + 0, 0, in_x5);
    v.lo = FUN_00356ae8();
    if (cbA) cbA(v.lo, v.hi, in_x4);
    if (cbB) cbB(unaff_x25 + *(int32_t *)(unaff_x19 + 0x30), in_x3, in_x5);
    FUN_00353b94();
    FUN_0034c4fc();
    FUN_000a6e14();
    FUN_00351100();
    r = FUN_00352980();
    if ((r & 1) == 0) {
        if (stk60) stk60((uint64_t)cbB);
        FUN_0034c5dc();
        FUN_00351378();
        cbX = NULL; /* extraout_x8_02 */
    } else {
        u3 = (stk60) ? stk60((uint64_t)in_x7) : 0;
        FUN_0034e5fc(u3, unaff_x26 + 0, unaff_x25 + *(int32_t *)(unaff_x19 + 0x30));
        cbX = NULL; /* extraout_x8_01 */
        cbA = in_x7;
    }
    if (cbX) cbX();
    FUN_0035a640();
    FUN_0035060c();
    if (cbA) cbA();
    FUN_003505e8();
    if (cbA) cbA();
    FUN_00352980();
    FUN_0008e500(r, stk18);
}

/* FUN_00321e64 @ 0x00321e64 (est. sk_swift_dispatch3_21e64)
 * Swift dispatch helper with two element-range callbacks and an error-gated
 * branch. Confidence: low. Notes: unaff_x19/x24/x25 offsets; callbacks via
 * *(ctx+0x10)/(ctx+8). */
void sk_swift_dispatch3_21e64(void)
{
    int64_t ctx0 = 0, ctx1 = 0, ctx2 = 0; /* extraout_x16_N */
    int64_t unaff_x19 = 0, unaff_x24 = 0, unaff_x25 = 0;
    uint64_t stk08 = 0, local_38 = 0;
    uint64_t extra_x9 = 0, extra_x9_00 = 0;
    sk_fn_t cbA = NULL, cbB = NULL, cbC = NULL, cbX = NULL;
    uint64_t r;
    FUN_0008e518();
    FUN_0035448c();
    FUN_00348e18();
    DAT_00658c00(*(uint64_t *)(ctx0 + 0x40));
    FUN_00348a80();
    DAT_00658c00();
    FUN_0034b3d8();
    FUN_0034b518();
    cbA = (sk_fn_t)(ctx1 + 0x10);
    if (cbA) cbA();
    FUN_0034b3c8();
    cbB = (sk_fn_t)(ctx2 + 0x10);
    if (cbB) cbB(unaff_x25 + extra_x9);
    FUN_0034c664();
    cbC = (sk_fn_t)(ctx0 + 0x10);
    if (cbC) cbC(unaff_x25 + extra_x9_00, local_38);
    FUN_0035a36c();
    cbX = NULL; /* extraout_x8_00 */
    if (cbX) cbX();
    FUN_003599ac();
    if (cbB) cbB();
    FUN_00358b24(unaff_x24 + *(int32_t *)(unaff_x19 + 0x40));
    if (cbC) cbC();
    FUN_003585c4();
    FUN_0014ae44();
    FUN_0034bddc();
    FUN_00351378();
    r = FUN_00352980();
    if ((r & 1) != 0) {
        FUN_00355f4c();
        FUN_00298cb8();
    }
    cbB = (sk_fn_t)(ctx0 + 8);
    FUN_003514e8();
    if (cbB) cbB();
    FUN_0035060c();
    if (cbB) cbB();
    FUN_00352980();
    FUN_0008e500(r, stk08);
}

/* FUN_00322010 @ 0x00322010 (est. sk_swift_dispatch4_22010)
 * Dispatch helper identical to 0x321e64 except the error branch calls
 * 0x321ac8. Confidence: low. */
void sk_swift_dispatch4_22010(void)
{
    int64_t ctx0 = 0, ctx1 = 0, ctx2 = 0; /* extraout_x16_N */
    int64_t unaff_x19 = 0, unaff_x24 = 0, unaff_x25 = 0;
    uint64_t stk08 = 0, local_38 = 0;
    uint64_t extra_x9 = 0, extra_x9_00 = 0;
    sk_fn_t cbA = NULL, cbB = NULL, cbC = NULL, cbX = NULL;
    uint64_t r;
    FUN_0008e518();
    FUN_0035448c();
    FUN_00348e18();
    DAT_00658c00(*(uint64_t *)(ctx0 + 0x40));
    FUN_00348a80();
    DAT_00658c00();
    FUN_0034b3d8();
    FUN_0034b518();
    cbA = (sk_fn_t)(ctx1 + 0x10);
    if (cbA) cbA();
    FUN_0034b3c8();
    cbB = (sk_fn_t)(ctx2 + 0x10);
    if (cbB) cbB(unaff_x25 + extra_x9);
    FUN_0034c664();
    cbC = (sk_fn_t)(ctx0 + 0x10);
    if (cbC) cbC(unaff_x25 + extra_x9_00, local_38);
    FUN_0035a36c();
    cbX = NULL; /* extraout_x8_00 */
    if (cbX) cbX();
    FUN_003599ac();
    if (cbB) cbB();
    FUN_00358b24(unaff_x24 + *(int32_t *)(unaff_x19 + 0x40));
    if (cbC) cbC();
    FUN_003585c4();
    FUN_0014ae44();
    FUN_0034bddc();
    FUN_00351378();
    r = FUN_00352980();
    if ((r & 1) != 0) {
        FUN_00355f4c();
        sk_swift_dispatch_21ac8();
    }
    cbB = (sk_fn_t)(ctx0 + 8);
    FUN_003514e8();
    if (cbB) cbB();
    FUN_0035060c();
    if (cbB) cbB();
    FUN_00352980();
    FUN_0008e500(r, stk08);
}

/* FUN_003221bc @ 0x003221bc (est. sk_swift_bool_221bc)
 * Runs two helpers and returns the low bit of the second. Confidence: low. */
uint32_t sk_swift_bool_221bc(void)
{
    uint32_t r;
    FUN_00359b0c();
    r = (uint32_t)FUN_0035aad8();
    return r & 1;
}

/* FUN_0032220c @ 0x0032220c (est. sk_swift_dispatch5_2220c)
 * Ten-argument dispatch helper: forwards an id and several values into the
 * element-copy callbacks with an error-gated branch. Confidence: low.
 * Notes: unaff_x19/x23/x24 offsets; indirect callbacks via *(ctx+0x10);
 * stack callback pair in_stack_00000080/88. */
void sk_swift_dispatch5_2220c(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e,
                              uint64_t f, uint64_t g, uint64_t h, uint64_t i, uint64_t j)
{
    int64_t ctx0 = 0, ctx1 = 0, ctx2 = 0; /* extraout_x16_N */
    int64_t unaff_x19 = 0, unaff_x23 = 0, unaff_x24 = 0;
    uint64_t extra_x9 = 0, extra_x9_00 = 0;
    uint64_t stk60 = 0, stk68 = 0, stk70 = 0, stk78 = 0;
    sk_fn_t cbA = NULL, cbB = NULL, cbC = NULL, cbX = NULL;
    sk_fn_t stk80 = NULL, stk88 = NULL;
    cl4_result_t v = {0,0}; /* = FUN_00355d10() */
    uint64_t r;
    FUN_0008e518();
    v.lo = FUN_00355d10();
    FUN_0037233c(v.lo, v.hi, h, stk60, 0, 0);
    FUN_00348e18();
    DAT_00658c00(*(uint64_t *)(ctx0 + 0x40));
    FUN_00348bbc();
    DAT_00658c00();
    FUN_0034b8bc();
    FUN_0034b518();
    cbA = (sk_fn_t)(ctx1 + 0x10);
    if (cbA) cbA();
    FUN_0034b3c8();
    cbB = (sk_fn_t)(ctx2 + 0x10);
    if (cbB) cbB(unaff_x24 + extra_x9, 0, h);
    FUN_0034dae8();
    cbC = (sk_fn_t)(ctx0 + 0x10);
    if (cbC) cbC(unaff_x24 + extra_x9_00, c, stk60);
    if (cbA) cbA((uint64_t)(ctx1 + 0x10));
    if (cbB) cbB(unaff_x23 + *(int32_t *)(unaff_x19 + 0x30), e, h);
    if (cbC) cbC(unaff_x23 + *(int32_t *)(unaff_x19 + 0x40), f, stk60);
    FUN_00351bec(stk68);
    FUN_0014ae44();
    FUN_0034ca08();
    FUN_00352e60();
    r = FUN_00352980();
    if ((r & 1) == 0) {
        if (stk80) stk80(stk68);
        FUN_0034ca08();
        FUN_00351100();
        cbX = NULL; /* extraout_x8_01 */
    } else {
        if (stk88) stk88(unaff_x24 + extra_x9, unaff_x24 + extra_x9_00,
                         unaff_x23 + *(int32_t *)(unaff_x19 + 0x30),
                         unaff_x23 + *(int32_t *)(unaff_x19 + 0x40),
                         h, stk60, stk70, stk78);
    }
    cbB = (sk_fn_t)(ctx0 + 8);
    FUN_00350524();
    if (cbB) cbB();
    FUN_003514e8();
    if (cbB) cbB();
    FUN_00352980();
    FUN_0008e500(r, j);
}

/* FUN_00322450 @ 0x00322450 (est. sk_swift_bool_22450)
 * Runs two helpers and returns the low bit of the second. Confidence: low. */
uint32_t sk_swift_bool_22450(void)
{
    uint32_t r;
    FUN_00359b0c();
    r = (uint32_t)FUN_0035aad8();
    return r & 1;
}

