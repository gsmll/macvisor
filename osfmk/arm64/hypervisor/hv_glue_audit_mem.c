/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
/* hv_glue_audit_mem.c — kernel touch-set recreation (tree hv-deps, FULL-AUDIT). */
#include "hv_compat.h"

/*
 * hv_glue_audit_mem.c — the kernel memory/copy touch-set the hypervisor calls
 * directly (category Mem), recreated per the FULL-AUDIT rule in AGENTS.md:
 * the hypervisor calls these DIRECTLY, so their bodies are reconstructed
 * faithfully from kernelcache.arm64.kc (image base fffffe0007004000).
 *
 * The FUN_ names are the Ghidra ground truth; the English names are estimates.
 * Real identities (confirmed by the wired-page/transparent-submap strings and
 * call-graph shape):
 *   kernel_copyin          @ 0xfffffe000b8afb18 — vm_map_wire
 *   kernel_copyin2         @ 0xfffffe000b8b122c — vm_map_unwire
 *   kernel_copyout         @ 0xfffffe000b8b49e8 — vm_map_protect
 *   kernel_mem_release     @ 0xfffffe000b8a8078 — vm_map_remove/vm_deallocate
 *   kernel_mem_validate    @ 0xfffffe000b8b51c8 — vm_map_enter (11 args)
 *   kernel_alloc           @ 0xfffffe000b8a6c14 — vm_allocate (returns {lo,hi})
 *   kernel_vm_object_batch_dealloc @ 0xfffffe000b8b6860 — vm_object_batch_dealloc
 *   hv_zone_alloc          @ 0xfffffe000b7eb624 — zalloc wrapper
 *   kernel_kalloc          @ 0xfffffe000b859c38 — zalloc (zone allocator)
 *
 * Callees 2+ levels into XNU stay externs (FUN_/DAT_ kept in comments).
 * Ghidra pseudo-artifacts (CONCAT44/SUB84, SoftwareBreakpoint, variadic
 * vtable calls) are reproduced with local helpers so the bodies compile.
 */

/* ------------------------------------------------------------------ *
 * Ghidra decompiler pseudo-artifacts used by the bodies below.
 * ------------------------------------------------------------------ */
#define CONCAT44(hi, lo)  ((uint64_t)(uint32_t)(hi) << 32 | (uint64_t)(uint32_t)(lo))
#define SUB84(a, off)     ((uint32_t)((uint64_t)(a) >> (8 * (off))))

/* Variadic vtable slot used by the fault-table handler dispatch:
 *   (**(code **)(table + 0x20))(4, start, len, mask, map) etc. */
typedef uint64_t (*hv_vtable_call_t)();

/* ------------------------------------------------------------------ *
 * Extern callees (2+ levels into XNU; FUN_ address kept in comments).
 * ------------------------------------------------------------------ */
extern void *SoftwareBreakpoint(uint32_t imm, uint64_t addr);               /* XNU brk assert */
extern void *current_task(void *);                                          /* FUN_fffffe000b8663e8 */
extern uint64_t per_cpu_get(void *);                                     /* FUN_fffffe000b866ec4 */
extern void  kernel_panic_msg_fmt(const char *fmt, ...) __attribute__((noreturn)); /* FUN_fffffe000c0e11ec */
extern void  hv_mem_panic_86a4(void *x, ...) __attribute__((noreturn));     /* FUN_fffffe000c0f86a4 */
extern void  kernel_panic_remove(const char *fmt, ...) __attribute__((noreturn)); /* FUN_fffffe000c0ed8e0 */

extern uint64_t kernel_map_lock(void *map, ...);                             /* FUN_fffffe000b7f5398 */
extern uint64_t kernel_map_ref(uint64_t map);                               /* FUN_fffffe000b7f62e8 */
extern uint64_t kernel_map_unref(uint64_t map, ...);                        /* FUN_fffffe000b7f6aac */
extern uint64_t kernel_map_lock2(void *map);                                /* FUN_fffffe000b7f6b94 */
extern uint64_t kernel_obj_lock(void *obj);                                 /* FUN_fffffe000b7f7050 */
extern uint64_t kernel_map_lookup(uint64_t *fault, void *map, uint64_t a,
                                  uint64_t b, uint64_t flags);              /* FUN_fffffe000b918644 */
extern void     kernel_vm_unwire(uint64_t *fault);                          /* FUN_fffffe000b91ab24 */
extern void     kernel_vm_sync(uint64_t a, uint64_t b);                     /* FUN_fffffe000b91600c */
extern uint64_t kernel_map_lookup_entry(void *map, ...);                    /* FUN_fffffe000b8adda8 */
extern void *   kernel_pmap_lookup(uint64_t a, uint64_t b);                 /* FUN_fffffe000b8cb920 */
extern void     kernel_vm_page_wire(void *obj);                             /* FUN_fffffe000b8ce7d4 */
extern void     kernel_vm_obj_ref(void *obj);                               /* FUN_fffffe000b8cf3f8 */
extern void     kernel_vm_page_unwire(uint64_t pg);                         /* FUN_fffffe000b8cc2f4 */
extern void     kernel_vm_page_enter(void *a, uint64_t b, uint64_t c,
                                     uint64_t d, uint64_t e, uint64_t f, ...); /* FUN_fffffe000b8d1fe4 */
extern uint64_t kernel_vm_obj_attr(uint64_t *a, uint64_t *b, uint64_t c,
                                   uint64_t d);                             /* FUN_fffffe000b8d45b0 */
extern uint64_t kernel_pmap_findpage(uint64_t *obj, uint64_t off);          /* FUN_fffffe000b8f4e94 */
extern uint64_t kernel_map_entry_wired(void *map, void *entry, uint64_t w); /* FUN_fffffe000b8b1114 */
extern uint64_t kernel_map_entry_uncow(uint64_t map, uint64_t entry,
                                       uint64_t a, uint64_t b);             /* FUN_fffffe000b8a3be8 */
extern uint64_t kernel_map_entry_uncow6(uint64_t map, void *entry, uint64_t a,
                                        uint64_t b, uint64_t c, uint64_t d); /* FUN_fffffe000b8a3de4 */
extern uint64_t kernel_map_copy_enter(void *map, ...);                     /* FUN_fffffe000b8a34b8 */
extern void     kernel_map_entry_free(void *entry);                         /* FUN_fffffe000b9166e0 */
extern uint64_t kernel_map_vm_fault_ent(uint64_t *fault, void *entry, void *a); /* FUN_fffffe000b917494 */
extern hv_u128_t kernel_map_wire_lookup(uint64_t map, void *entry);         /* FUN_fffffe000c0ed834 */
extern void     kernel_map_wire_zap(uint64_t a, uint64_t b, uint64_t c,
                                    uint64_t d, uint64_t e);                /* FUN_fffffe000c0ed8e0 */
extern void     kernel_vm_free(void *zone, void *obj);                      /* FUN_fffffe000b862b6c */
extern void     kernel_vm_wire_callback(uint64_t a, uint64_t b, uint64_t c,
                                        uint64_t d);                        /* FUN_fffffe000b812524 */
extern void     kernel_vm_wire_callback2(uint64_t a, uint64_t b, uint64_t c); /* FUN_fffffe000b812f5c */
extern uint64_t kernel_vm_prot_remove(uint64_t a, uint64_t b, uint64_t c,
                                      uint64_t d, ...);                 /* FUN_fffffe000b915588 */
extern uint64_t kernel_vm_report_fault(uint64_t a, uint64_t b, uint64_t c,
                                       uint64_t d, uint64_t e, uint64_t f,
                                       uint64_t g, uint64_t h, uint64_t i,
                                       uint64_t j);                         /* FUN_fffffe000b8847f0 */
extern void     kernel_vm_cs_check(uint64_t a, uint64_t b, uint64_t c);     /* FUN_fffffe000b86659c */
extern uint64_t kernel_vm_unmap_remove(uint64_t map, uint64_t a, uint64_t b,
                                       uint64_t c, uint64_t d);              /* FUN_fffffe000b8b355c */
extern void     kernel_vm_cleanup(uint64_t a, uint64_t b, ...);         /* FUN_fffffe000bf57704 */
extern void     kernel_vm_prot_tlb(uint64_t a, void *entry, uint64_t c,
                                   uint64_t d, uint64_t e, uint64_t f,
                                   uint64_t g);                             /* FUN_fffffe000b94bd20 */
extern void     kernel_vm_prot_dirty(uint64_t a, void *entry, uint64_t c);  /* FUN_fffffe000b8b5b6c */
extern uint64_t kernel_map_page_cow(uint64_t a, uint64_t b, uint64_t c);    /* FUN_fffffe000b8b166c */
extern uint64_t kernel_map_check(void *a, uint64_t b, uint64_t c, uint64_t d,
                                 uint64_t e, uint64_t f);                   /* FUN_fffffe000b9152dc */
extern uint64_t kernel_map_enter_int(void *map, uint64_t a, uint64_t b,
                                     uint64_t c, uint64_t *o1, uint64_t *o2,
                                     uint64_t *o3, uint64_t n, uint64_t m); /* FUN_fffffe000b8abdc4 */
extern uint64_t kernel_map_enter_sub(void *map, uint64_t a, uint64_t b,
                                     uint64_t c, uint64_t d, long *o1,
                                     uint64_t *o2, uint8_t *o3, uint64_t *o4); /* FUN_fffffe000b8b2b60 */
extern void     kernel_map_enter_done(void *map);                           /* FUN_fffffe000b8acc64 */
extern uint64_t kernel_map_enter_loop(void *map, uint64_t a, uint64_t b,
                                      uint64_t c, uint64_t d, uint64_t *o); /* FUN_fffffe000b8adeb4 */
extern uint64_t kernel_map_enter_loop2(void *map, uint64_t a, uint64_t b,
                                       uint64_t c, uint64_t d, uint64_t *o,
                                       uint64_t **o2);                      /* FUN_fffffe000b8af720 */
extern void     kernel_map_entry_commit(void *map, void *entry);            /* FUN_fffffe000b8c6d70 */
extern uint64_t kernel_map_entry_commit2(void *map, void *entry, uint64_t a,
                                         uint64_t b, uint64_t c);           /* FUN_fffffe000b8c6db8 */
extern uint64_t kernel_map_entry_link(uint64_t a, uint64_t b);              /* FUN_fffffe000b915978 */
extern void     kernel_vm_jit_downgrade(void *a, void *b, uint64_t c,
                                        const char *fmt, ...);              /* FUN_fffffe000bf48bc8 */
extern void     kernel_vm_obj_batch(void *obj);                             /* FUN_fffffe000b8a9e4c */
extern uint64_t kernel_vm_obj_batch_head(void);                             /* FUN_fffffe000b8aa1f4 */
extern uint64_t *kernel_copyin2(uint64_t map, uint64_t start, uint64_t end,
                                uint64_t flags, void *fault_table);         /* FUN_fffffe000b8b122c */

extern void *   kernel_page_alloc(uint64_t wired);                          /* FUN_fffffe000b8f58a4 */

/* kernel_alloc (b8a6c14) callees */
extern uint64_t *kernel_phys_alloc(uint64_t pages, uint64_t flags,
                                   uint64_t **out);                          /* FUN_fffffe000b8faabc */
extern uint64_t kernel_map_enter_pre(uint64_t map, uint64_t flags,
                                     uint64_t prot, uint64_t *tag);          /* FUN_fffffe000b8a730c */
extern uint64_t kernel_map_enter_insert(uint64_t map, uint64_t size,
                                        uint64_t param3, uint64_t tag,
                                        uint64_t *block_out);                /* FUN_fffffe000b8a748c */
extern void kernel_queue_free_walk();  /* FUN_fffffe000b8f6e54 (was misnamed kernel_page_unlink/kernel_vm_free_pages here; manifest-verified name = kernel_queue_free_walk; decompile walks *param_1 list, frees each elem; dropped-arg prototype per hv_kernel_shims.h) */
extern uint64_t kernel_va_tag(uint64_t a, uint64_t b, uint64_t c);           /* FUN_fffffe000b990e5c */
extern uint64_t kernel_random_va(uint64_t *buf, uint64_t n, void **out,
                                 uint64_t flags);                            /* FUN_fffffe000b7a5cc0 */
extern uint64_t kernel_alloc_fail_a(uint64_t map, uint64_t size,
                                    uint64_t flags);                         /* FUN_fffffe000c0ecf34 */
extern hv_u128_t kernel_alloc_fail_b(uint64_t map, uint64_t size);           /* FUN_fffffe000c0ecf68 */
extern long     kernel_phys_enter(uint32_t *obj, uint64_t a, uint64_t b,
                                  uint64_t c, uint64_t *blocks, uint64_t flags,
                                  uint32_t prot, int n, ...);          /* FUN_fffffe000b8a756c */
extern long     kernel_map_sync(uint64_t map, uint64_t *block_out);          /* FUN_fffffe000b917524 */
extern uint64_t DAT_fffffe000c648e40;    /* alloc ceiling */
extern uint32_t DAT_fffffe000c712428;    /* special-400 object refcount */
extern uint32_t hv_fault_special_400;    /* DAT_fffffe000c712400 */
extern uint32_t hv_fault_special_300;    /* DAT_fffffe000c712300 */
extern uint32_t hv_fault_special_800;    /* DAT_fffffe000c712800 */
extern uint64_t DAT_fffffe000c5f0000;    /* stack marker */
extern uint64_t hv_fault_boot_threshold; /* DAT_fffffe0007e9d348 */
extern void kernel_stack_check_panic(void) __attribute__((noreturn));  /* FUN_fffffe000c0e0620 */
extern void kernel_panic_a(void) __attribute__((noreturn));            /* FUN_fffffe000c0f86a4 */
extern void kernel_boot_misc_o(const char *fmt, ...);                  /* FUN_fffffe000b801ce4, kernel printf */
extern uint64_t DAT_fffffe0007e2527c;                                 /* code-signing flag */
extern uint64_t DAT_fffffe0007d81228;                                 /* map-check table */
extern uint8_t *DAT_fffffe0007e31d90;                                 /* cs-deny flag */
extern uint64_t DAT_fffffe000c68acf8;                                 /* jit downgrade table */
extern uint64_t DAT_fffffe000c68af18;                                 /* lock-args table */
extern uint64_t DAT_fffffe0007d7fac0;                                 /* lock-args table */
extern uint64_t DAT_fffffe0007d792d0;                                 /* lock-args table 2 */
extern uint64_t DAT_fffffe0007d792f0;                                 /* lock-args table 3 */
extern uint8_t  DAT_fffffe000c608b80;                                 /* zone array base */
extern void     kernel_lock_flush_ack(uint64_t a, uint64_t b, uint64_t c); /* FUN_fffffe000b812f5c */

/* kernel_kalloc (b859c38) zalloc callees (2+ levels into XNU, stubbed).
 * kernel_zone_lock/unlock (b7f74d4/b7f7538) are declared below with the
 * agent's void* forms. */
extern void     kernel_zone_lock_acquire(void *lock, void *cur);      /* FUN_fffffe000b7f9420 */
extern char *   kernel_zone_wait(void *lock, uint64_t a, uint64_t b,
                                 uint64_t c, void **d, void **e);     /* FUN_fffffe000b7f973c */
extern void     kernel_zone_wake(void *lock, uint64_t a, uint64_t b,
                                 uint64_t c, uint64_t d);             /* FUN_fffffe000b7fa7b8 */
extern void     kernel_zone_fill(long zone, uint64_t x);              /* FUN_fffffe000b859e28 */
extern char *   kernel_zone_gc(char *zone);                           /* FUN_fffffe000b85b3a8 */
extern char *   kernel_zone_gc2(char *zone);                          /* FUN_fffffe000b85b5e4 */
extern void     kernel_zone_pages(uint64_t base, uint64_t size);      /* FUN_fffffe000b85b844 */
extern void     kernel_zone_count(char *zone, uint64_t a, uint64_t b,
                                  uint64_t c, uint64_t d, uint64_t e);/* FUN_fffffe000b85b9d0 */
extern void     kernel_zone_trace(char *zone, uint64_t count);        /* FUN_fffffe000b85bbb0 */
extern char *   kernel_zone_finalize(char *zone, uint64_t a, uint64_t b,
                                     uint64_t c, uint64_t d, uint64_t e); /* FUN_fffffe000b85be14 */
extern char *   kernel_zone_callback(uint64_t *zone, uint64_t x);     /* FUN_fffffe000b8462e0 */
extern long     kernel_zone_wrap(char *zone, const char *msg);        /* FUN_fffffe000c0ea758 */
extern long *   kernel_page_alloc2(uint64_t flags);                   /* FUN_fffffe000b8f5be0 */
extern void     kernel_page_wait(uint64_t x);                         /* FUN_fffffe000b8f671c */
extern void     kernel_zone_page_zero(uint64_t base, uint64_t size);  /* FUN_fffffe000b961544 */
extern void     kernel_page_trace(uint64_t cpu, uint64_t zone, void *elem); /* FUN_fffffe000b7eda24 */
extern void     kernel_zone_array_panic(void *x) __attribute__((noreturn));  /* FUN_fffffe000c0ea524 */
extern void     kernel_zone_array_panic2(void *zone, ...);            /* FUN_fffffe000c0ea554 */
extern void     kernel_zone_array_panic3(void *zone, uint64_t x);     /* FUN_fffffe000c0ea59c */
extern void     kernel_zone_array_panic4(void *zone, void *x, const char *msg); /* FUN_fffffe000c0ea708 */
extern uint64_t kernel_zone_debug1(void **out);                       /* FUN_fffffe000b85b710 */
extern void     kernel_zone_debug2(void *x);                       /* FUN_fffffe000b85b334 */
extern void     kernel_zone_debug3(void *x);                          /* FUN_fffffe000b85b7a0 */
extern void     kernel_zone_debug4(void *x);                          /* FUN_fffffe000b85b7e4 */
extern void     kernel_zone_debug5(uint64_t x);                       /* FUN_fffffe000b85b824 */
extern uint64_t DAT_fffffe000c70bd60;   /* zone page-pool lock */
extern uint64_t DAT_fffffe000c70bd68;   /* zone page-pool owner (CONCAT44) */
extern uint64_t DAT_fffffe000c70bd68_4; /* zone page-pool owner hi */
extern uint64_t DAT_fffffe000c70be00[64]; /* zone page-pool low */
extern uint64_t DAT_fffffe000c70be08[64]; /* zone page-pool high */
extern uint64_t DAT_fffffe0007d7ca18;   /* compressor zone */
extern uint64_t DAT_fffffe000c5abffc[]; /* free-list bucket table */
extern uint64_t DAT_fffffe0007d800b0[]; /* zone type table */
extern uint64_t DAT_fffffe000c5fdab0;   /* element-count stat */
extern uint64_t DAT_fffffe000c5fdaa8;   /* zone-count stat */
extern uint64_t DAT_fffffe000c5b23f8;   /* zone debug flag (signed char) */
extern uint64_t DAT_fffffe000c5b23f0;   /* zone trace flag */
extern uint64_t DAT_fffffe000c649450;   /* zone free low */
extern uint64_t DAT_fffffe000c67f9b0;   /* zone free high */
extern uint64_t DAT_fffffe000c70c130;   /* zone callback table */
extern uint64_t DAT_fffffe000c60524c;   /* wired-zone stat */
extern uint64_t DAT_fffffe000c605258;   /* wired-zone sentinel */
extern uint64_t DAT_fffffe000c5f405c;   /* wired-zone stat 2 */
extern uint64_t DAT_fffffe000c5b04f0;   /* wire callback msg */
extern uint64_t PTR_DAT_fffffe000c5c89f8;/* per-CPU wired page counter */
extern uint64_t DAT_fffffe0007e0c9a8;   /* zone trace table */
extern uint64_t PTR_DAT_fffffe0007d7c9f0[8]; /* zone error strings */
extern uint64_t hv_fault_boot_threshold;/* DAT_fffffe0007e9d348 */
extern void *   kernel_vm_alloc_pages(uint64_t n, uint64_t flags, void **o);/* FUN_fffffe000b8faabc */
extern void     kernel_vm_obj_install(long pg, uint64_t *obj, uint64_t off,
                                      uint64_t a, uint64_t b, uint64_t c);  /* FUN_fffffe000b8f19b0 */
extern void     kernel_vm_map_pages(uint64_t *obj, uint64_t a, uint64_t b,
                                    uint64_t c, void *d, uint64_t e,
                                    uint64_t f, uint64_t g);                /* FUN_fffffe000b8a756c */
extern uint64_t kernel_vm_map_start(void *map, uint64_t a, uint64_t b,
                                    uint64_t c, uint64_t *o);               /* FUN_fffffe000b8a748c */
extern uint64_t kernel_vm_alloc_prep(void *map, uint64_t flags, uint64_t a,
                                     uint64_t *o);                          /* FUN_fffffe000b8a730c */
extern void     kernel_vm_markclean(void *map, void *obj);                  /* FUN_fffffe000b917524 */
extern uint64_t kernel_vm_alloc_phys(uint64_t a, uint64_t b, uint64_t c);   /* FUN_fffffe000b990e5c */
extern uint64_t kernel_ktrace(void *buf, uint64_t a, uint64_t b, uint64_t c); /* FUN_fffffe000b7a5cc0 */
extern void     kernel_alloc_panic(void *a, uint64_t b, uint64_t c) __attribute__((noreturn)); /* FUN_fffffe000c0ecf34 */
extern hv_u128_t kernel_alloc_panic2(void *a, uint64_t b);                  /* FUN_fffffe000c0ecf68 */

extern void     kernel_zone_alloc_core(uint64_t a, void *zone, uint64_t flags); /* FUN_fffffe000b85e180 */
extern void     kernel_zone_lock(void *zone);                               /* FUN_fffffe000b7f74d4 */
extern void     kernel_zone_unlock(void *zone);                             /* FUN_fffffe000b7f7538 */
extern void     kernel_zone_grow(void *zone, uint64_t n);                   /* FUN_fffffe000b859e28 */
extern uint64_t kernel_zone_get_page(void);                                 /* FUN_fffffe000b93c6c8 */
extern void     kernel_zone_page_zero(uint64_t pg, uint64_t n);             /* FUN_fffffe000b85b844 */
extern void     kernel_zone_pgtab(void *zone, uint64_t a, uint64_t b,
                                  uint64_t c, uint64_t d, uint64_t e);      /* FUN_fffffe000b85b9d0 */
extern void     kernel_zone_pgtab2(void *zone, uint64_t a, uint64_t b);     /* FUN_fffffe000b85bbb0 */
extern void     kernel_zone_deposit(void *zone, void *pg, uint64_t n, void **freelist); /* FUN_fffffe000b8f5be0 */
extern void     kernel_zone_verify(void *zone, void *pg, uint64_t n);       /* FUN_fffffe000b8f671c */
extern void     kernel_zone_cpu_free(void *cpu, void *tab, void *pg);       /* FUN_fffffe000b7eda24 */
extern void     kernel_zone_record(void *pg, uint64_t n);                   /* FUN_fffffe000b961544 */
extern void     kernel_zone_expand(void *zone, uint64_t a, uint64_t b, uint64_t c, uint64_t d); /* FUN_fffffe000b85b3a8 */
extern void     kernel_zone_expand2(void *zone, uint64_t a, uint64_t b, uint64_t c, uint64_t d); /* FUN_fffffe000b85b5e4 */
extern void     kernel_zone_finish(void *zone, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e); /* FUN_fffffe000b85be14 */
extern void     kernel_zone_wakeup(void *zone, uint64_t a, uint64_t b, uint64_t c, uint64_t d); /* FUN_fffffe000b85b710 */
extern void     kernel_zone_stat(void *zone);                               /* FUN_fffffe000b85b334 */
extern void     kernel_zone_stat2(void *zone);                              /* FUN_fffffe000b85b7a0 */
extern void     kernel_zone_stat3(void *zone);                              /* FUN_fffffe000b85b7e4 */
extern void     kernel_zone_stat4(void *zone);                              /* FUN_fffffe000b85b824 */
extern uint64_t kernel_zone_panic2(void *zone, const char *msg);            /* FUN_fffffe000c0ea554 */
extern void     kernel_zone_panic3(void *zone, ...) __attribute__((noreturn)); /* FUN_fffffe000c0ea524 */
extern void     kernel_zone_panic4(void *zone, ...) __attribute__((noreturn)); /* FUN_fffffe000c0ea708 */
extern void     kernel_zone_panic5(void *zone, void *pg) __attribute__((noreturn)); /* FUN_fffffe000c0ea59c */
extern void     kernel_zone_panic6(void *zone, void *pg) __attribute__((noreturn)); /* FUN_fffffe000c0ea758 */
extern void     kernel_zone_lock_wait(void *zone, void *cpu);               /* FUN_fffffe000b7f9420 */
extern void     kernel_zone_lock2(void *zone, void *a, uint64_t b, uint64_t c, void **o1, void **o2); /* FUN_fffffe000b7f973c */
extern void     kernel_zone_lock3(void *zone);                              /* FUN_fffffe000b7f9914 */
extern void     kernel_zone_lock4(void *zone);                              /* FUN_fffffe000b7f9920 */
extern void     kernel_zone_cpu_add(void *zone, uint64_t n);                /* FUN_fffffe000b8462e0 */
extern void     kernel_zone_lock_acq(void *lock, ...);                      /* FUN_fffffe000b7f0afc */
extern void     kernel_zone_lock_rel(void *lock, void *cpu);                /* FUN_fffffe000b7f1e80 */

/* ------------------------------------------------------------------ *
 * Kernel globals (DAT_/PTR_DAT_/MACH_HEADER kept in comments).
 * ------------------------------------------------------------------ */
