/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x0005acac-0x0005fd24 (worker SK11): the cL4 "xrt" thread-runtime /
 * panic-reporting / IPC message-register / sync / timebase / error-code layer:
 * per-CPU state getters, thread registry accessors, message-register and
 * capability-register bounds-checked accessors, the panic-backtrace and
 * error-code string formatting, the commpage/trace support, and the sync
 * (mutex/semaphore) primitives.
 *
 * Function C identifiers are address-based (sk_f_<addr>) so the 120 functions
 * of this slice call one another deterministically regardless of definition
 * order; descriptive estimated names live in the per-function comments and in
 * docs/sptm/manifest.json.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"
#include <stdarg.h>

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
#define DC_GVA(a) __asm__ volatile("dc cvau, %0" : : "r"((uint64_t)(a)))
#define GENTER() __asm__ volatile(".inst 0x00201420")
#define GEXIT()  __asm__ volatile(".inst 0x00201400")
static inline void sk_callsup(uint64_t kind)
{ __asm__ volatile("svc %0" : : "i"(0)); (void)kind; }
#define CallSupervisor(k) sk_callsup((uint64_t)(k))
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))
#define DataMemoryBarrier(a,b) __asm__ volatile("dmb %0" : : "i"((a)))
#define DataSynchronizationBarrier(a,b) __asm__ volatile("dsb %0" : : "i"((a)))
#define InstructionSynchronizationBarrier() __asm__ volatile("isb")
#define MemoryBarrier() __asm__ volatile("dmb sy")
#define LOAcquire()  __asm__ volatile("dmb ishld")
#define LORelease()  __asm__ volatile("dmb ish")
#define SK_CANARY (-0x2c8502b44bfffed6LL)

static uint8_t sk_tpidr_area[0x100] __attribute__((aligned(16)));
#define tpidr_el0    ((uint8_t *)sk_tpidr_area)
#define tpidrro_el0  ((uint8_t *)sk_tpidr_area)

/* External callees (outside this slice). Address-based names; each
 * declared `unsigned long` (64-bit ABI word) so any call site compiles.
 * Ghidra FUN_ address is ground truth. 0019AE9C returns a 16-byte pair. */
typedef struct { uint64_t lo; uint64_t hi; } sk_u128_t;

extern unsigned long sk_x_0000178C();   /* FUN_0000178C */
extern unsigned long sk_x_0000178c();   /* FUN_0000178C */
extern sk_u128_t sk_x_00034A2C();   /* FUN_00034A2C (16-byte pair) */
extern unsigned long sk_x_00034F70();   /* FUN_00034F70 */
extern unsigned long sk_x_0004BA18();   /* FUN_0004BA18 */
extern unsigned long sk_x_000533EC();   /* FUN_000533EC */
extern unsigned long sk_x_00053444();   /* FUN_00053444 */
extern unsigned long sk_x_000538C8();   /* FUN_000538C8 */
extern unsigned long sk_x_00054354();   /* FUN_00054354 */
extern unsigned long sk_x_00054610();   /* FUN_00054610 */
extern unsigned long sk_x_00054C9C();   /* FUN_00054C9C */
extern unsigned long sk_x_00054DE4();   /* FUN_00054DE4 */
extern unsigned long sk_x_000552C0();   /* FUN_000552C0 */
extern unsigned long sk_x_00055AFC();   /* FUN_00055AFC */
extern unsigned long sk_x_00055B20();   /* FUN_00055B20 */
extern unsigned long sk_x_0005FDAC();   /* FUN_0005FDAC */
extern unsigned long sk_x_000600F0();   /* FUN_000600F0 */
extern unsigned long sk_x_000603AC();   /* FUN_000603AC */
extern unsigned long sk_x_000603C4();   /* FUN_000603C4 */
extern unsigned long sk_x_000604FC();   /* FUN_000604FC */
extern unsigned long sk_x_00060524();   /* FUN_00060524 */
extern unsigned long sk_x_00060540();   /* FUN_00060540 */
extern unsigned long sk_x_0006054c();   /* FUN_0006054C */
extern unsigned long sk_x_00060570();   /* FUN_00060570 */
extern unsigned long sk_x_000605F8();   /* FUN_000605F8 */
extern unsigned long sk_x_000605f8();   /* FUN_000605F8 */
extern unsigned long sk_x_00060650();   /* FUN_00060650 */
extern unsigned long sk_x_000606B0();   /* FUN_000606B0 */
extern unsigned long sk_x_00061044();   /* FUN_00061044 */
extern unsigned long sk_x_000612D8();   /* FUN_000612D8 */
extern unsigned long sk_x_000612E0();   /* FUN_000612E0 */
extern unsigned long sk_x_0006132C();   /* FUN_0006132C */
extern unsigned long sk_x_000613EC();   /* FUN_000613EC */
extern unsigned long sk_x_00061488();   /* FUN_00061488 */
extern unsigned long sk_x_000614F8();   /* FUN_000614F8 */
extern unsigned long sk_x_0006156C();   /* FUN_0006156C */
extern unsigned long sk_x_000615FC();   /* FUN_000615FC */
extern unsigned long sk_x_00061630();   /* FUN_00061630 */
extern unsigned long sk_x_00061638();   /* FUN_00061638 */
extern unsigned long sk_x_000618CC();   /* FUN_000618CC */
extern unsigned long sk_x_0006198C();   /* FUN_0006198C */
extern unsigned long sk_x_000619C8();   /* FUN_000619C8 */
extern unsigned long sk_x_00062474();   /* FUN_00062474 */
extern unsigned long sk_x_00063910();   /* FUN_00063910 */
extern unsigned long sk_x_00063970();   /* FUN_00063970 */
extern unsigned long sk_x_00063A50();   /* FUN_00063A50 */
extern unsigned long sk_x_00063CFC();   /* FUN_00063CFC */
extern unsigned long sk_x_00063DD4();   /* FUN_00063DD4 */
extern unsigned long sk_x_00063FFC();   /* FUN_00063FFC */
extern unsigned long sk_x_0006402C();   /* FUN_0006402C */
extern unsigned long sk_x_00064108();   /* FUN_00064108 */
extern unsigned long sk_x_00064C24();   /* FUN_00064C24 */
extern unsigned long sk_x_0006562C();   /* FUN_0006562C */
extern unsigned long sk_x_00114330();   /* FUN_00114330 */
extern unsigned long sk_x_001143A0();   /* FUN_001143A0 */
extern unsigned long sk_x_001144A0();   /* FUN_001144A0 */
extern unsigned long sk_x_00115080();   /* FUN_00115080 */
extern unsigned long sk_x_001150E0();   /* FUN_001150E0 */
extern unsigned long sk_x_00116BB4();   /* FUN_00116BB4 */
extern unsigned long sk_x_00116BCC();   /* FUN_00116BCC */
extern unsigned long sk_x_00117CC4();   /* FUN_00117CC4 */
extern unsigned long sk_x_00117CC8();   /* FUN_00117CC8 */
extern unsigned long sk_x_00117cc4();   /* FUN_00117CC4 */
extern unsigned long sk_x_001185EC();   /* FUN_001185EC */
extern unsigned long sk_x_0011883C();   /* FUN_0011883C */
extern unsigned long sk_x_00118ABC();   /* FUN_00118ABC */
extern unsigned long sk_x_00118B28();   /* FUN_00118B28 */
extern unsigned long sk_x_00118C38();   /* FUN_00118C38 */
extern __attribute__((noreturn)) unsigned long sk_x_0011D7E8();   /* FUN_0011D7E8 */
extern unsigned long sk_x_0019AE2C();   /* FUN_0019AE2C */
extern unsigned long sk_x_0019AE60();   /* FUN_0019AE60 */
extern sk_u128_t sk_x_0019AE9C();   /* FUN_0019AE9C (16-byte) */
extern unsigned long sk_x_0019AF14();   /* FUN_0019AF14 */
extern unsigned long sk_x_0019AF88();   /* FUN_0019AF88 */
extern unsigned long sk_x_0019AFB0();   /* FUN_0019AFB0 */
extern unsigned long sk_x_0019AFBC();   /* FUN_0019AFBC */
extern unsigned long sk_x_004B23D8();   /* FUN_004B23D8 */
extern unsigned long sk_x_004B5FB8();   /* FUN_004B5FB8 */
extern unsigned long sk_x_004B6194();   /* FUN_004B6194 */
extern unsigned long sk_x_004B63CC();   /* FUN_004B63CC */
extern unsigned long sk_x_004B6430();   /* FUN_004B6430 */
extern unsigned long sk_x_004B6864();   /* FUN_004B6864 */
extern unsigned long sk_x_004B68A4();   /* FUN_004B68A4 */
extern unsigned long sk_x_004B6938();   /* FUN_004B6938 */
extern unsigned long sk_x_004B6984();   /* FUN_004B6984 */
extern unsigned long sk_x_004B69D0();   /* FUN_004B69D0 */
extern unsigned long sk_x_004B6D60();   /* FUN_004B6D60 */
extern unsigned long sk_x_004B6E24();   /* FUN_004B6E24 */
extern unsigned long sk_x_004B6E74();   /* FUN_004B6E74 */
extern unsigned long sk_x_004B6E88();   /* FUN_004B6E88 */
extern unsigned long sk_x_004B6E9C();   /* FUN_004B6E9C */
extern unsigned long sk_x_004B6ED0();   /* FUN_004B6ED0 */
extern unsigned long sk_x_004B6F20();   /* FUN_004B6F20 */
extern unsigned long sk_x_004B6F48();   /* FUN_004B6F48 */
extern unsigned long sk_x_004b23d8();   /* FUN_004B23D8 */
extern unsigned long sk_x_004b6c04();   /* FUN_004B6C04 */
extern unsigned long sk_x_004b6c50();   /* FUN_004B6C50 */
extern unsigned long sk_x_004b6c9c();   /* FUN_004B6C9C */

/* Image-base data globals referenced by this slice (Ghidra DAT_ ground truth). */
extern const uint8_t sk_g_0005d130[];   /* DAT_0005D130 */
extern uint64_t sk_g_004bb1a0;   /* DAT_004BB1A0 */
extern uint64_t sk_g_004bb1a8;   /* DAT_004BB1A8 */
extern uint64_t sk_g_004be030;   /* DAT_004BE030 */
extern uint64_t sk_g_004be038;   /* DAT_004BE038 */
extern const uint8_t sk_g_004be180[0x20];   /* DAT_004BE180 */
extern uint64_t sk_g_004be1a0;   /* DAT_004BE1A0 */
extern uint64_t sk_g_004be1a8;   /* DAT_004BE1A8 */
extern uint64_t sk_g_004be2f0;   /* DAT_004BE2F0 */
extern const uint8_t sk_g_005bc4d6[];   /* DAT_005BC4D6 */
extern const uint8_t sk_g_005bc4e9[];   /* DAT_005BC4E9 */
extern uint64_t sk_g_0064DB50;   /* DAT_0064DB50 */
extern const uint8_t sk_g_0064cb40[];   /* DAT_0064CB40 */
extern const uint8_t sk_g_0064cb48[];   /* DAT_0064CB48 */
extern const uint8_t sk_g_0064cb80[];   /* DAT_0064CB80 */
extern uint64_t sk_g_0064db58;   /* DAT_0064DB58 */
extern uint64_t sk_g_00689e9c;   /* DAT_00689E9C */
extern uint64_t sk_g_006B2560;   /* DAT_006B2560 */
extern uint64_t sk_g_006ad6e8;   /* DAT_006AD6E8 */
extern uint64_t sk_g_006ad900;   /* DAT_006AD900 */
extern uint64_t sk_g_006b04c0;   /* DAT_006B04C0 */
extern uint64_t sk_g_006b2688;   /* DAT_006B2688 */
extern uint64_t sk_g_006b2690;   /* DAT_006B2690 */
extern uint64_t sk_g_006b26a0;   /* DAT_006B26A0 */
extern uint64_t sk_g_006b26a4;   /* DAT_006B26A4 */
extern uint64_t sk_g_006b26a8;   /* DAT_006B26A8 */
extern uint64_t sk_g_006b26ac;   /* DAT_006B26AC */
extern uint64_t sk_g_006b26b0;   /* DAT_006B26B0 */
extern uint64_t sk_g_006b26b4;   /* DAT_006B26B4 */
extern uint64_t sk_g_006b26b8;   /* DAT_006B26B8 */
extern uint64_t sk_g_006b26bc;   /* DAT_006B26BC */

/* String literals referenced by this slice (Ghidra s_* names in comments). */
extern const char sk_str_004be040[];   /* s_..._004BE040 */
extern const char sk_str_004be060[];   /* s_..._004BE060 */
extern const char sk_str_004be080[];   /* s_..._004BE080 */
extern const char sk_str_004be0a0[];   /* s_..._004BE0A0 */
extern const char sk_str_004be0c0[];   /* s_..._004BE0C0 */
extern const char sk_str_004be0e0[];   /* s_..._004BE0E0 */
extern const char sk_str_004be100[];   /* s_..._004BE100 */
extern const char sk_str_004be120[];   /* s_..._004BE120 */
extern const char sk_str_004be140[];   /* s_..._004BE140 */
extern const char sk_str_004be160[];   /* s_..._004BE160 */
extern const char sk_str_004be1b0[];   /* s_..._004BE1B0 */
extern const char sk_str_004be1d0[];   /* s_..._004BE1D0 */
extern const char sk_str_004be1f0[];   /* s_..._004BE1F0 */
extern const char sk_str_004be210[];   /* s_..._004BE210 */
extern const char sk_str_004be230[];   /* s_..._004BE230 */
extern const char sk_str_004be250[];   /* s_..._004BE250 */
extern const char sk_str_004be270[];   /* s_..._004BE270 */
extern const char sk_str_004be290[];   /* s_..._004BE290 */
extern const char sk_str_004be2b0[];   /* s_..._004BE2B0 */
extern const char sk_str_004be2d0[];   /* s_..._004BE2D0 */
extern const char sk_str_005a8b30[];   /* s_..._005A8B30 */
extern const char sk_str_005a8c7b[];   /* s_..._005A8C7B */
extern const char sk_str_005bba0f[];   /* s_..._005BBA0F */
extern const char sk_str_005bc16c[];   /* s_..._005BC16C */
extern const char sk_str_005bc367[];   /* s_..._005BC367 */
extern const char sk_str_005bc391[];   /* s_..._005BC391 */
extern const char sk_str_005bc3bf[];   /* s_..._005BC3BF */
extern const char sk_str_005bc3d6[];   /* s_..._005BC3D6 */
extern const char sk_str_005bc486[];   /* s_..._005BC486 */
extern const char sk_str_005bc4b5[];   /* s_..._005BC4B5 */
extern const char sk_str_005bc4d9[];   /* s_..._005BC4D9 */
extern const char sk_str_005bc4ee[];   /* s_..._005BC4EE */
extern const char sk_str_005bc4f6[];   /* s_..._005BC4F6 */
extern const char sk_str_005bc520[];   /* s_..._005BC520 */
extern const char sk_str_005bc54e[];   /* s_..._005BC54E */
extern const char sk_str_005bc559[];   /* s_..._005BC559 */
extern const char sk_str_005bc6c6[];   /* s_..._005BC6C6 */
extern const char sk_str_005bc6d7[];   /* s_..._005BC6D7 */
extern const char sk_str_005bc719[];   /* s_..._005BC719 */
extern const char sk_str_005bc73c[];   /* s_..._005BC73C */
extern const char sk_str_005bc8ca[];   /* s_..._005BC8CA */
extern const char sk_str_005bc8f1[];   /* s_..._005BC8F1 */
extern const char sk_str_005bc90e[];   /* s_..._005BC90E */
extern const char sk_str_005bcac1[];   /* s_..._005BCAC1 */
extern const char sk_str_005bcb30[];   /* s_..._005BCB30 */
extern const char sk_str_005bcb5b[];   /* s_..._005BCB5B */
extern const char sk_str_005bcb91[];   /* s_..._005BCB91 */
extern const char sk_str_005bcbb9[];   /* s_..._005BCBB9 */
extern const char sk_str_005bcbd6[];   /* s_..._005BCBD6 */
extern const char sk_str_005bcbef[];   /* s_..._005BCBEF */
extern const char sk_str_005bcc0e[];   /* s_..._005BCC0E */
extern const char sk_str_005bcc3d[];   /* s_..._005BCC3D */
extern const char sk_str_005bcc65[];   /* s_..._005BCC65 */
extern const char sk_str_005bcc8c[];   /* s_..._005BCC8C */
extern const char sk_str_005bcca6[];   /* s_..._005BCCA6 */
extern const char sk_str_005bccc1[];   /* s_..._005BCCC1 */
extern const char sk_str_005bccde[];   /* s_..._005BCCDE */
extern const char sk_str_005bccf6[];   /* s_..._005BCCF6 */
extern const char sk_str_005bcd0e[];   /* s_..._005BCD0E */
extern const char sk_str_005bcd2c[];   /* s_..._005BCD2C */
extern const char sk_str_005bcd44[];   /* s_..._005BCD44 */
extern const char sk_str_005bcd56[];   /* s_..._005BCD56 */
extern const char sk_str_005bcdd0[];   /* s_..._005BCDD0 */
extern const char sk_str_005bce00[];   /* s_..._005BCE00 */
extern const char sk_str_005bce30[];   /* s_..._005BCE30 */
extern const char sk_str_005bce60[];   /* s_..._005BCE60 */
extern const char sk_str_005bce90[];   /* s_..._005BCE90 */
extern const char sk_str_005bcebc[];   /* s_..._005BCEBC */
extern const char sk_str_005bd02d[];   /* s_..._005BD02D */
extern const char sk_str_005bd169[];   /* s_..._005BD169 */
extern const char sk_str_005bd182[];   /* s_..._005BD182 */
extern const char sk_str_005bd1af[];   /* s_..._005BD1AF */
extern const char sk_str_00689ea0[];   /* s_..._00689EA0 */


/* Forward declarations (full prototypes, all 120 slice functions). */
uint64_t sk_f_0005acac(uint64_t slot_addr, uint64_t arg2, uint64_t arg3);
uint64_t sk_f_0005ace4(void);
uint64_t sk_f_0005ad24(void);
void sk_f_0005ad40(void);
void sk_f_0005ad58(int64_t trace);
void sk_f_0005ae4c(uint64_t thread_name, int64_t locks, uint64_t unused_arg, int32_t acquire);
void sk_f_0005afe8(int64_t obj, uint64_t arg2, uint64_t arg3);
void sk_f_0005b05c(int64_t obj, uint64_t arg2);
void sk_f_0005b0bc(int64_t obj);
void sk_f_0005b120(uint64_t slot);
void sk_f_0005b12c(uint64_t param);
void sk_f_0005b140(void);
uint64_t sk_f_0005b160(void);
void __attribute__((noreturn)) sk_f_0005b190(uint64_t thread, const char *reason);
void sk_f_0005b1b0(uint64_t thread, const char *reason, uint64_t arg3);
void sk_f_0005b824(uint64_t a, uint64_t b, uint64_t c, const char *d);
uint64_t sk_f_0005b860(uint64_t *out_name);
uint64_t sk_f_0005b89c(void);
uint32_t sk_f_0005b8c8(void);
uint64_t sk_f_0005ba14(void);
void sk_f_0005ba40(uint64_t arg);
void sk_f_0005ba5c(uint64_t *entry);
int64_t sk_f_0005baac(int key1, int key2);
void sk_f_0005baf0(uint64_t *entry);
uint64_t sk_f_0005bb68(void);
uint64_t sk_f_0005bbd8(uint8_t *thread, int64_t *out_size);
int sk_f_0005bc48(uint64_t *value_ptr, int32_t mode);
void sk_f_0005bce0(uint8_t *callback_slot);
void sk_f_0005bd10(uint64_t *node);
void sk_f_0005bd7c(void (*callback)(uint64_t), uint64_t callback_arg);
void sk_f_0005be48(uint64_t arg, uint64_t fn);
void sk_f_0005be84(uint64_t *node, int32_t mode);
void sk_f_0005bf20(uint64_t *node);
uint64_t sk_f_0005c0ac(void);
void sk_f_0005c16c(void);
uint64_t sk_f_0005c184(uint64_t src, uint64_t count);
uint64_t sk_f_0005c278(uint64_t dst, uint64_t count);
unsigned long sk_f_0005c380(const uint8_t *b, uint64_t *lo, uint64_t *hi);
unsigned long sk_f_0005c414(const uint8_t *b, uint64_t *acc);
unsigned long sk_f_0005c440(const uint8_t *b, uint16_t *w16, uint32_t *w32);
unsigned long sk_f_0005c468(const uint8_t *b, uint32_t *out);
unsigned long sk_f_0005c490(const uint8_t *b, uint64_t *acc);
unsigned long sk_f_0005c4a8(const uint8_t *b, uint32_t *acc);
unsigned long sk_f_0005c4c0(const uint8_t *b, uint64_t *lo, uint64_t *hi);
unsigned long sk_f_0005c510(void);
unsigned long sk_f_0005c520(void);
unsigned long sk_f_0005c53c(uint64_t selector);
unsigned long sk_f_0005c558(void);
unsigned long sk_f_0005c570(void);
void sk_f_0005c588(void);
unsigned long sk_f_0005c5a0(uint64_t sel_hi);
int64_t sk_f_0005c5b4(uint64_t arg);
void sk_f_0005c614(uint64_t arg);
void sk_f_0005c650(uint64_t *out, uint64_t timebase_id);
void sk_f_0005c710(void);
void sk_f_0005c764(uint64_t timebase_id, uint8_t *entry);
int64_t sk_f_0005c86c(uint64_t timebase_id, uint8_t (*target)[16], uint8_t (*out)[16],
                      uint64_t flags);
int64_t sk_f_0005c924(uint64_t timebase_id);
uint64_t sk_f_0005ca20(uint32_t timebase_id);
void sk_f_0005cb18(uint8_t value);
void sk_f_0005cb24(uint64_t token, uint64_t dividend, uint8_t (*out)[16], uint64_t flags);
uint64_t sk_f_0005cb9c(uint64_t *lock);
uint64_t sk_f_0005cc3c(uint64_t *lock, uint64_t arg2);
uint64_t sk_f_0005cdbc(uint64_t *lock);
void sk_f_0005ce54(uint64_t *lock);
void sk_f_0005cf08(uint64_t *lock, uint16_t mode);
unsigned long sk_f_0005cf14(void);
void sk_f_0005cf18(int64_t sp, uint64_t arg2, uint64_t arg3);
void sk_f_0005cf4c(int64_t target, uint64_t flags);
void sk_f_0005d03c(int64_t *slot, uint64_t flags);
uint64_t sk_f_0005d134(int64_t obj);
uint64_t sk_f_0005d154(int64_t object, int64_t *out_id);
uint16_t sk_f_0005d38c(uint64_t *queue, uint64_t queue_token);
void sk_f_0005d394(uint64_t *queue, int32_t clamp_to_capacity);
void sk_f_0005d470(uint32_t *slot, void (*completion)(void *), void *callback_arg);
void sk_f_0005d5dc(void);
void sk_f_0005d5e8(uint64_t target_thread, uint32_t register_num, uint64_t msg_lo,
                   uint64_t msg_hi);
uint64_t sk_f_0005d64c(int64_t target_thread, uint16_t config_word, uint64_t *msg_payload,
                   uint64_t flags);
uint64_t sk_f_0005d77c(void);
void sk_f_0005d7c8(int64_t *root_slot);
void sk_f_0005d84c(void);
void sk_f_0005d870(int64_t thread, int32_t reporting_enabled);
uint64_t sk_f_0005dab8(uint64_t (*handler)(int64_t, uint64_t), uint64_t target_thread,
                       uint8_t *cross_thread_flag, uint64_t arg);
void sk_f_0005db7c(uint64_t *thread);
uint64_t sk_f_0005dc4c(uint64_t cpu_index);
uint64_t sk_f_0005dc8c(uint64_t selector, uint64_t arg1, uint64_t arg2,
                       uint64_t arg3, uint64_t arg4);
void sk_f_0005dcb0(uint32_t selector, uint64_t msg0, uint64_t msg1, uint64_t thread, uint32_t flags);
void sk_f_0005dd70(uint64_t selector, uint64_t arg1, uint64_t arg2, uint64_t arg3);
void sk_f_0005dd94(uint32_t wake_idx, uint64_t msg0, uint32_t selector, uint64_t target_thread);
void sk_f_0005deb4(void);
void sk_f_0005ded8(uint64_t thread);
void sk_f_0005df34(uint32_t selector);
cl4_result_t sk_f_0005dfa8(uint64_t tag, uint16_t *msg);
void sk_f_0005e0dc(void);
void sk_f_0005e100(uint64_t cap_arg, uint8_t *selbuf);
void sk_f_0005e4ac(uint8_t error_code);
void sk_f_0005e4cc(void);
void sk_f_0005e4d8(int64_t thread, uint64_t out_lo, uint64_t out_hi, uint64_t flags);
void sk_f_0005e8a4(uint64_t *out, uint64_t mode, const char *fmt);
uint64_t sk_f_0005e958(uint32_t name);
int64_t sk_f_0005ea94(uint64_t src, uint64_t size, uint64_t offset, uint32_t nul_flag);
int64_t sk_f_0005eb78(uint64_t dst, uint64_t size, uint64_t offset);
void sk_f_0005ec20(uint32_t index, uint64_t value);
uint64_t sk_f_0005ec98(uint32_t index);
void sk_f_0005ed18(uint32_t index, uint64_t value);
void sk_f_0005edac(uint32_t index, uint64_t value);
uint64_t sk_f_0005ee40(uint64_t value);
uint64_t sk_f_0005ee48(uint64_t word);
uint64_t sk_f_0005ee50(uint64_t word);
uint64_t sk_f_0005ee58(uint64_t low_field, uint64_t mid_field, uint32_t high_field, int32_t enabled);
void sk_f_0005ee7c(void);
void sk_f_0005eec4(uint64_t *out_tcb, uint64_t creator, uint64_t entry_arg, int64_t stack_extra,
                   int32_t flags);
void sk_f_0005fac0(int64_t thread);
void sk_f_0005fad8(uint64_t wake_value);
void sk_f_0005fbc0(int64_t thread);
void sk_f_0005fbdc(uint64_t dest, uint64_t value, int64_t cap_count);
void sk_f_0005fc54(uint64_t dest, uint64_t *value_ptr, uint64_t cap_count);
void sk_f_0005fccc(int64_t thread);
void sk_f_0005fd24(int64_t thread);


/* FUN_0005acac @ 0x0005acac   (est. lazy_init_global_slot)
 * Ghidra: void FUN_0005acac(long *param_1,undefined8 param_2,undefined8 param_3)
 * Lazily initializes the global slot pointed to by `slot`: if it is still NULL, it is
 * filled by invoking sk_f_0005baac(param2, param3).  Because param_1 is passed in x0 and
 * x0 is not clobbered, the caller-visible ABI result is the (now initialized) slot pointer,
 * which callers read back as the return value.
 * Confidence: medium
 * Notes: Ghidra header shows void, but callers (0005afe8/0005b05c/0005b0bc) use the returned
 *   initialized pointer, so it is declared to return the slot value. */
uint64_t sk_f_0005acac(uint64_t slot_addr, uint64_t arg2, uint64_t arg3)
{
    int64_t *slot = (int64_t *)slot_addr;
    int64_t initialized;

    if (*slot == 0) {
        initialized = sk_f_0005baac(arg2, arg3);
        *slot = initialized;
    }
    return (uint64_t)*slot;
}

/* FUN_0005ace4 @ 0x0005ace4   (est. commpage_validate)
 * Ghidra: void FUN_0005ace4(void)
 * Validates that a commpage was supplied to the current thread.  If the commpage pointer
 * (thread + 0x108) is NULL, panics with "No commpage was supplied".  If the commpage is
 * smaller than a header region (0x30 words), traps via SoftwareBreakpoint.
 * Confidence: medium
 * Notes: s_No_commpage_was_supplied_005bc16c string; SoftwareBreakpoint(0x5519,0x5ad14). */
uint64_t sk_f_0005ace4(void)
{
    uint64_t commpage;

    commpage = *(uint64_t *)(sk_x_00054610() + 0x108);
    if (commpage == 0) {
        uint64_t msg = sk_x_00060524();
        sk_f_0005b190(msg, sk_str_005bc16c);
        __builtin_unreachable();
    }
    if (commpage <= commpage + 0x30) {
        return commpage;
    }
    SoftwareBreakpoint(0x5519, 0x5ad14);
}

/* FUN_0005ad24 @ 0x0005ad24   (est. commpage_get)
 * Ghidra: undefined8 FUN_0005ad24(void)
 * Returns the commpage pointer for the current thread (thread + 0x108).
 * Confidence: medium
 * Notes: reads (thread + 0x108) from sk_x_00054610(). */
uint64_t sk_f_0005ad24(void)
{
    return *(uint64_t *)(sk_x_00054610() + 0x108);
}

/* FUN_0005ad40 @ 0x0005ad40   (est. trace_tables_init)
 * Ghidra: void FUN_0005ad40(void)
 * Installs a pointer to a trace/dispatch table at fixed global address 0x64db08, then
 * initializes the trace tables via sk_f_0005ba5c().
 * Confidence: low
 * Notes: decompiler warns "Read-only address (ram,0x0064db08) is written"; the uRam artifact
 *   is transcribed as a raw volatile global store of 0x64da80. */
