/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 Secure Kernel / GL1, arm64e,
 * image base 0) — Apple's seL4-derived microkernel. Ground truth: Ghidra
 * FUN_ names + addresses; seL4/cL4 vocabulary. All names are estimates unless
 * header/string-matched. Confidence recorded per function. */
#include <stdint.h>
#include <stddef.h>

/* =====================================================================
 * Shared extern helpers (called by functions in this slice).
 * Address in comment = Ghidra FUN_ address of the real callee.
 * ===================================================================== */

/* ---- noreturn panic / fatal printers ---- */
extern void sk_fatal_msg(const char *msg);                       /* FUN_00118b28 */
extern void sk_panic_msg(unsigned long code, const char *fmt, ...); /* FUN_0005b1b0 */
extern void sk_corrupt_panic(void);                              /* FUN_00062c14 */
extern void sk_corrupt_panic_b(void);                            /* FUN_00062bfc */
extern void sk_assert_panic(const char *msg);                    /* FUN_004afae4 */
extern void sk_fault_slot(unsigned long obj);                    /* FUN_0005fd24 */

/* ---- noreturn helpers local to this region (bodies below) ---- */
extern void sk_stack_check_fail(void);  /* FUN_0067f660 noreturn */

/* ---- cL4 monitor / syscall primitives ---- */
extern void CallSupervisor(unsigned long call);
extern void SoftwareBreakpoint(unsigned long code, unsigned long addr) __attribute__((noreturn));
extern void GENTER(void);               /* GENTER opcode 0x00201420 */
extern void InstructionSynchronizationBarrier(void);
extern void DataSynchronizationBarrier(unsigned long a, unsigned long b, unsigned long c);
extern void SysOp_W(unsigned long o0, unsigned long o1, unsigned long o2, unsigned long o3, unsigned long o4);
extern void ControlFlowPredictionRestrictionByContext(unsigned long x);
extern void CachePrefetchPredictionRestrictionByContext(unsigned long x);
extern void DataValuePredictionRestrictionByContext(unsigned long x);
extern unsigned long tpidrro_el0;       /* read of tpidrro_el0 (per-CPU/user context base) */
extern unsigned long tpidr_el0;         /* read of tpidr_el0 */

/* ---- generic memory / copy helpers ---- */
extern void sk_memcpy(unsigned long dst, unsigned long src, unsigned long n); /* FUN_0067aa00 */
extern void sk_memzero(unsigned long dst, unsigned long n);                /* FUN_0067a780 */
extern void sk_strcpy_pad(void *dst, const void *src, unsigned long n);/* FUN_0067d440-ish pad copy */
extern void *sk_alloc_region(unsigned long addr, unsigned long kind);   /* FUN_006827a8 */
extern void *sk_free_obj(unsigned long obj);                            /* FUN_006823d4 */
extern void *sk_alloc_zero_obj(unsigned long size, unsigned long kind); /* FUN_00683f48 */
extern unsigned long sk_lookup_obj(void *obj);               /* FUN_00650c34 returns slot count */

/* ---- per-CPU / per-domain context object helpers ---- */
extern unsigned long sk_cur_thread(void);            /* FUN_006510cc */
extern void *sk_cur_save_ctx(void);                  /* FUN_00651108 */
extern void *sk_next_notif(unsigned long *key);      /* FUN_00650ed0 */
extern unsigned long sk_notif_slot_get(void *n, unsigned long idx); /* FUN_00650b3c */
extern void sk_send_msg(unsigned long word, unsigned long arg);     /* FUN_0065df30 */
extern unsigned long sk_object_lookup(unsigned long a, unsigned long b); /* FUN_0064fbc4 */
extern unsigned long sk_object_lookup2(void);        /* FUN_0064fc4c */
extern void sk_ret_ctx_restore(unsigned long a, unsigned long b, unsigned long c); /* FUN_0065c310 */
extern void sk_alloc_page(unsigned long addr);       /* FUN_0065e378 */
extern int  sk_alloc_page_chk(void);                 /* FUN_0065e370 */
extern void sk_page_commit(unsigned long obj, unsigned long flags); /* FUN_0065def0 */
extern void sk_page_unwire(void);                    /* FUN_0065db84 */
extern int  sk_page_unwire_chk(void);                /* FUN_0065dda4 */
extern void sk_page_destroy(void);                   /* FUN_0065de3c */

/* ---- cL4 object-store (bucket) helpers ---- */
extern unsigned long sk_bucket_lookup(unsigned long id, unsigned long a, unsigned long b); /* FUN_0065be08 */
extern unsigned long sk_bucket_head(void);            /* FUN_0065cb74 */
extern unsigned long sk_bucket_iter(unsigned long id, unsigned long a, unsigned long b);   /* FUN_0065cbbc */
extern int  sk_bucket_acquire(unsigned long a, unsigned long b); /* FUN_0065cc0c */
extern void sk_bucket_release(unsigned long obj);     /* FUN_0065cc50 */
extern unsigned long sk_bucket_current(void);         /* FUN_0065ccdc */
extern unsigned long sk_bucket_lookup_name(unsigned long *inout, int which); /* FUN_0065cda8 */
extern unsigned long sk_bucket_read16(unsigned long out, unsigned long n);    /* FUN_0065d3d8 */
extern void sk_store_write8(unsigned long addr, unsigned long val);   /* FUN_0067cad8 */
extern unsigned long sk_cur_ipc_buf(unsigned long *inout); /* FUN_00654cc8 */
extern unsigned long sk_str_decode_adv(unsigned long s, unsigned long n, unsigned long one, unsigned long arg); /* FUN_0067d6c0 */
extern int  sk_str_decode_token(unsigned long n, unsigned long arg); /* FUN_0067d3f8 */

/* ---- context / state save-restore ---- */
extern void sk_ctx_finish(unsigned long a, unsigned long b);  /* FUN_0064effc */
extern void sk_sys_before(void);                     /* FUN_0065c218 */
extern void sk_sys_after(void);                      /* FUN_0065c9fc */
extern void sk_sys_reset(void);                      /* FUN_0065db00 */
extern void sk_sys_signal(unsigned long obj);        /* FUN_0065fd70 */
extern unsigned long sk_sys_wait(unsigned long obj); /* FUN_00661318 */
extern unsigned long sk_sys_next(unsigned long n);   /* FUN_0066239c */
extern void sk_vcpu_enter(void *key, void *v);       /* FUN_0066b750 */
extern void sk_sched_tick(void);                     /* FUN_0065cbbc */
extern void sk_trace_flush(void);                    /* FUN_0067dbc0 */
extern void sk_cache_flush(unsigned long a, unsigned long b);  /* FUN_006825bc */
extern void sk_rt_disable(unsigned long a);            /* FUN_0067d798 */
extern void sk_rt_write(unsigned long a, unsigned long b, unsigned long c); /* FUN_0067d83c */
extern void sk_rt_writel(unsigned long a, unsigned long b);  /* FUN_0067cffc */
extern unsigned long sk_rt_writel_ok(unsigned long a, unsigned long b); /* FUN_0067d014 */
extern void sk_rt_writel2(unsigned long a, unsigned long b); /* FUN_0067d02c */
extern void sk_rt_clr(unsigned long a, unsigned long b);     /* FUN_0067cfe0 */
extern void sk_rt_writel_t(unsigned long a, unsigned long b, unsigned long c);/* FUN_0067cd74 */
extern unsigned long sk_cur_magic(void);             /* FUN_0066ad54 */
extern unsigned long sk_cur_magic2(void);            /* FUN_00683e50 */
extern unsigned long sk_cur_magic3(void);            /* FUN_00683e68 */
extern unsigned long sk_obj_release(unsigned long obj);   /* FUN_006860f4 */
extern void sk_obj_release2(void);      /* FUN_00683e80 */
extern void sk_obj_release3(void);                   /* FUN_00683ea4 */
extern unsigned long sk_obj_release4(void);           /* FUN_00683ee8 */
extern void sk_obj_release5(void);                   /* FUN_00683e40 */
extern void sk_obj_release6(void);                   /* FUN_00683f38 */
extern void sk_obj_release7(void);                   /* FUN_00683f4c */
extern void sk_sched_switch(void);                   /* FUN_00665bd4 */
extern int  sk_sched_ready(unsigned long a, unsigned long b); /* FUN_0065bcf0 */
extern int  sk_sched_init(void);                     /* FUN_0066133c */
extern int  sk_sched_pin(unsigned long a, unsigned long b, unsigned long c); /* FUN_00660eec */
extern unsigned long sk_sched_slot(unsigned long n);   /* FUN_0065d90c */
extern void sk_sched_wake(unsigned long a, unsigned long b, unsigned long c, unsigned long d,
                          unsigned long e, unsigned long f, unsigned long g, unsigned long h); /* FUN_006631d8 */
extern int  sk_sched_unpin(void);                    /* FUN_006635ac */
extern void sk_sched_unpin2(unsigned long a, unsigned long b); /* FUN_006635c0 */
extern unsigned long sk_sched_unpin3(unsigned long a, unsigned long b); /* FUN_0066363c */
extern void sk_sched_unpin4(unsigned long a, unsigned long b); /* FUN_00663644 */
extern int  sk_mem_reclaim(void);                    /* FUN_0064cbc0 */
extern void sk_mem_reclaim2(void);                   /* FUN_0064fec8 */
extern void sk_mem_reclaim3(void);                   /* FUN_00650418 */
extern void sk_flush_soft(void);                     /* FUN_0065c218 */
extern unsigned long sk_flush_soft2(void);           /* FUN_00652204 */

/* ---- vspace / page-table helpers ---- */
extern void sk_vas_walk_commit(unsigned long a, unsigned long b, unsigned short c, long d); /* FUN_0064f7e8 */
extern void sk_vas_walk_commit2(void);               /* FUN_0064fa00 */
extern void sk_vas_walk_commit3(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e); /* FUN_0064fe58 */
extern unsigned long sk_vas_region_at(unsigned long a); /* FUN_0064fd24 */
extern unsigned long sk_vas_size_of(unsigned long a); /* FUN_0064faa4 */
extern unsigned long sk_vas_size_end(unsigned long a); /* FUN_0064fb28 */
extern void sk_vas_split(unsigned long a, unsigned long *b, unsigned long *c, unsigned long *d); /* FUN_0064fd5c */
extern unsigned long sk_vas_name(const void *a, unsigned long b); /* FUN_0064f458 */
extern void sk_vas_name2(unsigned long a, unsigned long b); /* FUN_0064e07c */
extern void sk_vas_unmap_all(unsigned long a, unsigned long b);   /* FUN_0065cda8-ish */
extern unsigned char __data[];   /* image __data section base (slide anchor) */

/* ---- IPC / notification helpers ---- */
extern void sk_ipc_send(unsigned long word, unsigned long arg); /* FUN_0065df30 */
extern void sk_notif_send(void);                     /* FUN_0064fec8 */

/* ---- globals referenced by bodies ---- */
extern unsigned long _DAT_006b5ed0;   /* stack-check canary */
extern unsigned long _DAT_006feb88;   /* PRNG state */
extern unsigned long _DAT_006feb90;   /* PRNG state */
extern unsigned long _DAT_006b4368;   /* current object / context pointer */
extern unsigned long _DAT_006b4380;   /* alternate context pointer */
extern unsigned long _DAT_006b4330;
extern unsigned long _DAT_006b4350;
extern unsigned long _DAT_006b43a0;
extern unsigned long _DAT_006b43c0;
extern unsigned long _DAT_006b43e0;
extern unsigned long _DAT_006b4458;
extern unsigned long _DAT_006b45b8;
extern void (*_DAT_006b4870)(void);  /* method-dispatch slot 3 */
extern void (*_DAT_006b4868)(unsigned long);  /* method-dispatch slot 3 (alt) */
extern void (*_DAT_006b4878)(unsigned long);  /* method-dispatch slot 7 release */
extern unsigned long _DAT_006bb920;   /* object-store initialized flag */
extern unsigned char *_DAT_006bb928;
extern unsigned int *_DAT_006bb930;
extern unsigned long _DAT_006bb938;
extern unsigned long _DAT_006bb940;
extern unsigned long _DAT_006bb948;
extern unsigned long _DAT_006bb950;
extern unsigned long _DAT_006bb988;   /* optional late hook */
extern unsigned long _DAT_006fc010;
extern unsigned long _DAT_006fc4e8;
extern unsigned long _DAT_006fc4e0;
extern unsigned long _DAT_006fc520;
extern unsigned long _DAT_006fc518;
extern unsigned long _DAT_006fec88;   /* slide delta */
extern unsigned long _DAT_006fec90;
extern unsigned long _DAT_006fec91;
extern unsigned long _DAT_006fec92;
extern unsigned long _DAT_006fec98;
extern unsigned long _DAT_006fc5e0;
extern unsigned long _DAT_006fc4a8;
extern unsigned long _DAT_006fc420;
extern unsigned long _DAT_006fc4f8;
extern unsigned long _DAT_006fc428, _DAT_006fc430, _DAT_006fc438, _DAT_006fc478;
extern unsigned long _DAT_006fc480, _DAT_006fc488, _DAT_006fc490, _DAT_006fc4b0;
extern unsigned long _DAT_006fc4b8, _DAT_006fc4c0, _DAT_006fc4c8, _DAT_006fc4d0;
extern unsigned long _DAT_006fc498, _DAT_006fc4a0, _DAT_006fc4d8, _DAT_006fc4f0;
extern unsigned long _DAT_006fc450, _DAT_006fc460, _DAT_006fc500, _DAT_006fc508;
extern unsigned long _DAT_006fc510, _DAT_006fc528, _DAT_006fc530, _DAT_006fc538;
extern unsigned long _DAT_006fc540, _DAT_006fc548, _DAT_006fc550, _DAT_006fc558;
extern unsigned long _DAT_006fc560, _DAT_006fc568, _DAT_006fc570, _DAT_006fc578;
extern unsigned long _DAT_006fb9c0;
extern unsigned long _DAT_006b43a0b;
extern unsigned long _DAT_0064c020;   /* machine feature register */extern unsigned long _DAT_0064c038;   /* image data base */
extern unsigned long _DAT_0064c058;   /* feature field */
extern unsigned long _DAT_0064c05c;   /* feature field */
extern unsigned long _DAT_00654240;   /* teardown callback table */

/* =====================================================================
 * Function bodies (address order).
 * ===================================================================== */

/* ---- forward declarations (mutual references within this slice) ---- */
static void sk_syscall_dispatch(unsigned long a1, unsigned short *badge, void *a3,
                                unsigned long a4, long base, unsigned long a6);
static void sk_notif_dispatch_all(int preempt, unsigned int flags);
static void sk_notif_dispatch_type_b(unsigned long arg);
static void sk_notif_dispatch_all_panic(void);
static void sk_ipc_reply_commit(long base, unsigned long arg2, long target, unsigned long count);
static unsigned long sk_vas_translate(long vas, unsigned long addr, long out_base);
static unsigned char sk_vas_any_mapped(long vas, unsigned long addr);
static unsigned long sk_vas_region_find(unsigned char *block, unsigned long size);
static void sk_vas_store_init(unsigned int *table, unsigned long size);
static unsigned long sk_vas_present(long vas, unsigned long addr);
static unsigned long sk_vas_lookup(long vas, unsigned long addr, long out_base);
static unsigned long sk_store_slot288(void);
static unsigned long sk_store_slot2a8(void);
static unsigned long sk_store_slot298(long arg);
static void sk_store_type3_hook(unsigned long a);
static void sk_vas_store_build_b(long desc);
static int sk_obj_create(unsigned long kind, unsigned char *tag, unsigned long *out);
static void sk_notif_broadcast(int want_root, unsigned long arg);
static void sk_notif_dispatch_all_panic(void);
static void sk_vspace_teardown(long async);
static void sk_object_store_build(void);
static unsigned long sk_deref_obj(unsigned long *obj);
static unsigned char sk_store_type1(void);
static unsigned char sk_store_type2(void);
static unsigned char sk_store_type3(void);
static unsigned long sk_store_type2_get(void);
static unsigned long sk_store_reply_word(void);
static void sk_store_dispatch_teardown(long entry, unsigned long cap, long size,
                                       unsigned long a, unsigned long b);
static void sk_rt_clr_entry(int clear_locks);
static void sk_fatal_6a5cea(void);   /* FUN_006833d4 variant */
static void sk_fatal_6a5da6(void);   /* FUN_006833d4 variant */
static void sk_fatal_6a5de8(void);   /* FUN_006833d4 variant */
static void sk_fatal_6a5d4e(void);   /* FUN_006833d4 variant */
static void sk_fatal_6a5aab(void);   /* FUN_006833d4 variant */
static void sk_fatal_6a5afd(void);   /* FUN_0067b280 noreturn */
static void sk_fatal_6a576b(void);   /* FUN_0067b280 noreturn */
static void sk_fatal_6a5e5a(void);   /* FUN_006833d4 variant */
static void sk_fatal_6a5ce0(void);

/* store descriptor validators: 2/1/0x100000001 defined below; 4-11 in sibling slices */
static int sk_store_desc2(long type, long desc);
static int sk_store_desc1(long type, long desc);
static int sk_store_desc0x100000001(long type, long desc);
extern int sk_store_desc4(long type, long desc);   /* FUN_006580ec */
extern int sk_store_desc5(long type, long desc);   /* FUN_00658870 */
extern int sk_store_desc6(long type, long desc);   /* FUN_00658ff4 */
extern int sk_store_desc7(long type, long desc);   /* FUN_00659774 */
extern int sk_store_desc8(long type, long desc);   /* FUN_00659ef4 */
extern int sk_store_desc9(long type, long desc);   /* FUN_0065a674 */
extern int sk_store_desc10(long type, long desc);  /* FUN_0065adf4 */
extern int sk_store_desc11(long type, long desc);  /* FUN_0065b574 */

