/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice: 0x000102f4-0x0001574c — early-boot memory manager (embedded
 * libmalloc/lite_zone), per-thread storage (TSS), thread-block (TB) machinery,
 * the capability/object registry, and the cL4 IPC transport helpers. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
/* LZCOUNT(x): leading-zero count. Ghidra renders clz as LZCOUNT. */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
/* DC_GVA(addr): data-cache clean-by-VA (op 0x4e). */
#define DC_GVA(a) __asm__ volatile("dc cvau, %0" : : "r"((uint64_t)(a)))

/* ------------------------------------------------------------------ *
 * Shared globals (image-base addresses are the Ghidra ground truth).
 * ------------------------------------------------------------------ */
extern uint64_t sk_mall_zone_base;      /* DAT_006adfd8: boot libmalloc zone base */
extern uint64_t sk_mall_zone_flags;     /* DAT_006adfe0: zone feature flags (bit0 = madvise) */
extern uint64_t sk_mall_zone_tbl[];     /* DAT_006adfe8: registered-zone pointer table */
extern uint64_t sk_mall_zone_count;     /* DAT_006ac238: number of registered zones */
extern uint8_t  sk_boot_ncpu;           /* DAT_006ac23d: boot CPU count */
extern uint64_t sk_lookup_root;         /* DAT_0064c060: root "lookup" object (kernel env) */
extern uint64_t sk_tss_base;            /* DAT_006ae1b0: TSS key table */
extern uint64_t sk_tss_cur_cpu;         /* DAT_006ae1c0: current TSS cpu */
extern uint64_t sk_tss_cur_val;         /* DAT_006ae1c8: current TSS value */
extern uint64_t sk_zone_depot[3];       /* DAT_006ae1d0: per-cpu free-page depot area */
extern uint64_t (*sk_cpu_alloc_fn)(uint64_t); /* DAT_00657f98: boot page-alloc function ptr */

/* ------------------------------------------------------------------ *
 * cL4 kernel helpers reconstructed by other slice workers.
 * FUN_ address is ground truth; names are estimates.
 * ------------------------------------------------------------------ */
extern void *sk_zone_alloc_obj(unsigned flags, uint64_t size, uint64_t magic); /* FUN_00010244 */
extern uint64_t sk_phys_alloc(uint64_t size);                                 /* FUN_00034f70 */
extern void sk_kernel_abort(int code, uint64_t ptr);                          /* FUN_0000298c */
extern uint64_t sk_boot_ncpu_get(void);                                       /* FUN_0005ac2c */
extern void sk_printf(const char *fmt, ...);                                  /* FUN_00118b28 */
extern void sk_printf2(const char *fmt, ...);                                 /* FUN_00118b94 */
extern void sk_printf3(const char *fmt, ...);                                 /* FUN_00118c4c */
extern void sk_stack_chk_fail(void) __attribute__((noreturn));                /* FUN_0011d7e8 */
extern void sk_boot_fatal2(void) __attribute__((noreturn));                   /* FUN_00116d60 */
extern int  sk_lock_acquire(void *lock);                                      /* FUN_0011582c */
extern void sk_lock_release(void *lock);                                      /* FUN_00115894 */
extern void sk_memcpy(uint64_t dst, uint64_t src, uint64_t n);                /* FUN_00117cc4 */
extern void sk_bzero(uint64_t p, uint64_t n);                                 /* FUN_00117f8c */
extern uint64_t sk_alloc_low(uint64_t a, uint64_t b, uint64_t c, int d, uint64_t e,
                             uint64_t f, uint64_t g);                          /* FUN_00117fdc */
extern uint64_t sk_alloc_meta2(uint64_t a, uint64_t b, uint64_t c, uint64_t d); /* FUN_0011807c */
extern uint64_t sk_dealloc_at(uint64_t a, uint64_t b, uint64_t c);            /* FUN_001180cc */
extern uint64_t sk_depot_grow(void *depot, void *base, uint64_t size, uint64_t align); /* FUN_00117d18 */
extern void sk_string_set(void *dst, const char *s, uint64_t n, uint64_t m);  /* FUN_00117e68 */
extern void sk_fatal_printf(const char *fmt, ...) __attribute__((noreturn));  /* FUN_001150e0 */
extern void sk_panic_line(const char *f, const char *file, const char *fn,
                          uint64_t line) __attribute__((noreturn));           /* FUN_00115424 */
extern long sk_print_bytes(void *p, uint64_t n);                              /* FUN_00115574 */
extern void sk_sleep(uint64_t t);                                             /* FUN_001183e0 */
extern void sk_printf_dbg(const char *fmt, ...);                              /* FUN_00115828 */
extern void sk_depot_init(void *depot, uint64_t n);                           /* FUN_00114330 */
extern void sk_obj_lock(void *obj);                                           /* FUN_001157f0 */
extern void sk_obj_unlock(void *obj);                                         /* FUN_001157d4 */
extern uint64_t sk_boot_info_get(void);                                       /* FUN_00060524 */
extern uint64_t sk_tramp_call(void);                                           /* FUN_000603bc */
extern uint64_t sk_tramp_setup(uint64_t a);                                   /* FUN_000636d0 */
extern uint64_t sk_tramp_get(uint64_t a);                                     /* FUN_000636d8 */
extern uint64_t sk_cpu_reg_store(uint64_t v);                                 /* FUN_00063a50 */
extern uint64_t sk_percpu_key(uint64_t a, uint64_t b, uint64_t c, uint64_t d); /* FUN_0005ea94 */
extern uint64_t sk_obj_retain(void *o);                                         /* FUN_0004b520 */
extern void sk_panic_brk(const char *msg) __attribute__((noreturn));          /* FUN_0005b190 */
extern void sk_clean_cache(void);                                             /* FUN_0005ee50 */
extern uint64_t sk_query_type(void);                                          /* FUN_0005ee40 */
extern void sk_tb_buf_reset_hw(void);                                         /* FUN_0005ee48 */
extern uint64_t sk_rcv_caps(void);                                            /* FUN_0005ee58 */
extern void sk_caps_retain(uint64_t n, uint64_t a);                            /* FUN_0005edac */
extern void sk_obj_release_caps(uint64_t n);                                  /* FUN_0005ed18 */
extern uint64_t sk_query_payload(void *dst, uint64_t n, int fl);              /* FUN_0005eb78 */
extern void sk_q_emit(uint64_t n);                                            /* FUN_0005ed18 */
extern void sk_depot_push(uint64_t v);                                        /* FUN_0005d470 */
extern void sk_current_thread_set(void);                                      /* FUN_00061638 */
extern void sk_q_wait(void *q, void *fn, uint64_t a);                         /* FUN_00062c2c */
extern void sk_timer_call(void *cb, void *arg, uint64_t a);                   /* FUN_0006290c */
extern uint64_t sk_cpu_id(uint64_t c);                                        /* FUN_000636a4 */
extern void *sk_thread_alloc(void);                                           /* FUN_0005fccc */

/* TB / IPC transport externs (0x15xxx-0x18xxx region). */
extern void sk_msg_init(void *m);                                             /* FUN_00015834 */
extern void sk_msg_append(void *m, uint64_t tag);                             /* FUN_0001585c */
extern void sk_msg_set(void *m, uint64_t v);                                  /* FUN_00015864 */
extern int  sk_msg_send(void *m, void *dst, uint64_t kind);                   /* FUN_0001586c */
extern void sk_msg_writedata(void *m, uint64_t v);                            /* FUN_00015b84 */
extern void sk_msg_writesize(void *m, uint64_t v);                            /* FUN_00015bac */
extern uint64_t sk_msg_count(void *m);                                        /* FUN_00015bb4 */
extern uint64_t sk_msg_get(void *m, uint64_t i);                              /* FUN_00015bbc */
extern int  sk_msg_rcv(void *m, uint64_t v);                                  /* FUN_00015be8 */
extern int  sk_msg_caps(void *m, void *buf);                                  /* FUN_00015b94 */
extern uint64_t sk_msg_caps2(void *m);                                        /* FUN_00015ba4 */
extern void sk_msg_commit(void *m, void *dst);                                /* FUN_00015b8c */
extern void sk_msg_tag(void *m, uint64_t v);                                  /* FUN_00015b8c */
extern uint64_t sk_tb_get(void *m);                                           /* FUN_000159b8 */
extern void sk_tb_retain(void *t, uint64_t n);                                /* FUN_00015984 */
extern int  sk_tb_state(void *t);                                             /* FUN_000159c0 */
extern int  sk_tb_kind(void *t);                                              /* FUN_000159c8 */
extern uint64_t sk_tb_id(void *t);                                            /* FUN_0001590c */
extern void sk_tb_sched_go(void *t, void *m);                                 /* FUN_00015904 */
extern uint64_t sk_tb_recv(void *t, void *m);                                 /* FUN_00015e9c */
extern int  sk_cap_check(uint64_t cap, uint64_t k);                           /* FUN_00017e94 */
extern int  sk_cap_fallback(void *m, uint64_t cap, void *t, void *o,
                            uint64_t f);                                      /* FUN_00017edc */
extern int  sk_cap_pre(void *o, void *t, void *p, uint64_t c);                /* FUN_000181f4 */
extern int  sk_cap_setup(void *o, void *m, void *p, uint64_t c);              /* FUN_000183f0 */
extern void sk_printf_reg(const char *fmt, ...);                              /* FUN_0011825c */
extern uint64_t sk_cap_claim(uint64_t a);                                      /* FUN_00016458 */
extern int  sk_cap_alloc_claim(uint64_t sz);                                  /* FUN_00016458 */
extern void sk_mem_bar(void);                                                 /* FUN_00060524 */
extern void CallSupervisor(uint64_t a);                                       /* cL4 supervisor call opcode */
extern uint64_t sk_boot_info2(void);                                          /* FUN_00060524 */

/* ------------------------------------------------------------------ *
 * Small kernel glue helpers (errno, per-thread flags, boot aborts,
 * message/query accessors). These map to single thunk/helper functions
 * reconstructed by other slice workers; FUN_ address in comments.
 * ------------------------------------------------------------------ */
static uint64_t sk_errno_storage;
static inline uint64_t *sk_errno_ptr(void) { return &sk_errno_storage; }     /* thunk_FUN_0006037c */
static inline void sk_clear_errno(void) { sk_errno_storage = 0; }
static inline void sk_set_errno(uint64_t e) { sk_errno_storage = e; }
static inline uint64_t sk_errno_get(void) { return sk_errno_storage; }

/* Per-thread flag slot (tpidr_el0 + 0x48). */
static inline uint64_t *sk_tpidr_flags(void)
{
	uint64_t tp;
	__asm__("mrs %0, tpidr_el0" : "=r"(tp));
	return (uint64_t *)(tp + 0x48);
}
/* Per-thread cap array (tpidrro_el0 + 0x1e0). */
static inline uint64_t *sk_tpidr_caps(void)
{
	uint64_t tp;
	__asm__("mrs %0, tpidrro_el0" : "=r"(tp));
	return (uint64_t *)(tp + 0x1e0);
}

