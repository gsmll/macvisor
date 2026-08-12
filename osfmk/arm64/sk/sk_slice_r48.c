/* Recreated from cl4_kernel.raw (cL4 microkernel, arm64e, image base 0) — the
 * Secure Kernel (GL1), an seL4-derived microkernel. Ground truth: Ghidra
 * FUN_ names + addresses. This slice (0x6580ec-0x65d7b0) covers the
 * notification/signal subsystem: syscall entry stubs, object-type
 * method-table builders, and the notification-object list manager keyed off
 * the global @ 0x6fe638. All names are estimates unless string/header-matched.
 * English-first; Ghidra identifiers appear in comments only. */

#include <stdint.h>
#include <stdbool.h>

/* ---- Shared helpers used by this slice (defined elsewhere in the SK tree) ---- */
extern unsigned long sk_00661318(void);                 /* FUN_00661318: current-object/tcb getter */
extern long FUN_00661348(void *);                       /* FUN_00661348: spin/sched state enter */
extern void FUN_006613d0(void *);                       /* FUN_006613d0: state leave */
extern void FUN_00661428(void);                         /* FUN_00661428: full memory barrier / sched tick */
extern unsigned long FUN_00661e1c(void *, int, void *, unsigned int, int); /* FUN_00661e1c: msg send prep */
extern unsigned long FUN_00662098(void *);              /* FUN_00662098 */
extern unsigned long FUN_006621f4(void *);              /* FUN_006621f4 */
extern unsigned long FUN_00662264(void *);              /* FUN_00662264 */
extern void FUN_00662368(void *, void *, void *);       /* FUN_00662368: slot lookup */
extern unsigned long FUN_006623a4(void *);              /* FUN_006623a4 */
extern void FUN_00662630(void *, void *);               /* FUN_00662630: state save */
extern unsigned long FUN_006626f0(void *);              /* FUN_006626f0 */
extern void FUN_0066272c(void *, void *);               /* FUN_0066272c: slot lookup 2 */
extern void FUN_006631d8(unsigned long, int, void *, unsigned long, int, int, int, int, unsigned long, unsigned long); /* FUN_006631d8: panic helper */
extern unsigned long FUN_0066455c(void);                /* FUN_0066455c */
extern unsigned long FUN_006645bc(unsigned long);       /* FUN_006645bc */
extern long FUN_006661e0(unsigned long, void *);        /* FUN_006661e0: string/config lookup */
extern unsigned long FUN_0066ad54(void);                /* FUN_0066ad54: alloc */
extern void FUN_006860f4(void *);                       /* FUN_006860f4: free */
extern void FUN_00684820(void);                         /* FUN_00684820: lock panic */
extern void FUN_0067f660(void);                         /* FUN_0067f660: stack canary check / unwind */
extern void FUN_0067b280(unsigned long);                /* FUN_0067b280: noreturn panic(msg) */
extern void FUN_0067d1f0(void *, unsigned long);        /* FUN_0067d1f0: log msg */
extern void FUN_0067d440(unsigned long, void *);        /* FUN_0067d440: log */
extern void FUN_0067d6c0(unsigned long, int, int, void *); /* FUN_0067d6c0: log with args */
extern void FUN_0067d72c(unsigned long);                /* FUN_0067d72c: log string */
extern void FUN_0067d83c(void *, void *, void *);       /* FUN_0067d83c: log with ptrs */
extern unsigned long FUN_0067a780(void *, unsigned long); /* FUN_0067a780: memcpy */
extern unsigned long FUN_0067aa00(void *, void *, unsigned long); /* FUN_0067aa00: memcpy 2 */
extern long FUN_0067a900(unsigned long, int, unsigned long); /* FUN_0067a900: strnchr-like scan */
extern long FUN_0067aff0(long, unsigned long, unsigned long); /* FUN_0067aff0: strcmp */
extern void FUN_0067ca6c(void *, int, void *, void *);  /* FUN_0067ca6c: buffer format */
extern void FUN_0067ca84(void *, void *, int, void *, void *, void *); /* FUN_0067ca84: buffer format n */
extern unsigned long FUN_0067cd24(void *, void *, unsigned long, unsigned long); /* FUN_0067cd24: memmove/copy */
extern unsigned long FUN_00654cc8(void);                /* FUN_00654cc8 */
extern unsigned long FUN_00654d20(void);                /* FUN_00654d20 */
extern void FUN_006550cc(unsigned long, unsigned long, int, void *); /* FUN_006550cc: log */
extern void FUN_00656884(void *, int, unsigned long);   /* FUN_00656884: log object */
extern unsigned long FUN_00655848(void);                /* FUN_00655848: per-cpu base getter */
extern unsigned long FUN_00656c68(void);                /* FUN_00656c68 */
extern void FUN_00655e1c(void *, void *);               /* FUN_00655e1c: ref */
extern void FUN_0065f468(void *, unsigned long, int, int); /* FUN_0065f468: log + refs */
extern void FUN_0065e454(void *, void *);               /* FUN_0065e454: list init */
extern long FUN_0065e138(void *, void *);               /* FUN_0065e138: obj lookup */
extern void FUN_0065db84(void *);                       /* FUN_0065db84: lock acquire (slot) */
extern void FUN_0065de3c(void *);                       /* FUN_0065de3c: lock release (slot) */
extern unsigned long FUN_0065d804(int, unsigned long);  /* FUN_0065d804: register-dump helper */
extern void FUN_006833b0(void *);                       /* FUN_006833b0: vspace lookup */
extern unsigned long FUN_006833bc(void *);              /* FUN_006833bc: vspace attr */
extern unsigned long FUN_00683f74(void *, void *, void *); /* FUN_00683f74: notify-send */
extern void FUN_00684150(void *, void *);               /* FUN_00684150: notify-cancel */
extern void FUN_00684388(void *);                       /* FUN_00684388: notify-cleanup */
extern void *FUN_0064e07c(void);                        /* FUN_0064e07c: get object ops table */

/* ---- Global data touched by this slice (addresses per Ghidra) ---- */
extern void *_DAT_006b4368;                 /* 0x6b4368 log/state context ptr */
extern void *_DAT_006b4380;                 /* 0x6b4380 log context 2 */
extern unsigned long _DAT_006b51f8;         /* 0x6b51f8 */
extern unsigned long _DAT_006b5220;         /* 0x6b5220 */
extern unsigned long _DAT_006b5240;         /* 0x6b5240 */
extern long _DAT_006b5ed0;                  /* 0x6b5ed0 stack canary */
extern unsigned long _DAT_006fc590;         /* 0x6fc590 */
extern unsigned long _DAT_006fc598;         /* 0x6fc598 */
extern unsigned long _DAT_006fe5f0;         /* 0x6fe5f0 */
extern unsigned long _DAT_006fe630;         /* 0x6fe630 fn ptr (notify callback) */
extern long _DAT_006fe638;                  /* 0x6fe638 notification list head */
extern int DAT_006887b0;                    /* 0x6887b0 */
extern int DAT_006887b8;                    /* 0x6887b8 */
extern unsigned long DAT_006a66a9;          /* 0x6a66a9 */
extern unsigned long DAT_006a66ab;          /* 0x6a66ab */
extern unsigned long DAT_006a66ac;          /* 0x6a66ac */
extern unsigned long DAT_006a66ad;          /* 0x6a66ad */
extern unsigned long DAT_006a66af;          /* 0x6a66af */
extern unsigned long DAT_006a66b0;          /* 0x6a66b0 */
extern unsigned long DAT_006a66b1;          /* 0x6a66b1 */
extern unsigned long DAT_006a66b3;          /* 0x6a66b3 */
extern unsigned long DAT_006a66b4;          /* 0x6a66b4 */
extern unsigned long DAT_006a66b5;          /* 0x6a66b5 */
extern unsigned long DAT_006a66b7;          /* 0x6a66b7 */
extern unsigned long DAT_006a66b8;          /* 0x6a66b8 */

/* GENTER-opaque supervisor trap used by the syscall stubs below.
 * cL4 enters the kernel by staging IPC words in the per-thread message area
 * (TPIDRRO_EL0) and trapping with a supervisor call (SVC 0). */
#define CallSupervisor(n)  /* supervisor trap SVC(n) — kernel entry */
#define LORelease()        /* release the last-load spin */
#define SoftwareBreakpoint(a, b)  /* brk #imm */
#define GENTER()           /* GENTER opcode 0x00201420 */
#define GEXIT()            /* GEXIT opcode 0x00201400 */

/* TPIDRRO_EL0 holds a pointer to the per-thread IPC message area that the
 * syscall stubs below stage words into before trapping. */
static inline void *sk_thread_msg_area(void)
{
    void *v;
    asm volatile("mrs %0, tpidrro_el0" : "=r"(v));
    return v;
}

/* TPIDR_EL0 = per-thread base (used to reach per-CPU/id list anchors). */
static inline void *sk_thread_base(void)
{
    void *v;
    asm volatile("mrs %0, tpidr_el0" : "=r"(v));
    return v;
}

static long sk_notif_id_lookup(int major, int minor);

/* Forward: notification list ensure helper (defined in this file) */
static void sk_notif_list_ensure(long *slot, uint64_t major, uint64_t minor);

/* ===================================================================== */
/* Syscall entry stubs — pattern A: 3 IPC words staged then SVC trap     */
/* ===================================================================== */

/* FUN_00658628 @ 0x00658628   (est. sk_syscall3_00658628)
 * Ghidra: void FUN_00658628(undefined8,undefined8,undefined8,undefined8)
 * Stages 3 IPC words (param_2..param_4) in the per-thread message area
 * (TPIDRRO_EL0), traps into the kernel, then restores the first word.
 * Confidence: medium (structural syscall stub, no string match) */
static void sk_syscall3_00658628(uint64_t unused, uint64_t w0, uint64_t w1, uint64_t w2)
{
    uint64_t *msg = (uint64_t *)sk_thread_msg_area();
    msg[0] = w0;
    msg[1] = w1;
    msg[2] = w2;
    CallSupervisor(0);
    msg[0] = w0;
}

/* FUN_00658dac @ 0x00658dac   (est. sk_syscall3_00658dac)
 * Ghidra: void FUN_00658dac(undefined8,undefined8,undefined8,undefined8)
 * Same 3-word staged SVC trap pattern; used by a different endpoint table.
 * Confidence: medium */
static void sk_syscall3_00658dac(uint64_t unused, uint64_t w0, uint64_t w1, uint64_t w2)
{
    uint64_t *msg = (uint64_t *)sk_thread_msg_area();
    msg[0] = w0;
    msg[1] = w1;
    msg[2] = w2;
    CallSupervisor(0);
    msg[0] = w0;
}

/* FUN_0065952c @ 0x0065952c   (est. sk_syscall3_0065952c)
 * Ghidra: void FUN_0065952c(undefined8,undefined8,undefined8,undefined8)
 * 3-word staged SVC trap (endpoint table variant 0x400000001).
 * Confidence: medium */
static void sk_syscall3_0065952c(uint64_t unused, uint64_t w0, uint64_t w1, uint64_t w2)
{
    uint64_t *msg = (uint64_t *)sk_thread_msg_area();
    msg[0] = w0;
    msg[1] = w1;
    msg[2] = w2;
    CallSupervisor(0);
    msg[0] = w0;
}

/* FUN_00659cac @ 0x00659cac   (est. sk_syscall3_00659cac)
 * Ghidra: void FUN_00659cac(undefined8,undefined8,undefined8,undefined8)
 * 3-word staged SVC trap (endpoint table variant 0x500000001).
 * Confidence: medium */
static void sk_syscall3_00659cac(uint64_t unused, uint64_t w0, uint64_t w1, uint64_t w2)
{
    uint64_t *msg = (uint64_t *)sk_thread_msg_area();
    msg[0] = w0;
    msg[1] = w1;
    msg[2] = w2;
    CallSupervisor(0);
    msg[0] = w0;
}

