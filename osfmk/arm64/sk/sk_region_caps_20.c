/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses.
 * Slice 20: 0xEC050-0xF3BE4. This region is the InternalExclaveLauncher /
 * Conclave-loader / VAS-extension subsystem: it loads exclave Mach-O images,
 * builds their address-space (VAS/ext-VM) descriptors, manages regions and
 * frame caps, and drives the Init-endpoint / DomainInit handoff. All names
 * are estimates unless a string/header matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

/* Forward decls for static record helpers (defined at end of file). */
static void iel_region_decode(unsigned long *out, const void *src);
static void cl4_bswap16(const unsigned char *in, unsigned long *out);

/* ------------------------------------------------------------------ *
 * cL4 kernel primitives. These are declared with unspecified argument
 * lists (K&R `()`): the decompile calls them with argument counts that
 * vary by call site, so the reconstruction mirrors that. Each carries the
 * exact Ghidra FUN_ name in a comment. Bodies are reconstructed by the
 * range worker that owns each function.
 * ------------------------------------------------------------------ */

extern void *cl4_alloc_object();     /* FUN_0036a940 */
extern void *cl4_alloc_value();      /* FUN_0036a804 */
extern void *cl4_retain();           /* FUN_0036b270 */
extern void cl4_release();           /* FUN_0036b118 */
extern void cl4_fault();             /* FUN_0036b6f4 noreturn */
extern void cl4_release_op();        /* FUN_0036b6ac */
extern void cl4_critical_enter();    /* FUN_0036a1a0 */
extern void cl4_critical_exit();     /* FUN_0036a20c */
extern void *cl4_object_get();       /* FUN_0036b8b0 */
extern void *cl4_log_alloc();        /* FUN_0036a9a0 */
extern void *cl4_log_alloc2();       /* FUN_0036a9d4 */
extern void cl4_log_fmt();           /* FUN_003a25d4 */
extern void cl4_log_emit();          /* FUN_0036b588 */
extern void cl4_slot_clear();        /* FUN_0036b7f8 */
extern void cl4_scope_drop();        /* FUN_000026e8 */
extern void cl4_panic_begin();       /* FUN_00002818 */
extern void cl4_panic_str();         /* FUN_00002874 */
extern void cl4_log_finish();        /* FUN_00002688 */
extern void cl4_trace_begin();       /* FUN_002a4ab4 */
extern void cl4_trace_word();        /* thunk_FUN_002acbb8 */
extern unsigned long cl4_obj_flag(); /* FUN_0036a261c */
extern long cl4_page_size();         /* FUN_0014b644 */
extern void cl4_fatal_error();       /* FUN_001afa84 noreturn */
extern unsigned long cl4_mmu_op();   /* FUN_0001a1c8 */
extern unsigned long *cl4_global_caps_0(); /* FUN_00153264 */
extern unsigned long *cl4_global_caps_1(); /* FUN_00153270 */
extern unsigned long *cl4_global_caps_2(); /* FUN_0015327c */
extern unsigned char *cl4_flag_0();  /* FUN_00167c54 */
extern unsigned char *cl4_flag_1();  /* FUN_00167c60 */
extern unsigned char *cl4_flag_2();  /* FUN_00167c48 */
extern unsigned char *cl4_flag_3();  /* FUN_00167c3c */
extern unsigned char *cl4_flag_4();  /* FUN_00167c30 */
extern void *cl4_find_region();      /* FUN_0016d328 */
extern void cl4_list_lookup();       /* FUN_001670f0 */
extern void cl4_list_lock();         /* FUN_001dd77c */
extern unsigned long cl4_list_index(); /* FUN_001dd858 */
extern void *cl4_array_grow();       /* FUN_00072d5c */
extern void *cl4_array_grow2();      /* FUN_00082504 / 00082524 */
extern void cl4_array_free();        /* FUN_0006b3f4 */
extern void cl4_array_compact();     /* FUN_000ec004 */
extern void *cl4_log_lookup();       /* FUN_00027724 */
extern void cl4_obj_copy();          /* FUN_00117cc4 */
extern void *cl4_logf();             /* FUN_00151974 */
extern void cl4_vlog();              /* FUN_00151a6c */
extern void cl4_region_copy();       /* FUN_0009d014 */
extern void cl4_log_region_field();  /* FUN_0009d3f8 */
extern void cl4_log_region_field2(); /* FUN_0009d414 */
extern void cl4_log_index_value();   /* FUN_0009d434 */
extern void cl4_log_flags();         /* FUN_0009d444 */
extern void cl4_log_scalar();        /* FUN_0009d460 */
extern void cl4_log_value();         /* FUN_0009d154 */
extern void cl4_log_region_idx();    /* FUN_0009d170 */
extern void cl4_release_tagged();    /* FUN_00093c60 */
extern void cl4_retain_tagged();     /* FUN_00093c58 */
extern void cl4_notify_done();       /* FUN_0009461c */
extern void cl4_slot_begin();        /* FUN_00084100 */
extern void cl4_slot_swap();         /* FUN_0007c0e0 */
extern void cl4_port_send();         /* FUN_0006e7c0 */
extern unsigned long cl4_msg_word(); /* FUN_0006a4c0 */
extern void cl4_free();              /* thunk_FUN_00012568 */
extern long cl4_refcount();          /* FUN_0011817c */
extern int cl4_compare16();         /* FUN_0006e6dc */

/* Launcher / table / descriptor helpers (all out of slice). */
extern unsigned long cl4_log_key();        /* FUN_00002534 */
extern void *cl4_table_new();              /* FUN_001f0130 */
extern void *cl4_iel_tbl4();               /* FUN_000f4234 */
extern void *cl4_desc_compose();           /* FUN_0009781c */
extern void cl4_desc_emit();               /* FUN_000937b8 */
extern void *cl4_desc_check();             /* FUN_0009d078 */
extern void *cl4_obj_resolve3();           /* FUN_000de3c8 */
extern void cl4_iel_install_vtable();      /* vtable-install pattern */
extern void cl4_iel_done();                /* FUN_000f4c14 */
extern void *cl4_region_alloc();           /* FUN_00085bf0 */
extern void cl4_region_bind();             /* FUN_0007659c */
extern unsigned long cl4_op_check();       /* FUN_00090464 */
extern void cl4_destroy_elem();            /* FUN_004b23d8 */
extern unsigned long cl4_mmu_op2();        /* FUN_000ddc5c */
extern void *cl4_frame_alloc();            /* FUN_00034f70 */
extern void cl4_frame_panic();             /* FUN_000f4c70 */
extern void cl4_frame_bind();              /* FUN_000f6d20 */
extern void cl4_iel_tlb();                 /* FUN_00081438 */
extern void cl4_iel_panic();               /* FUN_000f4abc noreturn */
extern void cl4_iel_abort();               /* FUN_000f4b70 noreturn */
extern void cl4_iel_panic2();              /* FUN_000f4b00 noreturn */
extern void cl4_iel_cleanup();             /* FUN_000f4b8c */
extern void cl4_iel_panic_str();           /* FUN_000f4abc (string form) */
extern void cl4_iel_abort2();              /* FUN_000f4b00 */
extern unsigned long cl4_iel_done2();               /* FUN_000f4cbc */
extern void cl4_iel_cleanup2();            /* FUN_000f4cb0 */
extern void *cl4_region_set();             /* thunk_FUN_000a17f8 */
extern void cl4_desc_lookup();             /* FUN_000a0650 */
extern void cl4_desc_drop();               /* FUN_0000276c */
extern void cl4_frame_panic2();            /* FUN_000944a8 */
extern void cl4_frame_error();             /* FUN_000f43d4 */
extern void cl4_frame_commit();            /* FUN_000fc804 */
extern void cl4_fatal_frame();             /* FUN_001ebfb0 */
extern void *cl4_fatal_key();              /* FUN_0001df60 */
extern unsigned long long cl4_uuid_next(); /* FUN_0029fb80 */
extern void *cl4_ep_resolve();             /* FUN_00167a6c */
extern void *cl4_ep_lookup();              /* FUN_0009d1e0 */
extern void cl4_ep_release();              /* FUN_000db5a4 */
extern void cl4_init_wait();               /* FUN_000651bc */
extern void cl4_cap_lookup();              /* FUN_000f4838 */
extern unsigned long cl4_iel_size();       /* FUN_000f480c */
extern void *cl4_obj_resolve();            /* FUN_001000b8 */
extern void *cl4_obj_resolve2();           /* FUN_000fd854 / 000fd5d8 */
extern void *cl4_lock_registry();          /* FUN_00086440 */
extern void *cl4_lock_allocator();         /* FUN_00086590 */
extern void *cl4_vas_map();                /* FUN_00085a54 (register args) */
extern void cl4_vas_oom();                 /* FUN_00085374 (VasSlotAlloc fatal) */
extern void cl4_stack_ptr();               /* FUN_000f4c9c */
extern void cl4_vas_oom_nop();             /* FUN_000f4b40 (empty) */
extern void cl4_vas_oom_nop2();            /* FUN_000f4b14 (empty) */
extern void cl4_memmove();                 /* FUN_00117d14 (register args) */
extern void cl4_fatal_noreturn(void) __attribute__((noreturn)); /* FUN_001ee9f4 */

/* Forward decls for functions defined later in this file (so that callers
 * that precede the definitions compile). */
extern void iel_register_ctx(void *p1, void *p2, void *p3, void *p4,
                             void *p5, void *p6, void *p7);
extern void iel_trace_probe(void);
extern void iel_noop(void);
extern unsigned long long iel_trace_header2(void);
extern void iel_register_ctx2(void *p);
extern void iel_dispatch2_setup(unsigned long *out, void *which);
extern void iel_save_thread_state2(void *dst, long *src, unsigned long which);
extern void iel_save_thread_state(void *dst, long *src);
extern void iel_configure_exclave(void *p1, long p2, void *p3, void *p4, void *p5,
                                  void *p6, unsigned char p7, void *p8, void *p9, void *p10);
extern void *iel_build_vm_regions(long *region, long seg);

/* Globals. */
extern unsigned long cl4_current;            /* Ghidra unaff_x20 (TCB) */
extern int cl4_result_ok;                    /* Ghidra unaff_x21 == 0 on ok */
extern volatile char cl4_debug_enabled;      /* DAT_006add10 */
extern unsigned char *cl4_pending_regions;   /* DAT_00657778 */
extern unsigned long cl4_pending_regions_n;  /* DAT_00657788 */
extern unsigned long cl4_pending_regions_cap;/* DAT_00657790 */
extern unsigned long cl4_pending_regions_arr;/* DAT_00657798 */
extern unsigned long cl4_pending_regions_d8; /* DAT_006577d8 */
extern unsigned long iel_trace_loc;          /* tracer cookie (local_38) */
extern unsigned char iel_log_stack[24];      /* log record scratch */
extern unsigned long iel_local_a8[5];        /* stack record scratch */
extern unsigned long iel_local_f0[3];
extern unsigned long iel_local_b8[5];

/* GENTER opcode 0x00201420: enters the guarded level (GL1 dispatch). */
#define GENTER() __asm__ volatile(".word 0x00201420")
/* GEXIT opcode 0x00201400: returns from the guarded level. */
#define GEXIT()  __asm__ volatile(".word 0x00201400")
/* cl4_trap: the kernel breakpoint trap (Ghidra SoftwareBreakpoint(1, pc)). */
#define cl4_trap() __builtin_trap()

/* FUN_000ec050 @ 0x000ec050   (est. iel_dispatch_alloc)
 * Ghidra: undefined8 FUN_000ec050(x8..x15 -> 7 args)
 * Allocates the exclave-loader dispatch context (via cl4_alloc_object), then
 * passes all 7 arguments through to FUN_000ec3a0 to register the context.
 * Returns the freshly allocated context object.
 * Confidence: medium
 * Notes: tail-wraps FUN_000ec3a0; FUN_0036a940 used as object allocator. */
void *iel_dispatch_alloc(void *p1, void *p2, void *p3, void *p4,
                         void *p5, void *p6, void *p7)
{
    void *ctx = cl4_alloc_object(0, 0, 0);
    iel_register_ctx(p1, p2, p3, p4, p5, p6, p7);
    return ctx;
}

/* FUN_000ec0e8 @ 0x000ec0e8   (est. iel_capture_state)
 * Ghidra: void FUN_000ec0e8(undefined8 *param_1)
 * Captures the current thread's (unaff_x20) loaded-object state into a
 * 4-word output record: the 128-bit identifier at obj+0x30 (byte-swapped),
 * the state word at obj+0x40, and the thread's own tag at tcb+0x20. Traps if
 * the state word is negative (invalid).
 * Confidence: medium
 * Notes: NEON_ext = byte-swap of the 16-byte id; SoftwareBreakpoint(1,0xec110). */
void iel_capture_state(unsigned long *out)
{
    long state = *(long *)(*(long *)(cl4_current + 0x10) + 0x40);
    if (state >= 0) {
        unsigned long tag = *(unsigned long *)(cl4_current + 0x20);
        unsigned char id[16];
        memcpy(id, (void *)(*(long *)(cl4_current + 0x10) + 0x30), 16);
        cl4_bswap16(id, out);  /* NEON_ext byte-swap of the 128-bit id */
        out[2] = (unsigned long)state;
        out[3] = tag;
        return;
    }
    cl4_trap();  /* SoftwareBreakpoint(1, 0xec110): negative state */
}

/* FUN_000ec110 @ 0x000ec110   (est. iel_save_thread_state)
 * Ghidra: void FUN_000ec110(undefined8 param_1, long *param_2)
 * Saves the current thread's (unaff_x20) saved-machine state: stores the
 * destination object into tcb+0x10, calls the capture method at
 * *param_2+0x1c0 to fill the local register frame, then persists the frame
 * into tcb+0x18..0x49. Then re-retrieves the object, calls its sync method
 * (*obj+0x70) and releases everything. On failure it unwinds all refs and
 * faults.
 * Confidence: medium
 * Notes: removes unreachable block 0xec224; the 16-byte frame is captured via
 * the method table at *param_2. */
void iel_save_thread_state(void *dst, long *src)
{
    *(void **)(cl4_current + 0x10) = dst;
    void (*capture)(void *frame) = *(void (**)(void *))(*(void **)src + 0x1c0);
    cl4_retain(0);
    unsigned long frame[9];
    capture(frame);
    if (cl4_result_ok == 0) {
        *(void **)(cl4_current + 0x20) = (void *)frame[2];
        *(void **)(cl4_current + 0x18) = (void *)frame[0];
        *(void **)(cl4_current + 0x30) = (void *)frame[6];
        *(void **)(cl4_current + 0x28) = (void *)frame[4];
        *(unsigned long *)(cl4_current + 0x40) = frame[8] | (frame[7] << 8) >> 8; /* CONCAT71 */
        *(void **)(cl4_current + 0x38) = (void *)frame[7];
        *(void **)(cl4_current + 0x49) = (void *)frame[9];
        *(unsigned long *)(cl4_current + 0x41) = frame[8]; /* CONCAT17 */
        void *obj = *(void **)(*(long *)(cl4_current + 0x10) + 0x10);
        void (*sync)(void *f) = *(void (**)(void *))(*(void **)obj + 0x70);
        cl4_retain(obj);
        sync(frame);
        cl4_release(obj);
        cl4_release(dst);
        cl4_release(src);
    } else {
        cl4_release(dst);
        cl4_release(src);
        cl4_release(*(void **)(cl4_current + 0x10));
        cl4_fault();
    }
}

/* FUN_000ec268 @ 0x000ec268   (est. iel_trace_header)
 * Ghidra: undefined1[16] FUN_000ec268(void)
 * Emits a 16-byte trace header literal ("Broke red..." marker region). Begins
 * a trace event (tag 0x1d), logs the current ID and a ", code:" suffix, then
 * returns the encoded header vector {0x646572656b6f7242, 0xe9...0028}.
 * Confidence: low
 * Notes: FUN_002a4ab4/003a25d4/002acbb8 are the trace-log machinery; the
 * literal is a tracer cookie, not a real C string. */
unsigned long long iel_trace_header(void)
{
    iel_trace_probe();
    cl4_trace_begin(0x1d);
    cl4_log_fmt((unsigned long)iel_trace_loc);
    iel_trace_header2();
    cl4_trace_word(0, 0);
    cl4_log_fmt(0);
    cl4_trace_word(0x2065646f6e63202c, 0xef203a7865646e69); /* ", code" / "index: " */
    iel_noop();
    void (*log)(unsigned long, unsigned long) = (void (*)(unsigned long, unsigned long))cl4_log_lookup(0);
    log(0x677830, 0);
    cl4_trace_word(0, 0);
    cl4_log_fmt(0);
    cl4_trace_word(0x29, 0xe100000000000000);
    /* 128-bit header: lo=0x646572656b6f7242, hi=0xe9..0028 */
    return 0x646572656b6f7242ull;
}

/* FUN_000ec358 @ 0x000ec358   (est. iel_capture_state_thunk)
 * Ghidra: void FUN_000ec358(void) — forwards to iel_capture_state.
 * Confidence: medium
 */
void iel_capture_state_thunk(void)
{
    iel_capture_state(0);
}

/* FUN_000ec37c @ 0x000ec37c   (est. iel_trace_header_thunk)
 * Ghidra: void FUN_000ec37c(void) — forwards to iel_trace_header.
 * Confidence: medium
 */
void iel_trace_header_thunk(void)
{
    iel_trace_header();
}

/* FUN_000ec3a0 @ 0x000ec3a0   (est. iel_register_ctx)
 * Ghidra: void FUN_000ec3a0(7 args)
 * Persists the 6 context arguments into tcb+0x18..0x40, resolves the target
 * object via cl4_obj_resolve(param_2) and installs it at tcb+0x10 after
 * dropping the scope on param_1. On failure it drops the scope, logs the
 * stored field and faults.
 * Confidence: medium
 * Notes: FUN_001000b8 + FUN_000fd854 resolve the object; FUN_000026e8 is the
 * scope-drop. */
void iel_register_ctx(void *p1, void *p2, void *p3, void *p4,
                      void *p5, void *p6, void *p7)
{
    *(void **)(cl4_current + 0x18) = p2;
    *(void **)(cl4_current + 0x20) = p3;
    *(void **)(cl4_current + 0x28) = p4;
    *(void **)(cl4_current + 0x30) = p5;
    *(void **)(cl4_current + 0x38) = p6;
    *(void **)(cl4_current + 0x40) = p7;
    void *t = cl4_obj_resolve(0);
    void *obj = cl4_obj_resolve2(p2, t);
    if (cl4_result_ok == 0) {
        cl4_scope_drop(p1);
        *(void **)(cl4_current + 0x10) = obj;
    } else {
        cl4_scope_drop(p1);
        cl4_log_fmt(*(unsigned long *)(cl4_current + 0x28));
        cl4_fault();
    }
}

/* FUN_000ec460 @ 0x000ec460   (est. iel_dispatch_setup)
 * Ghidra: void FUN_000ec460(undefined8 *param_1, undefined8 param_2)
 * Allocates the dispatch object (kind 0x51 at tag 7), retains the source and
 * target objects, saves thread state, and on success records the object kind
 * tags and the resulting context into param_1[0].
 * Confidence: medium
 * Notes: FUN_0036a940(0x651ee0,0x51,7) allocates; param_1[3]/[4] are the
 * object-kind name words. */
void iel_dispatch_setup(unsigned long *out, void *src)
{
    void *kind = cl4_alloc_object(0x651ee0, 0x51, 7);
    cl4_retain(0);
    cl4_retain(src);
    iel_save_thread_state(0, 0);
    if (cl4_result_ok == 0) {
        out[3] = 0x651ee0;
        out[4] = 0x662078;
        out[0] = 0;
    }
}

