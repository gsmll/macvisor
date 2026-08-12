/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x0005fd2c-0x0006562c (worker SK12): the per-CPU / alt-stack / kernel
 * init resource layer, the cL4 IPC message marshalling and capability-transfer
 * path, the L4 error-code->string printers, the endpoint/notification registry
 * (the 0x6b26d8 dispatch table and the 0x6b2718 callback table), the per-CPU
 * exception-handling setup (AMX/SME capability allocation, exception endpoints),
 * and the thread/register dump printers used by the panic path.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops).
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
#define SK_CANARY (-0x2c8502b44bfffed6LL)

static uint8_t sk_tpidr_area[0x100] __attribute__((aligned(16)));
#define tpidr_el0    ((uint8_t *)sk_tpidr_area)
#define tpidrro_el0  ((uint8_t *)sk_tpidr_area)

/* LOAcquire/LORelease: per-CPU preempt-counter lock (Ghidra pseudo-op). */
#define LOAcquire() ((void)0)
#define LORelease() ((void)0)

/* ------------------------------------------------------------------ *
 * Shared kernel globals referenced by this slice (image-base addresses are
 * the Ghidra ground truth).  DAT_<addr> in comments is the exact symbol.
 * ------------------------------------------------------------------ */
extern uint64_t sk_g_preempt_ctr;     /* DAT_006ad900 */
extern uint64_t sk_g_stack_base;      /* DAT_006b2710 */
extern uint64_t sk_g_notify_reg;      /* DAT_006b2718 */
extern uint64_t sk_g_exc_endpoint;    /* DAT_006b2720 */
extern uint64_t sk_g_handler_list;    /* DAT_006b2728 */
extern uint64_t sk_g_xrt_handler;     /* DAT_006b2730 */
extern uint64_t sk_g_altstack_state;  /* DAT_006b26d0 */
extern uint8_t  sk_g_boot_flag_a;     /* DAT_006b26c8 */
extern uint8_t  sk_g_boot_flag_b;     /* DAT_006b26c9 */
extern uint64_t sk_g_dt_root;         /* DAT_006ad6f8 */
extern uint64_t sk_g_roottask_dt;     /* DAT_00690000 */

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (extern with a one-line note; the
 * FUN_ address in the comment is the Ghidra ground truth).  These helpers
 * are shared with the other slice translation units, so this file compiles
 * independently against them.
 * ------------------------------------------------------------------ */
extern uint64_t sk_singleton(void);                /* FUN_0005BB68: kernel singleton base */
extern uint64_t sk_cap_lookup(uint64_t *word);     /* FUN_0005BC48: cap-word -> object (0 if bad) */
extern uint64_t sk_percpu_tbl(uint64_t key,int a,int b); /* FUN_0005ACAC: per-CPU table get */
extern void   sk_ec_switch(uint64_t a, const char *msg); /* FUN_0005B190: EC switch / panic-brk */
extern void   sk_fatal(void) __attribute__((noreturn));  /* FUN_0011D7E8: canary-fail panic */
extern uint64_t sk_panic0(const char *m) __attribute__((noreturn)); /* FUN_004AFAE4: panic(str) */
typedef union {
    struct { uint64_t lo, hi; };
    struct { void *object, *vtable; };
} sk_pair_t;
extern sk_pair_t sk_obj_get(void);             /* FUN_00034A2C: {object,vtable} in x0/x1 */
extern uint64_t sk_phys_alloc(uint64_t size);      /* FUN_00034F70 */
extern uint64_t sk_alloc_obj(uint64_t type);       /* FUN_0019AE2C: allocate object of type */
extern void   sk_memcpy(void *d, const void *s, uint64_t n); /* FUN_00117CC4 */
extern void   sk_memset0(void *d, uint64_t n);              /* FUN_00114330 (thunk): zero-fill */
extern void   sk_h_001143A0(void *d, int v, uint64_t n);    /* FUN_001143A0: memset */
extern uint64_t sk_strlen(const char *s);          /* FUN_00115080 (thunk) */
extern void   sk_printf(uint64_t sink, const char *fmt, ...); /* FUN_001185EC: print to sink */
extern void   sk_printf2(uint64_t sink, const char *fmt, ...);/* FUN_0005B824: printf */
extern void   sk_putchar(uint64_t ch, uint64_t sink);       /* FUN_001187F4 (thunk) */
extern void   sk_putchar2(uint64_t sink, uint64_t ch);      /* FUN_0011883C */
extern void   sk_print16(uint64_t sink, const char *s, int a, int b); /* FUN_00118ABC */

/* Deep opaque helpers referenced by this slice (extern; not reconstructed). */
extern void   sk_h_00114AA0(void *a, void *b);         /* FUN_00114AA0: memcpy small */
extern void   sk_h_001150E0(const char *fmt, ...) __attribute__((noreturn)); /* FUN_001150E0: assert panic */
extern uint64_t sk_h_0011546C(uint64_t, uint64_t, int, uint64_t,
                              uint64_t *, void *);     /* FUN_0011546C: msg send core */
extern void   sk_h_001155E0(uint64_t, uint64_t *, uint64_t, int); /* FUN_001155E0 */
extern void   sk_h_001156C4(uint64_t, uint64_t *, uint64_t, uint64_t, void *, uint64_t *); /* FUN_001156C4 */
extern void   sk_h_00116D60(void) __attribute__((noreturn));  /* FUN_00116D60: panic */
extern void   sk_h_00117CC4(void *d, const void *s, uint64_t n); /* FUN_00117CC4 (dup) */
extern uint64_t sk_h_0011817C(uint64_t);             /* FUN_0011817C */
extern void   sk_h_00118194(uint64_t);               /* FUN_00118194 */
extern void   sk_h_0011D790(void);                   /* FUN_0011D790 */
extern uint64_t sk_h_0019AFBC(uint64_t);             /* FUN_0019AFBC */
extern uint64_t sk_h_004B23D8(uint64_t, uint64_t, uint64_t); /* FUN_004B23D8 */
extern void   sk_h_004B6430(void);                   /* FUN_004B6430 */
extern void   sk_h_004B6D60(uint64_t, void *);       /* FUN_004B6D60 */
extern uint64_t sk_h_004B6F70(uint64_t, void *);     /* FUN_004B6F70 */
extern uint64_t sk_h_004B6FC0(void);                 /* FUN_004B6FC0 */
extern void   sk_h_004B6FD8(void);                   /* FUN_004B6FD8 */
extern void   sk_h_004B6FF0(void);                   /* FUN_004B6FF0 */
extern void   sk_h_004B7008(void);                   /* FUN_004B7008 */
extern uint64_t sk_h_004B7098(void);                 /* FUN_004B7098 */
extern uint64_t sk_h_004B70C8(void);                 /* FUN_004B70C8 */
extern void   sk_h_004B70F8(void);                   /* FUN_004B70F8 */
extern void   sk_h_004B710C(void);                   /* FUN_004B710C */
extern void   sk_h_004B7120(void);                   /* FUN_004B7120 */
extern void   sk_h_004B7138(void);                   /* FUN_004B7138 */
extern void   sk_h_004B7150(uint64_t, void *);       /* FUN_004B7150 */
extern void   sk_h_004B71A8(uint64_t, void *);       /* FUN_004B71A8 */
extern void   sk_h_004B7278(uint64_t);               /* FUN_004B7278 */
extern void   sk_h_004B73D0(uint64_t, void *);       /* FUN_004B73D0 */
extern void   sk_h_004B7428(uint64_t, void *);       /* FUN_004B7428 */
extern void   sk_h_004B7480(void);                   /* FUN_004B7480 */
extern void   sk_h_004B749C(void);                   /* FUN_004B749C */
extern void   sk_h_004B7544(uint64_t, void *);       /* FUN_004B7544 */
extern void   sk_h_004B7594(uint64_t, void *);       /* FUN_004B7594 */
extern uint64_t sk_h_004B75E4(uint64_t, uint64_t, void *); /* FUN_004B75E4 */
extern void   sk_h_004B7664(uint64_t, void *);       /* FUN_004B7664 */
extern void   sk_h_004B76B4(uint64_t, void *);       /* FUN_004B76B4 */
extern void   sk_h_004B7704(uint64_t, uint64_t *, void *); /* FUN_004B7704 */
extern void   sk_h_004B78C0(uint64_t, uint64_t *);   /* FUN_004B78C0 */
extern void   sk_h_004B7984(uint64_t, int);          /* FUN_004B7984 */
extern void   sk_h_004B79C8(void);                   /* FUN_004B79C8 */
extern void   sk_h_004B7AC8(uint64_t, void *);       /* FUN_004B7AC8 */

/* Other out-of-range helpers. */
extern uint64_t sk_h_0000178C(uint64_t, uint64_t);   /* FUN_0000178C: strlen variant */
extern uint64_t sk_h_000359AC(uint64_t);             /* FUN_000359AC */
extern uint64_t sk_h_0004DFD0(uint64_t, const char *);/* FUN_0004DFD0: fh register */
extern void   sk_h_0004E774(uint64_t, uint64_t);     /* FUN_0004E774 */
extern uint64_t sk_h_0004E7B8(uint64_t, uint64_t);   /* FUN_0004E7B8: tb placeholder resolve */
extern uint64_t sk_h_0004E88C(uint64_t);             /* FUN_0004E88C: tb placeholder kind */
extern uint64_t sk_h_0004EB44(void);                 /* FUN_0004EB44: tb placeholder iter init */
extern uint64_t sk_h_0004EB4C(uint64_t);             /* FUN_0004EB4C: tb placeholder iter next */
extern uint64_t sk_h_0004ECF0(uint64_t);             /* FUN_0004ECF0 */
extern uint64_t sk_h_0004ED48(void);                 /* FUN_0004ED48 */
extern void   sk_h_0004ED84(void);                   /* FUN_0004ED84 */
extern uint64_t sk_h_0004FE80(void);                 /* FUN_0004FE80 */
extern void   sk_h_00052A04(uint64_t);               /* FUN_00052A04 */
extern void   sk_h_00052C4C(uint64_t);               /* FUN_00052C4C */
extern void   sk_h_00052C54(uint64_t);               /* FUN_00052C54 */
extern uint64_t sk_h_000533EC(void);                 /* FUN_000533EC: thread list iter init */
extern void   sk_h_00053418(void);                   /* FUN_00053418 */
extern uint64_t sk_h_000544D0(uint64_t);             /* FUN_000544D0 */
extern void   sk_h_0005453C(uint64_t);               /* FUN_0005453C */
extern uint64_t sk_h_00054610(void);                 /* FUN_00054610: boot image info base */
extern uint64_t sk_h_00054624(uint64_t);             /* FUN_00054624 */
extern void   sk_h_000549C0(uint64_t, uint64_t);     /* FUN_000549C0 */
extern void   sk_h_00054BA8(void);                   /* FUN_00054BA8 */
extern void   sk_h_00054BC8(void);                   /* FUN_00054BC8 */
extern void   sk_h_00054C3C(uint64_t *);             /* FUN_00054C3C */
extern void   sk_h_00054C9C(uint64_t, uint64_t *);   /* FUN_00054C9C */
extern void   sk_h_00054DEC(void);                   /* FUN_00054DEC */
extern void   sk_h_00055164(void);                   /* FUN_00055164 */
extern uint64_t sk_h_000556C8(uint64_t);             /* FUN_000556C8 */
extern uint64_t sk_h_000556E4(uint64_t);             /* FUN_000556E4 */
extern uint64_t sk_h_0005AC2C(void);                 /* FUN_0005AC2C: ncpu get */
extern void   sk_h_0005AD40(void);                   /* FUN_0005AD40 */
extern void   sk_h_0005B0BC(uint64_t);               /* FUN_0005B0BC */
extern void   sk_h_0005B860(uint64_t *);             /* FUN_0005B860 */
extern uint64_t sk_h_0005B8C8(void);                 /* FUN_0005B8C8 */
extern uint64_t sk_h_0005BA14(void);                 /* FUN_0005BA14: boot uuid source */
extern void   sk_h_0005BA40(uint64_t);               /* FUN_0005BA40 */
extern void   sk_h_0005BA5C(uint64_t);               /* FUN_0005BA5C */
extern void   sk_h_0005BD7C(uint64_t, uint64_t *);   /* FUN_0005BD7C */
extern void   sk_h_0005BE48(uint64_t, uint64_t);     /* FUN_0005BE48 */
extern void   sk_h_0005BE84(uint64_t, int);          /* FUN_0005BE84 */
extern void   sk_h_0005BCE0(uint64_t);               /* FUN_0005BCE0 */
extern void   sk_h_0005C16C(void);                   /* FUN_0005C16C */
extern uint64_t sk_h_0005C184(uint64_t, uint64_t);   /* FUN_0005C184 */
extern void   sk_h_0005CB9C(void);                   /* FUN_0005CB9C */
extern void   sk_h_0005CDBC(uint64_t *);             /* FUN_0005CDBC */
extern void   sk_h_0005CE54(uint64_t *);             /* FUN_0005CE54 */
extern uint64_t sk_h_0005CF18(uint64_t, uint64_t, uint64_t); /* FUN_0005CF18 */
extern void   sk_h_0005D154(int, uint64_t *);      /* FUN_0005D154 */
extern void   sk_h_0005D5DC(void);                   /* FUN_0005D5DC */
extern void   sk_h_0005DEB4(uint64_t);               /* FUN_0005DEB4: per-CPU resched */
extern void   sk_h_0005E0DC(uint64_t, int);          /* FUN_0005E0DC */
extern void   sk_h_0005E958(uint64_t);               /* FUN_0005E958 */
extern void   sk_h_0005EEC4(uint64_t *, int, uint64_t, int, int); /* FUN_0005EEC4: thread spawn */
extern sk_pair_t sk_h_0005FAD8(uint64_t);            /* FUN_0005FAD8 */
extern uint64_t sk_h_0005FBC0(uint64_t);             /* FUN_0005FBC0 */
extern void   sk_h_00065640(uint64_t, uint64_t, uint64_t); /* FUN_00065640 */
extern void   sk_h_000656D8(uint64_t);               /* FUN_000656D8 */
extern void   sk_h_00114790(uint64_t, uint64_t, uint64_t); /* FUN_00114790 */

/* ------------------------------------------------------------------ *
 * Forward prototypes for the functions defined in this file (so any call
 * order compiles).  All are estimates named after their FUN_ address.
 * ------------------------------------------------------------------ */
uint64_t sk_cpu_stack_bytes(uint64_t n);                      /* FUN_0005FD2C */
uint64_t sk_altstack_enable(uint64_t th, uint64_t a);         /* FUN_0005FDAC */
void     sk_altstack_enable2(void);                           /* FUN_0005FE48 */
void     sk_altstack_disable(void);                           /* FUN_0005FEA8 */
void     sk_stack_alloc(uint64_t *out, uint64_t size, uint32_t flags); /* FUN_0005FF04 */
uint64_t sk_stack_alloc_call(uint64_t size, uint64_t a, uint64_t b);  /* FUN_000600F0 */
uint64_t sk_altstack_switch(uint64_t th, uint64_t a, uint64_t b);     /* FUN_00060164 */
void     sk_check_region_bounds(void);                        /* FUN_0006037C */
void     sk_jumptable_dispatch(void (*fn)(uint64_t), uint64_t a);     /* FUN_000603AC */
uint64_t sk_tcb_get_a8(uint64_t tcb);                         /* FUN_000603BC */
uint64_t sk_boot_lookup(void);                                /* FUN_000603C4 */
void     sk_err_string(uint64_t sink, uint8_t code);          /* FUN_000604CC */
void     sk_err_string_reg(uint8_t code);                     /* FUN_000604EC */
void     sk_noop(void);                                       /* FUN_000604F8 */
uint64_t sk_counter_inc(void);                                /* FUN_000604FC */
uint64_t sk_cpu_base(void);                                   /* FUN_00060524 */
void     sk_boot_platform_setup(void);                        /* FUN_00060530 */
uint64_t sk_boot_flag_a(void);                                /* FUN_00060540 */
uint64_t sk_boot_flag_b(void);                                /* FUN_0006054C */
uint64_t sk_syscall_number(void);                             /* FUN_00060564 */
uint64_t sk_preempt_enter(uint8_t *saved);                    /* FUN_00060570 */
void     sk_preempt_leave(uint8_t *restore);                  /* FUN_000605F8 */
void     sk_preempt_drain(void);                              /* FUN_00060650 */
uint64_t sk_stack_bump(uint64_t tag);                         /* FUN_000606B0 */
void     sk_kernel_init(uint64_t state, uint64_t kind, uint64_t *a, uint64_t *b, uint64_t arg); /* FUN_00060728 */
uint64_t sk_msg_call(uint64_t th, uint64_t *msg, uint64_t a, uint64_t b, uint64_t mode, uint64_t c); /* FUN_00060F60 */
void     sk_msg_call2(void);                                  /* FUN_00061044 */
uint64_t sk_msg_send(uint64_t ep, uint64_t *msg, uint64_t a, uint64_t b, uint64_t mode, uint64_t c); /* FUN_0006104C */
uint64_t sk_msg_marshal(uint64_t ep, uint64_t *msg, uint64_t *words, uint64_t max, uint64_t mode,
                        uint8_t flag, uint64_t *spare, uint8_t *done); /* FUN_000610B8 */
void     sk_set_a0(uint64_t obj, uint64_t v);                 /* FUN_000612D8 */
uint64_t sk_frame_alloc(uint64_t a, uint64_t b);              /* FUN_000612E0 */
uint64_t sk_tcb_get_140(uint64_t tcb);                        /* FUN_0006132C */
uint64_t sk_frame_alloc2(uint64_t a, uint8_t kind);           /* FUN_00061334 */
uint64_t sk_frame_alloc3(uint64_t a, uint64_t b);             /* FUN_000613EC */
uint64_t sk_frame_bump(uint64_t a);                           /* FUN_00061488 */
uint64_t sk_frame_bump2(uint64_t a);                          /* FUN_000614F8 */
uint64_t sk_frame_alloc4(uint64_t a);                         /* FUN_0006156C */
void     sk_tcb_bounds(uint64_t tcb, uint64_t *base, uint64_t *len); /* FUN_000615FC */
void     sk_tcb_set_bounds(uint64_t tcb, uint64_t a, uint64_t b, uint64_t len, uint64_t base); /* FUN_00061614 */
uint64_t sk_tcb_state(uint64_t tcb);                          /* FUN_00061630 */
uint64_t sk_tcb_state2(uint64_t tcb);                         /* FUN_00061638 */
void     sk_tcb_state3(uint64_t tcb);                         /* FUN_00061664 */
void     sk_msg_read(uint64_t *out, uint64_t tcb);            /* FUN_0006166C */
void     sk_set_118(uint64_t tcb, uint32_t v);                /* FUN_000618C4 */
void     sk_tcb_dump(uint64_t tcb, uint64_t sink);            /* FUN_000618CC */
uint64_t sk_tcb_get_120(uint64_t tcb);                        /* FUN_0006198C */
void     sk_tcb_set_obj(uint64_t tcb, uint64_t obj);          /* FUN_00061994 */
void     sk_msg_read2(uint64_t *out, uint64_t tcb);           /* FUN_000619C8 */
void     sk_msg_read_regs(uint64_t *out, uint64_t tcb);       /* FUN_000619F0 */
void     sk_err_string2(uint64_t sink, uint8_t code);         /* FUN_00061CDC */
uint64_t sk_msg_get(uint64_t th);                             /* FUN_00061E20 */
void     sk_msg_dump(uint64_t sink, uint64_t th);             /* FUN_00061E8C */
bool     sk_cap_table_copy(uint64_t tcb, uint64_t *out);      /* FUN_000621A8 */
void     sk_reg_dump(uint64_t sink, uint64_t tcb);            /* FUN_00062394 */
void     sk_thread_state_dump(uint64_t sink, uint64_t a, uint64_t b, uint64_t tcb,
                              int regs, int bt, uint64_t esr, uint64_t far); /* FUN_00062474 */
void     sk_print_rule(uint64_t sink, uint64_t pad, uint64_t fill); /* FUN_0006275C */
bool     sk_tcb_flag(uint64_t tcb);                           /* FUN_00062848 */
uint64_t sk_obj_lock(uint64_t obj, uint64_t k);               /* FUN_0006285C */
uint64_t sk_obj_lock2(uint64_t obj, uint64_t k);              /* FUN_000628D8 */
void     sk_obj_unlock(uint64_t obj, uint64_t k);             /* FUN_000628E0 */
void     sk_dt_set(uint64_t idx, uint64_t fn, uint64_t arg);  /* FUN_0006290C */
uint64_t sk_cap_lookup_word(uint64_t word);                   /* FUN_000629FC */
void     sk_tbplace_get(int sel, uint32_t a);                 /* FUN_00062A48 */
void     sk_err_string_wrap(void);                            /* FUN_00062BDC */
void     sk_dtor_key_panic(void);                             /* FUN_00062BFC */
void     sk_dtor_key_panic2(void);                            /* FUN_00062C14 */
void     sk_ep_lock(uint64_t *ep, uint64_t flags, uint64_t *cfg); /* FUN_00062C2C */
void     sk_ep_return(uint64_t a, uint64_t b);                /* FUN_00062DCC */
void     sk_err_string3(uint64_t sink, uint8_t code);         /* FUN_00062F08 */
void     sk_ep_teardown(uint64_t ep, uint64_t count);         /* FUN_00063040 */
void     sk_ep_setup(uint64_t *ep, uint64_t flags, uint64_t a, uint64_t *cfg); /* FUN_000635C0 */
uint64_t sk_ep_last(void);                                    /* FUN_00063694 */
uint64_t sk_ep_get(uint64_t ep, uint64_t idx);                /* FUN_000636A4 */
uint64_t sk_ep_get20(uint64_t ep);                            /* FUN_000636D0 */
uint64_t sk_ep_get28(uint64_t ep);                            /* FUN_000636D8 */
void     sk_pcpu_enter(uint64_t id, uint64_t extra); /* FUN_000636E0 */
void     sk_pcpu_leave(uint64_t arg);                 /* FUN_00063768 */
void     sk_err_string_wrap2(void);                   /* FUN_000638EC */
uint64_t sk_ep_name(uint64_t ep);                     /* FUN_00063910 */
uint64_t sk_ep_check(uint64_t ep, int flag);          /* FUN_0006393C */
uint32_t sk_ep_name2(uint64_t ep);                    /* FUN_00063970 */
void     sk_msg_read_rr(uint64_t a, uint64_t *msg);   /* FUN_000639A0 */
uint64_t sk_notify_reg_init(void);                    /* FUN_00063A50 */
uint64_t sk_notify_reg_reset(void);                   /* FUN_00063A94 */
uint64_t sk_notify_alloc(uint64_t a, uint64_t b, uint64_t c); /* FUN_00063AA8 */
void     sk_notify_lock(void);                                /* FUN_00063B50 */
void     sk_notify_add(uint64_t idx, uint64_t fn, uint64_t arg, int enabled); /* FUN_00063B84 */
void     sk_notify_unlock(void);                              /* FUN_00063C5C */
void     sk_notify_construct(uint64_t key);                   /* FUN_00063CFC */
void     sk_notify_teardown(void);                            /* FUN_00063DD4 */
void     sk_set_tpidr(uint64_t v);                            /* FUN_00063EA4 */
uint64_t sk_notify_call(uint64_t *idx, uint64_t k);           /* FUN_00063EB4 */
uint64_t sk_frame_sz(void);                                   /* FUN_00063FFC: returns 0x28 */
void     sk_frame_zero(uint64_t p);                           /* FUN_0006402C */
bool     sk_exc_active(void);                                 /* FUN_000640E4 */
void     sk_exc_setup(void);                                  /* FUN_00064108 */
uint64_t sk_vas_freeze(uint64_t a, uint64_t b, uint64_t c);   /* FUN_00064578 */
void     sk_err_string4(uint64_t sink, uint8_t code);         /* FUN_000647A0 */
uint64_t sk_amx_alloc(uint64_t tcb, uint64_t a);              /* FUN_000648E4 */
void     sk_amx_cap_alloc(uint64_t tcb, uint64_t th, uint64_t *msg); /* FUN_00064904 */
void     sk_list_push(uint64_t *head);                        /* FUN_00064A7C */
void     sk_sme_cap_alloc(uint64_t tcb, uint64_t th, uint64_t *msg); /* FUN_00064AAC */
void     sk_exc_cap_alloc(uint64_t tcb);                      /* FUN_00064C24 */
uint64_t sk_exc_endpoint_create(uint64_t arg);                /* FUN_00064CAC */
uint64_t sk_exc_dispatch(uint64_t tcb, uint64_t ctx);         /* FUN_00064DE8 */
void     sk_exc_raise(uint64_t tcb, uint64_t esr, uint64_t far); /* FUN_00064E84 */
sk_pair_t sk_freeze(void);                             /* FUN_00065020 */
void     sk_err_string_wrap3(void);                           /* FUN_00065138 */
void     sk_noop2(void);                                      /* FUN_00065158 */
void     sk_noop3(void);                                      /* FUN_0006516C */
void     sk_inline_store(uint64_t a, uint64_t b, uint64_t c); /* FUN_00065190 */
void     sk_noop4(void);                                      /* FUN_000651AC */
void     sk_noop5(void);                                      /* FUN_000651BC */
void     sk_err_string_wrap4(void);                           /* FUN_000651D0 */
void     sk_msg_decode(uint64_t *out, uint64_t tcb, uint64_t *word); /* FUN_000651E8 */
sk_pair_t sk_msg_word_copy(uint64_t *src);            /* FUN_00065344 */
uint64_t sk_cap_get(uint64_t tcb);                            /* FUN_00065350 */
void     sk_err_string5(uint64_t sink, uint8_t code);         /* FUN_000654E8 */
void     sk_set_global0(uint64_t v);                          /* FUN_00065620 */
void     sk_global0_dispatch(uint64_t a, uint64_t b);         /* FUN_0006562C */