/* FUN_0065a42c @ 0x0065a42c   (est. sk_syscall3_0065a42c)
 * Ghidra: void FUN_0065a42c(undefined8,undefined8,undefined8,undefined8)
 * 3-word staged SVC trap (endpoint table variant 0x700000001).
 * Confidence: medium */
static void sk_syscall3_0065a42c(uint64_t unused, uint64_t w0, uint64_t w1, uint64_t w2)
{
    uint64_t *msg = (uint64_t *)sk_thread_msg_area();
    msg[0] = w0;
    msg[1] = w1;
    msg[2] = w2;
    CallSupervisor(0);
    msg[0] = w0;
}

/* FUN_0065abac @ 0x0065abac   (est. sk_syscall3_0065abac)
 * Ghidra: void FUN_0065abac(undefined8,undefined8,undefined8,undefined8)
 * 3-word staged SVC trap (endpoint table variant 0x700000001 sibling).
 * Confidence: medium */
static void sk_syscall3_0065abac(uint64_t unused, uint64_t w0, uint64_t w1, uint64_t w2)
{
    uint64_t *msg = (uint64_t *)sk_thread_msg_area();
    msg[0] = w0;
    msg[1] = w1;
    msg[2] = w2;
    CallSupervisor(0);
    msg[0] = w0;
}

/* FUN_0065baa8 @ 0x0065baa8   (est. sk_syscall3_0065baa8)
 * Ghidra: void FUN_0065baa8(undefined8,undefined8,undefined8,undefined8)
 * 3-word staged SVC trap (endpoint table variant 0x900000001).
 * Confidence: medium */
static void sk_syscall3_0065baa8(uint64_t unused, uint64_t w0, uint64_t w1, uint64_t w2)
{
    uint64_t *msg = (uint64_t *)sk_thread_msg_area();
    msg[0] = w0;
    msg[1] = w1;
    msg[2] = w2;
    CallSupervisor(0);
    msg[0] = w0;
}

/* ===================================================================== */
/* Syscall entry stubs — pattern B: 1-arg retry-while-flag SVC trap      */
/* ===================================================================== */

#define SK_NOTIF_STUB_B(name_, addr_) \
static void name_(uint64_t flag) \
{ \
    uint64_t *msg = (uint64_t *)sk_thread_msg_area(); \
    uint64_t saved = msg[0]; \
    do { \
        CallSupervisor(0); \
        msg[0] = saved; \
    } while (flag == 1); \
}

/* FUN_0065874c @ 0x0065874c — est. sk_notif_syscall1 (table 0x200000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065874c, 0x0065874c)
/* FUN_0065877c @ 0x0065877c — est. sk_notif_syscall1 (table 0x200000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065877c, 0x0065877c)
/* FUN_006587ac @ 0x006587ac — est. sk_notif_syscall1 (table 0x200000001) */
SK_NOTIF_STUB_B(sk_syscall1_006587ac, 0x006587ac)
/* FUN_006587dc @ 0x006587dc — est. sk_notif_syscall1 (table 0x200000001) */
SK_NOTIF_STUB_B(sk_syscall1_006587dc, 0x006587dc)
/* FUN_0065880c @ 0x0065880c — est. sk_notif_syscall1 (table 0x200000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065880c, 0x0065880c)
/* FUN_00658ed0 @ 0x00658ed0 — est. sk_notif_syscall1 (table 0x300000001) */
SK_NOTIF_STUB_B(sk_syscall1_00658ed0, 0x00658ed0)
/* FUN_00658f00 @ 0x00658f00 — est. sk_notif_syscall1 (table 0x300000001) */
SK_NOTIF_STUB_B(sk_syscall1_00658f00, 0x00658f00)
/* FUN_00658f30 @ 0x00658f30 — est. sk_notif_syscall1 (table 0x300000001) */
SK_NOTIF_STUB_B(sk_syscall1_00658f30, 0x00658f30)
/* FUN_00658f60 @ 0x00658f60 — est. sk_notif_syscall1 (table 0x300000001) */
SK_NOTIF_STUB_B(sk_syscall1_00658f60, 0x00658f60)
/* FUN_00658f90 @ 0x00658f90 — est. sk_notif_syscall1 (table 0x300000001) */
SK_NOTIF_STUB_B(sk_syscall1_00658f90, 0x00658f90)
/* FUN_00659650 @ 0x00659650 — est. sk_notif_syscall1 (table 0x400000001) */
SK_NOTIF_STUB_B(sk_syscall1_00659650, 0x00659650)
/* FUN_00659680 @ 0x00659680 — est. sk_notif_syscall1 (table 0x400000001) */
SK_NOTIF_STUB_B(sk_syscall1_00659680, 0x00659680)
/* FUN_006596b0 @ 0x006596b0 — est. sk_notif_syscall1 (table 0x400000001) */
SK_NOTIF_STUB_B(sk_syscall1_006596b0, 0x006596b0)
/* FUN_006596e0 @ 0x006596e0 — est. sk_notif_syscall1 (table 0x400000001) */
SK_NOTIF_STUB_B(sk_syscall1_006596e0, 0x006596e0)
/* FUN_00659710 @ 0x00659710 — est. sk_notif_syscall1 (table 0x400000001) */
SK_NOTIF_STUB_B(sk_syscall1_00659710, 0x00659710)
/* FUN_00659dd0 @ 0x00659dd0 — est. sk_notif_syscall1 (table 0x500000001) */
SK_NOTIF_STUB_B(sk_syscall1_00659dd0, 0x00659dd0)
/* FUN_00659e00 @ 0x00659e00 — est. sk_notif_syscall1 (table 0x500000001) */
SK_NOTIF_STUB_B(sk_syscall1_00659e00, 0x00659e00)
/* FUN_00659e30 @ 0x00659e30 — est. sk_notif_syscall1 (table 0x500000001) */
SK_NOTIF_STUB_B(sk_syscall1_00659e30, 0x00659e30)
/* FUN_00659e60 @ 0x00659e60 — est. sk_notif_syscall1 (table 0x500000001) */
SK_NOTIF_STUB_B(sk_syscall1_00659e60, 0x00659e60)
/* FUN_00659e90 @ 0x00659e90 — est. sk_notif_syscall1 (table 0x500000001) */
SK_NOTIF_STUB_B(sk_syscall1_00659e90, 0x00659e90)
/* FUN_0065a550 @ 0x0065a550 — est. sk_notif_syscall1 (table 0x700000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065a550, 0x0065a550)
/* FUN_0065a580 @ 0x0065a580 — est. sk_notif_syscall1 (table 0x700000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065a580, 0x0065a580)
/* FUN_0065a5b0 @ 0x0065a5b0 — est. sk_notif_syscall1 (table 0x700000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065a5b0, 0x0065a5b0)
/* FUN_0065a5e0 @ 0x0065a5e0 — est. sk_notif_syscall1 (table 0x700000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065a5e0, 0x0065a5e0)
/* FUN_0065a610 @ 0x0065a610 — est. sk_notif_syscall1 (table 0x700000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065a610, 0x0065a610)
/* FUN_0065acd0 @ 0x0065acd0 — est. sk_notif_syscall1 (table 0x800000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065acd0, 0x0065acd0)
/* FUN_0065ad00 @ 0x0065ad00 — est. sk_notif_syscall1 (table 0x800000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065ad00, 0x0065ad00)
/* FUN_0065ad30 @ 0x0065ad30 — est. sk_notif_syscall1 (table 0x800000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065ad30, 0x0065ad30)
/* FUN_0065ad60 @ 0x0065ad60 — est. sk_notif_syscall1 (table 0x800000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065ad60, 0x0065ad60)
/* FUN_0065ad90 @ 0x0065ad90 — est. sk_notif_syscall1 (table 0x800000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065ad90, 0x0065ad90)
/* FUN_0065b450 @ 0x0065b450 — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065b450, 0x0065b450)
/* FUN_0065b480 @ 0x0065b480 — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065b480, 0x0065b480)
/* FUN_0065b4b0 @ 0x0065b4b0 — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065b4b0, 0x0065b4b0)
/* FUN_0065b4e0 @ 0x0065b4e0 — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065b4e0, 0x0065b4e0)
/* FUN_0065b510 @ 0x0065b510 — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065b510, 0x0065b510)
/* FUN_0065bbcc @ 0x0065bbcc — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065bbcc, 0x0065bbcc)
/* FUN_0065bbfc @ 0x0065bbfc — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065bbfc, 0x0065bbfc)
/* FUN_0065bc2c @ 0x0065bc2c — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065bc2c, 0x0065bc2c)
/* FUN_0065bc5c @ 0x0065bc5c — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065bc5c, 0x0065bc5c)
/* FUN_0065bc8c @ 0x0065bc8c — est. sk_notif_syscall1 (table 0x900000001) */
SK_NOTIF_STUB_B(sk_syscall1_0065bc8c, 0x0065bc8c)

/* ===================================================================== */
/* Syscall entry stubs — pattern C: 1-word staged retry-while-flag SVC   */
/* ===================================================================== */

#define SK_NOTIF_STUB_C(name_, addr_) \
static void name_(uint64_t flag, uint64_t w0) \
{ \
    uint64_t *msg = (uint64_t *)sk_thread_msg_area(); \
    msg[0] = w0; \
    do { \
        CallSupervisor(0); \
        msg[0] = w0; \
    } while (flag == 1); \
}

/* FUN_0065883c @ 0x0065883c — est. sk_notif_syscall2 (table 0x200000001) */
SK_NOTIF_STUB_C(sk_syscall2_0065883c, 0x0065883c)
/* FUN_00658fc0 @ 0x00658fc0 — est. sk_notif_syscall2 (table 0x300000001) */
SK_NOTIF_STUB_C(sk_syscall2_00658fc0, 0x00658fc0)
/* FUN_00659740 @ 0x00659740 — est. sk_notif_syscall2 (table 0x400000001) */
SK_NOTIF_STUB_C(sk_syscall2_00659740, 0x00659740)
/* FUN_00659ec0 @ 0x00659ec0 — est. sk_notif_syscall2 (table 0x500000001) */
SK_NOTIF_STUB_C(sk_syscall2_00659ec0, 0x00659ec0)
/* FUN_0065a640 @ 0x0065a640 — est. sk_notif_syscall2 (table 0x700000001) */
SK_NOTIF_STUB_C(sk_syscall2_0065a640, 0x0065a640)
/* FUN_0065adc0 @ 0x0065adc0 — est. sk_notif_syscall2 (table 0x800000001) */
SK_NOTIF_STUB_C(sk_syscall2_0065adc0, 0x0065adc0)
/* FUN_0065b540 @ 0x0065b540 — est. sk_notif_syscall2 (table 0x900000001) */
SK_NOTIF_STUB_C(sk_syscall2_0065b540, 0x0065b540)
/* FUN_0065bcbc @ 0x0065bcbc — est. sk_notif_syscall2 (table 0x900000001) */
SK_NOTIF_STUB_C(sk_syscall2_0065bcbc, 0x0065bcbc)

/* ===================================================================== */
/* Object-type method-table builders (version-tagged descriptor tables)  */
/* ===================================================================== */

/* FUN_006580ec @ 0x006580ec   (est. sk_objtype_table_build_0x200000001)
 * Ghidra: bool FUN_006580ec(long param_1, long param_2)
 * If param_1 matches the table's version tag 0x200000001, populates the
 * 0x1c0-byte object-type method/descriptor table at param_2 with a version
 * stamp, a name-string pointer (0x6a5ed4), and a dense set of method
 * pointers / inline-code (LAB_) and data (DAT_) references that make up the
 * object-type ops table. Returns whether param_1 matched.
 * Confidence: medium (structural table builder; no string match) */
