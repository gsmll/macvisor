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