/* store method functions defined below (used in desc init tables) */
static void sk_store_call120(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
static void sk_store_call130(long loop);
static void sk_store_call138(long loop);
static void sk_store_call160(long loop, unsigned long word);
static void sk_store_call120b(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
static void sk_store_call128b(long loop);
static void sk_store_call138b(long loop);
static void sk_store_call160b(long loop, unsigned long word);
static void sk_store_call58(long loop);
static void sk_store_call68(long loop);
static void sk_store_call98(long loop);
static void sk_store_call120c(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
static void sk_store_call128c(long loop);
static void sk_store_call138c(long loop);
static void sk_store_call160c(long loop, unsigned long word);
static void sk_store_call58c(long loop);
static void sk_store_call68c(long loop);
static void sk_store_call98c(long loop);

/* string / data-table addresses referenced by desc init blocks */
extern unsigned char _DAT_006887a8[];
extern unsigned char _DAT_006887b0[];
extern unsigned char _DAT_006887c0[];
extern unsigned char _DAT_00688888[];
extern unsigned char _DAT_00688950[];
extern unsigned char _DAT_00688a20[];
extern unsigned char _DAT_00688af0[];
extern unsigned char _DAT_00688bc0[];
extern unsigned char _DAT_00657578[];
extern unsigned char _DAT_00657590[];
extern unsigned char _DAT_006575a8[];
extern unsigned char _DAT_006575c4[];
extern unsigned char _DAT_00657614[];
extern unsigned char _DAT_0065762c[];
extern unsigned char _DAT_00657644[];
extern unsigned char _DAT_0065766c[];
extern unsigned char _DAT_006576c8[];
extern unsigned char _DAT_006576e8[];
extern unsigned char _DAT_00657704[];
extern unsigned char _DAT_0065771c[];
extern unsigned char _DAT_00657724[];
extern unsigned char _DAT_00657774[];
extern unsigned char _DAT_00657cf0[];
extern unsigned char _DAT_00657d08[];
extern unsigned char _DAT_00657d20[];
extern unsigned char _DAT_00657d3c[];
extern unsigned char _DAT_00657d54[];
extern unsigned char _DAT_00657d8c[];
extern unsigned char _DAT_00657da4[];
extern unsigned char _DAT_00657dbc[];
extern unsigned char _DAT_00657de4[];
extern unsigned char _DAT_00657e08[];
extern unsigned char _DAT_00657e10[];
extern unsigned char _DAT_00657e18[];
extern unsigned char _DAT_00657e20[];
extern unsigned char _DAT_00657e28[];
extern unsigned char _DAT_00657e30[];
extern unsigned char _DAT_00657e38[];
extern unsigned char _DAT_00657e40[];
extern unsigned char _DAT_00657e60[];
extern unsigned char _DAT_00657e7c[];
extern unsigned char _DAT_00657e9c[];
extern unsigned char _DAT_00657ed0[];
extern unsigned char _DAT_00657eec[];
extern unsigned char _DAT_00657f0c[];
extern unsigned char _DAT_00657f2c[];
extern unsigned char _DAT_00657f74[];
extern unsigned char _DAT_00657fb4[];
extern unsigned char _DAT_00657fbc[];

/* ---- noreturn state-fatal panic helpers (FUN_006833d4 / FUN_0067b280 variants) ---- */
static void sk_fatal_6a5e5a(void)  { sk_fatal_msg("store state fatal"); }
static void sk_fatal_6a5aab(void)  { sk_fatal_msg("teardown fatal"); }
static void sk_fatal_6a5afd(void)  { sk_fatal_msg("init fatal"); }
static void sk_fatal_6a576b(void)  { sk_fatal_msg("slot check fatal"); }
static void sk_fatal_6a5cea(void)  { sk_fatal_msg("store build fatal (0x6a5cea)"); }
static void sk_fatal_6a5da6(void)  { sk_fatal_msg("store build fatal (0x6a5da6)"); }
static void sk_fatal_6a5de8(void)  { sk_fatal_msg("store build fatal (0x6a5de8)"); }
static void sk_fatal_6a5d4e(void)  { sk_fatal_msg("store build fatal (0x6a5d4e)"); }
static void sk_fatal_6a5ce0(void)  { sk_fatal_msg("store build fatal (0x6a5ce0)"); }

/* object-create helper (FUN_0066a8c4 vtable dispatch, 6-arg) */
extern int sk_obj_vt_call(void *self, unsigned long kind, unsigned char *tag,
                          unsigned long *out, unsigned long a, unsigned long b);

/* L4 error-code name strings (Ghidra s_L4_ErrorCode*_00688648..) */
extern unsigned char _DAT_00688788[];   /* overflow/hex fallback string */

/* sk_obj_create: dispatch object creation through the vtable (FUN_0066a8c4 + call) */
static int sk_obj_create(unsigned long kind, unsigned char *tag, unsigned long *out)
{
    /* returns nonzero on error; the real helper resolves self/vtable via FUN_0066a8c4 */
    return sk_obj_vt_call(0, kind, tag, out, 0, 0);
}

/* FUN_00652254 @ 0x00652254  (est. sk_syscall_dispatch)
 * Ghidra: void FUN_00652254(undefined8 param_1, ushort *param_2, undefined8 param_3,
 *                           undefined8 param_4, long param_5, undefined8 param_6)
 * System-call / capability dispatch: decodes a 28-bit (0..0x1c) syscall index from
 * the caller's badge word *param_2 (little-endian byte order), validates it, and
 * invokes the corresponding handler from the global dispatch table at 0x6b5f40
 * (each entry stride 0x30; handler pointer at +8, its owning domain at +0). The
 * target domain is resolved via FUN_0064fbc4; the handler is called only when the
 * domain owns the slot, then the resulting write range (param_5 + [base,base+size))
 * is bounds-checked against the region before jumping through the handler.
 * Confidence: medium */
static void sk_syscall_dispatch(unsigned long a1, unsigned short *badge, void *a3,
                                unsigned long a4, long base, unsigned long a6)
{
    unsigned long *region;            /* resolved domain region */
    unsigned long slot;               /* decoded syscall index */
    void (*handler)(unsigned long, unsigned short *, void *);
    unsigned long end;                /* end of the write range */

    region = (unsigned long *)sk_object_lookup(a4, a6);
    slot = (unsigned long)((unsigned char)badge[1] << 0x10) |
           ((unsigned long)*(unsigned char *)((long)badge + 3) << 0x18) |
           (unsigned long)badge[0];
    if (0x1c < (unsigned int)slot) {
        sk_fatal_msg("syscall index out of range");   /* FUN_0065c2f0(0,0x6a592b) noreturn */
    }
    handler = *(void (**)(unsigned long, unsigned short *, void *))((slot * 0x30) + 0x6b5f48);
    if (handler != 0 && *(long *)((slot * 0x30) + 0x6b5f40) != 0 && region != 0 &&
        (region = (unsigned long *)sk_object_lookup2(), region != 0)) {
        end = *(unsigned long *)((long)region + 0x20) + base;
        if (end < (unsigned long)(*(unsigned long *)((long)region + 0x20) + base) ||
            end - *(unsigned long *)((long)region + 0x20) < *(unsigned long *)((long)region + 0x28)) {
            /* overflow / underflow in the guest write range -> fault */
            SoftwareBreakpoint(0x5519, 0x652304);
        }
        handler(a1, badge, a3);
    }
}

/* FUN_00652354 @ 0x00652354  (est. sk_notif_dispatch_all)
 * Ghidra: void FUN_00652354(int param_1, uint param_2)
 * Iterates every live notification object in the notification bucket (list headed by
 * FUN_0065cb74) and, for each that is signalled (low bit of type word set), dispatches
 * it: first a "type-agnostic" dispatch (0x6a597e) when param_1 (preempt flag) is set,
 * then the per-notification dispatch (0x6a53cc). Uses the current-thread key
 * (FUN_006510cc) and the per-cpu save context (FUN_00651108).
 * Confidence: medium */
static void sk_notif_dispatch_all(int preempt, unsigned int flags)
{
    long *node;
    unsigned long cur;
    unsigned char save_ctx[16];
    short *n;
    unsigned long key;
    unsigned long size;
    unsigned long size2;

    node = (long *)sk_bucket_head();
    cur = sk_cur_thread();
    if (cur != 0 && cur + 8 < cur) {
        SoftwareBreakpoint(0x5519, 0x652550);
    }
    sk_memzero((unsigned long)save_ctx, sizeof save_ctx);
    do {
        if (node == 0) {
            return;
        }
        if (*(char *)(node + 1) < 0) {         /* object signalled */
            key = node[7];
            n = (short *)sk_next_notif(&key);
            if (n != 0) {
                do {
                    if (n + 6 < n) {
                        SoftwareBreakpoint(0x5519, 0x652550);
                    }
                    if (((char)n[1] == 0 && *(char *)((long)n + 3) == 0) && n[0] == 0) {
                        size = ((unsigned long)(unsigned char)n[2] << 0x10) |
                               ((unsigned long)*(unsigned char *)((long)n + 7) << 0x18) |
                               (unsigned long)n[0] |
                               ((unsigned long)((unsigned int)(unsigned char)n[4] << 0x10 |
                                                (unsigned int)*(unsigned char *)((long)n + 0xb) << 0x18 |
                                                (unsigned int)n[3]) << 0x20);
                        size2 = ((unsigned long)(unsigned char)n[2] << 0x10) |
                                ((unsigned long)*(unsigned char *)((long)n + 7) << 0x18) |
                                (unsigned long)n[0] |
                                ((unsigned long)((unsigned int)(unsigned char)n[4] << 0x10 |
                                                 (unsigned int)*(unsigned char *)((long)n + 0xb) << 0x18 |
                                                 (unsigned int)n[3]) << 0x20);
                        if (preempt != 0) {
                            if (key + 0x20 < key) {
                                SoftwareBreakpoint(0x5519, 0x652550);
                            }
                            sk_syscall_dispatch(cur, n, save_ctx, key, node[4], 0x6a597e);
                        }
                        if ((flags & 1) == 0) {
                            if (size < size2 || key + 0x20 < key) {
                                SoftwareBreakpoint(0x5519, 0x652550);
                            }
                            sk_syscall_dispatch(cur, n, save_ctx, key, node[4], 0x6a53cc);
                        }
                    }
                    n = (short *)sk_next_notif(&key);
                } while (n != 0);
            }
        }
        node = (long *)*node;
    } while (1);
}

/* FUN_00652550 @ 0x00652550  (est. sk_notif_dispatch_all2)
 * Ghidra: void FUN_00652550(int param_1, int param_2)
 * Like sk_notif_dispatch_all, but selects notifications by their type word: when
 * param_2 is set, only type-0 (badge word 0) notifications are pre-dispatched; every
 * non-zero-type notification is then dispatched. Same 0x6a53cc / 0x6a597e dispatch
 * endpoints.
 * Confidence: high (verified vs decompile 2026-08-12; trap 0x6527c8, byte-packing
 *   size/type, 0x6a53cc/0x6a597e endpoints, select_zero logic all match) */
static void sk_notif_dispatch_all2(int preempt, int select_zero)
{
    long *node;
    unsigned long cur;
    unsigned char save_ctx[16];
    unsigned short *n;
    unsigned long key;
    unsigned long size;
    unsigned long size2;
    unsigned int type;

    node = (long *)sk_bucket_head();
    cur = sk_cur_thread();
    if (cur != 0 && cur + 8 < cur) {
        SoftwareBreakpoint(0x5519, 0x6527c8);
    }
    sk_memzero((unsigned long)save_ctx, sizeof save_ctx);
    do {
        if (node == 0) {
            return;
        }
        if (*(char *)(node + 1) < 0) {
            key = node[7];
            n = (unsigned short *)sk_next_notif(&key);
            if (n != 0) {
                do {
                    if (n + 6 < n) {
                        SoftwareBreakpoint(0x5519, 0x6527c8);
                    }
                    size = ((unsigned long)(unsigned char)n[3] << 0x10) |
                           ((unsigned long)*(unsigned char *)((long)n + 7) << 0x18) |
                           (unsigned long)n[2] |
                           ((unsigned long)((unsigned int)(unsigned char)n[5] << 0x10 |
                                            (unsigned int)*(unsigned char *)((long)n + 0xb) << 0x18 |
                                            (unsigned int)n[4]) << 0x20);
                    type = ((unsigned int)(unsigned char)n[1] << 0x10) |
                           ((unsigned int)*(unsigned char *)((long)n + 3) << 0x18) |
                           (unsigned int)n[0];
                    if (select_zero != 0 && type == 0) {
                        if (key + 0x20 < key) {
                            SoftwareBreakpoint(0x5519, 0x6527c8);
                        }
                        sk_syscall_dispatch(cur, n, save_ctx, key, node[4], 0x6a53cc);
                        if (size < ((unsigned long)(unsigned char)n[3] << 0x10 |
                                    (unsigned long)*(unsigned char *)((long)n + 7) << 0x18 |
                                    (unsigned long)n[2] |
                                    ((unsigned long)((unsigned int)(unsigned char)n[5] << 0x10 |
                                                     (unsigned int)*(unsigned char *)((long)n + 0xb) << 0x18 |
                                                     (unsigned int)n[4]) << 0x20))) {
                            SoftwareBreakpoint(0x5519, 0x6527c8);
                        }
                        type = ((unsigned int)(unsigned char)n[1] << 0x10) |
                               ((unsigned int)*(unsigned char *)((long)n + 3) << 0x18) |
                               (unsigned int)n[0];
                    }
                    if (type != 0) {
                        if (preempt != 0) {
                            if (key + 0x20 < key) {
                                SoftwareBreakpoint(0x5519, 0x6527c8);
                            }
                            sk_syscall_dispatch(cur, n, save_ctx, key, node[4], 0x6a597e);
                        }
                        if (size < ((unsigned long)(unsigned char)n[3] << 0x10 |
                                    (unsigned long)*(unsigned char *)((long)n + 7) << 0x18 |
                                    (unsigned long)n[2] |
                                    ((unsigned long)((unsigned int)(unsigned char)n[5] << 0x10 |
                                                     (unsigned int)*(unsigned char *)((long)n + 0xb) << 0x18 |
                                                     (unsigned int)n[4]) << 0x20))) {
                            SoftwareBreakpoint(0x5519, 0x6527c8);
                        }
                        sk_syscall_dispatch(cur, n, save_ctx, key, node[4], 0x6a53cc);
                    }
                    n = (unsigned short *)sk_next_notif(&key);
                } while (n != 0);
            }
        }
        node = (long *)*node;
    } while (1);
}

/* FUN_006527c8 @ 0x006527c8  (est. sk_notif_dispatch_type_b)
 * Ghidra: void FUN_006527c8(undefined8 param_1)
 * Iterates notifications for the current thread and dispatches only those whose type
 * word equals 0xb, walking each matched notification's slot list (FUN_00650c34 /
 * FUN_00650b3c) and sending each slot address via sk_send_msg. If none matched, sends
 * the literal 0x706c6174 ("plat") tag.
 * Confidence: medium */
static void sk_notif_dispatch_type_b(unsigned long arg)
{
    unsigned long cur;
    unsigned short *n;
    unsigned long key;
    int matched;
    unsigned long slot;
    int i, cnt;
    unsigned short w2, w3, w4, w5, w6;
    unsigned char b1, b2;

    cur = sk_cur_thread();
    if (cur != 0 && cur + 8 < cur) {
        SoftwareBreakpoint(0x5519, 0x6529d8);
    }
    key = 0;
    n = (unsigned short *)sk_next_notif(&key);
    if (n != 0) {
        matched = 0;
        do {
            if (n + 6 < n) {
                SoftwareBreakpoint(0x5519, 0x6529d8);
            }
            if ((((unsigned int)(unsigned char)n[1] << 0x10) |
                 ((unsigned int)*(unsigned char *)((long)n + 3) << 0x18) |
                 (unsigned int)n[0]) == 0xb) {
                w2 = n[2]; b1 = *(unsigned char *)((long)n + 7); w3 = n[3];
                w4 = n[4]; b2 = *(unsigned char *)((long)n + 0xb); w5 = n[5]; w6 = 0;
                slot = sk_lookup_obj(n);
                if (slot != 0) {
                    cnt = 0;
                    do {
                        if ((((unsigned long)(unsigned char)w3 << 0x10) |
                             ((unsigned long)b1 << 0x18) | (unsigned long)w2 |
                             ((unsigned long)((unsigned int)(unsigned char)w5 << 0x10 |
                                              (unsigned int)b2 << 0x18 |
                                              (unsigned int)w4) << 0x20)) <
                            ((unsigned long)(unsigned char)n[3] << 0x10 |
                             (unsigned long)*(unsigned char *)((long)n + 7) << 0x18 |
                             (unsigned long)n[2] |
                             ((unsigned long)((unsigned int)(unsigned char)n[5] << 0x10 |
                                              (unsigned int)*(unsigned char *)((long)n + 0xb) << 0x18 |
                                              (unsigned int)n[4]) << 0x20))) {
                            SoftwareBreakpoint(0x5519, 0x6529d8);
                        }
                        n = (unsigned short *)sk_notif_slot_get(n, cnt);
                        sk_send_msg(((unsigned long)(unsigned char)n[1] << 0x10) |
                                    ((unsigned long)*(unsigned char *)((long)n + 3) << 0x18) |
                                    (unsigned long)n[0] |
                                    ((unsigned long)((unsigned int)(unsigned char)n[3] << 0x10 |
                                                     (unsigned int)*(unsigned char *)((long)n + 7) << 0x18 |
                                                     (unsigned int)n[2]) << 0x20), arg);
                        cnt++;
                    } while (slot != cnt);
                }
                matched = 1;
            }
            n = (unsigned short *)sk_next_notif(&key);
        } while (n != 0);
        if (matched) {
            return;
        }
    }
    sk_send_msg(0x706c6174, arg);   /* fallback "plat" tag when no 0xb notification */
}

/* FUN_006529d8 @ 0x006529d8  (est. sk_strlen_or_null)
 * Ghidra: char *FUN_006529d8(char *param_1, long param_2)
 * Returns a NUL-terminated sub-string pointer within [param_1, param_1+param_2), or
 * NULL if param_2 equals the current length (no terminator found). Scans for the
 * first '\0' byte.
 * Confidence: high */
static char *sk_strlen_or_null(char *s, long limit)
{
    char c;
    char *p;

    if (sk_cur_magic() == limit) {        /* thunk_FUN_0067b180 = magic read */
        s = 0;
    } else {
        if (limit == 0) {
            SoftwareBreakpoint(0x5519, 0x652a38);
        }
        p = s;
        do {
            if (s + limit < p + 1) {
                SoftwareBreakpoint(0x5519, 0x652a38);
            }
            c = *p;
            p = p + 1;
        } while (c != '\0');
    }
    return s;
}

/* FUN_00652a38 @ 0x00652a38  (est. sk_ipc_reply_copyout)
 * Ghidra: undefined8 FUN_00652a38(long *param_1, long param_2, ushort *param_3)
 * IPC reply copy-out: validates the calling thread's state slot (param_2+0x117), then
 * re-derives the capability slot pair from the caller's saved registers (param_2) and
 * writes the result back into the IPC buffer at param_3, advancing its slot index.
 * If the invocation result object (local_68) was non-zero it is dispatched as a reply
 * capability; a zero object aborts via sk_notif_dispatch_all (FUN_0065558c).
 * Confidence: medium */
static unsigned long sk_ipc_reply_copyout(long *vas, long thr, unsigned short *buf)
{
    unsigned long slot_off, slot2_off;
    long slot_ptr;
    unsigned char f1, f2, f3, f4, f5, f6, f7, f8;
    unsigned short w1, w2, w3, w4;
    unsigned short *cur, *end;
    unsigned long word;
    unsigned short cnt;
    unsigned long reply_obj;
    unsigned long dst;
    int rc;
    unsigned char save[16];
    unsigned long local_70, local_80, local_68;
    unsigned char local_90[8];
    long local_88;

    if ((*(unsigned char *)(thr + 0x117) >> 2) != 0) {
        sk_fatal_6a576b();
    }
    cur = buf + 0xc0;
    w1 = buf[0xc2];
    f1 = *(unsigned char *)(thr + 0x104);
    w2 = *(unsigned short *)(thr + 0x108);
    f3 = *(unsigned char *)(thr + 0x10b);
    f4 = *(unsigned char *)(thr + 0x10a);
    w3 = *(unsigned short *)(thr + 0x10c);
    f5 = *(unsigned char *)(thr + 0x10f);
    f6 = *(unsigned char *)(thr + 0x10e);
    word = ((unsigned long)f4 << 0x10) | ((unsigned long)f3 << 0x18) | (unsigned long)w2 |
           (((unsigned long)((unsigned int)f6 << 0x10) | ((unsigned int)f5 << 0x18) |
             (unsigned int)w3) << 0x20);
    slot_off = (((unsigned long)*(unsigned char *)(thr + 0x112) << 0x10) |
                ((unsigned long)*(unsigned char *)(thr + 0x113) << 0x18) |
                (unsigned long)*(unsigned short *)(thr + 0x110) |
                ((unsigned long)((unsigned int)*(unsigned char *)(thr + 0x116) << 0x10) |
                 ((unsigned int)*(unsigned char *)(thr + 0x117) << 0x18) |
                 (unsigned int)*(unsigned short *)(thr + 0x114)) << 0x20) * 0x40;
    if (slot_off < (unsigned long)vas[1]) {
        slot_ptr = slot_off + vas[0];
    } else {
        slot_ptr = 0;
    }
    f7 = *(unsigned char *)(thr + 0x102);
    f8 = *(unsigned char *)(thr + 0x106);
    w4 = buf[0xc1];
    cnt = buf[0xc3];
    f2 = *(unsigned char *)(thr + 0x101);
    f3 = *(unsigned char *)(thr + 0x100);
    f4 = *(unsigned char *)(thr + 0x103);
    f5 = *(unsigned char *)(thr + 0x105);
    f6 = *(unsigned char *)(thr + 0x107);
    w1 = buf[0xc0];
    /* signature: param_3 index (1..N) byte lane selection */
    rc = 0;   /* thunk_FUN_0067aff0(thr,0x6a5995,0x100) -> slot-check */
    if (rc != 0) {
        local_70 = 0;
        local_68 = 0;
        local_88 = 0;
        local_90[0] = 0x11;
        /* thunk_FUN_0067a780((ulong)local_90|1,0xf) zero fill */
        if (sk_obj_create(0x1a08, local_90, &local_70) != 0) {
            return 0;
        }
        sk_ipc_reply_commit(slot_ptr, local_70, local_68, word);
        if (local_68 == 0) {
            sk_notif_dispatch_all_panic();
        }
        (*(void (**)(unsigned long, unsigned char *))(local_68 + 8))(local_70, local_90);
        slot_ptr = local_88;
    }
    /* store the reply capability slot back into the IPC buffer at index */
    end = buf + ((unsigned long)(unsigned char)w4 << 0x10 |
                 ((unsigned long)*(unsigned char *)((long)buf + 0x183) << 0x18) |
                 (unsigned long)buf[0xc0] |
                 ((unsigned long)((unsigned int)(unsigned char)cnt << 0x10 |
                                  (unsigned int)*(unsigned char *)((long)buf + 0x187) << 0x18 |
                                  (unsigned int)buf[0xc2]) << 0x20)) * 0xc;
    if (buf <= end && end + 0xc <= cur && end <= end + 0xc) {
        *(char *)((long)end + 0x15) = (char)((unsigned long)slot_ptr >> 0x28);
        *(char *)(end + 8) = (char)slot_ptr;
        *(char *)((long)end + 0x13) = (char)((unsigned long)slot_ptr >> 0x18);
        *(char *)(end + 9) = (char)((unsigned long)slot_ptr >> 0x10);
        *(char *)((long)end + 0x11) = (char)((unsigned long)slot_ptr >> 8);
        *(char *)(end + 10) = (char)((unsigned long)slot_ptr >> 0x20);
        *(char *)((long)end + 0x17) = (char)((unsigned long)slot_ptr >> 0x38);
        *(char *)(end + 0xb) = (char)((unsigned long)slot_ptr >> 0x30);
        *(char *)((long)end + 0xd) = (char)(w3 >> 8);
        *(char *)(end + 4) = (char)w2;
        *(unsigned char *)((long)end + 0xb) = f3;
        *(unsigned char *)(end + 5) = f4;
        *(char *)((long)end + 9) = (char)(w2 >> 8);
        *(char *)(end + 6) = (char)w3;
        *(unsigned char *)((long)end + 0xf) = f5;
        *(unsigned char *)(end + 7) = f6;
        *(unsigned char *)end = f3;
        *(unsigned char *)((long)end + 5) = f5;
        *(unsigned char *)((long)end + 3) = f4;
        *(unsigned char *)(end + 1) = f7;
        *(unsigned char *)((long)end + 1) = f2;
        *(unsigned char *)(end + 2) = f1;
        *(unsigned char *)((long)end + 7) = f6;
        *(unsigned char *)(end + 3) = f8;
        slot_ptr = ((unsigned long)(unsigned char)buf[0xc1] << 0x10 |
                    ((unsigned long)*(unsigned char *)((long)buf + 0x183) << 0x18) |
                    (unsigned long)*cur |
                    ((unsigned long)((unsigned int)(unsigned char)buf[0xc3] << 0x10 |
                                     (unsigned int)*(unsigned char *)((long)buf + 0x187) << 0x18 |
                                     (unsigned int)buf[0xc2]) << 0x20)) + 1;
        *(char *)cur = (char)slot_ptr;
        *(unsigned char *)(buf + 0xc3) = (unsigned char)((unsigned long)slot_ptr >> 0x30);
        *(char *)((long)buf + 0x187) = (char)((unsigned long)slot_ptr >> 0x38);
        *(char *)(buf + 0xc2) = (char)((unsigned long)slot_ptr >> 0x20);
        *(char *)((long)buf + 0x185) = (char)((unsigned long)slot_ptr >> 0x28);
        *(unsigned char *)(buf + 0xc1) = (unsigned char)((unsigned long)slot_ptr >> 0x10);
        *(char *)((long)buf + 0x183) = (char)((unsigned long)slot_ptr >> 0x18);
        *(char *)((long)buf + 0x181) = (char)((unsigned long)slot_ptr >> 8);
        return 1;
    }
    SoftwareBreakpoint(0x5519, 0x652e24);
    return 0;
}

/* forward declaration (defined below) */
static void sk_ipc_reply_commit(long base, unsigned long arg2, long target, unsigned long count);

/* FUN_00652e34 @ 0x00652e34  (est. sk_ipc_reply_commit)
 * Ghidra: void FUN_00652e34(long param_1, undefined8 param_2, long param_3, ulong param_4)
 * Commits an IPC reply: zeroes the per-CPU user-message area (tpidrro_el0), delivers a
 * supervisor call (CallSupervisor(0)) carrying the reply word, and when the reply is
 * an error (nonzero low byte from the target's reply handler at param_3+0x28) routes
 * the error code into a global error table. If the caller-supplied region (param_1) is
 * non-NULL the region is unwired first. Loop until the target reports completion.
 * Confidence: medium */
static void sk_ipc_reply_commit(long base, unsigned long arg2, long target, unsigned long count)
{
    unsigned char *m;
    unsigned long i, w, err, cur;
    unsigned long canary = _DAT_006b5ed0;

    cur = sk_cur_magic();
    if (0x3fff < count) {
        w = 0;
        m = (unsigned char *)tpidrro_el0;
        do {
            m[4] = 0; m[1] = 0; m[5] = 0; m[2] = 0; m[3] = 0;
            m[0] = 0x11; m[6] = 0; m[7] = 0;
            m[0xd] = (char)(w >> 0x1a); m[8] = 0;
            m[9] = (char)(w << 6); m[0xb] = (char)(w >> 10); m[10] = (char)(w >> 2);
            m[0xc] = (char)(w >> 0x12);
            m[0xf] = (char)((w >> 0x20) >> 10); m[0xe] = (char)((w >> 0x20) >> 2);
            m[0x15] = (char)(cur >> 0x28); m[0x10] = (char)cur;
            m[0x13] = (char)(cur >> 0x18); m[0x12] = (char)(cur >> 0x10);
            m[0x11] = (char)(cur >> 8); m[0x14] = (char)(cur >> 0x20);
            m[0x17] = (char)(cur >> 0x38); m[0x16] = (char)(cur >> 0x30);
            CallSupervisor(0);
            m[7] = 0; m[6] = 0; m[5] = 0; m[4] = 0; m[3] = 0; m[2] = 0;
            m[0] = 0x11; m[1] = 0;
            if (base != 0) {
                sk_vas_unmap_all(base, 0);
                sk_fatal_msg("reply error");   /* FUN_0065c2f0(0,0x6a59a9) */
            }
            err = (**(unsigned long (**)(unsigned long, unsigned long, unsigned long))
                   (target + 0x28))(arg2, w << 0xe, cur);
            if ((err & 0xff) != 0) {
                m = (unsigned char *)((err & 0xff) * 8 + 0x6b5e50);
                if (m < (unsigned char *)0x6b5e50 || (unsigned char *)0x6b5e90 < m + 8 ||
                    m + 8 < m) {
                    SoftwareBreakpoint(0x5519, 0x6530a0);
                }
                sk_fatal_msg("reply error slot");  /* FUN_0065c2f0(0,0x6a59e4) */
            }
            do {
                CallSupervisor(4);
            } while (cur == 1);
            w++;
        } while (w != count >> 0xe);
    }
    if (_DAT_006b5ed0 == canary) {
        sk_obj_release(cur);
        return;
    }
    sk_stack_check_fail();
}

/* FUN_006530a0 @ 0x006530a0  (est. sk_l4_error_str)
 * Ghidra: void FUN_006530a0(undefined8 param_1, byte param_2)
 * Writes the L4 error-code name for param_2 (0..9) into param_1 as a 32-byte padded
 * string; codes >= 10 fall back to the raw hex representation.
 * Confidence: high (string-matched L4 error-code names) */
static void sk_l4_error_str(unsigned long dst, unsigned char code)
{
    char *name;

    if (9 < code) {
        sk_memcpy(dst, (unsigned long)_DAT_00688788, 0x20);
        sk_ctx_finish(dst, 0x20);
        return;
    }
    switch (code) {
    case 1: name = "L4_ErrorCodePreempted"; break;
    case 2: name = "L4_ErrorCodeCanceled"; break;
    case 3: name = "L4_ErrorCodeTruncated"; break;
    case 4: name = "L4_ErrorCodeCapInvalid"; break;
    case 5: name = "L4_ErrorCodeSlotInvalid"; break;
    case 6: name = "L4_ErrorCodeMethodInvalid"; break;
    case 7: name = "L4_ErrorCodeArgumentInvalid"; break;
    case 8: name = "L4_ErrorCodeOperationInvalid"; break;
    case 9: name = "L4_ErrorCodePermissionInvalid"; break;
    default: name = "L4_ErrorCodeSuccess"; break;
    }
    sk_memcpy(dst, (unsigned long)name, 0x20);
}

/* FUN_006531d8 @ 0x006531d8  (est. sk_vspace_slot_lookup)
 * Ghidra: void FUN_006531d8(long *param_1, long param_2, undefined1 *param_3)
 * Resolves the two capability slots (a pair: root and nested) for a thread by reading
 * its saved register file (param_2+0x100..0x11f) and writes the resulting 64-bit
 * pointers into param_3 at offsets 0x00 and 0xe8 respectively. The slot index fields
 * live at param_2+0x100 (vspace slot) and param_2+0x108 (region slot).
 * Confidence: medium */
static void sk_vspace_slot_lookup(long *vas, long thr, unsigned char *out)
{
    unsigned long off, off2;
    long slot_ptr, slot_ptr2;
    unsigned short u9, u10, u11, u12;
    unsigned char u1, u2, u3, u4, u5, u6, u7, u8;

    if ((*(unsigned char *)(thr + 0x107) >> 2) != 0) {
        sk_fatal_6a576b();
    }
    off = (((unsigned long)*(unsigned char *)(thr + 0x102) << 0x10) |
           ((unsigned long)*(unsigned char *)(thr + 0x103) << 0x18) |
           (unsigned long)*(unsigned short *)(thr + 0x100) |
           (((unsigned long)((unsigned int)*(unsigned char *)(thr + 0x106) << 0x10) |
             ((unsigned int)*(unsigned char *)(thr + 0x107) << 0x18) |
             (unsigned int)*(unsigned short *)(thr + 0x104)) << 0x20)) * 0x40;
    if (off < (unsigned long)vas[1]) {
        slot_ptr = off + vas[0];
    } else {
        slot_ptr = 0;
    }
    off2 = ((unsigned long)*(unsigned char *)(thr + 0x10a) << 0x10) |
           ((unsigned long)*(unsigned char *)(thr + 0x10b) << 0x18) |
           (unsigned long)*(unsigned short *)(thr + 0x108) |
           (((unsigned long)((unsigned int)*(unsigned char *)(thr + 0x10e) << 0x10) |
             ((unsigned int)*(unsigned char *)(thr + 0x10f) << 0x18) |
             (unsigned int)*(unsigned short *)(thr + 0x10c)) << 0x20);
    if (off2 != 0) {
        if ((*(unsigned char *)(thr + 0x10f) >> 2) != 0) {
            sk_fatal_6a576b();
        }
        off2 = off2 * 0x40;
        if (off2 < (unsigned long)vas[1]) {
            slot_ptr2 = off2 + vas[0];
            goto write_out;
        }
    }
    slot_ptr2 = 0;
write_out:
    out[0] = (char)slot_ptr;
    out[5] = (char)((unsigned long)slot_ptr >> 0x28);
    out[3] = (char)((unsigned long)slot_ptr >> 0x18);
    out[2] = (char)((unsigned long)slot_ptr >> 0x10);
    out[1] = (char)((unsigned long)slot_ptr >> 8);
    out[4] = (char)((unsigned long)slot_ptr >> 0x20);
    out[7] = (char)((unsigned long)slot_ptr >> 0x38);
    out[6] = (char)((unsigned long)slot_ptr >> 0x30);
    out[0xed] = (char)((unsigned long)slot_ptr2 >> 0x28);
    out[0xe8] = (char)slot_ptr2;
    out[0xeb] = (char)((unsigned long)slot_ptr2 >> 0x18);
    out[0xea] = (char)((unsigned long)slot_ptr2 >> 0x10);
    out[0xe9] = (char)((unsigned long)slot_ptr2 >> 8);
    out[0xec] = (char)((unsigned long)slot_ptr2 >> 0x20);
    out[0xef] = (char)((unsigned long)slot_ptr2 >> 0x38);
    out[0xee] = (char)((unsigned long)slot_ptr2 >> 0x30);
    /* 16-byte register block copy from thr+0x110 into out+0xf0 */
    u9 = *(unsigned short *)(thr + 0x110); u1 = *(unsigned char *)(thr + 0x113);
    u2 = *(unsigned char *)(thr + 0x112); u10 = *(unsigned short *)(thr + 0x114);
    u3 = *(unsigned char *)(thr + 0x117); u4 = *(unsigned char *)(thr + 0x116);
    u11 = *(unsigned short *)(thr + 0x118); u5 = *(unsigned char *)(thr + 0x11b);
    u6 = *(unsigned char *)(thr + 0x11a); u12 = *(unsigned short *)(thr + 0x11c);
    u7 = *(unsigned char *)(thr + 0x11f); u8 = *(unsigned char *)(thr + 0x11e);
    out[0xf0] = (char)u9; out[0xfd] = (char)((unsigned short)u12 >> 8);
    out[0xf9] = (char)((unsigned short)u11 >> 8); out[0xf5] = (char)((unsigned short)u10 >> 8);
    out[0xf3] = u1; out[0xf2] = u2; out[0xf1] = (char)((unsigned short)u9 >> 8);
    out[0xf8] = (char)u11; out[0xfb] = u5; out[0xf4] = (char)u10; out[0xfa] = u6;
    out[0xf7] = u3; out[0xf6] = u4; out[0xfc] = (char)u12; out[0xff] = u7; out[0xfe] = u8;
}

/* FUN_00653490 @ 0x00653490  (est. sk_vas_translate)
 * Ghidra: undefined8 FUN_00653490(long param_1, ulong param_2, long param_3)
 * Page-table translation walk: given a vspace (param_1) with a 4K frame-mask table,
 * maps the contiguous region at param_2 (must be 16K-aligned) through the frame table,
 * following indirect/leaf entries (with __data slide) and returning 1 if any entry was
 * resolved, else 0. Handles both physical and indirect (pointer) descriptors.
 * Confidence: high (verified vs decompile 2026-08-12; FIXED loop-bound clobber:
 *   bound uVar1 given its own var, no longer aliased by inner-loop mask=*q) */
static unsigned long sk_vas_translate(long vas, unsigned long addr, long out_base)
{
    unsigned long i, slot, mask, mask2, stride, bound;
    long base;
    unsigned short *idx;
    unsigned short count, total;
    short kind;
    unsigned long *p, *q, *np;
    unsigned char *data;
    int lshift;

    if (vas != 0) {
        if ((addr & 0x3fff) != 0) {
            SoftwareBreakpoint(1, 0x653670);
        }
        if (addr < 0xffffffffffffc000) {
            mask2 = 0;
            bound = addr + 0x4000;      /* uVar1: loop bound, never modified */
            base = *(long *)(vas + 8);
            data = __data;
            if (_DAT_006bb920 == 0) {
                data = 0;
            }
            count = (unsigned long)*(unsigned short *)(vas + 4);
            total = *(unsigned short *)(vas + 0x14);
            base = addr + count;
            i = 0;
            do {
                slot = 0;
                if (count != 0) {
                    slot = (addr - (long)(data + base)) / count;
                }
                if (total <= slot) {
                    return mask2;
                }
                idx = (unsigned short *)(vas + 0x16 + slot * 2);
                if (idx + 1 < idx || (unsigned short *)(vas + 0x16 + (unsigned long)total * 2) < idx + 1) {
                    SoftwareBreakpoint(0x5519, 0x65366c);
                }
                slot = (unsigned long)*idx;
                if (slot != 0xffff) {
                    kind = *(short *)(vas + 6);
                    if (kind != 0xc && kind != 7) {
                        SoftwareBreakpoint(1, 0x653670);
                    }
                    p = (unsigned long *)(i + out_base);
                    q = (unsigned long *)((long)p + slot);
                    if (q != 0) {
                        lshift = 2;
                        if (kind != 7) {
                            lshift = 3;
                        }
                        do {
                            mask = *q;
                            mask2 = mask >> 0x33 & 0x7ff;
                            stride = mask2 << lshift;
                            if (mask2 == 0) {
                                np = 0;
                                if (-1 < (long)mask) goto have_ptr;
                                np = (unsigned long *)data + (mask & 0xffffffff);
                            } else {
                                np = (unsigned long *)((long)p + (slot & 0xffff) + stride);
                                if (np != 0 &&
                                    (np < p || (unsigned long *)((long)p + count) < np + 1 ||
                                     np + 1 < np)) {
                                    SoftwareBreakpoint(0x5519, 0x65366c);
                                }
                                if ((long)mask < 0) {
                                    np = (unsigned long *)data + (mask & 0xffffffff);
                                } else {
have_ptr:
                                    np = (unsigned long *)data + (mask & 0x7ffffffffff | (mask >> 0x2b) << 0x38);
                                }
                            }
                            slot = (unsigned long)(unsigned int)((int)slot + (int)stride);
                            *q = (unsigned long)np;
                            q = np;
                        } while (np != 0);
                    }
                    mask2 = 1;
                }
                addr = i + base;
                i = i + count;
                if (bound <= addr) {
                    return mask2;
                }
            } while (1);
        }
    }
    return 0;
}

/* FUN_00653670 @ 0x00653670  (est. sk_vas_any_mapped)
 * Ghidra: byte FUN_00653670(long param_1, ulong param_2)
 * Returns 1 if any frame in the 16K-aligned region at param_2 within vspace param_1 is
 * present (frame-table entry != -1), else 0.
 * Confidence: medium */
static unsigned char sk_vas_any_mapped(long vas, unsigned long addr)
{
    unsigned char *data;
    unsigned long count, slot, end;
    short *e;
    unsigned char present;
    unsigned long step;

    if (vas != 0) {
        if ((addr & 0x3fff) != 0) {
            SoftwareBreakpoint(1, 0x653718);
        }
        if (addr < 0xffffffffffffc000) {
            present = 0;
            end = addr + 0x4000;
            data = __data;
            if (_DAT_006bb920 == 0) {
                data = 0;
            }
            count = (unsigned long)*(unsigned short *)(vas + 4);
            do {
                slot = 0;
                if (count != 0) {
                    slot = ((-(long)data - *(long *)(vas + 8)) + addr) / count;
                }
                if (*(unsigned short *)(vas + 0x14) <= slot) {
                    return present;
                }
                e = (short *)(vas + 0x16 + slot * 2);
                if (e + 1 < e ||
                    (short *)(vas + 0x16 + (unsigned long)*(unsigned short *)(vas + 0x14) * 2) < e + 1) {
                    SoftwareBreakpoint(0x5519, 0x653714);
                }
                present = (*e != -1) | present;
                addr = addr + count;
            } while (addr < end);
            return present;
        }
    }
    return 0;
}

/* FUN_00653718 @ 0x00653718  (est. sk_vas_region_find)
 * Ghidra: ulong FUN_00653718(undefined *param_1, ulong param_2)
 * Searches the global object store for a vspace region whose backing block matches
 * param_1; returns the region descriptor if found and its size covers param_2.
 * Confidence: medium */
static unsigned long sk_vas_region_find(unsigned char *block, unsigned long size)
{
    unsigned int *iter, *limit, *e;
    unsigned long i, count, base, end, off;
    unsigned char *data;
    long *reg;
    unsigned long word;

    if (_DAT_006bb928 != 0 && (count = (unsigned long)*_DAT_006bb930, *_DAT_006bb930 != 0)) {
        iter = _DAT_006bb930 + 1;
        limit = iter + count;
        base = _DAT_006bb948 + _DAT_006bb950;
        data = __data;
        if (_DAT_006bb920 == 0) {
            data = 0;
        }
        do {
            if (limit < iter + 1 || iter + 1 < iter) {
                SoftwareBreakpoint(0x5519, 0x653808);
            }
            word = *iter;
            if (word != 0) {
                off = _DAT_006bb948 + *(unsigned int *)(_DAT_006bb928 + 4) + (unsigned long)word;
                if (off != 0 &&
                    ((end = off + 0x18,
                     (((end < off || off < _DAT_006bb948) || base < end) ||
                      base <= off + 0x16) &&
                      (((end < off || off < _DAT_006bb948) || base < end) || off + 0x16 != base) ||
                     ((unsigned long)((long)((_DAT_006bb950 -
                                             ((unsigned long)word + (unsigned long)*(unsigned int *)(_DAT_006bb928 + 4))) + -0x16) >> 1) <
                      (unsigned long)*(unsigned short *)(off + 0x14))))) {
                    SoftwareBreakpoint(0x5519, 0x653808);
                }
                if (data + *(long *)(off + 8) == block) {
                    if ((unsigned long)*(unsigned short *)(off + 0x14) *
                        (unsigned long)*(unsigned short *)(off + 4) <= size) {
                        return off;
                    }
                    SoftwareBreakpoint(1, 0x653804);
                }
            }
            iter++;
            count--;
        } while (count != 0);
    }
    return 0;
}

/* FUN_00653808 @ 0x00653808  (est. sk_vas_store_init)
 * Ghidra: void FUN_00653808(uint *param_1, ulong param_2)
 * Initializes the global vspace object store from a descriptor table at param_1 with
 * total size param_2 (must be >= 0x1c). Registers the store window globals, then for
 * each object entry wires its backing pages via sk_vas_translate unless the global
 * object-store mode flags (DAT_006fec90/91/92) select the deferred software path.
 * Confidence: medium */
static void sk_vas_store_init(unsigned int *table, unsigned long size)
{
    unsigned int *iter, *limit, *entry, *e;
    unsigned long i, count, word, total;
    unsigned char *block;
    unsigned long base, slide;
    long *reg;
    unsigned long *slotp;
    unsigned short kind;
    unsigned long x1, x2;

    if (size < 0x1c) {
        SoftwareBreakpoint(1, 0x653a8c);
    }
    limit = (unsigned int *)((long)table + size);
    iter = (unsigned int *)((long)table + (unsigned long)table[1]);
    if (iter == 0) {
        count = 0;
    } else if ((iter + 1 < iter || iter < table) || limit < iter + 1 ||
               (count = (unsigned long)*iter, (unsigned long)((long)((size - table[1]) + -4) >> 2) < count)) {
        SoftwareBreakpoint(0x5519, 0x653878);
    }
    _DAT_006bb920 = 1;
    _DAT_006bb928 = (unsigned char *)table;
    _DAT_006bb930 = iter;
    _DAT_006bb948 = (unsigned long)table;
    _DAT_006bb950 = size;
    x1 = sk_object_lookup((unsigned long)__data, 0x6a53cc);
    x2 = sk_object_lookup((unsigned long)__data, 0x6a53d3);
    if ((int)count != 0) {
        i = 0;
        entry = iter + 1;
        do {
            e = entry + i;
            if ((e < entry || e + 1 < e) || entry + *iter < e + 1) {
                SoftwareBreakpoint(0x5519, 0x653878);
            }
            word = *e;
            if (word != 0) {
                e = (unsigned int *)((long)table + (unsigned long)word + (unsigned long)table[1]);
                if (e != 0 &&
                    ((e + 6 < e ||
                      ((unsigned int *)((long)e + 0x16U) < e + 6) ||
                      ((unsigned int *)((long)e + (unsigned long)(unsigned short)e[5] * 2 + 0x16) < e + 6)))) {
                    SoftwareBreakpoint(0x5519, 0x653878);
                }
                block = __data + *(long *)(e + 2);
                if (_DAT_006fec90 == 1) {
                    if ((x1 == 0) ||
                        (*(unsigned long *)(x1 + 0x20) <= (unsigned long)((long)block - (slide + *(long *)(x1 + 0x18))))) {
                        if ((x2 == 0) ||
                            (*(unsigned long *)(x2 + 0x20) <=
                             (unsigned long)((long)block - (slide + *(long *)(x2 + 0x18))))) {
                            goto sw_path;
                        }
                        slotp = &_DAT_006bb940;
                    } else {
                        slotp = &_DAT_006bb938;
                    }
                    *slotp = (unsigned long)e;
                } else {
sw_path:
                    if ((short)e[5] != 0) {
                        i = 0;
                        do {
                            sk_vas_translate((long)e, (unsigned long)block, (long)block);
                            i++;
                            block = block + 0x4000;
                        } while (i < (unsigned short)e[5]);
                    }
                }
            }
            i++;
        } while (i != count);
    }
}

/* FUN_00653a8c @ 0x00653a8c  (est. sk_vas_store_enable)
 * Ghidra: void FUN_00653a8c(long param_1)
 * Enables the global vspace store: verifies the machine/feature registers (DAT_0064c020
 * == 0x19, DAT_0064c058/5c == 5), records the image slide (__data - DAT_0064c038) and the
 * software-path flag (param_1), then calls sk_vas_store_init.
 * Confidence: medium */
static void sk_vas_store_enable(long sw_flag)
{
    if ((_DAT_0064c020 == 0x19) && (_DAT_0064c058 == 5) && (_DAT_0064c05c == 5)) {
        _DAT_006fec88 = (long)__data - _DAT_0064c038;
        _DAT_006fec90 = sw_flag != 0;
        _DAT_006fec91 = 0;
        _DAT_006fec92 = 1;
        sk_vas_store_init(0, 0);
        return;
    }
    SoftwareBreakpoint(1, 0x653b74);
}

/* FUN_00653b74 @ 0x00653b74  (est. sk_vas_store_count)
 * Ghidra: void FUN_00653b74(void)
 * If the software store mode is active, returns the object-store count; else reports
 * a fatal error via FUN_00666298(0x6a5a53,...).
 * Confidence: medium */
static void sk_vas_store_count(void)
{
    unsigned long out;

    if (_DAT_006fec92 == 1) {
        sk_vas_region_find(0, 0);     /* FUN_00653718 returns count via store */
        return;
    }
    out = 0;
    /* FUN_00666298(0x6a5a53,&out) — report store size */
}

/* FUN_00653bb8 @ 0x00653bb8  (est. sk_vas_present)
 * Ghidra: ulong FUN_00653bb8(long param_1, ulong param_2)
 * Returns 1 if the frame covering virtual address param_2 in vspace param_1 is present;
 * uses the software store path when enabled, else walks the inline frame table.
 * Confidence: medium */
static unsigned long sk_vas_present(long vas, unsigned long addr)
{
    short *base_e, *end_e, *e;
    unsigned long base_addr;

    if (_DAT_006fec92 == 1) {
        return sk_vas_any_mapped(vas, addr);
    }
    base_e = (short *)(vas + 0x18);
    end_e = (short *)(vas + (((unsigned long)*(unsigned char *)(vas + 0x16) << 2) |
                             ((unsigned long)*(unsigned char *)(vas + 0x17) << 10)) +
                      (unsigned long)*(unsigned short *)(vas + 0x14) * 2 + 0x18);
    if (base_e <= end_e) {
        base_addr = (((unsigned long)*(unsigned char *)(vas + 0xe) << 0x10) |
                     ((unsigned long)*(unsigned char *)(vas + 0xf) << 0x18) |
                     (unsigned long)*(unsigned short *)(vas + 0xc) |
                     (((unsigned long)((unsigned int)*(unsigned char *)(vas + 0x12) << 0x10) |
                       ((unsigned int)*(unsigned char *)(vas + 0x13) << 0x18) |
                       (unsigned int)*(unsigned short *)(vas + 0x10)) << 0x20)) + _DAT_006fec88;
        if (addr < base_addr || base_addr + (unsigned long)*(unsigned short *)(vas + 0x14) * 0x4000 <= addr) {
            return 0;
        }
        e = base_e + (addr - base_addr >> 0xe);
        if ((base_e <= e && e + 1 <= end_e) && e <= e + 1) {
            return (unsigned long)(*e != -1);
        }
    }
    SoftwareBreakpoint(0x5519, 0x653c98);
}

/* FUN_00653c98 @ 0x00653c98  (est. sk_vas_lookup)
 * Ghidra: undefined8 FUN_00653c98(long param_1, ulong param_2, long param_3)
 * Full vspace page-table lookup: resolves the frame descriptor for address param_2,
 * walking 16K-granule entries. Handles 0xfffe (indirect entry list) and 0xffff
 * (unmapped) entries, calling sk_vas_walk_commit to install the resolved block at
 * param_3. When the software store path is active delegates to sk_vas_translate.
 * Confidence: medium */
static unsigned long sk_vas_lookup(long vas, unsigned long addr, long out_base)
{
    unsigned short *p1, *p2, *p3, *p4, *p5;
    unsigned long w, end, off, v;
    unsigned short u8;
    int i;
    unsigned short *base_e, *end_e, *e;
    unsigned long base_addr;

    if (_DAT_006fec92 == 1) {
        v = sk_vas_translate(vas, addr, out_base);
        if ((v & 1) != 0) {
            return 1;
        }
        sk_obj_release5();
    }
    base_e = (unsigned short *)(vas + 0x18);
    end_e = (unsigned short *)(vas + (unsigned long)(unsigned int)*(unsigned short *)(vas + 0x16) * 4 +
                               (unsigned long)*(unsigned short *)(vas + 0x14) * 2 + 0x18);
    if (base_e <= end_e) {
        base_addr = ((unsigned long)*(unsigned char *)(vas + 0xe) << 0x10) |
                    ((unsigned long)*(unsigned char *)(vas + 0xf) << 0x18) |
                    (unsigned long)*(unsigned short *)(vas + 0xc) |
                    (((unsigned long)((unsigned int)*(unsigned char *)(vas + 0x12) << 0x10) |
                      ((unsigned int)*(unsigned char *)(vas + 0x13) << 0x18) |
                      (unsigned int)*(unsigned short *)(vas + 0x10)) << 0x20);
        end = base_addr + _DAT_006fec88;
        if (addr < end ||
            _DAT_006fec88 + (unsigned long)*(unsigned short *)(vas + 0x14) * 0x4000 + base_addr <= addr) {
            goto fault_path;
        }
        off = addr - end >> 0xe;
        e = base_e + off;
        if ((base_e <= e && e + 1 <= end_e) && e <= e + 1) {
            u8 = *e;
            if (u8 == 0xfffe) {
                if (*(unsigned short *)(vas + 0x16) != 0) {
                    for (i = 0; i < (unsigned int)*(unsigned short *)(vas + 0x16); i++) {
                        p1 = (unsigned short *)(vas + i * 4 + (unsigned long)*(unsigned short *)(vas + 0x14) * 2 + 0x18);
                        p2 = (unsigned short *)(vas + i * 4 + (unsigned long)*(unsigned short *)(vas + 0x14) * 2 + 0x1a);
                        p3 = (unsigned short *)(vas + i * 4 + (unsigned long)*(unsigned short *)(vas + 0x14) * 2 + 0x1c);
                        if (((((base_e < p1) || end_e < p2) || p2 < p1) || end_e <= p3) &&
                            ((((base_e < p1) || end_e < p2) || p2 < p1) || p3 != end_e ||
                             p3 <= p2) &&
                            ((((base_e < p1) || end_e < p2) || p2 < p1) || end_e <= p3) &&
                            ((((base_e < p1) || end_e < p2) || p2 < p1) || p3 != end_e ||
                             p2 != p3)) {
                            goto fault_path;
                        }
                        if (off == *p1) {
                            sk_vas_walk_commit(out_base + (unsigned long)*p2, addr & 0xffffffffffffc000,
                                               *(unsigned short *)(vas + 2), (long)__data - _DAT_006fec88);
                        }
                    }
                }
            } else {
                if (u8 == 0xffff) {
                    goto fault_path;
                }
                sk_vas_walk_commit(out_base + (unsigned long)u8, addr & 0xffffffffffffc000,
                                   *(unsigned short *)(vas + 2), (long)__data - _DAT_006fec88);
            }
            return 1;
        }
    }
fault_path:
    sk_obj_release5();
    /* software fallback path (0x653ea0): run the deferred fault handler */
    return 0;
}

/* FUN_0065403c @ 0x0065403c  (est. sk_vspace_teardown)
 * Ghidra: void FUN_0065403c(long param_1)
 * Vspace teardown path. If param_1 (deferred/async) is zero, performs the synchronous
 * teardown: resets per-CPU flags, tears down the object store (FUN_006557e0 +
 * FUN_006541d4), unmaps the page-table cache, schedules, and finally issues a
 * CallSupervisor(0) to hand control back. Non-zero takes a soft path.
 * Confidence: medium */
static void sk_vspace_teardown(long async)
{
    int rc;
    unsigned long cpu;
    unsigned char *m;

    cpu = (unsigned long)sk_bucket_lookup(0x6fc580, 2, 2);
    sk_rt_clr_entry(*(unsigned char *)(cpu + 0xd8) & 1);   /* FUN_006557e0 */
    sk_notif_broadcast(async != 0, 1);
    sk_cache_flush(0x6bb9c0, (unsigned long)&_DAT_006fb9c0);
    sk_notif_broadcast(async != 0, 0);
    if (async == 0 && (rc = sk_sched_init(), rc != 0)) {
        rc = sk_sched_pin(0x40000, (unsigned long)&_DAT_00654240, cpu);
    } else {
        sk_rt_disable(cpu);
        rc = sk_mem_reclaim();
    }
    if (rc == 0) {
        sk_sys_wait(0);
        sk_flush_soft();
        if (async != 0) {
            return;
        }
        sk_sys_after();
        sk_rt_write(0x6a5ac4, 0, 0);
        rc = sk_sched_ready(1, 2);
        if (rc == 1) {
            sk_sched_switch();
        }
        m = (unsigned char *)tpidrro_el0;
        m[1] = 0; m[0] = 0; m[4] = 0; m[2] = 0; m[5] = 0; m[3] = 0; m[6] = 0; m[7] = 0;
        CallSupervisor(0);
        m[0] = 0; m[7] = 0; m[6] = 0; m[5] = 0; m[4] = 0; m[3] = 0; m[2] = 0; m[1] = 0;
        sk_fatal_6a5afd();
    }
    sk_fatal_6a5aab();
}

/* FUN_006541d4 @ 0x006541d4  (est. sk_notif_broadcast)
 * Ghidra: void FUN_006541d4(int param_1, undefined8 param_2)
 * Broadcasts a notification: sends the "plat" tag, and if a pending syscall exists
 * dispatches the 0xb notifications with param_2 as argument; otherwise, when param_1
 * is set, sends the "root" tag.
 * Confidence: medium */
static void sk_notif_broadcast(int want_root, unsigned long arg)
{
    sk_send_msg(0x706c6174, 0);              /* "plat" */
    if (sk_flush_soft2() != 0) {
        sk_notif_dispatch_type_b(arg);
        return;
    }
    if (want_root != 0) {
        sk_send_msg(0x726f6f74, arg);        /* "root" */
    }
}

/* FUN_00654250 @ 0x00654250  (est. sk_vspace_teardown_fast)
 * Ghidra: void FUN_00654250(void)
 * Fast vspace teardown: disables the runtime context and reclaims memory.
 * Confidence: medium */
static void sk_vspace_teardown_fast(void)
{
    sk_rt_disable(0);
    sk_mem_reclaim();
}

/* FUN_0065426c @ 0x0065426c  (est. sk_rt_disable_entry)
 * Ghidra: void FUN_0065426c(void)
 * Disables the runtime/context: writes the "0x6a5baf" state tag.
 * Confidence: medium */
static void sk_rt_disable_entry(void)
{
    sk_rt_disable(0x6a5baf);
}

/* FUN_00654278 @ 0x00654278  (est. sk_cur_slot)
 * Ghidra: long FUN_00654278(void)
 * Resolves the current thread's syscall slot: prefers the live context (FUN_0066ad54),
 * then the saved one, then derives the slot id from the error code (1/6 -> 3, 4 -> 2).
 * Confidence: medium */
static long sk_cur_slot(void)
{
    long s;
    unsigned long code;

    s = sk_cur_magic();
    if (s != 0) {
        return s;
    }
    s = sk_cur_magic2();
    if (s != 0) {
        s = sk_obj_release(s);
        return s;
    }
    code = sk_cur_magic3();
    switch ((int)code) {
    case 1:
    case 6:
        return sk_sched_slot(3);
    case 4:
        return sk_sched_slot(2);
    default:
        return -1;
    }
}

/* FUN_0065427c @ 0x0065427c  (est. sk_cur_slot2)
 * Ghidra: long FUN_0065427c(void)
 * Same as sk_cur_slot (duplicate helper).
 * Confidence: medium */
static long sk_cur_slot2(void)
{
    long s;
    unsigned long code;

    s = sk_cur_magic();
    if (s != 0) {
        return s;
    }
    s = sk_cur_magic2();
    if (s != 0) {
        s = sk_obj_release(s);
        return s;
    }
    code = sk_cur_magic3();
    switch ((int)code) {
    case 1:
    case 6:
        return sk_sched_slot(3);
    case 4:
        return sk_sched_slot(2);
    default:
        return -1;
    }
}

/* FUN_006542a4 @ 0x006542a4  (est. sk_cur_slot3)
 * Ghidra: undefined8 FUN_006542a4(void)
 * Same as sk_cur_slot but without the live/saved context fast paths.
 * Confidence: medium */
static unsigned long sk_cur_slot3(void)
{
    unsigned long code;

    code = sk_cur_magic3();
    switch ((int)code) {
    case 1:
    case 6:
        return sk_sched_slot(3);
    case 4:
        return sk_sched_slot(2);
    default:
        return 0xffffffffffffffff;
    }
}

/* FUN_006542b0 @ 0x006542b0  (est. sk_slot_of_code)
 * Ghidra: undefined8 FUN_006542b0(undefined8 param_1)
 * Maps an error code to its syscall slot id (1/6 -> 3, 4 -> 2, else -1).
 * Confidence: medium */
static unsigned long sk_slot_of_code(unsigned long code)
{
    switch ((int)code) {
    case 1:
    case 6:
        return sk_sched_slot(3);
    case 4:
        return sk_sched_slot(2);
    default:
        return 0xffffffffffffffff;
    }
}

/* FUN_006542e0 @ 0x006542e0  (est. sk_object_store_relocate)
 * Ghidra: void FUN_006542e0(ulong param_1)
 * Relocates the global object store: acquires the store lock, records the new base
 * (param_1), then walks every object-store bucket (0x6fc008) and, for each entry with
 * a type-0xb tag, updates the per-CPU object table slot at 0x6fb9c8+0x2a0.
 * Confidence: medium */
static void sk_object_store_relocate(unsigned long new_base)
{
    unsigned short *bucket, *e;
    unsigned long i, cnt;
    unsigned long tag;
    unsigned long reg;

    if (new_base <= new_base + 0x4000) {
        if (sk_bucket_acquire(4, 4) == 0) {
            _DAT_006b4330 = new_base;
            sk_bucket_iter(0, 0, 0);
            _DAT_006b4350 = 0x6fb9d0;
            sk_bucket_iter(0, 0, 0);
            for (bucket = (unsigned short *)sk_bucket_lookup(0x6fc008, 2, 4);
                 bucket != (unsigned short *)0xffffffffffffffff;
                 bucket = (unsigned short *)
                   ((unsigned long)(unsigned char)bucket[5] << 0x10 |
                    ((unsigned long)*(unsigned char *)((long)bucket + 0xb) << 0x18) |
                    (unsigned long)bucket[4] |
                    ((unsigned long)((unsigned int)(unsigned char)bucket[7] << 0x10 |
                                     (unsigned int)*(unsigned char *)((long)bucket + 0xf) << 0x18 |
                                     (unsigned int)bucket[6]) << 0x20))) {
                if (bucket + 0x2000 < bucket) {
                    SoftwareBreakpoint(0x5519, 0x654528);
                }
                if ((((char)bucket[1] != 0 || *(char *)((long)bucket + 3) != 0) || bucket[0] != 0) ||
                    (((char)bucket[3] != 0 || *(char *)((long)bucket + 7) != 0) || bucket[2] != 0)) {
                    cnt = ((unsigned long)(unsigned char)bucket[1] << 0x10) |
                          ((unsigned long)*(unsigned char *)((long)bucket + 3) << 0x18) |
                          (unsigned long)bucket[0] |
                          ((unsigned long)((unsigned int)(unsigned char)bucket[3] << 0x10 |
                                           (unsigned int)*(unsigned char *)((long)bucket + 7) << 0x18 |
                                           (unsigned int)bucket[2]) << 0x20);
                    i = 0;
                    e = bucket + 0x10;
                    do {
                        if (e != 0 && ((e < bucket + 0x10 || (bucket + 0x2000 < e + 0x10)) ||
                                       e + 0x10 < e)) {
                            SoftwareBreakpoint(0x5519, 0x654528);
                        }
                        tag = *(unsigned int *)(e + 2) |
                              ((unsigned long)*(unsigned char *)((long)e + 7) << 0x20);
                        if (*(char *)((long)e + 7) == 0xb) {
                            if (e + 0x10 < e) {
                                SoftwareBreakpoint(0x5519, 0x654528);
                            }
                            reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
                            *(unsigned long *)(reg + 0x2a0) =
                                ((unsigned long)(unsigned char)e[1] << 0x10) |
                                ((unsigned long)*(unsigned char *)((long)e + 3) << 0x18) |
                                (unsigned long)e[0] | (tag << 0x20);
                        }
                        i++;
                        e = e + 0x10;
                    } while (i < cnt);
                }
            }
        }
        return;
    }
    SoftwareBreakpoint(0x5519, 0x654528);
}

/* FUN_00654528 @ 0x00654528  (est. sk_deref_obj)
 * Ghidra: undefined8 FUN_00654528(undefined8 *param_1)
 * Returns the first word of the given object.
 * Confidence: high */
static unsigned long sk_deref_obj(unsigned long *obj)
{
    return *obj;
}

/* FUN_00654530 @ 0x00654530  (est. sk_object_store_build)
 * Ghidra: void FUN_00654530(void)
 * Builds the global object store from the kernel-object descriptor buckets. Reads the
 * store window globals (FUN_00656868/6a14/6adc), walks the 0x6fc008 object buckets and
 * the 0x6fb9c8 per-CPU table, and dispatches each entry by its 16-bit tag (0..0x11):
 *  - 4: record vspace base/size window
 *  - 6/7/0xb: store region slots
 *  - 0xc/0xd/0xe: capacity high-water marks
 *  - 0x11: call sk_vas_store_count helper (FUN_0065505c)
 *  - 1/2/3/5/8/9/0xf/0x10: type-matched slots via FUN_0065505c / FUN_00656af8
 * Ends by panicking if the store state is invalid.
 * Confidence: medium */
static void sk_object_store_build(void)
{
    unsigned short *bucket, *e, *p;
    unsigned long i, cnt, word, addr, cap;
    unsigned long t1, t2, t3;
    unsigned long reg;
    unsigned long *slotp;
    unsigned char tag;
    unsigned long n;
    unsigned long u16, u17;

    t1 = sk_store_type1();          /* FUN_00656868 */
    t2 = sk_store_type2();          /* FUN_00656a14 */
    t3 = sk_store_type3();          /* FUN_00656adc */
    bucket = (unsigned short *)sk_bucket_lookup(0x6fc008, 2, 4);
    reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
    if ((*(unsigned char *)(reg + 0x630) & 1) != 0) {
        return;
    }
    for (;;) {
        if (bucket == (unsigned short *)0xffffffffffffffff) {
            if (*(char *)(reg + 0x278) != 0) {
                *(unsigned char *)(reg + 0x279) = 0;
                sk_fatal_6a5e5a();
            }
            if (*(char *)(reg + 0x27a) == 1) {
                sk_fatal_6a5cea();
            }
            addr = *(unsigned long *)(reg + 0x240);
            if (*(unsigned long *)(reg + 0x238) == addr) {
                sk_obj_release2();
            } else {
                word = *(unsigned long *)(reg + 0x250);
                if (*(unsigned long *)(reg + 0x238) == *(unsigned long *)(reg + 0x248)) {
                    if (addr < word) {
                        sk_fatal_6a5da6();
                    }
                    if (0x3ff < addr - word) {
                        *(unsigned long *)(reg + 600) = word;
                        cap = (addr - word & 0xffffffffffffffc0) + word;
                        reg = (long)(reg + 0x260) - 0x400;
                        *(long *)(reg + 0x260) = (long)reg;
                        *(long *)(reg + 0x268) = (long)reg;
                        *(long *)(reg + 0x270) = cap;
                        *(unsigned char *)(reg + 0x278) = 1;
                        *(unsigned char *)(reg + 0x630) = 1;
                        return;
                    }
                    sk_fatal_6a5de8();
                }
            }
            sk_fatal_6a5d4e();
        }
        if (bucket + 0x2000 < bucket) {
            break;
        }
        if ((((unsigned char)bucket[1] != 0 || *(unsigned char *)((long)bucket + 3) != 0) || bucket[0] != 0) ||
            (((unsigned char)bucket[3] != 0 || *(unsigned char *)((long)bucket + 7) != 0) || bucket[2] != 0)) {
            cnt = ((unsigned long)(unsigned char)bucket[1] << 0x10) |
                  ((unsigned long)*(unsigned char *)((long)bucket + 3) << 0x18) |
                  (unsigned long)bucket[0] |
                  ((unsigned long)((unsigned int)(unsigned char)bucket[3] << 0x10 |
                                   (unsigned int)*(unsigned char *)((long)bucket + 7) << 0x18 |
                                   (unsigned int)bucket[2]) << 0x20);
            i = 0;
            e = bucket + 0x10;
            do {
                if (e != 0 && ((e < bucket + 0x10 || (bucket + 0x2000 < e + 0x10)) ||
                               e + 0x10 < e)) {
                    goto invalid_store;
                }
                tag = *(unsigned char *)((long)e + 7);
                word = ((unsigned long)(unsigned char)e[1] << 0x10) |
                       ((unsigned long)*(unsigned char *)((long)e + 3) << 0x18) |
                       (unsigned long)e[0] | (*(unsigned int *)(e + 2) << 0x20);
                if (*(unsigned long *)(reg + 0x248) == 0 && *(long *)(reg + 0x250) == 0) {
                    *(unsigned long *)(reg + 0x248) = word;
record_next:
                    *(unsigned long *)(reg + 0x250) = word + 0x40;
                } else {
                    if (word < *(unsigned long *)(reg + 0x248)) {
                        *(unsigned long *)(reg + 0x248) = word;
                    }
                    if (*(unsigned long *)(reg + 0x250) < word + 0x40) {
                        goto record_next;
                    }
                }
                p = e + 0x10;
                if (tag < 0x12) {
                    switch (tag) {
                    case 1: case 2: case 3: case 5: case 8: case 9: case 0xf: case 0x10:
                        goto type_match;
                    case 4:
                        if (e <= p) {
                            sk_vas_store_build_b((long)e);   /* FUN_0065505c */
                        }
                        goto invalid_store;
                    case 6:
                        if (p < e) goto invalid_store;
                        reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
                        *(unsigned long *)(reg + 0x288) = word;
                        break;
                    case 7:
                        if (p < e) goto invalid_store;
                        reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
                        *(unsigned long *)(reg + 0x290) = word;
                        break;
                    case 10:
                        if (p < e) goto invalid_store;
                        reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
                        slotp = (unsigned long *)(reg + 0x38) + _DAT_006fc010 * 2;
                        if ((slotp < (unsigned long *)(reg + 0x38)) ||
                            ((unsigned long *)(reg + 0x238) < slotp + 2) || slotp + 2 < slotp) {
                            goto invalid_store;
                        }
                        *slotp = word;
                        *(unsigned short *)(slotp + 1) = (unsigned short)e[8] |
                                                         (*(unsigned char *)((long)e + 0x11) << 8);
                        _DAT_006fc010 = _DAT_006fc010 + 1;
                        break;
                    case 0xb:
                        if (p < e) goto invalid_store;
                        reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
                        *(unsigned long *)(reg + 0x2a0) = word;
                        break;
                    case 0xc:
                        *(unsigned long *)(reg + 0x28) = word;
                        *(unsigned long *)(reg + 0x30) = 0;
                        break;
                    case 0xd:
                        addr = (((unsigned long)(unsigned char)e[9] << 0x10) |
                                ((unsigned long)*(unsigned char *)((long)e + 0x13) << 0x18) |
                                (unsigned long)e[8]) << 0xc |
                               ((unsigned long)(unsigned char)e[10] << 0x2c);
                        if (*(unsigned long *)(reg + 0x20) <= addr) {
                            *(unsigned long *)(reg + 0x18) = word;
                            *(unsigned long *)(reg + 0x20) = addr;
                        }
                        break;
                    case 0xe:
                        addr = (((unsigned long)(unsigned char)e[9] << 0x10) |
                                ((unsigned long)*(unsigned char *)((long)e + 0x13) << 0x18) |
                                (unsigned long)e[8]) << 0xc |
                               ((unsigned long)(unsigned char)e[10] << 0x2c);
                        if (*(unsigned long *)(reg + 0x10) <= addr) {
                            *(unsigned long *)(reg + 8) = word;
                            *(unsigned long *)(reg + 0x10) = addr;
                        }
                        break;
                    case 0x11:
                        if (p < e) goto invalid_store;
                        sk_vas_store_build_b((long)e);
                    }
                } else {
type_match:
                    if (t1 == tag) {
                        if (p < e) goto invalid_store;
                        reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
                        *(unsigned long *)(reg + 0x2a8) = word;
                    } else if (t2 == tag) {
                        if (p < e) goto invalid_store;
                        reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
                        *(unsigned long *)(reg + 0x298) = word;
                    } else if (t3 == tag) {
                        if (p < e) goto invalid_store;
                        sk_store_type3_hook((long)e);      /* FUN_00656af8 */
                        slotp = (unsigned long *)sk_store_type2_get();
                        if (slotp + 1 < slotp) goto invalid_store;
                        *slotp = ((unsigned long)(unsigned char)e[1] << 0x10) |
                                 ((unsigned long)*(unsigned char *)((long)e + 3) << 0x18) |
                                 (unsigned long)e[0] | (*(unsigned int *)(e + 2) << 0x20);
                    } else {
                        if (tag != 5) goto type_done;
                        if (p < e) goto invalid_store;
                        reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
                        n = *(long *)(reg + 0x628);
                        slotp = (unsigned long *)(reg + 0x2c8) + n * 3;
                        if (slotp < (unsigned long *)(reg + 0x2c8)) goto invalid_store;
                        if (((unsigned long *)(reg + 0x628) < slotp + 3) || slotp + 3 < slotp) {
                            goto invalid_store;
                        }
                        *slotp = word;
                        slotp[1] = *(unsigned int *)(e + 8);
                        if ((p < e + 0xc) || (e + 0xc < e)) goto invalid_store;
                        *(unsigned char *)(slotp + 2) = *(unsigned char *)(e + 0xc) & 1;
                        *(unsigned long *)(reg + 0x628) = n + 1;
                    }
                }
type_done:
                i++;
                e = e + 0x10;
            } while (i < cnt);
        }
        bucket = (unsigned short *)
            ((unsigned long)(unsigned char)bucket[5] << 0x10 |
             ((unsigned long)*(unsigned char *)((long)bucket + 0xb) << 0x18) |
             (unsigned long)bucket[4] |
             ((unsigned long)((unsigned int)(unsigned char)bucket[7] << 0x10 |
                              (unsigned int)*(unsigned char *)((long)bucket + 0xf) << 0x18 |
                              (unsigned int)bucket[6]) << 0x20));
    }
invalid_store:
    SoftwareBreakpoint(0x5519, 0x654bd0);
}

/* FUN_00654cc8 @ 0x00654cc8  (est. sk_store_type2_get)
 * Ghidra: undefined8 FUN_00654cc8(void)
 * Returns the per-CPU store's reply slot word at 0x2a0.
 * Confidence: medium */
static unsigned long sk_store_type2_get(void)
{
    unsigned long reg;

    reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
    return *(unsigned long *)(reg + 0x2a0);
}

/* FUN_00654cf4 @ 0x00654cf4  (est. sk_store_slot288)
 * Ghidra: undefined8 FUN_00654cf4(void)
 * Returns the per-CPU store's 0x288 slot word.
 * Confidence: medium */
static unsigned long sk_store_slot288(void)
{
    unsigned long reg;

    reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
    return *(unsigned long *)(reg + 0x288);
}

/* FUN_00654d20 @ 0x00654d20  (est. sk_store_slot2a8)
 * Ghidra: undefined8 FUN_00654d20(void)
 * Returns the per-CPU store's 0x2a8 slot word.
 * Confidence: medium */
static unsigned long sk_store_slot2a8(void)
{
    unsigned long reg;

    reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
    return *(unsigned long *)(reg + 0x2a8);
}

/* FUN_00654d4c @ 0x00654d4c  (est. sk_store_touch)
 * Ghidra: void FUN_00654d4c(void)
 * Touches the object-store bucket (0x6fc008); no-op wrapper.
 * Confidence: medium */
static void sk_store_touch(void)
{
    sk_bucket_lookup(0x6fc008, 2, 4);
}

/* FUN_00654d60 @ 0x00654d60  (est. sk_store_slot298)
 * Ghidra: undefined8 FUN_00654d60(long param_1)
 * Returns the per-CPU store's 0x298 slot word, or 0 if param_1 is non-zero.
 * Confidence: medium */
static unsigned long sk_store_slot298(long arg)
{
    unsigned long reg;

    if (arg != 0) {
        return 0;
    }
    reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
    return *(unsigned long *)(reg + 0x298);
}

/* FUN_00654d9c @ 0x00654d9c  (est. sk_store_slot_base)
 * Ghidra: ulong FUN_00654d9c(long param_1)
 * Returns a pointer into the per-CPU store given a slot selector: 1 -> +0x2b8,
 * 3 -> +0x2b0, 2 -> +0x2c0 (the current write cursor), else 0.
 * Confidence: medium */
static unsigned long sk_store_slot_base(long which)
{
    unsigned long off, base, u;

    if (which == 1) {
        off = 0x2b8;
    } else {
        if (which == 2) {
            base = sk_bucket_lookup(0x6fb9c8, 2, 5);
            u = base + 0x2c0;
            if (u == 0) {
                return 0;
            }
            if ((u <= base + 0x2c8) && (base + 0x2b0 <= u)) {
                return u;
            }
            SoftwareBreakpoint(0x5519, 0x654e08);
        }
        if (which != 3) {
            return 0;
        }
        off = 0x2b0;
    }
    return sk_bucket_lookup(0x6fb9c8, 2, 5) + off;
}

/* FUN_00654e38 @ 0x00654e38  (est. sk_vas_window_commit)
 * Ghidra: void FUN_00654e38(ulong *param_1, long *param_2, ulong *param_3)
 * Commits the current vspace window: validates the store state (0x278 == 1), advances
 * it to 2, and reports the window [base, cur, count] into the three out params. The
 * base must be 16K-aligned and the cursor within [base, end].
 * Confidence: medium */
static void sk_vas_window_commit(unsigned long *out_base, long *out_cur, unsigned long *out_count)
{
    unsigned long reg, base, end, cur;

    reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
    if (reg + 0x238 <= reg + 0x288) {
        if (*(char *)(reg + 0x278) != 1) {
            *(unsigned char *)(reg + 0x279) = 1;
            sk_fatal_6a5e5a();
        }
        *(unsigned char *)(reg + 0x278) = 2;
        base = *(unsigned long *)(reg + 0x238);
        end = *(unsigned long *)(reg + 0x240);
        if (((((unsigned int)base | (unsigned int)end) & 0x3fff) == 0) &&
            (end == *(unsigned long *)(reg + 0x270)) &&
            (base <= *(unsigned long *)(reg + 0x268) &&
             *(unsigned long *)(reg + 0x268) <= end)) {
            *out_base = base;
            cur = *(long *)(reg + 0x268);
            *out_cur = cur;
            *out_count = (unsigned long)(*(long *)(reg + 0x270) - cur) >> 6;
            return;
        }
        sk_obj_release3();
    }
    SoftwareBreakpoint(0x5519, 0x654efc);
}

/* FUN_00654f20 @ 0x00654f20  (est. sk_vas_window_release)
 * Ghidra: void FUN_00654f20(void)
 * Releases the committed vspace window: when the store state is 2, advances it to 3
 * and frees every page in the recorded range; otherwise reports a fatal store error.
 * Confidence: medium */
static void sk_vas_window_release(void)
{
    unsigned long reg, page;

    reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
    if (reg + 0x288 < reg + 0x238) {
        SoftwareBreakpoint(0x5519, 0x654fa4);
    }
    if (*(char *)(reg + 0x278) == 2) {
        *(unsigned char *)(reg + 0x278) = 3;
        for (page = *(unsigned long *)(reg + 600); page < *(unsigned long *)(reg + 0x260);
             page = page + 0x40) {
            sk_obj_release(page);
        }
        return;
    }
    *(unsigned char *)(reg + 0x279) = 2;
    sk_fatal_6a5e5a();
}

/* FUN_00654fc8 @ 0x00654fc8  (est. sk_vas_window_alloc)
 * Ghidra: ulong *FUN_00654fc8(void)
 * Allocates the next 64-byte slot from the current vspace window (state 1), advancing
 * the cursor; when the window is exhausted it extends the store high-water mark and
 * returns the store base. Otherwise reports a fatal store error.
 * Confidence: medium */
static unsigned long *sk_vas_window_alloc(void)
{
    unsigned long reg, base, addr;
    unsigned long *slot;

    reg = sk_bucket_lookup(0x6fb9c8, 2, 5);
    if (reg + 0x288 < reg + 0x238) {
        SoftwareBreakpoint(0x5519, 0x655034);
    }
    if (*(char *)(reg + 0x278) == 1) {
        slot = *(unsigned long **)(reg + 0x268);
        if (slot < *(unsigned long **)(reg + 0x270)) {
            *(unsigned long **)(reg + 0x268) = slot + 8;
            return slot;
        }
        reg = sk_obj_release4();
        addr = ((((unsigned long)*(unsigned char *)(reg + 0x12) << 0x10) |
                 ((unsigned long)*(unsigned char *)(reg + 0x13) << 0x18) |
                 (unsigned long)*(unsigned short *)(reg + 0x10)) << 0xc |
                ((unsigned long)*(unsigned char *)(reg + 0x14) << 0x2c)) + 0x4000;
        slot = (unsigned long *)sk_bucket_lookup(0x6fb9c8, 2, 5);
        if (*slot < addr) {
            *slot = addr;
        }
        return slot;
    }
    *(unsigned char *)(reg + 0x279) = 1;
    sk_fatal_6a5e5a();
    return 0;
}

/* FUN_0065505c @ 0x0065505c  (est. sk_vas_store_build_b)
 * Ghidra: void FUN_0065505c(long param_1)
 * Records a 16K-aligned address from a store descriptor (param_1+0x10) as the new
 * store high-water mark if it exceeds the current value.
 * Confidence: medium */
static void sk_vas_store_build_b(long desc)
{
    unsigned long addr;
    unsigned long *reg;

    addr = ((((unsigned long)*(unsigned char *)(desc + 0x12) << 0x10) |
             ((unsigned long)*(unsigned char *)(desc + 0x13) << 0x18) |
             (unsigned long)*(unsigned short *)(desc + 0x10)) << 0xc |
            ((unsigned long)*(unsigned char *)(desc + 0x14) << 0x2c)) + 0x4000;
    reg = (unsigned long *)sk_bucket_lookup(0x6fb9c8, 2, 5);
    if (*reg < addr) {
        *reg = addr;
    }
}

/* FUN_006550cc @ 0x006550cc  (est. sk_str_decode)
 * Ghidra: int FUN_006550cc(undefined8 param_1, ulong param_2, ulong param_3, undefined8 param_4)
 * Decodes a NUL-separated string list at param_2 of length param_3, counting the
 * entries (each separated by 0x0a/0x10 tokens). Returns the entry count or stops
 * early on a decoding fault.
 * Confidence: medium */
static int sk_str_decode(unsigned long out, unsigned long s, unsigned long len, unsigned long arg)
{
    int count, rc;
    unsigned long end, off, chunk;

    end = 0;
    off = len;
    if (sk_cur_magic2() == 0 || (off = sk_cur_magic2() - s, off <= len)) {
        count = 0;
        for (;;) {
            if (off == 0) {
                return count;
            }
            sk_strcpy_pad((void *)out, (void *)arg, 0);
            chunk = off;
            if (sk_cur_magic2() != 0) {
                chunk = sk_cur_magic2() - s;
            }
            if (len < chunk) {
                break;
            }
            end = sk_str_decode_adv(s, chunk, 1, arg);
            count = count + (int)end;
            if (end < chunk) {
                return count;
            }
            rc = sk_str_decode_token(10, arg);
            if (rc == -1) {
                return count;
            }
            end = s + chunk + 1;
            if ((s + len < end) ||
                (len = len - (chunk + 1), (s + chunk + 1) < s)) {
                break;
            }
        }
    }
    SoftwareBreakpoint(0x5519, 0x6551a8);
}

/* FUN_006551c4 @ 0x006551c4  (est. sk_obj_equal)
 * Ghidra: bool FUN_006551c4(long param_1, long param_2)
 * Returns whether two objects are identical.
 * Confidence: high */
static int sk_obj_equal(long a, long b)
{
    return a == b;
}

/* FUN_006551d0 @ 0x006551d0  (est. sk_page_alloc_zero)
 * Ghidra: undefined8 FUN_006551d0(ulong param_1)
 * Allocates a zeroed page at param_1 (16-byte size check), returns 0 on success.
 * Confidence: medium */
static unsigned long sk_page_alloc_zero(unsigned long addr)
{
    if (addr <= addr + 0x10) {
        sk_alloc_page(addr);
        return 0;
    }
    SoftwareBreakpoint(0x5519, 0x655200);
}

/* FUN_00655200 @ 0x00655200  (est. sk_page_alloc)
 * Ghidra: void FUN_00655200(ulong param_1)
 * Allocates a page at param_1.
 * Confidence: medium */
static void sk_page_alloc(unsigned long addr)
{
    if (addr <= addr + 0x10) {
        sk_alloc_page(addr);
        return;
    }
    SoftwareBreakpoint(0x5519, 0x655218);
}

/* FUN_00655218 @ 0x00655218  (est. sk_obj_init_zero)
 * Ghidra: undefined8 FUN_00655218(undefined8 *param_1)
 * Zeroes a two-word object at param_1.
 * Confidence: medium */
static unsigned long sk_obj_init_zero(unsigned long *obj)
{
    if (obj <= obj + 2) {
        obj[0] = 0;
        obj[1] = 0;
        return 0;
    }
    SoftwareBreakpoint(0x5519, 0x655234);
}

/* FUN_00655234 @ 0x00655234  (est. sk_page_alloc_check)
 * Ghidra: undefined4 FUN_00655234(ulong param_1, ulong param_2)
 * Checks two page ranges for allocatability; returns 4 (busy) if the allocator fails,
 * else 0.
 * Confidence: medium */
static unsigned int sk_page_alloc_check(unsigned long a, unsigned long b)
{
    int rc;
    unsigned int result;

    if ((a <= a + 0x10) && (b <= b + 0x10)) {
        rc = sk_alloc_page_chk();
        result = 0;
        if (rc == 0) {
            result = 4;
        }
        return result;
    }
    SoftwareBreakpoint(0x5519, 0x655274);
}

/* FUN_00655274 @ 0x00655274  (est. sk_obj_init_flags)
 * Ghidra: undefined8 FUN_00655274(undefined8 *param_1, uint param_2)
 * Zeroes a two-word object and, when bit 1 of param_2 is set, commits it as a
 * 0x100-byte page.
 * Confidence: medium */
static unsigned long sk_obj_init_flags(unsigned long *obj, unsigned int flags)
{
    if (obj <= obj + 2) {
        obj[0] = 0;
        obj[1] = 0;
        if ((flags >> 1 & 1) != 0) {
            sk_page_commit((unsigned long)obj, 0x100);
        }
        return 0;
    }
    SoftwareBreakpoint(0x5519, 0x6552b0);
}

/* FUN_006552b0 @ 0x006552b0  (est. sk_page_unwire_entry)
 * Ghidra: void FUN_006552b0(ulong param_1)
 * Unwires a page at param_1.
 * Confidence: medium */
static void sk_page_unwire_entry(unsigned long addr)
{
    if (addr <= addr + 0x10) {
        sk_page_unwire();
        return;
    }
    SoftwareBreakpoint(0x5519, 0x6552c4);
}

/* FUN_006552c4 @ 0x006552c4  (est. sk_page_unwire_check)
 * Ghidra: undefined4 FUN_006552c4(ulong param_1)
 * Checks that a page at param_1 can be unwired; returns 3 on failure.
 * Confidence: medium */
static unsigned int sk_page_unwire_check(unsigned long addr)
{
    int rc;
    unsigned int result;

    if (addr <= addr + 0x10) {
        rc = sk_page_unwire_chk();
        result = 0;
        if (rc == 0) {
            result = 3;
        }
        return result;
    }
    SoftwareBreakpoint(0x5519, 0x6552f8);
}

/* FUN_006552f8 @ 0x006552f8  (est. sk_page_destroy_entry)
 * Ghidra: undefined8 FUN_006552f8(ulong param_1)
 * Destroys a page at param_1.
 * Confidence: medium */
static unsigned long sk_page_destroy_entry(unsigned long addr)
{
    if (addr <= addr + 0x10) {
        sk_page_destroy();
        return 0;
    }
    SoftwareBreakpoint(0x5519, 0x655324);
}

/* FUN_0065558c @ 0x0065558c  (est. sk_notif_dispatch_all)
 * Ghidra: void FUN_0065558c(void)
 * Fatal notification-dispatch abort: checks the current object is live, reports the
 * abort with a '=' diagnostic (FUN_006631d8), releases the object if still live, then
 * panics.
 * Confidence: medium */
static void sk_notif_dispatch_all_panic(void)
{
    int live;
    unsigned long ctx;

    live = sk_rt_writel_ok(_DAT_006b4368, 0);
    ctx = sk_sys_wait(0);
    sk_sched_wake(0x6a5e80, 0x3d, _DAT_006b4368, ctx, 1, 0, 0, 0);
    if (live == 0) {
        sk_rt_writel2(_DAT_006b4368, 0);
    }
    sk_fatal_msg("notification dispatch abort");   /* FUN_0065c2f0(ctx,0x6a5e80) */
}

/* FUN_006555fc @ 0x006555fc  (est. sk_notif_dispatch_abort)
 * Ghidra: void FUN_006555fc(undefined8 param_1)
 * Reports and aborts notification dispatch (param_1 diagnostic), then panics.
 * Confidence: medium */
static void sk_notif_dispatch_abort(unsigned long arg)
{
    sk_rt_write(_DAT_006b4368, arg, 0);
    sk_notif_dispatch_all_panic();
}

/* FUN_0065562c @ 0x0065562c  (est. sk_ctx_restore)
 * Ghidra: void FUN_0065562c(undefined8 param_1, undefined8 param_2)
 * Restores the saved context and returns control.
 * Confidence: medium */
static void sk_ctx_restore(unsigned long a, unsigned long b)
{
    sk_ret_ctx_restore(0, a, b);    /* FUN_0065c310 noreturn */
}

/* FUN_0065564c @ 0x0065564c  (est. sk_prng_fill)
 * Ghidra: void FUN_0065564c(long param_1, ulong param_2)
 * Fills param_2 bytes at param_1 with PRNG output using the xorshift state pair
 * (_DAT_006feb88/_feb90), 8 bytes per step.
 * Confidence: medium */
static void sk_prng_fill(long dst, unsigned long n)
{
    unsigned long i, a, b, out;
    unsigned long canary = _DAT_006b5ed0;

    i = 0;
    for (;;) {
        if (n < i || (b = n - i, n < i || b == 0)) {
            if (_DAT_006b5ed0 == canary) {
                return;
            }
            sk_stack_check_fail();
        }
        a = _DAT_006feb88 * 5;
        out = _DAT_006feb88 * 0x280;
        _DAT_006feb90 = _DAT_006feb90 ^ _DAT_006feb88;
        _DAT_006feb88 = (_DAT_006feb88 >> 0x28 | _DAT_006feb88 << 0x18) ^
                        _DAT_006feb90 << 0x10 ^ _DAT_006feb90;
        _DAT_006feb90 = _DAT_006feb90 >> 0x1b | _DAT_006feb90 << 0x25;
        out = (a >> 0x39 | out) * 9;
        if (7 < b) {
            b = 8;
        }
        sk_memcpy((unsigned long)dst + i, (unsigned long)&out, b);
        if (dst + i + b < dst + i) {
            SoftwareBreakpoint(0x5519, 0x67cc14);
        }
        i = b + i;
    }
}

/* FUN_00655650 @ 0x00655650  (est. sk_cap_slot_lookup)
 * Ghidra: ulong FUN_00655650(ulong param_1)
 * Looks up a capability slot by address; on success tags the upper 16 bits with the
 * slot's bucket id (param_1+0x40 >> 16), else returns 0xffff000000000000.
 * Confidence: medium */
static unsigned long sk_cap_slot_lookup(unsigned long addr)
{
    unsigned long l, result;
    unsigned long inout = addr;

    l = sk_bucket_lookup_name(&inout, 0);
    if (l == 0) {
        result = 0xffff000000000000;
    } else {
        result = (unsigned long)*(unsigned short *)(l + 0x40) << 0x30;
    }
    return inout & 0xffffffffffff | result;
}

/* FUN_0065569c @ 0x0065569c  (est. sk_obj_dispatch_58)
 * Ghidra: void FUN_0065569c(long param_1)
 * Dispatches the object at param_1: if it is the current or alternate context and the
 * scheduler is live, wakes it; otherwise writes through its +0x58 vtable slot.
 * Confidence: medium */
static void sk_obj_dispatch_58(long obj)
{
    unsigned long ctx;
    int live;

    ctx = sk_sys_wait(0);
    if ((obj == _DAT_006b4368 || obj == _DAT_006b4380) &&
        (live = sk_sched_unpin(), live != 0)) {
        sk_sched_unpin2(ctx, *(unsigned long *)(obj + 0x58));
        return;
    }
    sk_rt_writel(*(unsigned long *)(obj + 0x58), 0);
}

/* FUN_00655708 @ 0x00655708  (est. sk_obj_live)
 * Ghidra: ulong FUN_00655708(long param_1)
 * Returns whether the object at param_1 is live: for the current/alternate context,
 * via the scheduler; otherwise via the runtime write-check helper.
 * Confidence: medium */
static unsigned long sk_obj_live(long obj)
{
    int live;
    unsigned long ctx;

    ctx = sk_sys_wait(0);
    if ((obj == _DAT_006b4368 || obj == _DAT_006b4380) &&
        (live = sk_sched_unpin(), live != 0)) {
        return sk_sched_unpin3(ctx, *(unsigned long *)(obj + 0x58));
    }
    live = sk_rt_writel_ok(*(unsigned long *)(obj + 0x58), 0);
    return (unsigned long)(live != 0);
}

/* FUN_00655774 @ 0x00655774  (est. sk_obj_dispatch_58b)
 * Ghidra: void FUN_00655774(long param_1)
 * Dispatches the object at param_1 (like sk_obj_dispatch_58 but via the second
 * runtime write helper).
 * Confidence: medium */
static void sk_obj_dispatch_58b(long obj)
{
    unsigned long ctx;
    int live;

    ctx = sk_sys_wait(0);
    if ((obj == _DAT_006b4368 || obj == _DAT_006b4380) &&
        (live = sk_sched_unpin(), live != 0)) {
        sk_sched_unpin4(ctx, *(unsigned long *)(obj + 0x58));
        return;
    }
    sk_rt_writel2(*(unsigned long *)(obj + 0x58), 0);
}

/* FUN_006557e0 @ 0x006557e0  (est. sk_rt_clr_entry)
 * Ghidra: void FUN_006557e0(int param_1)
 * When param_1 is set, zeroes the two per-CPU lock words, then clears four runtime
 * state words (0x6feca8/0xb8/0xc8/0xd8).
 * Confidence: medium */
static void sk_rt_clr_entry(int clear_locks)
{
    if (clear_locks != 0) {
        _DAT_006b4458 = 0;
        _DAT_006b45b8 = 0;
    }
    sk_rt_clr(0x6feca8, 2);
    sk_rt_clr(0x6fecb8, 2);
    sk_rt_clr(0x6fecc8, 2);
    sk_rt_clr(0x6fecd8, 2);
}

/* FUN_00655848 @ 0x00655848  (est. sk_cur_cpu)
 * Ghidra: void FUN_00655848(void)
 * Returns the current CPU's per-CPU descriptor (0x6fc580).
 * Confidence: medium */
static unsigned long sk_cur_cpu(void)
{
    return sk_bucket_lookup(0x6fc580, 2, 2);
}

/* FUN_0065585c @ 0x0065585c  (est. sk_descriptor_parse)
 * Ghidra: undefined1 *FUN_0065585c(long param_1)
 * Parses a 0x400-byte descriptor table at param_1 (64 16-byte tag/value entries) into
 * the global per-CPU runtime descriptor fields (0x6fc4xx window). Returns the base of
 * the parsed descriptor window (0x6fc420).
 * Confidence: medium */
static unsigned char *sk_descriptor_parse(long table)
{
    long off, tag, val;
    unsigned long prng_seed;
    unsigned char *p;

    off = 0;
    prng_seed = 0;
    _DAT_006fc4e8 = 0;
    _DAT_006fc520 = 0x400;
    do {
        tag = *(long *)(table + off);
        if (tag - 1U < 0x2b) {
            val = *((long *)(table + off) + 1);
            switch (tag) {
            default: _DAT_006fc428 = val; break;
            case 2: _DAT_006fc430 = val; break;
            case 3: _DAT_006fc438 = val; break;
            case 4: case 5: case 6: case 10: case 0xb: case 0xd: case 0x19:
                break;
            case 7: _DAT_006fc478 = val; break;
            case 8: _DAT_006fc480 = val; break;
            case 9: _DAT_006fc488 = val; break;
            case 0xc: _DAT_006fc490 = val; break;
            case 0xe: _DAT_006fc4b0 = val; break;
            case 0xf: _DAT_006fc4b8 = val; break;
            case 0x10: _DAT_006fc4c0 = val; break;
            case 0x11: _DAT_006fc4c8 = val; break;
            case 0x12: _DAT_006fc4d0 = val; break;
            case 0x13: _DAT_006fc498 = val; break;
            case 0x14: _DAT_006fc4a0 = val; break;
            case 0x15: _DAT_006fc420 = val == 0; _DAT_006fc4d8 = val; break;
            case 0x16: prng_seed = val; break;
            case 0x17: _DAT_006fc4e8 = val; break;
            case 0x18: _DAT_006fc4f8 = (unsigned char)val; break;
            case 0x1a: _DAT_006fc500 = val; break;
            case 0x1b: _DAT_006fc508 = val; break;
            case 0x1c: _DAT_006fc510 = val; break;
            case 0x1d: _DAT_006fc528 = val;
            case 0x1e: _DAT_006fc530 = val; break;
            case 0x1f: _DAT_006fc538 = val; break;
            case 0x20: _DAT_006fc4a8 = val; break;
            case 0x21: _DAT_006fc540 = val; break;
            case 0x22: _DAT_006fc548 = val; break;
            case 0x23: _DAT_006fc550 = val; break;
            case 0x24: _DAT_006fc558 = val; break;
            case 0x25: _DAT_006fc560 = val; break;
            case 0x26: _DAT_006fc568 = val; break;
            case 0x27: _DAT_006fc4f0 = val; break;
            case 0x28: _DAT_006fc450 = val; break;
            case 0x29: _DAT_006fc460 = val; break;
            case 0x2a: _DAT_006fc570 = val; break;
            case 0x2b: _DAT_006fc578 = val;
            }
        }
        off = off + 0x10;
    } while (off != 0x400);
    _DAT_006fc518 = table;
    if (prng_seed != 0 && (prng_seed + _DAT_006fc4e8 * 0x78 < prng_seed + 0x78 ||
                           prng_seed + 0x78 < prng_seed)) {
        SoftwareBreakpoint(0x5519, 0x655aec);
    }
    _DAT_006b43a0 = table;
    _DAT_006fc4e0 = prng_seed;
    sk_bucket_iter(0x6b4388, 0, 0);
    _DAT_006b43c0 = (unsigned long)&_DAT_006fc420;
    sk_bucket_iter(0, 0, 0);
    return (unsigned char *)&_DAT_006fc420;
}

/* FUN_00655b98 @ 0x00655b98  (est. sk_obj_store_register)
 * Ghidra: void FUN_00655b98(undefined8 param_1)
 * Registers param_1 as the current object-store descriptor if the store lock is free.
 * Confidence: medium */
static void sk_obj_store_register(unsigned long desc)
{
    if (sk_bucket_acquire(2, 6) != 0) {
        return;
    }
    _DAT_006b43e0 = desc;
    sk_bucket_iter(0, 0, 0);
}

/* FUN_00655be4 @ 0x00655be4  (est. sk_store_get)
 * Ghidra: void FUN_00655be4(void)
 * Returns the current per-CPU store descriptor (0x6fc588).
 * Confidence: medium */
static unsigned long sk_store_get(void)
{
    return sk_bucket_lookup(0x6fc588, 2, 6);
}

/* FUN_00655bf8 @ 0x00655bf8  (est. sk_store_teardown)
 * Ghidra: void FUN_00655bf8(ulong param_1, long param_2)
 * Tears down param_2 object entries starting at param_1 (each 0x78 bytes): for each
 * entry whose "destroy" bit (word at +8 bit 7) is set, dispatches its teardown via
 * sk_store_dispatch_teardown, then releases the entry.
 * Confidence: medium */
static void sk_store_teardown(unsigned long base, long count)
{
    unsigned long entry;
    long remain;

    if (count != 0) {
        remain = count * 0x78;
        entry = base;
        do {
            if ((entry < base) || (base + remain < entry + 0x78) || entry + 0x78 < entry) {
                SoftwareBreakpoint(0x5519, 0x655c84);
            }
            if (((*(unsigned long *)(entry + 8) >> 7) & 1) != 0) {
                sk_store_dispatch_teardown(entry, *(unsigned long *)(entry + 0x38),
                                           *(unsigned long *)(entry + 0x20),
                                           *(unsigned long *)(entry + 0x50),
                                           *(unsigned long *)(entry + 0x48));
            }
            sk_bucket_release(entry);
            entry = entry + 0x78;
            count = count - 1;
        } while (count != 0);
    }
}

/* FUN_00655c84 @ 0x00655c84  (est. sk_store_dispatch_teardown)
 * Ghidra: void FUN_00655c84(long param_1, undefined8 param_2, long param_3, ...)
 * Populates an object-store entry (param_1) from a capability descriptor (param_2):
 * resolves its size bounds (FUN_0064faa4/fb28), splits the region (FUN_0064fd5c) and
 * records base/length/state, plus the 16-byte descriptor footer.
 * Confidence: medium */
static void sk_store_dispatch_teardown(long entry, unsigned long cap, long size,
                                       unsigned long a, unsigned long b)
{
    long base, len, end;
    unsigned long state, x, y, z;
    unsigned long desc_off;

    base = sk_vas_size_of(cap);
    end = sk_vas_size_end(cap);
    x = 0; y = 0; z = 0;
    sk_vas_split(cap, &x, &y, &z);
    *(unsigned long *)(entry + 0x48) = b;
    *(unsigned long *)(entry + 0x50) = a;
    *(long *)(entry + 0x20) = size;
    *(long *)(entry + 0x28) = base + size;
    *(long *)(entry + 0x30) = end - base;
    *(unsigned long *)(entry + 0x38) = cap;
    *(long *)(entry + 0x58) = x;
    *(long *)(entry + 0x60) = x << 4;
    *(unsigned long *)(entry + 0x68) = y;
    *(unsigned long *)(entry + 0x70) = z;
    *(unsigned long *)(entry + 8) = b;
    desc_off = sk_vas_region_at(cap);
    if (desc_off == 0) {
        sk_memzero((unsigned long)entry + 0x10, 0x10);
    } else if (desc_off + 0x10 < desc_off ||
               (sk_memcpy((unsigned long)entry + 0x10, desc_off, 0x10), entry + 0x20 < entry + 0x10)) {
        SoftwareBreakpoint(0x5519, 0x655d54);
    }
}

/* FUN_00655d7c @ 0x00655d7c  (est. sk_store_get_cap)
 * Ghidra: undefined8 FUN_00655d7c(void)
 * Returns the current store entry's capability (field +0x38).
 * Confidence: medium */
static unsigned long sk_store_get_cap(void)
{
    unsigned long e;

    e = (unsigned long)sk_bucket_current();
    if (e != 0) {
        return *(unsigned long *)(e + 0x38);
    }
    return 0;
}

/* FUN_00655d9c @ 0x00655d9c  (est. sk_store_get_size)
 * Ghidra: undefined8 FUN_00655d9c(void)
 * Returns the current store entry's size (field +0x20).
 * Confidence: medium */
static unsigned long sk_store_get_size(void)
{
    unsigned long e;

    e = (unsigned long)sk_bucket_current();
    if (e != 0) {
        return *(unsigned long *)(e + 0x20);
    }
    return 0;
}

/* FUN_00655dbc @ 0x00655dbc  (est. sk_store_get_footer)
 * Ghidra: void FUN_00655dbc(ulong param_1)
 * Copies the current store entry's 16-byte footer (at +0x10) into param_1, or zeroes
 * param_1 if no current entry exists.
 * Confidence: medium */
static void sk_store_get_footer(unsigned long out)
{
    unsigned long e;

    e = (unsigned long)sk_bucket_current();
    if (e == 0) {
        sk_memzero((unsigned long)out, 0x10);
        return;
    }
    sk_memcpy((unsigned long)out, e + 0x10, 0x10);
    if (out <= out + 0x10) {
        return;
    }
    SoftwareBreakpoint(0x5519, 0x655e1c);
}

/* FUN_00655e1c @ 0x00655e1c  (est. sk_store_write_back)
 * Ghidra: void FUN_00655e1c(undefined8 param_1, undefined8 param_2)
 * Writes back a store entry's dirty region: looks up the region by address and, when
 * the recorded size allows, copies param_2 bytes into it via the split helper.
 * Confidence: medium */
static void sk_store_write_back(unsigned long addr, unsigned long data)
{
    unsigned long inout = addr;
    unsigned long e;

    e = sk_bucket_lookup_name(&inout, 1);
    if (e != 0) {
        if ((*(unsigned long *)(e + 0x60) >> 4) < *(unsigned long *)(e + 0x58)) {
            SoftwareBreakpoint(0x5519, 0x655e7c);
        }
        sk_vas_walk_commit3(inout, data, *(unsigned long *)(e + 0x58),
                            *(unsigned long *)(e + 0x68), *(unsigned long *)(e + 0x70));
    }
}

/* FUN_00655e7c @ 0x00655e7c  (est. sk_store_noop)
 * Ghidra: undefined8 FUN_00655e7c(void)
 * No-op returning 0.
 * Confidence: high */
static unsigned long sk_store_noop(void)
{
    return 0;
}

/* FUN_00655e84 @ 0x00655e84  (est. sk_store_read16)
 * Ghidra: void FUN_00655e84(void)
 * Reads a 16-byte descriptor from the store (FUN_0065d3d8) and, on success, writes it
 * back via sk_store_write8; otherwise reports a store fault.
 * Confidence: medium */
static void sk_store_read16(void)
{
    unsigned long canary = _DAT_006b5ed0;
    unsigned long local_28, uStack_20;
    unsigned long rc;

    rc = sk_bucket_read16(local_28, 0x10);
    if (rc == 0x10) {
        sk_store_write8(local_28, uStack_20);
        if (_DAT_006b5ed0 == canary) {
            return;
        }
    } else {
        sk_obj_release6();
    }
    sk_stack_check_fail();
}

/* FUN_00655eec @ 0x00655eec  (est. sk_debug_write)
 * Ghidra: long FUN_00655eec(long param_1, char *param_2, long param_3)
 * Debug-output writer: for each of param_3 bytes at param_2, either reflects the byte
 * plus the current reply word into the per-CPU message area and issues a supervisor
 * call (when the target equals 0x6b4708 and a reply slot is live), or writes the byte
 * with a zero reply word. Restores the message area afterwards.
 * Confidence: medium */
static long sk_debug_write(long target, char *src, long n)
{
    unsigned long reply, reply2;
    long i;
    unsigned char *m;
    char c, sign;
    unsigned char b0, b1, b2, b3, b4, b5, b6, b7;
    unsigned short w;
    unsigned char u2, u3, u4, u5, u6, u7;
    unsigned char *w0;
    long e;

    if (target != 0x6b4448 || (e = sk_vas_name(src, n), e != 0)) {
        reply = sk_store_slot288();       /* thunk_FUN_00654cc8 returns {lo,hi} */
        reply2 = sk_store_slot2a8();
        m = (unsigned char *)tpidrro_el0;
        b0 = m[9]; b1 = m[8]; b2 = m[0xb]; b3 = m[10];
        w = *(unsigned short *)(m + 0xc);
        b4 = m[0xf]; b5 = m[0xe];
        if (n != 0) {
            i = 0;
            do {
                if (target == 0x6b4708 && (e = sk_store_reply_word(), e != 0)) {
                    reply = sk_store_reply_word();
                    if (src + n <= src + i || src + i < src) {
                        goto bounds_fault;
                    }
                    c = src[i];
                    m[0] = (char)reply;
                    m[5] = (char)(reply >> 0x28);
                    m[3] = (char)(reply >> 0x18);
                    m[2] = (char)(reply >> 0x10);
                    m[1] = (char)(reply >> 8);
                    m[4] = (char)(reply >> 0x20);
                    m[7] = (char)(reply >> 0x38);
                    m[6] = (char)(reply >> 0x30);
                    sign = (char)(c >> 7);
                    m[0xd] = sign; m[8] = c; m[0xb] = sign; m[10] = sign;
                    m[9] = sign; m[0xc] = sign; m[0xf] = (char)(c >> 7); m[0xe] = sign;
                    do {
                        CallSupervisor(0);
                        m[0] = (char)reply; m[5] = (char)(reply >> 0x28);
                        m[3] = (char)(reply >> 0x18); m[2] = (char)(reply >> 0x10);
                        m[1] = (char)(reply >> 8); m[4] = (char)(reply >> 0x20);
                        m[7] = (char)(reply >> 0x38); m[6] = (char)(reply >> 0x30);
                    } while (reply == 1);
                } else {
                    if (src + n <= src + i || src + i < src) {
                        goto bounds_fault;
                    }
                    c = src[i];
                    m[5] = 0; m[3] = 0; m[2] = 0; m[1] = 0; m[4] = 0;
                    m[0] = 0; m[7] = 0; m[6] = 0;
                    sign = (char)(c >> 7);
                    m[0xd] = sign; m[8] = c; m[0xb] = sign; m[10] = sign;
                    m[9] = sign; m[0xc] = sign; m[0xf] = (char)(c >> 7); m[0xe] = sign;
                    do {
                        CallSupervisor(0);
                        m[0] = 0; m[5] = 0; m[3] = 0; m[2] = 0; m[1] = 0;
                        m[4] = 0; m[7] = 0; m[6] = 0;
                    } while (reply == 1);
                }
                reply = 0;
                i++;
            } while (i != n);
        }
        m[8] = b1;
        m[0xd] = (char)((unsigned short)w >> 8);
        m[0xb] = b2; m[10] = b3; m[9] = b0; m[0xc] = (char)w;
        m[0xf] = b4; m[0xe] = b5;
    }
    return n;
bounds_fault:
    SoftwareBreakpoint(0x5519, 0x6561fc);
}

/* FUN_006561fc @ 0x006561fc  (est. sk_obj_dispatch_slot10)
 * Ghidra: void FUN_006561fc(undefined8 param_1, long param_2)
 * Dispatches the object at param_2 through its vtable slot at (+0x18)+0x10 when the
 * destroy bit (word at +8 bit 0x19) is set and the slot is non-NULL.
 * Confidence: medium */
static void sk_obj_dispatch_slot10(unsigned long a, long obj)
{
    void (**vt)(void);

    if ((*(unsigned int *)(obj + 8) >> 0x19 & 1) != 0) {
        vt = *(void (***)(void))(*(long *)(obj + 0x18) + 0x10);
        if (vt != 0 && vt != 0 && vt != 0) {
            (*vt)();
        }
    }
}

/* FUN_00656240 @ 0x00656240  (est. sk_obj_dispatch_slot18)
 * Ghidra: void FUN_00656240(long param_1)
 * Dispatches the object at param_1 through its vtable slot at (+0x18)+0x18 when the
 * destroy bit is set and the slot is non-NULL.
 * Confidence: medium */
static void sk_obj_dispatch_slot18(long obj)
{
    void (**vt)(void);

    if ((*(unsigned int *)(obj + 8) >> 0x19 & 1) != 0) {
        vt = *(void (***)(void))(*(long *)(obj + 0x18) + 0x18);
        if (vt != 0 && vt != 0 && vt != 0) {
            (*vt)();
        }
    }
}

/* FUN_00656284 @ 0x00656284  (est. sk_obj_retain)
 * Ghidra: undefined8 *FUN_00656284(undefined8 *param_1)
 * Retains a capability object (param_1): handles the shared (bit 0x18) and inline
 * (bit 0x1c) object forms. For a shared object, resolves its backing slot, and if it
 * has a copy (lVar3) copies the payload into a fresh object; otherwise performs a
 * reference-count increment, freeing the object when the count reaches zero.
 * Confidence: medium */
static unsigned long *sk_obj_retain(unsigned long *obj)
{
    unsigned int w;
    unsigned long *copy, *o;
    long size;
    unsigned int *slot;
    int rc;
    unsigned long u;

    if (obj == 0) {
        copy = 0;
    } else {
        copy = obj;
        if ((*(unsigned int *)(obj + 1) >> 0x18 & 1) == 0) {
            if ((*(unsigned int *)(obj + 1) >> 0x1c & 1) == 0) {
                u = *(unsigned long *)(obj[3] + 8);
                copy = (unsigned long *)sk_alloc_region(u, 0x10e0040a5821769);
                if (copy != 0) {
                    size = obj[2];
                    if (size == 0 || size == 0 || size == 0) {
                        o = (unsigned long *)sk_alloc_zero_obj(0, 0);
                        if (o != 0 && (*(unsigned int *)(o + 1) >> 0x1c & 1) == 0 &&
                            (*(unsigned int *)(o + 1) >> 0x18 & 1) != 0) {
                            do {
                                w = *(unsigned int *)(o + 1);
                                if ((w & 0xfffe) == 0 || (w & 0xfffe) == 0xfffe) {
                                    return o;
                                }
                                rc = -2;
                                if ((w & 0xffff) == 2) {
                                    rc = -1;
                                }
                            } while (*(unsigned int *)(o + 1) != w);
                            *(unsigned int *)(o + 1) = rc + w;
                            if ((w & 0xffff) == 2) {
                                sk_obj_dispatch_slot18((long)o);
                                (*_DAT_006b4878)((unsigned long)o);
                                o = (unsigned long *)sk_free_obj((unsigned long)o);
                                return o;
                            }
                        }
                        return o;
                    }
                    sk_memcpy((unsigned long)copy, (unsigned long)obj, u);
                    copy[2] = obj[2];
                    *(unsigned int *)(copy + 1) = *(unsigned int *)(copy + 1) & 0xffff0000;
                    *(unsigned int *)(copy + 1) = *(unsigned int *)(copy + 1) | 0x1000002;
                    sk_obj_dispatch_slot10((unsigned long)copy, (long)obj);
                    *copy = 0x6fefa8;
                }
            }
        } else {
            do {
                w = *(unsigned int *)(obj + 1);
                if (((w ^ 0xffffffff) & 0xfffe) == 0) {
                    return obj;
                }
            } while (*(unsigned int *)(obj + 1) != w);
            *(unsigned int *)(obj + 1) = w + 2;
        }
    }
    return copy;
}

/* FUN_00656474 @ 0x00656474  (est. sk_obj_dispatch)
 * Ghidra: void FUN_00656474(long *param_1, long param_2, uint param_3)
 * Method dispatch on a capability object: performs the operation identified by
 * param_3 (masked to 0x9f) on param_2, storing the resulting object back through
 * param_1. Handles release (3), retain (7), detach (8/0x18) and the extended
 * (0x83..0x97) operation set.
 * Confidence: medium */
static void sk_obj_dispatch(long *out, long obj, unsigned int op)
{
    unsigned int w, u1;
    unsigned long *copy;
    long *slot;
    long n;

    op = op & 0x9f;
    if (op < 0x18) {
        if (op == 3) {
            (*_DAT_006b4868)(obj);
            goto done;
        }
        if (op == 7) {
            obj = (long)sk_obj_retain((unsigned long *)obj);
            goto done;
        }
        if (op != 8) {
            return;
        }
    } else {
        if (op - 0x83 < 0x15 && (1 << (op - 0x83 & 0x1f) & 0x110011U) != 0) {
            goto done;
        }
        if (op != 0x18) {
            return;
        }
    }
    slot = *(long **)(obj + 8);
    if ((*(unsigned int *)(slot + 0x10) & 0xfffe) == 0) {
        u1 = *(unsigned int *)(obj + 0x14);
        copy = (unsigned long *)sk_alloc_region((unsigned long)u1, 0x10e0040f15f98b3);
        *copy = 0;
        *(unsigned int *)(copy + 2) = *(unsigned int *)(obj + 0x10) | 0x1000004;
        copy[1] = (unsigned long)copy;
        *(unsigned long **)(obj + 8) = copy;
        u1 = *(unsigned int *)(obj + 0x14);
        *(unsigned int *)((long)copy + 0x14) = u1;
        if ((*(unsigned int *)(obj + 0x10) >> 0x19 & 1) == 0) {
            n = 0;
            if (0x17 < u1) {
                n = (unsigned long)u1 - 0x18;
            }
            sk_rt_writel_t((unsigned long)(copy + 3), (unsigned long)u1 - 0x18, n);
        } else {
            copy[3] = *(unsigned long *)(obj + 0x18);
            copy[4] = *(unsigned long *)(obj + 0x20);
            if (*(unsigned int *)(obj + 0x10) >> 0x1c == 1) {
                copy[5] = *(unsigned long *)(obj + 0x28);
            }
            (*(void (**)(void))(obj + 0x18))();
        }
    } else if ((*(unsigned int *)(slot + 0x10) >> 0x18 & 1) != 0) {
        do {
            w = *(unsigned int *)(slot + 0x10);
            if (((w ^ 0xffffffff) & 0xfffe) == 0) {
                goto got_slot;
            }
        } while (*(unsigned int *)(slot + 0x10) != w);
        *(unsigned int *)(slot + 0x10) = w + 2;
    }
got_slot:
    obj = *(long *)(obj + 8);
done:
    *out = obj;
}

/* FUN_00656634 @ 0x00656634  (est. sk_obj_release_dispatch)
 * Ghidra: void FUN_00656634(long param_1, uint param_2)
 * Release dispatch on a capability object: performs the release operation identified
 * by param_2 (3=external release, 7=retain-drop, 8/0x18=inline release).
 * Confidence: medium */
static void sk_obj_release_dispatch(long obj, unsigned int op)
{
    unsigned int w;
    int rc;
    long *slot;

    op = op & 0x9f;
    if (op < 8) {
        if (op == 3) {
            (*_DAT_006b4870)();
            return;
        }
        if (op == 7) {
            if (obj != 0 && (*(unsigned int *)(obj + 8) >> 0x1c & 1) == 0 &&
                (*(unsigned int *)(obj + 8) >> 0x18 & 1) != 0) {
                do {
                    w = *(unsigned int *)(obj + 8);
                    if ((w & 0xfffe) == 0 || (w & 0xfffe) == 0xfffe) {
                        return;
                    }
                    rc = -2;
                    if ((w & 0xffff) == 2) {
                        rc = -1;
                    }
                } while (*(unsigned int *)(obj + 8) != w);
                *(unsigned int *)(obj + 8) = rc + w;
                if ((w & 0xffff) == 2) {
                    sk_obj_dispatch_slot18(obj);
                    (*_DAT_006b4878)((unsigned long)obj);
                    sk_free_obj((unsigned long)obj);
                    return;
                }
            }
            return;
        }
    } else if ((op == 0x18 || op == 8) &&
               (slot = *(long **)(obj + 8), (*(unsigned int *)(slot + 0x10) >> 0x18 & 1) != 0)) {
        if ((*(unsigned int *)(slot + 0x10) & 0xfffe) == 0) {
            sk_obj_release7();
            return;
        }
        do {
            w = *(unsigned int *)(slot + 0x10);
            if ((w & 0xfffe) == 0 || (w & 0xfffe) == 0xfffe) {
                return;
            }
            rc = -2;
            if ((w & 0xffff) == 2) {
                rc = -1;
            }
        } while (*(unsigned int *)(slot + 0x10) != w);
        *(unsigned int *)(slot + 0x10) = rc + w;
        if ((w & 0xffff) == 2) {
            if ((*(unsigned int *)(slot + 0x10) >> 0x19 & 1) != 0) {
                (*(void (**)(void))(slot + 0x20))();
            }
            sk_free_obj((unsigned long)slot);
        }
    }
}

/* FUN_00656744 @ 0x00656744  (est. sk_store_type_validate)
 * Ghidra: void FUN_00656744(undefined8 param_1)
 * Validates that param_1 is one of the known store descriptors by attempting each of
 * the eleven type-validator functions (FUN_00656ce4/57200/57974/580ec/58870/58ff4/
 * 59774/59ef4/5a674/5adf4/5b574); panics if none matches, else registers the store.
 * Confidence: medium */
static void sk_store_type_validate(unsigned long param)
{
    /* desc validators 4-11 are defined in sibling slices (0x6580ec..0x65b574) */
    if (((((((sk_store_desc2(param, 0x6fece8) & 1) == 0) &&
             ((sk_store_desc1(param, 0x6fece8) & 1) == 0)) &&
            ((sk_store_desc0x100000001(param, 0x6fece8) & 1) == 0)) &&
           (((sk_store_desc4(param, 0x6fece8) & 1) == 0) &&
            ((sk_store_desc5(param, 0x6fece8) & 1) == 0))) &&
          (((sk_store_desc6(param, 0x6fece8) & 1) == 0) &&
           (((sk_store_desc7(param, 0x6fece8) & 1) == 0) &&
            ((sk_store_desc8(param, 0x6fece8) & 1) == 0)))) &&
         (((sk_store_desc9(param, 0x6fece8) & 1) == 0) &&
          (((sk_store_desc10(param, 0x6fece8) & 1) == 0) &&
           ((sk_store_desc11(param, 0x6fece8) & 1) == 0)))) {
        SoftwareBreakpoint(1, 0x65684c);
    }
    sk_obj_store_register(0x6fece8);
}

/* FUN_0065684c @ 0x0065684c  (est. sk_store_field8)
 * Ghidra: undefined8 FUN_0065684c(void)
 * Returns store field +8.
 * Confidence: high */
static unsigned long sk_store_field8(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned long *)(reg + 8);
}

/* FUN_00656868 @ 0x00656868  (est. sk_store_type1)
 * Ghidra: undefined1 FUN_00656868(void)
 * Returns store field +0x20.
 * Confidence: high */
static unsigned char sk_store_type1(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned char *)(reg + 0x20);
}

/* FUN_00656884 @ 0x00656884  (est. sk_store_call28)
 * Ghidra: void FUN_00656884(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Calls the store's +0x28 method with three args.
 * Confidence: medium */
static void sk_store_call28(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(unsigned long, unsigned long, unsigned long))(reg + 0x28))(a, b, c);
}