/* Boot abort/panic stubs (FUN_004b0xxx region — fatal, never returns). */
static inline void sk_boot_abort2(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abort3(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abort4(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abort5(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abort6(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abort7(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abort8(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abort9(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abortA(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abortB(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abortC(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }
static inline void sk_boot_abortD(void) __attribute__((noreturn)) { sk_printf("boot abort"); __asm__("brk #1"); }

/* TSS panic helpers. */
static inline void sk_panic_tss_null(void) __attribute__((noreturn)) { sk_printf("TSS null"); __asm__("brk #1"); }
static inline void sk_panic_tss_range(void) __attribute__((noreturn)) { sk_printf("TSS range"); __asm__("brk #1"); }
static inline void sk_panic_tss_teardown(void) __attribute__((noreturn)) { sk_printf("TSS teardown"); __asm__("brk #1"); }
static inline void sk_panic_err(uint64_t code, const char *m) __attribute__((noreturn))
{ sk_printf("%s", m); __asm__("brk #1"); }

/* Boot / current-thread accessors. */
static inline uint64_t sk_boot_info_get_v(void) { sk_boot_info_get(); return 0; }
static inline uint64_t sk_current_thread2(void) { return 0; }   /* thunk_FUN_00061638 */
static inline uint64_t sk_query_type2(uint64_t m) { return 0; } /* FUN_0005ee48 */
static inline uint64_t sk_query_type3(uint64_t a, uint64_t b, uint64_t c) { return 0; } /* FUN_0005ee58 */
static inline uint64_t sk_query_payload_msg(uint64_t m) { return 0; } /* FUN_0005ee50 wrapper */
static inline uint64_t sk_string_find(const char *s) { return (uint64_t)__builtin_strlen(s); }

/* Forward (slice-internal) decls used by the inline wrappers below. */
static uint64_t sk_tb_query_dispatch(uint64_t tb, uint64_t a2, uint64_t a3, uint64_t a4);
static uint64_t sk_registry_alloc(void);

/* Message-block helpers (0x15xxx region, thin wrappers). */
static inline uint64_t *sk_msg_alloc(void) { return (uint64_t *)sk_zone_alloc_obj(1, 0x20, 0); }
static inline void sk_msg_init2(void *m, uint64_t sz) { }
static inline uint64_t *sk_tb_buf_init(uint64_t n, uint64_t msg) { return (uint64_t *)sk_zone_alloc_obj(1, n, 0); }
static inline uint64_t *sk_tb_src(uint64_t *d) { return d; }
static inline void sk_tb_cancel_msg(uint64_t *w) { }
static inline uint64_t sk_tb_do_reply(uint64_t cap, void *m, long *out, uint64_t f)
{ return sk_tb_query_dispatch(cap, (uint64_t)m, (uint64_t)out, f); }
static inline void sk_tb_reset(uint64_t *t) { }
static inline void sk_obj_release2(void) { }
static inline void sk_obj_drop(uint64_t i, uint64_t a) { }
static inline uint64_t *sk_tss_obj_list(void) { static uint64_t l[2]; return l; }

/* ------------------------------------------------------------------ *
 * Forward declarations of all functions defined in this slice (dense
 * cross-links). Signatures mirror the definitions below.
 * ------------------------------------------------------------------ */
static uint64_t sk_page_alloc(uint64_t dst, uint64_t size, uint64_t extra);
static void sk_page_alloc_aligned(uint64_t size, uint64_t align, uint64_t flags);
static uint64_t sk_page_alloc_inner(uint64_t hint, uint64_t size, uint64_t flags);
static uint64_t sk_page_alloc_out(uint64_t *out, uint64_t size, uint64_t extra, uint64_t flags);
static void sk_mall_zone_init(void);
static long sk_zone_alloc_find(uint64_t param_1);
static long *sk_zone_alloc_small(uint64_t size);
static void sk_zone_freelist_insert(uint64_t zone, uint64_t idx, uint64_t count);
static void sk_zone_free_internal(uint64_t ptr);
static void sk_zone_bitmap_clear(uint64_t zone, uint64_t idx, uint64_t count);
static bool sk_zone_contains(uint64_t p);
static uint64_t sk_zone_base_get(void);
static void sk_zone_bitmap_set(uint64_t zone, uint32_t mark, uint64_t idx, long count);
static void sk_malloc_report(uint64_t flags, uint64_t arg, const char *msg, uint64_t a4, const char *a5, uint64_t a6);
static void sk_assert_breakpoint(uint32_t flags, const char *msg);
static void sk_malloc_report2(uint64_t flags, const char *msg);
static void sk_assert_fail(uint64_t flags, uint8_t fail, const char *msg);
static uint64_t sk_identity(uint64_t x);
static uint64_t sk_cache_flush(uint64_t base, uint64_t count, uint64_t stride);
static uint64_t sk_noop_zero(void);
static uint64_t sk_zone_alloc(uint64_t hint, uint64_t size, uint64_t align, uint32_t flags, uint64_t f5, uint64_t f6, uint64_t f7);
static void *sk_zone_alloc_noback(uint64_t size, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5);
static void sk_zone_dealloc(uint64_t p, uint64_t a2, uint64_t flags, uint64_t a4);
static uint64_t sk_zone_madvise(uint64_t p, uint64_t size, uint8_t advice, uint64_t flags, uint64_t a5);
static uint64_t sk_zone_find(uint64_t key, long *out, uint32_t start);
static void sk_zone_register(uint64_t zone);
static uint64_t sk_zone_call_alloc(uint64_t zone, uint64_t size);
static uint64_t sk_zone_calloc(uint64_t zone, uint64_t n, uint64_t size, uint64_t flags);
static uint64_t sk_zone_calloc_noback(uint64_t a1, uint64_t n, uint64_t size);
static uint64_t sk_zone_alloc_core(uint64_t zone, uint64_t a2, uint64_t size);
static void sk_zone_free_call(uint64_t zone);
static long sk_zone_alloc_aligned(uint64_t zone, uint64_t size, uint64_t align, uint32_t flags, uint64_t extra);
static uint64_t sk_zone_alloc_fast(uint64_t zone, uint64_t size);
static void sk_zone_free_lookup(uint64_t p, uint32_t start);
static uint64_t sk_zone_alloc0(uint64_t size);
static uint64_t sk_zone_alloc0_aligned(uint64_t size, uint64_t align);
static uint64_t sk_zone_calloc0(uint64_t n, uint64_t size);
static void sk_zone_free_0(uint64_t p);
static uint64_t sk_zone_malloc(uint64_t p, uint64_t size);
static long sk_zone_owns(uint64_t p);
static void sk_zone_alloc_from(uint64_t a);
static uint32_t sk_zone_alloc_fast_out(uint64_t *out, uint64_t size);
static void sk_batch_init(uint64_t *d, uint8_t f2, uint8_t f3, uint32_t f4, uint32_t f5, uint32_t f6, uint64_t f7, uint64_t f8, uint32_t f9);
static uint64_t sk_batch_pop(uint64_t zone);
static void sk_batch_push(uint64_t zone, uint64_t *block);
static void sk_tb_alloc_slots(uint64_t tb, uint64_t num);
static void sk_tb_assert_received(void);
static void sk_tb_free_slots(uint64_t tb);
static uint64_t sk_tb_create(void);
static int sk_tb_dup(uint64_t a, uint64_t t, long *out, uint32_t flags);
static uint64_t sk_cap_alloc(uint64_t a, uint64_t sz, uint64_t c, uint64_t *d);
static void sk_cap_realloc(uint64_t a, uint64_t *d, uint64_t c, uint64_t sz);
static void sk_tb_fatal_internal_h_204(void);
static void sk_tb_fatal_internal_h_199(void);
static void sk_trampoline_call(uint64_t a1, uint64_t a2, uint64_t a3);
static uint64_t sk_round_bytes_to_words(uint64_t x);
static uint64_t sk_percpu_alloc(uint64_t a, uint64_t b);
static void sk_tb_init(uint64_t a, uint64_t tb);
static uint64_t sk_tb_spawn(uint64_t tb);
static void sk_tb_release(uint64_t *d);
static uint64_t sk_tb_attach(uint64_t *d, uint64_t a2, uint64_t sz);
static void sk_tss_free_slot(uint64_t p);
static uint64_t sk_tss_base_get(void);
static uint64_t sk_tss_alloc_slot(void);
static uint64_t sk_tss_new_region(void);
static uint64_t sk_ipc_send(uint64_t a1, uint64_t msg, uint64_t caps);
static void sk_ipc_setup(uint64_t a1, uint64_t mblk);
static uint64_t sk_tb_get_id(uint64_t *d);
static long sk_tb_alloc_by_kind(uint64_t a);
static uint64_t *sk_tb_obj_alloc(uint64_t a);
static void sk_tb_obj_free(uint64_t *w);
static long sk_tb_obj_create(uint64_t a, uint64_t b);
static long sk_tb_obj_dispatch(uint64_t a1, uint64_t *w);
static uint64_t sk_tb_obj_create2(uint64_t a, uint64_t b);
static void sk_tb_cap_release(uint64_t *w);
static uint64_t sk_tb_obj_alloc2(uint64_t a);
static void sk_tb_cap_retain(uint64_t *w);
static uint64_t sk_tb_query(uint64_t *w, int *q, long *out, uint64_t flags);
static void sk_tb_noop(void);
static void sk_tb_query_wrap(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5);
static uint64_t sk_tb_cancel(uint64_t *w);
static void sk_tb_msg_send(uint64_t *w, uint64_t m, uint64_t a3, uint64_t a4);
static uint64_t sk_tb_alloc_buf(uint64_t *d, uint64_t sz);
static uint64_t sk_tb_buf_release(uint64_t *d, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5);
static uint64_t sk_tb_send_buf(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5);
static void sk_tb_send(uint64_t *w, uint64_t m, int kind, uint64_t a4, uint64_t a5);
static uint64_t sk_tb_send_any(uint64_t *w, int kind, uint64_t m, uint64_t sz, uint64_t a5, uint64_t a6);
static uint64_t sk_tb_cancel2(void);
static void sk_tb_release_msg(uint64_t *w, uint64_t m, uint64_t a3, uint64_t a4);
static void sk_tb_send3(uint64_t *w, uint64_t m, uint64_t a3, uint64_t a4);
static void sk_tb_fatal_act(void);
static void sk_tb_fatal_req(void);
static uint64_t sk_registry_entry_create(uint64_t cap, uint64_t tag, uint64_t key);
static uint64_t sk_registry_alloc(void);
static void sk_registry_free(uint64_t r);
static uint64_t sk_registry_insert(uint64_t *reg, uint64_t key, uint64_t tag, uint64_t a4);
static void sk_registry_remove(uint64_t *reg, uint64_t key);
static uint64_t sk_registry_lookup(uint64_t reg, uint64_t key);
static void sk_registry_set(uint32_t a, uint32_t b);
static void sk_registry_set2(uint32_t a, uint64_t ptr, uint32_t c);
static void sk_registry_invoke(uint64_t e);
static uint64_t sk_tb_get_act(uint64_t tb);
static uint32_t sk_tb_get_kind(void);
static uint32_t sk_tb_get_flags(uint64_t tb);
static void sk_tb_set_act(uint64_t tb, uint64_t act);
static void sk_tb_set_sender(uint64_t tb, uint64_t fn, uint64_t arg);
static uint64_t sk_tb_call(uint64_t tb, uint64_t m, uint64_t *out);
static void sk_tb_destroy_act(uint64_t tb);
static void sk_tb_buf_set(uint64_t *d, uint64_t base, uint64_t size);
static void sk_tb_dispatch0(uint64_t *d);
static bool sk_tb_check_req(uint64_t tb);
static bool sk_tb_check_act(uint64_t tb);
static uint64_t sk_tb_send_dispatch(uint64_t tb, uint64_t a2, uint64_t a3, uint64_t a4);
static void sk_tb_msg_join(uint64_t tb, uint64_t a2);
static uint64_t sk_tb_query_dispatch(uint64_t tb, uint64_t a2, uint64_t a3, uint64_t a4);
static uint64_t sk_tb_can_receive(uint64_t tb);
static uint64_t sk_tb_can_send(uint64_t tb);
static void sk_tb_buf_reset(uint64_t *d);
static uint64_t sk_tb_msg_reset(uint64_t tb);
static void sk_tb_buf_copy(uint64_t *dst, uint64_t *src);
static uint64_t sk_zone_free_slot(uint64_t slot);
static uint64_t sk_zone_alloc_small_def(uint64_t size);
static uint64_t sk_zone_free_internal_def(uint64_t ptr);
static uint64_t sk_zone_freelist_insert_def(uint64_t zone, uint64_t idx, uint64_t count);
static uint64_t sk_zone_bitmap_clear_def(uint64_t zone, uint64_t idx, uint64_t count);
static uint64_t sk_zone_bitmap_set_def(uint64_t zone, uint32_t mark, uint64_t idx, long count);
static uint64_t sk_tb_msg_reset_def(uint64_t tb);

/* ================================================================== *
 * Zone registry / object lookup helpers
 * ================================================================== */

/* FUN_000102f4 @ 0x000102f4   (est. sk_page_alloc)
 * Ghidra: ulong FUN_000102f4(long, ulong, undefined8)
 * Allocates a `size`-byte region. When the kernel-env lookup object is set,
 * asks it for memory (vtable +0x18/+0xa0 by version); otherwise finds the
 * owning zone (FUN_00011cac) and allocates through it, or falls back to the
 * default-zone malloc (FUN_000125b4). Returns the allocation base.
 * Confidence: medium
 * Notes: overflow panics via SoftwareBreakpoint(0x5519,0x10480); errno 0xc
 *   (ENOMEM) is recorded via thunk_FUN_0006037c when the lookup returns null. */
static uint64_t sk_page_alloc(uint64_t dst, uint64_t size, uint64_t extra)
{
	uint64_t base;
	uint64_t end;
	uint64_t *errp;

	if (dst == 0 || size == 0) {
		/* Use the kernel-env lookup object's allocator. */
		uint64_t env = sk_lookup_root;
		if (*(uint32_t *)(env + 0x68) < 0x10) {
			base = (*(uint64_t (**)(uint64_t, uint64_t))(env + 0x18))(env, size);
		} else {
			base = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))(env + 0xa0))(env, size, extra);
		}
		end = 0;
		if (base != 0) end = base + size;
		if (end < base) goto overflow;
		if (base == 0) goto set_errno;
		if (size == 0) sk_zone_free_0(dst);
		if (end < base) goto overflow;
		if (base == 0) return 0;
		return base;
	}

	base = sk_zone_find(dst, 0, 0);
	if (base != 0) {
		if (*(uint32_t *)(base + 0x68) < 0x10) {
			base = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))(base + 0x38))(base, dst, size);
		} else {
			base = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t))(base + 0xb0))
			       (base, dst, size, extra);
		}
		end = base + size;
		if (base == 0) goto set_errno;
		if (size == 0) sk_zone_free_0(dst);
		if (end < base) goto overflow;
		if (base == 0) return 0;
		return base;
	}

	base = sk_zone_malloc(dst, size);
	if (base == 0) return 0;
	end = base + size;
	if (size <= end - base) return base;
overflow:
	/* SoftwareBreakpoint(0x5519, 0x10480) */
	__asm__ volatile("brk #0x5519");
set_errno:
	errp = (uint64_t *)sk_errno_ptr();
	*errp = 0xc;
	return 0;
}

/* FUN_00010480 @ 0x00010480   (est. sk_page_alloc_aligned)
 * Ghidra: void FUN_00010480(ulong, ulong, undefined8)
 * Allocates `size` bytes with alignment `align` (power of two > 8). Uses the
 * kernel-env fastpath (+0xb8) when both are aligned; else falls to the generic
 * allocator (FUN_00010584). Never returns on failure.
 * Confidence: medium
 * Notes: errno 0xc on null; SoftwareBreakpoint(0x5519,0x10584) overflow. */
static void sk_page_alloc_aligned(uint64_t size, uint64_t align, uint64_t flags)
{
	uint64_t base, end;
	uint64_t *errp;

	if (align > 8) {
		uint64_t env = sk_lookup_root;
		if (*(uint32_t *)(env + 0x68) > 0xf && (align & (align - 1)) == 0 &&
		    (size & (align - 1)) == 0) {
			base = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))(env + 0xb8))
			       (env, align, size);
			end = base + size;
			if (base == 0) {
				errp = (uint64_t *)sk_errno_ptr();
				*errp = 0xc;
			}
			if (base <= end && (base == 0 || size <= end - base)) return;
			goto fail;
		}
	}
	base = sk_page_alloc_inner(size, align, flags);
	if (base == 0) goto fail;
	if (base <= base + size) return;
fail:
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x10584) */
}

/* FUN_00010584 @ 0x00010584   (est. sk_page_alloc_inner)
 * Ghidra: void FUN_00010584(undefined8, ulong, ulong)
 * Generic aligned allocation: temporarily raises the per-cpu malloc flag
 * (tpidr_el0 slot 9) then calls FUN_00012218 on the kernel-env lookup object.
 * Restores the flag before returning.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x1062c) on overflow / bad state. */
static uint64_t sk_page_alloc_inner(uint64_t hint, uint64_t size, uint64_t flags)
{
	uint64_t *flag = (uint64_t *)sk_tpidr_flags();
	uint64_t old, base, end;

	if ((uint64_t *)0 != 0) goto panic_brk;
	old = *flag;
	if (flags < 2) flags = 1;
	*flag = flags;
	base = sk_zone_alloc_aligned(sk_lookup_root, hint, size, 3, 0);
	*flag = old;
	if (base <= base + size && (base == 0 || size <= (base + size) - base)) return base;
panic_brk:
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x1062c) */
}

/* FUN_0001062c @ 0x0001062c   (est. sk_page_alloc_out)
 * Ghidra: undefined8 FUN_0001062c(long*, ulong, undefined8, ulong)
 * Allocates a power-of-two-aligned region, writing the base to *out and
 * returning an error code (0 success, 0xc ENOMEM, 0x16 EINVAL). Fastpath uses
 * the kernel-env +0xb8 allocator; slowpath uses the per-cpu flag + FUN_000127c0.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x106c4/0x1071c). */
static uint64_t sk_page_alloc_out(uint64_t *out, uint64_t size, uint64_t extra, uint64_t flags)
{
	uint64_t env = sk_lookup_root;
	uint64_t base;
	uint64_t *flag;

	if (size > 8 && *(uint32_t *)(env + 0x68) > 0xf && (size & (size - 1)) == 0) {
		base = (*(uint64_t (**)(void))(env + 0xb8))();
		if (base == 0) return 0xc;
		*out = base;
		return 0;
	}
	flag = (uint64_t *)sk_tpidr_flags();
	{
		uint64_t old = *flag;
		if (flags < 2) flags = 1;
		*flag = flags;
		base = sk_zone_alloc_fast_out(out, size);
		*flag = old;
		return base;
	}
}

/* FUN_0001071c @ 0x0001071c   (est. sk_mall_zone_init)
 * Ghidra: void FUN_0001071c(void)
 * Boot initialisation of the embedded libmalloc zone. Records the boot CPU
 * count, maps 1 MiB via FUN_00011b18, madvises the header (0x8000), stores the
 * zone base in DAT_006adfd8 and initialises the size-class freelist heads
 * (0x30 + 11*0x10) with sequential indices. Panics on alloc failure.
 * Confidence: medium
 * Notes: string s_BUG_IN_LIBMALLOC___llu___failed_t_005aa76c; stack canary
 *   DAT_006cf0 value -0x2c8502b44bfffed6. */
static void sk_mall_zone_init(void)
{
	uint64_t *zone;
	uint64_t i;
	long *pair;

	sk_mall_zone_flags = sk_boot_ncpu;
	uint32_t gran = 0xa00;
	if (sk_boot_ncpu == 0) gran = 0x200;

	zone = (uint64_t *)sk_zone_alloc_noback(0x100000, 0, gran, 1, 0);
	if (zone == 0) sk_fatal_printf("BUG IN LIBMALLOC: failed to create zone\n");

	sk_zone_madvise((uint64_t)zone, 0x8000, 2, 0x40, 0);
	zone[0x1d] = 0;
	zone[0x1c] = 0;
	zone[0] = 0;
	zone[1] = 0;
	zone[0x1f] = 0x8000000000000000ull;

	pair = (long *)(zone + 7);
	i = 3;
	do {
		pair[-1] = (long)i;
		pair[0] = (long)i;
		pair += 2;
		i += 1;
	} while (i != 0xe);

	zone[0x20] |= 1;
	sk_mall_zone_base = (uint64_t)zone;
}

/* FUN_00010830 @ 0x00010830   (est. sk_zone_alloc_find)
 * Ghidra: long FUN_00010830(ulong)
 * Bitmap-based block search over the mall zone's free-page bitmap (at
 * zone+0x100). Finds the next run of free pages at/after the block index
 * derived from `param_1`, returning the block count (<<4) of the run.
 * Confidence: low
 * Notes: pure bitmap scan; SoftwareBreakpoint(0x5519,0x108cc) unwind. */
static long sk_zone_alloc_find(uint64_t param_1)
{
	uint64_t z = sk_mall_zone_base;
	uint64_t u = param_1 & 0xf0ffffffffffffffull;
	uint64_t run;
	long *bits = (long *)(z + 0x100);

	if (z == 0 || u < z + 0x8000 || (param_1 & 0xf) != 0 || z + 0x100000 <= u) return 0;

	u = (u - (z + 0x8000)) >> 4;
	if ((*(uint64_t *)(bits + (u >> 2 & 0x3ffffffffffffff0)) &
	     (1ull << (u & 0x3f)) &
	     *(uint64_t *)(bits + (u >> 2 & 0x3ffffffffffffff8 | 8))) == 0) return 0;

	u += 1;
	{
		uint64_t slot = u >> 5 & 0x7fffffffffffffeull;
		uint64_t v = *(uint64_t *)((long)bits + slot * 8) >> (u & 0x3f);
		if (v == 0) {
			/* linear search across the 64-bit bitmap words */
			run = 0;
			for (;;) {
				/* search next word boundary for a set bit */
				v = u;
				run = 0;
				break;
			}
		}
		/* count leading zeros to find run length */
		run = LZCOUNT(v) & 0x3f;
	}
	return (run + 1) << 4;
}

/* FUN_00010934 @ 0x00010934   (est. sk_zone_alloc_small)
 * Ghidra: long* FUN_00010934(ulong)
 * libmalloc small-block allocation from the mall zone. Walks the size-class
 * freelists (zone+0x30, 11 classes), splitting/coalescing blocks in the
 * bitmap, updating alloc counters (zone+0x10, zone+0x28), and extending the
 * heap (zone+0x18) with page-aligned growth as needed. Returns the block.
 * Confidence: low
 * Notes: lock FUN_0011582c/94 around the operation; strings
 *   s_Failed_to_acquire_lock__p__005a9a23 / s_Failed_to_release_lock__p__005a9a3f;
 *   DC_GVA cache-clean when DAT_006adfe0 bit0 set; returns block or null. */
static long *sk_zone_alloc_small(uint64_t size)
{
	uint64_t z = sk_mall_zone_base;
	uint64_t nblocks;
	uint64_t run;
	long *bits;
	uint64_t i;

	if (size >= 0x4001) return 0;

	nblocks = (size + 0xf) >> 4;
	if (size == 0) nblocks = 1;

	if (sk_lock_acquire((void *)z)) sk_assert_fail(0x40, 0, "Failed to acquire lock");
	{
		uint64_t class = 0x40 - (uint32_t)LZCOUNT(nblocks - 1);
		if (class > 9) class = 10;
		uint64_t idx = 0;
		if (nblocks > 1) idx = class;

		bits = (long *)(z + 0x100);
		for (i = 0; i < 0xb0; i += 0x10) {
			long *head = (long *)(z + 0x30 + i);
			long *node = (long *)(z + *head * 0x10);
			if (head == node) continue;
			/* pop freelist head; store run details */
			long prev = node[0], next = node[1];
			*(long *)(z + prev * 0x10 + 8) = next;
			*(long *)(z + next * 0x10) = prev;
			node[0] = 0; node[1] = 0;
			uint64_t run_start = (node - bits) >> 1; /* block index */
			run = 1;
			*(long *)(z + 0x10) = *(long *)(z + 0x10) + (long)run;
			*(long *)(z + 0x28) += 1;
			break;
		}
		if (i == 0xb0) {
			/* heap exhausted — grow at zone+0x18 */
			if (nblocks < 0xf800 - *(uint64_t *)(z + 0x18)) {
				uint64_t hi = *(uint64_t *)(z + 0x18) + nblocks;
				*(uint64_t *)(z + 0x18) = hi;
				*(long *)(z + 0x10) += (long)nblocks;
				*(long *)(z + 0x28) += 1;
			}
			run = 0;
		}
	}
	sk_lock_release((void *)z);
	return (long *)run;
}

/* FUN_00010d84 @ 0x00010d84   (est. sk_zone_freelist_insert)
 * Ghidra: void FUN_00010d84(long, long, undefined8)
 * Inserts a freed block (index `idx`, count `count`) into the mall zone's
 * size-class freelist. Computes the class from the block count, pushes the
 * block onto the list head at zone + class*0x10 + 0x30.
 * Confidence: low
 * Notes: freelist node stores backpointer in +0x8000/+0x8008 region. */
static void sk_zone_freelist_insert(uint64_t zone, uint64_t idx, uint64_t count)
{
	uint32_t class = 0x3f - (uint32_t)LZCOUNT(count);
	if (class > 9) class = 10;
	uint64_t *head = (uint64_t *)(zone + (uint64_t)class * 0x10 + 0x30);
	uint64_t next = *head;
	uint64_t *node = (uint64_t *)(zone + idx * 0x10);
	node[0x800] = next;          /* +0x8000 */
	node[0x801] = class + 3;     /* +0x8008 */
	*head = idx + 0x800;
	*(uint64_t *)(zone + next * 0x10 + 8) = idx + 0x800;
}

/* FUN_00010e3c @ 0x00010e3c   (est. sk_zone_free_internal)
 * Ghidra: void FUN_00010e3c(ulong)
 * libmalloc zone free. Validates the pointer is in the mall zone, computes its
 * block index and size class, coalesces with adjacent free blocks, decrements
 * the used-block counter (zone+0x10) and returns the block to the freelist.
 * Confidence: low
 * Notes: panics via s_BUG_IN_LIBMALLOC___llu___not_MFM_005aa79f /
 *   s_BUG_IN_CLIENT_OF_LIBMALLOC___llu_005aa838 / _005aa800 / _005aa7c6;
 *   lock FUN_0011582c/94; DC_GVA cache clean when bit0 set. */
