/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 01: 0x80000-0x100000 caps region.
 * This slice is the VAS (virtual-address-space) management / exclave-launch
 * subsystem: vas slot allocator, vas operation dispatch, the
 * InternalExclaveLauncher device-tree mapping, and object/refcount glue. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; bodies reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_00077770 @ 0x77770 — indirect dispatch/log helper: invoked with a
 * target address (the constants passed are code addresses). */
extern void cL4_dispatch_77770(uint64_t target);
/* FUN_000027e8 @ 0x27e8 — return a dispatch-table pointer in x16 (register
 * return); the caller then calls the slot at [x16+off]. */
extern void cL4_table_prep_27e8(void);
/* FUN_00002534 @ 0x2534 — allocate/initialize an object from a type
 * descriptor (arg1) + meta (arg2); returns the object pointer. */
extern void *cL4_type_alloc_2534(void *type_desc, void *meta);
/* FUN_0006e7c0 @ 0x6e7c0 — clone/copy an object's fields into a
 * destination, calling the source's copy vtable entry. */
extern long cL4_obj_copy_6e7c0(long dst, long src);
/* FUN_001afa84 @ 0x1afa84 — noreturn fatal-error reporter (message, kind,
 * flags + varargs). */
extern void cL4_fatal_1afa84(void *msg, uint64_t kind, uint64_t flags, ...);
/* FUN_00310d68 @ 0x310d68 — object lookup by tag + argument; returns
 * {ptr, size} pair. */
extern uint64_t cL4_obj_lookup_310d68(uint64_t tag, uint64_t arg);
/* FUN_00374104 @ 0x374104 — object operation; returns {status, ptr}. */
extern uint64_t cL4_obj_op_374104(long obj, uint64_t a, uint64_t b, long *c, long *d);
/* FUN_0006d52c @ 0x6d52c — query; returns 0 or an owner/domain id. */
extern long cL4_query_d52c(void);
/* FUN_0006b79c @ 0x6b79c — query returning a handle/pointer (0 = none). */
extern long cL4_query_b79c(void);
/* FUN_0006b7ac @ 0x6b7ac — query returning a size (negative = error). */
extern long cL4_query_b7ac(void);
/* FUN_0006d024 @ 0x6d024 — query returning a value. */
extern uint64_t cL4_query_d024(uint64_t a);
/* FUN_0006d150 @ 0x6d150 — query returning an error code (negative = err). */
extern long cL4_query_d150(uint64_t a);
/* FUN_0006cf50 @ 0x6cf50 — query returning a value. */
extern uint64_t cL4_query_cf50(uint64_t a);
/* FUN_0006b77c @ 0x6b77c — release/commit a memory range. */
extern void cL4_mem_release_b77c(uint64_t base);
/* FUN_0006b78c @ 0x6b78c — release/commit a memory range. */
extern void cL4_mem_release_b78c(uint64_t base);
/* FUN_0006b2ec @ 0x6b2ec — return a {ptr, size} pair. */
extern uint64_t cL4_pair_b2ec(void);
/* FUN_00066254 @ 0x66254 — object/capability operation returning status. */
extern uint64_t cL4_op_66254(uint64_t a, uint64_t b, uint64_t *out);
/* FUN_0006b360 @ 0x6b360 — release/cleanup helper. */
extern void cL4_release_b360(uint64_t a, uint64_t b, uint64_t c);
/* FUN_0011d7e8 @ 0x11d7e8 — noreturn stack-canary-check panic on mismatch. */
extern void cL4_canary_panic_11d7e8(void);
/* FUN_00066558 @ 0x66558 — capability operation returning status. */
extern uint32_t cL4_op_66558(uint64_t fn, void *stack, uint64_t a, uint64_t b);
/* FUN_00067704 @ 0x67704 — object operation returning a 16-byte pair. */
extern uint64_t cL4_op_67704(uint64_t a, uint64_t b);
/* FUN_00086440 @ 0x86440 — helper (logs via cL4_dispatch_77770). */
extern void cL4_help_86440(uint64_t a);
/* FUN_00086590 @ 0x86590 — helper. */
extern void cL4_help_86590(uint64_t a);
/* FUN_00085a54 @ 0x85a54 — VAS map/create operation (vas op). */
extern void *cL4_vas_map_85a54(void *out, uint64_t size, uint8_t k, uint32_t fl, uint8_t f);
/* FUN_00034f70 @ 0x34f70 — VAS slot allocator; returns 0 on failure. */
extern long cL4_vas_slot_alloc_34f70(void);
/* FUN_002a4ab4 @ 0x2a4ab4 — log a string prefix/kind. */
extern void cL4_log_kind_2a4ab4(uint64_t kind);
/* FUN_003a25d4 @ 0x3a25d4 — log a pointer/value. */
extern void cL4_log_val_3a25d4(uint64_t v);
/* FUN_00294bdc @ 0x294bdc — log a message (msg, kind, flags). */
extern void cL4_log_msg_294bdc(const char *msg, uint64_t kind, uint64_t flags);
/* FUN_002acbb8 @ 0x2acbb8 — log a value pair (tag, value); args are passed
 * in registers and may be omitted. */
extern void cL4_log_pair_2acbb8(uint64_t tag, ...);
/* FUN_00027724 @ 0x27724 — fetch a function pointer by symbol/type; returns
 * a code address to call. */