void sk_f_0005ad40(void)
{
    *(volatile uint64_t *)0x64db08 = 0x64da80;
    sk_f_0005ba5c(0);   /* decompiler dropped the enqueue-entry arg here */
    return;
}

/* FUN_0005ad58 @ 0x0005ad58   (est. trace_memory_alloc)
 * Ghidra: void FUN_0005ad58(long param_1)
 * Ensures the trace buffer for the given trace context has room for a 5-record trace entry:
 * if the current write position (trace+0x48) is below the limit (trace+0x28), requests a
 * (position + 5, capped at the limit) * 64-byte allocation from the allocator table stored at
 * trace+0x38, committing the new position on success.  On allocation failure, validates the
 * error against the fixed trace-memory region [0x64cb40,0x64cb80) and panics with
 * "Failed to allocate trace memory" if out of bounds.
 * Confidence: medium
 * Notes: s_Failed_to_allocate_trace_memory__005bc391; DAT_0064cb40/48/80 bounds checks;
 *   in_xzr treated as +0; SoftwareBreakpoint(0x5519,0x5ae4c); LORelease().
 *   Locals: alloc_bytes=local_28, free_pos=uVar3, cur=uVar4. */
void sk_f_0005ad58(int64_t trace)
{
    uint64_t alloc_bytes;
    uint64_t free_pos;
    uint64_t cur;
    uint64_t result;

    if (*(uint64_t *)(trace + 0x48) < *(uint64_t *)(trace + 0x28)) {
        free_pos = *(uint64_t *)(trace + 0x50);
        cur = *(uint64_t *)(trace + 0x48);
        if ((cur < free_pos || cur - free_pos == 0) ||
            ((cur - free_pos) + *(int64_t *)(trace + 0x60) < 5)) {
            if (cur <= free_pos) {
                cur = free_pos;
            }
            alloc_bytes = cur + 5;
            if (*(uint64_t *)(trace + 0x28) <= alloc_bytes) {
                alloc_bytes = *(uint64_t *)(trace + 0x28);
            }
            alloc_bytes <<= 6;
            result = (**(uint64_t (**)(uint64_t, uint64_t *))(*(int64_t *)(trace + 0x38) + 0x18))
                        (*(uint64_t *)(trace + 0x30), &alloc_bytes);
            result &= 0xff;
            if (result != 0) {
                uint64_t msg = sk_x_00060524();
                if ((uint8_t *)&sk_g_0064cb40 <= (uint8_t *)&sk_g_0064cb40 + result &&
                    (uint8_t *)&sk_g_0064cb48 + result <= (uint8_t *)&sk_g_0064cb80 &&
                    (uint8_t *)&sk_g_0064cb40 + result <= (uint8_t *)&sk_g_0064cb48 + result) {
                    sk_f_0005b190(msg, sk_str_005bc391);
                    __builtin_unreachable();
                }
                SoftwareBreakpoint(0x5519, 0x5ae4c);
            }
            *(uint64_t *)(trace + 0x48) = alloc_bytes >> 6;
            *(int64_t *)(trace + 0x50) = *(int64_t *)(trace + 0x50) + 0;
            LORelease();
        }
    }
    return;
}

/* FUN_0005ae4c @ 0x0005ae4c   (est. thread_run_acquire_locks)
 * Ghidra: void FUN_0005ae4c(undefined8 param_1,long param_2,undefined8 param_3,int param_4)
 * Thread entry helper: formats the thread name (sk_x_000618CC), logs "xrt: Thread ..."
 * (sk_x_00118B28), and, when `acquire` is set and the lock array (locks+0x10, count at
 * locks+0x38) is non-empty, walks each lock acquiring it via sk_f_0005bc48 and logging
 * "xrt: ... acquired at %02hhX:%02hhX" (sk_x_00054C9C) until acquisition fails.
 * Confidence: medium
 * Notes: stack canary guard; s__xrt__Thread__s__s__p_005bc3bf and
 *   s__xrt___p_acquired_at__02hhX_02hh_005bc3d6 strings; SoftwareBreakpoint(0x5519,0x5afe4)
 *   pointer-range check; sk_x_0011D7E8() stack-check-fail epilogue. */
void sk_f_0005ae4c(uint64_t thread_name, int64_t locks, uint64_t unused_arg, int32_t acquire)
{
    uint64_t stack_guard;
    int64_t *slot;
    int64_t lock;
    uint64_t idx;
    uint64_t dummy;
    uint8_t namebuf[20];

    stack_guard = -0x2c8502b44bfffed6;
    sk_x_000618CC(thread_name, namebuf);
    sk_x_00118B28(sk_str_005bc3bf);
    if ((acquire != 0) && (*(int64_t *)(locks + 0x38) != 0)) {
        idx = 0;
        slot = (int64_t *)(locks + 0x10);
        do {
            if (((slot < (int64_t *)(locks + 0x10)) || ((int64_t *)(locks + 0x38) < slot + 1)) ||
                (slot + 1 < slot)) {
                SoftwareBreakpoint(0x5519, 0x5afe4);
            }
            lock = *slot;
            if (sk_f_0005bc48(&lock, 1) == 0) break;
            dummy = 0;
            sk_x_00054C9C(*slot, &dummy);
            sk_x_00118B28(sk_str_005bc3d6);
            idx = idx + 1;
            slot = slot + 1;
        } while (idx < *(uint64_t *)(locks + 0x38));
    }
    if (stack_guard == -0x2c8502b44bfffed6) {
        return;
    }
    sk_x_0011D7E8();
}

/* FUN_0005afe8 @ 0x0005afe8   (est. lock_acquire_via_lazy_global)
 * Ghidra: void FUN_0005afe8(long param_1,undefined8 param_2,undefined8 param_3)
 * Acquires a lock on `obj` through the global lock-flavor selector at 0x6b04b8 (lazily
 * initialized via sk_f_0005acac): if the flavor is not 'acquire-style' or the underlying
 * sk_x_004B5FB8 reports a change, bumps the per-object lock count (obj+0x58).
 * Confidence: medium
 * Notes: reads flavor byte from the global at 0x6b04b8; obj+0x58 counter. */
void sk_f_0005afe8(int64_t obj, uint64_t arg2, uint64_t arg3)
{
    uint8_t *flavor;
    uint64_t changed;

    flavor = (uint8_t *)sk_f_0005acac(0x6b04b8, 1, 3);
    if ((*flavor != '\x02') || (changed = sk_x_004B5FB8(obj, arg3, arg2), (changed & 1) != 0)) {
        *(int64_t *)(obj + 0x58) = *(int64_t *)(obj + 0x58) + 1;
    }
    return;
}

/* FUN_0005b05c @ 0x0005b05c   (est. lock_release_via_lazy_global)
 * Ghidra: void FUN_0005b05c(long param_1,undefined8 param_2)
 * Releases a lock on `obj` via the global lock-flavor selector at 0x6b04b8: when the flavor is
 * 'acquire-style', calls sk_x_004B6194, then decrements the per-object lock count (obj+0x58).
 * Confidence: medium
 * Notes: reads flavor byte from the global at 0x6b04b8. */
void sk_f_0005b05c(int64_t obj, uint64_t arg2)
{
    uint8_t *flavor;

    flavor = (uint8_t *)sk_f_0005acac(0x6b04b8, 1, 3);
    if (*flavor == '\x02') {
        sk_x_004B6194(obj, arg2);
    }
    *(int64_t *)(obj + 0x58) = *(int64_t *)(obj + 0x58) + -1;
    return;
}

/* FUN_0005b0bc @ 0x0005b0bc   (est. lock_release_check_balanced)
 * Ghidra: void FUN_0005b0bc(long param_1)
 * Finalizes lock release for `obj`: when the global lock flavor (0x6b04b8) is 'acquire-style',
 * calls sk_x_004B63CC.  If the per-object lock count (obj+0x58) has not returned to zero,
 * panics with "thread holds locks after return from ...".
 * Confidence: medium
 * Notes: s_thread_holds_locks_after_return_f_005bc367 string; panic via sk_f_0005b190(0, ...). */
void sk_f_0005b0bc(int64_t obj)
{
    uint8_t *flavor;

    flavor = (uint8_t *)sk_f_0005acac(0x6b04b8, 1, 3);
    if (*flavor == '\x02') {
        sk_x_004B63CC(obj);
    }
    if (*(int64_t *)(obj + 0x58) == 0) {
        return;
    }
    sk_f_0005b190(0, sk_str_005bc367);
    __builtin_unreachable();
}

/* FUN_0005b120 @ 0x0005b120   (est. lock_flavor_ensure)
 * Ghidra: void FUN_0005b120(undefined8 param_1)
 * Ensures the global lock-flavor selector at the given slot is initialized by calling
 * sk_f_0005acac(param_1, 1, 3).
 * Confidence: medium
 * Notes: forwards to lazy-init; flavor params 1, 3. */
void sk_f_0005b120(uint64_t slot)
{
    sk_f_0005acac((uint64_t)slot, 1, 3);
    return;
}

/* FUN_0005b12c @ 0x0005b12c   (est. security_assertion_failed)
 * Ghidra: void FUN_0005b12c(undefined8 param_1)
 * Triggers a security assertion failure panic, logging "Security assertion failed: %s ..."
 * via sk_x_001150E0 (noreturn).  The parameter is passed through the stack for the message.
 * Confidence: medium
 * Notes: s_Security_assertion_failed___s__f_005a8b30 string; noreturn; param is unused beyond
 *   the ABI slot (uStack0000000000000010 artifact omitted). */
void sk_f_0005b12c(uint64_t param)
{
    sk_x_001150E0(sk_str_005a8b30);
    __builtin_unreachable();
}

/* FUN_0005b140 @ 0x0005b140   (est. trace_table_lazy_init)
 * Ghidra: void FUN_0005b140(void)
 * Lazily installs a trace/dispatch table pointer (0x65c4d8) into global _DAT_006b04c0 if it is
 * not already set.
 * Confidence: medium
 * Notes: _DAT_006b04c0 -> sk_g_006b04c0; write of 0x65c4d8; globals starting with '_' overlap
 *   smaller symbols at the same address (decompiler warning). */
void sk_f_0005b140(void)
{
    if (sk_g_006b04c0 != 0) {
        return;
    }
    sk_g_006b04c0 = 0x65c4d8;
    return;
}


/* part1.c — cL4 Secure Kernel (GL1) "xrt" thread-runtime panic & registry slice.
 * Worker Sk11P1. Addresses in order. */

/* FUN_0005b160 @ 0x0005b160   (est. no-op / placeholder return)
 * Ghidra: undefined8 FUN_0005b160(void)
 * Returns constant zero. Likely a placeholder or capability that always
 * reports "not present". No inputs, no side effects.
 * Confidence: high
 * Notes: trivial body; no globals or calls. */
uint64_t sk_f_0005b160(void)
{
    return 0;
}

/* FUN_0005b190 @ 0x0005b190   (est. xrt_panic)
 * Ghidra: void FUN_0005b190(undefined8 param_1,undefined8 param_2)
 * Noreturn panic entry: forwards both arguments plus the caller's frame
 * address into the full panic-message formatter. param_1 selects the
 * panicking thread (0 = current thread); param_2 is the panic reason/tag.
 * Does not return.
 * Confidence: high
 * Notes: &stack0x00000000 is the caller's stack frame; represented as the
 * address of a local. sk_f_0005b1b0 is noreturn. */
void sk_f_0005b190(uint64_t thread, const char *reason)
{
    uint64_t frame;
    sk_f_0005b1b0(thread, reason, (uint64_t)&frame);
}

/* FUN_0005b1b0 @ 0x0005b1b0   (est. xrt_full_panic_message)
 * Ghidra: void FUN_0005b1b0(ulong param_1,undefined8 param_2,undefined8 param_3)
 * Builds and dispatches the full panic message. Selects the panicking thread
 * (param_1, or the current thread from the runtime if param_1==0), sets the
 * "panic requested" flag on it and "in panic" on the current thread, formats
 * a 0x1b8-byte panic buffer with the reason/tag strings, prints the thread
 * name, gathers per-thread context (registry entry, IPC buffer, two
 * capability slots), assembles a capability-name table padded into display
 * columns, invokes the thread's panic handler (or logs its absence), copies
 * the message to the fixed output buffer (0x6b04d0) and triggers the
 * debugger to dump it. Traps (does not return) at the end.
 * Confidence: medium
 * Notes: Stack-overlap cap table represented as a single uint64 array
 *   (local_d0 region) plus a metadata array (auStack_c8 region). Several
 *   context fields (local_1a8..local_144, local_110..uStack_f8) are
 *   assembled but not read within the visible body; they are seeded into the
 *   region as in the decompile. Strings: s_xrt_0x_06x__Thread_requested_pa_005bc486,
 *   s__xrt_0x06x__Full_panic_message___005bc4b5, s_Panic_requested_005bc4d9,
 *   s_Unknown_005bc4ee, DAT_005bc4d6, DAT_005bc4e9,
 *   s__xrt_0x_06x__Thread_has_no_panic_005bc520, s__xrt_0x_06x__Thread_panic_handle_005bc4f6,
 *   s__Exclave__005bc54e, s__xrt_0x_06x__Unable_to_trigger_d_005bc559.
 *   unaff_x30 -> __builtin_return_address(0). tpidrro_el0 via mrs.
 *   Canary absent; ends in SoftwareBreakpoint(0x5519,0x5b824). */
void sk_f_0005b1b0(uint64_t thread, const char *reason, uint64_t arg3)
{
    long found;
    long *rec;
    char *name;
    uint64_t cur_thread;
    uint64_t thread_id;
    uint64_t id_hi;
    uint64_t id_lo;
    uint64_t cap_id1;
    uint64_t cap_id2;
    uint64_t cap_count;
    uint64_t slot;
    uint64_t padding;
    uint64_t copied;
    uint64_t remain;
    uint64_t *cap_entry;
    uint16_t entry_len;
    int64_t ipc_lo;
    int64_t ipc_hi;
    int64_t slot1;
    int64_t slot2;
    int64_t a;
    int64_t b;
    int64_t c;
    int64_t d;
    int64_t e;
    uint64_t v0;
    uint64_t v1;
    uint16_t *tls;
    uint16_t tls_lo;
    uint16_t tls_hi;
    char panic_buffer[0x1b8];          /* auStack_228 */
    char name_buf[0x130];              /* auStack_1a0 (thread-name print buffer) */
    char out_buffer[0x2000];           /* fixed output buffer at 0x6b04d0 */
    uint64_t slots[2];                 /* local_70 */
    uint64_t cap_region[16];           /* local_d0 region: context + cap-name table */
    uint64_t caps_meta[11];            /* auStack_c8 region (padding metadata) */

    cur_thread = sk_x_00060524();
    /* Select the panicking thread: param_1, or current thread if param_1==0. */
    if (thread != 0) {
        goto select_done;
    }
    thread = cur_thread;
select_done:
    /* Mark selected thread "panic requested" and current thread "in panic". */
    *(uint64_t *)(thread + 0x48) |= 0x20;
    *(uint64_t *)(cur_thread + 0x48) |= 0x40;

    id_hi = cur_thread >> 0xe & 0xffffff;
    id_lo = thread >> 0xe & 0xffffff;

    sk_x_001185EC(0xeb1a02bf914012ba, sk_str_005bc486);   /* "xrt: %#06x: Thread requested panic" */
    sk_x_00118ABC(sk_str_005bc4b5, 0x20, 1, 0xeb1a02bf914012ba); /* "xrt: %#06x: Full panic message --" */
    sk_x_00118C38(0xeb1a02bf914012ba, reason, arg3);
    sk_x_00118ABC((uint8_t *)&sk_g_005bc4d6, 2, 1, 0xeb1a02bf914012ba);
    if (thread == cur_thread) {
        sk_x_00062474(sk_str_005bc4d9, 0x3d, 0xeb1a02bf914012ba, thread,
                      1, 0, 0, 0, id_hi, id_lo);            /* "Panic requested" */
    }
    sk_x_00114330(panic_buffer, 0x1b8);                     /* clear the 0x1b8-byte buffer */
    sk_x_00116BB4(panic_buffer, 0x80, reason, arg3);          /* format message header */

    thread_id = *(uint64_t *)(thread + 8);
    found = sk_f_0005d154(thread_id, &slot2);               /* find thread record by id */
    if (found == 0) {
        rec = (long *)sk_f_0005acac(0x6b2568, 1, 1);        /* thread registry */
        if (*(long *)(rec + 0x78) == 0) {
            name = sk_str_005bc4ee;                         /* "Unknown" */
        } else {
            name = (char *)&sk_g_005bc4e9;
        }
    } else {
        name = (char *)&sk_g_005bc4e9;
    }
    sk_f_0005b824((uint64_t)name, 0x130, 0x40, (const char *)name_buf);

    /* Assemble thread-context fields (dead writes in this body; the record
     * is consumed by the panic subsystem via the stack layout). */
    rec = (long *)sk_f_0005acac(0x6b2568, 1, 1);
    cap_region[0] = *(uint64_t *)(rec + 0x40);              /* thread id */
    slot1 = sk_x_0019AFB0(thread_id);
    slot2 = *(uint64_t *)(thread + 0x10);
    cap_region[1] = sk_f_0005b8c8();                        /* thread id hex string */
    cap_region[2] = sk_x_0019AFBC(thread_id);
    cap_region[3] = sk_x_00063970(*(uint64_t *)(thread + 0xa8));
    cap_region[4] = *(uint32_t *)(thread + 0x118);

    ipc_lo = 0;
    ipc_hi = 0;
    sk_x_000615FC(thread, &ipc_hi, &ipc_lo);                /* IPC buffer info */
    slot1 = 0;
    slots[0] = 0;
    sk_x_000619C8(&slot1, thread);
    slots[0] = 0;
    if (thread == cur_thread) {
        slot1 = 0x5b40c;
        slots[0] = (uint64_t)__builtin_return_address(0);   /* unaff_x30 */
    }
    a = sk_x_000614F8(thread);
    b = sk_x_00061488(thread);
    c = sk_x_00061638(thread);
    d = sk_x_0006198C(thread);
    v0 = (uint64_t)ipc_hi;
    v1 = (uint64_t)ipc_lo;
    e = sk_x_0006132C(thread);

    found = sk_f_0005bc48(slots, 0);                        /* first cap-slot lookup */
    if (found == 0) {
        cap_id1 = 0xffff000000000000;
    } else {
        cap_id1 = (uint64_t)*(uint16_t *)(found + 0x40) << 0x30;
    }
    cap_id1 = slots[0] & 0xffffffffffff | cap_id1;
    slots[0] = (uint64_t)slot1;
    found = sk_f_0005bc48(slots, 0);                        /* second cap-slot lookup */
    if (found == 0) {
        cap_id2 = 0xffff000000000000;
    } else {
        cap_id2 = (uint64_t)*(uint16_t *)(found + 0x40) << 0x30;
    }
    cap_id2 = slots[0] & 0xffffffffffff | cap_id2;

    /* Seed the remaining context fields of the cap/context region. */
    cap_region[5]  = 0;                                     /* local_110 */
    cap_region[6]  = v0;                                    /* uStack_108 */
    cap_region[7]  = v1;                                    /* local_100 */
    cap_region[8]  = (uint64_t)slot1;                       /* local_e0 */
    cap_region[9]  = 0;                                     /* uStack_d8 */
    cap_region[10] = thread;                                /* local_140 */
    cap_region[11] = (uint64_t)a;                           /* uStack_138 */
    cap_region[12] = (uint64_t)b;                           /* local_130 */
    cap_region[13] = (uint64_t)c;                           /* uStack_128 */
    cap_region[14] = thread;                                /* local_120 */
    cap_region[15] = (uint64_t)d;                           /* uStack_118 */
    if (*(long *)(thread + 0xa8) != 0) {
        cap_region[5] = sk_x_00063910();                    /* local_110 */
    }

    /* Collect up to 0xc capability-name entries into the table base. */
    cap_count = sk_x_00061044(thread, 0, &cap_region[0], 0xc, 0);
    slot = 0;
    if (cap_count != 0) {
        slot = 0;
        cap_entry = &cap_region[0];
        do {
            entry_len = (uint16_t)(*cap_entry >> 48);       /* name length at +6 */
            if (slot <= entry_len && entry_len != 0xffff) {
                slot = entry_len + 1;
            }
            cap_entry = cap_entry + 1;
            cap_count = cap_count - 1;
        } while (cap_count != 0);
    }
    padding = 0;
    if (slot < 7) {
        padding = 6 - slot;
    }
    if (cap_count < (uint64_t)(padding << 1)) {
        *(uint16_t *)((uint8_t *)caps_meta + cap_count * 8 - 2) = 6;   /* sentinel slot */
    } else {
        cap_count = padding << 1;
    }
    if (slot < 7) {
        padding = 6 - slot;
        rec = (long *)sk_f_0005acac(0x6b2568, 1, 1);
        for (rec = (long *)*rec; rec != (long *)0x0; rec = (long *)*rec) {
            if (((int8_t)((uint8_t *)rec)[8] < 0) &&
                (copied = (uint64_t)*(uint16_t *)((uint8_t *)rec + 64), copied < slot)) {
                cap_entry = &cap_region[padding * 2 + copied * 2];
                copied = (uint64_t)(padding + copied) * 0x10 + 0x158;
                remain = 0;
                if (copied < 0x1b9) {
                    remain = 0x1b8 - copied;
                }
                sk_x_00117CC8(cap_entry, (uint8_t *)rec + 16, 0x10, remain);
            }
        }
    } else {
        padding = 0;
    }
    if (cap_count != 0) {
        cap_entry = &cap_region[0];
        do {
            *cap_entry = *cap_entry + (padding << 0x30);    /* pad each entry */
            cap_count = cap_count - 1;
            cap_entry = cap_entry + 1;
        } while (cap_count != 0);
    }

    if (*(void **)(cur_thread + 0xa0) == (void *)0x0) {
        name = sk_str_005bc520;                 /* "xrt: %#06x: Thread has no panic handler" */
    } else {
        (*(void (**)(char *))(cur_thread + 0xa0))(panic_buffer);
        name = sk_str_005bc4f6;                 /* "xrt: %#06x: Thread panic handler returned" */
    }
    sk_x_001185EC(0xeb1a02bf914012ba, name);
    sk_f_0005e4d8((uint64_t)panic_buffer, (uint64_t)out_buffer, 0x2000, 0);
    sk_x_000538C8(sk_str_005bc54e, (uint64_t)out_buffer, 0x2000, 0xeb1a02bf914012ba); /* "Exclave: " */

    /* Scan the output buffer for the terminator; at the first NUL trigger
     * the debugger/supervisor to dump the message, then trap. */
    for (copied = 0; copied != 0x2000; copied++) {
        if (out_buffer[copied] == '\0') {
            sk_x_0011883C((uint64_t)out_buffer, 0xaa1603fbd280001c);
            copied = (uint64_t)sk_x_00053444();
            if (copied != 0) {
                sk_x_000552C0(copied, 6, (uint64_t)out_buffer);
            }
            copied = (uint64_t)sk_x_000533EC();
            if (copied != 0) {
                __asm__ volatile("mrs %0, tpidrro_el0" : "=r"(tls));
                tls_lo = tls[0];
                tls_hi = tls[2];
                CallSupervisor(0);
                tls[0] = tls_lo;
                tls[2] = tls_hi;
            }
            sk_x_001185EC(0xeb1a02bf914012ba, sk_str_005bc559); /* "xrt: %#06x: Unable to trigger debugger" */
            SoftwareBreakpoint(1, 0x5b820);
        }
    }
    /* Does not return */
    SoftwareBreakpoint(0x5519, 0x5b824);
}

/* FUN_0005b824 @ 0x0005b824   (est. panic printer)
 * Ghidra: void FUN_0005b824(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Forwards to the console formatter, reordering arguments and appending the
 * caller frame address: (param_1, param_3, 0, param_2, param_4, frame).
 * param_1 is the string/name to print, param_2 a length, param_3 a
 * width/flag. Returns after the underlying print.
 * Confidence: medium
 * Notes: &stack0x00000000 represented as address of a local. */
void sk_f_0005b824(uint64_t a, uint64_t b, uint64_t c, const char *d)
{
    uint64_t frame;
    sk_x_00116BCC(a, c, 0, b, d, (uint64_t)&frame);
}

/* FUN_0005b860 @ 0x0005b860   (est. xrt_thread_name_get)
 * Ghidra: undefined8 FUN_0005b860(undefined8 *param_1)
 * Reads the current thread's name fields from the thread registry: stores
 * the name pointer (+0x70) through param_1 and returns the length/flag word
 * (+0x78).
 * Confidence: high
 * Notes: registry handle constant 0x6b2568. */
uint64_t sk_f_0005b860(uint64_t *out_name)
{
    long rec;
    uint64_t len;
    rec = (long)sk_f_0005acac(0x6b2568, 1, 1);
    len = *(uint64_t *)(rec + 0x78);
    *out_name = *(uint64_t *)(rec + 0x70);
    return len;
}

/* FUN_0005b89c @ 0x0005b89c   (est. xrt_thread_id_get)
 * Ghidra: undefined8 FUN_0005b89c(void)
 * Returns the current thread's id field (+0x40) from the thread registry.
 * Confidence: high
 * Notes: registry handle constant 0x6b2568. */
uint64_t sk_f_0005b89c(void)
{
    long rec;
    rec = (long)sk_f_0005acac(0x6b2568, 1, 1);
    return *(uint64_t *)(rec + 0x40);
}

/* FUN_0005b8c8 @ 0x0005b8c8   (est. xrt_thread_id_hex)
 * Ghidra: void FUN_0005b8c8(void)
 * Renders the current thread's id (low 16 bits) as an 8-hex-digit ASCII
 * string using the "0123456789abcdef" alphabet, packed into a uint32
 * (little-endian byte order). The caller reads the result in x0 even though
 * Ghidra shows a void signature.
 * Confidence: medium
 * Notes: hex alphabet s_0123456789abcdef_005bc6c6; canary present
 *   (local_18 = -0x2c8502b44bfffed6); on canary mismatch calls
 *   sk_x_0011D7E8 (noreturn). */
uint32_t sk_f_0005b8c8(void)
{
    uint64_t stack_guard;
    long rec;
    uint32_t result;
    uint16_t id;
    uint8_t hex_digits[16];
    uint64_t idx;

    stack_guard = -0x2c8502b44bfffed6;
    rec = (long)sk_f_0005acac(0x6b2568, 1, 1);
    result = 0;
    id = *(uint16_t *)(rec + 0x40);
    /* 16-entry hex alphabet "0123456789abcdef" (sk_str_005bc6c6):
     * bytes [0..7] packed into local_30, bytes [8..15] into uStack_28. */
    hex_digits[0]  = (uint8_t)sk_str_005bc6c6[0];
    hex_digits[1]  = (uint8_t)sk_str_005bc6c6[1];
    hex_digits[2]  = (uint8_t)sk_str_005bc6c6[2];
    hex_digits[3]  = (uint8_t)sk_str_005bc6c6[3];
    hex_digits[4]  = (uint8_t)sk_str_005bc6c6[4];
    hex_digits[5]  = (uint8_t)sk_str_005bc6c6[5];
    hex_digits[6]  = (uint8_t)sk_str_005bc6c6[6];
    hex_digits[7]  = (uint8_t)sk_str_005bc6c6[7];
    hex_digits[8]  = (uint8_t)sk_str_005bc6c6[8];
    hex_digits[9]  = (uint8_t)sk_str_005bc6c6[9];
    hex_digits[10] = (uint8_t)sk_str_005bc6c6[10];
    hex_digits[11] = (uint8_t)sk_str_005bc6c6[11];
    hex_digits[12] = (uint8_t)sk_str_005bc6c6[12];
    hex_digits[13] = (uint8_t)sk_str_005bc6c6[13];
    hex_digits[14] = (uint8_t)sk_str_005bc6c6[14];
    hex_digits[15] = (uint8_t)sk_str_005bc6c6[15];

    for (idx = 0; idx != 0x20; idx += 8) {
        result |= (uint32_t)hex_digits[id & 0xf] << idx;
        id = id >> 4;
    }
    if (stack_guard == -0x2c8502b44bfffed6) {
        return result;
    }
    sk_x_0011D7E8(result);
}

/* FUN_0005ba14 @ 0x0005ba14   (est. xrt_thread_registry_head)
 * Ghidra: undefined8 FUN_0005ba14(void)
 * Returns the thread registry's head pointer (element 0), i.e. the first
 * entry in the thread list.
 * Confidence: high
 * Notes: registry handle constant 0x6b2568. */
uint64_t sk_f_0005ba14(void)
{
    uint64_t *reg;
    reg = (uint64_t *)sk_f_0005acac(0x6b2568, 1, 1);
    return *reg;
}

/* FUN_0005ba40 @ 0x0005ba40   (est. xrt_register_exception_handler)
 * Ghidra: void FUN_0005ba40(undefined8 param_1)
 * Installs an exception/panic handler: stores the fixed descriptor address
 * 0x6b24d0 into the global at 0x64db30, stores the supplied argument into
 * the global at 0x6b2520, then enqueues the descriptor via sk_f_0005ba5c.
 * Confidence: low
 * Notes: raw absolute-address globals (not DAT_-named); Ghidra warning about
 *   writing read-only address 0x64db30. The decompile shows FUN_0005ba5c()
 *   with no argument (dropped); a local descriptor node is passed here. */
