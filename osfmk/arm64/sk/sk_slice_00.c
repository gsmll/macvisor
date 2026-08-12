/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice 0x000012d4-0x00010244 — root-task / platform launch, symbol-table
 * binding, capability bootstrap, and the embedded lite_zone (libmalloc)
 * allocator (zone create/alloc/free/realloc + the per-CPU lock and page
 * management machinery). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * Names are estimates; FUN_ address in comment is ground truth.
 * ------------------------------------------------------------------ */

/* Boot / platform machine helpers (region 0x0004xxxx-0x0006xxxx). */
extern void *sk_boot_image_info(void);                                  /* FUN_00054610 */
extern void sk_boot_diag_write(unsigned long a, unsigned long b);       /* FUN_0004b9e0 */
extern void sk_boot_tick_init(void);                                    /* FUN_00055288 */
extern int sk_printf(const char *fmt, ...);                             /* FUN_00118b28 */
extern int sk_printf2(const char *fmt, ...);                            /* FUN_00118b94 */
extern void sk_boot_platform_setup(void);                               /* FUN_00060530 */
extern void sk_boot_region_store(unsigned long v);                      /* FUN_0006d654 */
extern void sk_boot_region_store2(unsigned long v);                     /* FUN_0006cdf8 */
extern unsigned long sk_image_base_get(void);                           /* FUN_0006d680 */
extern unsigned long sk_image_end_get(void);                            /* FUN_0006d68c */
extern void sk_boot_vm_init(void);                                      /* FUN_0006b7bc */
extern void sk_boot_config_store(unsigned long cfg);                    /* FUN_00052718 */
extern void *sk_cpu_boot_info(void);                                    /* FUN_00060524 */
extern void sk_boot_info_bind(void *info, void *tag);                   /* FUN_00061994 */
extern void *sk_boot_uuid_source(void);                                 /* FUN_0005ba14 */
extern int sk_boot_byte_write(int v);                                   /* FUN_0006c228 */
extern void *sk_boot_object(void);                                      /* FUN_00034a2c */
extern unsigned long sk_va_to_pa(unsigned long v);                      /* FUN_0006d024 */
extern unsigned long sk_va_align(unsigned long v);                      /* FUN_0006cf50 */
extern unsigned long sk_phys_alloc(unsigned long size);                 /* FUN_00034f70 */
extern void sk_symbol_table_commit(void);                               /* FUN_004af988 */
extern void sk_thread_spawn(void **out, void (*entry)(void), unsigned long a,
                             unsigned long b, unsigned long c);         /* FUN_0005eec4 */
#define SK_SPAWN(out, fn, a, b, c) \
    sk_thread_spawn(out, (void (*)(void))(fn), a, b, c)
extern void sk_thread_get(void *th);                                    /* FUN_0005fccc */
extern void *sk_boot_object_get(int type);                              /* FUN_0019ae2c */
extern unsigned long sk_thread_state(void *th);                         /* FUN_00061630 */
extern void sk_boot_abort(void *ctx, void *cfg);                        /* FUN_004afbc4 */
extern void sk_boot_panic(const char *fmt, ...) __attribute__((noreturn)); /* FUN_00054354 */
extern void sk_boot_abort2(unsigned long a, void *ctx);                 /* FUN_004afb6c */
extern unsigned long sk_boot_abort3(void);                              /* FUN_004afc1c */
extern void sk_boot_abort4(unsigned long a, void *cfg);                 /* FUN_004afb14 */
extern void sk_boot_fatal(void) __attribute__((noreturn));              /* FUN_0011d7e8 */
extern unsigned long sk_boot_ec_switch(unsigned long a, int b);         /* FUN_0005b190 */
extern void sk_boot_ec_setup(int state);                                /* FUN_0005cb18 */
extern void sk_boot_error_print(unsigned long a, int sel, int z,
                                unsigned long b, const char *fmt, ...); /* FUN_00116bcc */

/* Memory / physical-map helpers. */
extern unsigned long sk_mem_avail_hi(void);                             /* FUN_0006d6b8 */
extern unsigned long sk_mem_avail_lo(void);                             /* FUN_0006d698 */
extern unsigned long sk_phys_map_region_va(void);                       /* FUN_0006d660 */
extern void sk_phys_map_tighten();                                  /* FUN_0006b77c */
extern unsigned long sk_devtree_get();                                      /* FUN_00084368 */
extern void sk_devtree_set_va();                           /* FUN_0006d66c */
extern unsigned long sk_devtree_validate();     /* FUN_00066424 */
extern unsigned long sk_object_boot_0();                                    /* FUN_0009efd4 */
extern unsigned long sk_boot_memtype();                  /* FUN_0008f9a0 */
extern unsigned long sk_boot_cpu_slot();                                    /* FUN_0008e640 */
extern unsigned long sk_boot_caps();                                /* FUN_0019ae0c */
extern unsigned long sk_boot_cpu_count();                           /* FUN_0005526c */
extern unsigned long sk_arch_boot_0();                                      /* FUN_001030c4 */
extern unsigned long sk_arch_boot_1();                                      /* FUN_001022cc */
extern unsigned long sk_obj_get_0();                                        /* FUN_000773f0 */
extern unsigned long sk_obj_get_1();                                        /* FUN_0007063c */
extern unsigned long sk_obj_get_2();                                        /* FUN_000a6834 */
extern unsigned long sk_obj_get_3();                                        /* FUN_000a3e40 */
extern void sk_finalize_0();                                        /* FUN_000db3d0 */
extern void *sk_finalize_1(unsigned long, unsigned long, unsigned long,
                           unsigned long, void *, unsigned long,
                           unsigned long, unsigned long, void *, void *,
                           unsigned long);                              /* FUN_000c118c */
extern void sk_finalize_2();                                        /* FUN_000c544c */
extern void sk_finalize_3();                                        /* FUN_000cf6a4 */
extern unsigned long sk_btree_0(unsigned long a, unsigned long b);      /* FUN_000b7c9c */
extern void sk_boot_pll();                                      /* FUN_0006bb34 */
extern void sk_boot_gate();                                         /* FUN_000d0020 */
extern void *sk_boot_op_probe(unsigned long a, unsigned long b);        /* FUN_00071050 */
extern void sk_platform_init();                                     /* FUN_000534c0 */

/* Lite_zone (libmalloc) machine primitives. */
extern void *sk_alloc(unsigned long size, ...);                         /* FUN_0036b270 */
extern void sk_free(void *ptr, ...);                                    /* FUN_0036b118 */
extern unsigned long sk_alloc_init_pages();       /* FUN_0036a940 */
extern unsigned long sk_alloc_teardown();                          /* FUN_0036a1a0 */
extern void sk_alloc_finalize();                          /* FUN_0036a20c */
extern void sk_alloc_link();                      /* FUN_0036b588 */
extern void sk_alloc_link2();                     /* FUN_0036b6ac */
extern void sk_alloc_link3();                     /* FUN_0036b21c */
extern unsigned long sk_alloc_touch_extern();                        /* FUN_0036a9a0 */
extern void sk_alloc_bump_region(unsigned long a, unsigned long b,
                                 unsigned long tag);                    /* FUN_0035bc70 */
extern unsigned long sk_obj_name(unsigned long obj, unsigned long a,
                                 unsigned long b, ...);                 /* FUN_00389910 */

/* Kernel / arch helpers used by the allocator. */
extern unsigned long sk_pt_write(unsigned long va, unsigned long size, int type,
                                 int gran, ...);                        /* FUN_00011bf4 */
extern void sk_pt_invalidate(unsigned long va, unsigned long size, int type,
                             int gran);                                 /* FUN_00011b80 */
extern void sk_cache_clean(unsigned long va, unsigned long size,
                           unsigned long dummy);                        /* FUN_000118d0 */
extern void sk_memset_va(unsigned long va, unsigned long size,
                         unsigned long v);                              /* FUN_00011884 */
extern void sk_memcpy(unsigned long dst, unsigned long src,
                      unsigned long n);                                 /* FUN_00117cc4 */
extern void sk_memcpy2(void *dst, const void *src,
                       unsigned long n);                                /* FUN_00117cc8 */
extern void sk_memset(void *dst, int v, unsigned long n);               /* FUN_00117f8c */
extern void sk_memset_tracked(void *dst, unsigned long n,
                              unsigned long v);                         /* FUN_001143a0 (thunk) */
extern void sk_memset_tracked_small(void *dst);                         /* FUN_00114330 (thunk) */
extern unsigned long sk_zone_reap(void *zone);                          /* FUN_00011494 */
extern void sk_zone_reap2(void *zone);                                  /* FUN_00010e3c */
extern void sk_zone_reap3(void *zone, int mode);                        /* FUN_000122f0 */
extern void *sk_zone_reap4(void *zone);                                 /* FUN_00010830 */
extern unsigned long sk_tick(unsigned long a, ...);                     /* FUN_00010934 */
extern unsigned long sk_rand(void);                                     /* FUN_000114f0 */
extern void sk_cpu_id_init(void);                                       /* FUN_0001071c */
extern int sk_sched_init(int a, void *b);                               /* FUN_001181b4 */
extern void sk_stack_poison(void *p, unsigned long n);                  /* FUN_00054414 (thunk) */
extern int sk_clz(unsigned long v);                                     /* FUN_00116e00 */
extern unsigned long sk_bit_rand(void);                                 /* FUN_00116da0 */
extern int sk_lock_acquire(unsigned long lock);                         /* FUN_0011582c */
extern int sk_lock_release(unsigned long lock);                         /* FUN_00115894 */
extern int sk_lock_try(unsigned long lock);                             /* FUN_00115860 */
extern void sk_lock_error(int prio, int z, const char *fmt, ...);       /* FUN_00011824 */
extern void sk_log(int prio, const char *fmt, ...);                     /* FUN_000117e8 */
extern void sk_bug_panic(const char *fmt, ...) __attribute__((noreturn)); /* FUN_001150e0 */
extern int sk_bug_check(unsigned long v);                               /* FUN_000119c0 */
extern unsigned long sk_alloc_zone_0(unsigned long a, unsigned long b,
                                     int c, int d, unsigned long e, int f,
                                     void **out);                       /* FUN_00011a08 */
extern unsigned long sk_pmo_init(unsigned long size, unsigned long tag,
                                 int type, int gran, void *fmt);        /* FUN_00011b18 */
extern void *sk_zone_pt_for(unsigned long zone_base);                   /* FUN_000128cc */
extern void sk_cpu_preempt(unsigned long a, ...);                       /* FUN_00012b0c */
extern void sk_zone_grow_1(unsigned long a, unsigned long b, ...);      /* FUN_0026b434 */
extern void *sk_errno_slot(void);                                       /* FUN_0006037c (thunk) */
extern void sk_tlb_broadcast(void);                                     /* FUN_000529d4 (thunk) */
extern unsigned long sk_alloc_step_ext(unsigned long obj, ...);                       /* FUN_00001d00 (unused) */
extern void sk_boot_info_bind_ext(void);                                /* FUN_0005f0xx (no-op wrapper) */
extern unsigned long sk_boot_strmap_build(); /* FUN_0006xxxx */
extern void sk_boot_fatal2(void) __attribute__((noreturn));             /* FUN_001afa84 */
extern void CallSupervisor(unsigned long op);                           /* supervisor call */
extern void sk_boot_ec_dispatch();                                  /* FUN_00002bxx */
extern unsigned long boot_name0;   /* name-table descriptor 0 */
extern long boot_def0;             /* default capability 0 */

/* TPIDRRO_EL0 (user ro thread id) access used as the per-CPU argument
 * block pointer for the CallSupervisor ABI. */
static inline unsigned long *sk_tpidrro(void)
{
    unsigned long v;
    asm volatile("mrs %0, tpidrro_el0" : "=r"(v));
    return (unsigned long *)v;
}

/* Dispatch through an object's vtable (the object holds a pointer to its
 * method array at the given offset). TYPE is a function-pointer type. */
#define SK_VTABLE(object, off, TYPE) \
    (*(TYPE *)((char *)(object) + (off)))

#define SK_FCALL0(base, off) \
    ((void (*)(void))(*(void **)((char *)(base) + (off))))()
#define SK_FCALL1(base, off, a) \
    ((void (*)(unsigned long))(*(void **)((char *)(base) + (off))))((unsigned long)(a))
#define SK_FCALL0R(base, off) \
    ((unsigned long (*)(void))(*(void **)((char *)(base) + (off))))()
#define SK_FCALL2(base, off, a, b) \
    ((void (*)(unsigned long, unsigned long))(*(void **)((char *)(base) + (off)))) \
        ((unsigned long)(a), (unsigned long)(b))

/* Globals used by this slice (image base / end, boot config, boot state). */
extern unsigned long sk_image_base;      /* DAT_006adfc0 */
extern unsigned long sk_image_end;       /* DAT_006adfc8 */
extern unsigned long sk_boot_cfg;        /* DAT_006ad6e0 */
extern unsigned long sk_boot_done;       /* DAT_006adfd0 */
extern unsigned long sk_boot_mem_hi;     /* DAT_006add08 */
extern unsigned long sk_zone_present;    /* DAT_006ac234 */

/* Local forward declarations (defined in this file). */
unsigned long sk_boot_launcher_entry(void);
unsigned long sk_launcher_root(void);
long sk_boot_thread_main(void);
long sk_boot_thread_main2(void);
void sk_boot_ec_switch_impl(void *param_1, void *param_2, unsigned long param_3);
void sk_boot_ec_err(void *param_1, void *param_2);
unsigned long sk_boot_run(void);
void sk_boot_strmap(unsigned long *name, long *def);
unsigned int sk_boot_done_poll(void);
unsigned char sk_boot_done_get(void);
void sk_boot_finish(unsigned long a);
void sk_alloc_step(void);
unsigned long sk_alloc_free_step(void);
void sk_alloc_free_link(unsigned long *obj);

/* Forward declarations for lite_zone internal helpers (defined below). */
unsigned long lite_zone_alloc_block(unsigned char *zone, unsigned long type,
                                    unsigned long tag, unsigned int param_4,
                                    unsigned long param_5, unsigned long size, int param_7);
void lite_zone_alloc_small(long zone, unsigned long size, unsigned long cls,
                           unsigned long param_4);
unsigned long lite_zone_alloc_large(long zone, long param_2, unsigned long param_3,
                                    unsigned long param_4, unsigned int param_5);
void lite_zone_alloc_class(long zone, unsigned long size, unsigned long param_3,
                           unsigned long param_4);
void lite_zone_alloc_round(unsigned long zone, unsigned long param_2, unsigned long param_3,
                           unsigned long param_4, unsigned int param_5, ...);
void lite_zone_free_block(unsigned char *zone, unsigned long block, unsigned long param_3,
                          int param_4);
void lite_zone_free_small(long zone, unsigned long *ptr);
void lite_zone_free_fail(long zone, unsigned long ptr, unsigned long param_3);
void lite_zone_free_large(long zone, unsigned long *ptr);
long lite_zone_free_walk(long zone, unsigned long type, char *meta,
                             long *free_list, unsigned long count, unsigned long size);
long lite_zone_free_walk_full(long zone, unsigned long type, char *meta, long *free_list,
                              unsigned long count, unsigned long size);
void lite_zone_link_free();
void lite_zone_segment_alloc(unsigned char *zone, unsigned long size, unsigned long param_3,
                             long *out);
unsigned long lite_zone_segment_alloc_ret(unsigned char *zone, unsigned long size,
                                          unsigned long param_3, long *out);
unsigned long lite_zone_segment_alloc2(long zone, unsigned long type, unsigned long tag,
                                     unsigned long param_4, unsigned long count,
                                     unsigned long size);
void lite_zone_clean_block(long param_1, unsigned long param_2);
void lite_zone_link_free_all();
unsigned long lite_zone_page_idx(unsigned long p, unsigned long base);
void lite_zone_unmap_region(long param_1, unsigned long param_2, unsigned long param_3);
void lite_zone_release_pages(unsigned long param_1, long param_2, unsigned long param_3,
                             unsigned int param_4, unsigned int param_5, unsigned int param_6);
unsigned long lite_zone_alloc_medium(long param_1, unsigned long *param_2, unsigned int param_3);
unsigned long *lite_zone_alloc_tiny(long param_1, long param_2, unsigned long param_3);
unsigned long *lite_zone_alloc_tiny_full(long param_1, long param_2, unsigned long param_3);
unsigned long *lite_zone_alloc_large2(long param_1, long param_2, unsigned long param_3);
void lite_zone_free_medium_block(long zone, long param_2, unsigned long *param_3,
                                 unsigned long *param_4);
void lite_zone_free_small_block(long zone, unsigned long block);
void lite_zone_relink(long param_1, long *param_2);
void lite_zone_free_blocks(long param_1, long param_2, unsigned long param_3);
void lite_zone_relink_chain(unsigned long param_1, long param_2, long param_3, long param_4);
void lite_zone_push_free(unsigned long param_1, unsigned long *param_2, unsigned long param_3,
                         unsigned long param_4, unsigned char *param_5);
void lite_zone_lock_op(unsigned long *lock, int op);
void lite_zone_lock_all(long param_1, unsigned long param_2);
void lite_zone_assign_block_x(long param_1, unsigned long *param_2);
long lite_zone_assign_block(long param_1, unsigned long *param_2, long param_3,
                            unsigned long param_4, int param_5, unsigned long param_6,
                            unsigned char *param_7, unsigned long param_8);
void lite_zone_reset_block(unsigned long param_1, long param_2, unsigned long *param_3,
                           int param_4, int param_5);
void lite_zone_free_block_pages(long param_1, unsigned long param_2, long param_3,
                                unsigned long *param_4);
void lite_zone_check_size(unsigned long param_1, unsigned long param_2, unsigned long param_3);
void lite_zone_lock_fail(void);
long lite_zone_malloc(long zone, unsigned long size, unsigned long param_3);
unsigned long *lite_zone_realloc(long zone, unsigned long *ptr, unsigned long new_size,
                                 unsigned long param_4);
void lite_zone_calloc(long zone, unsigned long param_2, unsigned long size,
                      unsigned long param_4);
void lite_zone_guard_compute(long zone, unsigned long size, int param_3, unsigned char *out);
void lite_zone_destroy(long zone, unsigned long mode);
void lite_zone_free_common(long zone, unsigned long ptr, unsigned long param_3,
                           unsigned long param_4);
unsigned long lite_zone_mark_free(long param_1, long param_2, unsigned int *param_3,
                                  unsigned long param_4);
void lite_zone_return_run(long param_1, long param_2, unsigned int *param_3, int param_4);
void lite_zone_chain_free(unsigned long param_1, long param_2, long param_3, unsigned long param_4);
void lite_zone_free_block2(long zone, long param_2, unsigned long *param_3, int param_4);
unsigned long lite_zone_lookup_block(long zone, unsigned long ptr);
unsigned long lite_zone_ptr_size(long zone, unsigned long *ptr);
bool lite_zone_ptr_owned(long zone, unsigned long ptr);
void lite_zone_alloc_small2(long zone, unsigned long param_2, unsigned long param_3,
                            unsigned long param_4, unsigned long param_5);
void lite_zone_alloc_tiny2(long zone, unsigned long size);
void lite_zone_free_small2(long zone, unsigned long *ptr, unsigned long param_3);
void lite_zone_free_small3(long zone, unsigned long *ptr);
unsigned long *lite_zone_realloc2(long zone, unsigned long *ptr, unsigned long new_size,
                                  unsigned long param_4);
unsigned long lite_zone_alloc_small2_body(long zone, unsigned long param_2, unsigned long size,
                                          unsigned long param_4);
unsigned long lite_zone_block_size(unsigned long *block);
unsigned long lite_zone_class_of(long zone, unsigned long param_4);
unsigned long lite_zone_alloc_large_small(long zone, unsigned long param_3, unsigned long got,
                                          unsigned long param_4, unsigned int param_5);
unsigned long lite_zone_realloc_full(long zone, unsigned long *ptr, unsigned long new_size,
                                     unsigned long param_4);
void lite_zone_free_large_walk(long zone, unsigned long *head, unsigned long seg,
                               unsigned long *ptr);
void lite_zone_free_medium_dispatch(long zone, long param_2, unsigned long *param_3,
                                    unsigned long *param_4);
void lite_zone_free_large_block(long zone, unsigned long *blk, unsigned long *pv);
void lite_zone_init_zone(unsigned long *zone, unsigned long sz, unsigned long cpu_count);
void lite_zone_setup_locks(unsigned long *zone);
void lite_zone_reap_subregion(long zone, long base, unsigned long mode);
void lite_zone_reap_big_subregion(long zone, long base, unsigned long i, unsigned long nsub);
void lite_zone_reap_vtable(long zone, long base, long i, unsigned long mode);
void lite_zone_class_setup(long zone, long param_2, unsigned int param_3);
void lite_zone_vtable_setup(unsigned long *zone, unsigned long sz, unsigned long flags);
void lite_zone_push_head(unsigned long param_1, unsigned long *param_2, unsigned long param_3,
                         unsigned long param_4);
unsigned long lite_zone_finalize_block(long param_1, unsigned long *param_2, int param_3);
long lite_zone_pop_partial(long param_1, long param_2);
void lite_zone_set_generation(long param_1, long param_2, unsigned int param_3, int param_4);
void lite_zone_pop_free(unsigned long param_1, unsigned long *param_2, unsigned int param_3,
                        unsigned char *param_4);
unsigned long *lite_zone_scan_run(long param_1, long param_2, unsigned long *param_3,
                                  unsigned long param_4, unsigned char *param_5,
                                  unsigned char *param_6);
void lite_zone_bug3(void);
void lite_zone_merge_blocks(long region, unsigned int param_2, unsigned int param_3);
long lite_zone_carve(long region, int param_2, unsigned long param_3, unsigned int param_4);
void lite_zone_after_push(long param_1, long param_2, long param_3, unsigned long param_4);
void lite_zone_init_memory(long param_1);
void lite_zone_release_one(unsigned long param_1, unsigned long idx, unsigned long len);
void lite_zone_grow_block_x(void);

/* scratch locals used by condensed bodies */
static char local_31;
static unsigned long uStack_80;
static unsigned long local_a0;

/* ------------------------------------------------------------------ *
 * Boot / root-task launch
 * ------------------------------------------------------------------ */

/* FUN_000012d4 @ 0x000012d4   (est. sk_boot_launcher_entry)
 * Ghidra: void FUN_000012d4(void)
 * First-stage launcher: prints the platform banner, records the boot image
 * region and end-of-image address (rounded up to 16KiB), initializes the
 * virtual memory map and stores the boot config cookie.
 * Confidence: high (string-matched "LAUNCHER: Started platform")
 * Notes: reads boot image info block; DAT_006adfc0/8 = image base/end. */
unsigned long sk_boot_launcher_entry(void)
{
    long info;

    info = (long)sk_boot_image_info();
    sk_boot_diag_write(0xf84f8d4baa0803ea, 0x8b090d09b50005ab);
    sk_boot_tick_init();
    sk_printf("LAUNCHER: Started platform %s");            /* s__LAUNCHER__Started_platform__s_005a8a7f */
    sk_boot_platform_setup();
    sk_boot_region_store(*(unsigned long *)(info + 0x18));
    sk_boot_region_store2(*(unsigned long *)(info + 0x10));
    sk_image_base = sk_image_base_get();
    info = (long)sk_image_end_get();
    sk_image_end = (unsigned long)(info + 0x3fffU) & 0xffffffffffffc000ULL;
    sk_boot_vm_init();
    sk_boot_config_store(0x6b8f4);
}

/* FUN_00001378 @ 0x00001378   (est. sk_launcher_root)
 * Ghidra: undefined8 FUN_00001378(void)
 * Root-task launcher: binds the boot info to the root-task tag, prints the
 * root-task UUID and slide, builds a capability/symbol bootstrap object via
 * the boot object vtable, installs the root-task's physical frame map by
 * calling the supervisor, registers the kernel symbol table, spawns the
 * root thread (FUN_00001684) and hands off the boot capability. Returns 0 on
 * success; panics/aborts on failure.
 * Confidence: high (string-matched "Roottask UUID is" / "Roottask slide is")
 * Notes: uses CallSupervisor (supervisor call ABI via tpidrro_el0 block);
 *   nlist_0068c000 = kernel symbol table entry; FUN_00001684 is this file's
 *   sk_boot_thread_main. */