extern uint64_t hv_kernel_map_base;       /* DAT_fffffe000c62b6a8 */
extern uint64_t hv_kernel_map_sentinel;   /* DAT_fffffe000c62b698 */
extern void *   hv_map_error_string;      /* DAT_fffffe000c68af18 */
extern void *   hv_vm_wire_string;        /* DAT_fffffe0007d7fb10 */
extern void *   hv_vm_wire_string2;       /* DAT_fffffe0007d7fb30 */
extern void *   hv_vm_fault_str;          /* DAT_fffffe0007d81228 */
extern void *   hv_vm_prot_string;        /* DAT_fffffe0007d7fac0 */
extern void *   hv_zone_alloc_zone;       /* DAT_fffffe0007d530f8 */
extern void *   hv_zone_entry_zone;       /* DAT_fffffe0007d53138 */
extern void *   hv_zone_entry_zone2;      /* DAT_fffffe0007d53178 */
extern void *   hv_zone_entry_zone3;      /* DAT_fffffe0007d531b8 */
extern void *   hv_zone_entry_zone4;      /* DAT_fffffe0007d531f8 */
extern uint64_t hv_map_wire_cow;          /* DAT_fffffe000c712400 */
extern uint64_t hv_map_wire_copy;         /* DAT_fffffe000c712300 */
extern uint64_t hv_map_wire_ro;           /* DAT_fffffe000c712800 */
extern uint8_t  hv_vm_unwire_fault_table[]; /* DAT_fffffe0007d81408 */
extern uint64_t hv_kernel_total_bytes;    /* DAT_fffffe000c6497b8 */
extern uint64_t hv_kernel_max_bytes;      /* DAT_fffffe000c649470 */
extern uint64_t hv_kernel_min_bytes;      /* DAT_fffffe000c649468 */
extern uint64_t hv_kernel_free_bytes;     /* DAT_fffffe000c67f9c0 */
extern uint64_t hv_kernel_wired_bytes;    /* DAT_fffffe000c6497b0 */
extern uint64_t hv_stat_wire_count[];     /* DAT_fffffe000c5f4054 (32) */
extern uint64_t hv_stat_wire_msg[];       /* DAT_fffffe000c5b04e8 (8) */
extern void *   hv_wire_callback_fn;      /* FUN_fffffe000b7f23d0 (address taken) */
extern void *   hv_wire_callback_fn2;     /* FUN_fffffe000b8b10fc (address taken) */
extern uint32_t hv_cs_jit_flag;           /* DAT_fffffe0007e2527c */
extern uint64_t hv_vm_prot_special;       /* DAT_fffffe000c68acf8 */
extern uint8_t *hv_vm_remap_flag;         /* DAT_fffffe0007e31d90 */
extern uint64_t hv_vm_owner_lock;         /* DAT_fffffe000c62b3d0 */
extern uint64_t hv_vm_wire_special;       /* DAT_fffffe000c5f405c */
extern uint64_t hv_vm_alloc_hi_limit;     /* DAT_fffffe000c648e40 */
extern uint64_t hv_vm_alloc_hi_bound;     /* DAT_fffffe0007e9d348 */
extern uint64_t hv_vm_alloc_magic;        /* DAT_fffffe000c5f0000 */
extern uint32_t hv_vm_obj_refcount;       /* DAT_fffffe000c712428 */
extern void *   MACH_HEADER;              /* kernel mach header (est.) */
extern uint64_t hv_zone_alloc_free;       /* DAT_fffffe000c5fdab0 */
extern int8_t   hv_zone_alloc_debug;      /* DAT_fffffe000c5b23f8 */
extern uint64_t hv_zone_alloc_stat;       /* DAT_fffffe000c5fdaa8 */
extern uint64_t hv_zone_alloc_stat2;      /* DAT_fffffe000c5b23f0 */
extern uint64_t hv_zone_alloc_min;        /* DAT_fffffe000c67f9b0 */
extern uint64_t hv_zone_alloc_min2;       /* DAT_fffffe000c649450 */
extern uint64_t hv_zone_alloc_cpu_ptr;    /* DAT_fffffe000c5c89f8 (PTR) */
extern void *   hv_zone_alloc_zone_tab;   /* DAT_fffffe0007e0c9a8 */
extern void *   hv_zone_alloc_zone_lk;    /* DAT_fffffe000c70c130 */
extern uint64_t hv_zone_alloc_pcpu0;      /* DAT_fffffe000c70bd60 */
extern uint64_t hv_zone_alloc_pcpu_lk;    /* DAT_fffffe000c70bd68 */
extern uint64_t hv_zone_alloc_pcpu_pgs[]; /* DAT_fffffe000c70be00 */
extern uint64_t hv_zone_alloc_pcpu_pgs2[];/* DAT_fffffe000c70be08 */
extern void *   hv_zone_alloc_fp;         /* DAT_fffffe000c605258 */
extern uint64_t hv_zone_alloc_fpcnt;      /* DAT_fffffe000c60524c */
extern uint64_t hv_zone_alloc_fpstat;     /* DAT_fffffe000c5f405c */
extern uint64_t hv_zone_alloc_fpmsg;      /* DAT_fffffe000c5b04f0 */
extern uint64_t hv_zone_alloc_array[];    /* DAT_fffffe000c5abffc */
extern uint64_t hv_zone_alloc_mode;       /* DAT_fffffe0007d800b0 */

/* ================================================================== *
 * kernel_copyin @ 0xfffffe000b8afb18   (est. vm_map_wire)
 * Ghidra: ulong (long param_1, ulong param_2, long param_3, uint param_4,
 *                undefined4 param_5, undefined8 param_6, undefined4 *param_7,
 *                long param_8)
 *
 * Wires (locks into physical memory) the map range [start, end) of the vm_map
 * at param_1. Walks the map entries, faulting in + wiring pages (via the
 * vm_fault entry helpers), and records the wired page into *param_7 when
 * requested. Returns 0 on success or a KERN_* error code; param_8 is the
 * fault/wire state table (its +0x20 slot is a vtable handler). The trailing
 * unwire pass (kernel_copyin2) is only used to undo entries on failure.
 *
 * Confidence: medium (faithful to decompile; entry-structure offsets are
 *   XNU vm_map_entry / vm_object layout estimates).
 * Notes: strings "Tried to lookup a wired page, but the page wasn't wired
 *   page=%p start=%llx end=%llx entry=%p" and "transparent submap
 *   configuration unexpectedly changed during vm_map_wire" confirm this is
 *   vm_map_wire. Wire-state machine (state_flags/state_ctrl + paging_state locals)
 *   mirrors the vm_fault family reconstructed in hv_el2.c. SoftwareBreakpoint
 *   (0xbffd) = XNU brk assert.
 * Kernel code recreated for audit (hv-deps). */
