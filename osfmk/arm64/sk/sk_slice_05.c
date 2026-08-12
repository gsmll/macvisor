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
unsigned long vas_iterate_objects(void (*)(void), unsigned long, unsigned long, unsigned long,
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
unsigned long vas_iterate_objects(void (*iter)(void), unsigned long p2, unsigned long p3,
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
    return count;
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
        return DAT_0064c2e0;
    unsigned long dom = sk_lock_and_alloc(&DAT_0064c2d8, &DAT_004bbe30); /* FUN_00027614 */
    slot = sk_type_register_inner();                   /* FUN_00027670 */
    type = 0x6720e8;
    DAT_0064c2e0 = sk_obj_reg_get((unsigned long)&DAT_004ea760, dom, (unsigned long)&type); /* FUN_00376820 */
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
    unsigned long (*op)(unsigned long, unsigned long) = *(unsigned long (**)(unsigned long, unsigned long))(self + 0x20);
    unsigned long arg = *(unsigned long *)(self + 0x28);
    cl4_retain((void *)arg);                           /* FUN_0036b270 */
    unsigned long rc = op(a, b);
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
    unsigned long server = cl4_alloc_object((unsigned long)&DAT_0064c380, 0x18, 7); /* FUN_0036a940 */
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
    unsigned long reg = sk_dispatch_async((unsigned long)&desc[2], (unsigned long)&desc[0]); /* FUN_0004b520 */
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
    unsigned long reg = sk_dispatch_async((unsigned long)&desc[2], (unsigned long)&desc[0]); /* FUN_0004b520 */
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
    unsigned long self = (unsigned long)__builtin_frame_address(0);
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
    unsigned long reg = sk_dispatch_async((unsigned long)&desc[2], (unsigned long)&desc[0]); /* FUN_0004b520 */
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
    sk_tb_metadata_call((unsigned long)&DAT_004bbfd0, 0, 0x67b148);   /* FUN_003ed2dc */
    if ((result & 0xff) == 2)
        return 0;
    if (rc == 0)
        sk_fatal_unavail("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                         "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    sk_swift_epilogue();                               /* FUN_00025704 */
    return rc;
}
/* FUN_00028374 @ 0x00028374   (est. vas_fault_release_a)
 * Ghidra: void FUN_00028374(void)
 * Trampoline release callback for a VAS fault context (self in x20). Releases
 * the two held object refs at self+0x10 and self+0x20, then drops the shared
 * lock reference. No return value; used as the teardown continuation of the
 * fault-release path.
 * Confidence: medium
 * Notes: uses unaff_x20 (self); identical twin of FUN_00028378. */
void
vas_fault_release_a(void)
{
	long *self;

	cl4_release(*(unsigned long *)(self + 0x10));	/* FUN_0036b118 */
	cl4_release(*(unsigned long *)(self + 0x20));	/* FUN_0036b118 */
	sk_lock_unref();				/* FUN_0036b21c */
}

/*----*/
/* FUN_00028378 @ 0x00028378   (est. vas_fault_release_b)
 * Ghidra: void FUN_00028378(void)
 * Trampoline release callback for a VAS fault context (self in x20). Identical
 * to FUN_00028374: releases the two object refs at self+0x10 / self+0x20 and
 * drops the shared lock reference.
 * Confidence: medium
 * Notes: uses unaff_x20 (self). */
void
vas_fault_release_b(void)
{
	long *self;

	cl4_release(*(unsigned long *)(self + 0x10));	/* FUN_0036b118 */
	cl4_release(*(unsigned long *)(self + 0x20));	/* FUN_0036b118 */
	sk_lock_unref();				/* FUN_0036b21c */
}

/*----*/
/* FUN_000283a8 @ 0x000283a8   (est. vas_dispatch_setup)
 * Ghidra: void FUN_000283a8(undefined8 param_1,undefined8 param_2,
 *          undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Async dispatch setup for a VAS fault/apply continuation. Stuffs the four
 * message-slot fields into the shared context (x22): +0xb8 desc, +0xc0, +0xc8
 * and +0xd0, then schedules the continuation LAB_000283d0 via the async
 * dispatcher. param_1 (the closure) is otherwise unused by this body.
 * Confidence: medium
 * Notes: uses unaff_x22 (shared continuation context); context +0xb8 is the
 *        message descriptor consumed by FUN_000285c8. */
void
vas_dispatch_setup(unsigned long param_1, unsigned long param_2,
                   unsigned long param_3, unsigned long param_4,
                   unsigned long param_5)
{
	long *ctx;

	*(unsigned long *)(ctx + 0xc8) = param_4;
	*(unsigned long *)(ctx + 0xd0) = param_5;
	*(unsigned long *)(ctx + 0xb8) = param_2;
	*(unsigned long *)(ctx + 0xc0) = param_3;
	sk_tb_async_dispatch((void *)0x283d0, 0, 0);	/* FUN_00408db8, LAB_000283d0 */
}

/*----*/
/* FUN_000284f4 @ 0x000284f4   (est. vas_fault_dispatch)
 * Ghidra: void FUN_000284f4(void)
 * Fault-apply dispatch continuation. Releases the pending async record held at
 * (head+0xd8) (head = *x22), then, based on a flag in x20, either continues
 * with the apply worker FUN_000285c8 (flag clear) or stamps (head+0x7c) from
 * (head+0x44) and routes to FUN_000248a4 (flag set). Finally schedules the
 * chosen continuation.
 * Confidence: medium
 * Notes: uses unaff_x20 (flag) and unaff_x22 (head context). */
void
vas_fault_dispatch(void)
{
	void (*next)(void);
	unsigned long *head;		/* unaff_x22 */
	unsigned long flag;		/* unaff_x20 */

	head = (unsigned long *)*((long *)head);	/* head = *x22 */
	sk_tb_async_release(*(unsigned long *)((char *)head + 0xd8));	/* FUN_0040bd24 */
	if (flag == 0) {
		next = vas_fault_apply;			/* FUN_000285c8 */
	} else {
		*(unsigned int *)((char *)head + 0x7c) = *(unsigned int *)((char *)head + 0x44);
		next = (void (*)(void))0x248a4;		/* FUN_000248a4 */
	}
	sk_tb_async_dispatch(next, 0, 0);		/* FUN_00408db8 */
}

/*----*/
/* FUN_000285c8 @ 0x000285c8   (est. vas_fault_apply)
 * Ghidra: void FUN_000285c8(void)
 * VAS fault-apply worker. Reads the message descriptor at ctx+0xb8. If its
 * kind byte is not 2, marshals the descriptor's seven fields into the context
 * (kind&1 at +0x48, payload words at +0x50..+0x70, tag at +0x78), runs the
 * swift epilogue, and re-reads the (possibly replaced) descriptor. Then copies
 * the seven fields back from the context into the descriptor and makes the
 * indirect method call through (ctx+8).
 * Confidence: medium
 * Notes: uses unaff_x22 (ctx); indirect jump at 0x2866c treated as a call;
 *        trailing copy writes desc[0]=uVar3, desc[8]=uVar4, +0x10=uVar5,
 *        +0x18=uVar6, +0x20=uVar7, +0x28=uVar8, +0x30=ctx+0xb0. */
void
vas_fault_apply(void)
{
	unsigned char *desc;
	unsigned long v0, v1, v2, v3, v4, v5, v6;
	long *ctx;

	desc = *(unsigned char **)((char *)ctx + 0xb8);
	if (*desc != 2) {
		*(unsigned char *)((char *)ctx + 0x48) = *desc & 1;
		*(unsigned long *)((char *)ctx + 0x58) = *(unsigned long *)(desc + 0x10);
		*(unsigned long *)((char *)ctx + 0x50) = *(unsigned long *)(desc + 8);
		*(unsigned long *)((char *)ctx + 0x68) = *(unsigned long *)(desc + 0x20);
		*(unsigned long *)((char *)ctx + 0x60) = *(unsigned long *)(desc + 0x18);
		*(unsigned long *)((char *)ctx + 0x70) = *(unsigned long *)(desc + 0x28);
		*(unsigned char *)((char *)ctx + 0x78) = desc[0x30];
		sk_swift_epilogue();			/* FUN_00025704 */
		desc = *(unsigned char **)((char *)ctx + 0xb8);
	}
	v0 = *(unsigned long *)((char *)ctx + 0x88);
	v1 = *(unsigned long *)((char *)ctx + 0x80);
	v2 = *(unsigned long *)((char *)ctx + 0x98);
	v3 = *(unsigned long *)((char *)ctx + 0x90);
	v4 = *(unsigned long *)((char *)ctx + 0xa8);
	v5 = *(unsigned long *)((char *)ctx + 0xa0);
	desc[0x30] = *(unsigned char *)((char *)ctx + 0xb0);
	*(unsigned long *)(desc + 0x18) = v2;
	*(unsigned long *)(desc + 0x10) = v3;
	*(unsigned long *)(desc + 0x28) = v4;
	*(unsigned long *)(desc + 0x20) = v5;
	*(unsigned long *)(desc + 8) = v0;
	*(unsigned long *)desc = v1;
	/* indirect method dispatch through (ctx+8) */
	(*(void (**)(void))*(unsigned long *)((char *)ctx + 8))();
}

/*----*/
/* FUN_00028680 @ 0x00028680   (est. vas_release_op_a)
 * Ghidra: void FUN_00028680(void)
 * Release-op trampoline (self in x20). If the op ref at self+0x10 is set,
 * invokes the teardown thunk FUN_00014578 and returns; otherwise hits the
 * noreturn software breakpoint at 0x286a8 (invalid release state).
 * Confidence: medium
 * Notes: uses unaff_x20 (self); twin of FUN_00028684. */
void
vas_release_op_a(void)
{
	long *self;

	if (*(long *)((char *)self + 0x10) != 0) {
		sk_rt_00014578();			/* thunk_FUN_00014578 */
		return;
	}
	/* noreturn bounds/state fault */
	(*(void (**)(void))SoftwareBreakpoint)(1, 0x286a8);
}

/*----*/
/* FUN_00028684 @ 0x00028684   (est. vas_release_op_b)
 * Ghidra: void FUN_00028684(void)
 * Release-op trampoline (self in x20). Identical to FUN_00028680: with the op
 * ref at self+0x10 set it invokes the teardown thunk FUN_00014578, else hits
 * the noreturn software breakpoint at 0x286a8.
 * Confidence: medium
 * Notes: uses unaff_x20 (self). */
void
vas_release_op_b(void)
{
	long *self;

	if (*(long *)((char *)self + 0x10) != 0) {
		sk_rt_00014578();			/* thunk_FUN_00014578 */
		return;
	}
	/* noreturn bounds/state fault */
	(*(void (**)(void))SoftwareBreakpoint)(1, 0x286a8);
}

/*----*/
/* FUN_000286a8 @ 0x000286a8   (est. vas_release_op_c)
 * Ghidra: void FUN_000286a8(void)
 * Release-op trampoline with an extra object release (self in x20). With the
 * op ref at self+0x10 set, invokes the teardown thunk FUN_00014578 and then
 * cl4_release_op before returning; otherwise hits the noreturn software
 * breakpoint at 0x286dc.
 * Confidence: medium
 * Notes: uses unaff_x20 (self); twin of FUN_000286ac. */
void
vas_release_op_c(void)
{
	long *self;

	if (*(long *)((char *)self + 0x10) != 0) {
		sk_rt_00014578();			/* thunk_FUN_00014578 */
		cl4_release_op();			/* FUN_0036b6ac */
		return;
	}
	/* noreturn bounds/state fault */
	(*(void (**)(void))SoftwareBreakpoint)(1, 0x286dc);
}

/*----*/
/* FUN_000286ac @ 0x000286ac   (est. vas_release_op_d)
 * Ghidra: void FUN_000286ac(void)
 * Release-op trampoline with an extra object release (self in x20). Identical
 * to FUN_000286a8: teardown thunk FUN_00014578 plus cl4_release_op when the op
 * ref is set, else the noreturn software breakpoint at 0x286dc.
 * Confidence: medium
 * Notes: uses unaff_x20 (self). */
void
vas_release_op_d(void)
{
	long *self;

	if (*(long *)((char *)self + 0x10) != 0) {
		sk_rt_00014578();			/* thunk_FUN_00014578 */
		cl4_release_op();			/* FUN_0036b6ac */
		return;
	}
	/* noreturn bounds/state fault */
	(*(void (**)(void))SoftwareBreakpoint)(1, 0x286dc);
}

/*----*/
/* FUN_000286dc @ 0x000286dc   (est. vas_type_descriptor_get)
 * Ghidra: undefined1 [16] FUN_000286dc(void)
 * Returns the VAS type-descriptor global DAT_0064c308, zero-extended into a
 * 16-byte result (low word = pointer, high word = 0). Read-only getter.
 * Confidence: high
 * Notes: decompile emits ZEXT816(0x64c308); transcribed as the low 8 bytes. */
unsigned long
vas_type_descriptor_get(void)
{
	return (unsigned long)DAT_0064c308;	/* 0x64c308, 16-byte ZEXT816 */
}

/*----*/
/* FUN_000286ec @ 0x000286ec   (est. vas_closure_capture)
 * Ghidra: void FUN_000286ec(undefined8 param_1)
 * Captures a closure for the dispatch continuation. Allocates a closure block
 * via sk_rt_0040bb18(DAT_004bbfcc), links it to the shared context (x22) as
 * (x22+0x10) with the closure body FUN_00025ac0, then calls vas_dispatch_setup
 * to stuff the captured fields into the context. Captures three values read
 * from self (x20) and one argument; a fourth captured value (x20+0x28) is
 * passed but discarded by the setup helper.
 * Confidence: medium
 * Notes: uses unaff_x20 (self) and unaff_x22 (shared ctx). */
void
vas_closure_capture(unsigned long param_1)
{
	unsigned long *cl;
	long *ctx;
	unsigned long *self;

	cl = (unsigned long *)sk_rt_0040bb18(DAT_004bbfcc);	/* FUN_0040bb18 */
	*(unsigned long **)((char *)ctx + 0x10) = cl;
	cl[0] = (unsigned long)ctx;
	cl[1] = (unsigned long)0x25ac0;			/* FUN_00025ac0 */
	vas_dispatch_setup((unsigned long)cl, param_1,	/* FUN_000283a8 */
	                   *(unsigned long *)((char *)self + 0x10),
	                   *(unsigned long *)((char *)self + 0x18),
	                   *(unsigned long *)((char *)self + 0x20));
}

/*----*/
/* FUN_000287e4 @ 0x000287e4   (est. vas_spanmap_alloc)
 * Ghidra: void FUN_000287e4(long *param_1,undefined8 param_2,undefined8 param_3)
 * Allocates a span-map region into the caller's result record param_1 (five
 * longs). Clears the record, runs the shared prelude FUN_00035ba0; if the
 * first word is still clear, allocates a physical frame (sk_phys_alloc) and
 * resolves the span map via sk_spanmap_get3, storing the five resulting longs
 * back into param_1. If the map still failed to materialize (empty or the
 * leaf-present bit at param_1+1 is clear), destroys the allocated frame.
 * Confidence: medium
 * Notes: leaf-present test is (*(byte *)(param_1+1) & 1). */
void
vas_spanmap_alloc(long *param_1, unsigned long param_2, unsigned long param_3)
{
	unsigned long span[5];
	unsigned long phys;

	param_1[4] = 0;
	param_1[1] = 0;
	param_1[0] = 0;
	param_1[3] = 0;
	param_1[2] = 0;
	sk_rt_00035ba0();				/* FUN_00035ba0 */
	if (*param_1 == 0) {
		phys = sk_phys_alloc();			/* FUN_00034f70 */
		sk_spanmap_get3(&span[0], param_2, param_3, phys);	/* FUN_00036008 */
		param_1[1] = span[1];
		param_1[0] = span[0];
		param_1[3] = span[3];
		param_1[2] = span[2];
		param_1[4] = span[4];
		if ((*param_1 == 0) || ((*(unsigned char *)(param_1 + 1) & 1) == 0)) {
			cl4_destroy_elem(phys);		/* FUN_004b23d8 */
		}
	}
}

/*----*/
/* FUN_0002887c @ 0x0002887c   (est. vas_object_clone)
 * Ghidra: undefined8 * FUN_0002887c(undefined8 param_1,undefined8 *param_2)
 * Deep-clones a VAS object's 10-word record. Allocates a 0x50-byte zone object
 * (sk_zone_alloc_obj), stores param_1 as the first word, then for each of the
 * nine words of the source param_2 dispatches async (sk_dispatch_async) and
 * records the returned handle into the clone slots 1..9. Returns the clone,
 * or hits the noreturn bounds breakpoint at 0x28950 if allocation failed.
 * Confidence: medium
 * Notes: the trailing `puVar2 <= puVar2 + 10` guard is always true, so the
 *        only failure path is a null allocation. */
unsigned long *
vas_object_clone(unsigned long param_1, unsigned long *param_2)
{
	unsigned long *clone;
	unsigned long slot;

	clone = (unsigned long *)sk_zone_alloc_obj(1, 0x50, 0xa0040cc6163ff);	/* FUN_00010244 */
	if (clone != (unsigned long *)0x0) {
		clone[0] = param_1;
		slot = sk_dispatch_async(*param_2);	/* FUN_0004b520 */
		clone[1] = slot;
		slot = sk_dispatch_async(param_2[1]);
		clone[2] = slot;
		slot = sk_dispatch_async(param_2[2]);
		clone[3] = slot;
		slot = sk_dispatch_async(param_2[3]);
		clone[4] = slot;
		slot = sk_dispatch_async(param_2[4]);
		clone[5] = slot;
		slot = sk_dispatch_async(param_2[5]);
		clone[6] = slot;
		slot = sk_dispatch_async(param_2[6]);
		clone[7] = slot;
		slot = sk_dispatch_async(param_2[7]);
		clone[8] = slot;
		slot = sk_dispatch_async(param_2[8]);
		clone[9] = slot;
		return clone;
	}
	/* noreturn bounds fault */
	(*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x28950);
	return 0;	/* unreachable */
}

/*----*/
/* FUN_00028950 @ 0x00028950   (est. vas_lookup_core)
 * Ghidra: long * FUN_00028950(long param_1,long param_2,long param_3,long param_4)
 * Linear lookup over a VAS object table. Table base at (param_1+0x1e8), entry
 * count at (param_1+0x1e0), each entry is 0xb longs; an entry's key words are
 * *(entry[1]+8) vs param_2, *(entry[1]+0x10) vs param_3, and entry[0] vs
 * param_4. Returns the matching entry, or NULL. Any pointer step out of the
 * [base, base+count*0xb) window trips the noreturn bounds breakpoint.
 * Confidence: medium
 * Notes: step unit 0xb (=11 longs) at 0x28a0c; SoftwareBreakpoint 0x5519/0x28a10. */
long *
vas_lookup_core(long param_1, long param_2, long param_3, long param_4)
{
	long *entry, *base, *end;
	long remaining;

	remaining = *(long *)(param_1 + 0x1e0);
	if (remaining != 0) {
		base = *(long **)(param_1 + 0x1e8);
		end = base + *(long *)(param_1 + 0x1d8) * 0xb;
		entry = base;
		do {
			if (param_2 != 0) {
				if (((end < entry + 0xb) || (entry + 0xb < entry)) || (entry < base))
					goto out_of_bounds;
				if (*(long *)(entry[1] + 8) == param_2)
					return entry;
			}
			if (param_3 != 0) {
				if (((end < entry + 0xb) || (entry + 0xb < entry)) || (entry < base))
					goto out_of_bounds;
				if (*(long *)(entry[1] + 0x10) == param_3)
					return entry;
			}
			if (param_4 != 0) {
				if (((end < entry + 0xb) || (entry + 0xb < entry)) || (entry < base)) {
out_of_bounds:
					/* noreturn bounds fault */
					(*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x28a10);
				}
				if (*entry == param_4)
					return entry;
			}
			entry = entry + 0xb;
			remaining = remaining - 1;
		} while (remaining != 0);
	}
	return (long *)0x0;
}

/*----*/
/* FUN_00028a10 @ 0x00028a10   (est. vas_lookup_value)
 * Ghidra: undefined8 FUN_00028a10(undefined8 param_1,undefined8 param_2)
 * Convenience lookup: resolves the entry whose key at entry[1]+0x10 equals
 * param_2 and returns the word at entry+8 (the associated value). Returns 0
 * when no entry matches.
 * Confidence: high */
unsigned long
vas_lookup_value(unsigned long param_1, unsigned long param_2)
{
	long *entry;
	unsigned long value;

	entry = vas_lookup_core(param_1, 0, param_2, 0);	/* FUN_00028950 */
	value = 0;
	if (entry != 0)
		value = *(unsigned long *)(entry + 8);
	return value;
}

/*----*/
/* FUN_00028a3c @ 0x00028a3c   (est. vas_lookup_pair)
 * Ghidra: undefined1 [16] FUN_00028a3c(undefined8 param_1,undefined8 param_2)
 * Convenience lookup: resolves the entry whose key at entry[1]+0x10 equals
 * param_2 and returns the 16-byte pair stored at entry+0x48 / entry+0x50
 * (zero pair when no entry matches).
 * Confidence: high
 * Notes: 16-byte result transcribed as two unsigned longs. */
void
vas_lookup_pair(unsigned long param_1, unsigned long param_2,
                unsigned long *lo, unsigned long *hi)
{
	long *entry;

	entry = vas_lookup_core(param_1, 0, param_2, 0);	/* FUN_00028950 */
	if (entry == 0) {
		*hi = 0;
		*lo = 0;
	} else {
		*lo = *(unsigned long *)(entry + 0x48);
		*hi = *(unsigned long *)(entry + 0x50);
	}
}

/*----*/
/* FUN_00028a78 @ 0x00028a78   (est. vas_lookup_extra)
 * Ghidra: undefined8 FUN_00028a78(undefined8 param_1,undefined8 param_2)
 * Convenience lookup: resolves the entry whose key at entry[1]+0x10 equals
 * param_2 and returns the word at entry+0x40 (an extra payload slot). Returns
 * 0 when no entry matches.
 * Confidence: high */
unsigned long
vas_lookup_extra(unsigned long param_1, unsigned long param_2)
{
	long *entry;
	unsigned long value;

	entry = vas_lookup_core(param_1, 0, param_2, 0);	/* FUN_00028950 */
	value = 0;
	if (entry != 0)
		value = *(unsigned long *)(entry + 0x40);
	return value;
}

/*----*/
/* FUN_00028aa4 @ 0x00028aa4   (est. vas_range_lookup)
 * Ghidra: undefined8 FUN_00028aa4(long param_1,long param_2)
 * Range probe over a VAS region table. Iterates entries at (param_1+0x1d8),
 * stepped 0x48 longs, count at (param_1+0x188). An entry is "active" when its
 * tag at (p-0x28) equals 1 and the difference (param_2 - base at p-0x20) is
 * below 0x4000 (16 KB window); returns 1 on the first match, else 0. Any
 * address arithmetic escaping the base window trips the bounds breakpoint.
 * Confidence: medium
 * Notes: SoftwareBreakpoint 0x5519/0x28b14; 0x4000 is the window size. */
unsigned long
vas_range_lookup(long param_1, long param_2)
{
	unsigned long entry;
	long remaining;

	remaining = *(long *)(param_1 + 0x188);
	if (remaining != 0) {
		entry = param_1 + 0x1d8;
		do {
			if ((entry != 0x48) &&
			    (((entry - 0x48 < param_1 + 400) || (param_1 + 0x1d8 < entry)) || (entry < entry - 0x48))) {
				/* noreturn bounds fault */
				(*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x28b14);
			}
			if ((*(char *)(entry - 0x28) == '\x01') &&
			    ((unsigned long)(param_2 - *(long *)(entry - 0x20)) < 0x4000))
				return 1;
			entry = entry + 0x48;
			remaining = remaining - 1;
		} while (remaining != 0);
	}
	return 0;
}

/*----*/
/* FUN_00028b14 @ 0x00028b14   (est. vas_type_register)
 * Ghidra: undefined8 * FUN_00028b14(undefined8 param_1,undefined8 param_2,
 *          undefined8 param_3,long *param_4)
 * Builds and registers a VAS type/object descriptor. Allocates a 0x210-byte
 * VAS object (sk_alloc_vas), stores the 4 context words (param_2, param_3,
 * type id, param_4), populates a capacity/slab record, links the object into
 * the global list under a mutex, and installs a ~40-entry dispatch/method table
 * (each entry a 10-word descriptor committed via sk_dispatch_async). Then
 * allocates two request slots (via sk_rt_004b1a74 / sk_rt_004b1aac) and, under
 * a lock, invokes the slot init to bind the message; encodes the result via
 * sk_rt_000462f8 / sk_rt_00046304 and finishes by calling the caller's
 * completion callback (param_4[2]). Returns the descriptor object.
 * Confidence: low
 * Notes: SoftwareBreakpoint 0x5519 at 0x299d8/0x299dc/0x29ae4/0x29c6c; the
 *        40-slot method table strings span DAT_0065ae70..DAT_0065b560 and the
 *        table is written as per-slot 10-word descriptor records. */
unsigned long *
vas_type_register(unsigned long param_1, unsigned long param_2,
                  unsigned long param_3, long *param_4)
{
	unsigned long *obj, *obj_end, *slot, *slot_base, *slot6;
	unsigned long uVar14, uVar9, buf_lo, buf_hi;
	unsigned long record[10];
	unsigned long tail_a, tail_b;
	unsigned long sbuf, ecode, rcode;
	unsigned long d48, d40, slot_hi;
	long *cl, *lvar;
	unsigned long buf_count, slot_count;
	unsigned long r1, r2, r3;
	long count;
	int init_ok;

	cl = param_4;
	obj = (unsigned long *)sk_alloc_vas(0x210, 0x10f00402e5e4be7);	/* FUN_000101a0 */
	obj_end = obj + 0x42;
	slot = (obj != (unsigned long *)0x0) ? obj_end : (unsigned long *)0x0;
	if (*param_4 == 0) {
		if ((obj_end < obj || slot < obj_end) || obj + 0x2c < obj + 0x2a)
			goto bounds_fault;			/* 0x299d8 */
		*param_4 = (long)(obj + 0x2a);
	}
	uVar14 = 0;
	uVar9 = sk_rt_00015388(3, param_1);		/* FUN_00015388 */
	init_ok = sk_rt_0005ab94(1, 1);			/* FUN_0005ab94 */
	if (init_ok == 1) {
		buf_count = 0x400;
		uVar14 = 0x1000040eed21634;
		buf_lo = sk_zone_alloc_obj(0x400, 0x30);	/* FUN_00010244 */
		buf_hi = (buf_lo != 0) ? buf_lo + 0xc000 : 0;
	} else {
		buf_lo = 0;
		buf_count = 0;
		buf_hi = 0;
	}
	if (((obj_end < obj) || (slot < obj_end)) ||
	    ((buf_hi < buf_lo) ||
	     ((unsigned long)(((long)(buf_hi - buf_lo) >> 4) * -0x5555555555555555) < buf_count))) {
bounds_fault:
		/* noreturn bounds fault */
		(*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x299dc);
	}
	/* zero-init the whole record, then apply the fixed words */
	for (count = 0; count < 0x42; count++)
		obj[count] = 0;
	obj[0] = 0;
	obj[1] = param_2;
	obj[2] = param_3;
	obj[3] = uVar9;
	obj[4] = (unsigned long)param_4;
	obj[0x30] = 0x100;
	obj[0x3e] = buf_count;
	obj[0x40] = buf_lo;
	slot_base = obj + 5;
	obj[6] = 0;
	*slot_base = 0;

	/* install the dispatch/method table: each entry is a 10-word descriptor */
	sk_mtx_lock((void *)0x6ac250);			/* FUN_00118164 */
	*obj = _DAT_006ac260;				/* head push */
	_DAT_006ac260 = (unsigned long)obj;
	sk_mtx_unlock((void *)0x6ac250);		/* FUN_00118194 */
	uVar9 = DAT_004bbfd8;

	record[0] = 0x6ad3a8; record[1] = uVar9; record[2] = 0x299e0; record[3] = 0x65ae70;
	record[4] = (unsigned long)obj; record[5] = (unsigned long)slot;
	record[6] = (unsigned long)obj; record[7] = (unsigned long)param_4;
	record[8] = param_2; record[9] = param_3;
	obj[5] = sk_dispatch_async(record);		/* FUN_0004b520 */

	record[2] = 0x29ae8; record[3] = 0x65ae90;
	obj[6] = sk_dispatch_async(record);

	record[2] = 0x29c7c; record[3] = 0x65aeb0;	/* FUN_00029c7c */
	obj[7] = sk_dispatch_async(record);

	record[2] = 0x29e3c; record[3] = 0x65aed0;	/* FUN_00029e3c */
	obj[8] = sk_dispatch_async(record);

	record[2] = 0x29ff0; record[3] = 0x65aef0;	/* FUN_00029ff0 */
	obj[9] = sk_dispatch_async(record);

	record[2] = 0x2a1dc; record[3] = 0x65af10;	/* FUN_0002a1dc */
	obj[0x10] = sk_dispatch_async(record);

	record[2] = 0x2a530; record[3] = 0x65af60;	/* FUN_0002a530 */
	obj[0x11] = sk_dispatch_async(record);

	record[2] = 0x2aa84; record[3] = 0x65afa0;	/* FUN_0002aa84 */
	obj[0x12] = sk_dispatch_async(record);

	record[2] = 0x2ae28; record[3] = 0x65afe0;	/* FUN_0002ae28 */
	obj[0x13] = sk_dispatch_async(record);

	record[2] = 0x2b1f8; record[3] = 0x65b000;	/* FUN_0002b1f8 */
	obj[10] = sk_dispatch_async(record);

	record[2] = 0x2b724; record[3] = 0x65b020;	/* FUN_0002b724 */
	obj[0x14] = sk_dispatch_async(record);

	record[2] = 0x2ba98; record[3] = 0x65b070;	/* vas_fh_handle_state */
	obj[0x19] = sk_dispatch_async(record);

	record[2] = 0x2bea0; record[3] = 0x65b0b0;	/* vas_fh_delete */
	obj[0x1a] = sk_dispatch_async(record);

	record[2] = 0x2c0c0; record[3] = 0x65b100;	/* vas_fh_size */
	obj[0x1b] = sk_dispatch_async(record);

	record[2] = 0x2c328; record[3] = 0x65b150;	/* vas_fh_get_range */
	obj[0x1c] = sk_dispatch_async(record);

	record[2] = 0x2c62c; record[3] = 0x65b1a0;	/* vas_fh_get_range2 */
	obj[0x1d] = sk_dispatch_async(record);

	record[2] = 0x2c930; record[3] = 0x65b1e0;	/* vas_fh_unregister */
	obj[0x1e] = sk_dispatch_async(record);

	record[2] = 0x2cb5c; record[3] = 0x65b260;	/* vas_fh_move */
	obj[0x15] = sk_dispatch_async(record);

	record[2] = 0x2d040; record[3] = 0x65b2b0;	/* vas_fh_swap */
	obj[0x16] = sk_dispatch_async(record);

	record[2] = 0x2d3b0; record[3] = 0x65b300;	/* vas_fh_resize */
	obj[0x17] = sk_dispatch_async(record);

	record[2] = 0x2d6dc; record[3] = 0x65b340;	/* vas_fh_state_set */
	obj[0x1f] = sk_dispatch_async(record);

	record[2] = 0x2d93c; record[3] = 0x65b3a0;	/* vas_fh_detach_sync */
	obj[0x18] = sk_dispatch_async(record);

	record[2] = 0x2db3c; record[3] = 0x65b3c0;	/* vas_fh_map_dispatch */
	obj[0xb] = sk_dispatch_async(record);

	record[2] = 0x2dd1c; record[3] = 0x65b3e0;	/* vas_fh_map6_dispatch */
	obj[0xc] = sk_dispatch_async(record);

	record[2] = 0x2defc; record[3] = 0x65b400;	/* vas_fh_map15_dispatch */
	obj[0xd] = sk_dispatch_async(record);

	record[2] = 0x2e0dc; record[3] = 0x65b420;	/* vas_fh_map14_dispatch */
	obj[0xe] = sk_dispatch_async(record);

	record[2] = 0x2e2bc; record[3] = 0x65b440;	/* vas_fh_clear */
	obj[0xf] = sk_dispatch_async(record);

	record[2] = 0x2e460; record[3] = 0x65b460;	/* vas_fh_clear2 */
	obj[0x21] = sk_dispatch_async(record);

	record[2] = 0x2e604; record[3] = 0x65b480;	/* vas_fh_get */
	obj[0x22] = sk_dispatch_async(record);

	record[2] = 0x2eb48; record[3] = 0x65b4a0;
	obj[0x24] = sk_dispatch_async(record);

	record[2] = 0x2ee90; record[3] = 0x65b4c0;	/* FUN_0002ee90 */
	obj[0x23] = sk_dispatch_async(record);

	record[2] = 0x2f09c; record[3] = 0x65b4e0;	/* FUN_0002f09c */
	obj[0x20] = sk_dispatch_async(record);

	record[2] = 0x2f240; record[3] = 0x65b500;	/* FUN_0002f240 */
	obj[0x25] = sk_dispatch_async(record);

	record[2] = 0x2f3fc; record[3] = 0x65b520;	/* FUN_0002f3fc */
	obj[0x26] = sk_dispatch_async(record);

	record[2] = 0x2f5b0; record[3] = 0x65b540;	/* FUN_0002f5b0 */
	obj[0x27] = sk_dispatch_async(record);

	record[2] = 0x2f780; record[3] = 0x65b560;	/* FUN_0002f780 */
	obj[0x28] = sk_dispatch_async(record);

	init_ok = sk_rt_000465c4(obj[3], slot_base);	/* FUN_000465c4 */
	if (init_ok == 0)
		return obj;

	/* first request-slot allocation (12-word records) */
	lvar = (long *)sk_rt_004b1a74();		/* FUN_004b1a74 */
	tail_a = (unsigned long)lvar;
	tail_b = (unsigned long)obj;			/* auVar21._8_8_ placeholder */
	rcode = *(unsigned long *)((char *)lvar + 0x20);
	if ((rcode < *(unsigned long *)((char *)lvar + 0x28)) ||
	    (*(unsigned long *)((char *)lvar + 0x30) < rcode))
		goto bounds_fault2;			/* 0x29ae4 */
	slot6 = (unsigned long *)(rcode + 0x1f0);
	if ((slot6 == (unsigned long *)(rcode + 0x208)) ||
	    ((rcode + 0x210 < rcode) && (rcode < *(unsigned long *)((char *)lvar + 0x28))) ||
	    (*(unsigned long *)((char *)lvar + 0x30) < rcode + 0x210))
		goto bounds_fault2;			/* 0x29ae4 */
	slot_count = *slot6;
	if (slot_count == 0) {
		slot = (unsigned long *)0x0;
	} else {
		count = *(long *)(rcode + 0x1f8);
		*(long *)(rcode + 0x1f8) = count + 1;
		r1 = count + 1;
		r2 = (slot_count != 0) ? r1 / slot_count : 0;
		slot_base = *(unsigned long **)(rcode + 0x200);
		slot = slot_base + (r1 - r2 * slot_count) * 0xc;
		if ((slot < slot_base || slot_base + slot_count * 0xc < slot + 0xc) || slot + 0xc < slot)
			goto bounds_fault2;		/* 0x29ae4 */
		*(unsigned int *)slot = 1;
		*(unsigned char *)(slot + 1) = 1;
		*(unsigned long *)((char *)slot + 0xd) = 0;
		*(unsigned long *)((char *)slot + 5) = 0;
		*(unsigned long *)((char *)slot + 0x1d) = 0;
		*(unsigned long *)((char *)slot + 0x15) = 0;
		*(unsigned long *)(slot + 10) = 0;
		*(unsigned long *)(slot + 8) = 0;
	}
	sk_mtx_lock(**(void ***)((char *)lvar + 0x38));	/* FUN_00118164 */
	lvar = (long *)sk_rt_00031a8c(*(unsigned long *)((char *)lvar + 0x40),
	                             *(unsigned long *)((char *)lvar + 0x48));	/* FUN_00031a8c */
	if (lvar != 0) {
		sk_mtx_unlock(**(void ***)((char *)lvar + 0x38));	/* FUN_00118194 */
		if (slot != (unsigned long *)0x0) {
			*(long *)(slot + 8) = (long)lvar;
			*(unsigned long *)(slot + 10) = 0;
			*(unsigned char *)(slot + 1) = 0;
		}
		/* indirect dispatch through (auVar21._8_8_ + 0x10) */
		return (unsigned long *)(*(void (**)(unsigned long, long))
		       *(unsigned long *)(tail_b + 0x10))(tail_b, (long)lvar);
	}
	/* second request-slot allocation (6-word records) */
	lvar = (long *)sk_rt_004b1aac();		/* FUN_004b1aac */
	tail_b = (unsigned long)lvar;
	rcode = *(unsigned long *)((char *)lvar + 0x20);
	if ((rcode < *(unsigned long *)((char *)lvar + 0x28)) ||
	    (*(unsigned long *)((char *)lvar + 0x30) < rcode))
		goto bounds_fault2;			/* 0x29c6c */
	slot6 = (unsigned long *)(rcode + 0x1f0);
	if ((slot6 == (unsigned long *)(rcode + 0x208)) ||
	    ((rcode + 0x210 < rcode) && (rcode < *(unsigned long *)((char *)lvar + 0x28))) ||
	    (*(unsigned long *)((char *)lvar + 0x30) < rcode + 0x210))
		goto bounds_fault2;			/* 0x29c6c */
	slot_count = *slot6;
	if (slot_count == 0) {
		slot = (unsigned long *)0x0;
	} else {
		count = *(long *)(rcode + 0x1f8);
		*(long *)(rcode + 0x1f8) = count + 1;
		r1 = count + 1;
		r2 = (slot_count != 0) ? r1 / slot_count : 0;
		slot_base = *(unsigned long **)(rcode + 0x200);
		slot = slot_base + (r1 - r2 * slot_count) * 6;
		if ((slot < slot_base || slot_base + slot_count * 6 < slot + 6) || slot + 6 < slot)
			goto bounds_fault2;		/* 0x29c6c */
		slot[0] = 0x100000002;
		slot[1] = tail_b;
		slot[2] = uVar14;
		slot[3] = 0;
		slot[4] = 0;
		slot[5] = 0;
	}
	r1 = 0;
	r2 = 0;
	r3 = 0;
	sbuf = 0;
	ecode = uVar14;
	sk_mtx_lock(**(void ***)((char *)lvar + 0x38));	/* FUN_00118164 */
	rcode = (*(unsigned long (**)(unsigned long, unsigned long, unsigned long *, unsigned long *))
	       **(unsigned long ***)((char *)lvar + 0x48))
	       (*(unsigned long *)((char *)lvar + 0x40), tail_b, &sbuf, &ecode);
	sk_mtx_unlock(**(void ***)((char *)lvar + 0x38));	/* FUN_00118194 */
	if ((rcode & 0xff) == 0) {
		sk_rt_000462f8(&r1, sbuf, ecode);	/* FUN_000462f8 */
		if (slot == (unsigned long *)0x0)
			goto finish;
		slot[4] = sbuf;
		slot[5] = ecode;
	} else {
		if (5 < ((unsigned int)rcode & 0xff) - 1)
			sk_swift_fatal("unknown vas return code 0x%x");	/* FUN_004afae4 */
		sk_rt_00046304(&r1, rcode & 0xffff00ff);	/* FUN_00046304 */
		if (slot == (unsigned long *)0x0)
			goto finish;
		*(char *)((long)slot + 1) = (char)rcode;
		*(short *)((long)slot + 2) = (short)(rcode >> 0x10);
	}
	*(unsigned char *)((long)slot + 4) = 0;
finish:
	slot_hi = r2;
	slot_base = (unsigned long *)r1;
	rcode = r3;
	/* caller completion callback through param_4[2] */
	return (unsigned long *)(*(void (**)(long *, unsigned long *))cl[2])(cl, &slot_hi);
bounds_fault2:
	/* noreturn bounds fault */
	(*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x29c6c);
	return 0;	/* unreachable */
}
/*--------------------------------------------------------------------*/
/* FUN_00029c7c @ 0x00029c7c   (est. vas_fh_attach)
 * Ghidra: void FUN_00029c7c(long param_1, undefined8 param_2, ulong param_3, long param_4)
 * Attaches a fault handler to the VAS: claims the next fault-handler request
 * slot in the round-robin ring (self+0x20 base, count at +0x1f0, next at
 * +0x1f8, free-list at +0x200), stamps it with kind 0x100000003, then
 * allocates a physical page (sk_phys_alloc) and maps it through the VAS
 * fault-map method (*(self+0x48)+0x40). The result is encoded and the reply
 * is delivered through param_4+0x10. On map failure the page is released.
 * Confidence: medium
 * Notes: shared request-slot preamble; ring bounds trap 0x5519 @0x29e2c;
 *   result encoders sk_rt_00046304/314; s_unknown_vas_return_code_0x_x_005ae5cc.
 */
void vas_fh_attach(long self, unsigned long key, unsigned long size, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned long *freebase, *slot;
    unsigned long page, status;
    unsigned long res_lo, res_hi;
    bool end_over, start_under;

    ring = *(unsigned long *)(self + 0x20);
    end = ring + 0x210;
    end_over = *(unsigned long *)(self + 0x28) < end;
    start_under = ring < *(unsigned long *)(self + 0x30);
    freebase = (unsigned long *)(ring + 0x1f0);
    if ((((end_over || end < ring) || start_under) || (unsigned long *)(ring + 0x208) <= freebase) &&
        (((end_over || end < ring) || start_under) || freebase != (unsigned long *)(ring + 0x208))) {
        /* ring out of bounds: trap 0x5519 @0x29e2c */
        (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x29e2c);
    }
    count = *freebase;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        next = *(long *)(ring + 0x1f8);
        *(long *)(ring + 0x1f8) = next + 1;
        idx = 0;
        if (count != 0) {
            idx = (next + 1) / count;
        }
        freebase = *(unsigned long **)(ring + 0x200);
        slot = freebase + ((next + 1) - idx * count) * 6;
        if ((slot < freebase || freebase + count * 6 < slot + 6) || slot + 6 < slot) {
            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x29e2c);
        }
        *slot = 0x100000003;
        slot[1] = key;
        slot[2] = size & 0xffffffff;
        slot[3] = 0;
        slot[4] = 0;
        slot[5] = 0;
    }
    res_lo = 0;
    res_hi = 0;
    page = sk_phys_alloc();                 /* FUN_00034f70 */
    if (page == 0) {
        sk_rt_00046304(&res_lo, 2);
        if (slot != (unsigned long *)0) {
            *(unsigned char *)((char *)slot + 1) = 2;
            *(unsigned short *)((char *)slot + 2) = 0;
        }
    } else {
        sk_mtx_lock(**(unsigned long **)(self + 0x38));       /* FUN_00118164 */
        status = (*(unsigned long (**)(unsigned long, unsigned long, unsigned long, unsigned long))
                  (*(long *)(self + 0x48) + 0x40))
                 (*(unsigned long *)(self + 0x40), key, size, page);
        sk_mtx_unlock(**(unsigned long **)(self + 0x38));     /* FUN_00118194 */
        if ((status & 0xff) == 0) {
            sk_rt_00046314(&res_lo, page);
            if (slot != (unsigned long *)0) {
                *(unsigned char *)((char *)slot + 4) = 0;
                slot[4] = 0;
                slot[5] = 0;
            }
            goto done;
        }
        cl4_destroy_elem(page);             /* FUN_004b23d8 */
        if (5 < ((unsigned int)status & 0xff) - 1) {
            /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
            sk_swift_fatal("unknown vas return code 0x%x");
        }
        sk_rt_00046304(&res_lo, status & 0xffff00ff);
        if (slot != (unsigned long *)0) {
            *(char *)((char *)slot + 1) = (char)status;
            *(short *)((char *)slot + 2) = (short)(status >> 0x10);
        }
    }
    *(unsigned char *)((char *)slot + 4) = 0;
done:
    (*(void (**)(long, unsigned long, unsigned long))(reply + 0x10))(reply, res_lo, res_hi);
}