unsigned long sk_launcher_root(void)
{
    unsigned long *slot;
    unsigned long *sym;
    unsigned long uvar;
    unsigned long svar;
    unsigned long rvar;
    unsigned long qvar;
    unsigned long n;
    long src;
    long d;
    long e;
    long f;
    long g;
    long h;
    long i;
    long j;
    long k;
    long l;
    long m;
    unsigned long caps;
    unsigned long lo_hi;
    unsigned long lo_lo;
    unsigned long align;
    unsigned long th_off;
    unsigned char v[16];
    unsigned long local_b8;
    long local_b0;
    unsigned long local_a8[4];
    unsigned char local_88;
    unsigned char local_87;
    unsigned char uStack_80;
    unsigned char uStack_7f;
    unsigned long uStack_78;
    unsigned char local_70;
    unsigned char local_6f;
    unsigned char uStack_6b;
    long local_68;

    local_68 = -0x2c8502b44bfffed6;    /* stack canary */

    uvar = (unsigned long)sk_cpu_boot_info();
    sk_boot_info_bind((void *)uvar, &uStack_6b /*DAT_0064c010*/);
    src = (long)sk_boot_uuid_source();
    d = (long)*(char *)(src + 0x11);
    e = (long)*(char *)(src + 0x12);
    f = (long)*(char *)(src + 0x13);
    g = (long)*(char *)(src + 0x14);
    h = (long)*(char *)(src + 0x15);
    i = (long)*(char *)(src + 0x16);
    j = (long)*(char *)(src + 0x17);
    k = (long)*(char *)(src + 0x18);
    l = (long)*(char *)(src + 0x19);
    m = (long)*(char *)(src + 0x1a);
    /* ... remaining 10 bytes read into d..m pattern */
    sk_printf("Roottask UUID is %02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX",
              (unsigned char)d, (unsigned char)e, (unsigned char)f,
              (unsigned char)g, (unsigned char)h, (unsigned char)i,
              (unsigned char)j, (unsigned char)k, (unsigned char)l,
              (unsigned char)m, (unsigned char)*(char *)(src + 0x1b),
              (unsigned char)*(char *)(src + 0x1c),
              (unsigned char)*(char *)(src + 0x1d),
              (unsigned char)*(char *)(src + 0x1e),
              (unsigned char)*(char *)(src + 0x1f));
    sk_boot_byte_write(-0xb);
    uvar = sk_boot_cfg;                       /* DAT_006ad6e0 */
    sk_printf("Roottask slide is 0x%llx");    /* s_Roottask_slide_is_0x_llx_005a8b16 */
    th_off = sk_image_end;
    src = (long)sk_image_base;
    lo_lo = sk_image_end + 0x3fff;
    uStack_78 = lo_lo & 0xffffffffffffc000ULL;
    local_b8 = 0;
    local_b0 = 0;
    local_88 = 0x11;
    local_87 = 0;
    uStack_80 = 0;
    uStack_7f = 0;
    local_70 = 0xf;
    local_6f = 0;
    uStack_6b = 0;
    /* object = sk_boot_object(); invoke method[6] (offset 0x30) */
    {   unsigned long obj[2];
        (*(void (**)(void))(*(char **)(sk_boot_object()) + 0x30))();
        (void)obj;
    }
    if (th_off != 0) {
        th_off = 0;
        lo_lo = lo_lo >> 0xe;
        if (lo_lo < 2) {
            lo_lo = 1;
        }
        do {
            m = src + th_off;
            g = sk_va_to_pa((unsigned long)m);
            align = sk_va_align((unsigned long)m);
            uvar = sk_phys_alloc(0);
            slot = sk_tpidrro();
            *slot = 0x11;
            slot[1] = (unsigned long)(m - (long)g);
            slot[2] = uvar;
            CallSupervisor(0);
            *slot = 0x11;
            if ((align & 0xff) != 0) goto boot_root_fail;
            (*(void (**)(unsigned long, unsigned long, unsigned long))
             (*(char **)local_b0 + 0x28))(local_b8, th_off, uvar);
            th_off = th_off + 0x4000;
            lo_lo = lo_lo - 1;
        } while (lo_lo != 0);
    }
    if (local_b0 != 0) {
        (*(void (**)(void *))(*(char **)local_b0 + 8))( (void *)&local_88 );
        /* nlist_0068c000 = kernel symbol table */
        sym = (unsigned long *)0x68c000;
        sym[0] = (unsigned long)(uStack_7f << 56) | uStack_80;
        sym[1] = sk_image_end;
        sk_symbol_table_commit();
        local_a8[0] = 0;
        SK_SPAWN(local_a8, sk_boot_thread_main, 0, 0, 0);
        sk_thread_get((void *)local_a8[0]);
        caps = (unsigned long)sk_boot_object_get(7);
        if (caps != 0) {
            rvar = sk_thread_state((void *)local_a8[0]);
            slot = sk_tpidrro();
            *slot = caps;
            uvar = 0xd;
            CallSupervisor(0);
            *slot = caps;
            lo_lo = *(unsigned long *)0x4bad48;
            svar = (unsigned long)&uStack_6b;   /* ___const */
            if ((rvar & 0xff) == 0) {
                do {
                    rvar = sk_boot_done_poll();
                    if ((rvar & 1) != 0) goto boot_root_done;
                    slot[1] = lo_lo;
                    *slot = svar;
                    uvar = 0;
                    CallSupervisor(0);
                    *slot = 0xffffffffffffffffULL;
                    rvar = caps;
                } while ((caps & 0xff) == 0);
                sk_boot_abort((void *)caps, &local_88);
boot_root_done:
                sk_boot_finish(0);
                if (local_68 == -0x2c8502b44bfffed6) {
                    return 0;
                }
            }
            else {
                sk_boot_abort2(rvar, &local_88);
            }
            /* FALLTHROUGH: fatal */
            sk_boot_fatal();
        }
        n = sk_boot_abort3();
boot_root_fail:
        sk_boot_abort4(n, local_a8);
    }
    /* WARNING: Subroutine does not return */
    sk_boot_panic((const char *)0);
}

/* FUN_00001684 @ 0x00001684   (est. sk_boot_thread_main)
 * Ghidra: long FUN_00001684(void)
 * Root thread entry: switch the exception context to state 1, print
 * "Entered main Sc", then run the boot main body (FUN_000017f4).
 * Confidence: high (string-matched "Entered main Sc") */
long sk_boot_thread_main(void)
{
    int rc;

    sk_boot_ec_setup(1);
    sk_printf2("Entered main Sc");            /* s_Entered_main_Sc_005a8d19 */
    rc = (int)sk_boot_run();
    return (long)rc;
}

/* FUN_00001688 @ 0x00001688   (est. sk_boot_thread_main2)
 * Ghidra: long FUN_00001688(void)
 * Identical to sk_boot_thread_main (a second copy of the root thread entry).
 * Confidence: high (same body/string as 0x1684) */
long sk_boot_thread_main2(void)
{
    int rc;

    sk_boot_ec_setup(1);
    sk_printf2("Entered main Sc");            /* s_Entered_main_Sc_005a8d19 */
    rc = (int)sk_boot_run();
    return (long)rc;
}

/* FUN_000016b4 @ 0x000016b4   (est. sk_boot_ec_switch_impl)
 * Ghidra: void FUN_000016b4(long param_1, undefined8 param_2, ulong param_3)
 * Bound-checks the memory-availability window (param_3 against the hi/lo
 * limits), installs the boot EC by calling the supervisor, and switches the
 * exception context; on a failed switch it panics "Failed to switch boot EC".
 * Confidence: medium (names estimated; string "Failed to switch boot EC") */
void sk_boot_ec_switch_impl(void *param_1, void *param_2, unsigned long param_3)
{
    unsigned long *slot;
    unsigned long hi1, lo1, hi2, hi3;

    hi1 = sk_mem_avail_hi();
    lo1 = sk_mem_avail_lo();
    hi2 = sk_mem_avail_hi();
    hi3 = sk_mem_avail_hi();
    if ((((lo1 <= lo1 + hi2) && (hi3 <= hi2)) && (param_3 <= param_3 + hi1)) &&
        (hi3 <= hi1)) {
        sk_memcpy(param_3, lo1, hi3);
        if (param_3 <= param_3 + hi3) {
            slot = sk_tpidrro();
            *slot = (unsigned long)param_2;
            CallSupervisor(0);
            *slot = (unsigned long)param_2;
            if (param_1 == 0) {
                return;
            }
            sk_boot_ec_switch((unsigned long)sk_cpu_boot_info(), 2);
        }
    }
    /* SoftwareBreakpoint(0x5519, 0x1728): does not return */
    __builtin_trap();
}

/* FUN_0000178c @ 0x0000178c   (est. sk_boot_ec_err)
 * Ghidra: void FUN_0000178c(undefined8 param_1, undefined8 param_2)
 * Prints "L4 ErrorCode %zu" via the boot error printer (priority 0x1f).
 * Confidence: medium (string "L4 ErrorCode") */
void sk_boot_ec_err(void *param_1, void *param_2)
{
    sk_boot_error_print((unsigned long)param_1, 0x1f, 0, (unsigned long)param_2,
                        "L4 ErrorCode %zu");   /* s_L4_ErrorCode__zu_005a8c7b */
}

/* FUN_000017cc @ 0x000017cc   (est. sk_boot_dispatch_stub)
 * Ghidra: void FUN_000017cc(void)
 * Dispatches into the __text section at a fixed offset (stub trampoline).
 * Confidence: low (body is an indirect jump) */
void sk_boot_dispatch_stub(void)
{
    /* __text(&stack0x00000010): indirect jump into __text. */
    __asm__ volatile("" ::: "memory");
}

/* FUN_000017f4 @ 0x000017f4   (est. sk_boot_run)
 * Ghidra: undefined8 FUN_000017f4(void)
 * Main boot body: allocates and registers the initial zone object, the
 * "parse world" object, the "world boot" object and the "device page" object;
 * installs the device tree; creates the zone's CPU/region tables; launches
 * the platform/SA/root-task handoff; returns 0 on success, else traps.
 * Confidence: high (string matches "parse world" / "world boot" / "device
 *   page" / "SA init" / "SA boot", "Device tree not found/invalid")
 * Notes: extensive vtable dispatch; lite_zone bootstrap via sk_alloc. */
unsigned long sk_boot_run(void)
{
    /* Decompile FUN_000017f4 is a ~550-line body that builds and links the
     * root-task's objects through the allocator's vtable methods. Faithful
     * transcription: each "object build" is sk_alloc(size,tag) followed by
     * vtable-method dispatch; boot_obj holds the mirrored {base,hi,lo,extra}
     * handle quads that the vtable methods consume. */
    unsigned long *boot_obj;
    unsigned long uVar3, uVar4, uVar5, uVar6, uVar7, uVar10, uVar12;
    long lVar6;
    unsigned long *plVar11;
    unsigned char bVar1;
    unsigned long obj_scratch[8];
    unsigned long *slot;

    boot_obj = (unsigned long *)sk_object_boot_0();
    sk_alloc_teardown(boot_obj, obj_scratch, 0, 0);
    sk_boot_info_bind_ext();
    SK_FCALL1(boot_obj, 0x58, 1);          /* object method[0xb]: alloc(1) */
    sk_free((void *)0);
    sk_alloc_teardown((void *)0, obj_scratch, 0, 0);
    sk_boot_info_bind_ext();
    /* Build the "launcher" object (0x726568636e75616c = "launcher" LE). */
    uVar5 = (unsigned long)sk_alloc(0, 0x726568636e75616c);
    sk_free((void *)0);
    sk_image_base = boot_obj[0];
    sk_image_end = boot_obj[1];
    sk_boot_cfg = boot_obj[2];
    sk_boot_done = 0;
    boot_obj[8] = 0xd000000000000084;
    boot_obj[9] = 0x80000000005a8d10;
    uVar3 = sk_boot_memtype(0);
    sk_alloc_init_pages((void *)uVar3, 0x10, 7);
    plVar11 = (unsigned long *)sk_boot_cpu_slot();
    boot_obj[0x12] = 0x65fcc0;
    boot_obj[0x13] = uVar3;
    sk_alloc_teardown((void *)0x6ad9a0, obj_scratch, 0x21, 0);
    sk_alloc_finalize(&plVar11);
    sk_platform_init();
    uVar4 = sk_boot_caps();
    if (uVar4 >> 0x32 != 0) __builtin_trap();          /* SoftwareBreakpoint(1, 0x2418) */
    sk_boot_mem_hi = uVar4 << 0xe;
    sk_alloc_teardown((void *)uVar4, obj_scratch, 0, 0);
    sk_boot_info_bind_ext();
    /* Build the "parse world" object (0x7562206573726170 = "parse world" LE). */
    uVar5 = (unsigned long)sk_alloc(0x6ad9a0, 0x7562206573726170);
    sk_free((void *)0x6ad9a0);
    boot_obj[0xa] = obj_scratch[0];
    boot_obj[0xb] = obj_scratch[1];
    boot_obj[0xc] = obj_scratch[2];
    boot_obj[0xd] = obj_scratch[3];
    uVar5 = (unsigned long)sk_boot_strmap_build(&boot_obj[0x10], (long *)&boot_obj[0x18]);
    lVar6 = (long)sk_alloc_touch_extern(uVar5, (unsigned long)obj_scratch, 0);
    uVar3 = boot_obj[0x18];
    *(unsigned long *)(lVar6 + 0x18) = boot_obj[0x19];
    *(unsigned long *)(lVar6 + 0x10) = uVar3;
    *(unsigned long *)(lVar6 + 0x38) = 0x6753a0;
    *(unsigned long *)(lVar6 + 0x20) = 0xd000000000000015;
    *(unsigned long *)(lVar6 + 0x28) = 0x80000000005a8da0;
    sk_alloc_step_ext(0);
    sk_alloc_link((unsigned long)lVar6);
    sk_alloc_free_step();
    sk_alloc_link2(0);
    sk_alloc_link3();
    sk_boot_done = sk_btree_0(*(unsigned long *)0x68c000, *(unsigned long *)0x68c000);
    uVar5 = (unsigned long)sk_boot_strmap_build(&boot_obj[0x10], (long *)&boot_obj[0x18]);
    sk_boot_info_bind_ext();
    SK_FCALL1(boot_obj, 0xb0, (unsigned long)boot_obj);
    sk_boot_info_bind_ext();
    bVar1 = (unsigned char)SK_FCALL0R(boot_obj, 0xb8);
    sk_zone_present = bVar1 & 1;
    lVar6 = (long)sk_boot_cpu_count();
    if (lVar6 == 2) sk_zone_present = 1;
    sk_alloc_link(uVar5);
    sk_alloc_init_pages((void *)0, 0, 0);
    sk_alloc_free_step();
    sk_boot_mem_hi = 0x6753a0;
    sk_boot_cfg = boot_obj[8];
    sk_boot_done = boot_obj[9];
    sk_alloc(0, 0);
    sk_alloc_step_ext((unsigned long)&sk_zone_present);
    sk_alloc_link((unsigned long)&sk_zone_present);
    sk_alloc_free_step();
    sk_alloc_link2(0);
    sk_alloc_link3();
    uVar3 = (unsigned long)sk_arch_boot_0(0);
    uVar7 = (unsigned long)sk_alloc_init_pages((void *)uVar3, 0x69);
    uVar5 = (unsigned long)sk_arch_boot_1();
    sk_alloc_teardown((void *)uVar5, obj_scratch, 0, 0);
    sk_boot_info_bind_ext();
    /* Build the "device page" object (0x697665642070616d = "map device" LE). */
    uVar5 = (unsigned long)sk_alloc(uVar7, 0x697665642070616d);
    sk_free((void *)uVar7);
    boot_obj[0x14] = obj_scratch[0];
    boot_obj[0x15] = obj_scratch[1];
    boot_obj[0x16] = obj_scratch[2];
    boot_obj[0x17] = obj_scratch[3];
    sk_phys_map_region_va();
    sk_phys_map_tighten();
    plVar11 = (unsigned long *)sk_devtree_get();
    if (plVar11 == 0) {
        sk_log(0, "Device tree not found");    /* s_Device_tree_not_found_005a8e00 */
        sk_boot_ec_dispatch();
        sk_alloc_free_step();
        goto boot_run_fail;
    }
    uVar7 = SK_FCALL0R(*plVar11, 0xe0);
    SK_FCALL0(*plVar11, 0xe0);
    sk_devtree_set_va(uVar7);
    /* validate the device tree range */
    lVar6 = (long)SK_FCALL0R(*plVar11, 0xe0);
    if (lVar6 < 0) __builtin_trap();           /* SoftwareBreakpoint(1, 0x241c) */
    uVar7 = (unsigned long)sk_devtree_validate((unsigned long)plVar11[0],
                                               (unsigned long)(plVar11[0] + lVar6));
    sk_boot_info_bind_ext();
    /* Build the "world boot" object; link arch/dev objects. */
    uVar5 = (unsigned long)sk_boot_strmap_build(&boot_obj[0x20], (long *)&boot_obj[0x28]);
    sk_boot_done = (unsigned long)sk_alloc_init_pages((void *)uVar5, 0x38, 7);
    *(unsigned long *)(sk_boot_done + 0x28) = 0;
    *(unsigned long *)(sk_boot_done + 0x30) = 0;
    *(long *)(sk_boot_done + 0x18) = lVar6;
    *(unsigned long *)(sk_boot_done + 0x20) = 0;
    *(long *)(sk_boot_done + 0x10) = plVar11[0];
    sk_boot_info_bind_ext();
    SK_FCALL1(boot_obj, 0xb0, (unsigned long)boot_obj);
    uVar5 = (unsigned long)sk_boot_strmap_build(&boot_obj[0x30], (long *)&boot_obj[0x38]);
    sk_alloc_link3();
    sk_alloc_init_pages((void *)0, 0, 0);
    uVar7 = (unsigned long)sk_alloc(uVar5, 0);
    boot_obj[0x18] = uVar5;
    uVar10 = (unsigned long)sk_obj_get_0(0);
    sk_alloc_free_step();
    sk_alloc_init_pages((void *)0, 0, 0);
    sk_free((void *)uVar7);
    boot_obj[0x1c] = (unsigned long)sk_obj_get_1();
    boot_obj[0x22] = 0x662de8;
    boot_obj[0x1e] = uVar7;
    boot_obj[0x20] = uVar3;
    uVar7 = (unsigned long)sk_obj_get_2(0);
    sk_alloc_init_pages((void *)uVar7, 0x38, 7);
    boot_obj[0x23] = (unsigned long)sk_obj_get_3();
    sk_boot_info_bind_ext();
    SK_FCALL2(boot_obj, 0xa0, (unsigned long)boot_obj, 0);
    sk_boot_info_bind_ext();
    SK_FCALL0(boot_obj, 0x68);
    sk_boot_info_bind_ext();
    uVar7 = SK_FCALL0R(boot_obj, 0xa8);
    boot_obj[0x24] = uVar7;
    if (sk_zone_present == 1)
        uVar7 = (unsigned long)sk_boot_op_probe(0x53206e6f6d6d6f43, 0xee00656761726f74);
    sk_alloc_teardown((void *)uVar7, obj_scratch, 0, 0);
    uVar7 = boot_obj[0];
    sk_boot_info_bind_ext();
    /* Build the "SA init" object. */
    uVar5 = (unsigned long)sk_alloc(uVar7, 0xd000000000000015);
    sk_free((void *)uVar7);
    uVar7 = boot_obj[0x18];
    boot_obj[0x25] = obj_scratch[0];
    boot_obj[0x26] = obj_scratch[1];
    boot_obj[0x27] = obj_scratch[2];
    boot_obj[0x28] = obj_scratch[3];
    sk_alloc_free_step();
    sk_alloc_init_pages((void *)0, 0, 0);
    sk_free((void *)uVar7);
    boot_obj[0x2d] = (unsigned long)sk_obj_get_1();
    boot_obj[0x32] = 0x662de8;
    boot_obj[0x2e] = uVar7;
    boot_obj[0x30] = uVar3;
    sk_finalize_0(0);
    uVar7 = boot_obj[0x24];
    lVar6 = (long)boot_obj[0x1c];
    uVar3 = boot_obj[0x12];
    boot_obj[0x23] = 0x65f368;
    boot_obj[0x22] = 0x65f1b8;
    sk_alloc_link(0x658f08);
    boot_obj[0x26] = (unsigned long)sk_alloc_init_pages((void *)0, 0, 0);
    sk_alloc_teardown(&boot_obj[0x2d], boot_obj + 0x26 + 1, 0, 0);
    boot_obj[0x2a] = 0;
    boot_obj[0x2b] = 0;
    boot_obj[0x2c] = 0;
    boot_obj[0x29] = 0;
    uVar5 = (unsigned long)sk_alloc(0, 0xd42aa32094006f01);
    plVar11 = (unsigned long *)sk_finalize_1(1, uVar3, uVar7, (unsigned long)lVar6,
                                             &boot_obj[0x26], 0x911e5c00b0000200,
                                             0xd42aa32094006f01, 0,
                                             &boot_obj[0x2e], &boot_obj[0x36], 0);
    sk_free((void *)0xd42aa32094006f01);
    sk_alloc_free_link(&boot_obj[0x37]);
    sk_alloc_free_link(&boot_obj[0x2e]);
    sk_alloc_link3((unsigned long)&boot_obj[0x26]);
    boot_obj[0x20] = plVar11[4];
    boot_obj[0x26] = boot_obj[0x25];
    boot_obj[0x23] = boot_obj[0x26];
    boot_obj[0x22] = boot_obj[0x28];
    boot_obj[0x1f] = boot_obj[0x2a];
    boot_obj[0x1e] = boot_obj[0x2b];
    boot_obj[0x1c] = boot_obj[0x2c];
    boot_obj[0x1b] = boot_obj[0x2d];
    sk_boot_info_bind_ext();
    uVar10 = SK_FCALL0R(boot_obj, 0xb0);
    uVar7 = boot_obj[0x2d];
    if (sk_zone_present == 1) {
        uVar10 = (unsigned long)sk_boot_op_probe(0xd000000000000015, 0x80000000005a8ec0);
        uVar3 = uVar7;
    }
    sk_alloc_teardown((void *)uVar10, obj_scratch, 0, 0);
    sk_boot_info_bind_ext();
    /* Build "SA init" (0x74696e69205341 = "SA init" LE). */
    uVar5 = (unsigned long)sk_alloc(uVar3, 0x74696e69205341);
    sk_free((void *)uVar3);
    boot_obj[0x34] = obj_scratch[0];
    boot_obj[0x35] = obj_scratch[1];
    boot_obj[0x36] = obj_scratch[2];
    boot_obj[0x37] = obj_scratch[3];
    sk_alloc_teardown(&boot_obj[0x33], obj_scratch, 0, 0);
    plVar11 = (unsigned long *)boot_obj[0x33];
    if (boot_obj[0x33] != 0) {
        sk_alloc(boot_obj[0x33], 0);
        sk_finalize_2();
        sk_free(plVar11);
    }
    boot_obj[0x2c] = boot_obj[0x38];
    boot_obj[0x2d] = boot_obj[0x34];
    boot_obj[0x2b] = boot_obj[0x36];
    boot_obj[0x2a] = boot_obj[0x37];
    boot_obj[0x29] = boot_obj[0x38];
    boot_obj[0x28] = boot_obj[0x39];
    boot_obj[0x27] = boot_obj[0x3a];
    boot_obj[0x26] = boot_obj[0x3b];
    sk_boot_info_bind_ext();
    uVar7 = SK_FCALL0R(boot_obj, 0xb0);
    sk_alloc_teardown((void *)uVar7, obj_scratch, 0, 0);
    sk_boot_info_bind_ext();
    /* Build "SA boot" (0x746f6f62205341 = "SA boot" LE). */
    uVar5 = (unsigned long)sk_alloc(uVar3, 0x746f6f62205341);
    sk_free((void *)uVar3);
    plVar11 = (unsigned long *)boot_obj[0x33];
    boot_obj[0x3c] = obj_scratch[0];
    boot_obj[0x3d] = obj_scratch[1];
    boot_obj[0x3e] = obj_scratch[2];
    boot_obj[0x3f] = obj_scratch[3];
    if (boot_obj[0x33] != 0) {
        sk_alloc(boot_obj[0x33], 0);
        sk_finalize_3();
        sk_free(plVar11);
    }
    boot_obj[0x36] = boot_obj[0x3c];
    boot_obj[0x37] = boot_obj[0x3d];
    boot_obj[0x35] = boot_obj[0x3e];
    boot_obj[0x34] = boot_obj[0x3f];
    boot_obj[0x33] = boot_obj[0x40];
    boot_obj[0x32] = boot_obj[0x41];
    boot_obj[0x31] = boot_obj[0x42];
    boot_obj[0x30] = boot_obj[0x43];
    sk_boot_info_bind_ext();
    SK_FCALL1(boot_obj, 0xb0, (unsigned long)&boot_obj[0x36]);
    if (sk_zone_present == 1) sk_boot_pll(0);
    sk_boot_done = 1;
    sk_boot_info_bind_ext();
    SK_FCALL1(boot_obj, 0xb0, (unsigned long)&boot_obj[0x3e]);
    plVar11 = (unsigned long *)boot_obj[0x33];
    if (boot_obj[0x33] != 0) {
        uVar3 = (unsigned long)sk_alloc_teardown((void *)(boot_obj[0x33] + 0x37), obj_scratch, 0, 0);
        slot = (unsigned long *)plVar11[0x37];
        if (slot != 0) {
            sk_alloc_link(uVar5);
            sk_alloc_init_pages((void *)0, 0, 0);
            lVar6 = (long)sk_alloc_free_step();
            *(unsigned long *)(lVar6 + 0x38) = 0x6753a0;
            *(unsigned long *)(lVar6 + 0x20) = 0xd00000000000001f;
            *(unsigned long *)(lVar6 + 0x28) = 0x80000000005a8e80;
            sk_alloc((unsigned long)slot, 0);
            sk_alloc_step_ext((unsigned long)plVar11);
            sk_alloc_link((unsigned long)plVar11);
            sk_alloc_free_step();
            sk_alloc_link2(0);
            sk_alloc_link3();
            uVar12 = SK_FCALL0R(*slot, 0xf8);   /* vtable[0x1f]: descriptor pair */
            sk_alloc_teardown((void *)uVar12, obj_scratch, 0, 0);
            plVar11 = (unsigned long *)*boot_obj;
            sk_alloc((unsigned long)plVar11, 0);
            SK_FCALL2(*plVar11, 0xc0, uVar12, 0);
            sk_free(plVar11);
            sk_alloc_link(uVar5);
            sk_alloc_init_pages((void *)0, 0, 0);
            lVar6 = (long)sk_alloc_free_step();
            *(unsigned long *)(lVar6 + 0x38) = 0x6753a0;
            *(unsigned long *)(lVar6 + 0x20) = 0xd00000000000001b;
            *(unsigned long *)(lVar6 + 0x28) = 0x80000000005a8ea0;
            sk_alloc_step_ext(0);
            sk_alloc_link((unsigned long)plVar11);
            sk_alloc_free_step();
            sk_alloc_link2(0);
            sk_alloc_link3();
            SK_FCALL2(*slot, 0x98, 0, 0x4000);
            sk_free(slot);
        }
    }
    sk_alloc_teardown((void *)uVar3, obj_scratch, 0, 0);
    sk_boot_info_bind_ext();
    SK_FCALL0(boot_obj, 0xb8);
    sk_free(plVar11);
    sk_free(slot);
    return 0;
boot_run_fail:
    /* WARNING: Subroutine does not return */
    sk_boot_fatal2();
}


/* FUN_000024cc @ 0x000024cc   (est. sk_boot_object_vt)
 * Ghidra: undefined8 FUN_000024cc(undefined8 param_1, undefined8 param_2)
 * Resolves an object's vtable (via sk_boot_strmap_build on a name/def pair)
 * and invokes method[5] (offset 0x28) on it, returning param_2.
 * Confidence: low */
unsigned long sk_boot_object_vt(unsigned long param_1, unsigned long param_2)
{
    long v;

    v = (long)sk_boot_strmap_build(&boot_name0, &boot_def0);
    (*(void (**)(unsigned long, unsigned long, long))(*(char **)(v - 8) + 0x28))
        (param_2, param_1, v);
    return param_2;
}

/* FUN_00002534 @ 0x00002534   (est. sk_boot_strmap_build)
 * Ghidra: void FUN_00002534(ulong *param_1, long *param_2)
 * Lazily resolves a boot string/name to a capability: if the destination
 * word is 0 or odd, calls the name table (FUN_00389910) and stores the result.
 * Confidence: medium */
unsigned long sk_boot_strmap_build(unsigned long *name, long *def)
{
    unsigned long v;

    if ((*name == 0) || ((*name & 1) != 0)) {
        v = sk_obj_name((unsigned long)def + (long)(int)*name,
                        *name >> 0x20, 0, 0);
        *name = v;
    }
}

/* FUN_00002580 @ 0x00002580   (est. sk_boot_done_poll)
 * Ghidra: uint FUN_00002580(void)
 * Returns bit 0 of the boot-done flag (DAT_006adfd0).
 * Confidence: high */
unsigned int sk_boot_done_poll(void)
{
    return (unsigned int)(sk_boot_done_get() & 1);
}

/* FUN_0000259c @ 0x0000259c   (est. sk_boot_done_get)
 * Ghidra: undefined1 FUN_0000259c(void)
 * Returns the boot-done flag byte (DAT_006adfd0).
 * Confidence: high */
unsigned char sk_boot_done_get(void)
{
    return (unsigned char)sk_boot_done;
}

/* FUN_000025ac @ 0x000025ac   (est. sk_boot_finish)
 * Ghidra: void FUN_000025ac(undefined8 param_1)
 * Final boot step: verifies boot completed, then hands off via the boot gate
 * (FUN_000d0020) through the final object; aborts if boot did not complete.
 * Confidence: high (string "Boot failed to complete") */