void sk_f_0005ba40(uint64_t arg)
{
    uint64_t desc;
    *(uint64_t *)0x64db30 = 0x6b24d0;   /* descriptor address */
    *(uint64_t *)0x6b2520 = arg;
    sk_f_0005ba5c(&desc);
}

/* FUN_0005ba5c @ 0x0005ba5c   (est. xrt_enqueue_registry)
 * Ghidra: void FUN_0005ba5c(long *param_1)
 * Links param_1 into the per-CPU queue whose head lives at cpu_data+0x10
 * (cpu_data read from TPIDR_EL0). Loops while param_1->next is 0, reading
 * the current head; when the head read is stable it splices param_1 in.
 * Falls to a spin/yield (sk_x_004B6864) and traps if the queue head
 * overflows.
 * Confidence: low
 * Notes: tpidr_el0 read via mrs; SoftwareBreakpoint(0x5519,0x5baac). */
void sk_f_0005ba5c(uint64_t *entry)
{
    uint64_t cpu_data;
    uint64_t *queue_head;
    uint64_t head;

    __asm__ volatile("mrs %0, tpidr_el0" : "=r"(cpu_data));
    queue_head = (uint64_t *)(cpu_data + 0x10);
    while (*entry == 0) {
        if (queue_head + 1 < queue_head) goto trap;
        head = *queue_head;
        *entry = head;
        if (*queue_head == head) {
            *queue_head = (uint64_t)(uintptr_t)entry;
            return;
        }
    }
    sk_x_004B6864();
trap:
    SoftwareBreakpoint(0x5519, 0x5baac);
}

/* FUN_0005baac @ 0x0005baac   (est. xrt_registry_find2)
 * Ghidra: long FUN_0005baac(int param_1,int param_2)
 * Walks the per-CPU registry list (head at cpu_data+0x10, TPIDR_EL0) and
 * returns the value field (element 3) of the last entry whose key1
 * (element 1) equals param_1 and key2 (element 2) equals param_2; returns
 * 0 when no match (or empty list).
 * Confidence: medium
 * Notes: entries are linked lists: [0]=next,[1]=key1,[2]=key2,[3]=value. */
int64_t sk_f_0005baac(int key1, int key2)
{
    uint64_t cpu_data;
    long *node;
    long result;
    long found;

    __asm__ volatile("mrs %0, tpidr_el0" : "=r"(cpu_data));
    node = *(long **)*(long **)(cpu_data + 0x10);
    if (node == (long *)0x0) {
        result = 0;
    } else {
        found = 0;
        do {
            result = node[3];
            if ((int)node[2] != key2 || (int)node[1] != key1) {
                result = found;
            }
            node = (long *)*node;
            found = result;
        } while (node != (long *)0x0);
    }
    return result;
}

/* FUN_0005baf0 @ 0x0005baf0   (est. xrt_thread_register)
 * Ghidra: void FUN_0005baf0(ulong *param_1)
 * Allocates a thread slot from the registry: reads the 16-bit id counter at
 * registry+8, hands the old value back through param_1[8], increments the
 * counter, then links param_1 into the registry head list (element 0) with
 * a compare-and-swap insert. Traps if the list pointer overflows.
 * Confidence: medium
 * Notes: registry handle constant 0x6b2568; SoftwareBreakpoint(0x5519,0x5bb68). */
void sk_f_0005baf0(uint64_t *entry)
{
    uint64_t *reg;
    int16_t old_id;
    uint64_t head;

    reg = (uint64_t *)sk_f_0005acac(0x6b2568, 1, 1);
    old_id = (int16_t)reg[1];
    *(int16_t *)(reg + 1) = old_id + 1;
    *(int16_t *)(entry + 8) = old_id;
    for (;;) {
        head = *reg;
        if (head > head + 0x78 || reg > reg + 0x12) break;
        *entry = head;
        if (*reg == head) {
            *reg = (uint64_t)entry;
            return;
        }
    }
    SoftwareBreakpoint(0x5519, 0x5bb68);
}


/* FUN_0005bb68 @ 0x0005bb68   (est. xrt_registry_entry)
 * Ghidra: void FUN_0005bb68(void)
 * Touches the xrt thread-runtime registry descriptor (at image-base 0x6b2568)
 * by invoking the registry-acquire helper and discarding the result. Used as a
 * bare entry/no-op initializer on the registry path.
 * Confidence: medium
 * Notes: arg 0x6b2568 is the image-base registry descriptor passed to FUN_0005acac. */
uint64_t sk_f_0005bb68(void)
{
    return sk_f_0005acac(0x6b2568, 1, 1);
}

/* FUN_0005bb7c @ 0x0005bb7c   (est. registry_find_first_thread)
 * Ghidra: ulong * FUN_0005bb7c(void)
 * Acquires the xrt thread registry and walks its singly-linked list of thread
 * entries, returning the first entry whose flag byte (at offset 8) has bit 0
 * clear (a "free/available" entry), or the sentinel list 0x65c4e8 when the list
 * is empty. Bounds-check failure on a candidate node traps via SoftwareBreakpoint.
 * Confidence: medium
 * Notes: node->next is stored as the first word; 0xfffffffff mask unwraps
 *        36-bit tagged pointers; *result+1 is the flag byte at word offset 1. */
uint64_t * sk_f_0005bb7c(void)
{
    uint64_t *result, *next;

    result = (uint64_t *)sk_f_0005acac(0x6b2568, 1, 1);
    next = (uint64_t *)*result;
    if (*result == 0) {
        result = (uint64_t *)0x65c4e8;
    }
    else {
        do {
            result = next;
            if (*result == 0) break;
            next = (uint64_t *)*result;
        } while ((*(uint8_t *)(result + 1) & 1) == 0);
        if (result + 0xf < result) {
            SoftwareBreakpoint(0x5519, 0x5bbc8);
        }
    }
    return result;
}

/* FUN_0005bbd8 @ 0x0005bbd8   (est. thread_name_range_scan)
 * Ghidra: ulong FUN_0005bbd8(long param_1,long *param_2)
 * Scans the byte range described by a thread object's {base,size} fields (at
 * offsets +0x50/+0x48) for the separator byte 0x2f ('/'), advancing the window
 * past each match. On failure (no byte found) writes the final size into *out_size
 * and returns the current base. A malformed (wrapping) window traps.
 * Confidence: medium
 * Notes: sk_x_001144A0 is the memchr-like scanner; 0x2f is a path/name separator. */
uint64_t sk_f_0005bbd8(uint8_t *thread, int64_t *out_size)
{
    int64_t size;
    uint64_t base;
    int64_t found;
    uint64_t next_base, limit;
    bool in_range;

    size = *(int64_t *)(thread + 0x48);
    base = *(uint64_t *)(thread + 0x50);
    do {
        found = sk_x_001144A0(base, 0x2f, size);
        if (found == 0) {
            *out_size = size;
            return base;
        }
        next_base = found + 1;
        limit = base + size;
        size = ~(found - base) + size;
        in_range = base <= next_base;
        base = next_base;
    } while (next_base <= limit && in_range);

    SoftwareBreakpoint(0x5519, 0x5bc30);
}

/* FUN_0005bc48 @ 0x0005bc48   (est. thread_registry_address_or_id_lookup)
 * Ghidra: void FUN_0005bc48(ulong *param_1,int param_2)
 * Walks the xrt thread registry list. In mode 0 it matches *value_ptr against
 * each entry's address range [node[5], node[5]+node[6]) and rewrites *value_ptr
 * to the offset into that region (value minus node[4]). In nonzero mode it
 * matches the entry's 16-bit id field (at byte offset 64) against the high 16
 * bits of *value_ptr and masks *value_ptr to its low 48 bits. Returns when the
 * first matching entry is found; silently returns if the list is empty.
 * Confidence: medium
 * Notes: node[5]/node[6] are the range base and length; node[4] is the region
 *        start used to compute an offset; id field is a short at offset 64. */
int sk_f_0005bc48(uint64_t *value_ptr, int32_t mode)
{
    int64_t *node;
    uint64_t value;

    node = (int64_t *)sk_f_0005acac(0x6b2568, 1, 1);
    node = (int64_t *)*node;
    do {
        if (node == 0) {
            return 0;   /* not found */
        }
        if (mode == 0) {
            value = *value_ptr;
            if (((uint64_t)node[5] <= value) && (value - node[5] < (uint64_t)node[6])) {
                *value_ptr = value - node[4];
                return 1;   /* found */
            }
        }
        else if (*(int16_t *)(node + 8) == (int16_t)(*value_ptr >> 0x30)) {
            *value_ptr = *value_ptr & 0xffffffffffff;
            return 1;   /* found */
        }
        node = (int64_t *)*node;
    } while (true);
}

/* FUN_0005bce0 @ 0x0005bce0   (est. register_thread_callback)
 * Ghidra: void FUN_0005bce0(long param_1)
 * Registers a per-thread callback by invoking the scheduler/registry helper
 * sk_f_0005d470 with the callback slot at callback_slot+8 and the callback
 * sk_f_0005bd10. A wrapping slot address (unsig 32-bit) traps.
 * Confidence: medium
 * Notes: callback target is the list-push routine sk_f_0005bd10. */
void sk_f_0005bce0(uint8_t *callback_slot)
{
    if ((uint32_t)(uintptr_t)(callback_slot + 8) <= (uint32_t)(uintptr_t)(callback_slot + 0xc)) {
        sk_f_0005d470((uint32_t *)(callback_slot + 8), (void (*)(void *))sk_f_0005bd10, 0);
        return;
    }
    SoftwareBreakpoint(0x5519, 0x5bd10);
}

/* FUN_0005bd10 @ 0x0005bd10   (est. registry_list_push)
 * Ghidra: void FUN_0005bd10(ulong *param_1)
 * Prepends node to the xrt thread registry's linked list headed at registry
 * offset +0x28. It stores the current head into *node and, if the head slot
 * is unchanged, installs node as the new head. Wrapping bounds trap.
 * Confidence: medium
 * Notes: registry +0x28 is the head slot; node next is the first word. */
void sk_f_0005bd10(uint64_t *node)
{
    uint64_t registry;
    uint64_t old_head;

    registry = sk_f_0005acac(0x6b2568, 1, 1);
    while ((old_head = *(uint64_t *)(registry + 0x28),
            old_head <= old_head + 0x28 &&
            (*node = old_head, registry <= registry + 0x90))) {
        if (*(uint64_t *)(registry + 0x28) == old_head) {
            *(uint64_t *)(registry + 0x28) = (uint64_t)node;
            return;
        }
    }
    SoftwareBreakpoint(0x5519, 0x5bd7c);
}

/* FUN_0005bd7c @ 0x0005bd7c   (est. registry_list_walk_with_callback)
 * Ghidra: void FUN_0005bd7c(code *param_1,undefined8 param_2)
 * Takes a per-thread lock, then walks the thread registry's tagged singly-linked
 * list headed at offset +0x10, invoking callback(callback_arg) once per entry.
 * The 36-bit tagged pointers are unwrapped; bit 0x2000000000 marks a terminal
 * entry (stops the walk). Malformed (wrapping) node addresses trap. The lock is
 * released before returning.
 * Confidence: medium
 * Notes: sk_x_00060570/sk_x_000605F8 are the lock acquire/release helpers. */
void sk_f_0005bd7c(void (*callback)(uint64_t), uint64_t callback_arg)
{
    uint64_t value;
    int acquired;
    uint64_t registry;
    uint64_t *node;
    uint8_t lock;

    lock = 0;
    do {
        acquired = sk_x_00060570(&lock);
    } while (acquired == 0);

    registry = sk_f_0005acac(0x6b2568, 1, 1);
    node = *(uint64_t **)(registry + 0x10);
    if (node == 0) {
        value = 0;
        goto recheck;
    }
    do {
        value = *node;
        if ((value >> 0x25 & 1) != 0) break;
        node = (uint64_t *)(value & 0xfffffffff);
    } while (node != 0);

    do {
        while (true) {
            if (node + 0x2f < node) {
                SoftwareBreakpoint(0x5519, 0x5be48);
            }
recheck:
            if (node == 0) {
                sk_x_000605F8(&lock);
                return;
            }
            (*callback)(callback_arg);
            node = (uint64_t *)(value & 0xfffffffff);
            if (node != 0) break;
            value = 0;
        }
        do {
            value = *node;
            if ((value >> 0x25 & 1) != 0) break;
            node = (uint64_t *)(value & 0xfffffffff);
        } while (node != 0);
    } while (true);
}

/* FUN_0005be48 @ 0x0005be48   (est. registry_set_callback_pair)
 * Ghidra: void FUN_0005be48(undefined8 param_1,undefined8 param_2)
 * Stores a callback/argument pair into the xrt thread registry at offsets +0x78
 * (arg) and +0x70 (fn). Simple field writer on the registry.
 * Confidence: low
 * Notes: registry offsets +0x70/+0x78 hold the saved callback pair. */
void sk_f_0005be48(uint64_t arg, uint64_t fn)
{
    uint64_t registry;

    registry = sk_f_0005acac(0x6b2568, 1, 1);
    *(uint64_t *)(registry + 0x70) = fn;
    *(uint64_t *)(registry + 0x78) = arg;
    return;
}

/* FUN_0005be84 @ 0x0005be84   (est. registry_stack_push)
 * Ghidra: void FUN_0005be84(ulong *param_1,int param_2)
 * Lock-free push of node onto one of the xrt registry's tagged stacks. In
 * mode 0 the head slot is at +0x10 and a counter at +0x18 is incremented; in
 * nonzero mode the head slot is at +0x20. A CAS loop stores the old head
 * (masked to its 36-bit pointer, tagged with bit 0x2000000000) into *node,
 * then installs node as the new head. If a global wakeup callback
 * (sk_g_006B2560) is installed it is invoked with (node, 1).
 * Confidence: medium
 * Notes: sk_g_006B2560 is the optional wake/callback hook at image-base 0x6b2560. */
void sk_f_0005be84(uint64_t *node, int32_t mode)
{
    uint64_t registry;
    uint64_t *head_slot;
    uint64_t old_head;

    registry = sk_f_0005acac(0x6b2568, 1, 1);
    if (mode == 0) {
        head_slot = (uint64_t *)(registry + 0x10);
        *(int64_t *)(registry + 0x18) = *(int64_t *)(registry + 0x18) + 1;
    }
    else {
        head_slot = (uint64_t *)(registry + 0x20);
    }
    do {
        old_head = *head_slot;
        *node = (old_head & 0xfffffffff) | 0x2000000000;
    } while (*head_slot != old_head);
    *head_slot = (uint64_t)node;

    if (sk_g_006B2560 != 0) {
        ((void (*)(uint64_t *, int))sk_g_006B2560)(node, 1);
    }
    return;
}

/* FUN_0005bf20 @ 0x0005bf20   (est. registry_stack_remove)
 * Ghidra: void FUN_0005bf20(ulong *param_1)
 * Removes node from the xrt registry's tagged stack headed at +0x10. It first
 * clears the caller's next tag (low 36 bits), takes the per-thread lock, then
 * performs a lock-free unlink of node from the list, fixing up the predecessor
 * to skip it while preserving the terminal-tag and next-pointer bits. If node
 * is the head it is popped directly. Malformed (wrapping) node addresses trap.
 * On success it clears *node and, if a global callback (sk_g_006B2560) is
 * installed, invokes it with (node, 0).
 * Confidence: medium
 * Notes: sk_x_00060650 is the post-unlink memory barrier; tag bit 0x2000000000
 *        is terminal. */
void sk_f_0005bf20(uint64_t *node)
{
    uint64_t registry;
    uint64_t value;
    uint64_t *pred, *cur, *cand;
    uint64_t prev_value, cand_value;
    uint8_t lock;

    registry = sk_f_0005acac(0x6b2568, 1, 1);
    *node = *node & 0xfffffffff;
    lock = 0;
    do {
        value = sk_x_00060570(&lock);
    } while ((value & 1) == 0);

    do {
        while (true) {
            cur = *(uint64_t **)(registry + 0x10);
            if (cur == 0) goto done;
            if (node != cur) break;
            if ((cur + 0x2f < node) ||
                (value = *node & 0xfffffffff, value + 0x178 < value)) {
badtrap:
                SoftwareBreakpoint(0x5519, 0x5c0ac);
            }
            if (*(uint64_t **)(registry + 0x10) == cur) {
                *(uint64_t *)(registry + 0x10) = value;
                goto done;
            }
        }
        if (cur + 0x2f < cur) goto badtrap;
        do {
            value = *cur;
            if ((value >> 0x25 & 1) != 0) break;
            cur = (uint64_t *)(value & 0xfffffffff);
        } while (cur != 0 && node != cur);
        if (cur + 0x2f < cur) goto badtrap;
        pred = cur;
        cand_value = value;
        if (cur == 0) goto done;
        do {
            prev_value = cand_value;
            cand = pred;
            pred = cand;
            if (cand == node) break;
            cand_value = 0;
            pred = (uint64_t *)(prev_value & 0xfffffffff);
            if ((pred != 0) && (node != pred)) {
                do {
                    cand_value = *pred;
                    if ((cand_value >> 0x25 & 1) != 0) break;
                    pred = (uint64_t *)(cand_value & 0xfffffffff);
                } while (pred != 0 && node != pred);
            }
            if (pred + 0x2f < pred) goto badtrap;
            cur = cand;
            value = prev_value;
        } while (pred != 0);
        if (pred == 0) goto done;
    } while ((cur == 0) || (*cur != value));

    *cur = (*node & 0xfff0000000000000) |
           (*node & 0xfffffffff) |
           ((value >> 0x24 & 0xffff) << 0x24);

done:
    sk_x_000605F8(&lock);
    sk_x_00060650();
    *node = 0;
    if (sk_g_006B2560 != 0) {
        ((void (*)(uint64_t *, int))sk_g_006B2560)(node, 0);
    }
    return;
}

/* FUN_0005c0ac @ 0x0005c0ac   (est. registry_stack_pop)
 * Ghidra: void FUN_0005c0ac(void)
 * Pops the head of the xrt registry's tagged stack at +0x20 (the nonzero-mode
 * stack pushed by sk_f_0005be84). CAS-verifies the head still matches, installs
 * the unwrapped next pointer as the new head, clears the popped node, and
 * returns. Empty stack returns immediately; wrapping addresses trap.
 * Confidence: medium
 * Notes: registry +0x20 is the stack head; next is masked to its 36-bit pointer. */
uint64_t sk_f_0005c0ac(void)
{
    uint64_t registry;
    uint64_t *node;
    uint64_t next;

    registry = sk_f_0005acac(0x6b2568, 1, 1);
    while (true) {
        node = *(uint64_t **)(registry + 0x20);
        if (node == 0) {
            return 0;
        }
        if ((node + 0x2f < node) ||
            (next = *node & 0xfffffffff, next + 0x178 < next)) break;
        if (*(uint64_t **)(registry + 0x20) == node) {
            *(uint64_t *)(registry + 0x20) = next;
            *node = 0;
            return next;
        }
    }
    SoftwareBreakpoint(0x5519, 0x5c11c);
}

/* FUN_0005c16c @ 0x0005c16c   (est. xrt_registry_global_set_and_init)
 * Ghidra: void FUN_0005c16c(void)
 * Stores the image-base registry pointer 0x6b2570 into the global at 0x64db50,
 * then runs the registry initializer sk_f_0005ba5c.
 * Confidence: low
 * Notes: sk_g_0064DB50 is a writable global (Ghidra "read-only" warning is an
 *        artifact of overlapping symbols); 0x6b2570 is another image-base ptr. */
void sk_f_0005c16c(void)
{
    sk_g_0064DB50 = 0x6b2570;
    sk_f_0005ba5c(0);   /* decompiler dropped the enqueue-entry arg here */
    return;
}


/* FUN_0005c184 @ 0x0005c184   (est. thread_buffer_append)
 * Ghidra: ulong FUN_0005c184(undefined8 param_1,ulong param_2)
 * Appends `count` bytes from the source buffer `src` to the end of the
 * current thread's byte stack buffer (capacity 0x78), growing its recorded
 * length by the number of bytes appended. Returns the number of bytes written
 * (0 when there is no room). On overflow it fails hard through a debug
 * breakpoint that never returns.
 * Confidence: medium
 * Notes: current-thread lookup via tpidr_el0 -> thread registry; the acquire
 *        (FUN_0005cb9c) / release (FUN_0005ce54) helpers bracket the update;
 *        FUN_00117cc4 is the byte copy; SoftwareBreakpoint(0x5519,0x5c278). */
uint64_t sk_f_0005c184(uint64_t src, uint64_t count)
{
    uint64_t *buffer;
    uint8_t *thread_reg;
    long *node;
    uint64_t *candidate;
    uint64_t *result;
    uint64_t written;

    thread_reg = (uint8_t *)tpidr_el0;
    node = *(long **)*(long **)(thread_reg + 0x10);
    if (node == (long *)0x0) {
        result = (uint64_t *)0x0;
    }
    else {
        candidate = (uint64_t *)0x0;
        do {
            result = (uint64_t *)node[3];
            if ((int)node[2] != 5 || (int)node[1] != 1) {
                result = candidate;
            }
            node = (long *)*node;
            candidate = result;
        } while (node != (long *)0x0);
    }
    candidate = result + 0x10;
    if (candidate <= result + 0x12) {
        sk_f_0005cb9c(candidate);
        if ((count < 0x79) && (*result <= 0x78 - count)) {
            written = (long)result + *result + 8;
            sk_x_00117CC4(written, src, count);
            if (written + count < written) goto fail;
            *result = *result + count;
        }
        else {
            count = 0;
        }
        if (result <= result + 0x12) {
            sk_f_0005ce54(candidate);
            return count;
        }
    }
fail:
    SoftwareBreakpoint(0x5519, 0x5c278);
}

/* FUN_0005c278 @ 0x0005c278   (est. thread_buffer_consume)
 * Ghidra: ulong FUN_0005c278(ulong param_1,ulong param_2)
 * Consumes the tail `count` bytes of the current thread's byte stack buffer,
 * copying them out to `dst` and shrinking the recorded length accordingly.
 * Returns the number of bytes consumed (0 when the buffer holds fewer). On
 * any bounds/overflow violation it fails hard through a never-returning
 * debug breakpoint.
 * Confidence: medium
 * Notes: shares the thread-registry lookup and the acquire/release helpers
 *        (FUN_0005cb9c / FUN_0005ce54); FUN_00117cc4 is the byte copy and
 *        thunk_FUN_00114330 the post-read cleanup; SoftwareBreakpoint(0x5519,
 *        0x5c324). */
uint64_t sk_f_0005c278(uint64_t dst, uint64_t count)
{
    uint64_t *src_ptr;
    uint8_t *thread_reg;
    long *node;
    uint64_t *candidate;
    uint64_t *result;
    uint64_t new_len;

    thread_reg = (uint8_t *)tpidr_el0;
    node = *(long **)*(long **)(thread_reg + 0x10);
    if (node == (long *)0x0) {
        result = (uint64_t *)0x0;
    }
    else {
        candidate = (uint64_t *)0x0;
        do {
            result = (uint64_t *)node[3];
            if ((int)node[2] != 5 || (int)node[1] != 1) {
                result = candidate;
            }
            node = (long *)*node;
            candidate = result;
        } while (node != (long *)0x0);
    }
    candidate = result + 0x10;
    if (candidate <= result + 0x12) {
        sk_f_0005cb9c(candidate);
        new_len = *result - count;
        if (*result < count) {
            count = 0;
        }
        else {
            src_ptr = (uint64_t *)((long)(result + 1) + new_len);
            if (((0x78U - new_len < count || candidate < src_ptr) || src_ptr < result + 1) ||
                (sk_x_00117CC4(dst, src_ptr, count), dst + count < dst)) goto fail;
            sk_x_00114330(src_ptr, count);
            *result = *result - count;
        }
        if (result <= result + 0x12) {
            sk_f_0005ce54(candidate);
            return count;
        }
    }
fail:
    SoftwareBreakpoint(0x5519, 0x5c324);
}






















/* SK11 slice 0x0005acac-0x0005fd24 — worker part4 (addresses 0005c558..0005ca20).
 * English-first faithful transcriptions of the cL4 "xrt" timebase / error-code /
 * capability-dispatch helpers. Ground truth: Ghidra FUN_ names + addresses. */





/* FUN_0005c588 @ 0x0005c588   (est. error_code_table_dump)
 * Ghidra: void FUN_0005c588(void)
 * Emits the L4 error-code string table. It forwards the "L4_ErrorCode %zu"
 * format string (s_L4_ErrorCode__zu_005a8c7b) along with a 0x20 element size
 * and 0x1f (31) element count through sk_f_0005b824, which performs the actual
 * formatted table output. Takes no arguments and returns nothing.
 * Confidence: medium
 * Notes: `&stack0x00000018` is a stack scratch buffer; s_L4_ErrorCode__zu_005a8c7b
 * is referenced as sk_str_005a8c7b. */
void sk_f_0005c588(void)
{
    uint8_t scratch[0x20];   /* &stack0x00000018: scratch buffer for table dump */
    sk_f_0005b824((uint64_t)(uintptr_t)scratch, 0x20, 0x1f, sk_str_005a8c7b);
    return;
}



/* FUN_0005c5b4 @ 0x0005c5b4   (est. capability_object_invoke)
 * Ghidra: long FUN_0005c5b4(undefined8 param_1)
 * Obtains a per-CPU/object context via FUN_00034F70; when non-null, it retrieves
 * the 16-byte capability object descriptor {ctx, vtable} from FUN_0004ba18 and
 * dispatches a method through the vtable stored at [vtable] with (ctx, arg,
 * ctx_len, ctx_len, 0). If the call returns non-zero, the context is released
 * via FUN_004B23D8 and zero is returned; otherwise the original context is
 * returned. Returns the context handle, or 0 on dispatch failure.
 * Confidence: medium
 * Notes: FUN_0004ba18's 16-byte (x0:x1) return is captured via the out-buffer
 * convention used by sibling slices; the method pointer is *(uint64_t*)vtable. */
int64_t sk_f_0005c5b4(uint64_t arg)
{
    int64_t ctx;
    uint64_t ep[2];                 /* FUN_0004ba18 16-byte return: {ctx, vtable} */
    uint64_t (*invoke)(uint64_t, uint64_t, int64_t, int64_t, uint64_t);

    ctx = (int64_t)sk_x_00034F70();
    if (ctx != 0) {
        sk_x_0004BA18((uint64_t)(uintptr_t)ep);
        invoke = *(uint64_t (*)(uint64_t, uint64_t, int64_t, int64_t, uint64_t))ep[1];
        if (invoke(ep[0], arg, ctx, ctx, 0) != 0) {
            sk_x_004B23D8((uint64_t)ctx);
            ctx = 0;
        }
    }
    return ctx;
}

/* FUN_0005c614 @ 0x0005c614   (est. capability_object_invoke_release)
 * Ghidra: void FUN_0005c614(undefined8 param_1)
 * Dispatches a method on the capability object from FUN_0004ba18: the method
 * pointer is read from the vtable at offset +0x10 and invoked with the object
 * context and arg. The object is then released via FUN_004B23D8(arg).
 * Returns nothing.
 * Confidence: medium
 * Notes: FUN_0004ba18's 16-byte (x0:x1) return is captured via the out-buffer
 * convention; method pointer = *(uint64_t*)(vtable + 0x10). */
void sk_f_0005c614(uint64_t arg)
{
    uint64_t ep[2];                 /* FUN_0004ba18 16-byte return: {ctx, vtable} */
    uint64_t (*invoke)(uint64_t, uint64_t);

    sk_x_0004BA18((uint64_t)(uintptr_t)ep);
    invoke = *(uint64_t (*)(uint64_t, uint64_t))(ep[1] + 0x10);
    invoke(ep[0], arg);
    sk_x_004B23D8(arg);
    return;
}

/* FUN_0005c650 @ 0x0005c650   (est. timebase_info_get)
 * Ghidra: void FUN_0005c650(undefined8 *param_1, ulong param_2)
 * Initializes the global timebase table entries 1..3 (skipping entry 0) via
 * sk_f_0005c764, then sets up a local timebase entry for the requested timebase
 * id (timebase_id) and extracts its conversion factors. The two 64-bit frequency
 * factors (entry+0x30 and entry+0x38) are stored half-swapped (a 16-byte EXT #8
 * rotation) into out[0]/out[1], and out[2] receives the timebase id
 * (timebase_id & 0xffffffff). Returns nothing.
 * Confidence: medium
 * Notes: Timebase table base 0x64db60 (80-byte strides). sk_f_0005c86c result is
 * discarded; only the entry factors written by sk_f_0005c764 are read back. */
void sk_f_0005c650(uint64_t *out, uint64_t timebase_id)
{
    uint64_t entry[10] = {0};       /* 0x50-byte local timebase entry */
    uint64_t idx;
    uint64_t table_addr;
    uint64_t lo, hi;

    idx = 0;
    table_addr = 0x64db60;
    do {
        if (((uint32_t)idx - 1 & 0xff) < 3) {
            sk_f_0005c764((uint32_t)idx & 0xff, (uint8_t *)table_addr);
        }
        idx = idx + 1;
        table_addr = table_addr + 0x50;
    } while (idx != 4);

    sk_f_0005c764(timebase_id, (uint8_t *)entry);
    sk_f_0005c86c(timebase_id, (uint8_t (*)[16])entry, (uint8_t (*)[16])0, 1);
    lo = entry[6];                  /* local_50 = entry[0x30] */
    hi = entry[7];                  /* uStack_48 = entry[0x38] */
    /* 16-byte EXT #8 half-swap: result = {old_hi, old_lo}. */
    out[0] = hi;
    out[1] = lo;
    out[2] = timebase_id & 0xffffffff;
    return;
}