/* FUN_006568d0 @ 0x006568d0  (est. sk_store_field30)
 * Ghidra: undefined1 FUN_006568d0(void)
 * Returns store field +0x30.
 * Confidence: high */
static unsigned char sk_store_field30(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned char *)(reg + 0x30);
}

/* FUN_006568ec @ 0x006568ec  (est. sk_store_field39)
 * Ghidra: undefined1 FUN_006568ec(void)
 * Returns store field +0x39.
 * Confidence: high */
static unsigned char sk_store_field39(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned char *)(reg + 0x39);
}

/* FUN_00656908 @ 0x00656908  (est. sk_store_field3a)
 * Ghidra: undefined1 FUN_00656908(void)
 * Returns store field +0x3a.
 * Confidence: high */
static unsigned char sk_store_field3a(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned char *)(reg + 0x3a);
}

/* FUN_00656924 @ 0x00656924  (est. sk_store_call88)
 * Ghidra: void FUN_00656924(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Calls the store's +0x88 method with four args.
 * Confidence: medium */
static void sk_store_call88(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(unsigned long, unsigned long, unsigned long, unsigned long))(reg + 0x88))(a, b, c, d);
}

/* FUN_00656978 @ 0x00656978  (est. sk_store_call90)
 * Ghidra: void FUN_00656978(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Calls the store's +0x90 method with three args.
 * Confidence: medium */