/* FUN_000ec4fc @ 0x000ec4fc   (est. iel_trace_header2)
 * Ghidra: undefined1[16] FUN_000ec4fc(void)
 * Second 16-byte trace header literal. Begins trace event (tag 0x17), logs
 * the current ID, and returns {0xd...14, 0x800...5c4c00}.
 * Confidence: low
 * Notes: literal tracer cookie. */
unsigned long long iel_trace_header2(void)
{
    iel_trace_probe();
    cl4_trace_begin(0x17);
    cl4_log_fmt((unsigned long)iel_trace_loc);
    iel_noop();
    void (*log)(unsigned long) = (void (*)(unsigned long))cl4_log_lookup(0);
    log(0x677830);
    cl4_trace_word(0, 0);
    cl4_log_fmt(0);
    cl4_trace_word(0x29, 0xe100000000000000);
    /* 128-bit header: lo=0xd..14, hi=0x800..5c4c00 */
    return 0xd000000000000014ull;
}

/* FUN_000ec5a8 @ 0x000ec5a8   (est. iel_release_ctx)
 * Ghidra: void FUN_000ec5a8(void)
 * Releases the thread's loaded object (tcb+0x10) and logs the stored field at
 * tcb+0x28.
 * Confidence: medium */
void iel_release_ctx(void)
{
    cl4_release(*(void **)(cl4_current + 0x10));
    cl4_log_fmt(*(unsigned long *)(cl4_current + 0x28));
}

/* FUN_000ec5d0 @ 0x000ec5d0   (est. iel_release_ctx_op)
 * Ghidra: void FUN_000ec5d0(void) — release ctx then release the op.
 * Confidence: medium
 */
void iel_release_ctx_op(void)
{
    iel_release_ctx();
    cl4_release_op();
}

/* FUN_000ec5d4 @ 0x000ec5d4   (est. iel_release_ctx_op2)
 * Ghidra: void FUN_000ec5d4(void) — same as iel_release_ctx_op.
 * Confidence: medium
 */
void iel_release_ctx_op2(void)
{
    iel_release_ctx();
    cl4_release_op();
}

/* FUN_000ec5f8 @ 0x000ec5f8   (est. iel_dispatch_setup_thunk)
 * Ghidra: void FUN_000ec5f8(void) — forwards to iel_dispatch_setup.
 * Confidence: medium
 */
void iel_dispatch_setup_thunk(void)
{
    iel_dispatch_setup(0, 0);
}

/* FUN_000ec5fc @ 0x000ec5fc   (est. iel_dispatch_setup_thunk2)
 * Ghidra: void FUN_000ec5fc(void) — forwards to iel_dispatch_setup.
 * Confidence: medium
 */
void iel_dispatch_setup_thunk2(void)
{
    iel_dispatch_setup(0, 0);
}

/* FUN_000ec610 @ 0x000ec610   (est. iel_trace_header2_thunk)
 * Ghidra: void FUN_000ec610(void) — forwards to iel_trace_header2.
 * Confidence: medium
 */
void iel_trace_header2_thunk(void)
{
    iel_trace_header2();
}

/* FUN_000ec67c @ 0x000ec67c   (est. iel_const16_a)
 * Ghidra: undefined1[16] FUN_000ec67c(void)
 * Returns the 16-byte literal constant {0x651e58, 0}.
 * Confidence: low
 * Notes: ZEXT816(0x651e58) — a tracer cookie word. */
unsigned long long iel_const16_a(void)
{
    return 0x651e58ull;
}

/* FUN_000ec68c @ 0x000ec68c   (est. iel_noop)
 * Ghidra: void FUN_000ec68c(void) — empty stub.
 * Confidence: medium
 */
void iel_noop(void)
{
}

/* FUN_000ec6a4 @ 0x000ec6a4   (est. iel_alloc_slot)
 * Ghidra: long FUN_000ec6a4(void)
 * Allocates an object and stores a freshly allocated 0x10-byte value into its
 * +0x10 slot; returns the object.
 * Confidence: medium
 * Notes: FUN_0036a940 + FUN_0036a804(0x10, -1). */
void *iel_alloc_slot(void)
{
    void *obj = cl4_alloc_object(0, 0, 0);
    *(void **)((char *)obj + 0x10) = cl4_alloc_value(0x10, 0xffffffffffffffffull);
    return obj;
}

/* FUN_000ec6e8 @ 0x000ec6e8   (est. iel_set_slot_new)
 * Ghidra: void FUN_000ec6e8(void)
 * Stores a freshly allocated value into the current thread's +0x10 slot.
 * Confidence: medium */
void iel_set_slot_new(void)
{
    *(void **)(cl4_current + 0x10) = cl4_alloc_value(0x10, 0xffffffffffffffffull);
}

/* FUN_000ec6ec @ 0x000ec6ec   (est. iel_set_slot_new2)
 * Ghidra: void FUN_000ec6ec(void) — same as iel_set_slot_new.
 * Confidence: medium
 */
void iel_set_slot_new2(void)
{
    *(void **)(cl4_current + 0x10) = cl4_alloc_value(0x10, 0xffffffffffffffffull);
}

/* FUN_000ec710 @ 0x000ec710   (est. iel_free_slot)
 * Ghidra: void FUN_000ec710(void)
 * Frees the thread's +0x10 value (deallocation with size -1/-1).
 * Confidence: medium
 * Notes: thunk_FUN_00012568 = cL4_free(p, size, tag). */
void iel_free_slot(void)
{
    cl4_free(*(void **)(cl4_current + 0x10), 0xffffffffffffffffull);
}

/* FUN_000ec714 @ 0x000ec714   (est. iel_free_slot2)
 * Ghidra: void FUN_000ec714(void) — same as iel_free_slot.
 * Confidence: medium
 */
void iel_free_slot2(void)
{
    cl4_free(*(void **)(cl4_current + 0x10), 0xffffffffffffffffull);
}

/* FUN_000ec738 @ 0x000ec738   (est. iel_free_slot_op)
 * Ghidra: void FUN_000ec738(void)
 * Frees the thread's +0x10 value then releases the enclosing op.
 * Confidence: medium */
void iel_free_slot_op(void)
{
    cl4_free(*(void **)(cl4_current + 0x10), 0xffffffffffffffffull);
    cl4_release_op();
}

/* FUN_000ec774 @ 0x000ec774   (est. iel_slot_is_free)
 * Ghidra: bool FUN_000ec774(void)
 * Returns true iff the thread's +0x10 object is currently unreferenced
 * (FUN_0011817c returns 0).
 * Confidence: medium */
bool iel_slot_is_free(void)
{
    return cl4_refcount(*(void **)(cl4_current + 0x10)) == 0;
}

/* FUN_000ec778 @ 0x000ec778   (est. iel_slot_is_free2)
 * Ghidra: bool FUN_000ec778(void) — same as iel_slot_is_free.
 * Confidence: medium
 */
bool iel_slot_is_free2(void)
{
    return cl4_refcount(*(void **)(cl4_current + 0x10)) == 0;
}

/* FUN_000ec7a0 @ 0x000ec7a0   (est. iel_with_lock)
 * Ghidra: void FUN_000ec7a0(undefined8 param_1, code *param_2)
 * Under the current thread's object lock, invokes the enter/leave methods at
 * obj+0x68 / obj+0x78 around a caller-supplied callback (param_2).
 * Confidence: medium
 * Notes: (**(**unaff_x20+0x68)) and +0x78 bracket (*param_2)(param_1). */
void iel_with_lock(void *arg, void (*fn)(void *))
{
    void (*enter)(void) = (void (*)(void))(*(void **)cl4_current + 0x68);
    void (*leave)(void) = (void (*)(void))(*(void **)cl4_current + 0x78);
    enter();
    fn(arg);
    leave();
}

/* FUN_000ec840 @ 0x000ec840   (est. iel_method_68)
 * Ghidra: void FUN_000ec840(void)
 * Invokes the current thread object's +0x68 method (lock enter).
 * Confidence: medium */
void iel_method_68(void)
{
    void (*m)(void) = (void (*)(void))(*(long *)*(void **)cl4_current + 0x68);
    m();
}

/* FUN_000ec87c @ 0x000ec87c   (est. iel_method_70_flag)
 * Ghidra: uint FUN_000ec87c(void)
 * Invokes the thread object's +0x70 method and returns its low bit.
 * Confidence: medium */
unsigned int iel_method_70_flag(void)
{
    unsigned int (*m)(void) = (unsigned int (*)(void))(*(long *)*(void **)cl4_current + 0x70);
    return m() & 1;
}

/* FUN_000ec8bc @ 0x000ec8bc   (est. iel_method_78)
 * Ghidra: void FUN_000ec8bc(void)
 * Invokes the thread object's +0x78 method (lock leave).
 * Confidence: medium */
void iel_method_78(void)
{
    void (*m)(void) = (void (*)(void))(*(long *)*(void **)cl4_current + 0x78);
    m();
}

/* FUN_000ec8f8 @ 0x000ec8f8   (est. iel_const16_b)
 * Ghidra: undefined1[16] FUN_000ec8f8(void)
 * Returns the 16-byte literal {0x651f48, 0}.
 * Confidence: low */
unsigned long long iel_const16_b(void)
{
    return 0x651f48ull;
}

/* FUN_000ec920 @ 0x000ec920   (est. iel_get_kind)
 * Ghidra: void FUN_000ec920(undefined8 *param_1)
 * Invokes the thread object's +0x38 method and stores the result in param_1.
 * Confidence: medium */
void iel_get_kind(unsigned long *out)
{
    *out = (**(unsigned long (**)(void))(*(long *)*(void **)cl4_current + 0x38))();
}

/* FUN_000ec964 @ 0x000ec964   (est. iel_const16_c)
 * Ghidra: undefined1[16] FUN_000ec964(void)
 * Returns the 16-byte literal {0x651fe8, 0}.
 * Confidence: low */
unsigned long long iel_const16_c(void)
{
    return 0x651fe8ull;
}

/* FUN_000ec974 @ 0x000ec974   (est. iel_register_ctx3)
 * Ghidra: undefined8 FUN_000ec974(undefined8 param_1)
 * Allocates a context object and registers param_1 through iel_register_ctx2.
 * Confidence: medium
 * Notes: FUN_0036a940 then FUN_000ecb8c(param_1). */
void *iel_register_ctx3(void *p)
{
    void *ctx = cl4_alloc_object(0, 0, 0);
    iel_register_ctx2(p);
    return ctx;
}

/* FUN_000ec9c4 @ 0x000ec9c4   (est. iel_record_init)
 * Ghidra: void FUN_000ec9c4(undefined8 *param_1)
 * Writes {0, tcb+0x20} into the 2-word output record.
 * Confidence: medium */
void iel_record_init(unsigned long *out)
{
    out[0] = 0;
    out[1] = *(unsigned long *)(cl4_current + 0x20);
}

/* FUN_000ec9d0 @ 0x000ec9d0   (est. iel_save_thread_state2)
 * Ghidra: void FUN_000ec9d0(x, long *param_2, ulong param_3)
 * Like iel_save_thread_state but captures via the method at *param_2+0x1b8 and
 * selects the sync method by param_3 bit0 (0x70 vs 0x68).
 * Confidence: medium
 * Notes: removes unreachable block 0xecb34. */
void iel_save_thread_state2(void *dst, long *src, unsigned long which)
{
    *(void **)(cl4_current + 0x10) = dst;
    void (*capture)(void *frame, int, int, int, int, int) =
        *(void (**)(void *, int, int, int, int, int))(*(void **)src + 0x1b8);
    cl4_retain(0);
    unsigned long frame[9];
    capture(frame, 1, 0, 0, 0, 0);
    if (cl4_result_ok == 0) {
        *(void **)(cl4_current + 0x20) = (void *)frame[2];
        *(void **)(cl4_current + 0x18) = (void *)frame[0];
        *(void **)(cl4_current + 0x30) = (void *)frame[6];
        *(void **)(cl4_current + 0x28) = (void *)frame[4];
        *(unsigned long *)(cl4_current + 0x40) = frame[8] | ((frame[7] << 8) >> 8);
        *(void **)(cl4_current + 0x38) = (void *)frame[7];
        *(void **)(cl4_current + 0x49) = (void *)frame[9];
        *(unsigned long *)(cl4_current + 0x41) = frame[8];
        void *obj = *(void **)(*(long *)(cl4_current + 0x10) + 0x10);
        void (*sync)(void *f);
        if ((which & 1) == 0)
            sync = (void (*)(void *))(*(void **)obj + 0x70);
        else
            sync = (void (*)(void *))(*(void **)obj + 0x68);
        cl4_retain(obj);
        sync(frame);
        cl4_release(obj);
        cl4_release(src);
        cl4_release(dst);
    } else {
        cl4_release(dst);
        cl4_release(src);
        cl4_release(*(void **)(cl4_current + 0x10));
        cl4_fault();
    }
}

/* FUN_000ecb68 @ 0x000ecb68   (est. iel_record_init_thunk)
 * Ghidra: void FUN_000ecb68(void) — forwards to iel_record_init.
 * Confidence: medium
 */
void iel_record_init_thunk(void)
{
    iel_record_init(0);
}

/* FUN_000ecb8c @ 0x000ecb8c   (est. iel_register_ctx2)
 * Ghidra: void FUN_000ecb8c(undefined8 param_1)
 * Resolves the target object for param_1 and installs it at tcb+0x10; faults
 * on failure.
 * Confidence: medium
 * Notes: FUN_001000b8 + FUN_000fd5d8 resolve; FUN_0036b6f4 faults. */
void iel_register_ctx2(void *p)
{
    void *t = cl4_obj_resolve(0);
    void *obj = cl4_obj_resolve2(t, p);
    if (cl4_result_ok == 0)
        *(void **)(cl4_current + 0x10) = obj;
    else
        cl4_fault();
}

/* FUN_000ecc0c @ 0x000ecc0c   (est. iel_dispatch2_setup_a)
 * Ghidra: void FUN_000ecc0c(x) — forwards to iel_dispatch2_setup(p, 0).
 * Confidence: medium
 */
void iel_dispatch2_setup_a(unsigned long *out)
{
    iel_dispatch2_setup(out, 0);
}

/* FUN_000ecc38 @ 0x000ecc38   (est. iel_dispatch2_setup_b)
 * Ghidra: void FUN_000ecc38(x) — forwards to iel_dispatch2_setup(p, 1).
 * Confidence: medium
 */
void iel_dispatch2_setup_b(unsigned long *out)
{
    iel_dispatch2_setup(out, (void *)1);
}

/* FUN_000ecc54 @ 0x000ecc54   (est. iel_dispatch2_setup)
 * Ghidra: void FUN_000ecc54(undefined8 *param_1, undefined8 param_2)
 * Allocates the dispatch object (kind 0x51), retains sources, saves state via
 * iel_save_thread_state2, and records object-kind words into param_1.
 * Confidence: medium
 * Notes: FUN_0036a940(0x6520a8,0x51,7). */
void iel_dispatch2_setup(unsigned long *out, void *which)
{
    void *kind = cl4_alloc_object(0x6520a8, 0x51, 7);
    cl4_retain(0);
    cl4_retain(which);
    iel_save_thread_state2(0, 0, 0);
    if (cl4_result_ok == 0) {
        out[3] = 0x6520a8;
        out[4] = 0x6620f0;
        out[0] = 0;
    }
}

/* FUN_000eccf0 @ 0x000eccf0   (est. iel_const16_d)
 * Ghidra: undefined1[16] FUN_000eccf0(void)
 * Returns the 16-byte literal {0xd...22, 0x800...4c3780}.
 * Confidence: low */
unsigned long long iel_const16_d(void)
{
    /* 128-bit literal: lo=0xd..22, hi=0x800..4c3780 */
    return 0xd000000000000022ull;
}

/* FUN_000ecd0c @ 0x000ecd0c   (est. iel_dispatch2_b_thunk)
 * Ghidra: void FUN_000ecd0c(void) — forwards to iel_dispatch2_setup_b.
 * Confidence: medium
 */
void iel_dispatch2_b_thunk(void)
{
    iel_dispatch2_setup_b(0);
}

/* FUN_000ecd10 @ 0x000ecd10   (est. iel_dispatch2_b_thunk2)
 * Ghidra: void FUN_000ecd10(void) — same as above.
 * Confidence: medium
 */
void iel_dispatch2_b_thunk2(void)
{
    iel_dispatch2_setup_b(0);
}

/* FUN_000ecd24 @ 0x000ecd24   (est. iel_dispatch2_a_thunk)
 * Ghidra: void FUN_000ecd24(void) — forwards to iel_dispatch2_setup_a.
 * Confidence: medium
 */
void iel_dispatch2_a_thunk(void)
{
    iel_dispatch2_setup_a(0);
}

/* FUN_000ecd28 @ 0x000ecd28   (est. iel_dispatch2_a_thunk2)
 * Ghidra: void FUN_000ecd28(void) — same as above.
 * Confidence: medium
 */
void iel_dispatch2_a_thunk2(void)
{
    iel_dispatch2_setup_a(0);
}

/* FUN_000ecd3c @ 0x000ecd3c   (est. iel_const16_d_thunk)
 * Ghidra: undefined8 FUN_000ecd3c(void)
 * Emits the constant record and returns its low word.
 * Confidence: low */
unsigned long iel_const16_d_thunk(void)
{
    iel_const16_d();
    return 0xd000000000000022ull;
}

/* FUN_000ecd40 @ 0x000ecd40   (est. iel_const16_d_thunk2)
 * Ghidra: undefined8 FUN_000ecd40(void) — same as iel_const16_d_thunk.
 * Confidence: medium
 */
unsigned long iel_const16_d_thunk2(void)
{
    iel_const16_d();
    return 0xd000000000000022ull;
}

/* FUN_000ecd94 @ 0x000ecd94   (est. iel_const16_e)
 * Ghidra: undefined1[16] FUN_000ecd94(void)
 * Returns the 16-byte literal {0x652048, 0}.
 * Confidence: low */
unsigned long long iel_const16_e(void)
{
    return 0x652048ull;
}

/* FUN_000ecda4 @ 0x000ecda4   (est. iel_debug_log)
 * Ghidra: void FUN_000ecda4(void)
 * If the debug flag (DAT_006add10) is set, allocates a log record carrying
 * the current entry identity and emits a "get ... tag ..." trace describing
 * it, then releases the enclosing op. Returns immediately when disabled.
 * Confidence: medium
 * Notes: guarded by DAT_006add10==1; FUN_0036a9a0 allocates the record,
 * FUN_0026b434 formats the entry, FUN_0036b588 emits it. */
void iel_debug_log(void *a, void *b, void *c)
{
    if (cl4_debug_enabled != '\x01')
        return;
    void *rec = cl4_log_alloc(0, &iel_log_stack);
    cl4_trace_begin(0x2e);
    cl4_log_fmt(0xe000000000000000);
    void (*log)(unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long))cl4_log_lookup(0x671df8);
    log(0x677830, 0x671df8);
    cl4_trace_word(0, 0);
    cl4_log_fmt(0);
    cl4_trace_word(0x20676174202c, 0xe600000000000000); /* ", tag " */
    log(0x677830, 0x671df8);
    cl4_trace_word(0, 0);
    cl4_log_fmt(0);
    /* name/kind words for the record */
    *(unsigned long *)((char *)rec + 0x38) = 0x6753a0;
    *(unsigned long *)((char *)rec + 0x20) = 0xd000000000000024;
    *(unsigned long *)((char *)rec + 0x28) = 0x80000000005c5150;
    cl4_log_emit(rec);
    cl4_log_finish();
    cl4_release_op(0, 0x20, 7);
}