/* FUN_0005c710 @ 0x0005c710   (est. timebase_table_init)
 * Ghidra: void FUN_0005c710(void)
 * Initializes the global timebase table entries 1..3 (skipping entry 0) at base
 * 0x64db60 with 80-byte strides by calling sk_f_0005c764 for each. Takes no
 * arguments and returns nothing.
 * Confidence: medium
 * Notes: Loop condition ((idx-1)&0xff)<3 selects indices 1,2,3; entry 0 is
 * intentionally not set up here. */
void sk_f_0005c710(void)
{
    uint64_t idx = 0;
    uint64_t table_addr = 0x64db60;

    do {
        if (((uint32_t)idx - 1 & 0xff) < 3) {
            sk_f_0005c764((uint32_t)idx & 0xff, (uint8_t *)table_addr);
        }
        idx = idx + 1;
        table_addr = table_addr + 0x50;
    } while (idx != 4);
    return;
}

/* FUN_0005c764 @ 0x0005c764   (est. timebase_setup)
 * Ghidra: void FUN_0005c764(ulong param_1, long param_2)
 * Sets up a timebase entry (entry, a caller-provided 0x50-byte buffer) for the
 * timebase id timebase_id. It bounds-checks the id against the global table
 * [0x64db60, 0x64dca0), copies the 0x50-byte template via FUN_00117CC4, and
 * returns early if the entry is already initialized (flag==1 and freq!=0). For
 * timebases 1..3 it reads the source frequency (FUN_00055B20), computes the
 * reduced tick/ns ratios via Euclid's GCD with 1e9, stores them at entry+0x30
 * and entry+0x38, and calls sk_f_0005cb24 to convert 0xffffffffffffffff ticks.
 * For timebase 0 it panics "invalid timebase %u".
 * Confidence: medium
 * Notes: s_invalid_timebase__u_005bc6d7 referenced as sk_str_005bc6d7; the GCD loop
 * is a faithful transcription of the decompiled Euclid reduction. */
void sk_f_0005c764(uint64_t timebase_id, uint8_t *entry)
{
    int64_t offset;
    uint64_t base, end, a, b, gcd, freq;
    uint64_t freq_ratio, ns_ratio;

    offset = (int64_t)((timebase_id & 0xffffffff) * 0x50);
    base = (uint64_t)offset + 0x64db60;
    end = (uint64_t)offset + 0x64dbb0;
    if ((base < 0x64db60 || 0x64dca0 < end) || end < base) {
        SoftwareBreakpoint(0x5519, 0x5c858);
    }
    sk_x_00117CC4((uint64_t)entry, base, 0x50);
    if ((*(uint8_t *)(entry + 0x20) == 0x01) && (*(int64_t *)(entry + 0x28) != 0)) {
        return;
    }
    if ((int)timebase_id - 1U < 3) {
        freq = sk_x_00055B20();
        *(uint64_t *)(entry + 0x28) = freq;
        /* Euclid GCD of freq and 1e9; gcd holds the GCD on exit. */
        a = freq;
        b = 1000000000;
        do {
            gcd = b;
            b = 0;
            if (gcd != 0) {
                b = a / gcd;
            }
            b = a - b * gcd;
            a = gcd;
        } while (b != 0);
        freq_ratio = 0;
        if (gcd != 0) {
            freq_ratio = freq / gcd;
        }
        ns_ratio = 0;
        if (gcd != 0) {
            ns_ratio = 1000000000 / gcd;
        }
        *(uint64_t *)(entry + 0x30) = freq_ratio;
        *(uint64_t *)(entry + 0x38) = ns_ratio;
        sk_f_0005cb24(timebase_id, 0xffffffffffffffff, (uint8_t (*)[16])(entry + 0x10), 0);
        return;
    }
    /* invalid timebase: noreturn panic */
    sk_f_0005b190(0, sk_str_005bc6d7);
    __builtin_unreachable();
}

/* FUN_0005c86c @ 0x0005c86c   (est. timebase_duration_to_ticks)
 * Ghidra: long FUN_0005c86c(undefined8 param_1, undefined1 (*param_2)[16], undefined1 (*param_3)[16], ulong param_4)
 * Converts a 128-bit target duration (target, {lo,hi}) into ticks for the
 * timebase id timebase_id. It sets up a local timebase entry via sk_f_0005c764,
 * then compares the target against the entry's reference value with the 128-bit
 * comparison helper FUN_0019AF88. When the target is below the reference it
 * computes the difference (optionally via FUN_0019AF14 unless flags&1 is set)
 * and scales it by the entry's conversion factors. When the target is at/above
 * the reference it stores the computed difference into out (if non-null) and
 * returns -1.
 * Confidence: medium
 * Notes: 128-bit helper returns are captured via the out-buffer convention;
 * sk_str/global references as per prelude. */
int64_t sk_f_0005c86c(uint64_t timebase_id, uint8_t (*target)[16], uint8_t (*out)[16],
                      uint64_t flags)
{
    uint8_t entry[0x50] = {0};
    uint64_t diff[2];
    uint64_t now_lo, now_hi, b_lo, b_hi;
    uint64_t scale_lo, scale_hi, freq_div;
    int cmp;
    int64_t result;

    sk_f_0005c764(timebase_id, (uint8_t *)entry);
    now_lo = *(uint64_t *)&entry[0x00];   /* local_90 */
    now_hi = *(uint64_t *)&entry[0x08];   /* uStack_88 */
    b_lo   = *(uint64_t *)&entry[0x10];   /* local_80 */
    b_hi   = *(uint64_t *)&entry[0x18];   /* uStack_78 */
    scale_lo = *(uint64_t *)&entry[0x28]; /* local_68 */
    scale_hi = *(uint64_t *)&entry[0x30]; /* local_60 */
    freq_div = *(uint64_t *)&entry[0x38]; /* uStack_58 */

    cmp = (int)sk_x_0019AF88(*(uint64_t *)*target, *(uint64_t *)(*target + 8), b_lo, b_hi);
    if (cmp < 1) {
        diff[0] = *(uint64_t *)*target;
        diff[1] = *(uint64_t *)(*target + 8);
        if ((flags & 1) == 0) {
            sk_x_0019AF14(*(uint64_t *)*target, *(uint64_t *)(*target + 8), now_lo, now_hi,
                          (uint64_t)(uintptr_t)diff);
        }
        result = 0;
        if (freq_div != 0) {
            result = (int64_t)((scale_hi * diff[1]) / freq_div);
        }
        result = result + (int64_t)(scale_lo * diff[0]);
    } else {
        if (out != NULL) {
            sk_x_0019AF14(*(uint64_t *)*target, *(uint64_t *)(*target + 8), b_lo, b_hi,
                          (uint64_t)(uintptr_t)*out);
        }
        result = -1;
    }
    return result;
}

/* FUN_0005c924 @ 0x0005c924   (est. timebase_read)
 * Ghidra: long FUN_0005c924(undefined8 param_1)
 * Reads the current timebase value for the given timebase id. For id 3 it
 * returns the value from FUN_00055AFC directly. For ids 1 and 2 it repeatedly
 * reads sk_f_0005ca20(timebase_id) until two consecutive reads agree, then
 * returns the older read plus the value from FUN_00055AFC (a stable timestamp).
 * For any other id it panics "invalid timebase %u".
 * Confidence: medium
 * Notes: s_invalid_timebase__u_005bc6d7 referenced as sk_str_005bc6d7; the loop is
 * a software-debounced tick read. */
int64_t sk_f_0005c924(uint64_t timebase_id)
{
    int64_t cur, prev, ext;

    if ((int)timebase_id == 3) {
        return (int64_t)sk_x_00055AFC();
    }
    cur = (int64_t)sk_f_0005ca20(timebase_id);
    if (((int)timebase_id - 1U & 0xff) < 2) {
        do {
            prev = cur;
            ext = (int64_t)sk_x_00055AFC();
            cur = (int64_t)sk_f_0005ca20(timebase_id);
        } while (cur != prev);
        return prev + ext;
    }
    /* invalid timebase: noreturn panic */
    sk_f_0005b190(0, sk_str_005bc6d7);
    __builtin_unreachable();
}

/* FUN_0005ca20 @ 0x0005ca20   (est. timebase_get_tick)
 * Ghidra: undefined8 FUN_0005ca20(uint param_1)
 * Returns the current tick value for the timebase id timebase_id from the global
 * timebase table (base 0x64db60, 80-byte entries). It validates the id bounds,
 * and if the table slot has no tick pointer yet, resolves it from the per-cpu
 * descriptor (FUN_0005ad24) plus the commpage base (FUN_0005ace4), storing the
 * resolved tick pointer at table[+0x40] and marking it valid (flag byte at
 * +0x48). Returns 0 if no tick source can be resolved. When the flag is set it
 * verifies the commpage version fields before returning the tick.
 * Confidence: medium
 * Notes: FUN_0005ace4 is void-returning in its own decompile; its x0 (commpage
 * base) is relied on here, matching the decompiler's model. */
uint64_t sk_f_0005ca20(uint32_t timebase_id)
{
    uint64_t offset;
    uint64_t *tick_ptr;
    uint64_t *lo_ptr, *hi_ptr;
    uint64_t tick, desc;
    uint64_t commpage_a, commpage_b;

    offset = (uint64_t)timebase_id * 0x50;
    if ((offset + 0x64db60 < 0x64db60 || 0x64dca0 < offset + 0x64dbb0) ||
        offset + 0x64dbb0 < offset + 0x64db60) {
        goto bounds_fail;
    }
    tick_ptr = *(uint64_t **)(offset + 0x64dba0);
    if (tick_ptr == NULL) {
        desc = sk_f_0005ad24();
        if (desc == 0) {
retry:
            tick_ptr = *(uint64_t **)(offset + 0x64dba0);
            if (tick_ptr == NULL) {
                return 0;
            }
        } else {
            if (timebase_id == 2) {
                if (((*(uint8_t *)(desc + 8) >> 1) & 1) == 0) {
                    goto retry;
                }
                commpage_a = sk_f_0005ace4();
                lo_ptr = (uint64_t *)(commpage_a + 0x20);
                hi_ptr = (uint64_t *)(commpage_a + 0x28);
            } else {
                if ((timebase_id != 1) || ((*(uint8_t *)(desc + 8) & 1) == 0)) {
                    goto retry;
                }
                commpage_a = sk_f_0005ace4();
                lo_ptr = (uint64_t *)(commpage_a + 0x18);
                hi_ptr = (uint64_t *)(commpage_a + 0x20);
            }
            if (hi_ptr < lo_ptr) {
                goto bounds_fail;
            }
            *(uint64_t **)(offset + 0x64dba0) = lo_ptr;
            *(uint8_t *)(offset + 0x64dba8) = 1;
        }
    }
    tick = *tick_ptr;
    if (*(uint8_t *)(offset + 0x64dba8) == 0x01) {
        commpage_a = sk_f_0005ace4();
        commpage_b = sk_f_0005ace4();
        if (*(int *)(commpage_a + 4) != *(int *)commpage_b) {
            sk_x_004B68A4();
bounds_fail:
            SoftwareBreakpoint(0x5519, 0x5cb18);
        }
    }
    return tick;
}


/* Worker SK11.P5 — cL4 "xrt" thread-runtime / sync-primitive slice.
 * Functions 0005cb18..0005d134. All sk_f_/sk_x_/sk_g_/sk_str_ symbols are
 * declared in the shared prelude; nothing here re-declares them. */

/* Real linker symbol for the shared-cache record array (7-long records). */
extern int64_t __shared_cache[];



/* FUN_0005cb18 @ 0x0005cb18   (est. set_xrt_global_byte)
 * Ghidra: void FUN_0005cb18(undefined1 param_1)
 * Stores a single byte into the global flag at image base 0x64db58. Trivial
 * one-byte runtime-flag setter with no other side effects.
 * Confidence: medium
 * Notes: Ghidra warns this write targets a read-only-address (ram,0x64db58);
 *   DAT_0064db58 -> sk_g_0064db58. */
void sk_f_0005cb18(uint8_t value)
{
    *(uint8_t *)&sk_g_0064db58 = value;
    return;
}

/* FUN_0005cb24 @ 0x0005cb24   (est. cap_record_divide)
 * Ghidra: void FUN_0005cb24(undefined8 param_1,ulong param_2,undefined1 (*param_3) [16],ulong param_4)
 * Fetches an 8-word record via the dispatch-record helper, then performs a
 * two-part division of the dividend producing a {quotient,remainder} pair
 * packed into a 16-byte result written through the caller-supplied pointer.
 * When bit 0 of the flags is clear the pair is refined by the 128-bit
 * segcmd helper before being stored.
 * Confidence: medium
 * Notes: FUN_0005c764 -> sk_f_0005c764 (fills local record); FUN_0019ae9c ->
 *   sk_x_0019AE9C (16-byte refinement helper); the 8-word record fields are
 *   renamed English. */
void sk_f_0005cb24(uint64_t token, uint64_t dividend, uint8_t (*out)[16], uint64_t flags)
{
    uint64_t rec0;
    uint64_t rec1;
    uint64_t rec2;
    uint64_t rec3;
    uint64_t rec4;
    uint64_t divisor_hi;
    uint64_t divisor_lo;
    int64_t multiply;
    uint64_t scratch0;
    uint64_t scratch1;
    uint64_t quotient;
    uint64_t remainder;
    sk_u128_t result;

    multiply = 0;
    divisor_lo = 0;
    scratch1 = 0;
    scratch0 = 0;
    rec3 = 0;
    rec2 = 0;
    divisor_hi = 0;
    rec4 = 0;
    rec1 = 0;
    rec0 = 0;
    sk_f_0005c764(token, (uint8_t *)&rec0);
    quotient = 0;
    if (divisor_hi != 0) {
        quotient = dividend / divisor_hi;
    }
    remainder = 0;
    if (divisor_lo != 0) {
        remainder = multiply * (dividend - quotient * divisor_hi) / divisor_lo;
    }
    result.hi = remainder;
    result.lo = quotient;
    if ((flags & 1) == 0) {
        result = sk_x_0019AE9C(quotient, remainder, rec0, rec1);
    }
    *(sk_u128_t *)*out = result;
    return;
}

/* FUN_0005cb9c @ 0x0005cb9c   (est. lock_acquire)
 * Ghidra: undefined8 FUN_0005cb9c(ulong *param_1)
 * Fast-path lock acquisition for the sync primitive at param_1. If the lock is
 * already owned by the current thread and recursion is allowed, the recursion
 * counters are adjusted. Otherwise the lock is claimed by stamping the owner
 * tag; a busy lock falls through to the slow recursive acquire.
 * Confidence: medium
 * Notes: FUN_00060524 -> sk_x_00060524 (current thread); FUN_0005afe8 ->
 *   sk_f_0005afe8 (error/record formatting); FUN_0005cc3c -> sk_f_0005cc3c
 *   (slow recursive acquire); SoftwareBreakpoint 0x5519/0x5cc3c. */
uint64_t sk_f_0005cb9c(uint64_t *lock)
{
    uint64_t owner;
    uint64_t thread;

    owner = *lock;
    thread = sk_x_00060524();
    if (thread + 0x178 < thread) {
        SoftwareBreakpoint(0x5519, 0x0005cc3c);
    }
    if ((((uint32_t)(thread >> 0xe) ^ (uint32_t)owner) & 0xffffff) == 0) {
        if (*(int16_t *)((char *)lock + 0xe) != 0) {
            *(int16_t *)((char *)lock + 0xe) = *(int16_t *)((char *)lock + 0xe) - 1;
            *(int16_t *)((char *)lock + 0xc) = *(int16_t *)((char *)lock + 0xc) + 1;
            goto acquired;
        }
    } else {
        do {
            if (owner != 0) goto contend;
            owner = *lock;
        } while (owner != 0);
        *lock = thread >> 0xe & 0xffffff;
        if (*(int16_t *)((char *)lock + 0xc) == 0) {
        acquired:
            sk_f_0005afe8(thread, (uint64_t)lock, 0);
            return 0;
        }
    }
contend:
    sk_f_0005cc3c(lock, 0);
    return 0;
}

/* FUN_0005cc3c @ 0x0005cc3c   (est. lock_acquire_recursive)
 * Ghidra: undefined8 FUN_0005cc3c(ulong *param_1,undefined8 param_2)
 * Slow/recursive mutex acquisition. Stamps the owner tag and the per-CPU
 * quantum into the current thread; panics if the recursion limit is exceeded
 * ("mutex recursion limit exceeded"). Otherwise spins through the wait chain,
 * resolving each waiter object and dispatching to the per-lock acquire op.
 * Confidence: medium
 * Notes: FUN_00060524 -> sk_x_00060524; FUN_0005dc4c -> sk_f_0005dc4c (per-cpu
 *   array); FUN_000606b0 -> sk_x_000606B0 (phys-to-object); FUN_0005dc8c ->
 *   sk_f_0005dc8c (acquire dispatch); FUN_0005b190 -> sk_f_0005b190 (noreturn
 *   panic); FUN_0005afe8 -> sk_f_0005afe8; DAT_006ad900 -> sk_g_006ad900;
 *   s_mutex_recursion_limit_exceeded_005bc73c -> sk_str_005bc73c. */
uint64_t sk_f_0005cc3c(uint64_t *lock, uint64_t arg2)
{
    uint32_t idx;
    uint32_t rc;
    uint64_t thread;
    uint64_t cpu_array;
    uint64_t quantum;
    uint64_t cur;
    uint64_t state;
    uint64_t owner;
    uint64_t next;
    uint64_t spin;

    idx = (uint32_t)lock >> 4 & 0xf;
    if ((uint8_t)lock[1] != 0) {
        idx = (uint8_t)lock[1] - 1;
    }
    thread = sk_x_00060524();
    cpu_array = sk_f_0005dc4c(idx & 0xff);
    quantum = sk_g_006ad900 >> 10;
    cur = sk_x_00060524();
    *(uint64_t *)(cur + 0x78) = quantum;
    state = thread >> 0xe & 0xffffff;
    owner = *lock;
    if (owner == 0) {
        *lock = state;
    }
    if ((owner != 0) && ((((uint32_t)owner ^ (uint32_t)(thread >> 0xe)) & 0xffffff) == 0)) {
        cpu_array = sk_x_00060524();
        sk_f_0005b190(cpu_array, sk_str_005bc73c);
    }
    if (owner != 0) {
        spin = 0;
        do {
            while (((uint32_t)owner >> 0x18 & 1) == 0) {
                next = *lock;
                if (next == owner) {
                    *lock = owner | 0x1000000;
                    break;
                }
                owner = next;
                if ((next == 0) && (owner = *lock, owner == 0)) {
                    *lock = spin | state;
                    goto done;
                }
            }
            owner = sk_x_000606B0((uint32_t)owner & 0xffffff);
            if (owner + 0x178 < owner) {
                SoftwareBreakpoint(0x5519, 0x0005cdac);
            }
            rc = sk_f_0005dc8c(idx & 0xff, (uint64_t)(uintptr_t)lock, (uint64_t)(uintptr_t)cpu_array, owner, arg2);
            if (rc == 1) {
                spin = 0;
            } else if (rc == 2) {
                spin = 0x1000000;
            } else if (rc == 3) {
                return 0;
            }
            cpu_array = sk_f_0005dc4c(idx & 0xff);
            owner = *lock;
        } while (owner != 0);
        *lock = spin | state;
    }
done:
    cpu_array = sk_x_00060524();
    sk_f_0005afe8(cpu_array, (uint64_t)lock, 0);
    return 1;
}

/* FUN_0005cdbc @ 0x0005cdbc   (est. lock_try)
 * Ghidra: undefined8 FUN_0005cdbc(ulong *param_1)
 * Non-blocking lock attempt. If the lock is already owned by this thread and
 * recursion is allowed the counters are updated and success is reported. A
 * free lock is claimed immediately; a busy lock returns failure without
 * waiting.
 * Confidence: medium
 * Notes: FUN_00060524 -> sk_x_00060524; FUN_0005afe8 -> sk_f_0005afe8;
 *   SoftwareBreakpoint 0x5519/0x5ce54. */
uint64_t sk_f_0005cdbc(uint64_t *lock)
{
    uint64_t owner;
    uint64_t thread;

    owner = *lock;
    thread = sk_x_00060524();
    if (thread + 0x178 < thread) {
        SoftwareBreakpoint(0x5519, 0x0005ce54);
    }
    if ((((uint32_t)(thread >> 0xe) ^ (uint32_t)owner) & 0xffffff) == 0) {
        if (*(int16_t *)((char *)lock + 0xe) != 0) {
            *(int16_t *)((char *)lock + 0xe) = *(int16_t *)((char *)lock + 0xe) - 1;
            *(int16_t *)((char *)lock + 0xc) = *(int16_t *)((char *)lock + 0xc) + 1;
            goto acquired;
        }
    } else {
        do {
            if (owner != 0) {
                return 0;
            }
            owner = *lock;
        } while (owner != 0);
        *lock = thread >> 0xe & 0xffffff;
        if (*(int16_t *)((char *)lock + 0xc) == 0) {
        acquired:
            sk_f_0005afe8(thread, (uint64_t)lock, 0);
            return 1;
        }
    }
    return 0;
}

/* FUN_0005ce54 @ 0x0005ce54   (est. lock_release)
 * Ghidra: void FUN_0005ce54(undefined8 *param_1)
 * Releases a mutex held by the current thread. Panics if the caller does not
 * own the lock ("tried to unlock lock I did not own"). On the final recursive
 * release the owner is cleared with a release barrier and any pending waiter
 * is dispatched via the per-lock wake op.
 * Confidence: medium
 * Notes: FUN_00060524 -> sk_x_00060524; FUN_0005b05c -> sk_f_0005b05c (release
 *   record); FUN_0005b190 -> sk_f_0005b190 (noreturn panic); FUN_0005dd70 ->
 *   sk_f_0005dd70 (wake dispatch); s_tried_to_unlock_lock_I_did_not_o_005bc719
 *   -> sk_str_005bc719; in_xzr treated as 0. */
void sk_f_0005ce54(uint64_t *lock)
{
    uint32_t idx;
    uint64_t owner;
    uint64_t thread;

    owner = *lock;
    thread = sk_x_00060524();
    if ((((uint32_t)(thread >> 0xe) ^ (uint32_t)owner) & 0xffffff) != 0) {
        sk_f_0005b190(0, sk_str_005bc719);
    }
    thread = sk_x_00060524();
    sk_f_0005b05c(thread, (uint64_t)lock);
    if (*(int16_t *)((char *)lock + 0xc) == 0) {
        owner = *lock;
        *lock = 0;
        LORelease();
        if (((uint32_t)owner >> 0x18 & 1) != 0) {
            idx = (uint32_t)lock >> 4 & 0xf;
            if (*(uint8_t *)(lock + 1) != 0) {
                idx = *(uint8_t *)(lock + 1) - 1;
            }
            sk_f_0005dd70(idx & 0xff, (uint64_t)lock, 3, 0);
            return;
        }
    } else {
        *(int16_t *)((char *)lock + 0xc) = *(int16_t *)((char *)lock + 0xc) - 1;
        *(int16_t *)((char *)lock + 0xe) = *(int16_t *)((char *)lock + 0xe) + 1;
    }
    return;
}

/* FUN_0005cf08 @ 0x0005cf08   (est. lock_set_mode)
 * Ghidra: void FUN_0005cf08(undefined8 *param_1,undefined2 param_2)
 * Stores the mode field at lock+0xe and clears the owner tag, re-arming the
 * sync primitive for fresh acquisition.
 * Confidence: medium
 * Notes: none. */
void sk_f_0005cf08(uint64_t *lock, uint16_t mode)
{
    *(uint16_t *)((char *)lock + 0xe) = mode;
    *lock = 0;
    return;
}



/* FUN_0005cf18 @ 0x0005cf18   (est. lock_record_switch)
 * Ghidra: void FUN_0005cf18(long param_1,undefined8 param_2,undefined8 param_3)
 * Preserves the frame-pointer/return-address pair and the unmodeled x8 register
 * below the caller's stack pointer, then invokes the thread-switch helper.
 * Confidence: medium
 * Notes: unaff_x29/unaff_x30 are uninitialized register artifacts preserved
 *   verbatim; FUN_000603ac -> sk_x_000603AC (thread switch). */
void sk_f_0005cf18(int64_t sp, uint64_t arg2, uint64_t arg3)
{
    uint64_t saved_x29;
    uint64_t saved_x30;

    *(uint64_t *)(sp + -0x10) = saved_x29;
    *(uint64_t *)(sp + -8) = saved_x30;
    *(uint64_t *)(sp + -0x20) = 0;  /* saved register (unmodeled x8) */
    sk_x_000603AC(arg2, arg3);
    return;
}

/* FUN_0005cf4c @ 0x0005cf4c   (est. notify_domain)
 * Ghidra: void FUN_0005cf4c(long param_1,undefined8 param_2)
 * Walks the two-slot shared-cache domain table and, for each entry whose key
 * matches, dispatches the domain notification. Skipped entirely when a domain
 * notification is disabled via the global control flag.
 * Confidence: medium
 * Notes: __shared_cache is a real linker symbol (array of 7-long records);
 *   DAT_006ad6e8 -> sk_g_006ad6e8; FUN_0005d03c -> sk_f_0005d03c (slot
 *   notify). */
void sk_f_0005cf4c(int64_t target, uint64_t flags)
{
    int64_t count;
    int64_t *slot;

    if (((int32_t)flags == 0) || ((sk_g_006ad6e8 & 1) == 0)) {
        count = 2;
        slot = &__shared_cache;
        do {
            if (*slot == target) {
                sk_f_0005d03c(slot, flags);
            }
            slot = slot + 7;
            count = count - 1;
        } while (count != 0);
    }
    return;
}

/* FUN_0005d03c @ 0x0005d03c   (est. notify_domain_slot)
 * Ghidra: void FUN_0005d03c(long *param_1,ulong param_2)
 * Recursively visits a domain slot's children (indexed from slot+2), then runs
 * the slot's registered callback if it has not already run for this phase. With
 * the phase flag clear, "plat"-magic slots invoke their callback directly while
 * others route through the thread-create helper; with the flag set the second
 * callback slot is invoked instead.
 * Confidence: medium
 * Notes: FUN_0005d03c recurses (sk_f_0005d03c); FUN_000600f0 -> sk_x_000600F0
 *   (thread create); &DAT_0005d130 -> (uint8_t*)&sk_g_0005d130;
 *   SoftwareBreakpoint 0x5519/0x5d130; magic 0x706c6174 = "plat". */
void sk_f_0005d03c(int64_t *slot, uint64_t flags)
{
    uint64_t count;
    uint64_t child;
    uint64_t i;

    count = slot[3];
    if (count != 0) {
        i = 0;
        do {
            child = *(uint64_t *)(slot[2] + i * 8);
            if (child != 0) {
                if (child + 0x38 < child) {
                    SoftwareBreakpoint(0x5519, 0x0005d130);
                }
                sk_f_0005d03c((int64_t *)child, flags);
                count = slot[3];
            }
            i = i + 1;
        } while (i < count);
    }
    if ((flags & 1) == 0) {
        if ((slot[4] != 1) && ((void (*)(void))slot[1] != (void (*)(void))0x0)) {
            if (*slot == 0x706c6174) {
                (*(void (*)(void))slot[1])();
            } else {
                sk_x_000600F0(0x40000, (uint8_t *)&sk_g_0005d130, slot);
            }
            slot[4] = 1;
        }
    } else if ((slot[5] != 1) && ((void (*)(void))slot[6] != (void (*)(void))0x0)) {
        (*(void (*)(void))slot[6])();
        slot[5] = 1;
    }
    return;
}

/* FUN_0005d134 @ 0x0005d134   (est. cap_lookup_slot)
 * Ghidra: undefined8 FUN_0005d134(long param_1)
 * Invokes the function pointer stored at offset +8 of the given object and
 * returns success (0).
 * Confidence: medium
 * Notes: indirect call via (obj + 8); always returns 0. */
uint64_t sk_f_0005d134(int64_t obj)
{
    (*(void (**)(void))(obj + 8))();
    return 0;
}


/* FUN_0005d154 @ 0x0005d154   (est. thread_name_or_id_get)
 * Ghidra: undefined8 FUN_0005d154(long param_1,long *param_2)
 * Resolves the component name/ID for an object. When the object pointer is null the
 * __COMPONENTNAME__ string lookup is used (via sk_x_0006562C) and the resulting id is
 * stored out. Otherwise it reads the id stored at offset 0x100 of the object and
 * validates it through the ID validator, trapping (SoftwareBreakpoint 0x5519) if the
 * id is invalid. The resolved id is written through out_id; the object id is returned.
 * Confidence: medium
 * Notes: long object + 0x20 is an 8-byte-unit offset, i.e. byte offset 0x100. */