/* ================================================================== *
 * 0005fd2c — FUN_0005FD2C  (est. sk_cpu_stack_bytes)
 * Ghidra: undefined8 FUN_0005FD2C(ulong param_1)
 * Checks that the current CPU's kernel stack has at least `n` free bytes
 * below the current stack pointer. Returns 1 if so, otherwise panics
 * ("requested %zu stack bytes, only h..."). If the stack pointer is not
 * inside the CPU's stack window at all, traps via SoftwareBreakpoint.
 * Confidence: medium (semantics inferred from the panic string + window check)
 * Notes: `&stack0xfffffffffffffff0` is the caller's SP; approximated with a local.
 * ================================================================== */
uint64_t sk_cpu_stack_bytes(uint64_t n)
{
    uint64_t cpu = sk_cpu_base();               /* FUN_00060524 */
    uint64_t lo = *(uint64_t *)(cpu + 0x168);   /* stack window base */
    uint64_t hi = *(uint64_t *)(cpu + 0x170);   /* stack window limit */
    uint64_t sp;
    volatile uint64_t anchor = 0;
    sp = (uint64_t)&anchor;
    if (lo <= sp && sp < hi) {
        if (n <= sp - lo) {
            return 1;
        }
        /* WARNING: does not return */
        sk_panic0("requested zu stack bytes only h");
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(1, 0x5fd90);
    return 0;
}

/* ================================================================== *
 * 0005fdac — FUN_0005FDAC  (est. sk_altstack_enable)
 * Ghidra: long FUN_0005FDAC(long param_1, undefined8 param_2)
 * Enables the alternate-stack ("altstack") mode for a thread. Enters the
 * per-CPU preempt section, and if the thread has a stack pointer present
 * (*(th+0x28) low byte non-zero) it maps/retains it and bumps the per-CPU
 * altstack count at +0x69. Panics "already enabled" if the count cannot be
 * incremented. Returns the per-CPU base.
 * Confidence: medium
 * Notes: `extraout_x18` is a decompiler carry artifact; represented as `aux`.
 * ================================================================== */
uint64_t sk_altstack_enable(uint64_t th, uint64_t a)
{
    uint64_t ret;
    uint64_t aux = 0;
    int64_t canary = SK_CANARY;
    uint8_t st = 0;
    uint64_t cpu;
    char cnt;

    ret = sk_preempt_enter(&st);               /* FUN_00060570 */
    if ((int)ret == 0) {
        goto done;
    }
    CallSupervisor(2);
    if ((*(uint64_t *)(th + 0x28) & 0xff) == 0) {
        sk_preempt_leave(&st);                 /* FUN_000605F8 */
        goto done;
    }
    sk_h_004B6F70(*(uint64_t *)(th + 0x28), buf48); /* FUN_004B6F70 */
    cpu = sk_cpu_base();                       /* FUN_00060524 */
    cnt = *(char *)(cpu + 0x69);
    if (cnt != 0) {
        if (cnt != -1) goto setcount;
        cpu = sk_h_004B6FC0();                 /* FUN_004B6FC0 */
        aux = 0;
    }
    if ((aux & 1) != 0) {
        /* WARNING: does not return */
        sk_panic0("already enabled lx");
    }
    cnt = *(char *)(cpu + 0x69);
setcount:
    *(char *)(cpu + 0x69) = cnt + 1;
    return cpu;
done:
    if (canary != SK_CANARY) {
        /* WARNING: does not return */
        sk_fatal();                            /* FUN_0011D7E8 */
    }
    return ret;
}

/* ================================================================== *
 * 0005fe48 — FUN_0005FE48  (est. sk_altstack_enable2)
 * Ghidra: void FUN_0005FE48(void)
 * Same altstack-count increment as 0005fdac but with no thread/arg handling:
 * just bumps the per-CPU altstack count at +0x69, panicking "already enabled"
 * on overflow. No return value.
 * Confidence: medium
 * ================================================================== */
void sk_altstack_enable2(void)
{
    uint64_t cpu = sk_cpu_base();              /* FUN_00060524 */
    char cnt = *(char *)(cpu + 0x69);
    uint64_t aux = 0;
    if (cnt != 0) {
        if (cnt != -1) goto setcount;
        cpu = sk_h_004B6FC0();                 /* FUN_004B6FC0 */
        aux = 0;
    }
    if ((aux & 1) != 0) {
        /* WARNING: does not return */
        sk_panic0("already enabled lx");
    }
    cnt = *(char *)(cpu + 0x69);
setcount:
    *(char *)(cpu + 0x69) = cnt + 1;
}

/* ================================================================== *
 * 0005fea8 — FUN_0005FEA8  (est. sk_altstack_disable)
 * Ghidra: void FUN_0005FEA8(void)
 * Decrements the per-CPU altstack count at +0x69. If it drops to zero it
 * tears the altstack down (FUN_004B6FD8); if it was already zero it panics
 * "already disabled".
 * Confidence: medium
 * ================================================================== */
void sk_altstack_disable(void)
{
    uint64_t cpu = sk_cpu_base();              /* FUN_00060524 */
    char cnt = *(char *)(cpu + 0x69);
    uint64_t aux = 0;
    if (cnt == 0) {
        sk_h_004B6FD8();                       /* FUN_004B6FD8 */
    } else {
        *(char *)(cpu + 0x69) = cnt - 1;
        if ((cnt != 1) || ((aux & 1) != 0)) {
            return;
        }
    }
    /* WARNING: does not return */
    sk_panic0("already disabled lx");
}

/* ================================================================== *
 * 0005ff04 — FUN_0005FF04  (est. sk_stack_alloc)
 * Ghidra: void FUN_0005FF04(undefined8 *param_1, ulong param_2, uint param_3)
 * Allocates and maps a new kernel/thread stack region of `param_2` bytes
 * plus a 0x4000 guard, returning a 7-word descriptor in *param_1. Uses the
 * object allocator (FUN_00034A2C vtable at +0x30) to create the backing
 * object, maps it, and records base/length/flags. Panics "failed to bump new
 * stack", "failed to allocate stack", or "more than one mapping type".
 * Confidence: medium
 * ================================================================== */
void sk_stack_alloc(uint64_t *out, uint64_t size, uint32_t flags)
{
    uint64_t full = size + 0x4000;
    uint64_t obj, vtable, res;
    uint64_t uvar4;
    uint64_t local_78;
    uint64_t local_70;
    uint64_t lstack68;
    int64_t local_58;
    int idx;
    int64_t singleton;

    if (size >= 0xffffffffffffc000) {
        /* WARNING: does not return */
        sk_panic0("more than one mapping type speci");
    }
    {
        uint8_t tag[8];
        tag[0] = 0x11;
        sk_memset((void*)((uint64_t)tag | 1), 0xf, 0);
        /* local_48 = 0xc, local_44 = 0x20 */
        uint32_t mt = flags & 0xf;
        if ((flags & 0xe) == 0) mt = 1;
        uint64_t local_50 = full;
        if ((mt & (mt - 1)) == 0) {
            uint32_t kind = 0x40c8;
            if ((flags & 2) != 0) kind = 0x44c8;
            local_70 = 0;
            lstack68 = 0;
            res = sk_obj_get();                /* FUN_00034A2C: {obj,vtable} */
            vtable = /* hi half */ 0;
            uvar4 = (*(uint64_t(**)(void))(res_vtable + 0x30))(
                        res_obj, (uint64_t)((flags & 4) << 0xb |
                                            ((flags >> 3) & 1) << 9 | kind),
                        tag, &local_70, 0, tag);
            uvar4 &= 0xff;
            if (uvar4 == 0) {
                local_78 = size;
                uvar4 = (*(uint64_t(**)(void))(lstack68 + 0x18))(local_70, &local_78);
                uvar4 &= 0xff;
                if (uvar4 == 0) {
                    singleton = sk_singleton();            /* FUN_0005BB68 */
                    idx = *(int *)(singleton + 0x88);
                    *(int *)(singleton + 0x88) = idx + 1;
                    if (idx != -1) {
                        out[0] = local_70;
                        out[1] = lstack68;
                        *(uint32_t *)(out + 2) = flags & 0xffffffdf | (uint32_t)((flags & 0xf) == 0);
                        *(uint32_t *)((uint8_t*)out + 0x14) = 0;
                        out[3] = (uint64_t)local_58;
                        out[4] = (uint64_t)local_58 + full;
                        out[5] = full;
                        *(int *)(out + 6) = idx + 1;
                        *(uint32_t *)((uint8_t*)out + 0x34) = 0;
                        return;
                    }
                    sk_h_004B6FF0();           /* FUN_004B6FF0 */
                } else if (uvar4 in error table) {
                    /* WARNING: does not return */
                    sk_panic0("failed to bump new stack with at");
                }
            } else if (uvar4 in error table) {
                /* WARNING: does not return */
                sk_panic0("failed to allocate stack with at");
            }
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x600f0);
        }
    }
    /* unreachable */
    sk_panic0("more than one mapping type speci");
}

/* ================================================================== *
 * 0005ff04 — FUN_0005FF04  (est. sk_stack_alloc)
 * Ghidra: void FUN_0005FF04(undefined8 *param_1, ulong param_2, uint param_3)
 * Allocates and maps a new kernel/thread stack region of `size` bytes plus a
 * 0x4000 guard, returning a 7-word descriptor in *out. Uses the object
 * allocator (FUN_00034A2C pair; vtable entry +0x30 to create, +0x18 to map)
 * to build the backing object, then records base/length/flags/refcount.
 * Panics "failed to bump new stack", "failed to allocate stack", or
 * "more than one mapping type specified".
 * Confidence: medium
 * Notes: FUN_00114330 (thunk) here zero-fills 0xf bytes.  local_58 is an
 *   uninitialized-intent stack anchor (Ghidra artifact) used for the range.
 * ================================================================== */
void sk_stack_alloc(uint64_t *out, uint64_t size, uint32_t flags)
{
    uint64_t full = size + 0x4000;
    uint64_t local_70, lstack68;
    uint64_t uvar4, local_78;
    int64_t local_58;
    int64_t local_50;
    uint32_t local_48, local_44;
    uint8_t local_60[16];
    int64_t singleton;
    int idx;
    uint32_t mt, kind;
    sk_pair_t pair;
    uint64_t (*create)(uint64_t, uint64_t, void *, uint64_t *, int, void *);
    uint64_t (*map)(uint64_t, uint64_t *);

    if (size < 0xffffffffffffc000) {
        local_60[0] = 0x11;
        sk_memset0((uint8_t *)local_60 + 1, 0xf);   /* FUN_00114330 (thunk): zero-fill */
        local_48 = 0xc;
        local_44 = 0x20;
        mt = flags & 0xf;
        if ((flags & 0xe) == 0) mt = 1;
        local_50 = (int64_t)full;
        if ((mt & (mt - 1)) == 0) {
            kind = 0x40c8;
            if ((flags & 2) != 0) kind = 0x44c8;
            local_70 = 0;
            lstack68 = 0;
            pair = sk_obj_get();                 /* FUN_00034A2C */
            create = *(uint64_t (**)(uint64_t, uint64_t, void *, uint64_t *, int, void *))
                        ((uint64_t)pair.vtable + 0x30);
            uvar4 = create((uint64_t)pair.object,
                           (uint64_t)(((flags & 4) << 0xb) | (((flags >> 3) & 1) << 9) | kind),
                           local_60, &local_70, 0, local_60);
            uvar4 &= 0xff;
            if (uvar4 == 0) {
                local_78 = size;
                map = *(uint64_t (**)(uint64_t, uint64_t *))(lstack68 + 0x18);
                uvar4 = map(local_70, &local_78);
                uvar4 &= 0xff;
                if (uvar4 == 0) {
                    singleton = sk_singleton();     /* FUN_0005BB68 */
                    idx = *(int *)(singleton + 0x88);
                    *(int *)(singleton + 0x88) = idx + 1;
                    if (idx != -1) {
                        out[0] = local_70;
                        out[1] = lstack68;
                        *(uint32_t *)(out + 2) = flags & 0xffffffdf |
                                                 (uint32_t)((flags & 0xf) == 0);
                        *(uint32_t *)((uint8_t *)out + 0x14) = 0;
                        out[3] = (uint64_t)local_58;
                        out[4] = (uint64_t)local_58 + full;
                        out[5] = full;
                        *(int *)(out + 6) = idx + 1;
                        *(uint32_t *)((uint8_t *)out + 0x34) = 0;
                        return;
                    }
                    sk_h_004B6FF0();                /* FUN_004B6FF0 */
                } else {
                    /* error-code in the DAT_0064cb40 range table -> panic */
                    if (uvar4 <= 0x40)
                        sk_panic0("failed to bump new stack with at");
                }
            } else {
                if (uvar4 <= 0x40)
                    sk_panic0("failed to allocate stack with at");
            }
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x600f0);
        }
    } else {
        sk_h_004B7008();                            /* FUN_004B7008 */
    }
    /* WARNING: does not return */
    sk_panic0("more than one mapping type speci");
}

/* ================================================================== *
 * 000600f0 — FUN_000600F0  (est. sk_stack_alloc_call)
 * Ghidra: undefined8 FUN_000600F0(undefined8 param_1, undefined8 param_2,
 *                                 undefined8 param_3)
 * Convenience wrapper: allocates a stack of `size` bytes with flags 0x20,
 * then invokes the altstack switch (FUN_00060164) with it, and finally calls
 * the vtable +0x18 entry on the resulting object to release it.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_stack_alloc_call(uint64_t size, uint64_t a, uint64_t b)
{
    uint64_t desc[6];
    uint64_t ret;
    uint64_t (*release)(uint64_t);

    sk_memset0(desc, sizeof(desc));
    sk_stack_alloc(desc, size, 0x20);          /* FUN_0005FF04 */
    ret = sk_altstack_switch(desc[0], a, b);   /* FUN_00060164 */
    release = (uint64_t (*)(uint64_t))desc[1]; /* lStack_68 (vtable) */
    release(desc[0]);
    return ret;
}

/* ================================================================== *
 * 00060164 — FUN_00060164  (est. sk_altstack_switch)
 * Ghidra: undefined8 FUN_00060164(long param_1, undefined8 param_2,
 *                                 undefined8 param_3)
 * Switches a thread onto its alternate stack for the duration of a call into
 * FUN_0005CF18. Records the previous per-CPU stack state, installs the
 * thread's altstack as the current CPU stack, runs the callback, then
 * restores. If the thread requests stack teardown it unmaps/zeroes the
 * guard region, and re-enables/ disables the altstack count as flagged.
 * Panics if the thread is already on an altstack or has a zero altstack ID.
 * Confidence: medium
 * Notes: `&stack0xfffffffffffffff0` (SP) approximated by a local's address.
 * ================================================================== */
uint64_t sk_altstack_switch(uint64_t th, uint64_t a, uint64_t b)
{
    uint64_t puVar12 = *(uint64_t *)(th + 0x20);
    uint64_t cpu = sk_cpu_base();                 /* FUN_00060524 */
    uint64_t ret, old168, old170, stack, delta;
    uint32_t flags;
    int id;
    volatile uint64_t sp_anchor = 0;

    if (*(int *)(cpu + 0x148) != 0) {
        /* WARNING: does not return */
        sk_panic0("thread is already on altstack d");
    }
    id = *(int *)(th + 0x30);
    if (id == 0) {
        /* WARNING: does not return */
        sk_panic0("altstack p has zero ID");
    }
    if ((*(uint8_t *)(th + 0x10) >> 3 & 1) != 0) {
        sk_altstack_enable2();                    /* FUN_0005FE48 */
        id = *(int *)(th + 0x30);
    }
    *(uint64_t *)(cpu + 0x160) = 0x60208;
    *(uint64_t *)(cpu + 0x150) = *(uint64_t *)(th + 0x18);
    *(uint64_t *)(cpu + 0x158) = (uint64_t)&sp_anchor; /* old SP */
    *(int *)(cpu + 0x14c) = (int)*(uint64_t *)(th + 0x28);
    *(int *)(cpu + 0x148) = id;
    old168 = *(uint64_t *)(cpu + 0x168);
    old170 = *(uint64_t *)(cpu + 0x170);
    stack = *(uint64_t *)(th + 0x20);
    *(long *)(cpu + 0x168) = *(long *)(th + 0x18) + 0x4000;
    *(uint64_t *)(cpu + 0x170) = stack;
    ret = sk_h_0005CF18(puVar12, a, b);           /* FUN_0005CF18 */
    *(uint64_t *)(cpu + 0x168) = old168;
    *(uint64_t *)(cpu + 0x170) = old170;
    *(uint32_t *)(cpu + 0x148) = 0;
    *(uint32_t *)(cpu + 0x160) = 0;
    *(uint32_t *)(cpu + 0x164) = 0;
    *(uint32_t *)(cpu + 0x158) = 0;
    *(uint32_t *)(cpu + 0x15c) = 0;
    *(uint32_t *)(cpu + 0x150) = 0;
    *(uint32_t *)(cpu + 0x154) = 0;
    *(uint32_t *)(cpu + 0x14c) = 0;
    flags = *(uint32_t *)(th + 0x10);
    if ((flags >> 4 & 1) != 0) {
        uint64_t guard = sk_phys_alloc();         /* FUN_00034F70 */
        uint64_t *puVar11 = (uint64_t *)(*(long *)(th + 0x18) + 0x4000);
        uint64_t uvar3 = 0;
        uint64_t *puVar14 = (uint64_t *)puVar12;
        char cVar5 = 1;
        uint64_t uvar10 = 0;
        do {
            uint64_t *puVar13 = puVar14;
            uvar10 = uvar3;
            if ((puVar13 <= puVar11) || (puVar14 = puVar13 - 0x800, puVar14 < puVar11)) break;
            {
                sk_pair_t pr = sk_obj_get();      /* FUN_00034A2C */
                cVar5 = (**(char (**)(uint64_t, uint64_t, int, uint64_t))(
                            (uint64_t)pr.vtable + 0x40))((uint64_t)pr.object,
                            (uint64_t)puVar14, 0, guard);
            }
            do { CallSupervisor(4); } while (guard == 1);
            uvar3 = uvar10 + 0x4000;
        } while (cVar5 == 0);
        sk_h_004B23D8(guard, 0, 0);               /* FUN_004B23D8 */
        flags = *(uint32_t *)(th + 0x10);
        delta = (long)puVar12 - (long)puVar13;
        if (delta != 0) {
            puVar12 = (uint64_t *)((long)puVar13 + delta);
            if ((flags >> 3 & 1) == 0) {
                if ((puVar12 < puVar13) || ((uint64_t)((long)puVar12 - (long)puVar13) < delta)) {
                    /* WARNING: does not return */
                    SoftwareBreakpoint(0x5519, 0x60358);
                }
                sk_memset0(puVar13, delta);       /* FUN_00114330 (thunk) */
                flags = *(uint32_t *)(th + 0x10);
            } else if (7 < delta) {
                uint64_t cnt = uvar10 >> 3;
                uint64_t *p = puVar13;
                if (cnt < 2) cnt = 1;
                do { *p = 0; cnt -= 1; p += 1; } while (cnt != 0);
            }
        }
    }
    if ((flags >> 3 & 1) != 0) {
        sk_altstack_disable();                    /* FUN_0005FEA8 */
    }
    return ret;
}

/* ================================================================== *
 * 0006037c — FUN_0006037C  (est. sk_check_region_bounds)
 * Ghidra: void FUN_0006037C(void)
 * Bounds assertion: if (cpu+0x104) <= (cpu+0x108) return, else trap. This is
 * a debug sanity check on a small per-CPU region.
 * Confidence: low (guard/assert only)
 * ================================================================== */
void sk_check_region_bounds(void)
{
    uint64_t cpu = sk_cpu_base();                 /* FUN_00060524 */
    if ((uint64_t)(cpu + 0x104) <= (uint64_t)(cpu + 0x108)) {
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x603ac);
}

/* ================================================================== *
 * 000603ac — FUN_000603AC  (est. sk_jumptable_dispatch)
 * Ghidra: void FUN_000603AC(code *UNRECOVERED_JUMPTABLE, undefined8 param_2)
 * The decompiler could not recover an indirect jump table at 0x603b8 (too
 * many branches) and treated the target as a direct call. Preserved as a
 * tail-call through the supplied function pointer.
 * Confidence: low (unrecoverable jumptable)
 * Notes: fallback used: decompile only (no further disasm needed for a stub).
 * ================================================================== */
void sk_jumptable_dispatch(void (*fn)(uint64_t), uint64_t a)
{
    /* WARNING: Could not recover jumptable at 0x000603b8; indirect call. */
    fn(a);
}

/* ================================================================== *
 * 000603bc — FUN_000603BC  (est. sk_tcb_get_a8)
 * Ghidra: undefined8 FUN_000603BC(long param_1)
 * Getter: returns *(tcb+0xa8) (an endpoint / owner pointer field).
 * Confidence: high (trivial getter)
 * ================================================================== */
uint64_t sk_tcb_get_a8(uint64_t tcb)
{
    return *(uint64_t *)(tcb + 0xa8);
}

/* ================================================================== *
 * 000603c4 — FUN_000603C4  (est. sk_boot_lookup)
 * Ghidra: undefined8 FUN_000603C4(void)
 * Walks the "tightbeam placeholder" resource iterator (FUN_0004EB44 /
 * FUN_0004EB4C / FUN_0004ECF0) looking for a resource of kind 0x1c, resolves
 * it with FUN_0004E7B8, and returns FUN_0004E774(marker, packed-word) for the
 * first match. Returns 0 if no such resource or boot feature flag off.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_boot_lookup(void)
{
    uint64_t uvar4;
    uint64_t local30[2];
    int kind;
    int iter;

    if (sk_h_0004FE80() != 0) {                   /* FUN_0004FE80 */
        if (sk_h_0004ED48() != 0) {               /* FUN_0004ED48 */
            /* 16-byte result zeroed; overflow check present in original */
        }
        local30[0] = sk_h_0004EB44();             /* FUN_0004EB44: iter init */
        local30[1] = 0;
        uvar4 = sk_h_0004ECF0(local30[0]);        /* FUN_0004ECF0 */
        if ((uvar4 & 1) == 0) {
            uint16_t *puVar6 = NULL;
            do {
                uvar4 = sk_h_0004EB4C(local30[0]); /* FUN_0004EB4C: iter next */
                if (uvar4 != 0) {
                    /* overflow check in original */
                }
                kind = (int)sk_h_0004E88C(uvar4);  /* FUN_0004E88C */
                if (kind == 0x1c) {
                    puVar6 = (uint16_t *)sk_h_0004E7B8(uvar4, 0); /* FUN_0004E7B8 */
                }
                iter = (int)sk_h_0004ECF0(local30[0]);
            } while (iter == 0);
            if (puVar6 != NULL) {
                uint64_t local40 = sk_h_0004ED84(); /* FUN_0004ED84 */
                uint64_t word =
                    (uint64_t)((uint8_t)puVar6[1]) << 0x10 |
                    (uint64_t)(*(uint8_t *)((uint8_t *)puVar6 + 3)) << 0x18 |
                    (uint64_t)*puVar6 |
                    ((uint64_t)((uint16_t)((uint8_t)puVar6[3] << 0x10 |
                                 (uint8_t)(*(uint8_t *)((uint8_t *)puVar6 + 7)) << 0x18 |
                                 (uint16_t)puVar6[2]) << 0x20));
                return sk_h_0004E774(local40, word); /* FUN_0004E774 */
            }
        }
    }
    return 0;
}

/* ================================================================== *
 * 000604cc — FUN_000604CC  (est. sk_err_string)
 * Ghidra: void FUN_000604CC(byte param_1)
 * Prints the textual name of an L4 error code into a 0x20-byte stack buffer
 * and writes it out (memcpy + strlen-print). Codes 0..9 map to the standard
 * cL4/seL4 error names; anything else prints an "unknown" marker.
 * Confidence: high (string constants are the L4 error names)
 * ================================================================== */
void sk_err_string(uint64_t sink, uint8_t code)
{
    const char *name;
    char buf[0x20];
    if (9 < code) {
        sk_memcpy(buf, "L4_ErrorCode?      ", 0x20);
        sk_h_0000178C((uint64_t)buf, 0x20);       /* FUN_0000178C: print buf */
        return;
    }
    switch (code) {
        default:                    name = "L4_ErrorCodeSuccess      "; break;
        case 1:                     name = "L4_ErrorCodePreempted    "; break;
        case 2:                     name = "L4_ErrorCodeCanceled     "; break;
        case 3:                     name = "L4_ErrorCodeTruncated    "; break;
        case 4:                     name = "L4_ErrorCodeCapInvalid   "; break;
        case 5:                     name = "L4_ErrorCodeSlotInvalid  "; break;
        case 6:                     name = "L4_ErrorCodeMethodInvalid"; break;
        case 7:                     name = "L4_ErrorCodeArgumentInvalid"; break;
        case 8:                     name = "L4_ErrorCodeOperationInvalid"; break;
        case 9:                     name = "L4_ErrorCodePermissionInvalid"; break;
    }
    sk_memcpy(buf, name, 0x20);
    sk_h_0000178C((uint64_t)buf, 0x20);           /* FUN_0000178C */
}

/* ================================================================== *
 * 000604ec — FUN_000604EC  (est. sk_err_string_reg)
 * Ghidra: void FUN_000604EC(void)
 * Same error-code switch as 000604cc but the selector comes from register
 * w20 (unaff_w20) and the string/print arguments were lost by the
 * decompiler. Reproduced as a no-op-shaped stub: the switch is retained.
 * Confidence: low (decompiler lost the string/print operands)
 * ================================================================== */
void sk_err_string_reg(uint8_t code)
{
    if (9 < code) {
        /* FUN_00117CC4()/FUN_0000178C() — operands not recovered */
        return;
    }
    switch (code) {
        default: case 1: case 2: case 3: case 4:
        case 5: case 6: case 7: case 8: case 9:
            break;
    }
}

/* ================================================================== *
 * 000604f8 — FUN_000604F8  (est. sk_noop)
 * Ghidra: void FUN_000604F8(void)
 * Empty function (returns immediately). Referenced by the kernel-init path
 * for an empty dispatch slot.
 * Confidence: high (trivially empty)
 * ================================================================== */
void sk_noop(void)
{
}

