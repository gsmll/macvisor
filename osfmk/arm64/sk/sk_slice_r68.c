/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x00663c04-0x0066afe8 (worker SKR68): the cL4 error-code / IPC result
 * stringification layer and its surrounding helpers — per-selector-group L4
 * error-code-to-string tables, string table copies, message-register / result
 * register dispatch, the 16-uint8_t result-pair helpers, and the 
 * function-pointer-table dispatch used by the operation wrappers. Many
 * functions share the same error-string switch pattern with distinct table
 * bases (0x68a080/0x68a0c8/0x68a240/0x68a3c8/0x68a4a8 ...).
 *
 * Function C identifiers are address-based (sk_f_<addr>) so the 120 functions
 * of this slice call one another deterministically regardless of definition
 * order; descriptive estimated names live in the per-function comments and in
 * docs/sptm/manifest.json.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include "sk_internal.h"

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

/* External callees (outside this slice). Address-based names; each declared
 * `unsigned long` (64-bit ABI word) with an unspecified parameter list so any
 * call site compiles. Ghidra FUN_ address is ground truth. sk_f_ = in-slice
 * (defined below), sk_x_ = out-of-slice extern. 16-uint8_t-return helpers return
 * sk_u128_t. */
typedef struct { uint64_t lo; uint64_t hi; } sk_u128_t;

extern void sk_f_00663c04(uint64_t msg_buf, uint8_t err_code);   /* FUN_0000663c04 */
extern void sk_f_00663d3c(int64_t obj, uint64_t count);   /* FUN_0000663d3c */
extern void sk_f_006642bc(uint64_t *obj, uint64_t flags, uint64_t unused, uint64_t *result);   /* FUN_00006642bc */
extern uint64_t sk_f_00664304(int64_t obj, int64_t index);   /* FUN_0000664304 */
extern void sk_f_00664330(uint64_t new_owner);   /* FUN_0000664330 */
extern void sk_f_006643b8(uint64_t new_owner);   /* FUN_00006643b8 */
extern void sk_f_0066453c(void);   /* FUN_000066453c */
extern uint64_t sk_f_0066455c(uint64_t obj);   /* FUN_000066455c */
extern void sk_f_00664588(uint64_t obj);   /* FUN_0000664588 */
extern uint32_t sk_f_006645bc(uint64_t obj);   /* FUN_00006645bc */
extern void sk_f_006645ec(uint64_t unused, uint64_t *slot);   /* FUN_00006645ec */
extern void sk_f_0066469c(void);   /* FUN_000066469c */
extern void sk_f_006646e0(void);   /* FUN_00006646e0 */
extern uint64_t sk_f_006646f4(uint64_t slot_value, uint64_t slot_meta, uint64_t register_flag);   /* FUN_00006646f4 */
extern void sk_f_0066479c(void);   /* FUN_000066479c */
extern void sk_f_006647d0(int64_t slot_idx, int64_t slot_value, uint64_t slot_meta, int register_flag);   /* FUN_00006647d0 */
extern void sk_f_006648a8(void);   /* FUN_00006648a8 */
extern void sk_f_006648dc(int64_t dest);   /* FUN_00006648dc */
extern void sk_f_006649b4(void);   /* FUN_00006649b4 */
extern void sk_f_00664a84(uint64_t new_tls);   /* FUN_0000664a84 */
extern uint64_t sk_f_00664a8c(int64_t *slot_idx, uint64_t table_id);   /* FUN_0000664a8c */
extern uint64_t sk_f_00664bd4(void);   /* FUN_0000664bd4 */
extern void sk_f_00664c04(void);   /* FUN_0000664c04 */
extern void sk_f_00664cbc(void);   /* FUN_0000664cbc */
extern long sk_f_0066512c(uint64_t arg0, uint64_t fault, int64_t tcb);   /* FUN_000066512c */
extern void sk_f_00665354(uint64_t buf, uint8_t code);   /* FUN_0000665354 */
extern uint64_t sk_f_00665498(uint64_t arg0, uint64_t obj);   /* FUN_0000665498 */
extern void sk_f_006654b8(uint64_t arg0, int64_t cap, int64_t *msg);   /* FUN_00006654b8 */
extern void sk_f_00665630(uint64_t *node);   /* FUN_0000665630 */
extern void sk_f_00665660(uint64_t arg0, int64_t cap, int64_t *msg);   /* FUN_0000665660 */
extern void sk_f_006657d8(int64_t obj);   /* FUN_00006657d8 */
extern long sk_f_00665860(uint64_t kind);   /* FUN_0000665860 */
extern uint64_t sk_f_0066599c(uint64_t recv, int64_t tcb);   /* FUN_000066599c */
extern void sk_f_00665a38(uint64_t who, uint64_t v0, uint64_t v1);   /* FUN_0000665a38 */
extern sk_u128_t sk_f_00665bd4(void);   /* FUN_0000665bd4 */
extern void sk_f_00665cec(void);   /* FUN_0000665cec */
extern void sk_f_00665d0c(void);   /* FUN_0000665d0c */
extern void sk_f_00665d20(void);   /* FUN_0000665d20 */
extern void sk_f_00665d44(uint64_t param_1, uint64_t param_2, uint64_t param_3);   /* FUN_0000665d44 */
extern void sk_f_00665d60(void);   /* FUN_0000665d60 */
extern void sk_f_00665d70(void);   /* FUN_0000665d70 */
extern void sk_f_00665d84(void);   /* FUN_0000665d84 */
extern void sk_f_00665d9c(uint64_t *desc, uint64_t aux_flag, uint64_t *cap_word);   /* FUN_0000665d9c */
extern sk_u128_t sk_f_00665ef8(const sk_u128_t *src);   /* FUN_0000665ef8 */
extern uint64_t sk_f_00665f04(void);   /* FUN_0000665f04 */
extern void sk_f_0066609c(uint64_t msg_buf, uint8_t err_code);   /* FUN_000066609c */
extern void sk_f_006661d4(uint64_t val);   /* FUN_00006661d4 */
extern void sk_f_006661e0(uint64_t a, uint64_t b);   /* FUN_00006661e0 */
extern unsigned long sk_f_006661f4(unsigned long *entry, unsigned long key, unsigned long *out);   /* FUN_00006661f4 */
extern unsigned long sk_f_0066628c(unsigned long root);   /* FUN_000066628c */
extern unsigned long sk_f_00666298(unsigned long key, unsigned long out);   /* FUN_0000666298 */
extern unsigned long sk_f_006662ac(long *obj, unsigned long a, unsigned long b);   /* FUN_00006662ac */
extern sk_u128_t sk_f_00666344(unsigned long obj, long *out);   /* FUN_0000666344 */
extern unsigned long sk_f_00666448(unsigned long *out, long *pool, unsigned long key, unsigned long size, int flags);   /* FUN_0000666448 */
extern unsigned long sk_f_00666800(void);   /* FUN_0000666800 */
extern unsigned long sk_f_00666808(long *fs, unsigned long *pg, unsigned long tok, unsigned int *ext, int flag);   /* FUN_0000666808 */
extern unsigned long sk_f_00666d84(void);   /* FUN_0000666d84 */
extern unsigned long sk_f_00666d90(unsigned int *src, unsigned int *dst, unsigned char *scratch, long len);   /* FUN_0000666d90 */
extern unsigned long sk_f_00667040(unsigned int *src, unsigned int *out, char *scratch, long budget);   /* FUN_0000667040 */
extern unsigned long sk_f_006673ec(unsigned long *obj);   /* FUN_00006673ec */
extern uint64_t * sk_f_0066745c(uint64_t * desc, uint64_t region);   /* FUN_000066745c */
extern void sk_f_00667530(long buf, long * out);   /* FUN_0000667530 */
extern bool sk_f_00667568(long buf);   /* FUN_0000667568 */
extern bool sk_f_00667578(long buf);   /* FUN_0000667578 */
extern uint64_t sk_f_00667588(long self);   /* FUN_0000667588 */
extern void sk_f_00667870(long self, uint64_t * item);   /* FUN_0000667870 */
extern void sk_f_00667d74(long self, long node);   /* FUN_0000667d74 */
extern void sk_f_00667e54(long self, uint64_t addr);   /* FUN_0000667e54 */
extern void sk_f_00668128(void);   /* FUN_0000668128 */
extern void sk_f_0066834c(long self);   /* FUN_000066834c */
extern uint64_t sk_f_00668c6c(void);   /* FUN_0000668c6c */
extern void sk_f_00668c78(long ptr);   /* FUN_0000668c78 */
extern void sk_f_00668c94(int64_t base);   /* FUN_0000668c94 */
extern void sk_f_00668cb0(uint64_t *out_msg, uint8_t error_code);   /* FUN_0000668cb0 */
extern void sk_f_00668dc4(uint64_t arg);   /* FUN_0000668dc4 */
extern void sk_f_00668dd8(void);   /* FUN_0000668dd8 */
extern uint64_t *sk_f_00668e24(uint64_t pool_base, uint16_t *free_list, int flags);   /* FUN_0000668e24 */
extern void sk_f_006690dc(uint64_t obj);   /* FUN_00006690dc */
extern void sk_f_00669134(uint64_t pool_base, uint16_t *free_list, uint64_t *obj);   /* FUN_0000669134 */
extern uint64_t *sk_f_0066924c(void);   /* FUN_000066924c */
extern uint64_t *sk_f_00669298(void);   /* FUN_0000669298 */
extern void sk_f_006692e4(void);   /* FUN_00006692e4 */
extern void sk_f_00669330(uint64_t obj);   /* FUN_0000669330 */
extern void sk_f_00669388(void);   /* FUN_0000669388 */
extern void sk_f_006693d4(uint64_t arg);   /* FUN_00006693d4 */
extern void sk_f_0066942c(void);   /* FUN_000066942c */
extern void sk_f_00669478(uint64_t arg);   /* FUN_0000669478 */
extern void sk_f_006694d0(void);   /* FUN_00006694d0 */
extern void sk_f_0066951c(uint64_t arg);   /* FUN_000066951c */
extern void sk_f_00669578(void);   /* FUN_0000669578 */
extern void sk_f_00669618(void);   /* FUN_0000669618 */
extern void sk_f_006699e8(int64_t desc);   /* FUN_00006699e8 */
extern void sk_f_00669a48(void);   /* FUN_0000669a48 */
extern uint64_t sk_f_00669af8(uint8_t kind, int64_t base, uint64_t size, uint8_t attr);   /* FUN_0000669af8 */
extern void sk_f_00669c3c(void);   /* FUN_0000669c3c */
extern uint64_t sk_f_00669c98(uint64_t arg);   /* FUN_0000669c98 */
extern uint64_t sk_f_00669cfc(void);   /* FUN_0000669cfc */
extern uint64_t *sk_f_00669db4(void);   /* FUN_0000669db4 */
extern void sk_f_0066a08c(uint64_t param_1);   /* FUN_000066a08c */
extern void sk_f_0066a1cc(uint64_t param_1);   /* FUN_000066a1cc */
extern uint64_t sk_f_0066a1d4(void);   /* FUN_000066a1d4 */
extern uint64_t sk_f_0066a1d8(void);   /* FUN_000066a1d8 */
extern int64_t sk_f_0066a300(void);   /* FUN_000066a300 */
extern uint64_t sk_f_0066a404(uint64_t ctx, uint8_t *desc);   /* FUN_000066a404 */
extern void sk_f_0066a558(uint64_t ctx, int64_t desc, int64_t block);   /* FUN_000066a558 */
extern void sk_f_0066a65c(void);   /* FUN_000066a65c */
extern void sk_f_0066a6b4(uint64_t param_1);   /* FUN_000066a6b4 */
extern void sk_f_0066a70c(uint64_t param_1);   /* FUN_000066a70c */
extern bool sk_f_0066a720(void);   /* FUN_000066a720 */
extern void sk_f_0066a768(void);   /* FUN_000066a768 */
extern void sk_f_0066a7b8(uint64_t value);   /* FUN_000066a7b8 */
extern int64_t *sk_f_0066a808(int64_t region_base, int64_t region_size, int64_t *descriptor);   /* FUN_000066a808 */
extern sk_u128_t sk_f_0066a8c4(void);   /* FUN_000066a8c4 */
extern void sk_f_0066a8f4(uint64_t region, uint64_t arg2, uint64_t arg3);   /* FUN_000066a8f4 */
extern bool sk_f_0066a988(int64_t region);   /* FUN_000066a988 */
extern sk_u128_t sk_f_0066a9bc(int64_t region);   /* FUN_000066a9bc */
extern void sk_f_0066ab40(int64_t region, uint8_t parity, uint64_t index);   /* FUN_000066ab40 */
extern int64_t sk_f_0066ad54(void);   /* FUN_000066ad54 */
extern void sk_f_0066af84(void);   /* FUN_000066af84 */
extern void sk_f_0066afe8(uint64_t *flist);   /* FUN_000066afe8 */

extern unsigned long sk_x_0064e07c();   /* FUN_000064e07c */
extern unsigned long sk_x_0064effc();   /* FUN_000064effc */
extern unsigned long sk_x_00654cc8();   /* FUN_0000654cc8 */
extern unsigned long sk_x_006551c4();   /* FUN_00006551c4 */
extern unsigned long sk_x_00655708();   /* FUN_0000655708 */
extern unsigned long sk_x_00655774();   /* FUN_0000655774 */
extern unsigned long sk_x_0065be08();   /* FUN_000065be08 */
extern unsigned long sk_x_0065c218();   /* FUN_000065c218 */
extern unsigned long sk_x_0065c2f0();   /* FUN_000065c2f0 */
extern unsigned long sk_x_0065cb74();   /* FUN_000065cb74 */
extern unsigned long sk_x_0065cbbc();   /* FUN_000065cbbc */
extern unsigned long sk_x_0065cc0c();   /* FUN_000065cc0c */
extern unsigned long sk_x_0065ccc8();   /* FUN_000065ccc8 */
extern unsigned long sk_x_0065cedc();   /* FUN_000065cedc */
extern unsigned long sk_x_0065db84();   /* FUN_000065db84 */
extern unsigned long sk_x_0065de3c();   /* FUN_000065de3c */
extern unsigned long sk_x_0065f058();   /* FUN_000065f058 */
extern unsigned long sk_x_0065fdb8();   /* FUN_000065fdb8 */
extern sk_u128_t sk_x_00660ab4();   /* FUN_0000660ab4 */
extern unsigned long sk_x_00661318();   /* FUN_0000661318 */
extern unsigned long sk_x_00661324();   /* FUN_0000661324 */
extern unsigned long sk_x_00662098();   /* FUN_0000662098 */
extern unsigned long sk_x_006621f4();   /* FUN_00006621f4 */
extern unsigned long sk_x_00662264();   /* FUN_0000662264 */
extern unsigned long sk_x_0066239c();   /* FUN_000066239c */
extern unsigned long sk_x_00662628();   /* FUN_0000662628 */
extern unsigned long sk_x_006626f8();   /* FUN_00006626f8 */
extern unsigned long sk_x_006631d8();   /* FUN_00006631d8 */
extern unsigned long sk_x_00663928();   /* FUN_0000663928 */
extern unsigned long sk_x_0066ad54();   /* FUN_000066ad54 */
extern unsigned long sk_x_0066b038();   /* FUN_000066b038 */
extern unsigned long sk_x_0066b870();   /* FUN_000066b870 */
extern unsigned long sk_x_0066b878();   /* FUN_000066b878 */
extern unsigned long sk_x_0066bce0();   /* FUN_000066bce0 */
extern unsigned long sk_x_0066bdf4();   /* FUN_000066bdf4 */
extern unsigned long sk_x_0066c084();   /* FUN_000066c084 */
extern unsigned long sk_x_0066c354();   /* FUN_000066c354 */
extern unsigned long sk_x_0066c5d0();   /* FUN_000066c5d0 */
extern unsigned long sk_x_0066c5f8();   /* FUN_000066c5f8 */
extern unsigned long sk_x_0067203c();   /* FUN_000067203c */
extern unsigned long sk_x_00677674();   /* FUN_0000677674 */
extern unsigned long sk_x_006777d8();   /* FUN_00006777d8 */
extern unsigned long sk_x_006782b4();   /* FUN_00006782b4 */
extern unsigned long sk_x_006787a0();   /* FUN_00006787a0 */
extern unsigned long sk_x_00678a64();   /* FUN_0000678a64 */
extern unsigned long sk_x_0067a7f0();   /* FUN_000067a7f0 */
extern unsigned long sk_x_0067aa00();   /* FUN_000067aa00 */
extern unsigned long sk_x_0067aeb0();   /* FUN_000067aeb0 */
extern unsigned long sk_x_0067b220();   /* FUN_000067b220 */
extern unsigned long sk_x_0067cc18();   /* FUN_000067cc18 */
extern unsigned long sk_x_0067cfe0();   /* FUN_000067cfe0 */
extern unsigned long sk_x_0067cffc();   /* FUN_000067cffc */
extern unsigned long sk_x_0067d02c();   /* FUN_000067d02c */
extern unsigned long sk_x_0067d1f0();   /* FUN_000067d1f0 */
extern unsigned long sk_x_0067d72c();   /* FUN_000067d72c */
extern unsigned long sk_x_0067f660();   /* FUN_000067f660 */
extern unsigned long sk_x_006832c8();   /* FUN_00006832c8 */
extern unsigned long sk_x_006833d4();   /* FUN_00006833d4 */
extern sk_u128_t sk_x_00684d1c();   /* FUN_0000684d1c */
extern unsigned long sk_x_00685234();   /* FUN_0000685234 */
extern unsigned long sk_x_006853e4();   /* FUN_00006853e4 */
extern unsigned long sk_x_0068543c();   /* FUN_000068543c */
extern unsigned long sk_x_00685458();   /* FUN_0000685458 */
extern unsigned long sk_x_006854e8();   /* FUN_00006854e8 */
extern unsigned long sk_x_00685538();   /* FUN_0000685538 */
extern unsigned long sk_x_00685588();   /* FUN_0000685588 */
extern unsigned long sk_x_00685608();   /* FUN_0000685608 */
extern unsigned long sk_x_00685658();   /* FUN_0000685658 */
extern unsigned long sk_x_006856a8();   /* FUN_00006856a8 */
extern unsigned long sk_x_00685864();   /* FUN_0000685864 */
extern unsigned long sk_x_00685928();   /* FUN_0000685928 */
extern unsigned long sk_x_0068596c();   /* FUN_000068596c */
extern unsigned long sk_x_00685a6c();   /* FUN_0000685a6c */
extern unsigned long sk_x_00685acc();   /* FUN_0000685acc */
extern unsigned long sk_x_00685b50();   /* FUN_0000685b50 */
extern unsigned long sk_x_00685b88();   /* FUN_0000685b88 */
extern unsigned long sk_x_00685c2c();   /* FUN_0000685c2c */
extern unsigned long sk_x_00685c64();   /* FUN_0000685c64 */
extern unsigned long sk_x_00685ca0();   /* FUN_0000685ca0 */
extern unsigned long sk_x_00685cd8();   /* FUN_0000685cd8 */
extern unsigned long sk_x_00685d10();   /* FUN_0000685d10 */
extern unsigned long sk_x_00685d4c();   /* FUN_0000685d4c */
extern unsigned long sk_x_00685d84();   /* FUN_0000685d84 */
extern unsigned long sk_x_00685dbc();   /* FUN_0000685dbc */
extern unsigned long sk_x_00685df4();   /* FUN_0000685df4 */
extern unsigned long sk_x_00685e1c();   /* FUN_0000685e1c */
extern unsigned long sk_x_00685e44();   /* FUN_0000685e44 */
extern unsigned long sk_x_00685e6c();   /* FUN_0000685e6c */
extern unsigned long sk_x_00685ea4();   /* FUN_0000685ea4 */
extern unsigned long sk_x_00685ee0();   /* FUN_0000685ee0 */
extern unsigned long sk_x_00685f08();   /* FUN_0000685f08 */
extern unsigned long sk_x_00685f40();   /* FUN_0000685f40 */
extern unsigned long sk_x_00685f78();   /* FUN_0000685f78 */
extern unsigned long sk_x_00685fb0();   /* FUN_0000685fb0 */
extern unsigned long sk_x_00685fe8();   /* FUN_0000685fe8 */
extern unsigned long sk_x_00686020();   /* FUN_0000686020 */
extern unsigned long sk_x_00686058();   /* FUN_0000686058 */
extern unsigned long sk_x_00686084();   /* FUN_0000686084 */
extern unsigned long sk_x_006860bc();   /* FUN_00006860bc */
extern unsigned long sk_x_006860f4();   /* FUN_00006860f4 */
extern unsigned long sk_x_006862a0();   /* FUN_00006862a0 */
extern unsigned long sk_x_006862d8();   /* FUN_00006862d8 */
extern unsigned long sk_x_00686310();   /* FUN_0000686310 */
extern unsigned long sk_x_00686348();   /* FUN_0000686348 */
extern unsigned long sk_x_00686380();   /* FUN_0000686380 */
extern unsigned long sk_x_006863b8();   /* FUN_00006863b8 */
extern unsigned long sk_x_0066b520();   /* FUN_000066b520 */
/* Image-base data globals referenced by this slice (Ghidra DAT_ ground truth). */
extern uint64_t sk_g_0002007e;   /* DAT_000002007e */
extern uint64_t sk_g_0066548c;   /* DAT_000066548c */
extern uint64_t sk_g_0068a080;   /* DAT_000068a080 */
extern uint64_t sk_g_0068a0a0;   /* DAT_000068a0a0 */
extern uint64_t sk_g_0068a0b8;   /* DAT_000068a0b8 */
extern uint64_t sk_g_0068a0c0;   /* DAT_000068a0c0 */
extern uint64_t sk_g_0068a208;   /* DAT_000068a208 */
extern uint64_t sk_g_0068a230;   /* DAT_000068a230 */
extern uint64_t sk_g_0068a238;   /* DAT_000068a238 (uRam0068a238) */
extern uint64_t sk_g_0068a380;   /* DAT_000068a380 */
extern uint64_t sk_g_0068a3a0;   /* DAT_000068a3a0 */
extern uint64_t sk_g_0068a3a8;   /* DAT_000068a3a8 */
extern uint64_t sk_g_0068a3b8;   /* DAT_000068a3b8 */
extern uint64_t sk_g_0068a508;   /* DAT_000068a508 */
extern uint64_t sk_g_0068a518;   /* DAT_000068a518 */
extern uint64_t sk_g_0068a578;   /* DAT_000068a578 */
extern uint64_t sk_g_0068a57c;   /* DAT_000068a57c */
extern uint64_t sk_g_0068a580;   /* DAT_000068a580 */
extern uint64_t sk_g_0068a738;   /* DAT_000068a738 */
extern uint64_t sk_g_0068a960;   /* DAT_000068a960 */
extern uint64_t sk_g_0068aa60;   /* DAT_000068aa60 */
extern uint64_t sk_g_0068aa70;   /* DAT_000068aa70 */
extern uint64_t sk_g_0068aa74;   /* DAT_000068aa74 */
extern uint64_t sk_g_0068aa78;   /* DAT_000068aa78 */
extern uint64_t sk_g_0068aa7c;   /* DAT_000068aa7c */
extern uint64_t sk_g_0068aa80;   /* DAT_000068aa80 */
extern uint64_t sk_g_0068aa88;   /* DAT_000068aa88 */
extern uint64_t sk_g_0068aa90;   /* DAT_000068aa90 */
extern uint64_t sk_g_0068aa94;   /* DAT_000068aa94 */
extern uint64_t sk_g_0068aa98;   /* DAT_000068aa98 */
extern uint64_t sk_g_0068aa9c;   /* DAT_000068aa9c */
extern uint64_t sk_g_0068aaa0;   /* DAT_000068aaa0 */
extern uint64_t sk_g_0068aab0;   /* DAT_000068aab0 */
extern uint64_t sk_g_0068aab4;   /* DAT_000068aab4 */
extern uint64_t sk_g_0068aab8;   /* DAT_000068aab8 */
extern uint64_t sk_g_0068aabc;   /* DAT_000068aabc */
extern uint64_t sk_g_0068aac0;   /* DAT_000068aac0 */
extern uint64_t sk_g_0068aac4;   /* DAT_000068aac4 */
extern uint64_t sk_g_0068aac8;   /* DAT_000068aac8 */
extern uint64_t sk_g_0068aacc;   /* DAT_000068aacc */
extern uint64_t sk_g_0068aad0;   /* DAT_000068aad0 */
extern uint64_t sk_g_0068aad4;   /* DAT_000068aad4 */
extern uint64_t sk_g_0068aad8;   /* DAT_000068aad8 */
extern uint64_t sk_g_0068aadc;   /* DAT_000068aadc */
extern uint64_t sk_g_006b4368;   /* DAT_00006b4368 */
extern uint64_t sk_g_006b56c8;   /* DAT_00006b56c8 */
extern uint64_t sk_g_006b56e0;   /* DAT_00006b56e0 */
extern uint64_t sk_g_006b5838;   /* DAT_00006b5838 */
extern uint64_t sk_g_006b5840;   /* DAT_00006b5840 */
extern uint64_t sk_g_006b5900;   /* DAT_00006b5900 */
extern uint64_t sk_g_006b5a38;   /* DAT_00006b5a38 */
extern uint64_t sk_g_006b5a40;   /* DAT_00006b5a40 */
extern uint64_t sk_g_006b5a48;   /* DAT_00006b5a48 */
extern uint64_t sk_g_006b5a50;   /* DAT_00006b5a50 */
extern uint64_t sk_g_006b5a58;   /* DAT_00006b5a58 */
extern uint64_t sk_g_006b5a68;   /* DAT_00006b5a68 */
extern uint64_t sk_g_006b5a78;   /* DAT_00006b5a78 */
extern uint64_t sk_g_006b5a80;   /* DAT_00006b5a80 */
extern uint64_t sk_g_006b5a88;   /* DAT_00006b5a88 */
extern uint64_t sk_g_006b5a90;   /* DAT_00006b5a90 */
extern uint64_t sk_g_006b5aa0;   /* DAT_00006b5aa0 */
extern uint64_t sk_g_006b5dc0;   /* DAT_00006b5dc0 */
extern uint64_t sk_g_006b5dd8;   /* DAT_00006b5dd8 */
extern uint64_t sk_g_006b5dd9;   /* DAT_00006b5dd9 */
extern uint64_t sk_g_006b5e58;   /* DAT_00006b5e58 */
extern uint64_t sk_g_006b5ed0;   /* DAT_00006b5ed0 */
extern uint64_t sk_g_006b6928;   /* DAT_00006b6928 */
extern uint64_t sk_g_006b6938;   /* DAT_00006b6938 */
extern uint64_t sk_g_006b6998;   /* DAT_00006b6998 */
extern uint64_t sk_g_006b70db;   /* DAT_00006b70db */
extern uint64_t sk_g_006b70dd;   /* DAT_00006b70dd */
extern uint64_t sk_g_006b70de;   /* DAT_00006b70de */
extern uint64_t sk_g_006b70df;   /* DAT_00006b70df */
extern uint64_t sk_g_006b70e1;   /* DAT_00006b70e1 */
extern uint64_t sk_g_006b70e2;   /* DAT_00006b70e2 */
extern uint64_t sk_g_006fe7e8;   /* DAT_00006fe7e8 */
extern uint64_t sk_g_006fe7f0;   /* DAT_00006fe7f0 */
extern uint64_t sk_g_006fe7f8;   /* DAT_00006fe7f8 */
extern uint64_t sk_g_006fe800;   /* DAT_00006fe800 */
extern uint64_t sk_g_006fe808;   /* DAT_00006fe808 */
extern uint64_t sk_g_006fe818;   /* DAT_00006fe818 */
extern uint64_t sk_g_006fe828;   /* DAT_00006fe828 */
extern uint64_t sk_g_006fe8b0;   /* DAT_00006fe8b0 */
extern uint64_t sk_g_006fe8e0;   /* DAT_00006fe8e0 */
extern uint64_t sk_g_006fe8e1;   /* DAT_00006fe8e1 */
extern uint64_t sk_g_006fe8e8;   /* DAT_00006fe8e8 */
extern uint64_t sk_g_006fe8f0;   /* DAT_00006fe8f0 */
extern uint64_t sk_g_006fe8f8;   /* DAT_00006fe8f8 */
extern uint64_t sk_g_006fe8f9;   /* DAT_00006fe8f9 */
extern uint64_t sk_g_006fe904;   /* DAT_00006fe904 */
extern uint64_t sk_g_006fe914;   /* DAT_00006fe914 */
extern uint64_t sk_g_006fe920;   /* DAT_00006fe920 */
extern uint64_t sk_g_006fe930;   /* DAT_00006fe930 */
extern uint64_t sk_g_006fe938;   /* DAT_00006fe938 */
extern uint64_t sk_g_006fe948;   /* DAT_00006fe948 */
extern uint64_t sk_g_006fe958;   /* DAT_00006fe958 */
extern uint64_t sk_g_006fe968;   /* DAT_00006fe968 */
extern uint64_t sk_g_006fe978;   /* DAT_00006fe978 */
extern uint64_t sk_g_006fe988;   /* DAT_00006fe988 */
extern uint64_t sk_g_006fe990;   /* DAT_00006fe990 */
extern uint64_t sk_g_006fe991;   /* DAT_00006fe991 */
extern uint64_t sk_g_006fe998;   /* DAT_00006fe998 */
extern uint64_t sk_g_006fe9a0;   /* DAT_00006fe9a0 */
extern uint64_t sk_g_006fe9a8;   /* DAT_00006fe9a8 */
extern uint64_t sk_g_006fe9a9;   /* DAT_00006fe9a9 */
extern uint64_t sk_g_006fe9b4;   /* DAT_00006fe9b4 */
extern uint64_t sk_g_006fe9c4;   /* DAT_00006fe9c4 */
extern uint64_t sk_g_006fe9d0;   /* DAT_00006fe9d0 */
extern uint64_t sk_g_006fe9e0;   /* DAT_00006fe9e0 */
extern uint64_t sk_g_006fe9e8;   /* DAT_00006fe9e8 */
extern uint64_t sk_g_006fe9f8;   /* DAT_00006fe9f8 */
extern uint64_t sk_g_006fea08;   /* DAT_00006fea08 */
extern uint64_t sk_g_006fea18;   /* DAT_00006fea18 */
extern uint64_t sk_g_006fea28;   /* DAT_00006fea28 */
extern uint64_t sk_g_006fea38;   /* DAT_00006fea38 */
extern uint64_t sk_g_006ff0c8;   /* DAT_00006ff0c8 */
extern uint64_t sk_g_00700170;   /* DAT_0000700170 */

extern uint64_t sk_g_0068a0b0;   /* DAT_000068a0b0 */
extern uint64_t sk_g_0068a3b0;   /* DAT_000068a3b0 */
extern uint64_t sk_g_0068a3c0;   /* DAT_000068a3c0 */
extern uint64_t sk_g_0068a510;   /* DAT_000068a510 */
extern uint64_t sk_g_0068a520;   /* DAT_000068a520 */
extern const char sk_str_00689f40[];   /* string at 0x00689f40 */
extern const char sk_str_00689f60[];   /* string at 0x00689f60 */
extern const char sk_str_00689f80[];   /* string at 0x00689f80 */
extern const char sk_str_00689fa0[];   /* string at 0x00689fa0 */
extern const char sk_str_00689fc0[];   /* string at 0x00689fc0 */
extern const char sk_str_00689fe0[];   /* string at 0x00689fe0 */
extern const char sk_str_0068a000[];   /* string at 0x0068a000 */
extern const char sk_str_0068a020[];   /* string at 0x0068a020 */
extern const char sk_str_0068a040[];   /* string at 0x0068a040 */
extern const char sk_str_0068a060[];   /* string at 0x0068a060 */
extern const char sk_str_0068a0c8[];   /* string at 0x0068a0c8 */
extern const char sk_str_0068a0e8[];   /* string at 0x0068a0e8 */
extern const char sk_str_0068a108[];   /* string at 0x0068a108 */
extern const char sk_str_0068a128[];   /* string at 0x0068a128 */
extern const char sk_str_0068a148[];   /* string at 0x0068a148 */
extern const char sk_str_0068a168[];   /* string at 0x0068a168 */
extern const char sk_str_0068a188[];   /* string at 0x0068a188 */
extern const char sk_str_0068a1a8[];   /* string at 0x0068a1a8 */
extern const char sk_str_0068a1c8[];   /* string at 0x0068a1c8 */
extern const char sk_str_0068a1e8[];   /* string at 0x0068a1e8 */
extern const char sk_str_0068a240[];   /* string at 0x0068a240 */
extern const char sk_str_0068a260[];   /* string at 0x0068a260 */
extern const char sk_str_0068a280[];   /* string at 0x0068a280 */
extern const char sk_str_0068a2a0[];   /* string at 0x0068a2a0 */
extern const char sk_str_0068a2c0[];   /* string at 0x0068a2c0 */
extern const char sk_str_0068a2e0[];   /* string at 0x0068a2e0 */
extern const char sk_str_0068a300[];   /* string at 0x0068a300 */
extern const char sk_str_0068a320[];   /* string at 0x0068a320 */
extern const char sk_str_0068a340[];   /* string at 0x0068a340 */
extern const char sk_str_0068a360[];   /* string at 0x0068a360 */
extern const char sk_str_0068a3c8[];   /* string at 0x0068a3c8 */
extern const char sk_str_0068a3e8[];   /* string at 0x0068a3e8 */
extern const char sk_str_0068a408[];   /* string at 0x0068a408 */
extern const char sk_str_0068a428[];   /* string at 0x0068a428 */
extern const char sk_str_0068a448[];   /* string at 0x0068a448 */
extern const char sk_str_0068a468[];   /* string at 0x0068a468 */
extern const char sk_str_0068a488[];   /* string at 0x0068a488 */
extern const char sk_str_0068a4a8[];   /* string at 0x0068a4a8 */
extern const char sk_str_0068a4c8[];   /* string at 0x0068a4c8 */
extern const char sk_str_0068a4e8[];   /* string at 0x0068a4e8 */
extern const char sk_str_006a9c4f[];   /* string at 0x006a9c4f */
extern const char sk_str_006a9c9a[];   /* string at 0x006a9c9a */
extern const char sk_str_006a9f4f[];   /* string at 0x006a9f4f */
extern const char sk_str_006aa0db[];   /* string at 0x006aa0db */

/* String constants referenced by this slice (Ghidra s_ ground truth). */
/* ===== part 0: fragment of SKR68 ===== */

/* FUN_00663c04 @ 0x00663c04   (est. sk_l4_error_string)
 * Ghidra: void FUN_00663c04(uint64_t param_1,uint8_t param_2)
 * Emits the human-readable L4 error-code name for a given error code into a
 * fixed 0x20-uint8_t message buffer. Codes 0..9 map to the standard L4 error
 * strings ("L4 ErrorCodeSuccess" ... "L4 ErrorCodePermissionInvalid"); any
 * code above 9 falls through to a generic "unknown error" diagnostic string.
 * The formatted result is written via the shared log-write helper (out-of-slice
 * sk_x_0067aa00).
 * Confidence: high
 * Notes: string refs s_L4_ErrorCode* at 0x00689f40..0x0068a060, DAT_0068a080;
 *   thunk_FUN_0067aa00, FUN_0064effc (both out-of-slice). */
void sk_f_00663c04(uint64_t msg_buf, uint8_t err_code)
{
    const char *err_name;

    if (9 < err_code) {
        sk_x_0067aa00(msg_buf, &sk_g_0068a080, 0x20);
        sk_x_0064effc(msg_buf, 0x20);
        return;
    }
    switch (err_code) {
    default:
        err_name = sk_str_00689f40;
        break;
    case 1:
        err_name = sk_str_00689f60;
        break;
    case 2:
        err_name = sk_str_00689f80;
        break;
    case 3:
        err_name = sk_str_00689fa0;
        break;
    case 4:
        err_name = sk_str_00689fc0;
        break;
    case 5:
        err_name = sk_str_00689fe0;
        break;
    case 6:
        err_name = sk_str_0068a000;
        break;
    case 7:
        err_name = sk_str_0068a020;
        break;
    case 8:
        err_name = sk_str_0068a040;
        break;
    case 9:
        err_name = sk_str_0068a060;
    }
    sk_x_0067aa00(msg_buf, err_name, 0x20);
    return;
}

/* FUN_00663d3c @ 0x00663d3c   (est. sk_scratchpad_drain_reply)
 * Ghidra: void FUN_00663d3c(long param_1,unsigned long param_2)
 * Drains `param_2` reply slots from a per-object scratch/queue structure at
 * `param_1`, releasing each queued entry (via sk_x_00685234) and the messages
 * referenced in its local/extended message regions (offsets +0xc0..0xe0 and
 * +0xe0..0x100 with per-entry 8-uint8_t stride starting at +0x1c0/+0x1e0),
 * then zeroing those message-region words. After draining, re-reads the
 * current queue count (sk_x_00661318/sk_x_00684d1c); if the head ran dry it
 * parks the object by registering its wait queue and issues a supervisor call
 * to block until a reply arrives. On completion it checks a saved debug
 * sentinel (sk_g_006b5ed0) and, if changed, unwinds through sk_x_0067f660.
 * Faithful transcription of a large blocking-reply-drain loop.
 * Confidence: medium
 * Notes: DAT_006b5ed0 sentinel, tpidrro_el0 mailbox store/restore around
 *   CallSupervisor(0); SoftwareBreakpoint(0x5519,0x6642a0) bounds checks;
 *   FUN_0065c2f0 no-return abort (0x6a7de6); FUN_0065fdb8 queue push,
 *   FUN_00662628 wake, FUN_00662098 tpidrro load; many out-of-slice callees. */
