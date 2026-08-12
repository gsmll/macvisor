/* sk_slice_06_shared.h — shared declarations for SK slice 06 (VAS subsystem,
 * region 0x0002ee90-0x00038184). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched. Included by
 * sk_slice_06.c and by each transcription fragment. */
#ifndef _SK_SLICE_06_SHARED_H_
#define _SK_SLICE_06_SHARED_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ---- Shared kernel helpers (FUN_ address = ground truth). ---- */
extern void sk_printf(const char *fmt, ...);                    /* FUN_00118b28 */
extern void sk_vas_abort(const char *fmt, ...) __attribute__((noreturn)); /* FUN_004afae4 */
extern int  sk_vm_lock_acquire(void);                           /* FUN_00118164 */
extern int  sk_vm_lock_release(void);                           /* FUN_00118194 */
extern int  sk_mutex_init(void *lock, uint32_t flags);          /* FUN_00118148 */
extern void sk_mem_zero(void *p, uint64_t v, uint64_t n);       /* FUN_001143a0 */
extern void sk_memcpy(uint64_t d, uint64_t s, uint64_t n);      /* FUN_00117cc4 */
extern void sk_memmove(void *d, void *s, uint64_t n);           /* FUN_00117d14 */
extern uint64_t sk_percpu_base(void);                           /* thunk_FUN_00060524 */
extern bool sk_obj_cmp(uint64_t a, uint64_t b);                 /* thunk_FUN_000539c0 */
extern uint8_t sk_trap_alloc_region(uint64_t kind, void *in, void *out,
                                    uint64_t a, void *stk);     /* FUN_0003c510 */
extern void sk_stack_chk_fail(void) __attribute__((noreturn));  /* FUN_0011d7e8 */
extern void sk_boot_fatal2(void) __attribute__((noreturn));     /* FUN_00116d60 */
extern void sk_vspace_alloc(uint64_t *out, uint64_t type, uint64_t flags); /* FUN_0005acac */
extern uint64_t sk_vspace_lookup(uint64_t type, uint64_t flags);            /* FUN_0005baac */
extern void sk_list_init(void *head);                           /* FUN_0005ba5c */
extern void sk_vm_lock_init_l(uint64_t lock, uint32_t flags);   /* FUN_00053aa4 */
extern uint64_t sk_vm_lock_acquire_l(uint64_t lock);            /* FUN_00053ae0 */
extern void sk_vm_lock_release_l(uint64_t lock);                /* FUN_00053b28 */

/* LZCOUNT: leading-zero count (Ghidra renders clz as LZCOUNT). */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))

/* VAS lock token pair. */
typedef struct { uint64_t flags; uint64_t counter; } sk_vas_lock_tok_t;

#define SK_ASRT_PANIC(line) sk_vas_abort("VAS assertion @0x%x", (unsigned)(line))

/* ---- VAS slot-manager. ---- */
typedef struct {
    uint8_t  pad[0x1f0];
    uint64_t count;      /* +0x1f0 */
    uint64_t write_idx;  /* +0x1f8 */
    uint64_t *ring;      /* +0x200 */
    uint64_t pad2;       /* +0x208 */
} sk_vas_slots_t;

static sk_vas_slots_t *sk_vas_slots(uint64_t vas);
static uint64_t *sk_vas_slot_reserve(sk_vas_slots_t *slots);
static void slot_res_store(uint64_t *slot, uint64_t code);
typedef struct { uint8_t present; uint8_t pad; uint32_t code; } sk_vas_res_t;
static void sk_vas_res_set(sk_vas_res_t *r, uint32_t code);
static void sk_vas_res_clear(sk_vas_res_t *r);
static void sk_vas_done(void *ctx, uint32_t hi16, uint32_t lo32);
static void sk_vas_check_result(uint64_t code);