extern void *cL4_fn_27724(uint64_t sym);
/* FUN_0036a9d4 @ 0x3a9d4 — allocate an object from a type descriptor. */
extern long cL4_alloc_3a9d4(uint64_t tag, long type_desc);
/* FUN_0036a940 @ 0x3a940 — allocate an object; returns pointer. */
extern void *cL4_alloc_3a940(uint64_t tag, uint64_t size, uint64_t flags);
/* FUN_0036a9a0 @ 0x3a9a0 — initialize an object header. */
extern long *cL4_obj_init_3a9a0(long obj, long *out);
/* FUN_0036a1a0 @ 0x3a1a0 — dispatch/call helper (async op). */
extern void cL4_dispatch_3a1a0(void *obj, uint64_t *stack, uint64_t flags, long pc);
/* FUN_00365b6c @ 0x365b6c — object call helper; returns status. */
extern uint64_t cL4_call_365b6c(void *a, void *b, uint64_t c, long d, uint64_t e);
/* FUN_0036b270 @ 0x3b270 — retain/refcount-increment helper. */
extern uint64_t cL4_retain_3a270(uint64_t v);
/* FUN_0036b118 @ 0x3b118 — release/refcount-decrement helper. */
extern void cL4_release_3a118(long v);
/* FUN_0036b6ac @ 0x3a6ac — release/destroy helper. */
extern void cL4_destroy_3a6ac(long v, uint64_t a, uint64_t b, uint64_t c);
/* FUN_00002688 @ 0x2688 — VAS helper. */
extern void cL4_help_2688(void);
/* FUN_0036b588 @ 0x3a588 — release helper. */
extern void cL4_release_3a588(long v);
/* FUN_0039a128 @ 0x3a128 — register a constructor/init for an object type. */
extern void cL4_ctor_3a128(uint64_t type, void *ctor);
/* FUN_0005acac @ 0x5acac — global/type lookup; returns pointer. */
extern long cL4_global_5acac(uint64_t id, uint64_t a, uint64_t b);
/* FUN_0006a4c0 @ 0x6a4c0 — object helper. */
extern void cL4_help_6a4c0(long obj, uint64_t a);
/* FUN_00077148 @ 0x77148 — fetch a function pointer; returns code*. */
extern void *cL4_fn_77148(uint64_t v);
/* FUN_00035944 @ 0x35944 — object op returning a 16-byte pair. */
extern uint64_t cL4_op_35944(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
/* FUN_000359d4 @ 0x359d4 — release a {ptr,size} pair. */
extern void cL4_release_359d4(uint64_t a, uint64_t b);
/* FUN_000026e8 @ 0x26e8 — release/cleanup helper. */
extern void cL4_release_26e8(uint64_t obj);
/* FUN_001ebfb0 @ 0x1ebfb0 — log/print a hex value. */
extern void cL4_log_hex_1ebfb0(void *out, uint64_t len, uint64_t fl, ...);
/* FUN_000552c0 @ 0x552c0 — device-tree property lookup. */
extern long cL4_dt_prop_552c0(uint64_t node, uint64_t kind, const char **name);
/* FUN_00151974 @ 0x151974 — get a timestamp/value pair. */
extern uint64_t cL4_ts_151974(void);
/* FUN_00151a6c @ 0x151a6c — log a message with address/kind. */
extern void cL4_log_151a6c(const void *fn, uint64_t a, const char *s, uint64_t b, uint64_t c, ...);
/* FUN_0026b434 @ 0x26b434 — map a range. */
extern void cL4_map_26b434(long obj, uint64_t size, uint64_t a, uint64_t b, uint64_t c);
/* FUN_0001e790 @ 0x1e790 — log helper. */
extern void cL4_log_1e790(void);
/* FUN_000867ec @ 0x867ec — no-op helper. */
extern void cL4_nop_867ec(void);
/* FUN_000867b4 @ 0x867b4 — no-op helper. */
extern void cL4_nop_867b4(void);
/* FUN_00086860 @ 0x86860 — no-op helper. */
extern void cL4_nop_86860(void);
/* FUN_00086840 @ 0x86840 — log helper. */
extern void cL4_log_86840(const char *msg);
/* FUN_00086410 @ 0x86410 — VAS operation. */
extern void cL4_vas_op_86410(uint64_t a, uint64_t b, uint64_t *msg);
/* FUN_00077070 @ 0x77070 — VAS helper. */
extern void cL4_help_77070(void);
/* FUN_000651bc @ 0x651bc — cleanup/commit helper. */
extern void cL4_commit_651bc(uint64_t v);
/* FUN_000867a8 @ 0x867a8 — helper. */
extern void cL4_help_867a8(uint64_t a, void *b);
/* FUN_00086434 @ 0x86434 — VAS op returning a 16-byte pair. */
extern uint64_t cL4_vas_op_86434(uint64_t a, uint64_t b);
/* FUN_0008647c @ 0x8647c — VAS op returning a 16-byte pair. */
extern uint64_t cL4_vas_op_8647c(uint64_t a, uint64_t b, uint64_t fl, uint64_t *k, void *out);
/* FUN_000867fc @ 0x867fc — helper. */
extern void cL4_help_867fc(void);
/* FUN_00085890 @ 0x85890 — VAS helper. */
extern void cL4_help_85890(uint64_t a, uint64_t b);
/* FUN_0006e6dc @ 0x6e6dc — flag/status getter. */
extern uint64_t cL4_status_6e6dc(uint64_t v);
/* FUN_00085b68 @ 0x85b68 — extract the top 16 bits of a value. */
extern uint64_t cL4_hi16_85b68(uint64_t v);
/* FUN_000867c4 @ 0x867c4 — log + trap helper. */
extern void cL4_log_trap_867c4(uint64_t code);
/* FUN_00117cc4 @ 0x117cc4 — helper. */
extern void cL4_help_117cc4(uint64_t a, uint64_t b);

/* Second-word (hi) halves of the aggregate-return helpers above. */
extern uint64_t cL4_obj_lookup_310d68_pair(void);
extern uint64_t cL4_obj_op_374104_pair(void);
extern uint64_t cL4_pair_b2ec2(void);
extern uint64_t cL4_op_67704_pair(void);
extern uint64_t cL4_ts_151974_pair(void);
extern uint64_t cL4_vas_op_86434_pair(void);
extern uint64_t cL4_op_35944_pair(void);

/* Register / context accessors (the decompiler surfaces values that arrive
 * in fixed registers or are carried in callee-saved registers x20..x22). */
extern void *cL4_table_current(void);          /* x16 from cL4_table_prep_27e8 */
extern long cL4_reg_x20(void);
extern long cL4_reg_x21(void);
extern long cL4_reg_x22(void);
extern long cL4_reg_x3(void);
extern long cL4_reg_x4(void);
extern uint64_t cL4_reg_x1(void);
extern uint64_t cL4_reg_x8(void);
extern uint32_t cL4_reg_w4(void);
extern bool cL4_flag_zr(void);
extern uint64_t cL4_tpidrro_el0(void);
extern void cL4_breakpoint(uint64_t addr);      /* SoftwareBreakpoint(1,addr) */
extern long cL4_cap_bitmap_slot(void);          /* FUN_00083f8c slot index */
extern void cL4_help_83a78(uint64_t *a, uint64_t *b);
extern void cL4_cap_destroy_ctx_pair(uint64_t a, uint64_t b, uint64_t *out);
extern void cL4_vas_map_slot(void *obj, uint64_t off, long slot);  /* [*obj+0x90] */

/* String constants referenced by the launcher/log paths. */
extern const char s_Fatal_error[];               /* s_Fatal_error_005accd0 "Fatal error" */

/* Globals written/read by the VAS global + device-tree paths. */
extern uint64_t _DAT_006ad998;
extern uint64_t _DAT_004bbff0;
extern uint64_t _DAT_004bbff8;
extern uint64_t _DAT_004baeb0;
extern uint64_t uRam_004baeb8;

/* Global: the current thread / TCB pointer. */
extern unsigned long cL4_current_thread;  /* _DAT_006c0380 */

/* Forward declarations of in-slice functions called out of order. */
uint64_t FUN_00083e9c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_000841a0(void);
void *FUN_00084368(void);
void FUN_00084824(uint64_t param_1, uint64_t param_2, uint64_t param_3);
uint64_t FUN_00084848(uint64_t param_1, uint64_t *param_2, uint64_t *param_3);
uint32_t FUN_00084948(uint64_t param_1);
void FUN_0008499c(void);
void FUN_000849c8(uint64_t *param_1);
void FUN_00084a74(long *param_1);
void *FUN_00084af0(uint64_t *out_pair);
uint32_t FUN_00084cc4(uint32_t param_1, uint32_t param_2);
void FUN_00085140(void);
void *FUN_000851d0(uint64_t *out_pair);
void FUN_00085258(uint64_t param_1, long param_2, uint64_t param_3);
void FUN_000854bc(void);
void FUN_0008553c(void);
uint8_t FUN_00084de4(uint64_t param_1, void *param_2, uint64_t param_3, uint64_t param_4);
void *FUN_00084ee0(uint64_t param_1, uint64_t *out_pair);

/* ------------------------------------------------------------------ *
 * Function bodies (address order).
 * ------------------------------------------------------------------ */

/* FUN_00083acc @ 0x83acc   (est. cL4_dispatch_trampoline)
 * Ghidra: undefined8 FUN_00083acc(undefined8 param_1)
 * Calls the global function pointer _DAT_39000062d4000009 with no arguments
 * and returns param_1 unchanged. A thin indirect-dispatch trampoline.
 * Confidence: low
 * Notes: _DAT_39000062d4000009 is a global code pointer. */
uint64_t FUN_00083acc(uint64_t param_1)
{
    extern void (*global_dispatch)(void);  /* _DAT_39000062d4000009 */
    global_dispatch();
    return param_1;
}

/* FUN_00083b18 @ 0x83b18   (est. cL4_table_get_60)
 * Ghidra: void FUN_00083b18(undefined8 *param_1)
 * Prepares a dispatch table (FUN_000027e8) then calls the slot at [table+0x60]
 * and stores the 8-byte result into *param_1.
 * Confidence: low
 * Notes: table pointer returned in x16 by cL4_table_prep_27e8. */
void FUN_00083b18(uint64_t *param_1)
{
    uint64_t *table;
    cL4_table_prep_27e8();
    table = cL4_table_current();              /* x16 returned by prep */
    *param_1 = ((uint64_t (*)(void))(table[0x60 / 8]))();
}

/* FUN_00083b58 @ 0x83b58   (est. cL4_table_call_68)
 * Ghidra: void FUN_00083b58(undefined8 *param_1)
 * Prepares a dispatch table, forwarding *param_1 into the prep, then calls
 * the slot at [table+0x68].
 * Confidence: low
 * Notes: table pointer returned in x16 by cL4_table_prep_27e8. */
void FUN_00083b58(uint64_t *param_1)
{
    uint64_t *table;
    cL4_table_prep_27e8();
    table = cL4_table_current();
    ((void (*)(void))(table[0x68 / 8]))();
}

/* FUN_00083b94 @ 0x83b94   (est. cL4_table_get16_78)
 * Ghidra: void FUN_00083b94(undefined1 (*param_1) [16])
 * Prepares a dispatch table then calls the slot at [table+0x78], which
 * returns a 16-byte pair that is stored into param_1[0..15].
 * Confidence: low
 * Notes: table pointer returned in x16 by cL4_table_prep_27e8. */
void FUN_00083b94(uint64_t *param_1)
{
    uint64_t *table;
    uint64_t pair[2];
    cL4_table_prep_27e8();
    table = cL4_table_current();
    ((uint64_t (*)(void))(table[0x78 / 8]))();
    /* 16-byte aggregate result copied to *param_1 (decompiler folded) */
    param_1[0] = pair[0];
    param_1[1] = pair[1];
}

/* FUN_00083be0 @ 0x83be0   (est. cL4_msg_83be0)
 * Ghidra: void FUN_00083be0(void)
 * Thin wrapper: dispatches the code address _DAT_0064ea20 via
 * cL4_dispatch_77770. Likely a named failure/message handler slot.
 * Confidence: low
 * Notes: target _DAT_0064ea20 holds code (not a string). */
void FUN_00083be0(void)
{
    cL4_dispatch_77770(0x64ea20);
}

/* FUN_00083c34 @ 0x83c34   (est. cL4_msg_83c34)
 * Ghidra: void FUN_00083c34(void)
 * Thin wrapper: dispatches the code address _DAT_0064eae8.
 * Confidence: low */
void FUN_00083c34(void)
{
    cL4_dispatch_77770(0x64eae8);
}

/* FUN_00083c40 @ 0x83c40   (est. cL4_msg_83c40)
 * Ghidra: void FUN_00083c40(void)
 * Thin wrapper: dispatches the code address 0x64eb48.
 * Confidence: low */
void FUN_00083c40(void)
{
    cL4_dispatch_77770(0x64eb48);
}

/* FUN_00083c4c @ 0x83c4c   (est. cL4_msg_83c4c)
 * Ghidra: void FUN_00083c4c(void)
 * Thin wrapper: dispatches the code address 0x64ebd0.
 * Confidence: low */
void FUN_00083c4c(void)
{
    cL4_dispatch_77770(0x64ebd0);
}

/* FUN_00083c58 @ 0x83c58   (est. cL4_msg_83c58)
 * Ghidra: void FUN_00083c58(void)
 * Thin wrapper: dispatches the code address 0x64ec50.
 * Confidence: low */
void FUN_00083c58(void)
{
    cL4_dispatch_77770(0x64ec50);
}

/* FUN_00083c64 @ 0x83c64   (est. cL4_msg_83c64)
 * Ghidra: void FUN_00083c64(void)
 * Thin wrapper: dispatches the code address 0x64ed30.
 * Confidence: low */
void FUN_00083c64(void)
{
    cL4_dispatch_77770(0x64ed30);
}

/* FUN_00083c70 @ 0x83c70   (est. cL4_msg_83c70)
 * Ghidra: void FUN_00083c70(void)
 * Thin wrapper: dispatches the code address 0x64eda8.
 * Confidence: low */
void FUN_00083c70(void)
{
    cL4_dispatch_77770(0x64eda8);
}

/* FUN_00083c7c @ 0x83c7c   (est. cL4_obj_probe)
 * Ghidra: undefined1[16] FUN_00083c7c(long param_1)
 * Looks up an object by tag 0x13f using the value at param_1+0x38. If the
 * returned size is < 0x40, calls cL4_obj_op_374104 to (re)size it to
 * (*ptr - 8) + 0x40; on success returns {0,0}, else returns the op's pair.
 * If the probe size was already >= 0x40 returns {ptr, 0x3f}.
 * Confidence: medium
 * Notes: 16-byte aggregate returns {ptr,size}. */
void *FUN_00083c7c(long param_1, uint64_t *out_pair)
{
    uint64_t probe[2];
    uint64_t op[2];
    long newsize;
    probe[0] = cL4_obj_lookup_310d68(0x13f, *(uint64_t *)(param_1 + 0x38));
    probe[1] = cL4_obj_lookup_310d68_pair();      /* second word of lookup */
    if (probe[1] < 0x40) {
        newsize = *(long *)(probe[0] - 8) + 0x40;
        op[0] = cL4_obj_op_374104(param_1, 0, 1, &newsize, (long *)(param_1 + 0x48));
        op[1] = cL4_obj_op_374104_pair();
        if (op[0] == 0) {
            out_pair[0] = 0;
            out_pair[1] = 0;
            return out_pair;
        }
        out_pair[0] = op[0];
        out_pair[1] = op[1];
        return out_pair;
    }
    out_pair[0] = probe[0];
    out_pair[1] = 0x3f;
    return out_pair;
}

/* FUN_00083cfc @ 0x83cfc   (est. cL4_msg_83cfc)
 * Ghidra: void FUN_00083cfc(void)
 * Thin wrapper: dispatches the code address 0x64ef30.
 * Confidence: low */
void FUN_00083cfc(void)
{
    cL4_dispatch_77770(0x64ef30);
}

/* FUN_00083d08 @ 0x83d08   (est. cL4_msg_83d08)
 * Ghidra: void FUN_00083d08(void)
 * Thin wrapper: dispatches the code address 0x64efa0.
 * Confidence: low */
void FUN_00083d08(void)
{
    cL4_dispatch_77770(0x64efa0);
}

/* FUN_00083d14 @ 0x83d14   (est. cL4_msg_83d14)
 * Ghidra: void FUN_00083d14(void)
 * Thin wrapper: dispatches the code address 0x64f010.
 * Confidence: low */
void FUN_00083d14(void)
{
    cL4_dispatch_77770(0x64f010);
}

/* FUN_00083d20 @ 0x83d20   (est. cL4_msg_83d20)
 * Ghidra: void FUN_00083d20(void)
 * Thin wrapper: dispatches the code address 0x64f080.
 * Confidence: low */
void FUN_00083d20(void)
{
    cL4_dispatch_77770(0x64f080);
}

/* FUN_00083d2c @ 0x83d2c   (est. cL4_vas_iterate)
 * Ghidra: void FUN_00083d2c(undefined8 *param_1)
 * Walks a VAS slot structure: while the current entry (x20[2]) is nonzero,
 * if it is not yet initialized, copies a 40-byte record from it into
 * param_1[0..4] and returns. Otherwise re-initializes the entry (clears the
 * 5-word output and calls FUN_00083e9c to allocate a fresh object). Then
 * advances the iterator to the next free slot, cloning the previous object
 * (cL4_obj_copy_6e7c0 path) and resets the cursor. When no slots remain,
 * zeroes param_1[0..4].
 * Confidence: medium
 * Notes: state machine with breakpoints on invariant violations (0x83e30,
 *   0x83e34). */
void FUN_00083d2c(uint64_t *param_1)
{
    extern long *g_vas_state;   /* unaff_x20 */
    long entry = g_vas_state[2];

    for (;;) {
        if (entry != 0) {
            uint64_t idx = g_vas_state[3];
            if (idx != *(uint64_t *)(entry + 0x10)) {
                if (idx < *(uint64_t *)(entry + 0x10)) {
                    uint64_t rec[5];
                    cL4_obj_copy_6e7c0(entry + (long)idx * 0x28 + 0x20,
                                       (long)(void *)&rec);
                    g_vas_state[3] = idx + 1;
                    param_1[1] = rec[1];
                    param_1[0] = rec[0];
                    param_1[3] = rec[3];
                    param_1[2] = rec[2];
                    param_1[4] = rec[4];
                    return;
                }
                cL4_breakpoint(0x83e34);   /* invariant violated */
            }
            param_1[0] = 0;
            param_1[1] = 0;
            param_1[2] = 0;
            param_1[3] = 0;
            param_1[4] = 0;
            cL4_type_alloc_2534((void *)0x64f0e0, (void *)0x4c1000);  /* via 83e9c */
        }
        {
            uint64_t n = g_vas_state[1];
            uint64_t cap = *(uint64_t *)(g_vas_state[0] + 0x10);
            if (n == cap) break;
            if (cap <= n)
                cL4_breakpoint(0x83e30);    /* invariant violated */
            entry = *(long *)(g_vas_state[0] + n * 8 + 0x20);
            g_vas_state[1] = n + 1;
            {
                long prev = g_vas_state[2];
                cL4_retain_3a270((uint64_t)entry);
                cL4_release_3a118(prev);
                g_vas_state[2] = entry;
                g_vas_state[3] = 0;
            }
        }
    }
    param_1[0] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
}

/* FUN_00083e34 @ 0x83e34   (est. cL4_vas_alloc_init)
 * Ghidra: undefined8 FUN_00083e34(undefined8 param_1, undefined8 param_2)
 * Allocates an object via cL4_type_alloc_2534(0x64f0e0, _DAT_004c1000) then
 * calls its vtable init slot (at [obj-8]+0x10) with (param_2, param_1, obj).
 * Returns param_2.
 * Confidence: low
 * Notes: _DAT_004c1000 type meta. */
uint64_t FUN_00083e34(uint64_t param_1, uint64_t param_2)
{
    long obj;
    obj = (long)cL4_type_alloc_2534((void *)0x64f0e0, (void *)0x4c1000);
    ((uint64_t (*)(uint64_t, uint64_t, long))(*(long *)(obj - 8) + 0x10))(
        param_2, param_1, obj);
    return param_2;
}

/* FUN_00083e9c @ 0x83e9c   (est. cL4_vas_obj_init)
 * Ghidra: undefined8 FUN_00083e9c(undefined8 param_1, undefined8 param_2,
 *        undefined8 param_3)
 * Allocates an object (cL4_type_alloc_2534), calls the no-op FUN_000841a0,
 * then invokes the table slot at [x16+8] on param_1. Returns param_1.
 * Confidence: low
 * Notes: table pointer in x16; FUN_000841a0 is a no-op. */
uint64_t FUN_00083e9c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    cL4_type_alloc_2534((void *)param_2, (void *)param_3);
    FUN_000841a0();
    /* [x16+8] table dispatch on param_1 */
    return param_1;
}