/*--------------------------------------------------------------------*/
/* FUN_00029e3c @ 0x00029e3c   (est. vas_fh_detach)
 * Ghidra: void FUN_00029e3c(long param_1, long param_2)
 * Detaches a fault handler from the VAS: claims the next request slot (kind 4,
 * 4-byte stride records), allocates a page and unmaps it through the VAS
 * fault-unmap method (*(self+0x48)+0x48). The result is encoded and the reply
 * is delivered through param_2+0x10. On failure the page is released.
 * Confidence: medium
 * Notes: shared request-slot preamble; ring bounds trap 0x5519 @0x29fe0;
 *   result encoders sk_rt_00046304/314; s_unknown_vas_return_code_0x_x_005ae5cc.
 */
void vas_fh_detach(long self, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned int *freebase, *slot;
    unsigned long page, status;
    unsigned long res_lo, res_hi;
    bool end_over, start_under;

    ring = *(unsigned long *)(self + 0x20);
    end = ring + 0x210;
    end_over = *(unsigned long *)(self + 0x28) < end;
    start_under = ring < *(unsigned long *)(self + 0x30);
    freebase = (unsigned int *)(ring + 0x1f0);
    if ((((end_over || end < ring) || start_under) || (unsigned int *)(ring + 0x208) <= freebase) &&
        (((end_over || end < ring) || start_under) || freebase != (unsigned int *)(ring + 0x208))) {
        /* ring out of bounds: trap 0x5519 @0x29fe0 */
        (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x29fe0);
    }
    count = *(unsigned long *)freebase;
    if (count == 0) {
        slot = (unsigned int *)0;
    } else {
        next = *(long *)(ring + 0x1f8);
        *(long *)(ring + 0x1f8) = next + 1;
        idx = 0;
        if (count != 0) {
            idx = (next + 1) / count;
        }
        freebase = *(unsigned int **)(ring + 0x200);
        slot = freebase + ((next + 1) - idx * count) * 0xc;
        if ((slot < freebase || freebase + count * 0xc < slot + 0xc) || slot + 0xc < slot) {
            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x29fe0);
        }
        *slot = 4;
        *(unsigned char *)((unsigned int *)slot + 1) = 1;
        *(unsigned long *)((char *)slot + 0xd) = 0;
        *(unsigned long *)((char *)slot + 5) = 0;
        *(unsigned long *)((char *)slot + 0x1d) = 0;
        *(unsigned long *)((char *)slot + 0x15) = 0;
        *(unsigned long *)((unsigned int *)slot + 10) = 0;
        *(unsigned long *)((unsigned int *)slot + 8) = 0;
    }
    res_lo = 0;
    res_hi = 0;
    page = sk_phys_alloc();                 /* FUN_00034f70 */
    if (page == 0) {
        sk_rt_00046304(&res_lo, 2);
        if (slot != (unsigned int *)0) {
            *(unsigned char *)((char *)slot + 1) = 2;
            *(unsigned short *)((char *)slot + 2) = 0;
        }
    } else {
        sk_mtx_lock(**(unsigned long **)(self + 0x38));       /* FUN_00118164 */
        status = (*(unsigned long (**)(unsigned long, unsigned long))
                  (*(long *)(self + 0x48) + 0x48))
                 (*(unsigned long *)(self + 0x40), page);
        sk_mtx_unlock(**(unsigned long **)(self + 0x38));     /* FUN_00118194 */
        if ((status & 0xff) == 0) {
            if (slot != (unsigned int *)0) {
                *(unsigned char *)((unsigned int *)slot + 1) = 0;
                *(unsigned long *)((unsigned int *)slot + 8) = 0;
                *(unsigned long *)((unsigned int *)slot + 10) = 0;
            }
            sk_rt_00046314(&res_lo, page);
            goto done;
        }
        cl4_destroy_elem(page);             /* FUN_004b23d8 */
        if (5 < ((unsigned int)status & 0xff) - 1) {
            /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
            sk_swift_fatal("unknown vas return code 0x%x");
        }
        sk_rt_00046304(&res_lo, status & 0xffff00ff);
        if (slot != (unsigned int *)0) {
            *(char *)((char *)slot + 1) = (char)status;
            *(short *)((char *)slot + 2) = (short)(status >> 0x10);
        }
    }
    *(unsigned char *)((unsigned int *)slot + 1) = 0;
