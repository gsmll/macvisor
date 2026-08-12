/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 21: 0x000f3c18-0x000f6530 — PMM-instance vtable thunks + frame-mapping helpers. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ *
 * Shared cL4 word/result types (see sk_internal.h).
 * ------------------------------------------------------------------ */
typedef uint64_t word_t;
typedef uint64_t cap_t;
typedef uint64_t vptr_t;
typedef uint64_t pptr_t;

/* 128-bit return pair (the binary packs 16-byte returns in x0/x1). */
typedef struct sk128 {
    uint64_t lo;
    uint64_t hi;
} sk128_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helper declarations (declared extern with a one-line
 * note; bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* Generic object acquire/release & error-report helpers (0x36xxxx region). */
extern void cL4_obj_unref(long obj);               /* FUN_0036b118 — release */
extern void cL4_ret_common(void);                  /* FUN_0036b21c — common thunk epilogue */
extern void cL4_lock_op(void *p);                  /* FUN_0036b8c0 — op with lock */
extern void cL4_lock_rel(void *p);                 /* FUN_0036b7f8 — op release */
extern void cL4_report_error(long code, void *str);/* FUN_000b42b8 — error/string report */
extern void cL4_panic_msg(long a, long b);         /* thunk_FUN_002acbb8 — panic/report msg */
extern long cL4_vtable_reg(long a, long b);        /* FUN_0036a9a0 — register into object */
extern long cL4_get_reg(void);                     /* FUN_0036a940 */
extern void cL4_put_reg(long a, long b, long c);   /* FUN_0036b6ac */
extern void cL4_finalize(long o);                  /* FUN_0036b588 */
extern void cL4_free_list(long o);                 /* FUN_0036b6f4 */
extern void cL4_dispatch2(long a, long b);         /* FUN_0036993c */

/* cL4 capability-object method helpers (0x0e-0x0f region, owned elsewhere). */
extern void cL4_op_a(long a, long b, long c, long d, char e, long f, long g, char h); /* FUN_000eecb4 */
extern void cL4_op_b(long a, long b);              /* FUN_000eed84 */
extern void cL4_op_c(long a, long b);              /* FUN_000efc74 */
extern void cL4_op_d(long a, long b, long c);      /* FUN_000f0000 */
extern void cL4_op_e(long a, long b, long c);      /* FUN_000f03f8 */
extern void cL4_op_f(long a, long b, long c, uint16_t d); /* FUN_000f06bc */
extern void cL4_op_g(long a, long b);              /* FUN_000f1ba8 */
extern void cL4_op_h(long a, long b);              /* FUN_000f1ff4 */
extern void cL4_op_i(long a, long b);              /* FUN_000f21e0 */
extern void cL4_op_j(long a, long b, long c, long d, long e, char f, char g, char h); /* FUN_000f2a30 */
extern void cL4_op_k(long a, long b, long c);      /* FUN_000f2ddc */
extern void cL4_op_l(long a, long b);              /* FUN_000f1ba8 */
extern void cL4_op_m(void);                        /* FUN_00084074 */
extern void cL4_op_n(void);                        /* FUN_0007bf80 */
extern void cL4_op_o(long o);                      /* FUN_000027e8 */
extern long cL4_init_type(long a, void *b);       /* FUN_00002534 */
extern void cL4_init2(void *a, long b, void *c);   /* FUN_0000276c */
extern void cL4_init3(void);                       /* FUN_00002804 */
extern long cL4_init4(void);                       /* FUN_00002688 */

/* Frame / vspace primitives (0x1-0x2 region). */
extern word_t cL4_frame_resolve_tagged(word_t a, word_t b, word_t c); /* FUN_0001da84 */
extern void cL4_copy_block(long a, void *b, long c); /* FUN_00117cc4 */
extern void cL4_async_setup(long a, void *b, long c, long d, long e, long f, long g, long h); /* FUN_00151a6c */
extern sk128_t cL4_async_state(void);              /* FUN_00151974 */
extern long cL4_tbl_init(long a, long b, long c, long d); /* FUN_001f0130 */
extern sk128_t cL4_tbl_query(long a, long b);     /* FUN_0006ae9c */
extern long cL4_tbl_resolve(long a, long b, long c, long d, long e); /* FUN_002a0cf8 */
extern sk128_t cL4_tbl_get(long a, long b, long c, long d); /* FUN_002a3e64 */
extern sk128_t cL4_tbl_enter(long a, long b, long c, long d, long e); /* FUN_002b439c */
extern long cL4_tbl_next(long a, long b, long c, long d, long e); /* FUN_002b3b50 */
extern sk128_t cL4_tbl_range(long a, long b, long c, long d, long e, long f); /* thunk_FUN_002b74c0 */
extern long cL4_range_check(long a, long b, long c, long d); /* FUN_002b15d0 */
extern word_t cL4_vector_add(uint8_t *vec);        /* FUN_003a261c */
extern sk128_t cL4_vector_pop(long a, long b);     /* FUN_0029d3d8 */
extern long cL4_vector_put(long a, long b, long c, long d); /* FUN_00467468 */
extern void cL4_vector_rel(long a, long b, long c); /* FUN_000b2260 */
extern void cL4_vector_del(long a, long b);        /* FUN_003a25d4 */
extern void cL4_vector_ret(long a, long b);        /* FUN_003a2610 */
extern void *cL4_grow(long a, long b, long c, void *v); /* FUN_00073690 */
extern long cL4_tbl_lookup(void *a);                       /* FUN_0024d9ac */
extern long cL4_find(long a, long b, long c, long d);      /* FUN_004917d8 */
extern long cL4_obj_ref(long a, long b);                   /* FUN_0036b270 — retain */
extern void cL4_mkrec(void *o, long a, long b, long c, long d, long e, long f); /* FUN_00467678 */
extern void cL4_describe(void *o, long a, long b);         /* FUN_00494240 */
extern long cL4_svc(void *a, long b, long c, long d, long e, long f); /* FUN_00471aec */
extern void cL4_ctxset(long *o, long a, long b, long c, long d, long e, long f, long g, long h); /* FUN_00467678 */
extern long cL4_reg_state(void);                   /* FUN_0039a128 */
extern sk128_t cL4_state_pair(long a, long b);     /* FUN_0007d054 */
extern sk128_t cL4_frame_classify(long a, long b, long c); /* FUN_0001d4f4 */
extern long cL4_enter_fault(void);                 /* FUN_0008f630 */
extern long cL4_fault_chk(long a, long b);         /* FUN_0008e140 */
extern long cL4_fault_get(void);                   /* FUN_0008e0d4 */
extern long cL4_fault_go(long a);                 /* FUN_000db7a8 */
extern void cL4_switch(long a, long b, long c);    /* FUN_002a4ab4 */
extern long cL4_reg2(long a, long b);              /* FUN_0006e7c0 */
extern long cL4_tbl_state(void);                   /* FUN_0039a128 */
extern void cL4_async_cb(long a, long b);          /* FUN_000f67b4 */
extern void cL4_free(void);                        /* FUN_0036b118 */

/* helpers used by pmm_frame_map_walk (0xf5080) — functions FUN_002b439c,
 * FUN_002b3b50, FUN_002a0cf8, FUN_0029d3d8, FUN_00467468, FUN_002b74c0,
 * FUN_003a261c (0xf-range vector/frame ops) */
extern sk128_t cL4_tbl_enter2(void);               /* FUN_002b439c — fetch current region */
extern long cL4_tbl_next2(void);                   /* FUN_002b3b50 — advance to next region */
extern long cL4_tbl_resolve2(long a, long b, long c, long d, long e); /* FUN_002a0cf8 */
extern unsigned cL4_lzcount(word_t v);             /* LZCOUNT intrinsic */

/* ------------------------------------------------------------------ *
 * Out-of-slice globals referenced by these bodies.
 * ------------------------------------------------------------------ */
extern word_t cL4_pmm_gbl;   /* _DAT_006ad9e0 — PMM global instance */
extern word_t cL4_gbl2;      /* _DAT_004baeb0 */
extern word_t cL4_gbl3;      /* uRam00000000004baeb8 */
extern word_t cL4_gbl4;      /* _DAT_00657778 */
extern word_t cL4_gbl5;      /* _DAT_006577e0 */
extern word_t cL4_gbl6;      /* _DAT_004c3958 */
extern word_t cL4_gbl7;      /* _DAT_004c3998 */
extern word_t cL4_gbl8;      /* _DAT_004c39a0 */
extern word_t cL4_gbl9;      /* _DAT_004c39a8 */
extern word_t cL4_gbl10;     /* _DAT_004c39b0 */
extern word_t cL4_gbl11;     /* _DAT_004c39b8 */
extern word_t cL4_gbl12;     /* _DAT_004c39f8 */
extern word_t cL4_gbl13;     /* _DAT_004c3a18 */
extern word_t cL4_gbl14;     /* _DAT_004c3a38 */
extern word_t cL4_gbl15;     /* _DAT_004c14b0 */
extern word_t cL4_gbl16;     /* _DAT_006577e0 */

/* string literals (in-image rodata, kept by Ghidra address). */
extern const char cL4_s_fatal[];          /* s_Fatal_error_005accd0 */
extern const char cL4_s_cowframes[];      /* s_cowFrames_region_machoFramesToCo_005c50d0 */
extern const char cL4_s_execctx[];        /* s_Failed_setting_execution_context_005c5700 */
extern const char cL4_s_pmmcreate[];      /* s_PMMInstance_could_not_create_SC_o_005c55b0 */

/* ------------------------------------------------------------------ *
 * Vtable-dispatch thunks.
 * Every `this`-based vtable thunk below is a C++ virtual-method forwarder:
 * it loads the object's vtable pointer from *this and calls the slot at the
 * given byte offset. They are named pmm_vm_* (Physical Memory Manager
 * virtual method). Confidence low — the true semantic name is unknown.
 * ------------------------------------------------------------------ */

/* Forward declarations (functions referenced before their definitions). */
sk128_t pmm_pack_err_msg(long param_1);
void pmm_async_cb_fwd(void);
uint64_t pmm_fptr_22_call(void *param_1);
uint64_t *pmm_release_word(uint64_t *param_1);
uint64_t pmm_fptr_2a_call(void *param_1, void *param_2);
uint64_t *pmm_copy_word(uint64_t *param_1, uint64_t *param_2);
void pmm_const_2(void);
void pmm_const_3(void);
void pmm_noop11(void);
void pmm_noop12(void);
uint8_t *pmm_split_ranges(uint64_t param_1, uint64_t param_2, long param_3, uint8_t param_4,
                          word_t param_5, word_t param_6, uint64_t param_7, uint64_t param_8);
void cL4_noop11_f(void);
void cL4_noop12_f(void);

/* FUN_000f3c18 @ 0x000f3c18   (est. pmm_vm_1b8)
 * Ghidra: void FUN_000f3c18(void)
 * Forwards the virtual method at vtable offset 0x1b8 on the object in x20.
 * Confidence: low
 * Notes: pure vtable thunk; this = x20, vtable = *x20, slot +0x1b8. */
void pmm_vm_1b8(void) {
    /* this = x20; call (*(vtable+0x1b8))() */
}

/* FUN_000f3c74 @ 0x000f3c74   (est. pmm_vm_270)
 * Ghidra: void FUN_000f3c74(undefined8 param_1)
 * Calls the vtable slot at +0x270 with an 80-byte stack buffer, then copies
 * 0x50 bytes of that result into param_1 (an out-buffer).
 * Confidence: low
 * Notes: this = x20; buffer auStack_70[80]; copy via FUN_00117cc4. */
void pmm_vm_270(uint64_t param_1) {
    uint8_t buf[80];
    /* (*(this->vtable+0x270))(buf); */
    cL4_copy_block(param_1, buf, 0x50);
}

/* FUN_000f3cd8 @ 0x000f3cd8   (est. pmm_vm_278)
 * Ghidra: void FUN_000f3cd8(undefined8 *param_1)
 * Calls the vtable slot at +0x278 with a stack buffer, then writes the
 * resulting 16-byte object (6 qwords + 7 trailing bytes) into param_1.
 * Confidence: low
 * Notes: this = x20; result laid out into param_1[0..5] + trailing bytes. */
void pmm_vm_278(uint64_t *param_1) {
    uint64_t r0, r1, r2, r3, r4, r5;
    uint8_t  b6, b7, b8, b9;
    /* (*(this->vtable+0x278))(&local_60);  // fills local_60..local_40, uStack_38.. */
    param_1[1] = r1;
    param_1[0] = r0;
    param_1[3] = r3;
    param_1[2] = r2;
    /* param_1[5] = CONCAT71(uStack_37,uStack_38); */
    param_1[4] = r4;
    /* *(param_1+0x31) = uStack_2f; */
    /* *(param_1+0x29) = CONCAT17(uStack_30,uStack_37); */
    (void)b6; (void)b7; (void)b8; (void)b9;
}

/* FUN_000f3d68 @ 0x000f3d68   (est. pmm_vm_288)
 * Forwards the virtual method at vtable offset 0x288 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_288(void) {
    /* (*(this->vtable+0x288))() */
}