uint64_t
kernel_copyin(void *map, uint64_t start, uint64_t end, uint32_t wire_flags,
              uint32_t param5, uint64_t param6, uint32_t *wired_page_out,
              void *fault_table)
{
    uint8_t  page_state;
    uint64_t entry_end;
    uint32_t entry_word2;
    uint32_t page_num;
    int16_t  entry_refc2;
    uint16_t entry_refc;
    uint8_t  unwired_flag;
    uint64_t entry_lo;
    void *   brk_code;
    int      refc;
    void *   wire_obj;
    uint64_t **ent_node;
    uint64_t **ent_node2;
    uint64_t map_obj;
    uint8_t  ent_state;
    uint32_t lookup_flags;
    uint32_t prot_ro;
    uint32_t entry_flags;
    uint32_t ent_flags;
    uint32_t wire_prot;
    uint64_t va_end;
    uint64_t entry_meta;
    uint64_t vmap;
    uint64_t *entry;
    long     entry_pmap;
    uint32_t wire_kind;
    int      wire_mode;
    long     page_obj;
    uint64_t *obj;
    uint64_t status;
    long     cur;
    uint64_t rc;
    uint64_t *obj2;
    uint64_t *obj2_4;
    uint64_t *obj2_5;
    uint64_t *obj2_2;
    uint64_t *obj2_0;
    uint64_t *obj2_1;
    uint8_t  wire_key[16];
    uint8_t  *fault_name2;
    uint64_t fault_word;
    void *   fault_fn;
    uint8_t  *fault_name3;
    uint32_t fault_flags;
    uint8_t  *fault_name;
    uint64_t fault_word2;
    uint64_t fault_fn2;
    uint8_t  *fault_name4;
    uint32_t fault_flags2;
    uint64_t state;
    uint64_t state_end;
    uint64_t state_lo;
    uint64_t *state_block;
    void **  fault_rec;
    uint32_t state_flags;
    uint32_t state_ctrl;
    uint64_t state_hi;
    uint32_t state_d8;
    uint32_t state_d4;
    uint32_t state_d0;
    uint32_t state_cc;
    uint32_t state_c8;
    uint32_t state_c4;
    uint32_t state_c0;
    uint32_t state_bc;
    uint32_t state_b8;
    uint32_t state_b4;
    uint64_t state_b0;
    uint32_t state_a8;
    uint32_t state_a4;
    uint64_t *ent_head;
    uint64_t **ent_tail;
    uint64_t paddr;
    uint64_t *obj_slot[2];

    ent_tail = &ent_head;
    ent_head = (uint64_t *)0;
    state_b8 = 0;
    state_b4 = 0;
    state_c0 = 0;
    state_bc = 0;
    state_a8 = 0;
    state_a4 = 0;
    state_b0 = 0;
    state_b0 = 0;
    state_d8 = 0;
    state_d4 = 0;
    state_hi = 0;
    state_hi = 0;
    state_c8 = 0;
    state_c4 = 0;
    state_d0 = 0;
    state_cc = 0;
    state_block = (uint64_t *)0;
    state_lo = 0;
    state_flags = 0;
    state_ctrl = 0;
    fault_rec = (void **)0;
    state_end = 0;
    state = 0;
    entry = *(uint64_t **)((uint8_t *)map + 0x58);
    vmap = start;
    if (entry != (uint64_t *)0) {
        if (entry == &hv_kernel_map_sentinel) {
            vmap = hv_kernel_map_base & (long)(start << 8) >> 0x3f | start;
        }
        else if ((start >> 0x37 & 1) == 0) {
            vmap = entry[3] - 1 & start;
        }
    }
    status = 0x20000001;
    start = end - start;
    if (start != 0) {
        rc = (uint64_t)(uint32_t)~(-1 << (uint64_t)(*(uint16_t *)((uint8_t *)map + 0x44) & 0x1f));
        if (!CARRY8(vmap, start)) {
            status = vmap & (rc ^ 0xffffffffffffffff);
            va_end = start + vmap + rc & ~rc;
            if (status < va_end) goto l_start;
        }
        if (*(void **)((uint8_t *)fault_table + 0x20) != (void *)0) {
            status = ((hv_vtable_call_t)(*(void **)((uint8_t *)fault_table + 0x20)))(4, vmap, start, rc, (uint64_t)map);
            if ((status >> 0x28 & 1) != 0) {
                kernel_vm_report_fault(*(uint64_t *)((uint8_t *)fault_table + 0x10), 1, 1,
                                       *(uint32_t *)((uint8_t *)fault_table + 0x18),
                                       vmap, start, rc, 0, 4, (long)(int)status);
            }
            if ((status >> 0x20 & 1) != 0) {
                if ((int)status == 0) {
                    status = 0;
                    va_end = 0;
l_start:
                    if (wire_flags < 8) {
                        wire_kind = 0;
                        wire_mode = (int)param6;
                        lookup_flags = 0x8069;
                        if (wire_mode == 0) {
                            lookup_flags = 0x69;
                        }
                        ent_flags = 2;
                        if (wire_mode == 0) {
                            ent_flags = 0;
                        }
                        if (wired_page_out == (uint32_t *)0) goto l_no_wire_out;
l_wire_out:
                        *wired_page_out = 0;
                        fault_rec = &fault_name;
                        fault_name = &hv_vm_wire_string;
                        fault_word2 = 0x40000000;
                        fault_fn2 = (uint64_t)0xfffffe000b8b105c;
                        fault_name4 = &hv_vm_wire_string2;
                        fault_flags2 = wire_flags;
l_wire_loop:
                        vmap = *(uint64_t *)((uint8_t *)map + 0x28);
                        rc = *(uint64_t *)((uint8_t *)map + 0x30);
                        status = (vmap <= status) * status + (vmap > status) * vmap;
                        va_end = (va_end <= rc) * va_end + (va_end > rc) * rc;
                        if (va_end <= status) {
                            return 0;
                        }
                        kernel_map_lock(map);
                        rc = (uint64_t)kernel_map_lookup(&state, map, status, va_end, lookup_flags);
                        vmap = state_lo;
                        if ((int)rc != 0) {
                            cur = tpidr_el1;
                            *(uint64_t *)(cur + 0x238) = 0;
                            return rc;
                        }
                        cur = 0;
                        for (;;) {
                            if (state_block != (uint64_t *)0) {
                                if (((state_ctrl & 0xc) == 8) && (state_end <= (uint64_t)state_block[3])) {
                                    if ((((uint8_t)state_flags >> 2) & 1) == 0) {
                                        state = CONCAT44(state_c4, state_c8);
                                    }
                                    else {
                                        state_hi = state_b0 + state_hi;
                                        state = state + state_b0;
                                    }
                                    state_block = (uint64_t *)CONCAT44(state_a4, state_a8);
                                    state_end = CONCAT44(state_bc, state_c0);
                                    state_lo = CONCAT44(state_b4, state_b8);
                                    state_ctrl = state_ctrl & 0xfffffff3;
                                    state_b0 = 0;
                                    state_a8 = 0;
                                    state_a4 = 0;
                                }
                                rc = state_block[3];
                                if ((uint64_t)state_block[3] < state_end) goto l_entry_next;
                                state_block = (uint64_t *)0;
l_entry_done:
                                cur = tpidr_el1;
                                *(uint64_t *)(cur + 0x238) = 0;
                                if ((state_ctrl & 0xc) == 8) {
                                    if ((((uint8_t)state_flags >> 2) & 1) == 0) {
                                        state = CONCAT44(state_c4, state_c8);
                                    }
                                    else {
                                        state_hi = state_b0 + state_hi;
                                        state = state + state_b0;
                                    }
                                    state_block = (uint64_t *)CONCAT44(state_a4, state_a8);
                                    state_lo = CONCAT44(state_b4, state_b8);
                                    state_end = CONCAT44(state_bc, state_c0);
                                    state_ctrl = state_ctrl & 0xfffffff3;
                                    state_b0 = 0;
                                    state_a8 = 0;
                                    state_a4 = 0;
                                }
                                if (((state_flags >> 2) & 1) == 0) {
                                    kernel_vm_unwire(&state);
                                }
                                else if ((state_block != (uint64_t *)0) &&
                                        ((~(uint32_t)*(state_block + 5) & 3) != 0)) {
                                    kernel_vm_sync(0, 0);
                                }
                                map = (void *)CONCAT44(state_b4, state_b8);
                                state_lo = 0;
                                state_block = (uint64_t *)0;
                                state_hi = 0;
                                state_d8 = 0;
                                state_ctrl = 0;
                                state_hi = 0;
                                state_cc = 0;
                                state_c8 = 0;
                                state_d4 = 0;
                                state_d0 = 0;
                                state_bc = 0;
                                state_b8 = 0;
                                state_c4 = 0;
                                state_c0 = 0;
                                state_b0 = 0;
                                state_a8 = 0;
                                state_b4 = 0;
                                state_b0 = 0;
                                state_a4 = 0;
                                entry = ent_head;
                                goto l_walk_new;
                            }
                            state_ctrl = state_ctrl & 0xfffffffd;
                            state_block = &state_hi;
                            rc = state;
l_entry_next:
                            entry = (uint64_t *)*state_block;
                            if (((state_flags >> 0x13) & 1) == 0) {
l_entry_walk:
                                state_block = entry;
                                if (entry == (uint64_t *)0) goto l_entry_done;
                                entry_meta = entry[5];
                                if ((((uint32_t)entry_meta >> 1) & 1) == 0) goto l_entry_process;
                            }
                            else {
                                entry_meta = entry[5];
                                if ((entry_meta & 3) == 2) {
                                    entry_lo = CONCAT44(state_bc, state_c0);
                                    entry_end = entry[3];
                                    state_b0 = entry[2] - (entry[6] & 0xfffffffffffff000);
                                    state = rc - state_b0;
                                    state_end = ((entry_lo <= entry_end) * entry_lo + (entry_lo > entry_end) * entry_end) - state_b0;
                                    state_lo = entry_meta & 0xfffffffffffffffc;
                                    state_block = (uint64_t *)0;
                                    state_ctrl = state_ctrl & 0xfffffff3 | 8;
                                    state_a8 = SUB84(entry, 0);
                                    state_a4 = (uint32_t)((uint64_t)entry >> 0x20);
                                    if (((state_flags >> 2) & 1) != 0) {
                                        state_hi = state;
                                    }
                                    entry = (uint64_t *)kernel_map_lookup_entry((void *)0, 0);
                                    goto l_entry_walk;
                                }
                                state_block = entry;
                                if ((((uint32_t)entry_meta >> 1) & 1) != 0) goto l_alloc_node;
l_entry_process:
                                page_obj = entry[3] - entry[2];
                                entry_flags = *(uint32_t *)(entry + 7);
                                state_block = entry;
                                if (((entry_flags >> 0x1e) & 1) == 0) {
                                    if ((entry_meta >> 0x20 == 0) ||
                                        (obj = (uint64_t *)(entry_meta >> 0x1a & 0x3fffffffc0 | 0xfffffe0000000000),
                                         obj == (uint64_t *)0)) {
                                        if ((entry_flags & 0x7800) == 0) {
                                            if (vmap == 0) {
                                                map_obj = 0xffffffffffffffff;
                                            }
                                            else {
                                                map_obj = *(uint64_t *)(vmap + 0xc0);
                                            }
                                            wire_obj = (void *)kernel_pmap_lookup(page_obj, map_obj);
                                            prot_ro = 0x40000000;
                                            if (wire_obj != &hv_map_wire_ro && wire_obj != &hv_map_wire_copy) {
                                                prot_ro = 0;
                                            }
                                            wire_prot = 0;
                                            if (wire_obj != &hv_map_wire_ro && wire_obj != &hv_map_wire_copy) {
                                                wire_prot = (uint32_t)((uint64_t)wire_obj >> 6);
                                            }
                                            entry[5] = entry[5] & 0xfffffffffffffffc;
                                            *(uint32_t *)(entry + 5) = 0;
                                            *(uint32_t *)((long)entry + 0x2c) = wire_prot;
                                            entry_word2 = *(uint32_t *)(entry + 7);
                                            entry_flags = prot_ro | entry_word2 & 0xbdbfffff;
                                            *(uint32_t *)(entry + 7) = entry_flags;
                                            if (wire_obj == &hv_map_wire_ro) {
                                                entry_flags = entry_flags | 2;
l_set_flags:
                                                *(uint32_t *)(entry + 7) = entry_flags;
                                            }
                                            else if (wire_obj == &hv_map_wire_copy) {
                                                entry_flags = prot_ro | entry_word2 & 0xbdbffffd;
                                                goto l_set_flags;
                                            }
                                            entry[6] = entry[6] & 0xfff;
                                            if (((entry_flags >> 0x1e) & 1) != 0) goto l_set_ro;
                                            if (wire_prot != 0) {
                                                obj = (uint64_t *)((uint64_t)wire_prot << 6 | 0xfffffe0000000000);
                                                goto l_wire_page;
                                            }
                                        }
                                        obj = (uint64_t *)0;
                                    }
                                }
                                else {
l_set_ro:
                                    obj = (uint64_t *)&hv_map_wire_copy;
                                    if ((entry_flags & 2) != 0) {
                                        obj = (uint64_t *)&hv_map_wire_ro;
                                    }
                                }
l_wire_page:
                                if (*(int *)(obj + 0xe) == 4) {
                                    rc = entry[6];
                                    if (((*(uint8_t *)((long)obj + 0x7e) >> 4) & 1) == 0) {
                                        kernel_vm_page_wire(obj);
                                        *(uint32_t *)((long)obj + 0x7c) = *(uint32_t *)((long)obj + 0x7c) | 0x100000;
                                        kernel_obj_lock(obj + 1);
                                        entry_flags = *(uint32_t *)(entry + 7);
                                    }
                                    if (((entry_flags >> 0x1e) & 1) == 0) {
                                        if (*(uint32_t *)((long)entry + 0x2c) == 0) {
                                            obj_slot[0] = (uint64_t *)0;
                                        }
                                        else {
                                            obj_slot[0] = (uint64_t *)((uint64_t)*(uint32_t *)((long)entry + 0x2c) << 6 | 0xfffffe0000000000);
                                        }
                                    }
                                    else {
                                        obj_slot[0] = (uint64_t *)&hv_map_wire_copy;
                                        if ((entry_flags & 2) != 0) {
                                            obj_slot[0] = (uint64_t *)&hv_map_wire_ro;
                                        }
                                    }
                                    paddr = entry[6] & 0xfffffffffffff000;
                                    kernel_vm_obj_attr(obj_slot, &paddr, page_obj, *(uint32_t *)(vmap + 0xb0) >> 2 & 1);
                                    entry_flags = *(uint32_t *)(entry + 7);
                                    if (((entry_flags >> 0x1e) & 1) == 0) {
                                        if (*(uint32_t *)((long)entry + 0x2c) != 0) {
                                            obj2 = (uint64_t *)((uint64_t)*(uint32_t *)((long)entry + 0x2c) << 6 | 0xfffffe0000000000);
                                            goto l_check_obj;
                                        }
                                        if (obj_slot[0] != (uint64_t *)0) goto l_set_obj;
                                    }
                                    else {
                                        obj2 = (uint64_t *)&hv_map_wire_copy;
                                        if ((entry_flags & 2) != 0) {
                                            obj2 = (uint64_t *)&hv_map_wire_ro;
                                        }
l_check_obj:
                                        if (obj_slot[0] != obj2) {
l_set_obj:
                                            *(int *)((long)entry + 0x2c) = (int)((uint64_t)obj_slot[0] >> 6);
                                            entry_flags = entry_flags | 0x20000;
                                            *(uint32_t *)(entry + 7) = entry_flags;
                                        }
                                    }
                                    if (paddr != (entry[6] & 0xfffffffffffff000)) {
                                        entry[6] = paddr & 0xfffffffffffff000 | entry[6] & 0xfff;
                                    }
                                    if (((entry_flags >> 0x1e) & 1) == 0) {
                                        if (*(uint32_t *)((long)entry + 0x2c) != 0) {
                                            obj2 = (uint64_t *)((uint64_t)*(uint32_t *)((long)entry + 0x2c) << 6 | 0xfffffe0000000000);
                                            goto l_check_obj2;
                                        }
                                        obj2 = (uint64_t *)0;
                                        if (obj != (uint64_t *)0) goto l_page_enter;
                                    }
                                    else {
                                        obj2 = (uint64_t *)&hv_map_wire_copy;
                                        if ((entry_flags & 2) != 0) {
                                            obj2 = (uint64_t *)&hv_map_wire_ro;
                                        }
l_check_obj2:
                                        if (obj2 != obj) {
l_page_enter:
                                            entry_pmap = *(long *)(vmap + 0x58);
                                            if (entry_pmap == 0) {
                                                entry_pmap = 0;
                                            }
                                            kernel_vm_page_enter(obj, rc & 0xfffffffffffff000, page_obj, entry_pmap,
                                                                 1L << ((uint64_t)*(uint16_t *)(vmap + 0x44) & 0x3f), entry[2],
                                                                 entry_flags >> 7 & 5, 0);
                                        }
                                    }
                                    kernel_vm_page_wire(obj2);
                                    if (*(int *)(obj2 + 0xe) == 4) {
                                        *(uint32_t *)(obj2 + 0xe) = 2;
                                        *(uint32_t *)((long)obj2 + 0x7c) = *(uint32_t *)((long)obj2 + 0x7c) | 0x200000;
                                    }
                                }
                                else {
                                    kernel_vm_page_wire(obj);
                                    obj2 = obj;
                                }
                                obj2[0x16] = obj2[0x16] | 0x2000000;
                                kernel_obj_lock(obj2 + 1);
l_alloc_node:
                                ent_node = (uint64_t **)hv_zone_alloc(&hv_zone_alloc_zone, 0);
                                if (*(int16_t *)((long)entry + 0x3c) == 0) {
                                    ent_state = 2;
                                    if ((wire_mode != 0) && ((((uint32_t)entry[5] >> 1) & 1) == 0)) {
                                        if (*(int16_t *)((long)entry + 0x3e) == 0) {
                                            cur = (entry[3] - entry[2]) + cur;
                                            kernel_map_ref(vmap);
                                            page_obj = hv_kernel_total_bytes;
                                            rc = *(uint64_t *)(vmap + 0x78);
                                            if ((rc <= hv_kernel_max_bytes) * rc +
                                                (rc > hv_kernel_max_bytes) * hv_kernel_max_bytes <
                                                (uint64_t)(*(long *)(vmap + 0x80) + cur)) {
                                                hv_kernel_total_bytes = hv_kernel_total_bytes + 1;
                                                kernel_map_unref(page_obj, vmap);
                                            }
                                            else {
                                                kernel_map_unref(vmap);
                                                if (cur + (uint64_t)hv_kernel_free_bytes * 0x4000 <= hv_kernel_min_bytes)
                                                    goto l_kernel_bytes;
                                                hv_kernel_wired_bytes = hv_kernel_wired_bytes + 1;
                                            }
                                            rc = 6;
                                            wire_obj = &hv_zone_entry_zone2;
                                            goto l_free_node;
                                        }
l_kernel_bytes:
                                        ent_state = 2;
                                    }
                                }
                                else {
                                    rc = (uint64_t)kernel_map_entry_wired((void *)vmap, entry, wire_mode != 0);
                                    if ((int)rc != 0) goto l_free_node2;
                                    ent_state = 0;
                                }
                                *(uint8_t *)(ent_node + 5) = ent_state;
                                ent_node[2] = (uint64_t *)entry[2];
                                ent_node[3] = (uint64_t *)entry[3];
                                ent_node[4] = (uint64_t *)(entry[6] & 0xfffffffffffff000);
                                *(uint8_t *)((long)ent_node + 0x29) = *(uint8_t *)(entry + 5) >> 1 & 1;
                                rc = entry[5];
                                if ((((uint32_t)rc >> 1) & 1) == 0) {
                                    if ((*(uint32_t *)(entry + 7) >> 0x1e & 1) == 0) {
                                        if (rc >> 0x20 == 0) {
                                            obj = (uint64_t *)0;
                                        }
                                        else {
                                            obj = (uint64_t *)(rc >> 0x1a & 0x3fffffffc0 | 0xfffffe0000000000);
                                        }
                                    }
                                    else {
                                        obj = (uint64_t *)&hv_map_wire_copy;
                                        if ((*(uint32_t *)(entry + 7) & 2) != 0) {
                                            obj = (uint64_t *)&hv_map_wire_ro;
                                        }
                                    }
                                    ent_node[6] = obj;
                                    if ((*(uint32_t *)(entry + 7) >> 0x1e & 1) == 0) {
                                        if ((*(uint32_t *)((long)entry + 0x2c) == 0) ||
                                            (obj = (uint64_t *)((uint64_t)*(uint32_t *)((long)entry + 0x2c) << 6 | 0xfffffe0000000000),
                                             obj == (uint64_t *)0)) goto l_node_flags;
                                    }
                                    else {
                                        obj = (uint64_t *)&hv_map_wire_copy;
                                        if ((*(uint32_t *)(entry + 7) & 2) != 0) {
                                            obj = (uint64_t *)&hv_map_wire_ro;
                                        }
                                    }
                                    kernel_vm_obj_ref(obj);
                                    refc = *(int *)(obj + 5);
                                    *(int *)(obj + 5) = refc + 1;
                                    if (refc + 0xf0000001U < 0xf0000002) goto l_panic_ovf;
                                    kernel_obj_lock(obj + 1);
                                }
                                else {
                                    *(uint8_t *)(ent_node + 5) = 0;
                                    ent_node[6] = (uint64_t *)0;
                                }
l_node_flags:
                                *ent_node = (uint64_t *)0;
                                ent_node[1] = ent_tail;
                                *ent_tail = ent_node;
                                ent_tail = ent_node;
                            }
                        }
                        goto l_wire_end;
                    }
                    goto l_out;
                }
            }
        }
l_wire_end:
        status = 4;
    }
l_out:
    if (wired_page_out != (uint32_t *)0) {
        *wired_page_out = 0;
    }
    wire_kind = 0;
    if ((uint32_t)status != 0x20000001) {
        wire_kind = (uint32_t)status;
    }
    return (uint64_t)wire_kind;
l_walk_new:
    if (entry == (uint64_t *)0) goto l_walk_done;
    if (*(char *)(entry + 5) != '\0') {
        rc = (uint64_t)kernel_map_copy_enter((void *)vmap, entry[6], entry[4], entry[3] - entry[2], param5, ent_flags);
        if ((int)rc != 0) {
            unwired_flag = false;
            entry = ent_head;
            goto l_release_chain;
        }
        *(uint8_t *)(entry + 5) = 1;
    }
    entry = (uint64_t *)*entry;
    goto l_walk_new;
l_walk_done:
    kernel_map_lock(map);
    rc = (uint64_t)kernel_map_lookup(&state, map, status, va_end, lookup_flags | 0x4000);
    if ((int)rc == 0) {
        if (state_lo != vmap) {
            kernel_panic_msg_fmt("transparent submap configuration unexpectedly changed during vm_map_wire @%s:%d");
        }
        ent_node = &ent_head;
l_wire_all:
        do {
            ent_node = (uint64_t **)*ent_node;
            if (state_block != (uint64_t *)0) {
                if (((state_ctrl & 0xc) == 8) && (state_end <= (uint64_t)state_block[3])) {
                    if ((((uint8_t)state_flags >> 2) & 1) == 0) {
                        state = CONCAT44(state_c4, state_c8);
                    }
                    else {
                        state_hi = state_b0 + state_hi;
                        state = state + state_b0;
                    }
                    state_block = (uint64_t *)CONCAT44(state_a4, state_a8);
                    state_end = CONCAT44(state_bc, state_c0);
                    state_lo = CONCAT44(state_b4, state_b8);
                    state_ctrl = state_ctrl & 0xfffffff3;
                    state_b0 = 0;
                    state_a8 = 0;
                    state_a4 = 0;
                }
                rc = state_block[3];
                if ((uint64_t)state_block[3] < state_end) goto l_wire_entry;
l_wire_all_done:
                state_block = (uint64_t *)0;
                *(uint64_t *)(cur + 0x238) = 0;
                if ((state_ctrl & 0xc) == 8) {
                    if ((((uint8_t)state_flags >> 2) & 1) == 0) {
                        state = CONCAT44(state_c4, state_c8);
                    }
                    else {
                        state_hi = state_b0 + state_hi;
                        state = state + state_b0;
                    }
                    state_block = (uint64_t *)CONCAT44(state_a4, state_a8);
                    state_lo = CONCAT44(state_b4, state_b8);
                    state_end = CONCAT44(state_bc, state_c0);
                    state_ctrl = state_ctrl & 0xfffffff3;
                    state_b0 = 0;
                    state_a8 = 0;
                    state_a4 = 0;
                }
                if (((state_flags >> 2) & 1) == 0) {
                    kernel_vm_unwire(&state);
                }
                else if ((state_block != (uint64_t *)0) && ((~(uint32_t)*(state_block + 5) & 3) != 0)) {
                    kernel_vm_sync(0, 0);
                }
                state_lo = 0;
                state_block = (uint64_t *)0;
                state_hi = 0;
                state_d8 = 0;
                state_ctrl = 0;
                state_hi = 0;
                state_cc = 0;
                state_c8 = 0;
                state_d4 = 0;
                state_d0 = 0;
                state_bc = 0;
                state_b8 = 0;
                state_c4 = 0;
                state_c0 = 0;
                state_b0 = 0;
                state_a8 = 0;
                state_b4 = 0;
                state_b0 = 0;
                state_a4 = 0;
                entry = ent_head;
                if (ent_head == (uint64_t *)0) {
                    return 0;
                }
                goto l_free_chain;
            }
            state_ctrl = state_ctrl & 0xfffffffd;
            state_block = &state_hi;
            rc = state;
l_wire_entry:
            entry = (uint64_t *)*state_block;
            if (((state_flags >> 0x13) & 1) == 0) {
l_wire_entry2:
                if (entry == (uint64_t *)0) goto l_wire_all_done;
            }
            else if ((entry[5] & 3) == 2) {
                entry_end = CONCAT44(state_bc, state_c0);
                entry_meta = entry[3];
                state_b0 = entry[2] - (entry[6] & 0xfffffffffffff000);
                state = rc - state_b0;
                state_end = ((entry_end <= entry_meta) * entry_end + (entry_end > entry_meta) * entry_meta) - state_b0;
                state_lo = entry[5] & 0xfffffffffffffffc;
                state_block = (uint64_t *)0;
                state_ctrl = state_ctrl & 0xfffffff3 | 8;
                state_a8 = SUB84(entry, 0);
                state_a4 = (uint32_t)((uint64_t)entry >> 0x20);
                if (((state_flags >> 2) & 1) != 0) {
                    state_hi = state;
                }
                entry = (uint64_t *)kernel_map_lookup_entry((void *)0, 0);
                goto l_wire_entry2;
            }
            obj2 = (uint64_t *)entry[3];
            obj = ent_node[3];
            state_block = entry;
            if (obj2 < ent_node[3]) {
                ent_node2 = (uint64_t **)hv_zone_alloc(&hv_zone_entry_zone3, 0);
                obj = ent_node[6];
                obj2_2 = ent_node[2];
                obj2_5 = ent_node[5];
                obj2_4 = ent_node[4];
                obj2_1 = ent_node[1];
                obj2_0 = *ent_node;
                ent_node2[3] = ent_node[3];
                ent_node2[2] = obj2_2;
                ent_node2[5] = obj2_5;
                ent_node2[4] = obj2_4;
                ent_node2[6] = obj;
                ent_node2[1] = obj2_1;
                *ent_node2 = obj2_0;
                *ent_node2 = (uint64_t *)0;
                ent_node2[1] = (uint64_t *)0;
                if ((((*(uint8_t *)((long)ent_node2 + 0x29) & 1) == 0) &&
                    (obj = ent_node[6], obj != (uint64_t *)0))) {
                    kernel_vm_obj_ref(obj);
                    refc = *(int *)(obj + 5);
                    *(int *)(obj + 5) = refc + 1;
                    if (refc + 0xf0000001U < 0xf0000002) {
l_panic_ovf:
                        hv_mem_panic_86a4((void *)0);
                    }
                    kernel_obj_lock(obj + 1);
                }
                ent_node2[4] = (uint64_t *)(((long)obj2 - (long)ent_node[2]) + (long)ent_node2[4]);
                ent_node2[2] = obj2;
                obj = *ent_node;
                if (obj == (uint64_t *)0) {
                    *ent_node2 = (uint64_t *)0;
                    ent_tail = ent_node2;
                }
                else {
                    if ((uint64_t **)obj[1] != ent_node) {
                        brk_code = (void *)SoftwareBreakpoint(0xbffd, 0xfffffe000b8b0f40);
                        ((void (*)(void))brk_code)();
                    }
                    *ent_node2 = obj;
                    obj[1] = (uint64_t)ent_node2;
                }
                *ent_node = ent_node2;
                ent_node2[1] = ent_node;
                ent_node[3] = obj2;
                obj = obj2;
            }
            kernel_map_vm_fault_ent(&state, entry, obj);
            if (*(char *)(ent_node + 5) != '\x01') {
                if (wired_page_out != (uint32_t *)0) {
                    if (*(char *)(ent_node + 5) == '\x02') break;
l_wire_report:
                    entry_flags = *(uint32_t *)(entry + 7);
                    if (((entry_flags >> 0x1e) & 1) == 0) {
                        if (*(uint32_t *)((long)entry + 0x2c) == 0) {
                            obj = (uint64_t *)0;
                        }
                        else {
                            obj = (uint64_t *)((uint64_t)*(uint32_t *)((long)entry + 0x2c) << 6 | 0xfffffe0000000000);
                        }
                    }
                    else {
                        obj = (uint64_t *)&hv_map_wire_copy;
                        if ((entry_flags & 2) != 0) {
                            obj = (uint64_t *)&hv_map_wire_ro;
                        }
                    }
                    rc = entry[6];
                    if (((entry_flags >> 8) & 1) == 0) {
                        kernel_vm_obj_ref((uint64_t)0);
                    }
                    else {
                        kernel_vm_page_wire(obj);
                    }
                    page_obj = kernel_pmap_findpage(obj, rc & 0xfffffffffffff000);
                    if ((page_obj == 0) || (page_state = *(uint8_t *)(page_obj + 0x2a) & 0xf, page_state != 1 && page_state != 0xe)) {
                        kernel_panic_msg_fmt("Tried to lookup a wired page, but the page wasn\'t wired page=%p start=%llx end=%llx entry=%p @%s:%d");
                    }
                    page_num = *(uint32_t *)(page_obj + 0x30);
                    if ((*(uint8_t *)((long)entry + 0x39) & 1) != 0) {
                        *(uint32_t *)(page_obj + 0x2c) = *(uint32_t *)(page_obj + 0x2c) | 0x1000;
                    }
                    kernel_obj_lock(obj + 1);
                    *wired_page_out = page_num;
                }
                goto l_wire_all;
            }
            rc = entry[5];
            if (((((uint32_t)rc >> 1) & 1) == 0) && ((*(uint8_t *)((long)ent_node + 0x29) & 1) == 0)) {
                if ((*(uint32_t *)(entry + 7) >> 0x1e & 1) == 0) {
                    if (rc >> 0x20 == 0) {
                        obj = (uint64_t *)0;
                    }
                    else {
                        obj = (uint64_t *)(rc >> 0x1a & 0x3fffffffc0 | 0xfffffe0000000000);
                    }
                }
                else {
                    obj = (uint64_t *)&hv_map_wire_copy;
                    if ((*(uint32_t *)(entry + 7) & 2) != 0) {
                        obj = (uint64_t *)&hv_map_wire_ro;
                    }
                }
                if (obj == ent_node[6]) {
                    if ((long)ent_node[4] - (entry[6] & 0xfffffffffffff000) ==
                        (long)ent_node[2] - entry[2]) {
                        if (*(int16_t *)((long)entry + 0x3c) == 0) {
                            rc = (uint64_t)kernel_map_entry_wired((void *)vmap, entry, wire_mode != 0);
                            if ((int)rc == 0) {
                                entry_meta = (uint64_t)wire_flags;
                                rc = (uint64_t)kernel_map_copy_enter((void *)vmap, entry, entry_meta, param5, wired_page_out, &state);
                                if ((int)rc != 0) {
                                    if (wire_mode == 0) {
l_entry_refc:
                                        entry_refc = *(uint16_t *)((long)entry + 0x3c);
                                        if (entry_refc == 0) goto l_zap;
                                        *(uint16_t *)((long)entry + 0x3c) = entry_refc - 1;
                                        if (entry_refc < 3) {
                                            kernel_map_entry_free(entry);
                                        }
                                    }
                                    else {
                                        entry_refc2 = *(int16_t *)((long)entry + 0x3e);
                                        if ((entry_refc2 != 0) && (*(int16_t *)((long)entry + 0x3e) = entry_refc2 + -1, entry_refc2 == 1)) {
                                            *(long *)(vmap + 0x80) = *(long *)(vmap + 0x80) + (entry[2] - entry[3]);
                                            goto l_entry_refc;
                                        }
                                    }
                                    *(uint8_t *)(ent_node + 5) = 2;
                                    *(uint64_t *)(cur + 0x238) = 0;
                                    goto l_unwire_state;
                                }
                                *(uint8_t *)(ent_node + 5) = 0;
                                goto l_wire_all;
                            }
                        }
                        else {
                            kernel_map_entry_uncow(vmap, (uint64_t)ent_node[6], (uint64_t)ent_node[4], (long)ent_node[3] - (long)ent_node[2]);
                            *(uint8_t *)(ent_node + 5) = 2;
                            rc = (uint64_t)kernel_map_entry_wired((void *)vmap, entry, wire_mode != 0);
                            if ((int)rc == 0) {
                                *(uint8_t *)(ent_node + 5) = 0;
                                if (wired_page_out != (uint32_t *)0) goto l_wire_report;
                                goto l_wire_all;
                            }
                        }
                        *(uint64_t *)(cur + 0x238) = 0;
                        if ((state_ctrl & 0xc) == 8) {
                            if ((((uint8_t)state_flags >> 2) & 1) == 0) {
                                state = CONCAT44(state_c4, state_c8);
                            }
                            else {
                                state_hi = state_b0 + state_hi;
                                state = state + state_b0;
                            }
                            state_block = (uint64_t *)CONCAT44(state_a4, state_a8);
                            state_lo = CONCAT44(state_b4, state_b8);
                            state_end = CONCAT44(state_bc, state_c0);
                            state_ctrl = state_ctrl & 0xfffffff3;
                            state_b0 = 0;
                            state_a8 = 0;
                            state_a4 = 0;
                        }
                        if (((state_flags >> 2) & 1) == 0) {
                            kernel_vm_unwire(&state);
                        }
                        else if ((state_block != (uint64_t *)0) && ((~(uint32_t)*(state_block + 5) & 3) != 0)) {
                            kernel_vm_sync(0, 0);
                        }
                        unwired_flag = false;
                        map = (void *)CONCAT44(state_b4, state_b8);
                        state_lo = 0;
                        state_block = (uint64_t *)0;
                        state_hi = 0;
                        state_d8 = 0;
                        state_ctrl = 0;
                        state_hi = 0;
                        state_cc = 0;
                        state_c8 = 0;
                        state_d4 = 0;
                        state_d0 = 0;
                        state_bc = 0;
                        state_b8 = 0;
                        state_c4 = 0;
                        state_c0 = 0;
                        state_b0 = 0;
                        state_a8 = 0;
                        state_b4 = 0;
                        state_b0 = 0;
                        state_a4 = 0;
                        *(uint8_t *)(ent_node + 5) = 2;
                        entry = ent_head;
                        goto l_release_chain;
                    }
                }
            }
            if (wire_mode == 0) {
                if ((*(uint64_t **)(vmap + 0x58) != (uint64_t *)0) &&
                   (*(uint64_t **)(vmap + 0x58) == &hv_kernel_map_sentinel)) {
                    kernel_map_wire_zap(vmap, status, va_end, entry[2], entry[3]);
                    entry_meta = va_end;
l_zap:
                    {
                        hv_u128_t a = kernel_map_wire_lookup(vmap, entry);
                        wire_key[0] = (uint8_t)a.lo; wire_key[8] = (uint8_t)a.hi;
                    }
                    vmap = *(uint64_t *)(entry_meta + 0x28);
                    if (((((uint32_t)vmap >> 1) & 1) == 0) &&
                       (wire_kind = *(uint32_t *)(entry_meta + 0x38), ((wire_kind >> 6) & 1) == 0)) {
                        lookup_flags = *(uint32_t *)(*(uint64_t *)(wire_key + 0) + 0x20);
                        if (((wire_kind >> 0x1e) & 1) == 0) {
                            if (vmap >> 0x20 == 0) {
                                return 4;
                            }
                            wire_obj = (void *)(vmap >> 0x1a & 0x3fffffffc0 | 0xfffffe0000000000);
                            if (wire_obj == (void *)0) {
                                return 4;
                            }
                        }
                        else {
                            wire_obj = &hv_map_wire_copy;
                            if ((wire_kind & 2) != 0) {
                                wire_obj = &hv_map_wire_ro;
                            }
                        }
                        if (*(int *)(wire_obj + 0x70) != 4) {
                            if ((lookup_flags & wire_kind >> 7 & 7) != lookup_flags) {
                                return 2;
                            }
                            if (*(long *)(entry_meta + 0x18) - *(long *)(entry_meta + 0x10) == 0x4000) {
                                vmap = kernel_map_page_cow(*(uint64_t *)(wire_key + 8), entry_meta, lookup_flags);
                                return vmap;
                            }
                        }
                    }
                    return 4;
                }
                *(uint64_t *)(cur + 0x238) = 0;
                if ((state_ctrl & 0xc) == 8) {
                    if ((((uint8_t)state_flags >> 2) & 1) == 0) {
                        state = CONCAT44(state_c4, state_c8);
                    }
                    else {
                        state_hi = state_b0 + state_hi;
                        state = state + state_b0;
                    }
                    state_block = (uint64_t *)CONCAT44(state_a4, state_a8);
                    state_lo = CONCAT44(state_b4, state_b8);
                    state_end = CONCAT44(state_bc, state_c0);
                    state_ctrl = state_ctrl & 0xfffffff3;
                    state_b0 = 0;
                    state_a8 = 0;
                    state_a4 = 0;
                }
                if (((state_flags >> 2) & 1) == 0) {
                    kernel_vm_unwire(&state);
                }
                else if ((state_block != (uint64_t *)0) && ((~(uint32_t)*(state_block + 5) & 3) != 0)) {
                    kernel_vm_sync(0, 0);
                }
                rc = 0;
                map = (void *)CONCAT44(state_b4, state_b8);
                unwired_flag = true;
                goto l_reset;
            }
            kernel_map_entry_uncow(vmap, (uint64_t)ent_node[6], (uint64_t)ent_node[4], (long)ent_node[3] - (long)ent_node[2]);
            *(uint8_t *)(ent_node + 5) = 2;
        } while (wired_page_out == (uint32_t *)0);
        *(uint64_t *)(cur + 0x238) = 0;
        if ((state_ctrl & 0xc) == 8) {
            if ((((uint8_t)state_flags >> 2) & 1) == 0) {
                state = CONCAT44(state_c4, state_c8);
            }
            else {
                state_hi = state_b0 + state_hi;
                state = state + state_b0;
            }
            state_block = (uint64_t *)CONCAT44(state_a4, state_a8);
            state_lo = CONCAT44(state_b4, state_b8);
            state_end = CONCAT44(state_bc, state_c0);
            state_ctrl = state_ctrl & 0xfffffff3;
            state_b0 = 0;
            state_a8 = 0;
            state_a4 = 0;
        }
        if (((state_flags >> 2) & 1) == 0) {
            kernel_vm_unwire(&state);
        }
        else if ((state_block != (uint64_t *)0) && ((~(uint32_t)*(state_block + 5) & 3) != 0)) {
            kernel_vm_sync(0, 0);
        }
        unwired_flag = false;
        map = (void *)CONCAT44(state_b4, state_b8);
        rc = 1;
        goto l_reset;
    }
    *(uint64_t *)(cur + 0x238) = 0;
    goto l_clear_state;
l_free_chain:
    obj = (uint64_t *)*entry;
    if (obj == (uint64_t *)0) {
        ent_node = (uint64_t **)entry[1];
        if (*(uint64_t **)entry[1] != entry) goto l_brk1;
    }
    else {
        if ((uint64_t *)obj[1] != entry) {
            brk_code = (void *)SoftwareBreakpoint(0xbffd, 0xfffffe000b8b0f38);
            ((void (*)(void))brk_code)();
        }
        if (*(uint64_t **)entry[1] != entry) {
l_brk1:
            brk_code = (void *)SoftwareBreakpoint(0xbffd, 0xfffffe000b8b0f30);
            ((void (*)(void))brk_code)();
        }
        obj[1] = (uint64_t)entry[1];
        ent_node = ent_tail;
    }
    ent_tail = ent_node;
    *(uint64_t *)entry[1] = *entry;
    if ((*(uint8_t *)((long)entry + 0x29) & 1) == 0) {
        kernel_vm_page_unwire(entry[6]);
    }
    kernel_vm_free(&hv_zone_entry_zone4, entry);
    entry = obj;
    if (obj == (uint64_t *)0) {
        return 0;
    }
    goto l_free_chain;
l_free_node2:
    wire_obj = &hv_zone_entry_zone;
l_free_node:
    kernel_vm_free(wire_obj, ent_node);
    cur = tpidr_el1;
    *(uint64_t *)(cur + 0x238) = 0;
l_unwire_state:
    if ((state_ctrl & 0xc) == 8) {
        if ((((uint8_t)state_flags >> 2) & 1) == 0) {
            state = CONCAT44(state_c4, state_c8);
        }
        else {
            state_hi = state_b0 + state_hi;
            state = state + state_b0;
        }
        state_block = (uint64_t *)CONCAT44(state_a4, state_a8);
        state_lo = CONCAT44(state_b4, state_b8);
        state_end = CONCAT44(state_bc, state_c0);
        state_ctrl = state_ctrl & 0xfffffff3;
        state_b0 = 0;
        state_a8 = 0;
        state_a4 = 0;
    }
    if (((state_flags >> 2) & 1) == 0) {
        kernel_vm_unwire(&state);
    }
    else if ((state_block != (uint64_t *)0) && ((~(uint32_t)*(state_block + 5) & 3) != 0)) {
        kernel_vm_sync(0, 0);
    }
    map = (void *)CONCAT44(state_b4, state_b8);
l_clear_state:
    unwired_flag = false;
l_reset:
    state_a8 = 0;
    state_b0 = 0;
    state_b0 = 0;
    state_b4 = 0;
    state_b8 = 0;
    state_bc = 0;
    state_c0 = 0;
    state_c4 = 0;
    state_c8 = 0;
    state_cc = 0;
    state_d0 = 0;
    state_d4 = 0;
    state_d8 = 0;
    state_hi = 0;
    state_hi = 0;
    state_ctrl = 0;
    state_block = (uint64_t *)0;
    state_lo = 0;
    state_a4 = 0;
    entry = ent_head;
l_release_chain:
    ent_head = entry;
    if (entry != (uint64_t *)0) {
        do {
            if (*(char *)(entry + 5) == '\x01') {
                kernel_map_entry_uncow(vmap, entry[6], entry[4], entry[3] - entry[2]);
            }
            else if ((*(char *)(entry + 5) == '\0') && ((*(uint8_t *)((long)entry + 0x29) & 1) == 0)) {
                kernel_copyin2(vmap, entry[2], entry[3], param6, &hv_vm_unwire_fault_table);
            }
            entry = (uint64_t *)*entry;
            obj = ent_head;
        } while (entry != (uint64_t *)0);
        while (obj != (uint64_t *)0) {
            entry = (uint64_t *)*obj;
            if (entry == (uint64_t *)0) {
                ent_node = (uint64_t **)obj[1];
                if (*(uint64_t **)obj[1] != obj) goto l_brk2;
            }
            else {
                if ((uint64_t *)entry[1] != obj) {
                    brk_code = (void *)SoftwareBreakpoint(0xbffd, 0xfffffe000b8b0f28);
                    ((void (*)(void))brk_code)();
                }
                if (*(uint64_t **)obj[1] != obj) {
l_brk2:
                    brk_code = (void *)SoftwareBreakpoint(0xbffd, 0xfffffe000b8b0f1c);
                    ((void (*)(void))brk_code)();
                }
                entry[1] = (uint64_t)obj[1];
                ent_node = ent_tail;
            }
            ent_tail = ent_node;
            *(uint64_t *)obj[1] = *obj;
            if ((*(uint8_t *)((long)obj + 0x29) & 1) == 0) {
                kernel_vm_page_unwire(obj[6]);
            }
            kernel_vm_free(&hv_zone_entry_zone4, obj);
            obj = entry;
        }
    }
    if (!unwired_flag) {
        return rc;
    }
    entry_flags = (wire_kind < 0x20) * wire_kind + (uint32_t)(wire_kind >= 0x20) * 0x1f;
    hv_stat_wire_count[entry_flags] = hv_stat_wire_count[entry_flags] + 1;
    kernel_vm_wire_callback((uint64_t)hv_wire_callback_fn, 0, hv_stat_wire_msg[(wire_kind < 8) * wire_kind + (uint32_t)(wire_kind >= 8) * 7], 1000);
    kernel_vm_wire_callback2(0, 0, 0);
    wire_kind = wire_kind + 1;
    if (wired_page_out != (uint32_t *)0) goto l_wire_out;
l_no_wire_out:
    fault_rec = &fault_name2;
    fault_name2 = &hv_vm_wire_string;
    fault_word = 0x40000000;
    fault_fn = (void *)0xfffffe000b8b10fc;
    fault_name3 = &hv_vm_wire_string2;
    fault_flags = wire_flags;
    goto l_wire_loop;
}

/* ================================================================== *
 * kernel_mem_release @ 0xfffffe000b8a8078   (est. kernel_mem_release)
 * Ghidra: ulong FUN_fffffe000b8a8078(long param_1, ulong param_2, ulong param_3)
 * Releases/commits a validated kernel range after copyin/copyout: aligns the
 * range against the map window, runs the fault-table vtable probe
 * (kernel_vm_prot_remove b9153f0) and, on the not-modified path, removes the
 * mapping via kernel_vm_unmap_remove (b8b355c). Returns 0 on success,
 * 4 (KERN_FAILURE-ish) on a misaligned/short range, or the probe status.
 * Confidence: high (complete decompile, 45 lines)
 * Notes: map sentinel DAT_fffffe000c62b698, map base DAT_fffffe000c62b6a8,
 *   fault-table report b8847f0. Called by hv.c hv_vm_map_core / hv_vcpu_slot_op.
 * Kernel code recreated for audit (hv-deps). */
int
kernel_mem_release(uint64_t map, uint64_t start, uint64_t len)
{
    uint64_t ret;          /* uVar1: vtable-probe status */
    uint64_t va;           /* r3: aligned start / page mask result */
    uint64_t lo, hi;       /* r4/r5: range bounds */
    uint64_t *pmap;        /* pobj_word: map's pmap */
    int rc;                /* iVar2 */

    if (map == 0) {
l_err:
        va = 4;
    } else {
        pmap = *(uint64_t **)(map + 0x58);
        if (pmap != (uint64_t *)0) {
            if (pmap == &hv_kernel_map_sentinel) {   /* DAT_fffffe000c62b698 */
                va = hv_kernel_map_base & (long)(start << 8) >> 0x3f | start;  /* DAT_fffffe000c62b6a8 */
            } else {
                if ((start >> 0x37 & 1) != 0)
                    goto l_aligned;
                va = pmap[3] - 1 & start;
            }
            if (va != start)
                goto l_err;
        }
l_aligned:
        if (len != 0) {
            va = (uint64_t)(uint)~(-1 << (uint64_t)(*(uint16_t *)(map + 0x44) & 0x1f));
            if (!CARRY8(start, len)) {
                lo = start & (va ^ 0xffffffffffffffff);
                hi = start + len + va & ~va;
                if (lo < hi)
                    goto l_call;
            }
            ret = kernel_vm_prot_remove(4, start, len, va);   /* FUN_fffffe000b9153f0 */
            rc = (int)ret;
            if (ret >> 0x28 != 0) {
                kernel_vm_report_fault(8, 1, 1, 8, start, len, va, 0, 4,
                                       (long)rc);             /* FUN_fffffe000b8847f0 */
            }
            if ((ret >> 0x20 & 1) == 0)
                goto l_err;
            lo = ret & 0xffffffff;
            hi = lo;
            if (rc == 0) {
l_call:
                va = kernel_vm_unmap_remove(map, lo, hi, 0, 0);  /* FUN_fffffe000b8b355c */
                return va;
            }
            if (rc != 0x20000001)
                return ret;
        }
        va = 0;
    }
    return va;
}