/* thunk_FUN_00081ce8 @ 0x83f00   (est. cL4_cap_set_add)
 * Ghidra: void thunk_FUN_00081ce8(..., long param_4)
 * Sets capability slot param_3 in a bitmap (via FUN_00083f8c) and bumps the
 * count at param_4+0x10, trapping on overflow (SoftwareBreakpoint 0x81d14).
 * Confidence: medium
 * Notes: bitmap slot selected by FUN_00083f8c return. */
void FUN_00083f00(uint64_t param_1, uint64_t param_2, uint64_t param_3, long param_4)
{
    long slot;
    slot = cL4_cap_bitmap_slot();                 /* FUN_00083f8c */
    *(uint64_t *)(cL4_table_current() + slot * 8) = param_3;
    if (!__builtin_add_overflow(*(long *)(param_4 + 0x10), 1, &(long){0})) {
        *(long *)(param_4 + 0x10) = *(long *)(param_4 + 0x10) + 1;
        return;
    }
    cL4_breakpoint(0x81d14);                      /* overflow */
}

/* thunk_FUN_0006afb4 @ 0x83f04   (est. cL4_cap_mask_build)
 * Ghidra: void thunk_FUN_0006afb4(long *param_1, long param_2)
 * Builds a 5-word capability/mask record into param_1 from param_2: a mask
 * derived from the byte at param_2+0x20, base pointers param_2 / param_2+0x40,
 * and a masked copy of the value at param_2+0x40.
 * Confidence: medium
 * Notes: word0=obj, word1=obj+0x40, word2=~mask, word3=0, word4=mask&val. */
void FUN_00083f04(long *param_1, long param_2)
{
    uint64_t shift = *(uint8_t *)(param_2 + 0x20) & 0x3f;
    uint64_t mask = (uint64_t)-1 << shift;
    uint64_t val = *(uint64_t *)(param_2 + 0x40);
    uint64_t neg = -mask;
    uint64_t lo = 0xffffffffffffffff;
    if (neg < 0x40)
        lo = ~((uint64_t)-1 << (neg & 0x3f));
    param_1[0] = param_2;
    param_1[1] = param_2 + 0x40;
    param_1[2] = ~mask;
    param_1[3] = 0;
    param_1[4] = lo & val;
}

/* thunk_FUN_0001612c @ 0x83f08   (est. cL4_obj_field_10)
 * Ghidra: undefined8 thunk_FUN_0001612c(long param_1)
 * Returns the 8-byte field at param_1+0x10.
 * Confidence: high */
uint64_t FUN_00083f08(long param_1)
{
    return *(uint64_t *)(param_1 + 0x10);
}

/* thunk_FUN_0008192c @ 0x83f1c   (est. cL4_cap_index_check)
 * Ghidra: void thunk_FUN_0008192c(ulong param_1, undefined8 param_2, long param_3)
 * Validates that capability index param_1 is non-negative and < the count at
 * param_3+0x10, trapping (SoftwareBreakpoint) otherwise.
 * Confidence: medium
 * Notes: breakpoints 0x81944 (negative) and 0x81948 (>= limit). */
void FUN_00083f1c(uint64_t param_1, uint64_t param_2, long param_3)
{
    if ((long)param_1 < 0)
        cL4_breakpoint(0x81944);
    if (param_1 < *(uint64_t *)(param_3 + 0x10))
        return;
    cL4_breakpoint(0x81948);
}

/* FUN_00083f24 @ 0x83f24   (est. cL4_fatal_error_pair)
 * Ghidra: undefined1[16] FUN_00083f24(void)
 * Returns the 16-byte pair {s_Fatal_error_005accd0, 0xb} — a fatal-error
 * message pointer plus kind.
 * Confidence: medium
 * Notes: s_Fatal_error_005accd0 = "Fatal error". */
void *FUN_00083f24(uint64_t *out_pair)
{
    out_pair[0] = (uint64_t)s_Fatal_error;
    out_pair[1] = 0xb;
    return out_pair;
}

/* FUN_00083f48 @ 0x83f48   (est. cL4_fatal_error_string)
 * Ghidra: char * FUN_00083f48(void)
 * Returns the "Fatal error" string.
 * Confidence: high */
const char *FUN_00083f48(void)
{
    return s_Fatal_error;
}

/* FUN_00083f5c @ 0x83f5c   (est. cL4_cap_sum)
 * Ghidra: long FUN_00083f5c(long param_1)
 * Returns *(g_vas_state + 0x10) + *(param_1 + 0x10).
 * Confidence: low */
long FUN_00083f5c(long param_1)
{
    extern long *g_vas_state;   /* unaff_x20 */
    return *(long *)(g_vas_state[0] + 0x10) + *(long *)(param_1 + 0x10);
}

/* FUN_00083f74 @ 0x83f74   (est. cL4_nop_handler)
 * Ghidra: void FUN_00083f74(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00083f74(void)
{
    return;
}

/* FUN_00083f8c @ 0x83f8c   (est. cL4_cap_bitmap_set)
 * Ghidra: void FUN_00083f8c(ulong param_1, undefined8 param_2, ...)
 * Sets bit param_1 in the bitmap at param_4+0x40 and stores param_2 into the
 * slot array at *(param_4+0x30) + param_1*8.
 * Confidence: medium
 * Notes: bitmap layout: bits at [base+0x40], slot array at [base+0x30]. */
void FUN_00083f8c(uint64_t param_1, uint64_t param_2, uint64_t param_3, long param_4)
{
    long w = param_4 + (param_1 >> 6) * 8;
    *(uint64_t *)(w + 0x40) |= (uint64_t)1 << (param_1 & 0x3f);
    *(uint64_t *)(*(long *)(param_4 + 0x30) + param_1 * 8) = param_2;
}