/* FUN_000f3dac @ 0x000f3dac   (est. pmm_vm_260)
 * Forwards the virtual method at vtable offset 0x260 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_260(void) {
    /* (*(this->vtable+0x260))() */
}

/* FUN_000f3df0 @ 0x000f3df0   (est. pmm_vm_2a0)
 * Forwards the virtual method at vtable offset 0x2a0 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_2a0(void) {
    /* (*(this->vtable+0x2a0))() */
}

/* FUN_000f3e34 @ 0x000f3e34   (est. pmm_vm_2a8)
 * Forwards the virtual method at vtable offset 0x2a8 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_2a8(void) {
    /* (*(this->vtable+0x2a8))() */
}

/* FUN_000f3e78 @ 0x000f3e78   (est. pmm_vm_e8)
 * Forwards the virtual method at vtable offset 0xe8 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_e8(void) {
    /* (*(this->vtable+0xe8))() */
}

/* FUN_000f3eb4 @ 0x000f3eb4   (est. pmm_vm_300)
 * Forwards the virtual method at vtable offset 0x300 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_300(void) {
    /* (*(this->vtable+0x300))() */
}

/* FUN_000f3ef8 @ 0x000f3ef8   (est. pmm_vm_308)
 * Forwards the virtual method at vtable offset 0x308 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_308(void) {
    /* (*(this->vtable+0x308))() */
}

/* FUN_000f3f3c @ 0x000f3f3c   (est. pmm_vm_310)
 * Forwards the virtual method at vtable offset 0x310 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_310(void) {
    /* (*(this->vtable+0x310))() */
}

/* FUN_000f3f80 @ 0x000f3f80   (est. pmm_vm_318)
 * Forwards the virtual method at vtable offset 0x318 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_318(void) {
    /* (*(this->vtable+0x318))() */
}

/* FUN_000f3fc4 @ 0x000f3fc4   (est. pmm_vm_328)
 * Forwards the virtual method at vtable offset 0x328 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_328(void) {
    /* (*(this->vtable+0x328))() */
}

/* FUN_000f4008 @ 0x000f4008   (est. pmm_vm_340)
 * Forwards the virtual method at vtable offset 0x340 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_340(void) {
    /* (*(this->vtable+0x340))() */
}

/* FUN_000f404c @ 0x000f404c   (est. pmm_vm_348)
 * Forwards the virtual method at vtable offset 0x348 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_348(void) {
    /* (*(this->vtable+0x348))() */
}

/* FUN_000f4090 @ 0x000f4090   (est. pmm_vm_350)
 * Forwards the virtual method at vtable offset 0x350 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_350(void) {
    /* (*(this->vtable+0x350))() */
}

/* FUN_000f40d4 @ 0x000f40d4   (est. pmm_vm_330)
 * Forwards the virtual method at vtable offset 0x330 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_330(void) {
    /* (*(this->vtable+0x330))() */
}

/* FUN_000f4120 @ 0x000f4120   (est. pmm_vm_338)
 * Ghidra: uint FUN_000f4120(void)
 * Calls the vtable slot at +0x338 and returns the low bit of its result
 * (a boolean predicate).
 * Confidence: low  Notes: pure vtable thunk, result & 1. */
uint32_t pmm_vm_338(void) {
    uint32_t r = 0; /* (*(this->vtable+0x338))(); */
    return r & 1;
}

/* FUN_000f4168 @ 0x000f4168   (est. pmm_vm_358)
 * Forwards the virtual method at vtable offset 0x358 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_358(void) {
    /* (*(this->vtable+0x358))() */
}

/* FUN_000f41ac @ 0x000f41ac   (est. pmm_vm_360)
 * Forwards the virtual method at vtable offset 0x360 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_360(void) {
    /* (*(this->vtable+0x360))() */
}

/* FUN_000f41f0 @ 0x000f41f0   (est. pmm_vm_368)
 * Forwards the virtual method at vtable offset 0x368 on the object in x20.
 * Confidence: low  Notes: pure vtable thunk. */
void pmm_vm_368(void) {
    /* (*(this->vtable+0x368))() */
}

/* FUN_000f4234 @ 0x000f4234   (est. pmm_const_init)
 * Ghidra: void FUN_000f4234(void)
 * Stores a fixed 8-byte constant into the global word at 0x652118
 * (uRam0000000000652118 = 0xaa1703e9394016e8). A data/init stub.
 * Confidence: low
 * Notes: decompiler removed an unreachable block (ram,0xf4248). */
void pmm_const_init(void) {
    /* uRam0000000000652118 = 0xaa1703e9394016e8; */
}

/* FUN_000f42b8 @ 0x000f42b8   (est. pmm_ctor_a)
 * Ghidra: void FUN_000f42b8(void)
 * Runs an object construction sequence: acquires the sub-object at this+0x10,
 * runs a helper, then returns via the common thunk epilogue.
 * Confidence: low  Notes: this = x20. */
void pmm_ctor_a(void) {
    cL4_lock_op((void *)(uintptr_t)((word_t)0 + 0x10));
    cL4_op_m();
    cL4_ret_common();
}

/* FUN_000f42bc @ 0x000f42bc   (est. pmm_ctor_b)
 * Identical body to pmm_ctor_a (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_ctor_b(void) {
    cL4_lock_op((void *)(uintptr_t)((word_t)0 + 0x10));
    cL4_op_m();
    cL4_ret_common();
}

/* FUN_000f430c @ 0x000f430c   (est. pmm_op_a)
 * Ghidra: void FUN_000f430c(void)
 * Forwards eight argument words/bytes read from this+0x10..0x48 into the
 * shared object operation helper FUN_000eecb4.
 * Confidence: low  Notes: this = x20; fields at +0x10..+0x48. */
void pmm_op_a(void) {
    cL4_op_a(/*+0x10*/0, /*+0x18*/0, /*+0x20*/0, /*+0x28*/0, /*+0x30*/0,
             /*+0x38*/0, /*+0x40*/0, /*+0x48*/0);
}

/* FUN_000f4310 @ 0x000f4310   (est. pmm_op_a2)
 * Identical body to pmm_op_a (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_a2(void) {
    cL4_op_a(0, 0, 0, 0, 0, 0, 0, 0);
}

/* FUN_000f4338 @ 0x000f4338   (est. pmm_op_b)
 * Ghidra: void FUN_000f4338(void)
 * Forwards two argument words read from this+0x18/+0x20 into FUN_000eed84.
 * Confidence: low  Notes: this = x20. */
void pmm_op_b(void) {
    cL4_op_b(/*+0x18*/0, /*+0x20*/0);
}

/* FUN_000f433c @ 0x000f433c   (est. pmm_op_b2)
 * Identical body to pmm_op_b (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_b2(void) {
    cL4_op_b(0, 0);
}

/* FUN_000f4354 @ 0x000f4354   (est. pmm_op_c)
 * Ghidra: void FUN_000f4354(void)
 * Forwards two argument words read from this+0x10/+0x18 into FUN_000efc74.
 * Confidence: low  Notes: this = x20. */
void pmm_op_c(void) {
    cL4_op_c(/*+0x10*/0, /*+0x18*/0);
}

/* FUN_000f4358 @ 0x000f4358   (est. pmm_op_c2)
 * Identical body to pmm_op_c (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_c2(void) {
    cL4_op_c(0, 0);
}

/* FUN_000f4370 @ 0x000f4370   (est. pmm_op_d)
 * Ghidra: void FUN_000f4370(void)
 * Forwards three argument words read from this+0x10/+0x18/+0x20 into
 * FUN_000f0000.
 * Confidence: low  Notes: this = x20. */
void pmm_op_d(void) {
    cL4_op_d(/*+0x10*/0, /*+0x18*/0, /*+0x20*/0);
}

/* FUN_000f4374 @ 0x000f4374   (est. pmm_op_d2)
 * Identical body to pmm_op_d (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_d2(void) {
    cL4_op_d(0, 0, 0);
}

/* FUN_000f4390 @ 0x000f4390   (est. pmm_op_e)
 * Ghidra: void FUN_000f4390(void)
 * Forwards three argument words read from this+0x10/+0x18/+0x20 into
 * FUN_000f03f8.
 * Confidence: low  Notes: this = x20. */
void pmm_op_e(void) {
    cL4_op_e(/*+0x10*/0, /*+0x18*/0, /*+0x20*/0);
}

/* FUN_000f4394 @ 0x000f4394   (est. pmm_op_e2)
 * Identical body to pmm_op_e (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_e2(void) {
    cL4_op_e(0, 0, 0);
}

/* FUN_000f43b0 @ 0x000f43b0   (est. pmm_op_f)
 * Ghidra: void FUN_000f43b0(void)
 * Forwards three argument words + a 16-bit value read from this+0x10..+0x28
 * into FUN_000f06bc.
 * Confidence: low  Notes: this = x20. */