static bool sk_objtype_table_build_0x200000001(uint64_t version, uint8_t *tbl)
{
    if (version == 0x200000001ULL) {
        *(uint64_t *)(tbl + 0x08) = 0x200000001ULL;
        *(uint64_t *)(tbl + 0x10) = 0x6a5ed4;                 /* name string */
        *(uint8_t  *)(tbl + 0x18) = 0;
        *(uint32_t *)(tbl + 0x1c) = 0xffffffff;
        *(uint8_t  *)(tbl + 0x20) = 0;
        *(uint64_t *)(tbl + 0x28) = 0;
        *(uint8_t  *)(tbl + 0x30) = 1;
        *(uint32_t *)(tbl + 0x34) = 3;
        *(int32_t  *)(tbl + 0x38) = (int32_t)DAT_006887b0;
        *(void **)  (tbl + 0x40) = (void *)0x00658474;        /* DAT_00658474 */
        *(void **)  (tbl + 0x48) = (void *)0x0065848c;        /* LAB_0065848c */
        *(void **)  (tbl + 0x50) = (void *)0x006584a4;        /* DAT_006584a4 */
        *(void **)  (tbl + 0x58) = (void *)sk_syscall1_0065874c; /* FUN_0065874c */
        *(void **)  (tbl + 0x60) = (void *)0x006584c0;        /* LAB_006584c0 */
        *(void **)  (tbl + 0x68) = (void *)sk_syscall1_0065877c; /* FUN_0065877c */
        *(void **)  (tbl + 0x70) = (void *)0x006584d8;        /* DAT_006584d8 */
        *(void **)  (tbl + 0x78) = (void *)0x00658510;        /* LAB_00658510 */
        *(void **)  (tbl + 0x80) = (void *)0x00658528;        /* LAB_00658528 */
        *(void **)  (tbl + 0x88) = (void *)0x00658540;        /* LAB_00658540 */
        *(void **)  (tbl + 0x90) = (void *)0x00658568;        /* DAT_00658568 */
        *(void **)  (tbl + 0x98) = (void *)sk_syscall1_006587ac; /* FUN_006587ac */
        *(uint8_t  *)(tbl + 0xa0) = 1;
        *(uint32_t *)(tbl + 0xa4) = 4;
        *(void **)  (tbl + 0xa8) = (void *)0x0065858c;        /* LAB_0065858c */
        *(void **)  (tbl + 0xb0) = (void *)0x00658594;        /* LAB_00658594 */
        *(void **)  (tbl + 0xb8) = (void *)0x0065859c;        /* DAT_0065859c */
        *(uint64_t *)(tbl + 0xc0) = 0x6585a4;
        *(uint64_t *)(tbl + 0xd0) = 0xc;
        *(void **)  (tbl + 0xd8) = (void *)0x006585ac;        /* LAB_006585ac */
        *(void **)  (tbl + 0xe0) = (void *)0x006585b4;        /* LAB_006585b4 */
        *(void **)  (tbl + 0xe8) = (void *)0x006585bc;        /* DAT_006585bc */
        *(uint16_t *)(tbl + 0xf0) = 0x1601;
        *(uint32_t *)(tbl + 0xf4) = 3;
        *(uint64_t *)(tbl + 0xf8) = 0x6585c4;
        *(void **)  (tbl + 0x100) = (void *)0x006585e4;       /* DAT_006585e4 */
        *(void **)  (tbl + 0x108) = (void *)0x00658600;       /* LAB_00658600 */
        *(void **)  (tbl + 0x110) = (void *)0x00658618;       /* LAB_00658618 */
        *(void **)  (tbl + 0x118) = (void *)0x00658620;       /* LAB_00658620 */
        *(void **)  (tbl + 0x120) = (void *)sk_syscall3_00658628; /* FUN_00658628 */
        *(void **)  (tbl + 0x128) = (void *)sk_syscall1_006587dc; /* FUN_006587dc */
        *(void **)  (tbl + 0x130) = (void *)0x00658654;       /* LAB_00658654 */
        *(void **)  (tbl + 0x138) = (void *)sk_syscall1_0065880c; /* FUN_0065880c */
        *(uint16_t *)(tbl + 0x149) = 0x1701;
        *(uint32_t *)(tbl + 0x14c) = 1;
        *(void **)  (tbl + 0x150) = (void *)0x00658670;       /* LAB_00658670 */
        *(void **)  (tbl + 0x158) = (void *)0x00658690;       /* LAB_00658690 */
        *(void **)  (tbl + 0x160) = (void *)sk_syscall2_0065883c; /* FUN_0065883c */
        *(void **)  (tbl + 0x168) = (void *)0x006586b0;       /* DAT_006586b0 */
        *(void **)  (tbl + 0x170) = (void *)0x006586f8;       /* DAT_006586f8 */
        *(uint8_t  *)(tbl + 0x140) = 1;
        *(uint32_t *)(tbl + 0x144) = 5;
        *(uint8_t  *)(tbl + 0x148) = 0;
        *(uint8_t  *)(tbl + 0x178) = 0x1a;
        *(void **)  (tbl + 0x180) = (void *)0x00688c90;       /* DAT_00688c90 */
        *(void **)  (tbl + 0x188) = (void *)0x00688d60;       /* DAT_00688d60 */
        *(uint64_t *)(tbl + 0x190) = 0x6b4ae8;
        *(void **)  (tbl + 0x198) = (void *)0x00658738;       /* LAB_00658738 */
        *(void **)  (tbl + 0x1a0) = (void *)0x00658740;       /* DAT_00658740 */
        *(uint8_t  *)(tbl + 0x1a8) = 1;
        *(uint64_t *)(tbl + 0x1b0) = 1;
        *(int32_t  *)(tbl + 0x1b8) = (int32_t)DAT_006887b8;
    }
    return version == 0x200000001ULL;
}

/* ===================================================================== */
/* Object-type method-table builders (generated; verify against decompile) */
/* ===================================================================== */

/* FUN_00658870 @ 0x00658870   (est. sk_objtype_table_build_0x300000001)
 * Ghidra: bool FUN_00658870(long param_1, long param_2)
 * Version-tagged object-type method-table builder. If param_1 matches tag
 * 0x300000001, fills the 0x1c0-byte descriptor table at param_2 with a version
 * stamp, name string (0x6a5ed4), method pointers and LAB_/DAT_ refs.
 * Returns whether param_1 matched the tag.
 * Confidence: medium (structural builder, no string match) */
static bool sk_objtype_table_build_0x300000001(uint64_t version, uint8_t *tbl)
{
    if (version == 0x300000001ULL) {
        *(uint64_t *)(tbl + 0x08) = 0x300000001ULL;
        *(uint64_t *)(tbl + 0x10) = 0x6a5ed4;
        *(uint8_t *)(tbl + 0x18) = 0;
        *(uint32_t *)(tbl + 0x1c) = 0xffffffff;
        *(uint8_t *)(tbl + 0x20) = 0;
        *(uint64_t *)(tbl + 0x28) = 0;
        *(uint8_t *)(tbl + 0x30) = 1;
        *(uint32_t *)(tbl + 0x34) = 3;
        *(int32_t *)(tbl + 0x38) = (int32_t)DAT_006887b0;
        *(void **)(tbl + 0x40) = (void *)(uintptr_t)0x00658bf8; /* &DAT_00658bf8 */
        *(void **)(tbl + 0x48) = (void *)(uintptr_t)0x00658c10; /* &DAT_00658c10 */
        *(void **)(tbl + 0x50) = (void *)(uintptr_t)0x00658c28; /* &LAB_00658c28 */
        *(void **)(tbl + 0x58) = (void *)sk_syscall1_00658ed0;
        *(void **)(tbl + 0x60) = (void *)(uintptr_t)0x00658c44; /* &LAB_00658c44 */
        *(void **)(tbl + 0x68) = (void *)sk_syscall1_00658f00;
        *(void **)(tbl + 0x70) = (void *)(uintptr_t)0x00658c5c; /* &DAT_00658c5c */
        *(void **)(tbl + 0x78) = (void *)(uintptr_t)0x00658c94; /* &LAB_00658c94 */
        *(void **)(tbl + 0x80) = (void *)(uintptr_t)0x00658cac; /* &LAB_00658cac */
        *(void **)(tbl + 0x88) = (void *)(uintptr_t)0x00658cc4; /* &LAB_00658cc4 */
        *(void **)(tbl + 0x90) = (void *)(uintptr_t)0x00658cec; /* &DAT_00658cec */
        *(void **)(tbl + 0x98) = (void *)sk_syscall1_00658f30;
        *(uint8_t *)(tbl + 0xa0) = 1;
        *(uint32_t *)(tbl + 0xa4) = 4;
        *(void **)(tbl + 0xa8) = (void *)(uintptr_t)0x00658d10; /* &LAB_00658d10 */
        *(void **)(tbl + 0xb0) = (void *)(uintptr_t)0x00658d18; /* &LAB_00658d18 */
        *(void **)(tbl + 0xb8) = (void *)(uintptr_t)0x00658d20; /* &LAB_00658d20 */
        *(void **)(tbl + 0xc0) = (void *)(uintptr_t)0x00658d28; /* &LAB_00658d28 */
        *(uint64_t *)(tbl + 0xd0) = 0xc;
        *(void **)(tbl + 0xd8) = (void *)(uintptr_t)0x00658d30; /* &LAB_00658d30 */
        *(void **)(tbl + 0xe0) = (void *)(uintptr_t)0x00658d38; /* &LAB_00658d38 */
        *(void **)(tbl + 0xe8) = (void *)(uintptr_t)0x00658d40; /* &LAB_00658d40 */
        *(uint16_t *)(tbl + 0xf0) = 0x1601;
        *(uint32_t *)(tbl + 0xf4) = 3;
        *(void **)(tbl + 0xf8) = (void *)(uintptr_t)0x00658d48; /* &LAB_00658d48 */
        *(void **)(tbl + 0x100) = (void *)(uintptr_t)0x00658d68; /* &LAB_00658d68 */
        *(void **)(tbl + 0x108) = (void *)(uintptr_t)0x00658d84; /* &LAB_00658d84 */
        *(void **)(tbl + 0x110) = (void *)(uintptr_t)0x00658d9c; /* &LAB_00658d9c */
        *(void **)(tbl + 0x118) = (void *)(uintptr_t)0x00658da4; /* &LAB_00658da4 */
        *(void **)(tbl + 0x120) = (void *)sk_syscall3_00658dac;
        *(void **)(tbl + 0x128) = (void *)sk_syscall1_00658f60;
        *(void **)(tbl + 0x130) = (void *)(uintptr_t)0x00658dd8; /* &LAB_00658dd8 */
        *(void **)(tbl + 0x138) = (void *)sk_syscall1_00658f90;
        *(uint16_t *)(tbl + 0x149) = 0x1701;
        *(uint32_t *)(tbl + 0x14c) = 1;
        *(void **)(tbl + 0x150) = (void *)(uintptr_t)0x00658df4; /* &LAB_00658df4 */
        *(void **)(tbl + 0x158) = (void *)(uintptr_t)0x00658e14; /* &LAB_00658e14 */
        *(void **)(tbl + 0x160) = (void *)sk_syscall2_00658fc0;
        *(void **)(tbl + 0x168) = (void *)(uintptr_t)0x00658e34; /* &LAB_00658e34 */
        *(void **)(tbl + 0x170) = (void *)(uintptr_t)0x00658e7c; /* &LAB_00658e7c */
        *(uint8_t *)(tbl + 0x140) = 1;
        *(uint32_t *)(tbl + 0x144) = 5;
        *(uint8_t *)(tbl + 0x148) = 0;
        *(uint8_t *)(tbl + 0x178) = 0x1a;
        *(void **)(tbl + 0x180) = (void *)(uintptr_t)0x00688e30; /* &DAT_00688e30 */
        *(void **)(tbl + 0x188) = (void *)(uintptr_t)0x00688f00; /* &DAT_00688f00 */
        *(uint64_t *)(tbl + 400) = 0x6b4bb8;
        *(void **)(tbl + 0x198) = (void *)(uintptr_t)0x00658ebc; /* &LAB_00658ebc */
        *(void **)(tbl + 0x1a0) = (void *)(uintptr_t)0x00658ec4; /* &LAB_00658ec4 */
        *(uint8_t *)(tbl + 0x1a8) = 1;
        *(uint64_t *)(tbl + 0x1b0) = 1;
        *(int32_t *)(tbl + 0x1b8) = (int32_t)DAT_006887b8;
        /* (unparsed) } */
    }
    return version == 0x300000001ULL;
}