/* ---- Forward declarations of all 120 slice functions. ---- */
static void sk_vas_op_0(uint64_t vas, uint64_t a2, uint64_t a3, uint64_t a4, void *cb);      /* 2ee90 */
static void sk_vas_op_1(uint64_t vas, void *cb);                                              /* 2f09c */
static void sk_vas_op_2(uint64_t vas, uint64_t a2, uint64_t a3, uint64_t a4, void *cb);      /* 2f240 */
static void sk_vas_op_3(uint64_t vas, uint64_t a2, uint64_t a3, void *cb);                   /* 2f3fc */
static void sk_vas_op_4(uint64_t vas, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, void *cb); /* 2f5b0 */
static void sk_vas_op_5(uint64_t vas, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, void *cb); /* 2f780 */
static void sk_vas_teardown(uint64_t vas);                                                    /* 2f94c */
static uint64_t *sk_vas_slot_lookup(uint64_t vas, uint64_t key);                              /* 2fa34 */
static sk_vas_lock_tok_t sk_vas_build(uint64_t vas, uint64_t *out);                           /* 2fa84 */
static void sk_cap_split(uint64_t *out, uint64_t *span, uint64_t phys, uint64_t off, int flag); /* 2fb88 */
static void sk_vas_span_map_thunk(void);                                                      /* 2ff40 */
static sk_vas_lock_tok_t sk_vas_span_map2(uint64_t *vas, uint64_t *span, uint64_t phys,
                                          uint32_t *pt, int write);                           /* 2ff48 */
static sk_vas_lock_tok_t sk_vas_span_map3(uint64_t *vas, uint64_t *span, uint64_t phys,
                                          uint32_t *pt, int write);                           /* 304c4 */