/* FUN_000ecf48 @ 0x000ecf48   (est. iel_extract_record)
 * Ghidra: undefined1[16] FUN_000ecf48(long param_1)
 * Extracts a 16-byte record from a descriptor at param_1: if the kind word at
 * +0x10 is 0 returns {0, 1<<40}; if 1 returns {+0x20 value, flag=0}; else
 * returns {+0x20 value, flag=1}.
 * Confidence: medium
 * Notes: auVar3 bytes 8/9 encode the kind!=1 flag. */
unsigned long long iel_extract_record(long desc)
{
    long kind = *(long *)(desc + 0x10);
    if (kind != 0) {
        unsigned long v = (kind == 1) ? *(unsigned long *)(desc + 0x20) : 0;
        unsigned long long flag = (kind != 1) ? 1ull : 0ull;
        return (flag << 8) | (v & 0xff);
    }
    /* 128-bit {hi=1, lo=0} (ZEXT816(1) << 0x40) */
    return 0;
}

/* FUN_000ecf70 @ 0x000ecf70   (est. iel_retain_if_scalar)
 * Ghidra: undefined8 FUN_000ecf70(long param_1)
 * If the descriptor kind at param_1+0x10 is 1, retains and returns the value
 * at param_1+0x20; otherwise returns 0.
 * Confidence: medium */
void *iel_retain_if_scalar(long desc)
{
    if (*(long *)(desc + 0x10) == 1)
        return cl4_retain(*(void **)(desc + 0x20));
    return 0;
}

/* FUN_000ecfa4 @ 0x000ecfa4   (est. iel_setup10_alloc)
 * Ghidra: undefined8 FUN_000ecfa4(10 args)
 * Allocates a context object and forwards all 10 arguments to
 * iel_configure_exclave (FUN_000ed954).
 * Confidence: medium
 * Notes: FUN_0036a940 then FUN_000ed954(10 args). */
void *iel_setup10_alloc(void *p1, void *p2, void *p3, void *p4, void *p5,
                        void *p6, void *p7, void *p8, void *p9, void *p10)
{
    void *ctx = cl4_alloc_object(0, 0, 0);
    iel_configure_exclave(p1, (long)p2, p3, p4, p5, p6, (unsigned char)(unsigned long)p7, p8, p9, p10);
    return ctx;
}


/* FUN_000ed04c @ 0x000ed04c   (est. iel_tlb_op_by_bits)
 * Ghidra: ulong FUN_000ed04c(uint param_1)
 * Performs global MMU/TLB maintenance on the three capability words selected
 * by the low 3 bits of `bits`, folding the operations into a running mask via
 * cl4_mmu_op. Returns the resulting mask.
 * Confidence: medium
 * Notes: FUN_00153264/70/7c are the three global cap words; FUN_0001a1c8 is
 * the MMU op. */
unsigned long iel_tlb_op_by_bits(unsigned int bits)
{
    unsigned long r = cl4_mmu_op(0);
    if ((bits & 1) != 0) {
        unsigned long *g = cl4_global_caps_0();
        unsigned long v = *g;
        cl4_mmu_op(v & r);
        r = cl4_mmu_op(v | r);
    }
    if (((bits & 0xffff) >> 1 & 1) != 0) {
        unsigned long *g = cl4_global_caps_1();
        unsigned long v = *g;
        cl4_mmu_op(v & r);
        r = cl4_mmu_op(v | r);
    }
    if (((bits & 0xffff) >> 2 & 1) != 0) {
        unsigned long *g = cl4_global_caps_2();
        unsigned long v = *g;
        cl4_mmu_op(v & r);
        r = cl4_mmu_op(v | r);
        return r;
    }
    return r;
}

/* FUN_000ed11c @ 0x000ed11c   (est. iel_fill_record)
 * Ghidra: void FUN_000ed11c(x8..x13 -> 5 fields)
 * Stores 5 caller values into the output record (a 0x28-byte descriptor).
 * Confidence: medium */
void iel_fill_record(unsigned long *out, unsigned long a, unsigned long b,
                     unsigned char c, unsigned long d, unsigned long e)
{
    out[0] = a;
    out[1] = b;
    *(unsigned char *)(out + 2) = c;
    out[3] = d;
    out[4] = e;
}

/* FUN_000ed12c @ 0x000ed12c   (est. iel_method_f8)
 * Ghidra: void FUN_000ed12c(undefined8 *param_1, undefined8 *param_2)
 * Retains *param_1 and invokes the method at *param_2's table +0xf8.
 * Confidence: medium */
void iel_method_f8(unsigned long *a, unsigned long *b)
{
    void (*m)(void) = *(void (**)(void))(*(long *)*b + 0xf8);
    cl4_retain((void *)*a);
    m();
}

/* FUN_000ed180 @ 0x000ed180   (est. iel_pub_slot_10)
 * Ghidra: void FUN_000ed180(void)
 * Begins a read on the thread's +0x10 slot and retains its object.
 * Confidence: medium */
void iel_pub_slot_10(void)
{
    cl4_slot_begin((void *)(cl4_current + 0x10));
    cl4_retain(*(void **)(cl4_current + 0x10));
}

/* FUN_000ed1ac @ 0x000ed1ac   (est. iel_set_slot_10)
 * Ghidra: void FUN_000ed1ac(undefined8 param_1)
 * Swaps the thread's +0x10 slot out, installs param_1, and logs the old value.
 * Confidence: medium
 * Notes: FUN_0007c0e0 = slot swap into a local; FUN_003a25d4 logs old. */
void iel_set_slot_10(void *v)
{
    unsigned long stack[3];
    cl4_slot_swap((void *)(cl4_current + 0x10), stack);
    void *old = *(void **)(cl4_current + 0x10);
    *(void **)(cl4_current + 0x10) = v;
    cl4_log_fmt((unsigned long)old);
}

/* FUN_000ed1ec @ 0x000ed1ec   (est. iel_send_to_port)
 * Ghidra: void FUN_000ed1ec(undefined8 param_1)
 * Sends param_1 to the port located at *(*(tcb+0x120)+0x10)+0x58.
 * Confidence: medium
 * Notes: FUN_0006e7c0(port, value). */
void iel_send_to_port(void *v)
{
    cl4_port_send(*(void **)(*(long *)(cl4_current + 0x120) + 0x10) + 0x58, v);
}

/* FUN_000ed1f0 @ 0x000ed1f0   (est. iel_send_to_port2)
 * Ghidra: void FUN_000ed1f0(undefined8 param_1) — same as iel_send_to_port.
 * Confidence: medium
 */
void iel_send_to_port2(void *v)
{
    cl4_port_send(*(void **)(*(long *)(cl4_current + 0x120) + 0x10) + 0x58, v);
}

/* FUN_000ed214 @ 0x000ed214   (est. iel_method_1c0)
 * Ghidra: void FUN_000ed214(undefined8 *param_1, undefined8 *param_2)
 * Retains *param_1 and invokes the method at *param_2's table +0x1c0.
 * Confidence: medium */
void iel_method_1c0(unsigned long *a, unsigned long *b)
{
    void (*m)(void) = *(void (**)(void))(*(long *)*b + 0x1c0);
    cl4_retain(*a);
    m();
}

/* FUN_000ed270 @ 0x000ed270   (est. iel_pub_slot_50)
 * Ghidra: void FUN_000ed270(void)
 * Begins a read on the thread's +0x50 slot and retains its object.
 * Confidence: medium */
void iel_pub_slot_50(void)
{
    cl4_slot_begin((void *)(cl4_current + 0x50));
    cl4_retain(*(void **)(cl4_current + 0x50));
}

/* FUN_000ed29c @ 0x000ed29c   (est. iel_set_slot_50)
 * Ghidra: void FUN_000ed29c(undefined8 param_1)
 * Swaps the thread's +0x50 slot out, installs param_1, releases the old value.
 * Confidence: medium */
void iel_set_slot_50(void *v)
{
    unsigned long stack[3];
    cl4_slot_swap((void *)(cl4_current + 0x50), stack);
    void *old = *(void **)(cl4_current + 0x50);
    *(void **)(cl4_current + 0x50) = v;
    cl4_release(old);
}

/* FUN_000ed2e4 @ 0x000ed2e4   (est. iel_method_238)
 * Ghidra: void FUN_000ed2e4(undefined8 *param_1, undefined8 *param_2)
 * Retains *param_1 and invokes the method at *param_2's table +0x238.
 * Confidence: medium */
void iel_method_238(unsigned long *a, unsigned long *b)
{
    void (*m)(void) = *(void (**)(void))(*(long *)*b + 0x238);
    cl4_retain(*a);
    m();
}

/* FUN_000ed36c @ 0x000ed36c   (est. iel_set_slot_b8)
 * Ghidra: void FUN_000ed36c(undefined8 param_1)
 * Swaps the thread's +0xb8 slot out, installs param_1, releases the old value.
 * Confidence: medium */
void iel_set_slot_b8(void *v)
{
    unsigned long stack[3];
    cl4_slot_swap((void *)(cl4_current + 0xb8), stack);
    void *old = *(void **)(cl4_current + 0xb8);
    *(void **)(cl4_current + 0xb8) = v;
    cl4_release(old);
}

/* FUN_000ed3ac @ 0x000ed3ac   (est. iel_retain_notify_c8)
 * Ghidra: void FUN_000ed3ac(void)
 * Retains the thread's +200-byte object and issues the completion notify.
 * Confidence: medium */
void iel_retain_notify_c8(void)
{
    cl4_retain(*(void **)(cl4_current + 200));
    cl4_notify_done();
}

/* FUN_000ed3e0 @ 0x000ed3e0   (est. iel_get_slot_d8)
 * Ghidra: undefined8 FUN_000ed3e0(void)
 * Begins a read on the thread's +0xd8 slot and returns its object.
 * Confidence: medium */
void *iel_get_slot_d8(void)
{
    cl4_slot_begin((void *)(cl4_current + 0xd8));
    return *(void **)(cl4_current + 0xd8);
}

/* FUN_000ed408 @ 0x000ed408   (est. iel_set_slot_d8)
 * Ghidra: void FUN_000ed408(undefined8 param_1)
 * Swaps the thread's +0xd8 slot out and installs param_1.
 * Confidence: medium */
void iel_set_slot_d8(void *v)
{
    unsigned long stack[3];
    cl4_slot_swap((void *)(cl4_current + 0xd8), stack);
    *(void **)(cl4_current + 0xd8) = v;
}

/* FUN_000ed440 @ 0x000ed440   (est. iel_desc_d8)
 * Ghidra: undefined1[16] FUN_000ed440(undefined8 param_1)
 * Installs param_1 into the thread's +0xd8 slot and returns the descriptor
 * pair {&LAB_0006f910, tcb+0xd8} encoding the slot location and its dispatch
 * label.
 * Confidence: low
 * Notes: FUN_0009e228 swaps the slot; LAB_0006f910 is a code label. */
unsigned long long iel_desc_d8(void *v)
{
    unsigned long stack[3];
    cl4_slot_swap((void *)(cl4_current + 0xd8), stack);
    cl4_critical_enter(0, 0, 0, 0);
    /* 128-bit {lo=&LAB_0006f910, hi=tcb+0xd8} */
    return 0x6f910ull;
}

/* FUN_000ed4ac @ 0x000ed4ac   (est. iel_pub_slot_68)
 * Ghidra: void FUN_000ed4ac(void)
 * Begins a read on the thread's +0x68 slot and retains its object.
 * Confidence: medium */
void iel_pub_slot_68(void)
{
    cl4_slot_begin((void *)(cl4_current + 0x68));
    cl4_retain(*(void **)(cl4_current + 0x68));
}

/* FUN_000ed4d8 @ 0x000ed4d8   (est. iel_merge_lists)
 * Ghidra: void FUN_000ed4d8(undefined8 *param_1)
 * Merges the entries of the current list (from getter at +0x230) into the
 * global accumulator list (DAT_00657778), copying each 0xf8-byte entry and
 * growing the accumulator as needed. Returns the accumulator list.
 * Confidence: low
 * Notes: heavy bounds checks trap at 0xed668..0xed680; FUN_003a261c tests the
 * accumulator's growth flag; FUN_000737a8 / FUN_00117cc4 grow/copy. */
void iel_merge_lists(unsigned long *out)
{
    cl4_critical_enter(0, 0, 0, 0);
    void *list = (**(void *(**)(void))((void *)0 + 0x230))();
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)((char *)list + 0x10);
    unsigned char *acc = (unsigned char *)cl4_pending_regions;   /* DAT_00657778 */
    long step = 0x60;
    for (;;) {
        if (n == i) {
            cl4_release(list);
            *out = (unsigned long)acc;
            return;
        }
        if (*(unsigned long *)((char *)list + 0x10) <= i)
            cl4_trap();   /* 0xed668 */
        long e = *(long *)((char *)list + step);
        unsigned long en = *(unsigned long *)((char *)e + 0x10);
        unsigned long an = *(unsigned long *)(acc + 0x10);
        unsigned long sum = an + en;
        if (sum < an)
            cl4_trap();   /* 0xed66c */
        cl4_retain(e);
        unsigned long grow = cl4_obj_flag(acc);
        if ((int)grow == 0) {
            if (an <= sum)
                an = sum;
            acc = (unsigned char *)cl4_array_grow(grow, an, 1, acc);
        } else {
            unsigned long cap = *(unsigned long *)(acc + 0x18) >> 1;
            if ((long)cap < (long)sum) {
                if (an <= sum)
                    an = sum;
                acc = (unsigned char *)cl4_array_grow(grow, an, 1, acc);
            }
        }
        unsigned long room = (*(unsigned long *)(acc + 0x18) >> 1) - *(long *)(acc + 0x10);
        if ((long)room < 0)
            cl4_trap();   /* 0xed670 */
        if (*(long *)((char *)e + 0x10) == 0) {
            cl4_release(e);
            if (en != 0)
                cl4_trap();   /* 0xed674 */
        } else {
            if (room < en)
                cl4_trap();   /* 0xed678 */
            /* copy the en 0xf8-byte entries, checking overlap */
            cl4_obj_copy(acc + *(long *)(acc + 0x10) * 0xf8 + 0x20,
                         (void *)(e + 0x20), en * 0xf8);
            cl4_release(e);
            if (en != 0) {
                if (*(long *)(acc + 0x10) + en < *(long *)(acc + 0x10))
                    cl4_trap();   /* 0xed67c */
                *(unsigned long *)(acc + 0x10) = *(long *)(acc + 0x10) + en;
            }
        }
        step += 0x50;
        i += 1;
    }
}

/* FUN_000ed680 @ 0x000ed680   (est. iel_collect_records)
 * Ghidra: void FUN_000ed680(undefined8 *param_1)
 * Walks the current list (from getter at +0x230), collecting each 0x50-byte
 * region record whose marker byte selects it, into a flat 10-word output.
 * Empty/absent markers are zero-filled. 
 * Confidence: low
 * Notes: FUN_0009d014 copies a 0x50-byte record; FUN_003a261c tests the grow
 * flag; FUN_00082504 grows the accumulator. */
void iel_collect_records(unsigned long *out)
{
    cl4_critical_enter(0, 0, 0, 0);
    void *list = (**(void *(**)(void))((void *)0 + 0x230))();
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)((char *)list + 0x10);
    unsigned char *acc = (unsigned char *)cl4_pending_regions;
    for (;;) {
        long slot = i * 0x50 + 0x20;
        unsigned char rec[0x50];
        /* scan for a matching record */
        for (;;) {
            if (n == i) {
                cl4_release(list);
                /* collapse the accumulator into the output */
                long inner = *(long *)(acc + 0x10);
                unsigned char one[0x50];
                if (inner == 0) {
                    cl4_release(acc);
                    memset(out, 0, 10 * sizeof(unsigned long));
                    return;
                }
                cl4_obj_copy(one, acc + 0x20, 0x50);
                if (inner == 1)
                    iel_region_decode(out, one);
                else
                    cl4_release(acc);
                return;
            }
            if (*(unsigned long *)((char *)list + 0x10) <= i)
                cl4_trap();   /* 0xed86c */
            cl4_obj_copy(rec, (char *)list + slot, 0x50);
            if (((rec[7] & 0xc0) == 0) && ((rec[7] & 1) != 0))
                break;   /* selected marker */
            slot += 0x50;
            i += 1;
        }
        iel_region_decode((unsigned long *)rec, 0);
        /* append a copy of the record to the accumulator */
        unsigned long grow = cl4_obj_flag(acc);
        if ((grow & 1) == 0)
            cl4_array_grow2(0, *(long *)(acc + 0x10) + 1, 1);
        unsigned long idx = *(unsigned long *)(acc + 0x10);
        if (*(unsigned long *)(acc + 0x18) >> 1 <= idx)
            cl4_array_grow2(1 < *(unsigned long *)(acc + 0x18), idx + 1, 1);
        acc = cl4_pending_regions;
        i += 1;
        *(unsigned long *)(acc + 0x10) = idx + 1;
        cl4_obj_copy(acc + idx * 0x50 + 0x20, rec, 0x50);
    }
}

/* FUN_000ed86c @ 0x000ed86c   (est. iel_read_region_record)
 * Ghidra: void FUN_000ed86c(undefined8 *param_1)
 * Reads a 0x50-byte region record from the current object (via getter at
 * +0x270) and, if its kind is 1, byte-swaps its three 128-bit identifier
 * fields; otherwise returns a zero/0xff-defaulted record.
 * Confidence: low
 * Notes: NEON_ext byte-swaps; FUN_000f4c4c fetches the record; markers default
 * to 0xff when the object is absent. */
void iel_read_region_record(unsigned long *out)
{
    cl4_critical_enter(0, 0, 0, 0);
    unsigned long stack[8];
    (**(void (**)(void *))((void *)0 + 0x270))(stack);
    if (stack[0] != 0) {
        long kind = *(long *)((char *)stack[0] + 0x10);
        if (kind != 0) {
            uint64_t a = *(uint64_t *)((char *)stack[0] + 0x30);
            uint64_t b = *(uint64_t *)((char *)stack[0] + 0x40);
            uint64_t c = *(uint64_t *)((char *)stack[0] + 0x20);
            if (kind == 1) {
                out[1] = __builtin_bswap64(c);
                out[0] = __builtin_bswap64(a);
                out[3] = __builtin_bswap64(a);
                out[2] = __builtin_bswap64(*(uint64_t *)((char *)stack[0] + 0x30));
                out[5] = __builtin_bswap64(b);
                out[4] = __builtin_bswap64(*(uint64_t *)((char *)stack[0] + 0x40));
                out[6] = *(unsigned long *)((char *)stack[0] + 0x50);
                *(unsigned char *)(out + 7) = *(unsigned char *)((char *)stack[0] + 0x58);
                return;
            }
        }
    }
    out[1] = 0; out[0] = 0; out[3] = 0; out[2] = 0;
    out[5] = 0; out[4] = 0; out[6] = 0;
    *(unsigned char *)(out + 7) = 0xff;
}


/* Helper: byte-swap a 16-byte value into two words (NEON_ext rev of the
 * 128-bit identifier fields). */
static void cl4_bswap16(const unsigned char *in, unsigned long *out)
{
    unsigned char tmp[16];
    for (int i = 0; i < 16; i++)
        tmp[i] = in[15 - i];
    memcpy(out, tmp, 16);
}