done:
    (*(void (**)(long, unsigned long, unsigned long))(reply + 0x10))(reply, res_lo, res_hi);
}

/*--------------------------------------------------------------------*/
/* FUN_00029ff0 @ 0x00029ff0   (est. vas_fh_kind)
 * Ghidra: void FUN_00029ff0(long param_1, undefined8 param_2, uint param_3, long param_4)
 * Sets the fault-handler kind for a VAS entry: claims a request slot (kind
 * 0x100000007) carrying the key and the new kind, validates the kind, then
 * calls the fault-kind method (*(self+0x48)+0x50). A successful return
 * records the fault-kind cookie (DAT_004bbff0/bbff8) in the slot and replies
 * with 1; error codes are encoded and replied.
 * Confidence: medium
 * Notes: shared request-slot preamble; trap 0x5519 @0x2a1ac;
 *   s_unknown_easm_fault_kind_0x_x_005ae5e9; s_unknown_vas_return_code_0x_x_005ae5cc.
 */
void vas_fh_kind(long self, unsigned long key, unsigned int kind, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned long *freebase, *slot;
    unsigned long status, kind_cookie;
    unsigned int res_lo;
    unsigned short res_hi;
    bool end_over, start_under;

    ring = *(unsigned long *)(self + 0x20);
    end = ring + 0x210;
    end_over = *(unsigned long *)(self + 0x28) < end;
    start_under = ring < *(unsigned long *)(self + 0x30);
    freebase = (unsigned long *)(ring + 0x1f0);
    if ((((end_over || end < ring) || start_under) || (unsigned long *)(ring + 0x208) <= freebase) &&
        (((end_over || end < ring) || start_under) || freebase != (unsigned long *)(ring + 0x208))) {
        (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a1ac);
    }
    count = *freebase;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        next = *(long *)(ring + 0x1f8);
        *(long *)(ring + 0x1f8) = next + 1;
        idx = 0;
        if (count != 0) {
            idx = (next + 1) / count;
        }
        freebase = *(unsigned long **)(ring + 0x200);
        slot = freebase + ((next + 1) - idx * count) * 6;
        if ((slot < freebase || freebase + count * 6 < slot + 6) || slot + 6 < slot) {
            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a1ac);
        }
        *slot = 0x100000007;
        slot[1] = key;
        slot[2] = (unsigned long)kind;
        slot[3] = 0;
        slot[4] = 0;
        slot[5] = 0;
    }
    if (2 < kind - 1) {
        /* FUN_004afae4 s_unknown_easm_fault_kind_0x_x_005ae5e9 */
        sk_swift_fatal("unknown easm fault kind 0x%x");
    }
    sk_mtx_lock(**(unsigned long **)(self + 0x38));           /* FUN_00118164 */
    status = (*(unsigned long (**)(unsigned long, unsigned long, unsigned int))
              (*(long *)(self + 0x48) + 0x50))
             (*(unsigned long *)(self + 0x40), key, (kind - 1) & 0xff);
    sk_mtx_unlock(**(unsigned long **)(self + 0x38));         /* FUN_00118194 */
    kind_cookie = *(unsigned long *)0x4bbff0;   /* _DAT_004bbff0 */
    res_hi = 0;
    res_lo = 0;
    if (((unsigned int)status & 0xff) == 5) {
        if (slot != (unsigned long *)0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        kind_cookie = 0;
    } else {
        if ((status & 0xff) != 0) {
            if (slot != (unsigned long *)0) {
                if (5 < ((unsigned int)status & 0xff) - 1) {
                    /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                    sk_swift_fatal("unknown vas return code 0x%x");
                }
                *(char *)((char *)slot + 1) = (char)status;
                *(short *)((char *)slot + 2) = (short)(status >> 0x10);
                *(unsigned char *)((char *)slot + 4) = 0;
            }
            if (5 < ((unsigned int)status & 0xff) - 1) {
                /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                sk_swift_fatal("unknown vas return code 0x%x");
            }
            sk_rt_000462e8(&res_lo, status & 0xffff00ff);
            goto reply;
        }
        if (slot != (unsigned long *)0) {
            slot[5] = *(unsigned long *)0x4bbff8;
            slot[4] = kind_cookie;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        kind_cookie = 1;
    }
    sk_rt_00046380(&res_lo, kind_cookie);
reply:
    (*(void (**)(long, unsigned long))(reply + 0x10))(reply,
        (unsigned long)(((unsigned long)res_hi << 32) | res_lo));
}

/*--------------------------------------------------------------------*/
/* FUN_0002a1dc @ 0x0002a1dc   (est. vas_fh_add_range)
 * Ghidra: void FUN_0002a1dc(long param_1, long param_2)
 * Adds a fault-handler address range to the VAS: claims a request slot (kind 8,
 * 4-byte stride records), then calls the range-allocation method
 * (*(self+0x48)+0x58) and the region-setup method (*(self+0x48)+0x30). On
 * success a fresh range id is allocated (scanning the table at self+0x20
 * base, entries at +0x190 stride 0x48, next-id at +0x180, count at +0x188)
 * and a new 9-word entry is appended; the result is encoded and replied.
 * Confidence: medium
 * Notes: shared request-slot preamble; trap 0x5519 @0x2a508;
 *   s_unknown_vas_return_code_0x_x_005ae5cc.
 */
void vas_fh_add_range(long self, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned int *freebase, *slot;
    unsigned long status, key;
    long range_id, entries, cnt;
    unsigned long *slot2;
    bool end_over, start_under;
    unsigned long res_lo, res_hi;
    unsigned long r0, r1, r2, r3, r4;
    unsigned long d0, d1, d2, d3, d4;

    ring = *(unsigned long *)(self + 0x20);
    end = ring + 0x210;
    end_over = *(unsigned long *)(self + 0x28) < end;
    start_under = ring < *(unsigned long *)(self + 0x30);
    freebase = (unsigned int *)(ring + 0x1f0);
    if ((((end_over || end < ring) || start_under) || (unsigned int *)(ring + 0x208) <= freebase) &&
        (((end_over || end < ring) || start_under) || freebase != (unsigned int *)(ring + 0x208))) {
        (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a508);
    }
    count = *(unsigned long *)freebase;
    if (count == 0) {
        slot = (unsigned int *)0;
    } else {
        next = *(long *)(ring + 0x1f8);
        *(long *)(ring + 0x1f8) = next + 1;
        idx = 0;
        if (count != 0) {
            idx = (next + 1) / count;
        }
        freebase = *(unsigned int **)(ring + 0x200);
        slot = freebase + ((next + 1) - idx * count) * 0xc;
        if ((slot < freebase || freebase + count * 0xc < slot + 0xc) || slot + 0xc < slot) {
            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a508);
        }
        *slot = 8;
        *(unsigned char *)((unsigned int *)slot + 1) = 1;
        *(unsigned long *)((char *)slot + 0xd) = 0;
        *(unsigned long *)((char *)slot + 5) = 0;
        *(unsigned long *)((char *)slot + 0x1d) = 0;
        *(unsigned long *)((char *)slot + 0x15) = 0;
        *(unsigned long *)((unsigned int *)slot + 10) = 0;
        *(unsigned long *)((unsigned int *)slot + 8) = 0;
    }
    res_lo = 0;
    res_hi = 0;
    sk_mtx_lock(**(unsigned long **)(self + 0x38));           /* FUN_00118164 */
    ring = *(unsigned long *)(self + 0x20);
    if (*(unsigned long *)(self + 0x28) < ring + 0x210 || ring < *(unsigned long *)(self + 0x30)) {
        (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a508);
    }
    if (*(long *)(ring + 0x188) == 0) {
        r0 = 0;
        r1 = 0;
        r2 = 0;
        r3 = 0;
        r4 = 0;
        status = (*(unsigned long (**)(unsigned long, unsigned long *))
                  (*(long *)(self + 0x48) + 0x58))
                 (*(unsigned long *)(self + 0x40), &r0);
        if ((status & 0xff) == 0) {
            d0 = DAT_004bc000;
            d1 = *(unsigned long *)0x4bc008;
            d2 = DAT_004bc010;
            d3 = *(unsigned long *)0x4bc018;
            status = (*(unsigned long (**)(unsigned long, unsigned long, unsigned long *,
                                           unsigned long *, unsigned long, unsigned long *))
                      (*(long *)(self + 0x48) + 0x30))
                     (*(unsigned long *)(self + 0x40), 0x1808, &d0, &r3, 0, &d0);
            if ((status & 0xff) == 0) {
                ring = *(unsigned long *)(self + 0x20);
                if ((ring != 0) &&
                   (((ring + 0x210 < ring) || (*(unsigned long *)(self + 0x28) < ring + 0x210)) ||
                    (ring < *(unsigned long *)(self + 0x30)))) {
                    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a508);
                }
                range_id = *(long *)(ring + 0x180);
                cnt = *(long *)(ring + 0x188);
                if (cnt != 0) {
                    entries = ring + 400;
                    next = entries;
                    while (1) {
                        if (((next < entries) || (ring + 0x1d8 < next + 0x48)) ||
                            (next + 0x48 < next)) {
                            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a508);
                        }
                        if (range_id != *(long *)(next + 0x18)) break;
                        range_id = range_id + 1;
                        next = entries;
                    }
                    /* scan remaining entries for the bumped id */
                    next = next + 0x48;
                    cnt = cnt + -1;
                    while (cnt != 0) {
                        if (((next < entries) || (ring + 0x1d8 < next + 0x48)) || (next + 0x48 < next)) {
                            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a508);
                        }
                        if (range_id == *(long *)(next + 0x18)) {
                            range_id = range_id + 1;
                            next = entries;
                            cnt = *(long *)(ring + 0x188);
                        } else {
                            next = next + 0x48;
                            cnt = cnt + -1;
                        }
                    }
                }
                *(long *)(ring + 0x180) = range_id + 1;
                ring = *(unsigned long *)(self + 0x20);
                if (((*(unsigned long *)(self + 0x28) < ring + 0x210) ||
                     (ring < *(unsigned long *)(self + 0x30))) ||
                    (slot2 = (unsigned long *)(ring + 400) + *(long *)(ring + 0x188) * 9,
                     (slot2 < (unsigned long *)(ring + 400) ||
                     (unsigned long *)(ring + 0x1d8) < slot2 + 9) || slot2 + 9 < slot2)) {
                    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a508);
                }
                slot2[1] = r1;
                *slot2 = r0;
                slot2[2] = r2;
                slot2[3] = (unsigned long)range_id;
                slot2[4] = 0;
                slot2[5] = 0;
                slot2[7] = r4;
                slot2[6] = r3;
                slot2[8] = d1;
                ring = *(unsigned long *)(self + 0x20);
                if ((*(unsigned long *)(self + 0x28) < ring + 0x210) ||
                    (ring < *(unsigned long *)(self + 0x30))) {
                    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a508);
                }
                *(long *)(ring + 0x188) = *(long *)(ring + 0x188) + 1;
                sk_mtx_unlock(**(unsigned long **)(self + 0x38));     /* FUN_00118194 */
                sk_rt_00046314(&res_lo, (unsigned long)range_id);
                if (slot != (unsigned int *)0) {
                    *(long *)((unsigned int *)slot + 8) = range_id;
                    *(unsigned long *)((unsigned int *)slot + 10) = 0;
                    *(unsigned char *)((unsigned int *)slot + 1) = 0;
                }
                goto reply;
            }
            /* region-setup failed: error callback (local_48+0x10)(local_58, uStack_50) */
            (*(void (**)(long, unsigned long))(r2 + 0x10))(r0, r1);
        }
    } else {
        status = 0x2de0005;
    }
    sk_mtx_unlock(**(unsigned long **)(self + 0x38));         /* FUN_00118194 */
    if (slot != (unsigned int *)0) {
        if (5 < ((unsigned int)status & 0xff) - 1) {
            /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
            sk_swift_fatal("unknown vas return code 0x%x");
        }
        *(char *)((char *)slot + 1) = (char)status;
        *(short *)((char *)slot + 2) = (short)(status >> 0x10);
        *(unsigned char *)((unsigned int *)slot + 1) = 0;
    }
    if (5 < ((unsigned int)status & 0xff) - 1) {
        /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
        sk_swift_fatal("unknown vas return code 0x%x");
    }
    sk_rt_00046304(&res_lo, status & 0xffff00ff);
reply:
    (*(void (**)(long, unsigned long, unsigned long))(reply + 0x10))(reply, res_lo, res_hi);
}

/*--------------------------------------------------------------------*/
/* FUN_0002a530 @ 0x0002a530   (est. vas_fh_lookup)
 * Ghidra: undefined8 FUN_0002a530(long param_1, undefined8 param_2,
 *   undefined8 param_3, ulong param_4, long param_5)
 * Resolves an existing fault handler by key: claims a request slot (kind
 * 0x100000009), then looks up the handler via vas_fh_lookup_range (FUN_0002a784)
 * with a callback descriptor pointing at vas_fh_activate (FUN_0002a80c). On
 * success the resolved (4-word) record is encoded through sk_rt_0004636c and
 * replied via param_5+0x10; the request slot is then torn down with
 * sk_rt_0004b8d0 and the lookup result returned.
 * Confidence: medium
 * Notes: shared request-slot preamble; trap 0x5519 @0x2a774; callback desc
 *   (0x6ad3a8, DAT_004bb180, FUN_0002a80c, 0x65af30); s_unknown_vas_return_code_0x_x_005ae5cc.
 */
unsigned long vas_fh_lookup(long self, unsigned long key, unsigned long param3,
                            unsigned long kind, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned long *freebase, *slot;
    unsigned long status;
    unsigned long *local_b8, *local_e0;
    unsigned long desc[6];
    unsigned long res[5];
    unsigned long out[5];
    unsigned long ret;
    bool ok, under;

    ring = *(unsigned long *)(self + 0x20);
    end = ring + 0x210;
    ok = (end <= *(unsigned long *)(self + 0x28));
    under = (*(unsigned long *)(self + 0x30) <= ring);
    freebase = (unsigned long *)(ring + 0x1f0);
    if (((ok && ring <= end) && under) && freebase < (unsigned long *)(ring + 0x208) ||
        ((ok && ring <= end) && under) && freebase == (unsigned long *)(ring + 0x208)) {
        count = *freebase;
        if (count == 0) {
            slot = (unsigned long *)0;
        } else {
            next = *(long *)(ring + 0x1f8);
            *(long *)(ring + 0x1f8) = next + 1;
            idx = 0;
            if (count != 0) {
                idx = (next + 1) / count;
            }
            freebase = *(unsigned long **)(ring + 0x200);
            slot = freebase + ((next + 1) - idx * count) * 6;
            if ((slot < freebase || freebase + count * 6 < slot + 6) || slot + 6 < slot) {
                (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a774);
            }
            *slot = 0x100000009;
            slot[1] = key;
            slot[2] = param3;
            slot[3] = kind & 0xffffffff;
            slot[4] = 0;
            slot[5] = 0;
        }
        res[4] = 0;
        res[2] = 0;
        res[3] = 0;
        res[0] = 0;
        res[1] = 0;
        out[0] = 0;
        out[1] = DAT_004bbfe0;
        out[4] = 0;
        out[2] = 0;
        out[3] = 0;
        local_b8 = out;
        sk_mtx_lock(**(unsigned long **)(self + 0x38));       /* FUN_00118164 */
        ring = *(unsigned long *)(self + 0x20);
        if ((ring == 0) ||
           ((ring <= ring + 0x210 && (ring + 0x210 <= *(unsigned long *)(self + 0x28))) &&
            (*(unsigned long *)(self + 0x30) <= ring))) {
            desc[0] = 0x6ad3a8;
            desc[1] = DAT_004bb180;
            desc[2] = (unsigned long)vas_fh_activate;   /* FUN_0002a80c */
            desc[3] = 0x65af30;
            desc[4] = kind;                 /* local_c0 = (undefined1)param_4 */
            local_e0 = local_b8;
            status = vas_fh_lookup_range(ring, key, (long)desc);   /* FUN_0002a784 */
            sk_mtx_unlock(**(unsigned long **)(self + 0x38));      /* FUN_00118194 */
            if ((status & 0xff) == 0) {
                res[3] = local_b8[3];
                res[0] = local_b8[4];
                res[4] = local_b8[5];
                res[1] = local_b8[6];
                sk_rt_0004636c(res, &res[0]);
            } else {
                if (5 < ((unsigned int)status & 0xff) - 1) {
                    /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                    sk_swift_fatal("unknown vas return code 0x%x");
                }
                sk_rt_00046304(res, status & 0xffff00ff);
                if (slot != (unsigned long *)0) {
                    *(char *)((char *)slot + 1) = (char)status;
                    *(short *)((char *)slot + 2) = (short)(status >> 0x10);
                    *(unsigned char *)((char *)slot + 4) = 0;
                }
            }
            out[4] = res[2];
            out[0] = res[0];
            out[3] = res[1];
            out[1] = res[3];
            out[2] = res[4];
            ret = (*(unsigned long (**)(long, unsigned long *))(reply + 0x10))(reply, out);
            sk_rt_0004b8d0(local_b8, 8);
            return ret;
        }
    }
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a774);
}

/*--------------------------------------------------------------------*/
/* FUN_0002a784 @ 0x0002a784   (est. vas_fh_lookup_range)
 * Ghidra: undefined8 FUN_0002a784(long param_1, long param_2, long param_3)
 * Looks up a fault handler in the VAS region table (entries at self+400 stride
 * 0x48, count at self+0x188) by matching the key stored at entry+0x18. On a
 * match the callback at (desc+0x10) is invoked with the matched entry and its
 * return value returned. If no entry matches, returns 0x1bf0006 (not-found).
 * Confidence: high
 * Notes: region entry bounds trap 0x5519 @0x2a80c.
 */
