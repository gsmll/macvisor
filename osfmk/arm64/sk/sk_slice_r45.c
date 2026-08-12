/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 Secure Kernel / GL1, arm64e,
 * image base 0) — Apple's seL4-derived microkernel. Ground truth: Ghidra
 * FUN_ names + addresses; seL4/cL4 vocabulary. All names are estimates unless
 * header/string-matched. Confidence recorded per function. */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* =====================================================================
 * Shared extern helpers (called by functions in this slice).
 * Address in comment = Ghidra FUN_ address of the real callee.
 * ===================================================================== */

/* ---- noreturn panic / assert printers ---- */
extern void sk_fatal_msg(const char *msg);                        /* FUN_00118b28 */
extern void sk_assert_panic(const char *msg);                     /* FUN_004afae4 */
extern void sk_security_assert(const char *msg);                  /* FUN_001150e0 */
extern void sk_panic_4(const char *a, const char *b, const char *c,
                       unsigned long d);                          /* FUN_00115424 */
extern void sk_stack_check_fail(void);                            /* FUN_0011d7e8 */
extern void sk_reboot(void);                                      /* FUN_00116d60 noreturn */
extern unsigned long sk_raise_bad(unsigned long a, unsigned long b); /* FUN_000101a0 (returns a ref/status) */
extern void SoftwareBreakpoint(unsigned long code, unsigned long addr);

/* ---- cL4 printf/log chain ---- */
extern void sk_log_start(unsigned long v, const char *fmt);       /* FUN_001185ec */
extern void sk_log_append(unsigned long key, const char *fmt, void *ctx); /* FUN_00118c38 */
extern void sk_log_end(unsigned long level, unsigned long key);   /* FUN_001187f4 */
extern void sk_log_fixed(const char *fmt, ...);                   /* FUN_00118abc (fixed-string log line; args vary) */
extern void sk_log_push(unsigned long key, unsigned long tag);    /* FUN_0011883c */
extern void sk_log_begin(unsigned long tag);                      /* FUN_0011858c */

/* ---- list context save/restore ---- */
extern void sk_list_ctx_save(void);                               /* FUN_0006d870 */
extern void sk_list_ctx_restore(void);                            /* FUN_0006d890 */

/* ---- panic-context trailer reporter (defined in slice r44) ---- */
extern void sk_panic_report_context10(unsigned long v);           /* FUN_004b80c8 */

/* ---- memory helpers ---- */
extern void sk_memcpy_n(void *dst, const void *src, unsigned long n); /* FUN_00117cc4 / FUN_00117cc8 */
extern void sk_memset_n(void *dst, unsigned long val, unsigned long n,
                        unsigned long size);                      /* FUN_00117d68 */
extern void sk_refcount_retain(void *obj, unsigned long n);       /* FUN_00104988 */
extern void sk_refcount_release(unsigned long n, void *obj);      /* FUN_00104f9c */
extern unsigned long sk_hash_combine(void *a, unsigned long b, void *c,
                                     unsigned long d, void *e, void *f); /* FUN_00104254 */
extern int sk_hash_compare(unsigned long n, void *a, void *b);    /* FUN_00104180 */
extern void sk_hash_abort(unsigned long n);                       /* FUN_00103dfc */

/* ---- lock / irq primitives ---- */
extern int sk_lck_acquire(unsigned long addr);                    /* FUN_00118164 */
extern void sk_lck_wait(unsigned long addr, unsigned long lock);  /* FUN_0011812c */
extern int sk_lck_release(void);                                  /* FUN_00118194 */
extern int sk_lck_broadcast(unsigned long addr);                  /* FUN_001180e0 */
extern void sk_irq_save(void);                                    /* FUN_00111848 */
extern void sk_irq_restore(void);                                 /* FUN_00111838 */

/* ---- StackshotConclaveSupport context helpers ---- */
extern void sk_stackshot_ctx_set(unsigned long v, unsigned long n); /* FUN_00046304 */
extern unsigned long sk_stackshot_ctx_get(void);                  /* FUN_0016fb80 */
extern void sk_ctx_save_restore(void *ctx, ...);                  /* FUN_0016fa6c (ctx save / restore; arg count varies) */
extern void sk_ctx_restore2(unsigned long a, unsigned long b);    /* FUN_0016f9c0 */

/* ---- StackshotDelegate fatal-trap printers ---- */
extern void sk_delegate_msg_a(const char *msg);                   /* FUN_001724cc */
extern void sk_delegate_msg_b(const char *msg);                   /* FUN_001724bc */
extern void sk_delegate_nomsg_a(void);                            /* FUN_0017244c */
extern void sk_delegate_nomsg_b(void);                            /* FUN_00172484 */
extern void sk_delegate_nomsg_c(void);                            /* FUN_001724a0 */
extern void sk_delegate_nomsg_d(void);                            /* FUN_00172468 */
extern void sk_delegate_report_a(const char *msg);                /* FUN_0004b488 */
extern void sk_delegate_report_b(const char *msg);                /* FUN_0004b478 */
extern void sk_buildroot_panic_a(const char *msg);                /* FUN_000179d8 */
extern void sk_buildroot_panic_b(const char *msg);                /* FUN_00015e2c */

/* ---- Swift runtime metadata / fatal type-init helpers ---- */
extern void sk_swift_runtime_enter(void);                         /* FUN_00359434 */
extern void sk_swift_set_runtime_enter(void);                     /* FUN_0036a9a0 */
extern unsigned long sk_swift_meta_get(unsigned long a, ...);     /* FUN_0035310c */
extern void sk_swift_meta_set(unsigned long v, unsigned int a, unsigned short b); /* FUN_0036a940 */
extern void sk_swift_type_fatal(unsigned long a, ...);            /* FUN_001b11bc (Swift type-descriptor fatal; args vary) */
extern void sk_meta_decode_begin(void);                           /* FUN_00361308 */
extern void sk_meta_decode_dispatch(void);                        /* FUN_003612f0 */
extern void sk_swift_box_init(void *buf, ...);                    /* FUN_00361320 (tagged box init) */
extern int sk_swift_is_conditional(void);                         /* FUN_0000456c */
extern void sk_swift_box_release(void *p);                        /* FUN_00368298 */
extern void sk_swift_fatal(unsigned long a, ...);                 /* FUN_00369bb0 noreturn */
extern void sk_swift_dealloc(unsigned long p);                    /* FUN_0035bd48 */
extern void thunk_FUN_00012568(unsigned long a, ...);             /* FUN_00012568 thunk (release; arg count varies) */

/* ---- backtrace / stackshot registry ---- */
extern void sk_backtrace_frame(void *frame);                      /* FUN_00369d48 */
extern void sk_stackshot_registry_pop(void *p);                   /* FUN_00369ca0 */
extern unsigned long sk_stackshot_registry_get(unsigned long key);/* FUN_00118cf8 */
extern unsigned long sk_stackshot_state_store(unsigned long v, unsigned long tag); /* FUN_0039c740 */
extern unsigned long sk_prespecializations_get(void);             /* FUN_0036e51c */
extern void sk_lock_pool_refill(void);                            /* FUN_0035b644 */
extern int sk_sys_object_lookup(unsigned long a, unsigned long b,
                                unsigned long c, unsigned long d); /* FUN_00116bb4 */

/* ---- globals referenced by bodies ---- */
extern unsigned long _DAT_006c0250;
extern unsigned long _DAT_006c0270;
extern unsigned long _DAT_006c0280;
extern unsigned long _DAT_006adf08;
extern long lRam0000000000657738;   /* global at 0x657738 */

/* ---- forward declarations (bodies appear later in address order) ---- */
static void sk_crypto_fail_reboot(unsigned long msg);             /* FUN_004b856c */
static void sk_mutex_fail_reboot(const char *msg);                /* FUN_004b89f8 */
static void sk_stackshot_key_begin(unsigned long key);            /* FUN_004b9df8 */
static unsigned long sk_swift_meta_dispatch(unsigned long cb); /* FUN_004b92b8 */
static void sk_meta_decode_sub(unsigned long out, unsigned long *stream,
                               long *offset, unsigned long base);   /* FUN_004b9634 */
static void sk_meta_decode_slot(unsigned long out, unsigned long *stream,
                                long *offset, unsigned long a, unsigned long b); /* FUN_004b992c */
static void sk_swift_sequence_box_fatal(void);                 /* FUN_004b92ec */
static void sk_swift_collection_box_pre(void);                 /* FUN_004b9418 */
static void sk_swift_randomaccess_collection_fatal(void);      /* FUN_004b9448 */
static void sk_swift_native_nsarray_fatal(void);               /* FUN_004b94e8 */
static void sk_swift_meta_set_from_stream(void);               /* FUN_0036a940() helper */
static void sk_stackshot_obj_enter(unsigned long a, unsigned long b,
                                   unsigned long c);           /* FUN_004b9e2c */
static void sk_stackshot_obj_enter2(unsigned long a);          /* FUN_004b9ed8 */

/* =====================================================================
 * Function bodies (address order).
 * ===================================================================== */

/* FUN_004b8238 @ 0x004b8238  (est. sk_panic_unexpected_l4_error)
 * Ghidra: void FUN_004b8238(void)
 * Unexpected L4 Error fatal: saves/restores the list context, prints the
 * panic-context trailer, then panics with the generic "Unexpected L4 Error"
 * message. Does not return. Confidence: high (string-matched) */
static void sk_panic_unexpected_l4_error(void)
{
    sk_list_ctx_save();
    sk_panic_report_context10(0);    /* FUN_004b80c8 (slice r44) */
    sk_list_ctx_restore();
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005bf810 */
}

/* FUN_004b8288 @ 0x004b8288  (est. sk_boot_untyped_region_count_panic)
 * Ghidra: void FUN_004b8288(void)
 * Boot fatal: "unt_idx < MAX_UNTYPED_REGIONS" asserted in boot_untyped_parse
 * (line 0x111). Does not return. Confidence: high (string-matched) */
static void sk_boot_untyped_region_count_panic(void)
{
    sk_panic_4("unt_idx < MAX_UNTYPED_REGIONS",   /* s__unt_idx_<__MAX_UNTYPED_REGIONS_005bf51c */
               "AppleInternal Library BuildRoot",
               "boot_untyped_parse", 0x111);      /* s__boot_untyped_parse_005bf53c */
}

/* FUN_004b82b4 @ 0x004b82b4  (est. sk_boot_irq_get_panic)
 * Ghidra: void FUN_004b82b4(void)
 * Boot fatal: L4 BootInfo Irq GetIrq_entry index < MAX_IRQ asserted in
 * boot_irq_parse (line 0x1c0). Does not return.
 * Confidence: high (string-matched) */
static void sk_boot_irq_get_panic(void)
{
    sk_panic_4("L4 BootInfo Irq GetIrq_entry < MAX_IRQ",  /* s_L4_BootInfo_Irq_GetIrq_entry__<_M_005bf900 */
               "AppleInternal Library BuildRoot",
               "boot_irq_parse", 0x1c0);           /* s__boot_irq_parse_005bf928 */
}

/* FUN_004b82e0 @ 0x004b82e0  (est. sk_boot_dart_pagetable_parse_panic)
 * Ghidra: void FUN_004b82e0(void)
 * Boot fatal: "boot_info_ndart_tables < MAX_DARTS" asserted in
 * boot_dart_pagetable_parse (line 0xe2). Does not return.
 * Confidence: high (string-matched) */
static void sk_boot_dart_pagetable_parse_panic(void)
{
    sk_panic_4("boot_info_ndart_tables < MAX_DARTS",  /* s__boot_info_ndart_tables_<_MAX_DA_005bf993 */
               "AppleInternal Library BuildRoot",
               "boot_dart_pagetable_parse", 0xe2);   /* s__boot_dart_pagetable_parse_005bf9b7 */
}

/* FUN_004b830c @ 0x004b830c  (est. sk_boot_dart_parse_panic)
 * Ghidra: void FUN_004b830c(void)
 * Boot fatal: "boot_info_ndarts < MAX_DARTS" asserted in boot_dart_parse
 * (line 0xd3). Does not return. Confidence: high (string-matched) */
static void sk_boot_dart_parse_panic(void)
{
    sk_panic_4("boot_info_ndarts < MAX_DARTS",     /* s__boot_info_ndarts_<_MAX_DARTS_005bf938 */
               "AppleInternal Library BuildRoot",
               "boot_dart_parse", 0xd3);           /* s__boot_dart_parse_005bf956 */
}