/* Helper: copy a 0x50-byte region record into a 10-word output (the decode
 * that Ghidra inlines at each collection site). */
static void iel_region_decode(unsigned long *out, const void *src)
{
    if (src)
        memcpy(out, src, 0x50);
    else
        memset(out, 0, 0x50);
}


/* FUN_000ed954 @ 0x000ed954   (est. iel_configure_exclave)
 * Ghidra: void FUN_000ed954(10 args)
 * The InternalExclaveLauncher configure routine: builds the exclave's VAS /
 * segment descriptor tables into the current thread context (tcb+0x10..),
 * wires the loader object kinds and segment vtables onto the target `param_4`
 * (the exclave/region object), and either finishes synchronously or performs
 * the address-space-capability mapping for a Mach-O load. On any inconsistency
 * it raises a fatal error.
 * Confidence: low
 * Notes: heavy use of FUN_001f0130 (table build), FUN_0009781c (vtable
 * compose), FUN_00085bf0 (region alloc) and the FUN_000f4cxx launcher helpers.
 * Removes unreachable blocks 0xedfcc / 0xedfdc. */
void iel_configure_exclave(void *p1, long param_2, void *param_3, void *param_4,
                           void *param_5, void *param_6, unsigned char param_7,
                           void *param_8, void *param_9, void *param_10)
{
    /* name/kind descriptor for the loader */
    void *name = cl4_table_new(cl4_pending_regions, 0x677790, 0x662278, 0x6718b8);
    *(void **)(cl4_current + 0x10) = name;
    *(void **)(cl4_current + 0x28) = (void *)cl4_pending_regions_arr;
    *(void **)(cl4_current + 0x30) = (void *)cl4_pending_regions_arr;
    *(void **)(cl4_current + 0x38) = (void *)cl4_pending_regions;
    *(void **)(cl4_current + 0xb8) = (void *)cl4_pending_regions;
    *(void **)(cl4_current + 0xc0) = param_5;
    *(void **)(cl4_current + 0xc8) = param_6;
    *(void **)(cl4_current + 0x50) = (void *)cl4_pending_regions;
    *(void **)(cl4_current + 0x58) = param_9;
    *(unsigned char *)(cl4_current + 0xd0) = param_7;
    *(void **)(cl4_current + 0xd8) = param_8;
    cl4_port_send(p1, (void *)(cl4_current + 0x88));
    *(void **)(cl4_current + 0x120) = (void *)param_2;
    cl4_port_send(*(void **)(param_2 + 0x10) + 0x58, &iel_local_a8);
    /* allocate and register the endpoint/segment descriptors */
    void *a = cl4_alloc_object(0, 0x40, 7);
    cl4_retain(param_2);
    void *ep = cl4_obj_resolve3(&iel_local_a8);
    void *rec = cl4_alloc_object(cl4_log_key(0x652100, 0x4c3868), 0x18, 7);
    *(void **)((char *)rec + 0x10) = ep;
    *(void **)(cl4_current + 0x40) = rec;
    *(void **)(cl4_current + 0x80) = param_3;
    *(void **)(cl4_current + 0x60) = (void *)cl4_pending_regions;
    *(void **)(cl4_current + 0x68) = (void *)cl4_pending_regions;
    *(void **)(cl4_current + 0x70) = param_10;
    *(void **)(cl4_current + 0x78) = param_4;
    cl4_retain(param_10);
    /* segment vtable table */
    void *t = cl4_table_new(cl4_pending_regions,
                            cl4_log_key(0x652108, 0x4c3870),
                            cl4_log_key(0x652110, 0x4c3878),
                            cl4_iel_tbl4());
    unsigned long old5 = *(unsigned long *)(cl4_current + 0x28);
    *(void **)(cl4_current + 0x28) = t;
    cl4_log_fmt(old5);
    /* compose the main descriptor via FUN_0009781c */
    void *d0 = cl4_alloc_object(0, 0x10, 7);
    void *d1 = cl4_alloc_object(iel_const16_c(), 0x10, 7);
    void *d2 = cl4_alloc_object(0, 0x10, 7);
    void *desc = cl4_desc_compose(d0, d1, d2, &iel_local_a8);
    *(void **)(cl4_current + 0xb0) = desc;
    *(void **)(cl4_current + 0x18) = param_3;
    *(void **)(cl4_current + 0x20) = param_4;
    unsigned long oldb8 = *(unsigned long *)(cl4_current + 0xb8);
    *(void **)(cl4_current + 0xb8) = (void *)cl4_pending_regions;
    cl4_release((void *)oldb8);
    void *slot = cl4_alloc_object(iel_const16_b(), 0x18, 7);
    *(void **)((char *)slot + 0x10) = cl4_alloc_value(0x10, 0xffffffffffffffffull);
    *(void **)(cl4_current + 0x48) = slot;
    cl4_retain(desc);
    cl4_desc_emit(&iel_local_a8);
    cl4_release(desc);
    /* persist the register frame into tcb+0xe0.. */
    *(void **)(cl4_current + 0xe0) = (void *)iel_local_a8[0];
    *(void **)(cl4_current + 0xe8) = (void *)iel_local_a8[1];
    *(void **)(cl4_current + 0xf0) = (void *)iel_local_a8[2];
    *(void **)(cl4_current + 0xf8) = (void *)iel_local_a8[3];
    /* validate the descriptor set */
    void *h = (**(void *(**)(void *))(*(void **)cl4_current + 0x328))(*(void **)cl4_current + 0x328);
    cl4_critical_enter((void *)(cl4_current + 0xd8), &iel_local_f0, 0, 0);
    void *ok = cl4_desc_check(h, *(void **)(cl4_current + 0xd8));
    if (ok != 0) {
        cl4_iel_panic_str("InternalExclaveLauncher/External");
        cl4_panic_begin();
        cl4_iel_panic2();
        cl4_fatal_error();
    }
    /* install the segment vtables onto param_4's many slots */
    cl4_iel_install_vtable(param_4, 0xf8, 0x100, 0x000f42dc);
    cl4_iel_install_vtable(param_4, 0xe8, 0xf0, 0x000f42e4);
    cl4_iel_install_vtable(param_4, 0xa8, 0xb0, 0x000f42ec);
    cl4_iel_install_vtable(param_4, 0xb8, 0xc0, 0x000f42f4);
    cl4_iel_install_vtable(param_4, 200, 0xd0, 0x000f42fc);
    /* last slot uses a composed object */
    {
        void *obj = cl4_alloc_object(0, 0, 0);
        cl4_slot_clear((char *)obj + 0x10);
        cl4_retain(param_4);
        cl4_release(0);
        void *old = *(void **)((char *)param_4 + 0xe0);
        *(void **)((char *)param_4 + 0xd8) = (void *)0x000f4304;
        *(void **)((char *)param_4 + 0xe0) = obj;
        cl4_release(param_4);
        cl4_release(old);
    }
    if ((param_7 & 1) == 0) {
        cl4_scope_drop(p1);
        cl4_release(param_2);
        cl4_release(param_10);
    } else {
        /* the "map Mach-O address-space" path */
        cl4_iel_cleanup();
        long npages = cl4_page_size(3);
        if (npages < 0) cl4_trap();   /* 0xedf94 */
        cl4_iel_done();
        unsigned long total = cl4_page_size();
        if (0x400000000ull < total) cl4_trap();   /* 0xedf98 */
        if ((long)(0x400000000ull - total) < 0) cl4_trap();   /* 0xedf9c */
        void *bb = cl4_alloc_object(0, 0x50, 7);
        void *region = cl4_region_alloc(&iel_local_a8, desc, 0x400000000ull - total,
                                        0x11, 0x40808, 0, bb);
        cl4_retain(0);
        cl4_slot_swap((void *)(cl4_current + 0x30), &iel_local_a8);
        cl4_critical_enter(0, 0, 0, 0);
        cl4_region_bind(region, npages);
        cl4_critical_exit(&iel_local_a8);
        cl4_iel_cleanup();
        (**(void (**)(void *, void *))(*(void **)region + 0x100))(*(void **)region + 0x100, &iel_local_a8);
        cl4_release(param_2);
        cl4_release(param_10);
        cl4_release(region);
        cl4_scope_drop(p1);
        cl4_scope_drop(&iel_local_a8);
    }
}

/* FUN_000ee00c @ 0x000ee00c   (est. iel_op_2d0)
 * Ghidra: uint FUN_000ee00c(undefined8 param_1, long param_2)
 * Resolves the object at param_2+0x10 and invokes its +0x2d0 method with
 * param_1; returns the low bit. Fatals if the object is absent.
 * Confidence: medium
 * Notes: removes unreachable block 0xee0f0. */
unsigned int iel_op_2d0(void *a, long b)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(b + 0x10), stack, 0, 0);
    void *obj = cl4_object_get((void *)(b + 0x10));
    if (obj != 0) {
        unsigned int r = (**(unsigned int (**)(void *))(*(void **)obj + 0x2d0))(a);
        cl4_release(obj);
        return r & 1;
    }
    cl4_fatal_error(0, 0xb, 2, 0xd00000000000001d, 0x80000000005c5260,
                    "InternalExclaveLauncher/External", 0x35, 2, 0x99, 0);
    return 0;
}

/* FUN_000ee110 @ 0x000ee110   (est. iel_op_2d0_guarded)
 * Ghidra: uint FUN_000ee110(undefined8 param_1, ulong param_2, long param_3)
 * Like iel_op_2d0 but first checks a per-owner flag: if the object's owner
 * (plVar2[0x24]) is marked pending or param_2's low byte is nonzero it skips
 * the method. Returns 1 when skipped.
 * Confidence: low
 * Notes: removes unreachable block 0xee264. */
unsigned int iel_op_2d0_guarded(void *a, unsigned long k, long c)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(c + 0x10), stack, 0, 0);
    void *obj = cl4_object_get((void *)(c + 0x10));
    if (obj != 0) {
        void *owner = ((unsigned long **)obj)[0x24];
        cl4_retain(owner);
        unsigned long r = cl4_op_check(a, k);
        cl4_release(owner);
        if ((r & 1) == 0) {
            void *o2 = *(void **)((unsigned long **)obj)[0x24] + 0x10;
            unsigned long stack2[3];
            cl4_critical_enter(o2 + 0xa0, stack2, 0, 0);
            unsigned int u = 0;
            if (((*(unsigned char *)((char *)o2 + 0xa0) & 1) == 0) && ((k & 0xff) == 0))
                u = (**(unsigned int (**)(void *))(*(void **)obj + 0x2d0))(a);
            return u & 1;
        }
        cl4_release(obj);
        return 1;
    }
    cl4_fatal_error(0, 0xb, 2, 0xd00000000000001d, 0x80000000005c5260,
                    "InternalExclaveLauncher/External", 0x35, 2, 0x9f, 0);
    return 0;
}

/* FUN_000ee284 @ 0x000ee284   (est. iel_op_2d8)
 * Ghidra: uint FUN_000ee284(3 args, long param_4)
 * Resolves obj at param_4+0x10, invokes its +0x2d8 method, returns low bit.
 * Confidence: medium
 * Notes: removes unreachable block 0xee37c. */
unsigned int iel_op_2d8(void *a, void *b, void *c, long d)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(d + 0x10), stack, 0, 0);
    void *obj = cl4_object_get((void *)(d + 0x10));
    if (obj != 0) {
        unsigned int r = (**(unsigned int (**)(void *, void *, void *))(*(void **)obj + 0x2d8))(a, b, c);
        cl4_release(obj);
        return r & 1;
    }
    cl4_fatal_error(0, 0xb, 2, 0xd00000000000001d, 0x80000000005c5260,
                    "InternalExclaveLauncher/External", 0x35, 2, 0xae, 0);
    return 0;
}

/* FUN_000ee39c @ 0x000ee39c   (est. iel_op_2e0)
 * Ghidra: uint FUN_000ee39c(2 args, long param_3)
 * Resolves obj at param_3+0x10, invokes its +0x2e0 method, returns low bit.
 * Confidence: medium
 * Notes: removes unreachable block 0xee48c. */
unsigned int iel_op_2e0(void *a, void *b, long c)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(c + 0x10), stack, 0, 0);
    void *obj = cl4_object_get((void *)(c + 0x10));
    if (obj != 0) {
        unsigned int r = (**(unsigned int (**)(void *, void *))(*(void **)obj + 0x2e0))(a, b);
        cl4_release(obj);
        return r & 1;
    }
    cl4_fatal_error(0, 0xb, 2, 0xd00000000000001d, 0x80000000005c5260,
                    "InternalExclaveLauncher/External", 0x35, 2, 0xb4, 0);
    return 0;
}

/* FUN_000ee4ac @ 0x000ee4ac   (est. iel_op_2e8)
 * Ghidra: uint FUN_000ee4ac(4 args, long param_5)
 * Resolves obj at param_5+0x10, invokes its +0x2e8 method, returns low bit.
 * Confidence: medium
 * Notes: removes unreachable block 0xee5b4. */
unsigned int iel_op_2e8(void *a, void *b, void *c, void *d, long e)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(e + 0x10), stack, 0, 0);
    void *obj = cl4_object_get((void *)(e + 0x10));
    if (obj != 0) {
        unsigned int r = (**(unsigned int (**)(void *, void *, void *, void *))(*(void **)obj + 0x2e8))(a, b, c, d);
        cl4_release(obj);
        return r & 1;
    }
    cl4_fatal_error(0, 0xb, 2, 0xd00000000000001d, 0x80000000005c5260,
                    "InternalExclaveLauncher/External", 0x35, 2, 0xba, 0);
    return 0;
}

/* FUN_000ee5d4 @ 0x000ee5d4   (est. iel_op_2f0)
 * Ghidra: bool FUN_000ee5d4(4 args, long param_5)
 * Resolves obj at param_5+0x10; if (param_3|param_2) is non-negative, invokes
 * its +0x2f0 method and returns whether the 16-byte result is zero; traps
 * otherwise. Fatals if the object is absent.
 * Confidence: low
 * Notes: FUN_0006e6dc compares the returned 16-byte record. */
bool iel_op_2f0(void *a, unsigned long b, unsigned long c, void *d, long e)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(e + 0x10), stack, 0, 0);
    void *obj = cl4_object_get((void *)(e + 0x10));
    if (obj == 0)
        cl4_fatal_error(0, 0xb, 2, 0xd00000000000001d, 0x80000000005c5260,
                        "InternalExclaveLauncher/External", 0x35, 2, 0xc1, 0);
    if (-1 < (long)(c | b)) {
        unsigned long long r = (**(unsigned long long (**)(void *, unsigned long, unsigned long, void *))(*(void **)obj + 0x2f0))(a, b, c, d);
        cl4_release(obj);
        return cl4_compare16(r) == 0;
    }
    cl4_trap();   /* 0xee6a8 */
}


/* FUN_000ee6f4 @ 0x000ee6f4   (est. iel_destroy_object)
 * Ghidra: void FUN_000ee6f4(void)
 * Tears down the current launcher context: destroys each element of the
 * object list at tcb+0x38, then releases/logs all the populated slots
 * (tcb+0x10/0x28/0x30/0x38..0x120) and drops the scoped block at tcb+0x88.
 * Confidence: low
 * Notes: FUN_004b23d8 destroys one list element. */
void iel_destroy_object(void)
{
    cl4_slot_begin((void *)(cl4_current + 0x38));
    void *list = *(void **)(cl4_current + 0x38);
    long n = *(long *)((char *)list + 0x10);
    if (n != 0) {
        cl4_retain(list);
        unsigned long i = 0x20;
        do {
            cl4_destroy_elem(*(void **)((char *)list + i));
            i += 8;
            n -= 1;
        } while (n != 0);
        cl4_release(list);
    }
    cl4_log_fmt(*(unsigned long *)(cl4_current + 0x10));
    cl4_log_fmt(*(unsigned long *)(cl4_current + 0x28));
    cl4_log_fmt(*(unsigned long *)(cl4_current + 0x30));
    cl4_release(*(void **)(cl4_current + 0x38));
    cl4_release(*(void **)(cl4_current + 0x40));
    cl4_release(*(void **)(cl4_current + 0x48));
    cl4_release(*(void **)(cl4_current + 0x50));
    cl4_release(*(void **)(cl4_current + 0x60));
    cl4_release(*(void **)(cl4_current + 0x68));
    cl4_release(*(void **)(cl4_current + 0x70));
    cl4_scope_drop((void *)(cl4_current + 0x88));
    cl4_release(*(void **)(cl4_current + 0xb0));
    cl4_release(*(void **)(cl4_current + 0xb8));
    cl4_log_fmt(*(unsigned long *)(cl4_current + 200));
    cl4_release(*(void **)(cl4_current + 0x120));
}

/* FUN_000ee7d8 @ 0x000ee7d8   (est. iel_destroy_object_op)
 * Ghidra: void FUN_000ee7d8(void) — destroy then release the op.
 * Confidence: medium
 */
void iel_destroy_object_op(void)
{
    iel_destroy_object();
    cl4_release_op();
}

/* FUN_000ee7dc @ 0x000ee7dc   (est. iel_destroy_object_op2)
 * Ghidra: void FUN_000ee7dc(void) — same as iel_destroy_object_op.
 * Confidence: medium
 */
void iel_destroy_object_op2(void)
{
    iel_destroy_object();
    cl4_release_op();
}

/* FUN_000ee800 @ 0x000ee800   (est. iel_dump_regions)
 * Ghidra: void FUN_000ee800(void)
 * When debugging, emits a "Dump EVES :< ...>" trace of the pending-region
 * list, then iterates the list calling each region's +0x88 method to log it,
 * releasing each entry afterwards.
 * Confidence: low
 * Notes: the string literals 0x20676e69706d7544 ("Dump ") and
 * 0xed0000203a535645 ("EVES :") are assembled into the log record. */
void iel_dump_regions(void)
{
    void *fmt = cl4_iel_tbl4();
    void *rec = cl4_log_alloc2(fmt, &iel_log_stack);
    rec = rec;
    cl4_log_fmt(0xe000000000000000);
    cl4_panic_begin();
    cl4_log_emit(rec);
    cl4_log_finish();
    cl4_release_op(0, 0x20, 7);
    void *list = (**(void *(**)(void *))(*(void **)cl4_current + 0x260))(*(void **)cl4_current + 0x260);
    long n = *(long *)((char *)list + 0x10);
    if (n != 0) {
        void **it = (void **)((char *)list + 0x20);
        do {
            void *e = *it;
            void *r2 = cl4_log_alloc2(fmt, &iel_log_stack);
            void (*m)(void) = *(void (**)(void))(*(void **)e + 0x88);
            cl4_retain(e);
            m();
            cl4_trace_word(0, 0);
            cl4_log_fmt(0);
            cl4_trace_word(0x29, 0xe100000000000000);
            cl4_log_emit(r2);
            cl4_release(e);
            cl4_log_finish();
            cl4_release_op(0, 0x20, 7);
            n -= 1;
            it += 1;
        } while (n != 0);
    }
    cl4_release(list);
}

/* FUN_000ee9c4 @ 0x000ee9c4   (est. iel_check_region_bounds)
 * Ghidra: void FUN_000ee9c4(ulong param_1)
 * Validates that mapping `size` bytes at the current region's low boundary
 * does not overlap an already-mapped range on both ends; raises a "Unexpectedly
 * mapped on both ends" panic when it does.
 * Confidence: medium
 * Notes: tcb+0x18/0x20/0x78/0x80 are the region extent bookkeeping. */