static void sk_store_call90(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(unsigned long, unsigned long, unsigned long))(reg + 0x90))(a, b, c);
}

/* FUN_006569c4 @ 0x006569c4  (est. sk_store_fieldd0)
 * Ghidra: undefined8 FUN_006569c4(void)
 * Returns store field +0xd0.
 * Confidence: high */
static unsigned long sk_store_fieldd0(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned long *)(reg + 0xd0);
}

/* FUN_006569e0 @ 0x006569e0  (est. sk_store_calld8)
 * Ghidra: void FUN_006569e0(undefined8 param_1)
 * Calls the store's +0xd8 method with one arg.
 * Confidence: medium */
static void sk_store_calld8(unsigned long a)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(unsigned long))(reg + 0xd8))(a);
}

/* FUN_00656a14 @ 0x00656a14  (est. sk_store_type2)
 * Ghidra: undefined1 FUN_00656a14(void)
 * Returns store field +0xf1.
 * Confidence: high */
static unsigned char sk_store_type2(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned char *)(reg + 0xf1);
}

/* FUN_00656a30 @ 0x00656a30  (est. sk_store_fieldf4)
 * Ghidra: undefined4 FUN_00656a30(void)
 * Returns store field +0xf4.
 * Confidence: high */
static unsigned int sk_store_fieldf4(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned int *)(reg + 0xf4);
}