/* FUN_004b8338 @ 0x004b8338  (est. sk_parse_self_macho_segments_panic)
 * Ghidra: void FUN_004b8338(void)
 * Boot fatal: "text_segment == NULL && data_seg..." invariant in
 * parse_self_macho (line 0xa2). Does not return.
 * Confidence: high (string-matched) */
static void sk_parse_self_macho_segments_panic(void)
{
    sk_panic_4("text_segment == NULL && data_seg != NULL",  /* s_text_segment____NULL____data_seg_005bf8d3 */
               "AppleInternal Library BuildRoot",
               "parse_self_macho", 0xa2);          /* s_parse_self_macho_005bf8c2 */
}

/* FUN_004b8364 @ 0x004b8364  (est. sk_parse_self_macho_image_panic)
 * Ghidra: void FUN_004b8364(void)
 * Boot fatal: "image == image->header || image..." invariant in
 * parse_self_macho (line 0x9a). Does not return.
 * Confidence: high (string-matched) */
static void sk_parse_self_macho_image_panic(void)
{
    sk_panic_4("image == image->header || image == NULL",  /* s_image____image_>header_____image_005bf89b */
               "AppleInternal Library BuildRoot",
               "parse_self_macho", 0x9a);          /* s_parse_self_macho_005bf8c2 */
}

/* FUN_004b8390 @ 0x004b8390  (est. sk_boot_untyped_finalize_panic)
 * Ghidra: void FUN_004b8390(void)
 * Boot fatal: "unt_idx < MAX_UNTYPED_REGIONS" asserted in boot_untyped_finalize
 * (line 0x1a5). Does not return. Confidence: high (string-matched) */
static void sk_boot_untyped_finalize_panic(void)
{
    sk_panic_4("unt_idx < MAX_UNTYPED_REGIONS",    /* s__unt_idx_<___MAX_UNTYPED_REGIONS_005bf87a */
               "AppleInternal Library BuildRoot",
               "boot_untyped_finalize", 0x1a5);    /* s__boot_untyped_finalize_005bf863 */
}

/* FUN_004b83bc @ 0x004b83bc  (est. sk_cbinfo_managed_untyped_panic)
 * Ghidra: void FUN_004b83bc(void)
 * Boot fatal: "UNTYPED_MANAGED < MAX_UNTYPED_RE..." asserted in
 * cbinfo_get_managed_untyped_pbase (line 0x2d6). Does not return.
 * Confidence: high (string-matched) */
static void sk_cbinfo_managed_untyped_panic(void)
{
    sk_panic_4("UNTYPED_MANAGED < MAX_UNTYPED_REGIONS",  /* s_UNTYPED_MANAGED_<_MAX_UNTYPED_RE_005bf295 */
               "AppleInternal Library BuildRoot",
               "cbinfo_get_managed_untyped_pbase", 0x2d6);  /* s_cbinfo_get_managed_untyped_pbase_005bf3ab */
}

/* FUN_004b83e8 @ 0x004b83e8  (est. sk_cbinfo_alloc_mngd_granular_panic)
 * Ghidra: void FUN_004b83e8(void)
 * Boot fatal: "size % UNTYPED_ALLOC_GRANULAR == 0" asserted in
 * cbinfo_alloc_mngd_phys (line 0x31e). Does not return.
 * Confidence: high (string-matched) */
static void sk_cbinfo_alloc_mngd_granular_panic(void)
{
    sk_panic_4("size % UNTYPED_ALLOC_GRANULAR == 0",  /* s__size___UNTYPED_ALLOC_GRANULAR____005bf404 */
               "AppleInternal Library BuildRoot",
               "cbinfo_alloc_mngd_phys", 0x31e);      /* s_cbinfo_alloc_mngd_phys_005bf429 */
}

/* FUN_004b8414 @ 0x004b8414  (est. sk_cbinfo_alloc_mngd_regions_panic)
 * Ghidra: void FUN_004b8414(void)
 * Boot fatal: "boot_info_untyped_regions UNTY..." asserted in
 * cbinfo_alloc_mngd_phys (line 0x34c). Does not return.
 * Confidence: high (string-matched) */
static void sk_cbinfo_alloc_mngd_regions_panic(void)
{
    sk_panic_4("boot_info_untyped_regions UNTY...",  /* s___boot_info_untyped_regions_UNTY_005bf440 */
               "AppleInternal Library BuildRoot",
               "cbinfo_alloc_mngd_phys", 0x34c);      /* s_cbinfo_alloc_mngd_phys_005bf429 */
}

/* FUN_004b8440 @ 0x004b8440  (est. sk_cbinfo_alloc_mngd_resoff_panic)
 * Ghidra: void FUN_004b8440(void)
 * Boot fatal: "res_off % UNTYPED_ALLOC_GRANULA..." asserted in
 * cbinfo_alloc_mngd_phys (line 0x35d). Does not return.
 * Confidence: high (string-matched) */
static void sk_cbinfo_alloc_mngd_resoff_panic(void)
{
    sk_panic_4("res_off % UNTYPED_ALLOC_GRANULA...",  /* s__res_off___UNTYPED_ALLOC_GRANULA_005bf49a */
               "AppleInternal Library BuildRoot",
               "cbinfo_alloc_mngd_phys", 0x35d);      /* s_cbinfo_alloc_mngd_phys_005bf429 */
}

/* FUN_004b846c @ 0x004b846c  (est. sk_cbinfo_alloc_mngd_regions2_panic)
 * Ghidra: void FUN_004b846c(void)
 * Boot fatal: "boot_info_untyped_regions UNTY..." asserted in
 * cbinfo_alloc_mngd_phys (line 0x365, same string as 0x414). Does not return.
 * Confidence: high (string-matched) */
static void sk_cbinfo_alloc_mngd_regions2_panic(void)
{
    sk_panic_4("boot_info_untyped_regions UNTY...",  /* s___boot_info_untyped_regions_UNTY_005bf440 */
               "AppleInternal Library BuildRoot",
               "cbinfo_alloc_mngd_phys", 0x365);      /* s_cbinfo_alloc_mngd_phys_005bf429 */
}

/* FUN_004b8498 @ 0x004b8498  (est. sk_cbinfo_get_irq_cap_panic)
 * Ghidra: void FUN_004b8498(void)
 * Boot fatal: "irq < MAX_IRQ" asserted in cbinfo_get_irq_cap (line 0x3da).
 * Does not return. Confidence: high (string-matched) */
static void sk_cbinfo_get_irq_cap_panic(void)
{
    sk_panic_4("irq < MAX_IRQ",                     /* s_irq_<_MAX_IRQ_005bf4c2 */
               "AppleInternal Library BuildRoot",
               "cbinfo_get_irq_cap", 0x3da);        /* s_cbinfo_get_irq_cap_005bf4d0 */
}

/* ---- ccrypto init-failure reboot wrappers ---- */

/* FUN_004b856c @ 0x004b856c  (est. sk_crypto_fail_reboot)
 * Ghidra: void FUN_004b856c(undefined8 param_1)
 * Common crypto-init failure sink: takes a failure-message pointer (unused
 * here) and reboots. Does not return. Confidence: low */
static void sk_crypto_fail_reboot(unsigned long msg)
{
    (void)msg;
    sk_reboot();   /* FUN_00116d60 */
}

/* FUN_004b84c4 @ 0x004b84c4  (est. sk_ccrng_init_expected_panic)
 * Ghidra: void FUN_004b84c4(void)
 * ccrng init failure: "ccrng_exclavecore_rng_init: expected..." then reboot.
 * Does not return. Confidence: high (string-matched) */
static void sk_ccrng_init_expected_panic(void)
{
    sk_crypto_fail_reboot((unsigned long)"ccrng_exclavecore_rng_init: expected...");  /* s_ccrng_exclavecore_rng_init__expe_005c6cef */
}

/* FUN_004b84dc @ 0x004b84dc  (est. sk_ccrng_init_interrupted_panic)
 * Ghidra: void FUN_004b84dc(void)
 * ccrng init failure: "ccrng_exclavecore_rng_init interrupted" then reboot.
 * Does not return. Confidence: high (string-matched) */
static void sk_ccrng_init_interrupted_panic(void)
{
    sk_crypto_fail_reboot((unsigned long)"ccrng_exclavecore_rng_init interrupted");  /* s_ccrng_exclavecore_rng_init_inter_005c6cc5 */
}

/* FUN_004b84f4 @ 0x004b84f4  (est. sk_ccdrbg_init_panic)
 * Ghidra: void FUN_004b84f4(void)
 * ccdrbg init failure: "ccdrbg_init" then reboot. Does not return.
 * Confidence: high (string-matched) */
static void sk_ccdrbg_init_panic(void)
{
    sk_crypto_fail_reboot((unsigned long)"ccdrbg_init");  /* s_ccdrbg_init___005c6d7f */
}

/* FUN_004b850c @ 0x004b850c  (est. sk_cc_lock_init_panic)
 * Ghidra: void FUN_004b850c(void)
 * cc_lock init failure: "cc_lock_init" then reboot. Does not return.
 * Confidence: high (string-matched) */
static void sk_cc_lock_init_panic(void)
{
    sk_crypto_fail_reboot((unsigned long)"cc_lock_init");  /* s_cc_lock_init___005c6da8 */
}

/* FUN_004b8524 @ 0x004b8524  (est. sk_ccrng_crypto_init_panic)
 * Ghidra: void FUN_004b8524(void)
 * ccrypto init failure: "ccrng_crypto_init" then reboot. Does not return.
 * Confidence: high (string-matched) */
static void sk_ccrng_crypto_init_panic(void)
{
    sk_crypto_fail_reboot((unsigned long)"ccrng_crypto_init");  /* s_ccrng_crypto_init___005c6db7 */
}

/* FUN_004b853c @ 0x004b853c  (est. sk_ccdrbg_entropy_panic)
 * Ghidra: void FUN_004b853c(void)
 * ccdrbg init failure: "Not enough input entropy (ccdrbg...)" then reboot.
 * Does not return. Confidence: high (string-matched) */
static void sk_ccdrbg_entropy_panic(void)
{
    sk_crypto_fail_reboot((unsigned long)"Not enough input entropy (ccdrbg...)");  /* s_Not_enough_input_entropy__ccdrbg_005c6d3b */
}

/* FUN_004b8554 @ 0x004b8554  (est. sk_ccrng_already_init_panic)
 * Ghidra: void FUN_004b8554(void)
 * ccrng init failure: "RNG already initialized" then reboot. Does not return.
 * Confidence: high (string-matched) */
static void sk_ccrng_already_init_panic(void)
{
    sk_crypto_fail_reboot((unsigned long)"RNG already initialized");  /* s_RNG_already_initialized_005c6d23 */
}

/* FUN_004b8590 @ 0x004b8590  (est. sk_slot_frames_init)
 * Ghidra: undefined8 FUN_004b8590(undefined8 *param_1, undefined8 param_2,
 *                        long param_3, ulong param_4)  [uses in_x6]
 * Initializes a 0x41-entry region header: given a size in *slot, validates it
 * against an unbound in_x6 limit, zeroes a buffer slot, sets its tag, marks
 * slot[0x88] occupied, and returns status. Returns 0 on success, 0xffffffc1
 * on a limit violation.
 * Confidence: low (in_x6 input register unavailable) */
static unsigned long sk_slot_frames_init(unsigned long *slot, unsigned long ret,
                                         long buf, unsigned long limit,
                                         unsigned long in_x6)
{
    unsigned long size = *slot;
    if (size < 0x41) {
        if (in_x6 < 0x10001 && (size >> 1) <= limit) {
            sk_memset_n((void *)(buf + 8), 0, size, 0x40);       /* FUN_00117d68(buf+8,0,size,0x40) */
            sk_memset_n((void *)(buf + 0x48), 1, size, 0x40);    /* FUN_00117d68(buf+0x48,1,size,0x40) */
            sk_refcount_retain((void *)buf, 3);        /* FUN_00104988(buf,3) */
            ret = 0;
            *(unsigned long *)(buf + 0x88) = 1;
        } else {
            ret = 0xffffffc1;
        }
    }
    return ret;
}