void sk_f_00663d3c(int64_t obj, uint64_t count)
{
    sk_u128_t reply;
    uint64_t queue_count;
    uint64_t sentinel_saved;
    int64_t slot;
    int64_t base;
    uint8_t reply_buf[32];

    reply.lo = obj;
    reply.hi = count;
    queue_count = *(uint64_t *)(obj + 0x30);
    sentinel_saved = sk_g_006b5ed0;
    while (count < queue_count) {
        base = *(uint64_t *)(obj + 0x18);
        *(uint64_t *)(obj + 0x18) = *(uint64_t *)(base + 0x50);
        *(uint64_t *)(obj + 0x30) = queue_count - 1;
        *(uint64_t *)(base + 0x50) = 0;
        if ((uint64_t)(base + 0x178) < (uint64_t)base) goto bounds_fault;
        sk_x_00685234(base);
        slot = sk_x_006621f4(base);
        if (*(int64_t *)(obj + 0x38) != 0) {
            int64_t i = 0;
            uint64_t n = 0;
            do {
                uint64_t *msg_ptr = (uint64_t *)(base + i + 0xc0);
                uint64_t *msg_end = (uint64_t *)(base + i + 200);
                if ((uint64_t)msg_ptr < (uint64_t)(base + 0xc0) ||
                    (uint64_t)(base + 0xe0) < (uint64_t)msg_end ||
                    (uint64_t)msg_end < (uint64_t)msg_ptr) goto bounds_fault;
                sk_x_006860f4(*msg_ptr);
                int64_t w = slot + i;
                uint8_t *wp = (uint8_t *)(w + 0x1c0);
                if ((uint64_t)wp < (uint64_t)(slot + 0x1c0) ||
                    (uint64_t)(slot + 0x1e0) < (uint64_t)(w + 0x1c8) ||
                    (uint64_t)(w + 0x1c8) < (uint64_t)wp) goto bounds_fault;
                *(uint8_t *)(w + 0x1c5) = 0;
                *(uint8_t *)(w + 0x1c3) = 0;
                *(uint8_t *)(w + 0x1c2) = 0;
                *(uint8_t *)(w + 0x1c1) = 0;
                *wp = 0;
                *(uint8_t *)(w + 0x1c4) = 0;
                *(uint8_t *)(w + 0x1c7) = 0;
                *(uint8_t *)(w + 0x1c6) = 0;
                n = n + 1;
                i = i + 8;
            } while (n < *(uint64_t *)(obj + 0x38));
        }
        if (*(int64_t *)(obj + 0x40) != 0) {
            int64_t i = 0;
            uint64_t n = 0;
            do {
                uint64_t *msg_ptr = (uint64_t *)(base + i + 0xe0);
                uint64_t *msg_end = (uint64_t *)(base + i + 0xe8);
                if ((uint64_t)msg_ptr < (uint64_t)(base + 0xe0) ||
                    (uint64_t)(base + 0x100) < (uint64_t)msg_end ||
                    (uint64_t)msg_end < (uint64_t)msg_ptr) goto bounds_fault;
                sk_x_006860f4(*msg_ptr);
                int64_t w = slot + i;
                uint8_t *wp = (uint8_t *)(w + 0x1e0);
                if ((uint64_t)wp < (uint64_t)(slot + 0x1e0) ||
                    (uint64_t)(slot + 0x200) < (uint64_t)(w + 0x1e8) ||
                    (uint64_t)(w + 0x1e8) < (uint64_t)wp) goto bounds_fault;
                *(uint8_t *)(w + 0x1e5) = 0;
                *(uint8_t *)(w + 0x1e3) = 0;
                *(uint8_t *)(w + 0x1e2) = 0;
                *(uint8_t *)(w + 0x1e1) = 0;
                *wp = 0;
                *(uint8_t *)(w + 0x1e4) = 0;
                *(uint8_t *)(w + 0x1e7) = 0;
                *(uint8_t *)(w + 0x1e6) = 0;
                n = n + 1;
                i = i + 8;
            } while (n < *(uint64_t *)(obj + 0x40));
        }
        uint64_t cur = sk_x_00661318();
        if (base == (int64_t)cur) {
            reply = (sk_u128_t)sk_x_00660ab4(base);
        } else {
            reply = (sk_u128_t)sk_x_00684d1c(base);
        }
        queue_count = *(uint64_t *)(obj + 0x30);
    }
    if (queue_count < count) {
        int64_t *head = (int64_t *)(obj + 0x18);
        int64_t *limit = (int64_t *)(obj + 0x20);
        do {
            if ((uint64_t)limit < (uint64_t)(head + 1) ||
                (uint64_t)(head + 1) < (uint64_t)head) goto bounds_fault;
            sk_x_0065fdb8(head, 0, obj, 0, 0);
            if (*head == 0) {
                sk_x_0065c2f0(0, 0x6a7de6);
            }
            uint32_t val = (uint32_t)*(uint16_t *)(obj + 0x30) +
                           ((*(uint16_t *)(obj + 0x30) >> 3) / 0x7d) * -1000;
            uint32_t digits = 0x48;
            uint32_t divisor = 1000;
            bool more;
            do {
                uint32_t q = divisor / 10;
                uint32_t d = 0;
                if (q != 0) {
                    d = (val & 0xffff) / q;
                }
                digits = d + 0x30 & 0xffff | digits << 8;
                val = val - d * q;
                more = 0x13 < divisor;
                divisor = q;
            } while (more);
            sk_x_00662628(*head, digits);
            *(int64_t *)(*head + 0xa8) = obj;
            slot = sk_x_006621f4();
            if (*(int64_t *)(obj + 0x38) != 0) {
                uint64_t n = 0;
                int64_t off = 0x1c0;
                do {
                    uint64_t v = sk_x_0066ad54();
                    uint8_t *wp = (uint8_t *)(slot + off);
                    if ((uint64_t)wp < (uint64_t)(slot + 0x1c0U) ||
                        (uint64_t)(slot + 0x1e0U) < (uint64_t)(wp + 8) ||
                        (uint64_t)(wp + 8) < (uint64_t)wp) goto bounds_fault;
                    *wp = (uint8_t)v;
                    wp[5] = (uint8_t)(v >> 0x28);
                    wp[3] = (uint8_t)(v >> 0x18);
                    wp[2] = (uint8_t)(v >> 0x10);
                    wp[1] = (uint8_t)(v >> 8);
                    wp[4] = (uint8_t)(v >> 0x20);
                    wp[7] = (uint8_t)(v >> 0x38);
                    wp[6] = (uint8_t)(v >> 0x30);
                    int64_t tgt = *head;
                    uint64_t *mp = (uint64_t *)(tgt + off + -0x100);
                    if ((uint64_t)mp < (uint64_t)(tgt + 0xc0U) ||
                        (uint64_t *)(tgt + off + -0xf8) < mp ||
                        (uint64_t)(tgt + 0xe0U) < (uint64_t)(tgt + off + -0xf8))
                        goto bounds_fault;
                    *mp = v;
                    n = n + 1;
                    off = off + 8;
                } while (n < *(uint64_t *)(obj + 0x38));
            }
            int64_t tgt;
            if (*(int64_t *)(obj + 0x40) == 0) {
                tgt = *head;
            } else {
                uint64_t n = 0;
                int64_t off = 0x1e0;
                do {
                    uint64_t v = sk_x_0066ad54();
                    uint8_t *wp = (uint8_t *)(slot + off);
                    if ((uint64_t)wp < (uint64_t)(slot + 0x1e0U) ||
                        (uint64_t)(slot + 0x200U) < (uint64_t)(wp + 8) ||
                        (uint64_t)(wp + 8) < (uint64_t)wp) goto bounds_fault;
                    *wp = (uint8_t)v;
                    wp[5] = (uint8_t)(v >> 0x28);
                    wp[3] = (uint8_t)(v >> 0x18);
                    wp[2] = (uint8_t)(v >> 0x10);
                    wp[1] = (uint8_t)(v >> 8);
                    wp[4] = (uint8_t)(v >> 0x20);
                    wp[7] = (uint8_t)(v >> 0x38);
                    wp[6] = (uint8_t)(v >> 0x30);
                    tgt = *head;
                    uint64_t *mp = (uint64_t *)(tgt + off + -0x100);
                    if ((uint64_t)mp < (uint64_t)(tgt + 0xe0U) ||
                        (uint64_t *)(tgt + off + -0xf8) < mp ||
                        (uint64_t)(tgt + 0x100U) < (uint64_t)(tgt + off + -0xf8))
                        goto bounds_fault;
                    *mp = v;
                    n = n + 1;
                    off = off + 8;
                } while (n < *(uint64_t *)(obj + 0x40));
            }
            queue_count = *(uint64_t *)(tgt + 0x28);
            uint64_t flags = *(uint64_t *)(obj + 0x10);
            uint8_t b0 = (uint8_t)flags & 0xfd;
            uint64_t tpidr = sk_x_00662098(tgt);
            uint8_t *mb = (uint8_t *)tpidrro_el0;
            uint8_t b1 = (uint8_t)(flags >> 8);
            mb[1] = b1;
            *mb = b0;
            uint8_t b4 = (uint8_t)(flags >> 0x20);
            mb[4] = b4;
            uint8_t b5 = (uint8_t)(flags >> 0x28);
            mb[5] = b5;
            uint8_t b2 = (uint8_t)(flags >> 0x10);
            mb[2] = b2;
            uint8_t b3 = (uint8_t)(flags >> 0x18);
            mb[3] = b3;
            uint8_t b6 = (uint8_t)(flags >> 0x30);
            mb[6] = b6;
            uint8_t b7 = (uint8_t)(flags >> 0x38);
            mb[7] = b7;
            mb[0xd] = (uint8_t)(tpidr >> 0x28);
            mb[8] = (uint8_t)tpidr;
            mb[0xb] = (uint8_t)(tpidr >> 0x18);
            mb[10] = (uint8_t)(tpidr >> 0x10);
            mb[9] = (uint8_t)(tpidr >> 8);
            mb[0xc] = (uint8_t)(tpidr >> 0x20);
            mb[0xf] = (uint8_t)(tpidr >> 0x38);
            mb[0xe] = (uint8_t)(tpidr >> 0x30);
            reply.hi = 0xf;
            reply.lo = queue_count;
            CallSupervisor(0);
            *mb = b0;
            mb[7] = b7;
            mb[6] = b6;
            mb[5] = b5;
            mb[4] = b4;
            mb[3] = b3;
            mb[2] = b2;
            mb[1] = b1;
            if ((queue_count & 0xff) != 0) {
                reply.lo = (uint64_t)sk_x_006853e4(queue_count, reply_buf);
                goto unwind_check;
            }
            slot = *head;
            head = (int64_t *)(slot + 0x50);
            limit = (int64_t *)(slot + 0x58);
            queue_count = *(int64_t *)(obj + 0x30) + 1;
            *(uint64_t *)(obj + 0x30) = queue_count;
        } while (queue_count < count);
    }
    if (sk_g_006b5ed0 == sentinel_saved) {
        return;
    }
unwind_check:
    sk_x_0067f660(reply.lo, reply.hi);
    return;

bounds_fault:
    {
        /* WARNING: Does not return */
        SoftwareBreakpoint(0x5519, 0x6642a0);;
    }
}

/* FUN_006642bc @ 0x006642bc   (est. sk_scratch_record_result)
 * Ghidra: void FUN_006642bc(uint64_t *param_1,unsigned long param_2,uint64_t param_3,uint64_t *param_4)
 * Records a completed reply/result into a scratch object: first re-arms the
 * object's notification (sk_x_00663928 with a flag bit `param_2|2`), then
 * copies a 24-uint8_t result payload (three 8-uint8_t words from `param_4`) into the
 * object's message region at offsets +0x50/+0x58/+0x60. `param_3` is unused.
 * Bounds-checks the destination pointer before writing.
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519,0x664304) on overflow; FUN_00663928
 *   out-of-slice; param_3 unreferenced by decompile. */
void sk_f_006642bc(uint64_t *obj, uint64_t flags, uint64_t unused, uint64_t *result)
{
    if ((uint64_t)obj <= (uint64_t)(obj + 10)) {
        sk_x_00663928(obj, flags | 2);
        obj[0xb] = result[1];
        obj[0xc] = result[2];
        obj[10] = result[0];
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x664304);;
}

/* FUN_00664304 @ 0x00664304   (est. sk_scratch_peek_reply)
 * Ghidra: uint64_t FUN_00664304(long param_1,long param_2)
 * Returns the 8-uint8_t reply word stored at index `param_2` in the scratch
 * object's reply array (base +0xc0, 8-uint8_t stride). The index is bounds-checked
 * against the +0xe0 limit; a violation traps via SoftwareBreakpoint.
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519,0x664330) on out-of-range index. */
uint64_t sk_f_00664304(int64_t obj, int64_t index)
{
    uint64_t *reply = (uint64_t *)(obj + 0xc0U) + index;
    if (((uint64_t)(obj + 0xc0U) <= (uint64_t)reply &&
         (uint64_t)(reply + 1) <= (uint64_t)(obj + 0xe0U)) &&
        (uint64_t)reply <= (uint64_t)(reply + 1)) {
        return *reply;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x664330);;
}

/* FUN_00664330 @ 0x00664330   (est. sk_scratch_claim_owner)
 * Ghidra: void FUN_00664330(uint64_t param_1)
 * Claims ownership of a scratch object on behalf of a new owner `param_1`.
 * Reads the current owner (sk_x_00661318) and the number of held busy slots
 * (bits 6..8 of the +0xb8 owner field); for each busy slot it spins on
 * CallSupervisor(4) until the slot's busy flag (at +0xc0, 8-uint8_t stride) drops
 * to a value other than 1. It then stores the new owner at +0xb0 and clears the
 * owner/busy word at +0xb8.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x6643b8) bounds fault; CallSupervisor(4)
 *   busy-wait; FUN_00661318 out-of-slice (current CPU/object owner). */
void sk_f_00664330(uint64_t new_owner)
{
    int64_t cur = (int64_t)sk_x_00661318();
    uint64_t busy = *(uint64_t *)(cur + 0xb8) >> 6 & 7;
    if (busy != 0) {
        uint64_t i = 0;
        do {
            int64_t *slot = (int64_t *)(cur + 0xc0U) + i;
            if ((uint64_t)slot < (uint64_t)(cur + 0xc0U) ||
                (uint64_t)(cur + 0xe0U) < (uint64_t)(slot + 1) ||
                (uint64_t)(slot + 1) < (uint64_t)slot) {
                /* WARNING: Does not return */
                SoftwareBreakpoint(0x5519, 0x6643b8);;
            }
            do {
                CallSupervisor(4);
            } while (*slot == 1);
            i = i + 1;
        } while (i != busy);
    }
    *(uint64_t *)(cur + 0xb0) = new_owner;
    *(uint64_t *)(cur + 0xb8) = 0;
    return;
}

/* FUN_006643b8 @ 0x006643b8   (est. sk_scratch_publish_owner)
 * Ghidra: void FUN_006643b8(uint64_t param_1)
 * Publishes a scratch object's reply/state into the per-CPU mailbox so a new
 * owner (sk_x_00661318) can take over. For each of the 4 reply slots it copies
 * the busy-slot word (at +0xe0) and the reply word (at +0xc0) into the
 * per-CPU region at +0x1e0/+0x1c0 (8-uint8_t little-endian stores), spinning on
 * CallSupervisor(4) for slots still marked busy by the current owner (bits 6..8
 * of +0xb0). Finally it clears the object owner (+0xb0) and stores the new
 * owner at +0xb8.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x66453c) bounds fault; tpidrro_el0 per-CPU
 *   base; FUN_0065c218/FUN_006626f8 out-of-slice teardown. */
void sk_f_006643b8(uint64_t new_owner)
{
    int64_t cur = (int64_t)sk_x_00661318();
    uint64_t i = 0;
    uint64_t owner = *(uint64_t *)(cur + 0xb0);
    do {
        uint64_t *slot = (uint64_t *)(cur + 0xe0) + i;
        if ((uint64_t)(cur + 0x100) < (uint64_t)(slot + 1) ||
            (uint64_t)(slot + 1) < (uint64_t)slot) goto bounds_fault;
        int64_t busy_val = (int64_t)*slot;
        if (i < (owner >> 6 & 7)) {
            do {
                CallSupervisor(4);
            } while (busy_val == 1);
        }
        int64_t cpu_base = (int64_t)tpidrro_el0;
        uint8_t *w = (uint8_t *)(cpu_base + 0x1e0U) + i * 8;
        if ((uint64_t)(cpu_base + 0x200U) < (uint64_t)(w + 8) ||
            (uint64_t)(w + 8) < (uint64_t)w) goto bounds_fault;
        *w = (uint8_t)busy_val;
        w[5] = (uint8_t)((uint64_t)busy_val >> 0x28);
        w[3] = (uint8_t)((uint64_t)busy_val >> 0x18);
        w[2] = (uint8_t)((uint64_t)busy_val >> 0x10);
        w[1] = (uint8_t)((uint64_t)busy_val >> 8);
        w[4] = (uint8_t)((uint64_t)busy_val >> 0x20);
        w[7] = (uint8_t)((uint64_t)busy_val >> 0x38);
        w[6] = (uint8_t)((uint64_t)busy_val >> 0x30);
        uint64_t *rp = (uint64_t *)(cur + 0xc0 + i * 8);
        if ((uint64_t)(cur + 0xe0) < (uint64_t)(rp + 1) ||
            (uint64_t)(rp + 1) < (uint64_t)rp) goto bounds_fault;
        int64_t wbase = cpu_base + i * 8;
        if ((uint64_t)(cpu_base + 0x1e0U) < (uint64_t)(wbase + 0x1c8U) ||
            (uint64_t)(wbase + 0x1c8U) < (uint64_t)(wbase + 0x1c0U)) goto bounds_fault;
        uint64_t rv = *rp;
        *(uint8_t *)(wbase + 0x1c0U) = (uint8_t)rv;
        *(uint8_t *)(wbase + 0x1c5) = (uint8_t)(rv >> 0x28);
        *(uint8_t *)(wbase + 0x1c3) = (uint8_t)(rv >> 0x18);
        *(uint8_t *)(wbase + 0x1c2) = (uint8_t)(rv >> 0x10);
        *(uint8_t *)(wbase + 0x1c1) = (uint8_t)(rv >> 8);
        *(uint8_t *)(wbase + 0x1c4) = (uint8_t)(rv >> 0x20);
        *(uint8_t *)(wbase + 0x1c7) = (uint8_t)(rv >> 0x38);
        *(uint8_t *)(wbase + 0x1c6) = (uint8_t)(rv >> 0x30);
        i = i + 1;
    } while (i != 4);
    if ((uint64_t)cur <= (uint64_t)(cur + 0x178)) {
        sk_x_0065c218(cur);
        sk_x_006626f8(cur, 0);
        *(uint64_t *)(cur + 0xb0) = 0;
        *(uint64_t *)(cur + 0xb8) = new_owner;
        return;
    }
bounds_fault:
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x66453c);;
}

/* FUN_0066453c @ 0x0066453c   (est. sk_scratch_report_error)
 * Ghidra: void FUN_0066453c(void)
 * Thin wrapper: formats the current error code string into a stack scratch
 * buffer via sk_f_00663c04. Ghidra decoded only a single argument (the buffer
 * address); the error-code argument is an undecoded register, so 0 is passed
 * here as a placeholder.
 * Confidence: low
 * Notes: only one argument visible in decompile (&stack); second param
 *   (error code) is register-only and not decoded. */
void sk_f_0066453c(void)
{
    uint64_t scratch;
    sk_f_00663c04(&scratch, 0);
    return;
}

/* FUN_0066455c @ 0x0066455c   (est. sk_obj_get_link)
 * Ghidra: uint64_t FUN_0066455c(unsigned long param_1)
 * Returns the 8-uint8_t link/forward pointer at offset +0x58 of an object, but
 * only when the object is valid (non-null) and its flag bit 1 (bit 1 of the
 * word at +0x10) is set; otherwise returns 0. Bounds-checks +0x70 before the
 * read.
 * Confidence: high
 * Notes: SoftwareBreakpoint(0x5519,0x664588) bounds fault; flag test
 *   (*(obj+0x10)>>1)&1. */
uint64_t sk_f_0066455c(uint64_t obj)
{
    uint64_t link = 0;
    if ((obj != 0) && (((*(uint64_t *)(obj + 0x10) >> 1) & 1) != 0)) {
        if ((uint64_t)(obj + 0x70) < obj) {
            /* WARNING: Does not return */
            SoftwareBreakpoint(0x5519, 0x664588);;
        }
        link = *(uint64_t *)(obj + 0x58);
    }
    return link;
}

/* FUN_00664588 @ 0x00664588   (est. sk_obj_check_link)
 * Ghidra: void FUN_00664588(unsigned long param_1)
 * Validates an object's link range: sign-extends flag bit 1 (bit 1 of the word
 * at +0x10) to a mask, applies it to both the object base and its +0x70 limit,
 * and traps if a non-zero masked base overflows past +0x70. Used as a bounds
 * pre-check before following a link.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x6645bc) bounds fault; mask computed by
 *   (*(obj+0x10)<<0x3e)>>0x3f. */
void sk_f_00664588(uint64_t obj)
{
    uint64_t mask = ((*(int64_t *)(obj + 0x10) << 0x3e) >> 0x3f);
    uint64_t base = obj & mask;
    if ((base != 0) &&
        ((uint64_t)(obj + 0x70 & mask) < (uint64_t)(base + 0x70) ||
         (uint64_t)(base + 0x70) < base)) {
        /* WARNING: Does not return */
        SoftwareBreakpoint(0x5519, 0x6645bc);;
    }
    return;
}

/* FUN_006645bc @ 0x006645bc   (est. sk_obj_get_code)
 * Ghidra: uint32_t FUN_006645bc(unsigned long param_1)
 * Returns the 32-bit code/status word at offset +0x60 of an object when the
 * object is valid and its flag bit 1 (bit 1 of the uint8_t at +0x10) is set;
 * otherwise returns the default sentinel 0x4e4f4550. Bounds-checks +0x70.
 * Confidence: high
 * Notes: default 0x4e4f4550 (little-endian bytes 'PEON'); SoftwareBreakpoint
 *   (0x5519,0x6645ec) bounds fault; flag test on *(uint8_t*)(obj+0x10)>>1&1. */
uint32_t sk_f_006645bc(uint64_t obj)
{
    uint32_t code = 0x4e4f4550;
    if ((obj != 0) && (((*(uint8_t *)(obj + 0x10) >> 1) & 1) != 0)) {
        if ((uint64_t)(obj + 0x70) < obj) {
            /* WARNING: Does not return */
            SoftwareBreakpoint(0x5519, 0x6645ec);;
        }
        code = *(uint32_t *)(obj + 0x60);
    }
    return code;
}

/* FUN_006645ec @ 0x006645ec   (est. sk_mailbox_swap)
 * Ghidra: void FUN_006645ec(uint64_t param_1,uint64_t *param_2)
 * Swaps an 8-uint8_t value through the per-CPU supervisor mailbox: reads the value
 * at `param_2`, stores it uint8_t-by-uint8_t into the tpidrro_el0 mailbox, issues
 * CallSupervisor(0) (which may overwrite the mailbox), then restores the same
 * value into the mailbox and writes it back to `param_2`. `param_1` is unused.
 * Confidence: medium
 * Notes: tpidrro_el0 per-CPU mailbox; CallSupervisor(0); param_1 unreferenced. */
void sk_f_006645ec(uint64_t unused, uint64_t *slot)
{
    uint64_t value = *slot;
    uint8_t *mb = (uint8_t *)tpidrro_el0;
    mb[0] = (uint8_t)value;
    mb[4] = (uint8_t)(value >> 0x20);
    mb[1] = (uint8_t)(value >> 8);
    mb[2] = (uint8_t)(value >> 0x10);
    mb[5] = (uint8_t)(value >> 0x28);
    mb[6] = (uint8_t)(value >> 0x30);
    mb[3] = (uint8_t)(value >> 0x18);
    mb[7] = (uint8_t)(value >> 0x38);
    CallSupervisor(0);
    mb[0] = (uint8_t)value;
    mb[7] = (uint8_t)(value >> 0x38);
    mb[6] = (uint8_t)(value >> 0x30);
    mb[5] = (uint8_t)(value >> 0x28);
    mb[4] = (uint8_t)(value >> 0x20);
    mb[3] = (uint8_t)(value >> 0x18);
    mb[2] = (uint8_t)(value >> 0x10);
    mb[1] = (uint8_t)(value >> 8);
    *slot = value;
    return;
}

/* FUN_0066469c @ 0x0066469c   (est. sk_percpu_get_or_init)
 * Ghidra: void FUN_0066469c(void)
 * Returns (via the cached global sk_g_006fe7e8) the per-CPU object pointer:
 * on first call it fetches the base from sk_x_0065ccc8() and reads its +0x50
 * field, bounds-checking +0x2f0, then caches it in the global. Subsequent
 * calls just return the cached value.
 * Confidence: medium
 * Notes: DAT_006fe7e8 cached global; SoftwareBreakpoint(0x5519,0x6646e0)
 *   bounds fault; FUN_0065ccc8 out-of-slice. */
void sk_f_0066469c(void)
{
    uint64_t value = sk_g_006fe7e8;
    if (sk_g_006fe7e8 == 0) {
        int64_t base = (int64_t)sk_x_0065ccc8();
        value = *(uint64_t *)(base + 0x50);
        if ((uint64_t)(value + 0x2f0) < value) {
            /* WARNING: Does not return */
            SoftwareBreakpoint(0x5519, 0x6646e0);;
        }
    }
    sk_g_006fe7e8 = value;
    return;
}
/* ===== part 1: fragment of SKR68 ===== */

/* FUN_006646e0 @ 0x006646e0   (est. pool_base_init)
 * Ghidra: void FUN_006646e0(void)
 * Writes the constant 0x6b53d8 into the shared pool-base global
 * sk_g_006fe7e8. Serves as an initializer for the slot-pool pointer.
 * Confidence: medium
 * Notes: writes _DAT_006fe7e8; Ghidra warning re overlapping '_' globals. */
void sk_f_006646e0(void)
{
    sk_g_006fe7e8 = 0x6b53d8;
}

/* FUN_006646f4 @ 0x006646f4   (est. pool_slot_alloc)
 * Ghidra: unsigned long FUN_006646f4(uint64_t param_1,uint64_t param_2,uint64_t param_3)
 * Allocates the next free slot index (0..0x1f) from the global slot pool,
 * initializing the pool pointer from the TLS block if it is not yet set.
 * The chosen slot is filled via sk_f_006647d0 and committed with
 * sk_f_006648a8. Returns the allocated slot index. A non-null TLS
 * (+0xf8) force  sk_x_0068543c/00685458 then a breakpoint trap.
 * Confidence: medium
 * Notes: reads/writes _DAT_006fe7e8; calls FUN_0065ccc8, FUN_0065db84,
 * FUN_0065cedc, FUN_0068543c, FUN_00685458; SoftwareBreakpoint(0x5519,0x66479c). */
uint64_t sk_f_006646f4(uint64_t slot_value, uint64_t slot_meta, uint64_t register_flag)
{
    uint64_t slot;
    uint64_t *pool;
    int64_t tls = tpidr_el0;

    if (*(int64_t *)(tls + 0xf8) == 0) {
        pool = (uint64_t *)sk_g_006fe7e8;
        if (sk_g_006fe7e8 == 0) {
            tls = sk_x_0065ccc8();
            pool = *(uint64_t **)(tls + 0x50);
            if ((uint64_t)pool + 0x5e < (uint64_t)pool) {
                goto breakpoint;   /* pool base overflow */
            }
        }
        sk_g_006fe7e8 = (uint64_t)pool;
        pool = (uint64_t *)sk_g_006fe7e8;
        sk_f_0066479c();
        slot = *pool;
        if (slot < 0x20) {
            *pool = slot + 1;
            sk_f_006647d0(slot, slot_value, slot_meta, register_flag);
            sk_f_006648a8();
            return slot;
        }
        sk_x_00685458();
    } else {
        sk_x_0068543c();
        sk_x_00685458();
    }
breakpoint:
    SoftwareBreakpoint(0x5519, 0x66479c);
    /* unreachable */
}

/* FUN_0066479c @ 0x0066479c   (est. pool_region_check)
 * Ghidra: void FUN_0066479c(void)
 * Fetches a TLS/cpu context via sk_x_0065ccc8 and validates that the
 * slot-pool window [base+0x60, base+0x70] is in bounds; when valid it
 * defers to sk_x_0065db84, otherwise it traps.
 * Confidence: medium
 * Notes: calls FUN_0065ccc8, FUN_0065db84; SoftwareBreakpoint(0x5519,0x6647d0). */
void sk_f_0066479c(void)
{
    int64_t base = sk_x_0065ccc8();

    if ((uint64_t)base + 0x60 <= (uint64_t)base + 0x70) {
        sk_x_0065db84();
        return;
    }
    SoftwareBreakpoint(0x5519, 0x6647d0);
}

/* FUN_006647d0 @ 0x006647d0   (est. pool_slot_fill)
 * Ghidra: void FUN_006647d0(long param_1,long param_2,uint64_t param_3,int param_4)
 * Stores the allocated slot entry: writes param_2 into the slot index
 * (param_1) within the pool and param_3 into the adjacent descriptor slot,
 * after bounds-checking both regions of the pool. When both param_2 and
 * param_4 are non-zero it registers the slot via sk_x_0065cedc with a
 * callback of sk_f_00664a8c and the slot index.
 * Confidence: medium
 * Notes: reads/writes _DAT_006fe7e8; calls FUN_0065ccc8, FUN_0065cedc,
 * FUN_00664a8c; SoftwareBreakpoint(0x5519,0x6648a8); local_48 holds param_1. */
void sk_f_006647d0(int64_t slot_idx, int64_t slot_value, uint64_t slot_meta, int register_flag)
{
    uint64_t *pool;
    uint64_t *lo;
    uint64_t *slot;
    int64_t idx_copy = slot_idx;

    pool = (uint64_t *)sk_g_006fe7e8;
    if (sk_g_006fe7e8 == 0) {
        int64_t tls = sk_x_0065ccc8();
        pool = *(uint64_t **)(tls + 0x50);
        if ((uint64_t)pool + 0x2f0 < (uint64_t)pool) {
            goto breakpoint;   /* pool base overflow */
        }
    }
    sk_g_006fe7e8 = (uint64_t)pool;
    pool = (uint64_t *)sk_g_006fe7e8;
    lo = (uint64_t *)(sk_g_006fe7e8 + 0x100);
    slot = (uint64_t *)(sk_g_006fe7e8 + (uint64_t)slot_idx * 8);
    if (((uint64_t *)(sk_g_006fe7e8 + 8) <= slot && slot + 1 <= lo) && slot <= slot + 1) {
        *(int64_t *)(sk_g_006fe7e8 + (uint64_t)slot_idx * 8) = slot_value;
        slot = lo + slot_idx;
        uint64_t *prev = slot - 1;
        if ((lo <= prev && slot <= (uint64_t *)(sk_g_006fe7e8 + 0x1f8)) && prev <= slot) {
            *prev = slot_meta;
            if (slot_value != 0 && register_flag != 0) {
                sk_x_0065cedc(sk_f_00664a8c, &idx_copy);
            }
            return;
        }
    }
breakpoint:
    SoftwareBreakpoint(0x5519, 0x6648a8);
}

/* FUN_006648a8 @ 0x006648a8   (est. pool_commit)
 * Ghidra: void FUN_006648a8(void)
 * Fetches a TLS/cpu context via sk_x_0065ccc8 and validates that the
 * slot-pool window [base+0x60, base+0x70] is in bounds; when valid it
 * defers to sk_x_0065de3c to commit the pool, otherwise it traps.
 * Confidence: medium
 * Notes: calls FUN_0065ccc8, FUN_0065de3c; SoftwareBreakpoint(0x5519,0x6648dc). */
void sk_f_006648a8(void)
{
    int64_t base = sk_x_0065ccc8();

    if ((uint64_t)base + 0x60 <= (uint64_t)base + 0x70) {
        sk_x_0065de3c();
        return;
    }
    SoftwareBreakpoint(0x5519, 0x6648dc);
}

/* FUN_006648dc @ 0x006648dc   (est. pool_sweep_entries)
 * Ghidra: void FUN_006648dc(long param_1)
 * Sweeps 0x1c per-slot hook/counter entries: for each entry whose optional
 * hook pointer (pool+0x20) is non-null it invokes the hook to (re)derive the
 * value stored into the destination array (param_1+0x18..), otherwise the
 * existing value is used. Each entry's activity counter at pool+0x210 is
 * incremented and an overflow (previous == -1) faults via sk_x_0065c2f0.
 * Completes by committing the pool with sk_f_006648a8.
 * Confidence: medium
 * Notes: reads/writes _DAT_006fe7e8; calls FUN_0065ccc8, FUN_0066479c,
 * FUN_0065c2f0, FUN_006648a8; SoftwareBreakpoint(0x5519,0x6649a4). */
void sk_f_006648dc(int64_t dest)
{
    uint64_t *pool;
    uint64_t *hi;
    uint64_t *cur;
    int64_t (*hook)(void);
    int64_t counter;
    int64_t *entry;
    int count = 0x1c;

    pool = (uint64_t *)sk_g_006fe7e8;
    if (sk_g_006fe7e8 == 0) {
        int64_t tls = sk_x_0065ccc8();
        pool = *(uint64_t **)(tls + 0x50);
        if ((uint64_t)pool + 0x2f0 < (uint64_t)pool) {
            goto breakpoint;   /* pool base overflow */
        }
    }
    sk_g_006fe7e8 = (uint64_t)pool;
    pool = (uint64_t *)sk_g_006fe7e8;
    sk_f_0066479c();
    hi = (uint64_t *)((uint64_t)pool + 0x100);
    entry = (int64_t *)(dest + 0x18);
    cur = pool;
    while ((uint64_t *)((uint64_t)cur + 0x28) <= hi &&
           (uint64_t *)((uint64_t)cur + 0x20) <= (uint64_t *)((uint64_t)cur + 0x28)) {
        hook = (int64_t (*)(void))*(uint64_t *)((uint64_t)cur + 0x20);
        if (hook == 0) {
            counter = *entry;
        } else {
            counter = hook();
            *entry = counter;
        }
        if (counter != 0) {
            counter = *(int64_t *)((uint64_t)cur + 0x210);
            *(int64_t *)((uint64_t)cur + 0x210) = counter + 1;
            if (counter == -1) {
                sk_x_0065c2f0(0, 0x6a7f0f);   /* noreturn counter-overflow fault */
            }
        }
        entry = entry + 1;
        cur = cur + 1;
        count = count - 1;
        if (count == 0) {
            sk_f_006648a8();
            return;
        }
    }
breakpoint:
    SoftwareBreakpoint(0x5519, 0x6649a4);
}

/* FUN_006649b4 @ 0x006649b4   (est. pool_teardown_entries)
 * Ghidra: void FUN_006649b4(void)
 * Walks the 0x1c TLS entry slots (tls+0x18..) while holding a re-entrancy
 * guard at tls+0xf8; for each non-zero entry it validates the corresponding
 * pool descriptor (pool+0x118/+0x120), runs its optional teardown hook with
 * the entry value, clears the slot, decrements the pool counter at +0x210,
 * and commits via sk_f_006648a8. Clears the guard and returns at the end.
 * Confidence: medium
 * Notes: reads/writes _DAT_006fe7e8 and tpidr_el0 fields; calls FUN_0065ccc8,
 * FUN_0066479c, FUN_006648a8; SoftwareBreakpoint(0x5519,0x664a84). */
void sk_f_006649b4(void)
{
    uint64_t *pool;
    uint64_t *addr;
    uint64_t *fnslot;
    void (*hook)(uint64_t);
    int64_t tls = tpidr_el0;
    int64_t off;

    pool = (uint64_t *)sk_g_006fe7e8;
    if (sk_g_006fe7e8 == 0) {
        int64_t ctx = sk_x_0065ccc8();
        pool = *(uint64_t **)(ctx + 0x50);
        if ((uint64_t)pool + 0x2f0 < (uint64_t)pool) {
            goto breakpoint;   /* pool base overflow */
        }
    }
    sk_g_006fe7e8 = (uint64_t)pool;
    pool = (uint64_t *)sk_g_006fe7e8;
    off = 0;
    *(int64_t *)(tls + 0xf8) = 1;
    do {
        if (*(int64_t *)(tls + 0x18 + off) != 0) {
            sk_f_0066479c();
            addr = (uint64_t *)((uint64_t)pool + off + 0x120);
            fnslot = (uint64_t *)((uint64_t)pool + off + 0x118);
            if ((uint64_t *)((uint64_t)pool + 0x1f8) < addr || addr < fnslot) {
                goto breakpoint;
            }
            hook = (void (*)(uint64_t))*fnslot;
            if (hook != 0) {
                hook(*(int64_t *)(tls + 0x18 + off));
            }
            *(int64_t *)(tls + 0x18 + off) = 0;
            int64_t cnt = *(int64_t *)((uint64_t)pool + off + 0x210);
            *(int64_t *)((uint64_t)pool + off + 0x210) = cnt - 1;
            sk_f_006648a8();
        }
        off = off + 8;
        if (off == 0xe0) {
            *(int64_t *)(tls + 0xf8) = 0;
            return;
        }
    } while (1);
breakpoint:
    SoftwareBreakpoint(0x5519, 0x664a84);
}