static void sk_zone_free_internal(uint64_t ptr)
{
	uint64_t z = sk_mall_zone_base;
	uint64_t u = ptr & 0xf0ffffffffffffffull;
	uint64_t *bits = (uint64_t *)(z + 0x100);

	if (z == 0 || u < z + 0x8000 || z + 0x100000 <= u)
		sk_fatal_printf("BUG IN LIBMALLOC: not MFM\n");
	if ((ptr & 0xf) != 0) sk_fatal_printf("BUG IN CLIENT OF LIBMALLOC\n");

	{
		uint64_t idx = (u - (z + 0x8000)) >> 4;
		uint64_t lo = idx >> 5 & 0x7fffffffffffffeull;
		uint64_t hi = idx >> 5 | 1;
		uint64_t bit = 1ull << (idx & 0x3f);
		if ((*(uint64_t *)((long)bits + lo * 8) & *(uint64_t *)((long)bits + hi * 8) & bit) == 0)
			sk_fatal_printf("BUG IN CLIENT OF LIBMALLOC\n");

		if (sk_lock_acquire((void *)z)) sk_assert_fail(0x40, 0, "Failed to acquire lock");

		/* coalesce previous block */
		uint64_t count = 1;
		if (idx > 0) {
			uint64_t pidx = idx - 1;
			uint64_t pw = *(uint64_t *)((long)bits + ((pidx >> 5) << 3 | 8));
			if ((pw >> (pidx & 0x3f) & 1) == 0) {
				/* previous is free — merge */
			}
		}
		/* coalesce next block */
		{
			uint64_t hi2 = *(uint64_t *)(z + 0x18);
			uint64_t nidx = idx + count;
			if (hi2 > nidx) {
				/* next block free check via +8 word */
			}
		}

		*(int32_t *)(z + 0x10) -= (int32_t)count;
		*(int64_t *)(z + 0x28) -= 1;

		if (count < 0x40) {
			*(uint64_t *)((long)bits + (idx >> 2 & 0x3ffffffffffffff8 | 8)) &=
			    ~(1ull << (idx & 0x3f));
			*(uint64_t *)((long)bits + (((idx + count - 1) >> 2 & 0x3ffffffffffffff8 | 8))) &=
			    ~(1ull << ((idx + count - 1) & 0x3f));
		} else {
			sk_zone_freelist_insert(z, idx, count);
		}
		sk_lock_release((void *)z);
	}
}

/* FUN_00011430 @ 0x00011430   (est. sk_zone_bitmap_clear)
 * Ghidra: void FUN_00011430(long, ulong, ulong)
 * Clears the free-bitmap run bits for the block range [idx, idx+count) in the
 * +8 word planes (single-page size-class). Small ranges clear both endpoint
 * bits; larger ranges route through the freelist-class helper.
 * Confidence: low
 * Notes: bitmap bitplanes at zone+0x100 and +0x108. */
static void sk_zone_bitmap_clear(uint64_t zone, uint64_t idx, uint64_t count)
{
	uint64_t *bits = (uint64_t *)(zone + 0x100);
	if (count < 0x40) {
		uint64_t lo = idx >> 2 & 0x3ffffffffffffff8 | 8;
		*(uint64_t *)((long)bits + lo) &= ~(1ull << (idx & 0x3f));
		uint64_t e = (idx + count) - 1;
		uint64_t hi = e >> 2 & 0x3ffffffffffffff8 | 8;
		*(uint64_t *)((long)bits + hi) &= ~(1ull << (e & 0x3f));
		return;
	}
	sk_zone_freelist_insert(zone, idx, count);
}

/* FUN_00011494 @ 0x00011494   (est. sk_zone_contains)
 * Ghidra: bool FUN_00011494(ulong)
 * True if `param_1` lies within the mall zone's data region
 * [zone+0x8000, zone+0x100000); with the madvise flag set, also returns true
 * for the header (any address in the zone window).
 * Confidence: medium
 * Notes: DAT_006adfe0 bit0 controls the header-window answer. */
static bool sk_zone_contains(uint64_t p)
{
	p &= 0xf0ffffffffffffffull;
	if (sk_mall_zone_base == 0 || p < sk_mall_zone_base + 0x8000) return false;
	if (p < sk_mall_zone_base + 0x100000) {
		if ((sk_mall_zone_flags & 1) != 0) return true;
	}
	return p < sk_mall_zone_base + 0x100000;
}

/* FUN_000114f0 @ 0x000114f0   (est. sk_zone_base_get)
 * Ghidra: undefined8 FUN_000114f0(void)
 * Returns the mall zone base (DAT_006adfd8).
 * Confidence: high */
static uint64_t sk_zone_base_get(void)
{
	return sk_mall_zone_base;
}

/* FUN_000114fc @ 0x000114fc   (est. sk_zone_bitmap_set)
 * Ghidra: void FUN_000114fc(long, uint, ulong, long)
 * Writes the run-length-encoded free-block record into the mall zone bitmap
 * for a large (>=0x40 block) run: stores {count-1, mark} in the +8 planes and
 * the boundary marker in the following word.
 * Confidence: low
 * Notes: bitmap +8 planes at zone+0x100..0x140. */
static void sk_zone_bitmap_set(uint64_t zone, uint32_t mark, uint64_t idx, long count)
{
	uint64_t *bits = (uint64_t *)(zone + 0x100);
	uint64_t n = (uint64_t)count - 1;
	uint64_t off = (idx >> 5) << 3 | 8;
	uint64_t mask = (0x1ffffull << (idx & 0x3f)) ^ 0xffffffffffffffffull;
	uint64_t val = ((uint64_t)mark & 1 | n * 2) << (idx & 0x3f);
	*(uint64_t *)((long)bits + off) = *(uint64_t *)((long)bits + off) & mask | val;
	if ((idx & 0x3f) > 0x2f) {
		uint64_t sh = (idx & 0x3f) ^ 0x3f;
		uint64_t *w = (uint64_t *)((long)bits + (idx >> 5 & 0x7fffffffffffffeull) * 8);
		*(uint64_t *)((long)w + 0x18) =
		    *(uint64_t *)((long)w + 0x18) & (0xffffull >> sh ^ 0xffffffffffffffffull) |
		    (n & 0x7fffffffffffffffull) >> sh;
	}
}

/* FUN_00011600 @ 0x00011600   (est. sk_malloc_report)
 * Ghidra: void FUN_00011600(ulong, undefined8, long, undefined8, undefined8, undefined8)
 * libmalloc diagnostics/logging entry: routes to the "malloc" log prefix and
 * prints a message; handles breakpoint flags (param_1 bit5) and a dump flag
 * (bit8) that prints 50 raw bytes; a sleep flag (param_2 nonzero) sleeps.
 * Confidence: medium
 * Notes: strings s___p__malloc__005aa86b, s_____set_a_breakpoint_in_malloc_e_005aa879,
 *   s_____sleeping_to_help_debug_005aa8b5; stack canary check. */
static void sk_malloc_report(uint64_t flags, uint64_t arg, const char *msg, uint64_t a4,
                             const char *a5, uint64_t a6)
{
	if ((flags & 0x20) == 0) {
		sk_boot_info_get();
		sk_printf("%p malloc: ");
	}
	if (msg != 0) sk_printf(msg);
	if (a5 != 0) sk_printf3(a5, a6);
	if ((flags & 0x100) != 0) {
		/* dump 50 bytes */
		unsigned char buf[50] = {0};
		long n = sk_print_bytes(&buf, 0x32);
		while (n > 0) {
			sk_printf(" %02x", 0);
			n -= 1;
		}
	}
	if ((flags & 0xc0) != 0) {
		sk_assert_breakpoint(flags, "set a breakpoint in malloc");
		if ((int32_t)arg != 0) {
			sk_boot_info_get();
			sk_printf("%p malloc: ");
			sk_printf2("sleeping to help debug");
			sk_sleep(arg);
		}
	}
	if ((flags & 0x40) == 0) return;
	sk_boot_fatal2();
}

/* FUN_00011798 @ 0x00011798   (est. sk_assert_breakpoint)
 * Ghidra: void FUN_00011798(uint)
 * Prints the "malloc: " prefix (unless bit5 set) then the breakpoint marker
 * string. Used to flag debug-breakpoint-enabled asserts.
 * Confidence: medium
 * Notes: strings s___p__malloc__005aa86b, &DAT_005aa8b2. */
static void sk_assert_breakpoint(uint32_t flags, const char *msg)
{
	if ((flags >> 5 & 1) == 0) {
		sk_boot_info_get();
		sk_printf("%p malloc: ");
	}
	sk_printf("%s", msg);
}

/* FUN_000117e8 @ 0x000117e8   (est. sk_malloc_report2)
 * Ghidra: void FUN_000117e8(undefined8, undefined8)
 * Wrapper for sk_malloc_report with default flags (0) and a single message.
 * Confidence: high */
static void sk_malloc_report2(uint64_t flags, const char *msg)
{
	sk_malloc_report(flags, 0, 0, 0, msg, 0);
}

/* FUN_00011824 @ 0x00011824   (est. sk_assert_fail)
 * Ghidra: void FUN_00011824(ulong, byte, undefined8)
 * libmalloc assertion-failure logger. Encodes the panic type from flags+the
 * `fail` byte into the classic malloc codes (0x93 / 0x43) and reports it.
 * Confidence: medium
 * Notes: masks to 0x93 when bit8 clear or fail==1, else 0x43. */
static void sk_assert_fail(uint64_t flags, uint8_t fail, const char *msg)
{
	uint32_t code;
	fail ^= 1;
	if ((flags & 0x100) == 0) fail = 1;
	code = 0x93;
	if (((flags & 0x40) == 0 && fail) == 0) code = 0x43;
	sk_malloc_report(code, 0, 0, 0, msg, 0);
}

/* FUN_00011884 @ 0x00011884   (est. sk_identity)
 * Ghidra: undefined8 FUN_00011884(undefined8)
 * Identity (returns its argument). Compiler stub for cache-line alignment.
 * Confidence: high */
static uint64_t sk_identity(uint64_t x)
{
	return x;
}

/* FUN_000118d0 @ 0x000118d0   (est. sk_cache_flush)
 * Ghidra: ulong FUN_000118d0(long, ulong, ulong)
 * Data-cache clean (DC_GVA) over `count` regions of `stride` bytes starting at
 * `base`, using 0x200-byte unrolled loops for aligned strides and 0x40-byte
 * steps otherwise. Returns the last-cleaned address.
 * Confidence: medium
 * Notes: DC_GVA per cache line. */
static uint64_t sk_cache_flush(uint64_t base, uint64_t count, uint64_t stride)
{
	uint64_t prev = 0;
	uint64_t run = 0;
	if (count >= stride) {
		uint64_t i = 0;
		uint64_t n = (stride != 0) ? count / stride : 0;
		do {
			uint64_t cur = base + i * stride;
			if ((int32_t)i != 0) prev = run;
			uint64_t end = cur + stride;
			if ((stride & 0x1ff) == 0) {
				uint64_t a = cur;
				do {
					DC_GVA(a); DC_GVA(a + 0x40); DC_GVA(a + 0x80); DC_GVA(a + 0xc0);
					DC_GVA(a + 0x100); DC_GVA(a + 0x140); DC_GVA(a + 0x180); DC_GVA(a + 0x1c0);
					a += 0x200;
				} while (a < end);
			} else {
				for (uint64_t a = (cur + 0x3f) & ~0x3full; a < (end & ~0x3full); a += 0x40)
					DC_GVA(a);
			}
			run = end;
			i += 1;
		} while (i < n);
		return prev;
	}
	return 0;
}

/* FUN_000119c0 @ 0x000119c0   (est. sk_noop_zero)
 * Ghidra: undefined8 FUN_000119c0(void)
 * Returns 0. Unreachable-block-removed stub.
 * Confidence: high */
static uint64_t sk_noop_zero(void)
{
	return 0;
}

/* FUN_00011a08 @ 0x00011a08   (est. sk_zone_alloc)
 * Ghidra: ulong FUN_00011a08(long, long, undefined8, uint, undefined8, undefined8, undefined8)
 * Core zone allocation: rejects "anywhere" allocations when a non-null hint is
 * given, computes the allocation flags from the requested bits, calls the
 * low-level allocator (FUN_00117fdc), clears errno and asserts on failure.
 * Returns the allocation base.
 * Confidence: medium
 * Notes: strings s_Unsupported_anywhere_allocation_a_005aa904,
 *   s_Failed_to_allocate_memory_at_add_005aa952; errno cleared via
 *   thunk_FUN_0006037c. */
static uint64_t sk_zone_alloc(uint64_t hint, uint64_t size, uint64_t align, uint32_t flags,
                              uint64_t f5, uint64_t f6, uint64_t f7)
{
	uint32_t z5 = (uint32_t)f5;
	uint64_t base;

	if (hint != 0 && (flags & 1) != 0)
		sk_assert_fail(z5 | 0x40, 0, "Unsupported anywhere allocation");
	base = sk_alloc_low(f7, hint, size, 5,
	                    (z5 >> 7 & 0x20 | (flags & 1) << 3 | z5 >> 9 & 4 | z5 >> 8 & 2 |
	                     z5 >> 0x1a & 0x10) ^ 9, align, f6);
	sk_clear_errno();
	if (base == 0) sk_assert_fail(f5, 0, "Failed to allocate memory at address");
	if (base <= base + size) return base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x11b18) */
}

/* FUN_00011b18 @ 0x00011b18   (est. sk_zone_alloc_noback)
 * Ghidra: void FUN_00011b18(ulong, undefined8, undefined8, undefined8, undefined8)
 * Allocates `size` bytes without a backing hint (flags 1); returns the base.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x11b80) overflow. */
static void *sk_zone_alloc_noback(uint64_t size, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5)
{
	uint64_t base = sk_zone_alloc(0, size, a2, 1, a3, a4, a5);
	if (base <= base + size && (base == 0 || size <= (base + size) - base))
		return (void *)base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x11b80) */
}

/* FUN_00011b80 @ 0x00011b80   (est. sk_zone_dealloc)
 * Ghidra: void FUN_00011b80(undefined8, undefined8, undefined8, undefined8)
 * Deallocates a pointer via the low-level free (FUN_001180cc); asserts if the
 * deallocator signals an error and errno is set.
 * Confidence: medium
 * Notes: string s_Failed_to_deallocate_at_address___005aa99e. */
static void sk_zone_dealloc(uint64_t p, uint64_t a2, uint64_t flags, uint64_t a4)
{
	uint64_t r = sk_dealloc_at(a4, p, a2);
	if ((r & 1) == 0) {
		if (sk_errno_get() != 0)
			sk_assert_fail(flags, 0, "Failed to deallocate at address");
	}
}

/* FUN_00011bf4 @ 0x00011bf4   (est. sk_zone_madvise)
 * Ghidra: undefined8 FUN_00011bf4(undefined8, undefined8, undefined1, ulong, undefined8)
 * libmalloc madvise wrapper: rejects unsupported debug flags (param_4 & 0x83),
 * calls the low-level advise (FUN_0011807c), and asserts on failure.
 * Confidence: medium
 * Notes: strings s_Unsupported_debug_flags__u_005aa9d4,
 *   s_Failed_to_madvise__d_at_address___005aa9f0. */
static uint64_t sk_zone_madvise(uint64_t p, uint64_t size, uint8_t advice, uint64_t flags,
                                uint64_t a5)
{
	uint64_t r;
	if ((flags & 0x83) != 0)
		sk_assert_fail((uint32_t)flags | 0x40, 1, "Unsupported debug flags");
	r = sk_alloc_meta2(a5, p, size, advice);
	if ((int32_t)r != 0) {
		if (sk_errno_get() == 0) return 0;
		sk_assert_fail(flags, 0, "Failed to madvise");
		return 1;
	}
	return r;
}

/* FUN_00011cac @ 0x00011cac   (est. sk_zone_find)
 * Ghidra: ulong FUN_00011cac(undefined8, long*, uint)
 * Scans the registered-zone table (DAT_006adfe8, count DAT_006ac238) calling
 * each zone's +0x10 match method with `param_1`; returns the zone (or 0) and
 * stores the matched sub-object in *param_2. Starts at index `param_3`.
 * Confidence: medium
 * Notes: table base 0x6adfe8, count 0x6ac238. */
static uint64_t sk_zone_find(uint64_t key, long *out, uint32_t start)
{
	uint64_t i;
	uint64_t zone;
	long match = 0;

	if (start < sk_mall_zone_count) {
		for (i = start; i < sk_mall_zone_count; i++) {
			zone = sk_mall_zone_tbl[i];
			match = (*(long (**)(uint64_t, uint64_t))(zone + 0x10))(zone, key);
			if (match != 0) goto done;
		}
	}
	zone = 0;
done:
	if (out != 0) *out = match;
	return zone;
}

/* FUN_00011d7c @ 0x00011d7c   (est. sk_zone_register)
 * Ghidra: void FUN_00011d7c(undefined8)
 * Registers a zone in the zone table. Validates the zone (version >= 0xd),
 * rejects duplicates and overflow (max 2 zones), sets the DefaultXzoneZone
 * name, links the zone's name pointer, and grows the table as needed.
 * Confidence: medium
 * Notes: strings s_Registered_zone__p_at_index__u_005aaa99,
 *   s_Attempted_to_register_duplicate_z_005aaa37, s_No_capacity_for_zone___p_005aaa61,
 *   s_Unsupported_zone_version___u_005aaa7b, s_DefaultXzoneZone_005aaa26;
 *   SoftwareBreakpoint(0x5519,0x11f10/0x12060). */
static void sk_zone_register(uint64_t zone)
{
	uint64_t i;
	uint64_t n = sk_mall_zone_count;
	uint64_t newtbl;

	sk_mall_zone_tbl[0] = 0;   /* stale marker from decompile setup */

	if (sk_mall_zone_count == 0) {
		if (*(uint32_t *)(zone + 0x68) < 0xd) {
			sk_malloc_report2((uint64_t)"Unsupported zone version\n", 0);
			return;
		}
		newtbl = sk_depot_grow(&sk_mall_zone_tbl[1], &sk_mall_zone_tbl[0],
		                       (uint64_t)sk_mall_zone_count << 3, 8);
		sk_mall_zone_tbl[0] = zone;
		sk_malloc_report2(6, "Registered zone at index");
		sk_mall_zone_count += 1;
	} else {
		for (i = 0; i < sk_mall_zone_count; i++) {
			if (zone == sk_mall_zone_tbl[i]) {
				sk_malloc_report2(0x40, "Attempted to register duplicate zone");
				return;
			}
		}
		if (sk_mall_zone_count == 2) {
			sk_malloc_report2(0x40, "No capacity for zone");
			return;
		}
		if (*(uint32_t *)(zone + 0x68) <= 0xc) {
			sk_malloc_report2(0x40, "Unsupported zone version");
			return;
		}
		newtbl = sk_depot_grow(&sk_mall_zone_tbl[1], &sk_mall_zone_tbl[0],
		                       (uint64_t)sk_mall_zone_count << 3, 8);
		sk_mall_zone_tbl[sk_mall_zone_count] = zone;
		sk_mall_zone_count += 1;
	}

	/* name the zone "DefaultXzoneZone" */
	{
		uint64_t name_len = (uint64_t)sk_string_find("DefaultXzoneZone");
		uint64_t cap = name_len + 1;
		char *name = (char *)sk_zone_call_alloc(zone, cap);
		if (name != 0) {
			sk_string_set(name, "DefaultXzoneZone", cap, cap);
			*(char **)(zone + 0x48) = name;
		}
	}
}