unsigned long vas_fh_lookup_range(long self, long key, long desc)
{
    long count, entry;

    count = *(long *)(self + 0x188);
    if (count != 0) {
        entry = self + 400;
        do {
            if ((entry != 0) &&
               (((entry < self + 400) || (self + 0x1d8 < entry + 0x48)) ||
                (entry + 0x48 < entry))) {
                (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2a80c);
            }
            if (*(long *)(entry + 0x18) == key) {
                return (*(unsigned long (**)(long, long))(desc + 0x10))(desc, entry);
            }
            entry = entry + 0x48;
            count = count + -1;
        } while (count != 0);
    }
    return 0x1bf0006;
}

/*--------------------------------------------------------------------*/
/* FUN_0002a80c @ 0x0002a80c   (est. vas_fh_activate)
 * Ghidra: ulong FUN_0002a80c(long param_1, undefined8 *param_2)
 * Activates a matched fault-handler record: dispatches on the fault kind
 * (self+0x40 minus one), calls the handler's fault method (param_2[2]+0x10)
 * to prepare the range. If the range is not yet mapped, pages are copied
 * (FUN_0002fa34-style) and mapped via the handler's mapping method
 * (param_2[7]+0x28), the record is marked active, and the mapping is
 * committed. A map/commit failure trips sk_swift_fatal. An already-active
 * handler logs a message and returns 0x3230001.
 * Confidence: low
 * Notes: s_easm__d_FH__lld__p_is_already_ac_005ad5a0;
 *   s_unknown_easm_fault_kind_0x_x_005ae5e9;
 *   s_easm_faulthandler_failed_to_copy_005ad5c5;
 *   s_easm_faulthandler_failed_to_map_c_005ad5ff; trap 0x5519 @0x2aa84;
 *   sk_rt_00046288/2a0/2c8 helpers.
 */
unsigned long vas_fh_activate(long self, unsigned long *rec)
{
    unsigned int kind;
    unsigned long status;
    unsigned long *map_slot;
    unsigned long page;
    unsigned long prep[5];
    unsigned char cbuffer[16];

    if ((*(unsigned char *)(rec + 4) & 1) == 0) {
        kind = *(unsigned char *)(self + 0x40) - 1;
        if (2 < kind) {
            /* FUN_004afae4 s_unknown_easm_fault_kind_0x_x_005ae5e9 */
            sk_swift_fatal("unknown easm fault kind 0x%x");
        }
        status = (*(unsigned long (**)(unsigned long, unsigned long, unsigned long,
                                       unsigned int, unsigned long *))
                  rec[2])(*rec, rec[1], *(unsigned long *)(self + 0x30), kind & 0xff, &prep[0]);
        if ((status & 0xff) == 0) {
            if ((prep[0] & 1) == 0) {
                /* range not mapped: validate + commit mapping */
                map_slot = *(unsigned long **)(*(long *)(self + 0x20) + 8);
                if (map_slot + 0x7 < map_slot + 0x3) goto trap;
                sk_rt_00046288();
                map_slot = *(unsigned long **)(self + 0x38);
                if (map_slot != (unsigned long *)0) {
                    *(unsigned char *)((char *)map_slot + 4) = 0;
                    *(unsigned long *)((char *)map_slot + 0x20) = 0;
                    *(unsigned long *)((char *)map_slot + 0x28) = 0;
                    return 0;
                }
            } else {
                page = sk_phys_alloc();             /* FUN_00034f70 */
                cbuffer[8] = (unsigned char)sk_boot_object().lo;   /* FUN_00034a2c */
                cbuffer[0] = (unsigned char)(sk_boot_object().hi & 0xff);
                status = (*(unsigned long (**)(unsigned long, unsigned long, unsigned int,
                                               unsigned long))
                          (((unsigned long *)sk_boot_object())[1] + 0x40))
                         (((unsigned long *)sk_boot_object())[0], prep[3], 1, page);
                status = status & 0xff;
                if (status != 0) {
                    /* FUN_004afae4 s_easm_faulthandler_failed_to_copy_005ad5c5 */
                    sk_swift_fatal("easm faulthandler failed to copy");
                }
                status = (*(unsigned long (**)(unsigned long, unsigned int, unsigned long))
                          (rec[7] + 0x28))(rec[6], 0, page);
                status = status & 0xff;
                if (status != 0) {
                    /* FUN_004afae4 s_easm_faulthandler_failed_to_map_c_005ad5ff */
                    sk_swift_fatal("easm faulthandler failed to map c");
                }
                cl4_destroy_elem(page);             /* FUN_004b23d8 */
                *(unsigned char *)(rec + 4) = 1;
                rec[5] = prep[2];
                map_slot = *(unsigned long **)(self + 0x38);
                if (map_slot != (unsigned long *)0) {
                    *(unsigned long *)((char *)map_slot + 0x20) = 1;
                    *(unsigned long *)((char *)map_slot + 0x28) = rec[8];
                    *(unsigned char *)((char *)map_slot + 4) = 0;
                }
                map_slot = *(unsigned long **)(*(long *)(self + 0x20) + 8);
                status = (unsigned long)(map_slot + 3);
                if ((unsigned long)map_slot + 0x38 < (unsigned long)(map_slot + 3)) goto trap;
                prep[3] = prep[2];
                prep[0] = 0;
                sk_rt_000462a0(status, prep);
            }
        } else {
            if (((unsigned int)status & 0xff) != 5) {
                return status;
            }
            map_slot = *(unsigned long **)(*(long *)(self + 0x20) + 8);
            if ((unsigned long)map_slot + 0x38 < (unsigned long)(map_slot + 3)) goto trap;
            sk_rt_000462c8();
        }
        status = 0;
    } else {
        sk_printf("easm %d FH %lld %p is already ac");   /* s_easm__d_FH__lld__p_is_already_ac_005ad5a0 */
        status = 0x3230001;
    }
    return status;
trap:
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2aa84);
}

/*--------------------------------------------------------------------*/
/* FUN_0002aa84 @ 0x0002aa84   (est. vas_fh_complete)
 * Ghidra: void FUN_0002aa84(long param_1, undefined8 param_2, undefined8 param_3,
 *   ulong param_4, long param_5)
 * Completes an outstanding fault: claims a request slot (kind 0x10000000a),
 * looks up the handler via vas_fh_lookup_range with a callback descriptor
 * pointing at vas_fh_complete_fault (FUN_0002ac94), and encodes/replies the
 * completion result through param_5+0x10.
 * Confidence: medium
 * Notes: shared request-slot preamble; trap 0x5519 @0x2ac74;
 *   s_unknown_vas_return_code_0x_x_005ae5cc.
 */
void vas_fh_complete(long self, unsigned long key, unsigned long param3,
                     unsigned long kind, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned long *freebase, *slot;
    unsigned long status;
    unsigned int res_lo;
    unsigned short res_hi;
    unsigned long desc[6];
    bool ok, under;

    ring = *(unsigned long *)(self + 0x20);
    end = ring + 0x210;
    ok = (end <= *(unsigned long *)(self + 0x28));
    under = (*(unsigned long *)(self + 0x30) <= ring);
    freebase = (unsigned long *)(ring + 0x1f0);
    if (((ok && ring <= end) && under) && freebase < (unsigned long *)(ring + 0x208) ||
        ((ok && ring <= end) && under) && freebase == (unsigned long *)(ring + 0x208)) {
        count = *freebase;
        if (count == 0) {
            slot = (unsigned long *)0;
        } else {
            next = *(long *)(ring + 0x1f8);
            *(long *)(ring + 0x1f8) = next + 1;
            idx = 0;
            if (count != 0) {
                idx = (next + 1) / count;
            }
            freebase = *(unsigned long **)(ring + 0x200);
            slot = freebase + ((next + 1) - idx * count) * 6;
            if ((slot < freebase || freebase + count * 6 < slot + 6) || slot + 6 < slot) {
                (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2ac74);
            }
            *slot = 0x10000000a;
            slot[1] = key;
            slot[2] = param3;
            slot[3] = kind & 0xffffffff;
            slot[4] = 0;
            slot[5] = 0;
        }
        res_hi = 0;
        res_lo = 0;
        sk_mtx_lock(**(unsigned long **)(self + 0x38));       /* FUN_00118164 */
        ring = *(unsigned long *)(self + 0x20);
        if ((ring == 0) ||
           ((ring <= ring + 0x210 && ring + 0x210 <= *(unsigned long *)(self + 0x28)) &&
            *(unsigned long *)(self + 0x30) <= ring)) {
            desc[0] = 0x6ad3a8;
            desc[1] = DAT_004bbfd8;
            desc[2] = (unsigned long)vas_fh_complete_fault;   /* FUN_0002ac94 */
            desc[3] = 0x65af80;
            desc[4] = kind;
            desc[5] = param3;
            status = vas_fh_lookup_range(ring, key, (long)desc);   /* FUN_0002a784 */
            sk_mtx_unlock(**(unsigned long **)(self + 0x38));      /* FUN_00118194 */
            if ((status & 0xff) == 0) {
                if (slot != (unsigned long *)0) {
                    *(unsigned char *)((char *)slot + 4) = 0;
                    slot[4] = 0;
                    slot[5] = 0;
                }
                sk_rt_000462e0(&res_lo);
            } else {
                if (slot != (unsigned long *)0) {
                    if (5 < ((unsigned int)status & 0xff) - 1) {
                        /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                        sk_swift_fatal("unknown vas return code 0x%x");
                    }
                    *(char *)((char *)slot + 1) = (char)status;
                    *(short *)((char *)slot + 2) = (short)(status >> 0x10);
                    *(unsigned char *)((char *)slot + 4) = 0;
                }
                if (5 < ((unsigned int)status & 0xff) - 1) {
                    /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                    sk_swift_fatal("unknown vas return code 0x%x");
                }
                sk_rt_000462e8(&res_lo, status & 0xffff00ff);
            }
            (*(void (**)(long, unsigned long))(reply + 0x10))(reply,
                (unsigned long)(((unsigned long)res_hi << 32) | res_lo));
            return;
        }
    }
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2ac74);
}

/*--------------------------------------------------------------------*/
/* FUN_0002ac94 @ 0x0002ac94   (est. vas_fh_complete_fault)
 * Ghidra: undefined1 [16] FUN_0002ac94(long param_1, long param_2)
 * Completes a matched fault record: if the record is active (kind flag at
 * rec+0x20), validates the faulting address against the record and invokes
 * vas_fh_deactivate (FUN_0002ad54). Returns 0x3610001 if the record was not
 * active; 0x36b0000/0x36b0001 depending on whether the stored address
 * (param_1+0x28) matches the record address (param_2+0x28).
 * Confidence: medium
 * Notes: s_easm__d_completefault__FH__lld___005ad75a/78a.
 */
unsigned long vas_fh_complete_fault(long self, long rec)
{
    unsigned long status;
    long addr, rec_addr;

    if ((*(unsigned char *)(rec + 0x20) & 1) == 0) {
        sk_printf("easm %d completefault FH %lld %p");   /* s_easm__d_completefault__FH__lld___005ad75a */
        status = 0x3610001;
    } else {
        addr = *(long *)(self + 0x28);
        rec_addr = *(long *)(rec + 0x28);
        if (addr != rec_addr) {
            sk_printf("easm %d completefault FH %lld %p");   /* s_easm__d_completefault__FH__lld___005ad78a */
        }
        status = 0x36b0000;
        if (addr != rec_addr) {
            status = 0x36b0001;
        }
        vas_fh_deactivate(rec, addr == rec_addr & *(unsigned char *)(self + 0x30));
    }
    return status;
}

/*--------------------------------------------------------------------*/
/* FUN_0002ad54 @ 0x0002ad54   (est. vas_fh_deactivate)
 * Ghidra: void FUN_0002ad54(undefined8 *param_1, undefined8 param_2)
 * Deactivates a fault-handler record: if the record is active (flag byte at
 * rec+4 == 1), deprovisions the mapped pages via the handler's deprovision
 * method (rec[7]+0x30), unmounts through (rec[2]+8), clears the active flag
 * and mapping pointer. A deprovision failure trips sk_swift_fatal.
 * Confidence: medium
 * Notes: s_easm_completefault_failed_to_dep_005ae606; trap 0x5519 @0x2ae28.
 */
void vas_fh_deactivate(unsigned long *rec, unsigned long result)
{
    unsigned long status;
    unsigned long dep[2];

    if (*(char *)(rec + 4) == '\x01') {
        dep[0] = 0;
        dep[1] = 0x4000;
        status = (*(unsigned long (**)(unsigned long, unsigned long *, unsigned long *))
                  (rec[7] + 0x30))(rec[6], &dep[0], &dep[1]);
        status = status & 0xff;
        if (status != 0) {
            /* FUN_004afae4 s_easm_completefault_failed_to_dep_005ae606 */
            sk_swift_fatal("easm completefault failed to dep");
            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2ae28);
        }
        (*(void (**)(unsigned long, unsigned long, unsigned long, unsigned long))
          (rec[2] + 8))(*rec, rec[1], rec[5], result);
        *(unsigned char *)(rec + 4) = 0;
        rec[5] = 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0002ae28 @ 0x0002ae28   (est. vas_fh_destroy)
 * Ghidra: void FUN_0002ae28(long param_1, undefined8 param_2, long param_3)
 * Destroys a fault handler: claims a request slot (kind 0x10000000b), looks
 * up the handler via vas_fh_lookup_range with a callback descriptor pointing
 * at vas_fh_destroy_cb (FUN_0002b03c), and encodes/replies the result through
 * param_3+0x10.
 * Confidence: medium
 * Notes: shared request-slot preamble; trap 0x5519 @0x2b01c;
 *   s_unknown_vas_return_code_0x_x_005ae5cc.
 */
void vas_fh_destroy(long self, unsigned long key, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned long *freebase, *slot;
    unsigned long status;
    unsigned int res_lo;
    unsigned short res_hi;
    unsigned long desc[6];
    bool ok, under;

    ring = *(unsigned long *)(self + 0x20);
    end = ring + 0x210;
    ok = (end <= *(unsigned long *)(self + 0x28));
    under = (*(unsigned long *)(self + 0x30) <= ring);
    freebase = (unsigned long *)(ring + 0x1f0);
    if (((ok && ring <= end) && under) && freebase < (unsigned long *)(ring + 0x208) ||
        ((ok && ring <= end) && under) && freebase == (unsigned long *)(ring + 0x208)) {
        count = *freebase;
        if (count == 0) {
            slot = (unsigned long *)0;
        } else {
            next = *(long *)(ring + 0x1f8);
            *(long *)(ring + 0x1f8) = next + 1;
            idx = 0;
            if (count != 0) {
                idx = (next + 1) / count;
            }
            freebase = *(unsigned long **)(ring + 0x200);
            slot = freebase + ((next + 1) - idx * count) * 6;
            if ((slot < freebase || freebase + count * 6 < slot + 6) || slot + 6 < slot) {
                (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b01c);
            }
            *slot = 0x10000000b;
            slot[1] = key;
            slot[2] = 0;
            slot[3] = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        res_hi = 0;
        res_lo = 0;
        sk_mtx_lock(**(unsigned long **)(self + 0x38));       /* FUN_00118164 */
        ring = *(unsigned long *)(self + 0x20);
        if ((ring == 0) ||
           ((ring <= ring + 0x210 && ring + 0x210 <= *(unsigned long *)(self + 0x28)) &&
            *(unsigned long *)(self + 0x30) <= ring)) {
            desc[0] = 0x6ad3a8;
            desc[1] = DAT_004bbfd8;
            desc[2] = (unsigned long)vas_fh_destroy_cb;   /* FUN_0002b03c */
            desc[3] = 0x65afc0;
            desc[4] = *(unsigned long *)(self + 0x28);
            desc[5] = *(unsigned long *)(self + 0x20);
            status = vas_fh_lookup_range(ring, key, (long)desc);   /* FUN_0002a784 */
            sk_mtx_unlock(**(unsigned long **)(self + 0x38));      /* FUN_00118194 */
            if ((status & 0xff) == 0) {
                if (slot != (unsigned long *)0) {
                    *(unsigned char *)((char *)slot + 4) = 0;
                    slot[4] = 0;
                    slot[5] = 0;
                }
                sk_rt_000462e0(&res_lo);
            } else {
                if (slot != (unsigned long *)0) {
                    if (5 < ((unsigned int)status & 0xff) - 1) {
                        /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                        sk_swift_fatal("unknown vas return code 0x%x");
                    }
                    *(char *)((char *)slot + 1) = (char)status;
                    *(short *)((char *)slot + 2) = (short)(status >> 0x10);
                    *(unsigned char *)((char *)slot + 4) = 0;
                }
                if (5 < ((unsigned int)status & 0xff) - 1) {
                    /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                    sk_swift_fatal("unknown vas return code 0x%x");
                }
                sk_rt_000462e8(&res_lo, status & 0xffff00ff);
            }
            (*(void (**)(long, unsigned long))(reply + 0x10))(reply,
                (unsigned long)(((unsigned long)res_hi << 32) | res_lo));
            return;
        }
    }
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b01c);
}

/*--------------------------------------------------------------------*/
/* FUN_0002b03c @ 0x0002b03c   (est. vas_fh_destroy_cb)
 * Ghidra: undefined1 [16] FUN_0002b03c(long param_1, long param_2)
 * Destroy callback invoked for a matched fault record: deactivates the record
 * (vas_fh_deactivate, FUN_0002ad54) if it is active, then removes it from the
 * VAS fault-handler table via vas_fh_table_remove (FUN_0002b0cc). Returns 0.
 * Confidence: medium
 * Notes: s_easm__d_destroy__FH__lld__p_is_a_005ad831; trap 0x5519 @0x2b0cc.
 */
unsigned long vas_fh_destroy_cb(long self, long rec)
{
    unsigned long table;

    if ((*(unsigned char *)(rec + 0x20) & 1) != 0) {
        sk_printf("easm %d destroy FH %lld %p is a");   /* s_easm__d_destroy__FH__lld__p_is_a_005ad831 */
        vas_fh_deactivate(rec, 0);
    }
    table = *(unsigned long *)(self + 0x28);
    if ((table != 0) &&
       ((table + 0x210 < table || *(unsigned long *)(self + 0x30) < table + 0x210) ||
        table < *(unsigned long *)(self + 0x38))) {
        (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b0cc);
    }
    vas_fh_table_remove(table, rec);   /* FUN_0002b0cc */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0002b0cc @ 0x0002b0cc   (est. vas_fh_table_remove)
 * Ghidra: void FUN_0002b0cc(long param_1, undefined8 *param_2)
 * Removes a fault-handler record from the VAS region table. Computes the
 * record index from the pointer (stride 0x48), validates it is active, then
 * deactivates it, frees the handler resources ((*rec[7])(rec[6]) and
 * (rec[2]+0x10)(*rec,rec[1])), swaps in the last table entry, and clears the
 * vacated slot.
 * Confidence: medium
 * Notes: s_fh__p_is_not_an_active_faulthand_005ae64c; trap 0x5519 @0x2b1e8.
 */
void vas_fh_table_remove(long self, unsigned long *rec)
{
    unsigned long *base, *last;
    long idx, count, i;
    unsigned long v0, v1, v2, v3, v4, v5, v6, v7, v8;

    base = (unsigned long *)(self + 400);
    idx = ((long)rec - (long)base >> 3) * -0x71c71c71c71c71c7L / 1;   /* /9 stride, see below */
    idx = ((long)rec - (long)base) / 9;
    if (*(unsigned long *)(self + 0x188) <= (unsigned long)idx) {
        /* FUN_004afae4 s_fh__p_is_not_an_active_faulthand_005ae64c */
        sk_swift_fatal("fh %p is not an active faulthand");
    }
    vas_fh_deactivate(rec, 0);
    (*(void (**)(unsigned long))(rec[7]))(rec[6]);
    (*(void (**)(unsigned long, unsigned long))(rec[2] + 0x10))(*rec, rec[1]);
    count = *(long *)(self + 0x188) + -1;
    *(long *)(self + 0x188) = count;
    if (idx - count != 0) {
        last = base + count * 9;
        if ((last < base || (unsigned long *)(self + 0x1d8) < last + 9) || last + 9 < last) {
            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b1e8);
        }
        v0 = *last;
        rec[1] = last[1];
        *rec = v0;
        v1 = last[3];
        v0 = last[2];
        v2 = last[5];
        v3 = last[4];
        v4 = last[7];
        v5 = last[6];
        rec[8] = last[8];
        rec[5] = v2;
        rec[4] = v3;
        rec[7] = v4;
        rec[6] = v5;
        rec[3] = v1;
        rec[2] = v0;
        idx = *(unsigned long *)(self + 0x188);
    }
    last = base + idx * 9;
    if ((base <= last && last + 9 <= (unsigned long *)(self + 0x1d8)) && last <= last + 9) {
        last[8] = 0;
        last[5] = 0;
        last[4] = 0;
        last[7] = 0;
        last[6] = 0;
        last[1] = 0;
        *last = 0;
        last[3] = 0;
        last[2] = 0;
        return;
    }
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b1e8);
}

/*--------------------------------------------------------------------*/
/* FUN_0002b1f8 @ 0x0002b1f8   (est. vas_fh_activate_slot)
 * Ghidra: void FUN_0002b1f8(long param_1, undefined8 param_2, long param_3)
 * Activates a fault handler from a decoded record: claims a request slot
 * (kind 0x100000006) with the key stored in both slot[1] and slot[2], then
 * calls the handler-create method (*(self+0x48)+0x38) which returns a
 * (16-byte) descriptor. On failure the result is encoded (kind 4); on success
 * the record is registered via vas_record_add (FUN_0002b3ec) and filled via
 * vas_record_fill (FUN_0002b5e8), and the result is encoded and replied.
 * Confidence: low
 * Notes: shared request-slot preamble; trap 0x5519 @0x2b3ec.
 */