/* ================================================================== *
 * kernel_copyin2 @ 0xfffffe000b8b122c   (est. kernel_copyin2 / vm_map_unwire)
 * Ghidra: ulong * FUN_fffffe000b8b122c(long param_1, ulong param_2, long param_3,
 *                                      int param_4, long param_5)
 * The unwire pass used to undo vm_map_wire (kernel_copyin) on failure:
 * aligns the range, walks the map entries dropping each entry's refcounts
 * (+0x3c/+0x3e), unwires the pages via the fault-state machine and, for
 * entries still marked wired, resolves the wire key through
 * kernel_map_wire_lookup (c0ed834). Returns 0 on success, &DAT_00000004
 * (status 4) on probe failure, or the probe status.
 * Confidence: high (complete decompile, ~150 lines)
 * Notes: fault-table vtable probe via b918644 lookup (flags 0x4029); unwire
 *   b91ab24 / sync b91600c; entry free b9166e0; entry-uncow b8a3de4;
 *   wire-lookup c0ed834; report b8847f0. Called by hv_vcpu_slot_op and the
 *   kernel_copyin release chain.
 * Kernel code recreated for audit (hv-deps). */
uint64_t *
kernel_copyin2(uint64_t map, uint64_t start, uint64_t end, uint64_t flags,
               void *fault_table)
{
    int16_t  entry_refc2;     /* sVar1: entry refcount at +0x3e */
    uint     state_lo;        /* r2: low word of the state flags */
    uint64_t *rc;             /* pr3: status return */
    ushort   entry_refc;      /* r4: entry refcount at +0x3c */
    uint     state_word;      /* r5 */
    uint64_t va_start;        /* obj_word: aligned range start */
    uint64_t va_end;          /* uVar7: aligned range end */
    uint64_t *pmap;           /* e8 */
    long     cur;             /* page_off: tpidr_el1 (also entry_pmap reuse) */
    uint64_t va;              /* uVar10 */
    uint64_t *entry;          /* obj_b: current map entry */
    uint64_t page_mask;       /* prot_ro2 */
    uint64_t state;           /* local_c0 */
    uint64_t state_end;       /* uStack_b8 */
    uint64_t vmap;            /* local_b0: active map */
    uint64_t *state_block;    /* puStack_a8 */
    void **  opts_ptr;        /* out_a0 = &PTR_DAT_fffffe0007d7fb70 */
    uint64_t state_flags;     /* obj_list: CONCAT44 state flags */
    uint64_t state_words[7];  /* obj_tail[7] */
    uint64_t *state_lo_ptr;   /* local_58 */

    state_words[5] = 0;
    state_words[4] = 0;
    state_lo_ptr = (uint64_t *)0;
    state_words[6] = 0;
    state_words[1] = 0;
    state_words[0] = 0;
    state_words[3] = 0;
    state_words[2] = 0;
    state_block = (uint64_t *)0;
    vmap = 0;
    state_flags = 0;
    opts_ptr = (void **)0;
    state_end = 0;
    state = 0;

    pmap = *(uint64_t **)(map + 0x58);
    va = start;
    if (pmap != (uint64_t *)0) {
        if (pmap == &hv_kernel_map_sentinel) {        /* DAT_fffffe000c62b698 */
            va = hv_kernel_map_base & (long)(start << 8) >> 0x3f | start;    /* DAT_fffffe000c62b6a8 */
        } else if ((start >> 0x37 & 1) == 0) {
            va = pmap[3] - 1 & start;
        }
    }
    start = end - start;
    if (start == 0) {
        return (uint64_t *)0;
    }
    page_mask = (uint64_t)(uint)~(-1 << (uint64_t)(*(uint16_t *)(map + 0x44) & 0x1f));
    if (CARRY8(va, start)) {
l_probe:
        if (*(void **)((uint8_t *)fault_table + 0x20) == (void *)0) {
l_err4:
            return (uint64_t *)0x4;                    /* DAT_00000004: Ghidra global at VA 4 */
        }
        rc = (uint64_t *)((hv_vtable_call_t)(*(void **)((uint8_t *)fault_table + 0x20)))
             (4, va, start, page_mask);
        if (((uint64_t)rc >> 0x28 & 1) != 0) {
            kernel_vm_report_fault(*(uint64_t *)((uint8_t *)fault_table + 0x10), 1, 1,
                                   *(uint32_t *)((uint8_t *)fault_table + 0x18),
                                   va, start, page_mask, 0, 4, (long)(int)rc);
        }
        if (((uint64_t)rc >> 0x20 & 1) == 0)
            goto l_err4;
        if ((int)rc != 0)
            goto l_done;
        va_start = 0;
        va_end = 0;
    } else {
        va_start = va & (page_mask ^ 0xffffffffffffffff);
        va_end = start + va + page_mask & ~page_mask;
        if (va_end <= va_start)
            goto l_probe;
    }
    va = *(uint64_t *)(map + 0x28);
    page_mask = *(uint64_t *)(map + 0x30);
    va = (va <= va_start) * va_start + (va > va_start) * va;
    page_mask = (va_end <= page_mask) * va_end + (va_end > page_mask) * page_mask;
    if (page_mask <= va) {
        return (uint64_t *)0;
    }
    opts_ptr = (void **)0xfffffe0007d7fb70;   /* &PTR_DAT_fffffe0007d7fb70 (decompiler global; dead store) */
    kernel_map_lock(0);                               /* FUN_fffffe000b7f5398; decompiler drops the arg */
    rc = (uint64_t *)kernel_map_lookup(&state, (void *)map, va, page_mask, 0x4029); /* FUN_fffffe000b918644 */
    if ((int)rc != 0) {
        cur = tpidr_el1;
        *(uint64_t *)(cur + 0x238) = 0;
        return rc;
    }
    rc = state_words;
    for (;;) {
        entry = state_lo_ptr;
        if (state_block == (uint64_t *)0) {
            state_lo = (uint32_t)(state_flags >> 32) & 0xfffffffd;
            state_flags = state_flags & 0xfffffffdffffffff;
            state_block = rc;
            va = state;
        } else {
            state_lo = (uint32_t)(state_flags >> 32);
            if ((((uint32_t)(state_flags >> 32) & 0xc) == 8) &&
                (state_end <= state_block[3])) {
                va = state_words[3];
                if (((uint8_t)state_flags >> 2 & 1) != 0) {
                    state_words[0] = state_words[6] + state_words[0];
                    va = state + state_words[6];
                }
                vmap = state_words[5];
                state_end = state_words[4];
                state_lo = (uint32_t)(state_flags >> 32) & 0xfffffff3;
                state_flags = state_flags & 0xfffffff3ffffffff;
                state_words[6] = 0;
                state_lo_ptr = (uint64_t *)0;
                state_block = entry;
                state = va;
            }
            va = state_block[3];
            if (state_end <= state_block[3]) {
                state_block = (uint64_t *)0;
                goto l_unwire_done;
            }
        }
        entry = (uint64_t *)*state_block;
        state_lo = (uint32_t)state_flags;
        if (((uint32_t)state_flags >> 0x13 & 1) != 0)
            break;
l_walk:
        state_block = entry;
        if (entry == (uint64_t *)0) {
l_unwire_done:
            cur = tpidr_el1;
            *(uint64_t *)(cur + 0x238) = 0;
            state_lo = (uint32_t)state_flags;
            if (((uint32_t)(state_flags >> 32) & 0xc) == 8) {
                va = state_words[3];
                if (((uint8_t)state_flags >> 2 & 1) != 0) {
                    state_words[0] = state_words[6] + state_words[0];
                    va = state + state_words[6];
                }
                state_block = state_lo_ptr;
                vmap = state_words[5];
                state_end = state_words[4];
                state_flags = state_flags & 0xfffffff3ffffffff;
                state_words[6] = 0;
                state_lo_ptr = (uint64_t *)0;
                state = va;
            }
            if ((state_lo >> 2 & 1) == 0) {
                kernel_vm_unwire(&state);             /* FUN_fffffe000b91ab24 */
                return (uint64_t *)0;
            }
            if (state_block == (uint64_t *)0) {
                return (uint64_t *)0;
            }
            if ((~(uint32_t)state_block[5] & 3) == 0) {
                return (uint64_t *)0;
            }
            kernel_vm_sync(0, 0);                         /* FUN_fffffe000b91600c */
            return (uint64_t *)0;
        }
        if (flags == 0)
            goto l_entry_process;
l_entry_refc2:
        entry_refc2 = *(int16_t *)((long)entry + 0x3e);
        state_block = entry;
        if ((entry_refc2 != 0) &&
            (*(int16_t *)((long)entry + 0x3e) = entry_refc2 + -1, entry_refc2 == 1)) {
            *(long *)(vmap + 0x80) = *(long *)(vmap + 0x80) + (entry[2] - entry[3]);
            entry_refc = *(ushort *)((long)entry + 0x3c);
            if (entry_refc == 0)
                goto l_wire_lookup;
l_entry_refc:
            entry = state_block;
            *(ushort *)((long)state_block + 0x3c) = entry_refc - 1;
            if ((entry_refc < 3) &&
                (kernel_map_entry_free(state_block), *(short *)((long)entry + 0x3c) == 0)) {
                *(uint *)(entry + 7) = (uint)entry[7] & 0xffdfffff;
                cur = *(long *)(vmap + 0x58);
                if (cur == 0) {
                    cur = 0;
                }
                kernel_map_entry_uncow6(vmap, entry, 0, cur, entry[2], entry[3]);  /* FUN_fffffe000b8a3de4 */
            }
        }
    }
    if ((entry[5] & 3) == 2) {
        page_mask = entry[3];
        state_words[6] = entry[2] - (entry[6] & 0xfffffffffffff000);
        state = va - state_words[6];
        state_end = ((state_words[4] <= page_mask) * state_words[4] +
                     (state_words[4] > page_mask) * page_mask) - state_words[6];
        vmap = entry[5] & 0xfffffffffffffffc;
        state_block = (uint64_t *)0;
        state_flags = CONCAT44(state_lo, (uint32_t)state_flags) & 0xfffffff3ffffffff | 0x800000000;
        if ((state_lo >> 2 & 1) != 0) {
            state_words[0] = state;
        }
        state_lo_ptr = entry;
        entry = (uint64_t *)kernel_map_lookup_entry(0, 0);   /* FUN_fffffe000b8adda8; decompiler drops the args */
        goto l_walk;
    }
    if (flags != 0)
        goto l_entry_refc2;
l_entry_process:
    entry_refc = *(ushort *)((long)entry + 0x3c);
    state_block = entry;
    if (entry_refc != 0)
        goto l_entry_refc;
l_wire_lookup:
    kernel_map_wire_lookup(vmap, state_block);          /* FUN_fffffe000c0ed834 */
l_done:
    if ((int)rc == 0x20000001) {
        return (uint64_t *)0;
    }
    return rc;
}

/* ================================================================== *
 * kernel_vm_object_batch_dealloc @ 0xfffffe000b8b6860   (est. kernel_vm_object_batch_dealloc)
 * Ghidra: undefined8 FUN_fffffe000b8b6860(void)
 * No-arg batch vm-object release: fetches the head of the kernel's global
 * batch free list (kernel_vm_obj_batch_head b8aa1f4) and drains it, queueing
 * each node through kernel_vm_obj_batch (b8a9e4c = refcount-dec + queue
 * free). Returns the head-getter value. The decompiler renders the head as
 * a local initialized to 0 and loses the getter->list assignment; the drain
 * loop is the real body (confirmed by the earlier disassembly finding).
 * Confidence: high (complete decompile)
 * Notes: called with no arguments by hv.c / hv_vmm.c / hv_vcpu.c; the
 *   decompiler's 5-arg call-site renderings are leftover registers.
 * Kernel code recreated for audit (hv-deps). */
uint64_t
kernel_vm_object_batch_dealloc(void)
{
    uint64_t *node;      /* head_p: next node */
    uint64_t *list;      /* local_30: the free-list head */
    uint64_t head;       /* uVar1: the head getter's return */

    list = (uint64_t *)0;
    head = kernel_vm_obj_batch_head();      /* FUN_fffffe000b8aa1f4 */
    list = (uint64_t *)head;                /* decompiler loses this assignment */
    while (list != (uint64_t *)0) {
        node = (uint64_t *)*list;
        if (node == (uint64_t *)0) {
            /* local_28 tail update elided (dead in the decompile) */
        }
        *list = 0;
        list = node;
        kernel_vm_obj_batch(0);             /* FUN_fffffe000b8a9e4c; arg dropped */
    }
    return head;
}

/* ================================================================== *
 * kernel_alloc @ 0xfffffe000b8a6c14   (est. kernel_alloc)
 * Ghidra: undefined1 [16] FUN_fffffe000b8a6c14(long param_1, ulong *param_2,
 *          undefined8 param_3, ulong param_4, ulong param_5, long param_6)
 * Kernel vm-object allocation returning {error, block} (x0/x1, hv_u128_t:
 * .lo = error/status, .hi = mapped block). Validates the requested size
 * against the allocation ceiling, allocates the translation pages, resolves
 * the object (shared/compressor/special zones by flag bits), wires the pages,
 * inserts the mapping, and returns the block; on failure the partial
 * allocations are unlinked and the error returned. The 0xc8a2/0xa0/0x800/
 * 0xa0000/0xc000 tags come from the flag decode; the hash path (b7a5cc0)
 * derives a VA tag when the caller asked for a random VA.
 * Confidence: high (complete decompile, ~250 lines)
 * Notes: callees b8f58a4 (page alloc), b8faabc (phys alloc), b8cb920 (object
 *   create), b8ce7d4/b8cf3f8 (page wire/obj ref), b7f7050 (obj lock),
 *   b8a730c/b8a748c (map enter), b7f62e8 (lock ref), b7f6aac (unref),
 *   b8cc2f4 (page unwire), b8f19b0 (page enter), b8a756c (phys enter),
 *   b917524 (map sync), b91600c (vm sync), b8f6e54, b990e5c (va tag),
 *   b7a5cc0 (random va), c0ecf34/c0ecf68 (failure paths), c0e0620 (stack
 *   check), c0f86a4 (refcount overflow). DAT_fffffe000c648e40 = alloc ceiling,
 *   DAT_fffffe000c712400/2300/2800 = special objects, DAT_fffffe000c5f0000
 *   = stack marker.
 * Kernel code recreated for audit (hv-deps). */
hv_u128_t
kernel_alloc(uint64_t map, uint64_t size, uint64_t param3, uint64_t flags,
             uint64_t prot, void *alloc_fn)
{
    uint      f_lo;              /* uVar1/hash_acc: flag-word low bits */
    bool      shared;            /* bVar2: 0x400000 shared flag */
    int       rc;                /* iVar3 */
    uint32_t *obj;               /* pr4: the resolved object */
    long      cur;               /* lVar5: tpidr_el1 / sync result */
    uint      tag_bits;          /* obj_word (uVar6): 0x300 flag group */
    uint      obj_word;          /* uVar6 reuse: object flags word / refcount */
    long      sync_out;          /* sync_out */
    uint      prot_word;         /* prot_word: prot word */
    long      page_off;          /* page_off: 0x4000 offset (shared pages) */
    uint8_t  *hash_buf;          /* pbVar10: hash input */
    uint32_t  obj_slot_word;     /* obj_slot_word: object slot word */
    uint      prot_ro2;          /* prot_ro2: 0x40000000 ro/copy prot */
    uint      hash_acc;          /* hash_acc: hash accumulator */
    ulong    *size_ref;          /* unaff_x22: size/flag ref (also the block out) */
    uint64_t  tag;               /* tag: VA tag / high return */
    long     *pg0, *pg1, *pg2;   /* plVar15/obj_tail/entry2/obj_list: page blocks */
    uint64_t  result_lo;         /* result_lo: error / low return */
    uint8_t   pmap_ok;           /* pmap_ok: map-disabled flag */
    uint64_t  aligned_size;      /* aligned_size: aligned size / tagged va */
    hv_u128_t result;            /* acnt_c2: {error, block} */
    hv_u128_t hash_result;       /* acnt_d2 */
    long      sync_ret;          /* sync_ret */
    uint64_t  va_lo, va_hi;
    uint64_t  *block_out;        /* local_68: mapped-block out */
    uint64_t  *phys_blocks[4];   /* local_70/obj_tail/entry2/obj_list */
    uint64_t  phys_count;
    long      stack_marker;      /* lStack_e8 */
    long      map_saved;         /* lStack_e0 */
    uint64_t  flags_saved;       /* st_d8 */
    uint64_t  obj_tag;           /* local_c0 */

    phys_blocks[0] = (long *)0;   /* local_70 */
    block_out = 0;                /* local_68 */
    tag = 0;                      /* off */
    if (((long)size - 1U < 0x1ffffffffff) &&
        (size_ref = (ulong *)(ulong)(((uint)(flags >> 8) & 0x4000) +
                                     ((uint)(flags >> 0xe) & 0x4000) +
                                     ((uint)(flags >> 9) & 0x4000)),
         size_ref <= (ulong *)size)) {
        f_lo = (uint)flags;
        if ((((flags & 0x60) == 0) && (alloc_fn == 0)) &&
            ((ulong *)((0x1fffffffff < DAT_fffffe000c648e40) * DAT_fffffe000c648e40 +
                       (ulong)(0x1fffffffff >= DAT_fffffe000c648e40) * 0x2000000000 >> 6) <
             (ulong *)size)) {
            pg1 = (long *)0;      /* obj_tail */
            pg2 = (long *)0;      /* entry2 */
            pg0 = (long *)0;      /* plVar15 */
            size_ref = (ulong *)0x6;
        } else {
            tag_bits = f_lo & 0x300;
            if ((flags & 0x300) == 0) {
                pmap_ok = *(byte *)(map + 0xb2) & 1;
            } else {
                pmap_ok = 1;
            }
            shared = (flags & 0x400000) != 0;
            tag = 0;
            if (shared) {
                tag = 0x800000000000000;
            }
            page_off = 0;
            if (shared) {
                page_off = 0x4000;
            }
            if ((flags & 0x10000000) != 0) {
                page_off = page_off + 0x4000;
            }
            tag = tag | (ulong)((f_lo & 0x10) >> 4) << 0x34;
            if ((flags & 0x400010) != 0) {
                /* off = tag (carried) */
            }
            /* param3/param1 saved; pmap_ok gates the page-allocation paths */
            if ((flags & 0x400000) == 0 || pmap_ok != 0) {
                pg0 = (long *)0;
l_alloc1:
                pg1 = pg0;                            /* obj_tail */
                if ((flags & 0x10000000) == 0 || pmap_ok != 0) {
                    pg2 = (long *)0;                  /* entry2 */
l_alloc2:
                    if ((flags & 0x800000) == 0 || pmap_ok != 0) {
                        pg0 = (long *)0;
                    } else {
                        pg0 = (long *)kernel_page_alloc((flags & 2) == 0);   /* FUN_fffffe000b8f58a4 */
                        if (pg0 == (long *)0)
                            goto l_fail;
                    }
                    aligned_size = (long)size + 0x3fffU & 0x3ffffffc000;
                    result_lo = aligned_size - (long)size_ref;
                    /* obj_list = pg0 */
                    if ((flags & 0x60) == 0) {
                        if (alloc_fn == 0) {
                            size_ref = (ulong *)kernel_phys_alloc(result_lo >> 0xe, flags, &phys_blocks[0]);  /* FUN_fffffe000b8faabc */
                            rc = (int)size_ref;
                            map = (uint64_t)map_saved;
                            pg0 = (long *)phys_blocks[1];
                        } else {
                            size_ref = (ulong *)((hv_vtable_call_t)(*(void **)(alloc_fn + 0x10)))
                                       (alloc_fn, result_lo, flags, &phys_blocks[0]);
                            rc = (int)size_ref;
                            map = (uint64_t)map_saved;
                            pg0 = (long *)phys_blocks[1];
                        }
                        if (rc != 0)
                            goto l_fail2;
                    }
                    tag = result_lo;
                    if ((f_lo >> 8 & 1) == 0) {
                        if ((f_lo >> 9 & 1) == 0) {
                            obj = (uint32_t *)kernel_pmap_lookup(aligned_size, *(uint64_t *)(map_saved + 0xc0));  /* FUN_fffffe000b8cb920 */
                            kernel_vm_page_wire(0);                             /* FUN_fffffe000b8ce7d4 */
                            *(ulong *)(obj + 6) = aligned_size;
                            obj[0x1c] = 2;
                            obj_word = obj[0x1f];
                            obj[0x1f] = obj_word | 0x200000;
                            if ((f_lo >> 0x1b & 1) != 0) {
                                *(uint8_t *)((long)obj + 0xae) = 0x22;
                                obj[0x1c] = 0;
                                obj[0x1f] = obj_word & 0xffdfffff;
                            }
                        } else {
                            obj = (uint32_t *)&hv_fault_special_400;   /* DAT_fffffe000c712400 */
                            kernel_vm_obj_ref(&hv_fault_special_400);  /* FUN_fffffe000b8cf3f8 */
                            rc = DAT_fffffe000c712428 + 1;
                            obj_word = DAT_fffffe000c712428 + 0xf0000001;
                            DAT_fffffe000c712428 = rc;
                            if (obj_word < 0xf0000002) {
                                kernel_panic_a();                       /* c0f86a4, noreturn */
                            }
                        }
                    } else {
                        if ((f_lo >> 0x1b & 1) == 0) {
                            obj = (uint32_t *)&hv_fault_special_300;    /* DAT_fffffe000c712300 */
                        } else {
                            /* off |= 0x2000 */
                            obj = (uint32_t *)&hv_fault_special_800;    /* DAT_fffffe000c712800 */
                        }
                        kernel_vm_obj_ref(obj);                         /* FUN_fffffe000b8cf3f8 */
                        rc = obj[10];
                        obj[10] = rc + 1;
                        if (rc + 0xf0000001U < 0xf0000002) {
                            kernel_panic_a();                           /* c0f86a4, noreturn */
                        }
                    }
                    kernel_obj_lock(obj + 2);                           /* FUN_fffffe000b7f7050 */
                    pg0 = (long *)phys_blocks[1];
                    if ((f_lo >> 0xd & 1) != 0) {
                        /* off |= 0x1000000000000000 */
                    }
                    if ((f_lo >> 0x15 & 1) != 0) {
                        /* off |= 0x80 */
                    }
                    kernel_map_enter_pre(map, flags, prot, &tag);   /* FUN_fffffe000b8a730c */
                    kernel_map_ref(map);                                /* FUN_fffffe000b7f62e8 */
                    size_ref = (ulong *)kernel_map_enter_insert(map, aligned_size, param3, tag, &block_out); /* FUN_fffffe000b8a748c */
                    sync_ret = kernel_map_unref(map);                     /* FUN_fffffe000b7f6aac */
                    if ((int)size_ref != 0) {
                        kernel_vm_page_unwire((uint64_t)obj);           /* FUN_fffffe000b8cc2f4 */
                        goto l_fail2;
                    }
                    prot_word = (uint)(prot >> 0x20);
                    f_lo = prot_word & 0xfffffffc;
                    if ((prot & 0x100000000) == 0) {
                        f_lo = 0;
                    }
                    prot_ro2 = 0x40000000;
                    if (obj != (uint32_t *)&hv_fault_special_800 &&
                        obj != (uint32_t *)&hv_fault_special_300) {
                        prot_ro2 = 0;
                    }
                    obj_slot_word = 0;
                    if (obj != (uint32_t *)&hv_fault_special_800 &&
                        obj != (uint32_t *)&hv_fault_special_300) {
                        obj_slot_word = (uint32_t)((uint64_t)obj >> 6);
                    }
                    *(ulong *)(block_out + 0x28) =
                         *(ulong *)(block_out + 0x28) & 0xfffffffffffffffc | prot >> 0x20 & 1;
                    tag = *(ulong *)(block_out + 0x10);
                    *(uint *)(block_out + 0x28) = f_lo | prot_word & 1;
                    *(uint32_t *)(block_out + 0x2c) = obj_slot_word;
                    f_lo = *(uint *)(block_out + 0x38);
                    prot_word = prot_ro2 | f_lo & 0xbdbfffff;
                    *(uint *)(block_out + 0x38) = prot_word;
                    if (obj == (uint32_t *)&hv_fault_special_800) {
                        prot_ro2 = prot_word | 2;
l_set_prot:
                        *(uint *)(block_out + 0x38) = prot_ro2;
                    } else if (obj == (uint32_t *)&hv_fault_special_300) {
                        prot_ro2 = prot_ro2 | f_lo & 0xbdbffffd;
                        goto l_set_prot;
                    }
                    result_lo = *(ulong *)(block_out + 0x30);
                    if (tag_bits != 0) {
                        result_lo = tag;
                    }
                    *(ulong *)(block_out + 0x30) = result_lo & 0xfffffffffffff000 | prot & 0xfff;
                    if ((flags & 0x240) == 0) {
                        *(uint16_t *)(block_out + 0x3c) = 1;
                    }
                    if ((pg1 != (long *)0) || (pg2 != (long *)0) ||
                        (pg0 != (long *)0 || (phys_blocks[0] != (long *)0))) {
                        kernel_vm_page_wire(obj);                       /* FUN_fffffe000b8ce7d4 */
                        pg0 = pg1;
                        result_lo = 0;
                        if (tag_bits != 0) {
                            result_lo = tag;
                        }
                        if (pg1 != (long *)0) {
                            kernel_vm_page_enter(pg1, (uint64_t)obj, result_lo, 0, 0, 0);   /* FUN_fffffe000b8f19b0 */
                            *(uint *)((long)pg0 + 0x2c) = *(uint *)((long)pg0 + 0x2c) & 0xfffffffe;
                        }
                        pg0 = pg2;
                        if (pg2 != (long *)0) {
                            kernel_vm_page_enter(pg2, (uint64_t)obj, result_lo + 0x4000, 0, 0, 0);
                            *(uint *)((long)pg0 + 0x2c) = *(uint *)((long)pg0 + 0x2c) & 0xfffffffe;
                        }
                        pg0 = (long *)phys_blocks[1];
                        if (phys_blocks[1] != (long *)0) {
                            kernel_vm_page_enter(phys_blocks[1], (uint64_t)obj, page_off + tag + result_lo, 0, 0, 0);
                            *(uint *)((long)pg0 + 0x2c) = *(uint *)((long)pg0 + 0x2c) & 0xfffffffe;
                        }
                        if (phys_blocks[0] == (long *)0) {
                            sync_ret = kernel_obj_lock(obj + 2);
                        } else {
                            if ((flags & 0x10200) == 0) {
                                obj_tag = 0x23;
                                if ((f_lo >> 0xf & 1) != 0) {
                                    obj_tag = 0xb;
                                }
                            } else {
                                obj_tag = 0xb;
                            }
                            sync_ret = kernel_phys_enter(obj, tag + page_off, result_lo + page_off, tag,
                                                       phys_blocks[0], flags, (uint)prot & 0xffff, 3);  /* FUN_fffffe000b8a756c */
                        }
                    }
                    sync_out = (long)block_out;
                    if ((tag_bits != 0) && ((prot & 0x100000000) == 0)) {
                        sync_ret = kernel_map_sync(map, block_out);       /* FUN_fffffe000b917524 */
                        sync_out = sync_ret;
                    }
                    kernel_vm_sync(sync_ret, sync_out);                      /* FUN_fffffe000b91600c */
                    if ((f_lo & 0x8000020) == 0x8000000) {
                        aligned_size = kernel_va_tag(tag + page_off, tag, 0); /* FUN_fffffe000b990e5c */
                        result_lo = 0;
                        tag = aligned_size - page_off;
                        if (((aligned_size ^ tag) & 0xffc0000000000000) != 0) {
                            tag = tag & 0xffffffffffff | 0xc8a2000000000000;
                        }
                    } else {
                        result_lo = 0;
                    }
                    goto l_ret;
                }
                pg2 = (long *)kernel_page_alloc((flags & 2) == 0);      /* FUN_fffffe000b8f58a4 */
                if (pg2 != (long *)0)
                    goto l_alloc2;
                pg2 = (long *)0;
l_fail:
                pg0 = (long *)0;
            } else {
                pg0 = (long *)kernel_page_alloc((flags & 2) == 0);
                if (pg0 != (long *)0)
                    goto l_alloc1;
                pg1 = (long *)0;
                pg2 = (long *)0;
            }
            size_ref = (ulong *)0x6;
            map = (uint64_t)map_saved;
        }
l_fail2:
        if ((flags & 1) == 0) {
            if (pg1 != (long *)0) {
                *pg1 = (long)phys_blocks[0];
                phys_blocks[0] = pg1;
            }
            if (pg2 != (long *)0) {
                *pg2 = (long)phys_blocks[0];
                phys_blocks[0] = pg2;
            }
            pg2 = phys_blocks[0];
            if (pg0 == (long *)0) {
                if (phys_blocks[0] != (long *)0)
                    goto l_unlink;
            } else {
                *pg0 = (long)phys_blocks[0];
                phys_blocks[0] = pg0;
l_unlink:
                kernel_queue_free_walk(phys_blocks[0], 0);                  /* FUN_fffffe000b8f6e54 */
            }
            tag = 0;
            result_lo = (ulong)size_ref & 0xffffffff;
l_ret:
            result.hi = tag;
            result.lo = result_lo;
            return result;
        }
    } else {
        kernel_alloc_fail_a(map, size, flags);                          /* FUN_fffffe000c0ecf34 */
    }
    tag = flags;
    hash_result = kernel_alloc_fail_b(map, size);                       /* FUN_fffffe000c0ecf68 */
    va_hi = hash_result.hi;
    result_lo = hash_result.lo;
    /* fallback path: tag derivation (stack marker check + hash) */
    stack_marker = DAT_fffffe000c5f0000;
    map_saved = map;
    flags_saved = flags;
    if (hv_fault_boot_threshold < 6 || result_lo != 0) {
        tag = *size_ref & 0xfffffffffffffff;
        goto l_tag_store;
    }
    hash_acc = (uint)(tag >> 0x10);
    obj_word = (uint)(hash_result.hi >> 32);
    if ((obj_word >> 0x10 & 1) == 0) {
        if ((obj_word >> 0xf & 1) != 0) {
            aligned_size = *size_ref;
            tag = 0xa000000000000000;
            goto l_tag_or;
        }
        if ((obj_word >> 0x11 & 1) != 0) {
            aligned_size = *size_ref;
            tag = 0x8000000000000000;
            goto l_tag_or;
        }
        if ((tag & 0xffff0000) != 0) {
            tag = *size_ref & 0x1fffffffffffffff | (tag >> 0x10) << 0x3d;
            goto l_tag_shift;
        }
        {
            uint64_t hashbuf[16] = {0};
            void *hashptr = (void *)0;
            result_lo = kernel_random_va(&hashbuf[4], 8, &hashptr, 0);     /* FUN_fffffe000b7a5cc0 */
            hash_acc = 0;
            if ((int)result_lo != 0) {
                page_off = (result_lo & 0xffffffff) << 3;
                hash_buf = (uint8_t *)&hashbuf[4];
                do {
                    hash_acc = (hash_acc + *hash_buf) * 0x401;
                    hash_acc = hash_acc ^ hash_acc >> 6;
                    page_off = page_off + -1;
                    hash_buf = hash_buf + 1;
                } while (page_off != 0);
                hash_acc = hash_acc * 9;
            }
            hash_acc = (hash_acc ^ hash_acc >> 0xb) * -0x7fff;
            tag = *size_ref & 0x1fffffffffffffff |
                  (ulong)(hash_acc + ((hash_acc & 0x3fff) / 3) * -3 + 1) << 0x3d;
            if ((hash_result.hi & 0x38000) != 0)
                goto l_tag_hi;
l_tag_shift:
            hash_acc = hash_acc >> 0xf;
        }
    } else {
        aligned_size = *size_ref;
        tag = 0xc000000000000000;
l_tag_or:
        tag = tag | aligned_size & 0x1fffffffffffffff;
l_tag_shift2:
        if ((hash_result.hi & 0x38000) == 0)
            goto l_tag_shift;
l_tag_hi:
        hash_acc = obj_word >> 0x15;
    }
    tag = tag & 0xe000000000000000 | tag & 0xfffffffffffffff | (ulong)(hash_acc & 1) << 0x3c;
l_tag_store:
    *size_ref = tag;
    if (DAT_fffffe000c5f0000 != stack_marker) {
        kernel_stack_check_panic();                                     /* FUN_fffffe000c0e0620, noreturn */
    }
    hash_result.lo = result_lo;
    return hash_result;
}