/* FUN_00664a84 @ 0x00664a84   (est. tls_base_set)
 * Ghidra: void FUN_00664a84(uint64_t param_1)
 * Installs the given value as the current thread's TLS base via tpidr_el0.
 * Confidence: medium
 * Notes: writes tpidr_el0. */
void sk_f_00664a84(uint64_t new_tls)
{
    tpidr_el0 = new_tls;
}

/* FUN_00664a8c @ 0x00664a8c   (est. pool_slot_hook)
 * Ghidra: uint64_t FUN_00664a8c(long *param_1,uint64_t param_2)
 * Callback invoked for an allocated pool slot: reads the slot index from
 * *param_1, resolves the per-slot function pointer at pool+idx*8 and calls it
 * to derive a value, storing the result into a table produced by
 * sk_x_00662264(param_2) at [idx-1]. Increments the slot counter at
 * pool+idx*8+0x1f8 and faults on overflow (previous == -1) via
 * sk_x_0065c2f0. Returns 1 on success.
 * Confidence: medium
 * Notes: reads/writes _DAT_006fe7e8; calls FUN_0065ccc8, FUN_00662264,
 * FUN_0065c2f0; SoftwareBreakpoint(0x5519,0x664b5c). */
uint64_t sk_f_00664a8c(int64_t *slot_idx, uint64_t table_id)
{
    uint64_t *pool;
    uint64_t *slot;
    int64_t *arr;
    int64_t *dst;
    int64_t idx = *slot_idx;

    pool = (uint64_t *)sk_g_006fe7e8;
    if (sk_g_006fe7e8 == 0) {
        int64_t tls = sk_x_0065ccc8();
        pool = *(uint64_t **)(tls + 0x50);
        if ((uint64_t)pool + 0x2f0 < (uint64_t)pool) {
            goto breakpoint;   /* pool base overflow */
        }
    }
    sk_g_006fe7e8 = (uint64_t)pool;
    pool = (uint64_t *)sk_g_006fe7e8;
    arr = (int64_t *)sk_x_00662264(table_id);
    slot = (uint64_t *)((uint64_t)pool + (uint64_t)idx * 8);
    if (((uint64_t *)((uint64_t)pool + 8) <= slot &&
         slot + 1 <= (uint64_t *)((uint64_t)pool + 0x100)) && slot <= slot + 1) {
        idx = idx - 1;
        int64_t val = (*(int64_t (*)(void))*slot)();
        dst = arr + idx;
        if ((arr <= dst && dst + 1 <= arr + 0x1f) && dst <= dst + 1) {
            *dst = val;
            if (val != 0) {
                int64_t cnt = *(int64_t *)((uint64_t)pool + (uint64_t)idx * 8 + 0x1f8);
                *(int64_t *)((uint64_t)pool + (uint64_t)idx * 8 + 0x1f8) = cnt + 1;
                if (cnt == -1) {
                    sk_x_0065c2f0(0, 0x6a7f0f);   /* noreturn counter overflow */
                }
            }
            return 1;
        }
    }
breakpoint:
    SoftwareBreakpoint(0x5519, 0x664b5c);
}

/* FUN_00664bd4 @ 0x00664bd4   (est. stub_success)
 * Ghidra: uint64_t FUN_00664bd4(void)
 * Trivial stub returning 0.
 * Confidence: medium */
uint64_t sk_f_00664bd4(void)
{
    return 0;
}

/* FUN_00664c04 @ 0x00664c04   (est. stub_nop)
 * Ghidra: void FUN_00664c04(void)
 * Empty function returning immediately; several blocks were removed as
 * unreachable by the decompiler.
 * Confidence: medium
 * Notes: decompiler removed unreachable blocks (ram,0x00664c48..0x00664cb8). */
void sk_f_00664c04(void)
{
}

/* FUN_00664cbc @ 0x00664cbc   (est. cpu_msg_channel_init)
 * Ghidra: void FUN_00664cbc(void)
 * One-time per-cpu message-channel setup: verifies the cpu context has no
 * channel yet (ctx+0x48), lazily allocates an 8-uint8_t channel object via
 * sk_x_006832c8 and registers it with sk_f_006642bc, then emits a fixed
 * header message through the tpidrro_el0 mailbox via repeated CallSupervisor
 * calls. When the channel kind matches it drains the pending queue
 * (_DAT_006ff0c8), forwarding each message through sk_x_00685588 and, on a
 * state change, encoding the cpu value into the mailbox and re-sending.
 * Finally it resets two global linked lists (sk_g_006fe7f8) and returns if
 * the saved  sk_g_006b5ed0 guard is unchanged, otherwise teardown faults.
 * Confidence: low (large body; many uint8_t-level mailbox writes and
 * unreachable-block removal; exact protocol semantics inferred)
 * Notes: globals _DAT_006b5ed0, _DAT_006b70db/dd/de/df/e1/e2, _DAT_006fe7f0,
 * _DAT_006fe7f8, _DAT_006b56c8, _DAT_006b56e0, _DAT_006ff0c8, _DAT_006b4368,
 * ram0x0068a0b0/DAT_0068a0b8/DAT_0068a0c0, _DAT_0066548c; calls
 * FUN_0065ccc8, FUN_0065c2f0, FUN_006832c8, FUN_00661324, FUN_0065f058,
 * thunk_FUN_0067aa00, FUN_006642bc, FUN_0065cedc, FUN_00654cc8,
 * FUN_00661318, FUN_0067d1f0, FUN_00685538, FUN_00685588, FUN_006854e8,
 * FUN_0067f660; SoftwareBreakpoint(0x5519,0x66505c); decompiler removed
 * unreachable blocks (ram,0x00664c48..0x00664cb8). */
void sk_f_00664cbc(void)
{
    uint8_t *msg;
    uint64_t u20;
    uint64_t queue_out[4];
    uint64_t saved = sk_g_006b5ed0;
    int64_t ctx = sk_x_0065ccc8();

    if (*(int64_t *)(ctx + 0x48) != 0) {
        goto fault;
    }
    u20 = ((uint64_t)sk_g_006b70dd << 0x10) | ((uint64_t)sk_g_006b70de << 0x18) |
          (uint64_t)sk_g_006b70db |
          ((uint64_t)(((uint32_t)sk_g_006b70e1 << 0x10) |
                      ((uint32_t)sk_g_006b70e2 << 0x18) | (uint32_t)sk_g_006b70df) << 0x20);
    if (u20 == 0) {
        sk_g_006fe7f0 = sk_x_006832c8(8);
        if (sk_g_006fe7f0 == 0) {
            sk_x_0065c2f0(0, 0x6a7f58);   /* noreturn allocation failure */
        }
        uint64_t kind = sk_x_00661324();
        u20 = sk_g_006fe7f0;
        if ((kind & 1) == 0) {
            sk_x_0065f058(sk_g_006fe7f0, 8);
            u20 = sk_g_006fe7f0;
        }
    }
    sk_g_006fe7f0 = u20;
    u20 = sk_g_006fe7f0;
    *(uint64_t *)(ctx + 0x48) = sk_g_006fe7f0;
    uint8_t stackbuf[40];
    sk_x_0067aa00(stackbuf, 0x6b6888, 0x28);
    uint64_t head = sk_g_0068a0b0;
    uint64_t head2 = sk_g_0068a0b8;
    uint64_t head3 = sk_g_0068a0c0;
    sk_f_006642bc(0x6ff0b0, u20, stackbuf, &head);
    u20 = sk_g_006fe7f0;
    msg = (uint8_t *)tpidrro_el0;
    msg[2] = 0x5d;
    msg[0] = 0x90;
    msg[4] = 0;
    msg[5] = 0;
    msg[2] = 0x66;
    msg[3] = 0;
    msg[6] = 0;
    msg[7] = 0;
    CallSupervisor(0);
    msg[0] = 0x90;
    msg[7] = 0;
    msg[6] = 0;
    msg[5] = 0;
    msg[4] = 0;
    msg[3] = 0;
    msg[2] = 0x66;
    msg[2] = 0x5d;
    if ((u20 & 0xff) == 0) {
        sk_x_0065cedc(&sk_g_0066548c, 0);
        u20 = sk_g_006ff0c8;
        ctx = sk_x_00654cc8();
        if (u20 != 0) {
            int64_t l18;
            int16_t s15;
            do {
                l18 = *(int64_t *)(u20 + 0x28);
                uint16_t u8 = *(uint16_t *)msg;
                uint8_t u1 = msg[3];
                uint8_t u2 = msg[2];
                uint16_t u10 = *(uint16_t *)(msg + 4);
                uint8_t u3 = msg[7];
                uint8_t u4 = msg[6];
                uint64_t u11;
                do {
                    CallSupervisor(0);
                    msg[0] = (uint8_t)u8;
                    msg[5] = (uint8_t)(u10 >> 8);
                    msg[3] = u1;
                    msg[2] = u2;
                    msg[1] = (uint8_t)(u8 >> 8);
                    msg[4] = (uint8_t)u10;
                    msg[7] = u3;
                    msg[6] = u4;
                    u11 = sk_g_006b4368;
                } while (l18 == 1);
                if (ctx != 0) {
                    sk_x_00661318(l18, 0x12);
                    if ((uint64_t)u20 + 0x178 < (uint64_t)u20) break;   /* overflow */
                    sk_x_0067d1f0(u11, 0x6a8102);
                    uint64_t u17 = *(uint64_t *)(u20 + 0x28);
                    uint8_t m1 = (uint8_t)((uint64_t)ctx >> 8);
                    uint8_t m4 = (uint8_t)((uint64_t)ctx >> 0x20);
                    uint8_t m5 = (uint8_t)((uint64_t)ctx >> 0x28);
                    uint8_t m2 = (uint8_t)((uint64_t)ctx >> 0x10);
                    uint8_t m3 = (uint8_t)((uint64_t)ctx >> 0x18);
                    uint8_t m6 = (uint8_t)((uint64_t)ctx >> 0x30);
                    uint8_t m7 = (uint8_t)((uint64_t)ctx >> 0x38);
                    msg[1] = m1;
                    msg[0] = (uint8_t)ctx;
                    msg[4] = m4;
                    msg[5] = m5;
                    msg[2] = m2;
                    msg[3] = m3;
                    msg[6] = m6;
                    msg[7] = m7;
                    CallSupervisor(0);
                    msg[0] = (uint8_t)ctx;
                    msg[7] = m7;
                    msg[6] = m6;
                    msg[5] = m5;
                    msg[4] = m4;
                    msg[3] = m3;
                    msg[2] = m2;
                    msg[1] = m1;
                    if ((u17 & 0xff) != 0) {
                        sk_x_00685538(u17, queue_out);
                        goto fault;
                    }
                }
                s15 = sk_x_00685588(u20, u20 + 0x178, queue_out);
                if (s15 == 1) goto done;
                u20 = queue_out[0];
            } while (s15 != 0);
            SoftwareBreakpoint(0x5519, 0x66505c);
        }
done:
        {
            bool changed;

            uint8_t *node = (uint8_t *)0;

            do {
                uint8_t *next = (uint8_t *)sk_g_006fe7f8;
                if (sk_g_006fe7f8 == (uint64_t)node) {
                    sk_g_006fe7f8 = (uint64_t)&sk_g_006b56c8;
                }
                changed = (next != node);
                sk_g_006b56c8 = (uint64_t)node;
                if (changed) {
                    sk_g_006b56c8 = (uint64_t)next;
                }
                node = next;
            } while (changed);
        }
        {
            bool changed;

            uint8_t *node = (uint8_t *)0;

            do {
                uint8_t *next = (uint8_t *)sk_g_006fe7f8;
                if (sk_g_006fe7f8 == (uint64_t)node) {
                    sk_g_006fe7f8 = (uint64_t)&sk_g_006b56e0;
                }
                changed = (next != node);
                sk_g_006b56e0 = (uint64_t)node;
                if (changed) {
                    sk_g_006b56e0 = (uint64_t)next;
                }
                node = next;
            } while (changed);
        }
        if (sk_g_006b5ed0 == saved) {
            return;
        }
    } else {
        sk_x_006854e8(u20, queue_out);
    }
    sk_x_0067f660();   /* noreturn teardown */
    return;
fault:
    sk_x_0065c2f0(0, 0x6a7f28);   /* noreturn */
}
/* ===== part 2: fragment of SKR68 ===== */

/* FUN_0066512c @ 0x0066512c   (est. sk_l4_fault_dispatch)
 * Ghidra: long FUN_0066512c(uint64_t param_1, unsigned long param_2, long param_3)
 * Dispatches an L4 fault/syscall. If the high 16 bits of the fault word select
 * a handler id (==1), it invokes the id bootstrap, resolves the per-id fault
 * handler through a global table (bounds-checked), and returns the id << 16
 * after releasing the domain; an out-of-range id traps via SoftwareBreakpoint.
 * Otherwise, when no id bits are set, it builds the message word from the
 * current TCB (tpidrro_el0) and walks the registered fault-handler list (head
 * sk_g_006fe7f8) calling each handler's dispatch callback; a result of 1
 * short-circuits and returns 0xffff0000 (error sentinel).
 * Confidence: medium
 * Notes: DAT_006b4368 (current domain), DAT_006b5e58 handler-table bounds check,
 *   SoftwareBreakpoint(0x5519,0x665354), string 0x6a845a passed to FUN_0067d1f0. */
long sk_f_0066512c(uint64_t arg0, uint64_t fault, int64_t tcb)
{
    uint8_t *table_ent;
    int hresult;
    int64_t result;
    int64_t *node;
    uint64_t msg_word0;
    uint64_t msg_word1;
    uint64_t msg_word2;
    sk_u128_t ipc_msg;
    uint64_t handler_id;
    uint64_t domain;

    if ((((uint32_t)(fault >> 0x10)) & 0xffff) == 1) {
        sk_u128_t idret = sk_f_0066a8c4();
        /* indirect call through the second return word + 0x60 */
        handler_id = ((uint64_t (*)(void))*(uint64_t *)(idret.hi + 0x60))();
        domain = sk_g_006b4368;
        handler_id &= 0xff;
        if (handler_id == 0) {
            return 0;
        }
        sk_x_00661318();
        table_ent = (uint8_t *)(handler_id * 8 + 0x6b5e50);
        if ((uint8_t *)0x6b5e4f < table_ent &&
            ((uint8_t *)&sk_g_006b5e58) + handler_id * 8 < (uint8_t *)0x6b5e91 &&
            table_ent <= ((uint8_t *)&sk_g_006b5e58) + handler_id * 8) {
            sk_x_0067d1f0(domain, 0x6a845a);   /* release domain; string 0x6a845a */
            return handler_id << 0x10;
        }
        SoftwareBreakpoint(0x5519, 0x665354);   /* does not return */
    }
    if ((fault & 0xffff0000) == 0) {
        uint8_t *tcb_base = (uint8_t *)tpidrro_el0;
        msg_word0 = (uint64_t)*(uint8_t *)(tcb_base + 10) << 0x10 |
                    (uint64_t)*(uint8_t *)(tcb_base + 0xb) << 0x18 |
                    (uint64_t)*(uint16_t *)(tcb_base + 8) |
                    ((uint64_t)((uint32_t)*(uint8_t *)(tcb_base + 0xe) << 0x10 |
                                (uint32_t)*(uint8_t *)(tcb_base + 0xf) << 0x18 |
                                (uint32_t)*(uint16_t *)(tcb_base + 0xc))) << 0x20;
        msg_word1 = (uint64_t)*(uint8_t *)(tcb_base + 0x12) << 0x10 |
                    (uint64_t)*(uint8_t *)(tcb_base + 0x13) << 0x18 |
                    (uint64_t)*(uint16_t *)(tcb_base + 0x10) |
                    ((uint64_t)((uint32_t)*(uint8_t *)(tcb_base + 0x16) << 0x10 |
                                (uint32_t)*(uint8_t *)(tcb_base + 0x17) << 0x18 |
                                (uint32_t)*(uint16_t *)(tcb_base + 0x14))) << 0x20;
        ipc_msg = sk_f_00665ef8(&msg_word0);
        msg_word1 = 0;
        msg_word0 = 0;
        msg_word2 = 0;
        sk_f_00665d9c(&msg_word0, tcb, &ipc_msg);
        node = *(int64_t **)(tcb + 0x98);
        if (node == 0) {
            hresult = 0;
            node = (int64_t *)sk_g_006fe7f8;
            for (; node != 0; node = (int64_t *)*node) {
                hresult = ((uint64_t (*)(uint64_t, int64_t, void *))node[2])(
                            node[1], tcb, &msg_word0);
                if (hresult - 1U < 2) break;
            }
            if (hresult == 1) {
                result = 0xffff0000;
            } else {
                result = sk_f_0066599c(tcb, &msg_word0);
            }
        } else {
            do {
                hresult = ((uint64_t (*)(uint64_t, int64_t, void *))node[2])(
                            node[1], tcb, &msg_word0);
                if (hresult - 1U < 2) break;
                node = (int64_t *)*node;
            } while (node != 0);
            if (hresult == 1) {
                result = 0xffff0000;
            } else if (hresult != 2) {
                /* scan from the global list head (joined_r0x00665290) */
                node = (int64_t *)sk_g_006fe7f8;
                for (; node != 0; node = (int64_t *)*node) {
                    hresult = ((uint64_t (*)(uint64_t, int64_t, void *))node[2])(
                                node[1], tcb, &msg_word0);
                    if (hresult - 1U < 2) break;
                }
                result = (hresult == 1) ? 0xffff0000
                                        : sk_f_0066599c(tcb, &msg_word0);
            } else {
                result = sk_f_0066599c(tcb, &msg_word0);
            }
        }
    } else {
        result = 0xffff0000;
    }
    return result;
}

/* FUN_00665354 @ 0x00665354   (est. sk_l4_errorcode_str)
 * Ghidra: void FUN_00665354(uint64_t param_1, uint8_t param_2)
 * Formats an L4 error code into the caller-supplied buffer buf (a fixed
 * 0x20-uint8_t name field). For codes 0..9 it copies the corresponding named
 * error string (Success, Preempted, Canceled, ...); for any code >9 it copies
 * a generic "invalid error code" string and additionally calls FUN_0064effc to
 * clear the field, signaling the invalid value.
 * Confidence: high
 * Notes: s_L4_ErrorCode* strings at 0x0068a0c8..0x0068a1e8; generic string
 *   DAT_0068a208; callees thunk_FUN_0067aa00 / FUN_0064effc. */
void sk_f_00665354(uint64_t buf, uint8_t code)
{
    const char *errstr;

    if (9 < code) {
        sk_x_0067aa00(buf, &sk_g_0068a208, 0x20);
        sk_x_0064effc(buf, 0x20);
        return;
    }
    switch (code) {
    default:
        errstr = sk_str_0068a0c8;   /* L4_ErrorCodeSuccess */
        break;
    case 1:
        errstr = sk_str_0068a0e8;   /* L4_ErrorCodePreempted */
        break;
    case 2:
        errstr = sk_str_0068a108;   /* L4_ErrorCodeCanceled */
        break;
    case 3:
        errstr = sk_str_0068a128;   /* L4_ErrorCodeTruncated */
        break;
    case 4:
        errstr = sk_str_0068a148;   /* L4_ErrorCodeCapInvalid */
        break;
    case 5:
        errstr = sk_str_0068a168;   /* L4_ErrorCodeSlotInvalid */
        break;
    case 6:
        errstr = sk_str_0068a188;   /* L4_ErrorCodeMethodInvalid */
        break;
    case 7:
        errstr = sk_str_0068a1a8;   /* L4_ErrorCodeArgumentInvalid */
        break;
    case 8:
        errstr = sk_str_0068a1c8;   /* L4_ErrorCodeOperationInvalid */
        break;
    case 9:
        errstr = sk_str_0068a1e8;   /* L4_ErrorCodePermissionInvalid */
        break;
    }
    sk_x_0067aa00(buf, errstr, 0x20);
}

/* FUN_00665498 @ 0x00665498   (est. sk_l4_obj_init_wrap)
 * Ghidra: uint64_t FUN_00665498(uint64_t param_1, uint64_t param_2)
 * Thin wrapper: initializes the object/capability identified by obj via
 * sk_f_006657d8 (which lazily allocates + wires the backing state) and returns
 * the constant success code 1.
 * Confidence: medium
 * Notes: only callee is in-slice FUN_006657d8. */
uint64_t sk_f_00665498(uint64_t arg0, uint64_t obj)
{
    sk_f_006657d8(obj);
    return 1;
}

/* FUN_006654b8 @ 0x006654b8   (est. sk_l4_send_msg_code3)
 * Ghidra: void FUN_006654b8(uint64_t param_1, long param_2, long *param_3)
 * Builds and performs an L4 synchronous message send under a preemption guard
 * (sk_g_006b5ed0). When the message header (msg) matches the expected tag
 * (tag==3, kind==0x02), it lazily allocates a 16-uint8_t capability object at
 * cap+0x108 (tag 0x15), then writes the message code 3 and the object pointer
 * into the TCB message word (tpidrro_el0) and calls the supervisor. On failure
 * it faults (noreturn FUN_0065c2f0). Returns under the guard or traps via
 * FUN_0067f660 if the guard was modified.
 * Confidence: medium
 * Notes: DAT_006b5ed0 preemption guard, FUN_006832c8(0x15) alloc,
 *   FUN_00685608 error path, CallSupervisor(0), string 0x6a8255. */
void sk_f_006654b8(uint64_t arg0, int64_t cap, int64_t *msg)
{
    int64_t newcap;
    uint64_t status;
    uint64_t fault;
    uint8_t scratch[32];
    int64_t guard;
    uint8_t *tcb;

    guard = sk_g_006b5ed0;
    if ((*msg == 3) && (((char)msg[3]) == '\x02')) {
        newcap = *(int64_t *)(cap + 0x108);
        if (newcap == 0) {
            newcap = sk_x_006832c8(0x15);
            *(int64_t *)(cap + 0x108) = newcap;
            status = 0;
            if (newcap == 0) {
                goto fatal;   /* sk_x_0065c2f0(status, 0x6a8255) does not return */
            }
        }
        fault = *(uint64_t *)(cap + 0x28);
        tcb = (uint8_t *)tpidrro_el0;
        tcb[1] = 0; tcb[4] = 0; tcb[2] = 0; tcb[5] = 0; tcb[3] = 0; tcb[6] = 0;
        tcb[0] = 3;
        tcb[7] = 0;
        tcb[8]  = (uint8_t)newcap;
        tcb[0xd] = (uint8_t)((uint64_t)newcap >> 0x28);
        tcb[0xb] = (uint8_t)((uint64_t)newcap >> 0x18);
        tcb[10]  = (uint8_t)((uint64_t)newcap >> 0x10);
        tcb[9]   = (uint8_t)((uint64_t)newcap >> 8);
        tcb[0xc] = (uint8_t)((uint64_t)newcap >> 0x20);
        tcb[0xf] = (uint8_t)((uint64_t)newcap >> 0x38);
        tcb[0xe] = (uint8_t)((uint64_t)newcap >> 0x30);
        cap = 0x13;
        CallSupervisor(0);
        tcb[0] = 3;
        tcb[7] = 0; tcb[6] = 0; tcb[5] = 0; tcb[4] = 0; tcb[3] = 0; tcb[2] = 0;
        tcb[1] = 0;
        if ((fault & 0xff) != 0) {
            status = sk_x_00685608(fault, scratch);
fatal:
            sk_x_0065c2f0(status, 0x6a8255);   /* does not return */
        }
        status = 1;
    } else {
        status = 0;
    }
    if (sk_g_006b5ed0 == guard) {
        return;
    }
    sk_x_0067f660(status, cap);   /* does not return */
}

/* FUN_00665630 @ 0x00665630   (est. sk_list_splice_push)
 * Ghidra: void FUN_00665630(uint64_t *param_1)
 * Walks the global list whose head is sk_g_006fe7f8, tracking the previous
 * node, and splices the new node into the head slot once the walk revisits the
 * node it started from (end/cycle detection). Always terminates and leaves the
 * node linked in.
 * Confidence: low
 * Notes: single global DAT_006fe7f8; loop relies on self-consistent list
 *   pointers; no explicit count bound. */
void sk_f_00665630(uint64_t *node)
{
    uint64_t *cur;
    uint64_t *prev;
    bool cont;

    *node = 0;
    prev = 0;
    do {
        cur = (uint64_t *)sk_g_006fe7f8;
        if (sk_g_006fe7f8 == (uint64_t)prev) {
            sk_g_006fe7f8 = (uint64_t)node;
        }
        cont = cur != prev;
        if (cont) {
            prev = cur;
        }
        *node = (uint64_t)prev;
        prev = cur;
    } while (cont);
}

/* FUN_00665660 @ 0x00665660   (est. sk_l4_send_msg_code2)
 * Ghidra: void FUN_00665660(uint64_t param_1, long param_2, long *param_3)
 * L4 synchronous message send (peer of sk_f_006654b8). When the message header
 * matches (tag==3, kind==0x03), lazily allocates a 16-uint8_t capability object at
 * cap+0x110 (tag 0x14), writes message code 2 with the object pointer into the
 * TCB message word and calls the supervisor. On failure faults (noreturn).
 * Returns under the preemption guard or traps via FUN_0067f660 if modified.
 * Confidence: medium
 * Notes: DAT_006b5ed0 guard, FUN_006832c8(0x14) alloc, FUN_00685658 error path,
 *   CallSupervisor(0), string 0x6a82fd. */
void sk_f_00665660(uint64_t arg0, int64_t cap, int64_t *msg)
{
    int64_t newcap;
    uint64_t status;
    uint64_t fault;
    uint8_t scratch[32];
    int64_t guard;
    uint8_t *tcb;

    guard = sk_g_006b5ed0;
    if ((*msg == 3) && (((char)msg[3]) == '\x03')) {
        newcap = *(int64_t *)(cap + 0x110);
        if (newcap == 0) {
            newcap = sk_x_006832c8(0x14);
            *(int64_t *)(cap + 0x110) = newcap;
            status = 0;
            if (newcap == 0) {
                goto fatal;   /* sk_x_0065c2f0(status, 0x6a82fd) does not return */
            }
        }
        fault = *(uint64_t *)(cap + 0x28);
        tcb = (uint8_t *)tpidrro_el0;
        tcb[1] = 0; tcb[4] = 0; tcb[2] = 0; tcb[5] = 0; tcb[3] = 0; tcb[6] = 0;
        tcb[0] = 2;
        tcb[7] = 0;
        tcb[8]  = (uint8_t)newcap;
        tcb[0xd] = (uint8_t)((uint64_t)newcap >> 0x28);
        tcb[0xb] = (uint8_t)((uint64_t)newcap >> 0x18);
        tcb[10]  = (uint8_t)((uint64_t)newcap >> 0x10);
        tcb[9]   = (uint8_t)((uint64_t)newcap >> 8);
        tcb[0xc] = (uint8_t)((uint64_t)newcap >> 0x20);
        tcb[0xf] = (uint8_t)((uint64_t)newcap >> 0x38);
        tcb[0xe] = (uint8_t)((uint64_t)newcap >> 0x30);
        cap = 0x13;
        CallSupervisor(0);
        tcb[0] = 2;
        tcb[7] = 0; tcb[6] = 0; tcb[5] = 0; tcb[4] = 0; tcb[3] = 0; tcb[2] = 0;
        tcb[1] = 0;
        if ((fault & 0xff) != 0) {
            status = sk_x_00685658(fault, scratch);
fatal:
            sk_x_0065c2f0(status, 0x6a82fd);   /* does not return */
        }
        status = 1;
    } else {
        status = 0;
    }
    if (sk_g_006b5ed0 == guard) {
        return;
    }
    sk_x_0067f660(status, cap);   /* does not return */
}

/* FUN_006657d8 @ 0x006657d8   (est. sk_l4_obj_init)
 * Ghidra: void FUN_006657d8(long param_1)
 * Lazily initializes the object at obj: if the slot at obj+0x88 is empty, it
 * obtains a backing object from sk_f_00665860 and stores it there, then wires
 * it via FUN_006856a8; allocation failure faults (noreturn). Returns under the
 * preemption guard or traps if the guard changed.
 * Confidence: medium
 * Notes: DAT_006b5ed0 guard, FUN_006856a8 wire-up, string-free noreturn guard
 *   check FUN_0067f660(status). */
void sk_f_006657d8(int64_t obj)
{
    uint64_t status;
    int64_t backing;
    uint8_t scratch[32];
    int64_t guard;

    guard = sk_g_006b5ed0;
    if (*(int64_t *)(obj + 0x88) == 0) {
        backing = sk_f_00665860();
        *(int64_t *)(obj + 0x88) = backing;
        status = 0;
        if (backing == 0) {
            goto done;   /* sk_x_0067f660(status) does not return */
        }
        sk_x_006856a8(obj, (int64_t *)(obj + 0x88), scratch);
    }
    status = 1;
done:
    if (sk_g_006b5ed0 == guard) {
        return;
    }
    sk_x_0067f660(status);   /* does not return */
}

/* FUN_00665860 @ 0x00665860   (est. sk_l4_alloc_supervisor)
 * Ghidra: long FUN_00665860(uint64_t param_1)
 * Allocates a new object under the supervisor. Reads the current per-cpu
 * context (sk_x_0065ccc8 + 0x48); when a context is present it allocates via
 * sk_f_0066ad54, builds a 24-uint8_t message (code from sk_g_0068a0a0, high word
 * at 0x68a0a8, and kind) in the TCB, and performs CallSupervisor(3). On a null
 * allocation it returns 0; otherwise returns the allocated object and, if a
 * context was retained, hands it to FUN_006860f4 for registration.
 * Confidence: low
 * Notes: uRam000000000068a0a8 = ((uint64_t*)&DAT_0068a0a0)[1]; CallSupervisor(3);
 *   FUN_0066ad54 alloc, FUN_006860f4(obj,obj,2) registration. */
long sk_f_00665860(uint64_t kind)
{
    uint64_t code_lo;
    uint64_t code_hi;
    int64_t ctx;
    int64_t obj;
    uint8_t *tcb;

    ctx = sk_x_0065ccc8();
    if (*(int64_t *)(ctx + 0x48) != 0) {
        obj = sk_f_0066ad54();
        code_hi = ((uint64_t *)&sk_g_0068a0a0)[1];   /* uRam 0x68a0a8 */
        code_lo = sk_g_0068a0a0;
        if (obj == 0) {
            return 0;
        }
        ctx = *(int64_t *)(ctx + 0x48);
        tcb = (uint8_t *)tpidrro_el0;
        tcb[0]  = (uint8_t)code_lo;
        tcb[0xd] = (uint8_t)(code_hi >> 0x28);
        tcb[9]   = (uint8_t)(code_hi >> 8);
        tcb[5]   = (uint8_t)(code_lo >> 0x28);
        tcb[3]   = (uint8_t)(code_lo >> 0x18);
        tcb[2]   = (uint8_t)(code_lo >> 0x10);
        tcb[1]   = (uint8_t)(code_lo >> 8);
        tcb[0x15] = (uint8_t)(kind >> 0x28);
        tcb[8]   = (uint8_t)code_hi;
        tcb[0xb] = (uint8_t)(code_hi >> 0x18);
        tcb[10]  = (uint8_t)(code_hi >> 0x10);
        tcb[0xc] = (uint8_t)(code_hi >> 0x20);
        tcb[0x11] = (uint8_t)(kind >> 8);
        tcb[0xf] = (uint8_t)(code_hi >> 0x38);
        tcb[0xe] = (uint8_t)(code_hi >> 0x30);
        tcb[4]   = (uint8_t)(code_lo >> 0x20);
        tcb[7]   = (uint8_t)(code_lo >> 0x38);
        tcb[6]   = (uint8_t)(code_lo >> 0x30);
        tcb[0x10] = (uint8_t)kind;
        tcb[0x13] = (uint8_t)(kind >> 0x18);
        tcb[0x12] = (uint8_t)(kind >> 0x10);
        tcb[0x14] = (uint8_t)(kind >> 0x20);
        tcb[0x17] = (uint8_t)(kind >> 0x38);
        tcb[0x16] = (uint8_t)(kind >> 0x30);
        CallSupervisor(3);
        if (ctx == 0) {
            return obj;
        }
        sk_x_006860f4(obj, obj, 2);
    }
    return 0;
}

/* FUN_0066599c @ 0x0066599c   (est. sk_l4_method_call)
 * Ghidra: uint64_t FUN_0066599c(uint64_t param_1, long param_2)
 * Performs an L4 method call on the object at tcb. First it consults the
 * per-cpu context's method dispatcher (sk_x_0065ccc8 + 0x80): if present and
 * its dispatch callback (at +0x10) returns 1, it short-circuits with the
 * 0xffff0000 error sentinel. Otherwise it reads the IPC tag word at tcb+0x10
 * (msg word +1) and hands off to sk_f_00665a38, then faults (noreturn
 * FUN_0065c2f0, string 0x6a8211).
 * Confidence: medium
 * Notes: FUN_0065ccc8 context, dispatch table at +0x80, string 0x6a8211. */
uint64_t sk_f_0066599c(uint64_t recv, int64_t tcb)
{
    int res;
    int64_t dtable;
    uint64_t *tag;
    uint64_t tag0;
    uint64_t tag1;

    dtable = sk_x_0065ccc8();
    dtable = *(int64_t *)(dtable + 0x80);
    if ((dtable != 0) &&
        res = ((uint64_t (*)(uint64_t, uint64_t, int64_t))*(uint64_t *)(dtable + 0x10))(
                     *(uint64_t *)(dtable + 8), recv, tcb),
         res == 1)) {
        return 0xffff0000;
    }
    tag = *(uint64_t **)(tcb + 0x10);
    if (tag == 0) {
        tag0 = 0;
        tag1 = 0;
    } else {
        tag0 = *tag;
        tag1 = tag[1];
    }
    sk_f_00665a38(recv, tag0, tag1);
    sk_x_0065c2f0(recv, 0x6a8211);   /* does not return */
}

/* FUN_00665a38 @ 0x00665a38   (est. sk_l4_msg_list_send)
 * Ghidra: void FUN_00665a38(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Walks the global message/notification list (head from sk_x_0065cb74) under a
 * lock acquired via sk_x_00655708(sk_g_006b4368). For each live node (sign bit
 * set on uint8_t +8) it runs a bounds/overflow check (SoftwareBreakpoint on wrap)
 * and dispatches the node to FUN_00685864. If the list is empty it reports a
 * fatal (FUN_006631d8, string 0x6a852b, code 0x21) and drops the lock if it was
 * acquired. Loops until a NULL node (unreachable terminator).
 * Confidence: medium
 * Notes: lock FUN_00655708/00655774 on DAT_006b4368, head FUN_0065cb74,
 *   SoftwareBreakpoint(0x5519,0x665b04), FUN_00685864 dispatch. */
void sk_f_00665a38(uint64_t who, uint64_t v0, uint64_t v1)
{
    int locked;
    uint64_t *node;
    uint64_t scratch;

    locked = sk_x_00655708(sk_g_006b4368);
    node = (uint64_t *)sk_x_0065cb74();
    do {
        if (node == 0) {
            sk_x_006631d8(0x6a852b, 0x21, sk_g_006b4368, who, 1, 1,
                          v0, v1);   /* fatal; string 0x6a852b */
            if (locked == 0) {
                sk_x_00655774(sk_g_006b4368);
            }
            return;
        }
        if (*(char *)(node + 1) < 0) {
            scratch = 0;
            if (node + 0xf < node) {
                SoftwareBreakpoint(0x5519, 0x665b04);   /* does not return */
            }
            sk_x_00685864(node, &scratch);
        }
        node = (uint64_t *)*node;
    } while (1);
}

/* FUN_00665bd4 @ 0x00665bd4   (est. sk_l4_bool_supervisor_call)
 * Ghidra: uint8_t [16] FUN_00665bd4(void)
 * Issues an L4 supervisor call that yields a 16-uint8_t {1,0} result (boolean
 * "true"). If the per-cpu context (sk_x_0065ccc8 + 0x48) is absent it faults
 * via FUN_0068596c; otherwise it writes the message code 0 with a sub-field 1
 * into the TCB and performs CallSupervisor(0). Afterwards, if no context was
 * retained it reports via FUN_00661318 + FUN_0067d1f0 (string 0x6a8419), else
 * it releases via FUN_00685928.
 * Confidence: low
 * Notes: ZEXT816(1) = {lo:1, hi:0}; CallSupervisor(0); DAT_006b4368 domain. */
sk_u128_t sk_f_00665bd4(void)
{
    uint64_t domain;
    int64_t ctx;
    uint8_t *tcb;

    ctx = sk_x_0065ccc8();
    ctx = *(int64_t *)(ctx + 0x48);
    if (ctx == 0) {
        sk_x_0068596c();
    } else {
        tcb = (uint8_t *)tpidrro_el0;
        tcb[1] = 0; tcb[4] = 0; tcb[0] = 0; tcb[5] = 0; tcb[6] = 0; tcb[7] = 0;
        tcb[2] = 1;
        tcb[3] = 0;
        CallSupervisor(0);
        tcb[0] = 0;
        tcb[7] = 0; tcb[6] = 0; tcb[5] = 0; tcb[4] = 0; tcb[3] = 0; tcb[2] = 1;
        tcb[1] = 0;
        domain = sk_g_006b4368;
        if (ctx == 0) {
            sk_x_00661318();
            sk_x_0067d1f0(domain, 0x6a8419);
        } else {
            sk_x_00685928(ctx, 0);
        }
    }
    return (sk_u128_t){ .lo = 1, .hi = 0 };
}