/* FUN_00083fb8 @ 0x83fb8   (est. cL4_nop_handler)
 * Ghidra: void FUN_00083fb8(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00083fb8(void)
{
    return;
}

/* FUN_00083fcc @ 0x83fcc   (est. cL4_cap_bitmap_setbit)
 * Ghidra: void FUN_00083fcc(ulong param_1)
 * Sets bit param_1 in the bitmap at in_x4+0x40.
 * Confidence: medium
 * Notes: base pointer in x4 (register-arg). */
void FUN_00083fcc(uint64_t param_1)
{
    long base = cL4_reg_x4();                     /* in_x4 */
    long w = base + (param_1 >> 6) * 8;
    *(uint64_t *)(w + 0x40) |= (uint64_t)1 << (param_1 & 0x3f);
}

/* FUN_00083ff0 @ 0x83ff0   (est. cL4_ptr_plus_20)
 * Ghidra: long FUN_00083ff0(void)
 * Returns x21 + 0x20.
 * Confidence: low
 * Notes: register-arg x21. */
long FUN_00083ff0(void)
{
    return cL4_reg_x21() + 0x20;
}

/* FUN_00084000 @ 0x84000   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084000(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084000(void)
{
    return;
}

/* FUN_00084010 @ 0x84010   (est. cL4_slot_store_10)
 * Ghidra: void FUN_00084010(undefined8 param_1)
 * Stores param_1 at in_x4+0x10.
 * Confidence: medium */
void FUN_00084010(uint64_t param_1)
{
    *(uint64_t *)(cL4_reg_x4() + 0x10) = param_1;
}

/* FUN_00084018 @ 0x84018   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084018(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084018(void)
{
    return;
}

/* FUN_00084024 @ 0x84024   (est. cL4_cap_bitmap_setbit)
 * Ghidra: void FUN_00084024(long param_1, ulong param_2)
 * Sets bit param_2 in the bitmap at param_1+0x40.
 * Confidence: medium */
void FUN_00084024(long param_1, uint64_t param_2)
{
    *(uint64_t *)(param_1 + 0x40) |= (uint64_t)1 << (param_2 & 0x3f);
}

/* FUN_0008403c @ 0x8403c   (est. cL4_nop_handler)
 * Ghidra: void FUN_0008403c(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_0008403c(void)
{
    return;
}

/* FUN_00084064 @ 0x84064   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084064(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084064(void)
{
    return;
}

/* FUN_00084074 @ 0x84074   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084074(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084074(void)
{
    return;
}

/* FUN_00084084 @ 0x84084   (est. cL4_fatal_default)
 * Ghidra: void FUN_00084084(void)
 * Invokes the noreturn fatal reporter with no arguments.
 * Confidence: medium */
void FUN_00084084(void)
{
    cL4_fatal_1afa84(0, 0, 0);
}

/* FUN_00084094 @ 0x84094   (est. cL4_slot_store_10)
 * Ghidra: void FUN_00084094(undefined8 param_1)
 * Stores param_1 at in_x3+0x10.
 * Confidence: medium */
void FUN_00084094(uint64_t param_1)
{
    *(uint64_t *)(cL4_reg_x3() + 0x10) = param_1;
}

/* FUN_0008409c @ 0x8409c   (est. cL4_nop_handler)
 * Ghidra: void FUN_0008409c(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_0008409c(void)
{
    return;
}

/* FUN_000840a8 @ 0x840a8   (est. cL4_helper_117cc4)
 * Ghidra: void FUN_000840a8(undefined8 param_1, ..., undefined8 param_4)
 * Forwards (param_4, param_1) to cL4_help_117cc4.
 * Confidence: low */
void FUN_000840a8(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
{
    cL4_help_117cc4(param_4, param_1);
}

/* FUN_000840b8 @ 0x840b8   (est. cL4_const_0)
 * Ghidra: undefined8 FUN_000840b8(void)
 * Returns 0.
 * Confidence: high */
uint64_t FUN_000840b8(void)
{
    return 0;
}

/* FUN_000840c8 @ 0x840c8   (est. cL4_nop_handler)
 * Ghidra: void FUN_000840c8(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_000840c8(void)
{
    return;
}

/* FUN_000840d8 @ 0x840d8   (est. cL4_nop_handler)
 * Ghidra: void FUN_000840d8(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_000840d8(void)
{
    return;
}

/* FUN_000840e8 @ 0x840e8   (est. cL4_nop_handler)
 * Ghidra: void FUN_000840e8(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_000840e8(void)
{
    return;
}

/* FUN_000840f4 @ 0x840f4   (est. cL4_nop_handler)
 * Ghidra: void FUN_000840f4(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_000840f4(void)
{
    return;
}

/* FUN_00084100 @ 0x84100   (est. cL4_dispatch_async)
 * Ghidra: void FUN_00084100(undefined8 param_1)
 * Dispatches param_1 through cL4_dispatch_3a1a0 with a stack buffer,
 * flags 0 and PC 0.
 * Confidence: low */
void FUN_00084100(uint64_t param_1)
{
    uint64_t stackbuf;
    cL4_dispatch_3a1a0((void *)param_1, &stackbuf, 0, 0);
}

/* FUN_00084110 @ 0x84110   (est. cL4_const_8)
 * Ghidra: undefined8 FUN_00084110(void)
 * Returns 8.
 * Confidence: high */
uint64_t FUN_00084110(void)
{
    return 8;
}

/* FUN_00084118 @ 0x84118   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084118(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084118(void)
{
    return;
}

/* FUN_0008412c @ 0x8412c   (est. cL4_nop_handler)
 * Ghidra: void FUN_0008412c(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_0008412c(void)
{
    return;
}

/* FUN_00084140 @ 0x84140   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084140(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084140(void)
{
    return;
}

/* FUN_00084154 @ 0x84154   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084154(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084154(void)
{
    return;
}

/* FUN_00084168 @ 0x84168   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084168(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084168(void)
{
    return;
}

/* FUN_00084174 @ 0x84174   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084174(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084174(void)
{
    return;
}

/* FUN_00084180 @ 0x84180   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084180(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084180(void)
{
    return;
}

/* FUN_0008418c @ 0x8418c   (est. cL4_nop_handler)
 * Ghidra: void FUN_0008418c(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_0008418c(void)
{
    return;
}

/* FUN_000841a0 @ 0x841a0   (est. cL4_nop_handler)
 * Ghidra: void FUN_000841a0(void)
 * Empty (no-op) handler slot (called by vas obj init).
 * Confidence: high */
void FUN_000841a0(void)
{
    return;
}

/* FUN_000841b4 @ 0x841b4   (est. cL4_cap_table_write)
 * Ghidra: void FUN_000841b4(long param_1, long param_2, ..., long param_6)
 * Writes {param_3, param_4} as a 16-byte entry at param_1 + param_2*0x10 and
 * param_5 into the auxiliary array at *(param_6+0x38) + param_2*8.
 * Confidence: medium */
void FUN_000841b4(long param_1, long param_2, uint64_t param_3, uint64_t param_4,
                  uint64_t param_5, long param_6)
{
    uint64_t *e = (uint64_t *)(param_1 + param_2 * 0x10);
    e[0] = param_3;
    e[1] = param_4;
    *(uint64_t *)(*(long *)(param_6 + 0x38) + param_2 * 8) = param_5;
}

/* FUN_000841d0 @ 0x841d0   (est. cL4_cap_table_write2)
 * Ghidra: void FUN_000841d0(long param_1, long param_2, ..., long param_6)
 * Writes param_3 at param_1 + param_2*8 and {param_4, param_5} as a 16-byte
 * entry at *(param_6+0x38) + param_2*0x10.
 * Confidence: medium */
void FUN_000841d0(long param_1, long param_2, uint64_t param_3, uint64_t param_4,
                  uint64_t param_5, long param_6)
{
    *(uint64_t *)(param_1 + param_2 * 8) = param_3;
    uint64_t *e = (uint64_t *)(*(long *)(param_6 + 0x38) + param_2 * 0x10);
    e[0] = param_4;
    e[1] = param_5;
}

/* FUN_000841ec @ 0x841ec   (est. cL4_fatal_msg)
 * Ghidra: void FUN_000841ec(undefined8 param_1)
 * Reports a fatal error (kind 0xb, flags 2) for param_1; does not return.
 * Confidence: medium */
void FUN_000841ec(uint64_t param_1)
{
    cL4_fatal_1afa84((void *)param_1, 0xb, 2);
}

/* FUN_00084200 @ 0x84200   (est. cL4_type_init)
 * Ghidra: void FUN_00084200(void)
 * Allocates/initializes the global object described by
 * cL4_type_alloc_2534(&DAT_0064e8a0, &DAT_004c08c0).
 * Confidence: low
 * Notes: result discarded. */
void FUN_00084200(void)
{
    cL4_type_alloc_2534((void *)0x64e8a0, (void *)0x4c08c0);
}

/* FUN_00084214 @ 0x84214   (est. cL4_helper_83a78)
 * Ghidra: void FUN_00084214(void)
 * Forwards two stack buffers to cL4_help_83a78 (out of slice).
 * Confidence: low */
void FUN_00084214(void)
{
    uint64_t a[25];
    uint64_t b[16];
    cL4_help_83a78(a, b);
}

/* FUN_00084220 @ 0x84220   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084220(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084220(void)
{
    return;
}

/* FUN_00084234 @ 0x84234   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084234(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084234(void)
{
    return;
}

/* FUN_00084248 @ 0x84248   (est. cL4_cap_pair_write)
 * Ghidra: void FUN_00084248(long param_1, ..., long param_6)
 * Writes two 16-byte pairs indexed by param_1: {param_2,param_3} into the
 * array at *(param_6+0x30)+param_1*0x10 and {param_4,param_5} into the array
 * at *(param_6+0x38)+param_1*0x10.
 * Confidence: medium */
void FUN_00084248(long param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4,
                  uint64_t param_5, long param_6)
{
    uint64_t *a = (uint64_t *)(*(long *)(param_6 + 0x30) + param_1 * 0x10);
    a[0] = param_2;
    a[1] = param_3;
    uint64_t *b = (uint64_t *)(*(long *)(param_6 + 0x38) + param_1 * 0x10);
    b[0] = param_4;
    b[1] = param_5;
}

/* thunk_FUN_0006649c @ 0x8426c   (est. cL4_cap_destroy)
 * Ghidra: undefined8 thunk_FUN_0006649c(void)
 * Queries a {ptr,size} pair (FUN_0006b2ec), performs an operation
 * (FUN_00066254) that may return a status in low bit, conditionally clears
 * the results, then releases via FUN_0006b360. If the status was nonzero,
 * triggers the canary-check panic (FUN_0011d7e8).
 * Confidence: low */
uint64_t FUN_0008426c(void)
{
    uint64_t pair0, pair1;
    uint64_t s1, s2;
    uint64_t op;
    bool ok;
    extern uint64_t cL4_pair_b2ec2(void);       /* second word of pair */
    pair0 = cL4_pair_b2ec();
    pair1 = cL4_pair_b2ec2();
    s1 = 0;
    s2 = 0;
    op = cL4_op_66254(pair0, pair1, &s1);
    ok = (op & 1) == 0;
    if (ok) {
        s1 = 0;
        s2 = 0;
    }
    cL4_release_b360(s1, op, s2);
    if (!ok)
        cL4_canary_panic_11d7e8();
    return 0;
}

/* FUN_00084270 @ 0x84270   (est. cL4_cap_destroy_ctx)
 * Ghidra: void FUN_00084270(undefined1(*)[16] param_1, ..., undefined1 param_4)
 * Invokes thunk_FUN_0006649c with the 2-word context at x20, stores the
 * resulting 16-byte pair into param_1 and param_1[1][0] = param_4.
 * Confidence: low */
void FUN_00084270(uint64_t *param_1, uint64_t param_2, uint64_t param_3, uint8_t param_4)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t pair[2];
    cL4_cap_destroy_ctx_pair(g_ctx[0], g_ctx[1], pair);
    param_1[0] = pair[0];
    param_1[1] = pair[1];
    ((uint8_t *)param_1)[16] = param_4;
}