/* ================================================================== *
 * hv_zone_alloc @ 0xfffffe000b7eb624   (est. hv_zone_alloc)
 * Ghidra: void FUN_fffffe000b7eb624(undefined8 *param_1, ulong param_2)
 * Zone-queue allocation front-end: returns the zone's cached queue head,
 * or the per-CPU pool when the per-CPU slot's lock word (zone[1] +
 * cpu_index*0x4000 + 0x1c) is free and the caller did not pass the
 * 0x40 "don't pool" flag, then forwards to hv_percpu_queue_pop (b85e180,
 * recreated in hv_helpers.c). Used by hv_vm_create and kdp_init.
 * Confidence: high (complete decompile, ~15 lines)
 * Notes: per-cpu index from tpidr_el1+0x1b0; flag bit 6 (0x40) selects the
 *   shared queue.
 * Kernel code recreated for audit (hv-deps). */
extern uint64_t hv_percpu_queue_pop(long cpu, long buf, uint64_t flags);   /* FUN_fffffe000b85e180, hv_helpers.c */
extern uint64_t kernel_feature_flag(void);                             /* FUN_fffffe000b93c6c8, current-cpu/generation */

/* copyin (b95c144) / copyout (b95d6f4) callees */
extern uint64_t pan;   /* PSTATE.PAN pseudo-register (est.) */
extern void     kernel_copy(uint64_t dst, uint64_t len);   /* FUN_fffffe000b95c414: (dst, len) */
extern uint64_t kernel_copy_pan(uint64_t va, void *dst, uint64_t len);  /* FUN_fffffe000b75f890 */
extern uint64_t kernel_copy_fallback(uint64_t va, void *dst, uint64_t len); /* FUN_fffffe000b75fed8 */
extern void     kernel_copy_sentinel(uint64_t dest, uint64_t source, uint64_t len); /* FUN_fffffe000b758bd0: (dest, source, len) memcpy-style; verified by disasm — copyin x0=x20(dst), copyout x1=x20(src). de-guess name kernel_early_init is a misnomer */
extern uint64_t kernel_copyout_pan(void *src, uint64_t va, uint64_t len); /* FUN_fffffe000b75fb2c — 3 args (x0=src, x1=va, x2=len) per disasm b95d998; decompile's 4th pan_state arg is a Ghidra x8 artifact */
extern uint64_t kernel_copyout_fallback(void *src, uint64_t va, uint64_t len); /* FUN_fffffe000b76002c */
extern void     kernel_tlb_flush(void);                     /* FUN_fffffe000b96c6d4 */

void *
hv_zone_alloc(void *zone, int kind)
{
    uint64_t result;     /* r2: the queue head */
    long     cur;        /* lVar1: tpidr_el1 */

    result = *(uint64_t *)zone;
    if ((((uint)kind >> 6 & 1) == 0) &&
        (cur = tpidr_el1,
         *(int *)(((uint64_t *)zone)[1] + (ulong)*(ushort *)(cur + 0x1b0) * 0x4000 + 0x1c) == 0)) {
        result = ((uint64_t *)zone)[6];
        kind = (int)((uint)kind | 0x40);
    }
    /* the decompile renders the return as void; the caller-visible value is
     * the pop result (x0 leftover). */
    return (void *)hv_percpu_queue_pop(result, ((uint64_t *)zone)[1], kind);  /* FUN_fffffe000b85e180 */
}

/* ================================================================== *
 * kernel_kalloc @ 0xfffffe000b859c38   (est. kernel_kalloc / zalloc)
 * Ghidra: char * FUN_fffffe000b859c38(long param_1, long param_2, ulong param_3)
 * The XNU zone allocator (zalloc) core: allocates `param_2` bytes (aligned to
 * `param_3`) out of zone `param_1` (a zone header). Serves from the zone's
 * per-CPU free lists first; on exhaustion grows the zone by allocating
 * backing pages (kernel_alloc b8a6c14 for the compressor/6 case, otherwise
 * the per-type page pool at DAT_fffffe000c70be00), initializes the new
 * element descriptors, and returns the element address (or a tagged
 * "invalid"/panic on exhaustion). Used by kdp_init as
 * kernel_kalloc(&kdp_serial_zone, 0x20, 7).
 * Confidence: high (complete decompile, ~500 lines; zone machinery faithful)
 * Notes: zone-header lock b7f74d4 / b7f7538; free-list bucket table
 *   DAT_fffffe000c5abffc (0x2bad-tagged); zone table DAT_fffffe0007d800b0;
 *   element-count stats DAT_fffffe000c5fdab0; wire callback b812524;
 *   zalloc panic strings via c0e11ec; range/stack checks c0ea554/c0ea59c/
 *   c0ea708/c0ea524; page alloc/fill b8f5be0/b961544; alloc-count wrap
 *   panic b85b710/b85b334/b85b7a0/b85b7e4/b85b824.
 * Kernel code recreated for audit (hv-deps). */
void *
kernel_kalloc(long zone, long size, uint64_t align)
{
    /* zone-header fields: +0x9c free-list head, +0xa0 element free list,
     * +0xa4 per-CPU bucket index, +0xa8 count, +0x8 pages, +0x80 lock,
     * +0x38 element size, +0x3c flags, +0x84/0x8c low/high water, +0x90/0x94
     * counts, +0x98/0x9c more free lists, +0xb0 threshold */
    uint     idx;              /* z_idx: element index */
    uint     idx2;             /* uVar41: free-list index */
    long     cur;              /* t7/t8: tpidr_el1 / temp */
    long     *page_slot;       /* pg_slot: per-CPU page counter */
    ushort  *elem;             /* elem4/e6..9/elem2/elem3: element ptr */
    ulong    avail;            /* avail2: aligned size */
    ulong    base;             /* b3: page base */
    ulong    base2;            /* t1: element base */
    ulong    bits;             /* b4: used-elem bitmap */
    uint     slot;             /* slot2: free-slot count */
    bool     have_extra;       /* bVar25: extra-flag path */
    bool     have_extra2;      /* bVar23: extra-flag carry */
    uint     z_flags;          /* z_flags2: zone flags */
    uint     z_flags2;         /* r35: type flags */
    ulong    elem_count;       /* elem_cnt: element count */
    uint     elem_count_sz;    /* elem_size: element size */
    char    *zone_rec;         /* zrec: zone header */
    char    *result;           /* zret: return value */
    char    *zone_lock;        /* lock2: zone header lock */
    uint8_t  zone_fill[16];    /* zone_fill: zone-fill record */
    ulong    type_hi;          /* t5: element-count based type index */
    uint     type_ix;          /* t4: type table index */
    uint     type_word;        /* z_flags2 (reuse): zone type word */
    uint     type_sel;         /* typ: element type selector */
    uint     elem_type;        /* r34: element type tag */
    uint     elem_type2;       /* uVar17: element type tag carry */
    uint     elem_slot;        /* r21: element slot */
    uint     elem_slot2;       /* slot_ix: element slot carry */
    uint     elem_hi;          /* uVar41: element high flags */
    uint     elem_flags;       /* r4: element flag word */
    uint     flags_hi;         /* fl_hi2: flags high */
    uint     flags_ro;         /* aligned_size/f_carry: flags ro */
    uint8_t  lock_extra2;      /* bStack_10e: lock extra flag */
    uint32_t lock_extra3;      /* lock_e3 */
    uint8_t  lock_extra4;      /* lock_e4 */
    uint     count_lo, count_hi, count_a, count_a2, count_a3, count_b,
             count_c, count_d, count_e, count_e2;
    uint     want;             /* want_cur: requested element count */
    uint     want2;            /* r5: sized want */
    uint     want_sz;          /* want_sz2: element size count */
    ulong    rnd, rnd2;        /* t2/b2: random / temp */
    ulong    bits_lo, bits_hi, bits_sz;   /* b1/b3/b2: bitmap words */
    uint     rc2, pg_idx, node_id;
    uint     r3, h1, h2, result_lo, cnt_c2, cnt_d2, popcount,
             zone_tag, f_carry, r5, cnt_word, slot2, want_cur, want_sz2, count_hi2,
             slot_ix, cnt_b, elem_size;
    ulong    t1, t2, t3, typ, t4, b1, b2, t5, b3,
             avail2, t6, b4;
    long     t7, t8, saved_cur;
    char    *lock2, *zrec, *zret;
    uint32_t *head_p, *elem2;
    ushort  *e6, *e7, *e8, *e9, *elem3, *elem4;
    void    *obj_a, *obj_b, *obj_c, *st_e0, *st_f0,
             *st_c8, *st_108;
    ulong    x1_carry, x8_carry;
    long     *pg_list, *pg_slot;
    int      *piVar12;
    byte     b13, bStack_10e;
    uint64_t lock_state, st_100, st_d8;
    void    *pcStack_f8, *pcStack_d0, *pcStack_e8, *pcStack_c0;
    ushort   lock_extra;
    uint32_t lock_e3;
    uint8_t  lock_e4;
    int      in_wzr = 0;       /* zero register */

    avail = size + align & (align ^ 0xffffffffffffffff);
    kernel_zone_lock((void *)(zone + 0x80));              /* FUN_fffffe000b7f74d4 */
    do {
        idx = *(uint *)(zone + 0x9c);
        while (idx != 0) {
            t7 = (ulong)idx * 0x10;
            if (avail + *(uint *)(t7 + 4) < 0x4001) {
                /* serve from the zone's element free list */
                base = size + *(uint *)(t7 + 4) & ~align;
                *(uint *)(t7 + 4) = (int)base + (int)avail & 0xffff;
                *(short *)(t7 + 2) = *(short *)(t7 + 2) + (short)avail;
                *(int *)(zone + 0xa8) = *(int *)(zone + 0xa8) - (int)avail;
                t8 = tpidr_el1;
                page_slot = (long *)(*(long *)(zone + 8) +
                                     (ulong)*(ushort *)(t8 + 0x1b0) * 0x4000);
                *page_slot = *page_slot + avail;
                if (*(ushort *)(t7 + 2) >> 3 < 0x7ff)
                    goto l_return_elem;
                if (*(uint *)(t7 + 8) == 0) {
                    idx2 = *(uint *)(t7 + 0xc);
l_unlink_head:
                    if ((int)idx2 < 1) {
                        t8 = (ulong)idx2 * 0x10;
                        if (*(uint *)(t8 + 8) == idx) {
                            *(uint32_t *)(t8 + 8) = *(uint32_t *)(t7 + 8);
                            goto l_relink;
                        }
                    } else {
                        t8 = (ulong)idx2 * 4;
                        head_p = (uint32_t *)((uint8_t *)&DAT_fffffe000c5abffc + t8);
                        if (t8 - (int)t8 != 0) {
                            head_p = (uint32_t *)((ulong)((uint8_t *)&DAT_fffffe000c5abffc + t8) &
                                                 0xffffffffffff | 0x2bad000000000000);
                        }
                        if (*head_p == idx) {
                            *head_p = *(uint *)(t7 + 8);
l_relink:
                            *(uint64_t *)(t7 + 8) = 0;
                            idx2 = *(uint *)(zone + 0xa0);
                            *(uint *)(t7 + 8) = idx2;
                            node_id = (int)(zone + 0x1fff3a540a4U >> 2);
                            if (idx2 != 0) {
                                if (*(int *)((ulong)idx2 * 0x10 + 0xc) != node_id)
                                    goto l_grow;
                                *(uint *)((ulong)idx2 * 0x10 + 0xc) = idx;
                            }
                            *(int *)(t7 + 0xc) = node_id;
                            *(uint *)(zone + 0xa0) = idx;
l_return_elem:
                            kernel_zone_unlock((void *)(zone + 0x80));    /* FUN_fffffe000b7f7538 */
                            return (char *)((-(ulong)(idx >> 0x1f) & 0xffffc00000000000 |
                                             (ulong)idx << 0xe) + (base & 0xffff));
                        }
                    }
                } else {
                    t8 = (ulong)*(uint *)(t7 + 8) * 0x10;
                    if (*(uint *)(t8 + 0xc) == idx) {
                        idx2 = *(uint *)(t7 + 0xc);
                        *(uint *)(t8 + 0xc) = idx2;
                        goto l_unlink_head;
                    }
                }
l_grow:
                /* free list exhausted: grow the zone */
                zone_fill[0] = 0; zone_fill[8] = 0;   /* zone_fill = FUN_fffffe000c0ea554(zone) */
                zone_rec = (char *)zone;
                if (0x40a < (ulong)(zone_rec + 0x1fff39f7480) >> 7) {
                    kernel_zone_array_panic(zone_rec);          /* c0ea524, noreturn */
                }
                /* element-count based type index */
                type_hi = (long)(zone_rec + 0x1fff39f7480) * 0x1555556;
                type_ix = type_hi >> 0x20;
                z_flags = *(uint *)((uint8_t *)&DAT_fffffe0007d800b0 + type_ix * 4);
                lock_state = 0;
                cur = tpidr_el1;
                lock_extra = 0;
                lock_extra2 = 0;
                lock_extra3 = 0;
                lock_extra4 = 0;
                if ((*(ushort *)(cur + 0xc0) >> 2 & 1) == 0) {
                    have_extra = false;
                    if (((char *)0xfffffe000c60977f < zone_rec) &&
                        (zone_rec < (char *)0xfffffe000c609841)) {
                        *(ushort *)(cur + 0xc0) = *(ushort *)(cur + 0xc0) | 4;
                        lock_extra2 = 1;
                        goto l_extra_set;
                    }
                } else {
l_extra_set:
                    lock_extra = 0x101;
                    have_extra = true;
                }
                type_word = (uint32_t)(zone_fill[8] >> 32);
                elem_hi = type_word & 2;
                zone_lock = zone_rec + 0x80;
                result = zone_rec;
                saved_cur = cur;
                goto l_alloc_loop;
            }
            idx = *(uint *)(t7 + 8);
        }
        kernel_zone_fill(zone, 0);                    /* FUN_fffffe000b859e28 */
    } while (1);

l_alloc_loop:
    if ((zone_rec[0x3d] & 1U) == 0) {
        if (*(uint *)(zone_rec + 0xb0) < *(uint *)(zone_rec + 0xa8))
            goto l_zone_low;
        if (*(uint *)(zone_rec + 0x84) <= *(uint *)(zone_rec + 0x8c)) {
            if (((*(long *)(zone_rec + 0x40) == 0) || (*(long *)(zone_rec + 0x40) == 0)) ||
                (*(short *)(zone_rec + 0x7c) == 0)) {
                if ((type_word >> 0xf & 1) == 0)
                    goto l_zone_low;
            } else {
                result = (char *)kernel_zone_gc(zone_rec);     /* FUN_fffffe000b85b3a8 */
                if (((type_word >> 0xf & 1) == 0) || (((ulong)result & 1) != 0))
                    goto l_zone_low;
            }
        }
    }
    cur = *(long *)(zone_rec + 0x20);
    if (cur == 0) {
l_zone_new:
        *(uint64_t **)(zone_rec + 0x20) = &lock_state;
        head_p = (uint32_t *)(zone_rec + 0xa4);
        elem_hi = elem_hi | 0x200000;
        type_word = 0x180;
        if ((z_flags & 0x4000) != 0) {
            type_word = 0x2000180;
        }
        elem_slot = z_flags >> 8 & 7;
        elem_type = 3;
        if ((z_flags & 0xff) == 1) {
            elem_type = 1;
        }
        flags_hi = (uint)(type_hi >> 0x20);
        flags_ro = flags_hi | 0xffffb400;
        flags_hi = flags_hi | 0xffffb000;
        type_sel = avail;
        obj_c = &hv_fault_special_300;             /* DAT_fffffe000c712300 */
        elem_flags = type_word;
        if ((z_flags & 0x700) != 0x300) {
            obj_c = &hv_fault_special_800;         /* DAT_fffffe000c712800 */
            elem_flags = type_word | 0x8000000;
        }
        goto l_zone_alloc;
    }
    if ((have_extra) && ((*(byte *)(cur + 0x11) & 1) == 0)) {
        kernel_zone_lock_acquire((void *)(zone_rec + 0x20), (void *)cur);   /* FUN_fffffe000b7f9420 */
        lock_state = *(uint64_t *)(zone_rec + 0x20);
        goto l_zone_new;
    }
    if (((avail & 2) != 0) && ((*(byte *)(cur + 0x10) & 1) != 0))
        goto l_zone_low;
    *(uint *)(zone_rec + 0x3c) = *(uint *)(zone_rec + 0x3c) | 8;
    st_e0 = &DAT_fffffe000c68af18;
    st_d8 = 0x40000000;
    pcStack_d0 = (void *)0xfffffe000b7f9914;
    st_c8 = &DAT_fffffe0007d792d0;
    st_108 = &DAT_fffffe000c68af18;
    st_100 = 0x40000000;
    pcStack_f8 = (void *)0xfffffe000b7f9920;
    st_f0 = &DAT_fffffe0007d792f0;
    pcStack_e8 = zone_lock;
    pcStack_c0 = zone_lock;
    result = (char *)kernel_zone_wait((void *)(zone_rec + 0x20), *(uint64_t *)(cur + 8), 8, 0,
                                      &st_e0, &st_108);   /* FUN_fffffe000b7f973c */
    goto l_alloc_loop;

l_zone_alloc:
    if (((uint)type_sel >> 0xf & 1) == 0)
        goto l_zone_pool;
    count_lo = *(uint *)(zone_rec + 0x8c);
    count_hi = *(uint *)(zone_rec + 0x84);
    do {
        if (count_lo < count_hi) {
l_zone_pool:
            elem = (ushort *)(ulong)flags_ro;
            type_sel = (ulong)*head_p;
            node_id = (int)((ulong)(zone_rec + 0x1fff3a540a8) >> 2);
            if (*head_p == 0) {
                z_flags2 = *(uint *)((uint8_t *)&DAT_fffffe0007d800b0 + type_ix * 4);
                type_sel = (ulong)z_flags2;
                count_lo = 0x180;
                if ((z_flags2 & 0x4000) != 0) {
                    count_lo = 0x2000180;
                }
                if (((z_flags2 & 0xff) != 1) &&
                    (((z_flags2 & 0xff) != 6 || ((type_sel & 0x700) != 0x300)))) {
                    count_lo = count_lo | 0x8000000;
                }
                elem_slot2 = (z_flags2 & 0xffff) >> 8 & 7;
                if (elem_slot2 == 3) {
l_flags_16:
                    count_lo = count_lo | 0x10000;
                } else if (elem_slot2 == 2) {
                    count_lo = count_lo | 0x8000;
                } else if ((z_flags2 & 0xff) == 6)
                    goto l_flags_16;
                elem_slot2 = elem_hi;
                if (((*(uint *)(zone_rec + 0x3c) >> 8 & 1) == 0) &&
                   ((*(uint *)(zone_rec + 0x3c) & 0x1000) != 0 || (type_sel & 0xff) == 6)) {
                    elem_slot2 = elem_type2;
                }
                type_sel = type_sel & 0xff;
                elem_count = *(ushort *)(zone_rec + 0x38);
                elem_count_sz = (ulong)elem_count;
                kernel_zone_unlock(zone_lock);                  /* FUN_fffffe000b7f7538 */
                count_e = *(uint *)(zone_rec + 0x3c);
                want = 1;
                want_sz = (uint)elem_count;
                want2 = want_sz;
                if ((type_sel != 6) && ((count_e >> 6 & 1) == 0)) {
                    rnd = kernel_feature_flag();                /* FUN_fffffe000b93c6c8 */
                    want = (int)rnd + (int)(rnd / 10) * -10 + 1;
                    count_e = *(uint *)(zone_rec + 0x3c);
                    want2 = want * want_sz;
                }
                slot = 0;
                if ((count_e >> 6 & 1) == 0) {
                    slot = 0;
                    count_e = want;
                    do {
                        rnd = kernel_feature_flag();            /* FUN_fffffe000b93c6c8 */
                        if ((rnd & 0x180) == 0) {
                            slot = slot + 1;
                        }
                        count_e = count_e - 1;
                    } while (count_e != 0);
                    have_extra = (rnd & 3) == 0;
                    if ((type_sel == 6) || ((*(uint *)(zone_rec + 0x3c) >> 6 & 1) != 0))
                        goto l_flags_extra;
                    count_e = want - 1;
                    bits_sz = (ulong)count_e;
                    bits = 1L << (bits_sz & 0x3f);
                    count_a = 1;
                    if (1 < slot) {
                        count_a = slot - 1;
                        bits_lo = ~(-1L << (bits_sz & 0x3f));
                        bits_hi = bits_lo;
                        if (count_a < count_e * 3 >> 2) {
                            count_b = 0;
                            bits_hi = 0;
                            if (count_e >> 2 < count_a) {
                                bits_sz = kernel_feature_flag();
                                bits_sz = bits_sz & 0xffffffffffffffffU >>
                                          ((ulong)(0x41 - want) & 0x3f);
                                count_c = (uint)POPCOUNT(bits_sz);
                                count_d = ((count_c <= count_a) * count_a +
                                           (count_c > count_a) * count_c) -
                                          ((count_a <= count_c) * count_a +
                                           (count_a > count_c) * count_c);
                                count_b = count_e - count_c;
                                count_e2 = ((count_a <= count_b) * count_b +
                                            (count_a > count_b) * count_a) -
                                           ((count_b <= count_a) * count_b +
                                            (count_b > count_a) * count_a);
                                bits_hi = bits_lo;
                                if (count_d <= count_e2) {
                                    bits_hi = 0;
                                }
                                bits_hi = bits_hi ^ bits_sz;
                                if (count_d <= count_e2) {
                                    count_b = count_c;
                                }
                                bits_sz = (ulong)count_b;
                                goto l_bits_next;
                            }
l_bits_loop2:
                            bits_hi = bits_hi ^ bits_lo;
                            pg_idx = count_a - count_b;
                            if (pg_idx != 0) {
                                count_e = count_e - count_b;
                                do {
                                    rnd2 = (ulong)count_e;
                                    rnd = kernel_feature_flag();
                                    bits_sz = 0;
                                    if (rnd2 != 0) {
                                        bits_sz = rnd / rnd2;
                                    }
                                    rnd = rnd - bits_sz * rnd2;
                                    bits_sz = bits_hi;
                                    if (rnd != 0) {
                                        do {
                                            bits_sz = bits_sz - 1 & bits_sz;
                                            count_a = (int)rnd - 1;
                                            rnd = (ulong)count_a;
                                        } while (count_a != 0);
                                    }
                                    bits_hi = bits_sz & -bits_sz ^ bits_hi;
                                    count_e = count_e - 1;
                                    pg_idx = pg_idx + -1;
                                } while (pg_idx != 0);
                            }
                            bits_hi = bits_hi ^ bits_lo;
                        } else {
l_bits_next:
                            count_b = (uint)bits_sz;
                            pg_idx = count_b - count_a;
                            if (count_b < count_a)
                                goto l_bits_loop2;
                            for (; pg_idx != 0; pg_idx = pg_idx + -1) {
                                rnd = kernel_feature_flag();
                                bits_lo = 0;
                                if (bits_sz != 0) {
                                    bits_lo = rnd / bits_sz;
                                }
                                rnd = rnd - bits_lo * bits_sz;
                                bits_lo = bits_hi;
                                if (rnd != 0) {
                                    do {
                                        bits_lo = bits_lo - 1 & bits_lo;
                                        count_e = (int)rnd - 1;
                                        rnd = (ulong)count_e;
                                    } while (count_e != 0);
                                }
                                bits_hi = bits_lo & -bits_lo ^ bits_hi;
                                bits_sz = (ulong)((int)bits_sz - 1);
                            }
                        }
                        bits = bits_hi | bits;
                        count_a = slot;
                    }
                    slot = count_a;
                    if ((rnd & 3) == 0) {
                        slot = slot + 1;
                    }
                } else {
l_flags_extra:
                    have_extra = false;
                    bits = (ulong)(slot << (ulong)(want - 1 & 0x1f));
                }
                rnd = DAT_fffffe000c70bd68;
                count_d = slot * want_sz;
                if (type_sel == 6) {
                    elem = (ushort *)0;
                    {
                        hv_u128_t alloc_ret = kernel_alloc(DAT_fffffe0007d7ca18,
                                                           (ulong)(count_d + want2) << 0xe,
                                                           0, z_flags2 & 0x2000 | elem_slot2 |
                                                           count_lo | 0x20, 0xc, 0);  /* FUN_fffffe000b8a6c14 */
                        pg_idx = (int)alloc_ret.lo;
                        base = alloc_ret.hi;
                    }
                } else {
                    bits_sz = (ulong)(count_d + want2) * 0x4000;
                    if (DAT_fffffe000c70bd68 == 0) {
                        DAT_fffffe000c70bd68 = (ulong)*(uint *)(cur + 0x518);
                    }
                    if (rnd != 0 || hv_debug_flag != 0) {
                        lck_mtx_lock(&DAT_fffffe000c70bd60, cur, rnd, 0);   /* FUN_fffffe000b7f0afc */
                    }
                    rnd = DAT_fffffe000c70be00[type_sel * 2];
                    pg_idx = 3;
                    base = 0;
                    if (bits_sz <= DAT_fffffe000c70be08[type_sel * 2] - rnd) {
                        if ((z_flags2 >> 0xd & 1) == 0) {
                            pg_idx = 0;
                            DAT_fffffe000c70be00[type_sel * 2] = rnd + bits_sz;
                            base = rnd;
                        } else {
                            pg_idx = 0;
                            base = DAT_fffffe000c70be08[type_sel * 2] +
                                   (ulong)(count_d + want2) * -0x4000;
                            DAT_fffffe000c70be08[type_sel * 2] = base;
                        }
                    }
                    type_sel = DAT_fffffe000c70bd68;
                    rc2 = (int)DAT_fffffe000c70bd68;
                    if (DAT_fffffe000c70bd68 == *(int *)(cur + 0x518)) {
                        DAT_fffffe000c70bd68 = CONCAT44(DAT_fffffe000c70bd68_4, in_wzr);
                    }
                    elem = (ushort *)(type_sel & 0xffffffff);
                    if ((rc2 != *(int *)(cur + 0x518)) || (hv_debug_flag != 0)) {
                        lck_mtx_unlock(&DAT_fffffe000c70bd60, cur);          /* FUN_fffffe000b7f1e80 */
                    }
                }
                if (pg_idx != 0)
                    goto l_exhausted;
                rnd = base >> 10 & 0xffffffff0;
                kernel_zone_pages(base, (ulong)(count_d + want2) << 0xe);  /* FUN_fffffe000b85b844 */
                count_lo = (uint)elem_count;
                have_extra2 = false;
                if (count_lo != 0) {
                    have_extra2 = have_extra;
                }
                if (have_extra2) {
                    type_sel = 0;
                    elem_count = (ushort)flags_ro;
                    if (3 < count_lo) {
                        type_sel = elem_count_sz & 0xfffc;
                        elem = (ushort *)(rnd + 0x40);
                        bits_sz = type_sel;
                        do {
                            elem[-0x20] = elem[-0x20] & 0x800 | elem_count;
                            elem[-0x10] = elem[-0x10] & 0x800 | elem_count;
                            *elem = *elem & 0x800 | elem_count;
                            elem[0x10] = elem[0x10] & 0x800 | elem_count;
                            elem = elem + 0x40;
                            bits_sz = bits_sz - 4;
                        } while (bits_sz != 0);
                        rnd = rnd + type_sel * 0x10;
                        if (type_sel == elem_count_sz)
                            goto l_elem_fill;
                    }
                    cur = elem_count_sz - type_sel;
                    elem = (ushort *)(rnd + type_sel * 0x10);
                    do {
                        *elem = *elem & 0x800 | elem_count;
                        rnd = rnd + 0x10;
                        cur = cur + -1;
                        elem = elem + 0x10;
                    } while (cur != 0);
                }
l_elem_fill:
                elem = (ushort *)0;
                type_sel = 0;
                bits_sz = elem_count_sz & 0xfffc;
                elem = (ushort *)(ulong)want;
                do {
                    if (count_lo != 0) {
                        base2 = 1L << ((ulong)elem & 0x3f) & bits;
                        elem_count = 0;
                        if (base2 != 0) {
                            elem_count = 0x400;
                        }
                        count_a = (uint)type_sel;
                        count_b = count_a + want_sz;
                        bits_sz = (ulong)count_b;
                        elem_count = elem_count | (ushort)(type_hi >> 0x20);
                        count_c = (uint)bits_sz;
                        if ((want_sz < 4) || (rnd = bits_sz, -count_lo < count_a)) {
l_elem_loop:
                            do {
                                cur = type_sel * 0x10;
                                e6 = (ushort *)(rnd + (long)(int)cur);
                                if (cur != (int)cur) {
                                    e6 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                        0x2bad000000000000);
                                }
                                *e6 = *e6 & 0xf800 | elem_count;
                                count_a = (int)type_sel + 1;
                                type_sel = (ulong)count_a;
                            } while (count_b != count_a);
                        } else {
                            do {
                                cur = type_sel * 0x10;
                                e6 = (ushort *)(rnd + (long)(int)cur);
                                if (cur != (int)cur) {
                                    e6 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                        0x2bad000000000000);
                                }
                                pg_idx = (int)type_sel;
                                cur = (ulong)(pg_idx + 1) * 0x10;
                                e7 = (ushort *)(rnd + (long)(int)cur);
                                if (cur != (int)cur) {
                                    e7 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                        0x2bad000000000000);
                                }
                                cur = (ulong)(pg_idx + 2) * 0x10;
                                elem = (ushort *)(rnd + (long)(int)cur);
                                if (cur != (int)cur) {
                                    elem = (ushort *)(rnd + cur & 0xffffffffffff |
                                                      0x2bad000000000000);
                                }
                                cur = (ulong)(pg_idx + 3) * 0x10;
                                e8 = (ushort *)(rnd + (long)(int)cur);
                                if (cur != (int)cur) {
                                    e8 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                        0x2bad000000000000);
                                }
                                elem_count = *e7;
                                count_a2 = *elem;
                                count_a3 = *e8;
                                *e6 = *e6 & 0xf800 | elem_count;
                                *e7 = elem_count & 0xf800 | elem_count;
                                *elem = count_a2 & 0xf800 | elem_count;
                                *e8 = count_a3 & 0xf800 | elem_count;
                                type_sel = (ulong)(pg_idx + 4);
                                rnd = rnd - 4;
                            } while (rnd != 0);
                            if (count_c != want_sz) {
                                type_sel = (ulong)(count_a + count_c);
                                goto l_elem_loop;
                            }
                        }
                        type_sel = bits_sz;
                        if (base2 != 0) {
                            type_sel = (ulong)(count_b + want_sz);
                            elem_count = (ushort)flags_hi;
                            if ((3 < want_sz) && (count_b <= -count_lo)) {
                                base2 = 0;
                                do {
                                    count_a = count_b + (int)base2;
                                    cur = (ulong)count_a * 0x10;
                                    e6 = (ushort *)(rnd + (long)(int)cur);
                                    if (cur != (int)cur) {
                                        e6 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                            0x2bad000000000000);
                                    }
                                    cur = (ulong)(count_a + 1) * 0x10;
                                    e7 = (ushort *)(rnd + (long)(int)cur);
                                    if (cur != (int)cur) {
                                        e7 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                            0x2bad000000000000);
                                    }
                                    cur = (ulong)(count_a + 2) * 0x10;
                                    e8 = (ushort *)(rnd + (long)(int)cur);
                                    if (cur != (int)cur) {
                                        e8 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                            0x2bad000000000000);
                                    }
                                    cur = (ulong)(count_a + 3) * 0x10;
                                    e9 = (ushort *)(rnd + (long)(int)cur);
                                    if (cur != (int)cur) {
                                        e9 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                            0x2bad000000000000);
                                    }
                                    count_a = *e7;
                                    count_a2 = *e9;
                                    count_a3 = *e8 & 0xc00 | flags_hi;
                                    elem = (ushort *)(ulong)count_a3;
                                    *e6 = *e6 & 0xc00 | elem_count;
                                    *e7 = count_a & 0xc00 | elem_count;
                                    *e8 = (ushort)count_a3;
                                    *e9 = count_a2 & 0xc00 | elem_count;
                                    base2 = base2 + 4;
                                } while (bits_sz != base2);
                                if (count_c == want_sz)
                                    goto l_elem_done;
                                bits_sz = (ulong)(count_b + count_c);
                            }
                            do {
                                cur = bits_sz * 0x10;
                                e6 = (ushort *)(rnd + (long)(int)cur);
                                if (cur != (int)cur) {
                                    e6 = (ushort *)(rnd + cur & 0xffffffffffff |
                                                        0x2bad000000000000);
                                }
                                *e6 = *e6 & 0xc00 | elem_count;
                                count_c = (int)bits_sz + 1;
                                bits_sz = (ulong)count_c;
                            } while (count_b + want_sz != count_c);
                        }
                    }