void pmm_op_f(void) {
    cL4_op_f(/*+0x10*/0, /*+0x18*/0, /*+0x20*/0, /*+0x28 as u16*/0);
}

/* FUN_000f43b4 @ 0x000f43b4   (est. pmm_op_f2)
 * Identical body to pmm_op_f (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_f2(void) {
    cL4_op_f(0, 0, 0, 0);
}

/* FUN_000f43d4 @ 0x000f43d4   (est. pmm_pack_word)
 * Ghidra: undefined1 [16] FUN_000f43d4(ulong param_1)
 * Packs a 128-bit descriptor: lo = ((param_1 & 0xffffffff) << 16) | 1,
 * hi = 0. Likely builds a small tagged value/token.
 * Confidence: low
 * Notes: returns a 16-byte value in x0/x1. */
sk128_t pmm_pack_word(word_t param_1) {
    sk128_t r;
    r.lo = ((param_1 & 0xffffffffu) << 16) | 1;
    r.hi = 0;
    return r;
}

/* FUN_000f43e8 @ 0x000f43e8   (est. pmm_op_g)
 * Ghidra: void FUN_000f43e8(void)
 * Forwards two argument words read from this+0x10/+0x18 into FUN_000f1ba8.
 * Confidence: low  Notes: this = x20. */
void pmm_op_g(void) {
    cL4_op_g(/*+0x10*/0, /*+0x18*/0);
}

/* FUN_000f43ec @ 0x000f43ec   (est. pmm_op_g2)
 * Identical body to pmm_op_g (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_g2(void) {
    cL4_op_g(0, 0);
}

/* FUN_000f4404 @ 0x000f4404   (est. pmm_parse_hex)
 * Ghidra: uint FUN_000f4404(long,long,ulong,ulong,ulong,ulong)
 * Parses an unsigned (optionally signed) hexadecimal string at the computed
 * byte offset, honoring bounds, and returns the parsed value (low byte),
 * with 0x100 set in the high byte on any overflow/malformed input. Uses
 * SoftwareBreakpoint(1,...) panics on out-of-range accesses.
 * Confidence: medium
 * Notes: callers pass (dst, len, start_vaddr, end_vaddr, ...); uses
 *   FUN_0001da84, FUN_002b15d0 for validation; breakpoints at 0xf47a4.. */
uint32_t pmm_parse_hex(long param_1, long param_2, word_t param_3, word_t param_4,
                       word_t param_5, word_t param_6) {
    uint32_t uVar7;
    uint32_t uVar8;
    uint8_t  bVar2;
    word_t   uVar11;
    word_t   uVar5;
    word_t   uVar1;
    long     lVar6;
    long     lVar10;
    word_t   uVar12;
    bool     bVar4;
    uint8_t *pbVar9;

    uVar7 = (uint32_t)((param_5 >> 0x3b) & 1);
    if ((param_6 & 0x1000000000000000) == 0) {
        uVar7 = 1;
    }
    uVar11 = 4ULL << uVar7;
    uVar5 = param_3;
    if ((param_3 & 0xc) == uVar11) {
        uVar5 = cL4_frame_resolve_tagged(param_3, param_5, param_6);
    }
    uVar12 = (param_6 >> 0x38) & 0xf;
    if (((param_6 >> 0x3c) & 1) == 0) {
        uVar5 = uVar5 >> 0x10;
    } else {
        uVar1 = param_5 & 0xffffffffffffULL;
        if ((param_6 & 0x2000000000000000) != 0) {
            uVar1 = uVar12;
        }
        if (uVar1 < (uVar5 >> 0x10)) {
            /* breakpoint 0xf47a4: does not return */
        }
        uVar5 = cL4_range_check(0xf, uVar5, param_5, param_6);
    }
    if ((param_3 & 0xc) == uVar11) {
        param_3 = cL4_frame_resolve_tagged(param_3, param_5, param_6);
    }
    if ((param_4 & 0xc) == uVar11) {
        param_4 = cL4_frame_resolve_tagged(param_4, param_5, param_6);
        if (((param_6 >> 0x3c) & 1) == 0) {
            goto resolve_lo;
        }
    resolve_hi:
        uVar11 = param_5 & 0xffffffffffffULL;
        if ((param_6 & 0x2000000000000000) != 0) {
            uVar11 = uVar12;
        }
        if (uVar11 < (param_3 >> 0x10)) { /* breakpoint 0xf4790 */ }
        if (uVar11 < (param_4 >> 0x10)) { /* breakpoint 0xf4794 */ }
        lVar6 = cL4_range_check(param_3, param_4, param_5, param_6);
    } else {
        if (((param_6 >> 0x3c) & 1) != 0) goto resolve_hi;
    resolve_lo:
        lVar6 = (param_4 >> 0x10) - (param_3 >> 0x10);
    }
    uVar11 = uVar5 + lVar6;
    if ((word_t)(uVar5 + lVar6) < uVar5) { /* breakpoint 0xf4778: carry */ }
    if ((int64_t)uVar11 < (int64_t)uVar5) { /* breakpoint 0xf477c */ }
    if ((int64_t)uVar5 < 0) { /* breakpoint 0xf4780 */ }
    if (param_2 < (int64_t)uVar11) { /* breakpoint 0xf4784 */ }
    pbVar9 = NULL;
    if (param_1 != 0) {
        pbVar9 = (uint8_t *)(uVar5 + param_1);
    }
    lVar10 = uVar11 - uVar5;
    if (lVar10 < 0) { /* breakpoint 0xf4788 */ }
    if ((lVar10 != 0) && (pbVar9 == NULL)) { /* breakpoint 0xf4798 */ }
    if (uVar11 == uVar5) { /* breakpoint 0xf478c */ }

    uVar7 = 0;
    uVar8 = 0;
    if (pbVar9 == NULL) goto final;
    if (*pbVar9 == '+') {
        lVar10 -= 1;
        if ((lVar10 != 0) && (pbVar9 == NULL)) { /* breakpoint 0xf47a0 */ }
        bVar4 = (lVar10 == 0);
        if ((lVar10 == 0) || (pbVar9 == NULL)) {
            uVar7 = 0;
            uVar8 = bVar4 ? 0x100 : 0;
            goto final;
        }
        uVar7 = 0;
        do {
            pbVar9++;
            bVar2 = *pbVar9;
            uVar8 = bVar2 - 0x30;
            if (uVar8 > 9) {
                uVar8 = (uint32_t)bVar2;
                if ((bVar2 - 0x41) < 6) {
                    uVar8 -= 0x37;
                } else {
                    if (uVar8 - 0x61 > 5) goto bad;
                    uVar8 -= 0x57;
                }
            }
            if ((uVar7 & 0xff) > 0xf) goto bad;
            uVar7 = uVar8 + uVar7 * 0x10;
            lVar10--;
        } while (lVar10 != 0);
    } else if (*pbVar9 == '-') {
        lVar10 -= 1;
        if ((lVar10 != 0) && (pbVar9 == NULL)) { /* breakpoint 0xf479c */ }
        bVar4 = (lVar10 == 0);
        if ((lVar10 == 0) || (pbVar9 == NULL)) {
            uVar7 = 0;
            uVar8 = bVar4 ? 0x100 : 0;
            goto final;
        }
        uVar7 = 0;
        do {
            pbVar9++;
            bVar2 = *pbVar9;
            uVar8 = bVar2 - 0x30;
            if (uVar8 > 9) {
                uVar8 = (uint32_t)bVar2;
                if ((bVar2 - 0x41) < 6) {
                    uVar8 -= 0x37;
                } else {
                    if (uVar8 - 0x61 > 5) goto bad;
                    uVar8 -= 0x57;
                }
            }
            if (((uVar7 & 0xff) > 0xf) ||
                (uVar7 = (uVar7 & 0xf) * 0x10 - (uVar8 & 0xff), (uVar7 & 0xffffff00) != 0))
                goto bad;
            lVar10--;
        } while (lVar10 != 0);
    } else {
        uVar7 = 0;
        uVar8 = 0;
        if (pbVar9 == NULL) goto final;
        do {
            bVar2 = *pbVar9;
            uVar8 = bVar2 - 0x30;
            if (uVar8 > 9) {
                uVar8 = (uint32_t)bVar2;
                if ((bVar2 - 0x41) < 6) {
                    uVar8 -= 0x37;
                } else {
                    if (uVar8 - 0x61 > 5) goto bad;
                    uVar8 -= 0x57;
                }
            }
            if ((uVar7 & 0xff) > 0xf) goto bad;
            uVar7 = uVar8 + uVar7 * 0x10;
            pbVar9++;
            lVar6--;
        } while (lVar6 != 0);
    }
    uVar8 = 0;
final:
    return uVar8 | (uVar7 & 0xff);
bad:
    uVar7 = 0;
    uVar8 = 0x100;
    goto final;
}

/* FUN_000f47a4 @ 0x000f47a4   (est. pmm_op_h)
 * Ghidra: void FUN_000f47a4(void)
 * Forwards two argument words read from this+0x10/+0x18 into FUN_000f1ff4.
 * Confidence: low  Notes: this = x20. */
void pmm_op_h(void) {
    cL4_op_h(/*+0x10*/0, /*+0x18*/0);
}

/* FUN_000f47a8 @ 0x000f47a8   (est. pmm_op_h2)
 * Identical body to pmm_op_h (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_h2(void) {
    cL4_op_h(0, 0);
}

/* FUN_000f47c0 @ 0x000f47c0   (est. pmm_op_i)
 * Ghidra: void FUN_000f47c0(void)
 * Forwards two argument words read from this+0x10/+0x18 into FUN_000f21e0.
 * Confidence: low  Notes: this = x20. */
void pmm_op_i(void) {
    cL4_op_i(/*+0x10*/0, /*+0x18*/0);
}

/* FUN_000f47c4 @ 0x000f47c4   (est. pmm_op_i2)
 * Identical body to pmm_op_i (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_i2(void) {
    cL4_op_i(0, 0);
}

/* FUN_000f47dc @ 0x000f47dc   (est. pmm_op_j)
 * Ghidra: void FUN_000f47dc(void)
 * Forwards eight argument words/bytes read from this+0x10..0x3a into
 * FUN_000f2a30.
 * Confidence: low  Notes: this = x20. */
void pmm_op_j(void) {
    cL4_op_j(/*+0x10*/0, /*+0x18*/0, /*+0x20*/0, /*+0x28*/0, /*+0x30*/0,
             /*+0x38*/0, /*+0x39*/0, /*+0x3a*/0);
}