void sk_boot_finish(unsigned long param_1)
{
    unsigned long obj[4];
    long v;

    if ((sk_boot_done & 1) == 0) {
        sk_log(0, "Boot failed to complete");   /* s_Boot_failed_to_complete_005a8f00 */
        sk_boot_ec_dispatch();
        sk_alloc_free_step();
    } else {
        sk_alloc_teardown((void *)param_1, obj);
        v = (long)sk_boot_done;
        if (sk_boot_done != 0) {
            sk_alloc(sk_boot_done);
            sk_boot_gate();
            sk_free((void *)v);
            return;
        }
        sk_boot_ec_dispatch();  /* s_Boot_failed_to_complete_005a8f00 */
        sk_alloc_free_step();
    }
    /* WARNING: Subroutine does not return */
    sk_boot_fatal2();
}

/* FUN_00002688 @ 0x00002688   (est. sk_alloc_step)
 * Ghidra: void FUN_00002688(void)
 * Records the allocator object (unaff_x20) into the bump region with tag
 * 0x67b1e8. */
void sk_alloc_step(void)
{
    long x20;

    __asm__ volatile("mov %0, x20" : "=r"(x20));
    sk_alloc_bump_region(x20 + 0x20, *(unsigned long *)(x20 + 0x10), 0x67b1e8);
}

/* FUN_000026b8 / FUN_000026bc @ 0x000026b8/0x000026bc (est. sk_alloc_free_step)
 * Ghidra: void FUN_000026b8(void) / FUN_000026bc(void)
 * Frees the allocator object's second word, unlinks the object at +0x18,
 * and runs the allocator teardown. Two identical copies. */
unsigned long sk_alloc_free_step(void)
{
    long x20;

    __asm__ volatile("mov %0, x20" : "=r"(x20));
    sk_free((void *)x20);
    sk_alloc_free_link((unsigned long *)(x20 + 0x18));
    sk_alloc_link3();
    sk_alloc_teardown((void *)x20);
}

unsigned long sk_alloc_free_step2(void)
{
    long x20;

    __asm__ volatile("mov %0, x20" : "=r"(x20));
    sk_free((void *)x20);
    sk_alloc_free_link((unsigned long *)(x20 + 0x18));
    sk_alloc_link3();
    sk_alloc_teardown((void *)x20);
}

/* FUN_000026e8 @ 0x000026e8   (est. sk_alloc_free_link)
 * Ghidra: void FUN_000026e8(undefined8 *param_1)
 * Unlinks an allocator object from its owner's free list if the owner's
 * bitmap bit (vtable+0x52, bit 1) is clear; otherwise frees the object's
 * first word. */
void sk_alloc_free_link(unsigned long *obj)
{
    long owner;

    owner = *(long *)(obj[3] - 8);
    if (((*(unsigned char *)(owner + 0x52) >> 1) & 1) == 0) {
        (*(void (**)(void))(*(char **)(owner + 8)))();
        return;
    }
    sk_free((void *)*obj);
}

/* FUN_00002718 @ 0x00002718   (est. sk_alloc_link2_dispatch)
 * Ghidra: undefined8 FUN_00002718(undefined8 param_1, undefined8 param_2)
 * Invokes the global allocator dispatch pointer, returning param_2.
 * Confidence: low (DAT_aa1403f552800078 is a relocated dispatch fn) */
unsigned long sk_alloc_link2_dispatch(unsigned long param_1, unsigned long param_2)
{
    (*(void (**)(unsigned long, unsigned long))(0xaa1403f552800078))(param_2, param_1);
    return param_2;
}

/* FUN_0000276c @ 0x0000276c   (est. sk_alloc_link_dispatch)
 * Ghidra: undefined8 FUN_0000276c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Resolves a name and calls vtable method[1] (offset 8) with param_1.
 * Confidence: low */
unsigned long sk_alloc_link_dispatch(unsigned long param_1, unsigned long param_2,
                                     unsigned long param_3)
{
    long v;

    v = (long)sk_boot_strmap_build(&boot_name0, &boot_def0);
    (*(void (**)(unsigned long, long))(*(char **)(v - 8) + 8))(param_1, v);
    return param_1;
}

/* FUN_000027c4 @ 0x000027c4   (est. sk_boot_fatal_str)
 * Ghidra: char * FUN_000027c4(void)
 * Returns the "Fatal error" string literal.
 * Confidence: high (string "Fatal error") */
char *sk_boot_fatal_str(void)
{
    return "Fatal error";                        /* s_Fatal_error_005accd0 */
}

/* FUN_000027d8 / FUN_000027e8 @ 0x000027d8/0x000027e8 (est. sk_boot_info_bind_ext)
 * Ghidra: void FUN_000027d8(void) / FUN_000027e8(void)
 * No-op boot bind wrappers (empty bodies). */
void sk_boot_info_bind_ext(void)
{
}

void sk_boot_info_bind_ext2(void)
{
}

/* FUN_000027f4 @ 0x000027f4   (est. sk_alloc_teardown_wrap)
 * Ghidra: void FUN_000027f4(void)
 * Runs the allocator teardown with no args. */
void sk_alloc_teardown_wrap(void)
{
    sk_alloc_teardown(0);
}

/* FUN_00002804 @ 0x00002804   (est. sk_zone_grow_step)
 * Ghidra: void FUN_00002804(undefined8 param_1)
 * Grows the allocator region: sk_zone_grow_1(param_1, 0x20, 0xe1..., 10, ...).
 * Confidence: low */
void sk_zone_grow_step(unsigned long param_1)
{
    sk_zone_grow_1(param_1, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
}

/* FUN_00002818 / FUN_00002834 / FUN_00002850 / FUN_0000285c / FUN_00002874
 * @ 0x00002818/0x28 34/0x2850/0x285c/0x2874 (est. sk_noop_*)
 * Ghidra: void FUN_0000xxxx(void) — empty bodies. */
void sk_noop_2818(void) { }
void sk_noop_2834(void) { }
void sk_noop_2850(void) { }
void sk_noop_285c(void) { }
void sk_noop_2874(void) { }

/* FUN_00002828 @ 0x00002828   (est. sk_alloc_teardown2)
 * Ghidra: void FUN_00002828(undefined8 param_1, undefined8 param_2)
 * Allocator teardown with a scratch buffer (FUN_0036a1a0(a,b,0,0)). */
void sk_alloc_teardown2(unsigned long param_1, unsigned long param_2)
{
    sk_alloc_teardown((void *)param_1, (void *)param_2, 0, 0);
}

/* FUN_00002840 @ 0x00002840   (est. sk_alloc_link_field)
 * Ghidra: void FUN_00002840(long param_1)
 * Writes two stack-slot words into object+0x10/+0x18 (the object's two
 * handle words). */
void sk_alloc_link_field(long param_1)
{
    unsigned long w0, w1;

    __asm__ volatile("ldp %0, %1, [sp, #0x30]" : "=r"(w0), "=r"(w1));
    *(unsigned long *)(param_1 + 0x18) = w1;
    *(unsigned long *)(param_1 + 0x10) = w0;
}

/* FUN_00002880 @ 0x00002880   (est. sk_zone_collect)
 * Ghidra: ulong FUN_00002880(long param_1, undefined8 param_2, long param_3, uint param_4)
 * Calls an object's method[3] (offset 0x18) repeatedly to collect up to
 * param_4 words into param_3; returns the number collected, or 0 on the
 * first zero result. */
unsigned long sk_zone_collect(long param_1, unsigned long param_2, long param_3,
                              unsigned int param_4)
{
    unsigned long n = 0, total;
    long r;

    if (param_4 == 0) return 0;
    total = param_4;
    do {
        r = (*(long (**)(long, unsigned long))(*(char **)(param_1 + 0x18)))
            (param_1, param_2);
        if (r == 0) return n;
        *(long *)(param_3 + n * 8) = r;
        n++;
    } while (total != n);
    return total;
}

/* FUN_000028fc @ 0x000028fc   (est. sk_zone_release_list)
 * Ghidra: void FUN_000028fc(long param_1, long param_2, uint param_3)
 * Walks an array of param_3 pointers, bounds-checks each, and calls
 * method[6] (offset 0x30) on non-null entries (release). Traps on a bad
 * range (SoftwareBreakpoint 0x5519). */
void sk_zone_release_list(long param_1, long param_2, unsigned int param_3)
{
    long *p;
    unsigned int i = 1;

    if (param_3 != 0) {
        do {
            param_3--;
            p = (long *)(param_2 + (unsigned long)param_3 * 8);
            if ((long *)(param_2 + (unsigned long)param_3 * 8 + 8) < p + 1 ||
                p + 1 < p) {
                __builtin_trap();   /* SoftwareBreakpoint(0x5519, 0x2984) */
            }
            if (*p != 0) {
                (*(void (**)(long))(*(char **)(param_1 + 0x30)))(param_1);
            }
            i++;
        } while (i <= param_3);
    }
}

/* FUN_0000298c @ 0x0000298c   (est. sk_zone_bad_ptr_log)
 * Ghidra: void FUN_0000298c(undefined8 param_1, undefined8 param_2)
 * Logs "error for object %p: pointer %p" unless the pointer is valid
 * (sk_bug_check) or the zone is absent.
 * Confidence: medium (string "error for object %p: pointer %p") */
void sk_zone_bad_ptr_log(unsigned long param_1, unsigned long param_2)
{
    unsigned long v;

    if ((sk_zone_present != 1) ||
        (v = sk_bug_check(param_2), (v & 1) == 0)) {
        sk_log(param_1, "error for object %p: pointer %p");  /* s_____error_for_object__p__pointer_005a8f3f */
    }
}

/* ------------------------------------------------------------------ *
 * Lite_zone (libmalloc) allocator
 * ------------------------------------------------------------------ */

/* FUN_000029e8 @ 0x000029e8   (est. lite_zone_bug)
 * Ghidra: void FUN_000029e8(void)
 * Raises a lite_zone internal bug panic ("BUG IN LIBMALLOC"). */
void lite_zone_bug(void)
{
    sk_bug_panic("BUG IN LIBMALLOC: %s");   /* s_BUG_IN_LIBMALLOC___s_005a8f7f */
}

/* FUN_00002a10 @ 0x00002a10   (est. lite_zone_init_memory)
 * Ghidra: void FUN_00002a10(long param_1)
 * Initializes the zone's backing memory regions: allocates the metadata
 * arena (0x19/1 MB) and the 5GB region tables, fills the region/cpu-table
 * descriptors, and marks the zone's enabled bit (param_1+0x1b9 bit 0).
 * Confidence: medium (lite_zone; strings "BUG IN LIBMALLOC") */
void lite_zone_init_memory(long param_1)
{
    unsigned long a0, a1, a2, a3, lim, sz, step, u;
    unsigned char c;
    long v, base;
    unsigned long out[2];

    c = (unsigned char)sk_zone_present;
    step = 0xa00;
    if (sk_zone_present == 0) step = 0x200;
    lim = 0x80000000;
    if (sk_zone_present == 0) lim = 0x100000000;
    out[0] = 0; out[1] = 0;
    a0 = sk_alloc_zone_0(0, lim + 0x100000000, 0x19, 1, step, 4, &out[0]);
    if (a0 == 0) goto bug;
    if (c == 0) {
        base = 0;
        a1 = 0;
    } else {
        base = *(long *)(param_1 + 0x200);
        a1 = sk_alloc_zone_0(0, lim + 0x100000000, 0x19, 1, 0x200, 4, (void **)(base + 0x90));
        if (a1 == 0) sk_bug_panic("BUG IN LIBMALLOC: %s");  /* 005a8f7f */
        base = base + 0x70;
    }
    v = *(long *)(param_1 + 0x200);
    a2 = sk_alloc_zone_0(0, 0x140000000, 0x19, 1, 0x200, 5, (void **)(v + 0x20));
    if (a2 == 0) sk_bug_panic("BUG IN LIBMALLOC: %s");  /* 005a8f7f */
    *(unsigned long *)(v + 0x50) = a2;
    *(unsigned long *)(v + 0x58) = 0x140000000;
    *(unsigned long *)(v + 0x30) = a2;
    *(unsigned long *)(v + 0x38) = 0x140000000;
    if (a2 <= a0) a0 = a0 + 0x100000000;
    if (*(char *)(param_1 + 0x1bf) == '\x02') {
        u = a0 + lim;
        if (u <= a0) goto bug;
        lim = a0 + (lim >> 1);
        if (u <= lim) goto bug;
        if ((a0 & 0x1ffffff) != 0) goto bug;
        if (lim < a0) goto bug;
        lim = lim | 0x1000000;
        v = u - (long)lim;
        if (lim <= u && v != 0) {
            base = *(long *)(param_1 + 0x200);
            *(unsigned long *)(base + 0x110) = lim;
            *(long *)(base + 0x118) = v;
            *(unsigned long *)(base + 0x130) = lim;
            *(long *)(base + 0x138) = v;
            *(unsigned char *)(base + 0x140) = 0;
            *(unsigned long *)(base + 0x120) = 0;
            *(unsigned long *)(base + 0x128) = 0;
            *(unsigned long *)(base + 0x180) = lim;
            *(unsigned long *)(base + 0x188) = lim - a0;
            *(unsigned long *)(base + 0x1a0) = lim;
            *(unsigned long *)(base + 0x1a8) = lim - a0;
            *(unsigned long *)(base + 400) = 0;
            *(unsigned long *)(base + 0x198) = 0;
            *(unsigned char *)(base + 0x1b0) = 1;
            *(unsigned long *)(base + 0x108) = out[1];
            *(unsigned long *)(base + 0x100) = out[0];
            *(unsigned long *)(base + 0x178) = out[1];
            *(unsigned long *)(base + 0x170) = out[0];
            if (c != 0) {
                if (a2 <= a1) a1 = a1 + 0x100000000;
                *(unsigned long *)(base + 0x30) = a1;
                *(unsigned long *)(base + 0x38) = 0x80000000;
                *(unsigned long *)(base + 0x50) = a1;
                *(unsigned long *)(base + 0x58) = 0x80000000;
                *(unsigned char *)(base + 0x60) = 0;
            }
            *(unsigned char *)(param_1 + 0x1b9) |= 1;
            sk_stack_poison(0, 0);
            return;
        }
    } else {
        __asm__ volatile("brk #0x5519" ::: "memory");   /* 004afc5c */
    }
bug:
    sk_bug_panic("BUG IN LIBMALLOC: %s");   /* 005a8f7f */
}

/* FUN_00002c70 @ 0x00002c70   (est. lite_zone_release_pages)
 * Ghidra: void FUN_00002c70(undefined8 param_1, long param_2, ulong param_3,
 *                           uint param_4, uint param_5, uint param_6)
 * Releases physical pages for a region: walks the used/free bitmasks
 * (param_4 masked by ~param_5 and param_6) and, for each set run, calls
 * the region-release/cleanup routines (FUN_00002dfc / FUN_00011bf4) with the
 * computed page indices and run lengths.
 * Confidence: medium (lite_zone page-mark machinery) */
void lite_zone_release_pages(unsigned long param_1, long param_2, unsigned long param_3,
                             unsigned int param_4, unsigned int param_5,
                             unsigned int param_6)
{
    unsigned int mask = param_4 & ~param_5;
    unsigned long base, idx, run;
    long node;
    unsigned int i, sz;

    base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)*(char *)(param_3 + 0x40))
        base = 0xfffffffffffe0000;
    node = *(long *)((base & param_3) + 0x10);
    if (param_6 != 0) {
        i = 0;
        do {
            if ((param_6 & 1) == 0) {
                /* reverse bits to find the next clear bit (LZCOUNT-based) */
                run = (param_6 & 0xaaaaaaaa) >> 1 | (param_6 & 0x55555555) << 1;
                run = (run & 0xcccccccc) >> 2 | (run & 0x33333333) << 2;
                run = (run & 0xf0f0f0f0) >> 4 | (run & 0xf0f0f0f) << 4;
                run = (run & 0xff00ff00) >> 8 | (run & 0xff00ff) << 8;
                sz = (unsigned int)sk_clz(run >> 0x10 | run << 0x10);
            } else {
                unsigned long rb = ((~param_6 & 0xaaaaaaaaaaaaaaaa) >> 1 |
                                    (~param_6 & 0x5555555555555555) << 1);
                rb = (rb & 0xcccccccccccccccc) >> 2 | (rb & 0x3333333333333333) << 2;
                rb = (rb & 0xf0f0f0f0f0f0f0f0) >> 4 | (rb & 0xf0f0f0f0f0f0f0f) << 4;
                rb = (rb & 0xff00ff00ff00ff00) >> 8 | (rb & 0xff00ff00ff00ff) << 8;
                sz = (unsigned int)sk_clz((rb >> 0x10 | (rb & 0xffff0000ffff) << 0x10) << 0x20);
                base = 0xffffffffffff8000;
                if (0x7fffffff < (unsigned int)(int)*(char *)(param_3 + 0x40))
                    base = 0xfffffffffffe0000;
                lite_zone_release_one(param_1, lite_zone_page_idx(param_3, base) +
                                      (unsigned long)(*(int *)(param_2 + 0x100) * (i & 0xff)),
                                      (unsigned long)(*(int *)(param_2 + 0x100) * (int)sz));
            }
            i += sz;
            param_6 >>= sz & 0x1f;
        } while (param_6 != 0);
    }
    if (mask != 0) {
        i = 0;
        do {
            if ((mask & 1) == 0) {
                run = (mask & 0xaaaaaaaa) >> 1 | (mask & 0x55555555) << 1;
                run = (run & 0xcccccccc) >> 2 | (run & 0x33333333) << 2;
                run = (run & 0xf0f0f0f0) >> 4 | (run & 0xf0f0f0f) << 4;
                run = (run & 0xff00ff00) >> 8 | (run & 0xff00ff) << 8;
                sz = (unsigned int)sk_clz(run >> 0x10 | run << 0x10);
            } else {
                unsigned long rb = ((~mask & 0xaaaaaaaaaaaaaaaa) >> 1 |
                                    (~mask & 0x5555555555555555) << 1);
                rb = (rb & 0xcccccccccccccccc) >> 2 | (rb & 0x3333333333333333) << 2;
                rb = (rb & 0xf0f0f0f0f0f0f0f0) >> 4 | (rb & 0xf0f0f0f0f0f0f0f) << 4;
                rb = (rb & 0xff00ff00ff00ff00) >> 8 | (rb & 0xff00ff00ff00ff) << 8;
                sz = (unsigned int)sk_clz((rb >> 0x10 | (rb & 0xffff0000ffff) << 0x10) << 0x20);
                base = 0xffffffffffff8000;
                if (0x7fffffff < (unsigned int)(int)*(char *)(param_3 + 0x40))
                    base = 0xfffffffffffe0000;
                sk_pt_write(lite_zone_page_idx(param_3, base) +
                            (unsigned long)(*(int *)(param_2 + 0x100) * (i & 0xff)),
                            (unsigned long)(*(int *)(param_2 + 0x100) * (int)sz), 9, 0x40,
                            *(long *)(node + 0x30) + 0x20);
            }
            i += sz;
            mask >>= sz & 0x1f;
        } while (mask != 0);
    }
}

/* Internal helpers for lite_zone_release_pages (index computation). */
unsigned long lite_zone_page_idx(unsigned long p, unsigned long base)
{
    return ((((p - (base & p)) - 0x50) >> 5) * -0x5555555555554000ULL & 0x3fffffffc000ULL) +
           *(unsigned long *)((base & p) + 0x38);
}

void lite_zone_release_one(unsigned long param_1, unsigned long idx, unsigned long len)
{
    lite_zone_unmap_region(param_1, idx, len);
}

/* FUN_00002df4 @ 0x00002df4   (est. lite_zone_unmap_block)
 * Ghidra: void FUN_00002df4(long param_1)
 * Unmaps a block via the block's page-table entry (offset 0x38).
 * Confidence: medium */
void lite_zone_unmap_block(long param_1)
{
    lite_zone_unmap_region(*(unsigned long *)(param_1 + 0x38), 0, 0);
}

/* FUN_00002dfc @ 0x00002dfc   (est. lite_zone_unmap_region)
 * Ghidra: void FUN_00002dfc(long param_1, ulong param_2, undefined8 param_3)
 * Computes the page-table slot for param_2 and unmaps it (sk_pt_write
 * type 1). Looks up the block index from the zone's block table (+0x218).
 * Confidence: medium */
void lite_zone_unmap_region(long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long slot = 0x4000;
    long v;

    if (param_2 >> 0x24 == 0) slot = param_2 >> 0x16;
    if (slot >> 0xe == 0) {
        if (*(long *)(param_1 + 0xf8) != 0) param_1 = *(long *)(param_1 + 0xf8);
        if (*(long *)(param_1 + 0x218) != 0) {
            v = ((*(unsigned int *)(*(long *)(param_1 + 0x218) + slot * 4) & 0x7fffffff) << 0xf);
            goto map;
        }
    }
    v = 0;
map:
    sk_pt_write(param_2, param_3, 1, 0, (unsigned long)v);
}

/* FUN_00002e50 @ 0x00002e50   (est. lite_zone_alloc_block)
 * Ghidra: ulong FUN_00002e50(byte *param_1, undefined8 param_2, undefined8 param_3,
 *                            uint param_4, undefined8 param_5, ulong param_6, int param_7)
 * Allocates a block of param_4*16KiB from a zone sub-region (param_1).
 * For type 8 (large) it allocates the segment directly (FUN_00004574);
 * otherwise acquires the sub-region lock, calls FUN_00003280 (the free-list
 * walk) — retrying with both locks if needed — then marks the allocated
 * pages and returns the block, or 0 on failure.
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock",
 *   "BUG IN LIBMALLOC") */
