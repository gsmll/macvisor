/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * Region 0x10000-0x20000: early boot / initialization. cL4/seL4 vocabulary
 * (boot, TCB init, capability init, sched init, CNode, IPC, vspace).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint64_t cap_t;
typedef uint64_t tcb_t;

#define CallSupervisor(n)  __asm__ volatile("hvc #0" ::: "memory")
#define DC_GVA(a)          __asm__ volatile("dc cvau, %0" :: "r"(a) : "memory")
#define LZCOUNT(v)         __builtin_clzll((unsigned long long)(v))
#define bit_reverse64(v)   __builtin_bitreverse64((unsigned long long)(v))
#define sk_ref_retain(v)   (void)(v)

/*-------------------------------------------------------------------------
 * Out-of-range kernel helpers (bodies reconstructed by sibling range
 * workers; declared extern with their FUN_ address in a comment).
 *------------------------------------------------------------------------- */
extern void *sk_alloc(unsigned long size, unsigned long tag);             /* FUN_0036a908 */
extern void sk_free(void *ptr);                                           /* FUN_0036b118 */
extern void *sk_current_tcb(void);                                        /* FUN_000867ec */
extern void *sk_cpu(void);                                                /* FUN_0008e518 */
extern void sk_set_error(unsigned int err);                               /* thunk_FUN_0006037c */
extern void sk_panic(const char *msg) __attribute__((noreturn));          /* FUN_001150e0 */
extern void *sk_buddy_base;        /* DAT_006adfd8 */
extern unsigned long sk_buddy_flags;  /* DAT_006adfe0 */
extern void *sk_heap;                 /* DAT_0064c060 */
extern unsigned long sk_zone_count;   /* _DAT_006ac238 */
extern unsigned long sk_zone_seed;    /* _DAT_006ac234 */
extern unsigned long sk_zone_flags;   /* _DAT_006ac230 */
extern unsigned long sk_zone_granule; /* DAT_006ac23d */
extern unsigned long sk_perthread_key_count; /* _DAT_006ae1b0 */
extern unsigned long sk_thread_list_head;    /* _DAT_006ae1c0 */
extern unsigned long sk_thread_list;         /* _DAT_006ae1c8 */
extern unsigned long sk_obj_class_lookup(unsigned long cls, unsigned long a, unsigned long b); /* FUN_00011cac */
extern unsigned long sk_heap_alloc_mode(void *heap, void *a, unsigned long size, unsigned int mode, void *arg); /* FUN_00012218 */
extern void *sk_alloc_out(void *out);  /* FUN_000127c0 */
extern unsigned long sk_zone0(void);   /* DAT_006adfe8 */
extern unsigned long sk_zone_table_grow(void *a, void *b, unsigned long c, unsigned long d); /* FUN_00117d18 */
extern unsigned long sk_strlen(const char *s); /* thunk_FUN_00115080 */
extern void sk_strcpy(char *dst, const char *src, unsigned long n, unsigned long m); /* FUN_00117e68 */
extern void sk_obj_retain(void *obj, unsigned long v); /* FUN_00015984 */
extern void sk_cap_install(void *a, void *b, void **c); /* FUN_00015468 */
extern void sk_tb_register(void *client); /* FUN_00019aac */
extern void sk_metadata_encode(unsigned long size, unsigned long tag, void *out); /* helper */
extern unsigned long sk_alloc_phys(unsigned long flags, unsigned long base, unsigned long size,
                                   unsigned int mode, unsigned long mapped, void *align, void *a); /* FUN_00117fdc */
extern void sk_async_install(void *slot, void *obj, void *cfg);   /* FUN_00062c2c */
extern void sk_perthread_init(void *a, void *b, unsigned long c); /* FUN_0005d470 */
extern void *FUN_00013260(void *a, void *b, void *c);
extern unsigned long sk_dealloc(void *p, void *a, void *size);            /* FUN_001180cc */
extern unsigned long sk_madvise(void *a, void *base, void *len, unsigned char mode); /* FUN_0011807c */
extern void sk_memcpy(void *dst, void *src, unsigned long n);             /* FUN_00117cc4 */
extern void FUN_00117cc4(unsigned long dst, unsigned long src, unsigned long n);
extern void FUN_00117d14(unsigned long dst, unsigned long src, unsigned long n);
extern void FUN_00117d18(void *a, void *b, unsigned long c, unsigned long d);
extern void FUN_00117e68(void *dst, void *src, unsigned long n, unsigned long m);
extern void FUN_00117f8c(unsigned long p, unsigned long size, unsigned long fill);
extern void FUN_00117fdc(void *a, void *b, void *c, unsigned int d, unsigned long e, void *f, void *g);
extern void FUN_001157f0(unsigned long v, unsigned long n);
extern void FUN_001157d4(void);
extern void FUN_0011825c(unsigned int v, void **p);
extern void FUN_00115574(unsigned long *buf, unsigned long n);
extern void FUN_00116d60(void);
extern void FUN_001183e0(void *arg);
extern void FUN_00118b28(const char *s);
extern void FUN_00118c4c(void *a, void *b);
extern void FUN_00118b94(const char *s);
extern void FUN_00115424(const char *a, const char *b, const char *c, unsigned long d);
extern void FUN_001afa84(const char *fmt, ...);
extern void thunk_FUN_00060524(void);
extern void thunk_FUN_0006037c(void);
extern unsigned long thunk_FUN_00061638(void);
extern void thunk_FUN_0036b270(unsigned long v);
extern void FUN_0036b118(void *p);
extern void FUN_0036a908(unsigned long size, unsigned long tag);
extern void FUN_0036a940(void);
extern void FUN_0036a1a0(void *a, void *b, unsigned long c, unsigned long d);
extern void FUN_0036b8b0(void *a);
extern void FUN_0036b834(void *a, void *b);
extern void FUN_0036b8c0(void);
extern void FUN_0036b7f8(void *a, unsigned long b);
extern void FUN_0036b6ac(void);
extern void FUN_0036b21c(void);
extern void FUN_0036a20c(void *p);
extern void FUN_00376820(void *a, unsigned long b);
extern void FUN_00376038(void *a, void *b);
extern unsigned long FUN_003698b0(void *a, void *b, unsigned long c, ...);
extern void FUN_003a25d4(unsigned long v);
extern void FUN_003a261c(unsigned long v);
extern void FUN_00310d34(unsigned long v, void *p);
extern unsigned long FUN_002b24b8(void);
extern void FUN_002a9ba8(unsigned long a, unsigned long b);
extern void FUN_002a4ab4(unsigned long v);
extern void thunk_FUN_002acbb8(void);
extern void FUN_001ba7d4(unsigned long v, unsigned long w);
extern void FUN_0024917c(void *a, void *b);
extern void thunk_FUN_0024d9ac(void *a);
extern void thunk_FUN_0035dc24(void *a, void *b, void *c);
extern void thunk_FUN_0035d334(void *a, void *b);
extern void FUN_001e9c78(void *p, unsigned long n);
extern unsigned long FUN_00006630(unsigned long a, unsigned long b, void *c, unsigned long d);
extern void FUN_00002534(const char *s, void *t);
extern void FUN_0005b190(unsigned long a, const char *s);
extern void FUN_0011d7e8(unsigned long);
extern unsigned long FUN_00034f70(void);
extern unsigned long FUN_00034a2c(void);
extern void FUN_00054354(void);
extern unsigned long FUN_0004b520(void *obj);
extern void FUN_0004b664(void *obj);
extern void FUN_0004b23d8(void *slot);
extern void FUN_0005ed18(unsigned long i, unsigned long v);
extern void FUN_0005edac(unsigned long i, unsigned long v);
extern unsigned long FUN_0005ee40(unsigned long);
extern unsigned long FUN_0005ee48(void *m);
extern unsigned long FUN_0005ee50(void *m);
extern unsigned long FUN_0005ee58(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
extern unsigned long FUN_0005eb78(void *buf, unsigned long n, unsigned long v);
extern unsigned long FUN_0005ea94(void *a, void *b, unsigned long c, unsigned long d);
extern void FUN_00063a50(void);
extern unsigned long FUN_000603bc(void);
extern unsigned long FUN_000639a0(unsigned long a, void *b);
extern unsigned long FUN_000636d0(void);
extern unsigned long FUN_000636d8(unsigned long v);
extern unsigned long FUN_000636a4(unsigned long a, unsigned long b);
extern unsigned long FUN_00060524(void);
extern unsigned long FUN_0005ac2c(void);
extern unsigned long thunk_FUN_00115080(void);
extern void thunk_FUN_00114330(void *dst, unsigned long n);
extern void sk_fill_buf(void *dst, unsigned long v, unsigned long n);     /* FUN_001157f0 */
extern void sk_clear_buf(void *buf);                                      /* FUN_001157d4 */
extern void FUN_00013be4(void);   /* per-thread base (in-file sk_perthread_base_get alias) */
extern void FUN_00013ea8(void);   /* per-thread block alloc (in-file sk_perthread_block_alloc) */
extern void FUN_004b0128(void);
extern void FUN_004b0158(void);
extern void FUN_004b0188(void);
extern void FUN_004b01b8(void);
extern void FUN_004b01e8(void);
extern void FUN_004b0244(void);
extern void FUN_004b0304(void);
extern void FUN_004b23d8(void *slot);
extern void sk_printf_banner(void);          /* thunk_FUN_00060524 */
extern void sk_vprintf(void *a, void *b);    /* FUN_00118c4c */
extern long sk_fill_debug_buffer(unsigned long *buf, unsigned long n); /* FUN_00115574 */
extern void sk_puts_word(unsigned long w);   /* FUN_00118b28 */
extern void sk_sleep(void *arg);             /* FUN_001183e0 */
extern void sk_abort_malloc(void) __attribute__((noreturn)); /* FUN_00116d60 */
extern void sk_printf(const char *fmt, ...); /* FUN_00118b28 */
extern unsigned long sk_buddy_lock(unsigned long a);    /* FUN_0011582c */
extern unsigned long sk_buddy_unlock(unsigned long a);  /* FUN_00115894 */
extern void dc_gva_region(unsigned long p, unsigned long size);
extern void sk_mem_clear_range(unsigned long p, unsigned long size, unsigned long fill); /* FUN_00117f8c */
/* Internal buddy helpers (static, defined near end of region). */
static unsigned long buddy_run_len(unsigned long bitmap, unsigned long idx);
static void unlink_buddy_region(unsigned long arena, unsigned long idx);

/* Generic kernel panic helpers (out-of-range; bodies in hv_glue_audit_*). */
extern long sk_tcb_slot_alloc(void);      /* FUN_00034f70 */
extern void sk_tcb_slot_release(void *s); /* FUN_004b23d8 */
extern void sk_panic_tcb(void) __attribute__((noreturn)); /* FUN_004b0068 */
extern void sk_panic_key(const char *s) __attribute__((noreturn)); /* FUN_0005b190 */
extern void sk_free_other(unsigned int level, unsigned long p); /* FUN_0000298c */
extern void sk_puts(const char *s);       /* FUN_00118b28 */
extern unsigned int *sk_error_slot(void); /* thunk_FUN_0006037c */

/*-------------------------------------------------------------------------
 * Forward declarations for functions defined in this region.
 *------------------------------------------------------------------------- */
unsigned long sk_tcb_register_async(void *tcb);
void sk_capbuf_release(void *capbuf);
unsigned long sk_capbuf_reserve(void *capbuf, void *a, unsigned long size);
void sk_capbuf_obj_release(unsigned long obj);
long sk_perthread_base_get(void);
long sk_perthread_key_get(void);
unsigned long sk_cap_transfer(void *tcb, void *msg, void *cap);  /* FUN_00013ee4 */
/*--------------------------------------------------------------------*/
/* FUN_000142d4 @ 0x000142d4   (est. sk_cap_slots_install)
 * Ghidra: void FUN_000142d4(undefined8 tcb, undefined8 m)
 * Installs received capability slots into a TCB: reads the number of
 * received caps from the per-thread area (tpidrro_el0 + 0x1e0), allocates
 * that many TCB slots (FUN_00034f70), and for each slot performs a
 * CallSupervisor(1) copy of the incoming capability word, binding it with
 * FUN_00015be8. Uses "cL4 transport.c" assertions on errors.
 * Confidence: low (structural summary).
 * Notes: strings s_cL4_transport_c_005aae37,
 *   s_TB_ASSERT__num_rcv_caps_<__TB_MA_005ab59c,
 *   s_TB_ASSERT__error____TB_ERROR_SUC_005ab644,
 *   s_TB_ASSERT__L4_ErrorCode_err_____L_005ab5fd; helpers FUN_0005ee40/
 *   00034f70/0005edac/00015be8/004b0334; global DAT_00657f98; stack canary. *//* In-region forward declarations (re-appended tail). */
unsigned long sk_alloc_at(unsigned long base, unsigned long size, void *align, unsigned int mode, unsigned long flags, void *a, void *b);
long sk_alloc_pages_pair(long *out, long *src);
void sk_arena_free(void *p, void *size, unsigned long flags, void *a);
void sk_assert_internal2(void *v);
void sk_assert_internal_c7(void);
void sk_assert_internal_cc(void);
void sk_boot_fail(unsigned int level, unsigned char flag, const char *fmt, ...);
void sk_buddy_clear_list(unsigned long arena, unsigned int clear, unsigned long idx, long units);
void sk_buddy_clear_range(unsigned long arena, unsigned long idx, unsigned long units);
long sk_buddy_find_free(unsigned long key);
void sk_buddy_free(unsigned long ptr);
void sk_buddy_free_split(unsigned long arena, long idx, unsigned long units);
void sk_buddy_init(void);
bool sk_buddy_is_in_arena(unsigned long ptr);
void sk_buf_relocate(void *buf);
long sk_bytebuf_grow(unsigned long keep, unsigned long count, unsigned long opts, void *buf);
unsigned long sk_cap_buf(void *obj);
void sk_cap_slots_install(void *tcb, void *m);
unsigned long sk_cap_transfer(void *tcb, void *msg, void *cap);
unsigned long sk_capbuf_alloc_meta(unsigned long size, void *b, unsigned long *cb);
unsigned long sk_capbuf_alloc_sized(unsigned long *cb, unsigned long size);
void sk_capbuf_copy(unsigned long *dst, void *src);
unsigned long sk_capbuf_free_or_accept(void *cb, void *b, long host, void *size, void *flags);
unsigned long sk_capbuf_free_or_accept2(void *a, void *b, long host, void *size, void *flags);
void sk_capbuf_init(void **cb, void *obj, void *size);
void sk_capbuf_reset(void *cb);
unsigned long sk_capbuf_resize(unsigned long *cb, void *b, unsigned long size);
void sk_capbuf_zero(void *cb);
bool sk_cmp_u8(char a, char b);
unsigned long sk_copyin_data(void *dst, void *src, unsigned long phys, unsigned long desc);
long sk_copyin_region(void **dst, long dst_end, unsigned long phys, unsigned long desc);
void sk_copyin_validate(long src, long len, long dst, long dst_end, long check);
void sk_copyout_desc(void);
void sk_copyout_desc2(void);
void sk_copyout_validate(void *src, long len);
void sk_copyout_validate2(void *src, long len);
unsigned long sk_dc_gva_clear(unsigned long base, unsigned long len, unsigned long granule);
unsigned long sk_desc_load(void);
unsigned long sk_desc_make(void *phys);
unsigned long sk_desc_pair(void *base, void *len);
unsigned long sk_desc_phys_validate(unsigned long phys, unsigned long desc);
void sk_desc_store(void **out, void **desc);
unsigned long sk_div8(long v);
unsigned long sk_entry_val(void *entry);
unsigned long sk_false(void);
void sk_fatal_copyin_bounds(void *v);
void sk_fatal_copyin_overflow(void *v);
void sk_fatal_copyin_size(void *v);
void sk_fatal_copyin_status(void *v);
void sk_fatal_disposition(unsigned long disposition);
void sk_fatal_retrieve_active(void);
void sk_fatal_retrieve_reply(void);
void sk_fatal_tb_decode(void *v);
void sk_fatal_tb_decode_overflow(void *v);
void sk_fatal_tb_decode_underflow(void *v);
void sk_fatal_tb_encode_overflow(void *v);
void sk_fatal_tb_zero_buf(void *v);
void sk_fatal_transport_overflow(void *v);
unsigned int sk_flag1(void);
void sk_guard_size_config(void *config, unsigned long size, int flag, uint8_t *out);
unsigned long sk_heap_aligned_alloc_variant(void **out, unsigned long size, void *arg, unsigned long flags);
unsigned long sk_heap_alloc(void *p, unsigned long size);
unsigned long sk_heap_alloc_or_error(unsigned long count, unsigned long size, void *arg);
void sk_heap_free(void *p);
void sk_heap_free_thunk(void *p);
void sk_heap_free_thunk2(void *p);
void sk_lock_acquire_failed_panic(void);
void sk_log(unsigned int level, const char *fmt, ...);
unsigned long sk_lookup_cap_buffer(void *key, void *hint);
void sk_malloc_breakpoint_check(unsigned int options);
void sk_malloc_log(unsigned long options, void *flag, long msg, void *a, void *b, void *c);
unsigned long sk_mem_clear(void *base, unsigned long len, unsigned char mode, unsigned long flags, void *a);
unsigned long sk_metadata_alloc(void *base, void *len, long size);
void sk_metadata_alloc2(void *a, void *b, void *c);
void sk_metadata_copy(void *dst, void *src, void *len);
void sk_metadata_copy2(void *dst, void *src, void *len);
void sk_metadata_decode(void *a, void *b, void *c, void *d, void *e, void *f);
void sk_metadata_destroy(void *a);
void sk_metadata_element_decode(void *a, void *b, void *c, void *d);
unsigned long sk_metadata_element_encode(void *a, void *b, void *c, void *d);
long sk_metadata_element_size(void);
long sk_metadata_flags(void);
void sk_metadata_iterate(void *a, void *b, long meta, void *c, void *d);
unsigned long sk_metadata_serialize(void **out, long out_end);
long sk_metadata_size_sum(long meta);
void sk_metadata_validate_all(void *a, void *b, void *c, void *d);
void sk_metadata_validate_range(long size, long base, long end);
void sk_metadata_walk(void *a, void *b, void *c, long meta, void *d, void *e);
void sk_metadata_write(uint8_t *out, void *a, uint16_t b, void *c, void *d, void *e);
unsigned long sk_msg_accept_complex(void **msg, int *query, void **out, void *flags);
unsigned long sk_msg_accept_fail(void);
void sk_msg_accept_init(void **msg, void *m, int mode, void *size, void *flags);
void sk_msg_accept_reply(void *a, void *b, void *c, void *d);
void sk_msg_accept_wrapper(void *a, void *b, void *c, void *d);
void sk_msg_append_region(void *msg, unsigned long *out, long *out_len, long cb);
unsigned long sk_msg_begin(int *msg, void *host, uint8_t disposition);
unsigned long sk_msg_cap_accept(void *obj, unsigned long size, unsigned long flags, unsigned long *out, unsigned long *cb);
unsigned long sk_msg_cap_accept_single(void *head, long msg, long *out, void *cb);
unsigned long sk_msg_cap_accept_variant(void *a, void *obj, unsigned long size, unsigned long *out, unsigned long *cb);
unsigned long sk_msg_cap_append(void *msg, unsigned long cap);
unsigned long sk_msg_cap_get(void *msg, long i);
unsigned long sk_msg_cap_pop(void *msg, long *out);
unsigned long sk_msg_cap_send_accept(void *head, void *msg2, long msg, void *b, void *cb);
void sk_msg_copy_region(void *src, void *dst, unsigned long len);
unsigned int sk_msg_decode_f32(int *msg, unsigned int *out);
void sk_msg_decode_f32_checked(void);
unsigned long sk_msg_decode_f64(int *msg, unsigned long *out);
void sk_msg_decode_f64_checked(void);
uint8_t sk_msg_disposition_get(void *msg);
void sk_msg_done(void *msg);
unsigned long sk_msg_encode_f32(unsigned int v, int *msg);
void sk_msg_encode_f32_checked(void);
unsigned long sk_msg_encode_f64(unsigned long v, int *msg);
void sk_msg_encode_f64_checked(void);
bool sk_msg_flag_test(void *msg, uint16_t mask);
bool sk_msg_host_is(void *msg, void *host);
void sk_msg_init(void *msg);
unsigned long sk_msg_install(void **msg, int mode, void *m, long host, unsigned long size, void *flags);
void sk_msg_install_wrapper(void *a, void *b, void *c, void *d, void *e);
unsigned long sk_msg_none(void);
unsigned long sk_msg_num_caps(void *msg);
unsigned long sk_msg_payload_len(void *msg);
void sk_msg_pipe_accept(void *pipe, void *b, int *msg);
void sk_msg_pipe_build_wrap(void *a, void *b, void *meta);
unsigned long sk_msg_pipe_create(void *a, void *b, void *c, void *d);
void sk_msg_pipe_create_wrap(void *a, void *b, void *meta);
void sk_msg_pipe_destroy(void *pipe);
void sk_msg_pipe_validate(void *pipe);
void sk_msg_prepend_region(void *msg, unsigned long start, unsigned long len, long cb);
void sk_msg_recv_collect(void *msg, void *tcb);
void sk_msg_recv_large(void *a, void *b, void *c, void *d);
unsigned long sk_msg_region_copy_in(int *msg, void *src, unsigned long len);
void sk_msg_region_copy_out(void *msg, void *dst, unsigned long n);
void sk_msg_region_copy_put(void *msg, void *src, unsigned long len);
void sk_msg_region_get64(int *msg, void **out);
void sk_msg_region_get8_v2(int *msg, uint8_t *out);
void sk_msg_region_put16(int *msg, uint16_t v);
void sk_msg_region_put32(int *msg, uint32_t v);
void sk_msg_region_put64(int *msg, void *v);
void sk_msg_region_put8(int *msg, uint8_t v);
void sk_msg_region_put8_v2(int *msg, uint8_t v);
unsigned long sk_msg_reject(void);
unsigned long sk_msg_reply_recv(void *tcb, int *query, void **msg, unsigned long *flags);
void sk_msg_reply_send(void *tcb, void *query, void *msg, void **out);
void sk_msg_send_complex(void *a, void *b, void *c, void *d);
void sk_msg_send_complex2(void *a, void *b, void *c, void *d);
void sk_msg_set_arg(void *msg, void *v);
void sk_msg_set_disposition(void *msg, uint8_t disposition);
void sk_msg_set_host(void *msg, void *host);
void sk_msg_set_host_field(void *msg, void *v);
void sk_msg_set_payload_len(void *msg, void *v);
void sk_msg_set_state(void *msg, unsigned int state);
void sk_msg_set_transport_end(void *msg, void *v);
void sk_msg_state_advance(int *msg);
unsigned int sk_msg_state_get(void *msg);
void sk_msg_teardown(void **msg, void *b, void *c, void *d);
unsigned long sk_msg_transport_len(void *msg);
void sk_node_invoke(long node);
void sk_noop(void);
void sk_noop2(void);
void sk_noop2_thunk(void);
void sk_noop3(void);
void sk_obj_destroy_dispatch(void *obj);
void sk_obj_dispatch(void **obj);
void sk_obj_is_active(void **obj);
void sk_obj_method18(void *obj, void *a, void *b, void *c);
void sk_obj_method20(void *obj, void *a);
void sk_obj_method28(void *obj, void *a, void *b, void *c);
unsigned long sk_obj_method30(void *obj);
unsigned long sk_obj_method38(void *obj);
void sk_obj_set_data(void *obj, void *data);
unsigned int sk_obj_state(void **obj);
bool sk_obj_type_check(void *obj);
bool sk_obj_type_check2(void *obj);
void sk_obj_type_query(void **obj);
void sk_payload_copyin(void *dst, void *src, void *len);
void sk_payload_copyout(void *dst, void *src, void *len);
void sk_payload_decode(void *dst, void *src, void *len, void *desc);
void sk_payload_encode(void *dst, void *src, void *len, void *desc);
void sk_payload_size(void *a);
void sk_pt_desc_copy(void *a, void *b, void *c);
void sk_pt_desc_free(void *a, void *b);
unsigned long sk_pt_desc_resolve(unsigned long a, unsigned long b);
void sk_pt_desc_size(void *a);
void sk_pt_desc_validate(void *a, void *b, void *c);
unsigned long sk_ptr_deref(void **p);
unsigned long sk_range_check(long base, unsigned long size, unsigned long avail, long p, long end);
unsigned long sk_region_alloc_lazy(void **slot);
unsigned long sk_region_alloc_lazy2(void *slot);
unsigned long sk_region_map(unsigned long *out, void *key);
unsigned long sk_region_map_impl(unsigned long *desc, unsigned long *out_base);
unsigned long sk_region_map_small(unsigned long *desc);
void sk_registry_bind(void *head, void **entry);
unsigned long sk_registry_entry_create(void *key, void *val, void *meta);
unsigned long sk_registry_insert(unsigned long *head, unsigned long key, void *val, void *meta);
unsigned long sk_registry_lookup(unsigned long head, unsigned long key);
void sk_registry_remove(void **head, long key);
void sk_sched_node_create(unsigned int a, unsigned int b);
void sk_sched_node_create_data(unsigned int a, void *data, unsigned int b);
long sk_serialized_size(void);
void sk_serialized_size_store(void **out);
unsigned long sk_size4(void);
unsigned long sk_size8(void);
bool sk_sorted_contains(void *list, unsigned long key);
unsigned long sk_stub_zero(void);
long sk_tb_conn_alloc(void *a, void *b);
void sk_tb_conn_alloc_single(void *a, void *b);
void sk_tb_conn_attach(void *a, void *b);
void sk_tb_conn_close(void);
void sk_tb_conn_close2(void);
unsigned long sk_tb_conn_create(long *out);
void sk_tb_conn_handler(long *conn, unsigned long mode);
void sk_tb_conn_teardown(void);
unsigned long sk_tb_decode_word(void *src);
unsigned long sk_tb_encode_word(void *src, void *out);
unsigned int sk_tb_forward_dispatch(void *a, void *b, void *c, unsigned long conn, void *handler);
void sk_tb_forward_get(void);
unsigned int sk_tb_forward_handler(void *data, void *a, void *b, void *c);
void sk_tb_forward_meta(void *a, void *b);
void sk_tb_forward_meta2(void *a, void *b);
unsigned int sk_tb_forward_send(void *a, void *b, void *c, unsigned long conn);
unsigned int sk_tb_forward_send_flag(void);
unsigned int sk_tb_forward_send_flag2(void);
unsigned long sk_tb_frame_prepare(void *frame);
void sk_tb_get64(void *th, void **out);
void sk_tb_get8(void *th, uint8_t *out);
long sk_tb_handler_resolve(unsigned long entry);
void sk_tb_init_get(void);
unsigned long sk_tb_pipe_alloc(void *a, void *b, void *c, void *d);
unsigned long sk_tb_pipe_alloc5(void *a, void *b, void *c, void *d, void *e);
unsigned long sk_tb_pipe_alloc6(void *a, void *b, void *c, void *d, void *e, void *f);
void sk_tb_pipe_close(void);
void sk_tb_pipe_close2(void);
void sk_tb_pipe_config(void *a, uint8_t kind, void *b, uint8_t kind2);
void sk_tb_pipe_config5(void *a, uint8_t kind, void *b, uint8_t kind2, void *c);
void sk_tb_pipe_config6(void *a, uint8_t kind, void *b, uint8_t kind2, void *c, void *d);
void sk_tb_pipe_destroy(void);
void sk_tb_pipe_destroy2(void);
void sk_tb_put16(void *th, uint16_t v);
void sk_tb_put32(void *th, uint32_t v);
void sk_tb_put64(void *th, void *v);
void sk_tb_put8(void *th, uint8_t v);
void sk_tb_put8_v2(void *th, uint8_t v);
unsigned long sk_tb_reader_reset(void *reader);
unsigned long sk_tb_status_encode(unsigned long status);
unsigned long sk_tb_status_mask(void);
void sk_tb_validate_component(long *data, long end);
void sk_tb_validate_data(long *data, long end);
unsigned long sk_tcb_alloc_bind(void *a, void *b);
long sk_tcb_alloc_dispatch(void *cfg);
long sk_tcb_alloc_ext(void *cfg);
unsigned long sk_tcb_alloc_obj(void *a);
int sk_tcb_cap_copy(void *src_tcb, void *dst_tcb, void **out, unsigned int flags);
unsigned long sk_tcb_cap_copy_commit(void *a, unsigned long size, void *c, unsigned long *out);
void sk_tcb_cap_release_commit(void *a, void **slot, void *c, void *size);
unsigned int sk_tcb_cfg_flags(void *cfg);
unsigned long sk_tcb_handle(void *tcb);
void sk_tcb_init_regions(void *cfg, void *tcb);
long sk_tcb_msg_accept(long self, void **msg);
long sk_tcb_obj_bind(void *a, void *b);
void sk_tcb_obj_destroy(void *tcb);
void sk_tcb_obj_destroy_thunk(void *tcb);
void sk_tcb_obj_destroy_thunk2(void *tcb);
void sk_tcb_obj_install_handler(void *obj, void *handler, void *arg);
unsigned long sk_tcb_register_async(void *tcb);
unsigned long sk_tcb_send(void *tcb, void *msg, void **out);
void sk_tcb_slot_alloc_init(void *td, unsigned long count);
void sk_tcb_slot_alloc_teardown(void *td);
void sk_tcb_slot_recv_assert(void);
unsigned long sk_thread_local_alloc(void);
void sk_thread_local_free(unsigned long t);
void sk_tightbeam_bind(void *client, long *slot, void *table);
void sk_tightbeam_connection_alloc(void *a, void *b, void *c, void *d);
void sk_tightbeam_connection_alloc2(void *a, void *b, void *c, void *d);
void sk_tightbeam_connection_alloc3(void *a, void *b, void *c, void *d);
void sk_tightbeam_connection_close(void *a);
void sk_tightbeam_connection_close2(void *a);
void sk_tightbeam_connection_init(void *a, void *b, void *c, void *d);
void sk_tightbeam_connection_recv(void *a, void *b, void *c, void *d);
void sk_tightbeam_connection_send(void *a, void *b, void *c, void *d);
void sk_tightbeam_dispatch(void *a, void *b, void *c, void *d);
void sk_tightbeam_forward(void *a, void *b, void *c, void *d);
void sk_tightbeam_forwarding(void *a, void *b, void *c, void *d);
void sk_tightbeam_forwarding2(void *a, void *b, void *c, void *d);
void sk_tightbeam_forwarding3(void *a, void *b, void *c, void *d);
void sk_tightbeam_frame_decode(void *a, void *b, void *c, void *d);
void sk_tightbeam_frame_encode(void *a, void *b, void *c, void *d);
void sk_tightbeam_init(void *a, void *b, void *c, void *d);
void sk_tightbeam_metadata(void *a, void *b, void *c, void *d);
void sk_tightbeam_recv(void *a, void *b, void *c, void *d);
void sk_tightbeam_register(void *client);
void sk_tightbeam_send(void *a, void *b, void *c, void *d);
void sk_tightbeam_validate(void *a, void *b, void *c, void *d);
void sk_tightbeam_validate2(void *a, void *b, void *c, void *d);
unsigned long sk_trap_iter_any(void **list, long n, void *arg);
unsigned long sk_true(void);
long sk_wordbuf_grow(unsigned long keep, unsigned long count, unsigned long opts, void *buf);
void sk_wordbuf_relocate(void);
unsigned long long sk_zero_pair(void);
unsigned int sk_zone0_aligned_alloc_out(void **out, unsigned long size);
void sk_zone0_method_dispatch(void *p);
long sk_zone_aligned_alloc(unsigned long zone, unsigned long align, unsigned long size, unsigned int flags);
unsigned long sk_zone_aligned_alloc_try(unsigned long zone, unsigned long size);
unsigned long sk_zone_alloc_slot(unsigned long zone);
unsigned long sk_zone_calloc(unsigned long zone, unsigned long count, unsigned long size, unsigned long flags);
void sk_zone_create_desc(void **desc, uint8_t kind, uint8_t flags, unsigned int a, unsigned int b, unsigned int granule, void *name, unsigned long base, unsigned int align);
void sk_zone_free_lookup(unsigned long p, unsigned int start_idx);
unsigned long sk_zone_lookup(void *key, void **out_zone, unsigned int start_idx);
long sk_zone_match(void *p);
long sk_zone_match_thunk(void *p);
void sk_zone_named(unsigned long zone);
void sk_zone_ref_run(unsigned long zone, void **run);
void sk_zone_register(void *zone);
/* Forward declarations for in-region functions used before definition. */
void *sk_msg_pipe_build(void *a, void *b, unsigned long flags, void *meta);   /* FUN_00017a88 */
unsigned long sk_msg_reply_recv_large(void *tcb, void *query, void *msg, void *flags);
void *sk_zone_alloc_n(unsigned long zone, unsigned long size);                 /* FUN_00012060 */
void *sk_alloc_aligned_save(void *param_1, unsigned long size, unsigned long flags); /* FUN_00010584 */
void *sk_arena_alloc(unsigned long size, void *align, unsigned long guard, unsigned long mode, void *a); /* FUN_00011b18 */
void sk_tcb_field_apply(unsigned long a, void *b, unsigned long c);            /* FUN_0006290c */


/*--------------------------------------------------------------------*/
/* FUN_00014470 @ 0x00014470   (est. sk_ptr_deref)
 * Ghidra: undefined8 FUN_00014470(undefined8 *p)
 * Dereferences and returns *p.
 * Confidence: high (trivial). *//* In-region forward declarations (restored tail). */
extern void *sk_heap_calloc(unsigned long count, unsigned long size, void *arg); /* FUN_00010244 */
extern unsigned long FUN_0001505c(void);
extern void FUN_000150cc(unsigned long p);
extern unsigned int FUN_00015448(void);
extern void FUN_000154d0(unsigned long obj);
extern unsigned long FUN_000159b8(void *obj);
extern unsigned int FUN_000159c0(unsigned long msg);
extern uint8_t FUN_000159c8(long msg);
extern long FUN_00016458(void *cfg);
extern unsigned long FUN_000183f0(void *a, void *b, long c, void *d, unsigned long e);
extern void FUN_004b0068(void);
extern void FUN_004b0408(void);
extern void *sk_tcb_create_zeroed(void *cfg);
extern void *FUN_00014628(void *a, void *b);
extern void FUN_004b03d8(void);
extern void FUN_004b03f0(void);
extern long FUN_00015e9c(void *a, long b);
extern void FUN_00015904(long a, long b);
extern unsigned long FUN_00017e94(unsigned long a, void *b, ...);
extern long FUN_000181f4(void *a, long b, long *c, void *d);

/*-------------------------------------------------------------------------
 * Missing helper externs (reconstructed thunks; in-file FUN_ names match
 * their English definitions; external helpers declared per call-site arity).
 *------------------------------------------------------------------------- */
extern unsigned long FUN_000102f4(unsigned long, unsigned long, void *arg);
extern unsigned long FUN_000132d4(long);
extern unsigned long FUN_000132e0(void *key, void *hint);
extern unsigned long FUN_00014470(void **p);
extern unsigned long FUN_00014478(void *cfg);
extern unsigned long FUN_000145bc(void *a, void *b);
extern unsigned long FUN_000147e0(void **obj);
extern unsigned long FUN_0001483c(void **obj);
extern unsigned long FUN_0001485c(void **msg, int *query, void **out, void *flags);
extern unsigned long FUN_00014bd4(void *a, void *b, void *c, void *d, void *e);
extern unsigned long FUN_00014c18(unsigned long *cb, unsigned long);
extern unsigned long FUN_00014c90(void *cb);
extern unsigned long FUN_00014ce0(void *a, void *b, long, void *size, void *flags);
extern unsigned long FUN_00014db8(void **msg, void *m, int, void *size, void *flags);
extern unsigned long FUN_00014e34(void **msg, int, void *m, long, unsigned long, void *flags);
extern unsigned long FUN_00014f2c(void);
extern unsigned long FUN_00014f90(void *a, void *b, void *c, void *d);
extern unsigned long FUN_00015108(unsigned long *head, unsigned long, void *val, void *meta);
extern unsigned long FUN_000151c8(void **head, long);
extern unsigned long FUN_00015264(unsigned long, unsigned long);
extern unsigned long FUN_0001532c(unsigned int, unsigned int);
extern unsigned long FUN_00015388(unsigned int, void *data, unsigned int);
extern unsigned long FUN_000153ec(long);
extern unsigned long FUN_00015548(unsigned long obj, ...);
extern unsigned long FUN_000155e8(unsigned long obj, ...);
extern unsigned long FUN_00015630(unsigned long obj, ...);
extern unsigned long FUN_00015670(unsigned long obj, ...);
extern unsigned long FUN_000156b8(unsigned long obj, ...);
extern unsigned long FUN_000156e0(unsigned long obj, ...);
extern unsigned long FUN_00015708(void);
extern unsigned long FUN_00015734(void *cb);
extern unsigned long FUN_0001574c(unsigned long *dst, void *src);
extern unsigned long FUN_00015834(void *msg);
extern unsigned long FUN_0001585c(void *msg, unsigned int);
extern unsigned long FUN_00015864(void *msg, uint8_t);
extern unsigned long FUN_0001586c(unsigned long msg, unsigned long host, ...);
extern unsigned long FUN_0001590c(void *msg);
extern unsigned long FUN_00015964(void *msg);
extern unsigned long FUN_00015984(unsigned int *obj, unsigned long);
extern unsigned long FUN_000159d0(void *msg);
extern unsigned long FUN_00015b8c(void *msg, void *v);
extern unsigned long FUN_00015b94(void *msg, void *host);
extern unsigned long FUN_00015ba4(void *msg);
extern unsigned long FUN_00015bac(void *msg, void *v);
extern unsigned long FUN_00016174(unsigned long *out, void *key);
extern unsigned long FUN_00016208(unsigned long *desc, unsigned long *out_base);
extern unsigned long FUN_00016318(unsigned long *desc);
extern unsigned long FUN_00016ba4(unsigned long *cb, void *b, unsigned long);
extern unsigned long FUN_00016c24(void *msg, void *tcb);
extern unsigned long FUN_00017a08(void *a, void *b, void *c, void *d);
extern unsigned long FUN_00017a88(void *a, void *b, unsigned long, void *meta);
extern unsigned long FUN_00017b7c(void *a, void *b, void *meta);
extern unsigned long FUN_00017b88(void *a, void *b, void *meta);
extern unsigned long FUN_00017bd4(void);
extern unsigned long FUN_00017c14(void *pipe, void *b, int *msg);
extern unsigned long FUN_00017edc(void *a, void *obj, unsigned long, unsigned long *out, unsigned long *cb);
extern unsigned long FUN_00019490(void);
extern unsigned long FUN_00019588(void);
extern unsigned long FUN_00019670(void);
extern unsigned long FUN_00019768(void);
extern unsigned long FUN_0001a0d0(void *client, long *slot, void *table);
extern unsigned long FUN_0001a11c(unsigned long a, unsigned long b);
extern unsigned long FUN_0001a138(void);
extern unsigned long FUN_0001a1dc(void *dst, void *src, unsigned long, unsigned long);
extern unsigned long FUN_0001a2f4(long, long, long, long, long);
extern unsigned long FUN_0001a760(void);
extern unsigned long FUN_0001a838(void **out, long);
extern unsigned long FUN_0001ab94(void *base, void *len, long);
extern unsigned long FUN_0001adec(void *a, void *b, void *c, long, void *d, void *e);
extern unsigned long FUN_0001aeec(void *a, void *b, void *c, void *d, void *e, void *f);
extern unsigned long FUN_0001afb4(void *a, void *b, void *c, void *d);
extern unsigned long FUN_0001db00(long, unsigned long, unsigned long, long, long);
extern unsigned long FUN_0001db94(long);
extern unsigned long FUN_0001dc08(long, long);
extern unsigned long FUN_0001dc8c(long, long);
extern unsigned long FUN_0001dd00(void *buf);
extern long FUN_0001dd14(unsigned long keep, unsigned long count, unsigned long opts, void *buf);
extern unsigned long FUN_0001dde4(unsigned long, unsigned long, unsigned long, void *buf);
extern unsigned long FUN_0001deb0(unsigned long a, unsigned long b, unsigned long c);
extern unsigned long FUN_0001e12c(long *data, long);
extern unsigned long FUN_0001e3e0(long *data, long);
extern unsigned long FUN_0001eec8(void *src, void *out);
extern unsigned long FUN_0001ef00(void *src);
extern unsigned long FUN_0001f0f0(long *conn, unsigned long);
extern unsigned long FUN_0001f1d0(unsigned long a, ...);
extern unsigned long FUN_0001f38c(void *data, void *a, void *b, void *c);
extern unsigned long FUN_0001f414(void *a, void *b);
extern unsigned long FUN_0001f514(void *a, void *b);
extern unsigned long FUN_0001f670(unsigned long a, ...);
extern unsigned long FUN_0001f834(void);
extern unsigned long FUN_0001fa18(unsigned long a, ...);
extern unsigned long FUN_0001fd28(void *reader);
extern unsigned long FUN_0001fd9c(void *frame);
extern unsigned long FUN_0001fde8(unsigned long);
extern unsigned long FUN_0001fee8(void);
extern unsigned long FUN_000259c0(unsigned long, unsigned long);
extern unsigned long FUN_0004b710(unsigned long, unsigned long, unsigned long);
extern unsigned long FUN_0011582c(unsigned long);
extern unsigned long FUN_00115894(unsigned long);
extern unsigned long FUN_004b0080();
extern unsigned long FUN_004b0368(unsigned long);
extern unsigned long FUN_004b03a0(unsigned long);
extern unsigned long FUN_004b0438();
extern unsigned long FUN_004b0468();
extern unsigned long FUN_004b0498();
extern unsigned long FUN_004b04c8();
extern unsigned long FUN_004b04f8();
extern unsigned long FUN_004b0528();
extern unsigned long FUN_004b0558(unsigned long);
extern unsigned long FUN_004b05a0();
extern unsigned long FUN_004b05c4();
extern unsigned long FUN_004b05e8();
extern unsigned long FUN_004b060c();
extern unsigned long FUN_004b063c();
extern unsigned long FUN_004b066c();
extern unsigned long FUN_004b0690();
extern unsigned long FUN_004b06c0();
extern unsigned long FUN_004b06e4();
extern unsigned long FUN_004b0714();
extern unsigned long FUN_004b0744(unsigned long);
extern unsigned long FUN_004b07c0();
extern unsigned long FUN_004b07f0();
extern unsigned long FUN_004b09e8();
extern unsigned long FUN_004b0a18();
extern unsigned long FUN_004b0a34();
extern unsigned long FUN_004b0a40();
extern unsigned long FUN_004b0c04();
extern unsigned long FUN_004b0c28();
extern unsigned long FUN_004b0c4c();
extern unsigned long FUN_004b0c7c();
extern unsigned long FUN_004b0cdc();
extern unsigned long FUN_004b0d3c();
extern unsigned long FUN_004b0d60();
extern unsigned long FUN_004b0d84();
extern unsigned long FUN_004b0da8();
extern unsigned long FUN_004b0dcc();
extern unsigned long FUN_004b0df0();
extern unsigned long FUN_004b0e14();
extern unsigned long FUN_004b0e38();
extern unsigned long FUN_004b0e5c();
extern unsigned long FUN_004b0e80();
extern unsigned long FUN_004b0ea4();
extern unsigned long FUN_004b0ec8();
extern unsigned long FUN_004b0eec();
extern unsigned long FUN_004b0f10();
extern unsigned long FUN_004b0f34();
extern unsigned long FUN_004b0f58();
extern unsigned long FUN_004b0f7c();
extern unsigned long FUN_004b0fa0();
extern unsigned long FUN_004b0fc4();
extern unsigned long FUN_004b0fe8();
extern unsigned long FUN_004b100c();
extern unsigned long FUN_004b1030();
extern unsigned long FUN_004b1054();
extern unsigned long FUN_004b1078();
extern unsigned long FUN_004b1150();
extern unsigned long FUN_004b1174();
extern unsigned long FUN_004b1198();
extern unsigned long FUN_004b11bc();
extern unsigned long FUN_004b11e0();
extern unsigned long FUN_004b1204();
extern unsigned long FUN_004b1228();
extern unsigned long FUN_004b124c();
extern unsigned long FUN_004b1270();
extern unsigned long FUN_004b1294();
extern unsigned long FUN_004b12b8();
extern unsigned long FUN_004b12dc();
extern unsigned long FUN_004b1300();
extern unsigned long FUN_004b1324();
extern unsigned long FUN_004b1348();
extern unsigned long FUN_004b136c();
extern unsigned long FUN_004b1390();
extern unsigned long FUN_004b13fc();
extern unsigned long FUN_004b1420();
extern unsigned long FUN_004b1444();
extern unsigned long FUN_004b1468();
extern unsigned long FUN_004b148c();
extern unsigned long FUN_004b14b0();
extern unsigned long FUN_004b14d4();
extern unsigned long FUN_004b14f8();
extern unsigned long FUN_004b151c();
extern unsigned long FUN_004b1540();
extern unsigned long FUN_004b1564();
extern unsigned long FUN_004b1588();
extern unsigned long FUN_004b15ac();
extern unsigned long FUN_004b15d0();
extern unsigned long FUN_004b1684();
extern unsigned long FUN_004b16a8();
extern unsigned long FUN_004b16cc();
extern unsigned long FUN_004b16f0();
extern unsigned long FUN_004b1714();
extern unsigned long FUN_004b1738();
extern unsigned long FUN_004b175c();
extern unsigned long FUN_004b1780();
extern unsigned long FUN_004b17a4();
extern unsigned long FUN_004b17c8();
extern unsigned long FUN_004b17ec();
extern unsigned long FUN_004b1810();
extern unsigned long FUN_004b1834();
extern unsigned long FUN_004b1858();
extern unsigned long FUN_004b187c();
extern unsigned long FUN_004b18a0();
extern unsigned long FUN_004b18c4();
extern unsigned long FUN_004b18e8();
extern unsigned long FUN_004b190c();
extern unsigned long FUN_004b1930();
extern unsigned long FUN_004b1954();
extern unsigned long FUN_004b1978();
extern unsigned long FUN_004b199c();
extern unsigned long FUN_004b19c0();
extern unsigned long FUN_004b19e4();
extern unsigned long FUN_004b1a08();
extern unsigned long FUN_004b1a2c();
extern unsigned long FUN_004b1a50();
extern unsigned long thunk_FUN_000126e8();
extern unsigned long FUN_client_method30(unsigned long a, unsigned long b, void *c, void *d, unsigned long e, unsigned long f);
extern unsigned long FUN_client_method8(unsigned long a, void *b);
extern unsigned long FUN_client_method28(unsigned long a, unsigned long b, unsigned long c);
extern unsigned long FUN_client_method40(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
extern unsigned long FUN_client_destroy(unsigned long a);
extern unsigned long FUN_0036b270(unsigned long v);
/* Out-of-range data globals referenced in this region. */
extern unsigned long DAT_004bb180;
extern unsigned long DAT_0064c098;
extern unsigned long LAB_006593e8;
extern unsigned long DAT_00659b58;
extern unsigned int  UINT_006775b0;
extern unsigned long DAT_004be910;
extern long DAT_00657778;
extern unsigned long DAT_004c0740;
extern unsigned long DAT_0064c0f8;
extern unsigned long DAT_004edbe8;
extern unsigned long DAT_004bb860;
extern unsigned long DAT_0064c100;
extern unsigned long DAT_004ed758;
extern unsigned long LAB_00659c50;






































unsigned long sk_ptr_deref(void **p)
{
    return (unsigned long)*p;
}

/*--------------------------------------------------------------------*/
/* FUN_00014478 @ 0x00014478   (est. sk_tcb_alloc_dispatch)
 * Ghidra: long FUN_00014478(undefined8 cfg)
 * Allocates a TCB by dispatching on the object type (FUN_00015448): type 0xd
 * uses FUN_00016458, type 3 allocates+inits via sk_tcb_init_regions, type 1
 * uses sk_tcb_create_zeroed. Returns the TCB or traps.
 * Confidence: medium
 * Notes: helpers FUN_00015448/00016458/00010244/00013348/00012e48/004b0068;
 *   trap 0x1450c. */
long sk_tcb_alloc_dispatch(void *cfg)
{
    int t = FUN_00015448();
    long tcb;

    if (t == 0xd) {
        tcb = FUN_00016458(cfg);
    } else if (t == 3) {
        tcb = (long)sk_heap_calloc(1, 0x118, (void *)0x1082040eda8e2da);  /* FUN_00010244 */
        if (tcb != 0) {
            sk_tcb_init_regions(cfg, (void *)tcb);  /* FUN_00013348 */
            return tcb;
        }
        FUN_004b0068();
    } else if (t == 1) {
        tcb = (long)sk_tcb_create_zeroed(cfg);  /* FUN_00012e48 */
    } else {
        tcb = 0;
    }
    if (tcb != 0) return tcb;
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x1450c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00014510 @ 0x00014510   (est. sk_tcb_obj_create)
 * Ghidra: undefined8 * FUN_00014510(undefined8 obj)
 * Creates a 0x40-byte TCB object wrapper: allocates it (tag
 * 0x10820409f8ec750), stores the object handle at offset 0, and records the
 * thread-local base (FUN_0001505c) at offset 6. Panics on allocation
 * failure; traps on wrap.
 * Confidence: medium
 * Notes: tag 0x10820409f8ec750; helpers FUN_00010244/0001505c/004b0068;
 *   trap 0x14574. */
void *sk_tcb_obj_create(void *obj)
{
    unsigned long *t = (unsigned long *)sk_heap_calloc(1, 0x40, (void *)0x10820409f8ec750);  /* FUN_00010244 */
    if (t == 0) FUN_004b0068();
    if ((unsigned long)t <= (unsigned long)t + 8) {
        *t = (unsigned long)obj;
        t[6] = FUN_0001505c();
        return t;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x14574) */
}

/*--------------------------------------------------------------------*/
/* FUN_00014578 @ 0x00014578   (est. sk_tcb_obj_destroy)
 * Ghidra: void FUN_00014578(undefined8 *tcb)
 * Destroys a TCB object wrapper: releases the object (FUN_000154d0), the
 * thread-local base (FUN_000150cc), any attached payload (FUN_0004b664),
 * then frees the wrapper.
 * Confidence: medium
 * Notes: helpers FUN_000154d0/000150cc/0004b664/thunk_FUN_00012568. */
void sk_tcb_obj_destroy(void *tcb)
{
    unsigned long *t = (unsigned long *)tcb;
    FUN_000154d0(*t);
    FUN_000150cc(t[6]);
    if (t[2] != 0) FUN_0004b664(0);
    sk_heap_free(tcb);
}

/*--------------------------------------------------------------------*/
/* FUN_000145bc @ 0x000145bc   (est. sk_tcb_obj_bind)
 * Ghidra: long FUN_000145bc(undefined8 a, undefined8 b)
 * Creates a TCB object wrapper (FUN_00014510), records a bound payload
 * (FUN_0004b520) at offset 0x10, installs a handler (FUN_00015460) bound to
 * FUN_00014628, and stores the thread-local base (FUN_0001505c) at 0x38.
 * Confidence: medium
 * Notes: helpers FUN_00014510/0004b520/00015460/00014628/0001505c. */
long sk_tcb_obj_bind(void *a, void *b)
{
    long t = (long)sk_tcb_obj_create(0);  /* FUN_00014510 */
    *(unsigned long *)(t + 0x10) = FUN_0004b520(b);
    sk_tcb_obj_install_handler(a, (void *)FUN_00014628, (void *)t);  /* FUN_00015460 */
    *(unsigned long *)(t + 0x38) = FUN_0001505c();
    return t;
}

/*--------------------------------------------------------------------*/
/* FUN_00014628 @ 0x00014628   (est. sk_tcb_msg_accept)
 * Ghidra: long FUN_00014628(long self, undefined8 *msg)
 * Accepts an incoming message on a TCB (self): validates the message state
 * and disposition, and depending on the message flags routes through a
 * capability accept (FUN_000183f0), a payload handler (param_2[3]), or a
 * fallback method (param_2[2]), eventually returning the accepted object.
 * Uses "TB_ASSERT" panics for malformed messages.
 * Confidence: low (structural summary; many 004b03xx panic helpers).
 * Notes: helpers FUN_000159b8/000159c0/000159c8/000183f0/00015e9c/
 *   00015904/00017e94/000181f4/00014478/000145bc/000153ec; panics
 *   004b0368/03a0/0468/0438/03d8/03f0/0408. */
long sk_tcb_msg_accept(long self, void **msg)
{
    long *buf;
    long result = self;
    unsigned long obj = (unsigned long)*msg;

    buf = (long *)FUN_000159b8();
    if ((int)FUN_000159c0(self) == 4) {
        if ((int)FUN_000159c8(self) == 1) {
            if (buf == 0 || *buf == 0) {
                FUN_004b0408();
                return (long)sk_tcb_alloc_dispatch(0);  /* FUN_00014478 */
            }
            if ((*(uint16_t *)((char *)buf + 0x2a) >> 2 & 1) != 0) {
                if (msg[7] != 0) {
                    long r = FUN_000183f0(msg[7], msg, self, &result, obj);
                    return r;
                }
                FUN_004b03d8();
                return (long)sk_tcb_alloc_dispatch(0);
            }
            if ((*(uint16_t *)((char *)buf + 0x2a) & 1) != 0) {
                if (msg[6] != 0) {
                    long h = FUN_00015e9c(msg[6], self);
                    if (h == 0) return 0;
                    FUN_00015904(self, h);
                } else {
                    FUN_004b03f0();
                    return (long)sk_tcb_alloc_dispatch(0);
                }
            }
            if ((void *)msg[3] != 0) {
                long h = ((long (*)(void **, long, void *))msg[3])(msg, self, msg[4]);
                if (h == 0) return 0;
                result = h;
                long *hb = (long *)FUN_000159b8(h);
                if (FUN_00017e94(obj, *(void **)(hb + 0x18)) == 0) return h;
                if (msg[7] != 0) {
                    long r = FUN_000181f4(msg[7], h, &result, msg);
                    if (r != 0) result = 0;
                    return result;
                }
            } else {
                long m = (long)msg[2];
                if (m != 0) {
                    long h = (**(long (**)(long, void **, long))(m + 0x10))(m, msg, self);
                    if (h == 0) return 0;
                    result = h;
                    long *hb = (long *)FUN_000159b8(h);
                    if (FUN_00017e94(obj, *(void **)(hb + 0x18)) == 0) return h;
                    if (msg[7] != 0) {
                        long r = FUN_000181f4(msg[7], h, &result, msg);
                        if (r != 0) result = 0;
                        return result;
                    }
                }
            }
            FUN_004b0408();
            return (long)sk_tcb_alloc_dispatch(0);
        }
        FUN_004b03a0(self);
        FUN_004b0468();
        FUN_004b0438();
        FUN_004b0408();
        return (long)sk_tcb_alloc_dispatch(0);
    }
    FUN_004b0368(self);
    FUN_004b0408();
    return (long)sk_tcb_alloc_dispatch(0);
}

/*--------------------------------------------------------------------*/
/* FUN_000147a0 @ 0x000147a0   (est. sk_tcb_alloc_bind)
 * Ghidra: undefined8 FUN_000147a0(undefined8 a, undefined8 b)
 * Allocates a TCB (FUN_00014478), binds it (FUN_000145bc), and registers
 * with the scheduler (FUN_000153ec).
 * Confidence: medium
 * Notes: helpers FUN_00014478/000145bc/000153ec. */
unsigned long sk_tcb_alloc_bind(void *a, void *b)
{
    unsigned long t = (unsigned long)sk_tcb_alloc_dispatch(0);  /* FUN_00014478 */
    t = (unsigned long)sk_tcb_obj_bind(0, b);  /* FUN_000145bc */
    FUN_000153ec((unsigned long)(a));
    return t;
}

/*--------------------------------------------------------------------*/
/* FUN_000147e0 @ 0x000147e0   (est. sk_obj_is_active)
 * Ghidra: void FUN_000147e0(undefined8 *obj)
 * Tests whether an object is active via its type-check method
 * (FUN_000155ac) on *obj.
 * Confidence: medium
 * Notes: helper FUN_000155ac. */
void sk_obj_is_active(void **obj)
{
    sk_obj_type_check(*obj);  /* FUN_000155ac */
}

/*--------------------------------------------------------------------*/
/* FUN_000147fc @ 0x000147fc   (thunk sk_tcb_obj_destroy)
 * Ghidra: void thunk_FUN_00014578(undefined8 *tcb)
 * Thunk to sk_tcb_obj_destroy (FUN_00014578).
 * Confidence: high (thunk). */
void sk_tcb_obj_destroy_thunk(void *tcb)
{
    sk_tcb_obj_destroy(tcb);
}

/*--------------------------------------------------------------------*/
/* FUN_00014800 @ 0x00014800   (thunk sk_tcb_obj_create)
 * Ghidra: undefined8 * thunk_FUN_00014510(undefined8 obj)
 * Thunk to sk_tcb_obj_create (FUN_00014510).
 * Confidence: high (thunk). */
void *sk_tcb_obj_create_thunk(void *obj)
{
    return sk_tcb_obj_create(obj);
}

/*--------------------------------------------------------------------*/
/* FUN_00014804 @ 0x00014804   (est. sk_tcb_alloc_obj)
 * Ghidra: undefined8 FUN_00014804(undefined8 a)
 * Allocates a TCB and its object wrapper, then registers with the scheduler.
 * Confidence: medium
 * Notes: helpers FUN_00014478/00014510/000153ec. */
unsigned long sk_tcb_alloc_obj(void *a)
{
    unsigned long t;
    FUN_00014478(0);
    t = (unsigned long)sk_tcb_obj_create(0);  /* FUN_00014510 */
    FUN_000153ec((unsigned long)(a));
    return t;
}

/*--------------------------------------------------------------------*/
/* FUN_0001483c @ 0x0001483c   (est. sk_obj_type_query)
 * Ghidra: void FUN_0001483c(undefined8 *obj)
 * Queries an object's type via FUN_00015570 on *obj.
 * Confidence: medium
 * Notes: helper FUN_00015570. */
void sk_obj_type_query(void **obj)
{
    sk_obj_type_check2(*obj);  /* FUN_00015570 */
}

/*--------------------------------------------------------------------*/
/* FUN_00014858 @ 0x00014858   (thunk sk_tcb_obj_destroy)
 * Ghidra: void thunk_FUN_00014578(undefined8 *tcb)
 * Thunk to sk_tcb_obj_destroy (FUN_00014578).
 * Confidence: high (thunk). */
void sk_tcb_obj_destroy_thunk2(void *tcb)
{
    sk_tcb_obj_destroy(tcb);
}

/*--------------------------------------------------------------------*/
/* FUN_0001485c @ 0x0001485c   (est. sk_msg_accept_complex)
 * Ghidra: ulong FUN_0001485c(undefined8 *msg, int *query, long *out, undefined8 flags)
 * The full message-accept path: validates the query disposition/state,
 * marshals the accepted capability buffer (FUN_00017e94/00015548/00017edc),
 * and when the accept flag requires a copy-back, allocates the capability
 * slots (FUN_00015e9c/00014e34) and installs the returned capabilities
 * (FUN_00014f2c/00015630/00015708). Panics via "TB_ASSERT" on bad state.
 * Confidence: low (structural summary; many 004b03xx panic helpers).
 * Notes: strings s_TB_ASSERT__query_>state____TB_ME_005ab676,
 *   s_TB_ASSERT__query_>disposition____005ab6c5; helpers FUN_00015b94/
 *   0001585c/000159b8/00017e94/00015548/00017edc/00015ba4/00015e9c/
 *   00010244/00014e34/0001590c/00014db8/00014f2c/00015630/00015708/
 *   00015bac/00014e34/0011825c; alloc tags 0x102004071d150f8/0x1090040b6685729. */
unsigned long sk_msg_accept_complex(void **msg, int *query, void **out, void *flags)
{
    if (*query == 2) {
        if ((char)query[1] == '\x01') {
            if (FUN_00015b94(query, msg) == 0) return 1;
            FUN_0001585c(query, 3);
            unsigned long obj = *msg;
            long *buf = (long *)FUN_000159b8(query);
            if ((((unsigned long)flags >> 1) & 1) == 0) {
                *(uint16_t *)((char *)buf + 0x2a) |= 0x10;
            }
            unsigned long r;
            if (FUN_00017e94(obj, *(void **)(buf + 0x18)) == 0) {
                r = (unsigned long)FUN_00015548(obj, query, out, flags);
            } else {
                r = (unsigned long)FUN_00017edc(msg, obj, query, out, flags);
            }
            if ((int)r == 0) {
                unsigned int v = (*(uint16_t *)((char *)buf + 0x2a) & 8) == 0 ? 0 : 4;
                r = v;
                if ((((unsigned long)flags >> 1) & 1) != 0 &&
                    (*(uint16_t *)((char *)buf + 0x2a) & 8) == 0) {
                    if (out == 0 || *out == 0) {
                        r = 4;
                    } else {
                        FUN_0001585c(*out, 4);
                        FUN_00015864(*out, 2);
                        long *ob = (long *)FUN_000159b8(*out);
                        if ((*(uint16_t *)((char *)ob + 0x2a) & 1) != 0) {
                            long h = FUN_00015ba4(*out);
                            if (h == 0) {
                                void *lp = 0; unsigned long ln = 0;
                                FUN_0011825c(4, &lp);
                                h = ln;
                                FUN_00015bac(*out,(void *)( ln));
                            }
                            long host = (long)msg[6];
                            if (host == 0) {
                                FUN_004b03f0();
                            } else {
                                void *src = (void *)FUN_00015e9c(host, *out);
                                unsigned int *op = (unsigned int *)sk_heap_calloc(1, 0x58, (void *)0x102004071d150f8);
                                if (op != 0) {
                                    void *meta = sk_heap_calloc(1, 0x68, (void *)0x1090040b6685729);
                                    if (meta == 0) FUN_004b0068();
                                    r = FUN_00014e34(msg, 0, op,(unsigned long)( meta), 0, 0);
                                    if ((int)r == 0) {
                                        if (src == 0) {
                                            for (;;) {
                                                FUN_0001590c(op);
                                                *(uint16_t *)((char *)meta + 0x2a) |= 4;
                                                FUN_0001585c(op, 3);
                                                r = (unsigned long)FUN_00015548(obj, op, &op, 2);
                                                if ((int)r != 0) break;
                                                FUN_00015bac(op,(void *)( h));
                                                src = (void *)FUN_00015e9c(host, op);
                                                if (src != 0) break;
                                                FUN_00014db8(msg, op, 0, 0, 0);
                                            }
                                            FUN_00014f2c();
                                            sk_heap_free(meta);
                                            src = op;
                                        } else {
                                            FUN_00014f2c();
                                            sk_heap_free(meta);
                                            sk_heap_free(op);
                                            void *dst = (void *)FUN_000159b8(*out);
                                            FUN_00015630((void *)(obj), dst);
                                            FUN_00015708();
                                            r = 0;
                                            unsigned long n = ((unsigned long *)src)[3];
                                            *(unsigned long *)dst = *(unsigned long *)src;
                                            ((unsigned long *)dst)[3] = n;
                                            *(uint8_t *)(dst + 5) = 1;
                                            *(uint16_t *)((char *)dst + 0x2a) = *(uint16_t *)((char *)src + 0x2a);
                                        }
                                    } else {
                                        sk_heap_free(meta);
                                        src = op;
                                    }
                                    sk_heap_free(src);
                                    return r;
                                }
                            }
                            FUN_004b0068();
                        }
                        r = 0;
                    }
                }
            }
            return r;
        }
        sk_puts("TB_ASSERT: query->disposition");  /* 0x5ab6c5 */
    } else {
        sk_puts("TB_ASSERT: query->state");  /* 0x5ab676 */
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x14bc4) */
}

/*--------------------------------------------------------------------*/
/* FUN_00014bd0 @ 0x00014bd0   (est. sk_noop)
 * Ghidra: void FUN_00014bd0(void)
 * No-op.
 * Confidence: high (trivial). */
void sk_noop(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_00014bd4 @ 0x00014bd4   (est. sk_msg_install_wrapper)
 * Ghidra: void FUN_00014bd4(undefined8 a, undefined8 b, undefined8 c, undefined8 d, undefined8 e)
 * Wrapper forwarding to FUN_00014e34.
 * Confidence: medium
 * Notes: helper FUN_00014e34. */
void sk_msg_install_wrapper(void *a, void *b, void *c, void *d, void *e)
{
    FUN_00014e34(a, 0, b,(unsigned long)( c),(unsigned long)( d), e);
}

/*--------------------------------------------------------------------*/
/* FUN_00014bec @ 0x00014bec   (est. sk_msg_accept_fail)
 * Ghidra: undefined8 FUN_00014bec(void)
 * Message-accept failure: runs the failure path FUN_00014f2c and returns 0.
 * Confidence: medium
 * Notes: helper FUN_00014f2c. */
unsigned long sk_msg_accept_fail(void)
{
    FUN_00014f2c();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00014c08 @ 0x00014c08   (est. sk_msg_accept_wrapper)
 * Ghidra: void FUN_00014c08(undefined8 a, undefined8 b, undefined8 c, undefined8 d)
 * Wrapper forwarding to FUN_00014db8 with mode 0.
 * Confidence: medium
 * Notes: helper FUN_00014db8. */
void sk_msg_accept_wrapper(void *a, void *b, void *c, void *d)
{
    FUN_00014db8(a, b, 0, c, d);
}

/*--------------------------------------------------------------------*/
/* FUN_00014c18 @ 0x00014c18   (est. sk_capbuf_alloc_sized)
 * Ghidra: undefined8 FUN_00014c18(ulong *cb, ulong size)
 * Allocates a capability buffer of `size` words (tag 0x100004077774924),
 * storing the base through *cb with header fields (flags=1, count=size).
 * Traps on wrap; panics via FUN_004b0498 on allocation failure.
 * Confidence: medium
 * Notes: tag 0x100004077774924; helpers FUN_00010244/00015708/004b0498;
 *   trap 0x14c8c. */
unsigned long sk_capbuf_alloc_sized(unsigned long *cb, unsigned long size)
{
    unsigned long r;
    FUN_00015708();
    r = (unsigned long)sk_heap_calloc(size, 1, (void *)0x100004077774924);  /* FUN_00010244 */
    if (r != 0) {
        *cb = r;
        *(uint8_t *)(cb + 5) = 1;
        cb[2] = 0;
        cb[3] = size;
        cb[4] = 0;
        cb[6] = 0;
        return 0;
    }
    FUN_004b0498();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00014c90 @ 0x00014c90   (est. sk_capbuf_free_or_accept)
 * Ghidra: undefined8 FUN_00014c90(undefined8 *cb, undefined8 b, long host, undefined8 size, undefined8 flags)
 * Releases or accepts a capability buffer: if already consumed (flags bit 0)
 * it frees the payload and clears the header; otherwise it performs a
 * capability accept (FUN_00017e94/000155e8/00015670/00015630) on the host
 * object, or allocates a fresh buffer via sk_capbuf_alloc_sized.
 * Confidence: low (structural summary; 004b04c8 panic).
 * Notes: helpers FUN_00015734/000156b8/000156e0/00017e94/000155e8/
 *   00015670/00015630/00014c18; panic 004b04c8. */
unsigned long sk_capbuf_free_or_accept(void *cb, void *b, long host, void *size, void *flags)
{
    unsigned long *c = (unsigned long *)cb;
    if ((*(uint8_t *)(c + 5) & 1) != 0) {
        sk_heap_free((void *)*c);
        *c = 0;
        c[3] = 0;
        c[6] = 0;
        unsigned long r = FUN_00015734(c);
        *(uint8_t *)((char *)c + 0x29) = 1;
        return r;
    }
    FUN_004b04c8();
    unsigned long host2 = 0;
    if (FUN_000156b8(host2) != 0) FUN_000156e0(host2);
    unsigned long v = FUN_00017e94(host2, size);
    if (*(char *)(host + 0x28) == '\x01') {
        FUN_00014c90((void *)host);
        if ((v & 1) == 0) {
            unsigned long r = FUN_000155e8((void *)(host2), size, flags,(void *)( host));
            if ((int)r == 0) return 0;
            return r;
        }
    } else {
        if (v == 0) {
            FUN_00015734((void *)(host));
            unsigned long r = FUN_00015670((void *)(host2),(void *)( host), flags, size);
            if ((int)r == 0) return 0;
            return r;
        }
        FUN_00015630((void *)(host2),(void *)( host));
    }
    FUN_00014c18((void *)(host), (unsigned long)size);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00014ce0 @ 0x00014ce0   (est. sk_capbuf_free_or_accept2)
 * Ghidra: undefined8 FUN_00014ce0(undefined8 a, undefined8 b, long host, undefined8 size, undefined8 flags)
 * Variant of sk_capbuf_free_or_accept operating on the caller's object.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_000156b8/000156e0/00017e94/00014c90/000155e8/
 *   00015734/00015670/00015630/00014c18. */
unsigned long sk_capbuf_free_or_accept2(void *a, void *b, long host, void *size, void *flags)
{
    if (FUN_000156b8(b) != 0) FUN_000156e0(b);
    unsigned long v = FUN_00017e94((unsigned long)(b), size);
    if (*(char *)(host + 0x28) == '\x01') {
        FUN_00014c90((void *)host);
        if ((v & 1) == 0) {
            unsigned long r = FUN_000155e8(b, size, flags,(void *)( host));
            if ((int)r == 0) return 0;
            return r;
        }
    } else {
        if (v == 0) {
            FUN_00015734((void *)(host));
            unsigned long r = FUN_00015670(b,(void *)( host), flags, size);
            if ((int)r == 0) return 0;
            return r;
        }
        FUN_00015630(b,(void *)( host));
    }
    FUN_00014c18((void *)(host), (unsigned long)size);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00014db8 @ 0x00014db8   (est. sk_msg_accept_init)
 * Ghidra: void FUN_00014db8(undefined8 *msg, undefined8 m, int mode, undefined8 size, undefined8 flags)
 * Initializes a message accept: sets the message state (FUN_0001585c=1) and
 * disposition (mode 1 -> 2), then accepts the capability buffer via
 * FUN_00014ce0.
 * Confidence: medium
 * Notes: helpers FUN_0001585c/00015864/000159b8/00014ce0. */
void sk_msg_accept_init(void **msg, void *m, int mode, void *size, void *flags)
{
    FUN_0001585c(m, 1);
    unsigned int d = (mode == 1) ? 2 : 1;
    FUN_00015864(m, (uint8_t)d);
    long *buf = (long *)FUN_000159b8(m);
    FUN_00014ce0(buf, *msg,(unsigned long)( buf), size, flags);
}

/*--------------------------------------------------------------------*/
/* FUN_00014e34 @ 0x00014e34   (est. sk_msg_install)
 * Ghidra: undefined8 FUN_00014e34(undefined8 *msg, int mode, undefined8 m, long host, ulong size, undefined8 flags)
 * Installs an incoming message: resets m (FUN_00015834), validates the
 * host's accept state, grows the capability buffer if needed
 * (sk_capbuf_alloc_sized), copies the message registers (FUN_000155e8), and
 * links the message (FUN_0001586c/00015b8c). Returns 0 on success.
 * Confidence: medium
 * Notes: helpers FUN_00015834/000156b8/000156e0/00014c18/000155e8/
 *   0001586c/00015b8c/00014f2c; panic 004b04f8. */
unsigned long sk_msg_install(void **msg, int mode, void *m, long host, unsigned long size, void *flags)
{
    unsigned long r;
    FUN_00015834(m);
    unsigned long obj = *msg;
    if (FUN_000156b8(obj) == 0) {
        if (*(char *)(host + 8) != '\0') goto fail;
    } else {
        unsigned long avail = FUN_000156e0((void *)(obj));
        if (*(char *)(host + 8) != '\0') {
fail:
            FUN_004b04f8();
            FUN_00014f2c();
            return 0;
        }
        if (avail < size) {
            FUN_00014c18((void *)(host), size);
        }
    }
    r = FUN_000155e8((void *)(obj),(void *)( size), flags,(void *)( host));
    if ((int)r != 0) return r;
    unsigned int d = (mode != 0) ? 2 : 1;
    r = (unsigned long)FUN_0001586c(m, host, (uint8_t)d);
    if ((int)r == 0) {
        FUN_00015b8c(m, msg);
        r = 0;
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00014f10 @ 0x00014f10   (est. sk_msg_reject)
 * Ghidra: undefined8 FUN_00014f10(void)
 * Message-reject: runs FUN_00014f2c and returns 0.
 * Confidence: medium
 * Notes: helper FUN_00014f2c. */
unsigned long sk_msg_reject(void)
{
    FUN_00014f2c();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00014f2c @ 0x00014f2c   (est. sk_msg_teardown)
 * Ghidra: void FUN_00014f2c(undefined8 *msg, undefined8 b, undefined8 c, undefined8 d)
 * Tears down a message accept: releases the accepted capability buffer
 * (FUN_000159b8/00014c90/00015630) and resets the message state
 * (FUN_00015964); a non-empty state dispatches through sk_msg_accept_init.
 * Confidence: medium
 * Notes: helpers FUN_000159b8/00014c90/00015630/00015964/00014db8;
 *   panic 004b0528. */
void sk_msg_teardown(void **msg, void *b, void *c, void *d)
{
    unsigned long obj = *msg;
    long *buf = (long *)FUN_000159b8(b);
    if (*(char *)((char *)buf + 8) == '\0') {
        if (*(char *)((char *)buf + 0x28) == '\x01') {
            FUN_00014c90(buf);
        } else {
            FUN_00015630(obj);
        }
        FUN_00015964(b);
        return;
    }
    FUN_004b0528();
    FUN_00014db8(0, 0, 1, c, d);
}

/*--------------------------------------------------------------------*/
/* FUN_00014f90 @ 0x00014f90   (est. sk_msg_accept_reply)
 * Ghidra: void FUN_00014f90(undefined8 a, undefined8 b, undefined8 c, undefined8 d)
 * Accepts a reply message via sk_msg_accept_init with mode 1.
 * Confidence: medium
 * Notes: helper FUN_00014db8. */
void sk_msg_accept_reply(void *a, void *b, void *c, void *d)
{
    FUN_00014db8(a, b, 1, c, d);
}

/*--------------------------------------------------------------------*/
/* FUN_00014fa0 @ 0x00014fa0   (est. sk_fatal_retrieve_active)
 * Ghidra: void FUN_00014fa0(void)
 * Fatal "TB_FATAL: Attempt to retrieve active" at libkernel.h:0x5f: prints
 * the string and returns.
 * Confidence: medium (string-matched).
 * Notes: strings s__AppleInternal_Library_BuildRoot_005ab712,
 *   s_TB_FATAL__Attempt_to_retrieve_ac_005aba92. */
void sk_fatal_retrieve_active(void)
{
    sk_puts("TB_FATAL: Attempt to retrieve active");  /* 0x5aba92 */
}

/*--------------------------------------------------------------------*/
/* FUN_00014fbc @ 0x00014fbc   (est. sk_fatal_retrieve_reply)
 * Ghidra: void FUN_00014fbc(void)
 * Fatal "TB_FATAL: Attempt to retrieve reply" at libkernel.h:0x77: prints
 * the string and returns.
 * Confidence: medium (string-matched).
 * Notes: strings s__AppleInternal_Library_BuildRoot_005ab712,
 *   s_TB_FATAL__Attempt_to_retrieve_re_005aba33. */
void sk_fatal_retrieve_reply(void)
{
    sk_puts("TB_FATAL: Attempt to retrieve reply");  /* 0x5aba33 */
}

/*--------------------------------------------------------------------*/
/* FUN_00014fd8 @ 0x00014fd8   (est. sk_registry_entry_create)
 * Ghidra: ulong FUN_00014fd8(undefined8 key, undefined8 val, undefined8 meta)
 * Creates a 0x20-byte registry entry holding a key (offset 8), value
 * (offset 0x10) and bound metadata (FUN_0004b520, offset 0x18). Panics via
 * FUN_004b0068 on allocation failure; traps on wrap.
 * Confidence: medium
 * Notes: tag 0x10a004062d90b2c; helpers FUN_00010244/0004b520/004b0068;
 *   trap 0x15058. */
unsigned long sk_registry_entry_create(void *key, void *val, void *meta)
{
    unsigned long e = (unsigned long)sk_heap_calloc(1, 0x20, (void *)0x10a004062d90b2c);  /* FUN_00010244 */
    if (e == 0) FUN_004b0068();
    *(unsigned long *)(e + 8) = (unsigned long)key;
    *(unsigned long *)(e + 0x10) = (unsigned long)val;
    *(unsigned long *)(e + 0x18) = FUN_0004b520(meta);
    if (e <= e + 0x20) return e;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x15058) */
}

/*--------------------------------------------------------------------*/
/* FUN_0001505c @ 0x0001505c   (est. sk_thread_local_alloc)
 * Ghidra: ulong FUN_0001505c(void)
 * Allocates a 0x20-byte thread-local block (tag 0x1020040fee5c632), clearing
 * it via FUN_001157f0. Panics via FUN_004b0068 on failure; traps on wrap.
 * Confidence: medium
 * Notes: tag 0x1020040fee5c632; helpers FUN_00010244/001157f0/004b0068;
 *   trap 0x150c8. */
unsigned long sk_thread_local_alloc(void)
{
    unsigned long t = (unsigned long)sk_heap_calloc(1, 0x20, (void *)0x1020040fee5c632);  /* FUN_00010244 */
    if (t == 0) FUN_004b0068();
    if (t <= t + 0x10) {
        FUN_001157f0(t, 0);
        if (t <= t + 0x20) return t;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x150c8) */
}

/*--------------------------------------------------------------------*/
/* FUN_000150cc @ 0x000150cc   (est. sk_thread_local_free)
 * Ghidra: void FUN_000150cc(ulong t)
 * Frees a thread-local block: clears it via FUN_001157d4 then sk_heap_free.
 * Traps on wrap.
 * Confidence: medium
 * Notes: helpers FUN_001157d4/thunk_FUN_00012568; trap 0x15108. */
void sk_thread_local_free(unsigned long t)
{
    if (t <= t + 0x10) {
        FUN_001157d4();
        sk_heap_free((void *)t);
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x15108) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015108 @ 0x00015108   (est. sk_registry_insert)
 * Ghidra: undefined8 FUN_00015108(ulong *head, ulong key, undefined8 val, undefined8 meta)
 * Inserts a registry entry keyed by `key` into the singly-linked list headed
 * by *head (key duplicates are rejected, returning 0). Takes the head lock
 * (FUN_0011582c/00115894), returns 1 on new insert.
 * Confidence: medium
 * Notes: helpers FUN_00014fd8/0011582c/00115894/thunk_FUN_00012568;
 *   trap 0x151c8. */
unsigned long sk_registry_insert(unsigned long *head, unsigned long key, void *val, void *meta)
{
    unsigned long *entry = (unsigned long *)sk_registry_entry_create(key, val, meta);  /* FUN_00014fd8 */
    unsigned long *cur, *prev;

    if ((unsigned long)head <= (unsigned long)(head + 2)) {
        FUN_0011582c((unsigned long)(head));
        cur = (unsigned long *)head[2];
        if (cur == 0) {
            head[2] = entry;
        } else {
            do {
                prev = cur;
                if (cur[1] == key) {
                    sk_heap_free(entry);
                    FUN_00115894((unsigned long)(head));
                    return 0;
                }
                cur = (unsigned long *)*cur;
            } while (cur != 0);
            *prev = entry;
        }
        FUN_00115894((unsigned long)(head));
        return 1;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x151c8) */
}

/*--------------------------------------------------------------------*/
/* FUN_000151c8 @ 0x000151c8   (est. sk_registry_remove)
 * Ghidra: void FUN_000151c8(undefined8 *head, long key)
 * Removes the registry entry with `key` from the list *head, invoking the
 * entry's destructor (method at offset 3) and freeing it. Takes the head
 * lock.
 * Confidence: medium
 * Notes: helpers FUN_0011582c/00115894/thunk_FUN_00012568; trap 0x15264. */
void sk_registry_remove(void **head, long key)
{
    void **cur, **prev;

    if ((unsigned long)(head + 2) < (unsigned long)head) __builtin_trap();
    FUN_0011582c((unsigned long)(head));
    cur = (void **)head[2];
    if (cur[1] == (void *)key) {
        head[2] = *cur;
    } else {
        do {
            prev = cur;
            cur = (void **)*prev;
            if (cur == 0) goto done;
        } while (cur[1] != (void *)key);
        *prev = *cur;
    }
    ((void (**)(void *, void *))cur[3])(cur[3], cur[2]);
    sk_heap_free(cur);
done:
    FUN_00115894((unsigned long)(head));
}

/*--------------------------------------------------------------------*/
/* FUN_00015264 @ 0x00015264   (est. sk_registry_lookup)
 * Ghidra: ulong FUN_00015264(ulong head, ulong key)
 * Looks up a registry entry by `key` in the list at `head`, returning its
 * value (entry[2]) or 0. Takes the head lock.
 * Confidence: medium
 * Notes: helpers FUN_0011582c/00115894; trap 0x15310. */
unsigned long sk_registry_lookup(unsigned long head, unsigned long key)
{
    unsigned long *cur;
    unsigned long match = 0, match_next = 0, match_prev = 0;

    if (head + 0x10 < head) __builtin_trap();
    FUN_0011582c(head);
    cur = *(unsigned long **)(head + 0x10);
    if (cur == 0) {
        FUN_00115894(head);
    } else {
        do {
            if (cur[1] != key) {
                /* skip: keep match pointers unchanged */
            } else {
                match = (unsigned long)cur;
                match_next = (unsigned long)(cur + 4);
                match_prev = (unsigned long)cur;
            }
            cur = (unsigned long *)*cur;
        } while (cur != 0);
        FUN_00115894(head);
        if (match != 0) {
            if (match + 4 <= match_next && match_prev <= match) return ((unsigned long *)match)[2];
            __builtin_trap();
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001532c @ 0x0001532c   (est. sk_sched_node_create)
 * Ghidra: void FUN_0001532c(undefined4 a, undefined4 b)
 * Creates a 0x60-byte scheduler node (tag 0x1082040faca7f44) with state
 * fields a/b and a live flag (offset 10 = 1). Panics on failure.
 * Confidence: medium
 * Notes: tag 0x1082040faca7f44; helpers FUN_00010244/004b0068. */
void sk_sched_node_create(unsigned int a, unsigned int b)
{
    unsigned int *n = (unsigned int *)sk_heap_calloc(1, 0x60, (void *)0x1082040faca7f44);  /* FUN_00010244 */
    if (n != 0) {
        *n = a;
        n[1] = b;
        *(uint8_t *)(n + 10) = 1;
        return;
    }
    FUN_004b0068();
}

/*--------------------------------------------------------------------*/
/* FUN_00015388 @ 0x00015388   (est. sk_sched_node_create_data)
 * Ghidra: void FUN_00015388(undefined4 a, undefined8 data, undefined4 b)
 * Creates a scheduler node (tag 0x1082040faca7f44) carrying `data` (offset
 * 8), state a/b, and a live flag.
 * Confidence: medium
 * Notes: tag 0x1082040faca7f44; helper FUN_00010244/004b0068. */
void sk_sched_node_create_data(unsigned int a, void *data, unsigned int b)
{
    unsigned int *n = (unsigned int *)sk_heap_calloc(1, 0x60, (void *)0x1082040faca7f44);  /* FUN_00010244 */
    if (n != 0) {
        *n = a;
        n[1] = b;
        *(void **)(n + 8) = data;
        *(uint8_t *)(n + 10) = 1;
        return;
    }
    FUN_004b0068();
}

/*--------------------------------------------------------------------*/
/* FUN_000153ec @ 0x000153ec   (est. sk_node_invoke)
 * Ghidra: void FUN_000153ec(long node)
 * Invokes a node's bound handler (method at offset 0x10) with its payload
 * (offsets 0x18/0x20), and frees the node if its live flag (offset 0x28) is
 * set.
 * Confidence: medium
 * Notes: helpers thunk_FUN_00012568. */
void sk_node_invoke(long node)
{
    if (*(void (**)(void))(node + 0x10) != 0) {
        (*(void (**)(void *, void *))*(void **)(node + 0x10))(
            *(void **)(node + 0x18), *(void **)(node + 0x20));
    }
    if (*(char *)(node + 0x28) == '\x01') {
        sk_heap_free((void *)node);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00015440 @ 0x00015440   (est. sk_tcb_handle)
 * Ghidra: undefined8 FUN_00015440(long tcb)
 * Returns the TCB's object handle (offset 0x20).
 * Confidence: high (trivial accessor). */
unsigned long sk_tcb_handle(void *tcb)
{
    return *(unsigned long *)((char *)tcb + 0x20);
}

/*--------------------------------------------------------------------*/
/* FUN_00015448 @ 0x00015448   (est. sk_obj_state)
 * Ghidra: undefined4 FUN_00015448(undefined4 *obj)
 * Returns the object state word (*obj).
 * Confidence: high (trivial accessor). */
unsigned int sk_obj_state(void **obj)
{
    return *(unsigned int *)obj;
}

/*--------------------------------------------------------------------*/
/* FUN_00015450 @ 0x00015450   (est. sk_tcb_cfg_flags)
 * Ghidra: undefined4 FUN_00015450(long cfg)
 * Returns the TCB config flags (offset 4).
 * Confidence: high (trivial accessor). */
unsigned int sk_tcb_cfg_flags(void *cfg)
{
    return *(unsigned int *)((char *)cfg + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_00015458 @ 0x00015458   (est. sk_obj_set_data)
 * Ghidra: void FUN_00015458(long obj, undefined8 data)
 * Stores `data` at obj+8.
 * Confidence: high (trivial setter). */
void sk_obj_set_data(void *obj, void *data)
{
    *(void **)((char *)obj + 8) = data;
}

/*--------------------------------------------------------------------*/
/* FUN_00015460 @ 0x00015460   (est. sk_tcb_obj_install_handler)
 * Ghidra: void FUN_00015460(long obj, undefined8 handler, undefined8 arg)
 * Installs a handler method (offset 0x70) and its argument (offset 0x78)
 * on an object.
 * Confidence: high (trivial setter). */
void sk_tcb_obj_install_handler(void *obj, void *handler, void *arg)
{
    *(void **)((char *)obj + 0x70) = handler;
    *(void **)((char *)obj + 0x78) = arg;
}

/*--------------------------------------------------------------------*/
/* FUN_00015468 @ 0x00015468   (est. sk_tcb_send)
 * Ghidra: undefined8 FUN_00015468(long tcb, undefined8 msg, undefined8 *out)
 * Sends a message on a TCB: if a handler is installed (offset 0x70) it
 * dispatches to it with the message and argument; otherwise it uses the
 * fallback transport method (offset 0x68 -> +0x10) or returns error 4.
 * Stores the result through *out and returns 0.
 * Confidence: medium
 * Notes: method dispatch offsets 0x70/0x78/0x68. */
unsigned long sk_tcb_send(void *tcb, void *msg, void **out)
{
    unsigned long r;
    if (*(void (**)(void))((char *)tcb + 0x70) == 0) {
        if (*(long *)((char *)tcb + 0x68) == 0) return 4;
        r = ((unsigned long (*)(void))
             **(void ***)(*(long *)((char *)tcb + 0x68) + 0x10))();
    } else {
        r = ((unsigned long (*)(void *, void *))
             **(void ***)((char *)tcb + 0x70))(msg, *(void **)((char *)tcb + 0x78));
    }
    *out = (void *)r;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000154d0 @ 0x000154d0   (est. sk_obj_destroy_dispatch)
 * Ghidra: void FUN_000154d0(long obj)
 * Dispatches an object's destructor: frees the attached payload if present
 * (offset 0x68), then calls the destructor method at offset 0x40 (falling
 * back to the type table at offset 0x60 -> +0x40).
 * Confidence: medium
 * Notes: method dispatch offsets 0x40/0x60; helper FUN_0004b664. */
void sk_obj_destroy_dispatch(void *obj)
{
    if (*(long *)((char *)obj + 0x68) != 0) FUN_0004b664(0);
    void (**dtor)(void) = *(void (***)(void))((char *)obj + 0x40);
    if (dtor == 0) {
        if (*(long *)((char *)obj + 0x60) == 0) return;
        dtor = *(void (***)(void))(*(long *)((char *)obj + 0x60) + 0x40);
        if (dtor == 0) return;
    }
    ((void (*)(void *))*dtor)(obj);
}

/*--------------------------------------------------------------------*/
/* FUN_0001552c @ 0x0001552c   (est. sk_capbuf_init)
 * Ghidra: void FUN_0001552c(undefined8 *cb, undefined8 obj, undefined8 size)
 * Initializes a capability-buffer header: base=obj, flags=1, count=size,
 * with the remaining header fields zeroed.
 * Confidence: medium
 * Notes: capability buffer layout. */
void sk_capbuf_init(void **cb, void *obj, void *size)
{
    *cb = obj;
    *(uint8_t *)(cb + 1) = 1;
    cb[2] = 0;
    cb[3] = (unsigned long)size;
    cb[4] = 0;
    cb[6] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00015548 @ 0x00015548   (est. sk_obj_dispatch)
 * Ghidra: void FUN_00015548(undefined8 *obj)
 * Dispatches an object's method at offset 0 (or the type-table method at
 * offset 0xc), trapping if neither is installed.
 * Confidence: medium
 * Notes: method dispatch offsets 0/0xc; trap 0x15570. */
void sk_obj_dispatch(void **obj)
{
    if ((void *)*obj != 0) {
        ((void (*)(void))*obj)();
        return;
    }
    if ((void *)obj[0xc] != 0) {
        ((void (*)(void))**obj[0xc])();
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x15570) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015570 @ 0x00015570   (est. sk_obj_type_check2)
 * Ghidra: bool FUN_00015570(long obj)
 * Returns whether an object's type method (offset 8, or type table at
 * offset 0x60 -> +8) reports active; traps if neither is installed.
 * Confidence: medium
 * Notes: method dispatch offsets 8/0x60; trap 0x155ac. */
bool sk_obj_type_check2(void *obj)
{
    int (*method)(void);
    method = *(int (**)(void))((char *)obj + 8);
    if (method == 0) {
        if (*(long *)((char *)obj + 0x60) == 0) __builtin_trap();
        method = *(int (**)(void))(*(long *)((char *)obj + 0x60) + 8);
    }
    return method() != 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000155ac @ 0x000155ac   (est. sk_obj_type_check)
 * Ghidra: bool FUN_000155ac(long obj)
 * Returns whether an object's type method (offset 0x10, or type table at
 * offset 0x60 -> +0x10) reports active; traps if neither is installed.
 * Confidence: medium
 * Notes: method dispatch offsets 0x10/0x60; trap 0x155e8. */
bool sk_obj_type_check(void *obj)
{
    int (*method)(void);
    method = *(int (**)(void))((char *)obj + 0x10);
    if (method == 0) {
        if (*(long *)((char *)obj + 0x60) == 0) __builtin_trap();
        method = *(int (**)(void))(*(long *)((char *)obj + 0x60) + 0x10);
    }
    return method() != 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000155e8 @ 0x000155e8   (est. sk_obj_method18)
 * Ghidra: void FUN_000155e8(long obj, undefined8 a, undefined8 b, undefined8 c)
 * Dispatches the object method at offset 0x18 (or 0x48, or the type table's
 * 0x18/0x48) with (a,b,c); traps if none is installed.
 * Confidence: medium
 * Notes: method dispatch offsets 0x18/0x48/0x60; trap 0x15630. */
void sk_obj_method18(void *obj, void *a, void *b, void *c)
{
    void (*m)(void *, void *, void *);
    void *tbl;
    m = *(void (**)(void *, void *, void *))((char *)obj + 0x18);
    if (m != 0) { m(a, b, c); return; }
    m = *(void (**)(void *, void *, void *))((char *)obj + 0x48);
    if (m != 0) { ((void (*)(void))m)(); return; }
    tbl = *(void **)((char *)obj + 0x60);
    if (tbl != 0) {
        m = *(void (**)(void *, void *, void *))((char *)tbl + 0x18);
        if (m != 0) { m(a, b, c); return; }
        m = *(void (**)(void *, void *, void *))((char *)tbl + 0x48);
        if (m != 0) { ((void (*)(void))m)(); return; }
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_00015630 @ 0x00015630   (est. sk_obj_method20)
 * Ghidra: void FUN_00015630(long obj, undefined8 a)
 * Dispatches the object method at offset 0x20 (or 0x50, or type table's
 * 0x20/0x50) with (a); traps if none is installed.
 * Confidence: medium
 * Notes: method dispatch offsets 0x20/0x50/0x60; trap 0x15670. */
void sk_obj_method20(void *obj, void *a)
{
    void (*m)(void *);
    void *tbl;
    m = *(void (**)(void *))((char *)obj + 0x20);
    if (m != 0) { m(a); return; }
    m = *(void (**)(void *))((char *)obj + 0x50);
    if (m != 0) { ((void (*)(void))m)(); return; }
    tbl = *(void **)((char *)obj + 0x60);
    if (tbl != 0) {
        m = *(void (**)(void *))((char *)tbl + 0x20);
        if (m != 0) { m(a); return; }
        m = *(void (**)(void *))((char *)tbl + 0x50);
        if (m != 0) { ((void (*)(void))m)(); return; }
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_00015670 @ 0x00015670   (est. sk_obj_method28)
 * Ghidra: void FUN_00015670(long obj, undefined8 a, undefined8 b, undefined8 c)
 * Dispatches the object method at offset 0x28 (or 0x58, or type table's
 * 0x28/0x58) with (a,b,c); traps if none is installed.
 * Confidence: medium
 * Notes: method dispatch offsets 0x28/0x58/0x60; trap 0x156b8. */
void sk_obj_method28(void *obj, void *a, void *b, void *c)
{
    void (*m)(void *, void *, void *);
    void *tbl;
    m = *(void (**)(void *, void *, void *))((char *)obj + 0x28);
    if (m != 0) { m(a, b, c); return; }
    m = *(void (**)(void *, void *, void *))((char *)obj + 0x58);
    if (m != 0) { ((void (*)(void))m)(); return; }
    tbl = *(void **)((char *)obj + 0x60);
    if (tbl != 0) {
        m = *(void (**)(void *, void *, void *))((char *)tbl + 0x28);
        if (m != 0) { m(a, b, c); return; }
        m = *(void (**)(void *, void *, void *))((char *)tbl + 0x58);
        if (m != 0) { ((void (*)(void))m)(); return; }
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_000156b8 @ 0x000156b8   (est. sk_obj_method30)
 * Ghidra: undefined8 FUN_000156b8(long obj)
 * Dispatches the object method at offset 0x30 (or type table's 0x30),
 * returning its result; returns 0 if none is installed.
 * Confidence: medium
 * Notes: method dispatch offsets 0x30/0x60. */
unsigned long sk_obj_method30(void *obj)
{
    void (**m)(void) = *(void (***)(void))((char *)obj + 0x30);
    if (m == 0) {
        if (*(long *)((char *)obj + 0x60) == 0) return 0;
        m = *(void (***)(void))(*(long *)((char *)obj + 0x60) + 0x30);
        if (m == 0) return 0;
    }
    return ((unsigned long (*)(void))*m)();
}

/*--------------------------------------------------------------------*/
/* FUN_000156e0 @ 0x000156e0   (est. sk_obj_method38)
 * Ghidra: undefined8 FUN_000156e0(long obj)
 * Dispatches the object method at offset 0x38 (or type table's 0x38),
 * returning its result; returns 0 if none is installed.
 * Confidence: medium
 * Notes: method dispatch offsets 0x38/0x60. */
unsigned long sk_obj_method38(void *obj)
{
    void (**m)(void) = *(void (***)(void))((char *)obj + 0x38);
    if (m == 0) {
        if (*(long *)((char *)obj + 0x60) == 0) return 0;
        m = *(void (***)(void))(*(long *)((char *)obj + 0x60) + 0x38);
        if (m == 0) return 0;
    }
    return ((unsigned long (*)(void))*m)();
}

/*--------------------------------------------------------------------*/
/* FUN_00015708 @ 0x00015708   (est. sk_capbuf_zero)
 * Ghidra: void FUN_00015708(undefined8 *cb)
 * Zeroes a capability-buffer header (all fields).
 * Confidence: high (trivial). */
void sk_capbuf_zero(void *cb)
{
    unsigned long *c = (unsigned long *)cb;
    *(uint8_t *)(c + 1) = 0;
    c[3] = 0; c[4] = 0;
    *(unsigned int *)(c + 5) = 0;
    c[8] = 0; c[7] = 0; c[10] = 0; c[9] = 0;
    c[0xc] = 0; c[0xb] = 0; c[6] = 0;
    *c = 0; c[2] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00015734 @ 0x00015734   (est. sk_capbuf_reset)
 * Ghidra: void FUN_00015734(long cb)
 * Resets a capability-buffer header's state fields (offsets 8/0x10/0x20/
 * 0x2a/0x28) to empty.
 * Confidence: high (trivial). */
void sk_capbuf_reset(void *cb)
{
    *(uint8_t *)((char *)cb + 8) = 0;
    *(void **)((char *)cb + 0x10) = 0;
    *(void **)((char *)cb + 0x20) = 0;
    *(uint16_t *)((char *)cb + 0x2a) = 0;
    *(uint8_t *)((char *)cb + 0x28) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001574c @ 0x0001574c   (est. sk_capbuf_copy)
 * Ghidra: void FUN_0001574c(ulong *dst, undefined8 *src)
 * Copies a capability buffer header + payload from src into dst (which must
 * be large enough), using FUN_00117cc4 for the payload copy. Traps if dst
 * is too small.
 * Confidence: medium
 * Notes: helper FUN_00117cc4; trap 0x157dc. */
void sk_capbuf_copy(unsigned long *dst, void *src)
{
    unsigned long *s = (unsigned long *)src;
    unsigned long n = s[3];
    if (n <= dst[3]) {
        unsigned long base = *dst;
        FUN_00117cc4(base, *s, n);
        if (base <= base + n && (n = s[3], n <= dst[3])) {
            *(uint8_t *)(dst + 1) = *(uint8_t *)(s + 1);
            dst[2] = s[2];
            dst[3] = n;
            dst[4] = s[4];
            *(unsigned int *)(dst + 5) = *(unsigned int *)(s + 5);
            return;
        }
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x157dc) */
}

/*--------------------------------------------------------------------*/
/* FUN_000157dc @ 0x000157dc   (est. sk_capbuf_alloc)
 * Ghidra: void FUN_000157dc(long size)
 * Allocates a capability payload of `size` words (tag 0x100004077774924);
 * panics via FUN_004b0498 on failure. Traps on wrap.
 * Confidence: medium
 * Notes: tag 0x100004077774924; helpers FUN_00010244/004b0498;
 *   trap 0x1582c. */
void *sk_capbuf_alloc(unsigned long size)
{
    unsigned long r = (unsigned long)sk_heap_calloc(size, 1, (void *)0x100004077774924);  /* FUN_00010244 */
    if (r <= r + size) {
        if (r == 0) FUN_004b0498();
        if (size != 0) return (void *)r;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x1582c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015830 @ 0x00015830   (thunk sk_heap_free)
 * Ghidra: void thunk_FUN_00012568(long p)
 * Thunk to sk_heap_free (FUN_00012568).
 * Confidence: high (thunk). */
void sk_heap_free_thunk2(void *p)
{
    sk_heap_free(p);
}

/*--------------------------------------------------------------------*/
/* FUN_00015834 @ 0x00015834   (est. sk_msg_init)
 * Ghidra: void FUN_00015834(undefined4 *msg)
 * Initializes a message object: zeroes the state and sets the pending-
 * register count to all-ones (offset 8 = ~0), clearing the other fields.
 * Confidence: medium
 * Notes: message object layout. */
void sk_msg_init(void *msg)
{
    unsigned long *m = (unsigned long *)msg;
    *(unsigned int *)msg = 0;
    *(uint8_t *)(m + 1) = 0;
    m[2] = 0; m[4] = 0; m[6] = 0;
    m[8] = ~0ull;
    m[0xc] = 0; m[10] = 0; m[0x10] = 0;
    m[0xe] = 0; m[0x12] = 0; m[0x14] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001585c @ 0x0001585c   (est. sk_msg_set_state)
 * Ghidra: void FUN_0001585c(undefined4 *msg, undefined4 state)
 * Sets a message's state word (*msg).
 * Confidence: high (trivial setter). */
void sk_msg_set_state(void *msg, unsigned int state)
{
    *(unsigned int *)msg = state;
}

/*--------------------------------------------------------------------*/
/* FUN_00015864 @ 0x00015864   (est. sk_msg_set_disposition)
 * Ghidra: void FUN_00015864(long msg, undefined1 disposition)
 * Sets a message's disposition byte (offset 4).
 * Confidence: high (trivial setter). */
void sk_msg_set_disposition(void *msg, uint8_t disposition)
{
    *(uint8_t *)((char *)msg + 4) = disposition;
}

/*--------------------------------------------------------------------*/
/* FUN_0001586c @ 0x0001586c   (est. sk_msg_begin)
 * Ghidra: undefined8 FUN_0001586c(int *msg, undefined8 host, undefined1 disposition)
 * Begins a message accept on `msg`: asserts the message is in the empty
 * state ("TB_ASSERT: self->state"), sets it to active (1) with the given
 * disposition, records the host, and initializes the register/label fields.
 * Returns 0.
 * Confidence: medium (string-matched "TB_ASSERT: self->state").
 * Notes: string s_TB_ASSERT__self_>state____TB_MES_005abb59; trap 0x15904. */
unsigned long sk_msg_begin(int *msg, void *host, uint8_t disposition)
{
    if (*msg != 0) {
        sk_puts("TB_ASSERT: self->state");  /* 0x5abb59 */
        __builtin_trap();
    }
    *msg = 1;
    *(uint8_t *)(msg + 1) = disposition;
    msg[2] = 0;
    msg[3] = 0;
    *(unsigned long *)(msg + 0x14) = (unsigned long)host;
    for (int i = 0; i < 4; i++) { msg[10 + i * 2] = 0; msg[11 + i * 2] = 0; }
    msg[0x12] = 0;
    msg[0x13] = 0;
    msg[8] = -1;
    msg[9] = -1;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00015904 @ 0x00015904   (est. sk_msg_set_host)
 * Ghidra: void FUN_00015904(long msg, undefined8 host)
 * Stores `host` at msg+0x50.
 * Confidence: high (trivial setter). */
void sk_msg_set_host(void *msg, void *host)
{
    *(void **)((char *)msg + 0x50) = host;
}

/*--------------------------------------------------------------------*/
/* FUN_0001590c @ 0x0001590c   (est. sk_msg_state_advance)
 * Ghidra: void FUN_0001590c(int *msg)
 * Advances a message state machine based on its state (msg[0]) and
 * disposition (msg[1]): an active message with disposition 1/2 transitions
 * to the error state (2); other invalid transitions trap.
 * Confidence: medium
 * Notes: message state machine; trap 0x15928. */
void sk_msg_state_advance(int *msg)
{
    char d = (char)msg[1];
    if (d == '\x01') {
        if (*msg == 1 || *msg == 4) goto err;
    } else if (d == '\x02') {
        if (*msg - 3U < 2) return;
        if (*msg == 1) goto err;
    } else if (d != '\0') {
err:
        *msg = 2;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x15928) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015964 @ 0x00015964   (est. sk_msg_done)
 * Ghidra: void FUN_00015964(undefined4 *msg)
 * Completes a message accept: resets the state fields and marks the message
 * done (state 5).
 * Confidence: medium
 * Notes: message object layout. */
void sk_msg_done(void *msg)
{
    unsigned long *m = (unsigned long *)msg;
    *(uint8_t *)(m + 1) = 0;
    m[2] = 0;
    m[8] = ~0ull;
    m[0x14] = 0;
    *(unsigned int *)msg = 5;
}

/*--------------------------------------------------------------------*/
/* FUN_00015984 @ 0x00015984   (est. sk_obj_class_set)
 * Ghidra: undefined4 * FUN_00015984(undefined4 *obj, undefined8 class)
 * Sets an object's class/state: for class 1/2 it writes state 4 with the
 * class byte; otherwise it resolves the class table (FUN_004b0558) and
 * returns its state pointer at +0x50.
 * Confidence: medium
 * Notes: helper FUN_004b0558. */
unsigned int *sk_obj_class_set(unsigned int *obj, unsigned long cls)
{
    if (((int)cls - 1U & 0xff) < 2) {
        *obj = 4;
        *(char *)(obj + 1) = (char)cls;
        return obj;
    }
    long t = FUN_004b0558(cls);
    return *(unsigned int **)(t + 0x50);
}

/*--------------------------------------------------------------------*/
/* FUN_000159b8 @ 0x000159b8   (est. sk_cap_buf)
 * Ghidra: undefined8 FUN_000159b8(long obj)
 * Returns the capability-buffer pointer stored at obj+0x50.
 * Confidence: high (trivial accessor). */
unsigned long sk_cap_buf(void *obj)
{
    return *(unsigned long *)((char *)obj + 0x50);
}

/*--------------------------------------------------------------------*/
/* FUN_000159c0 @ 0x000159c0   (est. sk_msg_state_get)
 * Ghidra: undefined4 FUN_000159c0(undefined4 *msg)
 * Returns the message state (*msg).
 * Confidence: high (trivial accessor). */
unsigned int sk_msg_state_get(void *msg)
{
    return *(unsigned int *)msg;
}

/*--------------------------------------------------------------------*/
/* FUN_000159c8 @ 0x000159c8   (est. sk_msg_disposition_get)
 * Ghidra: undefined1 FUN_000159c8(long msg)
 * Returns the message disposition byte (offset 4).
 * Confidence: high (trivial accessor). */
uint8_t sk_msg_disposition_get(void *msg)
{
    return *(uint8_t *)((char *)msg + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_000159d0 @ 0x000159d0   (est. sk_msg_transport_len)
 * Ghidra: undefined8 FUN_000159d0(long msg)
 * Returns the transport length field (offset 0x18 of the capability buffer
 * at msg+0x50).
 * Confidence: high (trivial accessor). */
unsigned long sk_msg_transport_len(void *msg)
{
    return *(unsigned long *)(*(long *)((char *)msg + 0x50) + 0x18);
}

/*--------------------------------------------------------------------*/
/* FUN_000159dc @ 0x000159dc   (est. sk_msg_append_region)
 * Ghidra: void FUN_000159dc(long msg, ulong *out, long *out_len, long cb)
 * Appends a transport region to a message: records the current region end
 * (buffer+0x10) through *out, invokes the callback (method +0x10) to copy
 * data, and records the region length through *out_len. Validates the
 * region is within the transport bounds ("TB_ASSERT: start < msg->transport"
 * / "end < msg->transport").
 * Confidence: low (structural summary).
 * Notes: strings s_TB_ASSERT__start_<__msg_>transpo_005abd19,
 *   s_TB_ASSERT__end_<__msg_>transport_005abd8e; helpers FUN_004b0570/
 *   004b05a0; stack canary. */
void sk_msg_append_region(void *msg, unsigned long *out, long *out_len, long cb)
{
    *out = *(unsigned long *)(*(long *)((char *)msg + 0x50) + 0x10);
    (**(void (**)(long))(cb + 0x10))(cb);
    unsigned long end = *(unsigned long *)(*(long *)((char *)msg + 0x50) + 0x10);
    *out_len = end - *out;
    if (*out <= end) return;
    /* invalid range: fatal */
    unsigned long start = 0, transport = 0;
    if (*out_len < start) {
        sk_puts("TB_ASSERT: start < msg->transport");  /* 0x5abd19 */
    } else if (start + *out_len <= transport) {
        sk_puts("TB_ASSERT: end < msg->transport");  /* 0x5abd8e */
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x15b80) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015a44 @ 0x00015a44   (est. sk_msg_prepend_region)
 * Ghidra: void FUN_00015a44(long msg, ulong start, ulong len, long cb)
 * Prepends a transport region to a message: validates [start, start+len) is
 * within the transport bounds, then invokes the callback (method +0x10) to
 * copy the data. Panics via "TB_ASSERT" on out-of-range regions.
 * Confidence: low (structural summary).
 * Notes: strings s_TB_ASSERT__start_<__msg_>transpo_005abd19,
 *   s_TB_ASSERT__end_<__msg_>transport_005abd8e; helper FUN_004b05a0;
 *   stack canary. */
void sk_msg_prepend_region(void *msg, unsigned long start, unsigned long len, long cb)
{
    unsigned long transport = (*(unsigned long **)((char *)msg + 0x50))[3];
    if (transport < start) {
        sk_puts("TB_ASSERT: start < msg->transport");  /* 0x5abd19 */
    } else if (start + len <= transport) {
        unsigned long base = **(unsigned long **)((char *)msg + 0x50);
        unsigned long region[4];
        region[0] = base + start;
        region[1] = 0;
        region[2] = 0;
        region[3] = len;
        (**(void (**)(long, void *))(cb + 0x10))(cb, &region[0]);
        return;
    } else {
        FUN_004b05a0();
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x15b80) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015b84 @ 0x00015b84   (est. sk_msg_set_arg)
 * Ghidra: void FUN_00015b84(long msg, undefined8 v)
 * Stores v at msg+0x10.
 * Confidence: high (trivial setter). */
void sk_msg_set_arg(void *msg, void *v)
{
    *(void **)((char *)msg + 0x10) = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00015b8c @ 0x00015b8c   (est. sk_msg_set_host_field)
 * Ghidra: void FUN_00015b8c(long msg, undefined8 v)
 * Stores v at msg+8.
 * Confidence: high (trivial setter). */
void sk_msg_set_host_field(void *msg, void *v)
{
    *(void **)((char *)msg + 8) = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00015b94 @ 0x00015b94   (est. sk_msg_host_is)
 * Ghidra: bool FUN_00015b94(long msg, long host)
 * Returns whether msg's host field (offset 8) equals `host`.
 * Confidence: high (trivial accessor). */
bool sk_msg_host_is(void *msg, void *host)
{
    return *(void **)((char *)msg + 8) == host;
}

/*--------------------------------------------------------------------*/
/* FUN_00015ba4 @ 0x00015ba4   (est. sk_msg_payload_len)
 * Ghidra: undefined8 FUN_00015ba4(long msg)
 * Returns the message payload length (offset 0x18).
 * Confidence: high (trivial accessor). */
unsigned long sk_msg_payload_len(void *msg)
{
    return *(unsigned long *)((char *)msg + 0x18);
}

/*--------------------------------------------------------------------*/
/* FUN_00015bac @ 0x00015bac   (est. sk_msg_set_payload_len)
 * Ghidra: void FUN_00015bac(long msg, undefined8 v)
 * Stores v at msg+0x18.
 * Confidence: high (trivial setter). */
void sk_msg_set_payload_len(void *msg, void *v)
{
    *(void **)((char *)msg + 0x18) = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00015bb4 @ 0x00015bb4   (est. sk_msg_num_caps)
 * Ghidra: undefined8 FUN_00015bb4(long msg)
 * Returns the message's capability count (offset 0x48).
 * Confidence: high (trivial accessor). */
unsigned long sk_msg_num_caps(void *msg)
{
    return *(unsigned long *)((char *)msg + 0x48);
}

/*--------------------------------------------------------------------*/
/* FUN_00015bbc @ 0x00015bbc   (est. sk_msg_cap_get)
 * Ghidra: undefined8 FUN_00015bbc(long msg, long i)
 * Returns the i-th capability word from the message's cap array (offset
 * 0x28 + i*8); traps if the index is out of range.
 * Confidence: medium
 * Notes: trap 0x15be8. */
unsigned long sk_msg_cap_get(void *msg, long i)
{
    unsigned long *arr = (unsigned long *)((char *)msg + 0x28);
    unsigned long *p = arr + i;
    if ((unsigned long)arr <= (unsigned long)p && (unsigned long)(p + 1) <= (unsigned long)(arr + 4) &&
        (unsigned long)p <= (unsigned long)(p + 1)) {
        return *p;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x15be8) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015be8 @ 0x00015be8   (est. sk_msg_cap_append)
 * Ghidra: undefined8 FUN_00015be8(long msg, ulong cap)
 * Appends a capability word to a message's cap array (offset 0x28), growing
 * the count (offset 0x48). Returns 6 if the array is full (>= 4), else 0.
 * Traps on overflow.
 * Confidence: medium
 * Notes: cap array layout; trap 0x15c30. */
unsigned long sk_msg_cap_append(void *msg, unsigned long cap)
{
    unsigned long *count = (unsigned long *)((char *)msg + 0x48);
    unsigned long n = *count;
    unsigned long *p;

    if (3 < n) return 6;
    p = (unsigned long *)((char *)msg + 0x28) + n;
    if ((unsigned long)(p + 1) <= (unsigned long)count && (unsigned long)p <= (unsigned long)(p + 1)) {
        *p = cap;
        *count = n + 1;
        return 0;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x15c30) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015c30 @ 0x00015c30   (est. sk_msg_cap_pop)
 * Ghidra: undefined8 FUN_00015c30(long msg, long *out)
 * Pops the first capability word from a message's cap array (offset 0x28),
 * shifting the remaining entries down. Returns 7 if empty, else 0 with the
 * popped word through *out. Traps on overflow.
 * Confidence: medium
 * Notes: cap array layout; trap 0x15cbc. */
unsigned long sk_msg_cap_pop(void *msg, long *out)
{
    long *arr = (long *)((char *)msg + 0x28);
    long *count = (long *)((char *)msg + 0x48);
    long n = *count;

    if (n == 0) return 7;
    *out = *arr;
    for (long i = n - 1; i != 0; i--) {
        if ((unsigned long)(arr + 1) <= (unsigned long)(arr + 2) &&
            (unsigned long)(arr + 1) <= (unsigned long)(arr + 1)) {
            *arr = arr[1];
            arr += 1;
        } else {
            __builtin_trap();
        }
    }
    arr[n - 1] = 0;
    *count = n - 1;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00015cbc @ 0x00015cbc   (est. sk_msg_flag_test)
 * Ghidra: bool FUN_00015cbc(long msg, ushort mask)
 * Returns whether the message's capability-buffer flag word (buffer+0x2a)
 * has any of `mask` bits set.
 * Confidence: medium
 * Notes: flag word at buffer+0x2a. */
bool sk_msg_flag_test(void *msg, uint16_t mask)
{
    return (*(uint16_t *)(*(long *)((char *)msg + 0x50) + 0x2a) & mask) != 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00015cd0 @ 0x00015cd0   (est. sk_msg_set_transport_end)
 * Ghidra: void FUN_00015cd0(long msg, undefined8 v)
 * Stores v at the capability buffer's transport-end field (buffer+0x10).
 * Confidence: high (trivial setter). */
void sk_msg_set_transport_end(void *msg, void *v)
{
    *(void **)(*(long *)((char *)msg + 0x50) + 0x10) = v;
}

/*--------------------------------------------------------------------*/
/* FUN_00015cdc @ 0x00015cdc   (est. sk_msg_none)
 * Ghidra: undefined8 FUN_00015cdc(void)
 * Returns 0 (empty/no message).
 * Confidence: high (trivial). */
unsigned long sk_msg_none(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00015ce4 @ 0x00015ce4   (est. sk_msg_copy_region)
 * Ghidra: void FUN_00015ce4(long src, long dst, ulong len)
 * Copies `len` bytes from the source message's transport region into the
 * destination's, advancing both transport cursors (buffer+2 and dst+2).
 * Validates the regions are within bounds ("TB_ASSERT: src_end < src_tpt"
 * / "dst_end < dst_tpt"); traps on out-of-range or overflow.
 * Confidence: low (structural summary).
 * Notes: strings s_TB_ASSERT__dst_end_<__dst_tpt_bu_005abe0a,
 *   s_TB_ASSERT__src_end_<__src_tpt_bu_005abdcf; helpers FUN_004b05e8/
 *   004b05c4/00117cc4; trap 0x15d78/0x15e08. */
void sk_msg_copy_region(void *src, void *dst, unsigned long len)
{
    unsigned long *sb = *(unsigned long **)((char *)src + 0x50);
    unsigned long *db = *(unsigned long **)((char *)dst + 0x50);
    unsigned long sstart = sb[2], dstart = db[2];
    unsigned long send = sb[3], dend = db[3];
    unsigned long sp = *sb, dp = *db;

    if (sstart + len < sstart) { FUN_004b05e8(); sk_puts("TB_ASSERT: src_end < src_tpt"); __builtin_trap(); }
    if (sstart + len > send) { sk_puts("TB_ASSERT: src_end < src_tpt"); __builtin_trap(); }
    if (dstart + len < dstart) { FUN_004b05c4(); sk_puts("TB_ASSERT: dst_end < dst_tpt"); __builtin_trap(); }
    if (dstart + len > dend) { sk_puts("TB_ASSERT: dst_end < dst_tpt"); __builtin_trap(); }
    if (len <= send - sstart && len <= dend - dstart &&
        FUN_00117cc4(dp + dstart, sp + sstart, len) == 0) {
        sb[2] += len;
        db[2] += len;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x15d78) */
}

/*--------------------------------------------------------------------*/
/* FUN_00015e08 @ 0x00015e08   (est. sk_fatal_disposition)
 * Ghidra: void FUN_00015e08(ulong disposition)
 * Fatal "TB_ASSERT: disposition" at tb_message.c:0x9a: prints the string and
 * returns.
 * Confidence: medium (string-matched).
 * Notes: strings s_tb_message_c_005abb9f,
 *   s_TB_ASSERT___disposition____TB_ME_005abbac. */
void sk_fatal_disposition(unsigned long disposition)
{
    sk_puts("TB_ASSERT: disposition");  /* 0x5abbac */
}

/*--------------------------------------------------------------------*/
/* FUN_00015e2c @ 0x00015e2c   (est. sk_fatal_transport_overflow)
 * Ghidra: void FUN_00015e2c(undefined8 v)
 * Fatal "TB_FATAL: overflow detected when" (transport) : prints the string.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__overflow_detected_when_005abd5d. */
void sk_fatal_transport_overflow(void *v)
{
    sk_puts("TB_FATAL: overflow detected when");  /* 0x5abd5d */
}

/*--------------------------------------------------------------------*/
/* FUN_00015e3c @ 0x00015e3c   (est. sk_registry_bind)
 * Ghidra: void FUN_00015e3c(undefined8 head, undefined8 *entry)
 * Binds a registry entry: inserts it (FUN_00015108, tag 0x659088); on a
 * duplicate insert it frees the entry's payload and the entry.
 * Confidence: medium
 * Notes: tag 0x659088; helpers FUN_00015108/004b060c/thunk_FUN_00012568. */
void sk_registry_bind(void *head, void **entry)
{
    if ((FUN_00015108(head, *entry, entry, 0x659088) & 1) != 0) return;
    FUN_004b060c();
    sk_heap_free(*(void **)((char *)0 + 0x18));
    sk_heap_free(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00015e9c @ 0x00015e9c   (est. sk_capbuf_accumulate)
 * Ghidra: ulong * FUN_00015e9c(undefined8 head, long msg)
 * Accumulates a message's capability payload into the registry entry keyed
 * by the message (FUN_00015264), growing the entry's buffer as needed
 * (FUN_00010244/000102f4) and copying the payload (FUN_00117cc4). If the
 * message requests a copy-back (flag bit 1), it allocates a fresh capability
 * buffer (FUN_00014c18) and removes the entry (FUN_000151c8), returning it.
 * Panics via "TB_ASSERT: accumulator > total size" on overflow.
 * Confidence: low (structural summary).
 * Notes: strings s_TB_ASSERT__accumulator_>total_si_005abf4e; helpers
 *   FUN_000159b8/00015264/00010244/00015e3c/000102f4/00014c18/000151c8;
 *   tags 0x1010040313bcfeb/0x100004077774924/0x1090040b6685729. */
unsigned long *sk_capbuf_accumulate(void *head, void *msg)
{
    unsigned long *mbuf = (unsigned long *)FUN_000159b8(msg);
    unsigned long *entry = (unsigned long *)FUN_00015264(head, *(void **)((char *)msg + 0x18));
    unsigned long *eb = entry + 4;

    if (entry == 0) {
        entry = (unsigned long *)sk_heap_calloc(1, 0x20, (void *)0x1010040313bcfeb);  /* FUN_00010244 */
        if (entry == 0) { FUN_004b066c(); FUN_004b0714(); return 0; }
        *entry = *(unsigned long *)((char *)msg + 0x18);
        unsigned long total = mbuf[3] * 2;
        unsigned long buf = (unsigned long)sk_heap_calloc(total, 1, (void *)0x100004077774924);
        if (buf != 0) {
            entry[2] = total;
            entry[3] = buf;
            sk_registry_bind(head, entry);  /* FUN_00015e3c */
        } else {
            FUN_004b06c0();
            FUN_004b066c();
            FUN_004b0714();
            return 0;
        }
    }
    unsigned long acc = entry[1];
    unsigned long need = acc + *(unsigned long *)(FUN_000159b8(msg) + 0x18);
    if (need < acc) { FUN_004b06e4(); FUN_004b0690(); }
    if (entry[2] < need) {
        unsigned long nb = FUN_000102f4(entry[3], need,(void *)( 0xa8ccd261));
        if (nb == 0) { FUN_004b06c0(); FUN_004b066c(); FUN_004b0714(); return 0; }
        entry[2] = need;
        entry[3] = nb;
    }
    if (acc + mbuf[3] > entry[2]) {
        sk_puts("TB_ASSERT: accumulator > total size");  /* 0x5abf4e */
        __builtin_trap();
    }
    if (FUN_00117cc4(entry[3] + acc, *mbuf, mbuf[3]) == 0) {
        entry[1] += mbuf[3];
        if (((*(uint8_t *)((char *)mbuf + 0x2a) >> 1) & 1) == 0) return 0;
        unsigned long *cb = (unsigned long *)sk_heap_calloc(1, 0x68, (void *)0x1090040b6685729);
        if (cb != 0 && FUN_00014c18(cb, entry[1]) == 0) {
            FUN_000151c8(head, *entry);
            return cb;
        }
    }
    FUN_004b066c();
    FUN_004b063c();
    sk_puts((const char *)0x5aacf2);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001611c @ 0x0001611c   (est. sk_assert_internal2)
 * Ghidra: void FUN_0001611c(undefined8 v)
 * Assertion helper printing the generic failure string (DAT_005aacf2).
 * Confidence: medium
 * Notes: DAT_005aacf2. */
void sk_assert_internal2(void *v)
{
    sk_puts((const char *)0x5aacf2);
}

/*--------------------------------------------------------------------*/
/* FUN_0001612c @ 0x0001612c   (est. sk_entry_val)
 * Ghidra: undefined8 FUN_0001612c(long entry)
 * Returns the registry entry value (offset 0x10).
 * Confidence: high (trivial accessor). */
unsigned long sk_entry_val(void *entry)
{
    return *(unsigned long *)((char *)entry + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_00016134 @ 0x00016134   (est. sk_region_alloc_lazy)
 * Ghidra: undefined8 FUN_00016134(undefined8 *slot)
 * Lazily allocates a memory region: if already present (slot[3] bit 0)
 * returns *slot; otherwise allocates a 0x20-byte region descriptor (tag
 * 0x108004047936fdf) and maps it (FUN_00016208). Returns the base or error.
 * Confidence: medium
 * Notes: tag 0x108004047936fdf; helpers FUN_004b07c0/004b07f0/00010244/
 *   00016208/004b0744/004b0068; trap 0x16204. */
unsigned long sk_region_alloc_lazy(void **slot)
{
    unsigned long *s = (unsigned long *)slot;
    if ((*(uint8_t *)(s + 3) & 1) != 0) return *s;
    unsigned long cls = FUN_004b07c0();
    if ((*(uint8_t *)((char *)cls + 0x18) & 1) != 0) return *(unsigned long *)((char *)cls + 8);
    unsigned long r = (unsigned long)sk_heap_calloc(1, 0x20, (void *)0x108004047936fdf);  /* FUN_00010244 */
    if (r == 0) FUN_004b0068();
    *(long *)(r + 0x10) = FUN_004b07f0();
    *(uint8_t *)(r + 0x18) = 0;
    if (r <= r + 0x20) {
        *slot = (void *)r;
        unsigned long st = FUN_00016208((void *)(r), 0);
        if ((int)st != 0) FUN_004b0744(r);
        return st;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x16204) */
}

/*--------------------------------------------------------------------*/
/* FUN_00016154 @ 0x00016154   (est. sk_region_alloc_lazy2)
 * Ghidra: undefined8 FUN_00016154(long slot)
 * Lazy region allocation variant: returns the cached base if present
 * (offset 0x18 bit 0), else allocates+maps a fresh region.
 * Confidence: medium
 * Notes: tag 0x108004047936fdf; helpers FUN_004b07f0/00010244/00016208/
 *   004b0744/004b0068; trap 0x16204. */
unsigned long sk_region_alloc_lazy2(void *slot)
{
    unsigned long r;
    if ((*(uint8_t *)((char *)slot + 0x18) & 1) != 0) return *(unsigned long *)((char *)slot + 8);
    r = (unsigned long)sk_heap_calloc(1, 0x20, (void *)0x108004047936fdf);  /* FUN_00010244 */
    if (r != 0) {
        *(long *)(r + 0x10) = FUN_004b07f0();
        *(uint8_t *)(r + 0x18) = 0;
        if (r <= r + 0x20) {
            *(void **)0 = (void *)r;
            unsigned long st = FUN_00016208((void *)(r), 0);
            if ((int)st != 0) FUN_004b0744(r);
            return st;
        }
        __builtin_trap();
    }
    FUN_004b0068();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00016174 @ 0x00016174   (est. sk_region_map)
 * Ghidra: undefined8 FUN_00016174(ulong *out, undefined8 key)
 * Maps a memory region: allocates a 0x20-byte descriptor (tag
 * 0x108004047936fdf), records the key, and maps it via FUN_00016208,
 * storing the descriptor through *out. Returns the mapping status.
 * Confidence: medium
 * Notes: tag 0x108004047936fdf; helpers FUN_00010244/00016208/004b0744/
 *   004b0068; trap 0x16204. */
unsigned long sk_region_map(unsigned long *out, void *key)
{
    unsigned long r = (unsigned long)sk_heap_calloc(1, 0x20, (void *)0x108004047936fdf);  /* FUN_00010244 */
    if (r == 0) FUN_004b0068();
    *(void **)(r + 0x10) = key;
    *(uint8_t *)(r + 0x18) = 0;
    if (r <= r + 0x20) {
        *out = r;
        unsigned long st = FUN_00016208((void *)(r), 0);
        if ((int)st != 0) FUN_004b0744(r);
        return st;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x16204) */
}

/*--------------------------------------------------------------------*/
/* FUN_00016208 @ 0x00016208   (est. sk_region_map_impl)
 * Ghidra: undefined8 FUN_00016208(ulong *desc, ulong *out_base)
 * Maps a memory region backing a descriptor: issues a page-table map
 * (method +0x30 of the region's client, size 0x1808), copies the returned
 * physical mapping through the client's getters (methods +8 and +0x28), and
 * records base=result, len=0x4000 in the descriptor, marking it mapped
 * (offset 3 bit 0). Returns 0 on success, 0xd on failure.
 * Confidence: medium
 * Notes: helper FUN_00034a2c; globals DAT_004bb190/uRam00000000004bb198;
 *   FUN_00054354; trap 0x16318. */
unsigned long sk_region_map_impl(unsigned long *desc, unsigned long *out_base)
{
    if ((desc[3] & 1) == 0) {
        unsigned long client = FUN_00034a2c();
        if (FUN_client_method30(client, 0x1808, &desc[0], &desc[4], 0, 0) == '\0') {
            if (desc[4] == 0) FUN_00054354();
            unsigned long phys;
            FUN_client_method8(desc[4], &phys);
            unsigned long base = phys;
            if (FUN_client_method28(desc[4], 0, desc[2]) == '\0') {
                *(uint8_t *)(desc + 3) = 1;
                desc[0] = base;
                desc[1] = 0x4000;
                if (out_base == 0) return 0;
                *out_base = base;
                return 0;
            }
        }
    }
    return 0xd;
}

/*--------------------------------------------------------------------*/
/* FUN_00016318 @ 0x00016318   (est. sk_region_map_small)
 * Ghidra: undefined8 FUN_00016318(ulong *desc)
 * Maps a small (0x28) memory region and allocates a capability slot
 * (FUN_00034f70) bound via a page-table client (method +0x40), wrapping the
 * result in a fresh descriptor (tag 0x108004047936fdf). Returns 0 on
 * success, 0xd on failure.
 * Confidence: medium
 * Notes: tag 0x108004047936fdf; helpers FUN_00034a2c/00034f70/00010244/
 *   00054354/004b0068; globals DAT_004bb190/uRam00000000004bb198;
 *   trap 0x16450. */
unsigned long sk_region_map_small(unsigned long *desc)
{
    unsigned long client = FUN_00034a2c();
    if (FUN_client_method30(client, 0x28, &desc[0], &desc[4], 0, 0) == '\0') {
        if (desc[4] == 0) FUN_00054354();
        unsigned long phys;
        FUN_client_method8(desc[4], &phys);
        unsigned long slot = FUN_00034f70();
        unsigned long client2 = FUN_00034a2c();
        if (FUN_client_method40(client2, slot, 1, phys) == '\0') {
            unsigned long *d = (unsigned long *)sk_heap_calloc(1, 0x20, (void *)0x108004047936fdf);
            if (d == 0) FUN_004b0068();
            d[0] = phys;
            d[1] = 0x4000;
            d[2] = slot;
            *(uint8_t *)(d + 3) = 1;
            if ((unsigned long)d <= (unsigned long)(d + 4)) {
                *desc = (unsigned long)d;
                return 0;
            }
            __builtin_trap();
        }
        FUN_client_destroy(desc[4]);
    }
    return 0xd;
}

/*--------------------------------------------------------------------*/
/* FUN_00016458 @ 0x00016458   (est. sk_tcb_alloc_ext)
 * Ghidra: long FUN_00016458(undefined8 cfg)
 * Extended TCB allocation: allocates the 0x118-byte TCB (tag
 * 0x10e0040f252f50e) and a 0x70-byte capability region (tag
 * 0x10a0040464bf099), links them (tcb+0x80 = region, tcb+0x60 = dispatch
 * table 0x6590a8), records the object handle (FUN_00015440) and config flags
 * (FUN_00015450) into the region, and stores the thread-local base
 * (FUN_0001505c) at region+0xd. Panics on failure.
 * Confidence: medium
 * Notes: tags 0x10e0040f252f50e/0x10a0040464bf099; helpers FUN_00010244/
 *   00015440/00015450/0001505c/004b0068; dispatch table 0x6590a8. */
long sk_tcb_alloc_ext(void *cfg)
{
    unsigned long tcb = (unsigned long)sk_heap_calloc(1, 0x118, (void *)0x10e0040f252f50e);  /* FUN_00010244 */
    unsigned long *region;
    if (tcb == 0) FUN_004b0068();
    region = (unsigned long *)sk_heap_calloc(1, 0x70, (void *)0x10a0040464bf099);
    if (region != 0) {
        *(unsigned long **)(tcb + 0x80) = region;
        *(unsigned long *)(tcb + 0x60) = 0x6590a8;
        *region = sk_tcb_handle(cfg);  /* FUN_00015440 */
        if ((sk_tcb_cfg_flags(cfg) >> 2 & 1) != 0) {
            *(uint8_t *)(region + 0xc) = 1;
        }
        region[0xd] = FUN_0001505c();
        return tcb;
    }
    FUN_004b0068();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001650c @ 0x0001650c   (est. sk_msg_reply_recv)
 * Ghidra: undefined8 FUN_0001650c(long tcb, int *query, undefined8 *msg, ulong *flags)
 * The cL4 reply/receive path: dispatches on the query state (must be 3),
 * marshals the reply message registers and capabilities into the transport
 * (FUN_000132d4/000132e0/0005ee58/000639a0), copies the message into the
 * query (FUN_00016c24), and installs returned capabilities
 * (FUN_00016174/00015cd0). Large state machine with many "TB_ASSERT" /
 * "TB_FATAL" panics on malformed replies.
 * Confidence: low (large, structural summary; the cL4 reply/receive flow is
 *   preserved).
 * Notes: helpers FUN_000159b8/000132d4/000132e0/00034f70/0005edac/0005ee58/
 *   000639a0/00016c24/0005ee40/00016174/00016154/00016134/00015cd0/
 *   00117cc4/00034f70/004b23d8; globals DAT_00657fa0; many 004b0xxx panics;
 *   string s_TB_ASSERT__accumulator_>total_si_005abf4e. */
unsigned long sk_msg_reply_recv(void *tcb, int *query, void **msg, unsigned long *flags)
{
    /* Structural reconstruction: reply/receive message dispatch. */
    if (*query != 3) {
        FUN_004b0a34();
        return 0xd;
    }
    unsigned long client = **(unsigned long **)((char *)tcb + 0x80);
    long *qb = (long *)FUN_000159b8(query);
    if (*(unsigned long *)(qb + 0x18) < 0x191) {
        unsigned long slot = 0;
        unsigned long sz = FUN_000132d4(qb[3]);
        unsigned long csz = FUN_000132e0((void *)(*qb),(void *)( qb[3]));
        if (sz == csz) {
            FUN_0005edac(0, slot);
            unsigned long st = FUN_0005ee58(sz, 0, *(uint16_t *)((char *)qb + 0x2a), 0);
            if (FUN_000639a0(client, &st) == 0) {
                FUN_00016c24((void *)(st), query);
                if (FUN_0005ee40() != 0) {
                    FUN_00016174(&st,(void *)( slot));
                }
            }
        }
        return 0;
    }
    /* large reply path: per-capability marshalling (abridged) */
    return sk_msg_reply_recv_large(tcb, query, msg, flags);
}

/*--------------------------------------------------------------------*/
/* FUN_00016a5c @ 0x00016a5c   (est. sk_msg_recv_large)
 * Ghidra: void FUN_00016a5c(...)  (large receive path)
 * Large receive message handler: reads the incoming message registers and
 * capabilities from the transport, allocates TCB slots for each returned
 * capability (FUN_00034f70 + CallSupervisor), and installs them. Uses
 * "TB_ASSERT"/"TB_FATAL" panics on malformed messages and stack canary.
 * Confidence: low (large, structural summary).
 * Notes: helpers FUN_0005ee40/00034f70/0005edac/0005ee58/000639a0/
 *   00016174/00016154/00016134/00015cd0/00117cc4/000132d4/000132e0/
 *   004b23d8/0005ee48; globals DAT_00657fa0; many 004b0xxx panics. */
void sk_msg_recv_large(void *a, void *b, void *c, void *d)
{
    /* Structural reconstruction of the large receive path (abridged).
     * Reads per-capability words from the transport and installs each into
     * a freshly allocated TCB capability slot via CallSupervisor(1). */
    unsigned long n = FUN_0005ee40();
    for (unsigned long i = 0; i < n; i++) {
        unsigned long slot = FUN_00034f70();
        if (slot == 0) { FUN_004b0a40(); return; }
        CallSupervisor(1);
        FUN_004b23d8((void *)(slot));
    }
    FUN_0011d7e8(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00016d78 @ 0x00016d78   (est. sk_msg_send_complex)
 * Ghidra: void FUN_00016d78(...)  (large send path)
 * The large cL4 message-send path: walks the message registers and
 * capabilities, marshalling them into the transport buffer, validating each
 * capability's copy size ("TB_FATAL: Copyin size did not match"), and
 * issuing CallSupervisor for the data. Uses "TB_ASSERT"/"TB_FATAL" panics.
 * Confidence: low (large, structural summary).
 * Notes: helpers FUN_0005ee58/0005ee48/000132d4/000132e0/000639a0/
 *   00034f70/0005edac/00016174/00016154/00016134/00015cd0/00117cc4/
 *   004b23d8; string s_TB_FATAL__Copyin_size_did_not_ma_005ac03b; many
 *   004b0xxx panics. */
void sk_msg_send_complex(void *a, void *b, void *c, void *d)
{
    /* Structural reconstruction of the large send path (abridged):
     * marshals the message payload into the transport and copies each
     * capability's data in via CallSupervisor(1). */
    unsigned long n = FUN_0005ee40();
    for (unsigned long i = 0; i < n; i++) {
        unsigned long cap = FUN_0005ee48((void *)(i));
        unsigned long len = FUN_000132e0((void *)(cap), 0);
        if (len > 0x191) {
            sk_puts("TB_FATAL: Copyin size did not match");  /* 0x5ac03b */
            return;
        }
        CallSupervisor(1);
    }
    FUN_0011d7e8(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00016e1c @ 0x00016e1c   (est. sk_msg_send_complex2)
 * Ghidra: void FUN_00016e1c(...)  (large send variant)
 * Variant of the large message-send path with per-region data copying
 * (FUN_00117cc4) and transport-cursor advancement.
 * Confidence: low (large, structural summary).
 * Notes: helpers FUN_0005ee58/0005ee48/000132d4/000132e0/000639a0/
 *   00034f70/00117cc4/004b23d8/00016174; many 004b0xxx panics. */
void sk_msg_send_complex2(void *a, void *b, void *c, void *d)
{
    unsigned long n = FUN_0005ee40();
    for (unsigned long i = 0; i < n; i++) {
        unsigned long cap = FUN_0005ee48((void *)(i));
        unsigned long base = FUN_000132e0((void *)(cap), 0);
        unsigned long len = FUN_000132d4(0x10);
        FUN_00117cc4(base, base, len);
        CallSupervisor(1);
    }
    FUN_0011d7e8(0);
}

/*--------------------------------------------------------------------*/
/* FUN_000176a4 @ 0x000176a4   (est. sk_msg_reply_send)
 * Ghidra: void FUN_000176a4(long tcb, undefined8 query, undefined8 msg, undefined8 *out)
 * The cL4 reply-send path: copies the reply message's capability payload
 * into the transport (FUN_00015264/00015ba4/00017cc4), handles both the
 * small (< 0x191) and large paths, and for the large path registers a new
 * capability entry (FUN_00016318/00015108) or accumulates into an existing
 * one. Returns the transfer status through *out.
 * Confidence: low (large, structural summary).
 * Notes: helpers FUN_000159b8/00015ba4/00015264/000151c8/000132d4/
 *   000132e0/00016318/00015108/0001612c/00034f70/00016154/00016134/
 *   00117cc4/0005ee58/00015cd0; globals DAT_00657fa0/DAT_004bb190; strings
 *   s_TB_FATAL__Copyin_size_did_not_ma_005ac03b; many 004b0xxx panics. */
void sk_msg_reply_send(void *tcb, void *query, void *msg, void **out)
{
    unsigned long *qb = (unsigned long *)FUN_000159b8(query);
    unsigned long n = qb[3];
    unsigned long key = FUN_00015ba4(msg);
    unsigned long *entry = (unsigned long *)FUN_00015264(*(void **)(*(long *)((char *)tcb + 0x80) + 0x68), key);

    if (n < 0x191) {
        if (entry != 0) FUN_000151c8(*(void **)(*(long *)((char *)tcb + 0x80) + 0x68), *entry);
        /* copy payload into the transport region */
        unsigned long len = qb[3];
        unsigned long buf[0x100];
        FUN_00117cc4((unsigned long)(buf), *qb, len);
        sk_heap_free((void *)*qb);
        *qb = 0;
        qb[3] = 0;
        qb[4] = 0;
        qb[2] = 0;
        qb[6] = 0;
        *(uint8_t *)(qb + 1) = 0;
        *(unsigned int *)(qb + 5) = 0x100;
        unsigned long nw = FUN_000132d4(len);
        if ((void *)(FUN_000132e0(buf, len) != nw)) { FUN_004b0c28(); FUN_004b0c04(); FUN_004b0068(); }
        *out = (void *)FUN_0005ee58(nw, false, 0, 0);
        return;
    }
    /* large path: register or accumulate the capability (abridged) */
    unsigned long reg = 0;
    if (entry == 0) {
        if (FUN_00016318(&reg) != 0) { *out = (void *)0xd; return; }
        unsigned long cap = FUN_00034f70();
        CallSupervisor(2);
        FUN_00016174(&reg,(void *)( cap));
        FUN_00015108(*(void **)(*(long *)((char *)tcb + 0x80) + 0x68), key,(void *)( reg),(void *)( 0x659128));
    } else {
        reg = entry[2];
    }
    *out = (void *)FUN_0005ee58(0, entry == 0, 0x20, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_000179c8 @ 0x000179c8   (est. sk_fatal_copyin_size)
 * Ghidra: void FUN_000179c8(undefined8 v)
 * Fatal "TB_FATAL: Copyin size did not match" at tb_message.c: prints the
 * string.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__Copyin_size_did_not_ma_005ac03b. */
void sk_fatal_copyin_size(void *v)
{
    sk_puts("TB_FATAL: Copyin size did not match");  /* 0x5ac03b */
}

/*--------------------------------------------------------------------*/
/* FUN_000179d8 @ 0x000179d8   (est. sk_fatal_copyin_overflow)
 * Ghidra: void FUN_000179d8(undefined8 v)
 * Fatal "TB_FATAL: overflow detected when" (copyin): prints the string.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__overflow_detected_when_005aae93. */
void sk_fatal_copyin_overflow(void *v)
{
    sk_puts("TB_FATAL: overflow detected when");  /* 0x5aae93 */
}

/*--------------------------------------------------------------------*/
/* FUN_000179e8 @ 0x000179e8   (est. sk_fatal_copyin_bounds)
 * Ghidra: void FUN_000179e8(undefined8 v)
 * Fatal copyin bounds check (DAT_005aae47): prints the string.
 * Confidence: medium
 * Notes: DAT_005aae47. */
void sk_fatal_copyin_bounds(void *v)
{
    sk_puts((const char *)0x5aae47);
}

/*--------------------------------------------------------------------*/
/* FUN_000179f8 @ 0x000179f8   (est. sk_fatal_copyin_status)
 * Ghidra: void FUN_000179f8(undefined8 v)
 * Fatal copyin status (DAT_005ac18d): prints the string.
 * Confidence: medium
 * Notes: DAT_005ac18d. */
void sk_fatal_copyin_status(void *v)
{
    sk_puts((const char *)0x5ac18d);
}

/*--------------------------------------------------------------------*/
/* FUN_00017a08 @ 0x00017a08   (est. sk_msg_pipe_create)
 * Ghidra: undefined8 FUN_00017a08(undefined8 a, undefined8 b, undefined8 c, undefined8 d)
 * Creates a message pipe: allocates two TCBs (FUN_00014478), builds the
 * pipe (FUN_00017a88), and registers both ends with the scheduler
 * (FUN_000153ec). Returns the pipe.
 * Confidence: medium
 * Notes: helpers FUN_00014478/00017a88/000153ec. */
unsigned long sk_msg_pipe_create(void *a, void *b, void *c, void *d)
{
    unsigned long t1 = (unsigned long)sk_tcb_alloc_dispatch(a);  /* FUN_00014478 */
    unsigned long t2 = (unsigned long)sk_tcb_alloc_dispatch(b);
    unsigned long pipe = (unsigned long)sk_msg_pipe_build(t1, t2, c, d);  /* FUN_00017a88 */
    FUN_000153ec((unsigned long)(a));
    FUN_000153ec((unsigned long)(b));
    return pipe;
}

/*--------------------------------------------------------------------*/
/* FUN_00017a88 @ 0x00017a88   (est. sk_msg_pipe_build)
 * Ghidra: undefined1 * FUN_00017a88(undefined8 a, undefined8 b, ulong flags, undefined8 meta)
 * Builds a message pipe: allocates a 0x20-byte pipe object (tag
 * 0x10a0040b1493d95), optionally marks it bidirectional (offset 0 = 1), binds
 * the two ends (FUN_000145bc / thunk_FUN_00014510), and records the meta
 * (FUN_0004b520) and destructor (FUN_00017c14). Returns the pipe.
 * Confidence: medium
 * Notes: tag 0x10a0040b1493d95; helpers FUN_00010244/004b0244/0004b520/
 *   000145bc/thunk_FUN_00014510/00017c14; globals DAT_004bb180; trap 0x17b78. */
void *sk_msg_pipe_build(void *a, void *b, unsigned long flags, void *meta)
{
    unsigned char *pipe = (unsigned char *)sk_heap_calloc(1, 0x20, (void *)0x10a0040b1493d95);  /* FUN_00010244 */
    unsigned long m;
    if (pipe == 0) {
        FUN_004b0244();
        pipe = (unsigned char *)sk_msg_pipe_build(0, 0, 0, 0x10a0040b1493d95);
        return pipe;
    }
    if ((flags & 1) != 0) *pipe = 1;
    m = FUN_0004b520(meta);
    unsigned long cfg[6];
    cfg[0] = 0x6ad3a8;
    cfg[1] = DAT_004bb180;
    cfg[2] = (unsigned long)FUN_00017c14;
    cfg[3] = 0x659148;
    cfg[4] = m;
    cfg[5] = (unsigned long)pipe;
    *(unsigned long *)(pipe + 8) = FUN_000145bc(a, &cfg);  /* bind end A */
    *(unsigned long *)(pipe + 0x10) = (unsigned long)sk_tcb_obj_create_thunk(b);  /* thunk_FUN_00014510 */
    *(unsigned long *)(pipe + 0x18) = m;
    if ((unsigned long)pipe <= (unsigned long)(pipe + 0x20)) return pipe;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x17b78) */
}

/*--------------------------------------------------------------------*/
/* FUN_00017b7c @ 0x00017b7c   (est. sk_msg_pipe_build_wrap)
 * Ghidra: void FUN_00017b7c(undefined8 a, undefined8 b, undefined8 meta)
 * Wrapper for sk_msg_pipe_build with flags=0.
 * Confidence: medium
 * Notes: helper FUN_00017a88. */
void sk_msg_pipe_build_wrap(void *a, void *b, void *meta)
{
    FUN_00017a88(a, b, 0, meta);
}

/*--------------------------------------------------------------------*/
/* FUN_00017b88 @ 0x00017b88   (est. sk_msg_pipe_create_wrap)
 * Ghidra: void FUN_00017b88(undefined8 a, undefined8 b, undefined8 meta)
 * Wrapper for sk_msg_pipe_create with flags=0.
 * Confidence: medium
 * Notes: helper FUN_00017a08. */
void sk_msg_pipe_create_wrap(void *a, void *b, void *meta)
{
    FUN_00017a08(a, b, 0, meta);
}

/*--------------------------------------------------------------------*/
/* FUN_00017b94 @ 0x00017b94   (est. sk_msg_pipe_validate)
 * Ghidra: void FUN_00017b94(long pipe)
 * Validates a message pipe: checks the second end (offset 0x10) is a valid
 * type, then the first end (offset 8).
 * Confidence: medium
 * Notes: helpers FUN_0001483c/000147e0. */
void sk_msg_pipe_validate(void *pipe)
{
    if (FUN_0001483c(*(void **)((char *)pipe + 0x10)) != 0) return;
    FUN_000147e0(*(void **)((char *)pipe + 8));
}

/*--------------------------------------------------------------------*/
/* FUN_00017bd4 @ 0x00017bd4   (est. sk_msg_pipe_destroy)
 * Ghidra: void FUN_00017bd4(long pipe)
 * Destroys a message pipe: frees the payload (FUN_0004b664), destroys both
 * ends (FUN_00014578), then frees the pipe.
 * Confidence: medium
 * Notes: helpers FUN_0004b664/00014578/thunk_FUN_00012568. */
void sk_msg_pipe_destroy(void *pipe)
{
    FUN_0004b664(*(void **)((char *)pipe + 0x18));
    sk_tcb_obj_destroy(*(void **)((char *)pipe + 8));  /* FUN_00014578 */
    sk_tcb_obj_destroy(*(void **)((char *)pipe + 0x10));
    sk_heap_free(pipe);
}

/*--------------------------------------------------------------------*/
/* FUN_00017c14 @ 0x00017c14   (est. sk_msg_pipe_accept)
 * Ghidra: void FUN_00017c14(long pipe, undefined8 b, int *msg)
 * The message-pipe accept handler: validates the pipe's capability region,
 * dispatches the message (method +0x10), copies the accepted message
 * (FUN_00014bd4/0001574c), and on reply performs a capability transfer
 * (FUN_0001485c/00014f90). Many "TB_ASSERT" panics on bad message state.
 * Confidence: low (structural summary).
 * Notes: string s_TB_ASSERT__in_msg_>state____TB_M_005ac3ef; helpers
 *   FUN_000159b8/00014bd4/0001574c/0001485c/00014f90/000159d0/00014470/
 *   0001590c/00015630/0004b710; panic 004b0c4c; trap 0x17e4c/0x17e74. */
void sk_msg_pipe_accept(void *pipe, void *b, int *msg)
{
    unsigned char *rb = *(unsigned char **)((char *)pipe + 0x28);
    long client = *(long *)((char *)pipe + 0x20);

    if (rb != 0) {
        if (((unsigned long)(rb + 0x20) < (unsigned long)rb) ||
            (unsigned long)*(unsigned char **)((char *)pipe + 0x30) < (unsigned long)(rb + 0x20) ||
            (unsigned long)rb < (unsigned long)*(unsigned char **)((char *)pipe + 0x38)) {
            __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x17e4c) */
        }
    }
    if ((**(int (**)(void))(client + 0x10))(client, rb, msg, 1) == 0) {
        FUN_0001590c(msg);
    } else {
        long *mb = (long *)FUN_000159b8(msg);
        *(void **)(mb + 0x10) = *(void **)(mb + 0x18);
        unsigned long obj = FUN_00014470(*(void **)(rb + 0x10));
        unsigned long rmsg[0xe] = {0};
        unsigned long meta = *(unsigned long *)(rb + 0x10);
        unsigned long len = FUN_000159d0(msg);
        FUN_00014bd4((void *)(meta), &rmsg, rmsg,(void *)( len), 0);
        if (*msg != 4) {
            sk_puts("TB_ASSERT: in_msg->state");  /* 0x5ac3ef */
            __builtin_trap();
        }
        /* validate and copy the reply */
        long *mb2 = (long *)FUN_000159b8(msg);
        long *mb3 = (long *)FUN_000159b8(&rmsg);
        if (*(long *)(mb2 + 0x18) != *(long *)(mb3 + 0x18)) {
            FUN_004b0c4c();
            FUN_0004b710(0, 0, 7);
            return;
        }
        FUN_0001574c(mb3, mb2);
        FUN_0001590c(&rmsg);
        unsigned long flags = (*rb == 0) ? 2 : 0;
        if (FUN_0001485c(meta, &rmsg, &meta, flags) == 0) {
            if ((*rb & 1) == 0 &&
                (**(int (**)(void))(client + 0x10))(client, rb, meta, 0) != 0) {
                unsigned long len2 = FUN_000159d0(&rmsg);
                FUN_00014f90(*(void **)(rb + 8), msg,(void *)( len2), 0);
                long *mb4 = (long *)FUN_000159b8(msg);
                FUN_0001574c(mb4, rmsg);
                *(void **)(mb4 + 0x10) = *(void **)(mb4 + 0x18);
                FUN_0001590c(msg);
            }
            FUN_00015630((void *)(FUN_00014470(*(void **)(rb + 0x10))), rmsg);
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00017e94 @ 0x00017e94   (est. sk_msg_cap_accept)
 * Ghidra: ulong FUN_00017e94(long obj, ulong size, ulong flags, ulong *out, ulong *cb)
 * Accepts a capability from a message: validates the object's accept state,
 * and loops over the message's capability words, copying each into the
 * destination via the object's accept methods (FUN_000155e8/00015670/
 *   00015548) and a scratch capability buffer (tag 0x1090040b6685729).
 * Returns 0 on success, or an error code (5 on no accept method).
 * Confidence: low (large, structural summary).
 * Notes: helpers FUN_000156e0/000159b8/00010244/000155e8/00015670/
 *   00015630/00015548/00014470/000156b8/00014db8/000159b8/0001574c/
 *   00015108/00015904/00014bd0/00014ce0; tags 0x1090040b6685729/
 *   0x1010040ba4d407c/0x100004077774924; panic 004b0c7c/004b0cac/004b0cdc;
 *   trap 0x1816c/0x18368. */
unsigned long sk_msg_cap_accept(void *obj, unsigned long size, unsigned long flags,
                                unsigned long *out, unsigned long *cb)
{
    /* Structural reconstruction: per-capability accept loop (abridged). */
    if (*(long *)((char *)obj + 0x60) != 0) {
        if (*(long *)(*(long *)((char *)obj + 0x60) + 0x38) == 0) return 0;
        return FUN_000156e0() < size;
    }
    unsigned long client = FUN_004b0c7c();
    if (FUN_000156b8(client) == 0) return 1;
    unsigned long avail = FUN_000156e0((void *)(client));
    unsigned long *mb = (unsigned long *)FUN_000159b8(flags);
    unsigned long n = mb[3];
    unsigned long *scratch = (unsigned long *)sk_heap_calloc(1, 0x68, (void *)0x1090040b6685729);
    unsigned long *entry = 0;
    if (scratch == 0) FUN_004b0068();
    unsigned long r = FUN_000155e8((void *)(client),(void *)( avail), 0, scratch);
    if ((int)r == 0) {
        for (unsigned long i = 0; i < n; i++) {
            unsigned long pos = i + avail;
            unsigned long cnt = (n <= pos) ? n - i : avail;
            r = FUN_00015670((void *)(client), scratch, 0,(void *)( cnt));
            if ((int)r != 0) { FUN_00015630(client, scratch); goto fail; }
            FUN_00117cc4(*scratch + scratch[4], *mb + mb[4] + i, cnt);
            scratch[2] += cnt;
            if ((unsigned long)(FUN_00015548(client, flags) != 0) { FUN_00015630(client, scratch); sk_heap_free(scratch); FUN_00015904(flags, mb); return r; })
        }
        FUN_00015630((void *)(client), scratch);
        sk_heap_free(scratch);
        if (out != 0 && n != 0) *out = (unsigned long)flags;
        FUN_00015904(flags,(unsigned long)( mb));
        return 0;
    }
fail:
    sk_heap_free(scratch);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00017edc @ 0x00017edc   (est. sk_msg_cap_accept_variant)
 * Ghidra: undefined8 FUN_00017edc(undefined8 a, undefined8 obj, ulong size, ulong *out, ulong *cb)
 * Variant of sk_msg_cap_accept operating on the caller-provided object.
 * Confidence: low (structural summary; mirrors sk_msg_cap_accept).
 * Notes: helpers FUN_000156b8/000156e0/000159b8/00010244/000155e8/
 *   00015670/00015630/00015548/00014470/00014db8/0001574c/00015108/
 *   00015904/00014bd0/00014ce0; tags 0x1090040b6685729/0x1010040ba4d407c/
 *   0x100004077774924; panics 004b0cac/004b0cdc/004b0068; traps 0x1816c/
 *   0x18368. */
unsigned long sk_msg_cap_accept_variant(void *a, void *obj, unsigned long size,
                                        unsigned long *out, unsigned long *cb)
{
    if (FUN_000156b8(obj) == 0) return 1;
    unsigned long avail = FUN_000156e0(obj);
    unsigned long *mb = (unsigned long *)FUN_000159b8(size);
    unsigned long n = mb[3];
    unsigned long *scratch = (unsigned long *)sk_heap_calloc(1, 0x68, (void *)0x1090040b6685729);
    if (scratch == 0) FUN_004b0068();
    unsigned long r = FUN_000155e8(obj,(void *)( avail), 0, scratch);
    if ((int)r == 0) {
        for (unsigned long i = 0; i < n; i++) {
            unsigned long pos = i + avail;
            unsigned long cnt = (n <= pos) ? n - i : avail;
            r = FUN_00015670(obj, scratch, 0,(void *)( cnt));
            if ((int)r != 0) { FUN_00015630(obj, scratch); goto fail; }
            FUN_00117cc4(*scratch + scratch[4], *mb + mb[4] + i, cnt);
            scratch[2] += cnt;
            if ((unsigned long)(FUN_00015548(obj, size) != 0) { FUN_00015630(obj, scratch); sk_heap_free(scratch); FUN_00015904(size, mb); return r; })
        }
        FUN_00015630(obj, scratch);
        sk_heap_free(scratch);
        if (out != 0 && n != 0) *out = (unsigned long)size;
        FUN_00015904(size,(unsigned long)( mb));
        return 0;
    }
fail:
    sk_heap_free(scratch);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_000181f4 @ 0x000181f4   (est. sk_msg_cap_accept_single)
 * Ghidra: undefined8 FUN_000181f4(undefined8 head, long msg, long *out, undefined8 cb)
 * Accepts a single capability from a message into the registry: finds the
 * message's capability entry (FUN_000159b8), copies its payload into a
 * fresh registry entry (tag 0x1010040ba4d407c), binds it (FUN_00015108),
 * and performs the accept (FUN_00014db8). Stores the result through *out.
 * Returns 0 on success, 5 if the object has no accept method.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_00014470/000156b8/000159b8/00010244/00015108/
 *   000156e0/00014db8/0001574c/0001590c; tags 0x1010040ba4d407c/
 *   0x100004077774924; panic 004b0cdc/004b0068/004b0498; trap 0x18368. */
unsigned long sk_msg_cap_accept_single(void *head, long msg, long *out, void *cb)
{
    unsigned long obj = FUN_00014470(cb);
    if (FUN_000156b8() == 0) return 5;
    unsigned long *mb = (unsigned long *)FUN_000159b8(msg);
    if ((*(uint8_t *)(mb + 5) & 1) == 0) {
        FUN_004b0cdc();
    } else {
        unsigned long key = *(unsigned long *)(msg + 0x18);
        unsigned long *entry = (unsigned long *)sk_heap_calloc(1, 0x20, (void *)0x1010040ba4d407c);
        unsigned long n = mb[3];
        unsigned long buf = (unsigned long)sk_heap_calloc(n, 1, (void *)0x100004077774924);
        if (entry != 0 && buf != 0) {
            FUN_00117cc4(buf, *mb, n);
            entry[2] = n;
            entry[3] = 0;
            *entry = key;
            entry[1] = buf;
            FUN_00015108(head, key, entry,(void *)( 0x659198));
            unsigned long avail = FUN_000156e0((void *)(obj));
            unsigned long r = FUN_00014db8(cb,(void *)( msg), 1,(void *)( avail), 0);
            if ((int)r != 0) return r;
            unsigned long *mb2 = (unsigned long *)FUN_000159b8(msg);
            if (avail <= entry[2]) {
                FUN_00117cc4(mb2[0] + mb2[4], entry[1], avail);
                mb2[2] += avail;
                entry[3] += avail;
                *(uint16_t *)((char *)mb2 + 0x2a) |= 1;
                *out = msg;
                FUN_0001590c((void *)(msg));
                return 0;
            }
        }
        __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18368) */
    }
    FUN_004b0068();
    return 0xd;
}

/*--------------------------------------------------------------------*/
/* FUN_000183f0 @ 0x000183f0   (est. sk_msg_cap_send_accept)
 * Ghidra: undefined8 FUN_000183f0(undefined8 head, undefined8 msg2, long msg, undefined8 b, undefined8 cb)
 * Send-accept path: locates the message's capability entry (FUN_00015264),
 * copies the accepted capability data into it, and advances the transport
 * cursor. Returns 2 if the message flags forbid accept, 0xf if the entry is
 * missing, else 0 on success.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_000159b8/00015264/000156e0/00014db8/0001574c/
 *   0001590c/000151c8/00117cc4; panic 004b0d0c; trap 0x184c4. */
unsigned long sk_msg_cap_send_accept(void *head, void *msg2, long msg, void *b, void *cb)
{
    long *mb = (long *)FUN_000159b8(msg);
    if ((*(uint8_t *)(mb + 0x28) & 1) == 0) {
        long *entry = (long *)FUN_00015264(head, *(void **)((char *)msg + 0x18));
        if (entry == 0) return 0xf;
        unsigned long avail = FUN_000156e0(cb);
        unsigned long used = *(unsigned long *)(entry + 0x18);
        unsigned long total = used + avail;
        unsigned long cap = *(unsigned long *)(entry + 0x10);
        unsigned long cnt = (cap <= total) ? cap - used : avail;
        unsigned long r = FUN_00014db8(msg2,(void *)( msg), 1,(void *)( cnt), 0);
        if ((int)r == 0) {
            unsigned long *mb2 = (unsigned long *)FUN_000159b8(msg);
            *(uint16_t *)((char *)mb2 + 0x2a) = (total < cap) ? 1 : 3;
            unsigned long src = *(long *)(entry + 8) + *(long *)(entry + 0x18);
            if (src <= src + cnt && cnt <= mb2[3]) {
                FUN_00117cc4(*mb2, src, cnt);
                *(unsigned long *)(entry + 0x18) = *(long *)(entry + 0x18) + cnt;
                FUN_0001590c((void *)(msg));
                if ((unsigned long)(cap <= total) FUN_000151c8(head, *(void **)((char *)msg + 0x18));)
                return 0;
            }
            __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x184c4) */
        }
        return r;
    }
    return 2;
}

/*--------------------------------------------------------------------*/
/* FUN_00018560 @ 0x00018560   (est. sk_trap_iter_any)
 * Ghidra: ulong FUN_00018560(undefined8 *list, long n, undefined8 arg)
 * Iterates over a list calling FUN_0001a11c on each element; returns the
 * first nonzero (true) result, else 1.
 * Confidence: medium
 * Notes: helper FUN_0001a11c. */
unsigned long sk_trap_iter_any(void **list, long n, void *arg)
{
    unsigned long r = 1;
    if (list != 0) {
        do {
            if (n == 0) return r;
            n -= 1;
            r = FUN_0001a11c(*list, arg);
            list += 1;
        } while ((r & 1) == 0);
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_000185b8 @ 0x000185b8   (est. sk_msg_region_cursor)
 * Ghidra: int * FUN_000185b8(int *msg, ulong n, ulong len)
 * Advances a message's transport-region cursor: for an active message with
 * enough room, returns it directly; otherwise it resolves the fallback
 * region and copies `len` bytes into it, returning the destination cursor.
 * Panics on invalid state.
 * Confidence: low (structural summary; many 004b0xxx panic helpers).
 * Notes: msg layout (state at 0, transport at +0x14); helpers FUN_00117cc4/
 *   004b0d3c/0d84/0d60/0da8/0e14/0df0/0dcc/0e38/0e80/0e5c/0ea4/0f10/0eec/0ec8;
 *   traps 0x186b8/0x18768. */
int *sk_msg_region_cursor(int *msg, unsigned long n, unsigned long len)
{
    if (*msg == 1) {
        unsigned long c = *(unsigned long *)(*(long *)(msg + 0x14) + 0x10);
        if (c + n >= c && c + n <= *(unsigned long *)(*(long *)(msg + 0x14) + 0x18)) {
            return msg;
        }
    } else {
        FUN_004b0d3c();
    }
    FUN_004b0d84();
    /* fallback: find the destination region and copy */
    int *dst = FUN_004b0d60();
    if (*dst == 4) {
        unsigned long cap = *(unsigned long *)(*(long *)(dst + 0x14) + 0x18);
        unsigned long cur = *(unsigned long *)(*(long *)(dst + 0x14) + 0x10);
        if (cap != 0 && cur + n >= cur && cur + n <= cap) return dst;
    } else {
        FUN_004b0da8();
        FUN_004b0e14();
        FUN_004b0df0();
    }
    dst = FUN_004b0dcc();
    if (*dst == 1) {
        unsigned long *b = *(unsigned long **)(dst + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur + len >= cur && cur + len <= cap) {
            unsigned long base = *b;
            unsigned long dest = base + cur;
            FUN_00117cc4(dest, 0, len);
            *(unsigned long *)(*(long *)(dst + 0x14) + 0x10) += len;
            return dst;
        }
        __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x186b8) */
    } else {
        FUN_004b0e38();
        FUN_004b0e80();
    }
    dst = FUN_004b0e5c();
    if (*dst == 4) {
        unsigned long *b = *(unsigned long **)(dst + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur + len >= cur && cur + len <= cap) {
                unsigned long base = *b;
                b[2] = cur + len;
                FUN_00117cc4(0, base + cur, len);
                return dst;
            }
            __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18768) */
        }
    } else {
        FUN_004b0ea4();
        FUN_004b0f10();
    }
    FUN_004b0eec();
    FUN_004b0ec8();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00018600 @ 0x00018600   (est. sk_msg_region_cursor_v2)
 * Ghidra: int * FUN_00018600(int *msg, ulong n, ulong len)
 * Region-cursor variant starting from a state-4 message; structurally
 * mirrors sk_msg_region_cursor.
 * Confidence: low (structural summary).
 * Notes: same helper set as FUN_000185b8. */
int *sk_msg_region_cursor_v2(int *msg, unsigned long n, unsigned long len)
{
    if (*msg == 4) {
        unsigned long cap = *(unsigned long *)(*(long *)(msg + 0x14) + 0x18);
        if (cap != 0) {
            unsigned long cur = *(unsigned long *)(*(long *)(msg + 0x14) + 0x10);
            if (cur + n >= cur && cur + n <= cap) return msg;
        }
    } else {
        FUN_004b0da8();
        FUN_004b0e14();
        FUN_004b0df0();
    }
    return sk_msg_region_cursor(msg, n, len);
}

/*--------------------------------------------------------------------*/
/* FUN_00018650 @ 0x00018650   (est. sk_msg_region_copy_in)
 * Ghidra: undefined8 FUN_00018650(int *msg, undefined8 src, ulong len)
 * Copies `len` bytes from `src` into the message's transport region,
 * advancing the cursor. Returns the copy status.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_00117cc4/004b0e38/0e80/0e5c/0ea4/0f10/0eec/0ec8;
 *   traps 0x186b8/0x18768. */
unsigned long sk_msg_region_copy_in(int *msg, void *src, unsigned long len)
{
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur + len >= cur && cur + len <= cap) {
            unsigned long base = *b;
            unsigned long dest = base + cur;
            FUN_00117cc4(dest,(unsigned long)( src), len);
            *(unsigned long *)(*(long *)(msg + 0x14) + 0x10) += len;
            return 0;
        }
        __builtin_trap();
    } else {
        FUN_004b0e38();
        FUN_004b0e80();
    }
    int *dst = FUN_004b0e5c();
    if (*dst == 4) {
        unsigned long *b = *(unsigned long **)(dst + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur + len >= cur && cur + len <= cap) {
                unsigned long base = *b;
                b[2] = cur + len;
                FUN_00117cc4((unsigned long)(src), base + cur, len);
                return 0;
            }
            __builtin_trap();
        }
    } else {
        FUN_004b0ea4();
        FUN_004b0f10();
    }
    FUN_004b0eec();
    FUN_004b0ec8();
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0001879c @ 0x0001879c   (est. sk_true)
 * Ghidra: undefined8 FUN_0001879c(void)
 * Returns 1.
 * Confidence: high (trivial). */
unsigned long sk_true(void)
{
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_000187a4 @ 0x000187a4   (est. sk_msg_region_put8)
 * Ghidra: void FUN_000187a4(int *msg, undefined1 v)
 * Writes a byte into the message transport region, advancing the cursor by
 * 1; falls back to the current-thread buffer if the message is not active.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b0f34/0f7c/0f58; trap 0x187f8/0x18854. */
void sk_msg_region_put8(int *msg, uint8_t v)
{
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur != ~0ull && cur + 1 <= cap) {
            unsigned char *base = (unsigned char *)*b;
            base[cur] = v;
            *(long *)(*(long *)(msg + 0x14) + 0x10) += 1;
            return;
        }
        goto fallback;
    } else {
        FUN_004b0f34();
    }
    FUN_004b0f7c();
fallback:
    unsigned long th = FUN_004b0f58();
    unsigned long *b = *(unsigned long **)(th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (cap != cur) {
        ((unsigned char *)*b)[cur] = v;
        *(long *)(*(long *)(th + 0x50) + 0x10) += 1;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18854) */
}

/*--------------------------------------------------------------------*/
/* FUN_0001882c @ 0x0001882c   (est. sk_tb_put8)
 * Ghidra: void FUN_0001882c(long th, undefined1 v)
 * Writes a byte into the current thread's transport buffer, advancing the
 * cursor by 1.
 * Confidence: low (structural summary).
 * Notes: buffer at th+0x50; trap 0x18854. */
void sk_tb_put8(void *th, uint8_t v)
{
    unsigned long *b = *(unsigned long **)((char *)th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (cap != cur) {
        ((unsigned char *)*b)[cur] = v;
        *(long *)(*(long *)((char *)th + 0x50) + 0x10) += 1;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18854) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018878 @ 0x00018878   (est. sk_msg_region_get8)
 * Ghidra: int * FUN_00018878(int *msg, undefined1 *out)
 * Reads a byte from the message transport region, advancing the cursor by
 * 1, and stores it through *out. Returns the message on success.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b0fa0/100c/0fe8/0fc4; trap 0x188d4. */
int *sk_msg_region_get8(int *msg, uint8_t *out)
{
    if (*msg == 4) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur != ~0ull && cur + 1 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 1;
                *out = base[cur];
                return msg;
            }
        }
    } else {
        FUN_004b0fa0();
        FUN_004b100c();
    }
    FUN_004b0fe8();
    FUN_004b0fc4();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000188fc @ 0x000188fc   (est. sk_msg_region_put8_v2)
 * Ghidra: void FUN_000188fc(int *msg, undefined1 v)
 * Byte-put variant; structurally mirrors sk_msg_region_put8 with a
 * different fallback path.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b1030/1078/1054; trap 0x18950/0x189ac. */
void sk_msg_region_put8_v2(int *msg, uint8_t v)
{
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur != ~0ull && cur + 1 <= cap) {
            ((unsigned char *)*b)[cur] = v;
            *(long *)(*(long *)(msg + 0x14) + 0x10) += 1;
            return;
        }
        goto fallback;
    } else {
        FUN_004b1030();
    }
    FUN_004b1078();
fallback:
    unsigned long th = FUN_004b1054();
    unsigned long *b = *(unsigned long **)(th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (cap != cur) {
        ((unsigned char *)*b)[cur] = v;
        *(long *)(*(long *)(th + 0x50) + 0x10) += 1;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x189ac) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018984 @ 0x00018984   (est. sk_tb_put8_v2)
 * Ghidra: void FUN_00018984(long th, undefined1 v)
 * Byte-put into the current thread's transport buffer (mirrors
 * sk_tb_put8).
 * Confidence: low (structural summary).
 * Notes: buffer at th+0x50; trap 0x189ac. */
void sk_tb_put8_v2(void *th, uint8_t v)
{
    sk_tb_put8(th, v);
}

/*--------------------------------------------------------------------*/
/* FUN_000189d0 @ 0x000189d0   (est. sk_msg_region_copy_put)
 * Ghidra: void FUN_000189d0(long msg, undefined8 src, ulong len)
 * Copies `len` bytes from `src` into the message transport region; on
 * overflow falls back to copying through the current thread buffer.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b109c/10c0/112c/1108/10e4; traps 0x18a24/0x18aa8/
 *   0x18af8. */
void sk_msg_region_copy_put(void *msg, void *src, unsigned long len)
{
    unsigned long *b = *(unsigned long **)((char *)msg + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (cur + len >= cur && cur + len <= cap) {
        unsigned long base = *b;
        b[2] = cur + len;
        FUN_00117cc4(base + cur,(unsigned long)( src), len);
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18a24) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018a4c @ 0x00018a4c   (est. sk_msg_region_get8_v2)
 * Ghidra: void FUN_00018a4c(int *msg, undefined1 *out)
 * Byte-get variant; structurally mirrors sk_msg_region_get8.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b10c0/112c/1108/10e4; traps 0x18aa8/0x18af8. */
void sk_msg_region_get8_v2(int *msg, uint8_t *out)
{
    sk_msg_region_get8(msg, out);
}

/*--------------------------------------------------------------------*/
/* FUN_00018ac8 @ 0x00018ac8   (est. sk_tb_get8)
 * Ghidra: void FUN_00018ac8(long th, undefined1 *out)
 * Reads a byte from the current thread's transport buffer, advancing the
 * cursor by 1.
 * Confidence: low (structural summary).
 * Notes: buffer at th+0x50; trap 0x18af8. */
void sk_tb_get8(void *th, uint8_t *out)
{
    unsigned long *b = *(unsigned long **)((char *)th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    b[2] = cur + 1;
    if (cap == cur) __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18af8) */
    *out = ((unsigned char *)*b)[cur];
}

/*--------------------------------------------------------------------*/
/* FUN_00018b0c @ 0x00018b0c   (est. sk_msg_region_put16)
 * Ghidra: void FUN_00018b0c(int *msg, undefined2 v)
 * Writes a 16-bit value into the message transport region, advancing the
 * cursor by 2.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b1150/1198/1174; trap 0x18b64/0x18bc4. */
void sk_msg_region_put16(int *msg, uint16_t v)
{
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur < ~1ull && cur + 2 <= cap) {
            *(uint16_t *)((char *)*b + cur) = v;
            *(long *)(*(long *)(msg + 0x14) + 0x10) += 2;
            return;
        }
    } else {
        FUN_004b1150();
    }
    FUN_004b1198();
    unsigned long th = FUN_004b1174();
    unsigned long *b = *(unsigned long **)(th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (1 < cap - cur) {
        *(uint16_t *)((char *)*b + cur) = v;
        *(long *)(th + 0x50) = *(long *)(*(long *)(th + 0x50) + 0x10) + 2;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18bc4) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018b98 @ 0x00018b98   (est. sk_tb_put16)
 * Ghidra: void FUN_00018b98(long th, undefined2 v)
 * Writes a 16-bit value into the current thread's transport buffer.
 * Confidence: low (structural summary).
 * Notes: buffer at th+0x50; trap 0x18bc4. */
void sk_tb_put16(void *th, uint16_t v)
{
    unsigned long *b = *(unsigned long **)((char *)th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (1 < cap - cur) {
        *(uint16_t *)((char *)*b + cur) = v;
        *(long *)(*(long *)((char *)th + 0x50) + 0x10) += 2;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18bc4) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018be8 @ 0x00018be8   (est. sk_msg_region_get16)
 * Ghidra: dword * FUN_00018be8(dword *msg, undefined2 *out)
 * Reads a 16-bit value from the message transport region, advancing the
 * cursor by 2.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b11bc/1228/1204/11e0; trap 0x18c48. */
void *sk_msg_region_get16(void *msg, uint16_t *out)
{
    int *m = (int *)msg;
    if (*m == 4) {
        unsigned long *b = *(unsigned long **)(m + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur < ~1ull && cur + 2 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 2;
                *out = *(uint16_t *)(base + cur);
                return msg;
            }
        }
    } else {
        FUN_004b11bc();
        FUN_004b1228();
    }
    FUN_004b1204();
    FUN_004b11e0();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00018c70 @ 0x00018c70   (est. sk_msg_region_put32)
 * Ghidra: void FUN_00018c70(int *msg, undefined4 v)
 * Writes a 32-bit value into the message transport region, advancing the
 * cursor by 4.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b124c/1294/1270; trap 0x18cc8/0x18d28. */
void sk_msg_region_put32(int *msg, uint32_t v)
{
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur < ~3ull && cur + 4 <= cap) {
            *(uint32_t *)((char *)*b + cur) = v;
            *(long *)(*(long *)(msg + 0x14) + 0x10) += 4;
            return;
        }
    } else {
        FUN_004b124c();
    }
    FUN_004b1294();
    unsigned long th = FUN_004b1270();
    unsigned long *b = *(unsigned long **)(th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (3 < cap - cur) {
        *(uint32_t *)((char *)*b + cur) = v;
        *(long *)(*(long *)(th + 0x50) + 0x10) += 4;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18d28) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018cfc @ 0x00018cfc   (est. sk_tb_put32)
 * Ghidra: void FUN_00018cfc(long th, undefined4 v)
 * Writes a 32-bit value into the current thread's transport buffer.
 * Confidence: low (structural summary).
 * Notes: buffer at th+0x50; trap 0x18d28. */
void sk_tb_put32(void *th, uint32_t v)
{
    unsigned long *b = *(unsigned long **)((char *)th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (3 < cap - cur) {
        *(uint32_t *)((char *)*b + cur) = v;
        *(long *)(*(long *)((char *)th + 0x50) + 0x10) += 4;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18d28) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018d4c @ 0x00018d4c   (est. sk_msg_region_get32)
 * Ghidra: dword * FUN_00018d4c(dword *msg, undefined4 *out)
 * Reads a 32-bit value from the message transport region, advancing the
 * cursor by 4.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b12b8/1324/1300/12dc; trap 0x18dac. */
void *sk_msg_region_get32(void *msg, uint32_t *out)
{
    int *m = (int *)msg;
    if (*m == 4) {
        unsigned long *b = *(unsigned long **)(m + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur < ~3ull && cur + 4 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 4;
                *out = *(uint32_t *)(base + cur);
                return msg;
            }
        }
    } else {
        FUN_004b12b8();
        FUN_004b1324();
    }
    FUN_004b1300();
    FUN_004b12dc();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00018dd4 @ 0x00018dd4   (est. sk_msg_region_put64)
 * Ghidra: void FUN_00018dd4(int *msg, undefined8 v)
 * Writes a 64-bit value into the message transport region, advancing the
 * cursor by 8.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b1348/1390/136c; trap 0x18e2c/0x18e8c. */
void sk_msg_region_put64(int *msg, void *v)
{
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur < ~7ull && cur + 8 <= cap) {
            *(void **)((char *)*b + cur) = v;
            *(long *)(*(long *)(msg + 0x14) + 0x10) += 8;
            return;
        }
    } else {
        FUN_004b1348();
    }
    FUN_004b1390();
    unsigned long th = FUN_004b136c();
    unsigned long *b = *(unsigned long **)(th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (7 < cap - cur) {
        *(void **)((char *)*b + cur) = v;
        *(long *)(*(long *)(th + 0x50) + 0x10) += 8;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18e8c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018e60 @ 0x00018e60   (est. sk_tb_put64)
 * Ghidra: void FUN_00018e60(long th, undefined8 v)
 * Writes a 64-bit value into the current thread's transport buffer.
 * Confidence: low (structural summary).
 * Notes: buffer at th+0x50; trap 0x18e8c. */
void sk_tb_put64(void *th, void *v)
{
    unsigned long *b = *(unsigned long **)((char *)th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (7 < cap - cur) {
        *(void **)((char *)*b + cur) = v;
        *(long *)(*(long *)((char *)th + 0x50) + 0x10) += 8;
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18e8c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018eb0 @ 0x00018eb0   (est. sk_msg_region_copy_out)
 * Ghidra: void FUN_00018eb0(long msg, undefined8 dst, ulong n)
 * Copies `n` 64-bit words out of the message transport region into `dst`,
 * advancing the cursor; on overflow reads through the current thread buffer.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b13d8/13b4/13fc/1468/1444/1420; trap 0x18f0c/0x18f98/
 *   0x18fec. */
void sk_msg_region_copy_out(void *msg, void *dst, unsigned long n)
{
    unsigned long len = n * 8;
    unsigned long *b = *(unsigned long **)((char *)msg + 0x50);
    unsigned long cur = b[2], cap = b[3];
    if (cur + len >= cur && cur + len <= cap) {
        unsigned long base = *b;
        b[2] = cur + len;
        FUN_00117cc4((unsigned long)(dst), base + cur, len);
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x18f0c) */
}

/*--------------------------------------------------------------------*/
/* FUN_00018f38 @ 0x00018f38   (est. sk_msg_region_get64)
 * Ghidra: void FUN_00018f38(int *msg, undefined8 *out)
 * Reads a 64-bit value from the message transport region, advancing the
 * cursor by 8.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b13fc/1468/1444/1420; trap 0x18f98/0x18fec. */
void sk_msg_region_get64(int *msg, void **out)
{
    if (*msg == 4) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur < ~7ull && cur + 8 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 8;
                *out = *(void **)(base + cur);
                return;
            }
        }
    } else {
        FUN_004b13fc();
        FUN_004b1468();
    }
    FUN_004b1444();
    unsigned long th = FUN_004b1420();
    unsigned long *b = *(unsigned long **)(th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    b[2] = cur + 8;
    if (cap - cur < 8) __builtin_trap();
    *out = *(void **)((char *)*b + cur);
}

/*--------------------------------------------------------------------*/
/* FUN_00018fb8 @ 0x00018fb8   (est. sk_tb_get64)
 * Ghidra: void FUN_00018fb8(long th, undefined8 *out)
 * Reads a 64-bit value from the current thread's transport buffer.
 * Confidence: low (structural summary).
 * Notes: buffer at th+0x50; trap 0x18fec. */
void sk_tb_get64(void *th, void **out)
{
    unsigned long *b = *(unsigned long **)((char *)th + 0x50);
    unsigned long cur = b[2], cap = b[3];
    b[2] = cur + 8;
    if (cap - cur < 8) __builtin_trap();
    *out = *(void **)((char *)*b + cur);
}

/*--------------------------------------------------------------------*/
/* FUN_00019000 @ 0x00019000   (est. sk_msg_region_put8_r)
 * Ghidra: int * FUN_00019000(int *msg, undefined1 v)
 * Byte-put returning the message cursor; structurally mirrors
 * sk_msg_region_put8.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b148c/14d4/14b0/14f8/1564/1540/151c; traps
 *   0x19054/0x190e4. */
int *sk_msg_region_put8_r(int *msg, uint8_t v)
{
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur <= ~1ull && cur + 1 <= cap) {
            ((unsigned char *)*b)[cur] = v;
            *(long *)(*(long *)(msg + 0x14) + 0x10) += 1;
            return msg;
        }
        goto fallback;
    } else {
        FUN_004b148c();
        FUN_004b14d4();
    }
fallback:
    int *dst = (int *)FUN_004b14b0();
    if (*dst == 4) {
        unsigned long *b = *(unsigned long **)(dst + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur != ~0ull && cur + 1 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 1;
                ((unsigned char *)dst)[0] = base[cur];
                return dst;
            }
        }
    } else {
        FUN_004b14f8();
        FUN_004b1564();
    }
    FUN_004b1540();
    FUN_004b151c();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001910c @ 0x0001910c   (est. sk_msg_region_put16_r)
 * Ghidra: dword * FUN_0001910c(dword *msg, undefined2 v)
 * 16-bit put returning the cursor; structurally mirrors sk_msg_region_put16.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b1588/15d0/15ac/15f4/1660/163c/1618; traps
 *   0x19164/0x191f8. */
void *sk_msg_region_put16_r(void *msg, uint16_t v)
{
    int *m = (int *)msg;
    if (*m == 1) {
        unsigned long *b = *(unsigned long **)(m + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur <= ~2ull && cur + 2 <= cap) {
            *(uint16_t *)((char *)*b + cur) = v;
            *(long *)(*(long *)(m + 0x14) + 0x10) += 2;
            return msg;
        }
    } else {
        FUN_004b1588();
        FUN_004b15d0();
    }
    FUN_004b15ac();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00019220 @ 0x00019220   (est. sk_msg_region_put32_r)
 * Ghidra: dword * FUN_00019220(dword *msg, undefined4 v)
 * 32-bit put returning the cursor; structurally mirrors sk_msg_region_put32.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b1684/16cc/16a8/16f0/175c/1738/1714; traps
 *   0x19278/0x1930c. */
void *sk_msg_region_put32_r(void *msg, uint32_t v)
{
    int *m = (int *)msg;
    if (*m == 1) {
        unsigned long *b = *(unsigned long **)(m + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur <= ~4ull && cur + 4 <= cap) {
            *(uint32_t *)((char *)*b + cur) = v;
            *(long *)(*(long *)(m + 0x14) + 0x10) += 4;
            return msg;
        }
    } else {
        FUN_004b1684();
        FUN_004b16cc();
    }
    FUN_004b16a8();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00019224 @ 0x00019224   (est. sk_msg_region_put32_r2)
 * Ghidra: dword * FUN_00019224(dword *msg, undefined4 v)
 * 32-bit put variant; identical body to FUN_00019220.
 * Confidence: low (structural summary). */
void *sk_msg_region_put32_r2(void *msg, uint32_t v)
{
    return sk_msg_region_put32_r(msg, v);
}

/*--------------------------------------------------------------------*/
/* FUN_000192b0 @ 0x000192b0   (est. sk_msg_region_get32_r)
 * Ghidra: dword * FUN_000192b0(dword *msg, undefined4 *out)
 * 32-bit get returning the cursor; structurally mirrors
 * sk_msg_region_get32.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b16f0/175c/1738/1714; trap 0x1930c. */
void *sk_msg_region_get32_r(void *msg, uint32_t *out)
{
    int *m = (int *)msg;
    if (*m == 4) {
        unsigned long *b = *(unsigned long **)(m + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur <= ~4ull && cur + 4 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 4;
                *out = *(uint32_t *)(base + cur);
                return msg;
            }
        }
    } else {
        FUN_004b16f0();
        FUN_004b175c();
    }
    FUN_004b1738();
    FUN_004b1714();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00019334 @ 0x00019334   (est. sk_msg_region_put64_r)
 * Ghidra: dword * FUN_00019334(dword *msg, undefined8 v)
 * 64-bit put returning the cursor; structurally mirrors sk_msg_region_put64.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b1780/17c8/17a4/17ec/1858/1834/1810; traps
 *   0x1938c/0x19420. */
void *sk_msg_region_put64_r(void *msg, void *v)
{
    int *m = (int *)msg;
    if (*m == 1) {
        unsigned long *b = *(unsigned long **)(m + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur <= ~8ull && cur + 8 <= cap) {
            *(void **)((char *)*b + cur) = v;
            *(long *)(*(long *)(m + 0x14) + 0x10) += 8;
            return msg;
        }
    } else {
        FUN_004b1780();
        FUN_004b17c8();
    }
    FUN_004b17a4();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00019338 @ 0x00019338   (est. sk_msg_region_put64_r2)
 * Ghidra: dword * FUN_00019338(dword *msg, undefined8 v)
 * 64-bit put variant; identical body to FUN_00019334.
 * Confidence: low (structural summary). */
void *sk_msg_region_put64_r2(void *msg, void *v)
{
    return sk_msg_region_put64_r(msg, v);
}

/*--------------------------------------------------------------------*/
/* FUN_000193c4 @ 0x000193c4   (est. sk_msg_region_get64_r)
 * Ghidra: dword * FUN_000193c4(dword *msg, undefined8 *out)
 * 64-bit get returning the cursor; structurally mirrors
 * sk_msg_region_get64.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_004b17ec/1858/1834/1810; trap 0x19420. */
void *sk_msg_region_get64_r(void *msg, void **out)
{
    int *m = (int *)msg;
    if (*m == 4) {
        unsigned long *b = *(unsigned long **)(m + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur <= ~8ull && cur + 8 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 8;
                *out = *(void **)(base + cur);
                return msg;
            }
        }
    } else {
        FUN_004b17ec();
        FUN_004b1858();
    }
    FUN_004b1834();
    FUN_004b1810();
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00019440 @ 0x00019440   (est. sk_size4)
 * Ghidra: undefined8 FUN_00019440(void)
 * Returns 4 (size of a u32 message element).
 * Confidence: high (trivial). */
unsigned long sk_size4(void)
{
    return 4;
}

/*--------------------------------------------------------------------*/
/* FUN_00019448 @ 0x00019448   (est. sk_msg_encode_f32_checked)
 * Ghidra: void FUN_00019448(void)
 * Encodes a u32 into the message, trapping with "TB_FATAL:
 * tb_message_encode_f32" on failure.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__tb_message_encode_f32__005ac8f6; helper
 *   FUN_00019490; trap 0x19490. */
void sk_msg_encode_f32_checked(void)
{
    if (FUN_00019490() == 0) return;
    sk_puts("TB_FATAL: tb_message_encode_f32");  /* 0x5ac8f6 */
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_00019490 @ 0x00019490   (est. sk_msg_encode_f32)
 * Ghidra: undefined8 FUN_00019490(uint v, int *msg)
 * Encodes a 32-bit float word into a message transport region, rejecting
 * non-finite values (returns 6) and advancing the cursor by 4. Returns 0.
 * Confidence: medium
 * Notes: helper FUN_00019588; strings s_TB_FATAL__tb_message_decode_f32__005ac926;
 *   panic 004b187c/18c4/18a0; trap 0x19504. */
unsigned long sk_msg_encode_f32(unsigned int v, int *msg)
{
    if (0x7f7fffff < (v & 0x7fffffff)) return 6;
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur < ~3ull && cur + 4 <= cap) {
            *(unsigned int *)((char *)*b + cur) = v;
            *(long *)(*(long *)(msg + 0x14) + 0x10) += 4;
            return 0;
        }
        __builtin_trap();
    } else {
        FUN_004b187c();
    }
    FUN_004b18c4();
    FUN_004b18a0();
    unsigned long r = FUN_00019588();
    if ((int)r != 0) {
        sk_puts("TB_FATAL: tb_message_decode_f32");  /* 0x5ac926 */
        __builtin_trap();
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00019540 @ 0x00019540   (est. sk_msg_decode_f32_checked)
 * Ghidra: void FUN_00019540(void)
 * Decodes a u32 from the message, trapping with "TB_FATAL:
 * tb_message_decode_f32" on failure.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__tb_message_decode_f32__005ac926; helper
 *   FUN_00019588; trap 0x19588. */
void sk_msg_decode_f32_checked(void)
{
    if (FUN_00019588() == 0) return;
    sk_puts("TB_FATAL: tb_message_decode_f32");  /* 0x5ac926 */
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_00019588 @ 0x00019588   (est. sk_msg_decode_f32)
 * Ghidra: undefined4 FUN_00019588(int *msg, uint *out)
 * Decodes a 32-bit float word from a message transport region (state 4),
 * advancing the cursor by 4. Returns 7 if the value is non-finite, 8 on a
 * read failure, else 0.
 * Confidence: medium
 * Notes: helpers FUN_004b18e8/1954/1930/190c; trap 0x195e8. */
unsigned int sk_msg_decode_f32(int *msg, unsigned int *out)
{
    if (*msg == 4) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur < ~3ull && cur + 4 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 4;
                unsigned int v = *(unsigned int *)(base + cur);
                *out = v;
                return (0x7f7fffff < (v & 0x7fffffff)) ? 7 : 0;
            }
        }
    } else {
        FUN_004b18e8();
        FUN_004b1954();
    }
    FUN_004b1930();
    FUN_004b190c();
    return 8;
}

/*--------------------------------------------------------------------*/
/* FUN_00019620 @ 0x00019620   (est. sk_size8)
 * Ghidra: undefined8 FUN_00019620(void)
 * Returns 8 (size of a u64 message element).
 * Confidence: high (trivial). */
unsigned long sk_size8(void)
{
    return 8;
}

/*--------------------------------------------------------------------*/
/* FUN_00019628 @ 0x00019628   (est. sk_msg_encode_f64_checked)
 * Ghidra: void FUN_00019628(void)
 * Encodes a u64 into the message, trapping with "TB_FATAL:
 * tb_message_encode_f64" on failure.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__tb_message_encode_f64__005ac956; helper
 *   FUN_00019670; trap 0x19670. */
void sk_msg_encode_f64_checked(void)
{
    if (FUN_00019670() == 0) return;
    sk_puts("TB_FATAL: tb_message_encode_f64");  /* 0x5ac956 */
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_00019670 @ 0x00019670   (est. sk_msg_encode_f64)
 * Ghidra: undefined8 FUN_00019670(ulong v, int *msg)
 * Encodes a 64-bit double word into a message transport region, rejecting
 * non-finite values (returns 6) and advancing the cursor by 8. Returns 0.
 * Confidence: medium
 * Notes: helper FUN_00019768; strings s_TB_FATAL__tb_message_decode_f64__005ac986;
 *   panic 004b1978/19c0/199c; trap 0x196e4. */
unsigned long sk_msg_encode_f64(unsigned long v, int *msg)
{
    if (0x7fefffffffffffffull < (v & 0x7fffffffffffffff)) return 6;
    if (*msg == 1) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cur = b[2], cap = b[3];
        if (cur < ~7ull && cur + 8 <= cap) {
            *(unsigned long *)((char *)*b + cur) = v;
            *(long *)(*(long *)(msg + 0x14) + 0x10) += 8;
            return 0;
        }
        __builtin_trap();
    } else {
        FUN_004b1978();
    }
    FUN_004b19c0();
    FUN_004b199c();
    unsigned long r = FUN_00019768();
    if ((int)r != 0) {
        sk_puts("TB_FATAL: tb_message_decode_f64");  /* 0x5ac986 */
        __builtin_trap();
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00019720 @ 0x00019720   (est. sk_msg_decode_f64_checked)
 * Ghidra: void FUN_00019720(void)
 * Decodes a u64 from the message, trapping with "TB_FATAL:
 * tb_message_decode_f64" on failure.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__tb_message_decode_f64__005ac986; helper
 *   FUN_00019768; trap 0x19768. */
void sk_msg_decode_f64_checked(void)
{
    if (FUN_00019768() == 0) return;
    sk_puts("TB_FATAL: tb_message_decode_f64");  /* 0x5ac986 */
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_00019768 @ 0x00019768   (est. sk_msg_decode_f64)
 * Ghidra: ulong FUN_00019768(int *msg, ulong *out)
 * Decodes a 64-bit double word from a message transport region (state 4),
 * advancing the cursor by 8. Returns 7 if non-finite, 8 on read failure,
 * else 0.
 * Confidence: medium
 * Notes: helpers FUN_004b19e4/1a50/1a2c/1a08; trap 0x197c8. */
unsigned long sk_msg_decode_f64(int *msg, unsigned long *out)
{
    if (*msg == 4) {
        unsigned long *b = *(unsigned long **)(msg + 0x14);
        unsigned long cap = b[3];
        if (cap != 0) {
            unsigned long cur = b[2];
            if (cur < ~7ull && cur + 8 <= cap) {
                unsigned char *base = (unsigned char *)*b;
                b[2] = cur + 8;
                unsigned long v = *(unsigned long *)(base + cur);
                *out = v;
                return (0x7fefffffffffffffull < (v & 0x7fffffffffffffff)) ? 7 : 0;
            }
        }
    } else {
        FUN_004b19e4();
        FUN_004b1a50();
    }
    FUN_004b1a2c();
    FUN_004b1a08();
    return 8;
}

/*--------------------------------------------------------------------*/
/* FUN_00019800 @ 0x00019800   (est. sk_fatal_tb_decode)
 * Ghidra: void FUN_00019800(undefined8 v)
 * Fatal tb_decode error (DAT_005ac851): prints the string.
 * Confidence: medium
 * Notes: DAT_005ac851. */
void sk_fatal_tb_decode(void *v)
{
    sk_puts((const char *)0x5ac851);
}

/*--------------------------------------------------------------------*/
/* FUN_00019810 @ 0x00019810   (est. sk_fatal_tb_zero_buf)
 * Ghidra: void FUN_00019810(undefined8 v)
 * Fatal "TB_FATAL: TB: 0-size buffer during" : prints the string.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__TB__size_0_buffer_duri_005ac891. */
void sk_fatal_tb_zero_buf(void *v)
{
    sk_puts("TB_FATAL: TB: 0-size buffer during");  /* 0x5ac891 */
}

/*--------------------------------------------------------------------*/
/* FUN_00019820 @ 0x00019820   (est. sk_fatal_tb_decode_underflow)
 * Ghidra: void FUN_00019820(undefined8 v)
 * Fatal tb decode underflow (DAT_005ac6d1): prints the string.
 * Confidence: medium
 * Notes: DAT_005ac6d1. */
void sk_fatal_tb_decode_underflow(void *v)
{
    sk_puts((const char *)0x5ac6d1);
}

/*--------------------------------------------------------------------*/
/* FUN_00019830 @ 0x00019830   (est. sk_fatal_tb_decode_overflow)
 * Ghidra: void FUN_00019830(undefined8 v)
 * Fatal "TB_FATAL: TB: overflow during de" (decode): prints the string.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__TB__overflow_during_de_005ac8c6. */
void sk_fatal_tb_decode_overflow(void *v)
{
    sk_puts("TB_FATAL: TB: overflow during de");  /* 0x5ac8c6 */
}

/*--------------------------------------------------------------------*/
/* FUN_00019840 @ 0x00019840   (est. sk_fatal_tb_encode_overflow)
 * Ghidra: void FUN_00019840(undefined8 v)
 * Fatal "TB_FATAL: TB: overflow during en" (encode): prints the string.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_FATAL__TB__overflow_during_en_005ac821. */
void sk_fatal_tb_encode_overflow(void *v)
{
    sk_puts("TB_FATAL: TB: overflow during en");  /* 0x5ac821 */
}

/*--------------------------------------------------------------------*/
/* FUN_00019850 @ 0x00019850   (est. sk_false)
 * Ghidra: undefined8 FUN_00019850(void)
 * Returns 0.
 * Confidence: high (trivial). */
unsigned long sk_false(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00019858 @ 0x00019858   (est. sk_zero_pair)
 * Ghidra: undefined1 [16] FUN_00019858(void)
 * Returns the zero 16-byte pair.
 * Confidence: high (trivial). */
unsigned long long sk_zero_pair(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00016af0 @ 0x00016af0   (est. sk_capbuf_alloc_meta)
 * Ghidra: undefined8 FUN_00016af0(ulong size, undefined8 b, ulong *cb)
 * Allocates a capability buffer of `size` words (tag 0x100004077774924),
 * initializing the header fields and storing the base through *cb. On
 * allocation failure it releases the previous buffer (thunk_FUN_00012568)
 * and returns its status.
 * Confidence: medium
 * Notes: tag 0x100004077774924; helpers FUN_00010244/004b0080/
 *   thunk_FUN_00012568; trap 0x16b5c. */
unsigned long sk_capbuf_alloc_meta(unsigned long size, void *b, unsigned long *cb)
{
    unsigned long r = (unsigned long)sk_heap_calloc(size, 1, (void *)0x100004077774924);  /* FUN_00010244 */
    if (r != 0) {
        cb[6] = 0;
        *cb = r;
        *(uint8_t *)(cb + 1) = 0;
        cb[2] = 0;
        cb[3] = size;
        cb[4] = 0;
        *(unsigned int *)(cb + 5) = 0;
        return 0;
    }
    unsigned long *old = (unsigned long *)FUN_004b0080();
    unsigned long r2 = (unsigned long)sk_heap_free(*old);
    *old = 0;
    old[3] = 0;
    old[4] = 0;
    old[2] = 0;
    old[6] = 0;
    *(uint8_t *)(old + 1) = 0;
    *(unsigned int *)(old + 5) = 0x100;
    return r2;
}

/*--------------------------------------------------------------------*/
/* FUN_00016ba4 @ 0x00016ba4   (est. sk_capbuf_resize)
 * Ghidra: undefined8 FUN_00016ba4(ulong *cb, undefined8 b, ulong size)
 * Resizes a capability buffer to `size` words (FUN_000102f4), returning 1
 * with a released buffer on allocation failure; returns 0 on success and
 * resets the cursor (cb[2]).
 * Confidence: medium
 * Notes: helper FUN_000102f4/004b0080; trap 0x16c0c. */
unsigned long sk_capbuf_resize(unsigned long *cb, void *b, unsigned long size)
{
    unsigned long r;
    if (size != cb[3]) {
        r = FUN_000102f4(*cb, size,(void *)( 0x360b8758));
        if (r + size < r) __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x16c0c) */
        if (r == 0) { FUN_004b0080(); return 1; }
        *cb = r;
        cb[3] = size;
    }
    cb[2] = 0;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00016c24 @ 0x00016c24   (est. sk_msg_recv_collect)
 * Ghidra: void FUN_00016c24(undefined8 msg, undefined8 tcb)
 * Collects a received message into a TCB: reads the incoming message words
 * (FUN_0005ee50/0005eb78), copies them into the TCB's capability buffer
 * (FUN_00016ba4/00117cc4), and records the message flags and transport
 * handle. Stack canary checked.
 * Confidence: medium
 * Notes: helpers FUN_000159b8/0005ee50/0005eb78/0005ee48/00015984/
 *   00060524/00061638/00015bac/00016ba4/00117cc4; globals DAT_00657fa0;
 *   panics 004b0a18/09e8; trap 0x16d6c. */
void sk_msg_recv_collect(void *msg, void *tcb)
{
    unsigned long *cb = (unsigned long *)FUN_000159b8(tcb);
    unsigned long n = FUN_0005ee50(msg);
    unsigned char buf[0x400];
    if (n >> 0x3d == 0) {
        unsigned long bytes = n * 8;
        FUN_00060524();
        if (n == FUN_0005eb78(buf, bytes, 0)) {
            *(uint16_t *)((char *)cb + 0x2a) = FUN_0005ee48(msg);
            FUN_00015984(tcb, 2);
            FUN_00060524();
            FUN_00015bac(tcb,(void *)( thunk_FUN_00061638()));
            FUN_00016ba4(cb, 0, bytes);
            if (cb[3] <= bytes && bytes - cb[3] != 0) __builtin_trap();
            FUN_00117cc4(*cb,(unsigned long)( buf), bytes);
            return;
        }
        FUN_004b09e8();
        __builtin_trap();
    } else {
        FUN_004b0a18();
        __builtin_trap();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000176a4 helper forward already declared; remaining tail: */
/* FUN_000179c8-000183f0 already above; 16a5c/16d78/16e1c above. */

/*--------------------------------------------------------------------*/
/* FUN_00019aac @ 0x00019aac   (est. sk_tightbeam_register)
 * Ghidra: void FUN_00019aac(undefined8 client)
 * Registers a client with the tightbeam dispatcher (DAT_0064c098, table
 * 0x6593e8) via FUN_0001a0d0.
 * Confidence: medium
 * Notes: globals DAT_0064c098/LAB_006593e8. */
void sk_tightbeam_register(void *client)
{
    FUN_0001a0d0(client, &DAT_0064c098, &LAB_006593e8);
}

/*--------------------------------------------------------------------*/
/* FUN_00019d40 @ 0x00019d40   (est. sk_alloc_pages_pair)
 * Ghidra: long FUN_00019d40(long *out, long *src)
 * Copies a page pointer from *src into *out, retains it (FUN_0036b270),
 * and returns src+0x10 (advancing a descriptor).
 * Confidence: medium
 * Notes: helper FUN_0036b270. */
long sk_alloc_pages_pair(long *out, long *src)
{
    long v = *src;
    *out = v;
    sk_ref_retain(v);  /* FUN_0036b270 */
    return v + 0x10;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a0d0 @ 0x0001a0d0   (est. sk_tightbeam_bind)
 * Ghidra: void FUN_0001a0d0(undefined8 client, long *slot, undefined8 table)
 * Binds a tightbeam client: if the slot is empty, allocates a binding
 * (FUN_00376038) and stores it through *slot.
 * Confidence: medium
 * Notes: helper FUN_00376038. */
void sk_tightbeam_bind(void *client, long *slot, void *table)
{
    if (*slot != 0) return;
    unsigned long r = FUN_00376038(client, table);
    if (r == 0) *slot = r;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a11c @ 0x0001a11c   (est. sk_flag1)
 * Ghidra: uint FUN_0001a11c(void)
 * Returns FUN_0001a138() & 1.
 * Confidence: medium
 * Notes: helper FUN_0001a138. */
unsigned int sk_flag1(void)
{
    return FUN_0001a138() & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a138 @ 0x0001a138   (est. sk_sorted_contains)
 * Ghidra: bool FUN_0001a138(long list, ulong key)
 * Binary search over a sorted 64-bit array (list+0x10, count list+8):
 * returns whether `key` is present. Traps on count < 0.
 * Confidence: medium
 * Notes: traps 0x1a1c0/0x1a1c4/0x1a1c8. */
bool sk_sorted_contains(void *list, unsigned long key)
{
    long lo, hi, mid;
    if (list == 0) return true;
    if (*(long *)((char *)list + 0x10) == 0) return false;
    hi = *(long *)((char *)list + 8) - 1;
    if (hi < 0) __builtin_trap();
    lo = 0;
    mid = hi / 2;
    while (lo <= mid && mid <= hi) {
        unsigned long v = *(unsigned long *)(*(long *)((char *)list + 0x10) + mid * 8);
        if (v == key) return true;
        if (key < v) hi = mid - 1;
        else lo = mid + 1;
        mid = lo + (hi - lo) / 2;
    }
    return false;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a1c8 @ 0x0001a1c8   (est. sk_noop2)
 * Ghidra: void FUN_0001a1c8(void)
 * No-op.
 * Confidence: high (trivial). */
void sk_noop2(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0001a1cc @ 0x0001a1cc   (est. sk_second_arg)
 * Ghidra: undefined8 FUN_0001a1cc(undefined8 a, undefined8 b)
 * Returns its second argument.
 * Confidence: high (trivial). */
void *sk_second_arg(void *a, void *b)
{
    return b;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a1dc @ 0x0001a1dc   (est. sk_copyin_data)
 * Ghidra: ulong FUN_0001a1dc(undefined8 dst, undefined8 src, ulong phys, ulong desc)
 * Copies data from a source descriptor into a destination region,
 * resolving the physical mapping (FUN_002b24b8) and memcopying via
 * FUN_0001a2f4. Returns the copied size.
 * Confidence: low (structural summary; paging/descriptor logic).
 * Notes: helpers FUN_002b24b8/0001d4a0/002a9ba8/0001a2f4/003a25d4/
 *   thunk_FUN_0036b270. */
unsigned long sk_copyin_data(void *dst, void *src, unsigned long phys, unsigned long desc)
{
    unsigned long p = phys & 0xffffffffffff;
    if ((desc & 0x2000000000000000) != 0) p = desc >> 0x38 & 0xf;
    thunk_FUN_0036b270(desc);
    FUN_003a25d4(desc);
    return p;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a2f4 @ 0x0001a2f4   (est. sk_copyin_validate)
 * Ghidra: void FUN_0001a2f4(long src, long len, long dst, long dst_end, long check)
 * Validates a copy range [src, src+len) fits within [dst, dst_end), then
 * copies via FUN_00117d14. Traps on out-of-range or negative length.
 * Confidence: medium
 * Notes: helper FUN_00117d14; traps 0x1a320/0x1a348/0x1a34c/0x1a350/0x1a354. */
void sk_copyin_validate(long src, long len, long dst, long dst_end, long check)
{
    long avail;
    if (check < 0) __builtin_trap();
    avail = (dst != 0) ? dst_end - dst : 0;
    if (avail < check) __builtin_trap();
    if (check == 0) {
        if (dst == 0) return;
    } else if (dst == 0) {
        __builtin_trap();
    }
    if (len <= check) {
        if (src == 0) return;
        if (len < 0) __builtin_trap();
        FUN_00117d14(dst, src, len);
        return;
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_0001a354 @ 0x0001a354   (est. sk_desc_make)
 * Ghidra: undefined1 [16] FUN_0001a354(undefined8 phys)
 * Builds a {base, len} descriptor pair from a physical address
 * (FUN_00115080), trapping on a negative result.
 * Confidence: medium
 * Notes: helper thunk_FUN_00115080; trap 0x1a388. */
unsigned long sk_desc_make(void *phys)
{
    long l = thunk_FUN_00115080();
    if (-1 < l) return (unsigned long)phys;  /* {base=phys, len=l} */
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x1a388) */
}

/*--------------------------------------------------------------------*/
/* FUN_0001a3dc @ 0x0001a3dc   (est. sk_copyout_validate)
 * Ghidra: void FUN_0001a3dc(long src, long len)
 * Validates and copies out `len` bytes from `src` via FUN_001e9c78,
 * treating a NULL source as length 0 and trapping on negative length.
 * Confidence: medium
 * Notes: helper FUN_001e9c78; trap 0x1a3f4. */
void sk_copyout_validate(void *src, long len)
{
    if (src == 0) len = 0;
    else if (len < 0) __builtin_trap();
    FUN_001e9c78(src, len);
}

/*--------------------------------------------------------------------*/
/* FUN_0001a3e0 @ 0x0001a3e0   (est. sk_copyout_validate2)
 * Ghidra: void FUN_0001a3e0(long src, long len)
 * Identical to sk_copyout_validate.
 * Confidence: medium
 * Notes: helper FUN_001e9c78; trap 0x1a3f4. */
void sk_copyout_validate2(void *src, long len)
{
    sk_copyout_validate(src, len);
}

/*--------------------------------------------------------------------*/
/* FUN_0001a404 @ 0x0001a404   (est. sk_copyout_desc)
 * Ghidra: void FUN_0001a404(void)
 * Copies out the descriptor [*x20, x20[1]] via FUN_001e9c78, handling NULL.
 * Confidence: medium
 * Notes: helper FUN_001e9c78; trap 0x1a424. */
void sk_copyout_desc(void)
{
    long *d = 0;
    long len = (*d == 0) ? 0 : d[1];
    if (d[1] < 0) __builtin_trap();
    FUN_001e9c78((void *)(*d), len);
}

/*--------------------------------------------------------------------*/
/* FUN_0001a408 @ 0x0001a408   (est. sk_copyout_desc2)
 * Ghidra: void FUN_0001a408(void)
 * Identical to sk_copyout_desc.
 * Confidence: medium
 * Notes: helper FUN_001e9c78; trap 0x1a424. */
void sk_copyout_desc2(void)
{
    sk_copyout_desc();
}

/*--------------------------------------------------------------------*/
/* FUN_0001a448 @ 0x0001a448   (est. sk_desc_pair)
 * Ghidra: undefined1 [16] FUN_0001a448(undefined8 base, undefined8 len)
 * Builds a {base, len} descriptor, retaining `len` (FUN_0036b270).
 * Confidence: medium
 * Notes: helper thunk_FUN_0036b270. */
unsigned long sk_desc_pair(void *base, void *len)
{
    thunk_FUN_0036b270((unsigned long)(len));
    return (unsigned long)base;  /* {base, len} */
}

/*--------------------------------------------------------------------*/
/* FUN_0001a47c @ 0x0001a47c   (est. sk_desc_phys_validate)
 * Ghidra: ulong FUN_0001a47c(ulong phys, ulong desc)
 * Validates a physical descriptor: returns phys if the low 48 bits are
 * nonzero, else logs via FUN_003698b0 (tag 0x6598d8) and returns 1.
 * Confidence: medium
 * Notes: helpers FUN_003a25d4/003698b0; globals DAT_00659b58/0x6598d8. */
unsigned long sk_desc_phys_validate(unsigned long phys, unsigned long desc)
{
    unsigned long p = phys & 0xffffffffffff;
    if ((desc & 0x2000000000000000) != 0) p = desc >> 0x38 & 0xf;
    if (p != 0) return phys;
    FUN_003a25d4(desc);
    unsigned char f = 1;
    FUN_003698b0(&f, &DAT_00659b58, 0x6598d8);
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a4f0 @ 0x0001a4f0   (est. sk_copyin_region)
 * Ghidra: long FUN_0001a4f0(undefined8 *dst, long dst_end, ulong phys, ulong desc)
 * Copies a data region into a destination buffer, writing a "DATADESC"
 * header (magic 0x5459504544415441) and the copied payload via
 * FUN_0001a1dc. Returns the region length, or 0 after logging a failure.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_002b24b8/0001a1dc/003698b0; magic 0x5459504544415441;
 *   globals DAT_00659b58/0x6598d8; traps 0x1a614/0x1a61c/0x1a620/0x1a624. */
long sk_copyin_region(void **dst, long dst_end, unsigned long phys, unsigned long desc)
{
    unsigned long p;
    long len;
    if ((desc >> 0x3c & 1) == 0) {
        p = phys & 0xffffffffffff;
        if ((desc & 0x2000000000000000) != 0) p = desc >> 0x38 & 0xf;
    } else {
        p = FUN_002b24b8();
    }
    len = p + 0x10;
    if (dst == 0) {
        if (len < 1) __builtin_trap();
    } else {
        unsigned long avail = dst_end - (long)dst;
        if (len <= avail) {
            if (len < 0) __builtin_trap();
            if (0xf < avail) {
                void **h = dst + 2;
                *dst = (void *)0x5459504544415441;
                dst[1] = (void *)len;
                FUN_0001a1dc(h,(void *)( dst_end), phys, desc);
                return len;
            }
            __builtin_trap();
        }
    }
    unsigned char f = 0;
    FUN_003698b0(&f, &DAT_00659b58, 0x6598d8, desc);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a648 @ 0x0001a648   (est. sk_desc_load)
 * Ghidra: undefined1 [16] FUN_0001a648(void)
 * Loads the descriptor at x20+0x10, retaining the length (x20+0x18).
 * Confidence: medium
 * Notes: helper thunk_FUN_0036b270. */
unsigned long sk_desc_load(void)
{
    return *(unsigned long *)0;  /* {base=x20+0x10, len=x20+0x18} */
}

/*--------------------------------------------------------------------*/
/* FUN_0001a72c @ 0x0001a72c   (est. sk_metadata_write)
 * Ghidra: void FUN_0001a72c(undefined1 *out, undefined8 a, undefined2 b, undefined8 c, undefined8 d, undefined8 e)
 * Writes a metadata record header: value `a` split across bytes/shorts,
 * then b/c/d/e fields.
 * Confidence: medium
 * Notes: metadata record layout. */
void sk_metadata_write(uint8_t *out, void *a, uint16_t b, void *c, void *d, void *e)
{
    unsigned long v = (unsigned long)a;
    out[0] = (uint8_t)v;
    out[1] = (uint8_t)(v >> 8);
    out[2] = (uint8_t)(v >> 0x10);
    *(uint16_t *)(out + 4) = (uint16_t)(v >> 0x20);
    *(uint16_t *)(out + 6) = (uint16_t)(v >> 0x30);
    *(uint16_t *)(out + 8) = b;
    *(void **)(out + 0x10) = c;
    *(void **)(out + 0x18) = d;
    *(void **)(out + 0x20) = e;
}

/*--------------------------------------------------------------------*/
/* FUN_0001a760 @ 0x0001a760   (est. sk_serialized_size)
 * Ghidra: long FUN_0001a760(void)
 * Computes the serialized size of a metadata/descriptor structure: 0x25
 * header plus the length of the data descriptor and each element's
 * descriptor length. Traps on overflow.
 * Confidence: medium
 * Notes: helpers FUN_002b24b8; traps 0x1a808/0x1a824/0x1a828/0x1a838. */
long sk_serialized_size(void)
{
    long size = 0x25;
    unsigned long n = *(unsigned long *)0;
    if (n == 0) {
        size = 0x25;
    } else {
        unsigned long p = *(unsigned long *)0 & 0xffffffffffff;
        if ((n & 0x2000000000000000) != 0) p = n >> 0x38 & 0xf;
        size = p + 0x25;
        if (p + 0x25 < p) __builtin_trap();
    }
    long extra = 0;
    unsigned long *e = (unsigned long *)(*(long *)0 + 0x28);
    long cnt = *(long *)(*(long *)0 + 0x10) + 1;
    for (;;) {
        cnt -= 1;
        if (cnt == 0) {
            if (size + extra < size) __builtin_trap();
            return size + extra;
        }
        unsigned long d = *e;
        unsigned long p = d >> 0x3c & 1 ? FUN_002b24b8() : ((d & 0x2000000000000000) ? d >> 0x38 & 0xf : e[-1] & 0xffffffffffff);
        if (p + 0x10 < p) break;
        e += 2;
        extra += p + 0x10;
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x1a808) */
}

/*--------------------------------------------------------------------*/
/* FUN_0001a838 @ 0x0001a838   (est. sk_metadata_serialize)
 * Ghidra: ulong FUN_0001a838(undefined8 *out, long out_end)
 * Serializes a metadata structure into `out`, writing a "CLNTDATA"
 * header (magic 0x434c4e5444415441), the total size, flags, and each
 * element's descriptor + payload. Returns the serialized size.
 * Confidence: low (structural summary).
 * Notes: magic 0x434c4e5444415441; helpers FUN_0001a760/002b24b8/0001a1dc/
 *   0001db00/0001a4f0/003698b0; globals DAT_00659b58/0x6598d8; traps
 *   0x1a8a8/0x1aac4/0x1aac8/0x1aacc/0x1aaf0/0x1aaf4/0x1aaf8/0x1aabc/
 *   0x1aac0/0x1ab00. */
unsigned long sk_metadata_serialize(void **out, long out_end)
{
    unsigned long total = FUN_0001a760();
    if (out == 0) {
        if (0 < (long)total) goto fail;
    } else if (out_end - (long)out < (long)total) {
fail:
        unsigned char f = 0;
        FUN_003698b0(&f, &DAT_00659b58, 0x6598d8);
        return 0;
    }
    unsigned long len = *(unsigned long *)0;
    unsigned long p;
    if (len == 0) p = 0;
    else if ((len >> 0x3c & 1) == 0) {
        p = *(unsigned long *)0 & 0xffffffffffff;
        if ((len & 0x2000000000000000) != 0) p = len >> 0x38 & 0xf;
    } else p = FUN_002b24b8();
    void **o = out;
    *o = (void *)0x434c4e5444415441;
    o[1] = (void *)total;
    *(uint8_t *)(o + 2) = *(uint8_t *)((char *)0 + 2);
    *(uint16_t *)((char *)o + 0x11) = *(uint16_t *)((char *)0 + 4);
    *(uint16_t *)((char *)o + 0x13) = *(uint16_t *)((char *)0 + 6);
    *(unsigned long *)((char *)o + 0x15) = p;
    *(long *)((char *)o + 0x1d) = *(long *)((char *)0 + 0x10);
    /* serialize each element descriptor + payload (abridged) */
    unsigned long used = 0x25;
    if (FUN_0001db00(0x25, p, out_end, out, 0) != 1) used = FUN_0001db00(0x25, p, out_end, out, 0);
    return total;
}

/*--------------------------------------------------------------------*/
/* FUN_0001ab00 @ 0x0001ab00   (est. sk_metadata_validate_range)
 * Ghidra: void FUN_0001ab00(long size, long base, long end)
 * Validates a metadata range [base, end) is at least `size` bytes;
 * traps on a short or negative range.
 * Confidence: medium
 * Notes: helper FUN_0001db00; traps 0x1ab7c/0x1ab80/0x1ab84. */
void sk_metadata_validate_range(long size, long base, long end)
{
    long avail;
    if (size < 0) __builtin_trap();
    avail = (base != 0) ? end - base : 0;
    unsigned long r = FUN_0001db00(0, size, avail, base, end);
    long used = (r == 1) ? avail : r;
    if (used <= avail) {
        if (-1 < used) return;
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_0001ab94 @ 0x0001ab94   (est. sk_metadata_alloc)
 * Ghidra: undefined1 [16] FUN_0001ab94(undefined8 base, undefined8 len, long size)
 * Allocates a metadata region of `size` bytes: allocates a descriptor
 * (FUN_0001db94), records the size, and zeroes the payload (FUN_00114330).
 * Returns {base, len}.
 * Confidence: medium
 * Notes: helpers FUN_0001db94/thunk_FUN_00114330; trap 0x1ac14. */
unsigned long sk_metadata_alloc(void *base, void *len, long size)
{
    if (size < 0) __builtin_trap();
    if (size != 0) {
        long d = (long)FUN_0001db94(size);
        *(long *)(d + 0x10) = size;
        thunk_FUN_00114330((void *)(d + 0x20), size);
    }
    return (unsigned long)base;  /* {base, len} */
}

/*--------------------------------------------------------------------*/
/* FUN_0001ac14 @ 0x0001ac14   (est. sk_metadata_iterate)
 * Ghidra: void FUN_0001ac14(undefined8 a, undefined8 b, long meta, undefined8 c, undefined8 d)
 * Iterates over a metadata structure, invoking a callback on each element
 * and validating the iteration invariants. (Large, structural.)
 * Confidence: low (large, structural summary).
 * Notes: helpers FUN_003a261c/0001dd00/0001adec/00310d34; globals
 *   UINT_006775b0; traps 0x1ade0/0x1ade4/0x1ade8/0x1add8/0x1addc/0x1adec. */
void sk_metadata_iterate(void *a, void *b, long meta, void *c, void *d)
{
    /* Structural reconstruction: walks the metadata element list and calls
     * the bound visitor per element, validating cursor progress. */
    long d0 = *(long *)(meta - 8);
    long cur = *(long *)(d0 + 0x10);
    long cursor = *(long *)0;
    cursor = cur;
    if (FUN_003a261c(cursor) & 1) {
        cursor = FUN_0001dd00((void *)(cursor));
    }
    FUN_0001adec(&cursor, a, b, meta, c, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0001adec @ 0x0001adec   (est. sk_metadata_walk)
 * Ghidra: void FUN_0001adec(...)  (large metadata walk)
 * Walks the metadata structure element by element, dispatching each through
 * a visitor and validating the cursor. (Large, structural.)
 * Confidence: low (large, structural summary).
 * Notes: many helper calls + traps. */
void sk_metadata_walk(void *a, void *b, void *c, long meta, void *d, void *e)
{
    /* Structural reconstruction (abridged): iterates the metadata elements
     * and validates each against the descriptor bounds. */
    long base = *(long *)(meta - 8);
    long *cur = (long *)(base + 0x10);
    long end = base + 0x20;
    for (long i = 0; i < *cur; i++) {
        /* visit element i (visitor callback) */
    }
    FUN_00310d34(0, &UINT_006775b0);
}

/*--------------------------------------------------------------------*/
/* FUN_0001aeec @ 0x0001aeec   (est. sk_metadata_decode)
 * Ghidra: void FUN_0001aeec(...)  (large metadata decode)
 * Decodes a serialized metadata region into structured elements. (Large.)
 * Confidence: low (large, structural summary). */
void sk_metadata_decode(void *a, void *b, void *c, void *d, void *e, void *f)
{
    /* Structural reconstruction (abridged): reads the header, validates the
     * size, and decodes each element descriptor. */
    FUN_0001a760();
}

/*--------------------------------------------------------------------*/
/* FUN_0001afb4 @ 0x0001afb4   (est. sk_metadata_element_encode)
 * Ghidra: undefined8 FUN_0001afb4(...)  (large element encode)
 * Encodes a metadata element. (Large, structural.)
 * Confidence: low (large, structural summary). */
unsigned long sk_metadata_element_encode(void *a, void *b, void *c, void *d)
{
    return FUN_0001db00(0, 0, 0, a, b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001b02c @ 0x0001b02c   (est. sk_metadata_element_decode)
 * Ghidra: void FUN_0001b02c(...)  (large element decode)
 * Decodes a metadata element. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_metadata_element_decode(void *a, void *b, void *c, void *d)
{
    FUN_003a25d4(0);
    FUN_00310d34(0, &UINT_006775b0);
}

/*--------------------------------------------------------------------*/
/* FUN_0001b360 @ 0x0001b360   (est. sk_noop3)
 * Ghidra: void FUN_0001b360(void)
 * No-op.
 * Confidence: high (trivial). */
void sk_noop3(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0001b370 @ 0x0001b370   (est. sk_metadata_flags)
 * Ghidra: long FUN_0001b370(void)
 * Derives metadata flags (large decode helper). (Structural.)
 * Confidence: low (structural summary). */
long sk_metadata_flags(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001b620 @ 0x0001b620   (est. sk_metadata_validate_all)
 * Ghidra: void FUN_0001b620(...)  (large metadata validation)
 * Validates the full metadata structure. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_metadata_validate_all(void *a, void *b, void *c, void *d)
{
    sk_puts("TB_ASSERT: metadata validation");  /* structural */
    FUN_00310d34(0, &UINT_006775b0);
}

/*--------------------------------------------------------------------*/
/* FUN_0001b998 @ 0x0001b998   (est. sk_metadata_element_size)
 * Ghidra: long FUN_0001b998(void)
 * Computes a metadata element size. (Structural.)
 * Confidence: low (structural summary). */
long sk_metadata_element_size(void)
{
    return FUN_0001a760();
}

/*--------------------------------------------------------------------*/
/* FUN_0001ba10 @ 0x0001ba10   (est. sk_metadata_copy)
 * Ghidra: void FUN_0001ba10(...)
 * Copies a metadata element. (Structural.)
 * Confidence: low (structural summary). */
void sk_metadata_copy(void *dst, void *src, void *len)
{
    FUN_00117cc4((unsigned long)(dst),(unsigned long)( src), (unsigned long)len);
}

/*--------------------------------------------------------------------*/
/* FUN_0001ba18 @ 0x0001ba18   (est. sk_metadata_copy2)
 * Ghidra: void FUN_0001ba18(...)
 * Second metadata-copy variant. (Structural.)
 * Confidence: low (structural summary). */
void sk_metadata_copy2(void *dst, void *src, void *len)
{
    FUN_00117cc4((unsigned long)(dst),(unsigned long)( src), (unsigned long)len);
}

/*--------------------------------------------------------------------*/
/* FUN_0001bcac @ 0x0001bcac   (est. sk_payload_encode)
 * Ghidra: void FUN_0001bcac(...)  (large payload encode)
 * Encodes a data payload region. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_payload_encode(void *dst, void *src, void *len, void *desc)
{
    FUN_0001a1dc(dst, src, (unsigned long)len, (unsigned long)desc);
}

/*--------------------------------------------------------------------*/
/* FUN_0001bd08 @ 0x0001bd08   (est. sk_payload_decode)
 * Ghidra: void FUN_0001bd08(...)  (large payload decode)
 * Decodes a data payload region. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_payload_decode(void *dst, void *src, void *len, void *desc)
{
    FUN_00117cc4((unsigned long)(dst),(unsigned long)( src), (unsigned long)len);
}

/*--------------------------------------------------------------------*/
/* FUN_0001bd84 @ 0x0001bd84   (est. sk_payload_copyin)
 * Ghidra: void FUN_0001bd84(...)
 * Copies a payload in. (Structural.)
 * Confidence: low (structural summary). */
void sk_payload_copyin(void *dst, void *src, void *len)
{
    FUN_00117cc4((unsigned long)(dst),(unsigned long)( src), (unsigned long)len);
}

/*--------------------------------------------------------------------*/
/* FUN_0001bea0 @ 0x0001bea0   (est. sk_payload_copyout)
 * Ghidra: void FUN_0001bea0(...)
 * Copies a payload out. (Structural.)
 * Confidence: low (structural summary). */
void sk_payload_copyout(void *dst, void *src, void *len)
{
    FUN_00117cc4((unsigned long)(dst),(unsigned long)( src), (unsigned long)len);
}

/*--------------------------------------------------------------------*/
/* FUN_0001bfa4 @ 0x0001bfa4   (est. sk_payload_size)
 * Ghidra: void FUN_0001bfa4(...)
 * Computes a payload size. (Structural.)
 * Confidence: low (structural summary). */
void sk_payload_size(void *a)
{
    FUN_0001a760();
}

/*--------------------------------------------------------------------*/
/* FUN_0001c038 @ 0x0001c038   (est. sk_tightbeam_frame_encode)
 * Ghidra: void FUN_0001c038(...)  (large tightbeam frame encode)
 * Encodes a tightbeam message frame. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_frame_encode(void *a, void *b, void *c, void *d)
{
    FUN_0001a838(a, (long)b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001c294 @ 0x0001c294   (est. sk_cmp_u8)
 * Ghidra: bool FUN_0001c294(char a, char b)
 * Returns whether two bytes are equal.
 * Confidence: high (trivial). */
bool sk_cmp_u8(char a, char b)
{
    return a == b;
}

/*--------------------------------------------------------------------*/
/* FUN_0001c2a4 @ 0x0001c2a4   (est. sk_tightbeam_init)
 * Ghidra: void FUN_0001c2a4(...)  (large tightbeam init)
 * Initializes a tightbeam connection. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_init(void *a, void *b, void *c, void *d)
{
    FUN_0001a0d0(a, b, c);
}

/*--------------------------------------------------------------------*/
/* FUN_0001c2e8 @ 0x0001c2e8   (est. sk_tightbeam_send)
 * Ghidra: void FUN_0001c2e8(...)  (large tightbeam send)
 * Sends a tightbeam message. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_send(void *a, void *b, void *c, void *d)
{
    FUN_0001a838(a, (long)b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001c330 @ 0x0001c330   (est. sk_tightbeam_recv)
 * Ghidra: void FUN_0001c330(...)  (large tightbeam recv)
 * Receives a tightbeam message. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_recv(void *a, void *b, void *c, void *d)
{
    FUN_00016c24(a, b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001c3c8 @ 0x0001c3c8   (est. sk_tightbeam_dispatch)
 * Ghidra: void FUN_0001c3c8(...)  (large tightbeam dispatch)
 * Dispatches an incoming tightbeam message. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_dispatch(void *a, void *b, void *c, void *d)
{
    FUN_00017c14(a, b, c);
}

/*--------------------------------------------------------------------*/
/* FUN_0001c4cc @ 0x0001c4cc   (est. sk_tightbeam_validate)
 * Ghidra: void FUN_0001c4cc(...)  (large tightbeam validate)
 * Validates a tightbeam frame. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_validate(void *a, void *b, void *c, void *d)
{
    FUN_0001e12c(a, (long)b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001c668 @ 0x0001c668   (est. sk_tightbeam_validate2)
 * Ghidra: void FUN_0001c668(...)  (large tightbeam validate2)
 * Second tightbeam validation. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_validate2(void *a, void *b, void *c, void *d)
{
    FUN_0001e3e0(a, (long)b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001c6fc @ 0x0001c6fc   (est. sk_tightbeam_frame_decode)
 * Ghidra: void FUN_0001c6fc(...)  (large tightbeam frame decode)
 * Decodes a tightbeam message frame. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_frame_decode(void *a, void *b, void *c, void *d)
{
    FUN_00016c24(a, b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001c81c @ 0x0001c81c   (est. sk_tightbeam_metadata)
 * Ghidra: void FUN_0001c81c(...)  (large tightbeam metadata)
 * Handles tightbeam metadata. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_metadata(void *a, void *b, void *c, void *d)
{
    FUN_0001a838(a, (long)b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001cba4 @ 0x0001cba4   (est. sk_tightbeam_connection_init)
 * Ghidra: void FUN_0001cba4(...)  (large tightbeam connection init)
 * Initializes a tightbeam connection object. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_connection_init(void *a, void *b, void *c, void *d)
{
    FUN_0001f1d0(a, 3, b, 3, c);
}

/*--------------------------------------------------------------------*/
/* FUN_0001cbec @ 0x0001cbec   (est. sk_tightbeam_connection_send)
 * Ghidra: void FUN_0001cbec(...)
 * Sends on a tightbeam connection. (Structural.)
 * Confidence: low (structural summary). */
void sk_tightbeam_connection_send(void *a, void *b, void *c, void *d)
{
    FUN_0001f834(a, b, c, (unsigned long)d);
}

/*--------------------------------------------------------------------*/
/* FUN_0001cc34 @ 0x0001cc34   (est. sk_tightbeam_connection_recv)
 * Ghidra: void FUN_0001cc34(...)
 * Receives on a tightbeam connection. (Structural.)
 * Confidence: low (structural summary). */
void sk_tightbeam_connection_recv(void *a, void *b, void *c, void *d)
{
    FUN_0001f834(a, b, c, (unsigned long)d);
}

/*--------------------------------------------------------------------*/
/* FUN_0001ccec @ 0x0001ccec   (est. sk_tightbeam_connection_close)
 * Ghidra: void FUN_0001ccec(...)
 * Closes a tightbeam connection. (Structural.)
 * Confidence: low (structural summary). */
void sk_tightbeam_connection_close(void *a)
{
    FUN_0036b118(a);
}

/*--------------------------------------------------------------------*/
/* FUN_0001ccf0 @ 0x0001ccf0   (est. sk_tightbeam_connection_close2)
 * Ghidra: void FUN_0001ccf0(...)
 * Second connection-close variant. (Structural.)
 * Confidence: low (structural summary). */
void sk_tightbeam_connection_close2(void *a)
{
    FUN_0036b118(a);
}

/*--------------------------------------------------------------------*/
/* FUN_0001cd1c @ 0x0001cd1c   (est. sk_tightbeam_forward)
 * Ghidra: void FUN_0001cd1c(...)  (large tightbeam forward)
 * Forwards a tightbeam message. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_forward(void *a, void *b, void *c, void *d)
{
    FUN_0001f834(a, b, c, (unsigned long)d);
}

/*--------------------------------------------------------------------*/
/* FUN_0001ced0 @ 0x0001ced0   (est. sk_tightbeam_forwarding)
 * Ghidra: void FUN_0001ced0(...)  (large tightbeam forwarding)
 * Forwards a tightbeam connection. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_forwarding(void *a, void *b, void *c, void *d)
{
    FUN_0001f834(a, b, c, (unsigned long)d);
}

/*--------------------------------------------------------------------*/
/* FUN_0001cf2c @ 0x0001cf2c   (est. sk_tightbeam_forwarding2)
 * Ghidra: void FUN_0001cf2c(...)  (large tightbeam forwarding2)
 * Second forwarding variant. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_forwarding2(void *a, void *b, void *c, void *d)
{
    FUN_0001f834(a, b, c, (unsigned long)d);
}

/*--------------------------------------------------------------------*/
/* FUN_0001cfc8 @ 0x0001cfc8   (est. sk_tightbeam_forwarding3)
 * Ghidra: void FUN_0001cfc8(...)  (large tightbeam forwarding3)
 * Third forwarding variant. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_forwarding3(void *a, void *b, void *c, void *d)
{
    FUN_0001f834(a, b, c, (unsigned long)d);
}

/*--------------------------------------------------------------------*/
/* FUN_0001d05c @ 0x0001d05c   (est. sk_tightbeam_connection_alloc)
 * Ghidra: void FUN_0001d05c(...)  (large tightbeam connection alloc)
 * Allocates a tightbeam connection. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_connection_alloc(void *a, void *b, void *c, void *d)
{
    FUN_0001f414(a, b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001d194 @ 0x0001d194   (est. sk_tightbeam_connection_alloc2)
 * Ghidra: void FUN_0001d194(...)  (large tightbeam connection alloc2)
 * Second connection allocator. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_connection_alloc2(void *a, void *b, void *c, void *d)
{
    FUN_0001f514(a, b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001d328 @ 0x0001d328   (est. sk_tightbeam_connection_alloc3)
 * Ghidra: void FUN_0001d328(...)  (large tightbeam connection alloc3)
 * Third connection allocator. (Large, structural.)
 * Confidence: low (large, structural summary). */
void sk_tightbeam_connection_alloc3(void *a, void *b, void *c, void *d)
{
    FUN_0001fa18(a, 3, b, 3, c, d);
}

/*--------------------------------------------------------------------*/
/* FUN_0001d4a0 @ 0x0001d4a0   (est. sk_pt_desc_resolve)
 * Ghidra: undefined1 [16] FUN_0001d4a0(ulong a, ulong b)
 * Resolves a page-table descriptor pair. (Structural.)
 * Confidence: low (structural summary). */
unsigned long sk_pt_desc_resolve(unsigned long a, unsigned long b)
{
    return a;
}

/*--------------------------------------------------------------------*/
/* FUN_0001d4f4 @ 0x0001d4f4   (est. sk_pt_desc_free)
 * Ghidra: void FUN_0001d4f4(...)
 * Frees a page-table descriptor. (Structural.)
 * Confidence: low (structural summary). */
void sk_pt_desc_free(void *a, void *b)
{
    FUN_003a25d4((unsigned long)b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001d540 @ 0x0001d540   (est. sk_pt_desc_validate)
 * Ghidra: void FUN_0001d540(...)
 * Validates a page-table descriptor. (Structural.)
 * Confidence: low (structural summary). */
void sk_pt_desc_validate(void *a, void *b, void *c)
{
    FUN_0001a2f4((long)a, (long)b, (long)c, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0001d648 @ 0x0001d648   (est. sk_pt_desc_copy)
 * Ghidra: void FUN_0001d648(...)
 * Copies a page-table descriptor. (Structural.)
 * Confidence: low (structural summary). */
void sk_pt_desc_copy(void *a, void *b, void *c)
{
    FUN_00117cc4((unsigned long)(a),(unsigned long)( b), (unsigned long)c);
}

/*--------------------------------------------------------------------*/
/* FUN_0001d7a0 @ 0x0001d7a0   (est. sk_pt_desc_size)
 * Ghidra: void FUN_0001d7a0(...)
 * Computes a page-table descriptor size. (Structural.)
 * Confidence: low (structural summary). */
void sk_pt_desc_size(void *a)
{
    FUN_0001a760();
}

/*--------------------------------------------------------------------*/
/* FUN_0001d888 @ 0x0001d888   (est. sk_metadata_destroy)
 * Ghidra: void FUN_0001d888(...)
 * Destroys a metadata structure. (Structural.)
 * Confidence: low (structural summary). */
void sk_metadata_destroy(void *a)
{
    FUN_0036b118(a);
}

/*--------------------------------------------------------------------*/
/* FUN_0001da84 @ 0x0001da84   (est. sk_metadata_alloc2)
 * Ghidra: void FUN_0001da84(...)
 * Second metadata allocator. (Structural.)
 * Confidence: low (structural summary). */
void sk_metadata_alloc2(void *a, void *b, void *c)
{
    FUN_0001ab94(a, b, (long)c);
}

/*--------------------------------------------------------------------*/
/* FUN_0001db00 @ 0x0001db00   (est. sk_range_check)
 * Ghidra: undefined1 [16] FUN_0001db00(long base, ulong size, ulong avail, long p, long end)
 * Range checker: returns {base+size, 0} if [base, base+size) fits within
 * [p, end), else {1, 0x100} indicating failure. Traps on negative inputs.
 * Confidence: medium
 * Notes: traps 0x1db7c/0x1db80/0x1db84/0x1db88/0x1db8c/0x1db90/0x1db94. */
unsigned long sk_range_check(long base, unsigned long size, unsigned long avail, long p, long end)
{
    unsigned long len = (p != 0) ? end - p : 0;
    if (base < 0) __builtin_trap();
    if ((long)len < base) __builtin_trap();
    if ((long)avail < 0) __builtin_trap();
    if (len < avail) __builtin_trap();
    avail -= (unsigned long)base;
    if ((long)size < 1) {
        if (((long)avail < 1) && ((long)size < (long)avail)) return 0x100000000000000ull;
    } else if ((-1 < (long)avail) && (avail < size)) {
        return 0x100000000000000ull;
    }
    unsigned long end_addr = (unsigned long)base + size;
    if ((unsigned long)base + size < (unsigned long)base) __builtin_trap();
    if ((long)end_addr < 0) __builtin_trap();
    if (len < end_addr) __builtin_trap();
    return end_addr;
}

/*--------------------------------------------------------------------*/
/* FUN_0001db94 @ 0x0001db94   (est. sk_metadata_buf_alloc)
 * Ghidra: undefined * FUN_0001db94(long size)
 * Allocates a metadata buffer of `size` bytes (FUN_0036a940, tag 7),
 * recording the element count. Returns the buffer.
 * Confidence: medium
 * Notes: helpers FUN_00002534/0036a940/thunk_FUN_000126e8; globals
 *   s___cstring_0064c108/DAT_004be910. */
void *sk_metadata_buf_alloc(long size)
{
    if (0 < size) {
        unsigned long t = FUN_00002534((const char *)0x64c108, &DAT_004be910);
        void *b = FUN_0036a940(t, size + 0x20, 7);
        long n = thunk_FUN_000126e8();
        *(unsigned long *)((char *)b + 0x10) = 0;
        *(long *)((char *)b + 0x18) = n * 2 + -0x40;
        return b;
    }
    return &DAT_00657778;
}

/*--------------------------------------------------------------------*/
/* FUN_0001dc08 @ 0x0001dc08   (est. sk_wordbuf_alloc)
 * Ghidra: undefined * FUN_0001dc08(long count, long cap)
 * Allocates a word buffer holding `count` 64-bit elements with capacity
 * `cap`, recording both in the header.
 * Confidence: medium
 * Notes: helpers FUN_00002534/0036a940/thunk_FUN_000126e8; globals
 *   s___cstring_0064c108+8/DAT_004c0740. */
void *sk_wordbuf_alloc(long count, long cap)
{
    long c = (cap <= count) ? count : cap;
    if (c == 0) return &DAT_00657778;
    unsigned long t = FUN_00002534((const char *)0x64c108 + 8, &DAT_004c0740);
    void *b = FUN_0036a940(t, c * 8 + 0x20, 7);
    long n = thunk_FUN_000126e8();
    long shift = (0x1f < n) ? n - 0x20 : n - 0x19;
    *(long *)((char *)b + 0x10) = count;
    *(long *)((char *)b + 0x18) = (shift >> 3) << 1;
    return b;
}

/*--------------------------------------------------------------------*/
/* FUN_0001dc8c @ 0x0001dc8c   (est. sk_bytebuf_alloc)
 * Ghidra: undefined * FUN_0001dc8c(long count, long cap)
 * Allocates a byte buffer holding `count` bytes with capacity `cap`.
 * Confidence: medium
 * Notes: helpers FUN_00002534/0036a940/thunk_FUN_000126e8; globals
 *   s___cstring_0064c108/DAT_004be910. */
void *sk_bytebuf_alloc(long count, long cap)
{
    long c = (cap <= count) ? count : cap;
    if (c == 0) return &DAT_00657778;
    unsigned long t = FUN_00002534((const char *)0x64c108, &DAT_004be910);
    void *b = FUN_0036a940(t, c + 0x20, 7);
    long n = thunk_FUN_000126e8();
    *(long *)((char *)b + 0x10) = count;
    *(long *)((char *)b + 0x18) = n * 2 + -0x40;
    return b;
}

/*--------------------------------------------------------------------*/
/* FUN_0001dd00 @ 0x0001dd00   (est. sk_buf_relocate)
 * Ghidra: void FUN_0001dd00(long buf)
 * Relocates a buffer, releasing it via sk_bytebuf_grow(0, ...).
 * Confidence: medium
 * Notes: helper FUN_0001dde4. */
void sk_buf_relocate(void *buf)
{
    FUN_0001dde4(0, *(unsigned long *)((char *)buf + 0x10), 0, buf);
}

/*--------------------------------------------------------------------*/
/* FUN_0001dd14 @ 0x0001dd14   (est. sk_wordbuf_grow)
 * Ghidra: long FUN_0001dd14(ulong keep, ulong count, ulong opts, long buf)
 * Grows a word buffer: allocates a new buffer (sk_wordbuf_alloc) with at
 * least `count` capacity, copies the existing elements (FUN_00117cc4 /
 * FUN_00117d14), and frees the old buffer (FUN_0036b118). Returns the new
 * buffer.
 * Confidence: medium
 * Notes: helpers FUN_0001dc08/00117cc4/00117d14/0036b118; traps 0x1dde0/
 *   0x1dde4. */
long sk_wordbuf_grow(unsigned long keep, unsigned long count, unsigned long opts, void *buf)
{
    unsigned long n = count;
    if ((opts & 1) != 0) {
        n = *(unsigned long *)((char *)buf + 0x18) >> 1;
        if ((long)n < (long)count) {
            n = *(unsigned long *)((char *)buf + 0x18) & 0xfffffffffffffffe;
            if ((long)n <= (long)count) n = count;
        }
    }
    long old = *(long *)((char *)buf + 0x10);
    long nb = (long)FUN_0001dc08(old, n);
    unsigned long newd = nb + 0x20;
    unsigned long oldd = (unsigned long)buf + 0x20;
    if ((keep & 1) == 0) {
        FUN_00117cc4(newd, oldd, old * 8);
    } else {
        if (nb != (long)buf && oldd + old * 8 > newd) {
            FUN_00117d14(newd, oldd, old << 3);
        }
        *(unsigned long *)((char *)buf + 0x10) = 0;
    }
    FUN_0036b118(buf);
    return nb;
}

/*--------------------------------------------------------------------*/
/* FUN_0001dde4 @ 0x0001dde4   (est. sk_bytebuf_grow)
 * Ghidra: long FUN_0001dde4(ulong keep, ulong count, ulong opts, long buf)
 * Grows a byte buffer (sk_bytebuf_alloc), mirroring sk_wordbuf_grow but
 * with byte granularity.
 * Confidence: medium
 * Notes: helpers FUN_0001dc8c/00117cc4/00117d14/0036b118; traps 0x1deac/
 *   0x1deb0. */
long sk_bytebuf_grow(unsigned long keep, unsigned long count, unsigned long opts, void *buf)
{
    unsigned long n = count;
    if ((opts & 1) != 0) {
        n = *(unsigned long *)((char *)buf + 0x18) >> 1;
        if ((long)n < (long)count) {
            n = *(unsigned long *)((char *)buf + 0x18) & 0xfffffffffffffffe;
            if ((long)n <= (long)count) n = count;
        }
    }
    long old = *(long *)((char *)buf + 0x10);
    long nb = (long)FUN_0001dc8c(old, n);
    unsigned long newd = nb + 0x20;
    unsigned long oldd = (unsigned long)buf + 0x20;
    if ((keep & 1) == 0) {
        FUN_00117cc4(newd, oldd, old);
    } else {
        if (nb != (long)buf && oldd + old > newd) {
            FUN_00117d14(newd, oldd, old);
        }
        *(unsigned long *)((char *)buf + 0x10) = 0;
    }
    FUN_0036b118(buf);
    return nb;
}

/*--------------------------------------------------------------------*/
/* FUN_0001deb0 @ 0x0001deb0   (est. sk_wordbuf_relocate)
 * Ghidra: void FUN_0001deb0(void)
 * Relocates a word buffer via sk_wordbuf_grow, storing the result through
 * the current descriptor pointer.
 * Confidence: medium
 * Notes: helper FUN_0001dd14. */
void sk_wordbuf_relocate(void)
{
    long r = FUN_0001dd14();
    *(long *)0 = r;
}

/*--------------------------------------------------------------------*/
/* FUN_0001df2c @ 0x0001df2c   (est. sk_desc_store)
 * Ghidra: void FUN_0001df2c(undefined8 *out, undefined8 *desc)
 * Stores a 4-word descriptor into *out.
 * Confidence: medium
 * Notes: helper FUN_0001afb4. */
void sk_desc_store(void **out, void **desc)
{
    *out = (void *)FUN_0001afb4(desc[0], desc[1], desc[2], desc[3]);
}

/*--------------------------------------------------------------------*/
/* FUN_0001df60 @ 0x0001df60   (est. sk_tb_forward_get)
 * Ghidra: void FUN_0001df60(void)
 * Lazily initializes the tightbeam forwarding table (DAT_0064c0f8) via
 * FUN_00376820.
 * Confidence: medium
 * Notes: globals DAT_0064c0f8/DAT_004edbe8/0x677880. */
void sk_tb_forward_get(void)
{
    if (DAT_0064c0f8 != 0) return;
    DAT_0064c0f8 = FUN_00376820(&DAT_004edbe8, 0x677880);
}

/*--------------------------------------------------------------------*/
/* FUN_0001dfb4 @ 0x0001dfb4   (est. sk_metadata_size_sum)
 * Ghidra: long FUN_0001dfb4(long meta)
 * Computes the total serialized size of a metadata structure: iterates the
 * element descriptors, summing each element's size, and returns the total.
 * Confidence: medium
 * Notes: helpers thunk_FUN_0024d9ac/0036b118/0001deb0/0001eec8/0024917c/
 *   0001ef00; globals DAT_004bb860/00657778/00657788; trap 0x1e12c. */
long sk_metadata_size_sum(long meta)
{
    unsigned long tag = thunk_FUN_0024d9ac(&DAT_004bb860);
    long n = *(long *)(meta + 0x10);
    if (n == 0) {
        FUN_0036b118((void *)(tag));
        return 0;
    }
    long *buf = &DAT_00657778;
    FUN_0001deb0(0, n, 0);
    long *e = (long *)(meta + 0x20);
    for (;;) {
        long save = (long)buf;
        n -= 1;
        unsigned long v[5] = {e[0], e[1], e[2], e[3], e[4]};
        unsigned long out[4];
        FUN_0001eec8(&v[0], out);
        FUN_0024917c(out, &v[0]);
        FUN_0001ef00(&v[0]);
        unsigned long sz = out[0];
        unsigned long cur = *(unsigned long *)((char *)buf + 0x10);
        if (*(unsigned long *)((char *)buf + 0x18) >> 1 <= cur) {
            FUN_0001deb0(1 < *(unsigned long *)((char *)buf + 0x18), cur + 1, 1);
        }
        *(unsigned long *)((char *)buf + 0x10) = cur + 1;
        *(unsigned long *)((char *)buf + cur * 8 + 0x20) = sz;
        if (n == 0) break;
        e += 5;
    }
    FUN_0036b118((void *)(tag));
    n = *(long *)((char *)buf + 0x10);
    long total = 0;
    long *szs = (long *)((char *)buf + 0x20);
    for (long i = 0; i < n; i++) {
        total += szs[i];
        if (total < 0) __builtin_trap();
    }
    FUN_0036b118(buf);
    return total;
}

/*--------------------------------------------------------------------*/
/* FUN_0001e12c @ 0x0001e12c   (est. sk_tb_validate_data)
 * Ghidra: void FUN_0001e12c(long *data, long end)
 * Validates a tightbeam data structure: checks the header magic
 * (0x5459504544415441 = "DATADATA"), the declared size fits, and otherwise
 * reports a fatal error ("Fatal error", "Tightbeam ComponentInitData.swift")
 * via FUN_001afa84.
 * Confidence: medium (string-matched "Fatal error").
 * Notes: strings s_Fatal_error_005accd0,
 *   s_Tightbeam_ComponentInitData_swif_005ac9c0; helpers FUN_0001e790/
 *   0001df60/001ba7d4/002a4ab4/002acbb8/003a25d4; magic 0x5459504544415441. */
void sk_tb_validate_data(long *data, long end)
{
    if (data == 0 || (unsigned long)(end - (long)data) < 0x10) {
        FUN_001afa84("Fatal error", 0xb, 2, 0xd000000000000037,
                     0x80000000005acba0, "Tightbeam ComponentInitData.swift", 0x21, 2, 0x19b, 0);
    } else if (*data == 0x5459504544415441) {
        if (data[1] < 0) __builtin_trap();
        if ((unsigned long)data[1] <= (unsigned long)(end - (long)data)) return;
        FUN_001afa84("Fatal error", 0xb, 2, 0xd000000000000023,
                     0x80000000005acb50, "Tightbeam ComponentInitData.swift", 0x21, 2, 0x1a2, 0);
    } else {
        FUN_001afa84("Fatal error", 0xb, 2, 0xd000000000000010,
                     0x80000000005acb80, "Tightbeam ComponentInitData.swift", 0x21, 2, 0x19f, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0001e3e0 @ 0x0001e3e0   (est. sk_tb_validate_component)
 * Ghidra: void FUN_0001e3e0(long *data, long end)
 * Validates a tightbeam component structure: checks the "CLNTDATA" magic
 * (0x434c4e5444415441), otherwise reports a fatal error via FUN_001afa84.
 * Confidence: medium (string-matched "Fatal error").
 * Notes: strings s_Fatal_error_005accd0,
 *   s_Tightbeam_ComponentInitData_swif_005ac9c0; magic 0x434c4e5444415441;
 *   helpers FUN_0001e790/0001df60/001ba7d4/002a4ab4/002acbb8/003a25d4. */
void sk_tb_validate_component(long *data, long end)
{
    if (data == 0 || (unsigned long)(end - (long)data) < 0x25) {
        FUN_001afa84("Fatal error", 0xb, 2, 0xd000000000000033,
                     0x80000000005acaf0, "Tightbeam ComponentInitData.swift", 0x21, 2, 0x1f2, 0);
    } else if (*data == 0x434c4e5444415441) {
        if (data[1] < 0) __builtin_trap();
        if ((unsigned long)data[1] <= (unsigned long)(end - (long)data)) return;
        FUN_001afa84("Fatal error", 0xb, 2, 0xd000000000000023,
                     0x80000000005acb50, "Tightbeam ComponentInitData.swift", 0x21, 2, 0x1fa, 0);
    } else {
        FUN_001afa84("Fatal error", 0xb, 2, 0xd00000000000001b,
                     0x80000000005acb30, "Tightbeam ComponentInitData.swift", 0x21, 2, 0x1f6, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0001e694 @ 0x0001e694   (est. sk_tb_init_validate)
 * Ghidra: long * FUN_0001e694(long *data, ulong size)
 * Validates a tightbeam init structure: rejects a negative size, an
 * oversized request (logs via FUN_003698b0, tag 0x659938), and a NULL or
 * wrong-magic header ("INITDATA" = 0x494e495444415441).
 * Confidence: medium
 * Notes: magic 0x494e495444415441; helpers FUN_003698b0; globals
 *   0x65a210/0x659938; traps 0x1e78c/0x1e790. */
long *sk_tb_init_validate(long *data, unsigned long size)
{
    if ((long)size < 0) __builtin_trap();
    if (size < 0x20) {
        unsigned char f = 0;
        FUN_003698b0(&f,(void *)( 0x65a210), 0x659938);
        return 0;
    }
    if (data == 0) __builtin_trap();
    if (*data == 0x494e495444415441) {
        if (size != (unsigned long)data[1]) {
            unsigned char f = 2;
            FUN_003698b0(&f,(void *)( 0x65a210), 0x659938);
            return (long *)2;
        }
    } else {
        unsigned char f = 1;
        FUN_003698b0(&f,(void *)( 0x65a210), 0x659938);
        return (long *)1;
    }
    return data;
}

/*--------------------------------------------------------------------*/
/* FUN_0001e790 @ 0x0001e790   (est. sk_tb_init_get)
 * Ghidra: void FUN_0001e790(void)
 * Lazily initializes the tightbeam init table (DAT_0064c100) via
 * FUN_00376820.
 * Confidence: medium
 * Notes: globals DAT_0064c100/DAT_004ed758/0x677790. */
void sk_tb_init_get(void)
{
    if (DAT_0064c100 != 0) return;
    DAT_0064c100 = FUN_00376820(&DAT_004ed758, 0x677790);
}

/*--------------------------------------------------------------------*/
/* FUN_0001eec8 @ 0x0001eec8   (est. sk_tb_encode_word)
 * Ghidra: undefined8 FUN_0001eec8(undefined8 src, undefined8 out)
 * Encodes a metadata element via the tightbeam codec (FUN_0035dc24,
 * table 0x659c50).
 * Confidence: medium
 * Notes: helpers thunk_FUN_0035dc24; table LAB_00659c50. */
unsigned long sk_tb_encode_word(void *src, void *out)
{
    thunk_FUN_0035dc24(out, src, &LAB_00659c50);
    return (unsigned long)out;
}

/*--------------------------------------------------------------------*/
/* FUN_0001ef00 @ 0x0001ef00   (est. sk_tb_decode_word)
 * Ghidra: undefined8 FUN_0001ef00(undefined8 src)
 * Decodes a metadata element via the tightbeam codec (FUN_0035d334).
 * Confidence: medium
 * Notes: helpers thunk_FUN_0035d334; table LAB_00659c50. */
unsigned long sk_tb_decode_word(void *src)
{
    thunk_FUN_0035d334(src, &LAB_00659c50);
    return (unsigned long)src;
}

/*--------------------------------------------------------------------*/
/* FUN_0001ef30 @ 0x0001ef30   (thunk sk_zone_match)
 * Ghidra: long thunk_FUN_000126e8(long p)
 * Thunk to sk_zone_match (FUN_000126e8).
 * Confidence: high (thunk). */
long sk_zone_match_thunk(void *p)
{
    return sk_zone_match(p);
}

/*--------------------------------------------------------------------*/
/* FUN_0001ef34 @ 0x0001ef34   (est. sk_serialized_size_store)
 * Ghidra: void FUN_0001ef34(undefined8 *out)
 * Stores the serialized size (FUN_0001a760) through *out.
 * Confidence: medium
 * Notes: helper FUN_0001a760. */
void sk_serialized_size_store(void **out)
{
    *out = (void *)FUN_0001a760();
}

/*--------------------------------------------------------------------*/
/* FUN_0001ef60 @ 0x0001ef60   (est. sk_tb_forward_meta)
 * Ghidra: void FUN_0001ef60(undefined8 a, undefined8 b)
 * Forwards tightbeam metadata via sk_metadata_decode.
 * Confidence: medium
 * Notes: helper FUN_0001aeec. */
void sk_tb_forward_meta(void *a, void *b)
{
    FUN_0001aeec(a, 0, 0, 0, 0, b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001ef64 @ 0x0001ef64   (est. sk_tb_forward_meta2)
 * Ghidra: void FUN_0001ef64(undefined8 a, undefined8 b)
 * Second metadata-forward variant.
 * Confidence: medium
 * Notes: helper FUN_0001aeec. */
void sk_tb_forward_meta2(void *a, void *b)
{
    FUN_0001aeec(a, 0, 0, 0, 0, b);
}

/*--------------------------------------------------------------------*/
/* FUN_0001ef88 @ 0x0001ef88   (thunk sk_noop2)
 * Ghidra: void thunk_FUN_0001a1c8(void)
 * Thunk to sk_noop2 (FUN_0001a1c8).
 * Confidence: high (thunk). */
void sk_noop2_thunk(void)
{
}

/*--------------------------------------------------------------------*/
/* FUN_0001efd4 @ 0x0001efd4   (est. sk_tb_conn_teardown)
 * Ghidra: void FUN_0001efd4(void)
 * Tears down a tightbeam connection's reader (FUN_0036a1a0/0036b8b0).
 * Confidence: medium
 * Notes: helpers FUN_0036a1a0/0036b8b0. */
void sk_tb_conn_teardown(void)
{
    FUN_0036a1a0(0, 0, 0, 0);
    FUN_0036b8b0(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0001f010 @ 0x0001f010   (est. sk_tb_conn_attach)
 * Ghidra: void FUN_0001f010(undefined8 a, undefined8 b)
 * Attaches a payload to a tightbeam connection reader.
 * Confidence: medium
 * Notes: helpers FUN_0036a1a0/0036b834/0036b118. */
void sk_tb_conn_attach(void *a, void *b)
{
    FUN_0036a1a0(0, 0, 1, 0);
    *(unsigned long *)0 = (unsigned long)b;
    FUN_0036b834(0, a);
    FUN_0036b118(a);
}

/*--------------------------------------------------------------------*/
/* FUN_0001f070 @ 0x0001f070   (est. sk_tb_conn_create)
 * Ghidra: undefined1 [16] FUN_0001f070(long *out)
 * Creates a tightbeam connection object: allocates 0x30 bytes (tag 0x1f57),
 * records the owner, sets up the reader (FUN_0036a1a0/0036b8b0), and
 * returns a {func=sk_tb_conn_handler, data=&conn+0x18} pair.
 * Confidence: medium
 * Notes: tag 0x1f57; helpers FUN_0036a908/0036a1a0/0036b8b0. */
unsigned long sk_tb_conn_create(long *out)
{
    long c = FUN_0036a908(0x30, 0x1f57);
    *out = c;
    *(long *)(c + 0x28) = 0;
    FUN_0036a1a0(0,(void *)( c), 0x21, 0);
    *(unsigned long *)(c + 0x18) = FUN_0036b8b0(0);
    *(unsigned long *)(c + 0x20) = 0;
    return (unsigned long)FUN_0001f0f0;  /* {func, data=c+0x18} */
}

/*--------------------------------------------------------------------*/
/* FUN_0001f0f0 @ 0x0001f0f0   (est. sk_tb_conn_handler)
 * Ghidra: void FUN_0001f0f0(long *conn, ulong mode)
 * Tightbeam connection handler: releases the bound payload (FUN_0036b834)
 * and frees the connection.
 * Confidence: medium
 * Notes: helpers FUN_0036b834/0036a20c/0036b118/thunk_FUN_00012568. */
void sk_tb_conn_handler(long *conn, unsigned long mode)
{
    long c = *conn;
    void *payload = *(void **)(c + 0x18);
    long owner = *(long *)(c + 0x28);
    *(unsigned long *)(owner + 0x20) = *(unsigned long *)(c + 0x20);
    FUN_0036b834((void *)(owner + 0x18), payload);
    if ((mode & 1) == 0) {
        FUN_0036a20c((void *)(c));
        FUN_0036b118(payload);
    } else {
        FUN_0036b118(*(void **)(c + 0x18));
        FUN_0036a20c((void *)(c));
    }
    sk_heap_free((void *)c);
}

/*--------------------------------------------------------------------*/
/* FUN_0001f168 @ 0x0001f168   (est. sk_tb_pipe_alloc)
 * Ghidra: undefined8 FUN_0001f168(undefined8 a, undefined8 b, undefined8 c, undefined8 d)
 * Allocates a tightbeam pipe (FUN_0036a940) and configures it via
 * FUN_0001f1d0.
 * Confidence: medium
 * Notes: helpers FUN_0036a940/0001f1d0. */
unsigned long sk_tb_pipe_alloc(void *a, void *b, void *c, void *d)
{
    unsigned long p = FUN_0036a940();
    FUN_0001f1d0(a,(unsigned long)( b), c,(unsigned long)( d));
    return p;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f1d0 @ 0x0001f1d0   (est. sk_tb_pipe_config)
 * Ghidra: void FUN_0001f1d0(undefined8 a, byte kind, undefined8 b, byte kind2)
 * Configures a tightbeam pipe: sets up the reader, creates the two
 * endpoint nodes (FUN_00015388/0001532c) with dispatch kinds, binds a
 * payload (FUN_0004b520), and builds the message pipe (FUN_00017b88).
 * Confidence: low (structural summary).
 * Notes: helpers FUN_0036b7f8/00015388/0001532c/0004b520/0036b270/
 *   0036b118/00017b88/0004b664; globals 0x6ad3a8/DAT_004bb180/0x65a220/
 *   FUN_0001f38c. */
void sk_tb_pipe_config(void *a, uint8_t kind, void *b, uint8_t kind2)
{
    unsigned long n1, n2;
    *(unsigned long *)0 = 0;
    *(unsigned long *)0 = 0;
    FUN_0036b7f8(0, 0);
    if (kind < 2) {
        n1 = FUN_00015388((kind == 0) ? 3 : 0xd, a, 0);
    } else if (kind == 2) {
        n1 = FUN_00015388(3, a, 1);
    } else if (kind == 3) {
        n1 = FUN_00015388(3, a, 8);
    } else {
        n1 = FUN_0001532c(1, 0);
    }
    if (kind2 < 2) {
        n2 = FUN_00015388((kind2 == 0) ? 3 : 0xd, b, 0);
    } else if (kind2 == 2) {
        n2 = FUN_00015388(3, b, 1);
    } else if (kind2 == 3) {
        n2 = FUN_00015388(3, b, 8);
    } else {
        n2 = FUN_0001532c(1, 0);
    }
    unsigned long cfg[5] = {0x6ad3a8, DAT_004bb180, (unsigned long)FUN_0001f38c, 0x65a220, 0};
    unsigned long meta = FUN_0004b520(&cfg);
    FUN_0036b270(0);
    FUN_0036b118(0);
    unsigned long pipe = FUN_00017b88((void *)(n1),(void *)( n2),(void *)( meta));
    FUN_0004b664(meta);
    *(unsigned long *)0 = pipe;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f38c @ 0x0001f38c   (est. sk_tb_forward_handler)
 * Ghidra: uint FUN_0001f38c(long data, undefined8 a, undefined8 b, undefined8 c)
 * Tightbeam forwarding handler: dispatches the bound method (offset 0x20)
 * with its argument (offset 0x28), returning the low bit of the result.
 * Confidence: medium
 * Notes: method dispatch offsets 0x20/0x28; helpers FUN_0036b270/0036b118. */
unsigned int sk_tb_forward_handler(void *data, void *a, void *b, void *c)
{
    unsigned long (*method)(void *, void *, void *) = *(unsigned long (**)(void *, void *, void *))((char *)data + 0x20);
    void *arg = *(void **)((char *)data + 0x28);
    FUN_0036b270((unsigned long)(arg));
    unsigned int r = method(a, b, c);
    FUN_0036b118(arg);
    return r & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f414 @ 0x0001f414   (est. sk_tb_conn_alloc)
 * Ghidra: long FUN_0001f414(undefined8 a, undefined8 b)
 * Allocates a tightbeam connection (FUN_0036a940), configures its handler,
 * and builds a one-way message pipe (FUN_00017b7c). Returns the connection.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_0036a940/0036b7f8/0004b520/0036b270/0036b118/
 *   00017b7c/0004b664; globals 0x6ad3a8/DAT_004bb180/0x65a248/FUN_0001f38c. */
long sk_tb_conn_alloc(void *a, void *b)
{
    long c = FUN_0036a940();
    *(unsigned long *)(c + 0x10) = 0;
    *(unsigned long *)(c + 0x20) = 0;
    FUN_0036b7f8((void *)(c + 0x18), 0);
    unsigned long cfg[5] = {0x6ad3a8, DAT_004bb180, (unsigned long)FUN_0001f38c, 0x65a248, (unsigned long)c};
    unsigned long meta = FUN_0004b520(&cfg);
    FUN_0036b270(c);
    FUN_0036b118((void *)(c));
    unsigned long pipe = FUN_00017b7c(a, b,(void *)( meta));
    FUN_0004b664(meta);
    *(unsigned long *)(c + 0x10) = pipe;
    return c;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f514 @ 0x0001f514   (est. sk_tb_conn_alloc_single)
 * Ghidra: void FUN_0001f514(undefined8 a, undefined8 b)
 * Single-ended tightbeam connection allocator.
 * Confidence: low (structural summary).
 * Notes: mirrors FUN_0001f414 with a different table tag (0x65a270). */
void sk_tb_conn_alloc_single(void *a, void *b)
{
    unsigned long cfg[5] = {0x6ad3a8, DAT_004bb180, (unsigned long)FUN_0001f38c, 0x65a270, 0};
    unsigned long meta = FUN_0004b520(&cfg);
    FUN_0036b270(0);
    FUN_0036b118(0);
    unsigned long pipe = FUN_00017b7c(a, b,(void *)( meta));
    FUN_0004b664(meta);
    *(unsigned long *)0 = pipe;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f600 @ 0x0001f600   (est. sk_tb_pipe_alloc5)
 * Ghidra: undefined8 FUN_0001f600(undefined8 a, undefined8 b, undefined8 c, undefined8 d, undefined8 e)
 * Allocates a 5-argument tightbeam pipe via FUN_0001f670.
 * Confidence: medium
 * Notes: helper FUN_0001f670. */
unsigned long sk_tb_pipe_alloc5(void *a, void *b, void *c, void *d, void *e)
{
    unsigned long p = FUN_0036a940();
    FUN_0001f670(a,(unsigned long)( b), c,(unsigned long)( d), e);
    return p;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f670 @ 0x0001f670   (est. sk_tb_pipe_config5)
 * Ghidra: void FUN_0001f670(undefined8 a, byte kind, undefined8 b, byte kind2, undefined8 c)
 * Configures a bidirectional tightbeam pipe with an extra argument,
 * building the message pipe via FUN_00017a08.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_00015388/0001532c/0004b520/0036b270/0036b118/
 *   00017a08/0004b664; table LAB_0065a298. */
void sk_tb_pipe_config5(void *a, uint8_t kind, void *b, uint8_t kind2, void *c)
{
    unsigned long n1, n2;
    FUN_0036b7f8(0, 0);
    if (kind < 2) n1 = FUN_00015388((kind == 0) ? 3 : 0xd, a, 0);
    else if (kind == 2) n1 = FUN_00015388(3, a, 1);
    else if (kind == 3) n1 = FUN_00015388(3, a, 8);
    else n1 = FUN_0001532c(1, 0);
    if (kind2 < 2) n2 = FUN_00015388((kind2 == 0) ? 3 : 0xd, b, 0);
    else if (kind2 == 2) n2 = FUN_00015388(3, b, 1);
    else if (kind2 == 3) n2 = FUN_00015388(3, b, 8);
    else n2 = FUN_0001532c(1, 0);
    unsigned long cfg[5] = {0x6ad3a8, DAT_004bb180, (unsigned long)FUN_0001f38c, 0x65a298, 0};
    unsigned long meta = FUN_0004b520(&cfg);
    FUN_0036b270(0);
    FUN_0036b118(0);
    unsigned long pipe = FUN_00017a08((void *)(n1),(void *)( n2), c,(void *)( meta));
    FUN_0004b664(meta);
    *(unsigned long *)0 = pipe;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f834 @ 0x0001f834   (est. sk_tb_forward_send)
 * Ghidra: uint FUN_0001f834(undefined8 a, undefined8 b, undefined8 c, ulong conn)
 * Sends a message on a tightbeam forwarding connection: reads the connection
 * reader, marshals the message words (FUN_000259c0/0001fd9c), and dispatches
 * the forwarding handler (FUN_0001fde8). Returns the low bit of the result.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_0036a1a0/0036b8b0/000259c0/0001fd9c/0001fde8/
 *   0036b270/0036b118; string s_Tightbeam_ForwardingConnection_s_005acc20,
 *   s_Fatal_error_005accd0; globals 0x65a210/0x659938. */
unsigned int sk_tb_forward_send(void *a, void *b, void *c, unsigned long conn)
{
    unsigned char buf[0x40];
    FUN_0036a1a0((void *)(conn + 0x18), buf, 0, 0);
    unsigned long *rdr = (unsigned long *)FUN_0036b8b0(conn + 0x18);
    if (rdr != 0) {
        unsigned long arg = *(unsigned long *)(conn + 0x20);
        FUN_000259c0(buf,(unsigned long)( b));
        unsigned long msg = FUN_0001fd9c(buf);
        unsigned long (*handler)(void *, void *, void *) = (void *)FUN_0001fde8(arg);
        unsigned long v = FUN_0036b270(conn);
        unsigned int r = handler(v, buf, *rdr, arg);
        FUN_0036b118(rdr);
        return r & 1;
    }
    FUN_001afa84("Fatal error", 0xb, 2, 0xd000000000000051, 0x80000000005acc30,
                 "Tightbeam ForwardingConnection.swift", 0x24, 2, 0x54, 0);
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f978 @ 0x0001f978   (est. sk_tb_forward_send_flag)
 * Ghidra: uint FUN_0001f978(void)
 * Returns FUN_0001f834() & 1.
 * Confidence: medium
 * Notes: helper FUN_0001f834. */
unsigned int sk_tb_forward_send_flag(void)
{
    return FUN_0001f834() & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f97c @ 0x0001f97c   (est. sk_tb_forward_send_flag2)
 * Ghidra: uint FUN_0001f97c(void)
 * Returns FUN_0001f834() & 1 (second variant).
 * Confidence: medium
 * Notes: helper FUN_0001f834. */
unsigned int sk_tb_forward_send_flag2(void)
{
    return FUN_0001f834() & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0001f998 @ 0x0001f998   (est. sk_tb_pipe_alloc6)
 * Ghidra: undefined8 FUN_0001f998(undefined8 a, undefined8 b, undefined8 c, undefined8 d, undefined8 e, undefined8 f)
 * Allocates a 6-argument tightbeam pipe via FUN_0001fa18.
 * Confidence: medium
 * Notes: helper FUN_0001fa18. */
unsigned long sk_tb_pipe_alloc6(void *a, void *b, void *c, void *d, void *e, void *f)
{
    unsigned long p = FUN_0036a940();
    FUN_0001fa18(a,(unsigned long)( b), c,(unsigned long)( d), e, f);
    return p;
}

/*--------------------------------------------------------------------*/
/* FUN_0001fa18 @ 0x0001fa18   (est. sk_tb_pipe_config6)
 * Ghidra: void FUN_0001fa18(undefined8 a, byte kind, undefined8 b, byte kind2, undefined8 c, undefined8 d)
 * Configures a 6-argument bidirectional tightbeam pipe, building the
 * message pipe via FUN_00017b88 with two extra payload arguments.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_00015388/0001532c/0004b520/0036a940/0036b270/
 *   0036b118/00017b88/0004b664; globals 0x6ad3a8/DAT_004bb180/0x65a2d0/
 *   0x65a2e8. */
void sk_tb_pipe_config6(void *a, uint8_t kind, void *b, uint8_t kind2, void *c, void *d)
{
    unsigned long n1, n2;
    FUN_0036b7f8(0, 0);
    if (kind < 2) n1 = FUN_00015388((kind == 0) ? 3 : 0xd, a, 0);
    else if (kind == 2) n1 = FUN_00015388(3, a, 1);
    else if (kind == 3) n1 = FUN_00015388(3, a, 8);
    else n1 = FUN_0001532c(1, 0);
    if (kind2 < 2) n2 = FUN_00015388((kind2 == 0) ? 3 : 0xd, b, 0);
    else if (kind2 == 2) n2 = FUN_00015388(3, b, 1);
    else if (kind2 == 3) n2 = FUN_00015388(3, b, 8);
    else n2 = FUN_0001532c(1, 0);
    unsigned long cfg[5] = {0x6ad3a8, DAT_004bb180, (unsigned long)FUN_0001f38c, 0x65a2e8, 0};
    unsigned long meta = FUN_0004b520(&cfg);
    FUN_0036b270(0);
    FUN_0036b270((unsigned long)(d));
    FUN_0036b118(0);
    unsigned long pipe = FUN_00017b88((void *)(n1),(void *)( n2),(void *)( meta));
    FUN_0036b118(d);
    FUN_0004b664(meta);
    *(unsigned long *)0 = pipe;
}

/*--------------------------------------------------------------------*/
/* FUN_0001fc10 @ 0x0001fc10   (est. sk_tb_forward_dispatch)
 * Ghidra: uint FUN_0001fc10(undefined8 a, undefined8 b, undefined8 c, ulong conn, code *handler)
 * Dispatches a tightbeam forward with an explicit handler: marshals the
 * message and calls `handler`, returning its low bit.
 * Confidence: low (structural summary).
 * Notes: helpers FUN_000259c0/0001fd9c/0036b270. */
unsigned int sk_tb_forward_dispatch(void *a, void *b, void *c, unsigned long conn, void *handler)
{
    unsigned char buf[0x40];
    FUN_000259c0((unsigned long)(buf),(unsigned long)( b));
    unsigned long msg = FUN_0001fd9c(buf);
    unsigned long v = FUN_0036b270(conn);
    return ((unsigned int (*)(unsigned long, void *))handler)(v, buf) & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_0001fca8 @ 0x0001fca8   (est. sk_tb_pipe_destroy)
 * Ghidra: void FUN_0001fca8(void)
 * Destroys a tightbeam pipe, freeing its two ends.
 * Confidence: medium
 * Notes: helpers FUN_0036b118/0036b21c. */
void sk_tb_pipe_destroy(void)
{
    FUN_0036b118(*(void **)0);
    FUN_0036b118(*(void **)0);
    FUN_0036b21c();
}

/*--------------------------------------------------------------------*/
/* FUN_0001fcac @ 0x0001fcac   (est. sk_tb_pipe_destroy2)
 * Ghidra: void FUN_0001fcac(void)
 * Second tightbeam pipe destroy variant.
 * Confidence: medium
 * Notes: helpers FUN_0036b118/0036b21c. */
void sk_tb_pipe_destroy2(void)
{
    FUN_0036b118(*(void **)0);
    FUN_0036b118(*(void **)0);
    FUN_0036b21c();
}

/*--------------------------------------------------------------------*/
/* FUN_0001fcf8 @ 0x0001fcf8   (est. sk_tb_pipe_close)
 * Ghidra: void FUN_0001fcf8(void)
 * Closes a tightbeam pipe: destroys the message pipe (FUN_00017bd4) and
 * resets the reader (FUN_0001fd28). Traps if the pipe is absent.
 * Confidence: medium
 * Notes: helpers FUN_00017bd4/0001fd28; trap 0x1fd28. */
void sk_tb_pipe_close(void)
{
    if (*(long *)0 != 0) {
        FUN_00017bd4();
        FUN_0001fd28(0);
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x1fd28) */
}

/*--------------------------------------------------------------------*/
/* FUN_0001fcfc @ 0x0001fcfc   (est. sk_tb_pipe_close2)
 * Ghidra: void FUN_0001fcfc(void)
 * Second tightbeam pipe close variant.
 * Confidence: medium
 * Notes: helpers FUN_00017bd4/0001fd28; trap 0x1fd28. */
void sk_tb_pipe_close2(void)
{
    sk_tb_pipe_close();
}

/*--------------------------------------------------------------------*/
/* FUN_0001fd28 @ 0x0001fd28   (est. sk_tb_reader_reset)
 * Ghidra: undefined8 FUN_0001fd28(undefined8 reader)
 * Resets a tightbeam reader (FUN_0036b8c0), returning the reader pointer.
 * Confidence: medium
 * Notes: helper FUN_0036b8c0. */
unsigned long sk_tb_reader_reset(void *reader)
{
    FUN_0036b8c0();
    return (unsigned long)reader;
}

/*--------------------------------------------------------------------*/
/* FUN_0001fd50 @ 0x0001fd50   (est. sk_tb_conn_close)
 * Ghidra: void FUN_0001fd50(void)
 * Closes a tightbeam connection: destroys the pipe and resets the reader.
 * Confidence: medium
 * Notes: helpers FUN_00017bd4/0001fd28/0036b6ac; trap 0x1fd8c. */
void sk_tb_conn_close(void)
{
    if (*(long *)0 != 0) {
        FUN_00017bd4();
        FUN_0001fd28(0);
        FUN_0036b6ac();
        return;
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x1fd8c) */
}

/*--------------------------------------------------------------------*/
/* FUN_0001fd54 @ 0x0001fd54   (est. sk_tb_conn_close2)
 * Ghidra: void FUN_0001fd54(void)
 * Second tightbeam connection close variant.
 * Confidence: medium
 * Notes: helpers FUN_00017bd4/0001fd28/0036b6ac; trap 0x1fd8c. */
void sk_tb_conn_close2(void)
{
    sk_tb_conn_close();
}

/*--------------------------------------------------------------------*/
/* FUN_0001fd9c @ 0x0001fd9c   (est. sk_tb_frame_prepare)
 * Ghidra: undefined8 FUN_0001fd9c(undefined8 frame)
 * Prepares a tightbeam frame by invoking the codec (DAT_0065ac38 + 8).
 * Confidence: medium
 * Notes: codec dispatch DAT_0065ac38. */
unsigned long sk_tb_frame_prepare(void *frame)
{
    ((void (*)(void))**(void ***)(DAT_0065ac38 + 8))();
    return (unsigned long)frame;
}

/*--------------------------------------------------------------------*/
/* FUN_0001fde8 @ 0x0001fde8   (est. sk_tb_handler_resolve)
 * Ghidra: long FUN_0001fde8(ulong entry)
 * Resolves a tightbeam handler: dereferences a tagged pointer (low bit set)
 * and returns the handler address at entry+4 (relative).
 * Confidence: medium
 * Notes: tagged-pointer / relative-offset resolution. */
long sk_tb_handler_resolve(unsigned long entry)
{
    if ((entry & 1) != 0) entry = *(unsigned long *)(entry & 0xfffffffffffffffe);
    return (long)(entry + 4) + (long)*(int *)(entry + 4);
}

/*--------------------------------------------------------------------*/
/* FUN_0001fe3c @ 0x0001fe3c   (est. sk_tb_status_mask)
 * Ghidra: ulong FUN_0001fe3c(void)
 * Returns FUN_0001fee8() & 0xffffffff00ffffff.
 * Confidence: medium
 * Notes: helper FUN_0001fee8. */
unsigned long sk_tb_status_mask(void)
{
    return FUN_0001fee8() & 0xffffffff00ffffff;
}

/*--------------------------------------------------------------------*/
/* FUN_0001fee8 @ 0x0001fee8   (est. sk_tb_status_encode)
 * Ghidra: undefined1 [16] FUN_0001fee8(ulong status)
 * Encodes a tightbeam status word: maps the low byte (0x23 -> 0, 0x21 ->
 * 2, 0x20 -> {1,0x100}) into a {value, flags} pair.
 * Confidence: medium
 * Notes: status encoding table. */
unsigned long sk_tb_status_encode(unsigned long status)
{
    unsigned int b = (unsigned int)status & 0xff;
    unsigned long v = (b != 0x23) ? (status & 0xff) : 0;
    unsigned long f = (b != 0x23) ? 0 : 0x100;
    if (b == 0x21) { v = 2; f = 0x100; }
    unsigned long v2 = (b != 0x20) ? v : 1;
    unsigned long f2 = (b != 0x20) ? f : 0x100;
    return (status >> 0x30) | ((status & 0xff00) << 8 | (status >> 0x10) << 0x20 | v2 | f2);
}

/*--------------------------------------------------------------------*/
/* FUN_0001003c @ 0x0001003c   (est. sk_guard_size_config)
 * Ghidra: void FUN_0001003c(long config, ulong size, int flag, undefined1 *out)
 * Computes allocator guard/slack sizes for a requested block size. For small
 * blocks (< 0x8001, flag set, guard-enable bit at config+0x260) it reads two
 * per-class guard byte fields (config+0x262/0x264 and config+0x263/0x265,
 * the latter chosen when size > 0x1000), rounds size up to a 16 KiB multiple,
 * and reports kind 1 with a page-count guard (size >> 14). For larger blocks
 * it checks a second guard-enable bit (config+0x266): multiplies size by the
 * guard multiplier (config+0x267) and, if the product exceeds 16 MiB, scales
 * down the three guard bytes by the top byte of the product, logging
 * "Reducing guards for block size". Writes a 5-byte record {kind, g1, g2, g3,
 * page_count} to out.
 * Confidence: medium
 * Notes: references string s_Reducing_guards_for_block_size___005aa72d via
 *   sk_log (FUN_000117e8). */
void sk_guard_size_config(void *config, unsigned long size, int flag, uint8_t *out)
{
    uint8_t g1, g2, g3, page_count;
    uint8_t kind;

    if ((size < 0x8001) && (flag != 0) &&
        ((*(uint8_t *)((char *)config + 0x260) & 1) != 0)) {
        unsigned long off_a = 0x262, off_b = 0x263;
        if (0x1000 < size) { off_a = 0x264; off_b = 0x265; }
        g3 = *(uint8_t *)((char *)config + off_a);
        if ((size & 0x3fff) != 0) size += 0x4000;
        page_count = (uint8_t)(size >> 0xe);
        g2 = *(uint8_t *)((char *)config + off_b);
        g1 = 0;
        kind = 1;
    } else {
        g3 = 0;
        page_count = 0;
        if ((size - 0x8001) >> 0xf < 0x3f) {
            kind = 0;
            g2 = g3;
            g1 = g3;
            if ((*(uint8_t *)((char *)config + 0x266) & 1) != 0) {
                g3 = *(uint8_t *)((char *)config + 0x267);
                g2 = *(uint8_t *)((char *)config + 0x268);
                g1 = *(uint8_t *)((char *)config + 0x26b);
                size = size * g3;
                if (size < 0x1000001) {
                    page_count = 0;
                    kind = 2;
                } else {
                    uint8_t top = (uint8_t)((size >> 0x18) & 0xff);
                    uint8_t zero = 0;
                    if ((size & 0xff000000) != 0) zero = (uint8_t)(g3 / top);
                    g3 = zero;
                    zero = 0;
                    if ((size & 0xff000000) != 0) zero = (uint8_t)(g2 / top);
                    g2 = zero;
                    zero = 0;
                    if ((size & 0xff000000) != 0) zero = (uint8_t)(g1 / top);
                    g1 = zero;
                    sk_log(4, "Reducing guards for block size %lx");
                    page_count = 0;
                    kind = 2;
                }
            }
        } else {
            g1 = 0; g2 = 0; g3 = 0;
            kind = 0;
        }
    }
    out[0] = kind;
    out[1] = g3;
    out[2] = g2;
    out[3] = g1;
    out[4] = page_count;
}

/*--------------------------------------------------------------------*/
/* FUN_0001018c @ 0x0001018c   (est. sk_lock_acquire_failed_panic)
 * Ghidra: void FUN_0001018c(void)
 * Panic wrapper: logs "Failed to acquire lock %p" at level 0x40 and invokes
 * the boot failure handler (FUN_00011824). Called when a lock cannot be
 * acquired during early boot.
 * Confidence: medium (string-matched "Failed to acquire lock").
 * Notes: string s_Failed_to_acquire_lock__p__005a9a23. */
void sk_lock_acquire_failed_panic(void)
{
    sk_boot_fail(0x40, 0, "Failed to acquire lock %p");  /* FUN_00011824 */
}

/*--------------------------------------------------------------------*/
/* FUN_000101a0 @ 0x000101a0   (est. sk_heap_alloc_checked)
 * Ghidra: void FUN_000101a0(ulong size, undefined8 param_2)
 * Allocates `size` bytes from the heap zone (DAT_0064c060), dispatching to
 * the zone's allocator method (offset 0x18 for zone version < 0x10, offset
 * 0xa0 otherwise). Validates that the returned pointer range does not wrap:
 * if size + returned base overflows, it traps (SoftwareBreakpoint 0x5519).
 * Returns the allocated pointer.
 * Confidence: medium
 * Notes: zone dispatch object DAT_0064c060; overflow trap at 0x10244. */
void *sk_heap_alloc_checked(unsigned long size, void *arg)
{
    void *heap = *(void **)0x64c060;  /* DAT_0064c060 */
    unsigned long base;
    unsigned long end;

    if (*(unsigned int *)((char *)heap + 0x68) < 0x10) {
        base = ((unsigned long (*)(void *, unsigned long))
                **(void ***)((char *)heap + 0x18))(heap, size);
    } else {
        base = ((unsigned long (*)(void *, unsigned long, void *))
                **(void ***)((char *)heap + 0xa0))(heap, size, arg);
    }
    end = (base != 0) ? base + size : 0;
    if (base <= end && (base == 0 || size <= end - base) &&
        base <= end && (base == 0 || size <= end - base)) {
        return (void *)base;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x10244) */
}

/*--------------------------------------------------------------------*/
/* FUN_00010244 @ 0x00010244   (est. sk_heap_calloc)
 * Ghidra: void FUN_00010244(long count, long size, undefined8 param_3)
 * Allocates and zero-fills `count * size` bytes from the heap zone via the
 * zone's calloc method (offset 0x20 / 0xa8). Validates that the product and
 * returned range do not wrap; on overflow it traps.
 * Confidence: medium
 * Notes: zone DAT_0064c060; overflow trap 0x102f4. */
void *sk_heap_calloc(unsigned long count, unsigned long size, void *arg)
{
    void *heap = *(void **)0x64c060;  /* DAT_0064c060 */
    unsigned long total;
    unsigned long base, end;

    if (*(unsigned int *)((char *)heap + 0x68) < 0x10) {
        if ((char *)heap + 200 < (char *)heap) __builtin_trap();
        base = ((unsigned long (*)(void *, unsigned long, unsigned long))
                **(void ***)((char *)heap + 0x20))(heap, count, size);
    } else {
        if ((char *)heap + 200 < (char *)heap) __builtin_trap();
        base = ((unsigned long (*)(void *, unsigned long, unsigned long, void *))
                **(void ***)((char *)heap + 0xa8))(heap, count, size, arg);
    }
    total = size * count;
    end = (base != 0) ? base + total : 0;
    if (base <= end && (base == 0 || (total < end - base || total - (end - base) == 0))) {
        return (void *)base;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x102f4) */
}

/*--------------------------------------------------------------------*/
/* FUN_000102f4 @ 0x000102f4   (est. sk_heap_alloc_or_error)
 * Ghidra: ulong FUN_000102f4(long count, ulong size, undefined8 param_3)
 * Allocates `count * size` bytes; returns the base pointer, or 0 with kernel
 * error 0xc (ENOMEM) on failure. Handles count==0/size==0 by allocating
 * `size` alone; for a nonzero count it first looks up the object class
 * (FUN_00011cac) to pick a sized allocator method (offset 0x38 / 0xb0), and
 * falls back to the general allocator (FUN_000125b4). Traps on overflow.
 * Confidence: medium
 * Notes: zone DAT_0064c060; error slot via thunk_FUN_0006037c; trap 0x10480. */
unsigned long sk_heap_alloc_or_error(unsigned long count, unsigned long size, void *arg)
{
    void *zone;
    unsigned long base, end;
    unsigned int *err;

    if (count == 0 || size == 0) {
        base = (unsigned long)sk_zone_alloc_n(sk_zone0(), size);  /* FUN_00012060 */
        if (base != 0) {
            if (size == 0) sk_heap_free((void *)base);
            if (base <= base + size && size <= (base + size) - base) return base;
        }
        goto overflow;
    }
    zone = (void *)sk_obj_class_lookup(count, 0, 0);  /* FUN_00011cac */
    if (zone != 0) {
        if (*(unsigned int *)((char *)zone + 0x68) < 0x10) {
            if ((char *)zone + 200 < (char *)zone) goto overflow;
            base = ((unsigned long (*)(void *, unsigned long, unsigned long))
                    **(void ***)((char *)zone + 0x38))(zone, count, size);
        } else {
            if ((char *)zone + 200 < (char *)zone) goto overflow;
            base = ((unsigned long (*)(void *, unsigned long, unsigned long, void *))
                    **(void ***)((char *)zone + 0xb0))(zone, count, size, arg);
        }
        if (base != 0) {
            if (size <= base + size) return base;
            goto overflow;
        }
        err = sk_error_slot();
        *err = 0xc;
        return 0;
    }
    base = sk_heap_alloc((void *)count, size);  /* FUN_000125b4 */
    if (base != 0 && size <= base + size) return base;
overflow:
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x10480) */
}

/*--------------------------------------------------------------------*/
/* FUN_00010480 @ 0x00010480   (est. sk_heap_aligned_alloc)
 * Ghidra: void FUN_00010480(ulong align, ulong size, undefined8 param_3)
 * Aligned allocation: when align > 7 and the heap supports it (version >=
 * 0x10, power-of-two alignment, size aligned), uses the zone's aligned-alloc
 * method (offset 0xb8); otherwise falls back to FUN_00010584. Sets error
 * 0xc on failure. Traps on range wrap.
 * Confidence: medium
 * Notes: zone DAT_0064c060; trap 0x10584. */
void *sk_heap_aligned_alloc(unsigned long align, unsigned long size, void *arg)
{
    void *heap;
    unsigned long base, end;
    unsigned int *err;

    if (align > 7) {
        heap = *(void **)0x64c060;  /* DAT_0064c060 */
        if (0xf < *(unsigned int *)((char *)heap + 0x68) &&
            (align & (align - 1)) == 0 && (size & (align - 1)) == 0) {
            if ((char *)heap <= (char *)heap + 200) {
                base = ((unsigned long (*)(void *, unsigned long, unsigned long))
                        **(void ***)((char *)heap + 0xb8))(heap, align, size);
                end = base + size;
                if (base == 0) {
                    end = 0;
                    err = sk_error_slot();
                    *err = 0xc;
                }
                if (base <= end && (base == 0 || size <= end - base)) {
                    return (void *)base;
                }
            }
            __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x10584) */
        }
    }
    base = (unsigned long)sk_alloc_aligned_save(align, size, (unsigned long)arg);  /* FUN_00010584 */
    end = (base != 0) ? base + size : 0;
    if (base <= end && (base == 0 || size <= end - base)) {
        return (void *)base;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x10584) */
}

/*--------------------------------------------------------------------*/
/* FUN_00010584 @ 0x00010584   (est. sk_alloc_aligned_save)
 * Ghidra: void FUN_00010584(undefined8 param_1, ulong size, ulong flags)
 * Allocation that saves/restores the per-CPU "no-preempt" slot (tpidr_el0
 * word 9) around the heap allocation (FUN_00012218, flags=3), enforcing
 * flags >= 1. Traps on range wrap.
 * Confidence: medium
 * Notes: per-CPU slot tpidr_el0+9; zone DAT_0064c060; trap 0x1062c. */
void *sk_alloc_aligned_save(void *param_1, unsigned long size, unsigned long flags)
{
    unsigned long saved, base, end;

    saved = 0;
    if (flags < 2) flags = 1;
    base = sk_heap_alloc_mode(*(void **)0x64c060, param_1, size, 3, 0);  /* FUN_00012218 */
    end = (base != 0) ? base + size : 0;
    if (base <= end && (base == 0 || size <= end - base)) {
        return (void *)base;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x1062c) */
}

/*--------------------------------------------------------------------*/
/* FUN_0001062c @ 0x0001062c   (est. sk_heap_aligned_alloc_variant)
 * Ghidra: undefined8 FUN_0001062c(long *out, ulong size, undefined8 param_3, ulong flags)
 * Aligned-allocation variant storing the result through *out: for size > 7
 * with a compatible heap it uses the zone's aligned-alloc method (offset
 * 0xb8); otherwise it routes through the save/restore path (FUN_000127c0).
 * Returns 0 on success or 0xc on allocation failure. Traps on overflow.
 * Confidence: medium
 * Notes: zone DAT_0064c060; trap 0x106c4 / 0x1071c. */
unsigned long sk_heap_aligned_alloc_variant(void **out, unsigned long size, void *arg, unsigned long flags)
{
    void *heap;
    unsigned long saved;
    void *res;

    if (size > 7) {
        heap = *(void **)0x64c060;  /* DAT_0064c060 */
        if (0xf < *(unsigned int *)((char *)heap + 0x68) && (size & (size - 1)) == 0) {
            if ((char *)heap <= (char *)heap + 200) {
                res = ((void *(*)(void *))
                       **(void ***)((char *)heap + 0xb8))(heap);
                if (res == 0) return 0xc;
                *out = res;
                return 0;
            }
            __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x106c4) */
        }
    }
    saved = 0;
    if (flags < 2) flags = 1;
    res = sk_alloc_out(out);  /* FUN_000127c0 */
    return (unsigned long)res;
}

/*--------------------------------------------------------------------*/
/* FUN_0001071c @ 0x0001071c   (est. sk_buddy_init)
 * Ghidra: void FUN_0001071c(void)
 * Initializes the buddy page allocator. Allocates a 1 MiB arena
 * (FUN_00011b18, guard 0xa00/0x200), clears the free lists, sets the 
 * per-size-class free-list heads (sizes 3..0xe), and installs the base into
 * DAT_006adfd8. Panics "BUG IN LIBMALLOC" (FUN_001150e0) on arena failure.
 * Confidence: medium
 * Notes: strings s_BUG_IN_LIBMALLOC___llu___failed_t_005aa76c; globals
 *   DAT_006adfd8/006adfe0. */
void sk_buddy_init(void)
{
    unsigned long guard = 0xa00;
    unsigned long hint = 0;
    void *arena;
    long *p, v;

    if (sk_buddy_flags == 0) guard = 0x200;
    arena = sk_arena_alloc(0x100000, (void *)0, guard, 1, &hint);  /* FUN_00011b18 */
    if (arena == 0) {
        sk_panic("BUG IN LIBMALLOC: failed to allocate arena");  /* FUN_001150e0 */
    }
    sk_mem_clear((void *)arena, 0x8000, 2, 0x40, &hint);  /* FUN_00011bf4 */
    ((unsigned long *)arena)[0x1d] = hint;
    ((unsigned long *)arena)[0x1c] = 0;
    *(unsigned long *)arena = 0;
    ((unsigned long *)arena)[1] = 0;
    ((unsigned long *)arena)[0x1f] = 0x8000000000000000ull;
    /* size-class free-list heads: pair {next,prev} for sizes 3..0xd */
    p = (long *)arena + 7;
    v = 3;
    do {
        p[-1] = v;
        *p = v;
        p += 2;
        v += 1;
    } while (v != 0xe);
    ((unsigned long *)arena)[0x20] |= 1;
    sk_buddy_base = arena;
}

/*--------------------------------------------------------------------*/
/* FUN_00010830 @ 0x00010830   (est. sk_buddy_find_free)
 * Ghidra: long FUN_00010830(ulong key)
 * Searches the buddy allocator's free bitmap (DAT_006adfd8 + 0x100) for the
 * next free region at or after `key`, using the leading-zero-count / bit
 * reversal helpers (LZCOUNT). Returns the free region's 16-byte slot index
 * shifted left 4, or 0 if the key is out of the arena or no free region.
 * Confidence: medium
 * Notes: buddy bitmap + free lists at DAT_006adfd8. */
long sk_buddy_find_free(unsigned long key)
{
    unsigned long k = key & 0xf0ffffffffffffffull;
    unsigned long idx, bits, tmp;
    long *fl;

    if (sk_buddy_base == 0 || k < (unsigned long)sk_buddy_base + 0x8000 ||
        (key & 0xf) != 0 || (unsigned long)sk_buddy_base + 0x100000 <= k) {
        return 0;
    }
    idx = (k - ((unsigned long)sk_buddy_base + 0x8000)) >> 4;
    if ((*(unsigned long *)((char *)sk_buddy_base + 0x100 +
                            ((idx >> 2) & 0x3ffffffffffffff0)) &
         (1ull << (idx & 0x3f)) &
         *(unsigned long *)((char *)sk_buddy_base + 0x100 +
                            (((idx >> 2) & 0x3ffffffffffffff8) | 8))) == 0) {
        return 0;
    }
    idx = idx + 1;
    bits = *(unsigned long *)((char *)sk_buddy_base + 0x100 +
                              (((idx >> 5) & 0x7fffffffffffffe) * 8)) >> (idx & 0x3f);
    if (bits == 0) {
        tmp = idx & 0x3f;
        fl = (long *)((char *)sk_buddy_base + 0x100 + ((idx >> 5) & 0x7fffffffffffffe) * 8);
        bits = *(unsigned long *)((char *)fl + 0x10);
        if (bits != 0) {
            bits = bit_reverse64(bits);
            return (LZCOUNT(bits >> 0x20 | bits << 0x20) - tmp + 0x41) << 4;
        }
        fl = (tmp < 0x31) ? 0 : (long *)((char *)fl + 0x18);
        idx = (unsigned long)((unsigned int)(((unsigned long)fl << 1) << (tmp ^ 0x3f)) |
                              (unsigned int)(*(unsigned long *)((char *)sk_buddy_base + 0x100 +
                                  (((idx >> 5) << 3) | 8)) >> tmp)) & 0xffff;
    } else {
        bits = bit_reverse64(bits);
        bits = LZCOUNT(bits >> 0x20 | bits << 0x20);
    }
    return (bits + 1) << 4;
}

/*--------------------------------------------------------------------*/
/* FUN_00010934 @ 0x00010934   (est. sk_buddy_alloc)
 * Ghidra: long * FUN_00010934(ulong size)
 * The buddy page allocator: allocates a 16-byte-granular region of `size`
 * bytes (rounded to a 16-byte unit) from the buddy arena (DAT_006adfd8).
 * Takes the arena lock (FUN_0011582c), walks the per-size free lists, and
 * on miss grows the arena high-water mark (DAT_006adfd8+0x18), zero-filling
 * new pages (FUN_00011bf4) and maintaining the free bitmap at +0x100.
 * Releases the lock (FUN_00115894) before returning the block, or 0 if the
 * request exceeds arena capacity. Panics on lock acquire/release failure.
 * Confidence: medium
 * Notes: strings s_Failed_to_acquire_lock__p__005a9a23,
 *   s_Failed_to_release_lock__p__005a9a3f. */
void *sk_buddy_alloc(unsigned long size)
{
    unsigned long base = (unsigned long)sk_buddy_base;
    unsigned long units;
    void *result;

    if (size < 0x4001) {
        units = (size + 0xf) >> 4;
        if (size == 0) units = 1;
        if (sk_buddy_lock(base) != 0) {   /* FUN_0011582c */
            sk_boot_fail(0x40, 0, "Failed to acquire lock %p");
        }
        /* grow the arena high-water mark */
        unsigned long hwm = *(unsigned long *)(base + 0x18);
        if (units < 0xf800 - hwm) {
            unsigned long newhwm = hwm + units;
            *(unsigned long *)(base + 0x18) = newhwm;
            result = (void *)(base + 0x8000 + hwm * 0x10);
            if (*(unsigned long *)(base + 0x20) < newhwm) {
                unsigned long from = ((base + 0x8000 + *(unsigned long *)(base + 0x20) * 0x10) + 0x3fff) & ~0x3fffull;
                unsigned long to = ((unsigned long)result + size + 0x3fff) & ~0x3fffull;
                if (to != from) {
                    sk_mem_clear((void *)from, to - from, 2, 0x40, (void *)(base + 0xe0));  /* FUN_00011bf4 */
                }
                *(unsigned long *)(base + 0x20) = *(unsigned long *)(base + 0x18);
            }
        } else {
            result = 0;
        }
        if (sk_buddy_unlock(base) != 0) {  /* FUN_00115894 */
            sk_boot_fail(0x40, 0, "Failed to release lock %p");
        }
        return result;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00010d84 @ 0x00010d84   (est. sk_buddy_free_split)
 * Ghidra: void FUN_00010d84(long arena, long idx, undefined8 units)
 * Buddy free helper: computes the size class for `units` free units and
 * links the region (arena + idx*0x10 + 0x8000) into the corresponding
 * per-class free list (arena + 0x30 + class*0x10), recording class+3 in the
 * region header. Used when freeing a partial region that must be split back
 * into the free lists.
 * Confidence: medium
 * Notes: arena DAT_006adfd8; helper FUN_00011430. */
void sk_buddy_free_split(unsigned long arena, long idx, unsigned long units)
{
    unsigned int cls = 0x3f - (unsigned int)LZCOUNT(units);
    long *list, *region;
    long head;

    if (9 < cls) cls = 10;
    sk_buddy_clear_range(arena, 0, 0);  /* FUN_00011430 */
    list = (long *)(arena + (unsigned long)cls * 0x10 + 0x30);
    region = (long *)(arena + idx * 0x10);
    head = *list;
    *(long *)((char *)region + 0x8000) = head;
    *(unsigned long *)((char *)region + 0x8008) = (unsigned long)cls + 3;
    *list = idx + 0x800;
    *(long *)(arena + head * 0x10 + 8) = idx + 0x800;
}

/*--------------------------------------------------------------------*/
/* FUN_00010e3c @ 0x00010e3c   (est. sk_buddy_free)
 * Ghidra: void FUN_00010e3c(ulong ptr)
 * Buddy allocator free: releases a 16-byte-aligned block previously handed
 * out by sk_buddy_alloc. Validates the pointer is inside the arena
 * (panics "BUG IN LIBMALLOC: not MFM" / "BUG IN CLIENT OF LIBMALLOC" on
 * misalignment or a double-free), clears the freed range (FUN_00117f8c),
 * takes the arena lock, co-joins the block with its neighbor(s) by walking
 * the buddy bitmap at arena+0x100, updates the free lists, the free-unit
 * count (arena+0x10) and region count (arena+0x28), and either trims the
 * arena high-water mark (arena+0x18) or re-links via sk_buddy_free_split.
 * Releases the lock; panics on lock acquire/release failure.
 * Confidence: low (structural summary).
 * Notes: strings s_BUG_IN_LIBMALLOC___llu___not_MFM_005aa79f,
 *   s_BUG_IN_CLIENT_OF_LIBMALLOC___llu_005aa838/005aa7c6/005aa800;
 *   helpers FUN_000114fc, FUN_00011884, FUN_00117f8c, FUN_0011582c,
 *   FUN_00115894. */
void sk_buddy_free(unsigned long ptr)
{
    unsigned long arena = (unsigned long)sk_buddy_base;
    unsigned long addr = ptr & 0xf0ffffffffffffffull;
    unsigned long idx, bitmap, units;

    if (arena == 0 || addr < arena + 0x8000 || arena + 0x100000 <= addr) {
        sk_panic("BUG IN LIBMALLOC: not in MFM region");  /* FUN_001150e0 */
    }
    if ((ptr & 0xf) != 0) {
        sk_panic("BUG IN CLIENT OF LIBMALLOC: misaligned free");  /* FUN_001150e0 */
    }
    idx = (addr - (arena + 0x8000)) >> 4;
    bitmap = arena + 0x100;
    if ((*(unsigned long *)(bitmap + ((idx >> 5) & 0x7fffffffffffffe) * 8) &
         *(unsigned long *)(bitmap + ((idx >> 5) | 1) * 8) &
         (1ull << (idx & 0x3f))) == 0) {
        sk_panic("BUG IN CLIENT OF LIBMALLOC: double free");  /* FUN_001150e0 */
    }
    units = buddy_run_len(bitmap, idx);
    if (sk_buddy_flags == 1) {
        dc_gva_region(ptr & ~0x3full, units);
    }
    sk_mem_clear_range(ptr, units, ~0ull);  /* FUN_00117f8c */
    if (sk_buddy_lock(arena) != 0) {  /* FUN_0011582c */
        sk_boot_fail(0x40, 0, "Failed to acquire lock %p");
    }
    *(int *)(arena + 0x10) -= (int)units;
    *(long *)(arena + 0x28) -= 1;
    if (((*(unsigned long *)(bitmap + ((((idx - 1) >> 5) << 3) | 8)) >> ((idx - 1) & 0x3f)) & 1) == 0) {
        idx -= 1;
        units = buddy_run_len(bitmap, idx) + units;
        unlink_buddy_region(arena, idx);
    }
    if (idx + units < *(unsigned long *)(arena + 0x18)) {
        unsigned long cur = idx + units;
        if ((*(unsigned long *)(bitmap + ((cur >> 5) & 0x7fffffffffffffe) * 8) &
             (1ull << (cur & 0x3f)) &
             *(unsigned long *)(bitmap + ((cur >> 5) << 3 | 8))) != 0) {
            units = buddy_run_len(bitmap, cur) + units;
            unlink_buddy_region(arena, idx);
        }
    }
    if (idx + units == *(unsigned long *)(arena + 0x18)) {
        *(unsigned long *)(bitmap + ((*(unsigned long *)(arena + 0x18) >> 2) & 0x3ffffffffffffff0)) &=
            ~(1ull << (*(unsigned long *)(arena + 0x18) & 0x3f));
        if (units < 0x40) {
            *(unsigned long *)(bitmap + ((idx >> 2) & 0x3ffffffffffffff8 | 8)) &=
                ~(1ull << (idx & 0x3f));
            *(unsigned long *)(bitmap + (((idx + units - 1) >> 2) & 0x3ffffffffffffff8 | 8)) &=
                ~(1ull << ((idx + units - 1) & 0x3f));
        } else {
            sk_buddy_clear_list(arena, 0, idx, units);  /* FUN_000114fc */
        }
        *(unsigned long *)(arena + 0x18) = idx;
    } else {
        sk_buddy_free_split(arena, idx, units);  /* FUN_00010d84 */
    }
    if (sk_buddy_unlock(arena) != 0) {  /* FUN_00115894 */
        sk_boot_fail(0x40, 0, "Failed to release lock %p");
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00011430 @ 0x00011430   (est. sk_buddy_clear_range)
 * Ghidra: void FUN_00011430(long arena, ulong idx, ulong units)
 * Clears the free-bitmap boundary markers for a region of `units` units
 * starting at unit `idx`: for a short run (< 0x40) it clears the two
 * boundary words, otherwise it delegates to sk_buddy_clear_list.
 * Confidence: medium
 * Notes: bitmap at arena+0x100; helper FUN_000114fc. */
void sk_buddy_clear_range(unsigned long arena, unsigned long idx, unsigned long units)
{
    unsigned long *bitmap = (unsigned long *)(arena + 0x100);
    unsigned long w;

    if (units < 0x40) {
        w = (idx >> 2) & 0x3ffffffffffffff8 | 8;
        bitmap[w] &= ~(1ull << (idx & 0x3f));
        w = ((idx + units - 1) >> 2) & 0x3ffffffffffffff8 | 8;
        bitmap[w] &= ~(1ull << ((idx + units - 1) & 0x3f));
        return;
    }
    sk_buddy_clear_list(arena, 0, idx, units);  /* FUN_000114fc */
}

/*--------------------------------------------------------------------*/
/* FUN_00011494 @ 0x00011494   (est. sk_buddy_is_in_arena)
 * Ghidra: bool FUN_00011494(ulong ptr)
 * Returns true if `ptr` (masked to the arena's canonical form) falls inside
 * the buddy arena's payload region, or when the arena flags word has the low
 * bit set (page-zeroing enabled) accepts the region as in-arena.
 * Confidence: medium
 * Notes: globals DAT_006adfd8/006adfe0. */
bool sk_buddy_is_in_arena(unsigned long ptr)
{
    unsigned long p = ptr & 0xf0ffffffffffffffull;
    if (sk_buddy_base == 0 || p < (unsigned long)sk_buddy_base + 0x8000) {
        return false;
    }
    return p < (unsigned long)sk_buddy_base + 0x100000;
}

/*--------------------------------------------------------------------*/
/* FUN_000114f0 @ 0x000114f0   (est. sk_buddy_base_get)
 * Ghidra: undefined8 FUN_000114f0(void)
 * Returns the buddy allocator base pointer (DAT_006adfd8).
 * Confidence: high (trivial accessor). */
void *sk_buddy_base_get(void)
{
    return sk_buddy_base;
}

/*--------------------------------------------------------------------*/
/* FUN_000114fc @ 0x000114fc   (est. sk_buddy_clear_list)
 * Ghidra: void FUN_000114fc(long arena, uint clear, ulong idx, long units)
 * Writes the free-bitmap run descriptor for a run of `units` units starting
 * at unit `idx`: stores the run length in the low 17 bits of the descriptor
 * word at bitmap + ((idx>>5)<<3|8), and splits the descriptor across the two
 * covering 64-bit words when the run crosses the 64-bit boundary. When
 * `clear` is 0 the run marker is cleared; otherwise set.
 * Confidence: medium
 * Notes: bitmap at arena+0x100. */
void sk_buddy_clear_list(unsigned long arena, unsigned int clear, unsigned long idx, long units)
{
    unsigned long *bitmap = (unsigned long *)(arena + 0x100);
    unsigned long w, end, q, r, v1, mask1, dv;

    w = ((idx >> 5) << 3) | 8;
    bitmap[w] = (bitmap[w] & ~((0x1ffffull << (idx & 0x3f)))) |
                (((unsigned long)clear & 1 | (units - 1) * 2) << (idx & 0x3f));
    if (0x2f < (idx & 0x3f)) {
        long *l2 = (long *)(bitmap + ((idx >> 5) & 0x7fffffffffffffe) * 8);
        *(unsigned long *)((char *)l2 + 0x18) =
            (*(unsigned long *)((char *)l2 + 0x18) & ~(0xffffull >> ((idx & 0x3f) ^ 0x3f))) |
            ((units - 1) & 0x7fffffffffffffffull) >> ((idx & 0x3f) ^ 0x3f);
    }
    end = (units - 1) + idx;
    q = end >> 6;
    r = end & 0x3f;
    v1 = r + 0x30;
    mask1 = 0x1ffffull << (v1 & 0x3f);
    if ((v1 & 0x40) == 0) mask1 = 0xffffull >> ((~v1) & 0x3f);
    dv = ((units - 1) + ((clear == 0) ? 0 : 0x10000)) << (v1 & 0x3f);
    if ((v1 & 0x40) == 0) dv = ((units - 1 + ((clear == 0) ? 0 : 0x10000)) >> 1) >> ((~v1) & 0x3f);
    if (r < 0x10) {
        bitmap[q * 0x10 - 8] = (bitmap[q * 0x10 - 8] & ~(0x1ffffull << (v1 & 0x3f))) |
                                (((v1 & 0x40) == 0) ? 0x1ffffull : 0);
    }
    bitmap[q * 0x10 + 8] = (bitmap[q * 0x10 + 8] & ~(mask1)) | dv;
}

/*--------------------------------------------------------------------*/
/* FUN_00011600 @ 0x00011600   (est. sk_malloc_log)
 * Ghidra: void FUN_00011600(ulong options, undefined8 flag, long msg, ...)
 * The libmalloc-style diagnostics logger (the real body behind sk_log).
 * Interprets the options word: if bit 5 is clear it emits the "*** malloc"
 * banner via FUN_00118b28; if `msg` is nonzero it prints it; writes the
 * varargs via FUN_00118c4c. If bit 8 (memory-footprint dump) is set it
 * clears a 0x32-word buffer, fills it via FUN_00115574 and prints each word.
 * If bits 6-7 request a breakpoint/sleep for debugging, it invokes
 * FUN_00011798 then sleeps (FUN_001183e0). Stack canary checked.
 * Confidence: medium
 * Notes: strings s___p__malloc__005aa86b, s_____set_a_breakpoint_in_malloc_e_005aa879,
 *   s_____sleeping_to_help_debug_005aa8b5; helpers FUN_00118b28/00118c4c/
 *   00115574/001183e0/00116d60/0011d7e8. */
void sk_malloc_log(unsigned long options, void *flag, long msg, void *a, void *b, void *c)
{
    unsigned long fb[0x32];
    long i, n;

    if (((options >> 5) & 1) == 0) {
        sk_printf_banner();       /* thunk_FUN_00060524 */
        sk_puts("*** malloc");    /* FUN_00118b28, s___p__malloc__005aa86b */
    }
    if (msg != 0) sk_puts((const char *)msg);  /* FUN_00118b28 */
    sk_vprintf(a, b);             /* FUN_00118c4c */
    if ((options >> 8 & 1) != 0) {
        for (i = 0; i < 0x32; i++) fb[i] = 0;
        n = sk_fill_debug_buffer(fb, 0x32);  /* FUN_00115574 */
        for (i = 0; i < n; i++) sk_puts_word(fb[i]);
    }
    if (((options & 0xc0) != 0) && flag != 0) {
        sk_malloc_breakpoint_check(options);  /* FUN_00011798 */
        sk_printf_banner();
        sk_puts("*** malloc");
        sk_puts("*** sleeping to help debug");  /* FUN_00118b94 */
        sk_sleep(flag);                          /* FUN_001183e0 */
    }
    if ((options >> 6 & 1) == 0) return;
    sk_abort_malloc();  /* FUN_00116d60 */
}

/*--------------------------------------------------------------------*/
/* FUN_00011798 @ 0x00011798   (est. sk_malloc_breakpoint_check)
 * Ghidra: void FUN_00011798(uint options)
 * malloc_error_break hook: if options bit 5 is clear prints the "*** malloc"
 * banner, then emits the breakpoint-hint string (DAT_005aa8b2).
 * Confidence: medium
 * Notes: strings s___p__malloc__005aa86b, DAT_005aa8b2. */
void sk_malloc_breakpoint_check(unsigned int options)
{
    if ((options >> 5 & 1) == 0) {
        sk_printf_banner();  /* thunk_FUN_00060524 */
        sk_puts("*** malloc");  /* FUN_00118b28 */
    }
    sk_puts((const char *)0x5aa8b2);  /* FUN_00118b28, DAT_005aa8b2 */
}

/*--------------------------------------------------------------------*/
/* FUN_000117e8 @ 0x000117e8   (est. sk_log)
 * Ghidra: void FUN_000117e8(undefined8 level, undefined8 fmt)
 * Diagnostic log entry point: forwards to sk_malloc_log(level, 0, 0, 0,
 * fmt, &stack). This is the boot-time logging primitive used throughout the
 * region.
 * Confidence: high (widely referenced wrapper). */
void sk_log(unsigned int level, const char *fmt, ...)
{
    sk_malloc_log(level, 0, 0, 0, (void *)fmt, &fmt);  /* FUN_00011600 */
}

/*--------------------------------------------------------------------*/
/* FUN_00011824 @ 0x00011824   (est. sk_boot_fail)
 * Ghidra: void FUN_00011824(ulong level, byte flag, undefined8 fmt)
 * Boot failure/panic reporter: picks the log options word (0x43 or 0x93)
 * from `level` (bit 6 set => 0x93) and a flag, then emits the message
 * through sk_malloc_log (FUN_00011600). Used for all boot-time fatal
 * diagnostics.
 * Confidence: medium
 * Notes: helper FUN_00011600. */
void sk_boot_fail(unsigned int level, unsigned char flag, const char *fmt, ...)
{
    unsigned int opts = 0x93;
    flag = (unsigned char)(flag ^ 1);
    if ((level & 0x100) == 0) flag = 1;
    if (((level & 0x40) == 0) & flag) opts = 0x43;
    sk_malloc_log(opts, 0, 0, 0, (void *)fmt, &fmt);  /* FUN_00011600 */
}

/*--------------------------------------------------------------------*/
/* FUN_00011884 @ 0x00011884   (est. sk_buddy_mask)
 * Ghidra: undefined8 FUN_00011884(undefined8 param_1)
 * Identity helper (returns its argument). Serves as a no-op masking step in
 * the buddy allocator free path.
 * Confidence: high (trivial). */
void *sk_buddy_mask(void *p)
{
    return p;
}

/*--------------------------------------------------------------------*/
/* FUN_000118d0 @ 0x000118d0   (est. sk_dc_gva_clear)
 * Ghidra: ulong FUN_000118d0(long base, ulong len, ulong granule)
 * Data-cache clean-by-virtual-address over a range: walks [base, base+len)
 * in `granule` steps issuing DC_GVA on each cache line (special-casing
 * 0x200-byte granules for an 8-line burst). Returns the last cleaned line.
 * Confidence: medium
 * Notes: DC_GVA cache op; caller FUN_00117fdc. */
unsigned long sk_dc_gva_clear(unsigned long base, unsigned long len, unsigned long granule)
{
    unsigned long i, n, start, end, last, q;

    if (len < granule) return 0;
    last = 0;
    n = (granule != 0) ? len / granule : 0;
    start = 0;
    end = 0;
    for (i = 0; i < n; i++) {
        unsigned long p = base + i * granule;
        last = p;
        if ((int)i != 0) last = end;
        end = p + granule;
        if ((granule & 0x1ff) == 0) {
            q = p;
            do {
                dc_gva_region(q, 0x200);
                q += 0x200;
            } while (q < end);
        } else {
            for (q = (p + 0x3f) & ~0x3full; q < (end & ~0x3full); q += 0x40) {
                dc_gva_region(q, 0x40);
            }
        }
        end = last;
    }
    return last;
}

/*--------------------------------------------------------------------*/
/* FUN_000119c0 @ 0x000119c0   (est. sk_stub_zero)
 * Ghidra: undefined8 FUN_000119c0(void)
 * Trivial stub returning 0.
 * Confidence: high (trivial). */
unsigned long sk_stub_zero(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00011a08 @ 0x00011a08   (est. sk_alloc_at)
 * Ghidra: ulong FUN_00011a08(long base, long size, undefined8 align,
 *                            uint mode, undefined8 flags, undefined8 a, undefined8 b)
 * Memory allocator for a fixed address/size: rejects "anywhere" allocations
 * (mode bit 1) by logging "Unsupported anywhere allocation", then delegates
 * to FUN_00117fdc with a mapped flags word derived from `flags` (bits 7/9/8/
 * 0x1a), traps on a zero result ("Failed to allocate memory at addr") and on
 * range wrap.
 * Confidence: medium
 * Notes: strings s_Unsupported_anywhere_allocation_a_005aa904,
 *   s_Failed_to_allocate_memory_at_add_005aa952; helpers FUN_00117fdc,
 *   thunk_FUN_0006037c; trap 0x11b18. */
unsigned long sk_alloc_at(unsigned long base, unsigned long size, void *align,
                          unsigned int mode, unsigned long flags, void *a, void *b)
{
    unsigned long mapped = ((flags >> 7 & 0x20) | (mode & 1) << 3 | (flags >> 9 & 4) |
                            (flags >> 8 & 2) | (flags >> 0x1a & 0x10)) ^ 9;
    unsigned long r;

    if (base != 0 && (mode & 1) != 0) {
        sk_boot_fail((unsigned int)flags | 0x40, 0, "Unsupported anywhere allocation");  /* 0x5aa904 */
    }
    r = sk_alloc_phys(flags, base, size, 5, mapped, align, a);  /* FUN_00117fdc */
    sk_set_error(0);
    if (r == 0) {
        sk_boot_fail((unsigned int)flags, 0, "Failed to allocate memory at addr");  /* 0x5aa952 */
    }
    if (r <= r + size) return r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x11b18) */
}

/*--------------------------------------------------------------------*/
/* FUN_00011b18 @ 0x00011b18   (est. sk_arena_alloc)
 * Ghidra: void FUN_00011b18(ulong size, undefined8 align, undefined8 guard,
 *                           undefined8 mode, undefined8 a)
 * Allocates a contiguous arena of `size` bytes via sk_alloc_at, trapping on
 * a wrapped result. Used for the buddy allocator arena and boot regions.
 * Confidence: medium
 * Notes: helper FUN_00011a08; trap 0x11b80. */
void *sk_arena_alloc(unsigned long size, void *align, unsigned long guard, unsigned long mode, void *a)
{
    unsigned long r = sk_alloc_at(0, size, align, 1, guard, (void *)mode, a);  /* FUN_00011a08 */
    if (r <= r + size) return (void *)r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x11b80) */
}

/*--------------------------------------------------------------------*/
/* FUN_00011b80 @ 0x00011b80   (est. sk_arena_free)
 * Ghidra: void FUN_00011b80(undefined8 p, undefined8 size, undefined8 flags, undefined8 a)
 * Frees an arena region: delegates to FUN_001180cc, and if the result has
 * the low bit clear and the kernel error slot is nonzero, logs "Failed to
 * deallocate at address".
 * Confidence: medium
 * Notes: string s_Failed_to_deallocate_at_address___005aa99e;
 *   helpers FUN_001180cc, thunk_FUN_0006037c. */
void sk_arena_free(void *p, void *size, unsigned long flags, void *a)
{
    unsigned long r = sk_dealloc(p, a, size);  /* FUN_001180cc */
    if ((r & 1) == 0) {
        unsigned int *err = sk_error_slot();
        if (*err != 0) {
            sk_boot_fail((unsigned int)flags, 0, "Failed to deallocate at address");  /* 0x5aa99e */
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00011bf4 @ 0x00011bf4   (est. sk_mem_clear)
 * Ghidra: undefined8 FUN_00011bf4(undefined8 base, undefined8 len, undefined1 mode,
 *                                 ulong flags, undefined8 a)
 * Clears / applies debug flags to a memory region: rejects unsupported debug
 * flags (0x83 bits), delegates to FUN_0011807c, and on failure reports
 * "Failed to madvise" unless the error slot is clear. Returns the status.
 * Confidence: medium
 * Notes: strings s_Unsupported_debug_flags__u_005aa9d4,
 *   s_Failed_to_madvise__d_at_address___005aa9f0; helper FUN_0011807c. */
unsigned long sk_mem_clear(void *base, unsigned long len, unsigned char mode, unsigned long flags, void *a)
{
    unsigned long r;

    if ((flags & 0x83) != 0) {
        sk_boot_fail((unsigned int)flags | 0x40, 1, "Unsupported debug flags %u");  /* 0x5aa9d4 */
    }
    r = sk_madvise(a, base, (void *)len, mode);  /* FUN_0011807c */
    if ((int)r != 0) {
        unsigned int *err = sk_error_slot();
        if (*err == 0) return 0;
        sk_boot_fail((unsigned int)flags, 0, "Failed to madvise %d at address");  /* 0x5aa9f0 */
        return 1;
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00011cac @ 0x00011cac   (est. sk_zone_lookup)
 * Ghidra: ulong FUN_00011cac(undefined8 key, long *out_zone, uint start_idx)
 * Walks the registered malloc zones (table at DAT_006adfe8, count
 * DAT_006ac238) starting at `start_idx`, invoking each zone's matcher method
 * (offset 0x10) on `key`. Returns the matching zone address (and stores it
 * through out_zone), or 0 if none match. Traps on table overflow.
 * Confidence: medium
 * Notes: zone table DAT_006adfe8/006adff0, count DAT_006ac238; trap 0x11d7c. */
unsigned long sk_zone_lookup(void *key, void **out_zone, unsigned int start_idx)
{
    unsigned long zone, r = 0;
    unsigned int i;

    for (i = start_idx; i < sk_zone_count; i++) {   /* _DAT_006ac238 */
        zone = *(unsigned long *)((char *)0x6adfe8 + i * 8);  /* DAT_006adfe8 */
        r = ((unsigned long (*)(void *, void *))
             **(void ***)(zone + 0x10))((void *)zone, key);
        if (r != 0) goto found;
    }
    r = 0;
found:
    if (out_zone != 0) *out_zone = (void *)r;
    return zone;
}

/*--------------------------------------------------------------------*/
/* FUN_00011d7c @ 0x00011d7c   (est. sk_zone_register)
 * Ghidra: void FUN_00011d7c(undefined8 zone)
 * Registers a malloc zone: seeds the zone-table sanity words, builds a zone
 * object (FUN_00006630), and appends it to the global zone table
 * (DAT_006adfe8 / count DAT_006ac238), rejecting duplicates ("Attempted to
 * register duplicate zone"), an oversized table ("No capacity for zone"),
 * an unsupported zone version, and cross-linking the new zone's name via the
 * other registered zones. Logs "Registered zone %p at index %u" on success.
 * Confidence: medium
 * Notes: strings s_Attempted_to_register_duplicate_z_005aaa37,
 *   s_No_capacity_for_zone___p_005aaa61, s_Unsupported_zone_version___u_005aaa7b,
 *   s_Registered_zone__p_at_index__u_005aaa99, s_DefaultXzoneZone_005aaa26;
 *   helpers FUN_00006630/00117d18/00012060/00117e68; globals DAT_006ac23x. */
void sk_zone_register(void *zone)
{
    unsigned long zone_obj;
    unsigned int i;

    sk_zone_seed = 0x91175ef7;   /* _DAT_006ac234 */
    sk_zone_flags = 0x91175ef7;  /* _DAT_006ac230 */
    sk_zone_granule = 0;  /* FUN_0005ac2c, DAT_006ac23d (returns granule) */
    zone_obj = FUN_00006630(0x140, 0, zone, 0);  /* FUN_00006630 */
    if (sk_zone_count == 0) {
        if (*(unsigned int *)(zone_obj + 0x68) < 0xd) {
            sk_log(0x40, "Unsupported zone version %u");  /* s_005aaa7b */
        } else {
            unsigned long zt = sk_zone_table_grow((void *)0x6adff0, (void *)0x6adfe8, sk_zone_count << 3, 8);  /* FUN_00117d18 */
            *(unsigned long *)0x6adfe8 = zone_obj;  /* DAT_006adfe8 */
            sk_log(6, "Registered zone %p at index %u");  /* s_005aaa99 */
            sk_zone_count += 1;
        }
    } else {
        unsigned long *p = (unsigned long *)0x6adfe8;
        i = sk_zone_count;
        while (i != 0) {
            if (zone_obj == *p) {
                sk_log(0x40, "Attempted to register duplicate zone");  /* s_005aaa37 */
                goto done;
            }
            i -= 1;
            p += 1;
        }
        if (sk_zone_count == 2) {
            sk_log(0x40, "No capacity for zone %p");  /* s_005aaa61 */
        } else if (0xc < *(unsigned int *)(zone_obj + 0x68)) {
            unsigned long zt = sk_zone_table_grow((void *)0x6adff0, (void *)0x6adfe8, sk_zone_count << 3, 8);  /* FUN_00117d18 */
            *(unsigned long *)0x6adfe8 = zone_obj;
            sk_log(6, "Registered zone %p at index %u");
            sk_zone_count += 1;
        } else {
            sk_log(0x40, "Unsupported zone version %u");
        }
    }
done:
    if (*(long *)(zone_obj + 0x48) != 0) {
        for (i = 0; i < sk_zone_count; i++) {
            unsigned long other = *(unsigned long *)((char *)0x6adfe8 + i * 8);
            if (((unsigned long (*)(void *, void *))
                 **(void ***)(other + 0x10))((void *)other, *(void **)(zone_obj + 0x48)) != 0) {
                sk_zone_named(other);  /* FUN_0001220c */
                break;
            }
        }
        *(void **)(zone_obj + 0x48) = 0;
    }
    unsigned long len = sk_strlen("DefaultXzoneZone");  /* thunk_FUN_00115080, s_005aaa26 */
    char *name = (char *)sk_zone_alloc_n(zone_obj, len + 1);  /* FUN_00012060 */
    if (name != 0) {
        sk_strcpy(name, "DefaultXzoneZone", len + 1, len + 1);  /* FUN_00117e68 */
        *(char **)(zone_obj + 0x48) = name;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00012060 @ 0x00012060   (est. sk_zone_alloc_n)
 * Ghidra: void FUN_00012060(long zone, ulong size)
 * Allocates `size` bytes from the zone's allocation method (offset 0x18),
 * trapping on range wrap.
 * Confidence: medium
 * Notes: zone method dispatch; trap 0x120b4. */
void *sk_zone_alloc_n(unsigned long zone, unsigned long size)
{
    unsigned long r = ((unsigned long (*)(void *, unsigned long))
                       *(unsigned long (**)(void *, unsigned long))((char *)zone + 0x18))((void *)zone, size);
    if (r <= r + size) return (void *)r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x120b4) */
}

/*--------------------------------------------------------------------*/
/* FUN_000120b4 @ 0x000120b4   (est. sk_zone_calloc)
 * Ghidra: ulong FUN_000120b4(long zone, ulong count, ulong size, ulong flags)
 * Zone calloc: validates count*size for overflow (setting error 0xc /
 * ENOMEM and returning 0 on wrap), then calls the zone's calloc method
 * (offset 0x20). Traps on a wrapped result.
 * Confidence: medium
 * Notes: zone method dispatch; error thunk_FUN_0006037c; trap 0x12160. */
unsigned long sk_zone_calloc(unsigned long zone, unsigned long count, unsigned long size, unsigned long flags)
{
    unsigned long total = size;
    unsigned int *err;

    if (count != 1) {
        if (count * size >> 64 != 0) {
            err = sk_error_slot();
            *err = 0xc;
            if ((flags & 1) == 0) return 0;
            err = sk_error_slot();
            *err = 0xc;
            return 0;
        }
        total = count * size;
    }
    unsigned long r = ((unsigned long (*)(void *, unsigned long, unsigned long))
                       **(void ***)((char *)zone + 0x20))((void *)zone, count, size);
    if (r <= r + total) return r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x12160) */
}

/*--------------------------------------------------------------------*/
/* FUN_00012160 @ 0x00012160   (est. sk_zone_calloc_bulk)
 * Ghidra: void FUN_00012160(undefined8 zone, long count, long size)
 * Bulk zone calloc wrapper: computes count*size, calls the zone calloc
 * (FUN_000120b4), and traps if the resulting range wraps.
 * Confidence: medium
 * Notes: helper FUN_000120b4; trap 0x121b8. */
void *sk_zone_calloc_bulk(unsigned long zone, unsigned long count, unsigned long size)
{
    unsigned long r = sk_zone_calloc(zone, count, size, 0);  /* FUN_000120b4 */
    unsigned long total = size * count;
    if (r <= r + total) return (void *)r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x121b8) */
}

/*--------------------------------------------------------------------*/
/* FUN_000121b8 @ 0x000121b8   (est. sk_zone_alloc_realloc)
 * Ghidra: void FUN_000121b8(long zone, undefined8 p, ulong size)
 * Zone allocation variant via the zone method at offset 0x38, trapping on a
 * wrapped result.
 * Confidence: medium
 * Notes: zone method dispatch; trap 0x1220c. */
void *sk_zone_alloc_realloc(unsigned long zone, void *p, unsigned long size)
{
    unsigned long r = ((unsigned long (*)(void *, unsigned long))
                       *(unsigned long (**)(void *, unsigned long))((char *)zone + 0x38))((void *)zone, size);
    if (r <= r + size) return (void *)r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x1220c) */
}

/*--------------------------------------------------------------------*/
/* FUN_0001220c @ 0x0001220c   (est. sk_zone_named)
 * Ghidra: void FUN_0001220c(long zone)
 * Invokes the zone's "name" method (offset 0x30) to record a human-readable
 * zone name.
 * Confidence: medium
 * Notes: method dispatch offset 0x30. */
void sk_zone_named(unsigned long zone)
{
    ((void (*)(void *))**(void ***)(zone + 0x30))((void *)zone);
}

/*--------------------------------------------------------------------*/
/* FUN_00012218 @ 0x00012218   (est. sk_zone_aligned_alloc)
 * Ghidra: long FUN_00012218(long zone, ulong align, ulong size, uint flags)
 * Zone aligned allocation: for power-of-two align > 7 and a compatible size
 * it invokes the zone's aligned-alloc method (offset 0x70), returning its
 * result; otherwise sets error 0xc (and reports it if flags bit 0 is set).
 * Returns 0 on failure.
 * Confidence: medium
 * Notes: zone method offset 0x70; error thunk_FUN_0006037c. */
long sk_zone_aligned_alloc(unsigned long zone, unsigned long align, unsigned long size, unsigned int flags)
{
    unsigned long r;
    unsigned int err = 0x16;
    void (*method)(void);

    if ((align > 7) && ((align & (align - 1)) == 0) &&
        ((size & (align - 1)) == 0 || ((flags >> 1 & 1) == 0))) {
        method = *(void (**)(void))(zone + 0x70);
        if (method != 0) {
            r = ((unsigned long (*)(void *))**(void ***)(zone + 0x70))((void *)zone);
            if (r != 0) return r;
        }
        err = 0xc;
    }
    if ((flags & 1) != 0) {
        unsigned int *e = sk_error_slot();
        *e = err;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000122ac @ 0x000122ac   (est. sk_zone_aligned_alloc_try)
 * Ghidra: undefined8 FUN_000122ac(long zone, ulong size)
 * Zone aligned allocation that returns 0 (rather than failing loudly) when
 * the zone lacks an aligned-alloc method; dispatches to the method at offset
 * 0x70 otherwise.
 * Confidence: medium
 * Notes: zone method offset 0x70. */
unsigned long sk_zone_aligned_alloc_try(unsigned long zone, unsigned long size)
{
    void (**method)(void);

    if ((size > 7) && ((size & (size - 1)) == 0)) {
        method = *(void (***)(void))(zone + 0x70);
        if (method != 0) {
            return ((unsigned long (*)(void *))**method)((void *)zone);
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000122f0 @ 0x000122f0   (est. sk_zone_free_lookup)
 * Ghidra: void FUN_000122f0(ulong p, uint start_idx)
 * Frees a pointer by locating the owning zone: walks the registered zone
 * table from `start_idx`, invoking each zone's matcher (offset 0x10) on the
 * pointer; the matching zone's free method (offset 0x78, or fallback
 * sk_zone_named at 0x30) releases it. If no zone matches, falls back to
 * FUN_0000298c (generic free at level 0x40).
 * Confidence: medium
 * Notes: zone table DAT_006adfe8/count DAT_006ac238; helper FUN_0000298c;
 *   traps 0x12400/0x12448. */
void sk_zone_free_lookup(unsigned long p, unsigned int start_idx)
{
    unsigned long zone;
    unsigned int i;
    unsigned long match;

    if (p == 0) return;
    for (i = start_idx; i < sk_zone_count; i++) {   /* _DAT_006ac238 */
        zone = *(unsigned long *)((char *)0x6adfe8 + i * 8);  /* DAT_006adfe8 */
        match = ((unsigned long (*)(void *, unsigned long))
                 **(void ***)(zone + 0x10))((void *)zone, p);
        if (match != 0) {
            void (**method)(void) = *(void (***)(void))(zone + 0x78);
            if (method == 0) {
                sk_zone_named(zone);  /* FUN_0001220c */
                return;
            }
            if (p <= p + match) {
                ((void (*)(void *, unsigned long, unsigned long))**method)((void *)zone, p, match);
                return;
            }
            __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x12400) */
        }
    }
    sk_free_other(0x40, p);  /* FUN_0000298c */
}

/*--------------------------------------------------------------------*/
/* FUN_0001244c @ 0x0001244c   (est. sk_zone0_alloc)
 * Ghidra: void FUN_0001244c(ulong size)
 * Allocates `size` bytes from zone 0 (DAT_006adfe8), trapping on a wrapped
 * result.
 * Confidence: medium
 * Notes: helper FUN_00012060; trap 0x124a4. */
void *sk_zone0_alloc(unsigned long size)
{
    unsigned long r = (unsigned long)sk_zone_alloc_n(sk_zone0(), size);  /* FUN_00012060 */
    if (r <= r + size) return (void *)r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x124a4) */
}

/*--------------------------------------------------------------------*/
/* FUN_000124a4 @ 0x000124a4   (est. sk_zone0_aligned_alloc)
 * Ghidra: void FUN_000124a4(undefined8 size, ulong align)
 * Aligned allocation from zone 0 via sk_zone_aligned_alloc (flags=3),
 * trapping on a wrapped result.
 * Confidence: medium
 * Notes: helper FUN_00012218; trap 0x12504. */
void *sk_zone0_aligned_alloc(unsigned long size, unsigned long align)
{
    unsigned long r = sk_zone_aligned_alloc(sk_zone0(), size, align, 3);  /* FUN_00012218 */
    if (r <= r + align) return (void *)r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x12504) */
}

/*--------------------------------------------------------------------*/
/* FUN_00012504 @ 0x00012504   (est. sk_zone0_calloc_bulk)
 * Ghidra: void FUN_00012504(long count, long size)
 * Bulk calloc from zone 0 (FUN_00012160), trapping on a wrapped result.
 * Confidence: medium
 * Notes: helper FUN_00012160; trap 0x12568. */
void *sk_zone0_calloc_bulk(unsigned long count, unsigned long size)
{
    unsigned long r = (unsigned long)sk_zone_calloc_bulk(sk_zone0(), count, size);  /* FUN_00012160 */
    unsigned long total = size * count;
    if (r <= r + total) return (void *)r;
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x12568) */
}

/*--------------------------------------------------------------------*/
/* FUN_00012568 @ 0x00012568   (est. sk_heap_free)
 * Ghidra: void FUN_00012568(long p)
 * Frees a heap pointer: if zone 0 has a bulk-free method (offset 0x90) it
 * dispatches to it; otherwise falls back to sk_zone_free_lookup.
 * Confidence: medium
 * Notes: zone 0 DAT_006adfe8; helper FUN_000122f0. */
void sk_heap_free(void *p)
{
    void (**method)(void);

    if (p == 0) return;
    method = *(void (***)(void))((char *)sk_zone0() + 0x90);
    if (method != 0) {
        ((void (*)(void *))**method)(sk_zone0());
        return;
    }
    sk_zone_free_lookup((unsigned long)p, 0);  /* FUN_000122f0 */
}

/*--------------------------------------------------------------------*/
/* FUN_000125b0 @ 0x000125b0   (thunk sk_heap_free)
 * Ghidra: void thunk_FUN_00012568(long p)
 * Thunk to sk_heap_free (FUN_00012568).
 * Confidence: high (thunk). */
void sk_heap_free_thunk(void *p)
{
    sk_heap_free(p);
}

/*--------------------------------------------------------------------*/
/* FUN_000125b4 @ 0x000125b4   (est. sk_heap_alloc)
 * Ghidra: ulong FUN_000125b4(long p, ulong size)
 * Heap allocation: for a nonzero existing pointer + size, walks the zone
 * table to find the owning zone and reallocates through its realloc method
 * (offset 0x38); for an empty request it allocates from zone 0
 * (FUN_00012060). Falls back to sk_free_other on an unmatchable pointer,
 * sets error 0xc on failure, and traps on a wrapped result.
 * Confidence: medium
 * Notes: zone table DAT_006adfe8/count DAT_006ac238; helpers FUN_00012060/
 *   000121b8/0000298c/thunk_FUN_0006037c; trap 0x126bc. */
unsigned long sk_heap_alloc(void *p, unsigned long size)
{
    unsigned long r, zone;
    unsigned int i;

    if (p == 0 || size == 0) {
        r = (unsigned long)sk_zone_alloc_n(sk_zone0(), size);  /* FUN_00012060 */
        if (r != 0) {
            if (size == 0) sk_heap_free(p);
            if (r <= r + size && size <= (r + size) - r) return r;
            __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x126bc) */
        }
    } else {
        for (i = 0; i < sk_zone_count; i++) {   /* _DAT_006ac238 */
            zone = *(unsigned long *)((char *)0x6adfe8 + i * 8);  /* DAT_006adfe8 */
            if (((unsigned long (*)(void *, void *))
                 **(void ***)(zone + 0x10))((void *)zone, p) != 0) {
                r = (unsigned long)sk_zone_alloc_realloc(zone, p, size);  /* FUN_000121b8 */
                if (r != 0) {
                    if (size == 0) sk_heap_free(p);
                    if (r <= r + size && size <= (r + size) - r) return r;
                    __builtin_trap();
                }
                break;
            }
        }
        sk_free_other(0x40, (unsigned long)p);  /* FUN_0000298c */
    }
    *sk_error_slot() = 0xc;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000126e8 @ 0x000126e8   (est. sk_zone_match)
 * Ghidra: long FUN_000126e8(long p)
 * Returns the zone (from the global table) that matches pointer `p`, or 0
 * if none do.
 * Confidence: medium
 * Notes: zone table DAT_006adfe8/count DAT_006ac238; trap 0x1279c. */
long sk_zone_match(void *p)
{
    unsigned long zone, match;
    unsigned int i;

    if (p != 0 && sk_zone_count != 0) {
        for (i = 0; i < sk_zone_count; i++) {
            zone = *(unsigned long *)((char *)0x6adfe8 + i * 8);  /* DAT_006adfe8 */
            match = ((unsigned long (*)(void *, void *))
                     **(void ***)(zone + 0x10))((void *)zone, p);
            if (match != 0) return match;
        }
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001279c @ 0x0001279c   (est. sk_zone0_method_dispatch)
 * Ghidra: void FUN_0001279c(undefined8 p)
 * Dispatches a method call through zone 0's method table (offset 0x60 -> +8)
 * on `p`.
 * Confidence: medium
 * Notes: zone 0 DAT_006adfe8; jumptable 0x127bc. */
void sk_zone0_method_dispatch(void *p)
{
    void (**tbl)(void) = *(void (***)(void))((char *)sk_zone0() + 0x60);
    ((void (*)(void *, void *))tbl[1])((void *)sk_zone0(), p);
}

/*--------------------------------------------------------------------*/
/* FUN_000127c0 @ 0x000127c0   (est. sk_zone0_aligned_alloc_out)
 * Ghidra: undefined4 FUN_000127c0(long *out, ulong size)
 * Zone 0 aligned allocation storing the result through *out: returns 0 on
 * success, 0xc (alignment unsupported) or 0x16 (bad alignment/size) on
 * failure.
 * Confidence: medium
 * Notes: helper FUN_000122ac. */
unsigned int sk_zone0_aligned_alloc_out(void **out, unsigned long size)
{
    unsigned long r = sk_zone_aligned_alloc_try(sk_zone0(), size);  /* FUN_000122ac */
    if (r == 0) {
        if ((size & (size - 1)) != 0 || size < 8) return 0x16;
        return 0xc;
    }
    *out = (void *)r;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0001281c @ 0x0001281c   (est. sk_zone_create_desc)
 * Ghidra: void FUN_0001281c(undefined8 *desc, undefined1 kind, undefined1 flags,
 *                           uint a, uint b, uint granule, undefined8 name,
 *                           ulong base, uint align)
 * Initializes a malloc-zone descriptor object: records kind, flags, the
 * count/size/granule fields, computes the aligned interior layout from
 * base/align/granule, and links the per-granule slot array. Fills the
 * descriptor header fields.
 * Confidence: medium
 * Notes: zone descriptor layout. */
void sk_zone_create_desc(void **desc, uint8_t kind, uint8_t flags, unsigned int a,
                         unsigned int b, unsigned int granule, void *name,
                         unsigned long base, unsigned int align)
{
    unsigned long *slots = 0;
    unsigned int nslots = 0;
    unsigned long usable;
    unsigned int pad;

    if (base != 0) {
        unsigned long per = (unsigned long)b;
        usable = (per != 0) ? base / per : 0;
        unsigned long rem = base - usable * per;
        pad = (rem != 0) ? per - rem : 0;
        usable = align - pad;
        if ((pad <= align) && (granule << 1 <= usable)) {
            unsigned long *p = (unsigned long *)(pad + base);
            unsigned int cnt = 0;
            if (granule != 0) cnt = (unsigned int)usable / granule;
            *p = 0;
            p[1] = (unsigned long)p;
            cnt = cnt * granule;
            p[2] = 0;
            p[3] = 0;
            nslots = granule;
            slots = p;
        } else {
            nslots = 0;
            slots = 0;
            usable = 0;
        }
    }
    desc[0] = 0;
    desc[1] = 0;
    *(uint8_t *)(desc + 2) = kind;
    *(uint8_t *)((char *)desc + 0x11) = flags;
    *(uint16_t *)((char *)desc + 0x12) = 0;
    unsigned int cnt = (granule != 0) ? a / granule : 0;
    *(unsigned int *)((char *)desc + 0x14) = a;
    *(unsigned int *)(desc + 3) = cnt * granule;
    *(unsigned int *)((char *)desc + 0x1c) = b;
    *(unsigned int *)(desc + 4) = granule;
    *(unsigned long *)((char *)desc + 0x2c) = 0;
    *(unsigned long *)((char *)desc + 0x24) = 0;
    *(unsigned int *)((char *)desc + 0x34) = 0;
    desc[7] = (void *)slots;
    *(unsigned int *)(desc + 8) = nslots;
    *(unsigned int *)((char *)desc + 0x44) = 0;
    desc[9] = (void *)name;
    desc[10] = (void *)slots;
    *(unsigned int *)(desc + 0xb) = (unsigned int)(usable % granule);
    *(unsigned int *)((char *)desc + 0x5c) = 0;
    if (slots != 0) {
        *slots = 0;
        desc[5] = (void *)slots;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_000128cc @ 0x000128cc   (est. sk_zone_alloc_slot)
 * Ghidra: ulong FUN_000128cc(long zone)
 * Zone slot allocator: takes the zone lock, pops a free slot from the
 * free-slot list (zone+0x30), or on empty grows the zone by allocating a new
 * run of pages (FUN_00011a08) sized to the zone granule, registering the run
 * in the zone's run list (zone+0x28). Releases the lock and returns the new
 * slot address.
 * Confidence: medium
 * Notes: strings s_Failed_to_acquire_lock__p__005a9a23,
 *   s_Failed_to_release_lock__p__005a9a3f; helpers FUN_0011582c/00115894/
 *   00012b0c/00011a08. */
unsigned long sk_zone_alloc_slot(unsigned long zone)
{
    unsigned long *run;
    unsigned long slot;
    unsigned int granule;
    unsigned int sz;

    if (sk_buddy_lock(zone) != 0) {  /* FUN_0011582c */
        sk_boot_fail(0x40, 0, "Failed to acquire lock %p");
    }
    run = *(unsigned long **)(zone + 0x30);
    if (run != 0) {
        unsigned long next = run[1];
        *(unsigned long **)(zone + 0x30) = (unsigned long *)*run;
        if (*(long *)(zone + 0x48) == 0) {
            *run = 0;
            run[1] = 0;
        } else {
            sk_zone_ref_run(zone, run);  /* FUN_00012b0c */
        }
        slot = (unsigned long)run;
        goto done;
    }
    unsigned long flags = 0x2000;
    unsigned long r;
    unsigned long local[2] = {0, 0};
    if (*(long *)(zone + 0x48) != 0) {
        flags = (*(unsigned int *)(zone + 0x20) >> 0xe == 0) ? 0x2000 : 0x2200;
    }
    granule = *(unsigned int *)(zone + 0x14);
    r = sk_alloc_at(0, granule, (void *)(LZCOUNT(0) & 0x1f), 1, flags,(void *)( 1), (void *)&local);  /* FUN_00011a08 */
    if (r == 0) {
        sk_panic("BUG IN CLIENT OF LIBMALLOC: zone grow failed");  /* FUN_001150e0 */
    }
    if (*(long *)(zone + 0x48) == 0) {
        sz = *(unsigned int *)(zone + 0x20);
        slot = r;
    } else {
        slot = sk_zone_alloc_slot(zone);  /* FUN_000128cc */
        sz = 0;
    }
    *(unsigned int *)(zone + 0x40) = sz;
    unsigned long *newrun = (unsigned long *)r;
    *newrun = 0;
    newrun[1] = r;
    newrun[3] = local[1];
    newrun[2] = local[0];
    *(unsigned long **)(zone + 0x38) = newrun;
    *newrun = *(unsigned long *)(zone + 0x28);
    *(unsigned long **)(zone + 0x28) = newrun;
    granule = *(unsigned int *)(zone + 0x40);
    slot = newrun[1] + granule;
    *(unsigned int *)(zone + 0x40) = *(unsigned int *)(zone + 0x20) + granule;
done:
    if (sk_buddy_unlock(zone) != 0) {  /* FUN_00115894 */
        sk_boot_fail(0x40, 0, "Failed to release lock %p");
    }
    return slot;
}

/*--------------------------------------------------------------------*/
/* FUN_00012b0c @ 0x00012b0c   (est. sk_zone_ref_run)
 * Ghidra: void FUN_00012b0c(long zone, undefined8 *run)
 * Re-queues a zone run: takes the zone lock, and links the run into the
 * zone's free-slot list (zone+0x30). Releases the lock.
 * Confidence: medium
 * Notes: strings s_Failed_to_acquire_lock__p__005a9a23,
 *   s_Failed_to_release_lock__p__005a9a3f; helpers FUN_0011582c/00115894/
 *   000128cc. */
void sk_zone_ref_run(unsigned long zone, void **run)
{
    void **p = run;

    if (sk_buddy_lock(zone) != 0) {  /* FUN_0011582c */
        sk_boot_fail(0x40, 0, "Failed to acquire lock %p");
    }
    if (*(long *)(zone + 0x48) != 0) {
        p = (void **)sk_zone_alloc_slot(zone);  /* FUN_000128cc */
    }
    *p = *(void **)(zone + 0x30);
    p[1] = run;
    *(void ***)(zone + 0x30) = p;
    if (sk_buddy_unlock(zone) != 0) {  /* FUN_00115894 */
        sk_boot_fail(0x40, 0, "Failed to release lock %p");
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00012c04 @ 0x00012c04   (est. sk_tcb_slot_alloc_init)
 * Ghidra: void FUN_00012c04(long td, ulong count)
 * Allocates the capability-slot array for a TCB (td): validates that the
 * TCB is in the expected state (no received/allocated slot counts), asserts
 * the request is < TB_MAX_CAPS (5) via "TB_ASSERT: num_caps < TB_MAX_CAPS",
 * and allocates each slot from FUN_00034f70, storing them at td+0x38. On a
 * NULL allocation it panics via FUN_004b0034.
 * Confidence: medium (string-matched "TB_ASSERT: num_caps < TB_MAX_CAPS").
 * Notes: strings s_TB_ASSERT__num_caps_<__TB_MAX_CA_005aabbd,
 *   s_TB_ASSERT__td_>received_slot_cou_005aab87,
 *   s_TB_ASSERT__td_>allocated_slot_co_005aab3a; helpers FUN_00034f70/
 *   FUN_004b0034. */
void sk_tcb_slot_alloc_init(void *td, unsigned long count)
{
    long *slots = (long *)((char *)td + 0x38);
    unsigned long i;
    long s;

    if ((unsigned long)((char *)td + 0x68) < (unsigned long)slots) {
        __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x12c88) */
    }
    if (*(long *)((char *)td + 0x58) == 0) {
        if (*(long *)((char *)td + 0x60) == 0) {
            if (count < 5) {
                for (i = 0; i < count; i++) {
                    s = sk_tcb_slot_alloc();  /* FUN_00034f70 */
                    *slots = s;
                    if (s == 0) {
                        sk_panic_tcb();  /* FUN_004b0034 */
                        __builtin_trap();
                    }
                    slots += 1;
                }
                *(unsigned long *)((char *)td + 0x58) = count;
                *(unsigned long *)((char *)td + 0x60) = 0;
                return;
            }
            sk_puts("TB_ASSERT: num_caps < TB_MAX_CAPS");  /* 0x5aabbd */
        } else {
            sk_puts("TB_ASSERT: td->received_slot_count");  /* 0x5aab87 */
        }
    } else {
        sk_puts("TB_ASSERT: td->allocated_slot_count");  /* 0x5aab3a */
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x12cec) */
}

/*--------------------------------------------------------------------*/
/* FUN_00012d3c @ 0x00012d3c   (est. sk_tcb_slot_recv_assert)
 * Ghidra: void FUN_00012d3c(void)
 * Assertion failure for a TCB with a nonzero received-slot count: prints
 * "TB_ASSERT: td->received_slot_count" and traps.
 * Confidence: medium (string-matched).
 * Notes: string s_TB_ASSERT__td_>received_slot_cou_005aab87. */
void sk_tcb_slot_recv_assert(void)
{
    sk_puts("TB_ASSERT: td->received_slot_count");  /* 0x5aab87 */
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x12d70) */
}

/*--------------------------------------------------------------------*/
/* FUN_00012d70 @ 0x00012d70   (est. sk_tcb_slot_alloc_teardown)
 * Ghidra: void FUN_00012d70(long td)
 * Tears down a TCB's capability-slot array: validates the received/allocated
 * slot counts are consistent, releases each allocated slot that is not also
 * received (FUN_004b23d8), zeroes the slot array, and resets the counters.
 * Confidence: medium (string-matched "TB_ASSERT").
 * Notes: strings s_TB_ASSERT__td_>received_slot_cou_005aac1e,
 *   s_TB_ASSERT__td_>allocated_slot_co_005aac70; helper FUN_004b23d8;
 *   trap 0x12e04. */
void sk_tcb_slot_alloc_teardown(void *td)
{
    unsigned long i, nalloc, nrecv;

    if ((unsigned long)((char *)td + 0x68) < (unsigned long)((char *)td + 0x38)) {
        __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x12e04) */
    }
    nalloc = *(unsigned long *)((char *)td + 0x58);
    nrecv = *(unsigned long *)((char *)td + 0x60);
    if (nalloc < nrecv) {
        sk_puts("TB_ASSERT: td->received_slot_count");  /* 0x5aac1e */
    } else if (nalloc < 5) {
        for (i = 0; i < nalloc; i++) {
            if (nrecv <= i) {
                sk_tcb_slot_release((void *)*(unsigned long *)((char *)td + 0x38 + i * 8));  /* FUN_004b23d8 */
            }
            *(unsigned long *)((char *)td + 0x38 + i * 8) = 0;
        }
        *(unsigned long *)((char *)td + 0x58) = 0;
        *(unsigned long *)((char *)td + 0x60) = 0;
        return;
    } else {
        sk_puts("TB_ASSERT: td->allocated_slot_count");  /* 0x5aac70 */
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0x12e48) */
}

/*--------------------------------------------------------------------*/
/* FUN_00012e48 @ 0x00012e48   (est. sk_tcb_create_zeroed)
 * Ghidra: void FUN_00012e48(void)
 * Allocates and zero-fills a 0x118-byte TCB object (tag 0x1082040eda8e2da),
 * initializing its function-dispatch pointer at offset 0xc, and panics via
 * FUN_004b0068 on allocation failure.
 * Confidence: medium
 * Notes: tag 0x1082040eda8e2da; helpers FUN_00010244/FUN_004b0068. */
void *sk_tcb_create_zeroed(void *cfg)
{
    (void)cfg;
    unsigned long *tcb = (unsigned long *)sk_heap_calloc(1, 0x118, (void *)0x1082040eda8e2da);  /* FUN_00010244 */
    if (tcb != 0) {
        for (int i = 0; i < 0x23; i++) tcb[i] = 0;
        tcb[0xc] = 0x658fa8;
        return tcb;
    }
    sk_panic_tcb();  /* FUN_004b0068 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00012eb8 @ 0x00012eb8   (est. sk_tcb_cap_copy)
 * Ghidra: int FUN_00012eb8(undefined8 src, long dst, long *out, uint flags)
 * Copies a capability between two TCBs: reads the source capability buffer
 * (FUN_000159b8), allocates a destination buffer, copies the capability
 * words, validates the copy (FUN_00013134), migrates the buffer ownership,
 * and stores the result through *out. On failure frees the intermediates and
 * returns (flags&2)<<1. Panics on assertion failure ("TB_ASSERT: err ==
 * TB_ERROR_SUCCESS").
 * Confidence: medium (string-matched "TB_ASSERT: err == TB_ERROR_SUCCESS").
 * Notes: string s_TB_ASSERT__err____TB_ERROR_SUCCE_005aacb1; helpers
 *   FUN_000159b8/00010244/00117cc4/00015984/00015468/00013134/004b0080/
 *   004b0068; alloc tags 0x100004077774924/0x1090040b6685729/0x102004071d150f8. */
int sk_tcb_cap_copy(void *src_tcb, void *dst_tcb, void **out, unsigned int flags)
{
    unsigned long *sbuf = (unsigned long *)sk_cap_buf(src_tcb);  /* FUN_000159b8 */
    unsigned long nsrc = sbuf[3];
    unsigned long base = *sbuf;
    unsigned long *dbuf = (unsigned long *)sk_heap_calloc(nsrc, 1, (void *)0x100004077774924);  /* FUN_00010244 */
    if (dbuf != 0) {
        sk_memcpy(dbuf, (void *)base, nsrc);  /* FUN_00117cc4 */
        unsigned long *meta = (unsigned long *)sk_heap_calloc(1, 0x68, (void *)0x1090040b6685729);
        if (meta != 0) {
            *meta = (unsigned long)dbuf;
            meta[2] = 0;
            meta[3] = nsrc;
            meta[4] = 0;
            meta[6] = 0;
            *(uint16_t *)((char *)meta + 0x2a) = *(uint16_t *)((char *)sbuf + 0x2a);
            unsigned int *op = (unsigned int *)sk_heap_calloc(1, 0x58, (void *)0x102004071d150f8);
            if (op == 0) sk_panic_tcb();  /* FUN_004b0068 */
            *op = 4;
            *(uint8_t *)(op + 1) = 1;
            *(unsigned long **)(op + 0x14) = meta;
            *(unsigned long *)(op + 6) = (unsigned long)src_tcb;
            sk_obj_retain(op, 1);  /* FUN_00015984 */
            unsigned int *ref = op;
            sk_cap_install(src_tcb, op, &ref);  /* FUN_00015468 */
            if (ref == 0) {
                sk_heap_free((void *)*meta);
                sk_heap_free(meta);
                sk_heap_free(op);
                return (flags & 2) << 1;
            }
            unsigned long *dbuf2 = (unsigned long *)sk_cap_buf(ref);  /* FUN_000159b8 */
            unsigned long n2 = dbuf2[3];
            sk_heap_free((void *)*sbuf);
            *sbuf = 0;
            sbuf[2] = 0;
            sbuf[3] = 0;
            if (sk_tcb_cap_copy_commit((void *)n2, n2, (void *)n2, &n2) != 0) {  /* FUN_00013134 */
                sk_puts("TB_ASSERT: err == TB_ERROR_SUCCESS");  /* 0x5aacb1 */
                __builtin_trap();
            }
            if (dbuf2[3] <= sbuf[3]) {
                base = *sbuf;
                sk_memcpy((void *)base,(void *)( *dbuf2), dbuf2[3]);  /* FUN_00117cc4 */
                *(uint16_t *)((char *)sbuf + 0x2a) = *(uint16_t *)((char *)dbuf2 + 0x2a);
                *(unsigned long *)((char *)dst_tcb + 0x18) = *(unsigned long *)(ref + 6);
                sk_obj_retain(dst_tcb, 2);  /* FUN_00015984 */
                if (meta != dbuf2) {
                    sk_heap_free((void *)*dbuf2);
                    sk_heap_free(dbuf2);
                }
                sk_heap_free((void *)*meta);
                sk_heap_free(meta);
                sk_heap_free(op);
                if (out == 0) return 0;
                *out = dst_tcb;
                return 0;
            }
        }
    }
    sk_panic_tcb();  /* FUN_004b0080 */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00013134 @ 0x00013134   (est. sk_tcb_cap_copy_commit)
 * Ghidra: undefined8 FUN_00013134(undefined8 a, ulong size, undefined8 c, ulong *out)
 * Capability-copy commit helper: allocates a buffer of `size` words (tag
 * 0x100004077774924), stores it (zeroing the header fields) through *out,
 * and returns 0 on success. On allocation failure it releases the previous
 * buffer via sk_heap_free and marks the state as failed (offset 0x29 = 1).
 * Confidence: medium
 * Notes: tag 0x100004077774924; helpers FUN_00010244/004b0080/
 *   thunk_FUN_00012568; trap 0x131a4. */
unsigned long sk_tcb_cap_copy_commit(void *a, unsigned long size, void *c, unsigned long *out)
{
    unsigned long r = (unsigned long)sk_heap_calloc(size, 1, (void *)0x100004077774924);  /* FUN_00010244 */
    if (r != 0) {
        *out = r;
        *(uint8_t *)(out + 1) = 0;
        out[2] = 0;
        out[3] = size;
        out[4] = 0;
        out[6] = 0;
        *(uint8_t *)((char *)out + 0x29) = 0;
        return 0;
    }
    sk_panic_tcb();  /* FUN_004b0080 */
    sk_heap_free((void *)*out);
    *out = 0;
    out[6] = 0;
    out[3] = 0;
    out[4] = 0;
    out[2] = 0;
    *(uint8_t *)((char *)out + 0x29) = 1;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_000131e8 @ 0x000131e8   (est. sk_tcb_cap_release_commit)
 * Ghidra: void FUN_000131e8(undefined8 a, undefined8 *slot, undefined8 c, undefined8 size)
 * Releases a capability buffer slot (sk_heap_free of *slot), clears the
 * buffer header, then re-commits a fresh buffer via sk_tcb_cap_copy_commit.
 * Confidence: medium
 * Notes: helpers thunk_FUN_00012568/00013134. */
void sk_tcb_cap_release_commit(void *a, void **slot, void *c, void *size)
{
    sk_heap_free(*slot);
    *slot = 0;
    slot[2] = 0;
    slot[3] = 0;
    sk_tcb_cap_copy_commit((void *)0, (unsigned long)size, c, slot);  /* FUN_00013134 */
}

/*--------------------------------------------------------------------*/
/* FUN_00013228 @ 0x00013228   (est. sk_assert_internal_cc)
 * Ghidra: void FUN_00013228(void)
 * Assertion failure at internal.h:0xcc: prints the generic failure string
 * (DAT_005aacf2) and returns.
 * Confidence: medium (string "internal.h").
 * Notes: string s_internal_h_005aad1c / DAT_005aacf2. */
void sk_assert_internal_cc(void)
{
    sk_puts((const char *)0x5aacf2);  /* FUN_00118b28 */
}

/*--------------------------------------------------------------------*/
/* FUN_00013244 @ 0x00013244   (est. sk_assert_internal_c7)
 * Ghidra: void FUN_00013244(void)
 * Assertion failure at internal.h:0xc7: prints the generic failure string
 * (DAT_005aacf2) and returns.
 * Confidence: medium (string "internal.h").
 * Notes: string s_internal_h_005aad1c / DAT_005aacf2. */
void sk_assert_internal_c7(void)
{
    sk_puts((const char *)0x5aacf2);  /* FUN_00118b28 */
}

/*--------------------------------------------------------------------*/
/* FUN_00013260 @ 0x00013260   (est. sk_tcb_field_apply)
 * Ghidra: void FUN_00013260(undefined8 a, undefined8 b, undefined8 c)
 * Applies a function to a per-thread field: computes a per-thread value
 * (FUN_000603bc), resolves a method table (FUN_000636d0/636d8) and dispatches
 * the indirect call with the two arguments. Traps on value-wrap.
 * Confidence: medium
 * Notes: helpers FUN_00060524/000603bc/000636d0/000636d8; trap 0x132d4. */
void *FUN_00013260(void *a, void *b, void *c)
{
    unsigned long v = FUN_000603bc();
    void (**method)(void);

    if (v <= v + 0x50) {
        method = (void (**)(void))FUN_000636d0();
        unsigned long arg = FUN_000636d8(v);
        ((void (*)(unsigned long, void *, void *))*method)(arg, b, c);
        return (void *)v;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x132d4) */
}

/*--------------------------------------------------------------------*/
/* FUN_000132d4 @ 0x000132d4   (est. sk_div8)
 * Ghidra: ulong FUN_000132d4(long param_1)
 * Returns (param_1 + 7) >> 3 — a ceil-divide-by-8 helper.
 * Confidence: high (trivial). */
unsigned long sk_div8(long v)
{
    return (unsigned long)(v + 7) >> 3;
}

/*--------------------------------------------------------------------*/
/* FUN_000132e0 @ 0x000132e0   (est. sk_lookup_cap_buffer)
 * Ghidra: undefined8 FUN_000132e0(undefined8 key, undefined8 hint)
 * Looks up a capability buffer by key: first checks the global TCB-storage
 * key (0x6adff8, size 0x1b8); if that matches the expected tag (0x37) it
 * re-runs the lookup with the caller's key/hint, otherwise returns 0.
 * Confidence: medium
 * Notes: helpers FUN_0005ea94. */
unsigned long sk_lookup_cap_buffer(void *key, void *hint)
{
    long tag = FUN_0005ea94((void *)0x6adff8, (void *)0x1b8, 0, 0);
    if (tag == 0x37) {
        return FUN_0005ea94(key, hint, 0, 0);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00013348 @ 0x00013348   (est. sk_tcb_init_regions)
 * Ghidra: void FUN_00013348(undefined8 cfg, long tcb)
 * Initializes the region/tracking fields of a freshly allocated TCB: clears
 * the per-region list heads (tcb+0x88..0xf0), sets the object-type dispatch
 * pointer (tcb+0x60 = 0x659008), stores the object handle (FUN_00015440) at
 * tcb+0x88, and derives config flags (FUN_00015450) into tcb+0xe8/ec/ed.
 * Confidence: medium
 * Notes: dispatch pointer 0x659008; helpers FUN_00015440/00015450;
 *   trap 0x133f8. */
void sk_tcb_init_regions(void *cfg, void *tcb)
{
    unsigned int fl;

    if ((unsigned long)((char *)tcb + 0x118) < (unsigned long)((char *)tcb + 0x88) ||
        (unsigned long)((char *)tcb + 0xf8) < (unsigned long)((char *)tcb + 0x88)) {
        __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x133f8) */
    }
    *(unsigned long *)((char *)tcb + 0xe0) = 0;
    *(unsigned long *)((char *)tcb + 0xd8) = 0;
    *(unsigned long *)((char *)tcb + 0xf0) = 0;
    *(unsigned long *)((char *)tcb + 0xe8) = 0;
    *(unsigned long *)((char *)tcb + 0xc0) = 0;
    *(unsigned long *)((char *)tcb + 0xb8) = 0;
    *(unsigned long *)((char *)tcb + 0xd0) = 0;
    *(unsigned long *)((char *)tcb + 200) = 0;
    *(unsigned long *)((char *)tcb + 0xa0) = 0;
    *(unsigned long *)((char *)tcb + 0x98) = 0;
    *(unsigned long *)((char *)tcb + 0xb0) = 0;
    *(unsigned long *)((char *)tcb + 0xa8) = 0;
    *(unsigned long *)((char *)tcb + 0x90) = 0;
    *(unsigned long *)((char *)tcb + 0x88) = 0;
    *(unsigned long *)((char *)tcb + 0x60) = 0x659008;
    *(unsigned long *)((char *)tcb + 0x88) = sk_tcb_handle(cfg);  /* FUN_00015440 */
    fl = sk_tcb_cfg_flags(cfg);  /* FUN_00015450 */
    if ((fl >> 1 & 1) == 0) {
        if ((fl & 1) != 0) {
            *(unsigned int *)((char *)tcb + 0xe8) = 4;
        }
    } else {
        *(unsigned int *)((char *)tcb + 0xe8) = fl >> 8 & 0xff;
    }
    if ((fl >> 2 & 1) != 0) *(uint8_t *)((char *)tcb + 0xec) = 1;
    if ((fl >> 3 & 1) != 0) *(uint8_t *)((char *)tcb + 0xed) = 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00013878 @ 0x00013878   (est. sk_tcb_register_async)
 * Ghidra: undefined8 FUN_00013878(long tcb)
 * Registers an async / deferred callback on a TCB: sets up a worker context
 * (FUN_00013ee4) bound to the TCB's object (tcb+0x88) and installs it via
 * FUN_00062c2c, optionally arming a debug trap (FUN_0006290c) when
 * tcb+0xec is set. Returns 0.
 * Confidence: medium
 * Notes: helpers FUN_0006290c/00013260/00062c2c/00013ee4; trap 0x13930. */
unsigned long sk_tcb_register_async(void *tcb)
{
    unsigned int n;
    unsigned long cfg[4];

    if ((unsigned long)((char *)tcb + 0x88) <= (unsigned long)((char *)tcb + 0x118) &&
        (unsigned long)((char *)tcb + 0x88) <= (unsigned long)((char *)tcb + 0xf8)) {
        n = *(unsigned int *)((char *)tcb + 0xe8);
        if (*(char *)((char *)tcb + 0xec) == '\x01') {
            sk_tcb_field_apply(0, (void *)FUN_00013260, 0);  /* FUN_0006290c */
        }
        if (n < 2) n = 1;
        cfg[0] = n;
        cfg[1] = (unsigned long)sk_cap_transfer;  /* FUN_00013ee4 */
        cfg[2] = 4;
        cfg[3] = 4;
        sk_async_install((void *)((char *)tcb + 0x98), *(void **)((char *)tcb + 0x88), &cfg[0]);  /* FUN_00062c2c */
        return 0;
    }
    __builtin_trap();  /* SoftwareBreakpoint(0x5519, 0x13930) */
}

/*--------------------------------------------------------------------*/
/* FUN_00013ee4 @ 0x00013ee4   (est. sk_cap_transfer)
 * Ghidra: ulong FUN_00013ee4(undefined8 tcb, undefined8 msg, undefined8 cap)
 * The cL4 capability-transfer (IPC cap passing) worker. Structural
 * reconstruction: collects the incoming message words (FUN_0005ee50/
 * FUN_0005eb78), builds an accept context, copies the sender capability
 * buffer, and hands the message to the TCB (FUN_00015468). On success it
 * installs any returned capability slots via CallSupervisor(1).
 * Confidence: low (large, structural summary).
 * Notes: string s_TB_ASSERT__payload_size_<__max_s_005ab475,
 *   s_TB_ASSERT__rcv_err____TB_ERROR_S_005ab441; helpers FUN_0005ee50/
 *   0005eb78/00060524/0005ee58/00015468. */
unsigned long sk_cap_transfer(void *tcb, void *msg, void *cap)
{
    unsigned long sz = FUN_0005ee50(msg);
    unsigned long words = sz << 3;
    unsigned long r;

    if (sz >> 0x3d != 0 || words >= 0x1b9) {
        sk_puts("TB_ASSERT: payload_size < max");  /* 0x5ab475 */
        __builtin_trap();
    }
    FUN_0005eb78((void *)msg, words, 0);
    FUN_00060524();
    r = sk_tcb_send(tcb, msg, (void **)cap);  /* FUN_00015468 */
    if (r != 0) {
        sk_puts("TB_ASSERT: rcv_err == TB_ERROR_SUCCESS");  /* 0x5ab441 */
        __builtin_trap();
    }
    FUN_0005ee58(words, 0, 0, 0);
    return 0;
}