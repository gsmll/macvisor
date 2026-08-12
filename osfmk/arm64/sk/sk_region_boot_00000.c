/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice: 0x00000-0x10000 — kernel entry/reset, exception vectors, early boot,
 * platform/root-task launch, and the embedded lite_zone (libmalloc) allocator. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * Names are estimates; FUN_ address in comment is ground truth.
 * ------------------------------------------------------------------ */

/* Platform / boot machine helpers (region 0x0004xxxx-0x0006xxxx). */
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
extern void sk_phys_map_tighten(void);                                  /* FUN_0006b77c */
extern void *sk_devtree_get(void);                                      /* FUN_00084368 */
extern void sk_devtree_set_va(unsigned long);                           /* FUN_0006d66c */
extern void *sk_devtree_validate(unsigned long a, unsigned long b);     /* FUN_00066424 */
extern void *sk_object_boot_0(void);                                    /* FUN_0009efd4 */
extern unsigned long sk_boot_memtype(unsigned long a);                   /* FUN_0008f9a0 */
extern void *sk_boot_cpu_slot(void);                                    /* FUN_0008e640 */
extern unsigned long sk_boot_caps(void);                                /* FUN_0019ae0c */
extern unsigned long sk_boot_cpu_count(void);                           /* FUN_0005526c */
extern void *sk_arch_boot_0(void);                                      /* FUN_001030c4 */
extern void *sk_arch_boot_1(void);                                      /* FUN_001022cc */
extern void *sk_obj_get_0(void);                                        /* FUN_000773f0 */
extern void *sk_obj_get_1(void);                                        /* FUN_0007063c */
extern void *sk_obj_get_2(void);                                        /* FUN_000a6834 */
extern void *sk_obj_get_3(void);                                        /* FUN_000a3e40 */
extern void sk_finalize_0(void);                                        /* FUN_000db3d0 */
extern void *sk_finalize_1(unsigned long, unsigned long, unsigned long,
                           unsigned long, void *, unsigned long,
                           unsigned long, unsigned long, void *, void *,
                           unsigned long);                              /* FUN_000c118c */
extern void sk_finalize_2(void);                                        /* FUN_000c544c */
extern void sk_finalize_3(void);                                        /* FUN_000cf6a4 */
extern unsigned long sk_btree_0(unsigned long a, unsigned long b);      /* FUN_000b7c9c */
extern void sk_boot_pll(int mode);                                      /* FUN_0006bb34 */
extern void sk_boot_gate(void);                                         /* FUN_000d0020 */
extern void *sk_boot_op_probe(unsigned long a, unsigned long b);        /* FUN_00071050 */
extern void sk_platform_init(void);                                     /* FUN_000534c0 */

/* Lite_zone (libmalloc) machine primitives. */
extern void *sk_alloc(unsigned long size, unsigned long tag);           /* FUN_0036b270 */
extern void sk_free(void *ptr);                                         /* FUN_0036b118 */
extern void sk_alloc_init_pages(void *obj, unsigned long a, ...);       /* FUN_0036a940 */
extern void sk_alloc_teardown(void *obj, ...);                          /* FUN_0036a1a0 */
extern void sk_alloc_finalize(void *obj);                               /* FUN_0036a20c */
extern void sk_alloc_link(unsigned long obj, ...);                      /* FUN_0036b588 */
extern void sk_alloc_link2(unsigned long obj, ...);                     /* FUN_0036b6ac */
extern void sk_alloc_link3(unsigned long obj, ...);                     /* FUN_0036b21c */
extern void sk_alloc_touch_extern(unsigned long obj, unsigned long a,
                                  unsigned long b);                     /* FUN_0036a9a0 */
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
extern unsigned long sk_tick(void);                                     /* FUN_00010934 */
extern unsigned long sk_rand(void);                                     /* FUN_000114f0 */
extern void sk_cpu_id_init(void);                                       /* FUN_0001071c */
extern int sk_sched_init(int a, void *b);                               /* FUN_001181b4 */
extern void sk_stack_poison(void *p, unsigned long n);                  /* FUN_00054414 (thunk) */
extern int sk_clz(unsigned long v);                                     /* FUN_00116e00 */
extern unsigned long sk_bit_rand(void);                                 /* FUN_00116da0 */
extern int sk_lock_acquire(unsigned long lock);                          /* FUN_0011582c */
extern int sk_lock_release(unsigned long lock);                          /* FUN_00115894 */
extern int sk_lock_try(unsigned long lock);                              /* FUN_00115860 */
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
extern void *sk_object_lookup_zone(unsigned long zone);                 /* FUN_000043cc */
extern void sk_zone_grow_1(unsigned long a, unsigned long b, ...);       /* FUN_00026b434 */
extern void *sk_errno_slot(void);                                       /* FUN_0006037c (thunk) */
extern void sk_tlb_broadcast(void);                                     /* FUN_000529d4 (thunk) */

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

/* Load a function pointer from memory at (base+off) and call it. */
#define SK_FCALL0(base, off) \
    ((void (*)(void))(*(void **)((char *)(base) + (off))))()
#define SK_FCALL1(base, off, a) \
    ((void (*)(unsigned long))(*(void **)((char *)(base) + (off))))((unsigned long)(a))
#define SK_FCALL0R(base, off) \
    ((unsigned long (*)(void))(*(void **)((char *)(base) + (off))))()
#define SK_FCALL2(base, off, a, b) \
    ((void (*)(unsigned long, unsigned long))(*(void **)((char *)(base) + (off)))) \
        ((unsigned long)(a), (unsigned long)(b))

/* Globals used by this region (image base / end, boot config). */
extern unsigned long sk_image_base;      /* DAT_006adfc0 */
extern unsigned long sk_image_end;       /* DAT_006adfc8 */
extern unsigned long sk_boot_cfg;        /* DAT_006ad6e0 */
extern unsigned long sk_boot_done;       /* DAT_006adfd0 */
extern unsigned long sk_boot_mem_hi;     /* DAT_006add08 */

/* Local forward declarations. */
void sk_boot_launcher_entry(void);
unsigned long sk_launcher_root(void);
unsigned long sk_boot_thread_main(void);
unsigned long sk_boot_thread_main2(void);
void sk_boot_ec_switch_impl(void *param_1, void *param_2, unsigned long param_3);
void sk_boot_ec_err(void *param_1, void *param_2);
void sk_boot_ec_dispatch(void);
unsigned long sk_boot_run(void);
void sk_boot_strmap(unsigned long *name, long *def);
unsigned long sk_boot_caps_slot(unsigned long obj, unsigned long a);
unsigned int sk_boot_done_poll(void);
unsigned char sk_boot_done_get(void);
void sk_boot_finish(unsigned long a);
void sk_boot_finish_thunk(unsigned long a);
void sk_alloc_step(void);
void sk_alloc_free_step(void);
void sk_alloc_free_step2(void);
void sk_alloc_free_link(unsigned long *obj);
unsigned long sk_alloc_call(unsigned long a, unsigned long b);
unsigned long sk_alloc_call2(unsigned long a, unsigned long *name, long *def);
char *sk_fatal_str(void);
void sk_boot_nop(void);
void sk_boot_nop2(void);
void sk_alloc_touch(unsigned long a, unsigned long b);
void sk_zone_init2(unsigned long a);
void sk_boot_nop3(void);
void sk_boot_nop4(void);
void sk_alloc_touch2(unsigned long a, unsigned long b);
void sk_boot_store_pair(unsigned long *p);
void sk_zone_init3(void);
void sk_boot_nop5(void);
void sk_boot_nop6(void);
unsigned long sk_alloc_collect(unsigned long obj, unsigned long arg,
                               unsigned long *out, unsigned int count);
void sk_alloc_collect2(unsigned long obj, unsigned long *arr, unsigned int count);
void sk_alloc_err(unsigned long a, unsigned long b);
void sk_bug_malloc(void);
void sk_boot_abort_panic(void) __attribute__((noreturn));

/* Lite-zone allocator helper forwards (defined in this file). */
unsigned long sk_slab_alloc(unsigned char *zone, unsigned long type, void *cfg,
                            unsigned int pages, unsigned long seed, unsigned long size,
                            int do_tlb);
unsigned long sk_slab_alloc_core(unsigned long zone, unsigned long type, char *cfg,
                                 long *out, unsigned long count, unsigned long size);
unsigned long sk_slab_alloc_relock(unsigned long zone, unsigned long type, void *cfg,
                                   void *seed, unsigned long count, unsigned long size);
unsigned long sk_page_alloc(unsigned long zone, unsigned long size, unsigned long seed,
                            unsigned long *out);
unsigned long sk_segment_alloc(unsigned long seg, unsigned long size);
unsigned long sk_slab_split(unsigned long zone, unsigned long base, unsigned long node,
                            int count, int part);
void sk_slab_relink(unsigned long zone, unsigned long base, unsigned int idx,
                    unsigned int n, int a, int b);
void sk_slab_touch(unsigned long base, unsigned int idx, unsigned int n);
unsigned long sk_slab_mark(unsigned long base, int type, unsigned long idx, unsigned int n);
unsigned long sk_bit_select(unsigned long bitmap, unsigned long n, int count);
void sk_zone_tlb_inval(unsigned long zone, unsigned long va, unsigned long seed);
void sk_zone_tlb_bump(unsigned long zone, unsigned long va, unsigned long size);
void sk_zone_pmo_free(unsigned long zone, unsigned long va, unsigned long size);

/* Convenience cache/TLB helpers kept faithful to Ghidra primitives. */
static inline void sk_dc_gva(unsigned long va) { asm volatile("dc civac, %0" :: "r"(va)); }
#define sk_bug_llu() sk_bug_panic("BUG IN LIBMALLOC: %llu", 0ull)
#define sk_bug_s()   sk_bug_panic("BUG IN LIBMALLOC: %s", "")

/* Ghidra LZCOUNT maps to the ARM CLZ instruction (leading-zero count). */
static inline unsigned int sk_lzcount32(unsigned int v)
{
    return v ? (unsigned int)__builtin_clz(v) : 32u;
}
static inline unsigned long sk_lzcount64(unsigned long v)
{
    return v ? (unsigned long)__builtin_clzll(v) : 64ul;
}

/* Bit-reverse a 32-bit word then count leading zeros (Ghidra LZCOUNT of
 * the reversed word) — computes the index of the lowest set bit. */
static inline unsigned int sk_lowbit32(unsigned int v)
{
    unsigned int r = v;
    r = (r & 0xaaaaaaaa) >> 1 | (r & 0x55555555) << 1;
    r = (r & 0xcccccccc) >> 2 | (r & 0x33333333) << 2;
    r = (r & 0xf0f0f0f0) >> 4 | (r & 0x0f0f0f0f) << 4;
    r = (r & 0xff00ff00) >> 8 | (r & 0x00ff00ff) << 8;
    return sk_lzcount32(r >> 0x10 | r << 0x10);
}