/* FUN_00665cec @ 0x00665cec   (est. sk_l4_err_str_thunk)
 * Ghidra: void FUN_00665cec(void)
 * Thunk that formats an L4 error-code string into a caller-local stack buffer
 * by forwarding to sk_f_00665354 (the L4 error-code stringifier). The code
 * argument is not explicitly set here, so it reads whatever is in x1.
 * Confidence: low
 * Notes: &stack0x00000010 is a local 0x20-uint8_t buffer; forwards to FUN_00665354. */
void sk_f_00665cec(void)
{
    uint8_t local_buf[0x20];

    sk_f_00665354((uint64_t)local_buf);
}
/* ===== part 3: fragment of SKR68 ===== */

/* FUN_00665d0c @ 0x00665d0c   (est. sk_placeholder_noop)
 * Ghidra: void FUN_00665d0c(void)
 * Empty function that immediately returns. Likely a reserved/placeholder stub
 * slot in the capability or kernel dispatch table.
 * Confidence: high
 * Notes: no body; Ghidra warns globals starting with '_' overlap smaller
 *   symbols at this address. */
void sk_f_00665d0c(void)
{
    return;
}

/* FUN_00665d20 @ 0x00665d20   (est. sk_placeholder_noop)
 * Ghidra: void FUN_00665d20(void)
 * Empty function that immediately returns. Reserved/placeholder stub slot.
 * Confidence: high
 * Notes: no body; Ghidra warns globals starting with '_' overlap smaller
 *   symbols at this address. */
void sk_f_00665d20(void)
{
    return;
}

/* FUN_00665d44 @ 0x00665d44   (est. sk_tag_write_byte_fields)
 * Ghidra: void FUN_00665d44(uint64_t param_1,uint64_t param_2,uint64_t param_3)
 * Stores tag bytes into a structure addressed through the x9 register (a
 * hidden extra argument): a uint8_t from w8 into offset +4, and the top two
 * bytes of param_3 into offsets +7 and +6. A tail fragment of a larger tag
 * builder that relies on register-passed state (x9/w8) rather than stack
 * arguments.
 * Confidence: medium
 * Notes: writes via in_x9 (x9 register) and in_w8 (w8 register) — hidden
 *   register arguments; offsets +4/+6/+7 of the target. */
void sk_f_00665d44(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint8_t tag_byte;   /* in_w8 — register-sourced uint8_t */
    uint64_t target;    /* in_x9 — register-sourced target base */

    (void)param_1;
    (void)param_2;
    /* tag_byte and target arrive via w8/x9 from the call site */
    *(uint8_t *)(target + 4) = tag_byte;
    *(char *)(target + 7) = (char)(param_3 >> 0x38);
    *(char *)(target + 6) = (char)(param_3 >> 0x30);
    return;
}

/* FUN_00665d60 @ 0x00665d60   (est. sk_placeholder_noop)
 * Ghidra: void FUN_00665d60(void)
 * Empty function that immediately returns. Reserved/placeholder stub slot.
 * Confidence: high
 * Notes: no body; Ghidra warns globals starting with '_' overlap smaller
 *   symbols at this address. */
void sk_f_00665d60(void)
{
    return;
}

/* FUN_00665d70 @ 0x00665d70   (est. sk_placeholder_noop)
 * Ghidra: void FUN_00665d70(void)
 * Empty function that immediately returns. Reserved/placeholder stub slot.
 * Confidence: high
 * Notes: no body; Ghidra warns globals starting with '_' overlap smaller
 *   symbols at this address. */
void sk_f_00665d70(void)
{
    return;
}

/* FUN_00665d84 @ 0x00665d84   (est. sk_forward_trampoline)
 * Ghidra: void FUN_00665d84(void)
 * Bare forwarding stub: calls the in-slice helper sk_f_00665354 and returns.
 * Confidence: high
 * Notes: sole body is a call to FUN_00665354 (in-slice). */
void sk_f_00665d84(void)
{
    sk_f_00665354();
    return;
}

/* FUN_00665d9c @ 0x00665d9c   (est. sk_cap_type_decode)
 * Ghidra: void FUN_00665d9c(uint64_t *param_1,long param_2,unsigned long *param_3)
 * Decodes a 16-uint8_t capability word (read as two u64s from cap_word) into a
 * 4-word / 32-uint8_t descriptor buffer at desc. The type field in bits 26..31
 * selects the decode; aux_flag is a secondary flag consulted for types 0x3c
 * and 0x3f. Fills the descriptor's words and tag bytes (offsets 0x18 and
 * 0x19) and, for object-bearing kinds, calls the type-address helper
 * sk_f_00665f04 to resolve the target address. Control-flow structure
 * (including the unreachable 0x1d branch) is preserved from the decompile.
 * Confidence: medium
 * Notes: callee sk_f_00665f04 (in-slice); tag bytes written at 0x18/0x19 of
 *   the descriptor. */
void sk_f_00665d9c(uint64_t *desc, uint64_t aux_flag, uint64_t *cap_word)
{
    uint64_t cap_lo = cap_word[0];
    uint64_t cap_hi = cap_word[1];
    uint32_t type = (uint32_t)(cap_lo >> 0x1a) & 0x3f;
    uint64_t addr;
    uint8_t tag;

    if (type < 0x24) {
        if (1 < type - 0x20) {               /* type in {0x22,0x23} */
            if (type == 0x1d) {              /* unreachable per range check */
                addr = sk_f_00665f04();
                desc[0] = 0; desc[1] = addr; desc[2] = 0; desc[3] = 0;
                if ((cap_lo & 0xffffff) != 0) {
                    return;
                }
                tag = 3;
                desc[0] = 3;
                goto write_tag3;
            }
            goto clear_desc;
        }
        /* type in {0x20,0x21} */
        desc[2] = 0; desc[3] = 0; desc[0] = 0; desc[1] = 0;
        if ((cap_lo & 0x3c) != 4) {
            return;
        }
        desc[0] = 1; desc[1] = cap_hi;
        *(uint8_t *)((uint64_t)desc + 0x19) = 2;
    }
    else {
        if (1 < type - 0x24) {               /* type > 0x25 */
            if (type != 0x3f) {
                if ((type == 0x3c) && (aux_flag != 0)) {
                    addr = sk_f_00665f04();
                    desc[0] = 2; desc[1] = addr; desc[2] = 0;
                    desc[3] = cap_lo & 0xffff;
                    return;
                }
clear_desc:
                desc[2] = 0; desc[3] = 0; desc[0] = 0; desc[1] = 0;
                return;
            }
            if (aux_flag == 0) {
                goto clear_desc;
            }
            addr = sk_f_00665f04();
            desc[0] = 0; desc[1] = addr; desc[2] = 0; desc[3] = 0;
            if ((cap_lo & 0xffffff) != 3) {
                return;
            }
            desc[0] = 3;
            tag = 2;
            goto write_tag2;
        }
        /* type in {0x24,0x25} */
        type = (uint32_t)cap_lo & 0x3f;
        desc[2] = 0; desc[3] = 0; desc[0] = 0; desc[1] = 0;
        if (0x11 < type) {
            return;
        }
        if ((1 << ((uint32_t)cap_lo & 0x1f) & 0xf0f0U) == 0) {
            if (type != 0x11) {
                return;
            }
            desc[0] = 4; desc[1] = cap_hi;
            tag = (uint8_t)((cap_lo & 0x40) >> 6);
write_tag3:
            *(uint8_t *)(desc + 3) = tag;
            return;
        }
        desc[0] = 1; desc[1] = cap_hi;
        *(char *)((uint64_t)desc + 0x19) = (char)((cap_lo & 0x40) >> 6);
    }
    tag = (uint8_t)cap_lo & 3;
write_tag2:
    *(uint8_t *)(desc + 3) = tag;
    return;
}

/* FUN_00665ef8 @ 0x00665ef8   (est. sk_load_u128)
 * Ghidra: uint8_t [16] FUN_00665ef8(uint8_t (*param_1) [16])
 * Loads the 16-uint8_t value pointed to by src and returns it as a 128-bit value
 * (lo/hi pair). Pure load-and-return.
 * Confidence: high
 * Notes: returns via sk_u128_t. */
sk_u128_t sk_f_00665ef8(const sk_u128_t *src)
{
    return *src;
}

/* FUN_00665f04 @ 0x00665f04   (est. sk_read_utcb_and_supercall)
 * Ghidra: unsigned long FUN_00665f04(void)
 * Reads the current thread's user-tagged control-block base from tpidrro_el0,
 * stamps it with two 64-bit tag values (from globals at 0x68a230/0x68a238),
 * issues a Supervisor call (CallSupervisor(0)) carrying a (handle, 3) tag
 * triple, then clears the block's tag bytes and sets uint8_t 0 to 0x1f. On
 * success (low uint8_t of the returned handle is zero) it recomposes and returns
 * a 64-bit word assembled from the block's tag bytes at offsets 0x10..0x17,
 * guarded by a stack canary (DAT_006b5ed0). On failure it routes into a
 * non-returning error path.
 * Confidence: medium
 * Notes: CallSupervisor(0); tpidrro_el0; globals DAT_0068a230 / uRam0068a238
 *   (word at 0x68a238, prelude only declares sk_g_0068a230 — declaration for
 *   sk_g_0068a238 may be needed), DAT_006b5ed0 (canary); out-of-slice callees
 *   sk_x_0066239c, sk_x_00685a6c, sk_x_0067f660 (noreturn). */
uint64_t sk_f_00665f04(void)
{
    uint64_t canary = sk_g_006b5ed0;
    uint64_t handle = sk_x_0066239c();
    uint64_t tag_hi = sk_g_0068a238;   /* uRam0068a238: word at 0x68a238 */
    uint64_t tag_lo = sk_g_0068a230;
    uint8_t *block = (uint8_t *)tpidrro_el0;
    uint8_t scratch[32];               /* auStack_58 */
    sk_u128_t sc_args;

    block[0]  = (uint8_t)tag_lo;
    block[1]  = (uint8_t)(tag_lo >> 8);
    block[2]  = (uint8_t)(tag_lo >> 0x10);
    block[3]  = (uint8_t)(tag_lo >> 0x18);
    block[4]  = (uint8_t)(tag_lo >> 0x20);
    block[5]  = (uint8_t)(tag_lo >> 0x28);
    block[6]  = (uint8_t)(tag_lo >> 0x30);
    block[7]  = (uint8_t)(tag_lo >> 0x38);
    block[8]  = (uint8_t)tag_hi;
    block[9]  = (uint8_t)(tag_hi >> 8);
    block[0xa] = (uint8_t)(tag_hi >> 0x10);
    block[0xb] = (uint8_t)(tag_hi >> 0x18);
    block[0xc] = (uint8_t)(tag_hi >> 0x20);
    block[0xd] = (uint8_t)(tag_hi >> 0x28);
    block[0xe] = (uint8_t)(tag_hi >> 0x30);
    block[0xf] = (uint8_t)(tag_hi >> 0x38);

    sc_args.hi = 3;
    sc_args.lo = handle;
    CallSupervisor(0);

    block[0] = 0x1f;
    block[7] = 0; block[6] = 0; block[5] = 0; block[4] = 0;
    block[3] = 0; block[2] = 0; block[1] = 0;

    if ((handle & 0xff) == 0) {
        if (sk_g_006b5ed0 == canary) {
            return (uint64_t)block[0x12] << 0x10 |
                   (uint64_t)block[0x13] << 0x18 |
                   (uint64_t)*(uint16_t *)(block + 0x10) |
                   ((uint64_t)((uint32_t)block[0x16] << 0x10 |
                               (uint32_t)block[0x17] << 0x18 |
                               (uint32_t)*(uint16_t *)(block + 0x14)) << 0x20);
        }
    }
    else {
        sc_args = sk_x_00685a6c(handle, scratch);
    }
    /* FUN_0067f660 does not return */
    sk_x_0067f660(sc_args.lo, sc_args.hi);
}

/* FUN_0066609c @ 0x0066609c   (est. sk_emit_l4_error_string)
 * Ghidra: void FUN_0066609c(uint64_t param_1,uint8_t param_2)
 * Writes the L4 error-code name string for codes 0..9 into the 0x20-uint8_t
 * message buffer msg_buf (via the out-of-slice log helper sk_x_0067aa00);
 * codes above 9 get a generic unknown diagnostic plus a fill. Mirrors the
 * sibling error-string emitter elsewhere in this slice.
 * Confidence: high
 * Notes: string refs s_L4_ErrorCode* at 0x68a240..0x68a360, DAT_0068a380;
 *   thunk_FUN_0067aa00 and FUN_0064effc (both out-of-slice). */
void sk_f_0066609c(uint64_t msg_buf, uint8_t err_code)
{
    const char *err_name;

    if (9 < err_code) {
        sk_x_0067aa00(msg_buf, &sk_g_0068a380, 0x20);
        sk_x_0064effc(msg_buf, 0x20);
        return;
    }
    switch (err_code) {
    default:
        err_name = sk_str_0068a240;
        break;
    case 1:
        err_name = sk_str_0068a260;
        break;
    case 2:
        err_name = sk_str_0068a280;
        break;
    case 3:
        err_name = sk_str_0068a2a0;
        break;
    case 4:
        err_name = sk_str_0068a2c0;
        break;
    case 5:
        err_name = sk_str_0068a2e0;
        break;
    case 6:
        err_name = sk_str_0068a300;
        break;
    case 7:
        err_name = sk_str_0068a320;
        break;
    case 8:
        err_name = sk_str_0068a340;
        break;
    case 9:
        err_name = sk_str_0068a360;
        break;
    }
    sk_x_0067aa00(msg_buf, err_name, 0x20);
    return;
}

/* FUN_006661d4 @ 0x006661d4   (est. sk_set_current_vm_ptr)
 * Ghidra: void FUN_006661d4(uint64_t param_1)
 * Stores the given pointer/value into the global at 0x6fe800 (a saved
 * context/VM pointer consumed later by sk_f_006661e0).
 * Confidence: high
 * Notes: writes DAT_006fe800 -> sk_g_006fe800. */
void sk_f_006661d4(uint64_t val)
{
    sk_g_006fe800 = val;
    return;
}

/* FUN_006661e0 @ 0x006661e0   (est. sk_dispatch_saved_ctx)
 * Ghidra: void FUN_006661e0(uint64_t param_1,uint64_t param_2)
 * Forwards the two arguments together with the previously saved global
 * (sk_g_006fe800) to the in-slice helper sk_f_006661f4.
 * Confidence: medium
 * Notes: reads DAT_006fe800; callee sk_f_006661f4 (in-slice). */
void sk_f_006661e0(uint64_t a, uint64_t b)
{
    sk_f_006661f4(sk_g_006fe800, a, b);
    return;
}
/* ===== part 4: fragment of SKR68 ===== */

/* FUN_006661f4 @ 0x006661f4   (est. region_entry_lookup)
 * Ghidra: long FUN_006661f4(long *param_1,uint64_t param_2,long *param_3)
 * Walks a chain of region/arena entries starting at `entry`, searching for the
 * entry whose per-entry key matches `key`. For each candidate it computes an
 * aligned payload address from a helper result plus the entry base, tests the
 * key via a matcher helper, and follows `entry[1]`'s next-link when the key
 * does not match. Returns the aligned payload address on success (and stores
 * the matched entry's first word into *out when out is non-null), 0 when the
 * chain ends.
 * Confidence: medium
 * Notes: thunk_FUN_0067b220/0067aeb0 helpers; 8-uint8_t alignment; null-chain ends. */
unsigned long sk_f_006661f4(unsigned long *entry, unsigned long key, unsigned long *out)
{
    unsigned long addr;
    while (1) {
        if (entry == 0) {
            return 0;
        }
        unsigned long *base = entry + 2;
        addr = sk_x_0067b220(base);
        addr = (addr + (unsigned long)base & 0xfffffffffffffff8ULL) + 8;
        if (sk_x_0067aeb0(base, key) == 0) {
            break;
        }
        if (entry[1] == 0) {
            return 0;
        }
        entry = (unsigned long *)((addr + *entry + 7ULL) & 0xfffffffffffffff8ULL);
    }
    if (out != 0) {
        *out = *entry;
    }
    return addr;
}

/* FUN_0066628c @ 0x0066628c   (est. set_global_entry_root)
 * Ghidra: void FUN_0066628c(uint64_t param_1)
 * Stores the caller-supplied pointer into the global root slot sk_g_006fe808.
 * Confidence: high
 * Notes: _DAT_006fe808 (global root). */
unsigned long sk_f_0066628c(unsigned long root)
{
    sk_g_006fe808 = root;
    return 0;
}

/* FUN_00666298 @ 0x00666298   (est. region_entry_lookup_root)
 * Ghidra: void FUN_00666298(uint64_t param_1,uint64_t param_2)
 * Convenience wrapper: performs sk_f_006661f4 against the global root chain
 * stored in sk_g_006fe808, passing through the key and the optional out pointer.
 * The result is discarded.
 * Confidence: high
 * Notes: _DAT_006fe808 read; FUN_006661f4. */
unsigned long sk_f_00666298(unsigned long key, unsigned long out)
{
    sk_f_006661f4((unsigned long *)sk_g_006fe808, key, (unsigned long *)out);
    return 0;
}

/* FUN_006662ac @ 0x006662ac   (est. region_init_attach)
 * Ghidra: void FUN_006662ac(long *param_1,uint64_t param_2,uint64_t param_3)
 * Initialises a 5-word region/arena object `obj` (all words cleared), then
 * requests a 5-word bundle from the allocator helper sk_x_0066bce0 keyed by
 * `a`/`b` and a token from sk_f_0066ad54, populating the object from the
 * bundle. If the object's first word is null (allocation failed) or its second
 * word is not marked valid (low bit clear), the token is released.
 * Confidence: medium
 * Notes: FUN_0066b878/FUN_0066ad54/FUN_0066bce0/FUN_006860f4; low-bit validity flag. */
unsigned long sk_f_006662ac(long *obj, unsigned long a, unsigned long b)
{
    obj[4] = 0;
    obj[1] = 0;
    obj[0] = 0;
    obj[3] = 0;
    obj[2] = 0;
    sk_x_0066b878();
    if (obj[0] == 0) {
        unsigned long tok = sk_f_0066ad54();
        long w0, w1, w2, w3, w4;
        sk_x_0066bce0(&w0, a, b, tok);
        obj[1] = w1;
        obj[0] = w0;
        obj[3] = w3;
        obj[2] = w2;
        obj[4] = w4;
        if ((obj[0] == 0) || ((*(unsigned char *)(obj + 1) & 1) == 0)) {
            sk_x_006860f4(tok);
        }
    }
    return 0;
}

/* FUN_00666344 @ 0x00666344   (est. region_lookup_twostage)
 * Ghidra: uint8_t  [16] FUN_00666344(long param_1,long *param_2)
 * Two-stage keyed lookup against an object `obj` (a vtable/interface pointer).
 * Clears a 17-word out structure, records the object, and via vtable slots
 * +0x10 (query), +0x18 (bind/set), +0x20 (release) tries a primary binding at
 * out[1] and, if that succeeds, a secondary binding at out[6]. Returns a
 * status word (error code in .lo, .hi always 0): 0 on success, otherwise one
 * of 0x10a0007/0x1150002/0x11d0002. On secondary failure the primary is
 * released.
 * Confidence: medium
 * Notes: DAT_0068a578/DAT_0068a57c (slot keys); returns (sk_u128_t){.lo=err,.hi=0}. */
sk_u128_t sk_f_00666344(unsigned long obj, long *out)
{
    unsigned long err = 0x10a0007;
    if ((obj != 0) && (out != 0)) {
        out[0] = (long)obj;
        out[0xe] = 0;
        out[0xd] = 0;
        out[0x10] = 0;
        out[0xf] = 0;
        unsigned long k1 = sk_g_0068a578;
        ((void (*)(unsigned long, long *))*(unsigned long *)(obj + 0x10))(sk_g_0068a578, out + 1);
        if (out[1] == 0) {
            err = 0x1150002;
        } else {
            ((void (*)(long *, unsigned long))*(unsigned long *)(obj + 0x18))(out + 1, k1);
            unsigned long k2 = sk_g_0068a57c;
            ((void (*)(unsigned long, long *))*(unsigned long *)(obj + 0x10))(sk_g_0068a57c, out + 6);
            if (out[6] == 0) {
                ((void (*)(long *))*(unsigned long *)(obj + 0x20))(out + 1);
                err = 0x11d0002;
            } else {
                ((void (*)(long *, unsigned long))*(unsigned long *)(obj + 0x18))(out + 6, k2);
                err = 0;
                out[0xb] = 0;
                out[0xc] = 0;
            }
        }
    }
    return (sk_u128_t){ .lo = err, .hi = 0 };
}

/* FUN_00666448 @ 0x00666448   (est. page_pool_alloc_slot)
 * Ghidra: void FUN_00666448(uint64_t *param_1,long *param_2,uint64_t param_3,unsigned long param_4,int param_5)
 * Allocates a slot of `size` bytes from a frame/pool cache object `pool` and
 * binds it to `key`, reporting the result through the 3-word `out`
 * (out[0]=status, out[1]=0, out[2]=allocated node). Handles both a fresh
 * compression via sk_f_00667040 and reuse of a cached/available node with a
 * large enough remaining capacity. Overflow-checked throughout; any violated
 * bound or pool-consistency failure traps via SoftwareBreakpoint. On success
 * the node is recorded in the pool's 0x6c counter and 0x10 accounting.
 * Confidence: medium
 * Notes: sk_f_00667040 (compress), sk_x_0066bce0, sk_x_0067aa00 (range), DAT_0068a57c,
 *        SoftwareBreakpoint(0x5519,0x666714); pool vtable slots +0/8/0x10/0x18. */
unsigned long sk_f_00666448(unsigned long *out, long *pool, unsigned long key, unsigned long size, int flags)
{
    unsigned long err;
    unsigned long end, end2, sz, u1, u3, delta, u2;
    unsigned long *node, *list, *n3, *n4, *n2;
    unsigned int avail, idx;

    if ((pool == 0) || (size == 0)) {
        err = 0x12f0007;
    } else if (flags != 0) {
        err = 0x1350005;
    } else {
        if ((((size + 4 < size) ||
              (end = size + sk_g_0068a57c, end < size + 4)) ||
             ((sz = pool[6], sz != 0 &&
              ((sz + 4 < sz) || (sz + pool[7] < sz + 4))))) ||
            ((sz = pool[1], sz != 0 &&
             ((sz + 4 < sz) || (sz + pool[2] < sz + 4)))))
            goto hardfail;
        idx = (unsigned int)sk_f_00667040(size);
        if (idx == 0) {
            sz = 0;
            avail = 4;
        } else {
            if ((int)idx < 1) {
                err = 0x1510002;
                goto err_out;
            }
            size = pool[6];
            end = (size == 0) ? 0 : (size + pool[7]);
            sz = 0x400000000;
        }
        list = (unsigned long *)(pool + 0xc);
        for (node = (unsigned long *)*list; node != 0; node = (unsigned long *)node[10]) {
            if (idx <= (unsigned int)node[6]) {
                avail = 0x40000 - (unsigned int)node[6];
                goto have_node;
            }
        }
        node = (unsigned long *)((unsigned long (*)(void))*(unsigned long *)*pool)();
        if (node != 0) {
            if ((node + 0xc < node) || (node + 5 < node)) goto hardfail;
            ((void (*)(unsigned long, unsigned long *))*(unsigned long *)(*pool + 0x10))(0x40000, node);
            if (*node != 0) {
                u3 = sk_x_0066b870();
                node[5] = u3;
                u3 = sk_g_0068a3a0;
                n3 = (unsigned long *)(pool + 0xb);
                u1 = *n3;
                n4 = node + 8;
                *n4 = u1;
                node[6] = u3;
                *(unsigned char *)(node + 7) = 1;
                if (u1 != 0) {
                    if (node + 9 < n4) goto hardfail;
                    *(unsigned long **)(u1 + 0x48) = n4;
                }
                *n3 = (unsigned long)node;
                if (list < n3) goto hardfail;
                u3 = *list;
                n4 = node + 10;
                *n4 = u3;
                node[9] = (unsigned long)n3;
                if (u3 != 0) {
                    if (node + 0xb < n4) goto hardfail;
                    *(unsigned long **)(u3 + 0x58) = n4;
                }
                pool[0xc] = (long)node;
                n3 = (unsigned long *)(pool + 0xd);
                if (n3 < list) goto hardfail;
                avail = 0;
                node[0xb] = (unsigned long)list;
                *(int *)n3 = (int)*n3 + 1;
have_node:
                if (node + 0xc < node) goto hardfail;
                u3 = node[2];
                ((void (*)(unsigned long *, unsigned long))*(unsigned long *)(*pool + 0x18))(node, (unsigned long)avail + idx);
                pool[0xe] = (node[2] - u3) + pool[0xe];
                u3 = *node;
                u1 = (u3 == 0) ? 0 : (u3 + node[1]);
                if ((((end < size) ||
                      (delta = (unsigned long)idx, end - size < delta)) ||
                     (end = u3 + avail, end < u3)) ||
                    (((u1 < end) || (u1 - end < delta)) ||
                     (sk_x_0067aa00(end, size, delta), end + delta < end)))
                    goto hardfail;
                *(unsigned int *)(node + 6) = (int)node[6] - (int)idx;
                {
                    unsigned long w0 = 0, w1 = 0, w2 = 0, w3 = 0, w4 = 0;
                    sk_x_0066bce0(&w2, node[5], key,
                                  (unsigned long)(idx & 0x3fff) |
                                  (unsigned long)(avail & 0xfffff) << 0xe | sz);
                    if (w2 == 0) sk_x_0067cc18();
                    if ((w1 & 1) != 0) {
                        node[5] = w0;
                        *(int *)((long)pool + 0x6c) = *(int *)((long)pool + 0x6c) + 1;
                        pool[0x10] = pool[0x10] + (long)delta;
                        if ((unsigned int)node[6] < 0x118d) {
                            u3 = node[10];
                            n3 = (unsigned long *)node[0xb];
                            if (u3 != 0) *(unsigned long **)(u3 + 0x58) = n3;
                            *n3 = u3;
                            *(unsigned char *)(node + 7) = 0;
                        }
                        out[0] = 0;
                        out[1] = 0;
                        out[2] = (unsigned long)node;
                        return 0;
                    }
                    err = 0x1880001;
                    goto err_out;
                }
            }
            ((void (*)(unsigned long *))*(unsigned long *)(*pool + 8))(node);
        }
        out[2] = 0;
        err = 0x1610002;
        goto err_tail;
    }
err_out:
    out[2] = 0;
err_tail:
    out[0] = err;
    out[1] = 0;
    return 0;
hardfail:
    SoftwareBreakpoint(0x5519, 0x666714);
    return 0;
}

/* FUN_00666800 @ 0x00666800   (est. page_repack_thunk)
 * Ghidra: void FUN_00666800(void)
 * Thin entry point that immediately invokes sk_f_00666808 (the frame repack /
 * pool maintainer). The decompiler drops the forwarded arguments.
 * Confidence: high
 * Notes: FUN_00666808. */
unsigned long sk_f_00666800(void)
{
    sk_f_00666808();
    return 0;
}

/* FUN_00666d84 @ 0x00666d84   (est. page_repack_thunk2)
 * Ghidra: void FUN_00666d84(void)
 * Thin entry point that immediately invokes sk_f_00666808 (the frame repack /
 * pool maintainer). The decompiler drops the forwarded arguments.
 * Confidence: high
 * Notes: FUN_00666808. */
unsigned long sk_f_00666d84(void)
{
    sk_f_00666808();
    return 0;
}

/* FUN_00666808 @ 0x00666808   (est. frame_set_repack_page)
 * Ghidra: uint8_t  [16] FUN_00666808(long *param_1,unsigned long *param_2,uint64_t param_3,uint32_t *param_4,int param_5)
 * Repacks / resizes a frame or page object `pg` within its owner set `fs`,
 * updating the owner's accounting (frame count at +0x6c and 0xd, in-use bytes
 * at 0xe/0xf/0x10) and the pool's free-list (list head at fs[0xc], node links
 * at pg[8]/pg[10], busy flag at pg[7]). Depending on a 2-bit mode decoded from
 * the allocation record it either moves/copies a bounded region (via
 * sk_f_00666d90) or fills a secondary buffer, then attempts to free or compact
 * the page; a large freed area triggers a fresh sub-frame allocation through
 * the owner's vtable. Returns status in .lo (0 on success, otherwise an
 * 0x1a6xxxx/0x1b2xxxx/0x1cfxxxx code), .hi always 0. All bounds and pool-link
 * invariants are checked; violations trap via SoftwareBreakpoint.
 * Confidence: medium
 * Notes: sk_f_00666d90, sk_x_0066b878/0066bdf4/0066c084/0066c354/0066c5d0/0066c5f8/0066b870,
 *        sk_x_0067aa00; DAT_0068a57c/DAT_0068a580; returns lo only (hi==0). */
unsigned long sk_f_00666808(long *fs, unsigned long *pg, unsigned long tok, unsigned int *ext, int flag)
{
    unsigned long err;
    unsigned long offh, sz, u1, u2, u3, delta, u4, u5, base, b1, b2, b3, ctr;
    unsigned long *list, *n3, *n4, *n2;
    unsigned int low, mode, cap, cnt, rem;

    err = 0x1a60007;
    if ((fs != 0) && (pg != 0)) {
        if ((flag != 0) && (ext == 0)) {
            err = 0x1aa0007;
            goto done;
        }
        {
            unsigned long r0 = 0, r1 = 0, r2 = 0, r3 = 0, r4 = 0;
            sk_x_0066b878(&r0, pg[5], tok);
            err = r0;
            if (r0 == 0) {
                err = 0x1b20004;
                goto done;
            }
            pg[5] = r4;
            offh = r0 >> 0xe & 0xfffff;
            low = (unsigned int)r0 & 0x3fff;
            if (flag != 0) {
                mode = (unsigned int)(r0 >> 0x22) & 3;
                if (mode == 1) {
                    base = *pg;
                    u1 = (base == 0) ? 0 : (base + pg[1]);
                    u2 = base + offh;
                    if ((((u2 != 0) && (((u2 < base) || (u2 + 4 < u2)) || (u1 < u2 + 4))) ||
                         ((ext != 0 && ((ext + 1 < ext) ||
                          ((unsigned int *)((long)ext + (unsigned long)sk_g_0068a580) < ext + 1))))) ||
                        ((base = fs[1], base != 0 && ((base + 4 < base) || (base + fs[2] < base + 4)))))
                        goto hardfail;
                    sk_f_00666d90(u2, ext, (unsigned char *)base, (long)low);
                } else {
                    if (mode != 0) {
                        err = 0x1cf0007;
                        goto done;
                    }
                    unsigned int *src = (unsigned int *)*pg;
                    unsigned int *slim = (src == 0) ? 0 : (unsigned int *)((long)src + pg[1]);
                    unsigned int *s2 = (unsigned int *)((long)src + offh);
                    if (((s2 < src) || (s2 + 1 < s2)) || (slim < s2 + 1)) goto hardfail;
                    unsigned int *dst = 0;
                    if (ext != 0) dst = (unsigned int *)((long)ext + (unsigned long)sk_g_0068a580);
                    if (3 < sk_g_0068a57c) {
                        unsigned int val = *s2;
                        unsigned long n = (unsigned long)(sk_g_0068a57c >> 2);
                        unsigned int *p = ext;
                        do {
                            if (((p < ext) || (dst < p + 1)) || (p + 1 < p)) goto hardfail;
                            *p = val;
                            n = n - 1;
                            p = p + 1;
                        } while (n != 0);
                    }
                }
            }
            list = pg + 0xc;
            {
                unsigned long o0 = 0, o1 = 0, o2 = 0;
                sk_x_0066bdf4(&o0, pg[5], tok, 0);
                pg[5] = o2;
            }
            *(int *)((long)fs + 0x6c) = *(int *)((long)fs + 0x6c) + -1;
            if (sk_x_0066c5d0(pg[5]) == 0) {
                if (list < pg) goto hardfail;
                *(int *)(fs + 0xd) = (int)fs[0xd] + -1;
                u2 = pg[6];
                low = *(unsigned int *)((long)pg + 0x34);
                fs[0xe] = fs[0xe] - pg[2];
                fs[0xf] = fs[0xf] - (unsigned long)low;
                fs[0x10] = fs[0x10] - (unsigned long)(0x40000 - (low + (int)u2));
                if ((char)pg[7] == '\x01') {
                    u2 = pg[10];
                    n3 = (unsigned long *)pg[0xb];
                    if (u2 != 0) *(unsigned long **)(u2 + 0x58) = n3;
                    *n3 = u2;
                    *(unsigned char *)(pg + 7) = 0;
                }
                u2 = pg[8];
                n3 = (unsigned long *)pg[9];
                if (u2 != 0) *(unsigned long **)(u2 + 0x48) = n3;
                *n3 = u2;
                sk_x_0066c5f8(pg[5], 0);
                ((void (*)(unsigned long *))*(unsigned long *)(*fs + 0x20))(pg);
                ((void (*)(unsigned long *))*(unsigned long *)(*fs + 8))(pg);
            } else {
                cap = (unsigned int)pg[6];
                if ((int)offh + (int)low < 0x40000 - (int)cap) {
                    low = *(int *)((long)pg + 0x34) + low;
                    *(unsigned int *)((long)pg + 0x34) = low;
                    u2 = u2 & 0x3fff;
                    fs[0xf] = fs[0xf] + (long)u2;
                    fs[0x10] = fs[0x10] - (long)u2;
                    if (0xffff < low) {
                        if (list < pg) goto hardfail;
                        {
                            unsigned long w0 = 0, w1 = 0, w2 = 0, w3 = 0, w4 = 0;
                            ((void (*)(unsigned long, unsigned long *))*(unsigned long *)(*fs + 0x10))(0x40000, &w2);
                            if (w2 == 0) {
                                cap = (unsigned int)pg[6];
                            } else {
                                u2 = sk_x_0066b870();
                                unsigned long g0 = 0, g1 = 0, g2 = 0;
                                sk_x_0066c084(&g0, pg[5], 0);
                                delta = sk_x_0066c354(&g0);
                                if ((delta & 3) == 0) {
                                    cap = 0x40000;
                                } else {
                                    u3 = 0;
                                    do {
                                        u4 = delta >> 0x1c & 0x3fff;
                                        cap = (unsigned int)u4 + (unsigned int)u3;
                                        ((void (*)(unsigned long *, unsigned long))*(unsigned long *)(*fs + 0x18))(&w2, (unsigned long)cap);
                                        u1 = (w2 == 0) ? 0 : (w2 + w1);
                                        base = *pg;
                                        b1 = (base == 0) ? 0 : (base + pg[1]);
                                        u5 = w2 + u3;
                                        b2 = base + (delta >> 0x2a & 0xfffff);
                                        b3 = b1 - b2 < u4;
                                        if (((((((u5 < w2 || b2 < base) || b1 < b2) || b3) || u1 <= u5) &&
                                              ((((u5 < w2 || b2 < base) || b1 < b2) || b3) || u5 != u1)) ||
                                             u1 - u5 < u4) ||
                                            (sk_x_0067aa00(u5, b2, u4), u5 + u4 < u5))
                                            goto hardfail;
                                        {
                                            unsigned long h0 = 0, h1 = 0, h2 = 0, h3 = 0, h4 = 0;
                                            sk_x_0066bce0(&h2, u2, (unsigned int)delta >> 6 & 0x3fffff,
                                                          delta >> 0x1c & 0xc00000000 |
                                                          (unsigned long)((unsigned int)u3 & 0xfffff) << 0xe | u4);
                                        }
                                        u2 = w1;
                                        delta = sk_x_0066c354(&g0);
                                        u3 = (unsigned long)cap;
                                    } while ((delta & 3) != 0);
                                    cap = 0x40000 - cap;
                                }
                                delta = pg[2];
                                sk_x_0066c5f8(pg[5], 0);
                                ((void (*)(unsigned long *))*(unsigned long *)(*fs + 0x20))(pg);
                                pg[1] = w1;
                                pg[0] = w2;
                                pg[3] = w3;
                                pg[2] = w0;
                                pg[4] = w4;
                                pg[5] = u2;
                                u4 = fs[0xe];
                                u5 = fs[0xf];
                                low = *(unsigned int *)((long)pg + 0x34);
                                *(unsigned int *)(pg + 6) = cap;
                                *(unsigned int *)((long)pg + 0x34) = 0;
                                fs[0xe] = (u4 - delta) + w0;
                                fs[0xf] = u5 - (unsigned long)low;
                            }
                        }
                    }
                } else {
                    cap = cap + low;
                    *(unsigned int *)(pg + 6) = cap;
                    fs[0x10] = fs[0x10] - (u2 & 0x3fff);
                }
                if ((0x118c < cap) && ((pg[7] & 1) == 0)) {
                    n3 = (unsigned long *)(fs + 0xc);
                    u2 = *n3;
                    n4 = pg + 10;
                    *n4 = u2;
                    if (u2 != 0) {
                        if (pg + 0xb < n4) goto hardfail;
                        *(unsigned long **)(u2 + 0x58) = n4;
                    }
                    if (list < pg) goto hardfail;
                    *n3 = (unsigned long)pg;
                    pg[0xb] = (unsigned long)n3;
                    *(unsigned char *)(pg + 7) = 1;
                }
            }
            err = 0;
        }
    }
done:
    return err;
hardfail:
    SoftwareBreakpoint(0x5519, 0x666d20);
    return 0;
}