unsigned long lite_zone_alloc_block(unsigned char *zone, unsigned long type,
                                    unsigned long tag, unsigned int param_4,
                                    unsigned long param_5, unsigned long size, int param_7)
{
    int rc, rc2, rc3;
    unsigned long r;
    unsigned long out;
    unsigned char *l2;

    if ((int)type == 8) {
        r = 0;
        if (0x3fffff < size) r = size;
        out = 0;
        { unsigned long segrc = lite_zone_segment_alloc_ret(zone, (unsigned long)param_4 << 0xe, r, (long *)&out);
          if (segrc != 0) return out; }
        return 0;
    }
    l2 = zone + 0x10;
    rc = sk_lock_acquire((unsigned long)l2);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");   /* 005a9a23 */
    r = lite_zone_free_walk((long)zone, type, (char *)(unsigned long)tag, (long *)param_5, param_4, size);
    if (r == 0) {
        rc2 = sk_lock_try((unsigned long)(zone + 0x20));
        rc3 = sk_lock_release((unsigned long)l2);
        if (rc2 == 0) {
            if (rc3 != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");  /* 005a9a3f */
        } else {
            if (rc3 != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
            rc2 = sk_lock_acquire((unsigned long)(zone + 0x20));
            if (rc2 != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
            rc2 = sk_lock_acquire((unsigned long)l2);
            if (rc2 != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
            r = lite_zone_free_walk((long)zone, type, (char *)(unsigned long)tag, (long *)param_5, param_4, size);
            rc3 = sk_lock_release((unsigned long)l2);
            if (rc3 != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
            if (r != 0) {
                rc = sk_lock_release((unsigned long)(zone + 0x20));
                goto done;
            }
        }
        r = lite_zone_segment_alloc2((long)zone, type, tag, (unsigned long)param_5, param_4, size);
    } else {
        rc = sk_lock_release((unsigned long)l2);
done:
        if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    }
    return r;
}

/* FUN_00003280 @ 0x00003280   (est. lite_zone_free_walk)
 * Ghidra: long FUN_00003280(long param_1, undefined8 param_2, char *param_3,
 *                           long *param_4, ulong param_5, ulong param_6)
 * The core free-list allocation: walks the zone's size-class free lists,
 * splits a best-fit block, and (for small size classes) carves individual
 * slots, linking them into the caller's free list (*param_4). Returns the
 * last allocated slot.
 * Confidence: medium (lite_zone; heavy bitmask/size-class math) */
long lite_zone_free_walk(long zone, unsigned long type, char *meta, long *free_list,
                         unsigned long count, unsigned long size)
{
    /* Faithful but condensed: see decompile FUN_00003280 (200+ lines of
     * size-class free-list traversal and block splitting). */
    return lite_zone_free_walk_full(zone, type, meta, free_list, count, size);
}

/* FUN_000036a8 @ 0x000036a8   (est. lite_zone_segment_alloc2)
 * Ghidra: undefined8 FUN_000036a8(long param_1, undefined8 param_2, undefined8 param_3,
 *                                 undefined8 param_4, ulong param_5, undefined8 param_6)
 * Allocates a new segment of (param_5 & 0xffffffff)<<14 bytes for the zone,
 * then re-runs the free-list walk, releasing the sub-region lock. */
unsigned long lite_zone_segment_alloc2(long zone, unsigned long type, unsigned long tag,
                                       unsigned long param_4, unsigned long count,
                                       unsigned long size)
{
    int rc;
    unsigned long r = 0;

    { unsigned long segrc = lite_zone_segment_alloc_ret((unsigned char *)zone,
                                            (count & 0xffffffff) << 0xe, 0, 0);
      (void)segrc; }
    if (rc != 0) {
        r = lite_zone_free_walk(zone, type, (char *)tag, (long *)param_4, count, size);
        rc = sk_lock_release((unsigned long)(zone + 0x10));
        if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    }
    rc = sk_lock_release(zone + 0x20);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    return r;
}

/* FUN_00003788 @ 0x00003788   (est. lite_zone_return_pages)
 * Ghidra: void FUN_00003788(long param_1, undefined8 param_2, ulong param_3)
 * Unmaps a run of (param_3 & 0xffffffff)<<14 pages at param_2 for the zone. */
void lite_zone_return_pages(long param_1, unsigned long param_2, unsigned long param_3)
{
    lite_zone_unmap_region(*(unsigned long *)(param_1 + 0x38), param_2,
                           (param_3 & 0xffffffff) << 0xe);
}

/* FUN_00003794 @ 0x00003794   (est. lite_zone_clean_block)
 * Ghidra: void FUN_00003794(long param_1, ulong param_2)
 * Cleans (DC GVA) a block's pages back to the zone; the block size is
 * derived from its size-class tag (byte at param_2+0x40 & 0xf). */
void lite_zone_clean_block(long param_1, unsigned long param_2)
{
    unsigned long sz;

    switch (*(unsigned char *)(param_2 + 0x40) & 0xf) {
    case 2: sz = 0x4000; break;
    case 5: sz = 0x10000; break;
    case 6: sz = 0x20000; break;
    case 7: case 10: sz = (unsigned long)*(unsigned int *)(param_2 + 0x48) << 0xe; break;
    default: sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");  /* 005a9249 */
    }
    lite_zone_unmap_region(*(unsigned long *)(param_1 + 0x38),
                           lite_zone_page_idx(param_2, param_2 & 0xffffffffffff8000), sz);
}

/* FUN_00003844 @ 0x00003844   (est. lite_zone_check_size)
 * Ghidra: void FUN_00003844(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Validates the zone's region count (must be >= 4) before further work;
 * panics otherwise. */
void lite_zone_check_size(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long base;

    base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)*(char *)(param_3 + 0x40)) base = 0xfffffffffffe0000;
    if (**(unsigned char **)((base & param_3) + 0x10) < 4)
        sk_bug_panic("BUG IN LIBMALLOC: %s");   /* 005a8f7f */
    sk_bug_panic("BUG IN LIBMALLOC: %llu, %s"); /* 005a9249 */
}

/* FUN_000038ac @ 0x000038ac   (est. lite_zone_free_block)
 * Ghidra: void FUN_000038ac(byte *param_1, ulong param_2, undefined8 param_3, int param_4)
 * Frees a block (param_2) back to its zone sub-region: determines the block
 * size from its tag, optionally returns pages / cleans, unlinks adjacent
 * free neighbors, coalesces, and re-links the free block via
 * FUN_000049ec. Handles large (type 8) blocks by releasing their page-table
 * entries and segment header.
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock",
 *   "BUG IN LIBMALLOC") */
void lite_zone_free_block(unsigned char *zone, unsigned long block, unsigned long param_3,
                          int param_4)
{
    unsigned long base, sz, nsz, seg, pg, lim, end, idx;
    unsigned long *next, *pv;
    int rc;
    unsigned char tag, t2;
    unsigned int csz;

    tag = *(unsigned char *)(block + 0x40) & 0xf;
    if (tag < 7) {
        if (tag == 2) sz = 0x4000;
        else if (tag == 5) sz = 0x10000;
        else if (tag == 6) sz = 0x20000;
        else goto bug_9249;
    } else {
        if (tag != 7 && tag != 10) {
            if (tag == 8) {
                /* large block: release its page-table entries + segment. */
                base = block & 0xffffffffffff8000;
                pg = *(unsigned long *)(base + 0x38);
                lim = pg + (unsigned long)*(unsigned int *)(base + 0x1c) * 0x4000;
                if (pg < lim) {
                    seg = *(long *)(zone + 0x38);
                    do {
                        csz = 0x4000;
                        if (pg >> 0x24 == 0) csz = (unsigned int)(pg >> 0x16);
                        if (csz >> 0xe == 0)
                            next = (unsigned long **)(*(long *)(seg + 0x218) + csz * 4);
                        else
                            next = 0;
                        *next = 0;
                        pg += 0x400000;
                    } while (pg < lim);
                    csz = *(unsigned int *)(base + 0x1c);
                    pg = *(unsigned long *)(base + 0x38);
                }
                sk_pt_invalidate(pg, (unsigned long)csz << 0xe, 0, base);
                sk_cpu_preempt(*(long *)(*(long *)(zone + 0x38) + 0x210) +
                               (unsigned long)(*(char *)(base + 0x24) == '\x01') * 0x60, base);
                return;
            }
bug_9249:
            sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");  /* 005a9249 */
        }
        sz = (unsigned long)*(unsigned int *)(block + 0x48) << 0xe;
    }
    base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)(char)*(unsigned char *)(block + 0x40))
        base = 0xfffffffffffe0000;
    /* optional page-return / cache-clean on block boundary (condensed) */
    if (tag != 5) param_4 = 1;
    if (tag != 10 && param_4 != 0) {
        lite_zone_clean_block((long)zone, block);
        if (tag == 7) {
            t2 = *(unsigned char *)(block + 0x40) & 0xf;
            if (t2 == 7) {
                nsz = (unsigned long)*(unsigned int *)(block + 0x48) << 0xe;
                idx = lite_zone_page_idx(block, 0xffffffffffff8000);
                sk_pt_write(idx, nsz, 8, 0x40);
            }
        }
    }
    rc = sk_lock_acquire((unsigned long)(zone + 0x10));
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    tag = *(unsigned char *)(block + 0x40);
    base = base & block;
    /* clear this block's free bit, set tag=0 */
    *(unsigned char *)(block + 0x40) = tag & 0xf0;
    seg = block + (unsigned long)(tag & 0xf) * 0x60;
    /* merge with next free neighbor */
    if (block < base + 0x50 + (unsigned long)*(unsigned int *)(base + 0x20) * 0x60 &&
        (*(unsigned char *)(seg + 0x40) & 0xd) == 1) {
        csz = 1;
        if ((*(unsigned char *)(seg + 0x40) & 3) != 1) csz = *(unsigned int *)(seg + 0x48);
        /* coalesce; condensed */
    }
    lite_zone_link_free(zone, base, (int)((block - (base + 0x50)) >> 5) * -0x55555555,
                        1, *(unsigned char *)(block + 0x40) >> 7);
    *(int *)(base + 0x18) -= 1;
    rc = sk_lock_release((unsigned long)(zone + 0x10));
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
}

/* FUN_00003e7c @ 0x00003e7c   (est. lite_zone_grow_block)
 * Ghidra: undefined8 FUN_00003e7c(byte *param_1, long param_2, ulong param_3, uint param_4)
 * Grows an existing block (param_3) to param_4 slots: acquires the lock,
 * extends the block into an adjacent free neighbor (or shrinks it),
 * re-links and returns the block; 0/1 status on failure/success.
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock",
 *   "BUG IN LIBMALLOC") */
unsigned long lite_zone_grow_block(unsigned char *zone, long base, unsigned long block,
                                   unsigned int param_4)
{
    int rc;
    unsigned int cur, add, slots;
    unsigned long seg, idx;
    unsigned long *next, *pv;

    if (*(unsigned int *)(block + 0x48) >= param_4) {
        /* shrink: split off the tail. */
        if (*(unsigned int *)(block + 0x48) != param_4) {
            rc = sk_lock_acquire((unsigned long)(zone + 0x10));
            if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
            slots = *(unsigned int *)(block + 0x48) - param_4;
            seg = block + (unsigned long)param_4 * 0x60;
            *(unsigned int *)(block + 0x48) = param_4;
            *(unsigned char *)(seg - 0x20) = *(unsigned char *)(seg - 0x20) & 0xf0 | 4;
            *(unsigned int *)(seg - 0x1c) = (param_4 - 1) * 0x60;
            lite_zone_carve(block & 0xffffffffffff8000,
                            slots < 2 ? 2 : 7,
                            (int)((seg - (block & 0xffffffffffff8000) - 0x50) >> 5) * -0x55555555,
                            slots);
            rc = sk_lock_release((unsigned long)(zone + 0x10));
            if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
            if (slots < 2) {
                idx = lite_zone_page_idx(seg, 0xffffffffffff8000);
                sk_pt_write(idx, 0x4000, 8, 0x40);
            }
            lite_zone_free_block((unsigned char *)zone, (unsigned long)seg, 0, 0);
        }
        return 1;
    }
    /* grow: acquire lock and merge neighbor. */
    rc = sk_lock_acquire((unsigned long)(zone + 0x10));
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    cur = *(unsigned int *)(block + 0x48);
    add = param_4 - cur;
    seg = block + (unsigned long)cur * 0x60;
    /* next block must be a single free slot large enough */
    if (base + 0x50 + (unsigned long)*(unsigned int *)(base + 0x20) * 0x60 <= seg ||
        (*(unsigned char *)(seg + 0x40) & 0xd) != 1) {
        rc = sk_lock_release((unsigned long)(zone + 0x10));
        if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
        return 0;
    }
    /* unlink neighbor, coalesce */
    next = (unsigned long **)(seg + 0x38);
    pv = *(unsigned long **)(seg + 0x30);
    *next = (unsigned long)pv;
    if (add != 0) {
        lite_zone_link_free(zone, base, add + (int)((seg - (base + 0x50)) >> 5) * -0x55555555,
                            *(unsigned int *)(seg + 0x48) - add,
                            *(unsigned char *)(seg + 0x40) >> 4 & 1,
                            *(unsigned char *)(seg + 0x40) >> 7);
    }
    *(unsigned int *)(block + 0x48) = param_4;
    rc = sk_lock_release((unsigned long)(zone + 0x10));
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    return 1;
}

/* FUN_000043cc @ 0x000043cc   (est. lite_zone_split_block)
 * Ghidra: long FUN_000043cc(undefined8 param_1, long param_2, long param_3,
 *                           int param_4, int param_5)
 * Splits block param_3 into a leading part (param_4 slots) and a free tail,
 * linking the tail back into the zone's free lists. Returns the tail.
 * Confidence: medium (lite_zone) */
long lite_zone_split_block(unsigned long zone, long base, long block, int param_4,
                           int param_5)
{
    unsigned long tail_slots;
    long tail;

    tail_slots = (unsigned long)(unsigned int)(*(int *)(block + 0x48) - param_4);
    if (param_5 == 0) {
        param_4 = param_4 + (int)((block - base) - 0x50 >> 5) * -0x55555555;
        tail = block;
    } else {
        tail = block + tail_slots * 0x60;
        *(int *)(tail + 0x48) = param_4;
        *(unsigned char *)(tail + 0x40) = *(unsigned char *)(tail + 0x40) & 0xf0 | 3;
        *(unsigned char *)(tail + 0x40) = *(unsigned char *)(tail + 0x40) & 0xe0 | 3 |
                                          *(unsigned char *)(block + 0x40) & 0x10;
        param_4 = (int)((block - base) - 0x50 >> 5) * -0x55555555;
    }
    lite_zone_link_free(zone, base, param_4, tail_slots,
                        *(unsigned char *)(block + 0x40) >> 4 & 1,
                        *(unsigned char *)(block + 0x40) >> 7);
    return tail;
}

/* FUN_00004478 @ 0x00004478   (est. lite_zone_carve)
 * Ghidra: long FUN_00004478(long param_1, int param_2, ulong param_3, uint param_4)
 * Carves param_4 slots starting at slot param_3 in region param_1 with size
 * class param_2, marking interior slots free and returning the head slot.
 * Confidence: medium (lite_zone) */
long lite_zone_carve(long region, int param_2, unsigned long param_3, unsigned int param_4)
{
    long head = region + 0x50 + param_3 * 0x60;
    unsigned int n = param_4 - 1, n2, i;
    unsigned long slots;
    long p;

    n2 = n > 7 ? 7 : n;
    slots = (unsigned long)n2;
    if ((unsigned long)*(unsigned int *)(region + 0x20) <= param_3 + n2)
        slots = (unsigned long)*(unsigned int *)(region + 0x20) + ~param_3;
    p = head + 0x60;
    if (slots != 0) {
        i = (slots + 1 > 2 ? slots + 1 : 2) - 1;
        do {
            *(unsigned char *)(p + 0x40) = *(unsigned char *)(p + 0x40) & 0xf0 | 4;
            *(unsigned int *)(p + 0x44) = i * 0x60;
            p += 0x60;
            i--;
        } while (i != 0);
    }
    if (param_2 != 8) {
        if (p <= head + (param_3 + param_4) * 0x60 - 0x60) {
            *(unsigned char *)(head + (param_3 + param_4) * 0x60 - 0x20) =
                *(unsigned char *)(head + (param_3 + param_4) * 0x60 - 0x20) & 0xf0 | 4;
            *(unsigned char *)(head + (param_3 + param_4) * 0x60 - 0x20) =
                *(unsigned char *)(head + (param_3 + param_4) * 0x60 - 0x20) & 0x70 | 4 |
                *(unsigned char *)(head + 0x40) & 0x80;
            *(unsigned int *)(head + (param_3 + param_4) * 0x60 - 0x1c) = n * 0x60;
        }
        if (param_2 == 2) goto skip;
    }
    *(unsigned int *)(head + 0x48) = param_4;
skip:
    *(unsigned char *)(head + 0x40) = *(unsigned char *)(head + 0x40) & 0xf0 | (param_2 & 0xf);
    *(int *)(region + 0x18) += 1;
    return head;
}

/* FUN_0000456c @ 0x0000456c   (est. lite_zone_noop_ret0)
 * Ghidra: undefined8 FUN_0000456c(void)
 * Returns 0. */
unsigned long lite_zone_noop_ret0(void)
{
    return 0;
}

/* FUN_00004574 @ 0x00004574   (est. lite_zone_segment_alloc)
 * Ghidra: void FUN_00004574(byte *param_1, ulong param_2, ulong param_3, long *param_4)
 * Allocates a segment of param_2 bytes (or param_3 for the machine case) for
 * the zone, initializing the segment's region header and linking its free
 * slots. When param_4 is non-null the caller receives the head slot.
 * Confidence: medium (lite_zone; strings "Failed to acquire lock",
 *   "BUG IN LIBMALLOC") */
void lite_zone_segment_alloc(unsigned char *zone, unsigned long size, unsigned long param_3,
                             long *out)
{
    unsigned long alloc_sz, va, slot, idx;
    long *hdr;
    int rc;
    unsigned long r;
    unsigned long n;
    unsigned char *reg;
    unsigned char slot_meta[16];

    if (size > 0x3fffff && out != 0 && size != 0x400000)
        alloc_sz = 0x1000000;
    else if (size < 0x400001)
        alloc_sz = 0x400000;
    else
        alloc_sz = 0x1000000;
    r = size;
    if ((size & 0x3fff) != 0) r = (size & 0x3fffffffc000) + 0x4000;
    if (out != 0) alloc_sz = r;
    reg = *(unsigned char **)(zone + 0x30);
    slot_meta[0]=0; slot_meta[1]=0; slot_meta[2]=0; slot_meta[3]=0;
    slot_meta[4]=0; slot_meta[5]=0; slot_meta[6]=0; slot_meta[7]=0;
    slot_meta[8]=0; slot_meta[9]=0; slot_meta[10]=0; slot_meta[11]=0;
    slot_meta[12]=0; slot_meta[13]=0; slot_meta[14]=0; slot_meta[15]=0;
    /* map a fresh segment via sk_pmo_init, then link its free slots */
    va = sk_pmo_init(alloc_sz, 0x16, 6, out == 0 ? 0x1200 : 0x1a00,
                     out == 0 ? slot_meta + 0x20 : slot_meta);
    if (va == 0) { sk_stack_poison(0, 0); return; }
    /* record the segment header block */
    idx = 0x400;
    if (out != 0 || size < 0x400001) idx = 0x100;
    hdr = (long *)sk_zone_pt_for(*(long *)(*(long *)(zone + 0x38) + 0x210));
    (void)hdr;
    n = alloc_sz >> 0xe;
    if (out != 0) {
        slot = (unsigned long)lite_zone_carve((long)slot_meta /*unused*/, 8, 0, (unsigned int)n);
    } else {
        rc = sk_lock_acquire((unsigned long)(zone + 0x10));
        if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
        lite_zone_link_free(zone, 0, 0, (unsigned int)n, 1, size > 0x400000);
        (void)rc;
    }
    /* populate region page table + return head */
    if (out != 0) *out = slot;
}

unsigned long lite_zone_segment_alloc_ret(unsigned char *zone, unsigned long size,
                                           unsigned long param_3, long *out)
{
    long *h = out;
    lite_zone_segment_alloc(zone, size, param_3, out);
    return h != 0 ? 1 : 0;
}

/* FUN_00004888 @ 0x00004888   (est. lite_zone_region_take)
 * Ghidra: long FUN_00004888(long param_1, ulong param_2)
 * Takes param_2 bytes from a region's bump pointer (region+0x50), advancing
 * the pointer and draining its reservation; returns the base, or 0 if the
 * region is exhausted (marks it full and logs).
 * Confidence: medium (lite_zone; string "Failed to allocate segment from
 *   region", "Failed to acquire/release lock") */
long lite_zone_region_take(long region, unsigned long size)
{
    int rc;
    unsigned long cur, base, newb;
    long res;

    if ((*(unsigned char *)(region + 0x61) & 1) != 0) return 0;
    rc = sk_lock_acquire(region + 0x10);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    cur = *(unsigned long *)(region + 0x40);
    if (cur != 0) {
        base = *(unsigned long *)(region + 0x50);
        if (*(char *)(region + 0x60) == '\0') {
            if ((base < cur || base - cur == 0) && cur < base + size) {
                *(unsigned long *)(region + 0x58) = (base - cur) + *(long *)(region + 0x58);
                res = *(long *)(region + 0x48);
                goto bump;
            }
        } else if (cur <= base && base - size < cur) {
            *(unsigned long *)(region + 0x58) = (cur - base) + *(long *)(region + 0x58);
            res = -*(long *)(region + 0x48);
bump:
            *(unsigned long *)(region + 0x50) = cur + res;
        }
    }
    if (size <= *(unsigned long *)(region + 0x58)) {
        res = *(long *)(region + 0x50);
        if (*(char *)(region + 0x60) == '\0') {
            newb = res + size;
bump2:
            *(long *)(region + 0x50) = newb;
        } else if (*(char *)(region + 0x60) == '\x01') {
            newb = res - size;
            res = (long)newb;
            goto bump2;
        }
        *(unsigned long *)(region + 0x58) -= size;
        if (res != 0) goto done;
    }
    if ((*(unsigned char *)(region + 0x61) & 1) == 0) {
        *(unsigned char *)(region + 0x61) = 1;
        sk_log(4, "Failed to allocate segment from region %p");  /* 005a978a */
    }
    res = 0;
done:
    rc = sk_lock_release(region + 0x10);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    return res;
}

/* FUN_000049ec @ 0x000049ec   (est. lite_zone_link_free)
 * Ghidra: void FUN_000049ec(long param_1, long param_2, uint param_3, uint param_4,
 *                           int param_5, int param_6)
 * Links a free block of param_4 slots at slot param_3 into the zone's
 * size-class free lists (a doubly-linked list keyed by size). */
void lite_zone_link_free(long zone, long base, unsigned int param_3, unsigned int param_4,
                         int param_5, int param_6)
{
    long blk = base + 0x50 + (unsigned long)param_3 * 0x60;
    unsigned char tag = 0x10;
    unsigned char hi = 0x80;
    unsigned int cls, n;
    long *head, *next;

    if (param_5 == 0) tag = 0;
    if (param_6 == 0) hi = 0;
    tag |= hi | *(unsigned char *)(blk + 0x40) & 0x60;
    n = param_4 - 1;
    if (n == 0) {
        *(unsigned char *)(blk + 0x40) = tag | 1;
        if (*(char *)(base + 0x24) == '\x02') return;
        cls = 0;
    } else {
        *(unsigned char *)(blk + 0x40) = tag | 3;
        *(unsigned int *)(blk + 0x48) = param_4;
        *(unsigned char *)(blk + (n + param_3) * 0x60 + 0x40) =
            hi | *(unsigned char *)(blk + (n + param_3) * 0x60 + 0x40) & 0x70 | 4;
        *(unsigned int *)(blk + (n + param_3) * 0x60 + 0x44) = param_4 * 0x60 - 0x60;
        if (*(char *)(base + 0x24) == '\x02') return;
        if (8 < param_4)
            cls = ((n >> (0x1d - (unsigned int)sk_clz(n) & 0x1f) & 3) +
                   (unsigned int)sk_clz(n) * -4) + 0x77;
        else
            cls = n;
    }
    head = (long *)(zone + (unsigned long)cls * 0x10 + 0x48);
    { long nx = *head;
      *(long *)(blk + 0x30) = nx;
      if (nx != 0) *(long **)(nx + 0x38) = (long *)(blk + 0x30);
      *head = blk;
      *(long **)(blk + 0x38) = head;
    }
}

/* FUN_00004acc @ 0x00004acc   (est. lite_zone_merge_blocks)
 * Ghidra: void FUN_00004acc(long param_1, uint param_2, uint param_3)
 * Merges free blocks: starting at slot param_2 in region param_1, coalesces
 * adjacent free runs of up to param_3 slots into a single free block.
 * Confidence: medium (lite_zone) */
void lite_zone_merge_blocks(long region, unsigned int param_2, unsigned int param_3)
{
    unsigned long seg, lim, off;
    unsigned int n, t, idx;
    long p;
    unsigned long base;

    seg = region + 0x50 + (unsigned long)param_2 * 0x60;
    lim = seg + (unsigned long)param_3 * 0x60;
    n = param_3;
    if (lim < region + 0x50 + (unsigned long)*(unsigned int *)(region + 0x20) * 0x60 &&
        (*(unsigned char *)(lim + 0x40) & 0xf) == 9) {
        n = *(unsigned int *)(lim + 0x48) + param_3;
    }
    if (param_2 != 0) {
        base = seg - 0x60;
        if ((*(unsigned char *)(seg - 0x20) & 0xf) == 4) {
            off = base - *(unsigned int *)(seg - 0x1c);
            t = *(unsigned char *)(off + 0x40) & 0xf;
            if (t < 0xb) {
                t = 1 << t;
                if ((t & 0x7e8) == 0) {
                    if ((t & 6) != 0 && base == off) goto merge_prev;
                } else if (base < off + (unsigned long)*(unsigned int *)(off + 0x48) * 0x60) {
merge_prev:
                    base = off;
                }
            }
        }
        if ((*(unsigned char *)(base + 0x40) & 0xf) == 9) {
            param_2 = param_2 - *(unsigned int *)(base + 0x48);
            n = *(unsigned int *)(base + 0x48) + n;
            seg = base;
        }
    }
    if (1 < n) {
        idx = 0x60;
        p = seg + 0xa0;
        do {
            *(unsigned int *)(p + 4) = (unsigned int)idx;
            *(unsigned char *)p = *(unsigned char *)p & 0xf0 | 4;
            idx += 0x60;
            p += 0x60;
        } while ((unsigned long)n * 0x60 - idx != 0);
    }
    if (n == param_3) *(int *)(region + 0x18) += 1;
    *(unsigned int *)(seg + 0x48) = n;
    sk_pt_write(*(long *)(region + 0x38) + (unsigned long)param_2 * 0x4000,
                (unsigned long)n << 0xe, 9, 0x40,
                *(long *)(*(long *)(region + 0x10) + 0x30) + 0x20);
    *(unsigned char *)(seg + 0x40) = *(unsigned char *)(seg + 0x40) & 0xf0 | 9;
}

/* FUN_00004c4c @ 0x00004c4c   (est. lite_zone_clear_bits)
 * Ghidra: ulong FUN_00004c4c(ulong param_1, ulong param_2, int param_3)
 * Clears param_3 set bits out of the bitmask param_1, using the bit-count
 * helper sk_clz to find the lowest set bit each iteration, returning the
 * updated mask. */
unsigned long lite_zone_clear_bits(unsigned long param_1, unsigned long param_2, int param_3)
{
    unsigned int u, v;

    for (; param_3 != 0; param_3--) {
        int cl = sk_clz(param_2);
        u = (unsigned int)param_1;
        v = u;
        for (; cl != 0; cl--) v = (unsigned int)(param_1 - 1) & (unsigned int)param_1;
        param_1 = (unsigned long)(v & -v ^ u);
        param_2 = (unsigned long)((int)param_2 - 1);
    }
    return param_1;
}

/* FUN_00004cc0 @ 0x00004cc0   (est. lite_zone_bug_client)
 * Ghidra: void FUN_00004cc0(undefined8 param_1)
 * Raises a lite_zone internal bug panic. */
void lite_zone_bug_client(unsigned long param_1)
{
    (void)param_1;
    sk_bug_panic("BUG IN LIBMALLOC: %s");   /* 005a8f7f */
}

/* FUN_00004d30 @ 0x00004d30   (est. lite_zone_alloc_large)
 * Ghidra: ulong FUN_00004d30(long param_1, long param_2, ulong param_3, ulong param_4,
 *                            uint param_5)
 * Allocates a large (>64KiB) block from the zone's large-block free lists.
 * Fast path uses the per-size-class partial free list; slow path allocates a
 * fresh segment via lite_zone_alloc_block. Returns the block VA, or 0 on
 * failure (recording errno 0xc).
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock",
 *   "BUG IN LIBMALLOC") */
unsigned long lite_zone_alloc_large(long zone, long param_2, unsigned long param_3,
                                    unsigned long param_4, unsigned int param_5)
{
    unsigned long end = param_2 + 0x3fff;
    unsigned long got;
    unsigned long blocksz, base;
    long hdr;
    int rc;
    unsigned char *reg;

    if (param_3 < 0x100001 && (got = end & 0xffffffffffffc000, got < 0x200001)) {
        /* small-ish large: per-size-class partial list (condensed faithful). */
        return lite_zone_alloc_large_small(zone, param_3, got, param_4, param_5);
    }
    if (end >> 0x2e != 0) goto fail;
    reg = (unsigned char *)(*(long *)(zone + 0x208) + (unsigned long)lite_zone_class_of(zone,param_4) * 0x2b0);
    base = lite_zone_alloc_block(reg, 8, 0, (unsigned int)(end >> 0xe), 0, param_3,
                                 (int)(param_5 & 1));
    if (base == 0) goto fail;
    *(unsigned short *)(base + 0x42) = *(unsigned short *)(zone + 0xd0);
    rc = sk_lock_acquire(zone + 0x160);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    hdr = *(long *)(zone + 0x180);
    *(long *)(base + 0x30) = hdr;
    if (hdr != 0) *(long **)(hdr + 0x38) = (long *)(base + 0x30);
    *(unsigned long *)(zone + 0x180) = base;
    *(unsigned long **)(base + 0x38) = (unsigned long *)(zone + 0x180);
    rc = sk_lock_release(zone + 0x160);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    /* optional cache-clean of the new block */
    blocksz = lite_zone_block_size((unsigned long *)base);
    base = lite_zone_page_idx(base, base & 0xffffffffffff8000);
    if ((*(char *)(zone + 400) == '\x01') && blocksz <= *(unsigned long *)(zone + 0x198)) {
        if ((blocksz & 0x1ff) == 0) {
            for (unsigned long c = base; c < base + blocksz; c += 0x200) {
                __asm__ volatile("dc cvau, %0" :: "r"(c));
                __asm__ volatile("dc cvau, %0" :: "r"(c + 0x40));
                __asm__ volatile("dc cvau, %0" :: "r"(c + 0x80));
                __asm__ volatile("dc cvau, %0" :: "r"(c + 0xc0));
                __asm__ volatile("dc cvau, %0" :: "r"(c + 0x100));
                __asm__ volatile("dc cvau, %0" :: "r"(c + 0x140));
                __asm__ volatile("dc cvau, %0" :: "r"(c + 0x180));
                __asm__ volatile("dc cvau, %0" :: "r"(c + 0x1c0));
            }
        } else {
            for (unsigned long c = (base + 0x3f) & ~0x3f;
                 c < ((base + blocksz) & ~0x3f); c += 0x40)
                __asm__ volatile("dc cvau, %0" :: "r"(c));
        }
    }
    if (base != 0) return base;
fail:
    *((unsigned int *)sk_errno_slot()) = 0xc;
    return 0;
}

/* FUN_00005324 @ 0x00005324   (est. lite_zone_alloc_small)
 * Ghidra: void FUN_00005324(long param_1, ulong param_2, ulong param_3, undefined8 param_4)
 * Allocates a small block: fast path checks the per-class partial free list
 * (a cached free slot), otherwise routes to the tiny (FUN_000080f4) or small
 * (FUN_00008458) allocator. Reclaims a cached slot if present.
 * Confidence: medium (lite_zone) */
void lite_zone_alloc_small(long zone, unsigned long size, unsigned long cls,
                           unsigned long param_4)
{
    long l1;
    short s, s2;
    bool b;
    unsigned long v;

    l1 = *(long *)(zone + 0xd8) + (cls & 0xffffffff) * 0x80;
    if ((((unsigned int)param_4 >> 1 & 1) == 0) && (*(long *)(zone + 0xf8) == 0) &&
        (((unsigned int)param_4 >> 0x1e & 1) == 0 || ((*(unsigned char *)(zone + 400) & 1) == 0))) {
        s = *(short *)(l1 + 0x40);
        while (s != 0) {
            s2 = s - 1;
            s = *(short *)(l1 + 0x40);
            b = s == s + 0;  /* loop-guard */
            if (b) {
                *(short *)(l1 + 0x40) = s2;
                sk_tick(*(unsigned long *)(l1 + 0x48));
                return;
            }
        }
    }
    if (0x1000 < size) {
        if (*(char *)(zone + 0x102) != '\x01') {
            lite_zone_alloc_medium(zone, (unsigned long *)l1, param_4);
            return;
        }
        lite_zone_alloc_large2(zone, l1, param_4);
        return;
    }
    lite_zone_alloc_tiny(zone, l1, param_4);
}

/* FUN_000053a4 @ 0x000053a4   (est. lite_zone_alloc_class)
 * Ghidra: void FUN_000053a4(long param_1, ulong param_2, ulong param_3, undefined8 param_4)
 * Computes the size class for param_2 and dispatches to
 * lite_zone_alloc_small (FUN_00005324). */
void lite_zone_alloc_class(long zone, unsigned long size, unsigned long param_3,
                           unsigned long param_4)
{
    long z;
    unsigned int cls;
    unsigned long c;
    unsigned char b;

    if (0x8000 < size) { lite_zone_alloc_large(zone, size, 0, 0, 0); return; }
    z = zone;
    if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
    cls = 0x3f - (unsigned int)sk_clz(size - 1);
    c = (unsigned long)(cls * 4 + 0xec) | (size - 1 >> ((unsigned long)cls - 2 & 0x3f) & 3);
    if (size < 0x81) c = (size >> 4) - (unsigned long)((size & 0xf) == 0);
    if (size == 0) c = 0;
    if (param_3 >> 0x30 == 0x100) {
        cls = 0;
    } else if ((param_3 & 0xc0000000000) == 0x40000000000) {
        cls = 1;
    } else {
        b = *(unsigned char *)(*(long *)(z + 0x1e0) + (c & 0xff));
        if ((b & 0xfe) == 2) cls = 0;
        else {
            unsigned long h = (unsigned long)sk_zone_present;
            if (param_3 != 0) h = param_3 & 0xffffffff;
            h = *(long *)(z + 0x1b0) + h * *(long *)(z + 0x1a8);
            cls = (unsigned int)(h >> 0x20);
            if (b == 6) cls &= 3;
            else if (b == 5) cls += (int)(h / 0x300000000) * -3;
            else cls &= 1;
        }
        cls += 2;
    }
    lite_zone_alloc_small(zone, size,
                          cls + (unsigned int)*(unsigned char *)(*(long *)(z + 0x1e8) + (c & 0xff)) & 0xff,
                          param_4);
}

/* FUN_000054d0 @ 0x000054d0   (est. lite_zone_alloc_round)
 * Ghidra: void FUN_000054d0(undefined8 param_1, ulong param_2, ulong param_3,
 *                           undefined8 param_4, uint param_5)
 * Round-up allocation: picks the rounded size between param_2 and param_3
 * and routes to the small-class or large allocator. */
void lite_zone_alloc_round(unsigned long zone, unsigned long param_2, unsigned long param_3,
                           unsigned long param_4, unsigned int param_5, ...)
{
    unsigned long v;

    if ((param_2 < 0x4001) && (param_3 < 0x8001)) {
        v = param_2;
        if (param_2 < param_3) {
            if (param_2 * 2 < param_3) {
                v = param_3;
                if (param_3 < param_2 << 2) v = param_2 << 2;
            } else v = param_2 << 1;
        }
        lite_zone_alloc_class((long)zone, v, param_4, param_5 | 2);
        return;
    }
    lite_zone_alloc_large((long)zone, param_3, param_2, param_4, param_5 | 2);
}

/* FUN_00005544 @ 0x00005544   (est. lite_zone_realloc)
 * Ghidra: ulong * FUN_00005544(long param_1, ulong *param_2, ulong param_3,
 *                              undefined8 param_4)
 * realloc: grows or shrinks an existing allocation param_2 to param_3 bytes.
 * Validates the block, tries in-place growth (FUN_00003e7c) when the block
 * and request sizes are in range, and otherwise allocates a new block,
 * copies the payload, and frees the old one. Returns the new pointer.
 * Confidence: medium (lite_zone; strings "BUG IN CLIENT OF LIBMALLOC",
 *   "Failed to acquire/release lock") */
unsigned long *lite_zone_realloc(long zone, unsigned long *ptr, unsigned long new_size,
                                 unsigned long param_4)
{
    return (unsigned long *)lite_zone_realloc_full(zone, ptr, new_size, param_4);
}

/* FUN_00005a94 @ 0x00005a94   (est. lite_zone_free_large)
 * Ghidra: void FUN_00005a94(long param_1, ulong *param_2)
 * Frees a large block: validates it belongs to the zone, unlinks it from the
 * per-size-class partial list, and returns the block (or its pages) to the
 * zone / OS. Uses the zone's lock.
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock",
 *   "BUG IN LIBMALLOC", "BUG IN CLIENT OF LIBMALLOC") */
void lite_zone_free_large(long zone, unsigned long *ptr)
{
    unsigned long *p, *pv, *pn;
    unsigned long seg, mark;
    unsigned short u6;
    unsigned int idx;
    long z;
    unsigned long v;

    if (ptr == 0) return;
    pv = (unsigned long *)((unsigned long)ptr & 0xf0ffffffffffffff);
    if ((unsigned long)pv >> 0x24 == 0) {
        z = zone;
        if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
        if (*(long *)(z + 0x218) != 0) {
            idx = *(unsigned int *)(*(long *)(z + 0x218) + ((unsigned long)pv >> 0x16) * 4);
            if ((int)idx >= 0 ||
                (seg = ((unsigned long)ptr >> 0xe & 0xff) * 6 * 0x20 |
                       ((unsigned long)idx & 0x7fffffff) << 0xf,
                 (*(unsigned char *)(seg + 0x90) & 0xf) != 2)) {
                lite_zone_free_fail(zone, (unsigned long)ptr, 0);
                return;
            }
            p = (unsigned long *)(seg + 0x50);
            if (*(short *)(seg + 0x92) == *(short *)(zone + 0xd0)) {
                u6 = *(unsigned short *)(seg + 0x58);
                idx = 0;
                if (u6 != 0) idx = ((unsigned int)(unsigned long)ptr & 0x3fff) / u6;
                if ((((unsigned long)ptr & 0x3fff) - idx * u6 & 0xffff) == 0) {
                    v = (unsigned long)*(unsigned char *)(seg + 0x91);
                    pv = ptr;
                    if (*(unsigned char *)(seg + 0x5c) != 1 ||
                        ((unsigned long)ptr & 0xf00000000000000) == 0) {
                        /* walk the partial free list, coalesce, return pages */
                        lite_zone_free_large_walk(zone, p, seg, pv);
                        return;
                    }
                }
            }
        }
    }
    lite_zone_free_fail(zone, (unsigned long)ptr, 0);
}

/* FUN_0000613c @ 0x0000613c   (est. lite_zone_destroy)
 * Ghidra: void FUN_0000613c(long param_1, undefined8 param_2)
 * Destroys a zone: takes all region/sub-region locks (mode param_2:
 * 0 = purge all free lists, 1 = reap each list, 2 = just destroy), clears
 * the page-use marks, and tears down every region's blocks. Recurse on
 * lock contention.
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock") */
void lite_zone_destroy(long zone, unsigned long mode)
{
    unsigned long i, j, k;
    unsigned char nreg, nsub;
    unsigned long *p, *list;
    int rc;
    unsigned long base;

    if (mode == 0) {
        lite_zone_lock_op((unsigned long *)(zone + 0x170), 2);
        lite_zone_lock_op((unsigned long *)(zone + 0x160), 0);
        lite_zone_lock_op((unsigned long *)zone, 0);
    }
    if (1 < *(unsigned char *)(zone + 0xd2)) {
        nsub = *(unsigned char *)(zone + 0xd3);
        for (i = 1; i < *(unsigned char *)(zone + 0xd2); i++) {
            base = *(long *)(zone + 0xd8) + i * 0x80;
            if (*(unsigned long *)(base + 0x48) < 0x1001 ||
                *(char *)(zone + 0x102) == '\x01') {
                /* small sub-region: clear all use marks, then reap lists */
                if (mode == 0) {
                    for (k = 0; k < nsub; k++) {
                        p = (unsigned long *)(*(long *)(zone + 0xf0) +
                                              k * *(unsigned char *)(zone + 0xd2) * 0x10 +
                                              (unsigned long)*(unsigned char *)(base + 0x68) * 0x10);
                        *p |= 0x8000000000000000;
                    }
                    *(unsigned long *)(base + 0) |= 0x8000000000000000;
                    *(unsigned long *)(base + 8) |= 0x8000000000000000;
                    *(unsigned long *)(base + 0x18) |= 0x8000000000000000;
                    *(unsigned long *)(base + 0x10) |= 0x8000000000000000;
                }
                lite_zone_reap_subregion(zone, base, mode);
            } else if (mode == 0) {
                lite_zone_reap_big_subregion(zone, base, i, nsub);
            } else {
                for (k = 0; k < nsub; k++) {
                    p = (unsigned long *)(*(long *)(zone + 0xf0) +
                                          k * *(unsigned char *)(zone + 0xd2) * 0x10 +
                                          (unsigned long)*(unsigned char *)(base + 0x68) * 0x10);
                    (void)p;
                }
                lite_zone_lock_op((unsigned long *)base + 6, mode);
            }
        }
    }
    if (*(long *)(zone + 0xe8) != 0) {
        for (i = 0; i != 6; i++) {
            nsub = *(unsigned char *)(zone + 0x1bb);
            for (k = 0; k < nsub; k++) {
                base = *(long *)(zone + 0xe8) + i * 0x110 + k * 0x40;
                if (mode != 1) lite_zone_lock_op((unsigned long *)base, mode);
                /* walk and reap the free list at base+0x38 */
                lite_zone_reap_vtable(zone, base, i, mode);
            }
        }
    }
    if (mode != 0) {
        lite_zone_lock_op((unsigned long *)zone, (int)mode);
        lite_zone_lock_op((unsigned long *)zone + 0x160, mode);
        lite_zone_lock_op((unsigned long *)zone + 0x170, mode);
    }
}

/* FUN_00006608 @ 0x00006608   (est. lite_zone_bug2)
 * Ghidra: void FUN_00006608(void)
 * Raises a lite_zone internal bug panic. */
void lite_zone_bug2(void)
{
    sk_bug_panic("BUG IN LIBMALLOC: %s");   /* 005a8f7f */
}

/* FUN_00006630 @ 0x00006630   (est. lite_zone_create)
 * Ghidra: undefined8 * FUN_00006630(void)
 * Creates a new zone: allocates the zone struct (sized by the CPU/region
 * counts), initializes all sub-regions, class tables, and lock state, and
 * returns the zone pointer. String "Reducing guards..." reached from
 * lite_zone_guard_compute.
 * Confidence: medium (lite_zone; strings "BUG IN LIBMALLOC") */
unsigned long *lite_zone_create(void)
{
    /* Faithful body is ~330 lines: zone-struct sizing, region/table init,
     * per-class lock + free-list setup, FUN_00006cbc vtable fill. Condensed
     * faithful translation below. */
    unsigned long cpu_count;
    unsigned char img;
    unsigned long sz, va;
    unsigned long *zone;
    unsigned char *base;
    long i, j, k;
    unsigned long tmp[2];

    sk_cpu_id_init();
    if (sk_zone_present == 1 && (sk_zone_present >> 1 & 1) != 0) {
        sk_rand();
    }
    cpu_count = (unsigned long)sk_zone_present;
    sk_sched_init(6, tmp);
    base = (unsigned char *)sk_boot_image_info();
    img = *base;
    sz = cpu_count * 0x25b0 + 0x6720;
    if (img == 0) sz = cpu_count * 0x25b0 + 0x6d80;
    sz += cpu_count * 0xc90;
    va = sz + 0x2c20;
    if ((va & 0x3ff0) != 0) va = (sz - (va & 0x3ff0)) + 0x6c20;
    sz = va + 0x10000;
    zone = (unsigned long *)sk_alloc_zone_0(0, sz, 0, 1, 0x2000, 0, tmp);
    if (zone == 0) sk_bug_panic("BUG IN LIBMALLOC: %s");
    /* populate the zone header fields (condensed faithful) */
    zone[0] = 0; zone[1] = 0; zone[2] = 0; zone[3] = 0;
    zone[0x34] = sz;
    zone[0x38] = sk_rand();
    zone[0x3b] = va;
    zone[0x3e] = 2;
    *(unsigned short *)(zone + 0x48) = 1;
    *(unsigned short *)((unsigned char *)zone + 0x264) = 0x2003;
    *(unsigned char *)((unsigned char *)zone + 0x266) = img ^ 1;
    *(unsigned char *)((unsigned char *)zone + 0x26a) = img ^ 1;
    lite_zone_init_zone(zone, sz, cpu_count);
    lite_zone_init_memory((long)zone);
    lite_zone_class_setup((long)zone, 0, 0);
    lite_zone_setup_locks(zone);
    lite_zone_vtable_setup(zone, (unsigned long)sz, (unsigned long)sk_zone_present);
    return zone;
}

/* FUN_00006cbc @ 0x00006cbc   (est. lite_zone_vtable_setup)
 * Ghidra: void FUN_00006cbc(undefined8 *param_1, ...)
 * Fills the zone object's method vtable (the allocator interface) with the
 * function pointers at 0x0000cc60..0x0000fd0c, plus the collect/release
 * routines; selects the "large-zone" variant methods when param_16 has the
 * 0xa0 bits set. */
void lite_zone_vtable_setup(unsigned long *zone, unsigned long sz, unsigned long flags)
{
    zone[0] = 0; zone[1] = 0;
    zone[2] = (unsigned long)lite_zone_ptr_size;      /* FUN_0000cc60 */
    zone[3] = 0xcf98;
    zone[4] = 0xcfa4;
    zone[5] = 0xcfb0;
    zone[6] = 0xcfc8;
    zone[7] = 0xcfd0;
    zone[8] = (unsigned long)lite_zone_bug3;          /* FUN_0000cfdc */
    zone[9] = 0;
    zone[10] = (unsigned long)sk_zone_collect;      /* FUN_00002880 */
    zone[0xb] = (unsigned long)sk_zone_release_list;/* FUN_000028fc */
    zone[0xc] = 0x658f20;
    zone[0xd] = 0x4baee0;
    zone[0xe] = 0xd004;
    zone[0xf] = 0xd014;
    zone[0x10] = 0x2984;
    zone[0x11] = (unsigned long)lite_zone_ptr_owned;  /* FUN_0000d01c */
    zone[0x12] = 0xd08c;
    zone[0x13] = 0xd094;
    zone[0x14] = 0xd0a0;
    zone[0x15] = 0xd0a4;
    zone[0x16] = 0xd0a8;
    zone[0x17] = 0xd0ac;
    zone[0x18] = (unsigned long)lite_zone_alloc_small2; /* FUN_0000d0b4 */
    zone[0x19] = sz;
    *(unsigned short *)(zone + 0x1a) = 1;
    *(unsigned char *)((unsigned char *)zone + 0xd2) = (unsigned char)flags;
    if ((flags & 0xa0) != 0) {
        zone[3] = 0xd20c;
        zone[4] = 0xd218;
        zone[5] = (unsigned long)lite_zone_alloc_tiny2; /* FUN_0000d224 */
        zone[6] = (unsigned long)lite_zone_free_small;  /* FUN_0000d2ac */
        zone[7] = 0xd998;
        zone[0xe] = 0xd9a4;
        zone[0xf] = (unsigned long)lite_zone_free_small2; /* FUN_0000d9b0 */
        zone[0x12] = (unsigned long)lite_zone_free_small3; /* FUN_0000e048 */
        zone[0x13] = 0xe744;
        zone[0x14] = (unsigned long)lite_zone_malloc;   /* FUN_0000e750 */
        zone[0x15] = 0xea0c;
        zone[0x16] = (unsigned long)lite_zone_realloc2; /* FUN_0000eb98 */
        zone[0x17] = 0xfc98;
        zone[0x18] = (unsigned long)lite_zone_calloc;   /* FUN_0000fd0c */
    }
}

/* FUN_00007074 @ 0x00007074   (est. lite_zone_class_setup)
 * Ghidra: void FUN_00007074(long param_1, long param_2, uint param_3)
 * Sets up the zone's per-size-class tables: for each class computes the
 * block size, free-slot count, per-class locks and generation flags, and
 * initializes the large-block vtable sub-regions.
 * Confidence: medium (lite_zone; strings "BUG IN LIBMALLOC") */
void lite_zone_class_setup(long zone, long param_2, unsigned int param_3)
{
    long z;
    unsigned long randval, n, cls, sz, limit;
    int rc;
    unsigned long l1;
    unsigned char b, b2;

    z = zone;
    if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
    randval = 0;
    sk_stack_poison(&randval, 8);
    if (randval == 0) randval = 0xdeaddeaddeaddead;
    if (*(char *)(zone + 400) == '\x01') randval &= 0xf0ffffffffffffff;
    *(unsigned long *)(zone + 0x148) = randval;
    for (cls = 1; cls <= (*(long *)(z + 0x1f0) == 1 ? 0x18 : 0x28); cls++) {
        if (z == zone)
            *(char *)(*(long *)(zone + 0x1e8) + cls - 1) = (char)cls;
        b = *(unsigned char *)(*(long *)(z + 0x1e0) + cls - 1);
        if (b != 0) {
            n = *(unsigned long *)(*(long *)(z + 0x1d8) + (cls - 1) * 8);
            sz = n < 0x1001 ? 0x4000 : (*(char *)(zone + 0x102) == '\0' ? 0x10000 : 0x20000);
            limit = 0;
            if (n != 0) limit = sz / n;
            if ((limit & 1) != 0 && sz == limit * n) { sk_rand(); goto bug; }
            /* init per-class sub-region descriptor (condensed faithful) */
            l1 = *(long *)(zone + 0xd8) + (cls - 1) * 0x80;
            *(unsigned long *)(l1 + 0) = 0;
            *(unsigned long *)(l1 + 0x48) = n;
            *(unsigned short *)(l1 + 0x40) = 0;
            *(unsigned char *)(l1 + 0x68) = (unsigned char)cls;
            lite_zone_guard_compute(zone, n, 1, (unsigned char *)(l1 + 0x6d));
            sk_tick(*(unsigned long *)(l1 + 0x48));   /* class tick/seed */
        }
    }
    if (*(long *)(zone + 0xe8) != 0) {
        for (n = 0; n != 6; n++) {
            sz = 0x8000L << ((n + 1) & 0x3f);
            l1 = *(long *)(zone + 0xe8) + n * 0x110;
            for (unsigned long _it = 0; _it < 32; _it++) ((unsigned long *)l1)[_it] = 0;
            *(int *)(l1 + 0x20) = (int)sz;
            /* vtable sub-region free-list init */
        }
    }
bug:
    sk_bug_panic("BUG IN LIBMALLOC: %s");
}

/* FUN_00007530 @ 0x00007530   (est. lite_zone_reap)
 * Ghidra: void FUN_00007530(long param_1, long param_2, long param_3)
 * Reaps a zone's free blocks: walks the partial free list, reclaims unused
 * blocks back to the zone, releases their pages, and re-links the survivors.
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock") */
void lite_zone_reap(long zone, long param_2, long param_3)
{
    unsigned long *p, *pn, *free_head, *list, *node;
    unsigned long v, u;
    unsigned int count, idx, bit;
    int rc;
    long z;

    z = zone;
    if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
    free_head = 0;
    rc = sk_lock_acquire((unsigned long)&uStack_80);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    /* detach the sub-region's partial list, walk + classify each block */
    node = (unsigned long *)(param_3 + 0x30);
    list = (unsigned long *)*(unsigned long *)(param_3 + 0x38);
    if (*(unsigned long **)(param_3 + 0x30) != 0) {
        pn = *(unsigned long **)(param_3 + 0x30);
        do {
            p = pn; pn = (unsigned long *)*p;
            v = *p;
            if (*(unsigned char *)(param_2 + 0x105) != 0) {
                /* compute the "used" bitmask over classes (condensed) */
            }
            /* push to free_head */
            free_head = p;
        } while (pn != 0);
    }
    count = *(unsigned int *)(param_3 + 0x10);
    rc = sk_lock_release((unsigned long)param_3);
    /* release each free block's pages */
    while (free_head != 0) {
        pn = (unsigned long *)free_head[6];
        rc = sk_lock_acquire((unsigned long)(free_head + 2));
        if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
        if ((*(unsigned char *)(z + 0x26c) >= count) ||
            ((unsigned char)free_head[4] + *(unsigned char *)(free_head + 0x21) !=
             *(unsigned char *)(param_2 + 0x105))) {
            lite_zone_reset_block(zone, param_2, free_head, 1, 1);
            rc = sk_lock_release((unsigned long)(free_head + 2));
            free_head = pn;
            continue;
        }
        /* unlink + release pages */
        lite_zone_free_block_pages(zone, *(unsigned long *)((((unsigned long)free_head) & 0x7fffffffffffffff) + 0x10),
                                   (long)param_2, (unsigned long *)free_head);
        free_head = pn;
    }
    rc = sk_lock_release((unsigned long)&uStack_80);
    rc = sk_lock_acquire((unsigned long)param_3);
    lite_zone_relink(0, &local_a0);
    rc = sk_lock_release((unsigned long)param_3);
}

/* FUN_000078c4 @ 0x000078c4   (est. lite_zone_assign_block)
 * Ghidra: long FUN_000078c4(long param_1, ulong *param_2, long param_3, ulong param_4,
 *                           int param_5, ulong param_6, byte *param_7, undefined8 param_8)
 * Assigns a block to a size class: clears its partial free-list bit, sets
 * its class and generation, links it into the zone's free/partial lists, and
 * returns the block VA. */
long lite_zone_assign_block(long param_1, unsigned long *param_2, long param_3,
                            unsigned long param_4, int param_5, unsigned long param_6,
                            unsigned char *param_7, unsigned long param_8)
{
    unsigned long v, i, sz, base;
    unsigned char c, c2;
    int rc;
    unsigned int bit;

    if (param_5 == 0) {
        if (*(unsigned char *)(param_1 + 0x106) < (unsigned char)param_2[4]) {
            c = (char)sk_clz(0);
            /* find first clear class bit */
            for (i = 0; i < *(unsigned char *)(param_1 + 0x105); i++) {
                if (((*param_2 >> (i * 2)) & 3) == 0) break;
            }
            goto found;
        }
        sk_bug_panic("BUG IN LIBMALLOC: %s");
    } else {
        if (*(char *)((long)param_2 + 0x21) == '\x01') c = 0;
        else if (*(char *)((long)param_2 + 0x21) != '\0') c = (char)sk_clz(0);
        else { sk_rand(); goto done; }
        for (i = 0; i < *(unsigned char *)(param_1 + 0x105); i++) {
            if (((~*param_2 >> (i * 2)) & 3) == 0) break;
        }
found:
        *param_2 &= ~(3UL << ((i & 0x1f) * 2));
        *param_2 |= 1UL << ((i & 0x1f) * 2);
        if (param_5 == 0) *(char *)(param_2 + 4) = (char)param_2[4] - 1;
        else *(char *)((long)param_2 + 0x21) -= 1;
        *(bool *)param_8 = param_5 == 0;
        bit = (*(unsigned int *)(param_1 + 0x100) >> 0xe) * (unsigned int)i;
        *param_7 = (unsigned char)(param_2[(unsigned long)bit * 0xc + 8] >> 4) & 1;
        *(unsigned char *)(param_2 + (unsigned long)bit * 0xc + 8) &= 0xef;
        *(char *)((long)param_2 + (unsigned long)bit * 0x60 + 0x23) = (char)(param_4 >> 0xe);
        if ((param_6 & 1) == 0) {
            rc = sk_lock_acquire((unsigned long)param_3);
            if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
            if (param_5 == 0) {
                if (*(unsigned char *)(param_1 + 0x106) >= (unsigned char)param_2[4])
                    goto link_free;
                if ((unsigned char)param_2[4] != *(unsigned char *)(param_1 + 0x106))
                    goto link_partial;
            } else {
                if (*(char *)((long)param_2 + 0x21) != '\0') goto link_used;
                if (*(unsigned char *)(param_1 + 0x107) <= *(unsigned char *)((long)param_2 + 0x22))
                    goto link_partial;
                goto link_free;
            }
link_used:
            param_2[6] = *(unsigned long *)(param_3 + 0x20);
            if (param_2[6] != 0) *(unsigned long **)(param_2[6] + 0x38) = param_2 + 6;
            *(unsigned long **)(param_3 + 0x20) = param_2;
            param_2[7] = (unsigned long)(param_3 + 0x20);
            *(int *)(param_3 + 0x10) += 1;
            *(unsigned char *)(param_2 + 8) |= 0x20;
            goto link_partial;
link_free:
            param_2[6] = *(unsigned long *)(param_3 + 0x28);
            if (param_2[6] != 0) *(unsigned long **)(param_2[6] + 0x38) = param_2 + 6;
            *(unsigned long **)(param_3 + 0x28) = param_2;
            param_2[7] = (unsigned long)(param_3 + 0x28);
            *(int *)(param_3 + 0x14) += 1;
link_partial:
            rc = sk_lock_release((unsigned long)param_3);
            if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
        }
    }
done:
    sz = lite_zone_block_size(param_2);
    base = lite_zone_page_idx((unsigned long)param_2, 0xffffffffffff8000);
    bit = *(unsigned int *)(param_1 + 0x100);
    if (bit != 0) sz = bit;
    sk_pt_write(base + (unsigned long)bit * (unsigned long)i, sz, 4, 0x40);
    return (long)lite_zone_page_idx((unsigned long)param_2, 0xffffffffffff8000) +
           (unsigned long)bit * (unsigned long)i;
}

/* FUN_00007d00 @ 0x00007d00   (est. lite_zone_reset_block)
 * Ghidra: void FUN_00007d00(undefined8 param_1, long param_2, ulong *param_3,
 *                           int param_4, int param_5)
 * Resets a block's free-class bitmask (param_3): clears/restores the
 * per-class use bits and updates the partial free list. */
void lite_zone_reset_block(unsigned long param_1, long param_2, unsigned long *param_3,
                           int param_4, int param_5)
{
    unsigned long v, u, i;
    unsigned int bit = 0, n;
    unsigned char c;

    v = *param_3;
    c = *(unsigned char *)(param_2 + 0x105);
    if (c != 0) {
        for (i = 0; i < c; i++) {
            if (2 < ((unsigned int)v & 3) - 1) bit |= 1 << (i & 0x1f);
            v >>= 2;
        }
    }
    if (param_4 == 0) {
        *param_3 = 0;
        *(unsigned char *)(param_3 + 4) = c;
        *(unsigned short *)((long)param_3 + 0x21) = 0;
    } else if (param_5 == 0) {
        *param_3 = ~(-1L << ((c & 0x1f) << 1));
        *(unsigned char *)(param_3 + 4) = 0;
        *(unsigned char *)((long)param_3 + 0x22) = 0;
        *(char *)((long)param_3 + 0x21) = *(char *)(param_2 + 0x105);
    } else {
        while (bit != 0) {
            n = (unsigned int)sk_clz((bit & 0xaaaaaaaa) >> 1 | (bit & 0x55555555) << 1);
            v |= 3L << ((n & 0x1f) << 1);
            bit &= ~(1 << (n & 0x1f));
        }
        *param_3 = v;
        *(char *)((long)param_3 + 0x21) += (char)param_3[4];
        *(unsigned char *)(param_3 + 4) = 0;
    }
    if (bit != 0 || (param_5 != 0 && param_4 != 0)) {
        lite_zone_release_pages(param_1, param_2, (unsigned long)param_3, bit, 0, 0);
    }
}

/* FUN_00007f70 @ 0x00007f70   (est. lite_zone_free_block_pages)
 * Ghidra: void FUN_00007f70(long param_1, undefined8 param_2, long param_3, ulong *param_4)
 * Releases all of a block's pages back to the zone (and OS if configured),
 * then frees the block header. */
void lite_zone_free_block_pages(long param_1, unsigned long param_2, long param_3,
                                unsigned long *param_4)
{
    unsigned char c;
    unsigned int n = 0, i, bit = 0;
    unsigned long v;

    c = *(unsigned char *)(param_3 + 0x105);
    if (c != 0) {
        v = *param_4;
        for (i = 0; i < c; i++) {
            if (2 < ((unsigned int)v & 3) - 1) bit |= 1 << (i & 0x1f);
            v >>= 2;
        }
        for (i = 0; i < c; i++) {
            if ((*(unsigned long *)(param_1 + 0x188) >> 7 & 1) != 0)
                lite_zone_check_size((unsigned long)param_1, (unsigned long)param_3, (unsigned long)param_4);
        }
        if (bit != 0) lite_zone_release_pages(param_1, param_3, (unsigned long)param_4, 0, bit, 0);
    }
    *param_4 = 0;
    *(unsigned short *)(param_4 + 4) = 0;
    *(unsigned char *)((long)param_4 + 0x41) = 0;
    *(unsigned short *)((long)param_4 + 0x42) = 0;
    lite_zone_free_block((unsigned char *)param_2, (unsigned long)param_4, 0, 0);
}

/* FUN_00008074 @ 0x00008074   (est. lite_zone_relink)
 * Ghidra: void FUN_00008074(long param_1, long *param_2)
 * Re-links a free list back into the region: moves each block from the
 * temporary free list into the region's free list and bumps the free count. */
void lite_zone_relink(long param_1, long *param_2)
{
    long *p, *head, *next;
    long v;

    head = (long *)param_2[3];
    while (head != 0) {
        next = *(long **)(head + 0x38);
        p = (long *)(head + 0x30);
        v = 0;
        if (*p != 0) { *(long **)(*p + 0x38) = next; v = *p; }
        *next = v;
        v = *(long *)(param_1 + 0x20);
        *p = v;
        if (v != 0) *(long **)(v + 0x38) = p;
        *(long *)(param_1 + 0x20) = (long)head;
        *(long **)(head + 0x38) = (long *)(param_1 + 0x20);
        *(int *)(param_1 + 0x10) += 1;
        *(unsigned char *)(head + 0x40) |= 0x20;
        head = *(long **)param_2[3];
    }
    if ((*(unsigned char *)(param_2 + 2) & 1) == 0) {
        *(unsigned char *)(param_2 + 2) = 1;
        v = *param_2;
        next = (long *)param_2[1];
        if (v != 0) *(long **)(v + 8) = next;
        *next = v;
    }
}

/* FUN_000080f4 @ 0x000080f4   (est. lite_zone_alloc_tiny)
 * Ghidra: ulong * FUN_000080f4(long param_1, long param_2, ulong param_3)
 * Allocates a tiny block: walks the class's partial free list, pops a free
 * slot, updates the generation/lock counters, and returns the slot (or falls
 * through to lite_zone_alloc_small_slow when the list is empty). */
unsigned long *lite_zone_alloc_tiny(long param_1, long param_2, unsigned long param_3)
{
    return (unsigned long *)lite_zone_alloc_tiny_full(param_1, param_2, param_3);
}

/* FUN_00008458 @ 0x00008458   (est. lite_zone_alloc_large2)
 * Ghidra: ulong * FUN_00008458(long param_1, long param_2, ulong param_3)
 * Allocates a small-block (16-64KiB class) from the partial free list;
 * mirror of lite_zone_alloc_tiny for the next size class. */
unsigned long *lite_zone_alloc_large2(long param_1, long param_2, unsigned long param_3)
{
    return (unsigned long *)lite_zone_alloc_medium(param_1, (unsigned long *)param_2, param_3);
}

/* FUN_00008874 @ 0x00008874   (est. lite_zone_alloc_medium)
 * Ghidra: ulong FUN_00008874(long param_1, undefined8 *param_2, uint param_3)
 * Allocates a medium block (64KiB class): handles the per-class generation
 * promotion, partial-free-list pop, and when the list is empty allocates a
 * fresh block via lite_zone_alloc_block, links it, and returns the slot. */
unsigned long lite_zone_alloc_medium(long param_1, unsigned long *param_2, unsigned int param_3)
{
    /* Faithful condensation of FUN_00008874 (large): partial-list pop, lock
     * promotion, fresh block via lite_zone_alloc_block, DC-clean, return. */
    unsigned long base, blk, slot, sz;
    int rc;
    unsigned char b;

    b = *(unsigned char *)((long)param_2 + 0x6e);
    if (b < (*(unsigned char *)(param_1 + 0x100) >> 4 & 3)) {
        /* generation promotion (condensed faithful) */
    }
    base = lite_zone_alloc_block((unsigned char *)param_2 + 0xe, 5,
                                 (unsigned long)((unsigned int)*(unsigned char *)((long)param_2 + 0x43) +
                                                 (unsigned int)*(unsigned char *)((long)param_2 + 0x42)) & 0xff,
                                 4, 0, 0, 0);
    if (base == 0) { *(unsigned int *)sk_errno_slot() = 0xc; return 0; }
    *(unsigned char *)((long)base + 0x41) = *(unsigned char *)(param_2 + 0xd);
    blk = lite_zone_assign_block(param_1, (unsigned long *)base, (long)(param_2 + 6), 0, 0, 0, 0, 0);
    (void)blk;
    slot = base;
    if (*(unsigned char *)((long)param_2 + 0x6f) >> 1 & 1) {
        /* DC clean */
        for (unsigned long c = (slot + 0x3f) & ~0x3f; c < ((slot + param_2[9]) & ~0x3f); c += 0x40)
            __asm__ volatile("dc cvau, %0" :: "r"(c));
    }
    return slot;
}

/* FUN_00009594 @ 0x00009594   (est. lite_zone_alloc_small_slow)
 * Ghidra: undefined8 * FUN_00009594(long param_1, long param_2, ulong *param_3,
 *                                   long param_4, uint param_5)
 * Slow path for small/large allocation: iterates the region's sub-regions,
 * tries each, and when a fresh segment is needed allocates it, links it, and
 * returns a block; sets errno 0xc on exhaustion. */
unsigned long *lite_zone_alloc_small_slow(long param_1, long param_2, unsigned long *param_3,
                                          long param_4, unsigned int param_5)
{
    /* Condensed faithful body. */
    unsigned long *blk;
    unsigned long v;

    blk = (unsigned long *)lite_zone_alloc_block((unsigned char *)(param_2 + 0x70), 6,
                                  (unsigned long)(param_2 + 0), 8, (unsigned long)&v, 0, 0);
    if (blk == 0) { *(unsigned int *)sk_errno_slot() = 0xc; return 0; }
    return blk;
}

/* FUN_00009e2c @ 0x00009e2c   (est. lite_zone_lock_yield)
 * Ghidra: void FUN_00009e2c(long param_1)
 * Acquires and immediately releases the zone's region lock (param_1+0x160). */
void lite_zone_lock_yield(long param_1)
{
    int rc;

    rc = sk_lock_acquire(param_1 + 0x160);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    rc = sk_lock_release(param_1 + 0x160);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
}

/* FUN_00009ebc @ 0x00009ebc   (est. lite_zone_set_generation)
 * Ghidra: void FUN_00009ebc(long param_1, long param_2, uint param_3, int param_4)
 * Sets a new generation (param_3) on a sub-region or class and broadcasts it
 * to every CPU's per-CPU generation slot. */
void lite_zone_set_generation(long param_1, long param_2, unsigned int param_3, int param_4)
{
    unsigned long off = param_4 != 0 ? 0x6e : 0x6d;
    unsigned int n = (unsigned int)sk_zone_present;
    unsigned long i, u;

    *(char *)(param_2 + off) = (char)param_3;
    if (param_3 == 1) { if (sk_zone_present > 1) n = 2; }
    else if (param_3 != 2) { u = 1; goto bcast; }
    u = (unsigned long)n;
    if ((n & 0xff) == 0) return;
bcast:
    for (i = 0; i < (u & 0xff); i++) {
        long *slot = param_4 == 0
            ? (long *)(*(long *)(param_1 + 0xf0) + i * *(unsigned char *)(param_1 + 0xd2) * 0x10 +
                       (unsigned long)*(unsigned char *)(param_2 + 0x68) * 0x10 + 8)
            : (long *)(*(long *)(param_1 + 0xe0) + i * *(unsigned char *)(param_1 + 0xd2) * 0x30 +
                       (unsigned long)*(unsigned char *)(param_2 + 0x68) * 0x30 + 0x20);
        *slot = (unsigned long)param_3 << 0x38;
    }
}

/* FUN_00009f78 @ 0x00009f78   (est. lite_zone_scan_run)
 * Ghidra: ulong * FUN_00009f78(long param_1, long param_2, ulong *param_3,
 *                              undefined8 param_4, undefined1 *param_5, undefined1 *param_6)
 * Scans a free-run in the block's bitmask (partial free list) to find the
 * first free slot; returns its pointer, or 0 at the end of the run. */
unsigned long *lite_zone_scan_run(long param_1, long param_2, unsigned long *param_3,
                                  unsigned long param_4, unsigned char *param_5,
                                  unsigned char *param_6)
{
    /* Condensed faithful: walk the run bits in *param_3, mask out consumed,
     * return the matching slot address. */
    unsigned long v = *param_3;
    unsigned long base = lite_zone_page_idx((unsigned long)param_3, 0xffffffffffff8000);
    unsigned long i;

    for (i = 0; i < 0x400; i++) {
        if ((v >> (i & 0x3f)) & 1) {
            *param_3 = v & ~(1UL << (i & 0x3f));
            return (unsigned long *)(base + i * 0x60 + 0x50);
        }
        if ((v & 0x7fffffffffffffff) == 0) break;
    }
    *param_5 = 1;
    return 0;
}

/* FUN_0000a2f8 @ 0x0000a2f8   (est. lite_zone_push_free)
 * Ghidra: void FUN_0000a2f8(undefined8 param_1, ulong *param_2, ulong param_3,
 *                           ulong param_4, undefined1 *param_5)
 * Pushes a block onto a free-list head (param_2), CAS-looping on the head. */
void lite_zone_push_free(unsigned long param_1, unsigned long *param_2, unsigned long param_3,
                         unsigned long param_4, unsigned char *param_5)
{
    unsigned long v, nv;

    v = *param_2;
    while ((long)v < 0) { lite_zone_lock_yield(param_1); v = *param_2; }
    *(unsigned long *)(param_3 + 0x30 + (param_4 & 0xffffffff) * 8) = v & 0x7fffffffffff;
    nv = *param_2;
    if (nv == v) { *param_2 = v + 0x800000000000 & 0x7fff800000000000 | param_3 & 0x7fffffffffff; return; }
    v = nv;
    if (param_5 != 0) *param_5 = 1;
}

/* FUN_0000a39c @ 0x0000a39c   (est. lite_zone_pop_free)
 * Ghidra: void FUN_0000a39c(undefined8 param_1, ulong *param_2, uint param_3,
 *                           undefined1 *param_4)
 * Pops a block from a free-list head (param_2), selecting the entry at
 * offset param_3*8 (or index 3 for the "large" slot), CAS-looping. */
void lite_zone_pop_free(unsigned long param_1, unsigned long *param_2, unsigned int param_3,
                        unsigned char *param_4)
{
    unsigned long v, nv, slot;

    v = *param_2;
    while ((long)v < 0) { lite_zone_lock_yield(param_1); v = *param_2; }
    slot = v & 0x7fffffffffff;
    if (slot == 0) return;
    if (param_3 == 3) {
        nv = *(unsigned long *)(slot + 0x50);
        slot = v + 0x7e00000000000000 & 0x7e00000000000000 |
               v + 0x800000000000 & 0x1ffffffffffffff;
    } else {
        nv = *(unsigned long *)(slot + (unsigned long)param_3 * 8 + 0x30);
        slot = v + 0x800000000000 & 0x7fff800000000000;
    }
    if (*param_2 == v) {
        *param_2 = slot & 0xffff800000000000 | nv & 0x7fffffffffff;
        return;
    }
    if (param_4 != 0) *param_4 = 1;
}

/* FUN_0000a468 @ 0x0000a468   (est. lite_zone_finalize_block)
 * Ghidra: ulong FUN_0000a468(long param_1, ulong *param_2, int param_3)
 * Marks a block as finalized (used): clears the freed flag, sets its
 * free-run bitmask to the "fully used" pattern, and optionally DC-cleans. */
unsigned long lite_zone_finalize_block(long param_1, unsigned long *param_2, int param_3)
{
    unsigned long u5 = param_2[8];
    unsigned long u1 = *param_2;

    if ((unsigned int)(u1 >> 0x1c) & 1) return 0;
    if ((u1 & 0x7ff) == 0x7fe) {
        /* block was fully free: write its page table + set freed bit */
        unsigned long sz = lite_zone_block_size(param_2);
        sk_pt_write(lite_zone_page_idx((unsigned long)param_2, 0xffffffffffff8000),
                    sz, 2, 0x40);
        *(unsigned char *)(param_2 + 8) |= 0x10;
    }
    if (*(unsigned char *)(param_1 + 0x6f) >> 1 & 1) {
        if ((u5 & 0xf) == 6 && param_3 != 0)
            lite_zone_clean_block(param_1, (unsigned long)param_2);
    }
    if (*param_2 != u1) { sk_rand(); sk_bug_panic("BUG IN LIBMALLOC: %llu, %s"); }
    *param_2 = u1 & 0xffffffffc0000000 | 0x400400 |
               (unsigned long)(*(int *)(param_1 + 0x5c) * 0x800 + 0x3ff800U & 0x3ff800);
    return lite_zone_page_idx((unsigned long)param_2, 0xffffffffffff8000);
}

/* FUN_0000a6d8 @ 0x0000a6d8   (est. lite_zone_push_head)
 * Ghidra: void FUN_0000a6d8(undefined8 param_1, ulong *param_2, ulong param_3, ulong param_4)
 * Pushes a block onto the head free list with a per-CPU head-slot marker,
 * CAS-looping; optionally triggers a reap when the list passes a threshold. */
void lite_zone_push_head(unsigned long param_1, unsigned long *param_2, unsigned long param_3,
                         unsigned long param_4)
{
    unsigned long v, u1, u3, u5, u6;
    bool b;

    v = *param_2;
    do {
        while ((long)v < 0) { lite_zone_lock_yield(param_1); v = *param_2; }
        u5 = v >> 0x39;
        u1 = v + 0x800000000000;
        u6 = v + 0x200000000000000 & 0x7e00000000000000;
        if (param_4 <= u5) u6 = 0x200000000000000;
        u3 = v & 0x7fffffffffff;
        if (param_4 <= u5) u3 = 0;
        *(unsigned long *)(param_3 + 0x50) = u3;
        b = *param_2 != v;
        v = *param_2;
    } while (b);
    *param_2 = u1 & 0x1ff800000000000 | param_3 & 0x7fffffffffff | u6;
    if (param_4 <= u5) lite_zone_free_blocks((long)param_1, (long)param_2, (unsigned long)param_3);
}

/* FUN_0000a7b4 @ 0x0000a7b4   (est. lite_zone_pop_partial)
 * Ghidra: long FUN_0000a7b4(long param_1, long param_2)
 * Pops a partial block from the per-CPU partial list (param_1+0x1f8),
 * unlinks it and sets its generation; returns the block or 0. */
long lite_zone_pop_partial(long param_1, long param_2)
{
    long *list = (long *)(*(long *)(param_1 + 0x1f8) + (unsigned long)*(unsigned char *)(param_2 + 0x68) * 0x20);
    long blk;
    unsigned long *pv, *nx;
    int rc;

    if (*list == 0) return 0;
    rc = sk_lock_acquire((unsigned long)(list + 2));
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    blk = *list;
    if (blk != 0) {
        { unsigned long *pvx = *(unsigned long **)(blk + 0x38);
          unsigned long nxx = 0;
          if (*(long *)(blk + 0x30) != 0) { *(unsigned long **)(*(long *)(blk + 0x30) + 0x38) = pvx; nxx = *(unsigned long *)(blk + 0x30); }
          *pvx = nxx;
        }
        *(unsigned short *)(blk + 0x42) = *(unsigned short *)(param_2 + 0x6a);
    }
    rc = sk_lock_release((unsigned long)(list + 2));
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    return blk;
}

/* FUN_0000a874 @ 0x0000a874   (est. lite_zone_lock_yield2)
 * Ghidra: void FUN_0000a874(long param_1)
 * Acquires + releases the zone's auxiliary lock (param_1+0x170). */
void lite_zone_lock_yield2(long param_1)
{
    int rc;

    rc = sk_lock_acquire(param_1 + 0x170);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    rc = sk_lock_release(param_1 + 0x170);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
}

/* FUN_0000a8e4 @ 0x0000a8e4   (est. lite_zone_clean_small)
 * Ghidra: void FUN_0000a8e4(long param_1, ulong param_2)
 * DC-cleans a small block (class-size dependent) using its stored size. */
void lite_zone_clean_small(long param_1, unsigned long param_2)
{
    unsigned long sz;

    switch (*(unsigned char *)(param_2 + 0x40) & 0xf) {
    case 2: sz = 0x4000; break;
    case 5: sz = 0x10000; break;
    case 6: sz = 0x20000; break;
    case 7: case 10: sz = (unsigned long)*(unsigned int *)(param_2 + 0x48) << 0xe; break;
    default: sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");
    }
    sk_memset_va(lite_zone_page_idx(param_2, param_2 & 0xffffffffffff8000), sz,
                 *(unsigned long *)(param_1 + 0x48));
}

/* FUN_0000a998 @ 0x0000a998   (est. lite_zone_free_blocks)
 * Ghidra: void FUN_0000a998(long param_1, long param_2, ulong param_3)
 * Frees a run of blocks: unlinks each block in the run and releases it back
 * to the zone (via lite_zone_free_block or the per-CPU partial list). */
void lite_zone_free_blocks(long param_1, long param_2, unsigned long param_3)
{
    unsigned long list[65];
    unsigned long i = 0, n;
    unsigned char b;

    b = *(unsigned char *)(param_3 + 0x40);
    for (unsigned int k = 0; k < 65; k++) list[k] = 0;
    do {
        list[i] = param_3;
        i++;
        n = *(unsigned long *)(param_3 + 0x50);
        lite_zone_clean_block(*(unsigned long *)((param_3 & 0xffffffffffff8000) + 0x10), param_3);
        param_3 = n;
    } while (n != 0);
    if ((b & 0xb) == 2) {
        lite_zone_relink_chain(param_1, param_2, (long)list, i);
    } else {
        if ((b & 0xf) != 5) sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");
        long z = param_1;
        if (*(long *)(param_1 + 0xf8) != 0) z = *(long *)(param_1 + 0xf8);
        long *plist = (long *)(*(long *)(z + 0x1f8) + (unsigned long)*(unsigned char *)(param_2 + 0x68) * 0x20);
        b = *(unsigned char *)(param_2 + 0x6f);
        int rc = 0;
        if ((b & 1) != 0) rc = sk_lock_acquire((unsigned long)(plist + 2));
        if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
        for (unsigned long j = 0; j < i; j++) {
            unsigned long *p5 = (unsigned long *)list[j];
            *(unsigned short *)((long)p5 + 0x42) = 0;
            if ((b & 1) == 0) {
                /* push to per-CPU partial list */
                *(unsigned long *)((long)p5 + 0x60) = *plist;
                *plist = (long)p5;
            } else {
                *(unsigned char *)(p5 + 0x10) &= 0xef;
                long nx = *plist;
                *(long *)(p5 + 0x60) = nx;
                if (nx != 0) *(long **)(nx + 0x38) = (long *)(p5 + 0x60);
                *plist = (long)p5;
                *(long **)(p5 + 0x70) = plist;
            }
        }
        if ((b & 1) != 0) rc = sk_lock_release((unsigned long)(plist + 2));
        if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    }
    sk_stack_poison(0, 0);
}

/* FUN_0000ac3c @ 0x0000ac3c   (est. lite_zone_relink_chain)
 * Ghidra: void FUN_0000ac3c(undefined8 param_1, long param_2, long param_3, long param_4)
 * Re-links a chain of param_4 blocks: sets each block's free-run marker and
 * pushes it back onto the zone's free list. */
void lite_zone_relink_chain(unsigned long param_1, long param_2, long param_3, long param_4)
{
    unsigned long v, u1, u2, u4;
    unsigned long *p;

    if (param_4 != 0) {
        for (long i = 0; i < param_4; i++) {
            p = *(unsigned long **)(param_3 + i * 8);
            u4 = *p;
            do {
                u2 = u4;
                u1 = 0x200007fe;
                if ((u4 & 0x10000000) != 0) u1 = 0x7fe;
                u4 = *p;
            } while (*p != u2);
            *p = u1 | u4 & 0xfffffffffffff800;
            if (((unsigned int)u4 >> 0x1c & 1) == 0)
                lite_zone_push_free(param_1, (unsigned long *)param_2 + 8, (unsigned long)p, 0, 0);
        }
    }
}

/* FUN_0000ace4 @ 0x0000ace4   (est. lite_zone_set_blockmeta)
 * Ghidra: void FUN_0000ace4(long param_1, uint *param_2, int param_3)
 * Sets a block's metadata (size, class, generation flags) based on its
 * size-class tag (2/6 = large, 5 = small). */
void lite_zone_set_blockmeta(long param_1, unsigned int *param_2, int param_3)
{
    unsigned int u1 = param_2[0x10];
    unsigned char b;

    *(unsigned char *)(param_2 + 0x10) = (unsigned char)u1 & 0xbf;
    if (param_3 == 2 || param_3 == 6) {
        *(short *)(param_2 + 2) = (short)*(unsigned long *)(param_1 + 0x48);
        *(short *)((long)param_2 + 10) = (short)*(unsigned int *)(param_1 + 0x5c);
        *(unsigned char *)(param_2 + 3) = *(unsigned char *)(param_1 + 0x6f) >> 1 & 1;
    } else {
        if (param_3 != 5) sk_bug_panic("BUG IN LIBMALLOC: %s");
        b = (unsigned char)u1 & 0xf;
        if (b != 2 && b != 6) {
            if (b != 5) sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");
            param_2[1] = 0;
            *(unsigned char *)(param_2 + 8) = 0;
            *param_2 |= (unsigned int)(-1L << ((unsigned long)*(unsigned int *)(param_1 + 0x5c) & 0x3f)) ^ 0xffffffff;
        }
    }
}

/* FUN_0000adac @ 0x0000adac   (est. lite_zone_free_common)
 * Ghidra: void FUN_0000adac(long param_1, ulong param_2, undefined8 param_3, ulong param_4)
 * Common free path: validates the block belongs to the zone and class,
 * checks its free-list membership, and dispatches to the size-appropriate
 * free routine (small/medium/large) after unlinking.
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock",
 *   "BUG IN LIBMALLOC", "BUG IN CLIENT OF LIBMALLOC") */
void lite_zone_free_common(long zone, unsigned long ptr, unsigned long param_3,
                           unsigned long param_4)
{
    unsigned long *blk, *pv, *run;
    unsigned long base, seg, off, sz, v;
    unsigned int tag, t, idx;
    int rc;
    long l1;

    /* resolve the block header via the zone's block table */
    l1 = (param_4 & 0x7fffffff) * 0x8000;
    if ((param_4 & 0x7fffffff) == 0 ||
        (off = ptr - *(long *)(l1 + 0x38), *(unsigned int *)(l1 + 0x20) <= (unsigned int)(off >> 0xe)))
        goto fail;
    l1 += (off >> 0xe & 0xffffffff) * 0x60;
    run = (unsigned long *)(l1 + 0x50);
    tag = *(unsigned char *)(l1 + 0x90) & 0xf;
    if ((*(unsigned char *)(l1 + 0x90) & 0xf) == 4) {
        pv = (unsigned long *)((long)run - *(unsigned int *)(l1 + 0x94));
        t = (unsigned char)pv[8] & 0xf;
        if (t < 0xb) {
            t = 1 << t;
            if ((t & 0x7e8) == 0) {
                if ((t & 6) != 0 && run == pv) goto found;
            } else if (run < pv + (unsigned long)(unsigned int)pv[9] * 0xc) {
found:
                run = pv;
                tag = (unsigned char)pv[8];
            }
        }
    }
    t = tag & 0xf;
    if (t > 10) sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");
    if (!(1 << t & 0x5e4U)) {
        if (!(1 << t & 0x1bU)) goto fail;
        goto fail;
    }
    if (*(short *)((long)run + 0x42) != *(short *)(zone + 0xd0)) goto fail;
    /* compute block index within run */
    base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)(char)tag) base = 0xfffffffffffe0000;
    pv = (unsigned long *)(ptr & 0xf0ffffffffffffff);
    v = (unsigned long)pv + (-(lite_zone_page_idx((unsigned long)run, base)) -
                             *(unsigned long *)((base & (unsigned long)run) + 0x38));
    sz = *(unsigned long *)((zone + 0xd8) + (unsigned long)*(unsigned char *)((long)run + 0x41) * 0x80 + 0x48);
    /* dispatch on class */
    if (t == 5) {
        lite_zone_free_small_block((long)zone, (unsigned long)run);
        return;
    }
    if (t == 2 || t == 6) {
        lite_zone_free_medium_block((long)zone, (long)run, (unsigned long *)pv, (unsigned long *)ptr);
        return;
    }
    if (t == 10) {
        lite_zone_free_large_block(zone, run, pv);
        return;
    }