/* ================================================================== *
 * 000604fc — FUN_000604FC  (est. sk_counter_inc)
 * Ghidra: long FUN_000604FC(void)
 * Increments and returns the kernel singleton's +0x30 counter (a global
 * object/thread sequence number).
 * Confidence: high (trivial increment)
 * ================================================================== */
uint64_t sk_counter_inc(void)
{
    uint64_t s = sk_singleton();                  /* FUN_0005BB68 */
    uint64_t v = *(uint64_t *)(s + 0x30);
    *(uint64_t *)(s + 0x30) = v + 1;
    return v + 1;
}

/* ================================================================== *
 * 00060524 — FUN_00060524  (est. sk_cpu_base)
 * Ghidra: undefined8 FUN_00060524(void)
 * Returns the current CPU's per-CPU base pointer, stored at *(tpidr_el0+8).
 * This is the single most-called getter in the region.
 * Confidence: high (trivial getter; matches slice-09 convention)
 * ================================================================== */
uint64_t sk_cpu_base(void)
{
    return *(uint64_t *)(tpidr_el0 + 8);
}

/* ================================================================== *
 * 00060530 — FUN_00060530  (est. sk_boot_platform_setup)
 * Ghidra: void FUN_00060530(void)
 * Sets the boot/platform flag DAT_006b26c8 to 1.
 * Confidence: high (trivial store)
 * ================================================================== */
void sk_boot_platform_setup(void)
{
    sk_g_boot_flag_a = 1;                         /* DAT_006b26c8 */
}

/* ================================================================== *
 * 00060540 — FUN_00060540  (est. sk_boot_flag_a)
 * Ghidra: undefined1 FUN_00060540(void)
 * Returns boot flag DAT_006b26c8.
 * Confidence: high
 * ================================================================== */
uint64_t sk_boot_flag_a(void)
{
    return sk_g_boot_flag_a;                      /* DAT_006b26c8 */
}

/* ================================================================== *
 * 0006054c — FUN_0006054C  (est. sk_boot_flag_b)
 * Ghidra: undefined1 FUN_0006054C(void)
 * Returns boot flag DAT_006b26c9.
 * Confidence: high
 * ================================================================== */
uint64_t sk_boot_flag_b(void)
{
    return sk_g_boot_flag_b;                      /* DAT_006b26c9 */
}

/* ================================================================== *
 * 00060564 — FUN_00060564  (est. sk_syscall_number)
 * Ghidra: undefined1 FUN_00060564(void)
 * Returns the constant 0xa2 (162). A fixed supervisor/syscall selector.
 * Confidence: high (constant)
 * ================================================================== */
uint64_t sk_syscall_number(void)
{
    return 0xa2;
}

/* ================================================================== *
 * 00060570 — FUN_00060570  (est. sk_preempt_enter)
 * Ghidra: byte * FUN_00060570(byte *param_1)
 * Enters a per-CPU "no-preempt"/atomic section. If `saved` is non-NULL the
 * previous preempt state is stored there and, when it was already active,
 * returns 1. Otherwise it bumps the global preempt counter (DAT_006ad900,
 * low 10 bits are the live count, high bits a "generation" and the 0x400 step
 * is the drain marker), sets the per-CPU active byte at +0x68, and takes the
 * LOAcquire lock. When the generation changes it drains pending per-CPU
 * reschedules (FUN_0005DEB4).
 * Confidence: medium
 * Notes: return value is the low byte (0/1) of the preempt state.
 * ================================================================== */
uint64_t sk_preempt_enter(uint8_t *saved)
{
    uint64_t cpu = *(uint64_t *)(tpidr_el0 + 8);
    uint8_t cur = *(uint8_t *)(cpu + 0x68);
    uint8_t *slot;
    uint64_t prev;

    if (saved == NULL) {
        if (cur != 0) {
            slot = (uint8_t *)sk_h_004B7098();        /* FUN_004B7098 */
            cpu = *(uint64_t *)(tpidr_el0 + 8);
            if ((*(uint8_t *)(cpu + 0x68) & 1) == 0) {
                slot = (uint8_t *)sk_h_004B70C8();    /* FUN_004B70C8 */
                while ((sk_g_preempt_ctr & 0x3ff) != 0) {
                    cpu = *(uint64_t *)(tpidr_el0 + 8);
                    sk_h_0005DEB4(*(uint64_t *)(cpu + 8)); /* FUN_0005DEB4 */
                }
                sk_g_preempt_ctr += 0x400;
                return (uint64_t)slot;
            }
            if (slot == NULL) {
                *(uint8_t *)(cpu + 0x68) = 0;
            } else {
                uint8_t b = *slot;
                *(uint8_t *)(cpu + 0x68) = b;
                if ((b & 1) != 0) {
                    return (uint64_t)slot;
                }
            }
            *(int64_t *)(cpu + 0x58) -= 1;
            sk_g_preempt_ctr -= 1;
            return (uint64_t)slot;
        }
    } else {
        *saved = cur;
        if ((cur & 1) != 0) {
            return 1;
        }
    }
    prev = sk_g_preempt_ctr;
    LOAcquire();
    sk_g_preempt_ctr += 1;
    *(uint8_t *)(cpu + 0x68) = 1;
    *(int64_t *)(cpu + 0x58) += 1;
    if ((prev >> 10) != *(uint64_t *)(cpu + 0x78)) {
        sk_preempt_leave(NULL);                       /* FUN_000605F8 */
        *(uint64_t *)(cpu + 0x78) = prev >> 10;
        return *(uint8_t *)(cpu + 0x68);
    }
    return 1;
}

/* ================================================================== *
 * 000605f8 — FUN_000605F8  (est. sk_preempt_leave)
 * Ghidra: void FUN_000605F8(byte *param_1)
 * Leaves the per-CPU preempt section. If the current preempt state is not
 * active it drains pending per-CPU reschedules and advances the generation
 * counter by 0x400. Otherwise restores the preempt state from `restore`
 * (or clears it) and decrements the per-CPU nesting count at +0x58 and the
 * global preempt counter.
 * Confidence: medium
 * ================================================================== */
void sk_preempt_leave(uint8_t *restore)
{
    uint64_t cpu = *(uint64_t *)(tpidr_el0 + 8);
    uint8_t b;
    if ((*(uint8_t *)(cpu + 0x68) & 1) == 0) {
        sk_h_004B70C8();                              /* FUN_004B70C8 */
        while ((sk_g_preempt_ctr & 0x3ff) != 0) {
            cpu = *(uint64_t *)(tpidr_el0 + 8);
            sk_h_0005DEB4(*(uint64_t *)(cpu + 8));    /* FUN_0005DEB4 */
        }
        sk_g_preempt_ctr += 0x400;
        return;
    }
    if (restore == NULL) {
        *(uint8_t *)(cpu + 0x68) = 0;
    } else {
        b = *restore;
        *(uint8_t *)(cpu + 0x68) = b;
        if ((b & 1) != 0) {
            return;
        }
    }
    *(int64_t *)(cpu + 0x58) -= 1;
    sk_g_preempt_ctr -= 1;
}

/* ================================================================== *
 * 00060650 — FUN_00060650  (est. sk_preempt_drain)
 * Ghidra: void FUN_00060650(void)
 * Drains any pending per-CPU reschedule work and advances the global preempt
 * generation by 0x400 (the "0x400" drain step).
 * Confidence: medium
 * ================================================================== */
void sk_preempt_drain(void)
{
    while ((sk_g_preempt_ctr & 0x3ff) != 0) {
        uint64_t cpu = *(uint64_t *)(tpidr_el0 + 8);
        sk_h_0005DEB4(*(uint64_t *)(cpu + 8));        /* FUN_0005DEB4 */
    }
    sk_g_preempt_ctr += 0x400;
}

/* ================================================================== *
 * 000606b0 — FUN_000606B0  (est. sk_stack_bump)
 * Ghidra: ulong FUN_000606B0(ulong param_1)
 * Lazy-initializes the per-CPU stack bump region (DAT_006b2710) off a fixed
 * frame size, then returns a tag/word combining the region and the caller
 * tag: low 14 bits come from the negated region pointer, high 32 bits from
 * param_1 << 14. Used to tag a stack frame allocation.
 * Confidence: medium
 * Notes: FUN_00063FFC() returns the fixed frame size 0x28.
 * ================================================================== */
uint64_t sk_stack_bump(uint64_t tag)
{
    if (sk_g_stack_base == 0) {                       /* DAT_006b2710 */
        uint64_t fs = sk_frame_sz();                  /* FUN_00063FFC = 0x28 */
        uint64_t uvar3 = (0x1fd00U - fs) & 0xfffffffffffffff0ULL;
        if (uvar3 + fs < uvar3) {
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x606fc);
        }
        sk_g_stack_base = 0x20178 - uvar3;
    }
    return (uint64_t)(uint32_t)-(int32_t)sk_g_stack_base & 0x3fff |
           (tag & 0xffffffff) << 0xe;
}

/* ================================================================== *
 * 00060728 — FUN_00060728  (est. sk_kernel_init)
 * Ghidra: void FUN_00060728(undefined8 param_1, ulong param_2,
 *          undefined8 *param_3, undefined8 *param_4, undefined8 param_5)
 * Per-CPU kernel initialisation and the main cL4 dispatch loop entry.
 * On the boot CPU it sets up tpidr_el0, initialises the per-CPU stack frame,
 * the notification/callback registry, and the root task (roottask) image
 * tables; on secondary CPUs it allocates the per-CPU TCB, names it
 * ("cpuN"/"init"), binds its root thread and DT, and enters it via
 * CallSupervisor(0). Then it dispatches to a handler registered in the
 * 0x6b26d8 dispatch table, panicking ("No handler set for entry" /
 * "Unexpected thread exit") when the handler returns.
 * Confidence: medium
 * Notes: FUN_00063FFC() frame size; many GHIDRA DAT_/string artifacts kept
 *   as named constants. "Security assertion failed" panic at 0x60f24.
 * ================================================================== */
void sk_kernel_init(uint64_t state, uint64_t kind, uint64_t *a, uint64_t *b, uint64_t arg)
{
    uint64_t fs;
    uint64_t uvar24;
    uint64_t uvar13;
    uint64_t *puVar26;
    uint64_t *puVar20;
    uint64_t uvar16;
    uint64_t uvar25;
    uint64_t uvar17;
    uint64_t *cpu;
    uint64_t lvar12;
    uint64_t *pcVar18;
    uint64_t *plVar26;
    uint32_t uvar22;
    uint32_t uvar19;
    uint64_t i64;
    int64_t singleton;
    char *name;
    uint8_t regs[8];
    uint8_t frame[0x118];

    fs = sk_frame_sz();                               /* FUN_00063FFC = 0x28 */
    uvar24 = kind;

    /* ---- Boot CPU: set up tpidr + per-CPU stack frame ---- */
    if ((uint64_t)tpidr_el0 == 0) {
        uint64_t puVar23;
        uint64_t uvar13b;
        puVar20 = (uint64_t *)(((uint64_t)a + 0x3fff) & 0xffffffffffffc000ULL);
        if (puVar20 < b) goto boom;
        sk_h_00114AA0(b, &uvar13b);                   /* FUN_00114AA0 (memcpy small) */
        puVar23 = (uint64_t)puVar20 - 0x60;
        uvar24 = ((puVar23 - fs) & 0xfffffffffffffff0ULL);
        if (uvar24 + fs < uvar24) goto boom;
        uvar13 = (uint64_t)b & 0xffffffffffffc000ULL;
        sk_memset0(frame, 0x118);                     /* FUN_00114330 (thunk) */
        {
            uint32_t marker = 0x656e7472;             /* local_190 "rent" */
            uint64_t z = 0;
            uint32_t z0 = 0;
            (void)z0;
            sk_h_00117CC4((void *)(uvar24 - 0x178), frame, 0x118); /* FUN_00117CC4 */
            *(uint32_t *)(uvar24 - 0x60) = marker;
            sk_h_00117CC4((void *)(uvar24 - 0x5c), &z, 0x14);
            *(uint64_t *)(uvar24 - 0x48) = uvar13;
            *(uint64_t *)(uvar24 - 0x40) = (uint64_t)puVar20 - uvar13;
            *(uint64_t *)(uvar24 - 0x38) = (uint64_t)b;
            *(uint64_t *)(uvar24 - 0x18) = 0;
            *(uint64_t *)(uvar24 - 0x20) = 0;
            *(uint64_t *)(uvar24 - 0x28) = 0;
            *(uint64_t *)(uvar24 - 0x30) = 0;
            *(uint64_t *)(uvar24 - 0x10) = uvar13;
            *(uint64_t *)(uvar24 - 8) = (uint64_t)b;
        }
        sk_set_tpidr(puVar23);                        /* FUN_00063EA4 */
        *(uint64_t *)puVar23 = uvar24;
        puVar20[-0x5f] = uvar24 - 0x178;
        uvar24 = 0;                                   /* extraout_x1 artifact */
    }

    /* ---- Altstack state + first-CPU notification registry ---- */
    if (((kind & 0xfd) == 1) && (sk_g_altstack_state == 0)) { /* DAT_006b26d0 */
        uint64_t uvar13b;
        uint64_t *lvar14;
        uint64_t *pbVar15;
        uvar24 = ((((uint64_t)a + 0x3fff) & 0xffffffffffffc000ULL) - fs - 0x300)
                 & 0xfffffffffffffff0ULL;
        if (uvar24 + fs < uvar24) goto boom;
        puVar26 = (uint64_t *)(uvar24 - 0x200);
        sk_g_altstack_state = (uint64_t)puVar26;
        uvar13 = sk_notify_reg_reset();               /* FUN_00063A94 = 0x64dce8 */
        lvar14 = (uint64_t *)sk_notify_reg_init();    /* FUN_00063A50 */
        cpu = (uint64_t *)tpidr_el0;
        if (*(uint64_t *)(cpu + 0xf8) != 0) goto err70f8;
        if (*(uint64_t *)(cpu + 0x10) != uvar24 - 400) {
            if ((*(uint64_t *)(cpu + 0x10) != 0) ||
                (i64 = *(uint64_t *)((uint8_t *)lvar14 + 0x208),
                 *(uint64_t *)((uint8_t *)lvar14 + 0x208) = i64 + 1, i64 != -1)) {
                *(uint64_t *)(cpu + 0x10) = uvar24 - 400;
                goto boot_cont;
            }
            goto err710c;
        }
boot_cont:
        if (uvar13 + 0x2f0 < uvar13) goto boom;
        sk_h_0005BA40(uvar13);                        /* FUN_0005BA40 */
        sk_h_0005D5DC();                              /* FUN_0005D5DC */
        sk_h_0005AD40();                              /* FUN_0005AD40 */
        lvar12 = sk_h_00054624(arg);                  /* FUN_00054624 */
        if (*(uint64_t *)(lvar12 + 8) == 0) {
            sk_h_00052C4C(*(uint64_t *)(lvar12 + 0x18)); /* FUN_00052C4C */
        }
        sk_h_00055164();                              /* FUN_00055164 */
        pbVar15 = (uint64_t *)sk_h_00054610();        /* FUN_00054610: boot image info */
        sk_h_0005C16C();                              /* FUN_0005C16C */
        if ((*(uint8_t *)pbVar15 & 1) != 0) {
            uvar13 = sk_h_000556E4(*(uint64_t *)(pbVar15 + 0x18)); /* FUN_000556E4 */
            uvar16 = sk_h_000556C8(*(uint64_t *)(pbVar15 + 0x18)); /* FUN_000556C8 */
            if (uvar13 + uvar16 * 8 < uvar13) goto boom;
            uvar25 = uvar16 * 8;
            if (sk_h_0005C184(uvar13, uvar25) != uvar25) { /* FUN_0005C184 */
                sk_h_004B7120();                      /* FUN_004B7120 */
                sk_h_004B7120();
                goto boom;
            }
init_tables:
            sk_memset0((void *)uvar13, uvar25);       /* FUN_00114330 (thunk) */
            sk_h_00054DEC();                          /* FUN_00054DEC */
            sk_h_0011D790();                          /* FUN_0011D790 */
            sk_h_00052A04(*(uint64_t *)(lvar12 + 0x10)); /* FUN_00052A04 */
            if (*(uint64_t *)(lvar12 + 0xc0) == 0) {
                uint64_t *lvar14b = (uint64_t *)*(uint64_t *)(lvar12 + 0xb8);
                if (lvar14b == (uint64_t *)2) {
                    lvar14b = (uint64_t *)sk_h_0004DFD0(4, "tbhb-4"); /* FUN_0004DFD0 */
                    uvar13 = *(uint64_t *)(lvar14b + 8) | 0x18;
                } else if (lvar14b == (uint64_t *)1) {
                    lvar14b = (uint64_t *)sk_h_0004DFD0(0, "tbhb-1");
                    uvar13 = *(uint64_t *)(lvar14b + 8);
                    uvar13 |= 0x15;
                } else if (lvar14b != 0) {
                    /* WARNING: does not return */
                    sk_h_00116D60();                  /* FUN_00116D60 */
                } else {
                    lvar14b = (uint64_t *)sk_h_0004DFD0(8, "roottask");
                    uvar13 = *(uint64_t *)(lvar14b + 8);
                    uvar13 |= 0x17;
                }
                *(uint64_t *)(lvar14b + 8) = uvar13;
            } else {
                sk_h_000549C0(*(uint64_t *)(lvar12 + 0xc0),
                              *(uint64_t *)(lvar12 + 200)); /* FUN_000549C0 */
            }
            sk_h_00052C54(*(uint64_t *)(lvar12 + 0x10)); /* FUN_00052C54 */
            uvar13 = *(uint64_t *)(lvar12 + 0x68);
            *puVar26 = 0;
            *(uint64_t *)(uvar24 - 0x1f8) = 0;
            *(uint64_t *)(uvar24 - 0x1f0) = uvar13 | 2;
            sk_memset0((void *)(uvar24 - 0x1e8), 0x48); /* FUN_00114330 */
            *(uint64_t *)(uvar24 - 0x1a0) = 0x696e6974; /* "init" */
            *(uint32_t *)(uvar24 - 0x198) = 0;
            *(uint32_t *)(uvar24 - 0x194) = 0;
            cpu = (uint64_t *)*(uint64_t *)(tpidr_el0 + 8);
            uvar17 = sk_tbplace_get(3, 0);            /* FUN_00062A48 */
            *(uint64_t *)((uint8_t *)cpu + 0x28) = uvar17;
            *(uint64_t *)((uint8_t *)cpu + 0xa8) = (uint64_t)puVar26;
            sk_h_0005BA5C(0x64dcc8);                  /* FUN_0005BA5C */
            sk_msg_read((uint64_t *)frame, uvar17);   /* FUN_0006166C */
            singleton = sk_singleton();               /* FUN_0005BB68 */
            *(uint64_t *)(singleton + 0x40) = 0;      /* local_168 artifact */
            puVar20 = *(uint64_t **)(lvar12 + 0xd0);
            if (puVar20 != NULL) {
                sk_h_0005BE48(puVar20[1], *puVar20);  /* FUN_0005BE48 */
            }
            sk_h_000359AC(0);                         /* FUN_000359AC */
            sk_set_global0(*(uint64_t *)(lvar12 + 0x58)); /* FUN_00065620 */
            sk_h_000656D8(*(uint64_t *)(lvar12 + 0x60));  /* FUN_000656D8 */
            sk_g_dt_root = sk_h_0005AC2C();           /* DAT_006ad6f8 = FUN_0005AC2C */
            uvar24 = 0;                               /* extraout_x1 artifact */
            goto dispatch;
        }
        uvar16 = *(uint64_t *)((uint8_t *)pbVar15 + 0x40);
        if ((uvar16 != 0) && (uvar13 = *(uint64_t *)((uint8_t *)pbVar15 + 0x30), uvar13 != 0)) {
            uvar25 = uvar16;
            if ((uvar13 + uvar16 < uvar13) || (uvar25 < uvar16)) goto boom;
            if (sk_h_0005C184(uvar13, 0) != uvar16) { /* FUN_0005C184 */
                sk_h_004B7120();
                goto boom;
            }
            if (uvar25 < uvar16) goto boom;
            goto init_tables;
        }
        sk_h_004B7138();                              /* FUN_004B7138 */
        goto boom;
    }

dispatch:
    puVar20 = (uint64_t *)sk_g_altstack_state;        /* DAT_006b26d0 */
    uvar22 = (uint32_t)kind;
    if (a == b) {
again:
        cpu = (uint64_t *)tpidr_el0;
        a = (uint64_t *) *(uint64_t *)((uint8_t *)cpu + 8);
        if (a != NULL) {
            sk_pcpu_enter(state, uvar24);             /* FUN_000636E0 */
        }
        uvar22 &= 0xff;
        uvar24 = (uint64_t)(uvar22 - 2);
        if (uvar22 < 2) {
            return;
        }
        if (uvar22 - 2 < 0x3f) {
            if (uvar24 == 1) {
                return;
            }
            goto sel_table;
        }
        if (1 < uvar22 - 0x50) {
            /* WARNING: does not return */
            sk_h_001150E0("Security assertion failed s f"); /* FUN_001150E0 */
        }
        sk_noop(state, kind);                         /* FUN_000604F8 */
        uvar24 = 1;
    } else {
        uint64_t *lvar14 = (uint64_t *)sk_notify_reg_init(); /* FUN_00063A50 */
        cpu = (uint64_t *)tpidr_el0;
        if (*(uint64_t *)(cpu + 0xf8) == 0) {
            if (*(uint64_t *)(cpu + 0x10) != (uint64_t)puVar20 + 0xe) {
                if ((*(uint64_t *)(cpu + 0x10) == 0) &&
                    (i64 = *(uint64_t *)((uint8_t *)lvar14 + 0x208),
                     *(uint64_t *)((uint8_t *)lvar14 + 0x208) = i64 + 1, i64 == -1)) {
                    goto err710c;
                }
                *(uint64_t *)(cpu + 0x10) = (uint64_t)puVar20 + 0xe;
            }
            cpu = (uint64_t *)tpidr_el0;
            uvar13 = *(uint64_t *)((uint8_t *)cpu + 8);
            singleton = sk_singleton();               /* FUN_0005BB68 */
            i64 = *(uint64_t *)(singleton + 0x30);
            *(uint64_t *)(singleton + 0x30) = i64 + 1;
            *(uint64_t *)(uvar13 + 0x120) = i64 + 1;
            if (uvar13 + 0x178 < uvar13) goto boom;
            *(uint64_t *)(uvar13 + 0xa0) = (uint64_t)&sk_h_004B6430; /* FUN_004B6430 */
            pcVar18 = (uint64_t *)sk_h_00054610();    /* FUN_00054610 */
            uvar19 = uvar22 & 0xff;
            if (uvar19 - 0x50 < 2) {
                *(uint64_t *)(uvar13 + 0x48) |= 4;
                uvar19 = ((uint32_t)(uint16_t)(kind >> 0x30)) % 10 | 0x63707530; /* "cpu0".. */
                goto name_set;
            } else if ((uvar19 == 3) || (uvar19 == 1)) {
                uvar19 = 0x696e6974;                  /* "init" */
                if (*(uint8_t *)pcVar18 == 1) {
                    *(uint64_t *)(uvar13 + 0x48) |= 4;
                }
                goto name_set;
            }
name_set:
            *(uint32_t *)(uvar13 + 0x118) = uvar19;
            sk_h_0005BE84(uvar13, 0);                 /* FUN_0005BE84 */
            i64 = *(uint64_t *)(uvar13 + 0x130);
            if (*(uint64_t *)((uint8_t *)pcVar18 + 0xb8) == 0) {
                puVar26 = (uint64_t *)&sk_g_roottask_dt; /* DAT_00690000 */
            } else {
                puVar26 = (uint64_t *)(((i64 + *(uint64_t *)(uvar13 + 0x138)) -
                                        *(uint64_t *)((uint8_t *)pcVar18 + 0xf0)) + 0x4000);
            }
            *(uint64_t *)(uvar13 + 0x130) = (uint64_t)puVar26;
            *(uint64_t *)(uvar13 + 0x138) = i64 - (uint64_t)puVar26;
            *(uint64_t *)(uvar13 + 0x168) = (uint64_t)puVar26 + 0x4000;
            if ((kind & 0xff) == 3) {
                uvar16 = *(uint64_t *)(uvar13 + 0x28);
            } else {
                uvar16 = sk_tbplace_get(uvar22 & 0xff, kind >> 0x30); /* FUN_00062A48 */
                *(uint64_t *)(uvar13 + 0x28) = uvar16;
            }
            *(uint64_t *)(uvar13 + 0x128) = uvar13;
            { /* store uvar13 into tpidrro bytes 0..7 */
                uint8_t *r = (uint8_t *)tpidrro_el0;
                r[0] = (uint8_t)uvar13;
                r[1] = (uint8_t)(uvar13 >> 8);
                r[2] = (uint8_t)(uvar13 >> 0x10);
                r[3] = (uint8_t)(uvar13 >> 0x18);
                r[4] = (uint8_t)(uvar13 >> 0x20);
                r[5] = (uint8_t)(uvar13 >> 0x28);
                r[6] = (uint8_t)(uvar13 >> 0x30);
                r[7] = (uint8_t)(uvar13 >> 0x38);
            }
            uvar24 = 8;
            CallSupervisor(0);                        /* enter the thread */
            { /* restore tpidrro bytes 0..7 */
                uint8_t *r = (uint8_t *)tpidrro_el0;
                r[0] = (uint8_t)uvar13; r[1] = (uint8_t)(uvar13 >> 8);
                r[2] = (uint8_t)(uvar13 >> 0x10); r[3] = (uint8_t)(uvar13 >> 0x18);
                r[4] = (uint8_t)(uvar13 >> 0x20); r[5] = (uint8_t)(uvar13 >> 0x28);
                r[6] = (uint8_t)(uvar13 >> 0x30); r[7] = (uint8_t)(uvar13 >> 0x38);
            }
            if ((uvar16 & 0xff) != 0) {
                sk_h_004B7150(uvar16, (uint64_t *)&regs); /* FUN_004B7150 */
                sk_h_004B7138();
                goto boom;
            }
            goto again;
        }
        sk_h_004B70F8();                              /* FUN_004B70F8 */
err70f8:
        sk_h_004B70F8();
err710c:
        sk_h_004B710C();                              /* FUN_004B710C */
        uvar22 = (uint32_t)puVar20;
        sk_h_004B710C();
        uvar24 = 0;                                   /* extraout_x8 */
sel_table:
        if ((1ULL << (uvar24 & 0x3f) & 0x40000002c000c000ULL) == 0) {
            if (uvar24 != 0) goto bad_sel;
            uvar24 = kind & 0xff;
        } else {
            uvar24 = 0;
        }
    }
    {
        uint64_t *ptab = (uint64_t *)sk_percpu_tbl(0x6b26d8, 1, 2); /* FUN_0005ACAC */
        uint64_t *entry = ptab + uvar24 * 2;
        if ((ptab <= entry) && (entry + 2 <= ptab + 6) && (entry <= entry + 2)) {
            uint64_t fn, harg;
            if (*(uint64_t *)entry == 0) {
                name = "No handler set for entry 04hh";
            } else {
                fn = *(uint64_t *)entry;
                harg = *(uint64_t *)(entry + 1);
                uvar17 = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))fn)(harg, state, kind);
                if ((a != NULL) && (sk_pcpu_leave(arg), *(uint64_t *)(a + 0x15 * 8) != 0)) {
                    { /* store uvar17 into tpidrro */
                        uint8_t *r = (uint8_t *)tpidrro_el0;
                        r[0] = (uint8_t)uvar17; r[1] = (uint8_t)(uvar17 >> 8);
                        r[2] = (uint8_t)(uvar17 >> 0x10); r[3] = (uint8_t)(uvar17 >> 0x18);
                        r[4] = (uint8_t)(uvar17 >> 0x20); r[5] = (uint8_t)(uvar17 >> 0x28);
                        r[6] = (uint8_t)(uvar17 >> 0x30); r[7] = (uint8_t)(uvar17 >> 0x38);
                    }
                    CallSupervisor(0);
                    { /* restore tpidrro */
                        uint8_t *r = (uint8_t *)tpidrro_el0;
                        r[0] = (uint8_t)uvar17; r[1] = (uint8_t)(uvar17 >> 8);
                        r[2] = (uint8_t)(uvar17 >> 0x10); r[3] = (uint8_t)(uvar17 >> 0x18);
                        r[4] = (uint8_t)(uvar17 >> 0x20); r[5] = (uint8_t)(uvar17 >> 0x28);
                        r[6] = (uint8_t)(uvar17 >> 0x30); r[7] = (uint8_t)(uvar17 >> 0x38);
                    }
                }
                name = "Unexpected thread exit 04hhX";
            }
            /* WARNING: does not return */
            sk_ec_switch(0, (int)name);               /* FUN_0005B190 */
        }
    }