/* FUN_000842b8 @ 0x842b8   (est. cL4_cap_test)
 * Ghidra: uint FUN_000842b8(undefined8 param_1, undefined8 param_2)
 * Runs cL4_op_66558(FUN_00084948, stack, *x20, x20[1]) and returns the low
 * bit of its status.
 * Confidence: low */
uint32_t FUN_000842b8(uint64_t param_1, uint64_t param_2)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t stack[2];
    stack[0] = param_1;
    stack[1] = param_2;
    return cL4_op_66558((uint64_t)FUN_00084948, stack, g_ctx[0], g_ctx[1]) & 1;
}

/* FUN_000842fc @ 0x842fc   (est. cL4_call_fn)
 * Ghidra: void FUN_000842fc(undefined1(*)[16] param_1, ..., code *param_4)
 * Calls the code pointer param_4 with (*x20, x20[1]) and stores the resulting
 * 16-byte pair into param_1.
 * Confidence: low */
void FUN_000842fc(uint64_t *param_1, uint64_t param_2, uint64_t param_3, void *param_4)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t pair[2];
    ((uint64_t (*)(uint64_t, uint64_t, uint64_t *))(param_4))(g_ctx[0], g_ctx[1], pair);
    param_1[0] = pair[0];
    param_1[1] = pair[1];
}

/* FUN_0008433c @ 0x8433c   (est. cL4_op_pair)
 * Ghidra: void FUN_0008433c(undefined1(*)[16] param_1, undefined8 param_2)
 * Runs cL4_op_67704(param_2, *x20) and stores the resulting 16-byte pair into
 * param_1.
 * Confidence: low */
void FUN_0008433c(uint64_t *param_1, uint64_t param_2)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t pair[2];
    pair[0] = cL4_op_67704(param_2, g_ctx[0]);
    pair[1] = cL4_op_67704_pair();
    param_1[0] = pair[0];
    param_1[1] = pair[1];
}

/* FUN_00084368 @ 0x84368   (est. cL4_exclave_launch_map)
 * Ghidra: long * FUN_00084368(void)
 * The InternalExclaveLauncher device-tree / VAS-extension path. Two branches:
 *  (1) When the owner query (FUN_0006d52c) is nonzero and the memory query
 *      (FUN_0006b79c) is zero: resolves a "DeviceTree" node, builds a VAS
 *      object, maps the device tree from the hypervisor (log
 *      "DEVICETREE FROM HYPERVISOR ON ADDRESSES 0x..."), and commits the
 *      resulting range.
 *  (2) Otherwise maps a DTBlob: walks the device tree, allocates vas slots
 *      (logging "VasSlotAlloc failed on ..." on failure), maps each 16 KiB
 *      page via FUN_00084824 / the object's map slot, logging
 *      "mapDeviceTree()" / "InternalExclaveLauncher/VASExtension.swift" on
 *      failure paths. Fatal errors report through FUN_001afa84 with
 *      "InternalExclaveLauncher/DTBlob.swift" / "VASExtension.swift".
 * Returns the mapped object pointer (0 on early exit).
 * Confidence: medium
 * Notes: large function; heavy out-of-slice dependency. Stack canary
 *   checked via FUN_0011d7e8 at exit. */
void *FUN_00084368(void)
{
    long owner;
    long v;
    long slot;
    uint64_t base, size, mapped;
    uint64_t tmp;

    owner = cL4_query_d52c();
    if (owner == 0 || (v = cL4_query_b79c(), v != 0)) {
        /* ---- DTBlob path ---- */
        base = cL4_query_b79c();
        mapped = cL4_query_b7ac();
        if ((long)mapped < 0)
            cL4_breakpoint(0x846c4);
        if (owner == 0) {
            size = cL4_query_d024(base);
            if (base != size) {
                cL4_fatal_1afa84((void *)s_Fatal_error, 0xb, 2, (uint64_t)-0x2fffffffffffffd1,
                                 0x80000000005c03d0,
                                 "InternalExclaveLauncher/DTBlob.swift", 0x24, 2, 0x55, 0);
            }
            mapped = cL4_query_d150(base);
            if ((long)mapped < 0)
                cL4_breakpoint(0x846cc);
            cL4_mem_release_b78c(0);
        }
        if (mapped != 0) {
            uint64_t sz = cL4_query_cf50(base);
            uint64_t lim = cL4_query_d024(base);
            uint64_t off = 0;
            void *vas;
            void *obj;
            if (base < lim)
                cL4_breakpoint(0x846c8);
            vas = cL4_alloc_3a940(0, 0x50, 7);
            obj = (void *)cL4_alloc_3a9d4((uint64_t)vas, 0x64e1c0);
            obj = cL4_vas_map_85a54(obj, mapped, 0x11, 0x1800, 0);
            {
                long n = (mapped >> 0xe) + 1;
                while (n = n - 1, n != 0) {
                    slot = cL4_vas_slot_alloc_34f70();
                    if (slot == 0) {
                        cL4_log_kind_2a4ab4(0x1e);
                        cL4_log_val_3a25d4(0xe000000000000000);
                        cL4_log_86840("VasSlotAlloc failed on ");
                        cL4_log_msg_294bdc("mapDeviceTree()", 0xf, 2);
                        cL4_log_pair_2acbb8(0, 0);
                        cL4_log_val_3a25d4(cL4_reg_x1());
                        cL4_log_pair_2acbb8(0x203a20, 0xe300000000000000);
                        cL4_log_msg_294bdc("mapDeviceTree()", 0xf, 2);
                        cL4_log_pair_2acbb8(0, 0);
                        cL4_log_val_3a25d4(cL4_reg_x1());
                        cL4_fatal_1afa84((void *)s_Fatal_error, 0xb, 2, (uint64_t)-0x2fffffffffffffd1,
                                         0x80000000005c03d0,
                                         "InternalExclaveLauncher/VASExtension.swift", 0x2a, 2, 0x6f, 0);
                    }
                    if ((base - lim) + off > base - lim)
                        cL4_breakpoint(0x846c0);
                    FUN_00084824(0, (base - lim) + off, slot);
                    {
                        uint64_t ts[2];
                        ts[0] = cL4_ts_151974();
                        ts[1] = cL4_ts_151974_pair();
                        cL4_log_151a6c((const void *)0xf61ac, 0, "__AppleInternal_Library_BuildRoot_...", 0xf0, 2, 0x65,
                                       ts[0], ts[1]);
                    }
                    cL4_vas_map_slot(obj, off, slot);   /* [*obj+0x90](off, slot) */
                    off += 0x4000;
                }
            }
            return obj;
        }
        return 0;
    }

    /* ---- DeviceTree-from-hypervisor path ---- */
    {
        uint64_t node = 0;
        uint64_t phys = 0;
        uint64_t ret = FUN_00084848(owner, &phys, &node);
        long vas = (long)cL4_type_alloc_2534((void *)0x64c040, (void *)0x4bbf40);
        long *desc = cL4_obj_init_3a9a0(vas, (long *)&tmp);
        desc[0x10 / 8] = _DAT_004baeb0;      /* from _DAT_004baeb0 */
        desc[0x18 / 8] = uRam_004baeb8;
        cL4_log_kind_2a4ab4(0x31);
        cL4_log_val_3a25d4(0xe000000000000000);
        cL4_log_86840("DEVICETREE FROM HYPERVISOR ON ADDRESSES 0x");
        {
            long v2 = phys;
            cL4_log_1e790();
            FUN_0008499c();
            cL4_log_pair_2acbb8(0, 0);
            cL4_log_val_3a25d4(cL4_reg_x1());
            cL4_log_pair_2acbb8(0x783020, 0xe300000000000000);
        }
        size = node;
        FUN_0008499c();
        cL4_log_pair_2acbb8(0, 0);
        cL4_log_val_3a25d4(cL4_reg_x1());
        desc[0x38 / 8] = 0x6753a0;
        desc[0x20 / 8] = phys + 0x13;
        desc[0x28 / 8] = 0xe000000000000000;
        cL4_map_26b434((long)desc, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        cL4_release_3a588((long)desc);
        cL4_help_2688();
        cL4_destroy_3a6ac(0x20, 7, 0, 0);
        if (ret != 0)
            cL4_breakpoint(0x846d0);
        if ((phys != 0) && (size != 0)) {
            if (0xffffffffffffc000 < size)
                cL4_breakpoint(0x846d4);
            cL4_mem_release_b77c(phys);
            if ((long)(size + 0x3fff) < 0)
                cL4_breakpoint(0x846d8);
            cL4_mem_release_b78c((size + 0x3fff) & 0x7fffffffffffc000);
            /* fall into the DTBlob path above */
            base = cL4_query_b79c();
            mapped = cL4_query_b7ac();
            if ((long)mapped < 0)
                cL4_breakpoint(0x846c4);
            if (owner == 0) {
                size = cL4_query_d024(base);
                if (base != size)
                    cL4_fatal_1afa84((void *)s_Fatal_error, 0xb, 2, (uint64_t)-0x2fffffffffffffd1,
                                     0x80000000005c03d0,
                                     "InternalExclaveLauncher/DTBlob.swift", 0x24, 2, 0x55, 0);
                mapped = cL4_query_d150(base);
                if ((long)mapped < 0)
                    cL4_breakpoint(0x846cc);
                cL4_mem_release_b78c(0);
            }
            if (mapped != 0) {
                uint64_t sz = cL4_query_cf50(base);
                uint64_t lim = cL4_query_d024(base);
                uint64_t off = 0;
                void *obj;
                if (base < lim)
                    cL4_breakpoint(0x846c8);
                obj = (void *)cL4_vas_map_85a54(0, mapped, 0x11, 0x1800, 0);
                {
                    long n = (mapped >> 0xe) + 1;
                    while (n = n - 1, n != 0) {
                        slot = cL4_vas_slot_alloc_34f70();
                        if (slot == 0) {
                            cL4_log_kind_2a4ab4(0x1e);
                            cL4_log_val_3a25d4(0xe000000000000000);
                            cL4_log_86840("VasSlotAlloc failed on ");
                            cL4_log_msg_294bdc("mapDeviceTree()", 0xf, 2);
                            cL4_log_pair_2acbb8(0, 0);
                            cL4_log_val_3a25d4(cL4_reg_x1());
                            cL4_log_pair_2acbb8(0x203a20, 0xe300000000000000);
                            cL4_fatal_1afa84((void *)s_Fatal_error, 0xb, 2, (uint64_t)-0x2fffffffffffffd1,
                                             0x80000000005c03d0,
                                             "InternalExclaveLauncher/VASExtension.swift", 0x2a, 2, 0x6f, 0);
                        }
                        if ((base - lim) + off > base - lim)
                            cL4_breakpoint(0x846c0);
                        FUN_00084824(0, (base - lim) + off, slot);
                        cL4_vas_map_slot(obj, off, slot);
                        off += 0x4000;
                    }
                }
                return obj;
            }
        }
    }
    return 0;
}

/* FUN_00084824 @ 0x84824   (est. cL4_supervisor_call)
 * Ghidra: void FUN_00084824(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Issues a supervisor call (CallSupervisor(0)) with a 3-word message block
 * rooted at tpidrro_el0: {0x11, param_2, param_3}; then restores the message
 * kind word to 0x11.
 * Confidence: medium
 * Notes: CallSupervisor(0) = svc #0 syscall; message block at tpidrro_el0
 *   (per-CPU register). */
void FUN_00084824(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    uint64_t *msg = (uint64_t *)cL4_tpidrro_el0();
    msg[0] = 0x11;
    msg[1] = param_2;
    msg[2] = param_3;
    __asm__ __volatile__("svc #0");       /* CallSupervisor(0) */
    msg[0] = 0x11;
}

/* FUN_00084848 @ 0x84848   (est. cL4_dt_resolve)
 * Ghidra: void FUN_00084848(undefined8 param_1, undefined8 *param_2, undefined8 *param_3)
 * Resolves the "DeviceTree" property of node param_1 (via cL4_dt_prop_552c0,
 * kind 4). On success stores the address into *param_2 and the value from
 * globals _DAT_004bbff0/8 into *param_3.
 * Confidence: medium
 * Notes: s_DeviceTree_005c044b = "DeviceTree". */
uint64_t FUN_00084848(uint64_t param_1, uint64_t *param_2, uint64_t *param_3)
{
    const char *name = "DeviceTree";
    uint64_t v0 = 0, v1 = 0;
    if (cL4_dt_prop_552c0(param_1, 4, &name) == 0) {
        *param_2 = v1;
        v1 = _DAT_004bbff8;
        v0 = _DAT_004bbff0;
        if (cL4_dt_prop_552c0(param_1, 4, &name) == 0)
            *param_3 = v1;
    }
    return 0;
}

/* FUN_00084948 @ 0x84948   (est. cL4_vtable_call)
 * Ghidra: uint FUN_00084948(undefined8 param_1)
 * Calls the vtable slot at (x20+0x10) with &param_1 and returns its low bit.
 * Confidence: low */
uint32_t FUN_00084948(uint64_t param_1)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t arg = param_1;
    return ((uint32_t (*)(uint64_t *))(g_ctx[2]))(&arg) & 1;
}