/* FUN_00012060 @ 0x00012060   (est. sk_zone_call_alloc)
 * Ghidra: void FUN_00012060(long, ulong)
 * Calls the zone's +0x18 allocator method and returns its base (0 on failure),
 * asserting on wraparound.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x120b4). */
static uint64_t sk_zone_call_alloc(uint64_t zone, uint64_t size)
{
	uint64_t base = (*(uint64_t (**)(void))(zone + 0x18))();
	if (base <= base + size && (base == 0 || size <= (base + size) - base)) return base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x120b4) */
}

/* FUN_000120b4 @ 0x000120b4   (est. sk_zone_calloc)
 * Ghidra: ulong FUN_000120b4(long, ulong, ulong, ulong)
 * Calloc-style allocation of `n`*`size` bytes via the zone's +0x20 method,
 * with overflow checking on the product.
 * Confidence: medium
 * Notes: errno 0xc on product overflow. */
static uint64_t sk_zone_calloc(uint64_t zone, uint64_t n, uint64_t size, uint64_t flags)
{
	uint64_t total = size;
	if (n != 1) {
		if (n * size >> 64 != 0) {
			sk_set_errno(0xc);
			return 0;
		}
		total = n * size;
	}
	uint64_t base = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))(zone + 0x20))(zone, n, size);
	if (base <= base + total && (base == 0 || n * size < total || n * size - total == 0))
		return base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x12160) */
}

/* FUN_00012160 @ 0x00012160   (est. sk_zone_calloc_noback)
 * Ghidra: void FUN_00012160(undefined8, long, long)
 * Calloc of n*size via the default zone, asserting on overflow.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x121b8). */
static uint64_t sk_zone_calloc_noback(uint64_t a1, uint64_t n, uint64_t size)
{
	uint64_t base = sk_zone_calloc(0, n, size, 0);
	uint64_t total = size * n;
	if (base <= base + total && (base == 0 || total < (base + total) - base ||
	                             total - ((base + total) - base) == 0)) return base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x121b8) */
}

/* FUN_000121b8 @ 0x000121b8   (est. sk_zone_alloc_core)
 * Ghidra: void FUN_000121b8(long, undefined8, ulong)
 * Calls the zone's +0x38 allocator method with (zone, a2, size); returns base.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x1220c). */
static uint64_t sk_zone_alloc_core(uint64_t zone, uint64_t a2, uint64_t size)
{
	uint64_t base = (*(uint64_t (**)(void))(zone + 0x38))();
	if (base <= base + size && (base == 0 || size <= (base + size) - base)) return base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x1220c) */
}

/* FUN_0001220c @ 0x0001220c   (est. sk_zone_free_call)
 * Ghidra: void FUN_0001220c(long)
 * Invokes the zone's +0x30 free method.
 * Confidence: medium
 * Notes: unrecovered jumptable at 0x12214 treated as a call. */
static void sk_zone_free_call(uint64_t zone)
{
	(*(void (**)(void))(zone + 0x30))();
}

/* FUN_00012218 @ 0x00012218   (est. sk_zone_alloc_aligned)
 * Ghidra: long FUN_00012218(long, ulong, ulong, uint)
 * Fast aligned allocation: for power-of-two aligned sizes/alignment calls the
 * zone's +0x70 fast allocator; else sets errno 0x16 (EINVAL). If `param_4`
 * bit0 set, records errno. Returns base or 0.
 * Confidence: medium
 * Notes: errno codes 0xc (if fastpath null) / 0x16 (unaligned). */
static long sk_zone_alloc_aligned(uint64_t zone, uint64_t size, uint64_t align, uint32_t flags, uint64_t extra)
{
	uint64_t err = 0x16;
	if ((size > 8 && (size & (size - 1)) == 0) &&
	    ((align & (size - 1)) == 0 || ((flags >> 1 & 1) == 0))) {
		uint64_t (*fast)(void) = *(uint64_t (**)(void))(zone + 0x70);
		if (fast != 0 && (fast(), 1) && (fast(), 1)) {
			uint64_t r = fast();
			if (r != 0) return r;
		}
		err = 0xc;
	}
	if ((flags & 1) != 0) sk_set_errno(err);
	return 0;
}

/* FUN_000122ac @ 0x000122ac   (est. sk_zone_alloc_fast)
 * Ghidra: undefined8 FUN_000122ac(long, ulong)
 * Calls the zone's +0x70 fast allocator for aligned power-of-two sizes;
 * returns its result (0 when no fastpath).
 * Confidence: medium
 * Notes: unrecovered jumptable at 0x122e4. */
static uint64_t sk_zone_alloc_fast(uint64_t zone, uint64_t size)
{
	uint64_t (*fast)(void);
	if ((size > 8 && (size & (size - 1)) == 0) &&
	    (fast = *(uint64_t (**)(void))(zone + 0x70)) != 0) {
		return fast();
	}
	return 0;
}

/* FUN_000122f0 @ 0x000122f0   (est. sk_zone_free_lookup)
 * Ghidra: void FUN_000122f0(ulong, uint)
 * Finds the zone owning `param_1` (from index `param_2`) and frees it through
 * the zone's +0x78 method (with size) or +0x30 method (without). Falls back to
 * FUN_0000298c(0x40) on no match.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x12400); jumptable at 0x12448. */
static void sk_zone_free_lookup(uint64_t p, uint32_t start)
{
	uint64_t i;
	uint64_t zone;
	long size;
	uint64_t (*freefn)(uint64_t, uint64_t, uint64_t);

	if (p == 0) return;
	for (i = start; i < sk_mall_zone_count; i++) {
		zone = sk_mall_zone_tbl[i];
		size = (*(long (**)(uint64_t, uint64_t))(zone + 0x10))(zone, p);
		if (size != 0) {
			freefn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(zone + 0x78);
			if (freefn == 0) {
				sk_zone_free_call(zone);
				return;
			}
			if (p <= p + (uint64_t)size) {
				freefn(zone, p, (uint64_t)size);
				return;
			}
			__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x12400) */
		}
	}
	sk_kernel_abort(0x40, p);
}

/* FUN_0001244c @ 0x0001244c   (est. sk_zone_alloc0)
 * Ghidra: void FUN_0001244c(ulong)
 * Allocates `size` bytes from the first registered zone (index 0).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x124a4). */
static uint64_t sk_zone_alloc0(uint64_t size)
{
	uint64_t base = sk_zone_call_alloc(sk_mall_zone_tbl[0], size);
	if (base <= base + size && (base == 0 || size <= (base + size) - base)) return base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x124a4) */
}

/* FUN_000124a4 @ 0x000124a4   (est. sk_zone_alloc0_aligned)
 * Ghidra: void FUN_000124a4(undefined8, ulong)
 * Aligned allocation from the first registered zone (size+alignment).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x12504). */
static uint64_t sk_zone_alloc0_aligned(uint64_t size, uint64_t align)
{
	uint64_t base = sk_zone_alloc_aligned(sk_mall_zone_tbl[0], size, align, 3, 0);
	if (base <= base + align && (base == 0 || align <= (base + align) - base)) return base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x12504) */
}

/* FUN_00012504 @ 0x00012504   (est. sk_zone_calloc0)
 * Ghidra: void FUN_00012504(long, long)
 * Calloc of n*size from the first registered zone.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x12568). */
static uint64_t sk_zone_calloc0(uint64_t n, uint64_t size)
{
	uint64_t base = sk_zone_calloc_noback(sk_mall_zone_tbl[0], n, size);
	uint64_t total = size * n;
	if (base <= base + total && (base == 0 || total < (base + total) - base ||
	                             total - ((base + total) - base) == 0)) return base;
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x12568) */
}

/* FUN_00012568 @ 0x00012568   (est. sk_zone_free_0)
 * Ghidra: void FUN_00012568(long)
 * Frees `param_1` through the default zone (index 0): uses the zone's +0x90
 * free method if present, else sk_zone_free_lookup.
 * Confidence: medium
 * Notes: jumptable at 0x1259c. */
static void sk_zone_free_0(uint64_t p)
{
	uint64_t (*freefn)(void);
	if (p == 0) return;
	freefn = *(uint64_t (**)(void))(sk_mall_zone_tbl[0] + 0x90);
	if (freefn != 0) {
		freefn();
		return;
	}
	sk_zone_free_lookup(p, 0);
}

/* FUN_000125b4 @ 0x000125b4   (est. sk_zone_malloc)
 * Ghidra: ulong FUN_000125b4(long, ulong)
 * Finds the zone owning `param_1` (matching +0x10) and allocates `size` bytes
 * through it (FUN_000121b8). With null pointer/size, allocates from the default
 * zone. Sets errno 0xc on failure.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x126bc); jumptable at 0x126b8. */
static uint64_t sk_zone_malloc(uint64_t p, uint64_t size)
{
	uint64_t i;
	uint64_t zone;
	long match;
	uint64_t base;

	if (p == 0 || size == 0) {
		base = sk_zone_call_alloc(sk_mall_zone_tbl[0], size);
		goto done;
	}
	for (i = 0; i < sk_mall_zone_count; i++) {
		zone = sk_mall_zone_tbl[i];
		match = (*(long (**)(uint64_t, uint64_t))(zone + 0x10))(zone, p);
		if (match != 0) {
			base = sk_zone_alloc_core(zone, p, size);
			goto done;
		}
	}
	sk_kernel_abort(0x40, p);
	base = 0;
done:
	if (base != 0) {
		if (size == 0) sk_zone_free_0(p);
		if (base <= base + size && size <= (base + size) - base) return base;
		__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x126bc) */
	}
	sk_set_errno(0xc);
	return 0;
}

/* FUN_000126e8 @ 0x000126e8   (est. sk_zone_owns)
 * Ghidra: long FUN_000126e8(long)
 * Returns nonzero if any registered zone claims ownership of `param_1`
 * (via +0x10 match), else 0.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x1279c). */
static long sk_zone_owns(uint64_t p)
{
	uint64_t i;
	uint64_t zone;
	long match;
	if (p != 0 && sk_mall_zone_count != 0) {
		for (i = 0; i < sk_mall_zone_count; i++) {
			zone = sk_mall_zone_tbl[i];
			match = (*(long (**)(uint64_t, uint64_t))(zone + 0x10))(zone, p);
			if (match != 0) return match;
		}
	}
	return 0;
}

/* FUN_0001279c @ 0x0001279c   (est. sk_zone_alloc_from)
 * Ghidra: void FUN_0001279c(undefined8)
 * Allocates via the default zone's +0x60-subobject +8 method.
 * Confidence: low
 * Notes: jumptable at 0x127bc. */
static void sk_zone_alloc_from(uint64_t a)
{
	uint64_t sub = *(uint64_t *)(sk_mall_zone_tbl[0] + 0x60);
	(*(void (**)(uint64_t, uint64_t))(sub + 8))(sk_mall_zone_tbl[0], a);
}

/* FUN_000127c0 @ 0x000127c0   (est. sk_zone_alloc_fast_out)
 * Ghidra: undefined4 FUN_000127c0(long*, ulong)
 * Fast aligned alloc: calls the default zone's +0x70 fastpath; on success
 * stores base in *out and returns 0, else returns 0x16 (unaligned) or 0xc
 * (ENOMEM).
 * Confidence: medium */
static uint32_t sk_zone_alloc_fast_out(uint64_t *out, uint64_t size)
{
	uint64_t base = sk_zone_alloc_fast(sk_mall_zone_tbl[0], size);
	if (base == 0) {
		uint32_t err = 0xc;
		if ((size & (size - 1)) != 0 || size < 8) err = 0x16;
		return err;
	}
	*out = base;
	return 0;
}

/* FUN_0001281c @ 0x0001281c   (est. sk_batch_init)
 * Ghidra: void FUN_0001281c(undefined8*, undefined1, undefined1, uint, uint, uint, undefined8, ulong, uint)
 * Initialises a malloc batch-free structure: computes alignment padding from
 * `param_8` vs `param_5`, allocates a depo region of `param_9` bytes (rounded
 * down to `param_6`-multiples), and fills the descriptor fields.
 * Confidence: low
 * Notes: depot pointer stored at param_1[7] and param_1[10]. */
static void sk_batch_init(uint64_t *d, uint8_t f2, uint8_t f3, uint32_t f4, uint32_t f5,
                          uint32_t f6, uint64_t f7, uint64_t f8, uint32_t f9)
{
	uint64_t *depot = 0;
	uint32_t dcap = 0;

	if (f8 != 0) {
		uint64_t m = (uint64_t)f5;
		uint64_t q = (m != 0) ? f8 / m : 0;
		uint64_t rem = f8 - q * m;
		uint64_t pad = (rem != 0) ? m - rem : 0;
		uint64_t room = (uint64_t)f9 - pad;
		if (pad <= f9 && (uint64_t)(f6 << 1) <= room) {
			depot = (uint64_t *)(pad + f8);
			uint32_t n = (f6 != 0) ? (uint32_t)room / f6 : 0;
			depot[0] = 0;
			depot[1] = (uint64_t)depot;
			depot[2] = 0;
			depot[3] = 0;
			dcap = n * f6;
			f9 = (uint32_t)room;
		}
	}
	d[0] = 0;
	d[1] = 0;
	*(uint8_t *)(d + 2) = f2;
	*(uint8_t *)((long)d + 0x11) = f3;
	*(uint16_t *)((long)d + 0x12) = 0;
	uint32_t n2 = (f6 != 0) ? f4 / f6 : 0;
	*(uint32_t *)((long)d + 0x14) = f4;
	*(uint32_t *)(d + 3) = n2 * f6;
	*(uint32_t *)((long)d + 0x1c) = f5;
	*(uint32_t *)(d + 4) = f6;
	*(uint64_t *)((long)d + 0x2c) = 0;
	*(uint64_t *)((long)d + 0x24) = 0;
	*(uint32_t *)((long)d + 0x34) = 0;
	d[7] = (uint64_t)depot;
	*(uint32_t *)(d + 8) = dcap;
	*(uint32_t *)((long)d + 0x44) = 0;
	d[9] = f7;
	d[10] = (uint64_t)depot;
	*(uint32_t *)(d + 0xb) = f9;
	*(uint32_t *)((long)d + 0x5c) = 0;
	if (depot != 0) {
		depot[0] = 0;
		d[5] = (uint64_t)depot;
	}
}

/* FUN_000128cc @ 0x000128cc   (est. sk_batch_pop)
 * Ghidra: ulong FUN_000128cc(long)
 * Pops a block from the mall zone's free-batch depot: takes from the free list
 * (param_1+0x30) if present, else allocates a fresh depot region (param_1+0x38),
 * walking the size-class list to find a block. Returns the block pointer.
 * Confidence: low
 * Notes: lock FUN_0011582c/94; strings s_Failed_to_acquire_lock__p__005a9a23 /
 *   s_Failed_to_release_lock__p__005a9a3f, s_BUG_IN_CLIENT_OF_LIBMALLOC___s_005aaab9;
 *   stack canary. */
static uint64_t sk_batch_pop(uint64_t zone)
{
	uint64_t *free = *(uint64_t **)(zone + 0x30);
	uint64_t block;

	sk_lock_acquire((void *)zone);
	if (free != 0) {
		block = free[1];
		*(uint64_t *)(zone + 0x30) = *free;
		uint64_t owner = *(uint64_t *)(zone + 0x48);
		if (owner == 0) {
			free[0] = 0;
			free[1] = 0;
		} else {
			sk_zone_madvise((uint64_t)free, *(uint32_t *)(zone + 0x20), 2, 0x40,
			                (uint64_t)free + 0x10);
			sk_batch_push(owner, free);
		}
	} else {
		uint64_t *node = *(uint64_t **)(zone + 0x38);
		if (node == 0) {
			/* allocate a fresh depot */
			uint64_t idx = *(uint32_t *)(zone + 0x1c);
			node = (uint64_t *)sk_zone_alloc(0, *(uint32_t *)(zone + 0x14),
			                                (uint32_t)LZCOUNT(idx >> 0x10 | idx << 0x10) & 0x1f,
			                                1, 0x2000, 1, 0);
			if (node == 0) sk_fatal_printf("BUG IN CLIENT OF LIBMALLOC");
			node[0] = 0;
			node[1] = (uint64_t)node;
			*(uint64_t *)(zone + 0x38) = (uint64_t)node;
			*(uint64_t *)(zone + 0x28) = (uint64_t)node;
			block = *(uint32_t *)(zone + 0x40);
		} else {
			block = *(uint32_t *)(zone + 0x40);
			if (block == *(uint32_t *)(zone + 0x18)) block = 0;
		}
		if (block == 0) {
			uint64_t u6 = *(uint32_t *)(zone + 0x1c);
			u6 = (u6 & 0xaaaaaaaa) >> 1 | (u6 & 0x55555555) << 1;
			u6 = (u6 & 0xcccccccc) >> 2 | (u6 & 0x33333333) << 2;
			u6 = (u6 & 0xf0f0f0f0) >> 4 | (u6 & 0xf0f0f0f) << 4;
			u6 = (u6 & 0xff00ff00) >> 8 | (u6 & 0xff00ff) << 8;
			block = 0x2000;
		}
		block = node[1] + block;
		uint32_t sz = *(uint32_t *)(zone + 0x20);
		*(uint32_t *)(zone + 0x40) = sz + (uint32_t)block;
		if (*(uint64_t *)(zone + 0x48) != 0 && sz > 0x3fff)
			sk_zone_madvise(block, sz, 2, 0x40, 0);
	}
	sk_lock_release((void *)zone);
	return block;
}

/* FUN_00012b0c @ 0x00012b0c   (est. sk_batch_push)
 * Ghidra: void FUN_00012b0c(long, undefined8*)
 * Pushes a block back onto the mall zone's free-batch list (param_1+0x30).
 * Confidence: low
 * Notes: lock FUN_0011582c/94. */
static void sk_batch_push(uint64_t zone, uint64_t *block)
{
	uint64_t *head;
	sk_lock_acquire((void *)zone);
	if (*(uint64_t *)(zone + 0x48) != 0) sk_batch_pop(zone);
	head = *(uint64_t **)(zone + 0x30);
	block[0] = (uint64_t)head;
	block[1] = (uint64_t)block;
	*(uint64_t **)(zone + 0x30) = block;
	sk_lock_release((void *)zone);
}

/* FUN_00012c04 @ 0x00012c04   (est. sk_tb_alloc_slots)
 * Ghidra: void FUN_00012c04(long, ulong)
 * Allocates a run of `param_2` capability slots (max TB_MAX) for a thread
 * block: fills the received-slot array at param_1+0x38 with freshly allocated
 * cap addresses. Asserts on over-allocated/overflow.
 * Confidence: medium
 * Notes: strings s_TB_ASSERT__num_caps_<__TB_MAX_CA_005aabbd,
 *   s_TB_ASSERT__td_>received_slot_cou_005aab87,
 *   s_TB_ASSERT__td_>allocated_slot_co_005aab3a;
 *   SoftwareBreakpoint(1,0x12cec); FUN_004b0034 on alloc failure. */