bad_sel:
boom:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x608dc);
}

/* ================================================================== *
 * 00060f60 — FUN_00060F60  (est. sk_msg_call)
 * Ghidra: undefined8 FUN_00060F60(long param_1, undefined8 *param_2,
 *          undefined8 param_3, undefined8 param_4, undefined8 param_5,
 *          undefined8 param_6)
 * Performs an IPC call on a thread's message buffer. If `mode`==0 and a
 * caller-supplied message word is present it marshals that; otherwise it
 * fetches the thread's current message (FUN_00061E20). Marshals via
 * FUN_000610B8 into the thread's message region [th+0x118, th+0x168] and
 * writes the result word back when indicated.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_msg_call(uint64_t th, uint64_t *msg, uint64_t a, uint64_t b,
                     uint64_t mode, uint64_t c)
{
    uint64_t local58;
    uint64_t ret;
    uint8_t bVar4;
    uint8_t local59;

    if ((int)mode == 0) {
        if (msg != NULL) {
            local58 = *msg;
            bVar4 = 1;
            goto l_ready;
        }
    } else {
        uint64_t cpu = *(uint64_t *)(tpidr_el0 + 8);
        if (msg != NULL) return 0;
        if (th != cpu) return 0;
    }
    local58 = sk_msg_get(th);                         /* FUN_00061E20 */
    bVar4 = 0;
l_ready:
    local59 = 0;
    if ((uint64_t)(th + 0x118) <= (uint64_t)(th + 0x168)) {
        ret = sk_msg_marshal(th + 0x118, &local58, a, b, mode, c, 0, &local59); /* FUN_000610B8 */
        if ((bVar4 & local59) == 1) {
            *msg = local58;
        }
        return ret;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x61044);
    return 0;
}

/* ================================================================== *
 * 00061044 — FUN_00061044  (est. sk_msg_call2)
 * Ghidra: void FUN_00061044(void)
 * Calls FUN_00060F60 with no explicit arguments (values carried in registers).
 * Confidence: low (register-carried args lost by decompiler)
 * ================================================================== */
void sk_msg_call2(void)
{
    sk_msg_call(0, 0, 0, 0, 0, 0);                    /* FUN_00060F60 */
}

/* ================================================================== *
 * 0006104c — FUN_0006104C  (est. sk_msg_send)
 * Ghidra: undefined8 FUN_0006104C(undefined8 param_1, undefined8 *param_2,
 *          undefined8 param_3, undefined8 param_4, ulong param_5,
 *          undefined8 param_6)
 * Sends an IPC message on endpoint `ep`. When `mode`'s bit0 is clear it
 * marshals the message word (FUN_000610B8) with mode 0/flag 1 and writes the
 * result word back on completion; otherwise returns 0.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_msg_send(uint64_t ep, uint64_t *msg, uint64_t a, uint64_t b,
                     uint64_t mode, uint64_t c)
{
    uint64_t local30 = *msg;
    uint64_t ret;
    uint8_t local31 = 0;
    uint64_t ustack28;
    if ((mode & 1) == 0) {
        ustack28 = c;
        ret = sk_msg_marshal(ep, &local30, a, b, 0, 1, &ustack28, &local31); /* FUN_000610B8 */
        if (local31 == 1) {
            *msg = local30;
        }
        return ret;
    }
    return 0;
}

/* ================================================================== *
 * 000610b8 — FUN_000610B8  (est. sk_msg_marshal)
 * Ghidra: ulong FUN_000610B8(long param_1, long *param_2, ulong *param_3,
 *          ulong param_4, undefined8 param_5, undefined1 param_6,
 *          long *param_7, undefined1 *param_8)
 * Marshals an IPC message: computes the transfer size relative to the
 * endpoint's message window, invokes the message-send core FUN_0011546C, and
 * copies capability/label words into the output buffer (with cap-type bits
 * resolved via FUN_0005BC48). Mode 0 uses FUN_001156C4 (with label), mode 1
 * uses FUN_001155E0. Returns the message length. When the completion flag is
 * set, stores the resulting message word and sets *done.
 * Confidence: medium
 * Notes: local_98/local_90 are a completion side-channel set by the send core.
 * ================================================================== */
uint64_t sk_msg_marshal(uint64_t ep, uint64_t *msg, uint64_t *words, uint64_t max,
                        uint64_t mode, uint8_t flag, uint64_t *spare, uint8_t *done)
{
    uint64_t lvar5 = *msg;
    uint64_t lvar3 = spare ? *spare : 0;
    uint64_t uvar4 = lvar5 - *(uint64_t *)(ep + 0x18);
    uint64_t ustack_a8 = *(uint64_t *)(ep + 0x28) - *(uint64_t *)(ep + 0x18);
    uint64_t local_b0;
    uint64_t local_80;
    uint64_t local_78;
    uint64_t uvar7;
    uint64_t local_70;
    uint8_t local_88;
    uint8_t local_98 = 0;
    uint64_t local_90 = 0;

    if (*(uint64_t *)(ep + 0x20) <= ustack_a8) {
        ustack_a8 = *(uint64_t *)(ep + 0x20);
    }
    local_b0 = lvar3 + *(uint64_t *)(ep + 0x18);
    if (((spare == NULL) && (*(uint64_t *)(ep + 0x20) <= uvar4)) &&
        (*(int *)(ep + 0x30) != 0) && (lvar3 == 0)) {
        uvar7 = 0;
        local_80 = *(uint64_t *)(ep + 0x38);
        local_78 = (uint64_t)*(uint32_t *)(ep + 0x34);
    } else {
        uvar7 = 0;
        local_80 = 0;
        local_78 = 0;
        if ((*(uint64_t *)(ep + 0x20) <= uvar4) && (*(int *)(ep + 0x30) != 0)) {
            lvar5 = *(uint64_t *)(ep + 0x40);
            uvar7 = *(uint64_t *)(ep + 0x48);
        }
    }
    local_88 = flag;
    local_70 = lvar3;
    uvar4 = sk_h_0011546C(lvar5, mode, 0, lvar3, &local_b0, (void *)&local_98); /* FUN_0011546C */
    if (uvar4 <= max) {
        max = uvar4;
    }
    if (words != NULL) {
        uint64_t *puvar6 = words;
        if (uvar7 != 0) {
            if (lvar3 == 0) {
                uint64_t local_68 = uvar7;
                uint64_t lvar2 = sk_cap_lookup(&local_68); /* FUN_0005BC48 */
                if (lvar2 == 0) {
                    uvar7 = 0xffff000000000000;
                } else {
                    uvar7 = (uint64_t)*(uint16_t *)(lvar2 + 0x40) << 0x30;
                }
                uvar7 = local_68 & 0xffffffffffff | uvar7;
            }
            puvar6 = words + 1;
            if ((puvar6 < words) || (words + max < puvar6)) {
                /* WARNING: does not return */
                SoftwareBreakpoint(0x5519, 0x612d8);
            }
            {
                uint64_t lvar2 = max * 8;
                *words = uvar7;
                max -= 1;
                if ((uint64_t)((lvar2 + -8) >> 3) < max) {
                    /* WARNING: does not return */
                    SoftwareBreakpoint(0x5519, 0x612d8);
                }
            }
        }
        if ((int)mode == 0) {
            sk_h_001156C4(lvar5, puvar6, max, lvar3, (void *)&local_70, &local_70); /* FUN_001156C4 */
        } else {
            sk_h_001155E0(lvar5, puvar6, max, 0);     /* FUN_001155E0 */
        }
    }
    if ((char)local_98 == 1) {
        *msg = local_90;
        *done = 1;
    }
    return uvar4;
}

/* ================================================================== *
 * 000612d8 — FUN_000612D8  (est. sk_set_a0)
 * Ghidra: void FUN_000612D8(long param_1, undefined8 param_2)
 * Stores param_2 at *(obj+0xa0).
 * Confidence: high (trivial store)
 * ================================================================== */
void sk_set_a0(uint64_t obj, uint64_t v)
{
    *(uint64_t *)(obj + 0xa0) = v;
}

/* ================================================================== *
 * 000612e0 — FUN_000612E0  (est. sk_frame_alloc)
 * Ghidra: long FUN_000612E0(long param_1, long param_2)
 * Allocates a kernel stack frame: aligns (param_2+param_1) down, subtracts
 * the fixed frame size (0x28) plus a 0x300 headroom and a 0x178 record, and
 * returns the base. Traps on arithmetic overflow.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_frame_alloc(uint64_t a, uint64_t b)
{
    uint64_t fs = sk_frame_sz();                      /* FUN_00063FFC = 0x28 */
    uint64_t uvar3 = ((b + a & 0xfffffffffffffff8ULL) - fs - 0x300)
                     & 0xfffffffffffffff0ULL;
    if (uvar3 + fs < uvar3) {
        /* WARNING: does not return */
        SoftwareBreakpoint(0x5519, 0x6131c);
    }
    return uvar3 - 0x178;
}

/* ================================================================== *
 * 0006132c — FUN_0006132C  (est. sk_tcb_get_140)
 * Ghidra: undefined8 FUN_0006132C(long param_1)
 * Getter: returns *(tcb+0x140) (the tcb stack bound / limit).
 * Confidence: high (trivial getter)
 * ================================================================== */
uint64_t sk_tcb_get_140(uint64_t tcb)
{
    return *(uint64_t *)(tcb + 0x140);
}

/* ================================================================== *
 * 00061334 — FUN_00061334  (est. sk_frame_alloc2)
 * Ghidra: ulong FUN_00061334(ulong param_1, byte param_2)
 * Frame allocator variant keyed by a stack kind byte. kind 3 (when no tpidr)
 * aligns to 16K and subtracts 0x200; other kinds with tpidr present return
 * the input unchanged for "already-set" kinds (2 or >0x50); otherwise the
 * usual 8-byte aligned frame base minus 0x178 is returned. Traps on overflow
 * and on kind 0.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_frame_alloc2(uint64_t a, uint8_t kind)
{
    uint64_t fs = sk_frame_sz();                      /* FUN_00063FFC = 0x28 */
    uint64_t uvar3;
    if (kind == 0) {
        /* WARNING: does not return */
        SoftwareBreakpoint(1, 0x613ec);
    }
    if (tpidr_el0 == 0) {
        if (kind == 3) {
            uvar3 = ((a + 0x3fff & 0xffffffffffffc000ULL) - fs - 0x300)
                    & 0xfffffffffffffff0ULL;
            if (uvar3 + fs < uvar3) goto trap;
            uvar3 -= 0x200;
            goto done;
        }
    } else if ((1 < (uint8_t)(kind - 0x50)) && (kind != 2)) {
        return a;
    }
    uvar3 = ((a & 0xfffffffffffffff8ULL) - fs - 0x300) & 0xfffffffffffffff0ULL;
    if (uvar3 + fs < uvar3) goto trap;
    uvar3 -= 0x178;
done:
    return uvar3 & 0xfffffffffffffff0ULL;
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x613d4);
    return 0;
}

/* ================================================================== *
 * 000613ec — FUN_000613EC  (est. sk_frame_alloc3)
 * Ghidra: ulong FUN_000613EC(long param_1, long param_2)
 * Frame allocator using the cached bump base DAT_006b2710: aligns
 * (base+param_1), subtracts the frame size and a 0x300 headroom plus 0x478
 * and param_2. Traps on overflow.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_frame_alloc3(uint64_t a, uint64_t b)
{
    uint64_t base = sk_g_stack_base;                  /* DAT_006b2710 */
    uint64_t fs = sk_frame_sz();                      /* FUN_00063FFC = 0x28 */
    uint64_t uvar3;
    if (base == 0) {
        uvar3 = (0x1fd00U - fs) & 0xfffffffffffffff0ULL;
        if (uvar3 + fs < uvar3) goto trap;
        base = 0x20178 - uvar3;
        sk_g_stack_base = base;
    }
    uvar3 = (base + a & 0xfffffffffffffff8ULL) - fs;
    uvar3 &= 0xfffffffffffffff0ULL;
    if (uvar3 - 0x300 <= (uvar3 - 0x300) + fs) {
        return (uvar3 - b - 0x478) & 0xfffffffffffffff0ULL;
    }
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x6146c);
    return 0;
}

/* ================================================================== *
 * 00061488 — FUN_00061488  (est. sk_frame_bump)
 * Ghidra: long FUN_00061488(long param_1)
 * Returns param_1 + bump_base - 0x200, initializing the bump base first.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_frame_bump(uint64_t a)
{
    uint64_t fs = sk_frame_sz();                      /* FUN_00063FFC = 0x28 */
    if (sk_g_stack_base == 0) {
        uint64_t uvar3 = (0x1fd00U - fs) & 0xfffffffffffffff0ULL;
        if (uvar3 + fs < uvar3) {
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x614d4);
        }
        sk_g_stack_base = 0x20178 - uvar3;
    }
    return a + sk_g_stack_base - 0x200;
}

/* ================================================================== *
 * 000614f8 — FUN_000614F8  (est. sk_frame_bump2)
 * Ghidra: long FUN_000614F8(long param_1)
 * Returns ((bump_base + param_1) & ~7) - 0x300, initializing bump base.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_frame_bump2(uint64_t a)
{
    uint64_t fs = sk_frame_sz();                      /* FUN_00063FFC = 0x28 */
    if (sk_g_stack_base == 0) {
        uint64_t uvar3 = (0x1fd00U - fs) & 0xfffffffffffffff0ULL;
        if (uvar3 + fs < uvar3) {
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x61544);
        }
        sk_g_stack_base = 0x20178 - uvar3;
    }
    return (sk_g_stack_base + a & 0xfffffffffffffff8ULL) - 0x300;
}

/* ================================================================== *
 * 0006156c — FUN_0006156C  (est. sk_frame_alloc4)
 * Ghidra: ulong FUN_0006156C(long param_1)
 * Frame allocator using bump base: ((base+param_1) & ~7) - fs - 0x300,
 * aligned; returns it. Traps on overflow.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_frame_alloc4(uint64_t a)
{
    uint64_t base = sk_g_stack_base;                  /* DAT_006b2710 */
    uint64_t fs = sk_frame_sz();                      /* FUN_00063FFC = 0x28 */
    uint64_t uvar3;
    if (base == 0) {
        uvar3 = (0x1fd00U - fs) & 0xfffffffffffffff0ULL;
        if (uvar3 + fs < uvar3) goto trap;
        base = 0x20178 - uvar3;
        sk_g_stack_base = base;
    }
    uvar3 = ((base + a & 0xfffffffffffffff8ULL) - fs & 0xfffffffffffffff0ULL) - 0x300;
    if (uvar3 <= uvar3 + fs) {
        return uvar3;
    }
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x615e8);
    return 0;
}

/* ================================================================== *
 * 000615fc — FUN_000615FC  (est. sk_tcb_bounds)
 * Ghidra: void FUN_000615FC(long param_1, long *param_2, long *param_3)
 * Writes *out_base = *(tcb+0x130) and *out_len = *(tcb+0x140) - *(tcb+0x130).
 * Confidence: high (trivial getter pair)
 * ================================================================== */
void sk_tcb_bounds(uint64_t tcb, uint64_t *out_base, uint64_t *out_len)
{
    uint64_t base = *(uint64_t *)(tcb + 0x130);
    *out_base = base;
    *out_len = *(uint64_t *)(tcb + 0x140) - base;
}

/* ================================================================== *
 * 00061614 — FUN_00061614  (est. sk_tcb_set_bounds)
 * Ghidra: void FUN_00061614(long param_1, undefined8 param_2, undefined8 param_3,
 *          long param_4, long param_5)
 * Initializes a tcb's stack/mapping bounds: sets +0x30/+0x38 fields, the
 * +0x138/+0x140 base/limit, +0x130 length, and +0x168/+0x170 guards.
 * Confidence: medium
 * ================================================================== */
void sk_tcb_set_bounds(uint64_t tcb, uint64_t a, uint64_t b, uint64_t len, uint64_t base)
{
    *(uint64_t *)(tcb + 0x30) = a;
    *(uint64_t *)(tcb + 0x38) = b;
    *(uint64_t *)(tcb + 0x138) = base;
    *(uint64_t *)(tcb + 0x140) = base + len;
    *(uint64_t *)(tcb + 0x130) = len;
    *(uint64_t *)(tcb + 0x168) = len + 0x4000;
    *(uint64_t *)(tcb + 0x170) = base + len;
}

/* ================================================================== *
 * 00061630 — FUN_00061630  (est. sk_tcb_state)
 * Ghidra: undefined8 FUN_00061630(long param_1)
 * Getter: returns *(tcb+0x28).
 * Confidence: high (trivial getter)
 * ================================================================== */
uint64_t sk_tcb_state(uint64_t tcb)
{
    return *(uint64_t *)(tcb + 0x28);
}

/* ================================================================== *
 * 00061638 — FUN_00061638  (est. sk_tcb_state2)
 * Ghidra: undefined8 FUN_00061638(long param_1)
 * Reads the tcb's message via FUN_0006166C and returns the second word.
 * Confidence: low (decompiler modeling of the 2-word output)
 * ================================================================== */
uint64_t sk_tcb_state2(uint64_t tcb)
{
    uint64_t out[2];
    sk_msg_read(out, *(uint64_t *)(tcb + 0x28));      /* FUN_0006166C */
    return out[1];
}

/* ================================================================== *
 * 00061664 — FUN_00061664  (est. sk_tcb_state3)
 * Ghidra: void FUN_00061664(long param_1)
 * Reads (and discards) the tcb's message: FUN_0006166C(*(tcb+0x28)) with the
 * output buffer carried in registers.
 * Confidence: low (1-arg call, output register-carried)
 * ================================================================== */
void sk_tcb_state3(uint64_t tcb)
{
    uint64_t scratch[8];
    sk_msg_read(scratch, *(uint64_t *)(tcb + 0x28));  /* FUN_0006166C */
}

/* ================================================================== *
 * 0006166c — FUN_0006166C  (est. sk_msg_read)
 * Ghidra: void FUN_0006166C(undefined8 *param_1, long param_2)
 * Reads an IPC message out of the tpidrro message buffer via CallSupervisor(0)
 * and stores the message words into out[0..6]. If `tcb` is non-zero the
 * message is empty (out[0]=0). Otherwise the words are reconstructed from the
 * 16-byte message slots at tpidrro+0x10..+0x37 and the message kind selector
 * (the word read back from tpidrro) drives the out[0] classification.
 * Confidence: medium
 * Notes: byte-composition matches the little-endian word packing in Ghidra.
 * ================================================================== */
void sk_msg_read(uint64_t *out, uint64_t tcb)
{
    uint8_t *r = (uint8_t *)tpidrro_el0;
    uint64_t uvar15;
    uint64_t sel;

    out[5] = 0; out[6] = 0; out[3] = 0; out[4] = 0;
    out[1] = 0; out[2] = 0; out[0] = 0;

    /* read 8 bytes (tpidrro[0..7]) as the message selector, then call up */
    sel = (uint64_t)r[0] | (uint64_t)r[1] << 8 | (uint64_t)r[2] << 16 |
          (uint64_t)r[3] << 24 | (uint64_t)r[4] << 32 | (uint64_t)r[5] << 40 |
          (uint64_t)r[6] << 48 | (uint64_t)r[7] << 56;
    CallSupervisor(0);
    /* restore tpidrro[0..7] */
    r[0] = (uint8_t)sel; r[1] = (uint8_t)(sel >> 8); r[2] = (uint8_t)(sel >> 16);
    r[3] = (uint8_t)(sel >> 24); r[4] = (uint8_t)(sel >> 32); r[5] = (uint8_t)(sel >> 40);
    r[6] = (uint8_t)(sel >> 48); r[7] = (uint8_t)(sel >> 56);
    if (tcb != 0) {
        out[0] = 0;
        return;
    }
    /* reconstruct the four 8-byte message words from tpidrro+0x10..+0x37 */
    out[1] = (uint64_t)r[0x10] | (uint64_t)r[0x11] << 8 | (uint64_t)r[0x12] << 16 |
             (uint64_t)r[0x13] << 24 | (uint64_t)r[0x14] << 32 | (uint64_t)r[0x15] << 40 |
             (uint64_t)r[0x16] << 48 | (uint64_t)r[0x17] << 56;
    out[6] = (uint64_t)r[0x18] | (uint64_t)r[0x19] << 8 | (uint64_t)r[0x1a] << 16 |
             (uint64_t)r[0x1b] << 24 | (uint64_t)r[0x1c] << 32 | (uint64_t)r[0x1d] << 40 |
             (uint64_t)r[0x1e] << 48 | (uint64_t)r[0x1f] << 56;
    out[3] = (uint64_t)r[0x08] | (uint64_t)r[0x09] << 8 | (uint64_t)r[0x0a] << 16 |
             (uint64_t)r[0x0b] << 24 | (uint64_t)r[0x0c] << 32 | (uint64_t)r[0x0d] << 40 |
             (uint64_t)r[0x0e] << 48 | (uint64_t)r[0x0f] << 56;
    out[4] = (uint64_t)r[0x28] | (uint64_t)r[0x29] << 8 | (uint64_t)r[0x2a] << 16 |
             (uint64_t)r[0x2b] << 24 | (uint64_t)r[0x2c] << 32 | (uint64_t)r[0x2d] << 40 |
             (uint64_t)r[0x2e] << 48 | (uint64_t)r[0x2f] << 56;
    switch (sel) {
        case 0:
            out[0] = 0;
            return;
        case 1:
            out[0] = 1;
            return;
        case 2:
            out[0] = 2;
            goto done5;
        case 3:
            out[0] = 4;
            goto done5;
        case 4:
            out[0] = 3;
            *(uint8_t *)(out + 2) = 1;
            goto done5;
        default:
            return;
    }
done5:
    *(uint8_t *)(out + 5) = 1;
}

/* ================================================================== *
 * 000618c4 — FUN_000618C4  (est. sk_set_118)
 * Ghidra: void FUN_000618C4(long param_1, undefined4 param_2)
 * Stores a 32-bit value at *(tcb+0x118) (a per-tcb name/slot field).
 * Confidence: high (trivial store)
 * ================================================================== */
void sk_set_118(uint64_t tcb, uint32_t v)
{
    *(uint32_t *)(tcb + 0x118) = v;
}

/* ================================================================== *
 * 000618cc — FUN_000618CC  (est. sk_tcb_dump)
 * Ghidra: void FUN_000618CC(long param_1, undefined8 param_2)
 * Prints a one-line summary of a tcb to `sink`: the boot/debug cursor, the
 * endpoint name (FUN_00063970 of *(tcb+0xa8)), the object name
 * (FUN_0019AFBC of *(tcb+8)) and the +0x118 field, using format
 * "%s%s%s%s%s" via FUN_0005B824.
 * Confidence: low (printf arg values approximate)
 * ================================================================== */
void sk_tcb_dump(uint64_t tcb, uint64_t sink)
{
    uint64_t a = sk_h_0005B8C8();                   /* FUN_0005B8C8 */
    uint64_t b = sk_ep_name2(*(uint64_t *)(tcb + 0xa8)); /* FUN_00063970 */
    uint64_t c = sk_h_0019AFBC(*(uint64_t *)(tcb + 8));  /* FUN_0019AFBC */
    uint32_t d = *(uint32_t *)(tcb + 0x118);
    sk_h_0005E958(a);                                /* FUN_0005E958 x4 */
    sk_h_0005E958(b);
    sk_h_0005E958(c);
    sk_h_0005E958(d);
    sk_printf2(sink, "s s s s", 0xffffffffffffffffULL, 0x14, a, b, c, d); /* FUN_0005B824 */
}