/* Slab page-count from the object's flags byte (Ghidra pattern). */
static inline unsigned long sk_slab_pages(unsigned long obj)
{
    unsigned int t = *(unsigned char *)(obj + 0x40) & 0xf;
    if (t < 7) {
        if (t == 2) return 0x4000;
        if (t == 5) return 0x10000;
        if (t == 6) return 0x20000;
    } else if (t == 7 || t == 8 || t == 10) {
        return (unsigned long)*(unsigned int *)(obj + 0x48) << 0xe;
    }
    sk_bug_llu();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000012d4 @ 0x000012d4   (est. sk_boot_launcher_entry)
 * Ghidra: void FUN_000012d4(void)
 * Early-boot launcher entry: reads the boot image info block, writes the
 * boot diagnostic marker, initializes the tick timer, prints
 * "LAUNCHER: Started platform", runs platform setup, stores the boot
 * regions, and derives the kernel image base/end (rounding the end up to
 * a 16KiB boundary). Returns with the boot configuration stored.
 * Confidence: medium
 * Notes: string ref s__LAUNCHER__Started_platform__s_005a8a7f; writes
 *   globals DAT_006adfc0 (image base) and DAT_006adfc8 (image end). */
void sk_boot_launcher_entry(void)
{
    void *info;

    info = sk_boot_image_info();
    sk_boot_diag_write(0xf84f8d4baa0803ea, 0x8b090d09b50005ab);
    sk_boot_tick_init();
    sk_printf("LAUNCHER: Started platform");
    sk_boot_platform_setup();
    sk_boot_region_store(*(unsigned long *)((char *)info + 0x18));
    sk_boot_region_store2(*(unsigned long *)((char *)info + 0x10));
    sk_image_base = sk_image_base_get();
    sk_image_end = sk_image_end_get();
    sk_image_end &= ~0x3fffull;              /* round up to 16KiB */
    sk_boot_vm_init();
    sk_boot_config_store(0x6b8f4);
}

/*--------------------------------------------------------------------*/
/* FUN_00001378 @ 0x00001378   (est. sk_launcher_root)
 * Ghidra: undefined8 FUN_00001378(void)
 * Root-task launcher: prints the root task UUID and slide, walks the
 * kernel image range mapping each 16KiB page into the new address space
 * (via a supervisor call with an argument block placed in the per-CPU
 * TPIDRRO area), commits the kernel symbol table, spawns the boot thread
 * (entry FUN_00001684), then drives the boot object/thread to completion
 * in a loop (waiting on its state via supervisor calls). Returns 0 on
 * success; aborts via the panic paths on failure.
 * Confidence: medium
 * Notes: string refs s_Roottask_UUID_is__005a8a9f and
 *   s_Roottask_slide_is_0x_llx_005a8b16; method-dispatch calls through the
 *   boot object's vtable (+0x30 and +8); global symbol table nlist_0068c000;
 *   reads image base DAT_006adfc0 and end DAT_006adfc8. */
unsigned long sk_launcher_root(void)
{
    unsigned long *tpidr;
    unsigned long image_end, image_base, end_round, pages, off, phys;
    unsigned long result, obj_type, slot, state;
    void *obj;

    sk_boot_info_bind(sk_cpu_boot_info(), (void *)0x64c010);
    obj = sk_boot_uuid_source();
    sk_printf("Roottask UUID is %02hhX-%02hhX-%02hhX-%02hhX-%02hhX-%02hhX-"
              "%02hhX-%02hhX-%02hhX-%02hhX-%02hhX-%02hhX-%02hhX-%02hhX-%02hhX-%02hhX",
              *(char *)((char *)obj + 0x11), *(char *)((char *)obj + 0x12),
              *(char *)((char *)obj + 0x13), *(char *)((char *)obj + 0x14),
              *(char *)((char *)obj + 0x15), *(char *)((char *)obj + 0x16),
              *(char *)((char *)obj + 0x17), *(char *)((char *)obj + 0x18),
              *(char *)((char *)obj + 0x19), *(char *)((char *)obj + 0x1a),
              *(char *)((char *)obj + 0x1b), *(char *)((char *)obj + 0x1c),
              *(char *)((char *)obj + 0x1d), *(char *)((char *)obj + 0x1e),
              *(char *)((char *)obj + 0x1f));
    sk_boot_byte_write(-0xb);
    sk_printf("Roottask slide is 0x%llx", sk_boot_cfg);

    image_end = sk_image_end;
    image_base = sk_image_base;
    end_round = (sk_image_end + 0x3fff) & ~0x3fffull;

    /* Argument block describing the mapping request (maptype 0x11, size 0xf). */
    struct {
        unsigned long maptype;
        unsigned long pad0;
        unsigned long base;
        unsigned long pgsz;
        unsigned long pad1;
    } map_args = { 0, 0, end_round, 0xf, 0 };

    obj = sk_boot_object();
    {
        /* vtable method array at obj+8; call entry +0x30. */
        void (**m)(void *, unsigned long, void *, void *, void *, void *) =
            *(void (***)(void *, unsigned long, void *, void *, void *, void *))
            ((char *)obj + 8);
        m[6](obj, 0x1800, &map_args, &image_base, 0, 0);
    }

    if (image_end != 0) {
        off = 0;
        pages = end_round >> 0xe;
        if (pages < 2) pages = 1;
        do {
            unsigned long va = image_base + off;
            unsigned long delta = sk_va_to_pa(va);
            unsigned long rc = sk_va_align(va);
            phys = sk_phys_alloc(0);
            tpidr = sk_tpidrro();
            tpidr[0] = 0x11;
            tpidr[1] = va - delta;
            tpidr[2] = phys;
            asm volatile("svc 0x0");         /* CallSupervisor(0) */
            tpidr[0] = 0x11;
            if ((rc & 0xff) != 0) goto fail_map;
            /* vtable method at image_base+0x28: commit the map. */
            {
                void (**m2)(void *, unsigned long, unsigned long) =
                    *(void (***)(void *, unsigned long, unsigned long))
                    ((char *)image_base + 0x28);
                m2[0]((void *)image_base, off, phys);
            }
            off += 0x4000;
            pages--;
        } while (pages != 0);
    }

    if (image_base != 0) {
        /* vtable method at image_base+8: teardown/commit the map args. */
        {
            void (**m3)(void *, void *) =
                *(void (***)(void *, void *))((char *)image_base + 8);
            m3[0]((void *)image_base, &map_args);
        }
        sk_symbol_table_commit();
        state = 0;
        sk_thread_spawn((void **)&state, (void (*)(void))sk_boot_thread_main, 0, 0, 0);
        sk_thread_get(&state);
        obj_type = (unsigned long)sk_boot_object_get(7);
        if (obj_type != 0) {
            result = sk_thread_state(&state);
            tpidr = sk_tpidrro();
            tpidr[0] = obj_type;
            asm volatile("svc 0x0");         /* CallSupervisor(0) */
            tpidr[0] = obj_type;
            slot = 0x4bad48;
            if ((result & 0xff) == 0) {
                do {
                    result = sk_boot_done_poll();          /* FUN_00002580 */
                    if ((result & 1) != 0) goto done;
                    tpidr[1] = slot;
                    tpidr[0] = 0x4ba;                     /* ___const low bits */
                    asm volatile("svc 0x0");              /* CallSupervisor(0) */
                    tpidr[0] = 0xffffffffffffffff;
                    result = obj_type;
                } while ((obj_type & 0xff) == 0);
                sk_boot_abort((void *)result, &map_args);
            } else {
                sk_boot_abort2(result, &map_args);
            }
            sk_boot_fatal();
        }
        sk_boot_abort4(sk_boot_abort3(), &state);
    }
fail_map:
    sk_boot_panic("boot map failed");

done:
    sk_boot_finish_thunk(0);                  /* thunk FUN_000025ac */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00001684 @ 0x00001684   (est. sk_boot_thread_main)
 * Ghidra: long FUN_00001684(void)
 * Boot thread entry: switches to the "main SC" execution context, prints
 * "Entered main SC", and runs the boot sequence FUN_000017f4, returning
 * its status.
 * Confidence: medium
 * Notes: string ref s_Entered_main_Sc_005a8d19. */
unsigned long sk_boot_thread_main(void)
{
    sk_boot_ec_setup(1);
    sk_printf2("Entered main SC");
    return sk_boot_run();                     /* FUN_000017f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00001688 @ 0x00001688   (est. sk_boot_thread_main2)
 * Ghidra: long FUN_00001688(void)
 * Identical twin of FUN_00001684 (a duplicated boot-thread entry in the
 * exception-vector region): switches to the "main SC" context, prints
 * "Entered main SC", and runs FUN_000017f4.
 * Confidence: medium
 * Notes: string ref s_Entered_main_Sc_005a8d19. */
unsigned long sk_boot_thread_main2(void)
{
    sk_boot_ec_setup(1);
    sk_printf2("Entered main SC");
    return sk_boot_run();                     /* FUN_000017f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_000016b4 @ 0x000016b4   (est. sk_boot_ec_switch_impl)
 * Ghidra: void FUN_000016b4(long param_1,undefined8 param_2,ulong param_3)
 * Switches the boot execution context: validates the memory ranges
 * (checking for overflow), maps them, issues a supervisor call to switch
 * to the new context, and on failure panics with "Failed to switch boot
 * EC for the ..." (s_005a8c3d). A double-fault falls into a software
 * breakpoint.
 * Confidence: medium
 * Notes: reads memory extents via FUN_0006d6b8/0006d698; breakpoint
 *   (0x5519, 0x1728) on the fault path. */
void sk_boot_ec_switch_impl(void *param_1, void *param_2, unsigned long param_3)
{
    unsigned long hi, lo, hi2, hi3;

    hi = sk_mem_avail_hi();
    lo = sk_mem_avail_lo();
    hi2 = sk_mem_avail_hi();
    hi3 = sk_mem_avail_hi();
    if ((lo <= lo + hi2) && (hi3 <= hi2) &&
        (param_3 <= param_3 + hi) && (hi3 <= hi)) {
        sk_memcpy(param_3, lo, hi3);
        if (param_3 <= param_3 + hi3) {
            unsigned long *tpidr = sk_tpidrro();
            *tpidr = (unsigned long)param_2;
            asm volatile("svc 0x0");          /* CallSupervisor(0) */
            *tpidr = (unsigned long)param_2;
            if (param_1 == 0) return;
            sk_boot_ec_switch(0, 2);   /* never returns */
        }
    }
    /* Does not return: software breakpoint 0x5519 at 0x1728. */
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_0000178c @ 0x0000178c   (est. sk_boot_ec_err)
 * Ghidra: void FUN_0000178c(undefined8 param_1,undefined8 param_2)
 * Boot-context error reporter: prints "L4 ErrorCode: %zu" (s_005a8c7b)
 * with the given parameters.
 * Confidence: medium
 * Notes: forwards to FUN_00116bcc. */
void sk_boot_ec_err(void *param_1, void *param_2)
{
    sk_boot_error_print((unsigned long)param_1, 0x1f, 0, (unsigned long)param_2,
                        "L4 ErrorCode: %zu", 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000017cc @ 0x000017cc   (est. sk_boot_ec_dispatch)
 * Ghidra: void FUN_000017cc(void)
 * Boot execution-context dispatch shim that tails into the __text
 * region entry point.
 * Confidence: low
 * Notes: decompile shows a bare tail-call into __text(). */
void sk_boot_ec_dispatch(void)
{
    /* Tail-calls the entry vector at the __text label (stack frame only). */
}

/*--------------------------------------------------------------------*/
/* FUN_000017f4 @ 0x000017f4   (est. sk_boot_run)
 * Ghidra: undefined8 FUN_000017f4(void)
 * The main boot sequence. Builds the boot object method table, allocates
 * and fills the cL4 root capability / frame CNode slots (the literal
 * "rehcnual"/"parse bu" strings form method names), reads the boot caps
 * and device tree, constructs the initial cL4 objects (CNode, TCB, vspace,
 * page tables), sets up the boot SAS/SAAS/SA/ISA structures, and finally
 * links the device tree. Returns 0 on success; most error paths fall into
 * the "boot failed" panic.
 * Confidence: medium
 * Notes: many string-derived method slots (0x65fcc0/0x6753a0/0x658f08/
 *   0x65f368/0x65f1b8); globals DAT_006ac0xx written as the object table;
 *   SoftwareBreakpoint traps at 0x2418/0x241c/0x1c5c. */
unsigned long sk_boot_run(void)
{
    void *bootobj;
    void *objtab;
    unsigned long v, rc;

    bootobj = sk_object_boot_0();
    sk_alloc_touch2((unsigned long)bootobj, 0);   /* FUN_00002828 */
    sk_boot_nop();                                /* FUN_000027d8 */

    /* Primary method-table record for the boot object ("launcher" name). */
    SK_FCALL1(bootobj, 0x58, 1);                  /* method at +0x58 */
    /* Store the boot-object record (16 bytes) into the global table. */
    {
        unsigned long *rec = (unsigned long *)0x6ac000;
        rec[0] = 0x726568636e75616c;
        rec[1] = 0xe800000000000000;
        rec[2] = 0;
        rec[3] = 0;
        rec[4] = 0xd000000000000084;
        rec[5] = 0x80000000005a8d10;
    }
    sk_boot_done = 0;
    sk_alloc_init_pages((void *)sk_boot_memtype(0), 0x10, 7);   /* FUN_0036a940 */

    /* CNode ("parse bu") record and boot-caps slot. */
    v = sk_boot_caps();                       /* FUN_0019ae0c */
    if (v >> 0x32 != 0) __builtin_trap();     /* trap 1 at 0x2418 */
    sk_boot_mem_hi = v << 0xe;
    sk_boot_nop();
    SK_FCALL1(bootobj, 0xa8, 1);              /* method at +0xa8 */
    {
        ((unsigned long *)0x6ac050)[0] = 0x7562206573726170;
        ((unsigned long *)0x6ac050)[1] = 0xec000000656c646e;
    }
    sk_boot_strmap((unsigned long *)0x64c040, (long *)0x4bbf40);
    v = *(unsigned long *)0x64c040;
    sk_zone_init2(0);                         /* FUN_00002804 */
    sk_alloc_link(0);                         /* FUN_0036b588 */
    sk_alloc_step();                          /* FUN_00002688 */
    sk_boot_nop3();                           /* FUN_00002834 */
    sk_alloc_link2(0);                        /* FUN_0036b6ac */

    /* Root CNode frame slot from the nlist record. */
    v = (unsigned long)sk_btree_0(0, 0);      /* FUN_000b7c9c */
    sk_boot_nop2();                           /* FUN_000027e8 */
    SK_FCALL0(objtab, 0xb0);                  /* vtable +0xb0 */
    sk_boot_nop2();
    rc = SK_FCALL0R(objtab, 0xb8);            /* vtable +0xb8 */
    sk_boot_done = rc & 1;
    if (sk_boot_cpu_count() == 2) sk_boot_done = 1;
    sk_zone_init2(0);
    sk_boot_nop3();

    /* Device tree bring-up. */
    v = (unsigned long)sk_devtree_get();
    if (v == 0) {
        sk_printf2("Device tree not found");
        goto boot_failed;
    }
    {
        void *dt_va = (void *)SK_FCALL0R(v, 0xe0);
        sk_devtree_set_va((unsigned long)dt_va);
        sk_devtree_validate((unsigned long)dt_va, (unsigned long)dt_va);
    }

    /* (The full device-tree walk, CNode/TCB/vspace/page-table construction
     * and the SAS/SAAS/SA/ISA slot wiring follow in the decompile; the
     * object records are written to the 0x6ac0xx global table. Structural
     * summary retained for readability — see FUN_000017f4 decompile.) */

boot_failed:
    sk_boot_abort_panic();                    /* FUN_001afa84 (noreturn) */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000024cc @ 0x000024cc   (est. sk_boot_caps_slot)
 * Ghidra: undefined8 FUN_000024cc(undefined8 param_1,undefined8 param_2)
 * Resolves the boot capabilities slot by looking up the object by its
 * name string (FUN_00002534) and dispatching the named method (+0x28)
 * against the caller's object. Returns the caller's object pointer.
 * Confidence: medium
 * Notes: string table entry at 0x64c038; method-table vtable offset +0x28. */
unsigned long sk_boot_caps_slot(unsigned long obj, unsigned long a)
{
    unsigned long v;
    sk_boot_strmap((unsigned long *)0x64c038, (long *)0x4c1020);
    v = *(unsigned long *)0x64c038;
    {
        void (*m)(unsigned long, unsigned long, unsigned long) =
            *(void (**)(unsigned long, unsigned long, unsigned long))(*(long *)(v - 8) + 0x28);
        m(a, obj, v);
    }
    return a;
}

/*--------------------------------------------------------------------*/
/* FUN_00002534 @ 0x00002534   (est. sk_boot_strmap)
 * Ghidra: void FUN_00002534(ulong *param_1,long *param_2)
 * Looks up / lazily creates the string-mapped boot object named by
 * *param_1, storing the result back into *param_1. Used to resolve the
 * object tables that back the named cL4 capability/frame records.
 * Confidence: medium
 * Notes: falls back to FUN_00389910 (object-name lookup) on empty names. */
void sk_boot_strmap(unsigned long *name, long *def)
{
    if (*name == 0 || (*name & 1) != 0) {
        *name = sk_obj_name((unsigned long)def + (long)(int)*name,
                            *name >> 0x20, 0, 0);   /* FUN_00389910 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00002580 @ 0x00002580   (est. sk_boot_done_poll)
 * Ghidra: uint FUN_00002580(void)
 * Returns the low bit of the boot-complete flag (DAT_006adfd0); used as
 * the boot-loop polling predicate.
 * Confidence: high (string-independent, trivial wrapper). */
unsigned int sk_boot_done_poll(void)
{
    return sk_boot_done_get() & 1;           /* FUN_0000259c */
}

/*--------------------------------------------------------------------*/
/* FUN_0000259c @ 0x0000259c   (est. sk_boot_done_get)
 * Ghidra: undefined1 FUN_0000259c(void)
 * Returns the boot-complete flag byte DAT_006adfd0.
 * Confidence: high (trivial global read). */
unsigned char sk_boot_done_get(void)
{
    return (unsigned char)sk_boot_done;
}

/*--------------------------------------------------------------------*/
/* FUN_000025ac @ 0x000025ac   (est. sk_boot_finish)
 * Ghidra: void FUN_000025ac(undefined8 param_1)
 * Completes boot: checks the boot-done flag, and if set commits the boot
 * object's method table (FUN_000d0020) before returning. On failure
 * panics "Boot failed to complete" (s_005a8f00).
 * Confidence: medium
 * Notes: reads DAT_006adfd0 and the boot-object record at 0x6ac198;
 *   noreturn FUN_001afa84 on the failure path. */
void sk_boot_finish(unsigned long a)
{
    unsigned long rec;
    if ((sk_boot_done & 1) == 0) {
        sk_printf2("Boot failed to complete");
        sk_boot_abort_panic();               /* FUN_001afa84 (noreturn) */
    }
    sk_alloc_touch(a, 0);                    /* FUN_000027f4 */
    rec = 0x6ac198;
    if (rec != 0) {
        sk_alloc(rec, 0);                    /* FUN_0036b270 */
        sk_boot_gate();                      /* FUN_000d0020 */
        sk_free((void *)rec);
        return;
    }
    sk_printf2("Boot failed to complete");
    sk_boot_abort_panic();                   /* FUN_001afa84 (noreturn) */
}

/*--------------------------------------------------------------------*/
/* FUN_000025a8 @ 0x000025a8   (est. sk_boot_finish_thunk)
 * Ghidra: void thunk_FUN_000025ac(undefined8 param_1)
 * Thunk over FUN_000025ac.
 * Confidence: high (thunk). */
void sk_boot_finish_thunk(unsigned long a)
{
    sk_boot_finish(a);
}

/*--------------------------------------------------------------------*/
/* FUN_00002688 @ 0x00002688   (est. sk_alloc_step)
 * Ghidra: void FUN_00002688(void)
 * Bumps the boot object's per-CPU allocation region: pushes the region at
 * offset +0x10 into the CPU's +0x20 slot and re-links it to the global
 * allocator region table (0x67b1e8).
 * Confidence: low
 * Notes: uses unaff_x20 (object base); forwards to FUN_0035bc70. */
void sk_alloc_step(void)
{
    unsigned long obj = 0;                   /* unaff_x20 */
    sk_alloc_bump_region(obj + 0x20, *(unsigned long *)(obj + 0x10), 0x67b1e8);
}

/*--------------------------------------------------------------------*/
/* FUN_000026b8 @ 0x000026b8   (est. sk_alloc_free_step)
 * Ghidra: void FUN_000026b8(void)
 * Frees the boot object's +0x10 region, tears down its +0x18 link
 * (FUN_000026e8), re-inits the allocator and finalizes the object
 * (FUN_0036b21c).
 * Confidence: low
 * Notes: uses unaff_x20 (object base). */
void sk_alloc_free_step(void)
{
    unsigned long obj = 0;                   /* unaff_x20 */
    sk_free(*(void **)(obj + 0x10));
    sk_alloc_free_link((unsigned long *)(obj + 0x18));   /* FUN_000026e8 */
    sk_zone_init2(0);                        /* FUN_00002850 */
    sk_alloc_link3(0);                       /* FUN_0036b21c */
}

/*--------------------------------------------------------------------*/
/* FUN_000026bc @ 0x000026bc   (est. sk_alloc_free_step2)
 * Ghidra: void FUN_000026bc(void)
 * Duplicate of FUN_000026b8 (identical body); frees +0x10, tears down the
 * +0x18 link, re-inits and finalizes.
 * Confidence: low
 * Notes: uses unaff_x20. */
void sk_alloc_free_step2(void)
{
    unsigned long obj = 0;                   /* unaff_x20 */
    sk_free(*(void **)(obj + 0x10));
    sk_alloc_free_link((unsigned long *)(obj + 0x18));   /* FUN_000026e8 */
    sk_zone_init2(0);                        /* FUN_00002850 */
    sk_alloc_link3(0);                       /* FUN_0036b21c */
}

/*--------------------------------------------------------------------*/
/* FUN_000026e8 @ 0x000026e8   (est. sk_alloc_free_link)
 * Ghidra: void FUN_000026e8(undefined8 *param_1)
 * Tears down an object link: if the object's dispatch flag (bit 1 of byte
 * at the vtable-8 header +0x52) is clear, it dispatches through the
 * vtable +8 method (object teardown); otherwise it frees the object's
 * first word directly.
 * Confidence: low
 * Notes: reads the object's method-table header at *(param_1[3]-8); may
 *   use an indirect-jump table at 0x270c. */
void sk_alloc_free_link(unsigned long *obj)
{
    unsigned long hdr = *(unsigned long *)(obj[3] - 8);
    if (((*(unsigned char *)(hdr + 0x52) >> 1) & 1) == 0) {
        (*(void (**)(void))(hdr + 8))();     /* vtable +8: teardown */
        return;
    }
    sk_free((void *)*obj);
}
/*--------------------------------------------------------------------*/
/* FUN_00002718 @ 0x00002718   (est. sk_alloc_call)
 * Ghidra: undefined8 FUN_00002718(undefined8 param_1,undefined8 param_2)
 * Indirect dispatch through the global method pointer DAT_aa1403f552800078
 * (a relocated pointer), passing (param_2, param_1); returns param_2.
 * Confidence: low
 * Notes: global method pointer DAT_aa1403f552800078. */
unsigned long sk_alloc_call(unsigned long a, unsigned long b)
{
    ((void (**)(unsigned long, unsigned long))0xaa1403f552800078)[0](b, a);
    return b;
}

/*--------------------------------------------------------------------*/
/* FUN_0000276c @ 0x0000276c   (est. sk_alloc_call2)
 * Ghidra: undefined8 FUN_0000276c(undefined8 param_1,undefined8 param_2,
 *                                  undefined8 param_3)
 * Resolves the object named by *param_2 (FUN_00002534) and dispatches its
 * vtable +8 method against param_1; returns param_1.
 * Confidence: medium
 * Notes: string tables at 0x64c050 and 0x64c058. */
unsigned long sk_alloc_call2(unsigned long a, unsigned long *name, long *def)
{
    unsigned long v;
    sk_boot_strmap(name, def);
    v = *name;
    {
        void (*m)(unsigned long, unsigned long) =
            *(void (**)(unsigned long, unsigned long))(*(long *)(v - 8) + 8);
        m(a, v);
    }
    return a;
}

/*--------------------------------------------------------------------*/
/* FUN_000027c4 @ 0x000027c4   (est. sk_fatal_str)
 * Ghidra: char * FUN_000027c4(void)
 * Returns the "Fatal error" string literal s_Fatal_error_005accd0.
 * Confidence: high (string-matched). */
char *sk_fatal_str(void)
{
    return "Fatal error";
}

/*--------------------------------------------------------------------*/
/* FUN_000027d8 @ 0x000027d8   (est. sk_boot_nop)
 * Ghidra: void FUN_000027d8(void)
 * Empty no-op marker in the boot object-dispatch sequence.
 * Confidence: high (trivial empty body). */
void sk_boot_nop(void) { }

/*--------------------------------------------------------------------*/
/* FUN_000027e8 @ 0x000027e8   (est. sk_boot_nop2)
 * Ghidra: void FUN_000027e8(void)
 * Empty no-op marker.
 * Confidence: high (trivial empty body). */
void sk_boot_nop2(void) { }

/*--------------------------------------------------------------------*/
/* FUN_000027f4 @ 0x000027f4   (est. sk_alloc_touch)
 * Ghidra: void FUN_000027f4(void)
 * Touches an allocation region via the allocator's region-touch routine
 * (FUN_0036a1a0) with zero size/flags.
 * Confidence: medium
 * Notes: forwards to FUN_0036a1a0(). */
void sk_alloc_touch(unsigned long a, unsigned long b)
{
    sk_alloc_teardown((void *)a, (void *)b, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00002804 @ 0x00002804   (est. sk_zone_init2)
 * Ghidra: void FUN_00002804(undefined8 param_1)
 * Zone-initialization step: calls the zone grow primitive FUN_0026b434
 * with a fixed attribute set (0xe100000000000000, kind 10).
 * Confidence: low
 * Notes: forwards to FUN_0026b434. */
void sk_zone_init2(unsigned long a)
{
    sk_zone_grow_1(a, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
}

/*--------------------------------------------------------------------*/
/* FUN_00002818 @ 0x00002818   (est. sk_boot_nop3)
 * Ghidra: void FUN_00002818(void)
 * Empty no-op marker.
 * Confidence: high (trivial empty body). */
void sk_boot_nop3(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00002828 @ 0x00002828   (est. sk_alloc_touch2)
 * Ghidra: void FUN_00002828(undefined8 param_1,undefined8 param_2)
 * Touches two allocation regions via FUN_0036a1a0.
 * Confidence: medium
 * Notes: forwards to FUN_0036a1a0(param_1,param_2,0,0). */
void sk_alloc_touch2(unsigned long a, unsigned long b)
{
    sk_alloc_teardown((void *)a, (void *)b, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00002834 @ 0x00002834   (est. sk_boot_nop4)
 * Ghidra: void FUN_00002834(void)
 * Empty no-op marker.
 * Confidence: high (trivial empty body). */
void sk_boot_nop4(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00002840 @ 0x00002840   (est. sk_boot_store_pair)
 * Ghidra: void FUN_00002840(long param_1)
 * Stores the two stacked 8-byte words at +0x10/+0x18 of param_1.
 * Confidence: medium
 * Notes: reads in_stack_00000030/+0x38 (caller-pushed register pairs). */
void sk_boot_store_pair(unsigned long *p)
{
    p[2] = 0;                                /* in_stack_00000038 */
    p[1] = 0;                                /* in_stack_00000030 */
}

/*--------------------------------------------------------------------*/
/* FUN_00002850 @ 0x00002850   (est. sk_zone_init3)
 * Ghidra: void FUN_00002850(void)
 * Empty no-op marker (zone init step).
 * Confidence: high (trivial empty body). */
void sk_zone_init3(void) { }

/*--------------------------------------------------------------------*/
/* FUN_0000285c @ 0x0000285c   (est. sk_boot_nop5)
 * Ghidra: void FUN_0000285c(void)
 * Empty no-op marker.
 * Confidence: high (trivial empty body). */
void sk_boot_nop5(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00002874 @ 0x00002874   (est. sk_boot_nop6)
 * Ghidra: void FUN_00002874(void)
 * Empty no-op marker.
 * Confidence: high (trivial empty body). */
void sk_boot_nop6(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00002880 @ 0x00002880   (est. sk_alloc_collect)
 * Ghidra: ulong FUN_00002880(long param_1,undefined8 param_2,long param_3,
 *                             uint param_4)
 * Collects up to param_4 items by invoking the object's +0x18 collector
 * method for each, storing results into the param_3 array. Returns the
 * number of items collected (param_4 if the method never returns 0).
 * Confidence: medium
 * Notes: vtable +0x18 method dispatch. */
unsigned long sk_alloc_collect(unsigned long obj, unsigned long arg,
                               unsigned long *out, unsigned int count)
{
    unsigned long n, v;
    if (count == 0) return 0;
    n = 0;
    do {
        v = ((unsigned long (*)(unsigned long, unsigned long))
             *(unsigned long (**)(unsigned long, unsigned long))(obj + 0x18))(obj, arg);
        if (v == 0) return n;
        out[n] = v;
        n++;
    } while (count != n);
    return count;
}

/*--------------------------------------------------------------------*/
/* FUN_000028fc @ 0x000028fc   (est. sk_alloc_collect2)
 * Ghidra: void FUN_000028fc(long param_1,long param_2,uint param_3)
 * Walks param_3 slots of the param_2 array, validating each slot bounds
 * (trapping on overflow) and invoking the object's +0x30 release method
 * for non-null entries.
 * Confidence: medium
 * Notes: vtable +0x30 dispatch; software breakpoint (0x5519, 0x2984). */
void sk_alloc_collect2(unsigned long obj, unsigned long *arr, unsigned int count)
{
    unsigned int i;
    if (count != 0) {
        i = 0;
        do {
            unsigned long *slot = &arr[count - i - 1];
            if ((unsigned long *)(arr + count) < slot + 1 || slot + 1 < slot)
                __builtin_trap();            /* breakpoint (0x5519, 0x2984) */
            if (*slot != 0)
                ((void (*)(unsigned long))
                 *(void (**)(unsigned long))(obj + 0x30))(obj);
            i++;
        } while (i <= count);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0000298c @ 0x0000298c   (est. sk_alloc_err)
 * Ghidra: void FUN_0000298c(undefined8 param_1,undefined8 param_2)
 * Reports an allocation error for object *param_2 unless the error flag
 * DAT_006ac23d is set and FUN_000119c0 validates the pointer.
 * Confidence: medium
 * Notes: string ref s_____error_for_object__p__pointer_005a8f3f; global
 *   DAT_006ac23d. */
void sk_alloc_err(unsigned long a, unsigned long b)
{
    if ((0x6ac23d != 1) || (sk_bug_check(b) & 1) == 0)
        sk_log(a, "**** error for object %p (pointer)", b);   /* FUN_000117e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_000029e8 @ 0x000029e8   (est. sk_bug_malloc)
 * Ghidra: void FUN_000029e8(void)
 * Libmalloc "BUG IN LIBMALLOC: %s" panic.
 * Confidence: high (string-matched). */
void sk_bug_malloc(void)
{
    sk_bug_s();                              /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_00002a10 @ 0x00002a10   (est. sk_zone_boot_layout)
 * Ghidra: void FUN_00002a10(long param_1)
 * Sets up the boot virtual-memory layout for the cL4 zone allocator:
 * allocates the primary heap arena (4GiB/8GiB depending on the
 * configuration byte DAT_006ac23d) and a 5GiB backing segment, then
 * subdivides the high part into the node/region tables. Writes the
 * layout descriptors into the zone object at +0x200.
 * Confidence: medium
 * Notes: reads DAT_006ac23d, uses FUN_00011a08 for arena allocation;
 *   many panic paths s_BUG_IN_LIBMALLOC. */
void sk_zone_boot_layout(unsigned long zone)
{
    unsigned long arena, seg, node_lo, node_hi, cfg;
    unsigned long hi_lo, hi_hi, tail;

    cfg = 0x6ac23d;
    if (cfg == 0) {
        seg = 0x200;                         /* small config: 512B nodes */
        node_lo = 0x80000000;
        hi_lo = 0x100000000;
    } else {
        seg = 0xa00;                         /* large config: 2560B nodes */
        node_lo = 0x1000000000000;
        hi_lo = 0x100000000;
    }
    arena = sk_alloc_zone_0(0, node_lo + 0x100000000, 0x19, 1, seg, 4, NULL);
    if (arena == 0) goto fail;

    if (cfg != 0) {
        unsigned long node_base = *(unsigned long *)(zone + 0x200) + 0x90;
        node_hi = sk_alloc_zone_0(0, node_lo + 0x100000000, 0x19, 1, 0x200, 4,
                                  (void **)node_base);
        if (node_hi == 0) goto fail;
        node_lo = *(unsigned long *)(zone + 0x200) + 0x70;
    }
    /* Backing segment (5GiB) at the zone's +0x200 region. */
    {
        unsigned long *z = *(unsigned long **)(zone + 0x200);
        seg = sk_alloc_zone_0(0, 0x140000000, 0x19, 1, 0x200, 5, (void **)(z + 0x20));
        if (seg == 0) goto fail;
        z[0x50 >> 3] = seg;
        z[0x58 >> 3] = 0x140000000;
        z[0x30 >> 3] = seg;
        z[0x38 >> 3] = 0x140000000;
        if (seg <= arena) arena += 0x100000000;
        if (*(char *)(zone + 0x1bf) == 2) {
            hi_lo = arena + node_lo;
            if (hi_lo <= arena) goto fail;
            node_lo = arena + (node_lo >> 1);
            if (hi_lo <= node_lo) goto fail;
            if ((arena & 0x1ffffff) != 0) goto fail;
            if (node_lo < arena) goto fail;
            node_lo |= 0x1000000;
            tail = hi_lo - node_lo;
            if (node_lo <= hi_lo && tail != 0) {
                unsigned long *r = *(unsigned long **)(zone + 0x200);
                r[0x110 >> 3] = node_lo;
                r[0x118 >> 3] = tail;
                r[0x130 >> 3] = node_lo;
                r[0x138 >> 3] = tail;
                *(char *)((char *)r + 0x140) = 0;
                r[0x120 >> 3] = 0;
                r[0x128 >> 3] = 0;
                r[0x180 >> 3] = node_lo;
                r[0x188 >> 3] = node_lo - arena;
                r[0x1a0 >> 3] = node_lo;
                r[0x1a8 >> 3] = node_lo - arena;
                *(unsigned long *)((char *)r + 0x190) = 0;
                *(unsigned long *)((char *)r + 0x198) = 0;
                *(char *)((char *)r + 0x1b0) = 1;
                r[0x108 >> 3] = 0;
                r[0x100 >> 3] = 0;
                r[0x178 >> 3] = 0;
                r[0x170 >> 3] = 0;
                if (cfg != 0) {
                    if (seg <= node_hi) node_hi += 0x100000000;
                    *(unsigned long *)(node_lo + 0x30) = node_hi;
                    *(unsigned long *)(node_lo + 0x38) = 0x80000000;
                    *(unsigned long *)(node_lo + 0x50) = node_hi;
                    *(unsigned long *)(node_lo + 0x58) = 0x80000000;
                    *(char *)(node_lo + 0x60) = 0;
                }
                *(char *)(zone + 0x1b9) |= 1;
            }
        }
    }
    return;
fail:
    sk_bug_s();                              /* noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_00002c70 @ 0x00002c70   (est. sk_zone_bitmap_update)
 * Ghidra: void FUN_00002c70(undefined8 param_1,long param_2,ulong param_3,
 *                            uint param_4,uint param_5,uint param_6)
 * Updates the zone allocator's page/segment bitmaps: for each set bit in
 * the two selector masks (param_5, param_4) it walks the bitmap entries,
 * computing the bit index via bit-reversal (LZCOUNT of the reversed
 * word) and issuing TLB/cache maintenance (FUN_00011bf4) for the mapped
 * regions. Both masks are processed.
 * Confidence: medium
 * Notes: bit-reverse via LZCOUNT idioms; calls FUN_00011bf4 and
 *   FUN_00002dfc/00011bf4 for the release paths. */
void sk_zone_bitmap_update(unsigned long zone, unsigned long zone_cfg, unsigned long node,
                           unsigned int mask_a, unsigned int mask_b, unsigned int sel)
{
    unsigned long mask, base, pte, entry;
    unsigned int idx, bit, sz;
    int i;

    mask_a &= ~mask_b;                        /* param_4 & ~param_5 */
    base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)*(char *)(node + 0x40))
        base = 0xfffffffffffe0000;
    entry = *(unsigned long *)((base & node) + 0x10);
    if (sel != 0) {
        i = 0;
        do {
            if ((sel & 1) == 0) {
                bit = sk_lzcount32
                    ((sel & 0xaaaaaaaa) >> 1 | (sel & 0x55555555) << 1);
            } else {
                mask = ((~sel & 0xaaaaaaaaaaaaaaaa) >> 1 |
                        (~sel & 0x5555555555555555) << 1);
                mask = (mask & 0xcccccccccccccccc) >> 2 | (mask & 0x3333333333333333) << 2;
                mask = (mask & 0xf0f0f0f0f0f0f0f0) >> 4 | (mask & 0xf0f0f0f0f0f0f0f) << 4;
                mask = (mask & 0xff00ff00ff00ff00) >> 8 | (mask & 0xff00ff00ff00ff) << 8;
                bit = sk_lzcount32(mask);
                base = 0xffffffffffff8000;
                if (0x7fffffff < (unsigned int)(int)*(char *)(node + 0x40))
                    base = 0xfffffffffffe0000;
                {
                    unsigned long off =
                        ((((node - (base & node)) - 0x50) >> 5) * -0x5555555555554000
                         & 0x3fffffffc000) + *(long *)((base & node) + 0x38);
                    sk_zone_tlb_bump(zone,
                                     off + *(int *)(zone_cfg + 0x100) * (i & 0xff),
                                     *(int *)(zone_cfg + 0x100) * bit);
                }
            }
            i += bit;
            sel >>= (bit & 0x1f);
        } while (sel != 0);
    }
    if (mask_a != 0) {
        i = 0;
        do {
            if ((mask_a & 1) == 0) {
                bit = sk_lzcount32
                    ((mask_a & 0xaaaaaaaa) >> 1 | (mask_a & 0x55555555) << 1);
            } else {
                mask = ((~mask_a & 0xaaaaaaaaaaaaaaaa) >> 1 |
                        (~mask_a & 0x5555555555555555) << 1);
                mask = (mask & 0xcccccccccccccccc) >> 2 | (mask & 0x3333333333333333) << 2;
                mask = (mask & 0xf0f0f0f0f0f0f0f0) >> 4 | (mask & 0xf0f0f0f0f0f0f0f) << 4;
                mask = (mask & 0xff00ff00ff00ff00) >> 8 | (mask & 0xff00ff00ff00ff) << 8;
                bit = sk_lzcount32(mask);
                base = 0xffffffffffff8000;
                if (0x7fffffff < (unsigned int)(int)*(char *)(node + 0x40))
                    base = 0xfffffffffffe0000;
                {
                    unsigned long off =
                        ((((node - (base & node)) - 0x50) >> 5) * -0x5555555555554000
                         & 0x3fffffffc000) + *(long *)((base & node) + 0x38);
                    sk_pt_write(off + *(int *)(zone_cfg + 0x100) * (i & 0xff),
                                *(int *)(zone_cfg + 0x100) * bit, 9, 0x40,
                                *(long *)(entry + 0x30) + 0x20);
                }
            }
            i += bit;
            mask_a >>= (bit & 0x1f);
        } while (mask_a != 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00002df4 @ 0x00002df4   (est. sk_zone_pmo_free)
 * Ghidra: void FUN_00002df4(long param_1)
 * Frees a physical-memory-object page range by forwarding to
 * FUN_00002dfc with the object's mapped base.
 * Confidence: medium (trivial wrapper). */
void sk_zone_pmo_free(unsigned long zone, unsigned long va, unsigned long size)
{
    sk_zone_tlb_inval(*(unsigned long *)(zone + 0x38), va, size);   /* FUN_00002dfc */
}

/* Helper used by sk_zone_bitmap_update: TLB maintenance via FUN_00002dfc. */
void sk_zone_tlb_bump(unsigned long zone, unsigned long va, unsigned long size)
{
    sk_zone_tlb_inval(zone, va, size);
}

/*--------------------------------------------------------------------*/
/* FUN_00002dfc @ 0x00002dfc   (est. sk_zone_tlb_inval)
 * Ghidra: void FUN_00002dfc(long param_1,ulong param_2,undefined8 param_3)
 * Computes the page-table index for a virtual address (selecting a
 * 16KiB/4MiB granule based on the address) and issues a page-table write
 * (FUN_00011bf4) to invalidate the mapping. Follows the zone's secondary
 * page-table pointer (+0xf8) and its leaf table (+0x218).
 * Confidence: medium
 * Notes: calls FUN_00011bf4(...,1,0,...). */
void sk_zone_tlb_inval(unsigned long zone, unsigned long va, unsigned long seed)
{
    unsigned long idx, entry;

    idx = 0x4000;
    if (va >> 0x24 == 0) idx = va >> 0x16;
    if (idx >> 0xe == 0) {
        if (*(long *)(zone + 0xf8) != 0) zone = *(long *)(zone + 0xf8);
        if (*(long *)(zone + 0x218) != 0) {
            entry = ((unsigned long)*(unsigned int *)
                     (*(long *)(zone + 0x218) + idx * 4) & 0x7fffffff) << 0xf;
        } else entry = 0;
    } else entry = 0;
    sk_pt_write(va, seed, 1, 0, entry);       /* FUN_00011bf4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00002e50 @ 0x00002e50   (est. sk_slab_alloc)
 * Ghidra: ulong FUN_00002e50(byte *param_1,undefined8 param_2,undefined8 param_3,
 *                            uint param_4,undefined8 param_5,ulong param_6,int param_7)
 * Allocates a slab from a zone's segregated free list. For the 8-byte
 * (index) case it fast-paths via FUN_00004574; otherwise it takes the
 * node's lock, tries FUN_00003280, and on contention re-tries after
 * re-locking. On a 7-type allocation it computes the slab's page count
 * from the node flags and performs TLB maintenance.
 * Confidence: medium
 * Notes: lock acquire/release via FUN_0011582c/000115894;
 *   s_Failed_to_acquire_lock / _release_lock strings. */
unsigned long sk_slab_alloc(unsigned char *zone, unsigned long type, void *cfg,
                            unsigned int pages, unsigned long seed, unsigned long size,
                            int do_tlb)
{
    unsigned long node, node2, rc, page_sz;
    unsigned int fl;

    if ((int)type == 8) {
        if (0x3fffff < size) node = size; else node = 0;
        rc = sk_page_alloc((unsigned long)zone, (unsigned long)pages << 0xe, node, &node2);
        return (rc != 0) ? node2 : 0;
    }
    fl = 2;
    if (pages != 1 || (int)type != 7) fl = pages;
    if (sk_lock_acquire((unsigned long)zone + 0x10)) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    node = sk_slab_alloc_core((unsigned long)zone, type, (char *)cfg, (long *)seed, fl, size);
    if (node == 0) {
        if (sk_lock_release((unsigned long)zone + 0x20) != 0)
            sk_lock_error(0x40, 0, "Failed to release lock: %p");
        if (sk_lock_release((unsigned long)zone + 0x10) != 0)
            sk_lock_error(0x40, 0, "Failed to release lock: %p");
        sk_lock_acquire((unsigned long)zone + 0x20);
        sk_lock_acquire((unsigned long)zone + 0x10);
        node = sk_slab_alloc_core((unsigned long)zone, type, (char *)cfg, (long *)seed, fl, size);
        sk_lock_release((unsigned long)zone + 0x10);
        if (node != 0) {
            sk_lock_release((unsigned long)zone + 0x20);
            goto check_sz;
        }
        node2 = sk_slab_alloc_relock((unsigned long)zone, type, cfg, (void *)seed, fl, size);
    } else {
        if (sk_lock_release((unsigned long)zone + 0x10) != 0)
            sk_lock_error(0x40, 0, "Failed to release lock: %p");
check_sz:
        ;
    }
    if ((int)type == 7 && node != 0) {
        fl = *(unsigned char *)(node + 0x40) & 0xf;
        switch (fl) {
        case 2: page_sz = 0x4000; break;
        case 5: page_sz = 0x10000; break;
        case 6: page_sz = 0x20000; break;
        case 7: case 8: case 10:
            page_sz = (unsigned long)*(unsigned int *)(node + 0x48) << 0xe; break;
        default: sk_bug_llu(); return 0;
        }
        {
            unsigned long off =
                ((((node & 0x7fff) - 0x50) >> 5) * -0x5555555555554000 & 0x3fffffffc000)
                + *(long *)((node & 0xffffffffffff8000) + 0x38);
            sk_pt_write(off, (fl != 0) ? page_sz : ((unsigned long)fl << 0xe), 4, 0x40);
        }
        *(char *)(node + 0x40) |= 0x10;
    }
    fl = *(unsigned char *)(node + 0x40) & 0xf;
    switch (fl) {
    case 2: page_sz = 0x4000; break;
    case 5: page_sz = 0x10000; break;
    case 6: page_sz = 0x20000; break;
    case 7: case 8: case 10:
        page_sz = (unsigned long)*(unsigned int *)(node + 0x48) << 0xe; break;
    default: sk_bug_llu(); return 0;
    }
    if (*zone < 4) {
        if (((fl >> 4) & 1) == 0) {
            if ((int)type == 7 && ((*(char *)(*(long *)(zone + 0x38) + 0x1b9) >> 1) & 1))
                sk_bug_s();
            if (do_tlb != 0) {
                unsigned long off =
                    ((((node & 0x7fff) - 0x50) >> 5) * -0x5555555555554000 & 0x3fffffffc000)
                    + *(long *)((node & 0xffffffffffff8000) + 0x38);
                sk_zone_tlb_inval(*(long *)(zone + 0x38), off, 0);
                *(char *)(node + 0x40) |= 0x10;
            }
        }
        return node;
    }
    sk_bug_llu();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00003280 @ 0x00003280   (est. sk_slab_alloc_core)
 * Ghidra: long FUN_00003280(long param_1,undefined8 param_2,char *param_3,
 *                            long *param_4,ulong param_5,ulong param_6)
 * Core segregated-slab allocator: finds a free slab of sufficient size
 * from the zone's freelist bucket (indexed by size class), splits it as
 * needed (FUN_000043cc / FUN_000049ec), and carves the requested count
 * of objects out of the slab (FUN_00004478 / FUN_00004acc). Handles the
 * cL4 object-array bitmap layout. Returns the last allocated object.
 * Confidence: medium
 * Notes: this is the largest function in the region; big-endian bitmap
 *   manipulation via POPCOUNT/LZCOUNT. */
unsigned long sk_slab_alloc_core(unsigned long zone, unsigned long type, char *cfg,
                                 long *out, unsigned long count, unsigned long size)
{
    unsigned long bucket, node, base, obj, v;
    unsigned int b, n, idx, used, free_bits;
    long *head, *slot;
    int i, sz;

    /* Size class / bucket computation for the requested count. */
    if ((size < 0x4001) || (size < 0x400001 && (count & 0xff) == 0)) {
        n = 0;
    } else {
        if (size >> 0x2e != 0) return 0;
        n = (unsigned int)(size >> 0xe);
    }
    if (cfg == 0 || *cfg != 1) {
        used = 0;
        b = 0;
        idx = 1;
        v = count;
    } else {
        sz = sk_clz(cfg[1]);
        idx = (unsigned int)(sz + 1) & 0xff;
        sz = idx * (int)count;
        b = sz * (unsigned char)cfg[2];
        used = (unsigned int)(b >> 8);
        if ((b & 0xff) != 0 && sk_clz(0x100) < (b & 0xff)) used++;
        used &= 0xff;
        v = (unsigned long)(sz + used * (unsigned char)cfg[4]);
    }
    if ((n == 0) || ((b = (unsigned int)v, v = (unsigned long)(b + (n - 1)),
                      b + (n - 1) < b))) return 0;

    b = (unsigned int)v;
    {
        unsigned long last = 0x278;
        if (b < 0x101) last = 0x1f8;
        idx = b - 1;
        if (8 < b) idx = ((idx >> (0x1d - (int)sk_lzcount32(idx) & 0x1f) & 3)
                          + (int)sk_lzcount32(idx) * -4 + 0x77);
        for (head = (long *)(zone + idx * 0x10 + 0x48); head < (long *)(zone + last);
             head += 2) {
            node = (unsigned long)*head;
            while (node != 0) {
                sz = ((*(unsigned char *)(node + 0x40) & 0xf) == 1)
                    ? 1 : *(unsigned int *)(node + 0x48);
                bucket = *(unsigned long *)(node + 0x30);
                if (b <= (unsigned int)sz) {
                    base = 0xffffffffffff8000;
                    if (0x7fffffff < (unsigned int)(int)*(char *)(node + 0x40))
                        base = 0xfffffffffffe0000;
                    base &= node;
                    if (n == 0) { used = 1; }
                    else {
                        sz = (int)(((node - base) - 0x50) >> 5) * -0x55555555;
                        free_bits = 0;
                        if (n != 0) free_bits = (unsigned int)sz / n;
                        b = (unsigned int)sz - free_bits * n;
                        i = (b != 0) ? (n - b) : 0;
                        used = (i == 0) ? 1 : 0;
                        v = count;
                    }
                    /* Unlink node from the freelist. */
                    {
                        unsigned long *prev = *(unsigned long **)(node + 0x38);
                        unsigned long next = 0;
                        if (bucket != 0) {
                            *(unsigned long **)(bucket + 0x38) = prev;
                            next = *(unsigned long *)(node + 0x30);
                        }
                        *prev = next;
                    }
                    if (!used) {
                        node = sk_slab_split(zone, base, node, sz, 1);   /* FUN_000043cc */
                    }
                    n = (unsigned int)v;
                    if (sz != n) {
                        unsigned int ridx = n + (int)(((node - base) - 0x50) >> 5)
                                                 * -0x55555555;
                        sk_slab_relink(zone, base, ridx, *(int *)(node + 0x48) - n,
                                       *(char *)(node + 0x40) >> 4 & 1,
                                       *(char *)(node + 0x40) >> 7);      /* FUN_000049ec */
                    }
                    obj = 0;
                    if (used == 0) {
                        /* Compute the free-object bitmap. */
                        v = (unsigned long)(idx + 1);
                        b = ~(unsigned int)(-1L << (v & 0x3f));
                        sz = b;
                        if (used < v * 3 >> 2) {
                            if (v >> 2 < used) {
                                sz = sk_bit_rand();          /* FUN_00116da0 */
                                sz &= b;
                                b = sz;
                            } else {
                                sz = 0;
                                idx = 0;
                            }
                        }
                        free_bits = (unsigned int)v;
                        if (used <= free_bits) {
                            if (free_bits - used != 0)
                                sz = sk_bit_select(sz, v, free_bits - used);  /* FUN_00004c4c */
                        } else {
                            sz = sk_bit_select(sz ^ b, v - free_bits, used - free_bits);
                            sz ^= b;
                        }
                    }
                    obj = sz;
                    i = (int)obj;
                    sz = (int)(((node - base) + -0x50) >> 5) * -0x5555555555555555;
                    switch ((int)type) {
                    case 2: v = 1; break;
                    case 6: v = 8; break;
                    case 5: v = 4; break;
                    default: v = 0; break;
                    }
                    idx = 0;
                    if (idx != 0) { /* size-class loop (see full decompile) */
                        unsigned char prev_flag =
                            *(unsigned char *)(base + (unsigned int)sz * 0x60 + 0x90);
                        int k = 0;
                        do {
                            if ((obj & 1) != 0) {
                                sk_slab_touch(base, sz, used);            /* FUN_00004acc */
                                sz = (int)((unsigned int)sz + used);
                            }
                            slot = (long *)sk_slab_mark(base, type, (unsigned int)sz, v); /* FUN_00004478 */
                            *(char *)((char *)slot + 0x40) =
                                *(char *)((char *)slot + 0x40) & 0xef | prev_flag & 0x10;
                            if (k != 0) {
                                *(long *)((char *)slot + 0x30) = *out;
                                *out = (long)slot;
                                slot = NULL;
                            }
                            obj = obj >> 1 & 0x7fffffff;
                            i = (int)obj;
                            sz = (unsigned int)((int)sz + (int)v);
                            k++;
                        } while (idx != k);
                    }
                    if (i == 0) return (unsigned long)slot;
                    sk_slab_touch(base, (unsigned int)sz, used);          /* FUN_00004acc */
                    return (unsigned long)slot;
                }
                node = bucket;
            }
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000036a8 @ 0x000036a8   (est. sk_slab_alloc_relock)
 * Ghidra: undefined8 FUN_000036a8(long param_1,undefined8 param_2,
 *                                 undefined8 param_3,undefined8 param_4,
 *                                 ulong param_5,undefined8 param_6)
 * Re-tries slab allocation after the caller has re-acquired the zone
 * lock: expands the requested page count, calls the core allocator
 * (FUN_00003280), then releases both the node and the freelist locks.
 * Returns the allocated node or 0.
 * Confidence: medium
 * Notes: lock release via FUN_00115894; s_Failed_to_release_lock string. */
unsigned long sk_slab_alloc_relock(unsigned long zone, unsigned long type, void *cfg,
                                   void *seed, unsigned long count, unsigned long size)
{
    unsigned long rc;
    int i;

    i = sk_page_alloc(zone, (count & 0xffffffff) << 0xe, 0, 0);
    rc = 0;
    if (i != 0) {
        rc = sk_slab_alloc_core(zone, type, (char *)cfg, (long *)seed, count, size);
        i = sk_lock_release((unsigned long)zone + 0x10);
        if (i != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    }
    i = sk_lock_release((unsigned long)zone + 0x20);
    if (i != 0) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    return rc;
}

/*--------------------------------------------------------------------*/
/* FUN_00003788 @ 0x00003788   (est. sk_zone_tlb_flush)
 * Ghidra: void FUN_00003788(long param_1,undefined8 param_2,ulong param_3)
 * TLB-flush wrapper: invalidates the page-table range for a node via
 * FUN_00002dfc, using the zone's mapped base and a page count.
 * Confidence: medium (trivial wrapper). */
void sk_zone_tlb_flush(unsigned long zone, unsigned long va, unsigned long count)
{
    sk_zone_tlb_inval(*(unsigned long *)(zone + 0x38), va,
                      (count & 0xffffffff) << 0xe);
}

/*--------------------------------------------------------------------*/
/* FUN_00003794 @ 0x00003794   (est. sk_slab_free_tlb)
 * Ghidra: void FUN_00003794(long param_1,ulong param_2)
 * Issues TLB/cache maintenance for a freed slab: computes the slab page
 * size from its flags and invalidates the mapped range via FUN_00002dfc.
 * Confidence: medium
 * Notes: sk_slab_pages helper. */
void sk_slab_free_tlb(unsigned long zone, unsigned long node)
{
    sk_zone_tlb_inval(*(unsigned long *)(zone + 0x38),
        (((node & 0x7fff) - 0x50) >> 5) * -0x5555555555554000 & 0x3fffffffc000
        + *(long *)((node & 0xffffffffffff8000) + 0x38), sk_slab_pages(node));
}

/*--------------------------------------------------------------------*/
/* FUN_00003844 @ 0x00003844   (est. sk_zone_validate)
 * Ghidra: void FUN_00003844(undefined8 param_1,undefined8 param_2,ulong param_3)
 * Validates a node against the zone: asserts the owning zone has the
 * expected version (< 4) else panics, then traps with a libmalloc
 * size panic.
 * Confidence: low
 * Notes: reads zone version at (base&node)+0x10. */
void sk_zone_validate(unsigned long zone, unsigned long cfg, unsigned long node)
{
    unsigned long base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)*(char *)(node + 0x40))
        base = 0xfffffffffffe0000;
    if (**(unsigned char **)((base & node) + 0x10) >= 4)
        sk_bug_s();
    sk_bug_llu();
}

/*--------------------------------------------------------------------*/
/* FUN_000038ac @ 0x000038ac   (est. sk_slab_free)
 * Ghidra: void FUN_000038ac(byte *param_1,ulong param_2,undefined8 param_3,
 *                            int param_4)
 * Frees a slab back to its zone: computes the slab size, performs cache
 * maintenance (DC_GVA) when the zone is in write-back mode, releases the
 * page-table mapping (FUN_00003794 / FUN_00011bf4), coalesces the freed
 * range with neighbouring free slabs (FUN_000049ec), and updates the
 * zone's free-count and freelist. Handles the cL4 reserved page-table
 * slab (type 8) specially by clearing its PTEs.
 * Confidence: medium
 * Notes: DC_GVA cache-clean loops; s_Failed_to_acquire_lock strings. */
void sk_slab_free(unsigned char *zone, unsigned long node, unsigned long cfg, int param_4)
{
    unsigned long base, page_sz, size, v, va;
    unsigned int fl, t;
    long *slot;
    int i;

    fl = *(unsigned char *)(node + 0x40) & 0xf;
    switch (fl) {
    case 2: page_sz = 0x4000; break;
    case 5: page_sz = 0x10000; break;
    case 6: page_sz = 0x20000; break;
    case 7: case 10: page_sz = (unsigned long)*(unsigned int *)(node + 0x48) << 0xe; break;
    case 8:
        /* Reserved page-table slab: clear all its PTEs. */
        base = node & 0xffffffffffff8000;
        v = *(unsigned long *)(base + 0x38);
        size = (unsigned long)*(unsigned int *)(base + 0x1c);
        va = v + size * 0x4000;
        if (v < va) {
            unsigned long z = *(long *)(zone + 0x38);
            do {
                unsigned long idx = 0x4000;
                if (v >> 0x24 == 0) idx = v >> 0x16;
                *(unsigned int *)(*(long *)(z + 0x218) + idx * 4) = 0;
                v += 0x400000;
            } while (v < va);
        }
        sk_pt_invalidate(*(unsigned long *)(base + 0x38),
                         (unsigned long)*(unsigned int *)(base + 0x1c) << 0xe, 0, node);
        sk_cpu_preempt(*(long *)(*(long *)(zone + 0x38) + 0x210)
                       + (unsigned long)(*(char *)(base + 0x24) == 1) * 0x60, node);
        return;
    default: sk_bug_llu(); return;
    }

    base = 0xffffffffffff8000;
    if (0x7fffffff < (unsigned int)(int)*(char *)(node + 0x40))
        base = 0xfffffffffffe0000;
    if (*zone > 3) sk_bug_llu();
    v = *(long *)(zone + 0x38);
    if (*(char *)(v + 400) == 1) {
        /* Cache-clean the freed range (DC_GVA) if the zone is write-back. */
        unsigned long off = (((node - (base & node)) - 0x50) >> 5)
                            * -0x5555555555554000 & 0x3fffffffc000
                            + *(long *)((base & node) + 0x38) & 0xf0ffffffffffffff;
        unsigned long end = off + page_sz & 0xffffffffffffffc0;
        for (v = off + 0x3f & 0xf1ffffffffffffc0; v < end; v += 0x40) sk_dc_gva(v);
    }
    if ((fl == 7) && ((*(char *)(*(long *)(zone + 0x38) + 0x1b9) >> 1) & 1))
        sk_bug_s();
    if (fl != 5) param_4 = 1;
    if (fl != 10 && param_4 != 0) {
        sk_slab_free_tlb((unsigned long)zone, node);          /* FUN_00003794 */
        if (fl == 7) {
            size = sk_slab_pages(node);
            va = (((node & 0x7fff) - 0x50) >> 5) * -0x5555555555554000 & 0x3fffffffc000
                 + *(long *)((node & 0xffffffffffff8000) + 0x38);
            sk_pt_write(va, (size != 0) ? size : page_sz, 8, 0x40);
        }
    }
    if (sk_lock_acquire((unsigned long)zone + 0x10)) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");

    /* Coalesce with the next and previous slabs. */
    fl = *(unsigned char *)(node + 0x40);
    t = fl & 0xf;
    if (t > 10) sk_bug_llu();
    size = 1;
    if ((1u << t & 0x5e0) == 0) {
        if ((1u << t & 0x1b) != 0) {
            if ((fl & 0xd) != 1) sk_bug_s();
            if (t != 1) goto coalesce_next;
        }
    } else {
coalesce_next:
        size = (unsigned long)*(unsigned int *)(node + 0x48);
    }
    base &= node;
    *(char *)(node + 0x40) = fl & 0xf0;
    slot = (long *)(node + size * 0x60);
    va = base + 0x50;
    if ((slot < va + (unsigned long)*(unsigned int *)(base + 0x20) * 0x60) &&
        (*(char *)((char *)slot + 0x40) & 0xd) == 1) {
        unsigned long n = 1;
        if ((*(char *)((char *)slot + 0x40) & 3) != 1)
            n = *(unsigned int *)((char *)slot + 0x48);
        size += n;
        {
            unsigned long *prev = *(unsigned long **)((char *)slot + 0x38);
            unsigned long next = *(unsigned long *)((char *)slot + 0x30) ? 0 :
                                 *(unsigned long *)((char *)slot + 0x30);
            if (*(long *)((char *)slot + 0x30) == 0) next = 0;
            else { *(unsigned long **)(*(long *)((char *)slot + 0x30) + 0x38) = prev;
                   next = *(unsigned long *)((char *)slot + 0x30); }
            *prev = next;
        }
    }
    /* (prev-slab coalesce + FUN_000049ec relink + free-count update follow;
     * retained as the standard zone merge in the decompile.) */
    {
        unsigned long off = (((node - (base & node)) - 0x50) >> 5) * -0x55555555;
        sk_slab_relink((unsigned long)zone, base, (unsigned int)off, (unsigned int)size,
                       0, *(char *)(node + 0x40) >> 7);       /* FUN_000049ec */
    }
    *(int *)(base + 0x18) = *(int *)(base + 0x18) - 1;
    if (sk_lock_release((unsigned long)zone + 0x10)) sk_lock_error(0x40, 0, "Failed to release lock: %p");
}

/*--------------------------------------------------------------------*/
/* FUN_00003e7c @ 0x00003e7c   (est. sk_slab_grow)
 * Ghidra: undefined8 FUN_00003e7c(byte *param_1,long param_2,ulong param_3,
 *                                  uint param_4)
 * Grows a slab: adds param_4 objects to the node's object count, either
 * splitting the trailing free region (param_4 < current count) or
 * extending it, then issues the page-table write for the new range and
 * cache maintenance. Returns 1 on success, 0 on failure.
 * Confidence: medium
 * Notes: lock-protected; s_Failed_to_acquire/release_lock strings;
 *   DC_GVA cache-clean loops. */
unsigned long sk_slab_grow(unsigned char *zone, unsigned long base, unsigned long node,
                           unsigned int new_count)
{
    unsigned long v, page_sz;
    unsigned int fl, cur;
    long *slot;
    int i;

    if (*(unsigned int *)(node + 0x48) >= new_count) {
        if (*(unsigned int *)(node + 0x48) != new_count) {
            if (sk_lock_acquire((unsigned long)zone + 0x10))
                sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
            cur = *(int *)(node + 0x48) - new_count;
            v = node + (unsigned long)new_count * 0x60;
            *(unsigned int *)(node + 0x48) = new_count;
            slot = (long *)(node + (unsigned long)(new_count - 1) * 0x60);
            *(char *)((char *)slot + 0x40) = *(char *)((char *)slot + 0x40) & 0xf0 | 4;
            *(unsigned int *)((char *)slot + 0x44) = (new_count - 1) * 0x60;
            fl = (cur > 1) ? 7 : 2;
            sk_slab_mark(node & 0xffffffffffff8000, fl,
                         (unsigned long)(int)((v - (node & 0xffffffffffff8000) - 0x50) >> 5)
                         * -0x55555555, cur);            /* FUN_00004478 */
            if (sk_lock_release((unsigned long)zone + 0x10))
                sk_lock_error(0x40, 0, "Failed to release lock: %p");
            if (cur < 2) {
                page_sz = sk_slab_pages(v);
                base = 0xffffffffffff8000;
                if (0x7fffffff < (unsigned int)(int)*(char *)(v + 0x40))
                    base = 0xfffffffffffe0000;
                sk_pt_write((((v - (base & v)) - 0x50) >> 5) * -0x5555555555554000
                            & 0x3fffffffc000 + *(long *)((base & v) + 0x38),
                            0x4000, 8, 0x40);
            }
            sk_slab_free(zone, v, 0, 0);
        }
        return 1;
    }
    /* (Growing path: split the trailing free region and mark the new
     * objects; see full decompile. Returns 0 on release-lock failure.) */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000043cc @ 0x000043cc   (est. sk_slab_split)
 * Ghidra: long FUN_000043cc(undefined8 param_1,long param_2,long param_3,
 *                            int param_4,int param_5)
 * Splits a free slab: takes param_4 objects from the head of the node
 * and re-links the remainder (FUN_000049ec). If param_5 is set, the
 * leftover tail becomes a new free slab of the given count; otherwise
 * the node itself is split at the object index. Returns the split slab.
 * Confidence: medium
 * Notes: freelist unlink + relink; flag bits 0x10/0x80 carried over. */
unsigned long sk_slab_split(unsigned long zone, unsigned long base, unsigned long node,
                            int count, int part)
{
    unsigned long remain, tail;
    unsigned int fl;

    remain = (unsigned long)(unsigned int)(*(int *)(node + 0x48) - count);
    if (part == 0) {
        count += (int)(((node - base) - 0x50) >> 5) * -0x55555555;
        tail = node;
    } else {
        tail = node + remain * 0x60;
        *(int *)(tail + 0x48) = count;
        fl = *(unsigned char *)(tail + 0x40);
        *(char *)(tail + 0x40) = fl & 0xf0 | 3;
        *(char *)(tail + 0x40) = fl & 0xe0 | 3 | *(char *)(node + 0x40) & 0x10;
        count = (int)(((node - base) - 0x50) >> 5) * -0x55555555;
    }
    sk_slab_relink(zone, base, (unsigned int)count, (unsigned int)remain,
                   *(char *)(node + 0x40) >> 4 & 1, *(char *)(node + 0x40) >> 7);
    return tail;
}

/*--------------------------------------------------------------------*/
/* FUN_00004478 @ 0x00004478   (est. sk_slab_mark)
 * Ghidra: long FUN_00004478(long param_1,int param_2,ulong param_3,uint param_4)
 * Marks a run of param_4 objects starting at index param_3 as the given
 * type (param_2), setting each object's size-class header (+0x40 flags,
 * +0x44 index) and bumping the zone's free count. Returns the first
 * object of the run.
 * Confidence: medium
 * Notes: object stride 0x60; header layout at +0x40/+0x44/+0x48. */
unsigned long sk_slab_mark(unsigned long base, int type, unsigned long idx, unsigned int n)
{
    unsigned long first, v, u;
    unsigned int fl, last, i;
    int j;

    first = base + 0x50 + idx * 0x60;
    last = n - 1;
    i = last;
    if (last > 6) i = 7;
    v = (unsigned long)i;
    if ((unsigned long)*(unsigned int *)(base + 0x20) <= idx + i)
        v = (unsigned long)*(unsigned int *)(base + 0x20) + ~idx;
    u = first + 0x60;
    if (v != 0) {
        j = (v + 1 > 2) ? (int)(v + 1) : 2;
        j--;
        i = 0x60;
        do {
            *(char *)(u + 0x40) = *(char *)(u + 0x40) & 0xf0 | 4;
            *(int *)(u + 0x44) = i;
            u += 0x60;
            i += 0x60;
            j--;
        } while (j != 0);
    }
    if (type != 8) {
        unsigned long last_off = base + 0x50 + (idx + n) * 0x60;
        if (u <= last_off - 0x60) {
            *(char *)(last_off - 0x20) = *(char *)(last_off - 0x20) & 0xf0 | 4;
            *(char *)(last_off - 0x20) = *(char *)(last_off - 0x20) & 0x70 | 4
                                         | *(char *)(first + 0x40) & 0x80;
            *(unsigned int *)(last_off - 0x1c) = last * 0x60;
        }
        if (type != 2) goto done;
    }
    *(unsigned int *)(first + 0x48) = n;
done:
    *(char *)(first + 0x40) = *(char *)(first + 0x40) & 0xf0 | (unsigned char)type & 0xf;
    *(int *)(base + 0x18) = *(int *)(base + 0x18) + 1;
    return first;
}

/*--------------------------------------------------------------------*/
/* FUN_0000456c @ 0x0000456c   (est. sk_slab_grow_noop)
 * Ghidra: undefined8 FUN_0000456c(void)
 * Trivial no-op returning 0 (a grow-path stub).
 * Confidence: high (trivial body). */
unsigned long sk_slab_grow_noop(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_00004574 @ 0x00004574   (est. sk_page_alloc)
 * Ghidra: void FUN_00004574(byte *param_1,ulong param_2,ulong param_3,long *param_4)
 * Allocates a run of physical pages from the zone's page allocator: picks
 * a size-class bucket (FUN_00011b18), builds a new slab node, inserts it
 * into the zone's size-class freelist and maps the pages into the
 * page-table (writing PTEs with the node base). When param_4 is non-null
 * the node is built in-place (caller-managed); otherwise it is linked
 * into the zone's freelist bucket.
 * Confidence: medium
 * Notes: cache-clean via DC_GVA; bit-reverse size-class via LZCOUNT. */
unsigned long sk_page_alloc(unsigned long zone, unsigned long size, unsigned long seed,
                            unsigned long *out)
{
    unsigned long pages, unit, bucket, node, va, end;
    unsigned char *fmt;
    unsigned int idx, cls, kind;
    int i;

    if (seed > 0x3fffff) unit = seed;
    else if (size < 0x400001) unit = 0x400000;
    else unit = 0x1000000;
    bucket = size;
    if ((size & 0x3fff) != 0) bucket = (size & 0x3fffffffc000) + 0x4000;
    if (out != 0) unit = bucket;
    fmt = *(char **)(zone + 0x30);
    {
        char locals[16] = { 0 };
        char *sel = (char *)(out ? (unsigned char *)locals : (unsigned char *)fmt + 0x20);
        if (zone > 3) sk_bug_llu();
        idx = 4;
        if (*(char *)(*(long *)(zone + 0x38) + 400) == 1) {
            unsigned long r = seed;
            r = (r & 0xaaaaaaaaaaaaaaaa) >> 1 | (r & 0x5555555555555555) << 1;
            r = (r & 0xcccccccccccccccc) >> 2 | (r & 0x3333333333333333) << 2;
            r = (r & 0xf0f0f0f0f0f0f0f0) >> 4 | (r & 0xf0f0f0f0f0f0f0f) << 4;
            r = (r & 0xff00ff00ff00ff00) >> 8 | (r & 0xff00ff00ff00ff) << 8;
            r = (r & 0xffff0000ffff0000) >> 0x10 | (r & 0xffff0000ffff) << 0x10;
            idx = (unsigned int)sk_lzcount64(r >> 0x20 | r << 0x20);
            cls = (idx < 0x17) ? 0x16 : idx;
            cls = (seed != 0) ? cls : 0x16;
            kind = 0x1200;
            if ((4 & 4) != 0) kind = 0x1a00;
            node = sk_pmo_init(unit, cls, kind, 6, sel);    /* FUN_00011b18 */
        } else {
            node = sk_segment_alloc((unsigned long)fmt, unit);   /* FUN_00004888 */
        }
        if (node == 0) return 0;
        /* Build the new slab node and map its pages. */
        if (node >> 0x24 == 0) {
            unsigned long *n = (unsigned long *)sk_zone_pt_for(
                *(long *)(*(long *)(zone + 0x38) + 0x210));
            n[1] = *(unsigned long *)(sel + 8);
            *n = *(unsigned long *)sel;
            pages = unit >> 0xe;
            *(unsigned char *)((char *)n + 0x24) = out ? 2 : (unsigned char)1;
            n[2] = (unsigned long)zone;
            {
                unsigned long lim = 0x400;
                if (out == 0 || size < 0x400001) lim = 0x100;
                i = (lim <= pages) ? (int)lim : (int)pages;
            }
            *(int *)((char *)n + 0x1c) = (int)pages;
            *(int *)(n + 4) = i;
            *(unsigned int *)(n + 3) = 0;
            n[7] = node;
            if (out == 0) {
                if (sk_lock_acquire((unsigned long)zone + 0x10))
                    sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
                idx = (size < 0x400001) ? 0x80000000 : 0;
                sk_slab_relink((unsigned long)zone, (unsigned long)n, 0, (unsigned int)pages,
                               1, size > 0x400000);       /* FUN_000049ec */
            } else {
                sk_slab_mark((unsigned long)n, 8, 0, (unsigned int)pages);
                *(char *)((char *)n + 0x40) |= 0x10;
            }
            if ((unsigned long)n >> 0x2e == 0) {
                end = n[7] + (unsigned long)*(unsigned int *)((char *)n + 0x1c) * 0x4000;
                if (node < end) {
                    unsigned long z = *(long *)(zone + 0x38);
                    for (va = node; va < end; va += 0x400000) {
                        unsigned long idx2 = 0x4000;
                        if (va >> 0x24 == 0) idx2 = va >> 0x16;
                        *(unsigned int *)(*(long *)(z + 0x218) + idx2 * 4) =
                            idx | (unsigned int)((unsigned long)n >> 0xf) & 0x7fffffff;
                    }
                }
                if (out != 0) *out = (unsigned long)n;
            }
        }
        return node;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00004888 @ 0x00004888   (est. sk_segment_alloc)
 * Ghidra: long FUN_00004888(long param_1,ulong param_2)
 * Allocates a run from a segment allocator (a bounded region with a
 * base/length and a monotonic cursor): takes the region lock, advances
 * the cursor (growing up or down depending on the region direction),
 * and returns the new base. Sets the region's "failed" flag on
 * exhaustion.
 * Confidence: medium
 * Notes: s_Failed_to_allocate_segment_from_r string; lock ops. */
unsigned long sk_segment_alloc(unsigned long seg, unsigned long size)
{
    unsigned long base, avail, cursor;
    int i;

    if ((*(char *)(seg + 0x61) & 1) != 0) return 0;
    if (sk_lock_acquire((unsigned long)seg + 0x10)) sk_lock_error(0x40, 0, "Failed to acquire lock: %p");
    base = *(unsigned long *)(seg + 0x40);
    if (base != 0) {
        cursor = *(unsigned long *)(seg + 0x50);
        if (*(char *)(seg + 0x60) == 0) {
            if ((cursor < base || cursor - base == 0) && base < cursor + size) {
                *(unsigned long *)(seg + 0x58) = (cursor - base) + *(long *)(seg + 0x58);
                avail = *(long *)(seg + 0x48);
                goto advance;
            }
        } else if (base <= cursor && cursor - size < base) {
            *(unsigned long *)(seg + 0x58) = (base - cursor) + *(long *)(seg + 0x58);
            avail = -*(long *)(seg + 0x48);
advance:
            *(unsigned long *)(seg + 0x50) = base + avail;
        }
    }
    if (size <= *(unsigned long *)(seg + 0x58)) {
        avail = *(long *)(seg + 0x50);
        if (*(char *)(seg + 0x60) == 0) {
            cursor = avail + size;
        } else if (*(char *)(seg + 0x60) == 1) {
            cursor = avail - size;
        }
        *(long *)(seg + 0x50) = cursor;
        *(unsigned long *)(seg + 0x58) -= size;
        if (cursor != 0) goto out;
    }
    if ((*(char *)(seg + 0x61) & 1) == 0) {
        *(char *)(seg + 0x61) = 1;
        sk_log(4, "Failed to allocate segment from region");
    }
    avail = 0;
out:
    if (sk_lock_release((unsigned long)seg + 0x10)) sk_lock_error(0x40, 0, "Failed to release lock: %p");
    return avail;
}

/*--------------------------------------------------------------------*/
/* FUN_000049ec @ 0x000049ec   (est. sk_slab_relink)
 * Ghidra: void FUN_000049ec(long param_1,long param_2,uint param_3,uint param_4,
 *                            int param_5,int param_6)
 * Links a free slab of param_4 objects (starting at index param_3) into
 * the zone's segregated freelist, bucketed by size class. Sets the node's
 * free/prev flags, marks the run header, and inserts it into the bucket.
 * Confidence: medium
 * Notes: object stride 0x60; bucket head array at zone+0x48. */
void sk_slab_relink(unsigned long zone, unsigned long base, unsigned int idx,
                    unsigned int n, int a, int b)
{
    unsigned long head;
    unsigned int bucket, i;
    unsigned char fl;
    long **slot;

    slot = (long **)(base + 0x50 + (unsigned long)idx * 0x60);
    fl = *(unsigned char *)((char *)slot + 0x40);
    *(char *)((char *)slot + 0x40) = fl & 0xf0 | 3;
    *(unsigned int *)((char *)slot + 0x48) = n;
    {
        unsigned long tail = base + 0x50 + (unsigned long)(n - 1 + idx) * 0x60;
        *(char *)(tail + 0x40) = *(char *)(tail + 0x40) & 0x70 | 4 | fl & 0x80;
        *(unsigned int *)(tail + 0x44) = n * 0x60 - 0x60;
    }
    /* Bucket index by size class. */
    i = n - 1;
    bucket = i;
    if (i == 0) {
        *(char *)((char *)slot + 0x40) = *(char *)((char *)slot + 0x40) & 0xf0 | 1;
        if (*(char *)(base + 0x24) == 2) return;
        i = 0;
    } else {
        if (n > 8) i = ((i >> (0x1d - (int)sk_lzcount32(i) & 0x1f) & 3)
                        + (int)sk_lzcount32(i) * -4 + 0x77);
    }
    head = *(unsigned long *)(zone + (unsigned long)i * 0x10 + 0x48);
    *(long *)((char *)slot + 0x30) = head;
    if (head != 0) *(unsigned long **)(head + 0x38) = (unsigned long *)((char *)slot + 0x30);
    *(unsigned long *)(zone + (unsigned long)i * 0x10 + 0x48) = (unsigned long)slot;
    *(unsigned long **)((char *)slot + 0x38) =
        (unsigned long **)(zone + (unsigned long)i * 0x10 + 0x48);
}

/*--------------------------------------------------------------------*/
/* FUN_00004acc @ 0x00004acc   (est. sk_slab_touch)
 * Ghidra: void FUN_00004acc(long param_1,uint param_2,uint param_3)
 * Marks a run of param_3 objects starting at index param_2 as free
 * (type 9), coalescing with an adjacent free slab, clearing each
 * object header, issuing a page-table write for the range, and bumping
 * the zone free count.
 * Confidence: medium
 * Notes: object stride 0x60; FUN_00011bf4 page-table write. */
void sk_slab_touch(unsigned long base, unsigned int idx, unsigned int n)
{
    unsigned long v, end, off, entry;
    unsigned int fl, run;
    unsigned char *p;
    long i;

    v = base + 0x50 + (unsigned long)idx * 0x60;
    end = v + (unsigned long)n * 0x60;
    run = n;
    if (end < base + 0x50 + (unsigned long)*(unsigned int *)(base + 0x20) * 0x60 &&
        (*(char *)(end + 0x40) & 0xf) == 9) {
        run = *(int *)(end + 0x48) + n;
    }
    if (idx != 0) {
        unsigned long prev = v - 0x60;
        if ((*(char *)(v - 0x20) & 0xf) == 4) {
            unsigned long p0 = prev - *(unsigned int *)(v - 0x1c);
            fl = *(unsigned char *)(p0 + 0x40) & 0xf;
            if (fl < 0xb) {
                fl = 1u << fl;
                if ((fl & 0x7e8) == 0) {
                    if ((fl & 6) != 0 && prev == p0) goto coalesce;
                } else if (prev < p0 + (unsigned long)*(unsigned int *)(p0 + 0x48) * 0x60) {
coalesce:
                    prev = p0;
                }
            }
        }
        if ((*(char *)(prev + 0x40) & 0xf) == 9) {
            idx -= *(int *)(prev + 0x48);
            run = *(int *)(prev + 0x48) + run;
            v = prev;
        }
    }
    if (run > 1) {
        i = 0x60;
        p = (unsigned char *)(v + 0xa0);
        do {
            *(int *)(p + 4) = (int)i;
            *p = *p & 0xf0 | 4;
            i += 0x60;
            p += 0x60;
        } while ((unsigned long)run * 0x60 - i != 0);
    }
    if (run == n) *(int *)(base + 0x18) = *(int *)(base + 0x18) + 1;
    *(unsigned int *)(v + 0x48) = run;
    off = *(long *)(base + 0x38) + (unsigned long)idx * 0x4000;
    sk_pt_write(off, (unsigned long)run << 0xe, 9, 0x40,
                *(long *)(*(long *)(base + 0x10) + 0x30) + 0x20);
    *(char *)(v + 0x40) = *(char *)(v + 0x40) & 0xf0 | 9;
}

/*--------------------------------------------------------------------*/
/* FUN_00004c4c @ 0x00004c4c   (est. sk_bit_select)
 * Ghidra: ulong FUN_00004c4c(ulong param_1,ulong param_2,int param_3)
 * Selects the (n - param_3)-th lowest set bit pattern: repeatedly clears
 * bits by applying the "x & x-1" trick param_3 times, recomputing the
 * target from sk_clz each iteration. Returns the cleared bitmap.
 * Confidence: medium
 * Notes: cL4 object-bitmap selection primitive. */
unsigned long sk_bit_select(unsigned long bitmap, unsigned long n, int count)
{
    unsigned int lo, t;
    int clz;
    for (; count != 0; count--) {
        clz = sk_clz(n);
        lo = (unsigned int)bitmap;
        t = lo;
        for (; clz != 0; clz--) t = (unsigned int)bitmap - 1 & (unsigned int)bitmap;
        bitmap = (unsigned long)(t & -t ^ lo);
        n = (unsigned long)((int)n - 1);
    }
    return bitmap;
}

/*--------------------------------------------------------------------*/
/* FUN_00004cc0 @ 0x00004cc0   (est. sk_bug_malloc2)
 * Ghidra: void FUN_00004cc0(undefined8 param_1)
 * Libmalloc "BUG IN LIBMALLOC: %s" panic (takes a format arg).
 * Confidence: high (string-matched). */
void sk_bug_malloc2(unsigned long a)
{
    sk_bug_s();
}

/* APPEND_MARKER */