/* FUN_00084984 @ 0x84984   (est. cL4_nop_handler)
 * Ghidra: void FUN_00084984(void)
 * Empty (no-op) handler slot.
 * Confidence: high */
void FUN_00084984(void)
{
    return;
}

/* FUN_0008499c @ 0x8499c   (est. cL4_log_hex)
 * Ghidra: void FUN_0008499c(void)
 * Logs a 16-byte hex value (FUN_001ebfb0 with length 0x10).
 * Confidence: low */
void FUN_0008499c(void)
{
    uint64_t buf[2];
    cL4_log_hex_1ebfb0(buf, 0x10, 0);
}

/* FUN_000849b4 @ 0x849b4   (est. cL4_log_vas_fail)
 * Ghidra: void FUN_000849b4(void)
 * Empty (no-op) handler slot; called with the "VasSlotAlloc failed on "
 * message in the launcher path.
 * Confidence: high
 * Notes: body is a bare return. */
void FUN_000849b4(void)
{
    return;
}

/* FUN_000849c8 @ 0x849c8   (est. cL4_pair_read)
 * Ghidra: void FUN_000849c8(undefined8 *param_1)
 * Reads the 16-byte pair from *(x20+0x10) + 0x10 and +0x18 into param_1.
 * Confidence: low */
void FUN_000849c8(uint64_t *param_1)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t *obj = *(uint64_t **)(g_ctx[2]);
    param_1[0] = *(obj + 2);
    param_1[1] = *(obj + 3);
}

/* FUN_000849d8 @ 0x849d8   (est. cL4_release_pair)
 * Ghidra: void FUN_000849d8(void)
 * Releases the object at *(x20+0x10) and runs cL4_destroy_3a6ac().
 * Confidence: low */
void FUN_000849d8(void)
{
    extern long *g_ctx;   /* unaff_x20 */
    cL4_release_3a118(*(g_ctx + 2));
    cL4_destroy_3a6ac(0, 0, 0, 0);
}

/* FUN_000849dc @ 0x849dc   (est. cL4_release_pair)
 * Ghidra: void FUN_000849dc(void)
 * Same as FUN_000849d8.
 * Confidence: low */
void FUN_000849dc(void)
{
    extern long *g_ctx;   /* unaff_x20 */
    cL4_release_3a118(*(g_ctx + 2));
    cL4_destroy_3a6ac(0, 0, 0, 0);
}

/* FUN_00084a04 @ 0x84a04   (est. cL4_pair_read_wrap)
 * Ghidra: void FUN_00084a04(void)
 * Wraps FUN_000849c8.
 * Confidence: low */
void FUN_00084a04(void)
{
    uint64_t pair[2];
    FUN_000849c8(pair);
}

/* FUN_00084a28 @ 0x84a28   (est. cL4_obj_pair_store)
 * Ghidra: void FUN_00084a28(undefined8 param_1, undefined8 param_2)
 * Allocates an object, stores param_1 at +0x10 and param_2 at +0x18.
 * Confidence: low */
void FUN_00084a28(uint64_t param_1, uint64_t param_2)
{
    long obj = (long)cL4_alloc_3a940(0, 0, 0);
    *(uint64_t *)(obj + 0x10) = param_1;
    *(uint64_t *)(obj + 0x18) = param_2;
}

/* FUN_00084a74 @ 0x84a74   (est. cL4_vas_obj_alloc)
 * Ghidra: void FUN_00084a74(long *param_1)
 * Allocates a VAS object (tag 0x64f178, size 0x18, flags 7) into param_1[0]
 * and initializes param_1[3]=0x64f178, param_1[4]=0x65f940.
 * Confidence: medium */
void FUN_00084a74(long *param_1)
{
    long obj = (long)cL4_alloc_3a940(0x64f178, 0x18, 7);
    *(uint64_t *)(obj + 0x10) = cL4_reg_x20();
    param_1[3] = 0x64f178;
    param_1[4] = 0x65f940;
    param_1[0] = obj;
    cL4_retain_3a270(0);
}

/* FUN_00084af0 @ 0x84af0   (est. cL4_vas_error)
 * Ghidra: undefined1[16] FUN_00084af0(void)
 * Logs a VAS error (kind 0x38) with hex addresses and the string
 * "Key i:clc avl" (0x76616c637865202c / 0xee00203a74694b65), then returns the
 * error pair {0xe000000000000000, 0}.
 * Confidence: low
 * Notes: two 8-byte ASCII words decoded inline. */
void *FUN_00084af0(uint64_t *out_pair)
{
    cL4_log_kind_2a4ab4(0x38);
    cL4_log_pair_2acbb8(0xd000000000000025, 0x80000000005c0440);
    cL4_log_pair_2acbb8(0, 0);
    cL4_log_val_3a25d4(cL4_reg_x1());
    cL4_log_pair_2acbb8(0x76616c637865202c, 0xee00203a74694b65);  /* "Key i:clc avl" */
    cL4_log_pair_2acbb8(0, 0);
    cL4_log_val_3a25d4(cL4_reg_x1());
    cL4_log_pair_2acbb8(0x29, 0xe100000000000000);
    out_pair[0] = 0xe000000000000000;
    out_pair[1] = 0;
    return out_pair;
}

/* FUN_00084c28 @ 0x84c28   (est. cL4_vas_alloc_wrap)
 * Ghidra: void FUN_00084c28(void)
 * Wraps FUN_00084a74.
 * Confidence: low */
void FUN_00084c28(void)
{
    long out[5];
    FUN_00084a74(out);
}

/* FUN_00084c2c @ 0x84c2c   (est. cL4_vas_alloc_wrap)
 * Ghidra: void FUN_00084c2c(void)
 * Wraps FUN_00084a74.
 * Confidence: low */
void FUN_00084c2c(void)
{
    long out[5];
    FUN_00084a74(out);
}

/* FUN_00084c40 @ 0x84c40   (est. cL4_vas_error_wrap)
 * Ghidra: void FUN_00084c40(void)
 * Wraps FUN_00084af0.
 * Confidence: low */
void FUN_00084c40(void)
{
    uint64_t pair[2];
    FUN_00084af0(pair);
}

/* FUN_00084c9c @ 0x84c9c   (est. cL4_const_pair)
 * Ghidra: undefined1[16] FUN_00084c9c(void)
 * Returns the 16-byte pair {0x64f110, 0}.
 * Confidence: medium */
void *FUN_00084c9c(uint64_t *out_pair)
{
    out_pair[0] = 0x64f110;
    out_pair[1] = 0;
    return out_pair;
}

/* FUN_00084cc4 @ 0x84cc4   (est. cL4_vas_op_combine)
 * Ghidra: uint FUN_00084cc4(uint param_1, uint param_2)
 * Returns param_2 | param_1 (combines two VAS op flags/status words).
 * Confidence: medium */