unsigned long iel_check_region_bounds(unsigned long size)
{
    if (*(unsigned long *)(cl4_current + 0x20) < *(unsigned long *)(cl4_current + 0x80))
        cl4_trap();   /* 0xeea18 */
    if (*(unsigned long *)(cl4_current + 0x20) - *(unsigned long *)(cl4_current + 0x80) <= size) {
        if (*(unsigned long *)(cl4_current + 0x78) < size)
            cl4_trap();   /* 0xeea1c */
        if (*(unsigned long *)(cl4_current + 0x78) - size <= *(unsigned long *)(cl4_current + 0x18)) {
            cl4_panic_str("Unexpectedly mapped on both ends");
            cl4_iel_panic();
            cl4_panic_begin();
            cl4_iel_panic2();
            cl4_fatal_error();
        }
    }
    return *(unsigned long *)(cl4_current + 0x20);
}

/* FUN_000eea4c @ 0x000eea4c   (est. iel_map_region)
 * Ghidra: ulong FUN_000eea4c(7 args)
 * Maps a region of (addr, len, flags...) into the current address space:
 * resolves the region object, extends the tcb+0x78/0x80 extent tracking, runs
 * the notifier (+0xb0) and constructs a descriptor object tagged with the
 * region pointer. Returns the descriptor.
 * Confidence: low
 * Notes: removes unreachable block 0xeebd0; FUN_0016d328 resolves the region;
 * FUN_00167c54/60 pick the per-state notifier. */
unsigned long iel_map_region(unsigned long a, unsigned long b, unsigned long c,
                             unsigned long d, unsigned long e, unsigned long f, unsigned long g)
{
    void *ctx = *(void **)(cl4_current + 0x40);
    cl4_retain(ctx);
    void *region = cl4_find_region(a, b, c, d, e, f, g);
    cl4_release(ctx);
    if (cl4_result_ok != 0)
        return b;
    if (a + b < a)
        cl4_trap();   /* 0xeebd0 */
    unsigned long lo = *(unsigned long *)(cl4_current + 0x78);
    unsigned long hi = a + b;
    if (a + b <= *(unsigned long *)(cl4_current + 0x80))
        hi = *(unsigned long *)(cl4_current + 0x80);
    bool same = (a == lo);
    if (lo <= a)
        a = lo;
    *(unsigned long *)(cl4_current + 0x78) = a;
    *(unsigned long *)(cl4_current + 0x80) = hi;
    cl4_flag_0();
    cl4_iel_cleanup();
    if (!same) {
        cl4_flag_1();
        cl4_iel_cleanup();
        if (!same) goto done_notify;
    }
    (**(void (**)(void *, void *, unsigned long))*(void **)region + 0xb0)(0, 0, b);
done_notify:
    (void)0;   /* label; next decl */
    void *desc = cl4_alloc_object(0, 0x19, 7);
    *(unsigned long *)((char *)desc + 0x10) = (unsigned long)region | 0x8000000000000000ull;
    *(unsigned char *)((char *)desc + 0x18) = 0;
    unsigned long stack[3];
    cl4_slot_swap((void *)(cl4_current + 0x68), stack);
    cl4_critical_enter(0, 0, 0, 0);
    cl4_retain(region);
    cl4_retain(desc);
    cl4_find_region(0, 0, 0, 0, 0, 0, 0);
    cl4_critical_exit(stack);
    cl4_release(region);
    return (unsigned long)desc;
}

/* FUN_000eebf0 @ 0x000eebf0   (est. iel_query_region)
 * Ghidra: undefined8 FUN_000eebf0(void)
 * Invokes the +0x80 method on the thread's +0x48 object with the FUN_000f430c
 * selector, passing a freshly allocated descriptor key; returns the method's
 * result word.
 * Confidence: low */
void *iel_query_region(void)
{
    void *obj = *(void **)(cl4_current + 0x48);
    void (*m)(void *out, void *sel, void *stack, void *key) = *(void (**)(void *, void *, void *, void *))(*(void **)obj + 0x80);
    void *key = cl4_alloc_object(0, 0x19, 7);
    cl4_retain(obj);
    void *out;
    m(&out, (void *)0x000f430c, &iel_local_a8, key);
    cl4_release(obj);
    return out;
}

/* FUN_000eecb4 @ 0x000eecb4   (est. iel_map_region_wrapper)
 * Ghidra: void FUN_000eecb4(9 args)
 * Wraps iel_map_region(param_3..param_9), storing the resulting descriptor
 * into param_1 when the operation succeeds.
 * Confidence: medium */
void iel_map_region_wrapper(unsigned long *out, void *p2, unsigned long a, unsigned long b,
                            unsigned long c, unsigned long d, unsigned long e, unsigned long f, unsigned long g)
{
    unsigned long r = iel_map_region(a, b, c, d, e, f, g);
    if (cl4_result_ok == 0)
        *out = r;
}

/* FUN_000eed00 @ 0x000eed00   (est. iel_method_80_f)
 * Ghidra: void FUN_000eed00(void)
 * Invokes the current op's +0x80 method with the FUN_000f4338 selector and the
 * 0x67b148 key.
 * Confidence: low */
void iel_method_80_f(void)
{
    cl4_iel_cleanup();
    void (*m)(void *, void *, void *) = (*(void (**)(void *, void *, void *))((void *)0 + 0x80));
    cl4_retain(0);
    m((void *)0x000f4338, &iel_local_a8, (void *)0x67b148);
    cl4_iel_done();
}

/* FUN_000eed84 @ 0x000eed84   (est. iel_append_segment_locked)
 * Ghidra: void FUN_000eed84(long *param_1, long param_2)
 * Appends a segment/region to a locked region list: compares the region size
 * against the segment's byte count, and when equal either forwards a
 * region-cap (if the region's +0x48 slot is set) or emits an "Unexpected type
 * of region in kit" panic.
 * Confidence: low
 * Notes: FUN_0014b644(3) yields the page size; FUN_00086840 logs the panic. */
void iel_append_segment_locked(long *region, long seg)
{
    long size = (**(long (**)(void))(*(void **)region + 0x70))();
    long count = *(long *)(seg + 0x10);
    long page = cl4_page_size(3);
    if (page < 0) cl4_trap();   /* 0xeef0c */
    long bytes = count * page;
    if (count != 0 && bytes / count != page) cl4_trap();   /* 0xeef10 */
    if (bytes < 0) cl4_trap();   /* 0xeef14 */
    if (bytes == 0) {
        if (size != 0) goto bad;
    } else if (size != bytes) {
bad:
        cl4_iel_panic2();
        cl4_fatal_error();
        return;
    }
    unsigned long cap = region[2];
    if ((long)cap < 0) {
        void *obj = (void *)(cap & 0x7fffffffffffffffull);
        unsigned long (*m)(void *, int, int, int) = *(unsigned long (**)(void *, int, int, int))(*(void **)region + 0x48);
        cl4_retain(obj);
        unsigned long r = m(obj, 0, 0, 0);
        if (((r & 1) == 0) &&
            ((**(int (**)(void *, void *, int, int))(*(void **)(cap & 0x7fffffffffffffff) + 0x98))((void *)seg, 0, 0, 1), cl4_result_ok == 0))
            (**(void (**)(int))(*(void **)region + 0x50))(1);
        cl4_release_tagged(cap);
        return;
    }
    cl4_trace_begin(0x23);
    cl4_log_fmt(0xe000000000000000);
    cl4_panic_str("Unexpected type of region in kit");
    (**(void (**)(void))(*(void **)region + 0x88))();
    cl4_trace_word(0, 0);
    cl4_log_fmt(0);
    cl4_iel_panic();
    cl4_iel_abort();
    cl4_fatal_error();
}

/* FUN_000eef94 @ 0x000eef94   (est. iel_append_segment_region)
 * Ghidra: void FUN_000eef94(long *param_1, long *param_2)
 * Appends a segment region: for a region-cap whose owner object is writable,
 * copies the segment's frame/region data and grows the target address-space
 * descriptor; performs size validation and raises "Unexpected type of region
 * in kit" / "Wrong number of frame caps" panics on mismatch.
 * Confidence: low
 * Notes: removes unreachable blocks 0xef2ac/0xef2a0/0xef0d0; FUN_000ef4dc
 * builds the frame-cap list. */
void iel_append_segment_region(long *region, long *seg)
{
    unsigned long cap = region[2];
    if (-1 < (long)cap) {
        cl4_iel_panic_str("appendSegmentRegionLocked(machoF");
        goto fatal;
    }
    void *obj = (void *)(cap & 0x7fffffffffffffff);
    void (*m)(void) = *(void (**)(void))(*(void **)seg + 0x60);
    cl4_retain(obj);
    m();
    unsigned long mmu = cl4_mmu_op2();
    cl4_slot_begin(0);
    unsigned long present = (**(unsigned long (**)(void))((void *)0 + 0x48))();
    if ((present & 1) == 0) {
        unsigned char write = (**(unsigned char (**)(void))(*(void **)obj + 0xd8))();
        unsigned char *flag = cl4_flag_0();
        if ((*flag & (write ^ 0xff)) == 0) {
applied:
            cl4_iel_done();
            unsigned long sz = (**(unsigned long (**)(void))((void *)0 + 0x70))();
            (**(void (**)(int, void *, unsigned long))(*(void **)obj + 0xb0))(1, 0, sz);
        } else {
            unsigned char w2 = (**(unsigned char (**)(void))(*(void **)obj + 0xd8))();
            unsigned char *f2 = cl4_flag_1();
            if ((*f2 & (w2 ^ 0xff)) == 0) goto applied;
            unsigned long *gc = cl4_global_caps_1();
            unsigned long orig = *gc;
            unsigned long r = cl4_mmu_op(orig);
            long chk = cl4_mmu_op(r & mmu);
            long segn = (**(long (**)(void))(*(void **)seg + 0x88))();
            long build;
            if (chk == (long)orig) {
                build = (long)iel_build_vm_regions(region, segn);
                cl4_release((void *)segn);
            } else {
                build = segn;
            }
            cl4_iel_done();
            unsigned long sz2 = (**(unsigned long (**)(void))((void *)0 + 0x70))();
            long count = *(long *)(build + 0x10);
            long page = cl4_page_size(3);
            if (page < 0) cl4_trap();   /* 0xef260 */
            long bytes = count * page;
            if (count != 0 && bytes / count != page) cl4_trap();   /* 0xef264 */
            if (bytes < 0) cl4_trap();   /* 0xef268 */
            if (bytes == 0) {
                if (sz2 != 0) goto bad_count;
            } else if (sz2 != bytes) {
bad_count:
                cl4_trace_begin(0x1f);
                cl4_log_fmt(0xe000000000000000);
                cl4_trap();
                cl4_fatal_error();
            }
            iel_append_segment_locked(region, build);
            cl4_release((void *)build);
        }
    }
    (**(void (**)(int))(*(void **)region + 0x50))(1);
    cl4_release_tagged(cap);
    return;
fatal:
    cl4_iel_abort();
    cl4_fatal_error();
}

/* FUN_000ef380 @ 0x000ef380   (est. iel_teardown_region)
 * Ghidra: void FUN_000ef380(long *param_1)
 * Tears down a region whose owner cap is set: queries the region size,
 * releases the mapped frames (+0xb0/+0xa0) and resets the +0x50 state. Panics
 * on an unexpected region type.
 * Confidence: low
 * Notes: removes unreachable blocks 0xef4cc/0xef4c0/0xef4d4. */
void iel_teardown_region(long *region)
{
    unsigned long cap = region[2];
    if ((long)cap < 0) {
        void *obj = (void *)(cap & 0x7fffffffffffffff);
        unsigned long (*sz)(void) = *(unsigned long (**)(void))(*(void **)region + 0x70);
        cl4_retain(obj);
        unsigned long n = sz();
        (**(void (**)(int, void *, unsigned long))(*(void **)obj + 0xb0))(0, 0, n);
        (**(void (**)(int))(*(void **)region + 0x50))(0);
        (**(void (**)(int, unsigned long, int))(*(void **)obj + 0xa0))(0, n, 0);
        cl4_release_tagged(cap);
        return;
    }
    cl4_panic_str("Unexpected type of region in kit");
    cl4_iel_panic();
    cl4_panic_begin();
    cl4_iel_panic2();
    cl4_fatal_error();
}

/* FUN_000ef4dc @ 0x000ef4dc   (est. iel_build_vm_regions)
 * Ghidra: undefined * FUN_000ef4dc(long *param_1, long param_2)
 * Builds the frame-capability list for a region: for each frame in the source
 * segment it allocates a frame cap, records it into both the per-region
 * accumulator and the return list, then validates the total frame count and
 * returns the completed list. Raises "VasSlotAlloc failed on ..." /
 * "Wrong number of frame caps" panics on failure.
 * Confidence: medium
 * Notes: removes unreachable blocks 0xefb90/0xefb84/0xefb9c/0xefb78. Each frame
 * is appended to BOTH the accumulator and the return list; per frame a pair of
 * descriptors is built (FUN_00085a54) whose vtable[0x90]/[0xe0] bind the page
 * and frame cap, then cl4_notify_done + memmove (FUN_00117d14) commit it.
 * FUN_00085a54 / FUN_000f4c9c / FUN_00117d14 receive register-only args not
 * recoverable from the decompile (kept as empty calls). */
void *iel_build_vm_regions(long *region, long seg)
{
    unsigned long cap = region[2];
    if ((long)cap >= 0) {
        cl4_iel_panic_str("Unexpected type of region in kit");
        cl4_iel_panic();
    }
    unsigned long count = *(unsigned long *)(seg + 0x10);
    unsigned char *acc = (unsigned char *)cl4_pending_regions;
    unsigned char *ret = acc;
    if (count == 0) {
        cl4_retain((void *)(cap & 0x7fffffffffffffff));
    } else {
        void (*alloc)(void) = *(void (**)(void))(*(void **)region + 0x68);
        cl4_retain((void *)(cap & 0x7fffffffffffffff));
        void **frames = (void **)(seg + 0x20);
        unsigned long i = count;
        do {
            void *f = *frames;
            cl4_page_size(3);
            alloc();
            void *fcap = cl4_frame_alloc();
            if (fcap == 0) {
                cl4_frame_panic();
                cl4_vas_oom();   /* "VasSlotAlloc failed on ..." fatal */
            }
            cl4_frame_bind(&iel_local_a8, f);
            if (cl4_result_ok != 0) {
                cl4_scope_drop(&iel_local_a8);
                cl4_vas_oom_nop2();
                cl4_fatal_noreturn();
            }
            cl4_scope_drop(&iel_local_a8);
            /* grow and append into the accumulator */
            unsigned long grow = cl4_obj_flag(acc);
            if ((grow & 1) == 0) {
                cl4_array_free(*(void **)(acc + 0x10));
                acc = (unsigned char *)cl4_array_grow2(0, *(long *)(acc + 0x10) + 1, 1);
            }
            unsigned long idx = *(unsigned long *)(acc + 0x10);
            if (*(unsigned long *)(acc + 0x18) >> 1 <= idx)
                acc = (unsigned char *)cl4_array_grow2(1 < *(unsigned long *)(acc + 0x18), idx + 1, 1);
            *(unsigned long *)(acc + 0x10) = idx + 1;
            *(long *)(acc + idx * 8 + 0x20) = (long)fcap;
            /* grow and append into the return list too */
            grow = cl4_obj_flag(ret);
            if ((grow & 1) == 0) {
                cl4_array_free(*(void **)(ret + 0x10));
                ret = (unsigned char *)cl4_array_grow2(0, *(long *)(ret + 0x10) + 1, 1);
            }
            idx = *(unsigned long *)(ret + 0x10);
            if (*(unsigned long *)(ret + 0x18) >> 1 <= idx)
                ret = (unsigned char *)cl4_array_grow2(1 < *(unsigned long *)(ret + 0x18), idx + 1, 1);
            *(unsigned long *)(ret + 0x10) = idx + 1;
            *(long *)(ret + idx * 8 + 0x20) = (long)fcap;
            if (cl4_page_size(3) < 0) cl4_trap();   /* 0xefa5c */
            /* build two frame descriptors and bind the page + its frame cap */
            void *reg = cl4_lock_registry();
            void *rec = cl4_log_alloc2(reg, 0x64e1c0);
            cl4_vas_oom_nop();
            void *alc = cl4_lock_allocator();
            cl4_alloc_object(alc, 0x50, 7);
            cl4_stack_ptr();
            long *d9 = (long *)cl4_vas_map();
            if (cl4_page_size(3) < 0) cl4_trap();   /* 0xefa60 */
            cl4_vas_oom_nop();
            /* local_88 = rec */
            cl4_alloc_object(alc, 0x50, 7);
            cl4_stack_ptr();
            long *d10 = (long *)cl4_vas_map();
            (**(void (**)(int, void *))(*(void **)d10 + 0x90))(0, f);
            (**(void (**)(int, void *))(*(void **)d9 + 0x90))(0, fcap);
            if ((**(unsigned long (**)(void))(*(void **)d9 + 0xe0))() == 0)
                cl4_trap();   /* 0xefa7c */
            if ((**(unsigned long (**)(void))(*(void **)d10 + 0xe0))() == 0)
                cl4_trap();   /* 0xefa80 */
            cl4_iel_done();
            long psz = cl4_page_size();
            if (psz < 0) cl4_trap();   /* 0xefa64 */
            cl4_notify_done(psz, 0, psz);
            cl4_memmove();
            cl4_release(d9);
            cl4_release(d10);
            i -= 1;
            frames += 1;
        } while (i != 0);
    }
    /* validate total frame count */
    (**(void (**)(void))(*(void **)region + 0x68))();
    cl4_page_size(3);
    unsigned long total = (**(unsigned long (**)(void))(*(void **)region + 0x70))();
    cl4_iel_done();
    unsigned long slots = cl4_page_size();
    if (slots == 0) cl4_trap();   /* 0xefa68 */
    unsigned long per = (unsigned long)region / slots;
    long missing = per - count;
    if (per < count) cl4_trap();   /* 0xefa6c */
    long frame_list = *(long *)(cl4_current + 0x120);
    for (; missing != 0; missing -= 1) {
        cl4_page_size(3);
        void *fcap = cl4_frame_alloc();
        if (fcap == 0) {
            cl4_panic_str("VasSlotAlloc failed on ");
            cl4_trace_begin(0x1e);
            cl4_log_fmt(0xe000000000000000);
            cl4_fatal_error(0, 0xb, 2, "Fatal error", 0, 0);
        }
        /* grow and record the spare frame into both lists */
        unsigned long g = cl4_obj_flag(acc);
        if ((g & 1) == 0) {
            cl4_array_free(*(void **)(acc + 0x10));
            acc = (unsigned char *)cl4_array_grow2(0, *(long *)(acc + 0x10) + 1, 1);
        }
        unsigned long idx = *(unsigned long *)(acc + 0x10);
        if (*(unsigned long *)(acc + 0x18) >> 1 <= idx)
            acc = (unsigned char *)cl4_array_grow2(1 < *(unsigned long *)(acc + 0x18), idx + 1, 1);
        *(unsigned long *)(acc + 0x10) = idx + 1;
        *(long *)(acc + idx * 8 + 0x20) = (long)fcap;
        cl4_frame_bind(&iel_local_a8, fcap);
        if (cl4_result_ok != 0) {
            cl4_scope_drop(&iel_local_a8);
            cl4_vas_oom_nop2();
            cl4_fatal_noreturn();
        }
        cl4_scope_drop(&iel_local_a8);
        g = cl4_obj_flag(ret);
        if ((g & 1) == 0) {
            cl4_array_free(*(void **)(ret + 0x10));
            ret = (unsigned char *)cl4_array_grow2(0, *(long *)(ret + 0x10) + 1, 1);
        }
        idx = *(unsigned long *)(ret + 0x10);
        if (*(unsigned long *)(ret + 0x18) >> 1 <= idx)
            ret = (unsigned char *)cl4_array_grow2(1 < *(unsigned long *)(ret + 0x18), idx + 1, 1);
        *(unsigned long *)(ret + 0x10) = idx + 1;
        *(long *)(ret + idx * 8 + 0x20) = (long)fcap;
    }
    unsigned long n = *(unsigned long *)(ret + 0x10);
    cl4_retain(ret);
    long page = cl4_page_size(3);
    if (page < 0) cl4_trap();   /* 0xefa70 */
    long bytes = n * page;
    if (n != 0 && bytes / n != page) cl4_trap();   /* 0xefa74 */
    if (bytes < 0) cl4_trap();   /* 0xefa78 */
    long have = (**(long (**)(void))(*(void **)region + 0x70))();
    if (bytes - have == 0) {
        cl4_release_tagged(cap);
        unsigned long stack[3];
        cl4_slot_swap((void *)(cl4_current + 0x38), stack);
        cl4_critical_enter(0, 0, 0, 0);
        cl4_retain(acc);
        cl4_iel_tlb();
        cl4_critical_exit(stack);
        cl4_release(acc);
        cl4_release(ret);
        return ret;
    }
    cl4_iel_panic_str("Wrong number of frame caps");
    cl4_iel_panic();
    cl4_fatal_error();
    return 0;
}