/* ===== part 4: local helpers for the bitmap codec functions =====
 * skr68p4_shl32: 128-bit vector left-shift by 32-bit lanes (approximates the
 *   Ghidra NEON_ushl(v, shiftvec, 4) emission; lane shift counts from the low
 *   5 bits of each 32-bit lane of the shift vector). Used only by the two
 *   bitmap codec bodies below.
 * skr68p4_zva: zeroes one 64-uint8_t cache line (DC ZVA), as emitted by the
 *   decompressor's 0x4321 path. */
static inline sk_u128_t skr68p4_shl32(sk_u128_t v, sk_u128_t s)
{
    unsigned int l0 = (unsigned int)v.lo, l1 = (unsigned int)(v.lo >> 32);
    unsigned int l2 = (unsigned int)v.hi, l3 = (unsigned int)(v.hi >> 32);
    unsigned int c0 = (unsigned int)s.lo, c1 = (unsigned int)(s.lo >> 32);
    unsigned int c2 = (unsigned int)s.hi, c3 = (unsigned int)(s.hi >> 32);
    sk_u128_t r;
    r.lo = (unsigned long)(l0 << (c0 & 31)) | ((unsigned long)(l1 << (c1 & 31)) << 32);
    r.hi = (unsigned long)(l2 << (c2 & 31)) | ((unsigned long)(l3 << (c3 & 31)) << 32);
    return r;
}
static inline void skr68p4_zva(void *p)
{
    unsigned long *w = (unsigned long *)p;
    int i;
    for (i = 0; i < 8; i++) w[i] = 0;
}

/* FUN_00666d90 @ 0x00666d90   (est. bitmap_page_decompress)
 * Ghidra: void FUN_00666d90(unsigned int *param_1,unsigned int *param_2,uint8_t *param_3,long param_4)
 * Decompresses / expands a bitmap page. If the source starts with the magic
 * 0x4321 (compressed form) it zeroes a 16 KiB destination then scatters each
 * (4-uint8_t value, 2-uint8_t offset) 6-uint8_t record at its offset. Otherwise it
 * runs the NEON bit-transpose path: a fixed shift+mask permutation turns the
 * source words into a uint8_t stream in the scratch buffer (using the global
 * 128-bit shift vectors and uint8_t masks), then an LZ-style decode loop (codes
 * 0/1/2/3+) with a 16-entry hash table rebuilds the destination unsigned int array.
 * Confidence: low
 * Notes: DAT_0068aa60/aa70..aa7c/aa80/aa88/aa90..aa9c/aaa0..aadc tables,
 *        DAT_0068a960 hash-class table, magic 0x4321, DC_ZVA, NEON_ushl. */
unsigned long sk_f_00666d90(unsigned int *src, unsigned int *dst, unsigned char *scratch, long len)
{
    unsigned int tbl[16];
    unsigned long lo, hi;
    int i;

    if (*src == 0x4321) {
        src = src + 1;
        {
            long n = 0x4000;
            unsigned int *zp = dst;
            do {
                skr68p4_zva(zp);
                skr68p4_zva(zp + 0x10);
                skr68p4_zva(zp + 0x20);
                skr68p4_zva(zp + 0x30);
                zp = zp + 0x40;
                n = n - 0x100;
            } while (n != 0);
        }
        {
            long m = 4;
            do {
                unsigned int *poff = src + 1;
                unsigned int val = *src;
                src = (unsigned int *)((long)src + 6);
                *(unsigned int *)((long)dst + (unsigned short)*poff) = val;
                m = m + 6;
            } while (m != len);
        }
        return 0;
    }

    for (i = 0; i < 16; i++) tbl[i] = 0;

    /* First SIMD pass: src[3..0x103) (1 KiB) -> 4 KiB of uint8_t stream at scratch. */
    {
        sk_u128_t shift = *(const sk_u128_t *)&sk_g_0068aa60;
        const unsigned char *mask = (const unsigned char *)&sk_g_0068aa70;
        unsigned char *outp = scratch;
        unsigned int *sp = src + 3;
        unsigned int *sp4;
        do {
            sp4 = sp + 4;
            unsigned int a = sp[0], b = sp[1], c = sp[2], d = sp[3];
            sk_u128_t va = { .lo = (unsigned long)a | ((unsigned long)a << 32),
                             .hi = (unsigned long)a | ((unsigned long)a << 32) };
            sk_u128_t vb = { .lo = (unsigned long)b | ((unsigned long)b << 32),
                             .hi = (unsigned long)b | ((unsigned long)b << 32) };
            sk_u128_t vc = { .lo = (unsigned long)c | ((unsigned long)c << 32),
                             .hi = (unsigned long)c | ((unsigned long)c << 32) };
            sk_u128_t vd = { .lo = (unsigned long)d | ((unsigned long)d << 32),
                             .hi = (unsigned long)d | ((unsigned long)d << 32) };
            va = skr68p4_shl32(va, shift);
            vb = skr68p4_shl32(vb, shift);
            vc = skr68p4_shl32(vc, shift);
            vd = skr68p4_shl32(vd, shift);
            {
                const unsigned char *pva = (const unsigned char *)&va;
                const unsigned char *pvb = (const unsigned char *)&vb;
                const unsigned char *pvc = (const unsigned char *)&vc;
                const unsigned char *pvd = (const unsigned char *)&vd;
                for (i = 0; i < 16; i++) {
                    outp[i]      = pva[i] & mask[i];
                    outp[i + 16] = pvb[i] & mask[i];
                    outp[i + 32] = pvc[i] & mask[i];
                    outp[i + 48] = pvd[i] & mask[i];
                }
            }
            outp = outp + 0x40;
            sp = sp4;
        } while (sp4 < src + 0x103);
    }

    /* Second pass: runs between the two recorded counts src[0] and src[1]. */
    {
        lo = (unsigned long)*src;
        hi = (unsigned long)src[1];
        unsigned int *pA = src + lo;
        unsigned int *pB = src + hi;
        if ((lo <= hi) && (hi - lo != 0)) {
            unsigned char *o8 = scratch + 0x1000;
            sk_u128_t sh2 = { .lo = sk_g_0068aa80, .hi = sk_g_0068aa88 };
            const unsigned char *mask2 = (const unsigned char *)&sk_g_0068aa90;
            int cnt = (int)(hi - lo);
            unsigned int n = (unsigned int)(cnt - 1);
            unsigned int *sp = pA;
            unsigned char *op = o8;
            int more;
            if ((cnt != 0) && (n != 0)) {
                do {
                    sp = sp + 2;
                    more = 1 < (int)n;
                    n = n - 2;
                    unsigned long v8 = *(unsigned long *)(sp - 2);
                    unsigned int u = (unsigned int)v8, t = (unsigned int)(v8 >> 32);
                    sk_u128_t v = { .lo = (unsigned long)u | ((unsigned long)u << 32),
                                    .hi = (unsigned long)t | ((unsigned long)t << 32) };
                    v = skr68p4_shl32(v, sh2);
                    {
                        const unsigned char *pv = (const unsigned char *)&v;
                        for (i = 0; i < 16; i++) op[i] = pv[i] & mask2[i];
                    }
                    op = op + 0x10;
                } while (more && (n != 0));
            }
            if (-1 < (int)n) {
                /* one leftover 8-uint8_t word: replicate + shift + mask */
                unsigned long v8 = (unsigned long)*sp;
                unsigned int u = (unsigned int)v8;
                sk_u128_t v = { .lo = (unsigned long)u | ((unsigned long)u << 32),
                                .hi = (unsigned long)u | ((unsigned long)u << 32) };
                v = skr68p4_shl32(v, sh2);
                {
                    const unsigned char *pv = (const unsigned char *)&v;
                    unsigned char mm[8] = { mask2[0], mask2[1], mask2[2], mask2[3],
                                            mask2[4], mask2[5], mask2[6], mask2[7] };
                    for (i = 0; i < 8; i++) o8[i] = pv[i] & mm[i];
                }
            }
        }
    }

    /* Third SIMD pass: tail at src[2], permuted into scratch+0x2000. */
    {
        sk_u128_t sh3 = *(const sk_u128_t *)&sk_g_0068aaa0;
        const unsigned char *mA = (const unsigned char *)&sk_g_0068aaa0;
        const unsigned char *mB = (const unsigned char *)&sk_g_0068aac0;
        long rem = (long)(src + src[2]) - (long)(src + hi);
        unsigned int *sp = src + hi;
        if ((src + hi <= src + src[2]) && (rem != 0)) {
            unsigned char *o9 = scratch + 0x2000;
            /* first element: shift with two mask tables (mB low half, mA high half) */
            {
                sk_u128_t v = { .lo = (unsigned long)*sp | ((unsigned long)*sp << 32),
                                .hi = (unsigned long)*sp | ((unsigned long)*sp << 32) };
                sk_u128_t shA = { .lo = mA[4] | ((unsigned long)mA[5] << 8) |
                                          ((unsigned long)mA[6] << 16) | ((unsigned long)mA[7] << 24),
                                  .hi = 0 };
                sk_u128_t r1 = skr68p4_shl32(v, sh3);
                sk_u128_t r2 = skr68p4_shl32(v, shA);
                const unsigned char *p1 = (const unsigned char *)&r1;
                const unsigned char *p2 = (const unsigned char *)&r2;
                for (i = 0; i < 8; i++) {
                    o9[i] = (p2[i] & mA[i]) | (p1[i] & mB[i]);
                }
            }
            sp = sp + 1;
            if (rem != 4) {
                unsigned char *op = o9 + 8;
                unsigned long left = rem - 0xc;
                if (7 < rem - 4) {
                    int more;
                    unsigned long nn;
                    do {
                        unsigned long v8 = *(unsigned long *)sp;
                        unsigned int u = (unsigned int)v8, t = (unsigned int)(v8 >> 32);
                        sk_u128_t v = { .lo = (unsigned long)u | ((unsigned long)u << 32),
                                        .hi = (unsigned long)t | ((unsigned long)t << 32) };
                        sk_u128_t r1 = skr68p4_shl32(v, sh3);
                        sk_u128_t shA = { .lo = (unsigned long)mA[4] |
                                                 ((unsigned long)mA[5] << 8) |
                                                 ((unsigned long)mA[6] << 16) |
                                                 ((unsigned long)mA[7] << 24),
                                          .hi = 0 };
                        sk_u128_t r2 = skr68p4_shl32(v, shA);
                        const unsigned char *p1 = (const unsigned char *)&r1;
                        const unsigned char *p2 = (const unsigned char *)&r2;
                        for (i = 0; i < 12; i++) {
                            op[i] = (p2[i] & mA[i]) | (p1[i] & mB[i]);
                        }
                        nn = left - 8;
                        more = 7 < (long)left;
                        op = op + 12;
                        left = nn;
                        sp = sp + 2;
                    } while (more);
                    if ((nn & 4) == 0) goto skip_tail8;
                }
                {
                    unsigned long v8 = (unsigned long)*sp;
                    unsigned int u = (unsigned int)v8;
                    sk_u128_t v = { .lo = (unsigned long)u | ((unsigned long)u << 32),
                                    .hi = (unsigned long)u | ((unsigned long)u << 32) };
                    sk_u128_t r1 = skr68p4_shl32(v, sh3);
                    sk_u128_t shA = { .lo = (unsigned long)mA[4] |
                                             ((unsigned long)mA[5] << 8) |
                                             ((unsigned long)mA[6] << 16) |
                                             ((unsigned long)mA[7] << 24),
                                      .hi = 0 };
                    sk_u128_t r2 = skr68p4_shl32(v, shA);
                    const unsigned char *p1 = (const unsigned char *)&r1;
                    const unsigned char *p2 = (const unsigned char *)&r2;
                    for (i = 0; i < 8; i++) {
                        o9[8 + i] = (p2[i] & mA[i]) | (p1[i] & mB[i]);
                    }
                }
            }
        }
    }
skip_tail8:

    /* Final decode loop: LZ-style uint8_t codes over the scratch streams. */
    {
        long n = 0x1000;
        unsigned char *bp = scratch + 0x1000;
        unsigned int *sp2 = src + 0x103;
        unsigned short *tp = (unsigned short *)(scratch + 0x2000);
        const unsigned char *tab = (const unsigned char *)&sk_g_0068a960;
        unsigned char code;
        do {
            while (1) {
                while (1) {
                    while (1) {
                        unsigned char *p1 = scratch + 1;
                        code = *scratch;
                        scratch = p1;
                        if (code != 0) break;
                        *dst = 0;
                        {
                            int done = (n == 0);
                            n = n - 1;
                            dst = dst + 1;
                            if (done || n == 0) return 0;
                        }
                    }
                    if (code != 2) break;
                    {
                        unsigned int val = *sp2;
                        *dst = val;
                        tbl[(unsigned char)tab[(val >> 10) & 0xff]] = val;
                        {
                            long m = n - 1;
                            int done = n < 1;
                            dst = dst + 1;
                            n = m;
                            sp2 = sp2 + 1;
                            if (m == 0 || done) return 0;
                        }
                    }
                }
                if (code < 3) break;
                {
                    unsigned int val = tbl[*bp];
                    long m = n - 1;
                    int done = n < 1;
                    *dst = val;
                    dst = dst + 1;
                    n = m;
                    bp = bp + 1;
                    if (m == 0 || done) return 0;
                }
            }
            {
                unsigned int val = tbl[*bp] & 0xfffffc00 | (unsigned int)*tp & 0x3ff;
                long m = n - 1;
                int done = 0 < n;
                tbl[*bp] = val;
                *dst = val;
                dst = dst + 1;
                n = m;
                bp = bp + 1;
                tp = tp + 1;
                if (!(m != 0 && done)) return 0;
            }
        } while (1);
    }
}

/* FUN_00667040 @ 0x00667040   (est. bitmap_page_compress)
 * Ghidra: unsigned long FUN_00667040(unsigned int *param_1,unsigned int *param_2,char *param_3,long param_4)
 * Compresses a bitmap page `src` into the output area `out` using a scratch
 * buffer `scratch`, honoring a maximum output budget `budget`. Produces either
 * the compact form (header word 0x4321 followed by 6-uint8_t (value, offset)
 * records for every non-zero 64-bit source word) or a packed encoding whose
 * first words are the three header words (out[0] length marker / magic,
 * out[1] and out[2] table offsets). Uses a 256-entry class table and a 16-entry
 * hash to code each source word as one of four uint8_t codes. Returns the encoded
 * length on success, 0 for degenerate single-record inputs, and -1 on any
 * budget-overrun or overflow (0xffffffffffffffff).
 * Confidence: low
 * Notes: DAT_0068a960 class table, magic 0x4321, local_40 hash, CONCAT bit-repack;
 *        block size 0x4000, record stride 6 bytes. */
unsigned long sk_f_00667040(unsigned int *src, unsigned int *out, char *scratch, long budget)
{
    unsigned int tbl[16];
    const unsigned char *tab = (const unsigned char *)&sk_g_0068a960;
    unsigned int *outend = out + 0x103;
    unsigned short *tp = (unsigned short *)(scratch + 0x2000);
    unsigned long *cstream = (unsigned long *)(scratch + 0x1000);
    int i;

    for (i = 0; i < 16; i++) tbl[i] = 0;

    {
        unsigned int *sp = src;
        char *pc = scratch;
        unsigned int *op17 = outend;
        unsigned long *c22 = cstream;
        unsigned short *tpw = tp;
        long budget2 = budget - 0x40c;
        long space = 0x1a0;
        int seen = 0;

        do {
            char *pcur = pc;
            unsigned int *nsp = sp + 1;
            unsigned int val = *sp;
            sp = nsp;
            if (val == 0) {
                *pcur = 0;
                {
                    long m = space - 1;
                    int more = 0 < space;
                    pc = pcur + 1;
                    space = m;
                    if ((m != 0) && more) continue;
                }
            } else {
                unsigned char cls = tab[(val >> 10) & 0xff];
                unsigned int r = tbl[cls] ^ val;
                if (r == 0) {
                    *pcur = 3;
                    {
                        unsigned long *cn = c22 + 1;
                        *(unsigned char *)c22 = (unsigned char)(cls >> 2);
                        long m = space - 1;
                        int more = 0 < space;
                        pc = pcur + 1;
                        space = m;
                        c22 = cn;
                        if ((m != 0) && more) continue;
                    }
                } else if ((r >> 10) == 0) {
                    *pcur = 1;
                    tbl[cls] = val;
                    {
                        unsigned long *cn = c22 + 1;
                        *(unsigned char *)c22 = (unsigned char)(cls >> 2);
                        unsigned short *tn = tpw + 1;
                        *tpw = (unsigned short)val & 0x3ff;
                        long m = space - 1;
                        int more = 0 < space;
                        pc = pcur + 1;
                        space = m;
                        c22 = cn;
                        tpw = tn;
                        if ((m != 0) && more) continue;
                    }
                } else {
                    {
                        long m = budget2 - 4;
                        if ((m == 0) || (budget2 < 4)) return 0xffffffffffffffffULL;
                        *op17 = val;
                        tbl[cls] = val;
                        *pcur = 2;
                        unsigned int *on = op17 + 1;
                        long m2 = space - 1;
                        int more = 0 < space;
                        budget2 = m;
                        pc = pcur + 1;
                        space = m2;
                        op17 = on;
                        if ((m2 != 0) && more) continue;
                    }
                }
            }
            if (seen) {
                if ((outend == op17) && (cstream == c22)) return 0;
                {
                    unsigned long wc = (unsigned long)((long)op17 - (long)outend) >> 2;
                    long ds = (long)c22 - (long)cstream;
                    unsigned long sc = (unsigned long)((long)tpw - (long)tp) >> 1;
                    if ((((sc != 0) || (ds != 0xfff)) || (*scratch != '\x02')) &&
                        (((sc != 1) || (ds != 0x1000)) || (*scratch != '\x01'))) {
                        unsigned long enc = (wc + ds) * 6 + 4;
                        if ((long)enc <= (long)((long)op17 +
                              ((unsigned long)((long)c22 - (long)cstream) >> 1) +
                              (((unsigned long)(((long)tpw - (long)tp) * 0x555) >> 0xb) -
                               (long)outend) + 0x40c)) {
                            if (budget < (long)enc) return 0xffffffffffffffffULL;
                            {
                                unsigned int *ro = out + 1;
                                *out = 0x4321;
                                long k = 0;
                                do {
                                    unsigned long w = *(unsigned long *)((long)src + k);
                                    if (w != 0) {
                                        if ((unsigned int)w != 0) {
                                            unsigned int *on = ro + 1;
                                            *ro = (unsigned int)w;
                                            ro = (unsigned int *)((long)ro + 6);
                                            *(short *)on = (short)k;
                                        }
                                        {
                                            unsigned int hi = (unsigned int)((unsigned long)w >> 0x20);
                                            if (hi != 0) {
                                                unsigned int *on = ro + 1;
                                                *ro = hi;
                                                ro = (unsigned int *)((long)ro + 6);
                                                *(short *)on = (short)k + 4;
                                            }
                                        }
                                    }
                                    k = k + 8;
                                } while (k != 0x4000);
                            }
                            return enc;
                        }
                        *out = (unsigned int)((unsigned long)((long)op17 - (long)out) >> 2) & 0x3fffffff;
                        {
                            unsigned int *op18 = out + 3;
                            unsigned long nz;
                            unsigned long *zlim;
                            char *rd = scratch;
                            do {
                                unsigned int u5 = *(unsigned int *)rd;
                                unsigned int u6 = *(unsigned int *)(rd + 4);
                                unsigned long l30 = *(unsigned long *)(rd + 8) << 4;
                                unsigned int u7 = *(unsigned int *)(rd + 0x10);
                                unsigned int u8 = *(unsigned int *)(rd + 0x14);
                                unsigned long l34 = *(unsigned long *)(rd + 0x18) << 4;
                                rd = rd + 0x20;
                                unsigned char b32 = (unsigned char)(u5 >> 0x18) | (unsigned char)(l30 >> 0x18);
                                unsigned char b33 = (unsigned char)(u7 >> 0x18) | (unsigned char)(l34 >> 0x18);
                                unsigned long u9 = ((unsigned long)b32 << 32) |
                                                  (unsigned long)(u6 | (unsigned int)(l30 >> 32));
                                u9 = u9 >> 6;
                                unsigned long u10 = ((unsigned long)b33 << 32) |
                                                    (unsigned long)(u8 | (unsigned int)(l34 >> 32));
                                u10 = u10 >> 6;
                                unsigned int o0 = (u5 | (unsigned int)l30 | (unsigned int)u9) & 0xffffff;
                                o0 |= ((unsigned int)(b32 | (unsigned int)((u9 >> 24) & 0xff))) << 24;
                                unsigned int o1 = (u7 | (unsigned int)l34 | (unsigned int)u10) & 0xffffff;
                                o1 |= ((unsigned int)(b33 | (unsigned int)((u10 >> 24) & 0xff))) << 24;
                                *op18 = o0;
                                op18[1] = o1;
                                op18 = op18 + 2;
                            } while (rd < pcur + 1);
                            nz = (unsigned long)((((long)c22 - (long)cstream) + 7) >> 3);
                            zlim = cstream + nz;
                            if (budget2 < (long)(nz * 4)) return 0xffffffffffffffffULL;
                            if (c22 < zlim) {
                                unsigned long *zz = c22;
                                unsigned long gap = (long)zlim - (long)c22;
                                if ((gap & 4) != 0) {
                                    zz = (unsigned long *)((long)c22 + 4);
                                    *(unsigned int *)c22 = 0;
                                }
                                c22 = zz;
                                if ((gap & 2) != 0) {
                                    c22 = (unsigned long *)((long)zz + 2);
                                    *(unsigned short *)zz = 0;
                                }
                                if ((gap & 1) != 0) {
                                    *(unsigned char *)c22 = 0;
                                }
                            }
                            {
                                unsigned int hdr = *out;
                                op18 = op17;
                                if (cstream < zlim) {
                                    unsigned long *cn;
                                    do {
                                        cn = cstream + 1;
                                        op18 = op17 + 1;
                                        *op17 = (unsigned int)*cstream | (unsigned int)(*cstream >> 0x1c);
                                        op17 = op18;
                                        cstream = cn;
                                    } while (cn < zlim);
                                    hdr = (unsigned int)(((long)op18 - (long)out) >> 2);
                                }
                                out[1] = hdr;
                            }
                            {
                                int idx = (int)((unsigned long)((long)tpw - (long)(scratch + 0x2000)) >> 1);
                                budget2 = budget2 + (long)nz * -4;
                                unsigned long *cr = (unsigned long *)(scratch + 0x2000);
                                while (1) {
                                    int left = idx < 3;
                                    idx = idx - 3;
                                    if (left) {
                                        op17 = op18;
                                        if (idx != -3) {
                                            if (budget2 < 5) return 0xffffffffffffffffULL;
                                            unsigned int v = (unsigned int)(unsigned short)*cr;
                                            if (idx != -2) {
                                                v = v | (unsigned int)*(unsigned short *)((long)cr + 2) << 10;
                                            }
                                            op17 = op18 + 1;
                                            *op18 = v;
                                        }
                                        {
                                            unsigned int cnt = (unsigned int)((unsigned long)((long)op17 - (long)out) >> 2);
                                            out[2] = cnt & 0x3fffffff;
                                            return (unsigned long)(cnt << 2);
                                        }
                                    }
                                    if ((budget2 + -4 == 0) || (budget2 < 4)) break;
                                    {
                                        unsigned long w = *cr;
                                        *op18 = (unsigned int)((w & 0xffffffff00000000 |
                                                                (w & 0x3ff0000 | (w & 0x3ff) << 6) << 6) >> 0xc);
                                        budget2 = budget2 - 4;
                                        cr = (unsigned long *)((long)cr + 6);
                                        op18 = op18 + 1;
                                    }
                                }
                                return 0xffffffffffffffffULL;
                            }
                        }
                    }
                    return 0;
                }
            }
            seen = 1;
            space = 0xe60;
            pc = pcur + 1;
            if (0x640 < (long)((long)op17 +
                  ((unsigned long)((long)c22 - (long)cstream) >> 1) +
                  (((unsigned long)(((long)tpw - (long)tp) * 0x555) >> 0xb) - (long)outend))) {
                return 0xffffffffffffffffULL;
            }
        } while (1);
    }
}

/* FUN_006673ec @ 0x006673ec   (est. obj_irqstate_init)
 * Ghidra: uint64_t * FUN_006673ec(uint64_t *param_1)
 * Initialises an interrupt/queue state object at `obj`: sets a type/version
 * field at obj[0xb] (0x2001), an IRQ priority at +0x5a (0x20) and a mask at
 * +0x5c (0x7e), clears the first five words, wires the object's internal
 * list/array pointers (obj[1] to obj+0xb, obj[5] to obj+9, obj[6] to obj+0xf),
 * records a code pointer obj[8] = 0x2007e, and zeroes a 16-uint8_t (two-word)
 * work area at obj+9. Returns the object pointer.
 * Confidence: medium
 * Notes: &DAT_0002007e -> &sk_g_0002007e; FUN_0067a7f0 (memset). */
unsigned long sk_f_006673ec(unsigned long *obj)
{
    *(unsigned short *)(obj + 0xb) = 0x2001;
    *(unsigned char *)((long)obj + 0x5a) = 0x20;
    *(unsigned short *)((long)obj + 0x5c) = 0x7e;
    obj[0] = 0;
    obj[1] = (unsigned long)(obj + 0xb);
    obj[2] = 0;
    obj[3] = 0;
    obj[4] = 0;
    obj[5] = (unsigned long)(obj + 9);
    obj[6] = (unsigned long)(obj + 0xf);
    obj[7] = 0;
    obj[8] = (unsigned long)&sk_g_0002007e;
    sk_x_0067a7f0(obj + 9, 0, 0x10);
    return (unsigned long)obj;
}
/* ===== part 5: fragment of SKR68 ===== */
/* Recreated from the cL4 Secure Kernel (GL1) — slice SKR68. Ground truth:
 * Ghidra FUN_ names + addresses. All names are estimates unless header-matched. */

/* FUN_0066745c @ 0x0066745c   (est. sk_buffer_desc_init)
 * Ghidra: uint64_t * FUN_0066745c(uint64_t *param_1,unsigned long param_2)
 * Initializes a frame-buffer descriptor block at `desc` that points into the
 * 16K-aligned memory region at `region`. It stamps three magic fields into the
 * region header (0x2001 type, 0x20 level, 0x1fe slot count), zero-fills the
 * tail, and fills the descriptor fields (head/tail pointers, region base,
 * buffer base, count, limit). Requires `region` to be 16K aligned, else panics.
 * Returns the descriptor on success.
 * Confidence: medium
 * Notes: panics via sk_x_006833d4(0x6a8669); SoftwareBreakpoint(0x5519,0x6674fc)
 *   on an out-of-bounds descriptor layout. */
uint64_t * sk_f_0066745c(uint64_t * desc, uint64_t region)
{
	uint64_t * tail;

	if ((region & 0x3fff) != 0) {
		sk_x_006833d4(0x6a8669);   /* panic: region not 16K aligned */
	}
	tail = desc + 9;
	*(uint16_t *)(region + 0x20) = 0x2001;
	*(uint8_t *)(region + 0x22) = 0x20;
	*(uint16_t *)(region + 0x24) = 0x1fe;
	sk_x_0067a7f0(tail, 0, 0x40);
	if (desc <= tail) {
		desc[0] = 0;
		desc[1] = (uint64_t)(region + 0x20);
		desc[2] = 0;
		desc[3] = region;
		desc[4] = region + 0x18;
		desc[5] = (uint64_t)tail;
		desc[6] = region + 0x40;
		desc[7] = 0;
		desc[8] = 0x801fe;
		return desc;
	}
	SoftwareBreakpoint(0x5519, 0x6674fc);
	return desc;
}

/* FUN_00667530 @ 0x00667530   (est. sk_buffer_desc_validate)
 * Ghidra: void FUN_00667530(long param_1,long *param_2)
 * Validates a buffer descriptor at `buf`: if its 16-bit type word at +0x40 is
 * 0x1fe (frame region), stores the descriptor pointer into *out and confirms
 * the +0x18 uint8_t count does not overflow when extended by 0x4000. Any other
 * type faults through sk_x_00685b50. Traps on the overflow/type check failing.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x667568) on failure. */
void sk_f_00667530(long buf, long * out)
{
	if (*(short *)(buf + 0x40) == 0x1fe) {
		*out = buf;
		if (*(unsigned long *)(buf + 0x18) <= *(unsigned long *)(buf + 0x18) + 0x4000) {
			return;
		}
	} else {
		sk_x_00685b50();
	}
	SoftwareBreakpoint(0x5519, 0x667568);
}

/* FUN_00667568 @ 0x00667568   (est. sk_buffer_is_frame_region)
 * Ghidra: bool FUN_00667568(long param_1)
 * Returns true when the 16-bit type word at offset +0x40 of the descriptor is
 * 0x1fe (a frame/slot region). Pure predicate; no side effects.
 * Confidence: high
 * Notes: trivial field test. */
bool sk_f_00667568(long buf)
{
	return *(short *)(buf + 0x40) == 0x1fe;
}

/* FUN_00667578 @ 0x00667578   (est. sk_buffer_is_msg_region)
 * Ghidra: bool FUN_00667578(long param_1)
 * Returns true when the 16-bit type word at offset +0x40 of the descriptor is
 * 0x7e (a message region). Pure predicate; no side effects.
 * Confidence: high
 * Notes: trivial field test. */
bool sk_f_00667578(long buf)
{
	return *(short *)(buf + 0x40) == 0x7e;
}

/* FUN_00667588 @ 0x00667588   (est. sk_buffer_alloc_slot)
 * Ghidra: unsigned long FUN_00667588(long param_1)
 * Allocates a 0x20-uint8_t slot out of the frame-buffer pool managed by the
 * container `self`. Walks the pool list at self+0x148, growing it with a new
 * node (sk_f_00669298) as needed and draining a per-container release list
 * (sk_f_00667870). Tracks slot usage with a 64-entry bitmap per node; returns
 * the address of the allocated slot. Type bit (self+9 & 1) selects which
 * allocator fills a fresh node. Panics on lock/refcount or bitmap errors.
 * Confidence: low
 * Notes: register-return (extraout x8/x9/x10) from sk_x_00685b88 is modelled
 *   as a single result; bitmap/bit-scan logic; many panic codes
 *   (0x6a8797, 0x6a885a). */
uint64_t sk_f_00667588(long self)
{
	uint64_t lock_addr = self + 0x40;
	if (lock_addr <= self + 0x50U) {
		uint8_t type_byte = *(uint8_t *)(self + 9);
		int rc = sk_x_0067cffc(lock_addr);
		if (rc != 0) {
			sk_x_006833d4(0x6a8797);
		}
		uint64_t node = *(uint64_t *)(self + 0x138);
		int64_t pending;
		if (node == 0) {
			pending = 0;
			do {
				if (pending == 0) {
					rc = sk_x_0067d02c(lock_addr);
					if (rc != 0) {
						sk_x_006833d4(0x6a8797);
					}
					if ((type_byte & 1) == 0) {
						pending = sk_f_00669c3c();
					} else {
						pending = sk_f_00669cfc();
					}
					rc = sk_x_0067cffc(lock_addr);
					if (rc != 0) {
						sk_x_006833d4(0x6a8797);
					}
				} else {
					sk_f_00667870(self, (uint64_t *)pending);
					pending = 0;
				}
				node = *(uint64_t *)(self + 0x138);
			} while (node == 0);
		} else {
			pending = 0;
		}
		uint64_t slot_base = node + 0x48;
		uint16_t * count_ptr = (uint16_t *)(*(long *)(node + 8) + 6);
		uint16_t used_count = *count_ptr;
		uint64_t result = (uint64_t)used_count;
		uint16_t slot_capacity = *(uint16_t *)(node + 0x40);
		uint64_t nwords, bitmap_word, bitmask;
		uint64_t * bitmap_ptr = (uint64_t *)0;
		if ((uint32_t)used_count < (uint32_t)slot_capacity) {
			uint32_t new_count = used_count + 1;
			*count_ptr = (uint16_t)new_count;
			if (new_count == slot_capacity) {
				if (slot_base < node) goto LAB_006677d4;
				sk_f_00667d74(self, node);
			}
			slot_base = *(uint64_t *)(node + 0x30);
			result = slot_base + result * 0x20;
		} else {
			nwords = (uint64_t)*(uint8_t *)(node + 0x42);
			if (nwords != 0) {
				result = 0;
				bitmap_ptr = *(uint64_t **)(node + 0x28);
				do {
					bitmap_word = *bitmap_ptr;
					if (bitmap_word != 0) goto LAB_006676b4;
					result = result - 0x800;
					bitmap_ptr = bitmap_ptr + 1;
				} while (nwords * 0x800 + result != 0);
			}
			/* sk_x_00685b88 frees a bitmap word; Ghidra reads x8/x9/x10 extraouts */
			slot_base = sk_x_00685b88((uint8_t *)(node + 0x42), node);
			bitmap_word = slot_base;
LAB_006676b4:
			nwords = 0;
			do {
				if ((bitmap_word >> (nwords & 0x3f) & 1) != 0) break;
				nwords = nwords + 1;
			} while (nwords != 0x40);
			bitmask = 1ULL << (nwords & 0x3f);
			if ((bitmask & bitmap_word) == 0) {
				sk_x_006833d4(0x6a885a);
			}
			bitmap_word = bitmap_word & (bitmask ^ 0xffffffffffffffff);
			*bitmap_ptr = bitmap_word;
			if (bitmap_word == 0) {
				if (slot_base < node) goto LAB_006677d4;
				sk_f_00667d74(self, node);
			}
			slot_base = *(uint64_t *)(node + 0x30);
			result = (slot_base + nwords * 0x20) - result;
		}
		if ((result == 0) ||
		    ((slot_base <= result && result <= result + 0x20) &&
		     result + 0x20 <= slot_base + (uint64_t)*(uint16_t *)(node + 0x40) * 0x20)) {
			rc = sk_x_0067d02c(lock_addr);
			if (rc == 0) {
				if (pending != 0) {
					if ((type_byte & 1) == 0) {
						sk_f_00669c98();
					} else {
						sk_f_0066a08c(pending);
					}
				}
				return result;
			}
			sk_x_006833d4(0x6a8797);
		}
	}
LAB_006677d4:
	SoftwareBreakpoint(0x5519, 0x6677d8);
	return 0;
}

/* FUN_00667870 @ 0x00667870   (est. sk_buffer_attach_item)
 * Ghidra: void FUN_00667870(long param_1,uint64_t *param_2)
 * Attaches the item descriptor `item` into the frame-buffer pool of `self`,
 * placing it in a free slot of a pool node (growing the node list via
 * sk_f_00669298 and draining the per-container pending list). Sets the item
 * flag at +0x43, threads it into the container's +0x140 tail list, and walks a
 * second "tx descriptor" list to enqueue the item's work buffer. Involves
 * several lock/unlock transitions (sk_x_0067d02c/sk_x_0067cffc) and a flush
 * callback (sk_f_0066834c) when self+0x1d1 is set. Complex multi-list enqueue.
 * Confidence: low
 * Notes: many panic codes (0x6a8797, 0x6a8ea8); SoftwareBreakpoint
 *   (0x5519,0x667b9c); allocators sk_f_00669298/sk_f_0066924c. */