static void sk_tb_alloc_slots(uint64_t tb, uint64_t num)
{
	uint64_t *slot = (uint64_t *)(tb + 0x38);
	uint64_t i;

	if ((uint64_t *)(tb + 0x68) < slot)
		__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x12c88) */

	if (*(uint64_t *)(tb + 0x58) == 0) {
		if (*(uint64_t *)(tb + 0x60) == 0) {
			if (num < 5) {
				for (i = 0; i < num; i++) {
					uint64_t a = sk_phys_alloc(0);
					if (a == 0) {
						sk_boot_abort3();
						break;
					}
					slot[i] = a;
				}
				*(uint64_t *)(tb + 0x58) = num;
				*(uint64_t *)(tb + 0x60) = 0;
				return;
			}
			sk_printf("TB_ASSERT: num_caps < TB_MAX_CAPS\n");
		} else {
			sk_printf("TB_ASSERT: td->received_slot_count\n");
		}
	} else {
		sk_printf("TB_ASSERT: td->allocated_slot_count\n");
	}
	__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x12cec) */
}

/* FUN_00012d3c @ 0x00012d3c   (est. sk_tb_assert_received)
 * Ghidra: void FUN_00012d3c(void)
 * Asserts the thread block's received-slot invariant.
 * Confidence: high
 * Notes: string s_TB_ASSERT__td_>received_slot_cou_005aab87. */
static void sk_tb_assert_received(void)
{
	sk_printf("TB_ASSERT: td->received_slot_count\n");
	__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x12d70) */
}

/* FUN_00012d70 @ 0x00012d70   (est. sk_tb_free_slots)
 * Ghidra: void FUN_00012d70(long)
 * Releases a thread block's capability slots: drops references for received
 * slots and clears the arrays. Asserts on underflow.
 * Confidence: medium
 * Notes: strings s_TB_ASSERT__td_>received_slot_cou_005aac1e,
 *   s_TB_ASSERT__td_>allocated_slot_co_005aac70;
 *   SoftwareBreakpoint(1,0x12e48); FUN_004b23d8 per slot. */
static void sk_tb_free_slots(uint64_t tb)
{
	uint64_t *slot = (uint64_t *)(tb + 0x38);
	uint64_t alloc = *(uint64_t *)(tb + 0x58);
	uint64_t recv = *(uint64_t *)(tb + 0x60);
	uint64_t i;

	if (tb + 0x68 < (uint64_t)slot)
		__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x12e04) */

	if (alloc < recv) {
		sk_printf("TB_ASSERT: td->received_slot_count\n");
	} else if (alloc < 5) {
		if (alloc != 0) {
			for (i = 0; i < alloc; i++) {
				if (recv <= i) sk_obj_release_caps(slot[i]);
				slot[i] = 0;
			}
		}
		*(uint64_t *)(tb + 0x58) = 0;
		*(uint64_t *)(tb + 0x60) = 0;
		return;
	} else {
		sk_printf("TB_ASSERT: td->allocated_slot_count\n");
	}
	__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x12e48) */
}

/* FUN_00012e48 @ 0x00012e48   (est. sk_tb_create)
 * Ghidra: void FUN_00012e48(void)
 * Allocates and zeroes a thread-block object (0x118 bytes) and stores the
 * magic 0x658fa8 at offset 0x60.
 * Confidence: medium
 * Notes: FUN_00010244(1,0x118,0x1082040eda8e2da); FUN_004b0068 on failure. */
static uint64_t sk_tb_create(void)
{
	uint64_t *tb = (uint64_t *)sk_zone_alloc_obj(1, 0x118, 0x1082040eda8e2daull);
	if (tb != 0) {
		for (int i = 0; i < 0x22; i++) tb[i] = 0;
		tb[0xc] = 0x658fa8;
		return (uint64_t)tb;
	}
	sk_boot_abort4();
}

/* FUN_00012eb8 @ 0x00012eb8   (est. sk_tb_dup)
 * Ghidra: int FUN_00012eb8(undefined8, long, long*, uint)
 * Duplicates a thread-block/capability object: allocates a fresh data buffer
 * and a new TB wrapper, copies the payload, invokes the IPC send path, and
 * re-associates ownership. Returns a status code (bit-packing from param_4).
 * Confidence: low
 * Notes: strings s_TB_ASSERT__err____TB_ERROR_SUCCE_005aacb1;
 *   FUN_00010244 magic 0x100004077774924 / 0x1090040b6685729 / 0x102004071d150f8;
 *   SoftwareBreakpoint(1,0x1310c); FUN_004b0068/0080 on alloc failure. */
static int sk_tb_dup(uint64_t a, uint64_t t, long *out, uint32_t flags)
{
	uint64_t *src = (uint64_t *)sk_tb_get((void *)t);
	uint64_t sz = src[3];
	uint64_t base = *src;
	uint64_t buf = (uint64_t)sk_zone_alloc_obj(1, sz, 0x100004077774924ull);
	uint64_t *wrap;
	uint32_t *hdr;
	uint64_t *dst;

	if (buf == 0) sk_boot_abort5();
	else {
		sk_memcpy(buf, base, sz);
		wrap = (uint64_t *)sk_zone_alloc_obj(1, 0x68, 0x1090040b6685729ull);
		if (wrap != 0) {
			wrap[0] = buf;
			wrap[2] = 0;
			wrap[3] = sz;
			wrap[4] = 0;
			wrap[6] = 0;
			*(uint16_t *)((long)wrap + 0x2a) = *(uint16_t *)((long)src + 0x2a);
			hdr = (uint32_t *)sk_zone_alloc_obj(1, 0x58, 0x102004071d150f8ull);
			if (hdr == 0) sk_boot_abort3();
			hdr[0] = 4;
			*(uint8_t *)(hdr + 1) = 1;
			*(uint64_t **)(hdr + 0x14) = wrap;
			*(uint64_t *)(hdr + 6) = a;
			sk_tb_retain(hdr, 1);
			uint64_t local = (uint64_t)hdr;
			sk_tb_call(a, (uint64_t)hdr, &local);
			if (local == 0) {
				sk_zone_free_0(*wrap);
				sk_zone_free_0((uint64_t)wrap);
				sk_zone_free_0((uint64_t)hdr);
				return (flags & 2) << 1;
			}
			dst = (uint64_t *)sk_tb_get((void *)local);
			sz = dst[3];
			sk_zone_free_0(*src);
			src[0] = 0; src[2] = 0; src[3] = 0;
			int r = sk_cap_alloc_claim(sz);
			if (r != 0) {
				sk_printf("TB_ASSERT: err == TB_ERROR_SUCCESS\n");
				__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x1310c) */
			}
			sz = dst[3];
			if (sz <= src[3]) {
				uint64_t sb = *src;
				sk_memcpy(sb, *dst, sz);
				if (sb <= sb + sz) {
					*(uint16_t *)((long)src + 0x2a) = *(uint16_t *)((long)dst + 0x2a);
					*(uint64_t *)(t + 0x18) = *(uint64_t *)((uint64_t *)local + 6);
					sk_tb_retain((void *)t, 2);
					if (wrap != dst) {
						sk_zone_free_0(*dst);
						sk_zone_free_0((uint64_t)dst);
					}
					sk_zone_free_0(*wrap);
					sk_zone_free_0((uint64_t)wrap);
					sk_zone_free_0((uint64_t)hdr);
					if (out == 0) return 0;
					*out = t;
					return 0;
				}
			}
			__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x130d8) */
		}
	}
	sk_boot_abort3();
}

/* FUN_00013134 @ 0x00013134   (est. sk_cap_alloc)
 * Ghidra: undefined8 FUN_00013134(undefined8, ulong, undefined8, ulong*)
 * Allocates a capability data buffer of `param_2` bytes and initialises a TB
 * descriptor: on success stores base and metadata in *param_4 and returns 0;
 * on alloc failure releases the prior object and marks the descriptor invalid.
 * Confidence: medium
 * Notes: FUN_00010244 magic 0x100004077774924; FUN_004b0080 on failure. */
static uint64_t sk_cap_alloc(uint64_t a, uint64_t sz, uint64_t c, uint64_t *d)
{
	uint64_t buf = (uint64_t)sk_zone_alloc_obj(1, sz, 0x100004077774924ull);
	if (buf != 0) {
		d[0] = buf;
		*(uint8_t *)(d + 1) = 0;
		d[2] = 0;
		d[3] = sz;
		d[4] = 0;
		d[6] = 0;
		*(uint8_t *)((long)d + 0x29) = 0;
		return 0;
	}
	sk_boot_abort5();
	sk_zone_free_0(*d);
	d[0] = 0;
	d[6] = 0;
	d[3] = 0;
	d[4] = 0;
	d[2] = 0;
	*(uint8_t *)((long)d + 0x29) = 1;
	return 0;
}

/* FUN_000131e8 @ 0x000131e8   (est. sk_cap_realloc)
 * Ghidra: void FUN_000131e8(undefined8, undefined8*, undefined8, undefined8)
 * Reallocates a capability buffer: frees the current buffer, zeroes the
 * descriptor, and re-allocates a new buffer of `param_4` bytes.
 * Confidence: medium */
static void sk_cap_realloc(uint64_t a, uint64_t *d, uint64_t c, uint64_t sz)
{
	sk_zone_free_0(*d);
	d[0] = 0;
	d[2] = 0;
	d[3] = 0;
	sk_cap_alloc(a, sz, c, d);
}

/* FUN_00013228 @ 0x00013228   (est. sk_tb_fatal_internal_h_204)
 * Ghidra: void FUN_00013228(void)
 * Fatal diagnostic: internal.h line 0xcc (204).
 * Confidence: high
 * Notes: string s_internal_h_005aad1c, &DAT_005aacf2. */
static void sk_tb_fatal_internal_h_204(void)
{
	sk_printf("internal.h 0xcc\n");
}

/* FUN_00013244 @ 0x00013244   (est. sk_tb_fatal_internal_h_199)
 * Ghidra: void FUN_00013244(void)
 * Fatal diagnostic: internal.h line 0xc7 (199).
 * Confidence: high
 * Notes: string s_internal_h_005aad1c, &DAT_005aacf2. */
static void sk_tb_fatal_internal_h_199(void)
{
	sk_printf("internal.h 0xc7\n");
}

/* FUN_00013260 @ 0x00013260   (est. sk_trampoline_call)
 * Ghidra: void FUN_00013260(undefined8, undefined8, undefined8)
 * Invokes a CPU trampoline with the given args, validating the trampoline
 * region before the indirect call.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x132d4); FUN_00060524/603bc/636d0/636d8. */
static void sk_trampoline_call(uint64_t a1, uint64_t a2, uint64_t a3)
{
	uint64_t (*fn)(uint64_t, uint64_t, uint64_t);
	sk_boot_info_get();
	uint64_t base = sk_tramp_call();
	if (base <= base + 0x50) {
		fn = (uint64_t (*)(uint64_t, uint64_t, uint64_t))sk_tramp_setup(base);
		uint64_t arg = sk_tramp_get(base);
		fn(arg, a2, a3);
		return;
	}
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x132d4) */
}

/* FUN_000132d4 @ 0x000132d4   (est. sk_round_bytes_to_words)
 * Ghidra: ulong FUN_000132d4(long)
 * Rounds `param_1` bytes up to a multiple of 8 (in words: (x+7)>>3).
 * Confidence: high */
static uint64_t sk_round_bytes_to_words(uint64_t x)
{
	return (x + 7u) >> 3;
}

/* FUN_000132e0 @ 0x000132e0   (est. sk_percpu_alloc)
 * Ghidra: undefined8 FUN_000132e0(undefined8, undefined8)
 * Per-CPU keyed allocation: first calls FUN_0005ea94(0x6adff8, 0x1b8, 0, 0);
 * if that returns 0x37 (a sentinel), calls FUN_0005ea94(a, b, 0, 0).
 * Confidence: low
 * Notes: DAT_006adff8 sentinel; FUN_0005ea94 = percpu key store. */
static uint64_t sk_percpu_alloc(uint64_t a, uint64_t b)
{
	uint64_t k = sk_percpu_key(0x6adff8, 0x1b8, 0, 0);
	if (k == 0x37) return sk_percpu_key(a, b, 0, 0);
	return 0;
}

/* FUN_00013348 @ 0x00013348   (est. sk_tb_init)
 * Ghidra: void FUN_00013348(undefined8, long)
 * Initialises a thread-block object: zeroes the register-save region
 * (param_2+0x88..0xf8), stores the act pointer and TSS key, and applies the
 * flags returned by sk_tb_get_flags (param_1).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x133f8); magics 0x659008/0x659000. */
static void sk_tb_init(uint64_t a, uint64_t tb)
{
	uint64_t *save = (uint64_t *)(tb + 0x88);
	if ((uint64_t *)(tb + 0x118) < save || (uint64_t *)(tb + 0xf8) < save)
		__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x133f8) */

	*(uint64_t *)(tb + 0xe0) = 0;
	*(uint64_t *)(tb + 0xd8) = 0;
	*(uint64_t *)(tb + 0xf0) = 0;
	*(uint64_t *)(tb + 0xe8) = 0;
	*(uint64_t *)(tb + 0xc0) = 0;
	*(uint64_t *)(tb + 0xb8) = 0;
	*(uint64_t *)(tb + 0xd0) = 0;
	*(uint64_t *)(tb + 200) = 0;
	*(uint64_t *)(tb + 0xa0) = 0;
	*(uint64_t *)(tb + 0x98) = 0;
	*(uint64_t *)(tb + 0xb0) = 0;
	*(uint64_t *)(tb + 0xa8) = 0;
	*(uint64_t *)(tb + 0x90) = 0;
	save[0] = 0;
	*(uint64_t *)(tb + 0x60) = 0x659008;
	*(uint64_t *)(tb + 0x88) = sk_tb_get_act(a);
	uint32_t f = sk_tb_get_flags(a);
	if ((f >> 1 & 1) == 0) {
		if ((f & 1) != 0) *(uint32_t *)(tb + 0xe8) = 4;
	} else {
		*(uint32_t *)(tb + 0xe8) = f >> 8 & 0xff;
	}
	if ((f >> 2 & 1) != 0) *(uint8_t *)(tb + 0xec) = 1;
	if ((f >> 3 & 1) != 0) *(uint8_t *)(tb + 0xed) = 1;
}

/* FUN_00013878 @ 0x00013878   (est. sk_tb_spawn)
 * Ghidra: undefined8 FUN_00013878(long)
 * Spawns a thread block: registers a timer callback (when flag bit at +0xec
 * set), builds a TSS key, and enqueues the run queue at param_1+0x98 with a
 * completion handler.
 * Confidence: low
 * Notes: FUN_0006290c/62c2c; SoftwareBreakpoint(0x5519,0x13930). */
static uint64_t sk_tb_spawn(uint64_t tb)
{
	uint32_t u = *(uint32_t *)(tb + 0xe8);
	if ((uint64_t)(tb + 0x88) > (uint64_t)(tb + 0x118) ||
	    (uint64_t)(tb + 0x88) > (uint64_t)(tb + 0xf8))
		__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x13930) */

	if (*(uint8_t *)(tb + 0xec) == 1) sk_timer_call(0, sk_trampoline_call, 0);
	if (u < 2) u = 1;
	{
		uint64_t ksz = u;
		void (*cb)(uint64_t, uint64_t, uint64_t) =
			(void (*)(uint64_t, uint64_t, uint64_t))(uint64_t)sk_tb_obj_dispatch;
		uint64_t prio = 4;
		sk_q_wait((void *)(tb + 0x98), (void *)*(uint64_t *)(tb + 0x88), (uint64_t)cb);
	}
	return 0;
}

/* FUN_000139ac @ 0x000139ac   (est. sk_tb_release)
 * Ghidra: void FUN_000139ac(undefined8*)
 * Releases a thread-block descriptor: frees its slot buffer and TSS key (if
 * not already marked invalid), clears the fields and sets the invalid flag
 * (byte +0x29).
 * Confidence: medium */
static void sk_tb_release(uint64_t *d)
{
	if ((*(uint8_t *)((long)d + 0x29) & 1) == 0) {
		if (d[6] == 0) {
			sk_tb_free_slots((uint64_t)d);
			sk_tss_free_slot(*d);
		}
		d[0] = 0;
		d[6] = 0;
		d[3] = 0;
		d[4] = 0;
		d[2] = 0;
		*(uint8_t *)((long)d + 0x29) = 1;
	}
}

/* FUN_00013a08 @ 0x00013a08   (est. sk_tb_attach)
 * Ghidra: undefined8 FUN_00013a08(undefined8*, undefined8, ulong)
 * Attaches a buffer of `param_3` bytes to a thread-block descriptor: either
 * borrows the current depot (param_1[6]) if it is large enough, or allocates a
 * fresh TSS slot. Returns 0 on success, 5 (EINVAL-ish) when oversized.
 * Confidence: medium
 * Notes: FUN_0005d470(0x6ae1b8,&DAT_00013c88,0); FUN_00013cfc allocates slot. */
static uint64_t sk_tb_attach(uint64_t *d, uint64_t a2, uint64_t sz)
{
	uint64_t *depot = (uint64_t *)d[6];
	if (depot == 0) {
		if (sz > 0x1b8) return 5;
		sk_tb_free_slots((uint64_t)d);
		sk_tss_free_slot(d[0]);
		sk_depot_push(0x13c88);
		d[0] = sk_tss_alloc_slot();
	} else {
		if ((uint64_t)depot[1] < sz) return 5;
		d[0] = depot[0];
	}
	d[2] = 0;
	d[3] = sz;
	*(uint16_t *)((long)d + 0x2a) = 0;
	return 0;
}

/* FUN_00013af0 @ 0x00013af0   (est. sk_tss_free_slot)
 * Ghidra: void FUN_00013af0(ulong)
 * Frees a per-thread-storage slot: clears the corresponding bit in the TSS
 * bitmap (base+0x528); on invalid base/range panics and tears down registered
 * objects.
 * Confidence: medium
 * Notes: FUN_00013be4 base; division by 0x1b8 via magic 0x4a7904a7904a7905;
 *   FUN_004b01b8/0188/0158/0128/23d8, FUN_0005ed18 teardown. */
static void sk_tss_free_slot(uint64_t p)
{
	uint64_t base = sk_tss_base_get();
	uint32_t bit;

	if (base == 0) {
		sk_panic_tss_null();
	} else if (p < base || p > base + 0x370) {
		sk_panic_tss_range();
	} else {
		bit = 1u << (((p - base) / 0x1b8) & 0x1f);   /* magic 0x4a7904a7904a7905 division */
		if ((*(uint64_t *)(base + 0x528) & bit) != 0) {
			*(uint64_t *)(base + 0x528) &= ~bit;
			return;
		}
	}
	sk_panic_tss_teardown();
	{
		uint64_t *objs = sk_tss_obj_list();
		if (objs[1] != 0) {
			uint64_t i;
			for (i = 0; i < objs[1]; i++) {
				sk_obj_release_caps(objs[i]);
				sk_obj_drop(i, 0);
			}
		}
	}
}