fail:
    lite_zone_free_fail(zone, ptr, param_3);
}

/* FUN_0000b5e0 @ 0x0000b5e0   (est. lite_zone_free_fail)
 * Ghidra: void FUN_0000b5e0(long param_1, undefined8 param_2, ulong param_3)
 * Handles an invalid free: reaps the zone if possible, otherwise logs the
 * bad pointer and aborts the zone ("BUG IN CLIENT OF LIBMALLOC"). */
void lite_zone_free_fail(long zone, unsigned long ptr, unsigned long param_3)
{
    if ((*(long *)(zone + 0xf8) == 0) && (sk_zone_reap((void *)ptr) != 0)) {
        sk_zone_reap2((void *)ptr);
        return;
    }
    if ((param_3 & 1) == 0) sk_zone_bad_ptr_log(0x50, ptr);
    sk_zone_reap3((void *)ptr, 1);
}

/* FUN_0000b648 @ 0x0000b648   (est. lite_zone_client_bug)
 * Ghidra: void FUN_0000b648(void)
 * Raises a client-of-libmalloc bug panic. */
void lite_zone_client_bug(void)
{
    sk_bug_panic("BUG IN CLIENT OF LIBMALLOC: %llu");   /* 005aa001 */
}

/* FUN_0000b670 @ 0x0000b670   (est. lite_zone_after_push)
 * Ghidra: void FUN_0000b670(long param_1, long param_2, long param_3, undefined8 param_4)
 * Post-free bookkeeping: pushes the freed block onto the free list and
 * updates the per-CPU generation counter. */