uint64_t sk_f_0005d154(int64_t object, int64_t *out_id)
{
    int64_t resolved_id;
    uint64_t object_id;

    if (object == 0) {
        resolved_id = 0;
        object_id = sk_x_0006562C(sk_str_005bba0f, &resolved_id);
    } else {
        object_id = *(uint64_t *)(object + 0x20);
        resolved_id = sk_x_00115080(object_id);
        if (resolved_id < 0) {
            SoftwareBreakpoint(0x5519, 0x5d184);
        }
    }
    *out_id = resolved_id;
    return object_id;
}

/* FUN_0005d38c @ 0x0005d38c   (est. waitq_dequeue_refcount)
 * Ghidra: ushort FUN_0005d38c(ulong *param_1,undefined8 param_2)
 * Atomically complete a dequeue of one waiter from a wait queue: bumps the high-16-bit
 * generation/ticket counter, calls the queue callback (sk_f_0005ce54), then performs a
 * CAS-based decouple of the ticket count, returning the number of waiting entries
 * remaining (computed from the queue's count field). Uses the queue hash/index via
 * sk_f_0005dc4c / sk_f_0005dc8c. Traps (SoftwareBreakpoint 0x5519) if the queue pointer
 * would underflow. The returned ushort is the residual waiter count.
 * Confidence: medium
 * Notes: packed 64-bit queue word: low 32 bits = ticket, bits 32-47 = count,
 *        bits 48-63 = waiters. Overlapping 0xffff00000000 masks preserved. */
uint16_t sk_f_0005d38c(uint64_t *queue, uint64_t queue_token)
{
    uint32_t queue_index;
    uint32_t ticket;
    uint16_t remaining_waiters;
    uint16_t waiter_delta;
    uint16_t computed_delta;
    int32_t decouple_result;
    bool changed;
    int32_t original_ticket;
    uint64_t queue_ref;
    uint64_t queue_word;
    uint64_t previous_word;
    uint64_t current_word;

    queue_index = ((uint32_t)queue >> 4) & 0xf;
    if ((uint8_t)queue[1] != 0) {
        queue_index = (uint8_t)queue[1] - 1;
    }
    queue_ref = sk_f_0005dc4c(queue_index & 0xff);
    if (queue + 2 < queue) {
        SoftwareBreakpoint(0x5519, 0x5d38c);
    }
    queue_word = *queue;
    ticket = (int32_t)(queue_word >> 0x20) + 1;
    original_ticket = (int32_t)queue_word;
    current_word = *queue;
    if (*queue == queue_word) {
        *queue = queue_word & 0xffff000000000000ULL | queue_word & 0xffffffffULL |
                 (uint64_t)(ticket & 0xffff) << 0x20;
        sk_f_0005ce54((uint64_t *)queue_token);
        current_word = queue_word;
    } else {
        do {
            previous_word = current_word;
            ticket = (int32_t)(previous_word >> 0x20) + 1;
            current_word = *queue;
        } while (*queue != previous_word);
        *queue = previous_word & 0xffff000000000000ULL | previous_word & 0xffffffffULL |
                 (uint64_t)(ticket & 0xffff) << 0x20;
        sk_f_0005ce54((uint64_t *)queue_token);
        current_word = previous_word;
        if ((int32_t)previous_word != original_ticket) {
            waiter_delta = 1;
            goto finish;
        }
    }
    decouple_result = sk_f_0005dc8c(queue_index & 0xff, (uint64_t)(uintptr_t)queue, (uint64_t)(uintptr_t)queue_ref, 0, 1);
    if (decouple_result == 3) {
        waiter_delta = 0;
        previous_word = queue_word;
    } else {
        do {
            queue_ref = sk_f_0005dc4c(queue_index & 0xff);
            current_word = *queue;
            changed = (int32_t)current_word != original_ticket;
            waiter_delta = (uint16_t)changed;
            previous_word = current_word;
            if (changed) break;
            decouple_result = sk_f_0005dc8c(queue_index & 0xff, (uint64_t)(uintptr_t)queue, (uint64_t)(uintptr_t)queue_ref, 0, 1);
            previous_word = queue_word;
        } while (decouple_result != 3);
        ticket = (uint32_t)(current_word >> 0x20);
    }
finish:
    remaining_waiters = (uint16_t)(current_word >> 0x30);
    computed_delta = 0;
    if (waiter_delta <= remaining_waiters) {
        computed_delta = remaining_waiters - waiter_delta;
    }
    queue_word = *queue;
    if (queue_word == (current_word & 0xffff000000000000ULL | (uint64_t)(ticket & 0xffff) << 0x20 |
                       previous_word & 0xffffffffULL)) {
        *queue = (uint64_t)(ticket - 1 & 0xffff) << 0x20 | (uint64_t)computed_delta << 0x30 |
                 previous_word & 0xffffffffULL;
    } else {
        do {
            remaining_waiters = (uint16_t)(queue_word >> 0x30);
            computed_delta = 0;
            if (waiter_delta <= remaining_waiters) {
                computed_delta = remaining_waiters - waiter_delta;
            }
            current_word = queue_word + 0xffff00000000ULL;
            previous_word = queue_word & 0xffffffffULL;
            changed = *queue != queue_word;
            queue_word = *queue;
        } while (changed);
        *queue = current_word & 0xffff00000000ULL | (uint64_t)computed_delta << 0x30 |
                 previous_word;
    }
    sk_f_0005cb9c((uint64_t *)queue_token);
    return waiter_delta;
}

/* FUN_0005d394 @ 0x0005d394   (est. waitq_enqueue_refcount)
 * Ghidra: void FUN_0005d394(ulong *param_1,int param_2)
 * Atomically enqueue one waiter on a wait queue: increments the low-32-bit ticket and
 * the high-16-bit waiter count (optionally clamped to the queue capacity when
 * clamp_to_capacity is nonzero... see Notes), retrying with a CAS loop if the queue
 * word changes. When the waiter count reaches capacity it invokes sk_f_0005dd70 to
 * park/wake the queue. Traps (SoftwareBreakpoint 0x5519) if the queue pointer would
 * underflow.
 * Confidence: medium
 * Notes: packed 64-bit queue word; bits 32-47 are the count compared against the
 *        waiter-count field. Following the decompile: when param_2==0 the count field
 *        is clamped to capacity (uVar7 wake selector 4), otherwise it is left
 *        unbounded (selector 6). */
void sk_f_0005d394(uint64_t *queue, int32_t clamp_to_capacity)
{
    bool changed;
    uint32_t queue_index;
    uint32_t count;
    uint32_t count_candidate;
    uint32_t wake_selector;
    uint16_t waiters;
    int32_t ticket;
    uint64_t queue_word;
    uint64_t current_word;
    uint64_t count_field;

    queue_index = ((uint32_t)queue >> 4) & 0xf;
    if ((uint8_t)queue[1] != 0) {
        queue_index = (uint8_t)queue[1] - 1;
    }
    if (queue + 2 < queue) {
        SoftwareBreakpoint(0x5519, 0x5d470);
    }
    queue_word = *queue;
    count = (uint32_t)(queue_word >> 0x20);
    waiters = (uint16_t)(queue_word >> 0x30);
    count_candidate = count & 0xffff;
    if (waiters + 1 < (count & 0xffff)) {
        count_candidate = waiters + 1;
    }
    count_field = queue_word >> 0x20;
    if (clamp_to_capacity == 0) {
        count_field = (uint64_t)count_candidate;
    }
    current_word = *queue;
    if (current_word == queue_word) {
        *queue = (uint64_t)((int32_t)queue_word + 1) | count_field << 0x30 |
                 queue_word & 0xffff00000000ULL;
    } else {
        do {
            count = (uint32_t)(current_word >> 0x20);
            waiters = (uint16_t)(current_word >> 0x30);
            ticket = (int32_t)current_word;
            count_candidate = count & 0xffff;
            if (waiters + 1 < (count & 0xffff)) {
                count_candidate = waiters + 1;
            }
            queue_word = current_word >> 0x20;
            if (clamp_to_capacity == 0) {
                queue_word = (uint64_t)count_candidate;
            }
            count_field = current_word & 0xffff00000000ULL;
            changed = *queue != current_word;
            current_word = *queue;
        } while (changed);
        *queue = (uint64_t)(ticket + 1) | queue_word << 0x30 | count_field;
    }
    if ((uint32_t)waiters < (count & 0xffff)) {
        wake_selector = 6;
        if (clamp_to_capacity == 0) {
            wake_selector = 4;
        }
        sk_f_0005dd70(queue_index & 0xff, (uint64_t)(uintptr_t)queue, wake_selector, 0);
        return;
    }
    return;
}

/* FUN_0005d470 @ 0x0005d470   (est. slot_release_run)
 * Ghidra: void FUN_0005d470(uint *param_1,code *param_2,undefined8 param_3)
 * Releases a capability/slot: when the slot is free (0) it is claimed with an owner
 * tag, the completion callback is run with callback_arg, then the slot is released to
 * 0xffffffff under LORelease and possibly parked via sk_f_0005dd70. When the slot is
 * already owned, it walks the owner chain re-parenting the owner id and calling
 * sk_f_0005dc8c for each live entry until the slot becomes 0xffffffff. Traps
 * (SoftwareBreakpoint 0x5519) on a size overrun from sk_x_000606B0.
 * Confidence: medium
 * Notes: slot is uint32_t; callback_arg is an opaque pointer passed to the callback
 *        (in practice &DAT_006b2688). sk_g_006ad900>>10 is stored into the
 *        current-thread timebase field at +0x78. */
void sk_f_0005d470(uint32_t *slot, void (*completion)(void *), void *callback_arg)
{
    uint32_t owner_tag;
    uint32_t slot_index;
    uint32_t owner_id;
    uint32_t slot_value;
    uint64_t timebase;
    int64_t current_thread;
    uint64_t scaled_time;
    uint64_t queue_ref;

    if (*slot != 0xffffffff) {
        slot_index = ((uint32_t)slot >> 4) & 0xf;
        timebase = sk_x_00060524();
        scaled_time = sk_g_006ad900 >> 10;
        current_thread = (int64_t)sk_x_00060524();
        *(uint64_t *)(current_thread + 0x78) = scaled_time;
        queue_ref = sk_f_0005dc4c(slot_index);
        owner_tag = (uint32_t)(timebase >> 0xc) & 0x3fffffc;
        slot_value = *slot;
        if (slot_value == 0) {
            *slot = owner_tag | 1;
            completion(callback_arg);
            slot_value = *slot;
            *slot = 0xffffffff;
            LORelease();
            if (slot_value == (owner_tag | 3)) {
                sk_f_0005dd70(slot_index, (uint64_t)(uintptr_t)slot, 6, 0);
                return;
            }
        } else {
            owner_id = slot_value >> 2 & 0xffffff;
            owner_tag = slot_value;
            if (((slot_value >> 2 & 0xffffff) << 2 | 1) == slot_value) {
                queue_ref = sk_f_0005dc4c(slot_index);
                owner_tag = *slot;
                if (owner_tag == slot_value) {
                    *slot = owner_id << 2 | 3;
                    goto reacquire;
                }
            }
            while (owner_tag != 0xffffffff) {
reacquire:
                timebase = sk_x_000606B0(owner_id);
                if (timebase + 0x178 < timebase) {
                    SoftwareBreakpoint(0x5519, 0x5d5dc);
                }
                sk_f_0005dc8c(slot_index, (uint64_t)(uintptr_t)slot, (uint64_t)(uintptr_t)queue_ref, timebase, 0);
                owner_tag = *slot;
            }
        }
    }
    return;
}

/* FUN_0005d5dc @ 0x0005d5dc   (est. sync_source_reset)
 * Ghidra: void FUN_0005d5dc(void)
 * Resets the sync source at global 0x64dca0 by forwarding to sk_f_0005ba5c.
 * Confidence: medium
 * Notes: literal 0x64dca0 is a global object address passed to the reset helper. */
void sk_f_0005d5dc(void)
{
    sk_f_0005ba5c((uint64_t *)(uintptr_t)0x64dca0);
    return;
}

/* FUN_0005d5e8 @ 0x0005d5e8   (est. msg_register_send)
 * Ghidra: void FUN_0005d5e8(undefined8 param_1,uint param_2,undefined8 param_3,undefined8 param_4)
 * Sends a message-register operation: builds a config word from the register number
 * (low nibble shifted up plus a type bit 8) and forwards the two 64-bit message
 * payload words to sk_f_0005d64c for the given thread. Stack canary guarded.
 * Confidence: medium
 * Notes: message_low/message_high are the two halves of the message payload; the
 *        address of message_low is passed. Canary epilogue via sk_x_0011D7E8. */
void sk_f_0005d5e8(uint64_t target_thread, uint32_t register_num, uint64_t msg_lo,
                   uint64_t msg_hi)
{
    uint64_t stack_guard = -0x2c8502b44bfffed6ULL;
    uint64_t message_low = msg_lo;
    uint64_t message_high = msg_hi;

    sk_f_0005d64c((int64_t)target_thread, (uint16_t)((register_num & 0xf) << 0xc | 8),
                  &message_low, 0);
    if (stack_guard == -0x2c8502b44bfffed6ULL) {
        return;
    }
    sk_x_0011D7E8();
}

/* FUN_0005d64c @ 0x0005d64c   (est. msg_register_operation)
 * Ghidra: void FUN_0005d64c(long param_1,undefined2 param_2,undefined8 *param_3,ulong param_4)
 * Performs a register-class IPC/message operation on target_thread: copies the two
 * message payload words from msg_payload into locals, resolves the target thread
 * context (optionally cross-thread when flags bit 0 is set and the thread differs from
 * the current one, recording the mismatch flag), then invokes the per-register handler
 * sk_f_0005dfa8 via sk_f_0005dab8 with the config word. On success the status is
 * finalized (default 5, or the register's stored status) and the function returns; on
 * error the code is decoded via sk_x_004B6938 and the stack-check-fail routine
 * sk_x_0011D7E8 is called. Stack canary guarded.
 * Confidence: medium
 * Notes: canary return path is nested inside the success branch. config (config_word)
 *        is passed by address through sk_f_0005dab8 as an opaque uint64_t. */
uint64_t sk_f_0005d64c(int64_t target_thread, uint16_t config_word, uint64_t *msg_payload,
                   uint64_t flags)
{
    bool is_cross_thread;
    int64_t current_thread;
    uint64_t run_result;
    uint64_t status;
    char *cross_thread_flag;
    char need_wake;
    uint16_t config;
    uint16_t pad1;
    uint16_t pad2;
    uint16_t pad3;
    uint64_t msg_low;
    uint64_t msg_high;
    uint64_t stored_status;
    uint64_t cross_thread_marker;
    uint8_t error_buf[32];
    uint64_t stack_guard = -0x2c8502b44bfffed6ULL;

    pad1 = 0;
    pad2 = 0;
    pad3 = 0;
    msg_high = msg_payload[1];
    msg_low = *msg_payload;
    stored_status = 0;
    cross_thread_marker = 0;
    config = config_word;
    if ((flags & 1) == 0) {
        is_cross_thread = false;
        cross_thread_flag = (char *)0;
    } else {
        current_thread = (int64_t)sk_x_00060524();
        cross_thread_flag = &need_wake;
        is_cross_thread = target_thread != current_thread;
        if (!is_cross_thread) {
            cross_thread_flag = (char *)0;
        }
    }
    cross_thread_marker = (uint64_t)is_cross_thread;
    need_wake = '\0';
    run_result = sk_f_0005dab8((uint64_t (*)(int64_t, uint64_t))sk_f_0005dfa8,
                               (uint64_t)target_thread, (uint8_t *)cross_thread_flag,
                               (uint64_t)(uintptr_t)&config);
    if ((run_result & 0xff) == 0) {
        status = 5;
        if (need_wake == '\0') {
            status = stored_status;
        }
        if (stack_guard == -0x2c8502b44bfffed6ULL) {
            return status;
        }
    } else {
        status = sk_x_004B6938(run_result, error_buf);
    }
    sk_x_0011D7E8(status);
}

/* FUN_0005d77c @ 0x0005d77c   (est. sync_space_init)
 * Ghidra: undefined8 FUN_0005d77c(void)
 * Initialises the sync space: releases the slot at global 0x6b2680 with
 * sk_f_0005d470, running sk_f_0005d7c8 as the completion callback on the address of
 * the result global DAT_006b2688, and returns that global.
 * Confidence: medium
 * Notes: the callback/argument pair is the code* + undefined8 from the decompile.
 *        Returns the global DAT_006b2688 value. */
uint64_t sk_f_0005d77c(void)
{
    sk_f_0005d470((uint32_t *)0x6b2680, (void (*)(void *))sk_f_0005d7c8,
                  (void *)&sk_g_006b2688);
    return sk_g_006b2688;
}

/* FUN_0005d7c8 @ 0x0005d7c8   (est. sync_space_init_vas_root)
 * Ghidra: void FUN_0005d7c8(long *param_1)
 * Completes sync-space VAS-root initialisation: obtains the VAS root object via
 * sk_x_00034F70, stores it out through root_slot, and when non-null validates it
 * through the object's vtable method at offset 0x48 (object/vtable obtained from the
 * 16-byte sk_x_00034A2C result). A false result triggers the "xrt: sync_space_init:
 * vas root" panic; a null root triggers the "space_top_init: vas slot alloc" panic
 * (sk_f_0005b190, noreturn). Traps (SoftwareBreakpoint 0x5519) on pointer underflow.
 * Confidence: medium
 * Notes: 16-byte aggregate return of sk_x_00034A2C split as object id (low) and vtable
 *        pointer (high); virtual call reads *(vtable+0x48). */
void sk_f_0005d7c8(int64_t *root_slot)
{
    int64_t vas_root;
    uint64_t object_id;
    uint64_t vtable;
    char status;

    vas_root = sk_x_00034F70();
    if (root_slot + 1 < root_slot) {
        SoftwareBreakpoint(0x5519, 0x5d82c);
    }
    *root_slot = vas_root;
    if (vas_root != 0) {
        /* obj_vt = sk_x_00034A2C(); -- 16-byte aggregate: lo=object, hi=vtable */
        sk_u128_t obj_vt = ((sk_u128_t (*)(void))sk_x_00034A2C)();
        object_id = obj_vt.lo;
        vtable = obj_vt.hi;
        status = ((char (*)(uint64_t, int64_t))(*(uint64_t *)(vtable + 0x48)))(object_id,
                                                                              *root_slot);
        if (status == '\0') {
            return;
        }
        sk_f_0005b190(0, sk_str_005bcb5b);
    }
    sk_f_0005b190(0, sk_str_005bcb30);
}

/* FUN_0005d84c @ 0x0005d84c   (est. sync_space_dispatch)
 * Ghidra: void FUN_0005d84c(void)
 * Dispatches a sync-space operation: lazily initialises the global dispatch function
 * pointer DAT_006b2690 to 0x65c560 when it is null, then calls the pointed-to function.
 * The decompiler could not recover the indirect-jump table and treated the call as an
 * indirect call.
 * Confidence: medium
 * Notes: DAT_006b2690 is a code-pointer global; represented via sk_g_006b2690. */
void sk_f_0005d84c(void)
{
    if (sk_g_006b2690 == 0) {
        sk_g_006b2690 = 0x65c560;
    }
    ((void (*)(void))sk_g_006b2690)();
    return;
}

/* FUN_0005d870 @ 0x0005d870   (est. error_code_report)
 * Ghidra: void FUN_0005d870(long param_1,int param_2)
 * Reports an error result from an IPC/sync operation for thread: returns early when
 * reporting_enabled is zero or the thread's "panic-disabled" flag (bit 3 of +0x48) is
 * set. Otherwise it obtains the current VAS root (sk_x_00034F70), issues a supervisor
 * call (CallSupervisor 3) to retrieve the thread's error, and when a nonzero error is
 * returned decodes the L4 error code into its string table (sk_str_004be0xx) and
 * prints it; a code >= 10 prints the generic error-data block DAT_004be180. On success
 * it finalises via sk_x_004B69D0. Stack canary guarded.
 * Confidence: medium
 * Notes: tpidrro_el0 is read inline to obtain the per-thread control block base;
 *        ctx is an uninitialized decompiler artifact forwarded to the printer.
 *        CallSupervisor(3) is a supervisor-call intrinsic. */
void sk_f_0005d870(int64_t thread, int32_t reporting_enabled)
{
    int64_t vas_root;
    uint64_t error_id;
    char *error_str;
    uint8_t error_name_buf[32];
    uint64_t stack_guard = -0x2c8502b44bfffed6ULL;
    uint64_t ctx;

    if ((reporting_enabled == 0) || ((*(uint8_t *)(thread + 0x48) >> 3 & 1) != 0)) {
        return;
    }
    vas_root = sk_x_00034F70();
    if (vas_root != 0) {
        uint8_t *tcb;
        uint8_t error_code;
        error_id = sk_x_00061630(thread);
        /* tcb = tpidrro_el0 (per-thread control block base) */
        __asm__ volatile("mrs %0, tpidrro_el0" : "=r"(tcb));
        tcb[5] = 0;
        tcb[3] = 0;
        tcb[2] = 0;
        tcb[1] = 2;
        *tcb = 0;
        tcb[4] = 0;
        tcb[7] = 0;
        tcb[6] = 0;
        CallSupervisor(3);
        if ((error_id & 0xff) != 0) {
            error_code = sk_x_004B6984(error_id, error_name_buf, 0x200);
            if (error_code < 10) {
                switch (error_code) {
                default:
                    error_str = sk_str_004be040;
                    break;
                case 1:
                    error_str = sk_str_004be060;
                    break;
                case 2:
                    error_str = sk_str_004be080;
                    break;
                case 3:
                    error_str = sk_str_004be0a0;
                    break;
                case 4:
                    error_str = sk_str_004be0c0;
                    break;
                case 5:
                    error_str = sk_str_004be0e0;
                    break;
                case 6:
                    error_str = sk_str_004be100;
                    break;
                case 7:
                    error_str = sk_str_004be120;
                    break;
                case 8:
                    error_str = sk_str_004be140;
                    break;
                case 9:
                    error_str = sk_str_004be160;
                    break;
                }
                sk_x_00117CC4(ctx, error_str, 0x20);
                return;
            }
            sk_x_00117CC4(ctx, &sk_g_004be180, 0x20);
            sk_x_0000178C(ctx, 0x20);
            return;
        }
        sk_x_004B69D0(tcb, vas_root, (uint8_t *)(thread + 0x48));
    }
    if (stack_guard == -0x2c8502b44bfffed6ULL) {
        sk_x_004B23D8(vas_root);
        return;
    }
    sk_x_0011D7E8();
}

/* FUN_0005dab8 @ 0x0005dab8   (est. thread_run_handler)
 * Ghidra: undefined8 FUN_0005dab8(code *param_1,ulong param_2,undefined1 *param_3,undefined8 param_4)
 * Runs a per-thread handler: resolves the target_thread against the current thread
 * (sk_x_00060524). When the target differs and cross_thread_flag (a flag slot) is
 * supplied, it first validates via sk_f_0005fdac and, if the target is not runnable,
 * sets *cross_thread_flag = 1 and returns 0. Otherwise the handler is invoked with the
 * thread's run-state field (+0x28) and arg. On cross-thread completion the supervisor
 * is pinged (CallSupervisor 4) until the thread state drains. Traps
 * (SoftwareBreakpoint 0x5519) on a bogus size comparison.
 * Confidence: medium
 * Notes: handler is typed as uint64_t(*)(int64_t, uint64_t); arg is an opaque value
 *        forwarded (in practice the address of a config word). */
uint64_t sk_f_0005dab8(uint64_t (*handler)(int64_t, uint64_t), uint64_t target_thread,
                       uint8_t *cross_thread_flag, uint64_t arg)
{
    uint64_t current_thread;
    uint64_t result;
    uint64_t resolved_thread;
    int64_t thread_state;

    current_thread = sk_x_00060524();
    if (target_thread == current_thread) {
        resolved_thread = current_thread;
        if (current_thread + 0x178 < target_thread) {
            SoftwareBreakpoint(0x5519, 0x5db7c);
        }
    } else {
        resolved_thread = target_thread;
        if (cross_thread_flag != (uint8_t *)0) {
            thread_state = *(int64_t *)(current_thread + 0x70);
            current_thread = sk_x_0005FDAC(target_thread, thread_state);
            if ((current_thread & 1) == 0) {
                *cross_thread_flag = 1;
                return 0;
            }
            goto run_handler;
        }
    }
    thread_state = *(int64_t *)(resolved_thread + 0x28);
run_handler:
    result = handler(thread_state, arg);
    current_thread = sk_x_00060524();
    if ((cross_thread_flag != (uint8_t *)0) && (target_thread != current_thread)) {
        do {
            CallSupervisor(4);
        } while (thread_state == 1);
    }
    return result;
}


/* part7.c — SK11 slice, worker P7. 12 functions, address order.
 * cL4 "xrt" thread-runtime layer: sync wake/wait primitives, per-cpu table reads,
 * the xrt dispatch table stubs, an IPC message send via supervisor call, and the
 * capability-identify / L4 error-code formatter. */

/* FUN_0005db7c @ 0x0005db7c   (est. sync_wake_thread)
 * Ghidra: void FUN_0005db7c(long param_1)
 * Wakes a (possibly other) thread out of a blocking sync wait. When the target is
 * the current thread the wake uses selector 0xd directly; otherwise a per-thread
 * spinlock (acquired via sk_x_00060570, released via sk_x_000605f8) is taken,
 * selector 0xc is used, and the lock is released. In both cases bit 3 of the
 * thread's 8-byte flags word at +0x48 is cleared once the wake is issued.
 * Confidence: medium
 * Notes: sk_x_00060524 is the current-thread getter; sk_f_0005d64c is the internal
 * send/wake primitive. Stack canary guarded. */
void sk_f_0005db7c(uint64_t *thread)
{
    uint64_t stack_guard = SK_CANARY;
    uint64_t msg[2];
    long current;
    uint8_t lock;
    int r;

    if ((((uint8_t *)thread)[0x48] >> 3 & 1) != 0) {
        current = sk_x_00060524();
        if (thread == (uint64_t *)current) {
            msg[0] = 0;
            msg[1] = 0;
            sk_f_0005d64c((uint64_t)thread, 0xd, &msg[0], 1);
            *(uint64_t *)((uint8_t *)thread + 0x48) =
                *(uint64_t *)((uint8_t *)thread + 0x48) & 0xfffffffffffffff7ull;
        } else {
            lock = 0;
            do {
                r = sk_x_00060570(&lock);
            } while (r == 0);
            msg[0] = 0;
            msg[1] = 0;
            sk_f_0005d64c((uint64_t)thread, 0xc, &msg[0], 1);
            *(uint64_t *)((uint8_t *)thread + 0x48) =
                *(uint64_t *)((uint8_t *)thread + 0x48) & 0xfffffffffffffff7ull;
            sk_x_000605f8(&lock);
        }
    }
    if (stack_guard == SK_CANARY) {
        return;
    }
    sk_x_0011D7E8();
}

/* FUN_0005dc4c @ 0x0005dc4c   (est. per_cpu_table_read)
 * Ghidra: undefined8 FUN_0005dc4c(ulong param_1)
 * Reads the 8-byte entry at index param_1 (masked to 32 bits) of the per-CPU table
 * rooted at 0x6b2698, resolved through sk_f_0005acac. A data memory barrier is
 * issued before the read so the table publication is visible. Returns the word.
 * Confidence: medium
 * Notes: param_1 is a CPU index; 0x6b2698 is the kernel-image per-cpu table base. */
uint64_t sk_f_0005dc4c(uint64_t cpu_index)
{
    long base;
    uint64_t value;

    base = sk_f_0005acac(0x6b2698, 1, 4);
    DataMemoryBarrier(2, 3);
    value = *(uint64_t *)(base + (cpu_index & 0xffffffff) * 8);
    return value;
}

/* FUN_0005dc8c @ 0x0005dc8c   (est. xrt_dispatch_10)
 * Ghidra: void FUN_0005dc8c(void)
 * Entry of the xrt dispatch table: lazily initializes the global table pointer
 * sk_g_006b2690 to 0x65c560 if it is still null, then invokes the handler at
 * offset +0x10 of that table (a code pointer, indirect call). Returns after the
 * handler returns.
 * Confidence: low
 * Notes: _DAT_006b2690 holds the dispatch-table address; 0x65c560 is the default
 * table image address. Sibling handlers dispatch at +0x08/+0x18/+0x20. */
uint64_t sk_f_0005dc8c(uint64_t selector, uint64_t arg1, uint64_t arg2,
                       uint64_t arg3, uint64_t arg4)
{
    uint64_t (*handler)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

    if (sk_g_006b2690 == 0) {
        sk_g_006b2690 = 0x65c560;
    }
    handler = *(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))
              (sk_g_006b2690 + 0x10);
    return handler(selector, arg1, arg2, arg3, arg4);
}

/* FUN_0005dcb0 @ 0x0005dcb0   (est. sync_wait)
 * Ghidra: void FUN_0005dcb0(uint param_1,undefined8 param_2,undefined8 param_3,long param_4,uint param_5)
 * Blocks the caller on a sync wait: builds a 16-byte message register block from
 * param_2/param_3, defaults the target thread to the current one, and issues the
 * send via sk_f_0005d64c with a tag combining the 4-bit selector (param_1) and a
 * blocking flag (1 without param_5, 2 with it). If the returned code (ignoring a
 * 5 sentinel) is < 4 and not the "unexpected wait interruption" case (param_5 bit 0
 * set, or code 3) the wait succeeded and the function returns; otherwise it panics
 * with the appropriate wait-interruption / unexpected-sync-return message.
 * Confidence: medium
 * Notes: sk_x_00060524 = current thread; s_Unexpected_wait_interruption_005bc8f1 /
 * s_unexpected_return_from_xrt__sync_005bc8ca. sk_f_0005b190 is the noreturn panic.
 * Stack canary guarded. */