void sk_f_00667870(long self, uint64_t * item)
{
	uint64_t * head = (uint64_t *)(self + 0x148);
	bool have_new_node = false;
	int64_t slot = 0;
	uint64_t work = 0;
	uint64_t * cur = (uint64_t *)0;
	uint64_t * tail_ptr = (uint64_t *)0, * walk = (uint64_t *)0, * walk_prev = (uint64_t *)0;
	if (head <= (uint64_t *)(self + 0x1c8)) {
		if (*(long *)(self + 0x138) != 0) {
			sk_x_00685c2c();
LAB_00667ba0:
			sk_x_00685cd8();
LAB_00667ba4:
			sk_x_006833d4(0x6a8797);
		}
		have_new_node = false;
		slot = 0;
		work = 0;
		cur = head;
		do {
			if (cur == (uint64_t *)0x0) {
				if (have_new_node) {
LAB_00667d50:
					sk_x_00685d4c();
LAB_00667d54:
					sk_x_006833d4(0x6a8ea8);
				}
				int rc = sk_x_0067d02c(self + 0x40);
				if (rc != 0) goto LAB_00667ce4;
				cur = (uint64_t *)sk_f_00669298();
				if (cur == (uint64_t *)0x0) {
					sk_x_00685d10();
					goto LAB_00667d50;
				}
				for (int k = 0; k < 16; k++) {
					cur[k] = 0;
				}
				rc = sk_x_0067cffc(self + 0x40);
				if (rc != 0) {
					sk_x_006833d4(0x6a8797);
				}
				uint64_t * tail_ptr = head;
				if ((uint64_t *)(self + 0x150) < head) break;
				while ((walk = (uint64_t *)*tail_ptr) != (uint64_t *)0x0) {
					tail_ptr = walk;
					if (walk + 1 < walk) goto LAB_00667b98;
				}
				*cur = 0;
				*tail_ptr = (uint64_t)cur;
				have_new_node = true;
			}
			int64_t off = 0;
			int64_t prev = slot;
			do {
				uint64_t * lo = (uint64_t *)((long)cur + off + 0x48);
				uint64_t * hi = (uint64_t *)((long)cur + off + 0x50);
				if (cur + 0x10 < hi || hi < lo) goto LAB_00667b98;
				slot = (int64_t)*lo;
				if (slot == 0) {
					char depth;
					if (prev == 0) {
						if (2 < *(uint8_t *)(self + 0xf8)) goto LAB_00667d54;
						depth = '\0';
						slot = item[1];
						*(uint8_t *)(slot + 0x10) = *(uint8_t *)(self + 0xf8);
						*(uint64_t *)(slot + 8) = *(uint64_t *)(self + 0x20);
					} else {
						if (work < prev + 0x48U) goto LAB_00667b98;
						prev = *(long *)(prev + 8);
						slot = item[1];
						*(uint64_t *)(slot + 8) = *(uint64_t *)(prev + 8);
						*(uint8_t *)(slot + 0x10) = *(uint8_t *)(prev + 0x10);
						depth = *(char *)(prev + 0x11) + '\x01';
					}
					*(char *)(slot + 0x11) = depth;
					*(uint64_t **)((long)cur + off + 0x48) = item;
					head = (uint64_t *)((long)cur + off + 0x10);
					if ((cur + 8 < head) ||
					    (cur = (uint64_t *)((long)cur + off + 8), head < cur))
						goto LAB_00667b98;
					*cur = item[6];
					if (*(char *)((long)item + 0x43) == '\x01') goto LAB_00667ba0;
					item[7] = 0;
					**(uint64_t **)(self + 0x140) = (uint64_t)item;
					*(uint64_t **)(self + 0x140) = item + 7;
					*(uint8_t *)((long)item + 0x43) = 1;
					if (*(char *)(self + 0x1d1) == '\x01') {
						sk_f_0066834c(self);
					}
					int rc = sk_x_0067d02c(self + 0x40);
					if (rc != 0) goto LAB_00667ba4;
					slot = sk_x_0065be08(0x6fe8d0, 4, 10);
					work = slot + 0xb0;
					if (slot + 0xc0U < work) goto LAB_00667b98;
					rc = sk_x_0067cffc(work);
					if (rc != 0) {
						sk_x_006833d4(0x6a8797);
					}
					have_new_node = false;
					head = *(uint64_t **)(slot + 0xa0);
					goto LAB_00667a94;
				}
				work = slot + 0x48;
				off = off + 8;
				prev = slot;
			} while (off != 0x38);
			cur = (uint64_t *)*cur;
		} while (true);
	}
LAB_00667b98:
	SoftwareBreakpoint(0x5519, 0x667b9c);
LAB_00667a94:
	{
		uint8_t used_count = *(uint8_t *)((long)head + 0x1a);
		if (used_count < *(uint8_t *)((long)head + 0x19)) goto LAB_00667b2c;
		head = (uint64_t *)*head;
		if (head == (uint64_t *)0x0) {
			if (!have_new_node) {
				int rc = sk_x_0067d02c(work);
				if (rc != 0) {
					sk_x_006833d4(0x6a8797);
				}
				cur = (uint64_t *)sk_f_0066924c();
				if (cur != (uint64_t *)0x0) {
					tail_ptr = cur + 1;
					*tail_ptr = (uint64_t)(cur + 4);
					*(uint16_t *)(cur + 3) = 0x1001;
					cur[2] = 0;
					rc = sk_x_0067cffc(work);
					if (rc != 0) {
						sk_x_006833d4(0x6a8797);
					}
					head = *(uint64_t **)(slot + 0xa0);
					walk = head;
					do {
						walk_prev = walk;
						walk = (uint64_t *)*walk_prev;
					} while ((uint64_t *)*walk_prev != (uint64_t *)0x0);
					*cur = 0;
					if (cur + 0x14 < cur) goto LAB_00667b98;
					*walk_prev = (uint64_t)cur;
					cur[2] = walk_prev[2];
					if (cur + 4 < tail_ptr) goto LAB_00667b98;
					walk_prev[2] = (uint64_t)tail_ptr;
					have_new_node = true;
					goto LAB_00667a94;
				}
				sk_x_00685c64();
			}
			sk_x_00685ca0();
LAB_00667ce4:
			sk_x_006833d4(0x6a8797);
		}
		goto LAB_00667a94;
LAB_00667b2c:
		cur = head + 4 + used_count;
		if ((head + 4 <= cur && cur + 1 <= head + 0x14) && cur <= cur + 1) {
			*cur = item[1];
			*(uint8_t *)((long)head + 0x1a) = used_count + 1;
			*item = (uint64_t)head;
			*(uint64_t **)(slot + 0xa0) = head;
			int rc = sk_x_0067d02c(work);
			if (rc != 0) {
				sk_x_006833d4(0x6a8797);
			}
			rc = sk_x_0067cffc(self + 0x40);
			if (rc != 0) {
				sk_x_006833d4(0x6a8797);
			}
			return;
		}
		goto LAB_00667b98;
	}
}

/* FUN_00667d74 @ 0x00667d74   (est. sk_buffer_drain_node)
 * Ghidra: void FUN_00667d74(long param_1,long param_2)
 * Drains pool node `node` (param_2) out of the container `self` once all its
 * bitmap words are clear and the node's used-slot counter is exhausted. Unlinks
 * it from the container's +0x138 list, clears the in-use flag at +0x43, and
 * resets the +0x140 tail to point at the list head when the list empties.
 * Panics if the node is not the current +0x138 head, or if it is still
 * referenced by the tail list.
 * Confidence: medium
 * Notes: panic codes 0x6a902f / 0x6a90ad. */
void sk_f_00667d74(long self, long node)
{
	if (*(long *)(self + 0x138) != node) {
		sk_x_006833d4(0x6a902f);
	}
	if (*(unsigned short *)(node + 0x40) <= *(unsigned short *)(*(long *)(node + 8) + 6)) {
		uint64_t nwords = (uint64_t)*(uint8_t *)(node + 0x42);
		if (nwords != 0) {
			long * word_ptr = *(long **)(node + 0x28);
			do {
				if (*word_ptr != 0) {
					return;
				}
				nwords = nwords - 1;
				word_ptr = word_ptr + 1;
			} while (nwords != 0);
		}
		if ((*(long *)(self + 0x140) + -0x38 == node) && (*(long *)(node + 0x38) != 0)) {
			sk_x_006833d4(0x6a90ad);
		}
		long next = *(long *)(*(long *)(self + 0x138) + 0x38);
		*(long *)(self + 0x138) = next;
		if (next == 0) {
			*(long **)(self + 0x140) = (long *)(self + 0x138);
		}
		*(uint8_t *)(node + 0x43) = 0;
	}
	return;
}

/* FUN_00667e54 @ 0x00667e54   (est. sk_buffer_mark_slot_used)
 * Ghidra: void FUN_00667e54(long param_1,unsigned long param_2)
 * Marks the 0x20-uint8_t slot at address `addr` (param_2) as used in the owning
 * frame/message pool of `self`. Scans the node list from self+0x148, computes
 * the slot index from the address delta, sets the corresponding bit in the
 * node bitmap (walking the words at node+0x28), and records the node in the
 * container's dirty/tail list at +0x140 when not already flagged. Writes zero
 * to addr+0x18. Panics on range/alignment or double-mark.
 * Confidence: low
 * Notes: zero-write at param_2+0x18; panic codes 0x6a894c, 0x6a8ad7,
 *   0x6a8a27, 0x6a8b39; SoftwareBreakpoint(0x5519,0x668030). */
void sk_f_00667e54(long self, uint64_t addr)
{
	uint64_t limit = 0x7e;
	if ((*(uint8_t *)(self + 9) & 1) != 0) {
		limit = 0x1fe;
	}
	*(uint8_t *)(addr + 0x18) = 0;
	uint64_t lock_addr = self + 0x40;
	if (lock_addr <= self + 0x50U) {
		int rc = sk_x_0067cffc(lock_addr);
		if (rc != 0) {
			sk_x_006833d4(0x6a8797);
		}
		long * node_ptr = (long *)(self + 0x148);
		uint64_t * word = (uint64_t *)(self + 0x1c8);
		while (node_ptr + 0x10 <= (long *)word) {
			int64_t off = 0;
			do {
				uint64_t * bounds;
				uint64_t node, node_base, bit;
				uint64_t slot_index;
				word = (uint64_t *)((long)node_ptr + off + 8);
				bounds = (uint64_t *)((long)node_ptr + off + 0x10);
				if (node_ptr + 8 < (long *)bounds || bounds < word) goto LAB_0066802c;
				node_base = *word;
				if (node_base == 0) break;
				slot_index = (uint64_t)(addr - node_base) >> 5;
				if (slot_index < limit) {
					word = (uint64_t *)((long)node_ptr + off + 0x48);
					if (((word < (uint64_t *)(node_ptr + 9)) ||
					     (bounds = (uint64_t *)((long)node_ptr + off + 0x50), node_ptr + 0x10 < (long *)bounds)) ||
					    (bounds < word)) goto LAB_0066802c;
					node = *word;
					if (*(uint64_t *)(node + 0x30) != node_base) {
						sk_x_006833d4(0x6a894c);
					}
					if ((addr < node_base) ||
					    (*(uint64_t *)(node + 0x30) + (uint64_t)*(unsigned short *)(node + 0x40) * 0x20 <= addr)) {
						sk_x_00685d84();
					} else if (slot_index < *(unsigned short *)(*(long *)(node + 8) + 6)) {
						word = *(uint64_t **)(node + 0x28);
						word = word + (slot_index >> 6);
						if (((word < *(uint64_t **)(node + 0x28)) ||
						     (*(uint64_t **)(node + 0x28) + *(uint8_t *)(node + 0x42) < word + 1)) ||
						    (word + 1 < word)) goto LAB_0066802c;
						bit = 1ULL << ((addr - node_base >> 5) & 0x3f);
						if ((*word & bit) != 0) {
							sk_x_006833d4(0x6a8ad7);
						}
						*word = *word | bit;
						if ((*(uint8_t *)(node + 0x43) & 1) == 0) {
							if (node + 0x48 < node) goto LAB_0066802c;
							*(uint64_t *)(node + 0x38) = 0;
							**(uint64_t **)(self + 0x140) = node;
							*(uint64_t **)(self + 0x140) = (uint64_t *)(node + 0x38);
							*(uint8_t *)(node + 0x43) = 1;
						}
						rc = sk_x_0067d02c(lock_addr);
						if (rc == 0) {
							return;
						}
						sk_x_006833d4(0x6a8797);
					}
					sk_x_006833d4(0x6a8a27);
				}
				off = off + 8;
			} while (off != 0x38);
			node_ptr = (long *)*node_ptr;
			word = (uint64_t *)(node_ptr + 0x10);
			if (node_ptr == (long *)0x0) {
				sk_x_006833d4(0x6a8b39);
			}
		}
	}
LAB_0066802c:
	SoftwareBreakpoint(0x5519, 0x668030);
}

/* FUN_00668128 @ 0x00668128   (est. sk_buffer_pool_init)
 * Ghidra: void FUN_00668128(void)
 * Global one-time initializer for the shared frame-buffer pool. Sets up the
 * container's global descriptors (sk_g_006b5838 head/tail), initializes the
 * per-slot allocator (sk_f_006673ec, sk_f_0066a808), allocates the main buffer
 * object via sk_x_0065cc0c(4,10), and if the slot region (0x6fe8c0) is present,
 * stamps its descriptor globals, wires the tx list (sk_f_0066a7b8), takes the
 * pool lock, and attaches the first buffer item (sk_f_00667870). Panics on any
 * lock or allocation failure.
 * Confidence: low
 * Notes: globals sk_g_006b5838/006b5840/006b5900/006fe828/006fe818/006fe8b0;
 *   fixed pool addresses 0x6b5700/0x6ff120/0x6fe8d0; panic 0x6a8797. */
void sk_f_00668128(void)
{
	int rc;

	sk_f_006673ec(0x6ff120);
	sk_f_0066a808(0x6b5700, 0x6b68f8, 0x6b68b0);
	sk_g_006b5838 = 0;
	sk_g_006b5840 = (uint64_t)&sk_g_006b5838;
	rc = sk_x_0067cfe0(0x6b58f0, 0);
	if (rc != 0) {
		sk_x_006833d4(0x6a8797);
	}
	sk_g_006b5900 = 0;
	sk_x_0065cbbc(0x6b59a0);
	rc = sk_x_0067cfe0(0x700160, 0);
	if (rc != 0) {
		sk_x_006833d4(0x6a8797);
	}
	int64_t obj = sk_x_0065cc0c(4, 10);
	if (obj == 0) {
		rc = sk_x_0067cfe0(0x6fe8c0, 0);
		if (rc == 0) {
			sk_g_006fe828 = 0x1001;
			sk_g_006fe818 = 0x6fe830;
			sk_x_0065cbbc(0x6b59c0);
			sk_f_0066a7b8(&sk_g_006fe818);
			sk_g_006fe8b0 = 0x6fe810;
			rc = sk_x_0067cffc(0x6b5740);
			if (rc != 0) {
				sk_x_006833d4(0x6a8797);
			}
			sk_f_00667870(0x6b5700, (uint64_t *)0x6ff120);
			rc = sk_x_0067d02c(0x6b5740);
			if (rc == 0) {
				return;
			}
			sk_x_006833d4(0x6a8797);
		}
	} else {
		sk_x_00685dbc();
	}
	sk_x_006833d4(0x6a8797);
}

/* FUN_00668c6c @ 0x00668c6c   (est. sk_buffer_pool_base)
 * Ghidra: uint64_t FUN_00668c6c(void)
 * Returns the fixed base address of the global frame-buffer pool (0x6b5700).
 * Pure accessor; no side effects.
 * Confidence: high
 * Notes: trivial constant return. */
uint64_t sk_f_00668c6c(void)
{
	return 0x6b5700;
}

/* FUN_00668c78 @ 0x00668c78   (est. sk_buffer_check_region)
 * Ghidra: void FUN_00668c78(long param_1)
 * Validates that the region range [ptr+0x60, ptr+0x130] is well-formed;
 * returns normally when 0x60 <= 0x130, else traps. A bounds sanity predicate
 * over a descriptor's internal range fields.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x668c94) on the failed check. */
void sk_f_00668c78(long ptr)
{
	if (ptr + 0x60U <= ptr + 0x130U) {
		return;
	}
	SoftwareBreakpoint(0x5519, 0x668c94);
}

/* FUN_0066834c @ 0x0066834c   (est. sk_buffer_map_pages)
 * Ghidra: void FUN_0066834c(long param_1)
 * Maps the frame-buffer pages of the container `self` into a fresh page-table
 * leaf region. Walks the node list from self+0x148; for each empty-node block it
 * allocates a root descriptor via the function pointer at sk_g_006b6928, then
 * for each page slot (0x1c000/0x4000 stride) it allocates a 16K page, translates
 * its virtual address via sk_x_00677674/sk_x_006777d8, maps it through the
 * table-map function pointer at sk_g_006b6938 and sk_x_006787a0, and threads
 * the leaf into self+0x1c8. Unwinds (sk_f_00668cb0) on any map error. The
 * whole pass is guarded by the +0x1d0 flag. Stack canary checked at exit.
 * Confidence: low
 * Notes: fn-ptr globals sk_g_006b6928/sk_g_006b6938; error table at
 *   0x6b5e50/0x6b5e58; canary sk_g_006b5ed0; struct seed constants at
 *   sk_g_0068a3a8/0068a3b0/0068a3b8/0068a3c0; many panic codes; SoftwareBreakpoint
 *   (0x5519,0x668bb8). */
void sk_f_0066834c(long self)
{
	uint8_t * err_ptr;
	uint64_t * leaf;
	long * leaf_end;
	bool progressed, loop_again;
	int rc;
	uint64_t result, vaddr, bound;
	long * slot_ptr, * node_ptr;
	long last_leaf, root, entry, off, base, block, limit, idx;
	long seed;             /* seed struct base */
	uint64_t seed_b8;      /* seed struct word */
	uint64_t seed_b0;      /* seed struct word */
	uint64_t seed_a8;      /* seed struct word */
	uint64_t seed_a0;      /* seed struct word */
	long out_root;         /* allocation root output */
	long out_tag;          /* allocation tag output */
	long canary;

	canary = sk_g_006b5ed0;   /* stack canary */
	if ((*(uint8_t *)(self + 9) & 1) == 0) {
		sk_x_00685e1c();
LAB_00668754:
		sk_x_006833d4(0x6a8797);
	}
	if ((*(uint8_t *)(self + 0x1d0) & 1) == 0) {
		loop_again = false;
		*(uint8_t *)(self + 0x1d0) = 1;
		node_ptr = (long *)(self + 0x148);
		do {
			if (node_ptr[8] == 0) {
				seed_b8 = sk_g_0068a3b0;
				seed = sk_g_0068a3a8;
				seed_a8 = sk_g_0068a3c0;
				seed_b0 = sk_g_0068a3b8;
				out_root = 0;
				out_tag = 0;
				rc = sk_x_0067d02c(self + 0x40);
				if (rc != 0) {
					sk_x_006833d4(0x6a8797);
				}
				result = ((uint64_t(*)(long, uint64_t, void *, long *, int, void *))sk_g_006b6928)
					(self, 0x1800, &seed, &out_root, 0, &seed);
				if ((result & 0xff) != 0) {
					idx = (result & 0xff) * 8;
					err_ptr = (uint8_t *)(idx + 0x6b5e50);
					if (((uint8_t *)0x6b5e4f < err_ptr &&
					     (uint8_t *)&sk_g_006b5e58 + idx < (uint8_t *)0x6b5e91) &&
					    err_ptr <= (uint8_t *)&sk_g_006b5e58 + idx) {
						sk_x_006833d4(0x6a923b);
					}
					goto LAB_00668bb4;
				}
				if (out_tag != 0x6b6978) {
					sk_x_006833d4(0x6a929c);
				}
				rc = sk_x_0067cffc(self + 0x40);
				if (rc != 0) {
					sk_x_006833d4(0x6a8797);
				}
				if (node_ptr[8] != 0) {
					sk_x_006833d4(0x6a9300);
				}
				node_ptr[8] = out_root;
				loop_again = true;
			}
			off = 0;
			idx = 0;
			slot_ptr = node_ptr + 9;
			limit = 1;
			progressed = loop_again;
			do {
				if (node_ptr + 0x10 < slot_ptr + 1 || slot_ptr + 1 < slot_ptr) goto LAB_00668bb4;
				entry = *slot_ptr;
				if (entry == 0) break;
				if (*(long *)(entry + 0x10) == 0) {
					if ((*(uint8_t *)(self + 9) & 1) == 0) {
						sk_x_00685df4();
LAB_00668a70:
						sk_x_006833d4(0x6a9458);
					}
					block = node_ptr[8];
					if (block == 0) {
						sk_x_006833d4(0x6a936d);
					}
					last_leaf = *(long *)(self + 0x1c8);
					if (last_leaf != 0) {
						if (*(long *)(last_leaf + 0x10) == 0) {
							sk_x_006833d4(0x6a93c5);
						}
						if (*(long *)(*(long *)(last_leaf + 0x18) + 8) != 0) goto LAB_00668a70;
					}
					result = *(uint64_t *)(entry + 0x18);
					if (result == 0 || (result & 0x3fff) != 0) {
						sk_x_006833d4(0x6a9515);
					}
					base = *(long *)(block + 8);
					rc = sk_x_0067d02c(self + 0x40);
					if (rc != 0) goto LAB_00668754;
					bound = block + 0x80;
					if (block + 0x90U < bound) goto LAB_00668bb4;
					rc = sk_x_0067cffc(bound);
					if (rc != 0) {
						sk_x_006833d4(0x6a8797);
					}
					seed_a0 = 0;
					seed_b8 = 0;
					seed = 0;
					seed_a8 = 0;
					seed_b0 = 0;
					sk_f_006662ac(&seed, *(uint64_t *)(block + 0x78),
						      (int)((uint64_t)(off + (base - *(long *)(self + 0x88))) >> 0xe) + 1);
					root = seed;
					*(uint64_t *)(block + 0x78) = seed_a0;
					rc = sk_x_0067d02c(bound);
					if (root == 0) {
						if (rc != 0) {
							sk_x_006833d4(0x6a8797);
						}
						idx = (seed_b0 & 0xff) * 8;
						err_ptr = (uint8_t *)(idx + 0x6b5e50);
						if (((uint8_t *)0x6b5e4f < err_ptr &&
						     (uint8_t *)&sk_g_006b5e58 + idx < (uint8_t *)0x6b5e91) &&
						    err_ptr <= (uint8_t *)&sk_g_006b5e58 + idx) {
							sk_x_006833d4(0x6a95fe);
						}
						goto LAB_00668bb4;
					}
					if (rc != 0) {
						sk_x_006833d4(0x6a8797);
					}
					block = off + base;
					vaddr = sk_x_00677674(self + 0x60, 1, block);
					bound = sk_x_006777d8(self + 0x60, vaddr);
					if ((bound & 1) == 0) {
						sk_x_006833d4(0x6a962a);
					}
					result = ((uint64_t(*)(uint64_t, uint64_t, uint64_t, uint64_t))sk_g_006b6938)
						(0x6b5700, result, 0, root);
					if ((result & 0xff) != 0) {
						idx = (result & 0xff) * 8;
						err_ptr = (uint8_t *)(idx + 0x6b5e50);
						if (((uint8_t *)0x6b5e4f < err_ptr &&
						     (uint8_t *)&sk_g_006b5e58 + idx < (uint8_t *)0x6b5e91) &&
						    err_ptr <= (uint8_t *)&sk_g_006b5e58 + idx) {
							sk_x_006833d4(0x6a968c);
						}
						goto LAB_00668bb4;
					}
					result = sk_x_006787a0(self + 0x60, vaddr, root, block, 0, 0);
					if ((result & 0xff) == 4) {
						result = sk_x_006782b4(self + 0x60, block);
						if ((result & 1) == 0) {
							sk_x_006833d4(0x6a9701);
						}
						result = sk_x_006787a0(self + 0x60, vaddr, root, block, 0, 0);
					}
					vaddr = sk_g_006b4368;
					if ((result & 0xff) != 0) {
						sk_f_00668cb0(&out_root);
						sk_x_00685acc(vaddr);
						sk_f_00668cb0(&out_root, result);
						sk_x_006833d4(0x6a71a1);
					}
					rc = sk_x_0067cffc(self + 0x40);
					if (rc != 0) {
						sk_x_006833d4(0x6a8797);
					}
					if (*(long *)(entry + 0x10) != 0) {
						sk_x_006833d4(0x6a986c);
					}
					leaf = *(uint64_t **)(entry + 0x18);
					leaf_end = *(long **)(entry + 0x20);
					if (0x3fff < (uint64_t)((long)leaf_end - (long)leaf)) {
						sk_x_006833d4(0x6a98cb);
					}
					root = *(long *)(entry + 8);
					if (0x4000 < (root - (long)leaf) + 0x3fe0U) {
						sk_x_006833d4(0x6a9921);
					}
					result = (long)leaf_end + off + (base - (long)leaf);
					*(uint8_t *)(leaf + 2) = 1;
					if ((result + 1 < result) ||
					    ((long)leaf + limit +
					     ((((long)leaf_end - (long)leaf) + idx * 0x4000) - (long)leaf_end) < 1))
						goto LAB_00668bb4;
					*leaf = result;
					*(uint16_t *)((long)leaf + 0x11) = 0x101;
					*leaf_end = off + ((base + root) - (long)leaf);
					if (last_leaf != 0) {
						*(long *)(*(long *)(last_leaf + 0x18) + 8) = block;
					}
					*(long *)(self + 0x1c8) = entry;
					*(long *)(entry + 0x10) = block;
					progressed = true;
				}
				idx = idx + 1;
				off = off + 0x4000;
				limit = limit + -0x4000;
				slot_ptr = slot_ptr + 1;
			} while (off != 0x1c000);
			slot_ptr = (long *)*node_ptr;
			node_ptr = slot_ptr;
			if (slot_ptr == (long *)0x0) {
				node_ptr = (long *)(self + 0x148);
			}
			loop_again = (bool)(slot_ptr != (long *)0x0 & progressed);
		} while ((slot_ptr != (long *)0x0) || (progressed));
		if ((*(uint8_t *)(self + 0x1d0) & 1) == 0) {
			sk_x_006833d4(0x6a91b3);
		}
		*(uint16_t *)(self + 0x1d0) = 0x100;
	}
	if (sk_g_006b5ed0 == canary) {
		return;
	}
	sk_x_0067f660();   /* stack canary mismatch */
LAB_00668bb4:
	SoftwareBreakpoint(0x5519, 0x668bb8);
}
/* ===== part 6: fragment of SKR68 ===== */

/* FUN_00668c94 @ 0x00668c94   (est. sk_alloc_region_bounds_ok)
 * Ghidra: void FUN_00668c94(long param_1)
 * Validates a region sized from base+0x58 through base+0x60 (i.e. requires at
 * least 8 bytes). Returns normally when the range is valid; otherwise traps
 * via SoftwareBreakpoint. Used as an entry sanity check for the allocator.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x668cb0) is the panic trap. */
void sk_f_00668c94(int64_t base)
{
  if ((uint64_t)(base + 0x58U) <= (uint64_t)(base + 0x60U)) {
    return;
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x668cb0);;
}

/* FUN_00668cb0 @ 0x00668cb0   (est. sk_error_msg_build)
 * Ghidra: void FUN_00668cb0(uint64_t *param_1,uint8_t param_2)
 * Fills a 32-uint8_t (4 x uint64) message record with the L4 error descriptor for
 * the given error code. For error code > 9 it copies a canned 32-uint8_t record
 * from globals 0068a508..0068a520 and forwards the message to sk_x_0064effc.
 * Otherwise it looks up one of the per-code L4 error strings (records at
 * 0068a3c8..0068a4e8) and copies its 32 bytes into the output.
 * Confidence: medium
 * Notes: Globals _DAT_0068a508/518/520, uRam0068a510; string record table
 *   s_L4_ErrorCode*_0068a3c8...; decompiler warns globals starting '_'
 *   overlap smaller symbols. */
void sk_f_00668cb0(uint64_t *out_msg, uint8_t error_code)
{
  const uint8_t *record;
  uint64_t w0, w1, w2, w3;

  w0 = sk_g_0068a520;
  w1 = sk_g_0068a518;
  w2 = sk_g_0068a508;

  if (9 < error_code) {
    out_msg[1] = sk_g_0068a510;
    out_msg[0] = w2;
    out_msg[3] = w0;
    out_msg[2] = w1;
    sk_x_0064effc(out_msg, 0x20);
    return;
  }

  switch (error_code) {
  default:
    record = (const uint8_t *)sk_str_0068a3c8;      /* L4_ErrorCodeSuccess */
    break;
  case 1:
    record = (const uint8_t *)sk_str_0068a3e8;      /* L4_ErrorCodePreempted */
    break;
  case 2:
    record = (const uint8_t *)sk_str_0068a408;      /* L4_ErrorCodeCanceled */
    break;
  case 3:
    record = (const uint8_t *)sk_str_0068a428;      /* L4_ErrorCodeTruncated */
    break;
  case 4:
    record = (const uint8_t *)sk_str_0068a448;      /* L4_ErrorCodeCapInvalid */
    break;
  case 5:
    record = (const uint8_t *)sk_str_0068a468;      /* L4_ErrorCodeSlotInvalid */
    break;
  case 6:
    record = (const uint8_t *)sk_str_0068a488;      /* L4_ErrorCodeMethodInvalid */
    break;
  case 7:
    record = (const uint8_t *)sk_str_0068a4a8;      /* L4_ErrorCodeArgumentInvalid */
    break;
  case 8:
    record = (const uint8_t *)sk_str_0068a4c8;      /* L4_ErrorCodeOperationInvalid */
    break;
  case 9:
    record = (const uint8_t *)sk_str_0068a4e8;      /* L4_ErrorCodePermissionInvalid */
  }

  w2 = *(const uint64_t *)(record + 0);
  w0 = *(const uint64_t *)(record + 0x18);
  w1 = *(const uint64_t *)(record + 0x10);
  out_msg[1] = *(const uint64_t *)(record + 8);
  out_msg[0] = w2;
  out_msg[3] = w0;
  out_msg[2] = w1;
}

/* FUN_00668dc4 @ 0x00668dc4   (est. sk_panic_bad_alloc_6a8cdf)
 * Ghidra: void FUN_00668dc4(uint64_t param_1)
 * Fatal-error helper: stores its argument then panics via sk_x_006833d4 with
 * the magic error code 0x6a8cdf. The argument is kept in a scratch slot before
 * the (non-returning) panic.
 * Confidence: medium
 * Notes: WARNING: subroutine does not return. */
void sk_f_00668dc4(uint64_t arg)
{
  sk_x_006833d4(0x6a8cdf);
}

/* FUN_00668dd8 @ 0x00668dd8   (est. sk_alloc_slab_158)
 * Ghidra: void FUN_00668dd8(void)
 * Allocates an object of size 0x158 from the slab pool returned by
 * sk_x_0065be08(0x6fea40,4,0xd). Verifies the pool layout bounds before handing
 * the freelist head (+0x158) to the allocator sk_f_00668e24; traps otherwise.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x668e24) is the bounds-fail trap. */
void sk_f_00668dd8(void)
{
  uint64_t pool;

  pool = sk_x_0065be08(0x6fea40, 4, 0xd);
  if ((uint64_t)pool <= (uint64_t)(pool + 0x3e0) &&
      (uint64_t)(pool + 0x158) <= (uint64_t)(pool + 400)) {
    sk_f_00668e24(pool, (uint16_t *)(pool + 0x158), 1);
    return;
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x668e24);;
}

/* FUN_00668e24 @ 0x00668e24   (est. sk_slab_alloc)
 * Ghidra: unsigned long * FUN_00668e24(unsigned long param_1,unsigned short *param_2,int param_3)
 * Core fixed-size slab allocator. pool_base identifies the slab; free_list is
 * its free-list header (a stack of free nodes plus a free-count field). When
 * flags is nonzero it first pops a pre-free'd node off the list head; otherwise
 * it walks the free-list and, if empty, replenishes it with a fresh 0x4000-uint8_t
 * chunk from sk_f_00669db4, splitting off a block of the requested size
 * (element 0 of the freelist). Returns the allocated node, zeroes it
 * (sk_x_0067a7f0), bumps the alloc count and releases the interrupt spinlock
 * (sk_f_0066ab40). Traps on structural/overflow failures.
 * Confidence: medium
 * Notes: bounds checks use magic 0x6db6db6db6db6db7 division; SoftwareBreakpoint
 *   traps at 0x669048 / panics sk_x_006833d4(0x6a9e9a,0x6a9ef7). */
uint64_t *sk_f_00668e24(uint64_t pool_base, uint16_t *free_list, int flags)
{
  uint64_t *node, *cur, *end, *p8, *p9;
  uint64_t req, v3, v4;
  sk_u128_t tmp;

  if (pool_base <= (uint64_t)(pool_base + 0x30)) {
    tmp = sk_f_0066a9bc();
    /* validate freelist sits inside the pool region */
    if (0xc < (uint64_t)(((int64_t)((int64_t)free_list + (-0xe8 - (int64_t)pool_base)) >> 3) *
                         0x6db6db6db6db6db7)) {
      sk_x_006833d4(0x6a9e9a);
    }
    req = (uint64_t)*free_list;
    if (0x3fff < req) {
      sk_x_006833d4(0x6a9ef7);
    }

    if (flags != 0) {
      cur = *(uint64_t **)((uint8_t *)free_list + 0x10);
      if (cur != 0) {
        end = *(uint64_t **)((uint8_t *)free_list + 0x14);
        if ((cur + 3 <= end) &&
            (node = *(uint64_t **)((uint8_t *)free_list + 0x18), node <= cur)) {
          /* pop the head of the pending-free stack */
          v4 = cur[1];
          v3 = *cur;
          *(uint64_t *)((uint8_t *)free_list + 0x18) = cur[2];
          *(uint64_t *)((uint8_t *)free_list + 0x14) = v4;
          *(uint64_t *)((uint8_t *)free_list + 0x10) = v3;
          v3 = *(int64_t *)((uint8_t *)free_list + 4) - 1;
          *(uint64_t *)((uint8_t *)free_list + 4) = v3;
          if (v3 < *(uint8_t *)((int64_t)free_list + 3)) {
            *(char *)((int64_t)free_list + 3) = (char)v3;
          }
          goto recheck;
        }
        goto fail;
      }
    }

    /* walk the free list looking for a node with room for req bytes */
    p8 = (uint64_t *)(pool_base + 200);
    p9 = (uint64_t *)(pool_base + 0xd0);
    do {
      node = (uint64_t *)*p8;
      if (node == 0) {
        /* empty: allocate a fresh 0x4000-uint8_t chunk */
        node = (uint64_t *)sk_f_00669db4();
        end = node + 0x800;
        if (node < end) {
          if (node == 0) {
            sk_f_0066ab40(pool_base, tmp.lo, tmp.hi);
            return 0;
          }
          if ((node + 2 <= end) && (node <= node + 2)) {
            *node = 0;
            node[1] = 0x4000;
            if ((p8 + 1 <= p9) && (p8 <= p8 + 1)) {
              *p8 = (uint64_t)node;
              v3 = 0x4000;
              goto split;
            }
          }
        }
        break;
      }
      end = node + 2;
      v3 = node[1];
      if (req <= v3) {
        goto split;
      }
      p8 = node;
      p9 = node + 1;
    } while (node <= end);

  fail:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x669048);;
    return 0;

  split:
    if (node + 2 <= end) {
      v4 = *node;
      v3 = v3 - req;
      cur = (uint64_t *)((int64_t)node + req);
      end = node;
      if (v3 < 0x10) {
        if ((v4 <= v4 + 0x10 && p8 + 1 <= p9) && p8 <= p8 + 1) {
          *p8 = v4;
          goto recheck;
        }
      }
      else if (v4 <= v4 + 0x10 && cur + 2 <= (uint64_t *)((int64_t)cur + v3)) {
        *cur = v4;
        cur[1] = v3;
        if (((cur <= cur + 2) && (p8 + 1 <= p9)) && (p8 <= p8 + 1)) {
          *p8 = (uint64_t)cur;
          goto recheck;
        }
      }
    }
    goto fail;

  recheck:
    if (((cur <= end) && (node <= cur)) &&
        (req <= (uint64_t)((int64_t)end - (int64_t)cur))) {
      sk_x_0067a7f0(cur, 0, req);
      *(int64_t *)((uint8_t *)free_list + 8) += 1;
      sk_f_0066ab40(pool_base, tmp.lo, tmp.hi);
      if (cur < end) {
        return cur;
      }
    }
    goto fail;
  }
  goto fail;
}

/* FUN_006690dc @ 0x006690dc   (est. sk_free_slab_158)
 * Ghidra: void FUN_006690dc(uint64_t param_1)
 * Returns an object into the 0x158-uint8_t slab. Resolves the pool via
 * sk_x_0065be08(0x6fea40,4,0xd), verifies layout bounds, then hands the object
 * to the freelist pusher sk_f_00669134; traps on bad layout.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x669134) is the bounds-fail trap. */
void sk_f_006690dc(uint64_t obj)
{
  uint64_t pool;

  pool = sk_x_0065be08(0x6fea40, 4, 0xd);
  if ((uint64_t)pool <= (uint64_t)(pool + 0x3e0) &&
      (uint64_t)(pool + 0x158) <= (uint64_t)(pool + 400)) {
    sk_f_00669134(pool, (uint16_t *)(pool + 0x158), (uint64_t *)obj);
    return;
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x669134);;
}

/* FUN_00669134 @ 0x00669134   (est. sk_slab_free)
 * Ghidra: void FUN_00669134(unsigned long param_1,unsigned short *param_2,uint64_t *param_3)
 * Returns an allocated object to the slab free list. Validates that the object
 * lies within the slab's recorded size (element 0), then links it onto the
 * pending-free stack at the freelist head (free_list+0x10/0x14/0x18), bumps the
 * free counts (free_list+4 and +0xc) and releases the interrupt spinlock
 * (sk_f_0066ab40). Traps if the object is out of range.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x66921c) trap; panics sk_x_006833d4(0x6a9e9a). */
void sk_f_00669134(uint64_t pool_base, uint16_t *free_list, uint64_t *obj)
{
  uint16_t rec_size;
  uint64_t v3, v4;
  sk_u128_t tmp;

  if (obj == 0) {
    return;
  }
  if (pool_base <= (uint64_t)(pool_base + 0x30)) {
    tmp = sk_f_0066a9bc(pool_base);
    if (0xc < (uint64_t)(((int64_t)((int64_t)free_list + (-0xe8 - (int64_t)pool_base)) >> 3) *
                         0x6db6db6db6db6db7)) {
      sk_x_006833d4(0x6a9e9a);
    }
    rec_size = *free_list;
    if (obj + 3 <= (uint64_t *)((int64_t)obj + (uint64_t)rec_size)) {
      /* push obj onto the pending-free stack */
      v4 = *(uint64_t *)((uint8_t *)free_list + 0x14);
      v3 = *(uint64_t *)((uint8_t *)free_list + 0x10);
      obj[2] = *(uint64_t *)((uint8_t *)free_list + 0x18);
      obj[1] = v4;
      obj[0] = v3;
      *(uint64_t **)((uint8_t *)free_list + 0x14) =
          (uint64_t *)((int64_t)obj + (uint64_t)rec_size);
      *(uint64_t **)((uint8_t *)free_list + 0x18) = obj;
      *(int64_t *)((uint8_t *)free_list + 4) += 1;
      *(int64_t *)((uint8_t *)free_list + 0xc) += 1;
      *(uint64_t **)((uint8_t *)free_list + 0x10) = obj;
      sk_f_0066ab40(pool_base, tmp.lo, tmp.hi);
      return;
    }
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x66921c);;
}

/* FUN_0066924c @ 0x0066924c   (est. sk_alloc_slab_1c8)
 * Ghidra: void FUN_0066924c(void)
 * Allocates an object of size 0x1c8 from the shared pool (freelist head at
 * pool+0x1c8) via sk_f_00668e24. Bounds-checks the pool layout first.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x669298) trap. */