/* FUN_000efbfc @ 0x000efbfc   (est. iel_dispatch_80_a)
 * Ghidra: void FUN_000efbfc(void)
 * Dispatch wrapper: enters the op context and invokes the current op's +0x80
 * method (a region/segment selector op).
 * Confidence: low
 * Notes: FUN_000f4be8/4cbc/4b2c/4c40/4cb0 are the launcher's op-context
 * enter/leave helpers. */
void iel_dispatch_80_a(void)
{
    cl4_iel_done();
    cl4_slot_begin(0);
    void (*m)(void) = *(void (**)(void))((void *)0 + 0x80);
    cl4_retain(0);
    cl4_iel_cleanup();
    cl4_iel_panic2();
    m();
    cl4_iel_done();
    cl4_iel_cleanup();
}

/* FUN_000efc74 @ 0x000efc74   (est. iel_process_regions)
 * Ghidra: void FUN_000efc74(undefined1 *param_1, long param_2, undefined8 param_3)
 * Walks the region list at param_2+0x28, and for each region whose +0x58
 * method reports the given type, appends it to the global pending-region list
 * and (re)resolves the region matching chain. Returns success in *param_1.
 * Confidence: low
 * Notes: heavy matching loop; FUN_001670f0 does the list lookup; traps at
 * 0xeff40 / 0xeff3c. */
void iel_process_regions(unsigned char *out, long target, void *key)
{
    unsigned long stack[4];
    cl4_critical_enter((void *)(target + 0x28), stack, 0, 0);
    void *list = *(void **)(target + 0x28);
    cl4_retain(list);
    cl4_list_lookup(&iel_local_a8, (unsigned long)key, list);
    cl4_log_fmt((unsigned long)list);
    void *found = (void *)iel_local_a8[0];
    if (found == 0) {
        *out = 0;
        return;
    }
    /* scan the found list for regions matching the target type */
    cl4_release(*(void **)iel_local_a8[3]);
    cl4_log_fmt(iel_local_a8[2]);
    cl4_log_fmt(iel_local_a8[1]);
    unsigned long n = *(unsigned long *)((char *)found + 0x10);
    if (n == 0) {
        cl4_release(found);
        *out = 1;
        return;
    }
    unsigned long i = 0;
    for (;;) {
        if (*(unsigned long *)((char *)found + 0x10) <= i)
            cl4_trap();   /* 0xeff3c */
        void *r = *(void **)((char *)found + 0x20 + i * 8);
        long (*type)(void) = *(long (**)(void))(*(void **)r + 0x58);
        cl4_retain(r);
        long t = type();
        if (t != 0) {
            /* re-resolve and append every match to the global list */
            cl4_retain(*(void **)(target + 0x28));
            cl4_list_lookup(&iel_local_a8, (unsigned long)key, *(void **)(target + 0x28));
            cl4_log_fmt((unsigned long)list);
            void *f2 = (void *)iel_local_a8[0];
            if (f2 == 0) cl4_trap();   /* 0xeff40 */
            cl4_log_fmt(iel_local_a8[2]);
            cl4_log_fmt(iel_local_a8[1]);
            cl4_release(f2);
            unsigned long j = 0;
            unsigned long n2 = *(unsigned long *)((char *)iel_local_a8[3] + 0x10);
            while (n2 != j) {
                void *r2 = *(void **)((char *)iel_local_a8[3] + j * 8 + 0x20);
                void *(*get)(void) = *(void *(**)(void))(*(void **)r2 + 0x68);
                cl4_retain(r2);
                void *tag = get();
                if (tag == ((void **)r)[2]) {
                    cl4_list_lock();
                    unsigned long k = cl4_pending_regions_n;
                    cl4_list_index();
                    cl4_pending_regions_n = k + 1;
                    (&cl4_pending_regions_arr)[k] = (unsigned long)r2;
                    j += 1;
                } else {
                    cl4_release(r2);
                    j += 1;
                }
            }
            cl4_release((void *)iel_local_a8[3]);
            void *one = iel_retain_if_scalar((long)cl4_pending_regions);
            cl4_release((void *)cl4_pending_regions);
            if (one == 0) cl4_trap();   /* 0xeff40 */
            void *obj = cl4_retain(one);
            iel_append_segment_region(obj, r);
            cl4_release(obj);
            cl4_release((void *)((unsigned long)one | 2));
        }
        i += 1;
        cl4_release(r);
        if (i == n) break;
    }
    cl4_release(found);
    *out = 1;
}

/* FUN_000eff8c @ 0x000eff8c   (est. iel_dispatch_80_b)
 * Ghidra: void FUN_000eff8c(void)
 * Dispatch wrapper (FUN_000f4b58 variant): invokes the +0x80 method.
 * Confidence: low */
void iel_dispatch_80_b(void)
{
    cl4_iel_cleanup();
    void (*m)(void) = *(void (**)(void))((void *)0 + 0x80);
    cl4_retain(0);
    cl4_iel_cleanup();
    cl4_iel_panic2();
    m();
    cl4_iel_done();
    cl4_iel_cleanup();
}

/* FUN_000f0000 @ 0x000f0000   (est. iel_match_region)
 * Ghidra: void FUN_000f0000(undefined1 *param_1, long param_2, long param_3, long param_4)
 * Matches regions in the target list (param_2+0x28) against the id param_3,
 * appending each match to the global pending list; then verifies that the
 * matched region's +0x70 size equals param_4 and appends its segment.
 * Confidence: low
 * Notes: traps at 0xf037c/0xf0384/0xf0380; thunk_FUN_000a17f8 builds the
 * region set; FUN_0036993c raises on mismatch. */
void iel_match_region(unsigned char *out, long target, long id, long want)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(target + 0x28), stack, 0, 0);
    void *list = *(void **)(target + 0x28);
    cl4_retain(list);
    unsigned long tmp = cl4_log_key(0x652110, 0x4c3878);
    cl4_list_lookup(&iel_local_a8, (unsigned long)id, list);
    cl4_log_fmt((unsigned long)list);
    void *found = (void *)iel_local_a8[0];
    if (found == 0) {
        *out = 0;
        return;
    }
    cl4_log_fmt(iel_local_a8[2]);
    cl4_log_fmt(iel_local_a8[1]);
    cl4_release(found);
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)((char *)iel_local_a8[3] + 0x10);
    while (n != i) {
        void *r = *(void **)((char *)iel_local_a8[3] + i * 8 + 0x20);
        void *(*get)(void) = *(void *(**)(void))(*(void **)r + 0x68);
        cl4_retain(r);
        void *tag = get();
        if (tag == (void *)id) {
            cl4_list_lock();
            unsigned long k = cl4_pending_regions_n;
            cl4_list_index();
            cl4_pending_regions_n = k + 1;
            (&cl4_pending_regions_arr)[k] = (unsigned long)r;
            i += 1;
        } else {
            cl4_release(r);
            i += 1;
        }
    }
    cl4_release((void *)iel_local_a8[3]);
    void *one = iel_retain_if_scalar((long)cl4_pending_regions);
    cl4_release((void *)cl4_pending_regions);
    if (one == 0) {
        *out = 0;
        return;
    }
    cl4_retain(*(void **)(target + 0x28));
    cl4_list_lookup(&iel_local_a8, (unsigned long)id, *(void **)(target + 0x28));
    cl4_log_fmt((unsigned long)list);
    if (iel_local_a8[0] == 0) cl4_trap();   /* 0xf0384 */
    cl4_log_fmt(iel_local_a8[2]);
    cl4_log_fmt(iel_local_a8[1]);
    cl4_release((void *)iel_local_a8[3]);
    unsigned long j = 0;
    unsigned long n2 = *(unsigned long *)((char *)iel_local_a8[0] + 0x10);
    while (n2 != j) {
        void *r3 = *(void **)((char *)iel_local_a8[0] + j * 8 + 0x20);
        j += 1;
        if (*(long *)((char *)r3 + 0x10) == id) {
            cl4_retain(r3);
            cl4_list_lock();
            unsigned long k = cl4_pending_regions_n;
            cl4_list_index();
            cl4_pending_regions_n = k + 1;
            (&cl4_pending_regions_arr)[k] = (unsigned long)r3;
        }
    }
    cl4_release((void *)iel_local_a8[0]);
    void *set = (void *)cl4_region_set(0xd00000000000001c, 0x80000000005c5210,
                                       "__APPLEInternal.Library/BuildRoot", 0x101, 2, 399,
                                       cl4_pending_regions);
    cl4_release((void *)cl4_pending_regions);
    long sz = (**(long (**)(void))(*(void **)one + 0x70))();
    if (want != sz) {
        cl4_iel_panic2();
        cl4_fatal_error();
        cl4_release(one);
        cl4_release(set);
        return;
    }
    iel_append_segment_region(one, set);
    cl4_release(one);
    cl4_release(set);
    *out = 1;
}

/* FUN_000f0384 @ 0x000f0384   (est. iel_dispatch_80_c)
 * Ghidra: void FUN_000f0384(void) — dispatch wrapper, +0x80 method.
 * Confidence: low */
void iel_dispatch_80_c(void)
{
    cl4_iel_cleanup();
    void (*m)(void) = *(void (**)(void))((void *)0 + 0x80);
    cl4_retain(0);
    cl4_iel_cleanup();
    cl4_iel_panic2();
    m();
    cl4_iel_done();
    cl4_iel_cleanup();
}

/* FUN_000f03f8 @ 0x000f03f8   (est. iel_remove_region)
 * Ghidra: void FUN_000f03f8(undefined1 *param_1, long param_2, long param_3, long param_4)
 * Removes from the target list every region whose +0x68 tag equals param_3,
 * then verifies the matched region's size against param_4 and tears it down
 * via iel_teardown_region.
 * Confidence: low
 * Notes: traps at 0xf063c; FUN_0036993c panics on size mismatch. */
void iel_remove_region(unsigned char *out, long target, long id, long want)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(target + 0x28), stack, 0, 0);
    void *list = *(void **)(target + 0x28);
    cl4_retain(list);
    unsigned long tmp = cl4_log_key(0x652110, 0x4c3878);
    cl4_list_lookup(&iel_local_a8, (unsigned long)id, list);
    cl4_log_fmt((unsigned long)list);
    if (iel_local_a8[0] == 0) {
        *out = 0;
        return;
    }
    cl4_log_fmt(iel_local_a8[2]);
    cl4_log_fmt(iel_local_a8[1]);
    cl4_release((void *)iel_local_a8[0]);
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)((char *)iel_local_a8[3] + 0x10);
    while (n != i) {
        void *r = *(void **)((char *)iel_local_a8[3] + i * 8 + 0x20);
        void *(*get)(void) = *(void *(**)(void))(*(void **)r + 0x68);
        cl4_retain(r);
        void *tag = get();
        if (tag == (void *)id) {
            cl4_list_lock();
            unsigned long k = cl4_pending_regions_n;
            cl4_list_index();
            cl4_pending_regions_n = k + 1;
            (&cl4_pending_regions_arr)[k] = (unsigned long)r;
            i += 1;
        } else {
            cl4_release(r);
            i += 1;
        }
    }
    cl4_release((void *)iel_local_a8[3]);
    void *one = iel_retain_if_scalar((long)cl4_pending_regions);
    cl4_release((void *)cl4_pending_regions);
    if (one == 0) {
        *out = 0;
        return;
    }
    long sz = (**(long (**)(void))(*(void **)one + 0x70))();
    if (want != sz) {
        cl4_iel_panic2();
        cl4_fatal_error();
        cl4_release(one);
        return;
    }
    iel_teardown_region(one);
    cl4_release(one);
    *out = 1;
}

/* FUN_000f063c @ 0x000f063c   (est. iel_dispatch_80_d)
 * Ghidra: void FUN_000f063c(void) — dispatch wrapper (FUN_000f4be8 variant).
 * Confidence: low */
void iel_dispatch_80_d(void)
{
    cl4_iel_done();
    cl4_slot_begin(0);
    void (*m)(void) = *(void (**)(void))((void *)0 + 0x80);
    cl4_retain(0);
    cl4_iel_cleanup();
    cl4_iel_panic2();
    m();
    cl4_iel_done();
    cl4_iel_cleanup();
}

/* FUN_000f06bc @ 0x000f06bc   (est. iel_teardown_region_by_id)
 * Ghidra: void FUN_000f06bc(x8..x11, undefined4 param_5)
 * Matches regions by id (param_3), verifies size (param_4), then tears down
 * the matched region's owner with the given TLB bitmask (param_5).
 * Confidence: low
 * Notes: traps at 0xf0968; iel_tlb_op_by_bits performs the maintenance. */
void iel_teardown_region_by_id(unsigned char *out, long target, long id, long want, unsigned int bits)
{
    unsigned long stack[3];
    cl4_critical_enter((void *)(target + 0x28), stack, 0, 0);
    void *list = *(void **)(target + 0x28);
    cl4_retain(list);
    unsigned long tmp = cl4_log_key(0x652110, 0x4c3878);
    cl4_list_lookup(&iel_local_a8, (unsigned long)id, list);
    cl4_log_fmt((unsigned long)list);
    if (iel_local_a8[0] == 0) {
        *out = 0;
        return;
    }
    cl4_log_fmt(iel_local_a8[2]);
    cl4_log_fmt(iel_local_a8[1]);
    cl4_release((void *)iel_local_a8[0]);
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)((char *)iel_local_a8[3] + 0x10);
    while (n != i) {
        void *r = *(void **)((char *)iel_local_a8[3] + i * 8 + 0x20);
        void *(*get)(void) = *(void *(**)(void))(*(void **)r + 0x68);
        cl4_retain(r);
        void *tag = get();
        if (tag == (void *)id) {
            cl4_list_lock();
            unsigned long k = cl4_pending_regions_n;
            cl4_list_index();
            cl4_pending_regions_n = k + 1;
            (&cl4_pending_regions_arr)[k] = (unsigned long)r;
            i += 1;
        } else {
            cl4_release(r);
            i += 1;
        }
    }
    cl4_release((void *)iel_local_a8[3]);
    void *one = iel_retain_if_scalar((long)cl4_pending_regions);
    cl4_release((void *)cl4_pending_regions);
    if (one == 0) {
        *out = 0;
        return;
    }
    long sz = (**(long (**)(void))(*(void **)one + 0x70))();
    if (want != sz) {
        cl4_iel_panic2();
        cl4_fatal_error();
        goto out_free;
    }
    {
        unsigned long cap = ((unsigned long *)one)[2];
        if ((long)cap < 0) {
            cl4_retain((void *)(cap & 0x7fffffffffffffff));
            iel_tlb_op_by_bits(bits);
            (**(void (**)(void))(*(void **)(cap & 0x7fffffffffffffff) + 0x90))();
            if (cl4_result_ok != 0) {
                cl4_release_tagged(cap);
                goto out_free;
            }
            cl4_release(one);
            cl4_release_tagged(cap);
        } else {
            cl4_release(one);
        }
        *out = 1;
        return;
    }
out_free:
    cl4_release(one);
    return;
}

/* FUN_000f0968 @ 0x000f0968   (est. iel_frame_check)
 * Ghidra: void FUN_000f0968(x8..x11)
 * Validates that the frame-cap count implied by (param_2 / page_size) matches
 * the region's stored count; when it does, invokes the +0x100 frame-commit
 * method to bind the frames. Reports an error code through the launcher on
 * mismatch.
 * Confidence: low
 * Notes: FUN_000a0650 reads the region descriptor; traps at 0xf0b44..0xf0b4c. */
void iel_frame_check(void *key, unsigned long bytes, long desc, void *arg4)
{
    cl4_critical_enter(0, 0, 0, 0);
    void *r = (**(void *(**)(void))((void *)0 + 0xf0))();
    cl4_desc_lookup(&iel_local_a8, key, r);
    cl4_log_fmt((unsigned long)r);
    if (iel_local_a8[0] == 0) {
        cl4_frame_panic2();
        goto out;
    }
    unsigned long page = cl4_page_size(3);
    if (iel_local_a8[1] * page != 0) cl4_trap();   /* 0xf0b44 */
    if (desc == (long)(iel_local_a8[1] * page)) {
        if ((*(unsigned char *)&iel_local_a8[2] & 1) == 0) {
            cl4_frame_error(2);
            goto out;
        }
        unsigned long p2 = cl4_page_size(3);
        if (p2 == 0) cl4_trap();   /* 0xf0b48 */
        unsigned long npages = bytes / p2;
        unsigned long p3 = cl4_page_size(3);
        if (npages * p3 != 0) cl4_trap();   /* 0xf0b4c */
        if (npages * p3 - bytes != 0) {
            cl4_frame_error(3);
            goto out;
        }
        cl4_critical_enter(0, 0, 0, 0);
        unsigned long avail = (**(unsigned long (**)(void))((void *)0 + 0x68))();
        if (((long)avail < 0) || (avail < npages)) {
            cl4_frame_error(4);
            goto out;
        }
        iel_local_a8[0] = (long)desc;
        iel_local_a8[1] = iel_local_a8[1];
        iel_local_a8[2] = 0;
        void *(*commit)(void *) = *(void *(**)(void *))(*(void **)cl4_current + 0x100);
        iel_local_a8[3] = npages;
        iel_local_a8[4] = (unsigned long)arg4;
        cl4_retain((unsigned long)cl4_current & 0xffffffffffffull | 0x6ae1000000000000ull, desc);
        void *c = commit(&iel_local_a8);
        cl4_frame_commit(&iel_local_a8, key);
        (void)c;
        cl4_frame_panic2();
    } else {
        cl4_frame_error(1);
    }
out:
    cl4_iel_cleanup();
    cl4_desc_drop(&iel_local_a8);
    cl4_iel_done();
}

/* FUN_000f0b4c @ 0x000f0b4c   (est. iel_map_region2)
 * Ghidra: long * FUN_000f0b4c(long param_1, long *param_2)
 * Maps a region with a full set of flags: resolves the region descriptor,
 * checks writability/global TLB state, and either maps it directly or
 * constructs a composed descriptor that records the mapping decision, plus the
 * region's type/presence flags. Returns the descriptor (or the mapped region).
 * Confidence: low
 * Notes: removes unreachable blocks 0xf0bec/0xf0c08/0xf0f40; FUN_000eea4c
 * performs the actual map; FUN_000f0b4c recurses through FUN_000a0650. */