/* FUN_00658ff4 @ 0x00658ff4   (est. sk_objtype_table_build_0x400000001)
 * Ghidra: bool FUN_00658ff4(long param_1, long param_2)
 * Version-tagged object-type method-table builder. If param_1 matches tag
 * 0x400000001, fills the 0x1c0-byte descriptor table at param_2 with a version
 * stamp, name string (0x6a5ed4), method pointers and LAB_/DAT_ refs.
 * Returns whether param_1 matched the tag.
 * Confidence: medium (structural builder, no string match) */
static bool sk_objtype_table_build_0x400000001(uint64_t version, uint8_t *tbl)
{
    if (version == 0x400000001ULL) {
        *(uint64_t *)(tbl + 0x08) = 0x400000001ULL;
        *(uint64_t *)(tbl + 0x10) = 0x6a5ed4;
        *(uint8_t *)(tbl + 0x18) = 0;
        *(uint32_t *)(tbl + 0x1c) = 0xffffffff;
        *(uint8_t *)(tbl + 0x20) = 0;
        *(uint64_t *)(tbl + 0x28) = 0;
        *(uint8_t *)(tbl + 0x30) = 1;
        *(uint32_t *)(tbl + 0x34) = 3;
        *(int32_t *)(tbl + 0x38) = (int32_t)DAT_006887b0;
        *(void **)(tbl + 0x40) = (void *)(uintptr_t)0x00659378; /* &LAB_00659378 */
        *(void **)(tbl + 0x48) = (void *)(uintptr_t)0x00659390; /* &LAB_00659390 */
        *(void **)(tbl + 0x50) = (void *)(uintptr_t)0x006593a8; /* &LAB_006593a8 */
        *(void **)(tbl + 0x58) = (void *)sk_syscall1_00659650;
        *(void **)(tbl + 0x60) = (void *)(uintptr_t)0x006593c4; /* &LAB_006593c4 */
        *(void **)(tbl + 0x68) = (void *)sk_syscall1_00659680;
        *(void **)(tbl + 0x70) = (void *)(uintptr_t)0x006593dc; /* &DAT_006593dc */
        *(void **)(tbl + 0x78) = (void *)(uintptr_t)0x00659414; /* &LAB_00659414 */
        *(void **)(tbl + 0x80) = (void *)(uintptr_t)0x0065942c; /* &LAB_0065942c */
        *(void **)(tbl + 0x88) = (void *)(uintptr_t)0x00659444; /* &LAB_00659444 */
        *(void **)(tbl + 0x90) = (void *)(uintptr_t)0x0065946c; /* &LAB_0065946c */
        *(void **)(tbl + 0x98) = (void *)sk_syscall1_006596b0;
        *(uint8_t *)(tbl + 0xa0) = 1;
        *(uint32_t *)(tbl + 0xa4) = 4;
        *(void **)(tbl + 0xa8) = (void *)(uintptr_t)0x00659490; /* &LAB_00659490 */
        *(void **)(tbl + 0xb0) = (void *)(uintptr_t)0x00659498; /* &LAB_00659498 */
        *(void **)(tbl + 0xb8) = (void *)(uintptr_t)0x006594a0; /* &LAB_006594a0 */
        *(void **)(tbl + 0xc0) = (void *)(uintptr_t)0x006594a8; /* &LAB_006594a8 */
        *(uint64_t *)(tbl + 0xd0) = 0xc;
        *(void **)(tbl + 0xd8) = (void *)(uintptr_t)0x006594b0; /* &LAB_006594b0 */
        *(void **)(tbl + 0xe0) = (void *)(uintptr_t)0x006594b8; /* &LAB_006594b8 */
        *(void **)(tbl + 0xe8) = (void *)(uintptr_t)0x006594c0; /* &LAB_006594c0 */
        *(uint16_t *)(tbl + 0xf0) = 0x1601;
        *(uint32_t *)(tbl + 0xf4) = 3;
        *(void **)(tbl + 0xf8) = (void *)(uintptr_t)0x006594c8; /* &LAB_006594c8 */
        *(void **)(tbl + 0x100) = (void *)(uintptr_t)0x006594e8; /* &LAB_006594e8 */
        *(void **)(tbl + 0x108) = (void *)(uintptr_t)0x00659504; /* &LAB_00659504 */
        *(void **)(tbl + 0x110) = (void *)(uintptr_t)0x0065951c; /* &LAB_0065951c */
        *(void **)(tbl + 0x118) = (void *)(uintptr_t)0x00659524; /* &LAB_00659524 */
        *(void **)(tbl + 0x120) = (void *)sk_syscall3_0065952c;
        *(void **)(tbl + 0x128) = (void *)sk_syscall1_006596e0;
        *(void **)(tbl + 0x130) = (void *)(uintptr_t)0x00659558; /* &LAB_00659558 */
        *(void **)(tbl + 0x138) = (void *)sk_syscall1_00659710;
        *(uint16_t *)(tbl + 0x149) = 0x1701;
        *(uint32_t *)(tbl + 0x14c) = 1;
        *(void **)(tbl + 0x150) = (void *)(uintptr_t)0x00659574; /* &LAB_00659574 */
        *(void **)(tbl + 0x158) = (void *)(uintptr_t)0x00659594; /* &LAB_00659594 */
        *(void **)(tbl + 0x160) = (void *)sk_syscall2_00659740;
        *(void **)(tbl + 0x168) = (void *)(uintptr_t)0x006595b4; /* &LAB_006595b4 */
        *(void **)(tbl + 0x170) = (void *)(uintptr_t)0x006595fc; /* &LAB_006595fc */
        *(uint8_t *)(tbl + 0x140) = 1;
        *(uint32_t *)(tbl + 0x144) = 5;
        *(uint8_t *)(tbl + 0x148) = 0;
        *(uint8_t *)(tbl + 0x178) = 0x1a;
        *(void **)(tbl + 0x180) = (void *)(uintptr_t)0x00688fd0; /* &DAT_00688fd0 */
        *(void **)(tbl + 0x188) = (void *)(uintptr_t)0x006890a0; /* &DAT_006890a0 */
        *(uint64_t *)(tbl + 400) = 0x6b4c88;
        *(void **)(tbl + 0x198) = (void *)(uintptr_t)0x0065963c; /* &LAB_0065963c */
        *(void **)(tbl + 0x1a0) = (void *)(uintptr_t)0x00659644; /* &LAB_00659644 */
        *(uint8_t *)(tbl + 0x1a8) = 1;
        *(uint64_t *)(tbl + 0x1b0) = 1;
        *(uint32_t *)(tbl + 0x1b8) = 1;
        /* (unparsed) } */
    }
    return version == 0x400000001ULL;
}

/* FUN_00659774 @ 0x00659774   (est. sk_objtype_table_build_0x500000001)
 * Ghidra: bool FUN_00659774(long param_1, long param_2)
 * Version-tagged object-type method-table builder. If param_1 matches tag
 * 0x500000001, fills the 0x1c0-byte descriptor table at param_2 with a version
 * stamp, name string (0x6a5ed4), method pointers and LAB_/DAT_ refs.
 * Returns whether param_1 matched the tag.
 * Confidence: medium (structural builder, no string match) */
static bool sk_objtype_table_build_0x500000001(uint64_t version, uint8_t *tbl)
{
    if (version == 0x500000001ULL) {
        *(uint64_t *)(tbl + 0x08) = 0x500000001ULL;
        *(uint64_t *)(tbl + 0x10) = 0x6a5ed4;
        *(uint8_t *)(tbl + 0x18) = 0;
        *(uint32_t *)(tbl + 0x1c) = 0xffffffff;
        *(uint8_t *)(tbl + 0x20) = 0;
        *(uint64_t *)(tbl + 0x28) = 0;
        *(uint8_t *)(tbl + 0x30) = 1;
        *(uint32_t *)(tbl + 0x34) = 3;
        *(int32_t *)(tbl + 0x38) = (int32_t)DAT_006887b0;
        *(void **)(tbl + 0x40) = (void *)(uintptr_t)0x00659af8; /* &LAB_00659af8 */
        *(void **)(tbl + 0x48) = (void *)(uintptr_t)0x00659b10; /* &LAB_00659b10 */
        *(void **)(tbl + 0x50) = (void *)(uintptr_t)0x00659b28; /* &LAB_00659b28 */
        *(void **)(tbl + 0x58) = (void *)sk_syscall1_00659dd0;
        *(void **)(tbl + 0x60) = (void *)(uintptr_t)0x00659b44; /* &DAT_00659b44 */
        *(void **)(tbl + 0x68) = (void *)sk_syscall1_00659e00;
        *(void **)(tbl + 0x70) = (void *)(uintptr_t)0x00659b5c; /* &LAB_00659b5c */
        *(void **)(tbl + 0x78) = (void *)(uintptr_t)0x00659b94; /* &LAB_00659b94 */
        *(void **)(tbl + 0x80) = (void *)(uintptr_t)0x00659bac; /* &LAB_00659bac */
        *(void **)(tbl + 0x88) = (void *)(uintptr_t)0x00659bc4; /* &LAB_00659bc4 */
        *(void **)(tbl + 0x90) = (void *)(uintptr_t)0x00659bec; /* &LAB_00659bec */
        *(void **)(tbl + 0x98) = (void *)sk_syscall1_00659e30;
        *(uint8_t *)(tbl + 0xa0) = 1;
        *(uint32_t *)(tbl + 0xa4) = 4;
        *(void **)(tbl + 0xa8) = (void *)(uintptr_t)0x00659c10; /* &LAB_00659c10 */
        *(void **)(tbl + 0xb0) = (void *)(uintptr_t)0x00659c18; /* &LAB_00659c18 */
        *(void **)(tbl + 0xb8) = (void *)(uintptr_t)0x00659c20; /* &LAB_00659c20 */
        *(void **)(tbl + 0xc0) = (void *)(uintptr_t)0x00659c28; /* &LAB_00659c28 */
        *(uint64_t *)(tbl + 0xd0) = 0xc;
        *(void **)(tbl + 0xd8) = (void *)(uintptr_t)0x00659c30; /* &LAB_00659c30 */
        *(void **)(tbl + 0xe0) = (void *)(uintptr_t)0x00659c38; /* &LAB_00659c38 */
        *(void **)(tbl + 0xe8) = (void *)(uintptr_t)0x00659c40; /* &LAB_00659c40 */
        *(uint16_t *)(tbl + 0xf0) = 0x1601;
        *(uint32_t *)(tbl + 0xf4) = 3;
        *(void **)(tbl + 0xf8) = (void *)(uintptr_t)0x00659c48; /* &DAT_00659c48 */
        *(void **)(tbl + 0x100) = (void *)(uintptr_t)0x00659c68; /* &LAB_00659c68 */
        *(void **)(tbl + 0x108) = (void *)(uintptr_t)0x00659c84; /* &LAB_00659c84 */
        *(void **)(tbl + 0x110) = (void *)(uintptr_t)0x00659c9c; /* &LAB_00659c9c */
        *(void **)(tbl + 0x118) = (void *)(uintptr_t)0x00659ca4; /* &LAB_00659ca4 */
        *(void **)(tbl + 0x120) = (void *)sk_syscall3_00659cac;
        *(void **)(tbl + 0x128) = (void *)sk_syscall1_00659e60;
        *(void **)(tbl + 0x130) = (void *)(uintptr_t)0x00659cd8; /* &LAB_00659cd8 */
        *(void **)(tbl + 0x138) = (void *)sk_syscall1_00659e90;
        *(uint16_t *)(tbl + 0x149) = 0x1701;
        *(uint32_t *)(tbl + 0x14c) = 1;
        *(void **)(tbl + 0x150) = (void *)(uintptr_t)0x00659cf4; /* &LAB_00659cf4 */
        *(void **)(tbl + 0x158) = (void *)(uintptr_t)0x00659d14; /* &LAB_00659d14 */
        *(void **)(tbl + 0x160) = (void *)sk_syscall2_00659ec0;
        *(void **)(tbl + 0x168) = (void *)(uintptr_t)0x00659d34; /* &LAB_00659d34 */
        *(void **)(tbl + 0x170) = (void *)(uintptr_t)0x00659d7c; /* &LAB_00659d7c */
        *(uint8_t *)(tbl + 0x140) = 1;
        *(uint32_t *)(tbl + 0x144) = 5;
        *(uint8_t *)(tbl + 0x148) = 0;
        *(uint8_t *)(tbl + 0x178) = 0x1a;
        *(void **)(tbl + 0x180) = (void *)(uintptr_t)0x00689170; /* &DAT_00689170 */
        *(void **)(tbl + 0x188) = (void *)(uintptr_t)0x00689240; /* &DAT_00689240 */
        *(uint64_t *)(tbl + 400) = 0x6b4d58;
        *(void **)(tbl + 0x198) = (void *)(uintptr_t)0x00659dbc; /* &LAB_00659dbc */
        *(void **)(tbl + 0x1a0) = (void *)(uintptr_t)0x00659dc4; /* &LAB_00659dc4 */
        *(uint8_t *)(tbl + 0x1a8) = 1;
        *(uint64_t *)(tbl + 0x1b0) = 1;
        *(uint32_t *)(tbl + 0x1b8) = 1;
        /* (unparsed) } */
    }
    return version == 0x500000001ULL;
}