void vas_fh_activate_slot(long self, unsigned long key, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned long *freebase, *slot;
    unsigned long status;
    unsigned long desc[2];
    unsigned int id;
    unsigned long out[10];
    unsigned long r[5];
    bool ok, under;

    ring = *(unsigned long *)(self + 0x20);
    end = ring + 0x210;
    ok = (end <= *(unsigned long *)(self + 0x28));
    under = (*(unsigned long *)(self + 0x30) <= ring);
    freebase = (unsigned long *)(ring + 0x1f0);
    if (((ok && ring <= end) && under) && freebase < (unsigned long *)(ring + 0x208) ||
        ((ok && ring <= end) && under) && freebase == (unsigned long *)(ring + 0x208)) {
        count = *freebase;
        if (count == 0) {
            slot = (unsigned long *)0;
        } else {
            next = *(long *)(ring + 0x1f8);
            *(long *)(ring + 0x1f8) = next + 1;
            idx = 0;
            if (count != 0) {
                idx = (next + 1) / count;
            }
            freebase = *(unsigned long **)(ring + 0x200);
            slot = freebase + ((next + 1) - idx * count) * 6;
            if ((slot < freebase || freebase + count * 6 < slot + 6) || slot + 6 < slot) {
                (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b3ec);
            }
            *slot = 0x100000006;
            slot[1] = key;
            slot[2] = key;
            slot[3] = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        /* zero result record */
        for (i = 0; i < 10; i++) out[i] = 0;
        id = 0;
        sk_mtx_lock(**(unsigned long **)(self + 0x38));       /* FUN_00118164 */
        desc[0] = (*(unsigned long (**)(unsigned long, unsigned long, unsigned int *,
                                        unsigned long *))
                   (*(long *)(self + 0x48) + 0x38))
                  (*(unsigned long *)(self + 0x40), key, &id, &out[0]);
        sk_mtx_unlock(**(unsigned long **)(self + 0x38));     /* FUN_00118194 */
        if (desc[0] == 0) {
            if (slot != (unsigned long *)0) {
                *(unsigned char *)((char *)slot + 1) = 4;
                *(unsigned short *)((char *)slot + 2) = 0;
                *(unsigned char *)((char *)slot + 4) = 0;
            }
            sk_rt_00046304(&out[0], 4);
        } else {
            if (slot != (unsigned long *)0) {
                *(unsigned char *)((char *)slot + 4) = 0;
                slot[4] = 0;
                slot[5] = 0;
            }
            ring = *(unsigned long *)(self + 0x20);
            if ((ring != 0) &&
               (((ring + 0x210 < ring) || (*(unsigned long *)(self + 0x28) < ring + 0x210)) ||
                (ring < *(unsigned long *)(self + 0x30)))) {
                (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b3ec);
            }
            r[0] = vas_record_add(ring, desc[0], desc[1]);   /* FUN_0002b3ec */
            vas_record_fill(&r[1], (char *)&out[0], id);     /* FUN_0002b5e8 */
            sk_rt_00046340(&out[0], &r[0]);
        }
        (*(void (**)(long, unsigned long *))(reply + 0x10))(reply, out);
        return;
    }
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b3ec);
}

/*--------------------------------------------------------------------*/
/* FUN_0002b3ec @ 0x0002b3ec   (est. vas_record_add)
 * Ghidra: long FUN_0002b3ec(long param_1, long param_2, long param_3)
 * Registers a fault-handler record key in the VAS's handler table. Validates
 * the table id (self+0x178), checks the record kind flag via (param_3+8), and
 * appends param_2 to the dynamic key array at (self+0x170, cap at +0x160,
 * used at +0x168), growing it with sk_realloc when full. The appended entry is
 * filled from the descriptor via vas_record_fill-style copy (sk_rt_00045d38/
 * 00045ce8). Returns param_2 on success.
 * Confidence: low
 * Notes: s__VAS_abort_in_function__s_at_lin_005ae776/7de/888/6ec;
 *   s_Type_0x_x_is_not_frame_or_cnode_005ae8e4; sk_realloc FUN_000102f4;
 *   sk_rt_004b1ae8/1b24; sk_boot_panic FUN_00054354.
 */
long vas_record_add(long self, long key, long desc)
{
    char c0, c1, c2;
    unsigned long cap, used, ncap;
    unsigned long *arr, *fill;
    unsigned long status;

    if (key != 0) {
        if (*(long *)(self + 0x178) == 0) {
            *(long *)(self + 0x178) = desc;
        } else if (*(long *)(self + 0x178) != desc) goto abort;
        if (desc == 0) {
            sk_boot_panic();               /* FUN_00054354 */
        }
        status = (*(unsigned long (**)(unsigned long, unsigned long))(desc + 8))(key, 0);
        if (((status >> 0x13 & 1) == 0) && (cap = sk_rt_0002fa34(self, key), cap == 0)) {
            used = *(unsigned long *)(self + 0x160);
            if (used < *(unsigned long *)(self + 0x168)) {
                /* FUN_004afae4 s__VAS_abort_in_function__s_at_lin_005ae776 */
                sk_swift_fatal("VAS abort in function %s at lin");
            }
            if (used <= *(unsigned long *)(self + 0x168)) {
                ncap = used * 2;
                if (ncap < 0x11) {
                    ncap = 0x10;
                }
                if (ncap < used) {
                    /* FUN_004afae4 s__VAS_abort_in_function__s_at_lin_005ae7de */
                    sk_swift_fatal("VAS abort in function %s at lin");
                }
                arr = (unsigned long *)sk_realloc(*(unsigned long *)(self + 0x170),
                                                  ncap << 3, 0x100004000313f17);   /* FUN_000102f4 */
                if (arr == (unsigned long *)0) {
                    /* out-of-memory: build a record from the source descriptor */
                    fill = (unsigned long *)sk_rt_004b1ae8();
                    fill[0] = fill[0] & 0xfff9fffe;
                    /* type of source desc */
                    c0 = ((char *)fill)[1] == 0x11 ? 1 : 2;   /* frame vs cnode */
                    fill[0] = fill[0] & 0xfff9fffe;
                    sk_rt_00045d38(fill + 2, (fill[0] & 1) ? &fill[0] : 0);
                    sk_rt_00045d38(fill + 6, 0);
                    sk_rt_00045ce8((unsigned long *)((char *)fill + 0x2a), 0);
                    sk_rt_00045ce8((unsigned long *)((char *)fill + 0x2c), 0);
                    return sk_rt_00045ce8((unsigned long *)((char *)fill + 0x2e), 0);
                }
                used = *(unsigned long *)(self + 0x160);
                ncap = ncap - used;
                if (used <= ncap && ncap != 0) {
                    fill = arr + used;
                    do {
                        if (((fill < arr) || (arr + used + ncap < fill + 1)) || (fill + 1 < fill)) {
                            (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2b530);
                        }
                        *fill = 0;
                        ncap = ncap + -1;
                        fill = fill + 1;
                    } while (ncap != 0);
                }
                *(unsigned long **)(self + 0x170) = arr;
                *(unsigned long *)(self + 0x160) = used * 2;
            }
            if (*(unsigned long *)(self + 0x160) <= *(unsigned long *)(self + 0x168)) {
                /* FUN_004afae4 s__VAS_abort_in_function__s_at_lin_005ae888 */
                sk_swift_fatal("VAS abort in function %s at lin");
            }
            *(long *)(*(long *)(self + 0x170) + *(unsigned long *)(self + 0x168) * 8) = key;
            *(unsigned long *)(self + 0x168) = *(unsigned long *)(self + 0x168) + 1;
        }
        return key;
    }
    sk_rt_004b1b24();
abort:
    /* FUN_004afae4 s__VAS_abort_in_function__s_at_lin_005ae6ec */
    sk_swift_fatal("VAS abort in function %s at lin");
}

/*--------------------------------------------------------------------*/
/* FUN_0002b5e8 @ 0x0002b5e8   (est. vas_record_fill)
 * Ghidra: void FUN_0002b5e8(ulong *param_1, char *param_2, uint param_3)
 * Fills a fault-handler record at param_1 from a source descriptor at
 * param_2. Reads the source type tag (frame 0x11 / cnode 0x04 -> kind 1/2),
 * copies the capability words and mapped address, and encodes the string
 * fields via sk_rt_00045ce8. flags at param_3 select which string fields are
 * present.
 * Confidence: medium
 * Notes: s_Type_0x_x_is_not_frame_or_cnode_005ae8e4; sk_rt_00045d38/00045ce8.
 */
void vas_record_fill(unsigned long *out, char *src, unsigned int flags)
{
    unsigned long *p, *p2;
    char c0, c1, c2;
    unsigned char kind;
    unsigned long local_48;
    char b0, b1, b2;

    *out = (unsigned long)(flags & 0xfff9fffe);
    if (*src == '\x11') {
        kind = 1;
    } else {
        if (*src != '\x04') {
            /* FUN_004afae4 s_Type_0x_x_is_not_frame_or_cnode_005ae8e4 */
            sk_swift_fatal("Type 0x%x is not frame or cnode");
        }
        kind = 2;
    }
    *(unsigned long *)((char *)out + 0x2a) = 0;
    *(unsigned char *)(out + 1) = kind;
    *(unsigned long *)((char *)out + 0x11) = 0;
    *(unsigned long *)((char *)out + 9) = 0;
    out[3] = 0;
    local_48 = *(unsigned long *)(src + 8);
    out[4] = *(unsigned long *)(src + 0x10);
    *(char *)(out + 5) = src[0x18];
    *(bool *)((char *)out + 0x29) = src[0x19] != '\0';
    *(unsigned long *)((char *)out + 0x32) = 0;
    out[7] = 0;
    c0 = src[0x1a];
    c1 = src[0x1b];
    c2 = src[0x1c];
    p2 = &local_48;
    p = (unsigned long *)0;
    if ((flags & 1) != 0) {
        p = p2;
    }
    b0 = c2;
    b1 = c1;
    b2 = c0;
    sk_rt_00045d38(out + 2, p);
    p2 = (unsigned long *)0;
    if ((flags & 0x20001) == 0x20000) {
        p2 = &local_48;
    }
    sk_rt_00045d38(out + 6, p2);
    p = (unsigned long *)0;
    if (c0 != '\0') {
        p = (unsigned long *)&b2;
    }
    sk_rt_00045ce8((unsigned long *)((char *)out + 0x2a), p);
    p = (unsigned long *)0;
    if (c1 != '\0') {
        p = (unsigned long *)&b1;
    }
    sk_rt_00045ce8((unsigned long *)((char *)out + 0x2c), p);
    p = (unsigned long *)0;
    if (c2 != '\0') {
        p = (unsigned long *)&b0;
    }
    sk_rt_00045ce8((unsigned long *)((char *)out + 0x2e), p);
}

/*--------------------------------------------------------------------*/
/* FUN_0002b724 @ 0x0002b724   (est. vas_fh_register)
 * Ghidra: void FUN_0002b724(long param_1, uint *param_2, long param_3)
 * Registers a decoded fault-handler record: validates the source record
 * bounds, decodes its capability fields (sk_rt_00045d08/00045cd8), builds a
 * request slot (kind 0x100000005), then calls the fault-register method
 * (*(self+0x48)+0x30) unless the reserved bit 0x40000 is set (0x3b50001).
 * On success the record is added (vas_record_add) and filled (vas_record_fill)
 * and the result encoded and replied via param_3+0x10.
 * Confidence: low
 * Notes: shared request-slot preamble; trap 0x5519 @0x2ba78;
 *   s_unknown_vas_return_code_0x_x_005ae5cc.
 */
void vas_fh_register(long self, unsigned int *src, long reply)
{
    unsigned long ring, end, count, next, idx;
    unsigned long *freebase, *slot;
    unsigned long status;
    unsigned long *p7, *p8;
    unsigned char *p9, *p10, *p11;
    unsigned long cap_word, r0, r1;
    unsigned int flags, d4;
    unsigned char t0, t1, t2, t3;
    unsigned long out[10];
    unsigned long r[5];
    bool ok, under;
    int i;

    r0 = 0;
    r1 = 0;
    if (src + 8 < src + 4) goto trap;
    p7 = (unsigned long *)sk_rt_00045d08();
    if ((src + 0x10 < src) || (src + 0x10 < src + 0xc)) goto trap;
    for (i = 0; i < 10; i++) out[i] = 0;
    p8 = (unsigned long *)sk_rt_00045d08();
    p9 = (unsigned char *)sk_rt_00045cd8((long)src + 0x2a);
    p10 = (unsigned char *)sk_rt_00045cd8(src + 0xb);
    p11 = (unsigned char *)sk_rt_00045cd8((long)src + 0x2e);
    if ((p7 != (unsigned long *)0) || (cap_word = 0, p7 = p8, p8 != (unsigned long *)0)) {
        cap_word = *p7;
    }
    flags = *src;
    d4 = 0;
    if (p8 != (unsigned long *)0) {
        d4 = 0x20000;
    }
    if (p7 != (unsigned long *)0) {
        d4 = 1;
    }
    d4 = d4 | flags;
    if (p9 == (unsigned char *)0) {
        t0 = 0;
        if (p10 == (unsigned char *)0) {
            t1 = 0;
        } else {
            t1 = *p10;
        }
    } else {
        t0 = *p9;
        if (p10 != (unsigned char *)0) {
            t1 = *p10;
        } else {
            t1 = 0;
        }
    }
    r1 = *(unsigned long *)(src + 8);
    t2 = (unsigned char)src[10];
    t3 = *(unsigned char *)((long)src + 0x29);
    if (p11 == (unsigned char *)0) {
        t2 = 0;
    } else {
        t2 = *p11;
    }
    /* record tag: cnode 0x04 -> kind 4, else frame 0x11 */
    cap_word = 4;
    if ((char)src[2] != '\x02') {
        cap_word = 0x11;
    }
    ring = *(unsigned long *)(self + 0x20);
    if ((((ring + 0x210 <= *(unsigned long *)(self + 0x28)) && (ring <= ring + 0x210)) &&
        (*(unsigned long *)(self + 0x30) <= ring)) &&
       ((unsigned long *)(ring + 0x1f0) <= (unsigned long *)(ring + 0x208))) {
        count = *(unsigned long *)(ring + 0x1f0);
        if (count == 0) {
            slot = (unsigned long *)0;
        } else {
            next = *(long *)(ring + 0x1f8);
            *(long *)(ring + 0x1f8) = next + 1;
            idx = 0;
            if (count != 0) {
                idx = (next + 1) / count;
            }
            freebase = *(unsigned long **)(ring + 0x200);
            slot = freebase + ((next + 1) - idx * count) * 6;
            if ((slot < freebase || freebase + count * 6 < slot + 6) || slot + 6 < slot) {
                (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2ba78);
            }
            *slot = 0x100000005;
            slot[1] = cap_word;
            slot[2] = r1;
            slot[3] = (unsigned long)d4;
            slot[4] = 0;
            slot[5] = 0;
        }
        sk_mtx_lock(**(unsigned long **)(self + 0x38));       /* FUN_00118164 */
        if ((flags >> 0x13 & 1) == 0) {
            status = (*(unsigned long (**)(unsigned long, unsigned long, unsigned long *,
                                           unsigned long *, unsigned int *, unsigned long *))
                      (*(long *)(self + 0x48) + 0x30))
                     (*(unsigned long *)(self + 0x40), d4, &cap_word, &r0, &d4, &cap_word);
        } else {
            status = 0x3b50001;
        }
        sk_mtx_unlock(**(unsigned long **)(self + 0x38));     /* FUN_00118194 */
        if ((status & 0xff) == 0) {
            if (slot != (unsigned long *)0) {
                slot[4] = r0;
                slot[5] = cap_word;
                *(unsigned char *)((char *)slot + 4) = 0;
            }
            ring = *(unsigned long *)(self + 0x20);
            if ((ring != 0) &&
               (((ring + 0x210 < ring) || (*(unsigned long *)(self + 0x28) < ring + 0x210)) ||
                (ring < *(unsigned long *)(self + 0x30)))) {
                (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2ba78);
            }
            r[0] = vas_record_add(ring, r0, r1);   /* FUN_0002b3ec */
            vas_record_fill(&r[1], (char *)&cap_word, d4);   /* FUN_0002b5e8 */
            sk_rt_00046340(&out[0], &r[0]);
        } else {
            if (slot != (unsigned long *)0) {
                if (5 < ((unsigned int)status & 0xff) - 1) {
                    /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                    sk_swift_fatal("unknown vas return code 0x%x");
                }
                *(char *)((char *)slot + 1) = (char)status;
                *(short *)((char *)slot + 2) = (short)(status >> 0x10);
                *(unsigned char *)((char *)slot + 4) = 0;
            }
            if (5 < ((unsigned int)status & 0xff) - 1) {
                /* FUN_004afae4 s_unknown_vas_return_code_0x_x_005ae5cc */
                sk_swift_fatal("unknown vas return code 0x%x");
            }
            sk_rt_00046304(&out[0], status & 0xffff00ff);
        }
        (*(void (**)(long, unsigned long *))(reply + 0x10))(reply, out);
        return;
    }
trap:
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2ba78);
}
/* vas_fh_handle_state @ 0x2ba98   (est. vas_fault_handler_lookup_dispatch)
 * Ghidra: undefined8 vas_fh_handle_state(long param_1, undefined8 param_2, long param_3)
 * Claims a request slot (kind 0x10000001b) for a VAS object lookup, locks the
 * server object, resolves the named object via the shared dispatch helper, then
 * encodes the outcome (success value or error code) into the reply. Takes
 * obj (the VAS server), reg_obj (the object name to look up) and reply
 * (whose +0x10 slot is the result-delivery method).
 * Confidence: high
 * Notes: two stacked record descriptors (record_a/record_b); helper vas_fh_lookup_entry
 *   is called with the descriptor base at &local_128 (the leading &local_118 arg
 *   is a Ghidra calling-convention artifact). */
