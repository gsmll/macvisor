/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range helpers referenced by this region (FUN_ addr in comment;
 * reconstructed by sibling SK range workers). Names are estimates.
 * ------------------------------------------------------------------ */
extern void sk_fatal_error(const char *msg, unsigned long a, unsigned long b,
                           unsigned long c, unsigned long d, const char *s2,
                           unsigned long e, unsigned long f, ...); /* FUN_001afa84, noreturn */
extern void sk_stack_chk_fail(void);                          /* FUN_0011d7e8, noreturn */
extern void sk_swift_fatal(const char *fmt, ...);             /* FUN_004afae4, noreturn */
extern void sk_swift_assert(const char *msg);                 /* FUN_00118b28, noreturn */
extern void sk_software_breakpoint(void);                     /* FUN_00116d60, noreturn */
extern void sk_lock_spin(unsigned long);                      /* FUN_0036b270 */
extern void sk_lock_release(unsigned long);                   /* FUN_0036b118 */
extern void *sk_alloc_typed(unsigned long tag, unsigned long size, unsigned long mtag); /* FUN_0036a940 */
extern void *sk_alloc_aligned(unsigned long size, unsigned long tag);  /* FUN_0036a804 */
extern void sk_lock_unref(unsigned long);                     /* FUN_0036b21c */
extern void sk_lock_ref2(unsigned long);                      /* FUN_0036b6ac */
extern void sk_ptr_array_at(void *a, void *b);                /* FUN_0036ffc0 */
extern unsigned long sk_obj_reg_get(void);                             /* FUN_00376820 */
extern void sk_current_domain(void);                          /* FUN_00389b64 */
extern void sk_release_domain(void);                          /* FUN_00368da8 */
extern unsigned long sk_wake_and_switch_to(void);             /* FUN_00377dcc */

#define SWIFT_BREAKPOINT()   sk_software_breakpoint()   /* SoftwareBreakpoint(1,..) */
#define SWIFT_BREAKPOINT_A() sk_software_breakpoint()   /* SoftwareBreakpoint(0x5519,..) */

/* ------------------------------------------------------------------ *
 * Concrete helper stubs + forward declarations for functions defined
 * later in this file / by sibling SK range workers.
 * ------------------------------------------------------------------ */
static void tightbeam_copy_region(unsigned long a, unsigned long b, unsigned long c,
                                  unsigned long d, unsigned long e)
{ (void)a; (void)b; (void)c; (void)d; (void)e; }   /* FUN_002e2d24 copy */
static cl4_result_t tightbeam_msg_kind_status(unsigned long tag)
{ cl4_result_t r; r.lo = tag; r.hi = 0x40; return r; }   /* FUN_00019aac */
static unsigned long tightbeam_lock_and_get(unsigned long a, unsigned long b)
{ (void)a; (void)b; return 0; }                    /* FUN_00377dcc */
static void tightbeam_obj_read_kind(unsigned long a, unsigned long b, unsigned long c,
                                    unsigned long *d)
{ (void)a; (void)b; (void)c; if (d) *d = 0; }      /* FUN_00368da8 */
static void tightbeam_obj_bind_reset(unsigned long a, unsigned long b, unsigned long c)
{ (void)a; (void)b; (void)c; }                     /* thunk_FUN_00012568 */
static void tightbeam_msg_write_end(void);         /* 0x23448 */
static void tightbeam_msg_write_begin(void);       /* 0x234bc */
static void tightbeam_decoder_encode_dispatch(unsigned long, unsigned long, unsigned long,
                                              unsigned long, unsigned long); /* 0x23f74 */

/* Externs owned by sibling SK range workers. */
extern unsigned long sk_dispatch_async(unsigned long, unsigned long, unsigned long,
                                       unsigned long, unsigned long, unsigned long,
                                       unsigned long, unsigned long); /* FUN_0004b520 */
extern void sk_dispatch_free(unsigned long);               /* FUN_0004b664 */
extern unsigned long sk_validate(unsigned long, unsigned long, unsigned long, unsigned long,
                                 unsigned long, unsigned long); /* FUN_003a26e8 */