/* FUN_000f47e0 @ 0x000f47e0   (est. pmm_op_j2)
 * Identical body to pmm_op_j (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_op_j2(void) {
    cL4_op_j(0, 0, 0, 0, 0, 0, 0, 0);
}

/* FUN_000f480c @ 0x000f480c   (est. pmm_align_up)
 * Ghidra: ulong FUN_000f480c(long param_1)
 * Rounds the given address up to a 16 KiB (0x4000) boundary.
 * Confidence: high  Notes: (addr + 0x3fff) & ~0x3fff. */
word_t pmm_align_up(word_t param_1) {
    return (param_1 + 0x3fffU) & 0xffffffffffffc000ULL;
}

/* FUN_000f481c @ 0x000f481c   (est. pmm_op_k)
 * Ghidra: void FUN_000f481c(void)
 * Calls the shared no-argument object operation FUN_000f2ddc.
 * Confidence: low  Notes: no this-derived args. */
void pmm_op_k(void) {
    cL4_op_l(0, 0);
}

/* FUN_000f4820 @ 0x000f4820   (est. pmm_op_k2)
 * Identical body to pmm_op_k (pair/const-overload thunk).
 * Confidence: low  Notes: no this-derived args. */
void pmm_op_k2(void) {
    cL4_op_l(0, 0);
}

/* FUN_000f4838 @ 0x000f4838   (est. pmm_indirect_call)
 * Ghidra: void FUN_000f4838(undefined8,long,undefined8,undefined8)
 * Treats param_2 as a call-target descriptor and invokes the function at
 * param_2+8 with (param_1, param_3, param_4). The decompiler could not
 * recover a jump table at 0xf4848.
 * Confidence: low
 * Notes: indirect jump treated as call; jumptable warning. */
void pmm_indirect_call(uint64_t param_1, long param_2, uint64_t param_3, uint64_t param_4) {
    /* (**(code **)(param_2 + 8))(param_1, param_3, param_4); */
}

/* FUN_000f4888 @ 0x000f4888   (est. pmm_vm_1b8_out)
 * Ghidra: void FUN_000f4888(void)
 * Runs the cL4 op-n helper, calls the vtable slot at +0x1b8 (via x16
 * carrier), and stores the result into the object pointed to by x19.
 * Confidence: low  Notes: this = x20; result stored to *unaff_x19. */
void pmm_vm_1b8_out(void) {
    word_t uVar1;
    cL4_op_n();
    uVar1 = 0; /* (*(this->vtable+0x1b8))(); */
    /* *unaff_x19 = uVar1; */
    (void)uVar1;
}

/* FUN_000f48cc @ 0x000f48cc   (est. pmm_vm_230_out)
 * Ghidra: void FUN_000f48cc(void)
 * Runs cL4 op-n, calls the vtable slot at +0x230 (via x16), stores result to
 * *x19.
 * Confidence: low  Notes: this = x20. */
void pmm_vm_230_out(void) {
    word_t uVar1;
    cL4_op_n();
    uVar1 = 0; /* (*(this->vtable+0x230))(); */
    /* *unaff_x19 = uVar1; */
    (void)uVar1;
}

/* FUN_000f4910 @ 0x000f4910   (est. pmm_vm_248_out)
 * Ghidra: void FUN_000f4910(void)
 * Runs cL4 op-n, calls the vtable slot at +0x248 (via x16), stores result to
 * *x19.
 * Confidence: low  Notes: this = x20. */
void pmm_vm_248_out(void) {
    word_t uVar1;
    cL4_op_n();
    uVar1 = 0; /* (*(this->vtable+0x248))(); */
    /* *unaff_x19 = uVar1; */
    (void)uVar1;
}

/* FUN_000f4950 @ 0x000f4950   (est. pmm_vm_250)
 * Ghidra: void FUN_000f4950(undefined8 *param_1)
 * Runs cL4 op-o on the first word of param_1, then calls the vtable slot at
 * +0x250 (via x16).
 * Confidence: low  Notes: this = x20. */
void pmm_vm_250(uint64_t *param_1) {
    cL4_op_o(*param_1);
    /* (*(this->vtable+0x250))(); */
}

/* FUN_000f4994 @ 0x000f4994   (est. pmm_type_info)
 * Ghidra: undefined1 [16] FUN_000f4994(void)
 * Returns a 128-bit value whose low word is the image address 0x652148
 * (a vtable/type-info pointer), hi = 0.
 * Confidence: low  Notes: returns ZEXT816(0x652148). */
sk128_t pmm_type_info(void) {
    sk128_t r;
    r.lo = 0x652148;
    r.hi = 0;
    return r;
}

/* FUN_000f4a58 @ 0x000f4a58   (est. pmm_vm_10_rel)
 * Ghidra: void FUN_000f4a58(void)
 * Releases the sub-object at this+0x10 and returns via the common epilogue.
 * Confidence: low  Notes: this = x20. */
void pmm_vm_10_rel(void) {
    cL4_obj_unref(/*+0x10*/0);
    cL4_ret_common();
}

/* FUN_000f4a5c @ 0x000f4a5c   (est. pmm_vm_10_rel2)
 * Identical body to pmm_vm_10_rel (pair/const-overload thunk).
 * Confidence: low  Notes: this = x20. */
void pmm_vm_10_rel2(void) {
    cL4_obj_unref(0);
    cL4_ret_common();
}

/* FUN_000f4a9c @ 0x000f4a9c   (est. pmm_noop_0)
 * Ghidra: void FUN_000f4a9c(void)
 * Empty default virtual-method body (no-op).
 * Confidence: high  Notes: returns immediately. */
void pmm_noop_0(void) {
}

/* FUN_000f4abc @ 0x000f4abc   (est. pmm_fatal_string)
 * Ghidra: char * FUN_000f4abc(void)
 * Returns the "Fatal error" string literal (s_Fatal_error_005accd0).
 * Confidence: high  Notes: string match. */
const char *pmm_fatal_string(void) {
    return cL4_s_fatal;
}

/* FUN_000f4ad0 @ 0x000f4ad0   (est. pmm_noop_1) — empty body. */
void pmm_noop_1(void) {}

/* FUN_000f4ae8 @ 0x000f4ae8   (est. pmm_noop_2) — empty body. */
void pmm_noop_2(void) {}

/* FUN_000f4b00 @ 0x000f4b00   (est. pmm_noop_3) — empty body. */
void pmm_noop_3(void) {}

/* FUN_000f4b14 @ 0x000f4b14   (est. pmm_noop_4) — empty body. */
void pmm_noop_4(void) {}

/* FUN_000f4b2c @ 0x000f4b2c   (est. pmm_noop_5) — empty body. */
void pmm_noop_5(void) {}

/* FUN_000f4b40 @ 0x000f4b40   (est. pmm_noop_6) — empty body. */
void pmm_noop_6(void) {}

/* FUN_000f4b58 @ 0x000f4b58   (est. pmm_noop_7) — empty body. */
void pmm_noop_7(void) {}

/* FUN_000f4b70 @ 0x000f4b70   (est. pmm_noop_8) — empty body. */
void pmm_noop_8(void) {}

/* FUN_000f4b7c @ 0x000f4b7c   (est. pmm_range_empty)
 * Ghidra: void FUN_000f4b7c(void)
 * Builds a 128-bit "empty range" value {lo=0, hi=0xe000000000000000} and
 * returns it in x0/x1 (stack locals at x29-0x80/-0x78).
 * Confidence: low  Notes: writes two stack words then returns. */
sk128_t pmm_range_empty(void) {
    sk128_t r;
    r.lo = 0;
    r.hi = 0xe000000000000000ULL;
    return r;
}

/* FUN_000f4b8c @ 0x000f4b8c   (est. pmm_noop_9) — empty body. */
void pmm_noop_9(void) {}

/* FUN_000f4ba0 @ 0x000f4ba0   (est. pmm_range_copy_panic)
 * Ghidra: void FUN_000f4ba0(void)
 * Copies two stack range words unchanged, then raises a fixed panic message
 * pair via thunk_FUN_002acbb8(0xd000000000000013, 0x80000000005c4f90).
 * Confidence: low  Notes: uses stack locals at x29-0x80/-0x78. */
void pmm_range_copy_panic(void) {
    /* word0 = *(x29-0x80); word1 = *(x29-0x78); */
    cL4_panic_msg(0xd000000000000013ULL, 0x80000000005c4f90ULL);
}

/* FUN_000f4bcc @ 0x000f4bcc   (est. pmm_lock_rel)
 * Ghidra: void FUN_000f4bcc(long param_1)
 * Calls the lock-release helper on the sub-object at param_1+0x10.
 * Confidence: low  Notes: FUN_0036b7f8(param_1 + 0x10). */
void pmm_lock_rel(long param_1) {
    cL4_lock_rel((void *)(param_1 + 0x10));
}

/* FUN_000f4bdc @ 0x000f4bdc   (est. pmm_noop_a) — empty body. */
void pmm_noop_a(void) {}

/* FUN_000f4be8 @ 0x000f4be8   (est. pmm_noop_b) — empty body. */
void pmm_noop_b(void) {}

/* FUN_000f4bf4 @ 0x000f4bf4   (est. pmm_init_1)
 * Ghidra: void FUN_000f4bf4(void)
 * Runs the cL4 type-initializer with (type=0x6524b8, &DAT_004c3958).
 * Confidence: low  Notes: FUN_00002534. */
void pmm_init_1(void) {
    cL4_init_type(0x6524b8, &cL4_gbl6);
}

/* FUN_000f4c08 @ 0x000f4c08   (est. pmm_noop_c) — empty body. */
void pmm_noop_c(void) {}

/* FUN_000f4c14 @ 0x000f4c14   (est. pmm_enum_3)
 * Ghidra: undefined8 FUN_000f4c14(void)
 * Returns the constant 3 (an enum/category value).
 * Confidence: high  Notes: returns 3. */
word_t pmm_enum_3(void) {
    return 3;
}

/* FUN_000f4c20 @ 0x000f4c20   (est. pmm_ptr_677880)
 * Ghidra: undefined8 FUN_000f4c20(void)
 * Returns the image address 0x677880 (a vtable/type pointer).
 * Confidence: low  Notes: returns 0x677880. */
word_t pmm_ptr_677880(void) {
    return 0x677880;
}

/* FUN_000f4c30 @ 0x000f4c30   (est. pmm_noop_d) — empty body. */
void pmm_noop_d(void) {}

/* FUN_000f4c40 @ 0x000f4c40   (est. pmm_obj_release)
 * Ghidra: void FUN_000f4c40(void)
 * Calls the object-release helper (FUN_0036b118) with no argument.
 * Confidence: low  Notes: FUN_0036b118(). */
void pmm_obj_release(void) {
    cL4_free();
}

/* FUN_000f4c4c @ 0x000f4c4c   (est. pmm_init_2)
 * Ghidra: void FUN_000f4c4c(void)
 * Runs the cL4 init-2 helper with (stack, 0x64f960, &DAT_004c14b0).
 * Confidence: low  Notes: FUN_0000276c. */