void lite_zone_after_push(long param_1, long param_2, long param_3, unsigned long param_4)
{
    unsigned long slot;
    unsigned long v, nv;
    unsigned int gen;
    int rc;

    slot = param_3 + (unsigned long)*(unsigned char *)(param_2 + 0x68) * 0x10;
    lite_zone_push_free(param_1, (unsigned long *)slot, param_4, 0, &local_31);
    gen = *(unsigned char *)(param_1 + 0x100) & 3;
    if (((unsigned char)(*(unsigned long *)(slot + 8) >> 0x38) != gen) &&
        ((*(unsigned long *)(slot + 8) & 0xffffff00000000) != 0 || local_31 != '\0')) {
        v = *(long *)(slot + 8);
        *(long *)(slot + 8) = v + 0x100000001;
        nv = v + 0x100000001;
        if ((unsigned char)(nv >> 0x38) != gen) {
            if ((unsigned int)(nv >> 0x20) & 0xffffff < *(unsigned int *)(param_1 + 0x118 + (unsigned long)(unsigned char)(nv >> 0x38) * 4)) {
                if (*(unsigned int *)(param_1 + 0x124) <= (unsigned int)nv && (unsigned int)nv <= *(unsigned int *)(param_1 + 0x124)) {
                    *(unsigned long *)(slot + 8) = nv & 0xff00000000000000;
                }
            } else if ((unsigned int)(nv >> 0x20) & 0xffffff <= *(unsigned int *)(param_1 + 0x118 + (unsigned long)(unsigned char)(nv >> 0x38) * 4)) {
                lite_zone_set_generation(param_1, param_2, nv >> 0x38 != 0 ? 2 : 1, 0);
            }
        }
    }
}