l_elem_done:
                    elem = (ushort *)((long)elem + 1);
                } while (elem != (ushort *)(ulong)want);
                if (slot != 0) {
                    DAT_fffffe000c5fdab0 = DAT_fffffe000c5fdab0 + (ulong)count_d;
                }
                if (DAT_fffffe000c5b23f8 < '\0') {
                    kernel_zone_count(zone_rec, rnd, want, want2, elem_count_sz, bits);  /* FUN_fffffe000b85b9d0 */
                    type_sel = (ulong)*(uint *)(zone_rec + 0xa4);
                } else {
                    kernel_zone_lock(zone_lock);                /* FUN_fffffe000b7f74d4 */
                    elem = (ushort *)0;
                    bits_sz = 0;
                    type_sel = (ulong)*head_p;
                    do {
                        cur = (bits_sz & 0xffffffff) * 0x10;
                        base = rnd + (long)(int)cur;
                        if (cur - (int)cur != 0) {
                            base = rnd + cur & 0xffffffffffff | 0x2bad000000000000;
                        }
                        *(int *)(base + 8) = (int)type_sel;
                        if (type_sel != 0) {
                            if (*(int *)(type_sel * 0x10 + 0xc) != node_id)
                                goto l_alloc_assert;
                            *(int *)(type_sel * 0x10 + 0xc) = (int)(base >> 4);
                        }
                        *(int *)(base + 0xc) = node_id;
                        type_sel = base >> 4 & 0xffffffff;
                        *head_p = (uint)(base >> 4);
                        base2 = elem_count_sz;
                        if ((bits >> ((ulong)elem & 0x3f) & 1) == 0) {
                            base2 = 0;
                        }
                        bits_sz = (bits_sz & 0xffffffff) + elem_count_sz + base2;
                        elem = (ushort *)((long)elem + 1);
                    } while ((ushort *)(ulong)want != elem);
                    if ((*(uint *)(zone_rec + 0x3c) & 0x40) != 0) {
                        want2 = want;
                    }
                    *(uint *)(zone_rec + 0x94) = want2 + *(int *)(zone_rec + 0x94);
                }
            }
            elem = (ushort *)(type_sel * 0x10);
            if (&DAT_fffffe000c608b80 + ((ulong)*elem & 0x3ff) * 0xc0 != (ulong)zone_rec)
                goto l_alloc_assert2;
            count_lo = 0;
            if (*(uint *)(elem + 4) != 0) {
                cur = (ulong)*(uint *)(elem + 4) * 0x10;
                if (*(uint *)(cur + 0xc) == type_sel) {
                    *(uint32_t *)(cur + 0xc) = *(uint32_t *)(elem + 6);
                    count_lo = *(uint *)(elem + 4);
                    goto l_zone_relink;
                }
                goto l_alloc_assert3;
            }
l_zone_relink:
            elem_count = 0;
            *head_p = count_lo;
            elem[4] = 0;
            elem[5] = 0;
            elem[6] = 0;
            elem[7] = 0;
            type_sel = -(type_sel >> 0x1f) & 0xffffc00000000000 | type_sel << 0xe;
            elem = (ushort *)elem;
            if ((*elem & 0xf000) != 0xe000)
                goto l_zone_commit;
            count_hi = (byte)elem[1];
            elem_count = (ulong)count_hi;
            elem = elem + count_hi * -8;
            if (((ulong)elem & 0xffc0000000000000) != 0) {
                elem = (ushort *)((ulong)elem & 0xffffffffffff | 0xc8a2000000000000);
            }
            count_lo = elem[1] + 0x8000;
            elem[1] = (ushort)count_lo;
            if (count_lo >> 0x10 == 0) {
                type_sel = type_sel + count_hi * -0x4000;
                if ((count_lo & 0xffff) != 0x8000) {
l_zone_commit:
                    kernel_zone_unlock(zone_lock);                  /* FUN_fffffe000b7f7538 */
                    count_hi = (uint)*(ushort *)(zone_rec + 0x38);
                    count_lo = count_hi;
                    if (((byte)zone_rec[0x3c] >> 6 & 1) == 0) {
                        count_lo = (uint)*(ushort *)(zone_rec + 0x34) +
                                   (uint)*(ushort *)(zone_rec + 0x36) + 0x3fff >> 0xe;
                    }
                    if (DAT_fffffe000c5b23f0 <= DAT_fffffe000c5fdaa8) {
                        kernel_zone_trace(zone_rec, count_lo);      /* FUN_fffffe000b85bbb0 */
                        count_hi = (uint)*(ushort *)(zone_rec + 0x38);
                    }
                    elem = (ushort *)0;
                    page_slot = (long *)0;
                    count_c = (uint)elem_count;
                    if (count_c != count_hi) {
                        pg_idx = 0;
                        page_slot = (long *)0;
                        elem = (ushort *)0;
                        do {
                            if (((z_flags & 0xff) == 1) ||
                               ((t3 = 0x20002, (z_flags & 0xff) == 6 &&
                                ((z_flags & 0x700) == 0x300)))) {
                                t3 = 2;
                            }
                            pg_list = (long *)kernel_page_alloc2(t3);   /* FUN_fffffe000b8f5be0 */
                            count_hi = (uint)elem;
                            if (pg_list == (long *)0) {
                                if ((count_lo <= count_hi) &&
                                   ((pg_idx != 0 || (DAT_fffffe000c67f9b0 <= DAT_fffffe000c649450))))
                                    break;
                                if ((avail & 2) != 0) {
                                    kernel_queue_free_walk(page_slot, 0);       /* FUN_fffffe000b8f6e54 */
                                    if (count_hi != 0) {
                                        elem = (ushort *)elem;
                                        kernel_page_trace(*(uint64_t *)(cur + 0x4e8),
                                                          DAT_fffffe0007e0c9a8, elem);  /* FUN_fffffe000b7eda24 */
                                        *(long *)(PTR_DAT_fffffe000c5c89f8 +
                                                  (ulong)*(ushort *)(cur + 0x1b0) * 0x4000) =
                                             *(long *)(PTR_DAT_fffffe000c5c89f8 +
                                                      (ulong)*(ushort *)(cur + 0x1b0) * 0x4000) +
                                             (long)elem;
                                    }
                                    kernel_zone_unlock(zone_lock);          /* FUN_fffffe000b7f74d4 */
                                    result = zone_lock;     /* decompiler: zret = (char *)unlock (x0 leftover) */
                                    if (((((*(uint *)(zone_rec + 0x3c) & 0x802) == 0) &&
                                         (*(uint *)(zone_rec + 0x8c) < *(uint *)(zone_rec + 0x84))) &&
                                        (0x11 < hv_fault_boot_threshold)) &&
                                       ((DAT_fffffe000c649450 < DAT_fffffe000c67f9b0 ||
                                        (((char *)0xfffffe000c60977f < zone_rec &&
                                         (zone_rec < (char *)0xfffffe000c609841)))))) {
                                        *(uint *)(zone_rec + 0x3c) = *(uint *)(zone_rec + 0x3c) | 2;
                                        result = (char *)kernel_zone_callback(&DAT_fffffe000c70c130, 0);  /* FUN_fffffe000b8462e0 */
                                    }
                                    if (count_c != 0) {
                                        z_flags = elem[1] - 0x8000;
                                        elem[1] = (ushort)z_flags;
                                        if ((z_flags & 0xffff0000) != 0)
                                            goto l_alloc_assert4;
                                        if ((z_flags & 0xffff) == 0) {
                                            pg_idx = (int)((ulong)elem >> 4);
                                            if (*(uint *)(elem + 4) == 0) {
                                                z_flags = *(uint *)(elem + 6);
                                            } else {
                                                cur = (ulong)*(uint *)(elem + 4) * 0x10;
                                                if (*(int *)(cur + 0xc) != pg_idx)
                                                    goto l_alloc_assert5;
                                                z_flags = *(uint *)(elem + 6);
                                                *(uint *)(cur + 0xc) = z_flags;
                                            }
                                            if ((int)z_flags < 1) {
                                                cur = (ulong)z_flags * 0x10;
                                                if (*(int *)(cur + 8) != pg_idx)
                                                    goto l_alloc_assert5;
                                                *(uint32_t *)(cur + 8) = *(uint32_t *)(elem + 4);
                                            } else {
                                                cur = (ulong)z_flags * 4;
                                                piVar12 = (int *)((uint8_t *)&DAT_fffffe000c5abffc + cur);
                                                if (cur - (int)cur != 0) {
                                                    piVar12 = (int *)((ulong)((uint8_t *)&DAT_fffffe000c5abffc + cur) &
                                                                     0xffffffffffff | 0x2bad000000000000);
                                                }
                                                if (*piVar12 != pg_idx)
                                                    goto l_alloc_assert5;
                                                *piVar12 = *(int *)(elem + 4);
                                            }
                                            elem[4] = 0;
                                            elem[5] = 0;
                                            elem[6] = 0;
                                            elem[7] = 0;
                                            z_flags = *(uint *)(zone_rec + 0x98);
                                            *(uint *)(elem + 4) = z_flags;
                                            pg_idx = (int)((ulong)(zone_rec + 0x1fff3a5409c) >> 2);
                                            if (z_flags != 0) {
                                                if (*(int *)((ulong)z_flags * 0x10 + 0xc) != pg_idx)
                                                    goto l_alloc_assert5;
                                                *(int *)((ulong)z_flags * 0x10 + 0xc) =
                                                    (int)((ulong)elem >> 4);
                                            }
                                            *(int *)(elem + 6) = pg_idx;
                                            *(int *)(zone_rec + 0x98) = (int)((ulong)elem >> 4);
                                            *(uint *)(zone_rec + 0x90) =
                                                *(int *)(zone_rec + 0x90) + count_c;
                                        }
                                    }
                                    elem = (ushort *)(elem + elem_count * 8);
                                    z_flags = *head_p;
                                    *(uint *)(elem + 4) = z_flags;
                                    if (z_flags != 0) {
                                        if (*(int *)((ulong)z_flags * 0x10 + 0xc) != node_id)
                                            goto l_alloc_assert;
                                        *(int *)((ulong)z_flags * 0x10 + 0xc) =
                                            (int)((ulong)elem >> 4);
                                    }
                                    *(int *)(elem + 6) = node_id;
                                    *head_p = (uint)((ulong)elem >> 4);
                                    goto l_zone_ret;
                                }
                                if ((lock_extra & 1) == 0) {
                                    kernel_zone_unlock(zone_lock);          /* FUN_fffffe000b7f7538 */
                                    if ((*(uint *)(zone_rec + 0x3c) >> 3 & 1) != 0) {
                                        *(uint *)(zone_rec + 0x3c) = *(uint *)(zone_rec + 0x3c) & 0xfffffff7;
                                        elem = (ushort *)0x2;
                                        kernel_zone_wake((void *)(zone_rec + 0x20), 0, 2, 0, 0);   /* FUN_fffffe000b7fa7b8 */
                                    }
                                    lock_extra = (uint16_t)(lock_extra & 0xff00) | 1;
                                    kernel_zone_unlock(zone_lock);          /* FUN_fffffe000b7f7538 */
                                }
                                pg_idx = pg_idx + 1;
                                kernel_page_wait(0);                        /* FUN_fffffe000b8f671c */
                            } else {
                                *pg_list = (long)page_slot;
                                elem = (ushort *)(ulong)(count_hi + 1);
                                elem = (ushort *)0;
                                kernel_zone_page_zero((ulong)*(uint *)(pg_list + 6) << 0xe, 0x4000);  /* FUN_fffffe000b961544 */
                                page_slot = pg_list;
                            }
                        } while ((uint)elem < *(ushort *)(zone_rec + 0x38) - count_c);
                    }
                    z_flags = z_flags & 0xff;
                    count_lo = elem_hi | 0x8000000;
                    if (z_flags == 6) {
                        count_lo = elem_flags;
                    }
                    obj_a = &hv_fault_special_800;
                    if (z_flags == 6) {
                        obj_a = obj_c;
                    }
                    want = elem_hi;
                    if (z_flags != 1) {
                        want = count_lo;
                    }
                    obj_b = &hv_fault_special_300;
                    if (z_flags != 1) {
                        obj_b = obj_a;
                    }
                    if (obj_b == (void *)DAT_fffffe000c605258) {
                        DAT_fffffe000c60524c = DAT_fffffe000c60524c + 1;
                        DAT_fffffe000c5f405c = DAT_fffffe000c5f405c + 1;
                        kernel_vm_wire_callback((uint64_t)0xfffffe000b7f23d0, 0,
                                                DAT_fffffe000c5b04f0, 1000);   /* FUN_fffffe000b812524 */
                        kernel_lock_flush_ack(0, 0, 0);                         /* FUN_fffffe000b812f5c */
                    }
                    kernel_map_ref((uint64_t)obj_b + 8);                      /* FUN_fffffe000b7f62e8 */
                    if (elem_slot == 3) {
l_zone_flags16:
                        want = want | 0x10000;
                    } else if (elem_slot == 2) {
                        want = want | 0x8000;
                    } else if ((z_flags & 0xff) == 6)
                        goto l_zone_flags16;
                    if (((*(uint *)(zone_rec + 0x3c) >> 8 & 1) != 0) ||
                       ((count_lo = elem_type2, (z_flags & 0xff) != 6 &&
                        ((*(uint *)(zone_rec + 0x3c) >> 0xc & 1) == 0)))) {
                        count_lo = elem_hi;
                    }
                    zone_tag = 0x19;
                    if (*(uint8_t *)((uint8_t *)&DAT_fffffe0007d800b0 + type_ix * 4) != '\x01') {
                        zone_tag = 0x23;
                    }
                    r3 = 0xb;
                    if (*(uint8_t *)((uint8_t *)&DAT_fffffe0007d800b0 + type_ix * 4) != '\x06') {
                        r3 = zone_tag;
                    }
                    kernel_phys_enter(obj_b, type_sel + (count_c << 0xe),
                                      type_sel + (count_c << 0xe), (long)elem << 0xe,
                                      page_slot, want | count_lo | z_flags & 0x2000,
                                      0xc, elem_type, r3);                   /* FUN_fffffe000b8a756c */
                    if ((int)elem != 0) {
                        kernel_page_trace(*(uint64_t *)(cur + 0x4e8),
                                          DAT_fffffe0007e0c9a8, elem);          /* FUN_fffffe000b7eda24 */
                        *(long *)(PTR_DAT_fffffe000c5c89f8 +
                                  (ulong)*(ushort *)(cur + 0x1b0) * 0x4000) =
                             *(long *)(PTR_DAT_fffffe000c5c89f8 +
                                      (ulong)*(ushort *)(cur + 0x1b0) * 0x4000) +
                             (long)elem;
                    }
                    result = (char *)kernel_zone_finalize(zone_rec, type_sel, 0,
                                                          elem_count, (int)elem + count_c, 0);  /* FUN_fffffe000b85be14 */
                    type_sel = avail & 0xffffffff;
                    goto l_zone_ret2;
                }
                pg_idx = (int)((ulong)elem >> 4);
                if (*(uint *)(elem + 4) == 0) {
                    base2 = (ulong)*(uint *)(elem + 6);
                    if (0 < (int)*(uint *)(elem + 6))
                        goto l_free_bucket;
l_free_head:
                    if (*(int *)(base2 * 0x10 + 8) != pg_idx)
                        goto l_alloc_assert5;
                    *(uint32_t *)(base2 * 0x10 + 8) = *(uint32_t *)(elem + 4);
l_free_relink:
                    elem[4] = 0;
                    elem[5] = 0;
                    elem[6] = 0;
                    elem[7] = 0;
                    count_lo = *(uint *)(zone_rec + 0x9c);
                    *(uint *)(elem + 4) = count_lo;
                    pg_idx = (int)((ulong)(zone_rec + 0x1fff3a540a0) >> 2);
                    if (count_lo != 0) {
                        if (*(int *)((ulong)count_lo * 0x10 + 0xc) != pg_idx)
                            goto l_alloc_assert5;
                        *(int *)((ulong)count_lo * 0x10 + 0xc) = (int)((ulong)elem >> 4);
                    }
                    *(int *)(elem + 6) = pg_idx;
                    *(int *)(zone_rec + 0x9c) = (int)((ulong)elem >> 4);
                    count_lo = *(uint *)(zone_rec + 0x90);
                    *(uint *)(zone_rec + 0x90) = count_lo - count_hi;
                    if (count_lo < count_hi) {
                        cur = (long)kernel_zone_wrap(zone_rec, "z_wired_empty wrap-around");  /* FUN_fffffe000c0ea758 */
                        if (0x40a < cur + 0x1fff39f7480U >> 7) {
                            kernel_zone_array_panic((void *)0);                 /* c0ea524, noreturn */
                        }
                        z_flags = *(uint *)((uint8_t *)&DAT_fffffe0007d800b0 +
                                          ((cur + 0x1fff39f7480U) * 0x1555556 >> 0x1e & 0x3fffffffc)) >>
                                  8 & 7;
                        if (4 < z_flags) {
                            return "invalid";
                        }
                        return (void *)PTR_DAT_fffffe0007d7c9f0[z_flags];
                    }
                    goto l_zone_commit;
                }
                cur = (ulong)*(uint *)(elem + 4) * 0x10;
                if (*(int *)(cur + 0xc) == pg_idx) {
                    count_lo = *(uint *)(elem + 6);
                    base2 = (ulong)count_lo;
                    *(uint *)(cur + 0xc) = count_lo;
                    if ((int)count_lo < 1)
                        goto l_free_head;
l_free_bucket:
                    cur = base2 * 4;
                    piVar12 = (int *)((uint8_t *)&DAT_fffffe000c5abffc + cur);
                    if (cur - (int)cur != 0) {
                        piVar12 = (int *)((ulong)((uint8_t *)&DAT_fffffe000c5abffc + cur) &
                                         0xffffffffffff | 0x2bad000000000000);
                    }
                    if (*piVar12 == pg_idx) {
                        *piVar12 = *(int *)(elem + 4);
                        goto l_free_relink;
                    }
                }
                goto l_alloc_assert5;
            }
            goto l_alloc_assert4;
        }
        result = (char *)kernel_zone_gc(zone_rec);              /* FUN_fffffe000b85b5e4 */