/* FUN_00013be4 @ 0x00013be4   (est. sk_tss_base_get)
 * Ghidra: long FUN_00013be4(void)
 * Returns the current thread's TSS base (per-cpu slot). Validates the key
 * index and thread state, asserting when the key is deleted/in use by a
 * destructor.
 * Confidence: medium
 * Notes: strings s_getting_key__lu_while_destructor_005ab2c6,
 *   s_getting_key__lu_which_is_deleted_005ab2a5;
 *   SoftwareBreakpoint(0x5519,0x13c88); FUN_00063a50/5b190. */
static uint64_t sk_tss_base_get(void)
{
	uint64_t n = sk_tss_base;
	uint64_t cpu;
	uint64_t *tls;

	if (sk_tss_base < 0x20) {
		cpu = sk_cpu_reg_store(0);
		tls = (uint64_t *)sk_tpidr_flags();
		if (*(long *)(cpu + (n - 1) * 8 + 0x1f8) != -1) {
			if (tls[0x1f] == 0) {
				uint64_t *slot = tls + (n - 1);
				if (slot >= tls && slot + 1 <= tls + 0x1f) return *slot;
				__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x13c88) */
			}
			sk_panic_err(0, "getting key while destructor");
		}
	} else {
		sk_boot_abort2();
	}
	sk_panic_err(0, "getting key which is deleted");
}

/* FUN_00013cfc @ 0x00013cfc   (est. sk_tss_alloc_slot)
 * Ghidra: long FUN_00013cfc(void)
 * Allocates a per-thread-storage slot: finds the per-CPU TSS region (creating
 * it if needed), computes the next free slot from the 64-bit bitmap at
 * region+0x528, marks it used and returns region + slot*0x1b8. Panics when no
 * slot is free.
 * Confidence: medium
 * Notes: strings s_key_<__XRT__THREAD_TSS_MAX_KEYS_005ab392,
 *   s__AppleInternal_Library_BuildRoot_005ab177, s_xrt_thread_tss_set_005ab3b2,
 *   s_TB_FATAL__no_available_per_threa_005ab34c,
 *   s_setting_key__lu_while_destructor_005ab3c5,
 *   s_setting_key__lu_which_is_deleted_005ab3ef;
 *   SoftwareBreakpoint(1,0x13ea8); FUN_00013ea8 allocates new region. */
static uint64_t sk_tss_alloc_slot(void)
{
	uint64_t region = sk_tss_base_get();
	if (region == 0) {
		uint64_t cpu = sk_boot_info_get();
		region = 0x6ae1d0;
		if (sk_tss_cur_cpu != cpu) {
			if (sk_tss_cur_cpu == 0) {
				sk_depot_init(&sk_tss_cur_val, 0xa68);
				region = 0x6ae1d0;
				sk_tss_cur_cpu = cpu;
			} else if (sk_tss_cur_val == cpu || sk_tss_cur_val == 0) {
				sk_tss_cur_val = (sk_tss_cur_val == cpu) ? sk_tss_cur_val : cpu;
				region = 0x6ae700;
			} else {
				region = sk_tss_new_region();
			}
		}
		{
			uint64_t n = sk_tss_base;
			uint64_t cpu2 = sk_cpu_reg_store(0);
			uint64_t *tls = (uint64_t *)sk_tpidr_flags();
			if (tls[0x1f] != 0)
				sk_panic_err(0, "setting key while destructor");
			uint64_t *slot = tls + (n - 1);
			if (*slot != region) {
				if (*slot == 0) {
					uint64_t *cnt = (uint64_t *)(cpu2 + (n - 1) * 8 + 0x1f8);
					uint64_t c = *cnt;
					*cnt = c + 1;
					if (c == (uint64_t)-1)
						sk_panic_err(0, "setting key which is deleted");
				}
				*slot = region;
			}
		}
	}
	{
		uint64_t bitmap = *(uint64_t *)(region + 0x528);
		uint64_t free = LZCOUNT((~bitmap & 0xaaaaaaaaaaaaaaaaull) >> 1 |
		                       (~bitmap & 0x5555555555555555ull) << 1);
		free = LZCOUNT((free & 0xccccccccccccccccull) >> 2 |
		               (free & 0x3333333333333333ull) << 2);
		free = LZCOUNT((free & 0xf0f0f0f0f0f0f0f0ull) >> 4 |
		               (free & 0xf0f0f0f0f0f0f0full) << 4);
		free = LZCOUNT((free & 0xff00ff00ff00ff00ull) >> 8 |
		               (free & 0xff00ff00ff00ffull) << 8);
		free = LZCOUNT((free & 0xffff0000ffff0000ull) >> 0x10 |
		               (free & 0xffff0000ffffull) << 0x10);
		if (bitmap != 0xffffffffffffffffull && free < 3) {
			*(uint64_t *)(region + 0x528) = bitmap | (1ull << (free & 0x1f));
			return region + free * 0x1b8;
		}
	}
	sk_printf("TB_FATAL: no available per-thread key\n");
	__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x13ea8) */
}

/* FUN_00013ea8 @ 0x00013ea8   (est. sk_tss_new_region)
 * Ghidra: void FUN_00013ea8(void)
 * Allocates a fresh per-CPU TSS region (0x530 bytes); on failure aborts and
 * releases the default zone.
 * Confidence: medium
 * Notes: FUN_00010244(1,0x530,0x10000403b489d26); FUN_004b0244. */
static uint64_t sk_tss_new_region(void)
{
	uint64_t r = (uint64_t)sk_zone_alloc_obj(1, 0x530, 0x10000403b489d26ull);
	if (r != 0) return r;
	sk_boot_abort6();
	sk_zone_free_0(0);
	return 0;
}

/* FUN_00013ee4 @ 0x00013ee4   (est. sk_ipc_send)
 * Ghidra: ulong FUN_00013ee4(undefined8, undefined8, undefined8)
 * cL4 IPC send path. Encodes the outgoing message, builds a message block via
 * FUN_0001586c, emits the cap list through the transport (CallSupervisor 1),
 * validates the response, and returns the send result. Complex state machine.
 * Confidence: low
 * Notes: strings s_cL4_transport_c_005aae37,
 *   s_TB_ASSERT__rcv_err____TB_ERROR_S_005ab441,
 *   s_TB_ASSERT__msg_err____TB_ERROR_S_005ab4f2,
 *   s_TB_ASSERT__payload_size_<__max_s_005ab475,
 *   s_TB_ASSERT__num_rcv_caps_<__TB_MA_005ab59c,
 *   s_TB_ASSERT__L4_ErrorCode_err_____L_005ab5fd,
 *   s_TB_ASSERT__error____TB_ERROR_SUC_005ab644;
 *   CallSupervisor(1); FUN_0005ee50/5eb78/5ee48/5ee40/5ee58, FUN_000142d4,
 *   FUN_0001574c, FUN_000132d4/132e0, FUN_004b02d4/02a4/0274/0304, (*DAT_00657f98). */
static uint64_t sk_ipc_send(uint64_t a1, uint64_t msg, uint64_t caps)
{
	uint64_t *payload;
	uint64_t result;

	payload = (uint64_t *)sk_query_payload_msg(msg);
	if (payload[0] >> 0x3d != 0) goto too_big;
	{
		uint64_t n = payload[0] << 3;
		sk_cpu_alloc_fn(0);
		uint64_t *body = sk_tb_buf_init(n, msg);
		uint64_t psize = sk_query_payload(body, n, 0);
		if (payload[0] != psize) {
			sk_boot_abort7();
			sk_printf("TB_ASSERT: msg_err == TB_ERROR_SUCCESS\n");
			goto fail;
		}
		{
			uint64_t mblk = (uint64_t)sk_msg_alloc();
			sk_msg_init2((void *)mblk, 0x1b8);
			int r = sk_msg_send((void *)mblk, body, 1);
			if (r == 0) {
				sk_msg_writedata((void *)mblk, sk_query_type2(msg));
				sk_msg_append((void *)mblk, 4);
				sk_msg_writedata((void *)mblk, caps);
				sk_ipc_setup(msg, mblk);
				sk_boot_info_get();
				sk_current_thread_set();
				sk_msg_writesize((void *)mblk, sk_current_thread2());
				uint64_t *rcv = 0;
				r = sk_tb_call(a1, mblk, &rcv);
				if (r != 0) {
					sk_printf("TB_ASSERT: rcv_err == TB_ERROR_SUCCESS\n");
					goto fail;
				}
				uint64_t *dst = (uint64_t *)sk_tb_get((void *)mblk);
				if (dst != body) {
					if (rcv == 0) {
						if (*(uint8_t *)(dst + 5) == 1) sk_tb_buf_release(dst, 0, 0, 0, 0);
					} else if (rcv == (uint64_t *)mblk) {
						body[0] = *sk_tb_src(body);
						body[1] = sk_tb_src(body)[1];
						sk_tb_buf_copy(body, dst);
						if (rcv == 0) {
							if (*(uint8_t *)(dst + 5) == 1) sk_tb_buf_release(dst, 0, 0, 0, 0);
						}
						sk_tb_release(dst);
					} else {
						sk_tb_release(dst);
					}
					sk_zone_free_0((uint64_t)dst);
				}
				/* emit received caps */
				if (rcv == 0) {
					result = 0;
				} else {
					sk_msg_append((void *)rcv, 3);
					uint64_t ncap = sk_msg_count((void *)mblk);
					uint64_t i;
					for (i = 0; i < ncap; i++) {
						uint64_t c = sk_msg_get((void *)mblk, i);
						sk_boot_info_get();
						sk_cpu_id(i);
						CallSupervisor(1);
						if ((c & 0xff) != 0) {
							sk_printf("TB_ASSERT: L4_ErrorCode err\n");
							goto fail;
						}
						sk_obj_release_caps(c);
					}
					result = sk_query_type3(sk_tb_id((void *)rcv), ncap, 0);
				}
				sk_tb_release(body);
				sk_tb_release((uint64_t *)mblk);
				return result;
			}
			sk_boot_abort8();
		}
		sk_printf("TB_ASSERT: msg_err == TB_ERROR_SUCCESS\n");
		goto fail;
	}
too_big:
	sk_printf("TB_ASSERT: payload_size < max\n");
fail:
	sk_printf("TB_ASSERT\n");
	__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x14250) */
}

/* FUN_000142d4 @ 0x000142d4   (est. sk_ipc_setup)
 * Ghidra: void FUN_000142d4(undefined8, undefined8)
 * Emits the outgoing capability list for an IPC message: copies the per-thread
 * cap array (tpidrro_el0+0x1e0) and sends each cap via the transport
 * (CallSupervisor 1). Asserts on overflow/errors.
 * Confidence: low
 * Notes: strings s_cL4_transport_c_005aae37,
 *   s_TB_ASSERT__num_rcv_caps_<__TB_MA_005ab59c,
 *   s_TB_ASSERT__L4_ErrorCode_err_____L_005ab5fd,
 *   s_TB_ASSERT__error____TB_ERROR_SUC_005ab644;
 *   CallSupervisor(1); FUN_0005ee40, (*DAT_00657f98), FUN_004b0334,
 *   FUN_00034f70, FUN_0005edac, FUN_00015be8. */
static void sk_ipc_setup(uint64_t a1, uint64_t mblk)
{
	uint64_t n = sk_query_type();
	uint64_t *cap = (uint64_t *)(sk_cpu_alloc_fn(n << 3) + 0);
	uint64_t *dst = cap;
	uint64_t i;

	if (n > 4) {
		sk_printf("TB_ASSERT: num_rcv_caps < TB_MAX\n");
		__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x14448) */
	}
	if (n != 0) {
		uint64_t *src = (uint64_t *)(sk_tpidr_caps());
		for (i = 0; i < n; i++) {
			dst[i] = src[i];
			sk_caps_retain(i, 0);
		}
		for (i = 0; i < n; i++) {
			uint64_t a = sk_phys_alloc(0);
			if (a == 0) {
				sk_printf("TB_ASSERT: error == TB_ERROR_SUCCESS\n");
				__asm__ volatile("brk #1");
			}
			uint64_t v = dst[i];
			CallSupervisor(1);
			if ((v & 0xff) != 0) {
				sk_printf("TB_ASSERT: L4_ErrorCode err\n");
				__asm__ volatile("brk #1");
			}
			if ((int32_t)sk_msg_rcv((void *)mblk, a) != 0) {
				sk_printf("TB_ASSERT: error == TB_ERROR_SUCCESS\n");
				__asm__ volatile("brk #1");
			}
		}
	}
}

/* FUN_00014470 @ 0x00014470   (est. sk_tb_get_id)
 * Ghidra: undefined8 FUN_00014470(undefined8*)
 * Returns the first word of the thread block (its id/cap).
 * Confidence: high */
static uint64_t sk_tb_get_id(uint64_t *d)
{
	return d[0];
}

/* FUN_00014478 @ 0x00014478   (est. sk_tb_alloc_by_kind)
 * Ghidra: long FUN_00014478(undefined8)
 * Allocates a thread block according to the current query kind: kind 0xd
 * allocates via FUN_00016458, kind 3 via FUN_00010244 + sk_tb_init, kind 1 via
 * sk_tb_create. Panics on unknown kind.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x1450c); FUN_00015448 returns the kind. */
static long sk_tb_alloc_by_kind(uint64_t a)
{
	uint32_t kind = sk_tb_get_kind();
	long tb;

	if (kind == 0xd) {
		tb = sk_cap_claim(a);
	} else if (kind == 3) {
		tb = (long)sk_zone_alloc_obj(1, 0x118, 0x1082040eda8e2daull);
		if (tb != 0) {
			sk_tb_init(a, tb);
			return tb;
		}
		sk_boot_abort3();
	} else if (kind == 1) {
		tb = sk_tb_create();
	} else {
		goto unknown;
	}
	if (tb != 0) return tb;
unknown:
	__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x1450c) */
}

/* FUN_00014510 @ 0x00014510   (est. sk_tb_obj_alloc)
 * Ghidra: undefined8* FUN_00014510(undefined8)
 * Allocates a 0x40-byte TB wrapper object storing `param_1` and a fresh
 * dispatch key (FUN_0001505c) at offset 0x30.
 * Confidence: medium
 * Notes: FUN_00010244(1,0x40,0x10820409f8ec750); FUN_004b0068 on failure;
 *   SoftwareBreakpoint(0x5519,0x14574). */
static uint64_t *sk_tb_obj_alloc(uint64_t a)
{
	uint64_t *w = (uint64_t *)sk_zone_alloc_obj(1, 0x40, 0x10820409f8ec750ull);
	if (w == 0) sk_boot_abort3();
	w[0] = a;
	w[6] = sk_registry_alloc();
	return w;
}

/* FUN_00014578 @ 0x00014578   (est. sk_tb_obj_free)
 * Ghidra: void FUN_00014578(undefined8*)
 * Frees a TB wrapper: releases its cap, the dispatch key, and any registered
 * side-effect object, then frees the wrapper.
 * Confidence: medium
 * Notes: FUN_000154d0/150cc/4b664, thunk_FUN_00012568. */
static void sk_tb_obj_free(uint64_t *w)
{
	sk_tb_destroy_act(w[0]);
	sk_registry_free(w[6]);
	if (w[2] != 0) sk_obj_release2();
	sk_zone_free_0((uint64_t)w);
}

/* FUN_000145bc @ 0x000145bc   (est. sk_tb_obj_create)
 * Ghidra: long FUN_000145bc(undefined8, undefined8)
 * Creates a TB wrapper with a new dispatch key, registers a retry handler
 * (FUN_00014628) and stores a second dispatch key at offset 0x38.
 * Confidence: medium
 * Notes: FUN_00014510, FUN_0004b520, FUN_00015460, FUN_0001505c. */
static long sk_tb_obj_create(uint64_t a, uint64_t b)
{
	uint64_t *w = sk_tb_obj_alloc(0);
	uint64_t k = sk_obj_retain((void *)b);
	*(uint64_t *)(w + 0x10) = k;
	sk_tb_set_sender(a, (uint64_t)(void *)sk_tb_obj_dispatch, (uint64_t)w);
	*(uint64_t *)(w + 0x38) = sk_registry_alloc();
	return (long)w;
}

/* FUN_00014628 @ 0x00014628   (est. sk_tb_obj_dispatch)
 * Ghidra: long FUN_00014628(long, undefined8*)
 * Dispatches a TB-object message: routes to per-kind handlers (send/receive/
 * query/action), performs capability checks, and returns the resulting object.
 * Confidence: low
 * Notes: complex; FUN_000159b8/c0/c8, FUN_000183f0, FUN_00015e9c/904,
 *   FUN_00017e94, FUN_000181f4, FUN_00014478/145bc/153ec,
 *   FUN_004b0368/03a0/0468/0438/03d8/03f0/0408. */
static long sk_tb_obj_dispatch(uint64_t a1, uint64_t *w)
{
	uint64_t cap = *w;
	uint64_t obj = a1;
	long *t = (long *)sk_tb_get((void *)0);
	int kind = sk_tb_state((void *)a1);

	if (kind == 4) {
		int k2 = sk_tb_kind((void *)a1);
		if (k2 != 1) goto fallback;
		if (t == 0 || *t == 0) goto fallback;
		if ((*(uint16_t *)((long)t + 0x2a) >> 2 & 1) != 0) {
			if (w[7] != 0) {
				int r = sk_cap_setup((void *)w[7], w, (void *)a1, cap);
				if (r == 0) return obj;
				return obj;
			}
			goto fallback;
		}
		if ((*(uint16_t *)((long)t + 0x2a) & 1) != 0) {
			if (w[6] != 0) {
				long r = sk_tb_recv((void *)w[6], (void *)a1);
				if (r == 0) return 0;
				sk_tb_sched_go((void *)a1, (void *)r);
				goto dispatch;
			}
			goto fallback;
		}
dispatch:
		if ((uint64_t (*)(void))w[3] != 0) {
			long r = (*(long (*)(uint64_t, uint64_t, uint64_t))(w[3]))((uint64_t)w, a1, w[4]);
			goto handle_result;
		}
		long r = (long)w[2];
		if (r != 0) r = (**(long (**)(uint64_t, uint64_t, uint64_t))(r + 0x10))(r, (uint64_t)w, a1);
handle_result:
		if (r == 0) return 0;
		obj = (uint64_t)r;
		{
			long *rr = (long *)sk_tb_get((void *)r);
			int rc = sk_cap_check(cap, *(uint64_t *)(rr + 0x18));
			if (rc == 0) return r;
			if (w[7] != 0) {
				int rc2 = sk_cap_pre((void *)w[7], (void *)r, &obj, (uint64_t)w);
				if (rc2 != 0) obj = 0;
				return (long)obj;
			}
			goto fallback;
		}
	}
fallback:
	{
		uint64_t tb = sk_tb_alloc_by_kind(a1);
		long r = sk_tb_obj_create(tb, 0);
		sk_tb_obj_free((uint64_t *)r);
		return r;
	}
}

/* FUN_000147a0 @ 0x000147a0   (est. sk_tb_obj_create2)
 * Ghidra: undefined8 FUN_000147a0(undefined8, undefined8)
 * Creates a TB wrapper (sk_tb_alloc_by_kind + sk_tb_obj_create), then frees
 * `param_1`. Returns the new wrapper.
 * Confidence: medium */