/* FUN_004b8668 @ 0x004b8668  (est. sk_region_copy_frames)
 * Ghidra: undefined8 FUN_004b8668(long *param_1, ulong param_2, long param_3,
 *                        ulong param_4)
 * Copies a series of 0x40-byte frames from a region's metadata stream into a
 * destination, hashing/validating each frame. On a hash mismatch the region is
 * marked invalid (-1) and 0xffffffc0 is returned; other failures return
 * 0xffffffc1 (size/limit) or 0xffffffc2 (region already full). Uses a stack
 * canary and calls the stack-check on corruption. Confidence: low */
static unsigned long sk_region_copy_frames(long *region, unsigned long count,
                                           long dst, unsigned long limit)
{
    unsigned long uVar1;
    int iVar2;
    unsigned long uVar3;
    unsigned long uVar4;
    unsigned long *puVar5;
    unsigned long frame[8];   /* local_a0..uStack_68: 64-byte scratch frame */
    unsigned long local_58;
    unsigned long uStack_90;

    local_58 = -0x2c8502b44bfffed6;              /* stack canary */
    puVar5 = *(unsigned long **)*region;
    uVar3 = *puVar5;
    if (count < 0x10001 && limit < 0x10001) {
        if ((*(int *)((unsigned long *)*region + 1) == 0) ||
            ((unsigned long)region[0x11] < 0x1000000000001)) {
            if (limit != 0) {
                sk_refcount_retain((void *)region, 1);   /* FUN_00104988(region,1) */
            }
            frame[0] = 0; frame[1] = 0; frame[2] = 0; frame[3] = 0;
            frame[4] = 0; frame[5] = 0; frame[6] = 0; frame[7] = 0;
            for (; count != 0; count = count - uVar1) {
                sk_memcpy_n(&frame[0], region + 9, uVar3);      /* FUN_00117cc8(&local_a0,region+9,uVar3,0x40) */
                uStack_90 = sk_hash_combine(puVar5, uVar3, region + 1, uVar3,
                                            region + 9, region + 9);  /* FUN_00104254 */
                iVar2 = sk_hash_compare(uVar3, &frame[0], region + 9); /* FUN_00104180 */
                if (iVar2 == 0) {
                    sk_refcount_release(0x40, region + 1);     /* FUN_00104f9c */
                    sk_refcount_release(0x40, region + 9);     /* FUN_00104f9c */
                    region[0x11] = -1;
                    sk_hash_abort(0);                          /* FUN_00103dfc */
                    uVar4 = 0xffffffc0;
                    goto done;
                }
                uVar1 = count;
                if (uVar3 <= count) {
                    uVar1 = uVar3;
                }
                sk_memcpy_n((void *)(dst + 0), region + 9, uVar1); /* FUN_00117cc4(dst,region+9,uVar1) */
                dst = dst + uVar1;
            }
            sk_refcount_retain((void *)region, 1);   /* FUN_00104988(region,1) */
            uVar4 = 0;
            region[0x11] = region[0x11] + 1;
        } else {
            uVar4 = 0xffffffc2;
        }
    } else {
        uVar4 = 0xffffffc1;
    }
done:
    sk_refcount_release(uVar3, &frame[0]);          /* FUN_00104f9c(uVar3,&local_a0) */
    if (local_58 != -0x2c8502b44bfffed6) {
        sk_stack_check_fail();                      /* FUN_0011d7e8 */
    }
    return uVar4;
}

/* FUN_004b881c @ 0x004b881c  (est. sk_slot_try_claim)
 * Ghidra: undefined8 FUN_004b881c(undefined8 *param_1, ulong param_2,
 *                        undefined8 param_3, ulong param_4)
 * Tries to claim a region slot: if the region's capacity (first word >> 1) fits
 * within the requested size and limit, marks it used (slot[0x11]=1) and returns
 * 0; otherwise returns 0xffffffc1. Confidence: low */
static unsigned long sk_slot_try_claim(unsigned long *slot, unsigned long size,
                                       unsigned long ret, unsigned long limit)
{
    unsigned long res;

    if (limit < 0x10001 && **(unsigned long **)*slot >> 1 <= size) {
        sk_refcount_retain((void *)slot, 2);       /* FUN_00104988(slot,2) */
        res = 0;
        slot[0x11] = 1;
    } else {
        res = 0xffffffc1;
    }
    return res;
}

/* FUN_004b8898 @ 0x004b8898  (est. sk_mutex_acquire)
 * Ghidra: bool FUN_004b8898(char *param_1)
 * Acquires a cL4 mutex object at the given address (0x657740/0x6bf590 family):
 * takes the lock, spins on the wait-flag while broadcasting a wakeup, sets the
 * owned flag, then releases and reports whether the lock was newly taken
 * (returns true when the previous flag was not 1). On acquire/release failure
 * it reboots (sk_mutex_fail_reboot). Confidence: medium */
static bool sk_mutex_acquire(char *lock)
{
    unsigned char b;
    bool res;
    int r;

    if (*lock == '\0') {
        r = sk_lck_acquire(0x6bf590);              /* FUN_00118164 */
        if (r != 0) {
            sk_mutex_fail_reboot("  %s: failed to acquire mutex");  /* s__s_failed_to_acquire_mutex_005c70e9 */
        }
        while ((b = (unsigned char)lock[1], (b >> 1 & 1) != 0)) {
            lock[1] = (char)(b | 4);
            sk_lck_wait(0x6bf5a0, 0x6bf590);       /* FUN_0011812c */
        }
        if (b != 1) {
            lock[1] = 2;
        }
        sk_irq_save();                             /* FUN_00111848 */
        r = sk_lck_release();                      /* FUN_00118194 */
        if (r != 0) {
            sk_mutex_fail_reboot("  %s: failed to release mutex");  /* s__s_failed_to_release_mutex_005c7104 */
        }
        res = b != 1;
    } else {
        res = false;
    }
    return res;
}

/* FUN_004b895c @ 0x004b895c  (est. sk_mutex_release_broadcast)
 * Ghidra: void FUN_004b895c(undefined4 *param_1)
 * Releases a cL4 mutex object: marks it free (0), re-acquires to make the
 * update atomic, clears the owned flag, and if the broadcast-flag was set
 * wakes waiters. Reboots on any acquire/release/broadcast failure.
 * Confidence: medium */
static void sk_mutex_release_broadcast(unsigned int *lock)
{
    unsigned char b;
    int r;

    *lock = 1;
    sk_irq_save();                                /* FUN_00111848 */
    r = sk_lck_acquire(0);                        /* FUN_00118164() — arg dropped in decompile */
    if (r != 0) {
        sk_irq_restore();                          /* FUN_00111838 */
        sk_mutex_fail_reboot("  %s: failed to acquire mutex");  /* s__s_failed_to_acquire_mutex_005c70e9 */
    }
    b = *(unsigned char *)((long)lock + 1);
    *(unsigned char *)((long)lock + 1) = 1;
    sk_irq_save();                                 /* FUN_00111848 */
    r = sk_lck_release();                          /* FUN_00118194 */
    if (r == 0) {
        if (((b >> 2 & 1) != 0) && (r = sk_lck_broadcast(0x6bf5a0), r != 0)) {  /* FUN_001180e0 */
            sk_irq_restore();
            sk_mutex_fail_reboot("  %s: failed to broadcast");   /* s__s_failed_to_broadcast_005c7133 */
        }
        return;
    }
    sk_irq_restore();
    sk_mutex_fail_reboot("  %s: failed to release mutex");   /* s__s_failed_to_release_mutex_005c7104 */
}

/* FUN_004b89f8 @ 0x004b89f8  (est. sk_mutex_fail_reboot)
 * Ghidra: void FUN_004b89f8(void)
 * Mutex-operation failure sink: reboots. The failure message passed at call
 * sites is unused here. Does not return. Confidence: low */
static void sk_mutex_fail_reboot(const char *msg)
{
    (void)msg;
    sk_reboot();   /* FUN_00116d60 */
}

/* FUN_004b8a08 @ 0x004b8a08  (est. sk_stackshot_ctx_report)
 * Ghidra: void FUN_004b8a08(undefined8 param_1)
 * Prints the StackshotConclaveSupport panic-context trailer: emits the
 * "  %s: %s: %d: %s" header, appends "%s: %zu", and flushes the log line
 * (level 10, key 0xeb1a02bf914012ba). Confidence: medium */
static void sk_stackshot_ctx_report(unsigned long v)
{
    char ctx[32];
    sk_log_start(v, "  %s: %s: %d: %s");          /* s___s____s__d____s___005a8c67 */
    sk_log_append(0xeb1a02bf914012baULL, "%s: %zu", ctx);  /* s__s__zu___005a8a1d */
    sk_log_end(10, 0xeb1a02bf914012baULL);        /* FUN_001187f4 */
}

/* FUN_004b8a8c @ 0x004b8a8c  (est. sk_stackshot_no_ctx_warning)
 * Ghidra: void FUN_004b8a8c(void)
 * StackshotConclaveSupport warning: logs the "can't..." message (0x3b bytes)
 * at the stackshot key. Confidence: high (string-matched) */
static void sk_stackshot_no_ctx_warning(void)
{
    sk_log_fixed("StackshotConclaveSupport: can't...", 0x3b, 1,
                 0xeb1a02bf914012baULL);          /* s__StackshotConclaveSupport__can_t_005ca344 */
}

/* FUN_004b8aac @ 0x004b8aac  (est. sk_stackshot_ctx_error)
 * Ghidra: void FUN_004b8aac(void)
 * StackshotConclaveSupport fatal: panics with "Could..." (assert). Does not
 * return. Confidence: high (string-matched) */
static void sk_stackshot_ctx_error(void)
{
    sk_assert_panic("StackshotConclaveSupport: Could...");  /* s__StackshotConclaveSupport__Could_005ca0c8 */
}

/* FUN_004b8ac4 @ 0x004b8ac4  (est. sk_stackshot_ctx_error2)
 * Ghidra: void FUN_004b8ac4(void)
 * StackshotConclaveSupport fatal: panics with "Could..." (assert variant).
 * Does not return. Confidence: high (string-matched) */
static void sk_stackshot_ctx_error2(void)
{
    sk_assert_panic("StackshotConclaveSupport: Could...");  /* s__StackshotConclaveSupport__Could_005ca7b6 */
}

/* FUN_004b8adc @ 0x004b8adc  (est. sk_stackshot_ctx_fault)
 * Ghidra: void FUN_004b8adc(undefined8 param_1, undefined8 param_2)
 * StackshotConclaveSupport fault reporter: saves a context buffer, prints the
 * context trailer, restores context (decompiler shows two FUN_0016fa6c calls
 * as the save/restore pair), then panics with "Unexpected L4 Error".
 * Does not return. Confidence: medium */
static void sk_stackshot_ctx_fault(unsigned long a, unsigned long b)
{
    char ctx[32];
    sk_ctx_save_restore(ctx);                      /* FUN_0016fa6c(ctx) */
    sk_stackshot_ctx_report(0xeb1a02bf914012baULL);
    sk_ctx_save_restore((void *)b, a);             /* FUN_0016fa6c(b,a) — decompile oddity */
    sk_assert_panic("Unexpected L4 Error: %s: %zu, err");  /* s_Unexpected_L4_Error___s__zu__err_005b6dc4 */
}

/* FUN_004b8b44 @ 0x004b8b44  (est. sk_stackshot_stack_report)
 * Ghidra: void FUN_004b8b44(undefined8 param_1, undefined8 param_2,
 *                  undefined8 param_3)
 * StackshotConclaveSupport stack report: sets context kind 5, restores a
 * context pair, then logs the "stack..." message (0x2f bytes). Confidence:
 * medium */
static void sk_stackshot_stack_report(unsigned long a, unsigned long b, unsigned long c)
{
    sk_stackshot_ctx_set(a, 5);                    /* FUN_00046304(a,5) */
    sk_ctx_restore2(b, c);                         /* FUN_0016f9c0(b,c) */
    sk_log_fixed("StackshotConclaveSupport: stack...", 0x2f, 1,
                 0xeb1a02bf914012baULL);          /* s__StackshotConclaveSupport__stack_005ca786 */
}

/* FUN_004b8b9c @ 0x004b8b9c  (est. sk_stackshot_no_stack)
 * Ghidra: void FUN_004b8b9c(undefined8 param_1)
 * StackshotConclaveSupport: logs "No st..." at the current context. Confidence:
 * high (string-matched) */