void pmm_init_2(void) {
    uint64_t stackval = 0;
    cL4_init2(&stackval, 0x64f960, &cL4_gbl15);
}

/* FUN_000f4c64 @ 0x000f4c64   (est. pmm_panic_empty)
 * Ghidra: void FUN_000f4c64(void)
 * Raises a default panic/report message (no args).
 * Confidence: low  Notes: thunk_FUN_002acbb8(). */
void pmm_panic_empty(void) {
    cL4_panic_msg(0, 0);
}

/* FUN_000f4c70 @ 0x000f4c70   (est. pmm_cowframes_desc)
 * Ghidra: undefined1 [16] FUN_000f4c70(void)
 * Returns a 128-bit descriptor {lo = "cowFrames region machoFramesToCo..."
 * string pointer, hi = 0x24}.
 * Confidence: high  Notes: string match; returns {str, 0x24}. */
sk128_t pmm_cowframes_desc(void) {
    sk128_t r;
    r.hi = 0x24;
    r.lo = (uint64_t)(uintptr_t)cL4_s_cowframes;
    return r;
}

/* FUN_000f4c84 @ 0x000f4c84   (est. pmm_noop_e) — empty body. */
void pmm_noop_e(void) {}

/* FUN_000f4c90 @ 0x000f4c90   (est. pmm_noop_f) — empty body. */
void pmm_noop_f(void) {}

/* FUN_000f4c9c @ 0x000f4c9c   (est. pmm_stack_ptr)
 * Ghidra: undefined1 * FUN_000f4c9c(void)
 * Returns a pointer into the caller's stack frame (0x68 bytes past the frame
 * pointer). This is a decompiler artifact of an address-taking local.
 * Confidence: low  Notes: returns &stack0x00000068. */
uint8_t *pmm_stack_ptr(void) {
    return NULL; /* &stack0x00000068 — decompiler artifact */
}

/* FUN_000f4cb0 @ 0x000f4cb0   (est. pmm_stack_byte)
 * Ghidra: undefined1 FUN_000f4cb0(void)
 * Returns the byte at the caller's frame pointer minus 0x21 (reads a local
 * byte from the stack).
 * Confidence: low  Notes: returns *(x29 - 0x21). */
uint8_t pmm_stack_byte(void) {
    return 0; /* *(uint8_t *)(x29 - 0x21) */
}

/* FUN_000f4cbc @ 0x000f4cbc   (est. pmm_noop_10) — empty body. */
void pmm_noop_10(void) {}

/* FUN_000f4cc8 @ 0x000f4cc8   (est. pmm_page_panic)
 * Ghidra: void FUN_000f4cc8(void)
 * Raises a fixed panic/report message pair: (0x736567617020 " page",
 * 0xe600000000000000).
 * Confidence: low  Notes: thunk_FUN_002acbb8(0x736567617020, 0xe6...). */
void pmm_page_panic(void) {
    cL4_panic_msg(0x736567617020ULL, 0xe600000000000000ULL);
}

/* FUN_000f4cdc @ 0x000f4cdc   (est. pmm_reg2)
 * Ghidra: void FUN_000f4cdc(void)
 * Calls FUN_0006e7c0 with (object from stack frame +0x58) and a stack
 * buffer.
 * Confidence: low  Notes: reads *(stack+0x48)+0x10... err, +0x58 target. */
void pmm_reg2(void) {
    long in_stack_0x48 = 0;
    cL4_reg2(*(long *)(in_stack_0x48 + 0x10) + 0x58, 0);
}

/* FUN_000f4cf0 @ 0x000f4cf0   (est. pmm_split_ranges)
 * Ghidra: undefined * FUN_000f4cf0(undefined8,undefined8,long,byte,ulong,ulong,undefined8,undefined8)
 * Builds a vector of (key, range) records covering [param_5, param_6), split
 * at 16 KiB frame boundaries. Each record is 0x20 bytes: a 16-byte key
 * (param_1/param_2), then start/end addresses. Uses frame-tagged resolution
 * and a growing vector; breaks at region-end flags.
 * Confidence: medium
 * Notes: uses FUN_002b439c, FUN_002b3b50, FUN_00073690 (grow); breakpoints
 *   at 0xf5074..0xf5080. */
uint8_t *pmm_split_ranges(uint64_t param_1, uint64_t param_2, long param_3, uint8_t param_4,
                          word_t param_5, word_t param_6, uint64_t param_7, uint64_t param_8) {
    word_t uVar6, uVar7, uVar3, uVar4;
    uint8_t *local_78;
    sk128_t auVar9, auVar10;

    auVar10.lo = param_1;
    auVar10.hi = param_2;
    if (param_3 < 0) { /* breakpoint 0xf5074 */ }
    uVar6 = param_5 >> 0xe;
    uVar7 = param_6 >> 0xe;
    if ((param_3 == 0) || (uVar6 == uVar7)) {
        if ((uVar6 == uVar7) && ((param_4 & 1) != 0)) {
            cL4_vector_del(param_8, 0);
            return (uint8_t *)&cL4_gbl4;
        }
        if (uVar7 < uVar6) { /* breakpoint 0xf507c */ }
        auVar10 = cL4_tbl_range(param_5, param_6, param_5, param_6, param_7, param_8);
        local_78 = (uint8_t *)cL4_grow(0, 1, 1, &cL4_gbl4);
        uVar6 = *(word_t *)(local_78 + 0x10);
        uVar7 = *(word_t *)(local_78 + 0x18);
    } else {
        cL4_put_reg(param_8, 0, 0);
        local_78 = (uint8_t *)&cL4_gbl4;
        uVar6 = param_5;
        uVar4 = param_5;
        for (;;) {
            word_t uVar8 = uVar6 >> 0xe;
            if (uVar8 == uVar7) break;
            auVar9 = cL4_tbl_enter(uVar6, param_5, param_6, param_7, param_8);
            if (auVar9.lo == auVar10.lo && auVar9.hi == auVar10.hi) {
                cL4_vector_del(auVar9.hi, 0);
            } else {
                uVar3 = cL4_tbl_resolve(auVar9.lo, auVar9.hi, param_1, param_2, 0);
                cL4_vector_del(auVar9.hi, 0);
                if ((uVar3 & 1) == 0) {
                    uVar6 = cL4_tbl_next(uVar6, param_5, param_6, param_7, param_8);
                    continue;
                }
            }
            bool bVar1 = ((uVar4 >> 0xe) == uVar8) & param_4;
            if (bVar1 == 0) {
                if (uVar8 < (uVar4 >> 0xe)) { /* breakpoint 0xf5078 */ }
                word_t uStart = param_5, uEnd = param_6;
                auVar9 = cL4_tbl_range(uVar4, uVar6, param_5, param_6, param_7, param_8);
                uVar4 = cL4_vector_add(local_78);
                if ((uVar4 & 1) == 0) {
                    local_78 = (uint8_t *)cL4_grow(0, *(long *)(local_78 + 0x10) + 1, 1, local_78);
                }
                uVar4 = *(word_t *)(local_78 + 0x10);
                if (*(word_t *)(local_78 + 0x18) >> 1 <= uVar4) {
                    local_78 = (uint8_t *)cL4_grow(1 < *(word_t *)(local_78 + 0x18), uVar4 + 1, 1, local_78);
                }
                *(word_t *)(local_78 + 0x10) = uVar4 + 1;
                /* record at local_78 + uVar4*0x20 + 0x20 = auVar9, +0x30 = uStart, +0x38 = uEnd */
            }
            uVar4 = cL4_tbl_next(uVar6, param_5, param_6, param_7, param_8);
            uVar6 = uVar4;
            if (bVar1 != 0) continue;
            if (*(long *)(local_78 + 0x10) == param_3) break;
        }
        if ((uVar4 >> 0xe == uVar7) && ((param_4 & 1) != 0)) {
            cL4_vector_ret(param_8, 2);
            return local_78;
        }
        if (uVar7 < (uVar4 >> 0xe)) { /* breakpoint 0xf5080 */ }
        auVar10 = cL4_tbl_range(uVar4, param_6, param_5, param_6, param_7, param_8);
        cL4_vector_del(param_8, 0);
        uVar6 = cL4_vector_add(local_78);
        if ((uVar6 & 1) == 0) {
            local_78 = (uint8_t *)cL4_grow(0, *(long *)(local_78 + 0x10) + 1, 1, local_78);
        }
        uVar6 = *(word_t *)(local_78 + 0x10);
        uVar7 = *(word_t *)(local_78 + 0x18);
    }
    if (uVar7 >> 1 <= uVar6) {
        local_78 = (uint8_t *)cL4_grow(1 < uVar7, uVar6 + 1, 1, local_78);
    }
    cL4_vector_del(param_8, 0);
    *(word_t *)(local_78 + 0x10) = uVar6 + 1;
    /* record at local_78 + uVar6*0x20 + 0x20 = auVar10, +0x30 = param_5, +0x38 = param_6 */
    return local_78;
}

/* FUN_000f5080 @ 0x000f5080   (est. pmm_frame_map_walk)
 * Ghidra: undefined1 [16] FUN_000f5080(undefined8 *,undefined8,long,ulong)
 * Walks the PMM frame bitmap (a bit set stored in a descriptor at
 * _DAT_006577e0) and performs cow-frame / region merge operations on each
 * set frame, building a result vector of merged (key, range) records. Also
 * handles the not-present fault path (allocates/registers a new object and
 * re-enters). Complex control flow; decompiler removed unreachable blocks.
 * Confidence: low
 * Notes: LZCOUNT-based bit scan; unreachable blocks at 0xf51d8/0xf5c10/0xf5c20;
 *   SoftwareBreakpoint panics at 0xf5bfc..0xf5c10; globals overlap warning. */