uint32_t FUN_00084cc4(uint32_t param_1, uint32_t param_2)
{
    return param_2 | param_1;
}

/* FUN_00084cd8 @ 0x84cd8   (est. cL4_vas_op_dispatch)
 * Ghidra: undefined8 FUN_00084cd8(undefined8 param_1, ..., undefined8 param_5)
 * Runs a VAS map operation (FUN_00085a54) after setup (FUN_000867b4,
 * FUN_0036a940); returns the allocated object.
 * Confidence: low */
uint64_t FUN_00084cd8(uint64_t param_1, uint64_t param_2, uint64_t param_3,
                      uint64_t param_4, uint64_t param_5)
{
    uint64_t obj;
    cL4_nop_867b4();
    obj = (uint64_t)cL4_alloc_3a940(0, 0, 0);
    cL4_vas_map_85a54((void *)param_1, param_2, param_3, param_4, param_5);
    return obj;
}

/* FUN_00084d50 @ 0x84d50   (est. cL4_vas_slot_try)
 * Ghidra: long FUN_00084d50(code *param_1, ..., undefined8 param_6)
 * Attempts to allocate a VAS slot (cL4_vas_slot_alloc_34f70); if allocation
 * succeeds (returns 0, i.e. success/failure inverted here), calls
 * (*param_1)(param_3, param_4, param_5, param_6). Returns the slot result.
 * Confidence: low
 * Notes: FUN_00034f70 returns 0 on allocation failure; the callback runs on
 *   the failure path. */
long FUN_00084d50(void *param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4,
                  uint64_t param_5, uint64_t param_6)
{
    long r = cL4_vas_slot_alloc_34f70();
    if (r == 0)
        ((void (*)(uint64_t, uint64_t, uint64_t, uint64_t))(param_1))(
            param_3, param_4, param_5, param_6);
    return r;
}

/* FUN_00084dc8 @ 0x84dc8   (est. cL4_vas_call_wrap)
 * Ghidra: undefined1 FUN_00084dc8(void)
 * Wraps FUN_00084de4.
 * Confidence: low */
uint8_t FUN_00084dc8(void)
{
    return FUN_00084de4(0, 0, 0, 0);
}

/* FUN_00084de4 @ 0x84de4   (est. cL4_vas_obj_call)
 * Ghidra: undefined1 FUN_00084de4(undefined8 param_1, code *param_2, ...)
 * Builds a call context (FUN_00365b6c) and invokes the object's method
 * param_2 with (param_3, param_4); returns the one-byte status result.
 * Confidence: low
 * Notes: heavy object dispatch machinery. */
uint8_t FUN_00084de4(uint64_t param_1, void *param_2, uint64_t param_3, uint64_t param_4)
{
    uint8_t status;
    uint64_t ctx0 = param_1;
    uint64_t args[2];
    void *meth;
    void *obj;
    uint64_t r;
    cL4_retain_3a270(0);
    obj = cL4_type_alloc_2534((void *)0x64f1c0, (void *)0x4c0db8);
    r = cL4_call_365b6c(&meth, &ctx0, 0x67b200, (long)obj, 7);
    meth = (void *)meth;
    args[0] = param_3;
    args[1] = param_4;
    ((void (*)(uint8_t *, uint64_t *, uint64_t *, uint64_t *))(meth))(
        &status, args, &ctx0, &ctx0);
    cL4_release_3a118((long)obj);
    return status;
}

/* FUN_00084e8c @ 0x84e8c   (est. cL4_vas_result_pack)
 * Ghidra: ulong FUN_00084e8c(undefined8 param_1, undefined8 param_2)
 * Packs (cL4_status_6e6dc() & 0xffffffff) | (cL4_hi16_85b68(param_1,param_2) << 0x20).
 * Confidence: low */
uint64_t FUN_00084e8c(uint64_t param_1, uint64_t param_2)
{
    uint64_t lo = cL4_status_6e6dc(0);
    uint64_t hi = cL4_hi16_85b68(param_1);
    return (lo & 0xffffffff) | (hi << 0x20);
}

/* FUN_00084ee0 @ 0x84ee0   (est. cL4_vas_error_code)
 * Ghidra: undefined1[16] FUN_00084ee0(ulong param_1)
 * Produces a VAS return code + message pair for an operation index param_1.
 * For indices < 8 the message is a fixed tag/error word; otherwise it logs a
 * hex index and returns the pair {0x80000000005c0470, 0xd000000000000012}
 * ("esource(exclaveC..." string + code).
 * Confidence: medium
 * Notes: message words are inline ASCII; strings
 *   "vasOperationInvalid" (0x5c04d0) and "vasVirtualSpaceUnavailable"
 *   (0x5c04b0) are logged for cases 1 and 3. */
void *FUN_00084ee0(uint64_t param_1, uint64_t *out_pair)
{
    uint64_t tag, msg;
    uint64_t hi = param_1 >> 0x20;

    switch (param_1 & 0xffffffff) {
    default:
        msg = 0xe000000000000000;
        tag = 0x6563637553736176;   /* "vasSucce" */
        /* falls through to hex-log + final tag below */
        break;
    case 1:
        cL4_log_86840("vasOperationInvalid");
        tag = 0xd000000000000013;
        msg = cL4_reg_x8();
        break;
    case 2:
        tag = 0x664f74754f736176;   /* "vasOtuOf" -> "vasOutOfMem..." */
        msg = 0xee0079726f6d654d;   /* "Memory.." */
        break;
    case 3:
        cL4_log_86840("vasVirtualSpaceUnavailable");
        tag = 0xd00000000000001a;
        msg = cL4_reg_x8();
        break;
    case 4:
        tag = 0x6f46746f4e736176;   /* "vasNtoFo" -> "vasNotFound" */
        msg = 0xeb00000000646e75;   /* "und.." */
        break;
    case 5:
    case 6:
        tag = 0xd000000000000012;
        msg = 0x80000000005c0470;   /* "esource(exclaveC..." */
        break;
    case 7:
        tag = 0x61766e6945736176;   /* "vasEinva" */
        msg = 0xe90000000000006c;
        break;
    }
    out_pair[0] = tag;
    out_pair[1] = msg;
    return out_pair;
}

/* FUN_00085140 @ 0x85140   (est. cL4_vas_global_init)
 * Ghidra: void FUN_00085140(void)
 * Initializes the global VAS object _DAT_006ad998 via cL4_alloc_3a9d4.
 * Confidence: low */
void FUN_00085140(void)
{
    _DAT_006ad998 = cL4_alloc_3a9d4(0x64f1f8, 0x64e1c0);
}

/* FUN_00085144 @ 0x85144   (est. cL4_vas_global_init)
 * Ghidra: void FUN_00085144(void)
 * Identical to FUN_00085140.
 * Confidence: low */
void FUN_00085144(void)
{
    _DAT_006ad998 = cL4_alloc_3a9d4(0x64f1f8, 0x64e1c0);
}

/* FUN_00085184 @ 0x85184   (est. cL4_vas_global_get)
 * Ghidra: undefined1 * FUN_00085184(void)
 * Registers FUN_00085140 as a constructor for type 0x64f1d8 and returns a
 * pointer to the global _DAT_006ad998.
 * Confidence: low */
void *FUN_00085184(void)
{
    cL4_ctor_3a128(0x64f1d8, (void *)FUN_00085140);
    return &_DAT_006ad998;
}

/* thunk_FUN_00034a2c @ 0x851d0   (est. cL4_vas_global_pair)
 * Ghidra: undefined1[16] thunk_FUN_00034a2c(void)
 * Looks up the global at (cL4_global_5acac(0x6af188, 4, 8) + 0x10) and
 * returns the 16-byte value there.
 * Confidence: low */
void *FUN_000851d0(uint64_t *out_pair)
{
    long g = cL4_global_5acac(0x6af188, 4, 8);
    out_pair[0] = *(uint64_t *)(g + 0x10);
    out_pair[1] = *(uint64_t *)(g + 0x18);
    return out_pair;
}

/* FUN_000851d4 @ 0x851d4   (est. cL4_vas_global_wrap)
 * Ghidra: void FUN_000851d4(void)
 * Wraps thunk_FUN_00034a2c.
 * Confidence: low */
void FUN_000851d4(void)
{
    uint64_t pair[2];
    FUN_000851d0(pair);
}

/* FUN_000851d8 @ 0x851d8   (est. cL4_vas_global_wrap)
 * Ghidra: void FUN_000851d8(void)
 * Wraps thunk_FUN_00034a2c.
 * Confidence: low */
void FUN_000851d8(void)
{
    uint64_t pair[2];
    FUN_000851d0(pair);
}

/* FUN_000851f4 @ 0x851f4   (est. cL4_cap_copy_ctx)
 * Ghidra: void FUN_000851f4(undefined8 param_1)
 * Clones the object at x20+0x20 into param_1 (cL4_obj_copy_6e7c0).
 * Confidence: low */
void FUN_000851f4(uint64_t param_1)
{
    extern long *g_ctx;   /* unaff_x20 */
    cL4_obj_copy_6e7c0((long)g_ctx + 0x20, (long)param_1);
}

/* FUN_000851f8 @ 0x851f8   (est. cL4_cap_copy_ctx)
 * Ghidra: void FUN_000851f8(undefined8 param_1)
 * Same as FUN_000851f4.
 * Confidence: low */
void FUN_000851f8(uint64_t param_1)
{
    extern long *g_ctx;   /* unaff_x20 */
    cL4_obj_copy_6e7c0((long)g_ctx + 0x20, (long)param_1);
}

/* FUN_00085214 @ 0x85214   (est. cL4_vas_op_launch)
 * Ghidra: void FUN_00085214(void)
 * Drives a VAS launch: setup (FUN_000867ec), alloc (FUN_0036a940), helper
 * (FUN_00086860), then the VAS op FUN_00085258.
 * Confidence: low */
void FUN_00085214(void)
{
    cL4_nop_867ec();
    cL4_alloc_3a940(0, 0, 0);
    cL4_nop_86860();
    FUN_00085258(0, 0, 0);
}

/* FUN_00085258 @ 0x85258   (est. cL4_vas_op_exec)
 * Ghidra: void FUN_00085258(undefined8 param_1, long param_2, undefined8 param_3)
 * Executes a VAS operation: clones the object at x20+0x20 into param_2, reads
 * {obj+0x18, obj+0x20}, releases obj, fetches a method pointer for obj+0x20
 * and calls it. If the returned pair is nonzero, post-processes via
 * cL4_op_35944 and stores the pair into x20+0x10, then releases; otherwise
 * traps at 0x8530c.
 * Confidence: low */