/* FUN_0065a674 @ 0x0065a674   (est. sk_objtype_table_build_0x700000001)
 * Ghidra: bool FUN_0065a674(long param_1, long param_2)
 * Version-tagged object-type method-table builder. If param_1 matches tag
 * 0x700000001, fills the 0x1c0-byte descriptor table at param_2 with a version
 * stamp, name string (0x6a5ed4), method pointers and LAB_/DAT_ refs.
 * Returns whether param_1 matched the tag.
 * Confidence: medium (structural builder, no string match) */
static bool sk_objtype_table_build_0x700000001(uint64_t version, uint8_t *tbl)
{
    if (version == 0x700000001ULL) {
        *(uint64_t *)(tbl + 0x08) = 0x700000001ULL;
        *(uint64_t *)(tbl + 0x10) = 0x6a5ed4;
        *(uint8_t *)(tbl + 0x18) = 0;
        *(uint32_t *)(tbl + 0x1c) = 0xffffffff;
        *(uint8_t *)(tbl + 0x20) = 0;
        *(uint64_t *)(tbl + 0x28) = 0;
        *(uint8_t *)(tbl + 0x30) = 1;
        *(uint32_t *)(tbl + 0x34) = 3;
        *(int32_t *)(tbl + 0x38) = (int32_t)DAT_006887b0;
        *(void **)(tbl + 0x40) = (void *)(uintptr_t)0x0065a9f8; /* &LAB_0065a9f8 */
        *(void **)(tbl + 0x48) = (void *)(uintptr_t)0x0065aa10; /* &LAB_0065aa10 */
        *(void **)(tbl + 0x50) = (void *)(uintptr_t)0x0065aa28; /* &LAB_0065aa28 */
        *(void **)(tbl + 0x58) = (void *)sk_syscall1_0065acd0;
        *(void **)(tbl + 0x60) = (void *)(uintptr_t)0x0065aa44; /* &DAT_0065aa44 */
        *(void **)(tbl + 0x68) = (void *)sk_syscall1_0065ad00;
        *(void **)(tbl + 0x70) = (void *)(uintptr_t)0x0065aa5c; /* &LAB_0065aa5c */
        *(void **)(tbl + 0x78) = (void *)(uintptr_t)0x0065aa94; /* &LAB_0065aa94 */
        *(void **)(tbl + 0x80) = (void *)(uintptr_t)0x0065aaac; /* &LAB_0065aaac */
        *(void **)(tbl + 0x88) = (void *)(uintptr_t)0x0065aac4; /* &LAB_0065aac4 */
        *(void **)(tbl + 0x90) = (void *)(uintptr_t)0x0065aaec; /* &LAB_0065aaec */
        *(void **)(tbl + 0x98) = (void *)sk_syscall1_0065ad30;
        *(uint8_t *)(tbl + 0xa0) = 1;
        *(uint32_t *)(tbl + 0xa4) = 4;
        *(void **)(tbl + 0xa8) = (void *)(uintptr_t)0x0065ab10; /* &LAB_0065ab10 */
        *(void **)(tbl + 0xb0) = (void *)(uintptr_t)0x0065ab18; /* &LAB_0065ab18 */
        *(void **)(tbl + 0xb8) = (void *)(uintptr_t)0x0065ab20; /* &LAB_0065ab20 */
        *(void **)(tbl + 0xc0) = (void *)(uintptr_t)0x0065ab28; /* &LAB_0065ab28 */
        *(uint64_t *)(tbl + 0xd0) = 0xc;
        *(void **)(tbl + 0xd8) = (void *)(uintptr_t)0x0065ab30; /* &LAB_0065ab30 */
        *(void **)(tbl + 0xe0) = (void *)(uintptr_t)0x0065ab38; /* &LAB_0065ab38 */
        *(void **)(tbl + 0xe8) = (void *)(uintptr_t)0x0065ab40; /* &LAB_0065ab40 */
        *(uint16_t *)(tbl + 0xf0) = 0x1601;
        *(uint32_t *)(tbl + 0xf4) = 3;
        *(void **)(tbl + 0xf8) = (void *)(uintptr_t)0x0065ab48; /* &LAB_0065ab48 */
        *(void **)(tbl + 0x100) = (void *)(uintptr_t)0x0065ab68; /* &LAB_0065ab68 */
        *(void **)(tbl + 0x108) = (void *)(uintptr_t)0x0065ab84; /* &LAB_0065ab84 */
        *(void **)(tbl + 0x110) = (void *)(uintptr_t)0x0065ab9c; /* &LAB_0065ab9c */
        *(void **)(tbl + 0x118) = (void *)(uintptr_t)0x0065aba4; /* &LAB_0065aba4 */
        *(void **)(tbl + 0x120) = (void *)sk_syscall3_0065abac;
        *(void **)(tbl + 0x128) = (void *)sk_syscall1_0065ad60;
        *(void **)(tbl + 0x130) = (void *)(uintptr_t)0x0065abd8; /* &LAB_0065abd8 */
        *(void **)(tbl + 0x138) = (void *)sk_syscall1_0065ad90;
        *(uint16_t *)(tbl + 0x149) = 0x1701;
        *(uint32_t *)(tbl + 0x14c) = 1;
        *(void **)(tbl + 0x150) = (void *)(uintptr_t)0x0065abf4; /* &LAB_0065abf4 */
        *(void **)(tbl + 0x158) = (void *)(uintptr_t)0x0065ac14; /* &LAB_0065ac14 */
        *(void **)(tbl + 0x160) = (void *)sk_syscall2_0065adc0;
        *(void **)(tbl + 0x168) = (void *)(uintptr_t)0x0065ac34; /* &DAT_0065ac34 */
        *(void **)(tbl + 0x170) = (void *)(uintptr_t)0x0065ac7c; /* &LAB_0065ac7c */
        *(uint8_t *)(tbl + 0x140) = 1;
        *(uint32_t *)(tbl + 0x144) = 5;
        *(uint8_t *)(tbl + 0x148) = 0;
        *(uint8_t *)(tbl + 0x178) = 0x1a;
        *(void **)(tbl + 0x180) = (void *)(uintptr_t)0x006894b0; /* &DAT_006894b0 */
        *(void **)(tbl + 0x188) = (void *)(uintptr_t)0x00689580; /* &DAT_00689580 */
        *(uint64_t *)(tbl + 400) = 0x6b4ef8;
        *(void **)(tbl + 0x198) = (void *)(uintptr_t)0x0065acbc; /* &LAB_0065acbc */
        *(void **)(tbl + 0x1a0) = (void *)(uintptr_t)0x0065acc4; /* &LAB_0065acc4 */
        *(uint8_t *)(tbl + 0x1a8) = 1;
        *(uint64_t *)(tbl + 0x1b0) = 1;
        *(uint32_t *)(tbl + 0x1b8) = 1;
        /* (unparsed) } */
    }
    return version == 0x700000001ULL;
}

/* FUN_0065adf4 @ 0x0065adf4   (est. sk_objtype_table_build_0x800000001)
 * Ghidra: bool FUN_0065adf4(long param_1, long param_2)
 * Version-tagged object-type method-table builder. If param_1 matches tag
 * 0x800000001, fills the 0x1c0-byte descriptor table at param_2 with a version
 * stamp, name string (0x6a5ed4), method pointers and LAB_/DAT_ refs.
 * Returns whether param_1 matched the tag.
 * Confidence: medium (structural builder, no string match) */