void sk_f_0005dcb0(uint32_t selector, uint64_t msg0, uint64_t msg1, uint64_t thread, uint32_t flags)
{
    uint64_t stack_guard = SK_CANARY;
    uint32_t tag_base;
    uint64_t msg[2];
    uint64_t result;
    uint64_t r;
    const char *err;

    tag_base = 1;
    if (flags != 0) {
        tag_base = 2;
    }
    msg[0] = msg0;
    msg[1] = msg1;
    if (thread == 0) {
        thread = sk_x_00060524();
    }
    result = sk_f_0005d64c(thread, tag_base | (uint32_t)((selector & 0xf) << 0xc),
                           &msg[0], 1);
    r = 0;
    if (result != 5) {
        r = result;
    }
    if (r < 4) {
        if (((flags & 1) != 0) || (r != 3)) {
            if (stack_guard == SK_CANARY) {
                return;
            }
            sk_x_0011D7E8();
        }
        err = sk_str_005bc8f1;            /* s_Unexpected_wait_interruption_005bc8f1 */
    } else {
        err = sk_str_005bc8ca;            /* s_unexpected_return_from_xrt__sync_005bc8ca */
    }
    sk_f_0005b190(0, err);                /* noreturn panic */
}

/* FUN_0005dd70 @ 0x0005dd70   (est. xrt_dispatch_18)
 * Ghidra: void FUN_0005dd70(void)
 * Entry of the xrt dispatch table: lazily initializes the global table pointer
 * sk_g_006b2690 to 0x65c560 if null, then invokes the handler at offset +0x18 of
 * that table (indirect call). Returns after the handler returns.
 * Confidence: low
 * Notes: _DAT_006b2690 dispatch-table address; default table at 0x65c560. */
void sk_f_0005dd70(uint64_t selector, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
    void (*handler)(uint64_t, uint64_t, uint64_t, uint64_t);

    if (sk_g_006b2690 == 0) {
        sk_g_006b2690 = 0x65c560;
    }
    handler = *(void (**)(uint64_t, uint64_t, uint64_t, uint64_t))(sk_g_006b2690 + 0x18);
    handler(selector, arg1, arg2, arg3);
}

/* FUN_0005dd94 @ 0x0005dd94   (est. sync_wake)
 * Ghidra: void FUN_0005dd94(uint param_1,undefined8 param_2,uint param_3,ulong param_4)
 * General sync-wake primitive. The wake selector param_3 is normalized: 3, 6 are
 * used as-is against the current thread; 4 (with a nonzero param_4) retargets the
 * wake to thread param_4; 4-without-target and 5 both collapse to 5; any other
 * selector panics as an invalid sync wake selector. A per-cpu wake counter indexed
 * by param_1 (table base 0x6b2698) is incremented, a release barrier is emitted,
 * and the 16-byte message block (param_2 + the fresh counter value) is sent via
 * sk_f_0005d64c with tag (selector | param_1<<12) & 0xffff. Returns on success.
 * Confidence: medium
 * Notes: s_invalid_sync_wake_selector__u_005bc90e panic; SoftwareBreakpoint(0x5519)
 * guards overflow of target+0x178. sk_x_00060524 = current thread. Epilogue passes
 * (send_result != 5) to the noreturn sk_x_0011D7E8. Stack canary guarded. */
void sk_f_0005dd94(uint32_t wake_idx, uint64_t msg0, uint32_t selector, uint64_t target_thread)
{
    uint64_t stack_guard = SK_CANARY;
    uint64_t target;
    long *counter;
    long base;
    uint64_t msg[2];
    uint64_t send_result;

    target = sk_x_00060524();
    if ((int)selector < 5) {
        if (selector == 3) {
            goto normalized;
        }
        if (selector != 4) {
            sk_f_0005b190(0, sk_str_005bc90e);   /* s_invalid_sync_wake_selector__u_005bc90e */
        }
        if (target_thread != 0) {
            selector = 4;
            target = target_thread;
            goto normalized;
        }
    } else if (selector != 5) {
        if (selector != 6) {
            sk_f_0005b190(0, sk_str_005bc90e);   /* s_invalid_sync_wake_selector__u_005bc90e */
        }
        goto normalized;
    }
    selector = 5;
normalized:
    base = sk_f_0005acac(0x6b2698, 1, 4);
    counter = (long *)(base + (uint64_t)wake_idx * 8);
    *counter = *counter + 1;
    LORelease();
    msg[0] = msg0;
    msg[1] = *(uint64_t *)(base + (uint64_t)wake_idx * 8);
    if (target + 0x178 < target) {
        SoftwareBreakpoint(0x5519, 0x5deb0);      /* overflow guard, noreturn */
    }
    send_result = sk_f_0005d64c(target, ((uint64_t)(selector | (wake_idx << 0xc)) & 0xffffu),
                                &msg[0], 0);
    if (stack_guard == SK_CANARY) {
        return;
    }
    sk_x_0011D7E8(send_result != 5);              /* noreturn stack-check-fail */
}

/* FUN_0005deb4 @ 0x0005deb4   (est. xrt_dispatch_20)
 * Ghidra: void FUN_0005deb4(void)
 * Entry of the xrt dispatch table: lazily initializes the global table pointer
 * sk_g_006b2690 to 0x65c560 if null, then invokes the handler at offset +0x20 of
 * that table (indirect call). Returns after the handler returns.
 * Confidence: low
 * Notes: _DAT_006b2690 dispatch-table address; default table at 0x65c560. */
void sk_f_0005deb4(void)
{
    if (sk_g_006b2690 == 0) {
        sk_g_006b2690 = 0x65c560;
    }
    (*(void (**)(void))(sk_g_006b2690 + 0x20))();
    return;
}

/* FUN_0005ded8 @ 0x0005ded8   (est. thread_send_op7)
 * Ghidra: void FUN_0005ded8(undefined8 param_1)
 * Issues an empty (zero message registers) send to thread param_1 with the fixed
 * selector 7 via sk_f_0005d64c. No message payload is provided. Returns on success.
 * Confidence: low
 * Notes: selector 7 falls within the thread-runtime sync selector space; the exact
 * operation (e.g. suspend/notify) is unidentified. Stack canary guarded. */
void sk_f_0005ded8(uint64_t thread)
{
    uint64_t stack_guard = SK_CANARY;
    uint64_t msg[2];

    msg[0] = 0;
    msg[1] = 0;
    sk_f_0005d64c(thread, 7, &msg[0], 1);
    if (stack_guard == SK_CANARY) {
        return;
    }
    sk_x_0011D7E8();
}

/* FUN_0005df34 @ 0x0005df34   (est. current_thread_send_op11)
 * Ghidra: void FUN_0005df34(uint param_1)
 * Sends to the current thread (sk_x_00060524) a zero-message-payload IPC with the
 * tag built from the 4-bit selector param_1 placed in bits 12-15 and selector 0x11
 * (17) in the low bits, via sk_f_0005d64c. Returns on success.
 * Confidence: low
 * Notes: 0x11 is a self-directed selector in the sync/thread-runtime space. Stack
 * canary guarded. */
void sk_f_0005df34(uint32_t selector)
{
    uint64_t stack_guard = SK_CANARY;
    uint64_t msg[2];
    uint64_t self;

    msg[0] = 0;
    msg[1] = 0;
    self = sk_x_00060524();
    sk_f_0005d64c(self, (uint32_t)((selector & 0xf) << 0xc | 0x11), &msg[0], 0);
    if (stack_guard == SK_CANARY) {
        return;
    }
    sk_x_0011D7E8();
}

/* FUN_0005dfa8 @ 0x0005dfa8   (est. ipc_send_message16)
 * Ghidra: undefined1  [16] FUN_0005dfa8(ulong param_1,ushort *param_2)
 * Sends a 16-byte IPC message block via supervisor call. The block is assembled
 * into the tpidrro area from param_2: a 16-bit tag (uVar5) at bytes 0-1, and two
 * 64-bit values at byte offsets 8 and 16 of param_2 written to bytes 0x10-0x17 and
 * the tag+zeros to bytes 0-7; CallSupervisor(0) performs the send. Afterwards a
 * flag byte at param_2 offset 0x20 selects whether the returned {lo,hi} pair is
 * {param_1, uVar5} (flag clear) or zero; the selected 64-bit value is also stored
 * back to param_2 byte offset 0x18.
 * Confidence: medium
 * Notes: return modeled as cl4_result_t {lo=param_1-or-0, hi=uVar5-or-0} matching
 * the 16-byte undefined1[16] return. CallSupervisor(0) is the SVC-0 syscall. */
cl4_result_t sk_f_0005dfa8(uint64_t tag, uint16_t *msg)
{
    uint16_t tag_word;
    uint64_t payload_lo;
    uint64_t payload_hi;
    uint8_t *area;
    uint8_t tag_hi;
    bool flag_set;
    cl4_result_t out;
    uint64_t stored;

    tag_word = *msg;
    payload_lo = *(uint64_t *)(msg + 4);         /* byte offset 8 */
    payload_hi = *(uint64_t *)(msg + 8);         /* byte offset 16 */
    area = tpidrro_el0;
    area[4] = 0;
    area[2] = 0;
    area[5] = 0;
    area[3] = 0;
    area[6] = 0;
    area[7] = 0;
    area[0] = (uint8_t)tag_word;
    tag_hi = (uint8_t)(tag_word >> 8);
    area[1] = tag_hi;
    area[0xd] = (uint8_t)(payload_lo >> 0x28);
    area[8] = (uint8_t)payload_lo;
    area[0xb] = (uint8_t)(payload_lo >> 0x18);
    area[10] = (uint8_t)(payload_lo >> 0x10);
    area[9] = (uint8_t)(payload_lo >> 8);
    area[0xc] = (uint8_t)(payload_lo >> 0x20);
    area[0xf] = (uint8_t)(payload_lo >> 0x38);
    area[0xe] = (uint8_t)(payload_lo >> 0x30);
    area[0x15] = (uint8_t)(payload_hi >> 0x28);
    area[0x10] = (uint8_t)payload_hi;
    area[0x13] = (uint8_t)(payload_hi >> 0x18);
    area[0x12] = (uint8_t)(payload_hi >> 0x10);
    area[0x11] = (uint8_t)(payload_hi >> 8);
    area[0x14] = (uint8_t)(payload_hi >> 0x20);
    area[0x17] = (uint8_t)(payload_hi >> 0x38);
    area[0x16] = (uint8_t)(payload_hi >> 0x30);
    CallSupervisor(0);
    area[0] = (uint8_t)tag_word;
    area[7] = 0;
    area[6] = 0;
    area[5] = 0;
    area[4] = 0;
    area[3] = 0;
    area[2] = 0;
    area[1] = tag_hi;
    flag_set = (((uint8_t)msg[0x10]) & (tag == 8)) == 0;   /* byte at offset 0x20 */
    stored = 0;
    if (flag_set) {
        stored = (uint64_t)tag_word;
    }
    *(uint64_t *)(msg + 0xc) = stored;                       /* byte offset 0x18 */
    out.lo = 0;
    if (flag_set) {
        out.lo = tag;
    }
    out.hi = 0;
    return out;
}

/* FUN_0005e0dc @ 0x0005e0dc   (est. xrt_dispatch_08)
 * Ghidra: void FUN_0005e0dc(void)
 * Entry of the xrt dispatch table: lazily initializes the global table pointer
 * sk_g_006b2690 to 0x65c560 if null, then invokes the handler at offset +0x08 of
 * that table (indirect call). Returns after the handler returns.
 * Confidence: low
 * Notes: _DAT_006b2690 dispatch-table address; default table at 0x65c560. */
void sk_f_0005e0dc(void)
{
    if (sk_g_006b2690 == 0) {
        sk_g_006b2690 = 0x65c560;
    }
    (*(void (**)(void))(sk_g_006b2690 + 8))();
    return;
}

/* FUN_0005e100 @ 0x0005e100   (est. cap_identify)
 * Ghidra: void FUN_0005e100(ulong param_1,undefined1 *param_2)
 * Identifies a capability / operation and formats the outcome. param_2 doubles as
 * a selector (cast to int) and, after reassignment, a message buffer (the tpidrro
 * area). Selector 8/9 load a 16-byte capability template from the static globals
 * (004be030/038 and 004bb1a0/a8 respectively) into the message area, issue
 * CallSupervisor(3), and when param_1&0xff is set fetch the resulting L4 error
 * code (sk_x_004b6c04) and format one of the L4_ErrorCode* strings (or an unknown
 * 0x20-byte blob) into a 0x20 scratch buffer. When the code is clear it falls into
 * the selector-9 self path: it stores the current-thread word into the buffer at
 * offset 0x1c0, issues CallSupervisor(0) with a (0x40,type=3) message, and on a
 * nonzero low byte of the 00689e9c capability word panics as an invalid capability
 * type to identify; otherwise it posts the result via sk_x_004b23d8. Selector 6 and
 * 0xd are accepted no-ops; any other selector panics with the invalid-cap-type
 * message.
 * Confidence: medium
 * Notes: s_invalid_cap_type_to_identify___u_005bcac1 panic; sk_f_0005b190 noreturn.
 * The 16-byte template globals are read as uint64_t pairs; DAT_00689e9c is the
 * 4-byte capability word whose bytes e9e/e9f are separately named DAT_00689e9e /
 * DAT_00689e9f. sk_x_00034F70, sk_x_004b6c50/04/9c, sk_x_00117cc4, sk_x_0000178c,
 * sk_x_004b23d8 are external helpers. Stack canary guarded. */
void sk_f_0005e100(uint64_t cap_arg, uint8_t *selbuf)
{
    uint64_t stack_guard = SK_CANARY;
    uint64_t self_word;
    uint64_t tmpl_hi;
    uint64_t tmpl_lo;
    uint8_t *area;
    uint8_t err_code;
    uint8_t scratch[32];
    uint8_t strbuf[0x20];
    const char *err_str;
    uint64_t cap_b0, cap_b3, cap_b2;
    uint32_t str_w0, str_b2, str_b3;
    uint32_t capword;
    int sel;

    self_word = sk_x_00034F70();
    tmpl_hi = sk_g_004be038;                   /* uRam...4be038 */
    tmpl_lo = sk_g_004be030;                   /* _DAT_004be030 */
    sel = (int)selbuf;
    if (sel < 9) {
        if (sel == 6) {
            /* selector 6: fall through to the common epilogue */
        } else if (sel == 8) {
            area = tpidrro_el0;
            *(uint64_t *)&strbuf[0] = sk_g_004be030;   /* local_80 */
            *(uint64_t *)&strbuf[8] = sk_g_004be038;   /* uStack_78 */
            area[0] = (uint8_t)tmpl_lo;
            area[0xd] = (uint8_t)(tmpl_hi >> 0x28);
            area[8] = (uint8_t)tmpl_hi;
            area[0xb] = (uint8_t)(tmpl_hi >> 0x18);
            area[10] = (uint8_t)(tmpl_hi >> 0x10);
            area[9] = (uint8_t)(tmpl_hi >> 8);
            area[5] = (uint8_t)(tmpl_lo >> 0x28);
            area[3] = (uint8_t)(tmpl_lo >> 0x18);
            area[2] = (uint8_t)(tmpl_lo >> 0x10);
            area[0xc] = (uint8_t)(tmpl_hi >> 0x20);
            area[1] = (uint8_t)(tmpl_lo >> 8);
            area[0xf] = (uint8_t)(tmpl_hi >> 0x38);
            area[0xe] = (uint8_t)(tmpl_hi >> 0x30);
            area[4] = (uint8_t)(tmpl_lo >> 0x20);
            area[7] = (uint8_t)(tmpl_lo >> 0x38);
            area[6] = (uint8_t)(tmpl_lo >> 0x30);
            area[0x15] = 0;
            area[0x11] = 0;
            area[0x10] = 0;
            area[0x13] = 0;
            area[0x12] = 0;
            area[0x14] = 0;
            area[0x17] = 0;
            area[0x16] = 0;
            CallSupervisor(3);
            if ((cap_arg & 0xff) != 0) {
                sk_x_004b6c50(cap_arg, scratch, 1);
                goto selector_ge9;
            }
            goto selector_e33c;
        } else {
            goto invalid_cap_type;
        }
    } else {
selector_ge9:
        tmpl_hi = sk_g_004bb1a8;               /* uRam...4bb1a8 */
        tmpl_lo = sk_g_004bb1a0;               /* _DAT_004bb1a0 */
        if ((int)selbuf == 9) {
            area = tpidrro_el0;
            *(uint64_t *)&strbuf[0] = sk_g_004bb1a0;   /* local_70 */
            *(uint64_t *)&strbuf[8] = sk_g_004bb1a8;   /* uStack_68 */
            area[0] = (uint8_t)tmpl_lo;
            area[0xd] = (uint8_t)(tmpl_hi >> 0x28);
            area[8] = (uint8_t)tmpl_hi;
            area[0xb] = (uint8_t)(tmpl_hi >> 0x18);
            area[10] = (uint8_t)(tmpl_hi >> 0x10);
            area[9] = (uint8_t)(tmpl_hi >> 8);
            area[5] = (uint8_t)(tmpl_lo >> 0x28);
            area[3] = (uint8_t)(tmpl_lo >> 0x18);
            area[2] = (uint8_t)(tmpl_lo >> 0x10);
            area[0xc] = (uint8_t)(tmpl_hi >> 0x20);
            area[1] = (uint8_t)(tmpl_lo >> 8);
            area[0xf] = (uint8_t)(tmpl_hi >> 0x38);
            area[0xe] = (uint8_t)(tmpl_hi >> 0x30);
            area[4] = (uint8_t)(tmpl_lo >> 0x20);
            area[7] = (uint8_t)(tmpl_lo >> 0x38);
            area[6] = (uint8_t)(tmpl_lo >> 0x30);
            area[0x15] = 0;
            area[0x11] = 0;
            area[0x10] = 0;
            area[0x13] = 0;
            area[0x12] = 0;
            area[0x14] = 0;
            area[0x17] = 0;
            area[0x16] = 0;
            CallSupervisor(3);
            if ((cap_arg & 0xff) != 0) {
                err_code = sk_x_004b6c04(cap_arg, scratch, 1);
                if (9 < err_code) {
                    sk_x_00117cc4(&strbuf[0], (uint8_t *)&sk_g_004be180, 0x20);
                    sk_x_0000178c(&strbuf[0], 0x20);
                    return;
                }
                switch (err_code) {
                default:
                    err_str = sk_str_004be040;      /* s_L4_ErrorCodeSuccess_004be040 */
                    break;
                case 1:
                    err_str = sk_str_004be060;      /* s_L4_ErrorCodePreempted_004be060 */
                    break;
                case 2:
                    err_str = sk_str_004be080;      /* s_L4_ErrorCodeCanceled_004be080 */
                    break;
                case 3:
                    err_str = sk_str_004be0a0;      /* s_L4_ErrorCodeTruncated_004be0a0 */
                    break;
                case 4:
                    err_str = sk_str_004be0c0;      /* s_L4_ErrorCodeCapInvalid_004be0c0 */
                    break;
                case 5:
                    err_str = sk_str_004be0e0;      /* s_L4_ErrorCodeSlotInvalid_004be0e0 */
                    break;
                case 6:
                    err_str = sk_str_004be100;      /* s_L4_ErrorCodeMethodInvalid_004be100 */
                    break;
                case 7:
                    err_str = sk_str_004be120;      /* s_L4_ErrorCodeArgumentInvalid_004be120 */
                    break;
                case 8:
                    err_str = sk_str_004be140;      /* s_L4_ErrorCodeOperationInvalid_004be140 */
                    break;
                case 9:
                    err_str = sk_str_004be160;      /* s_L4_ErrorCodePermissionInvalid_004be160 */
                    break;
                }
                sk_x_00117cc4(&strbuf[0], err_str, 0x20);
                return;
            }
selector_e33c:
            selbuf[0x1c0] = (uint8_t)self_word;
            selbuf[0x1c5] = (uint8_t)(self_word >> 0x28);
            selbuf[0x1c3] = (uint8_t)(self_word >> 0x18);
            selbuf[0x1c2] = (uint8_t)(self_word >> 0x10);
            selbuf[0x1c1] = (uint8_t)(self_word >> 8);
            selbuf[0x1c4] = (uint8_t)(self_word >> 0x20);
            selbuf[0x1c7] = (uint8_t)(self_word >> 0x38);
            selbuf[0x1c6] = (uint8_t)(self_word >> 0x30);
            capword = (uint32_t)sk_g_00689e9c;      /* _DAT_00689e9c (4 bytes e9c..e9f) */
            cap_b0 = (uint64_t)(uint8_t)capword;    /* byte at 00689e9c */
            cap_b3 = (uint64_t)(uint8_t)(capword >> 24);  /* DAT_00689e9f */
            cap_b2 = (uint64_t)(uint8_t)(capword >> 16);  /* DAT_00689e9e */
            str_w0 = (uint32_t)(uint16_t)((uint8_t)sk_str_00689ea0[0] |
                                          ((uint8_t)sk_str_00689ea0[1] << 8));  /* s_L4_ErrorCodeMethodInvalid_00689ea0 low 2 bytes */
            str_b2 = (uint32_t)(uint8_t)sk_str_00689ea0[2];
            str_b3 = (uint32_t)(uint8_t)sk_str_00689ea0[3];
            selbuf[0] = 0x40;
            selbuf[1] = 0;
            selbuf[4] = 0;
            selbuf[5] = 0;
            selbuf[2] = 3;
            selbuf[3] = 0;
            selbuf[6] = 0;
            selbuf[7] = 0;
            CallSupervisor(0);
            selbuf[0] = 0x40;
            selbuf[7] = 0;
            selbuf[6] = 0;
            selbuf[5] = 0;
            selbuf[4] = 0;
            selbuf[3] = 0;
            selbuf[2] = 3;
            selbuf[1] = 0;
            if ((capword & 0xff) != 0) {
                sk_x_004b6c9c(cap_b2 << 0x10 | cap_b3 << 0x18 | cap_b0 |
                              (uint64_t)(str_b2 << 0x10 | str_b3 << 0x18 | str_w0) << 0x20,
                              scratch);
invalid_cap_type:
                sk_f_0005b190(0, sk_str_005bcac1);  /* s_invalid_cap_type_to_identify___u_005bcac1, noreturn */
            }
            if (stack_guard == SK_CANARY) {
                sk_x_004b23d8(self_word, 0);
                return;
            }
            goto stack_fail;
        }
        if ((int)selbuf != 0xd) {
            goto invalid_cap_type;
        }
    }
    if (stack_guard == SK_CANARY) {
        return;
    }
stack_fail:
    sk_x_0011D7E8();
}


/* FUN_0005e4ac @ 0x0005e4ac   (est. l4_error_code_to_string)
 * Ghidra: void FUN_0005e4ac(byte param_1)
 * Maps an L4 error code (0-9) to a fixed 0x20-byte string description and prints it.
 * Codes 0-9 map to the L4_ErrorCode* string table; any code above 9 is out of range
 * and prints a generic 0x20-byte block instead. Output goes through the print
 * helpers (memcpy-like copy then flush).
 * Confidence: high
 * Notes: references s_L4_ErrorCodeSuccess_004be040 .. s_L4_ErrorCodePermissionInvalid_004be160
 *        and DAT_004be180 for the out-of-range fallback. */
void sk_f_0005e4ac(uint8_t error_code)
{
  char *text;
  uint8_t out[0x20];

  if (9 < error_code) {
    sk_x_00117CC4(out, (uint8_t *)&sk_g_004be180, 0x20);
    sk_x_0000178C(out, 0x20);
    return;
  }
  switch (error_code) {
  default:
    text = sk_str_004be040;                  /* s_L4_ErrorCodeSuccess_004be040 */
    break;
  case 1:
    text = sk_str_004be060;                  /* s_L4_ErrorCodePreempted_004be060 */
    break;
  case 2:
    text = sk_str_004be080;                  /* s_L4_ErrorCodeCanceled_004be080 */
    break;
  case 3:
    text = sk_str_004be0a0;                  /* s_L4_ErrorCodeTruncated_004be0a0 */
    break;
  case 4:
    text = sk_str_004be0c0;                  /* s_L4_ErrorCodeCapInvalid_004be0c0 */
    break;
  case 5:
    text = sk_str_004be0e0;                  /* s_L4_ErrorCodeSlotInvalid_004be0e0 */
    break;
  case 6:
    text = sk_str_004be100;                  /* s_L4_ErrorCodeMethodInvalid_004be100 */
    break;
  case 7:
    text = sk_str_004be120;                  /* s_L4_ErrorCodeArgumentInvalid_004be120 */
    break;
  case 8:
    text = sk_str_004be140;                  /* s_L4_ErrorCodeOperationInvalid_004be140 */
    break;
  case 9:
    text = sk_str_004be160;                  /* s_L4_ErrorCodePermissionInvalid_004be160 */
  }
  sk_x_00117CC4(out, text, 0x20);
  return;
}

/* FUN_0005e4cc @ 0x0005e4cc   (est. l4_error_code_to_string_degenerate)
 * Ghidra: void FUN_0005e4cc(void)
 * A degenerate variant that reads an uninitialized register (unaff_w20) as the
 * selector and dispatches through an empty switch, then calls the print helper.
 * The body is effectively a no-op shell whose real logic was not recovered by the
 * decompiler; all switch cases are empty.
 * Confidence: low
 * Notes: Ghidra artifact `unaff_w20` is an uninitialized register, so `selector`
 *        is a stand-in local; the call FUN_00117cc4() has no visible arguments. */
void sk_f_0005e4cc(void)
{
  uint8_t selector;                 /* Ghidra unaff_w20 (uninitialized register) */

  if (9 < selector) {
    sk_x_00117CC4();
    sk_x_0000178C();
    return;
  }
  switch (selector) {
  default:
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
  }
  sk_x_00117CC4();
  return;
}

/* FUN_0005e4d8 @ 0x0005e4d8   (est. xrt_dump_thread_info)
 * Ghidra: void FUN_0005e4d8(long param_1,undefined8 param_2,undefined8 param_3,ulong param_4)
 * Dumps a thread descriptor (param_1) into an output buffer described by out_buf[2]
 * (initialized from param_2/param_3) using the append helper sk_f_0005e8a4. Emits the
 * caller context header, then, unless the flags bit 0 is set, a multi-line registry
 * dump: component selector/name, thread stack range, call stack, address, TSS base,
 * IPC buffer, SCID/ECID/numeric ID/EPID, and a panic backtrace header. The backtrace
 * walks a frame table (from thread+0x158) and prints each entry.
 * Confidence: medium
 * Notes: references the s____s___s_at_PC__0x_012zx__LR__0x_005bcb91 and related
 *        registry/thread strings; backtrace walk uses SoftwareBreakpoint(0x5519,0x5e8a4)
 *        on out-of-bounds entries. */
void sk_f_0005e4d8(int64_t thread, uint64_t out_lo, uint64_t out_hi, uint64_t flags)
{
  uint64_t out_buf[2];
  uint64_t cursor;
  bool again;
  uint64_t entry_addr;
  int64_t count;

  out_buf[0] = out_lo;
  out_buf[1] = out_hi;
  sk_f_0005e8a4(out_buf, 0, sk_str_005bcb91);          /* "(s: %s @ PC 0x%012zx, LR 0x... */
  if ((flags & 1) == 0) {
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcbb9);        /* s_Address_space_ID__0x_016llx_005bcbb9 */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcbd6);        /* s_Component_ID__0x_016llx_005bcbd6 */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcbef);        /* s_Component_selector__0x_016llx_005bcbef */
    sk_f_0005e958(*(uint32_t *)(thread + 0xd8));
    sk_f_0005e958(*(uint32_t *)(thread + 0xe0));
    sk_f_0005e958(*(uint32_t *)(thread + 0xdc));
    sk_f_0005e958(*(uint32_t *)(thread + 0xe4));
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcc0e);        /* s_space_endpoint_component_name_ID_005bcc0e */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcc3d);        /* s_Thread_stack_range__0x_012zx__0x_005bcc3d */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcc65);        /* s_Thread_call_stack__0x_012zx__0x__005bcc65 */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcc8c);        /* s_Thread_address__0x_012zx_005bcc8c */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcca6);        /* s_Thread_TSS_base__0x_012zx_005bcca6 */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bccc1);        /* s_Thread_IPC_buffer__0x_012zx_005bccc1 */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bccde);        /* s_Thread_SCID__0x_016llx_005bccde */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bccf6);        /* s_Thread_ECID__0x_016llx_005bccf6 */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcd0e);        /* s_Thread_numeric_ID__0x_016llx_005bcd0e */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcd2c);        /* s_Thread_EPID__0x_016llx_005bcd2c */
    sk_f_0005e8a4(out_buf, 1, sk_str_005bcd44);        /* s_Panic_backtrace__005bcd44 */
    cursor = thread + 0x160;
    count = -0xc;
    do {
      if (thread + 0x1b8U < cursor) {
        /* WARNING: Does not return */
        SoftwareBreakpoint(0x5519, 0x5e8a4);
      }
      entry_addr = thread + 0x158U + (*(uint64_t *)(cursor - 8) >> 0x30) * 0x10;
      if (2 < *(uint64_t *)(cursor - 8) >> 0x31 || entry_addr == 0) {
        return;
      }
      if (entry_addr < thread + 0x158U || thread + 0x1b8U < entry_addr + 0x10 ||
          entry_addr + 0x10 < entry_addr) {
        /* WARNING: Does not return */
        SoftwareBreakpoint(0x5519, 0x5e8a4);
      }
      sk_f_0005e8a4(out_buf, 1, sk_str_005bcd56);      /* s_____02zd___02hhX_02hhX_02hhX_02h_005bcd56 */
      cursor = cursor + 8;
      again = (count != -1);
      count = count + 1;
    } while (again);
  }
  return;
}