/* FUN_00656a4c @ 0x00656a4c  (est. sk_store_call120)
 * Ghidra: void FUN_00656a4c(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Calls the store's +0x120 method with four args.
 * Confidence: medium */
static void sk_store_call120a(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(unsigned long, unsigned long, unsigned long, unsigned long))(reg + 0x120))(a, b, c, d);
}

/* FUN_00656aa0 @ 0x00656aa0  (est. sk_store_call130)
 * Ghidra: void FUN_00656aa0(undefined8 param_1, undefined8 param_2)
 * Calls the store's +0x130 method with two args.
 * Confidence: medium */
static void sk_store_call130a(unsigned long a, unsigned long b)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(unsigned long, unsigned long))(reg + 0x130))(a, b);
}

/* FUN_00656adc @ 0x00656adc  (est. sk_store_type3)
 * Ghidra: undefined1 FUN_00656adc(void)
 * Returns store field +0x14a.
 * Confidence: high */
static unsigned char sk_store_type3(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned char *)(reg + 0x14a);
}

/* FUN_00656af8 @ 0x00656af8  (est. sk_store_type3_hook)
 * Ghidra: void FUN_00656af8(undefined8 param_1)
 * Calls the store's +0x168 method with one arg.
 * Confidence: medium */
static void sk_store_type3_hook(unsigned long a)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(unsigned long))(reg + 0x168))(a);
}