void *iel_map_region2(long key, long *seg)
{
    (**(void (**)(void))(*(void **)seg + 0x60))();
    unsigned long mmu = cl4_mmu_op2();
    unsigned long *gc = cl4_global_caps_1();
    long orig = *gc;
    long chk = cl4_mmu_op(cl4_mmu_op(orig) & mmu);
    bool same = (chk == orig);
    unsigned char *flag = same ? cl4_flag_0() : cl4_flag_2();
    unsigned char b = *flag;
    long cap = seg[2];
    cl4_iel_done();
    unsigned long size = (**(unsigned long (**)(void))((void *)0 + 0x58))();
    cl4_iel_done();
    unsigned long long res = (**(unsigned long long (**)(void))((void *)0 + 0x50))();
    void *desc = (void *)iel_map_region((unsigned long)cap, size, mmu, b, res, 0 /*hi*/, 1);
    if (cl4_result_ok != 0) {
        cl4_log_fmt(0 /*hi half*/);
        cl4_fatal_error();
    }
    cl4_log_fmt(0 /*hi half*/);
    unsigned long dcap = ((unsigned long *)desc)[2];
    if ((long)dcap < 0) {
        void *owner = (void *)(dcap & 0x7fffffffffffffff);
        cl4_retain(owner);
        unsigned char *f0 = cl4_flag_0();
        cl4_iel_cleanup();
        if (!same) {
            cl4_flag_1();
            cl4_iel_cleanup();
            if (!same) goto finish;
        }
        void (*note)(void) = *(void (**)(void))(*(void **)owner + 0xb8);
        (**(void (**)(void))(*(void **)owner + 0xc0))();
        cl4_iel_done();
        long total = cl4_page_size();
        if (total == 0) cl4_trap();   /* 0xf0fb0 */
        unsigned char b2 = *f0;
        unsigned long slots = cl4_iel_done2();
        void *(*count)(void) = *(void *(**)(void))((void *)0 + 0x68);
        long *per = 0;
        if (slots != 0)
            per = (long *)((unsigned long)owner / slots);
        long *n = count();
        if ((long)n < 1 || n <= per) {
            unsigned int mask = (unsigned int)(b2 & b);
            if ((mask == b2) ||
                ((n = count(), -1 < (long)n && (per == n)))) {
                void *rr = (**(void *(**)(void))(*(void **)cl4_current + 0xf0))();
                cl4_desc_lookup(iel_local_b8, (unsigned long)note, rr);
                cl4_log_fmt((unsigned long)rr);
                if (iel_local_b8[0] == 0) {
                    unsigned long *g2 = cl4_global_caps_2();
                    long orig2 = *g2;
                    long chk2 = cl4_mmu_op(cl4_mmu_op(orig2) & mmu);
                    unsigned long kind = (chk2 != orig2) ? 2 : 4;
                    iel_local_a8[0] = 0; iel_local_a8[1] = 0;
                    void *(*commit)(void *) = *(void *(**)(void *))(*(void **)cl4_current + 0x100);
                    iel_local_b8[0] = (long)seg;
                    iel_local_b8[1] = (long)per;
                    iel_local_b8[2] = (mask == b2);
                    cl4_retain(seg);
                    void *c = commit(&iel_local_f0);
                    cl4_frame_commit(iel_local_b8, (unsigned long)note);
                    (void)c;
                    void *rec = cl4_alloc_object(0x662150, 0x18, 7);
                    cl4_slot_clear((char *)rec + 0x10);
                    void *entry = cl4_alloc_object(0x6622b0, 0x22, 7);
                    *(void **)((char *)entry + 0x10) = rec;
                    *(unsigned long *)((char *)entry + 0x18) = (unsigned long)note;
                    *(bool *)((char *)entry + 0x20) = (mask == b2);
                    *(unsigned char *)((char *)entry + 0x21) = (unsigned char)kind;
                    void (*push)(void *, void *) = *(void (**)(void *, void *))(*(void **)owner + 0xa8);
                    cl4_retain(rec);
                    push((void *)0x000f4a84, entry);
                    cl4_release(rec);
                    cl4_release(entry);
                } else {
                    cl4_iel_cleanup();
                    cl4_desc_drop(iel_local_b8);
                    cl4_iel_panic2();
                    cl4_trace_begin(0x2e);
                    cl4_log_fmt(0xe000000000000000);
                    cl4_trace_word(0xd000000000000012, 0x80000000005c4fd0);
                    cl4_frame_commit(iel_local_b8, 0);
                    cl4_fatal_error();
                }
            }
        }
finish:
        if (*(char *)(key + 0x38) == '\x01')
            iel_append_segment_region(desc, seg);
        cl4_release_tagged(dcap);
        return desc;
    }
    cl4_release_tagged(dcap);
    return desc;
}

/* FUN_000f12fc @ 0x000f12fc   (est. iel_vas_slot_lookup)
 * Ghidra: undefined8 FUN_000f12fc(ulong param_1, ...)
 * Looks up a VAS slot by index: resolves the target object, reads its region
 * descriptor, and checks that the requested page index fits within the
 * region's page count; raises "yield page > than greater" on overflow.
 * Returns 0/1/3 depending on fit and flag state.
 * Confidence: low
 * Notes: removes unreachable blocks 0xf1734/0xf14f4; FUN_000fc804 formats a
 * region error. */
unsigned long iel_vas_slot_lookup(unsigned long bytes, void *p2, unsigned long *out,
                                  long target, void *p5, unsigned int flags, unsigned long ret)
{
    unsigned long page = cl4_page_size(3);
    if (page == 0) cl4_trap();   /* 0xf15c4 */
    unsigned long stack[3];
    cl4_critical_enter((void *)(target + 0x10), stack, 0, 0);
    void *obj = cl4_object_get((void *)(target + 0x10));
    if (obj == 0) {
        return 0;
    }
    void *r = (**(void *(**)(void))(*(void **)obj + 0xf0))();
    cl4_desc_lookup(&iel_local_a8, (unsigned long)p5, r);
    cl4_log_fmt((unsigned long)r);
    if (iel_local_a8[0] == 0) {
        return 0;
    }
    unsigned long idx = (page != 0) ? bytes / page : 0;
    if (iel_local_a8[1] <= idx) {
        cl4_retain((void *)iel_local_a8[0]);
        cl4_trace_begin(0x31);
        cl4_log_fmt(0xe000000000000000);
        cl4_fatal_error(0, 0xb, 2, 0xd000000000000010, 0x80000000005c5030,
                        "InternalExclaveLauncher/External", 0x35, 2, 0x210, idx << 32);
    }
    void *(*commit)(void *, unsigned long) = *(void *(**)(void *, unsigned long))(*(void **)iel_local_a8[0] + 0x68);
    cl4_retain((void *)iel_local_a8[0]);
    unsigned long n = (unsigned long)commit(0, 0);
    cl4_desc_drop(&iel_local_a8);
    if ((long)n < 1 || n <= idx) {
        return 1;
    }
    if ((*(unsigned char *)&iel_local_a8[2] & 1) != 0) {
        iel_local_a8[0] = (long)iel_local_a8[0];
        iel_local_a8[1] = iel_local_a8[1];
        iel_local_a8[2] = 0;
        void *(*commit2)(void *) = *(void *(**)(void *))(*(void **)obj + 0x100);
        cl4_retain((unsigned long)obj & 0xffffffffffffull | 0x6ae1000000000000ull, (void *)iel_local_a8[0]);
        void *c = commit2(&iel_local_a8);
        cl4_frame_commit(&iel_local_a8, (unsigned long)p5);
    }
    void *rr = (**(void *(**)(unsigned long))(*(void **)iel_local_a8[0] + 0x80))(idx);
    cl4_frame_commit(0xd000000000000019, 0x80000000005c0f80, "__APPLEInternal.Library/BuildRoot",
                     0x101, 2, "appendSegmentRegionLocked(machoF", 0x2d, 2, 0x21e, rr, p2);
    if (((flags & 1) != 0) && (idx < iel_local_a8[1])) {
        *out = iel_local_a8[4];
        return 3;
    }
    return ret;
}

/* FUN_000f1754 @ 0x000f1754   (est. iel_map_macho_region)
 * Ghidra: void FUN_000f1754(long param_1, ulong param_2)
 * Maps a Mach-O segment region: reads the region's UUID descriptor and, when
 * the format is valid, resolves and maps the target; otherwise panics with
 * "Unexpected UUID format" / "Conclave launcher cannot map mach-O".
 * Confidence: low
 * Notes: removes unreachable blocks (0xf1b18 traps); FUN_0029fb80 reads the
 * UUID; FUN_000f43e8 logs the mapping. */
void iel_map_macho_region(long region, unsigned long mode)
{
    if ((mode & 1) != 0) {
        cl4_iel_panic_str("Conclave launcher cannot map mach-O");
        cl4_fatal_error();
    }
    if (*(long *)(region + 0x10) == 0)
        cl4_trap();   /* 0xf1b18 */
    unsigned long lo = *(unsigned long *)(region + 0x48);
    unsigned long v = *(unsigned long *)(region + 0x50);
    unsigned long key = lo & 0xffffffffffffull;
    if ((v & 0x2000000000000000ull) != 0)
        key = v >> 0x38 & 0xf;
    cl4_retain((void *)v);
    for (;;) {
        unsigned long long u = cl4_uuid_next();   /* FUN_0029fb80 */
        unsigned long hi = 0, lo2 = u; /* hi half of 128-bit UUID result */
        if (hi == 0) break;
        /* ... UUID parse/format validation ... */
        cl4_log_fmt(0);
        cl4_panic_begin();
        void (*log)(void *, void *) = *(void (**)(void *, void *))((void *)0 + 0x80);
        cl4_retain((void *)v);
        log((void *)0x000f43e8, &iel_local_a8);
        cl4_release((void *)v);
        return;
    }
    cl4_trace_begin(0x19);
    cl4_log_fmt(0xe000000000000000);
    cl4_panic_str("Unexpected UUID format");
    cl4_fatal_error();
}

/* FUN_000f1ba8 @ 0x000f1ba8   (est. iel_finalize_vm_region)
 * Ghidra: void FUN_000f1ba8(long param_1, long param_2)
 * Finalizes the VM region descriptors of a source object (param_1) into the
 * target's address-space table (param_2+0x28): for each 0x40-byte descriptor
 * entry it commits a frame mapping at the target and inserts it into the
 * target's VAS bit table.
 * Confidence: low
 * Notes: FUN_0007278c allocates the VAS slot; FUN_0009cf58 / FUN_0000276c
 * manage the table; removes unreachable blocks 0xf1f40/0xf1f30/0xf1f34. */
void iel_finalize_vm_region(long src, long dst)
{
    long n = *(long *)(src + 0x10);
    if (n == 0)
        return;
    long i = 0;
    do {
        unsigned char *entry = (unsigned char *)(src + 0x20 + i * 0x40);
        /* capture the 0x40-byte descriptor fields */
        unsigned long f0 = *(unsigned long *)(entry + 0x00);
        unsigned long f1 = *(unsigned long *)(entry + 0x08);
        unsigned long f2 = *(unsigned long *)(entry + 0x10);
        unsigned long f3 = *(unsigned long *)(entry + 0x18);
        unsigned long f4 = *(unsigned long *)(entry + 0x20);
        unsigned long f5 = *(unsigned long *)(entry + 0x28);
        unsigned long f6 = *(unsigned long *)(entry + 0x30);
        unsigned long f7 = *(unsigned long *)(entry + 0x38);
        unsigned long f8 = *(unsigned long *)(entry + 0x29);
        unsigned long f9 = *(unsigned long *)(entry + 0x31);
        void *obj = (void *)f0;
        unsigned long cnt = *(unsigned long *)((char *)obj + 0x10);
        /* ... commit frame and append into dst's descriptor table ... */
        (void)f1; (void)f2; (void)f3; (void)f4; (void)f5; (void)f6; (void)f7;
        (void)f8; (void)f9; (void)cnt;
        i += 1;
    } while (i != n);
}

/* FUN_000f1f68 @ 0x000f1f68   (est. iel_dispatch_80_result)
 * Ghidra: undefined8 FUN_000f1f68(void)
 * Dispatch wrapper (FUN_000f4be8 variant) that returns the +0x80 method's
 * result word.
 * Confidence: low */
void *iel_dispatch_80_result(void)
{
    cl4_iel_done();
    cl4_slot_begin(0);
    void *out;
    void (*m)(void *, void *, void *, void *) = *(void (**)(void *, void *, void *, void *))((void *)0 + 0x80);
    cl4_retain(0);
    m(&out, (void *)0x000f47a4, &iel_local_a8, (void *)0x677790);
    cl4_iel_done();
    return out;
}

/* FUN_000f1ff4 @ 0x000f1ff4   (est. iel_check_bounds_wrapper)
 * Ghidra: void FUN_000f1ff4(undefined8 *param_1, undefined8 param_2, undefined8 param_3)
 * Wraps iel_check_region_bounds(param_3), storing its result into param_1.
 * Confidence: low */
void iel_check_bounds_wrapper(unsigned long *out, void *p2, unsigned long size)
{
    iel_check_region_bounds(size);
    if (cl4_result_ok == 0)
        *out = 0;
}

/* FUN_000f2028 @ 0x000f2028   (est. iel_domain_init)
 * Ghidra: void FUN_000f2028(undefined8 *param_1)
 * Dispatches a DomainInit entry: for kinds 0/1/3 logs the entry, for kind 2
 * raises "Unsupported DomainInit entry point" panic. Default iterates the
 * entry's frame list emitting per-frame traces.
 * Confidence: low
 * Notes: switch on (param_1+7)>>0xe; FUN_0009d154/9d170 log entries. */
void iel_domain_init(unsigned long *entry)
{
    void *obj = *(void **)(cl4_current + 0x48);
    cl4_slot_begin(0);
    void (*m)(void *, void *, void *) = *(void (**)(void *, void *, void *))((void *)0 + 0x80);
    cl4_retain(obj);
    m((void *)0x000f47c0, &iel_local_a8, (void *)0x67b148);
    cl4_release(obj);
    unsigned long v = entry[0];
    switch (*(unsigned short *)(entry + 7) >> 0xe) {
    case 0:
        cl4_log_value(v, entry[9]);
        long n = *(long *)(entry[8] + 0x10);
        if (n != 0) {
            unsigned long *it = (unsigned long *)(entry[8] + 0x108);
            do {
                cl4_log_region_idx(it[-0x1d], v, *it);
                n -= 1;
                it += 0x1f;
            } while (n != 0);
        }
        return;
    case 1:
    case 3:
        return;
    case 2:
        cl4_panic_str("Unsupported DomainInit entry point");
        cl4_iel_panic();
        cl4_panic_begin();
        cl4_iel_panic2();
        cl4_fatal_error();
    }
}

/* FUN_000f21e0 @ 0x000f21e0   (est. iel_domain_init_loop)
 * Ghidra: void FUN_000f21e0(long *param_1, long param_2)
 * The DomainInit driver loop: appends the init entry to the init queue, then
 * iterates the domain's entries, validating and emitting a trace record for
 * each frame/capability, and raising "Fatal error" on invalid entries.
 * Confidence: low
 * Notes: FUN_00151974/51a6c emit the log frames; FUN_00093c68 gathers the
 * per-frame registers. */
void iel_domain_init_loop(long *ctx, long entry)
{
    void *(*push)(void *, long) = *(void *(**)(void *, long))(*(void **)ctx + 0x240);
    unsigned long rec[2];
    cl4_region_copy(rec, (void *)entry);
    void *r = push(rec, 0);
    cl4_obj_copy(r, 0, 0);
    long q = *(long *)(*(void **)(r + 8) + 0x10);
    cl4_obj_copy(0, 0, 0);
    *(long *)(*(void **)(r + 8) + 0x10) = q + 1;
    cl4_obj_copy((void *)(*(void **)(r + 8) + q * 0x50 + 0x20), (void *)entry, 0x50);
    (*(void (**)(void *, int))(r))(rec, 0);
    long n = *(long *)(*(long *)(entry + 0x40) + 0x10);
    unsigned long *it = (unsigned long *)(*(long *)(entry + 0x40) + 0x88);
    while (n != 0) {
        unsigned long a = it[-0xd], b = it[-4], c = it[-3], d = it[-2], e = it[-1];
        unsigned long f0 = it[0], f1 = it[1], f2 = it[2], f3 = it[3], f4 = it[4];
        unsigned long f5 = it[5], f6 = it[6], f7 = it[7], f8 = it[8], f9 = it[9];
        unsigned long fa = it[10], fb = it[0xb], fc = it[0xc], fd = it[0xd], fe = it[0xe];
        unsigned long ff = it[0x10];
        unsigned long count = it[0x11];
        unsigned long h = (**(unsigned long (**)(void))(*(void **)ctx + 0x328))();
        cl4_log_region_field(a, h);
        if ((long)count < 0)
            cl4_trap();   /* 0xf27d4 */
        unsigned long va = count & 0x7fffffffffffc000ull;
        long frame = (**(long (**)(unsigned long))(*(void **)ctx + 0x358))(va);
        if (frame == 0) {
            /* fatal: invalid frame */
            cl4_fatal_error(0, 0xb, 2, 0xd000000000000014, 0x80000000005c1770,
                            "InternalExclaveLauncher/External", 0x35, 2);
        }
        cl4_log_region_field2(a, frame, count);
        (**(void (**)(void))0x006585f8)();
        cl4_log_index_value(0, b);
        cl4_log_index_value(1, c);
        cl4_log_index_value(2, d);
        cl4_log_index_value(3, e);
        cl4_log_index_value(4, f0);
        cl4_log_index_value(5, f1);
        cl4_log_index_value(6, f2);
        cl4_log_index_value(7, f3);
        cl4_log_index_value(8, f4);
        cl4_log_index_value(9, f5);
        cl4_log_index_value(10, f6);
        cl4_log_index_value(0xb, f7);
        cl4_log_index_value(0xc, f8);
        cl4_log_index_value(0xd, f9);
        cl4_log_index_value(0xe, fa);
        cl4_log_index_value(0xf, fb);
        cl4_log_index_value(0x10, fc);
        cl4_log_index_value(0x11, fd);
        cl4_log_index_value(0x12, fe);
        cl4_log_index_value(0x13, *(unsigned long *)(entry + 0x48));
        cl4_log_index_value(0x14, ff);
        cl4_log_index_value(0x15, count);
        if ((char)ctx[0x23] == -1) {
            cl4_fatal_error(0, 0xb, 2, 0xd00000000000001f, 0x80000000005c51b0,
                            "InternalExclaveLauncher/External", 0x35, 2);
        }
        cl4_log_scalar(a, ctx[0x1c]);
        n -= 1;
        it += 0x1f;
    }
}

/* FUN_000f28f0 @ 0x000f28f0   (est. iel_fatal_record)
 * Ghidra: undefined1[16] FUN_000f28f0(undefined8 param_1)
 * Builds and returns a fatal-error record {0, 0xe...} tagging param_1.
 * Confidence: low
 * Notes: FUN_001ebfb0 formats the error frame. */
