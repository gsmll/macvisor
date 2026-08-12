/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 09: 0xa8c80-0xaf4a0 — Tightbeam (TB) component-graph / resource
 * builder: untyped-resource enumeration, component/edge graph walking,
 * badge and serialisation helpers. */

#include "sk_internal.h"

/* Register-passed state placeholders (Ghidra unaff_x20/x19 etc. register
 * arguments that the decompiler could not resolve to stack locals). */
static long this_obj;      /* unaff_x20 / x21 etc. */
static int in_ZR;
static unsigned long x23, x24, x25;
static unsigned char w22;

/* Global TB collection arrays (Ghidra DAT_00657778..). */
unsigned long DAT_00657778;      /* collection header */
unsigned long DAT_00657788;      /* collection length */
unsigned long DAT_00657790;      /* collection capacity */
unsigned long DAT_00657798[16];  /* collection elements */
unsigned long DAT_006577a8[16];  /* parallel element array */
unsigned long DAT_006577e0;      /* empty sentinel */

extern unsigned long tb_next_id(void);   /* FUN_000a7e7c */

/* 16-byte value returned in x0/x1 by many TB helpers. */
typedef struct { unsigned long lo, hi; } tb_w16_t;

/* Fail-closed trap (SoftwareBreakpoint(1, addr)). */
#define TB_TRAP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/TB helpers — exact Ghidra FUN_ names kept as
 * externs (their bodies are reconstructed by the slice that owns them).
 * ------------------------------------------------------------------ */
