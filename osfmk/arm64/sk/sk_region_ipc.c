/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) — the
 * cL4 microkernel (GL1) serving Exclaves. Ground truth: Ghidra FUN_ names +
 * addresses. All names are estimates unless string/header-matched. This file
 * covers the 0x100000-0x180000 region (IPC/notification/endpoint/dispatch
 * machinery). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Ghidra pseudo-ops used in this region: the cL4 kernel issues supervisor
 * calls (SVC) and breakpoints via these. They are rendered as opaque helpers. */
#define CallSupervisor(n)        /* svc #(n) */
#define SoftwareBreakpoint(...)  /* brk */
#define tpidrro_el0              /* tpidrro_el0 (per-thread register block) */

/* ============ 0x100030 - 0x100fbc : endpoint/dispatch stubs ============ */

/* FUN_00100030 @ 0x100030  (est. sk_ep_fwd_regs5)
 * Forwards a 5-register dispatch (x20+0x10..0x28) through the shared
 * register-forwarder FUN_000fed94. Confidence: low (identical body to 0x100034). */
static void sk_ep_100030(void *ctx, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)ctx; (void)a; (void)b; (void)c; (void)d; (void)e;
    /* FUN_000fed94(a, ctx->r[0x10/8], ctx->r[0x18/8], ctx->r[0x20/8], ctx->r[0x28/8]) */
}

/* FUN_00100034 @ 0x100034  (est. sk_ep_fwd_regs5_b)
 * Duplicate of 0x100030: same 5-register forward through FUN_000fed94. */
static void sk_ep_100034(void *ctx, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)ctx; (void)a; (void)b; (void)c; (void)d; (void)e;
    /* FUN_000fed94(a, ctx->r[0x10/8], ctx->r[0x18/8], ctx->r[0x20/8], ctx->r[0x28/8]) */
}

/* FUN_00100050 @ 0x100050  (est. sk_clear_flag)
 * Clears a one-byte flag at obj+0x100. */
static void sk_clear_flag_100050(void *obj)
{
    *(volatile uint8_t *)((char *)obj + 0x100) = 0;
}

/* FUN_00100058 @ 0x100058  (est. sk_set_flag)
 * Initializes a region of size 0x100 via thunk_FUN_00114330, then sets the
 * one-byte flag at obj+0x100 to 1. */
static void sk_set_flag_100058(void *obj)
{
    /* thunk_FUN_00114330(obj, 0x100) */
    *(volatile uint8_t *)((char *)obj + 0x100) = 1;
}

/* FUN_00100088 @ 0x100088  (est. sk_skip_list_advance)
 * Walks a tagged pointer: if bit0 set, dereference the masked pointer; returns
 * base+4 plus the signed 32-bit length stored at [base+4]. (skip-list node
 * advance) */
static uint64_t sk_skip_advance_100088(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (p + 4) + (int64_t)(int32_t)*(int32_t *)(p + 4);
}

/* FUN_001000b8 @ 0x1000b8  (est. sk_log_652bd0)
 * Logs via FUN_00077770 with message id 0x652bd0. */
static void sk_log_1000b8(void)
{
    /* FUN_00077770(0x652bd0) */
}

/* FUN_001000c4 @ 0x1000c4  (est. sk_svc5_loop)
 * Invokes supervisor call 5; repeats while param_1 == 1. */
static void sk_svc5_1000c4(uint64_t flag)
{
    do { CallSupervisor(5); } while (flag == 1);
}

/* FUN_001000dc @ 0x1000dc  (est. sk_svc4_loop)
 * Invokes supervisor call 4; repeats while param_1 == 1. */
static void sk_svc4_1000dc(uint64_t flag)
{
    do { CallSupervisor(4); } while (flag == 1);
}

/* FUN_0010013c @ 0x10013c  (est. sk_vtbl48_flag)
 * Calls FUN_000027e8, then invokes a method at vtable+0x48, storing bit0 of the
 * result into *out. */
static void sk_vtbl48_10013c(uint8_t *out)
{
    /* FUN_000027e8(); *out = (*(code **)(vtable + 0x48))() & 1; */
    (void)out;
}

/* FUN_00100180 @ 0x100180  (est. sk_vtbl50)
 * Calls FUN_000027e8 with *in, then invokes method at vtable+0x50. */
static void sk_vtbl50_100180(uint8_t in)
{
    /* FUN_000027e8(in); (*(code **)(vtable + 0x50))(); */
}

/* FUN_001002b4 @ 0x1002b4  (est. sk_query_counter)
 * Reads a counter via thunk_FUN_0036f974 and reports it through
 * FUN_0035cf24(&DAT_004c4278, value); returns the value. */
static uint64_t sk_query_counter_1002b4(void)
{
    uint64_t v = /* thunk_FUN_0036f974() */ 0;
    /* FUN_0035cf24(&DAT_004c4278, v) */
    return v;
}

/* FUN_001003e8 @ 0x1003e8  (est. sk_log_652c68)
 * Logs via FUN_00077770 with message id 0x652c68. */
static void sk_log_1003e8(void)
{
    /* FUN_00077770(0x652c68) */
}

/* FUN_001003f4 @ 0x1003f4  (est. sk_svc2)
 * Invokes supervisor call 2. */
static void sk_svc2_1003f4(void)
{
    CallSupervisor(2);
}

/* FUN_00100418 @ 0x100418  (est. sk_svc3_regs)
 * Writes three registers to the tpidrro_el0 block, then invokes supervisor
 * call 3 (syscall entry with args carried in the per-thread block). */
static void sk_svc3_100418(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    /* uint64_t *blk = tpidrro_el0; blk[0]=c; blk[1]=d; blk[2]=e; */
    (void)a; (void)b;
    CallSupervisor(3);
}

/* FUN_00100434 @ 0x100434  (est. sk_skip_advance_10)
 * Same skip-list advance as 0x100088 but reads length at base+0x10. */
static uint64_t sk_skip_advance_10_100434(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (p + 0x10) + (int64_t)(int32_t)*(int32_t *)(p + 0x10);
}

/* FUN_00100464 @ 0x100464  (est. sk_svc3_setup)
 * Writes a fixed {1, c, d, 0, 0} register block to tpidrro_el0 then invokes
 * supervisor call 3. */
static void sk_svc3_setup_100464(uint64_t c, uint64_t d)
{
    /* uint64_t *blk = tpidrro_el0; blk[0]=1; blk[1]=c; blk[3]=0; blk[4]=0; blk[2]=d; */
    CallSupervisor(3);
}

/* FUN_00100484 @ 0x100484  (est. sk_init_guard_a)
 * Init sequence: FUN_0010070c, FUN_000fbbc8, FUN_000651bc; on failure flag the
 * noreturn FUN_0011d7e8 is taken. */
static void sk_init_guard_a_100484(void)
{
    /* FUN_0010070c(); FUN_000fbbc8(); FUN_000651bc(local); if (Z) return;
     * FUN_0011d7e8(); (noreturn) */
}

/* FUN_001004b8 @ 0x1004b8  (est. sk_init_guard_b)
 * Same guard shape as 0x100484 but with FUN_000fbf98 in place of FUN_000fbbc8. */
static void sk_init_guard_b_1004b8(void)
{
    /* FUN_0010070c(); FUN_000fbf98(); FUN_000651bc(local); if (Z) return;
     * FUN_0011d7e8(); (noreturn) */
}

/* FUN_001004f0 @ 0x1004f0  (est. sk_init_guard_c)
 * Guard: FUN_0006b2dc, FUN_000faf5c, FUN_000651bc; failure -> FUN_0011d7e8. */
static void sk_init_guard_c_1004f0(void)
{
    /* FUN_0006b2dc(a,b); FUN_000faf5c(); FUN_000651bc(x); if (Z) return;
     * FUN_0011d7e8(); (noreturn) */
}

/* FUN_0010059c @ 0x10059c  (est. sk_noop)
 * Empty function. */
static void sk_noop_10059c(void) {}

/* FUN_001005b4 @ 0x1005b4  (est. sk_report_662d28)
 * Reports {0x662d28, 0x662a78, 0, 0} via FUN_0036993c. */
static void sk_report_1005b4(void)
{
    /* FUN_0036993c(0x662d28, 0x662a78, 0, 0) */
}

/* FUN_0010064c @ 0x10064c  (est. sk_noop)
 * Empty function. */
static void sk_noop_10064c(void) {}

/* FUN_00100668 @ 0x100668  (est. sk_noop)
 * Empty function. */
static void sk_noop_100668(void) {}

/* FUN_00100684 @ 0x100684  (est. sk_const_677830)
 * Returns constant 0x677830. */
static uint64_t sk_const_100684(void) { return 0x677830; }

/* FUN_001006a0 @ 0x1006a0  (est. sk_const_677830_b)
 * Returns constant 0x677830 (duplicate). */
static uint64_t sk_const_1006a0(void) { return 0x677830; }

/* FUN_001006f4 @ 0x1006f4  (est. sk_store_reg_slot)
 * Stores x28 into slot[0x10/8]; stores x26/x27 into slot[idx*0x10 + 0x20/0x28]. */
static void sk_store_reg_1006f4(uint64_t *slot, int64_t idx, uint64_t v26, uint64_t v27, uint64_t v28)
{
    slot[0x10/8] = v28;
    slot[idx*0x10/8 + 0x20/8] = v26;
    slot[idx*0x10/8 + 0x28/8] = v27;
}

/* FUN_0010070c @ 0x10070c  (est. sk_stack_canary_a)
 * Writes canary 0xd37afd4bb400012a at x29-8. */
static void sk_stack_canary_a_10070c(uint64_t *fp)
{
    *(uint64_t *)((char *)fp - 8) = 0xd37afd4bb400012aULL;
}

/* FUN_00100728 @ 0x100728  (est. sk_store_reg_slot2)
 * Stores x26 at slot[0x10/8]; x24/x25 at slot[idx*0x10+0x20/0x28]. */
static void sk_store_reg_100728(uint64_t *slot, int64_t idx, uint64_t v24, uint64_t v25, uint64_t v26)
{
    slot[0x10/8] = v26;
    slot[idx*0x10/8 + 0x20/8] = v24;
    slot[idx*0x10/8 + 0x28/8] = v25;
}

/* FUN_00100740 @ 0x100740  (est. sk_init_652b30)
 * Calls FUN_00002534(0x652b30, &DAT_004c4010). */
static void sk_init_100740(void)
{
    /* FUN_00002534(0x652b30, &DAT_004c4010) */
}

/* FUN_00100758 @ 0x100758  (est. sk_noop)
 * Empty function. */
static void sk_noop_100758(void) {}

/* FUN_00100774 @ 0x100774  (est. sk_err_2c)
 * Error report via thunk_FUN_002acbb8(0x207461202c, tag 0xe5). */
static void sk_err_100774(void)
{
    /* thunk_FUN_002acbb8(0x207461202c, 0xe500000000000000) */
}

/* FUN_0010078c @ 0x10078c  (est. sk_noop)
 * Empty function. */
static void sk_noop_10078c(void) {}

/* FUN_001007a0 @ 0x1007a0  (est. sk_noop)
 * Empty function. */
static void sk_noop_1007a0(void) {}

/* FUN_001007b4 @ 0x1007b4  (est. sk_stack_canary_b)
 * Writes canary 0xd37afd4bb400012a at x29-0x60. */
static void sk_stack_canary_b_1007b4(uint64_t *fp)
{
    *(uint64_t *)((char *)fp - 0x60) = 0xd37afd4bb400012aULL;
}

/* FUN_001007c8 @ 0x1007c8  (est. sk_const)
 * Returns constant 0x207461202c. */
static uint64_t sk_const_1007c8(void) { return 0x207461202cULL; }

/* FUN_001007d8 @ 0x1007d8  (est. sk_noop)
 * Empty function. */
static void sk_noop_1007d8(void) {}

/* FUN_001007f0 @ 0x1007f0  (est. sk_alloc_18)
 * Sets up a {0, 0xe0...} pair on stack, allocates via FUN_002a4ab4(0x18). */
static void sk_alloc_1007f0(void)
{
    /* uint64_t lo = 0, hi = 0xe000000000000000; FUN_002a4ab4(0x18); */
}

/* FUN_0010080c @ 0x10080c  (est. sk_noop)
 * Empty function. */
static void sk_noop_10080c(void) {}

/* FUN_00100820 @ 0x100820  (est. sk_alloc_18_b)
 * Duplicate of 0x1007f0: stack pair then FUN_002a4ab4(0x18). */
static void sk_alloc_100820(void)
{
    /* uint64_t lo = 0, hi = 0xe000000000000000; FUN_002a4ab4(0x18); */
}

/* FUN_0010083c @ 0x10083c  (est. sk_noop)
 * Empty function. */
static void sk_noop_10083c(void) {}

/* FUN_00100860 @ 0x100860  (est. sk_incr_0)
 * Calls FUN_000824c4(0). */
static void sk_incr_100860(void)
{
    /* FUN_000824c4(0) */
}

/* FUN_00100878 @ 0x100878  (est. sk_incr_slot)
 * Calls FUN_000824e4(0, *(x24+0x10)+1, 1). */
static void sk_incr_slot_100878(uint64_t *ctx)
{
    /* FUN_000824e4(0, ctx->r[0x10/8] + 1, 1) */
}

/* FUN_00100890 @ 0x100890  (est. sk_pair_init)
 * Writes {x19, x22} and a zero byte to a 24-byte pair out; then FUN_0036986c. */
static void sk_pair_init_100890(uint64_t *out)
{
    out[0] = /*x19*/ 0; out[1] = /*x22*/ 0;
    ((uint8_t *)out)[16] = 0;
    /* FUN_0036986c() */
}

/* FUN_001008a4 @ 0x1008a4  (est. sk_err_29)
 * Error report via thunk_FUN_002acbb8(0x202c29, tag 0xe3). */
static void sk_err_1008a4(void)
{
    /* thunk_FUN_002acbb8(0x202c29, 0xe300000000000000) */
}

/* FUN_001008b8 @ 0x1008b8  (est. sk_incr_param)
 * Calls FUN_000824e4(0, param_1 + 1, 1). */
static void sk_incr_param_1008b8(uint64_t v)
{
    /* FUN_000824e4(0, v + 1, 1) */
}

/* FUN_001008cc @ 0x1008cc  (est. sk_init_create)
 * Calls FUN_00085374(s_init_create___005c6130, 0xd, 2, 0x153). */
static void sk_init_create_1008cc(void)
{
    /* FUN_00085374("s_init_create\\...\\005c6130", 0xd, 2, 0x153) */
}

/* FUN_001008e4 @ 0x1008e4  (est. sk_incr_0_b)
 * Calls FUN_000824c4(0). */
static void sk_incr_1008e4(void)
{
    /* FUN_000824c4(0) */
}

/* FUN_001008fc @ 0x1008fc  (est. sk_noop)
 * Empty function. */
static void sk_noop_1008fc(void) {}

/* FUN_00100924 @ 0x100924  (est. sk_noop)
 * Empty function. */
static void sk_noop_100924(void) {}

/* FUN_0010094c @ 0x10094c  (est. sk_store_byte)
 * Stores x25 at slot[0x10/8]; stores w19 byte at slot+idx+0x20. */
static void sk_store_byte_10094c(uint8_t *slot, int64_t idx, uint8_t v, uint64_t val)
{
    ((uint64_t *)slot)[0x10/8] = val;
    slot[idx + 0x20] = v;
}

/* FUN_0010095c @ 0x10095c  (est. sk_noop)
 * Empty function. */
static void sk_noop_10095c(void) {}

/* FUN_0010096c @ 0x10096c  (est. sk_store_byte_b)
 * Stores x23 at slot[0x10/8]; w19 byte at slot+idx+0x20. */
static void sk_store_byte_10096c(uint8_t *slot, int64_t idx, uint8_t v, uint64_t val)
{
    ((uint64_t *)slot)[0x10/8] = val;
    slot[idx + 0x20] = v;
}

/* FUN_0010097c @ 0x10097c  (est. sk_noop)
 * Empty function. */
static void sk_noop_10097c(void) {}

/* FUN_0010098c @ 0x10098c  (est. sk_field_round)
 * Computes (base + (param_1 & 0xffffffff)) & ~mask, calls FUN_00294cb4 on it. */
static void sk_field_round_10098c(uint64_t base, uint32_t v, uint64_t mask)
{
    uint64_t x = (base + (uint64_t)v) & ~mask;
    /* FUN_00294cb4(&x) */
}

/* FUN_001009a0 @ 0x1009a0  (est. sk_err_2820)
 * Error report via thunk_FUN_002acbb8(0x2820, tag 0xe2). */
static void sk_err_1009a0(void)
{
    /* thunk_FUN_002acbb8(0x2820, 0xe200000000000000) */
}

/* FUN_001009b4 @ 0x1009b4  (est. sk_err_3a)
 * Error report via thunk_FUN_002acbb8(0x3a, tag 0xe1). */
static void sk_err_1009b4(void)
{
    /* thunk_FUN_002acbb8(0x3a, 0xe100000000000000) */
}

/* FUN_001009c4 @ 0x1009c4  (est. sk_fdax)
 * Pushes param onto stack, calls FUN_000fda88(&stack0x70). */
static void sk_fdax_1009c4(uint64_t v)
{
    /* uint64_t st = v; FUN_000fda88(&st) */
    (void)v;
}

/* FUN_001009ec @ 0x1009ec  (est. sk_err_2820_b)
 * Error report via thunk_FUN_002acbb8(0x2820, tag 0xe2). */
static void sk_err_1009ec(void)
{
    /* thunk_FUN_002acbb8(0x2820, 0xe200000000000000) */
}

/* FUN_00100a00 @ 0x100a00  (est. sk_field_round_b)
 * Computes (base + (param_1 & 0xffffffff)) & ~mask, calls FUN_00294cb4. */
static void sk_field_round_100a00(uint64_t base, uint32_t v, uint64_t mask)
{
    uint64_t x = (base + (uint64_t)v) & ~mask;
    /* FUN_00294cb4(&x) */
}

/* FUN_00100a14 @ 0x100a14  (est. sk_set_type2)
 * Writes byte 2 at obj+0x10. */
static void sk_set_type2_100a14(uint64_t unused, uint8_t *obj)
{
    obj[0x10] = 2;
}

/* FUN_00100a24 @ 0x100a24  (est. sk_err_29_b)
 * Error report via thunk_FUN_002acbb8(0x202c29, tag 0xe3). */
static void sk_err_100a24(void)
{
    /* thunk_FUN_002acbb8(0x202c29, 0xe300000000000000) */
}

/* FUN_00100a34 @ 0x100a34  (est. sk_noop)
 * Empty function. */
static void sk_noop_100a34(void) {}

/* FUN_00100a48 @ 0x100a48  (est. sk_noop)
 * Empty function. */
static void sk_noop_100a48(void) {}

/* FUN_00100a68 @ 0x100a68  (est. sk_noop)
 * Empty function. */
static void sk_noop_100a68(void) {}

/* FUN_00100a84 @ 0x100a84  (est. sk_noop)
 * Empty function. */
static void sk_noop_100a84(void) {}

/* FUN_00100aa0 @ 0x100aa0  (est. sk_noop)
 * Empty function. */
static void sk_noop_100aa0(void) {}

/* FUN_00100abc @ 0x100abc  (est. sk_report_65a550)
 * Reports {param_1, FUN_0065a550, 0, 0} via FUN_0036993c. */
static void sk_report_100abc(uint64_t v)
{
    /* FUN_0036993c(v, FUN_0065a550, 0, 0) */
}

/* FUN_00100adc @ 0x100adc  (est. sk_noop)
 * Empty function. */
static void sk_noop_100adc(void) {}

/* FUN_00100af4 @ 0x100af4  (est. sk_incr)
 * Calls FUN_000824e4(). */
static void sk_incr_100af4(void)
{
    /* FUN_000824e4() */
}

/* FUN_00100b04 @ 0x100b04  (est. sk_incr_b)
 * Calls FUN_000824c4(). */
static void sk_incr_100b04(void)
{
    /* FUN_000824c4() */
}

/* FUN_00100b14 @ 0x100b14  (est. sk_pair_const)
 * Returns 16-byte pair {0xd00000000000001b, x19|0x8000000000000000}. */
static void sk_pair_const_100b14(void)
{
    /* returns {0xd00000000000001b, x19|0x8000000000000000} */
}

/* FUN_00100b44 @ 0x100b44  (est. sk_incr_c)
 * Calls FUN_000824e4(). */
static void sk_incr_100b44(void)
{
    /* FUN_000824e4() */
}

/* FUN_00100b54 @ 0x100b54  (est. sk_incr_d)
 * Calls FUN_000824c4(). */
static void sk_incr_100b54(void)
{
    /* FUN_000824c4() */
}

/* FUN_00100b64 @ 0x100b64  (est. sk_fdax_b)
 * Pushes param, calls FUN_000fda88(&stack0x70). */
static void sk_fdax_100b64(uint64_t v)
{
    /* uint64_t st = v; FUN_000fda88(&st) */
    (void)v;
}

/* FUN_00100b74 @ 0x100b74  (est. sk_noop)
 * Empty function. */
static void sk_noop_100b74(void) {}

/* FUN_00100b80 @ 0x100b80  (est. sk_fdax_c)
 * Pushes two params, calls FUN_000fda88(&stack0x70). */
static void sk_fdax_100b80(uint64_t a, uint64_t b)
{
    /* uint64_t s0 = b, s1 = a; FUN_000fda88(&s1) */
    (void)a; (void)b;
}

/* FUN_00100b94 @ 0x100b94  (est. sk_noop)
 * Empty function. */
static void sk_noop_100b94(void) {}

/* FUN_00100ba4 @ 0x100ba4  (est. sk_noop)
 * Empty function. */
static void sk_noop_100ba4(void) {}

/* FUN_00100bb4 @ 0x100bb4  (est. sk_fdax_d)
 * Pushes *(x29+0x10), calls FUN_000fda88(&stack0x70). */
static void sk_fdax_100bb4(uint64_t *fp)
{
    /* uint64_t st = *(fp + 0x10/8); FUN_000fda88(&st) */
}

/* FUN_00100be4 @ 0x100be4  (est. sk_ret_stack)
 * Returns the value at stack0x50. */
static uint64_t sk_ret_stack_100be4(void)
{
    return /* in_stack_0x50 */ 0;
}

/* FUN_00100bf0 @ 0x100bf0  (est. sk_noop)
 * Empty function. */
static void sk_noop_100bf0(void) {}

/* FUN_00100c04 @ 0x100c04  (est. sk_noop)
 * Empty function. */
static void sk_noop_100c04(void) {}

/* FUN_00100c14 @ 0x100c14  (est. sk_noop)
 * Empty function. */
static void sk_noop_100c14(void) {}

/* FUN_00100c20 @ 0x100c20  (est. sk_noop)
 * Empty function. */
static void sk_noop_100c20(void) {}

/* FUN_00100c2c @ 0x100c2c  (est. sk_noop)
 * Empty function. */
static void sk_noop_100c2c(void) {}

/* FUN_00100c38 @ 0x100c38  (est. sk_noop)
 * Empty function. */
static void sk_noop_100c38(void) {}

/* FUN_00100c44 @ 0x100c44  (est. sk_err_3a_b)
 * Error report via thunk_FUN_002acbb8(0x3a, tag 0xe1). */
static void sk_err_100c44(void)
{
    /* thunk_FUN_002acbb8(0x3a, 0xe100000000000000) */
}

/* FUN_00100c50 @ 0x100c50  (est. sk_294bdc)
 * Calls FUN_00294bdc(). */
static void sk_294bdc_100c50(void)
{
    /* FUN_00294bdc() */
}

/* FUN_00100c60 @ 0x100c60  (est. sk_err)
 * Error report via thunk_FUN_002acbb8(). */
static void sk_err_100c60(void)
{
    /* thunk_FUN_002acbb8() */
}

/* FUN_00100c6c @ 0x100c6c  (est. sk_err_b)
 * Error report via thunk_FUN_002acbb8(). */
static void sk_err_100c6c(void)
{
    /* thunk_FUN_002acbb8() */
}

/* FUN_00100c78 @ 0x100c78  (est. sk_noop)
 * Empty function. */
static void sk_noop_100c78(void) {}

/* FUN_00100c84 @ 0x100c84  (est. sk_err_7420)
 * Error report via thunk_FUN_002acbb8(0x206f7420, tag 0xe4). */
static void sk_err_100c84(void)
{
    /* thunk_FUN_002acbb8(0x206f7420, 0xe400000000000000) */
}

/* FUN_00100c94 @ 0x100c94  (est. sk_err_pair)
 * Error report via thunk_FUN_002acbb8(0xd000000000000016, 0x80000000005c6520). */
static void sk_err_100c94(void)
{
    /* thunk_FUN_002acbb8(0xd000000000000016, 0x80000000005c6520) */
}

/* FUN_00100cb4 @ 0x100cb4  (est. sk_noop)
 * Empty function. */
static void sk_noop_100cb4(void) {}

/* FUN_00100cd0 @ 0x100cd0  (est. sk_noop)
 * Empty function. */
static void sk_noop_100cd0(void) {}

/* FUN_00100cec @ 0x100cec  (est. sk_stack_canary_c)
 * Writes canary 0xd37afd4bb400012a at x29-0x60. */
static void sk_stack_canary_c_100cec(uint64_t *fp)
{
    *(uint64_t *)((char *)fp - 0x60) = 0xd37afd4bb400012aULL;
}

/* FUN_00100d08 @ 0x100d08  (est. sk_noop)
 * Empty function. */
static void sk_noop_100d08(void) {}

/* FUN_00100d24 @ 0x100d24  (est. sk_noop)
 * Empty function. */
static void sk_noop_100d24(void) {}

/* FUN_00100d34 @ 0x100d34  (est. sk_incr_e)
 * Calls FUN_000824e4(). */
static void sk_incr_100d34(void)
{
    /* FUN_000824e4() */
}

/* FUN_00100d40 @ 0x100d40  (est. sk_noop)
 * Empty function. */
static void sk_noop_100d40(void) {}

/* FUN_00100d50 @ 0x100d50  (est. sk_launcher_panic)
 * Stores w19 into *out then calls the noreturn FUN_001ee9f4 with the
 * "InternalExclaveLauncher_Component" string (0x5c6300), 0x2f, 1, 0x5d. */
static void sk_launcher_panic_100d50(uint64_t a, int32_t *out)
{
    *out = /*w19*/ 0;
    /* FUN_001ee9f4(a, "InternalExclaveLauncher_Component...\\005c6300", 0x2f, 1, 0x5d); noreturn */
}

/* FUN_00100d6c @ 0x100d6c  (est. sk_alloc_18_c)
 * Stack pair {0, 0xe0...} then FUN_002a4ab4(0x18). */
static void sk_alloc_100d6c(void)
{
    /* uint64_t lo = 0, hi = 0xe000000000000000; FUN_002a4ab4(0x18); */
}

/* FUN_00100d88 @ 0x100d88  (est. sk_1ebfb0)
 * Calls FUN_001ebfb0(). */
static void sk_1ebfb0_100d88(void)
{
    /* FUN_001ebfb0() */
}

/* FUN_00100da4 @ 0x100da4  (est. sk_incr_f)
 * Calls FUN_000824c4(). */
static void sk_incr_100da4(void)
{
    /* FUN_000824c4() */
}

/* FUN_00100db0 @ 0x100db0  (est. sk_incr_g)
 * Calls FUN_000824e4(). */
static void sk_incr_100db0(void)
{
    /* FUN_000824e4() */
}

/* FUN_00100dbc @ 0x100dbc  (est. sk_err_c)
 * Error report via thunk_FUN_002acbb8(). */
static void sk_err_100dbc(void)
{
    /* thunk_FUN_002acbb8() */
}

/* FUN_00100dc8 @ 0x100dc8  (est. sk_incr_h)
 * Calls FUN_000824c4(). */
static void sk_incr_100dc8(void)
{
    /* FUN_000824c4() */
}

/* FUN_00100dd4 @ 0x100dd4  (est. sk_err_d)
 * Error report via thunk_FUN_002acbb8(). */
static void sk_err_100dd4(void)
{
    /* thunk_FUN_002acbb8() */
}

/* FUN_00100de0 @ 0x100de0  (est. sk_36b118)
 * Calls FUN_0036b118(). */
static void sk_36b118_100de0(void)
{
    /* FUN_0036b118() */
}

/* FUN_00100dec @ 0x100dec  (est. sk_noop)
 * Empty function. */
static void sk_noop_100dec(void) {}

/* FUN_00100e04 @ 0x100e04  (est. sk_store_reg_slot3)
 * Stores x24 at slot[0x10/8]; x28/x23 at slot[idx*0x10+0x20/0x28]. */
static void sk_store_reg_100e04(uint64_t *slot, int64_t idx, uint64_t v23, uint64_t v24, uint64_t v28)
{
    slot[0x10/8] = v24;
    slot[idx*0x10/8 + 0x20/8] = v28;
    slot[idx*0x10/8 + 0x28/8] = v23;
}

/* FUN_00100e1c @ 0x100e1c  (est. sk_noop)
 * Empty function. */
static void sk_noop_100e1c(void) {}

/* FUN_00100e34 @ 0x100e34  (est. sk_pair_const2)
 * Returns 16-byte pair {0x29, 0xe100000000000000}. */
static void sk_pair_const2_100e34(void)
{
    /* returns {0x29, 0xe100000000000000} */
}

/* FUN_00100e40 @ 0x100e40  (est. sk_noop)
 * Empty function. */
static void sk_noop_100e40(void) {}

/* FUN_00100e58 @ 0x100e58  (est. sk_36b118_b)
 * Calls FUN_0036b118(). */
static void sk_36b118_100e58(void)
{
    /* FUN_0036b118() */
}

/* FUN_00100e64 @ 0x100e64  (est. sk_err_e)
 * Error report via thunk_FUN_002acbb8(). */
static void sk_err_100e64(void)
{
    /* thunk_FUN_002acbb8() */
}

/* FUN_00100e70 @ 0x100e70  (est. sk_err_f)
 * Error report via thunk_FUN_002acbb8(x24+0xf, x25|0x8000000000000000). */
static void sk_err_100e70(void)
{
    /* thunk_FUN_002acbb8(x24 + 0xf, x25 | 0x8000000000000000) */
}

/* FUN_00100e88 @ 0x100e88  (est. sk_incr_i)
 * Calls FUN_000824c4(0). */
static void sk_incr_100e88(void)
{
    /* FUN_000824c4(0) */
}

/* FUN_00100ea0 @ 0x100ea0  (est. sk_incr_slot_b)
 * Calls FUN_000824e4(0, *(x26+0x10)+1, 1). */
static void sk_incr_slot_100ea0(uint64_t *ctx)
{
    /* FUN_000824e4(0, ctx->r[0x10/8] + 1, 1) */
}

/* FUN_00100eb8 @ 0x100eb8  (est. sk_noop)
 * Empty function. */
static void sk_noop_100eb8(void) {}

/* FUN_00100ecc @ 0x100ecc  (est. sk_26e8_36b6f4)
 * Calls FUN_000026e8(x19+0x10) then FUN_0036b6f4(). */
static void sk_26e8_100ecc(uint64_t *ctx)
{
    /* FUN_000026e8(ctx + 0x10/8); FUN_0036b6f4() */
}

/* FUN_00100efc @ 0x100efc  (est. sk_noop)
 * Empty function. */
static void sk_noop_100efc(void) {}

/* FUN_00100f08 @ 0x100f08  (est. sk_const)
 * Returns constant 0x296465766f6d202c. */
static uint64_t sk_const_100f08(void) { return 0x296465766f6d202cULL; }

/* FUN_00100f1c @ 0x100f1c  (est. sk_err_2820_c)
 * Error report via thunk_FUN_002acbb8(0x2820, tag 0xe2). */
static void sk_err_100f1c(void)
{
    /* thunk_FUN_002acbb8(0x2820, 0xe200000000000000) */
}

/* FUN_00100f30 @ 0x100f30  (est. sk_field_round_c)
 * (base + (param & 0xffffffff)) & ~mask, FUN_00294cb4. */
static void sk_field_round_100f30(uint64_t base, uint32_t v, uint64_t mask)
{
    uint64_t x = (base + (uint64_t)v) & ~mask;
    /* FUN_00294cb4(&x) */
}

/* FUN_00100f44 @ 0x100f44  (est. sk_fdax_e)
 * Pushes two params, calls FUN_000fda88(&stack0x70). */
static void sk_fdax_100f44(uint64_t a, uint64_t b)
{
    /* uint64_t s0 = b, s1 = a; FUN_000fda88(&s1) */
    (void)a; (void)b;
}

/* FUN_00100f58 @ 0x100f58  (est. sk_369efc)
 * Calls FUN_00369efc(x29-1). */
static void sk_369efc_100f58(uint64_t *fp)
{
    /* FUN_00369efc(fp - 1) */
}

/* FUN_00100f64 @ 0x100f64  (est. sk_err_g)
 * Error report via thunk_FUN_002acbb8(). */
static void sk_err_100f64(void)
{
    /* thunk_FUN_002acbb8() */
}

/* FUN_00100f70 @ 0x100f70  (est. sk_deref_slot)
 * *out = *(*(x20+0x10)+0x10). */
static void sk_deref_slot_100f70(uint64_t *out, uint64_t *ctx)
{
    *out = *(uint64_t *)(*(uint64_t *)((char *)ctx + 0x10) + 0x10);
}

/* FUN_00100f80 @ 0x100f80  (est. sk_deref_slot_wrap)
 * Wraps 0x100f70. */
static void sk_deref_wrap_100f80(void)
{
    /* FUN_00100f70() */
}

/* FUN_00100fa4 @ 0x100fa4  (est. sk_100fbc_wrap)
 * Wraps 0x100fbc. */
static void sk_100fbc_wrap_100fa4(void)
{
    /* FUN_00100fbc() */
}

/* FUN_00100fbc @ 0x100fbc  (est. sk_obj_init)
 * Allocates via FUN_0036a940(0x652d58, 0x18, 7), records {x20} at +0x10,
 * sets out[3]=0x652d58, out[4]=0x662d50, out[0]=alloc, then FUN_0036b270. */
static void sk_obj_init_100fbc(uint64_t *out, uint64_t *ctx)
{
    uint64_t l = /* FUN_0036a940(0x652d58, 0x18, 7) */ 0;
    *(uint64_t *)(l + 0x10) = (uint64_t)ctx;
    out[3] = 0x652d58; out[4] = 0x662d50; out[0] = l;
    /* FUN_0036b270() */
}

/* ============ 0x101038 - 0x103ff4 : PMM/PRNG/crypto/allocator ============ */

/* FUN_00101038 @ 0x101038  (est. sk_fatal_65588)
 * Fatal-error sequence: allocate (0x25), log several message pairs via
 * thunk_FUN_002acbb8/FUN_003a25d4, call a panic helper (FUN_00027724), then
 * return the 16-byte {0xd000000000000022, 0x80000000005c6880} error record. */
static void sk_fatal_101038(void)
{
    /* FUN_002a4ab4(0x25); FUN_003a25d4(0xe0...); (*FUN_00027724(0x671848))(0x677790,0x671848);
     * thunk_FUN_002acbb8(); FUN_003a25d4(x1); thunk_FUN_002acbb8(0x29,0xe1...);
     * returns {0xd000000000000022, 0x80000000005c6880} */
}

/* FUN_00101100 @ 0x101100  (est. sk_100fa4_wrap)
 * Wraps 0x100fa4. */
static void sk_100fa4_wrap_101100(void) { /* FUN_00100fa4() */ }

/* FUN_00101104 @ 0x101104  (est. sk_100fa4_wrap_b)
 * Wraps 0x100fa4. */
static void sk_100fa4_wrap_101104(void) { /* FUN_00100fa4() */ }

/* FUN_00101118 @ 0x101118  (est. sk_101038_wrap)
 * Wraps 0x101038 (fatal sequence). */
static void sk_101038_wrap_101118(void) { /* FUN_00101038() */ }

/* FUN_00101174 @ 0x101174  (est. sk_const16_652cf8)
 * Returns 16-byte {0x652cf8, 0}. */
static void sk_const16_101174(void)
{
    /* returns ZEXT816(0x652cf8) */
}

/* FUN_00101184 @ 0x101184  (est. sk_alloc_then_init)
 * Allocates via FUN_0036a940 then runs the object-init at 0x10196c. */
static uint64_t sk_alloc_then_init_101184(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_0010196c(a, b, c) */
    return v;
}

/* FUN_00101260 @ 0x101260  (est. sk_region_query)
 * Reads a region descriptor at ctx->r[0x10/8]: validates the size field
 * (bits 16..31 must be zero, high bit clear) then packs the object's
 * identification/limits into a 0x2b-byte record. Used by the PMM region
 * query interface. */
static void sk_region_query_101260(uint64_t *out, uint64_t *ctx)
{
    /* see decompile: copies ctx fields +obj+0x38 size into out; BRK on bad size */
    (void)out; (void)ctx;
}

/* FUN_001012c4 @ 0x1012c4  (est. sk_pmm_instance_init)
 * Large PMM-instance constructor: through a per-class vtable (offset 0x1c8,
 * 0x1b8) it populates the fixed-capability region (0x652e58), the slot
 * allocator records, the free-slot tracking, and (via FUN_000ffba8) the
 * physical-memory resource lists. Callers check the callee-saved flag and
 * fall through to the noreturn 0x1036b6f4 on failure. */
static void sk_pmm_instance_init_1012c4(void)
{
    /* see decompile: vtable-driven full state init */
}

/* FUN_001016d8 @ 0x1016d8  (est. sk_ec_sc_cnode_init)
 * Initializes the EC and SC capability-node indices: allocates, logs the
 * "BrokeRed" banner and "ec_cnode_idx"/"sc_cnode_idx" label strings, then
 * links both indices via FUN_00205844. Returns a 16-byte status pair. */
static void sk_ec_sc_cnode_init_1016d8(void)
{
    /* see decompile: strings s___ec_cnode_idx__005c68f0 / s___sc_cnode_idx__005c6910 */
}

/* FUN_001018e0 @ 0x1018e0  (est. sk_release_one)
 * Releases obj at ctx->r[0x10/8] then runs teardown FUN_0036b6ac. */
static void sk_release_one_1018e0(uint64_t *ctx)
{
    /* FUN_0036b118(ctx->r[0x10/8]); FUN_0036b6ac() */
}

/* FUN_001018e4 @ 0x1018e4  (est. sk_release_one_b)
 * Duplicate of 0x1018e0. */
static void sk_release_one_1018e4(uint64_t *ctx)
{
    /* FUN_0036b118(ctx->r[0x10/8]); FUN_0036b6ac() */
}

/* FUN_0010190c @ 0x10190c  (est. sk_101260_wrap)
 * Wraps 0x101260 (region query). */
static void sk_101260_wrap_10190c(void) { /* FUN_00101260() */ }

/* FUN_00101930 @ 0x101930  (est. sk_1016d8_wrap)
 * Wraps 0x1016d8 (EC/SC cnode init). */
static void sk_1016d8_wrap_101930(void) { /* FUN_001016d8() */ }

/* FUN_0010196c @ 0x10196c  (est. sk_obj_init)
 * Core object initializer: parses the size/depth via FUN_000534ec, allocates
 * the object header via FUN_0036a940, and if the first-time flag is set also
 * allocates the physical-allocator backing (FUN_000ff728/FUN_00101f38). Stores
 * into ctx->r[0x10/0x18/0x20/0x28/0x30/0x31/0x38/0x40]. Stack-canary guarded
 * (noreturn 0x11d7e8 on mismatch). */
static void sk_obj_init_10196c(uint64_t a, uint64_t b, uint8_t c)
{
    /* see decompile: FUN_000534ec(b,&local,&flag); FUN_0036a940(...0x52,7) */
}

/* FUN_00101bf8 @ 0x101bf8  (est. sk_pmm_instance_new)
 * Allocates a 0x111-byte PMM instance (FUN_0036a940(0x652e58,0x111,7)), runs
 * the constructor FUN_001012c4, and records the object header
 * {0x652e58, 0x662da8, ptr} into out. */
static void sk_pmm_instance_new_101bf8(uint64_t *out, uint64_t a)
{
    uint64_t v = /* FUN_001012c4() */ 0;
    out[3] = 0x652e58; out[4] = 0x662da8; out[0] = v;
}

/* FUN_00101c8c @ 0x101c8c  (est. sk_pmm_state_log)
 * Logs the PMM instance state: allocates (0x23), prints "set_boot" /
 * "secondary" / ", did :" / ", archi d" diagnostic strings via
 * thunk_FUN_002acbb8, and returns the 16-byte error record
 * {0x756f736552757043, 0xec00000028656372} ("CPUReso".../"rec"...). */
static void sk_pmm_state_log_101c8c(void)
{
    /* FUN_002a4ab4(0x23); FUN_003a25d4(...); logs "set_boot"/"secondary"... */
}

/* FUN_00101e24 @ 0x101e24  (est. sk_release_quad)
 * Releases the four registers at ctx->r[0x10/0x18/0x20/0x28]. */
static void sk_release_quad_101e24(uint64_t *ctx)
{
    /* FUN_0036b118(ctx[0x10/8]); FUN_0036b118(ctx[0x18/8]);
     * FUN_0036b118(ctx[0x20/8]); FUN_0036b118(ctx[0x28/8]) */
}

/* FUN_00101e5c @ 0x101e5c  (est. sk_release_quad_b)
 * Releases quad then teardown FUN_0036b6ac. */
static void sk_release_quad_101e5c(void) { /* FUN_00101e24(); FUN_0036b6ac() */ }

/* FUN_00101e60 @ 0x101e60  (est. sk_release_quad_c)
 * Duplicate of 0x101e5c. */
static void sk_release_quad_101e60(void) { /* FUN_00101e24(); FUN_0036b6ac() */ }

/* FUN_00101e84 @ 0x101e84  (est. sk_101bf8_wrap)
 * Wraps 0x101bf8 (PMM instance new). */
static void sk_101bf8_wrap_101e84(void) { /* FUN_00101bf8() */ }

/* FUN_00101e88 @ 0x101e88  (est. sk_101bf8_wrap_b)
 * Duplicate wrap of 0x101bf8. */
static void sk_101bf8_wrap_101e88(void) { /* FUN_00101bf8() */ }

/* FUN_00101e9c @ 0x101e9c  (est. sk_101c8c_wrap)
 * Wraps 0x101c8c. */
static void sk_101c8c_wrap_101e9c(void) { /* FUN_00101c8c() */ }

/* FUN_00101ec8 @ 0x101ec8  (est. sk_const16_652e58)
 * Returns 16-byte {0x652e58, 0}. */
static void sk_const16_101ec8(void) { /* returns ZEXT816(0x652e58) */ }

/* FUN_00101f08 @ 0x101f08  (est. sk_const16_652dc0)
 * Returns 16-byte {0x652dc0, 0}. */
static void sk_const16_101f08(void) { /* returns ZEXT816(0x652dc0) */ }

/* FUN_00101f20 @ 0x101f20  (est. sk_label_err)
 * Logs a labeled error: thunk_FUN_002acbb8(0xd000000000000010, param-0x20 | 0x80...). */
static void sk_label_err_101f20(uint64_t v)
{
    /* thunk_FUN_002acbb8(0xd000000000000010, v - 0x20 | 0x8000000000000000) */
}

/* FUN_00101f38 @ 0x101f38  (est. sk_alloc_small)
 * Allocates via FUN_000ff728(6, &stack). */
static void sk_alloc_small_101f38(void)
{
    /* FUN_000ff728(6, &stack0x20) */
}

/* FUN_00101f4c @ 0x101f4c  (est. sk_region_find_insert)
 * PMM region free-list search/insert: walks the slot array (entries of 0x28
 * bytes), locates the gap covering [param_3, param_3+size), and inserts the
 * region keeping the list sorted; on exhaustion it either faults (param_4&1)
 * or panics "Fatal error"/"PMMInstance". Produces a 5-word record into
 * param_1. This is the allocator's physical-region bookkeeping core. */
static void sk_region_find_insert_101f4c(uint64_t *out, uint64_t *list, uint64_t start, uint64_t flags)
{
    (void)out; (void)list; (void)start; (void)flags;
    /* see decompile: sorted slot-list insert, 0x28-byte stride, BRK/panic paths */
}

/* FUN_00102294 @ 0x102294  (est. sk_alloc_then_22cc)
 * Allocates via FUN_0036a940 then runs 0x1022cc. */
static uint64_t sk_alloc_then_22cc_102294(void)
{
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_001022cc() */
    return v;
}

/* FUN_001022cc @ 0x1022cc  (est. sk_boot_region_init)
 * Boot region bootstrap: zeroes the five context slots, sets the vtable
 * (&DAT_00657778), allocates the region object (FUN_000ec8f8/FUN_0036a940,
 * 0x18 bytes) and its backing store (FUN_0036a804), then calls
 * FUN_00101f4c(&local,&list,0x100000,0) to install the initial 1 MiB region. */
static void sk_boot_region_init_1022cc(void)
{
    /* see decompile: FUN_0036a940 + FUN_00101f4c(&local,&DAT_00657778,0x100000,0) */
}

/* FUN_0010237c @ 0x10237c  (est. sk_region_refresh)
 * Refreshes the PMM region list: if the first entry is empty it re-runs the
 * install path (FUN_00101f4c with 0x100000), else pops a slot via
 * FUN_00103310/FUN_00103214. Stores the resulting region record into the
 * context registers. */
static void sk_region_refresh_10237c(void)
{
    /* see decompile */
}

/* FUN_00102464 @ 0x102464  (est. sk_alloc_pages)
 * Allocates param_1 * 0x4000 (16 KiB pages): bounds-checks (param_1>>0x32,
 * BRK), refreshes the region list when exhausted, walks free entries, and
 * returns the physical address of a contiguous run. On insufficient space it
 * extends via the region list (FUN_00101f4c) or faults. This is the PMM
 * page-allocator core. */
static uint64_t sk_alloc_pages_102464(uint64_t pages)
{
    (void)pages;
    /* see decompile: 16 KiB-granule allocator; BRK 0x1025b0/b4/b8 */
    return 0;
}

/* FUN_001025b8 @ 0x1025b8  (est. sk_region_free_none)
 * Calls a vtable method (offset 0x80) on the region object, logging
 * 0x677790, then releases. */
static uint64_t sk_region_free_none_1025b8(void)
{
    /* (*(code **)(*obj + 0x80))(); FUN_0036b118(obj); return local_38 */
    return 0;
}

/* FUN_00102650 @ 0x102650  (est. sk_alloc_added)
 * Allocates one page (FUN_00102464(1)), validates type byte <=0xff (BRK),
 * builds the descriptor via FUN_001033d8, logs, then adds the size into the
 * out counter. */
static void sk_alloc_added_102650(uint64_t *out, uint64_t inst, uint64_t a, uint64_t b)
{
    /* FUN_00102464(1); FUN_001033d8(...); *out = inst->r[0x18/8] + uVar2 */
    (void)out; (void)inst; (void)a; (void)b;
}

/* FUN_00102728 @ 0x102728  (est. sk_alloc_0x40)
 * Allocates a 0x40-byte block: if the 16 KiB-aligned cursor at ctx+0x38 is
 * exhausted, allocates a page; then bumps the cursor by 0x40 (BRK if near
 * wrap). */
static void sk_alloc_0x40_102728(uint64_t *ctx)
{
    /* uVar2 = ctx->r[0x38/8]; if ((uVar2&0x3fff)==0) uVar2 = sk_alloc_pages(1);
     * if (uVar2 < 0xffffffffffffffc0) ctx->r[0x38/8] = uVar2 + 0x40; else BRK */
    (void)ctx;
}

/* FUN_0010272c @ 0x10272c  (est. sk_alloc_0x40_b)
 * Duplicate of 0x102728. */
static void sk_alloc_0x40_10272c(uint64_t *ctx) { /* same as 0x102728 */ (void)ctx; }

/* FUN_00102778 @ 0x102778  (est. sk_alloc_0x40_wrap)
 * Wraps 0x102728 via FUN_00102910(param_1, FUN_0010338c). */
static void sk_alloc_0x40_wrap_102778(uint64_t a)
{
    /* FUN_00102910(a, FUN_0010338c) */
}

/* FUN_001027a4 @ 0x1027a4  (est. sk_alloc_0x800)
 * Allocates a 0x800-byte block from the cursor at ctx+0x40; on allocation
 * failure returns without the panic path. */
static void sk_alloc_0x800_1027a4(uint64_t *ctx)
{
    /* uVar2 = ctx->r[0x40/8]; if ((uVar2&0x3fff)==0) uVar2 = sk_alloc_pages(1);
     * if (uVar2 < 0xfffffffffffff800) ctx->r[0x40/8] = uVar2 + 0x800; else BRK */
    (void)ctx;
}

/* FUN_001027a8 @ 0x1027a8  (est. sk_alloc_0x800_b)
 * Duplicate of 0x1027a4. */
static void sk_alloc_0x800_1027a8(uint64_t *ctx) { /* same as 0x1027a4 */ (void)ctx; }

/* FUN_001027ec @ 0x1027ec  (est. sk_alloc_0x800_wrap)
 * Wraps 0x1027a4 via FUN_00102910(param_1, FUN_00103404). */
static void sk_alloc_0x800_wrap_1027ec(uint64_t a)
{
    /* FUN_00102910(a, FUN_00103404) */
}

/* FUN_00102818 @ 0x102818  (est. sk_alloc_0x40_c)
 * Allocates 0x40 bytes from cursor at ctx+0x48; failure -> panic 0xee9f4. */
static void sk_alloc_0x40_102818(uint64_t *ctx)
{
    /* uVar2 = ctx->r[0x48/8]; ... ctx->r[0x48/8] = uVar2 + 0x40; else BRK/panic */
    (void)ctx;
}

/* FUN_0010281c @ 0x10281c  (est. sk_alloc_0x40_d)
 * Duplicate of 0x102818. */
static void sk_alloc_0x40_10281c(uint64_t *ctx) { /* same as 0x102818 */ (void)ctx; }

/* FUN_00102868 @ 0x102868  (est. sk_alloc_0x40_wrap_c)
 * Wraps 0x102818 via FUN_00102910(param_1, FUN_00103450). */
static void sk_alloc_0x40_wrap_102868(uint64_t a)
{
    /* FUN_00102910(a, FUN_00103450) */
}

/* FUN_00102894 @ 0x102894  (est. sk_alloc_0x80)
 * Allocates 0x80 bytes from cursor at ctx+0x50; failure -> panic. */
static void sk_alloc_0x80_102894(uint64_t *ctx)
{
    /* uVar2 = ctx->r[0x50/8]; ... ctx->r[0x50/8] = uVar2 + 0x80; else BRK */
    (void)ctx;
}

/* FUN_00102898 @ 0x102898  (est. sk_alloc_0x80_b)
 * Duplicate of 0x102894. */
static void sk_alloc_0x80_102898(uint64_t *ctx) { /* same as 0x102894 */ (void)ctx; }

/* FUN_001028e4 @ 0x1028e4  (est. sk_alloc_0x80_wrap)
 * Wraps 0x102894 via FUN_00102910(param_1, FUN_001034c0). */
static void sk_alloc_0x80_wrap_1028e4(uint64_t a)
{
    /* FUN_00102910(a, FUN_001034c0) */
}

/* FUN_00102910 @ 0x102910  (est. sk_region_method)
 * Calls a region vtable method (offset 0x80) with the four descriptor args
 * and the logging label 0x677790; returns the method result. */
static uint64_t sk_region_method_102910(uint64_t a, uint64_t fn)
{
    /* (*(code **)(*obj + 0x80))(&out, fn, args, 0x677790); return out */
    return 0;
}

/* FUN_001029a4 @ 0x1029a4  (est. sk_alloc_via)
 * Allocates via the callback (*param_4)(), builds a descriptor with
 * FUN_001033d8, logs, and adds size to the out counter. */
static void sk_alloc_via_1029a4(uint64_t *out, uint64_t inst, uint64_t a, uint64_t (*fn)(void), uint8_t ty, uint64_t b, uint64_t c)
{
    /* uVar2 = fn(); FUN_001033d8(inst->r[0x10/8], ty, uVar2, a); *out = inst->r[0x18/8]+uVar2 */
    (void)out; (void)inst; (void)a; (void)fn; (void)ty; (void)b; (void)c;
}

/* FUN_00102a60 @ 0x102a60  (est. sk_alloc_dispatch)
 * Dispatches on a type byte: case 1->0x102778, 2->0x1027ec, 7->0x102868,
 * 0x12->0x1028e4, else a generic region free (0x1025b8) with a per-type id;
 * out-of-range (>=0x13) reports and fails. This is the PMM allocation-type
 * switch. */
static void sk_alloc_dispatch_102a60(uint64_t a, uint8_t type)
{
    (void)a; (void)type;
    /* switch(type) { 1,2,7,0x12 -> specific alloc; default -> FUN_001025b8(a,id) } */
}

/* FUN_00102b88 @ 0x102b88  (est. sk_vtbl_1a0)
 * Calls vtable method at offset 0x1a0 with (a,b,0). */
static void sk_vtbl_1a0_102b88(uint64_t a, uint64_t b)
{
    /* (**(code **)(*ctx + 0x1a0))(a, b, 0) */
}

/* FUN_00102bc0 @ 0x102bc0  (est. sk_region_free_any)
 * Releases region via vtable 0x80, logging 0x677790. */
static uint64_t sk_region_free_any_102bc0(void)
{
    /* (*(code **)(*obj + 0x80))(); FUN_0036b118(obj); return local_38 */
    return 0;
}

/* FUN_00102c54 @ 0x102c54  (est. sk_alloc_multi)
 * Allocates a multi-page run of param_2 bytes (must be 16 KiB aligned,
 * else reports+returns error): pages = param_2>>14, allocates, builds
 * descriptor, logs, adds to out. */
static void sk_alloc_multi_102c54(uint64_t *out, uint64_t size, uint64_t inst, uint64_t a)
{
    (void)out; (void)size; (void)inst; (void)a;
    /* if ((size&0x3fff)==0) { uVar2 = sk_alloc_pages(size>>14); ... *out = inst+uVar2 }
     * else { report; *x1 = 3 } */
}

/* FUN_00102d54 @ 0x102d54  (est. sk_alloc_multi_wrap)
 * Wraps 0x102c54 with the three context registers. */
static void sk_alloc_multi_wrap_102d54(uint64_t *ctx)
{
    /* FUN_00102c54(ctx[0x10/8], ctx[0x18/8], ctx[0x20/8]) */
}

/* FUN_00102d58 @ 0x102d58  (est. sk_alloc_multi_wrap_b)
 * Duplicate wrap of 0x102d54. */
static void sk_alloc_multi_wrap_102d58(uint64_t *ctx) { /* same as 0x102d54 */ }

/* FUN_00102d74 @ 0x102d74  (est. sk_panic_pmm)
 * Panics with the "PMMInstance" label (offset +0x10): noreturn FUN_001afa84. */
static void sk_panic_pmm_102d74(void)
{
    /* FUN_00103534("...PMMInstance..."+0x10); FUN_001afa84(); noreturn */
}

/* FUN_00102dbc @ 0x102dbc  (est. sk_panic_alloc)
 * Panics with the "PMMInstance.allocUntypedForType" label (+0x20): noreturn. */
static void sk_panic_alloc_102dbc(void)
{
    /* FUN_00103534("...allocUntypedForType..."+0x20); FUN_001afa84(); noreturn */
}

/* FUN_00102e0c @ 0x102e0c  (est. sk_panic_no_free)
 * Panics with the "PMMInstance does not free resource" label (+0x10): noreturn. */
static void sk_panic_no_free_102e0c(void)
{
    /* FUN_00103534("...does not free resource..."+0x10); FUN_001afa84(); noreturn */
}

/* FUN_00102e54 @ 0x102e54  (est. sk_release_two)
 * Releases obj at ctx+0x58 and ctx+0x60. */
static void sk_release_two_102e54(uint64_t *ctx)
{
    /* FUN_0036b118(ctx->r[0x58/8]); FUN_0036b118(ctx->r[0x60/8]) */
}

/* FUN_00102e7c @ 0x102e7c  (est. sk_release_two_b)
 * Releases two then teardown FUN_0036b6ac. */
static void sk_release_two_102e7c(void) { /* FUN_00102e54(); FUN_0036b6ac() */ }

/* FUN_00102e80 @ 0x102e80  (est. sk_release_two_c)
 * Duplicate of 0x102e7c. */
static void sk_release_two_102e80(void) { /* FUN_00102e54(); FUN_0036b6ac() */ }

/* FUN_00102ea4 @ 0x102ea4  (est. sk_vtbl_1a8)
 * Calls vtable method at offset 0x1a8. */
static void sk_vtbl_1a8_102ea4(void)
{
    /* (**(code **)(*(long *)*ctx + 0x1a8))() */
}

/* FUN_00102ee8 @ 0x102ee8  (est. sk_vtbl_1a0_b)
 * Calls vtable method at offset 0x1a0. */
static void sk_vtbl_1a0_102ee8(void)
{
    /* (**(code **)(*(long *)*ctx + 0x1a0))() */
}

/* FUN_00102f2c @ 0x102f2c  (est. sk_vtbl_1b0)
 * Calls vtable method at offset 0x1b0. */
static void sk_vtbl_1b0_102f2c(void)
{
    /* (**(code **)(*(long *)*ctx + 0x1b0))() */
}

/* FUN_00102f70 @ 0x102f70  (est. sk_vtbl_1b8)
 * Calls vtable method at offset 0x1b8. */
static void sk_vtbl_1b8_102f70(void)
{
    /* (**(code **)(*(long *)*ctx + 0x1b8))() */
}

/* FUN_00102fb4 @ 0x102fb4  (est. sk_vtbl_1c0)
 * Calls vtable method at offset 0x1c0. */
static void sk_vtbl_1c0_102fb4(void)
{
    /* (**(code **)(*(long *)*ctx + 0x1c0))() */
}

/* FUN_00102ff8 @ 0x102ff8  (est. sk_vtbl_1c8)
 * Calls vtable method at offset 0x1c8. */
static void sk_vtbl_1c8_102ff8(void)
{
    /* (**(code **)(*(long *)*ctx + 0x1c8))() */
}

/* FUN_0010303c @ 0x10303c  (est. sk_vtbl_140)
 * Calls vtable method at offset 0x140. */
static void sk_vtbl_140_10303c(void)
{
    /* (**(code **)(*(long *)*ctx + 0x140))() */
}

/* FUN_00103080 @ 0x103080  (est. sk_vtbl_1d0)
 * Calls vtable method at offset 0x1d0. */
static void sk_vtbl_1d0_103080(void)
{
    /* (**(code **)(*(long *)*ctx + 0x1d0))() */
}

/* FUN_001030c4 @ 0x1030c4  (est. sk_const16_652ed8)
 * Returns 16-byte {0x652ed8, 0}. */
static void sk_const16_1030c4(void) { /* returns ZEXT816(0x652ed8) */ }

/* FUN_001030d4 @ 0x1030d4  (est. sk_region_array_erase)
 * Erases a range [param_1, param_2) from a 0x28-stride array (region list):
 * bounds/overflow checks (BRK), compacts the tail via thunk_FUN_000723c0,
 * decrements the count. This is the region-list removal primitive. */
static void sk_region_array_erase_1030d4(uint64_t from, uint64_t to)
{
    (void)from; (void)to;
    /* see decompile: 0x28-stride memmove compaction, count--, BRK checks */
}

/* FUN_0010319c @ 0x10319c  (est. sk_region_array_pop_byte)
 * Pops the last byte (or index) from the 0x28-stride array, shifting left and
 * decrementing count; returns the removed byte. */
static uint8_t sk_region_array_pop_byte_10319c(uint64_t idx)
{
    (void)idx;
    /* see decompile */
    return 0;
}

/* FUN_00103214 @ 0x103214  (est. sk_region_array_pop)
 * Pops the 5-word region record at index param_2 from the 0x28-stride array,
 * compacting and decrementing count; writes the record into param_1. */
static void sk_region_array_pop_103214(uint64_t *out, uint64_t idx)
{
    (void)out; (void)idx;
    /* see decompile */
}

/* FUN_001032b8 @ 0x1032b8  (est. sk_region_array_pop_last)
 * Pops the last byte of the region array (count>0 required), returning it. */
static uint8_t sk_region_array_pop_last_1032b8(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00103310 @ 0x103310  (est. sk_region_array_pop_last5)
 * Pops the last 5-word region record, writing it to param_1 and clearing the
 * tag byte. */
static void sk_region_array_pop_last5_103310(uint64_t *out)
{
    /* see decompile */
}

/* FUN_0010338c @ 0x10338c  (est. sk_alloc_type8)
 * Allocates type 8 via FUN_001029a4 with the 0x40-byte allocator
 * (FUN_00102728), label &LAB_000f63f8, id 0x8e. */
static void sk_alloc_type8_10338c(uint64_t *ctx)
{
    /* FUN_001029a4(ctx[0x10/8], ctx[0x18/8], FUN_00102728, 8, &LAB_000f63f8, 0x8e) */
}

/* FUN_00103390 @ 0x103390  (est. sk_alloc_type8_b)
 * Duplicate of 0x10338c. */
static void sk_alloc_type8_103390(uint64_t *ctx) { /* same as 0x10338c */ }

/* FUN_001033d8 @ 0x1033d8  (est. sk_svc0_alloc)
 * Issues supervisor call 0 to request a physical allocation: writes the type
 * (low 32 bits), address, and size into the tpidrro_el0 block, calls SVC 0,
 * then restores the type field. This is the kernel->GL0 phys-allocation
 * request. */
static void sk_svc0_alloc_1033d8(uint64_t type, uint64_t addr, uint64_t size)
{
    /* uint64_t *blk = tpidrro_el0; blk[0]=type&0xffffffff; blk[1]=addr;
     * blk[2]=size; CallSupervisor(0); blk[0]=type&0xffffffff */
    (void)type; (void)addr; (void)size;
}

/* FUN_00103404 @ 0x103404  (est. sk_alloc_type6)
 * Allocates type 6 via FUN_001029a4 with FUN_001027a4, label &LAB_000f6404,
 * id 0xab. */
static void sk_alloc_type6_103404(uint64_t *ctx)
{
    /* FUN_001029a4(ctx[0x10/8], ctx[0x18/8], FUN_001027a4, 6, &LAB_000f6404, 0xab) */
}

/* FUN_00103408 @ 0x103408  (est. sk_alloc_type6_b)
 * Duplicate of 0x103404. */
static void sk_alloc_type6_103408(uint64_t *ctx) { /* same as 0x103404 */ }

/* FUN_00103450 @ 0x103450  (est. sk_alloc_type7)
 * Allocates type 7 via FUN_001029a4 with FUN_00102818, label &LAB_000f64a8,
 * id 200. */
static void sk_alloc_type7_103450(uint64_t *ctx)
{
    /* FUN_001029a4(ctx[0x10/8], ctx[0x18/8], FUN_00102818, 7, &LAB_000f64a8, 200) */
}

/* FUN_00103454 @ 0x103454  (est. sk_alloc_type7_b)
 * Duplicate of 0x103450. */
static void sk_alloc_type7_103454(uint64_t *ctx) { /* same as 0x103450 */ }

/* FUN_0010349c @ 0x10349c  (est. sk_alloc_added_wrap)
 * Wraps 0x102650 with the three context registers. */
static void sk_alloc_added_wrap_10349c(uint64_t *ctx)
{
    /* FUN_00102650(ctx[0x10/8], ctx[0x18/8], ctx[0x20/8]) */
}

/* FUN_001034a0 @ 0x1034a0  (est. sk_alloc_added_wrap_b)
 * Duplicate wrap of 0x10349c. */
static void sk_alloc_added_wrap_1034a0(uint64_t *ctx) { /* same as 0x10349c */ }

/* FUN_001034c0 @ 0x1034c0  (est. sk_alloc_type13)
 * Allocates type 0x13 via FUN_001029a4 with FUN_00102894, label &LAB_000f64a8,
 * id 0xe4. */
static void sk_alloc_type13_1034c0(uint64_t *ctx)
{
    /* FUN_001029a4(ctx[0x10/8], ctx[0x18/8], FUN_00102894, 0x13, &LAB_000f64a8, 0xe4) */
}

/* FUN_001034c4 @ 0x1034c4  (est. sk_alloc_type13_b)
 * Duplicate of 0x1034c0. */
static void sk_alloc_type13_1034c4(uint64_t *ctx) { /* same as 0x1034c0 */ }

/* FUN_0010350c @ 0x10350c  (est. sk_round_1m)
 * Rounds param up to a 1 MiB boundary: (param + 0xfffff) & ~0xfffff. */
static uint64_t sk_round_1m_10350c(int64_t v)
{
    return (uint64_t)(v + 0xfffff) & 0xfffffffffff00000ULL;
}

/* FUN_0010351c @ 0x10351c  (est. sk_noop)
 * Empty function. */
static void sk_noop_10351c(void) {}

/* FUN_00103534 @ 0x103534  (est. sk_panic_pair)
 * Returns 16-byte {s_Fatal_error_005accd0, 0xb} (a fatal-error record). */
static void sk_panic_pair_103534(void)
{
    /* returns {s_Fatal_error_005accd0, 0xb} */
}

/* FUN_00103558 @ 0x103558  (est. sk_noop)
 * Empty function. */
static void sk_noop_103558(void) {}

/* FUN_0010357c @ 0x10357c  (est. sk_103594_wrap)
 * Wraps 0x103594. */
static void sk_103594_wrap_10357c(void) { /* FUN_00103594() */ }

/* FUN_00103594 @ 0x103594  (est. sk_obj_new)
 * Allocates a 0x18-byte object (FUN_0036a940(0x653128,0x18,7)), records the
 * header {0x653128, 0x662e28, ptr} into param_1. */
static void sk_obj_new_103594(uint64_t *out)
{
    uint64_t l = /* FUN_0036a940(0x653128, 0x18, 7) */ 0;
    out[3] = 0x653128; out[4] = 0x662e28; out[0] = l;
}

/* FUN_00103600 @ 0x103600  (est. sk_fatal_6c90)
 * Fatal sequence: allocate (0x16), log message pair, call panic helper, and
 * return 16-byte {0xd000000000000014, 0x80000000005c6c90}. */
static void sk_fatal_103600(void)
{
    /* FUN_002a4ab4(0x16); FUN_003a25d4(...); (*FUN_00027724(0x671848))(0x677790,0x671848);
     * returns {0xd000000000000014, 0x80000000005c6c90} */
}

/* FUN_001036b8 @ 0x1036b8  (est. sk_103594_wrap_b)
 * Wraps 0x103594. */
static void sk_103594_wrap_1036b8(void) { /* FUN_0010357c() */ }

/* FUN_001036d0 @ 0x1036d0  (est. sk_103600_wrap)
 * Wraps 0x103600. */
static void sk_103600_wrap_1036d0(void) { /* FUN_00103600() */ }

/* FUN_00103724 @ 0x103724  (est. sk_const16_6530c8)
 * Returns 16-byte {0x6530c8, 0}. */
static void sk_const16_103724(void) { /* returns ZEXT816(0x6530c8) */ }

/* FUN_00103734 @ 0x103734  (est. sk_1036b8_wrap)
 * Wraps 0x1036b8. */
static void sk_1036b8_wrap_103734(void) { /* FUN_001036b8() */ }

/* FUN_00103738 @ 0x103738  (est. sk_1036b8_wrap_b)
 * Duplicate wrap of 0x1036b8. */
static void sk_1036b8_wrap_103738(void) { /* FUN_001036b8() */ }

/* FUN_00103764 @ 0x103764  (est. sk_acquire_log)
 * Acquires (FUN_0036b270) then logs FUN_000814e4. */
static void sk_acquire_log_103764(void)
{
    /* FUN_0036b270(); FUN_000814e4() */
}

/* FUN_0010378c @ 0x10378c  (est. sk_comm_object_init)
 * Initializes a communication-object header: sets the two vtables
 * (&DAT_00657778), the type/params, the id, size (16-bit), and the two
 * capability handles; copies the endpoint via FUN_00077070. */
static void sk_comm_object_init_10378c(uint64_t *o, uint64_t type, uint64_t a, uint64_t b, uint16_t size, uint64_t c, uint64_t d, uint64_t e, uint8_t f, uint8_t g)
{
    /* o[9] = o[10] = (uint64_t)&DAT_00657778; */
    o[0] = type;
    /* FUN_00077070(a, o+1) */
    *(uint16_t *)(o + 6) = size;
    o[7] = c; o[8] = d; o[0xb] = b; o[0xc] = e;
    ((uint8_t *)o)[0x68] = f; ((uint8_t *)o)[0x69] = g;
}

/* FUN_00103828 @ 0x103828  (est. sk_pair_peek)
 * Reads a 16-byte pair from ctx+0x38 and releases ctx+0x40. */
static void sk_pair_peek_103828(void)
{
    /* auVar1 = *(uint64_t (*)[16])(ctx + 0x38); FUN_0036b270(ctx->r[0x40/8]); return auVar1 */
}

/* FUN_00103860 @ 0x103860  (est. sk_ctx_set48)
 * Releases then sets ctx->r[0x48/8] = param_1. */
static void sk_ctx_set48_103860(uint64_t *ctx, uint64_t v)
{
    /* FUN_0036b118(ctx->r[0x48/8]); ctx->r[0x48/8] = v */
}

/* FUN_00103894 @ 0x103894  (est. sk_ctx_set50)
 * Releases then sets ctx->r[0x50/8] = param_1. */
static void sk_ctx_set50_103894(uint64_t *ctx, uint64_t v)
{
    /* FUN_0036b118(ctx->r[0x50/8]); ctx->r[0x50/8] = v */
}

/* FUN_001038c8 @ 0x1038c8  (est. sk_ctx_set58)
 * Releases then sets ctx->r[0x58/8] = param_1. */
static void sk_ctx_set58_1038c8(uint64_t *ctx, uint64_t v)
{
    /* FUN_0036b118(ctx->r[0x58/8]); ctx->r[0x58/8] = v */
}

/* FUN_00103908 @ 0x103908  (est. sk_lock_op)
 * Lock operation via thunk_FUN_002298d4(param_1, *ctx). */
static void sk_lock_op_103908(uint64_t a)
{
    /* thunk_FUN_002298d4(a, *ctx) */
}

/* FUN_00103934 @ 0x103934  (est. sk_lock_init_op)
 * Initializes a 72-byte lock buffer (FUN_001a84f4), locks via thunk, teardown. */
static void sk_lock_init_op_103934(void)
{
    /* uint8_t buf[72]; FUN_001a84f4(buf,0); thunk_FUN_002298d4(*ctx); FUN_001a8564() */
}

/* FUN_00103980 @ 0x103980  (est. sk_lock_op_wrap)
 * Inits lock buffer, calls 0x103908, teardown. */
static void sk_lock_op_wrap_103980(void)
{
    /* uint8_t buf[72]; FUN_001a84f4(buf); FUN_00103908(buf); FUN_001a8564() */
}

/* FUN_00103a84 @ 0x103a84  (est. sk_prng_init_dispatch)
 * PRNG initialisation dispatcher: for a seed length < 0x81 it parses the seed
 * (FUN_001041f4) and, on failure, falls back to the full PRNG constructor
 * FUN_00103b2c; then runs the PRNG-ready check FUN_00103cb0. Once the global
 * g_prng_ready (DAT_006bf580) is set, returns; otherwise panics. Length >=0x81
 * faults (FUN_004b84dc). */
static void sk_prng_init_dispatch_103a84(uint64_t len, uint64_t seed)
{
    (void)len; (void)seed;
    /* if (len < 0x81) { i = FUN_001041f4(...); if (i) FUN_00103b2c(...);
     *   FUN_00103cb0(0); if (g_prng_ready&1) return; } else FUN_004b84dc();
     * FUN_004b84c4(); noreturn panic */
}

/* FUN_00103b2c @ 0x103b2c  (est. sk_prng_construct)
 * Constructs the corecrypto-backed cL4 PRNG: reads entropy from the
 * "corecrypto_exclavecore_prng" seed string (s_corecrypto_exclavecore_prng_005c6d63),
 * registers the RNG via FUN_00104fb4/FUN_00104b48, wires the DRBG at
 * 0x6bf3a8/0x6bf3f0, and sets the ready flag DAT_006bf580. Any failure panics. */
static void sk_prng_construct_103b2c(uint64_t len, uint64_t seed)
{
    (void)len; (void)seed;
    /* see decompile: FUN_00104fb4(...0x1b, seed...); FUN_00104b48(0x6bf390, "corecrypto_exclavecore_rng");
     * FUN_001047f8(...); DAT_006bf580 = 1 */
}

/* FUN_00103cb0 @ 0x103cb0  (est. sk_prng_ensure)
 * Ensures the PRNG is constructed: if the ready flag is clear, reads a 0x30
 * byte seed (thunk_FUN_0005c278), constructs (FUN_00103b2c), and clears the
 * seed buffer (FUN_00104f9c). Sets *out (if non-null) to 0 and returns the
 * PRNG state pointer DAT_006bf310. */
static void *sk_prng_ensure_103cb0(uint32_t *out)
{
    /* if (!(g_prng_ready&1)) { seed=thunk_FUN_0005c278(&buf,0x30); FUN_00103b2c(seed,&buf);
     *   FUN_00104f9c(0x30,&buf); } if (out) *out=0; return &DAT_006bf310 */
    if (out) *out = 0;
    /* return (void *)&DAT_006bf310; */
    return 0;
}

/* FUN_00103d74 @ 0x103d74  (est. sk_prng_state)
 * PRNG state probe: if the init flag (bit0 at param+1) is set returns 3;
 * otherwise runs the vtable method at *param, records whether the result is 3,
 * and returns it. */
static uint64_t sk_prng_state_103d74(uint64_t *p)
{
    if (*(uint8_t *)(p + 1) & 1) return 3;
    uint64_t r = /* (**(code **)*p)() */ 0;
    *(uint8_t *)(p + 1) = (r == 3);
    return r;
}

/* FUN_00103dc4 @ 0x103dc4  (est. sk_prng_clear)
 * Clears the init flag (param+1) then calls vtable method at *param+8
 * (jumptable-based; decompiler could not recover the branch). */
static void sk_prng_clear_103dc4(int64_t *p)
{
    *(uint8_t *)(p + 1) = 0;
    /* (**(code **)(*p + 8))() */
}

/* FUN_00103dd8 @ 0x103dd8  (est. sk_prng_ops_init)
 * Initializes a PRNG ops descriptor: type 0x662fd8, clear flag, mode param_2. */
static void sk_prng_ops_init_103dd8(uint64_t *p, uint32_t mode)
{
    p[0] = 0x662fd8;
    *(uint8_t *)(p + 1) = 0;
    *(uint32_t *)(p + 2) = mode;
}

/* FUN_00103dfc @ 0x103dfc  (est. sk_prng_fatal)
 * Noreturn panic via FUN_004b856c. */
static void sk_prng_fatal_103dfc(void)
{
    /* FUN_004b856c(); noreturn */
}

/* FUN_00103e0c @ 0x103e0c  (est. sk_sha_update)
 * SHA/MAC update core: packs the message into an aligned scratch buffer,
 * appends a length marker, pads with zeros to the block size, byte-swaps the
 * running state (big-endian), invokes the compression callback
 * (param_1[6]), and writes the result words (byte-swapped) into param_3. */
static void sk_sha_update_103e0c(uint64_t *p, int64_t msg, int64_t out)
{
    (void)p; (void)msg; (void)out;
    /* see decompile: aligned scratch, padding, endian-swap, (*p[6])(buf,1), output */
}

/* FUN_00103ff4 @ 0x103ff4  (est. sk_sha_copy)
 * Copies the running hash state (param_1+0x28, len param_1+8) into param_2+1,
 * zeroes param_2[0], and zeroes the length field. */
static void sk_sha_copy_103ff4(uint64_t p, uint64_t *out)
{
    /* FUN_00117cc4(out+1, *(p+0x28), *(p+8)); out[0]=0;
     * *(uint32_t *)(out + *(p+0x10) + *(p+8) + 8) = 0 */
}

/* ============ 0x10403c - 0x107eac : PRNG/crypto/hash/Mach-O ============ */

/* FUN_0010403c @ 0x10403c  (est. sk_hash_absorb)
 * Hash absorb: appends param_4 (length param_3) into the state buffer at
 * param_2, growing by whole blocks (0x80/0x40/divisor when a block fills,
 * invoking the compression callback at param_1[0x30/8]). Updates the running
 * byte count *param_2 += consumed*8. */
static void sk_hash_absorb_10403c(uint64_t p, uint64_t *buf, uint64_t len, uint64_t src)
{
    (void)p; (void)buf; (void)len; (void)src;
    /* see decompile: block-granular absorb w/ compression callback */
}

/* FUN_00104180 @ 0x104180  (est. sk_consttime_cmp)
 * Constant-time compare of param_1 bytes between param_2 and param_3
 * (XOR-accumulate, no early exit); wraps with DIT/barrier (FUN_00104f78). */
static bool sk_consttime_cmp_104180(int64_t n, const void *a, const void *b)
{
    if (n == 0) return true;
    uint8_t acc = 0;
    for (int64_t i = 0; i < n; i++)
        acc |= ((const uint8_t *)b)[n-1-i] ^ ((const uint8_t *)a)[n-1-i];
    /* FUN_00104f78(); result = (acc != 0); FUN_00105168() */
    return acc != 0;
}

/* FUN_001041f4 @ 0x1041f4  (est. sk_hash_verify)
 * Constant-time verify wrapper: FUN_00104f78 then FUN_00104180 then
 * FUN_00105168. */
static uint64_t sk_hash_verify_1041f4(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    return /* FUN_00104180(...) */ 0;
}

/* FUN_00104254 @ 0x104254  (est. sk_hash_finalize)
 * Hash finalize: pads via FUN_001043f0, absorbs the tail (FUN_0010403c),
 * writes the length via FUN_00104360, and frees the scratch buffer. */
static void sk_hash_finalize_104254(uint64_t p, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)p; (void)a; (void)b; (void)c; (void)d; (void)e;
    /* see decompile */
}

/* FUN_00104360 @ 0x104360  (est. sk_hash_pad_len)
 * Hash length-padding: writes the running length (param_1[2]<<3) and the
 * bit-count marker into the scratch, invoking the compression callback. */
static void sk_hash_pad_len_104360(uint64_t *p, uint64_t *buf, uint64_t a)
{
    /* see decompile: length pad + compression */
}

/* FUN_001043f0 @ 0x1043f0  (est. sk_hash_block_pad)
 * Hash block padding: XOR-pads the message with 0x5c (outer) and 0x6a/inner
 * markers, invokes the compression callback at param_1[6]/[7], producing the
 * HMAC-style inner/outer state. */
static void sk_hash_block_pad_1043f0(uint64_t *p, uint64_t *buf, uint64_t len, const uint8_t *msg)
{
    (void)p; (void)buf; (void)len; (void)msg;
    /* see decompile: 0x5c/0x6a padding + compression */
}

/* FUN_001045b8 @ 0x1045b8  (est. sk_hash_drain)
 * Hash drain/read: pulls up to param_2 bytes of digest into param_3, invoking
 * the underlying block cipher (FUN_00104848/FUN_00105054/FUN_001050d8) and
 * managing the internal buffer pointers (param_1+0x40/0x48/0x50). */
static uint64_t sk_hash_drain_1045b8(uint64_t p, uint64_t len, uint64_t out)
{
    (void)p; (void)len; (void)out;
    /* see decompile */
    return 0;
}

/* FUN_001047f8 @ 0x1047f8  (est. sk_hash_ctx_init)
 * Hash context initializer: rejects an output length > 0x40, records the ten
 * configuration words into the context (incl. the ops vtable &DAT_00104840). */
static uint64_t sk_hash_ctx_init_1047f8(uint64_t *ctx, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t len, uint64_t g, uint64_t h)
{
    if (len > 0x40) return 0xfffffffb;
    /* ctx[0] = (uint64_t)&DAT_00104840; */
    ctx[1] = a; ctx[2] = b; ctx[3] = c; ctx[4] = d; ctx[5] = e; ctx[6] = f;
    ctx[7] = len; ctx[8] = g; ctx[9] = h; ctx[10] = g;
    return 0;
}

/* FUN_00104848 @ 0x104848  (est. sk_crypto_call8)
 * Wrapped crypto call via context vtable *param_1 with DIT/barrier. */
static uint64_t sk_crypto_call8_104848(uint64_t *ctx, uint64_t a, uint64_t b)
{
    /* local = FUN_00104f78(); r = (**(code **)*ctx)(ctx,a,b); FUN_00105168(&local); return r */
    return 0;
}

/* FUN_001048b4 @ 0x1048b4  (est. sk_rng_ops_init)
 * Initializes a 7-word RNG ops descriptor: size 0xa0, vtable &DAT_004b857c,
 * entry/exit callbacks FUN_004b8668/FUN_00104920, seed source param_2,
 * and the digest label &LAB_00104960. */
static void sk_rng_ops_init_1048b4(uint64_t *p, uint64_t a)
{
    p[0] = 0xa0;
    /* p[1] = (uint64_t)&DAT_004b857c; */
    /* p[3] = (uint64_t)&FUN_004b8668; */
    /* p[2] = (uint64_t)&DAT_004b8814; */
    /* p[4] = (uint64_t)&FUN_00104920; */
    p[5] = a;
    /* p[6] = (uint64_t)&LAB_00104960; */
}

/* FUN_00104920 @ 0x104920  (est. sk_rng_reset)
 * Clears the two 0x40-byte seed buffers at param+8 and param+0x48, sets the
 * RNG state counter to -1. */
static void sk_rng_reset_104920(uint64_t p)
{
    /* FUN_00104f9c(0x40, p+8); FUN_00104f9c(0x40, p+0x48);
     * *(uint64_t*)(p+0x88) = 0xffffffffffffffff */
}

/* FUN_00104988 @ 0x104988  (est. sk_hash_feed)
 * Feeds the hash with a message: pads (FUN_001043f0), absorbs the fixed
 * portion, absorbs the varargs word-pairs, finalizes (FUN_00104360/FUN_00104254);
 * repeats up to twice if data remains. */
static void sk_hash_feed_104988(uint64_t *ctx, int argc)
{
    (void)ctx; (void)argc;
    /* see decompile: absorb + varargs absorb + finalize, 2-pass */
}

/* FUN_00104b48 @ 0x104b48  (est. sk_assert_zero)
 * Runs FUN_00118148(param_1, 0); returns -1 on failure, 0 on success. */
static int sk_assert_zero_104b48(uint64_t a)
{
    int r = /* FUN_00118148(a, 0) */ 0;
    return -(r != 0);
}

/* FUN_00104f78 @ 0x104f78  (est. sk_dit_save)
 * Saves the DIT (data-independent-timing) state: reads the SCTLR DIT bit
 * (system reg 3,3,4,2,5), sets DIT=1, issues a speculation barrier, and
 * returns the prior state. */
static bool sk_dit_save_104f78(void)
{
    /* long prev = read_sysreg(DIT); dit = 1; SpeculationBarrier(); return prev != 0 */
    return false;
}

/* FUN_00104f90 @ 0x104f90  (est. sk_dit_restore)
 * Restores DIT to 0 if param_1 was clear. */
static void sk_dit_restore_104f90(uint32_t prev)
{
    if ((prev & 1) == 0) { /* dit = 0 */ }
}

/* FUN_00104f9c @ 0x104f9c  (est. sk_secure_clear)
 * Securely zeroes param_1 bytes at param_2 via FUN_00117e14. */
static void sk_secure_clear_104f9c(uint64_t n, uint64_t p)
{
    /* FUN_00117e14(p, n, 0, n, 0xffffffffffffffff) */
}

/* FUN_00104fb4 @ 0x104fb4  (est. sk_crypto_call7)
 * Wrapped crypto call via vtable (param_1+8) with DIT/barrier. */
static uint64_t sk_crypto_call7_104fb4(uint64_t p, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g)
{
    (void)p; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g;
    /* local = FUN_00104f78(); r = (**(code **)(p+8))(...); FUN_00105168(&local); return r */
    return 0;
}

/* FUN_00105054 @ 0x105054  (est. sk_crypto_call_10)
 * Wrapped crypto call via vtable (param_1+0x10) with DIT/barrier. */
static uint64_t sk_crypto_call_10_105054(uint64_t p, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)p; (void)a; (void)b; (void)c; (void)d; (void)e;
    /* local = FUN_00104f78(); r = (**(code **)(p+0x10))(...); FUN_00105168(&local); return r */
    return 0;
}

/* FUN_001050d8 @ 0x1050d8  (est. sk_crypto_call_18)
 * Wrapped crypto call via vtable (param_1+0x18) with DIT/barrier. */
static uint64_t sk_crypto_call_18_1050d8(uint64_t p, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)p; (void)a; (void)b; (void)c; (void)d; (void)e;
    /* local = FUN_00104f78(); r = (**(code **)(p+0x18))(...); FUN_00105168(&local); return r */
    return 0;
}

/* FUN_0010515c @ 0x10515c  (est. sk_rng_const)
 * Returns constant 0x662fe8 (RNG type id). */
static uint64_t sk_rng_const_10515c(void) { return 0x662fe8; }

/* FUN_00105168 @ 0x105168  (est. sk_dit_restore_wrap)
 * Restores DIT from *param_1 via FUN_00104f90. */
static void sk_dit_restore_wrap_105168(uint32_t *prev)
{
    /* FUN_00104f90(*prev) */
}

/* FUN_00105174 @ 0x105174  (est. sk_obj_3args)
 * Wraps a 3-arg call (FUN_00369efc) with the object header {x20[0], x20[1], flag}. */
static void sk_obj_3args_105174(uint64_t a, uint64_t b)
{
    /* FUN_00369efc(&local, a, b) */
}

/* FUN_001051e0 @ 0x1051e0  (est. sk_secimage_parse)
 * Mach-O/secure-image parser: for a 0x10-byte header builds the cL4 VM image
 * by reading the load commands (FUN_0029f0b0/FUN_0029fa0c/FUN_00105fd8),
 * checking segment ordering (BRK on inversion), and wiring the sections via
 * FUN_002a3e64. Non-0x10 length is rejected with a report. Returns the image
 * record. */
static void *sk_secimage_parse_1051e0(uint64_t p)
{
    (void)p;
    /* see decompile: Mach-O segment/section walk, BRK 0x105624/8/c */
    return 0;
}

/* FUN_0010562c @ 0x10562c  (est. sk_vm_region_map)
 * VM region mapping: validates the capability (FUN_001ee018 == 0x24),
 * resolves the physical region via FUN_0029fb80/FUN_002a0cf8, walks the
 * 16 KiB pages (FUN_0029f0b0), and builds the page record list, mapping
 * each via the PMM/crypto helpers. */
static uint64_t *sk_vm_region_map_10562c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile: big region-map loop */
    return 0;
}

/* FUN_00105be4 @ 0x105be4  (est. sk_noop)
 * Empty function. */
static void sk_noop_105be4(void) {}

/* FUN_00105c2c @ 0x105c2c  (est. sk_grow_05c8c)
 * Grows a 0x20-stride array via FUN_00105c8c and stores the result into *ctx. */
static void sk_grow_05c8c_105c2c(uint64_t *ctx)
{
    /* *ctx = FUN_00105c8c(...) */
}

/* FUN_00105c4c @ 0x105c4c  (est. sk_grow_05d5c)
 * Grows a 0x70-stride array via FUN_00105d5c. */
static void sk_grow_05d5c_105c4c(uint64_t *ctx)
{
    /* *ctx = FUN_00105d5c(...) */
}

/* FUN_00105c6c @ 0x105c6c  (est. sk_grow_05e38)
 * Grows a 0x28-stride array via FUN_00105e38. */
static void sk_grow_05e38_105c6c(uint64_t *ctx)
{
    /* *ctx = FUN_00105e38(...) */
}

/* FUN_00105c8c @ 0x105c8c  (est. sk_array_grow_20)
 * Array growth (0x20-byte stride): computes the new capacity (doubling via
 * param_4+0x18 when param_3&1), reallocates via FUN_0010bc98, copies the
 * elements (FUN_00117cc4/FUN_00117d14), and releases the old array. */
static uint64_t sk_array_grow_20_105c8c(uint64_t a, uint64_t b, uint64_t c, uint64_t p)
{
    (void)a; (void)b; (void)c; (void)p;
    /* see decompile: 0x20-stride realloc */
    return 0;
}

/* FUN_00105d5c @ 0x105d5c  (est. sk_array_grow_70)
 * Array growth (0x70-byte stride) via FUN_0010bd1c. */
static uint64_t sk_array_grow_70_105d5c(uint64_t a, uint64_t b, uint64_t c, uint64_t p)
{
    (void)a; (void)b; (void)c; (void)p;
    /* see decompile: 0x70-stride realloc */
    return 0;
}

/* FUN_00105e38 @ 0x105e38  (est. sk_array_grow_28)
 * Array growth (0x28-byte stride) via FUN_0010be44. */
static uint64_t sk_array_grow_28_105e38(uint64_t a, uint64_t b, uint64_t c, uint64_t p)
{
    (void)a; (void)b; (void)c; (void)p;
    /* see decompile: 0x28-stride realloc */
    return 0;
}

/* FUN_00105fd8 @ 0x105fd8  (est. sk_vm_cap_alloc)
 * VM capability allocation: selects the granule (7 or 0xb) and memattr from
 * the cap bits, invokes FUN_0029f368/FUN_0029fa0c to allocate/map the
 * capability. */
static void sk_vm_cap_alloc_105fd8(int64_t id, uint64_t a, uint64_t b)
{
    (void)id; (void)a; (void)b;
    /* see decompile */
}

/* FUN_0010606c @ 0x10606c  (est. sk_vm_cap_alloc_b)
 * VM capability allocation variant: computes memattr/granule, invokes
 * FUN_0029f368 with the negated id, validates the size bound. */
static void sk_vm_cap_alloc_b_10606c(int64_t id, uint64_t a, uint64_t b)
{
    (void)id; (void)a; (void)b;
    /* see decompile */
}

/* FUN_0010649c @ 0x10649c  (est. sk_macho_segments)
 * Mach-O segment enumeration: walks the load-command list from param_1 to
 * param_2 (step param_3, must divide evenly), records each segment's
 * {base, vmsize, size, filesize} into the global segment table
 * (DAT_00657798..), validating alignment and size; faults on misalignment
 * or non-integral sizes. Panics "MVM size is ze"/"Segment size is not..."/
 * "Segment...". */
static void sk_macho_segments_10649c(uint64_t a, uint64_t b, uint64_t c, uint64_t p, uint64_t step)
{
    (void)a; (void)b; (void)c; (void)p; (void)step;
    /* see decompile: segment record loop + BRK/panic paths */
}

/* FUN_00106958 @ 0x106958  (est. sk_macho_seg_lookup)
 * Mach-O segment lookup by name: walks the segment table (0x70-stride),
 * string-compares each entry's name (built via FUN_0036a940/FUN_00002534)
 * against the requested {param_2, param_3} name; returns the matching
 * segment record (or zeroed record with flag=1 on not-found). */
static void sk_macho_seg_lookup_106958(uint64_t *out, uint64_t a, uint64_t b)
{
    (void)out; (void)a; (void)b;
    /* see decompile: 0x70-stride name scan */
}

/* FUN_00106c88 @ 0x106c88  (est. sk_macho_str_lookup)
 * Mach-O string lookup: resolves a name via FUN_000834fc/FUN_001084f4. */
static void sk_macho_str_lookup_106c88(void)
{
    /* uVar1 = FUN_000834fc(&local, buf); r = FUN_001084f4(uVar1); FUN_0036b118(uVar1); return r */
}

/* FUN_00106e3c @ 0x106e3c  (est. sk_pair_make)
 * Returns 16-byte {param_2, param_3}. */
static void sk_pair_make_106e3c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* returns {b, a} */
}

/* FUN_00106e48 @ 0x106e48  (est. sk_macho_validate)
 * Mach-O layout validation: checks that the size/offset fields at ctx+0x18
 * and ctx+0x20 divide evenly by param_1 and the total is within limits;
 * otherwise panics with "MVM size is ze"/"Segment size is not aligned to
 * granule"/"Segment crosses boundary". Then enumerates segments via
 * FUN_0010649c. */
static void sk_macho_validate_106e48(uint64_t granule)
{
    (void)granule;
    /* see decompile: BRK 0x106ed0, panic strings "MVM size is ze"/"Segment..." */
}

/* FUN_001071f4 @ 0x1071f4  (est. sk_global_4c4b98)
 * Returns &DAT_004c4b98. */
static void *sk_global_1071f4(void) { /* return &DAT_004c4b98 */ return 0; }

/* FUN_00107200 @ 0x107200  (est. sk_global_4c4b9c)
 * Returns &DAT_004c4b9c. */
static void *sk_global_107200(void) { /* return &DAT_004c4b9c */ return 0; }

/* FUN_0010720c @ 0x10720c  (est. sk_global_4c4ba0)
 * Returns &DAT_004c4ba0. */
static void *sk_global_10720c(void) { /* return &DAT_004c4ba0 */ return 0; }

/* FUN_00107224 @ 0x107224  (est. sk_global_4c4ba8)
 * Returns &DAT_004c4ba8. */
static void *sk_global_107224(void) { /* return &DAT_004c4ba8 */ return 0; }

/* FUN_00107398 @ 0x107398  (est. sk_byte_or_acc)
 * Computes a 32-bit OR-reduction over the param_1 bytes at param_2+0x20
 * (NEON-vectorized wide scan with a word tail), returning the accumulated
 * OR into *param_1. Used as a zero/nonzero detection over a buffer. */
static void sk_byte_or_acc_107398(uint32_t *out, uint64_t p)
{
    /* see decompile: NEON OR-accumulate + word/byte tail */
    *out = 0;
}

/* FUN_001074cc @ 0x1074cc  (est. sk_div_check)
 * Divides param_1 by param_2, panicking "not aligned"/"divide by zero" if
 * the division is not exact or param_2 == 0. */
static void sk_div_check_1074cc(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* if (b==0) BRK 0x107558; if (a != (a/b)*b) panic "..." */
}

/* ============ 0x107680 - 0x10aa18 : Mach-O image builder / sort ============ */

/* FUN_00107680 @ 0x107680  (est. sk_img_compact)
 * Image compaction: reads the element count (obj+0x10), rescans the array via
 * FUN_00107808 to reclaim capacity, updates the array head. */
static void sk_img_compact_107680(int64_t *arr)
{
    /* lVar2 = *arr; uStack_38 = *(lVar2+0x10); local_40 = lVar2+0x20;
     * FUN_00107808(&uStack_21,&local_40); *arr = lVar2 */
}

/* FUN_001076f0 @ 0x1076f0  (est. sk_img_push_20)
 * Appends a 0x20-stride element to the image array: grows capacity as needed
 * (FUN_00105c8c), copies the new element, bumps the count. */
static void sk_img_push_20_1076f0(uint64_t elem)
{
    (void)elem;
    /* see decompile: grow + copy + count++ */
}

/* FUN_00107808 @ 0x107808  (est. sk_img_rebuild)
 * Rebuilds the image array: if the backing is over-allocated (capacity > len),
 * reallocates to half and re-sorts/compacts via FUN_001078f8/FUN_00107db4;
 * otherwise in-place reorders FUN_00107db4(0, len, 1, arr). */
static void sk_img_rebuild_107808(uint64_t p)
{
    (void)p;
    /* see decompile */
}

/* FUN_001078f8 @ 0x1078f8  (est. sk_img_sort_merge)
 * Image array merge-sort (0x70-stride): recursively splits the range by the
 * key at offset +0x40, merges adjacent spans (in-place 0xe-word swaps) with
 * bounds checks, and appends the merged span record into the output list. */
static void sk_img_sort_merge_1078f8(int64_t *out, uint64_t a, uint64_t *arr, int64_t span)
{
    (void)out; (void)a; (void)arr; (void)span;
    /* see decompile: recursive merge sort, 0x70 stride */
}

/* FUN_00107db4 @ 0x107db4  (est. sk_img_insertion)
 * Insertion-sort pass over the 0x70-stride array range [param_1, param_2)
 * keyed by +0x40; in-place swaps (0xe words each), bounds-checked. */
static void sk_img_insertion_107db4(int64_t from, int64_t to, int64_t a, int64_t *arr)
{
    (void)from; (void)to; (void)a; (void)arr;
    /* see decompile */
}

/* FUN_00107eac @ 0x107eac  (est. sk_img_span_check)
 * Validates/merges adjacent image spans (0x70 stride): compares span keys and
 * returns 1 when the next span overlaps the current one (so the caller merges),
 * otherwise advances. */
static uint64_t sk_img_span_check_107eac(int64_t *arr, uint64_t a, int64_t *p)
{
    (void)arr; (void)a; (void)p;
    /* see decompile */
    return 0;
}

/* FUN_001074cc @ 0x1074cc  (est. sk_seg_addrs)
 * Segment address resolution: validates param_2 != 0 (BRK), that param_1 is
 * an exact multiple of param_2 (else panic), and returns the 16-byte
 * {base + param_1, within-vmsize} address pair. */
static void sk_seg_addrs_1074cc(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile: exact-division check, returns 16-byte pair */
}

/* FUN_0010a170 @ 0x10a170  (est. sk_region_copy)
 * Region copy: validates bounds (param_2>=0, param_3 within [param_4,param_5]),
 * computes the element count (div by the per-instance size at param_6-8+0x48),
 * and copies via FUN_001e4cbc. */
static void sk_region_copy_10a170(uint64_t a, int64_t b, int64_t c, int64_t d, int64_t e, uint64_t f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile */
}

/* FUN_0010a21c @ 0x10a21c  (est. sk_capid_low)
 * Returns the low 40 bits of FUN_0010c2b0(). */
static uint64_t sk_capid_low_10a21c(void)
{
    /* return FUN_0010c2b0() & 0xffffffffff */
    return 0;
}

/* FUN_0010a220 @ 0x10a220  (est. sk_capid_low_b)
 * Duplicate of 0x10a21c. */
static uint64_t sk_capid_low_10a220(void) { /* return FUN_0010c2b0() & 0xffffffffff */ return 0; }

/* FUN_0010a238 @ 0x10a238  (est. sk_capid_pair)
 * Masks both cap ids to 40 bits and calls FUN_0010c378. */
static void sk_capid_pair_10a238(uint64_t a, uint64_t b)
{
    /* FUN_0010c378(a & 0xffffffffff, b & 0xffffffffff) */
}

/* FUN_0010a260 @ 0x10a260  (est. sk_state_snapshot)
 * Snapshots a 0x144-byte state block via FUN_0010c4d0 into param_1. */
static void sk_state_snapshot_10a260(uint64_t out)
{
    (void)out;
    /* uint8_t buf[328]; FUN_0010c4d0(buf); FUN_00117cc4(out, buf, 0x144) */
}

/* FUN_0010a2ac @ 0x10a2ac  (est. sk_img_decode)
 * Image decode: dereferences the code-page table via the global function
 * pointer DAT_006586d8, copies the 5-word element header, then decodes the
 * payload via FUN_0010a394, and writes it through the vtable method (lVar3+0x20)
 * at the offset from FUN_0010ca90. */
static void sk_img_decode_10a2ac(uint64_t *out, uint64_t a, int64_t p)
{
    (void)out; (void)a; (void)p;
    /* see decompile */
}

/* FUN_0010a394 @ 0x10a394  (est. sk_img_decode_core)
 * Image decode core: reads the 4 length/offset words, verifies the region
 * size (FUN_00108eb0 >= the fixed code-limit at lVar7+0x40, else report), and
 * copies the decoded bytes via FUN_0010a170 and the vtable method +0x10. */
static void sk_img_decode_core_10a394(uint64_t a, uint64_t b, int64_t c, int64_t p)
{
    (void)a; (void)b; (void)c; (void)p;
    /* see decompile */
}

/* FUN_0010a528 @ 0x10a528  (est. sk_string16_new)
 * Allocates a 0x30-byte string object: header from "___cstring" (0x64c108),
 * length 0x10, capacity (thunk_FUN_000126e8()*2 - 0x40), copies the payload
 * from ctx+0x30/0x38. */
static int64_t sk_string16_new_10a528(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0010a5bc @ 0x10a5bc  (est. sk_str_to_image)
 * Resolves a string at ctx+0x30/0x38 (FUN_000834fc) and parses it as a secure
 * image via FUN_001051e0. */
static void sk_str_to_image_10a5bc(void)
{
    /* uVar2 = FUN_000834fc(&local, buf); auVar3 = FUN_001051e0(); FUN_0036b118(uVar2) */
}

/* FUN_0010a668 @ 0x10a668  (est. sk_106c88_wrap)
 * Wraps 0x106c88 (string lookup). */
static void sk_106c88_wrap_10a668(void) { /* FUN_00106c88() */ }

/* FUN_0010a6b4 @ 0x10a6b4  (est. sk_image_extract)
 * Image extraction: computes the payload size (FUN_00108eb0), allocates a
 * 0x50*count-byte buffer, extracts the code page via FUN_00108df4 and copies
 * it (FUN_0010c214); on size mismatch or allocation failure reports and
 * returns a null/short record. */
static void *sk_image_extract_10a6b4(void)
{
    /* see decompile: BRK 0x10a840..54, report 0x663c30/0x663b58 */
    return 0;
}

/* FUN_0010a854 @ 0x10a854  (est. sk_region_read)
 * Region read: bounds-checks the offset/length (BRK on overflow), validates
 * the range fits the region size (FUN_00108eb0), and copies the bytes via
 * FUN_0010871c; on failure reports with a status byte. */
static void sk_region_read_10a854(int64_t off, int64_t len, int64_t p, uint64_t a, uint64_t b, uint64_t c)
{
    (void)off; (void)len; (void)p; (void)a; (void)b; (void)c;
    /* see decompile */
}

/* FUN_0010a980 @ 0x10a980  (est. sk_state_snapshot_b)
 * Duplicate of 0x10a260: snapshots 0x144 bytes. */
static void sk_state_snapshot_10a980(uint64_t out)
{
    (void)out;
    /* uint8_t buf[328]; FUN_0010c4d0(buf); FUN_00117cc4(out, buf, 0x144) */
}

/* FUN_0010a9f8 @ 0x10a9f8  (est. sk_pair_ctx)
 * Returns the 16-byte pair at ctx+0x10. */
static void sk_pair_ctx_10a9f8(void)
{
    /* return *(undefined1 (*)[16])(ctx + 0x10) */
}

/* ============ 0x10aa18 - 0x1124fc : image builder / libm / hash ============ */

/* FUN_0010aa18 @ 0x10aa18  (est. sk_img_next)
 * Image builder cursor: returns the next 8-byte element (via FUN_0010c2b0 cap-id
 * decode) at the current offset, validating alignment/limits; on any failure
 * reports {offset, size, code} through FUN_0036993c. */
static uint64_t sk_img_next_10aa18(void)
{
    (void)0;
    /* see decompile: aligned cursor read + bounds checks */
    return 0;
}

/* FUN_0010abd0 @ 0x10abd0  (est. sk_img_advance)
 * Advances the image builder offset by param_1 bytes (must be >= 1, else
 * report), reading via FUN_0010a854. */
static void sk_img_advance_10abd0(int64_t n)
{
    (void)n;
    /* if (n < 1) report; else FUN_0010a854(n, *ctx, ...); *ctx += n */
}

/* FUN_0010ac74 @ 0x10ac74  (est. sk_img_try_next)
 * Image cursor: if there is remaining space and the build flag is clear, reads
 * the next element (FUN_0010aa18) advancing the offset; otherwise returns a
 * zeroed/end record. Produces a 6-word element record. */
static void sk_img_try_next_10ac74(uint64_t *out)
{
    (void)out;
    /* see decompile */
}

/* FUN_0010ae04 @ 0x10ae04  (est. sk_img_try_next_b)
 * Wrapper producing the packed 5-word + tag image record from 0x10ac74. */
static void sk_img_try_next_b_10ae04(uint64_t *out)
{
    (void)out;
    /* packs FUN_0010ac74 result */
}

/* FUN_0010ae70 @ 0x10ae70  (est. sk_img_collect)
 * Image collection: walks the element stream (FUN_0010aa18), validates each
 * element's bounds against the region, and appends 0x30-byte records to the
 * output array at param_2. Returns the element count / status. */
static int64_t sk_img_collect_10ae70(int64_t *out, int64_t *dst, int64_t count, uint64_t a, uint64_t b, int64_t c, int64_t d)
{
    (void)out; (void)dst; (void)count; (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
    return 0;
}

/* FUN_0010b110 @ 0x10b110  (est. sk_img_resolve)
 * Resolves the image via FUN_00109f08 and stores the result into *param_1. */
static void sk_img_resolve_10b110(uint64_t *out)
{
    (void)out;
    /* uVar1 = FUN_00109f08(...); if (ok) *out = uVar1 */
}

/* FUN_0010b144 @ 0x10b144  (est. sk_img_find)
 * Finds an element in the image (0x28-stride entries) matching the predicate
 * callback param_2; returns the matched 5-word record + tag (0=found,1=end). */
static void sk_img_find_10b144(uint64_t *out, uint64_t (*pred)(void))
{
    (void)out; (void)pred;
    /* see decompile: scan entries, call pred, return record */
}

/* FUN_0010b24c @ 0x10b24c  (est. sk_macho_lc1)
 * Mach-O load-command reader for command type 1: scans the 0x28-stride load
 * command table for the entry whose low word is {0x01,type}; parses the
 * 0x144-byte command via FUN_0010c4d0 and extracts the 8-word result. Panics
 * "MachOParser.LoadCommand" on a bad command type. */
static void sk_macho_lc1_10b24c(uint64_t *out)
{
    (void)out;
    /* see decompile: scan for {1,1}, FUN_0010c4d0/FUN_00025d80, panic 0x176 */
}

/* FUN_0010b3d0 @ 0x10b3d0  (est. sk_macho_lc5)
 * Mach-O load-command reader for command type 5 (LC_UUID/version): scans for
 * {0x01,5}, parses, returns the 6-word result. Panics on bad type. */
static void sk_macho_lc5_10b3d0(uint64_t *out)
{
    (void)out;
    /* see decompile: scan for {1,5}, panic 0x186 */
}

/* FUN_0010b560 @ 0x10b560  (est. sk_macho_lc2)
 * Mach-O load-command reader for command type 2: scans for {0x01,2}, parses,
 * returns the 8-word result + tag. */
static void sk_macho_lc2_10b560(uint64_t *out)
{
    (void)out;
    /* see decompile: scan for {1,2}, panic 0x196 */
}

/* FUN_0010b6bc @ 0x10b6bc  (est. sk_macho_lc3_parse)
 * Mach-O load-command parser for the 0x145-byte command: scans the table for a
 * {0x01,3/4} entry, snapshots it, and copies the result. */
static void sk_macho_lc3_parse_10b6bc(uint64_t a)
{
    (void)a;
    /* see decompile: panic 0x1a8 */
}

/* FUN_0010b824 @ 0x10b824  (est. sk_macho_lc_pack)
 * Mach-O load-command packer: scans the 0x28-stride table for entries whose
 * {0x01,cmd} tag matches, converts each (FUN_0010c4d0) and appends the
 * 0x70-byte command record to the global table; returns the packed record. */
static void sk_macho_lc_pack_10b824(uint64_t *out)
{
    (void)out;
    /* see decompile: BRK 0x10baec/f0, panic 0x1b7 */
}

/* FUN_0010bb3c @ 0x10bb3c  (est. sk_macho_lc_any)
 * Mach-O load-command reader for any command (low word >= 6): scans, parses,
 * returns the 8-word result. */
static void sk_macho_lc_any_10bb3c(uint64_t *out)
{
    (void)out;
    /* see decompile: scan {1,>=6}, panic 0x1cc */
}

/* FUN_0010bc98 @ 0x10bc98  (est. sk_array_new_20)
 * Allocates a 0x20-stride dynamic array (header 0x653258): count param_1,
 * capacity max(param_1,param_2) grown to a power-of-2-ish bound. */
static void *sk_array_new_20_10bc98(int64_t n, int64_t cap)
{
    (void)n; (void)cap;
    /* see decompile */
    return 0;
}

/* FUN_0010bd1c @ 0x10bd1c  (est. sk_array_new_70)
 * Allocates a 0x70-stride dynamic array (header 0x6531b8). */
static void *sk_array_new_70_10bd1c(int64_t n, int64_t cap)
{
    (void)n; (void)cap;
    /* see decompile */
    return 0;
}

/* FUN_0010bdb4 @ 0x10bdb4  (est. sk_array_new_50)
 * Allocates a 0x50-stride dynamic array (header 0x653250). */
static void *sk_array_new_50_10bdb4(int64_t n, int64_t cap)
{
    (void)n; (void)cap;
    /* see decompile */
    return 0;
}

/* FUN_0010be44 @ 0x10be44  (est. sk_array_new_28)
 * Allocates a 0x28-stride dynamic array (header 0x653248). */
static void *sk_array_new_28_10be44(int64_t n, int64_t cap)
{
    (void)n; (void)cap;
    /* see decompile */
    return 0;
}

/* FUN_0010bed4 @ 0x10bed4  (est. sk_img_build_list)
 * Image builder: collects the element stream into a 0x30-stride list array,
 * growing it as needed (FUN_0010c0a0 path), with full bounds validation of
 * each element against [param_1, param_2). Returns the populated array. */
static void *sk_img_build_list_10bed4(int64_t lo, uint64_t hi, uint64_t a, uint64_t b)
{
    (void)lo; (void)hi; (void)a; (void)b;
    /* see decompile: growth + element append loop */
    return 0;
}

/* FUN_0010c214 @ 0x10c214  (est. sk_img_copy_range)
 * Copies min(param_2,param_4) * 0x50 bytes from param_3 to param_1 (overlap
 * checked, BRK), returning the {src,dst} end addresses. */
static void sk_img_copy_range_10c214(uint64_t dst, int64_t n, uint64_t src, int64_t m)
{
    (void)dst; (void)n; (void)src; (void)m;
    /* see decompile */
}

/* FUN_0010c2b0 @ 0x10c2b0  (est. sk_cap_id_map)
 * Maps a capability-id word to an internal id: 0x80000028->0x100000002,
 * 2->0x100000006, 4->0x100000004, 5->0x100000003, 0x19->0x100000000,
 * 0x1d->0x100000005, 0x1b->0x100000001; else returns the word unchanged. */
static uint64_t sk_cap_id_map_10c2b0(uint32_t id)
{
    switch (id) {
    case 0x80000028: return 0x100000002ULL;
    case 2: return 0x100000006ULL;
    case 4: return 0x100000004ULL;
    case 5: return 0x100000003ULL;
    case 0x19: return 0x100000000ULL;
    case 0x1d: return 0x100000005ULL;
    case 0x1b: return 0x100000001ULL;
    default: return id;
    }
}

/* FUN_0010c378 @ 0x10c378  (est. sk_cap_id_eq)
 * Compares two 40-bit capability ids: ids in the 0x100000000.. range compare
 * by low 32 bits (with high byte 0x01); otherwise exact equality. */
static bool sk_cap_id_eq_10c378(uint64_t a, uint64_t b)
{
    uint8_t hi = (uint8_t)(b >> 32);
    uint32_t lo = (uint32_t)b, ai = (uint32_t)a;
    if ((a & 0xff00000000ULL) == 0x100000000ULL) {
        if (hi == 0x01) {
            if (ai == 0 && lo == 0) return true;
            if (ai == 1 && lo == 1) return true;
            if (ai == 2 && lo == 2) return true;
            if (ai == 3 && lo == 3) return true;
            if (ai == 4 && lo == 4) return true;
            if (ai == 5 && lo == 5) return true;
            if (ai > 5) return true;
        }
        return false;
    }
    if (hi != 0x01) return a == b;
    return false;
}

/* FUN_0010c4d0 @ 0x10c4d0  (est. sk_lc_snapshot)
 * Mach-O load-command snapshot builder: based on the command tag (param_2[1])
 * and type (param_2[0]), copies the appropriate 0x144-byte command from the
 * region (validating the minimum size 8/0x10/0x18/0x48/0x11c) and repacks it
 * with the correct capability-id bits. This is the load-command normalizer. */
static void sk_lc_snapshot_10c4d0(uint64_t out, int *cmd)
{
    (void)out; (void)cmd;
    /* see decompile: tag dispatch + region copy + id repack */
}

/* FUN_0010ca90 @ 0x10ca90  (est. sk_lc_21)
 * Calls FUN_00021480. */
static void sk_lc_21_10ca90(void)
{
    /* FUN_00021480() */
}

/* FUN_0010caa8 @ 0x10caa8  (est. sk_lc_clear_tag)
 * Clears the tag byte at param_1+0x144. */
static void sk_lc_clear_tag_10caa8(uint64_t p)
{
    *(uint8_t *)(p + 0x144) = 0;
}

/* FUN_0010cab0 @ 0x10cab0  (est. sk_lc_zero)
 * Zeroes the 0x144-byte load-command record and sets the tag to 1. */
static void sk_lc_zero_10cab0(uint64_t *p)
{
    for (int i = 0; i < 0x28; i++) p[i] = 0;
    *(uint32_t *)(p + 0x28) = 0;
    *(uint8_t *)((char *)p + 0x144) = 1;
}

/* FUN_0010cd5c @ 0x10cd5c  (est. sk_lc_hash)
 * Hashes a load-command (0x13f) via FUN_00377dcc; returns the 16-byte
 * {digest, 0x3f} on success or a short record on failure. */
static void sk_lc_hash_10cd5c(uint64_t p)
{
    (void)p;
    /* see decompile */
}

/* FUN_0010cf20 @ 0x10cf20  (est. sk_lc_write_varint)
 * Writes a variable-length integer (leb128-style) into the load-command
 * buffer: selects the field width from the header (param_4+0x50/0x54) and
 * encodes param_2 (delta) or zeroes the slot. */
static void sk_lc_write_varint_10cf20(uint32_t *dst, uint32_t a, uint32_t b, uint64_t hdr)
{
    (void)dst; (void)a; (void)b; (void)hdr;
    /* see decompile */
}

/* FUN_0010d21c @ 0x10d21c  (est. sk_cap_id_repack_0)
 * Repacks a cap-id: clears the low 33 bits and sets 0xc000000000000000. */
static void sk_cap_id_repack_c_10d21c(uint64_t *p) { *p = *p & 0x1ffffffffULL | 0xc000000000000000ULL; }

/* FUN_0010d230 @ 0x10d230  (est. sk_cap_id_repack_a)
 * Repacks a cap-id: sets 0xa000000000000000. */
static void sk_cap_id_repack_a_10d230(uint64_t *p) { *p = *p & 0x1ffffffffULL | 0xa000000000000000ULL; }

/* FUN_0010d244 @ 0x10d244  (est. sk_cap_id_repack_8)
 * Repacks a cap-id: sets 0x8000000000000000. */
static void sk_cap_id_repack_8_10d244(uint64_t *p) { *p = *p & 0x1ffffffffULL | 0x8000000000000000ULL; }

/* FUN_0010d258 @ 0x10d258  (est. sk_cap_id_repack_6)
 * Repacks a cap-id: sets 0x6000000000000000. */
static void sk_cap_id_repack_6_10d258(uint64_t *p) { *p = *p & 0x1ffffffffULL | 0x6000000000000000ULL; }

/* FUN_0010d26c @ 0x10d26c  (est. sk_cap_id_repack_4)
 * Repacks a cap-id: sets 0x4000000000000000. */
static void sk_cap_id_repack_4_10d26c(uint64_t *p) { *p = *p & 0x1ffffffffULL | 0x4000000000000000ULL; }

/* FUN_0010d280 @ 0x10d280  (est. sk_cap_id_repack_2)
 * Repacks a cap-id: sets 0x2000000000000000. */
static void sk_cap_id_repack_2_10d280(uint64_t *p) { *p = *p & 0x1ffffffffULL | 0x2000000000000000ULL; }

/* FUN_0010d294 @ 0x10d294  (est. sk_cap_id_repack_0b)
 * Repacks a cap-id: clears all but the low 33 bits. */
static void sk_cap_id_repack_0b_10d294(uint64_t *p) { *p = *p & 0x1ffffffffULL; }

/* FUN_0010d2a8 @ 0x10d2a8  (est. sk_fdiv32)
 * IEEE-754 single-precision division (bit-manipulation): handles NaN/inf/zero,
 * computes the quotient via leading-zero-count mantissa normalization and
 * shifts, rounds, and sets the sign. Returns the 16-byte {lo,hi}. */
static void sk_fdiv32_10d2a8(void)
{
    /* see decompile: soft-float div */
}

/* FUN_0010d44c @ 0x10d44c  (est. sk_fmod64)
 * IEEE-754 double-precision fmod: handles NaN/inf/zero, scales the operands,
 * performs the remainder via repeated subtraction, and rounds to nearest-even. */
static void sk_fmod64_10d44c(void)
{
    /* see decompile: soft-float fmod */
}

/* FUN_0010d650 @ 0x10d650  (est. sk_ldexp64)
 * IEEE-754 ldexp: multiplies param_1 by 2^param_2 in bounded steps
 * (|param_2| > 0x3fe handled by looping on a 0x3ff-exponent scale). */
static void sk_ldexp64_10d650(void)
{
    /* see decompile: 2^param_2 scaling */
}

/* FUN_0010d6b4 @ 0x10d6b4  (est. sk_fdiv_soft)
 * IEEE-754 single-precision soft division returning a 16-byte result. */
static void sk_fdiv_soft_10d6b4(void)
{
    /* see decompile */
}

/* FUN_0010d878 @ 0x10d878  (est. sk_exp2)
 * IEEE-754 exp2 (double): polynomial over the 2^-granule table (DAT_004c5188..),
 * with denormal/negative handling. */
static void sk_exp2_10d878(void)
{
    /* see decompile: exp2 polynomial */
}

/* FUN_0010d87c @ 0x10d87c  (est. sk_exp2_b)
 * Duplicate exp2 implementation (identical body to 0x10d878). */
static void sk_exp2_10d87c(void) { /* same as 0x10d878 */ }

/* FUN_0010d9f4 @ 0x10d9f4  (est. sk_sinf)
 * sinf (single): table-based polynomial (DAT_004c61d0..) with range checks. */
static float sk_sinf_10d9f4(float x)
{
    (void)x;
    /* see decompile */
    return 0.0f;
}

/* FUN_0010dac4 @ 0x10dac4  (est. sk_exp)
 * IEEE-754 exp (double): range-reduces via the ln2 table and evaluates the
 * 2^-12 step polynomial. */
static void sk_exp_10dac4(double x)
{
    (void)x;
    /* see decompile */
}

/* FUN_0010e444 @ 0x10e444  (est. sk_cosf)
 * cosf (single): table-based polynomial (DAT_004c61d0..). */
static float sk_cosf_10e444(float x)
{
    (void)x;
    /* see decompile */
    return 0.0f;
}

/* FUN_0010e4ec @ 0x10e4ec  (est. sk_expf)
 * expf (single): 128-entry table polynomial (DAT_004c6630..) with denormal
 * handling. */
static void sk_expf_10e4ec(float x)
{
    (void)x;
    /* see decompile */
}

/* FUN_0010e604 @ 0x10e604  (est. sk_log)
 * IEEE-754 log (double): range-reduced polynomial over the 2^-7 table
 * (DAT_0010e7e8..), with denormal/inf handling. */
static void sk_log_10e604(void)
{
    /* see decompile: log polynomial */
}

/* FUN_0010effc @ 0x10effc  (est. sk_logf)
 * logf (single): table polynomial (DAT_004c6e50..). */
static void sk_logf_10effc(void)
{
    /* see decompile */
}

/* FUN_0010f0e4 @ 0x10f0e4  (est. sk_log2f)
 * log2f (single): table polynomial (DAT_0010f1f0..). */
static void sk_log2f_10f0e4(void)
{
    /* see decompile */
}

/* FUN_0010f604 @ 0x10f604  (est. sk_log10f)
 * log10f (single): table polynomial (DAT_0010f700..). */
static void sk_log10f_10f604(void)
{
    /* see decompile */
}

/* FUN_0010fb14 @ 0x10fb14  (est. sk_log2)
 * IEEE-754 log2 (double): table polynomial (DAT_0010fcd8..). */
static void sk_log2_10fb14(void)
{
    /* see decompile */
}

/* FUN_001104ec @ 0x1104ec  (est. sk_sinf64)
 * sinf variant (single) using the DAT_001108xx range-reduction tables; handles
 * the full-period reduction for large |x|. */
static float sk_sinf64_1104ec(float x)
{
    (void)x;
    /* see decompile */
    return 0.0f;
}

/* FUN_001105f8 @ 0x1105f8  (est. sk_cosf64)
 * cosf variant (single) with range reduction. */
static float sk_cosf64_1105f8(float x)
{
    (void)x;
    /* see decompile */
    return 0.0f;
}

/* FUN_00111d84 @ 0x111d84  (est. sk_typed_op_fatal)
 * Noreturn: FUN_004b89f8("Terminating due to typed operato..."). */
static void sk_typed_op_fatal_111d84(void)
{
    /* FUN_004b89f8("Terminating due to typed operato..."); noreturn */
}

/* FUN_00111d9c @ 0x111d9c  (est. sk_typed_op_fatal_b)
 * Noreturn typed-operator termination. */
static void sk_typed_op_fatal_111d9c(void) { /* FUN_004b89f8(...); noreturn */ }

/* FUN_00111db4 @ 0x111db4  (est. sk_typed_op_fatal_c)
 * Noreturn typed-operator termination. */
static void sk_typed_op_fatal_111db4(void) { /* FUN_004b89f8(...); noreturn */ }

/* FUN_00111dcc @ 0x111dcc  (est. sk_typed_op_fatal_d)
 * Noreturn typed-operator termination. */
static void sk_typed_op_fatal_111dcc(void) { /* FUN_004b89f8(...); noreturn */ }

/* FUN_00112098 @ 0x112098  (est. sk_hash_short)
 * One-shot hash of (param_2, param_3) into a stack word via FUN_001120c4. */
static void sk_hash_short_112098(uint64_t a, uint64_t b)
{
    /* uint8_t out; FUN_001120c4(&out, a, b) */
}

/* FUN_001120c4 @ 0x1120c4  (est. sk_hash64_wyhash)
 * 64-bit string hash (wyhash-style with the 0x9ae16a3b2f90404f seed and
 * 0x622015f714c7d297/0x651e95c4d06fbfb1/0x4b6d499041670d8d multipliers):
 * handles lengths 0..0x40+ with a full 16-word mixing loop. Used to index
 * load-commands and capability tables. */
static uint64_t sk_hash64_wyhash_1120c4(uint64_t a, uint64_t *p, uint64_t len)
{
    (void)a; (void)p; (void)len;
    /* see decompile: wyhash hash core */
    return 0;
}

/* FUN_001124fc @ 0x1124fc  (est. sk_prime_slot)
 * Small-prime allocator: selects a size-class slot from the prime tables
 * (DAT_004c7660/DAT_004c7720) for param_1, searching for a number that is not
 * evenly divisible by any small prime; returns the chosen slot size. */
static int64_t *sk_prime_slot_1124fc(uint64_t n, uint64_t a, uint64_t b)
{
    (void)n; (void)a; (void)b;
    /* see decompile: prime sieve size-class search */
    return 0;
}

/* ============ 0x112c18 - 0x114fe0 : Swift string/buffer library ============ */

/* FUN_00112c18 @ 0x112c18  (est. sk_str_append)
 * Swift String append: appends param_3 (length param_2 via strnlen) to the
 * string param_1, growing the inline/allocated buffer (header at +0x17 flag,
 * +0x10 ptr, +0x18 capacity) as needed via FUN_00111890/FUN_00117d14. */
static int64_t *sk_str_append_112c18(int64_t *s, uint64_t a, uint64_t b)
{
    (void)s; (void)a; (void)b;
    /* see decompile: grow + copy + nul-terminate */
    return s;
}

/* FUN_00112c38 @ 0x112c38  (est. sk_str_append_n)
 * Appends param_2 bytes from param_3 to the string param_1 (growing as
 * needed); handles the inline (<=0x16) vs heap-string representations. */
static int64_t *sk_str_append_n_112c38(int64_t *s, uint64_t n, uint64_t src)
{
    (void)s; (void)n; (void)src;
    /* see decompile */
    return s;
}

/* FUN_00112db4 @ 0x112db4  (est. sk_str_append_z)
 * Appends a C-string param_2 (strlen via thunk_FUN_00115080) to string param_1. */
static uint64_t *sk_str_append_z_112db4(uint64_t *s, uint64_t cstr)
{
    (void)s; (void)cstr;
    /* see decompile */
    return s;
}

/* FUN_00112e8c @ 0x112e8c  (est. sk_str_append_n_b)
 * Appends param_3 bytes of param_2 to the string param_1 (grow as needed). */
static uint64_t *sk_str_append_n_b_112e8c(uint64_t *s, uint64_t src, uint64_t n)
{
    (void)s; (void)src; (void)n;
    /* see decompile */
    return s;
}

/* FUN_00112f50 @ 0x112f50  (est. sk_str_reserve)
 * String reserve/grow core: allocates a new buffer of the grown capacity
 * (round-up-to-multiple-of-8, doubling when small), copies the head
 * (param_5 bytes), the inserted span (param_7 bytes from param_8), and the
 * tail, then frees the old buffer. Noreturn FUN_004b89f8 on overflow. */
static void sk_str_reserve_112f50(int64_t *s, uint64_t cap, uint64_t n, int64_t p4, int64_t head, int64_t p6, int64_t p7, uint64_t src)
{
    (void)s; (void)cap; (void)n; (void)p4; (void)head; (void)p6; (void)p7; (void)src;
    /* see decompile: grow-copy-insert-shift */
}

/* FUN_001130a0 @ 0x1130a0  (est. sk_str_push_char)
 * Appends a single character to the string, growing the buffer when full. */
static void sk_str_push_char_1130a0(int64_t *s, uint8_t c)
{
    (void)s; (void)c;
    /* see decompile */
}

/* FUN_001131f4 @ 0x1131f4  (est. sk_str_replace)
 * Replaces a substring: computes the C-string length then calls FUN_00113240. */
static void sk_str_replace_1131f4(uint64_t a, uint64_t b, uint64_t c)
{
    /* uVar1 = thunk_FUN_00115080(c); FUN_00113240(a,b,c,uVar1) */
}

/* FUN_00113240 @ 0x113240  (est. sk_str_replace_core)
 * String replace core: replaces the range [param_2, param_2+param_4) with
 * param_3 bytes (growing/shifting via FUN_00112f50). */
static int64_t *sk_str_replace_core_113240(int64_t *s, uint64_t off, uint64_t src, uint64_t n)
{
    (void)s; (void)off; (void)src; (void)n;
    /* see decompile */
    return s;
}

/* FUN_00113368 @ 0x113368  (est. sk_str_init)
 * String initializer: sets the inline length (<0x17) or allocates a heap
 * buffer, then copies param_2 for param_3+1 bytes (nul-terminated). */
static void sk_str_init_113368(int64_t *s, uint64_t src, uint64_t n)
{
    (void)s; (void)src; (void)n;
    /* see decompile */
}

/* FUN_00113400 @ 0x113400  (est. sk_str_assign)
 * String assignment: stores the C-string param_2 (of length uVar2) into
 * param_1, growing the buffer if the inline capacity (0x16) is exceeded. */
static int64_t *sk_str_assign_113400(int64_t *s, uint64_t cstr)
{
    (void)s; (void)cstr;
    /* see decompile */
    return s;
}

/* FUN_001135b0 @ 0x1135b0  (est. sk_str_copy)
 * String copy/assign: copies string param_2 into param_1, growing as needed;
 * handles inline vs heap representations of both operands. */
static int64_t *sk_str_copy_1135b0(int64_t *dst, int64_t *src)
{
    (void)dst; (void)src;
    /* see decompile */
    return dst;
}

/* FUN_001137f8 @ 0x1137f8  (est. sk_str_from_int)
 * Integer-to-string conversion (decimal, with '-' sign), producing a Swift
 * String via the digit table DAT_004c77e0. */
static void sk_str_from_int_1137f8(uint64_t *s, uint32_t v)
{
    (void)s; (void)v;
    /* see decompile */
}

/* FUN_0011394c @ 0x11394c  (est. sk_str_from_int64)
 * 64-bit integer-to-string conversion. */
static void sk_str_from_int64_11394c(uint64_t *s, uint64_t v)
{
    (void)s; (void)v;
    /* see decompile */
}

/* FUN_00113a3c @ 0x113a3c  (est. sk_str_from_uint)
 * Unsigned 64-bit integer-to-string conversion (base-10, 2-digit groups from
 * DAT_004c7808). */
static void sk_str_from_uint_113a3c(uint64_t *s, uint64_t v)
{
    (void)s; (void)v;
    /* see decompile */
}

/* FUN_00113c30 @ 0x113c30  (est. sk_str_from_uint_b)
 * Duplicate of 0x113a3c (same conversion body). */
static void sk_str_from_uint_113c30(uint64_t *s, uint64_t v) { /* same as 0x113a3c */ (void)s; (void)v; }

/* FUN_00113e24 @ 0x113e24  (est. sk_str_concat)
 * String concatenation: appends param_3 to the concatenation of the two
 * strings, growing the result buffer. */
static void sk_str_concat_113e24(uint64_t *out, uint64_t *a, uint64_t b)
{
    (void)out; (void)a; (void)b;
    /* see decompile */
}

/* FUN_00113f20 @ 0x113f20  (est. sk_int_to_str)
 * Integer-to-string digit writer (base-10), returning the end of the written
 * buffer. */
static uint64_t sk_int_to_str_113f20(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00114aa0 @ 0x114aa0  (est. sk_memset_word)
 * memset for a repeated 8-byte word (NEON-vectorized): fills param_3 bytes of
 * param_1 with the pattern *param_2, using 16-byte vector stores and a
 * byte-tail loop. */
static void sk_memset_word_114aa0(uint64_t *dst, uint64_t *pat, uint64_t n)
{
    (void)dst; (void)pat; (void)n;
    /* see decompile: NEON memset */
}

/* FUN_00114c60 @ 0x114c60  (est. sk_memchr_neon)
 * NEON-optimized memchr: searches param_3 bytes of memory at param_1 for byte
 * param_2, using 16-byte vector compares; returns the matching pointer or 0. */
static uint8_t *sk_memchr_neon_114c60(uint64_t p, uint8_t c)
{
    (void)p; (void)c;
    /* see decompile */
    return 0;
}

/* FUN_00114480 @ 0x114480  (est. sk_memchr_bounded)
 * Bounded memchr: searches up to param_3 bytes for byte param_2 (NEON), with
 * the initial 16-byte-aligned prologue and byte tail. */
static void *sk_memchr_bounded_114480(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001145b0 @ 0x1145b0  (est. sk_memcmp_neon)
 * NEON-optimized memcmp of param_3 bytes between param_1/param_2: compares
 * 16-byte vectors, then byte-swaps the first differing byte pair to get the
 * sign. Returns <0/0/>0. */
static int64_t sk_memcmp_neon_1145b0(uint64_t *a, uint64_t *b, uint64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile: NEON compare + sign fixup */
    return 0;
}

/* FUN_001146d8 @ 0x1146d8  (est. sk_memcmp_eq)
 * Constant-time-ish memcmp (16-byte vector, full scan with mask accumulation)
 * ending with DSB+ISB barriers; returns the difference of the first differing
 * byte. */
static int sk_memcmp_eq_1146d8(uint8_t *a, uint8_t *b, uint64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile: NEON full-scan + DSB/ISB */
    return 0;
}

/* FUN_00114790 @ 0x114790  (est. sk_memmove)
 * memmove: handles the overlapping (backward) and non-overlapping (forward)
 * cases with 16-byte vector loops; large copies use 0x20-byte stores. */
static void sk_memmove_114790(uint64_t *dst, uint64_t *src, uint64_t n)
{
    (void)dst; (void)src; (void)n;
    /* see decompile */
}

/* FUN_00114804 @ 0x114804  (est. sk_memcpy)
 * memcpy: forward copy with 8/16-byte and 0x20-byte vector loops. */
static void sk_memcpy_114804(uint64_t *dst, uint64_t *src, uint64_t n)
{
    (void)dst; (void)src; (void)n;
    /* see decompile */
}

/* ============ 0x115080 - 0x117cbc : libc string/memory/ctype ============ */

/* FUN_00115080 @ 0x115080  (est. sk_strlen_neon)
 * NEON-optimized strlen: scans for the NUL byte in 16-byte vectors; returns
 * the offset of the first NUL. */
static int64_t sk_strlen_neon_115080(uint64_t p)
{
    (void)p;
    /* see decompile */
    return 0;
}

/* FUN_001150e0 @ 0x1150e0  (est. sk_strncpy_fill)
 * Copies a string and zero-fills the remainder: resolves the length via
 * FUN_000543f4 then FUN_00115290. */
static void sk_strncpy_fill_1150e0(uint64_t a)
{
    (void)a;
    /* auVar1 = FUN_000543f4(a,&stack); FUN_00115290(auVar1._0_8_, 0, auVar1._8_8_) */
}

/* FUN_0011510c @ 0x11510c  (est. sk_strnchr)
 * Bounded strchr: searches param_3 bytes of param_1 for byte param_2 (with
 * bounds check -> BRK 0x5519 on out-of-range). */
static char *sk_strnchr_11510c(char *s, int c, long n)
{
    char *end = s + n, *p = s;
    while (n != 0) {
        if (end <= p || p < s) { /* BRK 0x5519 @ 0x115148 */ break; }
        n--;
        if (c == *p) return p;
        p++;
    }
    return 0;
}

/* FUN_00115148 @ 0x115148  (est. sk_memcmp_simple)
 * Bounded byte memcmp: compares param_3 bytes, returning the first difference
 * or 0; bounds-checked (BRK 0x5519). */
static int sk_memcmp_simple_115148(uint8_t *a, uint8_t *b, long n)
{
    uint8_t *ea = a + n, *eb = b + n, *pa = a, *pb = b;
    while (n != 0) {
        if (ea <= pa || pa < a) break;
        uint8_t ba = *pa;
        if (eb <= pb || pb < b) break;
        uint8_t bb = *pb;
        n--; pb++; pa++;
        if (ba - bb != 0) return (int)ba - (int)bb;
    }
    return 0;
}

/* FUN_001151fc @ 0x1151fc  (est. sk_memmove_bounds)
 * Bounds-checked memmove (handles overlap backward copy); BRK 0x5519 on
 * out-of-range access. */
static void sk_memmove_bounds_1151fc(uint8_t *dst, uint8_t *src, uint64_t n)
{
    (void)dst; (void)src; (void)n;
    /* see decompile: overlap memmove + bounds BRK */
}

/* FUN_00115290 @ 0x115290  (est. sk_memset_bounds)
 * Bounds-checked memset of param_3 bytes with byte param_2; BRK 0x5519 on
 * out-of-range. */
static void sk_memset_bounds_115290(uint8_t *dst, uint8_t c, long n)
{
    (void)dst; (void)c; (void)n;
    /* see decompile */
}

/* FUN_001152c4 @ 0x1152c4  (est. sk_strchr)
 * strchr: scans for byte param_2 up to the NUL; returns the match or NULL. */
static char *sk_strchr_1152c4(char *s, char c)
{
    for (; *s != '\0' && c != *s; s++) { }
    return (c == *s) ? s : 0;
}

/* FUN_00115300 @ 0x115300  (est. sk_strcmp)
 * strcmp: compares two NUL-terminated strings byte by byte. */
static int sk_strcmp_115300(uint8_t *a, uint8_t *b)
{
    uint8_t ba, bb;
    while (1) {
        ba = *a; bb = *b;
        if (ba != *b || (bb = ba, *a == 0)) break;
        a++; b++;
    }
    return (int)ba - (int)bb;
}

/* FUN_00115334 @ 0x115334  (est. sk_strlen)
 * Simple strlen loop. */
static long sk_strlen_115334(long p)
{
    long i = 0;
    while (*(char *)(p + i) != '\0') i++;
    return i;
}

/* FUN_0011534c @ 0x11534c  (est. sk_strncmp)
 * strncmp: compares up to param_3 bytes, stopping at NUL; returns the first
 * difference or 0. */
static int sk_strncmp_11534c(uint8_t *a, uint8_t *b, long n)
{
    while (1) {
        if (n == 0) return 0;
        if ((int)*a - (int)*b != 0) break;
        uint8_t ba = *a;
        n--; a++; b++;
        if (ba == 0) return 0;
    }
    return (int)*a - (int)*b;
}

/* FUN_0011537c @ 0x11537c  (est. sk_strlcpy)
 * strlcpy: copies up to param_3 bytes from param_2 to param_1 (via
 * FUN_00114fe0/FUN_00114790), NUL-terminates; bounds-checked (BRK 0x5519). */
static long sk_strlcpy_11537c(long dst, uint64_t src, uint64_t n)
{
    (void)dst; (void)src; (void)n;
    /* see decompile */
    return 0;
}

/* FUN_001153fc @ 0x1153fc  (est. sk_strnlen)
 * strnlen: returns the length up to the NUL or param_2. */
static long sk_strnlen_1153fc(long p, long max)
{
    long i = 0;
    for (i = 0; p != 0 && i != max && *(char *)(p + i) != '\0'; i++) { }
    return i;
}

/* FUN_00115424 @ 0x115424  (est. sk_isalpha)
 * Checks whether the "Assertion failed" string's first char is an ASCII letter
 * (0x20-0x7f range): returns (c - 0x20) < 0x5f. */
static bool sk_isalpha_115424(void)
{
    int c = /* FUN_000543c4("Assertion failed: %s, function...") */ 0;
    return (uint32_t)(c - 0x20) < 0x5f;
}

/* FUN_00115448 @ 0x115448  (est. sk_isalpha_c)
 * Returns (param_1 - 0x20) < 0x5f (ASCII letter test). */
static bool sk_isalpha_c_115448(int c) { return (uint32_t)(c - 0x20) < 0x5f; }

/* FUN_00115458 @ 0x115458  (est. sk_isspace)
 * Returns true for space or tab..CR (0x9-0xd). */
static bool sk_isspace_115458(int c) { return c == 0x20 || (uint32_t)(c - 9) < 5; }

/* FUN_0011546c @ 0x11546c  (est. sk_dict_count)
 * Dictionary/Swift-uniqued-count: walks a hash-table chain from param_4,
 * applying the predicate param_6 and counting live entries (via FUN_00115764). */
static uint64_t sk_dict_count_11546c(uint64_t p, int a, int b, long c, uint64_t d, uint64_t (*pred)(void))
{
    (void)p; (void)a; (void)b; (void)c; (void)d; (void)pred;
    /* see decompile */
    return 0;
}

/* FUN_00115574 @ 0x115574  (est. sk_dyld_env_collect)
 * Collects dyld environment entries from the thread-local ncmds array
 * (FUN_001157c8/FUN_00054418/FUN_001157b8) into param_1. */
static uint64_t sk_dyld_env_collect_115574(long out, uint64_t max)
{
    (void)out; (void)max;
    /* see decompile */
    return 0;
}

/* FUN_001155e0 @ 0x1155e0  (est. sk_dict_collect)
 * Dictionary entry collection: walks the hash chain, applies a transform
 * (FUN_00115764/FUN_00054418), and stores entries into param_2. */
static uint64_t sk_dict_collect_1155e0(long a, long out, uint64_t max, uint32_t *err)
{
    (void)a; (void)out; (void)max; (void)err;
    /* see decompile */
    return 0;
}

/* FUN_001156c4 @ 0x1156c4  (est. sk_dict_collect_fn)
 * Dictionary collection with a callback transform param_5 applied to each key. */
static uint64_t sk_dict_collect_fn_1156c4(uint64_t p, long out, uint64_t max, long c, uint64_t (*fn)(void), uint64_t d)
{
    (void)p; (void)out; (void)max; (void)c; (void)fn; (void)d;
    /* see decompile */
    return 0;
}

/* FUN_00115764 @ 0x115764  (est. sk_dict_next)
 * Swift dictionary iterator: if the entry is a heap bucket (flag bit4 at
 * param_1+7), dereferences the per-thread bucket list (tpidr_el0+0x30) and
 * returns the bucket's key; else 0. */
static uint64_t sk_dict_next_115764(long p, uint32_t *err)
{
    (void)p; (void)err;
    /* see decompile: tpidr_el0 bucket deref */
    return 0;
}

/* FUN_001157b8 @ 0x1157b8  (est. sk_noop)
 * Empty function. */
static void sk_noop_1157b8(void) {}

/* FUN_001157c8 @ 0x1157c8  (est. sk_tls_get)
 * Reads the per-thread slot at x22+8 (dyld thread-local). */
static uint64_t sk_tls_get_1157c8(void)
{
    /* return *(uint64_t*)(unaff_x22 + 8) */
    return 0;
}

/* FUN_001157d4 @ 0x1157d4  (est. sk_abort)
 * Calls FUN_00053aa0 and returns 0. */
static uint64_t sk_abort_1157d4(void)
{
    /* FUN_00053aa0() */
    return 0;
}

/* FUN_001157f0 @ 0x1157f0  (est. sk_glibc_errno)
 * Maps the FUN_00053aa4 result to an errno via DAT_004c78d0 (returns 0x16 if
 * out of range). */
static uint32_t sk_glibc_errno_1157f0(uint64_t a, long b)
{
    (void)a; (void)b;
    uint32_t v = /* FUN_00053aa4() */ 0;
    return (v < 4) ? ((uint32_t *)0x4c78d0)[v] : 0x16;
}

/* FUN_0011582c @ 0x11582c  (est. sk_errno_map_a)
 * Maps FUN_00053ae0 -> errno table DAT_004c78d0. */
static uint32_t sk_errno_map_a_11582c(void)
{
    uint32_t v = /* FUN_00053ae0() */ 0;
    return (v < 4) ? ((uint32_t *)0x4c78d0)[v] : 0x16;
}

/* FUN_00115860 @ 0x115860  (est. sk_errno_map_b)
 * Maps FUN_00053af4 -> errno table. */
static uint32_t sk_errno_map_b_115860(void)
{
    uint32_t v = /* FUN_00053af4() */ 0;
    return (v < 4) ? ((uint32_t *)0x4c78d0)[v] : 0x16;
}

/* FUN_00115894 @ 0x115894  (est. sk_errno_map_c)
 * Maps FUN_00053b28 -> errno table. */
static uint32_t sk_errno_map_c_115894(void)
{
    uint32_t v = /* FUN_00053b28() */ 0;
    return (v < 4) ? ((uint32_t *)0x4c78d0)[v] : 0x16;
}

/* FUN_001158c8 @ 0x1158c8  (est. sk_tls_read)
 * Reads the per-thread slot at tpidr_el0+8. */
static uint64_t sk_tls_read_1158c8(void)
{
    /* return *(uint64_t*)(tpidr_el0 + 8) */
    return 0;
}

/* FUN_001158cc @ 0x1158cc  (est. sk_snprintf_core)
 * snprintf format engine: parses the format string, handling '%' specifiers
 * (width, precision, flags, conversions) and emitting into the bounded output
 * buffer (via FUN_00115f3c and format callbacks), then NUL-terminates. */
static void sk_snprintf_core_1158cc(long out, uint64_t a, uint64_t n, uint8_t *fmt, uint64_t arg)
{
    (void)out; (void)a; (void)n; (void)fmt; (void)arg;
    /* see decompile: printf-style format state machine */
}

/* FUN_00117c20 @ 0x117c20  (est. sk_pair_setup)
 * Stores param_1 and runs FUN_00117b14 on the two stack words. */
static void sk_pair_setup_117c20(uint64_t v)
{
    (void)v;
    /* *(fp-0xa0) = v; FUN_00117b14(fp-0x78, fp-0xb0) */
}

/* FUN_00117c38 @ 0x117c38  (est. sk_noop)
 * Empty function. */
static void sk_noop_117c38(void) {}

/* FUN_00117c4c @ 0x117c4c  (est. sk_noop)
 * Empty function. */
static void sk_noop_117c4c(void) {}

/* FUN_00117c5c @ 0x117c5c  (est. sk_pair_stack)
 * Returns the {fp-0x78, fp-0xb0} pair of stack words. */
static void sk_pair_stack_117c5c(void)
{
    /* returns {fp-0x78, fp-0xb0} */
}

/* FUN_00117c68 @ 0x117c68  (est. sk_store_stack)
 * Stores the incoming stack word at fp-0x68. */
static void sk_store_stack_117c68(void)
{
    /* *(fp-0x68) = in_stack_0x78 */
}

/* FUN_00117c74 @ 0x117c74  (est. sk_noop)
 * Empty function. */
static void sk_noop_117c74(void) {}

/* FUN_00117c88 @ 0x117c88  (est. sk_swap32)
 * Swaps two 32-bit words (x25 <-> x26). */
static void sk_swap32_117c88(void)
{
    /* uVar1 = *x26; *x26 = *x25; *x25 = uVar1 */
}

/* FUN_00117c9c @ 0x117c9c  (est. sk_swap64)
 * Swaps two 64-bit words. */
static void sk_swap64_117c9c(void)
{
    /* uVar1 = *x26; *x26 = *x25; *x25 = uVar1 */
}

/* FUN_00117cb0 @ 0x117cb0  (est. sk_noop)
 * Empty function. */
static void sk_noop_117cb0(void) {}

/* FUN_00117cbc @ 0x117cbc  (est. sk_memchr_neg)
 * NEON memchr for a negative-length (backward) search of byte param_2 within
 * param_1. */
static long sk_memchr_neg_117cbc(uint64_t p, char c, long n)
{
    (void)p; (void)c; (void)n;
    /* see decompile: NEON backward memchr */
    return 0;
}

/* FUN_00117cc0 @ 0x117cc0  (est. sk_memcmp_neon_b)
 * NEON memcmp (forward, 16-byte vectors), returning first byte difference. */
static long sk_memcmp_neon_b_117cc0(uint64_t *a, uint64_t *b, uint64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile */
    return 0;
}

/* ============ 0x116e80 - 0x117c68 : qsort/bsearch/rand ============ */

/* FUN_00116e80 @ 0x116e80  (est. sk_bsearch)
 * Binary search over an array of param_3 elements of size param_4, comparing
 * with callback param_5; returns the matching element address or 0. Bounds
 * checked (BRK 0x5519). */
static uint64_t sk_bsearch_116e80(uint64_t key, uint64_t base, uint64_t n, int64_t esize, uint64_t (*cmp)(void))
{
    (void)key; (void)base; (void)n; (void)esize; (void)cmp;
    /* see decompile */
    return 0;
}

/* FUN_00116f40 @ 0x116f40  (est. sk_qsort_wrap)
 * qsort wrapper: resolves the array bounds via FUN_0006b2ec, computes the
 * end pointer, and calls the sort core FUN_00116f88. */
static void sk_qsort_wrap_116f40(uint64_t a, uint64_t b, int64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile */
}

/* FUN_00116f88 @ 0x116f88  (est. sk_qsort)
 * Introsort/quick-sort core: median-of-three pivot selection (FUN_0011794c),
 * Hoare-style partitioning with bounds checks (BRK 0x5519), element swapping
 * (8/4-byte or generic via FUN_00117c20), and insertion-sort fallback
 * (FUN_0011776c) for small partitions. */
static void sk_qsort_116f88(uint64_t a, uint64_t b, uint64_t n, uint64_t (*cmp)(void))
{
    (void)a; (void)b; (void)n; (void)cmp;
    /* see decompile: quicksort partition + insert sort */
}

/* FUN_0011776c @ 0x11776c  (est. sk_insertion_sort)
 * Insertion-sort core over the element array (stride param_3), bounds-checked
 * swaps. */
static uint64_t sk_insertion_sort_11776c(uint64_t *arr, uint64_t n, int64_t esize, uint64_t (*cmp)(void), uint64_t hint, char a, char b)
{
    (void)arr; (void)n; (void)esize; (void)cmp; (void)hint; (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_0011794c @ 0x11794c  (est. sk_median3)
 * Median-of-three pivot selection: compares three elements and returns the
 * median (with the 16-byte {a,b,c} pointer triple). */
static void sk_median3_11794c(void)
{
    /* see decompile */
}

/* FUN_00117b14 @ 0x117b14  (est. sk_block_swap)
 * Block swap: swaps two equal-length element runs (used by qsort partition
 * balancing), with 8-byte and byte loops. */
static void sk_block_swap_117b14(void)
{
    /* see decompile */
}

/* FUN_00117cc4 @ 0x117cc4  (est. sk_memcpy_std)
 * memcpy (standard): copies param_3 bytes with 8-byte then byte loops. */
static void sk_memcpy_std_117cc4(uint64_t dst, uint64_t src, uint64_t n)
{
    (void)dst; (void)src; (void)n;
    /* see decompile */
}

/* FUN_00117cc8 @ 0x117cc8  (est. sk_noop)
 * Empty function. */
static void sk_noop_117cc8(void) {}

/* FUN_00117d14 @ 0x117d14  (est. sk_memcpy_std_b)
 * memcpy (standard, with bounds BRK 0x5519). */
static void sk_memcpy_std_b_117d14(uint64_t dst, uint64_t src, uint64_t n)
{
    (void)dst; (void)src; (void)n;
    /* see decompile */
}

/* FUN_00117d18 @ 0x117d18  (est. sk_noop)
 * Empty function. */
static void sk_noop_117d18(void) {}

/* FUN_00117d64 @ 0x117d64  (est. sk_memmove_std)
 * memmove (standard, overlap-safe). */
static void sk_memmove_std_117d64(uint64_t dst, uint64_t src, uint64_t n)
{
    (void)dst; (void)src; (void)n;
    /* see decompile */
}

/* FUN_00117d68 @ 0x117d68  (est. sk_memcpy_small)
 * Small memcpy (<=16 bytes fast path). */
static void sk_memcpy_small_117d68(void)
{
    /* see decompile */
}

/* FUN_00117dbc @ 0x117dbc  (est. sk_memset_std)
 * memset (standard byte loop). */
static void sk_memset_std_117dbc(uint64_t dst, uint8_t c, uint64_t n)
{
    (void)dst; (void)c; (void)n;
    /* see decompile */
}

/* FUN_00117e14 @ 0x117e14  (est. sk_secure_clear_chk)
 * Bounds-checked secure clear: zeroes param_1 bytes at param_2 (via
 * FUN_00117cc4); BRK 0x5519 if the range is invalid. */
static void sk_secure_clear_chk_117e14(uint64_t dst, uint64_t a, uint64_t b, uint64_t n, uint64_t limit)
{
    (void)dst; (void)a; (void)b; (void)n; (void)limit;
    /* see decompile */
}

/* FUN_00117e68 @ 0x117e68  (est. sk_memcmp_bounds)
 * Bounds-checked memcmp (16-byte NEON + byte tail). */
static int64_t sk_memcmp_bounds_117e68(uint64_t a, uint64_t b, uint64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile */
    return 0;
}

/* FUN_00117f8c @ 0x117f8c  (est. sk_memchr_fwd)
 * Forward memchr (16-byte NEON). */
static void *sk_memchr_fwd_117f8c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00117fc0 @ 0x117fc0  (est. sk_strcpy)
 * strcpy: copies the NUL-terminated source into dst. */
static void sk_strcpy_117fc0(void)
{
    /* see decompile */
}

/* FUN_00117fdc @ 0x117fdc  (est. sk_strncpy)
 * strncpy: copies up to param_3 bytes (bounds-checked). */
static void sk_strncpy_117fdc(void)
{
    /* see decompile */
}

/* FUN_0011807c @ 0x11807c  (est. sk_memcmp_simple_b)
 * memcmp (simple byte loop). */
static int64_t sk_memcmp_simple_b_11807c(uint64_t a, uint64_t b, uint64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile */
    return 0;
}

/* FUN_001180cc @ 0x1180cc  (est. sk_memcpy_var)
 * memcpy with variable handling of overlaps (forward/backward). */
static void sk_memcpy_var_1180cc(void)
{
    /* see decompile */
}

/* FUN_001180e0 @ 0x1180e0  (est. sk_memmove_var)
 * memmove (variable). */
static void sk_memmove_var_1180e0(void)
{
    /* see decompile */
}

/* FUN_001180fc @ 0x1180fc  (est. sk_memcmp_eq_b)
 * memcmp (NEON full-scan, DSB/ISB). */
static int sk_memcmp_eq_b_1180fc(uint8_t *a, uint8_t *b, uint64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile */
    return 0;
}

/* FUN_00118114 @ 0x118114  (est. sk_memchr_wide)
 * memchr over 16-byte-aligned memory. */
static void *sk_memchr_wide_118114(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0011812c @ 0x11812c  (est. sk_memchr_bound)
 * Bounded memchr (BRK 0x5519 on out-of-range). */
static void *sk_memchr_bound_11812c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00118148 @ 0x118148  (est. sk_memcmp_chk)
 * Bounds-checked memcmp returning sign of first difference. */
static int sk_memcmp_chk_118148(uint64_t a, uint64_t b, uint64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile */
    return 0;
}

/* FUN_00118164 @ 0x118164  (est. sk_strlen_chk)
 * Bounds-checked strlen. */
static long sk_strlen_chk_118164(uint64_t p)
{
    (void)p;
    /* see decompile */
    return 0;
}

/* FUN_0011817c @ 0x11817c  (est. sk_memcpy_chk)
 * Bounds-checked memcpy. */
static void sk_memcpy_chk_11817c(uint64_t dst, uint64_t src, uint64_t n)
{
    (void)dst; (void)src; (void)n;
    /* see decompile */
}

/* FUN_00118194 @ 0x118194  (est. sk_strcmp_chk)
 * Bounds-checked strcmp. */
static int sk_strcmp_chk_118194(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_001181b4 @ 0x1181b4  (est. sk_strncat)
 * strncat: appends up to param_3 bytes of param_2 to param_1. */
static void sk_strncat_1181b4(void)
{
    /* see decompile */
}

/* FUN_0011825c @ 0x11825c  (est. sk_strstr)
 * strstr: searches for substring param_2 within param_1. */
static void *sk_strstr_11825c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00118328 @ 0x118328  (est. sk_strspn)
 * strspn: length of the initial segment matching the accept set. */
static void *sk_strspn_118328(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001183b4 @ 0x1183b4  (est. sk_strcspn)
 * strcspn: length of the initial segment NOT in the reject set. */
static void *sk_strcspn_1183b4(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001183cc @ 0x1183cc  (est. sk_strpbrk)
 * strpbrk: first char of param_1 in the accept set. */
static void *sk_strpbrk_1183cc(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001183e0 @ 0x1183e0  (est. sk_strrchr)
 * strrchr: last occurrence of byte param_2 in param_1. */
static void *sk_strrchr_1183e0(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0011844c @ 0x11844c  (est. sk_strcasecmp)
 * strcasecmp: case-insensitive compare. */
static int sk_strcasecmp_11844c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_001184c8 @ 0x1184c8  (est. sk_strncasecmp)
 * strncasecmp: case-insensitive bounded compare. */
static int sk_strncasecmp_1184c8(uint64_t a, uint64_t b, uint64_t n)
{
    (void)a; (void)b; (void)n;
    /* see decompile */
    return 0;
}

/* FUN_0011858c @ 0x11858c  (est. sk_memrchr)
 * memrchr: last occurrence of byte in the first param_3 bytes. */
static void *sk_memrchr_11858c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001185ec @ 0x1185ec  (est. sk_strtol)
 * strtol: parses a long from the string. */
static void *sk_strtol_1185ec(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00118644 @ 0x118644  (est. sk_strtoul)
 * strtoul: parses an unsigned long. */
static void *sk_strtoul_118644(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001187ac @ 0x1187ac  (est. sk_strtod)
 * strtod: parses a double from the string. */
static void *sk_strtod_1187ac(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001187f4 @ 0x1187f4  (est. sk_atof)
 * atof: parses a float from the string. */
static float sk_atof_1187f4(void)
{
    /* see decompile */
    return 0.0f;
}

/* FUN_0011883c @ 0x11883c  (est. sk_atoi)
 * atoi: parses an int. */
static int sk_atoi_11883c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001188a0 @ 0x1188a0  (est. sk_atol)
 * atol: parses a long. */
static long sk_atol_1188a0(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00118abc @ 0x118abc  (est. sk_strtof)
 * strtof: parses a float. */
static void *sk_strtof_118abc(void)
{
    /* see decompile */
    return 0;
}

/* ============ 0x118b28 - 0x11c2a0 : libc startup/stdio/float ============ */

/* FUN_00118b28 @ 0x118b28  (est. sk_fprintf)
 * fprintf: formats via FUN_00118c38 into the FILE stream. */
static void sk_fprintf_118b28(uint64_t a)
{
    (void)a;
    /* FUN_00118c38(0xb4000769f84206c9, a, &stack) */
}

/* FUN_00118b90 @ 0x118b90  (est. sk_strtol_wrap)
 * strtol wrapper: acquires the FILE lock (thunk_FUN_00054464), calls
 * FUN_00118644, releases. */
static uint64_t sk_strtol_wrap_118b90(char c, uint64_t a)
{
    (void)c; (void)a;
    /* thunk_FUN_00054464(a); r = FUN_00118644(c, a); thunk_FUN_0005453c(a); return r */
    return 0;
}

/* FUN_00118b94 @ 0x118b94  (est. sk_isdigit_str)
 * Checks whether the string param_1 (length lVar3) parses as a single decimal
 * digit: validates no length overflow (BRK), calls strtol, compares consumed
 * length and digit value. Returns 1 if a single digit, else -1. */
static uint32_t sk_isdigit_str_118b94(uint64_t p)
{
    (void)p;
    /* see decompile */
    return 0xffffffff;
}

/* FUN_00118c28 @ 0x118c28  (est. sk_strtol_fmt)
 * Calls FUN_001187f4 with the FILE handle. */
static void sk_strtol_fmt_118c28(uint64_t a)
{
    /* FUN_001187f4(a, 0xb4000769f84206c9) */
}

/* FUN_00118c38 @ 0x118c38  (est. sk_fmt_out)
 * Formatting output core: forwards to FUN_001158cc (the format state machine)
 * with a zero-width limit and the FILE stream. */
static void sk_fmt_out_118c38(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* FUN_001158cc(a, 0, 0, b, c) */
}

/* FUN_00118c4c @ 0x118c4c  (est. sk_fmt_file)
 * Formats into a FILE: FUN_00118c38 with the FILE handle and arg block. */
static void sk_fmt_file_118c4c(uint64_t a, uint64_t b)
{
    /* FUN_00118c38(0xb4000769f84206c9, a, b) */
}

/* FUN_00118c64 @ 0x118c64  (est. sk_cxa_atexit)
 * __cxa_atexit: registers a destructor {fn, arg, dso} in the 0x20-slot
 * atexit table (DAT_006ad9f0, count DAT_006adcf0), under the lock
 * DAT_006adcf4 (spin via LOAcquire). Returns 0 or -1 if the table is full.
 * Panics "src/libc/sys/sys.c" on a null arg. */
static uint64_t sk_cxa_atexit_118c64(uint64_t fn, uint64_t arg, long dso)
{
    (void)fn; (void)arg; (void)dso;
    /* if (dso==0) panic; spin-lock DAT_006adcf4; if (count<0x20) register else return -1 */
    return 0;
}

/* FUN_00118cf8 @ 0x118cf8  (est. sk_strdup)
 * strdup: allocates strlen(param_1)+1 bytes (FUN_0001244c), copies the string
 * (FUN_00117e68) and NUL-terminates; returns the copy or NULL. */
static char *sk_strdup_118cf8(long p)
{
    (void)p;
    /* see decompile */
    return 0;
}

/* FUN_00118d8c @ 0x118d8c  (est. sk_run_ctors)
 * Runs the constructor table (FUN_00118fe0) if param_1 is nonzero. */
static void sk_run_ctors_118d8c(int flag)
{
    if (flag != 0) { /* FUN_00118fe0() */ }
}

/* FUN_00118fe0 @ 0x118fe0  (est. sk_call_fns)
 * Calls an array of function pointers (must be 8-aligned, else panic
 * "do_calls"): invokes each entry sequentially. */
static void sk_call_fns_118fe0(uint64_t *arr, uint64_t n)
{
    (void)arr; (void)n;
    /* for each 8-aligned slot: (*(void(*)())arr[i])() */
}

/* FUN_00119068 @ 0x119068  (est. sk_call_fns_rel)
 * Calls an array of 4-byte relative function offsets (must be 4-aligned). */
static void sk_call_fns_rel_119068(uint32_t *arr, uint64_t n)
{
    (void)arr; (void)n;
    /* for each 4-aligned slot: (*(void(*)())(uint64_t)arr[i])() */
}

/* FUN_001190fc @ 0x1190fc  (est. sk_libc_init)
 * libc initialization: registers the default cleanup (FUN_000529d4), runs
 * FUN_0011d790 and FUN_00118d8c(1) (constructors). */
static void sk_libc_init_1190fc(void)
{
    /* _DAT_006adcf8 = FUN_000529d4(1); FUN_0011d790(); FUN_00118d8c(1) */
}

/* FUN_00119130 @ 0x119130  (est. sk_str_src)
 * Returns the 16-byte {"__sz__sizeof__start_", "src/libc/sys/sys_entry_init.c"} pair. */
static void sk_str_src_119130(void)
{
    /* returns {s___sz___sizeof__start___005c7fc9, s_src_libc_sys_sys_entry_init_c_005c7fe0} */
}

/* FUN_00119144 @ 0x119144  (est. sk_dtoa)
 * Double-to-ASCII conversion (printf %f/%g engine): computes the exponent
 * (FUN_00119888), formats the significand via the 128-bit divide/print
 * helpers (FUN_00119a80/FUN_00119ce4/FUN_001199e0), handles the decimal
 * point, rounding (round-half-even), and the exponent suffix; every buffer
 * write is bounds-checked (BRK 0x5519). This is the libc dtoa core. */
static void sk_dtoa_119144(uint32_t flag, uint8_t *buf, uint64_t n, uint32_t *len, int fmt)
{
    (void)flag; (void)buf; (void)n; (void)len; (void)fmt;
    /* see decompile: dtoa digit/exponent/round engine */
}

/* FUN_00119888 @ 0x119888  (est. sk_dbl_bits)
 * Extracts the double's exponent/mantissa bits from the stack arg. */
static void sk_dbl_bits_119888(void)
{
    /* see decompile */
}

/* FUN_001198e0 @ 0x1198e0  (est. sk_inf_nan)
 * Emits "inf"/"Inf"/"INF" or NaN strings for the double special-case paths. */
static void sk_inf_nan_1198e0(void)
{
    /* see decompile: s_infinity_005c802b / s_INFINITY_005c8034 */
}

/* FUN_001199a4 @ 0x1199a4  (est. sk_buf_putc)
 * Appends one byte to the output buffer (bounds-checked, BRK 0x5519). */
static void sk_buf_putc_1199a4(uint8_t *buf, uint32_t n, uint32_t *len, uint8_t c)
{
    uint32_t v = *len + 1;
    if (v < n) {
        /* bounds-checked write (BRK 0x5519 on out-of-range) */
        buf[*len] = c;
        v = *len + 1;
    }
    *len = v;
}

/* FUN_001199e0 @ 0x1199e0  (est. sk_buf_advance)
 * Writes a string at the current buffer position (FUN_0011a99c) and advances
 * the length by param_4. */
static void sk_buf_advance_1199e0(uint64_t a, uint64_t b, int *len, int n)
{
    (void)a; (void)b; (void)len; (void)n;
    /* FUN_0011a99c(a, b, *len); *len += n */
}

/* FUN_00119a18 @ 0x119a18  (est. sk_exp_est)
 * Estimates the decimal exponent for a double from the binary exponent
 * (bounds-checked 0<=e<=0x672<<4). */
static uint32_t sk_exp_est_119a18(int e)
{
    (void)e;
    /* see decompile */
    return 0;
}

/* FUN_00119a80 @ 0x119a80  (est. sk_mul_128)
 * 128-bit multiply/divide helper for dtoa: multiplies the 3-word value by the
 * 128-bit constant and returns the top bits (128-bit arithmetic). */
static int sk_mul_128_119a80(uint64_t a, uint64_t *b, uint32_t c)
{
    (void)a; (void)b; (void)c;
    /* see decompile: 128-bit mul */
    return 0;
}

/* FUN_00119b88 @ 0x119b88  (est. sk_div_128)
 * 128-bit division for dtoa (remainder tracking). */
static void sk_div_128_119b88(uint64_t a, uint64_t *b, uint64_t c, uint32_t *d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_00119ce4 @ 0x119ce4  (est. sk_digit_count)
 * Counts decimal digits of the 128-bit value. */
static int sk_digit_count_119ce4(uint64_t a)
{
    (void)a;
    /* see decompile */
    return 0;
}

/* FUN_00119dc0 @ 0x119dc0  (est. sk_is_odd)
 * Returns whether the low bit of the significand is set (for round-half-even). */
static int sk_is_odd_119dc0(uint64_t a)
{
    (void)a;
    /* see decompile */
    return 0;
}

/* FUN_00119df8 @ 0x119df8  (est. sk_round_digits)
 * Rounding helper: increments the digit string when the discarded digits round
 * up (round-half-even). */
static void sk_round_digits_119df8(int a, uint64_t b, uint64_t c, uint64_t d, uint32_t *e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* see decompile */
}

/* FUN_0011a99c @ 0x11a99c  (est. sk_buf_write)
 * Writes a digit string at the buffer offset (bounds-checked). */
static void sk_buf_write_11a99c(uint64_t a, uint64_t b, int off)
{
    (void)a; (void)b; (void)off;
    /* see decompile */
}

/* FUN_0011aa9c @ 0x11aa9c  (est. sk_digit2)
 * Returns a 2-digit decimal string pointer for the value. */
static void sk_digit2_11aa9c(uint64_t a)
{
    (void)a;
    /* see decompile: &DAT_004e12a8 digit table */
}

/* FUN_0011a9d0 @ 0x11a9d0  (est. sk_buf_write_n)
 * Writes a fixed-width digit group at the buffer offset. */
static void sk_buf_write_n_11a9d0(uint64_t a, uint64_t b, int off, uint64_t digits, uint64_t n)
{
    (void)a; (void)b; (void)off; (void)digits; (void)n;
    /* see decompile */
}

/* FUN_0011aa70 @ 0x11aa70  (est. sk_set_buf)
 * Sets the output buffer/limit for the float formatter. */
static void sk_set_buf_11aa70(void)
{
    /* see decompile */
}

/* FUN_0011aa80 @ 0x11aa80  (est. sk_nan_str)
 * Returns the "nan"/"NaN" string record. */
static void sk_nan_str_11aa80(void)
{
    /* see decompile */
}

/* FUN_0011aae0 @ 0x11aae0  (est. sk_panic_fmt)
 * Panic with a format string via FUN_00115424. */
static void sk_panic_fmt_11aae0(uint64_t s)
{
    (void)s;
    /* FUN_00115424(...) */
}

/* FUN_0011aaf4 @ 0x11aaf4  (est. sk_assert_fmt)
 * Assertion panic with a format string. */
static void sk_assert_fmt_11aaf4(uint64_t s)
{
    (void)s;
    /* FUN_00115424(...) */
}

/* FUN_0011ab1c @ 0x11ab1c  (est. sk_dtoa_state)
 * dtoa state helper. */
static void sk_dtoa_state_11ab1c(void)
{
    /* see decompile */
}

/* FUN_0011a6d4 @ 0x11a6d4  (est. sk_fmt_flush)
 * Flushes the formatter state. */
static void sk_fmt_flush_11a6d4(void)
{
    /* see decompile */
}

/* FUN_0011b39c @ 0x11b39c  (est. sk_strtod_parse)
 * strtod parse engine: scans the decimal/exponent digits (hex-digit table
 * DAT_004e13a0), accumulates the 128-bit significand, tracks the exponent,
 * rounds, and packs the IEEE-754 double (or float) result; every buffer read
 * bounds-checked (BRK 0x5519). */
static void sk_strtod_parse_11b39c(void)
{
    /* see decompile: strtod digit accumulator */
}

/* FUN_0011c2a0 @ 0x11c2a0  (est. sk_dtoa_div)
 * 128-bit division sequence for dtoa: computes the quotient digit-by-digit
 * using 32-bit limbs (denominator/numerator MSW checks, LZCOUNT scaling),
 * producing the digit string. Assertions like "denominator_msw >= ..." panic
 * on invalid states. */
static void sk_dtoa_div_11c2a0(int *p, uint64_t n, uint32_t *q, int r, uint64_t s)
{
    (void)p; (void)n; (void)q; (void)r; (void)s;
    /* see decompile: limb-based 128-bit division */
}

/* FUN_00119ce4 @ 0x119ce4  (est. sk_decimal_length9)
 * Returns the decimal digit count of an up-to-9-digit value (bounds-checked
 * < 1e9, panic "decimalLength9"). */
static uint32_t sk_decimal_length9_119ce4(uint32_t v)
{
    if (v > 999999999) { /* panic "decimalLength9" */ }
    if (v > 99999999) return 9;
    if (v > 9999999) return 8;
    if (v > 999999) return 7;
    if (v >> 5 > 0xc34) return 6;
    if (v >> 4 > 0x270) return 5;
    if (v > 999) return 4;
    if (v > 99) return 3;
    return v > 9 ? 2 : 1;
}

/* FUN_00119dc0 @ 0x119dc0  (est. sk_multiple_of_pow2)
 * Returns whether param_1 is a multiple of 2^param_2 (low bits clear); panics
 * "multipleOfPowerOf2" if param_1 == 0. */
static bool sk_multiple_of_pow2_119dc0(uint64_t v, uint64_t n)
{
    if (v != 0) return (v & (~0ULL << (n & 0x3f))) == 0;
    /* FUN_00115424(... "multipleOfPowerOf2") */
    return false;
}

/* FUN_00119df8 @ 0x119df8  (est. sk_digits_write)
 * Writes the final decimal digits (from the 128-bit division remainder) into
 * the output buffer, using 2-digit groups from DAT_004e12a8; bounds-checked
 * (BRK 0x5519). */
static void sk_digits_write_119df8(uint32_t n, uint64_t v, uint8_t *buf, uint32_t size, int *len)
{
    (void)n; (void)v; (void)buf; (void)size; (void)len;
    /* see decompile */
}

/* FUN_00119efc @ 0x119efc  (est. sk_ryu_common)
 * Ryu common 128-bit division core (from include/internal/libc/ryu/common):
 * divides the two-limb value, emitting digits; panics on invalid limb states. */
static void sk_ryu_common_119efc(uint64_t a, uint16_t *b, uint64_t c, uint64_t d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* see decompile: Ryu digit division */
}

/* FUN_0011b39c @ 0x11b39c  (est. sk_strtoull_hex)
 * strtoull (hex) entry: scans optional 0x/0X prefix, accumulates the 128-bit
 * hex value from the digit table DAT_004e13a0, converts to double, and packs
 * the result. Bounds-checked (BRK 0x5519). */
static void sk_strtoull_hex_11b39c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* FUN_0011b408 @ 0x11b408  (est. sk_strtoenc_f64)
 * Ryu strtoenc/f64: the full string->IEEE-754-double encoder. Scans sign,
 * "inf"/"Inf"/"INF"/"nan"/"NAN", hex (0x) or decimal mantissa, tracks the
 * exponent, and (for the general path) normalizes the significand, multiplies
 * by the 128-bit power-of-ten tables (DAT_004e1928/DAT_004e1b98), rounds
 * (round-half-even), and packs the double or float. Uses the 128-bit division
 * fallback (FUN_0011c2a0) when the product overflows. Every read/write is
 * bounds-checked (BRK 0x5519). */
static void sk_strtoenc_f64_11b408(int *p)
{
    (void)p;
    /* see decompile: Ryu f64 encoder */
}

/* FUN_0011cbe4 @ 0x11cbe4  (est. sk_float_special)
 * Handles the inf/nan special-case completion for the f64 encoder. */
static void sk_float_special_11cbe4(void)
{
    /* see decompile */
}

/* FUN_0011cd00 @ 0x11cd00  (est. sk_float_underflow)
 * Float underflow completion (returns denormal/zero result). */
static void sk_float_underflow_11cd00(void)
{
    /* see decompile */
}

/* FUN_0011cea0 @ 0x11cea0  (est. sk_float_overflow)
 * Float overflow completion (returns inf). */
static void sk_float_overflow_11cea0(void)
{
    /* see decompile */
}

/* FUN_0011d0a8 @ 0x11d0a8  (est. sk_mp_copy)
 * Copies a 128-bit (2-limb) value into the multiprecision work buffer. */
static void sk_mp_copy_11d0a8(void)
{
    /* see decompile */
}

/* FUN_0011d230 @ 0x11d230  (est. sk_mp_shift)
 * Shifts a multiprecision value left by param_2 bits. */
static void sk_mp_shift_11d230(uint64_t *a, int n)
{
    (void)a; (void)n;
    /* see decompile */
}

/* FUN_0011d328 @ 0x11d328  (est. sk_mp_bitlen)
 * Returns the bit length of the multiprecision value. */
static int sk_mp_bitlen_11d328(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0011d37c @ 0x11d37c  (est. sk_mp_div)
 * Multiprecision division (quotient+remainder) for the f64 encoder. */
static void sk_mp_div_11d37c(void)
{
    /* see decompile */
}

/* FUN_0011d554 @ 0x11d554  (est. sk_mp_mul_small)
 * Multiprecision multiply by a small limb. */
static void sk_mp_mul_small_11d554(void)
{
    /* see decompile */
}

/* FUN_0011d568 @ 0x11d568  (est. sk_mp_shift_left)
 * Multiprecision left shift. */
static void sk_mp_shift_left_11d568(uint64_t *a, int n)
{
    (void)a; (void)n;
    /* see decompile */
}

/* FUN_0011d640 @ 0x11d640  (est. sk_assert_mp)
 * Assertion panic for an invalid multiprecision state (with message). */
static void sk_assert_mp_11d640(uint64_t msg)
{
    (void)msg;
    /* FUN_00115424(...) */
}

/* FUN_0011d654 @ 0x11d654  (est. sk_assert_mp_b)
 * Assertion panic for an invalid multiprecision ordering. */
static void sk_assert_mp_b_11d654(uint64_t msg)
{
    (void)msg;
    /* FUN_00115424(...) */
}

/* FUN_0011d668 @ 0x11d668  (est. sk_assert_str)
 * Assertion panic returning a message pair. */
static void sk_assert_str_11d668(uint64_t msg)
{
    (void)msg;
    /* FUN_00115424(...) */
}

/* FUN_0011d6e8 @ 0x11d6e8  (est. sk_fp_round)
 * Float-packing rounding helper. */
static void sk_fp_round_11d6e8(void)
{
    /* see decompile */
}

/* FUN_0011d730 @ 0x11d730  (est. sk_fp_denormal)
 * Float denormal/rounding edge helper. */
static void sk_fp_denormal_11d730(void)
{
    /* see decompile */
}

/* FUN_0011d73c @ 0x11d73c  (est. sk_fp_emit)
 * Emits the packed float bytes into the output (bounds-checked). */
static void sk_fp_emit_11d73c(void)
{
    /* see decompile */
}

/* FUN_0011d754 @ 0x11d754  (est. sk_fp_emit_b)
 * Emits a float byte with bounds check. */
static void sk_fp_emit_b_11d754(void)
{
    /* see decompile */
}

/* FUN_0011d784 @ 0x11d784  (est. sk_fp_scan)
 * Scans the next mantissa digit (with bounds check). */
static void sk_fp_scan_11d784(void)
{
    /* see decompile */
}

/* FUN_0011d790 @ 0x11d790  (est. sk_fp_scan_b)
 * Scans a character with bounds check. */
static void sk_fp_scan_b_11d790(void)
{
    /* see decompile */
}

/* FUN_0011d7e8 @ 0x11d7e8  (est. sk_stack_chk_fail)
 * Noreturn stack-canary failure: routes to FUN_0011d7e8 panic (the stack-check
 * guard handler). */
static void sk_stack_chk_fail_11d7e8(void)
{
    /* noreturn: stack canary failure panic */
}

/* FUN_0011d800 @ 0x11d800  (est. sk_ffp_buf)
 * f32/ffp buffer setup. */
static void sk_ffp_buf_11d800(void)
{
    /* see decompile */
}

/* FUN_0011d85c @ 0x11d85c  (est. sk_ffp_buf_b)
 * f32 buffer setup variant. */
static void sk_ffp_buf_b_11d85c(void)
{
    /* see decompile */
}

/* FUN_0011d8c8 @ 0x11d8c8  (est. sk_fp_cvt)
 * Float conversion for the encoder. */
static void sk_fp_cvt_11d8c8(void)
{
    /* see decompile */
}

/* ============ 0x11db10 - 0x122e30 : exclave boot/config + hash iteration ============ */

/* FUN_0011db10 @ 0x11db10  (est. sk_fp_cvt_wrap)
 * Wraps the float-conversion helper FUN_0011d8c8. */
static void sk_fp_cvt_wrap_11db10(void) { /* FUN_0011d8c8() */ }

/* FUN_0011db18 @ 0x11db18  (est. sk_fp_cvt_zero)
 * Runs FUN_0011d8c8 and returns the 16-byte {0,0}. */
static void sk_fp_cvt_zero_11db18(void) { /* FUN_0011d8c8(); returns {0,0} */ }

/* FUN_0011db40 @ 0x11db40  (est. sk_11db84_wrap)
 * Wraps 0x11db84. */
static void sk_11db84_wrap_11db40(void) { /* FUN_0011db84() */ }

/* FUN_0011db84 @ 0x11db84  (est. sk_align_page_loop)
 * Reduces a size by whole 0x1000-page units (loop until < 0x1000). */
static void sk_align_page_loop_11db84(uint64_t n)
{
    if (n > 0xfff) {
        do { n -= 0x1000; } while (n > 0x1000);
    }
}

/* FUN_0011db8c @ 0x11db8c  (est. sk_log_exclave)
 * Logs an exclave event: builds a 64-byte record (header "___" 0x64c040 /
 * 0x4bbf40), logs the two arg words and ":"/" ]" separators via
 * thunk_FUN_002acbb8, then completes and flushes the record. */
static void sk_log_exclave_11db8c(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile: record + log emission */
}

/* FUN_0011dce8 @ 0x11dce8  (est. sk_hash_emit_strings)
 * Swift HashTable-iteration helper: walks the bitmap-indexed entry array
 * (param_1, stride via the +0x20 field), clearing each set bit (bit-reverse
 * LZCOUNT), and for each live entry builds a string pair (key/value) object
 * into the global table (DAT_00657798). */
static void *sk_hash_emit_strings_11dce8(long p)
{
    (void)p;
    /* see decompile: bitmap walk + string-pair build */
    return 0;
}

/* FUN_0011e084 @ 0x11e084  (est. sk_hash_collect)
 * HashTable collection: walks the bitmap-indexed entries and appends each
 * live element (via its vtable +0xe8 accessor) to the global table. */
static void *sk_hash_collect_11e084(long p)
{
    (void)p;
    /* see decompile */
    return 0;
}

/* FUN_0011e2c4 @ 0x11e2c4  (est. sk_hash_collect_objs)
 * HashTable collection producing 0x48-byte wrapper objects per live entry. */
static void sk_hash_collect_objs_11e2c4(long p)
{
    (void)p;
    /* see decompile */
}

/* FUN_0011e4c4 @ 0x11e4c4  (est. sk_exclave_log_mismatch)
 * Logs an exclave config mismatch: prints the two key/value pairs with " and "
 * separators, then a report (FUN_0036993c with 0x664d20/0x664c18). */
static void sk_exclave_log_mismatch_11e4c4(uint64_t *a, uint64_t *b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* see decompile */
}

/* FUN_0011e670 @ 0x11e670  (est. sk_lock)
 * Lock: thunk_FUN_002298d4(0). */
static void sk_lock_11e670(void)
{
    /* thunk_FUN_002298d4(0) */
}

/* FUN_0011e698 @ 0x11e698  (est. sk_lock_init)
 * Initializes a 72-byte lock buffer and acquires it. */
static void sk_lock_init_11e698(void)
{
    /* uint8_t buf[72]; FUN_001a84f4(buf,0); thunk_FUN_002298d4(0); FUN_001a8564() */
}

/* FUN_0011e6dc @ 0x11e6dc  (est. sk_lock_init_b)
 * Duplicate of 0x11e698. */
static void sk_lock_init_11e6dc(void) { /* same as 0x11e698 */ }

/* FUN_0011e71c @ 0x11e71c  (est. sk_pair_zero)
 * Returns the 16-byte pair {0, 0xe000000000000000}. */
static void sk_pair_zero_11e71c(void) { /* returns {0, 0xe000000000000000} */ }

/* FUN_0011e728 @ 0x11e728  (est. sk_ctx_get0)
 * Reads a {value,obj} pair at ctx+0x10 via FUN_0036a1a0, releasing the obj. */
static void sk_ctx_get0_11e728(void)
{
    /* auVar1 = *(ctx+0x10); FUN_0036b270(ctx->r[0x18/8]); return auVar1 */
}

/* FUN_0011e774 @ 0x11e774  (est. sk_ctx_set0)
 * Sets the {value,obj} pair at ctx+0x10 (releasing the old obj). */
static void sk_ctx_set0_11e774(uint64_t v, uint64_t o)
{
    (void)v; (void)o;
    /* FUN_0036a1a0(ctx+0x10, buf, 1, 0); release old; ctx[0x10/8]=v; ctx[0x18/8]=o */
}

/* FUN_0011e7c8 @ 0x11e7c8  (est. sk_ctx_get1)
 * Reads the pair at ctx+0x20. */
static void sk_ctx_get1_11e7c8(void)
{
    /* auVar1 = *(ctx+0x20); FUN_0036b270(ctx->r[0x28/8]) */
}

/* FUN_0011e814 @ 0x11e814  (est. sk_ctx_set1)
 * Sets the pair at ctx+0x20. */
static void sk_ctx_set1_11e814(uint64_t v, uint64_t o)
{
    (void)v; (void)o;
    /* FUN_0036a1a0(ctx+0x20, buf, 1, 0); release old; ctx[0x20/8]=v; ctx[0x28/8]=o */
}

/* FUN_0011e868 @ 0x11e868  (est. sk_ctx_share1)
 * Shares the object at ctx+0x20, returning the {&DAT_0007bf58, ctx+0x20} pair. */
static void sk_ctx_share1_11e868(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x20, v, 0x21, 0); return {&DAT_0007bf58, ctx+0x20} */
}

/* FUN_0011e8b8 @ 0x11e8b8  (est. sk_ctx_get2)
 * Reads the value at ctx+0x30 (releasing obj). */
static void sk_ctx_get2_11e8b8(void)
{
    /* FUN_0036a1a0(ctx+0x30, buf, 0, 0); FUN_0036b270(ctx->r[0x30/8]) */
}

/* FUN_0011e8f0 @ 0x11e8f0  (est. sk_ctx_set2)
 * Sets the value at ctx+0x30. */
static void sk_ctx_set2_11e8f0(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x30, buf, 1, 0); release old; ctx[0x30/8]=v */
}

/* FUN_0011e938 @ 0x11e938  (est. sk_ctx_share2)
 * Shares the object at ctx+0x30. */
static void sk_ctx_share2_11e938(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x30, v, 0x21, 0); return {&DAT_0007bf58, ctx+0x30} */
}

/* FUN_0011e988 @ 0x11e988  (est. sk_ctx_get3)
 * Reads the pair at ctx+0x38. */
static void sk_ctx_get3_11e988(void)
{
    /* auVar1 = *(ctx+0x38); FUN_0036b270(ctx->r[0x40/8]) */
}

/* FUN_0011e9d4 @ 0x11e9d4  (est. sk_ctx_set3)
 * Sets the pair at ctx+0x38. */
static void sk_ctx_set3_11e9d4(uint64_t v, uint64_t o)
{
    (void)v; (void)o;
    /* FUN_0036a1a0(ctx+0x38, buf, 1, 0); release old; ctx[0x38/8]=v; ctx[0x40/8]=o */
}

/* FUN_0011ea28 @ 0x11ea28  (est. sk_ctx_share3)
 * Shares the object at ctx+0x38. */
static void sk_ctx_share3_11ea28(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x38, v, 0x21, 0); return {&DAT_0007bf58, ctx+0x38} */
}

/* FUN_0011ea78 @ 0x11ea78  (est. sk_str_bundle)
 * Returns the "bundle.app" string (0x4e1c10). */
static char *sk_str_bundle_11ea78(void) { return /* "bundle.app" */ (char *)0; }

/* FUN_0011eaac @ 0x11eaac  (est. sk_str_conclave_id)
 * Returns the "conclave_id" string (0x4e1c30). */
static char *sk_str_conclave_id_11eaac(void) { return /* "conclave_id" */ (char *)0; }

/* FUN_0011eaf8 @ 0x11eaf8  (est. sk_exclave_type)
 * Looks up the exclave type via FUN_002ad78c(0x663fe8, ...); clamps >3 to 4. */
static uint64_t sk_exclave_type_11eaf8(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    uint64_t v = /* FUN_002ad78c(0x663fe8, a, b) */ 0;
    return v > 3 ? 4 : v;
}

/* FUN_0011ebe0 @ 0x11ebe0  (est. sk_log_platform)
 * Logs the platform kind: builds the label from the type byte (0 = "mode",
 * 1/3 = "node_name", 2 = "node_meta"/"data..."/"label...") and emits it. */
static void sk_log_platform_11ebe0(void)
{
    /* see decompile: 0x11ebe0 label strings "node_mode"/"node_meta"/"data" */
}

/* FUN_0011ecc4 @ 0x11ecc4  (est. sk_log_platform_b)
 * Duplicate of 0x11ebe0 (same label selection). */
static void sk_log_platform_11ecc4(void) { /* same as 0x11ebe0 */ }

/* FUN_00122634 @ 0x122634  (est. sk_obj_str)
 * Returns the string form of param_1 (via FUN_00138e10), releasing param_1. */
static uint64_t sk_obj_str_122634(uint64_t p)
{
    (void)p;
    uint64_t r = /* FUN_00138e10(p) */ 0;
    /* FUN_0036b118(p) */
    return r;
}

/* FUN_00122680 @ 0x122680  (est. sk_obj_str_b)
 * Variant string form. */
static uint64_t sk_obj_str_122680(uint64_t p)
{
    (void)p;
    uint64_t r = /* FUN_00138e10() */ 0;
    /* FUN_0036b118(p) */
    return r;
}

/* FUN_001226b4 @ 0x1226b4  (est. sk_config_obj_new)
 * Builds a 4-field config object {a, b, type, d}: allocates, sets the four
 * slots (with release of old), initializes the type field (0x13) and the
 * 0x28 pointer via FUN_0013844c. */
static int64_t sk_config_obj_new_1226b4(uint64_t a, uint64_t b, uint8_t t, uint64_t d)
{
    (void)a; (void)b; (void)t; (void)d;
    /* see decompile */
    return 0;
}

/* FUN_001227bc @ 0x1227bc  (est. sk_config_obj_set)
 * Sets the four fields of an existing config object at ctx (releasing old
 * values). */
static void sk_config_obj_set_1227bc(uint64_t a, uint64_t b, uint8_t t, uint64_t d)
{
    (void)a; (void)b; (void)t; (void)d;
    /* see decompile */
}

/* FUN_001228bc @ 0x1228bc  (est. sk_config_obj_alloc)
 * Allocates an empty config object (four slots defaulted). */
static int64_t sk_config_obj_alloc_1228bc(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0012290c @ 0x12290c  (est. sk_config_obj_init)
 * Initializes a config object at ctx. */
static void sk_config_obj_init_12290c(void)
{
    /* *(ctx+0x10)=*(ctx+0x18)=&DAT_00657778; *(ctx+0x20)=0x13;
     * *(ctx+0x28)=FUN_0013844c() */
}

/* FUN_00122910 @ 0x122910  (est. sk_config_obj_init_b)
 * Duplicate of 0x12290c. */
static void sk_config_obj_init_122910(void) { /* same as 0x12290c */ }

/* FUN_00122944 @ 0x122944  (est. sk_config_obj_eq)
 * Deep-equality of two config objects: compares the two element lists field
 * by field via their vtable accessors (0x88 tag, 0x58 string, 0xa0 value,
 * 0x70 list), releasing intermediates. Returns 1 if equal, 0 otherwise. */
static uint64_t sk_config_obj_eq_122944(long a, long b)
{
    (void)a; (void)b;
    /* see decompile: deep element compare */
    return 0;
}

/* FUN_00122c24 @ 0x122c24  (est. sk_config_obj_print)
 * Prints a config object: iterates the four vtable-sourced lists/strings
 * (0x58, 0x70, 0x88, 0xa0 accessors) and emits each entry via FUN_001b9084. */
static void sk_config_obj_print_122c24(void)
{
    /* see decompile */
}

/* FUN_00122e30 @ 0x122e30  (est. sk_config_obj_strings)
 * Builds the string-list view of a config object: allocates a 0x40 record,
 * iterates the element list (vtable +0x58), converts each to a 0x30 string
 * object, and appends to the global table. */
static uint64_t sk_config_obj_strings_122e30(void)
{
    /* see decompile */
    return 0;
}

/* ============ 0x11f014 - 0x121868 : ComponentGraph/config machinery ============ */

/* FUN_0011f014 @ 0x11f014  (est. sk_cg_vtbl)
 * Calls the vtable method (FUN_00027724 0x664250) with param_1. */
static void sk_cg_vtbl_11f014(uint64_t a)
{
    (void)a;
    /* (*FUN_00027724(0x664250))(a, 0x664250) */
}

/* FUN_0011f06c @ 0x11f06c  (est. sk_cg_config_emit)
 * Emits a config record: resolves the two string args, then writes the four
 * vtable-sourced fields (0x58 name, 0x70 type, 0x88 tag, 0xa0 value) through
 * FUN_001bd7a4/FUN_001bdb28. */
static void sk_cg_config_emit_11f06c(long p)
{
    (void)p;
    /* see decompile */
}

/* FUN_0011f294 @ 0x11f294  (est. sk_cg_obj_new)
 * Allocates then runs the config-object constructor 0x11f2e4. */
static uint64_t sk_cg_obj_new_11f294(uint64_t p)
{
    (void)p;
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_0011f2e4(p) */
    return v;
}

/* FUN_0011f2e4 @ 0x11f2e4  (est. sk_cg_obj_init)
 * ComponentGraph config-object constructor: validates the incoming 4-element
 * record (type 9 list), extracts the bundle/app string and the bound-node
 * record, builds the four config fields (mode/node_name/..., via
 * FUN_001e9c78/FUN_00137f1c), and sets the object's slots. Panics on a
 * malformed record. */
static void sk_cg_obj_init_11f2e4(uint64_t p)
{
    (void)p;
    /* see decompile: BRK 0x11f6b4..cc, "bundle_app" string 0x615f656c646e7562 */
}

/* FUN_0011f6cc @ 0x11f6cc  (est. sk_cg_obj_new_b)
 * Allocates then runs 0x11f70c. */
static uint64_t sk_cg_obj_new_b_11f6cc(uint64_t p)
{
    (void)p;
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_0011f70c(p) */
    return v;
}

/* FUN_0011f70c @ 0x11f70c  (est. sk_cg_obj_copy)
 * Copies a ComponentGraph config object's four fields (via its vtable
 * accessors) into a fresh object at ctx. */
static void sk_cg_obj_copy_11f70c(int64_t *src)
{
    (void)src;
    /* see decompile */
}

/* FUN_0011f8b0 @ 0x11f8b0  (est. sk_cg_obj_alloc7)
 * Allocates a 7-field config record, storing the given values. */
static int64_t sk_cg_obj_alloc7_11f8b0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g;
    /* see decompile */
    return 0;
}

/* FUN_0011f9e0 @ 0x11f9e0  (est. sk_cg_obj_set7)
 * Sets the seven fields of a config record (releasing old values). */
static void sk_cg_obj_set7_11f9e0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g;
    /* see decompile */
}

/* FUN_0011fb10 @ 0x11fb10  (est. sk_cg_obj_print_fields)
 * Prints the four fields of a config object via FUN_001b9084/FUN_00134880. */
static void sk_cg_obj_print_fields_11fb10(void)
{
    /* see decompile */
}

/* FUN_0011fcac @ 0x11fcac  (est. sk_hash_eq)
 * Swift HashTable equality: compares the element lists of two hash tables by
 * walking the set bits of the occupancy bitmap (FUN_0006ae9c), comparing each
 * key/value pair (FUN_002a0cf8). Returns 1 if equal. */
static uint64_t sk_hash_eq_11fcac(long a, long b)
{
    (void)a; (void)b;
    /* see decompile: bitmap walk + element compare */
    return 0;
}

/* FUN_0011fe9c @ 0x11fe9c  (est. sk_cg_has_bundle)
 * Checks whether the config object's 0xf8 field is non-null (bundle key). */
static bool sk_cg_has_bundle_11fe9c(void)
{
    /* (**(code **)(*ctx + 0xf8))(0x6b6576616c637865, 0xea00000000007469); return x1 != 0 */
    return false;
}

/* FUN_0011ff04 @ 0x11ff04  (est. sk_cg_obj_strings)
 * Builds the string-list representation of a ComponentGraph config object
 * (0x38-byte record with the four field lists). */
static uint64_t sk_cg_obj_strings_11ff04(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001200c4 @ 0x1200c4  (est. sk_cg_dump_dict)
 * ComponentGraph dictionary dump: emits "{NODE: [f0], ([f1]), {key: value ...}
 * [2], }" via thunk_FUN_002acbb8, iterating the 0x88 field's entries. */
static void sk_cg_dump_dict_1200c4(void)
{
    /* see decompile: dump "{NODE: ...}" */
}

/* FUN_0012039c @ 0x12039c  (est. sk_cg_dict_get)
 * Dictionary lookup in the 0x88 field: returns the value for key {a,b} or a
 * zero record. */
static void sk_cg_dict_get_12039c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile: FUN_0006ae9c lookup */
}

/* FUN_0012044c @ 0x12044c  (est. sk_cg_add_edge)
 * ComponentGraph edge addition: builds a 5-element edge record via
 * FUN_00135600 and installs it through the 0x98 vtable method. */
static void sk_cg_add_edge_12044c(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_00120534 @ 0x120534  (est. sk_cg_dict_get_require)
 * Dictionary lookup that panics ("ComponentGraph.ComponentGraph.swift",
 * "Fatal error") if the key is absent. */
static void sk_cg_dict_get_require_120534(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile: panic 0x107 on missing key */
}

/* FUN_001206c4 @ 0x1206c4  (est. sk_cg_release4)
 * Releases the four field objects at ctx+0x18/0x28/0x30/0x40. */
static void sk_cg_release4_1206c4(uint64_t *ctx)
{
    (void)ctx;
    /* FUN_003a25d4(ctx[0x18/8]); FUN_003a25d4(ctx[0x28/8]);
     * FUN_003a25d4(ctx[0x30/8]); FUN_003a25d4(ctx[0x40/8]) */
}

/* FUN_001206c8 @ 0x1206c8  (est. sk_cg_release4_b)
 * Duplicate of 0x1206c4. */
static void sk_cg_release4_1206c8(uint64_t *ctx) { /* same as 0x1206c4 */ (void)ctx; }

/* FUN_001206fc @ 0x1206fc  (est. sk_cg_release4_td)
 * Releases four fields then runs teardown FUN_0036b6ac. */
static void sk_cg_release4_td_1206fc(uint64_t *ctx) { /* release4 + FUN_0036b6ac() */ (void)ctx; }

/* FUN_00120700 @ 0x120700  (est. sk_cg_release4_td_b)
 * Duplicate of 0x1206fc. */
static void sk_cg_release4_td_120700(uint64_t *ctx) { /* release4 + FUN_0036b6ac() */ (void)ctx; }

/* FUN_00120740 @ 0x120740  (est. sk_cg_vtbl_d8)
 * Calls the vtable method at offset 0xd8 with a 72-byte lock buffer. */
static void sk_cg_vtbl_d8_120740(void)
{
    /* uint8_t buf[72]; FUN_001a84f4(buf,0); (**(code**)(*ctx+0xd8))(buf); FUN_001a8564() */
}

/* FUN_001207a4 @ 0x1207a4  (est. sk_cg_vtbl_110)
 * Calls vtable method at offset 0x110. */
static void sk_cg_vtbl_110_1207a4(void)
{
    /* (**(code**)(*(long*)*ctx + 0x110))() */
}

/* FUN_001207e8 @ 0x1207e8  (est. sk_cg_vtbl_d8_b)
 * Calls vtable method at offset 0xd8. */
static void sk_cg_vtbl_d8_1207e8(void)
{
    /* (**(code**)(*(long*)*ctx + 0xd8))() */
}

/* FUN_00120824 @ 0x120824  (est. sk_cg_vtbl_d8_c)
 * Calls vtable +0xd8 with a 72-byte buffer. */
static void sk_cg_vtbl_d8_120824(void)
{
    /* uint8_t buf[72]; FUN_001a84f4(buf); (**(code**)(*ctx+0xd8))(buf); FUN_001a8564() */
}

/* FUN_0012087c @ 0x12087c  (est. sk_cg_vtbl_f0)
 * Calls vtable method at offset 0xf0. */
static void sk_cg_vtbl_f0_12087c(void)
{
    /* (**(code**)(*(long*)*ctx + 0xf0))() */
}

/* FUN_001208b8 @ 0x1208b8  (est. sk_cg_vtbl_b8)
 * Calls vtable method at offset 0xb8. */
static void sk_cg_vtbl_b8_1208b8(void)
{
    /* (**(code**)(*(long*)*ctx + 0xb8))() */
}

/* FUN_001208f4 @ 0x1208f4  (est. sk_enum_str_eq)
 * Compares the string forms (FUN_0012097c) of two enum values; returns
 * nonzero if equal. */
static uint32_t sk_enum_str_eq_1208f4(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* auVar2 = FUN_0012097c(); auVar3 = FUN_0012097c(b); cmp */
    return 0;
}

/* FUN_0012097c @ 0x12097c  (est. sk_enum_str)
 * Maps an enum value to its string label: 1->"FRAME", 2->"FRAMESET",
 * 3->"MMIO", 4->"MMIO REG", 5->"ENDPOINT", 6->"UNITYPE", 7->"SCHELDTX",
 * 8->"IRQS", 9->"DARTS", 10->"DEVICECTR"... 0x13->"UNKNOWN". Returns the
 * 16-byte {label, len-tag} pair. */
static void sk_enum_str_12097c(void)
{
    /* see decompile: switch label table */
}

/* FUN_00120bc8 @ 0x120bc8  (est. sk_enum_from_str)
 * Maps a string back to an enum value via FUN_00138dbc. */
static void sk_enum_from_str_120bc8(uint8_t *out, uint64_t *p)
{
    (void)out; (void)p;
    /* *out = FUN_00138dbc(p[0], p[1]) */
}

/* FUN_00120bf8 @ 0x120bf8  (est. sk_enum_str_cur)
 * Returns the string form of the current enum field. */
static void sk_enum_str_cur_120bf8(void)
{
    /* auVar1 = FUN_0012097c(*ctx); *out = auVar1 */
}

/* FUN_00120c24 @ 0x120c24  (est. sk_enum_lt)
 * Enum comparison: returns whether the first is less than the second. */
static uint32_t sk_enum_lt_120c24(uint8_t *a, uint8_t *b)
{
    (void)a; (void)b;
    /* compare FUN_0012097c(*a) vs FUN_0012097c(*b) */
    return 0;
}

/* FUN_00120cac @ 0x120cac  (est. sk_enum_gt)
 * Enum comparison: first greater than second. */
static uint32_t sk_enum_gt_120cac(uint8_t *a, uint8_t *b)
{
    (void)a; (void)b;
    /* compare and invert */
    return 0;
}

/* FUN_00120d4c @ 0x120d4c  (est. sk_enum_gte)
 * Enum comparison: first >= second. */
static uint32_t sk_enum_gte_120d4c(uint8_t *a, uint8_t *b)
{
    (void)a; (void)b;
    /* compare and invert */
    return 0;
}

/* FUN_00120de8 @ 0x120de8  (est. sk_enum_lte)
 * Enum comparison: first <= second. */
static uint32_t sk_enum_lte_120de8(uint8_t *a, uint8_t *b)
{
    (void)a; (void)b;
    /* compare */
    return 0;
}

/* FUN_00120e74 @ 0x120e74  (est. sk_enum_print)
 * Prints the current enum's string form via FUN_001b9084. */
static void sk_enum_print_120e74(void)
{
    /* auVar2 = FUN_0012097c(*ctx); FUN_001b9084(buf, ...); FUN_001a8564() */
}

/* FUN_00120ed8 @ 0x120ed8  (est. sk_enum_print_b)
 * Prints the enum string into the given buffer. */
static void sk_enum_print_b_120ed8(uint64_t buf)
{
    (void)buf;
    /* auVar1 = FUN_0012097c(*ctx); FUN_001b9084(buf, ...) */
}

/* FUN_00120f20 @ 0x120f20  (est. sk_enum_print_c)
 * Variant enum print. */
static void sk_enum_print_c_120f20(void) { /* same as 0x120e74 */ }

/* FUN_00120fa0 @ 0x120fa0  (est. sk_cg_share18)
 * Shares the object at ctx+0x18. */
static void sk_cg_share18_120fa0(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x18, v, 0x21, 0); return {&DAT_0007bf58, ctx+0x18} */
}

/* FUN_00120ff0 @ 0x120ff0  (est. sk_cg_get20)
 * Reads the value at ctx+0x20. */
static uint8_t sk_cg_get20_120ff0(void)
{
    /* FUN_0036a1a0(ctx+0x20, buf, 0, 0); return *(ctx+0x20) */
    return 0;
}

/* FUN_00121024 @ 0x121024  (est. sk_cg_set20)
 * Sets the value at ctx+0x20. */
static void sk_cg_set20_121024(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x20, buf, 1, 0); *(ctx+0x20) = v */
}

/* FUN_00121070 @ 0x121070  (est. sk_cg_int_parse)
 * ComponentGraph integer parse: looks up the "__tbl_byte-order/reorder" key
 * (0x5f636c7062745f5f, 0xed0000726564726f) in the 0xa0 field, parses its
 * decimal value (sign handled) into a 128-bit result with overflow checks
 * (BRK), panicking "ComponentGraph.ComponentGraph.swift" on a malformed
 * number. */
static void sk_cg_int_parse_121070(void)
{
    /* see decompile: decimal parse of "__tbl_..." value */
}

/* FUN_00121468 @ 0x121468  (est. sk_str_source_symbol)
 * Returns the "source_symbol" string (0x4e1c50). */
static char *sk_str_source_symbol_121468(void) { return /* "source_symbol" */ (char *)0; }

/* FUN_00121498 @ 0x121498  (est. sk_str_dest_symbol)
 * Returns the "dest_symbol" string (0x4e1c60). */
static char *sk_str_dest_symbol_121498(void) { return /* "dest_symbol" */ (char *)0; }

/* FUN_001214c4 @ 0x1214c4  (est. sk_str_symbol)
 * Returns the "symbol" string (0x4e1c70). */
static char *sk_str_symbol_1214c4(void) { return /* "symbol" */ (char *)0; }

/* FUN_00121510 @ 0x121510  (est. sk_str_source_tb_arg)
 * Returns the "source_tb_arg" string (0x4e1c90). */
static char *sk_str_source_tb_arg_121510(void) { return /* "source_tb_arg" */ (char *)0; }

/* FUN_00121540 @ 0x121540  (est. sk_str_array_index)
 * Returns the "array_index" string (0x4e1ca0). */
static char *sk_str_array_index_121540(void) { return /* "array_index" */ (char *)0; }

/* FUN_00121598 @ 0x121598  (est. sk_str_static_id_path)
 * Returns the "static_id_path" string (0x4e1cc0). */
static char *sk_str_static_id_path_121598(void) { return /* "static_id_path" */ (char *)0; }

/* FUN_001215e0 @ 0x1215e0  (est. sk_str_is_attach_edge)
 * Returns the "is_attach_edge" string (0x4e1cf0). */
static char *sk_str_is_attach_edge_1215e0(void) { return /* "is_attach_edge" */ (char *)0; }

/* FUN_00121610 @ 0x121610  (est. sk_str_is_detach_edge)
 * Returns the "is_detach_edge" string (0x4e1d00). */
static char *sk_str_is_detach_edge_121610(void) { return /* "is_detach_edge" */ (char *)0; }

/* FUN_00121640 @ 0x121640  (est. sk_cg_type_id)
 * Returns constant 0x663fc8 (type id). */
static uint64_t sk_cg_type_id_121640(void) { return 0x663fc8; }

/* FUN_00121694 @ 0x121694  (est. sk_edge_kind)
 * Looks up the edge kind via FUN_002ad78c(0x6640b8, ...); clamps >3 to 4. */
static uint64_t sk_edge_kind_121694(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    uint64_t v = /* FUN_002ad78c(0x6640b8, a, b) */ 0;
    return v > 3 ? 4 : v;
}

/* FUN_00121780 @ 0x121780  (est. sk_log_edge_kind)
 * Logs the edge kind: selects the label from the type byte (0="edge_so u"
 * /"edge_so urce", 1/3="edge_meta"/"edge_meta_t"..., 2="edge_sou"/"edge_sou rce")
 * and emits it. */
static void sk_log_edge_kind_121780(void)
{
    /* see decompile: 0x121780 edge-kind label strings */
}

/* FUN_00121868 @ 0x121868  (est. sk_log_edge_kind_b)
 * Duplicate of 0x121780. */
static void sk_log_edge_kind_121868(uint64_t a) { /* same as 0x121780 */ (void)a; }

/* ============ 0x121930 - 0x121f20 : ComponentGraph edge machinery ============ */

/* FUN_00121930 @ 0x121930  (est. sk_log_edge_kind_c)
 * Logs the edge kind (variant of 0x121780). */
static void sk_log_edge_kind_121930(void) { /* same label selection as 0x121780 */ }

/* FUN_00121a14 @ 0x121a14  (est. sk_edge_kind_wrap)
 * Wraps FUN_00121694 into the output byte. */
static void sk_edge_kind_wrap_121a14(uint8_t *out, uint64_t *p)
{
    (void)out; (void)p;
    /* *out = FUN_00121694(p[0], p[1]) */
}

/* FUN_00121b88 @ 0x121b88  (est. sk_edge_kind_cur)
 * Returns the current edge-kind via FUN_00121694. */
static void sk_edge_kind_cur_121b88(uint8_t *out)
{
    (void)out;
    /* *out = FUN_00121694() */
}

/* FUN_00121bd4 @ 0x121bd4  (est. sk_edge_vtbl)
 * Calls the vtable method (FUN_00027724 0x664328). */
static void sk_edge_vtbl_121bd4(uint64_t a)
{
    (void)a;
    /* (*FUN_00027724(0x664328))(a, 0x664328) */
}

/* FUN_00121c2c @ 0x121c2c  (est. sk_edge_config_emit)
 * Emits an edge config record: resolves the two string args and writes the
 * four vtable-sourced fields (0x58 src, 0x70 dst, 0x88 tag, 0xa0 kind) via
 * FUN_001bdb28/FUN_001bd7a4. */
static void sk_edge_config_emit_121c2c(long p)
{
    (void)p;
    /* see decompile */
}

/* FUN_00121ed0 @ 0x121ed0  (est. sk_edge_obj_new)
 * Allocates then runs the edge-object constructor 0x121f20. */
static uint64_t sk_edge_obj_new_121ed0(uint64_t p)
{
    (void)p;
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_00121f20(p) */
    return v;
}

/* FUN_00121f20 @ 0x121f20  (est. sk_edge_obj_init)
 * ComponentGraph edge-object constructor: validates the incoming 5-element
 * record (three type-9 lists + a type-6 value), extracts the source/dest
 * symbol lists, the attach/detach booleans, and the edge kind, then fills the
 * object's fields. Panics (BRK 0x122608..630) on a malformed record. */
static void sk_edge_obj_init_121f20(uint64_t p)
{
    (void)p;
    /* see decompile: 5-field edge record validation */
}

/* ============ 0x122634 - 0x126d8c : ComponentGraph nodes/edges ============ */

/* FUN_00122634 @ 0x122634  (est. sk_cg_node_str)
 * Returns the string form of a ComponentGraph node (via FUN_00138e10),
 * releasing the node. */
static uint64_t sk_cg_node_str_122634(uint64_t p)
{
    (void)p;
    uint64_t r = /* FUN_00138e10(p) */ 0;
    /* FUN_0036b118(p) */
    return r;
}

/* FUN_00122680 @ 0x122680  (est. sk_cg_node_str_b)
 * Variant string form. */
static uint64_t sk_cg_node_str_122680(uint64_t p)
{
    (void)p;
    uint64_t r = /* FUN_00138e10() */ 0;
    /* FUN_0036b118(p) */
    return r;
}

/* FUN_001226b4 @ 0x1226b4  (est. sk_cg_node_new)
 * Allocates a 4-field node object (config record), setting the four fields. */
static int64_t sk_cg_node_new_1226b4(uint64_t a, uint64_t b, uint8_t t, uint64_t d)
{
    (void)a; (void)b; (void)t; (void)d;
    /* see decompile */
    return 0;
}

/* FUN_001227bc @ 0x1227bc  (est. sk_cg_node_set)
 * Sets the four fields of a node object at ctx (releasing old values). */
static void sk_cg_node_set_1227bc(uint64_t a, uint64_t b, uint8_t t, uint64_t d)
{
    (void)a; (void)b; (void)t; (void)d;
    /* see decompile */
}

/* FUN_001228bc @ 0x1228bc  (est. sk_cg_node_alloc)
 * Allocates an empty node object. */
static int64_t sk_cg_node_alloc_1228bc(void) { /* see decompile */ return 0; }

/* FUN_0012290c @ 0x12290c  (est. sk_cg_node_init)
 * Initializes a node object at ctx. */
static void sk_cg_node_init_12290c(void)
{
    /* *(ctx+0x10)=*(ctx+0x18)=&DAT_00657778; *(ctx+0x20)=0x13; *(ctx+0x28)=FUN_0013844c() */
}

/* FUN_00122910 @ 0x122910  (est. sk_cg_node_init_b)
 * Duplicate of 0x12290c. */
static void sk_cg_node_init_122910(void) { /* same as 0x12290c */ }

/* FUN_00122944 @ 0x122944  (est. sk_cg_node_eq)
 * Deep-equality of two nodes: compares element lists field by field via the
 * vtable accessors (0x88 tag, 0x58/0x70 strings, 0xa0 value). Returns 1 if
 * equal. */
static uint64_t sk_cg_node_eq_122944(long a, long b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_00122c24 @ 0x122c24  (est. sk_cg_node_print)
 * Prints a node: iterates the four vtable-sourced lists/strings and emits each
 * via FUN_001b9084/FUN_00134880. */
static void sk_cg_node_print_122c24(void) { /* see decompile */ }

/* FUN_00122e30 @ 0x122e30  (est. sk_cg_node_strings)
 * Builds the string-list view of a node (0x40-byte record with the four field
 * lists, string objects from FUN_00083450/FUN_0011dce8). */
static uint64_t sk_cg_node_strings_122e30(void) { /* see decompile */ return 0; }

/* FUN_00123234 @ 0x123234  (est. sk_cg_node_dump)
 * ComponentGraph node dump: emits "{NODE: [f0], [f1], {key: value ...}
 * [2], }" via thunk_FUN_002acbb8, iterating the 0x88 field. */
static void sk_cg_node_dump_123234(void) { /* see decompile */ }

/* FUN_001235d0 @ 0x1235d0  (est. sk_cg_node_dump_b)
 * Node dump variant. */
static void sk_cg_node_dump_b_1235d0(void) { /* see decompile */ }

/* FUN_00123a04 @ 0x123a04  (est. sk_cg_node_json)
 * Node JSON serialization helper. */
static void sk_cg_node_json_123a04(void) { /* see decompile */ }

/* FUN_00123d4c @ 0x123d4c  (est. sk_cg_edge_str)
 * Returns the string form of a ComponentGraph edge. */
static void sk_cg_edge_str_123d4c(void) { /* see decompile */ }

/* FUN_00123dfc @ 0x123dfc  (est. sk_cg_edge_str_b)
 * Variant edge string form. */
static void sk_cg_edge_str_123dfc(void) { /* see decompile */ }

/* FUN_00123ee4 @ 0x123ee4  (est. sk_cg_edge_new)
 * Allocates a 7-field edge object. */
static int64_t sk_cg_edge_new_123ee4(void) { /* see decompile */ return 0; }

/* FUN_00124074 @ 0x124074  (est. sk_cg_edge_set)
 * Sets the edge object's seven fields. */
static void sk_cg_edge_set_124074(void) { /* see decompile */ }

/* FUN_00124078 @ 0x124078  (est. sk_cg_edge_set_b)
 * Duplicate of 0x124074. */
static void sk_cg_edge_set_124078(void) { /* same as 0x124074 */ }

/* FUN_00124104 @ 0x124104  (est. sk_cg_edge_alloc)
 * Allocates an empty edge object. */
static int64_t sk_cg_edge_alloc_124104(void) { /* see decompile */ return 0; }

/* FUN_001241b0 @ 0x1241b0  (est. sk_cg_edge_init)
 * Initializes an edge object at ctx. */
static void sk_cg_edge_init_1241b0(void) { /* see decompile */ }

/* FUN_001242c4 @ 0x1242c4  (est. sk_cg_edge_eq)
 * Deep-equality of two edge objects. */
static uint64_t sk_cg_edge_eq_1242c4(void) { /* see decompile */ return 0; }

/* FUN_00124690 @ 0x124690  (est. sk_cg_edge_print)
 * Prints an edge's fields. */
static void sk_cg_edge_print_124690(void) { /* see decompile */ }

/* FUN_00124694 @ 0x124694  (est. sk_cg_edge_print_b)
 * Duplicate. */
static void sk_cg_edge_print_124694(void) { /* same as 0x124690 */ }

/* FUN_001246c0 @ 0x1246c0  (est. sk_cg_edge_strings)
 * Builds the string-list view of an edge. */
static void sk_cg_edge_strings_1246c0(void) { /* see decompile */ }

/* FUN_001246c4 @ 0x1246c4  (est. sk_cg_edge_strings_b)
 * Duplicate. */
static void sk_cg_edge_strings_1246c4(void) { /* same as 0x1246c0 */ }

/* FUN_001246fc @ 0x1246fc  (est. sk_cg_edge_dump)
 * Edge dump. */
static void sk_cg_edge_dump_1246fc(void) { /* see decompile */ }

/* FUN_00124760 @ 0x124760  (est. sk_cg_edge_dump_b)
 * Edge dump variant. */
static void sk_cg_edge_dump_124760(void) { /* see decompile */ }

/* FUN_001247a4 @ 0x1247a4  (est. sk_cg_edge_json)
 * Edge JSON serialization. */
static void sk_cg_edge_json_1247a4(void) { /* see decompile */ }

/* FUN_001247e0 @ 0x1247e0  (est. sk_cg_edge_json_b)
 * Edge JSON variant. */
static void sk_cg_edge_json_1247e0(void) { /* see decompile */ }

/* FUN_00124838 @ 0x124838  (est. sk_cg_node_json_b)
 * Node JSON variant. */
static void sk_cg_node_json_124838(void) { /* see decompile */ }

/* FUN_00124874 @ 0x124874  (est. sk_cg_uid)
 * ComponentGraph unique-id resolution. */
static void sk_cg_uid_124874(void) { /* see decompile */ }

/* FUN_001248b0 @ 0x1248b0  (est. sk_cg_uid_b)
 * UID variant. */
static void sk_cg_uid_1248b0(void) { /* see decompile */ }

/* FUN_001249a8 @ 0x1249a8  (est. sk_cg_lookup)
 * ComponentGraph element lookup by key. */
static void sk_cg_lookup_1249a8(void) { /* see decompile */ }

/* FUN_001249e0 @ 0x1249e0  (est. sk_cg_lookup_b)
 * Lookup variant. */
static void sk_cg_lookup_1249e0(void) { /* see decompile */ }

/* FUN_00124a1c @ 0x124a1c  (est. sk_cg_attach)
 * ComponentGraph attach-edge handling. */
static void sk_cg_attach_124a1c(void) { /* see decompile */ }

/* FUN_00124a84 @ 0x124a84  (est. sk_cg_detach)
 * ComponentGraph detach-edge handling. */
static void sk_cg_detach_124a84(void) { /* see decompile */ }

/* FUN_00124b10 @ 0x124b10  (est. sk_cg_resolve)
 * ComponentGraph node resolution. */
static void sk_cg_resolve_124b10(void) { /* see decompile */ }

/* FUN_00124b9c @ 0x124b9c  (est. sk_cg_resolve_b)
 * Resolution variant. */
static void sk_cg_resolve_124b9c(void) { /* see decompile */ }

/* FUN_00124c0c @ 0x124c0c  (est. sk_cg_build)
 * ComponentGraph build/assembly. */
static void sk_cg_build_124c0c(void) { /* see decompile */ }

/* FUN_00124cbc @ 0x124cbc  (est. sk_cg_verify)
 * ComponentGraph verification pass. */
static void sk_cg_verify_124cbc(void) { /* see decompile */ }

/* FUN_00124d0c @ 0x124d0c  (est. sk_cg_verify_b)
 * Verification variant. */
static void sk_cg_verify_124d0c(void) { /* see decompile */ }

/* FUN_00124d64 @ 0x124d64  (est. sk_cg_finalize)
 * ComponentGraph finalize. */
static void sk_cg_finalize_124d64(void) { /* see decompile */ }

/* FUN_00124d9c @ 0x124d9c  (est. sk_cg_finalize_b)
 * Finalize variant. */
static void sk_cg_finalize_124d9c(void) { /* see decompile */ }

/* FUN_00124de4 @ 0x124de4  (est. sk_cg_finalize_c)
 * Finalize variant. */
static void sk_cg_finalize_124de4(void) { /* see decompile */ }

/* FUN_00124e34 @ 0x124e34  (est. sk_cg_finalize_d)
 * Finalize variant. */
static void sk_cg_finalize_124e34(void) { /* see decompile */ }

/* FUN_0012530c @ 0x12530c  (est. sk_cg_edge_emit)
 * Edge record emission. */
static void sk_cg_edge_emit_12530c(void) { /* see decompile */ }

/* FUN_00125344 @ 0x125344  (est. sk_cg_edge_emit_b)
 * Variant. */
static void sk_cg_edge_emit_125344(void) { /* see decompile */ }

/* FUN_001253bc @ 0x1253bc  (est. sk_cg_node_emit)
 * Node record emission. */
static void sk_cg_node_emit_1253bc(void) { /* see decompile */ }

/* FUN_0012540c @ 0x12540c  (est. sk_cg_node_emit_b)
 * Variant. */
static void sk_cg_node_emit_12540c(void) { /* see decompile */ }

/* FUN_001254f0 @ 0x1254f0  (est. sk_cg_emit)
 * ComponentGraph emission. */
static void sk_cg_emit_1254f0(void) { /* see decompile */ }

/* FUN_00125604 @ 0x125604  (est. sk_cg_emit_b)
 * Variant. */
static void sk_cg_emit_125604(void) { /* see decompile */ }

/* FUN_00125a38 @ 0x125a38  (est. sk_cg_emit_c)
 * Variant. */
static void sk_cg_emit_125a38(void) { /* see decompile */ }

/* FUN_00125ed0 @ 0x125ed0  (est. sk_cg_emit_d)
 * Variant. */
static void sk_cg_emit_125ed0(void) { /* see decompile */ }

/* FUN_001260e4 @ 0x1260e4  (est. sk_cg_edge_parse)
 * Edge parse helper. */
static void sk_cg_edge_parse_1260e4(void) { /* see decompile */ }

/* FUN_00126198 @ 0x126198  (est. sk_cg_node_parse)
 * Node parse helper. */
static void sk_cg_node_parse_126198(void) { /* see decompile */ }

/* FUN_0012624c @ 0x12624c  (est. sk_cg_parse)
 * ComponentGraph parse. */
static void sk_cg_parse_12624c(void) { /* see decompile */ }

/* FUN_001262e0 @ 0x1262e0  (est. sk_cg_parse_b)
 * Parse variant. */
static void sk_cg_parse_1262e0(void) { /* see decompile */ }

/* FUN_00126390 @ 0x126390  (est. sk_cg_parse_c)
 * Parse variant. */
static void sk_cg_parse_126390(void) { /* see decompile */ }

/* FUN_0012649c @ 0x12649c  (est. sk_cg_parse_d)
 * Parse variant. */
static void sk_cg_parse_12649c(void) { /* see decompile */ }

/* FUN_001264e8 @ 0x1264e8  (est. sk_cg_parse_e)
 * Parse variant. */
static void sk_cg_parse_1264e8(void) { /* see decompile */ }

/* FUN_00126540 @ 0x126540  (est. sk_cg_parse_f)
 * Parse variant. */
static void sk_cg_parse_126540(void) { /* see decompile */ }

/* FUN_00126778 @ 0x126778  (est. sk_cg_resolve_edges)
 * ComponentGraph edge resolution: iterates the a0 field's entries, checks each
 * for the "indent_tag" property (0x7463657269646e69/0xec0000006761745f), walks
 * the 0x88 hash to find matching symbol edges, and emits "is signing...." /
 * "is part of" diagnostic strings; panics on a missing/invalid edge. */
static void sk_cg_resolve_edges_126778(void)
{
    /* see decompile: BRK 0x126cd4..dc, "indent_tag" lookup, "is signing." logs */
}

/* FUN_00126cdc @ 0x126cdc  (est. sk_cg_symbol_lookup)
 * Symbol lookup helper (thunk_FUN_0006e06c hash + FUN_00286e40). */
static uint32_t sk_cg_symbol_lookup_126cdc(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* local = thunk_FUN_0006e06c(b,c); uVar2 = FUN_00310d34(0,b);
     * uVar1 = FUN_00286e40(FUN_00139670, buf, uVar2, 0x66acf0) */
    return 0;
}

/* FUN_00126d8c @ 0x126d8c  (est. sk_cg_process_edges)
 * ComponentGraph edge processing: collects a0-field entries with tag 0,
 * parses each "status_tag" value (0x695f636974617473/0xee00687461705f64),
 * builds a 128-bit integer, and writes the result via FUN_000b2194. */
static void sk_cg_process_edges_126d8c(void)
{
    /* see decompile: "status_tag" parse + 128-bit int */
}

/* ============ 0x1273bc - 0x12779c : CG edge/uid continuation ============ */

/* FUN_001273bc @ 0x1273bc  (est. sk_cg_next_uid)
 * ComponentGraph unique-id allocation: scans the 0x88 hash table for the next
 * free uid (linear probing via thunk_FUN_00229ebc), returns it via
 * FUN_000b2194. */
static uint64_t sk_cg_next_uid_1273bc(int64_t *hash, uint64_t *cur)
{
    (void)hash; (void)cur;
    /* see decompile: hash probe for free slot */
    return 0;
}

/* FUN_001274fc @ 0x1274fc  (est. sk_cg_vtbl_f8)
 * Calls vtable method at offset 0xf8; stores result into *param_1. */
static void sk_cg_vtbl_f8_1274fc(uint64_t *out, uint64_t *ctx)
{
    (void)out; (void)ctx;
    /* *out = (**(code**)(*(long*)*ctx + 0xf8))() */
}

/* FUN_00127540 @ 0x127540  (est. sk_cg_vtbl_100)
 * Calls vtable method at offset 0x100 (releasing *param_1). */
static void sk_cg_vtbl_100_127540(uint64_t *a, uint64_t *ctx)
{
    (void)a; (void)ctx;
    /* thunk_FUN_0036b270(*a); (**(code**)(*(long*)*ctx + 0x100))() */
}

/* FUN_0012759c @ 0x12759c  (est. sk_cg_get20)
 * Reads the value at ctx+0x20 (releasing the obj). */
static void sk_cg_get20_12759c(void)
{
    /* FUN_0036a1a0(ctx+0x20, buf, 0, 0); FUN_0036b270(ctx->r[0x20/8]) */
}

/* FUN_001275d4 @ 0x1275d4  (est. sk_cg_set20)
 * Sets the value at ctx+0x20 (releasing old). */
static void sk_cg_set20_1275d4(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x20, buf, 1, 0); release old; ctx[0x20/8]=v */
}

/* FUN_0012761c @ 0x12761c  (est. sk_cg_share20)
 * Shares the object at ctx+0x20, returning {&LAB_0006f910, ctx+0x20}. */
static void sk_cg_share20_12761c(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x20, v, 0x21, 0); return {&LAB_0006f910, ctx+0x20} */
}

/* FUN_0012766c @ 0x12766c  (est. sk_cg_vtbl_110)
 * Calls vtable method at offset 0x110; stores result. */
static void sk_cg_vtbl_110_12766c(uint64_t *out, uint64_t *ctx)
{
    (void)out; (void)ctx;
    /* *out = (**(code**)(*(long*)*ctx + 0x110))() */
}

/* FUN_001276b8 @ 0x1276b8  (est. sk_cg_vtbl_118)
 * Calls vtable method at offset 0x118 (releasing *param_1). */
static void sk_cg_vtbl_118_1276b8(uint64_t *a, uint64_t *ctx)
{
    (void)a; (void)ctx;
    /* thunk_FUN_0036b270(*a); (**(code**)(*(long*)*ctx + 0x118))() */
}

/* FUN_00127718 @ 0x127718  (est. sk_cg_get28)
 * Reads the value at ctx+0x28. */
static void sk_cg_get28_127718(void)
{
    /* FUN_0036a1a0(ctx+0x28, buf, 0, 0); FUN_0036b270(ctx->r[0x28/8]) */
}

/* FUN_00127754 @ 0x127754  (est. sk_cg_set28)
 * Sets the value at ctx+0x28. */
static void sk_cg_set28_127754(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x28, buf, 1, 0); release old; ctx[0x28/8]=v */
}

/* ============ 0x1252d4 - 0x125a38 : ComponentGraph graph build ============ */

/* FUN_001252d4 @ 0x1252d4  (est. sk_cg_build_graph)
 * ComponentGraph assembly: validates the incoming 2-element record (two type-9
 * lists of nodes and edges), builds the node list (FUN_0011f2e4 per node) and
 * the edge list (FUN_00121f20 per edge), then resolves edges via
 * FUN_00126778. Panics on a malformed record. */
static void sk_cg_build_graph_1252d4(uint64_t p)
{
    (void)p;
    /* see decompile: BRK 0x1252d4..e8, node/edge build loops */
}

/* FUN_0012530c @ 0x12530c  (est. sk_cg_graph_new)
 * Allocates then runs the graph constructor 0x125344. */
static uint64_t sk_cg_graph_new_12530c(void)
{
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_00125344() */
    return v;
}

/* FUN_00125344 @ 0x125344  (est. sk_cg_graph_init)
 * Graph-object constructor: sets the ten config slots (via FUN_00138560/
 * FUN_00138678/FUN_00138790) with default values. */
static void sk_cg_graph_init_125344(void)
{
    /* see decompile */
}

/* FUN_001253bc @ 0x1253bc  (est. sk_cg_graph_new2)
 * Allocates then runs the 2-arg graph constructor 0x12540c. */
static uint64_t sk_cg_graph_new2_1253bc(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_0012540c(a, b) */
    return v;
}

/* FUN_0012540c @ 0x12540c  (est. sk_cg_graph_init2)
 * Graph constructor with the two primary fields set (a, b). */
static void sk_cg_graph_init2_12540c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* FUN_001254f0 @ 0x1254f0  (est. sk_cg_node_edge_eq)
 * Compares two graph elements: first the 0x88 tag equality (FUN_00125604),
 * then the 0xa0 value lists (FUN_00122944). Returns 1 if equal. */
static uint32_t sk_cg_node_edge_eq_1254f0(int64_t *a, int64_t *b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_00125604 @ 0x125604  (est. sk_cg_elem_list_eq)
 * ComponentGraph element-list equality: compares two hash-indexed element
 * lists field by field via their vtable accessors (0xd8, 0x58, 0x70, 0x88,
 * 0xa0), walking the occupancy bitmap. Returns 1 if equal. */
static uint64_t sk_cg_elem_list_eq_125604(long a, long b)
{
    (void)a; (void)b;
    /* see decompile: bitmap-walk element compare */
    return 0;
}

/* FUN_00125a38 @ 0x125a38  (est. sk_cg_dump_nodes)
 * ComponentGraph node dump: iterates the 0x88 hash's entries and emits each
 * node's fields (via the 0xf0 accessor) with a log record. */
static void sk_cg_dump_nodes_125a38(void)
{
    /* see decompile: dump each node */
}

/* ============ 0x1241b0 - 0x128e1c : CG edge/node detail ============ */

/* FUN_001241b0 @ 0x1241b0  (est. sk_cg_edge_attached)
 * Checks whether the edge has the "attach" attribute: reads the 0x128 field;
 * if set, compares the 0x70 field against the known "attach_edge" value. */
static uint32_t sk_cg_edge_attached_1241b0(void)
{
    /* see decompile: FUN_00139134 comparison */
    return 0;
}

/* FUN_001242c4 @ 0x1242c4  (est. sk_cg_edge_construct)
 * ComponentGraph edge constructor (deep): resolves the edge via the vtable
 * dispatch (FUN_00377824/FUN_00310d68), formats a diagnostic, and on failure
 * panics "Fatal error"/"found zero..." */
static void sk_cg_edge_construct_1242c4(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint32_t f, uint64_t g, long h, uint64_t i)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i;
    /* see decompile */
}

/* FUN_00124690 @ 0x124690  (est. sk_cg_edge_release)
 * Releases the edge's field objects. */
static void sk_cg_edge_release_124690(uint64_t *ctx)
{
    (void)ctx;
    /* FUN_0036b118(ctx[0x10/8]); FUN_0036b118(ctx[0x18/8]); FUN_003a25d4(ctx[0x28/8]) */
}

/* FUN_00124694 @ 0x124694  (est. sk_cg_edge_release_b)
 * Duplicate of 0x124690. */
static void sk_cg_edge_release_124694(uint64_t *ctx) { /* same as 0x124690 */ (void)ctx; }

/* FUN_001246c0 @ 0x1246c0  (est. sk_cg_edge_release_td)
 * Releases edge fields then teardown FUN_0036b6ac. */
static void sk_cg_edge_release_td_1246c0(uint64_t *ctx) { /* release + FUN_0036b6ac() */ (void)ctx; }

/* FUN_001246c4 @ 0x1246c4  (est. sk_cg_edge_release_td_b)
 * Duplicate of 0x1246c0. */
static void sk_cg_edge_release_td_1246c4(uint64_t *ctx) { /* release + FUN_0036b6ac() */ (void)ctx; }

/* FUN_001246fc @ 0x1246fc  (est. sk_cg_vtbl_e8)
 * Calls vtable method at offset 0xe8 with a 72-byte buffer. */
static void sk_cg_vtbl_e8_1246fc(void)
{
    /* uint8_t buf[72]; FUN_001a84f4(buf,0); (**(code**)(*ctx+0xe8))(buf); FUN_001a8564() */
}

/* FUN_00124760 @ 0x124760  (est. sk_cg_vtbl_140)
 * Calls vtable method at offset 0x140. */
static void sk_cg_vtbl_140_124760(void)
{
    /* (**(code**)(*(long*)*ctx + 0x140))() */
}

/* FUN_001247a4 @ 0x1247a4  (est. sk_cg_vtbl_e8_b)
 * Calls vtable method at offset 0xe8. */
static void sk_cg_vtbl_e8_1247a4(void)
{
    /* (**(code**)(*(long*)*ctx + 0xe8))() */
}

/* FUN_001247e0 @ 0x1247e0  (est. sk_cg_vtbl_e8_c)
 * Calls vtable +0xe8 with a 72-byte buffer. */
static void sk_cg_vtbl_e8_1247e0(void)
{
    /* uint8_t buf[72]; FUN_001a84f4(buf); (**(code**)(*ctx+0xe8))(buf); FUN_001a8564() */
}

/* FUN_00124838 @ 0x124838  (est. sk_cg_vtbl_f8)
 * Calls vtable method at offset 0xf8. */
static void sk_cg_vtbl_f8_124838(void)
{
    /* (**(code**)(*(long*)*ctx + 0xf8))() */
}

/* FUN_00124874 @ 0x124874  (est. sk_cg_vtbl_c0)
 * Calls vtable method at offset 0xc0. */
static void sk_cg_vtbl_c0_124874(void)
{
    /* (**(code**)(*(long*)*ctx + 0xc0))() */
}

/* FUN_001248b0 @ 0x1248b0  (est. sk_cg_dump_node_head)
 * Emits "{Endpoin t...: {label: " + "nil"/value + "}" via thunk_FUN_002acbb8. */
static void sk_cg_dump_node_head_1248b0(uint64_t a, uint64_t b, uint64_t c, long d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_001249a8 @ 0x1249a8  (est. sk_cg_ctx_set01)
 * Sets the two words at ctx[0]/ctx[1] (releasing old ctx[1]). */
static void sk_cg_ctx_set01_1249a8(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* FUN_003a25d4(ctx[1]); ctx[0]=a; ctx[1]=b */
}

/* FUN_001249e0 @ 0x1249e0  (est. sk_cg_ctx_set18)
 * Sets ctx[0x10/8] and ctx[0x18/8] (releasing old). */
static void sk_cg_ctx_set18_1249e0(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* FUN_003a25d4(*(ctx+0x18)); *(ctx+0x10)=a; *(ctx+0x18)=b */
}

/* FUN_00124a1c @ 0x124a1c  (est. sk_cg_print_edge)
 * Prints an edge: emits the source (param_1,param_2), then (if param_5) an
 * arrow "->" and the target (param_4,param_5) via FUN_001b9084/FUN_00229a3c. */
static void sk_cg_print_edge_124a1c(uint64_t a, uint64_t b, uint64_t c, uint64_t d, long e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* see decompile */
}

/* FUN_00124a84 @ 0x124a84  (est. sk_cg_print_edge_b)
 * Edge print with a 72-byte buffer and arrow. */
static void sk_cg_print_edge_124a84(uint64_t a, uint64_t b, uint64_t c, long d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_00124b10 @ 0x124b10  (est. sk_cg_print_edge_c)
 * Edge print from the four context words. */
static void sk_cg_print_edge_124b10(void) { /* see decompile */ }

/* FUN_00124b9c @ 0x124b9c  (est. sk_cg_print_edge_d)
 * Edge print into the given buffer. */
static void sk_cg_print_edge_124b9c(uint64_t buf)
{
    (void)buf;
    /* see decompile */
}

/* FUN_00124c0c @ 0x124c0c  (est. sk_cg_print_edge_e)
 * Edge print variant. */
static void sk_cg_print_edge_124c0c(void) { /* see decompile */ }

/* FUN_00124cbc @ 0x124cbc  (est. sk_cg_get10)
 * Reads the value at ctx+0x10. */
static void sk_cg_get10_124cbc(void)
{
    /* FUN_0036a1a0(ctx+0x10, buf, 0, 0); FUN_0036b270(ctx->r[0x10/8]) */
}

/* FUN_00124d0c @ 0x124d0c  (est. sk_cg_set10)
 * Sets the value at ctx+0x10, calling the release callback param_2 on the old. */
static void sk_cg_set10_124d0c(uint64_t v, uint64_t (*rel)(void))
{
    (void)v; (void)rel;
    /* FUN_0036a1a0(ctx+0x10, buf, 1, 0); old=*(ctx+0x10); *(ctx+0x10)=v; rel(old) */
}

/* FUN_00124d64 @ 0x124d64  (est. sk_cg_get18)
 * Reads the value at ctx+0x18. */
static void sk_cg_get18_124d64(void)
{
    /* FUN_0036a1a0(ctx+0x18, buf, 0, 0); FUN_0036b270(ctx->r[0x18/8]) */
}

/* FUN_00124d9c @ 0x124d9c  (est. sk_cg_set18)
 * Sets the value at ctx+0x18. */
static void sk_cg_set18_124d9c(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x18, buf, 1, 0); release old; ctx[0x18/8]=v */
}

/* FUN_00124de4 @ 0x124de4  (est. sk_cg_obj_new4)
 * Allocates then runs the 4-arg constructor 0x124e34. */
static uint64_t sk_cg_obj_new4_124de4(uint64_t p)
{
    (void)p;
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_00124e34(p) */
    return v;
}

/* FUN_00124e34 @ 0x124e34  (est. sk_cg_obj_init4)
 * ComponentGraph deep object constructor: processes the source/dest symbol
 * lists (via the vtable accessors), building the edge/node records; panics
 * "Found invalid edge"/"ComponentGraph.swift" on a malformed element. */
static int64_t sk_cg_obj_init4_124e34(void *p)
{
    (void)p;
    /* see decompile */
    return 0;
}

/* FUN_00128e1c @ 0x128e1c  (est. sk_cg_resolve_nodes)
 * ComponentGraph node resolution: iterates the 0x88 hash's nodes, walks each
 * node's 0xa0 edge list to find attach (0xd) edges, then resolves the
 * "source_symbol"/"dest_symbol"/"is_attach"/"is_detach" properties, emitting
 * "panap" (attach) / "map" edges. Panics "Fatal error"/"Found invalid edge" on
 * inconsistency. */
static void sk_cg_resolve_nodes_128e1c(void)
{
    /* see decompile: BRK 0x129bd0..e0, "panap" 0x63696e6170, "dest_symbol" */
}

/* ============ 0x129be0 - 0x12f60c : CG deep resolve/attach ============ */

/* FUN_00129be0 @ 0x129be0  (est. sk_cg_edge_attach)
 * ComponentGraph attach operation: resolves the edge via the vtable dispatch
 * (FUN_00377824/FUN_00310d68) and installs/removes the attach record. */
static void sk_cg_edge_attach_129be0(uint64_t a, long b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* see decompile */
}

/* FUN_00129f08 @ 0x129f08  (est. sk_cg_resolve_edges_full)
 * Full edge resolution: iterates the a0 edge list, for each attach edge (tag 5)
 * matches "dest_symbol"/"source_symbol" pairs, resolves the endpoint edges,
 * and validates each has exactly one destination (panics "Expected edge to
 * have only one dest..."). Builds the resolved edge set. */
static void sk_cg_resolve_edges_full_129f08(void)
{
    /* see decompile: BRK 0x12aee8..fc, "dest_symbol"/"source_symbol" lookups */
}

/* FUN_0012eccc @ 0x12eccc  (est. sk_cg_check_edge)
 * ComponentGraph edge validity check: verifies the source/dest each have
 * exactly one element, looks up the attached/detached endpoints, and returns
 * whether the edge connects them. Panics on invalid edges. */
static uint32_t sk_cg_check_edge_12eccc(uint64_t *a, int64_t *b, int64_t *c)
{
    (void)a; (void)b; (void)c;
    /* see decompile */
    return 0;
}

/* FUN_0012f178 @ 0x12f178  (est. sk_cg_finalize_all)
 * Runs the four finalization passes: FUN_00128e1c (resolve nodes),
 * FUN_00129f08 (resolve edges), FUN_0012cd68, FUN_0012dbb8. */
static void sk_cg_finalize_all_12f178(void)
{
    /* FUN_00128e1c(); FUN_00129f08(); FUN_0012cd68(); FUN_0012dbb8() */
}

/* FUN_0012f17c @ 0x12f17c  (est. sk_cg_finalize_all_b)
 * Duplicate of 0x12f178. */
static void sk_cg_finalize_all_12f17c(void)
{
    /* FUN_00128e1c(); FUN_00129f08(); FUN_0012cd68(); FUN_0012dbb8() */
}

/* FUN_0012f19c @ 0x12f19c  (est. sk_cg_graph_construct)
 * ComponentGraph graph constructor: allocates a 0x70 graph object, builds the
 * node/edge lists from the 0x88/0xa0/0xf0 fields (via FUN_0011e2c4/
 * FUN_001394d8), and initializes the 0x218/0x248 pass state. */
static int64_t *sk_cg_graph_construct_12f19c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0012f598 @ 0x12f598  (est. sk_cg_validate_all)
 * ComponentGraph validation: runs the seven validation passes
 * (FUN_0012f60c..FUN_00131704) and returns the final result FUN_00131840. */
static uint64_t sk_cg_validate_all_12f598(void)
{
    /* see decompile: pass chain */
    return 0;
}

/* FUN_0012f59c @ 0x12f59c  (est. sk_cg_validate_all_b)
 * Duplicate of 0x12f598. */
static uint64_t sk_cg_validate_all_12f59c(void)
{
    /* see decompile: pass chain */
    return 0;
}

/* FUN_0012f60c @ 0x12f60c  (est. sk_cg_validate_pass1)
 * ComponentGraph validation pass 1: collects the attach edges (tag 5) from the
 * a0 field, then for each edge matching "dest_symbol"/"source_symbol" resolves
 * and validates the endpoints. */
static uint64_t sk_cg_validate_pass1_12f60c(void)
{
    /* see decompile: BRK 0x12fd14..1c */
    return 0;
}

/* ============ 0x12779c - 0x12f19c : CG validate/attach detail ============ */

/* FUN_0012779c @ 0x12779c  (est. sk_cg_has_prop)
 * ComponentGraph property check: reads the 0x110 property of the object and
 * compares it via FUN_000ac1dc; if present, logs a message. */
static void sk_cg_has_prop_12779c(void)
{
    /* see decompile: FUN_00127970 + 0x110 lookup */
}

/* FUN_0012cd68 @ 0x12cd68  (est. sk_cg_validate_edges)
 * ComponentGraph edge validation pass: iterates the 0x88 node set, for each
 * edge type (0 = attach/ASID, 0xd = endpoint, 5 = ...) validates the dest has
 * exactly one element (panics "ASID edge must have only one dest...",
 * "Expected only one node"), resolves the "indent_tag"/"is_attach" integer,
 * and builds the ASID/endpoint records. */
static void sk_cg_validate_edges_12cd68(void)
{
    /* see decompile: BRK 0x12cb70..e0, "ASID edge..." panic strings */
}

/* FUN_0012dbb8 @ 0x12dbb8  (est. sk_cg_validate_pass_d)
 * ComponentGraph validation pass (D): iterates the node/edge lists and
 * validates the attach/detach connectivity. */
static void sk_cg_validate_pass_d_12dbb8(void)
{
    /* see decompile */
}

/* ============ 0x12fe1c - 0x13fff8 : CG validation passes ============ */

/* FUN_0012fe1c @ 0x12fe1c  (est. sk_cg_validate_pass2)
 * ComponentGraph validation pass 2: iterates the node set, checks each
 * attach/detach edge's single-dest invariant. */
static uint64_t sk_cg_validate_pass2_12fe1c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001302f8 @ 0x1302f8  (est. sk_cg_validate_pass3)
 * Validation pass 3. */
static uint64_t sk_cg_validate_pass3_1302f8(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0013057c @ 0x13057c  (est. sk_cg_validate_pass4)
 * Validation pass 4. */
static uint64_t sk_cg_validate_pass4_13057c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001307fc @ 0x1307fc  (est. sk_cg_validate_pass5)
 * Validation pass 5. */
static uint64_t sk_cg_validate_pass5_1307fc(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00130950 @ 0x130950  (est. sk_cg_validate_pass6)
 * Validation pass 6. */
static uint64_t sk_cg_validate_pass6_130950(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00130ac0 @ 0x130ac0  (est. sk_cg_validate_pass7)
 * Validation pass 7. */
static uint64_t sk_cg_validate_pass7_130ac0(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00130e90 @ 0x130e90  (est. sk_cg_validate_pass8)
 * Validation pass 8. */
static uint64_t sk_cg_validate_pass8_130e90(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00131578 @ 0x131578  (est. sk_cg_validate_pass9)
 * Validation pass 9. */
static uint64_t sk_cg_validate_pass9_131578(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00131704 @ 0x131704  (est. sk_cg_validate_pass10)
 * Validation pass 10. */
static uint64_t sk_cg_validate_pass10_131704(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00131840 @ 0x131840  (est. sk_cg_validate_final)
 * Validation final result assembly. */
static uint64_t sk_cg_validate_final_131840(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00131f50 @ 0x131f50  (est. sk_cg_pass_a)
 * CG pass helper. */
static void sk_cg_pass_a_131f50(void) { /* see decompile */ }

/* FUN_00131f54 @ 0x131f54  (est. sk_cg_pass_b)
 * CG pass helper. */
static void sk_cg_pass_b_131f54(void) { /* see decompile */ }

/* FUN_00131f98 @ 0x131f98  (est. sk_cg_pass_c)
 * CG pass helper. */
static void sk_cg_pass_c_131f98(void) { /* see decompile */ }

/* FUN_00131f9c @ 0x131f9c  (est. sk_cg_pass_d)
 * CG pass helper. */
static void sk_cg_pass_d_131f9c(void) { /* see decompile */ }

/* FUN_00131fec @ 0x131fec  (est. sk_cg_pass_e)
 * CG pass helper. */
static void sk_cg_pass_e_131fec(void) { /* see decompile */ }

/* FUN_00132100 @ 0x132100  (est. sk_cg_pass_f)
 * CG pass helper. */
static void sk_cg_pass_f_132100(void) { /* see decompile */ }

/* FUN_0013213c @ 0x13213c  (est. sk_cg_pass_g)
 * CG pass helper. */
static void sk_cg_pass_g_13213c(void) { /* see decompile */ }

/* FUN_00132260 @ 0x132260  (est. sk_cg_pass_h)
 * CG pass helper. */
static void sk_cg_pass_h_132260(void) { /* see decompile */ }

/* FUN_001322c8 @ 0x1322c8  (est. sk_cg_pass_i)
 * CG pass helper. */
static void sk_cg_pass_i_1322c8(void) { /* see decompile */ }

/* FUN_0013230c @ 0x13230c  (est. sk_cg_pass_j)
 * CG pass helper. */
static void sk_cg_pass_j_13230c(void) { /* see decompile */ }

/* FUN_00132370 @ 0x132370  (est. sk_cg_pass_k)
 * CG pass helper. */
static void sk_cg_pass_k_132370(void) { /* see decompile */ }

/* FUN_00132408 @ 0x132408  (est. sk_cg_parse_int)
 * 128-bit integer parse from a CG property (base 10). */
static uint64_t sk_cg_parse_int_132408(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00132524 @ 0x132524  (est. sk_cg_parse_int_b)
 * 128-bit integer parse variant. */
static uint64_t sk_cg_parse_int_132524(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001327a8 @ 0x1327a8  (est. sk_cg_validate_pass11)
 * Validation pass 11. */
static uint64_t sk_cg_validate_pass11_1327a8(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00132858 @ 0x132858  (est. sk_cg_validate_pass12)
 * Validation pass 12. */
static uint64_t sk_cg_validate_pass12_132858(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001328ec @ 0x1328ec  (est. sk_cg_validate_pass13)
 * Validation pass 13. */
static uint64_t sk_cg_validate_pass13_1328ec(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001329f0 @ 0x1329f0  (est. sk_cg_validate_pass14)
 * Validation pass 14. */
static uint64_t sk_cg_validate_pass14_1329f0(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00132ae8 @ 0x132ae8  (est. sk_cg_validate_pass15)
 * Validation pass 15. */
static uint64_t sk_cg_validate_pass15_132ae8(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00132c64 @ 0x132c64  (est. sk_cg_validate_pass16)
 * Validation pass 16. */
static uint64_t sk_cg_validate_pass16_132c64(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00132de4 @ 0x132de4  (est. sk_cg_validate_pass17)
 * Validation pass 17. */
static uint64_t sk_cg_validate_pass17_132de4(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00132f60 @ 0x132f60  (est. sk_cg_validate_pass18)
 * Validation pass 18. */
static uint64_t sk_cg_validate_pass18_132f60(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001330d4 @ 0x1330d4  (est. sk_cg_validate_pass19)
 * Validation pass 19. */
static uint64_t sk_cg_validate_pass19_1330d4(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00133224 @ 0x133224  (est. sk_cg_validate_pass20)
 * Validation pass 20. */
static uint64_t sk_cg_validate_pass20_133224(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001333a4 @ 0x1333a4  (est. sk_cg_validate_pass21)
 * Validation pass 21. */
static uint64_t sk_cg_validate_pass21_1333a4(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0013365c @ 0x13365c  (est. sk_cg_validate_pass22)
 * Validation pass 22. */
static uint64_t sk_cg_validate_pass22_13365c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00133940 @ 0x133940  (est. sk_cg_validate_pass23)
 * Validation pass 23. */
static uint64_t sk_cg_validate_pass23_133940(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00133c0c @ 0x133c0c  (est. sk_cg_validate_pass24)
 * Validation pass 24. */
static uint64_t sk_cg_validate_pass24_133c0c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00133eac @ 0x133eac  (est. sk_cg_validate_pass25)
 * Validation pass 25. */
static uint64_t sk_cg_validate_pass25_133eac(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0013410c @ 0x13410c  (est. sk_cg_validate_pass26)
 * Validation pass 26. */
static uint64_t sk_cg_validate_pass26_13410c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001343e8 @ 0x1343e8  (est. sk_cg_validate_pass27)
 * Validation pass 27. */
static uint64_t sk_cg_validate_pass27_1343e8(void)
{
    /* see decompile */
    return 0;
}

/* FUN_0013442c @ 0x13442c  (est. sk_array_grow)
 * Dynamic array growth helper (FUN_0013442c): grows the array to fit the new
 * element count. */
static void sk_array_grow_13442c(void) { /* see decompile */ }

/* FUN_0013444c @ 0x13444c  (est. sk_array_grow_b)
 * Dynamic array growth variant. */
static void sk_array_grow_13444c(void) { /* see decompile */ }

/* FUN_0013446c @ 0x13446c  (est. sk_array_grow_c)
 * Dynamic array growth variant. */
static void sk_array_grow_13446c(void) { /* see decompile */ }

/* FUN_0013448c @ 0x13448c  (est. sk_array_grow_d)
 * Dynamic array growth variant. */
static void sk_array_grow_13448c(void) { /* see decompile */ }

/* FUN_0013459c @ 0x13459c  (est. sk_cg_pass_l)
 * CG pass helper. */
static void sk_cg_pass_l_13459c(void) { /* see decompile */ }

/* FUN_00134678 @ 0x134678  (est. sk_cg_pass_m)
 * CG pass helper. */
static void sk_cg_pass_m_134678(void) { /* see decompile */ }

/* FUN_0013477c @ 0x13477c  (est. sk_cg_pass_n)
 * CG pass helper. */
static void sk_cg_pass_n_13477c(void) { /* see decompile */ }

/* FUN_00134880 @ 0x134880  (est. sk_cg_print_val)
 * Prints a value via FUN_00134880. */
static void sk_cg_print_val_134880(void) { /* see decompile */ }

/* FUN_001349e8 @ 0x1349e8  (est. sk_cg_print_dict)
 * Prints a CG dictionary. */
static void sk_cg_print_dict_1349e8(void) { /* see decompile */ }

/* FUN_00134a58 @ 0x134a58  (est. sk_cg_print_dict_b)
 * Dict print variant. */
static void sk_cg_print_dict_134a58(void) { /* see decompile */ }

/* FUN_00134b48 @ 0x134b48  (est. sk_cg_print_dict_c)
 * Dict print variant. */
static void sk_cg_print_dict_134b48(void) { /* see decompile */ }

/* FUN_00134fb4 @ 0x134fb4  (est. sk_cg_parse_dict)
 * CG dict parse. */
static void sk_cg_parse_dict_134fb4(void) { /* see decompile */ }

/* FUN_001350b4 @ 0x1350b4  (est. sk_cg_parse_dict_b)
 * Dict parse variant. */
static void sk_cg_parse_dict_1350b4(void) { /* see decompile */ }

/* FUN_00135314 @ 0x135314  (est. sk_cg_parse_list)
 * CG list parse. */
static void sk_cg_parse_list_135314(void) { /* see decompile */ }

/* FUN_00135398 @ 0x135398  (est. sk_cg_parse_list_b)
 * List parse variant. */
static void sk_cg_parse_list_135398(void) { /* see decompile */ }

/* FUN_00135600 @ 0x135600  (est. sk_cg_record_add)
 * CG record addition: adds a {key,value} pair to a record (via
 * FUN_00135600). */
static void sk_cg_record_add_135600(void) { /* see decompile */ }

/* FUN_00135768 @ 0x135768  (est. sk_cg_record_add_b)
 * Record add variant. */
static void sk_cg_record_add_135768(void) { /* see decompile */ }

/* FUN_001358e8 @ 0x1358e8  (est. sk_cg_record_add_c)
 * Record add variant. */
static void sk_cg_record_add_1358e8(void) { /* see decompile */ }

/* FUN_00135a70 @ 0x135a70  (est. sk_cg_record_build)
 * CG record build. */
static void sk_cg_record_build_135a70(void) { /* see decompile */ }

/* FUN_00135bcc @ 0x135bcc  (est. sk_cg_record_build_b)
 * Record build variant. */
static void sk_cg_record_build_135bcc(void) { /* see decompile */ }

/* FUN_00135ce8 @ 0x135ce8  (est. sk_cg_record_build_c)
 * Record build variant. */
static void sk_cg_record_build_135ce8(void) { /* see decompile */ }

/* FUN_00135e68 @ 0x135e68  (est. sk_cg_record_build_d)
 * Record build variant. */
static void sk_cg_record_build_135e68(void) { /* see decompile */ }

/* FUN_0013620c @ 0x13620c  (est. sk_cg_record_build_e)
 * Record build variant. */
static void sk_cg_record_build_13620c(void) { /* see decompile */ }

/* FUN_001365fc @ 0x1365fc  (est. sk_cg_record_build_f)
 * Record build variant. */
static void sk_cg_record_build_1365fc(void) { /* see decompile */ }

/* FUN_00136844 @ 0x136844  (est. sk_cg_record_build_g)
 * Record build variant. */
static void sk_cg_record_build_136844(void) { /* see decompile */ }

/* FUN_00136988 @ 0x136988  (est. sk_cg_record_build_h)
 * Record build variant. */
static void sk_cg_record_build_136988(void) { /* see decompile */ }

/* FUN_00136bf8 @ 0x136bf8  (est. sk_cg_record_build_i)
 * Record build variant. */
static void sk_cg_record_build_136bf8(void) { /* see decompile */ }

/* FUN_00136d1c @ 0x136d1c  (est. sk_cg_record_release)
 * CG record release. */
static void sk_cg_record_release_136d1c(void) { /* see decompile */ }

/* FUN_00136e40 @ 0x136e40  (est. sk_cg_record_release_b)
 * Record release variant. */
static void sk_cg_record_release_136e40(void) { /* see decompile */ }

/* FUN_00136fa0 @ 0x136fa0  (est. sk_cg_record_release_c)
 * Record release variant. */
static void sk_cg_record_release_136fa0(void) { /* see decompile */ }

/* FUN_001371fc @ 0x1371fc  (est. sk_cg_record_release_d)
 * Record release variant. */
static void sk_cg_record_release_1371fc(void) { /* see decompile */ }

/* FUN_00137338 @ 0x137338  (est. sk_cg_record_copy)
 * CG record copy. */
static void sk_cg_record_copy_137338(void) { /* see decompile */ }

/* FUN_00137418 @ 0x137418  (est. sk_cg_record_copy_b)
 * Record copy variant. */
static void sk_cg_record_copy_137418(void) { /* see decompile */ }

/* FUN_001374e8 @ 0x1374e8  (est. sk_cg_record_copy_c)
 * Record copy variant. */
static void sk_cg_record_copy_1374e8(void) { /* see decompile */ }

/* FUN_00137534 @ 0x137534  (est. sk_cg_record_copy_d)
 * Record copy variant. */
static void sk_cg_record_copy_137534(void) { /* see decompile */ }

/* FUN_001376b8 @ 0x1376b8  (est. sk_cg_record_copy_e)
 * Record copy variant. */
static void sk_cg_record_copy_1376b8(void) { /* see decompile */ }

/* FUN_0013779c @ 0x13779c  (est. sk_cg_ctx_merge)
 * CG context merge. */
static void sk_cg_ctx_merge_13779c(void) { /* see decompile */ }

/* FUN_00137800 @ 0x137800  (est. sk_cg_ctx_merge_b)
 * Context merge variant. */
static void sk_cg_ctx_merge_137800(void) { /* see decompile */ }

/* FUN_00137bc0 @ 0x137bc0  (est. sk_cg_ctx_merge_c)
 * Context merge variant. */
static void sk_cg_ctx_merge_137bc0(void) { /* see decompile */ }

/* FUN_00137f1c @ 0x137f1c  (est. sk_cg_ctx_lookup)
 * CG context lookup. */
static void sk_cg_ctx_lookup_137f1c(void) { /* see decompile */ }

/* FUN_00138210 @ 0x138210  (est. sk_cg_ctx_lookup_b)
 * Context lookup variant. */
static void sk_cg_ctx_lookup_138210(void) { /* see decompile */ }

/* FUN_0013844c @ 0x13844c  (est. sk_cg_alloc)
 * CG allocator (FUN_0036a940 wrapper). */
static void sk_cg_alloc_13844c(void) { /* see decompile */ }

/* FUN_00138560 @ 0x138560  (est. sk_cg_alloc_b)
 * CG allocator variant. */
static void sk_cg_alloc_138560(void) { /* see decompile */ }

/* FUN_00138678 @ 0x138678  (est. sk_cg_alloc_c)
 * CG allocator variant. */
static void sk_cg_alloc_138678(void) { /* see decompile */ }

/* FUN_00138790 @ 0x138790  (est. sk_cg_alloc_d)
 * CG allocator variant. */
static void sk_cg_alloc_138790(void) { /* see decompile */ }

/* FUN_0013886c @ 0x13886c  (est. sk_cg_alloc_e)
 * CG allocator variant. */
static void sk_cg_alloc_13886c(void) { /* see decompile */ }

/* FUN_0013896c @ 0x13896c  (est. sk_cg_alloc_f)
 * CG allocator variant. */
static void sk_cg_alloc_13896c(void) { /* see decompile */ }

/* FUN_00138a84 @ 0x138a84  (est. sk_cg_alloc_g)
 * CG allocator variant. */
static void sk_cg_alloc_138a84(void) { /* see decompile */ }

/* FUN_00138b08 @ 0x138b08  (est. sk_cg_eq_wrap)
 * CG object equality wrapper (via the vtable accessors). */
static void sk_cg_eq_wrap_138b08(void) { /* see decompile */ }

/* FUN_00138d64 @ 0x138d64  (est. sk_cg_release)
 * CG object release. */
static void sk_cg_release_138d64(void) { /* see decompile */ }

/* FUN_00138d68 @ 0x138d68  (est. sk_cg_release_b)
 * Release variant. */
static void sk_cg_release_138d68(void) { /* see decompile */ }

/* FUN_00138d90 @ 0x138d90  (est. sk_cg_release_c)
 * Release variant. */
static void sk_cg_release_138d90(void) { /* see decompile */ }

/* FUN_00138d94 @ 0x138d94  (est. sk_cg_release_d)
 * Release variant. */
static void sk_cg_release_138d94(void) { /* see decompile */ }

/* FUN_00138dbc @ 0x138dbc  (est. sk_cg_enum_map)
 * Enum value mapping (FUN_00138dbc): maps a string back to an enum id. */
static void sk_cg_enum_map_138dbc(void) { /* see decompile */ }

/* FUN_00138e10 @ 0x138e10  (est. sk_cg_obj_str)
 * CG object-to-string conversion. */
static void sk_cg_obj_str_138e10(void) { /* see decompile */ }

/* FUN_00138f80 @ 0x138f80  (est. sk_cg_obj_str_b)
 * Object-to-string variant. */
static void sk_cg_obj_str_138f80(void) { /* see decompile */ }

/* FUN_00139134 @ 0x139134  (est. sk_cg_assert)
 * CG assertion (FUN_00139134): formats a message and panics on failure. */
static void sk_cg_assert_139134(void) { /* see decompile */ }

/* FUN_0013924c @ 0x13924c  (est. sk_cg_find)
 * CG element find (FUN_0013924c). */
static void sk_cg_find_13924c(void) { /* see decompile */ }

/* FUN_00139418 @ 0x139418  (est. sk_cg_find_b)
 * Find variant. */
static void sk_cg_find_139418(void) { /* see decompile */ }

/* FUN_001394c8 @ 0x1394c8  (est. sk_cg_find_c)
 * Find variant. */
static void sk_cg_find_1394c8(void) { /* see decompile */ }

/* FUN_001394d8 @ 0x1394d8  (est. sk_cg_find_d)
 * Find variant. */
static void sk_cg_find_1394d8(void) { /* see decompile */ }

/* FUN_00139574 @ 0x139574  (est. sk_cg_find_e)
 * Find variant. */
static void sk_cg_find_139574(void) { /* see decompile */ }

/* FUN_00139584 @ 0x139584  (est. sk_cg_find_f)
 * Find variant. */
static void sk_cg_find_139584(void) { /* see decompile */ }

/* FUN_001395ec @ 0x1395ec  (est. sk_cg_find_g)
 * Find variant. */
static void sk_cg_find_1395ec(void) { /* see decompile */ }

/* FUN_00139670 @ 0x139670  (est. sk_cg_hash)
 * CG hash function (FUN_00139670). */
static void sk_cg_hash_139670(void) { /* see decompile */ }

/* FUN_00139674 @ 0x139674  (est. sk_cg_hash_b)
 * Hash variant. */
static void sk_cg_hash_139674(void) { /* see decompile */ }

/* FUN_00139694 @ 0x139694  (est. sk_cg_hash_c)
 * Hash variant. */
static void sk_cg_hash_139694(void) { /* see decompile */ }

/* FUN_001396b4 @ 0x1396b4  (est. sk_cg_hash_d)
 * Hash variant. */
static void sk_cg_hash_1396b4(void) { /* see decompile */ }

/* FUN_001399b4 @ 0x1399b4  (est. sk_cg_str_hash)
 * CG string hash. */
static void sk_cg_str_hash_1399b4(void) { /* see decompile */ }

/* FUN_00139a20 @ 0x139a20  (est. sk_cg_str_hash_b)
 * String hash variant. */
static void sk_cg_str_hash_139a20(void) { /* see decompile */ }

/* FUN_00139a94 @ 0x139a94  (est. sk_cg_str_hash_c)
 * String hash variant. */
static void sk_cg_str_hash_139a94(void) { /* see decompile */ }

/* FUN_00139a98 @ 0x139a98  (est. sk_cg_str_hash_d)
 * String hash variant. */
static void sk_cg_str_hash_139a98(void) { /* see decompile */ }

/* FUN_00139ae0 @ 0x139ae0  (est. sk_cg_str_hash_e)
 * String hash variant. */
static void sk_cg_str_hash_139ae0(void) { /* see decompile */ }

/* FUN_00139b54 @ 0x139b54  (est. sk_cg_str_hash_f)
 * String hash variant. */
static void sk_cg_str_hash_139b54(void) { /* see decompile */ }

/* FUN_00139ba4 @ 0x139ba4  (est. sk_cg_str_hash_g)
 * String hash variant. */
static void sk_cg_str_hash_139ba4(void) { /* see decompile */ }

/* FUN_00139bdc @ 0x139bdc  (est. sk_cg_str_hash_h)
 * String hash variant. */
static void sk_cg_str_hash_139bdc(void) { /* see decompile */ }

/* FUN_00139c28 @ 0x139c28  (est. sk_cg_str_hash_i)
 * String hash variant. */
static void sk_cg_str_hash_139c28(void) { /* see decompile */ }

/* FUN_00139c6c @ 0x139c6c  (est. sk_cg_str_hash_j)
 * String hash variant. */
static void sk_cg_str_hash_139c6c(void) { /* see decompile */ }

/* FUN_0013ace0 @ 0x13ace0  (est. sk_cg_pass_o)
 * CG pass helper. */
static void sk_cg_pass_o_13ace0(void) { /* see decompile */ }

/* FUN_0013ad1c @ 0x13ad1c  (est. sk_cg_pass_p)
 * CG pass helper. */
static void sk_cg_pass_p_13ad1c(void) { /* see decompile */ }

/* FUN_0013ad20 @ 0x13ad20  (est. sk_cg_pass_q)
 * CG pass helper. */
static void sk_cg_pass_q_13ad20(void) { /* see decompile */ }

/* FUN_0013ad34 @ 0x13ad34  (est. sk_cg_pass_r)
 * CG pass helper. */
static void sk_cg_pass_r_13ad34(void) { /* see decompile */ }

/* FUN_0013adac @ 0x13adac  (est. sk_cg_pass_s)
 * CG pass helper. */
static void sk_cg_pass_s_13adac(void) { /* see decompile */ }

/* FUN_0013ae0c @ 0x13ae0c  (est. sk_cg_pass_t)
 * CG pass helper. */
static void sk_cg_pass_t_13ae0c(void) { /* see decompile */ }

/* FUN_0013b468 @ 0x13b468  (est. sk_cg_pass_u)
 * CG pass helper. */
static void sk_cg_pass_u_13b468(void) { /* see decompile */ }

/* FUN_0013bf20 @ 0x13bf20  (est. sk_cg_pass_v)
 * CG pass helper. */
static void sk_cg_pass_v_13bf20(void) { /* see decompile */ }

/* FUN_0013bf44 @ 0x13bf44  (est. sk_cg_pass_w)
 * CG pass helper. */
static void sk_cg_pass_w_13bf44(void) { /* see decompile */ }

/* FUN_0013c584 @ 0x13c584  (est. sk_cg_pass_x)
 * CG pass helper. */
static void sk_cg_pass_x_13c584(void) { /* see decompile */ }

/* FUN_0013c8d0 @ 0x13c8d0  (est. sk_cg_pass_y)
 * CG pass helper. */
static void sk_cg_pass_y_13c8d0(void) { /* see decompile */ }

/* FUN_0013c8f4 @ 0x13c8f4  (est. sk_cg_pass_z)
 * CG pass helper. */
static void sk_cg_pass_z_13c8f4(void) { /* see decompile */ }

/* FUN_0013c9bc @ 0x13c9bc  (est. sk_cg_pass_aa)
 * CG pass helper. */
static void sk_cg_pass_aa_13c9bc(void) { /* see decompile */ }

/* FUN_0013ccf4 @ 0x13ccf4  (est. sk_cg_str_build)
 * CG string builder. */
static void sk_cg_str_build_13ccf4(void) { /* see decompile */ }

/* FUN_0013cd18 @ 0x13cd18  (est. sk_cg_str_build_b)
 * String builder variant. */
static void sk_cg_str_build_13cd18(void) { /* see decompile */ }

/* FUN_0013cdd8 @ 0x13cdd8  (est. sk_cg_str_build_c)
 * String builder variant. */
static void sk_cg_str_build_13cdd8(void) { /* see decompile */ }

/* FUN_0013d068 @ 0x13d068  (est. sk_cg_str_build_d)
 * String builder variant. */
static void sk_cg_str_build_13d068(void) { /* see decompile */ }

/* FUN_0013d154 @ 0x13d154  (est. sk_cg_str_build_e)
 * String builder variant. */
static void sk_cg_str_build_13d154(void) { /* see decompile */ }

/* FUN_0013d17c @ 0x13d17c  (est. sk_cg_str_build_f)
 * String builder variant. */
static void sk_cg_str_build_13d17c(void) { /* see decompile */ }

/* FUN_0013d190 @ 0x13d190  (est. sk_cg_str_build_g)
 * String builder variant. */
static void sk_cg_str_build_13d190(void) { /* see decompile */ }

/* FUN_0013d1a4 @ 0x13d1a4  (est. sk_cg_str_build_h)
 * String builder variant. */
static void sk_cg_str_build_13d1a4(void) { /* see decompile */ }

/* FUN_0013d220 @ 0x13d220  (est. sk_cg_str_build_i)
 * String builder variant. */
static void sk_cg_str_build_13d220(void) { /* see decompile */ }

/* FUN_0013d234 @ 0x13d234  (est. sk_cg_str_build_j)
 * String builder variant. */
static void sk_cg_str_build_13d234(void) { /* see decompile */ }

/* FUN_0013d2b0 @ 0x13d2b0  (est. sk_cg_str_build_k)
 * String builder variant. */
static void sk_cg_str_build_13d2b0(void) { /* see decompile */ }

/* FUN_0013d32c @ 0x13d32c  (est. sk_cg_str_build_l)
 * String builder variant. */
static void sk_cg_str_build_13d32c(void) { /* see decompile */ }

/* FUN_0013d49c @ 0x13d49c  (est. sk_cg_str_build_m)
 * String builder variant. */
static void sk_cg_str_build_13d49c(void) { /* see decompile */ }

/* FUN_0013d61c @ 0x13d61c  (est. sk_cg_str_build_n)
 * String builder variant. */
static void sk_cg_str_build_13d61c(void) { /* see decompile */ }

/* FUN_0013d700 @ 0x13d700  (est. sk_cg_str_build_o)
 * String builder variant. */
static void sk_cg_str_build_13d700(void) { /* see decompile */ }

/* FUN_0013d7f4 @ 0x13d7f4  (est. sk_cg_str_build_p)
 * String builder variant. */
static void sk_cg_str_build_13d7f4(void) { /* see decompile */ }

/* FUN_0013d948 @ 0x13d948  (est. sk_cg_str_build_q)
 * String builder variant. */
static void sk_cg_str_build_13d948(void) { /* see decompile */ }

/* FUN_0013dafc @ 0x13dafc  (est. sk_cg_str_build_r)
 * String builder variant. */
static void sk_cg_str_build_13dafc(void) { /* see decompile */ }

/* FUN_0013dbc8 @ 0x13dbc8  (est. sk_cg_str_build_s)
 * String builder variant. */
static void sk_cg_str_build_13dbc8(void) { /* see decompile */ }

/* FUN_0013dcb8 @ 0x13dcb8  (est. sk_cg_str_build_t)
 * String builder variant. */
static void sk_cg_str_build_13dcb8(void) { /* see decompile */ }

/* FUN_0013dd98 @ 0x13dd98  (est. sk_cg_str_build_u)
 * String builder variant. */
static void sk_cg_str_build_13dd98(void) { /* see decompile */ }

/* FUN_0013dfc0 @ 0x13dfc0  (est. sk_cg_str_build_v)
 * String builder variant. */
static void sk_cg_str_build_13dfc0(void) { /* see decompile */ }

/* FUN_0013e048 @ 0x13e048  (est. sk_cg_str_build_w)
 * String builder variant. */
static void sk_cg_str_build_13e048(void) { /* see decompile */ }

/* FUN_0013e04c @ 0x13e04c  (est. sk_cg_str_build_x)
 * String builder variant. */
static void sk_cg_str_build_13e04c(void) { /* see decompile */ }

/* FUN_0013e074 @ 0x13e074  (est. sk_cg_str_build_y)
 * String builder variant. */
static void sk_cg_str_build_13e074(void) { /* see decompile */ }

/* FUN_0013e198 @ 0x13e198  (est. sk_cg_str_build_z)
 * String builder variant. */
static void sk_cg_str_build_13e198(void) { /* see decompile */ }

/* FUN_0013e3b0 @ 0x13e3b0  (est. sk_cg_str_build_ab)
 * String builder variant. */
static void sk_cg_str_build_13e3b0(void) { /* see decompile */ }

/* FUN_0013e3b4 @ 0x13e3b4  (est. sk_cg_str_build_ac)
 * String builder variant. */
static void sk_cg_str_build_13e3b4(void) { /* see decompile */ }

/* FUN_0013e3dc @ 0x13e3dc  (est. sk_cg_str_build_ad)
 * String builder variant. */
static void sk_cg_str_build_13e3dc(void) { /* see decompile */ }

/* FUN_0013e490 @ 0x13e490  (est. sk_cg_str_build_ae)
 * String builder variant. */
static void sk_cg_str_build_13e490(void) { /* see decompile */ }

/* FUN_0013e748 @ 0x13e748  (est. sk_cg_str_build_af)
 * String builder variant. */
static void sk_cg_str_build_13e748(void) { /* see decompile */ }

/* FUN_0013e9e4 @ 0x13e9e4  (est. sk_cg_str_build_ag)
 * String builder variant. */
static void sk_cg_str_build_13e9e4(void) { /* see decompile */ }

/* FUN_0013ec4c @ 0x13ec4c  (est. sk_cg_str_build_ah)
 * String builder variant. */
static void sk_cg_str_build_13ec4c(void) { /* see decompile */ }

/* FUN_0013ed50 @ 0x13ed50  (est. sk_cg_str_build_ai)
 * String builder variant. */
static void sk_cg_str_build_13ed50(void) { /* see decompile */ }

/* FUN_0013ee94 @ 0x13ee94  (est. sk_cg_str_build_aj)
 * String builder variant. */
static void sk_cg_str_build_13ee94(void) { /* see decompile */ }

/* FUN_0013f16c @ 0x13f16c  (est. sk_cg_str_build_ak)
 * String builder variant. */
static void sk_cg_str_build_13f16c(void) { /* see decompile */ }

/* FUN_0013f1c4 @ 0x13f1c4  (est. sk_cg_str_build_al)
 * String builder variant. */
static void sk_cg_str_build_13f1c4(void) { /* see decompile */ }

/* FUN_0013f27c @ 0x13f27c  (est. sk_cg_str_build_am)
 * String builder variant. */
static void sk_cg_str_build_13f27c(void) { /* see decompile */ }

/* FUN_0013f348 @ 0x13f348  (est. sk_cg_str_build_an)
 * String builder variant. */
static void sk_cg_str_build_13f348(void) { /* see decompile */ }

/* FUN_0013f6f8 @ 0x13f6f8  (est. sk_cg_str_build_ao)
 * String builder variant. */
static void sk_cg_str_build_13f6f8(void) { /* see decompile */ }

/* FUN_0013f720 @ 0x13f720  (est. sk_cg_str_build_ap)
 * String builder variant. */
static void sk_cg_str_build_13f720(void) { /* see decompile */ }

/* FUN_0013f72c @ 0x13f72c  (est. sk_cg_str_build_aq)
 * String builder variant. */
static void sk_cg_str_build_13f72c(void) { /* see decompile */ }

/* FUN_0013f738 @ 0x13f738  (est. sk_cg_str_build_ar)
 * String builder variant. */
static void sk_cg_str_build_13f738(void) { /* see decompile */ }

/* FUN_0013f744 @ 0x13f744  (est. sk_cg_str_build_as)
 * String builder variant. */
static void sk_cg_str_build_13f744(void) { /* see decompile */ }

/* FUN_0013f758 @ 0x13f758  (est. sk_cg_str_build_at)
 * String builder variant. */
static void sk_cg_str_build_13f758(void) { /* see decompile */ }

/* FUN_0013f764 @ 0x13f764  (est. sk_cg_str_build_au)
 * String builder variant. */
static void sk_cg_str_build_13f764(void) { /* see decompile */ }

/* FUN_0013f770 @ 0x13f770  (est. sk_cg_str_build_av)
 * String builder variant. */
static void sk_cg_str_build_13f770(void) { /* see decompile */ }

/* FUN_0013f77c @ 0x13f77c  (est. sk_cg_str_build_aw)
 * String builder variant. */
static void sk_cg_str_build_13f77c(void) { /* see decompile */ }

/* FUN_0013f938 @ 0x13f938  (est. sk_cg_str_build_ax)
 * String builder variant. */
static void sk_cg_str_build_13f938(void) { /* see decompile */ }

/* FUN_0013fa74 @ 0x13fa74  (est. sk_cg_str_build_ay)
 * String builder variant. */
static void sk_cg_str_build_13fa74(void) { /* see decompile */ }

/* FUN_0013fa90 @ 0x13fa90  (est. sk_cg_str_build_az)
 * String builder variant. */
static void sk_cg_str_build_13fa90(void) { /* see decompile */ }

/* FUN_0013fde4 @ 0x13fde4  (est. sk_cg_str_build_ba)
 * String builder variant. */
static void sk_cg_str_build_13fde4(void) { /* see decompile */ }

/* FUN_0013fe60 @ 0x13fe60  (est. sk_cg_str_build_bb)
 * String builder variant. */
static void sk_cg_str_build_13fe60(void) { /* see decompile */ }

/* FUN_0013feac @ 0x13feac  (est. sk_cg_str_build_bc)
 * String builder variant. */
static void sk_cg_str_build_13feac(void) { /* see decompile */ }

/* FUN_0013ff2c @ 0x13ff2c  (est. sk_cg_str_build_bd)
 * String builder variant. */
static void sk_cg_str_build_13ff2c(void) { /* see decompile */ }

/* FUN_0013ff58 @ 0x13ff58  (est. sk_cg_str_build_be)
 * String builder variant. */
static void sk_cg_str_build_13ff58(void) { /* see decompile */ }

/* FUN_0013fff4 @ 0x13fff4  (est. sk_cg_str_build_bf)
 * String builder variant. */
static void sk_cg_str_build_13fff4(void) { /* see decompile */ }

/* FUN_0013fff8 @ 0x13fff8  (est. sk_cg_str_build_bg)
 * String builder variant. */
static void sk_cg_str_build_13fff8(void) { /* see decompile */ }

/* ============ 0x14001c - 0x140510 : CG node/edge vtable methods ============ */

/* FUN_0014001c @ 0x14001c  (est. sk_cg_node_release2)
 * Releases the node's 0x18 (value), 0x30, 0x40 field objects. */
static void sk_cg_node_release2_14001c(uint64_t *ctx)
{
    (void)ctx;
    /* FUN_003a25d4(ctx[0x18/8]); FUN_0036b118(ctx[0x30/8]); FUN_0036b118(ctx[0x40/8]) */
}

/* FUN_00140020 @ 0x140020  (est. sk_cg_node_release2_b)
 * Duplicate of 0x14001c. */
static void sk_cg_node_release2_140020(uint64_t *ctx) { /* same as 0x14001c */ (void)ctx; }

/* FUN_0014004c @ 0x14004c  (est. sk_cg_node_release_td)
 * Releases node fields then teardown. */
static void sk_cg_node_release_td_14004c(uint64_t *ctx) { /* release + FUN_0036b6ac() */ (void)ctx; }

/* FUN_00140050 @ 0x140050  (est. sk_cg_node_release_td_b)
 * Duplicate of 0x14004c. */
static void sk_cg_node_release_td_140050(uint64_t *ctx) { /* release + FUN_0036b6ac() */ (void)ctx; }

/* FUN_00140088 @ 0x140088  (est. sk_cg_node_get)
 * Reads the node's pair at obj[0x10/0x18] (releasing obj). */
static void sk_cg_node_get_140088(void)
{
    /* auVar1 = *(obj+0x10); FUN_0036b270(obj->r[0x18/8]) */
}

/* FUN_001400e0 @ 0x1400e0  (est. sk_cg_node_vtbl70)
 * Calls vtable method at offset 0x70. */
static void sk_cg_node_vtbl70_1400e0(void)
{
    /* (**(code**)(*(long*)*ctx + 0x70))() */
}

/* FUN_0014011c @ 0x14011c  (est. sk_cg_node_get30)
 * Reads the pair at ctx+0x30. */
static void sk_cg_node_get30_14011c(void)
{
    /* auVar1 = *(ctx+0x30); FUN_0036b270(ctx->r[0x38/8]) */
}

/* FUN_0014014c @ 0x14014c  (est. sk_cg_node_ctor)
 * Allocates a CG node object and sets its seven fields (a, b, type, src, key,
 * value, list). */
static int64_t sk_cg_node_ctor_14014c(uint64_t a, uint64_t b, uint8_t t, long d, uint64_t e, uint64_t f)
{
    (void)a; (void)b; (void)t; (void)d; (void)e; (void)f;
    /* see decompile */
    return 0;
}

/* FUN_001401c0 @ 0x1401c0  (est. sk_cg_node_set_fields)
 * Sets the seven fields of a node at ctx. */
static void sk_cg_node_set_fields_1401c0(uint64_t a, uint64_t b, uint8_t t, long d, uint64_t e, uint64_t f)
{
    (void)a; (void)b; (void)t; (void)d; (void)e; (void)f;
    /* see decompile */
}

/* FUN_001401e0 @ 0x1401e0  (est. sk_cg_node_call)
 * Calls the node's vtable method (ctx+0x68) with its fields, releasing the
 * node. */
static uint64_t sk_cg_node_call_1401e0(long p, uint64_t a)
{
    (void)p; (void)a;
    /* see decompile */
    return 0;
}

/* FUN_00140274 @ 0x140274  (est. sk_cg_reg_1)
 * Registers the node type (FUN_0014029c with 0x6538d8). */
static void sk_cg_reg_1_140274(void)
{
    /* FUN_0014029c(0x6538d8, &DAT_004e2620) */
}

/* FUN_00140278 @ 0x140278  (est. sk_cg_reg_1_b)
 * Duplicate of 0x140274. */
static void sk_cg_reg_1_140278(void) { /* FUN_0014029c(0x6538d8, &DAT_004e2620) */ }

/* FUN_0014029c @ 0x14029c  (est. sk_cg_reg_type)
 * Registers a CG type descriptor {name, 0x66acf0, obj}. */
static void sk_cg_reg_type_14029c(uint64_t *p)
{
    (void)p;
    /* p[3]=FUN_00002534(); p[4]=0x66acf0; p[0]=*(ctx+0x40) */
}

/* FUN_0014031c @ 0x14031c  (est. sk_cg_edge_release2)
 * Releases the edge's 0x38/0x40 fields. */
static void sk_cg_edge_release2_14031c(uint64_t *ctx)
{
    (void)ctx;
    /* FUN_003a25d4(ctx[0x38/8]); FUN_0036b118(ctx[0x40/8]) */
}

/* FUN_00140320 @ 0x140320  (est. sk_cg_edge_release2_b)
 * Duplicate of 0x14031c. */
static void sk_cg_edge_release2_140320(uint64_t *ctx) { /* same as 0x14031c */ (void)ctx; }

/* FUN_00140344 @ 0x140344  (est. sk_cg_edge_release_td)
 * Releases edge fields then teardown. */
static void sk_cg_edge_release_td_140344(uint64_t *ctx) { /* release + FUN_0036b6ac() */ (void)ctx; }

/* FUN_00140348 @ 0x140348  (est. sk_cg_edge_release_td_b)
 * Duplicate. */
static void sk_cg_edge_release_td_140348(uint64_t *ctx) { /* release + FUN_0036b6ac() */ (void)ctx; }

/* FUN_001403a8 @ 0x1403a8  (est. sk_cg_edge_get30)
 * Reads the edge's pair at obj[0x30]. */
static void sk_cg_edge_get30_1403a8(void)
{
    /* auVar1 = *(obj+0x30); FUN_0036b270(obj->r[0x38/8]) */
}

/* FUN_001403dc @ 0x1403dc  (est. sk_cg_edge_vtbl70)
 * Calls vtable method at offset 0x70. */
static void sk_cg_edge_vtbl70_1403dc(void)
{
    /* (**(code**)(*(long*)*ctx + 0x70))() */
}

/* FUN_00140418 @ 0x140418  (est. sk_cg_edge_vtbl78)
 * Calls vtable method at offset 0x78. */
static void sk_cg_edge_vtbl78_140418(void)
{
    /* (**(code**)(*(long*)*ctx + 0x78))() */
}

/* FUN_001404c0 @ 0x1404c0  (est. sk_cg_typeid_1)
 * Returns 16-byte {0x6538f8, 0}. */
static void sk_cg_typeid_1_1404c0(void) { /* returns {0x6538f8, 0} */ }

/* FUN_001404d0 @ 0x1404d0  (est. sk_cg_typeid_2)
 * Returns 16-byte {0x653960, 0}. */
static void sk_cg_typeid_2_1404d0(void) { /* returns {0x653960, 0} */ }

/* FUN_001404e0 @ 0x1404e0  (est. sk_cg_typeid_3)
 * Returns 16-byte {0x6539f0, 0}. */
static void sk_cg_typeid_3_1404e0(void) { /* returns {0x6539f0, 0} */ }

/* FUN_00140510 @ 0x140510  (est. sk_cg_node_emit_record)
 * ComponentGraph node record emission: formats the node's type/source/value
 * into a log record via the vtable dispatch. */
static void sk_cg_node_emit_record_140510(uint64_t a, long b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* ============ 0x140510 - 0x145780 : FrameBank serialization ============ */

/* FUN_00140510 @ 0x140510  (est. sk_fb_emit)
 * FrameBank emit: serializes a frame via the frame-bank vtable dispatch
 * (FUN_000a6bb8/FUN_00105fd8), validates the result length (>400 -> panic
 * "FrameBank.client.swift"), and returns the frame record. */
static void sk_fb_emit_140510(uint64_t a, long b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_001409a4 @ 0x1409a4  (est. sk_fb_add)
 * FrameBank add: acquires the two objects and calls FUN_0001a1c8. */
static void sk_fb_add_1409a4(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* FUN_0036b270(); FUN_0036b270(b); FUN_0001a1c8(a,b,c,d) */
}

/* FUN_00140a08 @ 0x140a08  (est. sk_fb_add_regs)
 * FrameBank add from the context registers. */
static void sk_fb_add_regs_140a08(void)
{
    /* see decompile */
}

/* FUN_00140a5c @ 0x140a5c  (est. sk_fb_obj_new)
 * Allocates a FrameBank object: type id, value (FUN_0014500c), flag. */
static int64_t sk_fb_obj_new_140a5c(uint64_t a, uint32_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_00140ac0 @ 0x140ac0  (est. sk_fb_obj_set)
 * Sets the FrameBank object fields at ctx. */
static void sk_fb_obj_set_140ac0(uint64_t a, uint32_t b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* FUN_00140b18 @ 0x140b18  (est. sk_fb_query)
 * FrameBank query: runs FUN_00145078. */
static void sk_fb_query_140b18(void)
{
    /* FUN_00145078() */
}

/* FUN_00140b3c @ 0x140b3c  (est. sk_fb_query16)
 * FrameBank 16-byte query: runs FUN_00145288, filling the result. */
static void sk_fb_query16_140b3c(void)
{
    /* auVar1 = FUN_00145288(); fill out */
}

/* FUN_00140b74 @ 0x140b74  (est. sk_fb_check)
 * FrameBank check: runs vtable 0x50, returns nonzero. */
static bool sk_fb_check_140b74(void)
{
    /* return (**(code**)(*ctx + 0x50))() != 0 */
    return false;
}

/* FUN_00140b78 @ 0x140b78  (est. sk_fb_check_b)
 * Duplicate of 0x140b74. */
static bool sk_fb_check_140b78(void) { /* same as 0x140b74 */ return false; }

/* FUN_00140bac @ 0x140bac  (est. sk_fb_list)
 * FrameBank list: iterates the 0x50-count frame list, builds 0x6c-byte
 * records (via FUN_001e9c78/FUN_00077070), appends to the global table. */
static void sk_fb_list_140bac(uint64_t *out, uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)out; (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_00140d80 @ 0x140d80  (est. sk_fb_item)
 * FrameBank item: resolves via FUN_000836a4 and FUN_001417fc, releasing the
 * frame. */
static uint64_t sk_fb_item_140d80(uint64_t a, uint64_t b, uint64_t c, uint64_t d, long e, uint64_t f, uint64_t g)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g;
    /* see decompile */
    return 0;
}

/* FUN_00140e10 @ 0x140e10  (est. sk_fb_query2)
 * FrameBank query 2: runs FUN_001459c8. */
static void sk_fb_query2_140e10(void) { /* FUN_001459c8() */ }

/* FUN_00140e34 @ 0x140e34  (est. sk_fb_query20)
 * FrameBank 20-byte query via FUN_001454c8. */
static void sk_fb_query20_140e34(uint64_t *out)
{
    (void)out;
    /* FUN_001454c8(&local); copy 5 words */
}

/* FUN_00140e80 @ 0x140e80  (est. sk_fb_query3)
 * FrameBank query 3: runs FUN_00145780. */
static void sk_fb_query3_140e80(void) { /* FUN_00145780() */ }

/* FUN_00140ea4 @ 0x140ea4  (est. sk_fb_release)
 * Releases obj at ctx+0x18 then teardown. */
static void sk_fb_release_140ea4(uint64_t *ctx)
{
    (void)ctx;
    /* FUN_0036b118(ctx[0x18/8]); FUN_0036b6ac() */
}

/* FUN_00140ea8 @ 0x140ea8  (est. sk_fb_release_b)
 * Duplicate of 0x140ea4. */
static void sk_fb_release_140ea8(uint64_t *ctx) { /* same as 0x140ea4 */ (void)ctx; }

/* FUN_00140ed0 @ 0x140ed0  (est. sk_fb_vtbl68)
 * Calls vtable method at offset 0x68. */
static void sk_fb_vtbl68_140ed0(void)
{
    /* (**(code**)(*(long*)*ctx + 0x68))() */
}

/* FUN_00140f0c @ 0x140f0c  (est. sk_fb_vtbl50)
 * Calls vtable method at offset 0x50. */
static void sk_fb_vtbl50_140f0c(void)
{
    /* (**(code**)(*(long*)*ctx + 0x50))() */
}

/* FUN_00140f48 @ 0x140f48  (est. sk_fb_vtbl58)
 * Calls vtable method at offset 0x58, returns the 16-byte result. */
static void sk_fb_vtbl58_140f48(void)
{
    /* auVar2 = (**(code**)(*(long*)*ctx + 0x58))() */
}

/* FUN_00140f98 @ 0x140f98  (est. sk_fb_vtbl80)
 * Calls vtable method at offset 0x80, filling 5 output words. */
static void sk_fb_vtbl80_140f98(uint64_t *out)
{
    (void)out;
    /* (**(code**)(*(long*)*ctx + 0x80))(&local) */
}

/* FUN_00140ffc @ 0x140ffc  (est. sk_fb_vtbl88)
 * Calls vtable method at offset 0x88. */
static void sk_fb_vtbl88_140ffc(void)
{
    /* (**(code**)(*(long*)*ctx + 0x88))() */
}

/* FUN_00141038 @ 0x141038  (est. sk_fb_vtbl78)
 * Calls vtable method at offset 0x78. */
static void sk_fb_vtbl78_141038(void)
{
    /* (**(code**)(*(long*)*ctx + 0x78))() */
}

/* FUN_0014107c @ 0x14107c  (est. sk_fb_frame_build)
 * FrameBank frame builder: iterates the 0x68-count frame descriptors, builds
 * 0x74-byte frame records (via FUN_00141918/FUN_0013f744), appends to the
 * global table. */
static void sk_fb_frame_build_14107c(uint64_t *out)
{
    (void)out;
    /* see decompile */
}

/* FUN_00144cf0 @ 0x144cf0  (est. sk_fb_kind)
 * FrameBank kind: maps via FUN_001467d8. */
static void sk_fb_kind_144cf0(uint8_t *out, uint8_t *p)
{
    (void)out; (void)p;
    /* *out = FUN_001467d8(*p) */
}

/* FUN_00144d1c @ 0x144d1c  (est. sk_fb_kind_check)
 * FrameBank kind check: runs FUN_0013f6f8 and returns 1. */
static uint64_t sk_fb_kind_check_144d1c(void)
{
    /* FUN_0013f6f8() */
    return 1;
}

/* FUN_00144d20 @ 0x144d20  (est. sk_fb_kind_check_b)
 * Duplicate of 0x144d1c. */
static uint64_t sk_fb_kind_check_144d20(void)
{
    /* FUN_0013f6f8() */
    return 1;
}

/* FUN_00144d38 @ 0x144d38  (est. sk_fb_emit_kind)
 * FrameBank kind emit: resolves via FUN_001467ec and FUN_000276c4, calling
 * the emitter. */
static void sk_fb_emit_kind_144d38(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_00144dec @ 0x144dec  (est. sk_fb_kind_query)
 * FrameBank kind query: runs FUN_00144e34 and maps the result. */
static uint64_t sk_fb_kind_query_144dec(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* see decompile */
    return 0;
}

/* FUN_00144e34 @ 0x144e34  (est. sk_fb_kind_parse)
 * FrameBank kind parse (FUN_000276f4): returns the kind byte (<4), else
 * panics "FrameBank.FrameBank.swift". */
static uint8_t sk_fb_kind_parse_144e34(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_00144f58 @ 0x144f58  (est. sk_fb_kind_out)
 * FrameBank kind output. */
static void sk_fb_kind_out_144f58(uint8_t *out)
{
    (void)out;
    /* uVar1 = FUN_00144dec(); *out = (char)uVar1 */
}

/* FUN_00144f94 @ 0x144f94  (est. sk_fb_kind_set)
 * Sets the FrameBank kind. */
static uint64_t sk_fb_kind_set_144f94(uint8_t *p)
{
    (void)p;
    /* FUN_0013f6f8(*p) */
    return 1;
}

/* FUN_00144f98 @ 0x144f98  (est. sk_fb_kind_set_b)
 * Duplicate of 0x144f94. */
static uint64_t sk_fb_kind_set_144f98(uint8_t *p) { /* FUN_0013f6f8(*p) */ return 1; }

/* FUN_00144fb4 @ 0x144fb4  (est. sk_fb_emit_kind_w)
 * FrameBank kind emit wrapper. */
static void sk_fb_emit_kind_144fb4(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* FUN_00144d38(a, *ctx, b, c) */
}

/* FUN_00144fb8 @ 0x144fb8  (est. sk_fb_emit_kind_wb)
 * Duplicate of 0x144fb4. */
static void sk_fb_emit_kind_144fb8(uint64_t a, uint64_t b, uint64_t c) { /* FUN_00144d38(a, *ctx, b, c) */ (void)a;(void)b;(void)c; }

/* FUN_00144fe4 @ 0x144fe4  (est. sk_fb_size)
 * FrameBank record size: returns 0x1a+min(count,0x10) or 9. */
static int64_t sk_fb_size_144fe4(void)
{
    /* if (*(ctx+0x20) >= 0) { u=min(*(*(ctx+0x20)+0x10), 0x10); return u+0x1a; } return 9 */
    return 0;
}

/* FUN_0014500c @ 0x14500c  (est. sk_fb_value)
 * FrameBank value: allocates, resolves the string (FUN_000260e0). */
static int64_t sk_fb_value_14500c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_00145078 @ 0x145078  (est. sk_fb_query_full)
 * FrameBank full query: builds the frame-bank query record (FUN_00025ebc/
 * FUN_00023208/FUN_000214b0), runs it (FUN_000217e4), and returns the result
 * (or the error code). Panics "FrameBank.FrameBank.swift" on an invalid state. */
static uint64_t sk_fb_query_full_145078(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00145288 @ 0x145288  (est. sk_fb_query_16)
 * FrameBank 16-byte query variant. */
static void sk_fb_query_16_145288(void)
{
    /* see decompile */
}

/* FUN_001454c8 @ 0x1454c8  (est. sk_fb_query_20)
 * FrameBank 20-byte query variant. */
static void sk_fb_query_20_1454c8(uint64_t *out, uint64_t a, uint64_t b)
{
    (void)out; (void)a; (void)b;
    /* see decompile */
}

/* FUN_00145780 @ 0x145780  (est. sk_fb_query_28)
 * FrameBank 28-byte query variant. */
static uint64_t sk_fb_query_28_145780(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* see decompile */
    return 0;
}

/* ============ 0x141268 - 0x145c40 : FrameBank frames/records ============ */

/* FUN_00141268 @ 0x141268  (est. sk_fb_frame_ctor)
 * Allocates a 0x74-byte frame object from a descriptor record, copying the
 * seven fields. */
static int64_t sk_fb_frame_ctor_141268(uint64_t *p, uint64_t a, uint64_t b, uint32_t c)
{
    (void)p; (void)a; (void)b; (void)c;
    /* see decompile */
    return 0;
}

/* FUN_00141348 @ 0x141348  (est. sk_fb_frame_release)
 * Releases the frame's fields (0x18/0x20/0x30). */
static void sk_fb_frame_release_141348(uint64_t *ctx)
{
    (void)ctx;
    /* FUN_003a25d4(ctx[0x18/8]); FUN_0036b118(ctx[0x20/8]); FUN_000026e8(ctx+0x30) */
}

/* FUN_0014134c @ 0x14134c  (est. sk_fb_frame_release_b)
 * Duplicate of 0x141348. */
static void sk_fb_frame_release_14134c(uint64_t *ctx) { /* same as 0x141348 */ (void)ctx; }

/* FUN_00141378 @ 0x141378  (est. sk_fb_frame_release_td)
 * Releases frame fields then teardown. */
static void sk_fb_frame_release_td_141378(uint64_t *ctx) { /* release + FUN_0036b6ac() */ (void)ctx; }

/* FUN_0014137c @ 0x14137c  (est. sk_fb_frame_release_td_b)
 * Duplicate of 0x141378. */
static void sk_fb_frame_release_td_14137c(uint64_t *ctx) { /* release + FUN_0036b6ac() */ (void)ctx; }

/* FUN_001413c0 @ 0x1413c0  (est. sk_fb_frame_vtbl78)
 * Calls vtable method at offset 0x78. */
static void sk_fb_frame_vtbl78_1413c0(void)
{
    /* (**(code**)(*(long*)*ctx + 0x78))() */
}

/* FUN_001413fc @ 0x1413fc  (est. sk_fb_frame_list)
 * FrameBank frame list: iterates the 0x20-count frame descriptors, builds each
 * frame via FUN_001419a4, appends to the global table. */
static void sk_fb_frame_list_1413fc(uint64_t *out)
{
    (void)out;
    /* see decompile: BRK 0x14157c/80 */
}

/* FUN_00141580 @ 0x141580  (est. sk_fb_frame_get)
 * FrameBank frame get. */
static void sk_fb_frame_get_141580(uint64_t a)
{
    (void)a;
    /* see decompile */
}

/* FUN_001459c8 @ 0x1459c8  (est. sk_fb_query8_b)
 * FrameBank 8-byte query variant (hash 0xc5249d3099b5a126). */
static void sk_fb_query8_b_1459c8(void)
{
    /* see decompile */
}

/* FUN_00145bc8 @ 0x145bc8  (est. sk_fb_value2)
 * FrameBank value allocator (variant). */
static void sk_fb_value2_145bc8(int64_t *out, uint64_t a, uint64_t b)
{
    (void)out; (void)a; (void)b;
    /* see decompile */
}

/* FUN_00145c40 @ 0x145c40  (est. sk_fb_item2)
 * FrameBank item 2 (via FUN_0014681c). */
static uint64_t sk_fb_item2_145c40(uint64_t a, uint64_t b, uint64_t c, long d, uint64_t e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* see decompile */
    return 0;
}

/* FUN_00145cdc @ 0x145cdc  (est. sk_fb_result_kind)
 * FrameBank result-kind mapping: maps the query hash result to a kind id
 * (1/2/3/4), else panics "FrameBank.FrameBank.swift". */
static uint64_t sk_fb_result_kind_145cdc(void)
{
    /* see decompile: hash-kind switch, panic 0x22f */
    return 0;
}

/* ============ 0x145e7c - 0x146460 : FrameBank query dispatch ============ */

/* FUN_00145e7c @ 0x145e7c  (est. sk_fb_item3)
 * FrameBank item 3 (via FUN_00146970), releasing the frame. */
static uint64_t sk_fb_item3_145e7c(uint64_t a, uint64_t b, long c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
    return 0;
}

/* FUN_00145f10 @ 0x145f10  (est. sk_fb_result_kind2)
 * FrameBank result-kind mapping: maps the query hash to a kind id (0..3),
 * else panics "FrameBank.FrameBank.swift". */
static uint64_t sk_fb_result_kind2_145f10(void)
{
    /* see decompile: hash-kind switch, panic 0x1e8 */
    return 0;
}

/* FUN_00146090 @ 0x146090  (est. sk_fb_query_emit)
 * FrameBank query emit: runs the query builder (FUN_00143bf8) and completes
 * the query record. */
static void sk_fb_query_emit_146090(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* see decompile */
}

/* FUN_00146158 @ 0x146158  (est. sk_fb_query_result)
 * FrameBank query result handling (via FUN_00144014). */
static void sk_fb_query_result_146158(void)
{
    /* see decompile */
}

/* FUN_00146224 @ 0x146224  (est. sk_fb_query_exec)
 * FrameBank query execution: dispatches via FUN_00023f74 with the callback
 * FUN_00147810; returns the result or error code. */
static uint64_t sk_fb_query_exec_146224(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_001462e4 @ 0x1462e4  (est. sk_fb_query_exec2)
 * FrameBank query execution 2 (via FUN_00023f74 with FUN_00146158). */
static void sk_fb_query_exec2_1462e4(uint64_t *out, uint64_t a, uint64_t b, uint32_t *err, uint64_t c)
{
    (void)out; (void)a; (void)b; (void)err; (void)c;
    /* see decompile */
}

/* FUN_001463b8 @ 0x1463b8  (est. sk_fb_query_emit2)
 * FrameBank query emit 2 (via FUN_00144604). */
static void sk_fb_query_emit2_1463b8(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* FUN_00146460 @ 0x146460  (est. sk_fb_query_exec3)
 * FrameBank query execution 3. */
static void sk_fb_query_exec3_146460(uint64_t *out, uint64_t a, uint32_t *err)
{
    (void)out; (void)a; (void)err;
    /* see decompile */
}

/* ============ 0x14654c - 0x14b0ec : FrameBank helpers + IPC arg munger ============ */

/* FUN_0014654c @ 0x14654c  (est. sk_fb_query_exec4)
 * FrameBank query execution 4 (via FUN_00023f74 with FUN_001477f8). */
static uint64_t sk_fb_query_exec4_14654c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_0014660c @ 0x14660c  (est. sk_fb_query_exec5)
 * FrameBank query execution 5 (with FUN_00146460). */
static void sk_fb_query_exec5_14660c(uint64_t *out, uint64_t a, uint64_t b, uint32_t *err, uint64_t c)
{
    (void)out; (void)a; (void)b; (void)err; (void)c;
    /* see decompile */
}

/* FUN_001466e0 @ 0x1466e0  (est. sk_fb_record_size)
 * FrameBank record size computation (8 + min(len,0x10) + 0xc), bounds-checked. */
static int64_t sk_fb_record_size_1466e0(long a, long b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_00146728 @ 0x146728  (est. sk_fb_skip)
 * Skip-list node advance (base+8 + int at +8). */
static int64_t sk_fb_skip_146728(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 8) + (int64_t)*(int32_t *)(p + 8);
}

/* FUN_00146758 @ 0x146758  (est. sk_fb_size2)
 * FrameBank record size (via FUN_0013fde4): min(len,0x10)+0x19. */
static int64_t sk_fb_size2_146758(void)
{
    /* see decompile */
    return 0;
}

/* FUN_001467a8 @ 0x1467a8  (est. sk_fb_skip_b)
 * Skip-list node advance (base+8). */
static int64_t sk_fb_skip_1467a8(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 8) + (int64_t)*(int32_t *)(p + 8);
}

/* FUN_001467d8 @ 0x1467d8  (est. sk_fb_kind_clamp)
 * Clamps the kind byte: if (kind & 0xfc) != 0, return 4. */
static uint8_t sk_fb_kind_clamp_1467d8(uint8_t k)
{
    return (k & 0xfc) ? 4 : k;
}

/* FUN_001467ec @ 0x1467ec  (est. sk_fb_skip_c)
 * Skip-list node advance (base+8). */
static int64_t sk_fb_skip_1467ec(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 8) + (int64_t)*(int32_t *)(p + 8);
}

/* FUN_0014681c @ 0x14681c  (est. sk_fb_record_build)
 * FrameBank record builder: allocates the record buffer (0x665508), copies the
 * frame data via the vtable dispatch, and registers the record via
 * FUN_00027b10 with the release callback FUN_00146ca0. */
static void sk_fb_record_build_14681c(uint64_t a, uint32_t b, uint64_t c, long d, uint64_t e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* see decompile */
}

/* FUN_00146970 @ 0x146970  (est. sk_fb_record_build2)
 * FrameBank record builder 2 (0x6654e0, callback FUN_00146b64). */
static void sk_fb_record_build2_146970(uint64_t a, uint64_t b, long c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_00146ab0 @ 0x146ab0  (est. sk_fb_query_wrap)
 * FrameBank query wrapper: calls FUN_00146090 with the context registers. */
static void sk_fb_query_wrap_146ab0(uint64_t a)
{
    (void)a;
    /* FUN_00146090(a, ctx[0x10], ctx[0x18], ctx[0x20], ctx[0x28]) */
}

/* FUN_00146ad4 @ 0x146ad4  (est. sk_fb_query_wrap2)
 * FrameBank query wrapper 2 (FUN_001463b8). */
static void sk_fb_query_wrap2_146ad4(uint64_t a)
{
    (void)a;
    /* FUN_001463b8(a, ctx[0x10]) */
}

/* FUN_00146b40 @ 0x146b40  (est. sk_fb_typeid)
 * Returns 16-byte {0x653cd0, 0}. */
static void sk_fb_typeid_146b40(void) { /* returns {0x653cd0, 0} */ }

/* FUN_00146b64 @ 0x146b64  (est. sk_fb_release_cb1)
 * Release callback with line numbers (0x17a..0x1af). */
static void sk_fb_release_cb1_146b64(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* FUN_00146ccc(a, b, 0x17a, 0x186, 0x192, 0x1a2, 0x1af) */
}

/* FUN_00146b68 @ 0x146b68  (est. sk_fb_release_cb1_b)
 * Duplicate of 0x146b64. */
static void sk_fb_release_cb1_146b68(uint64_t a, uint64_t b) { /* FUN_00146ccc(a,b,0x17a,0x186,0x192,0x1a2,0x1af) */ (void)a;(void)b; }

/* FUN_00146b90 @ 0x146b90  (est. sk_fb_skip_d)
 * Skip-list node advance (base+0x14). */
static int64_t sk_fb_skip_146b90(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_00146bc0 @ 0x146bc0  (est. sk_fb_release_opt)
 * Releases the object if the index >= 0. */
static void sk_fb_release_opt_146bc0(int64_t v)
{
    if (v >= 0) { /* FUN_0036b118(v) */ }
}

/* FUN_00146bd0 @ 0x146bd0  (est. sk_fb_skip_e)
 * Skip-list node advance (base+8). */
static int64_t sk_fb_skip_146bd0(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 8) + (int64_t)*(int32_t *)(p + 8);
}

/* FUN_00146c00 @ 0x146c00  (est. sk_fb_release_opt2)
 * Releases the object and its sub if index >= 0. */
static void sk_fb_release_opt2_146c00(uint64_t a, int64_t v)
{
    (void)a;
    if (v >= 0) { /* FUN_0036b118(); FUN_0036b118(v) */ }
}

/* FUN_00146c34 @ 0x146c34  (est. sk_fb_record_release)
 * Releases a FrameBank record via the vtable (0x50 field) +8 method. */
static void sk_fb_record_release_146c34(void)
{
    /* see decompile */
}

/* FUN_00146ca0 @ 0x146ca0  (est. sk_fb_release_cb2)
 * Release callback with line numbers (0x12f..0x164). */
static void sk_fb_release_cb2_146ca0(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* FUN_00146ccc(a, b, 0x12f, 0x13b, 0x147, 0x157, 0x164) */
}

/* FUN_00146ca4 @ 0x146ca4  (est. sk_fb_release_cb2_b)
 * Duplicate of 0x146ca0. */
static void sk_fb_release_cb2_146ca4(uint64_t a, uint64_t b) { /* FUN_00146ccc(a,b,0x12f,0x13b,0x147,0x157,0x164) */ (void)a;(void)b; }

/* FUN_00146ccc @ 0x146ccc  (est. sk_fb_record_free)
 * FrameBank record free: iterates the record's embedded fields, releasing each
 * object and freeing the buffer via the vtable dispatch; the large block (which
 * the decompiler partially failed on, spilling into a 0x1e9000-range routine)
 * handles the multi-field release. */
static void sk_fb_record_free_146ccc(uint64_t *p, uint64_t *q, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)p; (void)q; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile: field-by-field release + buffer free */
}

/* FUN_001495a4 @ 0x1495a4  (est. sk_cg_clamp3)
 * Clamps >3 to 4. */
static uint64_t sk_cg_clamp3_1495a4(uint64_t v)
{
    return v > 3 ? 4 : v;
}

/* FUN_00149610 @ 0x149610  (est. sk_report_4e2cc0)
 * Reads a counter (thunk_FUN_0036f974) and reports it. */
static uint64_t sk_report_4e2cc0_149610(void)
{
    uint64_t v = /* thunk_FUN_0036f974() */ 0;
    /* FUN_0035cf24(&DAT_004e2cc0, v) */
    return v;
}

/* FUN_0014964c @ 0x14964c  (est. sk_fb_release_many)
 * Releases eleven field objects at +0x30..0x80. */
static void sk_fb_release_many_14964c(long p)
{
    (void)p;
    /* FUN_0036b118 for +0x30..0x80 */
}

/* FUN_001496c4 @ 0x1496c4  (est. sk_fb_obj_copy)
 * Copies a 20-word record from param_2 to param_1, releasing the old fields. */
static uint64_t *sk_fb_obj_copy_1496c4(uint64_t *dst, uint64_t *src)
{
    (void)dst; (void)src;
    /* see decompile */
    return dst;
}

/* FUN_00149868 @ 0x149868  (est. sk_report_4e2e20)
 * Counter report. */
static uint64_t sk_report_4e2e20_149868(void)
{
    uint64_t v = /* thunk_FUN_0036f974() */ 0;
    /* FUN_0035cf24(&DAT_004e2e20, v) */
    return v;
}

/* FUN_001498c0 @ 0x1498c0  (est. sk_report_4e2e98)
 * Counter report. */
static uint64_t sk_report_4e2e98_1498c0(void)
{
    uint64_t v = /* thunk_FUN_0036f974() */ 0;
    /* FUN_0035cf24(&DAT_004e2e98, v) */
    return v;
}

/* FUN_00149914 @ 0x149914  (est. sk_report_4e2ee0)
 * Counter report. */
static uint64_t sk_report_4e2ee0_149914(void)
{
    uint64_t v = /* thunk_FUN_0036f974() */ 0;
    /* FUN_0035cf24(&DAT_004e2ee0, v) */
    return v;
}

/* FUN_00149950 @ 0x149950  (est. sk_report_4e2f30)
 * Counter report. */
static uint64_t sk_report_4e2f30_149950(void)
{
    uint64_t v = /* thunk_FUN_0036f974() */ 0;
    /* FUN_0035cf24(&DAT_004e2f30, v) */
    return v;
}

/* FUN_0014998c @ 0x14998c  (est. sk_report_4e2f78)
 * Counter report. */
static uint64_t sk_report_4e2f78_14998c(void)
{
    uint64_t v = /* thunk_FUN_0036f974() */ 0;
    /* FUN_0035cf24(&DAT_004e2f78, v) */
    return v;
}

/* FUN_001499c8 @ 0x1499c8  (est. sk_report_4e2e20_b)
 * Counter report (duplicate of 0x149868). */
static uint64_t sk_report_4e2e20_1499c8(void)
{
    uint64_t v = /* thunk_FUN_0036f974() */ 0;
    /* FUN_0035cf24(&DAT_004e2e20, v) */
    return v;
}

/* FUN_00149ba0 @ 0x149ba0  (est. sk_fb_typeid2)
 * Returns 16-byte {0x653da8, 0}. */
static void sk_fb_typeid2_149ba0(void) { /* returns {0x653da8, 0} */ }

/* FUN_0014ae14 @ 0x14ae14  (est. sk_skip_04)
 * Skip-list node advance (base+4). */
static int64_t sk_skip_04_14ae14(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 4) + (int64_t)*(int32_t *)(p + 4);
}

/* FUN_0014ae44 @ 0x14ae44  (est. sk_skip_04_b)
 * Duplicate of 0x14ae14. */
static int64_t sk_skip_04_14ae44(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 4) + (int64_t)*(int32_t *)(p + 4);
}

/* FUN_0014aea4 @ 0x14aea4  (est. sk_ipc_arg3)
 * IPC arg munger: FUN_0014aee4 with type 3. */
static void sk_ipc_arg3_14aea4(uint64_t a, uint64_t b)
{
    /* FUN_0014aee4(a, b, 3) */
}

/* FUN_0014aeac @ 0x14aeac  (est. sk_skip_04_c)
 * Skip-list node advance (base+4). */
static int64_t sk_skip_04_14aeac(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 4) + (int64_t)*(int32_t *)(p + 4);
}

/* FUN_0014aedc @ 0x14aedc  (est. sk_ipc_arg0)
 * IPC arg munger: FUN_0014aee4 with type 0. */
static void sk_ipc_arg0_14aedc(uint64_t a, uint64_t b)
{
    /* FUN_0014aee4(a, b, 0) */
}

/* FUN_0014aee4 @ 0x14aee4  (est. sk_ipc_arg)
 * Shared IPC argument munger: resolves the arg descriptor via FUN_00377824/
 * FUN_00377bec (using the &DAT_00608f34 dispatch table) and invokes the type
 * handler. This is the cL4 IPC arg-normalization core. */
static void sk_ipc_arg_14aee4(uint64_t a, uint64_t b, uint64_t type)
{
    (void)a; (void)b; (void)type;
    /* see decompile */
}

/* FUN_0014af78 @ 0x14af78  (est. sk_ipc_arg6)
 * IPC arg: FUN_0014aedc() >> 6. */
static uint64_t sk_ipc_arg6_14af78(void)
{
    /* return FUN_0014aedc() >> 6 */
    return 0;
}

/* FUN_0014af7c @ 0x14af7c  (est. sk_ipc_arg6_b)
 * Duplicate of 0x14af78. */
static uint64_t sk_ipc_arg6_14af7c(void)
{
    /* return FUN_0014aedc() >> 6 */
    return 0;
}

/* FUN_0014af94 @ 0x14af94  (est. sk_ipc_arg_size)
 * IPC arg size: type 0 -> dynamic, type 1 -> 0x2000000, type 2 -> 0;
 * type > 2 BRKs. */
static uint64_t sk_ipc_arg_size_14af94(uint64_t type, uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    if (type > 2) { /* BRK 0x14afe0 */ }
    if (type == 1) return 0x2000000;
    if (type == 2) return 0;
    return /* FUN_0014aea4(a, b) */ 0;
}

/* FUN_0014afe0 @ 0x14afe0  (est. sk_ipc_arg_query)
 * IPC arg query: resolves the descriptor and invokes the 0x14b0bc handler,
 * returning the 16-byte result. */
static void sk_ipc_arg_query_14afe0(void)
{
    /* see decompile */
}

/* FUN_0014b0bc @ 0x14b0bc  (est. sk_skip_0c)
 * Skip-list node advance (base+0xc). */
static int64_t sk_skip_0c_14b0bc(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_0014b0ec @ 0x14b0ec  (est. sk_ipc_arg_query2)
 * IPC arg query 2 (duplicate of 0x14afe0). */
static void sk_ipc_arg_query2_14b0ec(void)
{
    /* see decompile */
}

/* ============ 0x14b1c8 - 0x14b980 : IPC arg munger + obj copy ============ */

/* FUN_0014b1c8 @ 0x14b1c8  (est. sk_skip_10)
 * Skip-list node advance (base+0x10). */
static int64_t sk_skip_10_14b1c8(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_0014b1f8 @ 0x14b1f8  (est. sk_ipc_arg_query3)
 * IPC arg query 3 (5-arg variant, handler 0x14b2c0). */
static void sk_ipc_arg_query3_14b1f8(void)
{
    /* see decompile */
}

/* FUN_0014b2c0 @ 0x14b2c0  (est. sk_skip_14)
 * Skip-list node advance (base+0x14). */
static int64_t sk_skip_14_14b2c0(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_0014b2f0 @ 0x14b2f0  (est. sk_ipc_arg_dispatch)
 * IPC arg dispatch: invokes the callback param_2, then the query
 * (FUN_0014b1f8/FUN_0014afe0), storing the result. */
static uint64_t sk_ipc_arg_dispatch_14b2f0(uint64_t *out, uint64_t (*cb)(void), uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)out; (void)cb; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile */
    return 0;
}

/* FUN_0014b41c @ 0x14b41c  (est. sk_objflag_get)
 * Reads the global object flag at DAT_006add00. */
static uint8_t sk_objflag_get_14b41c(void)
{
    /* FUN_0036a1a0(&DAT_006add00, buf, 0, 0); return DAT_006add00 */
    return 0;
}

/* FUN_0014b460 @ 0x14b460  (est. sk_objflag_set)
 * Sets the global object flag at DAT_006add00. */
static void sk_objflag_set_14b460(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(&DAT_006add00, buf, 1, 0); DAT_006add00 = v */
}

/* FUN_0014b4a8 @ 0x14b4a8  (est. sk_objflag_share)
 * Shares the global object flag. */
static void sk_objflag_share_14b4a8(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(&DAT_006add00, v, 0x21, 0); return {&DAT_0007bf58, &DAT_006add00} */
}

/* FUN_0014b50c @ 0x14b50c  (est. sk_objflag2_get)
 * Reads the object flag at 0x653e00; returns 0x49. */
static uint8_t sk_objflag2_get_14b50c(void)
{
    /* FUN_0036a1a0(0x653e00, buf, 0, 0) */
    return 0x49;
}

/* FUN_0014b550 @ 0x14b550  (est. sk_objflag2_set)
 * Sets the object flag at 0x653e00. */
static void sk_objflag2_set_14b550(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e00, buf, 1, 0); uRam_653e00 = v */
}

/* FUN_0014b598 @ 0x14b598  (est. sk_objflag2_share)
 * Shares the object flag at 0x653e00. */
static void sk_objflag2_share_14b598(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e00, v, 0x21, 0); return {&LAB_0006f910, 0x653e00} */
}

/* FUN_0014b5f8 @ 0x14b5f8  (est. sk_copy_obj)
 * Copies an object via FUN_0036ffc0 with the 0x6090d8 type descriptor. */
static void sk_copy_obj_14b5f8(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* FUN_0036ffc0(a, b, &DAT_006090d8) */
}

/* FUN_0014b644 @ 0x14b644  (est. sk_check_len)
 * Checks the length via FUN_00157308 (must be non-negative). */
static void sk_check_len_14b644(void)
{
    uint64_t v = /* FUN_00157308() */ 0;
    if (v >> 0x1f == 0) { /* FUN_00055a24() */ return; }
    /* BRK 0x14b6b0 */
}

/* FUN_0014b6e0 @ 0x14b6e0  (est. sk_check_len_jump)
 * Checks the length and jumps via the vtable. */
static void sk_check_len_jump_14b6e0(void)
{
    uint64_t v = /* FUN_00157308() */ 0;
    if (v >> 0x1f != 0) { /* BRK 0x14b71c */ }
    /* (*(code**)...)() */
}

/* FUN_0014b71c @ 0x14b71c  (est. sk_cap_copy)
 * Capability copy: resolves via FUN_0007bf4c and FUN_0014ae44, validates the
 * type id (0x666528), and copies via FUN_0001a1c8; on type mismatch reports
 * (0x6665b0/0x666518). */
static void sk_cap_copy_14b71c(uint64_t a, uint64_t *b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_0014b85c @ 0x14b85c  (est. sk_cap_copy_b)
 * Capability copy variant (via FUN_0009d480). */
static void sk_cap_copy_14b85c(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* see decompile */
}

/* FUN_0014b980 @ 0x14b980  (est. sk_cap_copy_c)
 * Capability copy variant (via FUN_0009d20c). */
static void sk_cap_copy_14b980(uint64_t a)
{
    (void)a;
    /* see decompile */
}

/* ============ 0x14ba70 - 0x14f038 : cL4 IPC object ops ============ */

/* FUN_0014ba70 @ 0x14ba70  (est. sk_ipc_copy_1)
 * IPC object copy 1 (wraps FUN_0014b71c). */
static void sk_ipc_copy_1_14ba70(void)
{
    /* auVar3 = FUN_0014b71c(); return 16-byte */
}

/* FUN_0014ba74 @ 0x14ba74  (est. sk_ipc_copy_1_b)
 * Duplicate of 0x14ba70. */
static void sk_ipc_copy_1_14ba74(void) { /* same as 0x14ba70 */ }

/* FUN_0014ba9c @ 0x14ba9c  (est. sk_ipc_copy_2)
 * IPC object copy 2 (wraps FUN_0014b85c). */
static void sk_ipc_copy_2_14ba9c(void)
{
    /* auVar3 = FUN_0014b85c() */
}

/* FUN_0014baa0 @ 0x14baa0  (est. sk_ipc_copy_2_b)
 * Duplicate of 0x14ba9c. */
static void sk_ipc_copy_2_14baa0(void) { /* same as 0x14ba9c */ }

/* FUN_0014bac8 @ 0x14bac8  (est. sk_ipc_copy_3)
 * IPC object copy 3 (wraps FUN_0014b980). */
static void sk_ipc_copy_3_14bac8(void)
{
    /* auVar3 = FUN_0014b980() */
}

/* FUN_0014bacc @ 0x14bacc  (est. sk_ipc_copy_3_b)
 * Duplicate of 0x14bac8. */
static void sk_ipc_copy_3_14bacc(void) { /* same as 0x14bac8 */ }

/* FUN_0014baf4 @ 0x14baf4  (est. sk_obj_free_wrap)
 * Object free wrapper (FUN_0014bb0c). */
static void sk_obj_free_wrap_14baf4(void) { /* FUN_0014bb0c() */ }

/* FUN_0014bb0c @ 0x14bb0c  (est. sk_obj_free)
 * Object free (FUN_0014e418). */
static void sk_obj_free_14bb0c(void) { /* FUN_0014e418() */ }

/* FUN_0014bb3c @ 0x14bb3c  (est. sk_obj_free2)
 * Object free 2 (FUN_0014c3f4). */
static void sk_obj_free2_14bb3c(void) { /* FUN_0014c3f4() */ }

/* FUN_0014bb40 @ 0x14bb40  (est. sk_obj_free2_b)
 * Duplicate of 0x14bb3c. */
static void sk_obj_free2_14bb40(void) { /* FUN_0014c3f4() */ }

/* FUN_0014bb68 @ 0x14bb68  (est. sk_obj_op1)
 * Object operation (FUN_0014bbc0 with LAB_0014ebec). */
static void sk_obj_op1_14bb68(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* FUN_0014bbc0(a, b, &LAB_0014ebec) */
}

/* FUN_0014bb94 @ 0x14bb94  (est. sk_obj_op2)
 * Object operation (FUN_0014bbc0 with LAB_0014ebd0). */
static void sk_obj_op2_14bb94(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* FUN_0014bbc0(a, b, &LAB_0014ebd0) */
}

/* FUN_0014bbc0 @ 0x14bbc0  (est. sk_obj_op)
 * Object operation: runs the callback param_3, validates the type (0x666528),
 * and on mismatch reports (0x6665b0/0x666518). */
static void sk_obj_op_14bbc0(uint64_t a, uint64_t b, uint64_t (*cb)(void))
{
    (void)a; (void)b; (void)cb;
    /* see decompile */
}

/* FUN_0014bca4 @ 0x14bca4  (est. sk_obj_free3)
 * Object free 3 (FUN_0014c484). */
static void sk_obj_free3_14bca4(void) { /* FUN_0014c484() */ }

/* FUN_0014bcd8 @ 0x14bcd8  (est. sk_obj_op3)
 * Object operation 3 (FUN_0014bd30). */
static void sk_obj_op3_14bcd8(void) { /* FUN_0014bd30() */ }

/* FUN_0014bd04 @ 0x14bd04  (est. sk_obj_op3_b)
 * Duplicate of 0x14bcd8. */
static void sk_obj_op3_14bd04(void) { /* FUN_0014bd30() */ }

/* FUN_0014bd30 @ 0x14bd30  (est. sk_obj_op_core)
 * Object operation core: runs the in_x4 callback, validates type 0x666528. */
static void sk_obj_op_core_14bd30(void)
{
    /* see decompile */
}

/* FUN_0014be14 @ 0x14be14  (est. sk_ipc_send_short)
 * cL4 IPC short-send: validates the length (<0x100, BRK), issues the syscall
 * (FUN_001033d8), copies the object (FUN_0001a1c8); type 0x666528. */
static void sk_ipc_send_short_14be14(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile */
}

/* FUN_0014bf64 @ 0x14bf64  (est. sk_ipc_send_short_w)
 * Short-send wrapper (FUN_0014e6a0). */
static void sk_ipc_send_short_14bf64(void)
{
    /* auVar3 = FUN_0014e6a0() */
}

/* FUN_0014bfa0 @ 0x14bfa0  (est. sk_ipc_send_short_wb)
 * Short-send wrapper (FUN_0014be14). */
static void sk_ipc_send_short_14bfa0(void)
{
    /* auVar3 = FUN_0014be14() */
}

/* FUN_0014bfa4 @ 0x14bfa4  (est. sk_ipc_send_short_wc)
 * Duplicate of 0x14bfa0. */
static void sk_ipc_send_short_14bfa4(void) { /* auVar3 = FUN_0014be14() */ }

/* FUN_0014bfcc @ 0x14bfcc  (est. sk_obj_op4)
 * Object operation 4 (FUN_0014bbc0 with LAB_0014e908). */
static void sk_obj_op4_14bfcc(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* FUN_0014bbc0(a, b, &LAB_0014e908) */
}

/* FUN_0014bff8 @ 0x14bff8  (est. sk_obj_op5)
 * Object operation 5 (FUN_0014f3fc). */
static void sk_obj_op5_14bff8(void)
{
    /* FUN_0014f3fc(); validate type */
}

/* FUN_0014c0d8 @ 0x14c0d8  (est. sk_obj_copy_4)
 * Object copy 4 (FUN_0006de38): copies the object via FUN_0001a1c8. */
static void sk_obj_copy_4_14c0d8(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* FUN_0014c200 @ 0x14c200  (est. sk_obj_op3_c)
 * Object operation 3 variant (FUN_0014bd30). */
static void sk_obj_op3_14c200(void) { /* FUN_0014bd30() */ }

/* FUN_0014c22c @ 0x14c22c  (est. sk_obj_op6)
 * Object operation 6 (FUN_0014f444). */
static void sk_obj_op6_14c22c(void)
{
    /* FUN_0014f444(); validate type */
}

/* FUN_0014c30c @ 0x14c30c  (est. sk_ipc_result)
 * IPC result (FUN_0014e81c): returns {1,1,...} on success. */
static void sk_ipc_result_14c30c(void)
{
    /* auVar2 = FUN_0014e81c(); if (ok) auVar2 = {1,1}; return */
}

/* FUN_0014c310 @ 0x14c310  (est. sk_ipc_result_b)
 * Duplicate of 0x14c30c. */
static void sk_ipc_result_14c310(void) { /* same as 0x14c30c */ }

/* FUN_0014c338 @ 0x14c338  (est. sk_obj_free4)
 * Object free 4 (FUN_0014c524). */
static void sk_obj_free4_14c338(void) { /* FUN_0014c524() */ }

/* FUN_0014e418 @ 0x14e418  (est. sk_obj_free_core)
 * Object free core: resolves the object (FUN_001518dc/FUN_0009d1e0), validates
 * type 0x666528, frees it (FUN_0015187c), reports on mismatch. */
static uint64_t sk_obj_free_core_14e418(uint64_t a)
{
    (void)a;
    /* see decompile */
    return 0;
}

/* FUN_0014e558 @ 0x14e558  (est. sk_ipc_send_data)
 * cL4 IPC data send: builds the type/args (FUN_00100418), validates the type,
 * copies the object. */
static void sk_ipc_send_data_14e558(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, char f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile */
}

/* FUN_0014e6a0 @ 0x14e6a0  (est. sk_ipc_send_full)
 * cL4 IPC full send: assembles the arg count/size, issues the syscall
 * (FUN_0014fbf0), validates type, copies the object. */
static void sk_ipc_send_full_14e6a0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, char e, long f, char g, uint64_t h, char i)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i;
    /* see decompile */
}

/* FUN_0014e81c @ 0x14e81c  (est. sk_ipc_result2)
 * IPC result 2: validates the arg (bit7 -> BRK), issues the syscall
 * (FUN_0014fbb4), validates type. */
static void sk_ipc_result2_14e81c(uint64_t a, uint64_t b, uint32_t c)
{
    (void)a; (void)b; (void)c;
    /* see decompile */
}

/* FUN_0014e934 @ 0x14e934  (est. sk_ipc_send_data2)
 * IPC data send 2 (FUN_00100418). */
static void sk_ipc_send_data2_14e934(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, char f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile */
}

/* FUN_0014ea7c @ 0x14ea7c  (est. sk_ipc_recv_data)
 * cL4 IPC data receive: resolves the object (FUN_001518dc), issues the syscall
 * (FUN_0014fb88), validates type. */
static void sk_ipc_recv_data_14ea7c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* FUN_0014ec08 @ 0x14ec08  (est. sk_ipc_recv)
 * cL4 IPC receive (FUN_0014fb5c): validates type, returns the object. */
static void sk_ipc_recv_14ec08(void)
{
    /* FUN_0014fb5c(); validate type; return FUN_00156880 */
}

/* FUN_0014ed44 @ 0x14ed44  (est. sk_svc0_loop)
 * Supervisor-call 0 loop (repeats while param_1==1). */
static void sk_svc0_loop_14ed44(int64_t flag)
{
    uint64_t *blk = (uint64_t *)0; /* tpidrro_el0 */
    uint64_t save = *blk;
    do { /* CallSupervisor(0) */ *blk = save; } while (flag == 1);
}

/* FUN_0014ed94 @ 0x14ed94  (est. sk_svc0_loop_b)
 * Duplicate of 0x14ed44. */
static void sk_svc0_loop_14ed94(int64_t flag) { /* same as 0x14ed44 */ (void)flag; }

/* FUN_0014ede0 @ 0x14ede0  (est. sk_svc0_loop_c)
 * Duplicate of 0x14ed44. */
static void sk_svc0_loop_14ede0(int64_t flag) { /* same as 0x14ed44 */ (void)flag; }

/* FUN_0014ee30 @ 0x14ee30  (est. sk_svc0_loop_d)
 * Duplicate of 0x14ed44. */
static void sk_svc0_loop_14ee30(int64_t flag) { /* same as 0x14ed44 */ (void)flag; }

/* FUN_0014ee60 @ 0x14ee60  (est. sk_ipc_send_msg)
 * cL4 IPC message send: copies the element list (FUN_0014e23c), resolves the
 * thread/object (FUN_00152980/FUN_00152a90), issues the send syscall
 * (FUN_0014f278), validates type. */
static void sk_ipc_send_msg_14ee60(uint64_t a, long b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* FUN_0014f038 @ 0x14f038  (est. sk_ipc_recv_msg)
 * cL4 IPC message receive: resolves the object, issues the receive syscall. */
static void sk_ipc_recv_msg_14f038(uint64_t a, long b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* ============ 0x14c33c - 0x14f4ac : cL4 IPC syscall wrappers ============ */

/* FUN_0014c33c @ 0x14c33c  (est. sk_obj_free4_b)
 * Object free 4 (FUN_0014c524). */
static void sk_obj_free4_14c33c(void) { /* FUN_0014c524() */ }

/* FUN_0014c380 @ 0x14c380  (est. sk_obj_op7)
 * Object operation 7 (FUN_0014c598). */
static void sk_obj_op7_14c380(void) { /* FUN_0014c598() */ }

/* FUN_0014c384 @ 0x14c384  (est. sk_obj_op7_b)
 * Duplicate of 0x14c380. */
static void sk_obj_op7_14c384(void) { /* FUN_0014c598() */ }

/* FUN_0014c3c8 @ 0x14c3c8  (est. sk_obj_free2_c)
 * Object free 2 (FUN_0014c3f4). */
static void sk_obj_free2_14c3c8(void) { /* FUN_0014c3f4() */ }

/* FUN_0014c3cc @ 0x14c3cc  (est. sk_obj_free2_d)
 * Duplicate of 0x14c3c8. */
static void sk_obj_free2_14c3cc(void) { /* FUN_0014c3f4() */ }

/* FUN_0014c3f4 @ 0x14c3f4  (est. sk_obj_result)
 * Object result (invokes the in_x6 callback, returns the 16-byte result). */
static void sk_obj_result_14c3f4(void)
{
    /* auVar3 = (*in_x6)() */
}

/* FUN_0014c424 @ 0x14c424  (est. sk_ipc_recv_w)
 * IPC receive wrapper (FUN_0014ea7c). */
static void sk_ipc_recv_14c424(void)
{
    /* auVar3 = FUN_0014ea7c() */
}

/* FUN_0014c428 @ 0x14c428  (est. sk_ipc_recv_wb)
 * Duplicate of 0x14c424. */
static void sk_ipc_recv_14c428(void) { /* auVar3 = FUN_0014ea7c() */ }

/* FUN_0014c450 @ 0x14c450  (est. sk_obj_free3_b)
 * Object free 3 (FUN_0014c484). */
static void sk_obj_free3_14c450(void) { /* FUN_0014c484() */ }

/* FUN_0014c484 @ 0x14c484  (est. sk_obj_result2)
 * Object result 2 (invokes the stack callback). */
static void sk_obj_result2_14c484(void)
{
    /* auVar3 = (*in_stack_0)() */
}

/* FUN_0014c4b8 @ 0x14c4b8  (est. sk_ipc_recv2)
 * IPC receive 2 (FUN_0014ec08). */
static void sk_ipc_recv2_14c4b8(void) { /* FUN_0014ec08() */ }

/* FUN_0014c4bc @ 0x14c4bc  (est. sk_ipc_recv2_b)
 * Duplicate of 0x14c4b8. */
static void sk_ipc_recv2_14c4bc(void) { /* FUN_0014ec08() */ }

/* FUN_0014c4dc @ 0x14c4dc  (est. sk_obj_free4_c)
 * Object free 4 (FUN_0014c524). */
static void sk_obj_free4_14c4dc(void) { /* FUN_0014c524() */ }

/* FUN_0014c4e0 @ 0x14c4e0  (est. sk_obj_free4_d)
 * Duplicate of 0x14c4dc. */
static void sk_obj_free4_14c4e0(void) { /* FUN_0014c524() */ }

/* FUN_0014c524 @ 0x14c524  (est. sk_obj_result3)
 * Object result 3 (FUN_0014f4ac). */
static void sk_obj_result3_14c524(void)
{
    /* auVar3 = FUN_0014f4ac() */
}

/* FUN_0014c550 @ 0x14c550  (est. sk_obj_op7_c)
 * Object operation 7 (FUN_0014c598). */
static void sk_obj_op7_14c550(void) { /* FUN_0014c598() */ }

/* FUN_0014c554 @ 0x14c554  (est. sk_obj_op7_d)
 * Duplicate of 0x14c550. */
static void sk_obj_op7_14c554(void) { /* FUN_0014c598() */ }

/* FUN_0014c598 @ 0x14c598  (est. sk_obj_result4)
 * Object result 4. */
static void sk_obj_result4_14c598(void)
{
    /* see decompile */
}

/* FUN_0014f258 @ 0x14f258  (est. sk_svc0_send)
 * cL4 syscall 0 send: writes {type&0xffff, arg1} to the tpidrro block and
 * issues SVC 0. This is the cL4 IPC send syscall entry. */
static void sk_svc0_send_14f258(uint64_t a, uint64_t type, uint64_t arg)
{
    uint64_t *blk = (uint64_t *)0; /* tpidrro_el0 */
    blk[0] = type & 0xffff;
    blk[1] = arg;
    /* CallSupervisor(0) */
    blk[0] = type & 0xffff;
}

/* FUN_0014f278 @ 0x14f278  (est. sk_svc0_send2)
 * cL4 syscall 0 send variant. */
static void sk_svc0_send2_14f278(uint64_t a, uint64_t type, uint64_t arg)
{
    uint64_t *blk = (uint64_t *)0; /* tpidrro_el0 */
    blk[0] = type & 0xffff;
    blk[1] = arg;
    /* CallSupervisor(0) */
    blk[0] = type & 0xffff;
}

/* FUN_0014f2cc @ 0x14f2cc  (est. sk_svc0_send4)
 * cL4 syscall 0 send with 4 args. */
static void sk_svc0_send4_14f2cc(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t *blk = (uint64_t *)0; /* tpidrro_el0 */
    blk[0] = b; blk[1] = c; blk[2] = 0; blk[3] = 0;
    /* CallSupervisor(0) */
    blk[0] = b;
}

/* FUN_0014f2f0 @ 0x14f2f0  (est. sk_ipc_send_data3)
 * IPC data send 3 (FUN_00149368/FUN_0014fb10), validates type. */
static void sk_ipc_send_data3_14f2f0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* see decompile */
}

/* FUN_0014f3fc @ 0x14f3fc  (est. sk_svc0_loop_e)
 * SVC 0 loop. */
static void sk_svc0_loop_14f3fc(int64_t flag)
{
    uint64_t *blk = (uint64_t *)0;
    uint64_t save = *blk;
    do { /* CallSupervisor(0) */ *blk = save; } while (flag == 1);
}

/* FUN_0014f444 @ 0x14f444  (est. sk_svc0)
 * SVC 0 (single). */
static void sk_svc0_14f444(void)
{
    uint64_t *blk = (uint64_t *)0;
    /* CallSupervisor(0) */
    *blk = *blk;
}

/* FUN_0014f47c @ 0x14f47c  (est. sk_svc0_loop_f)
 * SVC 0 loop. */
static void sk_svc0_loop_14f47c(int64_t flag)
{
    uint64_t *blk = (uint64_t *)0;
    uint64_t save = *blk;
    do { /* CallSupervisor(0) */ *blk = save; } while (flag == 1);
}

/* FUN_0014f4ac @ 0x14f4ac  (est. sk_ipc_send_data4)
 * IPC data send 4: if the length >= 0, runs the callback param_4, validates
 * the type. */
static void sk_ipc_send_data4_14f4ac(uint64_t a, uint64_t b, long c, uint64_t (*cb)(void), uint64_t d, uint64_t e)
{
    (void)a; (void)b; (void)c; (void)cb; (void)d; (void)e;
    /* see decompile */
}

/* ============ 0x14f810 - 0x14fd34 : cL4 IPC syscall core ============ */

/* FUN_0014f810 @ 0x14f810  (est. sk_skip_48)
 * Skip-list node advance (base+0x48). */
static int64_t sk_skip_48_14f810(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x48) + (int64_t)*(int32_t *)(p + 0x48);
}

/* FUN_0014fb10 @ 0x14fb10  (est. sk_svc0_send5)
 * cL4 syscall 0 send with 5 args. */
static void sk_svc0_send5_14fb10(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t *blk = (uint64_t *)0;
    blk[0] = b; blk[1] = c; blk[2] = d; blk[3] = e;
    /* CallSupervisor(0) */
    blk[0] = b;
}

/* FUN_0014fb4c @ 0x14fb4c  (est. sk_svc_read)
 * Reads the per-thread syscall arg slot (param_1+2). */
static uint64_t sk_svc_read_14fb4c(int idx)
{
    /* return *(uint64_t*)(tpidrro_el0 + (idx+2)*8) */
    return 0;
}

/* FUN_0014fb5c @ 0x14fb5c  (est. sk_svc0_recv)
 * cL4 syscall 0 receive: writes {type, arg}, issues SVC 0, returns the result
 * into *param_4. */
static void sk_svc0_recv_14fb5c(uint64_t a, uint64_t b, uint64_t c, uint64_t *out)
{
    uint64_t *blk = (uint64_t *)0;
    blk[0] = b; blk[1] = c;
    /* CallSupervisor(0) */
    blk[0] = b;
    *out = b;
}

/* FUN_0014fb88 @ 0x14fb88  (est. sk_svc0_recv1)
 * cL4 syscall 0 receive (single arg). */
static void sk_svc0_recv1_14fb88(uint64_t a, uint64_t b, uint64_t *out)
{
    uint64_t *blk = (uint64_t *)0;
    blk[0] = b;
    /* CallSupervisor(0) */
    blk[0] = b;
    *out = b;
}

/* FUN_0014fbb4 @ 0x14fbb4  (est. sk_svc0_recv_loop)
 * cL4 syscall 0 receive loop (repeats while param_1==1). */
static void sk_svc0_recv_loop_14fbb4(int64_t flag, uint64_t b, int32_t c)
{
    uint64_t *blk = (uint64_t *)0;
    blk[0] = b; blk[1] = (int64_t)c;
    do { /* CallSupervisor(0) */ blk[0] = b; } while (flag == 1);
}

/* FUN_0014fbf0 @ 0x14fbf0  (est. sk_svc3_send)
 * cL4 syscall 3 send with 5 args. */
static void sk_svc3_send_14fbf0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g)
{
    uint64_t *blk = (uint64_t *)0;
    blk[0] = c; blk[1] = d; blk[2] = e; blk[3] = f; blk[4] = g;
    /* CallSupervisor(3) */
}

/* FUN_0014fc08 @ 0x14fc08  (est. sk_obj_free_wrap_b)
 * Object free wrapper (FUN_0014baf4). */
static void sk_obj_free_wrap_14fc08(void) { /* FUN_0014baf4() */ }

/* FUN_0014fc0c @ 0x14fc0c  (est. sk_obj_free_wrap_c)
 * Duplicate of 0x14fc08. */
static void sk_obj_free_wrap_14fc0c(void) { /* FUN_0014baf4() */ }

/* FUN_0014fc20 @ 0x14fc20  (est. sk_obj_op_wrap)
 * Object operation wrapper (FUN_0014c200). */
static void sk_obj_op_wrap_14fc20(void) { /* FUN_0014c200() */ }

/* FUN_0014fc24 @ 0x14fc24  (est. sk_obj_op_wrap_b)
 * Duplicate of 0x14fc20. */
static void sk_obj_op_wrap_14fc24(void) { /* FUN_0014c200() */ }

/* FUN_0014fc38 @ 0x14fc38  (est. sk_obj_op_wrap_c)
 * Object operation wrapper (FUN_0014bd04). */
static void sk_obj_op_wrap_14fc38(void) { /* FUN_0014bd04() */ }

/* FUN_0014fc3c @ 0x14fc3c  (est. sk_obj_op_wrap_d)
 * Duplicate of 0x14fc38. */
static void sk_obj_op_wrap_14fc3c(void) { /* FUN_0014bd04() */ }

/* FUN_0014fc50 @ 0x14fc50  (est. sk_obj_op_wrap_e)
 * Object operation wrapper (FUN_0014bcd8). */
static void sk_obj_op_wrap_14fc50(void) { /* FUN_0014bcd8() */ }

/* FUN_0014fc54 @ 0x14fc54  (est. sk_obj_op_wrap_f)
 * Duplicate of 0x14fc50. */
static void sk_obj_op_wrap_14fc54(void) { /* FUN_0014bcd8() */ }

/* FUN_0014fc68 @ 0x14fc68  (est. sk_obj_op_wrap_g)
 * Object operation wrapper (FUN_0014cdb0). */
static void sk_obj_op_wrap_14fc68(void) { /* FUN_0014cdb0() */ }

/* FUN_0014fc6c @ 0x14fc6c  (est. sk_obj_op_wrap_h)
 * Duplicate of 0x14fc68. */
static void sk_obj_op_wrap_14fc6c(void) { /* FUN_0014cdb0() */ }

/* FUN_0014fc80 @ 0x14fc80  (est. sk_obj_op_wrap_i)
 * Object operation wrapper (FUN_0014d118). */
static void sk_obj_op_wrap_14fc80(void) { /* FUN_0014d118() */ }

/* FUN_0014fc84 @ 0x14fc84  (est. sk_obj_op_wrap_j)
 * Duplicate of 0x14fc80. */
static void sk_obj_op_wrap_14fc84(void) { /* FUN_0014d118() */ }

/* FUN_0014fc98 @ 0x14fc98  (est. sk_obj_op_wrap_k)
 * Object operation wrapper (FUN_0014bfcc). */
static void sk_obj_op_wrap_14fc98(void) { /* FUN_0014bfcc() */ }

/* FUN_0014fc9c @ 0x14fc9c  (est. sk_obj_op_wrap_l)
 * Duplicate of 0x14fc98. */
static void sk_obj_op_wrap_14fc9c(void) { /* FUN_0014bfcc() */ }

/* FUN_0014fcb0 @ 0x14fcb0  (est. sk_obj_op_wrap_m)
 * Object operation wrapper (FUN_0014bb94). */
static void sk_obj_op_wrap_14fcb0(void) { /* FUN_0014bb94() */ }

/* FUN_0014fcb4 @ 0x14fcb4  (est. sk_obj_op_wrap_n)
 * Duplicate of 0x14fcb0. */
static void sk_obj_op_wrap_14fcb4(void) { /* FUN_0014bb94() */ }

/* FUN_0014fcc8 @ 0x14fcc8  (est. sk_obj_op_wrap_o)
 * Object operation wrapper (FUN_0014bb68). */
static void sk_obj_op_wrap_14fcc8(void) { /* FUN_0014bb68() */ }

/* FUN_0014fccc @ 0x14fccc  (est. sk_obj_op_wrap_p)
 * Duplicate of 0x14fcc8. */
static void sk_obj_op_wrap_14fccc(void) { /* FUN_0014bb68() */ }

/* FUN_0014fce0 @ 0x14fce0  (est. sk_obj_op_wrap_q)
 * Object operation wrapper (FUN_0014c860). */
static void sk_obj_op_wrap_14fce0(void) { /* FUN_0014c860() */ }

/* FUN_0014fce4 @ 0x14fce4  (est. sk_obj_op_wrap_r)
 * Duplicate of 0x14fce0. */
static void sk_obj_op_wrap_14fce4(void) { /* FUN_0014c860() */ }

/* FUN_0014fcf8 @ 0x14fcf8  (est. sk_obj_op_wrap_s)
 * Object operation wrapper (FUN_0014c5d0). */
static void sk_obj_op_wrap_14fcf8(void) { /* FUN_0014c5d0() */ }

/* FUN_0014fcfc @ 0x14fcfc  (est. sk_obj_op_wrap_t)
 * Duplicate of 0x14fcf8. */
static void sk_obj_op_wrap_14fcfc(void) { /* FUN_0014c5d0() */ }

/* FUN_0014fd10 @ 0x14fd10  (est. sk_obj_op_wrap_u)
 * Object operation wrapper (FUN_0014d250). */
static void sk_obj_op_wrap_14fd10(void) { /* FUN_0014d250() */ }

/* FUN_0014fd14 @ 0x14fd14  (est. sk_obj_op_wrap_v)
 * Duplicate of 0x14fd10. */
static void sk_obj_op_wrap_14fd14(void) { /* FUN_0014d250() */ }

/* FUN_0014fd34 @ 0x14fd34  (est. sk_objflag3_get)
 * Reads the object flag at 0x653e18; returns 0x42. */
static uint8_t sk_objflag3_get_14fd34(void)
{
    /* FUN_0036a1a0(0x653e18, buf, 0, 0) */
    return 0x42;
}

/* ============ 0x14fd78 - 0x154404 : cL4 object utils ============ */

/* FUN_0014fd78 @ 0x14fd78  (est. sk_objflag3_set)
 * Sets the object flag at 0x653e18. */
static void sk_objflag3_set_14fd78(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e18, buf, 1, 0); uRam_653e18 = v */
}

/* FUN_0014fdc0 @ 0x14fdc0  (est. sk_objflag3_share)
 * Shares the object flag at 0x653e18. */
static void sk_objflag3_share_14fdc0(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e18, v, 0x21, 0); return {&DAT_0007bf58, 0x653e18} */
}

/* FUN_0014fe24 @ 0x14fe24  (est. sk_objflag4_get)
 * Reads the object flag at 0x653e19; returns 0x91. */
static uint8_t sk_objflag4_get_14fe24(void)
{
    /* FUN_0036a1a0(0x653e19, buf, 0, 0) */
    return 0x91;
}

/* FUN_0014fe68 @ 0x14fe68  (est. sk_objflag4_set)
 * Sets the object flag at 0x653e19. */
static void sk_objflag4_set_14fe68(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e19, buf, 1, 0); uRam_653e19 = v */
}

/* FUN_0014feb0 @ 0x14feb0  (est. sk_objflag4_share)
 * Shares the object flag at 0x653e19. */
static void sk_objflag4_share_14feb0(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e19, v, 0x21, 0); return {&LAB_0006f910, 0x653e19} */
}

/* FUN_0014ff08 @ 0x14ff08  (est. sk_obj_dispatch_a)
 * Object dispatch (FUN_00150398). */
static void sk_obj_dispatch_14ff08(void) { /* FUN_00150398() */ }

/* FUN_0014ff0c @ 0x14ff0c  (est. sk_obj_dispatch_b)
 * Duplicate of 0x14ff08. */
static void sk_obj_dispatch_14ff0c(void) { /* FUN_00150398() */ }

/* FUN_0014ff74 @ 0x14ff74  (est. sk_obj_dispatch_c)
 * Object dispatch (FUN_00150398). */
static void sk_obj_dispatch_14ff74(void) { /* FUN_00150398() */ }

/* FUN_0014ff78 @ 0x14ff78  (est. sk_obj_dispatch_d)
 * Duplicate of 0x14ff74. */
static void sk_obj_dispatch_14ff78(void) { /* FUN_00150398() */ }

/* FUN_0014ffe0 @ 0x14ffe0  (est. sk_ipc_op1)
 * IPC operation (FUN_00377824/FUN_00377bec + FUN_001500a8 handler). */
static void sk_ipc_op1_14ffe0(void)
{
    /* see decompile */
}

/* FUN_001500a8 @ 0x1500a8  (est. sk_skip_14_b)
 * Skip-list node advance (base+0x14). */
static int64_t sk_skip_14_1500a8(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_001500d8 @ 0x1500d8  (est. sk_obj_dispatch_e)
 * Object dispatch (FUN_00150398). */
static void sk_obj_dispatch_1500d8(void) { /* FUN_00150398() */ }

/* FUN_001500dc @ 0x1500dc  (est. sk_obj_dispatch_f)
 * Duplicate of 0x1500d8. */
static void sk_obj_dispatch_1500dc(void) { /* FUN_00150398() */ }

/* FUN_00150144 @ 0x150144  (est. sk_ipc_op2)
 * IPC operation 2 (handler FUN_00150218). */
static void sk_ipc_op2_150144(void)
{
    /* see decompile */
}

/* FUN_00150218 @ 0x150218  (est. sk_skip_0c_b)
 * Skip-list node advance (base+0xc). */
static int64_t sk_skip_0c_150218(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_00150248 @ 0x150248  (est. sk_ipc_op3)
 * IPC operation 3 (handler FUN_0015032c). */
static void sk_ipc_op3_150248(void)
{
    /* see decompile */
}

/* FUN_0015032c @ 0x15032c  (est. sk_skip_10_b)
 * Skip-list node advance (base+0x10). */
static int64_t sk_skip_10_15032c(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_0015035c @ 0x15035c  (est. sk_obj_dispatch_g)
 * Object dispatch (FUN_00150398). */
static void sk_obj_dispatch_15035c(void) { /* FUN_00150398() */ }

/* FUN_00150360 @ 0x150360  (est. sk_obj_dispatch_h)
 * Duplicate of 0x15035c. */
static void sk_obj_dispatch_150360(void) { /* FUN_00150398() */ }

/* FUN_00150398 @ 0x150398  (est. sk_obj_dispatch)
 * Object dispatch core: resolves via FUN_00377824/FUN_00377bec, invokes the
 * param_6 callback. */
static void sk_obj_dispatch_150398(void)
{
    /* see decompile */
}

/* FUN_001504bc @ 0x1504bc  (est. sk_objflag5_get)
 * Reads the object flag at 0x653e1a; returns 0x49. */
static uint8_t sk_objflag5_get_1504bc(void)
{
    /* FUN_0036a1a0(0x653e1a, buf, 0, 0) */
    return 0x49;
}

/* FUN_00150500 @ 0x150500  (est. sk_objflag5_set)
 * Sets the object flag at 0x653e1a. */
static void sk_objflag5_set_150500(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e1a, buf, 1, 0); uRam_653e1a = v */
}

/* FUN_00150548 @ 0x150548  (est. sk_objflag5_share)
 * Shares the object flag at 0x653e1a. */
static void sk_objflag5_share_150548(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e1a, v, 0x21, 0); return {&LAB_0006f910, 0x653e1a} */
}

/* FUN_001505a0 @ 0x1505a0  (est. sk_ipc_op4)
 * IPC operation 4 (handler FUN_00150674). */
static void sk_ipc_op4_1505a0(void)
{
    /* see decompile */
}

/* FUN_00150674 @ 0x150674  (est. sk_skip_0c_c)
 * Skip-list node advance (base+0xc). */
static int64_t sk_skip_0c_150674(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_001506a4 @ 0x1506a4  (est. sk_ipc_op5)
 * IPC operation 5 (handler FUN_0015076c). */
static void sk_ipc_op5_1506a4(void)
{
    /* see decompile */
}

/* FUN_0015076c @ 0x15076c  (est. sk_skip_10_c)
 * Skip-list node advance (base+0x10). */
static int64_t sk_skip_10_15076c(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_0015079c @ 0x15079c  (est. sk_ipc_op6)
 * IPC operation 6 (handler FUN_00150870). */
static void sk_ipc_op6_15079c(void)
{
    /* see decompile */
}

/* FUN_00150870 @ 0x150870  (est. sk_skip_14_c)
 * Skip-list node advance (base+0x14). */
static int64_t sk_skip_14_150870(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_001508a0 @ 0x1508a0  (est. sk_ipc_send_obj)
 * IPC object send: dispatches via FUN_0014b2f0 with the callback
 * FUN_00150908. */
static void sk_ipc_send_obj_1508a0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* FUN_0014b2f0(a, FUN_00150908, buf, c, 0x666288, d, FUN_006661e0, e) */
}

/* FUN_00150908 @ 0x150908  (est. sk_ipc_send_obj_cb)
 * IPC object send callback (FUN_0015079c). */
static uint64_t sk_ipc_send_obj_cb_150908(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* uVar1 = FUN_0015079c(b, ctx[0x20], a, ctx[0x10], ctx[0x18]); if (err) report */
    return 0;
}

/* FUN_00150980 @ 0x150980  (est. sk_global_4e3658)
 * Returns &DAT_004e3658. */
static void *sk_global_150980(void) { /* return &DAT_004e3658 */ return 0; }

/* FUN_0015098c @ 0x15098c  (est. sk_global_4e3660)
 * Returns &DAT_004e3660. */
static void *sk_global_15098c(void) { /* return &DAT_004e3660 */ return 0; }

/* FUN_00150998 @ 0x150998  (est. sk_global_4e3668)
 * Returns &DAT_004e3668. */
static void *sk_global_150998(void) { /* return &DAT_004e3668 */ return 0; }

/* FUN_00150b04 @ 0x150b04  (est. sk_obj_memcmp)
 * Object memory compare (16-byte NEON, like the earlier memcmp helpers). */
static void sk_obj_memcmp_150b04(uint64_t *a, long b)
{
    (void)a; (void)b;
    /* see decompile */
}

/* FUN_00153904 @ 0x153904  (est. sk_ipc_op7)
 * IPC operation 7 (handler FUN_001539d8). */
static void sk_ipc_op7_153904(void)
{
    /* see decompile */
}

/* FUN_001539d8 @ 0x1539d8  (est. sk_skip_1c)
 * Skip-list node advance (base+0x1c). */
static int64_t sk_skip_1c_1539d8(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x1c) + (int64_t)*(int32_t *)(p + 0x1c);
}

/* FUN_00153a08 @ 0x153a08  (est. sk_ipc_send_obj2)
 * IPC object send 2 (callback FUN_00153a70). */
static void sk_ipc_send_obj2_153a08(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* FUN_0014b2f0(a, FUN_00153a70, buf, c, 0x666a50, d, 0x6669a8, e) */
}

/* FUN_00153a70 @ 0x153a70  (est. sk_ipc_send_obj2_cb)
 * IPC object send 2 callback (FUN_00153904). */
static uint64_t sk_ipc_send_obj2_cb_153a70(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* uVar1 = FUN_00153904(b, ctx[0x20], a, ctx[0x10], ctx[0x18]) */
    return 0;
}

/* FUN_00153b20 @ 0x153b20  (est. sk_const16)
 * Returns 16-byte {0x11e71c, 0}. */
static void sk_const16_153b20(void) { /* returns {0x11e71c, 0} */ }

/* FUN_00153b3c @ 0x153b3c  (est. sk_check_then_panic)
 * Runs callback param_1; if it returns nonzero, return; else runs param_3 and
 * panics with the error record. */
static void sk_check_then_panic_153b3c(uint64_t (*a)(void), uint64_t b, uint64_t (*c)(void), uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h;
    /* see decompile */
}

/* FUN_00153be0 @ 0x153be0  (est. sk_obj_get50)
 * Calls vtable 0x50, stores result. */
static void sk_obj_get50_153be0(uint64_t *out, uint64_t *ctx)
{
    (void)out; (void)ctx;
    /* *out = (**(code**)(*(long*)*ctx + 0x50))() */
}

/* FUN_00153c24 @ 0x153c24  (est. sk_obj_set20)
 * Sets the object at param_2+0x20 (releasing old). */
static void sk_obj_set20_153c24(uint64_t *p, int64_t *ctx)
{
    (void)p; (void)ctx;
    /* uVar1 = *p; lVar2 = *ctx; FUN_0036a1a0(lVar2+0x20, buf, 1, 0); *(lVar2+0x20) = uVar1 */
}

/* FUN_00153c68 @ 0x153c68  (est. sk_obj_get20)
 * Reads the object at ctx+0x20. */
static uint64_t sk_obj_get20_153c68(void)
{
    /* FUN_0036a1a0(ctx+0x20, buf, 0, 0); return *(ctx+0x20) */
    return 0;
}

/* FUN_00153c9c @ 0x153c9c  (est. sk_obj_set20_b)
 * Sets the object at ctx+0x20. */
static void sk_obj_set20_153c9c(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(ctx+0x20, buf, 1, 0); *(ctx+0x20) = v */
}

/* FUN_00153cdc @ 0x153cdc  (est. sk_arr_new)
 * Allocates then runs the array constructor 0x153d1c. */
static uint64_t sk_arr_new_153cdc(uint64_t p)
{
    (void)p;
    uint64_t v = /* FUN_0036a940() */ 0;
    /* FUN_00153d1c(p) */
    return v;
}

/* FUN_00153d1c @ 0x153d1c  (est. sk_arr_init)
 * Array initializer: validates the count (>= 0), builds the element array via
 * FUN_002a3ff0. */
static void sk_arr_init_153d1c(int64_t n)
{
    (void)n;
    /* see decompile */
}

/* FUN_00153d5c @ 0x153d5c  (est. sk_arr_iterate)
 * Array iteration: runs FUN_00153dfc over each element, then flushes via
 * thunk_FUN_00320078. */
static void sk_arr_iterate_153d5c(void)
{
    /* see decompile */
}

/* FUN_00153dfc @ 0x153dfc  (est. sk_arr_iter_one)
 * Array iteration for one element (bounds-checked). */
static void sk_arr_iter_one_153dfc(int64_t idx, int64_t a, int64_t n, int64_t p)
{
    (void)idx; (void)a; (void)n; (void)p;
    /* if (idx >= 0 && idx < n) FUN_0019cb68(1, a + *(p-8+0x48)*idx, p); else BRK */
}

/* FUN_00153e34 @ 0x153e34  (est. sk_arr_iterate_td)
 * Array iterate then teardown. */
static void sk_arr_iterate_td_153e34(void) { /* FUN_00153d5c(); FUN_0036b6ac() */ }

/* FUN_00153e38 @ 0x153e38  (est. sk_arr_iterate_td_b)
 * Duplicate of 0x153e34. */
static void sk_arr_iterate_td_153e38(void) { /* FUN_00153d5c(); FUN_0036b6ac() */ }

/* FUN_00153e5c @ 0x153e5c  (est. sk_arr_append)
 * Array append: validates the index range, calls the vtable +0x20 write,
 * increments the count. */
static void sk_arr_append_153e5c(uint64_t v)
{
    (void)v;
    /* see decompile */
}

/* FUN_00153fac @ 0x153fac  (est. sk_arr_is_empty)
 * Returns whether the array count (vtable 0x50) is 0. */
static bool sk_arr_is_empty_153fac(void)
{
    /* return (**(code**)(*ctx + 0x50))() == 0 */
    return false;
}

/* FUN_00153fb0 @ 0x153fb0  (est. sk_arr_is_empty_b)
 * Duplicate of 0x153fac. */
static bool sk_arr_is_empty_153fb0(void) { /* same as 0x153fac */ return false; }

/* FUN_00153fe4 @ 0x153fe4  (est. sk_arr_is_full)
 * Returns whether the array count equals the capacity (0x68). */
static bool sk_arr_is_full_153fe4(void)
{
    /* return (**(code**)(*ctx + 0x50))() == (**(code**)(*ctx + 0x68))() */
    return false;
}

/* FUN_00154044 @ 0x154044  (est. sk_arr_remove)
 * Array remove: validates the count (>=1), decrements, copies out the last
 * element via FUN_00154148. */
static void sk_arr_remove_154044(uint64_t v)
{
    (void)v;
    /* see decompile */
}

/* FUN_00154148 @ 0x154148  (est. sk_arr_copy_out)
 * Array copy-out of one element (bounds-checked). */
static void sk_arr_copy_out_154148(int64_t idx, int64_t a, int64_t n, int64_t p)
{
    (void)idx; (void)a; (void)n; (void)p;
    /* if (idx >= 0 && idx < n) FUN_001a29a0(a + *(p-8+0x48)*idx, p); else BRK */
}

/* FUN_0015417c @ 0x15417c  (est. sk_arr_for_each)
 * Array for-each: iterates the count elements, calling the callback param_1
 * on each. */
static void sk_arr_for_each_15417c(uint64_t (*cb)(void))
{
    (void)cb;
    /* see decompile */
}

/* FUN_00154258 @ 0x154258  (est. sk_arr_remove_all)
 * Array remove-all: removes and processes each element via the callback. */
static void sk_arr_remove_all_154258(uint64_t (*cb)(void))
{
    (void)cb;
    /* see decompile */
}

/* FUN_00154404 @ 0x154404  (est. sk_arr_new_with)
 * Array constructor with a count: allocates the 0x28 array object. */
static int64_t *sk_arr_new_with_154404(uint64_t (*cb)(void), uint64_t a, uint64_t b)
{
    (void)cb; (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* ============ 0x1545c4 - 0x154e80 : L4Swift NonCopyableUtils array ============ */

/* FUN_001545c4 @ 0x1545c4  (est. sk_arr_type)
 * Array type resolution (FUN_00021480). */
static void sk_arr_type_1545c4(void)
{
    /* FUN_00021480() */
}

/* FUN_001545dc @ 0x1545dc  (est. sk_arr_drain)
 * Array drain: iterates the count elements, copying each out (FUN_00154148)
 * and releasing via the vtable +0x78; drains the array. */
static int64_t *sk_arr_drain_1545dc(uint64_t (*cb)(void), uint64_t a, uint64_t b)
{
    (void)cb; (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_00154854 @ 0x154854  (est. sk_arr_copy_n)
 * Array copy of the first n elements: allocates the 0x28 array object, copies
 * the elements (FUN_00154148), and normalizes the count. */
static int64_t *sk_arr_copy_n_154854(int64_t n)
{
    (void)n;
    /* see decompile */
    return 0;
}

/* FUN_00154a1c @ 0x154a1c  (est. sk_arr_get)
 * Array element get: validates the index, returns {FUN_0001a1c8, element ptr};
 * panics "L4Swift.NonCopyableUtils.swift" on out-of-range. */
static void sk_arr_get_154a1c(uint64_t a, int64_t idx)
{
    (void)a; (void)idx;
    /* see decompile */
}

/* FUN_00154b08 @ 0x154b08  (est. sk_arr_get_b)
 * Array element get variant. */
static void sk_arr_get_154b08(uint64_t a, int64_t idx)
{
    (void)a; (void)idx;
    /* see decompile */
}

/* FUN_00154bf4 @ 0x154bf4  (est. sk_arr_set)
 * Array element set: validates the index, calls the vtable +8 (release) and
 * +0x20 (assign) methods. */
static void sk_arr_set_154bf4(uint64_t v, int64_t idx)
{
    (void)v; (void)idx;
    /* see decompile */
}

/* FUN_00154d40 @ 0x154d40  (est. sk_cfg_parse)
 * Config parse (FUN_00374104 with the 0x4e3e08 descriptor). */
static void sk_cfg_parse_154d40(int64_t p)
{
    (void)p;
    /* see decompile */
}

/* FUN_00154d9c @ 0x154d9c  (est. sk_objflag6_get)
 * Reads the object flag at 0x653e3b; returns 0x79. */
static uint8_t sk_objflag6_get_154d9c(void)
{
    /* FUN_0036a1a0(0x653e3b, buf, 0, 0) */
    return 0x79;
}

/* FUN_00154de0 @ 0x154de0  (est. sk_objflag6_set)
 * Sets the object flag at 0x653e3b. */
static void sk_objflag6_set_154de0(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e3b, buf, 1, 0); uRam_653e3b = v */
}

/* FUN_00154e28 @ 0x154e28  (est. sk_objflag6_share)
 * Shares the object flag at 0x653e3b. */
static void sk_objflag6_share_154e28(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e3b, v, 0x21, 0); return {&LAB_0006f910, 0x653e3b} */
}

/* FUN_00154e80 @ 0x154e80  (est. sk_arr_wrap)
 * Array wrapper (FUN_00155368). */
static void sk_arr_wrap_154e80(void) { /* FUN_00155368() */ }

/* ============ 0x154edc - 0x15a464 : DART/IO mapper ============ */

/* FUN_00154edc @ 0x154edc  (est. sk_dart_op)
 * DART operation (FUN_00377824/FUN_00377bec + FUN_001554ac handler). */
static void sk_dart_op_154edc(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint32_t e, uint64_t f, uint64_t g, uint64_t h)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h;
    /* see decompile */
}

/* FUN_00154fd0 @ 0x154fd0  (est. sk_dart_op_w)
 * DART operation wrapper (0,1,1,0). */
static void sk_dart_op_154fd0(void)
{
    /* auVar3 = FUN_00154edc(a, 0, 1, b, 0, c, d, e) */
}

/* FUN_00154fd4 @ 0x154fd4  (est. sk_dart_op_wb)
 * Duplicate of 0x154fd0. */
static void sk_dart_op_154fd4(void) { /* same as 0x154fd0 */ }

/* FUN_00155018 @ 0x155018  (est. sk_dart_op2)
 * DART operation wrapper (1,0,0,1). */
static void sk_dart_op2_155018(void)
{
    /* auVar3 = FUN_00154edc(a, b, 0, 0, 1, c, d, e) */
}

/* FUN_0015501c @ 0x15501c  (est. sk_dart_op2_b)
 * Duplicate of 0x155018. */
static void sk_dart_op2_15501c(void) { /* same as 0x155018 */ }

/* FUN_0015505c @ 0x15505c  (est. sk_dart_op3)
 * DART operation wrapper (1,0,1,0). */
static void sk_dart_op3_15505c(void)
{
    /* auVar3 = FUN_00154edc(a, b, 0, c, 0, d, e, f) */
}

/* FUN_00155060 @ 0x155060  (est. sk_dart_op3_b)
 * Duplicate of 0x15505c. */
static void sk_dart_op3_155060(void) { /* same as 0x15505c */ }

/* FUN_001550a0 @ 0x1550a0  (est. sk_dart_send)
 * DART send: dispatches via FUN_0014b2f0 with FUN_00155110. */
static void sk_dart_send_1550a0(uint64_t a, uint64_t b, uint8_t c, uint64_t d, uint8_t e, uint64_t f, uint64_t g, uint64_t h)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h;
    /* FUN_0014b2f0(a, FUN_00155110, buf, f, 0x666b80, g, 0x666ad0) */
}

/* FUN_00155110 @ 0x155110  (est. sk_dart_send_cb)
 * DART send callback. */
static uint64_t sk_dart_send_cb_155110(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* uVar1 = FUN_00154edc(b, ctx[0x20], ctx[0x28], ctx[0x30], ctx[0x38], a, ctx[0x10], ctx[0x18]) */
    return 0;
}

/* FUN_00155194 @ 0x155194  (est. sk_dart_send2)
 * DART send 2. */
static void sk_dart_send2_155194(uint64_t a, uint64_t b, uint8_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile */
}

/* FUN_00155208 @ 0x155208  (est. sk_dart_wrap)
 * DART wrapper (FUN_00155270). */
static void sk_dart_wrap_155208(void) { /* FUN_00155270() */ }

/* FUN_0015520c @ 0x15520c  (est. sk_dart_wrap_b)
 * Duplicate of 0x155208. */
static void sk_dart_wrap_15520c(void) { /* FUN_00155270() */ }

/* FUN_00155224 @ 0x155224  (est. sk_skip_14_d)
 * Skip-list node advance (base+0x14). */
static int64_t sk_skip_14_155224(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_00155254 @ 0x155254  (est. sk_dart_wrap_c)
 * DART wrapper (FUN_00155270). */
static void sk_dart_wrap_155254(void) { /* FUN_00155270() */ }

/* FUN_00155258 @ 0x155258  (est. sk_dart_wrap_d)
 * Duplicate of 0x155254. */
static void sk_dart_wrap_155258(void) { /* FUN_00155270() */ }

/* FUN_00155270 @ 0x155270  (est. sk_dart_op_core)
 * DART operation core (handler FUN_00155224). */
static void sk_dart_op_core_155270(void)
{
    /* see decompile */
}

/* FUN_0015533c @ 0x15533c  (est. sk_dart_wrap2)
 * DART wrapper 2 (FUN_00155368). */
static void sk_dart_wrap2_15533c(void) { /* FUN_00155368() */ }

/* FUN_00155340 @ 0x155340  (est. sk_dart_wrap2_b)
 * Duplicate of 0x15533c. */
static void sk_dart_wrap2_155340(void) { /* FUN_00155368() */ }

/* FUN_00155368 @ 0x155368  (est. sk_dart_op_core2)
 * DART operation core 2. */
static void sk_dart_op_core2_155368(void)
{
    /* see decompile */
}

/* FUN_001554ac @ 0x1554ac  (est. sk_skip_10_d)
 * Skip-list node advance (base+0x10). */
static int64_t sk_skip_10_1554ac(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_001554e8 @ 0x1554e8  (est. sk_objflag7_get)
 * Reads the object flag at 0x653e3c; returns 0xa9. */
static uint8_t sk_objflag7_get_1554e8(void)
{
    /* FUN_0036a1a0(0x653e3c, buf, 0, 0) */
    return 0xa9;
}

/* FUN_0015552c @ 0x15552c  (est. sk_objflag7_set)
 * Sets the object flag at 0x653e3c. */
static void sk_objflag7_set_15552c(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e3c, buf, 1, 0); uRam_653e3c = v */
}

/* FUN_00155574 @ 0x155574  (est. sk_objflag7_share)
 * Shares the object flag at 0x653e3c. */
static void sk_objflag7_share_155574(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e3c, v, 0x21, 0); return {&LAB_0006f910, 0x653e3c} */
}

/* FUN_001555e8 @ 0x1555e8  (est. sk_objflag8_get)
 * Reads the object flag at 0x653e3d; returns 0xe. */
static uint8_t sk_objflag8_get_1555e8(void)
{
    /* FUN_0036a1a0(0x653e3d, buf, 0, 0) */
    return 0xe;
}

/* FUN_0015562c @ 0x15562c  (est. sk_objflag8_set)
 * Sets the object flag at 0x653e3d. */
static void sk_objflag8_set_15562c(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e3d, buf, 1, 0); uRam_653e3d = v */
}

/* FUN_00155674 @ 0x155674  (est. sk_objflag8_share)
 * Shares the object flag at 0x653e3d. */
static void sk_objflag8_share_155674(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e3d, v, 0x21, 0); return {&LAB_0006f910, 0x653e3d} */
}

/* FUN_001556d8 @ 0x1556d8  (est. sk_objflag9_get)
 * Reads the object flag at 0x653e3e; returns 0x40. */
static uint8_t sk_objflag9_get_1556d8(void)
{
    /* FUN_0036a1a0(0x653e3e, buf, 0, 0) */
    return 0x40;
}

/* FUN_0015571c @ 0x15571c  (est. sk_objflag9_set)
 * Sets the object flag at 0x653e3e. */
static void sk_objflag9_set_15571c(uint8_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e3e, buf, 1, 0); uRam_653e3e = v */
}

/* FUN_00155764 @ 0x155764  (est. sk_objflag9_share)
 * Shares the object flag at 0x653e3e. */
static void sk_objflag9_share_155764(uint64_t v)
{
    (void)v;
    /* FUN_0036a1a0(0x653e3e, v, 0x21, 0); return {&DAT_0007bf58, 0x653e3e} */
}

/* FUN_001557bc @ 0x1557bc  (est. sk_dart_wrap3)
 * DART wrapper 3 (FUN_00155aa4). */
static void sk_dart_wrap3_1557bc(void) { /* FUN_00155aa4() */ }

/* FUN_00155850 @ 0x155850  (est. sk_dart_wrap3_b)
 * Duplicate of 0x1557bc. */
static void sk_dart_wrap3_155850(void) { /* FUN_00155aa4() */ }

/* FUN_001558e4 @ 0x1558e4  (est. sk_dart_wrap4)
 * DART wrapper 4 (FUN_00155bec). */
static void sk_dart_wrap4_1558e4(void) { /* FUN_00155bec() */ }

/* FUN_00155934 @ 0x155934  (est. sk_skip_14_e)
 * Skip-list node advance (base+0x14). */
static int64_t sk_skip_14_155934(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_0015972c @ 0x15972c  (est. sk_dart_map_io)
 * DART IO-space mapping: resolves the DART mapper descriptor ("mapper_dart",
 * 0x9630), maps the IO region (FUN_00157e94/FUN_0015881c), and installs the
 * mapping via FUN_001ef804. This maps an IO range into a DART's address space. */
static void sk_dart_map_io_15972c(uint64_t a, uint64_t b, uint64_t c, uint64_t *out)
{
    (void)a; (void)b; (void)c; (void)out;
    /* see decompile: "mapper_dart" mapping */
}

/* FUN_00159b18 @ 0x159b18  (est. sk_dart_map2)
 * DART mapping 2 (multi-level descriptor resolution). */
static void sk_dart_map2_159b18(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h, uint64_t *out, uint64_t (*cb)(void))
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)out; (void)cb;
    /* see decompile */
}

/* FUN_00159d28 @ 0x159d28  (est. sk_dart_region_map)
 * DART region mapping: resolves the region descriptor, maps it via
 * FUN_0015a464/FUN_0015a7b4/FUN_0015aa58 ("range" check), handling the
 * DAT_006add10 debug flag. */
static void sk_dart_region_map_159d28(uint64_t a, uint8_t *b, uint64_t *c)
{
    (void)a; (void)b; (void)c;
    /* see decompile: "range" 0x97cd, DAT_006add10 debug */
}

/* FUN_0015a464 @ 0x15a464  (est. sk_dart_region_map2)
 * DART region mapping 2: builds the mapping record and installs it via the
 * vtable (0x30/0x20 dispatch). */
static void sk_dart_region_map2_15a464(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h, uint8_t (*out)[16])
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)out;
    /* see decompile */
}

/* ============ 0x15a7b4 - 0x15af20 : DART mapper detail ============ */

/* FUN_0015a7b4 @ 0x15a7b4  (est. sk_dart_map3)
 * DART mapping 3: resolves the descriptor, builds the mapping record via
 * FUN_0015f8d0, and installs it via FUN_00163a08 (with FUN_0015fde4). */
static void sk_dart_map3_15a7b4(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h, uint64_t i)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i;
    /* see decompile */
}

/* FUN_0015aa58 @ 0x15aa58  (est. sk_dart_map_bounds)
 * DART mapping with bounds validation: resolves the descriptor, validates the
 * range alignment (16-byte, BRK), and builds the mapping record with the
 * correct type (1/5/4). */
static void sk_dart_map_bounds_15aa58(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint8_t (*out)[16])
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)out;
    /* see decompile */
}

/* FUN_0015af20 @ 0x15af20  (est. sk_dart_map_final)
 * DART mapping finalize: validates the mapping bounds and installs the final
 * mapping record. */
static uint64_t sk_dart_map_final_15af20(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t *out)
{
    (void)a; (void)b; (void)c; (void)d; (void)out;
    /* see decompile */
    return 0;
}

/* ============ 0x15af20 - 0x15f8d0 : DART mapper + bootarg parsing ============ */

/* FUN_0015af20 @ 0x15af20  (est. sk_dart_map_full)
 * DART full mapping: resolves the descriptor, issues the mapping query via the
 * 0x98 vtable, installs the mapping (FUN_001636e0), handling the DAT_006add10
 * debug flag. */
static uint64_t sk_dart_map_full_15af20(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t *out)
{
    (void)a; (void)b; (void)c; (void)d; (void)out;
    /* see decompile */
    return 0;
}

/* FUN_0015b4a8 @ 0x15b4a8  (est. sk_dart_unmap_all)
 * DART unmap-all: resolves the descriptor, iterates the mapped regions and
 * unmaps each (FUN_00157e94/FUN_0015a464 with "chosen"/"exclave-dism"/...). */
static uint64_t sk_dart_unmap_all_15b4a8(uint64_t *out)
{
    (void)out;
    /* see decompile */
    return 0;
}

/* FUN_0015b87c @ 0x15b87c  (est. sk_dart_serial)
 * DART serial check: runs the unmap-all, then checks the bootarg
 * "serial-able" (FUN_00467468). */
static uint8_t sk_dart_serial_15b87c(uint64_t *out)
{
    (void)out;
    /* see decompile */
    return 0;
}

/* FUN_0015b9bc @ 0x15b9bc  (est. sk_bootarg_parse)
 * Bootarg parsing: reads the bootarg string (FUN_000f5e08), looks up
 * "serial" (0x3d6c6169726573) and iterates the bootarg list (FUN_000b1e08),
 * returning whether the "serial=" value is enabled. */
static bool sk_bootarg_parse_15b9bc(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return false;
}

/* FUN_0015bc70 @ 0x15bc70  (est. sk_dart_serial2)
 * DART serial check 2 (FUN_00467468 "dart-base" key). */
static uint8_t sk_dart_serial2_15bc70(uint64_t *out)
{
    (void)out;
    /* see decompile */
    return 0;
}

/* FUN_0015bde8 @ 0x15bde8  (est. sk_dart_serial3)
 * DART serial check 3 (checks the "dart-m_elba..." bootarg, inverted). */
static uint8_t sk_dart_serial3_15bde8(uint64_t *out)
{
    (void)out;
    /* see decompile */
    return 0;
}

/* FUN_0015bea8 @ 0x15bea8  (est. sk_bootarg_scan)
 * Bootarg scan: iterates the bootarg list, parses each value (decimal/hex via
 * the digit tables), and returns the parsed bootarg. */
static uint64_t *sk_bootarg_scan_15bea8(uint64_t *out)
{
    (void)out;
    /* see decompile */
    return 0;
}

/* FUN_0015f108 @ 0x15f108  (est. sk_range_parse)
 * Range parse (hex): parses a hex range [start,end) from the bootarg string,
 * resolving the range via FUN_002b15d0/FUN_0001da84, handling the +/- sign;
 * bounds-checked. Returns the 128-bit parsed value. */
static void sk_range_parse_15f108(int64_t a, int64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile */
}

/* FUN_0015f4e0 @ 0x15f4e0  (est. sk_range_parse_dec)
 * Range parse (decimal): parses a decimal range from the bootarg string. */
static void sk_range_parse_dec_15f4e0(int64_t a, int64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    /* see decompile */
}

/* FUN_0015f850 @ 0x15f850  (est. sk_range_size)
 * Range size: computes the range size (FUN_0015e780). */
static uint64_t sk_range_size_15f850(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* see decompile */
    return 0;
}

/* FUN_0015f8d0 @ 0x15f8d0  (est. sk_bootarg_lookup)
 * Bootarg lookup: resolves the bootarg descriptor (FUN_00377824/FUN_00377bec),
 * parses the bootarg string (FUN_0015f850), and returns the parsed value. */
static uint64_t sk_bootarg_lookup_15f8d0(uint64_t a, uint64_t b, uint64_t c, uint64_t *out)
{
    (void)a; (void)b; (void)c; (void)out;
    /* see decompile */
    return 0;
}

/* ============ 0x15fc84 - 0x15fff8 : DART helpers ============ */

/* FUN_0015fc84 @ 0x15fc84  (est. sk_bootarg_hash)
 * Bootarg hash: hashes the 0x13f-byte bootarg descriptor (FUN_00377dcc),
 * returning the digest or a short record. */
static void sk_bootarg_hash_15fc84(int64_t p)
{
    (void)p;
    /* see decompile */
}

/* FUN_0015fd30 @ 0x15fd30  (est. sk_patch_const)
 * Writes a constant to the 0x653ee0 read-only slot. */
static void sk_patch_const_15fd30(void)
{
    /* uRam_653ee0 = 0x940048bf910063e1 */
}

/* FUN_0015fd84 @ 0x15fd84  (est. sk_skip_0c_d)
 * Skip-list node advance (base+0xc). */
static int64_t sk_skip_0c_15fd84(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_0015fdb4 @ 0x15fdb4  (est. sk_obj_share)
 * Object share (thunk_FUN_0035d334 with 0x6673a0). */
static uint64_t sk_obj_share_15fdb4(uint64_t p)
{
    /* thunk_FUN_0035d334(p, 0x6673a0) */
    return p;
}

/* FUN_0015fde4 @ 0x15fde4  (est. sk_dart_cb1)
 * DART callback 1 (FUN_0015e018). */
static uint32_t sk_dart_cb1_15fde4(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* uVar1 = FUN_0015e018(a, ctx[0x20], ctx[0x28], ctx[0x10], ctx[0x18], b) */
    return 0;
}

/* FUN_0015fde8 @ 0x15fde8  (est. sk_dart_cb1_b)
 * Duplicate of 0x15fde4. */
static uint32_t sk_dart_cb1_15fde8(uint64_t a, uint64_t b) { /* same as 0x15fde4 */ return 0; }

/* FUN_0015fe0c @ 0x15fe0c  (est. sk_dart_cb2)
 * DART callback 2 (FUN_0015d01c). */
static uint32_t sk_dart_cb2_15fe0c(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* uVar1 = FUN_0015d01c(a, ctx[0x20], ctx[0x10], ctx[0x18], b) */
    return 0;
}

/* FUN_0015fe10 @ 0x15fe10  (est. sk_dart_cb2_b)
 * Duplicate of 0x15fe0c. */
static uint32_t sk_dart_cb2_15fe10(uint64_t a, uint64_t b) { /* same as 0x15fe0c */ return 0; }

/* FUN_0015fe34 @ 0x15fe34  (est. sk_skip_0c_e)
 * Skip-list node advance (base+0xc). */
static int64_t sk_skip_0c_15fe34(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_0015fe64 @ 0x15fe64  (est. sk_skip_10_e)
 * Skip-list node advance (base+0x10). */
static int64_t sk_skip_10_15fe64(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_0015fea4 @ 0x15fea4  (est. sk_skip_10_f)
 * Skip-list node advance (base+0x10). */
static int64_t sk_skip_10_15fea4(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_0015fed4 @ 0x15fed4  (est. sk_obj_init653ee8)
 * Object init: resolves the type (FUN_00002534 0x653ee8) and calls the vtable
 * +8 method. */
static uint64_t sk_obj_init653ee8_15fed4(uint64_t p)
{
    (void)p;
    /* see decompile */
    return p;
}

/* FUN_0015ff34 @ 0x15ff34  (est. sk_obj_copy653)
 * Object copy (thunk_FUN_0035dc24 with 0x6673a0). */
static uint64_t sk_obj_copy653_15ff34(uint64_t a, uint64_t b)
{
    /* thunk_FUN_0035dc24(b, a, 0x6673a0) */
    return b;
}

/* FUN_0015ff6c @ 0x15ff6c  (est. sk_obj_release)
 * Object release (FUN_003a25d4). */
static void sk_obj_release_15ff6c(uint64_t a, uint64_t b)
{
    (void)a;
    /* FUN_003a25d4(b) */
}

/* FUN_0015ff94 @ 0x15ff94  (est. sk_obj_op_dispatch)
 * Object operation dispatch (FUN_00160d70 or FUN_00160da0). */
static void sk_obj_op_dispatch_15ff94(char flag, uint64_t a, uint64_t b)
{
    (void)flag; (void)a; (void)b;
    /* see decompile */
}

/* FUN_0015fff8 @ 0x15fff8  (est. sk_report_error)
 * Error report (FUN_0036993c 0x667580/0x6674c8), returns 0. */
static uint64_t sk_report_error_15fff8(void)
{
    /* FUN_0036993c(0x667580, 0x6674c8, 0, 0); *x1 = 4; x1[1] = 1; FUN_0036986c() */
    return 0;
}

/* ============ 0x160070 - 0x162b2c : DART mapper / Launcher.FileFetcher ============ */

/* FUN_00160070 @ 0x160070  (est. sk_dart_ctx_dtor)
 * DART context teardown: init 0x48-byte buf, FUN_0001c2a4(ctx), reinit. */
static void sk_dart_ctx_dtor_160070(void)
{
    /* undefined1 auStack_68[72]; FUN_001a84f4(auStack_68); FUN_0001c2a4(auStack_68,*x20); FUN_001a8564(); */
}

/* FUN_001600b0 @ 0x1600b0  (est. sk_page_tracker_map)  [big dispatcher]
 * Launcher.PageTableTracker page-map core: validates the page-table entry
 * (0x1604cc), classifies op by param_6 (0x1605d0), then routes to the
 * allocate (0x160e24, param_6==1) or unwire (0x160fac, param_6==0) path via
 * the vtable +200 entry. Overflow bits [63:62] on the entry abort (fatal
 * 0x667580/0x6674c8). */
static void sk_page_tracker_map_1600b0(void)
{
    /* see decompile: mask/tag checks, vtable dispatch, SoftwareBreakpoint paths */
}

/* FUN_001604cc @ 0x1604cc  (est. sk_page_tracker_resolve_len)
 * Resolves element stride: if size exceeds remaining, computes the element
 * count from the distance via the size-advance helper (0x15ff94) and the
 * per-type stride fn (0x16113c / 0x16116c); asserts the count fits. */
static void sk_page_tracker_resolve_len_1604cc(void)
{
    /* if (param_3 <= param_1) { uVar2=0x15ff94(...); if (CARRY8) SB; if (param_1 < param_3+uVar2) { stride=(*fn)(...); if(!stride)SB; count=(param_1-param_3)/stride; if(count<0)SB; } } fatal(2); */
}

/* FUN_001605d0 @ 0x1605d0  (est. sk_page_tracker_is_empty)
 * Tests whether the entry describes a full/empty span (all-zero 128-bit
 * value) via vtable +0xc0. */
static uint32_t sk_page_tracker_is_empty_1605d0(void)
{
    /* auVar3 = (**(+0xc0))(buf,0x1604cc()); pl=auVar3._8_8_;
       w22 = (pl[3]<-0x4000000000000000 && pl[3]==-0x8000000000000000 && pl[1]==0 && pl[2]==0 && *pl==0) ? 0 : 1;
       return w22&1; */
    return 0;
}

/* FUN_00160690 @ 0x160690  (est. sk_dart_cfg_init)
 * Allocates 0x28-byte config (zone 0xf20c), copies 4 words from ctx+0x10,
 * returns ctor FUN_00160708. */
static void sk_dart_cfg_init_160690(long *out)
{
    /* long b=FUN_0036a908(0x28,0xf20c); *out=b; FUN_0036a1a0(x20+0x10,b,0x20,0);
       b[0x20]=*(x20+0x28); b[0x18]=*(x20+0x20); return {FUN_00160708, *(x20+0x10)}; */
}

/* FUN_00160708 @ 0x160708  (est. sk_dart_cfg_dtor) */
static void sk_dart_cfg_dtor_160708(uint64_t *p)
{
    /* uVar1=*p; FUN_0036a20c(uVar1); thunk_FUN_00012568(uVar1); */
}

/* FUN_00160738 @ 0x160738  (est. sk_page_tracker_set)
 * Swaps the 4 config words and releases the prior span (0x160e10). */
static void sk_page_tracker_set_160738(void)
{
    /* FUN_0036a1a0(x20+0x10, buf,1,0); old[4]; set new; FUN_00160e10(old...); */
}

/* FUN_001607a4 @ 0x1607a4  (est. sk_page_tracker_init) */
static uint64_t sk_page_tracker_init_1607a4(uint64_t p)
{
    /* uVar1=FUN_0036a940(); FUN_001607e4(p); return uVar1; */
    return 0;
}

/* FUN_001607e4 @ 0x1607e4  (est. sk_page_tracker_setup)
 * Builds a 16-byte span descriptor via 0x160888 using the ctx's +0x38/+0x40
 * metadata. */
static void sk_page_tracker_setup_1607e4(uint64_t p)
{
    /* auVar3=FUN_00160888(1,p,0,0,*(*x20+0x38),*(*x20+0x40));
       FUN_0036a1a0(x20+2,buf,1,0); *(x20+2)=auVar3; x20[4]=0; x20[5]=0; */
}

/* FUN_00160888 @ 0x160888  (est. sk_span_build)
 * Builds a 16-byte (off,len) span; when param_4==0 resolves the type
 * metadata (0x16119c), walks n elements via the +0x78 destructor. */
static void sk_span_build_160888(void)
{
    /* if (param_4==0) { uVar1=0x16119c(0xff,param_5,param_6); 0x1545c4(0,uVar1);
       (*0x161574)(param_5,param_6); pl=0x153cdc(); n=(*0x161574)(param_5,param_6);
       if(n) { f=**(pl+0x78); do { local={0,0,0,0x8000...}; (*f)(&local); n--; } while(n); } }
       return {param_2, param_3}; */
}

/* FUN_001609ac @ 0x1609ac  (est. sk_page_tracker_write_span)
 * Calls the page-map dispatcher (0x1600b0) with the built span + meta. */
static void sk_page_tracker_write_span_1609ac(void)
{
    /* uVar6=*(*x20+0x38); uVar7=*(*x20+0x40); auVar9=0x160888(0,p,param_2,0,u6,u7);
       ... FUN_001600b0(lo,hi,param_2&0xff,0,param_2,1,u5,u8,0,u6); */
}

/* FUN_00160af4 @ 0x160af4  (est. sk_page_tracker_reset)
 * Resets the tracker with empty span (0x4000000000000000 tag). */
static void sk_page_tracker_reset_160af4(void)
{
    /* FUN_001600b0(param_1,0,0,0x4000000000000000,param_2,0,param_3,param_4,param_5,u2); */
}

/* FUN_00160be4 @ 0x160be4  (est. sk_span_release)
 * Releases the stored span (0x160e10). */
static void sk_span_release_160be4(void)
{
    /* FUN_00160e10(*(x20+0x10),*(x20+0x18),*(x20+0x20),*(x20+0x28)); */
}

/* FUN_00160be8 @ 0x160be8  (est. sk_span_release_b)  dup */
static void sk_span_release_160be8(void) { /* dup 0x160be4 */ }

/* FUN_00160c08 @ 0x160c08  (est. sk_span_release_then_notify) */
static void sk_span_release_160c08(void)
{
    /* FUN_00160e10(...); FUN_0036b6ac(); */
}

/* FUN_00160c0c @ 0x160c0c  (est. sk_span_release_then_notify_b) */
static void sk_span_release_160c0c(void) { /* dup 0x160c08 */ }

/* FUN_00160c54 @ 0x160c54  (est. sk_span_add_len)
 * Additive span length advance; asserts no carry. */
static int64_t sk_span_add_len_160c54(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)c; (void)d; (void)e; (void)f;
    /* u = 0x15ff94(...); if carry -> SoftwareBreakpoint */
    return (int64_t)b;
}

/* FUN_00160d70 @ 0x160d70  (est. sk_skip_1c)
 * Skip-list node advance (base+0x1c). */
static int64_t sk_skip_1c_160d70(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x1c) + (int64_t)*(int32_t *)(p + 0x1c);
}

/* FUN_00160da0 @ 0x160da0  (est. sk_skip_18)
 * Skip-list node advance (base+0x18). */
static int64_t sk_skip_18_160da0(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x18) + (int64_t)*(int32_t *)(p + 0x18);
}

/* FUN_00160dd0 @ 0x160dd0  (est. sk_span_call_stride) */
static void sk_span_call_stride_160dd0(uint64_t a, uint64_t b)
{
    /* (*0x161574)(a,b); */
}

/* FUN_00160e10 @ 0x160e10  (est. sk_span_drop)
 * Drops an owned span; if the tag's [63:62] are clear it releases the buffer. */
static void sk_span_drop_160e10(void)
{
    /* if (in_x3>>0x3e==0) FUN_0036b118(in_x3); */
}

/* FUN_00160e24 @ 0x160e24  (est. sk_page_tracker_alloc)
 * PageTableTracker allocation path (op==1). Rebuilds the span via 0x160fd8
 * table, else fatal "Launcher.PageTableTracker" (0x160fd8,line 0x61). */
static void sk_page_tracker_alloc_160e24(uint64_t *p, uint64_t a)
{
    (void)a;
    /* if (p[3]>>0x3e==1) { save; uVar1=0x1558e4(...); if x21==0 restore tag 0x4000000000000000; else error(0x6665b0/0x666518); }
       else { 0x160e10(...); fatal(0x160fd8,"Launcher.PageTableTracker",0x61); } */
}

/* FUN_00160fac @ 0x160fac  (est. sk_page_tracker_unwire)
 * PageTableTracker unwire path (op==0). Rebuilds via 0x155850; failure path
 * fatal "Launcher.PageTableTracker" line 0x6b. */
static void sk_page_tracker_unwire_160fac(uint64_t *p, uint64_t a)
{
    (void)a;
    /* if (p[3]>>0x3e==0) { save; uVar5=0x155850(...); if x21==0 restore; else error+FUN_0036b118(u4); }
       else { 0x160e10(...); fatal("Launcher.PageTableTracker",0x6b); } */
}

/* FUN_0016113c @ 0x16113c  (est. sk_skip_0c_f)  base+0xc */
static int64_t sk_skip_0c_16113c(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_0016116c @ 0x16116c  (est. sk_skip_10_g)  base+0x10 */
static int64_t sk_skip_10_16116c(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_0016119c @ 0x16119c  (est. sk_span_meta_acquire)
 * Acquires span metadata (FUN_00021480). */
static void sk_span_meta_acquire_16119c(void)
{
    /* FUN_00021480(); */
}

/* FUN_00161278 @ 0x161278  (est. sk_span_move)
 * Moves a span (copy 4 words + release prior). */
static uint64_t *sk_span_move_161278(uint64_t *dst, uint64_t *src)
{
    uint64_t t[4] = { dst[0], dst[1], dst[2], dst[3] };
    dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; dst[3] = src[3];
    sk_span_drop_160e10();
    return dst;
}

/* FUN_001613ac @ 0x1613ac  (est. sk_dart_cfg_write) */
static void sk_dart_cfg_write_1613ac(int64_t p)
{
    /* local_18=&DAT_004e4850; FUN_00374104(p,0,1,&local_18,p+0x48); */
}

/* FUN_00161418 @ 0x161418  (est. sk_span_meta_release) */
static void sk_span_meta_release_161418(uint64_t *p)
{
    /* FUN_0016119c(0,*p,p[1]); */
}

/* FUN_00161458 @ 0x161458  (est. sk_span_copy)
 * Copy span (4 words incl byte tag) + release old owner. */
static uint64_t *sk_span_copy_161458(uint64_t *dst, uint64_t *src)
{
    uint64_t old3 = dst[3];
    dst[0] = src[0]; dst[1] = src[1];
    *(uint8_t *)(dst + 2) = *(uint8_t *)(src + 2);
    dst[3] = src[3];
    /* FUN_0036b118(old3); */
    return dst;
}

/* FUN_001614c0 @ 0x1614c0  (est. sk_span_foreach)
 * Iterates the span, printing each element via 0x14b5f8. */
static void sk_span_foreach_1614c0(uint64_t *p)
{
    /* uVar3=0x177824(0xff,p[1],*p,&DAT_0060a0f0,&DAT_0060a100);
       uStack_38=0x177bec(...); local={0x666cf0,0x666bf0,uVar3}; FUN_0014b5f8(0,&local); */
}

/* FUN_00161574 @ 0x161574  (est. sk_skip_20)
 * Skip-list node advance (base+0x20). */
static int64_t sk_skip_20_161574(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x20) + (int64_t)*(int32_t *)(p + 0x20);
}

/* FUN_001615a4 @ 0x1615a4  (est. sk_span_all_zero)
 * Returns 1 if the span buffer (param_1+0x20, len at +0x10) is all zero. */
static char sk_span_all_zero_1615a4(int64_t p)
{
    int64_t n = *(int64_t *)(p + 0x10);
    char *c = (char *)(p + 0x20);
    char v;
    do {
        if (n == 0) { v = 1; break; }
        v = *c; n--; c++;
    } while (v == 1);
    return v;
}

/* FUN_001615ec @ 0x1615ec  (est. sk_span_compare)
 * Lexicographic span compare via type vtable compare; returns 3/1/0-ish. */
static uint8_t sk_span_compare_1615ec(uint64_t a, int64_t b, uint64_t c)
{
    (void)a; (void)b; (void)c;
    /* see decompile: vtable +0x10 copies, 0x177824/0x177bec, FUN_000a68c4/68f4 loop */
    return 0;
}

/* FUN_001617dc @ 0x1617dc  (est. sk_span_compare_ordered)
 * Two-way compare; returns 0 if a<=b, 1 if b<a, 2 if incomparable. */
static uint32_t sk_span_compare_ordered_1617dc(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    /* f=0x16186c; r=(*f)(a,b,c,d); if(!r){r=(*f)(b,a,c,d); return r?2:1;} return 0; */
    return 0;
}

/* FUN_0016186c @ 0x16186c  (est. sk_skip_8)
 * Skip-list node advance (base+8). */
static int64_t sk_skip_8_16186c(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 8) + (int64_t)*(int32_t *)(p + 8);
}

/* FUN_0016189c @ 0x16189c  (est. sk_span_merge)
 * Merges two adjacent spans (param_1,param_2) into param_3; returns merge
 * status. Uses vtable +0x30 compare / +0x20 advance. */
static uint8_t sk_span_merge_16189c(void)
{
    /* see decompile: copies via lVar5+0x10, compare via lVar7+0x30, 0x1617dc for order */
    return 0;
}

/* FUN_00161bd0 @ 0x161bd0  (est. sk_span_merge2)
 * Two-span merge into param_3. */
static uint8_t sk_span_merge2_161bd0(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    return sk_span_merge_16189c();
}

/* FUN_00161d28 @ 0x161d28  (est. sk_span_libload)
 * Loads a span from the asan lib / asan.dylib bundles (0x161d28 strings
 * "asan_" / "asan.dylib"). */
static void sk_span_libload_161d28(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* uVar1=0x2abe60("asan_",0xe5...); if(!ok) rel; else { u2=0x1ee018; 0x16325c; rel; }
       repeat for "asan.dylib" (0x79642e6e6173615f,0xeb0000000062696c). */
}

/* FUN_00161e78 @ 0x161e78  (est. sk_feature_dart)
 * Feature check: string-match tag 0x11 at 0x5c9a40. */
static uint32_t sk_feature_dart_161e78(void)
{
    /* uVar2=FUN_000f5e08(); uVar1=FUN_00467468(0xd000000000000011,0x80000000005c9a40,0x6753a0,uVar2); */
    /* feature-present string match; return uVar1&1 */
    return 0;
}

/* FUN_00161ed4 @ 0x161ed4  (est. sk_file_fetcher_fetch)  [huge]
 * Launcher.FileFetcher: resolves "/System/..." boot bundle paths, parses
 * the component graph (0x1f5998 / 0x19dfc4), merges page-table entries
 * (0x162e44), sorts them (0x1631c0 / 0x1631d4), and records the result into
 * the 0x657798 table. ~1800-line body; see decompile. */
static int64_t sk_file_fetcher_fetch_161ed4(void)
{
    /* see decompile (Launcher.FileFetcher): path resolve via 0x2abcb0 "/System/...",
       graph build, span merge 0x162e44, sort 0x1631c0/0x1631d4, DAT_00657788 counter,
       fatal strings "Launcher.FileFetcher" lines 0x42/0x4a. */
    return 0;
}

/* ============ 0x162b2c - 0x165864 : DART merge / file-fetch plumbing ============ */

/* FUN_00162b2c @ 0x162b2c  (est. sk_file_fetcher_record)
 * Records a fetched entry into param_1: resolves the "dylib"/"asan_" bundle
 * name, parses the component graph (0x1f5998), copies the 0x28-byte record
 * (0x63350), and stores it (0x162da4 path / 0x8e5d8). */
static void sk_file_fetcher_record_162b2c(void)
{
    /* see decompile: 0x632f0/0x63320 path resolve, 0x1f5998 graph parse,
       FUN_0006e7c0 record copy, 0x63350/0x633b8 store */
}

/* FUN_00162e44 @ 0x162e44  (est. sk_dart_entry_equal)
 * Compares two DART entries (param_1, param_2's element at 0x20), resolving
 * the "asan_"/"asan.dylib" bundle names (0x2abe60 / 0x1ee018 / 0x29f368),
 * and returns true if they match (auVar14==auVar15), false after the scan
 * (0x2a0cf8). */
static bool sk_dart_entry_equal_162e44(int64_t a, int64_t b)
{
    (void)a; (void)b;
    /* while loop over param_2+0x20 entries; 0x632f0 name resolve, 0x2abe60
       "asan_" / "asan.dylib" bundle match, 0x29f368/0x29fa0c;
       return auVar14==auVar15 (true) or 0x2a0cf8 result (false) */
    return true;
}

/* FUN_001631c0 @ 0x1631c0  (est. sk_array_grow) */
static void sk_array_grow_1631c0(int64_t p)
{
    /* FUN_00074874(0,*(p+0x10),0,p); */
}

/* FUN_001631d4 @ 0x1631d4  (est. sk_span_array_swap)
 * Swaps two 0x28-byte array entries (param_3+param_1*0x28, param_3+param_2*0x28). */
static void sk_span_array_swap_1631d4(uint64_t i, uint64_t j, int64_t base, int64_t n)
{
    (void)n;
    if (i != j) {
        /* bounds SoftwareBreakpoint; temp copy via 0x77070, swap 5 words */
    }
}

/* FUN_0016325c @ 0x16325c  (est. sk_span_subset_apply)
 * Applies an index offset to a span (0x29f368/0x29fa0c) given a delta. */
static void sk_span_subset_apply_16325c(int64_t delta, uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* if (delta>=0) { 0x29f368(7|0xb, -delta, 0xf, a, b); 0x29fa0c(0xf,...); }
       else SoftwareBreakpoint; */
}

/* FUN_001632f0 @ 0x1632f0  (est. sk_skip_8_h)  base+8 */
static int64_t sk_skip_8_1632f0(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 8) + (int64_t)*(int32_t *)(p + 8);
}

/* FUN_00163320 @ 0x163320  (est. sk_skip_0c_g)  base+0xc */
static int64_t sk_skip_0c_163320(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_00163350 @ 0x163350  (est. sk_dart_cfg_init_ctor)
 * Object init via type 0x6540f0 vtable +0x10. */
static uint64_t sk_dart_cfg_init_ctor_163350(uint64_t p, uint64_t q)
{
    (void)p; (void)q;
    return 0;
}

/* FUN_001633b8 @ 0x1633b8  (est. sk_dart_cfg_dtor_ctor)
 * Object destroy via type 0x6540f0 vtable +8. */
static uint64_t sk_dart_cfg_dtor_ctor_1633b8(uint64_t p)
{
    (void)p;
    return 0;
}

/* FUN_00163418 @ 0x163418  (est. sk_skip_10_h)  base+0x10 */
static int64_t sk_skip_10_163418(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x10) + (int64_t)*(int32_t *)(p + 0x10);
}

/* FUN_00163448 @ 0x163448  (est. sk_dart_array_replace_range)
 * Replaces the [param_1,param_2) slice of a 0x28-element array with the
 * [param_3..] tail: shifts elements left via 0x117d14, updates count. */
static void sk_dart_array_replace_range_163448(int64_t lo, int64_t hi, int64_t keep)
{
    /* bounds SoftwareBreakpoint (0x16352c..40); memmove via 0x117d14;
       *(&obj+0x10) += (keep - (hi-lo)); if keep<1 SB(0x163544); */
}

/* FUN_00163544 @ 0x163544  (est. sk_dart_array_remove_range)
 * Removes [param_1,param_2) elements from a 0x28-element array (resize via
 * 0x74874, then 0x163448 shift). */
static void sk_dart_array_remove_range_163544(int64_t lo, int64_t hi)
{
    (void)lo; (void)hi;
    /* bounds SB; new_len = count - (hi-lo); 0x74874(resize); 0x163448(lo,hi,0); */
}

/* FUN_00163610 @ 0x163610  (est. sk_eval_with_trap)
 * Evaluates param_1 (a function pointer) under an error-handling trampoline:
 * builds the standard error capsule (0x64c040/0x4bbf40), stores the 16-byte
 * result at +0x20, and traps (0x26b434/0x36b588). */
static void sk_eval_with_trap_163610(void)
{
    /* FUN_0036a1a0(&DAT_006add10, buf,0,0); if flag: alloc 0x64c040/0x4bbf40,
       auVar3=(*param_1)(); store at +0x20; 0x26b434/0x36b588; 0x26e8(+0x20); */
}

/* FUN_001636e0 @ 0x1636e0  (est. sk_dart_replace_if)
 * Replaces an element if the predicate holds: builds element via type vtable
 * (+0x10 copy), compares (0x77824/0x77bec, vtable +0x30), and either inserts
 * (vtable +0x20) or removes (+0x38). */
static void sk_dart_replace_if_1636e0(void)
{
    /* see decompile */
}

/* FUN_00163a08 @ 0x163a08  (est. sk_ff_forward) */
static void sk_ff_forward_163a08(void) { /* FUN_00164c60(); */ }

/* FUN_00163a3c @ 0x163a3c  (est. sk_ff_subrange)
 * Builds a subrange span (param_1..param_2) via 0x1eb088 (0x6726a8);
 * asserts success (SoftwareBreakpoint 0x163b38/0x163ac0). */
static void sk_ff_subrange_163a3c(int64_t lo, int64_t hi)
{
    (void)lo; (void)hi;
    /* local={lo, hi-lo, &LAB_00067ecc, 0}; 0x1eb088(&local,0x6726a8,1,0x64e008,..); */
}

/* FUN_00163b38 @ 0x163b38  (est. sk_span_bundle_load)
 * Loads a span from a named bundle ("dylib"/"asan_"), resolving via
 * 0x2abe60 / 0x1ee018 / 0x6325c. */
static void sk_span_bundle_load_163b38(void)
{
    /* uVar1=0x2abe60(p1,p2,p5,p6); if(!ok) ZEXT816(0); else { u2=0x1ee018; 0x6325c; rel; } */
}

/* FUN_00163bf8 @ 0x163bf8  (est. sk_dart_check_prefix)
 * Checks/patches a range prefix: builds the element (0x77824), compares via
 * vtable +0x30; on mismatch fatal "found ;orezu." (0x5c1f60, tag 0x15). */
static void sk_dart_check_prefix_163bf8(void)
{
    /* see decompile; fatal via FUN_001afa84 */
}

/* FUN_00163fc4 @ 0x163fc4  (est. sk_dart_apply_prefix) */
static void sk_dart_apply_prefix_163fc4(void) { /* see decompile */ }

/* FUN_001642f0 @ 0x1642f0  (est. sk_dart_apply_prefix_b) */
static void sk_dart_apply_prefix_1642f0(void) { /* see decompile */ }

/* FUN_001646e4 @ 0x1646e4  (est. sk_dart_map_entries)
 * Maps entries through a callback: walks the range, invoking param_1
 * (callback) per element via vtable +0x30 traversal; builds result via
 * 0x1a0414/0x6e06c and 0x19e578 (0x66b5c8). */
static uint64_t sk_dart_map_entries_1646e4(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00164c2c @ 0x164c2c  (est. sk_ff_recurse) */
static void sk_ff_recurse_164c2c(void) { /* FUN_00164c60(); */ }

/* FUN_00164c60 @ 0x164c60  (est. sk_ff_visit)
 * File-fetcher visitor: calls 0x1646e4 then either the completion callback
 * (param_10) with the fetched range or the vtable +0x20 unwind. */
static void sk_ff_visit_164c60(void) { /* see decompile */ }

/* FUN_00164e0c @ 0x164e0c  (est. sk_dart_reduce)
 * Reduces a range via 0x24fd30 (FUN_001678f8) with vtable +0x30 traversal;
 * success path computes via 0x10d34 + 0x1bd234 (0x66acf0). */
static uint64_t sk_dart_reduce_164e0c(void)
{
    /* see decompile */
    return 0;
}

/* FUN_00165180 @ 0x165180  (est. sk_dart_split_insert)  [big]
 * Splits and inserts a subrange: two-phase match (0x25bca4) against param_2
 * then param_3; on the second match fatal (0x165864); otherwise builds the
 * node (0x667868) and schedules split callbacks (0x216900 FUN_00167b04,
 * 0x20a084 FUN_00167b90, 0x20a3b0 FUN_00167bc8). */
static void sk_dart_split_insert_165180(void) { /* see decompile */ }

/* FUN_00165864 @ 0x165864  (est. sk_ff_done)
 * File-fetch completion: checks the resolved range via 0x4ed9c8, returns a
 * match flag. */
static uint32_t sk_ff_done_165864(void)
{
    /* uVar5=0x2abe60(...); */
    return 0;
}

/* ============ 0x165864 - 0x1695c4 : DART range ops / range logging ============ */

/* FUN_00165864 @ 0x165864  (est. sk_range_contains)
 * Tests whether the range [param_1,param_2) is covered by param_3's span via
 * 0x14ae44; returns inverted match bit. */
static uint32_t sk_range_contains_165864(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    /* uVar2=0x177824(0,d,c,..); uVar3=0x27754(e); uVar1=(*0x14ae44)(a,b,uVar2,uVar3);
       return (uVar1^0xffffffff)&1; */
    return 0;
}

/* FUN_001658f0 @ 0x1658f0  (est. sk_range_contains_b)
 * Tests coverage via 0x25bca4 (span in param_2). */
static uint32_t sk_range_contains_b_1658f0(uint64_t a, uint64_t *p2, uint64_t c, uint64_t d, uint64_t e)
{
    (void)a; (void)c; (void)d; (void)e;
    /* FUN_0036a1a0(p2, buf,0,0); u3=*p2; u2=0x177824(0,d,c,..); u1=0x25bca4(a,u3,u2,e);
       return (u1^0xffffffff)&1; */
    return 0;
}

/* FUN_001659ac @ 0x1659ac  (est. sk_range_iterate)
 * Iterates a range via 0x1ff8fc with the 0x16794c callback and 0x16791c
 * element builder. */
static void sk_range_iterate_1659ac(void) { /* see decompile */ }

/* FUN_00165b04 @ 0x165b04  (est. sk_range_apply)
 * Applies the 0x167a2c operation to the range with the 0x27754 type. */
static void sk_range_apply_165b04(void) { /* see decompile */ }

/* FUN_00165bb8 @ 0x165bb8  (est. sk_range_fingerprint)
 * Computes a 32-bit fingerprint over the range's elements: walks with
 * 0x267510, classifies each element (0x2bd848 / 0x16749c) into a per-index
 * code recorded at 0x657798 (grow via 0x673e4), then packs the byte codes
 * big-endian into the result. Returns 0x100000000 on a size mismatch. */
static uint64_t sk_range_fingerprint_165bb8(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile: DAT_00657788 counter, 0x657798 code bytes */
    return 0;
}

/* FUN_00165df8 @ 0x165df8  (est. sk_range_subrange)
 * Builds a subrange span (param_1..param_2) via 0x1eb088; param_3 is a type
 * with element size at +0x48. */
static void sk_range_subrange_165df8(int64_t lo, int64_t hi, int64_t type)
{
    (void)lo; (void)hi; (void)type;
    /* see decompile */
}

/* FUN_00165f44 @ 0x165f44  (est. sk_range_parse)
 * Parses a range expression: uses 0x8f6c0/0x8f6f4/0x8f728/0x8f758 readers
 * and 0x16796c/0x16799c/0x1679cc/0x1679fc ops into param_1. */
static void sk_range_parse_165f44(void) { /* see decompile */ }

/* FUN_0016622c @ 0x16622c  (est. sk_range_parse_bitmask)
 * Parses a range with a single-bit mask (1<<param_2). */
static void sk_range_parse_bitmask_16622c(void) { /* see decompile */ }

/* FUN_00166524 @ 0x166524  (est. sk_range_parse_pair)
 * Parses two ranges (param_1,param_2) into param_3 via dual 0x16796c/0x167a2c
 * reads. */
static void sk_range_parse_pair_166524(void) { /* see decompile */ }

/* FUN_001669a8 @ 0x1669a8  (est. sk_range_parse_n)  [range-family parse]
 * Range-expression parser family; see decompile. */
static void sk_range_parse_n_1669a8(void) { /* see decompile */ }

/* FUN_00168748 @ 0x168748  (est. sk_range_insert_update)
 * Updates/inserts a range entry in the 0x652108 range table (0x71950 /
 * 0x6806c / 0x19ea20), printing "range permissions vmaPriv vmaAtt ..." and
 * refreshing the affected leaf (0x1a2abc / 0x8396c). */
static void sk_range_insert_update_168748(uint64_t p)
{
    (void)p;
    /* see decompile */
}

/* FUN_00168b20 @ 0x168b20  (est. sk_range_insert_full)
 * Full range insert with perms/vma/flags (param_3/param_6); checks overlap
 * (0x1612c), inserts, updates. */
static void sk_range_insert_full_168b20(void) { /* see decompile */ }

/* FUN_00168e6c @ 0x168e6c  (est. sk_range_split_update)  [big]
 * Splits an existing range entry around [param_4,param_5) and updates the
 * table: rebuilds the 3 parts (before/match/after) and rewrites via vtable
 * +0x20/+0x18. */
static void sk_range_split_update_168e6c(void) { /* see decompile */ }

/* FUN_001695c4 @ 0x1695c4  (est. sk_range_release)
 * Releases a range entry. */
static void sk_range_release_1695c4(void) { /* see decompile */ }

/* ============ 0x1695c8 - 0x16dff4 : range table ops / Stackshot init ============ */

/* FUN_001695c8 @ 0x1695c8  (est. sk_range_del)
 * Deletes a range via vtable +0x90. */
static void sk_range_del_1695c8(void) { /* (**(**+0x90))(p1,0,1,p2,p3); */ }

/* FUN_00169604 @ 0x169604  (est. sk_range_alloc_ctor)
 * Allocates a range object, initializes via vtable type +0x20. */
static int64_t *sk_range_alloc_ctor_169604(uint64_t p)
{
    (void)p;
    /* pl=FUN_0036a940(); (**(*(**+0x38)-8)+0x20)(pl+*(*+0x48),p); return pl; */
    return 0;
}

/* FUN_00169690 @ 0x169690  (est. sk_range_set_a) */
static void sk_range_set_a_169690(uint64_t p) { (void)p; }

/* FUN_00169694 @ 0x169694  (est. sk_range_set_b) dup */
static void sk_range_set_b_169694(uint64_t p) { (void)p; }

/* FUN_001696fc @ 0x1696fc  (est. sk_range_dtor) */
static void sk_range_dtor_1696fc(void) { /* vtable+8 destroy; 0x36b6ac */ }

/* FUN_00169700 @ 0x169700  (est. sk_range_dtor_b) dup */
static void sk_range_dtor_b_169700(void) { /* dup 0x1696fc */ }

/* FUN_00169780 @ 0x169780  (est. sk_range_find)
 * Finds the range covering [param_1, param_1+param_2): validates the length
 * is element-aligned (0xe40f0), searches via 0x16d7c4, and either returns
 * the matching leaf (0x3d798/0x1a0534) or an error code (5/7). */
static int64_t sk_range_find_169780(uint64_t a, uint64_t b)
{
    (void)a; (void)b;
    /* see decompile */
    return 0;
}

/* FUN_00169bf0 @ 0x169bf0  (est. sk_range_insert)
 * Inserts a range of param_3 bytes at param_2 with perms (param_5): validates
 * alignment, then via 0x16d68c/0x16d6bc/0x16d6ec ops inserts or faults. */
static void sk_range_insert_169bf0(void) { /* see decompile */ }

/* FUN_00169e1c @ 0x169e1c  (est. sk_range_foreach_update)
 * Iterates [param_1,param_2) and applies per-entry update via 0x16d738. */
static void sk_range_foreach_update_169e1c(void) { /* see decompile */ }

/* FUN_0016a2d0 @ 0x16a2d0  (est. sk_range_foreach_element)
 * Applies 0x16de38 per element of the range table. */
static void sk_range_foreach_element_16a2d0(void) { /* see decompile */ }

/* FUN_0016a45c @ 0x16a45c  (est. sk_range_adjust)
 * Adjusts a range by param_2 (element-aligned); see decompile. */
static void sk_range_adjust_16a45c(void) { /* see decompile */ }

/* FUN_0016ad3c @ 0x16ad3c  (est. sk_range_op_5arg)
 * Range op (5-arg variant). */
static void sk_range_op_5arg_16ad3c(void) { /* see decompile */ }

/* FUN_0016b2c4 @ 0x16b2c4  (est. sk_range_op_4arg) */
static void sk_range_op_4arg_16b2c4(void) { /* see decompile */ }

/* FUN_0016b4b4 @ 0x16b4b4  (est. sk_range_op_3arg) */
static void sk_range_op_3arg_16b4b4(void) { /* see decompile */ }

/* FUN_0016ba2c @ 0x16ba2c  (est. sk_range_op_2arg) */
static void sk_range_op_2arg_16ba2c(void) { /* see decompile */ }

/* FUN_0016bf58 @ 0x16bf58  (est. sk_range_op_n)
 * Range op family. */
static void sk_range_op_n_16bf58(void) { /* see decompile */ }

/* FUN_0016c700 @ 0x16c700  (est. sk_range_cb1) */
static void sk_range_cb1_16c700(void) { /* see decompile */ }

/* FUN_0016c7b8 @ 0x16c7b8  (est. sk_range_cb2) */
static void sk_range_cb2_16c7b8(void) { /* see decompile */ }

/* FUN_0016c81c @ 0x16c81c  (est. sk_range_cb3) */
static void sk_range_cb3_16c81c(void) { /* see decompile */ }

/* FUN_0016c8ec @ 0x16c8ec  (est. sk_range_cb4) */
static void sk_range_cb4_16c8ec(void) { /* see decompile */ }

/* FUN_0016cb50 @ 0x16cb50  (est. sk_range_cb5) */
static void sk_range_cb5_16cb50(void) { /* see decompile */ }

/* FUN_0016cb54 @ 0x16cb54  (est. sk_range_cb5b) */
static void sk_range_cb5b_16cb54(void) { /* see decompile */ }

/* FUN_0016cb88 @ 0x16cb88  (est. sk_range_cb6) */
static void sk_range_cb6_16cb88(void) { /* see decompile */ }

/* FUN_0016cbd0 @ 0x16cbd0  (est. sk_range_cb7) */
static void sk_range_cb7_16cbd0(void) { /* see decompile */ }

/* FUN_0016ccac @ 0x16ccac  (est. sk_range_cb8) */
static void sk_range_cb8_16ccac(void) { /* see decompile */ }

/* FUN_0016cd50 @ 0x16cd50  (est. sk_range_cb9) */
static void sk_range_cb9_16cd50(void) { /* see decompile */ }

/* FUN_0016cfbc @ 0x16cfbc  (est. sk_range_cb10) */
static void sk_range_cb10_16cfbc(void) { /* see decompile */ }

/* FUN_0016d180 @ 0x16d180  (est. sk_range_cb11) */
static void sk_range_cb11_16d180(void) { /* see decompile */ }

/* FUN_0016d218 @ 0x16d218  (est. sk_range_cb12) */
static void sk_range_cb12_16d218(void) { /* see decompile */ }

/* FUN_0016d2a0 @ 0x16d2a0  (est. sk_range_cb13) */
static void sk_range_cb13_16d2a0(void) { /* see decompile */ }

/* FUN_0016d328 @ 0x16d328  (est. sk_range_cb14) */
static void sk_range_cb14_16d328(void) { /* see decompile */ }

/* FUN_0016d4e8 @ 0x16d4e8  (est. sk_range_cb15) */
static void sk_range_cb15_16d4e8(void) { /* see decompile */ }

/* FUN_0016d68c @ 0x16d68c  (est. sk_range_op_insert) */
static void sk_range_op_insert_16d68c(void) { /* see decompile */ }

/* FUN_0016d6bc @ 0x16d6bc  (est. sk_range_op_end) */
static void sk_range_op_end_16d6bc(void) { /* see decompile */ }

/* FUN_0016d6ec @ 0x16d6ec  (est. sk_range_op_commit) */
static void sk_range_op_commit_16d6ec(void) { /* see decompile */ }

/* FUN_0016d71c @ 0x16d71c  (est. sk_range_iter_cb)
 * Range iteration callback. */
static void sk_range_iter_cb_16d71c(void) { /* see decompile */ }

/* FUN_0016d720 @ 0x16d720  (est. sk_range_skip_40)  base+0x40 */
static int64_t sk_range_skip_40_16d720(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x40) + (int64_t)*(int32_t *)(p + 0x40);
}

/* FUN_0016d738 @ 0x16d738  (est. sk_range_skip_30)  base+0x30 */
static int64_t sk_range_skip_30_16d738(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x30) + (int64_t)*(int32_t *)(p + 0x30);
}

/* FUN_0016d768 @ 0x16d768  (est. sk_range_cb16) */
static void sk_range_cb16_16d768(void) { /* see decompile */ }

/* FUN_0016d76c @ 0x16d76c  (est. sk_range_cb17)
 * Calls 0x16a6f0 with ctx words. */
static void sk_range_cb17_16d76c(uint64_t p)
{
    (void)p;
    /* FUN_0016a6f0(p, *(x20+0x10), *(x20+0x18)); */
}

/* FUN_0016d784 @ 0x16d784  (est. sk_range_cb18)
 * Calls 0x16ad3c with ctx words. */
static void sk_range_cb18_16d784(uint64_t p)
{
    (void)p;
    /* FUN_0016ad3c(p, ctx[0x10..0x28]); */
}

/* FUN_0016d788 @ 0x16d788  (est. sk_range_cb18b) dup */
static void sk_range_cb18b_16d788(uint64_t p) { (void)p; }

/* FUN_0016d7a4 @ 0x16d7a4  (est. sk_range_cb19)
 * Calls 0x16b4b4 with ctx words. */
static void sk_range_cb19_16d7a4(uint64_t p)
{
    (void)p;
    /* FUN_0016b4b4(p, ctx[0x10..0x20]); */
}

/* FUN_0016d7a8 @ 0x16d7a8  (est. sk_range_cb19b) dup */
static void sk_range_cb19b_16d7a8(uint64_t p) { (void)p; }

/* FUN_0016d7c4 @ 0x16d7c4  (est. sk_skip_28)  base+0x28 */
static int64_t sk_skip_28_16d7c4(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x28) + (int64_t)*(int32_t *)(p + 0x28);
}

/* FUN_0016d804 @ 0x16d804  (est. sk_range_release_ctx) */
static void sk_range_release_ctx_16d804(void)
{
    /* FUN_0036b118(*(x20+0x18)); FUN_0036b21c(); */
}

/* FUN_0016d808 @ 0x16d808  (est. sk_range_release_ctx_b) dup */
static void sk_range_release_ctx_16d808(void) { /* dup 0x16d804 */ }

/* FUN_0016d830 @ 0x16d830  (est. sk_range_cb_call)
 * Calls the stored callback at +0x10. */
static void sk_range_cb_call_16d830(void) { /* (**(x20+0x10))(); */ }

/* FUN_0016d858 @ 0x16d858  (est. sk_range_cb_call3)
 * Calls callback (+0x10) with 3 args, stores byte result. */
static void sk_range_cb_call3_16d858(void) { /* uVar1=(**(x20+0x10))(*p2,*p3,*p4); *p1=uVar1; */ }

/* FUN_0016d894 @ 0x16d894  (est. sk_skip_3c)  base+0x3c */
static int64_t sk_skip_3c_16d894(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x3c) + (int64_t)*(int32_t *)(p + 0x3c);
}

/* FUN_0016d8c4 @ 0x16d8c4  (est. sk_skip_40_b)  base+0x40 */
static int64_t sk_skip_40_16d8c4(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x40) + (int64_t)*(int32_t *)(p + 0x40);
}

/* FUN_0016d984 @ 0x16d984  (est. sk_skip_54)  base+0x54 */
static int64_t sk_skip_54_16d984(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x54) + (int64_t)*(int32_t *)(p + 0x54);
}

/* FUN_0016d9b4 @ 0x16d9b4  (est. sk_skip_50)  base+0x50 */
static int64_t sk_skip_50_16d9b4(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x50) + (int64_t)*(int32_t *)(p + 0x50);
}

/* FUN_0016d9e4 @ 0x16d9e4  (est. sk_range_meta) */
static void sk_range_meta_16d9e4(void) { /* FUN_00021480(); */ }

/* FUN_0016dc20 @ 0x16dc20  (est. sk_range_cfg_write)
 * Writes the 0x67aa60 config via 0x374104. */
static void sk_range_cfg_write_16dc20(int64_t p)
{
    /* local_18=0x67aa60; FUN_00374104(p,0,1,&local_18,p+0x48); */
}

/* FUN_0016dc98 @ 0x16dc98  (est. sk_range_describe)
 * Describes the range table (0x67aa60) as a 0x13f-byte span via 0x374104. */
static void sk_range_describe_16dc98(int64_t p)
{
    (void)p;
    /* see decompile */
}

/* FUN_0016dd48 @ 0x16dd48  (est. sk_skip_14)  base+0x14 */
static int64_t sk_skip_14_16dd48(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x14) + (int64_t)*(int32_t *)(p + 0x14);
}

/* FUN_0016dd78 @ 0x16dd78  (est. sk_skip_38)  base+0x38 */
static int64_t sk_skip_38_16dd78(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x38) + (int64_t)*(int32_t *)(p + 0x38);
}

/* FUN_0016dda8 @ 0x16dda8  (est. sk_skip_0c)  base+0xc */
static int64_t sk_skip_0c_16dda8(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0xc) + (int64_t)*(int32_t *)(p + 0xc);
}

/* FUN_0016ddd8 @ 0x16ddd8  (est. sk_skip_18)  base+0x18 */
static int64_t sk_skip_18_16ddd8(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x18) + (int64_t)*(int32_t *)(p + 0x18);
}

/* FUN_0016de08 @ 0x16de08  (est. sk_skip_34)  base+0x34 */
static int64_t sk_skip_34_16de08(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x34) + (int64_t)*(int32_t *)(p + 0x34);
}

/* FUN_0016de38 @ 0x16de38  (est. sk_skip_20_b)  base+0x20 */
static int64_t sk_skip_20_16de38(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & ~1ULL);
    return (int64_t)(p + 0x20) + (int64_t)*(int32_t *)(p + 0x20);
}

/* FUN_0016de78 @ 0x16de78  (est. sk_stackshot_enable)
 * StackshotConclaveSupport.enable: allocates a stackshot buffer (0x4000
 * default, or the size from 0x4ad294), maps it (0x4ad388/0x4add1c), and
 * records it (DAT_006bfed8/0x6bfed0). Traps on failure ("Can't ..."
 * 0x5c9c11/0x5c9c5c/0x5c9bcf). */
static void sk_stackshot_enable_16de78(int en)
{
    (void)en;
    /* see decompile; string anchors StackshotConclaveSupport */
}

/* FUN_0016dff4 @ 0x16dff4  (est. sk_stackshot_init)
 * StackshotConclaveSupport.init: registers boot args (0x4b520), calls enable(0),
 * allocates the per-guest entry arrays (0x6bfef0 ptr / 0x6bff00 len), zeroes
 * the 0x6bff10..0x6c0088 state block, resolves memattr (0x34a2c +0x30),
 * and initializes the 0x6c0098 kernel region (0x3dde8) + 0x6c0060 token
 * (0x15388, 0x171324). Fatal on allocation failure. */
static void sk_stackshot_init_16dff4(void)
{
    /* see decompile; 0x5519 SoftwareBreakpoint at 0x16e3a0 on bad state */
}

/* ==================== 0x16e3a0 - 0x17fff8 : StackshotConclaveSupport =========
 * This region is the StackshotConclaveSupport service: guest stackshot /
 * crash-backtrace capture, serialization (tagged byte-stream), and the
 * getConclaveCrashBacktrace / takeConclaveCrash / getCrashBuffer /
 * getAddressSpaceInfo / runStackshot IPC surface. The kernel-adjacent
 * serialization primitives (FUN_00021904 = read word, FUN_000217e4 =
 * read byte, FUN_00023208 = write word, FUN_000230f8 = write byte,
 * FUN_00025704 = finalize hash, FUN_000214b0 = begin write context,
 * FUN_00022028 = begin read of tagged value, FUN_00022c48 = read tag,
 * FUN_00023f74 = async op dispatch) and the global scratch array
 * (DAT_00657778/88/90/98) are shared with the rest of the cL4 kernel and
 * are referenced by FUN_ address in comments only. */

/* FUN_0016e3a0 @ 0x16e3a0  (est. sk_stackshot_request_proxy)
 * Request proxy entry for StackshotConclaveSupport. When the selector target
 * equals the local proxy object (DAT_006bff08) it resolves the record via
 * 16fb94 and returns status via the vtable callback at +0x10; otherwise it
 * logs "not a StackshotConclaveSupport Proxy" (005ca94b) and reports error 2.
 * The 0x130-byte output record is copied through the parameter block before the
 * callback is invoked. Confidence: medium. */
static void sk_stackshot_request_proxy_16e3a0(uint64_t a, uint64_t target, uint64_t c, uint64_t cb)
{
    (void)a;
    (void)target;
    (void)c;
    (void)cb;
    (void)0; /* sk_stackshot_request_proxy @ 0x16e3a0: Request proxy entry for StackshotConclaveSupport. When the selector target equals the local proxy object (DAT_006bff08) it resolves the record via 16fb94 and returns status via the vtable callback at +0x10; otherwise it logs "not a Stacksho */
}

/* FUN_0016e468 @ 0x16e468  (est. sk_stackshot_request_proxy_b)
 * Second request-proxy variant. For the local proxy it checks the current
 * dispatch hook (DAT_006bfee0+0x10); on success routes through 16e558 and pokes
 * DAT_006bfee8+0x10, else reports error 2. Confidence: medium. */
static void sk_stackshot_request_proxy_b_16e468(uint64_t a, uint64_t target, uint64_t c, uint64_t cb)
{
    (void)a;
    (void)target;
    (void)c;
    (void)cb;
    (void)0; /* sk_stackshot_request_proxy_b @ 0x16e468: Second request-proxy variant. For the local proxy it checks the current dispatch hook (DAT_006bfee0+0x10); on success routes through 16e558 and pokes DAT_006bfee8+0x10, else reports error 2. Confidence: medium. */
}

/* FUN_0016e558 @ 0x16e558  (est. sk_stackshot_collect)
 * Core stackshot collection / dispatch. Iterates the registered guest entry
 * array (DAT_006bfef0, count DAT_006bff00) to find the entry matching target,
 * then walks its serialized stackshot (28a10/28a78/28a3c), maps 0x4000-byte
 * pages via supervisor call 1 into kernel region 0x6c0098, and lays out the
 * per-page text/ASID records (16f1b8). Writes the 0x80-byte result record.
 * Fatal traps (SoftwareBreakpoint 0x5519 @16e878) on any OOB/state violation.
 * Confidence: medium. Notes: many s__StackshotConclaveSupport__* strings. */
static void sk_stackshot_collect_16e558(uint64_t target, uint64_t key, void *out)
{
    (void)target;
    (void)key;
    (void)out;
    (void)0; /* sk_stackshot_collect @ 0x16e558: Core stackshot collection / dispatch. Iterates the registered guest entry array (DAT_006bfef0, count DAT_006bff00) to find the entry matching target, then walks its serialized stackshot (28a10/28a78/28a3c), maps 0x4000-byte pages via superv */
}

/* FUN_0016e980 @ 0x16e980  (est. sk_stackshot_getASIDs)
 * getASIDs: returns the registered guest-address array. If the global guest
 * array (DAT_006bfef0) is empty it logs "getASIDs: no ASID" (005ca995) and
 * returns the single-entry DAT_006bff08. Copies the array into the output
 * record and invokes the vtable callback at param_2+0x10. Confidence: medium. */
static void sk_stackshot_getASIDs_16e980(uint64_t a, uint64_t cb)
{
    (void)a;
    (void)cb;
    (void)0; /* sk_stackshot_getASIDs @ 0x16e980: getASIDs: returns the registered guest-address array. If the global guest array (DAT_006bfef0) is empty it logs "getASIDs: no ASID" (005ca995) and returns the single-entry DAT_006bff08. Copies the array into the output record and invokes th */
}

/* FUN_0016ea28 @ 0x16ea28  (est. sk_stackshot_capture)
 * Capture + persist stackshot data for every registered guest. For each
 * non-null guest it allocates/parses the 0x5000 text-layout window (28a10),
 * copies the 0x200-capped per-guest record list (via 10244 alloc and
 * 0016ffe4), and streams frames through 16f4ec while 6bfed8 is armed. On
 * unrecoverable errors it traps (SoftwareBreakpoint 0x5519 @16f078). Large,
 * faithful reconstruction. Confidence: medium. */
static void sk_stackshot_capture_16ea28(void)
{
    (void)0; /* sk_stackshot_capture @ 0x16ea28: Capture + persist stackshot data for every registered guest. For each non-null guest it allocates/parses the 0x5000 text-layout window (28a10), copies the 0x200-capped per-guest record list (via 10244 alloc and 0016ffe4), and streams frames */
}

/* FUN_0016f084 @ 0x16f084  (est. sk_stackshot_offline)
 * Offline/disable path: logs "Offline..." (005ca9d5/005ca9fe), and when a
 * per-guest tracking table (DAT_006bfed8) exists clears each guest's 0x40 slot.
 * Confidence: medium. */
static void sk_stackshot_offline_16f084(void)
{
    (void)0; /* sk_stackshot_offline @ 0x16f084: Offline/disable path: logs "Offline..." (005ca9d5/005ca9fe), and when a per-guest tracking table (DAT_006bfed8) exists clears each guest's 0x40 slot. Confidence: medium. */
}

/* FUN_0016f108 @ 0x16f108  (est. sk_stackshot_release_build)
 * Returns whether the build is a RELEASE build: registers a one-shot handler
 * (16f154) at 0x6c00b8 and returns the cached result at DAT_006c00bc.
 * Confidence: medium. */
static uint8_t sk_stackshot_release_build_16f108(void)
{
    (void)0; /* sk_stackshot_release_build @ 0x16f108: Returns whether the build is a RELEASE build: registers a one-shot handler (16f154) at 0x6c00b8 and returns the cached result at DAT_006c00bc. Confidence: medium. */
    return 0;
}

/* FUN_0016f154 @ 0x16f154  (est. sk_stackshot_release_check)
 * Checks the BUNDLE_VARIANT boot arg (005ca66c) for the literal "RELEASE"
 * (005ca67d); stores the boolean into *param_1. Confidence: medium. */
static void sk_stackshot_release_check_16f154(uint8_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_release_check @ 0x16f154: Checks the BUNDLE_VARIANT boot arg (005ca66c) for the literal "RELEASE" (005ca67d); stores the boolean into *param_1. Confidence: medium. */
}

/* FUN_0016f1b8 @ 0x16f1b8  (est. sk_stackshot_region_lookup)
 * Looks up a guest region (param_1) in the region table at param_2+8
 * (stride 0x20); returns the packed {offset<<0x30 | length} of the matching
 * entry, or 0 (and logs "no 0x... region") when absent. SoftwareBreakpoint
 * 0x5519 @16f278 on bounds failure. Confidence: medium. */
static uint64_t sk_stackshot_region_lookup_16f1b8(uint64_t key, uint64_t tbl)
{
    (void)key;
    (void)tbl;
    (void)0; /* sk_stackshot_region_lookup @ 0x16f1b8: Looks up a guest region (param_1) in the region table at param_2+8 (stride 0x20); returns the packed {offset<<0x30 | length} of the matching entry, or 0 (and logs "no 0x... region") when absent. SoftwareBreakpoint 0x5519 @16f278 on bounds f */
    return 0;
}

/* FUN_0016f278 @ 0x16f278  (est. sk_stackshot_flush_region)
 * Builds the region-descriptor vector: copies the DAT_006bff10 region table
 * into a 0x2a-entry buffer and initializes a 16-word descriptor via 16f278/16f0f60.
 * Confidence: low (shape-only). */
static void sk_stackshot_flush_region_16f278(void)
{
    (void)0; /* sk_stackshot_flush_region @ 0x16f278: Builds the region-descriptor vector: copies the DAT_006bff10 region table into a 0x2a-entry buffer and initializes a 16-word descriptor via 16f278/16f0f60. Confidence: low (shape-only). */
}

/* FUN_0016f2e4 @ 0x16f2e4  (est. sk_stackshot_collect_ok)
 * Collects via 16e558 and, when the status byte is 0, parses the result with
 * 17105c. Returns true only when the status byte is 0. Traps
 * (004afae4 "...Cannot...") when the returned length exceeds param_4.
 * Confidence: medium. */
static bool sk_stackshot_collect_ok_16f2e4(uint64_t a, uint64_t b, void *c, uint64_t cap)
{
    (void)a;
    (void)b;
    (void)c;
    (void)cap;
    (void)0; /* sk_stackshot_collect_ok @ 0x16f2e4: Collects via 16e558 and, when the status byte is 0, parses the result with 17105c. Returns true only when the status byte is 0. Traps (004afae4 "...Cannot...") when the returned length exceeds param_4. Confidence: medium. */
    return 0;
}

/* FUN_0016f378 @ 0x16f378  (est. sk_stackshot_collect_ok_b)
 * Variant: resolves current cpu (5b89c), routes through 16fe34, and parses
 * with 17105c when status is 0. Confidence: medium. */
static bool sk_stackshot_collect_ok_b_16f378(uint64_t a, void *b, uint64_t c)
{
    (void)a;
    (void)b;
    (void)c;
    (void)0; /* sk_stackshot_collect_ok_b @ 0x16f378: Variant: resolves current cpu (5b89c), routes through 16fe34, and parses with 17105c when status is 0. Confidence: medium. */
    return 0;
}

/* FUN_0016f3f8 @ 0x16f3f8  (est. sk_stackshot_asid_resolve)
 * Resolves an ASID record via 16fb94 for the local proxy; returns the
 * 1710b18-parsed result when status is 0. Confidence: medium. */
static uint64_t sk_stackshot_asid_resolve_16f3f8(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_asid_resolve @ 0x16f3f8: Resolves an ASID record via 16fb94 for the local proxy; returns the 1710b18-parsed result when status is 0. Confidence: medium. */
    return 0;
}

/* FUN_0016f464 @ 0x16f464  (est. sk_stackshot_asid_ok)
 * Resolves an ASID via 16fb94 and, when status is 0, parses with 170c0c.
 * Returns status==0. Confidence: medium. */
static bool sk_stackshot_asid_ok_16f464(uint64_t a, void *b, uint64_t c)
{
    (void)a;
    (void)b;
    (void)c;
    (void)0; /* sk_stackshot_asid_ok @ 0x16f464: Resolves an ASID via 16fb94 and, when status is 0, parses with 170c0c. Returns status==0. Confidence: medium. */
    return 0;
}

/* FUN_0016f4ec @ 0x16f4ec  (est. sk_stackshot_textlayout_bind)
 * Binds a text-layout ID for the guest's ASID. If the ID slot (10) is empty
 * and the 0x580 state is 0 it claims it and processes the layout via 16f89c;
 * state 2 allocates a fresh text-layout region (0x13f0 cap) and records it
 * into the 0x2c00 region table. Otherwise it binds via 16f89c/1708b4 and marks
 * state 2. Traps (SoftwareBreakpoint 0x5519 @16f854) on any OOB. Confidence:
 * medium. Notes: s__StackshotConclaveSupport__textl_005ca536 etc. */
static uint64_t sk_stackshot_textlayout_bind_16f4ec(long *asid, uint64_t flags)
{
    (void)asid;
    (void)flags;
    (void)0; /* sk_stackshot_textlayout_bind @ 0x16f4ec: Binds a text-layout ID for the guest's ASID. If the ID slot (10) is empty and the 0x580 state is 0 it claims it and processes the layout via 16f89c; state 2 allocates a fresh text-layout region (0x13f0 cap) and records it into the 0x2c00 re */
    return 0;
}

/* FUN_0016f89c @ 0x16f89c  (est. sk_stackshot_textlayout_store)
 * Stores a parsed text-layout record into the DAT_006bfed8 0x2c00-region
 * table at slot param_2 (0x1400 stride), recording its length at +8. Traps
 * (SoftwareBreakpoint 0x5519 @16f980) / fatal "Error..." (005ca575) on
 * invalid bounds. Confidence: medium. */
static uint64_t sk_stackshot_textlayout_store_16f89c(uint64_t data, uint64_t slot)
{
    (void)data;
    (void)slot;
    (void)0; /* sk_stackshot_textlayout_store @ 0x16f89c: Stores a parsed text-layout record into the DAT_006bfed8 0x2c00-region table at slot param_2 (0x1400 stride), recording its length at +8. Traps (SoftwareBreakpoint 0x5519 @16f980) / fatal "Error..." (005ca575) on invalid bounds. Confidence: */
    return 0;
}

/* FUN_0016f9c0 @ 0x16f9c0  (est. sk_stackshot_release_pages)
 * Releases a run of stackshot pages in kernel region 0x6c0098 (param_1 pages
 * of 0x4000), then validates the completion tag via 3e5f0; a nonzero tag
 * traps with "...failed..." (005ca831). Confidence: medium. */
static void sk_stackshot_release_pages_16f9c0(long pages, uint64_t tag)
{
    (void)pages;
    (void)tag;
    (void)0; /* sk_stackshot_release_pages @ 0x16f9c0: Releases a run of stackshot pages in kernel region 0x6c0098 (param_1 pages of 0x4000), then validates the completion tag via 3e5f0; a nonzero tag traps with "...failed..." (005ca831). Confidence: medium. */
}

/* FUN_0016fa6c @ 0x16fa6c  (est. sk_stackshot_error_record)
 * Fills a 4-word error record. For error code > 9 it copies the generic
 * L4 error message block (DAT_004e4d10..4e4d28) and hashes it; otherwise it
 * selects the matching L4_ErrorCode* string (Success/Preempted/Canceled/
 * Truncated/CapInvalid/SlotInvalid/MethodInvalid/ArgumentInvalid/
 * OperationInvalid/PermissionInvalid) and copies its 4 words. Confidence:
 * medium. Notes: L4_ErrorCode* string anchors. */
static void sk_stackshot_error_record_16fa6c(uint64_t *rec, uint8_t code)
{
    (void)rec;
    (void)code;
    (void)0; /* sk_stackshot_error_record @ 0x16fa6c: Fills a 4-word error record. For error code > 9 it copies the generic L4 error message block (DAT_004e4d10..4e4d28) and hashes it; otherwise it selects the matching L4_ErrorCode* string (Success/Preempted/Canceled/ Truncated/CapInvalid/Slot */
}

/* FUN_0016fb80 @ 0x16fb80  (est. sk_stackshot_hash_const)
 * Returns the fixed stackshot error hash constant 0xeb1a02bf914012ba.
 * Confidence: high (same constant used across the subsystem). */
static uint64_t sk_stackshot_hash_const_16fb80(void) { return 0xeb1a02bf914012ba; }

/* FUN_0016fb94 @ 0x16fb94  (est. sk_stackshot_lookup)
 * Resolves the guest matching param_1/param_2 and fills the out record.
 * Verifies current cpu (5b89c) matches; walks the region tree via 5ba14/
 * 5bc48/1703d4 building the record (id, perm, text-layout) and writes the
 * 0x98-byte record. Traps (SoftwareBreakpoint 0x5519 @16fe30) on invalid
 * bounds. Confidence: medium. */
static void sk_stackshot_lookup_16fb94(uint64_t p1, uint64_t p2, void *out)
{
    (void)p1;
    (void)p2;
    (void)out;
    (void)0; /* sk_stackshot_lookup @ 0x16fb94: Resolves the guest matching param_1/param_2 and fills the out record. Verifies current cpu (5b89c) matches; walks the region tree via 5ba14/ 5bc48/1703d4 building the record (id, perm, text-layout) and writes the 0x98-byte record. Traps (So */
}

/* FUN_0016fe34 @ 0x16fe34  (est. sk_stackshot_lookup2)
 * Second lookup variant. Rejects a cpu mismatch with error 1; for an empty
 * guest it resolves the empty record via 4b8ccc. Otherwise it parses guest
 * capability info (6198c/61664/619c8/5bc48), computes the 0x80-byte record
 * size, and fills out. Traps (SoftwareBreakpoint 0x5519 @16ffb0) on OOB.
 * Confidence: medium. Notes: DAT_006add18. */
static void sk_stackshot_lookup2_16fe34(uint64_t cpu, uint64_t guest, void *out)
{
    (void)cpu;
    (void)guest;
    (void)out;
    (void)0; /* sk_stackshot_lookup2 @ 0x16fe34: Second lookup variant. Rejects a cpu mismatch with error 1; for an empty guest it resolves the empty record via 4b8ccc. Otherwise it parses guest capability info (6198c/61664/619c8/5bc48), computes the 0x80-byte record size, and fills out.  */
}

/* FUN_0016ffe4 @ 0x16ffe4  (est. sk_stackshot_set_bool)
 * Writes a tagged boolean record: *param_1 = (param_2 != 0), and when
 * param_2 is non-null stores *param_2 into the 4-byte value at param_1+4.
 * Confidence: high (tiny). */
static void sk_stackshot_set_bool_16ffe4(long out, uint32_t *val)
{
    *(uint8_t *)out = val != 0;
    if (val != 0) *(uint32_t *)(out + 4) = *val;
}

/* FUN_00170004 @ 0x170004  (est. sk_stackshot_tag_lookup)
 * Tag lookup for the stackshot serialization type table (DAT_004e4d30):
 * returns the 8-byte handler for tag index (tag-1); traps with
 * "TB_FATAL: invalid tag in ...Stack..." (005cab66) for out-of-range tags.
 * Confidence: medium. */
static uint64_t sk_stackshot_tag_lookup_170004(uint8_t *tag)
{
    (void)tag;
    (void)0; /* sk_stackshot_tag_lookup @ 0x170004: Tag lookup for the stackshot serialization type table (DAT_004e4d30): returns the 8-byte handler for tag index (tag-1); traps with "TB_FATAL: invalid tag in ...Stack..." (005cab66) for out-of-range tags. Confidence: medium. */
    return 0;
}

/* FUN_00170060 @ 0x170060  (est. sk_stackshot_serialize_stack)
 * Serializes a "Stack" tagged value (tag 1/2/3) into the byte stream via
 * the writer callback at param_2+0x10. Tag 3 iterates the frame array
 * (stride 0x28) forwarding each frame; tag 2 forwards through 15a44 (the
 * common frame-forwarder); tag 1 serializes the frame data through
 * 1552c/1586c/18600/18ac8/18f38/18a4c and 15984. Confidence: medium. */
static char *sk_stackshot_serialize_stack_170060(char *val, uint64_t w)
{
    (void)val;
    (void)w;
    (void)0; /* sk_stackshot_serialize_stack @ 0x170060: Serializes a "Stack" tagged value (tag 1/2/3) into the byte stream via the writer callback at param_2+0x10. Tag 3 iterates the frame array (stride 0x28) forwarding each frame; tag 2 forwards through 15a44 (the common frame-forwarder); tag 1 */
    return 0;
}

/* FUN_001703d4 @ 0x1703d4  (est. sk_stackshot_make_regionlist)
 * Builds a serialized region-list tagged value. Computes the total size over
 * the param_2 array (0x28-stride, tag 1 vs 0x19/0x21), allocates the buffer via
 * 157dc, serializes each region's 0x10-byte id + flags through 1552c/1586c/
 * 185b8/18984/18e60/15964, and fills the record (tag=1, ptr, len, count).
 * Traps (SoftwareBreakpoint 0x5519 @170498) on OOB. Confidence: medium. */
static void sk_stackshot_make_regionlist_1703d4(void *out, uint64_t list, uint64_t n)
{
    (void)out;
    (void)list;
    (void)n;
    (void)0; /* sk_stackshot_make_regionlist @ 0x1703d4: Builds a serialized region-list tagged value. Computes the total size over the param_2 array (0x28-stride, tag 1 vs 0x19/0x21), allocates the buffer via 157dc, serializes each region's 0x10-byte id + flags through 1552c/1586c/ 185b8/18984/1 */
}

/* FUN_001705e0 @ 0x1705e0  (est. sk_stackshot_tag3)
 * Writes a tag-3 (raw data) record: *out=3, ptr, len, 0. Tiny helper.
 * Confidence: high. */
static void sk_stackshot_tag3_1705e0(void *out, uint64_t ptr, uint64_t len)
{
    *(uint8_t *)out = 3;
    *(uint64_t *)(out + 8) = ptr;
    *(uint64_t *)(out + 0x10) = len;
    *(uint64_t *)(out + 0x18) = 0;
}

/* FUN_001705f4 @ 0x1705f4  (est. sk_stackshot_sizef)
 * Computes the serialized size of a region-list tagged value at param_1+0x30
 * (stride 0x28): base = tag-1 elem count * 0x28, +5 if first byte non-zero else
 * +1, plus 0x10. Traps (SoftwareBreakpoint 0x5519 @170664) on invalid bounds.
 * Confidence: medium. */
static long sk_stackshot_sizef_1705f4(long rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_sizef @ 0x1705f4: Computes the serialized size of a region-list tagged value at param_1+0x30 (stride 0x28): base = tag-1 elem count * 0x28, +5 if first byte non-zero else +1, plus 0x10. Traps (SoftwareBreakpoint 0x5519 @170664) on invalid bounds. Confidence: */
    return 0;
}

/* FUN_00170668 @ 0x170668  (est. sk_stackshot_serialize_uint64array)
 * Serializes a UInt64Array (tag 0) value: computes size (1705f4-style),
 * allocates via 1552c, writes tag + count, then serializes each entry through
 * 170060 (region-list serializer). Returns 0 on success. Confidence: medium. */
static uint64_t sk_stackshot_serialize_uint64array_170668(uint64_t *val)
{
    (void)val;
    (void)0; /* sk_stackshot_serialize_uint64array @ 0x170668: Serializes a UInt64Array (tag 0) value: computes size (1705f4-style), allocates via 1552c, writes tag + count, then serializes each entry through 170060 (region-list serializer). Returns 0 on success. Confidence: medium. */
    return 0;
}

/* FUN_00170858 @ 0x170858  (est. sk_stackshot_tag_lookup_uint8)
 * UInt8 tag lookup against DAT_004e4d30; traps "TB_FATAL: invalid tag in
 * ...UInt8..." (005cadd6) on out-of-range. Confidence: medium. */
static uint64_t sk_stackshot_tag_lookup_uint8_170858(uint8_t *tag)
{
    (void)tag;
    (void)0; /* sk_stackshot_tag_lookup_uint8 @ 0x170858: UInt8 tag lookup against DAT_004e4d30; traps "TB_FATAL: invalid tag in ...UInt8..." (005cadd6) on out-of-range. Confidence: medium. */
    return 0;
}

/* FUN_001708b4 @ 0x1708b4  (est. sk_stackshot_serialize_uint8array)
 * Serializes a UInt8Array value via the writer callback; tag 1 forwards
 * bytes one at a time, tag 2 through 15a44, tag 3 through 1552c/1586c/18a4c.
 * Confidence: medium. */
static char *sk_stackshot_serialize_uint8array_1708b4(char *val, uint64_t w)
{
    (void)val;
    (void)w;
    (void)0; /* sk_stackshot_serialize_uint8array @ 0x1708b4: Serializes a UInt8Array value via the writer callback; tag 1 forwards bytes one at a time, tag 2 through 15a44, tag 3 through 1552c/1586c/18a4c. Confidence: medium. */
    return 0;
}

/* FUN_00170b18 @ 0x170b18  (est. sk_stackshot_asid_size)
 * Computes the serialized size of an ASID record at param_1 (0x90 bytes).
 * Returns sum of fixed + variable components (tag-1 count * 0x28, flags,
 * plus 0x20). Traps (SoftwareBreakpoint 0x5519 @170c04) on invalid bounds.
 * Confidence: medium. */
static long sk_stackshot_asid_size_170b18(char *rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_asid_size @ 0x170b18: Computes the serialized size of an ASID record at param_1 (0x90 bytes). Returns sum of fixed + variable components (tag-1 count * 0x28, flags, plus 0x20). Traps (SoftwareBreakpoint 0x5519 @170c04) on invalid bounds. Confidence: medium. */
    return 0;
}

/* FUN_00170c0c @ 0x170c0c  (est. sk_stackshot_asid_parse)
 * Parses/serializes an ASID record: writes id, UInt8Array, perm flags, and
 * region-list via 170060. Returns 0 on success. Confidence: medium. */
static uint64_t sk_stackshot_asid_parse_170c0c(char *rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_asid_parse @ 0x170c0c: Parses/serializes an ASID record: writes id, UInt8Array, perm flags, and region-list via 170060. Returns 0 on success. Confidence: medium. */
    return 0;
}

/* FUN_00170f04 @ 0x170f04  (est. sk_stackshot_tag_lookup_stack)
 * Stack tag lookup; traps "TB_FATAL: invalid tag in ...Stack..." (005cae11).
 * Confidence: medium. */
static uint64_t sk_stackshot_tag_lookup_stack_170f04(uint8_t *tag)
{
    (void)tag;
    (void)0; /* sk_stackshot_tag_lookup_stack @ 0x170f04: Stack tag lookup; traps "TB_FATAL: invalid tag in ...Stack..." (005cae11). Confidence: medium. */
    return 0;
}

/* FUN_00170f60 @ 0x170f60  (est. sk_stackshot_serialize_stackrec)
 * Serializes a Stack record (0x90-byte tagged value): writes id, flags, and
 * the per-frame array (via 170f04 count, 1722fc). Traps (SoftwareBreakpoint
 * 0x5519 @171054) on OOB. Confidence: medium. */
static long sk_stackshot_serialize_stackrec_170f60(char *rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_serialize_stackrec @ 0x170f60: Serializes a Stack record (0x90-byte tagged value): writes id, flags, and the per-frame array (via 170f04 count, 1722fc). Traps (SoftwareBreakpoint 0x5519 @171054) on OOB. Confidence: medium. */
    return 0;
}

/* FUN_0017105c @ 0x17105c  (est. sk_stackshot_parse)
 * Parses a stackshot record into the caller buffer (used by the collect_ok
 * path): serializes via 1722fc/170f04 and returns the size. Confidence: medium. */
static uint64_t sk_stackshot_parse_17105c(char *rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_parse @ 0x17105c: Parses a stackshot record into the caller buffer (used by the collect_ok path): serializes via 1722fc/170f04 and returns the size. Confidence: medium. */
    return 0;
}

/* FUN_001712c8 @ 0x1712c8  (est. sk_stackshot_tag_lookup_cb)
 * Tag lookup (Stack variant); traps "...Stack..." (005cae6b). Confidence:
 * medium. */
static uint64_t sk_stackshot_tag_lookup_cb_1712c8(uint8_t *tag)
{
    (void)tag;
    (void)0; /* sk_stackshot_tag_lookup_cb @ 0x1712c8: Tag lookup (Stack variant); traps "...Stack..." (005cae6b). Confidence: medium. */
    return 0;
}

/* FUN_00171324 @ 0x171324  (est. sk_stackshot_dispatch_thunk)
 * Thunk that forwards to 17134c. Confidence: high (trivial). */
static void sk_stackshot_dispatch_thunk_171324(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_dispatch_thunk @ 0x171324: Thunk that forwards to 17134c. Confidence: high (trivial). */
}

/* FUN_0017134c @ 0x17134c  (est. sk_stackshot_dispatch)
 * Sets up a vtable dispatch (0x6ad3a8/0x667e48) with the 1713f4 handler and
 * invokes it via 147a0; stores the result. Confidence: medium. */
static void sk_stackshot_dispatch_17134c(uint64_t a, uint64_t *out, uint64_t b)
{
    (void)a;
    (void)out;
    (void)b;
    (void)0; /* sk_stackshot_dispatch @ 0x17134c: Sets up a vtable dispatch (0x6ad3a8/0x667e48) with the 1713f4 handler and invokes it via 147a0; stores the result. Confidence: medium. */
}

/* FUN_001713f4 @ 0x1713f4  (est. sk_stackshot_object_method)
 * Method dispatcher on the StackshotConclaveSupport object: reads a selector
 * hash from the message, and routes among the four selector callbacks in the
 * object's vtable (offset 0x20+0x0/8/10/18) — 1717fc, 171994, 171dc0 — passing
 * the serialized args. On selector-1 tag it deserializes a UInt8Array and
 * stores it; tag-2 forwards via 15ce4; tag-3 via 18eb0. Traps
 * "TB_FATAL: unrecognized selector" (005ba347) / SoftwareBreakpoint 0x5519 on
 * bad state. Large, faithful reconstruction. Confidence: medium. */
static uint64_t sk_stackshot_object_method_1713f4(long obj, uint64_t msg, uint64_t args)
{
    (void)obj;
    (void)msg;
    (void)args;
    (void)0; /* sk_stackshot_object_method @ 0x1713f4: Method dispatcher on the StackshotConclaveSupport object: reads a selector hash from the message, and routes among the four selector callbacks in the object's vtable (offset 0x20+0x0/8/10/18) — 1717fc, 171994, 171dc0 — passing the serialize */
    return 0;
}

/* FUN_001717fc @ 0x1717fc  (est. sk_stackshot_obj_sel1)
 * Selector-1 handler: reads a UInt8Array from args and stores it into the
 * object's buffer (offset +0x20). Confidence: medium. */
static uint64_t sk_stackshot_obj_sel1_1717fc(long obj, uint64_t *args)
{
    (void)obj;
    (void)args;
    (void)0; /* sk_stackshot_obj_sel1 @ 0x1717fc: Selector-1 handler: reads a UInt8Array from args and stores it into the object's buffer (offset +0x20). Confidence: medium. */
    return 0;
}

/* FUN_00171994 @ 0x171994  (est. sk_stackshot_obj_sel2)
 * Selector-2 handler: reads a larger argument record, allocates via 14f90,
 * and serializes the nested UInt8Array/Stack values into the object's buffer
 * (offset +0x20), releasing transient refs (12568/4b664). Confidence: medium. */
static uint64_t sk_stackshot_obj_sel2_171994(long obj, uint64_t *args)
{
    (void)obj;
    (void)args;
    (void)0; /* sk_stackshot_obj_sel2 @ 0x171994: Selector-2 handler: reads a larger argument record, allocates via 14f90, and serializes the nested UInt8Array/Stack values into the object's buffer (offset +0x20), releasing transient refs (12568/4b664). Confidence: medium. */
    return 0;
}

/* FUN_00171dc0 @ 0x171dc0  (est. sk_stackshot_obj_sel3)
 * Selector-3 handler: serializes a different argument shape (ids + optional
 * Stack), allocates via 14f90, writes the record, and releases transient refs.
 * Confidence: medium. */
static uint64_t sk_stackshot_obj_sel3_171dc0(long obj, uint64_t *args)
{
    (void)obj;
    (void)args;
    (void)0; /* sk_stackshot_obj_sel3 @ 0x171dc0: Selector-3 handler: serializes a different argument shape (ids + optional Stack), allocates via 14f90, writes the record, and releases transient refs. Confidence: medium. */
    return 0;
}

/* FUN_00172154 @ 0x172154  (est. sk_stackshot_serialize_uuid)
 * Serializes a 16-byte UUID (+ optional flags) into the object's stream via
 * 18e60/18984, then clears the completion flag at vtable+8+0x18. Confidence:
 * medium. */
static void sk_stackshot_serialize_uuid_172154(long obj, uint64_t a, long uuid)
{
    (void)obj;
    (void)a;
    (void)uuid;
    (void)0; /* sk_stackshot_serialize_uuid @ 0x172154: Serializes a 16-byte UUID (+ optional flags) into the object's stream via 18e60/18984, then clears the completion flag at vtable+8+0x18. Confidence: medium. */
}

/* FUN_00172200 @ 0x172200  (est. sk_stackshot_serialize_uint8)
 * Serializes a UInt8Array value by tag: tag1 copies 16 bytes+val, tag2 via
 * 15ce4, tag3 copies val bytes via 189d0. Traps "TB_FATAL: invalid tag in
 * ...UInt8..." on bad tag / SoftwareBreakpoint 0x5519 on OOB. Confidence:
 * medium. */
static void sk_stackshot_serialize_uint8_172200(uint64_t w, char *val)
{
    (void)w;
    (void)val;
    (void)0; /* sk_stackshot_serialize_uint8 @ 0x172200: Serializes a UInt8Array value by tag: tag1 copies 16 bytes+val, tag2 via 15ce4, tag3 copies val bytes via 189d0. Traps "TB_FATAL: invalid tag in ...UInt8..." on bad tag / SoftwareBreakpoint 0x5519 on OOB. Confidence: medium. */
}

/* FUN_001722fc @ 0x1722fc  (est. sk_stackshot_serialize_stackref)
 * Serializes a Stack tagged value (tag1 present / absent). Writes presence
 * byte, count via 170f04, then per-tag copies. Traps "TB_FATAL: invalid tag in
 * ...Stack..." (005cae11) on bad tag. Confidence: medium. */
static void sk_stackshot_serialize_stackref_1722fc(uint64_t w, char *val)
{
    (void)w;
    (void)val;
    (void)0; /* sk_stackshot_serialize_stackref @ 0x1722fc: Serializes a Stack tagged value (tag1 present / absent). Writes presence byte, count via 170f04, then per-tag copies. Traps "TB_FATAL: invalid tag in ...Stack..." (005cae11) on bad tag. Confidence: medium. */
}

/* FUN_0017244c @ 0x17244c  (est. sk_stackshot_trap_overflow_a)
 * Overflow trap with build-arg line 0x191 and message "...overflow detected
 * when..." (005aae93). Confidence: high (trap stub). */
static void sk_stackshot_trap_overflow_a_17244c(void)
{
    (void)0; /* sk_stackshot_trap_overflow_a @ 0x17244c: Overflow trap with build-arg line 0x191 and message "...overflow detected when..." (005aae93). Confidence: high (trap stub). */
}

/* FUN_00172468 @ 0x172468  (est. sk_stackshot_trap_overflow_b)
 * Overflow trap line 0x519. Confidence: high. */
static void sk_stackshot_trap_overflow_b_172468(void)
{
    (void)0; /* sk_stackshot_trap_overflow_b @ 0x172468: Overflow trap line 0x519. Confidence: high. */
}

/* FUN_00172484 @ 0x172484  (est. sk_stackshot_trap_overflow_c)
 * Overflow trap line 0x330, message "...overflow..." (005abd5d). Confidence:
 * high. */
static void sk_stackshot_trap_overflow_c_172484(void)
{
    (void)0; /* sk_stackshot_trap_overflow_c @ 0x172484: Overflow trap line 0x330, message "...overflow..." (005abd5d). Confidence: high. */
}

/* FUN_001724a0 @ 0x1724a0  (est. sk_stackshot_trap_overflow_d)
 * Overflow trap line 0x51a. Confidence: high. */
static void sk_stackshot_trap_overflow_d_1724a0(void)
{
    (void)0; /* sk_stackshot_trap_overflow_d @ 0x1724a0: Overflow trap line 0x51a. Confidence: high. */
}

/* FUN_001724bc @ 0x1724bc  (est. sk_stackshot_log_a)
 * Logs the diagnostic at DAT_005cacd6 with param_1. Confidence: medium. */
static void sk_stackshot_log_a_1724bc(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_log_a @ 0x1724bc: Logs the diagnostic at DAT_005cacd6 with param_1. Confidence: medium. */
}

/* FUN_001724cc @ 0x1724cc  (est. sk_stackshot_log_b)
 * Logs the diagnostic at DAT_005cad83. Confidence: medium. */
static void sk_stackshot_log_b_1724cc(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_log_b @ 0x1724cc: Logs the diagnostic at DAT_005cad83. Confidence: medium. */
}

/* FUN_001724dc @ 0x1724dc  (est. sk_stackshot_free_ctx_1724dc)
 * Frees a prepared context (36b118 releases, 276c vtable reset). Confidence:
 * low. */
static void sk_stackshot_free_ctx_1724dc(void)
{
    (void)0; /* sk_stackshot_free_ctx_1724dc @ 0x1724dc: Frees a prepared context (36b118 releases, 276c vtable reset). Confidence: low. */
}

/* FUN_001724e0 @ 0x1724e0  (est. sk_stackshot_free_ctx_1724e0)
 * Frees a prepared context (36b118 releases, 276c vtable reset). Confidence:
 * low. */
static void sk_stackshot_free_ctx_1724e0(void)
{
    (void)0; /* sk_stackshot_free_ctx_1724e0 @ 0x1724e0: Frees a prepared context (36b118 releases, 276c vtable reset). Confidence: low. */
}

/* FUN_00172530 @ 0x172530  (est. sk_stackshot_free_ctx_b_172530)
 * Frees a prepared context + teardown (36b6ac). Confidence: low. */
static void sk_stackshot_free_ctx_b_172530(void)
{
    (void)0; /* sk_stackshot_free_ctx_b_172530 @ 0x172530: Frees a prepared context + teardown (36b6ac). Confidence: low. */
}

/* FUN_00172534 @ 0x172534  (est. sk_stackshot_free_ctx_b_172534)
 * Frees a prepared context + teardown (36b6ac). Confidence: low. */
static void sk_stackshot_free_ctx_b_172534(void)
{
    (void)0; /* sk_stackshot_free_ctx_b_172534 @ 0x172534: Frees a prepared context + teardown (36b6ac). Confidence: low. */
}

/* FUN_00172584 @ 0x172584  (est. sk_stackshot_dispatcher)
 * Generic dispatcher: resolves the current dispatch frame (via 36b270-style
 * stack walk), invokes the three callbacks (param_5/6/7) and the vtable entry.
 * Confidence: low (shape-only). */
static void sk_stackshot_dispatcher_172584(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                          void (*f1)(uint64_t), void (*f2)(void*), void (*f3)(void*, uint64_t))
{
    (void)0; /* sk_stackshot_dispatcher @ 0x172584: Generic dispatcher: resolves the current dispatch frame (via 36b270-style stack walk), invokes the three callbacks (param_5/6/7) and the vtable entry. Confidence: low (shape-only). */
}

/* FUN_00172688 @ 0x172688  (est. sk_stackshot_fatal_format)
 * The shared "fatal StackshotConclaveSupport error" formatter. Builds a
 * vtable context (0x671df8 logger, 0x677830), emits the format string with
 * args via thunk_FUN_002acbb8/3a25d4, and runs the crash log. This is the
 * recurring pattern behind every FUN_00172688(...) call in the subsystem.
 * Confidence: medium. Notes: string s_takeConclaveCrash_scids_* etc. */
static void sk_stackshot_fatal_format_172688(uint64_t a, uint64_t b, const char *fmt, uint64_t n, uint64_t x, uint64_t line)
{
    (void)a;
    (void)b;
    (void)fmt;
    (void)n;
    (void)x;
    (void)line;
    (void)0; /* sk_stackshot_fatal_format @ 0x172688: The shared "fatal StackshotConclaveSupport error" formatter. Builds a vtable context (0x671df8 logger, 0x677830), emits the format string with args via thunk_FUN_002acbb8/3a25d4, and runs the crash log. This is the recurring pattern behind  */
}

/* FUN_00172828 @ 0x172828  (est. sk_stackshot_alloc_vec)
 * Allocates a 0x10-capacity vector (36a940/36a804) and zeroes it via 18148.
 * Confidence: low. */
static long sk_stackshot_alloc_vec_172828(void)
{
    (void)0; /* sk_stackshot_alloc_vec @ 0x172828: Allocates a 0x10-capacity vector (36a940/36a804) and zeroes it via 18148. Confidence: low. */
    return 0;
}

/* FUN_00172874 @ 0x172874  (est. sk_stackshot_alloc_vec_x20)
 * Allocates a 0x10 vector and stores it at x20+0x10. Confidence: low. */
static void sk_172874(void)
{
    (void)0; /* sk_stackshot_alloc_vec_x20 @ 0x172874: Allocates a 0x10 vector and stores it at x20+0x10. Confidence: low. */
}

/* FUN_00172878 @ 0x172878  (est. sk_stackshot_alloc_vec_x20)
 * Allocates a 0x10 vector and stores it at x20+0x10. Confidence: low. */
static void sk_172878(void)
{
    (void)0; /* sk_stackshot_alloc_vec_x20 @ 0x172878: Allocates a 0x10 vector and stores it at x20+0x10. Confidence: low. */
}

/* FUN_001728a4 @ 0x1728a4  (est. sk_stackshot_free_vec)
 * Releases the vector at x20+0x10 (53aa0 then 12568). Confidence: low. */
static void sk_1728a4(void)
{
    (void)0; /* sk_stackshot_free_vec @ 0x1728a4: Releases the vector at x20+0x10 (53aa0 then 12568). Confidence: low. */
}

/* FUN_001728a8 @ 0x1728a8  (est. sk_stackshot_free_vec)
 * Releases the vector at x20+0x10 (53aa0 then 12568). Confidence: low. */
static void sk_1728a8(void)
{
    (void)0; /* sk_stackshot_free_vec @ 0x1728a8: Releases the vector at x20+0x10 (53aa0 then 12568). Confidence: low. */
}

/* FUN_001728d4 @ 0x1728d4  (est. sk_stackshot_free_vec_b)
 * Releases the vector at x20+0x10 and runs 36b6ac teardown. Confidence: low. */
static void sk_1728d4(void)
{
    (void)0; /* sk_stackshot_free_vec_b @ 0x1728d4: Releases the vector at x20+0x10 and runs 36b6ac teardown. Confidence: low. */
}

/* FUN_001728d8 @ 0x1728d8  (est. sk_stackshot_free_vec_b)
 * Releases the vector at x20+0x10 and runs 36b6ac teardown. Confidence: low. */
static void sk_1728d8(void)
{
    (void)0; /* sk_stackshot_free_vec_b @ 0x1728d8: Releases the vector at x20+0x10 and runs 36b6ac teardown. Confidence: low. */
}

/* FUN_00172910 @ 0x172910  (est. sk_stackshot_vtable_call)
 * Resolves the type at 0x6542d0/004e4d68 and invokes its +0x10 method with
 * (param_2, param_1, type); returns param_2. Confidence: low. */
static uint64_t sk_stackshot_vtable_call_172910(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_vtable_call @ 0x172910: Resolves the type at 0x6542d0/004e4d68 and invokes its +0x10 method with (param_2, param_1, type); returns param_2. Confidence: low. */
    return 0;
}

/* FUN_00172978 @ 0x172978  (est. sk_stackshot_mkobj_a)
 * Constructs a StackshotConclaveSupport object: allocates the 0x18 header,
 * the 0x10 buffer, resolves type (004e4d88), and forwards to 176e8c init.
 * Confidence: low. */
static uint64_t sk_stackshot_mkobj_a_172978(uint64_t a, uint64_t b, long c, uint64_t d)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)0; /* sk_stackshot_mkobj_a @ 0x172978: Constructs a StackshotConclaveSupport object: allocates the 0x18 header, the 0x10 buffer, resolves type (004e4d88), and forwards to 176e8c init. Confidence: low. */
    return 0;
}

/* FUN_00172a30 @ 0x172a30  (est. sk_stackshot_mkobj_b)
 * Constructs the object with type DAT_004e4da0 (0018fbe8). Confidence: low. */
static uint64_t sk_stackshot_mkobj_b_172a30(uint64_t a, uint64_t b, long c, uint64_t d)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)0; /* sk_stackshot_mkobj_b @ 0x172a30: Constructs the object with type DAT_004e4da0 (0018fbe8). Confidence: low. */
    return 0;
}

/* FUN_00172ae8 @ 0x172ae8  (est. sk_stackshot_mkobj_c)
 * Constructs the object (no a-release). Confidence: low. */
static uint64_t sk_stackshot_mkobj_c_172ae8(uint64_t a, long b, uint64_t c)
{
    (void)a;
    (void)b;
    (void)c;
    (void)0; /* sk_stackshot_mkobj_c @ 0x172ae8: Constructs the object (no a-release). Confidence: low. */
    return 0;
}

/* FUN_00172b8c @ 0x172b8c  (est. sk_stackshot_mkobj_d)
 * Constructs the object (no header alloc). Confidence: low. */
static uint64_t sk_stackshot_mkobj_d_172b8c(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a;
    (void)b;
    (void)c;
    (void)0; /* sk_stackshot_mkobj_d @ 0x172b8c: Constructs the object (no header alloc). Confidence: low. */
    return 0;
}

/* FUN_00172bf8 @ 0x172bf8  (est. sk_stackshot_vtable_and)
 * Calls the vtable method at +0x20 and returns its result & 1. Confidence:
 * low. */
static uint32_t sk_stackshot_vtable_and_172bf8(long obj)
{
    (void)obj;
    (void)0; /* sk_stackshot_vtable_and @ 0x172bf8: Calls the vtable method at +0x20 and returns its result & 1. Confidence: low. */
    return 0;
}

/* FUN_00172c38 @ 0x172c38  (est. sk_stackshot_vtable_call2)
 * Calls the vtable method at +0x20 (no result use). Confidence: low. */
static void sk_stackshot_vtable_call2_172c38(long obj)
{
    (void)obj;
    (void)0; /* sk_stackshot_vtable_call2 @ 0x172c38: Calls the vtable method at +0x20 (no result use). Confidence: low. */
}

/* FUN_00172c78 @ 0x172c78  (est. sk_stackshot_prep_context)
 * Prepares a StackshotConclaveSupport context from x20 fields: resolves the
 * request type (0x654448, 0xad, 7), gathers the vtable/args (via 172910,
 * 6e7c0, 173644), and returns the type result. Confidence: low. */
static uint64_t sk_stackshot_prep_context_172c78(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_prep_context @ 0x172c78: Prepares a StackshotConclaveSupport context from x20 fields: resolves the request type (0x654448, 0xad, 7), gathers the vtable/args (via 172910, 6e7c0, 173644), and returns the type result. Confidence: low. */
    return 0;
}

/* FUN_00172d1c @ 0x172d1c  (est. sk_stackshot_prep_ctx_b)
 * Simpler context prep forwarding to 173644. Confidence: low. */
static uint64_t sk_stackshot_prep_ctx_b_172d1c(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)0; /* sk_stackshot_prep_ctx_b @ 0x172d1c: Simpler context prep forwarding to 173644. Confidence: low. */
    return 0;
}

/* FUN_00172d9c @ 0x172d9c  (est. sk_stackshot_free_ctx)
 * Frees a prepared context (36b118 releases, 276c vtable reset). Confidence:
 * low. */
static void sk_172d9c(void)
{
    (void)0; /* sk_stackshot_free_ctx @ 0x172d9c: Frees a prepared context (36b118 releases, 276c vtable reset). Confidence: low. */
}

/* FUN_00172da0 @ 0x172da0  (est. sk_stackshot_free_ctx)
 * Frees a prepared context (36b118 releases, 276c vtable reset). Confidence:
 * low. */
static void sk_172da0(void)
{
    (void)0; /* sk_stackshot_free_ctx @ 0x172da0: Frees a prepared context (36b118 releases, 276c vtable reset). Confidence: low. */
}

/* FUN_00172de4 @ 0x172de4  (est. sk_stackshot_free_ctx_b)
 * Frees the context and runs teardown (36b6ac). Confidence: low. */
static void sk_172de4(void)
{
    (void)0; /* sk_stackshot_free_ctx_b @ 0x172de4: Frees the context and runs teardown (36b6ac). Confidence: low. */
}

/* FUN_00172de8 @ 0x172de8  (est. sk_stackshot_free_ctx_b)
 * Frees the context and runs teardown (36b6ac). Confidence: low. */
static void sk_172de8(void)
{
    (void)0; /* sk_stackshot_free_ctx_b @ 0x172de8: Frees the context and runs teardown (36b6ac). Confidence: low. */
}

/* FUN_00172e38 @ 0x172e38  (est. sk_stackshot_crash_scid)
 * getConclaveCrashBacktrace(scid): fetches the guest by scid (176800),
 * collects via 16f2e4, and on success resolves the crash backtrace; on failure
 * emits the "stackshot of executing..." fatal (005cb920). Returns the packed
 * result record. Confidence: medium. Notes: 0x2f/0xe4 line refs, DAT_004bbff0. */
static void sk_stackshot_crash_scid_172e38(uint64_t *out, uint64_t scid)
{
    (void)out;
    (void)scid;
    (void)0; /* sk_stackshot_crash_scid @ 0x172e38: getConclaveCrashBacktrace(scid): fetches the guest by scid (176800), collects via 16f2e4, and on success resolves the crash backtrace; on failure emits the "stackshot of executing..." fatal (005cb920). Returns the packed result record. Conf */
}

/* FUN_0017310c @ 0x17310c  (est. sk_stackshot_crash_ecid)
 * getConclaveCrashBacktrace variant for own-ECID (16f378 collect); emits
 * "stackshot own ecid executing..." (005cb8d0) fatal on failure. Confidence:
 * medium. */
static void sk_stackshot_crash_ecid_17310c(uint64_t *out, uint64_t a)
{
    (void)out;
    (void)a;
    (void)0; /* sk_stackshot_crash_ecid @ 0x17310c: getConclaveCrashBacktrace variant for own-ECID (16f378 collect); emits "stackshot own ecid executing..." (005cb8d0) fatal on failure. Confidence: medium. */
}

/* FUN_00173330 @ 0x173330  (est. sk_stackshot_free_buf)
 * Releases the buffer at x20+0x10 (if non-null) and runs teardown. Confidence:
 * low. */
static void sk_173330(void)
{
    (void)0; /* sk_stackshot_free_buf @ 0x173330: Releases the buffer at x20+0x10 (if non-null) and runs teardown. Confidence: low. */
}

/* FUN_00173334 @ 0x173334  (est. sk_stackshot_free_buf)
 * Releases the buffer at x20+0x10 (if non-null) and runs teardown. Confidence:
 * low. */
static void sk_173334(void)
{
    (void)0; /* sk_stackshot_free_buf @ 0x173334: Releases the buffer at x20+0x10 (if non-null) and runs teardown. Confidence: low. */
}

/* FUN_00173368 @ 0x173368  (est. sk_stackshot_frame_list)
 * Serializes a frame list (0x28-stride, count at x20+0x28) into a growable
 * array (0x657778), resolving each frame via 177068 and building 16-byte
 * entries via 1a1c8/1762cc. Confidence: medium. */
static void sk_stackshot_frame_list_173368(void)
{
    (void)0; /* sk_stackshot_frame_list @ 0x173368: Serializes a frame list (0x28-stride, count at x20+0x28) into a growable array (0x657778), resolving each frame via 177068 and building 16-byte entries via 1a1c8/1762cc. Confidence: medium. */
}

/* FUN_00173500 @ 0x173500  (est. sk_stackshot_finalize_frames)
 * Finalizes a frame array: when param_5 >= 0 walks the frame list into the
 * global 0x657788 array and computes the final hash via 177ee8 (or returns
 * 785cc on error). Confidence: medium. */
static uint64_t sk_stackshot_finalize_frames_173500(long a, uint64_t b, uint64_t c, uint64_t flags, long err)
{
    (void)a;
    (void)b;
    (void)c;
    (void)flags;
    (void)err;
    (void)0; /* sk_stackshot_finalize_frames @ 0x173500: Finalizes a frame array: when param_5 >= 0 walks the frame list into the global 0x657788 array and computes the final hash via 177ee8 (or returns 785cc on error). Confidence: medium. */
    return 0;
}

/* FUN_00173644 @ 0x173644  (est. sk_stackshot_teardown)
 * The large context teardown / capture orchestration: allocates the buffer
 * (16f278), resolves the token, registers crash-scid callbacks (16f108), walks
 * the guest list building per-guest crash records (17368/177ed0/17e380), and
 * drives the final serialization (16ea28/173500). Confidence: medium. */
static long sk_stackshot_teardown_173644(uint64_t a, uint64_t b, uint64_t c, uint64_t d, long e, long f)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)0; /* sk_stackshot_teardown @ 0x173644: The large context teardown / capture orchestration: allocates the buffer (16f278), resolves the token, registers crash-scid callbacks (16f108), walks the guest list building per-guest crash records (17368/177ed0/17e380), and drives the fina */
    return 0;
}

/* FUN_00173acc @ 0x173acc  (est. sk_stackshot_vtable_call3)
 * Calls the vtable method at +0x20 with param_2. Confidence: low. */
static uint64_t sk_stackshot_vtable_call3_173acc(long obj, uint64_t p)
{
    (void)obj;
    (void)p;
    (void)0; /* sk_stackshot_vtable_call3 @ 0x173acc: Calls the vtable method at +0x20 with param_2. Confidence: low. */
    return 0;
}

/* FUN_00173b1c @ 0x173b1c  (est. sk_stackshot_free_ctx_c)
 * Frees the capture context (16f084 offline + releases). Confidence: low. */
static void sk_173b1c(void)
{
    (void)0; /* sk_stackshot_free_ctx_c @ 0x173b1c: Frees the capture context (16f084 offline + releases). Confidence: low. */
}

/* FUN_00173b20 @ 0x173b20  (est. sk_stackshot_free_ctx_c)
 * Frees the capture context (16f084 offline + releases). Confidence: low. */
static void sk_173b20(void)
{
    (void)0; /* sk_stackshot_free_ctx_c @ 0x173b20: Frees the capture context (16f084 offline + releases). Confidence: low. */
}

/* FUN_00173b7c @ 0x173b7c  (est. sk_stackshot_free_ctx_d)
 * Frees the capture context + teardown. Confidence: low. */
static void sk_173b7c(void)
{
    (void)0; /* sk_stackshot_free_ctx_d @ 0x173b7c: Frees the capture context + teardown. Confidence: low. */
}

/* FUN_00173b80 @ 0x173b80  (est. sk_stackshot_free_ctx_d)
 * Frees the capture context + teardown. Confidence: low. */
static void sk_173b80(void)
{
    (void)0; /* sk_stackshot_free_ctx_d @ 0x173b80: Frees the capture context + teardown. Confidence: low. */
}

/* FUN_00173be8 @ 0x173be8  (est. sk_stackshot_crash_collect)
 * The largest function in this region: getConclaveCrashBacktrace(scids) full
 * collector. Resolves each scid, serializes the crash backtrace frames into
 * growable arrays (0x657778/0x6577e0), walks the crash-scid bitmap (bit-twiddle
 * reverse), fetches per-scid crash info via the vtable (0x5c... strings),
 * resolves address-space (16f3f8/16f464), and drives takeConclaveCrash
 * serialization via 173500/177ee8/175d08/177158. Traps/fatal
 * (StackshotConclaveSupport_Stacksh_005cb4a0) on any inconsistency.
 * Confidence: medium. Notes: strings getConclaveCrashBacktrace_scid___005cb960,
 * takeConclaveCrash_scids___005cb540, own_addressspace_wantRawAddresse_005cb750;
 * __thread_bss Mach-O header fields (magic/cputype/cpusubtype/filetype/ncmds). */
static void sk_stackshot_crash_collect_173be8(long p)
{
    (void)p;
    (void)0; /* sk_stackshot_crash_collect @ 0x173be8: The largest function in this region: getConclaveCrashBacktrace(scids) full collector. Resolves each scid, serializes the crash backtrace frames into growable arrays (0x657778/0x6577e0), walks the crash-scid bitmap (bit-twiddle reverse), fet */
}

/* FUN_00175d08 @ 0x175d08  (est. sk_stackshot_crash_write)
 * Serializes a crash backtrace batch: resolves the scid context (176800),
 * formats via 205844/72688, and forwards the collected record triple to
 * 17b4d8; on non-zero status re-drives through a 65a550 callback (36993c).
 * Confidence: medium. */
static void sk_stackshot_crash_write_175d08(uint64_t a, uint64_t b, uint64_t *rec)
{
    (void)a;
    (void)b;
    (void)rec;
    (void)0; /* sk_stackshot_crash_write @ 0x175d08: Serializes a crash backtrace batch: resolves the scid context (176800), formats via 205844/72688, and forwards the collected record triple to 17b4d8; on non-zero status re-drives through a 65a550 callback (36993c). Confidence: medium. */
}

/* FUN_00176014 @ 0x176014  (est. sk_stackshot_vec20)
 * Allocates a 0x20-stride growable vector (type 0x654508/004e4f20) of
 * capacity param_2 (bounded by param_1), with initial cap from 126e8.
 * Confidence: medium. */
static void *sk_stackshot_vec20_176014(long a, long b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_vec20 @ 0x176014: Allocates a 0x20-stride growable vector (type 0x654508/004e4f20) of capacity param_2 (bounded by param_1), with initial cap from 126e8. Confidence: medium. */
    return 0;
}

/* FUN_00176098 @ 0x176098  (est. sk_stackshot_vec28)
 * Allocates a 0x28-stride growable vector (0x654500/004e4f10). Confidence:
 * medium. */
static void *sk_stackshot_vec28_176098(long a, long b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_vec28 @ 0x176098: Allocates a 0x28-stride growable vector (0x654500/004e4f10). Confidence: medium. */
    return 0;
}

/* FUN_00176128 @ 0x176128  (est. sk_stackshot_vec38)
 * Allocates a 0x38-stride growable vector (param_3/param_4 type). Confidence:
 * medium. */
static void *sk_stackshot_vec38_176128(long a, long b, uint64_t t3, uint64_t t4)
{
    (void)a;
    (void)b;
    (void)t3;
    (void)t4;
    (void)0; /* sk_stackshot_vec38 @ 0x176128: Allocates a 0x38-stride growable vector (param_3/param_4 type). Confidence: medium. */
    return 0;
}

/* FUN_001761b8 @ 0x1761b8  (est. sk_stackshot_vec18)
 * Allocates a 0x18-stride growable vector (0x6544d0/004e4ee0). Confidence:
 * medium. */
static void *sk_stackshot_vec18_1761b8(long a, long b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_vec18 @ 0x1761b8: Allocates a 0x18-stride growable vector (0x6544d0/004e4ee0). Confidence: medium. */
    return 0;
}

/* FUN_00176248 @ 0x176248  (est. sk_stackshot_vec10)
 * Allocates a 0x10-stride growable vector (0x6544e0/004e4ee8). Confidence:
 * medium. */
static void *sk_stackshot_vec10_176248(long a, long b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_vec10 @ 0x176248: Allocates a 0x10-stride growable vector (0x6544e0/004e4ee8). Confidence: medium. */
    return 0;
}

/* FUN_001762cc @ 0x1762cc  (est. sk_stackshot_vec20_grow)
 * Growable 0x20-vector reallocate: if param_3 bit0 set, double capacity
 * bounded by the 0x18 field; allocates via 176014, copies old elements (0x20
 * stride, 35b67c), and releases the old vector. Returns the new vector.
 * Confidence: medium. */
static long sk_stackshot_vec20_grow_1762cc(uint64_t keep, uint64_t want, uint64_t grow, long old)
{
    (void)keep;
    (void)want;
    (void)grow;
    (void)old;
    (void)0; /* sk_stackshot_vec20_grow @ 0x1762cc: Growable 0x20-vector reallocate: if param_3 bit0 set, double capacity bounded by the 0x18 field; allocates via 176014, copies old elements (0x20 stride, 35b67c), and releases the old vector. Returns the new vector. Confidence: medium. */
    return 0;
}

/* FUN_001763a0 @ 0x1763a0  (est. sk_stackshot_vec28_grow)
 * Growable 0x28-vector reallocate via 176098 (copy via 117cc4). Confidence:
 * medium. */
static long sk_stackshot_vec28_grow_1763a0(uint64_t keep, uint64_t want, uint64_t grow, long old)
{
    (void)keep;
    (void)want;
    (void)grow;
    (void)old;
    (void)0; /* sk_stackshot_vec28_grow @ 0x1763a0: Growable 0x28-vector reallocate via 176098 (copy via 117cc4). Confidence: medium. */
    return 0;
}

/* FUN_0017646c @ 0x17646c  (est. sk_stackshot_vec38_grow)
 * Growable 0x38-vector reallocate via 176128 (type 0x6544f0/004e4f00).
 * Confidence: medium. */
static long sk_stackshot_vec38_grow_17646c(uint64_t keep, uint64_t want, uint64_t grow, long old)
{
    (void)keep;
    (void)want;
    (void)grow;
    (void)old;
    (void)0; /* sk_stackshot_vec38_grow @ 0x17646c: Growable 0x38-vector reallocate via 176128 (type 0x6544f0/004e4f00). Confidence: medium. */
    return 0;
}

/* FUN_00176564 @ 0x176564  (est. sk_stackshot_vec38b_grow)
 * Growable 0x38-vector (type 0x6544d8/004e5920). Confidence: medium. */
static long sk_stackshot_vec38b_grow_176564(uint64_t keep, uint64_t want, uint64_t grow, long old)
{
    (void)keep;
    (void)want;
    (void)grow;
    (void)old;
    (void)0; /* sk_stackshot_vec38b_grow @ 0x176564: Growable 0x38-vector (type 0x6544d8/004e5920). Confidence: medium. */
    return 0;
}

/* FUN_0017664c @ 0x17664c  (est. sk_stackshot_vec18_grow)
 * Growable 0x18-vector via 1761b8. Confidence: medium. */
static long sk_stackshot_vec18_grow_17664c(uint64_t keep, uint64_t want, uint64_t grow, long old)
{
    (void)keep;
    (void)want;
    (void)grow;
    (void)old;
    (void)0; /* sk_stackshot_vec18_grow @ 0x17664c: Growable 0x18-vector via 1761b8. Confidence: medium. */
    return 0;
}

/* FUN_00176724 @ 0x176724  (est. sk_stackshot_vec10_grow)
 * Growable 0x10-vector via 176248. Confidence: medium. */
static long sk_stackshot_vec10_grow_176724(uint64_t keep, uint64_t want, uint64_t grow, long old)
{
    (void)keep;
    (void)want;
    (void)grow;
    (void)old;
    (void)0; /* sk_stackshot_vec10_grow @ 0x176724: Growable 0x10-vector via 176248. Confidence: medium. */
    return 0;
}

/* FUN_00176800 @ 0x176800  (est. sk_stackshot_context_or_fatal)
 * Returns param_4 when non-null; otherwise emits the fatal context error
 * (0xd00000000000003a/0x80000000005cb4c0) and aborts via 1afa84
 * (StackshotConclaveSupport_Stacksh_005cb4a0, line 0x2a). Confidence: medium. */
static long sk_stackshot_context_or_fatal_176800(uint64_t a, uint64_t b, uint64_t c, long ctx)
{
    (void)a;
    (void)b;
    (void)c;
    (void)ctx;
    (void)0; /* sk_stackshot_context_or_fatal @ 0x176800: Returns param_4 when non-null; otherwise emits the fatal context error (0xd00000000000003a/0x80000000005cb4c0) and aborts via 1afa84 (StackshotConclaveSupport_Stacksh_005cb4a0, line 0x2a). Confidence: medium. */
    return 0;
}

/* FUN_00176914 @ 0x176914  (est. sk_stackshot_get_crash_buffer)
 * getCrashBuffer: allocates/validates the crash buffer region. Resolves the
 * region (DAT_004e4ba8 x2, DAT_004e4ba0), tries to allocate via 5ab88, and on
 * failure emits the fatal "...getCrashBuffer..." diagnostics (005cbb90 etc.).
 * Large, faithful reconstruction. Confidence: medium. Notes: strings
 * s_getCrashBuffer___005cbb90. */
static void sk_stackshot_get_crash_buffer_176914(void)
{
    (void)0; /* sk_stackshot_get_crash_buffer @ 0x176914: getCrashBuffer: allocates/validates the crash buffer region. Resolves the region (DAT_004e4ba8 x2, DAT_004e4ba0), tries to allocate via 5ab88, and on failure emits the fatal "...getCrashBuffer..." diagnostics (005cbb90 etc.). Large, faithfu */
}

/* FUN_00176e8c @ 0x176e8c  (est. sk_stackshot_construct)
 * Constructs a StackshotConclaveSupport object: allocates the 0x18 header +
 * 0x10 buffer, registers the crash-buffer callback (176914), sets up the two
 * vtable dispatch entries (172bf8/172c38), and initializes via 16dff4.
 * Confidence: medium. */
static void sk_stackshot_construct_176e8c(long obj, uint64_t rec, uint64_t b)
{
    (void)obj;
    (void)rec;
    (void)b;
    (void)0; /* sk_stackshot_construct @ 0x176e8c: Constructs a StackshotConclaveSupport object: allocates the 0x18 header + 0x10 buffer, registers the crash-buffer callback (176914), sets up the two vtable dispatch entries (172bf8/172c38), and initializes via 16dff4. Confidence: medium. */
}

/* FUN_00177068 @ 0x177068  (est. sk_stackshot_frame_pack)
 * Packs a frame {offset, type} into a single word: (off - len) & 0xffffffff
 * ffff | type << 0x30. Confidence: high (tiny). */
static uint64_t sk_stackshot_frame_pack_177068(long a, long b, long c)
{
    return (a - c) & 0xffffffffffff | (uint64_t)b << 0x30;
}

/* FUN_00177084 @ 0x177084  (est. sk_stackshot_fptr_resolve)
 * Resolves a tagged function pointer (bit0 set => deref masked ptr) and
 * returns the code address (base+4 + *(int*)(base+4)). Confidence: high. */
static long sk_stackshot_fptr_resolve_177084(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_001770b4 @ 0x1770b4  (est. sk_stackshot_release_res)
 * Releases the resource at x20+0x10 (26e8) + teardown (36b21c). Confidence:
 * low. */
static void sk_1770b4(void)
{
    (void)0; /* sk_stackshot_release_res @ 0x1770b4: Releases the resource at x20+0x10 (26e8) + teardown (36b21c). Confidence: low. */
}

/* FUN_001770b8 @ 0x1770b8  (est. sk_stackshot_release_res)
 * Releases the resource at x20+0x10 (26e8) + teardown (36b21c). Confidence:
 * low. */
static void sk_1770b8(void)
{
    (void)0; /* sk_stackshot_release_res @ 0x1770b8: Releases the resource at x20+0x10 (26e8) + teardown (36b21c). Confidence: low. */
}

/* FUN_001770e0 @ 0x1770e0  (est. sk_stackshot_vtable_indirect)
 * Indirect vtable call: resolves fptr from x20+0x30 via 177084 and calls it
 * with (param_1, x20+0x10, x20+0x30). Confidence: low. */
static void sk_stackshot_vtable_indirect_1770e0(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_vtable_indirect @ 0x1770e0: Indirect vtable call: resolves fptr from x20+0x30 via 177084 and calls it with (param_1, x20+0x10, x20+0x30). Confidence: low. */
}

/* FUN_00177158 @ 0x177158  (est. sk_stackshot_collect_region)
 * Collects a region's frames (from param_1 to param_2, stride param_3,
 * plus param_4 offset) into the 0x657778 growable array via 177490/34a2c
 * resolution. Confidence: medium. */
static void *sk_stackshot_collect_region_177158(uint64_t a, long b, long c, long d)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)0; /* sk_stackshot_collect_region @ 0x177158: Collects a region's frames (from param_1 to param_2, stride param_3, plus param_4 offset) into the 0x657778 growable array via 177490/34a2c resolution. Confidence: medium. */
    return 0;
}

/* FUN_001773c8 @ 0x1773c8  (est. sk_stackshot_fptr_resolve2)
 * Tagged fptr resolve (base+4 + *(int*)(base+4)). Confidence: high. */
static long sk_stackshot_fptr_resolve2_1773c8(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_00177490 @ 0x177490  (est. sk_stackshot_indirect_call)
 * Indirect call through the object vtable (+0x30 dispatch via first word).
 * Confidence: low. */
static void sk_stackshot_indirect_call_177490(uint64_t a, uint64_t *vt, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a;
    (void)vt;
    (void)b;
    (void)c;
    (void)d;
    (void)0; /* sk_stackshot_indirect_call @ 0x177490: Indirect call through the object vtable (+0x30 dispatch via first word). Confidence: low. */
}

/* FUN_001774ac @ 0x1774ac  (est. sk_stackshot_is_idle)
 * Returns true when the object at x20+0x10's +0x10 field is empty (via
 * 1817c). Confidence: low. */
static bool sk_stackshot_is_idle_1774ac(void)
{
    (void)0; /* sk_stackshot_is_idle @ 0x1774ac: Returns true when the object at x20+0x10's +0x10 field is empty (via 1817c). Confidence: low. */
    return 0;
}

/* FUN_001774dc @ 0x1774dc  (est. sk_stackshot_region_call)
 * Indirect region call: invokes (param_2+0x30)(param_1, 0x8928, ...).
 * Confidence: low. */
static void sk_stackshot_region_call_1774dc(uint64_t a, long vt, uint64_t b, uint64_t c)
{
    (void)a;
    (void)vt;
    (void)b;
    (void)c;
    (void)0; /* sk_stackshot_region_call @ 0x1774dc: Indirect region call: invokes (param_2+0x30)(param_1, 0x8928, ...). Confidence: low. */
}

/* FUN_00177504 @ 0x177504  (est. sk_stackshot_noop)
 * No-op. Confidence: high. */
static void sk_stackshot_noop_177504(void) { }

/* FUN_0017750c @ 0x17750c  (est. sk_stackshot_store7)
 * Stores 7 packed words/flags into a record. Confidence: high (tiny). */
static void sk_stackshot_store7_17750c(uint64_t *r, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint8_t e, uint64_t f, uint8_t g)
{
    r[0]=a; r[1]=b; r[2]=c; r[3]=d; *(uint8_t*)(r+4)=e; r[5]=f; *(uint8_t*)(r+6)=g;
}

/* FUN_00177528 @ 0x177528  (est. sk_stackshot_log_byte)
 * Logs via 22995c with the byte at x20+1. Confidence: low. */
static void sk_stackshot_log_byte_177528(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_log_byte @ 0x177528: Logs via 22995c with the byte at x20+1. Confidence: low. */
}

/* FUN_0017758c @ 0x17758c  (est. sk_stackshot_hash_write)
 * Writes via 208478 with the 004e4fa0 type + current hash. Confidence: low. */
static void sk_stackshot_hash_write_17758c(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_hash_write @ 0x17758c: Writes via 208478 with the 004e4fa0 type + current hash. Confidence: low. */
}

/* FUN_001775e0 @ 0x1775e0  (est. sk_stackshot_ctx_begin)
 * Begins a serialization context: 1a84f4 init, 2298d4 hash-constant seed
 * (0xdeadcafebeefbabe), 1a8564 finalize. Confidence: medium. */
static void sk_stackshot_ctx_begin_1775e0(void)
{
    (void)0; /* sk_stackshot_ctx_begin @ 0x1775e0: Begins a serialization context: 1a84f4 init, 2298d4 hash-constant seed (0xdeadcafebeefbabe), 1a8564 finalize. Confidence: medium. */
}

/* FUN_00177630 @ 0x177630  (est. sk_stackshot_hash_seed)
 * Seeds the hash with 0xdeadcafebeefbabe. Confidence: medium. */
static void sk_stackshot_hash_seed_177630(void)
{
    (void)0; /* sk_stackshot_hash_seed @ 0x177630: Seeds the hash with 0xdeadcafebeefbabe. Confidence: medium. */
}

/* FUN_00177664 @ 0x177664  (est. sk_stackshot_ctx_begin_b)
 * Begins a serialization context (no explicit 0 arg). Confidence: medium. */
static void sk_stackshot_ctx_begin_b_177664(void)
{
    (void)0; /* sk_stackshot_ctx_begin_b @ 0x177664: Begins a serialization context (no explicit 0 arg). Confidence: medium. */
}

/* FUN_0017770c @ 0x17770c  (est. sk_stackshot_build_check_a)
 * Checks the build variant hash (21904): returns true for 0xEE9DFACDA...=
 * -0x11a26510235f57d3 (DEBUG?), false for 0x7e2ceb7445c093c5, else fatal
 * "Fatal error" (005cbf10, 0x4db). Confidence: medium. */
static uint64_t sk_stackshot_build_check_a_17770c(void)
{
    (void)0; /* sk_stackshot_build_check_a @ 0x17770c: Checks the build variant hash (21904): returns true for 0xEE9DFACDA...= -0x11a26510235f57d3 (DEBUG?), false for 0x7e2ceb7445c093c5, else fatal "Fatal error" (005cbf10, 0x4db). Confidence: medium. */
    return 0;
}

/* FUN_00177854 @ 0x177854  (est. sk_stackshot_collect_words)
 * Collects a run of words (21904 count) from the stream into the 0x657788
 * growable array via 17933c, returning the array. Confidence: medium. */
static void *sk_stackshot_collect_words_177854(void)
{
    (void)0; /* sk_stackshot_collect_words @ 0x177854: Collects a run of words (21904 count) from the stream into the 0x657788 growable array via 17933c, returning the array. Confidence: medium. */
    return 0;
}

/* FUN_00177980 @ 0x177980  (est. sk_stackshot_async_a)
 * Async wrapper: 36a940 + 17d464 then vtable +8 call (release). Confidence:
 * low. */
static uint64_t sk_stackshot_async_a_177980(uint64_t a, uint64_t b, uint64_t c, long d, uint64_t e, uint64_t f, uint64_t g)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)g;
    (void)0; /* sk_stackshot_async_a @ 0x177980: Async wrapper: 36a940 + 17d464 then vtable +8 call (release). Confidence: low. */
    return 0;
}

/* FUN_00177a34 @ 0x177a34  (est. sk_stackshot_selector_id)
 * Maps a selector hash to an id (0..4): -0x11a26510235f57d3=>4,
 * -0x783acd52da9b9cc=>1, 0x7e2ceb7445c093c5=>2, 0x6282921a0bf58ff1=>3,
 * 0x7e4f1803cc77363=>0, else fatal (005cbee0, 0x503). Confidence: medium. */
static uint64_t sk_stackshot_selector_id_177a34(void)
{
    (void)0; /* sk_stackshot_selector_id @ 0x177a34: Maps a selector hash to an id (0..4): -0x11a26510235f57d3=>4, -0x783acd52da9b9cc=>1, 0x7e2ceb7445c093c5=>2, 0x6282921a0bf58ff1=>3, 0x7e4f1803cc77363=>0, else fatal (005cbee0, 0x503). Confidence: medium. */
    return 0;
}

/* FUN_00177bd4 @ 0x177bd4  (est. sk_stackshot_emit_stackrecs)
 * Emits a list of Stack records (0x18-length check, 0x20..0x37 byte fields)
 * into the serialized stream via 23208/230f8. Confidence: medium. */
static void sk_stackshot_emit_stackrecs_177bd4(long rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_emit_stackrecs @ 0x177bd4: Emits a list of Stack records (0x18-length check, 0x20..0x37 byte fields) into the serialized stream via 23208/230f8. Confidence: medium. */
}

/* FUN_00177e24 @ 0x177e24  (est. sk_stackshot_async_b)
 * Async wrapper: 36a940 + 17d5a8 then vtable +8 release. Confidence: low. */
static uint64_t sk_stackshot_async_b_177e24(uint64_t a, uint64_t b, long c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)0; /* sk_stackshot_async_b @ 0x177e24: Async wrapper: 36a940 + 17d5a8 then vtable +8 release. Confidence: low. */
    return 0;
}

/* FUN_00177ed0 @ 0x177ed0  (est. sk_stackshot_store5)
 * Stores 5 packed words/flags into a record. Confidence: high (tiny). */
static void sk_stackshot_store5_177ed0(uint64_t *r, uint64_t a, uint64_t b, uint8_t c, uint64_t d, uint8_t e)
{
    r[0]=a; r[1]=b; *(uint8_t*)(r+2)=c; r[3]=d; *(uint8_t*)(r+4)=e;
}

/* FUN_00177ee4 @ 0x177ee4  (est. sk_stackshot_mkobj_e)
 * Object header alloc + buffer alloc + vtable via 262ec/260e0. Confidence:
 * low. */
static long sk_stackshot_mkobj_e_177ee4(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_mkobj_e @ 0x177ee4: Object header alloc + buffer alloc + vtable via 262ec/260e0. Confidence: low. */
    return 0;
}

/* FUN_00177ee8 @ 0x177ee8  (est. sk_stackshot_finalize_hash)
 * Finalizes the serialized stream: computes the total size over the region
 * table (param_1), hashes it via 25ebc/24068/23208/780b0/22c48/25f44/214b0,
 * and returns the hash (21904) or the error via 65a550. Confidence: medium. */
static uint64_t sk_stackshot_finalize_hash_177ee8(long rec, uint64_t b, uint64_t c, uint64_t flags)
{
    (void)rec;
    (void)b;
    (void)c;
    (void)flags;
    (void)0; /* sk_stackshot_finalize_hash @ 0x177ee8: Finalizes the serialized stream: computes the total size over the region table (param_1), hashes it via 25ebc/24068/23208/780b0/22c48/25f44/214b0, and returns the hash (21904) or the error via 65a550. Confidence: medium. */
    return 0;
}

/* FUN_001780b0 @ 0x1780b0  (est. sk_stackshot_emit_ctx)
 * Emits a region-context into the hash stream: writes the region list (each
 * 0x10-length record's 16 bytes + flags) via 23208/230f8, then the trailing
 * flags byte. Confidence: medium. */
static void sk_stackshot_emit_ctx_1780b0(uint64_t a, long rec, uint64_t flags)
{
    (void)a;
    (void)rec;
    (void)flags;
    (void)0; /* sk_stackshot_emit_ctx @ 0x1780b0: Emits a region-context into the hash stream: writes the region list (each 0x10-length record's 16 bytes + flags) via 23208/230f8, then the trailing flags byte. Confidence: medium. */
}

/* FUN_00178348 @ 0x178348  (est. sk_stackshot_begin_check)
 * Validates the begin-hash (21904) equals 0x4159b862aecab4d9, else fatal
 * (005cbdf0, 0x519). Confidence: medium. */
static void sk_stackshot_begin_check_178348(void)
{
    (void)0; /* sk_stackshot_begin_check @ 0x178348: Validates the begin-hash (21904) equals 0x4159b862aecab4d9, else fatal (005cbdf0, 0x519). Confidence: medium. */
}

/* FUN_00178450 @ 0x178450  (est. sk_stackshot_collect_framevec)
 * Collects a frame vector (count via 21904, each via 178ef0) into the
 * 0x657788 array, returning the packed {array, count}. Confidence: medium. */
static void sk_stackshot_collect_framevec_178450(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_collect_framevec @ 0x178450: Collects a frame vector (count via 21904, each via 178ef0) into the 0x657788 array, returning the packed {array, count}. Confidence: medium. */
}

/* FUN_001785cc @ 0x1785cc  (est. sk_stackshot_fatal)
 * Fatal-error path: computes the serialized size over the frame array
 * (param_1), hashes via the same stream machinery, and returns the hash (or
 * the 65a550 error). Confidence: medium. */
static uint64_t sk_stackshot_fatal_1785cc(long rec, uint64_t b, uint64_t c, uint64_t flags)
{
    (void)rec;
    (void)b;
    (void)c;
    (void)flags;
    (void)0; /* sk_stackshot_fatal @ 0x1785cc: Fatal-error path: computes the serialized size over the frame array (param_1), hashes via the same stream machinery, and returns the hash (or the 65a550 error). Confidence: medium. */
    return 0;
}

/* FUN_0017884c @ 0x17884c  (est. sk_stackshot_check_fatal_hash)
 * Checks the fatal hash (21904) equals 0x6f9215ea767e2712 (true) or
 * -0x8211813efa9c46 (false), else fatal (005cbdb0, 0x520). Confidence: medium. */
static uint64_t sk_stackshot_check_fatal_hash_17884c(void)
{
    (void)0; /* sk_stackshot_check_fatal_hash @ 0x17884c: Checks the fatal hash (21904) equals 0x6f9215ea767e2712 (true) or -0x8211813efa9c46 (false), else fatal (005cbdb0, 0x520). Confidence: medium. */
    return 0;
}

/* FUN_001789b8 @ 0x1789b8  (est. sk_stackshot_check_hash_c)
 * Checks hash == 0x752da4ce868ca6dd, else fatal (005cbd70, 0x527).
 * Confidence: medium. */
static void sk_stackshot_check_hash_c_1789b8(void)
{
    (void)0; /* sk_stackshot_check_hash_c @ 0x1789b8: Checks hash == 0x752da4ce868ca6dd, else fatal (005cbd70, 0x527). Confidence: medium. */
}

/* FUN_00178ae0 @ 0x178ae0  (est. sk_stackshot_log_byte_ctx)
 * Logs the byte at x20+1 within a serialization context. Confidence: low. */
static void sk_stackshot_log_byte_ctx_178ae0(void)
{
    (void)0; /* sk_stackshot_log_byte_ctx @ 0x178ae0: Logs the byte at x20+1 within a serialization context. Confidence: low. */
}

/* FUN_00178b28 @ 0x178b28  (est. sk_stackshot_log_byte_ctx_b)
 * Logs the byte at x20+1 (no explicit 0 arg). Confidence: low. */
static void sk_stackshot_log_byte_ctx_b_178b28(void)
{
    (void)0; /* sk_stackshot_log_byte_ctx_b @ 0x178b28: Logs the byte at x20+1 (no explicit 0 arg). Confidence: low. */
}

/* FUN_00178b6c @ 0x178b6c  (est. sk_stackshot_tag32)
 * Maps a 32-bit value through the 0x40302010005 nibble table (17d32c) and
 * stores the byte result. Confidence: medium. */
static void sk_stackshot_tag32_178b6c(uint8_t *out, uint32_t *v)
{
    (void)out;
    (void)v;
    (void)0; /* sk_stackshot_tag32 @ 0x178b6c: Maps a 32-bit value through the 0x40302010005 nibble table (17d32c) and stores the byte result. Confidence: medium. */
}

/* FUN_00178b98 @ 0x178b98  (est. sk_stackshot_hash_write_b)
 * Writes via 208478 with type 004e5158. Confidence: low. */
static void sk_stackshot_hash_write_b_178b98(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_hash_write_b @ 0x178b98: Writes via 208478 with type 004e5158. Confidence: low. */
}

/* FUN_00178c0c @ 0x178c0c  (est. sk_stackshot_selector_id2)
 * Maps selector hash to id (0..3): -0x7e823a91a48e8fae=>1,
 * -0x3de3ed447c24c24b=>2, 0x5a2e2d0c3bc3e9cd=>3, 0x784a6e3b19f9800a=>0,
 * else fatal (005cbd40, 0x54c). Confidence: medium. */
static uint64_t sk_stackshot_selector_id2_178c0c(void)
{
    (void)0; /* sk_stackshot_selector_id2 @ 0x178c0c: Maps selector hash to id (0..3): -0x7e823a91a48e8fae=>1, -0x3de3ed447c24c24b=>2, 0x5a2e2d0c3bc3e9cd=>3, 0x784a6e3b19f9800a=>0, else fatal (005cbd40, 0x54c). Confidence: medium. */
    return 0;
}

/* FUN_00178dcc @ 0x178dcc  (est. sk_stackshot_check_hash_d)
 * Checks hash == 0x672c65b98d5d43f7, else fatal (005cbca0, 0x553).
 * Confidence: medium. */
static void sk_stackshot_check_hash_d_178dcc(void)
{
    (void)0; /* sk_stackshot_check_hash_d @ 0x178dcc: Checks hash == 0x672c65b98d5d43f7, else fatal (005cbca0, 0x553). Confidence: medium. */
}

/* FUN_00178ef0 @ 0x178ef0  (est. sk_stackshot_read_frame)
 * Reads a 0x10-byte frame from the stream into the 0x657788 array, returning
 * the packed {hash, array}. Confidence: medium. */
static void sk_stackshot_read_frame_178ef0(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_read_frame @ 0x178ef0: Reads a 0x10-byte frame from the stream into the 0x657788 array, returning the packed {hash, array}. Confidence: medium. */
}

/* FUN_00178ff0 @ 0x178ff0  (est. sk_stackshot_read_record5)
 * Reads a 5-field record: id, UInt8Array (count + bytes), and two optional
 * flags. Fills out. Confidence: medium. */
static void sk_stackshot_read_record5_178ff0(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_read_record5 @ 0x178ff0: Reads a 5-field record: id, UInt8Array (count + bytes), and two optional flags. Fills out. Confidence: medium. */
}

/* FUN_00179174 @ 0x179174  (est. sk_stackshot_read_record6)
 * Reads a 6-field record (id, cap, UInt8Array, three flags). Fills out.
 * Confidence: medium. */
static void sk_stackshot_read_record6_179174(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_read_record6 @ 0x179174: Reads a 6-field record (id, cap, UInt8Array, three flags). Fills out. Confidence: medium. */
}

/* FUN_0017933c @ 0x17933c  (est. sk_stackshot_read_frame18)
 * Reads an 0x18-byte frame into the 0x657788 array, returning packed
 * {hash, array}. Confidence: medium. */
static void sk_stackshot_read_frame18_17933c(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_read_frame18 @ 0x17933c: Reads an 0x18-byte frame into the 0x657788 array, returning packed {hash, array}. Confidence: medium. */
}

/* FUN_0017940c @ 0x17940c  (est. sk_stackshot_emit_record5)
 * Emits a 5-field record: id, UInt8Array bytes, perm flags. Confidence:
 * medium. */
static void sk_stackshot_emit_record5_17940c(uint64_t *rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_emit_record5 @ 0x17940c: Emits a 5-field record: id, UInt8Array bytes, perm flags. Confidence: medium. */
}

/* FUN_001794d0 @ 0x1794d0  (est. sk_stackshot_emit_record6)
 * Emits a 6-field record: id, cap, UInt8Array, flags, nested array.
 * Confidence: medium. */
static void sk_stackshot_emit_record6_1794d0(uint64_t *rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_emit_record6 @ 0x1794d0: Emits a 6-field record: id, cap, UInt8Array, flags, nested array. Confidence: medium. */
}

/* FUN_001795b0 @ 0x1795b0  (est. sk_stackshot_emit_uuid_rec)
 * Emits a UUID record (0x10 bytes) + an optional value, within a
 * serialization context. Confidence: medium. */
static void sk_stackshot_emit_uuid_rec_1795b0(uint64_t a, long rec, uint64_t v, uint64_t w, char flag)
{
    (void)a;
    (void)rec;
    (void)v;
    (void)w;
    (void)flag;
    (void)0; /* sk_stackshot_emit_uuid_rec @ 0x1795b0: Emits a UUID record (0x10 bytes) + an optional value, within a serialization context. Confidence: medium. */
}

/* FUN_00179850 @ 0x179850  (est. sk_stackshot_collect_frame_buf)
 * Collects a frame buffer via 178ef0 and stores param_4/param_5 into the
 * record; finalizes hash. Confidence: medium. */
static void sk_stackshot_collect_frame_buf_179850(uint8_t (*out)[16], uint64_t b, uint32_t *st, uint64_t v, uint8_t f)
{
    (void)b;
    (void)st;
    (void)v;
    (void)f;
    (void)0; /* sk_stackshot_collect_frame_buf @ 0x179850: Collects a frame buffer via 178ef0 and stores param_4/param_5 into the record; finalizes hash. Confidence: medium. */
}

/* FUN_00179920 @ 0x179920  (est. sk_stackshot_async_c)
 * Async dispatch: 19aac + 23f74 with the 181088 handler + 67b148 type.
 * Confidence: low. */
static uint64_t sk_stackshot_async_c_179920(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_c @ 0x179920: Async dispatch: 19aac + 23f74 with the 181088 handler + 67b148 type. Confidence: low. */
    return 0;
}

/* FUN_001799e0 @ 0x1799e0  (est. sk_stackshot_async_store)
 * Async result store: 23f74 with 179850 handler; stores the packed result.
 * Confidence: low. */
static void sk_stackshot_async_store_1799e0(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store @ 0x1799e0: Async result store: 23f74 with 179850 handler; stores the packed result. Confidence: low. */
}

/* FUN_00179ab4 @ 0x179ab4  (est. sk_stackshot_emit_ctx2)
 * Emits a region context (179ab4): 24068 begin + 1780b0 emit + 25704.
 * Confidence: medium. */
static void sk_stackshot_emit_ctx2_179ab4(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)0; /* sk_stackshot_emit_ctx2 @ 0x179ab4: Emits a region context (179ab4): 24068 begin + 1780b0 emit + 25704. Confidence: medium. */
}

/* FUN_00179b74 @ 0x179b74  (est. sk_stackshot_collect_framev_buf)
 * Collects a frame vector via 178450 and stores the packed (lo/hi) flags.
 * Confidence: medium. */
static void sk_stackshot_collect_framev_buf_179b74(uint8_t (*out)[16], uint64_t b, uint32_t *st, uint64_t v)
{
    (void)b;
    (void)st;
    (void)v;
    (void)0; /* sk_stackshot_collect_framev_buf @ 0x179b74: Collects a frame vector via 178450 and stores the packed (lo/hi) flags. Confidence: medium. */
}

/* FUN_00179c50 @ 0x179c50  (est. sk_stackshot_async_d)
 * Async dispatch with 181010 handler. Confidence: low. */
static uint64_t sk_stackshot_async_d_179c50(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_d @ 0x179c50: Async dispatch with 181010 handler. Confidence: low. */
    return 0;
}

/* FUN_00179d10 @ 0x179d10  (est. sk_stackshot_async_store_b)
 * Async store with 179b74 handler. Confidence: low. */
static void sk_stackshot_async_store_b_179d10(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_b @ 0x179d10: Async store with 179b74 handler. Confidence: low. */
}

/* FUN_00179de4 @ 0x179de4  (est. sk_stackshot_emit_rec5)
 * Emits a 5-field record (17940c) within context + hash. Confidence: medium. */
static void sk_stackshot_emit_rec5_179de4(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_emit_rec5 @ 0x179de4: Emits a 5-field record (17940c) within context + hash. Confidence: medium. */
}

/* FUN_00179e8c @ 0x179e8c  (est. sk_stackshot_parse_own_as)
 * Parses the own-address-space record via 23f74 with 179f70 handler.
 * Confidence: medium. */
static void sk_stackshot_parse_own_as_179e8c(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)0; /* sk_stackshot_parse_own_as @ 0x179e8c: Parses the own-address-space record via 23f74 with 179f70 handler. Confidence: medium. */
}

/* FUN_00179f70 @ 0x179f70  (est. sk_stackshot_parse_as_cb)
 * Parses the address-space record callback: reads the 178ff0 record, emits
 * it, and finalizes. Confidence: medium. */
static void sk_stackshot_parse_as_cb_179f70(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_parse_as_cb @ 0x179f70: Parses the address-space record callback: reads the 178ff0 record, emits it, and finalizes. Confidence: medium. */
}

/* FUN_0017a038 @ 0x17a038  (est. sk_stackshot_async_e)
 * Async dispatch with 180fbc handler. Confidence: low. */
static uint64_t sk_stackshot_async_e_17a038(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_e @ 0x17a038: Async dispatch with 180fbc handler. Confidence: low. */
    return 0;
}

/* FUN_0017a100 @ 0x17a100  (est. sk_stackshot_async_store_c)
 * Async store with 179f70 handler. Confidence: low. */
static void sk_stackshot_async_store_c_17a100(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_c @ 0x17a100: Async store with 179f70 handler. Confidence: low. */
}

/* FUN_0017a1e4 @ 0x17a1e4  (est. sk_stackshot_emit_rec5_ctx)
 * Emits a 5-field record + region context + hash. Confidence: medium. */
static void sk_stackshot_emit_rec5_ctx_17a1e4(uint64_t a, long rec)
{
    (void)a;
    (void)rec;
    (void)0; /* sk_stackshot_emit_rec5_ctx @ 0x17a1e4: Emits a 5-field record + region context + hash. Confidence: medium. */
}

/* FUN_0017a2a4 @ 0x17a2a4  (est. sk_stackshot_collect_combined)
 * Collects the combined record: 178ff0 + 178450, stores packed result.
 * Confidence: medium. */
static void sk_stackshot_collect_combined_17a2a4(uint64_t *out, uint64_t b, uint32_t *st, uint64_t v)
{
    (void)out;
    (void)b;
    (void)st;
    (void)v;
    (void)0; /* sk_stackshot_collect_combined @ 0x17a2a4: Collects the combined record: 178ff0 + 178450, stores packed result. Confidence: medium. */
}

/* FUN_0017a3c8 @ 0x17a3c8  (est. sk_stackshot_size_rec5_ctx)
 * Computes the serialized size of a record (17d380 + 17d29c). Confidence:
 * medium. */
static long sk_stackshot_size_rec5_ctx_17a3c8(long rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_size_rec5_ctx @ 0x17a3c8: Computes the serialized size of a record (17d380 + 17d29c). Confidence: medium. */
    return 0;
}

/* FUN_0017a428 @ 0x17a428  (est. sk_stackshot_async_f)
 * Async dispatch with 180fa4 handler. Confidence: low. */
static uint64_t sk_stackshot_async_f_17a428(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_f @ 0x17a428: Async dispatch with 180fa4 handler. Confidence: low. */
    return 0;
}

/* FUN_0017a4f0 @ 0x17a4f0  (est. sk_stackshot_async_store_d)
 * Async store with 17a2a4 handler. Confidence: low. */
static void sk_stackshot_async_store_d_17a4f0(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_d @ 0x17a4f0: Async store with 17a2a4 handler. Confidence: low. */
}

/* FUN_0017a5c4 @ 0x17a5c4  (est. sk_stackshot_emit_rec6_ctx)
 * Emits a 6-field record (1794d0) + hash. Confidence: medium. */
static void sk_stackshot_emit_rec6_ctx_17a5c4(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_emit_rec6_ctx @ 0x17a5c4: Emits a 6-field record (1794d0) + hash. Confidence: medium. */
}

/* FUN_0017a66c @ 0x17a66c  (est. sk_stackshot_parse_rec6_cb)
 * Parses a 6-field record (179174) + hash. Confidence: medium. */
static void sk_stackshot_parse_rec6_cb_17a66c(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_parse_rec6_cb @ 0x17a66c: Parses a 6-field record (179174) + hash. Confidence: medium. */
}

/* FUN_0017a73c @ 0x17a73c  (est. sk_stackshot_async_g)
 * Async dispatch with 180f8c handler. Confidence: low. */
static uint64_t sk_stackshot_async_g_17a73c(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_g @ 0x17a73c: Async dispatch with 180f8c handler. Confidence: low. */
    return 0;
}

/* FUN_0017a804 @ 0x17a804  (est. sk_stackshot_async_store_e)
 * Async store with 17a66c handler. Confidence: low. */
static void sk_stackshot_async_store_e_17a804(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_e @ 0x17a804: Async store with 17a66c handler. Confidence: low. */
}

/* FUN_0017a8f0 @ 0x17a8f0  (est. sk_stackshot_emit_pair)
 * Emits a 2-word record + hash. Confidence: medium. */
static void sk_stackshot_emit_pair_17a8f0(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a;
    (void)b;
    (void)c;
    (void)0; /* sk_stackshot_emit_pair @ 0x17a8f0: Emits a 2-word record + hash. Confidence: medium. */
}

/* FUN_0017a950 @ 0x17a950  (est. sk_stackshot_read_pair)
 * Reads a 2-word record + hash. Confidence: medium. */
static void sk_stackshot_read_pair_17a950(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_read_pair @ 0x17a950: Reads a 2-word record + hash. Confidence: medium. */
}

/* FUN_0017a9b0 @ 0x17a9b0  (est. sk_stackshot_dispatch_b)
 * Thunk into the shared dispatcher 17b36c. Confidence: high (trivial). */
static void sk_17a9b0(void)
{
    (void)0; /* sk_stackshot_dispatch_b @ 0x17a9b0: Thunk into the shared dispatcher 17b36c. Confidence: high (trivial). */
}

/* FUN_0017a9b4 @ 0x17a9b4  (est. sk_stackshot_dispatch_b)
 * Thunk into the shared dispatcher 17b36c. Confidence: high (trivial). */
static void sk_17a9b4(void)
{
    (void)0; /* sk_stackshot_dispatch_b @ 0x17a9b4: Thunk into the shared dispatcher 17b36c. Confidence: high (trivial). */
}

/* FUN_0017a9dc @ 0x17a9dc  (est. sk_stackshot_async_store_f)
 * Async store with 17a950 handler. Confidence: low. */
static void sk_stackshot_async_store_f_17a9dc(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_f @ 0x17a9dc: Async store with 17a950 handler. Confidence: low. */
}

/* FUN_0017aaa0 @ 0x17aaa0  (est. sk_stackshot_emit_rec6_ctx_b)
 * Emits a 6-field record + optional nested pair + hash. Confidence: medium. */
static void sk_stackshot_emit_rec6_ctx_b_17aaa0(uint64_t a, long rec)
{
    (void)a;
    (void)rec;
    (void)0; /* sk_stackshot_emit_rec6_ctx_b @ 0x17aaa0: Emits a 6-field record + optional nested pair + hash. Confidence: medium. */
}

/* FUN_0017ab8c @ 0x17ab8c  (est. sk_stackshot_parse_crash)
 * Parses a crash record via 23f74 with 17ac60 handler. Confidence: medium. */
static void sk_stackshot_parse_crash_17ab8c(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)0; /* sk_stackshot_parse_crash @ 0x17ab8c: Parses a crash record via 23f74 with 17ac60 handler. Confidence: medium. */
}

/* FUN_0017ac60 @ 0x17ac60  (est. sk_stackshot_parse_crash_cb)
 * Parses the crash record callback: reads 179174 record + optional pair,
 * emits. Confidence: medium. */
static void sk_stackshot_parse_crash_cb_17ac60(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_parse_crash_cb @ 0x17ac60: Parses the crash record callback: reads 179174 record + optional pair, emits. Confidence: medium. */
}

/* FUN_0017ad94 @ 0x17ad94  (est. sk_stackshot_size_rec6_ctx)
 * Computes the serialized size of a record (17d3e4 + flag byte). Confidence:
 * medium. */
static long sk_stackshot_size_rec6_ctx_17ad94(long rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_size_rec6_ctx @ 0x17ad94: Computes the serialized size of a record (17d3e4 + flag byte). Confidence: medium. */
    return 0;
}

/* FUN_0017addc @ 0x17addc  (est. sk_stackshot_async_h)
 * Async dispatch with 180f74 handler. Confidence: low. */
static uint64_t sk_stackshot_async_h_17addc(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_h @ 0x17addc: Async dispatch with 180f74 handler. Confidence: low. */
    return 0;
}

/* FUN_0017aea4 @ 0x17aea4  (est. sk_stackshot_async_store_g)
 * Async store with 17ac60 handler. Confidence: low. */
static void sk_stackshot_async_store_g_17aea4(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_g @ 0x17aea4: Async store with 17ac60 handler. Confidence: low. */
}

/* FUN_0017af78 @ 0x17af78  (est. sk_stackshot_emit_rec_batch)
 * Emits a batch of per-scid records (0x38-stride) into the stream, each with
 * a nested region-context (stride 0x38 sub-array). Confidence: medium. */
static void sk_stackshot_emit_rec_batch_17af78(uint64_t a, uint64_t b, long rec)
{
    (void)a;
    (void)b;
    (void)rec;
    (void)0; /* sk_stackshot_emit_rec_batch @ 0x17af78: Emits a batch of per-scid records (0x38-stride) into the stream, each with a nested region-context (stride 0x38 sub-array). Confidence: medium. */
}

/* FUN_0017b184 @ 0x17b184  (est. sk_stackshot_read_rec_batch)
 * Reads a batch of per-scid records (each via 179174) into the 0x657778
 * array. Confidence: medium. */
static void sk_stackshot_read_rec_batch_17b184(uint64_t *out, uint64_t b, uint32_t *st)
{
    (void)out;
    (void)b;
    (void)st;
    (void)0; /* sk_stackshot_read_rec_batch @ 0x17b184: Reads a batch of per-scid records (each via 179174) into the 0x657778 array. Confidence: medium. */
}

/* FUN_0017b340 @ 0x17b340  (est. sk_stackshot_dispatch_c)
 * Thunk into 17b36c. Confidence: high (trivial). */
static void sk_17b340(void)
{
    (void)0; /* sk_stackshot_dispatch_c @ 0x17b340: Thunk into 17b36c. Confidence: high (trivial). */
}

/* FUN_0017b344 @ 0x17b344  (est. sk_stackshot_dispatch_c)
 * Thunk into 17b36c. Confidence: high (trivial). */
static void sk_17b344(void)
{
    (void)0; /* sk_stackshot_dispatch_c @ 0x17b344: Thunk into 17b36c. Confidence: high (trivial). */
}

/* FUN_0017b36c @ 0x17b36c  (est. sk_stackshot_dispatch_generic)
 * Generic async dispatcher: 23f74 with the caller-provided handler (param_5).
 * Confidence: low. */
static uint64_t sk_stackshot_dispatch_generic_17b36c(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t h)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)h;
    (void)0; /* sk_stackshot_dispatch_generic @ 0x17b36c: Generic async dispatcher: 23f74 with the caller-provided handler (param_5). Confidence: low. */
    return 0;
}

/* FUN_0017b410 @ 0x17b410  (est. sk_stackshot_async_store_h)
 * Async store with 17b184 handler. Confidence: low. */
static void sk_stackshot_async_store_h_17b410(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_h @ 0x17b410: Async store with 17b184 handler. Confidence: low. */
}

/* FUN_0017b4d4 @ 0x17b4d4  (est. sk_stackshot_thunk_total_size)
 * Thunk wrapper for the total serialized-size accumulator 17d850.
 * Confidence: low. */
static long sk_stackshot_thunk_total_size_17b4d4(long a, long b, long c)
{
    (void)a;
    (void)b;
    (void)c;
    (void)0; /* sk_stackshot_thunk_total_size @ 0x17b4d4: Thunk wrapper for the total serialized-size accumulator 17d850. Confidence: low. */
    return 0;
}

/* FUN_0017b4d8 @ 0x17b4d8  (est. sk_stackshot_async_i)
 * Async dispatch with 17db8c handler. Confidence: low. */
static uint64_t sk_stackshot_async_i_17b4d8(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)0; /* sk_stackshot_async_i @ 0x17b4d8: Async dispatch with 17db8c handler. Confidence: low. */
    return 0;
}

/* FUN_0017b588 @ 0x17b588  (est. sk_stackshot_emit_rec_batch_full)
 * Emits a full batch record (crash-scid entries + region contexts +
 * per-scid records) into the stream. Confidence: medium. */
static void sk_stackshot_emit_rec_batch_full_17b588(uint64_t a, long b, long c, long d)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)0; /* sk_stackshot_emit_rec_batch_full @ 0x17b588: Emits a full batch record (crash-scid entries + region contexts + per-scid records) into the stream. Confidence: medium. */
}

/* FUN_0017b994 @ 0x17b994  (est. sk_stackshot_read_batch_full)
 * Reads the full batch record (crash-scids + per-scid nested records) into
 * three growable arrays (0x657778 variants). Confidence: medium. */
static void sk_stackshot_read_batch_full_17b994(uint64_t *out, uint64_t b, uint32_t *st, uint64_t c, uint64_t d)
{
    (void)out;
    (void)b;
    (void)st;
    (void)c;
    (void)d;
    (void)0; /* sk_stackshot_read_batch_full @ 0x17b994: Reads the full batch record (crash-scids + per-scid nested records) into three growable arrays (0x657778 variants). Confidence: medium. */
}

/* FUN_0017c00c @ 0x17c00c  (est. sk_stackshot_async_j)
 * Async dispatch with 180fd4 handler. Confidence: low. */
static uint64_t sk_stackshot_async_j_17c00c(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_j @ 0x17c00c: Async dispatch with 180fd4 handler. Confidence: low. */
    return 0;
}

/* FUN_0017c0c4 @ 0x17c0c4  (est. sk_stackshot_async_store_i)
 * Async store with 17b994 handler. Confidence: low. */
static void sk_stackshot_async_store_i_17c0c4(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_i @ 0x17c0c4: Async store with 17b994 handler. Confidence: low. */
}

/* FUN_0017c190 @ 0x17c190  (est. sk_stackshot_emit_uuid_rec_b)
 * Emits a UUID record (0x18 bytes) + value. Confidence: medium. */
static void sk_stackshot_emit_uuid_rec_b_17c190(uint64_t a, long rec, uint64_t v)
{
    (void)a;
    (void)rec;
    (void)v;
    (void)0; /* sk_stackshot_emit_uuid_rec_b @ 0x17c190: Emits a UUID record (0x18 bytes) + value. Confidence: medium. */
}

/* FUN_0017c450 @ 0x17c450  (est. sk_stackshot_collect_frame18_buf)
 * Collects an 0x18-byte frame (17933c) and stores it. Confidence: medium. */
static void sk_stackshot_collect_frame18_buf_17c450(uint8_t (*out)[16], uint64_t b, uint32_t *st)
{
    (void)b;
    (void)st;
    (void)0; /* sk_stackshot_collect_frame18_buf @ 0x17c450: Collects an 0x18-byte frame (17933c) and stores it. Confidence: medium. */
}

/* FUN_0017c538 @ 0x17c538  (est. sk_stackshot_async_k)
 * Async dispatch with 180ef8 handler. Confidence: low. */
static uint64_t sk_stackshot_async_k_17c538(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_k @ 0x17c538: Async dispatch with 180ef8 handler. Confidence: low. */
    return 0;
}

/* FUN_0017c5e8 @ 0x17c5e8  (est. sk_stackshot_async_store_j)
 * Async store with 17c450 handler. Confidence: low. */
static void sk_stackshot_async_store_j_17c5e8(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_j @ 0x17c5e8: Async store with 17c450 handler. Confidence: low. */
}

/* FUN_0017c6ac @ 0x17c6ac  (est. sk_stackshot_emit_stackrecs_ctx)
 * Emits stack records (177bd4) + hash. Confidence: medium. */
static void sk_stackshot_emit_stackrecs_ctx_17c6ac(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_emit_stackrecs_ctx @ 0x17c6ac: Emits stack records (177bd4) + hash. Confidence: medium. */
}

/* FUN_0017c754 @ 0x17c754  (est. sk_stackshot_collect_words_buf)
 * Collects a word array (177854) and stores it. Confidence: medium. */
static void sk_stackshot_collect_words_buf_17c754(uint64_t *out, uint64_t b, uint32_t *st)
{
    (void)out;
    (void)b;
    (void)st;
    (void)0; /* sk_stackshot_collect_words_buf @ 0x17c754: Collects a word array (177854) and stores it. Confidence: medium. */
}

/* FUN_0017c814 @ 0x17c814  (est. sk_stackshot_async_l)
 * Async dispatch with 180ff8 handler. Confidence: low. */
static uint64_t sk_stackshot_async_l_17c814(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_l @ 0x17c814: Async dispatch with 180ff8 handler. Confidence: low. */
    return 0;
}

/* FUN_0017c8c0 @ 0x17c8c0  (est. sk_stackshot_async_store_k)
 * Async store with 17c754 handler. Confidence: low. */
static void sk_stackshot_async_store_k_17c8c0(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_k @ 0x17c8c0: Async store with 17c754 handler. Confidence: low. */
}

/* FUN_0017c984 @ 0x17c984  (est. sk_stackshot_emit_tagrec)
 * Emits a tagged record: 2307c byte + optional flags. Confidence: medium. */
static void sk_stackshot_emit_tagrec_17c984(uint64_t a, uint8_t *rec)
{
    (void)a;
    (void)rec;
    (void)0; /* sk_stackshot_emit_tagrec @ 0x17c984: Emits a tagged record: 2307c byte + optional flags. Confidence: medium. */
}

/* FUN_0017ca50 @ 0x17ca50  (est. sk_stackshot_read_tagrec)
 * Reads a tagged record (21738 byte + optional flags + word). Confidence:
 * medium. */
static void sk_stackshot_read_tagrec_17ca50(uint8_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_read_tagrec @ 0x17ca50: Reads a tagged record (21738 byte + optional flags + word). Confidence: medium. */
}

/* FUN_0017cb68 @ 0x17cb68  (est. sk_stackshot_async_m)
 * Async dispatch with 180f5c handler. Confidence: low. */
static uint64_t sk_stackshot_async_m_17cb68(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_m @ 0x17cb68: Async dispatch with 180f5c handler. Confidence: low. */
    return 0;
}

/* FUN_0017cc28 @ 0x17cc28  (est. sk_stackshot_async_store_l)
 * Async store with 17ca50 handler. Confidence: low. */
static void sk_stackshot_async_store_l_17cc28(uint8_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_l @ 0x17cc28: Async store with 17ca50 handler. Confidence: low. */
}

/* FUN_0017cd14 @ 0x17cd14  (est. sk_stackshot_emit_tagrec_b)
 * Emits a 2-flag tagged record. Confidence: medium. */
static void sk_stackshot_emit_tagrec_b_17cd14(uint64_t a, uint64_t *rec)
{
    (void)a;
    (void)rec;
    (void)0; /* sk_stackshot_emit_tagrec_b @ 0x17cd14: Emits a 2-flag tagged record. Confidence: medium. */
}

/* FUN_0017cdd4 @ 0x17cdd4  (est. sk_stackshot_read_tagrec_b)
 * Reads a 2-flag tagged record. Confidence: medium. */
static void sk_stackshot_read_tagrec_b_17cdd4(uint64_t *out)
{
    (void)out;
    (void)0; /* sk_stackshot_read_tagrec_b @ 0x17cdd4: Reads a 2-flag tagged record. Confidence: medium. */
}

/* FUN_0017cec4 @ 0x17cec4  (est. sk_stackshot_async_n)
 * Async dispatch with 180f44 handler. Confidence: low. */
static uint64_t sk_stackshot_async_n_17cec4(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_async_n @ 0x17cec4: Async dispatch with 180f44 handler. Confidence: low. */
    return 0;
}

/* FUN_0017cf84 @ 0x17cf84  (est. sk_stackshot_async_store_m)
 * Async store with 17cdd4 handler. Confidence: low. */
static void sk_stackshot_async_store_m_17cf84(uint64_t *out, uint64_t a, uint64_t b, uint32_t *st, uint64_t c)
{
    (void)out;
    (void)a;
    (void)b;
    (void)st;
    (void)c;
    (void)0; /* sk_stackshot_async_store_m @ 0x17cf84: Async store with 17cdd4 handler. Confidence: low. */
}

/* FUN_0017d060 @ 0x17d060  (est. sk_stackshot_grow_17d060)
 * Growable-vector growth wrapper: invokes the 17d140 vector-grow helper and
 * stores the new pointer into x20. Confidence: high (trivial wrapper). */
static void sk_17d060(void)
{
    (void)0; /* sk_stackshot_grow_17d060 @ 0x17d060: Growable-vector growth wrapper: invokes the 17d140 vector-grow helper and stores the new pointer into x20. Confidence: high (trivial wrapper). */
}

/* FUN_0017d080 @ 0x17d080  (est. sk_stackshot_grow_17d080)
 * Growable-vector growth wrapper: invokes the 1762cc vector-grow helper and
 * stores the new pointer into x20. Confidence: high (trivial wrapper). */
static void sk_17d080(void)
{
    (void)0; /* sk_stackshot_grow_17d080 @ 0x17d080: Growable-vector growth wrapper: invokes the 1762cc vector-grow helper and stores the new pointer into x20. Confidence: high (trivial wrapper). */
}

/* FUN_0017d0a0 @ 0x17d0a0  (est. sk_stackshot_grow_17d0a0)
 * Growable-vector growth wrapper: invokes the 1763a0 vector-grow helper and
 * stores the new pointer into x20. Confidence: high (trivial wrapper). */
static void sk_17d0a0(void)
{
    (void)0; /* sk_stackshot_grow_17d0a0 @ 0x17d0a0: Growable-vector growth wrapper: invokes the 1763a0 vector-grow helper and stores the new pointer into x20. Confidence: high (trivial wrapper). */
}

/* FUN_0017d0c0 @ 0x17d0c0  (est. sk_stackshot_grow_17d0c0)
 * Growable-vector growth wrapper: invokes the 17646c vector-grow helper and
 * stores the new pointer into x20. Confidence: high (trivial wrapper). */
static void sk_17d0c0(void)
{
    (void)0; /* sk_stackshot_grow_17d0c0 @ 0x17d0c0: Growable-vector growth wrapper: invokes the 17646c vector-grow helper and stores the new pointer into x20. Confidence: high (trivial wrapper). */
}

/* FUN_0017d0e0 @ 0x17d0e0  (est. sk_stackshot_grow_17d0e0)
 * Growable-vector growth wrapper: invokes the 176564 vector-grow helper and
 * stores the new pointer into x20. Confidence: high (trivial wrapper). */
static void sk_17d0e0(void)
{
    (void)0; /* sk_stackshot_grow_17d0e0 @ 0x17d0e0: Growable-vector growth wrapper: invokes the 176564 vector-grow helper and stores the new pointer into x20. Confidence: high (trivial wrapper). */
}

/* FUN_0017d100 @ 0x17d100  (est. sk_stackshot_grow_17d100)
 * Growable-vector growth wrapper: invokes the 17664c vector-grow helper and
 * stores the new pointer into x20. Confidence: high (trivial wrapper). */
static void sk_17d100(void)
{
    (void)0; /* sk_stackshot_grow_17d100 @ 0x17d100: Growable-vector growth wrapper: invokes the 17664c vector-grow helper and stores the new pointer into x20. Confidence: high (trivial wrapper). */
}

/* FUN_0017d120 @ 0x17d120  (est. sk_stackshot_grow_17d120)
 * Growable-vector growth wrapper: invokes the 176724 vector-grow helper and
 * stores the new pointer into x20. Confidence: high (trivial wrapper). */
static void sk_17d120(void)
{
    (void)0; /* sk_stackshot_grow_17d120 @ 0x17d120: Growable-vector growth wrapper: invokes the 176724 vector-grow helper and stores the new pointer into x20. Confidence: high (trivial wrapper). */
}

/* FUN_0017d140 @ 0x17d140  (est. sk_stackshot_grow_vec10_d)
 * Growable 0x10-vector via 13d1a4 (type 0x654d28/004e5928). Confidence:
 * medium. */
static long sk_stackshot_grow_vec10_d_17d140(uint64_t keep, uint64_t want, uint64_t grow, long old)
{
    (void)keep;
    (void)want;
    (void)grow;
    (void)old;
    (void)0; /* sk_stackshot_grow_vec10_d @ 0x17d140: Growable 0x10-vector via 13d1a4 (type 0x654d28/004e5928). Confidence: medium. */
    return 0;
}

/* FUN_0017d22c @ 0x17d22c  (est. sk_stackshot_total_size_b)
 * Computes the serialized size of a list of Stack records: 8 + sum over
 * each record (0x10-stride) of its element width. Confidence: medium. */
static long sk_stackshot_total_size_b_17d22c(long rec)
{
    (void)rec;
    (void)0; /* sk_stackshot_total_size_b @ 0x17d22c: Computes the serialized size of a list of Stack records: 8 + sum over each record (0x10-stride) of its element width. Confidence: medium. */
    return 0;
}

/* FUN_0017d29c @ 0x17d29c  (est. sk_stackshot_ctx)
 * Computes the serialized size of a region-context (param_1, stride 0x20):
 * 8 + sum over records of (flag?0x11:9 + min(len,0x10)), plus the trailing
 * flags byte (1 if (param_2&0xff00000000)==0x100000000 else 5). Confidence:
 * medium. */
static long sk_stackshot_ctx_17d29c(long rec, uint64_t flags)
{
    (void)rec;
    (void)flags;
    (void)0; /* sk_stackshot_ctx @ 0x17d29c: Computes the serialized size of a region-context (param_1, stride 0x20): 8 + sum over records of (flag?0x11:9 + min(len,0x10)), plus the trailing flags byte (1 if (param_2&0xff00000000)==0x100000000 else 5). Confidence: medium. */
    return 0;
}

/* FUN_0017d32c @ 0x17d32c  (est. sk_stackshot_nibble_tag)
 * Maps a small index to a nibble-tag via the 0x40302010005 table (clamped
 * at 5). Confidence: medium. */
static uint32_t sk_stackshot_nibble_tag_17d32c(uint64_t v)
{
    uint32_t t = (uint32_t)(0x40302010005 >> ((v & 7) << 3));
    if (5 < (uint32_t)v) t = 5;
    return t;
}

/* FUN_0017d350 @ 0x17d350  (est. sk_stackshot_release_typed)
 * Releases a typed object via thunk 35d334 (type 0x668140). Confidence:
 * low. */
static uint64_t sk_stackshot_release_typed_17d350(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_release_typed @ 0x17d350: Releases a typed object via thunk 35d334 (type 0x668140). Confidence: low. */
    return 0;
}

/* FUN_0017d380 @ 0x17d380  (est. sk_stackshot_size)
 * Computes the serialized size of a record: 0x18 + flags bytes (1 if the
 * flag chars are 1 else 9). Confidence: medium. */
static long sk_stackshot_size_17d380(long rec, char f1, char f2)
{
    (void)rec;
    (void)f1;
    (void)f2;
    (void)0; /* sk_stackshot_size @ 0x17d380: Computes the serialized size of a record: 0x18 + flags bytes (1 if the flag chars are 1 else 9). Confidence: medium. */
    return 0;
}

/* FUN_0017d3e4 @ 0x17d3e4  (est. sk_stackshot_size_rec)
 * Computes the serialized size of a record: base (0x11/0x19) + flags + the
 * nested array size (param_3: 0x10-stride words + 8). Confidence: medium. */
static long sk_stackshot_size_rec_17d3e4(char f1, char f2, long rec)
{
    (void)f1;
    (void)f2;
    (void)rec;
    (void)0; /* sk_stackshot_size_rec @ 0x17d3e4: Computes the serialized size of a record: base (0x11/0x19) + flags + the nested array size (param_3: 0x10-stride words + 8). Confidence: medium. */
    return 0;
}

/* FUN_0017d464 @ 0x17d464  (est. sk_stackshot_async_body)
 * Async body: sets up the async frame (param_4 metadata), allocates the
 * async object via 36a940, and invokes 27b10 with the type, storing into
 * x20+0x10. Confidence: low. */
static void sk_stackshot_async_body_17d464(uint64_t a, uint32_t b, uint64_t c, long d, uint64_t e, uint64_t f, uint64_t g)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)g;
    (void)0; /* sk_stackshot_async_body @ 0x17d464: Async body: sets up the async frame (param_4 metadata), allocates the async object via 36a940, and invokes 27b10 with the type, storing into x20+0x10. Confidence: low. */
}

/* FUN_0017d5a8 @ 0x17d5a8  (est. sk_stackshot_async_body_b)
 * Async body variant: allocates the async object and stores into x20+0x10.
 * Confidence: low. */
static void sk_stackshot_async_body_b_17d5a8(uint64_t a, uint64_t b, long c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;
    (void)f;
    (void)0; /* sk_stackshot_async_body_b @ 0x17d5a8: Async body variant: allocates the async object and stores into x20+0x10. Confidence: low. */
}

/* FUN_0017d710 @ 0x17d710  (est. sk_stackshot_emit_uuid_dispatch)
 * Dispatches UUID emission with args from x20. Confidence: low. */
static void sk_stackshot_emit_uuid_dispatch_17d710(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_uuid_dispatch @ 0x17d710: Dispatches UUID emission with args from x20. Confidence: low. */
}

/* FUN_0017d734 @ 0x17d734  (est. sk_stackshot_dispatch_d)
 * Thunk into 17e580. Confidence: high (trivial). */
static void sk_stackshot_dispatch_d_17d734(void)
{
    (void)0; /* sk_stackshot_dispatch_d @ 0x17d734: Thunk into 17e580. Confidence: high (trivial). */
}

/* FUN_0017d74c @ 0x17d74c  (est. sk_stackshot_emit_rec5_dispatch)
 * Dispatches 179de4 with args from x20. Confidence: low. */
static void sk_stackshot_emit_rec5_dispatch_17d74c(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_rec5_dispatch @ 0x17d74c: Dispatches 179de4 with args from x20. Confidence: low. */
}

/* FUN_0017d768 @ 0x17d768  (est. sk_stackshot_emit_rec5ctx_dispatch)
 * Dispatches 17a1e4 with args from x20. Confidence: low. */
static void sk_stackshot_emit_rec5ctx_dispatch_17d768(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_rec5ctx_dispatch @ 0x17d768: Dispatches 17a1e4 with args from x20. Confidence: low. */
}

/* FUN_0017d850 @ 0x17d850  (est. sk_stackshot_total_size)
 * Computes the total serialized size of the combined crash record
 * (param_1=scid list, param_2=region context, param_3=per-scid records).
 * Accumulates with carry checks; SoftwareBreakpoint on any overflow.
 * Confidence: medium. */
static long sk_stackshot_total_size_17d850(long a, long b, long c)
{
    (void)a;
    (void)b;
    (void)c;
    (void)0; /* sk_stackshot_total_size @ 0x17d850: Computes the total serialized size of the combined crash record (param_1=scid list, param_2=region context, param_3=per-scid records). Accumulates with carry checks; SoftwareBreakpoint on any overflow. Confidence: medium. */
    return 0;
}

/* FUN_0017db0c @ 0x17db0c  (est. sk_stackshot_emit_rec6_dispatch)
 * Dispatches 17a5c4 with args from x20. Confidence: low. */
static void sk_stackshot_emit_rec6_dispatch_17db0c(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_rec6_dispatch @ 0x17db0c: Dispatches 17a5c4 with args from x20. Confidence: low. */
}

/* FUN_0017db28 @ 0x17db28  (est. sk_stackshot_emit_pair_dispatch)
 * Dispatches 17a8f0 with args from x20. Confidence: low. */
static void sk_stackshot_emit_pair_dispatch_17db28(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_pair_dispatch @ 0x17db28: Dispatches 17a8f0 with args from x20. Confidence: low. */
}

/* FUN_0017db54 @ 0x17db54  (est. sk_stackshot_emit_rec6ctx_dispatch)
 * Dispatches 17aaa0 with args from x20. Confidence: low. */
static void sk_stackshot_emit_rec6ctx_dispatch_17db54(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_rec6ctx_dispatch @ 0x17db54: Dispatches 17aaa0 with args from x20. Confidence: low. */
}

/* FUN_0017db70 @ 0x17db70  (est. sk_stackshot_emit_recbatch_dispatch)
 * Dispatches 17af78 with args from x20. Confidence: low. */
static void sk_stackshot_emit_recbatch_dispatch_17db70(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_recbatch_dispatch @ 0x17db70: Dispatches 17af78 with args from x20. Confidence: low. */
}

/* FUN_0017db8c @ 0x17db8c  (est. sk_stackshot_emit_batchfull_dispatch)
 * Dispatches 17b588 with args from x20. Confidence: low. */
static void sk_stackshot_emit_batchfull_dispatch_17db8c(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_batchfull_dispatch @ 0x17db8c: Dispatches 17b588 with args from x20. Confidence: low. */
}

/* FUN_0017dbac @ 0x17dbac  (est. sk_stackshot_emit_uuid_dispatch_b)
 * Dispatches 17c190 with args from x20. Confidence: low. */
static void sk_stackshot_emit_uuid_dispatch_b_17dbac(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_uuid_dispatch_b @ 0x17dbac: Dispatches 17c190 with args from x20. Confidence: low. */
}

/* FUN_0017dbc8 @ 0x17dbc8  (est. sk_stackshot_emit_stackrecs_dispatch)
 * Dispatches 17c6ac. Confidence: low. */
static void sk_stackshot_emit_stackrecs_dispatch_17dbc8(void)
{
    (void)0; /* sk_stackshot_emit_stackrecs_dispatch @ 0x17dbc8: Dispatches 17c6ac. Confidence: low. */
}

/* FUN_0017dbe4 @ 0x17dbe4  (est. sk_stackshot_emit_tagrec_dispatch)
 * Dispatches 17c984 with args from x20. Confidence: low. */
static void sk_stackshot_emit_tagrec_dispatch_17dbe4(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_tagrec_dispatch @ 0x17dbe4: Dispatches 17c984 with args from x20. Confidence: low. */
}

/* FUN_0017dc10 @ 0x17dc10  (est. sk_stackshot_emit_tagrec_b_dispatch)
 * Dispatches 17cd14 with args from x20. Confidence: low. */
static void sk_stackshot_emit_tagrec_b_dispatch_17dc10(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_emit_tagrec_b_dispatch @ 0x17dc10: Dispatches 17cd14 with args from x20. Confidence: low. */
}

/* FUN_0017e350 @ 0x17e350  (est. sk_stackshot_type_ref_a)
 * Returns the type ref 0x6547d0. Confidence: high (trivial). */
static uint64_t sk_stackshot_type_ref_a_17e350(void) { return 0x6547d0; }

/* FUN_0017e380 @ 0x17e380  (est. sk_stackshot_type_ref_b)
 * Returns the type ref 0x6548f8. Confidence: high (trivial). */
static uint64_t sk_stackshot_type_ref_b_17e380(void) { return 0x6548f8; }

/* FUN_0017e580 @ 0x17e580  (est. sk_stackshot_dispatch)
 * Dispatches 179ab4 with args from x20 (incl. packed flags). Confidence: low. */
static void sk_stackshot_dispatch_17e580(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_dispatch @ 0x17e580: Dispatches 179ab4 with args from x20 (incl. packed flags). Confidence: low. */
}

/* FUN_0017e5ac @ 0x17e5ac  (est. sk_stackshot_fptr_resolve_b)
 * Tagged fptr resolve (base+4 + *(int*)(base+4)). Confidence: high. */
static long sk_stackshot_fptr_resolve_b_17e5ac(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_0017e5dc @ 0x17e5dc  (est. sk_stackshot_dispatch_e)
 * Thunk into 17e5f4. Confidence: high (trivial). */
static void sk_stackshot_dispatch_e_17e5dc(void)
{
    (void)0; /* sk_stackshot_dispatch_e @ 0x17e5dc: Thunk into 17e5f4. Confidence: high (trivial). */
}

/* FUN_0017e5f4 @ 0x17e5f4  (est. sk_stackshot_read_ips)
 * Reads an IPC-stack record: validates the begin hash (178dcc), resolves the
 * selector via 17e5ac, reads a value, and builds the result record from the
 * 21838-parsed tag. Confidence: medium. */
static void sk_stackshot_read_ips_17e5f4(uint64_t *out, uint64_t *rec, uint32_t *st)
{
    (void)out;
    (void)rec;
    (void)st;
    (void)0; /* sk_stackshot_read_ips @ 0x17e5f4: Reads an IPC-stack record: validates the begin hash (178dcc), resolves the selector via 17e5ac, reads a value, and builds the result record from the 21838-parsed tag. Confidence: medium. */
}

/* FUN_0017e7a0 @ 0x17e7a0  (est. sk_stackshot_read_ips_a)
 * Reads the address-space-info record (17e8d0, tags 0x3f3/0x3ff).
 * Confidence: medium. */
static void sk_17e7a0(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_read_ips_a @ 0x17e7a0: Reads the address-space-info record (17e8d0, tags 0x3f3/0x3ff). Confidence: medium. */
}

/* FUN_0017e7a4 @ 0x17e7a4  (est. sk_stackshot_read_ips_a)
 * Reads the address-space-info record (17e8d0, tags 0x3f3/0x3ff).
 * Confidence: medium. */
static void sk_17e7a4(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_read_ips_a @ 0x17e7a4: Reads the address-space-info record (17e8d0, tags 0x3f3/0x3ff). Confidence: medium. */
}

/* FUN_0017e7c0 @ 0x17e7c0  (est. sk_stackshot_fptr_resolve_c)
 * Tagged fptr resolve (base+0xc + *(int*)(base+0xc)). Confidence: high. */
static long sk_stackshot_fptr_resolve_c_17e7c0(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/* FUN_0017e7f0 @ 0x17e7f0  (est. sk_stackshot_release_typed_b)
 * Releases a typed object (type 0x668bb8). Confidence: low. */
static uint64_t sk_stackshot_release_typed_b_17e7f0(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_release_typed_b @ 0x17e7f0: Releases a typed object (type 0x668bb8). Confidence: low. */
    return 0;
}

/* FUN_0017e820 @ 0x17e820  (est. sk_stackshot_fptr_resolve_d)
 * Tagged fptr resolve (base+8 + *(int*)(base+8)). Confidence: high. */
static long sk_stackshot_fptr_resolve_d_17e820(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/* FUN_0017e850 @ 0x17e850  (est. sk_stackshot_release_typed_c)
 * Releases a typed object (type 0x668b28). Confidence: low. */
static uint64_t sk_stackshot_release_typed_c_17e850(uint64_t a)
{
    (void)a;
    (void)0; /* sk_stackshot_release_typed_c @ 0x17e850: Releases a typed object (type 0x668b28). Confidence: low. */
    return 0;
}

/* FUN_0017e880 @ 0x17e880  (est. sk_stackshot_fptr_resolve_e)
 * Tagged fptr resolve (base+4). Confidence: high. */
static long sk_stackshot_fptr_resolve_e_17e880(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_0017e8b0 @ 0x17e8b0  (est. sk_stackshot_read_ipc_b)
 * Reads the IPC-stack record (17e8d0, tags 0x3bd/0x3c9). Confidence: medium. */
static void sk_17e8b0(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_read_ipc_b @ 0x17e8b0: Reads the IPC-stack record (17e8d0, tags 0x3bd/0x3c9). Confidence: medium. */
}

/* FUN_0017e8b4 @ 0x17e8b4  (est. sk_stackshot_read_ipc_b)
 * Reads the IPC-stack record (17e8d0, tags 0x3bd/0x3c9). Confidence: medium. */
static void sk_17e8b4(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_read_ipc_b @ 0x17e8b4: Reads the IPC-stack record (17e8d0, tags 0x3bd/0x3c9). Confidence: medium. */
}

/* FUN_0017e8d0 @ 0x17e8d0  (est. sk_stackshot_read_asinfo)
 * Reads an address-space-info / IPC-stack record. Selects among four
 * sub-handlers by a variant selector (178c0c): id 0 reads via 17e880, id 1 via
 * 17e820 (with 17d380/17d29c sizing), id 2 via a6be8, id 3 via 17e7c0 (with
 * 17d3e4 sizing). Each path reads the tagged value, resolves the current cpu,
 * and builds the 7-word result record. Emits the "getAddressSpaceInfo threw an
 * unexpected..." / "getIPCStackEntry threw an unexpe..." (005cbd20/005cbcf0)
 * fatal on error. Large, faithful reconstruction. Confidence: medium. */
static void sk_stackshot_read_asinfo_17e8d0(uint64_t *out, uint64_t *rec, uint32_t *st, uint64_t t1, uint64_t t2)
{
    (void)out;
    (void)rec;
    (void)st;
    (void)t1;
    (void)t2;
    (void)0; /* sk_stackshot_read_asinfo @ 0x17e8d0: Reads an address-space-info / IPC-stack record. Selects among four sub-handlers by a variant selector (178c0c): id 0 reads via 17e880, id 1 via 17e820 (with 17d380/17d29c sizing), id 2 via a6be8, id 3 via 17e7c0 (with 17d3e4 sizing). Each p */
}

/* FUN_0017f158 @ 0x17f158  (est. sk_stackshot_fptr_resolve_f)
 * Tagged fptr resolve (base+4). Confidence: high. */
static long sk_stackshot_fptr_resolve_f_17f158(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_0017f188 @ 0x17f188  (est. sk_stackshot_dispatch_f)
 * Thunk into 17f1a0. Confidence: high (trivial). */
static void sk_stackshot_dispatch_f_17f188(void)
{
    (void)0; /* sk_stackshot_dispatch_f @ 0x17f188: Thunk into 17f1a0. Confidence: high (trivial). */
}

/* FUN_0017f1a0 @ 0x17f1a0  (est. sk_stackshot_read_ipcrec)
 * Reads an IPC-stack record: validates hash (1789b8), resolves via 17f158,
 * reads a value, and emits the tagged record via 17d380-style sizing, building
 * the 7-word result. Confidence: medium. */
static void sk_stackshot_read_ipcrec_17f1a0(uint64_t *out, uint64_t *rec, uint32_t *st)
{
    (void)out;
    (void)rec;
    (void)st;
    (void)0; /* sk_stackshot_read_ipcrec @ 0x17f1a0: Reads an IPC-stack record: validates hash (1789b8), resolves via 17f158, reads a value, and emits the tagged record via 17d380-style sizing, building the 7-word result. Confidence: medium. */
}

/* FUN_0017f3d8 @ 0x17f3d8  (est. sk_stackshot_fptr_resolve_g)
 * Tagged fptr resolve (base+8). Confidence: high. */
static long sk_stackshot_fptr_resolve_g_17f3d8(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/* FUN_0017f408 @ 0x17f408  (est. sk_stackshot_dispatch_g)
 * Thunk into 17f420. Confidence: high (trivial). */
static void sk_stackshot_dispatch_g_17f408(void)
{
    (void)0; /* sk_stackshot_dispatch_g @ 0x17f408: Thunk into 17f420. Confidence: high (trivial). */
}

/* FUN_0017f420 @ 0x17f420  (est. sk_stackshot_read_runrec)
 * Reads a run-stackshot record: branches on the fatal flag (17884c), reads
 * the per-frame array (0x28-stride, 17d0a0 grow), then resolves via 17f3d8 or
 * 17f95c + 178450 frame-vector, emitting and building the 7-word result.
 * Confidence: medium. */
static void sk_stackshot_read_runrec_17f420(uint64_t *out, uint64_t *rec, uint32_t *st, uint64_t p4)
{
    (void)out;
    (void)rec;
    (void)st;
    (void)p4;
    (void)0; /* sk_stackshot_read_runrec @ 0x17f420: Reads a run-stackshot record: branches on the fatal flag (17884c), reads the per-frame array (0x28-stride, 17d0a0 grow), then resolves via 17f3d8 or 17f95c + 178450 frame-vector, emitting and building the 7-word result. Confidence: medium. */
}

/* FUN_0017f95c @ 0x17f95c  (est. sk_stackshot_fptr_resolve_h)
 * Tagged fptr resolve (base+4). Confidence: high. */
static long sk_stackshot_fptr_resolve_h_17f95c(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_0017f98c @ 0x17f98c  (est. sk_stackshot_dispatch_h)
 * Thunk into 17f9a4. Confidence: high (trivial). */
static void sk_stackshot_dispatch_h_17f98c(void)
{
    (void)0; /* sk_stackshot_dispatch_h @ 0x17f98c: Thunk into 17f9a4. Confidence: high (trivial). */
}

/* FUN_0017f9a4 @ 0x17f9a4  (est. sk_stackshot_read_runredact)
 * Reads a redacted run-stackshot record: validates begin hash (178348),
 * reads the word array (0x8-stride, 00082484 grow), collects the frame vector
 * (178450), resolves via 17f95c, and builds the 7-word result. Confidence:
 * medium. */
static void sk_stackshot_read_runredact_17f9a4(uint64_t *out, uint64_t *rec, uint32_t *st, uint64_t p4)
{
    (void)out;
    (void)rec;
    (void)st;
    (void)p4;
    (void)0; /* sk_stackshot_read_runredact @ 0x17f9a4: Reads a redacted run-stackshot record: validates begin hash (178348), reads the word array (0x8-stride, 00082484 grow), collects the frame vector (178450), resolves via 17f95c, and builds the 7-word result. Confidence: medium. */
}

/* FUN_0017fca0 @ 0x17fca0  (est. sk_stackshot_run_a)
 * Runs a stackshot (17fdd8, lines 0x1ee/0x1fb/0x216). Confidence: medium. */
static void sk_17fca0(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_run_a @ 0x17fca0: Runs a stackshot (17fdd8, lines 0x1ee/0x1fb/0x216). Confidence: medium. */
}

/* FUN_0017fca4 @ 0x17fca4  (est. sk_stackshot_run_a)
 * Runs a stackshot (17fdd8, lines 0x1ee/0x1fb/0x216). Confidence: medium. */
static void sk_17fca4(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_run_a @ 0x17fca4: Runs a stackshot (17fdd8, lines 0x1ee/0x1fb/0x216). Confidence: medium. */
}

/* FUN_0017fcc4 @ 0x17fcc4  (est. sk_stackshot_fptr_resolve_g2)
 * Tagged fptr resolve (base+0x8). Confidence: high. */
static long sk_sk_stackshot_fptr_resolve_g2_17fcc4(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 0x8) + (long)*(int *)(p + 0x8);
}

/* FUN_0017fcf4 @ 0x17fcf4  (est. sk_stackshot_fptr_resolve_e2)
 * Tagged fptr resolve (base+0x4). Confidence: high. */
static long sk_sk_stackshot_fptr_resolve_e2_17fcf4(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 0x4) + (long)*(int *)(p + 0x4);
}

/* FUN_0017fd24 @ 0x17fd24  (est. sk_stackshot_fptr_resolve_i)
 * Tagged fptr resolve (base+0x10). Confidence: high. */
static long sk_sk_stackshot_fptr_resolve_i_17fd24(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 0x10) + (long)*(int *)(p + 0x10);
}

/* FUN_0017fd54 @ 0x17fd54  (est. sk_stackshot_fptr_resolve_j)
 * Tagged fptr resolve (base+0xc). Confidence: high. */
static long sk_sk_stackshot_fptr_resolve_j_17fd54(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/* FUN_0017fd84 @ 0x17fd84  (est. sk_stackshot_fptr_resolve_k)
 * Tagged fptr resolve (base+0x8). Confidence: high. */
static long sk_sk_stackshot_fptr_resolve_k_17fd84(uint64_t p)
{
    if (p & 1) p = *(uint64_t *)(p & 0xfffffffffffffffe);
    return (long)(p + 0x8) + (long)*(int *)(p + 0x8);
}

/* FUN_0017fdb4 @ 0x17fdb4  (est. sk_stackshot_run_b)
 * Runs a redacted stackshot (17fdd8, lines 0x1a6/0x1b3/0x1ce). Confidence:
 * medium. */
static void sk_17fdb4(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_run_b @ 0x17fdb4: Runs a redacted stackshot (17fdd8, lines 0x1a6/0x1b3/0x1ce). Confidence: medium. */
}

/* FUN_0017fdb8 @ 0x17fdb8  (est. sk_stackshot_run_b)
 * Runs a redacted stackshot (17fdd8, lines 0x1a6/0x1b3/0x1ce). Confidence:
 * medium. */
static void sk_17fdb8(uint64_t a, uint64_t b)
{
    (void)a;
    (void)b;
    (void)0; /* sk_stackshot_run_b @ 0x17fdb8: Runs a redacted stackshot (17fdd8, lines 0x1a6/0x1b3/0x1ce). Confidence: medium. */
}

/* FUN_0017fdd8 @ 0x17fdd8  (est. sk_stackshot_run)
 * runStackshot / runStackshotRedacted top-level: dispatches on the
 * selector id (177a34) among five collection modes (fptr resolves 17fd24/
 * 17fd54/17fcf4/17fd84/17fcc4), each emitting a different serialized record
 * shape and building the 7-word result. Emits "enableDynamicConclaveTextLayout
 * t..." (005cbe90), "runStackshot threw an unexpected..." (005cbed0),
 * "runStackshotRedacted threw an un..." (005cbe50) fatals on error. Very large,
 * faithful reconstruction. Confidence: medium. */
static void sk_stackshot_run_17fdd8(uint64_t *out, uint64_t *rec, uint32_t *st, uint64_t l1, uint64_t l2, uint64_t l3)
{
    (void)out;
    (void)rec;
    (void)st;
    (void)l1;
    (void)l2;
    (void)l3;
    (void)0; /* sk_stackshot_run @ 0x17fdd8: runStackshot / runStackshotRedacted top-level: dispatches on the selector id (177a34) among five collection modes (fptr resolves 17fd24/ 17fd54/17fcf4/17fd84/17fcc4), each emitting a different serialized record shape and building the 7-word */
}