unsigned long vas_fh_handle_state(unsigned long obj, unsigned long reg_obj, unsigned long reply)
{
    unsigned long cur, end, q, seq;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret;
    unsigned long record_a, record_b;
    unsigned long *ptr_a, *ptr_b;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long d = 0;
            if (seq != 0) { d = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - d * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x10000001b;
            slot[1] = reg_obj;
            slot[3] = 0;
            slot[2] = 0;
            slot[5] = 0;
            slot[4] = 0;
        }
        /* local_60..uStack_90 / local_a0 run of zeroed out-args */
        (void)0;
        record_b = 0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        record_a = 0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        ptr_a = &record_a;
        ptr_b = &record_b;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            /* descriptor: local_128 base, method +0x10 = vas_fh_map_page */
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bb180;
            unsigned long desc_2 = 0x2bdb8;    /* vas_fh_map_page */
            unsigned long desc_3 = 0x65b040;   /* DAT_0065b040 */
            unsigned long desc_4 = (unsigned long)ptr_a;
            unsigned long desc_5 = (unsigned long)ptr_b;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
            if ((ret & 0xff) == 0) {
                if (slot != (unsigned long *)0x0) {
                    unsigned int lo = *(unsigned int *)(ptr_b + 3);
                    slot[4] = ptr_b[4];
                    slot[5] = (unsigned long)lo;
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (ptr_b + 7 < ptr_b + 3) goto bounds_fail;
                vas_record_fill(&result, ptr_b + 3, *(unsigned int *)(ptr_a + 3)); /* FUN_0002b5e8 */
                sk_rt_00046320(&result, &result);   /* FUN_00046320 */
            } else {
                if (slot != (unsigned long *)0x0) {
                    *(unsigned char *)((unsigned long)slot + 1) = 4;
                    *(unsigned short *)((unsigned long)slot + 2) = 0;
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < (ret & 0xff) - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_00046304(&result, ret & 0xffff00ff);   /* FUN_00046304 */
            }
            result = (*(unsigned long (*)(unsigned long, unsigned long *)) * (unsigned long **)(reply + 0x10))(reply, &result);
            sk_rt_0004b8d0(&record_a, 8);   /* FUN_0004b8d0 */
            sk_rt_0004b8d0(&record_b, 8);   /* FUN_0004b8d0 */
            return result;
        }
    }
bounds_fail:
    /* WARNING: does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2bd24);
}

/*----*/
/* vas_fh_lookup_entry @ 0x2bd34   (est. vas_dispatch_resolve)
 * Ghidra: undefined1 [16] vas_fh_lookup_entry(long param_1, long param_2, long param_3)
 * Shared VAS dispatch core. If the current domain (FUN_0002fa34) is non-null,
 * resolve the object through the page check (FUN_0003c4c0) and, on success,
 * invoke the method at desc+0x10 with (desc, reg_obj, *(vas+0x178)); otherwise
 * return the error code 6. Returns a 16-byte value whose low byte holds the
 * status (0 = success).
 * Confidence: high
 * Notes: return read by callers only as low byte; modeled here as low word. */
unsigned long vas_fh_lookup_entry(unsigned long vas, unsigned long reg_obj, unsigned long *desc)
{
    unsigned long cur;
    unsigned long cookie;
    int ok;

    if ((reg_obj != 0) && (cur = sk_rt_0002fa34(), cur != 0)) {   /* FUN_0002fa34 */
        cookie = *(unsigned long *)(vas + 0x178);
        ok = sk_page_check(*(unsigned long *)(vas + 8), *(unsigned long *)(vas + 0x10),
                           reg_obj, cookie);                       /* FUN_0003c4c0 */
        if (ok != 0) {
            /* indirect dispatch through the descriptor method at +0x10 */
            return (*(unsigned long (*)(unsigned long *, unsigned long, unsigned long))*(unsigned long **)((unsigned char *)desc + 0x10))(desc, reg_obj, cookie);
        }
    }
    return 6;
}

/*----*/
/* vas_fh_map_page @ 0x2bdb8   (est. vas_fault_handler_lookup_fill)
 * Ghidra: undefined1 [16] vas_fh_map_page(long param_1, undefined8 param_2, long param_3)
 * Inner lookup implementation driven by the dispatcher: validates the request
 * region bounds, calls the (param_3+8) method with (param_2, slot) to obtain a
 * status and stores it into the object's +0x18 field; returns 0 on success.
 * Aborts (boot panic) if param_3 is null.
 * Confidence: high
 * Notes: uses SoftwareBreakpoint(0x5519,0x2be20) on the bounds check. */
unsigned long vas_fh_map_page(unsigned long obj, unsigned long reg_obj, unsigned long cb)
{
    unsigned long base = *(unsigned long *)(*(unsigned long *)(obj + 0x28) + 8);
    unsigned long end = base + 0x18;
    unsigned int status;

    if (base + 0x38U < end) {
        /* does not return */
        (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2be20);
    }
    if (cb != 0) {
        status = (*(unsigned int (*)(unsigned long, unsigned long))*(unsigned long **)(cb + 8))(reg_obj, end);
        *(unsigned int *)(*(unsigned long *)(*(unsigned long *)(obj + 0x20) + 8) + 0x18) = status;
        return 0;
    }
    /* does not return */
    sk_boot_panic();
}

/*----*/
/* sk_pair_copy8 @ 0x2be24   (est. vas_fault_handler_copy_regs)
 * Ghidra: void sk_pair_copy8(long param_1, long param_2)
 * Copies the two 8-byte request-region base words from src (+0x20/+0x28) into
 * dst (+0x20/+0x28). Used to carry the fault-handler request context across a
 * save/restore boundary.
 * Confidence: high */
void sk_pair_copy8(unsigned long dst, unsigned long src)
{
    sk_rt_0004b710(dst + 0x20, *(unsigned long *)(src + 0x20), 8);  /* FUN_0004b710 */
    sk_rt_0004b710(dst + 0x28, *(unsigned long *)(src + 0x28), 8);  /* FUN_0004b710 */
}

/*----*/
/* sk_pair_release @ 0x2be68   (est. vas_fault_handler_teardown_regs)
 * Ghidra: void sk_pair_release(long param_1)
 * Releases the two request-region base words of a fault-handler record at
 * (+0x28, then +0x20) via FUN_0004b8d0.
 * Confidence: high */
void sk_pair_release(unsigned long obj)
{
    sk_rt_0004b8d0(*(unsigned long *)(obj + 0x28), 8);  /* FUN_0004b8d0 */
    sk_rt_0004b8d0(*(unsigned long *)(obj + 0x20), 8);  /* FUN_0004b8d0 */
}

/*----*/
/* vas_fh_delete @ 0x2bea0   (est. vas_fault_handler_map)
 * Ghidra: void vas_fh_delete(long param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Claims a request slot (kind 0x10000001c), locks the server, dispatches the
 * (reg_obj, arg) map request, and delivers the status into the reply. Success
 * clears the slot payload; failure encodes the error code.
 * Confidence: high
 * Notes: helper method pointer &LAB_0002c0a4 at desc+0x10; DAT_0065b090 data. */
void vas_fh_delete(unsigned long obj, unsigned long reg_obj, unsigned long arg, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret;
    unsigned int c;
    unsigned int lo;
    unsigned short hi;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x10000001c;
            slot[1] = reg_obj;
            slot[2] = arg;
            slot[3] = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        hi = 0;
        lo = 0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bbfd8;
            unsigned long desc_2 = 0x2c0a4;    /* &LAB_0002c0a4 method */
            unsigned long desc_3 = 0x65b090;   /* DAT_0065b090 */
            unsigned long desc_4 = (unsigned long)arg;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
            if ((ret & 0xff) == 0) {
                if (slot != (unsigned long *)0x0) {
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                    slot[4] = 0;
                    slot[5] = 0;
                }
                sk_rt_000462e0(&lo);   /* FUN_000462e0 */
            } else {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_000462e8(&lo, ret & 0xffff00ff);   /* FUN_000462e8 */
            }
            (*(void (*)(unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, ((unsigned long)hi << 32) | lo);
            return;
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2c084);
}

/*----*/
/* vas_fh_size @ 0x2c0c0   (est. vas_fault_handler_map_region)
 * Ghidra: undefined8 vas_fh_size(long param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Claims a request slot (kind 0x10000001d) for mapping a region, dispatches the
 * (reg_obj, arg) request, and returns the resulting address (or error code)
 * through the reply. Success writes the resolved handle into the slot.
 * Confidence: high
 * Notes: method &LAB_0002c2f8, DAT_0065b0d0; local_70 record released at end. */
unsigned long vas_fh_size(unsigned long obj, unsigned long reg_obj, unsigned long arg, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret;
    unsigned int c;
    unsigned long record;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x10000001d;
            slot[1] = reg_obj;
            slot[2] = arg;
            slot[3] = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        result = 0;
        (void)0;
        record = 0;
        (void)0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bb180;
            unsigned long desc_2 = 0x2c2f8;    /* &LAB_0002c2f8 method */
            unsigned long desc_3 = 0x65b0d0;   /* DAT_0065b0d0 */
            unsigned long desc_4 = (unsigned long)&record;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
            if ((ret & 0xff) == 0) {
                if (slot != (unsigned long *)0x0) {
                    slot[4] = (&record)[3];
                    slot[5] = 0;
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                sk_rt_00046314(&result, (&record)[3]);   /* FUN_00046314 */
            } else {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_00046304(&result, ret & 0xffff00ff);   /* FUN_00046304 */
            }
            result = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, result, 0);
            sk_rt_0004b8d0(&record, 8);   /* FUN_0004b8d0 */
            return result;
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2c2d8);
}

/*----*/
/* vas_fh_get_range @ 0x2c328   (est. vas_fault_handler_move)
 * Ghidra: undefined8 vas_fh_get_range(long param_1, undefined8 param_2, undefined8 *param_3, long param_4)
 * Claims a request slot (kind 0x10000001e) for a two-value (from,to) move,
 * dispatches, and reports the resulting addresses through the reply. Reads the
 * two word values from *param_3, passes them into the record descriptors, and
 * stores both results back into the slot.
 * Confidence: high
 * Notes: method &LAB_0002c5b4, DAT_0065b120. */
unsigned long vas_fh_get_range(unsigned long obj, unsigned long reg_obj, unsigned long *arg2, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret;
    unsigned int c;
    unsigned long v0, v1, v2, r0, r1;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        v0 = *arg2;
        v1 = arg2[1];
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x10000001e;
            slot[1] = reg_obj;
            slot[2] = v0;
            slot[3] = v1;
            slot[4] = 0;
            slot[5] = 0;
            v0 = *arg2;
            v1 = arg2[1];
        }
        result = 0;
        (void)0;
        (void)0;
        r0 = 0;
        (void)0;
        r1 = 0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bb180;
            unsigned long desc_2 = 0x2c5b4;    /* &LAB_0002c5b4 method */
            unsigned long desc_3 = 0x65b120;   /* DAT_0065b120 */
            unsigned long desc_4 = (unsigned long)&r0;
            unsigned long desc_5 = (unsigned long)&r1;
            unsigned long desc_6 = (unsigned long)arg2;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5; (void)desc_6;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
            if ((ret & 0xff) == 0) {
                v2 = (&r1)[3];
                slot[4] = (&r0)[3];
                slot[5] = v2;
                *(unsigned char *)((unsigned long)slot + 4) = 0;
                sk_rt_000462f8(&result, (&r0)[3], (&r1)[3]);   /* FUN_000462f8 */
            } else {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_00046304(&result, ret & 0xffff00ff);   /* FUN_00046304 */
            }
            result = (*(unsigned long (*)(unsigned long, unsigned long *))*(unsigned long **)(reply + 0x10))(reply, &result);
            sk_rt_0004b8d0(&r1, 8);   /* FUN_0004b8d0 */
            sk_rt_0004b8d0(&r0, 8);   /* FUN_0004b8d0 */
            return result;
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2c594);
}

/*----*/
/* vas_fh_get_range2 @ 0x2c62c   (est. vas_fault_handler_move2)
 * Ghidra: undefined8 vas_fh_get_range2(long param_1, undefined8 param_2, undefined8 *param_3, long param_4)
 * Claims a request slot (kind 0x100000020) for a second two-value move variant
 * and reports the resolved addresses through the reply. Structurally identical
 * to 2c328 except for the slot kind, method (&LAB_0002c8b8) and data tag.
 * Confidence: high */
unsigned long vas_fh_get_range2(unsigned long obj, unsigned long reg_obj, unsigned long *arg2, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret;
    unsigned int c;
    unsigned long v0, v1, v2, r0, r1;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        v0 = *arg2;
        v1 = arg2[1];
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x100000020;
            slot[1] = reg_obj;
            slot[2] = v0;
            slot[3] = v1;
            slot[4] = 0;
            slot[5] = 0;
            v0 = *arg2;
            v1 = arg2[1];
        }
        result = 0;
        (void)0;
        (void)0;
        r0 = 0;
        (void)0;
        r1 = 0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        (void)0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bb180;
            unsigned long desc_2 = 0x2c8b8;    /* &LAB_0002c8b8 method */
            unsigned long desc_3 = 0x65b170;   /* DAT_0065b170 */
            unsigned long desc_4 = (unsigned long)&r0;
            unsigned long desc_5 = (unsigned long)&r1;
            unsigned long desc_6 = (unsigned long)arg2;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5; (void)desc_6;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
            if ((ret & 0xff) == 0) {
                v2 = (&r1)[3];
                slot[4] = (&r0)[3];
                slot[5] = v2;
                *(unsigned char *)((unsigned long)slot + 4) = 0;
                sk_rt_000462f8(&result, (&r0)[3], (&r1)[3]);   /* FUN_000462f8 */
            } else {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_00046304(&result, ret & 0xffff00ff);   /* FUN_00046304 */
            }
            result = (*(unsigned long (*)(unsigned long, unsigned long *))*(unsigned long **)(reply + 0x10))(reply, &result);
            sk_rt_0004b8d0(&r1, 8);   /* FUN_0004b8d0 */
            sk_rt_0004b8d0(&r0, 8);   /* FUN_0004b8d0 */
            return result;
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2c898);
}

/*----*/
/* vas_fh_unregister @ 0x2c930   (est. vas_fault_handler_unregister)
 * Ghidra: void vas_fh_unregister(long param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, long param_5)
 * Claims a request slot (kind 0x10000001f) to unregister a fault-handler entry,
 * dispatches the (reg_obj, arg) request, destroys the arg element, and delivers
 * the status into the reply.
 * Confidence: high
 * Notes: method &LAB_0002cb40, DAT_0065b1c0; cl4_destroy_elem on param_4. */
void vas_fh_unregister(unsigned long obj, unsigned long reg_obj, unsigned long arg, unsigned long elem, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret;
    unsigned int c;
    unsigned int lo;
    unsigned short hi;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x10000001f;
            slot[1] = reg_obj;
            slot[2] = arg;
            slot[3] = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        hi = 0;
        lo = 0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bbfd8;
            unsigned long desc_2 = 0x2cb40;    /* &LAB_0002cb40 method */
            unsigned long desc_3 = 0x65b1c0;   /* &DAT_0065b1c0 */
            unsigned long desc_4 = (unsigned long)arg;
            unsigned long desc_5 = (unsigned long)elem;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
            if ((ret & 0xff) == 0) {
                if (slot != (unsigned long *)0x0) {
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                    slot[4] = 0;
                    slot[5] = 0;
                }
                sk_rt_000462e0(&lo);   /* FUN_000462e0 */
            } else {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_000462e8(&lo, ret & 0xffff00ff);   /* FUN_000462e8 */
            }
            cl4_destroy_elem(elem);   /* FUN_004b23d8 */
            (*(void (*)(unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, ((unsigned long)hi << 32) | lo);
            return;
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2cb20);
}

/*----*/
/* vas_fh_move @ 0x2cb5c   (est. vas_fault_handler_move_swap)
 * Ghidra: undefined8 vas_fh_move(long param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Claims a request slot (kind 0x100000021) to move/swap a fault-handler entry:
 * on success it removes both reg_obj and arg from the live-registration list,
 * re-resolves the moved slot via FUN_0002b3ec and reports the resulting handle.
 * Confidence: high
 * Notes: method &DAT_0002ce4c / &LAB_0065b230; two vas_fh_region_remove unregisters. */
unsigned long vas_fh_move(unsigned long obj, unsigned long reg_obj, unsigned long arg, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret, val;
    unsigned int c;
    unsigned long rec;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x100000021;
            slot[1] = reg_obj;
            slot[2] = arg;
            slot[3] = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        result = 0;
        (void)0;
        rec = 0;
        (void)0;
        (void)0;
        (void)0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bb180;
            unsigned long desc_2 = 0x2ce4c;    /* &DAT_0002ce4c method */
            unsigned long desc_3 = 0x65b230;   /* &LAB_0065b230 */
            unsigned long desc_4 = *(unsigned long *)(obj + 0x28);
            unsigned long desc_5 = cur;
            unsigned long desc_6 = *(unsigned long *)(obj + 0x30);
            unsigned long desc_7 = (unsigned long)&rec;
            unsigned long desc_8 = (unsigned long)arg;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5; (void)desc_6; (void)desc_7; (void)desc_8;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            if ((ret & 0xff) != 0) {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_00046304(&result, ret & 0xffff00ff);   /* FUN_00046304 */
                goto done;
            }
            cur = *(unsigned long *)(obj + 0x20);
            if ((cur == 0) ||
               ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
                *(unsigned long *)(obj + 0x30) <= cur)) {
                vas_fh_region_remove(cur, reg_obj);   /* vas_fh_region_remove */
                cur = *(unsigned long *)(obj + 0x20);
                if ((cur == 0) ||
                   ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
                    *(unsigned long *)(obj + 0x30) <= cur)) {
                    vas_fh_region_remove(cur, arg);   /* vas_fh_region_remove */
                    cur = *(unsigned long *)(obj + 0x20);
                    if ((cur == 0) ||
                       ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
                        *(unsigned long *)(obj + 0x30) <= cur)) {
                        val = vas_record_add(cur, (&rec)[3], (&rec)[4]);   /* FUN_0002b3ec */
                        if (slot != (unsigned long *)0x0) {
                            slot[4] = val;
                            slot[5] = 0;
                            *(unsigned char *)((unsigned long)slot + 4) = 0;
                        }
                        sk_rt_00046314(&result);   /* FUN_00046314 */
                        goto done;
                    }
                }
            }
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2ce2c);
done:
    sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
    result = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, result, 0);
    sk_rt_0004b8d0(&rec, 8);   /* FUN_0004b8d0 */
    return result;
}

/*----*/
/* vas_fh_lookup_dispatch @ 0x2ce70   (est. vas_fault_handler_state_get)
 * Ghidra: void vas_fh_lookup_dispatch(long param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Thin state-get wrapper: builds a descriptor (method &LAB_0002cef0, data
 * &LAB_0065b200) around *(obj+0x20) and dispatches it with param_2 and
 * *(obj+0x40) as the request key. Result is delivered synchronously inside
 * the dispatch; this function returns void.
 * Confidence: high
 * Notes: no request-slot allocation, no lock in this wrapper. */
void vas_fh_lookup_dispatch(unsigned long obj, unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long desc_0 = 0x6ad3a8;
    unsigned long desc_1 = DAT_004bb180;
    unsigned long desc_2 = 0x2cef0;    /* &LAB_0002cef0 method */
    unsigned long desc_3 = 0x65b200;   /* &LAB_0065b200 */
    unsigned long desc_4 = *(unsigned long *)(obj + 0x20);
    unsigned long desc_5 = (unsigned long)b;
    unsigned long desc_6 = (unsigned long)c;
    (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5; (void)desc_6;
    vas_fh_lookup_entry(a, *(unsigned long *)(obj + 0x40), &desc_0);   /* vas_fh_lookup_entry */
}

/*----*/
/* vas_fh_region_remove @ 0x2cf20   (est. vas_registration_unregister)
 * Ghidra: void vas_fh_region_remove(long param_1, long param_2)
 * Removes an entry named param_2 from the current domain's registration list at
 * obj+0x168 (count), obj+0x170 (array). Validates the entry exists, decrements
 * the count and pulls the last element into the vacated slot. Aborts via
 * sk_swift_fatal on any invariant violation.
 * Confidence: high
 * Notes: strings s__VAS_abort_in_function__s_at_lin_005ae904 / _005ae9e0 / _005ae776. */
void vas_fh_region_remove(unsigned long obj, unsigned long key)
{
    unsigned long *list;
    unsigned long *tail;
    unsigned long *src;
    unsigned long count;
    unsigned long cap;

    list = (unsigned long *)sk_rt_0002fa34();   /* FUN_0002fa34 */
    if (list == (unsigned long *)0x0) {
        sk_swift_fatal("VAS abort in function %s at line %d", __func__, 0); /* FUN_004afae4 s__VAS_abort_in_function__s_at_lin_005ae904 */
    }
    count = *(unsigned long *)(obj + 0x168);
    if (count == 0) {
        sk_rt_004b1b60();   /* FUN_004b1b60 */
    } else if (count <= *(unsigned long *)(obj + 0x160)) {
        if (list <= list + 1) {
            if (*list != key) {
                sk_swift_fatal("VAS abort in function %s at line %d", __func__, 0); /* FUN_004afae4 s__VAS_abort_in_function__s_at_lin_005ae9e0 */
            }
            *(unsigned long *)(obj + 0x168) = count - 1;
            tail = *(unsigned long **)(obj + 0x170);
            src = tail + (count - 1);
            if ((tail <= src && src + 1 <= tail + *(unsigned long *)(obj + 0x160)) &&
                src <= src + 1) {
                *list = *src;
                return;
            }
        }
        /* does not return */
        (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2cfb4);
    }
    /* does not return */
    sk_swift_fatal("VAS abort in function %s at line %d", __func__, 0); /* FUN_004afae4 s__VAS_abort_in_function__s_at_lin_005ae776 */
}

/*----*/
/* vas_fh_swap @ 0x2d040   (est. vas_fault_handler_swap)
 * Ghidra: undefined8 vas_fh_swap(long param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Claims a request slot (kind 0x100000022) to swap a fault-handler entry: on
 * success it unregisters reg_obj, resolves two handles (FUN_0002b3ec) and
 * reports both results through the reply.
 * Confidence: high
 * Notes: method &LAB_0002d360, &LAB_0065b280. */
unsigned long vas_fh_swap(unsigned long obj, unsigned long reg_obj, unsigned long arg, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret, v1, v2;
    unsigned int c;
    unsigned long r0, r1;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x100000022;
            slot[1] = reg_obj;
            slot[2] = arg;
            slot[3] = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        result = 0;
        (void)0;
        (void)0;
        r0 = 0;
        (void)0;
        (void)0;
        (void)0;
        r1 = 0;
        (void)0;
        (void)0;
        (void)0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bb180;
            unsigned long desc_2 = 0x2d360;    /* &LAB_0002d360 method */
            unsigned long desc_3 = 0x65b280;   /* &LAB_0065b280 */
            unsigned long desc_4 = (unsigned long)&r0;
            unsigned long desc_5 = (unsigned long)&r1;
            unsigned long desc_6 = (unsigned long)arg;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5; (void)desc_6;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            if ((ret & 0xff) != 0) {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_00046304(&result, ret & 0xffff00ff);   /* FUN_00046304 */
                goto done;
            }
            cur = *(unsigned long *)(obj + 0x20);
            if ((cur == 0) ||
               ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
                *(unsigned long *)(obj + 0x30) <= cur)) {
                vas_fh_region_remove(cur, reg_obj);   /* vas_fh_region_remove */
                cur = *(unsigned long *)(obj + 0x20);
                if ((cur == 0) ||
                   ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
                    *(unsigned long *)(obj + 0x30) <= cur)) {
                    v1 = vas_record_add(cur, (&r0)[3], (&r0)[4]);   /* FUN_0002b3ec */
                    cur = *(unsigned long *)(obj + 0x20);
                    if ((cur == 0) ||
                       ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
                        *(unsigned long *)(obj + 0x30) <= cur)) {
                        v2 = vas_record_add(cur, (&r1)[3], (&r1)[4]);   /* FUN_0002b3ec */
                        sk_rt_000462f8(&result, v1, v2);   /* FUN_000462f8 */
                        if (slot != (unsigned long *)0x0) {
                            slot[4] = v1;
                            slot[5] = v2;
                            *(unsigned char *)((unsigned long)slot + 4) = 0;
                        }
                        goto done;
                    }
                }
            }
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2d340);
done:
    sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
    result = (*(unsigned long (*)(unsigned long, unsigned long *))*(unsigned long **)(reply + 0x10))(reply, &result);
    sk_rt_0004b8d0(&r1, 8);   /* FUN_0004b8d0 */
    sk_rt_0004b8d0(&r0, 8);   /* FUN_0004b8d0 */
    return result;
}

/*----*/
/* vas_fh_resize @ 0x2d3b0   (est. vas_fault_handler_resize)
 * Ghidra: undefined8 vas_fh_resize(long param_1, undefined8 param_2, undefined8 param_3, ulong param_4, long param_5)
 * Claims a request slot (kind 0x100000023) to resize a fault-handler entry to a
 * new size (param_4). On success it unregisters reg_obj, resolves the relocated
 * handle and reports it. The reply is invoked once to test delivery and, if it
 * returns 0, invoked again to obtain the final result.
 * Confidence: high
 * Notes: method &LAB_0002d6a0, &LAB_0065b2d0. */