sk128_t pmm_frame_map_walk(uint64_t *param_1, uint64_t param_2, long param_3, word_t param_4) {
    uint64_t *puVar1;
    uint8_t  *pbVar2;
    uint64_t  uVar3, uVar10, uVar11, uVar12, uVar13, uVar14, uVar19, uVar23;
    uint64_t  uVar16, uVar17, uVar18, uVar21, uVar24, uVar25, uVar26, uVar29, uVar31, uVar32;
    uint8_t   bVar4, bVar5, uVar7;
    bool      bVar6;
    int       iVar8;
    long      lVar15, lVar20, lVar27;
    uint32_t  uVar28;
    uint64_t *puVar22, *puVar30;
    uint64_t *puVar_scan;
    sk128_t   auVar33, auVar34, auVar35;
    uint64_t  local_2c0;
    word_t    local_2b8;
    long      local_2b0, local_2a8;
    uint8_t  *local_240;
    uint64_t  local_1e0, local_1d8, local_1d0, local_1c8;
    uint64_t *local_1b0;
    uint64_t  local_118, local_108, local_f8, local_f0, local_e0, local_d0, local_c8, local_c0;
    uint64_t  local_80, local_90, uStack_88, uStack_78, uStack_98, uStack_d8, uStack_100, local_a0;
    uint64_t  local_1c0, extraout_x1;
    long      lStack_e8, lStack_b8, local_110;
    sk128_t   local_b0;
    uint64_t  local_2b8_lo;
    uint64_t  scratch[10];

    local_2b0 = param_3;
    local_2b8 = param_4;
    auVar33 = cL4_state_pair(0, 6);
    uVar23 = *param_1;
    lVar27 = 0;
    /* pcVar9 = FUN_000f5d00(param_2);  auVar34 = (*pcVar9)(scratch, uVar23, param_2); */
    auVar34.lo = 0; auVar34.hi = lVar27;
    lVar27 = auVar34.hi;
    if (lVar27 == 0) {
        cL4_fault_chk(0, 0);
        if (/* in_ZR */ true) {
            uVar23 = cL4_fault_get();
            lVar27 = cL4_vtable_reg(uVar23, 0);
            /* *(lVar27+0x18) = uRam00000000004baeb8; *(lVar27+0x10) = _DAT_004baeb0; */
            *(uint64_t *)(lVar27 + 0x38) = 0x6753a0;
            *(uint64_t *)(lVar27 + 0x20) = 0xd00000000000003d;
            *(uint64_t *)(lVar27 + 0x28) = 0x80000000005c52b0;
            cL4_init3();
            cL4_finalize(lVar27);
            uVar23 = cL4_init4();
            cL4_put_reg(uVar23, 0x20, 7);
        }
        return auVar33;
    }
    local_1b0 = &cL4_gbl16;
    uVar10 = cL4_init_type(0x6524c8, &cL4_gbl7);
    uVar13 = uVar10;
    uVar11 = cL4_find(0xd000000000000024, 0x80000000005c52f0, 1, uVar10);
    lVar15 = lVar27;
    auVar35 = cL4_frame_classify(0xf, auVar34.lo, lVar27);
    uVar12 = cL4_obj_ref(uVar11, uVar10);
    cL4_mkrec(&local_118, auVar35.lo, auVar35.hi, lVar15, uVar13, uVar12, uVar10);
    cL4_vector_del(uVar13, 0);
    cL4_obj_unref(uVar12);
    if (local_110 != 0) {
        local_f0 = local_118;
        lStack_e8 = local_110;
        uStack_d8 = uStack_100;
        local_e0 = local_108;
        local_d0 = local_f8;
        uVar13 = cL4_tbl_lookup(&cL4_gbl14);
        uVar10 = cL4_init_type(0x652500, &cL4_gbl11);
        cL4_describe(&local_b0, uVar13, uVar10);
        cL4_obj_unref(uVar13);
        uVar13 = local_e0;
        lStack_b8 = lStack_e8;
        local_c0 = local_f0;
        pmm_fptr_22_call(&local_c0);
        local_c8 = uVar13;
        pmm_release_word(&local_c8);
        lVar20 = (long)pmm_split_ranges(0x2c, 0xe100000000000000, 0x7fffffffffffffff, 1,
                                     local_b0.lo, local_b0.hi, local_a0, uStack_98);
        lVar15 = *(long *)(lVar20 + 0x10);
        if (lVar15 != 0) {
            puVar22 = (uint64_t *)(lVar20 + 0x38);
            do {
                uVar13 = puVar22[-3];
                uVar12 = puVar22[-2];
                uVar10 = puVar22[-1];
                uVar3 = *puVar22;
                cL4_obj_ref(uVar3, 0);
                auVar35 = cL4_tbl_get(uVar13, uVar12, uVar10, uVar3);
                cL4_vector_del(uVar3, 0);
                cL4_vector_rel(local_b0.lo, auVar35.lo, auVar35.hi);
                cL4_vector_del(local_b0.hi, 0);
                puVar22 += 4;
                lVar15--;
            } while (lVar15 != 0);
        }
        cL4_obj_unref(lVar20);
    }
    uVar13 = cL4_init_type(0x6524d0, &cL4_gbl8);
    uVar14 = cL4_find(0xd000000000000029, 0x80000000005c5320, 1, uVar13);
    local_1e0 = uVar14;
    local_b0 = auVar34;
    uVar10 = cL4_init_type(0x6524d8, &cL4_gbl9);
    pmm_const_2(); uVar12 = 0;
    lVar15 = cL4_svc(&local_1e0, 0x6753a0, uVar13, uVar10, uVar12, 0x686470);
    cL4_vector_del(lVar27, 0);
    uVar21 = *(uint64_t *)(lVar15 + 0x10);
    if (uVar21 != 0) {
        uVar31 = 0;
    map_loop:
        if (*(uint64_t *)(lVar15 + 0x10) <= uVar31) { /* breakpoint 0xf5c00 */ }
        puVar22 = (uint64_t *)(lVar15 + 0x20 + uVar31 * 0x28);
        uStack_98 = puVar22[3];
        local_a0 = puVar22[2];
        local_b0.hi = puVar22[1];
        local_b0.lo = *puVar22;
        local_90 = puVar22[4];
        uStack_88 = local_a0;
        local_80 = local_b0.lo;
        uStack_78 = local_b0.hi;
        auVar34 = cL4_vector_pop(param_3, param_4);
        local_1c0 = auVar34.lo;
        uVar13 = cL4_tbl_lookup(&cL4_gbl12);
        pmm_fptr_2a_call(&local_80, &local_1e0);
        pmm_copy_word(&uStack_88, &local_1e0);
        uVar10 = cL4_init_type(0x6524e8, &cL4_gbl10);
        cL4_describe(&local_1e0, uVar13, uVar10);
        cL4_obj_unref(uVar13);
        uVar13 = local_1c8;
        cL4_tbl_get(local_1e0, local_1d8, local_1d0, local_1c8);
        auVar35 = cL4_vector_pop(0, 0);
        cL4_vector_del(uVar13, 0);
        cL4_vector_del(extraout_x1, 0);
        pmm_const_3(); uVar13 = 0;
        uVar16 = cL4_vector_put(auVar35.lo, auVar35.hi, 0x6753a0, uVar13);
        cL4_vector_del(auVar34.hi, 0);
        cL4_vector_del(auVar35.hi, 0);
        if ((uVar16 & 1) != 0) {
            uVar13 = cL4_tbl_lookup(&cL4_gbl13);
            cL4_describe(&local_1e0, uVar13, uVar10);
            cL4_obj_unref(uVar13);
            pmm_fptr_22_call(&local_80);
            pmm_release_word(&uStack_88);
            uVar10 = local_1c8;
            uVar13 = local_1d0;
            uVar26 = local_1d8;
            uVar16 = local_1e0;
            uVar24 = local_1d8 >> 0xe;
            if (uVar24 != (local_1e0 >> 0xe)) {
                cL4_obj_ref(local_1c8, 0);
                local_240 = (uint8_t *)&cL4_gbl4;
                uVar18 = uVar16;
                uVar25 = uVar16;
                for (;;) {
                    uVar29 = uVar18 >> 0xe;
                    uVar32 = uVar25 >> 0xe;
                    if (uVar29 == uVar24) goto merge_done;
                    pmm_noop_12();
                    auVar34 = cL4_tbl_enter2();
                    lVar27 = auVar34.hi;
                    if ((auVar34.lo == 0x2c) && (lVar27 == -0x1f00000000000000)) {
                        cL4_vector_del(lVar27, 0);
                    } else {
                        uVar17 = cL4_tbl_resolve(auVar34.lo, lVar27, 0x2c, 0xe100000000000000, 0);
                        cL4_vector_del(lVar27, 0);
                        if ((uVar17 & 1) == 0) {
                            pmm_noop_12();
                            uVar18 = cL4_tbl_next2();
                            continue;
                        }
                    }
                    if (uVar32 != uVar29) {
                        if (uVar29 < uVar32) { /* breakpoint 0xf5c04 */ }
                        uVar29 = uVar16;
                        uVar32 = uVar26;
                        auVar34 = cL4_tbl_range(uVar25, uVar18, uVar16, uVar26, uVar13, uVar10);
                        uVar18 = cL4_vector_add(local_240);
                        if ((uVar18 & 1) == 0) {
                            local_240 = (uint8_t *)cL4_grow(0, *(long *)(local_240 + 0x10) + 1, 1, local_240);
                        }
                        uVar18 = *(uint64_t *)(local_240 + 0x10);
                        if (*(uint64_t *)(local_240 + 0x18) >> 1 <= uVar18) {
                            local_240 = (uint8_t *)cL4_grow(1 < *(uint64_t *)(local_240 + 0x18),
                                                           uVar18 + 1, 1, local_240);
                        }
                        *(uint64_t *)(local_240 + 0x10) = uVar18 + 1;
                        /* record at local_240 + uVar18*0x20 + 0x20 = auVar34; +0x30=uVar29; +0x38=uVar32 */
                    }
                    pmm_noop_12();
                    uVar18 = cL4_tbl_next2();
                    uVar25 = uVar18;
                }
            }
            cL4_vector_del(local_1c8, 0);
            local_240 = (uint8_t *)&cL4_gbl4;
            goto drain_records;
        }
        pmm_fptr_22_call(&local_80);
        pmm_release_word(&uStack_88);
        goto advance_bit;
    }
merge_done:
    if (uVar32 == uVar24) {
        cL4_vector_ret(uVar10, 2);
    } else {
        if (uVar24 < uVar32) { /* breakpoint 0xf5c08 */ }
        auVar34 = cL4_tbl_range(uVar25, uVar26, uVar16, uVar26, uVar13, uVar10);
        cL4_vector_del(uVar10, 0);
        uVar24 = cL4_vector_add(local_240);
        if ((uVar24 & 1) == 0) {
            local_240 = (uint8_t *)cL4_grow(0, *(long *)(local_240 + 0x10) + 1, 1, local_240);
        }
        uVar24 = *(uint64_t *)(local_240 + 0x10);
        if (*(uint64_t *)(local_240 + 0x18) >> 1 <= uVar24) {
            local_240 = (uint8_t *)cL4_grow(1 < *(uint64_t *)(local_240 + 0x18), uVar24 + 1, 1, local_240);
        }
        cL4_vector_del(uVar10, 0);
        *(uint64_t *)(local_240 + 0x10) = uVar24 + 1;
        /* record at local_240 + uVar24*0x20 + 0x20 = auVar34; +0x30=uVar16; +0x38=uVar26 */
    }
drain_records:
    lVar27 = *(long *)(local_240 + 0x10);
    if (lVar27 == 0) {
        cL4_obj_unref(0);
    } else {
        puVar22 = (uint64_t *)(local_240 + 0x38);
        do {
            uVar13 = puVar22[-3];
            uVar12 = puVar22[-2];
            uVar10 = puVar22[-1];
            uVar3 = *puVar22;
            cL4_obj_ref(uVar3, 0);
            auVar34 = cL4_tbl_get(uVar13, uVar12, uVar10, uVar3);
            cL4_vector_del(uVar3, 0);
            cL4_vector_rel(&local_1e0, auVar34.lo, auVar34.hi);
            cL4_vector_del(local_1d8, 0);
            puVar22 += 4;
            lVar27--;
        } while (lVar27 != 0);
        cL4_obj_unref((long)local_240);
    }
advance_bit:
    uVar31++;
    if (uVar31 == uVar21) goto map_reload;
    goto map_loop;
map_reload:
    cL4_obj_unref(lVar15);
    puVar22 = local_1b0;
    puVar30 = local_1b0 + 7;
    uVar31 = 1ULL << (*(uint8_t *)(local_1b0 + 4) & 0x3f);
    uVar21 = 0xffffffffffffffffULL;
    if ((*(uint8_t *)(local_1b0 + 4) & 0x3f) < 6) {
        uVar21 = ~(-1LL << (uVar31 & 0x3f));
    }
    uVar21 &= *puVar30;
    cL4_obj_ref(local_1b0, 0);
    uVar10 = cL4_gbl3;
    uVar13 = cL4_gbl2;
    lVar27 = 0;
    while (true) {
        local_2a8 = auVar33.hi;
        local_2c0 = auVar33.lo;
        while (uVar21 == 0) {
            bVar6 = (lVar27 == 0x7fffffffffffffff);
            lVar27++;
            if (bVar6) { /* breakpoint 0xf5bfc */ }
            if ((long)((uVar31 + 0x3f) >> 6) <= lVar27) {
                cL4_obj_unref(uVar11);
                cL4_obj_unref(uVar14);
                cL4_vector_del((long)puVar22, 0);
                cL4_obj_unref((long)puVar22);
                return auVar33;
            }
            uVar21 = puVar30[lVar27];
        }
        uVar16 = (uVar21 & 0xaaaaaaaaaaaaaaaa) >> 1 | (uVar21 & 0x5555555555555555) << 1;
        uVar16 = (uVar16 & 0xcccccccccccccccc) >> 2 | (uVar16 & 0x3333333333333333) << 2;
        uVar16 = (uVar16 & 0xf0f0f0f0f0f0f0f0) >> 4 | (uVar16 & 0xf0f0f0f0f0f0f0f) << 4;
        uVar16 = (uVar16 & 0xff00ff00ff00ff00) >> 8 | (uVar16 & 0xff00ff00ff00ff) << 8;
        uVar16 = (uVar16 & 0xffff0000ffff0000) >> 0x10 | (uVar16 & 0xffff0000ffff) << 0x10;
        puVar_scan = (uint64_t *)(puVar22[6] + cL4_lzcount(uVar16 >> 0x20 | uVar16 << 0x20) * 0x10 +
                                  lVar27 * 0x400);
        uVar12 = *puVar_scan;
        uVar3 = puVar_scan[1];
        cL4_obj_ref(uVar3, 0);
        uVar7 = 0;
        pmm_noop_11();
        cL4_reg_state();
        lVar15 = cL4_pmm_gbl;
        uVar21 = (uVar21 - 1) & uVar21;
        if (*(long *)(cL4_pmm_gbl + 0x10) != 0) break;
    not_present:
        cL4_fault_chk(0, 0);
        if (uVar7) {
            uVar19 = cL4_fault_get();
            lVar15 = cL4_vtable_reg(uVar19, 0);
            *(uint64_t *)(lVar15 + 0x18) = uVar10;
            *(uint64_t *)(lVar15 + 0x10) = uVar13;
            local_1e0 = 0;
            local_1d8 = 0xe000000000000000;
            cL4_switch(0x3e);
            cL4_panic_msg(0xd000000000000013, 0x80000000005c5350);
            cL4_panic_msg(uVar12, uVar3);
            cL4_panic_msg(0xd000000000000029, 0x80000000005c5370);
            *(uint64_t *)(lVar15 + 0x38) = 0x6753a0;
            *(uint64_t *)(lVar15 + 0x20) = local_1e0;
            *(uint64_t *)(lVar15 + 0x28) = local_1d8;
            cL4_init3();
            cL4_finalize(lVar15);
            uVar12 = cL4_init4();
            cL4_put_reg(uVar12, 0x20, 7);
        }
        cL4_vector_del(uVar3, 0);
    }
    cL4_obj_ref(cL4_pmm_gbl, 0);
    auVar34 = cL4_tbl_query(uVar12, uVar3);
    if ((auVar34.hi & 1) == 0) {
        cL4_vector_del(lVar15, 0);
        goto not_present;
    }
    pbVar2 = (uint8_t *)(*(long *)(lVar15 + 0x38) + auVar34.lo * 2);
    bVar4 = *pbVar2;
    uVar16 = bVar4;
    bVar5 = pbVar2[1];
    uVar28 = bVar5;
    cL4_vector_del(lVar15, 0);
    cL4_vector_del(uVar3, 0);
    if ((bVar4 == 2) && (bVar5 == 1)) {
        /* code_r0x000f5868: re-resolve and set a cow bit */
        lVar27 = cL4_fault_go(param_2);
        uVar16 = 0;
        /* (*pcVar9)(auStack_168, uVar23, param_2); */
        if ((uVar16 & 1) == 0) continue;
        uVar28 = 1;
        uVar16 = 2;
    }
    uVar26 = local_2b8 >> 1;
    if ((long)uVar16 < local_2b0 || uVar26 <= uVar16) { /* breakpoint 0xf5c0c */ }
    bVar5 = *(uint8_t *)(local_2a8 + uVar16);
    bVar4 = 0;
    if (uVar28 < 8) {
        bVar4 = (uint8_t)(1 << (uVar28 & 7));
    }
    if ((local_2b8 & 1) != 0) {
        iVar8 = cL4_vector_add(local_2c0);
        if (iVar8 != 0) goto set_bit;
    }
    auVar33 = cL4_enter_fault(local_2c0, local_2a8);
    uVar26 = local_2b8 >> 1;
set_bit:
    local_2a8 = auVar33.hi;
    if ((long)uVar16 < local_2b0 || uVar26 <= uVar16) { /* breakpoint 0xf5c10 */ }
    *(uint8_t *)(local_2a8 + uVar16) = bVar5 | bVar4;
    (void)local_2b8_lo; (void)local_2c0; (void)local_1c0; (void)uVar29;
    (void)puVar_scan; (void)local_240; (void)local_2b8; (void)local_2b0;
}