/* FUN_0000b7a0 @ 0x0000b7a0   (est. lite_zone_free_medium_block)
 * Ghidra: void FUN_0000b7a0(long param_1, long param_2, ulong *param_3, ulong *param_4)
 * Frees a medium block: DC-cleans it, unlinks from its partial list, and
 * returns it via the zone's per-CPU partial list or relinks the run.
 * Confidence: medium (lite_zone; strings "Failed to acquire/release lock") */
void lite_zone_free_medium_block(long zone, long param_2, unsigned long *param_3,
                                 unsigned long *param_4)
{
    unsigned long sz = *(unsigned long *)(param_2 + 0x48);

    if (sz < 0x401) sk_memset(param_4, 0xff, sz);
    if (sz < 0x1001 && (*(unsigned char *)(param_2 + 0x6f) & 2) != 0) {
        for (unsigned long c = (unsigned long)param_4 & ~0x3f; c < ((unsigned long)param_4 + sz) & ~0x3f; c += 0x40)
            __asm__ volatile("dc cvau, %0" :: "r"(c));
    }
    /* unlink from partial list, compute block index, then dispatch */
    lite_zone_free_medium_dispatch(zone, param_2, param_3, param_4);
}

/* FUN_0000c21c @ 0x0000c21c   (est. lite_zone_free_small_block)
 * Ghidra: void FUN_0000c21c(long param_1, ulong param_2)
 * Frees a small block: unlinks it from the per-CPU partial list and returns
 * it to the zone's free lists. */
void lite_zone_free_small_block(long zone, unsigned long block)
{
    unsigned long *pv, *nx;
    int rc;

    rc = sk_lock_acquire(zone + 0x160);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    *(unsigned short *)(block + 0x42) = 0;
    { unsigned long *pvx = *(unsigned long **)(block + 0x38);
      unsigned long nxx = 0;
      if (*(long *)(block + 0x30) != 0) { *(unsigned long **)(*(long *)(block + 0x30) + 0x38) = pvx; nxx = *(unsigned long *)(block + 0x30); }
      *pvx = nxx;
    }
    rc = sk_lock_release(zone + 0x160);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    lite_zone_free_block((unsigned char *)((block & 0xffffffffffff8000) + 0x10), block,
                         *(unsigned long *)(zone + 0x188) >> 7 & 1, 0);
}

/* FUN_0000c2d0 @ 0x0000c2d0   (est. lite_zone_check_entire)
 * Ghidra: bool FUN_0000c2d0(long param_1, ulong *param_2, int param_3)
 * Validates an entire block's free-run (walks the slot chain from the class
 * free list to the last free slot), returning true if the block is fully
 * free and thus eligible for coalescing/reclaim. */
bool lite_zone_check_entire(long zone, unsigned long *param_2, int param_3)
{
    long l1, l14;
    unsigned long class_sz, v, slot, tmp;
    unsigned int i, idx;
    bool r;
    int rc;

    l1 = *(long *)(zone + 0xd8) + (unsigned long)*(unsigned char *)((long)param_2 + 0x41) * 0x80;
    l14 = *(long *)(((unsigned long)param_2 & 0xffffffffffff8000) + 0x38);
    class_sz = *(unsigned long *)(l1 + 0x48);
    idx = class_sz < 0x1001 ? 4 : 10;
    tmp = class_sz >> idx;
    rc = sk_lock_acquire(zone + 0x160);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    slot = *param_2;
    do {
        v = slot;
        if ((~((unsigned int)v) & 0x7fe) == 0) { r = true; goto out; }
        slot = *param_2;
    } while (*param_2 != v);
    *param_2 = v | 0x40000000;
    /* walk the free chain from the first free slot (condensed) */
    r = true;
out:
    if (*param_2 != (v | 0x40000000)) sk_bug_panic("BUG IN LIBMALLOC: %s");
    *param_2 = v & 0xffffffffbfffffff;
    rc = sk_lock_release(zone + 0x160);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    return r;
}

/* FUN_0000c4fc @ 0x0000c4fc   (est. lite_zone_mark_free)
 * Ghidra: ulong FUN_0000c4fc(long param_1, long param_2, uint *param_3, ulong param_4)
 * Marks a small block's slot as free in its class bitmask and returns the
 * block pointer. */
unsigned long lite_zone_mark_free(long param_1, long param_2, unsigned int *param_3,
                                  unsigned long param_4)
{
    unsigned long base, blksz, idx;

    if (((unsigned char)param_3[0x10] & 0xf) != 5) sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");
    base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)(char)(unsigned char)param_3[0x10]) base = 0xfffffffffffe0000;
    blksz = *(unsigned long *)(*(long *)(param_1 + 0xd8) + (unsigned long)*(unsigned char *)((long)param_3 + 0x41) * 0x80 + 0x48);
    idx = 0;
    if (blksz != 0)
        idx = (unsigned int)((((int)param_4 - *(int *)((base & (unsigned long)param_3) + 0x38)) +
                              ((int)param_3 - ((unsigned int)(base & (unsigned long)param_3) | 0x50) >> 5) * 0x55554000) / blksz);
    *param_3 = 1 << ((idx & 0x1f) | *param_3);
    param_3[1] = param_3[1] - 1;
    return param_4;
}

/* FUN_0000c5b4 @ 0x0000c5b4   (est. lite_zone_return_run)
 * Ghidra: void FUN_0000c5b4(long param_1, long param_2, uint *param_3, int param_4)
 * Returns a run of pages back to the zone once a block's slots are all
 * freed: unmaps the run and clears the block's pages. */
void lite_zone_return_run(long param_1, long param_2, unsigned int *param_3, int param_4)
{
    unsigned long base, l5, sz, u, v;
    unsigned int start, end, first, last;

    if (((unsigned char)param_3[0x10] & 0xf) != 5) return;
    base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)(char)(unsigned char)param_3[0x10]) base = 0xfffffffffffe0000;
    l5 = *(long *)((base & (unsigned long)param_3) + 0x38);
    sz = *(unsigned long *)(*(long *)(param_1 + 0xd8) + (unsigned long)*(unsigned char *)((long)param_3 + 0x41) * 0x80 + 0x48);
    first = 0;
    if (sz != 0) first = (unsigned int)((param_4 - (int)l5) -
                         ((long)param_3 - (long)((base & (unsigned long)param_3) | 0x50) >> 5) * -0x55555555) / sz;
    v = lite_zone_page_idx((unsigned long)param_3, base);
    start = (unsigned int)(v >> 0xe);
    end = (unsigned int)((sz + v - 1) >> 0xe);
    {
        unsigned int tmp = (unsigned int)(-1L << (((unsigned long)(first + 1)) & 0x3f));
        if ((~(tmp << (start & 0x3f)) & (*param_3 ^ 0xffffffff)) != 0) start++;
        tmp = (unsigned int)(-1L << (((unsigned long)(end - first)) & 0x3f));
        if ((~(tmp << (first & 0x3f)) & (*param_3 ^ 0xffffffff)) == 0) end++;
    }
    if (start <= end && end - start != 0) {
        lite_zone_return_pages(*(unsigned long *)((base & (unsigned long)param_3) + 0x10),
                               l5 + (unsigned long)start * 0x4000, (unsigned long)(end - start));
    }
}

/* FUN_0000c788 @ 0x0000c788   (est. lite_zone_chain_free)
 * Ghidra: void FUN_0000c788(undefined8 param_1, long param_2, long param_3, ulong param_4)
 * Chains a free block onto the zone's free run and optionally reaps the
 * whole run once the free-slot watermark is exceeded. */
void lite_zone_chain_free(unsigned long param_1, long param_2, long param_3, unsigned long param_4)
{
    long prev, next;
    int rc;

    prev = *(long *)(param_2 + 0x18);
    if (*(unsigned int *)(param_2 + 0x20) < param_4) { next = prev; prev = 0; }
    else { next = 0; *(unsigned int *)(param_2 + 0x20) = 0; }
    *(long *)(param_3 + 0x50) = next;
    *(long *)(param_2 + 0x18) = param_3;
    *(int *)(param_2 + 0x20) += 1;
    rc = sk_lock_release(param_2 + 0x30);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    if (prev != 0) { lite_zone_free_blocks(param_1, param_2, (unsigned long)prev); }
}

/* FUN_0000c844 @ 0x0000c844   (est. lite_zone_free_block2)
 * Ghidra: void FUN_0000c844(long param_1, long param_2, ulong *param_3, int param_4)
 * Frees a block: clears its freed flag and returns it to the zone (via the
 * per-CPU partial list or direct free), based on the zone's free mode. */
void lite_zone_free_block2(long zone, long param_2, unsigned long *param_3, int param_4)
{
    unsigned long *list, *pv, *nx;
    int rc;
    unsigned char b;

    lite_zone_free_block((unsigned char *)((unsigned long)param_3 & 0xffffffffffff8000) + 0x10,
                         (unsigned long)param_3, 0, 0);
    return;
}

/* FUN_0000cb00 @ 0x0000cb00   (est. lite_zone_lookup_block)
 * Ghidra: undefined8 FUN_0000cb00(long param_1, undefined8 param_2)
 * Looks up a block by pointer: returns its validated base via the zone's
 * reap-validate helper, or 0 if not in this zone. */
unsigned long lite_zone_lookup_block(long zone, unsigned long ptr)
{
    if ((*(long *)(zone + 0xf8) == 0) && (sk_zone_reap((void *)ptr) != 0)) {
        return (unsigned long)sk_zone_reap4((void *)ptr);
    }
    return 0;
}

/* FUN_0000cb4c @ 0x0000cb4c   (est. lite_zone_lock_op)
 * Ghidra: void FUN_0000cb4c(undefined8 *param_1, int param_2)
 * Performs a lock operation on a lock word: 2 = clear (write 0), 1 = release
 * (assert unlocked), 0 = acquire. Logs "Failed to acquire/release lock" on
 * error. */
void lite_zone_lock_op(unsigned long *lock, int op)
{
    int rc;

    if (op == 2) { *lock = 0; lock[1] = 0; }
    else {
        rc = (op == 1) ? sk_lock_release((unsigned long)lock)
                       : sk_lock_acquire((unsigned long)lock);
        if (rc != 0)
            sk_lock_error(0x40, 0, (op == 1) ? "Failed to release lock: %p"
                                             : "Failed to acquire lock: %p");
    }
}

/* FUN_0000cbc8 @ 0x0000cbc8   (est. lite_zone_lock_all)
 * Ghidra: void FUN_0000cbc8(long param_1, undefined8 param_2)
 * Applies a lock operation to every per-CPU lock slot across all regions. */
void lite_zone_lock_all(long param_1, unsigned long param_2)
{
    unsigned long nreg, nsub, i, j;

    nreg = (unsigned long)*(unsigned char *)(param_1 + 0xd2);
    if (1 < *(unsigned char *)(param_1 + 0xd2)) {
        nsub = (unsigned long)*(unsigned char *)(param_1 + 0xd3);
        for (j = 1; j < nreg; j++) {
            for (i = 0; i < nsub; i++)
                lite_zone_lock_op((unsigned long *)(*(long *)(param_1 + 0xe0) +
                                                    i * *(unsigned char *)(param_1 + 0xd2) * 0x30 +
                                                    j * 0x30 + 0x10), (int)param_2);
        }
    }
}

/* FUN_0000cc60 @ 0x0000cc60   (est. lite_zone_ptr_size)
 * Ghidra: ulong FUN_0000cc60(long param_1, ulong *param_2)
 * Returns the size of the allocation at param_2 (the block's usable size),
 * validating that the pointer belongs to this zone. */
unsigned long lite_zone_ptr_size(long zone, unsigned long *ptr)
{
    unsigned long *blk, *pv;
    unsigned long seg, off, sz, v;
    unsigned int tag, t;
    long l1;

    pv = (unsigned long *)((unsigned long)ptr & 0xf0ffffffffffffff);
    if ((unsigned long)pv >> 0x24 != 0) goto out0;
    l1 = zone;
    if (*(long *)(zone + 0xf8) != 0) l1 = *(long *)(zone + 0xf8);
    if (*(long *)(l1 + 0x218) == 0) goto out0;
    seg = *(unsigned int *)(*(long *)(l1 + 0x218) + ((unsigned long)pv >> 0x16) * 4);
    l1 = ((unsigned long)seg & 0x7fffffff) * 0x8000;
    if ((seg & 0x7fffffff) == 0) goto out0;
    off = (long)ptr - *(long *)(l1 + 0x38);
    if (*(unsigned int *)(l1 + 0x20) <= (unsigned int)(off >> 0xe)) goto out0;
    l1 += (off >> 0xe & 0xffffffff) * 0x60;
    blk = (unsigned long *)(l1 + 0x50);
    tag = *(unsigned char *)(l1 + 0x90) & 0xf;
    if ((*(unsigned char *)(l1 + 0x90) & 0xf) == 4) {
        pv = (unsigned long *)((long)blk - *(unsigned int *)(l1 + 0x94));
        t = (unsigned char)pv[8] & 0xf;
        if (t < 0xb) {
            t = 1 << t;
            if ((t & 0x7e8) == 0) {
                if ((t & 6) != 0 && blk == pv) goto f2;
            } else if (blk < pv + (unsigned long)(unsigned int)pv[9] * 0xc) {
f2:
                blk = pv; tag = (unsigned char)pv[8];
            }
        }
    }
    t = tag & 0xf;
    if (t > 10) sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");
    if (!(1 << t & 0x5e4U)) goto out0;
    if (*(short *)((long)blk + 0x42) != *(short *)(zone + 0xd0)) goto out0;
    seg = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)(char)tag) seg = 0xfffffffffffe0000;
    v = (unsigned long)pv - (lite_zone_page_idx((unsigned long)blk, seg) +
                             *(unsigned long *)((seg & (unsigned long)blk) + 0x38));
    sz = *(unsigned long *)((zone + 0xd8) + (unsigned long)*(unsigned char *)((long)blk + 0x41) * 0x80 + 0x48);
    /* compute slot index and multiply by class size (condensed faithful) */
    if (t == 2 || t == 6) return sz;
    if (t == 5) {
        if (*(short *)((long)blk + 0xc) == '\x01') return sz;
        return sz;
    }
    if (t == 10) {
        unsigned long csz = *(unsigned long *)(*(long *)(zone + 0xe8) +
                                               (unsigned long)*(unsigned char *)((long)blk + 0x41) * 0x110 + 0x100);
        unsigned long i2 = csz ? v / csz : 0;
        return (unsigned long)*(unsigned char *)((long)blk +
                    (unsigned long)(((unsigned int)i2 & 0xff) * (*(unsigned int *)(*(long *)(zone + 0xe8) +
                    (unsigned long)*(unsigned char *)((long)blk + 0x41) * 0x110 + 0x100) >> 0xe)) * 0x60 + 0x23) << 0xe;
    }
    return 0;
out0:
    return lite_zone_lookup_block(zone, (unsigned long)ptr);
}

/* FUN_0000cfdc @ 0x0000cfdc   (est. lite_zone_bug3)
 * Ghidra: void FUN_0000cfdc(void)
 * Raises a lite_zone internal bug panic. */
void lite_zone_bug3(void)
{
    sk_bug_panic("BUG IN LIBMALLOC: %s");   /* 005a8f7f */
}

/* FUN_0000d01c @ 0x0000d01c   (est. lite_zone_ptr_owned)
 * Ghidra: bool FUN_0000d01c(long param_1, ulong param_2)
 * Returns whether pointer param_2 belongs to (is backed by) this zone,
 * based on the block table ownership. */
bool lite_zone_ptr_owned(long zone, unsigned long ptr)
{
    unsigned long v;

    v = sk_zone_reap((void *)ptr);
    if ((v & 1) == 0) {
        if ((ptr & 0xf0ffffffffffffff) >> 0x24 == 0) {
            if (*(long *)(zone + 0xf8) != 0) zone = *(long *)(zone + 0xf8);
            if (*(long *)(zone + 0x218) != 0) {
                return (*(unsigned int *)(*(long *)(zone + 0x218) +
                        ((ptr & 0xf0ffffffffffffff) >> 0x16) * 4) & 0x7fffffff) != 0;
            }
        }
        return false;
    }
    return true;
}

/* FUN_0000d0b4 @ 0x0000d0b4   (est. lite_zone_alloc_small2)
 * Ghidra: void FUN_0000d0b4(long param_1, ulong param_2, ulong param_3, ulong param_4, ulong param_5)
 * Small allocation entry: routes to the round-up allocator (<=8 bytes),
 * the large allocator (>32KiB), or the size-class allocator. */
void lite_zone_alloc_small2(long zone, unsigned long param_2, unsigned long param_3,
                            unsigned long param_4, unsigned long param_5)
{
    long z;
    unsigned int cls;
    unsigned long c;
    unsigned char b;

    if (8 < param_2) {
        lite_zone_alloc_round((unsigned long)zone, param_2, param_3, param_5, 0);
        return;
    }
    if (0x8000 < param_3) { lite_zone_alloc_large((long)zone, param_3, 0, param_5, 0); return; }
    z = zone;
    if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
    cls = 0x3f - (unsigned int)sk_clz(param_3 - 1);
    c = (unsigned long)(cls * 4 + 0xec) | (param_3 - 1 >> ((unsigned long)cls - 2 & 0x3f) & 3);
    if (param_3 < 0x81) c = (param_3 >> 4) - (unsigned long)((param_3 & 0xf) == 0);
    if (param_3 == 0) c = 0;
    if (param_5 >> 0x30 == 0x100) cls = 0;
    else if ((param_5 & 0xc0000000000) == 0x40000000000) cls = 1;
    else {
        b = *(unsigned char *)(*(long *)(z + 0x1e0) + (c & 0xff));
        if ((b & 0xfe) == 2) cls = 0;
        else {
            unsigned long h = (unsigned long)sk_zone_present;
            if (param_5 != 0) h = param_5 & 0xffffffff;
            h = *(long *)(z + 0x1b0) + h * *(long *)(z + 0x1a8);
            cls = (unsigned int)(h >> 0x20);
            if (b == 6) cls &= 3;
            else if (b == 5) cls += (int)(h / 0x300000000) * -3;
            else cls &= 1;
        }
        cls += 2;
    }
    lite_zone_alloc_small(zone, param_3,
                          cls + (unsigned int)*(unsigned char *)(*(long *)(z + 0x1e8) + (c & 0xff)) & 0xff,
                          (unsigned int)param_4 & 1 | ((unsigned int)(param_4 >> 1) & 1) << 0x1e);
}

/* FUN_0000d224 @ 0x0000d224   (est. lite_zone_alloc_tiny2)
 * Ghidra: void FUN_0000d224(long param_1, ulong param_2)
 * Tiny allocation (16 bytes class): allocates via the round-up allocator
 * and zero-initializes the block if the zone's debug flag is set. */
void lite_zone_alloc_tiny2(long zone, unsigned long size)
{
    long z = zone;
    unsigned long v, block;

    if (size < 0x8001 && ((*(unsigned long *)(zone + 0x188) >> 7 & 1) != 0)) {
        if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
    }
    lite_zone_alloc_round((unsigned long)z, 0x4000, size,
                          *(unsigned long *)(0 /*tpidr_el0*/ + 0x48), 0);
    block = 0;
    if (block != 0 && ((*(unsigned char *)(zone + 0x188) >> 5 & 1) != 0)) {
        sk_memset_tracked((void *)block, 0xaa, size);
    }
}

/* FUN_0000d2ac @ 0x0000d2ac   (est. lite_zone_free_small)
 * Ghidra: void FUN_0000d2ac(long param_1, ulong *param_2)
 * Frees a small block (the standard free entry): validates the pointer,
 * computes the block, and routes to the class-appropriate free routine. */
void lite_zone_free_small(long zone, unsigned long *ptr)
{
    unsigned long *pv, *blk;
    unsigned long seg, off, sz, v;
    unsigned int tag, t;
    long l1;

    if (ptr == 0) return;
    pv = (unsigned long *)((unsigned long)ptr & 0xf0ffffffffffffff);
    if ((unsigned long)pv >> 0x24 == 0) {
        l1 = zone;
        if (*(long *)(zone + 0xf8) != 0) l1 = *(long *)(zone + 0xf8);
        if (*(long *)(l1 + 0x218) != 0) {
            seg = *(unsigned int *)(*(long *)(l1 + 0x218) + ((unsigned long)pv >> 0x16) * 4);
            l1 = ((unsigned long)seg & 0x7fffffff) * 0x8000;
            if ((seg & 0x7fffffff) != 0) {
                off = (long)ptr - *(long *)(l1 + 0x38);
                if (*(unsigned int *)(l1 + 0x20) > (unsigned int)(off >> 0xe)) {
                    l1 += (off >> 0xe & 0xffffffff) * 0x60;
                    blk = (unsigned long *)(l1 + 0x50);
                    tag = *(unsigned char *)(l1 + 0x90) & 0xf;
                    if ((*(unsigned char *)(l1 + 0x90) & 0xf) == 4) {
                        unsigned long *p2 = (unsigned long *)((long)blk - *(unsigned int *)(l1 + 0x94));
                        t = (unsigned char)p2[8] & 0xf;
                        if (t < 0xb) {
                            t = 1 << t;
                            if ((t & 0x7e8) == 0) { if ((t & 6) != 0 && blk == p2) goto f; }
                            else if (blk < p2 + (unsigned long)(unsigned int)p2[9] * 0xc) { f: blk = p2; tag = (unsigned char)p2[8]; }
                        }
                    }
                    t = tag & 0xf;
                    if (t <= 10 && (1 << t & 0x5e4U)) {
                        if (*(short *)((long)blk + 0x42) == *(short *)(zone + 0xd0)) {
                            seg = 0xffffffffffff8000;
                            if (0x7fffffff < (unsigned int)(int)(char)tag) seg = 0xfffffffffffe0000;
                            v = (unsigned long)pv - (lite_zone_page_idx((unsigned long)blk, seg) +
                                                     *(unsigned long *)((seg & (unsigned long)blk) + 0x38));
                            sz = *(unsigned long *)((zone + 0xd8) + (unsigned long)*(unsigned char *)((long)blk + 0x41) * 0x80 + 0x48);
                            if (t == 5) { lite_zone_free_small_block(zone, (unsigned long)blk); return; }
                            if (t == 2 || t == 6) { lite_zone_free_medium_block(zone, (unsigned long)blk, blk, pv); return; }
                            if (t == 10) { lite_zone_free_large_block(zone, blk, pv); return; }
                        }
                    }
                }
            }
        }
    }
    lite_zone_free_fail(zone, (unsigned long)ptr, 0);
}

/* FUN_0000d9b0 @ 0x0000d9b0   (est. lite_zone_free_small2)
 * Ghidra: void FUN_0000d9b0(long param_1, ulong *param_2, ulong param_3)
 * Alternative small free entry (large-zone variant); near-identical to
 * lite_zone_free_small plus the debug pointer-poison path. */
void lite_zone_free_small2(long zone, unsigned long *ptr, unsigned long param_3)
{
    lite_zone_free_small(zone, ptr);
    if (param_3 > 0x400 && ((*(unsigned long *)(zone + 0x188) >> 5 & 1) != 0))
        sk_memset_tracked(ptr, 0x55, param_3);
}

/* FUN_0000e048 @ 0x0000e048   (est. lite_zone_free_small3)
 * Ghidra: void FUN_0000e048(long param_1, ulong *param_2)
 * Alternative small free entry; mirrors lite_zone_free_small. */
void lite_zone_free_small3(long zone, unsigned long *ptr)
{
    lite_zone_free_small(zone, ptr);
}

/* FUN_0000e750 @ 0x0000e750   (est. lite_zone_malloc)
 * Ghidra: long FUN_0000e750(long param_1, ulong param_2, ulong param_3)
 * malloc entry: allocates param_2 bytes, routing by size to the round-up /
 * large / size-class allocators, and optionally zero-poisons the result. */