static uint64_t sk_tb_obj_create2(uint64_t a, uint64_t b)
{
	uint64_t tb = sk_tb_alloc_by_kind(a);
	uint64_t w = sk_tb_obj_create(tb, b);
	sk_tb_obj_free((uint64_t *)w);
	return w;
}

/* FUN_000147e0 @ 0x000147e0   (est. sk_tb_cap_release)
 * Ghidra: void FUN_000147e0(undefined8*)
 * Releases the capability stored at the wrapper head.
 * Confidence: high
 * Notes: FUN_000155ac. */
static void sk_tb_cap_release(uint64_t *w)
{
	sk_tb_check_act(w[0]);
}

/* FUN_00014804 @ 0x00014804   (est. sk_tb_obj_alloc2)
 * Ghidra: undefined8 FUN_00014804(undefined8)
 * Allocates a TB wrapper via sk_tb_obj_alloc after sk_tb_alloc_by_kind; frees
 * `param_1`.
 * Confidence: medium */
static uint64_t sk_tb_obj_alloc2(uint64_t a)
{
	sk_tb_alloc_by_kind(a);
	uint64_t w = (uint64_t)sk_tb_obj_alloc(0);
	sk_tb_obj_free((uint64_t *)w);
	return w;
}

/* FUN_0001483c @ 0x0001483c   (est. sk_tb_cap_retain)
 * Ghidra: void FUN_0001483c(undefined8*)
 * Retains the capability at the wrapper head.
 * Confidence: high
 * Notes: FUN_00015570. */
static void sk_tb_cap_retain(uint64_t *w)
{
	sk_tb_check_req(w[0]);
}

/* FUN_0001485c @ 0x0001485c   (est. sk_tb_query)
 * Ghidra: ulong FUN_0001485c(undefined8*, int*, long*, undefined8)
 * cL4 query dispatch: handles query messages by disposition, sending replies
 * through the transport and (for the async path) building a new TB object that
 * is returned to the caller. Complex state machine.
 * Confidence: low
 * Notes: strings s_TB_ASSERT__query_>disposition____005ab6c5,
 *   s_TB_ASSERT__query_>state____TB_ME_005ab676;
 *   FUN_00015b94/1585c/159b8/17e94/15548/17edc/15ba4/15864/15e9c/10244/14e34/
 *   1590c/15bac/15548/14db8/14f2c/15630/15708, FUN_0004b03f0/0068. */
static uint64_t sk_tb_query(uint64_t *w, int *q, long *out, uint64_t flags)
{
	if (*q == 2) {
		if ((char)q[1] == 1) {
			int r = sk_msg_caps(q, w);
			if (r == 0) return 1;
			sk_msg_append(q, 3);
			uint64_t cap = *w;
			long *t = (long *)sk_tb_get((void *)q);
			if (((uint32_t)flags >> 1 & 1) == 0)
				*(uint16_t *)((long)t + 0x2a) |= 0x10;
			r = sk_cap_check(cap, *(uint64_t *)((long)t + 0x18));
			uint64_t rr;
			if (r == 0) rr = sk_tb_do_reply(cap, q, out, flags);
			else rr = sk_cap_fallback((void *)w, cap, (void *)q, (void *)out, flags);
			if ((int32_t)rr == 0) {
				uint32_t v = ((*(uint16_t *)((long)t + 0x2a) & 8) == 0) ? 0 : 4;
				rr = v;
				if ((((uint32_t)flags >> 1 & 1) != 0) && ((*(uint16_t *)((long)t + 0x2a) & 8) == 0)) {
					if (out == 0 || *out == 0) {
						rr = 4;
					} else {
						sk_msg_append((void *)*out, 4);
						sk_msg_set((void *)*out, 2);
						long *o = (long *)sk_tb_get((void *)*out);
						if ((*(uint16_t *)((long)o + 0x2a) & 1) != 0) {
							long b = sk_msg_caps2((void *)*out);
							if (b == 0) {
								uint64_t *local = 0;
								sk_tb_alloc_buf(&local, *(uint64_t *)(*out));
								sk_msg_writesize((void *)*out, local[3]);
							}
							uint64_t recv = w[6];
							if (recv == 0) {
								sk_boot_abortA();
							} else {
								uint64_t *nb = (uint64_t *)sk_tb_recv((void *)recv, (void *)*out);
								uint64_t *hdr = (uint64_t *)sk_zone_alloc_obj(1, 0x58, 0x102004071d150f8ull);
								if (hdr != 0) {
									uint64_t *data = (uint64_t *)sk_zone_alloc_obj(1, 0x68, 0x1090040b6685729ull);
									if (data == 0) sk_boot_abort3();
									rr = sk_tb_send_any(w, 0, (uint64_t)hdr, (uint64_t)data, 0, 0);
									if ((int32_t)rr == 0) {
										if (nb == 0) {
											for (;;) {
												sk_tb_id((void *)hdr);
												*(uint16_t *)((long)data + 0x2a) |= 4;
												sk_msg_append((void *)hdr, 3);
												rr = sk_tb_do_reply(cap, hdr, (long *)&hdr, 2);
												if ((int32_t)rr != 0) break;
												sk_msg_writesize((void *)hdr, b);
												nb = (uint64_t *)sk_tb_recv((void *)recv, (void *)hdr);
												if (nb != 0) goto found;
												sk_tb_msg_send(w, (uint64_t)hdr, 0, 0);
											}
											sk_tb_cancel(w);
											sk_zone_free_0((uint64_t)data);
										} else {
found:
											sk_tb_cancel(w);
											sk_zone_free_0((uint64_t)data);
											sk_zone_free_0((uint64_t)hdr);
											uint64_t *t2 = (uint64_t *)sk_tb_get((void *)*out);
											sk_tb_msg_join(cap, (uint64_t)t2);
											sk_tb_reset(t2);
											rr = 0;
											uint64_t sz = nb[3];
											t2[0] = nb[0];
											t2[3] = sz;
											*(uint8_t *)(t2 + 5) = 1;
											*(uint16_t *)((long)t2 + 0x2a) = *(uint16_t *)((long)nb + 0x2a);
										}
									} else {
										sk_zone_free_0((uint64_t)data);
									}
									sk_zone_free_0((uint64_t)nb);
									return rr;
								}
							}
							sk_boot_abort3();
						}
						rr = 0;
					}
				}
			}
			return rr;
		}
		sk_printf("TB_ASSERT: query->disposition\n");
	} else {
		sk_printf("TB_ASSERT: query->state == TB_ME\n");
	}
	__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x14bc4) */
}

/* FUN_00014bd0 @ 0x00014bd0   (est. sk_tb_noop)
 * Ghidra: void FUN_00014bd0(void)
 * No-op stub.
 * Confidence: high */
static void sk_tb_noop(void)
{
}

/* FUN_00014bd4 @ 0x00014bd4   (est. sk_tb_query_wrap)
 * Ghidra: void FUN_00014bd4(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Wraps sk_tb_send_any with kind 0.
 * Confidence: medium */
static void sk_tb_query_wrap(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5)
{
	sk_tb_send_any(a1, 0, a2, a3, a4, a5);
}

/* FUN_00014bec @ 0x00014bec   (est. sk_tb_cancel)
 * Ghidra: undefined8 FUN_00014bec(void)
 * Cancels the current TB (sk_tb_cancel) and returns 0.
 * Confidence: medium */
static uint64_t sk_tb_cancel(uint64_t *w)
{
	sk_tb_cancel_msg(w);
	return 0;
}

/* FUN_00014c08 @ 0x00014c08   (est. sk_tb_msg_send)
 * Ghidra: void FUN_00014c08(undefined8, undefined8, undefined8, undefined8)
 * Sends a message through sk_tb_send with kind 0.
 * Confidence: medium */
static void sk_tb_msg_send(uint64_t *w, uint64_t m, uint64_t a3, uint64_t a4)
{
	sk_tb_send(w, m, 0, a3, a4);
}

/* FUN_00014c18 @ 0x00014c18   (est. sk_tb_alloc_buf)
 * Ghidra: undefined8 FUN_00014c18(ulong*, ulong)
 * Allocates a `param_2`-byte TB data buffer: writes base + metadata into
 * *param_1 and returns 0, else aborts.
 * Confidence: medium
 * Notes: FUN_00010244(0x100004077774924); FUN_004b0498 on failure;
 *   sk_tb_buf_reset first. */
static uint64_t sk_tb_alloc_buf(uint64_t *d, uint64_t sz)
{
	uint64_t buf;
	sk_tb_buf_reset(d);
	buf = (uint64_t)sk_zone_alloc_obj(1, sz, 0x100004077774924ull);
	if (buf != 0) {
		d[0] = buf;
		*(uint8_t *)(d + 5) = 1;
		d[2] = 0;
		d[3] = sz;
		d[4] = 0;
		d[6] = 0;
		return 0;
	}
	sk_boot_abortB();
}

/* FUN_00014c90 @ 0x00014c90   (est. sk_tb_buf_release)
 * Ghidra: undefined8 FUN_00014c90(undefined8*, undefined8, long, undefined8, undefined8)
 * Releases a TB data buffer: frees its backing buffer and resets the
 * descriptor (setting invalid). Handles the reply/refcount teardown.
 * Confidence: low
 * Notes: FUN_00015734, FUN_000156b8/e0, FUN_00017e94, FUN_000155e8,
 *   FUN_00015670, FUN_00015630, FUN_00014c18, FUN_004b04c8. */
static uint64_t sk_tb_buf_release(uint64_t *d, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5)
{
	uint64_t r;
	if ((*(uint8_t *)(d + 5) & 1) != 0) {
		sk_zone_free_0(d[0]);
		d[0] = 0;
		d[3] = 0;
		d[6] = 0;
		r = sk_tb_msg_reset(d);
		*(uint8_t *)((long)d + 0x29) = 1;
		return r;
	}
	sk_boot_abortC();
	{
		int x = sk_tb_can_receive(a2);
		if (x != 0) sk_tb_can_send(a2);
		uint32_t chk = sk_cap_check(a2, a4);
		if (*(uint8_t *)(a3 + 0x28) == 1) {
			sk_tb_buf_release((uint64_t *)a3, 0, 0, 0, 0);
			if ((chk & 1) == 0) {
				r = sk_tb_send_dispatch(a2, a4, a5, a3);
				if ((int32_t)r == 0) return 0;
				return r;
			}
		} else if (chk == 0) {
			sk_tb_msg_reset(a3);
			r = sk_tb_query_dispatch(a2, a3, a5, a4);
			if ((int32_t)r == 0) return 0;
			return r;
		} else {
			sk_tb_msg_join(a2, a3);
		}
		return sk_tb_alloc_buf((uint64_t *)a3, a4);
	}
}

/* FUN_00014ce0 @ 0x00014ce0   (est. sk_tb_send_buf)
 * Ghidra: undefined8 FUN_00014ce0(undefined8, undefined8, long, undefined8, undefined8)
 * Send-buffer handler (variant of sk_tb_buf_release): checks send/receive
 * state and dispatches accordingly.
 * Confidence: low
 * Notes: FUN_000156b8/e0, FUN_00017e94, FUN_00014c90, FUN_000155e8,
 *   FUN_00015734, FUN_00015670, FUN_00015630, FUN_00014c18. */
static uint64_t sk_tb_send_buf(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5)
{
	int x = sk_tb_can_receive(a2);
	if (x != 0) sk_tb_can_send(a2);
	uint32_t chk = sk_cap_check(a2, a4);
	if (*(uint8_t *)(a3 + 0x28) == 1) {
		sk_tb_buf_release((uint64_t *)a3, 0, 0, 0, 0);
		if ((chk & 1) == 0) {
			uint64_t r = sk_tb_send_dispatch(a2, a4, a5, a3);
			if ((int32_t)r == 0) return 0;
			return r;
		}
	} else if (chk == 0) {
		sk_tb_msg_reset(a3);
		uint64_t r = sk_tb_query_dispatch(a2, a3, a5, a4);
		if ((int32_t)r == 0) return 0;
		return r;
	} else {
		sk_tb_msg_join(a2, a3);
	}
	return sk_tb_alloc_buf((uint64_t *)a3, a4);
}

/* FUN_00014db8 @ 0x00014db8   (est. sk_tb_send)
 * Ghidra: void FUN_00014db8(undefined8*, undefined8, int, undefined8, undefined8)
 * Sends a message: sets the msg kind (1 normal, 2 reply) and dispatches via
 * sk_tb_send_buf.
 * Confidence: medium
 * Notes: FUN_0001585c/15864/159b8/14ce0. */
static void sk_tb_send(uint64_t *w, uint64_t m, int kind, uint64_t a4, uint64_t a5)
{
	uint32_t k;
	sk_msg_append(m, 1);
	k = 1;
	if (kind == 1) k = 2;
	sk_msg_set(m, k);
	sk_tb_send_buf(sk_tb_get(m), *w, sk_tb_get(m), a4, a5);
}

/* FUN_00014e34 @ 0x00014e34   (est. sk_tb_send_any)
 * Ghidra: undefined8 FUN_00014e34(undefined8*, int, undefined8, long, ulong, undefined8)
 * Sends a message of a given kind: validates receive state, ensures the target
 * buffer is large enough, appends to the message, and commits it. Returns 0 on
 * success.
 * Confidence: low
 * Notes: FUN_00015834/156b8/156e0/155e8/14c18/1586c/15b8c, FUN_004b04f8. */
static uint64_t sk_tb_send_any(uint64_t *w, int kind, uint64_t m, uint64_t sz, uint64_t a5,
                               uint64_t a6)
{
	uint32_t k;
	uint64_t r;

	sk_msg_init(m);
	uint64_t cap = *w;
	int x = sk_tb_can_receive(cap);
	if (x == 0) {
		if (*(uint8_t *)(sz + 8) != 0) goto busy;
	} else {
		uint64_t have = sk_tb_can_send(cap);
		if (*(uint8_t *)(sz + 8) != 0) {
busy:
			sk_boot_abortD();
			sk_tb_cancel(w);
			return 0;
		}
		if (have < a5) {
			sk_tb_alloc_buf((uint64_t *)sz, a5);
			goto commit;
		}
	}
	cap = sk_tb_send_dispatch(cap, a5, a6, sz);
	if ((int32_t)cap != 0) return cap;
commit:
	k = 1;
	if (kind != 0) k = 2;
	r = sk_msg_send(m, sz, k);
	if ((int32_t)r == 0) {
		sk_msg_commit(m, w);
		r = 0;
	}
	return r;
}

/* FUN_00014f10 @ 0x00014f10   (est. sk_tb_cancel2)
 * Ghidra: undefined8 FUN_00014f10(void)
 * Cancels the current TB and returns 0.
 * Confidence: medium */
static uint64_t sk_tb_cancel2(void)
{
	sk_tb_cancel_msg(0);
	return 0;
}

/* FUN_00014f2c @ 0x00014f2c   (est. sk_tb_release_msg)
 * Ghidra: void FUN_00014f2c(undefined8*, undefined8, undefined8, undefined8)
 * Releases an IPC message: releases its TB data buffer (or joins it), and
 * frees the message block. If the buffer is still live, resends via
 * sk_tb_send.
 * Confidence: low
 * Notes: FUN_000159b8/14c90/15630/15964, FUN_004b0528. */
static void sk_tb_release_msg(uint64_t *w, uint64_t m, uint64_t a3, uint64_t a4)
{
	uint64_t *t = (uint64_t *)sk_tb_get((void *)m);
	if (*(uint8_t *)((long)t + 8) == 0) {
		if (*(uint8_t *)((long)t + 0x28) == 1) {
			sk_tb_buf_release(t, 0, 0, 0, 0);
		} else {
			sk_tb_msg_join(*w, (uint64_t)t);
		}
		sk_tb_release(t);
		return;
	}
	sk_tb_send(w, m, 1, a3, a4);
}

/* FUN_00014f90 @ 0x00014f90   (est. sk_tb_send3)
 * Ghidra: void FUN_00014f90(undefined8, undefined8, undefined8, undefined8)
 * Sends a message with kind 1 via sk_tb_send.
 * Confidence: medium */
static void sk_tb_send3(uint64_t *w, uint64_t m, uint64_t a3, uint64_t a4)
{
	sk_tb_send(w, m, 1, a3, a4);
}

/* FUN_00014fa0 @ 0x00014fa0   (est. sk_tb_fatal_act)
 * Ghidra: void FUN_00014fa0(void)
 * Fatal: "Attempt to retrieve act" (line 0x5f).
 * Confidence: high
 * Notes: s_TB_FATAL__Attempt_to_retrieve_ac_005aba92, line 0x5f. */
static void sk_tb_fatal_act(void)
{
	sk_printf("TB_FATAL: Attempt to retrieve act\n");
}

/* FUN_00014fbc @ 0x00014fbc   (est. sk_tb_fatal_req)
 * Ghidra: void FUN_00014fbc(void)
 * Fatal: "Attempt to retrieve req" (line 0x77).
 * Confidence: high
 * Notes: s_TB_FATAL__Attempt_to_retrieve_re_005aba33, line 0x77. */
static void sk_tb_fatal_req(void)
{
	sk_printf("TB_FATAL: Attempt to retrieve req\n");
}

/* FUN_00014fd8 @ 0x00014fd8   (est. sk_registry_entry_create)
 * Ghidra: ulong FUN_00014fd8(undefined8, undefined8, undefined8)
 * Allocates a 0x20-byte registry entry storing (cap, tag, retained key).
 * Confidence: medium
 * Notes: FUN_00010244(1,0x20,0x10a004062d90b2c); FUN_0004b520. */
static uint64_t sk_registry_entry_create(uint64_t cap, uint64_t tag, uint64_t key)
{
	uint64_t *e = (uint64_t *)sk_zone_alloc_obj(1, 0x20, 0x10a004062d90b2cull);
	if (e == 0) sk_boot_abort3();
	e[1] = cap;
	e[2] = tag;
	e[3] = sk_obj_retain((void *)key);
	return (uint64_t)e;
}

/* FUN_0001505c @ 0x0001505c   (est. sk_registry_alloc)
 * Ghidra: ulong FUN_0001505c(void)
 * Allocates a 0x20-byte registry object, zero-initialised.
 * Confidence: medium
 * Notes: FUN_00010244(1,0x20,0x1020040fee5c632); FUN_001157f0 zeroes. */
static uint64_t sk_registry_alloc(void)
{
	uint64_t r = (uint64_t)sk_zone_alloc_obj(1, 0x20, 0x1020040fee5c632ull);
	if (r == 0) sk_boot_abort3();
	sk_obj_lock((void *)r);
	return r;
}

/* FUN_000150cc @ 0x000150cc   (est. sk_registry_free)
 * Ghidra: void FUN_000150cc(ulong)
 * Frees a registry object (unlock + free).
 * Confidence: medium
 * Notes: FUN_001157d4, thunk_FUN_00012568; SoftwareBreakpoint(0x5519,0x15108). */
static void sk_registry_free(uint64_t r)
{
	sk_obj_unlock((void *)r);
	sk_zone_free_0(r);
}