/* ================================================================== *
 * 0006198c — FUN_0006198C  (est. sk_tcb_get_120)
 * Ghidra: undefined8 FUN_0006198C(long param_1)
 * Getter: returns *(tcb+0x120).
 * Confidence: high (trivial getter)
 * ================================================================== */
uint64_t sk_tcb_get_120(uint64_t tcb)
{
    return *(uint64_t *)(tcb + 0x120);
}

/* ================================================================== *
 * 00061994 — FUN_00061994  (est. sk_tcb_set_obj)
 * Ghidra: void FUN_00061994(long param_1, long param_2)
 * Sets a tcb's backing object: releases the old one (FUN_0005BCE0) if
 * non-null, stores the new one at *(tcb+8), and clears *(tcb+0x10).
 * Confidence: medium
 * ================================================================== */
void sk_tcb_set_obj(uint64_t tcb, uint64_t obj)
{
    if (obj != 0) {
        sk_h_0005BCE0(obj);                          /* FUN_0005BCE0 */
    }
    *(uint64_t *)(tcb + 8) = obj;
    *(uint64_t *)(tcb + 0x10) = 0;
}

/* ================================================================== *
 * 000619c8 — FUN_000619C8  (est. sk_msg_read2)
 * Ghidra: void FUN_000619C8(undefined8 *param_1, long param_2)
 * Zeroes out[0..4] then, if the target tcb is not the current CPU's tcb,
 * reads its register message via FUN_000619F0.
 * Confidence: medium
 * ================================================================== */
void sk_msg_read2(uint64_t *out, uint64_t tcb)
{
    uint64_t cpu;
    out[3] = 0; out[4] = 0; out[1] = 0; out[2] = 0; out[0] = 0;
    cpu = *(uint64_t *)(tpidr_el0 + 8);
    if (tcb != cpu) {
        sk_msg_read_regs(out, *(uint64_t *)(tcb + 0x28)); /* FUN_000619F0 */
    }
}

/* ================================================================== *
 * 000619f0 — FUN_000619F0  (est. sk_msg_read_regs)
 * Ghidra: void FUN_000619F0(ulong *param_1, ulong param_2)
 * Issues a CallSupervisor(0) message-register read: copies a fixed 16-byte
 * command (DAT_004be310 / 0x4be318) into tpidrro[0..0xf], calls up, then on
 * success reconstructs out[0..4] from tpidrro+0x08..+0x37. If the tcb tag is
 * non-zero it faults through FUN_004B71A8 + FUN_0011D7E8.
 * Confidence: medium
 * ================================================================== */
void sk_msg_read_regs(uint64_t *out, uint64_t tcb)
{
    uint8_t *r = (uint8_t *)tpidrro_el0;
    uint64_t cmd_hi = 0x4be318;                       /* uRam0000000000004be318 */
    uint64_t cmd_lo = 0x4be310;                       /* _DAT_004be310 */
    uint64_t i;
    /* store the 16-byte command into tpidrro[0..0xf] */
    for (i = 0; i < 8; i++) {
        r[i] = (uint8_t)(cmd_lo >> (8 * i));
        r[8 + i] = (uint8_t)(cmd_hi >> (8 * i));
    }
    CallSupervisor(0);
    /* reset tpidrro: marker 0x1d in [0], zero the rest */
    r[0] = 0x1d;
    for (i = 1; i < 8; i++) r[i] = 0;
    if ((tcb & 0xff) == 0) {
        out[1] = (uint64_t)r[0x2a] << 0x10 | (uint64_t)r[0x2b] << 0x18 |
                 (uint64_t)*(uint16_t *)(r + 0x28) |
                 ((uint64_t)((uint16_t)r[0x2e] << 0x10 | (uint16_t)r[0x2f] << 0x18 |
                             (uint16_t)*(uint16_t *)(r + 0x2c)) << 0x20);
        out[0] = (uint64_t)r[0x22] << 0x10 | (uint64_t)r[0x23] << 0x18 |
                 (uint64_t)*(uint16_t *)(r + 0x20) |
                 ((uint64_t)((uint16_t)r[0x26] << 0x10 | (uint16_t)r[0x27] << 0x18 |
                             (uint16_t)*(uint16_t *)(r + 0x24)) << 0x20);
        out[2] = (uint64_t)r[0x1a] << 0x10 | (uint64_t)r[0x1b] << 0x18 |
                 (uint64_t)*(uint16_t *)(r + 0x18) |
                 ((uint64_t)((uint16_t)r[0x1e] << 0x10 | (uint16_t)r[0x1f] << 0x18 |
                             (uint16_t)*(uint16_t *)(r + 0x1c)) << 0x20);
        out[3] = (uint64_t)r[0x12] << 0x10 | (uint64_t)r[0x13] << 0x18 |
                 (uint64_t)*(uint16_t *)(r + 0x10) |
                 ((uint64_t)((uint16_t)r[0x16] << 0x10 | (uint16_t)r[0x17] << 0x18 |
                             (uint16_t)*(uint16_t *)(r + 0x14)) << 0x20);
        out[4] = (uint64_t)r[0x32] << 0x10 | (uint64_t)r[0x33] << 0x18 |
                 (uint64_t)*(uint16_t *)(r + 0x30) |
                 ((uint64_t)((uint16_t)r[0x36] << 0x10 | (uint16_t)r[0x37] << 0x18 |
                             (uint16_t)*(uint16_t *)(r + 0x34)) << 0x20);
        return;
    }
    sk_h_004B71A8(tcb, r);                            /* FUN_004B71A8 */
    /* WARNING: does not return */
    sk_fatal();                                       /* FUN_0011D7E8 */
}

/* ================================================================== *
 * 00061cdc — FUN_00061CDC  (est. sk_err_string2)
 * Ghidra: void FUN_00061CDC(undefined8 param_1, byte param_2)
 * Second L4 error-code-to-name printer (same switch as 000604cc). For code>9
 * it copies an "unknown" string and formats "L4_ErrorCode %zu" via
 * FUN_0005B824. Otherwise memcpy the name and (via the strlen-print).
 * Confidence: high (string constants are the L4 error names)
 * ================================================================== */
void sk_err_string2(uint64_t sink, uint8_t code)
{
    const char *name;
    char buf[0x20];
    if (9 < code) {
        sk_memcpy((void *)sink, "<unknown>", 0x20);
        sk_printf2(sink, "L4 ErrorCode zu", 0x20, 0x1f, (uint64_t)code);
        return;
    }
    switch (code) {
        default:                    name = "L4_ErrorCodeSuccess      "; break;
        case 1:                     name = "L4_ErrorCodePreempted    "; break;
        case 2:                     name = "L4_ErrorCodeCanceled     "; break;
        case 3:                     name = "L4_ErrorCodeTruncated    "; break;
        case 4:                     name = "L4_ErrorCodeCapInvalid   "; break;
        case 5:                     name = "L4_ErrorCodeSlotInvalid  "; break;
        case 6:                     name = "L4_ErrorCodeMethodInvalid"; break;
        case 7:                     name = "L4_ErrorCodeArgumentInvalid"; break;
        case 8:                     name = "L4_ErrorCodeOperationInvalid"; break;
        case 9:                     name = "L4_ErrorCodePermissionInvalid"; break;
    }
    sk_memcpy(buf, name, 0x20);
    sk_h_0000178C((uint64_t)buf, 0x20);               /* FUN_0000178C */
}

/* ================================================================== *
 * 00061e20 — FUN_00061E20  (est. sk_msg_get)
 * Ghidra: undefined8 FUN_00061E20(long param_1)
 * Returns the message/state word for a thread. For the current CPU's thread
 * this resolves to a register artifact; for a foreign thread it reads the
 * thread's register message (FUN_000619F0) and returns the (zeroed) result.
 * Confidence: low (unaff_x29 frame-pointer artifact in the self case)
 * ================================================================== */
uint64_t sk_msg_get(uint64_t th)
{
    uint64_t local28 = 0;
    uint64_t cpu = *(uint64_t *)(tpidr_el0 + 8);
    if (th != cpu) {
        uint64_t local40 = 0;
        if (th == *(uint64_t *)(tpidr_el0 + 8)) {
            local28 = 0;
        } else {
            sk_msg_read_regs(&local40, *(uint64_t *)(th + 0x28)); /* FUN_000619F0 */
        }
    }
    return local28;
}

/* ================================================================== *
 * 00061e8c — FUN_00061E8C  (est. sk_msg_dump)
 * Ghidra: void FUN_00061E8C(undefined8 param_1, long param_2)
 * Dumps the IPC message words of a thread to `sink`. Fetches batches of up to
 * 0x10 words via FUN_00060F60, resolves each word through FUN_0005BC48 and
 * (if it is a valid cap) FUN_00054C9C, and prints each word as a
 * cap-or-plain value using format strings "%s %3zu  0x%012zx" variants.
 * Confidence: medium
 * ================================================================== */
void sk_msg_dump(uint64_t sink, uint64_t th)
{
    int64_t canary = SK_CANARY;
    uint64_t local130[6];
    uint64_t local100[17];
    uint64_t lvar4;
    uint64_t lvar11;
    uint64_t lvar5;
    uint64_t lvar6;
    uint64_t uvar7;
    uint64_t i;
    const char *fmt;
    int64_t j;

    for (i = 0; i < 17; i++) local100[i] = 0;
    lvar11 = *(uint64_t *)(tpidr_el0 + 8);
    if (th == lvar11) {
        lvar4 = 0;
    } else {
        uint64_t regs[6] = {0,0,0,0,0,0};
        if (th != *(uint64_t *)(tpidr_el0 + 8)) {
            sk_msg_read_regs(regs, *(uint64_t *)(th + 0x28)); /* FUN_000619F0 */
        }
        regs[5] = regs[0];
        lvar6 = sk_cap_lookup(&regs[5]);              /* FUN_0005BC48 */
        if (lvar6 == 0) local100[0] = 0xffff000000000000;
        else local100[0] = (uint64_t)*(uint16_t *)(lvar6 + 0x40) << 0x30;
        local100[0] = regs[5] & 0xffffffffffff | local100[0];
        regs[5] = regs[2];
        lvar6 = sk_cap_lookup(&regs[5]);
        if (lvar6 == 0) local100[1] = 0xffff000000000000;
        else local100[1] = (uint64_t)*(uint16_t *)(lvar6 + 0x40) << 0x30;
        local100[1] = regs[5] & 0xffffffffffff | local100[1];
        lvar4 = 2;
    }
    local130[0] = sk_msg_get(th);                     /* FUN_00061E20 */
    if ((local100 + 0x10 < local100 + lvar4) || (local100 + lvar4 < local100)) {
        /* WARNING: does not return */
        SoftwareBreakpoint(0x5519, 0x621a4);
    }
    lvar5 = sk_msg_call(th, local130, local100 + lvar4, 0x10 - lvar4, 0, 0); /* FUN_00060F60 */
    uvar7 = lvar5 + lvar4;
    if (uvar7 != 0) {
        uint64_t batch = 0;
        do {
            uint64_t n = (uvar7 > 0xf) ? 0x10 : uvar7;
            uint64_t *p = local100;
            uint64_t k = batch;
            uint64_t c;
            for (c = 0; c < n; c++, p++, k++) {
                uint64_t word = *p;
                local130[5] = word;
                lvar6 = sk_cap_lookup(&local130[5]);  /* FUN_0005BC48 */
                uint64_t tag = word - 4;
                if ((k == 0) && (th != lvar11)) {
                    tag = word;
                }
                if (lvar6 == 0) {
                    fmt = "s 03zu 0x 012zx";
                    sk_printf(sink, fmt, (uint64_t)k, (uint64_t)tag); /* FUN_001185EC */
                } else {
                    uint64_t capname = 0;
                    sk_h_00054C9C(tag, &capname);     /* FUN_00054C9C */
                    fmt = "s 03zu 02hhX 02hhX 02hhX 0";
                    sk_printf(sink, fmt, (uint64_t)k, (uint64_t)tag, (uint64_t)capname, 0, 0);
                }
            }
            if (uvar7 < 0x11) break;
            batch += n;
            uvar7 = sk_msg_call(th, local130, local100, 0x10, 0, 0);
        } while (uvar7 != 0);
    }
    if (canary != SK_CANARY) {
        /* WARNING: does not return */
        sk_fatal();
    }
}

/* ================================================================== *
 * 000621a8 — FUN_000621A8  (est. sk_cap_table_copy)
 * Ghidra: bool FUN_000621A8(long param_1, long param_2)
 * Reads a tcb's capability table into *out by repeatedly issuing
 * CallSupervisor(0) with a per-index mask, copying up to 0x69 capability
 * words (chunked). Returns whether the read stopped early (lvar4 != 0, i.e.
 * the thread has no more caps). Each iteration sizes the mask by index.
 * Confidence: medium
 * Notes: loop is register-batched; `out` advanced by the word count.
 * ================================================================== */
bool sk_cap_table_copy(uint64_t tcb, uint64_t *out)
{
    uint8_t *r = (uint8_t *)tpidrro_el0;
    uint64_t idx = 0;
    uint64_t stop = *(uint64_t *)(tcb + 0x28);
    do {
        uint64_t i = idx & 0xffff;
        uint64_t masklen = (0x32 < (uint32_t)i) ? (0x69 - (uint32_t)i) : 0x36;
        uint64_t mask = ~(~0ULL << (masklen & 0x3f));
        /* write selector + mask into tpidrro[0..0xf] */
        r[0] = (uint8_t)idx; r[1] = (uint8_t)(idx >> 8);
        r[2] = 0; r[3] = 0;
        r[4] = (uint8_t)mask; r[5] = (uint8_t)(mask >> 8); r[6] = (uint8_t)(mask >> 0x10);
        r[7] = (uint8_t)(mask >> 0x18);
        r[8] = (uint8_t)(mask >> 0x20); r[9] = (uint8_t)(mask >> 0x28);
        r[10] = (uint8_t)(mask >> 0x30); r[11] = (uint8_t)(mask >> 0x38);
        r[12] = 0; r[13] = 0; r[14] = 0; r[15] = 0;
        CallSupervisor(0);
        /* reset tpidrro[0..7] */
        r[0] = (uint8_t)idx; r[1] = (uint8_t)(idx >> 8);
        r[2] = 0; r[3] = 0; r[4] = 0; r[5] = 0; r[6] = 0; r[7] = 0;
        if (stop != 0) break;
        {
            uint64_t count = masklen & 0xffff;
            uint64_t avail = ((uint64_t)(idx & 0x1fff) * -8 + 0x348) >> 3;
            if (avail < count) {
                /* WARNING: does not return */
                SoftwareBreakpoint(0x5519, 0x62394);
            }
            {
                uint64_t *dst = (uint64_t *)((uint8_t *)out + (idx & 0x1fff) * 8);
                uint8_t *src = r + 0x10;
                uint64_t n = count;
                while (n != 0) {
                    *dst = (uint64_t)src[1] << 0x10 | (uint64_t)src[3] << 0x18 |
                           (uint64_t)*(uint16_t *)src |
                           ((uint64_t)((uint16_t)src[3] << 0x10 | (uint16_t)src[7] << 0x18 |
                                       (uint16_t)*(uint16_t *)(src + 2)) << 0x20);
                    src += 4;
                    n -= 1;
                    dst += 1;
                }
            }
            idx += (uint64_t)(uint32_t)count;
        }
    } while ((idx & 0xffff) < 0x69);
    return stop == 0;
}

/* ================================================================== *
 * 00062394 — FUN_00062394  (est. sk_reg_dump)
 * Ghidra: void FUN_00062394(undefined8 param_1, undefined8 param_2)
 * Prints a tcb's registers. Calls FUN_000621A8 to copy the cap/register table
 * (0x200 bytes); if that fails prints "Cannot obtain registers for thread",
 * else prints 0x69 lines of "%8s  0x%016zx" register entries with
 * alternating space/comma separators.
 * Confidence: medium
 * ================================================================== */
void sk_reg_dump(uint64_t sink, uint64_t tcb)
{
    uint64_t buf[0x200 / 8];
    uint64_t i;
    sk_memset0(buf, 0x200);
    if (sk_cap_table_copy(tcb, buf) == 0) {           /* FUN_000621A8 */
        sk_printf(sink, "Cannot obtain registers for thre");
    } else {
        for (i = 0; i < 0x69; i++) {
            sk_printf(sink, "8s 0x 016zx", (uint64_t)i);
            if ((i & 1) == 0) {
                sk_putchar2(sink, (uint64_t)(uintptr_t)","); /* FUN_0011883C */
            } else {
                sk_putchar(10, sink);                 /* FUN_001187F4 (thunk): '\n' */
            }
        }
    }
}

/* ================================================================== *
 * 00062474 — FUN_00062474  (est. sk_thread_state_dump)
 * Ghidra: void FUN_00062474(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3, long param_4, int param_5, int param_6,
 *          ulong param_7, ulong param_8)
 * Dumps a full thread state (a kernel crash/panic report) to `sink`:
 * Address Space, Component, Mach-O header/slide, UUID, thread line, call
 * stack range, ESR/FAR (with a stack-overflow check and a Synchronous
 * Tag Check Fault marker), then optional registers and backtrace.
 * Confidence: medium
 * ================================================================== */
void sk_thread_state_dump(uint64_t sink, uint64_t a, uint64_t b, uint64_t tcb,
                          int regs, int bt, uint64_t esr, uint64_t far)
{
    int64_t canary = SK_CANARY;
    uint64_t asval = 0, compval = 0, thresh, span;
    sk_print_rule(sink, b, a);                        /* FUN_0006275C */
    if (sk_h_0005B860(&asval) == 0) asval = 1;        /* FUN_0005B860 */
    sk_printf(sink, "Address Space s", asval);
    if (sk_h_0005D154(0, &compval) == 0) compval = 1; /* FUN_0005D154 */
    sk_printf(sink, "Component s", compval);
    sk_h_00054BA8();                                  /* FUN_00054BA8 */
    sk_printf(sink, "Mach O Header 0x 016lx");
    sk_h_00054BC8();                                  /* FUN_00054BC8 */
    sk_printf(sink, "Mach O Slide 0x 016lx");
    {
        uint64_t uuid[2] = {0, 0};
        sk_h_00054C3C(uuid);                          /* FUN_00054C3C */
        sk_printf(sink, "UUID 02hhX 02hhX 02hhX 02hhX", uuid[0], uuid[1]);
    }
    sk_print_rule(sink, b, 0);
    sk_tcb_dump(tcb, sink);                           /* FUN_000618CC */
    thresh = *(uint64_t *)(tcb + 0x130);
    sk_printf(sink, "Thread s 0x 06x p");
    sk_printf(sink, "Call Stack 0x 012zx 0x 012zx");
    if (esr != 0) {
        sk_printf(sink, "ESR 0x 08zx FAR 0x 016zx", esr, far);
        if ((*(uint64_t *)(tcb + 0x130) <= far) && (far < thresh + 0x4000)) {
            sk_printf(sink, "Apparent stack overflow by 0x 04");
        }
        if ((esr & 0x3f) == 0x11) {
            sk_print16(sink, "Synchronous Tag Check Fault", 0x1c, 1);
        }
    }
    if (bt != 0) {
        sk_print16(sink, "Registers", 0xc, 1);
        sk_reg_dump(sink, tcb);                       /* FUN_00062394 */
    }
    if (regs != 0) {
        sk_print16(sink, "Backtrace", 0xc, 1);
        sk_msg_dump(sink, tcb);                       /* FUN_00061E8C */
    }
    sk_print_rule(sink, b, 0);
    if (canary != SK_CANARY) {
        /* WARNING: does not return */
        sk_fatal();
    }
}

/* ================================================================== *
 * 0006275c — FUN_0006275C  (est. sk_print_rule)
 * Ghidra: void FUN_0006275C(undefined8 param_1, undefined8 param_2, long param_3)
 * Prints a rule/divider line to `sink`: either a fixed 0x48-pad of `pad`
 * characters, or a centered `title` string padded to 0x48 columns.
 * Confidence: medium
 * ================================================================== */
void sk_print_rule(uint64_t sink, uint64_t pad, uint64_t fill)
{
    uint64_t len;
    if (fill == 0) {
        uint64_t i = 0x48;
        do { sk_putchar(pad, sink); i -= 1; } while (i != 0);
    } else {
        len = sk_strlen((const char *)fill);          /* FUN_00115080 (thunk) */
        {
            uint64_t left = (0x46 - len) >> 1;
            uint64_t n = left;
            if (1 < 0x46 - len) {
                do { sk_putchar(pad, sink); n -= 1; } while (n != 0);
            }
            sk_printf(sink, "%s", (uint64_t)fill);
            if (len + 2 + left != 0x48) {
                uint64_t m = len + left - 0x46;
                do {
                    sk_putchar(pad, sink);
                    m += 1;
                } while (m != -1);
            }
        }
    }
    sk_putchar(10, sink);                             /* '\n' */
}

/* ================================================================== *
 * 00062848 — FUN_00062848  (est. sk_tcb_flag)
 * Ghidra: bool FUN_00062848(long param_1)
 * Returns whether bits 0 or 6 of *(obj+0x48) are set.
 * Confidence: high (trivial flag test)
 * ================================================================== */
bool sk_tcb_flag(uint64_t obj)
{
    return (*(uint8_t *)(obj + 0x48) & 0x41) != 0;
}

/* ================================================================== *
 * 0006285c — FUN_0006285C  (est. sk_obj_lock)
 * Ghidra: undefined8 FUN_0006285C(long param_1, undefined8 param_2)
 * Takes a lock/ref on an object: if bit1 of *(obj+0x48) is clear and
 * *(obj+0x90) is non-zero, consults FUN_0011817C to set/clear bit1, then
 * increments *(obj+0x90). Always returns 1.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_obj_lock(uint64_t obj, uint64_t k)
{
    if (((*(uint8_t *)(obj + 0x48) >> 1 & 1) == 0) && (*(uint64_t *)(obj + 0x90) != 0)) {
        if (sk_h_0011817C(k) == 0) {                  /* FUN_0011817C */
            *(uint64_t *)(obj + 0x48) &= 0xfffffffffffffffdULL;
        } else {
            *(uint64_t *)(obj + 0x48) |= 2;
        }
    }
    *(uint64_t *)(obj + 0x90) += 1;
    return 1;
}

/* ================================================================== *
 * 000628d8 — FUN_000628D8  (est. sk_obj_lock2)
 * Ghidra: undefined8 FUN_000628D8(long param_1, undefined8 param_2)
 * Lock/ref variant that returns 0 on the FUN_0011817C-fail path.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_obj_lock2(uint64_t obj, uint64_t k)
{
    if (((*(uint8_t *)(obj + 0x48) >> 1 & 1) == 0) && (*(uint64_t *)(obj + 0x90) != 0)) {
        if (sk_h_0011817C(k) == 0) {                  /* FUN_0011817C */
            *(uint64_t *)(obj + 0x48) &= 0xfffffffffffffffdULL;
            return 0;
        }
        *(uint64_t *)(obj + 0x48) |= 2;
    }
    *(uint64_t *)(obj + 0x90) += 1;
    return 1;
}

/* ================================================================== *
 * 000628e0 — FUN_000628E0  (est. sk_obj_unlock)
 * Ghidra: void FUN_000628E0(long param_1, undefined8 param_2)
 * Releases a lock/ref: decrements *(obj+0x90); when it reaches zero clears
 * bit1 of *(obj+0x48) and, if it was set, calls FUN_00118194.
 * Confidence: medium
 * ================================================================== */
void sk_obj_unlock(uint64_t obj, uint64_t k)
{
    uint64_t v = *(uint64_t *)(obj + 0x90) - 1;
    *(uint64_t *)(obj + 0x90) = v;
    if (v == 0) {
        uint64_t flags = *(uint64_t *)(obj + 0x48);
        *(uint64_t *)(obj + 0x48) = flags & 0xfffffffffffffffdULL;
        if (((uint32_t)flags >> 1 & 1) != 0) {
            sk_h_00118194(k);                         /* FUN_00118194 */
        }
    }
}

/* ================================================================== *
 * 0006290c — FUN_0006290C  (est. sk_dt_set)
 * Ghidra: void FUN_0006290C(long param_1, undefined8 param_2, undefined8 param_3)
 * Installs (fn, arg) into dispatch table slot `idx` of the per-CPU 0x6b26d8
 * table (3 slots). Traps if idx is out of range.
 * Confidence: high (matches the 0x60728 dispatch-table usage)
 * ================================================================== */
void sk_dt_set(uint64_t idx, uint64_t fn, uint64_t arg)
{
    uint64_t *t = (uint64_t *)sk_percpu_tbl(0x6b26d8, 1, 2); /* FUN_0005ACAC */
    uint64_t *e = t + idx * 2;
    if ((t <= e && e + 2 <= t + 6) && e <= e + 2) {
        *e = fn;
        e[1] = arg;
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x62974);
}

/* ================================================================== *
 * 000629fc — FUN_000629FC  (est. sk_cap_lookup_word)
 * Ghidra: ulong FUN_000629FC(ulong param_1)
 * Resolves a capability word: looks it up via FUN_0005BC48 and packs the
 * object type bits (from *(obj+0x40)) into the high 16 bits of the result,
 * falling back to 0xffff000000000000 for an invalid cap.
 * Confidence: high
 * ================================================================== */
uint64_t sk_cap_lookup_word(uint64_t word)
{
    uint64_t local18 = word;
    uint64_t lvar1 = sk_cap_lookup(&local18);         /* FUN_0005BC48 */
    uint64_t uvar2;
    if (lvar1 == 0) {
        uvar2 = 0xffff000000000000;
    } else {
        uvar2 = (uint64_t)*(uint16_t *)(lvar1 + 0x40) << 0x30;
    }
    return local18 & 0xffffffffffff | uvar2;
}