static bool sk_objtype_table_build_0x800000001(uint64_t version, uint8_t *tbl)
{
    if (version == 0x800000001ULL) {
        *(uint64_t *)(tbl + 0x08) = 0x800000001ULL;
        *(uint64_t *)(tbl + 0x10) = 0x6a5ed4;
        *(uint8_t *)(tbl + 0x18) = 0;
        *(uint32_t *)(tbl + 0x1c) = 0xffffffff;
        *(uint8_t *)(tbl + 0x20) = 0;
        *(uint64_t *)(tbl + 0x28) = 0;
        *(uint8_t *)(tbl + 0x30) = 1;
        *(uint32_t *)(tbl + 0x34) = 3;
        *(int32_t *)(tbl + 0x38) = (int32_t)DAT_006887b0;
        *(void **)(tbl + 0x40) = (void *)(uintptr_t)0x0065b178; /* &LAB_0065b178 */
        *(void **)(tbl + 0x48) = (void *)(uintptr_t)0x0065b190; /* &DAT_0065b190 */
        *(void **)(tbl + 0x50) = (void *)(uintptr_t)0x0065b1a8; /* &DAT_0065b1a8 */
        *(void **)(tbl + 0x58) = (void *)sk_syscall1_0065b450;
        *(void **)(tbl + 0x60) = (void *)(uintptr_t)0x0065b1c4; /* &LAB_0065b1c4 */
        *(void **)(tbl + 0x68) = (void *)sk_syscall1_0065b480;
        *(void **)(tbl + 0x70) = (void *)(uintptr_t)0x0065b1dc; /* &DAT_0065b1dc */
        *(void **)(tbl + 0x78) = (void *)(uintptr_t)0x0065b214; /* &LAB_0065b214 */
        *(void **)(tbl + 0x80) = (void *)(uintptr_t)0x0065b22c; /* &DAT_0065b22c */
        *(void **)(tbl + 0x88) = (void *)(uintptr_t)0x0065b244; /* &DAT_0065b244 */
        *(void **)(tbl + 0x90) = (void *)(uintptr_t)0x0065b26c; /* &DAT_0065b26c */
        *(void **)(tbl + 0x98) = (void *)sk_syscall1_0065b4b0;
        *(uint8_t *)(tbl + 0xa0) = 1;
        *(uint32_t *)(tbl + 0xa4) = 4;
        *(void **)(tbl + 0xa8) = (void *)(uintptr_t)0x0065b290; /* &LAB_0065b290 */
        *(void **)(tbl + 0xb0) = (void *)(uintptr_t)0x0065b298; /* &LAB_0065b298 */
        *(void **)(tbl + 0xb8) = (void *)(uintptr_t)0x0065b2a0; /* &LAB_0065b2a0 */
        *(void **)(tbl + 0xc0) = (void *)(uintptr_t)0x0065b2a8; /* &LAB_0065b2a8 */
        *(uint64_t *)(tbl + 0xd0) = 0xc;
        *(void **)(tbl + 0xd8) = (void *)(uintptr_t)0x0065b2b0; /* &LAB_0065b2b0 */
        *(void **)(tbl + 0xe0) = (void *)(uintptr_t)0x0065b2b8; /* &LAB_0065b2b8 */
        *(void **)(tbl + 0xe8) = (void *)(uintptr_t)0x0065b2c0; /* &LAB_0065b2c0 */
        *(uint16_t *)(tbl + 0xf0) = 0x1601;
        *(uint32_t *)(tbl + 0xf4) = 3;
        *(void **)(tbl + 0xf8) = (void *)(uintptr_t)0x0065b2c8; /* &DAT_0065b2c8 */
        *(void **)(tbl + 0x100) = (void *)(uintptr_t)0x0065b2e8; /* &DAT_0065b2e8 */
        *(void **)(tbl + 0x108) = (void *)(uintptr_t)0x0065b304; /* &LAB_0065b304 */
        *(void **)(tbl + 0x110) = (void *)(uintptr_t)0x0065b31c; /* &DAT_0065b31c */
        *(void **)(tbl + 0x118) = (void *)(uintptr_t)0x0065b324; /* &LAB_0065b324 */
        *(void **)(tbl + 0x120) = (void *)sk_syscall1_0065b32c;
        *(void **)(tbl + 0x128) = (void *)sk_syscall1_0065b4e0;
        *(void **)(tbl + 0x130) = (void *)(uintptr_t)0x0065b358; /* &LAB_0065b358 */
        *(void **)(tbl + 0x138) = (void *)sk_syscall1_0065b510;
        *(uint16_t *)(tbl + 0x149) = 0x1701;
        *(uint32_t *)(tbl + 0x14c) = 1;
        *(void **)(tbl + 0x150) = (void *)(uintptr_t)0x0065b374; /* &DAT_0065b374 */
        *(void **)(tbl + 0x158) = (void *)(uintptr_t)0x0065b394; /* &DAT_0065b394 */
        *(void **)(tbl + 0x160) = (void *)sk_syscall2_0065b540;
        *(void **)(tbl + 0x168) = (void *)(uintptr_t)0x0065b3b4; /* &DAT_0065b3b4 */
        *(void **)(tbl + 0x170) = (void *)(uintptr_t)0x0065b3fc; /* &DAT_0065b3fc */
        *(uint8_t *)(tbl + 0x140) = 1;
        *(uint32_t *)(tbl + 0x144) = 5;
        *(uint8_t *)(tbl + 0x148) = 0;
        *(uint8_t *)(tbl + 0x178) = 0x1a;
        *(void **)(tbl + 0x180) = (void *)(uintptr_t)0x00689650; /* &DAT_00689650 */
        *(void **)(tbl + 0x188) = (void *)(uintptr_t)0x00689720; /* &DAT_00689720 */
        *(uint64_t *)(tbl + 400) = 0x6b4fc8;
        *(void **)(tbl + 0x198) = (void *)(uintptr_t)0x0065b43c; /* &DAT_0065b43c */
        *(void **)(tbl + 0x1a0) = (void *)(uintptr_t)0x0065b444; /* &LAB_0065b444 */
        *(uint8_t *)(tbl + 0x1a8) = 1;
        *(uint64_t *)(tbl + 0x1b0) = 1;
        *(uint32_t *)(tbl + 0x1b8) = 1;
        /* (unparsed) } */
    }
    return version == 0x800000001ULL;
}

/* FUN_0065b574 @ 0x0065b574   (est. sk_objtype_table_build_0x900000001)
 * Ghidra: bool FUN_0065b574(long param_1, long param_2)
 * Version-tagged object-type method-table builder. If param_1 matches tag
 * 0x900000001, fills the 0x1c0-byte descriptor table at param_2 with a version
 * stamp, name string (0x6a5ed4), method pointers and LAB_/DAT_ refs.
 * Returns whether param_1 matched the tag.
 * Confidence: medium (structural builder, no string match) */
static bool sk_objtype_table_build_0x900000001(uint64_t version, uint8_t *tbl)
{
    if (version == 0x900000001ULL) {
        *(uint64_t *)(tbl + 0x08) = 0x900000001ULL;
        *(uint64_t *)(tbl + 0x10) = 0x6a5ed4;
        *(uint8_t *)(tbl + 0x18) = 0;
        *(uint32_t *)(tbl + 0x1c) = 0xffffffff;
        *(uint8_t *)(tbl + 0x20) = 0;
        *(uint64_t *)(tbl + 0x28) = 0;
        *(uint8_t *)(tbl + 0x30) = 1;
        *(uint32_t *)(tbl + 0x34) = 3;
        *(int32_t *)(tbl + 0x38) = (int32_t)DAT_006887b0;
        *(void **)(tbl + 0x40) = (void *)(uintptr_t)0x0065b8f4; /* &LAB_0065b8f4 */
        *(void **)(tbl + 0x48) = (void *)(uintptr_t)0x0065b90c; /* &DAT_0065b90c */
        *(void **)(tbl + 0x50) = (void *)(uintptr_t)0x0065b924; /* &LAB_0065b924 */
        *(void **)(tbl + 0x58) = (void *)sk_syscall1_0065bbcc;
        *(void **)(tbl + 0x60) = (void *)(uintptr_t)0x0065b940; /* &DAT_0065b940 */
        *(void **)(tbl + 0x68) = (void *)sk_syscall1_0065bbfc;
        *(void **)(tbl + 0x70) = (void *)(uintptr_t)0x0065b958; /* &DAT_0065b958 */
        *(void **)(tbl + 0x78) = (void *)(uintptr_t)0x0065b990; /* &LAB_0065b990 */
        *(void **)(tbl + 0x80) = (void *)(uintptr_t)0x0065b9a8; /* &LAB_0065b9a8 */
        *(void **)(tbl + 0x88) = (void *)(uintptr_t)0x0065b9c0; /* &DAT_0065b9c0 */
        *(void **)(tbl + 0x90) = (void *)(uintptr_t)0x0065b9e8; /* &DAT_0065b9e8 */
        *(void **)(tbl + 0x98) = (void *)sk_syscall1_0065bc2c;
        *(uint8_t *)(tbl + 0xa0) = 1;
        *(uint32_t *)(tbl + 0xa4) = 4;
        *(void **)(tbl + 0xa8) = (void *)(uintptr_t)0x0065ba0c; /* &LAB_0065ba0c */
        *(void **)(tbl + 0xb0) = (void *)(uintptr_t)0x0065ba14; /* &LAB_0065ba14 */
        *(void **)(tbl + 0xb8) = (void *)(uintptr_t)0x0065ba1c; /* &LAB_0065ba1c */
        *(void **)(tbl + 0xc0) = (void *)(uintptr_t)0x0065ba24; /* &LAB_0065ba24 */
        *(uint64_t *)(tbl + 0xd0) = 0xc;
        *(void **)(tbl + 0xd8) = (void *)(uintptr_t)0x0065ba2c; /* &LAB_0065ba2c */
        *(void **)(tbl + 0xe0) = (void *)(uintptr_t)0x0065ba34; /* &DAT_0065ba34 */
        *(void **)(tbl + 0xe8) = (void *)(uintptr_t)0x0065ba3c; /* &LAB_0065ba3c */
        *(uint16_t *)(tbl + 0xf0) = 0x1601;
        *(uint32_t *)(tbl + 0xf4) = 3;
        *(void **)(tbl + 0xf8) = (void *)(uintptr_t)0x0065ba44; /* &LAB_0065ba44 */
        *(void **)(tbl + 0x100) = (void *)(uintptr_t)0x0065ba64; /* &DAT_0065ba64 */
        *(void **)(tbl + 0x108) = (void *)(uintptr_t)0x0065ba80; /* &LAB_0065ba80 */
        *(void **)(tbl + 0x110) = (void *)(uintptr_t)0x0065ba98; /* &LAB_0065ba98 */
        *(void **)(tbl + 0x118) = (void *)(uintptr_t)0x0065baa0; /* &LAB_0065baa0 */
        *(void **)(tbl + 0x120) = (void *)sk_syscall3_0065baa8;
        *(void **)(tbl + 0x128) = (void *)sk_syscall1_0065bc5c;
        *(void **)(tbl + 0x130) = (void *)(uintptr_t)0x0065bad4; /* &LAB_0065bad4 */
        *(void **)(tbl + 0x138) = (void *)sk_syscall1_0065bc8c;
        *(uint16_t *)(tbl + 0x149) = 0x1701;
        *(uint32_t *)(tbl + 0x14c) = 1;
        *(void **)(tbl + 0x150) = (void *)(uintptr_t)0x0065baf0; /* &DAT_0065baf0 */
        *(void **)(tbl + 0x158) = (void *)(uintptr_t)0x0065bb10; /* &DAT_0065bb10 */
        *(void **)(tbl + 0x160) = (void *)sk_syscall2_0065bcbc;
        *(void **)(tbl + 0x168) = (void *)(uintptr_t)0x0065bb30; /* &DAT_0065bb30 */
        *(void **)(tbl + 0x170) = (void *)(uintptr_t)0x0065bb78; /* &DAT_0065bb78 */
        *(uint8_t *)(tbl + 0x140) = 1;
        *(uint32_t *)(tbl + 0x144) = 5;
        *(uint8_t *)(tbl + 0x148) = 0;
        *(uint8_t *)(tbl + 0x178) = 0x1a;
        *(void **)(tbl + 0x180) = (void *)(uintptr_t)0x006897f0; /* &DAT_006897f0 */
        *(void **)(tbl + 0x188) = (void *)(uintptr_t)0x006898c0; /* &DAT_006898c0 */
        *(uint64_t *)(tbl + 400) = 0x6b5098;
        *(void **)(tbl + 0x198) = (void *)(uintptr_t)0x0065bbb8; /* &LAB_0065bbb8 */
        *(void **)(tbl + 0x1a0) = (void *)(uintptr_t)0x0065bbc0; /* &LAB_0065bbc0 */
        *(uint8_t *)(tbl + 0x1a8) = 1;
        *(uint64_t *)(tbl + 0x1b0) = 1;
        *(uint32_t *)(tbl + 0x1b8) = 0;
        /* (unparsed) } */
    }
    return version == 0x900000001ULL;
}


/* ===================================================================== */
/* Notification-list manager (global object @ 0x6fe638)                   */
/* ===================================================================== */

/* FUN_0065be08 @ 0x0065be08   (est. sk_notif_list_ensure)
 * Ghidra: void FUN_0065be08(long *param_1, undefined8 param_2, undefined8 param_3)
 * If the slot at *param_1 is null, lazily resolves the global notification
 * object via FUN_0065cc0c(param_2,param_3) (an id->object lookup keyed by
 * (major,minor)) and caches it. Used to fetch the singleton object whose
 * address is stored at 0x6fe638.
 * Confidence: medium */
static long sk_notif_list_ensure(long *slot, uint64_t major, uint64_t minor)
{
    if (*slot == 0) {
        *slot = sk_notif_id_lookup(major, minor);
    }
    return *slot;
}

/* FUN_0065cc0c @ 0x0065cc0c   (est. sk_notif_id_lookup)
 * Ghidra: long FUN_0065cc0c(int param_1,int param_2)
 * Walks the per-CPU object-id list (anchored at **(tpidr_el0+0x10)) and
 * returns the stored object pointer whose (id_major==param_1, id_minor==param_2)
 * match; returns 0 if not found.
 * Confidence: medium */
static long sk_notif_id_lookup(int major, int minor)
{
    long cur;
    long *list = *(long **)**(long **)((char *)sk_thread_base() + 0x10);
    long found = 0;
    if (list == 0) {
        return 0;
    }
    do {
        cur = list[3];
        if ((int)(uintptr_t)list[2] != minor || (int)(uintptr_t)list[1] != major) {
            cur = found;
        }
        list = (long *)*list;
        found = cur;
    } while (list != 0);
    return found;
}

/* FUN_0065c27c @ 0x0065c27c   (est. sk_notif_ensure_param)
 * Ghidra: void FUN_0065c27c(undefined8 param_1)
 * Ensures the notification object referenced by param_1 (a long* slot) is
 * populated via sk_notif_list_ensure with fixed ids (1,3).
 * Confidence: medium */