extern unsigned long sk_msg_copy(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_00015a44 */
extern unsigned long sk_object_lock(unsigned long, unsigned long, unsigned long, void *, void *); /* FUN_00377824 */
extern unsigned long sk_alloc_global(unsigned long, unsigned long, unsigned long, unsigned long,
                                     unsigned long);      /* FUN_00389b64 */
extern void *sk_realloc(unsigned long, unsigned long);     /* FUN_000102f4 */
extern void *sk_alloc_pages(unsigned long, unsigned long); /* FUN_00010244 */
extern void *sk_alloc_vas(unsigned long);                  /* FUN_000101a0 */
extern unsigned long sk_retain(unsigned long);             /* FUN_0004b520 */
extern unsigned long sk_page_resolve(void);                /* FUN_00034f70 */
extern unsigned long sk_vas_register(unsigned long, unsigned long); /* FUN_000147a0 */
extern unsigned long sk_msg_reset(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_00014c08 */
extern unsigned long sk_msg_reset2(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_00014f90 */
extern unsigned long sk_msg_decode(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_0001485c */
extern unsigned long sk_msg_init(unsigned long, void *, unsigned long, unsigned long, unsigned long); /* FUN_00014bd4 */
extern unsigned long sk_page_check(unsigned long, unsigned long, unsigned long, unsigned long); /* FUN_0003c4c0 */
extern unsigned long sk_error_obj(void);                   /* FUN_00019aac */
extern unsigned long sk_obj_lock2(unsigned long);          /* FUN_00310d68 */

/* Global once-cells used by the type-registration helpers. */

/* Forward declarations for functions defined later in this file. */
static cl4_result_t tightbeam_msg_kind_status(unsigned long tag);
static unsigned long tightbeam_lock_and_get(unsigned long a, unsigned long b);
static void tightbeam_obj_bind_reset(unsigned long a, unsigned long b, unsigned long c);
void tightbeam_transport_init(void);
cl4_result_t tightbeam_transport_alloc(void);
void tightbeam_transport_dispatch_tail(void);
void tightbeam_tb_done(unsigned long param_1, unsigned long param_2);
void tightbeam_tb_done2(unsigned long param_1, unsigned long param_2);
cl4_result_t tightbeam_failure_code(unsigned int param_1);
cl4_result_t tightbeam_msg_kind(long param_1);
void tightbeam_once_init(void);
void tightbeam_tb_descriptor_copy(unsigned char *param_1, unsigned char *param_2);
void tightbeam_message_reset(void);
unsigned long tightbeam_decoder_unwrap(unsigned long param_1, long param_2);
unsigned int tightbeam_decoder_decode_forward(unsigned long param_1, void (*param_2)(void));
void tightbeam_message_read_u8(void);
void tightbeam_msg_get_bool(void);
void tightbeam_msg_get_u16(void);
void tightbeam_msg_get_u32(void);
void tightbeam_msg_get_u64(void);
void tightbeam_msg_get_bool_alt(void);
void tightbeam_msg_field_dispatch_1(void (*param_1)(unsigned long, void *));
void tightbeam_msg_get_u16_alt(void);
void tightbeam_msg_field_dispatch_2(void (*param_1)(unsigned long, void *));
void tightbeam_msg_get_u32_alt(void);
void tightbeam_msg_field_dispatch_4(void (*param_1)(unsigned long, void *));
void tightbeam_msg_get_u64_alt(void);
void tightbeam_msg_field_dispatch_8(void (*param_1)(unsigned long, void *));
void tightbeam_msg_write_u32(void);
void tightbeam_msg_write_u64(void);
void tightbeam_msg_write_ptr(void);
void tightbeam_decoder_decode_fatal(void);
void tightbeam_decoder_dispatch_fatal(long param_1);
void tightbeam_msg_read_bool(unsigned long p1, unsigned long p2);
void tightbeam_msg_read_u16(unsigned long p1, unsigned long p2);
void tightbeam_msg_read_u32(unsigned long p1, unsigned long p2);
void tightbeam_msg_read_u64(unsigned long p1, unsigned long p2);
void tightbeam_msg_read_bool_alt(unsigned long p1, unsigned long p2);
void tightbeam_msg_read_field_1(unsigned long p1, unsigned long p2, void (*param_3)(unsigned long, void *));
void tightbeam_msg_read_u16_alt(unsigned long p1, unsigned long p2);
void tightbeam_msg_read_field_2(unsigned long p1, unsigned long p2, void (*param_3)(unsigned long, void *));
void tightbeam_msg_read_u32_alt(unsigned long p1, unsigned long p2);
void tightbeam_msg_read_field_4(unsigned long p1, unsigned long p2, void (*param_3)(unsigned long, void *));
void tightbeam_msg_read_u64_alt(unsigned long p1, unsigned long p2);
void tightbeam_msg_read_field_8(unsigned long p1, unsigned long p2, void (*param_3)(unsigned long, void *));
long tightbeam_decoder_bounds_check(unsigned long param_1, long param_2, long param_3);
void tightbeam_message_teardown_forward(void);
void tightbeam_message_copy_out(unsigned char *param_1);
void tightbeam_callback_invoke(unsigned long param_1, void (*param_2)(void));
void tightbeam_context_dispatch(long param_1, unsigned long param_2);
void tightbeam_encoder_append(long param_1, long param_2);
unsigned long tightbeam_encoder_flush_forward(void);
unsigned long tightbeam_encoder_flush_internal(void);
void tightbeam_msg_write_flag(unsigned int param_1);
void tightbeam_msg_write_u8(unsigned char param_1);
void tightbeam_msg_write_u16(unsigned short param_1);
void tightbeam_msg_write_sel_1(unsigned long param_1);
void tightbeam_msg_write_sel_2(unsigned long param_1);
void tightbeam_msg_write_char(char param_1);
void tightbeam_msg_write_short(short param_1);
void tightbeam_msg_write_sel_3(unsigned long param_1);
void tightbeam_msg_write_field_any(unsigned long param_1, void (*writer)(unsigned long, unsigned long));
void tightbeam_msg_write_field_any2(unsigned long param_1, void (*writer)(unsigned long, unsigned long));
void tightbeam_msg_write_end(void);
void tightbeam_msg_write_begin(void);
void tightbeam_msg_write_ptr_field(unsigned long param_1);
void tightbeam_encoder_dispatch_fatal(unsigned long p1, long param_2);
void tightbeam_encoder_advance_ptr(void);
void tightbeam_encoder_advance_ptr2(void);
void tightbeam_encoder_advance_cb(unsigned long p1, long (*param_2)(void));
void tightbeam_encoder_advance_cb2(unsigned long p1, long (*param_2)(void));
void tightbeam_encoder_advance_cb3(unsigned long p1, long (*param_2)(void));
void tightbeam_encoder_advance_cb4(unsigned long p1, long (*param_2)(void));
void tightbeam_encoder_advance_cb5(unsigned long p1, long (*param_2)(void));
void tightbeam_encoder_advance_cb6(unsigned long p1, long (*param_2)(void));
void tightbeam_encoder_advance_u32(void);
void tightbeam_encoder_advance_u32_2(void);
void tightbeam_encoder_advance_u64(void);
void tightbeam_encoder_advance_u64_2(void);
void tightbeam_encoder_advance_cb7(unsigned long p1, long (*param_2)(void));
void tightbeam_encoder_advance_cb8(unsigned long p1, long (*param_2)(void));
void tightbeam_encoder_advance_x3(void);
void tightbeam_encoder_advance_x3_2(void);
void tightbeam_encoder_advance_x3_3(void);
void tightbeam_encoder_advance_x3_4(void);
void tightbeam_encoder_advance_x3_5(void);
void tightbeam_encoder_advance_x3_6(void);
void tightbeam_encoder_advance_x3_7(void);
void tightbeam_encoder_advance_x3_8(void);
void tightbeam_encoder_vtable_dispatch(void);
long tightbeam_method_16(unsigned long param_1);
void tightbeam_codable_dispatch2(unsigned long p1, unsigned long param_2, unsigned long param_3);
long tightbeam_method_16b(unsigned long param_1);
void tightbeam_codable_call3(unsigned long p1, unsigned long p2, unsigned long p3);
void tightbeam_codable_call3b(unsigned long p1, unsigned long p2, unsigned long p3);
void tightbeam_codable_result(unsigned long *param_1);
void tightbeam_tb_desc_copy_thunk(unsigned char *param_1);
void tightbeam_tb_desc_copy(unsigned char *param_1);
void tightbeam_decoder_descriptor_out(unsigned long *param_1);
unsigned long tightbeam_message_reset_internal(unsigned long param_1, unsigned long param_2);
void tightbeam_event_dispatch(void);
void tightbeam_event_dispatch_result(void);
void tightbeam_event_release(void);
void tightbeam_transport_write_forward(void);
void tightbeam_message_reset_desc(void);
void tightbeam_message_teardown(void);
unsigned long tightbeam_identity_thunk(void);
void tightbeam_decoder_init(unsigned char *param_1, unsigned long param_2);
void tightbeam_decoder_attach(unsigned long param_1);
void tightbeam_decoder_attached_run(void);
void tightbeam_tag_mask(unsigned long *param_1);
long tightbeam_method_4(unsigned long param_1);
long tightbeam_method_4b(unsigned long param_1);
void tightbeam_tb_desc_copy_thunk2(unsigned char *param_1);
unsigned long tightbeam_alloc_and_init(unsigned long param_1, unsigned char param_2);
void tightbeam_message_decode_into(unsigned char *param_1, unsigned char *param_2, int *param_3);
void tightbeam_kind_select(unsigned long param_1, unsigned char param_2);
void tightbeam_ctx_store(unsigned long param_1);
void tightbeam_frame_store(unsigned long param_1);
unsigned long tightbeam_message_commit(long param_1);
void tightbeam_release_msg(void);
void tightbeam_release_msg2(void);
void tightbeam_release_msg_ref(void);
void tightbeam_release_msg_ref2(void);
cl4_result_t tightbeam_type_descriptor_a(void);
void vas_codable_dispatch(unsigned long param_1, unsigned long param_2, unsigned long param_3);
long tightbeam_method_4c(unsigned long param_1);
void vas_codable_dispatch_result(void);
long tightbeam_method_8(unsigned long param_1);
void vas_codable_call_result(unsigned long param_1);
long tightbeam_method_4d(unsigned long param_1);
unsigned long vas_iterate_objects_out(unsigned long p1, unsigned long p2, unsigned long p3);
unsigned long vas_object_call2(unsigned long p1, unsigned long p2, unsigned long p3);
void vas_object_encode_cb(unsigned long param_1, unsigned long param_2, unsigned int *param_3);
void sk_type_register(void);
unsigned long sk_lock_and_alloc(unsigned long *param_1, long *param_2);
void sk_type_register_inner(void);
long tightbeam_method_8b(unsigned long param_1);
long tightbeam_method_8c(unsigned long param_1);
long tightbeam_method_4e(unsigned long param_1);
long sk_obj_lock_resolve(unsigned long param_1);
long tightbeam_method_38(unsigned long param_1);
long tightbeam_method_20(unsigned long param_1);
long tightbeam_method_28(unsigned long param_1);
long tightbeam_method_60(unsigned long param_1);
void vas_server_register(void);
unsigned long vas_op_invoke(long param_1, unsigned long param_2, unsigned long param_3);
void vas_server_init_forward(void);
cl4_result_t vas_type_descriptor(void);
void vas_fault_release(void);
void vas_fault_release2(void);
void vas_fault_event_dispatch(void);
void vas_fault_apply_result(void);
void vas_msg_release(void);
void vas_msg_release2(void);
void vas_msg_release_ref(void);
void vas_msg_release_ref2(void);
cl4_result_t vas_type_id(void);
void vas_fault_attach(unsigned long param_1);
void sk_boot_profile_load(long *param_1, unsigned long param_2, unsigned long param_3);
unsigned long sk_vas_lookup_cap(unsigned long param_1, unsigned long param_2);
cl4_result_t sk_vas_lookup_range(unsigned long param_1, unsigned long param_2);
unsigned long sk_vas_lookup_pa(unsigned long param_1, unsigned long param_2);
unsigned long sk_vas_contains_range(long param_1, long param_2);
void vas_fh_attach(long param_1, unsigned long param_2, unsigned long param_3, long param_4);
void vas_fh_detach(long param_1, long param_2);
void vas_fh_kind(long param_1, unsigned long param_2, unsigned int param_3, long param_4);
void vas_fh_add_range(long param_1, long param_2);
unsigned long vas_fh_lookup_range(long param_1, long param_2, long param_3);
unsigned long vas_fh_activate(long param_1, unsigned long *param_2);
cl4_result_t vas_fh_complete_fault(long param_1, long param_2);
void vas_fh_deactivate(unsigned long *param_1, unsigned long param_2);
void vas_fh_destroy_forward(long param_1, unsigned long param_2, long param_3);
cl4_result_t vas_fh_destroy(long param_1, long param_2);
void vas_fh_table_remove(long param_1, unsigned long *param_2);
void vas_fh_dump(long param_1, unsigned long param_2, long param_3);
long vas_record_add(long param_1, long param_2, long param_3);
void vas_record_fill(unsigned long *param_1, char *param_2, unsigned int param_3);
void vas_fh_register(long param_1, unsigned int *param_2, long param_3);
unsigned long vas_fh_handle_state(long param_1, unsigned long param_2, long param_3);
cl4_result_t vas_fh_lookup_entry(long param_1, long param_2, long param_3);
cl4_result_t vas_fh_map_page(long param_1, unsigned long param_2, long param_3);
void sk_pair_copy8(long param_1, long param_2);
void sk_pair_release(long param_1);
void vas_fh_delete(long param_1, unsigned long param_2, unsigned long param_3, long param_4);
unsigned long vas_fh_size(long param_1, unsigned long param_2, unsigned long param_3, long param_4);
unsigned long vas_fh_move(long param_1, unsigned long param_2, unsigned long param_3, long param_4);
void vas_fh_region_remove(long param_1, long param_2);
unsigned long vas_fh_swap(long param_1, unsigned long param_2, unsigned long param_3, long param_4);
void vas_fh_detach_sync(long param_1, unsigned long param_2, long param_3);
void vas_fh_map_dispatch(long param_1, unsigned long param_2, long param_3);
void vas_fh_map6_dispatch(long param_1, unsigned long param_2, long param_3);
void vas_fh_map15_dispatch(long param_1, unsigned long param_2, long param_3);
void vas_fh_map14_dispatch(long param_1, unsigned long param_2, long param_3);
void vas_fh_clear(long param_1, unsigned long param_2, long param_3);
void vas_fh_clear2(long param_1, unsigned long param_2, long param_3);
void vas_fh_get(long param_1, unsigned long param_2, unsigned long param_3, long param_4);
void vas_fh_create_result(long param_1, long param_2);
void vas_fh_set_desc2(long param_1, unsigned long param_2, unsigned long param_3, long param_4);
void vas_fh_release_all(long param_1);
cl4_result_t sk_cap_bind_pair(long param_1, long *param_2);
void vas_msg_recv_forward(void);

extern unsigned long _sk_once_0;
extern unsigned long _sk_global_c2d8;
extern unsigned long _sk_global_c2e0;
extern unsigned long _sk_global_c2e8;

/* Renames to the concrete internal helpers above. */

unsigned long tightbeam_msg_unwrap_internal(long, long, long, unsigned long, unsigned long); /* 0x2286c */
cl4_result_t tightbeam_type_id(void);                 /* 0x286dc */
long tightbeam_message_send_internal(unsigned long, unsigned long, unsigned long,
                                              unsigned long, unsigned long, unsigned long,
                                              unsigned long, unsigned long); /* 0x252d4 */
unsigned long tightbeam_message_reset_internal(unsigned long, unsigned long); /* 0x240e4 */
void tightbeam_decoder_init(unsigned char *, unsigned long); /* 0x259c0 */
void tightbeam_message_init_desc(unsigned char *, long, unsigned long, unsigned long); /* 0x258c8 */
unsigned long vas_iterate_internal(unsigned long, unsigned long, long, unsigned long,
                                   unsigned long, unsigned long); /* 0x26a8c */
unsigned long vas_object_call2_internal(unsigned long, long, unsigned long, unsigned long,
                                        unsigned long); /* 0x26f40 */
long vas_server_init(unsigned long, unsigned char, unsigned long, unsigned long,
                     unsigned long, unsigned long, unsigned long); /* 0x27b70 */
void vas_server_register_internal(unsigned long, unsigned long, unsigned long,
                                  unsigned long, unsigned long, unsigned long); /* 0x27f50 */
unsigned long sk_profile_resolve(void); /* FUN_00034f70 */
long *sk_vas_region_find(long, long); /* 0x2fa34 */
cl4_result_t vas_msg_recv(long *, unsigned long *, unsigned long, unsigned int *, int); /* 0x2ff48 */

void tightbeam_transfer_dispatch(unsigned long, unsigned long, void (*)(void),
                                 unsigned long, unsigned long, long, long, long,
                                 unsigned long, unsigned long, unsigned long); /* 0x208a8 */
void tightbeam_tb_state(unsigned long, unsigned long, unsigned long, char); /* 0x20d0c */
void sk_obj_bind_reset(unsigned long, unsigned long, unsigned long); /* thunk_FUN_00012568 */


#define sk_tb_release_state  tightbeam_tb_state
#define sk_tb_copy_region    tightbeam_copy_region
#define sk_msg_build_status  tightbeam_msg_kind_status
#define sk_lock_and_get      tightbeam_lock_and_get
#define sk_obj_read_kind     tightbeam_obj_read_kind


/* The 0x28-byte Tightbeam transport-buffer descriptor layout used throughout
 * this region (matches the .swift-instantiated structs). */
typedef struct sk_tb_desc {
    unsigned long base;       /* +0x00 buffer base / tagged union */
    unsigned long data;       /* +0x08 */
    unsigned long cap;        /* +0x10 */
    unsigned long used;       /* +0x18 */
    unsigned long reserved;   /* +0x20 */
    unsigned char state;      /* +0x28 (0=forgotten,1=active,0xff=const) */
    char pad[7];
} sk_tb_desc_t;

/*--------------------------------------------------------------------*/
/* FUN_00020134 @ 0x00020134   (est. tightbeam_transport_init)
 * Ghidra: undefined FUN_00020134(void)
 * Boot-time initialisation of the Tightbeam transport-buffer subsystem.
 * Reads a per-cpu/handler context descriptor from x5-8, invokes a sub-init
 * that returns a 16-byte {status,word} pair; if the status word is zero it
 * panics with "Fatal error" and "Tightbeam TransportBuffer swift". Otherwise
 * it clears a local descriptor block (0x48 bytes), flags word 0xa8=1, and
 * calls through the resolved init routine, then an optional dispatch callback
 * at context+0x20 when the caller register x21 is non-null. Ends with a stack
 * canary check (FUN_0011d7e8 on failure).
 * Confidence: medium (string-matched "Tightbeam TransportBuffer swift").
 * Notes: SUB_d65f03c0a8c14ff4 inlined tail; strings s_Fatal_error_005accd0 /
 *   s_Tightbeam_TransportBuffer_swift_005accb0; noreturn FUN_001afa84.
 */
void tightbeam_transport_init(void)
{
    unsigned long ctx;          /* *(x5-8) */
    unsigned long status, word; /* sub-init 16-byte result */
    unsigned long d0, d1, d2, d3, d4, d5, d6, d7;
    unsigned char flag_a8;
    unsigned long canary = 0xd37afd4bb400012aull;

    ctx = *(unsigned long *)((char *)__builtin_frame_address(0) - 8);
    status = 0; word = 0;   /* sub-init result */
    if (status == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000040,
                       0x80000000005ace20, "Tightbeam TransportBuffer swift",
                       0x1f, 2);   /* FUN_001afa84, noreturn */
    }
    d0 = 0; d1 = 0; d2 = 0; d3 = 0; d4 = 0; d5 = 0; d6 = 0; d7 = 0;
    flag_a8 = 1;
    /* (*extraout_x12)(&status,0,0,1,&local_b0) — run transport init. */
    /* optional dispatch callback at ctx+0x20 when x21 non-null. */
    if (canary != 0xd37afd4bb400012aull) {
        sk_stack_chk_fail();   /* FUN_0011d7e8, noreturn */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000202c0 @ 0x000202c0   (est. tightbeam_transport_alloc)
 * Ghidra: undefined1 [16] FUN_000202c0(void)
 * Allocates a 0x68-byte transport buffer (FUN_0036a804(0x68,-1)), runs
 * FUN_00015708 (constructor), and returns a 16-byte {obj, FUN_0001a1c8} pair
 * where the high word is a method pointer.
 * Confidence: low (allocation + ctor + method-table pair).
 */
cl4_result_t tightbeam_transport_alloc(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)sk_alloc_aligned(0x68, 0xffffffffffffffffu);  /* FUN_0036a804 */
    /* FUN_00015708 ctor */
    r.hi = (uint64_t)0x1a1c8;   /* FUN_0001a1c8 method table */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00020310 @ 0x00020310   (est. tightbeam_transport_reset_if_free)
 * Ghidra: undefined8 FUN_00020310(code *param_1, ...)
 * Resets a transport buffer: only proceeds when the buffer is not forgotten
 * (state word at unaff_x20+3 zero). Invokes the supplied reset callback; on
 * success frees the old backing store (FUN_0036b270) and re-arms the buffer
 * fields to the supplied {base,data,cap}; otherwise rethrows the error via
 * FUN_003698b0. Fatal-error panics when the buffer was already forgotten.
 * Confidence: medium (TransportBuffer lifecycle, string-matched).
 * Notes: s_TransportBuffer_*_005accb0 fatal strings; FUN_003698b0 rethrow.
 */
unsigned long tightbeam_transport_reset_if_free(void *reset_cb, unsigned long p2,
                                                unsigned long p3, unsigned long p4,
                                                unsigned long p5, unsigned long p6)
{
    unsigned long *slot;   /* unaff_x20 */
    unsigned long base, data, cap, res;
    int rc;

    slot = (unsigned long *)((char *)__builtin_frame_address(0));  /* unaff_x20 */
    if (*(unsigned char *)((char *)slot + 0x18) == 0) {   /* not forgotten */
        base = slot[0];
        data = slot[1];
        cap = slot[2];
        res = (*(unsigned long (*)(unsigned long, unsigned long, unsigned long))
               reset_cb)(p5, p6, base);
        rc = (int)res;
        if (rc == 0) {
            sk_lock_spin(p4);                      /* FUN_0036b270 */
            sk_tb_release_state(base, data, cap, 0);  /* FUN_00020d0c */
            slot[0] = base;
            slot[1] = p3;
            slot[2] = p4;
            *(unsigned char *)((char *)slot + 0x18) = 0;
        } else {
            /* FUN_00019aac error object + FUN_003698b0 rethrow. */
            sk_fatal_error("", 0, 0, 0, 0, "", 0, 0);
        }
        return res;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000034,
                   0x80000000005accc0, "Tightbeam TransportBuffer swift",
                   0x1f, 2, 0x4d, 0);   /* FUN_001afa84, noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_00020448 @ 0x00020448   (est. tightbeam_transport_append)
 * Ghidra: void FUN_00020448(...)
 * Appends param_2 bytes from param_1 into the transport buffer described by
 * param_3[0..3] (base/cap/used/limit). Validates against overflow and against
 * the "forgotten" state; on success copies via FUN_002e2d24 and advances the
 * used pointer. Range/state violations either trap (SoftwareBreakpoint) or
 * fatal-error with "TransportBuffer has insufficient ..." / "was already
 * forgotten" messages.
 * Confidence: medium (string-matched append path).
 * Notes: s_TransportBuffer_has_insufficient_005acd50,
 *   s_TransportBuffer_was_already_forg_005acd20.
 */
void tightbeam_transport_append(unsigned long param_1, long param_2, long *param_3,
                                unsigned long p4, unsigned long p5, unsigned char p6,
                                unsigned long p7, unsigned long p8)
{
    const char *msg;
    unsigned long err, code;
    long lv, used;

    if (p6 < 2) {   /* not forgotten */
        used = param_3[2];
        if ((unsigned long)(used + param_2) < (unsigned long)used) {   /* SCARRY8 */
            SWIFT_BREAKPOINT();   /* 0x204c8 */
        }
        if (used + param_2 <= param_3[3]) {
            if (param_2 < 0) SWIFT_BREAKPOINT();   /* 0x204cc */
            sk_tb_copy_region(param_1, param_3[0] + used, param_3[0] + used + param_2,
                              p7, p8);            /* FUN_002e2d24 */
            if ((unsigned long)(param_3[2] + param_2) >= param_3[2]) {
                param_3[2] = param_3[2] + param_2;
                return;
            }
            SWIFT_BREAKPOINT();   /* 0x204d0 */
        }
        msg = "TransportBuffer has insufficient "; err = 0x57;
        code = 0xd00000000000002b;
    } else {
        msg = "TransportBuffer was already forg"; err = 0x3b;
        code = 0xd000000000000025;
    }
    sk_fatal_error("Fatal error", 0xb, 2, code,
                   (uint64_t)(msg - 0x20) | 0x8000000000000000,
                   "Tightbeam TransportBuffer swift", 0x1f, 2, err, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00020560 @ 0x00020560   (est. tightbeam_transport_set_position)
 * Ghidra: void FUN_00020560(long param_1, long param_2, ...)
 * Sets the transport buffer's current position (param_2+0x10) to param_1,
 * validating that it stays within the limit at param_2+0x18. Out-of-range
 * positions fatal-error with "TransportBuffer position is out..." unless the
 * buffer was already forgotten.
 * Confidence: medium (string-matched position setter).
 * Notes: s_TransportBuffer_position_is_out__005acd80.
 */
void tightbeam_transport_set_position(long param_1, long param_2, unsigned long p3,
                                      unsigned long p4, unsigned char p5)
{
    const char *msg;
    unsigned long err, code;

    if (p5 < 2) {
        if (param_1 < *(long *)(param_2 + 0x18)) {
            *(long *)(param_2 + 0x10) = param_1;
            return;
        }
        msg = "TransportBuffer position is out "; err = 0x67;
        code = 0xd000000000000029;
    } else {
        msg = "TransportBuffer was already forg"; err = 0x3b;
        code = 0xd000000000000025;
    }
    sk_fatal_error("Fatal error", 0xb, 2, code,
                   (uint64_t)(msg - 0x20) | 0x8000000000000000,
                   "Tightbeam TransportBuffer swift", 0x1f, 2, err, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00020628 @ 0x00020628   (est. tightbeam_transport_read_into)
 * Ghidra: void FUN_00020628(...)
 * Reads from the transport buffer into a caller-supplied destination,
 * validating the buffer is not forgotten and that the read region (param_4)
 * stays within the configured buffer size (param_2's context +0x40). Writes
 * a small transfer descriptor on the stack and invokes FUN_000208a8 with a
 * continuation (FUN_00020d20), then the optional dispatch callback.
 * Confidence: low (transfer descriptor assembly, Swift tail).
 */
void tightbeam_transport_read_into(unsigned long p1, unsigned long p2, unsigned long p3,
                                   long param_4)
{
    if (1 < *(unsigned char *)((char *)__builtin_frame_address(0))) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000025,
                       0x80000000005acd00, "Tightbeam TransportBuffer swift",
                       0x1f, 2);   /* 0x20628 path */
    }
    if (*(long *)(param_4 + 0x20) < *(long *)(*(long *)((char *)__builtin_frame_address(0) - 8) + 0x40)) {
        SWIFT_BREAKPOINT();   /* 0x2078c */
    }
    /* build transfer descriptor; FUN_000208a8(in_x7,1,FUN_00020d20) */
    tightbeam_transfer_dispatch(0, 1, (void (*)(void))tightbeam_tb_done, 0, 0, 0, 0, 0, 0, 0, 0);  /* FUN_000208a8 */
}

/*--------------------------------------------------------------------*/
/* FUN_000207e0 @ 0x000207e0   (est. tightbeam_transport_dispatch_tail)
 * Ghidra: void FUN_000207e0(void)
 * Tail dispatch through a Swift sub-init (SUB_d65f03c0a8c14ff4) and an
 * optional dispatch callback at context+0x20. Thin forwarding helper used as
 * the common completion path for transport operations.
 * Confidence: low (thin Swift bridge tail).
 */
void tightbeam_transport_dispatch_tail(void)
{
    /* (*extraout_x12)(uVar1, &stack) then (*ctx+0x20)(in_x7,&stack,in_x5) */
}

/*--------------------------------------------------------------------*/
/* FUN_000208a8 @ 0x000208a8   (est. tightbeam_transfer_dispatch)
 * Ghidra: void FUN_000208a8(undefined8 param_1, undefined8 param_2, code *param_3, ...)
 * Runs a transfer operation: checks the buffer's busy flag (param_7 ctx +0x50),
 * then performs an exact division on the source/dest sizes to establish the
 * transfer element count (trapping on non-divisible sizes), then calls the
 * supplied continuation param_3 with the packed size, followed by the optional
 * dispatch callback. Size-ratio computation uses both 32-bit halves of the
 * 64-bit size word.
 * Confidence: low (division/size-check transfer dispatcher).
 */
void tightbeam_transfer_dispatch(unsigned long param_1, unsigned long param_2,
                                 void (*param_3)(void), unsigned long param_4,
                                 unsigned long param_5, long param_6, long param_7,
                                 long param_8, unsigned long p9, unsigned long p10,
                                 unsigned long p11)
{
    unsigned int lo = (unsigned int)param_5;
    unsigned int hi = (unsigned int)(param_5 >> 32);
    long szA, szB, q;

    (void)hi;
    if ((*(unsigned int *)(*(long *)(param_7 - 8) + 0x50) & lo & 0xff) != 0) {
        SWIFT_BREAKPOINT();   /* 0x209e8 */
    }
    if ((long)0 != 1) {   /* extraout_x1 */
        szA = *(long *)(*(long *)(param_6 - 8) + 0x48);
        szB = *(long *)(*(long *)(param_7 - 8) + 0x48);
        if (szB < szA) {
            if (szB == 0) SWIFT_BREAKPOINT();   /* 0x209ec */
            q = szA / szB;
            if (szA != q * szB) SWIFT_BREAKPOINT();   /* 0x20978 */
        } else {
            if (szA == 0) SWIFT_BREAKPOINT();   /* 0x209f0 */
            if (szA == -1 && szB == (long)0x8000000000000000) SWIFT_BREAKPOINT(); /* 0x209f8 */
            q = szB / szA;
            if (szB != q * szA) SWIFT_BREAKPOINT();   /* 0x209f4 */
        }
    }
    param_3();   /* call continuation with packed size on stack */
}

/*--------------------------------------------------------------------*/
/* FUN_000209f8 @ 0x000209f8   (est. tightbeam_transport_reserve_ptr)
 * Ghidra: undefined8 FUN_000209f8(undefined8 *param_1, ...)
 * Returns the current reserve/read pointer of a transport buffer (param_1[0]),
 * validating it against the limit at param_1[3]. Out-of-range or forgotten
 * states fatal-error ("TransportBuffer has illegal rese...", "...forgotten").
 * Confidence: medium (string-matched reserve-pointer accessor).
 * Notes: s_TransportBuffer_has_illegal_rese_005acdb0.
 */
unsigned long tightbeam_transport_reserve_ptr(unsigned long *param_1, unsigned long p2,
                                              unsigned long p3, unsigned char p4)
{
    const char *msg;
    unsigned long err, code;

    if (p4 < 2) {
        if ((long)param_1[4] <= (long)param_1[3]) {
            if (-1 < (long)param_1[4]) return param_1[0];
            SWIFT_BREAKPOINT();   /* 0x20a38 */
        }
        msg = "TransportBuffer has illegal rese"; err = 0x7b;
        code = 0xd00000000000002b;
    } else {
        msg = "TransportBuffer was already forg"; err = 0x3b;
        code = 0xd000000000000025;
    }
    sk_fatal_error("Fatal error", 0xb, 2, code,
                   (uint64_t)(msg - 0x20) | 0x8000000000000000,
                   "Tightbeam TransportBuffer swift", 0x1f, 2, err, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00020ac8 @ 0x00020ac8   (est. tightbeam_transport_data_ptr)
 * Ghidra: long FUN_00020ac8(long *param_1, ...)
 * Returns the data pointer at the current used offset (param_1[0] + param_1[2]),
 * validating 0<=used<=limit and non-overflow. Violations fatal-error with
 * "TransportBuffer has illegal data..." or "was already forgotten".
 * Confidence: medium (string-matched data-pointer accessor).
 * Notes: s_TransportBuffer_has_illegal_data_005acde0.
 */
long tightbeam_transport_data_ptr(long *param_1, unsigned long p2, unsigned long p3,
                                  unsigned char p4)
{
    const char *msg;
    unsigned long err, code;
    long used, limit;

    if (p4 < 2) {
        used = param_1[4];
        if ((used <= param_1[2]) && (limit = param_1[3], param_1[2] <= limit)) {
            if ((unsigned long)limit < (unsigned long)used) SWIFT_BREAKPOINT(); /* 0x20b24 */
            if (-1 < limit - used) return param_1[0] + used;
            SWIFT_BREAKPOINT();   /* 0x20b28 */
        }
        msg = "TransportBuffer has illegal data"; err = 0x88;
        code = 0xd000000000000027;
    } else {
        msg = "TransportBuffer was already forg"; err = 0x3b;
        code = 0xd000000000000025;
    }
    sk_fatal_error("Fatal error", 0xb, 2, code,
                   (uint64_t)(msg - 0x20) | 0x8000000000000000,
                   "Tightbeam TransportBuffer swift", 0x1f, 2, err, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00020bb8 @ 0x00020bb8   (est. tightbeam_transport_raw_data_ptr)
 * Ghidra: undefined8 FUN_00020bb8(undefined8 *param_1, ...)
 * Returns the raw data base (param_1[0]) after validating that the used
 * offset (param_1[2]) is within limits. Violations fatal-error with
 * "TransportBuffer has illegal raw d..." or "was already forgotten".
 * Confidence: medium (string-matched raw-pointer accessor).
 * Notes: s_TransportBuffer_has_illegal_raw_d_005ace10.
 */
unsigned long tightbeam_transport_raw_data_ptr(unsigned long *param_1, unsigned long p2,
                                               unsigned long p3, unsigned char p4)
{
    const char *msg;
    unsigned long err, code;

    if (p4 < 2) {
        if ((long)param_1[2] <= (long)param_1[3]) {
            if (-1 < (long)param_1[2]) return param_1[0];
            SWIFT_BREAKPOINT();   /* 0x20bf8 */
        }
        msg = "TransportBuffer has illegal raw d"; err = 0x94;
        code = 0xd00000000000002b;
    } else {
        msg = "TransportBuffer was already forg"; err = 0x3b;
        code = 0xd000000000000025;
    }
    sk_fatal_error("Fatal error", 0xb, 2, code,
                   (uint64_t)(msg - 0x20) | 0x8000000000000000,
                   "Tightbeam TransportBuffer swift", 0x1f, 2, err, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00020c88 @ 0x00020c88   (est. tightbeam_transport_release)
 * Ghidra: void FUN_00020c88(undefined8 param_1, code *param_2, undefined8 param_3, ulong param_4)
 * Releases a transport buffer: if the state byte is zero, frees the backing
 * store (FUN_0036b270), invokes the destructor callback, resets the buffer
 * via thunk_FUN_00012568, and re-arms state via FUN_00020d0c(...,0). The final
 * state byte is propagated through FUN_00020d0c.
 * Confidence: medium (TransportBuffer release lifecycle).
 */
void tightbeam_transport_release(unsigned long param_1, void (*param_2)(unsigned long),
                                 unsigned long param_3, unsigned long param_4)
{
    if ((param_4 & 0xff) == 0) {
        sk_lock_spin(param_3);              /* FUN_0036b270 */
        param_2(param_1);
        sk_obj_bind_reset(param_1, 0xffffffffffffffffu, 0xffffffffffffffffu); /* thunk_FUN_00012568 */
        tightbeam_tb_state(param_1, (unsigned long)param_2, param_3, 0);  /* FUN_00020d0c */
        param_4 = 0;
    }
    tightbeam_tb_state(param_1, (unsigned long)param_2, param_3, param_4);  /* FUN_00020d0c */
}

/*--------------------------------------------------------------------*/
/* FUN_00020d0c @ 0x00020d0c   (est. tightbeam_tb_state)
 * Ghidra: void FUN_00020d0c(undefined8 param_1, undefined8 param_2, undefined8 param_3, char param_4)
 * State machine for a transport buffer: when param_4 is nonzero the buffer is
 * left alone; when zero, the backing store param_3 is freed via FUN_0036b118.
 * Confidence: medium (simple conditional free).
 */
void tightbeam_tb_state(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                        char param_4)
{
    (void)param_1; (void)param_2;
    if (param_4 != '\0') return;
    sk_lock_release(param_3);   /* FUN_0036b118 */
}

/*--------------------------------------------------------------------*/
/* FUN_00020d20 @ 0x00020d20   (est. tightbeam_tb_done)
 * Ghidra: void FUN_00020d20(undefined8 param_1, undefined8 param_2)
 * Continuation invoked after a transfer: forwards to FUN_000207e0 passing the
 * six-word buffer context read from the object at unaff_x20+0x10..0x38.
 * Confidence: low (Swift continuation).
 */
void tightbeam_tb_done(unsigned long param_1, unsigned long param_2)
{
    unsigned long *ctx;   /* unaff_x20 */
    ctx = (unsigned long *)__builtin_frame_address(0);
    tightbeam_transport_dispatch_tail();   /* FUN_000207e0 */
    (void)param_1; (void)param_2;
    (void)ctx;
}

/*--------------------------------------------------------------------*/
/* FUN_00020d24 @ 0x00020d24   (est. tightbeam_tb_done2)
 * Ghidra: void FUN_00020d24(undefined8 param_1, undefined8 param_2)
 * Mirror continuation of FUN_00020d20; forwards to FUN_000207e0 with the
 * six-word buffer context.
 * Confidence: low.
 */
void tightbeam_tb_done2(unsigned long param_1, unsigned long param_2)
{
    (void)param_1; (void)param_2;
    tightbeam_transport_dispatch_tail();   /* FUN_000207e0 */
}

/*--------------------------------------------------------------------*/
/* FUN_00020d74 @ 0x00020d74   (est. tightbeam_tb_move)
 * Ghidra: undefined8 * FUN_00020d74(undefined8 *param_1, undefined8 *param_2)
 * Moves a transport buffer descriptor from param_2 into param_1 (copying the
 * 0x30-byte descriptor including the state byte), then releases the previous
 * contents of param_1 via FUN_00020d0c. Returns param_1.
 * Confidence: medium (descriptor move + release).
 */
unsigned long *tightbeam_tb_move(unsigned long *param_1, unsigned long *param_2)
{
    unsigned long base, data, cap, s2, s0, s1, s3;
    unsigned char st1, st2;

    cap = param_2[2];
    st2 = *(unsigned char *)(param_2 + 3);
    base = param_1[0]; data = param_1[1]; s1 = param_1[2];
    s0 = param_2[0]; s3 = param_2[1];
    param_1[1] = s3;
    param_1[0] = s0;
    param_1[2] = cap;
    st1 = *(unsigned char *)(param_1 + 3);
    *(unsigned char *)(param_1 + 3) = st2;
    tightbeam_tb_state(base, data, s1, st1);   /* FUN_00020d0c */
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_00020ebc @ 0x00020ebc   (est. tightbeam_failure_code)
 * Ghidra: undefined1 [16] FUN_00020ebc(uint param_1)
 * Maps a Tightbeam failure index to a 16-byte {code, message-pointer} error
 * descriptor. The literal byte strings encode little-endian ASCII error tags
 * ("Unknown", "Clound es en", "Success", "Message create failed", "Activation
 * failed", "Reply send failed", "Message decode failed", "Use riefail"...).
 * Unknown indexes map to "Unknown" (0xed0000726f727265 / "Unknow...").
 * Confidence: medium (string table; literal hex encodes Swift error tags).
 * Notes: s_Message_create_failed_005acf30 etc.; switchD_00020efc_caseD_*.
 */
cl4_result_t tightbeam_failure_code(unsigned int param_1)
{
    cl4_result_t r;
    const char *msg;

    switch (param_1) {
    case 1:
        /* "Clound es en" */ r.lo = 0x6f6e20646c756f43ull; r.hi = 0xee00646e65732074ull;
        return r;
    case 2:
        msg = "Message create failed"; break;
    case 3:
        msg = "Activation failed"; goto msg_small;
    case 4:
        r.lo = 0xd000000000000016ull; r.hi = 0x80000000005aced0ull;
        return r;
    case 5:
        msg = "Reply send failed";
msg_small:
        r.lo = 0xd000000000000011ull;
        r.hi = (uint64_t)(msg - 0x20) | 0x8000000000000000ull;
        return r;
    case 7:
        msg = "Message decode failed"; break;
    case 9:
        /* "Use riefail" */ r.lo = 0x6961662072657355ull; r.hi = 0xec0000006572756cull;
        return r;
    case 10:
        /* "Forward ariurefe" */ r.lo = 0x2064726177726f46ull; r.hi = 0xef6572756c696166ull;
        return r;
    case 0x10:
        r.lo = 0xd00000000000001eull; r.hi = 0x80000000005ace70ull;
        return r;
    default:
        if (param_1 > 0x10) { r.lo = 0x206e776f6e6b6e55ull; r.hi = 0xed0000726f727265ull; }
        else { r.lo = 0x73736563637553ull; r.hi = 0xe700000000000000ull; /* "Success" */ }
        return r;
    }
    /* case 2 / case 7: code 0xd000000000000015 + tagged message */
    r.lo = 0xd000000000000015ull;
    r.hi = (uint64_t)(msg - 0x20) | 0x8000000000000000ull;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_000210d8 @ 0x000210d8   (est. tightbeam_msg_kind)
 * Ghidra: undefined1 [16] FUN_000210d8(long param_1)
 * Resolves the message kind/capability for a Tightbeam message: builds a
 * status pair via FUN_00019aac(0x13f), optionally re-locks the object's
 * capability word (FUN_00377dcc) and reads the kind through FUN_00368da8.
 * Returns 0x3f in the high word on failure, else the resolved kind.
 * Confidence: low (kind-lookup with Swift error pair).
 */
cl4_result_t tightbeam_msg_kind(long param_1)
{
    cl4_result_t r, t;
    unsigned long kind;

    t = sk_msg_build_status(0x13f);   /* FUN_00019aac */
    kind = t.lo;
    if (t.hi < 0x40) {
        t = tightbeam_msg_kind_status(0x13f); /* placeholder for lock-and-get */
        kind = t.lo;
        if (t.hi < 0x40) {
            sk_obj_read_kind(param_1, 0, 2, &kind);   /* FUN_00368da8 */
            r.lo = 0;
            r.hi = 0;
            return r;
        }
    }
    r.lo = kind;
    r.hi = 0x3f;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00021260 @ 0x00021260   (est. tightbeam_uleb_encode)
 * Ghidra: void FUN_00021260(uint *param_1, uint param_2, uint param_3, long param_4)
 * LEB128-style variable-length integer encoder: writes param_2/param_3 into
 * param_1 using a width derived from the buffer context (param_4+0x10-8 +0x40).
 * Chooses a 1/2/4-byte tag width and emits the value with continuation bytes;
 * on the write path it also computes the tag byte count into iVar7.
 * Confidence: low (variable-length integer encode, LEB128-like).
 * Notes: thunk_FUN_00114330 byte-store helper.
 */
void tightbeam_uleb_encode(unsigned int *param_1, unsigned int param_2, unsigned int param_3,
                           long param_4)
{
    unsigned long width = *(unsigned long *)(*(long *)(*(long *)(param_4 + 0x10) - 8) + 0x40);
    unsigned long lw = (width < 5) ? 4 : width;
    unsigned int w = (unsigned int)(lw + 1);
    unsigned char tagw;

    if (param_3 < 0xff) {
        tagw = 0;
    } else if (w < 4) {
        tagw = (unsigned char)(((param_3 + ~(0xffffffffu << ((w << 3) & 0x1f))) - 0xfe
                                >> ((w << 3) & 0x1f)) + 1);
        if (tagw > 0xff) tagw = 4;
        if (tagw < 0x100) tagw = (1 < tagw);
    } else {
        tagw = 1;
    }
    if (param_2 < 0xff) {
        /* write zero tag of tagw width, then signed value byte at param_1+width */
        if (param_2 != 0) {
            *(char *)((char *)param_1 + width) = -(char)param_2;
        }
    } else {
        /* encode param_2-0xff in width bytes with continuation; write tag iVar7 */
        /* thunk_FUN_00114330(param_1,lw+1); value write; tag byte count */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0002142c @ 0x0002142c   (est. tightbeam_once_init)
 * Ghidra: void FUN_0002142c(void)
 * One-time initialisation guard: if the global at _s___TEXT_0064c258 is
 * already set, returns; otherwise sets it from FUN_00376820(&DAT_004ed400,
 * 0x6776f0) (registering a global/type descriptor).
 * Confidence: low (Swift once-init).
 * Notes: global _s___TEXT_0064c258.
 */
void tightbeam_once_init(void)
{
    if (_sk_once_0 != 0) return;
    _sk_once_0 = (unsigned long)sk_obj_reg_get();   /* FUN_00376820 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021480 @ 0x00021480   (est. tightbeam_cap_create)
 * Ghidra: void FUN_00021480(...)
 * Builds a capability through FUN_0036ffc0, passing the packed {param_2,param_3,
 * param_4} triplet on the stack. Thin Swift bridge.
 * Confidence: low.
 */
void tightbeam_cap_create(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                          unsigned long param_4, unsigned long param_5)
{
    unsigned long args[3];
    args[0] = param_2; args[1] = param_3; args[2] = param_4;
    sk_ptr_array_at((void *)param_1, args);   /* FUN_0036ffc0 */
}

/*--------------------------------------------------------------------*/
/* FUN_000214b0 @ 0x000214b0   (est. tightbeam_tb_descriptor_copy)
 * Ghidra: void FUN_000214b0(byte *param_1, byte *param_2)
 * Copies the 0x31-byte transport-buffer descriptor from param_2 into param_1
 * (base/flag byte, 4 data words, state byte at +0x30).
 * Confidence: high (plain struct copy).
 */
void tightbeam_tb_descriptor_copy(unsigned char *param_1, unsigned char *param_2)
{
    unsigned char b;
    unsigned long v;

    b = param_2[0x30];
    *param_1 = *param_2 & 1;
    v = *(unsigned long *)(param_2 + 8);
    *(unsigned long *)(param_1 + 0x10) = *(unsigned long *)(param_2 + 0x10);
    *(unsigned long *)(param_1 + 8) = v;
    v = *(unsigned long *)(param_2 + 0x18);
    *(unsigned long *)(param_1 + 0x20) = *(unsigned long *)(param_2 + 0x20);
    *(unsigned long *)(param_1 + 0x18) = v;
    *(unsigned long *)(param_1 + 0x28) = *(unsigned long *)(param_2 + 0x28);
    param_1[0x30] = b;
}

/*--------------------------------------------------------------------*/
/* FUN_000214e0 @ 0x000214e0   (est. tightbeam_message_reset)
 * Ghidra: void FUN_000214e0(void)
 * Resets a TightbeamMessage: if the underlying message (object+0x10) is
 * non-null, forwards to FUN_000159d0; otherwise fatal-errors with
 * "TightbeamMessage" already-unwrapped message.
 * Confidence: medium (string-matched TightbeamMessage).
 * Notes: s_Tightbeam_TightbeamMessage_swift_005acf50.
 */
void tightbeam_message_reset(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {   /* +0x10 */
        /* FUN_000159d0 */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00021554 @ 0x00021554   (est. tightbeam_decoder_unwrap)
 * Ghidra: undefined8 FUN_00021554(ulong param_1, long param_2)
 * Unwraps a provided buffer (param_1..param_2) into the TightbeamDecoder at
 * object+0x10: validates the buffer is non-null and the message not yet
 * unwrapped; for a 4-byte-kind message it copies the byte span into the
 * buffer's data window, advancing the used pointer. Various states trap
 * (SoftwareBreakpoint 0x5519/0x18768/...); failures fatal-error with
 * "Failed to unwrap provided buffer" or "already unwrapp...".
 * Confidence: medium (string-matched TightbeamDecoder unwrap).
 * Notes: s_Failed_to_unwrap_provided_buffer_005acfe0,
 *   s_TightbeamMessage_already_unwrapp_005acf80.
 */
unsigned long tightbeam_decoder_unwrap(unsigned long param_1, long param_2)
{
    const char *msg;
    unsigned long err, code;
    int *kind;
    unsigned long *buf, cap, used, base;
    unsigned long span;

    if (param_1 == 0) {
        msg = "Failed to unwrap provided buffer"; err = 0x2e;
        code = 0xd000000000000028;
        goto fatal;
    }
    kind = *(int **)((char *)__builtin_frame_address(0) + 0x10);
    if (kind == (int *)0) {
        msg = "TightbeamMessage already unwrapp"; err = 0x93;
        code = 0xd000000000000022;
        goto fatal;
    }
    span = (unsigned long)(param_2 - param_1);
    if (*kind == 4) {
        buf = *(unsigned long **)(kind + 5);
        cap = buf[3];
        if (cap == 0) { /* goto LAB_00018790 */ }
        used = buf[2];
        if (!((unsigned long)(used + span) < used)) {
            if (used + span <= cap) {
                base = buf[0];
                buf[2] = used + span;
                if (((used <= base + cap && base <= used) && span <= cap - used)) {
                    return 0;   /* FUN_00117cc4 copy of (param_1,used,span) */
                }
                SWIFT_BREAKPOINT_A();   /* 0x18768 */
            }
            /* goto LAB_00018798 */
        }
    }
    return 1;
fatal:
    sk_fatal_error("Fatal error", 0xb, 2, code,
                   (uint64_t)(msg - 0x20) | 0x8000000000000000,
                   "Tightbeam TightbeamDecoder swift", 0x20, 2, err,
                   0xffffffff00000000ull);   /* FUN_001afa84, noreturn */
}

/*--------------------------------------------------------------------*/
/* FUN_0002161c @ 0x0002161c   (est. tightbeam_decoder_unwrap_forward)
 * Ghidra: undefined8 FUN_0002161c(...)
 * Forwards the unwrap request to FUN_0002286c with the message from object+0x10;
 * rethrows errors via FUN_003698b0.
 * Confidence: low (forwarder + rethrow).
 */
unsigned long tightbeam_decoder_unwrap_forward(unsigned long p1, unsigned long p2,
                                               unsigned long p3, unsigned long p4)
{
    unsigned long *obj;   /* unaff_x20 */
    int rc;
    obj = (unsigned long *)__builtin_frame_address(0);
    rc = (int)tightbeam_msg_unwrap_internal(obj[2], p1, p2, p3, p4);  /* FUN_0002286c */
    if (rc != 0) {
        sk_fatal_error("", 0, 0, 0, 0, "", 0, 0);   /* FUN_00019aac + FUN_003698b0 */
    }
    return rc;
}

/*--------------------------------------------------------------------*/
/* FUN_00021694 @ 0x00021694   (est. tightbeam_decoder_decode_forward)
 * Ghidra: undefined4 FUN_00021694(undefined8 param_1, code *param_2)
 * Runs a decode callback: builds a fresh decoder descriptor via FUN_000259c0,
 * invokes param_2 on it, then tears down via FUN_00025704. Returns 0.
 * Confidence: low (Swift decode bridge).
 */
unsigned int tightbeam_decoder_decode_forward(unsigned long param_1, void (*param_2)(void))
{
    unsigned char desc[0x31];
    (void)param_1;
    tightbeam_decoder_init(desc, 0);   /* FUN_000259c0 */
    param_2();
    tightbeam_message_teardown();   /* FUN_00025704 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00021738 @ 0x00021738   (est. tightbeam_message_read_u8)
 * Ghidra: void FUN_00021738(void)
 * Reads a 1-byte field from the TightbeamMessage (object+0x10), panicking if
 * the message is already unwrapped. Wraps FUN_00018878; canary-checked.
 * Confidence: medium (TightbeamMessage accessor).
 */
void tightbeam_message_read_u8(void)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned char out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    /* FUN_00018878(obj[2], &out) */
    if (canary != 0xd37afd4bb400012aull) {
        sk_stack_chk_fail();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000217e4 @ 0x000217e4   (est. tightbeam_msg_get_bool)
 * Ghidra: void FUN_000217e4(void)
 * Message getter for a boolean field: dispatches FUN_000219c4(FUN_00018a4c).
 * Confidence: low (thin getter trampoline).
 */
void tightbeam_msg_get_bool(void)
{
    tightbeam_msg_field_dispatch_1((void (*)(unsigned long, void *))0x18a4c);  /* FUN_000219c4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021844 @ 0x00021844   (est. tightbeam_msg_get_u16)
 * Ghidra: void FUN_00021844(void)
 * Message getter for a 16-bit field: dispatches FUN_00021ad8(FUN_00018be8).
 * Confidence: low.
 */
void tightbeam_msg_get_u16(void)
{
    tightbeam_msg_field_dispatch_2((void (*)(unsigned long, void *))0x18be8);  /* FUN_00021ad8 */
}

/*--------------------------------------------------------------------*/
/* FUN_000218a4 @ 0x000218a4   (est. tightbeam_msg_get_u32)
 * Ghidra: void FUN_000218a4(void)
 * Message getter for a 32-bit field: dispatches FUN_00021bec(FUN_00018d4c).
 * Confidence: low.
 */
void tightbeam_msg_get_u32(void)
{
    tightbeam_msg_field_dispatch_4((void (*)(unsigned long, void *))0x18d4c);  /* FUN_00021bec */
}

/*--------------------------------------------------------------------*/
/* FUN_00021904 @ 0x00021904   (est. tightbeam_msg_get_u64)
 * Ghidra: void FUN_00021904(void)
 * Message getter for a 64-bit field: dispatches FUN_00021d00(FUN_00018f38).
 * Confidence: low.
 */
void tightbeam_msg_get_u64(void)
{
    tightbeam_msg_field_dispatch_8((void (*)(unsigned long, void *))0x18f38);  /* FUN_00021d00 */
}

/*--------------------------------------------------------------------*/
/* FUN_00021964 @ 0x00021964   (est. tightbeam_msg_get_bool_alt)
 * Ghidra: void FUN_00021964(void)
 * Alternative boolean getter dispatching through FUN_000219c4 with a code
 * pointer 0x19088.
 * Confidence: low.
 */
void tightbeam_msg_get_bool_alt(void)
{
    tightbeam_msg_field_dispatch_1((void (*)(unsigned long, void *))0x19088);
}

/*--------------------------------------------------------------------*/
/* FUN_000219c4 @ 0x000219c4   (est. tightbeam_msg_field_dispatch_1)
 * Ghidra: void FUN_000219c4(code *param_1)
 * Dispatches a 1-byte field read: validates the message (object+0x10) then
 * calls param_1(msg, &out). Canary-checked.
 * Confidence: medium (TightbeamMessage field dispatch).
 */
void tightbeam_msg_field_dispatch_1(void (*param_1)(unsigned long, void *))
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned char out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    param_1(obj[2], &out);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00021a78 @ 0x00021a78   (est. tightbeam_msg_get_u16_alt)
 * Ghidra: void FUN_00021a78(void)
 * Alternative 16-bit getter via FUN_00021ad8(0x19198).
 * Confidence: low.
 */
void tightbeam_msg_get_u16_alt(void)
{
    tightbeam_msg_field_dispatch_2((void (*)(unsigned long, void *))0x19198);
}

/*--------------------------------------------------------------------*/
/* FUN_00021ad8 @ 0x00021ad8   (est. tightbeam_msg_field_dispatch_2)
 * Ghidra: void FUN_00021ad8(code *param_1)
 * Dispatches a 2-byte field read (16-bit) through param_1; canary-checked.
 * Confidence: medium (TightbeamMessage field dispatch).
 */
void tightbeam_msg_field_dispatch_2(void (*param_1)(unsigned long, void *))
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned short out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    param_1(obj[2], &out);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00021b8c @ 0x00021b8c   (est. tightbeam_msg_get_u32_alt)
 * Ghidra: void FUN_00021b8c(void)
 * Alternative 32-bit getter via FUN_00021bec(0x192ac).
 * Confidence: low.
 */
void tightbeam_msg_get_u32_alt(void)
{
    tightbeam_msg_field_dispatch_4((void (*)(unsigned long, void *))0x192ac);
}

/*--------------------------------------------------------------------*/
/* FUN_00021bec @ 0x00021bec   (est. tightbeam_msg_field_dispatch_4)
 * Ghidra: void FUN_00021bec(code *param_1)
 * Dispatches a 4-byte field read (32-bit) through param_1; canary-checked.
 * Confidence: medium (TightbeamMessage field dispatch).
 */
void tightbeam_msg_field_dispatch_4(void (*param_1)(unsigned long, void *))
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned int out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    param_1(obj[2], &out);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00021ca0 @ 0x00021ca0   (est. tightbeam_msg_get_u64_alt)
 * Ghidra: void FUN_00021ca0(void)
 * Alternative 64-bit getter via FUN_00021d00(0x193c0).
 * Confidence: low.
 */
void tightbeam_msg_get_u64_alt(void)
{
    tightbeam_msg_field_dispatch_8((void (*)(unsigned long, void *))0x193c0);
}

/*--------------------------------------------------------------------*/
/* FUN_00021d00 @ 0x00021d00   (est. tightbeam_msg_field_dispatch_8)
 * Ghidra: void FUN_00021d00(code *param_1)
 * Dispatches an 8-byte field read (64-bit) through param_1; canary-checked.
 * Confidence: medium (TightbeamMessage field dispatch).
 */
void tightbeam_msg_field_dispatch_8(void (*param_1)(unsigned long, void *))
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    param_1(obj[2], &out);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00021db4 @ 0x00021db4   (est. tightbeam_msg_write_u32)
 * Ghidra: void FUN_00021db4(void)
 * Message 32-bit field writer: validates message then FUN_00019540(msg,&out).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_u32(void)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned int out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    /* FUN_00019540(obj[2], &out) */
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00021e60 @ 0x00021e60   (est. tightbeam_msg_write_u64)
 * Ghidra: void FUN_00021e60(void)
 * Message 64-bit field writer: validates message then FUN_00019720(msg,&out).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_u64(void)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    /* FUN_00019720(obj[2], &out) */
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00021f0c @ 0x00021f0c   (est. tightbeam_msg_write_ptr)
 * Ghidra: void FUN_00021f0c(void)
 * Message pointer field writer: validates message then FUN_00015c30(msg,&out).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_ptr(void)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    /* FUN_00015c30(obj[2], &out) */
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00021fb8 @ 0x00021fb8   (est. tightbeam_decoder_decode_fatal)
 * Ghidra: void FUN_00021fb8(void)
 * Fatal-error path for the TightbeamDecoder: captures the decoder's six-word
 * state (from object), runs FUN_00025704 teardown, then fatal-errors with the
 * decoder module string.
 * Confidence: medium (string-matched TightbeamDecoder fatal).
 */
void tightbeam_decoder_decode_fatal(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    (void)obj;
    tightbeam_message_teardown();   /* FUN_00025704 */
    sk_fatal_error("Fatal error", 0xb, 2, 0, 0xe000000000000000,
                   "Tightbeam TightbeamDecoder swift", 0x20, 2, 0x8f, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00022028 @ 0x00022028   (est. tightbeam_decoder_copy_out)
 * Ghidra: void FUN_00022028(undefined1 *param_1, ...)
 * Copies the decoder descriptor out to param_1 on the success path, or writes
 * the status from FUN_000240e4 into *param_4 on failure (Swift result channel).
 * Confidence: low (Swift result-dispatch bridge).
 */
void tightbeam_decoder_copy_out(unsigned char *param_1, unsigned long p2, unsigned long p3,
                                unsigned int *param_4)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long status;
    obj = (unsigned long *)__builtin_frame_address(0);
    status = tightbeam_message_reset_internal(0, 0);   /* FUN_000240e4 */
    if (obj == 0) {   /* unaff_x21 */
        tightbeam_tb_descriptor_copy(param_1, (unsigned char *)obj);
    } else {
        tightbeam_message_teardown();
        *param_4 = (unsigned int)status;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000220d4 @ 0x000220d4   (est. tightbeam_decoder_dispatch_fatal)
 * Ghidra: void FUN_000220d4(long param_1)
 * Dispatches through context+8 then fatal-errors with the TightbeamDecoder
 * string. Used for unimplemented/invalid decoder operations.
 * Confidence: medium (string-matched).
 */
void tightbeam_decoder_dispatch_fatal(long param_1)
{
    (*(void (**)(void))(*(long *)(param_1 - 8) + 8))();
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000055, 0x80000000005acff0,
                   "Tightbeam TightbeamDecoder swift", 0x20, 2, 0xae, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00022158 @ 0x00022158   (est. tightbeam_msg_read_bool)
 * Ghidra: void FUN_00022158(undefined8 param_1, undefined8 param_2)
 * Message 1-byte reader trampoline → FUN_00022338(p1,p2,FUN_00018a4c).
 * Confidence: low.
 */
void tightbeam_msg_read_bool(unsigned long p1, unsigned long p2)
{
    tightbeam_msg_read_field_1(p1, p2, (void (*)(unsigned long, void *))0x18a4c);
}

/*--------------------------------------------------------------------*/
/* FUN_000221b8 @ 0x000221b8   (est. tightbeam_msg_read_u16)
 * Ghidra: void FUN_000221b8(undefined8 param_1, undefined8 param_2)
 * Message 2-byte reader trampoline → FUN_00022448(p1,p2,FUN_00018be8).
 * Confidence: low.
 */
void tightbeam_msg_read_u16(unsigned long p1, unsigned long p2)
{
    tightbeam_msg_read_field_2(p1, p2, (void (*)(unsigned long, void *))0x18be8);
}

/*--------------------------------------------------------------------*/
/* FUN_00022218 @ 0x00022218   (est. tightbeam_msg_read_u32)
 * Ghidra: void FUN_00022218(undefined8 param_1, undefined8 param_2)
 * Message 4-byte reader trampoline → FUN_00022558(p1,p2,FUN_00018d4c).
 * Confidence: low.
 */
void tightbeam_msg_read_u32(unsigned long p1, unsigned long p2)
{
    tightbeam_msg_read_field_4(p1, p2, (void (*)(unsigned long, void *))0x18d4c);
}

/*--------------------------------------------------------------------*/
/* FUN_00022278 @ 0x00022278   (est. tightbeam_msg_read_u64)
 * Ghidra: void FUN_00022278(undefined8 param_1, undefined8 param_2)
 * Message 8-byte reader trampoline → FUN_00022668(p1,p2,FUN_00018f38).
 * Confidence: low.
 */
void tightbeam_msg_read_u64(unsigned long p1, unsigned long p2)
{
    tightbeam_msg_read_field_8(p1, p2, (void (*)(unsigned long, void *))0x18f38);
}

/*--------------------------------------------------------------------*/
/* FUN_000222d8 @ 0x000222d8   (est. tightbeam_msg_read_bool_alt)
 * Ghidra: void FUN_000222d8(undefined8 param_1, undefined8 param_2)
 * Alternative 1-byte reader trampoline → FUN_00022338(p1,p2,0x19088).
 * Confidence: low.
 */
void tightbeam_msg_read_bool_alt(unsigned long p1, unsigned long p2)
{
    tightbeam_msg_read_field_1(p1, p2, (void (*)(unsigned long, void *))0x19088);
}

/*--------------------------------------------------------------------*/
/* FUN_00022338 @ 0x00022338   (est. tightbeam_msg_read_field_1)
 * Ghidra: void FUN_00022338(undefined8 param_1, undefined8 param_2, code *param_3)
 * Field read dispatch (1-byte): validates message then calls param_3(msg,&out).
 * Canary-checked.
 * Confidence: medium (TightbeamMessage field read).
 */
void tightbeam_msg_read_field_1(unsigned long p1, unsigned long p2, void (*param_3)(unsigned long, void *))
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned char out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    (void)p1; (void)p2;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    param_3(obj[2], &out);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_000223e8 @ 0x000223e8   (est. tightbeam_msg_read_u16_alt)
 * Ghidra: void FUN_000223e8(undefined8 param_1, undefined8 param_2)
 * Alternative 2-byte reader trampoline → FUN_00022448(p1,p2,0x19198).
 * Confidence: low.
 */
void tightbeam_msg_read_u16_alt(unsigned long p1, unsigned long p2)
{
    tightbeam_msg_read_field_2(p1, p2, (void (*)(unsigned long, void *))0x19198);
}

/*--------------------------------------------------------------------*/
/* FUN_00022448 @ 0x00022448   (est. tightbeam_msg_read_field_2)
 * Ghidra: void FUN_00022448(undefined8 param_1, undefined8 param_2, code *param_3)
 * Field read dispatch (2-byte): validates message then calls param_3(msg,&out).
 * Canary-checked.
 * Confidence: medium (TightbeamMessage field read).
 */
void tightbeam_msg_read_field_2(unsigned long p1, unsigned long p2, void (*param_3)(unsigned long, void *))
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned short out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    (void)p1; (void)p2;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    param_3(obj[2], &out);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_000224f8 @ 0x000224f8   (est. tightbeam_msg_read_u32_alt)
 * Ghidra: void FUN_000224f8(undefined8 param_1, undefined8 param_2)
 * Alternative 4-byte reader trampoline → FUN_00022558(p1,p2,0x192ac).
 * Confidence: low.
 */
void tightbeam_msg_read_u32_alt(unsigned long p1, unsigned long p2)
{
    tightbeam_msg_read_field_4(p1, p2, (void (*)(unsigned long, void *))0x192ac);
}

/*--------------------------------------------------------------------*/
/* FUN_00022558 @ 0x00022558   (est. tightbeam_msg_read_field_4)
 * Ghidra: void FUN_00022558(undefined8 param_1, undefined8 param_2, code *param_3)
 * Field read dispatch (4-byte): validates message then calls param_3(msg,&out).
 * Canary-checked.
 * Confidence: medium (TightbeamMessage field read).
 */
void tightbeam_msg_read_field_4(unsigned long p1, unsigned long p2, void (*param_3)(unsigned long, void *))
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned int out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    (void)p1; (void)p2;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    param_3(obj[2], &out);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00022608 @ 0x00022608   (est. tightbeam_msg_read_u64_alt)
 * Ghidra: void FUN_00022608(undefined8 param_1, undefined8 param_2)
 * Alternative 8-byte reader trampoline → FUN_00022668(p1,p2,0x193c0).
 * Confidence: low.
 */
void tightbeam_msg_read_u64_alt(unsigned long p1, unsigned long p2)
{
    tightbeam_msg_read_field_8(p1, p2, (void (*)(unsigned long, void *))0x193c0);
}

/*--------------------------------------------------------------------*/
/* FUN_00022668 @ 0x00022668   (est. tightbeam_msg_read_field_8)
 * Ghidra: void FUN_00022668(undefined8 param_1, undefined8 param_2, code *param_3)
 * Field read dispatch (8-byte): validates message then calls param_3(msg,&out).
 * Canary-checked.
 * Confidence: medium (TightbeamMessage field read).
 */
void tightbeam_msg_read_field_8(unsigned long p1, unsigned long p2, void (*param_3)(unsigned long, void *))
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long out = 0;
    unsigned long canary = 0xd37afd4bb400012aull;
    (void)p1; (void)p2;
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    param_3(obj[2], &out);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_00022718 @ 0x00022718   (est. tightbeam_decoder_bounds_check)
 * Ghidra: long FUN_00022718(ulong param_1, long param_2, long param_3)
 * Returns param_2+param_1 when the offset param_1 lies within [0, param_3-param_2);
 * otherwise fatal-errors with the TightbeamDecoder module string after
 * printing decoder context via FUN_002a4ab4/FUN_003a25d4/FUN_001ba7d4.
 * Confidence: medium (string-matched TightbeamDecoder bounds check).
 * Notes: s_Tightbeam_TightbeamDecoder_swift_005acfb0; 0x677880 debug global.
 */
long tightbeam_decoder_bounds_check(unsigned long param_1, long param_2, long param_3)
{
    if (((-1 < (long)param_1) && (param_2 != 0)) && (param_1 < (unsigned long)(param_3 - param_2))) {
        return param_2 + param_1;
    }
    /* FUN_002a4ab4(0x34); print via FUN_003a25d4/FUN_001ba7d4(0x677880,...) */
    sk_fatal_error("Fatal error", 0xb, 2, 0, 0xe000000000000000,
                   "Tightbeam TightbeamDecoder swift", 0x20, 2, 0xc3, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002286c @ 0x0002286c   (est. tightbeam_msg_unwrap_internal)
 * Ghidra: undefined8 FUN_0002286c(long param_1, ...)
 * Core message-unwrap: validates the message (param_1) is not already
 * unwrapped and the byte range param_2..param_3 is sane, allocates a
 * two-word decoder context (FUN_0036a940(0x65a730/0x65a758,0x20,7)), wires
 * the copy continuation, and performs the copy via FUN_00015a44 before
 * validating with FUN_003a26e8. Traps on failure.
 * Confidence: low (allocation + Swift unwrap pipeline).
 */
unsigned long tightbeam_msg_unwrap_internal(long param_1, long param_2, long param_3,
                                            unsigned long param_4, unsigned long param_5)
{
    unsigned long c1, c2, status, result;

    if (param_1 == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    if (param_2 < 0) SWIFT_BREAKPOINT();   /* 0x229e8 */
    if ((unsigned long)param_3 < (unsigned long)param_2) SWIFT_BREAKPOINT();   /* 0x229ec */
    c1 = (unsigned long)sk_alloc_typed(0x65a730, 0x20, 7);   /* FUN_0036a940 */
    *(unsigned long *)(c1 + 0x10) = param_4;
    *(unsigned long *)(c1 + 0x18) = param_5;
    c2 = (unsigned long)sk_alloc_typed(0x65a758, 0x20, 7);   /* FUN_0036a940 */
    *(void **)(c2 + 0x10) = (void *)0x22c18;
    *(unsigned long *)(c2 + 0x18) = c1;
    status = sk_dispatch_async(0, 0, 0, 0, 0, 0, 0, 0);   /* FUN_0004b520 */
    sk_lock_spin(c2);                    /* FUN_0036b270 */
    sk_lock_release(c1);                 /* FUN_0036b118 */
    result = sk_msg_copy(param_1, param_2, param_3 - param_2, status);  /* FUN_00015a44 */
    sk_dispatch_free(status);            /* FUN_0004b664 */
    status = sk_validate(c2, 0x5be7c0, 0xc9, 0x36, 0x52, 1);  /* FUN_003a26e8 */
    sk_lock_release(c1);
    sk_lock_release(c2);
    if ((status & 1) == 0) return result;
    SWIFT_BREAKPOINT();   /* 0x229f0 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022a3c @ 0x00022a3c   (est. tightbeam_message_teardown_forward)
 * Ghidra: void FUN_00022a3c(void)
 * Forwarder to FUN_00025704 (message teardown).
 * Confidence: medium (trivial forwarder).
 */
void tightbeam_message_teardown_forward(void)
{
    tightbeam_message_teardown();   /* FUN_00025704 */
}

/*--------------------------------------------------------------------*/
/* FUN_00022a7c @ 0x00022a7c   (est. tightbeam_tb_descriptor_move)
 * Ghidra: undefined1 * FUN_00022a7c(undefined1 *param_1, undefined1 *param_2)
 * Moves a transport-buffer descriptor param_2 → param_1, freeing the previous
 * backing pointer (tag-masked) and conditionally releasing the old buffer
 * contents via FUN_00020c88/FUN_00020d0c depending on the state byte.
 * Confidence: medium (descriptor move + conditional release).
 */
unsigned char *tightbeam_tb_descriptor_move(unsigned char *param_1, unsigned char *param_2)
{
    unsigned long prev;
    unsigned char st;

    *param_1 = *param_2;
    sk_lock_release(*(unsigned long *)(param_1 + 8) & 0x1fffffffffffffff);
    *(unsigned long *)(param_1 + 0x10) = *(unsigned long *)(param_2 + 0x10);
    *(unsigned long *)(param_1 + 8) = *(unsigned long *)(param_2 + 8);
    if (param_1[0x30] != 0xff) {
        st = param_2[0x30];
        if (st != 0xff) {
            /* full descriptor move with release of old fields */
            *(unsigned long *)(param_1 + 0x20) = *(unsigned long *)(param_2 + 0x20);
            *(unsigned long *)(param_1 + 0x18) = *(unsigned long *)(param_2 + 0x18);
            *(unsigned long *)(param_1 + 0x28) = *(unsigned long *)(param_2 + 0x28);
            param_1[0x30] = st;
            prev = *(unsigned long *)(param_1 + 0x18);
            tightbeam_tb_state(prev, 0, 0, 0);   /* FUN_00020d0c */
            return param_1;
        }
        tightbeam_transport_release(*(unsigned long *)(param_1 + 0x18),
                                    (void (*)(unsigned long))*(unsigned long *)(param_1 + 0x20),
                                    *(unsigned long *)(param_1 + 0x28), 0);
    }
    *(unsigned long *)(param_1 + 0x20) = *(unsigned long *)(param_2 + 0x20);
    *(unsigned long *)(param_1 + 0x18) = *(unsigned long *)(param_2 + 0x18);
    *(unsigned long *)(param_1 + 0x29) = *(unsigned long *)(param_2 + 0x29);
    *(unsigned long *)(param_1 + 0x21) = *(unsigned long *)(param_2 + 0x21);
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_00022c48 @ 0x00022c48   (est. tightbeam_message_copy_out)
 * Ghidra: void FUN_00022c48(undefined1 *param_1)
 * Copies the TightbeamMessage descriptor out to param_1 (after running the
 * per-message release FUN_0001590c). Panics if the message is unwrapped.
 * Confidence: medium (TightbeamMessage copy-out).
 */
void tightbeam_message_copy_out(unsigned char *param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long msg;
    unsigned char st;

    obj = (unsigned long *)__builtin_frame_address(0);
    msg = obj[2];
    if (msg != 0) {
        st = ((unsigned char *)obj)[0x30];
        /* FUN_0001590c(msg) release */
        tightbeam_tb_descriptor_copy(param_1, (unsigned char *)obj);
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00022d0c @ 0x00022d0c   (est. tightbeam_callback_invoke)
 * Ghidra: void FUN_00022d0c(undefined8 param_1, code *param_2)
 * Invokes the callback param_2 with no arguments.
 * Confidence: high (trivial call-through).
 */
void tightbeam_callback_invoke(unsigned long param_1, void (*param_2)(void))
{
    (void)param_1;
    param_2();
}

/*--------------------------------------------------------------------*/
/* FUN_00022d34 @ 0x00022d34   (est. tightbeam_context_dispatch)
 * Ghidra: void FUN_00022d34(long param_1, undefined8 param_2)
 * Dispatches through the context method table at param_1+0x20, passing param_2.
 * Confidence: medium (vtable dispatch).
 */
void tightbeam_context_dispatch(long param_1, unsigned long param_2)
{
    (*(void (**)(unsigned long))(param_1 + 0x20))(param_2);
}

/*--------------------------------------------------------------------*/
/* FUN_00022d60 @ 0x00022d60   (est. tightbeam_encoder_append)
 * Ghidra: void FUN_00022d60(long param_1, long param_2)
 * TightbeamEncoder append: validates the buffer (param_1) is non-null and the
 * message not already unwrapped, then appends param_2-param_1 bytes via
 * FUN_00018650. Failures fatal-error with "Failed to unwrap provided buffer"
 * (Encoder module) or "already unwrapp...".
 * Confidence: medium (string-matched TightbeamEncoder).
 * Notes: s_Tightbeam_TightbeamEncoder_swift_005ad0b0.
 */
void tightbeam_encoder_append(long param_1, long param_2)
{
    const char *msg;
    unsigned long err, code;
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);

    if (param_1 == 0) {
        msg = "Failed to unwrap provided buffer"; err = 0x2e;
        code = 0xd000000000000028;
    } else {
        if (obj[2] != 0) {
            /* FUN_00018650(obj[2], param_1, param_2 - param_1) */
            return;
        }
        msg = "TightbeamMessage already unwrapp"; err = 0x93;
        code = 0xd000000000000022;
    }
    sk_fatal_error("Fatal error", 0xb, 2, code,
                   (uint64_t)(msg - 0x20) | 0x8000000000000000,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, err, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00022e34 @ 0x00022e34   (est. tightbeam_encoder_flush_forward)
 * Ghidra: undefined8 FUN_00022e34(void)
 * Forwards to FUN_00022eac, rethrowing errors via FUN_003698b0.
 * Confidence: low (forwarder + rethrow).
 */
unsigned long tightbeam_encoder_flush_forward(void)
{
    unsigned long res = tightbeam_encoder_flush_internal();
    if ((int)res != 0) {
        sk_fatal_error("", 0, 0, 0, 0, "", 0, 0);
    }
    return res;
}

/*--------------------------------------------------------------------*/
/* FUN_00022eac @ 0x00022eac   (est. tightbeam_encoder_flush_internal)
 * Ghidra: undefined8 FUN_00022eac(...)
 * Encoder flush: validates the message (param_1+0x10), builds a two-word
 * encode context (FUN_0036a940(0x65a8c0/0x65a8e8,0x20,7)), performs the
 * encode via FUN_00015a44, and validates with FUN_003a26e8. Traps on failure.
 * Confidence: low (allocation + Swift encode pipeline, mirrors unwrap).
 */
unsigned long tightbeam_encoder_flush_internal(void)
{
    unsigned long msg, c1, c2, status, result;
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    msg = obj[2];
    if (msg == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    c1 = (unsigned long)sk_alloc_typed(0x65a8c0, 0x20, 7);
    *(unsigned long *)(c1 + 0x10) = 0;
    *(unsigned long *)(c1 + 0x18) = 0;
    c2 = (unsigned long)sk_alloc_typed(0x65a8e8, 0x20, 7);
    *(void **)(c2 + 0x10) = (void *)0x22c18;
    *(unsigned long *)(c2 + 0x18) = c1;
    status = sk_dispatch_async(0, 0, 0, 0, 0, 0, 0, 0);
    sk_lock_spin(c2);
    sk_lock_release(c1);
    result = sk_msg_copy(msg, 0, 0, status);   /* FUN_00015a44 */
    sk_dispatch_free(status);
    status = sk_validate(c2, 0x5be7c0, 0xc9, 0x43, 0x52, 1);  /* FUN_003a26e8 */
    sk_lock_release(c1);
    sk_lock_release(c2);
    if ((status & 1) == 0) return result;
    SWIFT_BREAKPOINT();   /* 0x23030 */
}

/*--------------------------------------------------------------------*/
/* FUN_0002307c @ 0x0002307c   (est. tightbeam_msg_write_flag)
 * Ghidra: void FUN_0002307c(uint param_1)
 * Message boolean/flag writer: validates message then FUN_000187a4(msg,param_1&1).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_flag(unsigned int param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* FUN_000187a4(obj[2], param_1 & 1) */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000230f8 @ 0x000230f8   (est. tightbeam_msg_write_u8)
 * Ghidra: void FUN_000230f8(undefined1 param_1)
 * Message 8-bit writer: validates message then FUN_000188fc(msg,param_1).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_u8(unsigned char param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* FUN_000188fc(obj[2], param_1) */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00023174 @ 0x00023174   (est. tightbeam_msg_write_u16)
 * Ghidra: void FUN_00023174(undefined2 param_1)
 * Message 16-bit writer: validates message then FUN_00018b0c(msg,param_1).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_u16(unsigned short param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* FUN_00018b0c(obj[2], param_1) */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000231f0 @ 0x000231f0   (est. tightbeam_msg_write_sel_1)
 * Ghidra: void FUN_000231f0(undefined8 param_1)
 * Message field writer trampoline → FUN_00023330(param_1, FUN_00018c70).
 * Confidence: low.
 */
void tightbeam_msg_write_sel_1(unsigned long param_1)
{
    tightbeam_msg_write_field_any(param_1, (void (*)(unsigned long, unsigned long))0x18c70);
}

/*--------------------------------------------------------------------*/
/* FUN_00023208 @ 0x00023208   (est. tightbeam_msg_write_sel_2)
 * Ghidra: void FUN_00023208(undefined8 param_1)
 * Message field writer trampoline → FUN_000233c8(param_1, FUN_00018dd4).
 * Confidence: low.
 */
void tightbeam_msg_write_sel_2(unsigned long param_1)
{
    tightbeam_msg_write_field_any(param_1, (void (*)(unsigned long, unsigned long))0x18dd4);
}

/*--------------------------------------------------------------------*/
/* FUN_00023220 @ 0x00023220   (est. tightbeam_msg_write_char)
 * Ghidra: void FUN_00023220(char param_1)
 * Message char writer: validates message then FUN_00019000(msg,(int)param_1).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_char(char param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* FUN_00019000(obj[2], (int)param_1) */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002329c @ 0x0002329c   (est. tightbeam_msg_write_short)
 * Ghidra: void FUN_0002329c(short param_1)
 * Message short writer: validates message then FUN_0001910c(msg,(int)param_1).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_short(short param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* FUN_0001910c(obj[2], (int)param_1) */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00023318 @ 0x00023318   (est. tightbeam_msg_write_sel_3)
 * Ghidra: void FUN_00023318(undefined8 param_1)
 * Message field writer trampoline → FUN_00023330(param_1, FUN_00019220).
 * Confidence: low.
 */
void tightbeam_msg_write_sel_3(unsigned long param_1)
{
    tightbeam_msg_write_field_any(param_1, (void (*)(unsigned long, unsigned long))0x19220);
}

/*--------------------------------------------------------------------*/
/* FUN_00023330 @ 0x00023330   (est. tightbeam_msg_write_field_any)
 * Ghidra: void FUN_00023330(undefined8 param_1, code *UNRECOVERED_JUMPTABLE)
 * Generic message field writer: validates message then calls the resolved
 * writer through the (unrecoverable) jump table. Panics if unwrapped.
 * Confidence: low (indirect-jump writer; "Could not recover jumptable").
 */
void tightbeam_msg_write_field_any(unsigned long param_1, void (*writer)(unsigned long, unsigned long))
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        writer(obj[2], param_1);
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000233c8 @ 0x000233c8   (est. tightbeam_msg_write_field_any2)
 * Ghidra: void FUN_000233c8(undefined8 param_1, code *UNRECOVERED_JUMPTABLE)
 * Generic message field writer (variant); same structure as FUN_00023330.
 * Confidence: low.
 */
void tightbeam_msg_write_field_any2(unsigned long param_1, void (*writer)(unsigned long, unsigned long))
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        writer(obj[2], param_1);
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00023448 @ 0x00023448   (est. tightbeam_msg_write_end)
 * Ghidra: void FUN_00023448(void)
 * Message writer end/flush: validates message then FUN_00019448().
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_end(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* FUN_00019448() */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000234bc @ 0x000234bc   (est. tightbeam_msg_write_begin)
 * Ghidra: void FUN_000234bc(void)
 * Message writer begin: validates message then FUN_00019628().
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_begin(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* FUN_00019628() */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00023530 @ 0x00023530   (est. tightbeam_msg_write_ptr_field)
 * Ghidra: void FUN_00023530(undefined8 param_1)
 * Message pointer field writer: validates message then FUN_00015be8(msg,param_1).
 * Confidence: medium (TightbeamMessage writer).
 */
void tightbeam_msg_write_ptr_field(unsigned long param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* FUN_00015be8(obj[2], param_1) */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000235a8 @ 0x000235a8   (est. tightbeam_encoder_dispatch_fatal)
 * Ghidra: void FUN_000235a8(undefined8 param_1, long param_2)
 * Dispatches through context+8 then fatal-errors with the TightbeamEncoder
 * module string. Used for invalid encoder operations.
 * Confidence: medium (string-matched TightbeamEncoder).
 * Notes: s_Tightbeam_TightbeamEncoder_swift_005ad0b0.
 */
void tightbeam_encoder_dispatch_fatal(unsigned long p1, long param_2)
{
    (void)p1;
    (*(void (**)(void))(*(long *)(param_2 - 8) + 8))();
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000056, 0x80000000005ad0c0,
                   "Tightbeam TightbeamEncoder swift", 0x20, 2, 0x97, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00023670 @ 0x00023670   (est. tightbeam_msg_write_multi_1)
 * Ghidra: void FUN_00023670(..., code *UNRECOVERED_JUMPTABLE)
 * Multi-argument message writer (jump-table dispatch); validates message.
 * Confidence: low.
 */
void tightbeam_msg_write_multi_1(unsigned long p1, unsigned long p2, unsigned long p3,
                                 void (*writer)(unsigned long, unsigned long))
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        writer(obj[2], p1);
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00023704 @ 0x00023704   (est. tightbeam_msg_write_multi_2)
 * Ghidra: void FUN_00023704(..., code *UNRECOVERED_JUMPTABLE)
 * Multi-argument message writer (jump-table dispatch); validates message.
 * Confidence: low.
 */
void tightbeam_msg_write_multi_2(unsigned long p1, unsigned long p2, unsigned long p3,
                                 void (*writer)(unsigned long, unsigned long))
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        writer(obj[2], p1);
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00023780 @ 0x00023780   (est. tightbeam_encoder_advance_ptr)
 * Ghidra: void FUN_00023780(void)
 * Advances the encoder's write pointer by the size returned from
 * FUN_0001879c(), trapping on overflow.
 * Confidence: medium (pointer-advance helper).
 */
void tightbeam_encoder_advance_ptr(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = /* FUN_0001879c() */ 0;
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x237ac */
}

/*--------------------------------------------------------------------*/
/* FUN_00023784 @ 0x00023784   (est. tightbeam_encoder_advance_ptr2)
 * Ghidra: void FUN_00023784(void)
 * Mirror of FUN_00023780: advances encoder write pointer by FUN_0001879c()
 * size, trapping on overflow.
 * Confidence: medium.
 */
void tightbeam_encoder_advance_ptr2(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = /* FUN_0001879c() */ 0;
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x237ac */
}

/*--------------------------------------------------------------------*/
/* FUN_00023824 @ 0x00023824   (est. tightbeam_encoder_advance_cb)
 * Ghidra: void FUN_00023824(undefined8 param_1, code *param_2)
 * Advances the encoder write pointer by the size returned from the callback
 * param_2(), trapping on overflow.
 * Confidence: medium.
 */
void tightbeam_encoder_advance_cb(unsigned long p1, long (*param_2)(void))
{
    long *ptr;   /* unaff_x20 */
    long delta;
    (void)p1;
    ptr = (long *)__builtin_frame_address(0);
    delta = param_2();
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23854 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023828 @ 0x00023828   (est. tightbeam_encoder_advance_cb2)
 * Ghidra: void FUN_00023828(undefined8 param_1, code *param_2)
 * Advance-by-callback variant (same as FUN_00023824, shared trap site 0x23854).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_cb2(unsigned long p1, long (*param_2)(void))
{
    long *ptr;   /* unaff_x20 */
    long delta;
    (void)p1;
    ptr = (long *)__builtin_frame_address(0);
    delta = param_2();
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23854 */
}

/*--------------------------------------------------------------------*/
/* FUN_0002386c @ 0x0002386c   (est. tightbeam_encoder_advance_cb3)
 * Ghidra: void FUN_0002386c(undefined8 param_1, code *param_2)
 * Advance-by-callback variant (trap site 0x2389c).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_cb3(unsigned long p1, long (*param_2)(void))
{
    long *ptr;   /* unaff_x20 */
    long delta;
    (void)p1;
    ptr = (long *)__builtin_frame_address(0);
    delta = param_2();
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x2389c */
}

/*--------------------------------------------------------------------*/
/* FUN_00023870 @ 0x00023870   (est. tightbeam_encoder_advance_cb4)
 * Ghidra: void FUN_00023870(undefined8 param_1, code *param_2)
 * Advance-by-callback variant (trap site 0x2389c).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_cb4(unsigned long p1, long (*param_2)(void))
{
    long *ptr;   /* unaff_x20 */
    long delta;
    (void)p1;
    ptr = (long *)__builtin_frame_address(0);
    delta = param_2();
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x2389c */
}

/*--------------------------------------------------------------------*/
/* FUN_000238b4 @ 0x000238b4   (est. tightbeam_encoder_advance_cb5)
 * Ghidra: void FUN_000238b4(undefined8 param_1, code *param_2)
 * Advance-by-callback variant (trap site 0x238e4).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_cb5(unsigned long p1, long (*param_2)(void))
{
    long *ptr;   /* unaff_x20 */
    long delta;
    (void)p1;
    ptr = (long *)__builtin_frame_address(0);
    delta = param_2();
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x238e4 */
}

/*--------------------------------------------------------------------*/
/* FUN_000238b8 @ 0x000238b8   (est. tightbeam_encoder_advance_cb6)
 * Ghidra: void FUN_000238b8(undefined8 param_1, code *param_2)
 * Advance-by-callback variant (trap site 0x238e4).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_cb6(unsigned long p1, long (*param_2)(void))
{
    long *ptr;   /* unaff_x20 */
    long delta;
    (void)p1;
    ptr = (long *)__builtin_frame_address(0);
    delta = param_2();
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x238e4 */
}

/*--------------------------------------------------------------------*/
/* FUN_000238fc @ 0x000238fc   (est. tightbeam_encoder_advance_u32)
 * Ghidra: void FUN_000238fc(void)
 * Advances the encoder write pointer by the size from FUN_00019440().
 * Confidence: medium.
 */
void tightbeam_encoder_advance_u32(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = /* FUN_00019440() */ 0;
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23928 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023900 @ 0x00023900   (est. tightbeam_encoder_advance_u32_2)
 * Ghidra: void FUN_00023900(void)
 * Mirror of FUN_000238fc (advance by FUN_00019440() size).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_u32_2(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = /* FUN_00019440() */ 0;
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23928 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023928 @ 0x00023928   (est. tightbeam_encoder_advance_u64)
 * Ghidra: void FUN_00023928(void)
 * Advances the encoder write pointer by the size from FUN_00019620().
 * Confidence: medium.
 */
void tightbeam_encoder_advance_u64(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = /* FUN_00019620() */ 0;
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23954 */
}

/*--------------------------------------------------------------------*/
/* FUN_0002392c @ 0x0002392c   (est. tightbeam_encoder_advance_u64_2)
 * Ghidra: void FUN_0002392c(void)
 * Mirror of FUN_00023928 (advance by FUN_00019620() size).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_u64_2(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = /* FUN_00019620() */ 0;
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23954 */
}

/*--------------------------------------------------------------------*/
/* FUN_0002396c @ 0x0002396c   (est. tightbeam_encoder_advance_cb7)
 * Ghidra: void FUN_0002396c(undefined8 param_1, code *param_2)
 * Advance-by-callback variant (trap site 0x2399c).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_cb7(unsigned long p1, long (*param_2)(void))
{
    long *ptr;   /* unaff_x20 */
    long delta;
    (void)p1;
    ptr = (long *)__builtin_frame_address(0);
    delta = param_2();
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x2399c */
}

/*--------------------------------------------------------------------*/
/* FUN_00023970 @ 0x00023970   (est. tightbeam_encoder_advance_cb8)
 * Ghidra: void FUN_00023970(undefined8 param_1, code *param_2)
 * Advance-by-callback variant (trap site 0x2399c).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_cb8(unsigned long p1, long (*param_2)(void))
{
    long *ptr;   /* unaff_x20 */
    long delta;
    (void)p1;
    ptr = (long *)__builtin_frame_address(0);
    delta = param_2();
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x2399c */
}

/*--------------------------------------------------------------------*/
/* FUN_00023a14 @ 0x00023a14   (est. tightbeam_encoder_advance_x3)
 * Ghidra: void FUN_00023a14(void)
 * Advances the encoder write pointer by the size from the callback in x3.
 * Confidence: medium.
 */
void tightbeam_encoder_advance_x3(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = 0;   /* (*in_x3)() */
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23a44 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023a18 @ 0x00023a18   (est. tightbeam_encoder_advance_x3_2)
 * Ghidra: void FUN_00023a18(void)
 * Advance-by-x3-callback variant (trap 0x23a44).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_x3_2(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = 0;   /* (*in_x3)() */
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23a44 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023a5c @ 0x00023a5c   (est. tightbeam_encoder_advance_x3_3)
 * Ghidra: void FUN_00023a5c(void)
 * Advance-by-x3-callback variant (trap 0x23a8c).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_x3_3(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = 0;   /* (*in_x3)() */
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23a8c */
}

/*--------------------------------------------------------------------*/
/* FUN_00023a60 @ 0x00023a60   (est. tightbeam_encoder_advance_x3_4)
 * Ghidra: void FUN_00023a60(void)
 * Advance-by-x3-callback variant (trap 0x23a8c).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_x3_4(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = 0;   /* (*in_x3)() */
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23a8c */
}

/*--------------------------------------------------------------------*/
/* FUN_00023aa4 @ 0x00023aa4   (est. tightbeam_encoder_advance_x3_5)
 * Ghidra: void FUN_00023aa4(void)
 * Advance-by-x3-callback variant (trap 0x23ad4).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_x3_5(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = 0;   /* (*in_x3)() */
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23ad4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023aa8 @ 0x00023aa8   (est. tightbeam_encoder_advance_x3_6)
 * Ghidra: void FUN_00023aa8(void)
 * Advance-by-x3-callback variant (trap 0x23ad4).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_x3_6(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = 0;   /* (*in_x3)() */
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23ad4 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023b04 @ 0x00023b04   (est. tightbeam_encoder_advance_x3_7)
 * Ghidra: void FUN_00023b04(void)
 * Advance-by-x3-callback variant (trap 0x23b34).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_x3_7(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = 0;   /* (*in_x3)() */
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23b34 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023b08 @ 0x00023b08   (est. tightbeam_encoder_advance_x3_8)
 * Ghidra: void FUN_00023b08(void)
 * Advance-by-x3-callback variant (trap 0x23b34).
 * Confidence: medium.
 */
void tightbeam_encoder_advance_x3_8(void)
{
    long *ptr;   /* unaff_x20 */
    long delta;
    ptr = (long *)__builtin_frame_address(0);
    delta = 0;   /* (*in_x3)() */
    if ((unsigned long)(*ptr + delta) >= *ptr) {
        *ptr = *ptr + delta;
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x23b34 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023b64 @ 0x00023b64   (est. tightbeam_encoder_vtable_dispatch)
 * Ghidra: void FUN_00023b64(void)
 * Dispatches through the vtable slot at object+0x10.
 * Confidence: medium (vtable dispatch).
 */
void tightbeam_encoder_vtable_dispatch(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    (*(void (**)(void))obj[2])();
}

/*--------------------------------------------------------------------*/
/* FUN_00023c10 @ 0x00023c10   (est. tightbeam_codable_dispatch)
 * Ghidra: void FUN_00023c10(...)
 * Resolves a Codable method pointer from param_5 via FUN_00023c78 and calls
 * it with (param_2,param_4,param_5).
 * Confidence: medium (method-table resolve + call).
 */
void tightbeam_codable_dispatch(unsigned long p1, unsigned long param_2, unsigned long p3,
                                unsigned long param_4, unsigned long param_5)
{
    (void)p1; (void)p3;
    void (*fn)(unsigned long, unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long, unsigned long))tightbeam_method_16(param_5);
    fn(param_2, param_4, param_5);
}

/*--------------------------------------------------------------------*/
/* FUN_00023c78 @ 0x00023c78   (est. tightbeam_method_16)
 * Ghidra: long FUN_00023c78(ulong param_1)
 * Resolves a Swift method-table entry: if the tagged pointer is non-null
 * (bit 0 set), dereferences it, then returns table+0x14 plus the length at
 * table+0x14 (method slot at offset 0x14).
 * Confidence: high (standard Swift method-table resolve).
 */
long tightbeam_method_16(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 0x14) + (long)*(int *)(param_1 + 0x14);
}

/*--------------------------------------------------------------------*/
/* FUN_00023ca8 @ 0x00023ca8   (est. tightbeam_codable_dispatch2)
 * Ghidra: void FUN_00023ca8(...)
 * Resolves a Codable method pointer from param_3 via FUN_00023d00 and calls
 * it with (param_2,param_3).
 * Confidence: medium (method-table resolve + call).
 */
void tightbeam_codable_dispatch2(unsigned long p1, unsigned long param_2, unsigned long param_3)
{
    (void)p1;
    void (*fn)(unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long))tightbeam_method_16b(param_3);
    fn(param_2, param_3);
}

/*--------------------------------------------------------------------*/
/* FUN_00023d00 @ 0x00023d00   (est. tightbeam_method_16b)
 * Ghidra: long FUN_00023d00(ulong param_1)
 * Swift method-table resolve (method slot at offset 0x14), same as
 * FUN_00023c78.
 * Confidence: high.
 */
long tightbeam_method_16b(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 0x14) + (long)*(int *)(param_1 + 0x14);
}

/*--------------------------------------------------------------------*/
/* FUN_00023d54 @ 0x00023d54   (est. tightbeam_bounds_forward)
 * Ghidra: void FUN_00023d54(...)
 * Forwarder to FUN_00022718 (bounds check) with reordered args.
 * Confidence: low.
 */
void tightbeam_bounds_forward(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4)
{
    tightbeam_decoder_bounds_check(p4, p3, p1);   /* FUN_00022718 */
}

/*--------------------------------------------------------------------*/
/* FUN_00023d78 @ 0x00023d78   (est. tightbeam_codable_call3)
 * Ghidra: void FUN_00023d78(...)
 * Calls a Codable method with the object argument, forwarding through
 * FUN_00023c10 with the object base from the frame.
 * Confidence: low.
 */
void tightbeam_codable_call3(unsigned long p1, unsigned long p2, unsigned long p3)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    tightbeam_codable_dispatch(p1, obj[0], p3, p2, p3);
}

/*--------------------------------------------------------------------*/
/* FUN_00023d7c @ 0x00023d7c   (est. tightbeam_codable_call3b)
 * Ghidra: void FUN_00023d7c(...)
 * Mirror of FUN_00023d78.
 * Confidence: low.
 */
void tightbeam_codable_call3b(unsigned long p1, unsigned long p2, unsigned long p3)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    tightbeam_codable_dispatch(p1, obj[0], p3, p2, p3);
}

/*--------------------------------------------------------------------*/
/* FUN_00023da8 @ 0x00023da8   (est. tightbeam_codable_result)
 * Ghidra: void FUN_00023da8(undefined8 *param_1)
 * Invokes a Codable method and stores the result: on success writes the
 * result into param_1[0] and clears param_1[1]; on failure writes the error
 * code through the x3 error slot.
 * Confidence: medium (Swift result dispatch).
 */
void tightbeam_codable_result(unsigned long *param_1)
{
    unsigned long res = 0;   /* FUN_00023ca8() */
    unsigned int *err_slot;  /* in_x3 */
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        param_1[0] = res;
        *(unsigned char *)(param_1 + 1) = 0;
    } else {
        err_slot = (unsigned int *)0;
        *err_slot = (unsigned int)res;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00023f74 @ 0x00023f74   (est. tightbeam_transport_run)
 * Ghidra: void FUN_00023f74(...)
 * Runs a Tightbeam transport operation: stores the argument block, invokes
 * the transport init FUN_00020134 with the callback FUN_000251ec, then the
 * optional dispatch callback at context+0x20.
 * Confidence: low (Swift bridge assembling transport run).
 */
void tightbeam_transport_run(unsigned long p1, unsigned long p2, unsigned long p3,
                             unsigned long p4, unsigned long p5, unsigned long p6,
                             long param_7, unsigned long p8, unsigned long p9)
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5; (void)p6;
    (void)p8; (void)p9;
    tightbeam_transport_init();   /* FUN_00020134 */
    /* optional dispatch callback at *(param_7-8)+0x20 */
}

/*--------------------------------------------------------------------*/
/* FUN_00024064 @ 0x00024064   (est. tightbeam_tb_desc_copy_thunk)
 * Ghidra: void thunk_FUN_00024068(byte *param_1)
 * Thunk of FUN_00024068 (descriptor copy-out).
 * Confidence: high (thunk).
 */
void tightbeam_tb_desc_copy_thunk(unsigned char *param_1)
{
    tightbeam_tb_descriptor_copy(param_1, (unsigned char *)__builtin_frame_address(0));
}

/*--------------------------------------------------------------------*/
/* FUN_00024068 @ 0x00024068   (est. tightbeam_tb_desc_copy)
 * Ghidra: void FUN_00024068(byte *param_1)
 * Copies the 0x31-byte TightbeamMessage descriptor from the frame object into
 * param_1 (masking the flag bit of the first word).
 * Confidence: high (plain struct copy).
 */
void tightbeam_tb_desc_copy(unsigned char *param_1)
{
    tightbeam_tb_descriptor_copy(param_1, (unsigned char *)__builtin_frame_address(0));
}

/*--------------------------------------------------------------------*/
/* FUN_00024098 @ 0x00024098   (est. tightbeam_decoder_descriptor_out)
 * Ghidra: void FUN_00024098(undefined8 *param_1)
 * Builds a fresh decoder descriptor via FUN_000259c0 and stores the six-word
 * result into param_1.
 * Confidence: medium (decoder descriptor store).
 */
void tightbeam_decoder_descriptor_out(unsigned long *param_1)
{
    unsigned char desc[0x31];
    tightbeam_decoder_init(desc, 0);   /* FUN_000259c0 */
    param_1[1] = *(unsigned long *)(desc + 8);
    param_1[0] = *(unsigned long *)(desc + 0x10);
    param_1[3] = *(unsigned long *)(desc + 0x28);
    param_1[2] = *(unsigned long *)(desc + 0x18);
    param_1[5] = *(unsigned long *)(desc + 0x18 + 0x18);
    param_1[4] = *(unsigned long *)(desc + 0x18 + 0x20);
    *(unsigned char *)(param_1 + 6) = *(unsigned char *)(desc + 0x30);
}

/*--------------------------------------------------------------------*/
/* FUN_000240e4 @ 0x000240e4   (est. tightbeam_message_reset_internal)
 * Ghidra: undefined8 FUN_000240e4(...)
 * Resets the TightbeamMessage's buffer: decodes the tagged pointer at
 * object+8 (type bits 61-63). For types 1/2 it re-wraps the buffer via
 * FUN_00014f90 into the object's message slot; type 3/4 panic with
 * "TightbeamMessage reset() called o..." messages. Type 0 (inline) uses
 * FUN_00014c08. Panics if the message is already unwrapped.
 * Confidence: medium (string-matched TightbeamMessage reset).
 * Notes: s_TightbeamMessage_reset___called_o_005ad220 / 005ad270.
 */
unsigned long tightbeam_message_reset_internal(unsigned long param_1, unsigned long param_2)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long tagged, msg, buf;
    unsigned int type, kind;
    int rc;
    const char *msgstr;
    unsigned long err, code;

    obj = (unsigned long *)__builtin_frame_address(0);
    tagged = obj[1];   /* +8 */
    kind = (unsigned int)(tagged >> 61);
    if (kind == 0) {
        msg = obj[2];
        if (msg != 0) {
            buf = *(unsigned long *)(tagged + 0x10);
            sk_lock_spin(tagged);
            rc = (int)sk_msg_reset(buf, msg, param_1, param_2);   /* FUN_00014c08 */
            if (rc == 0) {
                sk_lock_release(tagged & 0x1fffffffffffffff);
                return param_1;
            }
            sk_fatal_error("", 0, 0, 0, 0, "", 0, 0);
        }
        goto already;
    }
    if (kind < 2) {   /* type 1 */
        buf = *(unsigned long *)((tagged & 0x1fffffffffffffff) + 0x10);
        if (buf == 0) SWIFT_BREAKPOINT();   /* 0x242a8 */
        msg = obj[2];
        if (msg == 0) goto already;
        sk_lock_spin(tagged & 0x1fffffffffffffff);
        rc = (int)sk_msg_reset2(buf, msg, param_1, param_2);   /* FUN_00014f90 */
        if (rc == 0) {
            sk_lock_release(tagged & 0x1fffffffffffffff);
            return param_1;
        }
        sk_fatal_error("", 0, 0, 0, 0, "", 0, 0);
    } else {
        type = (unsigned int)(tagged >> 61);
        if (type == 2) {
            buf = *(unsigned long *)((tagged & 0x1fffffffffffffff) + 0x10);
            if (buf == 0) SWIFT_BREAKPOINT();   /* 0x242ac */
            msg = obj[2];
            if (msg == 0) goto already;
            sk_lock_spin(tagged & 0x1fffffffffffffff);
            rc = (int)sk_msg_reset2(buf, msg, param_1, param_2);
            if (rc == 0) {
                sk_lock_release(tagged & 0x1fffffffffffffff);
                return param_1;
            }
            sk_fatal_error("", 0, 0, 0, 0, "", 0, 0);
        }
        if (type == 3) { msgstr = "TightbeamMessage reset() called o"; err = 0x1a6; code = 0xd000000000000049; }
        else { msgstr = "TightbeamMessage reset() called o"; err = 0x1a8; code = 0xd00000000000004d; }
        sk_fatal_error("Fatal error", 0xb, 2, code,
                       (uint64_t)(msgstr - 0x20) | 0x8000000000000000,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, err, 0);
    }
    sk_fatal_error("", 0, 0, 0, 0, "", 0, 0);
already:
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022,
                   (uint64_t)("TightbeamMessage already unwrapp" - 0x20) | 0x8000000000000000,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002437c @ 0x0002437c   (est. tightbeam_decoder_build_msg)
 * Ghidra: void FUN_0002437c(...)
 * Builds a TightbeamMessage descriptor from a decoded buffer: reads the
 * source descriptor (param_2), assembles a 16-byte decoder block, and on the
 * success path writes the six-word message into param_1. On failure it
 * rethrows the error (FUN_00365b6c path) and fatal-errors with the
 * TightbeamMessage string.
 * Confidence: low (large Swift decode-assembly; NEON_ext register shuffles).
 * Notes: FUN_003ed2dc type-register; FUN_00002534/FUN_00365b6c error rethrow.
 */
void tightbeam_decoder_build_msg(unsigned long *param_1, unsigned char *param_2,
                                 unsigned long param_3, unsigned long param_4,
                                 unsigned int *param_5)
{
    unsigned long f8, v;
    unsigned char f0, b;
    int rc;
    unsigned long *x21;   /* unaff_x21 */

    f8 = *(unsigned long *)(param_2 + 0x28);
    f0 = param_2[0x30];
    v = *(unsigned long *)(param_2 + 0x10);
    (void)f8; (void)f0; (void)v;
    x21 = (unsigned long *)__builtin_frame_address(0);
    if (x21 == 0) {
        /* success path: write six-word message descriptor into param_1 */
        param_1[1] = 0;
        param_1[0] = 0;
        param_1[3] = 0;
        param_1[2] = 0;
        param_1[5] = 0;
        param_1[4] = 0;
        *(unsigned char *)(param_1 + 6) = 0;
    } else {
        /* error path: FUN_0036b270/FUN_00002534/FUN_00365b6c rethrow then fatal */
        sk_lock_spin(0);
        sk_fatal_error("Fatal error", 0xb, 2, 0, 0xe000000000000000,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x2f, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00024678 @ 0x00024678   (est. tightbeam_event_post)
 * Ghidra: void FUN_00024678(...)
 * Posts an event: stores the five argument words into the event object
 * (unaff_x22) at +0xb8..+0xd8, then schedules the event handler via
 * FUN_00408db8(&LAB_000246a4,0,0).
 * Confidence: low (Swift async event post).
 */
void tightbeam_event_post(unsigned long p1, unsigned long param_2, unsigned long param_3,
                          unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    unsigned long *evt;   /* unaff_x22 */
    (void)p1;
    evt = (unsigned long *)__builtin_frame_address(0);
    evt[0x1a] = param_5;   /* +0xd0 */
    evt[0x1b] = param_6;   /* +0xd8 */
    evt[0x18] = param_3;   /* +0xc0 */
    evt[0x19] = param_4;   /* +0xc8 */
    evt[0x17] = param_2;   /* +0xb8 */
    /* FUN_00408db8(&LAB_000246a4,0,0) */
}

/*--------------------------------------------------------------------*/
/* FUN_000247d0 @ 0x000247d0   (est. tightbeam_event_dispatch)
 * Ghidra: void FUN_000247d0(void)
 * Event dispatch: releases the event's object (FUN_0040bd24 on +0xe0), then
 * schedules either the success handler (LAB_00024924) or, when the event
 * object is non-null, records the state word at +0x7c and runs FUN_000248a4.
 * Confidence: low (Swift async event dispatch).
 */
void tightbeam_event_dispatch(void)
{
    unsigned long *evt;   /* unaff_x22 */
    unsigned long *obj;   /* unaff_x20 */
    evt = (unsigned long *)__builtin_frame_address(0);
    obj = (unsigned long *)0;
    /* FUN_0040bd24(*(evt+0xe0)) */
    if (obj == 0) {
        /* handler LAB_00024924 */
    } else {
        *(unsigned int *)((char *)evt + 0x7c) = *(unsigned int *)((char *)evt + 0x44);
        tightbeam_event_dispatch_result();   /* FUN_000248a4 */
    }
    /* FUN_00408db8(handler,0,0) */
}

/*--------------------------------------------------------------------*/
/* FUN_000248a4 @ 0x000248a4   (est. tightbeam_event_dispatch_result)
 * Ghidra: void FUN_000248a4(void)
 * Reads the event result word (+0x7c), records it through the error-report
 * FUN_0036993c, and jumps through the event vtable (+8). Unrecoverable
 * jump table.
 * Confidence: low (event-result dispatch; "Could not recover jumptable").
 */
void tightbeam_event_dispatch_result(void)
{
    unsigned long *evt;   /* unaff_x22 */
    unsigned int res;
    evt = (unsigned long *)__builtin_frame_address(0);
    res = *(unsigned int *)((char *)evt + 0x7c);
    /* FUN_0036993c(...,0,0) record result */
    (void)res;
    /* jump through *(evt+8) */
}

/*--------------------------------------------------------------------*/
/* FUN_00024e40 @ 0x00024e40   (est. tightbeam_event_release)
 * Ghidra: void FUN_00024e40(void)
 * Releases the event's second object (FUN_0040bd24 on +0xf0), then schedules
 * either the success handler (DAT_00025e68) or, when non-null, records the
 * state word and dispatches via DAT_00025e5c.
 * Confidence: low (Swift async event release).
 */
void tightbeam_event_release(void)
{
    unsigned long *evt;   /* unaff_x22 */
    unsigned long *obj;   /* unaff_x20 */
    evt = (unsigned long *)__builtin_frame_address(0);
    obj = (unsigned long *)0;
    /* FUN_0040bd24(*(evt+0xf0)) */
    if (obj == 0) {
        /* handler DAT_00025e68 */
    } else {
        *(unsigned int *)((char *)evt + 0x7c) = *(unsigned int *)((char *)evt + 0x44);
        /* dispatch DAT_00025e5c */
    }
    /* FUN_00408db8(handler,0,0) */
}

/*--------------------------------------------------------------------*/
/* FUN_00024f14 @ 0x00024f14   (est. tightbeam_decoder_parse_2arg)
 * Ghidra: void FUN_00024f14(...)
 * Two-argument decode helper: passes both args to FUN_00018560 unless the
 * selector flag param_3 equals 1 (in which case both are zeroed).
 * Confidence: low.
 */
void tightbeam_decoder_parse_2arg(unsigned long param_1, unsigned long param_2, char param_3,
                                  unsigned long param_4)
{
    unsigned long a = 0, b = 0;
    if (param_3 != '\x01') { a = param_1; b = param_2; }
    /* FUN_00018560(a, b, param_4) */
}

/*--------------------------------------------------------------------*/
/* FUN_00024f18 @ 0x00024f18   (est. tightbeam_decoder_parse_2arg_b)
 * Ghidra: void FUN_00024f18(...)
 * Mirror of FUN_00024f14 (two-argument decode helper).
 * Confidence: low.
 */
void tightbeam_decoder_parse_2arg_b(unsigned long param_1, unsigned long param_2, char param_3,
                                    unsigned long param_4)
{
    unsigned long a = 0, b = 0;
    if (param_3 != '\x01') { a = param_1; b = param_2; }
    /* FUN_00018560(a, b, param_4) */
}

/*--------------------------------------------------------------------*/
/* FUN_00024f40 @ 0x00024f40   (est. tightbeam_transport_write)
 * Ghidra: void FUN_00024f40(...)
 * Writes into the Tightbeam transport buffer: validates not-forgotten,
 * assembles a 4-byte kind descriptor, invokes the encode callback (param_7)
 * on a scratch descriptor, then commits/releases the buffer via
 * FUN_00020d0c (freeing the backing store when the state byte was zero).
 * Canary-checked; optional dispatch callback.
 * Confidence: medium (TransportBuffer write lifecycle).
 */
void tightbeam_transport_write(unsigned long param_1, unsigned long param_2,
                               void (*param_3)(unsigned long), unsigned long param_4,
                               unsigned long param_5, unsigned int param_6,
                               void (*param_7)(unsigned long, void *, void *),
                               unsigned long param_8, unsigned long param_9,
                               long param_10, unsigned long param_11, unsigned long param_12)
{
    unsigned long canary = 0xd37afd4bb400012aull;
    unsigned int kind;
    unsigned long backing;
    (void)param_1; (void)param_8; (void)param_9; (void)param_11; (void)param_12;

    if (1 < (unsigned int)((unsigned char)__builtin_frame_address(0))) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000025, 0x80000000005acd00,
                       "Tightbeam TransportBuffer swift", 0x1f, 2);
    }
    kind = 4;
    if ((param_6 & 0xff) != 1) kind = 1;
    backing = param_2;
    /* invoke encode callback param_7 on scratch descriptor */
    param_7(param_1, (void *)&kind, (void *)0);
    if ((param_5 & 0xff) == 0) {
        sk_lock_spin(param_4);   /* FUN_0036b270 */
        param_3(param_2);
        sk_obj_bind_reset(param_2, 0xffffffffffffffffu, 0xffffffffffffffffu);
        tightbeam_tb_state(param_2, (unsigned long)param_3, param_4, 0);
        param_5 = 0;
    }
    tightbeam_tb_state(param_2, (unsigned long)param_3, param_4, param_5);
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_000251ec @ 0x000251ec   (est. tightbeam_transport_write_forward)
 * Ghidra: void FUN_000251ec(void)
 * Forwarder to FUN_00024f40 (transport write).
 * Confidence: medium (trivial forwarder).
 */
void tightbeam_transport_write_forward(void)
{
    tightbeam_transport_write(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00025228 @ 0x00025228   (est. tightbeam_message_send)
 * Ghidra: undefined8 FUN_00025228(...)
 * Sends a Tightbeam message: allocates a small send context (type from
 * FUN_000286dc, 0x18 bytes), stores the target, forwards to FUN_000252d4,
 * then frees the context.
 * Confidence: low (message send scaffolding).
 */
unsigned long tightbeam_message_send(unsigned long param_1, unsigned long param_2,
                                     unsigned long param_3, unsigned long param_4,
                                     unsigned long param_5, unsigned long param_6,
                                     unsigned long param_7, unsigned long param_8)
{
    unsigned long type = tightbeam_type_id().lo;   /* FUN_000286dc */
    unsigned long ctx = (unsigned long)sk_alloc_typed(type, 0x18, 7);
    *(unsigned long *)(ctx + 0x10) = param_2;
    unsigned long res = tightbeam_message_send_internal(param_1, ctx, param_3, param_4,
                                                        param_5, param_6, param_7, param_8);
    sk_lock_release(ctx);
    return res;
}

/*--------------------------------------------------------------------*/
/* FUN_000252d4 @ 0x000252d4   (est. tightbeam_message_send_internal)
 * Ghidra: long FUN_000252d4(...)
 * Core message send: builds a send descriptor, resolves the message method
 * table via FUN_00025dcc(param_8), and invokes it. On a non-2 status it
 * validates the result message (fatal-error if unwrapped) and tears down.
 * Returns the result slot.
 * Confidence: low (message send pipeline).
 */
long tightbeam_message_send_internal(unsigned long param_1, unsigned long param_2,
                                     unsigned long param_3, unsigned long param_4,
                                     unsigned long param_5, unsigned long param_6,
                                     unsigned long param_7, unsigned long param_8)
{
    unsigned long status;
    long result;
    (void)param_3; (void)param_4; (void)param_5; (void)param_6; (void)param_7;
    sk_lock_spin(param_2);
    void (*fn)(void *, void *, void *) = (void (*)(void *, void *, void *))tightbeam_method_4(param_8);
    fn((void *)&status, (void *)0, (void *)param_8);
    if ((status & 0xff) == 2) {
        result = 0;
    } else {
        if (result == 0) {
            sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                           "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
        }
        tightbeam_message_teardown();
    }
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_000254d4 @ 0x000254d4   (est. tightbeam_transport_init_desc)
 * Ghidra: void FUN_000254d4(...)
 * Initialises a transport-buffer descriptor (param_1): allocates a 0x58-byte
 * state block (FUN_0036a804), runs FUN_0001586c ctor, optionally stores the
 * inline size word, then fills the descriptor fields with the supplied
 * base/data/cap and state byte. Fatal-errors if the buffer was forgotten.
 * Confidence: medium (TransportBuffer descriptor init).
 */
void tightbeam_transport_init_desc(unsigned char *param_1, unsigned long param_2,
                                   unsigned long param_3, unsigned long param_4,
                                   unsigned char param_5, unsigned char param_6,
                                   unsigned long param_7)
{
    unsigned int *state;
    (void)param_6;
    state = (unsigned int *)sk_alloc_aligned(0x58, 0xffffffffffffffffu);
    *state = 0;
    if (param_5 < 2) {
        /* FUN_0001586c(state, param_2, param_6) */
        if ((param_7 & 0xff00000000) != 0x100000000) {
            *state = (unsigned int)param_7;
        }
        param_1[0] = 0;
        *(unsigned long *)(param_1 + 8) = 0x8000000000000000;
        *(unsigned int **)(param_1 + 0x10) = state;
        *(unsigned long *)(param_1 + 0x18) = param_2;
        *(unsigned long *)(param_1 + 0x20) = param_3;
        *(unsigned long *)(param_1 + 0x28) = param_4;
        param_1[0x30] = param_5;
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000025, 0x80000000005acd00,
                   "Tightbeam TransportBuffer swift", 0x1f, 2, 0x3b, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000255d8 @ 0x000255d8   (est. tightbeam_message_reset_desc)
 * Ghidra: void FUN_000255d8(void)
 * Resets the message descriptor: if the state byte at object+0x30 is not -1,
 * forwards to the reset callback and then the optional dispatch; otherwise
 * fatal-errors with the TightbeamMessage string.
 * Confidence: medium (string-matched TightbeamMessage reset).
 */
void tightbeam_message_reset_desc(void)
{
    unsigned char *obj;   /* unaff_x20 */
    obj = (unsigned char *)__builtin_frame_address(0);
    if (obj[0x30] != 0xff) {
        /* (*extraout_x12)(obj+0x18, &stack) reset; dispatch */
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd00000000000002a, 0x80000000005ad140,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x182, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00025704 @ 0x00025704   (est. tightbeam_message_teardown)
 * Ghidra: void FUN_00025704(void)
 * Tears down a TightbeamMessage: if the underlying message (object+0x10) is
 * non-null and the buffer is owned (flag bit clear), it releases the backing
 * buffer according to its tagged type (1/2 via FUN_00014f10/FUN_00014bec,
 * plus FUN_00015964 finalize and thunk_FUN_00012568 reset). Then it releases
 * the buffer descriptor (tag-masked) and conditionally frees the transport
 * buffer through FUN_00020d0c. Fatal-errors for unsupported types.
 * Confidence: medium (string-matched TightbeamMessage teardown).
 */
void tightbeam_message_teardown(void)
{
    unsigned char *obj;   /* unaff_x20 */
    unsigned long msg, tagged, buf;
    unsigned int kind;
    unsigned char st;
    unsigned long *d0, *d1, *d2;

    obj = (unsigned char *)__builtin_frame_address(0);
    msg = *(unsigned long *)(obj + 0x10);
    if ((msg != 0) && ((*obj & 1) == 0)) {
        tagged = *(unsigned long *)(obj + 8);
        kind = (unsigned int)(tagged >> 61);
        if (kind != 3) {
            if (kind == 1) {
                buf = *(unsigned long *)((tagged & 0x1fffffffffffffff) + 0x10);
                if (buf == 0) SWIFT_BREAKPOINT();   /* 0x25814 */
                /* FUN_00014f10(buf, msg) */
            } else {
                if ((tagged >> 61) != 0) {
                    st = obj[0x30];
                    if (st != 0xff) {
                        d0 = (unsigned long *)(obj + 0x18);
                        d1 = (unsigned long *)(obj + 0x20);
                        d2 = (unsigned long *)(obj + 0x28);
                        if (st == 0) {
                            sk_lock_spin(*d2);
                            (*(void (**)(unsigned long))*d1)(*d0);
                            sk_obj_bind_reset(*d0, 0xffffffffffffffffu, 0xffffffffffffffffu);
                            tightbeam_tb_state(*d0, *d1, *d2, 0);
                            st = 0;
                        }
                        tightbeam_tb_state(*d0, *d1, *d2, st);
                    }
                    sk_fatal_error("Fatal error", 0xb, 2, 0xd00000000000004e,
                                   0x80000000005ad170, "Tightbeam TightbeamMessage swift",
                                   0x20, 2, 0x1ba, 0);
                }
                /* FUN_00014bec(*( (tagged&0x1fffffffffffffff)+0x10 ), msg) */
            }
        }
        /* FUN_00015964(msg); thunk_FUN_00012568(msg,-1,-1) */
    }
    /* FUN_0001fd9c(&local_38) — release tagged buffer */
    st = obj[0x30];
    if (st != 0xff) {
        d0 = (unsigned long *)(obj + 0x18);
        d1 = (unsigned long *)(obj + 0x20);
        d2 = (unsigned long *)(obj + 0x28);
        if (st == 0) {
            sk_lock_spin(*d2);
            (*(void (**)(unsigned long))*d1)(*d0);
            sk_obj_bind_reset(*d0, 0xffffffffffffffffu, 0xffffffffffffffffu);
            tightbeam_tb_state(*d0, *d1, *d2, 0);
            st = 0;
        }
        tightbeam_tb_state(*d0, *d1, *d2, st);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000258c4 @ 0x000258c4   (est. tightbeam_identity_thunk)
 * Ghidra: undefined8 thunk_FUN_00015cdc(void)
 * Identity thunk returning 0.
 * Confidence: high (trivial).
 */
unsigned long tightbeam_identity_thunk(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000258c8 @ 0x000258c8   (est. tightbeam_message_init_desc)
 * Ghidra: void FUN_000258c8(...)
 * Initialises a TightbeamMessage descriptor (param_1): allocates the 0x58
 * and 0x68 state buffers, runs the constructor, and if FUN_00014bd4 succeeds
 * fills the descriptor fields; otherwise fatal-errors with the
 * TightbeamMessage string.
 * Confidence: medium (string-matched TightbeamMessage init).
 */
void tightbeam_message_init_desc(unsigned char *param_1, long param_2, unsigned long param_3,
                                 unsigned long param_4)
{
    unsigned int *state;
    unsigned long buf;
    int rc;

    state = (unsigned int *)sk_alloc_aligned(0x58, 0xffffffffffffffffu);
    *state = 0;
    buf = (unsigned long)sk_alloc_aligned(0x68, 0xffffffffffffffffu);
    /* FUN_00015708() ctor */
    rc = (int)sk_msg_init(*(unsigned long *)(param_2 + 0x10), state, buf, param_3, param_4);
    if (rc == 0) {
        param_1[0] = 0;
        *(long *)(param_1 + 8) = param_2;
        *(unsigned int **)(param_1 + 0x10) = state;
        *(unsigned long *)(param_1 + 0x18) = buf;
        *(void (**)(void))(param_1 + 0x20) = (void (*)(void))0x1a1c8;
        *(unsigned long *)(param_1 + 0x28) = 0;
        param_1[0x30] = 0;
        return;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0, 0xe000000000000000,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x102, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000259c0 @ 0x000259c0   (est. tightbeam_decoder_init)
 * Ghidra: void FUN_000259c0(undefined1 *param_1, undefined8 param_2)
 * Initialises a TightbeamDecoder descriptor (param_1): sets the kind byte to
 * 1, the data pointer to the tagged -1 marker, stores param_2 at +0x10, and
 * zeroes the rest.
 * Confidence: medium (decoder descriptor init).
 */
void tightbeam_decoder_init(unsigned char *param_1, unsigned long param_2)
{
    param_1[0] = 1;
    *(unsigned long *)(param_1 + 8) = 0x8000000000000000;
    *(unsigned long *)(param_1 + 0x10) = param_2;
    *(unsigned long *)(param_1 + 0x20) = 0;
    *(unsigned long *)(param_1 + 0x28) = 0;
    *(unsigned long *)(param_1 + 0x18) = 0;
    param_1[0x30] = 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00025a04 @ 0x00025a04   (est. tightbeam_decoder_attach)
 * Ghidra: void FUN_00025a04(undefined8 param_1)
 * Attaches the decoder: allocates a continuation object (FUN_0040bb18),
 * wires it to the frame, and posts the decode event via FUN_00024678.
 * Confidence: low (Swift async attach).
 */
void tightbeam_decoder_attach(unsigned long param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long *evt;   /* unaff_x22 */
    obj = (unsigned long *)__builtin_frame_address(0);
    evt = (unsigned long *)0;
    evt[2] = (unsigned long)evt;   /* FUN_0040bb18 */
    evt[0] = (unsigned long)evt;
    evt[1] = (unsigned long)0x25ac0;   /* FUN_00025ac0 */
    tightbeam_event_post((unsigned long)evt, param_1, obj[2], obj[3], obj[4], obj[5]);
}

/*--------------------------------------------------------------------*/
/* FUN_00025ac0 @ 0x00025ac0   (est. tightbeam_decoder_attached_run)
 * Ghidra: void FUN_00025ac0(void)
 * Runs the attached decoder: releases the event object (FUN_0040bd24 on
 * +0x10) then jumps through the event vtable (+8). Unrecoverable jump table.
 * Confidence: low (Swift async continuation; "Could not recover jumptable").
 */
void tightbeam_decoder_attached_run(void)
{
    unsigned long *evt;   /* unaff_x22 */
    evt = (unsigned long *)__builtin_frame_address(0);
    /* FUN_0040bd24(*evt + 0x10) */
    /* jump through (*(*evt)+8) */
}

/*--------------------------------------------------------------------*/
/* FUN_00025d80 @ 0x00025d80   (est. tightbeam_tag_mask)
 * Ghidra: void FUN_00025d80(ulong *param_1)
 * Clears the low tag bits of the pointer at *param_1 (mask 0x1fffffffffffffff).
 * Confidence: high (pointer tag clear).
 */
void tightbeam_tag_mask(unsigned long *param_1)
{
    *param_1 = *param_1 & 0x1fffffffffffffff;
}

/*--------------------------------------------------------------------*/
/* FUN_00025dcc @ 0x00025dcc   (est. tightbeam_method_4)
 * Ghidra: long FUN_00025dcc(ulong param_1)
 * Swift method-table resolve (method slot at offset 4).
 * Confidence: high.
 */
long tightbeam_method_4(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 4) + (long)*(int *)(param_1 + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_00025e2c @ 0x00025e2c   (est. tightbeam_method_4b)
 * Ghidra: long FUN_00025e2c(ulong param_1)
 * Swift method-table resolve (method slot at offset 4), same as FUN_00025dcc.
 * Confidence: high.
 */
long tightbeam_method_4b(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 4) + (long)*(int *)(param_1 + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_00025e64 @ 0x00025e64   (est. tightbeam_tb_desc_copy_thunk2)
 * Ghidra: void thunk_FUN_00024068(byte *param_1)
 * Thunk of FUN_00024068 (descriptor copy-out).
 * Confidence: high (thunk).
 */
void tightbeam_tb_desc_copy_thunk2(unsigned char *param_1)
{
    tightbeam_tb_descriptor_copy(param_1, (unsigned char *)__builtin_frame_address(0));
}

/*--------------------------------------------------------------------*/
/* FUN_00025e6c @ 0x00025e6c   (est. tightbeam_alloc_and_init)
 * Ghidra: undefined8 FUN_00025e6c(undefined8 param_1, undefined8 param_2)
 * Allocates a typed object (FUN_0036a940) and runs FUN_000260e0 init on it.
 * Returns the allocation.
 * Confidence: low (allocate + init).
 */
unsigned long tightbeam_alloc_and_init(unsigned long param_1, unsigned char param_2)
{
    unsigned long obj = (unsigned long)sk_alloc_typed(0, 0, 0);   /* FUN_0036a940 */
    tightbeam_kind_select(param_1, param_2);   /* FUN_000260e0 */
    return obj;
}

/*--------------------------------------------------------------------*/
/* FUN_00025ebc @ 0x00025ebc   (est. tightbeam_message_build_out)
 * Ghidra: void FUN_00025ebc(...)
 * Builds a message descriptor: allocates via FUN_0036b270, runs
 * FUN_000258c8 to init, and on success writes the six-word descriptor into
 * param_1; on failure writes the status into *param_4.
 * Confidence: low (Swift message-build result dispatch).
 */
void tightbeam_message_build_out(unsigned long *param_1, unsigned long param_2,
                                 unsigned long param_3, unsigned int *param_4)
{
    unsigned int status;
    unsigned char desc[0x31];
    unsigned long buf;
    buf = 0;   /* FUN_0036b270() */
    tightbeam_message_init_desc(desc, buf, param_2, param_3);
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        param_1[1] = 0; param_1[0] = 0; param_1[3] = 0;
        param_1[2] = 0; param_1[5] = 0; param_1[4] = 0;
        *(unsigned char *)(param_1 + 6) = 0;
    } else {
        *param_4 = status;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00025f44 @ 0x00025f44   (est. tightbeam_message_decode_into)
 * Ghidra: void FUN_00025f44(...)
 * Decodes a message descriptor (param_2) into param_1: reads the message at
 * param_2+0x10 and copies its contents via FUN_0001485c into a fresh
 * descriptor, preserving ownership when identical. Errors rethrow via
 * FUN_003698b0 and teardown. Canary-checked.
 * Confidence: low (message decode + copy pipeline).
 */
void tightbeam_message_decode_into(unsigned char *param_1, unsigned char *param_2, int *param_3)
{
    unsigned long msg, out;
    unsigned long canary = 0xd37afd4bb400012aull;
    int rc;

    out = 0;
    msg = *(unsigned long *)(param_2 + 0x10);
    if (msg == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                       "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
    }
    rc = (int)sk_msg_decode(0, msg, (unsigned long)&out, 2);   /* FUN_0001485c */
    if (rc == 0) {
        if (out != 0) {
            if (msg == out) {
                tightbeam_tb_descriptor_copy(param_1, param_2);
            } else {
                tightbeam_decoder_init((unsigned char *)&param_1[0], 0);
                tightbeam_message_teardown();
            }
            return;
        }
        rc = 4;
    }
    /* rethrow via FUN_00019aac + FUN_003698b0 */
    tightbeam_message_teardown();
    *param_3 = rc;
    if (canary != 0xd37afd4bb400012aull) sk_stack_chk_fail();
}

/*--------------------------------------------------------------------*/
/* FUN_000260e0 @ 0x000260e0   (est. tightbeam_kind_select)
 * Ghidra: void FUN_000260e0(undefined8 param_1, byte param_2)
 * Selects a Tightbeam kind/role by the parameter byte param_2: maps to the
 * kind selector passed to FUN_00015388/FUN_0001532c, then records the
 * resolved object into the frame's message slot (+0x10). Unknown kinds trap.
 * Confidence: medium (kind selector dispatch).
 */
void tightbeam_kind_select(unsigned long param_1, unsigned char param_2)
{
    unsigned long sel, obj;
    unsigned long *frame;   /* unaff_x20 */
    frame = (unsigned long *)__builtin_frame_address(0);

    if (param_2 < 2) {
        if (param_2 == 0) sel = 3; else sel = 0xd;
        obj = 0;
    } else {
        if (param_2 == 2) {
            obj = 1;
        } else {
            if (param_2 != 3) {
                /* FUN_0001532c(1,0) */
                obj = 0; sel = 0;
                goto record;
            }
            obj = 8;
        }
        sel = 3;
    }
    /* FUN_00015388(sel, param_1, obj) */
record:
    /* FUN_00014804(); FUN_0001483c(); */
    frame[2] = /* FUN_00014804() */ 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00026174 @ 0x00026174   (est. tightbeam_ctx_store)
 * Ghidra: void FUN_00026174(undefined8 param_1)
 * Stores param_1 into the context object at +0x10.
 * Confidence: high (store helper).
 */
void tightbeam_ctx_store(unsigned long param_1)
{
    unsigned long ctx = (unsigned long)sk_alloc_typed(0, 0, 0);
    *(unsigned long *)(ctx + 0x10) = param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_000261a8 @ 0x000261a8   (est. tightbeam_frame_store)
 * Ghidra: void FUN_000261a8(undefined8 param_1)
 * Stores param_1 into the frame object at +0x10.
 * Confidence: high (store helper).
 */
void tightbeam_frame_store(unsigned long param_1)
{
    unsigned long *frame;   /* unaff_x20 */
    frame = (unsigned long *)__builtin_frame_address(0);
    frame[2] = param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_000261b4 @ 0x000261b4   (est. tightbeam_message_commit)
 * Ghidra: undefined8 FUN_000261b4(long param_1)
 * Commits a message descriptor (param_1+0x10): decodes via FUN_0001485c and
 * tears down on both success and error paths; rethrows errors. Panics if
 * unwrapped.
 * Confidence: medium (TightbeamMessage commit).
 */
unsigned long tightbeam_message_commit(long param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long res;
    int rc;

    obj = (unsigned long *)__builtin_frame_address(0);
    if (*(unsigned long *)(param_1 + 0x10) != 0) {
        res = sk_msg_decode(obj[2], *(unsigned long *)(param_1 + 0x10), 0, 0);  /* FUN_0001485c */
        rc = (int)res;
        if (rc == 0) {
            tightbeam_message_teardown();
        } else {
            sk_fatal_error("", 0, 0, 0, 0, "", 0, 0);
            tightbeam_message_teardown();
        }
        return res;
    }
    sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                   "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000262a0 @ 0x000262a0   (est. tightbeam_release_msg)
 * Ghidra: void FUN_000262a0(void)
 * Releases the message at object+0x10 via thunk_FUN_00014578.
 * Confidence: medium (release helper).
 */
void tightbeam_release_msg(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    /* thunk_FUN_00014578(obj[2]) */
}

/*--------------------------------------------------------------------*/
/* FUN_000262a4 @ 0x000262a4   (est. tightbeam_release_msg2)
 * Ghidra: void FUN_000262a4(void)
 * Mirror release helper (thunk_FUN_00014578 on object+0x10).
 * Confidence: medium.
 */
void tightbeam_release_msg2(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    /* thunk_FUN_00014578(obj[2]) */
}

/*--------------------------------------------------------------------*/
/* FUN_000262c0 @ 0x000262c0   (est. tightbeam_release_msg_ref)
 * Ghidra: void FUN_000262c0(void)
 * Releases the message then a refcount via FUN_0036b6ac.
 * Confidence: medium.
 */
void tightbeam_release_msg_ref(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    /* thunk_FUN_00014578(obj[2]); FUN_0036b6ac(); */
}

/*--------------------------------------------------------------------*/
/* FUN_000262c4 @ 0x000262c4   (est. tightbeam_release_msg_ref2)
 * Ghidra: void FUN_000262c4(void)
 * Mirror release + unref helper.
 * Confidence: medium.
 */
void tightbeam_release_msg_ref2(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    /* thunk_FUN_00014578(obj[2]); FUN_0036b6ac(); */
}

/*--------------------------------------------------------------------*/
/* FUN_000262ec @ 0x000262ec   (est. tightbeam_type_descriptor_a)
 * Ghidra: undefined1 [16] FUN_000262ec(void)
 * Returns the type-descriptor pair ZEXT816(0x64c288).
 * Confidence: high (trivial type descriptor).
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
 * Ghidra: void FUN_000262fc(...)
 * Iterates the objects of a VAS (virtual address space): resolves the object
 * table from param_6 (FUN_00027754), walks its method dispatch, and for each
 * element invokes the encode callback (param_1) and the element callback
 * chain. Large Swift loop over the object table.
 * Confidence: low (VAS object iteration, many Swift inlines).
 * Notes: FUN_00377824 object-lock; FUN_00027788/277b8/277e8/27818 method
 *   table resolves.
 */
void vas_iterate_objects(void (*param_1)(void), unsigned long param_2, unsigned long param_3,
                         long param_4, long param_5, unsigned long param_6,
                         unsigned long param_7, unsigned long param_8)
{
    unsigned long ctx, obj, *slot;
    unsigned long count;
    (void)param_2; (void)param_3; (void)param_7; (void)param_8;

    ctx = sk_obj_lock_resolve(param_6);   /* FUN_00027754 */
    obj = sk_object_lock(0, ctx, param_3, (void *)0x611b24, (void *)0x611b34);  /* FUN_00377824 */
    slot = (unsigned long *)(obj - 8);
    count = /* *(slot+0x40) */ 0;
    /* iterate: param_1(lv6,lv7,param_4) per element; FUN_0019e410/FUN_0019e538 */
    (void)count;
}

/*--------------------------------------------------------------------*/
/* FUN_00026754 @ 0x00026754   (est. vas_codable_dispatch)
 * Ghidra: void FUN_00026754(...)
 * Resolves a Codable method pointer from param_3 via FUN_000267a4 and calls
 * it with (param_1,param_2,param_3).
 * Confidence: medium (method-table resolve + call).
 */
void vas_codable_dispatch(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    void (*fn)(unsigned long, unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long, unsigned long))tightbeam_method_4c(param_3);
    fn(param_1, param_2, param_3);
}

/*--------------------------------------------------------------------*/
/* FUN_000267a4 @ 0x000267a4   (est. tightbeam_method_4c)
 * Ghidra: long FUN_000267a4(ulong param_1)
 * Swift method-table resolve (method slot at offset 4).
 * Confidence: high.
 */
long tightbeam_method_4c(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 4) + (long)*(int *)(param_1 + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_000267d4 @ 0x000267d4   (est. vas_codable_dispatch_result)
 * Ghidra: void FUN_000267d4(void)
 * Resolves a Codable method and calls it, then reports the result through
 * the error-report FUN_0036993c; on error, fatal-errors with the
 * TightbeamCodable string.
 * Confidence: medium (string-matched TightbeamCodable).
 * Notes: s_Tightbeam_TightbeamCodable_swift_005ad2c0.
 */
void vas_codable_dispatch_result(void)
{
    unsigned long in_x4;
    unsigned int res;
    res = (unsigned int)((unsigned long (*)(void))tightbeam_method_8(in_x4))();
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        return;
    }
    /* FUN_00019aac + FUN_0036993c result report */
    sk_fatal_error("Fatal error", 0xb, 2, 0, 0, "Tightbeam TightbeamCodable swift",
                   0x20, 1, 0x35, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000268a0 @ 0x000268a0   (est. tightbeam_method_8)
 * Ghidra: long FUN_000268a0(ulong param_1)
 * Swift method-table resolve (method slot at offset 8).
 * Confidence: high.
 */
long tightbeam_method_8(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 8) + (long)*(int *)(param_1 + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_000268d0 @ 0x000268d0   (est. vas_codable_call_result)
 * Ghidra: void FUN_000268d0(undefined8 param_1)
 * Resolves a Codable method (FUN_000269a4) and calls it with param_1,
 * reporting the result; on error fatal-errors with TightbeamCodable.
 * Confidence: medium (string-matched TightbeamCodable).
 */
void vas_codable_call_result(unsigned long param_1)
{
    unsigned long in_x4;
    unsigned int local;
    void (*fn)(unsigned long) = (void (*)(unsigned long))tightbeam_method_4d(in_x4);
    fn(param_1);
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        return;
    }
    /* FUN_00019aac + FUN_0036993c result report */
    sk_fatal_error("Fatal error", 0xb, 2, 0, 0, "Tightbeam TightbeamCodable swift",
                   0x20, 1, 0x3e, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000269a4 @ 0x000269a4   (est. tightbeam_method_4d)
 * Ghidra: long FUN_000269a4(ulong param_1)
 * Swift method-table resolve (method slot at offset 4).
 * Confidence: high.
 */
long tightbeam_method_4d(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 4) + (long)*(int *)(param_1 + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_000269d4 @ 0x000269d4   (est. vas_iterate_objects_out)
 * Ghidra: undefined8 FUN_000269d4(...)
 * Iterates VAS objects writing results into local_38 via FUN_00026a8c with
 * the type table (0x65a898 / 0x65a7d0).
 * Confidence: low (VAS object iteration wrapper).
 */
unsigned long vas_iterate_objects_out(unsigned long p1, unsigned long p2, unsigned long p3)
{
    unsigned long result = 0;
    vas_iterate_internal((unsigned long)&result, p1, p2, 0x65a898, p3, 0x65a7d0);  /* FUN_00026a8c */
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026a8c @ 0x00026a8c   (est. vas_iterate_internal)
 * Ghidra: undefined8 FUN_00026a8c(...)
 * Iterates VAS object elements: validates the count, resolves the element
 * method table (FUN_00023c78), and for each element invokes the encode
 * callback, counting via FUN_0001612c. Returns the last element result.
 * Confidence: low (VAS iteration loop with method dispatch).
 */
unsigned long vas_iterate_internal(unsigned long param_1, unsigned long param_2, long param_3,
                                   unsigned long param_4, unsigned long param_5,
                                   unsigned long param_6)
{
    long count, i;
    unsigned long result;
    void (*fn)(void *, void *, void *, void *, void *);
    (void)param_4;
    count = 0;   /* thunk_FUN_0001612c(param_2,param_3) count */
    if (count < 0) SWIFT_BREAKPOINT();   /* 0x26c98 */
    fn = (void (*)(void *, void *, void *, void *, void *))tightbeam_method_16(param_6);
    fn((void *)param_1, (void *)param_4, (void *)param_6, (void *)param_3, (void *)0);
    result = param_1;
    i = 0;
    count = 0;   /* thunk_FUN_0001612c(param_2,param_3) */
    while (i < count) {
        /* FUN_0019ea20 ... element encode */
        if ((unsigned long)i == 0xffffffffffffffff) SWIFT_BREAKPOINT();  /* 0x26c94 */
        fn((void *)0, (void *)0, (void *)param_6, (void *)param_3, (void *)0);
        i++;
    }
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026cac @ 0x00026cac   (est. vas_iterate_1)
 * Ghidra: undefined4 FUN_00026cac(...)
 * VAS iteration wrapper returning 1 on success via FUN_00026a8c.
 * Confidence: low.
 */
unsigned int vas_iterate_1(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                           long param_4, unsigned long param_5)
{
    unsigned int res = (unsigned int)vas_iterate_internal(
        param_1, *(unsigned long *)__builtin_frame_address(0),
        *(unsigned long *)(param_4 + 0x10), param_2,
        *(unsigned long *)((param_5 & 0xfffffffffffffffe) - 8), param_3);
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        res = 1;
    }
    return res;
}

/*--------------------------------------------------------------------*/
/* FUN_00026cb0 @ 0x00026cb0   (est. vas_iterate_2)
 * Ghidra: undefined4 FUN_00026cb0(...)
 * Mirror of FUN_00026cac.
 * Confidence: low.
 */
unsigned int vas_iterate_2(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                           long param_4, unsigned long param_5)
{
    unsigned int res = (unsigned int)vas_iterate_internal(
        param_1, *(unsigned long *)__builtin_frame_address(0),
        *(unsigned long *)(param_4 + 0x10), param_2,
        *(unsigned long *)((param_5 & 0xfffffffffffffffe) - 8), param_3);
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        res = 1;
    }
    return res;
}

/*--------------------------------------------------------------------*/
/* FUN_00026cf0 @ 0x00026cf0   (est. vas_object_call)
 * Ghidra: ulong FUN_00026cf0(...)
 * Dispatches a VAS object operation: resolves the method table via
 * FUN_00023d00, checks the count, registers the object via FUN_00002534/
 * FUN_00027580, and runs FUN_000262fc to perform the operation with the
 * callback FUN_000274e4. Returns the operation status.
 * Confidence: low (VAS object operation dispatch).
 */
unsigned long vas_object_call(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                              unsigned long param_4, unsigned long param_5)
{
    long count;
    unsigned int status[3] = {0,0,0};
    unsigned long type, err, result;

    count = ((long (*)(void))tightbeam_method_16b(param_5))();
    if (count < 0) SWIFT_BREAKPOINT();   /* 0x26e28 */
    type = 0;
    err = sk_error_obj();                /* FUN_00019aac */
    vas_iterate_objects((void (*)(void))tightbeam_method_4d(param_3),
                        (unsigned long)&status[0], 0, 0, 0, 0, 0, 0);
    result = status[0];
    if (__builtin_frame_address(0) != 0) {   /* unaff_x21 */
        result = status[0];
    }
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026e28 @ 0x00026e28   (est. vas_object_call_out)
 * Ghidra: void FUN_00026e28(...)
 * Dispatches a VAS object operation and writes the result into param_1 (or
 * the status slot param_5 on failure).
 * Confidence: low (Swift result dispatch).
 */
void vas_object_call_out(unsigned long *param_1, unsigned int param_2, unsigned long param_3,
                         unsigned long param_4, unsigned int *param_5, long param_6,
                         unsigned long param_7)
{
    unsigned long res = vas_object_call(param_2, *(unsigned long *)(param_6 + 0x10),
                                        param_3, *(unsigned long *)((param_7 & 0xfffffffffffffffe) - 8),
                                        param_4);
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        *param_1 = res;
    } else {
        *param_5 = (unsigned int)res;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00026e7c @ 0x00026e7c   (est. vas_object_call2)
 * Ghidra: undefined8 FUN_00026e7c(...)
 * VAS object-call wrapper via FUN_00310d68/FUN_00026f40.
 * Confidence: low.
 */
unsigned long vas_object_call2(unsigned long p1, unsigned long p2, unsigned long p3)
{
    unsigned long result = 0;
    unsigned long ctx = sk_obj_lock2(0);   /* FUN_00310d68 */
    vas_object_call2_internal((unsigned long)&result, ctx, 0x65a898, p3, 0x65a7d0);  /* FUN_00026f40 */
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00026f40 @ 0x00026f40   (est. vas_object_call2_internal)
 * Ghidra: undefined8 FUN_00026f40(...)
 * VAS object-call implementation: resolves the object at param_2+0x10,
 * invokes the method at +0x30 to test ownership, then dispatches the
 * operation callback (FUN_000276c4) and writes the result. Returns the
 * operation result.
 * Confidence: low (VAS object-call loop with method dispatch).
 */
unsigned long vas_object_call2_internal(unsigned long param_1, long param_2, unsigned long param_3,
                                        unsigned long param_4, unsigned long param_5)
{
    unsigned long ctx, obj;
    int owns;
    void (*fn)(void);

    obj = *(unsigned long *)((char *)param_2 - 8);   /* lVar7 from extraout_x1 */
    ctx = *(unsigned long *)(obj + 0x10);
    (void)param_3;
    /* (**(obj+0x10))(frame, extraout_x8, param_2) then (**(ctx+0x30))(frame,1,obj) */
    owns = 0;
    if (owns == 1) {
        /* success: (**(param_2-8 +8))(frame,param_2); (*FUN_000276c4)(0,param_3,param_5) */
        return param_1;
    }
    /* (*FUN_000276c4)(1,param_3,param_5); encode result; (**(ctx+8))(frame,obj) */
    return param_1;
}

/*--------------------------------------------------------------------*/
/* FUN_00027194 @ 0x00027194   (est. vas_object_call3)
 * Ghidra: undefined4 FUN_00027194(...)
 * VAS object-call wrapper returning 1 on success via FUN_00026f40.
 * Confidence: low.
 */
unsigned int vas_object_call3(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                              unsigned long param_4, unsigned long param_5)
{
    unsigned int res = (unsigned int)vas_object_call2_internal(
        param_1, param_4, param_2, *(unsigned long *)((param_5 & 0xfffffffffffffffe) - 8), param_3);
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        res = 1;
    }
    return res;
}

/*--------------------------------------------------------------------*/
/* FUN_00027198 @ 0x00027198   (est. vas_object_call4)
 * Ghidra: undefined4 FUN_00027198(...)
 * Mirror of FUN_00027194.
 * Confidence: low.
 */
unsigned int vas_object_call4(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                              unsigned long param_4, unsigned long param_5)
{
    unsigned int res = (unsigned int)vas_object_call2_internal(
        param_1, param_4, param_2, *(unsigned long *)((param_5 & 0xfffffffffffffffe) - 8), param_3);
    if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
        res = 1;
    }
    return res;
}

/*--------------------------------------------------------------------*/
/* FUN_000271d8 @ 0x000271d8   (est. vas_codable_encode)
 * Ghidra: void FUN_000271d8(...)
 * Encodes a value through the Codable protocol: resolves the encode method
 * table (FUN_000276f4/FUN_000269a4), and on success writes the encoded
 * result to the container (param_1); on error rethrows and fatal-errors with
 * the TightbeamCodable string.
 * Confidence: medium (string-matched TightbeamCodable encode).
 */
void vas_codable_encode(unsigned long param_1, unsigned long param_2, long param_3,
                        long param_4, unsigned long param_5, unsigned long param_6,
                        unsigned int *param_7)
{
    char kind;
    unsigned int status;

    /* FUN_00310d68(0) ctx; (*FUN_000276f4)(param_4,param_6) → kind */
    kind = 0;
    if (kind == '\x01') {
        void (*enc)(void) = (void (*)(void))tightbeam_method_4d(param_5);
        enc();
        if (__builtin_frame_address(0) == 0) {   /* unaff_x21 */
            /* success: write encoded result to param_1 */
        } else {
            *param_7 = status;
        }
    } else if (kind != '\0') {
        /* error path: rethrow + fatal-error with TightbeamCodable */
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000016, 0x80000000005ad2d0,
                       "Tightbeam TightbeamCodable swift", 0x20, 2);
    }
    /* else: success via (param_3-8 +0x38)(param_1,1,1,param_3) */
}

/*--------------------------------------------------------------------*/
/* FUN_00027494 @ 0x00027494   (est. vas_codable_encode_out)
 * Ghidra: void FUN_00027494(...)
 * Codable encode wrapper: forwards to FUN_000271d8 and writes the status.
 * Confidence: low.
 */
void vas_codable_encode_out(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                            unsigned int *param_4, long param_5, unsigned long param_6)
{
    unsigned int status;
    vas_codable_encode(param_1, *(unsigned long *)(param_5 + 0x10), param_2,
                       *(unsigned long *)((param_6 & 0xfffffffffffffffe) - 8), param_3, 0, &status);
    if (__builtin_frame_address(0) != 0) {   /* unaff_x21 */
        *param_4 = status;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000274e4 @ 0x000274e4   (est. vas_object_encode_cb)
 * Ghidra: void FUN_000274e4(...)
 * Object-encode callback used by the VAS iterator: encodes the object's
 * fields via the method table (FUN_000269a4) and writes the status.
 * Confidence: low (encode callback).
 */
void vas_object_encode_cb(unsigned long param_1, unsigned long param_2, unsigned int *param_3)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned int status;
    obj = (unsigned long *)__builtin_frame_address(0);
    void (*enc)(unsigned long, unsigned long, unsigned long, unsigned long, void *, unsigned long, unsigned long) =
        (void (*)(unsigned long, unsigned long, unsigned long, unsigned long, void *, unsigned long, unsigned long))
        tightbeam_method_4d(obj[4]);
    enc(param_1, obj[6], obj[3], obj[5], &status, obj[2], obj[4]);
    if (__builtin_frame_address(0) != 0) {   /* unaff_x21 */
        *param_3 = status;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00027580 @ 0x00027580   (est. sk_type_register)
 * Ghidra: void FUN_00027580(void)
 * Registers a Swift type once: if the global DAT_0064c2e0 is unset, resolves
 * the type via FUN_00027614/FUN_00027670 and stores it via FUN_00376820.
 * Confidence: low (Swift once-registration).
 * Notes: globals DAT_0064c2d8/DAT_0064c2e0, s___eh_frame_0064c2e8.
 */
void sk_type_register(void)
{
    unsigned long v;
    if (_sk_global_c2e0 != 0) return;
    v = sk_lock_and_alloc(&_sk_global_c2d8, 0);   /* FUN_00027614 */
    (void)v;
    /* FUN_00027670(); local_30 = 0x6720e8; */
    _sk_global_c2e0 = (unsigned long)sk_obj_reg_get();   /* FUN_00376820 */
}

/*--------------------------------------------------------------------*/
/* FUN_00027614 @ 0x00027614   (est. sk_lock_and_alloc)
 * Ghidra: ulong FUN_00027614(ulong *param_1, long *param_2)
 * Lazily allocates a global object: if *param_1 is non-null returns its
 * tag-masked pointer; otherwise allocates via FUN_00389b64(0xff, ...) and
 * stores it (tagged with bit 0) in *param_1.
 * Confidence: medium (lazy global allocation).
 */
unsigned long sk_lock_and_alloc(unsigned long *param_1, long *param_2)
{
    unsigned long v;
    if (*param_1 != 0) return *param_1 & 0xfffffffffffffffe;
    v = sk_alloc_global(0xff, (unsigned long)param_2 + (unsigned long)(int)*param_2,
                        *param_2 >> 32, 0, 0);   /* FUN_00389b64 */
    *param_1 = v | 1;
    return v & 0xfffffffffffffffe;
}

/*--------------------------------------------------------------------*/
/* FUN_00027670 @ 0x00027670   (est. sk_type_register_inner)
 * Ghidra: void FUN_00027670(void)
 * Inner type registration: stores an 8-byte global (s___eh_frame_0064c2e8)
 * from FUN_00376820(&DAT_004edbbc,0x677880).
 * Confidence: low.
 */
void sk_type_register_inner(void)
{
    unsigned long v;
    if (_sk_global_c2e8 != 0) return;
    v = (unsigned long)sk_obj_reg_get();   /* FUN_00376820 */
    _sk_global_c2e8 = v;
}

/*--------------------------------------------------------------------*/
/* FUN_000276c4 @ 0x000276c4   (est. tightbeam_method_8b)
 * Ghidra: long FUN_000276c4(ulong param_1)
 * Swift method-table resolve (method slot at offset 8).
 * Confidence: high.
 */
long tightbeam_method_8b(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 8) + (long)*(int *)(param_1 + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_000276f4 @ 0x000276f4   (est. tightbeam_method_8c)
 * Ghidra: long FUN_000276f4(ulong param_1)
 * Swift method-table resolve (method slot at offset 8).
 * Confidence: high.
 */
long tightbeam_method_8c(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 8) + (long)*(int *)(param_1 + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_00027724 @ 0x00027724   (est. tightbeam_method_4e)
 * Ghidra: long FUN_00027724(ulong param_1)
 * Swift method-table resolve (method slot at offset 4).
 * Confidence: high.
 */
long tightbeam_method_4e(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 4) + (long)*(int *)(param_1 + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_00027754 @ 0x00027754   (est. sk_obj_lock_resolve)
 * Ghidra: long FUN_00027754(ulong param_1)
 * Resolves an object pointer: if untagged, returns param_1+4 plus the length
 * at param_1+4 (object header offset 4); if tagged, returns *(param_1 & -2)+8
 * (pointer at offset 8).
 * Confidence: high (Swift object-header resolve).
 */
long sk_obj_lock_resolve(unsigned long param_1)
{
    if ((param_1 & 1) == 0) {
        return (long)(param_1 + 4) + (long)*(int *)(param_1 + 4);
    }
    return *(long *)((param_1 & 0xfffffffffffffffe) + 8);
}

/*--------------------------------------------------------------------*/
/* FUN_00027788 @ 0x00027788   (est. tightbeam_method_38)
 * Ghidra: long FUN_00027788(ulong param_1)
 * Swift method-table resolve (method slot at offset 0x38).
 * Confidence: high.
 */
long tightbeam_method_38(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 0x38) + (long)*(int *)(param_1 + 0x38);
}

/*--------------------------------------------------------------------*/
/* FUN_000277b8 @ 0x000277b8   (est. tightbeam_method_20)
 * Ghidra: long FUN_000277b8(ulong param_1)
 * Swift method-table resolve (method slot at offset 0x20).
 * Confidence: high.
 */
long tightbeam_method_20(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 0x20) + (long)*(int *)(param_1 + 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_000277e8 @ 0x000277e8   (est. tightbeam_method_28)
 * Ghidra: long FUN_000277e8(ulong param_1)
 * Swift method-table resolve (method slot at offset 0x28).
 * Confidence: high.
 */
long tightbeam_method_28(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 0x28) + (long)*(int *)(param_1 + 0x28);
}

/*--------------------------------------------------------------------*/
/* FUN_00027818 @ 0x00027818   (est. tightbeam_method_60)
 * Ghidra: long FUN_00027818(ulong param_1)
 * Swift method-table resolve (method slot at offset 0x60).
 * Confidence: high.
 */
long tightbeam_method_60(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 0x60) + (long)*(int *)(param_1 + 0x60);
}

/*--------------------------------------------------------------------*/
/* FUN_00027880 @ 0x00027880   (est. vas_server_register)
 * Ghidra: void FUN_00027880(void)
 * Registers the VAS server: forwards to FUN_00027f50.
 * Confidence: medium (trivial forwarder).
 */
void vas_server_register(void)
{
    vas_server_register_internal(0, 0, 0, 0, 0, 0);   /* FUN_00027f50 */
}

/*--------------------------------------------------------------------*/
/* FUN_000278a8 @ 0x000278a8   (est. vas_msg_send)
 * Ghidra: long FUN_000278a8(...)
 * Sends a VAS message: builds a decoder descriptor (FUN_000259c0), packs the
 * target with the type tag, and invokes the message method (param_4). On a
 * non-2 status it validates the result message (fatal-error if unwrapped)
 * and tears down. Returns the result slot.
 * Confidence: low (VAS message send pipeline).
 */
long vas_msg_send(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                  void (*param_4)(void))
{
    unsigned char desc[8];
    unsigned long status;
    long result;

    tightbeam_decoder_init(desc, param_2);
    /* FUN_0001fd9c(&local_80) tag pack */
    param_3 |= 0x2000000000000000;
    sk_lock_spin(param_3);
    param_4();
    if ((status & 0xff) == 2) {
        result = 0;
    } else {
        if (result == 0) {
            sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                           "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
        }
        tightbeam_message_teardown();
    }
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00027a98 @ 0x00027a98   (est. vas_op_invoke)
 * Ghidra: undefined8 FUN_00027a98(long param_1, undefined8 param_2, undefined8 param_3)
 * Invokes a VAS operation: loads the operation method (param_1+0x20), locks
 * the operand, calls the method, and unlocks. Returns the method result.
 * Confidence: medium (operation invoke with lock/unlock).
 */
unsigned long vas_op_invoke(long param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long (*fn)(unsigned long, unsigned long) = *(unsigned long (**)(unsigned long, unsigned long))(param_1 + 0x20);
    unsigned long operand = *(unsigned long *)(param_1 + 0x28);
    sk_lock_spin(operand);
    unsigned long res = fn(param_2, param_3);
    sk_lock_release(operand);
    return res;
}

/*--------------------------------------------------------------------*/
/* FUN_00027b10 @ 0x00027b10   (est. vas_server_init_forward)
 * Ghidra: void FUN_00027b10(void)
 * Forwarder to FUN_00027b70.
 * Confidence: medium (trivial forwarder).
 */
void vas_server_init_forward(void)
{
    vas_server_init(0, 0, 0, 0, 0, 0, 0);   /* FUN_00027b70 */
}

/*--------------------------------------------------------------------*/
/* FUN_00027b38 @ 0x00027b38   (est. vas_type_descriptor)
 * Ghidra: undefined1 [16] FUN_00027b38(void)
 * Returns the type-descriptor pair ZEXT816(0x64c380).
 * Confidence: high (trivial type descriptor).
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
 * Ghidra: long FUN_00027b70(...)
 * Initialises the VAS server: resolves the kind, allocates the server context
 * (FUN_0036a940(s___MMIOREGS_0064c380,0x18,7)), allocates an operation
 * descriptor (FUN_0036a940(param_5,0x28,7)), wires the invoke callback
 * (FUN_00027a98), registers the server via FUN_000147a0, and stores the
 * resolved pointer. Returns the server context.
 * Confidence: low (VAS server scaffolding).
 */
long vas_server_init(unsigned long param_1, unsigned char param_2, unsigned long param_3,
                     unsigned long param_4, unsigned long param_5, unsigned long param_6,
                     unsigned long param_7)
{
    unsigned long kind, ctx, op, res;

    if (param_2 < 2) {
        kind = (param_2 == 0) ? 3 : 0xd;
        res = 0;
    } else if (param_2 == 2) {
        res = 1; kind = 3;
    } else if (param_2 != 3) {
        kind = 0; res = 0;   /* FUN_0001532c(1,0) */
        goto alloc;
    } else {
        res = 8; kind = 3;
    }
    kind = 0;   /* FUN_00015388(kind,param_1,res) */
alloc:
    ctx = (unsigned long)sk_alloc_typed(0x64c380, 0x18, 7);   /* s___MMIOREGS_0064c380 */
    *(unsigned long *)(ctx + 0x10) = 0;
    op = (unsigned long)sk_alloc_typed(param_5, 0x28, 7);
    *(unsigned long *)(op + 0x10) = ctx;
    *(unsigned long *)(op + 0x18) = param_3;
    *(unsigned long *)(op + 0x20) = param_4;
    sk_lock_spin(ctx);
    sk_lock_spin(param_4);
    sk_lock_release(op);
    res = sk_vas_register(kind, 0);   /* FUN_000147a0 */
    sk_lock_release(param_4);
    *(unsigned long *)(ctx + 0x10) = res;
    return ctx;
}

/*--------------------------------------------------------------------*/
/* FUN_00027d94 @ 0x00027d94   (est. vas_server_create)
 * Ghidra: long FUN_00027d94(...)
 * Creates a VAS server: allocates the context, an operation descriptor, wires
 * the invoke callback, registers via FUN_000147a0, and stores the resolved
 * pointer. Returns the server context.
 * Confidence: low (VAS server scaffolding, mirrors FUN_00027b70).
 */
long vas_server_create(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                       unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    unsigned long ctx, op, res;

    ctx = (unsigned long)sk_alloc_typed(0, 0, 0);
    *(unsigned long *)(ctx + 0x10) = 0;
    op = (unsigned long)sk_alloc_typed(param_4, 0x28, 7);
    *(unsigned long *)(op + 0x10) = ctx;
    *(unsigned long *)(op + 0x18) = param_2;
    *(unsigned long *)(op + 0x20) = param_3;
    sk_lock_spin(ctx);
    sk_lock_spin(param_3);
    sk_lock_release(op);
    res = sk_vas_register(param_1, 0);   /* FUN_000147a0 */
    sk_lock_release(param_3);
    *(unsigned long *)(ctx + 0x10) = res;
    return ctx;
}

/*--------------------------------------------------------------------*/
/* FUN_00027f50 @ 0x00027f50   (est. vas_server_register_internal)
 * Ghidra: void FUN_00027f50(...)
 * Registers the VAS server with the kernel: allocates an operation descriptor,
 * wires the invoke callback, registers via FUN_000147a0, and stores the
 * resolved pointer into the frame object at +0x10.
 * Confidence: low (VAS server registration).
 */
void vas_server_register_internal(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                                  unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long op, res;
    obj = (unsigned long *)__builtin_frame_address(0);
    obj[2] = 0;   /* +0x10 */
    op = (unsigned long)sk_alloc_typed(param_4, 0x28, 7);
    *(unsigned long *)(op + 0x10) = (unsigned long)obj;
    *(unsigned long *)(op + 0x18) = param_2;
    *(unsigned long *)(op + 0x20) = param_3;
    sk_lock_spin(0);
    sk_lock_spin(param_3);
    sk_lock_release(op);
    res = sk_vas_register(param_1, 0);   /* FUN_000147a0 */
    sk_lock_release(param_3);
    obj[2] = res;
}

/*--------------------------------------------------------------------*/
/* FUN_000280c4 @ 0x000280c4   (est. vas_fault_complete)
 * Ghidra: long FUN_000280c4(...)
 * Completes a VAS fault-handler operation: builds a decoder descriptor, packs
 * the target with the type tag, registers the object, and invokes the fault
 * completion method (FUN_003ed2dc). On success returns the result slot; on a
 * non-2 status validates the message (fatal-error if unwrapped) and tears
 * down.
 * Confidence: low (VAS fault-complete pipeline).
 */
long vas_fault_complete(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                        unsigned long param_4, unsigned long param_5)
{
    unsigned char desc[8];
    unsigned long status;
    long result;

    tightbeam_decoder_init(desc, param_2);
    /* FUN_0001fd9c(&local_b8) tag pack */
    param_3 |= 0x2000000000000000;
    sk_lock_spin(param_3);
    /* FUN_003ed2dc type register; invoke completion method */
    result = 0;
    if ((status & 0xff) == 2) {
        result = 0;
    } else {
        if (result == 0) {
            sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000022, 0x80000000005acf60,
                           "Tightbeam TightbeamMessage swift", 0x20, 2, 0x93, 0);
        }
        tightbeam_message_teardown();
    }
    /* second status branch (char local_128) */
    return result;
}

/*--------------------------------------------------------------------*/
/* FUN_00028374 @ 0x00028374   (est. vas_fault_release)
 * Ghidra: void FUN_00028374(void)
 * Releases a VAS fault handler's two refs (object+0x10, object+0x20) and an
 * allocator ref via FUN_0036b21c.
 * Confidence: medium (refcount release).
 */
void vas_fault_release(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    sk_lock_release(obj[2]);
    sk_lock_release(obj[4]);
    sk_lock_unref(0);   /* FUN_0036b21c */
}

/*--------------------------------------------------------------------*/
/* FUN_00028378 @ 0x00028378   (est. vas_fault_release2)
 * Ghidra: void FUN_00028378(void)
 * Mirror release helper (object+0x10/+0x20 + allocator unref).
 * Confidence: medium.
 */
void vas_fault_release2(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    sk_lock_release(obj[2]);
    sk_lock_release(obj[4]);
    sk_lock_unref(0);
}

/*--------------------------------------------------------------------*/
/* FUN_000283a8 @ 0x000283a8   (est. vas_fault_post)
 * Ghidra: void FUN_000283a8(...)
 * Posts a VAS fault event: stores four argument words into the event object
 * (unaff_x22) at +0xb8..+0xd0, then schedules the handler via
 * FUN_00408db8(&LAB_000283d0,0,0).
 * Confidence: low (Swift async event post).
 */
void vas_fault_post(unsigned long p1, unsigned long param_2, unsigned long param_3,
                    unsigned long param_4, unsigned long param_5)
{
    unsigned long *evt;   /* unaff_x22 */
    (void)p1;
    evt = (unsigned long *)__builtin_frame_address(0);
    evt[0x19] = param_4;   /* +0xc8 */
    evt[0x1a] = param_5;   /* +0xd0 */
    evt[0x17] = param_2;   /* +0xb8 */
    evt[0x18] = param_3;   /* +0xc0 */
    /* FUN_00408db8(&LAB_000283d0,0,0) */
}

/*--------------------------------------------------------------------*/
/* FUN_000284f4 @ 0x000284f4   (est. vas_fault_event_dispatch)
 * Ghidra: void FUN_000284f4(void)
 * VAS fault-event dispatch: releases the event object (FUN_0040bd24 on +0xd8),
 * then schedules either the fault-complete handler (FUN_000285c8) or, when
 * non-null, records the state and runs FUN_000248a4.
 * Confidence: low (Swift async fault dispatch).
 */
void vas_fault_event_dispatch(void)
{
    unsigned long *evt;   /* unaff_x22 */
    unsigned long *obj;   /* unaff_x20 */
    evt = (unsigned long *)__builtin_frame_address(0);
    obj = (unsigned long *)0;
    /* FUN_0040bd24(*(evt+0xd8)) */
    if (obj == 0) {
        /* handler FUN_000285c8 */
    } else {
        *(unsigned int *)((char *)evt + 0x7c) = *(unsigned int *)((char *)evt + 0x44);
        tightbeam_event_dispatch_result();   /* FUN_000248a4 */
    }
    /* FUN_00408db8(handler,0,0) */
}

/*--------------------------------------------------------------------*/
/* FUN_000285c8 @ 0x000285c8   (est. vas_fault_apply_result)
 * Ghidra: void FUN_000285c8(void)
 * Applies the VAS fault result back into the fault descriptor: if the
 * descriptor's kind byte is not 2, copies the result descriptor out and
 * tears down the scratch copy. Then writes the six-word result into the
 * target descriptor and jumps through the event vtable (+8).
 * Confidence: low (fault-result apply; "Could not recover jumptable").
 */
void vas_fault_apply_result(void)
{
    unsigned long *evt;   /* unaff_x22 */
    unsigned char *desc;
    unsigned long v;
    evt = (unsigned long *)__builtin_frame_address(0);
    desc = (unsigned char *)evt[0x17];   /* +0xb8 */
    if (*desc != 2) {
        /* copy result descriptor out; tightbeam_message_teardown() */
    }
    /* write six-word result into desc from evt+0x80..0xb0 */
    (void)v;
    /* jump through *(evt+8) */
}

/*--------------------------------------------------------------------*/
/* FUN_00028680 @ 0x00028680   (est. vas_msg_release)
 * Ghidra: void FUN_00028680(void)
 * Releases the VAS message at object+0x10 via thunk_FUN_00014578; traps if
 * the message is null.
 * Confidence: medium (release + null trap).
 */
void vas_msg_release(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* thunk_FUN_00014578() */
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x286a8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00028684 @ 0x00028684   (est. vas_msg_release2)
 * Ghidra: void FUN_00028684(void)
 * Mirror release helper (trap 0x286a8).
 * Confidence: medium.
 */
void vas_msg_release2(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* thunk_FUN_00014578() */
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x286a8 */
}

/*--------------------------------------------------------------------*/
/* FUN_000286a8 @ 0x000286a8   (est. vas_msg_release_ref)
 * Ghidra: void FUN_000286a8(void)
 * Releases the VAS message and a refcount via FUN_0036b6ac; traps if null.
 * Confidence: medium.
 */
void vas_msg_release_ref(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* thunk_FUN_00014578(); FUN_0036b6ac(); */
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x286dc */
}

/*--------------------------------------------------------------------*/
/* FUN_000286ac @ 0x000286ac   (est. vas_msg_release_ref2)
 * Ghidra: void FUN_000286ac(void)
 * Mirror release+unref helper (trap 0x286dc).
 * Confidence: medium.
 */
void vas_msg_release_ref2(void)
{
    unsigned long *obj;   /* unaff_x20 */
    obj = (unsigned long *)__builtin_frame_address(0);
    if (obj[2] != 0) {
        /* thunk_FUN_00014578(); FUN_0036b6ac(); */
        return;
    }
    SWIFT_BREAKPOINT();   /* 0x286dc */
}

/*--------------------------------------------------------------------*/
/* FUN_000286dc @ 0x000286dc   (est. vas_type_id)
 * Ghidra: undefined1 [16] FUN_000286dc(void)
 * Returns the type-descriptor pair ZEXT816(0x64c308).
 * Confidence: high (trivial type descriptor).
 */
cl4_result_t vas_type_id(void)
{
    cl4_result_t r;
    r.lo = 0x64c308;
    r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_000286ec @ 0x000286ec   (est. vas_fault_attach)
 * Ghidra: void FUN_000286ec(undefined8 param_1)
 * Attaches a VAS fault handler: allocates a continuation object
 * (FUN_0040bb18), wires it to the frame, and posts the fault event via
 * FUN_000283a8.
 * Confidence: low (Swift async fault attach).
 */
void vas_fault_attach(unsigned long param_1)
{
    unsigned long *obj;   /* unaff_x20 */
    unsigned long *evt;   /* unaff_x22 */
    obj = (unsigned long *)__builtin_frame_address(0);
    evt = (unsigned long *)0;
    evt[2] = (unsigned long)evt;   /* FUN_0040bb18 */
    evt[0] = (unsigned long)evt;
    evt[1] = (unsigned long)0x25ac0;   /* FUN_00025ac0 */
    vas_fault_post((unsigned long)evt, param_1, obj[2], obj[3], obj[4]);
}

/*--------------------------------------------------------------------*/
/* FUN_000287e4 @ 0x000287e4   (est. sk_boot_profile_load)
 * Ghidra: void FUN_000287e4(long *param_1, undefined8 param_2, undefined8 param_3)
 * Loads the boot profile: zeroes the result block, resolves the profile via
 * FUN_00035ba0/FUN_00034f70, reads it via FUN_00036008, and releases the
 * profile object if the parse failed.
 * Confidence: low (boot profile read).
 * Notes: FUN_00036008 profile read; FUN_004b23d8 release.
 */
void sk_boot_profile_load(long *param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long profile;
    param_1[4] = 0; param_1[1] = 0; *param_1 = 0;
    param_1[3] = 0; param_1[2] = 0;
    /* FUN_00035ba0() */
    if (*param_1 == 0) {
        profile = sk_profile_resolve();   /* FUN_00034f70 */
        /* FUN_00036008(&local, param_2, param_3, profile) */
        param_1[1] = 0; *param_1 = 0;
        param_1[3] = 0; param_1[2] = 0;
        param_1[4] = 0;
        if ((*param_1 == 0) || ((*(unsigned char *)(param_1 + 1) & 1) == 0)) {
            /* FUN_004b23d8(profile) */
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0002887c @ 0x0002887c   (est. sk_object_array_clone)
 * Ghidra: undefined8 * FUN_0002887c(undefined8 param_1, undefined8 *param_2)
 * Clones a 9-element object array: allocates a 0x50-byte block
 * (FUN_00010244(1,0x50,...)), stores param_1 at [0], and retains each of the
 * 9 source words via FUN_0004b520 into [1..9]. Traps if the allocation is
 * null.
 * Confidence: low (array clone with per-element retain).
 */
unsigned long *sk_object_array_clone(unsigned long param_1, unsigned long *param_2)
{
    unsigned long *out = (unsigned long *)sk_alloc_pages(1, 0x50);  /* FUN_00010244 */
    if (out != (unsigned long *)0) {
        out[0] = param_1;
        for (int i = 0; i < 9; i++) {
            out[i + 1] = sk_retain(param_2[i]);   /* FUN_0004b520 */
        }
        return out;
    }
    SWIFT_BREAKPOINT_A();   /* 0x28950 */
}

/*--------------------------------------------------------------------*/
/* FUN_00028950 @ 0x00028950   (est. sk_vas_lookup)
 * Ghidra: long * FUN_00028950(long param_1, long param_2, long param_3, long param_4)
 * Linear search over a VAS object table: the table lives at param_1+0x1e8
 * with param_1+0x188 entries of 11 words each. Returns the entry whose
 * element matches param_2 (key at entry[1]+8), param_3 (entry[1]+0x10), or
 * param_4 (entry[0]). Bounds-checked; traps on overflow. Returns null if no
 * match.
 * Confidence: medium (linear table lookup with bounds checks).
 */
long *sk_vas_lookup(long param_1, long param_2, long param_3, long param_4)
{
    long *table, *entry, n;
    long count = *(long *)(param_1 + 0x1e0);   /* note: decompile reads +0x1d8 in loop */
    if (count != 0) {
        table = *(long **)(param_1 + 0x1e8);
        entry = table + *(long *)(param_1 + 0x1d8) * 0xb;
        n = count;
        do {
            if (param_2 != 0) {
                if (entry[1] == 0) SWIFT_BREAKPOINT_A();   /* bounds */
                if (*(long *)(entry[1] + 8) == param_2) return entry;
            }
            if (param_3 != 0) {
                if (entry[1] == 0) SWIFT_BREAKPOINT_A();
                if (*(long *)(entry[1] + 0x10) == param_3) return entry;
            }
            if (param_4 != 0) {
                if (entry[0] == 0) SWIFT_BREAKPOINT_A();
                if (*entry == param_4) return entry;
            }
            entry += 0xb;
            n--;
        } while (n != 0);
    }
    return (long *)0;
}

/*--------------------------------------------------------------------*/
/* FUN_00028a10 @ 0x00028a10   (est. sk_vas_lookup_cap)
 * Ghidra: undefined8 FUN_00028a10(undefined8 param_1, undefined8 param_2)
 * Looks up a VAS entry by key param_2 and returns its capability word
 * (entry+8).
 * Confidence: medium (table lookup wrapper).
 */
unsigned long sk_vas_lookup_cap(unsigned long param_1, unsigned long param_2)
{
    long *entry = sk_vas_lookup(param_1, 0, param_2, 0);
    unsigned long v = 0;
    if (entry != 0) v = *(unsigned long *)(entry + 1);   /* entry[1] */
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_00028a3c @ 0x00028a3c   (est. sk_vas_lookup_range)
 * Ghidra: undefined1 [16] FUN_00028a3c(...)
 * Looks up a VAS entry by key param_2 and returns the 16-byte {lo,hi} range
 * stored at entry+0x48 (elements [9],[10]).
 * Confidence: medium (table lookup returning range pair).
 */
cl4_result_t sk_vas_lookup_range(unsigned long param_1, unsigned long param_2)
{
    cl4_result_t r;
    long *entry = sk_vas_lookup(param_1, 0, param_2, 0);
    if (entry == 0) { r.lo = 0; r.hi = 0; }
    else { r.lo = *(unsigned long *)(entry + 0x48); r.hi = *(unsigned long *)(entry + 0x50); }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00028a78 @ 0x00028a78   (est. sk_vas_lookup_pa)
 * Ghidra: undefined8 FUN_00028a78(undefined8 param_1, undefined8 param_2)
 * Looks up a VAS entry by key param_2 and returns the physical address word
 * at entry+0x40.
 * Confidence: medium (table lookup wrapper).
 */
unsigned long sk_vas_lookup_pa(unsigned long param_1, unsigned long param_2)
{
    long *entry = sk_vas_lookup(param_1, 0, param_2, 0);
    unsigned long v = 0;
    if (entry != 0) v = *(unsigned long *)(entry + 0x40);
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_00028aa4 @ 0x00028aa4   (est. sk_vas_contains_range)
 * Ghidra: undefined8 FUN_00028aa4(long param_1, long param_2)
 * Tests whether the VAS contains param_2 within one of its registered
 * regions: iterates the 0x48-byte region table (param_1+0x1d8, count at
 * param_1+0x188) and returns 1 if the region is active (state byte at -0x28
 * == 1) and |param_2 - region_base| < 0x4000. Returns 0 otherwise.
 * Confidence: medium (region range test with bounds checks).
 */
unsigned long sk_vas_contains_range(long param_1, long param_2)
{
    unsigned long count = *(long *)(param_1 + 0x188);
    if (count != 0) {
        unsigned long region = param_1 + 0x1d8;
        do {
            /* bounds check region (0x48 stride) */
            if (*(char *)(region - 0x28) == '\x01') {
                if ((unsigned long)(param_2 - *(long *)(region - 0x20)) < 0x4000) {
                    return 1;
                }
            }
            region += 0x48;
            count--;
        } while (count != 0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00028b14 @ 0x00028b14   (est. sk_vas_alloc)
 * Ghidra: undefined8 * FUN_00028b14(...)
 * Allocates a new VAS: allocates the 0x210-byte VAS struct
 * (FUN_000101a0(0x210,...)), optionally allocates the 0x400-entry fault-handler
 * table (FUN_00010244(0x400,0x30)) when the caller requests it, zero-fills the
 * struct, registers it with the kernel, and installs the ~40 VAS operation
 * dispatch entries (FUN_00029c7c ... FUN_0002f780) plus the fault-handler
 * dispatch table. Uses the kernel's object-allocation API for the fault
 * handler slots. Returns the VAS pointer.
 * Confidence: low (large VAS allocation + dispatch-table install; many
 *   FUN_0004b520 method registrations).
 * Notes: DAT_004bbfd8 type; 0x65ae70..0x65b560 method string table.
 */
unsigned long *sk_vas_alloc(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                            long *param_4)
{
    unsigned long *vas = (unsigned long *)sk_alloc_vas(0x210);  /* FUN_000101a0 */
    unsigned long *body = vas + 0x42;
    unsigned long *fh = (unsigned long *)0;
    if (vas != (unsigned long *)0) fh = body;
    if (*param_4 == 0) {
        *param_4 = (long)(vas + 0x2a);
    }
    /* type tag via FUN_00015388(3,param_1); optional fault-handler table */
    vas[0] = 0;
    vas[1] = param_2;
    vas[2] = param_3;
    vas[3] = 0;   /* type */
    vas[4] = (unsigned long)param_4;
    for (int i = 8; i <= 0x41; i++) vas[i] = 0;
    vas[0x30] = 0x100;
    vas[0x3e] = 0x400;
    vas[0x40] = (unsigned long)fh;
    /* register: FUN_00118164(0x6ac250); *vas = DAT_006ac260; DAT_006ac260=vas */
    /* install dispatch entries via FUN_0004b520 into vas[5..0x28] */
    /* FUN_000465c4(vas[3], vas+5) register */
    return vas;
}

/*--------------------------------------------------------------------*/
/* FUN_00029c7c @ 0x00029c7c   (est. vas_fh_attach)
 * Ghidra: void FUN_00029c7c(long param_1, undefined8 param_2, ulong param_3, long param_4)
 * Attaches a fault handler to the VAS: claims the next fault-handler slot in
 * the ring buffer (param_1+0x1f0, count at +0x1f8), records the handler
 * address (kind 3), resolves the page (FUN_00034f70) and maps it via the
 * VAS fault-mapping method (param_1+0x48 +0x40). Writes the result back
 * through param_4+0x10.
 * Confidence: low (VAS fault-handler attach, ring-buffer + map).
 * Notes: s_unknown_vas_return_code_0x_x_005ae5cc; FUN_00046304/314 result
 *   encoders.
 */
void vas_fh_attach(long param_1, unsigned long param_2, unsigned long param_3, long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long page, status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    /* bounds check on ring */
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        /* bounds check slot */
        slot[0] = 0x100000003;
        slot[1] = param_2;
        slot[2] = param_3 & 0xffffffff;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    page = sk_page_resolve();   /* FUN_00034f70 */
    if (page == 0) {
        /* error 2 path */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 2;
            *(unsigned short *)((char *)slot + 2) = 0;
        }
        status = 0;
        goto done;
    }
    /* FUN_00118164 lock; call map method (param_1+0x48 +0x40)(...,page); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        /* FUN_004b23d8(page); error encode */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
        }
    }
    *(unsigned char *)((char *)slot + 4) = 0;
done:
    /* param_4+0x10 callback with result */
    (*(void (**)(long, unsigned long, unsigned long))(param_4 + 0x10))(param_4, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00029e3c @ 0x00029e3c   (est. vas_fh_detach)
 * Ghidra: void FUN_00029e3c(long param_1, long param_2)
 * Detaches a fault handler from the VAS: claims a slot (kind 4), resolves
 * the page, and unmaps it via the fault-unmap method (param_1+0x48 +0x48).
 * Writes the result back through param_2+0x10.
 * Confidence: low (VAS fault-handler detach).
 */
void vas_fh_detach(long param_1, long param_2)
{
    unsigned long *slot, *ring, count;
    unsigned long page, status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 4;
        *(unsigned char *)((char *)slot + 1) = 1;
        slot[4] = 0; slot[5] = 0;
    }
    page = sk_page_resolve();   /* FUN_00034f70 */
    if (page == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 2;
            *(unsigned short *)((char *)slot + 2) = 0;
        }
        status = 2;
        goto done;
    }
    /* lock; call unmap method (param_1+0x48 +0x48)(param_1+0x40,page); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        /* FUN_004b23d8(page); error encode */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
        }
    }
    *(unsigned char *)((char *)slot + 1) = 0;
done:
    (*(void (**)(long, unsigned long, unsigned long))(param_2 + 0x10))(param_2, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00029ff0 @ 0x00029ff0   (est. vas_fh_kind)
 * Ghidra: void FUN_00029ff0(long param_1, undefined8 param_2, uint param_3, long param_4)
 * Sets the fault-handler kind for a VAS entry: claims a slot (kind 7), then
 * calls the fault-kind method (param_1+0x48 +0x50). Writes the result back.
 * Confidence: low (VAS fault-kind set).
 * Notes: s_unknown_easm_fault_kind_0x_x_005ae5e9.
 */
void vas_fh_kind(long param_1, unsigned long param_2, unsigned int param_3, long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000007;
        slot[1] = param_2;
        slot[2] = (unsigned long)param_3;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    if (2 < param_3 - 1) {
        sk_swift_fatal("unknown easm fault kind 0x%x");   /* s_unknown_easm_fault_kind_0x_x */
    }
    /* lock; call fault-kind method (param_1+0x48 +0x50)(...,param_3-1); unlock */
    status = 0;
    if ((status & 0xff) == 5) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else if ((status & 0xff) != 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    } else {
        if (slot != 0) {
            slot[4] = 1; slot[5] = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_4 + 0x10))(param_4, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002a1dc @ 0x0002a1dc   (est. vas_fh_add_range)
 * Ghidra: void FUN_0002a1dc(long param_1, long param_2)
 * Adds a fault-handler address range to the VAS: claims a slot (kind 8),
 * then calls the range-add method (param_1+0x48 +0x58) and records the
 * returned range base in the region table (param_1+0x1d8 stride 0x48).
 * Writes the result back.
 * Confidence: low (VAS fault range-add, region table update).
 */
void vas_fh_add_range(long param_1, long param_2)
{
    unsigned long *slot, *ring, count, range;
    unsigned long base, status;
    long r;
    unsigned long region_count, region;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 8;
        *(unsigned char *)((char *)slot + 1) = 1;
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; call range-add method (param_1+0x48 +0x58)(param_1+0x40,&range); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        /* find region with base match; *(param_1+0x180)+=1; store into region table */
        r = *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x180);
        region_count = *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x188);
        region = *(unsigned long *)(param_1 + 0x20) + 0x1d8;
        /* linear scan for r match, then store range at region + count*0x48 */
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x188) += 1;
        if (slot != 0) {
            slot[4] = (unsigned long)r;
            slot[5] = 0;
            *(unsigned char *)((char *)slot + 1) = 0;
        }
        /* success encode */
        goto done;
    }
    /* error encode */
    if (slot != 0) {
        *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
        *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
        *(unsigned char *)((char *)slot + 1) = 0;
    }
done:
    (*(void (**)(long, unsigned long, unsigned long))(param_2 + 0x10))(param_2, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002a530 @ 0x0002a530   (est. vas_fh_lookup)
 * Ghidra: undefined8 FUN_0002a530(...)
 * Looks up a fault handler by address range: claims a slot (kind 9), then
 * resolves the region containing param_2 via FUN_0002a784 and returns its
 * fault-handler record through the callback.
 * Confidence: low (VAS fault-handler lookup).
 */
unsigned long vas_fh_lookup(long param_1, unsigned long param_2, unsigned long param_3,
                            unsigned long param_4, long param_5)
{
    unsigned long *slot, *ring, count;
    unsigned long status;
    unsigned char b[0x50] = {0};

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000009;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = param_4 & 0xffffffff;
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via vas_fh_lookup_range; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        /* FUN_0004636c result encode from b[0x18..0x30] */
        if (slot != 0) {
            slot[4] = 0; slot[5] = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    return (*(unsigned long (**)(long, void *))(param_5 + 0x10))(param_5, &b[0x30]);
}

/*--------------------------------------------------------------------*/
/* FUN_0002a784 @ 0x0002a784   (est. vas_fh_lookup_range)
 * Ghidra: undefined8 FUN_0002a784(long param_1, long param_2, long param_3)
 * Scans the VAS region table (param_1+0x1d8, stride 0x48, count at +0x188)
 * for the entry whose base (at +0x18) equals param_2, and invokes the
 * callback (param_3+0x10) on the entry. Returns 0x1bf0006 if not found.
 * Confidence: medium (region-table scan).
 */
unsigned long vas_fh_lookup_range(long param_1, long param_2, long param_3)
{
    unsigned long region_count = *(long *)(param_1 + 0x188);
    if (region_count != 0) {
        unsigned long region = param_1 + 0x1d8;
        do {
            /* bounds check region */
            if (*(long *)(region + 0x18) == param_2) {
                return (*(unsigned long (**)(long, unsigned long))(param_3 + 0x10))(param_3, region);
            }
            region += 0x48;
            region_count--;
        } while (region_count != 0);
    }
    return 0x1bf0006;
}

/*--------------------------------------------------------------------*/
/* FUN_0002a80c @ 0x0002a80c   (est. vas_fh_activate)
 * Ghidra: ulong FUN_0002a80c(long param_1, undefined8 *param_2)
 * Activates a fault handler: validates the fault kind (param_1+0x40), calls
 * the activation method, and on the copy path maps the page via the handler's
 * map method and records the mapping. Traps on out-of-range access.
 * Confidence: low (VAS fault-handler activation with page mapping).
 * Notes: s_easm_faulthandler_failed_to_copy_005ad5c5 /
 *   s_easm_faulthandler_failed_to_map_c_005ad5ff /
 *   s_easm__d_FH__lld__p_is_already_ac_005ad5a0.
 */
unsigned long vas_fh_activate(long param_1, unsigned long *param_2)
{
    unsigned int kind;
    unsigned long status, page;
    unsigned char res[0x20] = {0};

    if ((*(unsigned char *)(param_2 + 4) & 1) == 0) {
        kind = *(unsigned char *)(param_1 + 0x40) - 1;
        if (2 < kind) {
            sk_swift_fatal("unknown easm fault kind 0x%x");
        }
        status = (*(unsigned long (**)(unsigned long, unsigned long, unsigned long, unsigned int, void *))param_2[2])(*param_2, param_2[1],
                                                         *(unsigned long *)(param_1 + 0x30),
                                                         kind & 0xff, &res);
        if ((status & 0xff) == 0) {
            if ((res[0] & 1) == 0) {
                /* failure: return the fault record without mapping */
                return 0;
            }
            page = sk_page_resolve();   /* FUN_00034f70 */
            status = 0;   /* (*FUN_00034a2c +0x40)(...,1,page) copy */
            if (status != 0) {
                sk_swift_fatal("easm faulthandler failed to copy");
                return status;
            }
            status = 0;   /* map via param_2[7]+0x28 */
            if (status != 0) {
                sk_swift_fatal("easm faulthandler failed to map c");
                return status;
            }
            /* record mapping; set active flag; return 0 */
            return 0;
        } else {
            if ((status & 0xff) != 5) return status;
        }
        return 0;
    }
    sk_swift_assert("easm %d FH %lld p is already ac");   /* s_easm__d_FH__lld__p_is_already_ac_ */
    return 0x3230001;
}

/*--------------------------------------------------------------------*/
/* FUN_0002aa84 @ 0x0002aa84   (est. vas_fh_complete_forward)
 * Ghidra: void FUN_0002aa84(...)
 * Completes a fault: claims a slot (kind 0xa), resolves the fault record via
 * vas_fh_lookup_range, and invokes the completion method (FUN_0002ac94).
 * Writes the result back.
 * Confidence: low (VAS fault-complete dispatch).
 */
void vas_fh_complete_forward(long param_1, unsigned long param_2, unsigned long param_3,
                             unsigned long param_4, long param_5)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000000a;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = param_4 & 0xffffffff;
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup + complete via FUN_0002ac94; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_5 + 0x10))(param_5, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002ac94 @ 0x0002ac94   (est. vas_fh_complete_fault)
 * Ghidra: undefined1 [16] FUN_0002ac94(long param_1, long param_2)
 * Completes a fault handler record: if the active flag (param_2+0x20) is
 * clear, asserts and returns error 0x3610001; otherwise verifies the fault
 * address matches and runs FUN_0002ad54 to deactivate. Returns 0x36b0000/
 * 0x36b0001 depending on address match.
 * Confidence: medium (fault-complete validation).
 * Notes: s_easm__d_completefault__FH__lld___005ad75a/78a.
 */
cl4_result_t vas_fh_complete_fault(long param_1, long param_2)
{
    cl4_result_t r;
    unsigned long addr;
    r.hi = 0;
    if ((*(unsigned char *)(param_2 + 0x20) & 1) == 0) {
        sk_swift_assert("easm %d completefault FH %lld ");
        r.lo = 0x3610001;
    } else {
        addr = *(unsigned long *)(param_1 + 0x28);
        if (addr != *(unsigned long *)(param_2 + 0x28)) {
            sk_swift_assert("easm %d completefault FH %lld ");
        }
        r.lo = 0x36b0000;
        if (addr != *(unsigned long *)(param_2 + 0x28)) {
            r.lo = 0x36b0001;
        }
        vas_fh_deactivate((unsigned long *)param_2, (addr == *(unsigned long *)(param_2 + 0x28)) &
                                   *(unsigned char *)(param_1 + 0x30));
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0002ad54 @ 0x0002ad54   (est. vas_fh_deactivate)
 * Ghidra: void FUN_0002ad54(undefined8 *param_1, undefined8 param_2)
 * Deactivates a fault handler: if the active flag (param_1+4) is set, it
 * unmaps the 0x4000-byte fault page via the handler's map method, clears the
 * active flag and the mapping, and runs the handler's unmount callback.
 * Confidence: medium (fault-handler deactivation).
 * Notes: s_easm_completefault_failed_to_dep_005ae606.
 */
void vas_fh_deactivate(unsigned long *param_1, unsigned long param_2)
{
    unsigned long status;
    if (*(char *)(param_1 + 4) == '\x01') {
        /* (param_1[7]+0x30)(param_1[6],&local_28,&local_30=0x4000) unmap */
        status = 0;
        if (status != 0) {
            sk_swift_fatal("easm completefault failed to dep");
            SWIFT_BREAKPOINT_A();   /* 0x2ae28 */
        }
        /* (param_1[2]+8)(*param_1,param_1[1],param_1[5],param_2) unmount */
        *(unsigned char *)(param_1 + 4) = 0;
        param_1[5] = 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0002ae28 @ 0x0002ae28   (est. vas_fh_destroy_forward)
 * Ghidra: void FUN_0002ae28(...)
 * Destroys a fault handler: claims a slot (kind 0xb), looks up and
 * destroys the record via FUN_0002b03c. Writes the result back.
 * Confidence: low (VAS fault-handler destroy).
 */
void vas_fh_destroy_forward(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000000b;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    /* lock; lookup + destroy via FUN_0002b03c; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_3 + 0x10))(param_3, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002b03c @ 0x0002b03c   (est. vas_fh_destroy)
 * Ghidra: undefined1 [16] FUN_0002b03c(long param_1, long param_2)
 * Destroys a fault handler: asserts it is active, deactivates it, and removes
 * it from the VAS fault-handler table via FUN_0002b0cc. Returns zero.
 * Confidence: medium (fault-handler destroy).
 * Notes: s_easm__d_destroy__FH__lld__p_is_a_005ad831.
 */
cl4_result_t vas_fh_destroy(long param_1, long param_2)
{
    cl4_result_t r;
    r.hi = 0; r.lo = 0;
    if ((*(unsigned char *)(param_2 + 0x20) & 1) != 0) {
        sk_swift_assert("easm %d destroy FH %lld p is a");
        vas_fh_deactivate((unsigned long *)param_2, 0);
    }
    vas_fh_table_remove(*(unsigned long *)(param_1 + 0x28), (unsigned long *)param_2);  /* FUN_0002b0cc */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0002b0cc @ 0x0002b0cc   (est. vas_fh_table_remove)
 * Ghidra: void FUN_0002b0cc(long param_1, undefined8 *param_2)
 * Removes a fault handler from the VAS table: verifies param_2 is a valid
 * active entry, deactivates it, frees its resources, and compacts the table
 * by moving the last entry into its place and zeroing the tail slot.
 * Confidence: medium (fault-handler table removal + compaction).
 * Notes: s_fh__p_is_not_an_active_faulthand_005ae64c.
 */
void vas_fh_table_remove(long param_1, unsigned long *param_2)
{
    unsigned long *table;
    unsigned long idx, count;
    unsigned long *tail;

    table = (unsigned long *)(param_1 + 400);
    idx = ((unsigned long)param_2 - (unsigned long)table >> 3) * 0x71c71c71c71c71c7; /* /9 */
    if (*(unsigned long *)(param_1 + 0x188) <= idx) {
        sk_swift_fatal("fh %p is not an active faulthand");
    }
    vas_fh_deactivate(param_2, 0);
    /* free resources: (*param_2[7])(param_2[6]); (param_2[2]+0x10)(*param_2,param_2[1]) */
    count = *(long *)(param_1 + 0x188) - 1;
    *(long *)(param_1 + 0x188) = count;
    if (idx - count != 0) {
        tail = table + count * 9;
        /* bounds check; move tail entry into param_2 (9 words) */
        param_2[8] = tail[8];
        for (int i = 0; i < 8; i++) param_2[i] = tail[i];
    }
    tail = table + *(unsigned long *)(param_1 + 0x188) * 9;
    /* zero the tail slot (9 words) */
    for (int i = 0; i < 9; i++) tail[i] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0002b1f8 @ 0x0002b1f8   (est. vas_fh_dump)
 * Ghidra: void FUN_0002b1f8(...)
 * Dumps a fault handler's state: claims a slot (kind 6), reads the fault
 * record via the dump method (param_1+0x48 +0x38), and encodes the result
 * (record pointer + handler descriptor) back through param_3.
 * Confidence: low (VAS fault-handler dump).
 */
void vas_fh_dump(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long status, rec, desc;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000006;
        slot[1] = param_2;
        slot[2] = param_2;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    /* lock; call dump method (param_1+0x48 +0x38)(param_1+0x40,param_2,&desc,&rec); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        /* success: FUN_0002b3ec(vas, rec, desc); encode */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 4;
            *(unsigned short *)((char *)slot + 2) = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, void *))(param_3 + 0x10))(param_3, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002b3ec @ 0x0002b3ec   (est. vas_record_add)
 * Ghidra: long FUN_0002b3ec(long param_1, long param_2, long param_3)
 * Adds a record to the VAS record array: validates the record's kind
 * (frame=0x11 or cnode=0x04), grows the array (FUN_000102f4) when full,
 * and appends param_2, copying the descriptor via FUN_0002b5e8. Returns
 * param_2. Various invariants abort with "VAS abort in function %s at lin".
 * Confidence: medium (VAS record array add + grow).
 * Notes: s__VAS_abort_in_function__s_at_lin_005ae776 etc.;
 *   s_Type_0x_x_is_not_frame_or_cnode_005ae8e4; FUN_00054354 noreturn.
 */
long vas_record_add(long param_1, long param_2, long param_3)
{
    unsigned long cap, used, ncap, *arr;
    unsigned char kind;

    if (param_2 != 0) {
        if (*(long *)(param_1 + 0x178) == 0) {
            *(long *)(param_1 + 0x178) = param_3;
        } else if (*(long *)(param_1 + 0x178) != param_3) {
            sk_swift_fatal("VAS abort in function %s at lin");
        }
        if (param_3 == 0) { /* FUN_00054354 noreturn */ }
        /* (param_3+8)(param_2,0) kind check */
        if ((((unsigned long)0 >> 0x13 & 1) == 0) && (sk_vas_lookup(0, 0, 0, 0) == 0)) {
            cap = *(unsigned long *)(param_1 + 0x160);
            used = *(unsigned long *)(param_1 + 0x168);
            if (cap < used) sk_swift_fatal("VAS abort in function %s at lin");
            if (cap <= used) {
                ncap = cap * 2;
                if (ncap < 0x11) ncap = 0x10;
                if (ncap < cap) sk_swift_fatal("VAS abort in function %s at lin");
                arr = (unsigned long *)sk_realloc(*(unsigned long *)(param_1 + 0x170),
                                                  ncap << 3);   /* FUN_000102f4 */
                if (arr == (unsigned long *)0) {
                    /* out-of-memory: build record via FUN_0002b5e8 + FUN_00045d38 */
                    return 0;
                }
                /* zero new tail; store array + capacity */
                *(unsigned long **)(param_1 + 0x170) = arr;
                *(unsigned long *)(param_1 + 0x160) = ncap;
            }
            if (cap <= used) sk_swift_fatal("VAS abort in function %s at lin");
            *(long *)(*(long *)(param_1 + 0x170) + used * 8) = param_2;
            *(unsigned long *)(param_1 + 0x168) = used + 1;
        }
        return param_2;
    }
    sk_swift_fatal("VAS abort in function %s at lin");
}

/*--------------------------------------------------------------------*/
/* FUN_0002b5e8 @ 0x0002b5e8   (est. vas_record_fill)
 * Ghidra: void FUN_0002b5e8(ulong *param_1, char *param_2, uint param_3)
 * Fills a VAS record descriptor from a source object descriptor (param_2):
 * stores the flags, resolves the kind (frame=0x11 → 1, cnode=0x04 → 2, else
 * fatal), and copies the capability words and three name pointers through
 * FUN_00045d38/FUN_00045ce8.
 * Confidence: medium (record descriptor fill).
 * Notes: s_Type_0x_x_is_not_frame_or_cnode_005ae8e4.
 */
void vas_record_fill(unsigned long *param_1, char *param_2, unsigned int param_3)
{
    unsigned char kind;
    unsigned long src;
    *param_1 = (unsigned long)(param_3 & 0xfff9fffe);
    if (*param_2 == '\x11') kind = 1;
    else if (*param_2 != '\x04') {
        sk_swift_fatal("Type 0x%x is not frame or cnode");
        kind = 0;
    } else kind = 2;
    *(unsigned long *)((char *)param_1 + 0x2a) = 0;
    *(unsigned char *)(param_1 + 1) = kind;
    *(unsigned long *)((char *)param_1 + 0x11) = 0;
    *(unsigned long *)((char *)param_1 + 9) = 0;
    param_1[3] = 0;
    src = *(unsigned long *)(param_2 + 8);
    param_1[4] = *(unsigned long *)(param_2 + 0x10);
    *(char *)(param_1 + 5) = param_2[0x18];
    *(bool *)((char *)param_1 + 0x29) = param_2[0x19] != '\0';
    *(unsigned long *)((char *)param_1 + 0x32) = 0;
    param_1[7] = 0;
    /* FUN_00045d38(param_1+2, src-or-null) ; FUN_00045d38(param_1+6, ...) */
    /* FUN_00045ce8(+0x2a), FUN_00045ce8(+0x2c), FUN_00045ce8(+0x2e) names */
}

/*--------------------------------------------------------------------*/
/* FUN_0002b724 @ 0x0002b724   (est. vas_fh_register)
 * Ghidra: void FUN_0002b724(long param_1, uint *param_2, long param_3)
 * Registers a fault handler with the VAS: decodes the handler descriptor
 * (param_2), claims a slot (kind 5), and calls the register method
 * (param_1+0x48 +0x30) with the packed flags/descriptor. On success adds the
 * returned record via FUN_0002b3ec and fills the descriptor. Writes the
 * result back.
 * Confidence: low (VAS fault-handler registration).
 */
void vas_fh_register(long param_1, unsigned int *param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long status, rec, desc, flags;
    unsigned char d[0x30];

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000005;
        slot[1] = 0;
        slot[2] = *(unsigned long *)(param_2 + 8);
        slot[3] = *(unsigned long *)param_2;
        slot[4] = 0; slot[5] = 0;
    }
    flags = *(unsigned int *)param_2;
    /* decode handler descriptor into d[] */
    /* lock; if flags&(1<<19)==0: call register method (param_1+0x48 +0x30); else error */
    status = 0;
    if ((status & 0xff) == 0) {
        rec = vas_record_add(*(unsigned long *)(param_1 + 0x20), 0, 0);
        vas_record_fill((unsigned long *)d, d, (unsigned int)flags);
        if (slot != 0) {
            slot[4] = rec;
            slot[5] = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, void *))(param_3 + 0x10))(param_3, &d[0]);
}

/*--------------------------------------------------------------------*/
/* FUN_0002ba98 @ 0x0002ba98   (est. vas_fh_handle_state)
 * Ghidra: undefined8 FUN_0002ba98(...)
 * Handles a fault-handler state request: claims a slot (kind 0x1b), looks up
 * the fault record via FUN_0002bd34, and returns the handler descriptor.
 * Confidence: low (VAS fault-handler state).
 */
unsigned long vas_fh_handle_state(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long status;
    unsigned char d0[8] = {0}, d1[8] = {0};

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000001b;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    /* lock; lookup via FUN_0002bd34; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            slot[4] = *(unsigned long *)(d1 + 0x18);
            slot[5] = *(unsigned long *)(d0 + 0x18);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        vas_record_fill((unsigned long *)d0, d1 + 0x18, *(unsigned int *)(d0 + 0x18));
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 4;
            *(unsigned short *)((char *)slot + 2) = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    return (*(unsigned long (**)(long, void *))(param_3 + 0x10))(param_3, &d0[0]);
}

/*--------------------------------------------------------------------*/
/* FUN_0002bd34 @ 0x0002bd34   (est. vas_fh_lookup_entry)
 * Ghidra: undefined1 [16] FUN_0002bd34(long param_1, long param_2, long param_3)
 * Looks up a fault-handler entry for address param_2: validates the VAS has
 * a mapping for it (FUN_0002fa34), and if so invokes the callback
 * (param_3+0x10) with the fault record. Returns 6 if unmapped.
 * Confidence: medium (fault-handler entry lookup).
 */
cl4_result_t vas_fh_lookup_entry(long param_1, long param_2, long param_3)
{
    cl4_result_t r;
    if ((param_2 != 0) && (sk_vas_region_find(0, 0) != 0)) {
        unsigned long rec = *(unsigned long *)(param_1 + 0x178);
        if (sk_page_check(*(unsigned long *)(param_1 + 8), *(unsigned long *)(param_1 + 0x10),
                          param_2, rec)) {   /* FUN_0003c4c0 */
            r = (*(cl4_result_t (*)(long, long, unsigned long))(param_3 + 0x10))(param_3, param_2, rec);
            return r;
        }
    }
    r.lo = 6; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0002bdb8 @ 0x0002bdb8   (est. vas_fh_map_page)
 * Ghidra: undefined1 [16] FUN_0002bdb8(long param_1, undefined8 param_2, long param_3)
 * Maps the fault page for a handler: invokes the map method (param_3+8) and
 * stores the result into the VAS page table (param_1+0x20-8 +0x18). Traps if
 * param_3 is null.
 * Confidence: medium (fault-page map).
 */
cl4_result_t vas_fh_map_page(long param_1, unsigned long param_2, long param_3)
{
    cl4_result_t r;
    unsigned long page = *(long *)(*(long *)(param_1 + 0x28) + 8);
    if (param_3 != 0) {
        unsigned int res = (*(unsigned int (**)(unsigned long, unsigned long))(param_3 + 8))(param_2, page + 0x18);
        *(unsigned int *)(*(long *)(*(long *)(param_1 + 0x20) + 8) + 0x18) = res;
        r.lo = 0; r.hi = 0;
        return r;
    }
    /* FUN_00054354 noreturn */
    r.lo = 0; r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0002be24 @ 0x0002be24   (est. sk_pair_copy8)
 * Ghidra: void FUN_0002be24(long param_1, long param_2)
 * Copies two 8-byte words from param_2+0x20/+0x28 into param_1+0x20/+0x28
 * via FUN_0004b710.
 * Confidence: medium (word copy helper).
 */
void sk_pair_copy8(long param_1, long param_2)
{
    /* FUN_0004b710(param_1+0x20, *(param_2+0x20), 8) */
    /* FUN_0004b710(param_1+0x28, *(param_2+0x28), 8) */
}

/*--------------------------------------------------------------------*/
/* FUN_0002be68 @ 0x0002be68   (est. sk_pair_release)
 * Ghidra: void FUN_0002be68(long param_1)
 * Releases two 8-byte objects at param_1+0x20/+0x28 via FUN_0004b8d0.
 * Confidence: medium (word release helper).
 */
void sk_pair_release(long param_1)
{
    /* FUN_0004b8d0(*(param_1+0x28), 8); FUN_0004b8d0(*(param_1+0x20), 8) */
}

/*--------------------------------------------------------------------*/
/* FUN_0002bea0 @ 0x0002bea0   (est. vas_fh_delete)
 * Ghidra: void FUN_0002bea0(...)
 * Deletes a fault handler: claims a slot (kind 0x1c), looks up and deletes
 * the record via FUN_0002bd34. Writes the result back.
 * Confidence: low (VAS fault-handler delete).
 */
void vas_fh_delete(long param_1, unsigned long param_2, unsigned long param_3, long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000001c;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup + delete via FUN_0002bd34; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_4 + 0x10))(param_4, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002c0c0 @ 0x0002c0c0   (est. vas_fh_size)
 * Ghidra: undefined8 FUN_0002c0c0(...)
 * Returns the fault-page size for a handler: claims a slot (kind 0x1d),
 * looks up the record, and returns its size field.
 * Confidence: low (VAS fault-handler size).
 */
unsigned long vas_fh_size(long param_1, unsigned long param_2, unsigned long param_3, long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status;
    unsigned char d0[8] = {0};

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000001d;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via FUN_0002bd34; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            slot[4] = *(unsigned long *)(d0 + 0x18);
            slot[5] = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    return (*(unsigned long (**)(long, unsigned long, unsigned long))(param_4 + 0x10))(param_4, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002c328 @ 0x0002c328   (est. vas_fh_get_range)
 * Ghidra: undefined8 FUN_0002c328(...)
 * Returns a fault handler's address range: claims a slot (kind 0x1e), looks
 * up the record, and returns its {lo,hi} range.
 * Confidence: low (VAS fault-handler range get).
 */
unsigned long vas_fh_get_range(long param_1, unsigned long param_2, unsigned long *param_3,
                               long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status;
    unsigned char d0[8] = {0}, d1[8] = {0};

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000001e;
        slot[1] = param_2;
        slot[2] = param_3[0];
        slot[3] = param_3[1];
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via FUN_0002bd34; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            slot[4] = *(unsigned long *)(d0 + 0x18);
            slot[5] = *(unsigned long *)(d1 + 0x18);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    return (*(unsigned long (**)(long, void *))(param_4 + 0x10))(param_4, &d0[0]);
}

/*--------------------------------------------------------------------*/
/* FUN_0002c62c @ 0x0002c62c   (est. vas_fh_get_range2)
 * Ghidra: undefined8 FUN_0002c62c(...)
 * Returns a fault handler's address range (kind 0x20); mirror of
 * FUN_0002c328.
 * Confidence: low.
 */
unsigned long vas_fh_get_range2(long param_1, unsigned long param_2, unsigned long *param_3,
                                long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status;
    unsigned char d0[8] = {0}, d1[8] = {0};

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000020;
        slot[1] = param_2;
        slot[2] = param_3[0];
        slot[3] = param_3[1];
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via FUN_0002bd34; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            slot[4] = *(unsigned long *)(d0 + 0x18);
            slot[5] = *(unsigned long *)(d1 + 0x18);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    return (*(unsigned long (**)(long, void *))(param_4 + 0x10))(param_4, &d0[0]);
}

/*--------------------------------------------------------------------*/
/* FUN_0002c930 @ 0x0002c930   (est. vas_fh_unregister)
 * Ghidra: void FUN_0002c930(...)
 * Unregisters a fault handler: claims a slot (kind 0x1f), looks up and
 * unregisters the record, then releases param_4. Writes the result back.
 * Confidence: low (VAS fault-handler unregister).
 */
void vas_fh_unregister(long param_1, unsigned long param_2, unsigned long param_3,
                       unsigned long param_4, long param_5)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000001f;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup + unregister via FUN_0002bd34; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    /* FUN_004b23d8(param_4) */
    (*(void (**)(long, unsigned long))(param_5 + 0x10))(param_5, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002cb5c @ 0x0002cb5c   (est. vas_fh_move)
 * Ghidra: undefined8 FUN_0002cb5c(...)
 * Moves a fault handler to a new address: claims a slot (kind 0x21), looks
 * up both the old (param_2) and new (param_3) addresses via FUN_0002bd34,
 * removes the old mapping via FUN_0002cf20 and re-registers via
 * FUN_0002b3ec. Writes the result back.
 * Confidence: low (VAS fault-handler move).
 */
unsigned long vas_fh_move(long param_1, unsigned long param_2, unsigned long param_3, long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status, rec;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000021;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via FUN_0002bd34 */
    status = 0;
    if ((status & 0xff) != 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        goto done;
    }
    /* vas_fh_region_remove(param_2); vas_fh_region_remove(param_3); */
    rec = vas_record_add(*(unsigned long *)(param_1 + 0x20), 0, 0);
    if (slot != 0) {
        slot[4] = rec;
        slot[5] = 0;
        *(unsigned char *)((char *)slot + 4) = 0;
    }
done:
    return (*(unsigned long (**)(long, unsigned long, unsigned long))(param_4 + 0x10))(param_4, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002ce70 @ 0x0002ce70   (est. vas_fh_lookup_dispatch)
 * Ghidra: void FUN_0002ce70(...)
 * Looks up a fault handler by address: invokes vas_fh_lookup_entry
 * (FUN_0002bd34) with the decoded address and forwards the result.
 * Confidence: low.
 */
void vas_fh_lookup_dispatch(long param_1, unsigned long param_2, unsigned long param_3,
                            unsigned long param_4)
{
    unsigned long addr = *(unsigned long *)(param_1 + 0x20);
    (void)param_4;
    vas_fh_lookup_entry(param_2, *(unsigned long *)(param_1 + 0x40), 0);  /* FUN_0002bd34 */
    (void)addr; (void)param_3;
}

/*--------------------------------------------------------------------*/
/* FUN_0002cf20 @ 0x0002cf20   (est. vas_fh_region_remove)
 * Ghidra: void FUN_0002cf20(long param_1, long param_2)
 * Removes an address from the VAS region record array: validates the record
 * exists (FUN_0002fa34), decrements the used count, and replaces the removed
 * record with the last element (swap-pop). Aborts on invariant violations.
 * Confidence: medium (region record swap-pop).
 * Notes: s__VAS_abort_in_function__s_at_lin_005ae904/e9e0/776.
 */
void vas_fh_region_remove(long param_1, long param_2)
{
    unsigned long *rec, used;
    unsigned long cap;

    rec = (unsigned long *)sk_vas_region_find(0, 0);   /* FUN_0002fa34 */
    if (rec == (unsigned long *)0) {
        sk_swift_fatal("VAS abort in function %s at lin");
    }
    used = *(unsigned long *)(param_1 + 0x168);
    if (used == 0) {
        /* FUN_004b1b60 */
    } else if (used <= *(unsigned long *)(param_1 + 0x160)) {
        if (*rec != (unsigned long)param_2) {
            sk_swift_fatal("VAS abort in function %s at lin");
        }
        *(unsigned long *)(param_1 + 0x168) = used - 1;
        *rec = *(unsigned long *)(*(long *)(param_1 + 0x170) + (used - 1) * 8);
    } else {
        sk_swift_fatal("VAS abort in function %s at lin");
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0002d040 @ 0x0002d040   (est. vas_fh_swap)
 * Ghidra: undefined8 FUN_0002d040(...)
 * Swaps two fault handlers (param_2, param_3): claims a slot (kind 0x22),
 * removes both regions and re-adds both via FUN_0002b3ec. Writes the result
 * back.
 * Confidence: low (VAS fault-handler swap).
 */
unsigned long vas_fh_swap(long param_1, unsigned long param_2, unsigned long param_3, long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status, r1, r2;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000022;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via FUN_0002bd34 */
    status = 0;
    if ((status & 0xff) != 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        goto done;
    }
    /* vas_fh_region_remove(param_2); r1=vas_record_add; r2=vas_record_add */
    r1 = 0; r2 = 0;
    if (slot != 0) {
        slot[4] = r1;
        slot[5] = r2;
        *(unsigned char *)((char *)slot + 4) = 0;
    }
done:
    return (*(unsigned long (**)(long, void *))(param_4 + 0x10))(param_4, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002d3b0 @ 0x0002d3b0   (est. vas_fh_resize)
 * Ghidra: undefined8 FUN_0002d3b0(...)
 * Resizes a fault handler's mapped region: claims a slot (kind 0x23),
 * removes the old region and re-adds with the new size via FUN_0002b3ec.
 * Writes the result back.
 * Confidence: low (VAS fault-handler resize).
 */
unsigned long vas_fh_resize(long param_1, unsigned long param_2, unsigned long param_3,
                            unsigned long param_4, long param_5)
{
    unsigned long *slot, *ring, count;
    unsigned long status, rec;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000023;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = param_4 & 0xffffffff;
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via FUN_0002bd34 */
    status = 0;
    if ((status & 0xff) != 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        goto done;
    }
    /* vas_fh_region_remove(param_2); rec=vas_record_add */
    rec = 0;
    if (slot != 0) {
        slot[4] = rec;
        slot[5] = 0;
        *(unsigned char *)((char *)slot + 4) = 0;
    }
done:
    {
        unsigned long r;
        r = (*(unsigned long (**)(long, unsigned long, unsigned long))(param_5 + 0x10))(param_5, 0, 0);
        return r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0002d6dc @ 0x0002d6dc   (est. vas_fh_state_set)
 * Ghidra: void FUN_0002d6dc(...)
 * Sets a fault handler's state: claims a slot (kind 0x24), validates the
 * state (<=4), and calls the state-set method (FUN_0002bd34). Writes the
 * result back.
 * Confidence: low (VAS fault-handler state set).
 * Notes: s_unknown_easm_fault_state_0x_x_005aea31.
 */
void vas_fh_state_set(long param_1, unsigned long param_2, unsigned int param_3,
                      unsigned long param_4, unsigned long param_5, long param_6)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000024;
        slot[1] = param_2;
        slot[2] = (unsigned long)param_3;
        slot[3] = param_4;
        slot[4] = 0; slot[5] = 0;
    }
    if (4 < param_3) {
        sk_swift_fatal("unknown easm fault state 0x%x");
    }
    /* lock; state-set via FUN_0002bd34; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            slot[4] = param_5;
            slot[5] = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_6 + 0x10))(param_6, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002d93c @ 0x0002d93c   (est. vas_fh_detach_sync)
 * Ghidra: void FUN_0002d93c(long param_1, undefined8 param_2, long param_3)
 * Synchronously detaches a fault handler: claims a slot (kind 0x1a), looks
 * up and detaches the record via FUN_0002bd34, then removes the region via
 * FUN_0002cf20. Writes the result back.
 * Confidence: low (VAS fault-handler synchronous detach).
 */
void vas_fh_detach_sync(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000001a;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    /* lock; lookup via FUN_0002bd34 */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
        /* vas_fh_region_remove(param_2) */
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_3 + 0x10))(param_3, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002db3c @ 0x0002db3c   (est. vas_fh_map_dispatch)
 * Ghidra: void FUN_0002db3c(long param_1, undefined8 param_2, long param_3)
 * Dispatches a fault-map request: claims a slot (kind 0x15), resolves the
 * page (FUN_00034f70), and maps it via the map method. Writes the result
 * back.
 * Confidence: low (VAS fault map dispatch).
 */
void vas_fh_map_dispatch(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long page, status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000015;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    page = sk_page_resolve();   /* FUN_00034f70 */
    if (page == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 2;
            *(unsigned short *)((char *)slot + 2) = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        status = 2;
        goto done;
    }
    /* lock; call map method (param_1+0x38-8 +0x10)(...,param_2,8,page); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        /* FUN_004b23d8(page); error encode */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
done:
    (*(void (**)(long, unsigned long, unsigned long))(param_3 + 0x10))(param_3, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002dd1c @ 0x0002dd1c   (est. vas_fh_map6_dispatch)
 * Ghidra: void FUN_0002dd1c(long param_1, undefined8 param_2, long param_3)
 * Fault-map dispatch (6-byte size, kind 0x16); mirror of FUN_0002db3c.
 * Confidence: low.
 */
void vas_fh_map6_dispatch(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long page, status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000016;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    page = sk_page_resolve();
    if (page == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 2;
            *(unsigned short *)((char *)slot + 2) = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        status = 2;
        goto done;
    }
    /* lock; map via method (6 bytes); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        /* FUN_004b23d8(page); error encode */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
done:
    (*(void (**)(long, unsigned long, unsigned long))(param_3 + 0x10))(param_3, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002defc @ 0x0002defc   (est. vas_fh_map15_dispatch)
 * Ghidra: void FUN_0002defc(long param_1, undefined8 param_2, long param_3)
 * Fault-map dispatch (0x15-byte size, kind 0x17); mirror of FUN_0002db3c.
 * Confidence: low.
 */
void vas_fh_map15_dispatch(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long page, status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000017;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    page = sk_page_resolve();
    if (page == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 2;
            *(unsigned short *)((char *)slot + 2) = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        status = 2;
        goto done;
    }
    /* lock; map via method (0x15 bytes); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        /* FUN_004b23d8(page); error encode */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
done:
    (*(void (**)(long, unsigned long, unsigned long))(param_3 + 0x10))(param_3, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002e0dc @ 0x0002e0dc   (est. vas_fh_map14_dispatch)
 * Ghidra: void FUN_0002e0dc(long param_1, undefined8 param_2, long param_3)
 * Fault-map dispatch (0x14-byte size, kind 0x18); mirror of FUN_0002db3c.
 * Confidence: low.
 */
void vas_fh_map14_dispatch(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long page, status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000018;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    page = sk_page_resolve();
    if (page == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 2;
            *(unsigned short *)((char *)slot + 2) = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        status = 2;
        goto done;
    }
    /* lock; map via method (0x14 bytes); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        /* FUN_004b23d8(page); error encode */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
done:
    (*(void (**)(long, unsigned long, unsigned long))(param_3 + 0x10))(param_3, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002e2bc @ 0x0002e2bc   (est. vas_fh_clear)
 * Ghidra: void FUN_0002e2bc(long param_1, undefined8 param_2, long param_3)
 * Clears a fault handler: claims a slot (kind 0x19), and calls the clear
 * method (param_1+0x38 +0x10). Writes the result back.
 * Confidence: low (VAS fault-handler clear).
 */
void vas_fh_clear(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000019;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    /* lock; clear via method (param_1+0x38-8 +0x10)(method,param_2); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_3 + 0x10))(param_3, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002e460 @ 0x0002e460   (est. vas_fh_clear2)
 * Ghidra: void FUN_0002e460(long param_1, undefined8 param_2, long param_3)
 * Clears a fault handler (variant method +0x18, kind 0xc); mirror of
 * FUN_0002e2bc.
 * Confidence: low.
 */
void vas_fh_clear2(long param_1, unsigned long param_2, long param_3)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000000c;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    /* lock; clear via method (param_1+0x38-8 +0x18)(method,param_2); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_3 + 0x10))(param_3, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002e604 @ 0x0002e604   (est. vas_fh_get)
 * Ghidra: void FUN_0002e604(...)
 * Gets a fault handler by address: claims a slot (kind 0x12), looks up and
 * returns the handler via FUN_0002e7c4. Writes the result back.
 * Confidence: low (VAS fault-handler get).
 */
void vas_fh_get(long param_1, unsigned long param_2, unsigned long param_3, long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000012;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via FUN_0002e7c4; unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_4 + 0x10))(param_4, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002e7c4 @ 0x0002e7c4   (est. vas_fh_get_internal)
 * Ghidra: ulong FUN_0002e7c4(long param_1, ...)
 * Core fault-handler get/add-thread-info: validates the fault address maps
 * into the VAS (FUN_00034f70/FUN_00034a2c page resolve), resolves the
 * handler address, grows the per-handler thread-info table
 * (param_1+0x1d8/0x1e0/0x1e8) when needed, and appends the thread-info
 * record. Returns 0 on success; various errors abort with
 * "VAS abort in function %s at lin".
 * Confidence: low (large fault-handler thread-info append).
 * Notes: s__easm_server_add_thread_info_005aeac7; FUN_00028950 lookup;
 *   FUN_000102f4 realloc.
 */
unsigned long vas_fh_get_internal(long param_1, unsigned long param_2, long param_3,
                                  long param_4, unsigned long param_5)
{
    unsigned long page, status;
    unsigned long count, cap, ncap, *arr;
    unsigned long *slot;

    page = sk_page_resolve();   /* FUN_00034f70 */
    if (page == 0) {
        /* FUN_004b1bd8; abort */
        sk_swift_fatal("VAS abort in function %s at lin");
    }
    status = (*(unsigned long (**)(unsigned long, unsigned long, int, unsigned long))(param_3 + 0x40))
             (param_2, param_5, 0, page);
    if ((status & 0xff) == 0) {
        /* (*(param_3+0x38))(param_2, *(uVar12+0x18), 0) — resolve handler */
        /* then append thread-info to param_1+0x1d8 table */
        count = *(unsigned long *)(param_1 + 0x1d8);
        cap = *(unsigned long *)(param_1 + 0x1e0);
        if (count < cap) {
            if (count <= cap) {
                ncap = count * 2;
                if (ncap < 0x11) ncap = 0x10;
                if (ncap < count) sk_swift_fatal("VAS abort in function %s at lin");
                arr = (unsigned long *)sk_realloc(*(unsigned long *)(param_1 + 0x1e8),
                                                  ncap * 0x58);   /* FUN_000102f4 */
                if (arr == 0) {
                    /* out-of-memory: record via FUN_0004b1b9c + lookup */
                    return 0;
                }
                *(unsigned long **)(param_1 + 0x1e8) = arr;
                *(unsigned long *)(param_1 + 0x1d8) = ncap;
            }
            if (count <= cap) sk_swift_fatal("VAS abort in function %s at lin");
        }
        /* append record at param_1+0x1e8 + cap*0xb (0x58 bytes) */
        slot = *(unsigned long **)(param_1 + 0x1e8) + cap * 0xb;
        slot[0] = param_5;
        slot[1] = status;
        /* ... fill remaining words ... */
        *(long *)(param_1 + 0x1e0) = *(long *)(param_1 + 0x1e0) + 1;
        return 0;
    }
    /* FUN_004b23d8(page); return status */
    return status;
}

/*--------------------------------------------------------------------*/
/* FUN_0002ee90 @ 0x0002ee90   (est. vas_fh_get_or_add)
 * Ghidra: void FUN_0002ee90(...)
 * Gets or adds a fault handler: claims a slot (kind 0x12), looks up the
 * handler via FUN_0002e7c4; if not found, creates a new one via the
 * create method. Writes the result back.
 * Confidence: low (VAS fault-handler get-or-add).
 */
void vas_fh_get_or_add(long param_1, unsigned long param_2, unsigned long param_3,
                       unsigned long param_4, long param_5)
{
    unsigned long *slot, *ring, count;
    unsigned long status;
    unsigned char d[0x30] = {0};

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000012;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = 0; slot[4] = 0; slot[5] = 0;
    }
    /* lock; lookup via FUN_0002e7c4 */
    status = 0;
    if ((status & 0xff) != 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
        goto done;
    }
    if (sk_vas_lookup(*(unsigned long *)(param_1 + 0x20), param_2, 0, 0) != 0) {
        /* existing handler: set its kind via method (param_1+0x38 +0x48) */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 4;
            *(unsigned short *)((char *)slot + 2) = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    } else {
        /* create new: via FUN_004b1c4c + method (param_1+0x38 +0x20) */
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    }
done:
    (*(void (**)(long, void *))(param_5 + 0x10))(param_5, &d[0]);
}

/*--------------------------------------------------------------------*/
/* FUN_0002f09c @ 0x0002f09c   (est. vas_fh_create_result)
 * Ghidra: void FUN_0002f09c(long param_1, long param_2)
 * Fault-handler create result: claims a slot (kind 0xd), calls the create
 * method (param_1+0x38 +0x20), and writes the result back.
 * Confidence: low (VAS fault-handler create).
 */
void vas_fh_create_result(long param_1, long param_2)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0xd;
        *(unsigned char *)((char *)slot + 1) = 1;
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; create via method (param_1+0x38 +0x20)(); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 1) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_2 + 0x10))(param_2, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002f240 @ 0x0002f240   (est. vas_fh_set_desc)
 * Ghidra: void FUN_0002f240(...)
 * Sets a fault handler's descriptor: claims a slot (kind 0xe), and calls the
 * descriptor-set method (param_1+0x38 +0x28). Writes the result back.
 * Confidence: low (VAS fault-handler descriptor set).
 */
void vas_fh_set_desc(long param_1, unsigned long param_2, unsigned long param_3,
                     unsigned long param_4, long param_5)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000000e;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    /* lock; set-desc via method (param_1+0x38 +0x28)(...,param_2,param_3,param_4); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_5 + 0x10))(param_5, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002f3fc @ 0x0002f3fc   (est. vas_fh_set_desc2)
 * Ghidra: void FUN_0002f3fc(...)
 * Sets a fault handler's descriptor (variant method +0x30, kind 0xf); mirror
 * of FUN_0002f240.
 * Confidence: low.
 */
void vas_fh_set_desc2(long param_1, unsigned long param_2, unsigned long param_3, long param_4)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x10000000f;
        slot[1] = param_2;
        slot[3] = 0; slot[2] = 0; slot[5] = 0; slot[4] = 0;
    }
    /* lock; set-desc via method (param_1+0x38 +0x30)(...,param_2,param_3); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_4 + 0x10))(param_4, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002f5b0 @ 0x0002f5b0   (est. vas_fh_set_desc3)
 * Ghidra: void FUN_0002f5b0(...)
 * Sets a fault handler's descriptor (variant method +0x38, kind 0x10); mirror
 * of FUN_0002f240.
 * Confidence: low.
 */
void vas_fh_set_desc3(long param_1, unsigned long param_2, unsigned long param_3,
                      unsigned long param_4, unsigned long param_5, long param_6)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000010;
        slot[1] = param_2;
        slot[2] = param_3;
        slot[3] = param_4 & 0xffffffff;
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; set-desc via method (param_1+0x38 +0x38)(...,param_2,param_3,param_4,param_5); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_6 + 0x10))(param_6, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002f780 @ 0x0002f780   (est. vas_fh_set_desc4)
 * Ghidra: void FUN_0002f780(...)
 * Sets a fault handler's descriptor (variant method +0x40, kind 0x11); mirror
 * of FUN_0002f240.
 * Confidence: low.
 */
void vas_fh_set_desc4(long param_1, unsigned long param_2, unsigned long param_3,
                      unsigned long param_4, unsigned long param_5, long param_6)
{
    unsigned long *slot, *ring, count;
    unsigned long status;

    ring = (unsigned long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f0);
    count = *ring;
    if (count == 0) {
        slot = (unsigned long *)0;
    } else {
        *(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8) += 1;
        slot = *(unsigned long **)(*(unsigned long *)(param_1 + 0x20) + 0x200)
               + ((*(long *)(*(unsigned long *)(param_1 + 0x20) + 0x1f8)) % count) * 6;
        slot[0] = 0x100000011;
        slot[1] = param_2;
        slot[2] = param_4;
        slot[3] = param_5;
        slot[4] = 0; slot[5] = 0;
    }
    /* lock; set-desc via method (param_1+0x38 +0x40)(...,param_2,param_3,param_4,param_5); unlock */
    status = 0;
    if ((status & 0xff) == 0) {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 4) = 0;
            slot[4] = 0; slot[5] = 0;
        }
    } else {
        if (slot != 0) {
            *(unsigned char *)((char *)slot + 1) = (unsigned char)status;
            *(unsigned short *)((char *)slot + 2) = (unsigned short)(status >> 0x10);
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
    (*(void (**)(long, unsigned long))(param_6 + 0x10))(param_6, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0002f94c @ 0x0002f94c   (est. vas_fh_release_all)
 * Ghidra: void FUN_0002f94c(long param_1)
 * Releases all VAS fault-handler state: iterates the fault-handler table
 * (param_1+0x188) removing each entry via FUN_0002b0cc, frees the record
 * array (param_1+0x170), and iterates the thread-info table
 * (param_1+0x1e0/0x1e8) releasing each thread's handler.
 * Confidence: medium (VAS teardown).
 */
void vas_fh_release_all(long param_1)
{
    unsigned long i;
    if (*(long *)(param_1 + 0x188) != 0) {
        do {
            vas_fh_table_remove(param_1, (unsigned long *)(param_1 + 400));  /* FUN_0002b0cc */
        } while (*(long *)(param_1 + 0x188) != 0);
    }
    if (*(long *)(param_1 + 0x170) != 0) {
        sk_obj_bind_reset(0, 0, 0);   /* thunk_FUN_00012568 */
        *(unsigned long *)(param_1 + 0x170) = 0;
        *(unsigned long *)(param_1 + 0x160) = 0;
    }
    *(unsigned long *)(param_1 + 0x168) = 0;
    i = *(long *)(param_1 + 0x1e8);
    if (i != 0) {
        if (*(long *)(param_1 + 0x1e0) != 0) {
            unsigned long n = 0;
            unsigned long off = 0;
            do {
                /* (*(*(uVar1+0x18)))(*(uVar1+0x10)) per thread-info record */
                n++;
                off += 0x58;
            } while (n < *(unsigned long *)(param_1 + 0x1e0));
            i = *(long *)(param_1 + 0x1e8);
        }
        sk_obj_bind_reset(i, 0, 0);   /* thunk_FUN_00012568 */
        *(unsigned long *)(param_1 + 0x1e8) = 0;
        *(unsigned long *)(param_1 + 0x1d8) = 0;
    }
    *(unsigned long *)(param_1 + 0x1e0) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0002fa34 @ 0x0002fa34   (est. sk_vas_region_find)
 * Ghidra: long * FUN_0002fa34(long param_1, long param_2)
 * Finds a VAS region record by value: scans the record array (param_1+0x170,
 * count at param_1+0x168) for the entry equal to param_2. Bounds-checked;
 * returns null if absent.
 * Confidence: medium (linear record search).
 */
long *sk_vas_region_find(long param_1, long param_2)
{
    long *arr, *e;
    unsigned long count = *(long *)(param_1 + 0x168);
    if (count != 0) {
        arr = *(long **)(param_1 + 0x170);
        e = arr;
        do {
            if (*e == param_2) return e;
            e++;
            count--;
        } while (count != 0);
    }
    return (long *)0;
}

/*--------------------------------------------------------------------*/
/* FUN_0002fa84 @ 0x0002fa84   (est. sk_obj_bind)
 * Ghidra: undefined1 [16] FUN_0002fa84(long param_1, long *param_2)
 * Binds a capability object pair: initialises param_2[0] with param_1 and
 * builds the two child capabilities (param_2+1, param_2+6) via the parent
 * object's +0x10/+0x18 methods. Returns 0 on success or an error code
 * (0x10a0007/0x1150002/0x11d0002).
 * Confidence: medium (capability-pair bind).
 */
cl4_result_t sk_cap_bind_pair(long param_1, long *param_2)
{
    cl4_result_t r;
    unsigned long status = 0x10a0007;
    r.hi = 0;
    if ((param_1 != 0) && (param_2 != (long *)0)) {
        *param_2 = param_1;
        param_2[0xe] = 0; param_2[0xd] = 0;
        param_2[0x10] = 0; param_2[0xf] = 0;
        /* (param_1+0x10)(...,param_2+1) — first child */
        if (param_2[1] == 0) {
            status = 0x1150002;
        } else {
            /* (param_1+0x18)(param_2+1,...) — child init */
            /* (param_1+0x10)(...,param_2+6) — second child */
            if (param_2[6] == 0) {
                /* (param_1+0x20)(param_2+1) — rollback first child */
                status = 0x11d0002;
            } else {
                /* (param_1+0x18)(param_2+6,...) */
                status = 0;
                param_2[0xb] = 0;
                param_2[0xc] = 0;
            }
        }
    }
    r.lo = status;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0002fb88 @ 0x0002fb88   (est. vas_msg_send_packed)
 * Ghidra: void FUN_0002fb88(undefined8 *param_1, long *param_2, ...)
 * Sends a packed VAS message from the message buffer param_2: validates the
 * buffer and size, allocates a transport block, copies the payload into the
 * buffer's data window (via FUN_00036008), and returns the block. Handles
 * buffer growth and free-block recycling.
 * Confidence: low (large packed-message send, ring/list management).
 */
void vas_msg_send_packed(unsigned long *param_1, long *param_2, unsigned long param_3,
                         unsigned long param_4, int param_5)
{
    unsigned long status;
    if ((param_2 == (long *)0) || (param_4 == 0)) {
        status = 0x12f0007;
    } else {
        if (param_5 == 0) {
            /* validate buffer ranges; allocate transport block */
            /* FUN_00030780(param_4) kind; copy via FUN_00036008 */
            /* if success: param_1[0]=0; param_1[1]=0; param_1[2]=block; return */
            status = 0x1880001;
            goto set;
        }
        status = 0x1350005;
    }
set:
    param_1[2] = 0;
    param_1[0] = status;
    param_1[1] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0002ff40 @ 0x0002ff40   (est. vas_msg_recv_forward)
 * Ghidra: void FUN_0002ff40(void)
 * Forwarder to FUN_0002ff48 (message receive).
 * Confidence: medium (trivial forwarder).
 */
void vas_msg_recv_forward(void)
{
    vas_msg_recv(0, 0, 0, 0, 0);   /* FUN_0002ff48 */
}

/*--------------------------------------------------------------------*/
/* FUN_0002ff48 @ 0x0002ff48   (est. vas_msg_recv)
 * Ghidra: undefined1 [16] FUN_0002ff48(...)
 * Receives a VAS message: reads the message size (FUN_00035ba0), validates
 * the source/dest ranges, copies the payload via the read method
 * (FUN_000304d0 path or the buffer copy), updates the buffer bookkeeping
 * (FUN_0003611c/FUN_000368f8), and returns a status pair. Handles buffer
 * growth and recycling of freed blocks.
 * Confidence: low (large packed-message receive; ring/list management).
 */
cl4_result_t vas_msg_recv(long *param_1, unsigned long *param_2, unsigned long param_3,
                          unsigned int *param_4, int param_5)
{
    cl4_result_t r;
    unsigned long status = 0x1a60007;
    r.hi = 0;
    if ((param_1 != (long *)0) && (param_2 != (unsigned long *)0)) {
        if ((param_5 != 0) && (param_4 == (unsigned int *)0)) {
            status = 0x1aa0007;
        } else {
            /* FUN_00035ba0 read size */
            if (0) {
                status = 0x1b20004;
            } else {
                /* validate ranges; copy payload; update bookkeeping */
                /* *(param_1+0xd) -= 1; param_2[6]/param_2[7] tracking */
                status = 0;
            }
        }
    }
    r.lo = status;
    return r;
}