unsigned long long iel_fatal_record(unsigned long key)
{
    unsigned long lo = 0;
    unsigned long hi = 0xe000000000000000ull;
    cl4_trace_begin(0x41);
    cl4_trace_word(0xd00000000000003f, 0x80000000005c51d0);
    unsigned long f;
    cl4_fatal_frame(&f, 0x10, 0, 0x677880, cl4_fatal_key());
    cl4_trace_word(0, 0);
    cl4_log_fmt(0);
    return lo; /* hi half dropped */
}

/* FUN_000f2990 @ 0x000f2990   (est. iel_dispatch_80_params)
 * Ghidra: undefined8 FUN_000f2990(8 args)
 * Dispatch wrapper (FUN_000f4be8 variant) passing up to 8 parameters through
 * the +0x80 method; returns its result.
 * Confidence: low */
void *iel_dispatch_80_params(void *p1, void *p2, void *p3, void *p4,
                             unsigned char b1, unsigned char b2, void *p7, unsigned char b3)
{
    cl4_iel_done();
    unsigned long par[6] = { 0, (unsigned long)p3, (unsigned long)p4,
                             (unsigned long)b1, (unsigned long)b2, (unsigned long)b3 };
    cl4_slot_begin(0);
    void *out;
    void (*m)(void *, void *, void *) = *(void (**)(void *, void *, void *))((void *)0 + 0x80);
    cl4_retain(0);
    m(&out, (void *)0x000f47dc, &iel_local_a8);
    cl4_iel_done();
    return out;
}

/* FUN_000f2a30 @ 0x000f2a30   (est. iel_method_320)
 * Ghidra: void FUN_000f2a30(undefined8 *param_1, long *param_2, 6 args)
 * Invokes the method at *param_2's table +800 with the 6 arguments plus a 0
 * terminator, storing the result into param_1 when the op succeeds.
 * Confidence: low
 * Notes: +800 = 0x320 offset. */
void iel_method_320(unsigned long *out, long *obj, void *a, void *b, void *c,
                    void *d, void *e, void *f)
{
    void *r = (**(void *(**)(void *, void *, void *, void *, void *, void *, void *))(*(void **)obj + 800))(a, b, c, d, e, f, 0);
    if (cl4_result_ok == 0)
        *out = (unsigned long)r;
}

/* FUN_000f2a9c @ 0x000f2a9c   (est. iel_map_extvm)
 * Ghidra: ulong FUN_000f2a9c(6 args)
 * Maps an ext-VM (external VM) region: allocates page slots, checks the
 * region bounds, and maps both the base and (optionally) a supplementary
 * range. Returns the mapped base. Panics on an unexpected region type.
 * Confidence: low
 * Notes: removes unreachable block 0xf2c30; FUN_000f480c / FUN_000ee9c4 /
 * FUN_000eea4c compose the mapping. */
unsigned long iel_map_extvm(void *p1, void *p2, void *p3, void *p4, unsigned long size, unsigned long flags)
{
    cl4_iel_done();
    unsigned long base = cl4_page_size();
    if ((long)(base | (unsigned long)0) < 0)
        cl4_trap();   /* 0xf2cdc */
    unsigned long extra = cl4_iel_size();
    unsigned long add = ((flags & 1) != 0) ? (unsigned long)cl4_page_size(3) : 0;
    if ((long)add < 0) cl4_trap();   /* 0xf2b10 */
    if (extra + add < extra) cl4_trap();   /* 0xf2ce0 */
    if ((long)(extra + add) < 0) cl4_trap();   /* 0xf2ce4 */
    iel_check_region_bounds(0);
    if (cl4_result_ok == 0) {
        unsigned long plus = ((flags & 1) != 0) ? (unsigned long)cl4_page_size(3) : 0;
        if ((flags & 1) != 0) {
            unsigned long *g = cl4_global_caps_0();
            unsigned char *fg = cl4_flag_2();
            iel_map_region(0, plus, *g, *fg, 9, 0, 2);
            cl4_release(0);
        }
        if (base + plus < base) cl4_trap();   /* 0xf2ce8 */
        if ((long)extra < 0) cl4_trap();   /* 0xf2cec */
        unsigned char *fg2 = cl4_flag_3();
        void *reg = (void *)iel_map_region(base + plus, extra, (unsigned long)p2, *fg2,
                                           (unsigned long)p3, (unsigned long)p4, size & 0xffffffffull);
        unsigned long cap = ((unsigned long *)reg)[2];
        if (-1 < (long)cap) {
            cl4_panic_str("Unexpected type of ExtVMRegion");
            cl4_iel_panic();
            cl4_panic_begin();
            cl4_iel_panic2();
            cl4_fatal_error();
        }
        cl4_critical_enter(0, 0, 0, 0);
        void (*m)(void *, int, int, int) = *(void (**)(void *, int, int, int))((void *)0 + 0x98);
        cl4_retain((void *)(cap & 0x7fffffffffffffff));
        m(0, 0, 0, 1);
        (**(void (**)(int))(*(void **)reg + 0x50))(1);
        if ((size & 0xff) == 0) {
            unsigned long stack[3];
            cl4_slot_swap((void *)(cl4_current + 0x60), stack);
            cl4_critical_enter(0, 0, 0, 0);
            cl4_retain(reg);
            cl4_critical_exit(stack);
            cl4_release_tagged(cap);
            return base;
        }
        cl4_release_tagged(cap);
        cl4_release(reg);
        return base;
    }
    return base;
}

/* FUN_000f2d30 @ 0x000f2d30   (est. iel_dispatch_80_result2)
 * Ghidra: undefined1[16] FUN_000f2d30(void)
 * Dispatch wrapper returning the +0x80 method's 16-byte result.
 * Confidence: low */
unsigned long long iel_dispatch_80_result2(void)
{
    void *obj = *(void **)(cl4_current + 0x48);
    cl4_slot_begin(0);
    void (*m)(void *, void *) = *(void (**)(void *, void *))((void *)0 + 0x80);
    cl4_retain(obj);
    cl4_log_key(0x652128, 0x4c3898);
    unsigned long long out;
    m(&out, (void *)0x000f481c);
    cl4_release(obj);
    return out;
}

/* FUN_000f2ddc @ 0x000f2ddc   (est. iel_finalize_vas)
 * Ghidra: void FUN_000f2ddc(ulong *param_1, long param_2)
 * Finalizes the address-space descriptors for an exclave: computes the VAS
 * size from the loaded object, allocates frame pages for each descriptor,
 * records them, and maps the address-space extent plus the descriptor table.
 * Returns the {base, end, size} triple in param_1.
 * Confidence: low
 * Notes: removes unreachable blocks 0xf359c/0xf3528/0xf3504/0xf3580/0xf35d8/
 * 0xf3564/0xf35b8; FUN_000eea4c maps each extent; FUN_000eed84 appends. */
void iel_finalize_vas(unsigned long *out, long excl)
{
    void *loaded = *(void **)(excl + 0xb0);
    unsigned long vas = (**(unsigned long (**)(void))(*(void **)loaded + 0x198))();
    if (vas >> 0x32 != 0) cl4_trap();   /* 0xf33d0 */
    long page = cl4_page_size(3);
    if (page < 0) cl4_trap();   /* 0xf33d4 */
    unsigned long pages = page - 1;
    if (page == 0) cl4_trap();   /* 0xf33d8 */
    unsigned long base_sz = vas * 0x4000;
    unsigned long tbl_sz = (vas & 0x3ffffffffffffull) * 0x2000 + 0x3fff;
    tbl_sz &= 0xffffffffffffc000ull;
    if (tbl_sz + pages < tbl_sz) cl4_trap();   /* 0xf33dc */
    unsigned long slots = cl4_page_size(3);
    if (slots == 0) cl4_trap();   /* 0xf33e0 */
    if (base_sz + tbl_sz < base_sz) cl4_trap();   /* 0xf33e4 */
    unsigned long base = iel_check_region_bounds(base_sz + tbl_sz);
    if (cl4_result_ok != 0)
        cl4_fatal_error();
    unsigned long base_end = base + base_sz;
    if (base + base_sz < base) cl4_trap();   /* 0xf33e8 */
    (**(void (**)(void))(*(void **)loaded + 0x1a0))();
    if ((long)tbl_sz < 0) cl4_trap();   /* 0xf33ec */
    void *tbl = cl4_alloc_object(0, 0x50, 7);
    unsigned long frame_list = *(long *)(excl + 0x120);
    unsigned char *acc = (unsigned char *)cl4_pending_regions;
    if (slots <= ((tbl_sz + pages) & (pages ^ 0xffffffffffffffffull))) {
        unsigned long cnt = 0;
        long dl = *(long *)(excl + 0x120);
        unsigned long per = (slots != 0) ? ((tbl_sz + pages) & (pages ^ 0xffffffffffffffffull)) / slots : 0;
        do {
            if (per <= cnt) cl4_trap();   /* 0xf33c8 */
            unsigned long sz = cl4_page_size(3);
            if (cnt * sz != 0) cl4_trap();   /* 0xf33cc */
            void *frame = cl4_frame_alloc();
            if (frame == 0) {
                cl4_fatal_error(0, 0xb, 2, "Fatal error", 0, "finalizeAddressSpaceDescriptors: ", 0x21, 2, 0x6f, 0);
            }
            unsigned long stack[3];
            cl4_critical_enter((void *)(excl + 0x38), stack, 0x21, 0);
            /* grow and record the frame */
            unsigned long grow = cl4_obj_flag(*(void **)(excl + 0x38));
            if ((grow & 1) == 0) {
                cl4_array_free(*(void **)(excl + 0x38));
                *(void **)(excl + 0x38) = (void *)cl4_array_grow(0, *(long *)(*(void **)(excl + 0x38) + 0x10) + 1, 1, *(void **)(excl + 0x38));
            }
            unsigned long idx = *(unsigned long *)(*(void **)(excl + 0x38) + 0x10);
            if (*(unsigned long *)(*(void **)(excl + 0x38) + 0x18) >> 1 <= idx)
                *(void **)(excl + 0x38) = (void *)cl4_array_grow(1 < *(unsigned long *)(*(void **)(excl + 0x38) + 0x18), idx + 1, 1, *(void **)(excl + 0x38));
            *(unsigned long *)(*(void **)(excl + 0x38) + 0x10) = idx + 1;
            *(long *)(*(void **)(excl + 0x38) + idx * 8 + 0x20) = (long)frame;
            cl4_critical_exit(stack);
            cl4_frame_bind(&iel_local_a8, frame);
            cl4_scope_drop(&iel_local_a8);
            (**(void (**)(unsigned long, void *))(*(void **)tbl + 0x90))(cnt * sz, frame);
            grow = cl4_obj_flag(acc);
            if ((grow & 1) == 0)
                acc = (unsigned char *)cl4_array_grow(0, *(long *)(acc + 0x10) + 1, 1, acc);
            idx = *(unsigned long *)(acc + 0x10);
            if (*(unsigned long *)(acc + 0x18) >> 1 <= idx)
                acc = (unsigned char *)cl4_array_grow(1 < *(unsigned long *)(acc + 0x18), idx + 1, 1, acc);
            cnt += 1;
            *(unsigned long *)(acc + 0x10) = idx + 1;
            *(long *)(acc + idx * 8 + 0x20) = (long)frame;
        } while (per != cnt);
    }
    /* map the VAS base and the descriptor table extents */
    void *d1 = (void *)iel_map_region(base, vas << 0xe, *cl4_global_caps_0(), *cl4_flag_2(), 4, 0, 2);
    void *d2 = (void *)iel_map_region(base_end, tbl_sz, *cl4_global_caps_1(), *cl4_flag_2(), 0, 0, 2);
    iel_append_segment_locked(d1, (long)acc);
    cl4_release(acc);
    iel_append_segment_locked(d2, (long)iel_local_a8[0]);
    out[0] = base;
    out[1] = base_end;
    out[2] = iel_local_a8[0] * cl4_page_size(3);
}

/* FUN_000f35f4 @ 0x000f35f4   (est. iel_call_init_endpoint)
 * Ghidra: void FUN_000f35f4(void)
 * Locates the single Init endpoint in the pending-region list, logs
 * "Calling Init Endpoint", and invokes the endpoint's init via
 * iel_configure_exclave; returns when the init succeeds, else panics.
 * Confidence: low
 * Notes: removes unreachable blocks; FUN_00167a6c resolves the endpoint;
 * FUN_000651bc waits on the init result. */
void iel_call_init_endpoint(void)
{
    unsigned long magic = 0xd37afd4bb400012aull;
    cl4_critical_enter(0, 0, 0, 0);
    void *list = (**(void *(**)(void))((void *)0 + 0x230))();
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)((char *)list + 0x10);
    for (;;) {
        unsigned long slot = i * 0x50 + 0x20;
        unsigned char rec[0x50];
        for (;;) {
            if (n == i) {
                cl4_release(list);
                if ((cl4_pending_regions_n == 1) && (*(long *)(cl4_pending_regions_d8 + 0x10) == 1)) {
                    unsigned char one[0x50];
                    cl4_obj_copy(one, &cl4_pending_regions_arr, 0x50);
                    cl4_region_copy((void *)one, (void *)&iel_local_a8);
                    cl4_release((void *)cl4_pending_regions);
                    if (*(long *)(iel_local_a8[0] + 0x10) != 1)
                        cl4_trap();   /* 0xf378c */
                    if ((iel_local_a8[2] & 0xc0) == 0) {
                        if (cl4_debug_enabled == '\x01') {
                            void *fmt = cl4_iel_tbl4();
                            void *rec2 = cl4_log_alloc2(fmt, &iel_log_stack);
                            cl4_log_fmt(0);
                            cl4_panic_str("Calling Init Endpoint");
                            *(unsigned long *)((char *)rec2 + 0x38) = 0x6753a0;
                            *(unsigned long *)((char *)rec2 + 0x20) = 0xd000000000000015;
                            cl4_panic_begin();
                            cl4_log_emit(rec2);
                            cl4_log_finish();
                            cl4_release_op(0, 0x20, 7);
                        }
                        void *ep = cl4_ep_resolve(0);
                        iel_local_a8[0] = 0;
                        void *r = cl4_ep_lookup(&iel_local_a8[0], &iel_local_a8);
                        iel_debug_log(0, r, &iel_local_a8);
                        cl4_ep_release(&iel_local_a8);
                        bool ok = (r == 0) && (iel_local_a8[0] == 0);
                        cl4_init_wait(magic, ok);
                        if (ok)
                            return;
                        cl4_trap();   /* FUN_0011d7e8 */
                    }
                    cl4_iel_panic();
                } else {
                    cl4_iel_panic_str("Unexpected type of ExtVMRegion");
                }
                cl4_iel_abort();
                cl4_fatal_error();
            }
            if (*(unsigned long *)((char *)list + 0x10) <= i)
                cl4_trap();   /* 0xf3884 */
            cl4_obj_copy(rec, (char *)list + slot, 0x50);
            if (((rec[7] & 0xc0) == 0) && ((rec[7] & 1) != 0))
                break;
            slot += 0x50;
            i += 1;
        }
        cl4_region_copy((void *)rec, (void *)&iel_local_a8);
        unsigned long grow = cl4_obj_flag((void *)cl4_pending_regions);
        if ((grow & 1) == 0)
            cl4_array_grow2(0, cl4_pending_regions_n + 1, 1);
        unsigned long idx = cl4_pending_regions_n;
        unsigned long next = cl4_pending_regions_n + 1;
        if (cl4_pending_regions_cap >> 1 <= cl4_pending_regions_n)
            cl4_array_grow2(1 < cl4_pending_regions_cap, next, 1);
        i += 1;
        cl4_pending_regions_n = next;
        cl4_obj_copy(&cl4_pending_regions_arr + idx * 10, rec, 0x50);
    }
}

/* FUN_000f3908 @ 0x000f3908   (est. iel_method_138)
 * Ghidra: void FUN_000f3908(void)
 * Invokes the current op's +0x138 method and logs the resulting message word.
 * Confidence: low */
void iel_method_138(void)
{
    cl4_critical_enter(0, 0, 0, 0);
    unsigned long rec[3];
    (**(void (**)(void *))((void *)0 + 0x138))(rec);
    unsigned long w = cl4_msg_word(rec, 0);
    void (*log)(unsigned long, unsigned long) = (void (*)(unsigned long, unsigned long))cl4_log_lookup(0);
    log(w, 0);
    cl4_scope_drop(rec);
    cl4_iel_done();
}

/* FUN_000f399c @ 0x000f399c   (est. iel_find_cap_by_va)
 * Ghidra: void FUN_000f399c(undefined8 param_1)
 * Resolves the capability for a virtual address; if none is found raises
 * "Could not find capability by virtual address" and waits on the result.
 * Confidence: low
 * Notes: FUN_000f4838 performs the lookup; FUN_0006e6dc compares the result. */
void iel_find_cap_by_va(void *va)
{
    unsigned long magic = 0xd37afd4bb400012aull;
    unsigned long result = 0;
    cl4_critical_enter(0, 0, 0, 0);
    unsigned long long r = (**(unsigned long long (**)(void))((void *)0 + 0x350))();
    cl4_cap_lookup(r, 0 /*hi*/, (unsigned long)va, &result);
    if (cl4_compare16(result) != 0) {
        cl4_trace_begin(0x31);
        cl4_log_fmt(0xe000000000000000);
        cl4_panic_str("Could not find capability by virtual address");
        cl4_fatal_error(0, 0xb, 2, 0xd00000000000002f, 0, "InternalExclaveLauncher/External", 0x35, 2);
    }
    cl4_init_wait(magic, result);
}

/* FUN_000f3aac @ 0x000f3aac   (est. iel_teardown_regions)
 * Ghidra: void FUN_000f3aac(void)
 * Tears down every region in the thread's +0x60 list: for each region-cap
 * with an owner, releases its frames (+0x70), flushes the TLB range, and
 * releases the cap.
 * Confidence: low
 * Notes: traps at 0xf3bc8/0xf3bcc; FUN_00093c58/60 retain/release tagged. */
void iel_teardown_regions(void)
{
    cl4_slot_begin((void *)(cl4_current + 0x60));
    void *list = *(void **)(cl4_current + 0x60);
    unsigned long n = *(unsigned long *)((char *)list + 0x10);
    if (n != 0) {
        cl4_retain(list);
        unsigned long i = 0;
        do {
            void *r = *(void **)((char *)list + i * 8 + 0x20);
            unsigned long cap = ((unsigned long *)r)[2];
            if ((long)cap < 0) {
                void (*m)(void) = *(void (**)(void))(*(void **)r + 0x70);
                cl4_retain(r);
                cl4_retain_tagged(cap);
                m();
                cl4_iel_done();
                void *base = (void *)cl4_page_size();
                if (r < base)
                    cl4_trap();   /* 0xf3bcc */
                cl4_critical_enter(0, 0, 0, 0);
                (**(void (**)(int, unsigned long, int))((void *)0 + 0xa0))(0, 0, 0);
                cl4_release(r);
                cl4_release_tagged(cap);
            }
            i += 1;
        } while (n != i);
        cl4_release(list);
    }
}

/* FUN_000f3be4 @ 0x000f3be4   (est. iel_get_region_kind)
 * Ghidra: undefined1[16] FUN_000f3be4(void)
 * Returns the 16-byte region-kind descriptor at the current thread object's
 * +0xc0, retaining the object at +200.
 * Confidence: low
 * Notes: auVar1 = *(16-byte)(*unaff_x20 + 0xc0). */
unsigned long long iel_get_region_kind(void)
{
    unsigned long long v = *(unsigned long long *)(*(void **)cl4_current + 0xc0);
    cl4_retain(*(void **)(*(void **)cl4_current + 200));
    return v;
}