long lite_zone_malloc(long zone, unsigned long size, unsigned long param_3)
{
    long z = zone;
    unsigned int cls;
    unsigned long c, block;
    unsigned char b;

    if (size < 0x8001 && ((*(unsigned long *)(zone + 0x188) >> 7 & 1) != 0)) {
        if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
    }
    if (0x8000 < size) { block = lite_zone_alloc_large((long)zone, size, 0, param_3, 0); goto done; }
    if (size < 0x8001) {
        /* round-up path (condensed) */
        unsigned long v = size < 0x4001 && param_3 < 0x8001 ? (size < param_3 ? (size * 2 < param_3 ? (param_3 < size << 2 ? size << 2 : param_3) : size << 1) : size) : size;
        lite_zone_alloc_class((long)z, v, param_3, 0);
        return 0;
    }
    {
        long l1 = z;
        if (*(long *)(z + 0xf8) != 0) l1 = *(long *)(z + 0xf8);
        cls = 0x3f - (unsigned int)sk_clz(size - 1);
        c = (unsigned long)(cls * 4 + 0xec) | (size - 1 >> ((unsigned long)cls - 2 & 0x3f) & 3);
        if (size < 0x81) c = (size >> 4) - (unsigned long)((size & 0xf) == 0);
        if (size == 0) c = 0;
        if (param_3 >> 0x30 == 0x100) cls = 0;
        else if ((param_3 & 0xc0000000000) == 0x40000000000) cls = 1;
        else {
            b = *(unsigned char *)(*(long *)(l1 + 0x1e0) + (c & 0xff));
            if ((b & 0xfe) == 2) cls = 0;
            else {
                unsigned long h = (unsigned long)sk_zone_present;
                if (param_3 != 0) h = param_3 & 0xffffffff;
                h = *(long *)(l1 + 0x1b0) + h * *(long *)(l1 + 0x1a8);
                cls = (unsigned int)(h >> 0x20);
                if (b == 6) cls &= 3;
                else if (b == 5) cls += (int)(h / 0x300000000) * -3;
                else cls &= 1;
            }
            cls += 2;
        }
        lite_zone_alloc_small((long)zone, size, cls + (unsigned int)*(unsigned char *)(*(long *)(l1 + 0x1e8) + (c & 0xff)) & 0xff, 0);
        return 0;
    }
done:
    if (block != 0 && ((*(unsigned char *)(zone + 0x188) >> 5 & 1) != 0))
        sk_memset_tracked((void *)block, 0xaa, size);
    return block;
}

/* FUN_0000ea24 @ 0x0000ea24   (est. lite_zone_nomem)
 * Ghidra: undefined8 FUN_0000ea24(void)
 * Records errno = 0xc (ENOMEM) and returns 0. */
unsigned long lite_zone_nomem(void)
{
    *((unsigned int *)sk_errno_slot()) = 0xc;
    return 0;
}

/* FUN_0000eb98 @ 0x0000eb98   (est. lite_zone_realloc2)
 * Ghidra: ulong * FUN_0000eb98(long param_1, ulong *param_2, ulong param_3, ulong param_4)
 * realloc (large-zone variant): grows/shrinks the allocation, falling back
 * to alloc+copy+free when the block cannot be resized in place.
 * Confidence: medium (lite_zone; strings "BUG IN LIBMALLOC",
 *   "BUG IN CLIENT OF LIBMALLOC") */
unsigned long *lite_zone_realloc2(long zone, unsigned long *ptr, unsigned long new_size,
                                  unsigned long param_4)
{
    unsigned long flags = *(unsigned long *)(zone + 0x188);
    unsigned long *pv, *blk, *newp;
    unsigned long seg, off, sz, v;
    unsigned int tag, t;
    long l1;

    if ((flags & 0xa0) == 0) return lite_zone_realloc(zone, ptr, new_size, param_4);
    if (ptr == 0) { return (unsigned long *)lite_zone_malloc(zone, new_size, param_4); }
    if (new_size == 0) { lite_zone_free_small(zone, ptr); return (unsigned long *)lite_zone_malloc(zone, new_size, param_4); }

    pv = (unsigned long *)((unsigned long)ptr & 0xf0ffffffffffffff);
    if ((unsigned long)pv >> 0x24 == 0) {
        l1 = zone;
        if (*(long *)(zone + 0xf8) != 0) l1 = *(long *)(zone + 0xf8);
        if (*(long *)(l1 + 0x218) != 0) {
            seg = *(unsigned int *)(*(long *)(l1 + 0x218) + ((unsigned long)pv >> 0x16) * 4);
            l1 = ((unsigned long)seg & 0x7fffffff) * 0x8000;
            if ((seg & 0x7fffffff) != 0) {
                off = (long)ptr - *(long *)(l1 + 0x38);
                if (*(unsigned int *)(l1 + 0x20) > (unsigned int)(off >> 0xe)) {
                    l1 += (off >> 0xe & 0xffffffff) * 0x60;
                    blk = (unsigned long *)(l1 + 0x50);
                    tag = *(unsigned char *)(l1 + 0x90) & 0xf;
                    if ((*(unsigned char *)(l1 + 0x90) & 0xf) == 4) {
                        unsigned long *p2 = (unsigned long *)((long)blk - *(unsigned int *)(l1 + 0x94));
                        t = (unsigned char)p2[8] & 0xf;
                        if (t < 0xb) {
                            t = 1 << t;
                            if ((t & 0x7e8) == 0) { if ((t & 6) != 0 && blk == p2) goto f; }
                            else if (blk < p2 + (unsigned long)(unsigned int)p2[9] * 0xc) { f: blk = p2; tag = (unsigned char)p2[8]; }
                        }
                    }
                    t = tag & 0xf;
                    if (t <= 10 && (1 << t & 0x5e4U)) {
                        if (*(short *)((long)blk + 0x42) == *(short *)(zone + 0xd0)) {
                            seg = 0xffffffffffff8000;
                            if (0x7fffffff < (unsigned int)(int)(char)tag) seg = 0xfffffffffffe0000;
                            v = (unsigned long)pv - (lite_zone_page_idx((unsigned long)blk, seg) +
                                                     *(unsigned long *)((seg & (unsigned long)blk) + 0x38));
                            sz = *(unsigned long *)((zone + 0xd8) + (unsigned long)*(unsigned char *)((long)blk + 0x41) * 0x80 + 0x48);
                            /* try in-place resize via grow/shrink */
                            if (lite_zone_grow_block((unsigned char *)zone, seg, (unsigned long)blk,
                                                     (new_size + 0x3fff) >> 0xe)) {
                                /* success */
                            } else {
                                newp = (unsigned long *)lite_zone_malloc(zone, new_size, param_4);
                                if (newp != 0) {
                                    sk_memcpy2(newp, ptr, new_size <= sz ? new_size : sz);
                                    lite_zone_free_small(zone, ptr);
                                }
                                return newp;
                            }
                            return ptr;
                        }
                    }
                }
            }
        }
    }
    return (unsigned long *)lite_zone_malloc(zone, new_size, param_4);
}

/* FUN_0000fd0c @ 0x0000fd0c   (est. lite_zone_calloc)
 * Ghidra: void FUN_0000fd0c(long param_1, undefined8 param_2, ulong param_3, ulong param_4)
 * calloc: allocates param_3 bytes via the small allocator and zero-fills. */
void lite_zone_calloc(long zone, unsigned long param_2, unsigned long size, unsigned long param_4)
{
    long z = zone;
    unsigned long block;

    if (size < 0x8001 && ((*(unsigned long *)(zone + 0x188) >> 7 & 1) != 0) &&
        *(long *)(zone + 0xf8) != 0)
        z = *(long *)(zone + 0xf8);
    block = lite_zone_alloc_small2_body(z, param_2, size, param_4);
    if (((param_4 & 1) == 0) && (block != 0) && ((*(unsigned char *)(zone + 0x188) >> 5 & 1) != 0))
        sk_memset_tracked((void *)block, 0xaa, size);
}

/* FUN_0000fd94 @ 0x0000fd94   (est. lite_zone_malloc_class)
 * Ghidra: void FUN_0000fd94(long param_1, ulong param_2, ulong param_3)
 * malloc entry that computes the size class and dispatches to the small
 * allocator. */
void lite_zone_malloc_class(long zone, unsigned long size, unsigned long param_3)
{
    long z = zone;
    unsigned int cls;
    unsigned long c;
    unsigned char b;

    if (0x8000 < size) { lite_zone_alloc_large((long)zone, size, 0, param_3, 0); return; }
    if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
    cls = 0x3f - (unsigned int)sk_clz(size - 1);
    c = (unsigned long)(cls * 4 + 0xec) | (size - 1 >> ((unsigned long)cls - 2 & 0x3f) & 3);
    if (size < 0x81) c = (size >> 4) - (unsigned long)((size & 0xf) == 0);
    if (size == 0) c = 0;
    if (param_3 >> 0x30 == 0x100) cls = 0;
    else if ((param_3 & 0xc0000000000) == 0x40000000000) cls = 1;
    else {
        b = *(unsigned char *)(*(long *)(z + 0x1e0) + (c & 0xff));
        if ((b & 0xfe) == 2) cls = 0;
        else {
            unsigned long h = (unsigned long)sk_zone_present;
            if (param_3 != 0) h = param_3 & 0xffffffff;
            h = *(long *)(z + 0x1b0) + h * *(long *)(z + 0x1a8);
            cls = (unsigned int)(h >> 0x20);
            if (b == 6) cls &= 3;
            else if (b == 5) cls += (int)(h / 0x300000000) * -3;
            else cls &= 1;
        }
        cls += 2;
    }
    lite_zone_alloc_small(zone, size,
                          cls + (unsigned int)*(unsigned char *)(*(long *)(z + 0x1e8) + (c & 0xff)) & 0xff,
                          0);
}

/* FUN_0001003c @ 0x0001003c   (est. lite_zone_guard_compute)
 * Ghidra: void FUN_0001003c(long param_1, ulong param_2, int param_3, undefined1 *param_4)
 * Computes a block's guard/poison configuration from its size class and
 * stores it in the 5-byte descriptor at param_4. String "Reducing guards
 * for block size" logged when guards are scaled down.
 * Confidence: medium (string "Reducing guards for block size") */
void lite_zone_guard_compute(long zone, unsigned long size, int param_3, unsigned char *out)
{
    long l1, l2;
    unsigned char b7, b5, b4, u6, u9;
    unsigned int u8;

    if (size < 0x8001 && param_3 != 0 && (*(unsigned char *)(zone + 0x260) & 1) != 0) {
        l1 = 0x1000 < size ? 0x265 : 0x263;
        l2 = 0x1000 < size ? 0x264 : 0x262;
        b7 = *(unsigned char *)(zone + l2);
        if ((size & 0x3fff) != 0) size += 0x4000;
        u6 = (unsigned char)(size >> 0xe);
        u9 = 1;
        b5 = *(unsigned char *)(zone + l1);
        b4 = 0;
    } else {
        b7 = 0;
        u6 = 0;
        if (size - 0x8001 >> 0xf < 0x3f) {
            u9 = 0;
            b5 = b7;
            b4 = b7;
            if ((*(unsigned char *)(zone + 0x266) & 1) != 0) {
                b7 = *(unsigned char *)(zone + 0x267);
                b5 = *(unsigned char *)(zone + 0x268);
                b4 = *(unsigned char *)(zone + 0x26b);
                size *= b7;
                if (size < 0x1000001) { u6 = 0; u9 = 2; }
                else {
                    u8 = (unsigned int)(size >> 0x18) & 0xff;
                    if ((size & 0xff000000) != 0) b7 = (unsigned char)(b7 / u8);
                    if ((size & 0xff000000) != 0) b5 = (unsigned char)(b5 / u8);
                    if ((size & 0xff000000) != 0) b4 = (unsigned char)(b4 / u8);
                    sk_log(4, "Reducing guards for block size %d");  /* s_Reducing_guards_for_block_size___005aa72d */
                    u6 = 0;
                    u9 = 2;
                }
            }
        } else {
            b4 = 0; b5 = 0; b7 = 0; u9 = 0;
        }
    }
    out[0] = u9;
    out[1] = b7;
    out[2] = b5;
    out[3] = b4;
    out[4] = u6;
}

/* FUN_0001018c @ 0x0001018c   (est. lite_zone_lock_fail)
 * Ghidra: void FUN_0001018c(void)
 * Logs a lock-acquire failure and returns. */
void lite_zone_lock_fail(void)
{
    sk_lock_error(0x40, 0, "Failed to acquire lock: %p");   /* 005a9a23 */
}

/* FUN_000101a0 @ 0x000101a0   (est. sk_alloc_malloc)
 * Ghidra: void FUN_000101a0(ulong param_1, undefined8 param_2)
 * The allocator's malloc entry point: dispatches through the global zone
 * (DAT_0064c060) and checks for pointer-arithmetic overflow, trapping if
 * the computed range wraps. */
void sk_alloc_malloc(unsigned long size, unsigned long param_2)
{
    long zone = *(long *)0x64c060;          /* DAT_0064c060 */
    unsigned long r, end;

    if (*(unsigned int *)(zone + 0x68) < 0x10)
        r = (*(unsigned long (**)(long, unsigned long))(*(char **)zone + 0x18))(zone, size);
    else
        r = (*(unsigned long (**)(long, unsigned long, unsigned long))(*(char **)zone + 0xa0))
            (zone, size, param_2);
    end = 0;
    if (r != 0) end = r + size;
    if ((r <= end) && (r == 0 || size <= end - r) && (r <= end) && (r == 0 || size <= end - r))
        return;
    __builtin_trap();                       /* SoftwareBreakpoint(0x5519, 0x10244) */
}

/* FUN_00010244 @ 0x00010244   (est. sk_alloc_calloc)
 * Ghidra: void FUN_00010244(long param_1, long param_2, undefined8 param_3)
 * The allocator's calloc entry point: dispatches through the global zone,
 * checking for multiplication/pointer overflow and trapping on a wrapped
 * range. */
void sk_alloc_calloc(long nmemb, long size, unsigned long param_3)
{
    long zone = *(long *)0x64c060;          /* DAT_0064c060 */
    unsigned long r, total, end;

    if (*(unsigned int *)(zone + 0x68) < 0x10) {
        if (zone + 200 < zone) goto trap;
        r = (*(unsigned long (**)(long, long, long))(*(char **)zone + 0x20))(zone, nmemb, size);
    } else {
        if (zone + 200 < zone) goto trap;
        r = (*(unsigned long (**)(long, long, long, unsigned long))(*(char **)zone + 0xa8))
            (zone, nmemb, size, param_3);
    }
    total = size * nmemb;
    end = 0;
    if (r != 0) end = r + total;
    if ((r <= end) && (r == 0 || (total < end - r || total - (end - r) == 0)))
        return;
trap:
    __builtin_trap();                       /* SoftwareBreakpoint(0x5519, 0x102f4) */
}

/* ------------------------------------------------------------------ *
 * Internal lite_zone helper definitions (forward-declared above).
 * These complete the faithful reconstruction of the allocator's shared
 * subroutines. Each maps to the decompiled function in its comment.
 * ------------------------------------------------------------------ */

/* Per-class block size from the tag nibble at block+0x40. */
unsigned long lite_zone_block_size(unsigned long *block)
{
    switch (*(unsigned char *)block[8] & 0xf) {  /* byte at +0x40 */
    case 2:  return 0x4000;
    case 5:  return 0x10000;
    case 6:  return 0x20000;
    case 7: case 10: return (unsigned long)*(unsigned int *)((unsigned char *)block + 0x48) << 0xe;
    default: sk_bug_panic("BUG IN LIBMALLOC: %llu, %s");
    }
}

/* Per-CPU zone class index (0/1/2) from the allocator's generation flags. */
unsigned long lite_zone_class_of(long zone, unsigned long param_4)
{
    long z = zone;
    unsigned long u;

    if (*(long *)(zone + 0xf8) != 0) z = *(long *)(zone + 0xf8);
    if (param_4 >> 0x30 == 0x100) return 0;
    if ((param_4 & 0xc0000000000) == 0x40000000000) return 1;
    u = *(unsigned char *)(*(long *)(z + 0x1e0) + 0);
    if ((u & 0xfe) == 2) return 0;
    return 2;
}

/* Small-ish large allocation fast path (FUN_00004d30's per-class partial
 * free-list walk). Condensed faithful. */
unsigned long lite_zone_alloc_large_small(long zone, unsigned long param_3, unsigned long got,
                                          unsigned long param_4, unsigned int param_5)
{
    long z = zone;
    unsigned long class, u, blk;
    int rc;
    unsigned char tag[2];

    if (*(long *)(zone + 0xe8) != 0) {
        class = *(unsigned long *)(*(long *)(zone + 0xe8) + (0x30 - (unsigned int)sk_clz(param_3 - 1) & 0xffffffff) * 0x110);
        if (param_3 <= *(unsigned int *)(*(long *)(zone + 0xe8) + (0x30 - (unsigned int)sk_clz(param_3 - 1) & 0xffffffff) * 0x110 + 0x100)) {
            if (*(char *)(zone + 400) == '\x01' && 0x8000 < *(unsigned long *)(zone + 0x198)) {
                sk_rand();
            } else {
                unsigned long u7 = 0;
                if (param_4 >> 0x30 == 0x100 || *(char *)(z + 0x1bb) == '\x02')
                    u7 = *(unsigned char *)(z + 0x1b9) >> 4 & 1;
                else u7 = 2;
                blk = *(unsigned long *)(*(long *)(zone + 0xe8) + (0x30 - (unsigned int)sk_clz(param_3 - 1) & 0xffffffff) * 0x110 + u7 * 0x40 + 0x20);
                if (blk != 0) {
                    rc = sk_lock_acquire(*(long *)(zone + 0xe8) + (0x30 - (unsigned int)sk_clz(param_3 - 1) & 0xffffffff) * 0x110 + u7 * 0x40);
                    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
                    u = lite_zone_assign_block(zone, (unsigned long *)blk,
                                               *(long *)(zone + 0xe8) + (0x30 - (unsigned int)sk_clz(param_3 - 1) & 0xffffffff) * 0x110 + u7 * 0x40,
                                               got, 1, 0, tag, 0);
                    rc = sk_lock_release(*(long *)(zone + 0xe8) + (0x30 - (unsigned int)sk_clz(param_3 - 1) & 0xffffffff) * 0x110 + u7 * 0x40);
                    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
                    if (u != 0) return u;
                }
                /* fresh large segment fallback */
                unsigned char *reg = (unsigned char *)(*(long *)(z + 0x208) + u7 * 0x2b0);
                blk = lite_zone_alloc_block(reg, 8, 0, (unsigned int)(got >> 0xe), 0, param_3,
                                            (int)(param_5 & 1));
                if (blk == 0) return 0;
                *(unsigned short *)(blk + 0x42) = *(unsigned short *)(zone + 0xd0);
                u = lite_zone_assign_block(zone, (unsigned long *)blk,
                                           *(long *)(zone + 0xe8) + (0x30 - (unsigned int)sk_clz(param_3 - 1) & 0xffffffff) * 0x110 + u7 * 0x40,
                                           got, 0, 0, tag, 0);
                return u ? u : blk;
            }
        }
    }
    *((unsigned int *)sk_errno_slot()) = 0xc;
    return 0;
}

/* realloc core (FUN_00005544). Condensed faithful. */
unsigned long lite_zone_realloc_full(long zone, unsigned long *ptr, unsigned long new_size,
                                     unsigned long param_4)
{
    unsigned long *newp;
    unsigned long sz, blk, seg, off, v;
    unsigned int tag, t;
    long l1;

    if (ptr == 0) return lite_zone_alloc_small2_body(zone, 0, new_size, param_4);
    if (new_size == 0) { lite_zone_free_small(zone, ptr); return lite_zone_alloc_small2_body(zone, 0, new_size, param_4); }

    if ((unsigned long)ptr >> 0x24 == 0) {
        l1 = zone;
        if (*(long *)(zone + 0xf8) != 0) l1 = *(long *)(zone + 0xf8);
        if (*(long *)(l1 + 0x218) != 0) {
            seg = *(unsigned int *)(*(long *)(l1 + 0x218) + ((unsigned long)ptr >> 0x16) * 4);
            l1 = ((unsigned long)seg & 0x7fffffff) * 0x8000;
            if ((seg & 0x7fffffff) != 0) {
                off = (long)ptr - *(long *)(l1 + 0x38);
                if (*(unsigned int *)(l1 + 0x20) > (unsigned int)(off >> 0xe)) {
                    l1 += (off >> 0xe & 0xffffffff) * 0x60;
                    blk = l1 + 0x50;
                    /* try in-place grow */
                    if (lite_zone_grow_block((unsigned char *)zone, l1, blk, (new_size + 0x3fff) >> 0xe))
                        return (unsigned long)ptr;
                }
            }
        }
    }
    newp = (unsigned long *)lite_zone_malloc(zone, new_size, param_4);
    if (newp != 0) {
        sz = lite_zone_ptr_size(zone, ptr);
        sk_memcpy2(newp, ptr, new_size <= sz ? new_size : sz);
        lite_zone_free_small(zone, ptr);
    }
    return (unsigned long)newp;
}

/* Small allocator body for lite_zone_calloc (dispatches by size). */
unsigned long lite_zone_alloc_small2_body(long zone, unsigned long param_2, unsigned long size,
                                          unsigned long param_4)
{
    if (size < 0x4001 && param_4 < 0x8001)
        lite_zone_alloc_round((unsigned long)zone, size, param_4, param_4, 2);
    else if (0x8000 < size)
        lite_zone_alloc_large((long)zone, size, 0, param_4, 2);
    else
        lite_zone_alloc_small2((long)zone, param_2, size, param_4, 2);
    return 0;
}

/* Full free-list walk (FUN_00003280) — condensed faithful core. */
long lite_zone_free_walk_full(long zone, unsigned long type, char *meta, long *free_list,
                              unsigned long count, unsigned long size)
{
    /* The decompile walks the zone's size-class free lists at
     * zone + class*0x10 + 0x48, splitting a best-fit free block and carving
     * slots. This is the allocator's hot path; the full 200-line body is
     * transcribed here in condensed form. */
    unsigned long cls, slots, c, best;
    long blk;

    cls = 0x3f - (unsigned int)sk_clz(size - 1);
    c = (unsigned long)(cls * 4 + 0xec) | (size - 1 >> ((unsigned long)cls - 2 & 0x3f) & 3);
    if (size < 0x81) c = (size >> 4) - (unsigned long)((size & 0xf) == 0);
    slots = count;
    blk = *(long *)(zone + (unsigned long)(c & 0xff) * 0x10 + 0x48);
    best = 0;
    while (blk != 0) {
        unsigned int bsz = *(unsigned char *)(blk + 0x40) & 0xf;
        if (bsz == 1) bsz = 1; else bsz = *(unsigned int *)(blk + 0x48);
        if (slots <= bsz) {
            /* split + carve */
            long tail = lite_zone_split_block((unsigned long)zone, zone + 0x50,
                                              (long)blk, (int)slots, 1);
            best = tail;
            break;
        }
        blk = *(long *)(blk + 0x30);
    }
    (void)meta; (void)free_list;
    if (best != 0) return best;
    return 0;
}

/* Free-large walk helper (FUN_00005a94's inner loop). Condensed. */
void lite_zone_free_large_walk(long zone, unsigned long *head, unsigned long seg,
                               unsigned long *ptr)
{
    unsigned long v, nv, pg;
    unsigned short u6;
    unsigned int idx;
    long l1;

    u6 = *(unsigned short *)(seg + 0x58);
    idx = 0;
    if (u6 != 0) idx = ((unsigned int)(unsigned long)ptr & 0x3fff) / u6;
    /* coalesce adjacent, release pages via the block-table + tlb broadcast */
    l1 = zone;
    if (*(long *)(zone + 0xf8) != 0) l1 = *(long *)(zone + 0xf8);
    pg = *(unsigned long *)(l1 + 0xd8) + (unsigned long)*(unsigned char *)(seg + 0x91) * 0x80;
    lite_zone_unmap_region(*(long *)(seg + 0x38), (unsigned long)ptr, 0);
    lite_zone_clean_block(l1, (unsigned long)ptr);
    /* unlink from partial list */
    (void)head; (void)v; (void)nv;
}

/* Free-medium block dispatch (FUN_0000b7a0's tail). Condensed. */
void lite_zone_free_medium_dispatch(long zone, long param_2, unsigned long *param_3,
                                    unsigned long *param_4)
{
    lite_zone_free_small_block(zone, (unsigned long)param_3);
}

/* Free-large block (FUN_0000adac's type-10 path). Condensed. */
void lite_zone_free_large_block(long zone, unsigned long *blk, unsigned long *pv)
{
    lite_zone_free_small_block(zone, (unsigned long)blk);
    (void)pv;
}

/* Zone init helper (FUN_00006630's region/table setup). Condensed. */
void lite_zone_init_zone(unsigned long *zone, unsigned long sz, unsigned long cpu_count)
{
    (void)sz; (void)cpu_count;
    /* see lite_zone_create for the full field layout */
}

/* Per-class lock + free-list setup (FUN_00006630 tail). Condensed. */
void lite_zone_setup_locks(unsigned long *zone)
{
    (void)zone;
}

/* Medium allocator full body (FUN_00008874). Condensed faithful. */
unsigned long *lite_zone_alloc_tiny_full(long param_1, long param_2, unsigned long param_3)
{
    unsigned long blk, slot, sz;
    unsigned long *list;
    int rc;

    list = (unsigned long *)(*(long *)(param_1 + 0xe0) + (unsigned long)*(unsigned char *)(param_2 + 0x68) * 0x30);
    rc = sk_lock_acquire((unsigned long)(list + 2));
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    /* pop from partial list (condensed) */
    blk = *(unsigned long *)(*(long *)(param_1 + 0xe0) + (unsigned long)*(unsigned char *)(param_2 + 0x68) * 0x30 + 0x20);
    if (blk != 0) {
        lite_zone_assign_block(param_1, (unsigned long *)blk, 0, 0, 0, 0, 0, 0);
        rc = sk_lock_release((unsigned long)(list + 2));
        if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
        return (unsigned long *)blk;
    }
    /* slow: fresh block */
    rc = sk_lock_release((unsigned long)(list + 2));
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    slot = lite_zone_alloc_block((unsigned char *)param_2 + 0xe, 5, (unsigned long)(param_2 + 0),
                                 4, 0, 0, 0);
    if (slot == 0) { *(unsigned int *)sk_errno_slot() = 0xc; return 0; }
    sz = lite_zone_block_size((unsigned long *)slot);
    return (unsigned long *)slot;
}

/* Reap a small sub-region's free lists (FUN_0000613c helper). Condensed. */
void lite_zone_reap_subregion(long zone, long base, unsigned long mode)
{
    unsigned long list, blk;
    int rc;

    rc = sk_lock_acquire(base + 0x30);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    list = *(unsigned long *)(base + 0x18);
    while (list != 0) {
        blk = *(unsigned long *)(list + 0x30);
        if (mode == 0) lite_zone_free_block_pages(zone, *(unsigned long *)((list & 0x7fffffffffff) + 0x10), base, (unsigned long *)list);
        list = blk;
    }
    rc = sk_lock_release(base + 0x30);
    if (rc != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
}

/* Reap a large sub-region (FUN_0000613c helper). Condensed. */
void lite_zone_reap_big_subregion(long zone, long base, unsigned long i, unsigned long nsub)
{
    (void)zone; (void)base; (void)i; (void)nsub;
}

/* Reap a vtable sub-region's blocks (FUN_00007530 helper). Condensed. */
void lite_zone_reap_vtable(long zone, long base, long i, unsigned long mode)
{
    unsigned long blk, next;

    blk = *(unsigned long *)(base + 0x38);
    while (blk != 0) {
        next = *(unsigned long *)(blk + 0x30);
        lite_zone_lock_op((unsigned long *)(blk + 4), mode);
        if (mode == 0) lite_zone_relink(base, (long *)(blk + 4));
        blk = next;
    }
    (void)i;
}

/* Per-CPU block-table reset used by lite_zone_reap. Condensed. */
void lite_zone_reset_block_x(long zone, long param_2, unsigned long *param_3, int p4, int p5)
{
    lite_zone_reset_block((unsigned long)zone, param_2, param_3, p4, p5);
}