static void sk_stackshot_no_stack(unsigned long ctx)
{
    unsigned long v;
    sk_stackshot_ctx_set(ctx, 3);                  /* FUN_00046304(ctx,3) */
    v = sk_stackshot_ctx_get();                    /* FUN_0016fb80 */
    sk_log_start(v, "StackshotConclaveSupport: No st...");  /* s__StackshotConclaveSupport__No_st_005ca719 */
}

/* FUN_004b8bdc @ 0x004b8bdc  (est. sk_stackshot_no_exception)
 * Ghidra: void FUN_004b8bdc(undefined8 param_1)
 * StackshotConclaveSupport: logs "No ec..." at the current context. Confidence:
 * high (string-matched) */
static void sk_stackshot_no_exception(unsigned long ctx)
{
    unsigned long v;
    sk_stackshot_ctx_set(ctx, 3);                  /* FUN_00046304(ctx,3) */
    v = sk_stackshot_ctx_get();                    /* FUN_0016fb80 */
    sk_log_start(v, "StackshotConclaveSupport: No ec...");  /* s__StackshotConclaveSupport__No_ec_005ca6e7 */
}

/* FUN_004b8c1c @ 0x004b8c1c  (est. sk_stackshot_no_dispatch)
 * Ghidra: void FUN_004b8c1c(undefined8 param_1)
 * StackshotConclaveSupport: logs "No da..." at the current context. Confidence:
 * high (string-matched) */
static void sk_stackshot_no_dispatch(unsigned long ctx)
{
    unsigned long v;
    sk_stackshot_ctx_set(ctx, 3);                  /* FUN_00046304(ctx,3) */
    v = sk_stackshot_ctx_get();                    /* FUN_0016fb80 */
    sk_log_start(v, "StackshotConclaveSupport: No da...");  /* s__StackshotConclaveSupport__No_da_005ca6b7 */
}

/* FUN_004b8c5c @ 0x004b8c5c  (est. sk_stackshot_no_dispatch2)
 * Ghidra: void FUN_004b8c5c(undefined8 param_1)
 * StackshotConclaveSupport: logs "No da..." at the current context (kind 1).
 * Confidence: high (string-matched) */
static void sk_stackshot_no_dispatch2(unsigned long ctx)
{
    unsigned long v;
    sk_stackshot_ctx_set(ctx, 1);                  /* FUN_00046304(ctx,1) */
    v = sk_stackshot_ctx_get();                    /* FUN_0016fb80 */
    sk_log_start(v, "StackshotConclaveSupport: No da...");  /* s__StackshotConclaveSupport__No_da_005ca685 */
}

/* FUN_004b8c9c @ 0x004b8c9c  (est. sk_incorrect_assumption_panic)
 * Ghidra: void FUN_004b8c9c(void)
 * Stackshot fatal: panics with "incorrect assumption: invalid n...". Does not
 * return. Confidence: high (string-matched) */
static void sk_incorrect_assumption_panic(void)
{
    sk_assert_panic("incorrect assumption: invalid n...");  /* s_incorrect_assumption___invalid_n_005ca4c5 */
}

/* FUN_004b8cb4 @ 0x004b8cb4  (est. sk_ran_out_of_heap_space_panic)
 * Ghidra: void FUN_004b8cb4(void)
 * Stackshot fatal: panics with "ran out of heap space". Does not return.
 * Confidence: high (string-matched) */
static void sk_ran_out_of_heap_space_panic(void)
{
    sk_assert_panic("ran out of heap space");   /* s_ran_out_of_heap_space_005ca4af */
}

/* FUN_004b8ccc @ 0x004b8ccc  (est. sk_get_thread_info_panic)
 * Ghidra: void FUN_004b8ccc(void)
 * Fatal in get_thread_info: "thread" invariant (line 0x6f). Does not return.
 * Confidence: high (string-matched) */
static void sk_get_thread_info_panic(void)
{
    sk_panic_4("thread",                          /* s_thread_005caa77 */
               "AppleInternal Library BuildRoot", /* s__AppleInternal_Library_BuildRoot_005caa7e */
               "get_thread_info", 0x6f);          /* s_get_thread_info_005cab56 */
}

/* ---- StackshotDelegate C++ fatal-trap stubs (004b8cf8..004b9094) ----
 * Each prints a context/delegate message then traps via SoftwareBreakpoint. */

/* FUN_004b8cf8 @ 0x004b8cf8  (est. sk_stackshot_delegate_trap)
 * Ghidra: void FUN_004b8cf8(void)
 * StackshotDelegate C++ fatal: prints the delegate message then traps at
 * 0x4b8d1c. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap(void)
{
    sk_delegate_msg_a("StackshotDelegate C++");  /* FUN_001724cc + s_StackshotDelegate_C_c_005cad2a */
    SoftwareBreakpoint(1, 0x4b8d1c);
}

/* FUN_004b8d1c @ 0x004b8d1c  (est. sk_stackshot_delegate_trap2)
 * Ghidra: void FUN_004b8d1c(void)
 * StackshotDelegate C++ fatal: prints the delegate message then traps at
 * 0x4b8d40. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap2(void)
{
    sk_delegate_msg_b("StackshotDelegate C++");  /* FUN_001724bc + s_StackshotDelegate_C_c_005cad2a */
    SoftwareBreakpoint(1, 0x4b8d40);
}

/* FUN_004b8d40 @ 0x004b8d40  (est. sk_stackshot_delegate_trap3)
 * Ghidra: void FUN_004b8d40(void)
 * StackshotDelegate C++ fatal: prints the delegate context then traps at
 * 0x4b8d58. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap3(void)
{
    sk_delegate_nomsg_a();                        /* FUN_0017244c */
    SoftwareBreakpoint(1, 0x4b8d58);
}

/* FUN_004b8d58 @ 0x004b8d58  (est. sk_stackshot_delegate_trap4)
 * Ghidra: void FUN_004b8d58(void)
 * StackshotDelegate C++ fatal: prints the delegate message then traps at
 * 0x4b8d7c. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap4(void)
{
    sk_delegate_msg_a("StackshotDelegate C++");  /* FUN_001724cc */
    SoftwareBreakpoint(1, 0x4b8d7c);
}

/* FUN_004b8d7c @ 0x004b8d7c  (est. sk_stackshot_delegate_trap5)
 * Ghidra: void FUN_004b8d7c(void)
 * StackshotDelegate C++ fatal: prints the delegate message then traps at
 * 0x4b8da0. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap5(void)
{
    sk_delegate_msg_b("StackshotDelegate C++");  /* FUN_001724bc */
    SoftwareBreakpoint(1, 0x4b8da0);
}

/* FUN_004b8da0 @ 0x004b8da0  (est. sk_stackshot_delegate_trap6)
 * Ghidra: void FUN_004b8da0(void)
 * StackshotDelegate C++ fatal: prints the delegate context then traps at
 * 0x4b8db8. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap6(void)
{
    sk_delegate_nomsg_b();                        /* FUN_00172484 */
    SoftwareBreakpoint(1, 0x4b8db8);
}

/* FUN_004b8db8 @ 0x004b8db8  (est. sk_stackshot_delegate_trap7)
 * Ghidra: void FUN_004b8db8(void)
 * StackshotDelegate C++ fatal: prints the delegate context then traps at
 * 0x4b8dd0. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap7(void)
{
    sk_delegate_nomsg_c();                        /* FUN_001724a0 */
    SoftwareBreakpoint(1, 0x4b8dd0);
}

/* FUN_004b8dd0 @ 0x004b8dd0  (est. sk_stackshot_delegate_trap8)
 * Ghidra: void FUN_004b8dd0(void)
 * StackshotDelegate C++ fatal: prints the delegate context then traps at
 * 0x4b8de8. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap8(void)
{
    sk_delegate_nomsg_d();                        /* FUN_00172468 */
    SoftwareBreakpoint(1, 0x4b8de8);
}

/* FUN_004b8de8 @ 0x004b8de8  (est. sk_stackshot_delegate_trap9)
 * Ghidra: void FUN_004b8de8(void)
 * StackshotDelegate C++ fatal: prints the delegate report then traps at
 * 0x4b8e0c. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap9(void)
{
    sk_delegate_report_a("StackshotDelegate C++");  /* FUN_0004b488 */
    SoftwareBreakpoint(1, 0x4b8e0c);
}

/* FUN_004b8e0c @ 0x004b8e0c  (est. sk_stackshot_delegate_trap10)
 * Ghidra: void FUN_004b8e0c(void)
 * StackshotDelegate C++ fatal: prints the delegate report then traps at
 * 0x4b8e30. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap10(void)
{
    sk_delegate_report_b("StackshotDelegate C++");  /* FUN_0004b478 */
    SoftwareBreakpoint(1, 0x4b8e30);
}

/* FUN_004b8e30 @ 0x004b8e30  (est. sk_stackshot_delegate_fatal_msg)
 * Ghidra: void FUN_004b8e30(void)
 * StackshotDelegate fatal: prints the DAT_005cb335 message then traps at
 * 0x4b8e60. Does not return. Confidence: low */
static void sk_stackshot_delegate_fatal_msg(void)
{
    sk_fatal_msg((const char *)0x5cb335);        /* FUN_00118b28 + DAT_005cb335 */
    SoftwareBreakpoint(1, 0x4b8e60);
}

/* FUN_004b8e60 @ 0x004b8e60  (est. sk_stackshot_delegate_trap11)
 * Ghidra: void FUN_004b8e60(void)
 * StackshotDelegate C++ fatal: prints the delegate report then traps at
 * 0x4b8e84. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap11(void)
{
    sk_delegate_report_a("StackshotDelegate C++");  /* FUN_0004b488 */
    SoftwareBreakpoint(1, 0x4b8e84);
}

/* FUN_004b8e84 @ 0x004b8e84  (est. sk_stackshot_delegate_trap12)
 * Ghidra: void FUN_004b8e84(void)
 * StackshotDelegate C++ fatal: prints the delegate report then traps at
 * 0x4b8ea8. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap12(void)
{
    sk_delegate_report_b("StackshotDelegate C++");  /* FUN_0004b478 */
    SoftwareBreakpoint(1, 0x4b8ea8);
}

/* FUN_004b8ea8 @ 0x004b8ea8  (est. sk_stackshot_delegate_fatal_msg2)
 * Ghidra: void FUN_004b8ea8(void)
 * StackshotDelegate fatal: prints the DAT_005cb16b message then traps at
 * 0x4b8ed8. Does not return. Confidence: low */
static void sk_stackshot_delegate_fatal_msg2(void)
{
    sk_fatal_msg((const char *)0x5cb16b);        /* FUN_00118b28 + DAT_005cb16b */
    SoftwareBreakpoint(1, 0x4b8ed8);
}

/* FUN_004b8ed8 @ 0x004b8ed8  (est. sk_stackshot_delegate_trap13)
 * Ghidra: void FUN_004b8ed8(void)
 * StackshotDelegate C++ fatal: prints the delegate report then traps at
 * 0x4b8efc. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap13(void)
{
    sk_delegate_report_a("StackshotDelegate C++");  /* FUN_0004b488 */
    SoftwareBreakpoint(1, 0x4b8efc);
}

/* FUN_004b8efc @ 0x004b8efc  (est. sk_stackshot_delegate_trap14)
 * Ghidra: void FUN_004b8efc(void)
 * StackshotDelegate C++ fatal: prints the delegate report then traps at
 * 0x4b8f20. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap14(void)
{
    sk_delegate_report_b("StackshotDelegate C++");  /* FUN_0004b478 */
    SoftwareBreakpoint(1, 0x4b8f20);
}

/* FUN_004b8f20 @ 0x004b8f20  (est. sk_stackshot_delegate_fatal_msg3)
 * Ghidra: void FUN_004b8f20(void)
 * StackshotDelegate fatal: prints the DAT_005caf6f message then traps at
 * 0x4b8f50. Does not return. Confidence: low */
static void sk_stackshot_delegate_fatal_msg3(void)
{
    sk_fatal_msg((const char *)0x5caf6f);        /* FUN_00118b28 + DAT_005caf6f */
    SoftwareBreakpoint(1, 0x4b8f50);
}