/* FUN_0005e8a4 @ 0x0005e8a4   (est. xrt_outbuf_append)
 * Ghidra: void FUN_0005e8a4(ulong *param_1,ulong param_2,undefined8 param_3)
 * Appends a formatted string to an output buffer described by out[2]: out[0] is the
 * current write position and out[1] is the remaining capacity. If remaining capacity
 * is at least 2 bytes, the string param_3 is formatted into the buffer (mode bit 0
 * selects the fallback path that first measures the formatted length into scratch)
 * and the position/capacity are advanced by the produced length (clamped to capacity).
 * A buffer-wrap condition trips SoftwareBreakpoint(0x5519,0x5e940).
 * Confidence: medium
 * Notes: FUN_00116bb4 is the format helper (sk_x_00116BB4); `va` stands in for the
 *        Ghidra `&stack0x00000000` vararg anchor. */
void sk_f_0005e8a4(uint64_t *out, uint64_t mode, const char *fmt)
{
  uint64_t room;
  uint64_t len;
  uint64_t base;
  uint64_t cap;
  uint64_t newpos;
  va_list va;
  uint8_t scratch;
  int n;

  if (1 < out[1]) {
    if ((mode & 1) == 0) {
      room = out[1];
    }
    else {
      n = sk_x_00116BB4(&scratch, 1, fmt, &va);
      if (n < 0) {
        return;
      }
      room = out[1];
      if (room <= (uint64_t)n) {
        return;
      }
    }
    n = sk_x_00116BB4(out[0], room, fmt, &va);
    len = (uint64_t)(n & ((int)n >> 0x1f ^ 0xffffffffU));   /* abs(n) */
    base = out[0];
    cap = out[1];
    if (cap <= len) {
      len = cap - 1;
    }
    newpos = base + len;
    if (base + cap < newpos || newpos < base) {
      /* WARNING: Does not return */
      SoftwareBreakpoint(0x5519, 0x5e940);
    }
    out[0] = newpos;
    out[1] = cap - len;
  }
  return;
}

/* FUN_0005e958 @ 0x0005e958   (est. sanitize_short_name)
 * Ghidra: undefined8 FUN_0005e958(undefined4 param_1)
 * Sanitizes a 4-byte name (param_1): any byte that is not an alphanumeric or one of
 * the permitted punctuation characters is replaced with '?' (0x3f). The name is then
 * NUL-terminated. The recovered logic packs the sanitized bytes back into an 8-byte
 * value (local_8) by walking the byte frame; an out-of-range walk trips
 * SoftwareBreakpoint(0x5519,0x5ea94).
 * Confidence: low
 * Notes: Ghidra artifact stack layout (local_10/uStack_c/local_8/bStack_11) is
 *        reproduced via a local byte frame[0x11]. */
uint64_t sk_f_0005e958(uint32_t name)
{
  uint8_t frame[0x11];
  uint8_t *fill_ptr;
  uint8_t *dst_ptr;
  uint8_t *src_ptr;
  int64_t idx;
  int64_t fill_cnt;
  uint8_t ch;
  uint32_t u;
  uint64_t packed;

  *(uint32_t *)&frame[0] = name;         /* local_10 */
  *(uint32_t *)&frame[4] = 0;            /* uStack_c */
  idx = 0;
  do {
    ch = frame[idx];                     /* *(byte *)(&local_10 + idx) */
    if (ch == 0) {
      if (idx == 0) {
        idx = 4;
        fill_cnt = 4;
        fill_ptr = &frame[0];
        goto fill_loop;
      }
      break;
    }
    u = (uint32_t)ch;
    if (((9 < u - 0x30 && 0x19 < (ch & 0xffffffdf) - 0x41) &&
         (0x3c < u - 0x23 || (1 << ((u - 0x23) & 0x3f) & 0x1000000000000587) == 0)) &&
        (u != 0x7e)) {
      frame[idx] = 0x3f;                 /* replace invalid char with '?' */
    }
    idx = idx + 1;
  } while (idx != 4);
  goto terminate;
  for (;;) {                             /* fill remaining name bytes with '?' */
    *fill_ptr = 0x3f;
    fill_cnt = fill_cnt - 1;
    fill_ptr = fill_ptr + 1;
    if (fill_cnt == 0) {
      break;
    }
fill_loop:
    if (&frame[5] <= fill_ptr || fill_ptr < &frame[0]) {
      goto out_of_range;
    }
  }
terminate:
  dst_ptr = &frame[0] + idx;
  if (dst_ptr < &frame[5] && &frame[0] <= dst_ptr) {
    *dst_ptr = 0;                        /* NUL-terminate */
    *(uint64_t *)&frame[8] = 0;          /* local_8 = 0 */
    dst_ptr = &frame[8];
    for (;;) {
      src_ptr = &frame[0x10] + idx;      /* &bStack_11 + idx */
      if (&frame[5] <= src_ptr || src_ptr < &frame[0] ||
          &frame[0xd] <= dst_ptr || dst_ptr < &frame[8]) {
        break;
      }
      *dst_ptr = *src_ptr;
      idx = idx - 1;
      dst_ptr = dst_ptr + 1;
      if (idx == 0) {
        return *(uint64_t *)&frame[8];
      }
    }
  }
out_of_range:
  /* WARNING: Does not return */
  SoftwareBreakpoint(0x5519, 0x5ea94);
  return 0;
}

/* FUN_0005ea94 @ 0x0005ea94   (est. put_message_region)
 * Ghidra: long FUN_0005ea94(undefined8 param_1,ulong param_2,ulong param_3,uint param_4)
 * Writes param_2 bytes from the source buffer param_1 into the current thread's
 * message region at offset param_3 (each offset unit is 8 bytes past the thread base),
 * and, when param_4 is nonzero, appends a NUL byte after the copied data. Returns the
 * next free offset unit (param_3 + ceil((param_2+param_4)/8)). Bounds are checked
 * against the 0x37-unit message area; overflow triggers a panic ("size/offset bigger
 * than available message").
 * Confidence: medium
 * Notes: references s_size_0x_zx_bigger_than_available_005bcebc and
 *        s_offset_0x_zx_bigger_than_message_005bce90; `thread_base` = tpidrro_el0. */
int64_t sk_f_0005ea94(uint64_t src, uint64_t size, uint64_t offset, uint32_t nul_flag)
{
  uint8_t *thread_base;
  uint8_t *dst;
  int64_t remaining;

  if (offset < 0x37) {
    remaining = offset * -8 + 0x1b8;
    if (size + nul_flag <= (uint64_t)remaining) {
      thread_base = (uint8_t *)tpidrro_el0;
      if (size <= (uint64_t)remaining) {
        dst = thread_base + offset * 8 + 8;
        sk_x_00117CC4(dst, (uint8_t *)src, size);
        if (dst <= dst + size) {
          if (nul_flag != 0) {
            dst = dst + size;
            if (thread_base + 0x1c0 <= dst || dst < thread_base) {
              /* WARNING: Does not return */
              SoftwareBreakpoint(0x5519, 0x5eae8);
            }
            *dst = 0;
          }
          return (int64_t)(offset + (size + nul_flag + 7 >> 3));
        }
      }
      /* WARNING: Does not return */
      SoftwareBreakpoint(0x5519, 0x5eae8);
    }
    sk_f_0005b190(0, sk_str_005bcebc);   /* s_size_0x_zx_bigger_than_available_005bcebc */
    __builtin_unreachable();
  }
  sk_f_0005b190(0, sk_str_005bce90);     /* s_offset_0x_zx_bigger_than_message_005bce90 */
  __builtin_unreachable();
}

/* FUN_0005eb78 @ 0x0005eb78   (est. get_message_region)
 * Ghidra: long FUN_0005eb78(ulong param_1,ulong param_2,ulong param_3)
 * Copies param_2 bytes from the current thread's message region at offset param_3 into
 * the destination buffer param_1 and returns the next free offset unit
 * (param_3 + ceil(param_2/8)). Out-of-range offset/size triggers a panic
 * ("size/offset bigger than available message").
 * Confidence: medium
 * Notes: references s_size_0x_zx_bigger_than_available_005bcebc and
 *        s_offset_0x_zx_bigger_than_message_005bce90; `thread_base` = tpidrro_el0. */
int64_t sk_f_0005eb78(uint64_t dst, uint64_t size, uint64_t offset)
{
  uint64_t thread_base;
  int64_t remaining;

  if (offset < 0x37) {
    remaining = offset * -8 + 0x1b8;
    if (size <= (uint64_t)remaining) {
      thread_base = (uint64_t)(uintptr_t)tpidrro_el0;
      sk_x_00117CC4((uint8_t *)dst, (uint8_t *)(thread_base + offset * 8 + 8), size);
      if (dst <= dst + size) {
        return (int64_t)(offset + (size + 7 >> 3));
      }
      /* WARNING: Does not return */
      SoftwareBreakpoint(0x5519, 0x5ec20);
    }
    sk_f_0005b190(0, sk_str_005bcebc);   /* s_size_0x_zx_bigger_than_available_005bcebc */
    __builtin_unreachable();
  }
  sk_f_0005b190(0, sk_str_005bce90);     /* s_offset_0x_zx_bigger_than_message_005bce90 */
  __builtin_unreachable();
}

/* FUN_0005ec20 @ 0x0005ec20   (est. set_message_register)
 * Ghidra: void FUN_0005ec20(uint param_1,undefined8 param_2)
 * Stores the 8-byte value param_2 into message register param_1 of the current thread,
 * little-endian byte-by-byte at thread_base + param_1*8 + 8. An index >= 0x37 panics
 * ("set message register %d out of bounds").
 * Confidence: high
 * Notes: references s_set_message_register__d_out_of_b_005bcdd0; thread_base = tpidrro_el0. */
void sk_f_0005ec20(uint32_t index, uint64_t value)
{
  uint64_t thread_base;
  uint8_t *slot;

  if (index < 0x37) {
    thread_base = (uint64_t)(uintptr_t)tpidrro_el0;
    slot = (uint8_t *)(thread_base + (uint64_t)index * 8);
    slot[8] = (uint8_t)value;
    slot[0xd] = (uint8_t)(value >> 0x28);
    slot[0xb] = (uint8_t)(value >> 0x18);
    slot[10] = (uint8_t)(value >> 0x10);
    slot[9] = (uint8_t)(value >> 8);
    slot[0xc] = (uint8_t)(value >> 0x20);
    slot[0xf] = (uint8_t)(value >> 0x38);
    slot[0xe] = (uint8_t)(value >> 0x30);
    return;
  }
  /* WARNING: Subroutine does not return */
  sk_f_0005b190(0, sk_str_005bcdd0);     /* s_set_message_register__d_out_of_b_005bcdd0 */
  __builtin_unreachable();
}

/* FUN_0005ec98 @ 0x0005ec98   (est. get_message_register)
 * Ghidra: ulong FUN_0005ec98(uint param_1)
 * Reads message register param_1 of the current thread as a little-endian 8-byte value
 * (assembled byte-by-byte from thread_base + param_1*8 + 8). An index >= 0x37 panics
 * ("get message register %d out of bounds").
 * Confidence: high
 * Notes: references s_get_message_register__d_out_of_b_005bce00; thread_base = tpidrro_el0. */
uint64_t sk_f_0005ec98(uint32_t index)
{
  uint64_t thread_base;
  uint8_t *slot;

  if (index < 0x37) {
    thread_base = (uint64_t)(uintptr_t)tpidrro_el0;
    slot = (uint8_t *)(thread_base + (uint64_t)index * 8);
    return (uint64_t)slot[10] << 0x10 | (uint64_t)slot[0xb] << 0x18 |
           (uint64_t)*(uint16_t *)(slot + 8) |
           (uint64_t)((uint32_t)slot[0xe] << 0x10 | (uint32_t)slot[0xf] << 0x18 |
                      (uint32_t)*(uint16_t *)(slot + 0xc)) << 0x20;
  }
  /* WARNING: Subroutine does not return */
  sk_f_0005b190(0, sk_str_005bce00);     /* s_get_message_register__d_out_of_b_005bce00 */
  __builtin_unreachable();
}

/* FUN_0005ed18 @ 0x0005ed18   (est. set_src_cap_register)
 * Ghidra: void FUN_0005ed18(uint param_1,undefined8 param_2)
 * Stores the 8-byte capability value param_2 into source capability register param_1
 * (index < 4) of the current thread, little-endian byte-by-byte at
 * thread_base + param_1*8 + 0x1c0. An index >= 4 panics ("set src cap register %d out
 * of bounds"); an out-of-bounds store target trips SoftwareBreakpoint(0x5519,0x5ed84).
 * Confidence: high
 * Notes: references s_set_src_cap_register__d_out_of_b_005bce30; thread_base = tpidrro_el0. */
void sk_f_0005ed18(uint32_t index, uint64_t value)
{
  uint64_t thread_base;
  uint8_t *slot;

  if (3 < index) {
    /* WARNING: Subroutine does not return */
    sk_f_0005b190(0, sk_str_005bce30);   /* s_set_src_cap_register__d_out_of_b_005bce30 */
    __builtin_unreachable();
  }
  thread_base = (uint64_t)(uintptr_t)tpidrro_el0;
  slot = (uint8_t *)(thread_base + (uint64_t)index * 8);
  if ((uint8_t *)(slot + 0x1c8) <= (uint8_t *)(thread_base + 0x1e0) &&
      (uint8_t *)(slot + 0x1c0) <= (uint8_t *)(slot + 0x1c8)) {
    slot[0x1c0] = (uint8_t)value;
    slot[0x1c5] = (uint8_t)(value >> 0x28);
    slot[0x1c3] = (uint8_t)(value >> 0x18);
    slot[0x1c2] = (uint8_t)(value >> 0x10);
    slot[0x1c1] = (uint8_t)(value >> 8);
    slot[0x1c4] = (uint8_t)(value >> 0x20);
    slot[0x1c7] = (uint8_t)(value >> 0x38);
    slot[0x1c6] = (uint8_t)(value >> 0x30);
    return;
  }
  /* WARNING: Does not return */
  SoftwareBreakpoint(0x5519, 0x5ed84);
}

/* FUN_0005edac @ 0x0005edac   (est. set_dst_cap_register)
 * Ghidra: void FUN_0005edac(uint param_1,undefined8 param_2)
 * Stores the 8-byte capability value param_2 into destination capability register
 * param_1 (index < 4) of the current thread, little-endian byte-by-byte at
 * thread_base + param_1*8 + 0x1e0. An index >= 4 panics ("set dst cap register %d out
 * of bounds"); an out-of-bounds store target trips SoftwareBreakpoint(0x5519,0x5ee18).
 * Confidence: high
 * Notes: references s_set_dst_cap_register__d_out_of_b_005bce60; thread_base = tpidrro_el0. */
void sk_f_0005edac(uint32_t index, uint64_t value)
{
  uint64_t thread_base;
  uint8_t *slot;

  if (3 < index) {
    /* WARNING: Subroutine does not return */
    sk_f_0005b190(0, sk_str_005bce60);   /* s_set_dst_cap_register__d_out_of_b_005bce60 */
    __builtin_unreachable();
  }
  thread_base = (uint64_t)(uintptr_t)tpidrro_el0;
  slot = (uint8_t *)(thread_base + (uint64_t)index * 8);
  if ((uint8_t *)(slot + 0x1e8) <= (uint8_t *)(thread_base + 0x200) &&
      (uint8_t *)(slot + 0x1e0) <= (uint8_t *)(slot + 0x1e8)) {
    slot[0x1e0] = (uint8_t)value;
    slot[0x1e5] = (uint8_t)(value >> 0x28);
    slot[0x1e3] = (uint8_t)(value >> 0x18);
    slot[0x1e2] = (uint8_t)(value >> 0x10);
    slot[0x1e1] = (uint8_t)(value >> 8);
    slot[0x1e4] = (uint8_t)(value >> 0x20);
    slot[0x1e7] = (uint8_t)(value >> 0x38);
    slot[0x1e6] = (uint8_t)(value >> 0x30);
    return;
  }
  /* WARNING: Does not return */
  SoftwareBreakpoint(0x5519, 0x5ee18);
}

/* FUN_0005ee40 @ 0x0005ee40   (est. extract_priority_field)
 * Ghidra: ulong FUN_0005ee40(ulong param_1)
 * Extracts a 3-bit field from param_1 by shifting right 6 and masking with 7.
 * Confidence: high
 * Notes: trivial bit-field extraction. */
uint64_t sk_f_0005ee40(uint64_t value)
{
  return value >> 6 & 7;
}


/* part9.c — SK11 slice 0x0005ee48..0x0005fd24 (cL4 "xrt" thread-runtime).
 * Faithful English-first transcriptions of the Ghidra decompiles in
 * /tmp/sk11b/<addr>.txt.  Cross-slice callees use sk_x_/sk_str_/sk_g_
 * (predeclared); intra-slice callees use sk_f_<addr>.
 *
 * Local helpers (LE 64-bit byte stores/loads used by the decompiler's
 * message-register byte dances and 128-bit pairs). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

static inline void sk_p9_store_le64(uint8_t *dst, uint64_t v)
{
    dst[0] = (uint8_t)(v);
    dst[1] = (uint8_t)(v >> 8);
    dst[2] = (uint8_t)(v >> 16);
    dst[3] = (uint8_t)(v >> 24);
    dst[4] = (uint8_t)(v >> 32);
    dst[5] = (uint8_t)(v >> 40);
    dst[6] = (uint8_t)(v >> 48);
    dst[7] = (uint8_t)(v >> 56);
}

static inline uint64_t sk_p9_load_le64(const uint8_t *src)
{
    return (uint64_t)src[0] | ((uint64_t)src[1] << 8) | ((uint64_t)src[2] << 16) |
           ((uint64_t)src[3] << 24) | ((uint64_t)src[4] << 32) | ((uint64_t)src[5] << 40) |
           ((uint64_t)src[6] << 48) | ((uint64_t)src[7] << 56);
}

/* FUN_0005ee48 @ 0x0005ee48   (est. ipc_buffer_word)
 * Ghidra: ulong FUN_0005ee48(ulong param_1)
 * Extracts a 16-bit field from a thread/IPC word: the high 16 bits (bits 16-31).
 * Pure bit extraction helper for message/capability register words.
 * Confidence: high
 * Notes: none. */
uint64_t sk_f_0005ee48(uint64_t word)
{
    return (word >> 0x10) & 0xffff;
}

/* FUN_0005ee50 @ 0x0005ee50   (est. ipc_buffer_index)
 * Ghidra: ulong FUN_0005ee50(ulong param_1)
 * Extracts the low 6 bits (0x3f) of a thread/IPC word — an index/slot field.
 * Pure bit-extraction helper.
 * Confidence: high
 * Notes: none. */
uint64_t sk_f_0005ee50(uint64_t word)
{
    return word & 0x3f;
}

/* FUN_0005ee58 @ 0x0005ee58   (est. message_reg_pack)
 * Ghidra: ulong FUN_0005ee58(ulong param_1,ulong param_2,uint param_3,int param_4)
 * Packs a message/capability-register selector word: low 6 bits from param_1,
 * 3 bits from param_2 at bits 6-8, param_3 at bits 16+, and an enabled bit
 * (0x1000 when param_4 != 0) that gates the 13-bit slot field.
 * Confidence: high
 * Notes: none. */
uint64_t sk_f_0005ee58(uint64_t low_field, uint64_t mid_field, uint32_t high_field, int32_t enabled)
{
    uint64_t enabled_mask = 0x1000;
    if (enabled == 0) {
        enabled_mask = 0;
    }
    return (low_field & 0x3f) | ((mid_field & 7) << 6) | ((uint64_t)high_field << 0x10) | enabled_mask;
}

/* FUN_0005ee7c @ 0x0005ee7c   (est. xrt_init_once)
 * Ghidra: void FUN_0005ee7c(void)
 * One-time xrt runtime initialisation gated by a global flag bit: if not yet
 * initialised, run the (idempotent) per-cpu setup helpers, bump the active-thread
 * counter, and set the flag.  Called at each thread entry to lazily prime state.
 * Confidence: medium
 * Notes: DAT_006b26a0 is the init-flag global; counter at thread registry +0x38. */
void sk_f_0005ee7c(void)
{
    if ((sk_g_006b26a0 & 1) == 0) {
        if ((sk_x_0006054c() & 1) == 0) {
            sk_x_00064108();
        }
        uint64_t registry = sk_f_0005bb68();
        *(uint16_t *)(registry + 0x38) = *(uint16_t *)(registry + 0x38) + 1;
        sk_g_006b26a0 = 1;
    }
    return;
}

/* FUN_0005eec4 @ 0x0005eec4   (est. thread_create)
 * Ghidra: void FUN_0005eec4(ulong *param_1,undefined8 param_2,ulong param_3,long param_4,int param_5)
 * Creates a new thread: allocates the TCB and a stack via the runtime allocator
 * (an ops table), wires the TCB fields (parent, priority 0x11, stack bounds),
 * configures a user IPC buffer, publishes the thread ID through the TPIDRRO
 * message registers, registers the thread with the kernel (CallSupervisor), then
 * builds the scheduler message and enqueues it.  On any step failure the thread is
 * torn down, an error is reported, and the TCB count is decremented.  On success
 * the new TCB is stored through param_1.  Stack canary at local_70.
 * Confidence: medium
 * Notes: strings "Failed to make thread stack" (sk_str_005bd182) and "Thread stack
 *        allocation size" (sk_str_005bd1af); L4_ErrorCode* strings via sk_str_004be1b0..;
 *        DAT_004be2f0 is an unknown-string global; _DAT_004be1a0/_004be1a8 a 16-byte
 *        msg header global; tpidrro_el0 is the message-register area; allocator ops at
 *        auVar33._8_8_ (+0x30/+0x40), thread ops table local_b8 entries [0]/[1]/[3]/[10];
 *        counters DAT_006b26a4..bc are failure tallies; sk_x_0011D7E8 = stack-check fail. */