static void sk_notif_ensure_param(uint64_t *slot)
{
    sk_notif_list_ensure((long *)slot, 1, 3);
}

/* FUN_0065ccc8 @ 0x0065ccc8   (est. sk_notif_ensure_default)
 * Ghidra: void FUN_0065ccc8(void)
 * Ensures the default notification object at 0x6fe638 is populated (ids 1,1).
 * Confidence: medium */
static void sk_notif_ensure_default(void)
{
    sk_notif_list_ensure(&_DAT_006fe638, 1, 1);
}

/* FUN_0065c9c0 @ 0x0065c9c0   (est. sk_notif_get_info)
 * Ghidra: undefined8 FUN_0065c9c0(undefined8 *param_1)
 * Fetches the notification object at 0x6fe638; writes its +0x70 field to
 * *param_1 and returns its +0x78 field.
 * Confidence: medium */
static uint64_t sk_notif_get_info(uint64_t *out)
{
    long obj = sk_notif_list_ensure(&_DAT_006fe638, 1, 1);
    uint64_t r = *(uint64_t *)(obj + 0x78);
    *out = *(uint64_t *)(obj + 0x70);
    return r;
}

/* FUN_0065c9fc @ 0x0065c9fc   (est. sk_notif_get_slot)
 * Ghidra: undefined8 FUN_0065c9fc(void)
 * Returns the +0x40 word of the notification object at 0x6fe638.
 * Confidence: medium */
static uint64_t sk_notif_get_slot(void)
{
    long obj = sk_notif_list_ensure(&_DAT_006fe638, 1, 1);
    return *(uint64_t *)(obj + 0x40);
}

/* FUN_0065cb74 @ 0x0065cb74   (est. sk_notif_get_head)
 * Ghidra: undefined8 FUN_0065cb74(void)
 * Returns the first word (*) of the notification object at 0x6fe638.
 * Confidence: medium */
static uint64_t sk_notif_get_head(void)
{
    uint64_t *obj = (uint64_t *)sk_notif_list_ensure(&_DAT_006fe638, 1, 1);
    return *obj;
}

/* FUN_0065cfa8 @ 0x0065cfa8   (est. sk_notif_set_info)
 * Ghidra: void FUN_0065cfa8(undefined8 param_1, undefined8 param_2)
 * Stores param_1 into obj+0x78 and param_2 into obj+0x70 of the 0x6fe638 obj.
 * Confidence: medium */
static void sk_notif_set_info(uint64_t a, uint64_t b)
{
    long obj = sk_notif_list_ensure(&_DAT_006fe638, 1, 1);
    *(uint64_t *)(obj + 0x70) = b;
    *(uint64_t *)(obj + 0x78) = a;
}

/* ===================================================================== */
/* Small helpers                                                          */
/* ===================================================================== */

/* FUN_0065c984 @ 0x0065c984   (est. sk_log_msg)
 * Ghidra: void FUN_0065c984(undefined8,undefined8,undefined8,undefined8)
 * Forwards to the n-arg log/formatter FUN_0067ca84 with a 0 pad arg.
 * Confidence: medium */
static void sk_log_msg(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    FUN_0067ca84((void *)a, (void *)c, 0, (void *)b, (void *)d, 0);
}

/* FUN_0065cba0 @ 0x0065cba0   (est. sk_reg_setup_a)
 * Ghidra: void FUN_0065cba0(undefined8 param_1)
 * Stores 0x6fe5a0 into the global slot 0x6b5220 and param_1 into 0x6fe5f0,
 * then links it into the notification list via FUN_0065cbbc.
 * Confidence: medium */
static void sk_reg_setup_a(uint64_t param_1)
{
    _DAT_006b5220 = 0x6fe5a0;
    _DAT_006fe5f0 = param_1;
    FUN_0065cbbc((long *)&_DAT_006b5220);
}

/* FUN_0065be9c @ 0x0065be9c   (est. sk_reg_setup_b)
 * Ghidra: void FUN_0065be9c(void)
 * Stores 0x6b5170 into 0x6b51f8 and links it into the list via FUN_0065cbbc.
 * Confidence: medium */
static void sk_reg_setup_b(void)
{
    _DAT_006b51f8 = 0x6b5170;
    FUN_0065cbbc((long *)&_DAT_006b51f8);
}

/* FUN_0065d2cc @ 0x0065d2cc   (est. sk_reg_setup_c)
 * Ghidra: void FUN_0065d2cc(void)
 * Stores 0x6fe640 into 0x6b5240 and links it into the list via FUN_0065cbbc.
 * Confidence: medium */
static void sk_reg_setup_c(void)
{
    _DAT_006b5240 = 0x6fe640;
    FUN_0065cbbc((long *)&_DAT_006b5240);
}

/* FUN_0065c29c @ 0x0065c29c   (est. sk_reg_init_once)
 * Ghidra: void FUN_0065c29c(void)
 * If global 0x6fc598 is non-zero, returns; else initializes it to 0x6b6490.
 * Confidence: medium */
static void sk_reg_init_once(void)
{
    if (_DAT_006fc598 != 0) {
        return;
    }
    _DAT_006fc598 = 0x6b6490;
}

/* FUN_0065c288 @ 0x0065c288   (est. sk_panic_msg_once)
 * Ghidra: void FUN_0065c288(undefined8 param_1)
 * Captures param_1 into a stack slot then calls noreturn panic FUN_0067b280
 * with message 0x6a612a.
 * Confidence: medium */
static void sk_panic_msg_once(uint64_t param_1)
{
    uint64_t saved = param_1;
    (void)saved;
    FUN_0067b280(0x6a612a);   /* noreturn */
}

/* FUN_0065d6e8 @ 0x0065d6e8   (est. sk_log_warn_5139)
 * Ghidra: void FUN_0065d6e8(void)
 * Logs message 0x6a5139 with a 0x20/0x1f framing.
 * Confidence: medium */
static void sk_log_warn_5139(void)
{
    uint8_t scratch[0x20];
    sk_log_msg((uint64_t)(uintptr_t)scratch, 0x20, 0x1f, 0x6a5139);
}

/* ===================================================================== */
/* Empty no-op stubs (FUN_0065d4e0, d574, d5a0, d5c8, d5f0, d608, d620,  */
/* d670, d680, d69c, d6b8, d6d0, d700) — return immediately              */
/* ===================================================================== */

/* FUN_0065d4e0 @ 0x0065d4e0   (est. sk_noop) — empty */
static void sk_noop_d4e0(void) { }
/* FUN_0065d574 @ 0x0065d574   (est. sk_noop) — empty */
static void sk_noop_d574(void) { }
/* FUN_0065d5a0 @ 0x0065d5a0   (est. sk_noop) — empty */
static void sk_noop_d5a0(void) { }
/* FUN_0065d5c8 @ 0x0065d5c8   (est. sk_noop) — empty */
static void sk_noop_d5c8(void) { }
/* FUN_0065d5f0 @ 0x0065d5f0   (est. sk_noop) — empty */
static void sk_noop_d5f0(void) { }
/* FUN_0065d608 @ 0x0065d608   (est. sk_noop) — empty */
static void sk_noop_d608(void) { }
/* FUN_0065d620 @ 0x0065d620   (est. sk_noop) — empty */
static void sk_noop_d620(void) { }
/* FUN_0065d670 @ 0x0065d670   (est. sk_noop) — empty */
static void sk_noop_d670(void) { }
/* FUN_0065d680 @ 0x0065d680   (est. sk_noop) — empty */
static void sk_noop_d680(void) { }
/* FUN_0065d69c @ 0x0065d69c   (est. sk_noop) — empty */
static void sk_noop_d69c(void) { }
/* FUN_0065d6b8 @ 0x0065d6b8   (est. sk_noop) — empty */
static void sk_noop_d6b8(void) { }
/* FUN_0065d6d0 @ 0x0065d6d0   (est. sk_noop) — empty */
static void sk_noop_d6d0(void) { }
/* FUN_0065d700 @ 0x0065d700   (est. sk_noop) — empty */
static void sk_noop_d700(void) { }

/* ===================================================================== */
/* Complex notification logic                                            */
/* ===================================================================== */

/* FUN_0065bd88 @ 0x0065bd88   (est. sk_notif_feature_check)
 * Ghidra: ulong FUN_0065bd88(void)
 * Returns whether a notification feature is enabled: reads a per-cpu byte
 * (FUN_00655848); if bit0 clear, looks up string 0x6a60ff via FUN_006661e0,
 * compares against 0x6a610e; if equal calls FUN_0065bcf0(2,1) and returns
 * whether that returned 1.
 * Confidence: medium */
static uint64_t sk_notif_feature_check(void)
{
    uint64_t r = FUN_00656c68();
    if ((int)r != 0) {
        uint8_t *pcb = (uint8_t *)FUN_00655848();
        if ((*pcb & 1) == 0) {
            uint64_t local = 0;
            long l = FUN_006661e0(0x6a60ff, &local);
            if (l == 0 || FUN_0067aff0(l, 0x6a610e, local) == 0) {
                int v = FUN_0065bcf0(2, 1);
                r = (uint64_t)(v == 1);
            } else {
                r = 1;
            }
        } else {
            r = 0;
        }
    }
    return r;
}

/* FUN_0065be40 @ 0x0065be40   (est. sk_notif_state_check)
 * Ghidra: void FUN_0065be40(void)
 * Reads per-cpu base +0x108; if zero, panics (msg 0x6a6110, noreturn) via
 * FUN_0065c2f0. Bounds-checks before returning.
 * Confidence: medium */
static void sk_notif_state_check(void)
{
    long base = FUN_00655848();
    uint64_t v = *(uint64_t *)(base + 0x108);
    if (v == 0) {
        uint64_t ctx = FUN_00661318();
        FUN_0065c2f0(ctx, 0x6a6110);   /* noreturn */
    }
    if (v <= v + 0x30) {
        return;
    }
    /* bounds violated */
    SoftwareBreakpoint(0x5519, 0x65be70);
}

/* FUN_0065be80 @ 0x0065be80   (est. sk_notif_state_get)
 * Ghidra: undefined8 FUN_0065be80(void)
 * Returns per-cpu base +0x108.
 * Confidence: medium */
static uint64_t sk_notif_state_get(void)
{
    long base = FUN_00655848();
    return *(uint64_t *)(base + 0x108);
}

/* FUN_0065bcf0 @ 0x0065bcf0   (est. sk_cfg_bit_test)
 * Ghidra: undefined4 FUN_0065bcf0(ulong param_1, uint param_2)
 * Looks up string/array 0x6a60cc (FUN_006661e0); returns 0 if missing; if the
 * byte at index param_1 is out of range panics; returns 1 if its bit
 * (param_2 mod 32) is set else 2.
 * Confidence: medium */
static uint32_t sk_cfg_bit_test(uint64_t idx, uint32_t bit)
{
    uint64_t len = 0;
    long base = FUN_006661e0(0x6a60cc, &len);
    if (base == 0) {
        return 0;
    }
    if (len < (idx & 0xffffffff)) {
        uint64_t ctx = FUN_00661318();
        FUN_0065c2f0(ctx, 0x6a60da);   /* noreturn */
    }
    char *p = (char *)(base + (idx & 0xffffffff));
    if ((char *)(base + len) <= p) {
        SoftwareBreakpoint(0x5519, 0x65bd78);
    }
    uint32_t r = 1;
    if ((((uint32_t)(int)*p >> (bit & 0x1f)) & 1) == 0) {
        r = 2;
    }
    return r;
}

/* FUN_0065c2f0 @ 0x0065c2f0   (est. sk_panic2)
 * Ghidra: void FUN_0065c2f0(undefined8 param_1, undefined8 param_2)
 * Noreturn: forwards to FUN_0065c310 with the current stack pointer.
 * Confidence: medium */