/* FUN_00656b2c @ 0x00656b2c  (est. sk_store_table_at)
 * Ghidra: undefined8 FUN_00656b2c(uint param_1)
 * Returns the word at index param_1 of the store's primary pointer table (+0x180),
 * or 0 when param_1 is out of the table's declared range (+0x178).
 * Confidence: medium */
static unsigned long sk_store_table_at(unsigned int idx)
{
    unsigned long base, p;

    if (((int)idx < 0) || ((p = sk_store_get(), *(unsigned char *)(p + 0x178)) <= idx)) {
        return 0;
    }
    base = *(unsigned long *)(p + 0x180);
    p = base + idx * 8;
    if ((p < base || base + *(unsigned char *)(p + 0x178) < p + 8) || p + 8 < p) {
        SoftwareBreakpoint(0x5519, 0x656b98);
    }
    return *(unsigned long *)p;
}

/* FUN_00656b98 @ 0x00656b98  (est. sk_store_table_b)
 * Ghidra: undefined8 FUN_00656b98(uint param_1)
 * Returns the word at index param_1 of the store's secondary pointer table (+400),
 * or 0 when out of range.
 * Confidence: medium */
static unsigned long sk_store_table_b(unsigned int idx)
{
    unsigned long base, p;

    if (((int)idx < 0) || ((p = sk_store_get(), *(unsigned char *)(p + 0x178)) <= idx)) {
        return 0;
    }
    base = *(unsigned long *)(p + 400);
    p = base + idx * 8;
    if ((p < base || base + *(unsigned char *)(p + 0x178) < p + 8) || p + 8 < p) {
        SoftwareBreakpoint(0x5519, 0x656c04);
    }
    return *(unsigned long *)p;
}