/* FUN_004b8f50 @ 0x004b8f50  (est. sk_stackshot_delegate_trap15)
 * Ghidra: void FUN_004b8f50(void)
 * StackshotDelegate C++ fatal: prints the delegate report then traps at
 * 0x4b8f74. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap15(void)
{
    sk_delegate_report_a("StackshotDelegate C++");  /* FUN_0004b488 */
    SoftwareBreakpoint(1, 0x4b8f74);
}

/* FUN_004b8f74 @ 0x004b8f74  (est. sk_stackshot_delegate_trap16)
 * Ghidra: void FUN_004b8f74(void)
 * StackshotDelegate C++ fatal: prints the delegate report then traps at
 * 0x4b8f98. Does not return. Confidence: low */
static void sk_stackshot_delegate_trap16(void)
{
    sk_delegate_report_b("StackshotDelegate C++");  /* FUN_0004b478 */
    SoftwareBreakpoint(1, 0x4b8f98);
}

/* FUN_004b8f98 @ 0x004b8f98  (est. sk_stackshot_delegate_fatal_msg4)
 * Ghidra: void FUN_004b8f98(void)
 * StackshotDelegate fatal: prints the DAT_005caec8 message then traps at
 * 0x4b8fc8. Does not return. Confidence: low */
static void sk_stackshot_delegate_fatal_msg4(void)
{
    sk_fatal_msg((const char *)0x5caec8);        /* FUN_00118b28 + DAT_005caec8 */
    SoftwareBreakpoint(1, 0x4b8fc8);
}

/* FUN_004b8fc8 @ 0x004b8fc8  (est. sk_buildroot_trap_a)
 * Ghidra: void FUN_004b8fc8(void)
 * AppleInternal buildroot fatal: prints the buildroot message then traps at
 * 0x4b8fec. Does not return. Confidence: low */
static void sk_buildroot_trap_a(void)
{
    sk_buildroot_panic_a("AppleInternal Library BuildRoot");  /* FUN_000179d8 + s__AppleInternal_Library_BuildRoot_005cabb6 */
    SoftwareBreakpoint(1, 0x4b8fec);
}

/* FUN_004b8fec @ 0x004b8fec  (est. sk_buildroot_trap_b)
 * Ghidra: void FUN_004b8fec(void)
 * AppleInternal buildroot fatal: prints the buildroot message then traps at
 * 0x4b9010. Does not return. Confidence: low */
static void sk_buildroot_trap_b(void)
{
    sk_buildroot_panic_b("AppleInternal Library BuildRoot");  /* FUN_00015e2c + s__AppleInternal_Library_BuildRoot_005cabb6 */
    SoftwareBreakpoint(1, 0x4b9010);
}

/* FUN_004b9010 @ 0x004b9010  (est. sk_buildroot_trap_c)
 * Ghidra: void FUN_004b9010(void)
 * AppleInternal buildroot fatal: prints the buildroot message then traps at
 * 0x4b9034. Does not return. Confidence: low */
static void sk_buildroot_trap_c(void)
{
    sk_buildroot_panic_a("AppleInternal Library BuildRoot");  /* FUN_000179d8 + s__AppleInternal_Library_BuildRoot_005cabb6 */
    SoftwareBreakpoint(1, 0x4b9034);
}

/* FUN_004b9034 @ 0x004b9034  (est. sk_tb_invalid_error_trap)
 * Ghidra: void FUN_004b9034(void)
 * TB fatal: prints "TB_FATAL: invalid error returned" then traps at 0x4b9064.
 * Does not return. Confidence: high (string-matched) */
static void sk_tb_invalid_error_trap(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005cb3f1 */
    SoftwareBreakpoint(1, 0x4b9064);
}

/* FUN_004b9064 @ 0x004b9064  (est. sk_tb_invalid_error_trap2)
 * Ghidra: void FUN_004b9064(void)
 * TB fatal: prints "TB_FATAL: invalid error returned" then traps at 0x4b9094.
 * Does not return. Confidence: high (string-matched) */
static void sk_tb_invalid_error_trap2(void)
{
    sk_fatal_msg("TB_FATAL: invalid error returned");  /* s_TB_FATAL__invalid_error_returned_005cb434 */
    SoftwareBreakpoint(1, 0x4b9094);
}

/* FUN_004b9094 @ 0x004b9094  (est. sk_buildroot_trap_d)
 * Ghidra: void FUN_004b9094(void)
 * AppleInternal buildroot fatal: prints the buildroot message then traps at
 * 0x4b90b8. Does not return. Confidence: low */
static void sk_buildroot_trap_d(void)
{
    sk_buildroot_panic_a("AppleInternal Library BuildRoot");  /* FUN_000179d8 + s__AppleInternal_Library_BuildRoot_005cabb6 */
    SoftwareBreakpoint(1, 0x4b90b8);
}

/* ---- Swift runtime metadata fatal traps (004b90b8..004b94e8) ----
 * Each is the "init(doNotCallMeBase:)" / placeholder type-descriptor fatal for
 * a Swift standard-library collection metatype. They route through
 * sk_swift_type_fatal (FUN_001b11bc) which does not return; the trailing
 * &stack argument is the callback continuation address. */

/* FUN_004b90d0 @ 0x004b90d0  (est. sk_swift_emptyarray_storage_fatal)
 * Ghidra: void FUN_004b90d0(void)
 * Swift fatal: Swift.ContiguousArrayBuffer's _EmptyArrayStorage placeholder
 * init is not callable; traps at 0x4b9110. Does not return. Confidence: low */
static void sk_swift_emptyarray_storage_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ContiguousArrayBuffer", 0x21,
                        (unsigned long)"Swift._EmptyArrayStorage", 0x19,
                        (unsigned long)"init(doNotCallMeBase:)", 0x17, 0x20, 0x16);
    SoftwareBreakpoint(1, 0x4b9110);
}

/* FUN_004b90b8 @ 0x004b90b8  (est. sk_swift_emptyarray_storage_fatal2)
 * Ghidra: void FUN_004b90b8(void)
 * Swift fatal for _EmptyArrayStorage (with continuation), traps at 0x4b9110.
 * Does not return. Confidence: low */
static void sk_swift_emptyarray_storage_fatal2(void)
{
    sk_swift_runtime_enter();                      /* FUN_00359434 */
    sk_swift_emptyarray_storage_fatal();
    sk_swift_type_fatal((unsigned long)"Swift.ContiguousArrayBuffer", 0x21,
                        (unsigned long)"Swift._EmptyArrayStorage", 0x19,
                        (unsigned long)"init(doNotCallMeBase:)", 0x17, 0x20, 0x16,
                        (unsigned long)0, (unsigned long)sk_swift_emptyarray_storage_fatal);
    SoftwareBreakpoint(1, 0x4b9110);
}

/* FUN_004b9140 @ 0x004b9140  (est. sk_swift_staticarray_storage_fatal)
 * Ghidra: void FUN_004b9140(void)
 * Swift fatal: Swift.ContiguousArrayBuffer's _StaticArrayStorage placeholder
 * init; traps at 0x4b9180. Does not return. Confidence: low */
static void sk_swift_staticarray_storage_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ContiguousArrayBuffer", 0x21,
                        (unsigned long)"Swift._StaticArrayStorage", 0x1a,
                        (unsigned long)"init(doNotCallMeBase:)", 0x17, 0x58, 0x16);
    SoftwareBreakpoint(1, 0x4b9180);
}

/* FUN_004b9128 @ 0x004b9128  (est. sk_swift_staticarray_storage_fatal2)
 * Ghidra: void FUN_004b9128(void)
 * Swift fatal for _StaticArrayStorage (with continuation); traps at 0x4b9180.
 * Does not return. Confidence: low */
static void sk_swift_staticarray_storage_fatal2(void)
{
    sk_swift_runtime_enter();                      /* FUN_00359434 */
    sk_swift_staticarray_storage_fatal();
    sk_swift_type_fatal((unsigned long)"Swift.ContiguousArrayBuffer", 0x21,
                        (unsigned long)"Swift._StaticArrayStorage", 0x1a,
                        (unsigned long)"init(doNotCallMeBase:)", 0x17, 0x58, 0x16,
                        (unsigned long)0, (unsigned long)sk_swift_staticarray_storage_fatal);
    SoftwareBreakpoint(1, 0x4b9180);
}

/* FUN_004b9110 @ 0x004b9110  (est. sk_swift_staticarray_storage_fatal3)
 * Ghidra: void FUN_004b9110(void)
 * Swift fatal for _StaticArrayStorage (top-level variant, references
 * sk_swift_native_nsarray_fatal); traps at 0x4b9180. Does not return.
 * Confidence: low */
static void sk_swift_staticarray_storage_fatal3(void)
{
    unsigned long stack_slot;
    sk_swift_runtime_enter();                      /* FUN_00359434 */
    sk_swift_native_nsarray_fatal();
    sk_swift_runtime_enter();                      /* FUN_00359434 */
    sk_swift_staticarray_storage_fatal();
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.ContiguousArrayBuffer", 0x21,
                        (unsigned long)"Swift._StaticArrayStorage", 0x1a,
                        (unsigned long)"init(doNotCallMeBase:)", 0x17, 0x58, 0x16,
                        stack_slot, (unsigned long)sk_swift_staticarray_storage_fatal);
    SoftwareBreakpoint(1, 0x4b9180);
}

/* FUN_004b9198 @ 0x004b9198  (est. sk_swift_dictionary_storage_fatal)
 * Ghidra: void FUN_004b9198(void)
 * Swift fatal: Swift.DictionaryStorage's _RawDictionaryStorage placeholder
 * init; traps at 0x4b91d8. Does not return. Confidence: low */
static void sk_swift_dictionary_storage_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.DictionaryStorage", 0x1d,
                        (unsigned long)"Swift._RawDictionaryStorage", 0x1c,
                        (unsigned long)"init", 6, 0x1a, 0x10);
    SoftwareBreakpoint(1, 0x4b91d8);
}

/* FUN_004b9180 @ 0x004b9180  (est. sk_swift_dictionary_storage_fatal2)
 * Ghidra: void FUN_004b9180(void)
 * Swift fatal for _RawDictionaryStorage (with continuation); traps at 0x4b91d8.
 * Does not return. Confidence: low */
static void sk_swift_dictionary_storage_fatal2(void)
{
    unsigned long stack_slot;
    sk_swift_runtime_enter();                      /* FUN_00359434 */
    sk_swift_dictionary_storage_fatal();
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.DictionaryStorage", 0x1d,
                        (unsigned long)"Swift._RawDictionaryStorage", 0x1c,
                        (unsigned long)"init", 6, 0x1a, 0x10,
                        stack_slot, (unsigned long)sk_swift_dictionary_storage_fatal);
    SoftwareBreakpoint(1, 0x4b91d8);
}

/* FUN_004b9200 @ 0x004b9200  (est. sk_swift_iterator_box_fatal)
 * Ghidra: void FUN_004b9200(void)
 * Swift fatal: Swift.ExistentialCollection's _IteratorBox placeholder init;
 * traps at 0x4b923c. Does not return. Confidence: low */
static void sk_swift_iterator_box_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._IteratorBox", 0x12,
                        (unsigned long)"init", 6, 0x99, 0x16);
    SoftwareBreakpoint(1, 0x4b923c);
}

/* FUN_004b91dc @ 0x004b91dc  (est. sk_swift_iterator_box_fatal2)
 * Ghidra: void FUN_004b91dc(void)
 * Swift fatal for _IteratorBox (with continuation at 0x4b91fc); traps at
 * 0x4b923c. Does not return. Confidence: low */
static void sk_swift_iterator_box_fatal2(void)
{
    unsigned long stack_slot;
    sk_swift_meta_dispatch((unsigned long)0x4b91fc);   /* FUN_004b92b8(0x4b91fc) */
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._IteratorBox", 0x12,
                        (unsigned long)"init", 6, 0x99, 0x16,
                        stack_slot, (unsigned long)0x4b91fc);
    SoftwareBreakpoint(1, 0x4b923c);
}

/* FUN_004b91d8 @ 0x004b91d8  (est. sk_swift_iterator_box_fatal3)
 * Ghidra: void FUN_004b91d8(void)
 * Swift fatal for _IteratorBox (duplicate of 004b91dc); traps at 0x4b923c.
 * Does not return. Confidence: low */