static void sk_vas_pt_write(uint32_t *dst, uint32_t *src, uint8_t *map, uint64_t off);        /* 304d0 */
static uint64_t sk_vas_pt_count(uint32_t *dst, uint32_t *src, char *map, uint64_t n);         /* 30780 */
static uint64_t *sk_vas_desc_init(uint64_t *d);                                               /* 30b2c */
static uint64_t *sk_vas_desc_init2(uint64_t *d, uint64_t base);                               /* 30b9c */
static void sk_vas_add(uint64_t vas, uint64_t *desc);                                         /* 30c70 */
static bool sk_vas_is_page(uint64_t o);                                                       /* 30ca8 */
static bool sk_vas_is_span(uint64_t o);                                                       /* 30cb8 */
static uint64_t sk_vas_page_alloc(uint64_t vas);                                              /* 30cc8 */
static void sk_vas_page_add(uint64_t vas, uint64_t *page);                                    /* 30fb0 */
static void sk_vas_page_free(uint64_t vas, uint64_t page);                                    /* 314b4 */
static void sk_vas_page_map(uint64_t vas, uint64_t p);                                        /* 31594 */
static void sk_vas_global_init(void);                                                         /* 31868 */
static uint64_t sk_vas_rebuild(uint64_t vas, uint64_t kind);                                  /* 31a8c */
static void sk_vas_rebuild_inner(uint64_t vas);                                               /* 31bf4 */
static uint64_t *sk_vas_registry(void);                                                       /* 32514 */
static uint64_t *sk_vas_new(char *p, uint64_t a2, uint64_t a3, uint64_t a4);                  /* 32520 */
static void sk_vas_init(uint64_t vas, uint64_t *p, uint64_t a3, uint64_t a4, uint64_t a5);    /* 3264c */
static void sk_vas_destroy(uint64_t *vas);                                                    /* 32774 */
static void sk_vas_teardown2(uint64_t vas);                                                   /* 32888 */
static void sk_vas_reinit(uint64_t vas, uint64_t a2, uint64_t a3);                            /* 32c68 */
static void sk_vas_chk_bounds0(uint64_t vas);                                                 /* 32cd0 */
static void sk_vas_chk_bounds1(uint64_t vas);                                                 /* 32cec */
static void sk_vas_error_string(uint64_t *out, uint8_t code);                                 /* 32d08 */
static void sk_vas_abort0(uint64_t a) __attribute__((noreturn));                              /* 32e1c */
static void sk_vas_abort1(uint64_t a) __attribute__((noreturn));                              /* 32e30 */
static void sk_pool_alloc_0(void);                                                            /* 32e44 */
static uint64_t *sk_pool_alloc(uint64_t pool, uint16_t *meta, int grab);                      /* 32e90 */
static void sk_pool_free_0(uint64_t page);                                                    /* 33148 */
static void sk_pool_free(uint64_t pool, uint16_t *meta, uint64_t *page);                      /* 331a0 */
static void sk_pool_alloc_1(void);                                                            /* 332b8 */
static void sk_pool_free_1(uint64_t page);                                                    /* 33304 */
static void sk_pool_alloc_2(void);                                                            /* 3335c */
static void sk_pool_alloc_3(void);                                                            /* 333a8 */
static void sk_pool_free_3(uint64_t page);                                                    /* 333f4 */
static void sk_pool_alloc_4(void);                                                            /* 3344c */
static void sk_pool_free_4(uint64_t page);                                                    /* 33498 */
static void sk_pool_alloc_5(void);                                                            /* 334f0 */
static void sk_pool_free_5(uint64_t page);                                                    /* 3353c */
static void sk_pool_alloc_6(void);                                                            /* 33594 */
static void sk_pool_free_6(uint64_t page);                                                    /* 335e0 */
static void sk_pool_alloc_7(void);                                                            /* 33638 */
static void sk_pool_free_7(uint64_t page);                                                    /* 33684 */
static void sk_pool_alloc_8(void);                                                            /* 336e0 */
static void sk_vas_registry_init(void);                                                       /* 33780 */
static void sk_vas_registry_call(uint64_t o);                                                 /* 33b50 */
static void sk_vas_heap_init(void);                                                           /* 33bb0 */
static uint64_t sk_vas_heap_alloc_span(uint8_t k, uint64_t base, uint64_t n, uint8_t m);      /* 33c60 */
static void sk_vas_region_alloc(void);                                                        /* 33da4 */
static uint64_t sk_vas_region_free(uint64_t page);                                            /* 33e00 */
static uint64_t sk_vas_region_alloc2(void);                                                   /* 33e64 */
static uint64_t *sk_vas_heap_alloc(void);                                                     /* 33f1c */
static void sk_vas_heap_free(uint64_t page);                                                  /* 341f4 */
static void sk_vas_mark_slots(uint64_t a);                                                    /* 34334 */
static uint64_t sk_vas_alloc_direct(void);                                                    /* 3433c */
static uint64_t sk_vas_alloc_indirect(void);                                                  /* 34340 */
static uint64_t sk_vas_alloc_slow(void);                                                      /* 34468 */
static void sk_vas_reserve(uint64_t vas, uint8_t *meta);                                      /* 3456c */
static void sk_vas_unreserve(uint64_t vas, uint64_t meta, uint64_t addr);                     /* 346c0 */
static void sk_capslot_alloc(void);                                                           /* 347c4 */
static void sk_capslot_free(uint64_t cap);                                                    /* 3481c */
static void sk_vas_abort2(uint64_t a) __attribute__((noreturn));                              /* 34874 */
static bool sk_vas_check_init(void);                                                          /* 34888 */
static void sk_vas_check_grow(void);                                                          /* 348d0 */
static void sk_vas_set_root(uint64_t v);                                                      /* 34920 */
static uint64_t *sk_vas_obj_init(uint64_t a, uint64_t b, uint64_t *c);                        /* 34970 */
static sk_vas_lock_tok_t sk_vas_obj_root(void);                                               /* 34a2c */
static void sk_vas_check_inc(void);                                                           /* 34a5c */
static void sk_vas_check_dec(void);                                                           /* 34ad0 */
static void sk_vas_lock_init(uint64_t lock, uint64_t a2, uint64_t a3);                        /* 34b10 */
static bool sk_vas_locked(uint64_t lock);                                                     /* 34ba4 */
static sk_vas_lock_tok_t sk_vas_lock_acquire(uint64_t lock);                                  /* 34bd8 */
static void sk_vas_lock_release(uint64_t lock, uint8_t flags, uint64_t counter);              /* 34d5c */
static uint64_t sk_vas_slot_alloc(void);                                                      /* 34f70 */
static uint64_t sk_capslot_take(void);                                                        /* 351a0 */
static void sk_capslot_push(uint64_t *cap);                                                   /* 35204 */
static void sk_rb_insert(uint64_t *root, uint64_t node);                                      /* 35254 */
static uint64_t sk_rb_find(uint64_t addr);                                                    /* 35418 */
static uint64_t sk_vas_slot_alloc_range(uint64_t va, uint64_t n, uint64_t total);             /* 3548c */
static bool sk_capslot_mark(uint64_t *cap, uint64_t va);                                      /* 35684 */
static void sk_vas_mark_cap_slots(uint64_t va, uint64_t n, uint64_t a3, uint64_t a4);         /* 3573c */
static void sk_vas_mark_cb(uint64_t a, uint64_t b, uint64_t c, uint64_t d);                   /* 35944 */
static void sk_vas_reinit_thunk(uint64_t a, uint64_t b, uint64_t c, uint64_t d);              /* 359a0 */
static void sk_vas_set(uint64_t v);                                                           /* 359ac */
static void sk_vas_destroy_check(uint64_t vas, uint64_t kind);                                /* 359d4 */
static void sk_vas_boot_init(uint64_t a, uint64_t b, uint64_t c);                             /* 35a78 */
static uint64_t sk_capslot_alloc_zero(void);                                                  /* 35b98 */
static void sk_vas_map_lookup(uint64_t *d, uint64_t span, uint64_t phys);                     /* 35ba0 */
static void sk_vas_cap_build(uint64_t *out, uint64_t kind, uint64_t a3, uint64_t a4, uint32_t flag); /* 35bac */
static void sk_vas_span_map(uint64_t *out, uint64_t span, uint64_t phys, uint64_t a4, uint64_t a5); /* 36008 */
static uint64_t sk_vas_cap_get(uint64_t cap);                                                 /* 36010 */
static void sk_vas_cap_lookup(uint64_t *out, uint64_t cap, uint32_t kind, void (*cb)(uint64_t)); /* 3611c */
static void sk_vas_cap_describe(uint64_t *out, uint64_t cap, uint32_t kind);                  /* 363ac */
static void sk_vas_cap_desc_walk(uint64_t *cap, uint32_t kind);                               /* 3652c */
static uint64_t sk_vas_cap_next(char *it);                                                    /* 3667c */
static void sk_vas_cap_merge(uint64_t *out, uint64_t a, uint64_t b);                          /* 367a8 */
static uint32_t sk_vas_cap_kind(uint32_t cap);                                                /* 368f8 */
static void sk_vas_cap_free(uint64_t cap, void (*cb)(uint64_t));                              /* 36920 */
static void sk_vas_cap_clone(uint64_t *out, uint64_t cap, uint64_t n);                        /* 36a94 */
static sk_vas_lock_tok_t sk_vas_cap_insert(uint64_t *slots, uint64_t cap, uint32_t n, uint32_t flag); /* 36bd4 */
static void sk_vas_cap_alloc_slot(uint64_t slots, uint64_t cap);                              /* 36d58 */
static void sk_vas_span_alloc(uint64_t *out, uint64_t *slots, uint32_t kind, uint64_t flag);  /* 36dec */
static uint32_t sk_vas_slot_remove(uint64_t *slots, uint32_t idx, uint32_t n);                /* 3730c */
static sk_vas_lock_tok_t sk_vas_slot_compact(uint64_t *slots, uint32_t kind, void (*cb)(uint64_t)); /* 373a4 */
static void sk_vas_span_free(uint64_t *slots, void (*cb)(uint64_t));                           /* 37e9c */
static void sk_freezer_alloc(uint64_t size, uint64_t *out);                                   /* 37fb8 */
static void sk_freezer_bump(uint64_t *fz, uint64_t size);                                     /* 380b4 */
static void sk_freezer_destroy(uint64_t *fz);                                                 /* 38184 */

#endif /* _SK_SLICE_06_SHARED_H_ */