static void sk_panic2(uint64_t a, uint64_t b)
{
    FUN_0065c310(a, b, (uint64_t)(uintptr_t)&sk_thread_base);
}

/* FUN_0065cbbc @ 0x0065cbbc   (est. sk_list_push)
 * Ghidra: void FUN_0065cbbc(long *param_1)
 * Inserts the block referenced by *param_1 into the per-thread list anchored
 * at (tpidr_el0+0x10); loop until slot free. Panics on overflow.
 * Confidence: medium */
static void sk_list_push(long *node)
{
    long *slot;
    long tbase = (long)(uintptr_t)sk_thread_base();
    long **list = *(long ***)(tbase + 0x10);
    while (*node == 0) {
        slot = *list;
        *node = (long)slot;
        if (*list == slot) {
            *list = (long)node;
            return;
        }
    }
    FUN_00684820();   /* lock/overflow panic */
    SoftwareBreakpoint(0x5519, 0x65cc0c);
}

/* FUN_0065cda8 @ 0x0065cda8   (est. sk_notif_lookup)
 * Ghidra: void FUN_0065cda8(ulong *param_1, int param_2)
 * Walks the notification object's list (0x6fe638). If param_2==0, matches by
 * address range [plVar1[5], plVar1[5]+plVar1[6]) on *param_1 and rewrites
 * *param_1 -= plVar1[4]; if param_2!=0 matches tag (short at +0x40) against
 * (*param_1 >> 0x30) and masks to low 48 bits. Returns on match.
 * Confidence: medium */
static long sk_notif_lookup(uint64_t *key, int mode)
{
    long *node = (long *)sk_notif_list_ensure(&_DAT_006fe638, 1, 1);
    node = (long *)*node;
    while (1) {
        if (node == 0) {
            return 0;
        }
        if (mode == 0) {
            uint64_t k = *key;
            if ((uint64_t)node[5] <= k && (k - node[5]) < (uint64_t)node[6]) {
                k = k - node[4];
                *key = k;
                return (long)k;
            }
        } else if (*(int16_t *)(node + 8) == (int16_t)(*key >> 0x30)) {
            uint64_t k = *key & 0xffffffffffff;
            *key = k;
            return (long)k;
        }
        node = (long *)*node;
    }
}

/* FUN_0065ce40 @ 0x0065ce40   (est. sk_slot_init)
 * Ghidra: void FUN_0065ce40(long param_1)
 * If (param_1+8)..(param_1+0xc) in range, calls FUN_0065e454(param_1+8,
 * FUN_0065ce70) to install the notifier; else panics.
 * Confidence: medium */
static void sk_slot_init(uint64_t param_1)
{
    if (param_1 + 8U <= param_1 + 0xcU) {
        FUN_0065e454((void *)(param_1 + 8), (void *)&sk_slot_attach);
        return;
    }
    SoftwareBreakpoint(0x5519, 0x65ce70);
}

/* FUN_0065ce70 @ 0x0065ce70   (est. sk_slot_attach)
 * Ghidra: void FUN_0065ce70(ulong *param_1)
 * Links param_1 into the notification object's +0x28 slot list (0x6fe638).
 * Confidence: medium */
static void sk_slot_attach(uint64_t *param_1)
{
    uint64_t obj = sk_notif_list_ensure(&_DAT_006fe638, 1, 1);
    while (1) {
        uint64_t v = *(uint64_t *)(obj + 0x28);
        *param_1 = v;
        if (*(uint64_t *)(obj + 0x28) == v) {
            *(uint64_t *)(obj + 0x28) = (uint64_t)param_1;
            return;
        }
    }
}

/* FUN_0065d7b0 @ 0x0065d7b0   (est. sk_reg_dump_all)
 * Ghidra: void FUN_0065d7b0(void)
 * Iterates 4 register-dump slots starting at 0x6b5250 (stride 0x50) and
 * invokes FUN_0065d804 for indices 0..3.
 * Confidence: medium */
static void sk_reg_dump_all(void)
{
    uint64_t idx = 0;
    uint64_t base = 0x6b5250;
    do {
        if ((((uint32_t)idx - 1) & 0xff) < 3) {
            FUN_0065d804((uint32_t)idx & 0xff, base);
        }
        idx = idx + 1;
        base = base + 0x50;
    } while (idx != 4);
}

typedef struct { uint64_t obj; uint64_t *ops; } sk_ops_pair_t;

/* FUN_0065d714 @ 0x0065d714   (est. sk_alloc_bind)
 * Ghidra: long FUN_0065d714(undefined8 param_1)
 * Allocates via FUN_0066ad54; if non-null, fetches the {obj, ops} pair
 * (FUN_0064e07c) and calls ops[0] (bind) with (obj,param_1,alloc,alloc,0);
 * on a non-zero result frees the allocation and returns 0.
 * Confidence: medium */
static long sk_alloc_bind(uint64_t param_1)
{
    long alloc = FUN_0066ad54();
    if (alloc != 0) {
        sk_ops_pair_t ops = {0};
        uint64_t *ops_addr = (uint64_t *)(uintptr_t)FUN_0064e07c();
        ops.obj = ops_addr[0];
        ops.ops = (uint64_t *)ops_addr[1];
        long r2 = ((long (*)(uint64_t, uint64_t, long, long, int))ops.ops[0])
                        (ops.obj, param_1, alloc, alloc, 0);
        if (r2 != 0) {
            FUN_006860f4((void *)alloc);
            alloc = 0;
        }
    }
    return alloc;
}

/* FUN_0065d774 @ 0x0065d774   (est. sk_free_bind)
 * Ghidra: void FUN_0065d774(undefined8 param_1)
 * Fetches {obj, ops} via FUN_0064e07c, calls ops[2] (release) with
 * (obj, param_1), then frees param_1.
 * Confidence: medium */
static void sk_free_bind(uint64_t param_1)
{
    sk_ops_pair_t ops = {0};
    uint64_t *ops_addr = (uint64_t *)(uintptr_t)FUN_0064e07c();
    ops.obj = ops_addr[0];
    ops.ops = (uint64_t *)ops_addr[1];
    ((void (*)(uint64_t, uint64_t))ops.ops[2])(ops.obj, param_1);
    FUN_006860f4((void *)param_1);
}


/* ===================================================================== */
/* Remaining complex logic                                               */
/* ===================================================================== */

/* FUN_0065beb4 @ 0x0065beb4   (est. sk_io_ring_push)
 * Ghidra: void FUN_0065beb4(long param_1)
 * Append path into an I/O ring: if write pos (+0x48) < limit (+0x28), compute
 * a 5-byte (0x28) budget, grow via method at obj+0x38[3] (args obj+0x30, &len);
 * on low-byte error panics; advances +0x48/=64 and +0x50; releases LO.
 * Confidence: medium */
static void sk_io_ring_push(uint64_t ring)
{
    if (*(uint64_t *)(ring + 0x48) < *(uint64_t *)(ring + 0x28)) {
        uint64_t pos = *(uint64_t *)(ring + 0x50);
        uint64_t wp = *(uint64_t *)(ring + 0x48);
        if (wp >= pos && (wp - pos) == 0 && (wp - pos) + *(long *)(ring + 0x60) < 5) {
            if (wp > pos) wp = pos;
            uint64_t budget = wp + 5;
            if (*(uint64_t *)(ring + 0x28) <= wp + 5) {
                budget = *(uint64_t *)(ring + 0x28);
            }
            budget = budget << 6;
            uint64_t r = (**(uint64_t (**)(uint64_t, uint64_t *))(*(long *)(ring + 0x38) + 0x18))
                                (*(uint64_t *)(ring + 0x30), &budget);
            if ((r & 0xff) != 0) {
                uint64_t ctx = FUN_00661318();
                uint64_t err = (r & 0xff) * 8;
                uint64_t *tbl = (uint64_t *)(err + 0x6b5e50);
                if ((uint64_t *)0x6b5e4f < tbl && (uint64_t *)(0x6b5e58) + (err / 8) < (uint64_t *)0x6b5e91
                    && tbl <= (uint64_t *)(0x6b5e58) + (err / 8)) {
                    FUN_0065c2f0(ctx, 0x6a6374);   /* noreturn */
                }
                SoftwareBreakpoint(0x5519, 0x65bfa8);
            }
            *(uint64_t *)(ring + 0x48) = budget >> 6;
            *(long *)(ring + 0x50) += 0;   /* in_xzr = 0 */
            LORelease();
        }
    }
}

/* FUN_0065bfa8 @ 0x0065bfa8   (est. sk_objtype_release_all)
 * Ghidra: void FUN_0065bfa8(undefined8 param_1, long param_2, undefined8 param_3, int param_4)
 * Under a stack canary, saves state (FUN_00662630) and logs 0x6a63a2. If
 * param_4 and the object at param_2+0x38 is non-zero, iterates the list at
 * param_2+0x10 releasing each entry (FUN_00655e1c) and logging 0x6a63b9.
 * Checks canary before returning (FUN_0067f660 on mismatch).
 * Confidence: medium */
static void sk_objtype_release_all(uint64_t a, uint64_t obj, uint64_t b, int flag)
{
    long canary = _DAT_006b5ed0;
    FUN_00662630((void *)a, (void *)&b);
    FUN_0067d72c(0x6a63a2);
    if (flag != 0 && *(long *)(obj + 0x38) != 0) {
        uint64_t i = 0;
        long *it = (long *)(obj + 0x10);
        while (i < *(uint64_t *)(obj + 0x38)) {
            long entry = *it;
            uint64_t key = (uint64_t)entry;
            sk_notif_lookup(&key, 1);
            if ((long)key == 0) break;
            uint64_t local = 0;
            FUN_00655e1c((void *)*it, &local);
            FUN_0067d72c(0x6a63b9);
            i = i + 1;
            it = it + 1;
        }
    }
    if (_DAT_006b5ed0 == canary) {
        return;
    }
    FUN_0067f660();
}

/* FUN_0065c144 @ 0x0065c144   (est. sk_notif_send)
 * Ghidra: void FUN_0065c144(long param_1, undefined8 param_2, undefined8 param_3)
 * If the flag byte at 0x6fc590 != 2 or FUN_00683f74 succeeds, increments
 * param_1+0x58 (pending count).
 * Confidence: medium */
static void sk_notif_send(uint64_t obj, uint64_t a, uint64_t b)
{
    char *flag = (char *)sk_notif_list_ensure(&_DAT_006fc590, 1, 3);
    if (*flag != '\x02' || (FUN_00683f74((void *)obj, (void *)b, (void *)a) & 1) != 0) {
        *(long *)(obj + 0x58) = *(long *)(obj + 0x58) + 1;
    }
}

/* FUN_0065c1b8 @ 0x0065c1b8   (est. sk_notif_cancel)
 * Ghidra: void FUN_0065c1b8(long param_1, undefined8 param_2)
 * If flag byte at 0x6fc590 == 2, cancels via FUN_00684150; decrements
 * param_1+0x58.
 * Confidence: medium */
static void sk_notif_cancel(uint64_t obj, uint64_t a)
{
    char *flag = (char *)sk_notif_list_ensure(&_DAT_006fc590, 1, 3);
    if (*flag == '\x02') {
        FUN_00684150((void *)obj, (void *)a);
    }
    *(long *)(obj + 0x58) = *(long *)(obj + 0x58) + -1;
}

/* FUN_0065c218 @ 0x0065c218   (est. sk_notif_cleanup)
 * Ghidra: void FUN_0065c218(long param_1)
 * If flag byte at 0x6fc590 == 2, cleans up via FUN_00684388; if pending count
 * (param_1+0x58) is non-zero, panics (msg 0x6a634a).
 * Confidence: medium */
static void sk_notif_cleanup(uint64_t obj)
{
    char *flag = (char *)sk_notif_list_ensure(&_DAT_006fc590, 1, 3);
    if (*flag == '\x02') {
        FUN_00684388((void *)obj);
    }
    if (*(long *)(obj + 0x58) == 0) {
        return;
    }
    FUN_0065c2f0(0, 0x6a634a);   /* noreturn */
}