static void sk_swift_iterator_box_fatal3(void)
{
    unsigned long stack_slot;
    sk_swift_meta_dispatch((unsigned long)0x4b91fc);   /* FUN_004b92b8(0x4b91fc) */
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._IteratorBox", 0x12,
                        (unsigned long)"init", 6, 0x99, 0x16,
                        stack_slot, (unsigned long)0x4b91fc);
    SoftwareBreakpoint(1, 0x4b923c);
}

/* FUN_004b9254 @ 0x004b9254  (est. sk_swift_anycollection_box_fatal)
 * Ghidra: void FUN_004b9254(void)
 * Swift fatal: Swift.ExistentialCollection's _AnyCollectionBox placeholder
 * init; traps at 0x4b9294. Does not return. Confidence: low */
static void sk_swift_anycollection_box_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._AnyCollectionBox", 0x17,
                        (unsigned long)"init", 6, 0x10e, 0x10);
    SoftwareBreakpoint(1, 0x4b9294);
}

/* FUN_004b923c @ 0x004b923c  (est. sk_swift_anycollection_box_fatal2)
 * Ghidra: void FUN_004b923c(void)
 * Swift fatal for _AnyCollectionBox (with continuation); traps at 0x4b9294.
 * Does not return. Confidence: low */
static void sk_swift_anycollection_box_fatal2(void)
{
    unsigned long stack_slot;
    sk_swift_runtime_enter();                      /* FUN_00359434 */
    sk_swift_anycollection_box_fatal();
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._AnyCollectionBox", 0x17,
                        (unsigned long)"init", 6, 0x10e, 0x10,
                        stack_slot, (unsigned long)sk_swift_anycollection_box_fatal);
    SoftwareBreakpoint(1, 0x4b9294);
}

/* FUN_004b92b8 @ 0x004b92b8  (est. sk_swift_meta_dispatch)
 * Ghidra: void FUN_004b92b8(void)  [uses unaff_x19/x20]
 * Swift metadata dispatch: resolves metadata via sk_swift_meta_get, stores a
 * two-field metadata value from the register-carried object (unaff_x20), then
 * invokes the register-carried continuation (unaff_x19) and traps at 0x4b92ec.
 * The x19/x20 inputs are carried across the register-based metadata decoder
 * and are unavailable in the decompile. Confidence: low */
static unsigned long sk_swift_meta_dispatch(unsigned long cb)
{
    unsigned long v;
    v = sk_swift_meta_get(0);                      /* FUN_0035310c */
    /* unaff_x20 + 0x18 / + 0x1c metadata fields not available */
    sk_swift_meta_set(v, 0, 0);                    /* FUN_0036a940 */
    (*(void (*)(void))cb)();
    SoftwareBreakpoint(1, 0x4b92ec);
    return 0;
}

/* FUN_004b9294 @ 0x004b9294  (est. sk_swift_meta_dispatch2)
 * Ghidra: void FUN_004b9294(void)  [uses unaff_x19/x20]
 * Swift metadata dispatch (with callback): drives the 004b92b8 dispatch core
 * with the sequence-box continuation, then re-resolves metadata and stores it
 * before invoking the register-carried x19 continuation. Traps at 0x4b92ec.
 * Confidence: low */
static void sk_swift_meta_dispatch2(unsigned long x19_cb)
{
    unsigned long v;
    v = sk_swift_meta_dispatch((unsigned long)sk_swift_sequence_box_fatal); /* FUN_004b92b8(004b92ec) */
    v = sk_swift_meta_get(v, (unsigned long)sk_swift_meta_dispatch);        /* FUN_0035310c */
    /* unaff_x20 + 0x18 / + 0x1c metadata fields not available */
    sk_swift_meta_set(v, 0, 0);                    /* FUN_0036a940 */
    (*(void (*)(void))x19_cb)();
    SoftwareBreakpoint(1, 0x4b92ec);
}

/* FUN_004b9298 @ 0x004b9298  (est. sk_swift_meta_dispatch3)
 * Ghidra: void FUN_004b9298(void)  [uses unaff_x19/x20]
 * Swift metadata dispatch (duplicate of 004b9294). Traps at 0x4b92ec.
 * Confidence: low */
static void sk_swift_meta_dispatch3(unsigned long x19_cb)
{
    unsigned long v;
    v = sk_swift_meta_dispatch((unsigned long)sk_swift_sequence_box_fatal); /* FUN_004b92b8(004b92ec) */
    v = sk_swift_meta_get(v, (unsigned long)sk_swift_meta_dispatch);        /* FUN_0035310c */
    sk_swift_meta_set(v, 0, 0);                    /* FUN_0036a940 */
    (*(void (*)(void))x19_cb)();
    SoftwareBreakpoint(1, 0x4b92ec);
}

/* FUN_004b92ec @ 0x004b92ec  (est. sk_swift_sequence_box_fatal)
 * Ghidra: void FUN_004b92ec(void)
 * Swift fatal: Swift.ExistentialCollection's _SequenceBox placeholder init;
 * traps at 0x4b932c. Does not return. Confidence: low */
static void sk_swift_sequence_box_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._SequenceBox", 0x12,
                        (unsigned long)"init", 6, 0x20e, 0x16);
    SoftwareBreakpoint(1, 0x4b932c);
}

/* FUN_004b92f0 @ 0x004b92f0  (est. sk_swift_sequence_box_fatal2)
 * Ghidra: void FUN_004b92f0(void)
 * Swift fatal for _SequenceBox (duplicate of 004b92ec); traps at 0x4b932c.
 * Does not return. Confidence: low */
static void sk_swift_sequence_box_fatal2(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._SequenceBox", 0x12,
                        (unsigned long)"init", 6, 0x20e, 0x16);
    SoftwareBreakpoint(1, 0x4b932c);
}

/* FUN_004b9354 @ 0x004b9354  (est. sk_swift_collection_box_fatal)
 * Ghidra: void FUN_004b9354(void)
 * Swift fatal: Swift.ExistentialCollection's _CollectionBox placeholder init;
 * traps at 0x4b9390. Does not return. Confidence: low */
static void sk_swift_collection_box_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._CollectionBox", 0x14,
                        (unsigned long)"init(startIndex:endIndex:)", 0x1b, 0x26e, 0x16);
    SoftwareBreakpoint(1, 0x4b9390);
}

/* FUN_004b9330 @ 0x004b9330  (est. sk_swift_collection_box_fatal2)
 * Ghidra: void FUN_004b9330(void)
 * Swift fatal for _CollectionBox (with continuation at 0x4b9350); traps at
 * 0x4b9390. Does not return. Confidence: low */
static void sk_swift_collection_box_fatal2(void)
{
    unsigned long stack_slot;
    sk_swift_collection_box_pre();                 /* FUN_004b9418 */
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._CollectionBox", 0x14,
                        (unsigned long)"init(startIndex:endIndex:)", 0x1b, 0x26e, 0x16,
                        stack_slot, (unsigned long)0x4b9350);
    SoftwareBreakpoint(1, 0x4b9390);
}

/* FUN_004b932c @ 0x004b932c  (est. sk_swift_collection_box_fatal3)
 * Ghidra: void FUN_004b932c(void)
 * Swift fatal for _CollectionBox (duplicate of 004b9330); traps at 0x4b9390.
 * Does not return. Confidence: low */
static void sk_swift_collection_box_fatal3(void)
{
    unsigned long stack_slot;
    sk_swift_collection_box_pre();                 /* FUN_004b9418 */
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._CollectionBox", 0x14,
                        (unsigned long)"init(startIndex:endIndex:)", 0x1b, 0x26e, 0x16,
                        stack_slot, (unsigned long)0x4b9350);
    SoftwareBreakpoint(1, 0x4b9390);
}

/* FUN_004b93b8 @ 0x004b93b8  (est. sk_swift_bidirectional_collection_fatal)
 * Ghidra: void FUN_004b93b8(void)
 * Swift fatal: _BidirectionalCollectionBox placeholder init; traps at 0x4b93f4.
 * Does not return. Confidence: low */
static void sk_swift_bidirectional_collection_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._BidirectionalCollectionBox", 0x21,
                        (unsigned long)"init(startIndex:endIndex:)", 0x1b, 0x332, 0x16);
    SoftwareBreakpoint(1, 0x4b93f4);
}

/* FUN_004b9394 @ 0x004b9394  (est. sk_swift_bidirectional_collection_fatal2)
 * Ghidra: void FUN_004b9394(void)
 * Swift fatal for _BidirectionalCollectionBox (with continuation at 0x4b93b4);
 * traps at 0x4b93f4. Does not return. Confidence: low */
static void sk_swift_bidirectional_collection_fatal2(void)
{
    unsigned long stack_slot;
    sk_swift_collection_box_pre();                 /* FUN_004b9418 */
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._BidirectionalCollectionBox", 0x21,
                        (unsigned long)"init(startIndex:endIndex:)", 0x1b, 0x332, 0x16,
                        stack_slot, (unsigned long)0x4b93b4);
    SoftwareBreakpoint(1, 0x4b93f4);
}

/* FUN_004b9390 @ 0x004b9390  (est. sk_swift_bidirectional_collection_fatal3)
 * Ghidra: void FUN_004b9390(void)
 * Swift fatal for _BidirectionalCollectionBox (duplicate of 004b9394); traps
 * at 0x4b93f4. Does not return. Confidence: low */
static void sk_swift_bidirectional_collection_fatal3(void)
{
    unsigned long stack_slot;
    sk_swift_collection_box_pre();                 /* FUN_004b9418 */
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._BidirectionalCollectionBox", 0x21,
                        (unsigned long)"init(startIndex:endIndex:)", 0x1b, 0x332, 0x16,
                        stack_slot, (unsigned long)0x4b93b4);
    SoftwareBreakpoint(1, 0x4b93f4);
}

/* FUN_004b9418 @ 0x004b9418  (est. sk_swift_collection_box_pre)
 * Ghidra: void FUN_004b9418(void)  [uses in_x4]
 * Swift metadata box pre-step: resolves and stores metadata from the stream
 * (FUN_0036a940), then invokes the continuation carried in x4, and traps at
 * 0x4b9448. The x4 callback is register-carried. Confidence: low */
static void sk_swift_collection_box_pre(void)
{
    sk_swift_meta_set_from_stream();               /* FUN_0036a940() */
    /* in_x4 continuation not available in decompile */
    SoftwareBreakpoint(1, 0x4b9448);
}

/* FUN_004b93f4 @ 0x004b93f4  (est. sk_swift_collection_box_pre2)
 * Ghidra: void FUN_004b93f4(void)  [uses unaff_x19]
 * Swift metadata box pre-step (calls 004b9418 then the metadata setter, then
 * invokes the register-carried x19 continuation = sk_swift_randomaccess_
 * collection_fatal, and traps at 0x4b9448). Confidence: low */
static void sk_swift_collection_box_pre2(void)
{
    sk_swift_collection_box_pre();
    sk_swift_meta_set_from_stream();               /* FUN_0036a940() */
    sk_swift_randomaccess_collection_fatal();
    SoftwareBreakpoint(1, 0x4b9448);
}

/* FUN_004b93f8 @ 0x004b93f8  (est. sk_swift_collection_box_pre3)
 * Ghidra: void FUN_004b93f8(void)  [uses unaff_x19]
 * Swift metadata box pre-step (duplicate of 004b93f4). Traps at 0x4b9448.
 * Confidence: low */
static void sk_swift_collection_box_pre3(void)
{
    sk_swift_collection_box_pre();
    sk_swift_meta_set_from_stream();               /* FUN_0036a940() */
    sk_swift_randomaccess_collection_fatal();
    SoftwareBreakpoint(1, 0x4b9448);
}

/* FUN_004b9448 @ 0x004b9448  (est. sk_swift_randomaccess_collection_fatal)
 * Ghidra: void FUN_004b9448(void)
 * Swift fatal: _RandomAccessCollectionBox placeholder init; traps at 0x4b9488.
 * Does not return. Confidence: low */
static void sk_swift_randomaccess_collection_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._RandomAccessCollectionBox", 0x20,
                        (unsigned long)"init(startIndex:endIndex:)", 0x1b, 0x409, 0x16);
    SoftwareBreakpoint(1, 0x4b9488);
}

/* FUN_004b944c @ 0x004b944c  (est. sk_swift_randomaccess_collection_fatal2)
 * Ghidra: void FUN_004b944c(void)
 * Swift fatal for _RandomAccessCollectionBox (duplicate of 004b9448); traps at
 * 0x4b9488. Does not return. Confidence: low */