/* FUN_000f5c74 @ 0x000f5c74   (est. pmm_tbl_init)
 * Ghidra: void FUN_000f5c74(void)
 * Initializes the global PMM table/object (_DAT_006ad9e0) via the table
 * constructor FUN_001f0130 with four type/pointer arguments.
 * Confidence: low  Notes: _DAT_006ad9e0 = FUN_001f0130(0x662348,...). */
void pmm_tbl_init(void) {
    cL4_pmm_gbl = cL4_tbl_init(0x662348, 0x6753a0, 0x662330, 0x66dfb8);
}

/* FUN_000f5c78 @ 0x000f5c78   (est. pmm_tbl_init2)
 * Identical body to pmm_tbl_init (pair/const-overload thunk).
 * Confidence: low  Notes: _DAT_006ad9e0 = FUN_001f0130(...). */
void pmm_tbl_init2(void) {
    cL4_pmm_gbl = cL4_tbl_init(0x662348, 0x6753a0, 0x662330, 0x66dfb8);
}

/* FUN_000f5cd4 @ 0x000f5cd4   (est. pmm_tbl_get)
 * Ghidra: undefined1 * FUN_000f5cd4(void)
 * Runs the cL4 reg-state helper twice, then returns the address of the
 * global PMM table/object (_DAT_006ad9e0).
 * Confidence: low  Notes: FUN_000f606c, FUN_0039a128. */
uint8_t *pmm_tbl_get(void) {
    cL4_reg_state(); /* FUN_000f606c(0x6524f8) */
    cL4_reg_state(); /* FUN_0039a128() */
    return (uint8_t *)&cL4_pmm_gbl;
}

/* FUN_000f5d00 @ 0x000f5d00   (est. pmm_unpack_retaddr)
 * Ghidra: long FUN_000f5d00(ulong param_1)
 * If the low bit of param_1 is set, dereferences the tagged pointer
 * (param_1 & ~1) to load the real value; then computes
 * (value + 0x10) + *(int *)(value + 0x10) — resolving a return-address /
 * relocation table entry.
 * Confidence: medium  Notes: tagged-pointer + int-offset resolution. */
long pmm_unpack_retaddr(word_t param_1) {
    if ((param_1 & 1) != 0) {
        param_1 = *(word_t *)(param_1 & 0xfffffffffffffffeULL);
    }
    return (long)(param_1 + 0x10) + (long)*(int *)(param_1 + 0x10);
}

/* FUN_000f5d30 @ 0x000f5d30   (est. pmm_const_2)
 * Ghidra: void FUN_000f5d30(void)
 * Stores a fixed 8-byte constant into the global word at 0x6524e0
 * (uRam00000000006524e0 = 0x54000348eb08013f). Data/init stub.
 * Confidence: low  Notes: unreachable block removed at 0xf5d44. */
void pmm_const_2(void) {
    /* uRam00000000006524e0 = 0x54000348eb08013f; */
}

/* FUN_000f5d84 @ 0x000f5d84   (est. pmm_fptr_2a_call)
 * Ghidra: undefined8 FUN_000f5d84(undefined8,undefined8)
 * Calls the function pointer stored in the global _DAT_f108181f3700022a
 * with (param_2, param_1), returning param_2.
 * Confidence: low  Notes: (*_DAT_f108181f3700022a)(param_2, param_1). */
uint64_t pmm_fptr_2a_call(uint64_t param_1, uint64_t param_2) {
    /* (*_DAT_f108181f3700022a)(param_2, param_1); */
    return param_2;
}

/* FUN_000f5dd8 @ 0x000f5dd8   (est. pmm_copy_word)
 * Ghidra: undefined8 * FUN_000f5dd8(undefined8 *,undefined8 *)
 * Copies the first word of param_1 into param_2, retains the source, and
 * returns param_2.
 * Confidence: low  Notes: *param_2 = *param_1; FUN_0036b270(); */
uint64_t *pmm_copy_word(uint64_t *param_1, uint64_t *param_2) {
    *param_2 = *param_1;
    cL4_obj_ref(0, 0);
    return param_2;
}

/* FUN_000f5e08 @ 0x000f5e08   (est. pmm_const_3)
 * Ghidra: void FUN_000f5e08(void)
 * Stores a fixed 8-byte constant into the global word at 0x6524f0
 * (uRam00000000006524f0 = 0x540002c8eb09011f). Data/init stub.
 * Confidence: low  Notes: unreachable block removed at 0xf5e1c. */
void pmm_const_3(void) {
    /* uRam00000000006524f0 = 0x540002c8eb09011f; */
}