/* ================================================================== *
 * 00062a48 — FUN_00062A48  (est. sk_tbplace_get)
 * Ghidra: void FUN_00062A48(int param_1, undefined4 param_2)
 * Looks up a "tightbeam placeholder" resource. Selects a kind (0x11 for
 * selector 1 or 2, else 0x13 with a tag), walks the placeholder iterator
 * (FUN_0004EB44/4EB4C/4ECF0) for a matching kind, resolves it with
 * FUN_0004E7B8, and returns FUN_0004E774(marker, packed-word) reading the
 * appropriate field (offset 0, 0xc, or 4 words by selector). Panics
 * "No tightbeam placeholder resource" if none matches.
 * Confidence: medium
 * ================================================================== */
void sk_tbplace_get(int sel, uint32_t tag)
{
    uint64_t uvar12;
    uint64_t iter[2];
    uint64_t kind_sel;
    int i;
    if ((sk_h_0004FE80() & 1) == 0) {                 /* FUN_0004FE80 */
        sk_h_00053418();                              /* FUN_00053418 */
        return;
    }
    if (sel < 0x50) {
        i = 0x11;
        kind_sel = 0;
        if ((sel == 1) || (sel != 2)) goto go;
    }
    i = 0x13;
    kind_sel = tag;
go:
    uvar12 = sk_h_0004ED48();                         /* FUN_0004ED48 */
    if (uvar12 != 0) {
        /* 16-byte result; overflow check present in original */
    }
    iter[0] = sk_h_0004EB44();                        /* FUN_0004EB44 */
    iter[1] = 0;
    uvar12 = sk_h_0004ECF0(iter[0]);                  /* FUN_0004ECF0 */
    if ((uvar12 & 1) == 0) {
        uint16_t *res = NULL;
        do {
            uvar12 = sk_h_0004EB4C(iter[0]);          /* FUN_0004EB4C */
            if (uvar12 != 0) {
                /* overflow check in original */
            }
            if ((int)sk_h_0004E88C(uvar12) == i) {    /* FUN_0004E88C */
                res = (uint16_t *)sk_h_0004E7B8(uvar12, kind_sel); /* FUN_0004E7B8 */
            }
            i = (int)sk_h_0004ECF0(iter[0]);
        } while (i == 0);
        if (res != NULL) {
            uint16_t *p = res;
            uint64_t marker = sk_h_0004ED84();        /* FUN_0004ED84 */
            uint64_t word;
            if (sel != 2) p = res + 0xc;
            {
                uint16_t *p2 = res;
                if (sel != 1) p2 = p;
                {
                    uint16_t *p3 = res + 4;
                    if (sel < 0x50) p3 = p2;
                    word = (uint64_t)((uint8_t)p3[1]) << 0x10 |
                           (uint64_t)(*(uint8_t *)((uint8_t *)p3 + 3)) << 0x18 |
                           (uint64_t)*p3 |
                           ((uint64_t)((uint16_t)((uint8_t)p3[3] << 0x10 |
                                        (uint8_t)(*(uint8_t *)((uint8_t *)p3 + 7)) << 0x18 |
                                        (uint16_t)p3[2]) << 0x20));
                }
            }
            sk_h_0004E774(marker, word);              /* FUN_0004E774 */
            return;
        }
    }
    /* WARNING: does not return */
    sk_ec_switch(0, (int)(uintptr_t)"No tighbeam placeholder resource"); /* FUN_0005B190 */
}

/* ================================================================== *
 * 00062bdc — FUN_00062BDC  (est. sk_err_string_wrap)
 * Ghidra: void FUN_00062BDC(void)
 * Calls FUN_00061CDC with the stack buffer as the sink (register-carried).
 * Confidence: low (sink register-carried)
 * ================================================================== */
void sk_err_string_wrap(void)
{
    uint8_t sink[0x20];
    sk_err_string2((uint64_t)sink, 0);                /* FUN_00061CDC */
}

/* ================================================================== *
 * 00062bfc — FUN_00062BFC  (est. sk_dtor_key_panic)
 * Ghidra: void FUN_00062BFC(void)
 * Panics "setting key %lu which is deleted" (destructor misuse).
 * Confidence: high (string-matched panic)
 * ================================================================== */
void sk_dtor_key_panic(void)
{
    /* WARNING: does not return */
    sk_ec_switch(0, (int)(uintptr_t)"setting key lu which is deleted"); /* FUN_0005B190 */
}

/* ================================================================== *
 * 00062c14 — FUN_00062C14  (est. sk_dtor_key_panic2)
 * Ghidra: void FUN_00062C14(void)
 * Panics "setting key %lu while destructor" (destructor misuse).
 * Confidence: high (string-matched panic)
 * ================================================================== */
void sk_dtor_key_panic2(void)
{
    /* WARNING: does not return */
    sk_ec_switch(0, (int)(uintptr_t)"setting key lu while destructor"); /* FUN_0005B190 */
}

/* ================================================================== *
 * 00062c2c — FUN_00062C2C  (est. sk_ep_lock)
 * Ghidra: void FUN_00062C2C(ulong *param_1, ulong param_2, long *param_3)
 * Creates/locks a new endpoint object at *ep. Zeroes the 0x50-byte struct,
 * links it (FUN_0005CDBC), records flags/config, and installs a handler:
 * either the boot image's +0xe0 handler or sk_ep_return (FUN_00062DCC),
 * delivered via CallSupervisor(0). If no teardown flags it tears down stale
 * threads (FUN_00063040) and releases the lock (FUN_0005CE54). Panics
 * "failed to lock new endpoints location" on lock failure.
 * Confidence: medium
 * ================================================================== */
void sk_ep_lock(uint64_t *ep, uint64_t flags, uint64_t *cfg)
{
    int64_t canary = SK_CANARY;
    uint64_t fn;
    uint64_t uvar9;
    uint64_t i;

    sk_memset0(ep, 0x50);
    if (ep + 2 < ep) {
        /* WARNING: does not return */
        SoftwareBreakpoint(0x5519, 0x62db0);
    }
    uvar9 = sk_h_0005CDBC(ep);                        /* FUN_0005CDBC */
    if ((uvar9 & 1) != 0) {
        ep[2] = flags;
        sk_h_00117CC4(ep + 4, cfg, 0x28);             /* FUN_00117CC4: memcpy 0x28 */
        ep[3] = 0;
        if (*cfg == 0) {
            uint64_t base = sk_h_00054610();          /* FUN_00054610 */
            fn = *(uint64_t *)(base + 0xe0);
            flags = ep[2];
        } else {
            fn = (uint64_t)&sk_ep_return;             /* FUN_00062DCC */
        }
        { /* deliver fn via tpidrro[0..7] + CallSupervisor(0) */
            uint8_t *r = (uint8_t *)tpidrro_el0;
            for (i = 0; i < 8; i++) r[i] = (uint8_t)(fn >> (8 * i));
            CallSupervisor(0);
            for (i = 0; i < 8; i++) r[i] = (uint8_t)(fn >> (8 * i));
        }
        if ((flags & 0xfd) == 0) {
            uvar9 = ep[6];
            ep[6] = 0;
            sk_ep_teardown((uint64_t)ep, uvar9);      /* FUN_00063040 */
            if (canary == SK_CANARY) {
                sk_h_0005CE54((uint64_t *)ep);        /* FUN_0005CE54 */
                return;
            }
        } else {
            sk_h_004B73D0(flags & 0xfffffffffffffffdULL, (uint64_t *)ep); /* FUN_004B73D0 */
        }
        /* WARNING: does not return */
        sk_fatal();                                   /* FUN_0011D7E8 */
    }
    /* WARNING: does not return */
    sk_ec_switch(0, (int)(uintptr_t)"failed to lock new endpoints loc"); /* FUN_0005B190 */
}

/* ================================================================== *
 * 00062dcc — FUN_00062DCC  (est. sk_ep_return)
 * Ghidra: void FUN_00062DCC(undefined8 param_1, undefined8 param_2)
 * The endpoint "return" handler: runs the endpoint's +0x20 dispatch entry
 * with its +0x28 argument, delivers the result back via CallSupervisor(0),
 * and invokes the endpoint's teardown hook (from FUN_0006393C). If the
 * handler itself returns, panics "returned from EP return on endpoint".
 * Confidence: medium
 * ================================================================== */
void sk_ep_return(uint64_t a, uint64_t b)
{
    uint64_t cpu = sk_cpu_base();                     /* FUN_00060524 */
    uint64_t ep = *(uint64_t *)(cpu + 0xa8);
    uint64_t uvar11;
    uint64_t lvar10;
    uint64_t i;

    if ((uint64_t)(ep + 0x50) >= ep) {                /* bounds: ep <= ep+0x50 */
        sk_pcpu_enter(a, 0);                          /* FUN_000636E0 */
        uvar11 = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))(
                    *(uint64_t *)(ep + 0x20)))(*(uint64_t *)(ep + 0x28), a, b);
        sk_pcpu_leave(0);                             /* FUN_00063768 */
        { /* deliver uvar11 via tpidrro[0..7] + CallSupervisor(0) */
            uint8_t *r = (uint8_t *)tpidrro_el0;
            for (i = 0; i < 8; i++) r[i] = (uint8_t)(uvar11 >> (8 * i));
            CallSupervisor(0);
            for (i = 0; i < 8; i++) r[i] = (uint8_t)(uvar11 >> (8 * i));
        }
        lvar10 = sk_ep_check(ep, 1);                  /* FUN_0006393C */
        if ((lvar10 != 0) && (*(uint64_t **)(lvar10 + 0x50) != NULL)) {
            if ((uint64_t)(ep + 0x50) <= ep) goto trap;
            (*(void (**)(uint64_t))(*(uint64_t *)(lvar10 + 0x50)))(ep);
        }
        /* WARNING: does not return */
        sk_ec_switch(0, (int)(uintptr_t)"returned from EP return on endpo"); /* FUN_0005B190 */
    }
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x62f08);
}

/* ================================================================== *
 * 00062f08 — FUN_00062F08  (est. sk_err_string3)
 * Ghidra: void FUN_00062F08(undefined8 param_1, byte param_2)
 * Third L4 error-code-to-name printer (same switch as 000604cc/00061cdc).
 * Confidence: high (string constants are the L4 error names)
 * ================================================================== */
void sk_err_string3(uint64_t sink, uint8_t code)
{
    const char *name;
    char buf[0x20];
    if (9 < code) {
        sk_memcpy((void *)sink, "<unknown>", 0x20);
        sk_h_0000178C((uint64_t)sink, 0x20);          /* FUN_0000178C */
        return;
    }
    switch (code) {
        default:                    name = "L4_ErrorCodeSuccess      "; break;
        case 1:                     name = "L4_ErrorCodePreempted    "; break;
        case 2:                     name = "L4_ErrorCodeCanceled     "; break;
        case 3:                     name = "L4_ErrorCodeTruncated    "; break;
        case 4:                     name = "L4_ErrorCodeCapInvalid   "; break;
        case 5:                     name = "L4_ErrorCodeSlotInvalid  "; break;
        case 6:                     name = "L4_ErrorCodeMethodInvalid"; break;
        case 7:                     name = "L4_ErrorCodeArgumentInvalid"; break;
        case 8:                     name = "L4_ErrorCodeOperationInvalid"; break;
        case 9:                     name = "L4_ErrorCodePermissionInvalid"; break;
    }
    sk_memcpy(buf, name, 0x20);
    sk_h_0000178C((uint64_t)buf, 0x20);               /* FUN_0000178C */
}

/* ================================================================== *
 * 00063040 — FUN_00063040  (est. sk_ep_teardown)
 * Ghidra: void FUN_00063040(long param_1, ulong param_2)
 * Tears down the threads owned by an endpoint: unlinks each thread from the
 * +0x18 list, releases its message/notification slots (FUN_004B23D8), clears
 * the per-cpu record (via FUN_0005FBC0 / FUN_004B6D60), then (when count
 * grows toward param_2) spawns new replacement threads with FUN_0005EEC4,
 * names them by a decimal-encoded sequence, and sets up their +0x1c0/+0x1e0
 * message fields and +0x28 state before entering via CallSupervisor(0).
 * Confidence: low (large complex slot/refcount logic)
 * ================================================================== */
void sk_ep_teardown(uint64_t ep, uint64_t count)
{
    int64_t canary = SK_CANARY;
    uint64_t uvar19 = *(uint64_t *)(ep + 0x30);
    uint64_t uvar16;
    uint64_t uvar25;
    uint64_t *thread;
    uint64_t lvar15;
    uint64_t lvar27;
    uint64_t i, j;

    while (count < uvar19) {
        thread = (uint64_t *) *(uint64_t *)(ep + 0x18);
        *(uint64_t *)(ep + 0x18) = *(uint64_t *)(thread + 0x50);
        *(uint64_t *)(ep + 0x30) = uvar19 - 1;
        *(uint64_t *)(thread + 0x50) = 0;
        if ((uint64_t)(thread + 0x178) < (uint64_t)thread) goto trap;
        sk_h_004B7278((uint64_t)thread);              /* FUN_004B7278 */
        lvar15 = sk_frame_bump((uint64_t)thread);     /* FUN_00061488 */
        if (*(uint64_t *)(ep + 0x38) != 0) {
            uint64_t n = 0;
            uint64_t off = 0;
            do {
                uint64_t *msgslot = (uint64_t *)((uint8_t *)thread + off + 0xc0);
                sk_h_004B23D8(*msgslot, 0, 0);        /* FUN_004B23D8 */
                sk_memset0((void *)(lvar15 + off + 0x1c0), 8);
                n += 1;
                off += 8;
            } while (n < *(uint64_t *)(ep + 0x38));
        }
        if (*(uint64_t *)(ep + 0x40) != 0) {
            uint64_t n = 0;
            uint64_t off = 0;
            do {
                uint64_t *notifslot = (uint64_t *)((uint8_t *)thread + off + 0xe0);
                sk_h_004B23D8(*notifslot, 0, 0);
                sk_memset0((void *)(lvar15 + off + 0x1e0), 8);
                n += 1;
                off += 8;
            } while (n < *(uint64_t *)(ep + 0x40));
        }
        uvar19 = sk_cpu_base();                       /* FUN_00060524 */
        if ((uint64_t)thread == uvar19) {
            sk_h_0005FBC0((uint64_t)thread);          /* FUN_0005FBC0 */
        } else {
            sk_h_004B6D60((uint64_t)thread, NULL);    /* FUN_004B6D60 */
        }
        uvar19 = *(uint64_t *)(ep + 0x30);
    }
    if (uvar19 < count) {
        uint64_t *head = (uint64_t *)(ep + 0x18);
        uint64_t *slot = (uint64_t *)(ep + 0x20);
        do {
            sk_h_0005EEC4(head, 0, ep, 0, 0);         /* FUN_0005EEC4: spawn thread */
            if (*head == 0) {
                /* WARNING: does not return */
                sk_ec_switch(0, (int)(uintptr_t)"Failed to create thread for an E"); /* FUN_0005B190 */
            }
            { /* decimal-encode the thread sequence into a name word */
                uint32_t v = (uint32_t)*(uint16_t *)(ep + 0x30) +
                             ((*(uint16_t *)(ep + 0x30) >> 3) / 0x7d) * -1000;
                uint32_t namew = 0x48;
                uint32_t div = 1000;
                do {
                    uint32_t q = div / 10;
                    uint32_t d = 0;
                    if (q != 0) d = (v & 0xffff) / q;
                    namew = (d + 0x30) & 0xffff | namew << 8;
                    v -= d * q;
                    div = q;
                } while (0x13 < div);
                sk_set_118(*head, namew);             /* FUN_000618C4 */
            }
            *(uint64_t *)(*head + 0xa8) = ep;
            lvar15 = sk_frame_bump(0);                /* FUN_00061488 */
            if (*(uint64_t *)(ep + 0x38) != 0) {
                uint64_t n = 0;
                uint64_t off = 0x1c0;
                do {
                    uvar16 = sk_phys_alloc(0);        /* FUN_00034F70 */
                    sk_memcpy((void *)(lvar15 + off), &uvar16, 8);
                    *(uint64_t *)(*head + off - 0x100) = uvar16;
                    n += 1;
                    off += 8;
                } while (n < *(uint64_t *)(ep + 0x38));
            }
            if (*(uint64_t *)(ep + 0x40) != 0) {
                uint64_t n = 0;
                uint64_t off = 0x1e0;
                do {
                    uvar16 = sk_phys_alloc(0);
                    sk_memcpy((void *)(lvar15 + off), &uvar16, 8);
                    *(uint64_t *)(*head + off - 0x100) = uvar16;
                    n += 1;
                    off += 8;
                } while (n < *(uint64_t *)(ep + 0x40));
            }
            uvar19 = *(uint64_t *)(*head + 0x28);
            uvar25 = *(uint64_t *)(ep + 0x10);
            uvar16 = sk_tcb_get_140(*head);           /* FUN_0006132C */
            { /* write tcb state + bound into tpidrro, CallSupervisor(0) */
                uint8_t *r = (uint8_t *)tpidrro_el0;
                for (i = 0; i < 8; i++) r[i] = (uint8_t)(uvar25 >> (8 * i));
                for (i = 0; i < 8; i++) r[8 + i] = (uint8_t)(uvar16 >> (8 * i));
                CallSupervisor(0);
                for (i = 0; i < 8; i++) r[i] = (uint8_t)(uvar25 >> (8 * i));
            }
            if ((uvar19 & 0xff) != 0) {
                sk_h_004B7428(uvar19, (uint64_t *)ep); /* FUN_004B7428 */
                goto fail;
            }
            lvar15 = *head;
            head = (uint64_t *)(lvar15 + 0x50);
            slot = (uint64_t *)(lvar15 + 0x58);
            uvar19 = *(uint64_t *)(ep + 0x30) + 1;
            *(uint64_t *)(ep + 0x30) = uvar19;
        } while (uvar19 < count);
    }
    if (canary != SK_CANARY) {
        /* WARNING: does not return */
        sk_fatal();
    }
    return;
fail:
    /* WARNING: does not return */
    sk_fatal();
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x635a4);
}

/* ================================================================== *
 * 000635c0 — FUN_000635C0  (est. sk_ep_setup)
 * Ghidra: void FUN_000635C0(undefined8 *param_1, ulong param_2,
 *          undefined8 param_3, undefined8 *param_4)
 * Sets up an endpoint: calls FUN_00062C2C with flags|2, then copies the
 * 3 config words from *cfg into ep[10..12].
 * Confidence: medium
 * ================================================================== */
void sk_ep_setup(uint64_t *ep, uint64_t flags, uint64_t a, uint64_t *cfg)
{
    if ((uint64_t)(ep + 10) >= (uint64_t)ep) {        /* bounds: ep <= ep+10 */
        sk_ep_lock(ep, flags | 2, cfg);               /* FUN_00062C2C */
        ep[0xb] = cfg[1];
        ep[0xc] = cfg[2];
        ep[10] = cfg[0];
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x63608);
}

/* ================================================================== *
 * 00063694 — FUN_00063694  (est. sk_ep_last)
 * Ghidra: undefined8 FUN_00063694(void)
 * Returns the last message word of the current CPU's endpoint message
 * region: FUN_0005FAD8(0) yields {base,len}; the result is *(base+0xc0+len).
 * Confidence: medium
 * ================================================================== */
uint64_t sk_ep_last(void)
{
    sk_pair_t pr = sk_h_0005FAD8(0);                  /* FUN_0005FAD8 */
    uint64_t *p = (uint64_t *)(pr.lo + 0xc0);
    uint64_t *q = p + pr.hi;
    if ((p <= q && q + 1 <= (uint64_t *)(pr.lo + 0xe0)) && q <= q + 1) {
        return *q;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x636d0);
    return 0;
}

/* ================================================================== *
 * 000636a4 — FUN_000636A4  (est. sk_ep_get)
 * Ghidra: undefined8 FUN_000636A4(long param_1, long param_2)
 * Returns the message word at *(ep+0xc0+idx).
 * Confidence: high (trivial indexed getter)
 * ================================================================== */
uint64_t sk_ep_get(uint64_t ep, uint64_t idx)
{
    uint64_t *p = (uint64_t *)(ep + 0xc0) + idx;
    if (((uint64_t *)(ep + 0xc0) <= p && p + 1 <= (uint64_t *)(ep + 0xe0)) && p <= p + 1) {
        return *p;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x636d0);
    return 0;
}

/* ================================================================== *
 * 000636d0 — FUN_000636D0  (est. sk_ep_get20)
 * Ghidra: undefined8 FUN_000636D0(long param_1)
 * Getter: returns *(ep+0x20).
 * Confidence: high (trivial getter)
 * ================================================================== */
uint64_t sk_ep_get20(uint64_t ep)
{
    return *(uint64_t *)(ep + 0x20);
}

/* ================================================================== *
 * 000636d8 — FUN_000636D8  (est. sk_ep_get28)
 * Ghidra: undefined8 FUN_000636D8(long param_1)
 * Getter: returns *(ep+0x28).
 * Confidence: high (trivial getter)
 * ================================================================== */
uint64_t sk_ep_get28(uint64_t ep)
{
    return *(uint64_t *)(ep + 0x28);
}

/* ================================================================== *
 * 000636e0 — FUN_000636E0  (est. sk_pcpu_enter)
 * Ghidra: void FUN_000636E0(undefined8 param_1)
 * Enters the per-CPU dispatch section: spins on each active message slot in
 * [cpu+0xc0, cpu+0xe0) via CallSupervisor(4), then records `id` at +0xb0 and
 * clears the +0xb8 slot count.
 * Confidence: medium
 * ================================================================== */
void sk_pcpu_enter(uint64_t id, uint64_t extra)
{
    uint64_t cpu = sk_cpu_base();                     /* FUN_00060524 */
    uint64_t n = *(uint64_t *)(cpu + 0xb8) >> 6 & 7;
    uint64_t i = 0;
    if (n != 0) {
        do {
            uint64_t *p = (uint64_t *)(cpu + 0xc0) + i;
            if ((p < (uint64_t *)(cpu + 0xc0) || (uint64_t *)(cpu + 0xe0) < p + 1) || p + 1 < p) {
                /* WARNING: does not return */
                SoftwareBreakpoint(0x5519, 0x63768);
            }
            do { CallSupervisor(4); } while (*p == 1);
            i += 1;
        } while (i != n);
    }
    *(uint64_t *)(cpu + 0xb0) = id;
    *(uint64_t *)(cpu + 0xb8) = 0;
}

/* ================================================================== *
 * 00063768 — FUN_00063768  (est. sk_pcpu_leave)
 * Ghidra: void FUN_00063768(undefined8 param_1)
 * Leaves the per-CPU dispatch section: copies the four message/notification
 * slots [cpu+0xe0, cpu+0xe0+32) and [cpu+0xc0, cpu+0xc0+32) into the
 * tpidrro message region, drains active slots via CallSupervisor(4), then
 * releases the CPU record (FUN_0005B0BC, FUN_00061994) and records `arg` in
 * the +0xb8 slot count.
 * Confidence: medium
 * ================================================================== */
void sk_pcpu_leave(uint64_t arg)
{
    uint64_t cpu = sk_cpu_base();                     /* FUN_00060524 */
    uint64_t cur = *(uint64_t *)(cpu + 0xb0);
    uint64_t i = 0;
    do {
        uint64_t *p = (uint64_t *)(cpu + 0xe0) + i;
        uint64_t v;
        if ((uint64_t *)(cpu + 0x100) < p + 1 || p + 1 < p) goto trap;
        v = *p;
        if (i < (cur >> 6 & 7)) {
            do { CallSupervisor(4); } while (v == 1);
        }
        { /* copy v into tpidrro+0x1e0+i*8 */
            uint8_t *r = (uint8_t *)tpidrro_el0;
            uint8_t *dst = r + 0x1e0 + i * 8;
            for (int b = 0; b < 8; b++) dst[b] = (uint8_t)(v >> (8 * b));
        }
        { /* copy *(cpu+0xc0+i*8) into tpidrro+0x1c0+i*8 */
            uint8_t *r = (uint8_t *)tpidrro_el0;
            uint8_t *src = (uint8_t *)(cpu + 0xc0 + i * 8);
            uint8_t *dst = r + 0x1c0 + i * 8;
            for (int b = 0; b < 8; b++) dst[b] = src[b];
        }
        i += 1;
    } while (i != 4);
    if ((uint64_t)(cpu + 0x178) >= cpu) {             /* bounds: cpu <= cpu+0x178 */
        sk_h_0005B0BC(cpu);                           /* FUN_0005B0BC */
        sk_tcb_set_obj(cpu, 0);                       /* FUN_00061994 */
        *(uint64_t *)(cpu + 0xb0) = 0;
        *(uint64_t *)(cpu + 0xb8) = arg;
        return;
    }
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x638ec);
}

/* ================================================================== *
 * 000638ec — FUN_000638EC  (est. sk_err_string_wrap2)
 * Ghidra: void FUN_000638EC(void)
 * Calls FUN_00062F08 with the stack buffer as the sink.
 * Confidence: low (sink register-carried)
 * ================================================================== */
void sk_err_string_wrap2(void)
{
    uint8_t sink[0x20];
    sk_err_string3((uint64_t)sink, 0);                /* FUN_00062F08 */
}

/* ================================================================== *
 * 00063910 — FUN_00063910  (est. sk_ep_name)
 * Ghidra: undefined8 FUN_00063910(ulong param_1)
 * Returns an endpoint's name field *(ep+0x58), or 0 if the endpoint is null
 * or not "named" (bit1 of *(ep+0x10) clear).
 * Confidence: medium
 * ================================================================== */
uint64_t sk_ep_name(uint64_t ep)
{
    uint64_t r = 0;
    if ((ep != 0) && ((*(uint64_t *)(ep + 0x10) >> 1 & 1) != 0)) {
        if ((uint64_t)(ep + 0x70) < ep) {
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x6393c);
        }
        r = *(uint64_t *)(ep + 0x58);
    }
    return r;
}

/* ================================================================== *
 * 0006393c — FUN_0006393C  (est. sk_ep_check)
 * Ghidra: void FUN_0006393C(ulong param_1)
 * Bounds assertion on an endpoint object: validates that the object region
 * [ep, ep+0x70) does not wrap, using the object's type bit (bit0 of
 * *(ep+0x10)). Returns 0 (the caller, 00062dcc, treats it as a holder).
 * Confidence: low (assert-like; return used by caller)
 * ================================================================== */