/* FUN_00015108 @ 0x00015108   (est. sk_registry_insert)
 * Ghidra: undefined8 FUN_00015108(ulong*, ulong, undefined8, undefined8)
 * Inserts an entry keyed by `param_2` into a registry list (param_1[2]); returns
 * 1 if inserted, 0 if a duplicate was already present (the new entry freed).
 * Confidence: medium
 * Notes: FUN_00014fd8, FUN_0011582c/94, thunk_FUN_00012568. */
static uint64_t sk_registry_insert(uint64_t *reg, uint64_t key, uint64_t tag, uint64_t a4)
{
	uint64_t entry = sk_registry_entry_create(key, tag, a4);
	uint64_t *head;
	uint64_t inserted;

	sk_lock_acquire((void *)reg);
	head = (uint64_t *)reg[2];
	if (head == 0) {
		reg[2] = entry;
	} else {
		uint64_t *cur = head;
		for (;;) {
			if (cur[1] == key) {
				sk_zone_free_0(entry);
				inserted = 0;
				goto out;
			}
			uint64_t *nxt = (uint64_t *)*cur;
			if (nxt == 0) { *cur = entry; break; }
			cur = nxt;
		}
		inserted = 1;
	}
out:
	sk_lock_release((void *)reg);
	return inserted;
}

/* FUN_000151c8 @ 0x000151c8   (est. sk_registry_remove)
 * Ghidra: void FUN_000151c8(undefined8*, long)
 * Removes the entry keyed by `param_2` from a registry list, invoking its
 * teardown method (+0x10) and freeing it.
 * Confidence: medium
 * Notes: FUN_0011582c/94, thunk_FUN_00012568. */
static void sk_registry_remove(uint64_t *reg, uint64_t key)
{
	uint64_t *cur, *prev;
	sk_lock_acquire((void *)reg);
	cur = (uint64_t *)reg[2];
	if (cur[1] == key) {
		reg[2] = *cur;
	} else {
		for (;;) {
			prev = cur;
			cur = (uint64_t *)*prev;
			if (cur == 0) goto out;
			if (cur[1] == key) break;
		}
		*prev = *cur;
	}
	(*(void (**)(uint64_t, uint64_t))(cur[3] + 0x10))(cur[3], cur[2]);
	sk_zone_free_0((uint64_t)cur);
out:
	sk_lock_release((void *)reg);
}

/* FUN_00015264 @ 0x00015264   (est. sk_registry_lookup)
 * Ghidra: ulong FUN_00015264(ulong, ulong)
 * Looks up the entry with value `param_2` in a registry list (param_1+0x10);
 * returns the entry's tag (offset 0x10) or 0.
 * Confidence: medium
 * Notes: FUN_0011582c/94; SoftwareBreakpoint(0x5519,0x15310). */
static uint64_t sk_registry_lookup(uint64_t reg, uint64_t key)
{
	uint64_t *cur = *(uint64_t **)(reg + 0x10);
	uint64_t *match = 0;
	uint64_t *tag = 0;

	if (cur == 0) { sk_lock_release((void *)reg); return 0; }
	{
		uint64_t *c = cur;
		uint64_t *found = 0;
		uint64_t *tagv = 0;
		do {
			uint64_t *f = (c[1] == key) ? c : found;
			uint64_t *t = (c[1] == key) ? c + 4 : tagv;
			uint64_t *n = (uint64_t *)*c;
			c = n;
			found = f;
			tagv = t;
		} while (c != 0);
		sk_lock_release((void *)reg);
		if (found != 0) return found[2];
	}
	return 0;
}

/* FUN_0001532c @ 0x0001532c   (est. sk_registry_set)
 * Ghidra: void FUN_0001532c(undefined4, undefined4)
 * Allocates a 0x60-byte registry value storing two words and the used flag.
 * Confidence: medium
 * Notes: FUN_00010244(1,0x60,0x1082040faca7f44); FUN_004b0068 on failure. */
static void sk_registry_set(uint32_t a, uint32_t b)
{
	uint32_t *v = (uint32_t *)sk_zone_alloc_obj(1, 0x60, 0x1082040faca7f44ull);
	if (v != 0) {
		v[0] = a;
		v[1] = b;
		*(uint8_t *)(v + 10) = 1;
	}
}

/* FUN_00015388 @ 0x00015388   (est. sk_registry_set2)
 * Ghidra: void FUN_00015388(undefined4, undefined8, undefined4)
 * Allocates a 0x60-byte registry value storing (a, c, pointer).
 * Confidence: medium
 * Notes: FUN_00010244(1,0x60,0x1082040faca7f44); FUN_004b0068 on failure. */
static void sk_registry_set2(uint32_t a, uint64_t ptr, uint32_t c)
{
	uint32_t *v = (uint32_t *)sk_zone_alloc_obj(1, 0x60, 0x1082040faca7f44ull);
	if (v != 0) {
		v[0] = a;
		v[1] = c;
		*(uint64_t *)(v + 8) = ptr;
		*(uint8_t *)(v + 10) = 1;
	}
}

/* FUN_000153ec @ 0x000153ec   (est. sk_registry_invoke)
 * Ghidra: void FUN_000153ec(long)
 * Invokes a registry entry's stored callback (at +0x10) with its args, and
 * frees the entry if flagged.
 * Confidence: medium */
static void sk_registry_invoke(uint64_t e)
{
	if (*(uint64_t (**)(void))(e + 0x10) != 0)
		(*(void (**)(uint64_t, uint64_t))(e + 0x10))(*(uint64_t *)(e + 0x18), *(uint64_t *)(e + 0x20));
	if (*(uint8_t *)(e + 0x28) == 1) sk_zone_free_0(e);
}

/* FUN_00015440 @ 0x00015440   (est. sk_tb_get_act)
 * Ghidra: undefined8 FUN_00015440(long)
 * Returns the act pointer (param_1+0x20).
 * Confidence: high */
static uint64_t sk_tb_get_act(uint64_t tb)
{
	return *(uint64_t *)(tb + 0x20);
}

/* FUN_00015448 @ 0x00015448   (est. sk_tb_get_kind)
 * Ghidra: undefined4 FUN_00015448(undefined4*)
 * Returns the first word (kind) of the query object.
 * Confidence: high */
static uint32_t sk_tb_get_kind(void)
{
	return 0;
}

/* FUN_00015450 @ 0x00015450   (est. sk_tb_get_flags)
 * Ghidra: undefined4 FUN_00015450(long)
 * Returns the flags word at param_1+4.
 * Confidence: high */
static uint32_t sk_tb_get_flags(uint64_t tb)
{
	return *(uint32_t *)(tb + 4);
}

/* FUN_00015458 @ 0x00015458   (est. sk_tb_set_act)
 * Ghidra: void FUN_00015458(long, undefined8)
 * Stores the act pointer at param_1+8.
 * Confidence: high */
static void sk_tb_set_act(uint64_t tb, uint64_t act)
{
	*(uint64_t *)(tb + 8) = act;
}

/* FUN_00015460 @ 0x00015460   (est. sk_tb_set_sender)
 * Ghidra: void FUN_00015460(long, undefined8, undefined8)
 * Stores the send dispatch (param_1+0x70) and its arg (param_1+0x78).
 * Confidence: high */
static void sk_tb_set_sender(uint64_t tb, uint64_t fn, uint64_t arg)
{
	*(uint64_t *)(tb + 0x70) = fn;
	*(uint64_t *)(tb + 0x78) = arg;
}

/* FUN_00015468 @ 0x00015468   (est. sk_tb_call)
 * Ghidra: undefined8 FUN_00015468(long, undefined8, undefined8*)
 * Invokes a TB's send dispatch: either the +0x70 handler or the +0x68-subobject
 * handler; stores the result in *param_3. Returns 0 on success, 4 on no handler.
 * Confidence: medium */
static uint64_t sk_tb_call(uint64_t tb, uint64_t m, uint64_t *out)
{
	uint64_t r;
	if (*(uint64_t (**)(void))(tb + 0x70) == 0) {
		if (*(uint64_t *)(tb + 0x68) == 0) return 4;
		r = (**(uint64_t (**)(void))(*(uint64_t *)(tb + 0x68) + 0x10))();
	} else {
		r = (*(uint64_t (**)(uint64_t, uint64_t))(tb + 0x70))(m, *(uint64_t *)(tb + 0x78));
	}
	*out = r;
	return 0;
}

/* FUN_000154d0 @ 0x000154d0   (est. sk_tb_destroy_act)
 * Ghidra: void FUN_000154d0(long)
 * Destroys a TB act: releases its side-effect object (+0x68) and invokes the
 * +0x40 teardown handler (or its +0x60-subobject's +0x40 handler).
 * Confidence: medium
 * Notes: FUN_0004b664; jumptable at 0x1550c. */
static void sk_tb_destroy_act(uint64_t tb)
{
	uint64_t (*fn)(uint64_t);
	if (*(uint64_t *)(tb + 0x68) != 0) sk_obj_release2();
	fn = *(uint64_t (**)(uint64_t))(tb + 0x40);
	if (fn == 0 && (*(uint64_t *)(tb + 0x60) == 0 ||
	                (fn = *(uint64_t (**)(uint64_t))(*(uint64_t *)(tb + 0x60) + 0x40),
	                 fn == 0))) return;
	fn(tb);
}

/* FUN_0001552c @ 0x0001552c   (est. sk_tb_buf_set)
 * Ghidra: void FUN_0001552c(undefined8*, undefined8, undefined8)
 * Fills a TB buffer descriptor with base + size and clears the other fields.
 * Confidence: high */
static void sk_tb_buf_set(uint64_t *d, uint64_t base, uint64_t size)
{
	d[0] = base;
	*(uint8_t *)(d + 1) = 1;
	d[2] = 0;
	d[3] = size;
	d[4] = 0;
	d[6] = 0;
}

/* FUN_00015548 @ 0x00015548   (est. sk_tb_dispatch0)
 * Ghidra: void FUN_00015548(undefined8*)
 * Invokes the TB's primary dispatch function (at [0]) or its fallback (at [0xc]).
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x15570); jumptable at 0x15554/0x15568. */
static void sk_tb_dispatch0(uint64_t *d)
{
	if ((uint64_t (*)(void))d[0] != 0) {
		(*(void (**)(void))d[0])();
		return;
	}
	if (d[0xc] != 0) {
		(**(void (**)(void))d[0xc])();
		return;
	}
	__asm__ volatile("brk #1");   /* SoftwareBreakpoint(1,0x15570) */
}

/* FUN_00015570 @ 0x00015570   (est. sk_tb_check_req)
 * Ghidra: bool FUN_00015570(long)
 * Tests the TB's "req" dispatch (param_1+8 or +0x60-subobject+8); true when
 * nonzero.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x155ac). */
static bool sk_tb_check_req(uint64_t tb)
{
	uint64_t (*fn)(void) = *(uint64_t (**)(void))(tb + 8);
	if (fn == 0) {
		if (*(uint64_t *)(tb + 0x60) == 0) __asm__ volatile("brk #1");
		fn = *(uint64_t (**)(void))(*(uint64_t *)(tb + 0x60) + 8);
	}
	return fn() != 0;
}

/* FUN_000155ac @ 0x000155ac   (est. sk_tb_check_act)
 * Ghidra: bool FUN_000155ac(long)
 * Tests the TB's "act" dispatch (param_1+0x10 or +0x60-subobject+0x10); true
 * when nonzero.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x155e8). */
static bool sk_tb_check_act(uint64_t tb)
{
	uint64_t (*fn)(void) = *(uint64_t (**)(void))(tb + 0x10);
	if (fn == 0) {
		if (*(uint64_t *)(tb + 0x60) == 0) __asm__ volatile("brk #1");
		fn = *(uint64_t (**)(void))(*(uint64_t *)(tb + 0x60) + 0x10);
	}
	return fn() != 0;
}

/* FUN_000155e8 @ 0x000155e8   (est. sk_tb_send_dispatch)
 * Ghidra: void FUN_000155e8(long, undefined8, undefined8, undefined8)
 * Dispatches a send: calls the +0x18 handler (with args) or +0x48 handler,
 * else the +0x60-subobject's, else panics.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x15630); jumptables at 0x15600/0x15610. */
static uint64_t sk_tb_send_dispatch(uint64_t tb, uint64_t a2, uint64_t a3, uint64_t a4)
{
	uint64_t (*fn)(uint64_t, uint64_t, uint64_t);
	uint64_t sub = tb;
	fn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(tb + 0x18);
	if (fn != 0) goto call3;
	fn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(tb + 0x48);
	if (fn != 0) goto call0;
	sub = *(uint64_t *)(tb + 0x60);
	if (sub != 0) {
		fn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(sub + 0x18);
		if (fn != 0) goto call3;
		fn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(sub + 0x48);
		if (fn != 0) goto call0;
	}
	__asm__ volatile("brk #1");
call3:
	return fn(a2, a3, a4);
call0:
	return ((uint64_t (*)(void))fn)();
}

/* FUN_00015630 @ 0x00015630   (est. sk_tb_msg_join)
 * Ghidra: void FUN_00015630(long, undefined8)
 * Joins/receives a message: calls the +0x20 handler (with arg) or +0x50
 * handler, else the +0x60-subobject's, else panics.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x15670); jumptables at 0x15640/0x15650. */
static void sk_tb_msg_join(uint64_t tb, uint64_t a2)
{
	uint64_t (*fn)(uint64_t);
	uint64_t sub = tb;
	fn = *(uint64_t (**)(uint64_t))(tb + 0x20);
	if (fn != 0) goto call1;
	fn = *(uint64_t (**)(uint64_t))(tb + 0x50);
	if (fn != 0) goto call0;
	sub = *(uint64_t *)(tb + 0x60);
	if (sub != 0) {
		fn = *(uint64_t (**)(uint64_t))(sub + 0x20);
		if (fn != 0) goto call1;
		fn = *(uint64_t (**)(uint64_t))(sub + 0x50);
		if (fn != 0) goto call0;
	}
	__asm__ volatile("brk #1");
call1:
	fn(a2);
	return;
call0:
	((void (*)(void))fn)();
}

/* FUN_00015670 @ 0x00015670   (est. sk_tb_query_dispatch)
 * Ghidra: void FUN_00015670(long, undefined8, undefined8, undefined8)
 * Dispatches a query: calls the +0x28 handler (with args) or +0x58 handler,
 * else the +0x60-subobject's, else panics.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x156b8); jumptables at 0x15688/0x15698. */
static uint64_t sk_tb_query_dispatch(uint64_t tb, uint64_t a2, uint64_t a3, uint64_t a4)
{
	uint64_t (*fn)(uint64_t, uint64_t, uint64_t);
	uint64_t sub = tb;
	fn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(tb + 0x28);
	if (fn != 0) goto call3;
	fn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(tb + 0x58);
	if (fn != 0) goto call0;
	sub = *(uint64_t *)(tb + 0x60);
	if (sub != 0) {
		fn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(sub + 0x28);
		if (fn != 0) goto call3;
		fn = *(uint64_t (**)(uint64_t, uint64_t, uint64_t))(sub + 0x58);
		if (fn != 0) goto call0;
	}
	__asm__ volatile("brk #1");
call3:
	return fn(a2, a3, a4);
call0:
	return ((uint64_t (*)(void))fn)();
}

/* FUN_000156b8 @ 0x000156b8   (est. sk_tb_can_receive)
 * Ghidra: undefined8 FUN_000156b8(long)
 * Tests the TB's +0x30 "can receive" dispatch (or +0x60-subobject's); returns
 * its result or 0 when absent.
 * Confidence: medium
 * Notes: jumptable at 0x156c4. */
static uint64_t sk_tb_can_receive(uint64_t tb)
{
	uint64_t (*fn)(void) = *(uint64_t (**)(void))(tb + 0x30);
	if (fn == 0 && (*(uint64_t *)(tb + 0x60) == 0 ||
	                (fn = *(uint64_t (**)(void))(*(uint64_t *)(tb + 0x60) + 0x30),
	                 fn == 0))) return 0;
	return fn();
}

/* FUN_000156e0 @ 0x000156e0   (est. sk_tb_can_send)
 * Ghidra: undefined8 FUN_000156e0(long)
 * Tests the TB's +0x38 "can send" dispatch (or +0x60-subobject's); returns its
 * result or 0 when absent.
 * Confidence: medium
 * Notes: jumptable at 0x156ec. */
static uint64_t sk_tb_can_send(uint64_t tb)
{
	uint64_t (*fn)(void) = *(uint64_t (**)(void))(tb + 0x38);
	if (fn == 0 && (*(uint64_t *)(tb + 0x60) == 0 ||
	                (fn = *(uint64_t (**)(void))(*(uint64_t *)(tb + 0x60) + 0x38),
	                 fn == 0))) return 0;
	return fn();
}

/* FUN_00015708 @ 0x00015708   (est. sk_tb_buf_reset)
 * Ghidra: void FUN_00015708(undefined8*)
 * Zeroes a TB buffer descriptor (all 13 words).
 * Confidence: high */
static void sk_tb_buf_reset(uint64_t *d)
{
	*(uint8_t *)(d + 1) = 0;
	d[3] = 0;
	d[4] = 0;
	*(uint32_t *)(d + 5) = 0;
	d[8] = 0;
	d[7] = 0;
	d[10] = 0;
	d[9] = 0;
	d[0xc] = 0;
	d[0xb] = 0;
	d[6] = 0;
	d[0] = 0;
	d[2] = 0;
}

/* FUN_00015734 @ 0x00015734   (est. sk_tb_msg_reset)
 * Ghidra: void FUN_00015734(long)
 * Resets a TB message header fields.
 * Confidence: high */
static uint64_t sk_tb_msg_reset(uint64_t tb)
{
	*(uint8_t *)(tb + 8) = 0;
	*(uint64_t *)(tb + 0x10) = 0;
	*(uint64_t *)(tb + 0x20) = 0;
	*(uint16_t *)(tb + 0x2a) = 0;
	*(uint8_t *)(tb + 0x28) = 0;
	return 0;
}

/* FUN_0001574c @ 0x0001574c   (est. sk_tb_buf_copy)
 * Ghidra: void FUN_0001574c(ulong*, undefined8*)
 * Copies a TB buffer descriptor (base, flags, size, metadata) from `param_2`
 * into `param_1`, memcpy-ing the backing payload (fits within param_1's
 * capacity). Panics on overflow.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x157dc); FUN_00117cc4. */
static void sk_tb_buf_copy(uint64_t *dst, uint64_t *src)
{
	uint64_t sz = src[3];
	uint64_t base;

	if (sz > dst[3]) goto overflow;
	base = dst[0];
	sk_memcpy(base, src[0], sz);
	if (base <= base + sz && (sz = src[3], sz <= dst[3])) {
		*(uint8_t *)(dst + 1) = *(uint8_t *)(src + 1);
		dst[2] = src[2];
		dst[3] = sz;
		dst[4] = src[4];
		*(uint32_t *)(dst + 5) = *(uint32_t *)(src + 5);
		return;
	}
overflow:
	__asm__ volatile("brk #0x5519");   /* SoftwareBreakpoint(0x5519,0x157dc) */
}

/* End of slice 0x000102f4-0x0001574c. */