/* FUN_00656c04 @ 0x00656c04  (est. sk_store_call198)
 * Ghidra: void FUN_00656c04(void)
 * Calls the store's +0x198 method (no args).
 * Confidence: medium */
static void sk_store_call198(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(void))(reg + 0x198))();
}

/* FUN_00656c28 @ 0x00656c28  (est. sk_store_call1a0)
 * Ghidra: void FUN_00656c28(void)
 * Calls the store's +0x1a0 method (no args).
 * Confidence: medium */
static void sk_store_call1a0(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    (*(void (**)(void))(reg + 0x1a0))();
}

/* FUN_00656c4c @ 0x00656c4c  (est. sk_store_reply_word)
 * Ghidra: undefined8 FUN_00656c4c(void)
 * Returns store field +0x1b0 (the reply word).
 * Confidence: high */
static unsigned long sk_store_reply_word(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned long *)(reg + 0x1b0);
}

/* FUN_00656c68 @ 0x00656c68  (est. sk_store_field1b8)
 * Ghidra: undefined1 FUN_00656c68(void)
 * Returns store field +0x1b8.
 * Confidence: high */
static unsigned char sk_store_field1b8(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    return *(unsigned char *)(reg + 0x1b8);
}

/* FUN_00656c84 @ 0x00656c84  (est. sk_store_restrict_ctx)
 * Ghidra: void FUN_00656c84(void)
 * Applies context / branch / cache-prefetch / data-value prediction restrictions and
 * synchronizes the caches (ISB/DSB) when the store's enable flags are set.
 * Confidence: high (instruction-set matched) */
static void sk_store_restrict_ctx(void)
{
    unsigned long reg;

    reg = (unsigned long)sk_store_get();
    if ((*(unsigned char *)(reg + 0x1b9) & 1) == 0) {
        reg = (unsigned long)sk_store_get();
        if (*(char *)(reg + 0x1bb) == 1) {
            InstructionSynchronizationBarrier();
        }
        reg = (unsigned long)sk_store_get();
        if ((*(unsigned char *)(reg + 0x1ba) & 1) == 0) {
            SysOp_W(3, 7, 3, 6, 0);
        }
        ControlFlowPredictionRestrictionByContext(0);
        CachePrefetchPredictionRestrictionByContext(0);
        DataValuePredictionRestrictionByContext(0);
        DataSynchronizationBarrier(3, 3, 0);
        InstructionSynchronizationBarrier();
    }
}

/* FUN_00656ce4 @ 0x00656ce4  (est. sk_store_desc2)
 * Ghidra: bool FUN_00656ce4(long param_1, long param_2)
 * Initializes an object-store descriptor block (param_2) for descriptor type 2
 * (a kernel-object / capability-bucket store). Fills the method table, type tag
 * (0x6a5ed4), slot table pointer (DAT_006887c0) and vtable entries (LAB_00656f8c..).
 * Returns (param_1 == 2).
 * Confidence: medium */