uint64_t *sk_f_0066924c(void)
{
  uint64_t pool;

  pool = sk_x_0065be08(0x6fea40, 4, 0xd);
  if ((uint64_t)pool <= (uint64_t)(pool + 0x3e0) &&
      (uint64_t)(pool + 0x1c8) <= (uint64_t)(pool + 0x200)) {
    return (uint64_t *)sk_f_00668e24(pool, (uint16_t *)(pool + 0x1c8), 1);
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x669298);;
}

/* FUN_00669298 @ 0x00669298   (est. sk_alloc_slab_270)
 * Ghidra: void FUN_00669298(void)
 * Allocates an object of size 0x270 from the shared pool (freelist head at
 * pool+0x270) via sk_f_00668e24. Bounds-checks the pool layout first.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x6692e4) trap. */
uint64_t *sk_f_00669298(void)
{
  uint64_t pool;

  pool = sk_x_0065be08(0x6fea40, 4, 0xd);
  if ((uint64_t)pool <= (uint64_t)(pool + 0x3e0) &&
      (uint64_t)(pool + 0x270) <= (uint64_t)(pool + 0x2a8)) {
    return (uint64_t *)sk_f_00668e24(pool, (uint16_t *)(pool + 0x270), 1);
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x6692e4);;
}

/* FUN_006692e4 @ 0x006692e4   (est. sk_alloc_slab_2a8)
 * Ghidra: void FUN_006692e4(void)
 * Allocates an object of size 0x2a8 from the shared pool (freelist head at
 * pool+0x2a8) via sk_f_00668e24. Bounds-checks the pool layout first.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x669330) trap. */
void sk_f_006692e4(void)
{
  uint64_t pool;

  pool = sk_x_0065be08(0x6fea40, 4, 0xd);
  if ((uint64_t)pool <= (uint64_t)(pool + 0x3e0) &&
      (uint64_t)(pool + 0x2a8) <= (uint64_t)(pool + 0x2e0)) {
    sk_f_00668e24(pool, (uint16_t *)(pool + 0x2a8), 1);
    return;
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x669330);;
}

/* FUN_00669330 @ 0x00669330   (est. sk_free_slab_2a8)
 * Ghidra: void FUN_00669330(uint64_t param_1)
 * Returns an object into the 0x2a8-uint8_t slab (freelist head at pool+0x2a8) via
 * sk_f_00669134. Bounds-checks the pool layout first.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x669388) trap. */
void sk_f_00669330(uint64_t obj)
{
  uint64_t pool;

  pool = sk_x_0065be08(0x6fea40, 4, 0xd);
  if ((uint64_t)pool <= (uint64_t)(pool + 0x3e0) &&
      (uint64_t)(pool + 0x2a8) <= (uint64_t)(pool + 0x2e0)) {
    sk_f_00669134(pool, (uint16_t *)(pool + 0x2a8), (uint64_t *)obj);
    return;
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x669388);;
}

/* FUN_00669388 @ 0x00669388   (est. sk_alloc_slab_2e0)
 * Ghidra: void FUN_00669388(void)
 * Allocates an object of size 0x2e0 from the shared pool (freelist head at
 * pool+0x2e0) via sk_f_00668e24. Bounds-checks the pool layout first.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x6693d4) trap. */
void sk_f_00669388(void)
{
  uint64_t pool;

  pool = sk_x_0065be08(0x6fea40, 4, 0xd);
  if ((uint64_t)pool <= (uint64_t)(pool + 0x3e0) &&
      (uint64_t)(pool + 0x2e0) <= (uint64_t)(pool + 0x318)) {
    sk_f_00668e24(pool, (uint16_t *)(pool + 0x2e0), 1);
    return;
  }
  /* WARNING: does not return */
  SoftwareBreakpoint(0x5519, 0x6693d4);;
}
/* ===== part 7: fragment of SKR68 ===== */
/* Recreated from cL4 Secure Kernel slice SKR68. Ground truth: Ghidra FUN_
 * names + addresses. All names are estimates. Bodies only — the shared prelude
 * (types, intrinsics, externs) lives in the parent file. */

/* FUN_006693d4 @ 0x006693d4   (est. sk_pool_cfg_slot_2e0)
 * Ghidra: void FUN_006693d4(uint64_t param_1)
 * Resolves the 0x6fea40 pool region via the 0x6fea40 slot lookup, validates
 * that the [base+0x2e0, base+0x318) sub-slot is in range, then configures that
 * sub-slot with the given descriptor argument through sk_f_00669134. On a
 * bounds failure it traps via SoftwareBreakpoint(0x5519, 0x66942c).
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd); panic breakpoint 0x5519. */
void sk_f_006693d4(uint64_t arg)
{
    uint64_t base;

    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base <= base + 0x3e0 && base + 0x2e0 <= base + 0x318) {
        sk_f_00669134(base, base + 0x2e0, arg);
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x66942c);;
}

/* FUN_0066942c @ 0x0066942c   (est. sk_pool_commit_slot_318)
 * Ghidra: void FUN_0066942c(void)
 * Resolves the 0x6fea40 pool region, validates the [base+0x318, base+0x350)
 * sub-slot, then commits it via sk_f_00668e24(base, base+0x318, 1). Bounds
 * failure traps via SoftwareBreakpoint(0x5519, 0x669478).
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd); commit flag 1. */
void sk_f_0066942c(void)
{
    uint64_t base;

    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base <= base + 0x3e0 && base + 0x318 <= base + 0x350) {
        sk_f_00668e24(base, base + 0x318, 1);
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x669478);;
}

/* FUN_00669478 @ 0x00669478   (est. sk_pool_cfg_slot_318)
 * Ghidra: void FUN_00669478(uint64_t param_1)
 * Resolves the 0x6fea40 pool region, validates the [base+0x318, base+0x350)
 * sub-slot, then configures it with the given descriptor argument via
 * sk_f_00669134. Bounds failure traps via SoftwareBreakpoint(0x5519, 0x6694d0).
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd). */
void sk_f_00669478(uint64_t arg)
{
    uint64_t base;

    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base <= base + 0x3e0 && base + 0x318 <= base + 0x350) {
        sk_f_00669134(base, base + 0x318, arg);
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x6694d0);;
}

/* FUN_006694d0 @ 0x006694d0   (est. sk_pool_commit_slot_350)
 * Ghidra: void FUN_006694d0(void)
 * Resolves the 0x6fea40 pool region, validates the [base+0x350, base+0x388)
 * sub-slot, then commits it via sk_f_00668e24(base, base+0x350, 1). Bounds
 * failure traps via SoftwareBreakpoint(0x5519, 0x66951c).
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd); commit flag 1. */
void sk_f_006694d0(void)
{
    uint64_t base;

    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base <= base + 0x3e0 && base + 0x350 <= base + 0x388) {
        sk_f_00668e24(base, base + 0x350, 1);
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x66951c);;
}

/* FUN_0066951c @ 0x0066951c   (est. sk_pool_cfg_slot_350)
 * Ghidra: void FUN_0066951c(uint64_t param_1)
 * Resolves the 0x6fea40 pool region, validates the [base+0x350, base+0x388)
 * sub-slot, then configures it with the given descriptor argument via
 * sk_f_00669134. Bounds failure traps via SoftwareBreakpoint(0x5519, 0x669574).
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd). */
void sk_f_0066951c(uint64_t arg)
{
    uint64_t base;

    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base <= base + 0x3e0 && base + 0x350 <= base + 0x388) {
        sk_f_00669134(base, base + 0x350, arg);
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x669574);;
}

/* FUN_00669578 @ 0x00669578   (est. sk_pool_commit_slot_388)
 * Ghidra: void FUN_00669578(void)
 * Resolves the 0x6fea40 pool region, validates the [base+0x388, base+0x3c0)
 * sub-slot, then commits it via sk_f_00668e24(base, base+0x388, 1). Bounds
 * failure traps via SoftwareBreakpoint(0x5519, 0x6695c0).
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd); commit flag 1. */
void sk_f_00669578(void)
{
    uint64_t base;

    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base <= base + 0x3e0 && base + 0x388 <= base + 0x3c0) {
        sk_f_00668e24(base, base + 0x388, 1);
        return;
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x6695c0);;
}

/* FUN_006699e8 @ 0x006699e8   (est. sk_pool_slot_dispatch)
 * Ghidra: void FUN_006699e8(long param_1)
 * Acquires the 0x6b5a00 pool context via sk_f_0066a9bc (16-uint8_t state), calls
 * the descriptor's virtual method at offset +0x10 with the descriptor pointer,
 * then releases the context via sk_f_0066ab40. A thin dispatch wrapper.
 * Confidence: medium
 * Notes: context get/release FUN_0066a9bc / FUN_0066ab40; indirect call at
 *   (**(code **)(param_1 + 0x10))(param_1). */
void sk_f_006699e8(int64_t desc)
{
    sk_u128_t ctx;

    ctx = sk_f_0066a9bc(0x6b5a00);
    ((uint64_t (*)(uint64_t))*(uint64_t *)(desc + 0x10))(desc);
    sk_f_0066ab40(0x6b5a00, ctx.lo, ctx.hi);
}

/* FUN_00669618 @ 0x00669618   (est. sk_pool_table_init)
 * Ghidra: void FUN_00669618(void)
 * Per-CPU-safe pool table initializer. After a domain gate check
 * (sk_x_0065cc0c(4,0xd)) and cache barrier, it fills two contiguous region
 * descriptors at 0x6fe8e0 and 0x6fe990 (type uint8_t, base, size, end uint8_t, flags)
 * from globals 0x6b5a78/0x6b5a80/0x6b5a88/0x6b5a90 (and 0x6b5a40/0x6b5a48/
 * 0x6b5a50/0x6b5a58), links them via 0x6b5aa0/0x6b5a68, then scans three table
 * slots at 0x6b5dc0. Empty slots get filled via sk_x_00678a64; otherwise an
 * object is found (sk_x_00685e44) and either dispatched directly or claimed by
 * scanning its three sub-slots and, when all are busy, its 0x38-stride entry
 * table, committing a free entry through sk_f_00668e24/sk_f_00669134.
 * Confidence: low
 * Notes: WARNING globals starting with '_' overlap smaller symbols; heavy
 *   uint8_t/qword global struct writes (0x6fe8e0..0x6fea40); callbacks
 *   0x669814 passed into sk_f_0066a8f4; panic strings 0x6a9f4f/0x6aa0db; many
 *   SoftwareBreakpoint(0x5519,...) bounds traps; globals 0x6b5dd8/0x6b5dd9
 *   are counters. */
void sk_f_00669618(void)
{
    uint8_t *slot_ptr;
    uint8_t *slot_end;
    int64_t l4;
    int64_t l5;
    uint64_t obj;
    uint64_t u7;
    int64_t *tbl;
    sk_u128_t ctx;
    uint8_t *descA;
    uint8_t *descB;

    l4 = sk_x_0065cc0c(4, 0xd);
    if (l4 != 0) {
        return;
    }

    sk_x_0065cbbc(0x6b59e0);
    sk_g_006fe930 = sk_f_00668c6c();
    sk_g_006b5a38 = sk_g_0068a738;
    /* descriptor A at 0x6fe8e0 */
    descA = (uint8_t *)&sk_g_006fe8e0;
    descA[0x10] = sk_g_006b5a88 - sk_g_006b5a80;   /* _DAT_006fe8f0 */
    descA[0x00] = (uint8_t)sk_g_006b5a78;          /* DAT_006fe8e0 */
    descA[0x01] = 0;                               /* _DAT_006fe8e1 */
    *(uint32_t *)(descA + 0x05) = 0;               /* uRam6fe8e5 */
    *(uint64_t *)(descA + 0x08) = sk_g_006b5a80;   /* _DAT_006fe8e8 */
    descA[0x18] = (uint8_t)sk_g_006b5a90;          /* DAT_006fe8f8 */
    descA[0x19] = 0;                               /* _DAT_006fe8f9 */
    *(uint64_t *)(descA + 0x1d) = 0x1000149000000ULL; /* uRam6fe8fd */
    *(uint64_t *)(descA + 0x2c) = 0;               /* uRam6fe90c */
    *(uint64_t *)(descA + 0x24) = 0;               /* _DAT_006fe904 */
    *(uint64_t *)(descA + 0x3c) = 0;               /* uRam6fe91c */
    *(uint64_t *)(descA + 0x34) = 0;               /* _DAT_006fe914 */
    *(uint64_t *)(descA + 0x48) = 0;               /* uRam6fe928 */
    *(uint64_t *)(descA + 0x40) = 0;               /* _DAT_006fe920 */
    *(uint64_t *)(descA + 0x44) = 0;               /* uRam6fe924 */
    *(uint64_t *)(descA + 0xa8) = 0;               /* _DAT_006fe988 */
    *(uint64_t *)(descA + 0xa0) = 0;               /* uRam6fe980 */
    *(uint64_t *)(descA + 0x98) = 0;               /* _DAT_006fe978 */
    *(uint64_t *)(descA + 0x90) = 0;               /* uRam6fe970 */
    *(uint64_t *)(descA + 0x88) = 0;               /* _DAT_006fe968 */
    *(uint64_t *)(descA + 0x80) = 0;               /* uRam6fe960 */
    *(uint64_t *)(descA + 0x78) = 0;               /* _DAT_006fe958 */
    *(uint64_t *)(descA + 0x70) = 0;               /* uRam6fe950 */
    *(uint64_t *)(descA + 0x68) = 0;               /* _DAT_006fe948 */
    *(uint64_t *)(descA + 0x60) = 0;               /* uRam6fe940 */
    *(uint64_t *)(descA + 0x58) = 0;               /* _DAT_006fe938 */
    sk_g_006b5aa0 = (uint64_t)&sk_g_006fe8e0;      /* _DAT_006b5aa0 */

    /* descriptor B at 0x6fe990 */
    descB = (uint8_t *)&sk_g_006fe990;
    descB[0x10] = sk_g_006b5a50 - sk_g_006b5a48;   /* _DAT_006fe9a0 */
    descB[0x00] = (uint8_t)sk_g_006b5a40;          /* DAT_006fe990 */
    descB[0x01] = 0;                               /* _DAT_006fe991 */
    *(uint32_t *)(descB + 0x05) = 0;               /* uRam6fe995 */
    *(uint64_t *)(descB + 0x08) = sk_g_006b5a48;   /* _DAT_006fe998 */
    descB[0x18] = (uint8_t)sk_g_006b5a58;          /* DAT_006fe9a8 */
    descB[0x19] = 0;                               /* _DAT_006fe9a9 */
    *(uint64_t *)(descB + 0x1d) = 0x1000149000000ULL; /* uRam6fe9ad */
    *(uint64_t *)(descB + 0x2c) = 0;               /* uRam6fe9bc */
    *(uint64_t *)(descB + 0x24) = 0;               /* _DAT_006fe9b4 */
    *(uint64_t *)(descB + 0x3c) = 0;               /* uRam6fe9cc */
    *(uint64_t *)(descB + 0x34) = 0;               /* _DAT_006fe9c4 */
    *(uint64_t *)(descB + 0x48) = 0;               /* uRam6fe9d8 */
    *(uint64_t *)(descB + 0x40) = 0;               /* _DAT_006fe9d0 */
    *(uint64_t *)(descB + 0x44) = 0;               /* uRam6fe9d4 */
    *(uint64_t *)(descB + 0xa8) = 0;               /* _DAT_006fea38 */
    *(uint64_t *)(descB + 0xa0) = 0;               /* uRam6fea30 */
    *(uint64_t *)(descB + 0x98) = 0;               /* _DAT_006fea28 */
    *(uint64_t *)(descB + 0x90) = 0;               /* uRam6fea20 */
    *(uint64_t *)(descB + 0x88) = 0;               /* _DAT_006fea18 */
    *(uint64_t *)(descB + 0x80) = 0;               /* uRam6fea10 */
    *(uint64_t *)(descB + 0x78) = 0;               /* _DAT_006fea08 */
    *(uint64_t *)(descB + 0x70) = 0;               /* uRam6fea00 */
    *(uint64_t *)(descB + 0x68) = 0;               /* _DAT_006fe9f8 */
    *(uint64_t *)(descB + 0x60) = 0;               /* uRam6fe9f0 */
    *(uint64_t *)(descB + 0x58) = 0;               /* _DAT_006fe9e8 */
    sk_g_006b5a68 = (uint64_t)&sk_g_006fe990;      /* _DAT_006b5a68 */
    sk_g_006fe9e0 = sk_g_006fe930;                 /* _DAT_006fe9e0 */

    sk_f_0066a8f4(0x6b5a00, 0x669814, 0x6b5a00);   /* 0x669814 = code callback */
    tbl = (int64_t *)&sk_g_006b5dc0;
    ctx = sk_f_0066a9bc(0x6b5a00);
    l4 = 3;
    for (;;) {
        if ((int64_t *)&sk_g_006b5dd8 < tbl + 1 || tbl + 1 < tbl ||
            tbl < (int64_t *)&sk_g_006b5dc0) {
            /* WARNING: Does not return */
            SoftwareBreakpoint(0x5519, 0x669810);;
        }
        if (*tbl == 0) {
            l5 = sk_x_00678a64();
            if (l5 == 0) {
                obj = sk_x_00685e44();
                if (obj + 0x30 < obj) {
                    goto bounds_panic_66997c;
                }
                u7 = sk_f_0066a988();
                if ((u7 & 1) == 0) {
                    goto panic_669f4f;
                }
                if (((*(uint8_t *)(obj + 0x41) & 1) != 0) ||
                    (*(int8_t *)(obj + 0x79) == 1)) {
                    goto LAB_6699b0;
                }
                if (*(int8_t *)(obj + 0xc0) == 1) {
                    l4 = sk_x_00685f08();
                    ctx = sk_f_0066a9bc(0x6b5a00);
                    ((uint64_t (*)(uint64_t))*(uint64_t *)(l4 + 0x10))(l4);
                    sk_f_0066ab40(0x6b5a00, ctx.lo, ctx.hi);
                    return;
                }
                l4 = 0;
                *(uint8_t *)(obj + 0xc0) = 1;
                slot_ptr = (uint8_t *)(obj + 0x3d8);
                break;
            }
            *tbl = l5;
            sk_g_006b5dd8 = sk_g_006b5dd8 + 1;
        }
        tbl = tbl + 1;
        l4 = l4 - 1;
        if (l4 == 0) {
            sk_g_006b5dd9 = 3;
            sk_f_0066ab40(0x6b5a00, ctx.lo, ctx.hi);
            return;
        }
    }

    for (;;) {
        slot_end = (uint8_t *)(obj + 0x3c0 + l4 * 8);
        if (slot_ptr < slot_end + 8 || slot_end + 8 < slot_end) {
            goto bounds_panic_66997c;
        }
        if (*(int64_t *)slot_end == 0) {
            *(uint8_t *)(obj + 0xc2) = 1;
            l4 = sk_f_0066ad54();
            *(uint8_t *)(obj + 0xc2) = 0;
            if (l4 == 0) {
                sk_x_00685ee0();
LAB_6699b0:
                sk_x_00685f40();
LAB_6699b4:
                sk_x_00685e6c();
LAB_6699b8:
                sk_x_00685ea4();
panic_669f4f:
                /* WARNING: Subroutine does not return */
                sk_x_006833d4(sk_str_006a9f4f);
            }
            *(int64_t *)slot_end = l4;
            if (2 < *slot_ptr) {
                /* WARNING: Subroutine does not return */
                sk_x_006833d4(sk_str_006aa0db);
            }
            l4 = 0;
            *slot_ptr = *slot_ptr + 1;
        } else {
            l4 = l4 + 1;
            if (l4 == 3) {
                l4 = 0;
                while (1) {
                    l5 = obj + l4;
                    if (obj + 0x3c0 < l5 + 0x120U) {
                        goto bounds_panic_66997c;
                    }
                    if (*(uint64_t *)(l5 + 0xf0) <
                        (uint64_t)*(uint8_t *)(l5 + 0xea)) {
                        break;
                    }
                    l4 = l4 + 0x38;
                    if (l4 == 0x2d8) {
                        *(uint8_t *)(obj + 0xc0) = 0;
                        if (((*(uint8_t *)(obj + 0x41) & 1) == 0) &&
                            (*(int8_t *)(obj + 0x79) != 1)) {
                            return;
                        }
                        goto LAB_6699b4;
                    }
                }
                u7 = obj + l4 + 0xe8;
                if (obj + l4 + 0x120 < u7) {
                    goto bounds_panic_66997c;
                }
                l4 = sk_f_00668e24(obj, u7, 0);
                if (l4 == 0) {
                    goto LAB_6699b8;
                }
                sk_f_00669134(obj, u7, l4);
                l4 = 0;
            }
        }
    }

bounds_panic_66997c:
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x66997c);;
}

/* FUN_00669a48 @ 0x00669a48   (est. sk_pool_descr_config)
 * Ghidra: void FUN_00669a48(void)
 * Configures the region descriptors held in the 0x6fea40 pool object. For the
 * [base+0x78, base+0xb0) descriptor it maps the range described by the fields
 * at +0x78/+0x80/+0x88/+0x90 via sk_f_00669af8, stores the result token at
 * +0xa0 and marks it live at +0xa8; then unconditionally maps a fixed
 * 0x10020000-uint8_t region at 0x200000 with kind 4/attr 0xfe into +0xb0. Finally
 * it maps the [base+0x40,base+0x50) descriptor into +0x68 and marks +0x70.
 * Bounds failure traps via SoftwareBreakpoint(0x5519, 0x669af8).
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd); fixed map args
 *   (4,0x200000,0x10020000,0xfe). */
void sk_f_00669a48(void)
{
    uint64_t base;
    uint64_t tok;

    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base + 0x78 <= base + 0xb0) {
        tok = sk_f_00669af8(*(uint8_t *)(base + 0x78),
                            *(int64_t *)(base + 0x80),
                            *(int64_t *)(base + 0x88) - *(int64_t *)(base + 0x80),
                            *(uint8_t *)(base + 0x90));
        *(uint64_t *)(base + 0xa0) = tok;
        *(uint8_t *)(base + 0xa8) = 1;
        tok = sk_f_00669af8(4, 0x200000, 0x10020000, 0xfe);
        *(uint64_t *)(base + 0xb0) = tok;
        if (base <= base + 0x3e0) {
            tok = sk_f_00669af8(*(uint8_t *)(base + 0x40),
                                *(int64_t *)(base + 0x48),
                                *(int64_t *)(base + 0x50) - *(int64_t *)(base + 0x48),
                                *(uint8_t *)(base + 0x58));
            *(uint64_t *)(base + 0x68) = tok;
            *(uint8_t *)(base + 0x70) = 1;
            return;
        }
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x669af8);;
}

/* FUN_00669af8 @ 0x00669af8   (est. sk_pool_region_map)
 * Ghidra: uint64_t FUN_00669af8(uint8_t param_1,long param_2,
 *     uint64_t param_3,uint8_t param_4)
 * Maps a region described by (kind, base, size, attr) through sk_x_0067203c,
 * which takes a 32-uint8_t config struct plus an out pointer and returns an error
 * code whose low uint8_t selects a slot in a small 0x6b5e50 error-string table.
 * On success (low uint8_t 0) returns the output token. On failure with a nonzero
 * base it hard-panics via sk_x_006833d4(sk_str_006a9c9a); with a zero base it
 * logs sk_str_006a9c4f via sk_x_0067d72c and returns 0; otherwise it traps via
 * SoftwareBreakpoint(0x5519, 0x669c3c).
 * Confidence: medium
 * Notes: config struct built on the stack (offsets 0/1/5/8/16/24/25/29);
 *   error table DAT_006b5e58/0x6b5e4f..0x6b5e91; kind base selects
 *   0x1000148 (zero base) vs 0x1000149 (nonzero base). */
uint64_t sk_f_00669af8(uint8_t kind, int64_t base, uint64_t size, uint8_t attr)
{
    int64_t err;
    uint8_t *tbl_hi;
    uint8_t *tbl_lo;
    uint32_t req_kind;
    sk_u128_t out;
    uint8_t cfg[32];

    *(uint32_t *)(cfg + 1) = 0;   /* local_4f + uStack_4b */
    *(uint32_t *)(cfg + 25) = 0;  /* local_37 + uStack_33 */
    req_kind = 0x1000148;
    if (base != 0) {
        req_kind = 0x1000149;
    }
    out.lo = 0;
    out.hi = 0;
    cfg[0] = kind;                 /* local_50 */
    *(int64_t *)(cfg + 8) = base;  /* local_48 */
    *(uint64_t *)(cfg + 16) = size;/* uStack_40 */
    cfg[24] = attr;                /* local_38 */
    err = sk_x_0067203c(req_kind, cfg, &out, 0, 0);
    if ((err & 0xff) == 0) {
        return out.lo;
    }
    tbl_lo = (uint8_t *)((err & 0xff) * 8 + 0x6b5e50);
    tbl_hi = (uint8_t *)&sk_g_006b5e58 + (err & 0xff) * 8;   /* DAT_006b5e58 */
    if (base == 0) {
        if ((tbl_hi < (uint8_t *)0x6b5e91 && tbl_lo <= tbl_hi) &&
            (uint8_t *)0x6b5e4f < tbl_lo) {
            sk_x_0067d72c(sk_str_006a9c4f);
            return 0;
        }
    } else if ((tbl_hi < (uint8_t *)0x6b5e91 && tbl_lo <= tbl_hi) &&
               (uint8_t *)0x6b5e4f < tbl_lo) {
        /* WARNING: Subroutine does not return */
        sk_x_006833d4(sk_str_006a9c9a);
    }
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x669c3c);;
}

/* FUN_00669c3c @ 0x00669c3c   (est. sk_pool_commit_slot_200)
 * Ghidra: void FUN_00669c3c(void)
 * Resolves the 0x6fea40 pool region, validates the [base+0x200, base+0x238)
 * sub-slot (trapping on a bounds failure), commits it via
 * sk_f_00668e24(base, base+0x200, 1), and on a nonzero error result calls
 * sk_f_006673ec. Returns void.
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd); error path sk_f_006673ec. */
void sk_f_00669c3c(void)
{
    uint64_t base;
    int64_t err;

    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base + 0x3e0 < base || base + 0x238 < base + 0x200) {
        /* WARNING: Does not return */
        SoftwareBreakpoint(0x5519, 0x669c98);;
    }
    err = sk_f_00668e24(base, base + 0x200, 1);
    if (err != 0) {
        sk_f_006673ec();
        return;
    }
    return;
}

/* FUN_00669c98 @ 0x00669c98   (est. sk_pool_dispatch)
 * Ghidra: uint64_t FUN_00669c98(uint64_t param_1)
 * Dispatches a pool operation on the 0x6fea40 object. If sk_f_00667578
 * reports active (bit 0), it configures the [base+0x200, base+0x238) sub-slot
 * with the argument via sk_f_00669134 and returns its result. Otherwise it
 * runs sk_x_00685f78, commits the [base+0x238, base+0x270) sub-slot via
 * sk_f_00668e24(...,1); on error it looks up a partner via sk_f_00669db4 and,
 * if found, returns sk_f_0066745c(error, partner), else re-configures the
 * sub-slot with the error and returns 0. Bounds failures trap via
 * SoftwareBreakpoint(0x5519, 0x669cf8 / 0x669db4).
 * Confidence: medium
 * Notes: pool lookup FUN_0065be08(0x6fea40,4,0xd); partner helpers
 *   sk_f_00669db4 / sk_f_0066745c. */
uint64_t sk_f_00669c98(uint64_t arg)
{
    uint64_t base;
    uint64_t res;
    int64_t err;
    int64_t partner;

    base = sk_f_00667578();
    if ((base & 1) != 0) {
        base = sk_x_0065be08(0x6fea40, 4, 0xd);
        if (base <= base + 0x3e0 && base + 0x200 <= base + 0x238) {
            res = sk_f_00669134(base, base + 0x200, arg);
            return res;
        }
        /* WARNING: Does not return */
        SoftwareBreakpoint(0x5519, 0x669cf8);;
    }
    sk_x_00685f78();
    base = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (base <= base + 0x3e0 && base + 0x238 <= base + 0x270) {
        err = sk_f_00668e24(base, base + 0x238, 1);
        if (err != 0) {
            partner = sk_f_00669db4();
            if (partner != 0) {
                res = sk_f_0066745c(err, partner);
                return res;
            }
            base = sk_x_0065be08(0x6fea40, 4, 0xd);
            if ((base + 0x3e0 < base) || (base + 0x270 < base + 0x238)) {
                goto bounds_panic_669db4;
            }
            sk_f_00669134(base, base + 0x238, err);
        }
        return 0;
    }
bounds_panic_669db4:
    /* WARNING: Does not return */
    SoftwareBreakpoint(0x5519, 0x669db4);;
}
/* ===== part 8: fragment of SKR68 ===== */

/* FUN_00669cfc @ 0x669cfc   (est. sk_alloc_locked)
 * Ghidra: uint64_t FUN_00669cfc(void)
 * Acquires the region lock at context+0x238, then allocates a page block via
 * sk_f_00669db4. If the allocation succeeds, links the locked region with the
 * block through sk_f_0066745c and returns its result; otherwise releases the
 * lock and returns 0. The bounds guards are overflow checks on the per-cpu
 * context base; on overflow it hits a SoftwareBreakpoint (fatal).
 * Confidence: medium
 * Notes: FUN_0065be08(0x6fea40,4,0xd) is the context-base getter; FUN_00668e24
 *   = lock-acquire, FUN_00669134 = lock-release. SoftwareBreakpoint 0x5519. */
uint64_t sk_f_00669cfc(void)
{
    uint64_t ctx, lock, blk;
    uint64_t result;

    ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (ctx <= ctx + 0x3e0 && ctx + 0x238 <= ctx + 0x270) {
        lock = sk_f_00668e24(ctx, ctx + 0x238, 1);
        if (lock != 0) {
            blk = sk_f_00669db4();
            if (blk != 0) {
                result = sk_f_0066745c(lock, blk);
                return result;
            }
            ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
            if ((ctx + 0x3e0 < ctx) || (ctx + 0x270 < ctx + 0x238)) goto fatal_669db0;
            sk_f_00669134(ctx, ctx + 0x238, lock);
        }
        return 0;
    }
fatal_669db0:
    SoftwareBreakpoint(0x5519, 0x669db4);
}

/* FUN_00669db4 @ 0x669db4   (est. sk_page_block_alloc)
 * Ghidra: uint64_t * FUN_00669db4(void)
 * Core page-block allocator. Pops a 0x4000-uint8_t (16 KiB) page-aligned block
 * off the per-cpu free list anchored at context+0xd0/+0xd8/+0xe0. When the
 * list is empty it prepares a fresh region descriptor (sk_f_0066a404),
 * validates it against the region callback (sk_g_006b6998), and links the new
 * block in. The 0xc0 flag selects a special continuation-based allocation path
 * that may resume into sk_f_0066a08c. Returns the allocated block or 0.
 * Confidence: low
 * Notes: continuation/coroutine frame built for FUN_00667568 (resume addr
 *   sk_f_0066a08c) is a decompiler artifact; extraout_x1 from FUN_0064e07c is
 *   a second return register. DAT_006b6998 = callback fn-ptr global,
 *   DAT_006b5e58 = error-code table anchor. Panics: sk_x_006833d4. */
uint64_t *sk_f_00669db4(void)
{
    uint64_t ctx, uVar6, uVar9, uVar13, code;
    uint64_t *head, *puVar7, *puVar10, *puVar11;
    sk_u128_t save1, save2, rc64;
    uint64_t err_out, delta, tabval, reg_h;
    bool bVar4;
    int64_t local70[2];

    ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (ctx + 0x30 < ctx) goto fatal_669fc4;
    save1 = sk_f_0066a9bc();
    head = *(uint64_t **)(ctx + 0xd0);
    if (head == 0) {
        uVar6 = sk_x_0065be08(0x6fea40, 4, 0xd);
        if (uVar6 + 0x30 < uVar6) goto fatal_669fc4;
        save2 = sk_f_0066a9bc();
        if ((uVar6 + 0x3e0 < uVar6) || (uVar6 + 0x78 < uVar6 + 0x40)) goto fatal_669fc4;
        puVar7 = (uint64_t *)sk_f_0066a404(uVar6, (uint8_t *)(uVar6 + 0x40));
        if (puVar7 == 0) {
            if (*(uint8_t *)(uVar6 + 0xc0) == 1) {
                uVar9 = sk_x_00685fb0();
                /* Continuation frame for sk_f_00667568: it may resume into
                   sk_f_0066a08c with frame values (uVar6+0x3e0, ctx, save1,
                   saved sp). */
                ctx = sk_f_00667568();
                if ((ctx & 1) == 0) {
                    uVar9 = sk_x_00685fe8();
                    head = (uint64_t *)sk_x_0066b520(uVar9, 0x40);
                    return head;
                }
                err_out = 0;
                head = (uint64_t *)sk_f_00667530(uVar9, &err_out);
                uVar9 = err_out;
                if (head != 0) {
                    delta = 0;
                    if (((uint64_t)head & 0x3fff) != 0) delta = 0x4000;
                    if ((uint64_t *)(delta + ((uint64_t)head & 0xffffffffffffc000)) == head) {
                        uVar6 = sk_x_0065be08(0x6fea40, 4, 0xd);
                        if ((uVar6 <= uVar6 + 0x3e0) && (uVar6 + 0x238 <= uVar6 + 0x270)) {
                            sk_f_00669134(uVar6, uVar6 + 0x238, uVar9);
                            uVar6 = sk_x_0065be08(0x6fea40, 4, 0xd);
                            if (uVar6 <= uVar6 + 0x30) {
                                save1 = sk_f_0066a9bc();
                                uVar9 = *(uint64_t *)(uVar6 + 0xe0);
                                uVar13 = *(uint64_t *)(uVar6 + 0xd0);
                                head[1] = *(uint64_t *)(uVar6 + 0xd8);
                                head[0] = uVar13;
                                head[2] = uVar9;
                                *(uint64_t **)(uVar6 + 0xd0) = head;
                                *(uint64_t **)(uVar6 + 0xd8) = head + 0x800;
                                *(uint64_t **)(uVar6 + 0xe0) = head;
                                if (uVar6 <= uVar6 + 0x3e0) {
                                    puVar11 = (uint64_t *)sk_f_0066ab40(uVar6, save1.lo, save1.hi);
                                    return puVar11;
                                }
                            }
                        }
                        SoftwareBreakpoint(0x5519, 0x66a1a0);
                    }
                }
                sk_x_006833d4(0x6a9ad5);   /* noreturn */
            }
            sk_f_0066ab40(uVar6, save2.lo, save2.hi);
            if (uVar6 <= uVar6 + 0x3e0) {
                sk_f_0066ab40(uVar6, save1.lo, save1.hi);
                return 0;
            }
            goto fatal_669fc4;
        }
        local70[1] = 0x4000;
        local70[0] = (int64_t)puVar7 - *(int64_t *)(*(int64_t *)(uVar6 + 0x68) + 8);
        code = ((uint64_t(*)(uint64_t, int64_t *, int64_t *))sk_g_006b6998)(
                    *(uint64_t *)(uVar6 + 0x68), local70, local70 + 1);
        if ((code & 0xff) != 0) {
            delta = (code & 0xff) * 8;
            head = (uint64_t *)(delta + 0x6b5e50);
            if (((uint64_t *)0x6b5e4f < head && &sk_g_006b5e58 + delta < (uint64_t *)0x6b5e91) &&
                head <= &sk_g_006b5e58 + delta) {
                tabval = *head;
                reg_h = code >> 0x10 & 0xffff;
                sk_x_006833d4(0x6a9e6e);   /* noreturn */
            }
            goto fatal_669fc4;
        }
        sk_f_0066a558(uVar6, (int64_t)(uVar6 + 0x40), (int64_t)puVar7);
        sk_f_0066ab40(uVar6, save2.lo, save2.hi);
        puVar11 = puVar7 + 0x800;
        rc64 = sk_x_0064e07c();
        puVar10 = puVar7;
        if ((*(uint8_t *)(rc64.hi + 0x38) & 1) == 0) {
            if ((puVar11 < puVar7) || ((uint64_t)((int64_t)puVar11 - (int64_t)puVar7) < 0x4000)) goto fatal_669fc4;
            sk_x_0067a7f0(puVar7, 0, 0x4000);
        }
    } else {
        puVar11 = *(uint64_t **)(ctx + 0xd8);
        puVar7 = *(uint64_t **)(ctx + 0xe0);
        if (puVar11 < head + 3 || head < puVar7) goto fatal_669fc4;
        uVar13 = head[1];
        uVar9 = head[0];
        *(uint64_t *)(ctx + 0xe0) = head[2];
        *(uint64_t *)(ctx + 0xd8) = uVar13;
        *(uint64_t *)(ctx + 0xd0) = uVar9;
        head[1] = 0;
        head[2] = 0;
        head[0] = 0;
        puVar10 = head;
    }
    if (ctx <= ctx + 0x3e0) {
        sk_f_0066ab40(ctx, save1.lo, save1.hi);
        delta = 0;
        if (((uint64_t)puVar10 & 0x3fff) != 0) delta = 0x4000;
        if ((uint64_t *)(delta + ((uint64_t)puVar10 & 0xffffffffffffc000)) != puVar10) {
            sk_x_006833d4(0x6a9d2f);   /* noreturn */
        }
        if (head == 0) {
            bVar4 = ((int64_t)puVar11 - (int64_t)puVar10 & 0xffffffffffffc000U) != 0;
        } else {
            if (((puVar11 < puVar10) || (puVar10 < puVar7)) ||
                ((uint64_t)((int64_t)puVar11 - (int64_t)puVar10) < 0x4000)) goto fatal_669fc4;
            sk_x_0067a7f0(puVar10, 0, 0x4000);
            bVar4 = true;
        }
        if (((puVar10 <= puVar11) && (puVar7 <= puVar10)) && (bVar4)) {
            return puVar10;
        }
    }
fatal_669fc4:
    SoftwareBreakpoint(0x5519, 0x669fc8);
}