l_zone_ret2:
        if (((zone_rec[0x3d] & 1U) != 0) || (*(uint *)(zone_rec + 0xb0) < *(uint *)(zone_rec + 0xa8)))
            goto l_zone_ret;
        count_lo = *(uint *)(zone_rec + 0x8c);
        count_hi = *(uint *)(zone_rec + 0x84);
        if (count_lo < count_hi)
            goto l_zone_alloc;
        if (((*(long *)(zone_rec + 0x40) != 0) && (*(long *)(zone_rec + 0x40) != 0)) &&
            (*(short *)(zone_rec + 0x7c) != 0))
            break;
        if (((uint)type_sel >> 0xf & 1) == 0)
            goto l_zone_ret;
    } while (1);
    result = (char *)kernel_zone_gc(zone_rec);                  /* FUN_fffffe000b85b3a8 */
    if ((((uint)type_sel >> 0xf & 1) == 0) || (((ulong)result & 1) != 0)) {
l_zone_ret:
        if (*(uint64_t **)(zone_rec + 0x20) == &lock_state) {
            *(uint64_t *)(zone_rec + 0x20) = lock_state;
            z_flags = *(uint *)(zone_rec + 0x3c);
        } else {
            **(uint64_t **)(zone_rec + 0x20) = 0;
            z_flags = *(uint *)(zone_rec + 0x3c);
        }
        if ((z_flags >> 3 & 1) != 0) {
            *(uint *)(zone_rec + 0x3c) = z_flags & 0xfffffff7;
            kernel_zone_wake((void *)(zone_rec + 0x20), 0, 2, 0, 0);   /* FUN_fffffe000b7fa7b8 */
            result = zone_rec;    /* decompiler: zret = (char *)wake (x0 leftover) */
        }
l_zone_low:
        if ((lock_extra2 & 1) != 0) {
            *(ushort *)(saved_cur + 0xc0) = *(ushort *)(saved_cur + 0xc0) & 0xfffb;
        }
        return result;
    }
    goto l_zone_alloc;
l_alloc_assert:
    kernel_zone_array_panic2(zone_rec);                         /* FUN_fffffe000c0ea554 */
    type_sel = x8_carry;
l_alloc_assert2:
    kernel_zone_array_panic3(zone_rec, -(type_sel >> 0x1f & 1) & 0xffffc00000000000 |
                             (type_sel & 0xffffffff) << 0xe);  /* FUN_fffffe000c0ea59c */
l_alloc_assert3:
    kernel_zone_array_panic2(zone_rec, elem);                   /* FUN_fffffe000c0ea554 */
l_alloc_assert5:
    kernel_zone_array_panic2(zone_rec, elem);                   /* FUN_fffffe000c0ea554 */
l_alloc_assert4:
    kernel_zone_array_panic4(zone_rec, elem, "alloc_count wrap-around");  /* FUN_fffffe000c0ea708 */
l_exhausted:
    st_e0 = (void *)0;
    t3 = kernel_zone_debug1(&st_e0);                   /* FUN_fffffe000b85b710 */
    kernel_zone_debug2(zone_rec);                               /* FUN_fffffe000b85b334 */
    kernel_zone_debug2((void *)t3);                              /* FUN_fffffe000b85b334 */
    obj_c = st_e0;
    kernel_zone_debug3(st_e0);                             /* FUN_fffffe000b85b7a0 */
    kernel_zone_debug4(obj_c);                                /* FUN_fffffe000b85b7e4 */
    kernel_zone_debug5(t3);                                 /* FUN_fffffe000b85b824 */
    kernel_panic_msg_fmt(
        "zalloc[%d]: zone map exhausted while allocating from zone [%s%s], likely due to memory leak in zone [%s%s] (%u%c, %d elements allocated) @%s:%d");
}

/* ================================================================== *
 * kernel_mem_validate @ 0xfffffe000b8b51c8   (est. kernel_mem_validate / vm_map_enter)
 * Ghidra: ulong FUN_fffffe000b8b51c8(long param_1, ulong *param_2, ulong param_3,
 *          undefined8 param_4, ulong param_5, long param_6, ulong param_7,
 *          ulong param_8, uint *param_9, uint *param_10, uint param_11)
 * The 11-argument vm_map_enter entry: enters the range [va, va+len) into the
 * target map (param_6) with the given protection/flag word, creating the map
 * entries and objects (the "block" from kernel_alloc is param_7 = the
 * caller-supplied VA). On success writes the mapped VA to *param_2 and the
 * resulting protection words to *param_9/*param_10. Returns 0 on success or a
 * KERN_* error. Called by kernel_alloc/kernel_copyout/hv.c/hv_vcpu.c.
 * Confidence: high (complete decompile, ~180 lines)
 * Notes: callees b9152dc (map check), b8abdc4 (map enter int), b8b2b60
 *   (map enter sub), b8acc64 (enter done), b7f62e8 (map ref), b8adeb4 /
 *   b8af720 (enter loop), b8c6d70 / b8c6db8 (entry commit), b86659c (cs
 *   check), bf48bc8 (jit downgrade), b915978 (entry link), b91600c (vm sync),
 *   b7f6aac (map unref), b8a9e4c (obj batch). "vm_remap ... VM_PROT_COPY
 *   denied" and "%s: downgrade JIT for entry [%p, %p)" panic strings.
 * Kernel code recreated for audit (hv-deps). */
int
kernel_mem_validate(void *vm, void *map_out_arg, uint64_t len, uint64_t prot,
                    uint32_t flags32, uint64_t x, uint64_t block, int z,
                    int *out1_arg, int *out2_arg, int k)
{
    uint64_t map = (uint64_t)vm;           /* param_1 */
    uint64_t *map_out = (uint64_t *)map_out_arg;   /* param_2 */
    uint64_t param4 = prot;                /* param_4 */
    uint64_t flags = (uint64_t)flags32;    /* param_5 */
    uint64_t map2 = x;                     /* param_6 */
    uint64_t va = block;                   /* param_7 */
    uint64_t param8 = (uint64_t)z;         /* param_8 */
    uint32_t *out1 = (uint32_t *)out1_arg; /* param_9 */
    uint32_t *out2 = (uint32_t *)out2_arg; /* param_10 */
    uint32_t depth = (uint32_t)k;          /* param_11 */
    uint     f_word;           /* uVar1: flags-word carry */
    uint     f_lo;             /* uVar10: flags low */
    uint     f_hi;             /* obj_slot_word: flags high */
    ushort   shift1;           /* r3: map shift */
    ushort   shift2;           /* r4: map2 shift */
    long     entry;            /* lVar5: created entry (entry2) */
    uint     rc;               /* uVar6: status */
    ulong    va_end;           /* uVar7: range end */
    uint64_t x1;             /* prot_word: register carry */
    long     cur;              /* page_off: tpidr_el1 */
    ulong    va_start;         /* prot_ro2/h2: aligned start */
    ulong    va_mask;          /* result_lo: original va */
    uint64_t *pmap;            /* puVar17 */
    ulong    va_hi;            /* cnt_c2 */
    ulong    enter_flags;      /* cnt_d2/r22 */
    void *obj_p;        /* object ptr */
    long     *ent;             /* plVar21: list entry */
    long     *list_head;       /* plVar23 */
    ulong    out_b8;         /* sub out */
    uint8_t  auStack_b0[8];    /* sub out bytes */
    long     out_a8;         /* sub out */
    long     out_a0;         /* entry out */
    uint64_t *obj_list;      /* batch list */
    uint64_t **obj_tail;     /* &obj_list */
    long     entry2;         /* entry */
    uint64_t out_word;       /* CONCAT44 out */
    long     off;         /* offset */
    uint64_t off2;      /* offset2 */
    uint64_t va_end2;          /* aligned end (uVar7 companion) */
    uint64_t x1_carry2 = 0;  /* Ghidra x1_carry2 post-call register */
    uint64_t x1_carry = 0;     /* Ghidra x1_carry post-call register */

    off = 0;
    off2 = 0;
    obj_tail = &obj_list;
    obj_list = (uint64_t *)0;
    if (((map != 0) && (map2 != 0)) && (depth < 3)) {
        shift1 = *(ushort *)(map + 0x44);
        va_mask = *map_out;
        f_lo = *out1;
        f_hi = *out2;
        if ((f_lo < 8) && (out_word = CONCAT44(f_lo, f_hi), f_hi < 8)) {
            f_hi = -1 << (ulong)(*(ushort *)(map2 + 0x44) & 0x1f);
            f_word = f_hi;
            if ((f_lo & (f_hi ^ 0xffffffff)) != 0) {
                out_word = 0;
                va_end = kernel_map_check(&DAT_fffffe0007d81228, f_lo, f_hi, 0,
                                          (long)&out_word + 4, (uint64_t)&out_word);  /* FUN_fffffe000b9152dc */
                if ((int)va_end != 0) {
                    if ((int)va_end == 0x20000001) {
                        return 0;
                    }
                    return va_end;
                }
                f_word = -1 << (ulong)(*(ushort *)(map2 + 0x44) & 0x1f);
            }
            if (len != 0) {
                va_end = (ulong)~f_word;
                va_start = va & (va_end ^ 0xffffffffffffffff);
                va_end2 = va_start;
                if ((flags & 0x100000) != 0) {
                    va_end2 = va;
                }
                if ((!CARRY8(va_end2, len)) &&
                   (va_hi = va_end2 + len + va_end & ~va_end, va_end = va_hi - va_start,
                    va_start <= va_hi && va_end != 0)) {
                    shift2 = *(ushort *)(map + 0x44);
                    va_hi = va_end;
                    if ((flags & 0x100000) != 0) {
                        va_hi = len;
                    }
                    if ((((uint)flags >> 6 & 1) == 0) || ((int)param8 != 0)) {
                        va_end = 0x2000000000000;
                        if (map2 != map) {
                            va_end = 0;
                        }
                        pmap = *(uint64_t **)(map + 0x58);
                        if (pmap == (uint64_t *)0) {
                            va_mask = 0;
                        } else {
                            va_mask = 0x80000000000000;
                            if (pmap != &hv_kernel_map_sentinel) {   /* DAT_fffffe000c62b698 */
                                va_mask = 0;
                            }
                        }
                        entry2 = 0;
                        enter_flags = va_end | flags & 0xfe7dffffffffffff | va_mask;
                        va_start = kernel_map_enter_int((void *)map2, va_start, va_end, param8,
                                                        &entry2,
                                                        (uint64_t *)((long)&out_word + 4),
                                                        &out_word, depth, enter_flags);  /* FUN_fffffe000b8abdc4 */
                        entry = entry2;
                        if ((int)va_start != 0) {
                            return va_start;
                        }
                        va_hi = -1L << ((ulong)shift1 & 0x3f);
                        va_start = va & va_end & (long)(flags << 0x2b) >> 0x3f;
                        if (map2 == map) {
                            va_end = enter_flags | 0x1e7dffffffffffff |
                                     (ulong)*(byte *)(entry + 4) << 0x3d;
                        } else {
                            va_end = enter_flags | 0xc000000000000000;
                            if (flags >> 0x3d != 0 || map != 0) {
                                va_end = enter_flags;
                            }
                        }
                        f_lo = (uint)va_hi;
                        if (f_word != f_lo) {
                            out_b8 = 0;
                            out_a8 = 0;
                            out_a0 = entry;
                            va_end = kernel_map_enter_sub((void *)entry, va_start, va_hi,
                                                          (uint64_t)map, param8 & 0xffffffff,
                                                          &out_a0, (uint64_t *)&out_a8,
                                                          auStack_b0, &out_b8);  /* FUN_fffffe000b8b2b60 */
                            if ((int)va_end != 0) {
                                kernel_map_enter_done((void *)entry);   /* FUN_fffffe000b8acc64 */
                                return va_end;
                            }
                            if (out_b8 != 0) {
                                va_start = ((out_b8 <= va_start) * va_start +
                                            (out_b8 > va_start) * out_b8) - out_b8;
                            }
                            va_start = va_start + out_a8;
                            va_end = *(ulong *)(out_a0 + 0x10);
                        }
                        va_hi = va_end + ~f_lo & va_hi;
                        if (va_hi != 0) {
                            pmap = *(uint64_t **)(map + 0x58);
                            if ((((pmap != (uint64_t *)0) && (0x7fffc000 < va_hi)) &&
                                (pmap == &hv_kernel_map_sentinel)) && ((enter_flags >> 0x34 & 1) == 0)) {
                                kernel_map_enter_done((void *)entry);
                                return 3;
                            }
                            va_end = -1L << ((ulong)shift2 & 0x3f);
                            kernel_map_ref(map);                    /* FUN_fffffe000b7f62e8 */
                            f_lo = (uint)enter_flags;
                            if ((enter_flags & 1) == 0) {
                                rc = kernel_map_enter_loop((void *)map, va_mask & va_end, va_hi, param4,
                                                           enter_flags, &off);   /* FUN_fffffe000b8adeb4 */
                            } else {
                                rc = kernel_map_enter_loop2((void *)map, va_mask & va_end, va_hi, param4,
                                                            enter_flags, &off, &obj_list);  /* FUN_fffffe000b8af720 */
                            }
                            entry = entry2;
                            if (rc == 0) {
                                list_head = (long *)(entry + 0x18);
                                ent = (long *)*list_head;
                                while (ent != list_head) {
                                    kernel_map_entry_commit((void *)entry, ent);   /* FUN_fffffe000b8c6d70 */
                                    x1 = x1_carry;
                                    if ((enter_flags >> 0x2a & 1) == 0) {
                                        f_hi = *(uint *)(ent + 7);
l_prot_check:
                                        if ((f_lo >> 5 & 1) == 0)
                                            goto l_flags_done;
l_set_flags:
                                        f_word = f_hi & 0xfdff847f | 0x2000880;
                                        *(uint *)(ent + 7) = f_word;
                                        f_word = f_hi & 0x400000;
                                    } else {
                                        f_hi = *(uint *)(ent + 7);
                                        if (((f_hi >> 0x13 & 1) != 0) &&
                                           ((((f_hi >> 0xd & 1) == 0 || (DAT_fffffe0007e31d90 == (uint8_t *)0)) ||
                                            ((*DAT_fffffe0007e31d90 & 1) == 0)))) {
                                            kernel_vm_cs_check(0, 0, 0);        /* FUN_fffffe000b86659c */
                                            x1 = tpidr_el1;
                                            x1 = per_cpu_get((void *)x1);
                                            cur = (long)current_task(0);
                                            if (cur != 0) {
                                                current_task((void *)x1);
                                            }
                                            kernel_boot_misc_o(
                                                "%d[%s] vm_remap(0x%llx,0x%llx) VM_PROT_COPY denied on permanent mapping prot 0x%x/0x%x developer %d\n");
                                            x1 = ent[2];
                                            f_hi = *(uint *)(ent + 7);
                                            goto l_prot_check;
                                        }
                                        *(uint *)(ent + 7) = f_hi | 0x1000;
                                        f_hi = *(uint *)(ent + 7);
                                        if ((f_lo >> 5 & 1) != 0)
                                            goto l_set_flags;
l_flags_done:
                                        f_word = f_hi >> 0x16 & 1;
                                        f_hi = f_hi;
                                    }
                                    if (((f_word != 0) && ((enter_flags >> 0x2a & 1) == 0)) &&
                                       ((*(uint *)(map + 0xb0) & 0x8800) != 0)) {
                                        kernel_vm_jit_downgrade(&MACH_HEADER, &DAT_fffffe000c68acf8, 0,
                                                                "%s: downgrade JIT for entry [%p, %p)");  /* FUN_fffffe000bf48bc8 */
                                        f_hi = *(uint *)(ent + 7);
                                        f_word = f_hi & 0xffbfddff;
                                        *(uint *)(ent + 7) = f_word;
                                        x1 = x1_carry2;
                                        if ((enter_flags >> 0x2b & 1) != 0) {
                                            out_word = CONCAT44((uint32_t)(out_word >> 32) & f_hi >> 7,
                                                                (uint)out_word & f_hi >> 0xb) &
                                                       0x30000000b;
                                        }
                                    }
                                    cur = (off << 1) >> 1;
                                    ent[3] = cur + ent[3];
                                    ent[2] = cur + ent[2];
                                    if (((f_lo >> 6 & 1) != 0) &&
                                       (va_mask = ent[5], ((uint)va_mask >> 1 & 1) == 0)) {
                                        if ((f_word >> 0x1e & 1) == 0) {
                                            if ((va_mask >> 0x20 != 0) &&
                                               (obj_p = (void *)(va_mask >> 0x1a & 0x3fffffffc0 |
                                                                         0xfffffe0000000000),
                                               obj_p != (void *)0)) goto l_obj_check;
                                        } else {
                                            obj_p = (void *)&hv_fault_special_300;
                                            if ((f_word & 2) != 0) {
                                                obj_p = (void *)&hv_fault_special_800;
                                            }
l_obj_check:
                                            if ((((uint8_t *)obj_p)[0x7d] >> 4 & 1) == 0)
                                                goto l_jit_check;
                                        }
                                        f_word = f_word | 0x4000000;
                                        *(uint *)(ent + 7) = f_word;
                                    }
l_jit_check:
                                    if ((f_word >> 0x1e & 1) == 0) {
                                        if ((*(uint *)((long)ent + 0x2c) != 0) &&
                                           (obj_p = (void *)((ulong)*(uint *)((long)ent + 0x2c) << 6 |
                                                                    0xfffffe0000000000),
                                           obj_p != (void *)0)) goto l_obj_check2;
                                    } else {
                                        obj_p = (void *)&hv_fault_special_300;
                                        if ((f_word & 2) != 0) {
                                            obj_p = (void *)&hv_fault_special_800;
                                        }
l_obj_check2:
                                        if (((uint8_t *)obj_p)[0xae] == '\"') {
                                            *(uint *)(map + 0xb0) = *(uint *)(map + 0xb0) | 0x800000;
                                        }
                                    }
                                    *(uint32_t *)(ent + 4) = 0x30000;
                                    cur = tpidr_el1;
                                    *(int *)(cur + 0x22c) = *(int *)(cur + 0x22c) + 1;
                                    if (hv_debug_flag != 0) {
                                        kernel_map_entry_link((uint64_t)ent, x1);   /* FUN_fffffe000b915978 */
                                    }
                                    x1 = kernel_map_entry_commit2((void *)map, ent, off, off2,
                                                                  enter_flags);       /* FUN_fffffe000b8c6db8 */
                                    kernel_vm_sync(x1, (uint64_t)ent);              /* FUN_fffffe000b91600c */
                                    ent = (long *)*list_head;
                                }
                            }
                            if ((f_lo >> 5 & 1) != 0) {
                                out_word = 0x100000001;
                            }
                            kernel_map_unref(map);                      /* FUN_fffffe000b7f6aac */
                            if (obj_list != (uint64_t *)0) {
                                do {
                                    pmap = (uint64_t *)*obj_list;
                                    if (pmap == (uint64_t *)0) {
                                        obj_tail = &obj_list;
                                    }
                                    *obj_list = 0;
                                    obj_list = (uint64_t *)pmap;
                                    kernel_vm_obj_batch(0);             /* FUN_fffffe000b8a9e4c */
                                } while (obj_list != (uint64_t *)0);
                            }
                            if (rc == 0) {
                                *map_out = (va_start & (long)(enter_flags << 0x2b) >> 0x3f) +
                                           ((off << 1) >> 1);
                                *out1 = (uint32_t)(out_word >> 32);
                                *out2 = (uint)out_word;
                            }
                            kernel_map_enter_done((void *)entry);       /* FUN_fffffe000b8acc64 */
                            return (ulong)rc;
                        }
                        kernel_map_enter_done((void *)entry);
                    }
                }
            }
        }
    }
    return 4;
}

/* ================================================================== *
 * kernel_copyout @ 0xfffffe000b8b49e8   (est. kernel_copyout / vm_map_protect)
 * Ghidra: ulong FUN_fffffe000b8b49e8(long param_1, ulong param_2, ulong param_3,
 *          int param_4, uint param_5)
 * The vm_map_protect path: changes the protection of the map range
 * [start, end) to `prot` with `flags`. Walks the map entries updating the
 * per-entry protection words (incl. the write-and-exec code-signing check),
 * faulting in shared/copy pages as needed, and returns 0 on success or a
 * KERN_* error. Called by hv_vcpu_slot_op as the copyout helper.
 * Confidence: high (complete decompile, ~250 lines)
 * Notes: the "CODE SIGNING: %d[%s] %s:%d(0x%llx,0x%llx,0x%x) can't have both
 *   write and exec at the same time" panic-string path calls the 11-arg
 *   vm_map_enter (kernel_mem_validate b8b51c8); vm_map_protect panic string
 *   via c0e11ec. Callees b915588 (prot remove), b8847f0 (report), b86659c
 *   (cs check), b7f62e8 (map ref), b8adda8 (lookup entry), b7f6b94 (map
 *   lock2), b918644 (map lookup), b8b5b6c (prot dirty), b94bd20 (prot tlb),
 *   b7f6aac (map unref), b91ab24 (unwire), b91600c (vm sync), bf57704
 *   (cleanup).
 * Kernel code recreated for audit (hv-deps). */