unsigned long vas_fh_resize(unsigned long obj, unsigned long reg_obj, unsigned long arg, unsigned long newsize, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret, v;
    unsigned int c;
    int r1;
    unsigned long rec;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x100000023;
            slot[1] = reg_obj;
            slot[2] = arg;
            slot[3] = newsize & 0xffffffff;
            slot[4] = 0;
            slot[5] = 0;
        }
        result = 0;
        (void)0;
        rec = 0;
        (void)0;
        (void)0;
        (void)0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bb180;
            unsigned long desc_2 = 0x2d6a0;    /* &LAB_0002d6a0 method */
            unsigned long desc_3 = 0x65b2d0;   /* &LAB_0065b2d0 */
            unsigned long desc_4 = (unsigned char)newsize;
            unsigned long desc_5 = (unsigned long)&rec;
            unsigned long desc_6 = (unsigned long)arg;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5; (void)desc_6;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            if ((ret & 0xff) != 0) {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_00046304(&result, ret & 0xffff00ff);   /* FUN_00046304 */
                goto done;
            }
            cur = *(unsigned long *)(obj + 0x20);
            if ((cur == 0) ||
               ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
                *(unsigned long *)(obj + 0x30) <= cur)) {
                vas_fh_region_remove(cur, reg_obj);   /* vas_fh_region_remove */
                cur = *(unsigned long *)(obj + 0x20);
                if ((cur == 0) ||
                   ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
                    *(unsigned long *)(obj + 0x30) <= cur)) {
                    v = vas_record_add(cur, (&rec)[3], (&rec)[4]);   /* FUN_0002b3ec */
                    if (slot != (unsigned long *)0x0) {
                        slot[4] = v;
                        slot[5] = 0;
                        *(unsigned char *)((unsigned long)slot + 4) = 0;
                    }
                    sk_rt_00046314(&result);   /* FUN_00046314 */
                    goto done;
                }
            }
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2d658);
done:
    sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
    r1 = (*(int (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, result, 0);
    if (r1 == 0) {
        result = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, result, 0);
        sk_rt_0004b8d0(&rec, 8);   /* FUN_0004b8d0 */
        return result;
    }
    /* does not return */
    sk_swift_fatal("VAS abort in function %s at line %d", __func__, 0); /* FUN_004afae4 s__VAS_abort_in_function__s_at_lin_005adea5 */
}

/*----*/
/* vas_fh_state_set @ 0x2d6dc   (est. vas_fault_handler_state_set)
 * Ghidra: void vas_fh_state_set(long param_1, undefined8 param_2, uint param_3, undefined8 param_4, undefined8 param_5, long param_6)
 * Claims a request slot (kind 0x100000024) to set a fault-handler state (param_3,
 * must be <= 4) with two context args (param_4, param_5) and delivers the status.
 * Success stores param_5 into the slot payload.
 * Confidence: high
 * Notes: method &LAB_0002d91c, &DAT_0065b320; string s__unknown_easm_fault_state_0x_x_005aea31. */
void vas_fh_state_set(unsigned long obj, unsigned long reg_obj, unsigned int state, unsigned long a1, unsigned long a2, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret;
    unsigned int c;
    unsigned int lo;
    unsigned short hi;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x100000024;
            slot[1] = reg_obj;
            slot[2] = (unsigned long)state;
            slot[3] = a1;
            slot[4] = 0;
            slot[5] = 0;
        }
        hi = 0;
        lo = 0;
        if (4 < state) {
            sk_swift_fatal("unknown easm fault state 0x%x\n", state); /* FUN_004afae4 s__unknown_easm_fault_state_0x_x_005aea31 */
        }
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            unsigned long desc_0 = 0x6ad3a8;
            unsigned long desc_1 = DAT_004bbfd8;
            unsigned long desc_2 = 0x2d91c;    /* &LAB_0002d91c method */
            unsigned long desc_3 = 0x65b320;   /* &DAT_0065b320 */
            unsigned long desc_4 = (unsigned char)state;
            unsigned long desc_5 = (unsigned long)a1;
            unsigned long desc_6 = (unsigned long)a2;
            (void)desc_0; (void)desc_1; (void)desc_2; (void)desc_3; (void)desc_4; (void)desc_5; (void)desc_6;
            ret = vas_fh_lookup_entry(cur, reg_obj, &desc_0);   /* vas_fh_lookup_entry */
            sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
            if ((ret & 0xff) == 0) {
                if (slot != (unsigned long *)0x0) {
                    slot[4] = a2;
                    slot[5] = 0;
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                sk_rt_000462e0(&lo);   /* FUN_000462e0 */
            } else {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_000462e8(&lo, ret & 0xffff00ff);   /* FUN_000462e8 */
            }
            (*(void (*)(unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, ((unsigned long)hi << 32) | lo);
            return;
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2d8ec);
}

/*----*/
/* vas_fh_detach_sync @ 0x2d93c   (est. vas_fault_handler_lookup_unregister)
 * Ghidra: void vas_fh_detach_sync(long param_1, undefined8 param_2, long param_3)
 * Claims a request slot (kind 0x10000001a) for a lookup-then-unregister op:
 * dispatches via the static descriptor &LAB_0065b380, and on success removes
 * reg_obj from the registration list (vas_fh_region_remove) and reports success;
 * otherwise reports the error code. Uses the negated form of the bounds check.
 * Confidence: high */
void vas_fh_detach_sync(unsigned long obj, unsigned long reg_obj, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_lo, floor_lo;
    unsigned long *slot;
    unsigned long ret;
    unsigned int lo;
    unsigned short hi;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_lo = (*(unsigned long *)(obj + 0x28) < end);
    floor_lo = (cur < *(unsigned long *)(obj + 0x30));
    hdr = (unsigned long *)(cur + 0x1f0);
    if ((((cap_lo || end < cur) || floor_lo) || (unsigned long *)(cur + 0x208) <= hdr) &&
        (((cap_lo || end < cur) || floor_lo) || hdr != (unsigned long *)(cur + 0x208)))
        goto bounds_fail;
    seq = *hdr;
    if (seq == 0) {
        slot = (unsigned long *)0x0;
    } else {
        unsigned long l = *(unsigned long *)(cur + 0x1f8);
        *(unsigned long *)(cur + 0x1f8) = l + 1;
        unsigned long s = l + 1;
        unsigned long m = 0;
        if (seq != 0) { m = s / seq; }
        unsigned long *base = *(unsigned long **)(cur + 0x200);
        slot = base + (s - m * seq) * 6;
        if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
            goto bounds_fail;
        slot[0] = 0x10000001a;
        slot[1] = reg_obj;
        slot[3] = 0;
        slot[2] = 0;
        slot[5] = 0;
        slot[4] = 0;
    }
    hi = 0;
    lo = 0;
    sk_mtx_lock(**(unsigned long **)(obj + 0x38));
    cur = *(unsigned long *)(obj + 0x20);
    if ((cur != 0) &&
       ((cur + 0x210 < cur || *(unsigned long *)(obj + 0x28) < cur + 0x210) ||
        cur < *(unsigned long *)(obj + 0x30))) goto bounds_fail;
    ret = vas_fh_lookup_entry(cur, reg_obj, (unsigned long *)0x65b380);   /* vas_fh_lookup_entry, desc &LAB_0065b380 */
    if (slot == (unsigned long *)0x0) {
        if ((ret & 0xff) == 0) goto success;
    } else {
        if ((ret & 0xff) == 0) {
            *(unsigned char *)((unsigned long)slot + 4) = 0;
            slot[4] = 0;
            slot[5] = 0;
success:
            cur = *(unsigned long *)(obj + 0x20);
            if ((cur != 0) &&
               ((cur + 0x210 < cur || *(unsigned long *)(obj + 0x28) < cur + 0x210) ||
                cur < *(unsigned long *)(obj + 0x30))) goto bounds_fail;
            vas_fh_region_remove(cur, reg_obj);   /* vas_fh_region_remove */
            sk_rt_000462e0(&lo);   /* FUN_000462e0 */
            goto done;
        }
        if (5 < ((unsigned int)ret & 0xff) - 1) {
            sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
        }
        *(char *)((unsigned long)slot + 1) = (char)ret;
        *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
        *(unsigned char *)((unsigned long)slot + 4) = 0;
    }
    if (5 < ((unsigned int)ret & 0xff) - 1) {
        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
    }
    sk_rt_000462e8(&lo, ret & 0xffff00ff);   /* FUN_000462e8 */
done:
    sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
    (*(void (*)(unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, ((unsigned long)hi << 32) | lo);
    return;
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2db0c);
}

/*----*/
/* vas_fh_map_dispatch @ 0x2db3c   (est. vas_fault_handler_map_8)
 * Ghidra: void vas_fh_map_dispatch(long param_1, undefined8 param_2, long param_3)
 * Map-dispatch family member: claims a request slot (kind 0x100000015), phys-
 * allocates a page (FUN_00034f70), and if one is obtained invokes the method
 * table entry at *(*(obj+0x38)+8)+0x10 with (reg_obj, size=8, page). On success
 * the page handle is encoded and reported; on failure the page is destroyed and
 * the error code reported.
 * Confidence: high
 * Notes: the 2db3c/2dd1c/2defc/2e0dc family differs only in kind and size byte. */
void vas_fh_map_dispatch(unsigned long obj, unsigned long reg_obj, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_lo, floor_lo;
    unsigned long *slot;
    unsigned long page, ret;
    unsigned long m;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_lo = (*(unsigned long *)(obj + 0x28) < end);
    floor_lo = (cur < *(unsigned long *)(obj + 0x30));
    hdr = (unsigned long *)(cur + 0x1f0);
    if ((((cap_lo || end < cur) || floor_lo) || (unsigned long *)(cur + 0x208) <= hdr) &&
        (((cap_lo || end < cur) || floor_lo) || hdr != (unsigned long *)(cur + 0x208)))
        goto bounds_fail;
    seq = *hdr;
    if (seq == 0) {
        slot = (unsigned long *)0x0;
    } else {
        unsigned long l = *(unsigned long *)(cur + 0x1f8);
        *(unsigned long *)(cur + 0x1f8) = l + 1;
        unsigned long s = l + 1;
        unsigned long m2 = 0;
        if (seq != 0) { m2 = s / seq; }
        unsigned long *base = *(unsigned long **)(cur + 0x200);
        slot = base + (s - m2 * seq) * 6;
        if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
            goto bounds_fail;
        slot[0] = 0x100000015;
        slot[1] = reg_obj;
        slot[3] = 0;
        slot[2] = 0;
        slot[5] = 0;
        slot[4] = 0;
    }
    result = 0;
    (void)0;
    page = sk_phys_alloc();   /* FUN_00034f70 */
    if (page == 0) {
        if (slot != (unsigned long *)0x0) {
            *(unsigned char *)((unsigned long)slot + 1) = 2;
            *(unsigned short *)((unsigned long)slot + 2) = 0;
            *(unsigned char *)((unsigned long)slot + 4) = 0;
        }
        ret = 2;
    } else {
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        m = *(unsigned long *)(*(unsigned long *)(obj + 0x38) + 8);
        ret = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long))*(unsigned long **)(m + 0x10))(m, reg_obj, 8, page);
        sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
        if (slot == (unsigned long *)0x0) {
            if ((ret & 0xff) == 0) goto mapok;
        } else {
            if ((ret & 0xff) == 0) {
                *(unsigned char *)((unsigned long)slot + 4) = 0;
                slot[4] = 0;
                slot[5] = 0;
mapok:
                sk_rt_00046314(&result, page);   /* FUN_00046314 */
                goto deliver;
            }
            if (5 < ((unsigned int)ret & 0xff) - 1) {
                sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
            }
            *(char *)((unsigned long)slot + 1) = (char)ret;
            *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
            *(unsigned char *)((unsigned long)slot + 4) = 0;
        }
        cl4_destroy_elem(page);   /* FUN_004b23d8 */
        if (5 < ((unsigned int)ret & 0xff) - 1) {
            sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
        }
        ret = ret & 0xffff00ff;
    }
    sk_rt_00046304(&result, ret);   /* FUN_00046304 */
deliver:
    (*(void (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, result, 0);
    return;
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2dcfc);
}

/*----*/
/* vas_fh_map6_dispatch @ 0x2dd1c   (est. vas_fault_handler_map_6)
 * Ghidra: void vas_fh_map6_dispatch(long param_1, undefined8 param_2, long param_3)
 * Map-dispatch family member: kind 0x100000016, size byte 6. Same shape as
 * 2db3c; on page-allocation failure reports code 2.
 * Confidence: high */
void vas_fh_map6_dispatch(unsigned long obj, unsigned long reg_obj, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_lo, floor_lo;
    unsigned long *slot;
    unsigned long page, ret;
    unsigned long m;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_lo = (*(unsigned long *)(obj + 0x28) < end);
    floor_lo = (cur < *(unsigned long *)(obj + 0x30));
    hdr = (unsigned long *)(cur + 0x1f0);
    if ((((cap_lo || end < cur) || floor_lo) || (unsigned long *)(cur + 0x208) <= hdr) &&
        (((cap_lo || end < cur) || floor_lo) || hdr != (unsigned long *)(cur + 0x208)))
        goto bounds_fail;
    seq = *hdr;
    if (seq == 0) {
        slot = (unsigned long *)0x0;
    } else {
        unsigned long l = *(unsigned long *)(cur + 0x1f8);
        *(unsigned long *)(cur + 0x1f8) = l + 1;
        unsigned long s = l + 1;
        unsigned long m2 = 0;
        if (seq != 0) { m2 = s / seq; }
        unsigned long *base = *(unsigned long **)(cur + 0x200);
        slot = base + (s - m2 * seq) * 6;
        if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
            goto bounds_fail;
        slot[0] = 0x100000016;
        slot[1] = reg_obj;
        slot[3] = 0;
        slot[2] = 0;
        slot[5] = 0;
        slot[4] = 0;
    }
    result = 0;
    (void)0;
    page = sk_phys_alloc();   /* FUN_00034f70 */
    if (page == 0) {
        if (slot != (unsigned long *)0x0) {
            *(unsigned char *)((unsigned long)slot + 1) = 2;
            *(unsigned short *)((unsigned long)slot + 2) = 0;
            *(unsigned char *)((unsigned long)slot + 4) = 0;
        }
        ret = 2;
    } else {
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        m = *(unsigned long *)(*(unsigned long *)(obj + 0x38) + 8);
        ret = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long))*(unsigned long **)(m + 0x10))(m, reg_obj, 6, page);
        sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
        if (slot == (unsigned long *)0x0) {
            if ((ret & 0xff) == 0) goto mapok;
        } else {
            if ((ret & 0xff) == 0) {
                *(unsigned char *)((unsigned long)slot + 4) = 0;
                slot[4] = 0;
                slot[5] = 0;
mapok:
                sk_rt_00046314(&result, page);   /* FUN_00046314 */
                goto deliver;
            }
            if (5 < ((unsigned int)ret & 0xff) - 1) {
                sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
            }
            *(char *)((unsigned long)slot + 1) = (char)ret;
            *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
            *(unsigned char *)((unsigned long)slot + 4) = 0;
        }
        cl4_destroy_elem(page);   /* FUN_004b23d8 */
        if (5 < ((unsigned int)ret & 0xff) - 1) {
            sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
        }
        ret = ret & 0xffff00ff;
    }
    sk_rt_00046304(&result, ret);   /* FUN_00046304 */
deliver:
    (*(void (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, result, 0);
    return;
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2dedc);
}

/*----*/
/* vas_fh_map15_dispatch @ 0x2defc   (est. vas_fault_handler_map_21)
 * Ghidra: void vas_fh_map15_dispatch(long param_1, undefined8 param_2, long param_3)
 * Map-dispatch family member: kind 0x100000017, size byte 0x15. Same shape as
 * 2db3c; on page-allocation failure reports code 2.
 * Confidence: high */
void vas_fh_map15_dispatch(unsigned long obj, unsigned long reg_obj, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_lo, floor_lo;
    unsigned long *slot;
    unsigned long page, ret;
    unsigned long m;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_lo = (*(unsigned long *)(obj + 0x28) < end);
    floor_lo = (cur < *(unsigned long *)(obj + 0x30));
    hdr = (unsigned long *)(cur + 0x1f0);
    if ((((cap_lo || end < cur) || floor_lo) || (unsigned long *)(cur + 0x208) <= hdr) &&
        (((cap_lo || end < cur) || floor_lo) || hdr != (unsigned long *)(cur + 0x208)))
        goto bounds_fail;
    seq = *hdr;
    if (seq == 0) {
        slot = (unsigned long *)0x0;
    } else {
        unsigned long l = *(unsigned long *)(cur + 0x1f8);
        *(unsigned long *)(cur + 0x1f8) = l + 1;
        unsigned long s = l + 1;
        unsigned long m2 = 0;
        if (seq != 0) { m2 = s / seq; }
        unsigned long *base = *(unsigned long **)(cur + 0x200);
        slot = base + (s - m2 * seq) * 6;
        if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
            goto bounds_fail;
        slot[0] = 0x100000017;
        slot[1] = reg_obj;
        slot[3] = 0;
        slot[2] = 0;
        slot[5] = 0;
        slot[4] = 0;
    }
    result = 0;
    (void)0;
    page = sk_phys_alloc();   /* FUN_00034f70 */
    if (page == 0) {
        if (slot != (unsigned long *)0x0) {
            *(unsigned char *)((unsigned long)slot + 1) = 2;
            *(unsigned short *)((unsigned long)slot + 2) = 0;
            *(unsigned char *)((unsigned long)slot + 4) = 0;
        }
        ret = 2;
    } else {
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        m = *(unsigned long *)(*(unsigned long *)(obj + 0x38) + 8);
        ret = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long))*(unsigned long **)(m + 0x10))(m, reg_obj, 0x15, page);
        sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
        if (slot == (unsigned long *)0x0) {
            if ((ret & 0xff) == 0) goto mapok;
        } else {
            if ((ret & 0xff) == 0) {
                *(unsigned char *)((unsigned long)slot + 4) = 0;
                slot[4] = 0;
                slot[5] = 0;
mapok:
                sk_rt_00046314(&result, page);   /* FUN_00046314 */
                goto deliver;
            }
            if (5 < ((unsigned int)ret & 0xff) - 1) {
                sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
            }
            *(char *)((unsigned long)slot + 1) = (char)ret;
            *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
            *(unsigned char *)((unsigned long)slot + 4) = 0;
        }
        cl4_destroy_elem(page);   /* FUN_004b23d8 */
        if (5 < ((unsigned int)ret & 0xff) - 1) {
            sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
        }
        ret = ret & 0xffff00ff;
    }
    sk_rt_00046304(&result, ret);   /* FUN_00046304 */
deliver:
    (*(void (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, result, 0);
    return;
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2e0bc);
}

/*----*/
/* vas_fh_map14_dispatch @ 0x2e0dc   (est. vas_fault_handler_map_20)
 * Ghidra: void vas_fh_map14_dispatch(long param_1, undefined8 param_2, long param_3)
 * Map-dispatch family member: kind 0x100000018, size byte 0x14. Same shape as
 * 2db3c; on page-allocation failure reports code 2.
 * Confidence: high */
void vas_fh_map14_dispatch(unsigned long obj, unsigned long reg_obj, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_lo, floor_lo;
    unsigned long *slot;
    unsigned long page, ret;
    unsigned long m;
    unsigned long result;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_lo = (*(unsigned long *)(obj + 0x28) < end);
    floor_lo = (cur < *(unsigned long *)(obj + 0x30));
    hdr = (unsigned long *)(cur + 0x1f0);
    if ((((cap_lo || end < cur) || floor_lo) || (unsigned long *)(cur + 0x208) <= hdr) &&
        (((cap_lo || end < cur) || floor_lo) || hdr != (unsigned long *)(cur + 0x208)))
        goto bounds_fail;
    seq = *hdr;
    if (seq == 0) {
        slot = (unsigned long *)0x0;
    } else {
        unsigned long l = *(unsigned long *)(cur + 0x1f8);
        *(unsigned long *)(cur + 0x1f8) = l + 1;
        unsigned long s = l + 1;
        unsigned long m2 = 0;
        if (seq != 0) { m2 = s / seq; }
        unsigned long *base = *(unsigned long **)(cur + 0x200);
        slot = base + (s - m2 * seq) * 6;
        if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
            goto bounds_fail;
        slot[0] = 0x100000018;
        slot[1] = reg_obj;
        slot[3] = 0;
        slot[2] = 0;
        slot[5] = 0;
        slot[4] = 0;
    }
    result = 0;
    (void)0;
    page = sk_phys_alloc();   /* FUN_00034f70 */
    if (page == 0) {
        if (slot != (unsigned long *)0x0) {
            *(unsigned char *)((unsigned long)slot + 1) = 2;
            *(unsigned short *)((unsigned long)slot + 2) = 0;
            *(unsigned char *)((unsigned long)slot + 4) = 0;
        }
        ret = 2;
    } else {
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        m = *(unsigned long *)(*(unsigned long *)(obj + 0x38) + 8);
        ret = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long))*(unsigned long **)(m + 0x10))(m, reg_obj, 0x14, page);
        sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
        if (slot == (unsigned long *)0x0) {
            if ((ret & 0xff) == 0) goto mapok;
        } else {
            if ((ret & 0xff) == 0) {
                *(unsigned char *)((unsigned long)slot + 4) = 0;
                slot[4] = 0;
                slot[5] = 0;
mapok:
                sk_rt_00046314(&result, page);   /* FUN_00046314 */
                goto deliver;
            }
            if (5 < ((unsigned int)ret & 0xff) - 1) {
                sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
            }
            *(char *)((unsigned long)slot + 1) = (char)ret;
            *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
            *(unsigned char *)((unsigned long)slot + 4) = 0;
        }
        cl4_destroy_elem(page);   /* FUN_004b23d8 */
        if (5 < ((unsigned int)ret & 0xff) - 1) {
            sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
        }
        ret = ret & 0xffff00ff;
    }
    sk_rt_00046304(&result, ret);   /* FUN_00046304 */
deliver:
    (*(void (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, result, 0);
    return;
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2e29c);
}

/*----*/
/* vas_fh_clear @ 0x2e2bc   (est. vas_fault_handler_commit)
 * Ghidra: void vas_fh_clear(long param_1, undefined8 param_2, long param_3)
 * Claims a request slot (kind 0x100000019) and commits a fault-handler op by
 * invoking the method table entry at *(*(obj+0x38)+0x10)+0x10 with (reg_obj).
 * Reports success/error through the reply.
 * Confidence: high */