static int sk_store_desc2(long type, long desc)
{
    if (type == 2) {
        *(unsigned long *)(desc + 8) = 2;
        *(unsigned long *)(desc + 0x10) = 0x6a5ed4;
        *(unsigned char *)(desc + 0x18) = 1;
        *(unsigned int *)(desc + 0x1c) = 2;
        *(unsigned char *)(desc + 0x20) = 0x18;
        *(unsigned long *)(desc + 0x28) = (unsigned long)&_DAT_00688788;   /* LAB_00656f8c */
        *(unsigned char *)(desc + 0x30) = 0;
        *(unsigned long *)(desc + 0x34) = 0xffffffff;
        *(unsigned long *)(desc + 0x48) = 0;
        *(unsigned long *)(desc + 0x40) = 0;
        *(unsigned long *)(desc + 0x58) = 0;
        *(unsigned long *)(desc + 0x50) = 0;
        *(unsigned long *)(desc + 0x68) = 0;
        *(unsigned long *)(desc + 0x60) = 0;
        *(unsigned long *)(desc + 0x78) = 0;
        *(unsigned long *)(desc + 0x70) = 0;
        *(unsigned long *)(desc + 0x88) = 0;
        *(unsigned long *)(desc + 0x80) = 0;
        *(unsigned long *)(desc + 0x98) = 0;
        *(unsigned long *)(desc + 0x90) = 0;
        *(unsigned char *)(desc + 0xa0) = 1;
        *(unsigned int *)(desc + 0xa4) = 3;
        *(unsigned long *)(desc + 0xa8) = (unsigned long)&_DAT_00688788;   /* LAB_00656fac */
        *(unsigned long *)(desc + 0xb0) = (unsigned long)&_DAT_00688788;   /* LAB_00656fb4 */
        *(unsigned long *)(desc + 0xb8) = (unsigned long)&_DAT_00688788;   /* LAB_00656fbc */
        *(unsigned long *)(desc + 0xc0) = (unsigned long)&_DAT_00688788;   /* LAB_00656fc4 */
        *(unsigned long *)(desc + 0xd0) = 0xc;
        *(unsigned long *)(desc + 0xd8) = (unsigned long)&_DAT_00688788;   /* LAB_00656fcc */
        *(unsigned long *)(desc + 0xe0) = (unsigned long)&_DAT_00688788;   /* LAB_00656fd4 */
        *(unsigned long *)(desc + 0xe8) = (unsigned long)&_DAT_00688788;   /* LAB_00656fdc */
        *(unsigned short *)(desc + 0xf0) = 0x1601;
        *(unsigned int *)(desc + 0xf4) = 3;
        *(unsigned long *)(desc + 0xf8) = (unsigned long)&_DAT_00688788;   /* LAB_00656fe4 */
        *(unsigned long *)(desc + 0x100) = (unsigned long)&_DAT_00688788;  /* LAB_00657004 */
        *(unsigned long *)(desc + 0x108) = (unsigned long)&_DAT_00688788;  /* LAB_00657020 */
        *(unsigned long *)(desc + 0x110) = (unsigned long)&_DAT_00688788;  /* LAB_00657038 */
        *(unsigned long *)(desc + 0x118) = (unsigned long)&_DAT_00688788;  /* LAB_00657040 */
        *(unsigned long *)(desc + 0x120) = (unsigned long)&sk_store_call120;   /* FUN_00657048 */
        *(unsigned long *)(desc + 0x128) = (unsigned long)&sk_store_call130;   /* FUN_0065716c */
        *(unsigned long *)(desc + 0x130) = (unsigned long)&_DAT_00688788;  /* LAB_00657074 */
        *(unsigned long *)(desc + 0x138) = (unsigned long)&sk_store_call138;   /* FUN_0065719c */
        *(unsigned short *)(desc + 0x149) = 0x1701;
        *(unsigned int *)(desc + 0x14c) = 1;
        *(unsigned long *)(desc + 0x150) = (unsigned long)&_DAT_00688788;  /* LAB_00657090 */
        *(unsigned long *)(desc + 0x158) = (unsigned long)&_DAT_00688788;  /* LAB_006570b0 */
        *(unsigned long *)(desc + 0x160) = (unsigned long)&sk_store_call160;   /* FUN_006571cc */
        *(unsigned long *)(desc + 0x168) = (unsigned long)&_DAT_00688788;  /* LAB_006570d0 */
        *(unsigned long *)(desc + 0x170) = (unsigned long)&_DAT_00688788;  /* LAB_00657118 */
        *(unsigned char *)(desc + 0x140) = 1;
        *(unsigned int *)(desc + 0x144) = 5;
        *(unsigned char *)(desc + 0x148) = 1;
        *(unsigned char *)(desc + 0x178) = 0x19;
        *(unsigned long *)(desc + 0x180) = (unsigned long)&_DAT_006887c0;
        *(unsigned long *)(desc + 0x188) = (unsigned long)&_DAT_00688888;
        *(unsigned long *)(desc + 400) = 0x6b4880;
        *(unsigned long *)(desc + 0x198) = (unsigned long)&_DAT_00688788;  /* LAB_00657158 */
        *(unsigned long *)(desc + 0x1a0) = (unsigned long)&_DAT_00688788;  /* LAB_00657160 */
        *(unsigned char *)(desc + 0x1a8) = 1;
        *(unsigned long *)(desc + 0x1b0) = 0;
        *(int *)(desc + 0x1b8) = (int)_DAT_006887a8;
    }
    return type == 2;
}

/* FUN_00657048 @ 0x00657048  (est. sk_store_call120)
 * Ghidra: void FUN_00657048(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Supervisor-call message send: writes three words into the per-CPU message area and
 * issues CallSupervisor(0).
 * Confidence: high (CallSupervisor matched) */
static void sk_store_call120(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long *m;

    m = (unsigned long *)tpidrro_el0;
    m[0] = b;
    m[1] = c;
    m[2] = d;
    CallSupervisor(0);
    m[0] = b;
}

/* FUN_0065716c @ 0x0065716c  (est. sk_store_call130)
 * Ghidra: void FUN_0065716c(long param_1)
 * Supervisor-call loop: repeats CallSupervisor(0) while param_1 == 1.
 * Confidence: high */
static void sk_store_call130(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_0065719c @ 0x0065719c  (est. sk_store_call138)
 * Ghidra: void FUN_0065719c(long param_1)
 * Supervisor-call loop: repeats CallSupervisor(0) while param_1 == 1.
 * Confidence: high */
static void sk_store_call138(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_006571cc @ 0x006571cc  (est. sk_store_call160)
 * Ghidra: void FUN_006571cc(long param_1, undefined8 param_2)
 * Supervisor-call loop with a message word: repeats CallSupervisor(0) while param_1
 * == 1.
 * Confidence: high */
static void sk_store_call160(long loop, unsigned long word)
{
    unsigned long *m;

    m = (unsigned long *)tpidrro_el0;
    m[0] = word;
    do {
        CallSupervisor(0);
        m[0] = word;
    } while (loop == 1);
}

/* FUN_00657200 @ 0x00657200  (est. sk_store_desc1)
 * Ghidra: bool FUN_00657200(long param_1, long param_2)
 * Initializes an object-store descriptor block for descriptor type 1 (a scheduler /
 * per-CPU store). Fills the method table, type tag (0x6a5ed4), slot table pointer
 * (DAT_00688950) and vtable entries. Returns (param_1 == 1).
 * Confidence: medium */
static int sk_store_desc1(long type, long desc)
{
    if (type == 1) {
        *(unsigned long *)(desc + 8) = 1;
        *(unsigned long *)(desc + 0x10) = 0x6a5ed4;
        *(unsigned char *)(desc + 0x18) = 0;
        *(unsigned int *)(desc + 0x1c) = 0xffffffff;
        *(unsigned char *)(desc + 0x20) = 0;
        *(unsigned long *)(desc + 0x28) = 0;
        *(unsigned char *)(desc + 0x30) = 1;
        *(unsigned int *)(desc + 0x34) = 3;
        *(int *)(desc + 0x38) = (int)_DAT_006887b0;
        *(unsigned long *)(desc + 0x40) = (unsigned long)&_DAT_00657578;
        *(unsigned long *)(desc + 0x48) = (unsigned long)&_DAT_00657590;
        *(unsigned long *)(desc + 0x50) = (unsigned long)&_DAT_006575a8;
        *(unsigned long *)(desc + 0x58) = (unsigned long)&sk_store_call58;    /* FUN_00657850 */
        *(unsigned long *)(desc + 0x60) = (unsigned long)&_DAT_006575c4;
        *(unsigned long *)(desc + 0x68) = (unsigned long)&sk_store_call68;    /* FUN_00657880 */
        *(unsigned long *)(desc + 0x70) = 0x6575dc;
        *(unsigned long *)(desc + 0x78) = (unsigned long)&_DAT_00657614;
        *(unsigned long *)(desc + 0x80) = (unsigned long)&_DAT_0065762c;
        *(unsigned long *)(desc + 0x88) = (unsigned long)&_DAT_00657644;
        *(unsigned long *)(desc + 0x90) = (unsigned long)&_DAT_0065766c;
        *(unsigned long *)(desc + 0x98) = (unsigned long)&sk_store_call98;    /* FUN_006578b0 */
        *(unsigned char *)(desc + 0xa0) = 1;
        *(unsigned int *)(desc + 0xa4) = 4;
        *(unsigned long *)(desc + 0xa8) = (unsigned long)&_DAT_00688788;      /* LAB_00657690 */
        *(unsigned long *)(desc + 0xb0) = (unsigned long)&_DAT_00688788;      /* LAB_00657698 */
        *(unsigned long *)(desc + 0xb8) = (unsigned long)&_DAT_00688788;      /* LAB_006576a0 */
        *(unsigned long *)(desc + 0xc0) = (unsigned long)&_DAT_00688788;      /* LAB_006576a8 */
        *(unsigned long *)(desc + 0xd0) = 0xc;
        *(unsigned long *)(desc + 0xd8) = (unsigned long)&_DAT_00688788;      /* LAB_006576b0 */
        *(unsigned long *)(desc + 0xe0) = (unsigned long)&_DAT_00688788;      /* LAB_006576b8 */
        *(unsigned long *)(desc + 0xe8) = (unsigned long)&_DAT_00688788;      /* LAB_006576c0 */
        *(unsigned short *)(desc + 0xf0) = 0x1601;
        *(unsigned int *)(desc + 0xf4) = 3;
        *(unsigned long *)(desc + 0xf8) = (unsigned long)&_DAT_006576c8;
        *(unsigned long *)(desc + 0x100) = (unsigned long)&_DAT_006576e8;
        *(unsigned long *)(desc + 0x108) = (unsigned long)&_DAT_00657704;
        *(unsigned long *)(desc + 0x110) = (unsigned long)&_DAT_0065771c;
        *(unsigned long *)(desc + 0x118) = (unsigned long)&_DAT_00657724;
        *(unsigned long *)(desc + 0x120) = (unsigned long)&sk_store_call120b; /* FUN_0065772c */
        *(unsigned long *)(desc + 0x128) = (unsigned long)&sk_store_call128b; /* FUN_006578e0 */
        *(unsigned long *)(desc + 0x130) = (unsigned long)&_DAT_00688788;     /* LAB_00657758 */
        *(unsigned long *)(desc + 0x138) = (unsigned long)&sk_store_call138b; /* FUN_00657910 */
        *(unsigned short *)(desc + 0x149) = 0x1701;
        *(unsigned int *)(desc + 0x14c) = 1;
        *(unsigned long *)(desc + 0x150) = (unsigned long)&_DAT_00657774;
        *(unsigned long *)(desc + 0x158) = 0x657794;
        *(unsigned long *)(desc + 0x160) = (unsigned long)&sk_store_call160b; /* FUN_00657940 */
        *(unsigned long *)(desc + 0x168) = 0x6577b4;
        *(unsigned long *)(desc + 0x170) = 0x6577fc;
        *(unsigned char *)(desc + 0x140) = 1;
        *(unsigned int *)(desc + 0x144) = 5;
        *(unsigned char *)(desc + 0x148) = 0;
        *(unsigned char *)(desc + 0x178) = 0x1a;
        *(unsigned long *)(desc + 0x180) = (unsigned long)&_DAT_00688950;
        *(unsigned long *)(desc + 0x188) = (unsigned long)&_DAT_00688a20;
        *(unsigned long *)(desc + 400) = 0x6b4948;
        *(unsigned long *)(desc + 0x198) = (unsigned long)&_DAT_00688788;     /* LAB_0065783c */
        *(unsigned long *)(desc + 0x1a0) = (unsigned long)&_DAT_00688788;     /* LAB_00657844 */
        *(unsigned char *)(desc + 0x1a8) = 1;
        *(unsigned long *)(desc + 0x1b0) = 1;
        *(unsigned int *)(desc + 0x1b8) = 0;
    }
    return type == 1;
}

/* FUN_0065772c @ 0x0065772c  (est. sk_store_call120b)
 * Ghidra: void FUN_0065772c(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Supervisor-call message send: writes three words and issues CallSupervisor(0).
 * Confidence: high */
static void sk_store_call120b(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long *m;

    m = (unsigned long *)tpidrro_el0;
    m[0] = b;
    m[1] = c;
    m[2] = d;
    CallSupervisor(0);
    m[0] = b;
}

/* FUN_00657850 @ 0x00657850  (est. sk_store_call58)
 * Ghidra: void FUN_00657850(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call58(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_00657880 @ 0x00657880  (est. sk_store_call68)
 * Ghidra: void FUN_00657880(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call68(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_006578b0 @ 0x006578b0  (est. sk_store_call98)
 * Ghidra: void FUN_006578b0(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call98(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_006578e0 @ 0x006578e0  (est. sk_store_call128b)
 * Ghidra: void FUN_006578e0(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call128b(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_00657910 @ 0x00657910  (est. sk_store_call138b)
 * Ghidra: void FUN_00657910(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call138b(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_00657940 @ 0x00657940  (est. sk_store_call160b)
 * Ghidra: void FUN_00657940(long param_1, undefined8 param_2)
 * Supervisor-call loop with a message word while param_1 == 1.
 * Confidence: high */
static void sk_store_call160b(long loop, unsigned long word)
{
    unsigned long *m;

    m = (unsigned long *)tpidrro_el0;
    m[0] = word;
    do {
        CallSupervisor(0);
        m[0] = word;
    } while (loop == 1);
}

/* FUN_00657974 @ 0x00657974  (est. sk_store_desc0x100000001)
 * Ghidra: bool FUN_00657974(long param_1, long param_2)
 * Initializes an object-store descriptor block for descriptor type 0x100000001 (a
 * third store class). Fills the method table, type tag (0x6a5ed4) and slot table
 * pointer (DAT_00688af0). Returns (param_1 == 0x100000001).
 * Confidence: medium */
static int sk_store_desc0x100000001(long type, long desc)
{
    if (type == 0x100000001) {
        *(unsigned long *)(desc + 8) = 0x100000001;
        *(unsigned long *)(desc + 0x10) = 0x6a5ed4;
        *(unsigned char *)(desc + 0x18) = 0;
        *(unsigned int *)(desc + 0x1c) = 0xffffffff;
        *(unsigned char *)(desc + 0x20) = 0;
        *(unsigned long *)(desc + 0x28) = 0;
        *(unsigned char *)(desc + 0x30) = 1;
        *(unsigned int *)(desc + 0x34) = 3;
        *(int *)(desc + 0x38) = (int)_DAT_006887b0;
        *(unsigned long *)(desc + 0x40) = (unsigned long)&_DAT_00657cf0;
        *(unsigned long *)(desc + 0x48) = (unsigned long)&_DAT_00657d08;
        *(unsigned long *)(desc + 0x50) = (unsigned long)&_DAT_00657d20;
        *(unsigned long *)(desc + 0x58) = (unsigned long)&sk_store_call58c;   /* FUN_00657fc8 */
        *(unsigned long *)(desc + 0x60) = (unsigned long)&_DAT_00657d3c;
        *(unsigned long *)(desc + 0x68) = (unsigned long)&sk_store_call68c;   /* FUN_00657ff8 */
        *(unsigned long *)(desc + 0x70) = (unsigned long)&_DAT_00657d54;
        *(unsigned long *)(desc + 0x78) = (unsigned long)&_DAT_00657d8c;
        *(unsigned long *)(desc + 0x80) = (unsigned long)&_DAT_00657da4;
        *(unsigned long *)(desc + 0x88) = (unsigned long)&_DAT_00657dbc;
        *(unsigned long *)(desc + 0x90) = (unsigned long)&_DAT_00657de4;
        *(unsigned long *)(desc + 0x98) = (unsigned long)&sk_store_call98c;   /* FUN_00658028 */
        *(unsigned char *)(desc + 0xa0) = 1;
        *(unsigned int *)(desc + 0xa4) = 4;
        *(unsigned long *)(desc + 0xa8) = (unsigned long)&_DAT_00657e08;
        *(unsigned long *)(desc + 0xb0) = (unsigned long)&_DAT_00657e10;
        *(unsigned long *)(desc + 0xb8) = (unsigned long)&_DAT_00657e18;
        *(unsigned long *)(desc + 0xc0) = (unsigned long)&_DAT_00657e20;
        *(unsigned long *)(desc + 0xd0) = 0xc;
        *(unsigned long *)(desc + 0xd8) = (unsigned long)&_DAT_00657e28;
        *(unsigned long *)(desc + 0xe0) = (unsigned long)&_DAT_00657e30;
        *(unsigned long *)(desc + 0xe8) = (unsigned long)&_DAT_00657e38;
        *(unsigned short *)(desc + 0xf0) = 0x1601;
        *(unsigned int *)(desc + 0xf4) = 3;
        *(unsigned long *)(desc + 0xf8) = (unsigned long)&_DAT_00657e40;
        *(unsigned long *)(desc + 0x100) = (unsigned long)&_DAT_00657e60;
        *(unsigned long *)(desc + 0x108) = (unsigned long)&_DAT_00657e7c;
        *(unsigned long *)(desc + 0x110) = 0x657e94;
        *(unsigned long *)(desc + 0x118) = (unsigned long)&_DAT_00657e9c;
        *(unsigned long *)(desc + 0x120) = (unsigned long)&sk_store_call120c;  /* FUN_00657ea4 */
        *(unsigned long *)(desc + 0x128) = (unsigned long)&sk_store_call128c;  /* FUN_00658058 */
        *(unsigned long *)(desc + 0x130) = (unsigned long)&_DAT_00657ed0;
        *(unsigned long *)(desc + 0x138) = (unsigned long)&sk_store_call138c;  /* FUN_00658088 */
        *(unsigned short *)(desc + 0x149) = 0x1701;
        *(unsigned int *)(desc + 0x14c) = 1;
        *(unsigned long *)(desc + 0x150) = (unsigned long)&_DAT_00657eec;
        *(unsigned long *)(desc + 0x158) = (unsigned long)&_DAT_00657f0c;
        *(unsigned long *)(desc + 0x160) = (unsigned long)&sk_store_call160c;  /* FUN_006580b8 */
        *(unsigned long *)(desc + 0x168) = (unsigned long)&_DAT_00657f2c;
        *(unsigned long *)(desc + 0x170) = (unsigned long)&_DAT_00657f74;
        *(unsigned char *)(desc + 0x140) = 1;
        *(unsigned int *)(desc + 0x144) = 5;
        *(unsigned char *)(desc + 0x148) = 0;
        *(unsigned char *)(desc + 0x178) = 0x1a;
        *(unsigned long *)(desc + 0x180) = (unsigned long)&_DAT_00688af0;
        *(unsigned long *)(desc + 0x188) = (unsigned long)&_DAT_00688bc0;
        *(unsigned long *)(desc + 400) = 0x6b4a18;
        *(unsigned long *)(desc + 0x198) = (unsigned long)&_DAT_00657fb4;
        *(unsigned long *)(desc + 0x1a0) = (unsigned long)&_DAT_00657fbc;
        *(unsigned char *)(desc + 0x1a8) = 1;
        *(unsigned long *)(desc + 0x1b0) = 1;
        *(unsigned int *)(desc + 0x1b8) = 0;
    }
    return type == 0x100000001;
}

/* FUN_00657ea4 @ 0x00657ea4  (est. sk_store_call120c)
 * Ghidra: void FUN_00657ea4(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Supervisor-call message send: writes three words and issues CallSupervisor(0).
 * Confidence: high */
static void sk_store_call120c(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long *m;

    m = (unsigned long *)tpidrro_el0;
    m[0] = b;
    m[1] = c;
    m[2] = d;
    CallSupervisor(0);
    m[0] = b;
}

/* FUN_00657fc8 @ 0x00657fc8  (est. sk_store_call58c)
 * Ghidra: void FUN_00657fc8(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call58c(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_00657ff8 @ 0x00657ff8  (est. sk_store_call68c)
 * Ghidra: void FUN_00657ff8(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call68c(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_00658028 @ 0x00658028  (est. sk_store_call98c)
 * Ghidra: void FUN_00658028(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call98c(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_00658058 @ 0x00658058  (est. sk_store_call128c)
 * Ghidra: void FUN_00658058(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call128c(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_00658088 @ 0x00658088  (est. sk_store_call138c)
 * Ghidra: void FUN_00658088(long param_1)
 * Supervisor-call loop while param_1 == 1.
 * Confidence: high */
static void sk_store_call138c(long loop)
{
    unsigned long *m;
    unsigned long saved;

    m = (unsigned long *)tpidrro_el0;
    saved = m[0];
    do {
        CallSupervisor(0);
        m[0] = saved;
    } while (loop == 1);
}

/* FUN_006580b8 @ 0x006580b8  (est. sk_store_call160c)
 * Ghidra: void FUN_006580b8(long param_1, undefined8 param_2)
 * Supervisor-call loop with a message word while param_1 == 1.
 * Confidence: high */
static void sk_store_call160c(long loop, unsigned long word)
{
    unsigned long *m;

    m = (unsigned long *)tpidrro_el0;
    m[0] = word;
    do {
        CallSupervisor(0);
        m[0] = word;
    } while (loop == 1);
}