uint64_t
kernel_copyout(uint64_t map, uint64_t start, uint64_t end, int prot,
               uint32_t flags)
{
    long     cur;             /* lVar1: tpidr_el1 / entry pmap */
    uint64_t r2;           /* register carry */
    uint     r3;           /* entry flags hi */
    uint     r4;           /* entry prot */
    uint     r5;           /* new prot word */
    byte     pflag;           /* pmap-ok flag */
    uint64_t *pmap;           /* e7 */
    long     p8;           /* pmap2 */
    uint     r9;           /* cow flag */
    uint64_t va;              /* uVar10: current va / status */
    uint64_t *entry;          /* obj_b */
    uint64_t va_start;        /* prot_ro2 */
    uint64_t va_end;          /* hash_acc */
    uint64_t va_end2;         /* hash_acc companion: aligned end */
    uint64_t page_mask;       /* h1 */
    uint64_t lock_arg0;       /* local_140 = &DAT_fffffe000c68af18 */
    uint64_t lock_arg1;       /* local_138 = 0x42000000 */
    void *   lock_arg2;       /* local_130 = FUN_fffffe000b8b5928 */
    uint64_t *lock_arg3;      /* plock_state = &enter_out */
    uint64_t lock_arg4;       /* local_128 = &DAT_fffffe0007d7fac0 */
    int      lock_prot;       /* local_118 = prot */
    uint     enter_out1;      /* local_110 */
    uint32_t enter_out2;      /* uStack_10c */
    uint64_t enter_size;      /* local_108 */
    uint64_t state;           /* local_100 */
    uint64_t state_end;       /* uStack_f8 */
    uint64_t vmap;            /* local_f0 */
    uint64_t *state_block;    /* puStack_e8 */
    void **  opts_ptr;        /* local_e0 */
    uint64_t state_flags;     /* local_d8 */
    uint64_t state_hi;        /* local_d0 */
    uint64_t state_lo;        /* out_b8 */
    uint64_t state_b0;        /* local_b0 */
    uint64_t state_a8;        /* uStack_a8 */
    uint64_t state_a0;        /* out_a0 */
    uint64_t *state_lo_ptr;   /* obj_list */
    uint64_t enter_out;       /* entry2 */
    uint64_t *enter_out_p;    /* out_word = &enter_out */
    uint64_t enter_flags;     /* off = 0x2000000000 */
    uint     flags_saved;     /* local_70 */

    enter_out_p = &enter_out;
    enter_out = 0;
    enter_flags = 0x2000000000;
    state_a8 = 0;
    state_b0 = 0;
    state_lo_ptr = (uint64_t *)0;
    state_a0 = 0;
    state_hi = 0;
    state_lo = 0;
    /* state_hi2/c0 zeroed */
    state_block = (uint64_t *)0;
    vmap = 0;
    state_flags = 0;
    opts_ptr = (void **)0;
    state_end = 0;
    state = 0;
    pmap = *(uint64_t **)(map + 0x58);
    va = start;
    if (pmap != (uint64_t *)0) {
        if (pmap == &hv_kernel_map_sentinel) {           /* DAT_fffffe000c62b698 */
            va = hv_kernel_map_base & (long)(start << 8) >> 0x3f | start;   /* DAT_fffffe000c62b6a8 */
        } else if ((start >> 0x37 & 1) == 0) {
            va = pmap[3] - 1 & start;
        }
    }
    if ((flags & 0xffffffe8) != 0) {
        flags_saved = 0;
        va = 4;
        goto l_done;
    }
    va_end = 0x20000001;
    flags_saved = flags;
    if (end != start) {
        page_mask = (uint64_t)(uint)~(-1 << (uint64_t)(*(uint16_t *)(map + 0x44) & 0x1f));
        end = end - start;
        if (!CARRY8(va, end)) {
            va_end = va & (page_mask ^ 0xffffffffffffffff);
            va_end2 = end + va + page_mask & ~page_mask;
            if (va_end2 <= va_end)
                goto l_probe;
l_enter:
            if ((flags >> 4 & 1) != 0) {
                if (*(uint64_t *)(map + 0x30) <= va_end) {
                    va = 1;
                    goto l_done;
                }
                if (((((flags >> 2 & 1) != 0) &&
                     ((pmap = *(uint64_t **)(map + 0x58), pmap == (uint64_t *)0 ||
                      (pmap != &hv_kernel_map_sentinel)))) &&
                    ((DAT_fffffe0007e2527c != 0 || (*(uint *)(map + 0xb0) & 0x1000) != 0 ||
                     ((*(byte *)(pmap + 0xe) & 1) == 0)))) &&
                   ((*(uint *)(map + 0xb0) >> 0xb & 1) == 0)) {
                    kernel_vm_cs_check(va_end, va_end2, (long)(int)flags);  /* FUN_fffffe000b86659c */
                    r2 = tpidr_el1;
                    r2 = per_cpu_get((void *)r2);   /* FUN_fffffe000b866ec4 */
                    cur = (long)current_task(0);          /* decompiler drops the arg */
                    if (cur != 0) {
                        current_task((void *)r2);
                    }
                    kernel_boot_misc_o(
                        "CODE SIGNING: %d[%s] %s:%d(0x%llx,0x%llx,0x%x) can\'t have both write and exec at the same time\n");  /* FUN_fffffe000b801ce4 */
                    va = 2;
                    goto l_done;
                }
                enter_out1 = flags & 7;
                enter_out2 = 0;
                enter_size = va_end;
                va = kernel_mem_validate(
                         (void *)map, &enter_size, va_end2 - va_end, 0,
                         (uint32_t)((ulong)((*(uint *)(map + 0xb0) >> 0x12 ^ 0xffffffff) & 1) << 0x33 |
                         0x40000004001), (uint64_t)map, va_end, 1,
                         (int *)&enter_out2, (int *)&enter_out1, 1);  /* FUN_fffffe000b8b51c8 */
                if ((int)va != 0)
                    goto l_done;
                *(uint *)(enter_out_p + 3) = *(uint *)(enter_out_p + 3) & 0xffffffef;
            }
            kernel_map_ref(map);                           /* FUN_fffffe000b7f62e8 */
            if ((va_end < *(uint64_t *)(map + 0x30)) &&
                (cur = (long)kernel_map_lookup_entry((void *)map, va_end), cur != 0)) {  /* FUN_fffffe000b8adda8 */
                if ((*(uint *)(cur + 0x38) & 0x100000) != 0) {
                    va_end = va_end & 0xffffffffffffc000;
                    va_end2 = va_end2 + 0x3fff & 0xffffffffffffc000;
                }
                opts_ptr = (void **)&lock_arg0;
                lock_arg0 = (uint64_t)&DAT_fffffe000c68af18;
                lock_arg1 = 0x42000000;
                lock_arg2 = (void *)0xfffffe000b8b5928;
                lock_arg3 = &enter_out;
                lock_arg4 = (uint64_t)&DAT_fffffe0007d7fac0;
                lock_prot = prot;
                kernel_map_lock2((void *)map);             /* FUN_fffffe000b7f6b94 */
                va = kernel_map_lookup(&state, (void *)map, va_end, va_end2, 0x16029);  /* FUN_fffffe000b918644 */
                if ((int)va == 0) {
                    r9 = 0;
l_loop:
                    entry = state_lo_ptr;
                    if (state_block == (uint64_t *)0) {
                        r4 = (uint32_t)(state_flags >> 32) & 0xfffffffd;
                        state_flags = state_flags & 0xfffffffdffffffff;
                        state_block = &state_hi;
                        va = state;
                    } else {
                        r4 = (uint32_t)(state_flags >> 32);
                        if ((((uint32_t)(state_flags >> 32) & 0xc) == 8) &&
                            (state_end <= state_block[3])) {
                            va = state_lo;
                            if (((uint8_t)state_flags >> 2 & 1) != 0) {
                                state_hi = state_a0 + state_hi;
                                va = state + state_a0;
                            }
                            vmap = state_a8;
                            state_end = state_b0;
                            r4 = (uint32_t)(state_flags >> 32) & 0xfffffff3;
                            state_flags = state_flags & 0xfffffff3ffffffff;
                            state_a0 = 0;
                            state_lo_ptr = (uint64_t *)0;
                            state_block = entry;
                            state = va;
                        }
                        va = state_block[3];
                        if (state_end <= state_block[3])
                            goto l_unwire;
                    }
                    entry = (uint64_t *)*state_block;
                    r3 = (uint32_t)state_flags;
                    if (((uint32_t)state_flags >> 0x13 & 1) == 0) {
l_walk:
                        if (entry == (uint64_t *)0)
                            goto l_unwire;
                    } else if ((entry[5] & 3) == 2) {
                        va_end = entry[3];
                        state_a0 = entry[2] - (entry[6] & 0xfffffffffffff000);
                        state = va - state_a0;
                        state_end = ((state_b0 <= va_end) * state_b0 +
                                     (state_b0 > va_end) * va_end) - state_a0;
                        vmap = entry[5] & 0xfffffffffffffffc;
                        state_block = (uint64_t *)0;
                        state_flags = CONCAT44(r4, (uint32_t)state_flags) &
                                      0xfffffff3ffffffff | 0x800000000;
                        if ((r3 >> 2 & 1) != 0) {
                            state_hi = state;
                        }
                        state_lo_ptr = entry;
                        entry = (uint64_t *)kernel_map_lookup_entry(0, 0);  /* FUN_fffffe000b8adda8 */
                        goto l_walk;
                    }
                    va = vmap;
                    r4 = (uint)entry[7];
                    r3 = r4 >> 7 & 7;
                    if (prot == 0) {
                        r5 = r4 & 0xfffffc00 | r4 & 0x7f |
                                (*(uint *)(enter_out_p + 3) & 7) << 7;
                    } else {
                        r5 = (*(uint *)(enter_out_p + 3) & 0xf) << 0xb;
                        *(uint *)(entry + 7) = r4 & 0xffff8000 | r4 & 0x7ff | r5;
                        r5 = r4 & 0xffff8000 | r4 & 0x400 | r5 |
                                r4 & 0x7f | (*(uint *)(enter_out_p + 3) & r3) << 7;
                    }
                    *(uint *)(entry + 7) = r5;
                    state_block = entry;
                    if (((r5 & 0x800200) == 0x200 && (r4 & 0x200) == 0) ||
                        (((r5 ^ 0xffffffff) & 0x800100) == 0 && (r4 & 0x100) == 0)) {
                        kernel_vm_prot_dirty(vmap, entry, 0x40000000000);   /* FUN_fffffe000b8b5b6c */
                        r5 = (uint)entry[7];
                    }
                    r4 = r5 >> 7 & 7;
                    if (r4 != r3) {
                        va_end = entry[5];
                        if ((((((uint)va_end >> 1 & 1) == 0) && ((r5 >> 0x1e & 1) == 0)) &&
                            (va_end >> 0x20 != 0)) &&
                           ((uint32_t *)(va_end >> 0x1a & 0x3fffffffc0 | 0xfffffe0000000000) ==
                            &hv_fault_special_400)) {
                            r9 = (r5 & 0x100) << 4 | r9;
                        } else {
                            r4 = r5 >> 7 & 5;
                        }
                        cur = *(long *)(va + 0x58);
                        if (cur == 0) {
                            p8 = 0;
l_pmap:
                            pflag = 1;
                        } else {
                            p8 = cur;
                            if (cur == 0)
                                goto l_pmap;
                            pflag = *(byte *)(*(long *)(cur + 0x20) + 0x4c) ^ 1;
                        }
                        if ((r4 == 7) && ((pflag & 1) != 0)) {
                            if (((r5 >> 0x1d & 1) == 0) && ((*(byte *)(p8 + 0x70) & 1) != 0)) {
                                r4 = 7;
                            } else {
                                if (*(short *)((long)entry + 0x3c) != 0) {
                                    kernel_panic_msg_fmt("vm_map_protect(%p,0x%llx,0x%llx) new=0x%x wired=%x @%s:%d");
                                }
                                r4 = 0;
                            }
                        }
                        if ((((uint)va_end >> 1 & 1) == 0) || ((r5 >> 0x11 & 1) == 0)) {
                            if (cur == 0) {
                                cur = 0;
                            }
                            va_end = entry[2];
                            page_mask = entry[3];
                            r3 = r9;
                        } else {
                            cur = *(long *)((va_end & 0xfffffffffffffffc) + 0x58);
                            if (cur == 0) {
                                cur = 0;
                            }
                            va_end = entry[2];
                            page_mask = entry[3];
                            r3 = 0;
                        }
                        kernel_vm_prot_tlb(va + 0x58 & 0xffffffffffff | 0x250c000000000000,
                                           (void *)cur, va_end, page_mask, r4, r3, 0);  /* FUN_fffffe000b94bd20 */
                    }
                    goto l_loop;
                }
                cur = tpidr_el1;
                *(uint64_t *)(cur + 0x238) = 0;
                vmap = 0;
                state_block = (uint64_t *)0;
            } else {
                kernel_map_unref(map);                     /* FUN_fffffe000b7f6aac */
                va = 1;
            }
            goto l_done;
        }
l_probe:
        va = kernel_vm_prot_remove(4, va, end, page_mask, map);   /* FUN_fffffe000b915588 */
        if (va >> 0x28 != 0) {
            kernel_vm_report_fault(0x22, 1, 1, 0x22, va, end, page_mask, 0, 4,
                                   (long)(int)va);         /* FUN_fffffe000b8847f0 */
        }
        if ((va >> 0x20 & 1) == 0) {
            va = 4;
        } else if ((int)va == 0) {
            va = 0;
            va_end = 0;
            flags = *(uint *)(enter_out_p + 3);
            goto l_enter;
        }
    }
    r9 = 0;
    if ((uint)va != 0x20000001) {
        r9 = (uint)va;
    }
    va = (uint64_t)r9;
l_done:
    kernel_vm_cleanup((uint64_t)&enter_out, 8);           /* FUN_fffffe000bf57704 */
    return va;
l_unwire:
    state_block = (uint64_t *)0;
    cur = tpidr_el1;
    *(uint64_t *)(cur + 0x238) = 0;
    r9 = (uint)state_flags;
    if (((uint32_t)(state_flags >> 32) & 0xc) == 8) {
        va = state_lo;
        if (((uint8_t)state_flags >> 2 & 1) != 0) {
            state_hi = state_a0 + state_hi;
            va = state + state_a0;
        }
        state_block = state_lo_ptr;
        vmap = state_a8;
        state_end = state_b0;
        state_flags = state_flags & 0xfffffff3ffffffff;
        state_a0 = 0;
        state_lo_ptr = (uint64_t *)0;
        state = va;
    }
    if ((r9 >> 2 & 1) == 0) {
        kernel_vm_unwire(&state);                         /* FUN_fffffe000b91ab24 */
    } else if ((state_block != (uint64_t *)0) && ((~(uint32_t)state_block[5] & 3) != 0)) {
        kernel_vm_sync(0, 0);                             /* FUN_fffffe000b91600c */
    }
    va = 0;
    vmap = 0;
    state_block = (uint64_t *)0;
    goto l_done;
}

/* ================================================================== *
 * copyin @ 0xfffffe000b95c144   (est. copyin)
 * Ghidra: undefined8 FUN_fffffe000b95c144(ulong param_1, undefined8 param_2,
 *          ulong param_3)
 * The universal user->kernel copyin: copies `len` bytes from the user
 * address `src` into the kernel buffer `dst`. Returns 0 on success, 0xe
 * (EFAULT) when the range falls outside the current task's address-space
 * window (as->min/+0x28 .. as->max/+0x30, carry-checked), 0x16 for an
 * oversized request (len >= 0x4000001), or the copy primitive's status.
 * The address-space spec (the tagged-address sentinel DAT_fffffe000c62b698)
 * selects the sentinel-map copy path (b758bd0) or the PAN-aware copy
 * (b75f890, with the pan=0/1 disable around it) / fallback copy (b75fed8).
 * Direct callee of hv.c hv_vm_map_core and hv_vcpu_create.
 * Confidence: high (complete decompile, ~70 lines)
 * Notes: callees b95c414 (copy), b75f890 (PAN copy), b75fed8 (copy
 *   fallback), b758bd0 (sentinel-map copy — the de-guess name
 *   kernel_early_init for b758bd0 is a misnomer, see manifest), panic
 *   c0e11ec "copy_ensure_address_space_spec changed address" /
 *   "NULL task in %s". Warning: Removing unreachable block
 *   (ram,0xfffffe000b95c28c).
 * Kernel code recreated for audit (hv-deps). */
int
copyin(const void *src, void *dst, size_t len)
{
    long     cur;           /* lVar1: tpidr_el1 */
    long     task;          /* lVar6/lVar2: current task */
    uint64_t rc;            /* uVar3: copy status */
    uint64_t va;            /* uVar4: resolved user address */
    uint64_t *pmap;         /* puVar5: task pmap */
    uint64_t src_a = (uint64_t)src;   /* param_1 as integer */

    cur = tpidr_el1;
    if (len == 0) {
        return 0;
    }
    if (len < 0x4000001) {
        task = *(long *)(cur + 0x420);
        pmap = *(uint64_t **)(task + 0x58);
        va = src_a;
        if (((((hv_fault_boot_threshold < 0x12) && (*(long *)(cur + 0x418) == 0)) ||
             (task = (long)per_cpu_base(cur), task == 0)) ||
            ((*(ushort *)(task + 0x6b0) >> 2 & 1) != 0)) &&
           ((pmap != (uint64_t *)0 && (pmap != (uint64_t *)0)))) {
            if (src_a == 0) {
                va = 0;
            } else if (pmap == &hv_kernel_map_sentinel) {   /* DAT_fffffe000c62b698 */
                va = src_a | 0xf00000000000000;
            } else {
                va = src_a & 0xf0ffffffffffffff;
            }
        }
        if (((va < *(uint64_t *)(task + 0x28)) || (CARRY8(va, len))) ||
            (*(uint64_t *)(task + 0x30) < va + len)) {
            return 0xe;                             /* EFAULT */
        }
        if ((va & 0xff00000000000000) == 0 || pmap == &hv_kernel_map_sentinel) {
            kernel_copy((uint64_t)dst, len);        /* FUN_fffffe000b95c414: (dst, len) */
            pmap = *(uint64_t **)(task + 0x58);
            if ((pmap == (uint64_t *)0) || (pmap != &hv_kernel_map_sentinel)) {
                va = src_a & 0xff7fffffffffffff;
                if (pmap == &hv_kernel_map_sentinel) {
                    va = src_a | 0x80000000000000;
                }
                if (va == src_a) {
                    task = (long)per_cpu_base(cur);
                    if (task == 0) {
                        kernel_panic_msg_fmt("NULL task in %s @%s:%d");
                    }
                    if (((((task == 0) || ((*(ushort *)(task + 0x6b0) >> 2 & 1) == 0)) ||
                         ((*(byte *)(task + 0x361) >> 6 & 1) == 0)) &&
                        ((*(byte *)(cur + 0x1c8) & 1) == 0)) &&
                       (((hv_fault_boot_threshold < 0x12 && (*(long *)(cur + 0x418) == 0)) ||
                         (((*(ushort *)(task + 0x6b0) >> 2 & 1) != 0 ||
                           (-1 < *(char *)(*(long *)(cur + 0x420) + 0xb2))))))) {
                        pan = 0;
                        rc = kernel_copy_pan(va, dst, len);   /* FUN_fffffe000b75f890 */
                        pan = 1;
                        if ((int)rc != 0x23) {
                            return (int)rc;
                        }
                    }
                    rc = kernel_copy_fallback(va, dst, len);   /* FUN_fffffe000b75fed8 */
                    *(uint8_t *)(cur + 0x1f0) = 0;
                    return (int)rc;
                }
            } else if ((src_a | 0x80000000000000) == src_a) {
                kernel_copy_sentinel((uint64_t)dst, src_a | 0x80000000000000, len);  /* b758bd0(dest, source, len) — disasm: x0=x20(dst), x2=x19(len) */
                return 0;
            }
            kernel_panic_msg_fmt("copy_ensure_address_space_spec changed address: 0x%llx->0x%llx @%s:%d");
        }
    }
    return 0x16;
}

/* ================================================================== *
 * copyout @ 0xfffffe000b95d6f4   (est. copyout)
 * Ghidra: undefined8 FUN_fffffe000b95d6f4(undefined8 param_1, ulong param_2,
 *          ulong param_3)
 * The universal kernel->user copyout: copies `len` bytes from the kernel
 * buffer `src` to the user address `dst`. Mirror of copyin (b95c144) with
 * the PAN handling: resolves the address-space spec, bounds-checks dst
 * against the task window (+0x28/+0x30, carry-checked, 0xe on violation),
 * and for the PAN-eligible path disables PAN (S3_6_15_1_6 write) around
 * kernel_copyout_pan (b75fb2c), re-enables it, takes the preemption
 * counter (+0x1c0) with a TLB flush at zero, then falls through to
 * kernel_copyout_fallback (b76002c). The sentinel-map path uses
 * kernel_copy_sentinel (b758bd0). Returns 0 on success, 0xe/0x16 errors.
 * Direct callee of hv_vcpu_create (b989040) and hv_capabilities (b984fd8).
 * Confidence: high (complete decompile, ~120 lines)
 * Notes: PAN state register S3_6_15_1_5/6 written with the constants
 *   0x2020a53a302abae6/0x2020a52a302abae6 (est. PAN/UAO toggles); callees
 *   b95c414, b758bd0, b75fb2c, b76002c, b866ec4, panics c0e11ec/c0f1874,
 *   TLB flush b96c6d4. Warning: Removing unreachable block
 *   (ram,0xfffffe000b95d840).
 * Kernel code recreated for audit (hv-deps). */
int
copyout(const void *src, void *dst, size_t len)
{
    int      rc;            /* iVar1: preemption counter */
    uint8_t  pan_flag;      /* bVar2: PAN state flag */
    long     cur;           /* lVar3: tpidr_el1 */
    long     task;          /* lVar4/lVar11: current task */
    uint64_t status;        /* uVar5: copy status */
    uint64_t va;            /* uVar6: resolved user address */
    uint64_t pan_state;     /* uVar7: PAN register state */
    uint64_t *pmap;         /* puVar8/puVar10: task pmap */
    uint64_t dst_a = (uint64_t)dst;   /* param_2 as integer */

    cur = tpidr_el1;
    if (len == 0) {
l_zero:
        status = 0;
    } else {
        if (len < 0x4000001) {
            task = *(long *)(cur + 0x420);
            pmap = *(uint64_t **)(task + 0x58);
            va = dst_a;
            if (((((hv_fault_boot_threshold < 0x12) && (*(long *)(cur + 0x418) == 0)) ||
                 (task = (long)per_cpu_base(cur), task == 0)) ||
                ((*(ushort *)(task + 0x6b0) >> 2 & 1) != 0)) &&
               ((pmap != (uint64_t *)0 && (pmap != (uint64_t *)0)))) {
                if (dst_a == 0) {
                    va = 0;
                } else if (pmap == &hv_kernel_map_sentinel) {   /* DAT_fffffe000c62b698 */
                    va = dst_a | 0xf00000000000000;
                } else {
                    va = dst_a & 0xf0ffffffffffffff;
                }
            }
            if (((va < *(uint64_t *)(task + 0x28)) || (CARRY8(va, len))) ||
                (*(uint64_t *)(task + 0x30) < va + len)) {
                return 0xe;                             /* EFAULT */
            }
            if ((va & 0xff00000000000000) == 0 || pmap == &hv_kernel_map_sentinel) {
                kernel_copy((uint64_t)src, len);        /* FUN_fffffe000b95c414: (src, len) */
                pmap = *(uint64_t **)(task + 0x58);
                if (pmap == (uint64_t *)0) {
                    pmap = (uint64_t *)0;
                } else {
                    if (pmap == &hv_kernel_map_sentinel) {
                        if ((dst_a | 0x80000000000000) != dst_a)
                            goto l_spec_changed;
                        kernel_copy_sentinel(dst_a | 0x80000000000000, (uint64_t)src, len);  /* b758bd0(dest, source, len) — disasm: x1=x20(src), x2=x19(len) */
                        goto l_zero;
                    }
                }
                va = dst_a & 0xff7fffffffffffff;
                if (pmap == &hv_kernel_map_sentinel) {
                    va = dst_a | 0x80000000000000;
                }
                if (va == dst_a) {
                    task = (long)per_cpu_base(cur);
                    if (task == 0) {
                        kernel_panic_msg_fmt("NULL task in %s @%s:%d");
                    }
                    if (((((task == 0) || ((*(ushort *)(task + 0x6b0) >> 2 & 1) == 0)) ||
                         ((*(byte *)(task + 0x361) >> 6 & 1) == 0)) &&
                        ((*(byte *)(cur + 0x1c8) & 1) == 0)) &&
                       (((hv_fault_boot_threshold < 0x12 && (*(long *)(cur + 0x418) == 0)) ||
                         (((*(ushort *)(task + 0x6b0) >> 2 & 1) != 0 ||
                           (-1 < *(char *)(*(long *)(cur + 0x420) + 0xb2))))))) {
                        if (pmap == (uint64_t *)0) {
                            pmap = (uint64_t *)0;
                        }
                        pan = 0;
                        pan_state = (uint64_t)*(uint8_t *)((uint8_t *)pmap + 0x75);
                        if (((*(uint8_t *)((uint8_t *)pmap + 0x75) & 1) != 0) &&
                           (pan_state = UnkSytemRegRead(3, 6, 0xf, 1, 5),
                           ((pan_state ^ 0xffffffffffffffff) & 0x3000000000) == 0)) {
                            pan_state = 0x2020a53a302abae6;
                            UnkSytemRegWrite(3, 6, 0xf, 1, 6, 0x2020a53a302abae6);
                            InstructionSynchronizationBarrier();
                        }
                        status = kernel_copyout_pan((void *)src, va, len);   /* FUN_fffffe000b75fb2c; disasm b95d998: x0=src, x1=va, x2=len */
                        pan = 1;
                        if (((*(uint8_t *)(*pmap + 0x75) & 1) != 0) &&
                           (task = (long)UnkSytemRegRead(3, 6, 0xf, 1, 6),
                            task != 0x2020a52a302abae6)) {
                            UnkSytemRegWrite(3, 6, 0xf, 1, 6, 0x2020a52a302abae6);
                            InstructionSynchronizationBarrier();
                        }
                        if ((int)status != 0x23) {
                            return (int)status;
                        }
                        pan_flag = *(uint8_t *)(*pmap + 0x75);
                    } else {
                        pan_flag = *(uint8_t *)((uint8_t *)pmap + 0x75);
                    }
                    if ((pan_flag & 1) != 0) {
                        *(int *)(cur + 0x1c0) = *(int *)(cur + 0x1c0) + 1;
                        *(uint8_t *)(cur + 0x1f0) = 1;
                        if ((*(uint8_t *)(*(long *)(cur + 0x1b8) + 0x6b) & 1) == 0) {
                            rc = *(int *)(cur + 0x1c0);
                        } else {
                            InstructionSynchronizationBarrier();
                            *(uint8_t *)(*(long *)(cur + 0x1b8) + 0x6b) = 0;
                            rc = *(int *)(cur + 0x1c0);
                        }
                        if (rc == 0) {
                            kernel_panic();             /* c0f1874, noreturn */
                        }
                        *(int *)(cur + 0x1c0) = rc - 1;
                        if ((rc - 1 == 0) && ((*(uint8_t *)(*(long *)(cur + 0x1b8) + 0x4c) >> 2 & 1) != 0)) {
                            kernel_tlb_flush();          /* b96c6d4 */
                        }
                    }
                    status = kernel_copyout_fallback((void *)src, va, len);   /* FUN_fffffe000b76002c; disasm b95da04: x0=src, x1=va, x2=len */
                    *(uint8_t *)(cur + 0x1f0) = 0;
                    return (int)status;
                }
l_spec_changed:
                kernel_panic_msg_fmt("copy_ensure_address_space_spec changed address: 0x%llx->0x%llx @%s:%d");
            }
        }
        status = 0x16;
    }
    return (int)status;
}