void FUN_00085258(uint64_t param_1, long param_2, uint64_t param_3)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t v1, v2;
    uint64_t pair[2];
    void *meth;
    cL4_obj_copy_6e7c0(param_2, (long)g_ctx + 0x20);
    v1 = *(uint64_t *)(param_2 + 0x18);
    v2 = *(uint64_t *)(param_2 + 0x20);
    cL4_help_6a4c0(param_2, v1);
    meth = cL4_fn_77148(v2);
    pair[0] = ((uint64_t (*)(uint64_t, uint64_t))(meth))(v1, v2);
    pair[1] = ((uint64_t (*)(uint64_t, uint64_t))(meth))(v1, v2) /* 2nd word */;
    if (pair[1] != 0) {
        uint64_t r[2];
        r[0] = cL4_op_35944(param_1, pair[0], pair[1], param_3);
        r[1] = cL4_op_35944_pair();
        *(uint64_t *)((char *)g_ctx + 0x10) = r[0];
        cL4_release_26e8(param_2);
        return;
    }
    cL4_breakpoint(0x8530c);
}

/* FUN_0008530c @ 0x8530c   (est. cL4_vas_release_pair)
 * Ghidra: void FUN_0008530c(void)
 * Releases the {x20+0x10, x20+0x18} pair (cL4_release_359d4) and the object
 * at x20+0x20 (cL4_release_26e8).
 * Confidence: low */
void FUN_0008530c(void)
{
    extern long *g_ctx;   /* unaff_x20 */
    cL4_release_359d4(*(uint64_t *)((char *)g_ctx + 0x10),
                      *(uint64_t *)((char *)g_ctx + 0x18));
    cL4_release_26e8((uint64_t)g_ctx + 0x20);
}

/* FUN_00085310 @ 0x85310   (est. cL4_vas_release_pair)
 * Ghidra: void FUN_00085310(void)
 * Same as FUN_0008530c.
 * Confidence: low */
void FUN_00085310(void)
{
    extern long *g_ctx;   /* unaff_x20 */
    cL4_release_359d4(*(uint64_t *)((char *)g_ctx + 0x10),
                      *(uint64_t *)((char *)g_ctx + 0x18));
    cL4_release_26e8((uint64_t)g_ctx + 0x20);
}

/* FUN_00085334 @ 0x85334   (est. cL4_vas_release_destroy)
 * Ghidra: void FUN_00085334(void)
 * Like FUN_0008530c plus a final destroy (cL4_destroy_3a6ac).
 * Confidence: low */
void FUN_00085334(void)
{
    extern long *g_ctx;   /* unaff_x20 */
    cL4_release_359d4(*(uint64_t *)((char *)g_ctx + 0x10),
                      *(uint64_t *)((char *)g_ctx + 0x18));
    cL4_release_26e8((uint64_t)g_ctx + 0x20);
    cL4_destroy_3a6ac(0, 0, 0, 0);
}

/* FUN_00085338 @ 0x85338   (est. cL4_vas_release_destroy)
 * Ghidra: void FUN_00085338(void)
 * Same as FUN_00085334.
 * Confidence: low */
void FUN_00085338(void)
{
    extern long *g_ctx;   /* unaff_x20 */
    cL4_release_359d4(*(uint64_t *)((char *)g_ctx + 0x10),
                      *(uint64_t *)((char *)g_ctx + 0x18));
    cL4_release_26e8((uint64_t)g_ctx + 0x20);
    cL4_destroy_3a6ac(0, 0, 0, 0);
}

/* FUN_00085374 @ 0x85374   (est. cL4_vas_slot_fail_fatal)
 * Ghidra: void FUN_00085374(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Logs a fatal VAS-slot-allocation failure (kind 0x1e, "VasSlotAlloc failed
 * on " + message) then traps at 0x85470 (does not return).
 * Confidence: medium
 * Notes: log sequence matches the launcher failure path. */
void FUN_00085374(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    cL4_log_kind_2a4ab4(0x1e);
    cL4_log_val_3a25d4(0xe000000000000000);
    cL4_log_86840("VasSlotAlloc failed on ");
    cL4_log_msg_294bdc((const char *)param_1, param_2, param_3);
    cL4_log_pair_2acbb8(0, 0);
    cL4_log_val_3a25d4(cL4_reg_x1());
    cL4_log_pair_2acbb8(0x203a20, 0xe300000000000000);
    cL4_log_pair_2acbb8(0, 0);
    cL4_log_val_3a25d4(cL4_reg_x1());
    cL4_log_trap_867c4(0x6f);
    cL4_breakpoint(0x85470);
}

/* FUN_00085480 @ 0x85480   (est. cL4_vas_op_setup)
 * Ghidra: void FUN_00085480(void)
 * VAS op setup: nops, alloc, helper, then FUN_000854bc.
 * Confidence: low */
void FUN_00085480(void)
{
    cL4_nop_867ec();
    cL4_nop_867b4();
    cL4_alloc_3a940(0, 0, 0);
    cL4_nop_86860();
    FUN_000854bc();
}

/* FUN_000854bc @ 0x854bc   (est. cL4_vas_op_dispatch2)
 * Ghidra: void FUN_000854bc(void)
 * Dispatches a VAS operation: fetches a {ptr,size} pair (FUN_0006b2ec),
 * builds a supervisor message block {0x11, 0, ...}, runs the VAS op
 * (FUN_00086410), stores results into x20, runs FUN_00077070 and commits
 * (FUN_000651bc); canary-check panic on failure.
 * Confidence: low */
void FUN_000854bc(void)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t pair[2];
    uint8_t msg[8] = {0x11, 0, 0, 0, 0, 0, 0, 0};
    uint64_t v;
    cL4_nop_867ec();
    pair[0] = cL4_pair_b2ec();
    pair[1] = cL4_pair_b2ec2();
    cL4_vas_op_86410(pair[0], pair[1], (uint64_t *)msg);
    *(uint64_t *)((char *)g_ctx + 0x10) = cL4_reg_x22();
    *(uint64_t *)((char *)g_ctx + 0x18) = cL4_reg_x21();
    *(uint8_t *)((char *)g_ctx + 0x20) = cL4_reg_w4();
    cL4_help_77070();
    *(uint8_t *)((char *)g_ctx + 0x21) = 0;
    cL4_commit_651bc(cL4_reg_x8());
    if ((bool)cL4_flag_zr())
        return;
    cL4_canary_panic_11d7e8();
}

/* FUN_0008553c @ 0x8553c   (est. cL4_vas_dealloc)
 * Ghidra: void FUN_0008553c(void)
 * VAS deallocation op: reads x20+0x10 into a stack context, and if the object
 * is present and flagged (byte x20+0x21 == 1), runs the dealloc op
 * (FUN_00086434), checks status (FUN_0006e6dc) and on failure logs
 * "Could not deallocate vas span " + FUN_00084ee0(code) and traps at 0x8562c.
 * Finally releases the context (cL4_release_26e8).
 * Confidence: medium
 * Notes: s_Could_not_deallocate_vas_span_005c04f0. */
void FUN_0008553c(void)
{
    extern long *g_ctx;   /* unaff_x20 */
    uint64_t ctx[3];
    uint64_t pair[2];
    uint64_t st;
    cL4_help_867a8((uint64_t)g_ctx + 0x10, ctx);
    cL4_dispatch_3a1a0(0, 0, 0, 0);
    if ((*(long *)((char *)g_ctx + 0x10) != 0) &&
        (*(uint8_t *)((char *)g_ctx + 0x21) == 1)) {
        pair[0] = cL4_vas_op_86434(*(long *)((char *)g_ctx + 0x10),
                                   *(uint64_t *)((char *)g_ctx + 0x18));
        pair[1] = cL4_vas_op_86434_pair();
        st = cL4_status_6e6dc(0);
        if (st != 0) {
            uint64_t code = st & 0xffffffff | cL4_hi16_85b68(st) << 0x20;
            cL4_log_kind_2a4ab4(0x20);
            cL4_log_val_3a25d4(0xe000000000000000);
            cL4_log_86840("Could not deallocate vas span ");
            FUN_00084ee0(code, pair);
            cL4_log_pair_2acbb8(0, 0);
            cL4_log_val_3a25d4(cL4_reg_x1());
            cL4_log_trap_867c4(0x92);
            cL4_breakpoint(0x8562c);
        }
    }
    cL4_release_26e8((uint64_t)g_ctx + 0x28);
}

/* FUN_0008562c @ 0x8562c   (est. cL4_vas_dealloc_teardown)
 * Ghidra: void FUN_0008562c(void)
 * Runs FUN_0008553c then teardown (nop, destroy).
 * Confidence: low */
void FUN_0008562c(void)
{
    FUN_0008553c();
    cL4_nop_867b4();
    cL4_destroy_3a6ac(0, 0, 0, 0);
}

/* FUN_00085630 @ 0x85630   (est. cL4_vas_dealloc_teardown)
 * Ghidra: void FUN_00085630(void)
 * Same as FUN_0008562c.
 * Confidence: low */
void FUN_00085630(void)
{
    FUN_0008553c();
    cL4_nop_867b4();
    cL4_destroy_3a6ac(0, 0, 0, 0);
}

/* FUN_000856ac @ 0x856ac   (est. cL4_const_100)
 * Ghidra: undefined8 FUN_000856ac(void)
 * Returns 0x100.
 * Confidence: high */
uint64_t FUN_000856ac(void)
{
    return 0x100;
}

/* FUN_00085754 @ 0x85754   (est. cL4_mask_and_not)
 * Ghidra: uint FUN_00085754(uint param_1, uint param_2)
 * Returns param_2 & ~param_1.
 * Confidence: medium */
uint32_t FUN_00085754(uint32_t param_1, uint32_t param_2)
{
    return param_2 & (param_1 ^ 0xffffffff);
}

/* FUN_00085764 @ 0x85764   (est. cL4_log_trap2)
 * Ghidra: void FUN_00085764(void)
 * Fetches a function pointer (FUN_00027724) and calls it with two addresses
 * (0x6776f0, 0x671298) — a log/trap helper.
 * Confidence: low */
void FUN_00085764(void)
{
    void (*fn)(uint64_t, uint64_t) = cL4_fn_27724(0x671298);
    fn(0x6776f0, 0x671298);
}

/* FUN_00085854 @ 0x85854   (est. cL4_vas_flag_combine)
 * Ghidra: void FUN_00085854(undefined4 *param_1, undefined4 *param_2,
 *        undefined4 *param_3)
 * Computes *param_1 = cL4_vas_op_combine(*param_2, *param_3).
 * Confidence: medium */
void FUN_00085854(uint32_t *param_1, uint32_t *param_2, uint32_t *param_3)
{
    *param_1 = FUN_00084cc4(*param_2, *param_3);
}