/* FUN_0066a08c @ 0x66a08c   (est. sk_page_block_commit)
 * Ghidra: void FUN_0066a08c(uint64_t param_1)
 * Allocates a page block (continuation entry). If allocation is currently
 * permitted (sk_f_00667568 low bit), calls sk_f_00667530 to obtain a block,
 * verifies it is 0x4000-aligned, releases the region lock at +0x238, and links
 * the block into the per-cpu free list at +0xd0/+0xd8/+0xe0. Otherwise defers
 * via sk_x_0066b520(uVar5, 0x40). On any invariant violation it panics.
 * Confidence: medium
 * Notes: continuation resume target of FUN_00667568 (see 0x669db4). */
void sk_f_0066a08c(uint64_t param_1)
{
    uint64_t uVar3, uVar5, uVar6, delta;
    uint64_t *blk;
    sk_u128_t save;
    uint64_t err_out;

    uVar3 = sk_f_00667568();
    if ((uVar3 & 1) == 0) {
        uVar5 = sk_x_00685fe8();
        sk_x_0066b520(uVar5, 0x40);
        return;
    }
    err_out = 0;
    blk = (uint64_t *)sk_f_00667530(param_1, &err_out);
    uVar5 = err_out;
    if (blk != 0) {
        delta = 0;
        if (((uint64_t)blk & 0x3fff) != 0) delta = 0x4000;
        if ((uint64_t *)(delta + ((uint64_t)blk & 0xffffffffffffc000)) == blk) {
            uVar3 = sk_x_0065be08(0x6fea40, 4, 0xd);
            if (uVar3 <= uVar3 + 0x3e0) {
                if (uVar3 + 0x238 <= uVar3 + 0x270) {
                    sk_f_00669134(uVar3, uVar3 + 0x238, uVar5);
                    uVar3 = sk_x_0065be08(0x6fea40, 4, 0xd);
                    if (uVar3 <= uVar3 + 0x30) {
                        save = sk_f_0066a9bc();
                        uVar5 = *(uint64_t *)(uVar3 + 0xe0);
                        uVar6 = *(uint64_t *)(uVar3 + 0xd0);
                        blk[1] = *(uint64_t *)(uVar3 + 0xd8);
                        blk[0] = uVar6;
                        blk[2] = uVar5;
                        *(uint64_t **)(uVar3 + 0xd0) = blk;
                        *(uint64_t **)(uVar3 + 0xd8) = blk + 0x800;
                        *(uint64_t **)(uVar3 + 0xe0) = blk;
                        if (uVar3 <= uVar3 + 0x3e0) {
                            sk_f_0066ab40(uVar3, save.lo, save.hi);
                            return;
                        }
                    }
                }
            }
            SoftwareBreakpoint(0x5519, 0x66a1a0);
        }
    }
    sk_x_006833d4(0x6a9ad5);   /* noreturn */
}

/* FUN_0066a1cc @ 0x66a1cc   (est. sk_alloc_defer)
 * Ghidra: void FUN_0066a1cc(uint64_t param_1)
 * Thin shim that defers/queues an allocation request by forwarding to
 * sk_x_0066b520(param_1, 0x40). No other work is performed.
 * Confidence: high */
void sk_f_0066a1cc(uint64_t param_1)
{
    sk_x_0066b520(param_1, 0x40);
}

/* FUN_0066a1d4 @ 0x66a1d4   (est. sk_free_block_pop)
 * Ghidra: unsigned long FUN_0066a1d4(void)
 * Pops a free block from the small per-cpu 3-slot cache at context+0x3c0
 * (guarded by flags at +0xc2 bit0 / +0xc1). If all three slots are empty the
 * cache is refilled via sk_x_00686058. On a hit the slot is cleared and the
 * running count at +0x3d8 is decremented (min tracked at +0x3d9). If the
 * count hits zero it allocates a fresh region block through sk_f_00668e24
 * under the +0xc1 flag. Returns the popped block.
 * Confidence: low
 * Notes: refill path returns a (block, slot-ptr, count-ptr) triple in
 *   x0/x1/x2 (extraout_x8/x9/x10) — modeled here as block + re-derived ctx
 *   pointers; identical body to 0x66a1d8. */
uint64_t sk_f_0066a1d4(void)
{
    uint64_t ctx, blk;
    uint64_t *slot, *count;
    int64_t i;
    uint8_t cnt;

    ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (((*(uint8_t *)(ctx + 0xc2) & 1) == 0) || (*(uint8_t *)(ctx + 0xc1) == 1)) {
        slot = (uint64_t *)(ctx + 0x3c0);
        count = (uint64_t *)(ctx + 0x3d8);
        i = 3;
        do {
            if (count < slot + 1 || slot + 1 < slot) {
                SoftwareBreakpoint(0x5519, 0x66a278);
            }
            blk = *slot;
            if (blk != 0) goto pop;
            slot = slot + 1;
            i = i - 1;
        } while (i != 0);
        /* Cache empty: refill the 3 slots; x0 = first block, x1/x2 = pointers. */
        blk = sk_x_00686058();
        slot = (uint64_t *)(ctx + 0x3c0);
        count = (uint64_t *)(ctx + 0x3d8);
pop:
        *slot = 0;
        cnt = (uint8_t)*count;
        if (cnt == 0) {
            sk_x_00686020();
            ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
            *(uint8_t *)(ctx + 0xc1) = 1;
            blk = sk_x_0065be08(0x6fea40, 4, 0xd);
            if (blk <= blk + 0x3e0 && blk + 0xe8 <= blk + 0x120) {
                blk = sk_f_00668e24(blk, blk + 0xe8, 1);
                *(uint8_t *)(ctx + 0xc1) = 0;
                if (blk <= blk + 0x48) {
                    return blk;
                }
            }
            SoftwareBreakpoint(0x5519, 0x66a300);
        }
        *(uint8_t *)(ctx + 0x3d8) = cnt - 1;
        if ((uint8_t)(cnt - 1) < *(uint8_t *)(ctx + 0x3d9)) {
            *(uint8_t *)(ctx + 0x3d9) = cnt - 1;
        }
    } else {
        blk = 0;
    }
    return blk;
}

/* FUN_0066a1d8 @ 0x66a1d8   (est. sk_free_block_pop)
 * Ghidra: unsigned long FUN_0066a1d8(void)
 * Duplicate of sk_f_0066a1d4 (identical decompiled body): pops a free block
 * from the 3-slot cache at context+0x3c0, refilling via sk_x_00686058 when
 * empty, and allocating a fresh region block via sk_f_00668e24 when the
 * count reaches zero. Returns the popped block.
 * Confidence: low
 * Notes: identical to 0x66a1d4; likely a distinct entry point or alias. */
uint64_t sk_f_0066a1d8(void)
{
    uint64_t ctx, blk;
    uint64_t *slot, *count;
    int64_t i;
    uint8_t cnt;

    ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (((*(uint8_t *)(ctx + 0xc2) & 1) == 0) || (*(uint8_t *)(ctx + 0xc1) == 1)) {
        slot = (uint64_t *)(ctx + 0x3c0);
        count = (uint64_t *)(ctx + 0x3d8);
        i = 3;
        do {
            if (count < slot + 1 || slot + 1 < slot) {
                SoftwareBreakpoint(0x5519, 0x66a278);
            }
            blk = *slot;
            if (blk != 0) goto pop;
            slot = slot + 1;
            i = i - 1;
        } while (i != 0);
        blk = sk_x_00686058();
        slot = (uint64_t *)(ctx + 0x3c0);
        count = (uint64_t *)(ctx + 0x3d8);
pop:
        *slot = 0;
        cnt = (uint8_t)*count;
        if (cnt == 0) {
            sk_x_00686020();
            ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
            *(uint8_t *)(ctx + 0xc1) = 1;
            blk = sk_x_0065be08(0x6fea40, 4, 0xd);
            if (blk <= blk + 0x3e0 && blk + 0xe8 <= blk + 0x120) {
                blk = sk_f_00668e24(blk, blk + 0xe8, 1);
                *(uint8_t *)(ctx + 0xc1) = 0;
                if (blk <= blk + 0x48) {
                    return blk;
                }
            }
            SoftwareBreakpoint(0x5519, 0x66a300);
        }
        *(uint8_t *)(ctx + 0x3d8) = cnt - 1;
        if ((uint8_t)(cnt - 1) < *(uint8_t *)(ctx + 0x3d9)) {
            *(uint8_t *)(ctx + 0x3d9) = cnt - 1;
        }
    } else {
        blk = 0;
    }
    return blk;
}

/* FUN_0066a300 @ 0x66a300   (est. sk_block_alloc_region)
 * Ghidra: long FUN_0066a300(void)
 * Allocates a region block under the +0xc1 in-progress flag. Prepares the
 * region descriptor at context+0x78 via sk_f_0066a404, validates the block
 * through the callback sk_g_006b6998, then reverts the reservation with
 * sk_f_0066a558. On validation success the running total at +0x98 is advanced
 * by 0x4000 and the block is returned; otherwise 0 is returned.
 * Confidence: medium
 * Notes: callback global _DAT_006b6998; local_50[2] passed as arg buffer. */
int64_t sk_f_0066a300(void)
{
    uint64_t ctx, err;
    int64_t blk;
    sk_u128_t save;
    int64_t local50[2];

    ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (ctx <= ctx + 0x30) {
        save = sk_f_0066a9bc();
        *(uint8_t *)(ctx + 0xc1) = 1;
        if (ctx <= ctx + 0x3e0) {
            blk = sk_f_0066a404(ctx, (uint8_t *)(ctx + 0x78));
            if (blk != 0) {
                local50[1] = 0x4000;
                local50[0] = blk - *(int64_t *)(*(int64_t *)(ctx + 0xa0) + 8);
                err = ((uint64_t(*)(uint64_t, int64_t *, int64_t *))sk_g_006b6998)(
                          *(uint64_t *)(ctx + 0xa0), local50, local50 + 1);
                sk_f_0066a558(ctx, (int64_t)(ctx + 0x78), blk);
                if (err != 0) {
                    blk = 0;
                    *(int64_t *)(ctx + 0x98) = *(int64_t *)(ctx + 0x98) + 0x4000;
                }
            }
            *(uint8_t *)(ctx + 0xc1) = 0;
            sk_f_0066ab40(ctx, save.lo, save.hi);
            return blk;
        }
    }
    SoftwareBreakpoint(0x5519, 0x66a404);
}

/* FUN_0066a404 @ 0x66a404   (est. sk_region_desc_prepare)
 * Ghidra: void FUN_0066a404(unsigned long param_1, uint8_t *param_2)
 * Prepares a region descriptor (param_2) for its first allocation: checks the
 * guard flag, extends the region end (via sk_f_00669af8 when the arena is
 * exhausted), marks the descriptor active (uint8_t +1 = 1) and sets the current
 * end (+0x20) to end - 0x4000. Returns the reserved block base in x0 (Ghidra
 * types the function void but callers consume the return). Panics on overflow
 * or state violations.
 * Confidence: medium
 * Notes: Ghidra shows `void` but callers at 0x669db4/0x66a300 use the return;
 *   x0 at return holds end - 0x4000 (or 0 on the early bail). */
uint64_t sk_f_0066a404(uint64_t ctx, uint8_t *desc)
{
    uint64_t r, end, arena, newblock;

    if (ctx + 0x30 < ctx) {
fatal_6a4c8:
        SoftwareBreakpoint(0x5519, 0x66a4cc);
    }
    r = sk_f_0066a988();
    if ((r & 1) == 0) {
        sk_x_006833d4(0x6a9f4f);   /* noreturn */
    }
    if (desc[1] != 1) {
        end = *(uint64_t *)(desc + 0x20);
        if ((desc[0x30] & 1) == 0) {
            if (end <= *(uint64_t *)(desc + 8)) {
                sk_x_006833d4(0x6aa26c);   /* noreturn */
            }
        } else {
            arena = *(uint64_t *)(*(int64_t *)(desc + 0x28) + 8);
            if (*(uint64_t *)(*(int64_t *)(desc + 0x28) + 0x10) < end - arena) goto panic_6aa2e9;
            if (end == arena) {
                end = sk_f_00669af8(desc[0], 0, 0x10000, desc[0x18]);
                if (end == 0) {
                    return 0;
                }
                *(uint64_t *)(desc + 0x28) = end;
                if (end + 0x20 < end) goto fatal_6a4c8;
                end = *(int64_t *)(end + 0x10) + *(int64_t *)(end + 8);
            }
        }
        desc[1] = 1;
        newblock = end - 0x4000;
        *(uint64_t *)(desc + 0x20) = newblock;
        return newblock;
    }
    sk_x_00686084();
panic_6aa2e9:
    sk_x_006833d4(0x6aa2e9);   /* noreturn */
}

/* FUN_0066a558 @ 0x66a558   (est. sk_region_desc_release)
 * Ghidra: void FUN_0066a558(unsigned long param_1,long param_2,long param_3)
 * Reverts a region-descriptor reservation made by sk_f_0066a404: verifies the
 * descriptor's current end (+0x20) still equals the reserved block and that
 * the arena bounds are consistent, then clears the active flag (uint8_t +1).
 * Recycles via sk_x_006860bc when the descriptor was already inactive, else
 * panics on a state mismatch.
 * Confidence: medium
 * Notes: pairs with 0x66a404; panics at 0x6aa3ef / 0x6aa458 / 0x6a9f4f. */
void sk_f_0066a558(uint64_t ctx, int64_t desc, int64_t block)
{
    uint64_t r;
    int64_t arena;

    if (ctx + 0x30 < ctx) {
        SoftwareBreakpoint(0x5519, 0x66a5d8);
    }
    r = sk_f_0066a988();
    if ((r & 1) != 0) {
        if ((*(uint8_t *)(desc + 1) & 1) == 0) {
            sk_x_006860bc();
        } else if (block == *(int64_t *)(desc + 0x20)) {
            arena = *(int64_t *)(desc + 0x28);
            if (arena != 0) {
                if (*(uint64_t *)(arena + 0x10) <= (uint64_t)(block - *(int64_t *)(arena + 8))) {
                    sk_x_006833d4(0x6aa458);   /* noreturn */
                }
            }
            *(uint8_t *)(desc + 1) = 0;
            return;
        }
        sk_x_006833d4(0x6aa3ef);   /* noreturn */
    }
    sk_x_006833d4(0x6a9f4f);   /* noreturn */
}

/* FUN_0066a65c @ 0x66a65c   (est. sk_region_acquire)
 * Ghidra: void FUN_0066a65c(void)
 * Acquires the region lock at context+0x120 via sk_f_00668e24, after overflow
 * guards on the per-cpu context base. Returns silently on success; a failed or
 * overflowing acquire hits a SoftwareBreakpoint (fatal).
 * Confidence: high
 * Notes: lock region 0x120..0x158; guards 0x3e0/0x40. */
void sk_f_0066a65c(void)
{
    uint64_t ctx;

    ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (ctx <= ctx + 0x3e0 && ctx + 0x120 <= ctx + 0x158) {
        ctx = sk_f_00668e24(ctx, ctx + 0x120, 1);
        if (ctx <= ctx + 0x40) {
            return;
        }
    }
    SoftwareBreakpoint(0x5519, 0x66a6b4);
}

/* FUN_0066a6b4 @ 0x66a6b4   (est. sk_region_release)
 * Ghidra: void FUN_0066a6b4(uint64_t param_1)
 * Releases the region lock at context+0x120 via sk_f_00669134(param_1), after
 * overflow guards on the per-cpu context base. Returns silently on success; a
 * failing release hits a SoftwareBreakpoint (fatal). Counterpart of
 * sk_f_0066a65c.
 * Confidence: high
 * Notes: lock region 0x120..0x158. */
void sk_f_0066a6b4(uint64_t param_1)
{
    uint64_t ctx;

    ctx = sk_x_0065be08(0x6fea40, 4, 0xd);
    if (ctx <= ctx + 0x3e0 && ctx + 0x120 <= ctx + 0x158) {
        sk_f_00669134(ctx, ctx + 0x120, param_1);
        return;
    }
    SoftwareBreakpoint(0x5519, 0x66a70c);
}

/* FUN_0066a70c @ 0x66a70c   (est. sk_panic_msg)
 * Ghidra: void FUN_0066a70c(uint64_t param_1)
 * Always-panic helper: passes the argument straight through to the message
 * logger sk_x_006833d4 with a fixed message string (0x6a9997) and does not
 * return. The parameter is stored but unused.
 * Confidence: high
 * Notes: stack store of param_1 is a decompiler artifact; 0x6a9997 is a string
 *   address; sk_x_006833d4 is noreturn. */
void sk_f_0066a70c(uint64_t param_1)
{
    (void)param_1;
    sk_x_006833d4(0x6a9997);   /* noreturn */
}
/* ===== part 9: fragment of SKR68 ===== */

/* FUN_0066a720 @ 0x0066a720   (est. page_allocator_active)
 * Ghidra: bool FUN_0066a720(void)
 * Checks whether the page allocator is initialized by acquiring a
 * short-term reservation (4 pages, size-8 class) on the global allocator
 * metadata at 0x6fea48. If the reservation fails, an error string is
 * logged and the failure handler is invoked. Returns true when the
 * reservation succeeded.
 * Confidence: medium
 * Notes: calls sk_x_0065cc0c (reserve), sk_x_0065cbbc (log string
 * s_..._0x6b5e30), sk_f_0066a768 (fail handler). */
bool sk_f_0066a720(void)
{
    int64_t reservation;

    reservation = sk_x_0065cc0c(4, 8);
    if (reservation == 0) {
        sk_x_0065cbbc(0x6b5e30);
        sk_f_0066a768();
    }
    return reservation == 0;
}

/* FUN_0066a768 @ 0x0066a768   (est. page_allocator_fail_fallback)
 * Ghidra: void FUN_0066a768(void)
 * Fallback path taken when the page allocator reservation fails. Reads the
 * allocator state block at 0x6fea48 and, if the page count (offset 0x48)
 * fits within the supported range, derives a fresh memory offset at
 * offset 0x44 as (count * 0x8000) + 0x20000. Otherwise it re-fetches a
 * per-cpu/global pointer and stores it into the init-latch global at
 * 0x00700170, panicking if that latch is already set.
 * Confidence: medium
 * Notes: calls sk_x_0065be08 (allocator state), sk_x_006862a0,
 * sk_x_006833d4 (noreturn panic, string 0x6aa4b8); global sk_g_00700170. */
void sk_f_0066a768(void)
{
    uint32_t page_count;
    int64_t state;
    uint64_t init_val;

    state = sk_x_0065be08(0x6fea48, 4, 8);
    page_count = *(uint32_t *)(state + 0x48) * 0x8000;
    if (*(uint32_t *)(state + 0x48) >> 0x11 == 0 && page_count < 0xfffe0000) {
        *(uint32_t *)(state + 0x44) = page_count + 0x20000;
        return;
    }
    init_val = sk_x_006862a0();
    if (sk_g_00700170 == 0) {
        sk_g_00700170 = init_val;
        return;
    }
    /* noreturn */
    sk_x_006833d4(0x6aa4b8);
}

/* FUN_0066a7b8 @ 0x0066a7b8   (est. page_allocator_set_latch)
 * Ghidra: void FUN_0066a7b8(uint64_t param_1)
 * One-shot initializer for the allocator init-latch global: records the
 * supplied value into sk_g_00700170 the first time, panicking on any
 * subsequent call (latch already set).
 * Confidence: medium
 * Notes: calls sk_x_006833d4 (noreturn panic, string 0x6aa4b8); global
 * sk_g_00700170. */
void sk_f_0066a7b8(uint64_t value)
{
    if (sk_g_00700170 == 0) {
        sk_g_00700170 = value;
        return;
    }
    /* noreturn */
    sk_x_006833d4(0x6aa4b8);
}

/* FUN_0066a808 @ 0x0066a808   (est. page_allocator_reserve_region)
 * Ghidra: long * FUN_0066a808(long param_1,long param_2,long *param_3)
 * Attempts to reserve/establish a page region against the allocator state
 * block at 0x6fea48. If the allocator is inactive, it returns the state
 * block when a live region is already present, else records the requested
 * region (base, size, and descriptor) into the block and marks it active.
 * When a descriptor is missing it panics through the failure helpers.
 * Returns the state block pointer, or the block's current region pointer
 * (offset 0x10) on the inactive/error path.
 * Confidence: medium
 * Notes: calls sk_f_0066a720 (active check), sk_x_0065be08 (state),
 * sk_x_00686310/00686348/006863b8/006862d8/00686380 (panic/error helpers). */
int64_t *sk_f_0066a808(int64_t region_base, int64_t region_size, int64_t *descriptor)
{
    uint64_t active;
    int64_t *state;
    int64_t *pl;

    active = sk_f_0066a720();
    state = (int64_t *)sk_x_0065be08(0x6fea48, 4, 8);
    if ((active & 1) == 0) {
        if ((*(uint8_t *)(state + 1) & 1) != 0) {
            pl = (int64_t *)*state;
            if ((((pl != (int64_t *)0x0) && (*pl != 0)) && (pl[1] != 0)) && (pl[2] != 0)) {
                return state;
            }
            sk_x_00686310();
            goto LAB_inactive_error;
        }
    } else {
        if (*(uint8_t *)(state + 1) == 0) {
            if (region_base == 0) goto LAB_absent;
            if (((descriptor != (int64_t *)0x0) && (*descriptor != 0)) && (descriptor[1] != 0)) {
                state[2] = region_base;
                state[3] = region_size;
                *state = (int64_t)descriptor;
                *(uint8_t *)(state + 1) = 1;
                return state;
            }
LAB_inactive_error:
            sk_x_00686348();
        }
        sk_x_006863b8();
    }
    sk_x_006862d8();
LAB_absent:
    sk_x_00686380();
    {
        int64_t lv = sk_x_0065be08(0x6fea48, 4, 8);
        return *(int64_t **)(lv + 0x10);
    }
}

/* FUN_0066a8c4 @ 0x0066a8c4   (est. page_allocator_current_region)
 * Ghidra: uint8_t [16] FUN_0066a8c4(void)
 * Loads and returns the 16-uint8_t region descriptor currently recorded in
 * the allocator state block (offset 0x10) at 0x6fea48.
 * Confidence: medium
 * Notes: calls sk_x_0065be08 (allocator state); 16-uint8_t return via
 * sk_u128_t. */
sk_u128_t sk_f_0066a8c4(void)
{
    int64_t state;

    state = sk_x_0065be08(0x6fea48, 4, 8);
    return *(sk_u128_t *)(state + 0x10);
}

/* FUN_0066a8f4 @ 0x0066a8f4   (est. page_allocator_region_init)
 * Ghidra: void FUN_0066a8f4(unsigned long param_1,uint64_t param_2,uint64_t param_3)
 * Initializes a page-region descriptor at the given address, trapping via
 * SoftwareBreakpoint if the 16-uint8_t header would wrap. Validates the
 * region through sk_x_0067cfe0 and, on success, fills the descriptor with
 * an object base (offset 0x10 = 0), a size of 0x100 (offset 0x18), and the
 * two supplied arguments (offsets 0x20, 0x28). Panics on validation
 * failure.
 * Confidence: medium
 * Notes: calls SoftwareBreakpoint(0x5519,0x66a954), sk_x_0067cfe0
 * (validate), sk_x_006833d4 (noreturn panic, string 0x6a8797). */
void sk_f_0066a8f4(uint64_t region, uint64_t arg2, uint64_t arg3)
{
    int validate;

    if (region + 0x10 < region) {
        /* noreturn */
        SoftwareBreakpoint(0x5519, 0x66a954);
    }
    validate = sk_x_0067cfe0(region, 0);
    if (validate == 0) {
        *(uint64_t *)(region + 0x10) = 0;
        *(uint64_t *)(region + 0x18) = 0x100;
        *(uint64_t *)(region + 0x20) = arg2;
        *(uint64_t *)(region + 0x28) = arg3;
        return;
    }
    /* noreturn */
    sk_x_006833d4(0x6a8797);
}

/* FUN_0066a988 @ 0x0066a988   (est. page_allocator_region_valid)
 * Ghidra: bool FUN_0066a988(long param_1)
 * Tests whether the page-region at param_1 currently holds a live object:
 * compares the region's object pointer (offset 0x10) against the current
 * per-cpu/global token and returns true when they match.
 * Confidence: medium
 * Notes: calls sk_x_00661318 (current token), thunk sk_x_006551c4
 * (compare). */
bool sk_f_0066a988(int64_t region)
{
    uint64_t token;
    int cmp;

    token = sk_x_00661318();
    cmp = sk_x_006551c4(token, *(uint64_t *)(region + 0x10));
    return cmp != 0;
}

/* FUN_0066a9bc @ 0x0066a9bc   (est. page_allocator_region_reserve_slot)
 * Ghidra: uint8_t [16] FUN_0066a9bc(long param_1)
 * Reserves a slot out of the page-region at param_1, returning a 16-uint8_t
 * {kind, index} pair. When the region holds no live object (token
 * mismatch), it validates the region, requires a null object pointer and a
 * low uint8_t of 0 in the size field, then installs the current token as the
 * object (offset 0x10) and bumps the size field by 0x101, returning
 * {kind=0, index=old_size+0x100}. Otherwise the object is live: it
 * validates the size-field low uint8_t is not 0xff or 0, increments the size
 * field by 1, and returns {kind=1, index=size}. Panics on validation or
 * state violations.
 * Confidence: medium
 * Notes: 16-uint8_t return via sk_u128_t (lo=kind, hi=index); calls
 * sk_x_00661318, thunk sk_x_006551c4, sk_x_0067cffc (validate),
 * sk_x_006833d4 (noreturn panic: strings 0x6a8797, 0x6aa97d, 0x6aaa08,
 * 0x6aa8e9, 0x6aa86b). */
sk_u128_t sk_f_0066a9bc(int64_t region)
{
    int cmp;
    uint64_t token;
    uint64_t index;
    uint64_t kind;
    uint64_t size;

    token = sk_x_00661318();
    cmp = sk_x_006551c4(token, *(uint64_t *)(region + 0x10));
    if (cmp == 0) {
        if (sk_x_0067cffc(region) != 0) {
            /* noreturn */
            sk_x_006833d4(0x6a8797);
        }
        if (*(int64_t *)(region + 0x10) != 0) {
            /* noreturn */
            sk_x_006833d4(0x6aa97d);
        }
        size = *(uint64_t *)(region + 0x18);
        if ((size & 0xff) != 0) {
            /* noreturn */
            sk_x_006833d4(0x6aaa08);
        }
        index = size + 0x100;
        token = sk_x_00661318();
        *(uint64_t *)(region + 0x10) = token;
        *(uint64_t *)(region + 0x18) = size + 0x101;
        kind = 0;
    } else {
        index = *(uint64_t *)(region + 0x18);
        if (((uint32_t)index & 0xff) == 0xff) {
            /* noreturn */
            sk_x_006833d4(0x6aa8e9);
        }
        if ((index & 0xff) == 0) {
            /* noreturn */
            sk_x_006833d4(0x6aa86b);
        }
        *(uint64_t *)(region + 0x18) = index + 1;
        kind = 1;
    }
    return (sk_u128_t){ .lo = kind, .hi = index };
}

/* FUN_0066ab40 @ 0x0066ab40   (est. page_allocator_region_release_slot)
 * Ghidra: void FUN_0066ab40(long param_1,uint8_t param_2,unsigned long param_3)
 * Releases a previously reserved slot from the page-region at param_1.
 * Requires the region to hold the current live object (token match) and
 * the size field to equal param_3 + 1, and the low uint8_t of param_3 to
 * match the parity bit param_2. If param_2 bit 0 is clear it also verifies
 * the low uint8_t is 0, clears the object pointer and rewinds the size field
 * to param_3, then re-validates the region. Otherwise it just rewinds the
 * size field to param_3. Panics on any mismatch.
 * Confidence: medium
 * Notes: calls sk_x_00661318, thunk sk_x_006551c4, indirect call at
 * region+0x20, sk_x_0067d02c (validate), sk_x_006833d4 (noreturn panic:
 * strings 0x6aaa84, 0x6aaaf4, 0x6aab8f, 0x6a8797). */
void sk_f_0066ab40(int64_t region, uint8_t parity, uint64_t index)
{
    int cmp;
    uint64_t token;

    token = sk_x_00661318();
    cmp = sk_x_006551c4(token, *(uint64_t *)(region + 0x10));
    if (cmp == 0) {
        /* noreturn */
        sk_x_006833d4(0x6aaa84);
    }
    if (index + 1 != *(int64_t *)(region + 0x18)) {
        /* noreturn */
        sk_x_006833d4(0x6aaaf4);
    }
    if (((index & 0xff) != 0) != (bool)(parity & 1)) {
        /* noreturn */
        sk_x_006833d4(0x6aab8f);
    }
    if ((parity & 1) == 0) {
        (*(void (**)(void))(region + 0x20))(*(uint64_t *)(region + 0x28));
        token = sk_x_00661318();
        cmp = sk_x_006551c4(token, *(uint64_t *)(region + 0x10));
        if (cmp == 0) {
            /* noreturn */
            sk_x_006833d4(0x6aaa84);
        }
        if (index + 1 != *(int64_t *)(region + 0x18)) {
            /* noreturn */
            sk_x_006833d4(0x6aaaf4);
        }
        if ((index & 0xff) != 0) {
            /* noreturn */
            sk_x_006833d4(0x6aab8f);
        }
        *(uint64_t *)(region + 0x10) = 0;
        *(uint64_t *)(region + 0x18) = index;
        if (sk_x_0067d02c(region) != 0) {
            /* noreturn */
            sk_x_006833d4(0x6a8797);
        }
    } else {
        *(uint64_t *)(region + 0x18) = index;
    }
}

/* FUN_0066ad54 @ 0x0066ad54   (est. page_allocator_alloc_frame)
 * Ghidra: long FUN_0066ad54(void)
 * Allocates a free frame from the page allocator. Reads the allocator
 * state block at 0x6fea48, reserves a slot from the region descriptor
 * (sk_f_0066a9bc) to obtain a {kind, index} pair, and obtains the current
 * free-frame free-list head from state offset 0x30. If no free-list head
 * exists, it either verifies the region quota before growing, runs the
 * region-fill callback, or acquires a fresh free-list page (sk_f_0066af84)
 * and pulls a frame from it via the list head callback; on success it
 * links the new free-list into the state. Frames are allocated by scanning
 * the free-list page's 64-bit slot bitmap, bit-reversing each word and
 * locating the highest set bit via LZCOUNT to pick a free slot, then
 * relinking the list when slots remain. Returns the allocated frame
 * pointer, or releases the reservation and panics on exhaustion/state
 * errors.
 * Confidence: medium
 * Notes: calls sk_f_0066a9bc, sk_f_0066ab40, sk_f_0066af84,
 * sk_f_0066afe8, sk_x_0066b038, sk_x_0065be08 (state), sk_x_006833d4
 * (noreturn panic: 0x6aac78, 0x6aacda, 0x6aad25, 0x6aad67); uses LZCOUNT
 * intrinsic and 0x8000-page/0x100-slot accounting. */
int64_t sk_f_0066ad54(void)
{
    int16_t slot_count;
    int64_t *state;
    uint64_t index;
    uint64_t kind;
    int64_t frame;
    int64_t result;
    int64_t lvar;
    uint64_t bit_index;
    uint64_t word;
    uint64_t rev;
    uint64_t *flist;
    sk_u128_t slot;

    state = (int64_t *)sk_x_0065be08(0x6fea48, 4, 8);
    slot = sk_f_0066a9bc(*(uint64_t *)(*state + 0x10));
    index = slot.hi;
    kind = slot.lo;
    flist = (uint64_t *)state[6];
    if (flist == (uint64_t *)0x0) {
        if (*(uint32_t *)((int64_t)state + 0x44) <= *(uint32_t *)(state + 8)) {
            sk_f_0066ab40(*(uint64_t *)(*state + 0x10), kind, index);
            /* noreturn */
            sk_x_006833d4(0x6aac78);
        }
        if (((kind & 1) != 0) &&
            (result = (*(int64_t (**)(void))(*state + 0x18))(), result != 0)) {
            goto LAB_release;
        }
        flist = (uint64_t *)sk_f_0066af84();
        if (flist == (uint64_t *)0x0) {
            sk_f_0066ab40(*(uint64_t *)(*state + 0x10), kind, index);
            /* noreturn */
            sk_x_006833d4(0x6aacda);
        }
        result = (*(int64_t (**)(void))(*state + 8))();
        if (result == 0) {
            sk_f_0066afe8(flist);
            sk_f_0066ab40(*(uint64_t *)(*state + 0x10), kind, index);
            /* noreturn */
            sk_x_006833d4(0x6aad25);
        }
        flist[1] = 0;
        flist[0] = 0;
        flist[3] = 0;
        flist[2] = 0;
        flist[4] = 0;
        flist[5] = result;
        flist[7] = 0;
        flist[8] = 0;
        flist[6] = 0;
        sk_x_0066b038(state + 4, flist);
        *(int32_t *)(state + 8) = (int32_t)state[8] + 0x100;
    } else {
        state[6] = flist[6];
        flist[6] = 0;
    }
    lvar = 0;
    result = 0;
    do {
        word = *(uint64_t *)((int64_t)flist + lvar);
        if (word != 0xffffffffffffffff) {
            rev = (~word & 0xaaaaaaaaaaaaaaaa) >> 1 | (~word & 0x5555555555555555) << 1;
            rev = (rev & 0xcccccccccccccccc) >> 2 | (rev & 0x3333333333333333) << 2;
            rev = (rev & 0xf0f0f0f0f0f0f0f0) >> 4 | (rev & 0xf0f0f0f0f0f0f0f) << 4;
            rev = (rev & 0xff00ff00ff00ff00) >> 8 | (rev & 0xff00ff00ff00ff) << 8;
            rev = (rev & 0xffff0000ffff0000) >> 0x10 | (rev & 0xffff0000ffff) << 0x10;
            rev = LZCOUNT(rev >> 0x20 | rev << 0x20);
            *(uint64_t *)((int64_t)flist + lvar) = (uint64_t)1 << (rev & 0x3f) | word;
            result = (flist[5] + rev * 0x40) - result;
            if (result != 0) {
                slot_count = *(int16_t *)(flist + 4);
                *(uint16_t *)(flist + 4) = (uint16_t)(slot_count + 1);
                if ((uint16_t)(slot_count + 1) < 0x100) {
                    flist[6] = state[6];
                    state[6] = (int64_t)flist;
                }
                goto LAB_release;
            }
            break;
        }
        result = result - 0x1000;
        lvar = lvar + 8;
    } while (lvar != 0x20);
    /* noreturn */
    sk_x_006833d4(0x6aad67);

LAB_release:
    sk_f_0066ab40(*(uint64_t *)(*state + 0x10), kind, index);
    return result;
}

/* FUN_0066af84 @ 0x0066af84   (est. page_allocator_new_freelist)
 * Ghidra: void FUN_0066af84(void)
 * Obtains a fresh free-list page from the allocator state block at
 * 0x6fea48: reads the current list head at state offset 0x28 and, if
 * present, pops it (moving its next link into the head slot). When no
 * free-list page is available it dispatches through an indirect allocator
 * callback at state offset 0x0. Traps via SoftwareBreakpoint if the popped
 * page's internal bounds would wrap (next <= next+0x48 fails).
 * Confidence: medium
 * Notes: calls sk_x_0065be08 (state), SoftwareBreakpoint(0x5519,0x66afe8);
 * decompiler notes a non-recoverable jumptable at 0x0066afe0. */
void sk_f_0066af84(void)
{
    uint64_t *flist;
    uint64_t head;

    flist = (uint64_t *)sk_x_0065be08(0x6fea48, 4, 8);
    head = flist[5];
    if (head == 0) {
        /* noreturn (indirect jumptable dispatch) */
        (*(void (**)(void))*flist)();
        return;
    }
    flist[5] = *(uint64_t *)(head + 0x30);
    if (head <= head + 0x48) {
        return;
    }
    /* noreturn */
    SoftwareBreakpoint(0x5519, 0x66afe8);
}

/* FUN_0066afe8 @ 0x0066afe8   (est. page_allocator_freelist_push)
 * Ghidra: void FUN_0066afe8(uint64_t *param_1)
 * Pushes a free-list page onto the allocator's free-list head: zeroes all
 * of the page's fields except the current head pointer (state offset
 * 0x28), which is captured and stored as the new page's forward link
 * (offset 0x30), then makes the page the new head.
 * Confidence: medium
 * Notes: calls sk_x_0065be08 (allocator state). */
void sk_f_0066afe8(uint64_t *flist)
{
    int64_t state;
    uint64_t head;

    state = sk_x_0065be08(0x6fea48, 4, 8);
    head = *(uint64_t *)(state + 0x28);
    flist[1] = 0;
    flist[0] = 0;
    flist[3] = 0;
    flist[2] = 0;
    flist[5] = 0;
    flist[4] = 0;
    flist[6] = head;
    flist[7] = 0;
    flist[8] = 0;
    *(uint64_t **)(state + 0x28) = flist;
}