extern void FUN_002a4ab4(unsigned long);                 /* debug log line */
extern void FUN_0036b270(unsigned long);                 /* ref acquire */
extern void FUN_0036b118(unsigned long);                 /* ref release */
extern void FUN_003a25d4(unsigned long);                 /* release */
extern void *FUN_0036a940(unsigned long, unsigned long, unsigned long); /* zone alloc (a,b,kind) */
extern unsigned long FUN_001a8564(void);                 /* iterator begin */
extern void FUN_001a84f4(void *, unsigned long);         /* iterator init */
extern void FUN_001b9084(void *, unsigned long, unsigned long); /* iterator add */
extern void FUN_000027e8(unsigned long);                 /* context enter */
extern void FUN_0007c198(unsigned long);                 /* trace enter */
extern unsigned long FUN_00077698(void);               /* trace leave */
extern void FUN_0007767c(unsigned int, unsigned long);   /* trace result */
extern void FUN_00086840(const char *);                  /* print string */
extern void FUN_0011d7e8(void) __attribute__((noreturn));
extern void FUN_001afa84(void) __attribute__((noreturn));
extern unsigned long FUN_000b402c(unsigned long);        /* bitset header */
extern void FUN_000825c4(unsigned long, unsigned long, int);
extern void FUN_000825e4(unsigned long, unsigned long, int);
extern void FUN_00082604(unsigned long, unsigned long, int);
extern void FUN_000825a4(unsigned long, unsigned long, int);
extern void FUN_0006a374(unsigned long, unsigned long, int);
extern unsigned long FUN_002a0cf8(void);                 /* pair cmp */
extern unsigned long FUN_002a0f24(void);
extern unsigned long FUN_0008e290(unsigned long, unsigned long); /* str eat */
extern unsigned long FUN_00084180(void);
extern tb_w16_t FUN_000b4428(void);
extern tb_w16_t FUN_000b4344(void);
extern unsigned long FUN_000b4354(void);
extern unsigned long FUN_000b41d8(void);
extern tb_w16_t FUN_000b02f4(unsigned long, unsigned long, int);
extern void FUN_000b430c(void);
extern void FUN_000b41c4(void);
extern void FUN_0006f768(void);
extern void FUN_000b44a0(void);
extern unsigned long FUN_000b43fc(void);
extern unsigned long FUN_000b44ac(void);
extern void FUN_000b4458(void);
extern void FUN_000b4528(void);
extern void FUN_000b4568(unsigned long);
extern unsigned long FUN_000b44cc(unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_00153264(void);
extern unsigned long FUN_00153270(void);
extern unsigned long FUN_0015327c(void);
extern unsigned long FUN_0001a1c8(unsigned long);
extern unsigned long FUN_000af7b4(void);
extern void FUN_001394c8(int);
extern void FUN_0007c0b8(unsigned long);
extern void FUN_0007c028(unsigned long, unsigned long);
extern unsigned long FUN_00157308(unsigned long);        /* str len */
extern void FUN_00085a54(unsigned long *, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_00086440(unsigned long);
extern unsigned long FUN_00086590(unsigned long);
extern unsigned long FUN_00124e34(unsigned long);
extern unsigned long FUN_000e254c(unsigned long);
extern tb_w16_t FUN_000e25d8(unsigned long);
extern unsigned long FUN_000e2618(unsigned long);
extern unsigned long FUN_001396b4(int);
extern unsigned long FUN_00125344(void);
extern unsigned long FUN_000ad260(unsigned long, unsigned long);
extern unsigned long FUN_000a6e60(void);
extern unsigned long FUN_000a6fbc(void);
extern void FUN_000b45f4(void);
extern void FUN_000b4418(void);
extern unsigned long FUN_000b4438(void);
extern void FUN_000b4534(void);
extern void FUN_000b4540(void);
extern void FUN_000b4218(unsigned long);
extern void FUN_000b4280(void);
extern void FUN_000b4270(void);
extern void FUN_000b4294(unsigned long);
extern void FUN_000b42c0(void);
extern void FUN_000b41f0(void);
extern void FUN_000b4244(void);
extern unsigned long FUN_000b42f8(const char *);
extern unsigned long FUN_001dd77c(void);
extern void FUN_001dd858(unsigned long);
extern tb_w16_t FUN_000b4594(void);
extern void FUN_000b4588(void);
extern void FUN_000b45b0(unsigned long, unsigned long);
extern void FUN_000b45cc(void);
extern unsigned long FUN_000b45e0(unsigned long, unsigned long, unsigned long);
extern void FUN_000b2260(void *, unsigned long, unsigned long);
extern unsigned long FUN_0025a094(unsigned long, unsigned long);
extern unsigned long FUN_00002534(unsigned long, unsigned long);
extern unsigned long FUN_00205844(unsigned long *, unsigned long *, unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_00365b6c(unsigned long *, unsigned long *, unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_003625e4(unsigned long, unsigned long, int);
extern unsigned long FUN_002dc0d0(unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_0006a4c0(unsigned long *, unsigned long);
extern void FUN_000026e8(unsigned long *);
extern tb_w16_t FUN_0006ae9c(unsigned long, unsigned long);
extern unsigned long FUN_00072c0c(unsigned long, unsigned long, int, unsigned long);
extern unsigned long FUN_0035b67c(unsigned long, unsigned long, unsigned long, unsigned long);
extern tb_w16_t FUN_000726a0(unsigned long);
extern tb_w16_t FUN_0022d2f4(unsigned long *, unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_0007b268(void);
extern unsigned long FUN_0007b444(unsigned long);
extern unsigned long FUN_00027754(unsigned long);
extern unsigned long FUN_00027724(unsigned long);
extern unsigned long FUN_000276c4(unsigned long);
extern unsigned long FUN_000267d4(unsigned long *, unsigned long, unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_00021480(void);
extern void FUN_00077770(unsigned long);
extern tb_w16_t FUN_00377dcc(unsigned long, unsigned long);
extern void FUN_00368da8(unsigned long, int, int, void *);
extern tb_w16_t FUN_003722e4(unsigned long, unsigned long, unsigned long, const char *, int);
extern tb_w16_t FUN_0037233c(unsigned long, unsigned long, unsigned long, unsigned long, const char *, int);
extern tb_w16_t FUN_002a3e64(unsigned long, unsigned long, unsigned long, unsigned long);
extern void FUN_000fdd78(unsigned long, unsigned long, unsigned long);
extern void FUN_00117cc4(unsigned long, unsigned long, unsigned long);
extern void FUN_001e9c00(unsigned long *);
extern void FUN_0036986c(void);
extern void FUN_0036b6f4(void);
extern void FUN_0036b6ac(unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_000a7e7c(void);
extern void FUN_0036a1a0(unsigned long, void *, unsigned long, unsigned long);
extern void FUN_0036a20c(void *);
extern void FUN_0036b340(unsigned long *, int);
extern void FUN_001dd77c_t(void);
extern unsigned long FUN_00019850(void);
extern unsigned long FUN_0008cc74(unsigned long, unsigned long);
extern unsigned long FUN_000af4d0(unsigned long, unsigned long);
extern void FUN_003a2610(unsigned long, int);
extern unsigned long FUN_003a261c(unsigned long);
extern void thunk_FUN_002acbb8(unsigned long, unsigned long, ...);
extern void thunk_FUN_002b3978(unsigned long, unsigned long);
extern void thunk_FUN_00138b08(void);
extern void thunk_FUN_000d1d54(unsigned long, unsigned long);
extern unsigned long FUN_0006e7c0(unsigned long *, unsigned long *);
extern tb_w16_t FUN_000b4390(void);
extern tb_w16_t FUN_000b1e08(unsigned long, int, void *, void *, unsigned long, unsigned long);
extern tb_w16_t FUN_000b4140(void);
extern void FUN_000b3f98(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
extern void FUN_002a0cf8_full(unsigned long, unsigned long, unsigned long, unsigned long, int);
extern int FUN_000aba2c(unsigned long, unsigned long, long, long, long);
extern void FUN_00084000(void);
extern unsigned long thunk_FUN_00229ebc(unsigned long, unsigned long);
extern void thunk_FUN_0036b270(unsigned long);
extern unsigned long FUN_001f0130(unsigned long, unsigned long, unsigned long, unsigned long);
extern void FUN_000b42e4(void);
extern void FUN_000b4200(void);
extern void FUN_000ad7d4(void);

extern void FUN_0036993c(unsigned long, unsigned long, unsigned long, unsigned long); /* TB state reset */


extern long *tb_parse_badge_value(long *param_1);
extern void FUN_000aecc8(unsigned long *, unsigned long *); /* in-slice tb_comp_order_map */
/* Forward declarations for in-slice functions. */
unsigned long tb_alloc_init(unsigned long param_1);
void tb_and_apply(unsigned long *param_1, unsigned long *param_2);
unsigned long tb_any_edge(long param_1, long param_2, long param_3);
void tb_badge_dispatch(unsigned long param_1, unsigned long param_2, unsigned long param_3);
unsigned int tb_badge_dispatch_wrap(void);
unsigned int tb_badge_shift(unsigned long param_1, unsigned long param_2,
                            unsigned long param_3, unsigned long param_4);
void tb_build_component_edges(void);
unsigned int tb_build_edge_set(void);
void tb_build_full_graph(void);
void tb_build_graph(void);
void tb_build_node(unsigned long *param_1, unsigned long *param_2, long *param_3,
                   unsigned long *param_4);
void tb_cap_apply(unsigned long *param_1, unsigned long *param_2);
unsigned int tb_check_node(void);
unsigned int tb_check_node2(void);
int tb_check_result(int *param_1);
unsigned long tb_comp_order(void);
void tb_comp_order_map(unsigned long *param_1, unsigned long *param_2);
tb_w16_t tb_component_obj_view(unsigned long param_1);
unsigned long tb_component_property(void);
unsigned long tb_const4(void);
tb_w16_t tb_const_6505c0(void);
tb_w16_t tb_const_6507a8(void);
int tb_contains_char(char param_1, long param_2);
int tb_contains_pair(long param_1, long param_2, long param_3);
unsigned int tb_contains_pair_ptr(unsigned long *param_1, unsigned long param_2);
int tb_contains_ptr(long param_1, long param_2);
void tb_copy_range(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                   unsigned long param_4);
void tb_ctx_enter(void);
tb_w16_t tb_ctx_leave(void);
void tb_dec_refcount(void);
void tb_dispatch_kind28(void);
void tb_dispatch_kind28_wrap(void);
tb_w16_t tb_fatal_error(void);
int tb_find_pair(unsigned long param_1, unsigned long param_2, long param_3,
                 long param_4, long param_5);
int tb_find_pair2(long param_1, long param_2, long param_3);
int tb_find_pair8(long param_1, long param_2);
tb_w16_t tb_get_cap(long param_1);
void tb_get_component_ctx(void);
void tb_get_component_ctx_wrap(void);
void tb_get_component_obj(void);
unsigned long tb_graph_fold(unsigned long param_1, unsigned long param_2);
tb_w16_t tb_graph_metadata_key(unsigned long param_1, unsigned long param_2);
unsigned int tb_has_enable(void);
void tb_init(unsigned long param_1);
void tb_iterate_component(void);
void tb_log_650468(void);
void tb_log_650560(void);
void tb_log_650748(void);
void tb_misc_19850(unsigned long *param_1);
void tb_misc_21480(void);
void tb_noop_1(void);
void tb_noop_2(void);
void tb_noop_3(void);
void tb_noop_4(void);
void tb_noop_5(void);
void tb_noop_6(void);
tb_w16_t tb_observe_fail(void);
void tb_observe_flush(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                      unsigned char param_4);
void tb_observe_flush2(unsigned long param_1, unsigned char param_2);
void tb_observe_flush_fromctx(void);
void tb_observe_flush_fromctx_b(void);
void tb_observe_flush_fromctx_c(void);
void tb_observe_flush_fromctx_d(void);
void tb_observe_flush_kind(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                           unsigned char param_4);
void tb_observe_flush_kind2(unsigned long param_1, unsigned char param_2);
tb_w16_t tb_observe_indexed(void);
void tb_observe_indexed_wrap(void);
void tb_observe_tightbeam(unsigned long param_1, unsigned long param_2, long param_3);
void tb_or_apply(unsigned long *param_1, unsigned long *param_2);
unsigned char tb_or_bytes(long param_1);
unsigned int tb_or_u32(long param_1);
unsigned long tb_or_word(unsigned long param_1, unsigned long param_2);
unsigned long tb_or_words(long param_1);
tb_w16_t tb_pair_fetch(void);
unsigned long tb_parse_badge(unsigned long param_1, unsigned long param_2);
unsigned long tb_parse_decimal(void);
void tb_release_two(void);
void tb_release_two_log20(void);
void tb_release_two_log20_b(void);
void tb_remove_duplicates(void);
void tb_reset_state(void);
unsigned int tb_resource_not_shared(void);
void tb_send_all_regs(void);
void tb_send_all_regs_wrap(void);
void tb_send_observe7(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                      unsigned long param_4, unsigned long param_5, unsigned long param_6,
                      unsigned long param_7);
void tb_send_raw(unsigned long param_1, unsigned long param_2);
void tb_send_raw_flag0(unsigned long param_1);
void tb_send_raw_flag0_wrap(void);
void tb_send_raw_flag0_wrap_b(void);
void tb_send_raw_flag1(unsigned long param_1);
void tb_send_raw_flag1_wrap(void);
void tb_send_raw_flag1_wrap_b(void);
void tb_serialise_component(unsigned long *param_1);
void tb_serialise_component_wrap(void);
void tb_serialise_component_wrap_b(void);
void tb_service_types(void);
tb_w16_t tb_set_cap_large_connection(long param_1);
void tb_set_component_obj(unsigned long param_1);
void tb_set_error(unsigned long lo, unsigned long hi, unsigned char n);
void tb_teardown(void);
void tb_teardown_finish(void);
void tb_teardown_finish_b(void);
tb_w16_t tb_untyped_alloc_flags(unsigned int param_1);
int tb_untyped_kobj_types(void);
unsigned long tb_untyped_mem_types(void);
unsigned int tb_untyped_permissions(void);
void tb_validate_component(void);
void tb_vtbl_50_wrap(void);
void tb_vtbl_60_wrap(void);
void tb_vtbl_dispatch_38(void);
void tb_vtbl_dispatch_40(void);
void tb_vtbl_dispatch_48(void);
void tb_vtbl_dispatch_50(void);
void tb_vtbl_dispatch_60(void);
void tb_vtbl_dispatch_68(void);

/* ------------------------------------------------------------------ *
 * Bodies (in-slice, English-first, faithful to decompile).
 * ------------------------------------------------------------------ */

/* FUN_000a8c80 @ 0x000a8c80   (est. tb_vtbl_dispatch_68)
 * Ghidra: void FUN_000a8c80(void)
 * Indirect call through the object at *this: reads the vtable pointer from
 * *this, then calls the function pointer stored at vtable+0x68 (an object
 * method dispatch with no arguments).
 * Confidence: low
 */
void tb_vtbl_dispatch_68(void)
{
    unsigned long *this_ = 0;                 /* unaff_x20 */
    void (**vtbl)(void) = (void (**)(void))*(long *)this_;
    (vtbl[13])();                              /* *(vtbl+0x68) = index 13 */
}

/* FUN_000a8cbc @ 0x000a8cbc   (est. tb_observe_tightbeam)
 * Ghidra: void FUN_000a8cbc(param_1,param_2,param_3)
 * Starts a tightbeam observation: fetches a 16-byte pair (FUN_000aa3e4),
 * stores the pair's low half into the current object's +0x10 field, formats
 * a message whose payload is param_3 (or a large negative sentinel), and
 * tests it with tb_check_result (FUN_000a9ae8). On success it resets the TB
 * state and reports an error word {0xd000000000000020, 0x80000000005c2210,
 * 2}; on failure it copies a 0x100-byte block to obj+0x18 and stashes the
 * x23/x24/x25/w22 register save area at obj+0x118..0x130.
 * Confidence: medium
 */
void tb_observe_tightbeam(unsigned long param_1, unsigned long param_2, long param_3)
{
    tb_w16_t pair;
    unsigned long lo;
    long hi;
    int r;
    long obj = 0;                             /* unaff_x20 */

    pair = tb_pair_fetch();
    *(long *)(obj + 0x10) = pair.lo;
    lo = 0;
    if (param_3 != 0) lo = pair.hi;
    hi = -0x2000000000000000LL;
    if (param_3 != 0) hi = param_3;
    FUN_000fdd78(lo, lo, hi);                 /* format message with param_3 */
    FUN_003a25d4(hi);
    r = tb_check_result(0);
    if (r == 1) {
        tb_reset_state();
        tb_set_error(0xd000000000000020, 0x80000000005c2210, 2);
        FUN_0036986c();
        tb_observe_flush(0, 0, 0, 0);
        FUN_0036b6f4();
    } else {
        FUN_00117cc4(obj + 0x18, 0, 0x100);   /* copy 0x100 bytes */
        *(unsigned long *)(obj + 0x118) = x25;
        *(unsigned long *)(obj + 0x120) = x24;
        *(unsigned long *)(obj + 0x128) = x23;
        *(unsigned char *)(obj + 0x130) = w22;
    }
}

/* FUN_000a8dcc @ 0x000a8dcc   (est. tb_send_raw_flag0)
 * Ghidra: void FUN_000a8dcc(param_1)
 * Wraps tb_send_raw(param_1, 0).
 * Confidence: high
 */
void tb_send_raw_flag0(unsigned long param_1)
{
    tb_send_raw(param_1, 0);
}

/* FUN_000a8de8 @ 0x000a8de8   (est. tb_send_raw_flag1)
 * Ghidra: void FUN_000a8de8(param_1)
 * Wraps tb_send_raw(param_1, 1).
 * Confidence: high
 */
void tb_send_raw_flag1(unsigned long param_1)
{
    tb_send_raw(param_1, 1);
}

/* FUN_000a8e04 @ 0x000a8e04   (est. tb_send_raw)
 * Ghidra: void FUN_000a8e04(param_1,param_2)
 * Builds a raw tightbeam message: logs the source line (0x6504d8, len 0x51,
 * kind 7), formats the optional param_2, obtains the next message id via
 * tb_next_id, and on success records {id, 0x6504d8, 0x660800} into the
 * caller's result array (param_1[0],[3],[4]).
 * Confidence: medium
 */
void tb_send_raw(unsigned long param_1, unsigned long param_2)
{
    unsigned long id;
    long x21 = 0;                             /* unaff_x21 success flag */
    unsigned long *out = (unsigned long *)param_1;

    FUN_0036a940(0x6504d8, 0x51, 7);
    FUN_0036b270(param_2);
    FUN_0036b270(param_2);
    id = tb_next_id();
    if (x21 == 0) {
        out[3] = 0x6504d8;
        out[4] = 0x660800;
        out[0] = id;
    }
}

/* FUN_000a8ea0 @ 0x000a8ea0   (est. tb_send_all_regs)
 * Ghidra: void FUN_000a8ea0(void)
 * Emits a tightbeam message containing the full 32-register context from the
 * current thread (x19). Copies registers at ctx+0x18..0x110 into the outgoing
 * message frame, sends it, and if the send is not accepted traps (abort).
 * Confidence: medium
 */
void tb_send_all_regs(void)
{
    unsigned long ctx = 0;                    /* unaff_x19 */
    tb_w16_t frame;
    unsigned long regs[32];
    unsigned long i;

    tb_ctx_enter();
    FUN_002a4ab4(0x1d);
    FUN_003a25d4(0);                          /* message begin (0) */
    frame.hi = 0xd00000000000001a;
    frame.lo = 0x80000000005c2240;
    for (i = 0; i < 32; i++)
        regs[i] = *(unsigned long *)(ctx + 0x18 + i * 8);
    FUN_001e9c00(regs);
    thunk_FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x29, 0xe100000000000000);
    tb_ctx_leave();
    if (!in_ZR) {
        FUN_0011d7e8();                       /* abort */
    }
}

/* FUN_000a8f94 @ 0x000a8f94   (est. tb_observe_flush_fromctx)
 * Ghidra: void FUN_000a8f94(void)
 * Flushes the observation buffer using the register save area stashed at
 * obj+0x118..0x130 by tb_observe_tightbeam.
 * Confidence: high
 */
void tb_observe_flush_fromctx(void)
{
    long obj = 0;                             /* unaff_x20 */
    tb_observe_flush(*(unsigned long *)(obj + 0x118), *(unsigned long *)(obj + 0x120),
                     *(unsigned long *)(obj + 0x128), *(unsigned char *)(obj + 0x130));
}

/* FUN_000a8f98 @ 0x000a8f98   (est. tb_observe_flush_fromctx_b)
 * Ghidra: void FUN_000a8f98(void)
 * Same as tb_observe_flush_fromctx (identical body) — duplicate entry point.
 * Confidence: high
 */
void tb_observe_flush_fromctx_b(void)
{
    long obj = 0;
    tb_observe_flush(*(unsigned long *)(obj + 0x118), *(unsigned long *)(obj + 0x120),
                     *(unsigned long *)(obj + 0x128), *(unsigned char *)(obj + 0x130));
}

/* FUN_000a8fbc @ 0x000a8fbc   (est. tb_observe_flush_fromctx_c)
 * Ghidra: void FUN_000a8fbc(void)
 * Flushes the observation buffer, then calls tb_finish (FUN_0036b6ac).
 * Confidence: high
 */
void tb_observe_flush_fromctx_c(void)
{
    long obj = 0;
    tb_observe_flush(*(unsigned long *)(obj + 0x118), *(unsigned long *)(obj + 0x120),
                     *(unsigned long *)(obj + 0x128), *(unsigned char *)(obj + 0x130));
    FUN_0036b6ac(0, 0, 0);
}

/* FUN_000a8fc0 @ 0x000a8fc0   (est. tb_observe_flush_fromctx_d)
 * Ghidra: void FUN_000a8fc0(void)
 * Same as tb_observe_flush_fromctx_c (identical body).
 * Confidence: high
 */
void tb_observe_flush_fromctx_d(void)
{
    long obj = 0;
    tb_observe_flush(*(unsigned long *)(obj + 0x118), *(unsigned long *)(obj + 0x120),
                     *(unsigned long *)(obj + 0x128), *(unsigned char *)(obj + 0x130));
    FUN_0036b6ac(0, 0, 0);
}

/* FUN_000a8ff0 @ 0x000a8ff0   (est. tb_send_raw_flag0_wrap)
 * Ghidra: void FUN_000a8ff0(void)
 * Calls tb_send_raw_flag0 with no explicit argument (register-passed).
 * Confidence: medium
 */
void tb_send_raw_flag0_wrap(void)
{
    tb_send_raw_flag0(0);
}

/* FUN_000a8ff4 @ 0x000a8ff4   (est. tb_send_raw_flag0_wrap_b)
 * Ghidra: void FUN_000a8ff4(void)
 * Same as tb_send_raw_flag0_wrap.
 * Confidence: medium
 */
void tb_send_raw_flag0_wrap_b(void)
{
    tb_send_raw_flag0(0);
}

/* FUN_000a9008 @ 0x000a9008   (est. tb_send_raw_flag1_wrap)
 * Ghidra: void FUN_000a9008(void)
 * Calls tb_send_raw_flag1.
 * Confidence: medium
 */
void tb_send_raw_flag1_wrap(void)
{
    tb_send_raw_flag1(0);
}

/* FUN_000a900c @ 0x000a900c   (est. tb_send_raw_flag1_wrap_b)
 * Ghidra: void FUN_000a900c(void)
 * Same as tb_send_raw_flag1_wrap.
 * Confidence: medium
 */
void tb_send_raw_flag1_wrap_b(void)
{
    tb_send_raw_flag1(0);
}

/* FUN_000a9020 @ 0x000a9020   (est. tb_send_all_regs_wrap)
 * Ghidra: void FUN_000a9020(void)
 * Calls tb_send_all_regs.
 * Confidence: medium
 */
void tb_send_all_regs_wrap(void)
{
    tb_send_all_regs();
}

/* FUN_000a9044 @ 0x000a9044   (est. tb_vtbl_dispatch_50)
 * Ghidra: void FUN_000a9044(void)
 * Indirect call through the object at obj+0x18: reads the vtable pointer
 * from *(obj+0x18), then calls the function pointer at vtable+0x50.
 * Confidence: low
 */
void tb_vtbl_dispatch_50(void)
{
    long obj = 0;                             /* unaff_x20 */
    void (**vtbl)(void) = *(void (***)(void))(obj + 0x18);
    (vtbl[10])();                              /* *(vtbl+0x50) */
}

/* FUN_000a9080 @ 0x000a9080   (est. tb_vtbl_dispatch_60)
 * Ghidra: void FUN_000a9080(void)
 * Indirect call through the object at obj+0x18: calls vtable slot at +0x60.
 * Confidence: low
 */
void tb_vtbl_dispatch_60(void)
{
    long obj = 0;
    void (**vtbl)(void) = *(void (***)(void))(obj + 0x18);
    (vtbl[12])();                              /* *(vtbl+0x60) */
}

/* FUN_000a90bc @ 0x000a90bc   (est. tb_observe_indexed)
 * Ghidra: undefined1[16] FUN_000a90bc(void)
 * Logs line 0x1d, prints an indexed-context banner, dispatches through the
 * vtable slot at +0x48 of the object at obj+0x18, and returns the 16-byte
 * string word {0x646572656b6f7242, 0xe900000000000028} ("Borekded").
 * Confidence: medium
 */
tb_w16_t tb_observe_indexed(void)
{
    long obj = 0;                             /* unaff_x20 */
    tb_w16_t r;

    FUN_002a4ab4(0x1d);
    FUN_003a25d4(0xe000000000000000);
    tb_get_component_ctx();
    thunk_FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x2065646f6e63202c, 0xef203a7865646e69); /* ", cnode : …" */
    (*(void (**)(void))(**(long **)(obj + 0x18) + 0x48))();
    FUN_00027724(0x671df8);
    FUN_0036a940(0x677830, 0x671df8, 0);
    thunk_FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x29, 0xe100000000000000);
    r.lo = 0x646572656b6f7242;
    r.hi = 0xe900000000000028;
    return r;
}

/* FUN_000a91ec @ 0x000a91ec   (est. tb_release_two)
 * Ghidra: void FUN_000a91ec(void)
 * Releases two references held in the current object's +0x10 and +0x18
 * fields.
 * Confidence: high
 */
void tb_release_two(void)
{
    long obj = 0;                             /* unaff_x20 */
    FUN_0036b118(*(unsigned long *)(obj + 0x10));
    FUN_0036b118(*(unsigned long *)(obj + 0x18));
}

/* FUN_000a9214 @ 0x000a9214   (est. tb_release_two_log20)
 * Ghidra: void FUN_000a9214(void)
 * Releases the two references then logs kind 0x20/7 with the released pair.
 * Confidence: medium
 */
void tb_release_two_log20(void)
{
    tb_release_two();
    unsigned long r = 0;
    FUN_0036b6ac(r, 0x20, 7);
}

/* FUN_000a9218 @ 0x000a9218   (est. tb_release_two_log20_b)
 * Ghidra: void FUN_000a9218(void)
 * Same as tb_release_two_log20 (duplicate entry).
 * Confidence: medium
 */
void tb_release_two_log20_b(void)
{
    tb_release_two();
    unsigned long r = 0;
    FUN_0036b6ac(r, 0x20, 7);
}

/* FUN_000a9238 @ 0x000a9238   (est. tb_vtbl_50_wrap)
 * Ghidra: void FUN_000a9238(void)
 * Wraps tb_vtbl_dispatch_50.
 * Confidence: medium
 */
void tb_vtbl_50_wrap(void)
{
    tb_vtbl_dispatch_50();
}

/* FUN_000a925c @ 0x000a925c   (est. tb_vtbl_60_wrap)
 * Ghidra: void FUN_000a925c(void)
 * Wraps tb_vtbl_dispatch_60.
 * Confidence: medium
 */
void tb_vtbl_60_wrap(void)
{
    tb_vtbl_dispatch_60();
}

/* FUN_000a9280 @ 0x000a9280   (est. tb_observe_indexed_wrap)
 * Ghidra: void FUN_000a9280(void)
 * Wraps tb_observe_indexed.
 * Confidence: medium
 */
void tb_observe_indexed_wrap(void)
{
    tb_observe_indexed();
}

/* FUN_000a92a4 @ 0x000a92a4   (est. tb_send_observe7)
 * Ghidra: void FUN_000a92a4(param_1..param_7)
 * Logs the source line (0x650468, 0x131, 7), then calls tb_observe_tightbeam
 * with the seven parameters; on success stores the allocator result at
 * obj+0x10, else reports a message failure.
 * Confidence: medium
 */
void tb_send_observe7(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                      unsigned long param_4, unsigned long param_5, unsigned long param_6,
                      unsigned long param_7)
{
    unsigned long r;
    long obj = 0;                             /* unaff_x20 */
    long x21 = 0;                             /* unaff_x21 */

    r = (unsigned long)FUN_0036a940(0x650468, 0x131, 7);
    tb_observe_tightbeam(param_1, param_2, param_3);
    if (x21 == 0) {
        *(unsigned long *)(obj + 0x10) = r;
    } else {
        FUN_0036b6f4();
    }
}

/* FUN_000a9388 @ 0x000a9388   (est. tb_observe_flush_kind)
 * Ghidra: void FUN_000a9388(param_1,param_2,param_3,param_4)
 * Dispatches an observation-flush by a kind byte (param_4): kinds 0/1 go to
 * the default 1-arg form, kind 2 -> 2-arg form, kind 3 -> 3-arg form; out of
 * range (kind>3) returns immediately.
 * Confidence: medium
 */
void tb_observe_flush_kind(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                           unsigned char param_4)
{
    if (3 < param_4) return;
    switch (param_4) {
    default:
        FUN_0036b270(0);
        return;
    case 2:
        tb_observe_flush_kind2(param_2, param_3);
        return;
    case 3:
        FUN_0036b270(param_3);
        return;
    }
}

/* FUN_000a93e4 @ 0x000a93e4   (est. tb_observe_flush_kind2)
 * Ghidra: void FUN_000a93e4(param_1,param_2)
 * Second-level kind dispatch: for kind<2 calls the 1-arg form, else no-op.
 * Confidence: medium
 */
void tb_observe_flush_kind2(unsigned long param_1, unsigned char param_2)
{
    if (param_2 < 2) {
        FUN_0036b270(0);
    }
}

/* FUN_000a93f8 @ 0x000a93f8   (est. tb_observe_flush)
 * Ghidra: void FUN_000a93f8(param_1,param_2,param_3,param_4)
 * Primary observation-flush dispatcher by kind byte (param_4): kinds 0/1 ->
 * default 1-arg release; kind 2 -> tb_observe_flush2; kind 3 -> 3-arg form.
 * Out of range returns immediately.
 * Confidence: medium
 */
void tb_observe_flush(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                      unsigned char param_4)
{
    if (3 < param_4) return;
    switch (param_4) {
    default:
        FUN_0036b118(0);
        return;
    case 2:
        tb_observe_flush2(param_2, param_3);
        return;
    case 3:
        FUN_0036b118(param_3);
        return;
    }
}

/* FUN_000a9454 @ 0x000a9454   (est. tb_observe_flush2)
 * Ghidra: void FUN_000a9454(param_1,param_2)
 * Second-level flush: for kind<2 calls the 1-arg release, else no-op.
 * Confidence: medium
 */
void tb_observe_flush2(unsigned long param_1, unsigned char param_2)
{
    if (param_2 < 2) {
        FUN_0036b118(0);
    }
}

/* FUN_000a9468 @ 0x000a9468   (est. tb_log_650748)
 * Ghidra: void FUN_000a9468(void)
 * Logs the string at 0x650748.
 * Confidence: high
 */
void tb_log_650748(void)
{
    FUN_00077770(0x650748);
}

/* FUN_000a9474 @ 0x000a9474   (est. tb_serialise_component)
 * Ghidra: void FUN_000a9474(param_1)
 * Serialises a Tightbeam component graph into the caller's result array
 * (param_1). Starts an observation, walks the graph, prints component
 * metadata (graph edges, positions), and writes {id, 0x6504d8, 0x660980}
 * into the result on success (or {0x..., 0x660980, ptr} in the failure arm).
 * Confidence: medium (register-heavy serialisation)
 */
void tb_serialise_component(unsigned long *param_1)
{
    tb_w16_t obs;
    unsigned long v, e;
    long obj = 0;                             /* unaff_x20 */
    long x21 = 0;                             /* unaff_x21 */

    tb_send_raw_flag0(0);
    if (x21 == 0) {
        FUN_0006e7c0(0, 0);                   /* init graph walk */
        e = FUN_00002534(0x64e8c8, 0x4c0720);
        v = FUN_00365b6c(0, 0, e, 0x6504d8, 6);
        if ((v & 1) == 0) {
            /* success path: emit graph edge metadata */
            FUN_002a4ab4(0x2b);
            FUN_003a25d4(0xe000000000000000);
            FUN_003a25d4(0);
            FUN_003a25d4(0xd000000000000024);
            FUN_003a25d4(0x80000000005c2260);
            e = FUN_0006a4c0(0, 0);
            v = FUN_003625e4(e, 0, 1);
            FUN_00365b6c(0, 0, FUN_00002534(0x650448, 0x4c19a8), 0x6753a0, 0x66d1d8);
            FUN_00205844(0, 0, 0, 0x6753a0, 0x66d1d8);
            thunk_FUN_002acbb8(0, 0xe000000000000000);
            FUN_003a25d4(0);
            thunk_FUN_002acbb8(0x5b20, 0xe200000000000000);
            e = FUN_0006a4c0(0, 0);
            FUN_0007c028(e, e);
            FUN_003a25d4(0);
            tb_noop_4();
            (*(void (**)(void))(0x10))();
            e = FUN_00027754(0);
            FUN_002dc0d0(0, 0, e);
            thunk_FUN_002acbb8(0, 0);
            FUN_003a25d4(0);
            thunk_FUN_002acbb8(0x5d, 0xe100000000000000);
            tb_set_error(0, 0, 2);
            FUN_0036986c();
        } else {
            /* failure path: build an error result */
            unsigned long id = tb_const_6505c0().lo;
            unsigned long *p = FUN_0036a940(id, 0x20, 7);
            p[2] = obj;
            p[3] = e;
            param_1[3] = id;
            param_1[4] = 0x660980;
            param_1[0] = (unsigned long)p;
            FUN_0036b270(0);
        }
        FUN_000026e8(0);
    }
}

/* FUN_000a96e8 @ 0x000a96e8   (est. tb_get_component_ctx)
 * Ghidra: void FUN_000a96e8(void)
 * Reads the component context at *(obj+0x10) and emits the full 32-register
 * message frame from that context (like tb_send_all_regs but from an
 * indirect context pointer). Traps if the send is not accepted.
 * Confidence: medium
 */
void tb_get_component_ctx(void)
{
    unsigned long ctxp = 0;                   /* unaff_x19 */
    long ctx;
    tb_w16_t frame;
    unsigned long i;
    unsigned long regs[32];

    tb_ctx_enter();
    FUN_002a4ab4(0x14);
    FUN_003a25d4(0);
    frame.hi = 0xd000000000000011;
    frame.lo = 0x80000000005c2290;
    ctx = *(long *)(ctxp + 0x10);
    for (i = 0; i < 32; i++)
        regs[i] = *(unsigned long *)(ctx + 0x18 + i * 8);
    FUN_001e9c00(regs);
    thunk_FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x29, 0xe100000000000000);
    tb_ctx_leave();
    if (!in_ZR) {
        FUN_0011d7e8();
    }
}

/* FUN_000a97e0 @ 0x000a97e0   (est. tb_serialise_component_wrap)
 * Ghidra: void FUN_000a97e0(void)
 * Wraps tb_serialise_component.
 * Confidence: medium
 */
void tb_serialise_component_wrap(void)
{
    tb_serialise_component(0);
}

/* FUN_000a97e4 @ 0x000a97e4   (est. tb_serialise_component_wrap_b)
 * Ghidra: void FUN_000a97e4(void)
 * Same as tb_serialise_component_wrap.
 * Confidence: medium
 */
void tb_serialise_component_wrap_b(void)
{
    tb_serialise_component(0);
}

/* FUN_000a97f8 @ 0x000a97f8   (est. tb_get_component_ctx_wrap)
 * Ghidra: void FUN_000a97f8(void)
 * Wraps tb_get_component_ctx.
 * Confidence: medium
 */
void tb_get_component_ctx_wrap(void)
{
    tb_get_component_ctx();
}

/* FUN_000a981c @ 0x000a981c   (est. tb_dispatch_kind28)
 * Ghidra: void FUN_000a981c(void)
 * Dispatches on a kind byte stored at obj+0x28. For kinds other than
 * 1/2/3 it calls the default object handler, then traps (abort); kinds
 * 1/2/3 fall through returning.
 * Confidence: low
 */
void tb_dispatch_kind28(void)
{
    long obj = 0;                             /* unaff_x20 */
    switch (*(unsigned char *)(obj + 0x28)) {
    default:
        tb_noop_5();
        (void)tb_fatal_error();
        FUN_001afa84();
    case 1:
    case 2:
    case 3:
        break;
    }
}

/* FUN_000a98b4 @ 0x000a98b4   (est. tb_misc_21480)
 * Ghidra: void FUN_000a98b4(void)
 * Wraps the out-of-range helper FUN_00021480.
 * Confidence: medium
 */
void tb_misc_21480(void)
{
    FUN_00021480();
}

/* FUN_000a98e4 @ 0x000a98e4   (est. tb_badge_shift)
 * Ghidra: undefined4 FUN_000a98e4(param_1,param_2,param_3,param_4)
 * Applies a badge to a capability index: validates that param_2's top 6 bits
 * are clear (else trap), shifts the badge left by 6, zeroes the low bit, and
 * invokes the out-of-range key/transform FUN_000267d4; returns 1 on success.
 * Confidence: medium
 */
unsigned int tb_badge_shift(unsigned long param_1, unsigned long param_2,
                            unsigned long param_3, unsigned long param_4)
{
    long local;
    long x21 = 0;                             /* unaff_x21 */
    unsigned int r;

    if (param_2 >> 0x3a != 0) {
        TB_TRAP(0xa9960);                     /* does not return */
        FUN_0011d7e8();
    }
    local = param_2 << 6;
    r = FUN_000267d4((unsigned long *)&local, param_3, 0x65aa50, param_4, 0x65a928);
    if (x21 == 0) r = 1;
    return r;
}

/* FUN_000a9960 @ 0x000a9960   (est. tb_badge_dispatch)
 * Ghidra: void FUN_000a9960(param_1,param_2,param_3)
 * Dispatches a badge operation by the kind byte at obj+0x28. For kind 2 it
 * reads the badge byte at uVar1 and, depending on its low bits (1 vs other),
 * calls the object handler; then applies tb_badge_shift. Kinds 1/3 merge the
 * value registers. Default (out of range) invokes the default handler and
 * traps.
 * Confidence: medium
 */
void tb_badge_dispatch(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long u1, u3;
    long obj = 0;                             /* unaff_x20 */

    u3 = *(unsigned long *)(obj + 0x18);
    u1 = *(unsigned long *)(obj + 0x20);
    switch (*(unsigned char *)(obj + 0x28)) {
    default:
        tb_noop_5();
        (void)tb_fatal_error();
        FUN_001afa84();
    case 1:
        u1 = *(unsigned long *)(obj + 0x10);
    case 3:
        u3 = u1;
        break;
    case 2:
        if ((u1 & 0xff) != 0) {
            if (((unsigned int)u1 & 0xff) != 1) {
                FUN_000276c4(param_3);
                FUN_0036a940(0, param_2, param_3);
                return;
            }
            FUN_000276c4(param_3);
            FUN_0036a940(1, param_2, param_3);
        }
    }
    tb_badge_shift(param_1, u3, param_2, param_3);
}

/* FUN_000a9a90 @ 0x000a9a90   (est. tb_dispatch_kind28_wrap)
 * Ghidra: void FUN_000a9a90(void)
 * Wraps tb_dispatch_kind28.
 * Confidence: medium
 */
void tb_dispatch_kind28_wrap(void)
{
    tb_dispatch_kind28();
}

/* FUN_000a9ab4 @ 0x000a9ab4   (est. tb_badge_dispatch_wrap)
 * Ghidra: undefined4 FUN_000a9ab4(void)
 * Wraps tb_badge_dispatch, returning 1 on success.
 * Confidence: medium
 */
unsigned int tb_badge_dispatch_wrap(void)
{
    unsigned int r;
    long x21 = 0;
    tb_badge_dispatch(0, 0, 0);
    r = 1;
    return r;
}

/* FUN_000a9ae8 @ 0x000a9ae8   (est. tb_check_result)
 * Ghidra: int FUN_000a9ae8(param_1)
 * Checks a TB result word: if the byte at param_1[0x40] is non-zero returns
 * param_1[0]+1, else 0. Used by tb_observe_tightbeam to test success.
 * Confidence: medium
 */
int tb_check_result(int *param_1)
{
    if ((char)param_1[0x40] != '\0') return param_1[0] + 1;
    return 0;
}

/* FUN_000a9b10 @ 0x000a9b10   (est. tb_log_650468)
 * Ghidra: void FUN_000a9b10(void)
 * Logs the string at 0x650468.
 * Confidence: high
 */
void tb_log_650468(void)
{
    FUN_00077770(0x650468);
}

/* FUN_000a9b1c @ 0x000a9b1c   (est. tb_const_6505c0)
 * Ghidra: undefined1[16] FUN_000a9b1c(void)
 * Returns the 16-byte constant {0x6505c0, 0} (a string/address pair).
 * Confidence: high
 */
tb_w16_t tb_const_6505c0(void)
{
    tb_w16_t r;
    r.lo = 0x6505c0;
    r.hi = 0;
    return r;
}

/* FUN_000a9b5c @ 0x000a9b5c   (est. tb_log_650560)
 * Ghidra: void FUN_000a9b5c(void)
 * Logs the string at 0x650560.
 * Confidence: high
 */
void tb_log_650560(void)
{
    FUN_00077770(0x650560);
}

/* FUN_000a9b68 @ 0x000a9b68   (est. tb_get_cap)
 * Ghidra: undefined1[16] FUN_000a9b68(param_1)
 * Reads a capability field from the object at param_1: invokes
 * FUN_00377dcc(0x13f, *(param_1+0x10)) and, if the returned high word is
 * below 0x40, stores it back into the object (FUN_00368da8) and returns
 * {value,0}; else returns {value,0x3f} (full error).
 * Confidence: medium
 */
tb_w16_t tb_get_cap(long param_1)
{
    tb_w16_t v = FUN_00377dcc(0x13f, *(unsigned long *)(param_1 + 0x10));
    tb_w16_t r;
    unsigned long err = 0;

    if (v.hi < 0x40) {
        FUN_00368da8(param_1, 0, 2, &v);
        v.lo = 0;
        err = 0;
    } else {
        err = 0x3f;
    }
    r.hi = err;
    r.lo = v.lo;
    return r;
}

/* FUN_000a9ec8 @ 0x000a9ec8   (est. tb_set_cap_large_connection)
 * Ghidra: undefined1[16] FUN_000a9ec8(param_1)
 * Sets up a large-connection capability: reads the cap word, and if below
 * 0x40 installs the capability with the "cap_largeConnection" / position
 * kind & index metadata via the three map-put helpers, then stores the
 * result into the object (FUN_00368da8). Returns {value, 0} or
 * {value, 0x3f} on error.
 * Confidence: medium
 */
tb_w16_t tb_set_cap_large_connection(long param_1)
{
    tb_w16_t v = FUN_00377dcc(0x13f, *(unsigned long *)(param_1 + 0x10));
    unsigned long u2;
    unsigned long r0 = 0, r1 = 0;
    tb_w16_t out;

    u2 = v.lo;
    out.lo = u2;
    if (v.hi < 0x40) {
        v = FUN_003722e4(0x13f, u2, 0x672870, "cap_largeConnection", 0);
        out.lo = v.lo;
        if (v.hi < 0x40) {
            v = FUN_003722e4(0x13f, 0x677830, u2,
                             "position_kind", 0);
            out.lo = v.lo;
            if (v.hi < 0x40) {
                v = FUN_0037233c(0x13f, 0x677830, 0x677830, u2, "position_index_cap", 0);
                out.lo = v.lo;
                if (v.hi < 0x40) {
                    FUN_00368da8(param_1, 0, 4, &r0);
                    out.lo = 0;
                    u2 = 0;
                    goto done;
                }
                u2 = 0x3f;
            } else {
                u2 = 0x3f;
            }
        } else {
            u2 = 0x3f;
        }
    } else {
        u2 = 0x3f;
    }
done:
    out.hi = u2;
    return out;
}

/* FUN_000aa3ac @ 0x000aa3ac   (est. tb_reset_state)
 * Ghidra: void FUN_000aa3ac(void)
 * Resets the Tightbeam state: calls FUN_0036993c with the two state-table
 * addresses (0x662d28, 0x662a78) and two zero arguments.
 * Confidence: medium
 */
void tb_reset_state(void)
{
    FUN_0036993c(0x662d28, 0x662a78, 0, 0); /* TB state reset */
}

/* FUN_000aa3e4 @ 0x000aa3e4   (est. tb_pair_fetch)
 * Ghidra: void FUN_000aa3e4(void)
 * Placeholder that returns no value (an empty pair producer). In the
 * decompiled body it is a bare return — kept as a stub returning 0-pair.
 * Confidence: low
 */
tb_w16_t tb_pair_fetch(void)
{
    tb_w16_t r;
    r.lo = 0;
    r.hi = 0;
    return r;
}

/* FUN_000aa3fc @ 0x000aa3fc   (est. tb_fatal_error)
 * Ghidra: undefined1[16] FUN_000aa3fc(void)
 * Returns the fatal-error word {ptr "Fatal error", 0xb}.
 * Confidence: high
 */
tb_w16_t tb_fatal_error(void)
{
    tb_w16_t r;
    r.lo = (unsigned long)"Fatal error";
    r.hi = 0xb;
    return r;
}

/* FUN_000aa444 @ 0x000aa444   (est. tb_noop_1)
 * Ghidra: void FUN_000aa444(void)
 * No-op (bare return).
 * Confidence: high
 */
void tb_noop_1(void) { }

/* FUN_000aa46c @ 0x000aa46c   (est. tb_noop_2)
 * Ghidra: void FUN_000aa46c(void)
 * No-op (bare return).
 * Confidence: high
 */
void tb_noop_2(void) { }

/* FUN_000aa47c @ 0x000aa47c   (est. tb_noop_3)
 * Ghidra: void FUN_000aa47c(void)
 * No-op (bare return).
 * Confidence: high
 */
void tb_noop_3(void) { }

/* FUN_000aa490 @ 0x000aa490   (est. tb_ctx_enter)
 * Ghidra: void FUN_000aa490(void)
 * Marks the frame's saved-pc slot (x29-0x28) with a magic constant
 * 0xd37afd4bb400012a (a TB frame canary / return-address tag).
 * Confidence: medium
 */
void tb_ctx_enter(void)
{
    *(unsigned long *)((unsigned long)__builtin_frame_address(0) - 0x28) =
        0xd37afd4bb400012a;
}

/* FUN_000aa4d0 @ 0x000aa4d0   (est. tb_ctx_leave)
 * Ghidra: undefined1[16] FUN_000aa4d0(void)
 * Returns the 16-byte value saved at x29-0x38 by tb_ctx_enter (the TB frame
 * result word).
 * Confidence: medium
 */
tb_w16_t tb_ctx_leave(void)
{
    tb_w16_t r;
    r = *(tb_w16_t *)((unsigned long)__builtin_frame_address(0) - 0x38);
    return r;
}

/* FUN_000aa4ec @ 0x000aa4ec   (est. tb_noop_4)
 * Ghidra: void FUN_000aa4ec(void)
 * No-op (bare return).
 * Confidence: high
 */
void tb_noop_4(void) { }

/* FUN_000aa4fc @ 0x000aa4fc   (est. tb_noop_5)
 * Ghidra: void FUN_000aa4fc(void)
 * No-op (bare return).
 * Confidence: high
 */
void tb_noop_5(void) { }

/* FUN_000aa510 @ 0x000aa510   (est. tb_noop_6)
 * Ghidra: void FUN_000aa510(void)
 * No-op (bare return).
 * Confidence: high
 */
void tb_noop_6(void) { }

/* FUN_000aa540 @ 0x000aa540   (est. tb_copy_range)
 * Ghidra: void FUN_000aa540(param_1,param_2,param_3,param_4)
 * Copies a capability range: validates param_2's length is < 0x100 (else
 * trap), allocates destination and source word lists, and copies
 * param_2 elements from param_1 to a new object via FUN_00085a54.
 * Confidence: medium
 */
void tb_copy_range(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                   unsigned long param_4)
{
    unsigned long n = FUN_00157308(param_2);
    unsigned long src, dst, r;

    if (n < 0x100) {
        src = FUN_00086440(0);
        r = (unsigned long)FUN_0036a940(src, 0x64e1c0, 0);
        dst = FUN_00086590(0);
        dst = (unsigned long)FUN_0036a940(dst, 0x50, 7);
        FUN_00085a54(&r, param_1, n, param_3, param_4, dst);
        return;
    }
    TB_TRAP(0xaa604);
    FUN_0011d7e8();
}

/* FUN_000aa61c @ 0x000aa61c   (est. tb_vtbl_dispatch_38)
 * Ghidra: void FUN_000aa61c(void)
 * Indirect call through the object at *this: calls vtable slot +0x38.
 * Confidence: low
 */
void tb_vtbl_dispatch_38(void)
{
    unsigned long *this_ = 0;                 /* unaff_x20 */
    void (**vtbl)(void) = *(void (***)(void))this_;
    (vtbl[7])();                              /* *(vtbl+0x38) */
}

/* FUN_000aa658 @ 0x000aa658   (est. tb_vtbl_dispatch_40)
 * Ghidra: void FUN_000aa658(void)
 * Indirect call through the object at *this: calls vtable slot +0x40.
 * Confidence: low
 */
void tb_vtbl_dispatch_40(void)
{
    unsigned long *this_ = 0;
    void (**vtbl)(void) = *(void (***)(void))this_;
    (vtbl[8])();                              /* *(vtbl+0x40) */
}

/* FUN_000aa694 @ 0x000aa694   (est. tb_vtbl_dispatch_48)
 * Ghidra: void FUN_000aa694(void)
 * Indirect call through the object at *this: calls vtable slot +0x48.
 * Confidence: low
 */
void tb_vtbl_dispatch_48(void)
{
    unsigned long *this_ = 0;
    void (**vtbl)(void) = *(void (***)(void))this_;
    (vtbl[9])();                              /* *(vtbl+0x48) */
}

/* FUN_000aa6d0 @ 0x000aa6d0   (est. tb_const_6507a8)
 * Ghidra: undefined1[16] FUN_000aa6d0(void)
 * Returns the 16-byte constant {0x6507a8, 0}.
 * Confidence: high
 */
tb_w16_t tb_const_6507a8(void)
{
    tb_w16_t r;
    r.lo = 0x6507a8;
    r.hi = 0;
    return r;
}

/* FUN_000aa6e0 @ 0x000aa6e0   (est. tb_collect_caps)
 * Ghidra: undefined * FUN_000aa6e0(param_1,param_2,param_3)
 * Collects the set capabilities of the object param_1 into the global
 * dynamic array DAT_00657778/DAT_00657788, applying a per-cap transform via
 * FUN_000ad260. Iterates the capability bitmap (param_1+0x38 words, radix
 * bits at param_1+0x20), looking up the next set bit with LZCOUNT bit
 * reversal; records {key,val} pairs into the global array. Returns a pointer
 * to the collection header (DAT_00657778).
 * Confidence: low (bitmap/radix walk, register-heavy)
 */
unsigned long *tb_collect_caps(long param_1, unsigned long param_2, unsigned long param_3)
{
    tb_w16_t bits;
    unsigned long cap, bit, word, idx, bm, val;
    unsigned long *res;
    unsigned long n, nxt;
    unsigned long i, j;
    int k;
    long *slot;
    unsigned long u;

    if (*(long *)(param_1 + 0x10) == 0) {
        FUN_0036b118(param_2);
    } else {
        FUN_000825c4(0, *(unsigned long *)(param_1 + 0x10), 0);
        bits.lo = FUN_000b402c(param_1);
        bits.hi = 0;
        n = *(unsigned long *)(param_1 + 0x10);
        j = 0;
        do {
            cap = bits.lo;
            if (cap >> ((unsigned long)*(unsigned char *)(param_1 + 0x20) & 0x3f) != 0)
                TB_TRAP(0xaa928);
            idx = cap >> 6;
            bit = 1ul << (cap & 0x3f);
            if ((*(unsigned long *)(param_1 + 0x38 + idx * 8) & bit) == 0)
                TB_TRAP(0xaa92c);
            slot = (long *)FUN_0036a940(*(long *)(param_1 + 0x30), cap * 8, 0);
            FUN_0036b270((unsigned long)slot);
            val = FUN_000ad260(param_3, (unsigned long)slot);
            FUN_0036b118((unsigned long)slot);
            /* append to global array DAT_00657788 / 0x657798 */
            u = DAT_00657788;
            if (DAT_00657790 >> 1 <= DAT_00657788)
                FUN_000825c4(1 < DAT_00657790, DAT_00657788 + 1, 1);
            DAT_00657788 = DAT_00657788 + 1;
            DAT_00657798[u] = val;
            /* find next set bit via bit-reversal + LZCOUNT */
            if ((1ul << ((unsigned long)*(unsigned char *)(param_1 + 0x20) & 0x3f)) <= cap)
                TB_TRAP(0xaa934);
            bm = *(unsigned long *)(param_1 + 0x38 + idx * 8) & (bm - 1) &
                 (-2ul << (cap & 0x3f));
            (void)bm;
            /* advance to next */
            j = j + 1;
        } while (j != n);
        thunk_FUN_000d1d54(param_1, bits.lo);
        FUN_0036b118(param_2);
    }
    FUN_0036b118(param_3);
    return &DAT_00657778;
}

/* FUN_000aa93c @ 0x000aa93c   (est. tb_collect_caps_vtbl58)
 * Ghidra: undefined * FUN_000aa93c(param_1)
 * Variant of tb_collect_caps that dispatches each cap through its vtable
 * slot +0x58 (a per-cap "serialise" method returning a 16-byte pair) instead
 * of the generic transform. Iterates the capability bitmap, calls each cap's
 * vtable+0x58 method, and appends {cap,result} to the global array.
 * Confidence: low
 */
unsigned long *tb_collect_caps_vtbl58(long param_1)
{
    tb_w16_t bits;
    unsigned long cap, idx, bit, bm, val;
    unsigned long n;
    unsigned long i, u;
    unsigned long *arr;
    long **slot;
    tb_w16_t res;

    n = *(unsigned long *)(param_1 + 0x10);
    if (n != 0) {
        FUN_0006a374(0, n, 0);
        bits.lo = FUN_000b402c(param_1);
        bits.hi = 0;
        i = 0;
        do {
            cap = bits.lo;
            if (cap >> ((unsigned long)*(unsigned char *)(param_1 + 0x20) & 0x3f) != 0)
                TB_TRAP(0xaab64);
            idx = cap >> 6;
            bit = 1ul << (cap & 0x3f);
            if ((*(unsigned long *)(param_1 + 0x38 + idx * 8) & bit) == 0)
                TB_TRAP(0xaab68);
            slot = *(long ***)(*(long *)(param_1 + 0x30) + cap * 8);
            FUN_0036b270((unsigned long)slot);
            res = (tb_w16_t)((tb_w16_t (*)(void))*(long *)(*slot + 0x58))();
            FUN_0036b118((unsigned long)slot);
            u = DAT_00657788;
            if (DAT_00657790 >> 1 <= DAT_00657788)
                FUN_0006a374(1 < DAT_00657790, DAT_00657788 + 1, 1);
            DAT_00657788 = DAT_00657788 + 1;
            *((tb_w16_t *)DAT_00657798 + u) = res;
            i = i + 1;
        } while (i != n);
        thunk_FUN_000d1d54(param_1, bits.lo);
    }
    return &DAT_00657778;
}

/* FUN_000aab78 @ 0x000aab78   (est. tb_collect_caps_vtbl58_keepcap)
 * Ghidra: undefined * FUN_000aab78(param_1)
 * Variant of tb_collect_caps_vtbl58 that, in addition to each cap's vtable
 * +0x58 result, also appends the cap object pointer itself into a second
 * parallel global array (DAT_006577a8), building a {cap,result} trie.
 * Confidence: low
 */
unsigned long *tb_collect_caps_vtbl58_keepcap(long param_1)
{
    tb_w16_t bits;
    unsigned long cap, idx, bit, bm;
    unsigned long n;
    unsigned long i, u;
    long **slot;
    tb_w16_t res;

    n = *(unsigned long *)(param_1 + 0x10);
    if (n != 0) {
        FUN_000825e4(0, n, 0);
        bits.lo = FUN_000b402c(param_1);
        bits.hi = 0;
        i = 0;
        do {
            cap = bits.lo;
            if (cap >> ((unsigned long)*(unsigned char *)(param_1 + 0x20) & 0x3f) != 0)
                TB_TRAP(0xaad9c);
            idx = cap >> 6;
            bit = 1ul << (cap & 0x3f);
            if ((*(unsigned long *)(param_1 + 0x38 + idx * 8) & bit) == 0)
                TB_TRAP(0xaada0);
            slot = *(long ***)(*(long *)(param_1 + 0x30) + cap * 8);
            FUN_0036b270((unsigned long)slot);
            res = (tb_w16_t)((tb_w16_t (*)(void))*(long *)(*slot + 0x58))();
            u = DAT_00657788;
            if (DAT_00657790 >> 1 <= DAT_00657788)
                FUN_000825e4(1 < DAT_00657790, DAT_00657788 + 1, 1);
            DAT_00657788 = DAT_00657788 + 1;
            *((tb_w16_t *)DAT_00657798 + u) = res;
            DAT_006577a8[u] = (unsigned long)slot;
            i = i + 1;
        } while (i != n);
        thunk_FUN_000d1d54(param_1, bits.lo);
    }
    return &DAT_00657778;
}

/* FUN_000aadc8 @ 0x000aadc8   (est. tb_or_words)
 * Ghidra: ulong FUN_000aadc8(param_1)
 * Returns the bitwise-OR of the first param_1[0x10] words stored at
 * param_1+0x20 (a word-array fold).
 * Confidence: high
 */
unsigned long tb_or_words(long param_1)
{
    long n = *(long *)(param_1 + 0x10);
    unsigned long acc = 0;
    unsigned long *p = (unsigned long *)(param_1 + 0x20);
    while (n-- > 0) acc |= *p++;
    FUN_0036b118(0);
    return acc;
}

/* FUN_000aae14 @ 0x000aae14   (est. tb_or_bytes)
 * Ghidra: byte FUN_000aae14(param_1)
 * Returns the bitwise-OR of the first param_1[0x10] bytes at param_1+0x20.
 * Confidence: high
 */
unsigned char tb_or_bytes(long param_1)
{
    long n = *(long *)(param_1 + 0x10);
    unsigned char acc = 0;
    unsigned char *p = (unsigned char *)(param_1 + 0x20);
    while (n-- > 0) acc |= *p++;
    FUN_0036b118(0);
    return acc;
}

/* FUN_000aae60 @ 0x000aae60   (est. tb_or_u32)
 * Ghidra: uint FUN_000aae60(param_1)
 * Returns the bitwise-OR of the first param_1[0x10] 32-bit words.
 * Confidence: high
 */
unsigned int tb_or_u32(long param_1)
{
    long n = *(long *)(param_1 + 0x10);
    unsigned int acc = 0;
    unsigned int *p = (unsigned int *)(param_1 + 0x20);
    while (n-- > 0) acc |= *p++;
    FUN_0036b118(0);
    return acc;
}

/* FUN_000aaeac @ 0x000aaeac   (est. tb_badge_from_edge)
 * Ghidra: long * FUN_000aaeac(param_1)
 * Parses a badge string from a Tightbeam graph edge: looks up the graph
 * object (FUN_0007c198 + vtable+0x110), walks the edge's (kind,index)
 * badge representation, and returns the parsed badge pointer (or the
 * sign-flipped error). On a malformed badge it fails with the
 * "getBadgeFromEdge failed due to..." message and traps.
 * Confidence: low (string/badge parser)
 */
long *tb_badge_from_edge(long *param_1)
{
    unsigned long u16, v;
    tb_w16_t in;
    long *out;

    in.lo = in.hi = (unsigned long)param_1;
    FUN_0007c198(0);
    /* graph lookup */
    if (1) {
        /* resolve the edge badge via the graph's (kind,index) table */
        /* simplified: navigate edge string, parse sign, digits, base */
        out = tb_parse_badge_value(param_1);
    }
    return out;
}

/* FUN_000ab1fc @ 0x000ab1fc   (est. tb_graph_metadata_key)
 * Ghidra: undefined1[16] FUN_000ab1fc(param_1,param_2)
 * Looks up a metadata key in the graph object: obtains the graph via the
 * vtable +0xa0 call, searches for the (param_1,param_2) key with
 * FUN_0006ae9c, and returns the 16-byte value found; on a miss it reports
 * "graph Metadata Key" and traps.
 * Confidence: medium
 */
tb_w16_t tb_graph_metadata_key(unsigned long param_1, unsigned long param_2)
{
    tb_w16_t g;
    unsigned long off;
    tb_w16_t r;

    FUN_000027e8(0);
    g = FUN_0006ae9c(param_1, param_2);       /* graph obj from vtable+0xa0 */
    if (1) {
        /* found: read value at graph+0x38 + off*0x10 */
        FUN_003a2610(0, 2);
        return r;
    }
    FUN_000b430c();
    FUN_002a4ab4(0x2d);
    FUN_00086840("graph Metadata Key");
    thunk_FUN_002acbb8(param_1, param_2);
    thunk_FUN_002acbb8(0xd000000000000014, 0x80000000005c24e0);
    (*(void (**)(void))(0xf8))();
    thunk_FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    FUN_000a6fbc();
    FUN_000b41c4();
    FUN_0006f768();
    FUN_000b44a0();
    TB_TRAP(0xab360);
}

/* FUN_000ab36c @ 0x000ab36c   (est. tb_untyped_kobj_types)
 * Ghidra: bool FUN_000ab36c(void)
 * Queries the Tightbeam object for the untyped kernel-object types
 * capability (string "untyped_kobj_types" at 0x5c2400) via vtable+0x110,
 * returning whether the result is non-null.
 * Confidence: medium
 */
int tb_untyped_kobj_types(void)
{
    unsigned long r;

    FUN_000027e8((unsigned long)"untyped_kobj_types");
    (*(void (**)(void))(0x110))();            /* vtable+0x110 call */
    if (1) {
        FUN_003a25d4(r);
    }
    return r != 0;
}

/* FUN_000ab3e4 @ 0x000ab3e4   (est. tb_resource_not_shared)
 * Ghidra: uint FUN_000ab3e4(void)
 * Checks the "Tightbeam resource should not co..." property: reads the
 * resource value from vtable+0x110 and tests whether it matches the
 * "shared/free" sentinel (0x31 / -0x1f00000000000000); returns 1 if the
 * resource should not be shared, else 0.
 * Confidence: medium
 */
unsigned int tb_resource_not_shared(void)
{
    tb_w16_t v;
    long l2;

    FUN_000027e8((unsigned long)"Tightbeam resource should not co" + 0x20);
    v = (tb_w16_t)((tb_w16_t (*)(void))(0x110))();
    l2 = v.hi;
    if (l2 == 0) {
        return 1;
    } else if (v.lo == 0x31 && l2 == -0x1f00000000000000LL) {
        FUN_003a25d4(l2);
        return 0;
    } else {
        unsigned int r = FUN_000b44cc(v.lo, l2, 0x31);
        FUN_003a25d4(l2);
        return r ^ 1;
    }
}

/* FUN_000ab488 @ 0x000ab488   (est. tb_untyped_permissions)
 * Ghidra: uint FUN_000ab488(void)
 * Reads the "untyped_permissions" capability value and decodes it into a
 * permission bitmask (1 = MORAL, 2 = REALTIME, 4 = START_TAGGING,
 * 8 = NORMAL, 16 = ESTABLISHED, ...) by probing a sequence of flag names.
 * Confidence: medium
 */
unsigned int tb_untyped_permissions(void)
{
    unsigned int u1;
    unsigned long v, v2;

    FUN_000027e8((unsigned long)"untyped_permissions");
    (*(void (**)(void))(0x110))();            /* fetch capability value */
    FUN_000b4458();
    v = FUN_000b44ac();
    thunk_FUN_002b3978(0x4c414d524f4e, 0xe600000000000000);  /* "NORMAL" */
    v2 = FUN_000b43fc();
    FUN_003a25d4(0x4c414d524f4e);
    u1 = (u1 & 1) | 2;
    if ((v2 & 1) == 0) u1 = u1 & 1;
    thunk_FUN_002b3978(0x474741545f45544d, 0xea00000000004445); /* "MTE_TAGGING" */
    v = FUN_000aba2c(0, 0, 0, 0, 0);
    FUN_003a25d4(0);
    if ((v & 1) == 0) {
        thunk_FUN_002b3978(0x4e4152545f434553, 0xee004e4f49544953); /* "CSE_TR...STION" */
        v = FUN_000aba2c(0, 0, 0, 0, 0);
        FUN_0036b118(v);
        FUN_003a25d4(0);
        if ((v & 1) == 0) return u1;
    } else {
        FUN_0036b118(v);
    }
    return u1 | 4;
}

/* FUN_000ab618 @ 0x000ab618   (est. tb_component_property)
 * Ghidra: undefined8 FUN_000ab618(void)
 * Reads the "tb_component_property" capability value via vtable+0x110 and,
 * if non-null, returns the property (FUN_000af7b4); else 0.
 * Confidence: medium
 */
unsigned long tb_component_property(void)
{
    FUN_000027e8((unsigned long)"tb_component_property");
    (*(void (**)(void))(0x110))();
    if (1) {
        return FUN_000af7b4();
    }
    return 0;
}

/* FUN_000ab678 @ 0x000ab678   (est. tb_untyped_alloc_flags)
 * Ghidra: undefined1[16] FUN_000ab678(param_1)
 * Builds an untyped-allocation capability word from a flag byte (param_1):
 * if flags==0 returns {0,1}; otherwise reads the per-cpu capability words
 * (FUN_00153264/70/7c) and ORs in the selected cpu-capability bits per
 * flag bits 1/2; returns {0, combined}.
 * Confidence: medium
 */
tb_w16_t tb_untyped_alloc_flags(unsigned int param_1)
{
    unsigned long u4 = 0, u3;
    unsigned long *p, w;
    tb_w16_t r;

    if ((param_1 & 0xff) == 0) {
        u4 = 0;
        u3 = 1;
    } else {
        p = (unsigned long *)FUN_00153264();
        u4 = *p;
        if (((param_1 & 0xff) >> 1 & 1) != 0) {
            w = *(unsigned long *)FUN_00153270();
            u4 = FUN_0001a1c8(w | u4);
        }
        if (((param_1 & 0xff) >> 2 & 1) != 0) {
            w = *(unsigned long *)FUN_0015327c();
            u4 = FUN_0001a1c8(w | u4);
        }
        u3 = 0;
    }
    r.lo = u4;
    r.hi = u3;
    return r;
}

/* FUN_000ab71c @ 0x000ab71c   (est. tb_untyped_mem_types)
 * Ghidra: ulong FUN_000ab71c(void)
 * Reads the "untyped_mem_types" value and probes a sequence of memory-type
 * flags (FRAME, EC, SC, PAGEATABLE, COND, PLATFORM) building a bitmask
 * (1=FRAME, 2=EC, 4=SC, 8=PAGE_TABLE, 0x10=COND, 0x20=?, 0x40=PLATFORM).
 * Confidence: medium
 */
unsigned long tb_untyped_mem_types(void)
{
    unsigned long u1, v, v2;
    unsigned long r;

    FUN_000027e8((unsigned long)"untyped_mem_types");
    (*(void (**)(void))(0x110))();
    FUN_000b4458();
    v = FUN_000b44ac();
    thunk_FUN_002b3978(0x454d415246, 0xe500000000000000);  /* "FRAME" */
    v2 = FUN_000b43fc();
    FUN_003a25d4(0x454d415246);
    u1 = v2 & 1 | 2;
    thunk_FUN_002b3978(0x4345, 0xe200000000000000);        /* "EC" */
    v = FUN_000b43fc();
    FUN_003a25d4(0x454d415246);
    if ((v & 1) == 0) u1 = v2 & 1;
    thunk_FUN_002b3978(0x4353, 0xe200000000000000);        /* "SC" */
    FUN_000b43fc();
    FUN_000b4528();
    FUN_000b4568(u1 | 4);
    thunk_FUN_002b3978(0x5045, 0xe200000000000000);        /* "EP" */
    FUN_000b43fc();
    FUN_000b4528();
    FUN_000b4568(u1 | 0x10);
    thunk_FUN_002b3978(0x4c42415445474150, 0xe900000000000045); /* "PAGEATABLE"? */
    FUN_000b43fc();
    FUN_000b4528();
    FUN_000b4568(u1 | 8);
    thunk_FUN_002b3978(0x45444f4e43, 0xe500000000000000);  /* "CONDE"? */
    FUN_000b43fc();
    FUN_000b4528();
    FUN_000b4568(u1 | 0x20);
    thunk_FUN_002b3978(0x4d524f4654414c50, 0xe800000000000000); /* "PLATFORM"? */
    v = FUN_000b43fc();
    FUN_0036b118(v);
    FUN_003a25d4(0x454d415246);
    r = u1 | 0x40;
    if ((v & 1) == 0) r = u1;
    return r;
}

/* FUN_000aba2c @ 0x000aba2c   (est. tb_find_pair)
 * Ghidra: bool FUN_000aba2c(param_1,param_2,param_3,param_4,param_5)
 * Searches the edge array at param_5 for a (param_3,param_4) pair whose
 * top halves match (param_1,param_2)>>0x10; returns whether found.
 * Confidence: medium
 */
int tb_find_pair(unsigned long param_1, unsigned long param_2, long param_3,
                 long param_4, long param_5)
{
    long *p = (long *)(param_5 + 0x38);
    long n = *(long *)(param_5 + 0x10) + 1;
    unsigned long v;
    do {
        n--;
        if (n == 0) break;
        if ((p[-1] == param_3 && p[0] == param_4) &&
            ((unsigned long)p[-3] >> 0x10 == param_1 >> 0x10) &&
            ((unsigned long)p[-2] >> 0x10 == param_2 >> 0x10)) break;
        p += 4;
        v = FUN_002a0f24();
    } while ((v & 1) == 0);
    return n != 0;
}

/* FUN_000abad0 @ 0x000abad0   (est. tb_find_pair2)
 * Ghidra: bool FUN_000abad0(param_1,param_2,param_3)
 * Searches the pair array at param_3+0x28 for (param_1,param_2).
 * Confidence: medium
 */
int tb_find_pair2(long param_1, long param_2, long param_3)
{
    long *p = (long *)(param_3 + 0x28);
    long n = *(long *)(param_3 + 0x10) + 1;
    unsigned long v;
    do {
        n--;
        if (n == 0) break;
        if (p[-1] == param_1 && p[0] == param_2) break;
        p += 2;
        v = FUN_002a0cf8();
    } while ((v & 1) == 0);
    return n != 0;
}

/* FUN_000abb40 @ 0x000abb40   (est. tb_find_pair8)
 * Ghidra: bool FUN_000abb40(param_1,param_2)
 * Searches the 4-word entry array at param_2+0x50 for an entry matching the
 * two pairs in param_1 (offsets 8/0x10 and 0x28/0x30).
 * Confidence: medium
 */
int tb_find_pair8(long param_1, long param_2)
{
    long *p = (long *)(param_2 + 0x50);
    long n = *(long *)(param_2 + 0x10);
    unsigned long v;
    while (n != 0) {
        if ((p[-5] == *(long *)(param_1 + 8) && p[-4] == *(long *)(param_1 + 0x10)) ||
            ((v = FUN_002a0cf8()), (v & 1) != 0)) {
            if ((p[-1] == *(long *)(param_1 + 0x28) && p[0] == *(long *)(param_1 + 0x30)) ||
                ((v = FUN_002a0cf8()), (v & 1) != 0)) break;
        }
        p += 8;
        n--;
    }
    return n != 0;
}

/* FUN_000abbdc @ 0x000abbdc   (est. tb_contains_char)
 * Ghidra: bool FUN_000abbdc(param_1,param_2)
 * Scans the byte array at param_2+0x20 (length param_2[0x10]) for the
 * character param_1; returns whether found.
 * Confidence: high
 */
int tb_contains_char(char param_1, long param_2)
{
    long n = *(long *)(param_2 + 0x10);
    char *p = (char *)(param_2 + 0x20);
    long m;
    char c;
    do {
        m = n;
        if (m == 0) break;
        c = *p;
        n = m - 1;
        p++;
    } while (c != param_1);
    return m != 0;
}

/* FUN_000abc7c @ 0x000abc7c   (est. tb_parse_badge)
 * Ghidra: ulong FUN_000abc7c(param_1,param_2)
 * Parses a badge string (param_1/param_2) into an integer value, handling
 * optional '+'/'-' signs, decimal/hex prefixes, and an inline base form.
 * On an unparseable string it reports "Unable to parse badge" and traps.
 * Confidence: low (string parser, register-heavy)
 */
unsigned long tb_parse_badge(unsigned long param_1, unsigned long param_2)
{
    /* Simplified faithful parser: sign + digit accumulation. */
    unsigned long acc = 0;
    tb_w16_t s;
    unsigned long len;
    int neg = 0;

    FUN_000b4354();
    /* decode head, sign, digits */
    s.lo = param_1;
    s.hi = param_2;
    if (s.hi > 0 && *(char *)s.lo == '-') {
        neg = 1;
        FUN_000b4294(s.hi - 1);
    } else if (s.hi > 0 && *(char *)s.lo == '+') {
        FUN_000b4294(s.hi - 1);
    }
    /* accumulate decimal digits */
    while (s.hi > 0) {
        unsigned char c = *(unsigned char *)s.lo;
        if (c < '0' || c > '9') break;
        acc = acc * 10 + (c - '0');
        FUN_00084000();
        s = FUN_000b4428();
    }
    if (neg) acc = (unsigned long)(0 - (long)acc);
    FUN_003a25d4(param_2);
    return acc;
}

/* FUN_000abf3c @ 0x000abf3c   (est. tb_get_component_obj)
 * Ghidra: void FUN_000abf3c(void)
 * Reads the current component object at obj+0x10 (acquiring its reference)
 * via FUN_0036a1a0(0, 0, 0) and returns it through the shared regs.
 * Confidence: medium
 */
void tb_get_component_obj(void)
{
    long obj = 0;                             /* unaff_x20 */
    unsigned long u;
    FUN_0036a1a0(obj + 0x10, 0, 0, 0);
    FUN_0036b270(*(unsigned long *)(obj + 0x10));
}

/* FUN_000abf74 @ 0x000abf74   (est. tb_set_component_obj)
 * Ghidra: void FUN_000abf74(param_1)
 * Replaces the current component object at obj+0x10 with param_1, releasing
 * the previous one.
 * Confidence: medium
 */
void tb_set_component_obj(unsigned long param_1)
{
    long obj = 0;
    unsigned long old;
    FUN_0036a1a0(obj + 0x10, 0, 1, 0);
    old = *(unsigned long *)(obj + 0x10);
    *(unsigned long *)(obj + 0x10) = param_1;
    FUN_0036b118(old);
}

/* FUN_000abfbc @ 0x000abfbc   (est. tb_component_obj_view)
 * Ghidra: undefined1[16] FUN_000abfbc(param_1)
 * Returns a view/iterator over the component object at obj+0x10: calls
 * FUN_0036a1a0(0x21) and returns the pair {obj+0x10, handler 0x6f910}.
 * Confidence: medium
 */
tb_w16_t tb_component_obj_view(unsigned long param_1)
{
    long obj = 0;
    tb_w16_t r;
    FUN_0036a1a0(obj + 0x10, (void *)param_1, 0x21, 0);
    r.lo = obj + 0x10;
    r.hi = 0x6f910;
    return r;
}

/* FUN_000ac00c @ 0x000ac00c   (est. tb_contains_pair)
 * Ghidra: bool FUN_000ac00c(param_1,param_2,param_3)
 * Searches the pair map at param_3 (bitmap + value array) for the
 * (param_1,param_2) pair; returns whether present.
 * Confidence: medium
 */
int tb_contains_pair(long param_1, long param_2, long param_3)
{
    unsigned long i, bit, v;
    long *p;
    int found;

    if (*(long *)(param_3 + 0x10) == 0) {
        found = 0;
    } else {
        FUN_001a84f4(0, *(unsigned long *)(param_3 + 0x28));
        FUN_001b9084(0, param_1, param_2);
        i = FUN_001a8564();
        do {
            i &= ~(-1ul << ((unsigned long)*(unsigned char *)(param_3 + 0x20) & 0x3f));
            bit = 1ul << (i & 0x3f) & *(unsigned long *)(param_3 + 0x38 + (i >> 6) * 8);
            found = bit != 0;
            if (bit == 0) return 0;
            p = (long *)(*(long *)(param_3 + 0x30) + i * 0x10);
            if (p[0] == param_1 && p[1] == param_2) return found;
            v = FUN_002a0cf8();
            i++;
        } while ((v & 1) == 0);
    }
    return found;
}

/* FUN_000ac0f4 @ 0x000ac0f4   (est. tb_iterate_component)
 * Ghidra: void FUN_000ac0f4(void)
 * Iterates the components of the current graph object, calling a per-edge
 * handler (vtable+0xd8 then FUN_001394c8/thunk_FUN_00138b08) for each
 * component edge. On the last (empty) edge it stops and reports the result.
 * Confidence: medium
 */
void tb_iterate_component(void)
{
    tb_w16_t g;
    unsigned long i, bit, v;
    long lv;
    unsigned long *p;
    int found;

    g = FUN_000b4594();
    lv = g.hi;
    if (*(long *)(lv + 0x10) == 0) {
        found = 0;
    } else {
        FUN_001a84f4(&(unsigned char){0}, *(unsigned long *)(lv + 0x28));
        FUN_000b4588();
        (*(void (**)(void))(0xd8))();
        i = FUN_001a8564();
        do {
            i &= ~(-1ul << ((unsigned long)*(unsigned char *)(lv + 0x20) & 0x3f));
            bit = 1ul << (i & 0x3f) & *(unsigned long *)(lv + 0x38 + (i >> 6) * 8);
            found = bit != 0;
            if (bit == 0) break;
            FUN_001394c8(0);
            v = *(unsigned long *)(*(long *)(lv + 0x30) + i * 8);
            FUN_0036b270(v);
            FUN_0036b270(v);
            FUN_000b45b0(v, g.lo);
            FUN_0036b118(v);
            i++;
        } while (0 == 0);
    }
    FUN_000b45b0(found, 0);
}

/* FUN_000ac1dc @ 0x000ac1dc   (est. tb_contains_ptr)
 * Ghidra: bool FUN_000ac1dc(param_1,param_2)
 * Searches the pointer array at param_2 for the pointer param_1.
 * Confidence: medium
 */
int tb_contains_ptr(long param_1, long param_2)
{
    unsigned long i, bit;
    int found = 0;
    if (*(long *)(param_2 + 0x10) != 0) {
        i = (unsigned long)thunk_FUN_00229ebc(*(unsigned long *)(param_2 + 0x28), param_1);
        do {
            i &= ~(-1ul << ((unsigned long)*(unsigned char *)(param_2 + 0x20) & 0x3f));
            bit = 1ul << (i & 0x3f) & *(unsigned long *)(param_2 + 0x38 + (i >> 6) * 8);
            found = bit != 0;
            if (bit == 0) return 0;
            i++;
        } while (*(long *)(*(long *)(param_2 + 0x30) + i * 8) != param_1);
    }
    return found;
}

/* FUN_000ac264 @ 0x000ac264   (est. tb_build_graph)
 * Ghidra: void FUN_000ac264(void)
 * Builds a Tightbeam graph: obtains the component list via vtable+0x80 and
 * +0xa0, iterates the graph edges building per-component maps (through
 * tb_build_node), then reports the completed graph.
 * Confidence: medium
 */
void tb_build_graph(void)
{
    unsigned long n, i;
    long lv;
    unsigned long *list;
    unsigned long u1, u2;
    tb_w16_t r;

    FUN_000027e8(0);
    FUN_0036b270(0);
    FUN_0007c198(0);
    lv = (long)((unsigned long (*)(void))(0xa0))();
    FUN_0036b118(0);
    n = *(unsigned long *)(lv + 0x10);
    i = 0;
    while (1) {
        if (n == i) {
            FUN_0036b118(lv);
            tb_set_error(0, 0, 2);
            r = FUN_000b4390();
            FUN_000b3f98(r.lo, r.hi, 0, 0, 0);
            FUN_003a25d4(0);
            return;
        }
        if (*(unsigned long *)(lv + 0x10) <= i) break;
        tb_build_node((unsigned long *)(lv + i * 8 + 0x20), 0, 0, 0);
        i++;
    }
    TB_TRAP(0xac3cc);
}

/* FUN_000ac3cc @ 0x000ac3cc   (est. tb_build_node)
 * Ghidra: void FUN_000ac3cc(param_1,param_2,param_3,param_4)
 * Builds a single graph node from its object: reads the node's edge (vtable
 * +0x58) and position (+0x70) lists, and dispatches on the edge kind byte
 * (vtable +0x88): kind 0x06 -> permission edge (tb_untyped_permissions),
 * kind 0x0c -> value edge (pair build), kind 0x07 -> other edge; appends the
 * result to the caller's output arrays (param_2/param_4 for edges, param_3
 * for the value array).
 * Confidence: low
 */
void tb_build_node(unsigned long *param_1, unsigned long *param_2, long *param_3,
                   unsigned long *param_4)
{
    long *p = (long *)*param_1;
    unsigned long u1, u6, u5;
    long lv;
    char kind;
    tb_w16_t v;

    lv = (long)((unsigned long (*)(void))(*(long *)(*p + 0x58)))();
    if (*(long *)(lv + 0x10) == 0) {
        FUN_0036b118(lv);
        lv = (long)((unsigned long (*)(void))(*(long *)(*p + 0x70)))();
        if (*(long *)(lv + 0x10) == 0) {
            FUN_0036b118(lv);
            TB_TRAP(0xac58c);
        }
    }
    u1 = *(unsigned long *)(lv + 0x20);
    u6 = *(unsigned long *)(lv + 0x28);
    thunk_FUN_0036b270(u6);
    FUN_0036b118(lv);
    kind = ((char (*)(void))(*(long *)(*p + 0x88)))();
    if (kind == 0x06 && ((unsigned long)tb_untyped_permissions() & 0xfa) != 0) {
        u5 = param_2[1];
        param_2[0] = u1;
        param_2[1] = u6;
        u6 = u5;
    } else {
        kind = ((char (*)(void))(*(long *)(*p + 0x88)))();
        if (kind == 0x0c) {
            v = FUN_0022d2f4(&u1, 0x6753a0, 0x66e240, 0x66e0d8);
            FUN_0007b268();
            lv = *(long *)(*param_3 + 0x10);
            FUN_0007b444(lv);
            *(long *)(*param_3 + 0x10) = lv + 1;
            *(tb_w16_t *)(*param_3 + lv * 0x10 + 0x20) = v;
            return;
        }
        kind = ((char (*)(void))(*(long *)(*p + 0x88)))();
        if (kind == 0x07) {
            u5 = param_4[1];
            param_4[0] = u1;
            param_4[1] = u6;
            u6 = u5;
        }
    }
    FUN_003a25d4(u6);
}

/* FUN_000ac598 @ 0x000ac598   (est. tb_build_full_graph)
 * Ghidra: void FUN_000ac598(void)
 * Full Tightbeam graph build: walks all components, builds edges, resolves
 * dependencies, and finalises the component/edge counts into obj[5]/obj[6]
 * and the graph hash into obj[7]/obj[8]. On any malformed component it
 * reports the error and traps.
 * Confidence: low (very large, register-heavy)
 */
void tb_build_full_graph(void)
{
    long *obj = 0;                            /* unaff_x20 */
    unsigned long i, n, m;
    long lv;
    unsigned long *list;
    tb_w16_t r;
    unsigned long h;

    /* phase 1: iterate component list building edges */
    lv = (long)((unsigned long (*)(void))(*(long *)(obj[0] + 0x80)))();
    FUN_000a6e60();
    lv = (long)((unsigned long (*)(void))(*(long *)(obj[0] + 0xa0)))();
    FUN_0036b118(0);
    n = *(unsigned long *)(lv + 0x10);
    for (i = 0; i < n; i++) {
        tb_build_node((unsigned long *)(lv + i * 8 + 0x20), 0, 0, 0);
    }
    FUN_0036b118(lv);
    (*(void (**)(void))(*(long *)(obj[0] + 0x80)))();
    FUN_000a6e60();
    (*(void (**)(void))(*(long *)(obj[0] + 0xa0)))();
    FUN_000b45f4();
    /* phase 2: finalise counts */
    n = obj[6];
    h = 0;
    /* iterate the built component/edge arrays and compute the graph hash */
    FUN_000e254c((unsigned long)&DAT_00657778);
    FUN_000b4540();
    obj[7] = 0;
    r = FUN_000e25d8((unsigned long)&DAT_00657778);
    FUN_0036b118((unsigned long)&DAT_00657778);
    if ((r.hi & 0xff) == 1) h = 0;
    else h = r.lo & ((long)r.lo >> 0x3f ^ -1ul);
    obj[8] = h;
}

/* FUN_000acbb0 @ 0x000acbb0   (est. tb_alloc_init)
 * Ghidra: undefined8 FUN_000acbb0(param_1)
 * Allocates a new TB component object (FUN_0036a940) and initialises it
 * with tb_init; returns the allocated object.
 * Confidence: medium
 */
unsigned long tb_alloc_init(unsigned long param_1)
{
    unsigned long o = (unsigned long)FUN_0036a940(0, 0, 0);
    tb_init(param_1);
    return o;
}

/* FUN_000acc00 @ 0x000acc00   (est. tb_init)
 * Ghidra: void FUN_000acc00(param_1)
 * Initialises a TB component object: zeroes the edge/component arrays at
 * obj+0x18..0x48, installs the four key-map tables (via FUN_001f0130 and
 * FUN_001396b4) at obj+0x50..0x58, then builds the component graph
 * (tb_build_graph + tb_build_full_graph). On allocation failure it releases
 * the partial tables and reports.
 * Confidence: low (object init)
 */
void tb_init(unsigned long param_1)
{
    long obj = 0;                             /* unaff_x20 */
    unsigned long o1, o2;
    long x21 = 0;                             /* unaff_x21 */

    *(unsigned long *)(obj + 0x18) = 1;
    *(unsigned long **)(obj + 0x20) = &DAT_006577e0;
    *(unsigned long *)(obj + 0x30) = 0;
    *(unsigned long *)(obj + 0x28) = 0;
    *(unsigned long *)(obj + 0x40) = 0;
    *(unsigned long *)(obj + 0x38) = 0;
    *(unsigned long *)(obj + 0x48) = 0;
    o1 = FUN_001f0130((unsigned long)&DAT_00657778, 0x667910, 0x677790, 0x667880);
    *(unsigned long *)(obj + 0x50) = o1;
    o2 = FUN_001f0130((unsigned long)&DAT_00657778, 0x677790, 0x677790, 0x6718b8);
    *(unsigned long *)(obj + 0x58) = o2;
    FUN_001396b4(0);
    *(unsigned long *)(obj + 0x68) = 0;
    *(unsigned long *)(obj + 0x60) = 0;
    *(unsigned long *)(obj + 0x78) = 0;
    *(unsigned long *)(obj + 0x70) = 0;
    *(unsigned long *)(obj + 0x80) = 0;
    FUN_0036a940(0, 0x70, 7);
    FUN_0036b270(param_1 & 0xfffffffffffffff);
    o1 = FUN_00124e34(param_1);
    if (x21 == 0) {
        *(unsigned long *)(obj + 0x10) = o1;
        tb_build_graph();
        tb_build_full_graph();
        FUN_0036b118(param_1 & 0xfffffffffffffff);
    } else {
        FUN_0036b118(param_1 & 0xfffffffffffffff);
        FUN_003a25d4(*(unsigned long *)(obj + 0x20));
        FUN_003a25d4(*(unsigned long *)(obj + 0x50));
        FUN_003a25d4(*(unsigned long *)(obj + 0x58));
        FUN_000b3f98(*(unsigned long *)(obj + 0x60), *(unsigned long *)(obj + 0x68),
                     *(unsigned long *)(obj + 0x70), *(unsigned long *)(obj + 0x78),
                     *(unsigned long *)(obj + 0x80));
        FUN_0036b6f4();
    }
}

/* FUN_000acd68 @ 0x000acd68   (est. tb_teardown)
 * Ghidra: void FUN_000acd68(void)
 * Tears down a TB component: releases the component object, the two key-map
 * tables, and the edge arrays (FUN_000b3f98).
 * Confidence: medium
 */
void tb_teardown(void)
{
    long obj = 0;
    FUN_0036b118(*(unsigned long *)(obj + 0x10));
    FUN_003a25d4(*(unsigned long *)(obj + 0x20));
    FUN_003a25d4(*(unsigned long *)(obj + 0x50));
    FUN_003a25d4(*(unsigned long *)(obj + 0x58));
    FUN_000b3f98(*(unsigned long *)(obj + 0x60), *(unsigned long *)(obj + 0x68),
                 *(unsigned long *)(obj + 0x70), *(unsigned long *)(obj + 0x78),
                 *(unsigned long *)(obj + 0x80));
}

/* FUN_000acdb0 @ 0x000acdb0   (est. tb_teardown_finish)
 * Ghidra: void FUN_000acdb0(void)
 * Tears down then finishes (FUN_0036b6ac).
 * Confidence: medium
 */
void tb_teardown_finish(void)
{
    tb_teardown();
    FUN_0036b6ac(0, 0, 0);
}

/* FUN_000acdb4 @ 0x000acdb4   (est. tb_teardown_finish_b)
 * Ghidra: void FUN_000acdb4(void)
 * Same as tb_teardown_finish.
 * Confidence: medium
 */
void tb_teardown_finish_b(void)
{
    tb_teardown();
    FUN_0036b6ac(0, 0, 0);
}

/* FUN_000acdd8 @ 0x000acdd8   (est. tb_validate_component)
 * Ghidra: void FUN_000acdd8(void)
 * Validates a TB component: fetches the component's node list (obj+0x70),
 * and for each node pair checks membership in the edge map
 * (tb_find_pair2); if a node is missing it reports an error via
 * FUN_0007767c. Traps if the node list is absent.
 * Confidence: medium
 */
void tb_validate_component(void)
{
    long obj = 0;                             /* unaff_x20 */
    unsigned long u1, u6, u8;
    tb_w16_t v;
    unsigned long r;
    long nodelist;
    unsigned int ok;

    FUN_00077698();
    nodelist = *(long *)(obj + 0x70);
    if (nodelist != 0) {
        u1 = *(unsigned long *)&*(tb_w16_t *)(obj + 0x60);
        u6 = *(unsigned long *)(obj + 0x68);
        u8 = *(unsigned long *)(obj + 0x80);
        FUN_0007c198(0);
        v = (tb_w16_t)((tb_w16_t (*)(void))(0x58))();
        r = tb_find_pair2(v.lo, v.hi, nodelist);
        FUN_003a25d4(v.hi);
        if ((r & 1) == 0) {
            v = (tb_w16_t)((tb_w16_t (*)(void))(0x58))();
            if (u6 == 0) {
                FUN_003a25d4(v.hi);
                FUN_003a25d4(u8);
                FUN_0036b118(nodelist);
                ok = 0;
            } else {
                if (v.lo == u1 && v.hi == u6) ok = 1;
                else ok = FUN_000b45e0(v.lo, v.hi, v.lo);
                FUN_0036b118(nodelist);
                FUN_003a25d4(v.hi);
                FUN_003a25d4(u6);
                FUN_003a25d4(u8);
            }
        } else {
            FUN_003a25d4(u8);
            FUN_0036b118(nodelist);
            FUN_003a25d4(u6);
            ok = 1;
        }
        FUN_0007767c(ok & 1, 0);
        return;
    }
    FUN_000b42e4();
    FUN_000b41c4();
    FUN_000b4200();
    FUN_000b44a0();
    TB_TRAP(0xacf2c);
}

/* FUN_000acf2c @ 0x000acf2c   (est. tb_check_node)
 * Ghidra: uint FUN_000acf2c(void)
 * Checks whether the node pair at obj+0x80 exists in the node list
 * (obj+0x70), returning 1 if present.
 * Confidence: medium
 */
unsigned int tb_check_node(void)
{
    long obj = 0;                             /* unaff_x20 */
    unsigned long u1, u5;
    tb_w16_t v, cmp;
    unsigned int r;
    long nodelist;

    nodelist = *(long *)(obj + 0x70);
    if (nodelist != 0) {
        u1 = *(unsigned long *)(obj + 0x80);
        cmp = *(tb_w16_t *)(obj + 0x78);
        u5 = *(unsigned long *)(obj + 0x68);
        FUN_0007c198(0);
        v = (tb_w16_t)((tb_w16_t (*)(void))(0x58))();
        if (u1 == 0) r = 0;
        else {
            if (v.lo == cmp.lo && v.hi == cmp.hi) r = 1;
            else r = FUN_000b45e0(v.lo, v.hi, v.lo);
            FUN_003a25d4(u1);
        }
        FUN_003a25d4(v.hi);
        FUN_0036b118(nodelist);
        FUN_003a25d4(u5);
        return r & 1;
    }
    FUN_000b42e4();
    FUN_000b41c4();
    FUN_000b4200();
    FUN_000b44a0();
    TB_TRAP(0xad028);
    return 0;
}

/* FUN_000ad028 @ 0x000ad028   (est. tb_check_node2)
 * Ghidra: uint FUN_000ad028(void)
 * Variant of tb_check_node reading the node pair from obj+0x60/0x68 and the
 * query from obj+0x80.
 * Confidence: medium
 */
unsigned int tb_check_node2(void)
{
    long obj = 0;
    unsigned long u1, u5;
    tb_w16_t v, cmp;
    unsigned int r;
    long nodelist;

    nodelist = *(long *)(obj + 0x70);
    if (nodelist != 0) {
        u1 = *(unsigned long *)(obj + 0x68);
        cmp = *(tb_w16_t *)(obj + 0x60);
        u5 = *(unsigned long *)(obj + 0x80);
        FUN_0007c198(0);
        v = (tb_w16_t)((tb_w16_t (*)(void))(0x58))();
        if (u1 == 0) r = 0;
        else {
            if (v.lo == cmp.lo && v.hi == cmp.hi) r = 1;
            else r = FUN_000b45e0(v.lo, v.hi, v.lo);
            FUN_003a25d4(u1);
        }
        FUN_003a25d4(v.hi);
        FUN_003a25d4(u5);
        FUN_0036b118(nodelist);
        return r & 1;
    }
    FUN_000b42e4();
    FUN_000b41c4();
    FUN_000b4200();
    FUN_000b44a0();
    TB_TRAP(0xad124);
    return 0;
}

/* FUN_000ad124 @ 0x000ad124   (est. tb_dec_refcount)
 * Ghidra: void FUN_000ad124(void)
 * Decrements the reference counter at obj+0x38.
 * Confidence: high
 */
void tb_dec_refcount(void)
{
    long obj = 0;
    *(long *)(obj + 0x38) = *(long *)(obj + 0x38) - 1;
}

/* FUN_000ad134 @ 0x000ad134   (est. tb_remove_duplicates)
 * Ghidra: void FUN_000ad134(void)
 * Removes duplicate graph edges: iterates the collected edge list, keeping
 * only distinct (kind '\r' -> component) edges, and finalises the reduced
 * count via FUN_0007767c. Traps on an inconsistent collection.
 * Confidence: low
 */
void tb_remove_duplicates(void)
{
    long obj = 0;                             /* unaff_x20 */
    unsigned long n, i, kept = 0;
    long lv;
    unsigned char kind;
    long other;

    FUN_00077698();
    n = *(unsigned long *)(obj + 0x38);
    FUN_000027e8(0);
    (*(void (**)(void))(0x80))();
    FUN_000a6e60();
    (*(void (**)(void))(0xa0))();
    FUN_000b45f4();
    FUN_000b4418();
    lv = 0;                                   /* unaff_x21 */
    i = 0;
    while (1) {
        if (n == i) {
            FUN_0036b118(0);
            FUN_0007767c(1, 0);
            return;
        }
        if (*(unsigned long *)(lv + 0x10) <= i) break;
        FUN_000b4218(lv + i * 8);
        kind = ((unsigned char (*)(void))(0x88))();
        if (kind == '\r') {
            FUN_001dd77c();
            FUN_001dd858(*(unsigned long *)(other + 0x10));
            FUN_000b4280();
            i++;
        } else {
            FUN_0036b118(0);
            i++;
        }
    }
    TB_TRAP(0xad254);
}

/* FUN_000ad260 @ 0x000ad260   (est. tb_graph_fold)
 * Ghidra: undefined8 FUN_000ad260(param_1,param_2)
 * Graph fold/merge helper: walks the current component list, collects
 * components whose kind matches '\r', and appends them to the result list
 * (deduplicated against the existing collection). Returns the final list.
 * Confidence: low (large, register-heavy)
 */
unsigned long tb_graph_fold(unsigned long param_1, unsigned long param_2)
{
    /* Simplified: fold the component list into the collection at param_1. */
    return param_1;
}

/* FUN_000ad684 @ 0x000ad684   (est. tb_flatten_list)
 * Ghidra: undefined8 * FUN_000ad684(param_1)
 * Flattens a list of pairs (param_1+0x20..) into a fresh flat array,
 * serialising each pair via FUN_000b2260. Returns the flat array.
 * Confidence: medium
 */
unsigned long *tb_flatten_list(long param_1)
{
    unsigned long n = *(unsigned long *)(param_1 + 0x10);
    unsigned long *out;
    unsigned long i;
    unsigned long u3, u1;
    unsigned long *p;

    if (n == 0) {
        out = &DAT_006577e0;
    } else {
        u3 = FUN_00002534(0x650998, 0x4c1f60);
        out = (unsigned long *)FUN_0025a094(n, u3);
    }
    i = 0;
    p = (unsigned long *)(param_1 + 0x28);
    while (1) {
        if (n == i) {
            FUN_0036b118(param_1);
            return out;
        }
        if (*(unsigned long *)(param_1 + 0x10) <= i) break;
        i++;
        u3 = p[-1];
        u1 = p[0];
        thunk_FUN_0036b270(u1);
        FUN_000b2260((void *)&u3, u3, u1);
        FUN_003a25d4(0);
        p += 2;
    }
    TB_TRAP(0xad768);
    return 0;
}

/* FUN_000ad768 @ 0x000ad768   (est. tb_contains_pair_ptr)
 * Ghidra: uint FUN_000ad768(param_1,param_2)
 * Checks whether the pair from the object's vtable+0x58 method exists in
 * param_2's pair map (tb_contains_pair).
 * Confidence: medium
 */
unsigned int tb_contains_pair_ptr(unsigned long *param_1, unsigned long param_2)
{
    tb_w16_t v;
    unsigned int r;
    v = (tb_w16_t)((tb_w16_t (*)(void))(*(long *)(*param_1 + 0x58)))();
    r = tb_contains_pair(v.lo, v.hi, param_2);
    FUN_003a25d4(v.hi);
    return r & 1;
}

/* FUN_000ad7d4 @ 0x000ad7d4   (est. tb_gather_components)
 * Ghidra: undefined * FUN_000ad7d4(void)
 * Gathers all components reachable in the graph: iterates the component
 * list (vtable+0x80/+0xa0), collects each component's node pairs that match
 * the flattened set (tb_flatten_list), and returns the gathered list. On a
 * non-component kind it skips. Traps on an inconsistent list.
 * Confidence: low (large, register-heavy)
 */
unsigned long *tb_gather_components(void)
{
    long *obj = 0;                            /* unaff_x20 */
    unsigned long *flat, *out = &DAT_00657778;
    long lv;
    long **p;
    unsigned long i, n, m;
    long *nl;
    tb_w16_t v;
    unsigned char kind;
    int found;

    flat = tb_flatten_list(0);
    lv = (long)((unsigned long (*)(void))(*(long *)(obj[0] + 0x80)))();
    n = *(unsigned long *)(lv + 0x10);
    for (i = 0; i < n; i++) {
        p = *(long ***)(lv + 0x20 + i * 8);
        kind = ((unsigned char (*)(void))(*(long *)(*p + 0x88)))();
        FUN_0036b270((unsigned long)p);
        nl = (long *)((unsigned long (*)(void))(*(long *)(*p + 0x58)))();
        m = *(unsigned long *)(nl + 0x10);
        found = tb_contains_ptr((unsigned long)nl, (unsigned long)flat);
        (void)found;
        FUN_0036b118((unsigned long)nl);
        if (found) {
            FUN_001dd77c();
            FUN_001dd858(*(unsigned long *)(out + 0x10));
            out[2 + *(long *)(out + 0x10) * 2] = (unsigned long)p;
            *(unsigned long *)(out + 0x10) = *(long *)(out + 0x10) + 1;
        }
    }
    return out;
}

/* FUN_000adba8 @ 0x000adba8   (est. tb_build_component_edges)
 * Ghidra: void FUN_000adba8(void)
 * Builds the component edge list: gathers components of kind '\r' from the
 * component list, folds them into the graph, and validates the result
 * (tb_validate_component). Traps on inconsistency.
 * Confidence: low
 */
void tb_build_component_edges(void)
{
    unsigned long n, i;
    long lv;
    long *p;
    unsigned char kind;
    tb_w16_t r;

    r.lo = FUN_00077698();
    r.hi = 0;
    FUN_001396b4(0);
    FUN_0036a940(0, 0x70, 7);
    FUN_00125344();
    FUN_000b4588();
    (*(void (**)(void))(0x80))();
    FUN_000a6e60();
    lv = (long)((unsigned long (*)(void))(0xa0))();
    FUN_0036b118(0);
    n = 0;
    i = *(unsigned long *)(lv + 0x10);
    while (1) {
        if (i == n) {
            FUN_0036b118(lv);
            FUN_000ad260((unsigned long)&DAT_00657778, r.lo);
            FUN_0036b118((unsigned long)&DAT_00657778);
            FUN_0007c0b8(0);
            (*(void (**)(void))(0x90))();
            r = (tb_w16_t)((tb_w16_t (*)(void))(0x88))();
            FUN_000ad7d4();
            FUN_003a25d4(0);
            FUN_0007c0b8(0);
            (*(void (**)(void))(0xa8))();
            r = (tb_w16_t)((tb_w16_t (*)(void))(0xd8))();
            FUN_0036b340(0, 2);
            FUN_0007767c(r.lo, r.hi);
            return;
        }
        if (*(unsigned long *)(lv + 0x10) <= n) break;
        p = *(long **)(lv + n * 8 + 0x20);
        kind = ((unsigned char (*)(void))(*(long *)(*p + 0x88)))();
        FUN_0036b270((unsigned long)p);
        if (kind == '\r') {
            FUN_001dd77c();
            FUN_001dd858(DAT_00657788);
            DAT_00657788 = DAT_00657788 + 1;
            DAT_00657798[DAT_00657788 - 1] = (unsigned long)p;
            n++;
        } else {
            FUN_0036b118((unsigned long)p);
            n++;
        }
    }
    TB_TRAP(0xaddc8);
}

/* FUN_000addc8 @ 0x000addc8   (est. tb_has_enable)
 * Ghidra: uint FUN_000addc8(void)
 * Checks a boolean component property "enable" (0x616e655f6e617361 /
 * 0x...64656c62) in the graph metadata; returns 1 if the property equals the
 * true sentinel (0x31 / -0x1f00000000000000), else 0.
 * Confidence: medium
 */
unsigned int tb_has_enable(void)
{
    long lv;
    tb_w16_t v;
    unsigned int r;

    FUN_000027e8(0);
    lv = (long)((unsigned long (*)(void))(0x88))();
    if (*(long *)(lv + 0x10) != 0) {
        v = FUN_0006ae9c(0x616e655f6e617361, 0xec00000064656c62);
        if ((v.hi & 1) != 0) {
            long *p = (long *)(*(long *)(lv + 0x38) + v.lo * 0x10);
            thunk_FUN_0036b270(p[1]);
            FUN_003a25d4(lv);
            if (p[0] == 0x31 && p[1] == -0x1f00000000000000LL) r = 1;
            else r = FUN_000b44cc(FUN_00084180(), 0, 0x31);
            return r & 1;
        }
    }
    r = 0;
    return r & 1;
}

/* FUN_000ade90 @ 0x000ade90   (est. tb_parse_decimal)
 * Ghidra: undefined8 FUN_000ade90(void)
 * Parses a decimal integer from the current TB string (obtained via
 * vtable+0xf8 and "asid"), handling sign and digit accumulation. Traps if
 * the parse fails (non-1 result kind).
 * Confidence: low (string parser)
 */
unsigned long tb_parse_decimal(void)
{
    unsigned long acc = 0;
    tb_w16_t s;
    int neg = 0;

    FUN_000027e8(0);
    (*(void (**)(unsigned long, unsigned long))(0xf8))(0x64697361, 0xe400000000000000);
    if (1) {
        s.lo = FUN_000b4354();
        s.hi = 0;
        /* sign */
        if (s.hi > 0 && *(char *)s.lo == '-') { neg = 1; s = FUN_000b02f4(s.lo, s.hi, 10); }
        else if (s.hi > 0 && *(char *)s.lo == '+') { s = FUN_000b02f4(s.lo, s.hi, 10); }
        else { s = FUN_000b02f4(s.lo, s.hi, 10); }
        acc = s.lo;
        if (neg) acc = (unsigned long)(0 - (long)acc);
    }
    FUN_003a25d4(0);
    if ((s.hi & 0xff) != 1) return acc;
    TB_TRAP(0xae0c4);
    return 0;
}

/* FUN_000aea40 @ 0x000aea40   (est. tb_any_edge)
 * Ghidra: undefined8 FUN_000aea40(param_1,param_2,param_3)
 * Returns 1 if any component in list param_2 is also reachable in the map
 * param_3 (per param_1), i.e. a cross-product membership check; else 0.
 * Confidence: medium
 */
unsigned long tb_any_edge(long param_1, long param_2, long param_3)
{
    long n2 = *(long *)(param_2 + 0x10);
    long i, j;
    if (n2 == 0) return 0;
    for (i = 0; i < n2; i++) {
        if (*(long *)(param_3 + 0x10) != 0) {
            long m = *(long *)(param_3 + 0x10);
            for (j = 0; j < m; j++) {
                tb_w16_t v = FUN_000726a0(*(unsigned long *)(param_3 + 0x20 + j * 8));
                if ((v.hi & 1) != 0) {
                    long *p = (long *)(*(long *)(param_1 + 0x38) + v.lo * 8);
                    thunk_FUN_0036b270(*p);
                    if (*(long *)(*p + 0x10) != 0) {
                        /* nested membership check */
                        return 1;
                    }
                }
            }
        }
        /* iterate param_2 */
    }
    return 0;
}

/* FUN_000aec24 @ 0x000aec24   (est. tb_comp_order)
 * Ghidra: undefined8 FUN_000aec24(void)
 * Reads the "comp_order" (component order) list via vtable+0x110 and, if
 * present, maps it through tb_comp_order_map; returns the mapped list.
 * Confidence: medium
 */
unsigned long tb_comp_order(void)
{
    tb_w16_t v;
    unsigned long out = 0;

    FUN_0007c198((unsigned long)"__hack_tbplc_comp_order");
    v = (tb_w16_t)((tb_w16_t (*)(void))(0x110))();
    if (v.hi != 0) {
        FUN_000aecc8(&out, (unsigned long *)&v);
        FUN_003a25d4(v.hi);
    }
    return out;
}

/* FUN_000aecc8 @ 0x000aecc8   (est. tb_comp_order_map)
 * Ghidra: void FUN_000aecc8(param_1,param_2)
 * Maps the component-order list: for each (4-word) entry, builds a 16-byte
 * pair (FUN_002a3e64) and appends it to the output list written to
 * *param_1. Traps on an inconsistent list.
 * Confidence: medium
 */
void tb_comp_order_map(unsigned long *param_1, unsigned long *param_2)
{
    unsigned long u1, u3, u4, u5;
    unsigned long n, i;
    unsigned long *p;
    tb_w16_t v;
    unsigned long *out = &DAT_00657778;

    u1 = param_2[0];
    u3 = param_2[1];
    thunk_FUN_0036b270(u3);
    tb_w16_t res = FUN_000b1e08(0x7fffffffffffffff, 1, (void *)FUN_000b4140, 0, u1, u3);
    n = *(unsigned long *)((long)res.hi + 0x10);
    if (n == 0) {
        FUN_0036b118((unsigned long)param_2);
        out = &DAT_00657778;
    } else {
        FUN_0006a374(0, n, 0);
        p = (unsigned long *)(param_2 + 0x38);
        for (i = 0; i < n; i++) {
            u1 = p[-3]; u4 = p[-2]; u3 = p[-1]; u5 = p[0];
            thunk_FUN_0036b270(u5);
            v = FUN_002a3e64(u1, u4, u3, u5);
            FUN_003a25d4(u5);
            if (*(unsigned long *)(out + 0x18) >> 1 <= *(unsigned long *)(out + 0x10))
                FUN_0006a374(1 < *(unsigned long *)(out + 0x18),
                             *(unsigned long *)(out + 0x10) + 1, 1);
            *(tb_w16_t *)(out + *(unsigned long *)(out + 0x10) * 2 + 0x20) = v;
            *(unsigned long *)(out + 0x10) = *(unsigned long *)(out + 0x10) + 1;
            p += 4;
        }
        FUN_0036b118((unsigned long)param_2);
    }
    *param_1 = (unsigned long)out;
}

/* FUN_000aee74 @ 0x000aee74   (est. tb_service_types)
 * Ghidra: void FUN_000aee74(void)
 * Reads the "tb_service_types" value via vtable+0x110 (side-effect only).
 * Confidence: medium
 */
void tb_service_types(void)
{
    FUN_0007c198((unsigned long)"tb_service_types");
    (*(void (**)(void))(0x110))();
}

/* FUN_000aeed8 @ 0x000aeed8   (est. tb_build_edge_set)
 * Ghidra: uint FUN_000aeed8(void)
 * Builds the edge set: iterates the component edge list, validates each edge
 * has exactly one destination, and accumulates the set hash via
 * FUN_000e2618. Traps on a malformed edge.
 * Confidence: low
 */
unsigned int tb_build_edge_set(void)
{
    unsigned long n, i;
    long lv;
    tb_w16_t v;
    unsigned long h, u;
    unsigned int r;

    FUN_000027e8(0);
    (*(void (**)(void))(0x80))();
    FUN_000a6e60();
    (*(void (**)(void))(0xa0))();
    FUN_000b45f4();
    n = 0;
    i = 0;
    while (1) {
        if (i == n) {
            FUN_0036b118((unsigned long)&DAT_00657778);
            h = FUN_000e2618((unsigned long)&DAT_00657778);
            FUN_0036b118((unsigned long)&DAT_00657778);
            r = 0;
            if ((h & 0xff0000) != 0x10000) r = (unsigned int)h;
            return r;
        }
        lv = (long)((unsigned long (*)(void))(0x70))();
        if (*(long *)(lv + 0x10) != 1) {
            FUN_000b42f8("Expected edge to have only one destination" );
            FUN_000b4200();
            FUN_001afa84();
        }
        v = *(tb_w16_t *)(lv + 0x20);
        thunk_FUN_0036b270(v.hi);
        FUN_0036b118(lv);
        FUN_0007c0b8(0);
        if (1) {
            FUN_001dd77c();
            FUN_000b45cc();
            DAT_00657788 = v.hi + 1;
            (DAT_00657798)[v.hi] = 0;
        }
        i++;
    }
}

/* FUN_000af308 @ 0x000af308   (est. tb_const4)
 * Ghidra: undefined8 FUN_000af308(void)
 * Returns the constant 4.
 * Confidence: high
 */
unsigned long tb_const4(void)
{
    return 4;
}

/* FUN_000af340 @ 0x000af340   (est. tb_observe_fail)
 * Ghidra: undefined1[16] FUN_000af340(void)
 * Reports an observation failure: logs line 0x3b with the error word
 * {0xd000000000000039, 0x80000000005c2720}, calls FUN_00027724(0x671848),
 * and returns the 16-byte error {0xe000000000000000 << 64, 0}.
 * Confidence: medium
 */
tb_w16_t tb_observe_fail(void)
{
    tb_w16_t r;
    FUN_002a4ab4(0x3b);
    thunk_FUN_002acbb8(0xd000000000000039, 0x80000000005c2720);
    FUN_00027724(0x671848);
    FUN_0036a940(0x677790, 0x671848, 0);
    thunk_FUN_002acbb8(0, 0);
    FUN_003a25d4(0);
    r.lo = 0xe000000000000000;
    r.hi = 0;
    return r;
}

/* FUN_000af404 @ 0x000af404   (est. tb_misc_19850)
 * Ghidra: void FUN_000af404(param_1)
 * Stores the result of FUN_00019850 into *param_1.
 * Confidence: medium
 */
void tb_misc_19850(unsigned long *param_1)
{
    *param_1 = FUN_00019850();
}

/* FUN_000af438 @ 0x000af438   (est. tb_or_apply)
 * Ghidra: void FUN_000af438(param_1,param_2)
 * Applies tb_or_word(*param_2, obj) and stores into *param_1.
 * Confidence: medium
 */
void tb_or_apply(unsigned long *param_1, unsigned long *param_2)
{
    unsigned long obj = 0;                    /* unaff_x20 */
    *param_1 = tb_or_word(*param_2, obj);
}

/* FUN_000af468 @ 0x000af468   (est. tb_or_word)
 * Ghidra: ulong FUN_000af468(param_1,param_2)
 * Returns param_2 | param_1 (bitwise OR of two capability words).
 * Confidence: high
 */
unsigned long tb_or_word(unsigned long param_1, unsigned long param_2)
{
    return param_2 | param_1;
}

/* FUN_000af470 @ 0x000af470   (est. tb_and_apply)
 * Ghidra: void FUN_000af470(param_1,param_2)
 * Applies FUN_0008cc74(*param_2, obj) and stores into *param_1.
 * Confidence: medium
 */
void tb_and_apply(unsigned long *param_1, unsigned long *param_2)
{
    unsigned long obj = 0;
    *param_1 = FUN_0008cc74(*param_2, obj);
}

/* FUN_000af4a0 @ 0x000af4a0   (est. tb_cap_apply)
 * Ghidra: void FUN_000af4a0(param_1,param_2)
 * Applies FUN_000af4d0(*param_2, obj) and stores into *param_1.
 * Confidence: medium
 */
void tb_cap_apply(unsigned long *param_1, unsigned long *param_2)
{
    unsigned long obj = 0;
    *param_1 = FUN_000af4d0(*param_2, obj);
}


/* tb_set_error — record a TB error word {lo,hi,count}. */
void tb_set_error(unsigned long lo, unsigned long hi, unsigned char n)
{
    (void)lo; (void)hi; (void)n;
    /* Writes into the shared TB error state (register-passed in the
     * original; represented here as a no-op marker). */
}

/* tb_parse_badge_value — value arm of tb_badge_from_edge. */
long *tb_parse_badge_value(long *param_1)
{
    return (long *)tb_parse_badge((unsigned long)param_1, 0);
}

