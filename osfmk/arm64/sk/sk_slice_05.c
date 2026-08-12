/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * Slice 0x258c8-0x2e7c4: Tightbeam message codec continuation plus the VAS
 * (Virtual Address Space) fault-handler registry — the exclave-side easm
 * (event async state machine) faulthandler subsystem: a typed, reference-
 * counted table of faulthandler records keyed by region address, driven by a
 * method-dispatch table (FUN_0004b520) and a round-robin free-list allocator
 * for the async request slots (records at +0x1f0..+0x208). cL4/seL4 vocab.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/*-------------------------------------------------------------------------
 * Out-of-range helpers (reconstructed by sibling SK workers; declared extern
 * with their FUN_ address in a comment). Concrete signatures; pointer args
 * are cast to (unsigned long) at call sites.
 *------------------------------------------------------------------------- */
extern void sk_swift_fatal(const char *fmt, ...) __attribute__((noreturn));   /* FUN_004afae4 */
extern void sk_fatal_unavail(const char *msg, ...) __attribute__((noreturn)); /* FUN_001afa84 */
extern void sk_stack_chk_fail(void) __attribute__((noreturn));                /* FUN_0011d7e8 */
extern void sk_printf(const char *msg);                                       /* FUN_00118b28 */
extern void sk_boot_panic(void) __attribute__((noreturn));                    /* FUN_00054354 */
extern void sk_swift_epilogue(void);                                          /* FUN_00025704 */
extern void cl4_release(void *ptr);                                           /* FUN_0036b118 */
extern unsigned long cl4_retain(void *ptr);                                   /* FUN_0036b270 */
extern void cl4_release_op(void *ptr);                                        /* FUN_0036b6ac */
extern void sk_lock_unref(void);                                              /* FUN_0036b21c */
extern unsigned long cl4_alloc_object(unsigned long, ...);                    /* FUN_0036a940 */
extern unsigned long cl4_alloc_value(unsigned long, ...);                     /* FUN_0036a804 */
extern unsigned long cl4_log_alloc(unsigned long, unsigned long);             /* FUN_0036a9a0 */
extern unsigned long sk_alloc_vas(unsigned long);                             /* FUN_000101a0 */
extern unsigned long sk_zone_alloc_obj(unsigned long, unsigned long, unsigned long); /* FUN_00010244 */
extern unsigned long sk_realloc(unsigned long, unsigned long, unsigned long); /* FUN_000102f4 */
extern long sk_msg_init(unsigned long, void *, unsigned long, unsigned long, unsigned long); /* FUN_00014bd4 */
extern long sk_msg_decode(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_0001485c */
extern unsigned long sk_error_obj(unsigned long);                             /* FUN_00019aac */
extern unsigned long sk_phys_alloc(void);                                     /* FUN_00034f70 */
extern unsigned long sk_boot_object(void);                                    /* FUN_00034a2c */
extern unsigned long sk_spanmap_get3(void *);                                 /* FUN_00036008 */
extern int sk_page_check(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_0003c4c0 */
extern unsigned long sk_current_domain(unsigned long, ...);                   /* FUN_00389b64 */
extern unsigned long sk_obj_lock2(unsigned long);                             /* FUN_00310d68 */
extern unsigned long sk_dispatch_async(unsigned long, ...);                   /* FUN_0004b520 */
extern void sk_dispatch_free(unsigned long);                                  /* FUN_0004b664 */
extern void sk_mtx_lock(unsigned long);                                       /* FUN_00118164 */
extern void sk_mtx_unlock(unsigned long);                                     /* FUN_00118194 */
extern void cl4_destroy_elem(unsigned long);                                  /* FUN_004b23d8 */
extern unsigned long sk_obj_reg_get(unsigned long, ...);                      /* FUN_00376820 */
extern unsigned long sk_lock_acquire(unsigned long, unsigned long, unsigned long, void *, void *); /* FUN_00377824 */
extern void cl4_log_emit(unsigned long);                                      /* FUN_0036b588 */
extern void cl4_log_fmt(unsigned long);                                       /* FUN_003a25d4 */
extern void cl4_trace_begin(unsigned long);                                   /* FUN_002a4ab4 */
extern void sk_tb_async_dispatch(void *, void *, void *);                     /* FUN_00408db8 */
extern void sk_tb_async_release(unsigned long);                               /* FUN_0040bd24 */
extern unsigned long cl4_mmu_op(unsigned long, ...);                          /* FUN_0001a1c8 */
extern unsigned long sk_tb_get(void);                                         /* FUN_000159b8 */
extern void sk_tb_storage_deinit(unsigned long *);                            /* FUN_0001fd9c */
extern void sk_tb_metadata_call(unsigned long, unsigned long, unsigned long); /* FUN_003ed2dc */
extern void sk_tb_error_push(unsigned long);                                  /* FUN_002acbb8 */
extern unsigned long sk_vas_register(unsigned long, unsigned long);           /* FUN_000147a0 */
extern unsigned long sk_f_00002534(unsigned long, ...);                       /* FUN_00002534 */
extern unsigned long sk_rt_003698b0(unsigned long, ...);                      /* FUN_003698b0 */
extern unsigned long sk_rt_006f6b4(unsigned long, ...);                       /* FUN_0006f6b4 */
extern unsigned long sk_rt_0019e410(unsigned long, ...);                      /* FUN_0019e410 */
extern unsigned long sk_rt_0019e538(unsigned long, ...);                      /* FUN_0019e538 */
extern unsigned long sk_rt_0019e578(unsigned long, ...);                      /* FUN_0019e578 */
extern unsigned long sk_rt_001a0414(unsigned long, ...);                      /* FUN_001a0414 */
extern unsigned long sk_rt_0019ea20(unsigned long, ...);                      /* FUN_0019ea20 */
extern unsigned long sk_rt_0019dd10(unsigned long, ...);                      /* FUN_0019dd10 */
extern unsigned long sk_rt_0026b434(unsigned long, ...);                      /* FUN_0026b434 */
extern unsigned long sk_rt_001ee9f4(unsigned long, ...);                      /* FUN_001ee9f4 */
extern unsigned long sk_rt_00117d68(unsigned long, ...);                      /* FUN_00117d68 */
extern unsigned long sk_rt_000465c4(unsigned long, ...);                      /* FUN_000465c4 */
extern unsigned long sk_rt_0005ab94(unsigned long, ...);                      /* FUN_0005ab94 */
extern unsigned long sk_rt_00031a8c(unsigned long, ...);                      /* FUN_00031a8c */
extern unsigned long sk_rt_00035ba0(unsigned long, ...);                      /* FUN_00035ba0 */
extern unsigned long sk_rt_00045cd8(unsigned long, ...);                      /* FUN_00045cd8 */
extern unsigned long sk_rt_00045ce8(unsigned long, ...);                      /* FUN_00045ce8 */
extern unsigned long sk_rt_00045d08(unsigned long, ...);                      /* FUN_00045d08 */
extern unsigned long sk_rt_00045d38(unsigned long, ...);                      /* FUN_00045d38 */
extern unsigned long sk_rt_00046288(unsigned long, ...);                      /* FUN_00046288 */
extern unsigned long sk_rt_000462a0(unsigned long, ...);                      /* FUN_000462a0 */
extern unsigned long sk_rt_000462c8(unsigned long, ...);                      /* FUN_000462c8 */
extern unsigned long sk_rt_000462e0(unsigned long, ...);                      /* FUN_000462e0 */
extern unsigned long sk_rt_000462e8(unsigned long, ...);                      /* FUN_000462e8 */
extern unsigned long sk_rt_000462f8(unsigned long, ...);                      /* FUN_000462f8 */
extern unsigned long sk_rt_00046304(unsigned long, ...);                      /* FUN_00046304 */
extern unsigned long sk_rt_00046314(unsigned long, ...);                      /* FUN_00046314 */
extern unsigned long sk_rt_00046320(unsigned long, ...);                      /* FUN_00046320 */
extern unsigned long sk_rt_00046340(unsigned long, ...);                      /* FUN_00046340 */
extern unsigned long sk_rt_0004636c(unsigned long, ...);                      /* FUN_0004636c */
extern unsigned long sk_rt_00046380(unsigned long, ...);                      /* FUN_00046380 */
extern unsigned long sk_rt_0004b710(unsigned long, ...);                      /* FUN_0004b710 */
extern unsigned long sk_rt_0004b8d0(unsigned long, ...);                      /* FUN_0004b8d0 */
extern unsigned long sk_rt_0040bb18(unsigned long, ...);                      /* FUN_0040bb18 */
extern unsigned long sk_rt_004b1a74(unsigned long, ...);                      /* FUN_004b1a74 */
extern unsigned long sk_rt_004b1aac(unsigned long, ...);                      /* FUN_004b1aac */
extern unsigned long sk_rt_004b1ae8(unsigned long, ...);                      /* FUN_004b1ae8 */
extern unsigned long sk_rt_004b1b24(unsigned long, ...);                      /* FUN_004b1b24 */
extern unsigned long sk_rt_004b1b60(unsigned long, ...);                      /* FUN_004b1b60 */
extern unsigned long sk_rt_004b1b9c(unsigned long, ...);                      /* FUN_004b1b9c */
extern unsigned long sk_rt_004b1bd8(unsigned long, ...);                      /* FUN_004b1bd8 */
extern unsigned long sk_rt_004b1c10(unsigned long, ...);                      /* FUN_004b1c10 */
extern unsigned long sk_rt_0001612c(unsigned long, ...);                      /* FUN_0001612c */
extern unsigned long sk_rt_00023c78(unsigned long, ...);                      /* FUN_00023c78 */
extern unsigned long sk_rt_00023d00(unsigned long, ...);                      /* FUN_00023d00 */
extern unsigned long sk_rt_00014804(void);                                    /* FUN_00014804 */
extern unsigned long sk_rt_0001483c(void);                                    /* FUN_0001483c */
extern unsigned long sk_rt_0001532c(unsigned long, ...);                      /* FUN_0001532c */
extern unsigned long sk_rt_00015388(unsigned long, ...);                      /* FUN_00015388 */
extern unsigned long sk_rt_00015708(void);                                    /* FUN_00015708 */
extern unsigned long sk_rt_00014578(unsigned long, ...);                      /* FUN_00014578 */
extern unsigned long sk_rt_000248a4(unsigned long, ...);                      /* FUN_000248a4 */
extern unsigned long sk_rt_00310d80(unsigned long, ...);                      /* FUN_00310d80 */
extern unsigned long sk_rt_00024678(unsigned long, ...);                      /* FUN_00024678 */
extern unsigned long sk_rt_002a4ab4(unsigned long, ...);                      /* FUN_002a4ab4 */
extern unsigned long sk_rt_002acbb8(unsigned long, ...);                      /* FUN_002acbb8 */
extern unsigned long sk_rt_001afa84(unsigned long, ...);                      /* FUN_001afa84 */
extern unsigned long sk_indirect_call(unsigned long, ...);   /* opaque indirect Swift call */

/*-------------------------------------------------------------------------
 * Out-of-range global metadata / string-table addresses (opaque externs).
 *------------------------------------------------------------------------- */
extern unsigned long DAT_0064c2d8, DAT_0064c2e0;
extern unsigned long DAT_004bb180, DAT_004bbfd8, DAT_004bbfe0, DAT_004bbfe8, DAT_004bb178;
extern unsigned long DAT_004bbc24, DAT_004bbe30, DAT_004bbf40, DAT_004bbfcc, DAT_004bbfd0;
extern unsigned long DAT_0064c040, DAT_004bbf40, DAT_004ea760, DAT_004edbbc;
extern unsigned long DAT_0060e208, DAT_0060e230, DAT_00611b24, DAT_00611b34;
extern unsigned long DAT_004bc000, DAT_004bc008, DAT_004bc010, DAT_004bc018;
extern unsigned long DAT_0064cb40, DAT_0064cb48, DAT_0064cb80;
extern unsigned long DAT_0065b1a0, DAT_0065b1c0, DAT_0065b1e0, DAT_0065b300, DAT_0065b320;
extern unsigned long DAT_0065b3c0, DAT_0065b400, DAT_0065b440;
extern unsigned long DAT_0065a550, DAT_0065ae70, DAT_0065ae90, DAT_0065aeb0, DAT_0065aed0;
extern unsigned long DAT_0065aef0, DAT_0065af10, DAT_0065af30, DAT_0065af60, DAT_0065afa0;
extern unsigned long DAT_0065afe0, DAT_0065b000, DAT_0065b020, DAT_0065b040, DAT_0065b070;
extern unsigned long DAT_0065b0b0, DAT_0065b100, DAT_0065b150, DAT_0065b170, DAT_0065b1c0;
extern unsigned long DAT_0065b200, DAT_0065b230, DAT_0065b260, DAT_0065b280, DAT_0065b2b0;
extern unsigned long DAT_0065b2d0, DAT_0065b340, DAT_0065b3a0, DAT_0065b3c0, DAT_0065b3e0;
extern unsigned long DAT_0065b400, DAT_0065b420, DAT_0065b440, DAT_0065b460, DAT_0065b480;
extern unsigned long DAT_0065b4a0, DAT_0065b4c0, DAT_0065b4e0, DAT_0065b500, DAT_0065b520;
extern unsigned long DAT_0065b540, DAT_0065b560;
extern unsigned long DAT_004baeb0, DAT_004baeb8, DAT_004bb180, DAT_0067b148;
extern unsigned long DAT_004bbf40, DAT_0064c308, DAT_0064c288, DAT_0064c380;
extern unsigned long DAT_0064c040, DAT_004bbe30;
extern unsigned long DAT_0064c2e8, DAT_004edbbc;
extern unsigned long DAT_004bbfcc, DAT_00675c30;


/*-------------------------------------------------------------------------
 * Forward declarations (same-file cross references; C99 requires decls).
 *------------------------------------------------------------------------- */
void tightbeam_message_init_desc(unsigned char *, unsigned long, unsigned long, unsigned long, unsigned int *);
void tightbeam_decoder_init(unsigned char *, unsigned long);
void tightbeam_decoder_attach(unsigned long);
void tightbeam_decoder_attached_run(void);
void tightbeam_tag_mask(unsigned long *);
long tightbeam_method_4(unsigned long);
long tightbeam_method_4b(unsigned long);
unsigned long tightbeam_alloc_and_init(unsigned long, unsigned char);
void tightbeam_message_build_out(unsigned long *, unsigned long, unsigned long, unsigned int *);
void tightbeam_message_decode_into(unsigned char *, unsigned char *, int *);
void tightbeam_kind_select(unsigned long, unsigned char);
void tightbeam_ctx_store(unsigned long);
void tightbeam_frame_store(unsigned long);
unsigned long tightbeam_message_commit(unsigned long);
void tightbeam_release_msg(void);
void tightbeam_release_msg2(void);
void tightbeam_release_msg_ref(void);
void tightbeam_release_msg_ref2(void);
cl4_result_t tightbeam_type_descriptor_a(void);
void vas_iterate_objects(void (*)(void), unsigned long, unsigned long, unsigned long,
                         unsigned long, unsigned long, unsigned long, unsigned long);
void vas_codable_dispatch(unsigned long, unsigned long, unsigned long);
long tightbeam_method_4c(unsigned long);
void vas_codable_dispatch_result(void);
long tightbeam_method_8(unsigned long);
void vas_codable_call_result(unsigned long);
long tightbeam_method_4d(unsigned long);
unsigned long vas_iterate_objects_out(unsigned long, unsigned long, unsigned long);
unsigned long vas_iterate_internal(unsigned long, unsigned long, unsigned long, unsigned long,
                                   unsigned long, unsigned long);
unsigned int vas_iterate_1(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
unsigned int vas_iterate_2(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
unsigned long vas_object_call(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void vas_object_call_out(unsigned long *, unsigned int, unsigned long, unsigned long,
                         unsigned int *, unsigned long, unsigned long);
unsigned long vas_object_call2(unsigned long, unsigned long, unsigned long);
unsigned long vas_object_call2_internal(unsigned long, unsigned long, unsigned long, unsigned long,
                                        unsigned long);
unsigned int vas_object_call3(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
unsigned int vas_object_call4(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
void vas_codable_encode(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long,
                        unsigned long, unsigned int *);
void vas_codable_encode_out(unsigned long, unsigned long, unsigned long, unsigned int *,
                            unsigned long, unsigned long);
void vas_object_encode_cb(unsigned long, unsigned long, unsigned int *);
unsigned long sk_type_register(void);
unsigned long sk_lock_and_alloc(unsigned long *, long *);
unsigned long sk_type_register_inner(void);
long tightbeam_method_8b(unsigned long);
long tightbeam_method_8c(unsigned long);
long tightbeam_method_4e(unsigned long);
long sk_obj_lock_resolve(unsigned long);
long tightbeam_method_38(unsigned long);
long tightbeam_method_20(unsigned long);
long tightbeam_method_28(unsigned long);
long tightbeam_method_60(unsigned long);
void vas_server_register(void);
long vas_msg_send(unsigned long, unsigned long, unsigned long, void (*)(void));
unsigned long vas_op_invoke(unsigned long, unsigned long, unsigned long);
void vas_server_init_forward(void);
cl4_result_t vas_type_descriptor(void);
unsigned long vas_server_init(unsigned long, unsigned char, unsigned long, unsigned long,
                              unsigned long, unsigned long, unsigned long);
unsigned long vas_server_create(unsigned long, unsigned long, unsigned long, unsigned long,
                                unsigned long, unsigned long);
void vas_server_register_internal(unsigned long, unsigned long, unsigned long, unsigned long,
                                  unsigned long, unsigned long);
long vas_fault_complete(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);

/*--------------------------------------------------------------------*/
/* FUN_000258c8 @ 0x000258c8   (est. tightbeam_message_init_desc)
 * Ghidra: void FUN_000258c8(undefined1 *param_1,long param_2,undefined8,undefined8)
 * Initialises a TightbeamMessage descriptor at param_1: allocates a 0x58-byte
 * state block and a 0x68-byte buffer, runs the message constructor
 * (FUN_00015708) and the msg init (FUN_00014bd4) against the storage pointer
 * taken from param_2+0x10; on success fills the six-word descriptor, else
 * raises a Swift fatal with the TightbeamMessage string.
 * Confidence: medium (string-matched "Tightbeam TightbeamMessage swift").
 * Notes: sk_alloc_aligned(FUN_0036a804); FATAL s_Fatal_error_005accd0.
 */
void tightbeam_message_init_desc(unsigned char *desc, unsigned long owner,
                                 unsigned long a, unsigned long b,
                                 unsigned int *err)
{
    unsigned int *state;
    unsigned long buf;
    int rc;

    state = (unsigned int *)cl4_alloc_value(0x58, 0xffffffffffffffffu);
    *state = 0;
    buf = cl4_alloc_value(0x68, 0xffffffffffffffffu);
    sk_rt_00015708();                                  /* FUN_00015708 ctor */
    rc = (int)sk_msg_init(*(unsigned long *)(owner + 0x10), state, buf, a, b); /* FUN_00014bd4 */
    if (rc == 0) {
        desc[0] = 0;
        *(unsigned long *)(desc + 8) = owner;
        *(unsigned int **)(desc + 0x10) = state;
        *(unsigned long *)(desc + 0x18) = buf;
        *(unsigned long *)(desc + 0x20) = (unsigned long)cl4_mmu_op; /* FUN_0001a1c8 */
        *(unsigned long *)(desc + 0x28) = 0;
        desc[0x30] = 0;
        return;
    }
    sk_fatal_unavail("Fatal error", 0xb, 2, 0, 0xe000000000000000,
                     "Tightbeam TightbeamMessage swift", 0x20, 2, 0x102, 0); /* FUN_001afa84 */
}

/*--------------------------------------------------------------------*/
/* FUN_000259c0 @ 0x000259c0   (est. tightbeam_decoder_init)
 * Ghidra: void FUN_000259c0(undefined1 *param_1, undefined8 param_2)
 * Initialises a TightbeamDecoder descriptor (param_1): sets the kind byte to
 * 1, the data pointer to the tagged -1 marker, stores param_2 at +0x10, the
 * field-token from FUN_000159b8 at +0x18, and zeroes the rest. Ends with the
 * tail-call epilogue FUN_00025704.
 * Confidence: medium (decoder descriptor init).
 */
void tightbeam_decoder_init(unsigned char *desc, unsigned long payload)
{
    unsigned long token = sk_tb_get();                 /* FUN_000159b8 */
    desc[0] = 1;
    *(unsigned long *)(desc + 8) = 0x8000000000000000;
    *(unsigned long *)(desc + 0x10) = payload;
    *(unsigned long *)(desc + 0x20) = 0;
    *(unsigned long *)(desc + 0x28) = 0;
    *(unsigned long *)(desc + 0x18) = token;
    desc[0x30] = 1;
    sk_swift_epilogue();                               /* FUN_00025704 */
}

/*--------------------------------------------------------------------*/
/* FUN_00025a04 @ 0x00025a04   (est. tightbeam_decoder_attach)
 * Ghidra: void FUN_00025a04(undefined8 param_1)
 * Attaches a decoder continuation: allocates an async job (FUN_0040bb18)
 * wired to the captured frame context, records the run entry
 * FUN_00025ac0, and posts the decode event via FUN_00024678.
 * Confidence: low (Swift async attach; relies on frame registers).
 * Notes: DAT_004bbc24; event posted with captured frame fields.
 */
void tightbeam_decoder_attach(unsigned long payload)
{
    unsigned long ctx = *(unsigned long *)(__builtin_frame_address(0) + 0x10);
    unsigned long f3  = *(unsigned long *)(__builtin_frame_address(0) + 0x18);
    unsigned long f2  = *(unsigned long *)(__builtin_frame_address(0) + 0x20);
    unsigned long f4  = *(unsigned long *)(__builtin_frame_address(0) + 0x28);
    unsigned long f6  = *(unsigned long *)(__builtin_frame_address(0) + 0x30);
    long *job = (long *)sk_rt_0040bb18(DAT_004bbc24);
    *(long **)(__builtin_frame_address(0) + 0x10) = job;
    *job = (long)__builtin_frame_address(0);
    job[1] = (long)tightbeam_decoder_attached_run;      /* FUN_00025ac0 */
    sk_rt_00024678((unsigned long)job, payload, f2, f4, f6, ctx, f3); /* FUN_00024678 */
}

/*--------------------------------------------------------------------*/
/* FUN_00025ac0 @ 0x00025ac0   (est. tightbeam_decoder_attached_run)
 * Ghidra: void FUN_00025ac0(void)
 * Runs the attached decoder: releases the event continuation object
 * (FUN_0040bd24 on +0x10) then jumps through the event vtable (+8).
 * Unrecoverable jump table (indirect call).
 * Confidence: low (indirect jump table not recovered).
 */
void tightbeam_decoder_attached_run(void)
{
    long *frame = (long *)*((long *)__builtin_frame_address(0));
    sk_tb_async_release(*(unsigned long *)(*frame + 0x10)); /* FUN_0040bd24 */
    (*(void (**)(void))(frame + 8))();
}

/*--------------------------------------------------------------------*/
/* FUN_00025d80 @ 0x00025d80   (est. tightbeam_tag_mask)
 * Ghidra: void FUN_00025d80(ulong *param_1)
 * Clears the top three tag bits of the tagged pointer at param_1
 * (0x1fffffffffffffff mask), canonicalising a tagged reference.
 * Confidence: high (trivial bit op).
 */
void tightbeam_tag_mask(unsigned long *ptr)
{
    *ptr = *ptr & 0x1fffffffffffffff;
}

/*--------------------------------------------------------------------*/
/* FUN_00025dcc @ 0x00025dcc   (est. tightbeam_method_4)
 * Ghidra: long FUN_00025dcc(ulong param_1)
 * Swift method-table resolver: dereferences the object (clearing the low
 * isa/tag bit) and computes the method entry for slot offset 4 by adding the
 * 4-byte signed method-table delta.
 * Confidence: high (standard Swift witness-table resolution).
 */
long tightbeam_method_4(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 4) + (long)*(int *)(obj + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_00025e2c @ 0x00025e2c   (est. tightbeam_method_4b)
 * Ghidra: long FUN_00025e2c(ulong param_1)
 * Method-table resolver for slot offset 4; byte-identical to FUN_00025dcc.
 * Confidence: high (trivial witness-table resolution).
 */
long tightbeam_method_4b(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 4) + (long)*(int *)(obj + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_00025e6c @ 0x00025e6c   (est. tightbeam_alloc_and_init)
 * Ghidra: undefined8 FUN_00025e6c(undefined8, undefined8)
 * Allocates a typed object (FUN_0036a940), runs the kind-select init
 * FUN_000260e0 on it, and returns the object. The allocation result in x0
 * is preserved across the init call.
 * Confidence: low (thin alloc+init wrapper).
 */
unsigned long tightbeam_alloc_and_init(unsigned long obj, unsigned char kind)
{
    unsigned long result = cl4_alloc_object(0);         /* FUN_0036a940 */
    tightbeam_kind_select(obj, kind);                  /* FUN_000260e0 */
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00025ebc @ 0x00025ebc   (est. tightbeam_message_build_out)
 * Ghidra: void FUN_00025ebc(undefined8 *param_1, undefined8, undefined8, undefined4 *)
 * Builds a message descriptor into the six-word out-slot param_1: spins a
 * lock (FUN_0036b270), inits a message descriptor via FUN_000258c8, and on
 * success copies the six descriptor words; on failure writes the error code
 * to param_4.
 * Confidence: medium (message build-out).
 */
void tightbeam_message_build_out(unsigned long *out, unsigned long a,
                                 unsigned long b, unsigned int *err)
{
    unsigned long owner = cl4_retain(0);               /* FUN_0036b270 */
    unsigned long desc[6];
    unsigned int rc;
    unsigned char kind;
    tightbeam_message_init_desc((unsigned char *)&desc[0], owner, a, b, &rc); /* FUN_000258c8 */
    if (__builtin_frame_address(0) == 0) {
        out[1] = desc[3];
        out[0] = desc[0];
        out[3] = desc[5];
        out[2] = desc[2];
        out[5] = desc[4];
        out[4] = desc[1];
        *(unsigned char *)(out + 6) = kind;
    } else {
        *err = rc;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00025f44 @ 0x00025f44   (est. tightbeam_message_decode_into)
 * Ghidra: void FUN_00025f44(undefined1 *, undefined1 *, int *)
 * Decodes a TightbeamMessage: validates the message buffer (fatal if absent),
 * runs the decode (FUN_0001485c); if the decode consumed the whole buffer it
 * copies the five decoded words into param_1, otherwise re-inits a decoder
 * (FUN_000259c0) and copies. On error builds an error object (FUN_00019aac)
 * and reports via FUN_003698b0. Stack protector epilogue.
 * Confidence: medium (message decode path).
 */
void tightbeam_message_decode_into(unsigned char *out, unsigned char *msg, int *err)
{
    long base = 0;
    unsigned long sp = *(unsigned long *)(msg + 0x10);
    if (sp == 0)
        sk_fatal_unavail("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                         "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    int rc = (int)sk_msg_decode(*(unsigned long *)(__builtin_frame_address(0) + 0x10),
                                sp, (unsigned long)&base, 2);         /* FUN_0001485c */
    if (rc == 0) {
        if (base != 0) {
            if (sp == base) {
                unsigned long w3 = *(unsigned long *)(msg + 0x20);
                unsigned long w2 = *(unsigned long *)(msg + 0x18);
                unsigned long w4 = *(unsigned long *)(msg + 0x28);
                unsigned char k = msg[0x30];
                long len = sp;
                out[0] = msg[0];
                *(unsigned long *)(out + 8) = *(unsigned long *)(msg + 8);
                *(long *)(out + 0x10) = len;
                *(unsigned long *)(out + 0x20) = w3;
                *(unsigned long *)(out + 0x18) = w2;
                *(unsigned long *)(out + 0x28) = w4;
                out[0x30] = k;
                sk_swift_epilogue();
                return;
            }
            unsigned char newmsg[16];
            tightbeam_decoder_init(newmsg, 0);         /* FUN_000259c0 */
            sk_swift_epilogue();                       /* FUN_00025704 */
            msg = newmsg;
        }
        unsigned long w1 = *(unsigned long *)(msg + 8);
        out[0] = msg[0];
        *(unsigned long *)(out + 8) = w1;
        *(long *)(out + 0x10) = base;
        *(unsigned long *)(out + 0x20) = *(unsigned long *)(msg + 0x20);
        *(unsigned long *)(out + 0x18) = *(unsigned long *)(msg + 0x18);
        *(unsigned long *)(out + 0x28) = *(unsigned long *)(msg + 0x28);
        out[0x30] = msg[0x30];
        sk_swift_epilogue();
        return;
    }
    int code = rc;
    unsigned long eobj = sk_error_obj(0);              /* FUN_00019aac */
    sk_rt_003698b0((unsigned long)&code, eobj, DAT_0065a550);         /* FUN_003698b0 */
    sk_swift_epilogue();                               /* FUN_00025704 */
    *err = code;
    sk_stack_chk_fail();                               /* FUN_0011d7e8 */
}

/*--------------------------------------------------------------------*/
/* FUN_000260e0 @ 0x000260e0   (est. tightbeam_kind_select)
 * Ghidra: void FUN_000260e0(undefined8 param_1, byte param_2)
 * Selects a Tightbeam kind: maps the kind byte to (size, flags) and invokes
 * the typed init FUN_00015388; then stores the current-domain token
 * (FUN_00014804/FUN_0001483c) at the object's +0x10.
 * Confidence: low (kind switch / Swift enum init).
 */
void tightbeam_kind_select(unsigned long obj, unsigned char kind)
{
    unsigned long size, flags;
    if (kind < 2) {
        size = (kind == 0) ? 3 : 0xd;
        flags = 0;
    } else {
        if (kind == 2) {
            flags = 1;
        } else {
            if (kind != 3) {
                sk_rt_0001532c(1, 0);
                goto done;
            }
            flags = 8;
        }
        size = 3;
    }
    sk_rt_00015388(size, obj, flags);
done:
    *(unsigned long *)(__builtin_frame_address(0) + 0x10) = sk_rt_00014804();
    sk_rt_0001483c();
}

/*--------------------------------------------------------------------*/
/* FUN_00026174 @ 0x00026174   (est. tightbeam_ctx_store)
 * Ghidra: void FUN_00026174(undefined8 param_1)
 * Allocates a context object (FUN_0036a940) and stores param_1 at +0x10.
 * Confidence: low (alloc+store wrapper).
 */
void tightbeam_ctx_store(unsigned long value)
{
    unsigned long obj = cl4_alloc_object(0);            /* FUN_0036a940 */
    *(unsigned long *)(obj + 0x10) = value;
}

/*--------------------------------------------------------------------*/
/* FUN_000261a8 @ 0x000261a8   (est. tightbeam_frame_store)
 * Ghidra: void FUN_000261a8(undefined8 param_1)
 * Stores param_1 at the current frame's +0x10 slot.
 * Confidence: high (trivial frame store).
 */
void tightbeam_frame_store(unsigned long value)
{
    *(unsigned long *)(__builtin_frame_address(0) + 0x10) = value;
}

/*--------------------------------------------------------------------*/
/* FUN_000261b4 @ 0x000261b4   (est. tightbeam_message_commit)
 * Ghidra: undefined8 FUN_000261b4(long param_1)
 * Commits a message: if the buffer at param_1+0x10 is non-empty, decodes it
 * (FUN_0001485c), runs the epilogue, and returns the decode status; else
 * fatal. Returns 0 on success, error object/status otherwise.
 * Confidence: medium (message commit/decode).
 */
unsigned long tightbeam_message_commit(unsigned long msg)
{
    if (*(long *)(msg + 0x10) != 0) {
        unsigned long rc = sk_msg_decode(*(unsigned long *)(__builtin_frame_address(0) + 0x10),
                                         *(long *)(msg + 0x10), 0, 0); /* FUN_0001485c */
        int code = (int)rc;
        if (code == 0) {
            sk_swift_epilogue();
        } else {
            unsigned long eobj = sk_error_obj(0);      /* FUN_00019aac */
            sk_rt_003698b0((unsigned long)&code, eobj, DAT_0065a550); /* FUN_003698b0 */
            sk_swift_epilogue();
        }
        return rc;
    }
    sk_fatal_unavail("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                     "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000262a0 @ 0x000262a0   (est. tightbeam_release_msg)
 * Ghidra: void FUN_000262a0(void)
 * Releases the message buffer stored at frame +0x10 via thunk_FUN_00014578.
 * Confidence: medium (thin release wrapper).
 */
void tightbeam_release_msg(void)
{
    sk_rt_00014578(*(unsigned long *)(__builtin_frame_address(0) + 0x10)); /* thunk_FUN_00014578 */
}

/*--------------------------------------------------------------------*/
/* FUN_000262a4 @ 0x000262a4   (est. tightbeam_release_msg2)
 * Ghidra: void FUN_000262a4(void)
 * Mirror of FUN_000262a0.
 * Confidence: medium.
 */
void tightbeam_release_msg2(void)
{
    sk_rt_00014578(*(unsigned long *)(__builtin_frame_address(0) + 0x10)); /* thunk_FUN_00014578 */
}

/*--------------------------------------------------------------------*/
/* FUN_000262c0 @ 0x000262c0   (est. tightbeam_release_msg_ref)
 * Ghidra: void FUN_000262c0(void)
 * Releases the message buffer then the owning reference (FUN_0036b6ac).
 * Confidence: medium.
 */
void tightbeam_release_msg_ref(void)
{
    sk_rt_00014578(*(unsigned long *)(__builtin_frame_address(0) + 0x10)); /* thunk_FUN_00014578 */
    cl4_release_op(0);                                 /* FUN_0036b6ac */
}

/*--------------------------------------------------------------------*/
/* FUN_000262c4 @ 0x000262c4   (est. tightbeam_release_msg_ref2)
 * Ghidra: void FUN_000262c4(void)
 * Mirror of FUN_000262c0.
 * Confidence: medium.
 */
void tightbeam_release_msg_ref2(void)
{
    sk_rt_00014578(*(unsigned long *)(__builtin_frame_address(0) + 0x10)); /* thunk_FUN_00014578 */
    cl4_release_op(0);                                 /* FUN_0036b6ac */
}

/*--------------------------------------------------------------------*/
/* FUN_000262ec @ 0x000262ec   (est. tightbeam_type_descriptor_a)
 * Ghidra: undefined1 [16] FUN_000262ec(void)
 * Returns the 16-byte type descriptor pair (0x64c288, 0).
 * Confidence: low (type-metadata accessor).
 */
cl4_result_t tightbeam_type_descriptor_a(void)
{
    cl4_result_t r;
    r.lo = 0x64c288;
    r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_000262fc @ 0x000262fc   (est. vas_iterate_objects)
 * Ghidra: void FUN_000262fc(code *param_1, undefined8, undefined8, long, long,
 *                           undefined8, undefined8, undefined8)
 * Iterates the objects of a VAS container: resolves the object lock
 * (FUN_00027754) and per-key method dispatch entries, and for each element
 * walks the iteration callback (param_1) until the element count is
 * exhausted. Heavy Swift indirect-call frame; aborts via SoftwareBreakpoint
 * on out-of-contract status.
 * Confidence: low (dense indirect-call iterator).
 * Notes: sk_lock_acquire(FUN_00377824); method slots 27788/277b8/277e8/27818.
 */
void vas_iterate_objects(void (*iter)(void), unsigned long p2, unsigned long p3,
                         unsigned long p4, unsigned long p5, unsigned long p6,
                         unsigned long p7, unsigned long p8)
{
    unsigned long (*fn)(unsigned long, ...);
    unsigned long (*f28)(unsigned long, ...);
    unsigned long (*step)(unsigned long, ...);
    unsigned long (*next)(unsigned long, ...);
    unsigned long *sub;
    unsigned long count;
    long i;

    unsigned long lock = sk_obj_lock2(p6);             /* FUN_00027754 */
    unsigned long mlock = sk_lock_acquire(0, lock, p3, &DAT_00611b24, &DAT_00611b34); /* 00377824 */
    f28 = (unsigned long (*)(unsigned long, ...))tightbeam_method_38(p6);     /* FUN_00027788 */
    sub = (unsigned long *)sk_rt_001a0414(0, p4);      /* FUN_001a0414 */
    if ((long)f28(p3, p6) == 0) {
        /* empty: nothing to iterate */
    } else {
        unsigned long saved = sk_rt_006f6b4(p4);       /* FUN_0006f6b4 */
        unsigned long ctx = sk_rt_00310d80(0, p4);     /* FUN_00310d80 */
        sk_rt_0019e410((unsigned long)f28);            /* FUN_0019e410 */
        next = (unsigned long (*)(unsigned long, ...))tightbeam_method_20(p6); /* FUN_000277b8 */
        next(0, p3, p6);
        if ((long)f28 < 0) {
            /* does not return */
            sk_boot_panic();
        }
        step = (unsigned long (*)(unsigned long, ...))tightbeam_method_28(p6); /* FUN_000277e8 */
        count = (unsigned long)(long)f28;
        i = 0;
        do {
            /* element buffer */
            unsigned long elem[3];
            step((unsigned long)&elem, i, p3, p6);
            /* invoke store op */
            sk_indirect_call(0, 0, 0);
            sk_indirect_call((unsigned long)&elem, (unsigned long)&elem, 0);
            ((unsigned long (*)(unsigned long, unsigned long, unsigned long))iter)(0, 0, 0);
            sk_indirect_call(0, 0);
            sk_rt_0019e538(i, ctx);                    /* FUN_0019e538 */
            (void)tightbeam_method_60(p6);             /* FUN_00027818 */
            i++;
        } while (i != count);
        sk_rt_0019dd10(0);                              /* FUN_0019dd10 */
        sk_rt_0019e578((unsigned long)&sub, p4, ctx, 0x66b5c8);       /* FUN_0019e578 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00026754 @ 0x00026754   (est. vas_codable_dispatch)
 * Ghidra: void FUN_00026754(undefined8, undefined8, undefined8)
 * Resolves a Codable method pointer from param_3 (FUN_000267a4) and invokes
 * it with the three arguments.
 * Confidence: medium (thin method-dispatch wrapper).
 */
void vas_codable_dispatch(unsigned long a, unsigned long b, unsigned long method)
{
    unsigned long (*fn)(unsigned long, ...) = (unsigned long (*)(unsigned long, ...))tightbeam_method_4c(method); /* FUN_000267a4 */
    fn(a, b, method);
}

/*--------------------------------------------------------------------*/
/* FUN_000267a4 @ 0x000267a4   (est. tightbeam_method_4c)
 * Ghidra: long FUN_000267a4(ulong param_1)
 * Method-table resolver for slot offset 4 (Swift witness table).
 * Confidence: high (trivial witness-table resolution).
 */
long tightbeam_method_4c(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 4) + (long)*(int *)(obj + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_000267d4 @ 0x000267d4   (est. vas_codable_dispatch_result)
 * Ghidra: void FUN_000267d4(void)
 * Resolves a method from the in_x4 register (FUN_000268a0), calls it with no
 * args; on non-zero status raises a Swift fatal with the TightbeamCodable
 * string.
 * Confidence: low (result-dispatch; relies on in_x4).
 */
void vas_codable_dispatch_result(void)
{
    unsigned long code;
    unsigned long (*fn)(unsigned long, ...) = (unsigned long (*)(unsigned long, ...))tightbeam_method_8(0); /* FUN_000268a0 */
    code = (unsigned long)((unsigned int (*)(void))fn)();
    if (__builtin_frame_address(0) == 0)
        return;
    unsigned long eobj = sk_error_obj(0);              /* FUN_00019aac */
    cl4_result_t r = { eobj, DAT_0065a550 };
    r.hi = 0;
    r.lo = code;
    sk_rt_001ee9f4(r.lo, "Tightbeam TightbeamCodable swift", 0x20, 1, 0x35); /* FUN_001ee9f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_000268a0 @ 0x000268a0   (est. tightbeam_method_8)
 * Ghidra: long FUN_000268a0(ulong param_1)
 * Method-table resolver for slot offset 8.
 * Confidence: high (trivial witness-table resolution).
 */
long tightbeam_method_8(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 8) + (long)*(int *)(obj + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_000268d0 @ 0x000268d0   (est. vas_codable_call_result)
 * Ghidra: void FUN_000268d0(undefined8 param_1)
 * Resolves a method (FUN_000269a4) and calls it with param_1; on non-zero
 * status raises a Swift fatal with the TightbeamCodable string.
 * Confidence: low (result-dispatch).
 */
void vas_codable_call_result(unsigned long arg)
{
    unsigned int code;
    unsigned long (*fn)(unsigned long, ...) = (unsigned long (*)(unsigned long, ...))tightbeam_method_4d(0); /* FUN_000269a4 */
    fn(arg);
    if (__builtin_frame_address(0) == 0)
        return;
    unsigned long eobj = sk_error_obj(0);              /* FUN_00019aac */
    cl4_result_t r = { eobj, DAT_0065a550 };
    r.hi = 0;
    r.lo = code;
    sk_rt_001ee9f4(r.lo, "Tightbeam TightbeamCodable swift", 0x20, 1, 0x3e); /* FUN_001ee9f4 */
}

/*--------------------------------------------------------------------*/
/* FUN_000269a4 @ 0x000269a4   (est. tightbeam_method_4d)
 * Ghidra: long FUN_000269a4(ulong param_1)
 * Method-table resolver for slot offset 4.
 * Confidence: high (trivial witness-table resolution).
 */
long tightbeam_method_4d(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 4) + (long)*(int *)(obj + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_000269d4 @ 0x000269d4   (est. vas_iterate_objects_out)
 * Ghidra: undefined8 FUN_000269d4(undefined8, undefined8, undefined8)
 * Wraps the internal VAS iteration, writing its result into a stack slot.
 * Confidence: medium (wrapper over FUN_00026a8c).
 * Notes: method-descriptor constants 0x65a898 / 0x65a7d0.
 */
unsigned long vas_iterate_objects_out(unsigned long p1, unsigned long p2, unsigned long p3)
{
    unsigned long result = 0;
    vas_iterate_internal((unsigned long)&result, p1, p2, 0x65a898, p3, 0x65a7d0); /* FUN_00026a8c */
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026a8c @ 0x00026a8c   (est. vas_iterate_internal)
 * Ghidra: undefined8 FUN_00026a8c(undefined8, undefined8, long, undefined8,
 *                                 undefined8, undefined8)
 * Core VAS iteration: resolves the iterator method (FUN_00023c78), loops over
 * elements invoking the per-element store op (FUN_000268a0), honouring the
 * iterated count returned by FUN_0001612c. SoftwareBreakpoint on contract
 * violation.
 * Confidence: low (dense indirect-call iterator).
 */
unsigned long vas_iterate_internal(unsigned long out, unsigned long p2, unsigned long p3,
                                   unsigned long p4, unsigned long p5, unsigned long p6)
{
    unsigned long ctx = sk_rt_00310d80(0, p3);         /* FUN_00310d80 */
    long n = (long)sk_rt_0001612c(0, p3);              /* thunk_FUN_0001612c */
    if (n < 0)
        sk_boot_panic();
    unsigned long (*get)(unsigned long, ...) = (unsigned long (*)(unsigned long, ...))sk_rt_00023c78(p6); /* FUN_00023c78 */
    get(n, p4, p6);
    n = (long)sk_rt_0001612c(p2, p3);                  /* thunk_FUN_0001612c */
    unsigned long result = 0;
    if (n != 0) {
        long i = 0;
        unsigned long buf[4];
        do {
            sk_rt_0019ea20((unsigned long)&buf, i, p2, p3);           /* FUN_0019ea20 */
            long next = i + 1;
            if (next < i)
                sk_boot_panic();
            /* invoke store op (element) */
            sk_indirect_call((unsigned long)&buf, (unsigned long)&buf, p3);
            unsigned long elem = p5;
            result = ((unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long))tightbeam_method_8(elem))(out, p4, p6, p3, elem); /* 268a0 */
            /* invoke release */
            sk_indirect_call((unsigned long)&buf, p3);
            if (__builtin_frame_address(0) != 0)
                return result;
            long m = (long)sk_rt_0001612c(p2, p3);
            i = i + 1;
            if (next == m)
                break;
        } while (1);
    }
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026cac @ 0x00026cac   (est. vas_iterate_1)
 * Ghidra: undefined4 FUN_00026cac(undefined8, undefined8, undefined8, long, ulong)
 * VAS iteration wrapper returning 1 on success via FUN_00026a8c.
 * Confidence: low (wrapper).
 */
unsigned int vas_iterate_1(unsigned long a, unsigned long b, unsigned long c,
                           unsigned long p4, unsigned long p5)
{
    unsigned int result;
    result = (unsigned int)vas_iterate_internal(a, *(unsigned long *)(__builtin_frame_address(0)),
                                                *(unsigned long *)(p4 + 0x10), b,
                                                *(unsigned long *)((p5 & 0xfffffffffffffffe) - 8), c);
    if (__builtin_frame_address(0) == 0)
        result = 1;
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026cb0 @ 0x00026cb0   (est. vas_iterate_2)
 * Ghidra: undefined4 FUN_00026cb0(undefined8, undefined8, undefined8, long, ulong)
 * Mirror of FUN_00026cac.
 * Confidence: low.
 */
unsigned int vas_iterate_2(unsigned long a, unsigned long b, unsigned long c,
                           unsigned long p4, unsigned long p5)
{
    unsigned int result;
    result = (unsigned int)vas_iterate_internal(a, *(unsigned long *)(__builtin_frame_address(0)),
                                                *(unsigned long *)(p4 + 0x10), b,
                                                *(unsigned long *)((p5 & 0xfffffffffffffffe) - 8), c);
    if (__builtin_frame_address(0) == 0)
        result = 1;
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026cf0 @ 0x00026cf0   (est. vas_object_call)
 * Ghidra: ulong FUN_00026cf0(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Invokes a VAS object operation: resolves the op method (FUN_00023d00),
 * prepares the iteration context, and runs vas_iterate_objects with the
 * encode callback FUN_000274e4. Returns the operation status.
 * Confidence: low (VAS object op dispatcher).
 */
unsigned long vas_object_call(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4, unsigned long p5)
{
    long ctx = (long)(*(long (*)(unsigned long, unsigned long))sk_rt_00023d00(p5))(p3, p5); /* FUN_00023d00 */
    if (ctx < 0)
        sk_boot_panic();
    unsigned int slot[3] = {0, 0, 0};
    unsigned long meta = sk_f_00002534((unsigned long)&DAT_0064c2d8, (unsigned long)&DAT_004bbe30); /* FUN_00002534 */
    unsigned long eobj = sk_error_obj(0);              /* FUN_00019aac */
    unsigned long type = sk_type_register();           /* FUN_00027580 */
    unsigned long rc = vas_iterate_objects((void (*)(void))vas_object_encode_cb,  /* 274e4 */
                                           (unsigned long)&slot, meta, p2, eobj, type,
                                           DAT_0065a550, (unsigned long)slot);
    if (__builtin_frame_address(0) != 0)
        rc = (unsigned long)slot[0];
    return rc;
}

/*--------------------------------------------------------------------*/
/* FUN_00026e28 @ 0x00026e28   (est. vas_object_call_out)
 * Ghidra: void FUN_00026e28(undefined8 *, undefined4, undefined8, undefined8,
 *                           undefined4 *, long, ulong)
 * Wrapper: calls vas_object_call and writes the status either to param_1
 * (success) or param_5 (error).
 * Confidence: low.
 */
void vas_object_call_out(unsigned long *out, unsigned int p2, unsigned long p3,
                         unsigned long p4, unsigned int *err, unsigned long p6,
                         unsigned long p7)
{
    unsigned long rc = vas_object_call(p2, *(unsigned long *)(p6 + 0x10), p3,
                                       *(unsigned long *)((p7 & 0xfffffffffffffffe) - 8), p4);
    if (__builtin_frame_address(0) == 0)
        *out = rc;
    else
        *err = (int)rc;
}

/*--------------------------------------------------------------------*/
/* FUN_00026e7c @ 0x00026e7c   (est. vas_object_call2)
 * Ghidra: undefined8 FUN_00026e7c(undefined8, undefined8, undefined8)
 * Wrapper over the internal object-call2 with fixed method descriptors.
 * Confidence: medium.
 */
unsigned long vas_object_call2(unsigned long p1, unsigned long p2, unsigned long p3)
{
    unsigned long result = 0;
    unsigned long ctx = sk_obj_lock2(0);               /* FUN_00310d68 */
    vas_object_call2_internal((unsigned long)&result, ctx, 0x65a898, p3, 0x65a7d0); /* FUN_00026f40 */
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026f40 @ 0x00026f40   (est. vas_object_call2_internal)
 * Ghidra: undefined8 FUN_00026f40(undefined8, long, undefined8, undefined8, undefined8)
 * Internal object-call2: runs the object-call step (FUN_000276c4) with kind 0
 * or 1, encodes the result, and returns via the method FUN_000268a0.
 * Confidence: low (dense indirect-call op).
 */
unsigned long vas_object_call2_internal(unsigned long out, unsigned long p2, unsigned long p3,
                                        unsigned long p4, unsigned long p5)
{
    unsigned long ctx = p4;
    long obj = *(long *)(p2 - 8);
    /* invoke object op on context */
    sk_indirect_call(0, 0, p2);
    int kind = ((int (*)(unsigned long, unsigned long, unsigned long))(*(unsigned long *)(obj + 0x30)))(0, 1, ctx);
    if (kind == 1) {
        sk_indirect_call(0, p2);
        ((unsigned long (*)(unsigned long, unsigned long, unsigned long))tightbeam_method_8b(p5))(0, p3, p5); /* FUN_000276c4 */
    } else {
        sk_indirect_call(0, 0, ctx);
        ((unsigned long (*)(unsigned long, unsigned long, unsigned long))tightbeam_method_8b(p5))(1, p3, p5); /* FUN_000276c4 */
        unsigned long elem = p4;
        out = ((unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long))tightbeam_method_8(elem))(out, p3, p5, ctx, elem); /* 268a0 */
        sk_indirect_call(0, ctx);
    }
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_00027194 @ 0x00027194   (est. vas_object_call3)
 * Ghidra: undefined4 FUN_00027194(undefined8, undefined8, undefined8, undefined8, ulong)
 * Wrapper returning 1 on success via FUN_00026f40.
 * Confidence: low.
 */
unsigned int vas_object_call3(unsigned long a, unsigned long b, unsigned long c,
                              unsigned long p4, unsigned long p5)
{
    unsigned int result;
    result = (unsigned int)vas_object_call2_internal(a, p4, b,
                                                     *(unsigned long *)((p5 & 0xfffffffffffffffe) - 8), c);
    if (__builtin_frame_address(0) == 0)
        result = 1;
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00027198 @ 0x00027198   (est. vas_object_call4)
 * Ghidra: undefined4 FUN_00027198(undefined8, undefined8, undefined8, undefined8, ulong)
 * Mirror of FUN_00027194.
 * Confidence: low.
 */
unsigned int vas_object_call4(unsigned long a, unsigned long b, unsigned long c,
                              unsigned long p4, unsigned long p5)
{
    unsigned int result;
    result = (unsigned int)vas_object_call2_internal(a, p4, b,
                                                     *(unsigned long *)((p5 & 0xfffffffffffffffe) - 8), c);
    if (__builtin_frame_address(0) == 0)
        result = 1;
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_000271d8 @ 0x000271d8   (est. vas_codable_encode)
 * Ghidra: void FUN_000271d8(undefined8, undefined8, long, long, undefined8,
 *                           undefined8, undefined4 *)
 * Encodes a Codable value: resolves the kind via FUN_000276f4; if kind 1 runs
 * the encode method FUN_000269a4 and either commits or writes the error; on
 * other kinds raises a Swift fatal with the TightbeamCodable string.
 * Confidence: low (Swift Codable encode).
 */
void vas_codable_encode(unsigned long out, unsigned long p2, unsigned long p3,
                        unsigned long p4, unsigned long p5, unsigned long p6,
                        unsigned int *err)
{
    unsigned int code;
    unsigned char kind = ((unsigned char (*)(unsigned long, unsigned long))tightbeam_method_8c(p6))(p4, p6); /* 276f4 */
    if (kind == 1) {
        unsigned long frame[8];
        ((unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned int *, unsigned long, unsigned long))tightbeam_method_4d(p5))((unsigned long)&frame, p2, p4, p6, &code, p3, p5); /* 269a4 */
        if (__builtin_frame_address(0) == 0) {
            ((void (*)(unsigned long, unsigned long, unsigned long, unsigned long))(*(unsigned long *)(*(long *)(p3 - 8) + 0x38)))((unsigned long)&frame, 0, 1, p3);
            ((void (*)(unsigned long, unsigned long, unsigned long))(*(unsigned long *)(*(long *)(sk_obj_lock2(0) - 8) + 0x20)))(out, (unsigned long)&frame, 0);
        } else {
            *err = code;
        }
    } else if (kind != 0) {
        ((void (*)(unsigned long, unsigned long))(*(unsigned long *)(*(long *)(p4 - 8) + 8)))(p2, p4);
        cl4_log_fmt(0xe000000000000000);
        sk_tb_error_push(0);                            /* FUN_002acbb8 */
        cl4_log_fmt(0x80000000005ad2d0);
        (void)tightbeam_method_4e(0x670738);                       /* FUN_00027724 */
        sk_tb_error_push(0);
        sk_fatal_unavail("Fatal error", 0xb, 2, 0xd000000000000016, 0x80000000005ad2d0,
                         "Tightbeam TightbeamCodable swift", 0x20, 2); /* FUN_001afa84 */
    }
    ((void (*)(unsigned long, unsigned long, unsigned long, unsigned long))(*(unsigned long *)(*(long *)(p3 - 8) + 0x38)))(out, 1, 1, p3);
}

/*--------------------------------------------------------------------*/
/* FUN_00027494 @ 0x00027494   (est. vas_codable_encode_out)
 * Ghidra: void FUN_00027494(undefined8, undefined8, undefined8, undefined4 *,
 *                           long, ulong)
 * Codable-encode wrapper forwarding to FUN_000271d8.
 * Confidence: low.
 */
void vas_codable_encode_out(unsigned long out, unsigned long p2, unsigned long p3,
                            unsigned int *err, unsigned long p5, unsigned long p6)
{
    unsigned int code;
    vas_codable_encode(out, *(unsigned long *)(p5 + 0x10), p2,
                       *(unsigned long *)((p6 & 0xfffffffffffffffe) - 8), p3, 0, &code);
    if (__builtin_frame_address(0) != 0)
        *err = code;
}

/*--------------------------------------------------------------------*/
/* FUN_000274e4 @ 0x000274e4   (est. vas_object_encode_cb)
 * Ghidra: void FUN_000274e4(undefined8, undefined8, undefined4 *)
 * Object-encode callback: reads the frame fields and invokes the encode
 * method FUN_000269a4, writing the status to param_3 on error.
 * Confidence: low (iteration callback).
 */
void vas_object_encode_cb(unsigned long p1, unsigned long p2, unsigned int *err)
{
    unsigned long f1 = *(unsigned long *)(__builtin_frame_address(0) + 0x10);
    unsigned long f3 = *(unsigned long *)(__builtin_frame_address(0) + 0x18);
    unsigned long f2 = *(unsigned long *)(__builtin_frame_address(0) + 0x20);
    unsigned long f4 = *(unsigned long *)(__builtin_frame_address(0) + 0x28);
    unsigned long f6 = *(unsigned long *)(__builtin_frame_address(0) + 0x30);
    unsigned int code;
    ((unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned int *, unsigned long, unsigned long))tightbeam_method_4d(f2))(p1, f6, f3, f4, &code, f1, f2); /* FUN_000269a4 */
    if (__builtin_frame_address(0) != 0)
        *err = code;
}

/*--------------------------------------------------------------------*/
/* FUN_00027580 @ 0x00027580   (est. sk_type_register)
 * Ghidra: void FUN_00027580(void)
 * Registers the Tightbeam/VAS type: if already registered (DAT_0064c2e0)
 * returns; otherwise locks the domain (FUN_00027614), computes the type via
 * FUN_00027670 and stores it via FUN_00376820.
 * Confidence: low (one-shot type registration).
 * Notes: globals DAT_0064c2d8/DAT_0064c2e0/DAT_004bbe30/DAT_004ea760.
 */
unsigned long sk_type_register(void)
{
    unsigned long type;
    unsigned long slot;
    if (DAT_0064c2e0 != 0)
        return;
    unsigned long dom = sk_lock_and_alloc(&DAT_0064c2d8, &DAT_004bbe30); /* FUN_00027614 */
    slot = sk_type_register_inner();                   /* FUN_00027670 */
    type = 0x6720e8;
    DAT_0064c2e0 = sk_obj_reg_get(&DAT_004ea760, dom, &type); /* FUN_00376820 */
}

/*--------------------------------------------------------------------*/
/* FUN_00027614 @ 0x00027614   (est. sk_lock_and_alloc)
 * Ghidra: ulong FUN_00027614(ulong *param_1, long *param_2)
 * Returns the existing tagged lock value at param_1, or allocates a fresh
 * domain via FUN_00389b64 and stores it tagged.
 * Confidence: medium (lazy domain allocation).
 */
unsigned long sk_lock_and_alloc(unsigned long *lock, long *meta)
{
    if (*lock != 0)
        return *lock & 0xfffffffffffffffe;
    unsigned long v = sk_current_domain(0xff, (unsigned long)meta + (long)(int)*meta,
                                        (unsigned long)*meta >> 0x20, 0, 0); /* FUN_00389b64 */
    *lock = v | 1;
    return v & 0xfffffffffffffffe;
}

/*--------------------------------------------------------------------*/
/* FUN_00027670 @ 0x00027670   (est. sk_type_register_inner)
 * Ghidra: void FUN_00027670(void)
 * One-shot: stores the 8-byte type metadata from FUN_00376820 into the
 * byte array at DAT_0064c2e8.
 * Confidence: low (type-metadata store).
 */
unsigned long sk_type_register_inner(void)
{
    unsigned long v;
    if (*(unsigned long *)&DAT_0064c2e8 != 0)
        return *(unsigned long *)&DAT_0064c2e8;
    v = sk_obj_reg_get((unsigned long)&DAT_004edbbc, 0x677880); /* FUN_00376820 */
    *(unsigned long *)&DAT_0064c2e8 = v;
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_000276c4 @ 0x000276c4   (est. tightbeam_method_8b)
 * Ghidra: long FUN_000276c4(ulong param_1)
 * Method-table resolver for slot offset 8.
 * Confidence: high.
 */
long tightbeam_method_8b(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 8) + (long)*(int *)(obj + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_000276f4 @ 0x000276f4   (est. tightbeam_method_8c)
 * Ghidra: long FUN_000276f4(ulong param_1)
 * Method-table resolver for slot offset 8.
 * Confidence: high.
 */
long tightbeam_method_8c(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 8) + (long)*(int *)(obj + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_00027724 @ 0x00027724   (est. tightbeam_method_4e)
 * Ghidra: long FUN_00027724(ulong param_1)
 * Method-table resolver for slot offset 4.
 * Confidence: high.
 */
long tightbeam_method_4e(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 4) + (long)*(int *)(obj + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_00027754 @ 0x00027754   (est. sk_obj_lock_resolve)
 * Ghidra: long FUN_00027754(ulong param_1)
 * Resolves an object lock: if untagged returns the method pointer at +4;
 * if tagged returns the loaded lock pointer at +8.
 * Confidence: medium (tagged pointer lock resolution).
 */
long sk_obj_lock_resolve(unsigned long obj)
{
    if ((obj & 1) == 0)
        return (long)(obj + 4) + (long)*(int *)(obj + 4);
    return *(long *)((obj & 0xfffffffffffffffe) + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_00027788 @ 0x00027788   (est. tightbeam_method_38)
 * Ghidra: long FUN_00027788(ulong param_1)
 * Method-table resolver for slot offset 0x38.
 * Confidence: high.
 */
long tightbeam_method_38(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 0x38) + (long)*(int *)(obj + 0x38);
}

/*--------------------------------------------------------------------*/
/* FUN_000277b8 @ 0x000277b8   (est. tightbeam_method_20)
 * Ghidra: long FUN_000277b8(ulong param_1)
 * Method-table resolver for slot offset 0x20.
 * Confidence: high.
 */
long tightbeam_method_20(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 0x20) + (long)*(int *)(obj + 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_000277e8 @ 0x000277e8   (est. tightbeam_method_28)
 * Ghidra: long FUN_000277e8(ulong param_1)
 * Method-table resolver for slot offset 0x28.
 * Confidence: high.
 */
long tightbeam_method_28(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 0x28) + (long)*(int *)(obj + 0x28);
}

/*--------------------------------------------------------------------*/
/* FUN_00027818 @ 0x00027818   (est. tightbeam_method_60)
 * Ghidra: long FUN_00027818(ulong param_1)
 * Method-table resolver for slot offset 0x60.
 * Confidence: high.
 */
long tightbeam_method_60(unsigned long obj)
{
    if ((obj & 1) != 0)
        obj = *(unsigned long *)(obj & 0xfffffffffffffffe);
    return (long)(obj + 0x60) + (long)*(int *)(obj + 0x60);
}

/*--------------------------------------------------------------------*/
/* FUN_00027880 @ 0x00027880   (est. vas_server_register)
 * Ghidra: void FUN_00027880(void)
 * Registers the VAS server by forwarding to FUN_00027f50.
 * Confidence: low (forwarder).
 */
void vas_server_register(void)
{
    vas_server_register_internal(0, 0, 0, 0, 0, 0);   /* FUN_00027f50 */
}

/*--------------------------------------------------------------------*/
/* FUN_000278a8 @ 0x000278a8   (est. vas_msg_send)
 * Ghidra: long FUN_000278a8(undefined8, undefined8, ulong, code *)
 * Sends a VAS message: inits a decoder descriptor (FUN_000259c0), deinits the
 * storage (FUN_0001fd9c), retains the payload (FUN_0036b270) and invokes the
 * send callback; returns 0 when the callback reports status 2, else fatal.
 * Confidence: low (async message send).
 */
long vas_msg_send(unsigned long out, unsigned long p2, unsigned long payload,
                  void (*cb)(void))
{
    unsigned char desc[16];
    unsigned long storage;
    unsigned long result;
    tightbeam_decoder_init(desc, p2);                  /* FUN_000259c0 */
    storage = *(unsigned long *)&desc[8];
    sk_tb_storage_deinit(&storage);                    /* FUN_0001fd9c */
    unsigned long flags = payload | 0x2000000000000000;
    cl4_retain((void *)payload);                       /* FUN_0036b270 */
    ((void (*)(unsigned long, unsigned long, unsigned long))cb)((unsigned long)&result, (unsigned long)&flags, (unsigned long)desc);
    if ((result & 0xff) == 2)
        return 0;
    unsigned long r = result;
    if (r == 0)
        sk_fatal_unavail("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                         "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    sk_swift_epilogue();                               /* FUN_00025704 */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00027a98 @ 0x00027a98   (est. vas_op_invoke)
 * Ghidra: undefined8 FUN_00027a98(long param_1, undefined8, undefined8)
 * Invokes the operation stored at param_1+0x20 with the retained arg at
 * param_1+0x28, releasing it afterwards.
 * Confidence: low (op invocation with retain/release).
 */
unsigned long vas_op_invoke(unsigned long self, unsigned long a, unsigned long b)
{
    void (*op)(void) = *(void (**)(void))(self + 0x20);
    unsigned long arg = *(unsigned long *)(self + 0x28);
    cl4_retain((void *)arg);                           /* FUN_0036b270 */
    unsigned long rc = (unsigned long)op(a, b);
    cl4_release((void *)arg);                          /* FUN_0036b118 */
    return rc;
}

/*--------------------------------------------------------------------*/
/* FUN_00027b10 @ 0x00027b10   (est. vas_server_init_forward)
 * Ghidra: void FUN_00027b10(void)
 * Forwarder to FUN_00027b70.
 * Confidence: low.
 */
void vas_server_init_forward(void)
{
    vas_server_init(0, 0, 0, 0, 0, 0, 0);              /* FUN_00027b70 */
}

/*--------------------------------------------------------------------*/
/* FUN_00027b38 @ 0x00027b38   (est. vas_type_descriptor)
 * Ghidra: undefined1 [16] FUN_00027b38(void)
 * Returns the 16-byte type descriptor pair (0x64c380, 0).
 * Confidence: low (type-metadata accessor).
 */
cl4_result_t vas_type_descriptor(void)
{
    cl4_result_t r;
    r.lo = 0x64c380;
    r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00027b70 @ 0x00027b70   (est. vas_server_init)
 * Ghidra: long FUN_00027b70(undefined8, byte, undefined8, undefined8, undefined8,
 *                           undefined8, undefined8)
 * Initialises the VAS server: maps the kind to (size, flags) via
 * FUN_00015388, allocates the server object and a 0x28-byte op descriptor,
 * wires the op-invoke entry FUN_00027a98, registers via FUN_000147a0, and
 * stores the server at the owner's +0x10.
 * Confidence: low (VAS server scaffolding).
 */
unsigned long vas_server_init(unsigned long p1, unsigned char kind, unsigned long p3,
                              unsigned long p4, unsigned long p5, unsigned long p6,
                              unsigned long p7)
{
    unsigned long size, flags;
    if (kind < 2)
        size = (kind == 0) ? 3 : 0xd, flags = 0;
    else if (kind == 2)
        flags = 1, size = 3;
    else if (kind != 3) {
        size = sk_rt_0001532c(1, 0);
        goto reg;
    } else
        flags = 8, size = 3;
    size = sk_rt_00015388(size, p1, flags);
reg:
    unsigned long server = cl4_alloc_object(&DAT_0064c380, 0x18, 7); /* FUN_0036a940 */
    *(unsigned long *)(server + 0x10) = 0;
    unsigned long opdesc = cl4_alloc_object(p5, 0x28, 7); /* FUN_0036a940 */
    *(unsigned long *)(opdesc + 0x10) = server;
    *(unsigned long *)(opdesc + 0x18) = p3;
    *(unsigned long *)(opdesc + 0x20) = p4;
    unsigned long desc[8];
    desc[0] = 0x6ad3a8;
    desc[1] = DAT_004bb180;
    desc[2] = (unsigned long)vas_op_invoke;            /* FUN_00027a98 */
    desc[3] = p7;
    desc[4] = p6;
    unsigned long reg = sk_dispatch_async(&desc[2], &desc[0]); /* FUN_0004b520 */
    cl4_retain((void *)server);                        /* FUN_0036b270 */
    cl4_retain((void *)p4);                            /* FUN_0036b270 */
    cl4_release((void *)opdesc);                       /* FUN_0036b118 */
    unsigned long handle = sk_vas_register(size, reg); /* FUN_000147a0 */
    sk_dispatch_free(reg);                             /* FUN_0004b664 */
    unsigned long meta = sk_f_00002534((unsigned long)&DAT_0064c040, (unsigned long)&DAT_004bbf40); /* FUN_00002534 */
    unsigned long logobj = cl4_log_alloc(meta, 0);     /* FUN_0036a9a0 */
    *(unsigned long *)(logobj + 0x18) = DAT_004baeb8;
    *(unsigned long *)(logobj + 0x10) = DAT_004baeb0;
    *(unsigned long *)(logobj + 0x38) = 0x6753a0;
    *(unsigned long *)(logobj + 0x20) = 0xd00000000000001b;
    *(unsigned long *)(logobj + 0x28) = 0x80000000005ad2f0;
    sk_rt_0026b434(logobj, 0x20, 0xe100000000000000, 10, 0xe100000000000000); /* FUN_0026b434 */
    cl4_log_emit(logobj);                              /* FUN_0036b588 */
    cl4_log_fmt(*(unsigned long *)(logobj + 0x20));    /* FUN_003a25d4 */
    cl4_release((void *)p4);                           /* FUN_0036b118 */
    *(unsigned long *)(server + 0x10) = handle;
    return server;
}

/*--------------------------------------------------------------------*/
/* FUN_00027d94 @ 0x00027d94   (est. vas_server_create)
 * Ghidra: long FUN_00027d94(undefined8, undefined8, undefined8, undefined8,
 *                           undefined8, undefined8)
 * Creates a VAS server object (without the kind mapping): allocates the server
 * and op descriptor, wires the op-invoke entry, registers, and stores the
 * handle at +0x10. Confidence low (mirrors FUN_00027b70).
 */
unsigned long vas_server_create(unsigned long p1, unsigned long p2, unsigned long p3,
                                unsigned long p4, unsigned long p5, unsigned long p6)
{
    unsigned long server = cl4_alloc_object(0);         /* FUN_0036a940 */
    *(unsigned long *)(server + 0x10) = 0;
    unsigned long opdesc = cl4_alloc_object(p4, 0x28, 7); /* FUN_0036a940 */
    *(unsigned long *)(opdesc + 0x10) = server;
    *(unsigned long *)(opdesc + 0x18) = p2;
    *(unsigned long *)(opdesc + 0x20) = p3;
    unsigned long desc[8];
    desc[0] = 0x6ad3a8;
    desc[1] = DAT_004bb180;
    desc[2] = (unsigned long)vas_op_invoke;            /* FUN_00027a98 */
    desc[3] = p6;
    desc[4] = p5;
    unsigned long reg = sk_dispatch_async(&desc[2], &desc[0]); /* FUN_0004b520 */
    cl4_retain((void *)server);                        /* FUN_0036b270 */
    cl4_retain((void *)p3);                            /* FUN_0036b270 */
    cl4_release((void *)opdesc);                       /* FUN_0036b118 */
    unsigned long handle = sk_vas_register(p1, reg);   /* FUN_000147a0 */
    sk_dispatch_free(reg);                             /* FUN_0004b664 */
    unsigned long meta = sk_f_00002534((unsigned long)&DAT_0064c040, (unsigned long)&DAT_004bbf40); /* FUN_00002534 */
    unsigned long logobj = cl4_log_alloc(meta, 0);     /* FUN_0036a9a0 */
    *(unsigned long *)(logobj + 0x18) = DAT_004baeb8;
    *(unsigned long *)(logobj + 0x10) = DAT_004baeb0;
    *(unsigned long *)(logobj + 0x38) = 0x6753a0;
    *(unsigned long *)(logobj + 0x20) = 0xd00000000000001b;
    *(unsigned long *)(logobj + 0x28) = 0x80000000005ad2f0;
    sk_rt_0026b434(logobj, 0x20, 0xe100000000000000, 10, 0xe100000000000000); /* FUN_0026b434 */
    cl4_log_emit(logobj);                              /* FUN_0036b588 */
    cl4_log_fmt(*(unsigned long *)(logobj + 0x20));    /* FUN_003a25d4 */
    cl4_release((void *)p3);                           /* FUN_0036b118 */
    *(unsigned long *)(server + 0x10) = handle;
    return server;
}

/*--------------------------------------------------------------------*/
/* FUN_00027f50 @ 0x00027f50   (est. vas_server_register_internal)
 * Ghidra: void FUN_00027f50(undefined8, undefined8, undefined8, undefined8,
 *                           undefined8, undefined8)
 * Internal VAS server registration on the current frame context: allocates
 * the op descriptor, registers, and stores the handle at frame +0x10.
 * Confidence: low.
 */
void vas_server_register_internal(unsigned long p1, unsigned long p2, unsigned long p3,
                                  unsigned long p4, unsigned long p5, unsigned long p6)
{
    unsigned long self = __builtin_frame_address(0);
    *(unsigned long *)(self + 0x10) = 0;
    unsigned long opdesc = cl4_alloc_object(p4, 0x28, 7); /* FUN_0036a940 */
    *(unsigned long *)(opdesc + 0x10) = self;
    *(unsigned long *)(opdesc + 0x18) = p2;
    *(unsigned long *)(opdesc + 0x20) = p3;
    unsigned long desc[8];
    desc[0] = 0x6ad3a8;
    desc[1] = DAT_004bb180;
    desc[2] = (unsigned long)vas_op_invoke;            /* FUN_00027a98 */
    desc[3] = p6;
    desc[4] = p5;
    unsigned long reg = sk_dispatch_async(&desc[2], &desc[0]); /* FUN_0004b520 */
    cl4_retain(0);                                     /* FUN_0036b270 */
    cl4_retain((void *)p3);                            /* FUN_0036b270 */
    cl4_release((void *)opdesc);                       /* FUN_0036b118 */
    unsigned long handle = sk_vas_register(p1, reg);   /* FUN_000147a0 */
    sk_dispatch_free(reg);                             /* FUN_0004b664 */
    unsigned long meta = sk_f_00002534((unsigned long)&DAT_0064c040, (unsigned long)&DAT_004bbf40); /* FUN_00002534 */
    unsigned long logobj = cl4_log_alloc(meta, 0);     /* FUN_0036a9a0 */
    *(unsigned long *)(logobj + 0x18) = DAT_004baeb8;
    *(unsigned long *)(logobj + 0x10) = DAT_004baeb0;
    *(unsigned long *)(logobj + 0x38) = 0x6753a0;
    *(unsigned long *)(logobj + 0x20) = 0xd00000000000001b;
    *(unsigned long *)(logobj + 0x28) = 0x80000000005ad2f0;
    sk_rt_0026b434(logobj, 0x20, 0xe100000000000000, 10, 0xe100000000000000); /* FUN_0026b434 */
    cl4_log_emit(logobj);                              /* FUN_0036b588 */
    cl4_log_fmt(*(unsigned long *)(logobj + 0x20));    /* FUN_003a25d4 */
    cl4_release((void *)p3);                           /* FUN_0036b118 */
    *(unsigned long *)(self + 0x10) = handle;
}

/*--------------------------------------------------------------------*/
/* FUN_000280c4 @ 0x000280c4   (est. vas_fault_complete)
 * Ghidra: long FUN_000280c4(undefined8, undefined8, ulong, undefined8, undefined8)
 * Completes a VAS fault: builds a decoder descriptor, packs the fault result
 * tag, and calls the completion path FUN_003ed2dc; returns 0 on tag 2.
 * Confidence: low (fault-completion).
 */
long vas_fault_complete(unsigned long out, unsigned long p2, unsigned long flags,
                        unsigned long p4, unsigned long p5)
{
    unsigned char desc[16];
    unsigned long storage;
    tightbeam_decoder_init(desc, p2);                  /* FUN_000259c0 */
    storage = *(unsigned long *)&desc[8];
    sk_tb_storage_deinit(&storage);                    /* FUN_0001fd9c */
    unsigned long fflags = flags | 0x2000000000000000;
    unsigned long result = 2, rc = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0;
    cl4_retain((void *)flags);                         /* FUN_0036b270 */
    sk_tb_metadata_call(&DAT_004bbfd0, 0, 0x67b148);   /* FUN_003ed2dc */
    if ((result & 0xff) == 2)
        return 0;
    if (rc == 0)
        sk_fatal_unavail("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                         "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    sk_swift_epilogue();                               /* FUN_00025704 */
    return rc;
}