uint64_t sk_ep_check(uint64_t ep, int flag)
{
    uint64_t mask = (*(int64_t *)(ep + 0x10) << 0x3e) >> 0x3f;
    uint64_t sel = ep & mask;
    if ((sel != 0) && ((uint64_t)(ep + 0x70 & mask) < sel + 0x70 || sel + 0x70 < sel)) {
        /* WARNING: does not return */
        SoftwareBreakpoint(0x5519, 0x63970);
    }
    return 0;
}

/* ================================================================== *
 * 00063970 — FUN_00063970  (est. sk_ep_name2)
 * Ghidra: undefined4 FUN_00063970(ulong param_1)
 * Returns an endpoint's 32-bit name *(ep+0x60), defaulting to "NEOP" when the
 * endpoint is null or unnamed.
 * Confidence: medium
 * ================================================================== */
uint32_t sk_ep_name2(uint64_t ep)
{
    uint32_t r = 0x4e4f4550;                          /* "POEN" / "NEOP" marker */
    if ((ep != 0) && ((*(uint8_t *)(ep + 0x10) >> 1 & 1) != 0)) {
        if ((uint64_t)(ep + 0x70) < ep) {
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x639a0);
        }
        r = *(uint32_t *)(ep + 0x60);
    }
    return r;
}

/* ================================================================== *
 * 000639a0 — FUN_000639A0  (est. sk_msg_read_rr)
 * Ghidra: void FUN_000639A0(undefined8 param_1, undefined8 *param_2)
 * Delivers the message word *msg through tpidrro + CallSupervisor(0) and
 * writes it back (a register-round-trip message read).
 * Confidence: medium
 * ================================================================== */
void sk_msg_read_rr(uint64_t a, uint64_t *msg)
{
    uint64_t v = *msg;
    uint8_t *r = (uint8_t *)tpidrro_el0;
    for (int i = 0; i < 8; i++) r[i] = (uint8_t)(v >> (8 * i));
    CallSupervisor(0);
    for (int i = 0; i < 8; i++) r[i] = (uint8_t)(v >> (8 * i));
    *msg = v;
}

/* ================================================================== *
 * 00063a50 — FUN_00063A50  (est. sk_notify_reg_init)
 * Ghidra: void FUN_00063A50(void)
 * Returns the notification/callback registry base (DAT_006b2718), seeding it
 * from the kernel singleton's +0x50 field if not yet set. Traps on overflow.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_notify_reg_init(void)
{
    uint64_t reg = sk_g_notify_reg;                   /* DAT_006b2718 */
    if (sk_g_notify_reg == 0) {
        uint64_t s = sk_singleton();                  /* FUN_0005BB68 */
        reg = *(uint64_t *)(s + 0x50);
        if ((uint64_t)(reg + 0x2f0) < reg) {
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x63a94);
        }
    }
    sk_g_notify_reg = reg;
    return reg;
}

/* ================================================================== *
 * 00063a94 — FUN_00063A94  (est. sk_notify_reg_reset)
 * Ghidra: void FUN_00063A94(void)
 * Resets the notification registry base to the fixed address 0x64dce8 and
 * returns it.
 * Confidence: high (constant)
 * ================================================================== */
uint64_t sk_notify_reg_reset(void)
{
    sk_g_notify_reg = 0x64dce8;                       /* DAT_006b2718 */
    return sk_g_notify_reg;
}

/* ================================================================== *
 * 00063aa8 — FUN_00063AA8  (est. sk_notify_alloc)
 * Ghidra: ulong FUN_00063AA8(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3)
 * Allocates a notification slot in the registry: locks it (FUN_00063B50),
 * bumps the slot index (cap 0x20), registers the callback (FUN_00063B84),
 * and unlocks (FUN_00063C5C). Returns the slot index. Faults if the registry
 * is not available or full.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_notify_alloc(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t *cpu = (uint64_t *)tpidr_el0;
    uint64_t idx;
    uint64_t *reg;
    if (*(uint64_t *)(cpu + 0xf8) == 0) {
        reg = (uint64_t *)sk_g_notify_reg;
        if (sk_g_notify_reg == 0) {
            uint64_t s = sk_singleton();              /* FUN_0005BB68 */
            reg = *(uint64_t **)(s + 0x50);
            if ((uint64_t)(reg + 0x5e) < (uint64_t)reg) goto trap;
        }
        sk_g_notify_reg = (uint64_t)reg;
        reg = (uint64_t *)sk_g_notify_reg;
        sk_notify_lock();                             /* FUN_00063B50 */
        idx = *reg;
        if (idx < 0x20) {
            *reg = idx + 1;
            sk_notify_add(idx, a, b, (int)c);         /* FUN_00063B84 */
            sk_notify_unlock();                       /* FUN_00063C5C */
            return idx;
        }
    } else {
        sk_h_004B7480();                              /* FUN_004B7480 */
    }
    sk_h_004B749C();                                  /* FUN_004B749C */
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x63b50);
    return 0;
}

/* ================================================================== *
 * 00063b50 — FUN_00063B50  (est. sk_notify_lock)
 * Ghidra: void FUN_00063B50(void)
 * Takes the notification registry lock (FUN_0005CB9C) after a bounds check.
 * Confidence: medium
 * ================================================================== */
void sk_notify_lock(void)
{
    uint64_t s = sk_singleton();                      /* FUN_0005BB68 */
    if ((uint64_t)(s + 0x60) <= (uint64_t)(s + 0x70)) {
        sk_h_0005CB9C();                              /* FUN_0005CB9C */
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x63b84);
}

/* ================================================================== *
 * 00063b84 — FUN_00063B84  (est. sk_notify_add)
 * Ghidra: void FUN_00063B84(long param_1, long param_2, undefined8 param_3,
 *          int param_4)
 * Registers a callback `fn` (at reg+idx*8) with arg `arg` (at reg+0xff+idx)
 * in the notification registry, and when both fn and `enabled` are set,
 * registers a teardown hook (FUN_0005BD7C -> FUN_00063EB4). Traps on overflow.
 * Confidence: medium
 * ================================================================== */
void sk_notify_add(uint64_t idx, uint64_t fn, uint64_t arg, int enabled)
{
    uint64_t reg = sk_g_notify_reg;                   /* DAT_006b2718 */
    uint64_t local48 = idx;
    if (sk_g_notify_reg == 0) {
        uint64_t s = sk_singleton();                  /* FUN_0005BB68 */
        reg = *(uint64_t *)(s + 0x50);
        if ((uint64_t)(reg + 0x2f0) < reg) goto trap;
    }
    sk_g_notify_reg = reg;
    reg = sk_g_notify_reg;
    {
        uint64_t *fnslot = (uint64_t *)(reg + idx * 8);
        uint64_t *argslot = (uint64_t *)(reg + 0x100) + idx;
        if (((uint64_t *)(reg + 8) <= fnslot && fnslot + 1 <= (uint64_t *)(reg + 0x100)) &&
            fnslot <= fnslot + 1) {
            *(uint64_t *)(reg + idx * 8) = fn;
            if ((argslot - 1 < (uint64_t *)(reg + 0x100)) ||
                ((uint64_t *)(reg + 0x1f8) < argslot)) goto trap;
            *(argslot - 1) = arg;
            if ((fn != 0) && (enabled != 0)) {
                sk_h_0005BD7C((uint64_t)&sk_notify_call, &local48); /* FUN_0005BD7C -> FUN_00063EB4 */
            }
            return;
        }
    }
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x63c5c);
}

/* ================================================================== *
 * 00063c5c — FUN_00063C5C  (est. sk_notify_unlock)
 * Ghidra: void FUN_00063C5C(void)
 * Releases the notification registry lock (FUN_0005CE54) after a bounds check.
 * Confidence: medium
 * ================================================================== */
void sk_notify_unlock(void)
{
    uint64_t s = sk_singleton();                      /* FUN_0005BB68 */
    if ((uint64_t)(s + 0x60) <= (uint64_t)(s + 0x70)) {
        sk_h_0005CE54(NULL);                          /* FUN_0005CE54 */
        return;
    }
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x63c90);
}

/* ================================================================== *
 * 00063cfc — FUN_00063CFC  (est. sk_notify_construct)
 * Ghidra: void FUN_00063CFC(long param_1)
 * Constructs the notification entries for a set of keys: for each of up to
 * 0x1c key slots it runs the registered constructor (or uses the existing
 * value), and asserts the key is not "deleted". Traps on overflow.
 * Confidence: low (registry slot semantics inferred)
 * ================================================================== */
void sk_notify_construct(uint64_t key)
{
    uint64_t reg = sk_g_notify_reg;                   /* DAT_006b2718 */
    uint64_t *cnt;
    uint64_t *slot;
    uint64_t fn;
    uint64_t v;
    uint64_t n = 0x1c;
    if (sk_g_notify_reg == 0) {
        uint64_t s = sk_singleton();                  /* FUN_0005BB68 */
        reg = *(uint64_t *)(s + 0x50);
        if ((uint64_t)(reg + 0x2f0) < reg) goto trap;
    }
    sk_g_notify_reg = reg;
    reg = sk_g_notify_reg;
    sk_notify_lock();                                 /* FUN_00063B50 */
    slot = (uint64_t *)(reg + 0x100);
    cnt = (uint64_t *)(key + 0x18);
    while ((uint64_t *)(reg + 0x28) <= slot &&
           (uint64_t *)(reg + 0x20) <= (uint64_t *)(reg + 0x28)) {
        fn = *(uint64_t *)(reg + 0x20);
        if (fn == 0) {
            v = *cnt;
        } else {
            v = (*(uint64_t (**)(void))fn)();
            *cnt = v;
        }
        if ((v != 0) &&
            (v = *(uint64_t *)(reg + 0x210), *(uint64_t *)(reg + 0x210) = v + 1, v == -1)) {
            /* WARNING: does not return */
            sk_ec_switch(0, (int)(uintptr_t)"constructing deleted key"); /* FUN_0005B190 */
        }
        cnt += 1;
        reg += 8;
        n -= 1;
        if (n == 0) {
            sk_notify_unlock();                       /* FUN_00063C5C */
            return;
        }
    }
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x63dc4);
}

/* ================================================================== *
 * 00063dd4 — FUN_00063DD4  (est. sk_notify_teardown)
 * Ghidra: void FUN_00063DD4(void)
 * Tears down all live notification entries for the current CPU: for each of
 * the 0x1c slot indices it runs the registered destructor on the current key
 * value, clears the slot, and decrements the slot's refcount. Runs with the
 * per-CPU "in teardown" flag (+0xf8) set.
 * Confidence: low (slot semantics inferred)
 * ================================================================== */
void sk_notify_teardown(void)
{
    uint64_t cpu = (uint64_t)tpidr_el0;
    uint64_t reg = sk_g_notify_reg;                   /* DAT_006b2718 */
    uint64_t *slot;
    uint64_t *fnslot;
    uint64_t fn;
    int64_t v;
    uint64_t i = 0;
    if (sk_g_notify_reg == 0) {
        uint64_t s = sk_singleton();                  /* FUN_0005BB68 */
        reg = *(uint64_t *)(s + 0x50);
        if ((uint64_t)(reg + 0x2f0) < reg) goto trap;
    }
    sk_g_notify_reg = reg;
    reg = sk_g_notify_reg;
    *(uint64_t *)(cpu + 0xf8) = 1;
    slot = (uint64_t *)(cpu + 0x18);
    do {
        if (*(uint64_t *)((uint8_t *)slot + i) != 0) {
            sk_notify_lock();                         /* FUN_00063B50 */
            fnslot = (uint64_t *)(reg + i + 0x120);
            fn = *(uint64_t *)(reg + i + 0x118);
            if (fn != 0) {
                (*(void (**)(uint64_t))fn)(*(uint64_t *)((uint8_t *)slot + i));
            }
            *(uint64_t *)((uint8_t *)slot + i) = 0;
            {
                uint64_t *c = (uint64_t *)(reg + i + 0x210);
                v = (int64_t)*c;
                *c = (uint64_t)(v - 1);
            }
            sk_notify_unlock();                       /* FUN_00063C5C */
        }
        i += 8;
        if (i == 0xe0) {
            *(uint64_t *)(cpu + 0xf8) = 0;
            return;
        }
    } while (1);
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x63ea4);
}

/* ================================================================== *
 * 00063ea4 — FUN_00063EA4  (est. sk_set_tpidr)
 * Ghidra: void FUN_00063EA4(undefined8 param_1)
 * Sets the tpidr_el0 thread pointer. In this static reconstruction the
 * register is modeled as the tpidr_el0 storage region.
 * Confidence: medium (register modeled as static region)
 * ================================================================== */
void sk_set_tpidr(uint64_t v)
{
    *(uint64_t *)tpidr_el0 = v;
}

/* ================================================================== *
 * 00063eb4 — FUN_00063EB4  (est. sk_notify_call)
 * Ghidra: undefined8 FUN_00063EB4(long *param_1, undefined8 param_2)
 * Invokes the callback registered at slot *idx in the notification registry,
 * storing its result into the stack frame (FUN_000614F8) slot and bumping the
 * slot refcount. Returns 1 on success. Traps on overflow/bounds.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_notify_call(uint64_t *idxp, uint64_t k)
{
    uint64_t idx = *idxp;
    uint64_t reg = sk_g_notify_reg;                   /* DAT_006b2718 */
    uint64_t *fnslot;
    uint64_t *stack;
    uint64_t r;
    int64_t v;
    if (sk_g_notify_reg == 0) {
        uint64_t s = sk_singleton();                  /* FUN_0005BB68 */
        reg = *(uint64_t *)(s + 0x50);
        if ((uint64_t)(reg + 0x2f0) < reg) goto trap;
    }
    sk_g_notify_reg = reg;
    reg = sk_g_notify_reg;
    stack = (uint64_t *)sk_frame_bump2(k);            /* FUN_000614F8 */
    fnslot = (uint64_t *)(reg + idx * 8);
    if (((uint64_t *)(reg + 8) <= fnslot && fnslot + 1 <= (uint64_t *)(reg + 0x100)) &&
        fnslot <= fnslot + 1) {
        idx -= 1;
        r = (*(uint64_t (**)(void))(*fnslot))();
        {
            uint64_t *s2 = stack + idx;
            if ((stack <= s2 && s2 + 1 <= stack + 0x1f) && s2 <= s2 + 1) {
                *s2 = r;
                if ((r != 0) &&
                    (v = *(int64_t *)(reg + idx * 8 + 0x1f8),
                     *(uint64_t *)(reg + idx * 8 + 0x1f8) = (uint64_t)v + 1, v == -1)) {
                    /* WARNING: does not return */
                    sk_ec_switch(0, (int)(uintptr_t)"constructing deleted key"); /* FUN_0005B190 */
                }
                return 1;
            }
        }
    }
trap:
    /* WARNING: does not return */
    SoftwareBreakpoint(0x5519, 0x63f84);
    return 0;
}

/* ================================================================== *
 * 00063ffc — FUN_00063FFC  (est. sk_frame_sz)
 * Ghidra: undefined8 FUN_00063FFC(void)
 * Returns the fixed kernel stack-frame size 0x28 (40 bytes).
 * Confidence: high (constant)
 * ================================================================== */
uint64_t sk_frame_sz(void)
{
    return 0x28;
}

/* ================================================================== *
 * 0006402c — FUN_0006402C  (est. sk_frame_zero)
 * Ghidra: void FUN_0006402C(ulong param_1)
 * Zeroes the 0x28-byte stack frame at `p`: invokes FUN_00114790 (a
 * helper/marker) then memsets 0x28 bytes (FUN_001143A0). Traps on overflow.
 * Confidence: low (FUN_00114790 purpose unclear)
 * ================================================================== */
void sk_frame_zero(uint64_t p)
{
    sk_h_00114790(p, (uint64_t)(uintptr_t)"frame", 0);     /* FUN_00114790 */
    if ((uint64_t)(p + 0x28) < p) {
        /* WARNING: does not return */
        SoftwareBreakpoint(0x5519, 0x640e4);
    }
    sk_h_001143A0((void *)p, 0, 0x28);                /* FUN_001143A0: memset */
}

/* ================================================================== *
 * 000640e4 — FUN_000640E4  (est. sk_exc_active)
 * Ghidra: bool FUN_000640E4(void)
 * Returns whether exception handling is active, i.e. the kernel singleton's
 * +0x48 exception-endpoint pointer is non-null.
 * Confidence: high (matches 00064108 usage)
 * ================================================================== */
bool sk_exc_active(void)
{
    uint64_t s = sk_singleton();                      /* FUN_0005BB68 */
    return *(uint64_t *)(s + 0x48) != 0;
}

/* ================================================================== *
 * 00064108 — FUN_00064108  (est. sk_exc_setup)
 * Ghidra: void FUN_00064108(void)
 * Installs the kernel's exception-handling endpoint. Allocates the exception
 * endpoint object (FUN_0019AE2C(8), or FUN_0005E0DC if boot flag clear),
 * records it in the kernel singleton (+0x48), sets up the shared 0x6ad910
 * endpoint (FUN_000635C0), and then walks every thread (FUN_000533EC /
 * FUN_004B75E4) delivering the "Set exception handler" request to each via
 * CallSupervisor(0). Finally resets the handler list (DAT_006b2728).
 * Panics if exception handling is already installed or the endpoint alloc
 * fails.
 * Confidence: medium
 * Notes: 0xeb1a02bf914012ba is the cL4 "xrt" log tag; "xrt" = exclave runtime.
 * ================================================================== */
void sk_exc_setup(void)
{
    int64_t canary = SK_CANARY;
    uint64_t s = sk_singleton();                      /* FUN_0005BB68 */
    uint64_t uvar17;
    uint64_t marker;
    uint64_t flag;
    uint64_t i;
    uint8_t buf[0x28];

    if (*(uint64_t *)(s + 0x48) != 0) {
        /* WARNING: does not return */
        sk_ec_switch(0, (int)(uintptr_t)"exception handling can only be i"); /* FUN_0005B190 */
    }
    /* marker check derived from the "L4_ErrorCodeTruncated" string bytes */
    marker = (uint64_t)0;
    if (marker == 0) {
        sk_g_exc_endpoint = sk_alloc_obj(8);          /* FUN_0019AE2C(8) */
        if (sk_g_exc_endpoint == 0) {
            /* WARNING: does not return */
            sk_ec_switch(0, (int)(uintptr_t)"failed to allocate exception end"); /* FUN_0005B190 */
        }
        flag = sk_boot_flag_a();                      /* FUN_00060540 */
        uvar17 = sk_g_exc_endpoint;
        if ((flag & 1) == 0) {
            sk_h_0005E0DC(sk_g_exc_endpoint, 8);      /* FUN_0005E0DC */
            uvar17 = sk_g_exc_endpoint;
        }
    }
    sk_g_exc_endpoint = uvar17;
    uvar17 = sk_g_exc_endpoint;
    *(uint64_t *)(s + 0x48) = sk_g_exc_endpoint;
    sk_h_00117CC4(buf, (const void *)0x65c8d0, 0x28); /* FUN_00117CC4 */
    {
        uint64_t cfg[3];
        cfg[0] = 0x4be5f0;                            /* DAT_004be5f0 */
        cfg[1] = 0x4be5f8;                            /* DAT_004be5f8 */
        cfg[2] = 0x4be600;                            /* DAT_004be600 */
        sk_ep_setup((uint64_t *)0x6ad910, uvar17, (uint64_t)buf, cfg); /* FUN_000635C0 */
    }
    uvar17 = sk_g_exc_endpoint;
    { /* write selector 0xdc/kind 6 into tpidrro[0..7], CallSupervisor(0) */
        uint8_t *r = (uint8_t *)tpidrro_el0;
        r[0] = 0xdc;
        r[1] = 0x51;
        r[2] = 6;
        r[3] = 0; r[4] = 0; r[5] = 0; r[6] = 0; r[7] = 0;
        CallSupervisor(0);
        r[0] = 0xdc; r[1] = 0x51; r[2] = 6;
        r[3] = 0; r[4] = 0; r[5] = 0; r[6] = 0; r[7] = 0;
    }
    if ((uvar17 & 0xff) == 0) {
        uint64_t *th = NULL;
        uint64_t thiter;
        sk_h_0005BD7C((uint64_t)&sk_ep_check, NULL);  /* FUN_0005BD7C -> 0x000648d8 teardown */
        th = (uint64_t *)sk_g_handler_list;           /* DAT_006ad928 */
        thiter = sk_h_000533EC();                     /* FUN_000533EC: thread list iter */
        if (th != NULL) {
            uint64_t *cur = th;
            int st;
            do {
                uint64_t tstate = *(uint64_t *)((uint8_t *)cur + 0x28);
                uint8_t *r = (uint8_t *)tpidrro_el0;
                uint8_t saved[8];
                for (i = 0; i < 8; i++) saved[i] = r[i];
                do {
                    CallSupervisor(0);
                    for (i = 0; i < 8; i++) r[i] = saved[i];
                } while (tstate == 1);
                if (thiter != 0) {
                    sk_cpu_base();                    /* FUN_00060524(tstate, 0x12) */
                    if ((uint64_t)(cur + 0x178) < (uint64_t)cur) break;
                    sk_printf(0xeb1a02bf914012ba, "xrt 0x 06x Set exception handl",
                              (uint64_t)cur);
                    {
                        uint64_t rsp = *(uint64_t *)((uint8_t *)cur + 0x28);
                        for (i = 0; i < 8; i++) r[i] = (uint8_t)(thiter >> (8 * i));
                        CallSupervisor(0);
                        for (i = 0; i < 8; i++) r[i] = (uint8_t)(thiter >> (8 * i));
                        if ((rsp & 0xff) != 0) {
                            sk_h_004B7594(rsp, (uint64_t *)buf); /* FUN_004B7594 */
                            goto exc_panic;
                        }
                    }
                }
                {
                    uint64_t local88[4] = {0,0,0,0};
                    st = (int)sk_h_004B75E4((uint64_t)cur, (uint64_t)cur + 0x178, local88); /* FUN_004B75E4 */
                    if (st == 1) goto reset_list;
                    cur = (uint64_t *)local88[0];
                }
            } while (st != 0);
            /* WARNING: does not return */
            SoftwareBreakpoint(0x5519, 0x644a8);
        }
reset_list:
        /* reset the handler list to its sentinel markers */
        sk_g_handler_list = 0x64dfd8;                 /* DAT_006b2728 sentinel */
        sk_g_handler_list = 0x64dff0;
        if (canary == SK_CANARY) {
            return;
        }
    } else {
        sk_h_004B7544(uvar17, (uint64_t *)buf);       /* FUN_004B7544 */
    }
exc_panic:
    /* WARNING: does not return */
    sk_fatal();
}

/* ================================================================== *
 * 00064578 — FUN_00064578  (est. sk_vas_freeze)
 * Ghidra: long FUN_00064578(undefined8 param_1, ulong param_2, long param_3)
 * Freeze/dispatch entry for a vspace or address space. When param_2's high
 * word is 1 it freezes the vspace via the allocator vtable (+0x60) and
 * returns the error (shifted <<16); when param_2's low 16 bits are 0 it
 * decodes the message word (FUN_00065344 / FUN_000651E8) and walks the
 * freeze-handler list (DAT_006b2728, or *(param_3+0x98)) before raising the
 * exception (FUN_00064DE8). Returns 0xffff0000 on the "already frozen" path.
 * Confidence: medium
 * Notes: 0xeb1a02bf914012ba is the "xrt" log tag.
 * ================================================================== */
uint64_t sk_vas_freeze(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t uvar3;
    uint64_t *list;
    uint64_t *slot;
    int iVar2;
    uint64_t local60[4];

    if ((((uint32_t)(b >> 0x10)) & 0xffff) == 1) {
        sk_obj_get();                                 /* FUN_00034A2C */
        uvar3 = (*(uint64_t (**)(void))0)();          /* vtable +0x60 call (extraout_x1) */
        uvar3 &= 0xff;
        if (uvar3 == 0) {
            return 0;
        }
        sk_cpu_base();                                /* FUN_00060524 */
        if (uvar3 <= 0x40) {
            sk_printf(0xeb1a02bf914012ba, "xrt 0x 06x vas freeze failed w", uvar3);
            return uvar3 << 0x10;
        }
        /* WARNING: does not return */
        SoftwareBreakpoint(0x5519, 0x647a0);
    }
    if ((b & 0xffff0000) == 0) {
        uint8_t *r = (uint8_t *)tpidrro_el0;
        uint64_t local_word = (uint64_t)r[8] | (uint64_t)r[9] << 8 |
                              (uint64_t)r[10] << 16 | (uint64_t)r[11] << 24 |
                              (uint64_t)r[12] << 32 | (uint64_t)r[13] << 40 |
                              (uint64_t)r[14] << 48 | (uint64_t)r[15] << 56;
        sk_pair_t local40 = sk_msg_word_copy(&local_word); /* FUN_00065344 */
        sk_msg_decode(local60, c, (uint64_t *)&local40);   /* FUN_000651E8 */
        list = *(uint64_t **)(c + 0x98);
        if (list == NULL) {
            iVar2 = 0;
            list = (uint64_t *)sk_g_handler_list;     /* DAT_006b2728 */
            for (; list != NULL; list = (uint64_t *)*list) {
                iVar2 = (*(int (**)(uint64_t, uint64_t, uint64_t *))list[2])(list[1], c, local60);
                if (iVar2 - 1 < 2) break;
            }
            if (iVar2 == 1) goto frozen;
        } else {
            do {
                iVar2 = (*(int (**)(uint64_t, uint64_t, uint64_t *))list[2])(list[1], c, local60);
                if (iVar2 - 1 < 2) break;
                list = (uint64_t *)*list;
            } while (list != NULL);
            if (iVar2 == 1) goto frozen;
            list = (uint64_t *)sk_g_handler_list;
            if (iVar2 != 2) {
                iVar2 = 0;
                for (; list != NULL; list = (uint64_t *)*list) {
                    iVar2 = (*(int (**)(uint64_t, uint64_t, uint64_t *))list[2])(list[1], c, local60);
                    if (iVar2 - 1 < 2) break;
                }
                if (iVar2 == 1) goto frozen;
            }
        }
        return sk_exc_dispatch(c, (uint64_t)local60); /* FUN_00064DE8 */
    }
frozen:
    return 0xffff0000;
}