static void sk_swift_randomaccess_collection_fatal2(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.ExistentialCollection", 0x21,
                        (unsigned long)"Swift._RandomAccessCollectionBox", 0x20,
                        (unsigned long)"init(startIndex:endIndex:)", 0x1b, 0x409, 0x16);
    SoftwareBreakpoint(1, 0x4b9488);
}

/* FUN_004b94a8 @ 0x004b94a8  (est. sk_swift_set_storage_fatal)
 * Ghidra: void FUN_004b94a8(void)
 * Swift fatal: Swift.SetStorage's _RawSetStorage placeholder init; traps at
 * 0x4b94e8. Does not return. Confidence: low */
static void sk_swift_set_storage_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.SetStorage", 0x16,
                        (unsigned long)"Swift._RawSetStorage", 0x15,
                        (unsigned long)"init", 6, 0x1a, 0x10);
    SoftwareBreakpoint(1, 0x4b94e8);
}

/* FUN_004b9488 @ 0x004b9488  (est. sk_swift_set_storage_fatal2)
 * Ghidra: void FUN_004b9488(void)
 * Swift fatal for _RawSetStorage (with continuation); traps at 0x4b94e8.
 * Does not return. Confidence: low */
static void sk_swift_set_storage_fatal2(void)
{
    unsigned long stack_slot;
    sk_swift_set_runtime_enter();                  /* FUN_0036a9a0 */
    sk_swift_set_storage_fatal();
    stack_slot = (unsigned long)&stack_slot;
    sk_swift_type_fatal((unsigned long)"Swift.SetStorage", 0x16,
                        (unsigned long)"Swift._RawSetStorage", 0x15,
                        (unsigned long)"init", 6, 0x1a, 0x10,
                        stack_slot, (unsigned long)sk_swift_set_storage_fatal);
    SoftwareBreakpoint(1, 0x4b94e8);
}

/* FUN_004b94e8 @ 0x004b94e8  (est. sk_swift_native_nsarray_fatal)
 * Ghidra: void FUN_004b94e8(void)
 * Swift fatal: Swift.SwiftNativeNSArray's _ContiguousArrayStorageBase
 * placeholder init; traps at 0x4b9528. Does not return. Confidence: low */
static void sk_swift_native_nsarray_fatal(void)
{
    sk_swift_type_fatal((unsigned long)"Swift.SwiftNativeNSArray", 0x1e,
                        (unsigned long)"Swift._ContiguousArrayStorageBase", 0x22,
                        (unsigned long)"init", 6, 0x207, 0x10);
    SoftwareBreakpoint(1, 0x4b9528);
}

/* FUN_004b9528 @ 0x004b9528  (est. sk_stackshot_registry_refill)
 * Ghidra: void FUN_004b9528(void)
 * Refills the stackshot registry (lock at 0x657740): if acquire succeeds,
 * performs the refill helper then releases. Confidence: medium */
static void sk_stackshot_registry_refill(void)
{
    int r;
    r = sk_mutex_acquire((char *)0x657740);
    if (r != 0) {
        sk_lock_pool_refill();                     /* FUN_0035b644 */
        sk_mutex_release_broadcast((unsigned int *)0x657740);
    }
}

/* FUN_004b9568 @ 0x004b9568  (est. sk_meta_decode_next)
 * Ghidra: void FUN_004b9568(undefined8 param_1, ulong *param_2, long *param_3,
 *                  long param_4)
 * Advances a Mach-O/Swift metadata stream: reads a tagged value at *param_2
 * (low 3 bytes = length, top byte = dispatch selector), bumps the stream and
 * byte-offset pointers, and if the decoded index is in range dispatches into
 * the metadata decoder at 0x679ac0. Confidence: low */
static void sk_meta_decode_next(unsigned long out, unsigned long *stream,
                                long *offset, long base)
{
    unsigned long hdr;
    unsigned long *p;
    unsigned long word0, word1, word2;
    unsigned long off, idx, next;
    unsigned long local_58;
    long local_60;

    hdr = *stream;
    p = (unsigned long *)((hdr + 8) & 0x7fffffffffffffff);
    word0 = *p;
    word1 = p[1];
    word2 = p[2];
    next = hdr + 0x20;
    local_60 = *offset;
    off = (*(unsigned long (**)(unsigned long))(hdr & 0x7fffffffffffffff))(base + local_60);
    *stream = next + word1 + word0 * 8;
    *offset = *offset + word2;
    if ((off & 0xffffffff) < word0) {
        local_58 = next + word0 * 8 +
                   *(long *)((next & 0x7fffffffffffffff) + (off & 0xffffffff) * 8);
        sk_meta_decode_sub(out, &local_58, &local_60, base);   /* FUN_004b9634 */
    }
}

/* FUN_004b9634 @ 0x004b9634  (est. sk_meta_decode_sub)
 * Ghidra: void FUN_004b9634(undefined8 param_1, ulong *param_2, long *param_3,
 *                  undefined8 param_4)
 * Recursive Mach-O metadata decoder: reads a length-prefixed element from the
 * stream, advances the pointers, and while the top byte (dispatch selector) is
 * nonzero invokes the corresponding decoder from the 0x679ac0 dispatch table.
 * Confidence: low */
static void sk_meta_decode_sub(unsigned long out, unsigned long *stream,
                               long *offset, unsigned long base)
{
    unsigned long v;
    v = *(unsigned long *)(*stream & 0x7fffffffffffffff);
    *stream = *stream + 8;
    *offset = *offset + (v & 0xffffffffffffff);
    while (v >> 0x38 != 0) {
        (*(void (**)(unsigned long, unsigned long *, long *, unsigned long))
            ((v >> 0x38) * 8 + 0x679ac0))(out, stream, offset, base);
        v = *(unsigned long *)(*stream & 0x7fffffffffffffff);
        *stream = *stream + 8;
        *offset = *offset + (v & 0xffffffffffffff);
    }
}

/* FUN_004b9704 @ 0x004b9704  (est. sk_meta_decode_copy)
 * Ghidra: void FUN_004b9704(void)  [uses unaff_x19/x20/x21/x22]
 * Metadata decoder copy loop: walks the tagged stream in x22, copies each
 * length-prefixed element from the x19 source base to the x20 destination
 * base (offset in x21), and dispatches on the top byte via the 0x679ac0
 * table. Register inputs are carried across the decoder. Confidence: low */
static void sk_meta_decode_copy(unsigned long x19_src, unsigned long x20_dst,
                                long *x21_off, unsigned long *x22_stream,
                                unsigned long x9_cb)
{
    long base_off;
    unsigned long word, len;

    sk_meta_decode_begin();                        /* FUN_00361308 */
    while (true) {
        base_off = *x21_off;
        word = *(unsigned long *)(*x22_stream & 0x7fffffffffffffff);
        *x22_stream = *x22_stream + 8;
        len = word & 0xffffffffffffff;
        if (len != 0) {
            sk_memcpy_n((void *)(x20_dst + base_off), (void *)(x19_src + base_off), len);
        }
        *x21_off = len + base_off;
        if (word >> 0x38 == 0) {
            break;
        }
        sk_meta_decode_dispatch();                 /* FUN_003612f0 */
        (*(void (*)(void))x9_cb)();
    }
}

/* FUN_004b97b4 @ 0x004b97b4  (est. sk_meta_decode_merge)
 * Ghidra: void FUN_004b97b4(undefined8 param_1, ulong *param_2, long *param_3,
 *                  long param_4, long param_5)
 * Metadata decoder merge: reads a three-word descriptor, calls a comparator
 * on the two payload offsets, and conditionally walks/decodes elements (via
 * 004b992c or the 0x679ac0 table) before copying the merged run and advancing
 * the stream. Confidence: low */
static void sk_meta_decode_merge(unsigned long out, unsigned long *stream,
                                 long *offset, long a, long b)
{
    unsigned long *p;
    unsigned long (*cmp)(unsigned long);
    long w1, w2;
    int ra, rb;
    unsigned long head;
    unsigned long next;
    unsigned long local_70;
    long local_68;

    p = (unsigned long *)(*stream & 0x7fffffffffffffff);
    cmp = (unsigned long (*)(unsigned long))*p;
    w1 = p[1];
    w2 = p[2];
    head = *stream + 0x18;
    local_70 = head;
    ra = (int)cmp(b + *offset);
    rb = (int)cmp(a + *offset);
    next = head;
    if (ra != 0 || rb != 0) {
        if (ra == 0) {
            if (w1 != 0) {
                do {
                    sk_meta_decode_slot(out, &local_70, offset, a, b);  /* FUN_004b992c */
                    next = local_70;
                } while ((local_70 & 0x7fffffffffffffff) <
                         (head & 0x7fffffffffffffff) + w1);
            }
        } else {
            if (rb == 0) {
                local_68 = *offset;
                if (w1 != 0) {
                    unsigned long *it;
                    unsigned long *end;
                    it = (unsigned long *)(head & 0x7fffffffffffffff);
                    end = (unsigned long *)((unsigned long)it + w1);
                    next = head;
                    do {
                        next = next + 8;
                        local_68 = local_68 + (*it & 0xffffffffffffff);
                        head = *it >> 0x38;
                        if (head != 0) {
                            (*(void (**)(unsigned long, unsigned long *, long *,
                                         unsigned long))(head * 8 + 0x679ac0))
                                (out, &next, &local_68, a);
                        }
                        it = (unsigned long *)(next & 0x7fffffffffffffff);
                    } while (it < end);
                }
            } else {
                next = head + w1;
            }
            sk_memcpy_n((void *)(a + *offset), (void *)(b + *offset), w2);
            *offset = *offset + w2;
            next = next;
        }
    }
    *stream = next;
}

/* FUN_004b992c @ 0x004b992c  (est. sk_meta_decode_slot)
 * Ghidra: void FUN_004b992c(undefined8 param_1, undefined8 param_2, long *param_3)
 *   [called with 5 args: out, stream, offset, a, b; uses unaff_x19/x20/x21]
 * Metadata decoder slot: reads a length-prefixed element from the stream,
 * copies it between the a/b payload bases at *offset (register x19/x20 in the
 * original), bumps the offset, and if the top byte selects a dispatch calls
 * the 0x679c30 table entry. Confidence: low */
static void sk_meta_decode_slot(unsigned long out, unsigned long *stream,
                                long *offset, unsigned long a, unsigned long b)
{
    unsigned long word, len, cb;
    long base_off;
    void (*dispatch)(void);

    sk_meta_decode_begin();                        /* FUN_00361308 */
    word = *(unsigned long *)(*stream & 0x7fffffffffffffff);
    *stream = *stream + 8;
    base_off = *offset;
    len = word & 0xffffffffffffff;
    if (len != 0) {
        /* unaff_x20 (a) + base_off <- unaff_x19 (b) + base_off */
        sk_memcpy_n((void *)(a + base_off), (void *)(b + base_off), len);
    }
    *offset = base_off + len;   /* *unaff_x21 = lVar3 + uVar1 */
    cb = word >> 0x38;
    if (cb != 0) {
        dispatch = *(void (**)(void))(cb * 8 + 0x679c30);
        sk_meta_decode_dispatch();                 /* FUN_003612f0 */
        dispatch();
    }
}

/* FUN_004b99dc @ 0x004b99dc  (est. sk_meta_decode_single)
 * Ghidra: void FUN_004b99dc(undefined8 param_1, ulong *param_2, long *param_3)
 * Metadata decoder single element: reads a length-prefixed element and, when
 * the top byte selects dispatch selector 1, hits bad-instruction data (the
 * decompiler truncated control flow here); default returns. Confidence: low */
static void sk_meta_decode_single(unsigned long out, unsigned long *stream,
                                  long *offset)
{
    unsigned long v;
    v = *(unsigned long *)(*stream & 0x7fffffffffffffff);
    *stream = *stream + 8;
    *offset = *offset + (v & 0xffffffffffffff);
    switch (v >> 0x38) {
    case 1:
        /* WARNING: bad instruction — decompiler truncated control flow */
        break;
    default:
        return;
    }
}

/* FUN_004b9a28 @ 0x004b9a28  (est. sk_meta_decode_copy2)
 * Ghidra: void FUN_004b9a28(void)  [uses unaff_x19/x20/x21/x22]
 * Metadata decoder copy loop (variant of 004b9704 that re-reads the offset
 * after each copy). Walks the x22 stream, copies length-prefixed elements
 * between x19/x20, dispatches on the top byte. Confidence: low */