void sk_f_0005eec4(uint64_t *out_tcb, uint64_t creator, uint64_t entry_arg, int64_t stack_extra,
                   int32_t flags)
{
    int64_t stack_guard = -0x2c8502b44bfffed6;
    uint8_t err_buf[32];                            /* error-code decode buffer */
    uint64_t registry = sk_f_0005bb68();
    uint16_t *counter_ptr = (uint16_t *)(registry + 0x38);
    uint16_t counter = *counter_ptr;
    *counter_ptr = (uint16_t)(counter + 1);
    uint64_t thread = 0;                            /* raw TCB (hoisted for register_thread) */
    uint64_t priority = 0x11;                       /* default thread priority */

    if (counter < 0x400) {
        thread = sk_f_0005c0ac();          /* allocate raw TCB */
        if (thread != 0) {
            sk_f_0005db7c((uint64_t *)0);   /* decompiler dropped thread arg */
            goto register_thread;
        }

        int64_t stack_size = 0x24000;
        int64_t stack_low = 0;
        uint64_t alloc_ctx = 0;
        uint64_t *rt_ops = (uint64_t *)0x0;   /* thread ops table */

        int32_t is_kernel_thread = sk_x_00054DE4();
        uint32_t alloc_flags = 0x40c8;
        if (is_kernel_thread == 0) {
            alloc_flags = 0x41140c8;
        }
        sk_u128_t alloc = sk_x_00034A2C();       /* 16-byte pair: lo=cookie, hi=allocator ops */
        uint8_t **alloc_ops = (uint8_t **)alloc.hi;
        char ok = ((int (*)(uint64_t, uint64_t, void *, void *, uint64_t, uint64_t))
                   alloc_ops[6])(alloc.lo, alloc_flags, &priority, &alloc_ctx, 0, 0);
        uint64_t check = sk_x_00054DE4();
        if (((check & 1) == 0) &&
            ((char)(((int (*)(void *, uint64_t, uint64_t, uint64_t))rt_ops[10])
                    (alloc_ctx, 0, 0x4000, 0x20000)) != 0)) {
fail_stack_alloc:
            uint64_t msg = (uint64_t)sk_str_005bd182;      /* "Failed to make thread stack" */
            goto panic_path;
        }
        if (ok != 0) {
            sk_g_006b26a4 += 1;
            goto decrement;
        }
        if (rt_ops == (uint64_t *)0x0) {
            sk_x_00054354();                               /* noreturn */
        }
        ((void (*)(void *, void *))rt_ops[1])(alloc_ctx, &priority);
        thread = sk_x_000612E0(stack_low, stack_size);
        if (thread + 0x178 < thread) goto overflow_trap;
        int64_t stack_top = sk_x_000613EC(thread, 0);
        uint64_t avail = (uint64_t)((stack_low - stack_top) + stack_size);
        if (0x1ffff < avail) {
            uint64_t msg = (uint64_t)sk_str_005bd1af;      /* "Thread stack allocation size..." */
            goto panic_path;
        }
        uint64_t resolved_stack = avail;
        is_kernel_thread = sk_x_00054DE4();
        if (is_kernel_thread != 0) {
            resolved_stack = 0x20000;
        }
        ok = ((int (*)(void *, void *))rt_ops[3])(alloc_ctx, &resolved_stack);
        if (ok == 0) {
            sk_x_001143A0(thread, 0, 0x178);               /* zero TCB header */
            *(uint64_t *)(thread + 0x30) = alloc_ctx;
            *(uint64_t **)(thread + 0x38) = rt_ops;
            *(int64_t *)(thread + 0x138) = stack_size;
            *(int64_t *)(thread + 0x130) = stack_low;
            *(int64_t *)(thread + 0x140) = stack_top;
            *(int64_t *)(thread + 0x168) = stack_low + 0x4000;
            *(int64_t *)(thread + 0x170) = stack_top;
            uint64_t thread_id = sk_x_00061488(thread);
            int64_t tcb_alloc = sk_x_00034F70();
            if (tcb_alloc == 0) {
                sk_g_006b26ac += 1;
            } else {
                alloc = sk_x_00034A2C();
                alloc_ops = (uint8_t **)alloc.hi;
                ok = ((int (*)(uint64_t, uint64_t, uint64_t, uint64_t))
                      alloc_ops[8])(alloc.lo, thread_id, 1, tcb_alloc);
                if (ok == 0) {
                    int64_t user_tcb = sk_x_00034F70();
                    *(int64_t *)(thread + 0x70) = user_tcb;
                    if (user_tcb == 0) {
                        sk_g_006b26b4 += 1;
                    } else {
                        uint64_t ipc_buf = sk_x_0019AE2C(6);
                        *(uint64_t *)(thread + 0x28) = ipc_buf;
                        if (ipc_buf == 0) {
                            sk_g_006b26b8 += 1;
                        } else {
                            uint8_t *msg_regs = (uint8_t *)tpidrro_el0;
                            sk_p9_store_le64(&msg_regs[0], (uint64_t)tcb_alloc);
                            CallSupervisor(0);
                            sk_p9_store_le64(&msg_regs[0], (uint64_t)tcb_alloc);
                            if ((ipc_buf & 0xff) != 0) {
                                uint8_t err_code = sk_x_004B6E24(ipc_buf, err_buf);
                                if (err_code < 10) {
                                    const char *err_str;
                                    switch (err_code) {
                                    default:
                                        err_str = sk_str_004be1b0;   /* L4_ErrorCodeSuccess */
                                        break;
                                    case 1:
                                        err_str = sk_str_004be1d0;   /* Preempted */
                                        break;
                                    case 2:
                                        err_str = sk_str_004be1f0;   /* Canceled */
                                        break;
                                    case 3:
                                        err_str = sk_str_004be210;   /* Truncated */
                                        break;
                                    case 4:
                                        err_str = sk_str_004be230;   /* CapInvalid */
                                        break;
                                    case 5:
                                        err_str = sk_str_004be250;   /* SlotInvalid */
                                        break;
                                    case 6:
                                        err_str = sk_str_004be270;   /* MethodInvalid */
                                        break;
                                    case 7:
                                        err_str = sk_str_004be290;   /* ArgumentInvalid */
                                        break;
                                    case 8:
                                        err_str = sk_str_004be2b0;   /* OperationInvalid */
                                        break;
                                    case 9:
                                        err_str = sk_str_004be2d0;   /* PermissionInvalid */
                                        break;
                                    }
                                    sk_x_00117CC4(err_str, 0x20);
                                    return;
                                }
                                sk_x_00117CC4((uint8_t *)&sk_g_004be2f0, 0x20);
                                sk_x_0000178C(0x20);
                                return;
                            }
                            if (ipc_buf == 0) {
                                int64_t ipc_buf_obj = *(int64_t *)(thread + 0x28);
                                uint64_t proto_id = sk_f_0005d77c(0, 0xb);
                                sk_p9_store_le64(&msg_regs[0], proto_id);
                                CallSupervisor(0);
                                sk_p9_store_le64(&msg_regs[0], proto_id);
                                if (ipc_buf_obj == 0) {
                                    uint64_t st = sk_x_00064C24(thread, 9);
                                    if ((st & 1) == 0) {
alloc_failed_notify:
                                        sk_x_004B6E88();
                                    } else {
                                        int64_t sch_result = sk_x_000603C4();
                                        if (sch_result == 0) {
                                            goto register_thread;
                                        }
                                        int64_t tcb2 = *(int64_t *)(thread + 0x28);
                                        msg_regs[0] = 1;
                                        msg_regs[1] = 0; msg_regs[2] = 0; msg_regs[3] = 0;
                                        msg_regs[4] = 0; msg_regs[5] = 0; msg_regs[6] = 0;
                                        msg_regs[7] = 0;
                                        sk_p9_store_le64(&msg_regs[8], (uint64_t)sch_result);
                                        CallSupervisor(0);
                                        msg_regs[0] = 1;
                                        msg_regs[1] = 0; msg_regs[2] = 0; msg_regs[3] = 0;
                                        msg_regs[4] = 0; msg_regs[5] = 0; msg_regs[6] = 0;
                                        msg_regs[7] = 0;
                                        if (tcb2 == 0) goto register_thread;
                                        sk_x_004B6E74(tcb2, 0x13);
                                    }
                                    sk_x_004B6E9C(thread);
                                } else {
                                    sk_g_006b26bc += 1;
                                }
                            }
                            sk_x_0019AE60(*(uint64_t *)(thread + 0x28), 6);
                        }
                        sk_x_004B23D8(*(uint64_t *)(thread + 0x70));
                    }
                } else {
                    sk_g_006b26b0 += 1;
                }
                sk_x_004B23D8((uint64_t)tcb_alloc);
            }
        } else {
            sk_g_006b26a8 += 1;
        }
        ((void (*)(void *))rt_ops[0])(alloc_ctx);
    }
    goto decrement;

register_thread:
    {
        uint64_t now = sk_x_000604FC();
        *(uint64_t *)(thread + 0x120) = now;
        uint32_t digits_val = (uint32_t)now + ((((uint32_t)now >> 3) & 0x1fff) / 0x7d) * -1000;
        uint32_t packed = 0x54;                       /* leading 'T' */
        uint32_t scale = 1000;
        bool more;
        do {
            uint32_t divisor = scale / 10;
            uint32_t digit = 0;
            if (divisor != 0) {
                digit = (digits_val & 0xffff) / divisor;
            }
            packed = ((digit + 0x30) & 0xffff) | (packed << 8);
            digits_val = digits_val - digit * divisor;
            more = 0x13 < scale;
            scale = divisor;
        } while (more);
        *(uint32_t *)(thread + 0x118) = packed;
        *(uint64_t *)(thread + 0x128) = thread;
        uint64_t ipc_buf = *(uint64_t *)(thread + 0x28);
        uint8_t *msg_regs = (uint8_t *)tpidrro_el0;
        sk_p9_store_le64(&msg_regs[0], thread);
        CallSupervisor(0);
        sk_p9_store_le64(&msg_regs[0], thread);
        if ((ipc_buf & 0xff) != 0) {
            sk_x_004B6ED0(ipc_buf, &priority);
            goto fail_stack_alloc;
        }
        *(uint64_t *)(thread + 0x18) = creator;
        *(uint64_t *)(thread + 0x20) = entry_arg;
        *(uint64_t *)(thread + 0x90) = 0;
        *(uint64_t *)(thread + 0x40) = 0;
        *(uint64_t *)(thread + 0x48) = 0;
        *(uint64_t *)(thread + 0x50) = 0;
        *(uint64_t *)(thread + 0x58) = 0;
        *(uint8_t *)(thread + 0x80) = 0;
        *(uint32_t *)(thread + 0x84) = 0;
        *(uint64_t *)(thread + 0xa8) = 0;
        *(uint64_t *)(thread + 8) = 0;
        *(uint64_t *)(thread + 0x10) = 0;
        if (thread + 0x178 < thread) goto overflow_trap;
        int64_t reg_tcb = sk_x_0006156C(thread, 8);
        int64_t sched = sk_x_00063FFC();
        if (sched == 0) {
            reg_tcb = 0;
        } else {
            sk_x_0006402C(reg_tcb);
        }
        int64_t *slot = (int64_t *)sk_x_000614F8(thread);
        sk_x_001143A0(slot, 0, 0x100);
        slot[0x1f] = 0;
        slot[0] = reg_tcb;
        slot[1] = thread;
        int64_t cur_state = sk_x_00063A50();
        int64_t cur_tpidr = (int64_t)tpidr_el0;
        if (*(int64_t *)(cur_state + 0x208) == -1) {
            sk_x_004B6F48();
        } else if (*(int64_t *)(cur_tpidr + 0xf8) == 0) {
            slot[2] = *(int64_t *)(cur_tpidr + 0x10);
            if (slot + 0x20 < slot) goto overflow_trap;
            sk_x_00063CFC(slot);
            cl4_result_t range = sk_x_000613EC(thread, stack_extra);  /* 16-byte {lo,hi} */
            uint64_t range_hi = range.hi;
            uint64_t range_lo = range.lo;
            if ((*(int64_t *)(thread + 0x130) - (int64_t)range_lo) +
                *(int64_t *)(thread + 0x138) < 0x20000) {
                if (stack_extra != 0) {
                    if (((entry_arg + (uint64_t)stack_extra < entry_arg) ||
                         (range_lo + (uint64_t)stack_extra < range_lo) ||
                         (sk_x_00117CC4(range_lo, entry_arg, stack_extra),
                          range_lo + (uint64_t)stack_extra < range_lo) ||
                         (range_lo != 0 && range_lo + (uint64_t)stack_extra <= range_lo)))
                        goto overflow_trap;
                    *(uint64_t *)(thread + 0x20) = range_lo;
                }
                sk_x_000612D8(thread, sk_x_004B6430);
                /* build the scheduler message in the TPIDRRO register area */
                sk_p9_store_le64(&msg_regs[0x10], thread);
                sk_x_00114330(&msg_regs[0x18], 0x10);
                msg_regs[0x28] = 0xbc;
                msg_regs[0x29] = 0xfa;
                msg_regs[0x2a] = 5;
                msg_regs[0x2b] = 0;
                msg_regs[0x2c] = 0;
                msg_regs[0x2d] = 0;
                msg_regs[0x2e] = 0;
                msg_regs[0x2f] = 0;
                sk_p9_store_le64(&msg_regs[0x30], range_lo);
                sk_p9_store_le64(&msg_regs[0x38], (uint64_t)slot);
                uint64_t slot_id = sk_x_00061488(thread);
                sk_p9_store_le64(&msg_regs[0x40], slot_id);
                uint64_t hdr_hi = sk_g_004be1a8;
                uint64_t hdr_lo = sk_g_004be1a0;
                int64_t ipc2 = *(int64_t *)(thread + 0x28);
                sk_p9_store_le64(&msg_regs[0], hdr_lo);
                sk_p9_store_le64(&msg_regs[8], hdr_hi);
                CallSupervisor(0);
                msg_regs[0] = 0; msg_regs[1] = 0; msg_regs[2] = 0; msg_regs[3] = 0;
                msg_regs[4] = 0; msg_regs[5] = 0; msg_regs[6] = 0; msg_regs[7] = 0;
                if (ipc2 == 0) {
                    int32_t dbg = sk_x_00060540();
                    if ((flags != 0) && (dbg == 0)) {
                        sk_f_0005d84c(thread, 1);
                    }
                    sk_f_0005be84(thread, 0);
                    *out_tcb = thread;
                    goto done;
                }
            }
            sk_x_004B6D60(thread, range_hi);
            goto decrement;
        }
        sk_x_004B6F20();
        counter_ptr = (uint16_t *)(thread >> 0x38);
        goto alloc_failed_notify;
    }

overflow_trap:
    SoftwareBreakpoint(0x5519, 0x5f588);

panic_path:
    sk_f_0005b190(0, msg);       /* noreturn panic */

decrement:
    *counter_ptr = (uint16_t)(*counter_ptr - 1);

done:
    if (stack_guard == -0x2c8502b44bfffed6) {
        return;
    }
    sk_x_0011D7E8();             /* noreturn stack-check fail */
}

/* FUN_0005fac0 @ 0x0005fac0   (est. thread_suspend)
 * Ghidra: void FUN_0005fac0(long param_1)
 * Suspends a thread: runs its suspend hook (*(param_1+0x18) fn, arg *(param_1+0x20)),
 * then the shared suspend path — marks the TCB suspended (0x84 = 2 after the
 * message-register wait), publishes the current TCB, waits on the message register
 * and decrements the thread count.  Falls into a debugger break (SoftwareBreakpoint)
 * as "suspend should not return".  Takes param_1 as the thread.
 * Confidence: medium
 * Notes: string "suspend should not return" (sk_str_005bd02d); callees are the
 *        wait/suspend helpers; sk_f_0005b190 is the noreturn panic. */
void sk_f_0005fac0(int64_t thread)
{
    ((void (*)(uint64_t))*(uint64_t *)(thread + 0x18))(*(uint64_t *)(thread + 0x20));
    uint64_t suspend_arg = sk_f_0005fad8(0);
    uint64_t thread = sk_x_00060524();
    if (thread <= thread + 0x178) {
        sk_f_0005b0bc();
        sk_x_00063DD4();
        *(uint64_t *)(thread + 0x40) = suspend_arg;
        *(uint8_t *)(thread + 0x80) = 1;
        int32_t *wait_reg = (int32_t *)(thread + 0x84);
        uint32_t reg_id = ((uint32_t)wait_reg >> 4) & 0xf;
        uint64_t word = sk_f_0005dc4c(reg_id);
        int32_t wval = *wait_reg;
        while (wval == 0) {
            sk_f_0005dc8c(reg_id, (uint64_t)(uintptr_t)wait_reg, (uint64_t)(uintptr_t)word, 0, 0);
            word = sk_f_0005dc4c(reg_id);
            wval = *wait_reg;
        }
        sk_f_0005dd70((((uint32_t)(thread + 0x80) >> 4) & 0xf), (uint64_t)(uintptr_t)(thread + 0x80), 5, 0);
        if (wval == 2) {
            sk_f_0005bf20(thread);
            uint64_t registry = sk_f_0005bb68();
            uint16_t *counter_ptr = (uint16_t *)(registry + 0x38);
            uint16_t counter = *counter_ptr;
            *counter_ptr = (uint16_t)(counter - 1);
            sk_f_0005be84((((uint64_t)((uint32_t)((uint64_t)counter_ptr >> 32))) << 32) |
                          (uint64_t)counter, thread, 1);
        }
        sk_x_00060524();
        sk_f_0005db7c((uint64_t *)0);   /* decompiler dropped thread arg */
        sk_f_0005b190(0, (uint64_t)sk_str_005bd02d);   /* noreturn panic */
    }
    SoftwareBreakpoint(0x5519, 0x5fbc0);
}

/* FUN_0005fad8 @ 0x0005fad8   (est. suspend_core)
 * Ghidra: void FUN_0005fad8(undefined8 param_1)
 * Core suspend path (shared with thread_suspend): publishes the current TCB, marks
 * it suspended, waits on the message register and decrements the thread count, then
 * reports "suspend should not return" (noreturn panic).  param_1 is stored as the
 * suspend wake value at thread+0x40.
 * Confidence: medium
 * Notes: string sk_str_005bd02d; sk_f_0005b190 noreturn panic. */
void sk_f_0005fad8(uint64_t wake_value)
{
    uint64_t thread = sk_x_00060524();
    if (thread <= thread + 0x178) {
        sk_f_0005b0bc();
        sk_x_00063DD4();
        *(uint64_t *)(thread + 0x40) = wake_value;
        *(uint8_t *)(thread + 0x80) = 1;
        int32_t *wait_reg = (int32_t *)(thread + 0x84);
        uint32_t reg_id = ((uint32_t)wait_reg >> 4) & 0xf;
        uint64_t word = sk_f_0005dc4c(reg_id);
        int32_t wval = *wait_reg;
        while (wval == 0) {
            sk_f_0005dc8c(reg_id, (uint64_t)(uintptr_t)wait_reg, (uint64_t)(uintptr_t)word, 0, 0);
            word = sk_f_0005dc4c(reg_id);
            wval = *wait_reg;
        }
        sk_f_0005dd70((((uint32_t)(thread + 0x80) >> 4) & 0xf), (uint64_t)(uintptr_t)(thread + 0x80), 5, 0);
        if (wval == 2) {
            sk_f_0005bf20(thread);
            uint64_t registry = sk_f_0005bb68();
            uint16_t *counter_ptr = (uint16_t *)(registry + 0x38);
            uint16_t counter = *counter_ptr;
            *counter_ptr = (uint16_t)(counter - 1);
            sk_f_0005be84((((uint64_t)((uint32_t)((uint64_t)counter_ptr >> 32))) << 32) |
                          (uint64_t)counter, thread, 1);
        }
        sk_x_00060524();
        sk_f_0005db7c((uint64_t *)0);   /* decompiler dropped thread arg */
        sk_f_0005b190(0, (uint64_t)sk_str_005bd02d);   /* noreturn panic */
    }
    SoftwareBreakpoint(0x5519, 0x5fbc0);
}

/* FUN_0005fbc0 @ 0x0005fbc0   (est. thread_mark_suspended)
 * Ghidra: void FUN_0005fbc0(long param_1)
 * Marks a thread suspended: writes 2 into the wait register field at param_1+0x84
 * and publishes that field via sk_f_0005dd70.  Simple state transition helper.
 * Confidence: high
 * Notes: none. */
void sk_f_0005fbc0(int64_t thread)
{
    *(uint32_t *)(thread + 0x84) = 2;
    sk_f_0005dd70((((uint32_t)(thread + 0x84) >> 4) & 0xf), (uint64_t)(uintptr_t)(thread + 0x84), 5, 0);
    return;
}

/* FUN_0005fbdc @ 0x0005fbdc   (est. send_msg_with_caps)
 * Ghidra: void FUN_0005fbdc(undefined8 param_1,undefined8 param_2,long param_3)
 * Sends an IPC message (param_1 = destination/thread) carrying a value (param_2) and
 * an optional capability-transfer count (param_3): resolves the capability(s) via
 * sk_f_0005c86c and performs the message send via sk_f_0005d5e8.
 * Confidence: medium
 * Notes: none. */
void sk_f_0005fbdc(uint64_t dest, uint64_t value, int64_t cap_count)
{
    uint64_t caps = 0;
    if (cap_count != 0) {
        caps = sk_f_0005c86c(2, cap_count, 0, 1);
    }
    uint64_t value = sk_f_0005c86c(2, value, 0, 0);
    sk_f_0005d5e8(dest, 2, value, caps);
    return;
}

/* FUN_0005fc54 @ 0x0005fc54   (est. send_128bit_msg)
 * Ghidra: void FUN_0005fc54(undefined8 param_1,undefined8 *param_2,undefined8 param_3)
 * Sends a 128-bit IPC message: builds a zeroed 16-byte local, populates it via the
 * cap lookup (sk_f_0005c924 / sk_f_0005cb24), combines the 128-bit value with the
 * caller's 128-bit operand via the 128-bit op sk_x_0019AE9C, then hands the local
 * (as the value word) to sk_f_0005fbdc.
 * Confidence: medium
 * Notes: FUN_0019ae9c is a 128-bit combine op; local_40 is the 16-byte buffer whose
 *        address is passed to sk_f_0005fbdc as its value word (decompiler type decay). */
void sk_f_0005fc54(uint64_t dest, uint64_t *value_ptr, uint64_t cap_count)
{
    uint8_t value128[16];
    sk_p9_store_le64(&value128[0], 0);
    sk_p9_store_le64(&value128[8], 0);
    uint64_t cap = sk_f_0005c924(2);
    sk_f_0005cb24(2, cap, value128, 0);
    sk_u128_t combined = sk_x_0019AE9C(sk_p9_load_le64(&value128[0]),
                                       sk_p9_load_le64(&value128[8]),
                                       value_ptr[0], value_ptr[1]);
    sk_p9_store_le64(&value128[0], combined.lo);
    sk_p9_store_le64(&value128[8], combined.hi);
    sk_f_0005fbdc(dest, (uint64_t)(uintptr_t)value128, cap_count);
    return;
}

/* FUN_0005fccc @ 0x0005fccc   (est. populate_stack_128k)
 * Ghidra: void FUN_0005fccc(long param_1)
 * Populates a thread's stack region: invokes the stack-populate op (entry +0x18 of
 * the ops table at param_1+0x38) with the user handle (param_1+0x30) and a requested
 * 0x20000-byte extent; on failure panics "failed to populate stack".
 * Confidence: medium
 * Notes: string sk_str_005bd169; sk_f_0005b190 noreturn panic. */
void sk_f_0005fccc(int64_t thread)
{
    uint64_t extent = 0x20000;
    char ok = ((int (*)(uint64_t, void *))
               (*(uint64_t *)(thread + 0x38) + 0x18))(*(uint64_t *)(thread + 0x30), &extent);
    if (ok == '\0') {
        return;
    }
    sk_f_0005b190(0, (uint64_t)sk_str_005bd169);   /* noreturn panic */
}

/* FUN_0005fd24 @ 0x0005fd24   (est. populate_stack_48k)
 * Ghidra: void FUN_0005fd24(long param_1)
 * Populates a thread's stack region with a 0xc000-byte extent via the same stack
 * populate op as FUN_0005fccc; panics "failed to populate stack" on failure.
 * Confidence: medium
 * Notes: string sk_str_005bd169; sk_f_0005b190 noreturn panic. */
void sk_f_0005fd24(int64_t thread)
{
    uint64_t extent = 0xc000;
    char ok = ((int (*)(uint64_t, void *))
               (*(uint64_t *)(thread + 0x38) + 0x18))(*(uint64_t *)(thread + 0x30), &extent);
    if (ok == '\0') {
        return;
    }
    sk_f_0005b190(0, (uint64_t)sk_str_005bd169);   /* noreturn panic */
}


/* ---- Disassembly-based reconstructions (decompiler failed) ----
 * These 14 addresses are register-ABI / tail fragments that Ghidra's
 * auto-analysis carved into FUN_* entries but the decompiler collapsed to a
 * bare `return;` (it cannot recover the input registers x8/x9/x10/x19/x20 or
 * the sp+0x18/sp+0x28 struct slots). Reconstructed from disassemble_function
 * (fallback, per contract). Semantics below are faithful to the instruction
 * stream; the exact C signature / return convention is uncertain, hence
 * confidence low. */

/* FUN_0005c380 @ 0x0005c380   (est. le128_load_from_bytes)
 * Ghidra: void FUN_0005c380(void)
 * Reads 16 bytes from the base register (x8) and assembles them into two
 * little-endian 64-bit words (bytes 0-7 -> lo, bytes 8-15 -> hi) via byte
 * loads and OR-shift accumulation; the two words are delivered in x9/x10
 * (non-standard register result convention).
 * Confidence: low
 * Notes: fallback=disassemble_function; register-ABI fragment; decompiler
 *   returned bare `return;`. */
unsigned long sk_f_0005c380(const uint8_t *b, uint64_t *lo, uint64_t *hi)
{
    *lo = (uint64_t)b[0] | ((uint64_t)b[1] << 8) | ((uint64_t)b[2] << 16) |
          ((uint64_t)b[3] << 24) | ((uint64_t)b[4] << 32) | ((uint64_t)b[5] << 40) |
          ((uint64_t)b[6] << 48) | ((uint64_t)b[7] << 56);
    *hi = (uint64_t)b[8] | ((uint64_t)b[9] << 8) | ((uint64_t)b[10] << 16) |
          ((uint64_t)b[11] << 24) | ((uint64_t)b[12] << 32) | ((uint64_t)b[13] << 40) |
          ((uint64_t)b[14] << 48) | ((uint64_t)b[15] << 56);
    return 0;
}

/* FUN_0005c414 @ 0x0005c414   (est. le32_word_from_bytes_tail)
 * Ghidra: void FUN_0005c414(void)
 * Tail fragment: continues assembling a little-endian 32-bit word from bytes
 * at [x8+4..x8+7] and ORs it into the running 64-bit value (x9/x10 are live
 * inputs from a preceding fragment).
 * Confidence: low
 * Notes: fallback=disassemble_function; continuation fragment, no standalone
 *   entry/exit; decompiler returned bare `return;`. */
unsigned long sk_f_0005c414(const uint8_t *b, uint64_t *acc)
{
    uint32_t w = (uint32_t)b[4] | ((uint32_t)b[5] << 8) | ((uint32_t)b[6] << 16) |
                 ((uint32_t)b[7] << 24);
    *acc |= (uint64_t)w;
    return *acc;
}

/* FUN_0005c440 @ 0x0005c440   (est. le16_le32_field_build)
 * Ghidra: void FUN_0005c440(void)
 * Preserves x9/x10 (stp to sp+0x18), then assembles a little-endian 16-bit
 * value from [x8+0x10..x8+0x11] and a little-endian 32-bit value from
 * [x8+2..x8+5] into x9/x10.
 * Confidence: low
 * Notes: fallback=disassemble_function; register-ABI fragment (x8 base);
 *   decompiler returned bare `return;`. */
unsigned long sk_f_0005c440(const uint8_t *b, uint16_t *w16, uint32_t *w32)
{
    *w16 = (uint16_t)((uint16_t)b[0x10] | ((uint16_t)b[0x11] << 8));
    *w32 = (uint32_t)b[2] | ((uint32_t)b[3] << 8) | ((uint32_t)b[4] << 16) |
           ((uint32_t)b[5] << 24);
    return 0;
}

/* FUN_0005c468 @ 0x0005c468   (est. le32_word_from_bytes)
 * Ghidra: void FUN_0005c468(void)
 * Assembles a little-endian 32-bit word from bytes [x8+0..x8+3] into x9; the
 * fragment continues past 0x5c48c (body truncated by the disassembler).
 * Confidence: low
 * Notes: fallback=disassemble_function; fragment; decompiler returned bare
 *   `return;`. */
unsigned long sk_f_0005c468(const uint8_t *b, uint32_t *out)
{
    *out = (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) |
           ((uint32_t)b[3] << 24);
    return 0;
}

/* FUN_0005c490 @ 0x0005c490   (est. le32_word_upper_bits)
 * Ghidra: void FUN_0005c490(void)
 * Assembles a little-endian 32-bit word from bytes [x8+2..x8+5] and ORs it
 * into the running x9 (continuation of a preceding word-build).
 * Confidence: low
 * Notes: fallback=disassemble_function; fragment; decompiler returned bare
 *   `return;`. */
unsigned long sk_f_0005c490(const uint8_t *b, uint64_t *acc)
{
    uint32_t w = (uint32_t)b[2] | ((uint32_t)b[3] << 8) | ((uint32_t)b[4] << 16) |
                 ((uint32_t)b[5] << 24);
    *acc |= (uint64_t)w;
    return *acc;
}

/* FUN_0005c4a8 @ 0x0005c4a8   (est. le32_word_tail)
 * Ghidra: void FUN_0005c4a8(void)
 * Assembles a little-endian 32-bit word from bytes [x8+2..x8+5] into x8 and
 * ORs it with the running w10 (continuation fragment).
 * Confidence: low
 * Notes: fallback=disassemble_function; fragment; decompiler returned bare
 *   `return;`. */
unsigned long sk_f_0005c4a8(const uint8_t *b, uint32_t *acc)
{
    uint32_t w = (uint32_t)b[2] | ((uint32_t)b[3] << 8) | ((uint32_t)b[4] << 16) |
                 ((uint32_t)b[5] << 24);
    *acc |= w;
    return *acc;
}

/* FUN_0005c4c0 @ 0x0005c4c0   (est. le64_pair_from_bytes)
 * Ghidra: void FUN_0005c4c0(void)
 * Assembles two little-endian words from bytes at [x8+8..x8+0xd] and
 * [x8+4..x8+7], ORs them into the running x9/x10, and spills both to
 * sp+0x18/sp+0x20 (struct-slot result convention).
 * Confidence: low
 * Notes: fallback=disassemble_function; register-ABI fragment; decompiler
 *   returned bare `return;`. */
unsigned long sk_f_0005c4c0(const uint8_t *b, uint64_t *lo, uint64_t *hi)
{
    uint32_t wlo = (uint32_t)b[4] | ((uint32_t)b[5] << 8) | ((uint32_t)b[6] << 16) |
                   ((uint32_t)b[7] << 24);
    uint32_t whi = (uint32_t)b[8] | ((uint32_t)b[9] << 8) | ((uint32_t)b[10] << 16) |
                   ((uint32_t)b[11] << 24);
    *lo = (uint64_t)wlo;
    *hi = (uint64_t)whi;
    return 0;
}

/* FUN_0005c510 @ 0x0005c510   (est. magic_word_store)
 * Ghidra: void FUN_0005c510(void)
 * Builds the 64-bit constant 0x0000006400006574 ('et'|'d' — a tag fragment)
 * and stores it (with a zero high word) to sp+0x28. Fragment of an init
 * routine; no input registers used.
 * Confidence: low
 * Notes: fallback=disassemble_function; stores to stack slot sp+0x28;
 *   decompiler returned bare `return;`. */
unsigned long sk_f_0005c510(void)
{
    return 0x0000006400006574ull; /* stored to sp+0x28 by the fragment */
}

/* FUN_0005c520 @ 0x0005c520   (est. tag_word_store)
 * Ghidra: void FUN_0005c520(void)
 * Builds the little-endian 32-bit tag 0x6c61766e ("nval") with the byte 0x69
 * ('i') extending it to 0x64696c61766e, stores it to sp+0x28, and loads the
 * string pointer at image base 0x4bd000+0xf6f into x8 (returned by the
 * fragment). Fragment of a name/magic initializer.
 * Confidence: low
 * Notes: fallback=disassemble_function; stores to sp+0x28; string ref
 *   0x4bd000+0xf6f; decompiler returned bare `return;`. */
unsigned long sk_f_0005c520(void)
{
    /* tag 0x64696c61766e ("nvalid" bytes LE), plus string ptr 0x4bd000+0xf6f */
    return 0x64696c61766eull;
}

/* FUN_0005c53c @ 0x0005c53c   (est. low_byte_masked_lookup)
 * Ghidra: void FUN_0005c53c(void)
 * Saves x0 into x20, loads the global pointer at image base 0x64c000+0xc98
 * into x19, masks both x20 and x0 to their low byte, and returns (x16 holds
 * the masked x0 — a selector-index lookup helper).
 * Confidence: low
 * Notes: fallback=disassemble_function; global DAT_0064cc98; register result
 *   convention; decompiler returned bare `return;`. */
unsigned long sk_f_0005c53c(uint64_t selector)
{
    /* x19 = *(uint64_t *)(0x64c000+0xc98) — table base (unused in this frag) */
    return selector & 0xff;
}

/* FUN_0005c558 @ 0x0005c558   (est. tag_word_store_b)
 * Ghidra: void FUN_0005c558(void)
 * Builds the little-endian 32-bit tag 0x00737365 ("ess"), stores it to
 * sp+0x28, and loads string pointer 0x4bd000+0xeef. Fragment.
 * Confidence: low
 * Notes: fallback=disassemble_function; stores to sp+0x28; string ref
 *   0x4bd000+0xeef; decompiler returned bare `return;`. */
unsigned long sk_f_0005c558(void)
{
    return 0x0000737365ull;
}

/* FUN_0005c570 @ 0x0005c570   (est. tag_word_store_c)
 * Ghidra: void FUN_0005c570(void)
 * Builds the little-endian 32-bit tag 0x64656c65 ("led"), stores it to
 * sp+0x28, and loads string pointer 0x4bd000+0xf2f. Fragment.
 * Confidence: low
 * Notes: fallback=disassemble_function; stores to sp+0x28; string ref
 *   0x4bd000+0xf2f; decompiler returned bare `return;`. */
unsigned long sk_f_0005c570(void)
{
    return 0x000064656c65ull;
}

/* FUN_0005c5a0 @ 0x0005c5a0   (est. ptr_shift_pair_store)
 * Ghidra: void FUN_0005c5a0(void)
 * Stores {sp+0x18, x20>>8} as a pair to [sp], and moves x19 into x0 (result).
 * Fragment passing an address and a shifted selector as a stack pair.
 * Confidence: low
 * Notes: fallback=disassemble_function; register-ABI fragment; decompiler
 *   returned bare `return;`. */
unsigned long sk_f_0005c5a0(uint64_t sel_hi)
{
    /* stores (uint64_t)(sp+0x18) and (sel_hi >> 8) as a pair to [sp];
     * result in x0 from x19 */
    return sel_hi >> 8;
}

/* FUN_0005cf14 @ 0x0005cf14   (est. noop_return)
 * Ghidra: void FUN_0005cf14(void)
 * Body is a single `ret` — a genuine no-op (does nothing, returns).
 * Confidence: low
 * Notes: fallback=disassemble_function; the only instruction is ret. */
unsigned long sk_f_0005cf14(void)
{
    return 0;
}