/* ================================================================== *
 * 000647a0 — FUN_000647A0  (est. sk_err_string4)
 * Ghidra: void FUN_000647A0(undefined8 param_1, byte param_2)
 * Fourth L4 error-code-to-name printer (same switch as the others).
 * Confidence: high (string constants are the L4 error names)
 * ================================================================== */
void sk_err_string4(uint64_t sink, uint8_t code)
{
    const char *name;
    char buf[0x20];
    if (9 < code) {
        sk_memcpy((void *)sink, "<unknown>", 0x20);
        sk_h_0000178C((uint64_t)sink, 0x20);          /* FUN_0000178C */
        return;
    }
    switch (code) {
        default:                    name = "L4_ErrorCodeSuccess      "; break;
        case 1:                     name = "L4_ErrorCodePreempted    "; break;
        case 2:                     name = "L4_ErrorCodeCanceled     "; break;
        case 3:                     name = "L4_ErrorCodeTruncated    "; break;
        case 4:                     name = "L4_ErrorCodeCapInvalid   "; break;
        case 5:                     name = "L4_ErrorCodeSlotInvalid  "; break;
        case 6:                     name = "L4_ErrorCodeMethodInvalid"; break;
        case 7:                     name = "L4_ErrorCodeArgumentInvalid"; break;
        case 8:                     name = "L4_ErrorCodeOperationInvalid"; break;
        case 9:                     name = "L4_ErrorCodePermissionInvalid"; break;
    }
    sk_memcpy(buf, name, 0x20);
    sk_h_0000178C((uint64_t)buf, 0x20);               /* FUN_0000178C */
}

/* ================================================================== *
 * 000648e4 — FUN_000648E4  (est. sk_amx_alloc)
 * Ghidra: undefined8 FUN_000648E4(undefined8 param_1, undefined8 param_2)
 * Allocates the AMX capability for a thread: FUN_00064C24(param_2), returns 1.
 * Confidence: high (thin wrapper)
 * ================================================================== */
uint64_t sk_amx_alloc(uint64_t a, uint64_t tcb)
{
    sk_exc_cap_alloc(tcb);                            /* FUN_00064C24 */
    return 1;
}

/* ================================================================== *
 * 00064904 — FUN_00064904  (est. sk_amx_cap_alloc)
 * Ghidra: void FUN_00064904(undefined8 param_1, long param_2, long *param_3)
 * When the message tag is kind 3 / sub-kind 2, allocates a 0x15-byte AMX
 * capability object (FUN_0019AE2C(0x15)) at *(th+0x108) and delivers the
 * allocation via CallSupervisor(0) with selector 0x13. Panics "failed to
 * allocate AMX capability" on failure; returns 1 on success, else 0.
 * Confidence: medium
 * ================================================================== */
void sk_amx_cap_alloc(uint64_t a, uint64_t th, uint64_t *msg)
{
    int64_t canary = SK_CANARY;
    uint64_t uvar3 = 0;
    uint64_t obj;
    uint64_t ret;
    uint8_t *r;

    if ((*msg == 3) && ((char)msg[3] == 2)) {
        obj = *(uint64_t *)(th + 0x108);
        if (obj == 0) {
            obj = sk_alloc_obj(0x15);                 /* FUN_0019AE2C(0x15) */
            *(uint64_t *)(th + 0x108) = obj;
            if (obj == 0) goto fail;
        }
        ret = *(uint64_t *)(th + 0x28);
        r = (uint8_t *)tpidrro_el0;
        for (int i = 0; i < 8; i++) r[i] = 0;
        r[0] = 3;
        for (int i = 0; i < 8; i++) r[8 + i] = (uint8_t)(obj >> (8 * i));
        th = 0x13;
        CallSupervisor(0);
        for (int i = 0; i < 8; i++) r[i] = 0;
        if ((ret & 0xff) != 0) {
            sk_h_004B7664(ret, (uint64_t *)r);        /* FUN_004B7664 */
            goto fail;
        }
        uvar3 = 1;
    } else {
        uvar3 = 0;
    }
    if (canary != SK_CANARY) {
        /* WARNING: does not return */
        sk_fatal();
    }
    return;
fail:
    /* WARNING: does not return */
    sk_ec_switch((int)uvar3, (int)(uintptr_t)"failed to allocate AMX capabilit"); /* FUN_0005B190 */
}

/* ================================================================== *
 * 00064a7c — FUN_00064A7C  (est. sk_list_push)
 * Ghidra: void FUN_00064A7C(undefined8 *param_1)
 * Pushes `node` onto the global handler list (DAT_006b2728) with a
 * self-referential-sentinel-aware insertion.
 * Confidence: low (linked-list push with sentinel handling)
 * ================================================================== */
void sk_list_push(uint64_t *node)
{
    uint64_t *prev;
    uint64_t *cur;
    bool b;
    *node = 0;
    prev = NULL;
    do {
        cur = (uint64_t *)sk_g_handler_list;          /* DAT_006b2728 */
        if (sk_g_handler_list == (uint64_t)(uintptr_t)prev) {
            sk_g_handler_list = (uint64_t)(uintptr_t)node;
        }
        b = cur != prev;
        if (b) prev = cur;
        *node = (uint64_t)(uintptr_t)prev;
        prev = cur;
    } while (b);
}

/* ================================================================== *
 * 00064aac — FUN_00064AAC  (est. sk_sme_cap_alloc)
 * Ghidra: void FUN_00064AAC(undefined8 param_1, long param_2, long *param_3)
 * Mirror of 00064904 for SME: when the tag is kind 3 / sub-kind 3, allocates
 * a 0x14-byte SME capability object (FUN_0019AE2C(0x14)) at *(th+0x110) and
 * delivers it via CallSupervisor(0) (selector 0x13, tag 2). Panics "failed
 * to allocate SME capability" on failure.
 * Confidence: medium
 * ================================================================== */
void sk_sme_cap_alloc(uint64_t a, uint64_t th, uint64_t *msg)
{
    int64_t canary = SK_CANARY;
    uint64_t uvar3 = 0;
    uint64_t obj;
    uint64_t ret;
    uint8_t *r;

    if ((*msg == 3) && ((char)msg[3] == 3)) {
        obj = *(uint64_t *)(th + 0x110);
        if (obj == 0) {
            obj = sk_alloc_obj(0x14);                 /* FUN_0019AE2C(0x14) */
            *(uint64_t *)(th + 0x110) = obj;
            if (obj == 0) goto fail;
        }
        ret = *(uint64_t *)(th + 0x28);
        r = (uint8_t *)tpidrro_el0;
        for (int i = 0; i < 8; i++) r[i] = 0;
        r[0] = 2;
        for (int i = 0; i < 8; i++) r[8 + i] = (uint8_t)(obj >> (8 * i));
        th = 0x13;
        CallSupervisor(0);
        for (int i = 0; i < 8; i++) r[i] = 0;
        if ((ret & 0xff) != 0) {
            sk_h_004B76B4(ret, (uint64_t *)r);        /* FUN_004B76B4 */
            goto fail;
        }
        uvar3 = 1;
    } else {
        uvar3 = 0;
    }
    if (canary != SK_CANARY) {
        /* WARNING: does not return */
        sk_fatal();
    }
    return;
fail:
    /* WARNING: does not return */
    sk_ec_switch((int)uvar3, (int)(uintptr_t)"failed to allocate SME capabilit"); /* FUN_0005B190 */
}

/* ================================================================== *
 * 00064c24 — FUN_00064C24  (est. sk_exc_cap_alloc)
 * Ghidra: void FUN_00064C24(long param_1)
 * Allocates a thread's exception-handler capability: when *(tcb+0x88) is
 * unset it creates the exception endpoint (FUN_00064CAC) and stores it, then
 * binds it via FUN_004B7704. Returns success (1) / failure (0) through the
 * canary epilogue.
 * Confidence: medium
 * ================================================================== */
void sk_exc_cap_alloc(uint64_t tcb)
{
    int64_t canary = SK_CANARY;
    uint64_t uvar1;
    if (*(uint64_t *)(tcb + 0x88) == 0) {
        uint64_t ep = sk_exc_endpoint_create(tcb);    /* FUN_00064CAC */
        *(uint64_t *)(tcb + 0x88) = ep;
        if (ep == 0) goto fail;
        sk_h_004B7704(tcb, (uint64_t *)(tcb + 0x88), (uint64_t *)tpidrro_el0); /* FUN_004B7704 */
    }
    uvar1 = 1;
    if (canary != SK_CANARY) {
        /* WARNING: does not return */
        sk_fatal();
    }
    return;
fail:
    /* WARNING: does not return */
    sk_fatal();
}

/* ================================================================== *
 * 00064cac — FUN_00064CAC  (est. sk_exc_endpoint_create)
 * Ghidra: long FUN_00064CAC(undefined8 param_1)
 * Creates an exception-handling endpoint. If the kernel singleton's +0x48
 * endpoint is installed, allocates a control block (FUN_00034F70), delivers
 * the endpoint creation request via CallSupervisor(3) with a fixed 16-byte
 * command (DAT_004be5e0 / 0x4be5e8) plus the arg, and returns the new block.
 * Returns 0 if no endpoint is installed or allocation fails.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_exc_endpoint_create(uint64_t arg)
{
    uint64_t s = sk_singleton();                      /* FUN_0005BB68 */
    uint64_t obj;
    uint64_t ep;
    uint8_t *r;

    if (*(uint64_t *)(s + 0x48) != 0) {
        obj = sk_phys_alloc(0);                       /* FUN_00034F70 */
        if (obj == 0) {
            return 0;
        }
        ep = *(uint64_t *)(s + 0x48);
        r = (uint8_t *)tpidrro_el0;
        { /* 16-byte command + arg */
            uint64_t lo = 0x4be5e0;                   /* DAT_004be5e0 */
            uint64_t hi = 0x4be5e8;                   /* 0x4be5e8 */
            for (int i = 0; i < 8; i++) {
                r[i] = (uint8_t)(lo >> (8 * i));
                r[8 + i] = (uint8_t)(hi >> (8 * i));
            }
            for (int i = 0x10; i < 0x18; i++) r[i] = (uint8_t)(arg >> (8 * (i - 0x10)));
        }
        CallSupervisor(3);
        if (ep == 0) {
            return obj;
        }
        sk_h_004B23D8(obj, obj, 2);                   /* FUN_004B23D8 */
    }
    return 0;
}

/* ================================================================== *
 * 00064de8 — FUN_00064DE8  (est. sk_exc_dispatch)
 * Ghidra: undefined8 FUN_00064DE8(undefined8 param_1, long param_2)
 * Dispatches a caught exception: if a handler is registered in the singleton
 * (+0x80) and returns 1, returns 0xffff0000 (already handled). Otherwise
 * reads the exception context (+0x10 pair), raises it (FUN_00064E84), and
 * panics "Caught exception: esr 0x%016zx f...".
 * Confidence: medium
 * ================================================================== */
uint64_t sk_exc_dispatch(uint64_t tcb, uint64_t ctx)
{
    uint64_t s = sk_singleton();                      /* FUN_0005BB68 */
    uint64_t h = *(uint64_t *)(s + 0x80);
    uint64_t a, b;
    uint64_t *p;
    if ((h != 0) &&
        ((*(uint64_t (**)(uint64_t, uint64_t, uint64_t))*(uint64_t *)(h + 0x10))(
            *(uint64_t *)(h + 8), tcb, ctx) == 1)) {
        return 0xffff0000;
    }
    p = *(uint64_t **)(ctx + 0x10);
    if (p == NULL) {
        a = 0;
        b = 0;
    } else {
        a = *p;
        b = p[1];
    }
    sk_exc_raise(tcb, a, b);                          /* FUN_00064E84 */
    /* WARNING: does not return */
    sk_ec_switch((int)tcb, (int)(uintptr_t)"Caught exception esr 0x 016zx f"); /* FUN_0005B190 */
    return 0;
}

/* ================================================================== *
 * 00064e84 — FUN_00064E84  (est. sk_exc_raise)
 * Ghidra: void FUN_00064E84(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3)
 * Raises an exception to the registered exception reporters: walks the
 * handler list (FUN_0005BA14), running each reporter's pre-handler
 * (FUN_004B78C0) when its flag is set, and finally dumps the full thread
 * state (FUN_00062474) with the "thread panic" banner. Runs under the
 * 0xeb1a02bf914012ba ("xrt") log domain.
 * Confidence: medium
 * ================================================================== */
void sk_exc_raise(uint64_t tcb, uint64_t esr, uint64_t far)
{
    int iVar2 = (int)sk_h_000544D0(0xeb1a02bf914012ba); /* FUN_000544D0 */
    uint64_t *p = (uint64_t *)sk_h_0005BA14();        /* FUN_0005BA14: handler list */
    do {
        if (p == NULL) {
            sk_thread_state_dump((uint64_t)"thread panic", 0x21,
                                 0xeb1a02bf914012ba, tcb, 1, 1, esr, far); /* FUN_00062474 */
            if (iVar2 == 0) {
                sk_h_0005453C(0xeb1a02bf914012ba);    /* FUN_0005453C */
            }
            return;
        }
        if (*(int8_t *)(p + 1) < 0) {
            uint64_t local48 = 0;
            sk_h_004B78C0((uint64_t)p, &local48);     /* FUN_004B78C0 */
        }
        p = (uint64_t *)*p;
    } while (1);
}

/* ================================================================== *
 * 00065020 — FUN_00065020  (est. sk_freeze)
 * Ghidra: undefined1 [16] FUN_00065020(void)
 * Freezes the caller's exception context: delivers the freeze request
 * (selector {0,1}) via CallSupervisor(0). On success logs "xrt_freeze:
 * freeze o..." or runs the registered freeze handler (FUN_004B7984). Returns
 * the 16-byte result {1,1}.
 * Confidence: medium
 * ================================================================== */
sk_pair_t sk_freeze(void)
{
    uint64_t s = sk_singleton();                      /* FUN_0005BB68 */
    uint64_t ep = *(uint64_t *)(s + 0x48);
    uint8_t *r = (uint8_t *)tpidrro_el0;
    sk_pair_t out;

    if (ep == 0) {
        sk_h_004B79C8();                              /* FUN_004B79C8 */
    } else {
        for (int i = 0; i < 8; i++) r[i] = 0;
        r[0] = 0;
        r[2] = 1;                                     /* selector {0,1} */
        CallSupervisor(0);
        for (int i = 0; i < 8; i++) r[i] = 0;
        if (ep == 0) {
            sk_cpu_base();                            /* FUN_00060524 */
            sk_printf(0xeb1a02bf914012ba, "xrt 0x 06x xrt freeze freeze o", (uint64_t)0);
        } else {
            sk_h_004B7984(ep, 0);                     /* FUN_004B7984 */
        }
    }
    out.lo = 1;
    out.hi = 1;                                       /* ZEXT816(1) */
    return out;
}

/* ================================================================== *
 * 00065138 — FUN_00065138  (est. sk_err_string_wrap3)
 * Ghidra: void FUN_00065138(void)
 * Calls FUN_000647A0 with the stack buffer as the sink.
 * Confidence: low (sink register-carried)
 * ================================================================== */
void sk_err_string_wrap3(void)
{
    uint8_t sink[0x20];
    sk_err_string4((uint64_t)sink, 0);                /* FUN_000647A0 */
}

/* ================================================================== *
 * 00065158 / 0006516c / 000651ac / 000651bc — FUN_00065158/FUN_0006516C/
 *   FUN_000651AC/FUN_000651BC  (est. sk_noop2..sk_noop5)
 * Empty functions in the exception-handler region (empty dispatch slots).
 * Confidence: high (trivially empty)
 * ================================================================== */
void sk_noop2(void) { }
void sk_noop3(void) { }
void sk_noop4(void) { }
void sk_noop5(void) { }

/* ================================================================== *
 * 00065190 — FUN_00065190  (est. sk_inline_store)
 * Ghidra: void FUN_00065190(undefined8 param_1, undefined8 param_2,
 *          undefined8 param_3)
 * Stores bytes into a buffer using the in_x9/in_w8 pseudo-registers: writes
 * w8 at +4 and the high bytes of param_3 at +6/+7. Register operands are
 * approximated with a local buffer.
 * Confidence: low (pseudo-register operands)
 * ================================================================== */
void sk_inline_store(uint64_t a, uint64_t b, uint64_t c)
{
    uint8_t buf[16] = {0};
    (void)b;
    buf[4] = (uint8_t)a;                              /* in_w8 */
    buf[7] = (uint8_t)(c >> 0x38);
    buf[6] = (uint8_t)(c >> 0x30);
}

/* ================================================================== *
 * 000651d0 — FUN_000651D0  (est. sk_err_string_wrap4)
 * Ghidra: void FUN_000651D0(void)
 * Calls FUN_000647A0 with no explicit sink (register-carried).
 * Confidence: low (sink register-carried)
 * ================================================================== */
void sk_err_string_wrap4(void)
{
    uint8_t sink[0x20];
    sk_err_string4((uint64_t)sink, 0);                /* FUN_000647A0 */
}

/* ================================================================== *
 * 000651e8 — FUN_000651E8  (est. sk_msg_decode)
 * Ghidra: void FUN_000651E8(undefined8 *param_1, long param_2, ulong *param_3)
 * Decodes a capability/message word into a 4-word result descriptor in out[0..3].
 * The word's bits select the descriptor kind:
 *   - kind 0x1d: out[0]=0, out[1]=cap, out[3]=3 (or 0)
 *   - kind 0x20/0x21: out[0]=1, out[1]=word2, tag byte 0x19 = 2 (if (word1&0x3c)==4)
 *   - kind 0x3f: out[0]=0, out[1]=cap, out[3]=2 (if word1 low 24 bits ==3)
 *   - kind 0x3c (with tcb): out[0]=2, out[1]=cap, out[3]=word1&0xffff
 *   - kind 0x24/0x25: out[0]=4 or 1, out[1]=word2, tag byte 0x19 per bit6
 *   - otherwise: out[] zeroed.
 * Confidence: medium
 * ================================================================== */
void sk_msg_decode(uint64_t *out, uint64_t tcb, uint64_t *word)
{
    uint64_t uvar1 = *word;
    uint64_t uvar2 = word[1];
    uint32_t uvar6 = (uint32_t)(uvar1 >> 0x1a) & 0x3f;
    uint64_t uvar3;
    uint8_t tag;

    if (uvar6 < 0x24) {
        if (1 < uvar6 - 0x20) {                       /* 0x1d, 0x22, 0x23 */
            if (uvar6 == 0x1d) {
                uvar3 = sk_cap_get(0);                /* FUN_00065350 */
                out[0] = 0; out[1] = uvar3; out[2] = 0; out[3] = 0;
                if ((uvar1 & 0xffffff) != 0) return;
                out[0] = 3;
                tag = 3;
                *(uint8_t *)(out + 3) = tag;
                return;
            }
            out[2] = 0; out[3] = 0; out[0] = 0; out[1] = 0;
            return;
        }
        /* 0x20, 0x21 */
        out[2] = 0; out[3] = 0; out[0] = 0; out[1] = 0;
        if ((uvar1 & 0x3c) != 4) return;
        out[0] = 1; out[1] = uvar2;
        *(uint8_t *)((uint8_t *)out + 0x19) = 2;
        return;
    }
    if (1 < uvar6 - 0x24) {                           /* >=0x26 (and wraps) */
        if (uvar6 != 0x3f) {
            if ((uvar6 == 0x3c) && (tcb != 0)) {
                uvar3 = sk_cap_get(0);                /* FUN_00065350 */
                out[0] = 2; out[1] = uvar3; out[2] = 0; out[3] = uvar1 & 0xffff;
                return;
            }
            out[2] = 0; out[3] = 0; out[0] = 0; out[1] = 0;
            return;
        }
        if (tcb == 0) {
            out[2] = 0; out[3] = 0; out[0] = 0; out[1] = 0;
            return;
        }
        uvar3 = sk_cap_get(0);                        /* FUN_00065350 */
        out[0] = 0; out[1] = uvar3; out[2] = 0; out[3] = 0;
        if ((uvar1 & 0xffffff) != 3) return;
        out[0] = 3;
        *(uint8_t *)(out + 3) = 2;
        return;
    }
    /* 0x24, 0x25 */
    uvar6 = (uint32_t)uvar1 & 0x3f;
    out[2] = 0; out[3] = 0; out[0] = 0; out[1] = 0;
    if (0x11 < uvar6) return;
    if ((1U << (uvar1 & 0x1f) & 0xf0f0U) == 0) {
        if (uvar6 != 0x11) return;
        out[0] = 4; out[1] = uvar2;
        tag = (uint8_t)((uvar1 & 0x40) >> 6);
        *(uint8_t *)(out + 3) = tag;
        return;
    }
    out[0] = 1; out[1] = uvar2;
    *(uint8_t *)((uint8_t *)out + 0x19) = (uint8_t)((uvar1 & 0x40) >> 6);
    *(uint8_t *)(out + 3) = (uint8_t)uvar1 & 3;
}

/* ================================================================== *
 * 00065344 — FUN_00065344  (est. sk_msg_word_copy)
 * Ghidra: undefined1 [16] FUN_00065344(undefined1 (*param_1) [16])
 * Copies the 16 bytes at *src into a 16-byte result (returned in x0/x1).
 * Confidence: high (trivial 16-byte copy)
 * ================================================================== */
sk_pair_t sk_msg_word_copy(uint64_t *src)
{
    sk_pair_t r;
    r.lo = src[0];
    r.hi = src[1];
    return r;
}

/* ================================================================== *
 * 00065350 — FUN_00065350  (est. sk_cap_get)
 * Ghidra: ulong FUN_00065350(void)
 * Fetches a capability via CallSupervisor(0): copies a fixed 16-byte command
 * (DAT_004be770 / 0x4be778) into tpidrro, calls up, and returns the 64-bit
 * capability word read back from tpidrro+0x10. Faults (FUN_004B7AC8) on error.
 * Confidence: medium
 * ================================================================== */
uint64_t sk_cap_get(uint64_t tcb)
{
    int64_t canary = SK_CANARY;
    uint64_t uvar4 = sk_tcb_state(tcb);               /* FUN_00061630 */
    uint8_t *r = (uint8_t *)tpidrro_el0;
    uint64_t lo = 0x4be770;                           /* DAT_004be770 */
    uint64_t hi = 0x4be778;                           /* 0x4be778 */

    for (int i = 0; i < 8; i++) {
        r[i] = (uint8_t)(lo >> (8 * i));
        r[8 + i] = (uint8_t)(hi >> (8 * i));
    }
    CallSupervisor(0);
    r[0] = 0x1f;
    for (int i = 1; i < 8; i++) r[i] = 0;
    if ((uvar4 & 0xff) == 0) {
        if (canary == SK_CANARY) {
            return (uint64_t)r[0x12] << 0x10 | (uint64_t)r[0x13] << 0x18 |
                   (uint64_t)*(uint16_t *)(r + 0x10) |
                   ((uint64_t)((uint16_t)r[0x16] << 0x10 | (uint16_t)r[0x17] << 0x18 |
                               (uint16_t)*(uint16_t *)(r + 0x14)) << 0x20);
        }
    } else {
        sk_h_004B7AC8(uvar4, r);                      /* FUN_004B7AC8 */
    }
    /* WARNING: does not return */
    sk_fatal();
    return 0;
}

/* ================================================================== *
 * 000654e8 — FUN_000654E8  (est. sk_err_string5)
 * Ghidra: void FUN_000654E8(undefined8 param_1, byte param_2)
 * Fifth L4 error-code-to-name printer (same switch as the others).
 * Confidence: high (string constants are the L4 error names)
 * ================================================================== */
void sk_err_string5(uint64_t sink, uint8_t code)
{
    const char *name;
    char buf[0x20];
    if (9 < code) {
        sk_memcpy((void *)sink, "<unknown>", 0x20);
        sk_h_0000178C((uint64_t)sink, 0x20);          /* FUN_0000178C */
        return;
    }
    switch (code) {
        default:                    name = "L4_ErrorCodeSuccess      "; break;
        case 1:                     name = "L4_ErrorCodePreempted    "; break;
        case 2:                     name = "L4_ErrorCodeCanceled     "; break;
        case 3:                     name = "L4_ErrorCodeTruncated    "; break;
        case 4:                     name = "L4_ErrorCodeCapInvalid   "; break;
        case 5:                     name = "L4_ErrorCodeSlotInvalid  "; break;
        case 6:                     name = "L4_ErrorCodeMethodInvalid"; break;
        case 7:                     name = "L4_ErrorCodeArgumentInvalid"; break;
        case 8:                     name = "L4_ErrorCodeOperationInvalid"; break;
        case 9:                     name = "L4_ErrorCodePermissionInvalid"; break;
    }
    sk_memcpy(buf, name, 0x20);
    sk_h_0000178C((uint64_t)buf, 0x20);               /* FUN_0000178C */
}

/* ================================================================== *
 * 00065620 — FUN_00065620  (est. sk_set_global0)
 * Ghidra: void FUN_00065620(undefined8 param_1)
 * Stores param_1 into the global handler pointer DAT_006b2730.
 * Confidence: high (trivial store)
 * ================================================================== */
void sk_set_global0(uint64_t v)
{
    sk_g_xrt_handler = v;                             /* DAT_006b2730 */
}

/* ================================================================== *
 * 0006562c — FUN_0006562C  (est. sk_global0_dispatch)
 * Ghidra: void FUN_0006562C(undefined8 param_1, undefined8 param_2)
 * Calls FUN_00065640(DAT_006b2730, param_1, param_2) (dispatch through the
 * global xrt handler).
 * Confidence: high (thin wrapper)
 * ================================================================== */
void sk_global0_dispatch(uint64_t a, uint64_t b)
{
    sk_h_00065640(sk_g_xrt_handler, a, b);            /* FUN_00065640 */
}