/* FUN_000f5e5c @ 0x000f5e5c   (est. pmm_fptr_22_call)
 * Ghidra: undefined8 FUN_000f5e5c(undefined8 param_1)
 * Calls the function pointer stored in the global _DAT_f108181f37000222
 * with no arguments, returning param_1 unchanged.
 * Confidence: low  Notes: (*_DAT_f108181f37000222)(); */
uint64_t pmm_fptr_22_call(uint64_t param_1) {
    /* (*_DAT_f108181f37000222)(); */
    return param_1;
}

/* FUN_000f5ea8 @ 0x000f5ea8   (est. pmm_release_word)
 * Ghidra: undefined8 * FUN_000f5ea8(undefined8 *param_1)
 * Releases the object in *param_1 and returns param_1.
 * Confidence: low  Notes: FUN_0036b118(*param_1). */
uint64_t *pmm_release_word(uint64_t *param_1) {
    cL4_obj_unref(*param_1);
    return param_1;
}

/* FUN_000f6028 @ 0x000f6028   (est. pmm_dispatch_2)
 * Ghidra: void FUN_000f6028(void)
 * Copies six caller-stack argument words into stack locals, then calls the
 * cL4 dispatch-2 helper with (0x6673a0, 0x6672a8, 0, 0).
 * Confidence: low  Notes: FUN_0036993c. */
void pmm_dispatch_2(void) {
    cL4_dispatch2(0x6673a0, 0x6672a8);
}

/* FUN_000f606c @ 0x000f606c   (est. pmm_noop_11) — empty body. */
void pmm_noop_11(void) {}

/* FUN_000f6084 @ 0x000f6084   (est. pmm_frame_desc_store)
 * Ghidra: void FUN_000f6084(undefined8,undefined8 *)
 * Captures six caller-stack argument words plus two register values (x19,
 * x20) and a byte (w21) into the 9-word descriptor at param_2.
 * Confidence: low  Notes: builds a frame/op descriptor record. */
void pmm_frame_desc_store(uint64_t param_1, uint64_t *param_2) {
    (void)param_1;
    /* param_2[0..5] = stack args 0xb0..0x90; param_2[6]=x19; param_2[7]=x20; byte=x21 */
}

/* FUN_000f60b0 @ 0x000f60b0   (est. pmm_noop_12) — empty body. */
void pmm_noop_12(void) {}

/* FUN_000f60c4 @ 0x000f60c4   (est. pmm_async_submit)
 * Ghidra: void FUN_000f60c4(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Fetches the async-state word pair and submits an asynchronous operation
 * that will invoke the callback FUN_000f645c, passing param_2/param_3 as
 * callback context.
 * Confidence: medium  Notes: FUN_00151974 + FUN_00151a6c(FUN_000f645c,...). */
void pmm_async_submit(uint64_t param_1, uint64_t param_2, uint64_t param_3,
                      uint64_t param_4, uint64_t param_5, uint64_t param_6, uint64_t param_7) {
    sk128_t st = cL4_async_state(); /* FUN_00151974 */
    uint64_t local_50 = param_2;
    uint64_t uStack_48 = param_3;
    (void)param_1; (void)param_4; (void)param_5; (void)param_6; (void)param_7;
    cL4_async_setup((uint64_t)(uintptr_t)&pmm_async_cb_fwd, 0, param_4, param_5, param_6, param_7,
                    st.lo, st.hi);
    (void)local_50; (void)uStack_48;
}

/* FUN_000f6224 @ 0x000f6224   (est. pmm_err_3b)
 * Ghidra: void FUN_000f6224(void)
 * Reports error code 0x3b with string at 0x80000000005c5670.
 * Confidence: low  Notes: FUN_000b42b8(0x3b, 0x80000000005c5670). */
void pmm_err_3b(void) {
    cL4_report_error(0x3b, (void *)0x80000000005c5670ULL);
}

/* FUN_000f623c @ 0x000f623c   (est. pmm_err_37)
 * Reports error code 0x37 with string at 0x80000000005c5630.
 * Confidence: low  Notes: FUN_000b42b8(0x37, 0x80000000005c5630). */
void pmm_err_37(void) {
    cL4_report_error(0x37, (void *)0x80000000005c5630ULL);
}

/* FUN_000f626c @ 0x000f626c   (est. pmm_err_36)
 * Reports error code 0x36 with string at 0x80000000005c5710.
 * Confidence: low  Notes: FUN_000b42b8(0x36, 0x80000000005c5710). */
void pmm_err_36(void) {
    cL4_report_error(0x36, (void *)0x80000000005c5710ULL);
}

/* FUN_000f629c @ 0x000f629c   (est. pmm_err_execctx)
 * Ghidra: void FUN_000f629c(void)
 * Reports the "Failed setting execution context" failure via FUN_000f64ac.
 * Confidence: high  Notes: string match. */
void pmm_err_execctx(void) {
    pmm_pack_err_msg((long)(uintptr_t)cL4_s_execctx);
}

/* FUN_000f62a8 @ 0x000f62a8   (est. pmm_err_2d)
 * Reports error code 0x2d with string at 0x80000000005c56b0.
 * Confidence: low  Notes: FUN_000b42b8(0x2d, 0x80000000005c56b0). */
void pmm_err_2d(void) {
    cL4_report_error(0x2d, (void *)0x80000000005c56b0ULL);
}

/* FUN_000f6320 @ 0x000f6320   (est. pmm_err_3c)
 * Reports error code 0x3c with string at 0x80000000005c5950.
 * Confidence: low  Notes: FUN_000b42b8(0x3c, 0x80000000005c5950). */
void pmm_err_3c(void) {
    cL4_report_error(0x3c, (void *)0x80000000005c5950ULL);
}

/* FUN_000f6380 @ 0x000f6380   (est. pmm_err_41)
 * Reports error code 0x41 with string at 0x80000000005c5840.
 * Confidence: low  Notes: FUN_000b42b8(0x41, 0x80000000005c5840). */
void pmm_err_41(void) {
    cL4_report_error(0x41, (void *)0x80000000005c5840ULL);
}

/* FUN_000f6410 @ 0x000f6410   (est. pmm_err_pmmcreate)
 * Ghidra: void FUN_000f6410(void)
 * Reports the "PMMInstance could not create SC..." failure via FUN_000f64ac.
 * Confidence: high  Notes: string match. */
void pmm_err_pmmcreate(void) {
    pmm_pack_err_msg((long)(uintptr_t)cL4_s_pmmcreate);
}

/* FUN_000f6434 @ 0x000f6434   (est. pmm_call_fnptr)
 * Ghidra: void FUN_000f6434(code *param_1)
 * Invokes the function pointer in param_1.
 * Confidence: high  Notes: (*param_1)(); */
void pmm_call_fnptr(uint64_t (*param_1)(void)) {
    if (param_1) param_1();
}

/* FUN_000f645c @ 0x000f645c   (est. pmm_async_cb_fwd)
 * Ghidra: void FUN_000f645c(void)
 * Calls the function pointer stored at this+0x10 (async callback forwarder).
 * Confidence: low  Notes: this = x20; (**(code **)(x20 + 0x10))(). */
void pmm_async_cb_fwd(void) {
    /* (**(code **)(unaff_x20 + 0x10))(); */
}

/* FUN_000f64ac @ 0x000f64ac   (est. pmm_pack_err_msg)
 * Ghidra: undefined1 [16] FUN_000f64ac(long param_1)
 * Builds a 128-bit error descriptor: lo = 0xd000000000000026,
 * hi = (param_1 - 0x20) | 0x8000000000000000.
 * Confidence: medium  Notes: returns {0xd000000000000026, param_1-0x20|0x8000...}. */
sk128_t pmm_pack_err_msg(long param_1) {
    sk128_t r;
    r.lo = 0xd000000000000026ULL;
    r.hi = (uint64_t)(param_1 - 0x20U) | 0x8000000000000000ULL;
    return r;
}

/* FUN_000f64c0 @ 0x000f64c0   (est. pmm_reg3)
 * Ghidra: undefined8 FUN_000f64c0(undefined8,undefined8)
 * Saves the current register-state value, runs the cL4 async-cb helper with
 * (param_1, param_2), and returns the saved value.
 * Confidence: low  Notes: FUN_0036a940() + FUN_000f67b4(param_1,param_2). */
uint64_t pmm_reg3(uint64_t param_1, uint64_t param_2) {
    uint64_t uVar1 = cL4_get_reg(); /* FUN_0036a940 */
    cL4_async_cb(param_1, param_2); /* FUN_000f67b4 */
    return uVar1;
}

/* FUN_000f6518 @ 0x000f6518   (est. pmm_attr_get)
 * Ghidra: void FUN_000f6518(undefined8 *param_1)
 * Reads three attribute words from the object (fields of the sub-object at
 * this+0x10, plus this+0x20) and writes them into param_1[0..2].
 * Confidence: low  Notes: this = x20; getter. */
void pmm_attr_get(uint64_t *param_1) {
    word_t uVar1 = /* this+0x20 */ 0;
    word_t uVar2 = /* *(*(this+0x10)+0x10) */ 0;
    word_t uVar3 = /* *(*(this+0x10)+0x18) */ 0;
    param_1[1] = uVar3;
    param_1[0] = uVar2;
    param_1[2] = uVar1;
}

/* FUN_000f6530 @ 0x000f6530   (est. pmm_set_execctx)
 * Ghidra: void FUN_000f6530(long,long *)
 * Sets the object's execution-context sub-object (this+0x10) to param_1,
 * then copies its attribute pair into the object and runs an inner
 * operation; on failure releases and reports.
 * Confidence: low  Notes: this = x20, x21 = success flag; unreachable block
 *   removed at 0xf6660. */
void pmm_set_execctx(long param_1, long *param_2) {
    /* this+0x10 = param_1; */
    word_t uVar1 = *(word_t *)(param_1 + 0x10);
    word_t uVar2 = *(word_t *)(param_1 + 0x18);
    /* pcVar4 = *(param_2->vtable + 0x1b8); */
    cL4_obj_ref(0, 0);
    /* (*pcVar4)(&local_90, 8, uVar1, uVar2, 0, 0); */
    if (0 /* unaff_x21 == 0 */) {
        /* this+0x20 = uStack_88; this+0x18 = local_90; this+0x30 = uStack_78;
         * this+0x28 = uStack_80; this+0x40 = CONCAT71(...); this+0x38 = local_70;
         * this+0x49 = uStack_5f; this+0x41 = CONCAT17(...); */
        /* plVar3 = *(this+0x10)->+0x20; (*plVar3->vtable+0x70)(&local_90); */
        cL4_obj_unref(0);
        cL4_obj_unref(param_1);
        cL4_obj_unref((long)param_2);
    } else {
        cL4_obj_unref(param_1);
        cL4_obj_unref((long)param_2);
        cL4_obj_unref(/* this+0x10 */ 0);
        cL4_free_list(0);
    }
}

