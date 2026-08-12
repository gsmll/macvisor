/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SK188 slice (0x004081cc-0x0040a9f4): the Swift L4 async-runtime / job
 * machinery. The region is dominated by Swift-stored-property accessor
 * witnesses (getters/setters) for the async job/task object (self in
 * unaff_x22, unaff_x19, or unaff_x21), plus the core runtime primitives:
 *
 *   - L4 error-code reply helpers keyed off the two 16-byte globals
 *     s_L4_ErrorCodePermissionInvalid (0x0068a6b8) and
 *     s_L4_ErrorCodeOperationInvalid (0x0068a698) — each holds a
 *     function-pointer (word at +8) to a slot-owning allocator;
 *   - the double-word compare-exchange state machine on the job status word
 *     (job+0x60/+0x68, bit 0x800 = running/finalized) used by the error-reply
 *     builder (0x4085c0) and the job runner (0x4095a0);
 *   - the future/job enqueue-dequeue and reference-count release path
 *     (0x408db8, 0x408c4c, 0x408ae4, 0x4098c8, 0x4099d4, 0x4090f0);
 *   - the async job descriptor->job builder (0x409e90) and the "run inline
 *     within async" helper (0x409c24) — these install raw instruction words
 *     into freshly allocated storage (Ghidra warns "read-only address
 *     ram,0x00657998 is written");
 *   - the Swift data-race detector runtime (0x4088d8/0x408a3c/0x409180/
 *     0x409184, string "data race detected ... at ..." at 0x005dc6ba) and
 *     the fatal-error strings ("Fatal error: invalid clock ID %d" 0x005dc751,
 *     "called runInline within an async" 0x005dc7a6,
 *     "future reported an error, but wa..." 0x005dc82e,
 *     "Unexpected IsIsolatingCurrentCon..." 0x005dc773);
 *   - indirect dispatch thunks that jump through lazily-initialised global
 *     function pointers (_DAT_006adf78/80/88/98/a0) when a backing runtime
 *     hook is installed.
 *
 * Swift ABI: heap allocation (FUN_0040bb18 / FUN_0040bcf8 / FUN_000101a0),
 * retain/release (FUN_0036b270 / FUN_0036b118) and lock operations
 * (LOAcquire/LORelease, FUN_0037a978/FUN_0037a48c) are rendered faithfully;
 * the high-level Swift semantics of the accessor block and of the indirect
 * dispatch thunks are necessarily partial. Confidence is medium for the
 * error-code/refcount/status machinery and low for the accessor block and
 * the instruction-patching data-race and job-builder functions.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* Ghidra's undefined1[16] return pair: _0_8_ = lo, _8_8_ = hi. */
typedef struct { word_t lo; word_t hi; } sk_128_t;

static sk_128_t sk_128_zero(void) { sk_128_t z = {0, 0}; return z; }

/* SoftwareBreakpoint(1, <addr>) — the cL4 panic/unreachable primitive. */
#define SK188_BKPT(addr) __builtin_trap()
/* LOAcquire()/LORelease() — Swift concurrency lock-owner acquire/release. */
#define LOAcquire()  sk_lo_acquire()
#define LORelease()  sk_lo_release()

/* ---- Globals (Ghidra DAT_/s_/string refs; address = ground truth). ---- */
extern word_t sk_l4_err_perm[2];   /* s_L4_ErrorCodePermissionInvalid @0x0068a6b8 (fn ptr at [1]) */
extern word_t sk_l4_err_op[2];     /* s_L4_ErrorCodeOperationInvalid   @0x0068a698 (fn ptr at [1]) */
extern word_t sk_rt_dispatch_78;   /* _DAT_006adf78 */
extern word_t sk_rt_dispatch_80;   /* _DAT_006adf80 */
extern word_t sk_rt_dispatch_88;   /* _DAT_006adf88 */
extern word_t sk_rt_dispatch_98;   /* _DAT_006adf98 */
extern word_t sk_rt_dispatch_a0;   /* _DAT_006adfa0 */
extern word_t sk_alloc_fn_658c88;  /* DAT_00658c88 (fn ptr) */
extern word_t sk_cputype;          /* __thread_bss.cputype */
extern int    sk_drace_mode;       /* _DAT_006c0b88 */
extern int    sk_drace_once90;     /* _DAT_006c0b90 (once token) */
extern word_t sk_drace_hook98;     /* _DAT_006c0b98 */
extern int    sk_drace_oncea0;     /* _DAT_006c0ba0 (once token) */
extern int    sk_drace_oncea8;     /* _DAT_006c0ba8 (once token) */

/* ---- Shared kernel / Swift-runtime externs (ground truth FUN_ address).
 * Arity is deliberately flexible (variadic) because the Swift ABI and
 * tail-merge conventions produce varying arg counts; bodies call them with
 * the counts shown in each decompile. ---- */
extern word_t sk_alloc(word_t, ...);            /* FUN_0040bb18 */
extern void   sk_free(word_t, ...);             /* FUN_0040bd24 */
extern word_t sk_alloc_buf(word_t, ...);        /* FUN_0040bcf8 */
extern word_t sk_alloc_pool(word_t, ...);       /* FUN_000101a0 */
extern void   sk_swift_retain(word_t, ...);             /* FUN_0036b270 */
extern void   sk_swift_release(word_t, ...);    /* FUN_0036b118 */
extern void   sk_lo_acquire(void);              /* LOAcquire */
extern void   sk_lo_release(void);              /* LORelease */
extern void   sk_lock_acquire(word_t, ...);     /* FUN_0037a48c */
extern void   sk_lock_release(word_t, ...);     /* FUN_0037a978 */
extern word_t sk_swift_array_destroy(word_t, ...);      /* FUN_0036a244 */
extern word_t sk_swift_array_append(word_t, ...);       /* FUN_0036a2ac */
extern word_t sk_swift_obj_free(word_t, ...);           /* FUN_0036b6ac */
extern word_t sk_string_cache(word_t, ...);             /* FUN_00002534 */
extern word_t sk_string_conv(word_t, ...);              /* FUN_00377824 */
extern word_t sk_string_conv2(word_t, ...);             /* FUN_00377dcc */
extern word_t sk_printf(word_t, ...);                   /* FUN_003f540c */
extern word_t sk_log(word_t, ...);                      /* FUN_003f6278 */
extern word_t sk_trace(word_t, ...);                    /* FUN_00251638 */
extern word_t sk_l4_log(word_t, ...);                   /* FUN_004b9d68 */
extern void   sk_memcpy(word_t, ...);           /* thunk_FUN_00114330 */
extern word_t sk_str_format(word_t, ...);       /* FUN_00116bb4 */
extern word_t sk_str_emit(word_t, ...);         /* FUN_0011883c */
extern word_t sk_str_emit2(word_t, ...);        /* FUN_0011858c */
extern word_t sk_clock_get(word_t, ...);        /* FUN_0011825c */
extern word_t sk_clock_get2(word_t, ...);       /* FUN_001181b4 */
extern word_t sk_heap_free(word_t, ...);                /* thunk_FUN_00012568 */
extern word_t sk_str_cmp(word_t, ...);          /* FUN_00377ca8 */
extern word_t sk_identity_hash(word_t, ...);    /* FUN_003a25b8 */
extern word_t sk_obj_merge(word_t, ...);        /* FUN_003d5284 */
extern word_t sk_obj_merge2(word_t, ...);               /* thunk_FUN_003d5138 */
extern word_t sk_obj_none(word_t, ...);                 /* FUN_003d3dac */
extern word_t sk_rt_once(word_t, ...);          /* FUN_003d3dd8 */
extern word_t sk_drace_mode_get(word_t, ...);   /* FUN_0035bdf8 */
extern word_t sk_drace_check2(word_t, ...);             /* FUN_00369b0c */
extern word_t sk_drace_install(word_t, ...);    /* thunk_FUN_00369b04 */
extern sk_128_t sk_copy128(word_t, ...);        /* FUN_0040c2d8 */
extern word_t sk_128_save(word_t, ...);         /* FUN_0040c0f8 */
extern word_t sk_128_load(word_t, ...);         /* FUN_0040bda0 */
extern word_t sk_job_clean(word_t, ...);                /* FUN_0040c5d8 */
extern word_t sk_cas_call(word_t, ...);         /* FUN_0040c09c */
extern word_t sk_cas_send(word_t, ...);         /* FUN_0040c640 */
extern word_t sk_state_lock(word_t, ...);               /* FUN_0040b2c8 */
extern word_t sk_state_set(word_t, ...);        /* FUN_0040b6cc */
extern word_t sk_build_front(word_t, ...);      /* FUN_0040bdd0 */
extern word_t sk_build_cb(word_t, ...);         /* FUN_0040af00 */
extern word_t sk_timer_cancel(word_t, ...);     /* FUN_0040d604 */
extern word_t sk_job_gc(word_t, ...);                   /* FUN_0040b084 */
extern word_t sk_job_gc2(word_t, ...);                  /* FUN_0040b0cc */
extern word_t sk_job_gc3(word_t, ...);                  /* FUN_0040b128 */
extern word_t sk_job_gc4(word_t, ...);                  /* FUN_0040b03c */
extern word_t sk_buf_init(word_t, ...);         /* FUN_004ba660 */
extern word_t sk_buf_zero(word_t, ...);         /* FUN_0040b280 */
extern word_t sk_timer_is_pending(word_t, ...); /* FUN_0040cfb0 */
extern word_t sk_job_finalize(word_t, ...);     /* FUN_0040c748 */
extern word_t sk_job_link(word_t, ...);         /* FUN_0040eef8 */
extern word_t sk_timer_arm(word_t, ...);        /* FUN_0040c970 */
extern word_t sk_job_wake(word_t, ...);         /* FUN_0040f5c0 */
extern word_t sk_job_delay(word_t, ...);        /* FUN_0040c3a4 */
extern word_t sk_job_async(word_t, ...);        /* FUN_0040c4b0 */
extern word_t sk_async_arg(word_t, ...);        /* FUN_0040cfec */
extern word_t sk_async_arg2(word_t, ...);       /* FUN_0040cfd0 */
extern word_t sk_rt_fallback_1(word_t, ...);            /* FUN_0040f9f4 */
extern word_t sk_rt_fallback_2(word_t, ...);            /* FUN_0040fa5c */
extern word_t sk_rt_fallback_3(word_t, ...);            /* FUN_0040faac */
extern word_t sk_rt_fallback_4(word_t, ...);            /* thunk_FUN_00019858 */
extern word_t sk_rt_check(word_t, ...);                 /* FUN_0040c350 */
extern word_t sk_rt_is_isolated(word_t, ...);           /* FUN_003fc8a0 */
extern word_t sk_job_meta(word_t, ...);         /* FUN_0040b128 */
extern word_t sk_fatal(word_t, ...) __attribute__((noreturn));            /* FUN_004ba640 */
extern void   sk_fatal2(void) __attribute__((noreturn));          /* FUN_00116d60 */
extern void   sk_stack_chk_fail(void) __attribute__((noreturn));  /* FUN_0011d7e8 */
extern void   sk_unreachable(void) __attribute__((noreturn));     /* FUN_001afa84 */

/* ---- Slice functions (forward declarations). ---- */
static void    sk_l4_init_call(word_t g);                                    /* 4081cc */
static word_t  sk_acc_get_90(word_t self);                                  /* 4081d8 */
static void    sk_acc_void_1(void);                                          /* 4081e4 */
static void    sk_acc_void_2(void);                                          /* 4081f0 */
static void    sk_acc_void_3(void);                                          /* 4081fc */
static sk_128_t sk_acc_get_3850(word_t self);                                /* 408210 */
static void    sk_acc_set_multi(word_t a, word_t v);                         /* 408224 */
static void    sk_acc_void_4(void);                                          /* 408238 */
static void    sk_acc_void_5(void);                                          /* 408244 */
static void    sk_acc_void_6(void);                                          /* 408258 */
static sk_128_t sk_acc_get_a090(word_t self);                                /* 40826c */
static sk_128_t sk_acc_get_6038(word_t self);                                /* 408280 */
static void    sk_acc_void_7(void);                                          /* 408294 */
static void    sk_acc_void_8(void);                                          /* 4082a8 */
static void    sk_acc_void_9(void);                                          /* 4082b4 */
static void    sk_acc_set_byte10(word_t self, uint8_t v);                    /* 4082c8 */
static void    sk_acc_set_slot0(word_t *self, word_t v);                     /* 4082d4 */
static void    sk_acc_copy2(word_t dst, word_t src);                         /* 4082e0 */
static void    sk_acc_set_40(word_t self, word_t v);                         /* 408308 */
static void    sk_acc_void_10(void);                                         /* 408314 */
static void    sk_acc_set_b0(word_t self, word_t v);                         /* 408328 */
static void    sk_acc_void_11(void);                                         /* 40833c */
static sk_128_t sk_acc_get_8070(word_t self);                                /* 408348 */
static void    sk_acc_set_flag1(word_t *p);                                  /* 408354 */
static word_t  sk_acc_identity(word_t v);                                    /* 408360 */
static word_t  sk_acc_get_10(word_t self);                                   /* 408374 */
static void    sk_acc_void_12(void);                                         /* 408380 */
static void    sk_acc_set_d8(word_t p, word_t v);                            /* 40838c */
static word_t  sk_acc_set_d8_get10(word_t p, word_t v, word_t self);         /* 4083a0 */
static void    sk_acc_void_13(void);                                         /* 4083b4 */
static word_t  sk_acc_const_ff(void);                                        /* 4083c0 */
static void    sk_acc_set_a8(word_t self, word_t v);                         /* 4083cc */
static void    sk_acc_void_14(void);                                         /* 4083d8 */
static word_t  sk_acc_const_100(void);                                       /* 4083e4 */
static sk_128_t sk_acc_add_stack(void);                                      /* 4083f0 */
static void    sk_acc_void_15(void);                                         /* 408404 */
static word_t  sk_acc_add_2(void);                                           /* 408410 */
static void    sk_acc_void_16(void);                                         /* 40841c */
static sk_128_t sk_acc_zero(void);                                           /* 408428 */
static void    sk_acc_void_17(void);                                         /* 408434 */
static sk_128_t sk_acc_add_stack2(void);                                     /* 408440 */
static void    sk_acc_set_68(word_t self, word_t v);                         /* 408454 */
static void    sk_acc_void_18(void);                                         /* 408460 */
static void    sk_acc_void_19(void);                                         /* 40846c */
static void    sk_acc_void_20(void);                                         /* 408488 */
static void    sk_acc_void_21(void);                                         /* 4084a4 */
static void    sk_printf_log(void);                                          /* 4084c0 */
static void    sk_unreachable_thunk(void);                                   /* 4084d4 */
static void    sk_log2(void);                                                /* 4084e8 */
static void    sk_async_arg_call(word_t self);                               /* 4084fc */
static void    sk_swift_retain_xor(word_t p, word_t v);                      /* 408510 */
static void    sk_string_cache_fixed(void);                                  /* 408524 */
static void    sk_string_conv_ff(void);                                      /* 408538 */
static void    sk_trace_self(void);                                          /* 40854c */
static void    sk_async_arg2_call(word_t self);                              /* 408560 */
static void    sk_swift_retain_field30(word_t self);                         /* 408574 */
static void    sk_acc_set_98(word_t self, word_t v);                         /* 408588 */
static void    sk_alloc_align16(word_t p);                                   /* 40859c */
static void    sk_unreachable_thunk2(void);                                  /* 4085a8 */
static void    sk_string_conv_none(void);                                    /* 4085b4 */
static void    sk_err_reply_build(word_t obj);                               /* 4085c0 */
static void    sk_err_set_perm(word_t arg);                                  /* 408784 */
static void    sk_err_clear_perm(word_t arg);                                /* 4087cc */
static word_t  sk_err_op_get(void);                                          /* 40880c */
static word_t  sk_err_op_take(void);                                         /* 408834 */
static word_t  sk_err_op_swap(word_t arg);                                   /* 408864 */
static word_t  sk_err_op_none(void);                                         /* 408898 */
static void    sk_err_op_clear(void);                                        /* 4088a0 */
static void    sk_drace_check(void);                                         /* 4088d8 */
static void    sk_drace_msg_build(word_t *out);                              /* 408a3c */
static void    sk_err_reply_dispose(word_t obj, word_t r, word_t r3);        /* 408ae4 */
static void    sk_l4_once_dispatch(word_t a, word_t b);                      /* 408bdc */
static word_t  sk_cmp_try(word_t a, word_t b, word_t flags);                 /* 408c4c */
static void    sk_future_resume(word_t a, word_t b, word_t c);               /* 408db8 */
static void    sk_ref_dec(word_t *p);                                        /* 4090f0 */
static void    sk_drace_handle(word_t *out);                                 /* 409150 */
static void    sk_drace_mode_set(void);                                      /* 409180 */
static void    sk_drace_mode_set2(void);                                     /* 409184 */
static void    sk_job_timer_set(word_t v, word_t *out, int on);              /* 4091ac */
static word_t  sk_job_self_ptr(word_t p);                                    /* 409210 */
static word_t  sk_job_size(void);                                            /* 409218 */
static word_t  sk_job_send(word_t *p, word_t a, word_t b);                   /* 409220 */
static word_t  sk_job_send2(word_t *p, word_t a, word_t b);                  /* 409224 */
static void    sk_clock_resolve(word_t *a, word_t *b, int id);               /* 409248 */
static void    sk_clock_resolve2(word_t *a, word_t *b, int id);              /* 4092d8 */
static void    sk_rt_dispatch0(word_t a);                                    /* 409354 */
static void    sk_rt_dispatch1(word_t a, word_t b);                          /* 409384 */
static void    sk_rt_dispatch2(word_t a, word_t b);                          /* 4093b4 */
static void    sk_rt_dispatch3(void);                                        /* 409414 */
static word_t  sk_rt_dispatch4(word_t a, word_t b);                          /* 409444 */
static word_t  sk_isolating_or_flags(word_t p);                              /* 409484 */
static void    sk_assert_isolating(int v);                                   /* 40949c */
static word_t  sk_cmp_try2(word_t *p);                                       /* 4094c8 */
static void    sk_l4_once_init2(void);                                       /* 4094ec */
static void    sk_job_kind_dispatch(word_t *p);                              /* 409540 */
static word_t  sk_run_job(word_t self, word_t job, word_t *out, word_t a4,
                          word_t a5, word_t a6);                             /* 4095a0 */
static sk_128_t sk_future_get(word_t p);                                      /* 4097cc */
static void    sk_job_teardown(word_t p);                                    /* 409818 */
static void    sk_job_teardown2(word_t p);                                   /* 40981c */
static void    sk_job_state_set(word_t p);                                   /* 409858 */
static void    sk_job_enqueue(word_t self, word_t job);                      /* 4098c8 */
static word_t  sk_job_destroy(word_t p);                                     /* 4099d4 */
static word_t  sk_combined_read(word_t p);                                   /* 409a34 */
static void    sk_job_copy_state(word_t *d, word_t *s, word_t *t);           /* 409a54 */
static void    sk_job_release(void);                                         /* 409b14 */
static void    sk_job_release2(void);                                        /* 409b18 */
static word_t  sk_job_flags(word_t p);                                       /* 409c10 */
static word_t  sk_job_field_98(word_t p);                                    /* 409c1c */
static void    sk_run_inline(word_t out, int *desc, word_t a3, word_t a4);   /* 409c24 */
static void    sk_noop(void);                                                /* 409e14 */
static sk_128_t sk_job_build(word_t flags, uint8_t *desc, word_t a3,
                             word_t a4, word_t a5, word_t a6);               /* 409e90 */
static void    sk_invoke(word_t a, word_t job, word_t cb, word_t a4);        /* 40a530 */
static word_t  sk_job_is_error(word_t p);                                    /* 40a688 */
static void    sk_l4_log0(word_t a);                                         /* 40a694 */
static void    sk_invoke_future(word_t a, word_t job, word_t cb, word_t a4); /* 40a6c0 */
static void    sk_job_state_set2(word_t p);                                  /* 40a7f0 */
static void    sk_job_state_set3(word_t p, word_t v);                        /* 40a860 */
static word_t *sk_job_alloc(word_t a, word_t b);                             /* 40a8d8 */
static void    sk_job_check_cancel(word_t p);                                /* 40a9b0 */
static word_t *sk_job_alloc2(word_t a, word_t b);                            /* 40a9f4 */

/* ======================================================================
 * Stored-property accessor witnesses (Swift). self lives in unaff_x22 /
 * unaff_x19 / unaff_x21; most are getters, setters, or empty protocol
 * witnesses. Faithful but low confidence on the object identity.
 * ==================================================================== */

/* FUN_004081cc @ 0x004081cc — L4 init call: forwards a global (DAT_005a01bc)
 * to the L4 boot/init helper FUN_0040bb18. Confidence: low. */
static void sk_l4_init_call(word_t g)
{
    sk_alloc(g); /* FUN_0040bb18(DAT_005a01bc) */
}

/* FUN_004081d8 @ 0x004081d8 — getter: field at self+0x90. */
static word_t sk_acc_get_90(word_t self)
{
    return *(word_t *)(self + 0x90);
}

/* FUN_004081e4 @ 0x004081e4 — empty protocol witness. */
static void sk_acc_void_1(void) { }

/* FUN_004081f0 @ 0x004081f0 — empty protocol witness. */
static void sk_acc_void_2(void) { }

/* FUN_004081fc @ 0x004081fc — empty protocol witness. */
static void sk_acc_void_3(void) { }

/* FUN_00408210 @ 0x00408210 — getter returning pair {+0x38, +0x50}. */
static sk_128_t sk_acc_get_3850(word_t self)
{
    sk_128_t r;
    r.lo = *(word_t *)(self + 0x38);
    r.hi = *(word_t *)(self + 0x50);
    return r;
}

/* FUN_00408224 @ 0x00408224 — multi-field setter: writes self1+0x20/0x28
 * and self2+0x10/0x18/0x20 from the register/stack arguments. */
static void sk_acc_set_multi(word_t a, word_t v)
{
    word_t self1 = a;                 /* unaff_x19 */
    word_t v2 = v;                    /* unaff_x20 */
    word_t self2 = 0;                 /* unaff_x23 */
    word_t s0 = 0, s8 = 0, s16 = 0;   /* in_stack_00000000/08/10 */

    *(word_t *)(self1 + 0x20) = v2;
    *(word_t *)(self1 + 0x28) = a;
    *(word_t *)(self2 + 0x10) = s16;
    *(word_t *)(self2 + 0x20) = s8;
    *(word_t *)(self2 + 0x18) = s0;
}

/* FUN_00408238 @ 0x00408238, FUN_00408244 @ 0x00408244, FUN_00408258 @ 0x00408258
 * — empty protocol witnesses (byte-identical). */
static void sk_acc_void_4(void) { }
static void sk_acc_void_5(void) { }
static void sk_acc_void_6(void) { }

/* FUN_0040826c @ 0x0040826c — getter pair {+0xa0, +0x90}. */
static sk_128_t sk_acc_get_a090(word_t self)
{
    sk_128_t r;
    r.lo = *(word_t *)(self + 0xa0);
    r.hi = *(word_t *)(self + 0x90);
    return r;
}

/* FUN_00408280 @ 0x00408280 — getter pair {+0x60, +0x38}. */
static sk_128_t sk_acc_get_6038(word_t self)
{
    sk_128_t r;
    r.lo = *(word_t *)(self + 0x60);
    r.hi = *(word_t *)(self + 0x38);
    return r;
}

/* FUN_00408294 @ 0x00408294, FUN_004082a8 @ 0x004082a8, FUN_004082b4 @ 0x004082b4
 * — empty protocol witnesses (byte-identical). */
static void sk_acc_void_7(void) { }
static void sk_acc_void_8(void) { }
static void sk_acc_void_9(void) { }

/* FUN_004082c8 @ 0x004082c8 — setter: byte at self+0x10 = in_w8. */
static void sk_acc_set_byte10(word_t self, uint8_t v)
{
    *(uint8_t *)(self + 0x10) = v;
}

/* FUN_004082d4 @ 0x004082d4 — setter: *self = v. */
static void sk_acc_set_slot0(word_t *self, word_t v)
{
    *self = v;
}

/* FUN_004082e0 @ 0x004082e0 — copy 2 bytes from src+0x10 to dst+0x10. */
static void sk_acc_copy2(word_t dst, word_t src)
{
    *(uint8_t *)(dst + 0x10) = *(uint8_t *)(src + 0x10);
    *(uint8_t *)(dst + 0x11) = *(uint8_t *)(src + 0x11);
}

/* FUN_00408308 @ 0x00408308 — setter: self+0x40 = src+0x18. */
static void sk_acc_set_40(word_t self, word_t v)
{
    *(word_t *)(self + 0x40) = *(word_t *)(v + 0x18);
}

/* FUN_00408314 @ 0x00408314 — empty protocol witness. */
static void sk_acc_void_10(void) { }

/* FUN_00408328 @ 0x00408328 — setter: self+0xb0 = v, self+0xb8 = src+0x28. */
static void sk_acc_set_b0(word_t self, word_t v)
{
    word_t src = 0; /* unaff_x24 */
    *(word_t *)(self + 0xb0) = v;
    *(word_t *)(self + 0xb8) = *(word_t *)(src + 0x28);
}

/* FUN_0040833c @ 0x0040833c — empty protocol witness. */
static void sk_acc_void_11(void) { }

/* FUN_00408348 @ 0x00408348 — getter pair {+0x80, +0x70}. */
static sk_128_t sk_acc_get_8070(word_t self)
{
    sk_128_t r;
    r.lo = *(word_t *)(self + 0x80);
    r.hi = *(word_t *)(self + 0x70);
    return r;
}

/* FUN_00408354 @ 0x00408354 — setter: *p = 1. */
static void sk_acc_set_flag1(word_t *p)
{
    *p = 1;
}

/* FUN_00408360 @ 0x00408360 — identity function. */
static word_t sk_acc_identity(word_t v)
{
    return v;
}

/* FUN_00408374 @ 0x00408374 — getter: self+0x10. */
static word_t sk_acc_get_10(word_t self)
{
    return *(word_t *)(self + 0x10);
}

static void sk_acc_void_12(void) { }

/* FUN_0040838c @ 0x0040838c — setter: p+8 = in_x16. */
static void sk_acc_set_d8(word_t p, word_t v)
{
    *(word_t *)(p + 8) = v;
}

/* FUN_004083a0 @ 0x004083a0 — setter p+8 = v, then getter self+0x10. */
static word_t sk_acc_set_d8_get10(word_t p, word_t v, word_t self)
{
    *(word_t *)(p + 8) = v;
    return *(word_t *)(self + 0x10);
}

/* FUN_004083b4 @ 0x004083b4 — empty protocol witness. */
static void sk_acc_void_13(void) { }

/* FUN_004083c0 @ 0x004083c0 — constant 0xff. */
static word_t sk_acc_const_ff(void) { return 0xff; }

/* FUN_004083cc @ 0x004083cc — setter: self+0xa8 = v. */
static void sk_acc_set_a8(word_t self, word_t v)
{
    *(word_t *)(self + 0xa8) = v;
}

/* FUN_004083d8 @ 0x004083d8 — empty protocol witness. */
static void sk_acc_void_14(void) { }

/* FUN_004083e4 @ 0x004083e4 — constant 0x100. */
static word_t sk_acc_const_100(void) { return 0x100; }

/* FUN_004083f0 @ 0x004083f0 — pair: lo = x28+x26, hi = in_stack_00000018. */
static sk_128_t sk_acc_add_stack(void)
{
    sk_128_t r;
    r.lo = 0; /* unaff_x28 + unaff_x26 */
    r.hi = 0; /* in_stack_00000018 */
    return r;
}

/* FUN_00408404 @ 0x00408404 — empty protocol witness. */
static void sk_acc_void_15(void) { }

/* FUN_00408410 @ 0x00408410 — sum x27 + x25. */
static word_t sk_acc_add_2(void)
{
    return 0; /* unaff_x27 + unaff_x25 */
}

/* FUN_0040841c @ 0x0040841c — empty protocol witness. */
static void sk_acc_void_16(void) { }

/* FUN_00408428 @ 0x00408428 — zero 128-bit pair. */
static sk_128_t sk_acc_zero(void) { return sk_128_zero(); }

/* FUN_00408434 @ 0x00408434 — empty protocol witness. */
static void sk_acc_void_17(void) { }

/* FUN_00408440 @ 0x00408440 — pair: lo = x21+x26, hi = in_stack_00000008. */
static sk_128_t sk_acc_add_stack2(void)
{
    sk_128_t r;
    r.lo = 0; /* unaff_x21 + unaff_x26 */
    r.hi = 0; /* in_stack_00000008 */
    return r;
}

/* FUN_00408454 @ 0x00408454 — setter: self+0x68 = v. */
static void sk_acc_set_68(word_t self, word_t v)
{
    *(word_t *)(self + 0x68) = v;
}

/* FUN_00408460 @ 0x00408460, FUN_0040846c @ 0x0040846c,
 * FUN_00408488 @ 0x00408488, FUN_004084a4 @ 0x004084a4
 * — empty protocol witnesses (byte-identical). */
static void sk_acc_void_18(void) { }
static void sk_acc_void_19(void) { }
static void sk_acc_void_20(void) { }
static void sk_acc_void_21(void) { }

/* FUN_004084c0 @ 0x004084c0 — printf log helper FUN_003f540c(). */
static void sk_printf_log(void)
{
    sk_printf((word_t)0); /* FUN_003f540c() */
}

/* FUN_004084d4 @ 0x004084d4 — unconditional unreachable (FUN_001afa84). */
static void sk_unreachable_thunk(void)
{
    sk_unreachable(); /* FUN_001afa84() — does not return */
}

/* FUN_004084e8 @ 0x004084e8 — log helper FUN_003f6278(). */
static void sk_log2(void)
{
    sk_log((word_t)0); /* FUN_003f6278() */
}

/* FUN_004084fc @ 0x004084fc — passes self+0xa0 to FUN_0040bd24 (free). */
static void sk_async_arg_call(word_t self)
{
    sk_free(*(word_t *)(self + 0xa0)); /* FUN_0040bd24(self+0xa0) */
}

/* FUN_00408510 @ 0x00408510 — store v into *self then retain a masked
 * pointer (param_1+0x10 with bits cleared). */
static void sk_swift_retain_xor(word_t p, word_t v)
{
    word_t *self = (word_t *)p;
    *self = v;
    sk_swift_retain(p + 0x10 & ~p); /* FUN_0036b270 */
}

/* FUN_00408524 @ 0x00408524 — string cache (FUN_00002534) with fixed args. */
static void sk_string_cache_fixed(void)
{
    sk_string_cache(0x6562b0, 0x005a1700); /* DAT_005a1700 */
}

/* FUN_00408538 @ 0x00408538 — string convert (FUN_00377824) with 0xff. */
static void sk_string_conv_ff(void)
{
    sk_string_conv(0xff); /* FUN_00377824 */
}

/* FUN_0040854c @ 0x0040854c — trace helper FUN_00251638(). */
static void sk_trace_self(void)
{
    sk_trace((word_t)0); /* FUN_00251638() */
}

/* FUN_00408560 @ 0x00408560 — FUN_0040cfec(self+0x10, self+0x130). */
static void sk_async_arg2_call(word_t self)
{
    sk_async_arg(self + 0x10, *(word_t *)(self + 0x130)); /* FUN_0040cfec */
}

/* FUN_00408574 @ 0x00408574 — retain self+0x30 (FUN_0036b270). */
static void sk_swift_retain_field30(word_t self)
{
    sk_swift_retain(*(word_t *)(self + 0x30)); /* thunk_FUN_0036b270 */
}

/* FUN_00408588 @ 0x00408588 — setter self+0x98 = v, then
 * FUN_00377dcc(0, self+0x88). */
static void sk_acc_set_98(word_t self, word_t v)
{
    *(word_t *)(self + 0x98) = v;
    sk_string_conv2(0, *(word_t *)(self + 0x88)); /* FUN_00377dcc */
}

/* FUN_0040859c @ 0x0040859c — FUN_0040bb18(p & ~0xf) (16-align alloc). */
static void sk_alloc_align16(word_t p)
{
    sk_alloc(p + 0xf & ~(word_t)0xf); /* FUN_0040bb18(p+0xf & 0xfffffffffffffff0) */
}

/* FUN_004085a8 @ 0x004085a8 — unconditional unreachable. */
static void sk_unreachable_thunk2(void)
{
    sk_unreachable(); /* FUN_001afa84() — does not return */
}

/* FUN_004085b4 @ 0x004085b4 — string convert FUN_00377824(). */
static void sk_string_conv_none(void)
{
    sk_string_conv((word_t)0); /* FUN_00377824() */
}

/* ======================================================================
 * L4 error-code reply machinery + job status state machine.
 * ==================================================================== */

/* FUN_004085c0 @ 0x004085c0 — l4_error_reply_build (est.)
 * Builds/commits an L4 error reply on the given object. If the object is
 * absent or already in a failed state (obj+0x20 != 0), it pushes a
 * PermissionInvalid error slot and invokes the object's callback (+0x38).
 * Otherwise it pushes an OperationInvalid error slot, retargets the object's
 * error slot to the object itself, and runs the double-word compare-exchange
 * that ORs the finalised bit (0x800) into the status word at +0x68 (with a
 * slow path through FUN_0040c0f8/FUN_0040bda0 when the high bit is already
 * set). Confidence: medium. */
static void sk_err_reply_build(word_t obj)
{
    word_t *slot;
    word_t lv, lw;          /* double-word CAS accumulators */
    word_t t0, t1;
    word_t hi, lo;

    if (obj == 0 || *(char *)(obj + 0x20) != '\0') {
        /* PermissionInvalid path. */
        slot = (word_t *)((word_t(*)(void))sk_l4_err_perm[1])();
        lo = *slot;
        *(word_t *)(obj + 0x28) = (word_t)-1;
        if ((*(uint8_t *)(lo + 0x30) & 1) == 0) {
            *(word_t *)(lo + 0x28) = 0;
            *(uint8_t *)(lo + 0x30) = 1;
        }
        (*(void(**)(word_t))(obj + 0x38))(obj);
    } else {
        /* OperationInvalid path: set the error slot to obj itself. */
        slot = (word_t *)((word_t(*)(void))sk_l4_err_op[1])();
        lo = *slot;
        *slot = obj;
        hi = *(word_t *)(obj + 0x60);
        lo = *(word_t *)(obj + 0x68);
        if (((uint32_t)hi >> 0xe & 1) == 0) {
            word_t w1 = *(word_t *)(obj + 0x60);
            word_t w2 = *(word_t *)(obj + 0x68);
            if ((w1 == lo) && (w2 == hi)) {
                *(word_t *)(obj + 0x60) = lo;
                *(word_t *)(obj + 0x68) = (word_t)((uint32_t)hi & 0xffffa3ff | 0x800);
            }
            if (w1 != hi || w2 != lo) {
                do {
                    t0 = *(word_t *)(obj + 0x60);
                    t1 = *(word_t *)(obj + 0x68);
                    if ((t0 == w2) && (t1 == w1)) {
                        *(word_t *)(obj + 0x60) = w2;
                        *(word_t *)(obj + 0x68) = (word_t)((uint32_t)w1 & 0xffffe3ff | 0x800);
                    }
                    w1 = t0;
                    w2 = t1;
                } while (t0 != hi || t1 != lo);
            }
        } else {
            word_t u = *(word_t *)(obj + 0xa0);
            word_t stk = 0;
            sk_128_save(obj, u, (word_t)(uintptr_t)&hi, (word_t)0); /* FUN_0040c0f8 */
            sk_128_load(obj, u);                    /* FUN_0040bda0 */
            *(word_t *)(obj + 0xa0) = 0;
        }
        slot = (word_t *)((word_t(*)(void))sk_l4_err_perm[1])();
        lv = *slot;
        *(word_t *)(obj + 0x28) = (word_t)-1;
        if ((*(uint8_t *)(lv + 0x30) & 1) == 0) {
            *(word_t *)(lv + 0x28) = 0;
            *(uint8_t *)(lv + 0x30) = 1;
        }
        sk_swift_array_destroy(obj + 0x50);         /* FUN_0036a244 */
        (*(void(**)(void))(obj + 0x38))();
        if (lo != 0) {
            *slot = lo;
        }
    }
}

/* FUN_00408784 @ 0x00408784 — sk_err_set_perm: allocates a PermissionInvalid
 * error slot (FUN via sk_l4_err_perm[1]) and arms its failure flag. */
static void sk_err_set_perm(word_t arg)
{
    word_t *slot;
    word_t p;
    word_t f;

    slot = (word_t *)((word_t(*)(word_t))sk_l4_err_perm[1])(arg);
    f = *slot;
    *(word_t *)(arg + 0x28) = (word_t)-1;
    if ((*(uint8_t *)(f + 0x30) & 1) == 0) {
        *(word_t *)(f + 0x28) = 0;
        *(uint8_t *)(f + 0x30) = 1;
    }
}

/* FUN_004087cc @ 0x004087cc — sk_err_clear_perm: allocates a PermissionInvalid
 * slot and clears its failure flag; panics (SoftwareBreakpoint 0x40880c) if
 * the flag is already clear. */
static void sk_err_clear_perm(word_t arg)
{
    word_t *slot;
    word_t f;

    slot = (word_t *)((word_t(*)(word_t))sk_l4_err_perm[1])(arg);
    f = *slot;
    if ((*(uint8_t *)(f + 0x30) & 1) != 0) {
        *(word_t *)(arg + 0x28) = 0;
        *(uint8_t *)(f + 0x30) = 0;
        return;
    }
    SK188_BKPT(0x40880c); /* SoftwareBreakpoint(1,0x40880c) — does not return */
}

/* FUN_0040880c @ 0x0040880c — sk_err_op_get: returns the current
 * OperationInvalid error slot. */
static word_t sk_err_op_get(void)
{
    word_t *slot = (word_t *)((word_t(*)(void))sk_l4_err_op[1])();
    return *slot;
}

/* FUN_00408834 @ 0x00408834 — sk_err_op_take: returns and clears the current
 * OperationInvalid error slot. */
static word_t sk_err_op_take(void)
{
    word_t *slot = (word_t *)((word_t(*)(void))sk_l4_err_op[1])();
    word_t v = *slot;
    *slot = 0;
    return v;
}

/* FUN_00408864 @ 0x00408864 — sk_err_op_swap: returns the current
 * OperationInvalid slot and replaces it with arg. */
static word_t sk_err_op_swap(word_t arg)
{
    word_t *slot = (word_t *)((word_t(*)(word_t))sk_l4_err_op[1])(arg);
    word_t v = *slot;
    *slot = arg;
    return v;
}

/* FUN_00408898 @ 0x00408898 — sk_err_op_none: constant 0 (no error). */
static word_t sk_err_op_none(void) { return 0; }

/* FUN_004088a0 @ 0x004088a0 — sk_err_op_clear: clears the OperationInvalid
 * slot if set (via FUN_0040c5d8). */
static void sk_err_op_clear(void)
{
    word_t *slot = (word_t *)((word_t(*)(void))sk_l4_err_op[1])();
    if (*slot != 0) {
        sk_job_clean((word_t)0); /* FUN_0040c5d8 */
    }
}

/* FUN_004088d8 @ 0x004088d8 — sk_drace_check: Swift data-race-detector
 * runtime. Runs a once-init on the token at 0x006c0b90 (FUN_003d3dd8) with
 * FUN_00408a38 as the init, then if the detector mode (0x006c0b88) is active
 * performs a data-race check: builds a "data race detected" message, calls
 * FUN_00369b0c, and if nonzero installs a raw-instruction trampoline
 * (Ghidra renders the 16 bytes as the constants 0x3900012a528005ca,
 * 0x54000643fa4d3120, ...) via FUN_00369b04; finally emits the trace
 * (FUN_0011883c/FUN_0011858c with tag 0xeb1a02bf914012ba), frees the message
 * (thunk_FUN_00012568), and if the detector is in the "first" mode panics
 * via FUN_00116d60. Confidence: low (instruction-patching path). */
static void sk_drace_check(void)
{
    bool first;
    int chk;
    word_t msg = 0;
    word_t a4 = 0, a5 = 0;
    word_t w[8];

    if (-1 < sk_drace_once90) {
        sk_rt_once((word_t)(uintptr_t)&sk_drace_once90, (word_t)0x00408a38, (word_t)0);
        /* FUN_003d3dd8(&DAT_006c0b90,&DAT_00408a38,0) */
    }
    if (sk_drace_mode != 0) {
        first = sk_drace_mode != 1;
        (void)sk_cmp_try2(&a4);       /* FUN_004094c8(&local_40) */
        sk_drace_msg_build(&msg);     /* FUN_00408a3c(&local_48) */
        chk = (int)sk_drace_check2((word_t)0);  /* FUN_00369b0c() */
        if (chk != 0) {
            w[0] = 0x3900012a528005ca;  /* raw instruction word (trampoline) */
            w[1] = 0x54000643fa4d3120;
            w[2] = 0x540003e26b16015f;
            w[3] = 0x1100052ab9400289;
            w[4] = 0xfa4d3120eb0a013f;
            w[5] = 0x8b2941a98b3641aa;
            w[6] = 0x39400108540004e3;
            w[7] = 0x540001426b16017f;
            sk_drace_install(first, msg, (word_t)w); /* thunk_FUN_00369b04(bVar1,local_48,&local_a0) */
        }
        sk_str_emit(msg, 0xeb1a02bf914012ba);   /* FUN_0011883c */
        sk_str_emit2(0xeb1a02bf914012ba);        /* FUN_0011858c */
        sk_heap_free(msg);                       /* thunk_FUN_00012568 */
        if (first) {
            sk_fatal2();                         /* FUN_00116d60 — does not return */
        }
    }
}

/* FUN_00408a3c @ 0x00408a3c — sk_drace_msg_build: builds a
 * "data race detected ... at ..." message string (0x005dc6ba) through
 * FUN_00116bb4 with optional heap allocation (FUN_000101a0) and free
 * (thunk_FUN_00012568); stores the result in *out (0 on failure). */
static void sk_drace_msg_build(word_t *out)
{
    int r;
    word_t p;

    r = (int)sk_str_format(0, 0, 0x005dc6ba, 0); /* FUN_00116bb4(0,0,s__s__data_race_detected___s_at____005dc6ba,&stack) */
    *out = 0;
    if (-1 < r) {
        p = sk_alloc_pool(r + 1, 0x100004077774924); /* FUN_000101a0 */
        if (p != 0) {
            r = (int)sk_str_format(p, r + 1, 0x005dc6ba, 0); /* FUN_00116bb4 */
            if (r < 0) {
                sk_heap_free(p);  /* thunk_FUN_00012568 */
            } else {
                *out = p;
            }
        }
    }
}

/* FUN_00408ae4 @ 0x00408ae4 — sk_err_reply_dispose: installs the L4 error
 * reply frame (param_2/param_3) into the PermissionInvalid slot, runs
 * sk_err_reply_build(param_1) to commit the reply, then restores the slot;
 * if the frame was retained (param_2 != 0, param_3 == 0) releases the object
 * via FUN_0037a978 + sk_ref_dec. Confidence: medium. */
static void sk_err_reply_dispose(word_t obj, word_t r, word_t r3)
{
    word_t saved;
    word_t *slot;
    word_t frame[2];
    word_t lv;

    char f1 = 1;   /* local_50 */
    char f2 = 0;   /* local_48 */
    char f3 = 0;   /* local_40 */
    sk_128_t c128 = sk_128_zero(); /* local_60 */

    if (r == 0) {
        if (obj == 0) {
            c128 = sk_128_zero();
        } else {
            c128 = sk_128_zero();
            if (*(char *)(obj + 0x20) == '\0') {
                c128 = sk_copy128(obj, 0); /* FUN_0040c2d8(obj,0) */
            }
        }
    } else {
        c128 = sk_128_zero();
        f1 = 0;
    }
    frame[0] = r;
    frame[1] = r3;
    slot = (word_t *)((word_t(*)(void))sk_l4_err_perm[1])();
    saved = *slot;
    *slot = (word_t)frame;
    sk_err_reply_build(obj); /* FUN_004085c0 */
    lv = frame[0];
    if (f3 == 1) {
        f3 = 0;
    }
    *slot = saved;
    if ((f1 == 1) && (frame[0] != 0) && (r3 == 0)) {
        sk_lock_release(frame[0] + 0x20);  /* FUN_0037a978 */
        sk_ref_dec((word_t *)lv);          /* FUN_004090f0 */
    }
}

/* FUN_00408bdc @ 0x00408bdc — sk_l4_once_dispatch: runs the once-init on
 * 0x006c0ba0 (init FUN_00409150, key 0x006c0b98) then calls
 * sk_cmp_try(a, b, hook). */
static void sk_l4_once_dispatch(word_t a, word_t b)
{
    if (-1 < sk_drace_oncea0) {
        sk_rt_once((word_t)(uintptr_t)&sk_drace_oncea0, (word_t)(uintptr_t)sk_drace_handle,
                   (word_t)(uintptr_t)&sk_drace_hook98);
        /* FUN_003d3dd8(&DAT_006c0ba0,FUN_00409150,&DAT_006c0b98) */
    }
    sk_cmp_try(a, b, (word_t)sk_drace_hook98); /* FUN_00408c4c(a,b,_DAT_006c0b98) */
}

/* FUN_00408c4c @ 0x00408c4c — sk_cmp_try: object-compare-and-try against a
 * fresh frame. Returns 1 on success/merge, 0 on failure. Follows the
 * PermissionInvalid slot: if empty, does a raw compare (FUN_004094c8) and on
 * mismatch falls to sk_rt_dispatch2 (FUN_004093b4); if non-empty, compares
 * the stored frame, applies the bit-3 flag rules, and on the merge path uses
 * FUN_003a25b8/FUN_003d5284, then byte-copies the PermissionInvalid global
 * and returns 1. Confidence: medium. */
static word_t sk_cmp_try(word_t a, word_t b, word_t flags)
{
    word_t *slot;
    word_t f0, f1;
    word_t lv;
    int r;
    word_t res;

    word_t la = a;  /* local_40 */
    word_t lb = b;  /* local_38 */

    slot = (word_t *)((word_t(*)(word_t))sk_l4_err_perm[1])(a);
    slot = (word_t *)*slot;
    if (slot == (word_t *)0) {
        r = (int)sk_cmp_try2(&la); /* FUN_004094c8 */
        if (r == 0) goto cmp_fallback;
        res = sk_obj_none((word_t)0); /* FUN_003d3dac */
    } else {
        f1 = slot[1];
        f0 = *slot;
        if (*slot == (word_t)0) {
            return 1;
        }
        r = (int)sk_cmp_try2(&f0); /* FUN_004094c8 */
        if ((r != 0) && ((sk_cmp_try2(&la) & 1) != 0)) {
            return 1;
        }
        if ((flags >> 3 & 1) == 0) {
            r = (int)sk_cmp_try2(&la);
            if ((r != 0) && ((int)sk_cmp_try2(&f0) == 0)) {
                return sk_cmp_try2(&f0);
            }
            res = sk_cmp_try2(&la);
            if (((res & 1) == 0) && ((sk_cmp_try2(&f0) & 1) != 0)) {
                return 0;
            }
        }
        if (((lb & 7) != 1) || (f0 == 0) || (f1 == 0) || (la == 0)) goto cmp_fallback;
        res = sk_str_cmp(f1 & ~(word_t)7, lb & ~(word_t)7); /* FUN_00377ca8 */
        if ((res & 1) == 0) goto cmp_fallback;
        lv = sk_identity_hash(f0);  /* FUN_003a25b8 */
        res = sk_obj_merge(f0, la, lv, lb & ~(word_t)7); /* FUN_003d5284 */
    }
    if ((res & 1) != 0) {
        /* byte-copy the PermissionInvalid global's fn-ptr word into itself
         * (Ghidra: s_L4_ErrorCodePermissionInvalid[8..0xf] = bytes of _8_8_). */
        ((volatile uint8_t *)sk_l4_err_perm)[8]  = (uint8_t)(sk_l4_err_perm[1] >> 0);
        ((volatile uint8_t *)sk_l4_err_perm)[9]  = (uint8_t)(sk_l4_err_perm[1] >> 8);
        ((volatile uint8_t *)sk_l4_err_perm)[10] = (uint8_t)(sk_l4_err_perm[1] >> 16);
        ((volatile uint8_t *)sk_l4_err_perm)[11] = (uint8_t)(sk_l4_err_perm[1] >> 24);
        ((volatile uint8_t *)sk_l4_err_perm)[12] = (uint8_t)(sk_l4_err_perm[1] >> 32);
        ((volatile uint8_t *)sk_l4_err_perm)[13] = (uint8_t)(sk_l4_err_perm[1] >> 40);
        ((volatile uint8_t *)sk_l4_err_perm)[14] = (uint8_t)(sk_l4_err_perm[1] >> 48);
        ((volatile uint8_t *)sk_l4_err_perm)[15] = (uint8_t)(sk_l4_err_perm[1] >> 56);
        return 1;
    }
cmp_fallback:
    sk_rt_dispatch2(la, lb);  /* FUN_004093b4 */
    res = sk_cmp_try2((word_t *)0); /* FUN_0040949c — assert helper */
    if ((int)res == 1) {
        return res;
    }
    if (((res & 0xff) != 0) && ((flags >> 3 & 1) != 0)) {
        sk_rt_dispatch1(la, lb); /* FUN_00409384 */
        return 1;
    }
    return 0;
}

/* FUN_00408db8 @ 0x00408db8 — sk_future_resume: resume/attach a future.
 * Allocates the OperationInvalid slot (with arg a), reads the current
 * PermissionInvalid slot triple (ptr/flag/ctx), and if the stored object
 * matches param_2 it returns early via the indirect vtable; otherwise it
 * writes the pending state into the future (obj+0x40/+0x38), refcounts
 * param_2 through FUN_0037a48c, and either stores the pair back into the
 * existing slot or allocates a new frame through the PermissionInvalid
 * callback chain. Ghidra loses the final indirect jump ("could not recover
 * jumptable"). Confidence: low. */
static void sk_future_resume(word_t a, word_t b, word_t c)
{
    word_t *slot_op;
    word_t *slot_perm;
    word_t s0, s1, s2;
    word_t lv;
    word_t *pl;
    word_t lv6;
    int rc;
    word_t stk;

    slot_op = (word_t *)((word_t(*)(word_t, word_t))sk_l4_err_op[1])((word_t)(uintptr_t)(sk_l4_err_op + 1), a);
    lv = *slot_op;
    slot_perm = (word_t *)((word_t(*)(void))sk_l4_err_perm[1])();
    pl = (word_t *)*slot_perm;
    if (pl == (word_t *)0) {
        s0 = 0; s1 = 0; s2 = 0;
    } else {
        s0 = *pl;
        s1 = pl[1];
        s2 = pl[2];
    }
    lv6 = sk_copy128(lv, 0).lo; /* FUN_0040c2d8 */
    if (s0 == b) {
        if (lv6 == s2) {
            /* early return through indirect vtable (unrecoverable jumptable) */
            (*(void(*)(void))slot_perm)();
            return;
        }
        {
            word_t v7 = (s2 == 0) ? sk_obj_merge2((word_t)0) : s2;  /* thunk_FUN_003d5138 */
            word_t v8 = (lv6 == 0) ? sk_obj_merge2((word_t)0) : lv6;
            if (v7 == v8) {
                (*(void(*)(void))slot_perm)();
                return;
            }
        }
    }
    *(word_t *)(lv + 0x40) = 0;   /* unaff_x22 */
    *(word_t *)(lv + 0x38) = (word_t)slot_perm;
    if ((s2 == 0) && (pl == (word_t *)0 || ((char)pl[4] == 1))) {
        if (s0 == 0) {
            if ((s1 & 7) != 2) goto store_pair;
        } else if (s1 != 0) goto store_pair;
        if (b == 0) goto after_ref;
        if (c == 0) {
            rc = *(int *)(b + 0x30);
            LOAcquire();
            *(int *)(b + 0x30) = rc + 1;
            sk_lock_acquire((word_t)0, b + 0x20); /* FUN_0037a48c(CONCAT44(word_t, ...),b+0x20) */
        }
after_ref:
        if (s0 != 0) {
            sk_lock_release(s0 + 0x20); /* FUN_0037a978 */
            sk_ref_dec((word_t *)s0);   /* FUN_004090f0 */
        }
        if (pl != (word_t *)0) {
            *pl = b;
            pl[1] = c;
            *(sk_128_t *)(pl + 2) = sk_copy128(lv, 0); /* FUN_0040c2d8 */
            (**(void(**)(word_t *))(lv + 0x38))((word_t *)(lv + 0x38));
            return;
        }
        {
            char f1 = 1, f2 = 0, f3 = 0;
            sk_128_t frm = sk_copy128(lv, 0); /* local_88 */
            stk = *slot_perm;
            *slot_perm = (word_t)&stk;
            *(word_t *)&stk = b;
            *(word_t *)((word_t)&stk + 8) = c;
            (**(void(**)(word_t *))(lv + 0x38))((word_t *)(lv + 0x38));
            lv = stk;
            if (f3 == 1) { f3 = 0; }
            *slot_perm = stk;
            if (stk == 0) return;
            if (c != 0) return;
            sk_lock_release(stk + 0x20); /* FUN_0037a978 */
            sk_ref_dec((word_t *)lv);    /* FUN_004090f0 */
        }
        return;
    }
store_pair:
    *slot_op = 0;
}

/* FUN_004090f0 @ 0x004090f0 — sk_ref_dec: decrements the refcount at
 * param_1[6]; at 1 it releases the lock (thunk_FUN_00053aa0 on param_1+4)
 * and frees the object through FUN_0036b6ac using its header's type
 * (*(uint *)(*param_1+0x18) / +0x1c). */
static void sk_ref_dec(word_t *p)
{
    int rc = (int)p[6];
    *(int *)(p + 6) = rc - 1;
    LORelease();
    if (rc == 1) {
        sk_lock_release((word_t)(p + 4));         /* thunk_FUN_00053aa0 */
        sk_swift_obj_free((word_t)p,
                          *(uint32_t *)(*p + 0x18),
                          *(uint16_t *)(*p + 0x1c)); /* FUN_0036b6ac */
    }
}

/* FUN_00409150 @ 0x00409150 — sk_drace_handle: if the data-race mode
 * (FUN_0035bdf8) is inactive, writes 8 into *out. */
static void sk_drace_handle(word_t *out)
{
    uint32_t m = (uint32_t)sk_drace_mode_get((word_t)0); /* FUN_0035bdf8 */
    if ((m & 1) == 0) {
        *out = 8;
    }
}

/* FUN_00409180 / 0x00409184 — sk_drace_mode_set / _set2: set the data-race
 * detector mode to 1, or 2 if FUN_0035bdf8() reports no race support. */
static void sk_drace_mode_set(void)
{
    int m = (int)sk_drace_mode_get((word_t)0); /* FUN_0035bdf8 */
    sk_drace_mode = 1;
    if (m == 0) { sk_drace_mode = 2; }
}
/* FUN_00409184 @ 0x00409184 — sk_drace_mode_set2 (byte-identical twin of 0x00409180). */
static void sk_drace_mode_set2(void)
{
    int m = (int)sk_drace_mode_get((word_t)0); /* FUN_0035bdf8 */
    sk_drace_mode = 1;
    if (m == 0) { sk_drace_mode = 2; }
}

/* FUN_004091ac @ 0x004091ac — sk_job_timer_set: fills a 4-word timer/job
 * descriptor (v, flags with bit pattern, size 8 or 0) and runs the
 * CAS callback FUN_00409220 via FUN_0040c09c. */
static void sk_job_timer_set(word_t v, word_t *out, int on)
{
    word_t s;
    word_t local;

    out[0] = 1;
    out[1] = 0;
    s = 8;
    if (on == 0) { s = 0; }
    out[2] = v;
    out[3] = s | v & ~(word_t)0xc;
    local = v;
    sk_cas_call((word_t)(uintptr_t)out, (word_t)(uintptr_t)sk_job_send,
                (word_t)(uintptr_t)&local); /* FUN_0040c09c */
}

/* FUN_00409210 @ 0x00409210 — sk_job_self_ptr: returns p + 0x50. */
static word_t sk_job_self_ptr(word_t p) { return p + 0x50; }

/* FUN_00409218 @ 0x00409218 — sk_job_size: constant 0x230. */
static word_t sk_job_size(void) { return 0x230; }

/* FUN_00409220 / 0x00409224 — sk_job_send / _send2: forward the stored
 * callback to FUN_0040c640(*p, a, b, 0) and return 1. */
static word_t sk_job_send(word_t *p, word_t a, word_t b)
{
    sk_cas_send(*(word_t *)*p, a, b, 0); /* FUN_0040c640 */
    return 1;
}
/* FUN_00409224 @ 0x00409224 — sk_job_send2 (byte-identical twin of 0x00409220). */
static word_t sk_job_send2(word_t *p, word_t a, word_t b)
{
    sk_cas_send(*(word_t *)*p, a, b, 0); /* FUN_0040c640 */
    return 1;
}

/* FUN_00409248 @ 0x00409248 — sk_clock_resolve: maps a clock ID to a clock
 * pair through FUN_0011825c; fatal (FUN_004ba640 "Fatal error: invalid clock
 * ID %d" 0x005dc751) on an unrecognised ID. */
static void sk_clock_resolve(word_t *a, word_t *b, int id)
{
    word_t clk;

    if (id == 3) {
        sk_clock_get(2, (word_t *)&clk); /* FUN_0011825c(2,&local_30) */
    } else if (id == 2) {
        sk_clock_get(1, (word_t *)&clk); /* FUN_0011825c(1,&local_40) */
        a = (word_t *)clk;
        b = (word_t *)(clk + 0); /* uStack_38 */
    } else if (id != 1) {
        sk_fatal(0, 0x005dc751); /* FUN_004ba640 — does not return */
    } else {
        sk_clock_get(1, (word_t *)&clk); /* FUN_0011825c(1,&local_30) */
    }
    *a = clk;
    *b = 0;
}

/* FUN_004092d8 @ 0x004092d8 — sk_clock_resolve2: same via FUN_001181b4. */
static void sk_clock_resolve2(word_t *a, word_t *b, int id)
{
    word_t clk;

    if (id == 3) {
        sk_clock_get2(2, (word_t *)&clk); /* FUN_001181b4(2,&local_30) */
    } else if ((id != 2) && (id != 1)) {
        sk_fatal(0, 0x005dc751); /* FUN_004ba640 — does not return */
    } else {
        sk_clock_get2(1, (word_t *)&clk); /* FUN_001181b4(1,&local_30) */
    }
    *a = clk;
    *b = 0;
}

/* ---- Indirect runtime dispatch thunks (jump through lazily installed
 * global function pointers; fall back to FUN_0040f9f4/FUN_0040fa5c/
 * FUN_0040faac/thunk_FUN_00019858 when not yet installed). ---- */

/* FUN_00409354 @ 0x00409354 — sk_rt_dispatch0. */
static void sk_rt_dispatch0(word_t a)
{
    if (sk_rt_dispatch_78 == 0) {
        sk_rt_is_isolated((word_t)0); /* FUN_003fc8a0 */
        return;
    }
    ((void(*)(word_t, word_t))sk_rt_dispatch_78)(a, 0x409380);
}

/* FUN_00409384 @ 0x00409384 — sk_rt_dispatch1. */
static void sk_rt_dispatch1(word_t a, word_t b)
{
    if (sk_rt_dispatch_80 == 0) {
        sk_rt_fallback_1((word_t)0); /* FUN_0040f9f4 */
        return;
    }
    ((void(*)(word_t, word_t, word_t))sk_rt_dispatch_80)(a, b, 0x4093b0);
}

/* FUN_004093b4 @ 0x004093b4 — sk_rt_dispatch2. */
static void sk_rt_dispatch2(word_t a, word_t b)
{
    if (sk_rt_dispatch_88 == 0) {
        sk_rt_fallback_2((word_t)0); /* FUN_0040fa5c */
        return;
    }
    ((void(*)(word_t, word_t, word_t))sk_rt_dispatch_88)(a, b, 0x4093e0);
}

/* FUN_00409414 @ 0x00409414 — sk_rt_dispatch3. */
static void sk_rt_dispatch3(void)
{
    if (sk_rt_dispatch_98 == 0) {
        sk_rt_fallback_4((word_t)0); /* thunk_FUN_00019858 */
        return;
    }
    ((void(*)(word_t))sk_rt_dispatch_98)(0x409440);
}

/* FUN_00409444 @ 0x00409444 — sk_rt_dispatch4. */
static word_t sk_rt_dispatch4(word_t a, word_t b)
{
    if (sk_rt_dispatch_a0 == 0) {
        sk_rt_fallback_3((word_t)0); /* FUN_0040faac */
        return 0;
    }
    return ((word_t(*)(word_t, word_t, word_t))sk_rt_dispatch_a0)(a, b, 0x409470);
}

/* FUN_00409484 @ 0x00409484 — sk_isolating_or_flags: if the object is valid
 * (non-null and obj+0x20 == 0) returns sk_job_destroy(obj), else returns the
 * low 32 bits of obj+0x24. */
static word_t sk_isolating_or_flags(word_t p)
{
    if ((p != 0) && (*(char *)(p + 0x20) == '\0')) {
        return sk_combined_read(p); /* FUN_00409a34 */
    }
    return (word_t)*(uint32_t *)(p + 0x24);
}

/* FUN_0040949c @ 0x0040949c — sk_assert_isolating: fatal
 * (FUN_004ba640, "Unexpected IsIsolatingCurrentCon..." 0x005dc773) unless
 * v+1 < 3. */
static void sk_assert_isolating(int v)
{
    if ((unsigned)(v + 1) < 3) {
        return;
    }
    sk_fatal(0, 0x005dc773); /* FUN_004ba640 — does not return */
}

/* FUN_004094c8 @ 0x004094c8 — sk_cmp_try2: runs sk_rt_dispatch4 on the two
 * words of *p and returns the low bit. */
static word_t sk_cmp_try2(word_t *p)
{
    uint32_t r = (uint32_t)sk_rt_dispatch4(p[0], p[1]); /* FUN_00409444 */
    return r & 1;
}

/* FUN_004094ec @ 0x004094ec — sk_l4_once_init2: once-init on 0x006c0ba8
 * (init FUN_0040953c, key FUN_003d5058). */
static void sk_l4_once_init2(void)
{
    if (-1 < sk_drace_oncea8) {
        sk_rt_once((word_t)(uintptr_t)&sk_drace_oncea8, (word_t)0x0040953c, (word_t)0x003d5058);
        /* FUN_003d3dd8(&DAT_006c0ba8,&DAT_0040953c,FUN_003d5058) */
    }
}

/* FUN_00409540 @ 0x00409540 — sk_job_kind_dispatch: dispatches a job by its
 * 2-bit kind tag (p[0] & 3). Kind 1: indirect call through the type's
 * metadata vtable (+8) with a payload pointer derived from p[1]-8's +0x50.
 * Kind 2: release p[2]. Kind 0: panic (SoftwareBreakpoint 0x4095a0).
 * Confidence: low. */
static void sk_job_kind_dispatch(word_t *p)
{
    word_t kind = *p & 3;
    if (kind < 2) {
        if (kind == 1) {
            word_t off = (word_t)*(uint8_t *)(*(word_t *)(p[1] - 8) + 0x50);
            (**(void(**)(word_t))(*(word_t *)(p[1] - 8) + 8))
                ((word_t)p + off + 0x18 & ~off);
            return;
        }
        SK188_BKPT(0x4095a0); /* SoftwareBreakpoint(1,0x4095a0) */
    }
    if (kind == 2) {
        sk_swift_release(p[2]); /* thunk_FUN_0036b118 */
    }
}

/* FUN_004095a0 @ 0x004095a0 — sk_run_job: the job runner. Reads the job's
 * async state pointer (base 0xc0, or 0xd0 when flag 0x1000000 set, plus bit
 * 0x17-masked offset), switches on the state's 2-bit kind: for kind 3 builds
 * a 0x30-byte async frame (FUN_0040bcf8), stores the reply/send parameters,
 * links it into the job (FUN_0040bdd0/FUN_0040af00), appends to the async
 * buffer (FUN_0036a2ac), clears the permission flag (FUN_004087cc), then
 * pumps the error slots (FUN_00408834/FUN_00408ae4/FUN_00408864) until the
 * state kind leaves the in-flight range, and finally commits the
 * double-word CAS finalisation (bit 0x800) on the status word, with the
 * FUN_0040c0f8/FUN_0040bda0 slow path. Returns the final state kind.
 * Confidence: low (state machine). */
static word_t sk_run_job(word_t self, word_t job, word_t *out, word_t a4,
                         word_t a5, word_t a6)
{
    word_t base = 0xc0;
    if ((*(uint32_t *)(self + 0x20) & 0x1000000) != 0) { base = 0xd0; }
    {
        word_t off = (word_t)(*(uint32_t *)(self + 0x20) >> 0x17) & 8;
        word_t sp = *(word_t *)(self + base + off) & 3;
        if (sp - 3 < (word_t)-2) {
            word_t *frame;
            word_t hi, lo, w1, w2, t0, t1, u;

            out[2] = 0;
            out[3] = a6;
            out[1] = (a4 == 0) ? 0 : a4;
            out[0] = (a5 == 0) ? 0 : a5;
            frame = (word_t *)sk_alloc_buf(job, 0x30); /* FUN_0040bcf8 */
            frame[0] = 0;
            frame[1] = 0;
            *(uint32_t *)(frame + 4) = 1;
            frame[5] = job;
            frame[2] = self;
            *(word_t **)(job + 0xa0) = frame;
            hi = *(word_t *)(job + 0x60);
            lo = *(word_t *)(job + 0x68);
            sk_build_front(job, (word_t)frame, (word_t)&hi, (word_t)sk_build_cb,
                           (word_t)&frame); /* FUN_0040bdd0 */
            sk_swift_array_append(job + 0x50);   /* FUN_0036a2ac */
            sk_err_clear_perm(job);              /* FUN_004087cc */
            do {
                u = sk_err_op_take();            /* FUN_00408834 */
                sk_err_reply_dispose(self, 0, 0);/* FUN_00408ae4 */
                sk_err_op_swap(u);               /* FUN_00408864 */
                sp = *(word_t *)(self + base + off) & 3;
            } while (sp - 1 > 1); /* 1 < sp-1 */
            hi = *(word_t *)(job + 0x60);
            lo = *(word_t *)(job + 0x68);
            if (((uint32_t)hi >> 0xe & 1) == 0) {
                w1 = *(word_t *)(job + 0x60);
                w2 = *(word_t *)(job + 0x68);
                if ((w1 == lo) && (w2 == hi)) {
                    *(word_t *)(job + 0x60) = lo;
                    *(word_t *)(job + 0x68) = (word_t)((uint32_t)hi & 0xffffa3ff | 0x800);
                }
                if (w1 != hi || w2 != lo) {
                    do {
                        t0 = *(word_t *)(job + 0x60);
                        t1 = *(word_t *)(job + 0x68);
                        if ((t0 == w2) && (t1 == w1)) {
                            *(word_t *)(job + 0x60) = w2;
                            *(word_t *)(job + 0x68) = (word_t)((uint32_t)w1 & 0xffffe3ff | 0x800);
                        }
                        w1 = t0; w2 = t1;
                    } while (t0 != hi || t1 != lo);
                }
            } else {
                u = *(word_t *)(job + 0xa0);
                sk_128_save(job, u, (word_t)(uintptr_t)&hi, (word_t)(uintptr_t)&frame); /* FUN_0040c0f8 */
                sk_128_load(job, u);                       /* FUN_0040bda0 */
                *(word_t *)(job + 0xa0) = 0;
            }
            sk_err_set_perm(job);                /* FUN_00408784 */
            sk_swift_array_destroy(job + 0x50);  /* FUN_0036a244 */
        }
        return sp;
    }
}

/* FUN_004097cc @ 0x004097cc — sk_future_get: returns the future value stored
 * at p+0x18, merged through the object identity hash (FUN_003a25b8 +
 * FUN_003d52d0); 0 if the pointer at p+0x10 is empty. */
static sk_128_t sk_future_get(word_t p)
{
    word_t v;
    word_t lp = *(word_t *)(p + 0x10);
    if (lp == 0) {
        v = 0;
    } else {
        v = sk_identity_hash(lp);  /* FUN_003a25b8 */
        v = sk_obj_merge(lp, v, *(word_t *)(p + 0x18)); /* FUN_003d52d0 */
    }
    return (sk_128_t){ v, 0 };
}

/* FUN_00409818 / 0x0040981c — sk_job_teardown / _teardown2: free the async
 * buffer (thunk_FUN_00012568, kind 0xf), clear the owner's slot (+0x40 then
 * +0x20), and run sk_job_state_set on the stored object. */
static void sk_job_teardown(word_t p)
{
    word_t lv = *(word_t *)(p + 0x48);
    sk_heap_free(p, 0x50, 0xf);                       /* thunk_FUN_00012568 */
    *(word_t *)(*(word_t *)(lv + 0x40) + 0x20) = 0;
    sk_job_state_set(lv);                            /* FUN_00409858 */
}
/* FUN_0040981c @ 0x0040981c — sk_job_teardown2 (byte-identical twin of 0x00409818). */
static void sk_job_teardown2(word_t p)
{
    word_t lv = *(word_t *)(p + 0x48);
    sk_heap_free(p, 0x50, 0xf);                       /* thunk_FUN_00012568 */
    *(word_t *)(*(word_t *)(lv + 0x40) + 0x20) = 0;
    sk_job_state_set(lv);                            /* FUN_00409858 */
}

/* FUN_00409858 @ 0x00409858 — sk_job_state_set: takes the state lock
 * (FUN_0040b2c8), sets the state of *(p+0x40) to 2 (cancelled/finished),
 * then if it was already 2 wakes the waiters (FUN_0040b6cc). */
static void sk_job_state_set(word_t p)
{
    word_t lv;
    sk_state_lock((word_t)0);              /* FUN_0040b2c8 */
    lv = *(word_t *)(p + 0x40);
    if ((*(word_t *)(lv + 0x18) == 0) && (*(word_t *)(lv + 0x18) == 0)) {
        *(word_t *)(lv + 0x18) = 2;
        return;
    }
    *(word_t *)(lv + 0x18) = 2;
    sk_state_set(*(word_t *)(lv + 0x40)); /* FUN_0040b6cc */
}

/* FUN_004098c8 @ 0x004098c8 — sk_job_enqueue: enqueue a job onto an async
 * queue. Computes the state-pointer offset from job+0x20 flags, reads the
 * pending word (job-8 header size), refcounts the queue entry (1/2) under
 * LOAcquire/LORelease, forwards the async argument (FUN_0040cfd0) when the
 * "is async" bit is set, then walks the linked wake list (nodes at +0x10,
 * callback at +0x40) invoking each waiter's vtable with the job payload.
 * Confidence: low. */
static void sk_job_enqueue(word_t self, word_t job)
{
    word_t base = 0xc0;
    word_t *q, u5, u3, u2;
    word_t lv;

    if ((*(uint32_t *)(self + 0x20) & 0x1000000) != 0) { base = 0xd0; }
    q = (word_t *)(self + base + ((word_t)(*(uint32_t *)(self + 0x20) >> 0x17) & 8));
    u5 = *(word_t *)(job + -8);
    q[2] = u5;
    u3 = 1;
    if (u5 != 0) { u3 = 2; }
    LOAcquire();
    u2 = *q;
    *q = u3;
    LORelease();
    if ((*(uint32_t *)(self + 0x20) >> 0x1a & 1) != 0) {
        base = 0xc0;
        if ((*(uint32_t *)(self + 0x20) & 0x1000000) != 0) { base = 0xd0; }
        sk_async_arg2(*(word_t *)(self + base), self, job); /* FUN_0040cfd0 */
    }
    u2 = u2 & ~(word_t)3;
    while (u2 != 0) {
        lv = *(word_t *)(u2 + 0x40);
        u2 = *(word_t *)(u2 + 0x10);
        if (u5 == 0) {
            word_t off = (word_t)*(uint8_t *)(*(word_t *)(q[1] - 8) + 0x50);
            (**(void(**)(word_t, word_t))(*(word_t *)(q[1] - 8) + 0x10))
                (*(word_t *)(lv + 0x18),
                 (word_t)q + off + 0x18 & ~off);
        } else {
            *(word_t *)(lv + 0x10) = q[2];
            sk_swift_retain((word_t)0); /* thunk_FUN_0036b270 */
        }
    }
}

/* FUN_004099d4 @ 0x004099d4 — sk_job_destroy: releases the job. If the
 * "owned" bit (flag 0x2000000) is set, runs sk_job_kind_dispatch on the
 * state pointer; then releases the lock (thunk_FUN_00053aa0 on +0xb0) and
 * tears down the callback list (FUN_0040af3c on +0x70). Returns p. */
static word_t sk_job_destroy(word_t p)
{
    uint32_t flags = *(uint32_t *)(p + 0x20);
    word_t base;

    if ((flags >> 0x19 & 1) != 0) {
        base = 0xc0;
        if ((flags & 0x1000000) != 0) { base = 0xd0; }
        sk_job_kind_dispatch((word_t *)(p + base + ((word_t)(flags >> 0x17) & 8))); /* FUN_00409540 */
    }
    sk_lock_release(p + 0xb0);   /* thunk_FUN_00053aa0 */
    sk_build_cb(p + 0x70);       /* FUN_0040af3c */
    return p;
}

/* FUN_00409a34 @ 0x00409a34 — sk_combined_read: packs two 32-bit fields
 * (+0x24 low, +0x90 high) into one word. */
static word_t sk_combined_read(word_t p)
{
    return ((word_t)*(uint32_t *)(p + 0x90) << 32) | *(uint32_t *)(p + 0x24);
}

/* FUN_00409a54 @ 0x00409a54 — sk_job_copy_state: copies a 7-word job/state
 * tuple from s/t into d, normalising the third word's null to 0. */
static void sk_job_copy_state(word_t *d, word_t *s, word_t *t)
{
    word_t lv;

    d[0] = s[0];
    d[1] = s[1];
    lv = s[2];
    if (lv == 0) { lv = 0; }
    d[2] = lv;
    d[3] = t[0];
    d[5] = t[2];
    d[4] = t[1];
    d[6] = t[3];
}

/* FUN_00409b14 / 0x00409b18 — sk_job_release / _release2: destroy the job
 * (FUN_004099d4) and free its storage (thunk_FUN_00012568). */
static void sk_job_release(void)
{
    sk_job_destroy(0);      /* FUN_004099d4() */
    sk_heap_free((word_t)0); /* thunk_FUN_00012568() */
}
/* FUN_00409b18 @ 0x00409b18 — sk_job_release2 (byte-identical twin of 0x00409b14). */
static void sk_job_release2(void)
{
    sk_job_destroy(0);      /* FUN_004099d4() */
    sk_heap_free((word_t)0); /* thunk_FUN_00012568() */
}

/* FUN_00409c10 @ 0x00409c10 — sk_job_flags: low byte of p+0x60. */
static word_t sk_job_flags(word_t p) { return *(word_t *)(p + 0x60) & 0xff; }

/* FUN_00409c1c @ 0x00409c1c — sk_job_field_98: value at p+0x98. */
static word_t sk_job_field_98(word_t p) { return *(word_t *)(p + 0x98); }

/* FUN_00409c24 @ 0x00409c24 — sk_run_inline: "called runInline within an
 * async" guard (fatal FUN_004ba640, 0x005dc7a6) unless the OperationInvalid
 * slot is empty; then builds a job from the descriptor (param_2, size in
 * *param_2, count param_2[1]) via sk_job_build, optionally with a 0x1000
 * zeroed scratch buffer (FUN_003d3dac + DAT_00658c88 + thunk_FUN_00114330),
 * and runs it inline. Stack canary at 0x2c8502b44bfffed6 triggers
 * FUN_0011d7e8. Confidence: low. */
static void sk_run_inline(word_t out, int *desc, word_t a3, word_t a4)
{
    word_t sz, blk, lv;
    uint8_t *scratch;
    word_t scratch_sz;
    word_t canary = 0x2c8502b44bfffed6;
    word_t local[4];

    lv = sk_err_op_get();   /* FUN_0040880c */
    if (lv != 0) {
        sk_fatal(0, 0x005dc7a6); /* FUN_004ba640 — does not return */
    }
    sz = (desc == 0) ? 0 : ((word_t)desc + (word_t)*desc);
    {
        int cnt = desc[1];
        word_t esz = 0; /* FUN_00409e14(0,0,a4,cnt) — void; X1 size register artifact */
        if (esz < 0x1001) {
            scratch_sz = 0x1000;
            ((void(*)(void))sk_alloc_fn_658c88)();   /* DAT_00658c88 */
            scratch = (uint8_t *)&local;              /* auStack_1080 */
            sk_memcpy((word_t)(uintptr_t)scratch, (word_t)0x1000); /* thunk_FUN_00114330 */
        } else {
            scratch_sz = 0;
            scratch = (uint8_t *)0;
        }
        local[0] = 0xff;
        local[1] = 0;
        local[2] = (word_t)scratch;
        local[3] = scratch_sz;
        lv = sk_job_build(0x200, (uint8_t *)&local, a4, sz, a3, cnt).hi; /* FUN_00409e90 */
        sk_err_reply_dispose(lv, 0, 0); /* FUN_00408ae4 */
        {
            word_t base = 0xc0;
            word_t off, u;
            if ((*(uint32_t *)(lv + 0x20) & 0x1000000) != 0) { base = 0xd0; }
            off = (word_t)(*(uint32_t *)(lv + 0x20) >> 0x17) & 8;
            u = (word_t)*(uint8_t *)(*(word_t *)(*(word_t *)(lv + base + off + 8) + -8) + 0x50);
            (**(void(**)(word_t, word_t, word_t))(*(word_t *)(a4 + -8) + 0x10))
                (out, u + lv + base + off + 0x18 & ~u, a4);
        }
        sk_job_destroy(lv); /* FUN_004099d4 */
    }
    if (canary != 0x2c8502b44bfffed6) {
        sk_stack_chk_fail(); /* FUN_0011d7e8 — does not return */
    }
}

/* FUN_00409e14 @ 0x00409e14 — sk_noop: empty. */
static void sk_noop(void) { }

/* FUN_00409e90 @ 0x00409e90 — sk_job_build: the async job descriptor->job
 * builder. Walks a linked descriptor list (desc+8 = next, tagged kind byte
 * desc[0], payload desc+0x10), accumulating into the job flags word (uVar20)
 * and collecting the resume context; maps clock/timer fields; then allocates
 * the job (FUN_00409210/FUN_0040bcf8/FUN_000101a0), fills its header (kind
 * 0xb900342a5280006a, size/type words), installs the continuation pointer
 * (puVar15), stores the callback/async fields, and runs the per-kind
 * finalisers (FUN_004091ac, FUN_0040c3a4, FUN_0040c4b0, FUN_0040c748,
 * FUN_0040eef8, FUN_0040c970, FUN_0040f5c0). Returns {lo=job, hi=body}.
 * Ghidra reports a read-only-address write at ram,0x00657998.
 * Confidence: low (Swift async ABI). */
static sk_128_t sk_job_build(word_t flags, uint8_t *desc, word_t a3,
                             word_t a4, word_t a5, word_t a6)
{
    uint32_t u16 = (uint32_t)flags;
    uint32_t jf = (u16 & 0x100) << 0x10;
    uint8_t *pn = (uint8_t *)0;
    uint8_t b6 = 0;
    word_t l19 = 0, l21 = 0, u22 = 0, lvar3 = 0;
    uint32_t u14 = 0;
    sk_128_t au23 = sk_128_zero();
    uint8_t *pb = (uint8_t *)0;
    word_t u12, u13;
    uint32_t isz;
    word_t lvar9, pu, i8, u10;
    sk_128_t au24;
    word_t *pu11, *pu1;
    void *pu15;

    if (desc != (uint8_t *)0) {
        uint8_t *pb17 = (uint8_t *)0;
        do {
            uint8_t b5 = *desc;
            pn = pb17;
            if (b5 < 6) {
                if (b5 < 4) {
                    if (b5 == 1) {
                        l21 = *(word_t *)(desc + 0x10);
                        jf |= 0x4000000;
                    } else if (b5 == 3) {
                        l19 = *(word_t *)(desc + 0x10);
                        jf |= 0x11000000;
                        b6 = 1;
                    }
                } else if (b5 == 5) {
                    u14 = 0;
                    au23 = *(sk_128_t *)(desc + 0x10);
                    jf |= 0x20000000;
                } else if (b5 == 4) {
                    SK188_BKPT(0x409fa4); /* SoftwareBreakpoint(1,0x409fa4) */
                }
            } else if (b5 == 6) {
                au23 = sk_future_get((word_t)desc); /* FUN_004097cc */
                jf |= 0x20000000;
                u14 = 1;
            } else if (b5 == 7) {
                u22 = *(word_t *)(desc + 0x10);
                jf |= 0x40000000;
            } else {
                pb = desc;
                if (b5 != 0xff) { pb = pb17; }
            }
            desc = *(uint8_t **)(desc + 8);
            pb17 = pn;
        } while (desc != (uint8_t *)0);
    }
    if (a3 != 0) { jf |= 0x2000000; }
    lvar9 = sk_err_op_get(); /* FUN_0040880c */
    lvar3 = 0;
    if ((jf & 0x1000000) != 0) { lvar3 = lvar9; }
    if (((u16 >> 0xd & 1) != 0) && (l21 != 0)) {
        sk_timer_cancel(l21, 1); /* FUN_0040d604 */
    }
    if ((u16 >> 9 & 1) == 0) {
        flags = flags & 0xff;
        if (((u16 >> 10 & 1) != 0) || ((jf & 0x14000000) != 0)) {
            if ((jf & 0x14000000) == 0) {
                if (flags == 0) {
                    u12 = (lvar9 == 0) ? sk_err_op_none() : *(word_t *)(lvar9 + 0x98); /* FUN_00408898 */
                    flags = (u12 != 0x21) ? u12 : 0x19;
                }
            } else if (flags == 0) {
                flags = (*(word_t *)(lvar9 + 0x98) != 0x21) ? *(word_t *)(lvar9 + 0x98) : 0x19;
            }
        }
    } else {
        flags = sk_err_op_none(); /* FUN_00408898 */
    }
    u12 = (flags != 0) ? flags : 0x15;
    au24 = sk_128_zero(); /* FUN_00409e14(lvar3,l21,a3,a6) — void, X1 artifact */
    u13 = au24.hi;
    if (l19 == 0) {
        if ((pb == (uint8_t *)0) ||
            (pu11 = *(word_t **)(pb + 0x10), pu11 == (word_t *)0)) {
            pu11 = (word_t *)sk_alloc_pool(u13, 0x7738fbe); /* FUN_000101a0 */
            goto do_header;
        }
        i8 = *(int *)(pb + 0x18) - (uint32_t)au24.hi;
    } else {
        u10 = sk_job_size(); /* FUN_00409218 */
        if ((u13 <= u10) & b6) {
            pu11 = (word_t *)sk_job_self_ptr(l19); /* FUN_00409210 */
            i8 = (int)sk_job_size() - (uint32_t)au24.hi; /* FUN_00409218 */
            b6 = 1;
        } else {
            pu11 = (word_t *)sk_alloc_buf(lvar3, u13 + 0x200); /* FUN_0040bcf8 */
            b6 = 0;
do_header:
            i8 = 0x200;
        }
    }
    pu1 = (word_t *)((word_t)pu11 + au24.lo);
    if (((u16 >> 0xe & 1) == 0) && (a3 != 0)) {
        pu15 = (void *)0x409b4c;
        if (a4 == 0) { a4 = 0; }
    } else {
        pu15 = (void *)0x409b34;
        if (a4 != 0) { a4 = 0; }
    }
    pu1[-3] = a4;
    pu1[-2] = a5;
    if (((jf >> 0x1d & 1) == 0) && (lvar3 != 0) &&
        (au24 = sk_copy128(lvar9, 0), au24.lo != 0)) {
        jf |= 0x20000000;
        au23 = au24;
    }
    if (l19 == 0) {
        pu11[0] = 0xb900342a5280006a;
        pu11[1] = 3;
        *(uint32_t *)(pu11 + 4) = jf;
        pu11[5] = 0;
        pu11[6] = 0;
        pu11[7] = (word_t)pu15;
        pu11[8] = (word_t)pu1;
    } else {
        pu11[0] = 0xb900342a5280006a;
        pu11[1] = 0x80000004ffffffff;
        *(uint32_t *)(pu11 + 4) = jf;
        pu11[5] = 0;
        pu11[6] = 0;
        pu11[7] = (word_t)pu15;
        pu11[8] = (word_t)pu1;
    }
    *(uint32_t *)((word_t)pu11 + 0x24) = 0x3900803f;   /* raw instruction word */
    *(uint32_t *)((word_t)pu11 + 0x24) = 0x3900803f;
    if (lvar3 != 0) {
        pu11[0x18] = lvar9;
        pu11[0x19] = 0;
    }
    if (l21 != 0) {
        word_t base = 0xc0;
        if ((jf & 0x1000000) != 0) { base = 0xd0; }
        *(word_t *)((word_t)pu11 + base) = l21;
    }
    if (a3 != 0) {
        word_t base = 0xc0;
        word_t *pu2;
        word_t u10;
        if ((jf & 0x1000000) != 0) { base = 0xd0; }
        pu2 = (word_t *)((word_t)pu11 + ((word_t)(jf >> 0x17) & 8) + base);
        pu2[0] = 0;
        pu2[1] = a3;
        pu2[2] = 0;
        u10 = (word_t)*(uint8_t *)(*(word_t *)(a3 + -8) + 0x50);
        pu1[-4] = (word_t)pu2 + u10 + 0x18 & ~u10;
    }
    *pu1 = 0;
    if (pb == (uint8_t *)0) {
        if (l19 != 0) {
            pu1[1] = (word_t)sk_job_gc;   /* FUN_0040b084 */
            goto set_rest;
        }
        if (((u16 >> 0xf & 1) == 0) && (a5 != 0)) {
            pu1[1] = (word_t)sk_job_gc2;  /* FUN_0040b0cc */
        } else {
            pu1[1] = (word_t)sk_job_gc3;  /* FUN_0040b128 */
        }
    } else {
        pu1[1] = (word_t)sk_job_gc4;      /* FUN_0040b03c */
        if ((l19 != 0) || (*(word_t *)(pb + 0x10) != 0)) {
set_rest:
            if (i8 != 0) {
                pu11[10] = 0;
                pu11[0xb] = 0;
                sk_buf_init((word_t)(uintptr_t)(pu11 + 0xe), (word_t)(uintptr_t)pu11 + u13, i8); /* FUN_004ba660 */
                pu11[0x11] = 0;
                goto after_buf;
            }
        }
    }
    pu11[0xe] = 0;
    pu11[0xf] = 0;
    *(uint32_t *)(pu11 + 0x10) = 0;
    pu11[0x11] = 0;
    pu11[10] = 0;
    pu11[0xb] = 0;
after_buf:
    pu11[0x13] = u12;
    pu11[0x14] = 0;
    sk_buf_zero((word_t)(uintptr_t)(pu11 + 0x16), 0); /* FUN_0040b280 */
    pu11[0xc] = u12 & 0xffffffff;
    pu11[0xd] = 0;
    if (lvar3 != 0) {
        if (((l21 != 0) && (u12 = sk_timer_is_pending(l21), (u12 & 1) != 0)) ||
            (((uint32_t)*(word_t *)(lvar9 + 0x60) >> 8 & 1) != 0)) {
            sk_job_finalize((word_t)(uintptr_t)pu11); /* FUN_0040c748 */
        }
        sk_job_link((word_t)(uintptr_t)(pu11 + 0x11), (word_t)(uintptr_t)pu11, lvar9); /* FUN_0040eef8 */
    }
    if (l21 != 0) {
        sk_timer_arm(l21, (word_t)(uintptr_t)pu11); /* FUN_0040c970 */
        sk_swift_retain((word_t)(uintptr_t)pu11);   /* FUN_0036b270 */
    }
    if ((u16 >> 10 & 1) != 0) {
        sk_job_wake((word_t)(uintptr_t)pu11); /* FUN_0040f5c0 */
    }
    if (l19 != 0) {
        sk_job_timer_set((word_t)(uintptr_t)pu11, (word_t *)l19, b6 ^ 1); /* FUN_004091ac */
    }
    if ((jf >> 0x1d & 1) != 0) {
        sk_job_delay((word_t)(uintptr_t)pu11, a6, a3, u14); /* FUN_0040c3a4 */
    }
    if (jf >> 0x1e != 0) {
        sk_job_async((word_t)(uintptr_t)pu11, u22); /* FUN_0040c4b0 */
    }
    if ((u16 >> 0xc & 1) != 0) {
        sk_swift_retain((word_t)(uintptr_t)pu11); /* FUN_0036b270 */
    }
    au23.lo = (word_t)(uintptr_t)pu11;
    au23.hi = (word_t)(uintptr_t)pu1;
    return au23;
}

/* FUN_0040a530 @ 0x0040a530 — sk_invoke: run a job through sk_run_job with
 * a fixed continuation pointer (0x409b68). On state kind 2 retains the async
 * arg; otherwise calls the stored vtable (+0x10) with the async payload;
 * then jumps through the original callback (unrecoverable jumptable). */
static void sk_invoke(word_t a, word_t job, word_t cb, word_t a4)
{
    word_t lv = sk_err_op_get();   /* FUN_0040880c */
    word_t l4 = (a4 == 0) ? 0 : a4;
    word_t base, off, u;
    word_t res;

    *(word_t *)(lv + 0x38) = 0x409b68;
    *(word_t *)(lv + 0x40) = l4;
    res = sk_run_job(job, lv, (word_t *)a4, cb, 0, 0); /* FUN_004095a0(job,lv,a4,cb) */
    base = 0xc0;
    if ((*(uint32_t *)(job + 0x20) & 0x1000000) != 0) { base = 0xd0; }
    base = job + base + ((word_t)(*(uint32_t *)(job + 0x20) >> 0x17) & 8);
    if (res == 2) {
        sk_swift_retain(*(word_t *)(base + 0x10)); /* thunk_FUN_0036b270 */
    } else {
        off = (word_t)*(uint8_t *)(*(word_t *)(*(word_t *)(base + 8) + -8) + 0x50);
        (**(void(**)(word_t, word_t))(*(word_t *)(*(word_t *)(base + 8) + -8) + 0x10))
            (a, off + base + 0x18 & ~off);
    }
    ((void(*)(void))cb)(); /* indirect jump — unrecoverable jumptable */
}

/* FUN_0040a688 @ 0x0040a688 — sk_job_is_error: bit 8 of p+0x60. */
static word_t sk_job_is_error(word_t p) { return *(word_t *)(p + 0x60) >> 8 & 1; }

/* FUN_0040a694 @ 0x0040a694 — sk_l4_log0: FUN_004b9d68(0, a). */
static void sk_l4_log0(word_t a) { sk_l4_log(0, a); }

/* FUN_0040a6c0 @ 0x0040a6c0 — sk_invoke_future: like sk_invoke but for the
 * future path; fatal ("future reported an error, but wa..." 0x005dc82e) if
 * the run returns state kind 2. */
static void sk_invoke_future(word_t a, word_t job, word_t cb, word_t a4)
{
    word_t lv = sk_err_op_get(); /* FUN_0040880c */
    word_t l2 = (a4 == 0) ? 0 : a4;
    word_t base, off, u;
    word_t res;

    *(word_t *)(lv + 0x38) = 0x409bd4;
    *(word_t *)(lv + 0x40) = l2;
    res = sk_run_job((word_t)(uintptr_t)(lv + 0x38), job, (word_t *)lv, a4, cb, 0);
    /* FUN_004095a0(lv+0x38,job,lv,a4,cb) */
    if (res == 2) {
        sk_fatal(0, 0x005dc82e); /* FUN_004ba640 — does not return */
    }
    base = 0xc0;
    if ((*(uint32_t *)(job + 0x20) & 0x1000000) != 0) { base = 0xd0; }
    base = job + base + ((word_t)(*(uint32_t *)(job + 0x20) >> 0x17) & 8);
    off = (word_t)*(uint8_t *)(*(word_t *)(*(word_t *)(base + 8) + -8) + 0x50);
    (**(void(**)(word_t, word_t))(*(word_t *)(*(word_t *)(base + 8) + -8) + 0x10))
        (a, off + base + 0x18 & ~off);
    ((void(*)(void))cb)(); /* indirect jump — unrecoverable jumptable */
}

/* FUN_0040a7f0 @ 0x0040a7f0 — sk_job_state_set2: same as sk_job_state_set
 * (state lock + set state 2 + wake). */
static void sk_job_state_set2(word_t p)
{
    word_t lv;
    sk_state_lock((word_t)0);   /* FUN_0040b2c8 */
    lv = *(word_t *)(p + 0x40);
    if ((*(word_t *)(lv + 0x18) == 0) && (*(word_t *)(lv + 0x18) == 0)) {
        *(word_t *)(lv + 0x18) = 2;
        return;
    }
    *(word_t *)(lv + 0x18) = 2;
    sk_state_set(*(word_t *)(lv + 0x40)); /* FUN_0040b6cc */
}

/* FUN_0040a860 @ 0x0040a860 — sk_job_state_set3: set the state value (+0x20)
 * and state 2 + wake. */
static void sk_job_state_set3(word_t p, word_t v)
{
    word_t lv;
    sk_state_lock((word_t)0);   /* FUN_0040b2c8 */
    lv = *(word_t *)(p + 0x40);
    *(word_t *)(lv + 0x20) = v;
    if ((*(word_t *)(lv + 0x18) == 0) && (*(word_t *)(lv + 0x18) == 0)) {
        *(word_t *)(lv + 0x18) = 2;
        return;
    }
    *(word_t *)(lv + 0x18) = 2;
    sk_state_set(*(word_t *)(lv + 0x40)); /* FUN_0040b6cc */
}

/* FUN_0040a8d8 @ 0x0040a8d8 — sk_job_alloc: allocate a job (kind 3) of
 * 0x20 bytes, store the two payload words, and run the CAS callback
 * (0x409b700) via FUN_0040c09c; if the callback reports success, invoke the
 * stored fn ptr (puVar1[2]) and free the job, returning null. */
static word_t *sk_job_alloc(word_t a, word_t b)
{
    word_t *p = (word_t *)sk_alloc(0x20); /* FUN_0040bb18 */
    char flag = 0;
    word_t *local;

    p[0] = 3;
    p[1] = 0;
    p[2] = a;
    p[3] = b;
    local = &(word_t){0};
    sk_cas_call((word_t)(uintptr_t)p, (word_t)0x409b700, (word_t)(uintptr_t)&local); /* FUN_0040c09c */
    if (flag == 1) {
        ((void(*)(void))p[2])();
        sk_free((word_t)p);   /* FUN_0040bd24 */
        p = (word_t *)0;
    }
    return p;
}

/* FUN_0040a9b0 @ 0x0040a9b0 — sk_job_check_cancel: if the job is non-null,
 * checks the runtime (FUN_0040c350) and frees the job if cancelled. */
static void sk_job_check_cancel(word_t p)
{
    if (p != 0) {
        sk_err_op_get();       /* FUN_0040880c */
        if (sk_rt_check((word_t)0) != 0) {   /* FUN_0040c350 */
            sk_free(p);        /* FUN_0040bd24 */
        }
    }
}

/* FUN_0040a9f4 @ 0x0040a9f4 — sk_job_alloc2: allocate a job (kind 4) of
 * 0x20 bytes; when a is nonzero, the type word (pdVar2) points at the job
 * body's own storage; runs the CAS callback (0x409b71c) via FUN_0040c09c. */
static word_t *sk_job_alloc2(word_t a, word_t b)
{
    word_t *p = (word_t *)sk_alloc(0x20); /* FUN_0040bb18 */
    word_t *type = &sk_cputype;           /* __thread_bss.cputype */

    p[0] = 4;
    p[1] = 0;
    if (a != 0) { type = (word_t *)(p + 2); }
    p[2] = a;
    p[3] = b;
    sk_cas_call((word_t)(uintptr_t)type, (word_t)(uintptr_t)p, (word_t)0x409b71c); /* FUN_0040c09c */
    return p;
}