static void sk_meta_decode_copy2(unsigned long x19_src, unsigned long x20_dst,
                                 long *x21_off, unsigned long *x22_stream,
                                 unsigned long x9_cb)
{
    long base_off;
    unsigned long word, len;

    sk_meta_decode_begin();                        /* FUN_00361308 */
    while (true) {
        base_off = *x21_off;
        word = *(unsigned long *)(*x22_stream & 0x7fffffffffffffff);
        *x22_stream = *x22_stream + 8;
        len = word & 0xffffffffffffff;
        if (len != 0) {
            sk_memcpy_n((void *)(x20_dst + base_off), (void *)(x19_src + base_off), len);
            base_off = *x21_off;
        }
        *x21_off = base_off + len;
        if (word >> 0x38 == 0) {
            break;
        }
        sk_meta_decode_dispatch();                 /* FUN_003612f0 */
        (*(void (*)(void))x9_cb)();
    }
}

/* FUN_004b9ac8 @ 0x004b9ac8  (est. sk_stackshot_state_set_a)
 * Ghidra: void FUN_004b9ac8(undefined8 param_1)
 * Stores a stackshot state value: acquires the lock at 0x6c0258 and, on
 * success, records param_1 into global _DAT_006c0250 via the state store then
 * releases. Confidence: medium */
static void sk_stackshot_state_set_a(unsigned long v)
{
    int r;
    r = sk_mutex_acquire((char *)0x6c0258);
    if (r != 0) {
        _DAT_006c0250 = sk_stackshot_state_store(v, (unsigned long)0x60ce80);  /* FUN_0039c740 */
        sk_mutex_release_broadcast((unsigned int *)0x6c0258);
    }
}

/* FUN_004b9b38 @ 0x004b9b38  (est. sk_swift_generic_dispatch)
 * Ghidra: void FUN_004b9b38(undefined8 param_1, undefined8 param_2)
 * Swift runtime generic dispatch: boxes both arguments (type-init), checks a
 * conditional flag, and either invokes the fatal path or a callback before
 * re-releasing the boxes. Confidence: low */
static void sk_swift_generic_dispatch(unsigned long a, unsigned long b)
{
    unsigned long box[2];
    char tag[8];
    char cStack_49;
    unsigned char extra[24];
    unsigned long **p;
    int r;

    sk_swift_box_init(box, a, 1);                  /* FUN_00361320(box,a,1) */
    sk_swift_box_init(extra, b, 1);                /* FUN_00361320(extra,b,1) */
    r = sk_swift_is_conditional();                 /* FUN_0000456c */
    p = (unsigned long **)box[0];
    if (-1 < cStack_49) {
        p = (unsigned long **)box;
    }
    if (r == 0) {
        sk_swift_box_release(p);                   /* FUN_00368298 */
        sk_swift_fatal(0);                         /* FUN_00369bb0 noreturn */
    }
    sk_swift_box_release(p);                       /* FUN_00368298 */
    sk_stackshot_obj_enter2(0);                    /* FUN_004b9ed8(0) */
    if (cStack_49 < 0) {
        thunk_FUN_00012568(box[0], ((unsigned long)(unsigned char)cStack_49 << 56) | 0);
    }
}

/* FUN_004b9c0c @ 0x004b9c0c  (est. sk_stackshot_state_set_b)
 * Ghidra: void FUN_004b9c0c(undefined8 param_1)
 * Stores a stackshot state value (lock at 0x6c0278, global _DAT_006c0270).
 * Confidence: medium */
static void sk_stackshot_state_set_b(unsigned long v)
{
    int r;
    r = sk_mutex_acquire((char *)0x6c0278);
    if (r != 0) {
        _DAT_006c0270 = sk_stackshot_state_store(v, (unsigned long)0x60ce80);  /* FUN_0039c740 */
        sk_mutex_release_broadcast((unsigned int *)0x6c0278);
    }
}

/* FUN_004b9c78 @ 0x004b9c78  (est. sk_stackshot_unavailable)
 * Ghidra: void FUN_004b9c78(undefined8 param_1, undefined8 param_2, int param_3)
 * Stackshot value printer: if the flag is nonzero logs "<unavailable>",
 * otherwise starts the " %4u: 0x%0*16tx " header line. Confidence: medium */
static void sk_stackshot_unavailable(unsigned long a, unsigned long b, int flag)
{
    if (flag != 0) {
        sk_log_fixed("<unavailable>", 0xd, 1);    /* s_<unavailable>_005d43f2 */
        return;
    }
    sk_log_start(0xeb1a02bf914012baULL, " %4u: 0x%0*16tx ");  /* s___4u_0x_0_16tx_005d4400 */
}

/* FUN_004b9ccc @ 0x004b9ccc  (est. sk_backtrace_unavailable)
 * Ghidra: void FUN_004b9ccc(undefined4 param_1)
 * Emits a "backtrace unavailable" frame: initializes a backtrace frame with
 * the given code, runs the frame printer, logs "<backtrace_unavailable>", and
 * validates the stack canary. Confidence: medium */
static void sk_backtrace_unavailable(unsigned int code)
{
    unsigned long canary = -0x2c8502b44bfffed6;
    unsigned int code_slot;
    unsigned long frame;
    unsigned int *pslot;
    unsigned long *pframe;
    long local_18;

    local_18 = canary;
    pframe = &frame;
    pslot = &code_slot;
    frame = 0x67a468;                              /* backtrace frame header */
    code_slot = code;
    sk_backtrace_frame(&frame);                    /* FUN_00369d48 */
    sk_log_fixed("<backtrace_unavailable>", 0x18, 1, 0xeb1a02bf914012baULL);  /* s_<backtrace_unavailable>_005d4410 */
    if (local_18 != canary) {
        sk_stack_check_fail();                     /* FUN_0011d7e8 */
    }
}

/* FUN_004b9df8 @ 0x004b9df8  (est. sk_stackshot_key_begin)
 * Ghidra: void FUN_004b9df8(undefined8 param_1)
 * Begins a stackshot keyed log section: pushes the key and starts the line.
 * Confidence: medium */
static void sk_stackshot_key_begin(unsigned long key)
{
    sk_log_push(key, 0xeb1a02bf914012baULL);      /* FUN_0011883c */
    sk_log_begin(0xeb1a02bf914012baULL);          /* FUN_0011858c */
}

/* FUN_004b9e2c @ 0x004b9e2c  (est. sk_stackshot_obj_enter)
 * Ghidra: void FUN_004b9e2c(undefined8 param_1, undefined8 param_2,
 *                  undefined8 param_3)
 * Enters a stackshot object: looks up a named object via sk_sys_object_lookup
 * (raising a fault on the found index), then begins the keyed log section and
 * releases the object reference. Confidence: medium */
static void sk_stackshot_obj_enter(unsigned long a, unsigned long b, unsigned long c)
{
    int r;
    unsigned long ref;

    r = sk_sys_object_lookup(0, 0, b, c);          /* FUN_00116bb4 */
    if (-1 < r) {
        ref = sk_raise_bad(r + 1, 0x100004077774924);  /* FUN_000101a0 (returns ref) */
        if ((ref == 0) ||
            (r = sk_sys_object_lookup(ref, r + 1, b, c), -1 < r)) {
            goto done;
        }
        thunk_FUN_00012568(ref);
    }
    ref = 0;
done:
    sk_stackshot_key_begin(ref);                   /* FUN_004b9df8 */
    thunk_FUN_00012568(ref);
}

/* FUN_004b9ed8 @ 0x004b9ed8  (est. sk_stackshot_obj_enter2)
 * Ghidra: void FUN_004b9ed8(undefined8 param_1, undefined8 param_2)
 * Enters a stackshot object (two-arg wrapper of 004b9e2c with a null third
 * argument). Confidence: medium */
static void sk_stackshot_obj_enter2(unsigned long a)
{
    sk_stackshot_obj_enter(a, 0, 0);
}

/* FUN_004b9d68 @ 0x004b9d68  (est. sk_stackshot_registry_enter)
 * Ghidra: void FUN_004b9d68(undefined8 param_1, undefined8 param_2)
 * Enters the stackshot registry: begins the key, spins on the global registry
 * slot (resolving or popping the next entry), stores the resolved value, then
 * asserts. Confidence: low */
static void sk_stackshot_registry_enter(unsigned long a, unsigned long b)
{
    long l;
    unsigned long local_38;

    sk_stackshot_key_begin(b);                     /* FUN_004b9df8 */
    local_38 = 0;
    do {
        l = _DAT_006c0280;
        thunk_FUN_00012568(local_38);
        if (l == 0) {
            local_38 = sk_stackshot_registry_get(b);   /* FUN_00118cf8 */
        } else {
            sk_stackshot_registry_pop(&local_38);      /* FUN_00369ca0 */
        }
    } while (_DAT_006c0280 != l);
    _DAT_006c0280 = local_38;
    sk_security_assert((const char *)0x5aa8b2);    /* FUN_001150e0(&DAT_005aa8b2) */
}

/* FUN_004b9f04 @ 0x004b9f04  (est. sk_stackshot_value_dump)
 * Ghidra: void FUN_004b9f04(undefined8 param_1)
 * Stackshot value dump: marks the value unavailable then starts the "0x%lx "
 * value line. Confidence: medium */
static void sk_stackshot_value_dump(unsigned long v)
{
    sk_stackshot_unavailable(0, v, 1);             /* FUN_004b9c78(0,v,1) */
    sk_log_start(0xeb1a02bf914012baULL, "0x%lx "); /* s__0x_lx___005d469d */
}

/* FUN_004b9f58 @ 0x004b9f58  (est. sk_stackshot_unknown)
 * Ghidra: void FUN_004b9f58(void)
 * Stackshot: logs the "<unknown>" placeholder. Confidence: medium */
static void sk_stackshot_unknown(void)
{
    sk_log_fixed("<unknown>", 0xb, 1, 0xeb1a02bf914012baULL);  /* s_<unknown>__005d46a8 */
}

/* FUN_004b9f8c @ 0x004b9f8c  (est. sk_swift_deinit_object)
 * Ghidra: void FUN_004b9f8c(long *param_1)
 * Swift object deallocation fatal: resolves the object pointer (or null),
 * runs the deallocator, then panics with the "Object 0x%p of class %s
 * deallocate..." message. Does not return. Confidence: medium */
static void sk_swift_deinit_object(long *obj)
{
    long p;
    p = *obj;
    if (p == 0) {
        p = 0;
    }
    sk_swift_dealloc(p);                           /* FUN_0035bd48 */
    sk_swift_fatal(0, "Object 0x%p of class %s deallocate...");  /* FUN_00369bb0 + s_Object__p_of_class__s_deallocate_005d47ea */
}

/* FUN_004ba00c @ 0x004ba00c  (est. sk_stackshot_registry_update)
 * Ghidra: void FUN_004ba00c(void)
 * Updates the stackshot registry pointer: acquires the lock at 0x657740 and,
 * on success, stores the current registry value (from _DAT_006adf08 or a
 * sentinel) into the 0x657738 global, then releases. Confidence: medium */
static void sk_stackshot_registry_update(void)
{
    int r;
    r = sk_mutex_acquire((char *)0x657740);
    if (r != 0) {
        lRam0000000000657738 = -0xae502812aa7333;   /* global at 0x657738 */
        if (_DAT_006adf08 != 0) {
            lRam0000000000657738 = _DAT_006adf08;
        }
        sk_mutex_release_broadcast((unsigned int *)0x657740);
    }
}

/* FUN_004ba070 @ 0x004ba070  (est. sk_prespecializations_report)
 * Ghidra: void FUN_004ba070(void)
 * Prespecializations report: reads the prespecialization library value and
 * logs the "Prespecializations library: Retu..." message. Confidence: medium */
static void sk_prespecializations_report(void)
{
    unsigned long v;
    v = sk_prespecializations_get();               /* FUN_0036e51c */
    sk_log_start(v, "Prespecializations library: Retu...");  /* s_Prespecializations_library__Retu_005d4c58 */
}

/* internal helper: metadata setter used by the box pre-step (FUN_0036a940) */
static void sk_swift_meta_set_from_stream(void)
{
    sk_swift_meta_set(0, 0, 0);                    /* FUN_0036a940() */
}