void vas_fh_clear(unsigned long obj, unsigned long reg_obj, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_lo, floor_lo;
    unsigned long *slot;
    unsigned long ret;
    unsigned long m;
    unsigned int lo;
    unsigned short hi;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_lo = (*(unsigned long *)(obj + 0x28) < end);
    floor_lo = (cur < *(unsigned long *)(obj + 0x30));
    hdr = (unsigned long *)(cur + 0x1f0);
    if ((((cap_lo || end < cur) || floor_lo) || (unsigned long *)(cur + 0x208) <= hdr) &&
        (((cap_lo || end < cur) || floor_lo) || hdr != (unsigned long *)(cur + 0x208)))
        goto bounds_fail;
    seq = *hdr;
    if (seq == 0) {
        slot = (unsigned long *)0x0;
    } else {
        unsigned long l = *(unsigned long *)(cur + 0x1f8);
        *(unsigned long *)(cur + 0x1f8) = l + 1;
        unsigned long s = l + 1;
        unsigned long m2 = 0;
        if (seq != 0) { m2 = s / seq; }
        unsigned long *base = *(unsigned long **)(cur + 0x200);
        slot = base + (s - m2 * seq) * 6;
        if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
            goto bounds_fail;
        slot[0] = 0x100000019;
        slot[1] = reg_obj;
        slot[3] = 0;
        slot[2] = 0;
        slot[5] = 0;
        slot[4] = 0;
    }
    hi = 0;
    lo = 0;
    sk_mtx_lock(**(unsigned long **)(obj + 0x38));
    m = *(unsigned long *)(*(unsigned long *)(obj + 0x38) + 0x10);
    ret = (*(unsigned long (*)(unsigned long, unsigned long))*(unsigned long **)(m + 0x10))(m, reg_obj);
    sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
    if (slot == (unsigned long *)0x0) {
        if ((ret & 0xff) == 0) goto ok;
    } else {
        if ((ret & 0xff) == 0) {
            *(unsigned char *)((unsigned long)slot + 4) = 0;
            slot[4] = 0;
            slot[5] = 0;
ok:
            sk_rt_000462e0(&lo);   /* FUN_000462e0 */
            goto done;
        }
        if (5 < ((unsigned int)ret & 0xff) - 1) {
            sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
        }
        *(char *)((unsigned long)slot + 1) = (char)ret;
        *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
        *(unsigned char *)((unsigned long)slot + 4) = 0;
    }
    if (5 < ((unsigned int)ret & 0xff) - 1) {
        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
    }
    sk_rt_000462e8(&lo, ret & 0xffff00ff);   /* FUN_000462e8 */
done:
    (*(void (*)(unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, ((unsigned long)hi << 32) | lo);
    return;
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2e440);
}

/*----*/
/* vas_fh_clear2 @ 0x2e460   (est. vas_fault_handler_commit_2)
 * Ghidra: void vas_fh_clear2(long param_1, undefined8 param_2, long param_3)
 * Claims a request slot (kind 0x10000000c) and runs a second commit variant via
 * the method table entry at *(*(obj+0x38)+0x18)+0x10 with (reg_obj). Reports
 * success/error through the reply.
 * Confidence: high */
void vas_fh_clear2(unsigned long obj, unsigned long reg_obj, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_lo, floor_lo;
    unsigned long *slot;
    unsigned long ret;
    unsigned long m;
    unsigned int lo;
    unsigned short hi;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_lo = (*(unsigned long *)(obj + 0x28) < end);
    floor_lo = (cur < *(unsigned long *)(obj + 0x30));
    hdr = (unsigned long *)(cur + 0x1f0);
    if ((((cap_lo || end < cur) || floor_lo) || (unsigned long *)(cur + 0x208) <= hdr) &&
        (((cap_lo || end < cur) || floor_lo) || hdr != (unsigned long *)(cur + 0x208)))
        goto bounds_fail;
    seq = *hdr;
    if (seq == 0) {
        slot = (unsigned long *)0x0;
    } else {
        unsigned long l = *(unsigned long *)(cur + 0x1f8);
        *(unsigned long *)(cur + 0x1f8) = l + 1;
        unsigned long s = l + 1;
        unsigned long m2 = 0;
        if (seq != 0) { m2 = s / seq; }
        unsigned long *base = *(unsigned long **)(cur + 0x200);
        slot = base + (s - m2 * seq) * 6;
        if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
            goto bounds_fail;
        slot[0] = 0x10000000c;
        slot[1] = reg_obj;
        slot[3] = 0;
        slot[2] = 0;
        slot[5] = 0;
        slot[4] = 0;
    }
    hi = 0;
    lo = 0;
    sk_mtx_lock(**(unsigned long **)(obj + 0x38));
    m = *(unsigned long *)(*(unsigned long *)(obj + 0x38) + 0x18);
    ret = (*(unsigned long (*)(unsigned long, unsigned long))*(unsigned long **)(m + 0x10))(m, reg_obj);
    sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
    if (slot == (unsigned long *)0x0) {
        if ((ret & 0xff) == 0) goto ok;
    } else {
        if ((ret & 0xff) == 0) {
            *(unsigned char *)((unsigned long)slot + 4) = 0;
            slot[4] = 0;
            slot[5] = 0;
ok:
            sk_rt_000462e0(&lo);   /* FUN_000462e0 */
            goto done;
        }
        if (5 < ((unsigned int)ret & 0xff) - 1) {
            sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
        }
        *(char *)((unsigned long)slot + 1) = (char)ret;
        *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
        *(unsigned char *)((unsigned long)slot + 4) = 0;
    }
    if (5 < ((unsigned int)ret & 0xff) - 1) {
        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
    }
    sk_rt_000462e8(&lo, ret & 0xffff00ff);   /* FUN_000462e8 */
done:
    (*(void (*)(unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, ((unsigned long)hi << 32) | lo);
    return;
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2e5e4);
}

/*----*/
/* vas_fh_get @ 0x2e604   (est. vas_fault_handler_add_thread_info)
 * Ghidra: void vas_fh_get(long param_1, undefined8 param_2, undefined8 param_3, long param_4)
 * Claims a request slot (kind 0x100000012) and forwards to the easm server
 * add-thread-info core (vas_fh_get_internal) with the server's +0x40/+0x48 fields,
 * reg_obj and arg. Reports the outcome through the reply.
 * Confidence: high */
void vas_fh_get(unsigned long obj, unsigned long reg_obj, unsigned long arg, unsigned long reply)
{
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_ok, floor_ok;
    unsigned long *slot;
    unsigned long ret;
    unsigned int c;
    unsigned int lo;
    unsigned short hi;

    cur = *(unsigned long *)(obj + 0x20);
    end = cur + 0x210;
    cap_ok = (end <= *(unsigned long *)(obj + 0x28));
    floor_ok = (*(unsigned long *)(obj + 0x30) <= cur);
    hdr = (unsigned long *)(cur + 0x1f0);
    if (((cap_ok && cur <= end) && floor_ok) && hdr < (unsigned long *)(cur + 0x208) ||
        ((cap_ok && cur <= end) && floor_ok) && hdr == (unsigned long *)(cur + 0x208)) {
        seq = *hdr;
        if (seq == 0) {
            slot = (unsigned long *)0x0;
        } else {
            unsigned long l = *(unsigned long *)(cur + 0x1f8);
            *(unsigned long *)(cur + 0x1f8) = l + 1;
            unsigned long s = l + 1;
            unsigned long m = 0;
            if (seq != 0) { m = s / seq; }
            unsigned long *base = *(unsigned long **)(cur + 0x200);
            slot = base + (s - m * seq) * 6;
            if ((slot < base || base + seq * 6 < slot + 6) || slot + 6 < slot)
                goto bounds_fail;
            slot[0] = 0x100000012;
            slot[1] = reg_obj;
            slot[2] = arg;
            slot[3] = 0;
            slot[4] = 0;
            slot[5] = 0;
        }
        hi = 0;
        lo = 0;
        sk_mtx_lock(**(unsigned long **)(obj + 0x38));
        cur = *(unsigned long *)(obj + 0x20);
        if ((cur == 0) ||
           ((cur <= cur + 0x210 && cur + 0x210 <= *(unsigned long *)(obj + 0x28)) &&
            *(unsigned long *)(obj + 0x30) <= cur)) {
            ret = vas_fh_get_internal(cur, *(unsigned long *)(obj + 0x40), *(unsigned long *)(obj + 0x48),
                                 reg_obj, arg);   /* vas_fh_get_internal */
            if ((ret & 0xff) == 0) {
                sk_rt_000462e0(&lo);   /* FUN_000462e0 */
                if (slot != (unsigned long *)0x0) {
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                    slot[4] = 0;
                    slot[5] = 0;
                }
            } else {
                c = (unsigned int)ret & 0xff;
                if (slot != (unsigned long *)0x0) {
                    if (5 < c - 1) {
                        sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                    }
                    *(char *)((unsigned long)slot + 1) = (char)ret;
                    *(short *)((unsigned long)slot + 2) = (short)(ret >> 0x10);
                    *(unsigned char *)((unsigned long)slot + 4) = 0;
                }
                if (5 < c - 1) {
                    sk_swift_fatal("unknown vas return code 0x%x\n", ret); /* FUN_004afae4 */
                }
                sk_rt_000462e8(&lo, ret & 0xffff00ff);   /* FUN_000462e8 */
            }
            sk_mtx_unlock(**(unsigned long **)(obj + 0x38));
            (*(void (*)(unsigned long, unsigned long))*(unsigned long **)(reply + 0x10))(reply, ((unsigned long)hi << 32) | lo);
            return;
        }
    }
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2e7a4);
}

/*----*/
/* vas_fh_get_internal @ 0x2e7c4   (est. easm_server_add_thread_info)
 * Ghidra: ulong vas_fh_get_internal(long param_1, undefined8 param_2, long param_3, long param_4, ulong param_5)
 * Core add-thread-info path for the easm server. Phys-allocates a page, maps it
 * through the param_3 method (+0x40), verifies the entry key at the mapped slot
 * and grows the server's thread-info array at obj+0x1d8 (count) / +0x1e8 (array)
 * / +0x1e0 (used), appending a new 0xb-word record. On realloc failure it issues
 * a nested request-slot allocation (kind 0x100000014) to report the error. The
 * 128-bit auVar29 value is the boot-object / record descriptor pair.
 * Confidence: medium
 * Notes: string s__easm_server_add_thread_info_005aeac7; magic uVar16 =
 *   0x10e0040669e76eb; bounds SoftwareBreakpoint(0x5519,0x2ea54); globals
 *   DAT_004bc000/008/010/018. */
unsigned long vas_fh_get_internal(unsigned long obj, unsigned long param_2, unsigned long param_3, unsigned long key, unsigned long val)
{
    typedef struct { unsigned long lo; unsigned long hi; } pair_t;
    pair_t a29, a4, a5, a6, boot;
    unsigned long cur, end, seq, d;
    unsigned long *hdr;
    int cap_lo, floor_lo;
    unsigned long *slot;
    unsigned long page, ret, m, uvar16, nbuf;
    unsigned long cnt, used, arr, u18, u17, u22, u23;
    unsigned long r, idx;
    unsigned long *base, *src2, *dst;
    unsigned long u12;

    (void)a5; (void)a6; (void)boot;
    uvar16 = 0x10e0040669e76eb;
    page = sk_phys_alloc();   /* FUN_00034f70 */
    if (page == 0) {
        sk_rt_004b1bd8();   /* FUN_004b1bd8 */
        goto abort_line;
    }
    ret = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long, unsigned long))*(unsigned long **)(param_3 + 0x40))(param_2, val, 0, page);
    if ((ret & 0xff) == 0) {
        /* descriptor built from DAT_004bc000/008/010/018 */
        unsigned long d0 = _DAT_004bc000, d1 = _DAT_004bc008, d2 = _DAT_004bc010, d3 = _DAT_004bc018;
        (void)d0; (void)d1; (void)d2; (void)d3;
        boot = sk_boot_object();   /* FUN_00034a2c, returns 128-bit */
        ret = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long *, unsigned long *, unsigned long, unsigned long *)) * (unsigned long **)(boot.hi + 0x30))(boot.lo, 0x1800, &d0, &base, 0, &d1);
        if ((ret & 0xff) != 0) goto e874;
        r = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long)) * (unsigned long **)((unsigned long *)&base)[5])(base, 0, page);
        cl4_destroy_elem(page);   /* FUN_004b23d8 */
        ret = 0;
        if ((r & 0xff) != 0) { ret = r; }
    } else {
e874:
        cl4_destroy_elem(page);   /* FUN_004b23d8 */
    }
    if ((ret & 0xff) != 0) { return ret; }
    u12 = (unsigned long)((unsigned long *)&base)[2] + (val & 0x3fff);
    if (*(unsigned long *)(u12 + 8) != key) {
        (*(void (*)(unsigned long)) * (unsigned long **)((unsigned long *)&base)[0])(base);
        return 0x20c0001;
    }
    u18 = u12 + 0x50;
    a29 = (pair_t)(*(pair_t (*)(unsigned long, unsigned long, unsigned long))*(unsigned long **)(param_3 + 0x38))(param_2, *(unsigned long *)(u12 + 0x18), 0);
    if (u18 < u12) goto overflow;
    cnt = *(unsigned long *)(obj + 0x1d8);
    used = *(unsigned long *)(obj + 0x1e0);
    if (cnt < used) goto abort_line;
    if (cnt <= used) {
        /* grow the thread-info array */
        u17 = cnt * 2;
        if (u17 < 0x11) { u17 = 0x10; }
        if (u17 < cnt) {
            sk_swift_fatal("VAS abort in function %s at line %d", __func__, 0); /* FUN_004afae4 s__easm_server_add_thread_info_005aeac7 */
        }
        u23 = u17 * 0x58;
        nbuf = sk_realloc(*(unsigned long *)(obj + 0x1e8), u23);   /* FUN_000102f4 */
        if (nbuf == 0) {
            /* nested request-slot allocation to report the failure (kind 0x14) */
            a29 = sk_rt_004b1b9c();   /* FUN_004b1b9c, returns 128-bit */
            cur = *(unsigned long *)(a29.lo + 0x20);
            end = cur + 0x210;
            cap_lo = (*(unsigned long *)(a29.lo + 0x28) < end);
            floor_lo = (cur < *(unsigned long *)(a29.lo + 0x30));
            hdr = (unsigned long *)(cur + 0x1f0);
            if ((((cap_lo || end < cur) || floor_lo) || (unsigned long *)(cur + 0x208) <= hdr) &&
                (((cap_lo || end < cur) || floor_lo) || hdr != (unsigned long *)(cur + 0x208)))
                goto bounds_fail;
            seq = *hdr;
            if (seq == 0) {
                slot = (unsigned long *)0x0;
            } else {
                unsigned long l = *(unsigned long *)(cur + 0x1f8);
                *(unsigned long *)(cur + 0x1f8) = l + 1;
                unsigned long s = l + 1;
                unsigned long m2 = 0;
                if (seq != 0) { m2 = s / seq; }
                unsigned long *b = *(unsigned long **)(cur + 0x200);
                slot = b + (s - m2 * seq) * 6;
                if ((slot < b || b + seq * 6 < slot + 6) || slot + 6 < slot)
                    goto bounds_fail;
                slot[0] = 0x100000014;
                slot[1] = a29.hi;
                slot[2] = uvar16;
                slot[3] = 0;
                slot[4] = 0;
                slot[5] = 0;
            }
            {
                unsigned int lo2 = 0; unsigned short hi2 = 0;
                (void)hi2;
                sk_mtx_lock(**(unsigned long **)(a29.lo + 0x38));
                cur = *(unsigned long *)(a29.lo + 0x20);
                if ((cur != 0) &&
                   ((cur + 0x210 < cur || *(unsigned long *)(a29.lo + 0x28) < cur + 0x210) ||
                    cur < *(unsigned long *)(a29.lo + 0x30))) goto bounds_fail;
                idx = sk_rt_00028950(cur, 0, 0, uvar16);   /* FUN_00028950 */
                if (idx == 0) {
                    sk_rt_000462e8(&lo2, 4);   /* FUN_000462e8 */
                    if (slot == (unsigned long *)0x0) goto edd4;
                    *(unsigned char *)((unsigned long)slot + 1) = 4;
                } else {
                    if (*(unsigned long *)(*(unsigned long *)(idx + 8) + 8) == a29.hi) {
                        r = (*(unsigned long (*)(unsigned long)) * (unsigned long **)*(unsigned long **)(idx + 0x18))(*(unsigned long *)(idx + 0x10));
                        if (slot == (unsigned long *)0x0) {
                            if ((r & 0xff) == 0) goto ed10;
                        } else {
                            if ((r & 0xff) == 0) {
                                *(unsigned char *)((unsigned long)slot + 4) = 0;
                                slot[4] = 0;
                                slot[5] = 0;
ed10:
                                cur = *(unsigned long *)(a29.lo + 0x20);
                                if ((cur != 0) &&
                                   ((cur + 0x210 < cur || *(unsigned long *)(a29.lo + 0x28) < cur + 0x210) ||
                                    cur < *(unsigned long *)(a29.lo + 0x30))) goto bounds_fail;
                                src2 = (unsigned long *)sk_rt_00028950(cur, 0, 0, uvar16);   /* FUN_00028950 */
                                if (src2 == (unsigned long *)0x0) {
                                    sk_swift_fatal("VAS abort in function %s at line %d", __func__, 0); /* FUN_004afae4 */
                                }
                                u18 = *(unsigned long *)(cur + 0x1e0);
                                if (u18 == 0) {
                                    sk_rt_004b1c10();   /* FUN_004b1c10 */
                                    goto abort_line;
                                }
                                u17 = *(unsigned long *)(cur + 0x1d8);
                                if (u17 < u18) goto abort_line;
                                u18 = u18 - 1;
                                *(unsigned long *)(cur + 0x1e0) = u18;
                                base = *(unsigned long **)(cur + 0x1e8);
                                dst = base + u18 * 0xb;
                                if ((u17 * 0x58 + u18 * -0x58 < 0x58 || base + u17 * 0xb < dst) ||
                                    dst < base) goto bounds_fail;
                                {
                                    unsigned long t0 = dst[0], t1 = dst[1], t2 = dst[2], t3 = dst[3];
                                    unsigned long t4 = dst[4], t5 = dst[5], t6 = dst[6], t7 = dst[7];
                                    unsigned long t8 = dst[8], t9 = dst[9], t10 = dst[10];
                                    src2[0] = t0; src2[1] = t1; src2[2] = t2; src2[3] = t3;
                                    src2[4] = t4; src2[5] = t5; src2[6] = t6; src2[7] = t7;
                                    src2[8] = t8; src2[9] = t9; src2[10] = t10;
                                }
                                if (src2 + 0xb < src2) goto bounds_fail;
                                sk_rt_000462e0(&lo2);   /* FUN_000462e0 */
                                goto edd4;
                            }
                            if (5 < ((unsigned int)r & 0xff) - 1) {
                                sk_swift_fatal("unknown vas return code 0x%x\n", r); /* FUN_004afae4 */
                            }
                            *(char *)((unsigned long)slot + 1) = (char)r;
                            *(short *)((unsigned long)slot + 2) = (short)(r >> 0x10);
                            *(unsigned char *)((unsigned long)slot + 4) = 0;
                        }
                        if (5 < ((unsigned int)r & 0xff) - 1) {
                            sk_swift_fatal("unknown vas return code 0x%x\n", r); /* FUN_004afae4 */
                        }
                        sk_rt_000462e8(&lo2, r & 0xffff00ff);   /* FUN_000462e8 */
                        goto edd4;
                    }
                    sk_rt_000462e8(&lo2, 0x5780001);   /* FUN_000462e8 */
                    if (slot == (unsigned long *)0x0) goto edd4;
                    *(unsigned char *)((unsigned long)slot + 1) = 1;
                }
                *(unsigned short *)((unsigned long)slot + 2) = 0;
                *(unsigned char *)((unsigned long)slot + 4) = 0;
edd4:
                sk_mtx_unlock(**(unsigned long **)(a29.lo + 0x38));
                return (*(unsigned long (*)(unsigned long, unsigned long)) * (unsigned long **)0)(0, ((unsigned long)lo2) | 0);
            }
        }
        /* grow-copy the existing array */
        u18 = *(unsigned long *)(obj + 0x1d8);
        idx = u17 - u18;
        if (u18 <= u17 && idx != 0) {
            u22 = u18 * 0x58;
            u18 = u23 + u18 * -0x58;
            do {
                unsigned long srcaddr;
                int small = (u18 < 0x58);
                u18 = u18 - 0x58;
                srcaddr = nbuf + u22;
                if ((small) || (srcaddr >= nbuf + u23) || (srcaddr < nbuf)) goto overflow;
                {
                    unsigned long clear = 0;
                    if (u22 <= u23) { clear = u23 - u22; }
                    sk_rt_00117d68(srcaddr, 0, 0x58, clear);   /* FUN_00117d68 memset */
                }
                u22 = u22 + 0x58;
                idx = idx - 1;
            } while (idx != 0);
        }
        if ((nbuf + u23 < nbuf) || (u23 / 8) < u17) goto overflow;
        *(unsigned long *)(obj + 0x1e8) = nbuf;
        *(unsigned long *)(obj + 0x1d8) = u17;
        used = *(unsigned long *)(obj + 0x1e0);
        cnt = u17;
    }
    if (cnt <= used) {
        sk_swift_fatal("VAS abort in function %s at line %d", __func__, 0); /* FUN_004afae4 s__easm_server_add_thread_info_005aeac7 */
    }
    base = *(unsigned long **)(obj + 0x1e8);
    dst = base + used * 0xb;
    if ((0x57 < cnt * 0x58 + used * -0x58 && dst <= base + cnt * 0xb) &&
        base <= dst) {
        dst[0] = val;
        dst[1] = u12;
        dst[3] = (unsigned long)&base[1];
        dst[2] = (unsigned long)&base[0];
        dst[5] = (unsigned long)&base[3];
        dst[4] = (unsigned long)&base[2];
        dst[7] = (unsigned long)&base[5];
        dst[6] = (unsigned long)&base[4];
        dst[8] = 0;
        dst[9] = a29.lo;
        dst[10] = a29.hi;
        if (dst <= dst + 0xb) {
            *(unsigned long *)(obj + 0x1e0) = *(unsigned long *)(obj + 0x1e0) + 1;
            return 0;
        }
    }
overflow:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2ea54);
abort_line:
    /* does not return */
    sk_swift_fatal("VAS abort in function %s at line %d", __func__, 0); /* FUN_004afae4 s__easm_server_add_thread_info_005aeac7 */
bounds_fail:
    /* does not return */
    (*(void (**)(void))SoftwareBreakpoint)(0x5519, 0x2eda0);
}
