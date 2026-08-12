/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0), Apple's code-signing / entitlement /
 * trust-cache / code-execution-policy authority. Ground truth: Ghidra FUN_
 * names + addresses in `txm.raw`. All names are estimates unless a string /
 * header name matches (confidence high). TXM = Trusted Execution Monitor GL0,
 * image base 0.
 *
 * This file covers the image4 / boot-manifest region 0x56000-0x60000 (batch
 * T6): the runtime callback dispatch table (0x576f0-0x57850,
 * txm_runtime_* entries), the image4 property-set accessors and constraint
 * enforcement engine (property tags 0x1d558/0x1d568/0x1d578/0x1d588/0x1d598),
 * the manifest/payload decode + trust-evaluation + anti-replay / odometer
 * machinery, the CoreEntitlements subset-equality checks (FUN_0005e374
 * family), and the entitlements-blob parser (FUN_0005fb88, magic "<?xm").
 *
 * Shared kernel/hardware deps are declared extern with a one-line note.
 */

#ifndef __ASSEMBLER__
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ */
/* Shared TXM runtime primitives (extern; bodies live in sibling files) */
/* ------------------------------------------------------------------ */

/* TXM console/panic writer: formats a message and halts the monitor.
 * FUN_00050d70; noreturn. */
extern void txm_panic_fmt(const char *fmt, ...);
/* TXM bounds/overflow panic (FUN_00029a3c); noreturn. */
extern void txm_panic_bounds(int code);
/* Stack-canary check tail (FUN_0002f13c); noreturn on mismatch. */
extern void txm_stack_check(void);
/* Panic printer used by the runtime-callback dispatcher (FUN_00029784). */
extern void txm_panic_call(const char *fmt, ...);

/* Per-CPU / process TXM context getters. */
extern uint64_t txm_percpu_state(void);         /* FUN_0005077c */
extern uint64_t txm_percpu_context(void);       /* FUN_0005078c */

/* "Optional not set" / "unreachable" panic helpers (FUN_0005a4d4/4ec/4fc). */
extern void txm_optional_not_set(void);
extern void txm_unreachable(void);

/* mem/str/format helpers. */
extern void   txm_snprintf(void *out, size_t cap, const char *fmt, ...);   /* FUN_0002eb44 */
extern void   txm_format_ident(void *out, const char *src, size_t n, uint64_t cap); /* FUN_0002efc4 */
extern void   txm_bzero(void *dst, size_t n);                              /* FUN_0002d240 */
extern int    txm_memcmp(const void *a, const void *b, size_t n);          /* FUN_0002d4d0 */
extern void   txm_memcpy(void *dst, const void *src, size_t n);            /* FUN_0002d6b0 */
extern size_t txm_strlen(const char *s);                                   /* FUN_0002dbe0 */
extern size_t txm_strnlen(const char *s, size_t max);                      /* FUN_0002dc80 */
extern int    txm_strncmp(const char *a, const char *b, size_t n);         /* FUN_0002d3c0 */
extern uint32_t txm_strtoul(const char *s, char **end, int base);          /* FUN_0002d990 */
extern uint64_t txm_hash_bytes(const void *p);                             /* FUN_0002abe4 */

/* Object alloc/free + CE log. */
extern void  *txm_alloc(size_t n);              /* FUN_00024f14 */
extern void   txm_free(void *p);                /* FUN_00029894 */
extern void   txm_ce_log(const char *fmt, ...); /* FUN_00025c6c */
extern void   txm_dictionary_iter_reset(void);  /* FUN_0002986c */

/* ASN.1 / DER decode + image4 property query (img4decode internals). */
extern int    txm_der_decode_item(uint64_t *data, uint64_t *out);       /* FUN_00044178 */
extern int    txm_decode_string(uint64_t *data, ...);                   /* FUN_0004443c */
extern int    txm_decode_int(uint64_t *data, ...);                      /* FUN_00044580 */
extern int    txm_der_dict_iter(uint64_t *d, uint64_t *out);            /* FUN_000446f4 */
extern int    txm_der_dict_next(uint64_t *d, uint64_t *out);            /* FUN_00044724 */
extern int    txm_get_property_oid(uint64_t obj, ...);                  /* FUN_0004507c */
extern int    txm_get_property_data(uint64_t obj, uint64_t *out);       /* FUN_00045034 */
extern int    txm_get_manifest_restore(uint64_t obj, ...);              /* FUN_000450dc */
extern int    txm_img4_query_property(uint64_t obj, uint32_t tag, ...); /* FUN_00045208 */
extern int    txm_img4_get_data(uint64_t obj, uint32_t tag, void **p, uint32_t *n); /* FUN_00045364 */
extern int    txm_encode_init_mode(void);                               /* FUN_00045418 */
extern void   txm_encode_payload(uint64_t a, uint64_t b, uint64_t c);   /* FUN_00045504/55a0 */
extern int    txm_decode_trust_eval(uint64_t a, ...);                   /* FUN_000456f8 */

/* Dictionary (DER plist) low-level parse helpers. */
extern int    txm_dict_find_key(uint64_t *it, uint32_t tag, uint64_t *out); /* FUN_00037304 */
extern int    txm_dict_len(uint64_t *it, uint64_t *out);                    /* FUN_000374a0 */
extern int    txm_dict_next(uint64_t *it, uint64_t *out);                   /* FUN_00037570 */
extern int    txm_dict_has_more(uint64_t *it, uint64_t *out);               /* FUN_00037584 */
extern int    txm_dict_elem(uint64_t *it, uint32_t tag, uint64_t *out);     /* FUN_0003767c */

/* Hash (SHA-2 / GCM-style) digest helpers. */
extern void   txm_sha256(uint64_t *state, uint64_t *out);  /* FUN_00038288 */
extern void   txm_sha_update_data(uint64_t *state, uint64_t *out, uint64_t a, uint64_t b); /* FUN_000385b8 */

/* Digest-object copy / hash helpers. */
extern void   txm_digest_copy(void *dst, const void *src);  /* FUN_0004ff74 */
extern void   txm_digest_set(const void *src, void *dst);   /* FUN_0004f8b0 */
extern void   txm_digest_import(void *dst, const void *src);/* FUN_0004f980 */
extern int    txm_hash_query(uint64_t tag, ...);            /* FUN_0004f9b8 */
extern int    txm_hash_query2(uint64_t tag, ...);           /* FUN_0004f9c8 */
extern void   txm_hash_combine(void *a, const void *b);     /* FUN_0004f948 */

/* Property / environment / img4decode object helpers. */
extern int    txm_env_query(void);                          /* FUN_00050420 */
extern uint64_t txm_env_get(uint64_t a);                    /* FUN_0005042c */
extern void   txm_property_set_init(uint64_t *d, ...);      /* FUN_00051c78 */
extern int    txm_cdhash_lookup(uint64_t a, ...);           /* FUN_00051bd0 */
extern int    txm_cdhash_lookup2(uint64_t a, ...);          /* FUN_00051b3c */
extern uint64_t txm_cdhash_resolve(uint64_t a);             /* FUN_00051ce0 */
extern uint64_t txm_cdhash_info(uint64_t a);                /* FUN_00051ccc */
extern int    txm_img4_init_payload(uint64_t a, ...);       /* FUN_00052318/522f4 */
extern void   txm_img4_copy_manifest(uint64_t a, uint64_t b, uint64_t c); /* FUN_000522d8 */
extern void   txm_img4_set_restore(uint64_t a, ...);        /* FUN_00052370 */
extern void   txm_img4_teardown(uint64_t a, uint64_t *out); /* FUN_000523a0/5244c */
extern int    txm_property_get_oid(uint64_t a, ...);        /* FUN_00052a34 */
extern int    txm_property_find(uint64_t a, ...);           /* FUN_00052a78 */
extern int    txm_property_check(uint64_t a, ...);          /* FUN_00052a88 */
extern uint64_t txm_env_level(uint64_t a);                  /* FUN_00052da8 */
extern uint32_t txm_parse_uint(uint64_t a, char **end, int base); /* FUN_00052fe4 */
extern uint64_t txm_digest_oid(uint64_t *it, uint64_t *fmt);/* FUN_00053070 */

/* img4decode manifest/payload property getters (foreign, not in this batch). */
extern int    txm_decode_get_manifest(uint64_t a, uint64_t *out, uint32_t *n); /* FUN_00061a34 */
extern int    txm_decode_copy_manifest_digest(uint64_t a, uint64_t *out, uint64_t n); /* FUN_00061960 */
extern int    txm_decode_copy_payload_digest(uint64_t a, uint64_t *out, uint64_t n);  /* FUN_00061880 */
extern int    txm_decode_get_bool(uint64_t a, uint32_t tag, void *out);   /* FUN_00061b48 */
extern int    txm_decode_get_int(uint64_t a, uint32_t tag, void *out);    /* FUN_00061a80 */
extern int    txm_decode_get_uint64(uint64_t a, uint32_t tag, void *out); /* FUN_00061ae4 */
extern int    txm_decode_trust_eval2(uint64_t a, uint64_t b, uint64_t c); /* FUN_00061e08 */

/* Debug breakpoint intrinsic (Ghidra `SoftwareBreakpoint`). */
extern void   txm_breakpoint(unsigned code, uint64_t addr);

#ifndef __ASSEMBLER__
/* Internal recreated-function forward declarations (ordering). */
bool txm_manifest_has_more_props(uint64_t obj);
bool txm_manifest_needs_restore(uint64_t key, uint64_t rec);
bool txm_manifest_restore_revalidate(uint64_t key, uint64_t rec);
bool txm_property_available(uint64_t prop, uint64_t set);
bool txm_property_match(uint64_t a, uint64_t b);
int txm_ce_bool_equal(uint64_t a, uint8_t expect);
int txm_enforce_digest64_constraint(uint64_t prop, uint64_t obj, uint64_t a, uint64_t b);
int txm_iter_is_entitlement(uint64_t p);
int txm_iter_is_manifest_profile(uint64_t p);
int txm_iter_is_payload_profile(uint64_t p);
int txm_iter_not_manifest(uint64_t p);
int txm_iter_not_payload(uint64_t p);
int64_t txm_iter_terminal(uint64_t p);
uint32_t * txm_property_get_uint32(uint32_t *obj, uint64_t prop, uint32_t *val);
uint32_t txm_boot_chain_integrity_check(uint64_t base, uint64_t *rec);
uint32_t txm_ce_alloc_valid(uint64_t obj);
uint32_t txm_ce_data_cmp(uint64_t a, uint64_t data, uint64_t len, int wildcard);
uint32_t txm_ce_data_equal(uint64_t a, uint64_t span);
uint32_t txm_ce_key_dict_wrap(int *a, uint64_t *ctx);
uint32_t txm_ce_key_lookup_cb(uint64_t a, uint64_t *ctx);
uint32_t txm_ce_key_lookup_cb_direct(uint64_t a);
uint32_t txm_dict_apply(uint64_t dict, uint64_t cb, uint64_t ctx);
uint32_t txm_enforce_bool_constraint(uint64_t prop, uint64_t obj, uint8_t *req, uint8_t *val);
uint32_t txm_enforce_uint32_constraint(uint64_t prop, uint64_t obj, uint32_t *req, uint32_t *val);
uint32_t txm_enforce_uint64_constraint(uint64_t prop, uint64_t obj, uint64_t *req, uint64_t *val);
uint32_t txm_entitlements_blob_parse(uint64_t ctx, uint32_t type, uint8_t *blob, uint64_t a, uint64_t b);
uint32_t txm_entitlements_parse(uint64_t blob, uint64_t *out);
uint32_t txm_errno_lookup(uint32_t idx);
uint32_t txm_odometer_minmax(uint64_t src, uint32_t min, uint32_t max);
uint32_t txm_property_tag(uint64_t p);
uint32_t txm_runtime_name_validate(char *name, uint64_t key);
uint64_t * txm_digest_import_obj(uint64_t *obj, uint64_t *len, uint64_t *desc);
uint64_t * txm_img4_decode_init_manifest(uint64_t *rec, uint64_t ctx, uint64_t restore);
uint64_t * txm_img4_decode_init_payload(uint64_t *rec, uint64_t ctx, uint64_t restore);
uint64_t * txm_img4_get_property_dispatch(uint64_t key, uint64_t obj, uint64_t tag, uint64_t rec);
uint64_t * txm_manifest_constraint_ctx(uint64_t *rec, uint64_t ctx, uint64_t profile);
uint64_t * txm_odometer_current(void);
uint64_t * txm_property_get_uint64(uint64_t *obj, uint64_t prop, uint64_t *val);
uint64_t * txm_range_normalize(uint64_t base, uint64_t len, uint32_t extra);
uint64_t * txm_type_property_table(void);
uint64_t * txm_type_singleton(void);
uint64_t txm_cdhash_lookup_dispatch(uint64_t base, int tag, int exp, uint64_t *out);
uint64_t txm_ce_alloc_free(uint64_t obj);
uint64_t txm_ce_alloc_sort(uint64_t obj);
uint64_t txm_ce_array_subset(int *a, uint64_t b);
uint64_t txm_ce_bool_get(uint64_t a, uint8_t *out);
uint64_t txm_ce_data_cmp_alt(uint64_t *a, uint64_t data, uint64_t len);
uint64_t txm_ce_data_get(uint64_t a, uint64_t *out);
uint64_t txm_ce_dict_match(uint64_t a, uint64_t b);
uint64_t txm_ce_dict_subset(uint64_t a, uint64_t b);
uint64_t txm_ce_key_apply(int *a, uint64_t ctx);
uint64_t txm_ce_key_array_elem(uint64_t a, uint64_t *ctx);
uint64_t txm_ce_key_copy(uint64_t *a, uint64_t *out);
uint64_t txm_ce_key_count(uint64_t a, uint64_t ctx);
uint64_t txm_ce_key_entitlement(uint64_t *a, uint64_t *ctx);
uint64_t txm_ce_key_lookup(uint64_t dict, uint64_t key, uint64_t *out);
uint64_t txm_ce_key_lookup2(uint64_t a, uint64_t *ctx);
uint64_t txm_ce_key_lookup_cb2(uint64_t a, uint64_t ctx);
uint64_t txm_ce_span_match(uint64_t a, uint64_t *span);
uint64_t txm_ce_subset(uint64_t a, uint64_t b);
uint64_t txm_ce_subset_key(uint64_t a, uint64_t b);
uint64_t txm_ce_type_code(uint64_t a, uint32_t *out);
uint64_t txm_context_available(void);
uint64_t txm_context_dispatch(uint8_t *ctx);
uint64_t txm_current_object(void);
uint64_t txm_decode_trust_eval(uint64_t *rec, uint64_t impl, uint64_t p3);
uint64_t txm_decode_trust_eval2(uint64_t *rec, uint64_t impl, uint64_t p3);
uint64_t txm_dict_apply_dict(uint64_t dict, uint64_t cb, uint64_t ctx);
uint64_t txm_dict_count(uint64_t dict, uint64_t *out);
uint64_t txm_dict_elem(uint64_t arr, uint64_t idx, uint64_t *out);
uint64_t txm_dict_next_value(uint64_t obj, uint64_t *key, uint64_t *span, uint64_t *span2, uint64_t *it);
uint64_t txm_dict_parse(uint64_t *iter, uint64_t span);
uint64_t txm_dict_parse_collection(uint64_t *iter, uint64_t span);
uint64_t txm_digest64_import(uint64_t obj, uint64_t a, uint32_t n);
uint64_t txm_digest_equal(uint64_t a, uint64_t b);
uint64_t txm_digest_oid_type(uint64_t *oid);
uint64_t txm_digest_set_bytes(uint64_t obj, uint64_t src, uint64_t n);
uint64_t txm_enforce_digest64_constraint_v(uint64_t *obj, uint64_t prop, uint64_t a, uint64_t b);
uint64_t txm_enforce_digest_constraint(uint64_t prop, uint64_t obj, uint64_t a, uint64_t b);
uint64_t txm_entitlements_dict_init(uint64_t obj, uint64_t *span, uint64_t *iter);
uint64_t txm_guest_count(void);
uint64_t txm_guest_index(void);
uint64_t txm_hex_cstr_length(uint64_t src, uint64_t out);
uint64_t txm_identifier_16byte(uint64_t obj, uint64_t ctx, uint64_t out);
uint64_t txm_identifier_from_cstr(uint64_t out, uint64_t src, uint64_t cap);
uint64_t txm_image4_cert_root_parse(uint64_t def, uint64_t data, uint64_t *out);
uint64_t txm_image4_cert_type(uint64_t obj, uint32_t *out);
uint64_t txm_impl_ctx_name(void);
uint64_t txm_impl_stub_bad(void);
uint64_t txm_impl_stub_ok(void);
uint64_t txm_impl_type_label(uint64_t a, uint64_t obj);
uint64_t txm_impl_vtable_dispatch(uint64_t impl, uint64_t op, uint64_t *out);
uint64_t txm_iterator_next(uint64_t *it);
uint64_t txm_manifest_decode_init(uint64_t *rec);
uint64_t txm_manifest_exec_policy_check(uint8_t *ctx, uint64_t arg2, uint64_t *arg3);
uint64_t txm_manifest_restore_lookup(uint64_t rec);
uint64_t txm_manifest_trust_evaluate(uint64_t *rec, uint64_t impl, uint64_t flag, uint64_t p4, uint64_t p5);
uint64_t txm_nonce_entangle(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t out);
uint64_t txm_nonce_equal(uint64_t a, uint64_t b);
uint64_t txm_nonce_set(uint64_t obj, uint64_t src, uint64_t n);
uint64_t txm_null_iter(void);
uint64_t txm_object_tag_check(uint64_t a, uint64_t tag);
uint64_t txm_odometer_chip_query(uint64_t *obj);
uint64_t txm_odometer_compare(uint64_t a, uint64_t b);
uint64_t txm_odometer_entangle_check(uint64_t base, uint64_t *rec);
uint64_t txm_odometer_query_nonce(uint64_t *obj, uint64_t ctx, int type, uint64_t out);
uint64_t txm_odometer_restore_bool(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src);
uint64_t txm_odometer_restore_digest3(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src);
uint64_t txm_odometer_restore_query(uint64_t *obj, uint64_t ctx, uint64_t out);
uint64_t txm_odometer_restore_type(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src);
uint64_t txm_odometer_restore_uint32(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src);
uint64_t txm_panic_unsupported_image4_cert(void);
uint64_t txm_parse_12byte(uint64_t obj, uint64_t *out, uint64_t span);
uint64_t txm_parse_18byte(uint64_t obj, uint64_t *out, uint64_t span);
uint64_t txm_parse_23byte(uint64_t obj, uint64_t *out, uint64_t span);
uint64_t txm_parse_4byte(uint64_t obj, uint64_t *out, uint64_t span);
uint64_t txm_parse_bool(uint64_t obj, uint64_t span);
uint64_t txm_parse_decimal(uint64_t obj, uint64_t *out, uint64_t span);
uint64_t txm_parse_entitlement(uint64_t obj, uint64_t *out, uint64_t span);
uint64_t txm_payload_decode_init(uint64_t *obj);
uint64_t txm_payload_init_manifest(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t restore);
uint64_t txm_payload_init_payload(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t restore);
uint64_t txm_payload_type_check(uint64_t *obj);
uint64_t txm_policy_bool_count(uint64_t obj, uint64_t ctx, int *out);
uint64_t txm_policy_impose(uint64_t *rec, uint64_t set, uint64_t key, uint64_t obj, uint64_t *ep);
uint64_t txm_policy_init(uint64_t *policy, uint64_t name, uint64_t impl, uint64_t ctx);
uint64_t txm_policy_prepare(uint64_t *policy);
uint64_t txm_policy_replay_check(uint64_t *policy);
uint64_t txm_policy_table_find(uint64_t policy, uint64_t *table, uint64_t n);
uint64_t txm_property_bool_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint8_t *out);
uint64_t txm_property_digest64_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t out);
uint64_t txm_property_digest_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t out);
uint64_t txm_property_get(uint64_t container, uint64_t prop);
uint64_t txm_property_get_bool_impl(uint64_t a, uint64_t b, uint8_t *out);
uint64_t txm_property_get_digest(uint64_t obj, uint64_t prop, uint64_t val);
uint64_t txm_property_get_digest64(uint64_t obj, uint64_t prop, uint64_t val);
uint64_t txm_property_get_uint32_impl(uint64_t a, uint64_t b, uint32_t *out);
uint64_t txm_property_get_uint64_impl(uint64_t a, uint64_t b, uint64_t *out);
uint64_t txm_property_impose_env(uint64_t obj, uint64_t set, uint64_t key);
uint64_t txm_property_override_lookup(uint64_t base, uint64_t prop, uint64_t *alt);
uint64_t txm_property_override_validate(uint64_t base, uint64_t prop);
uint64_t txm_property_set_by_tag(int *tag, int kind);
uint64_t txm_property_set_default(uint64_t set);
uint64_t txm_property_set_lookup(uint64_t container, uint64_t prop);
uint64_t txm_property_set_resolve(uint64_t set, uint64_t prop, uint64_t fallback);
uint64_t txm_property_uint32_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint32_t *out);
uint64_t txm_property_uint64_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t *out);
uint64_t txm_restore_constraint(uint8_t *obj, uint64_t ctx, uint64_t prop, uint64_t expect);
uint64_t txm_restore_info_batch(uint64_t obj, uint64_t rec, uint64_t prop, uint64_t src);
uint64_t txm_restore_info_impose(uint64_t obj, uint64_t rec, uint64_t prop, uint64_t src);
uint64_t txm_restore_info_impose2(uint64_t obj, uint64_t rec, uint64_t prop, uint64_t src);
uint64_t txm_restore_info_query(uint64_t *obj, uint64_t prop, uint64_t src, uint64_t out);
uint64_t txm_runtime_bad_id_a(void);
uint64_t txm_runtime_bad_id_b(void);
uint64_t txm_runtime_stub_null(void);
uint8_t * txm_property_get_bool(uint8_t *obj, uint64_t prop, uint8_t *val);
uint8_t txm_restore_info_bool(uint8_t *obj, uint64_t prop);
void txm_ce_cstr_match(uint64_t a, uint64_t s);
void txm_cpu_ctx_revalidate_a(void);
void txm_cpu_ctx_revalidate_b(void);
void txm_cpu_ctx_validate(void);
void txm_decode_impl_dispatch(uint64_t impl);
void txm_decode_manifest_if_mode(uint64_t a, uint64_t b, uint64_t c);
void txm_decode_payload_if_mode(uint64_t a, uint64_t b, uint64_t c);
void txm_digest64_copy_set(uint64_t *dst, uint64_t *src);
void txm_digest_copy_get(uint64_t src, uint64_t dst);
void txm_digest_copy_set(uint64_t dst, uint64_t src);
void txm_digest_export_32(uint64_t src, uint64_t dst, uint32_t *len);
void txm_digest_export_64(uint64_t src, uint64_t dst, uint64_t *len);
void txm_digest_import_copy(uint64_t obj, uint64_t out);
void txm_digest_import_dispatch(uint64_t obj, uint64_t arg);
void txm_digest_import_set(uint64_t obj, uint64_t key, uint64_t *out);
void txm_digest_release(uint64_t obj, uint64_t arg, uint64_t *out);
void txm_enforce_digest64_constraint2(uint64_t *obj, uint64_t prop);
void txm_entangle_nonce(uint64_t obj, uint64_t src, uint64_t manifest, uint64_t out);
void txm_env_query_thunk(void);
void txm_expert_tag_validate(uint64_t obj, uint32_t expect);
void txm_flag_manifest_hash_present(uint64_t obj);
void txm_flag_manifest_present(uint64_t obj);
void txm_flag_odometer_present(uint64_t obj, uint8_t v);
void txm_identifier_import_16(uint64_t obj, uint64_t *src);
void txm_image4_cert_root_parse_v(uint64_t def, uint64_t data, uint64_t *out);
void txm_img4_get_property_apply(uint64_t *obj, uint64_t reg, uint64_t tag, uint64_t rec);
void txm_impl_ctx_reval_a(void);
void txm_impl_ctx_reval_b(void);
void txm_impl_ctx_validate(void);
void txm_impl_stub_void(void);
void txm_log_level(uint64_t obj, uint64_t level);
void txm_manifest_digest_compute(uint64_t *rec, uint64_t impl, uint64_t out);
void txm_manifest_dump(uint64_t obj);
void txm_manifest_get_raw(uint64_t rec, uint64_t out);
void txm_manifest_hash_import(uint64_t obj, uint64_t *src);
void txm_manifest_payload_digest_release(uint64_t *rec);
void txm_manifest_record_release(uint64_t *rec);
void txm_manifest_restore_release(uint64_t *rec);
void txm_manifest_trust_eval_call(void);
void txm_nonce_copy_set(uint64_t dst, uint64_t src);
void txm_odometer_restore_digest(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src);
void txm_odometer_restore_digest2(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src);
void txm_optional_not_set(void);
void txm_panic_failed_resolve_expert(void);
void txm_panic_guest_unavailable(void);
void txm_panic_illegal_chip_config(void);
void txm_panic_illegal_odometer_consumption(void);
void txm_panic_no_anti_replay_policy(void);
void txm_panic_no_guests(void);
void txm_payload_digest_compute(uint64_t *rec, uint64_t impl, uint64_t out);
void txm_payload_digest_get(uint64_t obj, uint64_t out);
void txm_payload_digest_get_v(uint64_t obj, uint64_t out);
void txm_payload_get_raw(uint64_t obj, uint64_t out);
void txm_payload_init_core(uint64_t *obj, uint64_t prop, uint64_t ctx);
void txm_payload_set_range(uint64_t obj, uint64_t base, uint64_t len);
void txm_percpu_ctx_reval_a(void);
void txm_percpu_ctx_reval_b(void);
void txm_percpu_ctx_validate2(void);
void txm_percpu_state_thunk(void);
void txm_policy_any_bool(uint64_t obj, uint64_t ctx, uint64_t out);
void txm_property_entropy_resolve(uint64_t obj, uint64_t src, uint64_t arg);
void txm_property_set_bool(uint8_t *obj, uint64_t prop, uint8_t *val);
void txm_property_set_digest(uint64_t obj, uint64_t prop, uint64_t val);
void txm_property_set_digest64(uint64_t obj, uint64_t prop, uint64_t val);
void txm_property_set_uint32(uint32_t *obj, uint64_t prop, uint32_t *val);
void txm_property_set_uint64(uint64_t *obj, uint64_t prop, uint64_t *val);
void txm_query_anchor(uint64_t obj);
void txm_record_attach(uint64_t rec, uint64_t ctx, uint64_t propset);
void txm_runtime_alloc_type(void);
void txm_runtime_chain_panic(void);
void txm_runtime_copy_nonce(void);
void txm_runtime_dealloc_type(void);
void txm_runtime_get_identifier_bool(void);
void txm_runtime_get_identifier_cstr(void);
void txm_runtime_get_identifier_digest(void);
void txm_runtime_get_identifier_uint(void);
void txm_runtime_get_identifier_uint2(void);
void txm_runtime_log(void);
void txm_runtime_log_handle(void);
void txm_runtime_roll_nonce(void);
void txm_runtime_set_nonce(void);
void txm_runtime_stub_void(void);
void txm_snprintf_var(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
void txm_store_tag_swapped(uint32_t *rec, uint32_t tag);
void txm_store_tag_swapped_ptr(uint64_t rec, uint32_t *tag);
void txm_trust_eval_record(uint64_t *rec, int rc, uint64_t eval);
void txm_unreachable(void);
void txm_vtable_dispatch_100(uint64_t obj);
void txm_vtable_dispatch_20(uint64_t obj);
void txm_vtable_dispatch_28(uint64_t obj);
void txm_vtable_dispatch_78(uint64_t obj);
void txm_vtable_dispatch_80(uint64_t obj);
void txm_vtable_dispatch_80_ctx_a(void);
void txm_vtable_dispatch_80_ctx_b(void);
void txm_vtable_dispatch_88(uint64_t obj);
void txm_vtable_dispatch_90(uint64_t obj);
void txm_vtable_dispatch_98(uint64_t obj);
void txm_vtable_dispatch_a0(uint64_t obj);
void txm_vtable_dispatch_b0(uint64_t obj);
void txm_vtable_dispatch_b8(uint64_t obj);
void txm_vtable_dispatch_f0(uint64_t obj);
void txm_vtable_dispatch_f8(uint64_t obj);
#endif /* __ASSEMBLER__ */

/* ------------------------------------------------------------------ */
/* Globals referenced by this region (addresses from Ghidra) */
/* ------------------------------------------------------------------ */
extern uint64_t txm_canary;          /* DAT_00006cf0 stack canary */

#endif /* __ASSEMBLER__ */
/* ============================================================================
 * FUN_0005602c @ 0x0005602c  (est. txm_manifest_exec_policy_check)
 * Ghidra: long FUN_0005602c(byte *param_1, undefined8 param_2, undefined8 *param_3)
 * Entry point of the code-region execution-policy evaluation: resolves the
 * per-CPU context (param_1[1] via FUN_0005652c), loads the boot-manifest
 * profile into a local record (0x1c570), and drives the manifest-identity
 * (mix-n-match id) and manifest-hash queries, then imposes the boot-chain
 * constraints (FUN_0005979c / FUN_000598b0 / FUN_000598bc / FUN_00059a54).
 * Returns an error/status code (0 success, 0x55 rejected, >0x6b panics).
 * Confidence: medium
 * Notes: string refs 0x503b "failed to query mix_n_match identity",
 *   0x5066 "failed to query manifest hash id"; runs the odometer/anti-replay
 *   stage gates. */
static uint64_t
txm_manifest_exec_policy_check(uint8_t *ctx, uint64_t arg2, uint64_t *arg3)
{
    uint64_t rc;
    uint64_t obj;
    uint64_t *profile;
    uint8_t *p;
    uint64_t saved = txm_canary;

    profile = (uint64_t *)arg3;
    obj = txm_percpu_state();                  /* FUN_0005652c(ctx[8]) */
    if (obj == 0)
        obj = txm_percpu_state();              /* FUN_0005077c */
    (void)0;                                   /* local_d0 init / 0x1c570 record memset */
    /* Local boot profile record (structure at 0x1c570) zeroed by caller. */
    if (obj == 0) {
        txm_panic_fmt("failed to resolve expert function");   /* FUN_000564b8 */
    } else if ((*(uint64_t *)(ctx + 0x30) == 0) || ((*ctx >> 1 & 1) != 0) ||
               (int)txm_env_query() == 0) {    /* thunk_FUN_0005abf4 */
        uint64_t chain = *(uint64_t *)(ctx + 0x270);
        if (chain == 0) {
            if (*(int16_t *)(*(uint64_t *)(ctx + 0x30) + 0x58) == 0) {
                txm_optional_not_set();        /* FUN_00051c78 + canary */
                p = (uint8_t *)*profile;
                obj = txm_percpu_state();
                if (obj == 0)
                    obj = txm_percpu_state();
                uint64_t info = profile[1];
                uint32_t flags = (uint32_t)*(uint64_t *)p;
                if ((flags >> 2 & 1) == 0) {
                    if (profile[2] != 0) {
                        obj = 0;
                    }
                    if ((flags >> 3 & 1) != 0) {
                        obj = 0;
                    }
                    if ((*(uint64_t *)(info + 0x18) == 1) && (*(uint64_t *)(info + 0x10) == 1)) {
                        obj = 0;
                    }
                } else {
                    /* Mix-n-match manifest identity + hash query path. */
                    if (p + 0x4d8 <= p)
                        txm_panic_bounds(0x19);
                    uint64_t id = *(uint64_t *)(p + 8);
                    obj = txm_percpu_state();
                    if (obj == 0)
                        obj = txm_percpu_state();
                    if (txm_percpu_state()) {   /* FUN_00056578 nonzero check */
                        int r = 0;              /* FUN_0004f9b8(id, info, 0xc, local) */
                        if (r == 0)
                            txm_panic_fmt("mixed");   /* simplified: only on query fail */
                    }
                    id = *(uint64_t *)(p + 8);
                    obj = txm_percpu_state();
                    if (obj == 0)
                        obj = txm_percpu_state();
                    /* zero 0x118-byte manifest hash query block, then */
                    if (txm_percpu_state()) {   /* FUN_00056578 */
                        int r = 0;              /* FUN_0004f9c8(id, info, 0xb, &block) */
                        if (r == 0) {
                            /* FUN_0004f948/FUN_00057ca8/FUN_0005c830 */
                        } else {
                            txm_panic_fmt("manifest hash query failed");
                        }
                    }
                    obj = 0;                    /* FUN_0005c820 */
                }
                if ((*(uint64_t *)(p + 0x30) == 0) && ((*p >> 5 & 1) == 0)) {
                    obj = 0;                    /* FUN_0005c858 */
                }
                if (*(uint64_t *)(info + 0xd0) == 0) {
                    obj = 0;                    /* FUN_0005c810 */
                }
                *(uint32_t *)(profile + 0xd) = 0;
                if (txm_canary == saved)
                    return obj;
                txm_stack_check();
            }
            uint64_t r = txm_manifest_constraint_ctx(ctx + 0x278, obj, *(uint64_t *)(ctx + 0x30) + 0x30); /* FUN_0005979c */
            rc = (r == 0) ? 0 : 0;
            /* local_d0 = r */
        } else {
            rc = 0;
        }
        /* FUN_000598b0(chain,&stack,&local); FUN_0004f980(&local,arg3); */
        if (arg3 != 0) {
            profile = (uint64_t *)arg3;
        }
        int s = 0;                              /* FUN_000598bc */
        uint64_t l4 = 0;
        if (s == 0) {
            l4 = 0;                             /* FUN_00059a54(chain, arg2, ctx[0x30], 0) */
        } else {
            l4 = 0x4f;
        }
        rc = l4;
        if (rc == 0x55)
            rc = 8;
        else if (rc > 0x6b)
            txm_panic_fmt("panic: error not set to valid po");   /* FUN_00050d70 */
        if (txm_canary == saved)
            return rc;
    }
    txm_stack_check();
    return 0; /* unreachable */
}

/* ============================================================================
 * FUN_0005642c @ 0x0005642c  (est. txm_manifest_record_release)
 * Ghidra: void FUN_0005642c(long *param_1)
 * Releases a manifest execution-policy record: tears down the boot-chain and
 * property-set sub-records (FUN_00059fe8/5ad14), copies the two digest
 * records back (FUN_0004f8b0), and clears the context association
 * (FUN_00057f38). */
static void
txm_manifest_record_release(uint64_t *rec)
{
    uint64_t l3 = *rec;
    if (l3 != 0) {
        uint64_t id = *(uint64_t *)(l3 + 8);
        uint64_t state = txm_percpu_state();
        uint64_t a = l3 + 0x498, b = l3 + 0x4b8;
        txm_manifest_payload_digest_release(l3 + 0x270);   /* FUN_00059fe8 */
        txm_manifest_restore_release(l3 + 0x30);           /* FUN_0005ad14 */
        txm_digest_set(id, &a);                            /* FUN_0004f8b0 */
        txm_digest_set(id, &b);
        txm_digest_release(state, *(uint64_t *)(l3 + 0x10), rec); /* FUN_00057f38 */
    }
}

/* ============================================================================
 * FUN_000564b8 @ 0x000564b8  (est. txm_panic_failed_resolve_expert)
 * Ghidra: void FUN_000564b8(void) — noreturn panic wrapper. */
static void
txm_panic_failed_resolve_expert(void)
{
    txm_panic_fmt("panic: failed to resolve expert f");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_000564d8 / FUN_000564dc @ 0x000564d8/0x564dc  (est. txm_cpu_ctx_revalidate)
 * Ghidra: void FUN_000564d8/0x564dc(void) — obtain per-CPU context, PAC-check
 *   the return address (SoftwareBreakpoint(0xc471) on mismatch), then run the
 *   per-CPU context validation (FUN_00054848). */
static void
txm_cpu_ctx_revalidate_a(void)
{
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    (void)txm_percpu_state();
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x564fc);
    /* FUN_00054848 */
}
static void
txm_cpu_ctx_revalidate_b(void)
{
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    (void)txm_percpu_state();
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x564fc);
    /* FUN_00054848 */
}

/* ============================================================================
 * FUN_00056500 @ 0x00056500  (est. txm_cpu_ctx_validate)
 * Ghidra: void FUN_00056500(void) — capture per-CPU ctx, validate via
 *   FUN_000548a8. */
static void
txm_cpu_ctx_validate(void)
{
    uint64_t ctx = txm_percpu_state();
    /* FUN_000548a8(&ctx) */
}

/* ============================================================================
 * FUN_0005652c @ 0x0005652c  (est. txm_context_dispatch)
 * Ghidra: undefined8 FUN_0005652c(undefined *param_1)
 * If param_1 is the known runtime context block (DAT_0001d350), invoke its
 * dispatch function at +0x58 and return its result; otherwise 0. */
static uint64_t
txm_context_dispatch(uint8_t *ctx)
{
    if (ctx == (uint8_t *)0x1d350) {
        return ((uint64_t (*)(void))(*(uint64_t *)(ctx + 0x58)))();
    }
    return 0;
}

/* ============================================================================
 * FUN_00056578 @ 0x00056578  (est. txm_context_available)
 * Ghidra: undefined8 FUN_00056578(void) — always returns 0 (context flag
 *   query stub). */
static uint64_t
txm_context_available(void)
{
    return 0;
}

/* ============================================================================
 * FUN_00056584 @ 0x00056584  (est. txm_cdhash_lookup_dispatch)
 * Ghidra: undefined8 FUN_00056584(long param_1,int param_2,int param_3,undefined8 *param_4)
 * Dispatches a code-signing lookup by fourcc tag (param_2): "apdc"/"vpdc"/
 * "apc0"/"dvdi"/"pdmg" etc. via the per-type helpers; falls back to scanning
 * the association table at param_1+0x18 (count at +0x28). Returns 0 on match
 * (writes param_4), 2 on miss. */
static uint64_t
txm_cdhash_lookup_dispatch(uint64_t base, int tag, int exp, uint64_t *out)
{
    if (tag < 0x61706463) {
        if (tag == 0) {
            return txm_cdhash_lookup(base, exp, out);       /* FUN_00051bd0 */
        }
        if (tag != 0x61706330) {
            /* generic table scan */
            if (*(uint64_t *)(base + 0x28) == 0)
                return 2;
            uint64_t n = 0;
            for (;;) {
                uint64_t e = *(uint64_t *)(*(uint64_t *)(base + 0x18) + n * 8);
                int *pi = (int *)txm_cdhash_resolve(e);      /* FUN_00051ce0 */
                int key = *pi;
                int alt = (*(int **)(pi + 0x16) != 0) ? **(int **)(pi + 0x16) : key;
                uint64_t info = txm_cdhash_info(e);          /* FUN_00051ccc */
                if (((tag == key || tag == alt)) && (*(int *)(info + 0x30) == exp))
                    break;
                n++;
                if (*(uint64_t *)(base + 0x28) <= n)
                    return 2;
            }
            *out = *(uint64_t *)(*(uint64_t *)(base + 0x18) + n * 8);
            return 0;
        }
        /* "apc0" -> "dvdi" */
        return txm_cdhash_lookup2(base, 0x64766469, out);    /* FUN_00051b3c */
    } else {
        if ((tag != 0x61706463) && (tag != 0x76706463))
            goto scan;
        return txm_cdhash_lookup2(base, 0x70646d67, out);    /* "pdmg" */
    }
scan:
    {
        if (*(uint64_t *)(base + 0x28) == 0)
            return 2;
        uint64_t n = 0;
        for (;;) {
            uint64_t e = *(uint64_t *)(*(uint64_t *)(base + 0x18) + n * 8);
            int *pi = (int *)txm_cdhash_resolve(e);
            int key = *pi;
            int alt = (*(int **)(pi + 0x16) != 0) ? **(int **)(pi + 0x16) : key;
            uint64_t info = txm_cdhash_info(e);
            if (((tag == key || tag == alt)) && (*(int *)(info + 0x30) == exp))
                break;
            n++;
            if (*(uint64_t *)(base + 0x28) <= n)
                return 2;
        }
        *out = *(uint64_t *)(*(uint64_t *)(base + 0x18) + n * 8);
        return 0;
    }
}

/* ============================================================================
 * FUN_000565f8 @ 0x000565f8  (est. txm_object_tag_check)
 * Ghidra: undefined8 FUN_000565f8(undefined8 param_1,long param_2)
 * Returns 0x60 if param_2 is not the expected boot-profile tag 0x1d240, else
 * bounds-panics. */
static uint64_t
txm_object_tag_check(uint64_t a, uint64_t tag)
{
    if (tag != 0x1d240)
        return 0x60;
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_00056628 @ 0x00056628  (est. txm_null_iter)
 * Ghidra: undefined8 FUN_00056628(void) — empty iterator sentinel. */
static uint64_t
txm_null_iter(void)
{
    return 0;
}

/* ============================================================================
 * FUN_00056634 @ 0x00056634  (est. txm_iter_is_manifest_profile)
 * Ghidra: int FUN_00056634(long param_1) — true iff tag == 0x1d608. */
static int
txm_iter_is_manifest_profile(uint64_t p)
{
    return -(int)(*(uint64_t *)(p + 0x30) == 0x1d608);
}

/* ============================================================================
 * FUN_00056650 @ 0x00056650  (est. txm_iter_is_payload_profile)
 * Ghidra: int FUN_00056650(long param_1) — true iff tag != 0x1d5f8. */
static int
txm_iter_is_payload_profile(uint64_t p)
{
    return -(int)(*(uint64_t *)(p + 0x30) != 0x1d5f8);
}

/* ============================================================================
 * FUN_0005666c @ 0x0005666c  (est. txm_iter_not_manifest)
 * Ghidra: int FUN_0005666c(long param_1) — true iff +0x38 != 0. */
static int
txm_iter_not_manifest(uint64_t p)
{
    return -(int)(*(int *)(p + 0x38) != 0);
}

/* ============================================================================
 * FUN_00056680 @ 0x00056680  (est. txm_iter_not_payload)
 * Ghidra: int FUN_00056680(long param_1) — true iff +0x38 != 1. */
static int
txm_iter_not_payload(uint64_t p)
{
    return -(int)(*(int *)(p + 0x38) != 1);
}

/* ============================================================================
 * FUN_00056694 @ 0x00056694  (est. txm_iter_terminal)
 * Ghidra: long FUN_00056694(long param_1) — sign bit of +0x40 (iterator
 *   end marker). */
static int64_t
txm_iter_terminal(uint64_t p)
{
    return (int64_t)(*(int64_t *)(p + 0x40)) >> 63;
}

/* ============================================================================
 * FUN_000566a4 @ 0x000566a4  (est. txm_iter_is_entitlement)
 * Ghidra: int FUN_000566a4(long param_1) — true iff +0x10 == 0x22. */
static int
txm_iter_is_entitlement(uint64_t p)
{
    return -(int)(*(uint64_t *)(p + 0x10) == 0x22);
}

/* ============================================================================
 * FUN_000566b8 @ 0x000566b8  (est. txm_iterator_next)
 * Ghidra: undefined8 FUN_000566b8(undefined8 *param_1)
 * Generic bounded iterator: param_1[2] is the index (starts at -1), param_1[0]
 * is an optional custom "get" callback (default FUN_00056628), param_1[1] is
 * the element table base (DAT_0001cf30). Advances until a callback returns 0
 * or the 0x27-slot bound is reached; records result in param_1[1]. */
static uint64_t
txm_iterator_next(uint64_t *it)
{
    uint64_t idx = it[2] + 1;
    if (idx == 0x27) {
        return 0;
    }
    if ((int64_t)it[2] < -1)
        txm_panic_fmt("panic: iteration underflow: idx");   /* FUN_00050d70 */
    if (0x27 < idx)
        txm_panic_fmt("panic: iteration overflow: idx");
    uint64_t (*get)(uint64_t) = txm_null_iter;             /* FUN_00056628 */
    if (it[0] != 0)
        get = (uint64_t (*)(uint64_t))it[0];
    for (;;) {
        uint64_t e = *(uint64_t *)(0x1cf30 + idx * 8);
        int r = get(e);
        if (r == 0) {
            it[1] = e;
            it[2] = idx;
            return e;
        }
        idx++;
        if (idx == 0x27)
            break;
    }
    it[1] = 0;
    it[2] = idx;
    return 0;
}

/* ============================================================================
 * FUN_00056794 @ 0x00056794  (est. txm_manifest_restore_revalidate)
 * Ghidra: bool FUN_00056794(undefined8 param_1,long param_2)
 * Re-validates a restored manifest record: resolves the backing property set
 * and, if present, enforces the restore-info + boot-chain constraint
 * (FUN_00059980 + FUN_0005c230). Returns true when no violation. */
static bool
txm_manifest_restore_revalidate(uint64_t key, uint64_t rec)
{
    uint64_t ps = *(uint64_t *)(rec + 0x10);
    uint64_t obj = txm_property_get_oid(key, ps);   /* FUN_00052a34 */
    if (obj != 0) {
        if (*(uint64_t *)(ps + 0xd8) == 0) {
            if (ps < ps + 0x110)
                txm_panic_fmt("illegal chip configuration");   /* FUN_000569f8 */
            txm_panic_bounds(0x19);
        }
        uint64_t r = txm_manifest_restore_lookup(*(uint64_t *)(rec + 8)); /* FUN_00059980 */
        if ((r == 0) && (*(int16_t *)(rec + 0x3c0) != 0) && (*(int16_t *)(rec + 0x360) != 0)) {
            int v = txm_restore_constraint(rec, key, *(uint64_t *)(ps + 0xd8), rec + 0x2f8); /* FUN_0005c230 */
            return v != 0;
        }
    }
    return true;
}

/* ============================================================================
 * FUN_00056834 @ 0x00056834  (est. txm_odometer_entangle_check)
 * Ghidra: ulong FUN_00056834(long param_1,undefined8 *param_2)
 * Odometer anti-replay check: queries the chip entropy (FUN_0005c0cc) and the
 * mix-n-match identity (FUN_00058fa0), entangles the nonce (FUN_0005bd78) and
 * enforces the boot-chain constraint (FUN_0005b7f0). Returns error code;
 * panics on invalid (>0x6b). Logs "failed to entangle"/"anti-replay violation"
 * / "failed to query". */
static uint64_t
txm_odometer_entangle_check(uint64_t base, uint64_t *rec)
{
    uint64_t saved = txm_canary;
    uint64_t name = *rec;
    uint64_t obj = txm_property_get_oid(base, rec[2]);       /* FUN_00052a34 */
    if (*(int16_t *)(rec + 0x78) == 0) {
        txm_optional_not_set();                              /* FUN_00051c78 */
        goto fail;
    }
    uint64_t ps = rec[2];
    uint32_t type = *(uint32_t *)(rec + 0x6d);
    uint64_t e1 = 0, e2 = 0, ent = 0;
    uint64_t rc = txm_odometer_query_nonce(rec, base, type, &ent);  /* FUN_0005c0cc */
    if ((int)rc == 0) {
        rc = txm_mix_match_query(name, ps, type, &ent, &e1);        /* FUN_00058fa0 */
        if ((int)rc != 0) {
            uint64_t m = *rec;
            txm_optional_not_set();                                /* FUN_00042b84 */
            txm_panic_fmt("odometer: failed to entangle");         /* FUN_000585b8 */
            rc = *(uint32_t *)(base + 0x18);
            if (rc > 0x6b)
                txm_panic_fmt("panic: error not set to valid po");
        } else {
            txm_entangle_nonce(name, ps, &e1, &ent);               /* FUN_0005bd78 */
            int v = txm_enforce_digest_constraint(obj, name, rec + 0x6e, &ent); /* FUN_0005b7f0 */
            if (v != 0) {
                rc = *(uint32_t *)(base + 0x18);
                uint64_t m = *rec;
                txm_optional_not_set();
                txm_panic_fmt("odometer: anti-replay violation");
                if (rc > 0x6b)
                    txm_panic_fmt("panic: error not set to valid po");
            } else {
                rc = 0;
            }
        }
    } else {
        uint64_t m = *rec;
        txm_optional_not_set();
        txm_panic_fmt("odometer: failed to query");
        if (rc > 0x6b)
            txm_panic_fmt("panic: error not set to valid po");
    }
    if (txm_canary == saved)
        return rc;
fail:
    txm_stack_check();
    return 0;
}

/* ============================================================================
 * FUN_000569f8 @ 0x000569f8  (est. txm_panic_illegal_chip_config)
 * Ghidra: void FUN_000569f8(void) — noreturn panic. */
static void
txm_panic_illegal_chip_config(void)
{
    txm_optional_not_set();
    txm_panic_fmt("panic: illegal chip configuratio");
}

/* ============================================================================
 * FUN_00056a1c @ 0x00056a1c  (est. txm_image4_cert_root_parse)
 * Ghidra: undefined8 FUN_00056a1c(long param_1,undefined8 param_2,undefined8 *param_3)
 * Resolves and parses the image4 certificate root from the chip definition
 * (param_1+0x20). Selects the root slot by the resolved cert type
 * (FUN_00058e9c); for type>=2 walks the anchor chain via DERDecodeItem
 * (FUN_00044178) and extracts the root (FUN_00057a30 + FUN_00047ba0). Logs
 * "failed to parse root %d"/"DERDecodeItem %d"/"failed to query anchor 0x%lx". */
static uint64_t
txm_image4_cert_root_parse(uint64_t def, uint64_t data, uint64_t *out)
{
    uint32_t type = 0;
    if (*(uint64_t *)(def + 0x20) == 0)
        txm_panic_fmt("panic: illegal chip definition: no");
    int r = txm_image4_cert_type(data, &type);          /* FUN_00058e9c */
    if (r != 0)
        txm_panic_fmt("panic: cannot resolve image4 cer");
    if (type < 2)
        return *(uint64_t *)(*(uint64_t *)(def + 0x20) + (uint64_t)type * 8);
    uint64_t saved = txm_canary;
    uint64_t chip = txm_panic_unsupported_image4_cert();   /* FUN_00056e70 */
    if (*(uint64_t *)(chip + 0x20) != 0)
        txm_panic_fmt("panic: illegal chip definition: t");
    uint64_t a = 0, b = 0;
    int q = txm_query_anchor(chip, *(uint64_t *)(chip + 0x38), chip, &a, &b); /* FUN_00058fc0 */
    if (q == 0) {
        uint64_t root = ((uint64_t (*)(void))(*(uint64_t *)(chip + 0x30)))();
        uint64_t base = *(uint64_t *)(root + 0x18);
        uint64_t len = *(uint64_t *)(root + 0x20);
        if (len + base < len)
            txm_panic_bounds(0x19);
        uint64_t der = 0;
        /* FUN_0004ff74(&der) */
        int d = txm_der_decode_item(&len, &der);        /* FUN_00044178 */
        if (d == 0) {
            /* FUN_0004ff74 */
            uint64_t oid = txm_digest_oid_type(&der);   /* FUN_00057a30 */
            int p = txm_parse_root(a, b, oid, 0, out);  /* FUN_00047ba0 */
            if (p == 0) {
                return *out;
            }
            txm_panic_fmt("failed to parse root %d");
        } else {
            txm_panic_fmt("DERDecodeItem %d");
        }
    } else {
        txm_panic_fmt("failed to query anchor 0x%lx");
    }
    if (txm_canary == saved)
        return 0;
    txm_stack_check();
    return 0;
}

/* ============================================================================
 * FUN_00056aa4 @ 0x00056aa4  (est. txm_image4_cert_root_parse_v)
 * Ghidra: void FUN_00056aa4(long param_1,undefined8 param_2,undefined8 *param_3)
 * Variant of FUN_00056a1c reading the chip definition from param_1 directly
 * (param_1+0x38 as the query anchor) and writing the parsed root into
 * param_3. */
static void
txm_image4_cert_root_parse_v(uint64_t def, uint64_t data, uint64_t *out)
{
    uint64_t saved = txm_canary;
    uint64_t a = 0, b = 0;
    if (*(uint64_t *)(def + 0x20) != 0)
        txm_panic_fmt("panic: illegal chip definition: t");
    int q = txm_query_anchor(data, *(uint64_t *)(def + 0x38), def, &a, &b);
    if (q == 0) {
        uint64_t root = ((uint64_t (*)(void))(*(uint64_t *)(def + 0x30)))();
        uint64_t base = *(uint64_t *)(root + 0x18);
        uint64_t len = *(uint64_t *)(root + 0x20);
        if (len + base < len)
            txm_panic_bounds(0x19);
        uint64_t der = 0;
        int d = txm_der_decode_item(&len, &der);
        if (d == 0) {
            uint64_t oid = txm_digest_oid_type(&der);
            int p = txm_parse_root(a, b, oid, 0, out);
            if (p == 0)
                return;
            txm_panic_fmt("failed to parse root %d");
        } else {
            txm_panic_fmt("DERDecodeItem %d");
        }
    } else {
        txm_panic_fmt("failed to query anchor 0x%lx");
    }
    if (txm_canary == saved)
        return;
    txm_stack_check();
}

/* ============================================================================
 * FUN_00056c3c @ 0x00056c3c  (est. txm_property_set_lookup)
 * Ghidra: ulong FUN_00056c3c(long param_1,long param_2)
 * Looks up a property set in the property container for a given property
 * (param_2). Branches on the property type tag (param_1+0x10): type 1 resolves
 * through FUN_00056e90, otherwise returns the container base if its element
 * count (param_2+0x50) is satisfied. */
static uint64_t
txm_property_set_lookup(uint64_t container, uint64_t prop)
{
    uint64_t result = txm_env_query();          /* FUN_00050420 */
    if (result == 0)
        return 0;
    uint64_t tag = txm_env_get(container);      /* FUN_0005042c */
    uint64_t count = *(uint64_t *)(container + 0x10);
    uint64_t base = result + 0x118;
    if (1 < count - 2 && count != 0) {
        if (count != 1) {
            txm_panic_fmt("panic: unreachable case %s 0x");  /* FUN_00050d70 */
        }
        uint64_t r = txm_property_get(tag, prop);            /* FUN_00056e90 */
        if (r != 0)
            base = result + 0x118;
        result = (r != 0) ? result : 0;
        count = *(uint64_t *)(container + 0x10);
    }
    if (count < *(uint64_t *)(prop + 0x50))
        return 0;
    if ((result != 0) && (base <= result))
        txm_panic_bounds(0x19);
    return result;
}

/* ============================================================================
 * FUN_00056d00 @ 0x00056d00  (est. txm_property_set_resolve)
 * Ghidra: long FUN_00056d00(long param_1,undefined8 param_2,long param_3)
 * Resolves the active property set: prefers the override at param_1+0x108 if
 * present, else the chip default (DAT_0001c848); then validates via
 * FUN_0005b134 / FUN_00056c3c. Returns the selected set (default param_3). */
static uint64_t
txm_property_set_resolve(uint64_t set, uint64_t prop, uint64_t fallback)
{
    if (set != 0) {
        uint64_t def = 0x1c848;
        if (*(uint64_t *)(set + 0x108) != 0)
            def = *(uint64_t *)(set + 0x108);
        uint64_t r = txm_property_match(prop, def);          /* FUN_0005b134 */
        if (((r & 1) == 0) && (txm_property_set_lookup(set, prop) != 0))
            fallback = txm_property_set_lookup(set, prop);
    }
    return fallback;
}

/* ============================================================================
 * FUN_00056d6c @ 0x00056d6c  (est. txm_property_set_default)
 * Ghidra: undefined * FUN_00056d6c(long param_1)
 * Returns the chip default property set (param_1+0x108 if set, else
 * DAT_0001c848). */
static uint64_t
txm_property_set_default(uint64_t set)
{
    if (*(uint64_t *)(set + 0x108) != 0)
        return *(uint64_t *)(set + 0x108);
    return 0x1c848;
}

/* ============================================================================
 * FUN_00056d88 @ 0x00056d88  (est. txm_property_override_lookup)
 * Ghidra: long FUN_00056d88(long param_1,long param_2,long *param_3)
 * Looks up a property override by tag index (param_2+0x10): first in
 * param_1+0x40 (0x22-entry override table), then in the caller's override
 * table param_3. Bounds-checked against 0x22 entries. */
static uint64_t
txm_property_override_lookup(uint64_t base, uint64_t prop, uint64_t *alt)
{
    uint64_t idx = *(uint64_t *)(prop + 0x10);
    if (idx == 0x22)
        return prop;
    uint64_t *table = *(uint64_t **)(base + 0x40);
    if (table != 0) {
        if (table + idx >= table + 0x22 || table + idx < table)
            txm_panic_bounds(0x19);
        if (table[idx] != 0)
            return table[idx];
    }
    if (alt != 0) {
        if (alt + idx >= alt + 0x22 || alt + idx < alt)
            txm_panic_bounds(0x19);
        if (alt[idx] != 0)
            return alt[idx];
    }
    return prop;
}

/* ============================================================================
 * FUN_00056e00 @ 0x00056e00  (est. txm_decode_impl_dispatch)
 * Ghidra: void FUN_00056e00(long param_1) — indirect jump through +0x28
 *   (decode-implementation dispatcher). */
static void
txm_decode_impl_dispatch(uint64_t impl)
{
    ((void (*)(void))(*(uint64_t *)(impl + 0x28)))();
}

/* ============================================================================
 * FUN_00056e10 @ 0x00056e10  (est. txm_property_override_validate)
 * Ghidra: undefined8 FUN_00056e10(long param_1,undefined8 param_2)
 * Scans the 5 override slots at param_1+0x80..+0xa0 (stride 8); returns 0 if
 * a slot validates via FUN_0005b134 (matches param_2), else 0xffffffff. */
static uint64_t
txm_property_override_validate(uint64_t base, uint64_t prop)
{
    uint64_t i = 0;
    for (;;) {
        if (*(uint64_t *)(base + 0x80 + i) == 0)
            return 0xffffffff;
        if (txm_property_match(prop, *(uint64_t *)(base + 0x80 + i)) != 0)  /* FUN_0005b134 */
            return 0;
        i += 8;
        if (i == 0x28)
            return 0xffffffff;
    }
}

/* ============================================================================
 * FUN_00056e70 @ 0x00056e70  (est. txm_panic_unsupported_image4_cert)
 * Ghidra: void FUN_00056e70(void) — noreturn panic. */
static uint64_t
txm_panic_unsupported_image4_cert(void)
{
    txm_panic_fmt("panic: unsupported image4 cert t");
}

/* ============================================================================
 * FUN_00056e90 @ 0x00056e90  (est. txm_property_get)
 * Ghidra: ulong FUN_00056e90(ulong param_1,long param_2)
 * Returns the value of property param_2 within container param_1 when the
 * property's presence bit (param_2+0x48) is set in the container's bitmask
 * (param_1+8); offset is param_2+0x40, bounded to 0xa0. */
static uint64_t
txm_property_get(uint64_t container, uint64_t prop)
{
    if ((int64_t)(*(int64_t *)(prop + 0x40)) >= 0) {
        if (*(uint64_t *)(prop + 0x48) == 0)
            txm_panic_fmt("panic: illegal property definition");
        if ((*(uint64_t *)(container + 8) & *(uint64_t *)(prop + 0x48)) != 0) {
            uint64_t v = container + *(int64_t *)(prop + 0x40);
            if (v == 0)
                return 0;
            if (v < container + 0xa0 && container <= v)
                return v;
            txm_panic_bounds(0x19);
        }
    }
    return 0;
}

/* ============================================================================
 * FUN_00056f04 @ 0x00056f04  (est. txm_property_set_bool)
 * Ghidra: void FUN_00056f04(byte *param_1,long param_2,byte *param_3)
 * Image4 bool property setter (tag 0x1d558): ORs the presence bit into
 * param_1+8 and stores `*param_3 & 1` at the property offset. */
static void
txm_property_set_bool(uint8_t *obj, uint64_t prop, uint8_t *val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d558)
        txm_panic_fmt("panic: non-%s property set: prop");   /* FUN_00050d70 */
    int64_t off = *(int64_t *)(prop + 0x40);
    if (off >= 0) {
        *(uint64_t *)(obj + 8) |= *(uint64_t *)(prop + 0x48);
        uint8_t *p = obj + off;
        if (p < obj + 0xa0 && obj <= p) {
            *p = *val & 1;
            return;
        }
        txm_panic_bounds(0x19);
    }
    txm_panic_fmt("panic: property not present in c");
}

/* ============================================================================
 * FUN_00056fac @ 0x00056fac  (est. txm_property_set_uint32)
 * Ghidra: void FUN_00056fac(undefined4 *param_1,long param_2,undefined4 *param_3)
 * Image4 uint32 property setter (tag 0x1d568). */
static void
txm_property_set_uint32(uint32_t *obj, uint64_t prop, uint32_t *val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d568)
        txm_panic_fmt("panic: non-%s property set: prop");
    int64_t off = *(int64_t *)(prop + 0x40);
    if (off >= 0) {
        *(uint64_t *)(obj + 2) |= *(uint64_t *)(prop + 0x48);
        uint32_t *p = (uint32_t *)((char *)obj + off);
        if (p < obj + 0x28 && obj <= p) {
            *p = *val;
            return;
        }
        txm_panic_bounds(0x19);
    }
    txm_panic_fmt("panic: property not present in c");
}

/* ============================================================================
 * FUN_00057050 @ 0x00057050  (est. txm_property_set_uint64)
 * Ghidra: void FUN_00057050(undefined8 *param_1,long param_2,undefined8 *param_3)
 * Image4 uint64 property setter (tag 0x1d578). */
static void
txm_property_set_uint64(uint64_t *obj, uint64_t prop, uint64_t *val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d578)
        txm_panic_fmt("panic: non-%s property set: prop");
    int64_t off = *(int64_t *)(prop + 0x40);
    if (off >= 0) {
        obj[1] |= *(uint64_t *)(prop + 0x48);
        uint64_t *p = (uint64_t *)((char *)obj + off);
        if (p < obj + 0x14 && obj <= p) {
            *p = *val;
            return;
        }
        txm_panic_bounds(0x19);
    }
    txm_panic_fmt("panic: property not present in c");
}

/* ============================================================================
 * FUN_000570f4 @ 0x000570f4  (est. txm_property_set_digest)
 * Ghidra: void FUN_000570f4(ulong param_1,long param_2,undefined8 param_3)
 * Image4 digest property setter (tag 0x1d588): ORs presence bit, then copies
 * the digest via FUN_00057c20. */
static void
txm_property_set_digest(uint64_t obj, uint64_t prop, uint64_t val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d588)
        txm_panic_fmt("panic: non-%s property set: prop");
    int64_t off = *(int64_t *)(prop + 0x40);
    if (off >= 0) {
        *(uint64_t *)(obj + 8) |= *(uint64_t *)(prop + 0x48);
        uint64_t p = obj + off;
        if ((p != 0) && (obj + 0xa0 <= p || p < obj))
            txm_panic_bounds(0x19);
        uint64_t lr = (uint64_t)__builtin_return_address(0);
        if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
            txm_breakpoint(0xc471, 0x57168);
        txm_digest_copy_set(p, val);                         /* FUN_00057c20 */
        return;
    }
    txm_panic_fmt("panic: property not present in c");
}

/* ============================================================================
 * FUN_000571ac @ 0x000571ac  (est. txm_property_set_digest64)
 * Ghidra: void FUN_000571ac(ulong param_1,long param_2,undefined8 param_3)
 * Image4 64-byte digest property setter (tag 0x1d598); copies via
 *   FUN_0005d498. */
static void
txm_property_set_digest64(uint64_t obj, uint64_t prop, uint64_t val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d598)
        txm_panic_fmt("panic: non-%s property set: prop");
    int64_t off = *(int64_t *)(prop + 0x40);
    if (off >= 0) {
        *(uint64_t *)(obj + 8) |= *(uint64_t *)(prop + 0x48);
        uint64_t p = obj + off;
        if ((p != 0) && (obj + 0xa0 <= p || p < obj))
            txm_panic_bounds(0x19);
        uint64_t lr = (uint64_t)__builtin_return_address(0);
        if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
            txm_breakpoint(0xc471, 0x57220);
        txm_digest64_copy_set(p, val);                       /* FUN_0005d498 */
        return;
    }
    txm_panic_fmt("panic: property not present in c");
}

/* ============================================================================
 * FUN_00057264 @ 0x00057264  (est. txm_property_get_bool)
 * Ghidra: byte * FUN_00057264(byte *param_1,long param_2,byte *param_3)
 * Image4 bool property getter (tag 0x1d558): returns the value pointer if the
 *   presence bit is set, storing `*p & 1` into param_3; else NULL. */
static uint8_t *
txm_property_get_bool(uint8_t *obj, uint64_t prop, uint8_t *val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d558)
        txm_panic_fmt("panic: non-%s property set: prop");
    if ((int64_t)(*(int64_t *)(prop + 0x40)) >= 0) {
        if ((*(uint64_t *)(prop + 0x48) & *(uint64_t *)(obj + 8)) == 0)
            return 0;
        uint8_t *p = obj + *(int64_t *)(prop + 0x40);
        if (obj + 0xa0 <= p || p < obj)
            txm_panic_bounds(0x19);
        *val = *p & 1;
        return p;
    }
    txm_panic_fmt("panic: property not present in c");
}

/* ============================================================================
 * FUN_00057318 @ 0x00057318  (est. txm_property_get_uint32)
 * Ghidra: undefined4 * FUN_00057318(undefined4 *param_1,long param_2,undefined4 *param_3)
 * Image4 uint32 property getter (tag 0x1d568). */
static uint32_t *
txm_property_get_uint32(uint32_t *obj, uint64_t prop, uint32_t *val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d568)
        txm_panic_fmt("panic: non-%s property set: prop");
    if ((int64_t)(*(int64_t *)(prop + 0x40)) >= 0) {
        if ((*(uint64_t *)(prop + 0x48) & *(uint64_t *)(obj + 2)) == 0)
            return 0;
        uint32_t *p = (uint32_t *)((char *)obj + *(int64_t *)(prop + 0x40));
        if (obj + 0x28 <= p || p < obj)
            txm_panic_bounds(0x19);
        *val = *p;
        return p;
    }
    txm_panic_fmt("panic: property not present in c");
}

/* ============================================================================
 * FUN_000573c8 @ 0x000573c8  (est. txm_property_get_uint64)
 * Ghidra: undefined8 * FUN_000573c8(undefined8 *param_1,long param_2,undefined8 *param_3)
 * Image4 uint64 property getter (tag 0x1d578). */
static uint64_t *
txm_property_get_uint64(uint64_t *obj, uint64_t prop, uint64_t *val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d578)
        txm_panic_fmt("panic: non-%s property set: prop");
    if ((int64_t)(*(int64_t *)(prop + 0x40)) >= 0) {
        if ((*(uint64_t *)(prop + 0x48) & obj[1]) == 0)
            return 0;
        uint64_t *p = (uint64_t *)((char *)obj + *(int64_t *)(prop + 0x40));
        if (obj + 0x14 <= p || p < obj)
            txm_panic_bounds(0x19);
        *val = *p;
        return p;
    }
    txm_panic_fmt("panic: property not present in c");
}

/* ============================================================================
 * FUN_00057478 @ 0x00057478  (est. txm_property_get_digest)
 * Ghidra: undefined8 FUN_00057478(ulong param_1,long param_2,undefined8 param_3)
 * Image4 digest property getter (tag 0x1d588): returns 0 if absent, else
 *   returns FUN_00057c20(param_3, &value). */
static uint64_t
txm_property_get_digest(uint64_t obj, uint64_t prop, uint64_t val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d588)
        txm_panic_fmt("panic: non-%s property set: prop");
    if ((int64_t)(*(int64_t *)(prop + 0x40)) < 0)
        txm_panic_fmt("panic: property not present in c");
    if ((*(uint64_t *)(prop + 0x48) & *(uint64_t *)(obj + 8)) == 0)
        return 0;
    uint64_t p = obj + *(int64_t *)(prop + 0x40);
    if ((p != 0) && (obj + 0xa0 <= p || p < obj))
        txm_panic_bounds(0x19);
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x574e8);
    return txm_digest_copy_get(val, p);                     /* FUN_00057c20 */
}

/* ============================================================================
 * FUN_0005753c @ 0x0005753c  (est. txm_property_get_digest64)
 * Ghidra: undefined8 FUN_0005753c(ulong param_1,long param_2,undefined8 param_3)
 * Image4 64-byte digest property getter (tag 0x1d598). */
static uint64_t
txm_property_get_digest64(uint64_t obj, uint64_t prop, uint64_t val)
{
    if (*(uint64_t *)(prop + 0x28) != 0x1d598)
        txm_panic_fmt("panic: non-%s property set: prop");
    if ((int64_t)(*(int64_t *)(prop + 0x40)) < 0)
        txm_panic_fmt("panic: property not present in c");
    if ((*(uint64_t *)(prop + 0x48) & *(uint64_t *)(obj + 8)) == 0)
        return 0;
    uint64_t p = obj + *(int64_t *)(prop + 0x40);
    if ((p != 0) && (obj + 0xa0 <= p || p < obj))
        txm_panic_bounds(0x19);
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x575ac);
    return txm_digest64_copy_get(val, p);                   /* FUN_0005d498 */
}

/* ============================================================================
 * FUN_0005760c @ 0x0005760c  (est. txm_property_tag)
 * Ghidra: undefined4 FUN_0005760c(long param_1) — returns the property tag
 *   at +0x18. */
static uint32_t
txm_property_tag(uint64_t p)
{
    return *(uint32_t *)(p + 0x18);
}

/* ============================================================================
 * FUN_00057618 @ 0x00057618  (est. txm_runtime_name_validate)
 * Ghidra: void FUN_00057618(char *param_1,undefined8 param_2)
 * Validates a runtime component name (param_1): empty names are rejected
 * (code 2); otherwise formats "%s" (FUN_0002efc4) and looks it up
 * (FUN_00054228), returning 0 on success / 0x16 on failure. */
static uint32_t
txm_runtime_name_validate(char *name, uint64_t key)
{
    uint64_t saved = txm_canary;
    if (*name == '\0')
        return 2;
    uint64_t fmt[4] = {0, 0, 0, 0};
    txm_format_ident(fmt, name, 0x25, 0x25);
    int r = 0;                                              /* FUN_00054228 */
    if (r != 0)
        return 0x16;
    if (txm_canary != saved)
        txm_stack_check();
    return 0;
}

/* ============================================================================
 * FUN_000576bc @ 0x000576bc  (est. txm_runtime_stub_null)
 * Ghidra: undefined8 FUN_000576bc(void) — returns 0. */
static uint64_t
txm_runtime_stub_null(void)
{
    return 0;
}

/* ============================================================================
 * FUN_000576c8 @ 0x000576c8  (est. txm_runtime_stub_void)
 * Ghidra: void FUN_000576c8(void) — no-op. */
static void
txm_runtime_stub_void(void)
{
}

/* ============================================================================
 * FUN_000576d0 @ 0x000576d0  (est. txm_percpu_state_thunk)
 * Ghidra: void thunk_FUN_0005077c(void) — thunk to per-CPU state getter. */
static void
txm_percpu_state_thunk(void)
{
    (void)txm_percpu_state();
}

/* ============================================================================
 * FUN_000576d8 / FUN_000576e4 @ 0x000576d8/0x576e4  (est. txm_runtime_bad_id)
 * Ghidra: undefined8 FUN_000576d8/0x576e4(void) — returns 0x2d (unknown
 *   runtime identifier). */
static uint64_t
txm_runtime_bad_id_a(void)
{
    return 0x2d;
}
static uint64_t
txm_runtime_bad_id_b(void)
{
    return 0x2d;
}

/* ============================================================================
 * FUN_000576f0 @ 0x000576f0  (est. txm_runtime_log)
 * Ghidra: void FUN_000576f0(void)
 * Runtime-log dispatch entry. Builds the runtime callback chain (each txm_runtime_*
 * entry registers its successor via FUN_00057870) then, at the end of the
 * chain, panics with "function should never be called" (FUN_00029784). These
 * entries are forward-declared placeholders that get replaced at runtime; the
 * panic is the dead-end fallback if a wired slot is invoked directly.
 * Confidence: medium (string-matched: s__txm_runtime_log_0000548e). */
static void
txm_runtime_log(void)
{
    txm_runtime_log_handle();        /* FUN_00057710 */
    txm_runtime_get_identifier_bool();   /* FUN_00057730 */
    txm_runtime_get_identifier_uint();   /* FUN_00057750 */
    txm_runtime_get_identifier_uint2();  /* FUN_00057770 */
    txm_runtime_get_identifier_digest(); /* FUN_00057790 */
    txm_runtime_get_identifier_cstr();   /* FUN_000577b0 */
    txm_runtime_alloc_type();            /* FUN_000577d0 */
    txm_runtime_dealloc_type();          /* FUN_000577f0 */
    txm_runtime_set_nonce();             /* FUN_00057810 */
    txm_runtime_roll_nonce();            /* FUN_00057830 */
    txm_runtime_copy_nonce();            /* FUN_00057850 */
    txm_panic_call("panic: function should never be ca");  /* FUN_00029784 */
}

/* ============================================================================
 * FUN_00057710 @ 0x00057710  (est. txm_runtime_log_handle)
 * Ghidra: void FUN_00057710(void) — runtime-log-handle dispatch; builds the
 *   remaining callback chain then panics. String s__txm_runtime_log_handle. */
static void
txm_runtime_log_handle(void)
{
    txm_runtime_get_identifier_bool();
    txm_runtime_get_identifier_uint();
    txm_runtime_get_identifier_uint2();
    txm_runtime_get_identifier_digest();
    txm_runtime_get_identifier_cstr();
    txm_runtime_alloc_type();
    txm_runtime_dealloc_type();
    txm_runtime_set_nonce();
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_00057730 @ 0x00057730  (est. txm_runtime_get_identifier_bool)
 * Ghidra: void FUN_00057730(void) — string s__txm_runtime_get_identifier_bool. */
static void
txm_runtime_get_identifier_bool(void)
{
    txm_runtime_get_identifier_uint();
    txm_runtime_get_identifier_uint2();
    txm_runtime_get_identifier_digest();
    txm_runtime_get_identifier_cstr();
    txm_runtime_alloc_type();
    txm_runtime_dealloc_type();
    txm_runtime_set_nonce();
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_00057750 @ 0x00057750  (est. txm_runtime_get_identifier_uint)
 * Ghidra: void FUN_00057750(void) — string s__txm_runtime_get_identifier_uint. */
static void
txm_runtime_get_identifier_uint(void)
{
    txm_runtime_get_identifier_uint2();
    txm_runtime_get_identifier_digest();
    txm_runtime_get_identifier_cstr();
    txm_runtime_alloc_type();
    txm_runtime_dealloc_type();
    txm_runtime_set_nonce();
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_00057770 @ 0x00057770  (est. txm_runtime_get_identifier_uint2)
 * Ghidra: void FUN_00057770(void) — string s__txm_runtime_get_identifier_uint. */
static void
txm_runtime_get_identifier_uint2(void)
{
    txm_runtime_get_identifier_digest();
    txm_runtime_get_identifier_cstr();
    txm_runtime_alloc_type();
    txm_runtime_dealloc_type();
    txm_runtime_set_nonce();
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_00057790 @ 0x00057790  (est. txm_runtime_get_identifier_digest)
 * Ghidra: void FUN_00057790(void) — string s__txm_runtime_get_identifier_dige. */
static void
txm_runtime_get_identifier_digest(void)
{
    txm_runtime_get_identifier_cstr();
    txm_runtime_alloc_type();
    txm_runtime_dealloc_type();
    txm_runtime_set_nonce();
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_000577b0 @ 0x000577b0  (est. txm_runtime_get_identifier_cstr)
 * Ghidra: void FUN_000577b0(void) — string s__txm_runtime_get_identifier_cstr. */
static void
txm_runtime_get_identifier_cstr(void)
{
    txm_runtime_alloc_type();
    txm_runtime_dealloc_type();
    txm_runtime_set_nonce();
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_000577d0 @ 0x000577d0  (est. txm_runtime_alloc_type)
 * Ghidra: void FUN_000577d0(void) — string s__txm_runtime_alloc_type. */
static void
txm_runtime_alloc_type(void)
{
    txm_runtime_dealloc_type();
    txm_runtime_set_nonce();
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_000577f0 @ 0x000577f0  (est. txm_runtime_dealloc_type)
 * Ghidra: void FUN_000577f0(void) — string s__txm_runtime_dealloc_type. */
static void
txm_runtime_dealloc_type(void)
{
    txm_runtime_set_nonce();
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_00057810 @ 0x00057810  (est. txm_runtime_set_nonce)
 * Ghidra: void FUN_00057810(void) — string s__txm_runtime_set_nonce. */
static void
txm_runtime_set_nonce(void)
{
    txm_runtime_roll_nonce();
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_00057830 @ 0x00057830  (est. txm_runtime_roll_nonce)
 * Ghidra: void FUN_00057830(void) — string s__txm_runtime_roll_nonce. */
static void
txm_runtime_roll_nonce(void)
{
    txm_runtime_copy_nonce();
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_00057850 @ 0x00057850  (est. txm_runtime_copy_nonce)
 * Ghidra: void FUN_00057850(void) — string s__txm_runtime_copy_nonce. */
static void
txm_runtime_copy_nonce(void)
{
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_00057870 @ 0x00057870  (est. txm_runtime_chain_panic)
 * Ghidra: void FUN_00057870(void) — shared callback-chain terminator; always
 *   panics with "function should never be called". */
static void
txm_runtime_chain_panic(void)
{
    txm_panic_call("panic: function should never be ca");
}

/* ============================================================================
 * FUN_0005789c @ 0x0005789c  (est. txm_identifier_from_cstr)
 * Ghidra: ulong FUN_0005789c(ulong param_1,ulong param_2,ulong param_3)
 * Builds an image4 identifier (param_1) from a NUL-terminated string (param_2,
 * bounded by param_3): computes the string length, clamps to 0x3f, copies with
 * txm_format_ident, and records the length in param_1+0x40 / 0x48. */
static uint64_t
txm_identifier_from_cstr(uint64_t out, uint64_t src, uint64_t cap)
{
    uint64_t n = 0;
    while (*(char *)(src + n) != '\0')
        n++;
    if ((cap <= n) && (src <= src + n)) {
        uint64_t len = txm_strnlen(src, cap);        /* thunk_FUN_0002dbe0 */
        uint64_t cl = len;
        if (cl > 0x3e)
            cl = 0x3f;
        if (out <= out + cl + 1) {
            txm_format_ident(out, src, cl + 1, 0xffffffffffffffff);  /* FUN_0002efc4 */
            *(uint64_t *)(out + 0x40) = cl;
            *(uint64_t *)(out + 0x48) = len;
            return out;
        }
    }
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_0005793c @ 0x0005793c  (est. txm_errno_lookup)
 * Ghidra: undefined4 FUN_0005793c(uint param_1)
 * Maps an internal error index (0-7) to an external error code from the table
 * at DAT_0000db88; default 0xe. */
static uint32_t
txm_errno_lookup(uint32_t idx)
{
    if (idx < 8)
        return *(uint32_t *)(0xdb88 + (uint64_t)idx * 4);
    return 0xe;
}

/* ============================================================================
 * FUN_00057960 @ 0x00057960  (est. txm_decode_payload_if_mode)
 * Ghidra: void FUN_00057960(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Decodes an img4 payload iff the encoder mode (FUN_00045418) is 2 (payload
 *   mode); otherwise returns without action. */
static void
txm_decode_payload_if_mode(uint64_t a, uint64_t b, uint64_t c)
{
    if (txm_encode_init_mode() != 2)   /* FUN_00045418 */
        return;
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x579b4);
    txm_encode_payload(a, b, c);       /* FUN_00045504 */
}

/* ============================================================================
 * FUN_000579c8 @ 0x000579c8  (est. txm_decode_manifest_if_mode)
 * Ghidra: void FUN_000579c8(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Decodes an img4 manifest iff the encoder mode is 2; else returns. */
static void
txm_decode_manifest_if_mode(uint64_t a, uint64_t b, uint64_t c)
{
    if (txm_encode_init_mode() != 2)
        return;
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x57a1c);
    txm_encode_payload(a, b, c);       /* FUN_000455a0 */
}

/* ============================================================================
 * FUN_00057a30 @ 0x00057a30  (est. txm_digest_oid_type)
 * Ghidra: undefined8 FUN_00057a30(undefined8 *param_1)
 * Classifies a digest algorithm by matching the OID in param_1 against the
 * known img4 digest OIDs (DAT_00011d50/58/60/68/70/78/80/88/90/98). Returns a
 * bit flag (1/2/4/8/0x10); panics "unsupported digest type" on no match. */
static uint64_t
txm_digest_oid_type(uint64_t *oid)
{
    uint64_t tag = oid[1];
    if (tag == 0x11d58) {
        if (txm_memcmp(oid[0], 0x11d50, 0) == 0)
            return 1;
        tag = oid[1];
    }
    if (tag == 0x11d98) {
        if (txm_memcmp(oid[0], 0x11d90, 0) == 0)
            return 2;
        tag = oid[1];
    }
    if (tag == 0x11d68) {
        if (txm_memcmp(oid[0], 0x11d60, 0) == 0)
            return 4;
        tag = oid[1];
    }
    if (tag == 0x11d78) {
        if (txm_memcmp(oid[0], 0x11d70, 0) == 0)
            return 8;
        tag = oid[1];
    }
    if ((tag == 0x11d88) && (txm_memcmp(oid[0], 0x11d80, 0) == 0))
        return 0x10;
    txm_panic_fmt("panic: unsupported digest type %s");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_00057b58 @ 0x00057b58  (est. txm_digest_set_bytes)
 * Ghidra: long FUN_00057b58(long param_1,undefined8 param_2,ulong param_3)
 * Stores a digest (param_2, param_3 bytes) into a digest object at param_1+8,
 * recording the length at param_1+0x48. Length must be < 0x41. */
static uint64_t
txm_digest_set_bytes(uint64_t obj, uint64_t src, uint64_t n)
{
    if (n < 0x41) {
        txm_memcpy(obj + 8, src, n);
        *(uint64_t *)(obj + 0x48) = n;
        return obj;
    }
    txm_panic_fmt("panic: digest length overflow: a");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_00057bb4 @ 0x00057bb4  (est. txm_digest_import_obj)
 * Ghidra: undefined8 * FUN_00057bb4(undefined8 *param_1,ulong *param_2,undefined8 *param_3)
 * Initializes a digest object (param_1) from a digest descriptor: length in
 *   param_2, data/type in param_3. */
static uint64_t *
txm_digest_import_obj(uint64_t *obj, uint64_t *len, uint64_t *desc)
{
    if (*len < 0x41) {
        /* FUN_00037f5c(len, desc[1], *desc, obj+1) */
        obj[9] = *len;
        *obj = (uint64_t)len;
        return obj;
    }
    txm_panic_fmt("panic: digest length overflow: a");
}

/* ============================================================================
 * FUN_00057c20 @ 0x00057c20  (est. txm_digest_copy_set)
 * Ghidra: void FUN_00057c20(undefined8 param_1,long param_2)
 * Copies a digest into param_1 from param_2+8 (length checked < 0x41). */
static void
txm_digest_copy_set(uint64_t dst, uint64_t src)
{
    if (0x40 < *(uint64_t *)(src + 0x48))
        txm_panic_bounds(0x19);
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x57c40);
    txm_digest_set_bytes(dst, src + 8);                  /* FUN_00057b58 */
}

/* ============================================================================
 * FUN_00057c58 @ 0x00057c58  (est. txm_digest_equal)
 * Ghidra: undefined8 FUN_00057c58(long param_1,long param_2)
 * Compares two digests; 0 if equal (length match + memcmp), 1 otherwise. */
static uint64_t
txm_digest_equal(uint64_t a, uint64_t b)
{
    if (*(uint64_t *)(a + 0x48) != *(uint64_t *)(b + 0x48))
        return 1;
    if (*(uint64_t *)(a + 0x48) < 0x41) {
        uint64_t lr = (uint64_t)__builtin_return_address(0);
        if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
            txm_breakpoint(0xc471, 0x57c88);
        return txm_memcmp(a + 8, b + 8, 0);   /* thunk_FUN_0002d4d0 */
    }
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_00057ca8 @ 0x00057ca8  (est. txm_digest_copy_get)
 * Ghidra: void FUN_00057ca8(long param_1,undefined8 param_2)
 * Copies a digest from param_1+8 into param_2 via FUN_0004ff74. */
static void
txm_digest_copy_get(uint64_t src, uint64_t dst)
{
    if (0x40 < *(uint64_t *)(src + 0x48))
        txm_panic_bounds(0x19);
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x57cd0);
    txm_digest_copy(dst, src + 8);                       /* FUN_0004ff74 */
}

/* ============================================================================
 * FUN_00057ce8 @ 0x00057ce8  (est. txm_digest_export_64)
 * Ghidra: void FUN_00057ce8(long param_1,undefined8 param_2,ulong *param_3)
 * Exports a digest into param_2, updating param_3 with the written length. */
static void
txm_digest_export_64(uint64_t src, uint64_t dst, uint64_t *len)
{
    if (*len < *(uint64_t *)(src + 0x48))
        txm_panic_fmt("panic: digest length overflow: a");
    if (*(uint64_t *)(src + 0x48) < 0x41) {
        txm_memcpy(dst, src + 8, 0);
        if (*(uint64_t *)(src + 0x48) <= *len) {
            *len = *(uint64_t *)(src + 0x48);
            return;
        }
    }
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_00057d68 @ 0x00057d68  (est. txm_digest_export_32)
 * Ghidra: void FUN_00057d68(long param_1,undefined8 param_2,uint *param_3)
 * Exports a digest into param_2, updating param_3 (uint) with the length. */
static void
txm_digest_export_32(uint64_t src, uint64_t dst, uint32_t *len)
{
    if ((uint64_t)*len < *(uint64_t *)(src + 0x48))
        txm_panic_fmt("panic: digest length overflow: a");
    if (*(uint64_t *)(src + 0x48) < 0x41) {
        txm_memcpy(dst, src + 8, 0);
        uint64_t n = *(uint64_t *)(src + 0x48);
        if (n >> 0x20 != 0)
            txm_panic_fmt("panic: integer cast overflow: v");  /* FUN_00050d70 */
        if (n <= *len) {
            *len = (uint32_t)n;
            return;
        }
    }
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_00057e10 @ 0x00057e10  (est. txm_expert_tag_validate)
 * Ghidra: void FUN_00057e10(long param_1,uint param_2)
 * Validates an "expert" operation tag: byte-swaps both the current tag
 * (param_1+8) and the expected tag (param_2), prints both as hex (FUN_0002ee48)
 * and panics "unexpected expert op" on mismatch. */
static void
txm_expert_tag_validate(uint64_t obj, uint32_t expect)
{
    uint32_t cur = *(uint32_t *)(obj + 8);
    if (cur == expect)
        return;
    uint32_t t = (cur & 0xff00ff00) >> 8 | (cur & 0xff00ff) << 8;
    uint32_t e1 = t >> 0x10 | t << 0x10;
    /* FUN_0002ee48(&cur_swapped,&e1,4,5) */
    t = (expect & 0xff00ff00) >> 8 | (expect & 0xff00ff) << 8;
    e1 = t >> 0x10 | t << 0x10;
    /* FUN_0002ee48(&expect_swapped,&e1,4,5) */
    txm_panic_fmt("panic: unexpected expert op");          /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_00057eb0 @ 0x00057eb0  (est. txm_vtable_dispatch_20)
 * Ghidra: void FUN_00057eb0(long param_1) — indirect jump through +0x20. */
static void
txm_vtable_dispatch_20(uint64_t obj)
{
    ((void (*)(void))(*(uint64_t *)(obj + 0x20)))();
}

/* ============================================================================
 * FUN_00057ec0 @ 0x00057ec0  (est. txm_vtable_dispatch_28)
 * Ghidra: void FUN_00057ec0(long param_1) — indirect jump through +0x28. */
static void
txm_vtable_dispatch_28(uint64_t obj)
{
    ((void (*)(void))(*(uint64_t *)(obj + 0x28)))();
}

/* ============================================================================
 * FUN_00057ed0 @ 0x00057ed0  (est. txm_impl_vtable_dispatch)
 * Ghidra: long FUN_00057ed0(long param_1,undefined8 param_2,long *param_3)
 * Dispatches through a decode-implementation vtable: for a foreign type
 * (FUN_00042b84 nonzero) returns the type-singleton (FUN_00059250) + its
 * dispatch (+0x48); else invokes the implementation's method at +0x40. */
static uint64_t
txm_impl_vtable_dispatch(uint64_t impl, uint64_t op, uint64_t *out)
{
    uint64_t r = txm_optional_not_set();        /* FUN_00042b84 */
    if (r == 0) {
        uint64_t *singleton = txm_type_singleton();   /* FUN_00059250 */
        uint64_t s = singleton[0];
        if ((singleton[1] != 0) && (*(uint64_t *)(s + 0x48) != 0 && *out != 0)) {
            s = ((uint64_t (*)(void))(*(uint64_t *)(s + 0x48)))();
        }
        *out = 0;
        return s;
    }
    if (*(uint64_t *)(impl + 0x40) != 0) {
        uint64_t lr = (uint64_t)__builtin_return_address(0);
        if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
            txm_breakpoint(0xc471, 0x57f1c);
        return ((uint64_t (*)(uint64_t, uint64_t))(*(uint64_t *)(impl + 0x40)))(impl, op);
    }
    return 0;
}

/* ============================================================================
 * FUN_00057f38 @ 0x00057f38  (est. txm_digest_release)
 * Ghidra: void FUN_00057f38(long param_1,long param_2,long *param_3)
 * Calls the release hook at param_1+0x48 (if set and *param_3 != 0) and clears
 *   param_3. */
static void
txm_digest_release(uint64_t obj, uint64_t arg, uint64_t *out)
{
    if ((arg != 0) && (*(uint64_t *)(obj + 0x48) != 0 && *out != 0)) {
        ((void (*)(void))(*(uint64_t *)(obj + 0x48)))();
    }
    *out = 0;
}

/* ============================================================================
 * FUN_00057f7c @ 0x00057f7c  (est. txm_manifest_dump)
 * Ghidra: void FUN_00057f7c(long param_1)
 * Dumps a manifest/identifier object: queries its kind (call at +0x78),
 * formats the 4-byte tag as hex, and iterates the property table
 * (FUN_000566b8 over 0x1d3f0), printing each property as
 * "%-6s %-36s %s" / hex; dispatch by property value type (0/1/2/3/4).
 * Confidence: medium. */
static void
txm_manifest_dump(uint64_t obj)
{
    uint64_t saved = txm_canary;
    uint64_t ident[5] = {0x1d3f0, 0x1d3f8, 0x1d400, 0, 0};
    uint64_t kind = 0;
    int r = ((int (*)(uint64_t, uint64_t *))(*(uint64_t *)(obj + 0x78)))(obj, &kind);
    if (r == 0) {
        if ((2 < kind) && (kind != 3))
            txm_panic_fmt("panic: unreachable case %s 0x");
        txm_snprintf(&ident, 0x20, "0x%llx");
    } else {
        kind = 3;
    }
    /* Format the 4-byte tag via FUN_0002eeac/FUN_0002ee48 into a hex label. */
    txm_panic_fmt("");   /* printf banner lines via FUN_000585b8 */
    uint64_t pv = ((uint64_t (*)(uint64_t, uint64_t))(*(uint64_t *)(obj + 0x80)))(obj, kind);
    (void)txm_optional_not_set();
    uint64_t e;
    if ((*(uint64_t *)(obj + 0x68) == 0) || ((e = ((uint64_t (*)(uint64_t))(*(uint64_t *)(obj + 0x68)))(obj)) < 7)) {
        if ((*(uint64_t *)(obj + 0x70) == 0) || ((e = ((uint64_t (*)(uint64_t))(*(uint64_t *)(obj + 0x70)))(obj)) < 7)) {
            /* iterate property table */
            for (;;) {
                uint64_t id = txm_iterator_next(ident);
                if (id == 0) {
                    uint64_t d[0x40];  /* 0x200-byte scratch */
                    int rc = txm_property_digest_query(obj, 0, 0x1a858, d);  /* FUN_00058b88 */
                    if (rc == 0)
                        txm_digest_copy_get(d, &d);
                    if (*(uint64_t *)(obj + 0x38) != 0) {
                        txm_panic_fmt("");
                        ((void (*)(uint64_t, int))(*(uint64_t *)(obj + 0x38)))(obj, 1);
                    }
                    if (txm_canary == saved)
                        return;
                    txm_stack_check();
                }
                uint64_t base = id + 0x68;
                int vtype = **(int **)(id + 0x28);
                int rc = 0;
                if (vtype < 2) {
                    if (vtype == 0)
                        rc = txm_property_bool_query(obj, pv, id, &d);    /* FUN_0005861c */
                    else if (vtype == 1)
                        rc = txm_property_uint32_query(obj, pv, id, &d);  /* FUN_000587f0 */
                } else if (vtype == 2) {
                    rc = txm_property_uint64_query(obj, pv, id, &d);      /* FUN_000589bc */
                } else if (vtype == 3) {
                    rc = txm_property_digest_query(obj, pv, id, &d);      /* FUN_00058b88 */
                } else if (vtype == 4) {
                    rc = txm_property_digest64_query(obj, pv, id, &d);    /* FUN_00058d18 */
                } else {
                    txm_panic_fmt("panic: unreachable case %s 0x");
                }
                txm_panic_fmt("");   /* print the property line */
            }
        }
    }
    txm_panic_fmt("panic: unreachable case %s 0x");
}

/* ============================================================================
 * FUN_0005856c @ 0x0005856c  (est. txm_vtable_dispatch_78)
 * Ghidra: void FUN_0005856c(long param_1) — indirect jump through +0x78. */
static void
txm_vtable_dispatch_78(uint64_t obj)
{
    ((void (*)(void))(*(uint64_t *)(obj + 0x78)))();
}

/* ============================================================================
 * FUN_0005857c @ 0x0005857c  (est. txm_snprintf_var)
 * Ghidra: void FUN_0005857c(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * Thin wrapper over FUN_0002eb44 (snprintf). */
static void
txm_snprintf_var(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    txm_snprintf(a, c, 0, d);   /* FUN_0002eb44(a,c,0,b,d) */
}

/* ============================================================================
 * FUN_000585b8 @ 0x000585b8  (est. txm_log_level)
 * Ghidra: void FUN_000585b8(long param_1,ulong param_2)
 * Log writer: if the level (param_2) < 4, calls the object's log hook at
 *   +0x30; else panics "unreachable case". */
static void
txm_log_level(uint64_t obj, uint64_t level)
{
    if (level < 4) {
        ((void (*)(void))(*(uint64_t *)(obj + 0x30)))();
        return;
    }
    txm_panic_fmt("panic: unreachable case %s 0x");
}

/* ============================================================================
 * FUN_0005860c @ 0x0005860c  (est. txm_vtable_dispatch_80)
 * Ghidra: void FUN_0005860c(long param_1) — indirect jump through +0x80. */
static void
txm_vtable_dispatch_80(uint64_t obj)
{
    ((void (*)(void))(*(uint64_t *)(obj + 0x80)))();
}

/* ============================================================================
 * FUN_0005861c @ 0x0005861c  (est. txm_property_bool_query)
 * Ghidra: ulong FUN_0005861c(undefined8 param_1,long param_2,long param_3,byte *param_4)
 * Queries a bool property (param_3) from a manifest/payload object; resolves
 *   the active property set (FUN_00056d00), invokes the property-set getter
 *   (+0xc8 vtable) and normalizes the value into *param_4. */
static uint64_t
txm_property_bool_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint8_t *out)
{
    uint64_t saved = txm_canary;
    uint8_t raw = 0;
    if (ctx != 0)
        (void)txm_env_query(ctx);              /* FUN_00050420 */
    uint64_t set = txm_property_set_resolve(ctx, prop, obj);  /* FUN_00056d00 */
    uint64_t rc = ((uint64_t (*)(uint64_t, uint64_t, uint64_t, uint8_t *))(*(uint64_t *)(set + 200)))(set, ctx, prop, &raw);
    uint32_t e = (uint32_t)rc;
    if ((e > 0x2d) || ((1ULL << (rc & 0x3f) & 0x200000080005ULL) == 0))
        txm_panic_fmt("failed to query property %s %d");
    uint64_t d[0x10] = {0};
    uint64_t fmt = 0x2f6e61;                   /* "na" prefix */
    uint8_t val = raw & 1;
    uint64_t (*get)(uint64_t, uint64_t, uint8_t *) = txm_property_get_bool;  /* FUN_00059220 */
    if (*(uint64_t *)(prop + 0x30) != 0x1d5e8)
        get = (uint64_t (*)(uint64_t, uint64_t, uint8_t *))(*(uint64_t *)(prop + 0x58));
    if (e != 2) {
        if (e != 0) goto done;
        get = (uint64_t (*)(uint64_t, uint64_t, uint8_t *))(*(uint64_t *)(prop + 0x60));
        txm_snprintf_var(&d, 0x40, 0x40, 0x5870);
    }
    if (get != 0) {
        rc = get(prop, ctx, &val);
        e = (uint32_t)rc;
        raw = val;
    }
done:
    if (e == 0) {
        rc = 0;
        *out = raw & 1;
    } else if (rc > 0x6b) {
        txm_panic_fmt("panic: error not set to valid po");
    }
    if (txm_canary != saved)
        txm_stack_check();
    return rc;
}

/* ============================================================================
 * FUN_000587f0 @ 0x000587f0  (est. txm_property_uint32_query)
 * Ghidra: ulong FUN_000587f0(undefined8 param_1,long param_2,long param_3,undefined4 *param_4)
 * Queries a uint32 property via the property-set getter at +0xd0. */
static uint64_t
txm_property_uint32_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint32_t *out)
{
    uint64_t saved = txm_canary;
    uint32_t raw = 0;
    if (ctx != 0)
        (void)txm_env_query(ctx);
    uint64_t set = txm_property_set_resolve(ctx, prop, obj);
    uint64_t rc = ((uint64_t (*)(uint64_t, uint64_t, uint64_t, uint32_t *))(*(uint64_t *)(set + 0xd0)))(set, ctx, prop, &raw);
    uint32_t e = (uint32_t)rc;
    if ((e > 0x2d) || ((1ULL << (rc & 0x3f) & 0x200000080005ULL) == 0))
        txm_panic_fmt("failed to query property %s %d");
    uint64_t d[0x10] = {0};
    uint32_t val = raw;
    uint64_t (*get)(uint64_t, uint64_t, uint32_t *) = txm_property_get_uint32;  /* FUN_00059230 */
    if (*(uint64_t *)(prop + 0x30) != 0x1d5e8)
        get = (uint64_t (*)(uint64_t, uint64_t, uint32_t *))(*(uint64_t *)(prop + 0x58));
    if (e != 2) {
        if (e != 0) goto done;
        get = (uint64_t (*)(uint64_t, uint64_t, uint32_t *))(*(uint64_t *)(prop + 0x60));
        txm_snprintf_var(&d, 0x40, 0x40, 0x5870);
    }
    if (get != 0) {
        rc = get(prop, ctx, &val);
        e = (uint32_t)rc;
        raw = val;
    }
done:
    if (e == 0) {
        rc = 0;
        *out = raw;
    } else if (rc > 0x6b) {
        txm_panic_fmt("panic: error not set to valid po");
    }
    if (txm_canary != saved)
        txm_stack_check();
    return rc;
}

/* ============================================================================
 * FUN_000589bc @ 0x000589bc  (est. txm_property_uint64_query)
 * Ghidra: ulong FUN_000589bc(undefined8 param_1,long param_2,long param_3,undefined8 *param_4)
 * Queries a uint64 property via the property-set getter at +0xd8. */
static uint64_t
txm_property_uint64_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t *out)
{
    uint64_t saved = txm_canary;
    uint64_t raw = 0;
    if (ctx != 0)
        (void)txm_env_query(ctx);
    uint64_t set = txm_property_set_resolve(ctx, prop, obj);
    uint64_t rc = ((uint64_t (*)(uint64_t, uint64_t, uint64_t, uint64_t *))(*(uint64_t *)(set + 0xd8)))(set, ctx, prop, &raw);
    uint32_t e = (uint32_t)rc;
    if ((e > 0x2d) || ((1ULL << (rc & 0x3f) & 0x200000080005ULL) == 0))
        txm_panic_fmt("failed to query property %s %d");
    uint64_t d[0x10] = {0};
    uint64_t val = raw;
    uint64_t (*get)(uint64_t, uint64_t, uint64_t *) = txm_property_get_uint64;  /* FUN_00059240 */
    if (*(uint64_t *)(prop + 0x30) != 0x1d5e8)
        get = (uint64_t (*)(uint64_t, uint64_t, uint64_t *))(*(uint64_t *)(prop + 0x58));
    if (e != 2) {
        if (e != 0) goto done;
        get = (uint64_t (*)(uint64_t, uint64_t, uint64_t *))(*(uint64_t *)(prop + 0x60));
        txm_snprintf_var(&d, 0x40, 0x40, 0x55db);
    }
    if (get != 0) {
        rc = get(prop, ctx, &val);
        e = (uint32_t)rc;
        raw = val;
    }
done:
    if (e == 0) {
        rc = 0;
        *out = raw;
    } else if (rc > 0x6b) {
        txm_panic_fmt("panic: error not set to valid po");
    }
    if (txm_canary != saved)
        txm_stack_check();
    return rc;
}

/* ============================================================================
 * FUN_00058b88 @ 0x00058b88  (est. txm_property_digest_query)
 * Ghidra: ulong FUN_00058b88(undefined8 param_1,long param_2,long param_3,undefined8 param_4)
 * Queries a digest property via the property-set getter at +0xe0. */
static uint64_t
txm_property_digest_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t out)
{
    uint64_t saved = txm_canary;
    uint64_t raw[0x30] = {0};
    if (ctx != 0)
        (void)txm_env_query(ctx);
    uint64_t set = txm_property_set_resolve(ctx, prop, obj);
    uint64_t rc = ((uint64_t (*)(uint64_t, uint64_t, uint64_t, uint64_t *))(*(uint64_t *)(set + 0xe0)))(set, ctx, prop, raw);
    uint32_t e = (uint32_t)rc;
    if ((e > 0x2d) || ((1ULL << (rc & 0x3f) & 0x200000080005ULL) == 0))
        txm_panic_fmt("failed to query property %s %d");
    if (e == 2) {
        if (*(uint64_t *)(prop + 0x30) != 0x1d5e8) {
            rc = 2;
            goto done;
        }
        uint64_t d[0x30] = {0};
        txm_digest_copy_get(raw, d);       /* FUN_00057ca8 */
        txm_digest_copy_set(raw, d);       /* FUN_00057c20 */
    } else if (e != 0) {
        if (e > 0x6b)
            txm_panic_fmt("panic: error not set to valid po");
        goto done;
    }
    txm_digest_copy_set(out, raw);         /* FUN_00057c20 */
    rc = 0;
done:
    if (txm_canary == saved)
        return rc;
    txm_stack_check();
    return rc;
}

/* ============================================================================
 * FUN_00058d18 @ 0x00058d18  (est. txm_property_digest64_query)
 * Ghidra: ulong FUN_00058d18(undefined8 param_1,long param_2,long param_3,undefined8 param_4)
 * Queries a 64-byte digest property via the property-set getter at +0xe8. */
static uint64_t
txm_property_digest64_query(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t out)
{
    uint64_t saved = txm_canary;
    uint64_t raw[0x30] = {0};
    if (ctx != 0)
        (void)txm_env_query(ctx);
    uint64_t set = txm_property_set_resolve(ctx, prop, obj);
    uint64_t rc = ((uint64_t (*)(uint64_t, uint64_t, uint64_t, uint64_t *))(*(uint64_t *)(set + 0xe8)))(set, ctx, prop, raw);
    uint32_t e = (uint32_t)rc;
    if ((e > 0x2d) || ((1ULL << (rc & 0x3f) & 0x200000080005ULL) == 0))
        txm_panic_fmt("failed to query property %s %d");
    if (e == 2) {
        if (*(uint64_t *)(prop + 0x30) != 0x1d5e8) {
            rc = 2;
            goto done;
        }
        uint64_t d[0x30] = {0};
        txm_digest64_copy_set(raw, d);     /* FUN_0005d498 */
    } else if (e != 0) {
        if (e > 0x6b)
            txm_panic_fmt("panic: error not set to valid po");
        goto done;
    }
    txm_digest64_copy_set(out, raw);       /* FUN_0005d498 */
    rc = 0;
done:
    if (txm_canary == saved)
        return rc;
    txm_stack_check();
    return rc;
}

/* ============================================================================
 * FUN_00058e9c @ 0x00058e9c  (est. txm_image4_cert_type)
 * Ghidra: undefined8 FUN_00058e9c(long param_1,uint *param_2)
 * Resolves the image4 certificate type via the object's query hook (+0xd0);
 * rejects types > 1 ("unsupported image4 cert type %u", code 0x2d). */
static uint64_t
txm_image4_cert_type(uint64_t obj, uint32_t *out)
{
    uint32_t t = 0;
    int r = ((int (*)(uint64_t, int, uint64_t, uint32_t *))(*(uint64_t *)(obj + 0xd0)))(obj, 0, 0x1c178, &t);
    uint32_t type = 0;
    if ((r == 0) && (type = t, 1 < t)) {
        txm_panic_fmt("unsupported image4 cert type %u");
        return 0x2d;
    }
    *out = type;
    return 0;
}

/* ============================================================================
 * FUN_00058f24 @ 0x00058f24  (est. txm_property_entropy_resolve)
 * Ghidra: void FUN_00058f24(long param_1,long param_2,undefined8 param_3)
 * Resolves an entropy/nonce source: if param_2 is 0, obtains it via the
 *   object's +0x80 hook, then dispatches through the +0x60 method. */
static void
txm_property_entropy_resolve(uint64_t obj, uint64_t src, uint64_t arg)
{
    if (src == 0)
        src = ((uint64_t (*)(uint64_t))(*(uint64_t *)(obj + 0x80)))(obj);
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x58f78);
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(obj + 0x60)))(obj, src, arg);
}

/* ============================================================================
 * FUN_00058f80/90/a0/b0 @ 0x00058f80-0x58fb0  (est. txm_vtable_dispatch_88..a0)
 * Ghidra: void FUN_00058f80/90/a0/b0(long param_1) — indirect jumps through
 *   +0x88/0x90/0x98/0xa0. */
static void
txm_vtable_dispatch_88(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0x88)))(); }
static void
txm_vtable_dispatch_90(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0x90)))(); }
static void
txm_vtable_dispatch_98(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0x98)))(); }
static void
txm_vtable_dispatch_a0(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0xa0)))(); }

/* ============================================================================
 * FUN_00058fc0 @ 0x00058fc0  (est. txm_query_anchor)
 * Ghidra: void FUN_00058fc0(long param_1) — indirect jump through +0xa8. */
static void
txm_query_anchor(uint64_t obj)
{
    ((void (*)(void))(*(uint64_t *)(obj + 0xa8)))();
}

/* ============================================================================
 * FUN_00058fd0/fe0/ff0/9000/9010 @ 0x00058fd0-0x59010  (est. txm_vtable_dispatch)
 * Ghidra: void FUN_00058fd0..59010 — indirect jumps through +0xb0/0xb8/0xf0/0xf8/0x100. */
static void
txm_vtable_dispatch_b0(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0xb0)))(); }
static void
txm_vtable_dispatch_b8(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0xb8)))(); }
static void
txm_vtable_dispatch_f0(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0xf0)))(); }
static void
txm_vtable_dispatch_f8(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0xf8)))(); }
static void
txm_vtable_dispatch_100(uint64_t obj) { ((void (*)(void))(*(uint64_t *)(obj + 0x100)))(); }

/* ============================================================================
 * FUN_00059020 @ 0x00059020  (est. txm_manifest_has_more_props)
 * Ghidra: bool FUN_00059020(long param_1)
 * Returns true when the +0x68 hook reports fewer elements than the +0x70 hook
 *   (i.e. there are more properties to iterate). */
static bool
txm_manifest_has_more_props(uint64_t obj)
{
    uint64_t a = (*(uint64_t *)(obj + 0x68) != 0) ? ((uint64_t (*)(uint64_t))(*(uint64_t *)(obj + 0x68)))(obj) : 0;
    uint64_t b = (*(uint64_t *)(obj + 0x70) != 0) ? ((uint64_t (*)(uint64_t))(*(uint64_t *)(obj + 0x70)))(obj) : 6;
    return a < b;
}

/* ============================================================================
 * FUN_00059084 @ 0x00059084  (est. txm_identifier_16byte)
 * Ghidra: undefined8 FUN_00059084(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Builds a 16-byte identifier from two queried properties (uint32 at 0x1c600
 *   and uint64 at 0x1c8b0), byte-swapping both and storing the result. */
static uint64_t
txm_identifier_16byte(uint64_t obj, uint64_t ctx, uint64_t out)
{
    uint64_t a = 0, b = 0;
    uint64_t rc = txm_property_uint32_query(obj, ctx, 0x1c600, (uint32_t *)&a | 4);
    if (((int)rc == 0) && (rc = txm_property_uint64_query(obj, ctx, 0x1c8b0, &b), (int)rc == 0)) {
        uint32_t t = (uint32_t)(a & 0xffffffff);
        uint32_t s = (t & 0xff00ff00) >> 8 | (t & 0xff00ff) << 8;
        a = (uint64_t)(s >> 0x10 | s << 0x10) << 0x20;
        uint64_t s2 = (b & 0xff00ff00ff00ff00) >> 8 | (b & 0xff00ff00ff00ff) << 8;
        s2 = (s2 & 0xffff0000ffff0000) >> 0x10 | (s2 & 0xffff0000ffff) << 0x10;
        b = s2 >> 0x20 | s2 << 0x20;
        txm_digest_set_bytes(out, &a, 0x10);   /* FUN_00057b58 */
        rc = 0;
    }
    return rc;
}

/* ============================================================================
 * FUN_00059120 @ 0x00059120  (est. txm_policy_bool_count)
 * Ghidra: ulong FUN_00059120(undefined8 param_1,undefined8 param_2,int *param_3)
 * Counts the set bits among three policy bool properties (table at 0x1d408),
 *   ORs them into *param_3. */
static uint64_t
txm_policy_bool_count(uint64_t obj, uint64_t ctx, int *out)
{
    int total = 0;
    uint64_t i = 0;
    for (;;) {
        uint8_t v = 0;
        uint64_t rc = txm_property_bool_query(obj, ctx, *(uint64_t *)(0x1d408 + i), &v);
        if ((rc > 0x2d) || ((1ULL << (rc & 0x3f) & 0x200000000005ULL) == 0))
            return rc;
        total += (v & 1);
        i += 8;
        if (i == 0x18)
            break;
    }
    *out = total;
    return 0;
}

/* ============================================================================
 * FUN_000591d8 @ 0x000591d8  (est. txm_policy_any_bool)
 * Ghidra: void FUN_000591d8(undefined4 param_1,undefined8 param_2,undefined8 param_3)
 * Stores true in *param_3 when any policy bool property is set. */
static void
txm_policy_any_bool(uint64_t obj, uint64_t ctx, uint64_t out)
{
    int n = 0;
    if (txm_policy_bool_count(obj, ctx, &n) == 0)
        *(bool *)out = (n != 0);
}

/* ============================================================================
 * FUN_00059220 @ 0x00059220  (est. txm_property_get_bool_impl)
 * Ghidra: undefined8 FUN_00059220(undefined8 param_1,undefined8 param_2,undefined1 *param_3)
 * Default bool getter: writes 0. */
static uint64_t
txm_property_get_bool_impl(uint64_t a, uint64_t b, uint8_t *out)
{
    *out = 0;
    return 0;
}

/* ============================================================================
 * FUN_00059230 @ 0x00059230  (est. txm_property_get_uint32_impl)
 * Ghidra: undefined8 FUN_00059230(...) — default uint32 getter: writes 0. */
static uint64_t
txm_property_get_uint32_impl(uint64_t a, uint64_t b, uint32_t *out)
{
    *out = 0;
    return 0;
}

/* ============================================================================
 * FUN_00059240 @ 0x00059240  (est. txm_property_get_uint64_impl)
 * Ghidra: undefined8 FUN_00059240(...) — default uint64 getter: writes 0. */
static uint64_t
txm_property_get_uint64_impl(uint64_t a, uint64_t b, uint64_t *out)
{
    *out = 0;
    return 0;
}

/* ============================================================================
 * FUN_00059250 @ 0x00059250  (est. txm_type_singleton)
 * Ghidra: void FUN_00059250(void) — panics "type not available". */
static uint64_t *
txm_type_singleton(void)
{
    txm_panic_fmt("panic: type not available");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_00059268 @ 0x00059268  (est. txm_store_tag_swapped)
 * Ghidra: void FUN_00059268(uint *param_1,uint param_2)
 * Stores a 4-byte tag (byte-swapped into a second word) into a 9-byte record. */
static void
txm_store_tag_swapped(uint32_t *rec, uint32_t tag)
{
    *rec = tag;
    if (rec + 1 <= (uint32_t *)((char *)rec + 9)) {
        uint32_t t = (tag & 0xff00ff00) >> 8 | (tag & 0xff00ff) << 8;
        *(uint8_t *)(rec + 2) = 0;
        rec[1] = t >> 0x10 | t << 0x10;
        return;
    }
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_000592a8 @ 0x000592a8  (est. txm_store_tag_swapped_ptr)
 * Ghidra: void FUN_000592a8(undefined8 param_1,undefined4 *param_2) */
static void
txm_store_tag_swapped_ptr(uint64_t rec, uint32_t *tag)
{
    txm_store_tag_swapped(rec, *tag);
}

/* ============================================================================
 * FUN_000592b4 @ 0x000592b4  (est. txm_manifest_trust_evaluate)
 * Ghidra: ulong FUN_000592b4(undefined8 *param_1,long param_2,long param_3,undefined8 param_4,...)
 * The manifest trust-evaluation hub: allocates the anti-replay policy object
 *   (FUN_00057ed0 via DAT_0000d7c8 / DAT_0000d7b0), boots the chip environment
 *   (FUN_00056e00), prepares anti-replay (FUN_0005c61c/FUN_0005c6d4), performs
 *   the manifest trust evaluation (FUN_00059628 / FUN_000596b8 depending on
 *   param_3) and the anti-replay replay check (FUN_0005c944). Logs
 *   "chip environment not booted %s", "failed to prepare anti-replay",
 *   "trust evaluation failed %d", "manifest replay denied %d".
 * Confidence: medium. */
static uint64_t
txm_manifest_trust_evaluate(uint64_t *rec, uint64_t impl, uint64_t flag, uint64_t p4, uint64_t p5)
{
    uint64_t saved = txm_canary;
    uint64_t *ar = 0, *sp = 0;
    uint64_t obj = rec[0], code = rec[1];
    uint64_t (*trust)(uint64_t *, uint64_t, uint64_t) = txm_decode_trust_eval;  /* FUN_00059628 */
    if (flag == 0)
        trust = txm_decode_trust_eval2;          /* FUN_000596b8 */
    uint64_t lvl = txm_env_level(0xd7c8);        /* FUN_00052da8 */
    if (lvl < 2)
        lvl = 1;
    if (lvl == 1) {
        /* alloca-style stack frame + zero init */
        ar = (uint64_t *)(0);
        /* fallthrough */
        ar = (uint64_t *)txm_impl_vtable_dispatch(obj, 0xd7c8, (uint64_t *)&ar);
    } else if (lvl == 2) {
        ar = (uint64_t *)txm_impl_vtable_dispatch(obj, 0xd7c8, (uint64_t *)&ar);
        if (ar == 0) {
            txm_optional_not_set();
            ar = (uint64_t *)(0);
        }
    } else {
        txm_panic_fmt("panic: unreachable case %s 0x");
    }
    uint64_t chip = txm_decode_impl_dispatch_result(impl, obj, (uint64_t)ar);  /* FUN_00056e00 */
    if (chip == 0) {
        txm_panic_fmt("chip environment not booted %s");
        return 0x52;
    }
    lvl = txm_env_level(0xd7b0);
    if (lvl < 2)
        lvl = 1;
    uint64_t *sp2;
    if (lvl == 1) {
        /* alloca + zero init */
        sp2 = (uint64_t *)(0);
    } else if (lvl == 2) {
        sp2 = (uint64_t *)txm_impl_vtable_dispatch(obj, 0xd7b0, (uint64_t *)&sp2);
        if (sp2 == 0) {
            sp2 = (uint64_t *)(0);
        }
    } else {
        txm_panic_fmt("panic: unreachable case %s 0x");
    }
    uint64_t policy = txm_policy_init(sp2, obj, rec, impl);   /* FUN_0005c61c */
    uint64_t rc = txm_policy_prepare();                        /* FUN_0005c6d4 */
    if ((int)rc == 0) {
        if ((code != 0) && (*(uint64_t *)(code + 0x20) != 0)) {
            ((void (*)(uint64_t *, uint64_t, uint64_t))(*(uint64_t *)(code + 0x20)))(rec, policy, rec[2]);
        }
        ar[5] = (uint64_t)(rec);
        int t = trust(rec, (uint64_t)rec, (uint64_t)ar);
        if (t == 0) {
            rc = txm_policy_replay_check(policy);              /* FUN_0005c944 */
            if ((int)rc == 0) {
                rc = 0;
                goto out;
            }
            txm_panic_fmt("manifest replay denied %d");
        } else {
            rc = 0xffffffff & 0xffffffff;
            txm_panic_fmt("trust evaluation failed %d");
        }
    } else {
        txm_panic_fmt("failed to prepare anti-replay %s");
    }
out:
    txm_digest_release(obj, 0xd7c8, (uint64_t *)&ar);
    txm_digest_release(obj, 0xd7b0, (uint64_t *)&sp);
    if (rc < 0x6c) {
        if (txm_canary != saved)
            txm_stack_check();
        return rc;
    }
    txm_panic_fmt("panic: error not set to valid po");
    return rc;
}

/* ============================================================================
 * FUN_00059628 @ 0x00059628  (est. txm_decode_trust_eval)
 * Ghidra: undefined8 FUN_00059628(undefined8 *param_1,long param_2,undefined8 param_3)
 * Performs Img4DecodePerformTrustEvaluation when the manifest flag is set
 *   (rec+0x42), else panics via FUN_0005a4ec. Logs "Img4DecodePerformTrustEvaluation". */
static uint64_t
txm_decode_trust_eval(uint64_t *rec, uint64_t impl, uint64_t p3)
{
    if (*(int16_t *)(rec + 0x42) != 0) {
        uint64_t rc = 0;   /* FUN_000456f8(**(uint32 **)(*(uint64_t *)(impl+0x10)+8), rec+9, impl+0x20, impl+0x28, p3) */
        if ((int)rc != 0)
            txm_panic_fmt("Img4DecodePerformTrustEvaluation");
        txm_trust_eval_record(rec, rc, p3);    /* FUN_0005a04c */
        return rc;
    }
    txm_unreachable();                         /* FUN_0005a4ec */
}

/* ============================================================================
 * FUN_000596b8 @ 0x000596b8  (est. txm_decode_trust_eval2)
 * Ghidra: undefined8 FUN_000596b8(undefined8 *param_1,long param_2,undefined8 param_3)
 * Manifest-trust evaluation variant. Logs
 *   "Img4DecodePerformManifestTrustEv". */
static uint64_t
txm_decode_trust_eval2(uint64_t *rec, uint64_t impl, uint64_t p3)
{
    if (*(int16_t *)(rec + 0x42) != 0) {
        uint64_t rc = 0;   /* FUN_00061e08(rec+9, impl+0x20, impl+0x28, p3) */
        if ((int)rc != 0)
            txm_panic_fmt("Img4DecodePerformManifestTrustEv");
        txm_trust_eval_record(rec, rc, p3);
        return rc;
    }
    txm_unreachable();
}

/* ============================================================================
 * FUN_00059740 @ 0x00059740  (est. txm_img4_decode_init_manifest)
 * Ghidra: long * FUN_00059740(long *param_1,long param_2,undefined8 param_3)
 * Initializes an img4 manifest decode object: stores the context, zeroes the
 *   0x208-byte scratch, sets the restore-info callback (FUN_00052318), and
 *   marks it initialized (rec+8 = 1). */
static uint64_t *
txm_img4_decode_init_manifest(uint64_t *rec, uint64_t ctx, uint64_t restore)
{
    if (ctx == 0)
        ctx = txm_percpu_state();
    rec[1] = 0;
    rec[2] = 0;
    rec[0] = ctx;
    txm_bzero(rec + 3, 0x208);
    txm_img4_set_restore(rec + 3, restore);    /* FUN_00052318 */
    *(int16_t *)(rec + 8) = 1;
    return rec;
}

/* ============================================================================
 * FUN_0005979c @ 0x0005979c  (est. txm_manifest_constraint_ctx)
 * Ghidra: long * FUN_0005979c(long *param_1,long param_2,long param_3)
 * Initializes the manifest execution-policy constraint context (0x220 bytes
 *   of zeroed state), stores the profile (param_3) and marks it active. */
static uint64_t *
txm_manifest_constraint_ctx(uint64_t *rec, uint64_t ctx, uint64_t profile)
{
    if (ctx == 0)
        ctx = txm_percpu_state();
    rec[1] = 0;
    rec[2] = 0;
    rec[0] = ctx;
    uint64_t *p = rec + 3;
    for (int i = 0; i < 0x40; i++)
        p[i] = 0;
    rec[0x43] = profile;
    /* FUN_00052370(rec+3, profile) */
    *(int16_t *)(rec + 8) = 1;
    return rec;
}

/* ============================================================================
 * FUN_00059854 @ 0x00059854  (est. txm_img4_decode_init_payload)
 * Ghidra: long * FUN_00059854(long *param_1,long param_2,undefined8 param_3)
 * Initializes an img4 payload decode object (FUN_000522f4 for the payload
 *   restore-info callback). */
static uint64_t *
txm_img4_decode_init_payload(uint64_t *rec, uint64_t ctx, uint64_t restore)
{
    if (ctx == 0)
        ctx = txm_percpu_state();
    rec[1] = 0;
    rec[2] = 0;
    rec[0] = ctx;
    txm_bzero(rec + 3, 0x208);
    txm_img4_set_restore(rec + 3, restore);    /* FUN_000522f4 */
    *(int16_t *)(rec + 8) = 1;
    return rec;
}

/* ============================================================================
 * FUN_000598b0 @ 0x000598b0  (est. txm_record_attach)
 * Ghidra: void FUN_000598b0(long param_1,undefined8 param_2,undefined8 param_3)
 * Attaches the property-set (param_3) and context (param_2) to a record. */
static void
txm_record_attach(uint64_t rec, uint64_t ctx, uint64_t propset)
{
    *(uint64_t *)(rec + 8) = propset;
    *(uint64_t *)(rec + 0x10) = ctx;
}

/* ============================================================================
 * FUN_000598bc @ 0x000598bc  (est. txm_manifest_decode_init)
 * Ghidra: undefined8 FUN_000598bc(undefined8 *param_1)
 * Decodes the manifest body (FUN_000579c8) into the object's property
 *   set, sets the manifest flag (rec+0x42), or maps the error via
 *   FUN_0005793c ("Img4DecodeInitAsManifest %d"). */
static uint64_t
txm_manifest_decode_init(uint64_t *rec)
{
    uint64_t *base = (*(int16_t *)(rec + 8) != 0) ? rec + 8 : 0;
    uint64_t *prop = (*(int16_t *)(rec + 8) != 0) ? rec + 3 : 0;
    uint64_t len = rec[3];
    if (prop + 5 <= base || len + rec[4] < len)
        txm_panic_bounds(0x19);
    int r = txm_decode_manifest_if_mode(len, rec[4], (uint64_t)(rec + 9));  /* FUN_000579c8 */
    if (r == 0) {
        *(int16_t *)(rec + 0x42) = 1;
        return 0;
    }
    uint64_t e = txm_errno_lookup();
    txm_panic_fmt("Img4DecodeInitAsManifest %d");
    if (e > 0x6b)
        txm_panic_fmt("panic: error not set to valid po");
    return e;
}

/* ============================================================================
 * FUN_00059980 @ 0x00059980  (est. txm_manifest_restore_lookup)
 * Ghidra: long FUN_00059980(long param_1)
 * Restores a manifest's restore-info record (rec+0x48) if the restore flag
 *   (rec+0x210) is set; panics "Img4DecodeRestoreInfoExis" on failure. */
static uint64_t
txm_manifest_restore_lookup(uint64_t rec)
{
    if (*(int16_t *)(rec + 0x210) == 0)
        txm_unreachable();                     /* FUN_0005a4ec */
    rec = rec + 0x48;
    uint8_t ok = 0;
    int r = 0;                                /* FUN_000450dc(rec, &ok) */
    if (r == 0) {
        if ((ok & 1) == 0)
            rec = 0;
        return rec;
    }
    txm_panic_fmt("panic: Img4DecodeRestoreInfoExis");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_000599e4 @ 0x000599e4  (est. txm_manifest_get_raw)
 * Ghidra: void FUN_000599e4(long param_1,undefined8 param_2)
 * Copies the raw manifest bytes (rec+0x48) into param_2 via FUN_000522d8,
 *   obtaining them through FUN_00061a34; panics "Img4DecodeGetManifest %d". */
static void
txm_manifest_get_raw(uint64_t rec, uint64_t out)
{
    uint64_t base = (*(int16_t *)(rec + 0x210) != 0) ? rec + 0x48 : 0;
    uint64_t a = 0;
    uint32_t n = 0;
    int r = txm_decode_get_manifest(base, &a, &n);    /* FUN_00061a34 */
    if (r == 0) {
        txm_img4_copy_manifest(out, a, n);            /* FUN_000522d8 */
        return;
    }
    txm_panic_fmt("panic: Img4DecodeGetManifest %d");
}

/* ============================================================================
 * FUN_00059a54 @ 0x00059a54  (est. txm_manifest_trust_eval_call)
 * Ghidra: void FUN_00059a54(void) — thunk to FUN_000592b4 (trust evaluation). */
static void
txm_manifest_trust_eval_call(void)
{
    (void)txm_manifest_trust_evaluate(0, 0, 0, 0, 0);
}

/* ============================================================================
 * FUN_00059a90 @ 0x00059a90  (est. txm_img4_get_property_dispatch)
 * Ghidra: undefined8 * FUN_00059a90(undefined8 param_1,undefined8 param_2,ulong param_3,long param_4)
 * Image4 property-getter dispatcher: for a property container tag
 *   (param_3, 0-6), invokes the associated getter callback
 *   (bool/uint32/uint64/data) from the object's method table (param_4+0x10).
 *   Panics "bogus property container index" for index > 6. */
static uint64_t *
txm_img4_get_property_dispatch(uint64_t key, uint64_t obj, uint64_t tag, uint64_t rec)
{
    uint32_t kind = (uint32_t)tag;
    if (kind > 6)
        txm_panic_fmt("panic: bogus property container i");
    if (kind == 1) {
        uint64_t *ep = *(uint64_t **)(rec + 0x28);
        uint64_t *base = (uint64_t *)*ep;
        uint64_t len = ep[1];
        uint64_t tagrec[2] = {0, 0};
        uint64_t t = txm_store_tag_swapped(&tagrec, key);  /* FUN_00059268 */
        uint64_t set = txm_property_set_by_tag(t, 1);      /* FUN_0005b074 */
        if ((set != 0) && (txm_policy_impose(base, set, len, obj, ep) != 0)) {   /* FUN_0005a0ac */
            *(int *)(ep + 8) = 0;
            txm_panic_fmt("object property failed to impose");
            return (uint64_t *)((uintptr_t)&((struct{int magic;}){0}.magic) + 3);
        }
        if (base + 0x44 <= base)
            txm_panic_bounds(0x19);
        txm_img4_get_property_apply(base, 1, key, obj);    /* FUN_00059c48 */
        return 0;
    }
    if (kind != 0) {
        uint64_t *get = txm_type_property_table();         /* FUN_0005a4fc */
        uint64_t obj2 = get[0], reg = get[1];
        uint64_t *m = (uint64_t *)obj2[1];
        uint64_t tagrec[4] = {0, 0, 0, 0};
        if (m == 0)
            return obj2;
        uint64_t t = txm_store_tag_swapped(&tagrec, tag);  /* FUN_00059268 */
        uint64_t vtype = *(uint64_t *)(rec + 0x10);
        if (vtype == 4) {
            if (m[2] == 0)
                return (uint64_t *)t;
            uint64_t a = 0, b = 0;
            if (txm_img4_get_data(rec, tag, &a, &b) == 0)   /* FUN_00045364 */
                return (uint64_t *)((uint64_t (*)(uint64_t *, uint64_t *, uint64_t, uint64_t, uint64_t, uint64_t))m[2])(obj2, &tagrec, reg, a, b, obj2[2]);
            txm_panic_fmt("Img4DecodeGetPropertyData %s");
        } else if (vtype == 2) {
            if (m[1] == 0)
                return (uint64_t *)t;
            uint64_t v = 0;
            if (txm_decode_get_uint64(rec, tag, &v) == 0)   /* FUN_00061ae4 */
                return (uint64_t *)((uint64_t (*)(uint64_t *, uint64_t *, uint64_t, uint64_t, uint64_t))m[1])(obj2, &tagrec, reg, v, obj2[2]);
            txm_panic_fmt("Img4DecodeGetPropertyInteger64 %s");
        } else {
            if (vtype != 1)
                txm_panic_fmt("panic: unreachable case %s 0x");
            if (m[0] == 0)
                return (uint64_t *)t;
            uint8_t v = 0;
            if (txm_decode_get_bool(rec, tag, &v) == 0)     /* FUN_00061b48 */
                return (uint64_t *)((uint64_t (*)(uint64_t *, uint64_t *, uint64_t, uint64_t, uint64_t))m[0])(obj2, &tagrec, reg, v & 1, obj2[2]);
            txm_panic_fmt("Img4DecodeGetPropertyBoolean %s");
        }
        txm_log_level(reg, 0);
        return 0;
    }
    {
        uint64_t *ep = *(uint64_t **)(rec + 0x28);
        uint64_t *base = (uint64_t *)*ep;
        uint64_t len = ep[1];
        uint64_t off = ep[6];
        uint64_t tagrec[2] = {0, 0};
        uint64_t t = txm_store_tag_swapped(&tagrec, key);
        uint64_t set = txm_property_set_by_tag(t, 0);       /* FUN_0005b074 */
        if (set == 0) {
            if (base + 0x44 <= base || t + 0xc <= t)
                txm_panic_bounds(0x19);
        } else {
            int r = txm_property_impose_env(off, set, obj);  /* FUN_0005c864 */
            if ((r != 0) && (txm_policy_impose(base, set, len, obj, ep) != 0)) {
                *(int *)(ep + 8) = r;
                txm_panic_fmt("property failed to impose on env");
                return 0;
            }
            if (base + 0x44 <= base)
                txm_panic_bounds(0x19);
        }
        txm_img4_get_property_apply(base, 0, key, obj);
        return 0;
    }
}

/* ============================================================================
 * FUN_00059c48 @ 0x00059c48  (est. txm_img4_get_property_apply)
 * Ghidra: void FUN_00059c48(undefined8 *param_1,undefined8 param_2,ulong param_3,long param_4)
 * Applies a fetched property value to the object: invokes the appropriate
 *   getter callback (bool/uint32/uint64/data) from the object method table
 *   (param_4+0x10), logging on failure. */
static void
txm_img4_get_property_apply(uint64_t *obj, uint64_t reg, uint64_t tag, uint64_t rec)
{
    uint64_t *m = (uint64_t *)obj[1];
    uint64_t tagrec[4] = {0, 0, 0, 0};
    if (m == 0)
        return;
    txm_store_tag_swapped(&tagrec, tag);
    uint64_t vtype = *(uint64_t *)(rec + 0x10);
    if (vtype == 4) {
        if (m[2] == 0)
            return;
        uint64_t a = 0, b = 0;
        if (txm_img4_get_data(rec, tag, &a, &b) == 0) {
            ((void (*)(uint64_t *, uint64_t *, uint64_t, uint64_t, uint64_t, uint64_t))m[2])(obj, &tagrec, reg, a, b, obj[2]);
            return;
        }
        txm_panic_fmt("Img4DecodeGetPropertyData %s");
    } else if (vtype == 2) {
        if (m[1] == 0)
            return;
        uint64_t v = 0;
        if (txm_decode_get_uint64(rec, tag, &v) == 0) {
            ((void (*)(uint64_t *, uint64_t *, uint64_t, uint64_t, uint64_t))m[1])(obj, &tagrec, reg, v, obj[2]);
            return;
        }
        txm_panic_fmt("Img4DecodeGetPropertyInteger64 %s");
    } else {
        if (vtype != 1)
            txm_panic_fmt("panic: unreachable case %s 0x");
        if (m[0] == 0)
            return;
        uint8_t v = 0;
        if (txm_decode_get_bool(rec, tag, &v) == 0) {
            ((void (*)(uint64_t *, uint64_t *, uint64_t, uint64_t, uint64_t))m[0])(obj, &tagrec, reg, v & 1, obj[2]);
            return;
        }
        txm_panic_fmt("Img4DecodeGetPropertyBoolean %s");
    }
    txm_log_level(obj[0], 0);
}

/* ============================================================================
 * FUN_00059e14 @ 0x00059e14  (est. txm_manifest_digest_compute)
 * Ghidra: void FUN_00059e14(undefined8 *param_1,long param_2,undefined8 param_3)
 * Computes the manifest digest: allocates the decode implementation via
 *   DAT_0000d7c8 (FUN_00057ed0/FUN_00056e00), extracts the manifest digest
 *   (FUN_00061960) and writes it into param_3. Panics
 *   "Img4DecodeCopyManifestDig" on failure. */
static void
txm_manifest_digest_compute(uint64_t *rec, uint64_t impl, uint64_t out)
{
    uint64_t saved = txm_canary;
    uint64_t obj = rec[0];
    uint64_t *d = 0;
    uint8_t *manifest = (*(int16_t *)(rec + 0x42) != 0) ? (uint8_t *)(rec + 9) : 0;
    uint64_t digest[0x20] = {0};
    uint64_t lvl = txm_env_level(0xd7c8);
    if (lvl < 2)
        lvl = 1;
    uint64_t *dec;
    if (lvl == 1) {
        /* alloca + zero */
        dec = (uint64_t *)(0);
    } else if (lvl == 2) {
        dec = (uint64_t *)txm_impl_vtable_dispatch(obj, 0xd7c8, (uint64_t *)&dec);
        if (dec == 0)
            dec = (uint64_t *)(0);
    } else {
        txm_panic_fmt("panic: unreachable case %s 0x");
    }
    uint64_t chip = txm_decode_impl_dispatch_result(impl, obj, (uint64_t)dec);
    if (chip == 0)
        txm_panic_fmt("panic: no decode implementation a");
    uint64_t len = **(uint64_t **)(chip + 0x20);
    if (len > 0x40)
        txm_panic_bounds(0x19);
    uint64_t rc = txm_decode_copy_manifest_digest(manifest, digest, len);  /* FUN_00061960 */
    if ((int)rc == 0) {
        txm_digest_release(obj, 0xd7c8, (uint64_t *)&dec);
        txm_digest_set_bytes(out, digest, len);   /* FUN_00057b58 */
        if (txm_canary != saved)
            txm_stack_check();
        return;
    }
    txm_panic_fmt("panic: Img4DecodeCopyManifestDig");
}

/* ============================================================================
 * FUN_00059fe8 @ 0x00059fe8  (est. txm_manifest_payload_digest_release)
 * Ghidra: void FUN_00059fe8(long *param_1)
 * Releases a manifest/payload digest record: tears down the backing
 *   digest object (FUN_000523a0), clears the active flag and frees the
 *   outer record (FUN_0005244c). */
static void
txm_manifest_payload_digest_release(uint64_t *rec)
{
    uint64_t l = *rec;
    if (l != 0) {
        if (*(int16_t *)(l + 0x40) == 0)
            txm_unreachable();                 /* FUN_0005a4ec */
        uint64_t local = l + 0x18;
        if (*(uint64_t *)(l + 0x218) != 0)
            txm_img4_teardown(*(uint64_t *)(l + 0x218), &local);   /* FUN_000523a0 */
        *(int16_t *)(l + 0x40) = 0;
        /* FUN_0005244c(&local) */
        *rec = 0;
    }
}

/* ============================================================================
 * FUN_0005a04c @ 0x0005a04c  (est. txm_trust_eval_record)
 * Ghidra: void FUN_0005a04c(undefined8 *param_1,int param_2,long param_3)
 * Records a failed trust-evaluation result: sets the error code field to 0x50
 *   if not already set, and logs "trust evaluation %dr %d ct %d". */
static void
txm_trust_eval_record(uint64_t *rec, int rc, uint64_t eval)
{
    if (rc != 0) {
        if (*(int *)(*(uint64_t *)(eval + 0x28) + 0x40) == -1)
            *(uint32_t *)(*(uint64_t *)(eval + 0x28) + 0x40) = 0x50;
        txm_panic_fmt("trust evaluation %dr %d ct %d");
    }
}

/* ============================================================================
 * FUN_0005a0ac @ 0x0005a0ac  (est. txm_policy_impose)
 * Ghidra: undefined8 FUN_0005a0ac(undefined8 *param_1,long param_2,undefined8 param_3,...)
 * Imposes an img4 property-set constraint on an object: for each property in
 *   the set (param_3), resolves the constraint type and value (bool/uint32/
 *   uint64/digest/digest64) from the decode object and enforces it via
 *   FUN_0005b224/430/610/7f0/bb1c. Returns 0 on success.
 * Confidence: medium. */
static uint64_t
txm_policy_impose(uint64_t *rec, uint64_t set, uint64_t key, uint64_t obj, uint64_t *ep)
{
    uint64_t saved = txm_canary;
    uint64_t objname = rec[0];
    uint64_t def = txm_property_set_default(key);    /* FUN_00056d6c */
    uint64_t raw = 0, val = 0;
    uint32_t tag = *(uint32_t *)(set + 0x18);
    uint64_t prop = txm_property_override_lookup(key, set, *(uint64_t *)(ep + 0x18));  /* FUN_00056d88 */
    int ctype = *(int *)(prop + 0x38);
    uint64_t rc;
    if (ctype == 0) {
        rc = 0xd;
        goto impose;
    } else if (ctype == 1) {
        rc = 0x55;
        goto impose;
    } else if (ctype != 6) {
        txm_panic_fmt("panic: unreachable case %s 0x");
    }
impose:
    if (txm_property_available(prop, key) != 0) {        /* FUN_0005b180 */
        uint64_t vtype = **(uint64_t **)(prop + 0x28);
        if (vtype < 2) {
            if (vtype == 0) {
                uint8_t qv = 0;
                if (txm_decode_get_bool(obj, tag, &qv) != 0) {
                    txm_panic_fmt("Img4DecodeGetPropertyBoolean %d");
                    goto nxt;
                }
                rc = txm_property_bool_query(objname, key, prop, &val);   /* FUN_0005861c */
                if ((int)rc == 0)
                    rc = txm_enforce_bool_constraint(prop, objname, qv, &val);  /* FUN_0005b224 */
            } else if (vtype == 1) {
                uint32_t qv = 0;
                if (txm_decode_get_int(obj, tag, &qv) != 0) {
                    txm_panic_fmt("Img4DecodeGetPropertyInteger %d");
                    goto nxt;
                }
                rc = txm_property_uint32_query(objname, key, prop, &val);
                if ((int)rc == 0)
                    rc = txm_enforce_uint32_constraint(prop, objname, qv, &val); /* FUN_0005b430 */
            }
        } else if (vtype == 2) {
            uint64_t qv = 0;
            if (txm_decode_get_uint64(obj, tag, &qv) == 0) {
                rc = txm_property_uint64_query(objname, key, prop, &val);
                if ((int)rc == 0)
                    rc = txm_enforce_uint64_constraint(prop, objname, qv, &val); /* FUN_0005b610 */
            } else {
                txm_panic_fmt("Img4DecodeGetPropertyInteger64 %s");
                rc = txm_errno_lookup();
                goto nxt;
            }
        } else if (vtype == 3) {
            uint64_t a = 0; uint32_t b = 0;
            if (txm_img4_get_data(obj, tag, &a, &b) == 0) {
                txm_digest_set_bytes(&raw, a, b);
                if (txm_property_match(prop, def) == 0) {   /* FUN_0005b134 */
                    rc = txm_property_digest_query(objname, key, prop, &val);
                } else {
                    txm_digest_import_set(*(uint64_t *)(ep + 0x10), key, &val);  /* FUN_0005acd4 */
                }
                rc = txm_enforce_digest_constraint(prop, objname, &raw, &val);   /* FUN_0005b7f0 */
            }
        } else if (vtype == 4) {
            uint64_t a = 0; uint32_t b = 0;
            if (txm_img4_get_data(obj, tag, &a, &b) == 0) {
                txm_digest64_import(&raw, a, b);            /* FUN_0005d258 */
                rc = txm_property_digest64_query(objname, key, prop, &val);
                if ((int)rc == 0)
                    rc = txm_enforce_digest64_constraint(prop, objname, &raw, &val); /* FUN_0005bb1c */
            } else {
                txm_panic_fmt("Img4DecodeGetPropertyData %d");
                rc = txm_errno_lookup();
            }
        } else {
            txm_panic_fmt("panic: unreachable case %s 0x");
        }
nxt:
        if ((rec[1] != 0) && (*(uint64_t *)(rec[1] + 0x18) != 0)) {
            ((void (*)(uint64_t *, uint64_t, uint64_t, uint64_t))(*(uint64_t *)(rec[1] + 0x18)))(rec, key, prop, rec[2]);
        }
        if (rc > 0x6b)
            txm_panic_fmt("panic: error not set to valid po");
    } else {
        rc = 0;
    }
    if (txm_canary != saved)
        txm_stack_check();
    return rc;
}

/* ============================================================================
 * FUN_0005a4d4 @ 0x0005a4d4  (est. txm_optional_not_set)
 * Ghidra: void FUN_0005a4d4(void) — PAC-checks return address, then panics
 *   "optional not set". */
static void
txm_optional_not_set(void)
{
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a4e8);
    txm_panic_fmt("panic: optional not set");       /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_0005a4ec @ 0x0005a4ec  (est. txm_unreachable)
 * Ghidra: void FUN_0005a4ec(void) — calls txm_optional_not_set then panics
 *   "unreachable". */
static void
txm_unreachable(void)
{
    txm_optional_not_set();
    txm_panic_fmt("panic: unreachable");            /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_0005a4fc @ 0x0005a4fc  (est. txm_type_property_table)
 * Ghidra: void FUN_0005a4fc(void) — panics "unreachable". */
static uint64_t *
txm_type_property_table(void)
{
    txm_panic_fmt("panic: unreachable");
    return 0;
}

/* ============================================================================
 * FUN_0005a514 @ 0x0005a514  (est. txm_manifest_needs_restore)
 * Ghidra: bool FUN_0005a514(undefined8 param_1,long param_2)
 * Returns true when the property set (param_2+0x10) is unresolvable or the
 *   manifest's restore flag (param_2+0x210) is clear. */
static bool
txm_manifest_needs_restore(uint64_t key, uint64_t rec)
{
    if (txm_property_get_oid(key, *(uint64_t *)(rec + 0x10)) == 0)   /* FUN_00052a34 */
        return true;
    return *(int16_t *)(rec + 0x210) == 0;
}

/* ============================================================================
 * FUN_0005a554 @ 0x0005a554  (est. txm_boot_chain_integrity_check)
 * Ghidra: uint FUN_0005a554(long param_1,undefined8 *param_2)
 * Enforces the boot-chain-integrity constraint on a manifest: computes the
 *   manifest digest (FUN_00059e14) and enforces it (FUN_0005b7f0). Logs
 *   "odometer %s %s boot_chain_integrity". */
static uint32_t
txm_boot_chain_integrity_check(uint64_t base, uint64_t *rec)
{
    uint64_t saved = txm_canary;
    uint64_t name = rec[0], obj = rec[1], prop = rec[2];
    uint64_t context = txm_property_get_oid(base, prop);
    uint64_t digest[0x20] = {0};
    if (*(int16_t *)(rec + 0x42) == 0) {
        txm_optional_not_set();                       /* FUN_00051c78 */
    } else {
        txm_manifest_digest_compute(obj, prop, digest);    /* FUN_00059e14 */
        if (txm_enforce_digest_constraint(context, name, digest, rec + 0x38) == 0) {  /* FUN_0005b7f0 */
            if (txm_canary == saved)
                return 0;
        } else {
            uint32_t e = *(uint32_t *)(base + 0x18);
            uint64_t m = *rec;
            txm_optional_not_set();
            txm_panic_fmt("odometer %s %s boot_chain_inte");
            if (e > 0x6b)
                txm_panic_fmt("panic: error not set to valid po");
            if (txm_canary == saved)
                return e;
        }
    }
    txm_stack_check();
    return 0;
}

/* ============================================================================
 * FUN_0005a664 / FUN_0005a668 @ 0x0005a664/0x5a668  (est. txm_vtable_dispatch_80_ctx)
 * Ghidra: void FUN_0005a664/0x5a668(void) — PAC-check, then dispatch through
 *   +0x80 on the per-CPU context. */
static void
txm_vtable_dispatch_80_ctx_a(void)
{
    uint64_t ctx = txm_percpu_context();
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a68c);
    txm_vtable_dispatch_80(ctx, 0);        /* FUN_0005860c */
}
static void
txm_vtable_dispatch_80_ctx_b(void)
{
    uint64_t ctx = txm_percpu_context();
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a68c);
    txm_vtable_dispatch_80(ctx, 0);
}

/* ============================================================================
 * FUN_0005a690 @ 0x0005a690  (est. txm_current_object)
 * Ghidra: void FUN_0005a690(void)
 * Returns the current decode object: queries via FUN_0005856c (vtable +0x78)
 *   and falls back to 0, then dispatches through +0x80. */
static uint64_t
txm_current_object(void)
{
    uint64_t ctx = txm_percpu_context();
    uint64_t obj = 0;
    int r = txm_vtable_dispatch_78(ctx, &obj);   /* FUN_0005856c */
    if (r != 0)
        obj = 0;
    txm_vtable_dispatch_80(ctx, obj);            /* FUN_0005860c */
    return obj;
}

/* ============================================================================
 * FUN_0005a6e4 @ 0x0005a6e4  (est. txm_nonce_set)
 * Ghidra: long FUN_0005a6e4(long param_1,undefined8 param_2,ulong param_3)
 * Stores a nonce (max 0x10 bytes) into an object, recording the length at
 *   +0x10. Panics "nonce too large" otherwise. */
static uint64_t
txm_nonce_set(uint64_t obj, uint64_t src, uint64_t n)
{
    if (n < 0x11) {
        txm_memcpy(obj, src, n);
        *(uint64_t *)(obj + 0x10) = n;
        return obj;
    }
    txm_panic_fmt("panic: nonce too large: actual");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_0005a73c @ 0x0005a73c  (est. txm_nonce_copy_set)
 * Ghidra: void FUN_0005a73c(undefined8 param_1,long param_2)
 * Copies a nonce into param_1 from param_2+0x10 length; bounds-checked. */
static void
txm_nonce_copy_set(uint64_t dst, uint64_t src)
{
    if (0x10 < *(uint64_t *)(src + 0x10))
        txm_panic_bounds(0x19);
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a758);
    txm_nonce_set(dst, src + 0x10);
}

/* ============================================================================
 * FUN_0005a770 @ 0x0005a770  (est. txm_nonce_equal)
 * Ghidra: undefined8 FUN_0005a770(long param_1,long param_2)
 * Compares two nonces; 0xffffffff if lengths differ, else memcmp of the data. */
static uint64_t
txm_nonce_equal(uint64_t a, uint64_t b)
{
    if (*(uint64_t *)(a + 0x10) != *(uint64_t *)(b + 0x10))
        return 0xffffffff;
    if (*(uint64_t *)(a + 0x10) < 0x11) {
        uint64_t lr = (uint64_t)__builtin_return_address(0);
        if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
            txm_breakpoint(0xc471, 0x5a798);
        return txm_memcmp(a, b, 0);
    }
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_0005a7c4 / FUN_0005a7c8 @ 0x0005a7c4/0x5a7c8  (est. txm_percpu_ctx_reval)
 * Ghidra: void FUN_0005a7c4/0x5a7c8(void) — per-CPU ctx revalidation pair
 *   (identical to 0x564d8 family). */
static void
txm_percpu_ctx_reval_a(void)
{
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    (void)txm_percpu_state();
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a7e8);
    /* FUN_00054848 */
}
static void
txm_percpu_ctx_reval_b(void)
{
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    (void)txm_percpu_state();
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a7e8);
    /* FUN_00054848 */
}

/* ============================================================================
 * FUN_0005a7ec @ 0x0005a7ec  (est. txm_percpu_ctx_validate2)
 * Ghidra: void FUN_0005a7ec(void) — per-CPU ctx validate (FUN_000548a8). */
static void
txm_percpu_ctx_validate2(void)
{
    uint64_t ctx = txm_percpu_state();
    /* FUN_000548a8(&ctx) */
}

/* ============================================================================
 * FUN_0005a818 / FUN_0005a81c @ 0x0005a818/0x5a81c  (est. txm_impl_type_label)
 * Ghidra: undefined * FUN_0005a818/0x5a81c(undefined8 param_1,undefined8 param_2)
 * Returns the implementation type label (DAT_00019dd0 vs DAT_0001aa60) based
 *   on the decoded object at +0x48. */
static uint64_t
txm_impl_type_label(uint64_t a, uint64_t obj)
{
    uint64_t o = txm_vtable_dispatch_80(obj, 0);
    if (*(uint64_t *)(o + 0x48) != 0)
        return 0x19dd0;
    return 0x1aa60;
}

/* ============================================================================
 * FUN_0005a854 @ 0x0005a854  (est. txm_impl_stub_ok)
 * Ghidra: undefined8 FUN_0005a854(void) — returns 0. */
static uint64_t
txm_impl_stub_ok(void)
{
    return 0;
}

/* ============================================================================
 * FUN_0005a860 @ 0x0005a860  (est. txm_impl_stub_bad)
 * Ghidra: undefined8 FUN_0005a860(void) — returns 0x2d. */
static uint64_t
txm_impl_stub_bad(void)
{
    return 0x2d;
}

/* ============================================================================
 * FUN_0005a86c @ 0x0005a86c  (est. txm_impl_stub_void)
 * Ghidra: void FUN_0005a86c(void) — no-op. */
static void
txm_impl_stub_void(void)
{
}

/* ============================================================================
 * FUN_0005a874 / FUN_0005a878 @ 0x0005a874/0x5a878  (est. txm_impl_ctx_reval)
 * Ghidra: void FUN_0005a874/0x5a878(void) — per-CPU ctx revalidation pair. */
static void
txm_impl_ctx_reval_a(void)
{
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    (void)txm_percpu_state();
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a898);
    /* FUN_00054848 */
}
static void
txm_impl_ctx_reval_b(void)
{
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    (void)txm_percpu_state();
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a898);
    /* FUN_00054848 */
}

/* ============================================================================
 * FUN_0005a89c @ 0x0005a89c  (est. txm_impl_ctx_validate)
 * Ghidra: void FUN_0005a89c(void) — per-CPU ctx validate. */
static void
txm_impl_ctx_validate(void)
{
    uint64_t ctx = txm_percpu_state();
    /* FUN_000548a8(&ctx) */
}

/* ============================================================================
 * FUN_0005a8c8 @ 0x0005a8c8  (est. txm_impl_ctx_name)
 * Ghidra: undefined * FUN_0005a8c8(void) — returns a constant string/name
 *   pointer (DAT_000159a8). */
static uint64_t
txm_impl_ctx_name(void)
{
    return 0x159a8;
}

/* ============================================================================
 * FUN_0005a8d8 @ 0x0005a8d8  (est. txm_guest_count)
 * Ghidra: undefined8 FUN_0005a8d8(void)
 * Returns the guest count from the current object (+0x70); panics via
 *   FUN_0005a96c if unavailable. */
static uint64_t
txm_guest_count(void)
{
    uint64_t o = txm_current_object();
    if (*(uint64_t *)(o + 0x70) != 0)
        return **(uint64_t **)(o + 0x70);
    if (o < o + 0x110)
        txm_panic_no_guests();
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_0005a914 @ 0x0005a914  (est. txm_guest_index)
 * Ghidra: undefined8 FUN_0005a914(void)
 * Returns the current guest index from the object (+0x70+0x10); panics
 *   otherwise. */
static uint64_t
txm_guest_index(void)
{
    uint64_t o = txm_current_object();
    if (*(uint64_t *)(o + 0x70) != 0)
        return *(uint64_t *)(*(uint64_t *)(o + 0x70) + 0x10);
    if (o < o + 0x110)
        txm_panic_no_guests();
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_0005a950 @ 0x0005a950  (est. txm_panic_no_guests)
 * Ghidra: void FUN_0005a950(undefined8 param_1) — panics "no cryptex1 guests
 *   for %s". */
static void
txm_panic_no_guests(void)
{
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a968);
    txm_panic_fmt("panic: no cryptex1 guests for %s");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_0005a96c @ 0x0005a96c  (est. txm_panic_guest_unavailable)
 * Ghidra: void FUN_0005a96c(void) — optional-not-set + no-guests + unreachable. */
static void
txm_panic_guest_unavailable(void)
{
    txm_optional_not_set();
    txm_panic_no_guests();
    txm_unreachable();
}

/* ============================================================================
 * FUN_0005a98c / FUN_0005a990 @ 0x0005a98c/0x5a990  (est. txm_payload_digest_get)
 * Ghidra: void FUN_0005a98c/0x5a990(long param_1,undefined8 param_2)
 * Copies the payload bytes (param_1+0x30, length +0x38) into param_2 when the
 *   payload flag (+0x58) is set; else optional-not-set. */
static void
txm_payload_digest_get(uint64_t obj, uint64_t out)
{
    if (*(int16_t *)(obj + 0x58) == 0) {
        txm_optional_not_set();
        return;
    }
    uint64_t base = *(uint64_t *)(obj + 0x30);
    if (base + *(int64_t *)(obj + 0x38) < base)
        txm_panic_bounds(0x19);
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5a9d4);
    txm_img4_copy_manifest(out, base, *(uint64_t *)(obj + 0x38));  /* FUN_000522d8 */
}

/* ============================================================================
 * FUN_0005a9e4 @ 0x0005a9e4  (est. txm_payload_init_manifest)
 * Ghidra: long FUN_0005a9e4(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Initializes a payload object (FUN_0005aa30) and its manifest scratch
 *   (FUN_00052318), marking it active. */
static uint64_t
txm_payload_init_manifest(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t restore)
{
    txm_payload_init_core(obj, prop, ctx);      /* FUN_0005aa30 */
    txm_img4_set_restore(obj + 0x30, restore);  /* FUN_00052318 */
    *(int16_t *)(obj + 0x58) = 1;
    return obj;
}

/* ============================================================================
 * FUN_0005aa30 @ 0x0005aa30  (est. txm_payload_init_core)
 * Ghidra: void FUN_0005aa30(long *param_1,undefined8 param_2,long param_3)
 * Initializes the payload object core: context, property tag (via
 *   FUN_000592a8), method table pointer (DAT_0001d528), zeroed state. */
static void
txm_payload_init_core(uint64_t *obj, uint64_t prop, uint64_t ctx)
{
    if (ctx == 0)
        ctx = txm_percpu_state();
    obj[0] = ctx;
    uint64_t tag = txm_store_tag_swapped_ptr((uint64_t)(obj + 2), prop);  /* FUN_000592a8 */
    obj[1] = tag;
    obj[4] = 0x1d528;
    uint64_t *p = obj + 5;
    for (int i = 0; i < 0x9; i++)
        p[i] = 0;
}

/* ============================================================================
 * FUN_0005aa8c @ 0x0005aa8c  (est. txm_payload_init_payload)
 * Ghidra: long FUN_0005aa8c(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Initializes a payload object with the payload restore callback
 *   (FUN_000522f4). */
static uint64_t
txm_payload_init_payload(uint64_t obj, uint64_t ctx, uint64_t prop, uint64_t restore)
{
    txm_payload_init_core(obj, prop, ctx);
    txm_img4_set_restore(obj + 0x30, restore);  /* FUN_000522f4 */
    *(int16_t *)(obj + 0x58) = 1;
    return obj;
}

/* ============================================================================
 * FUN_0005aad8 @ 0x0005aad8  (est. txm_payload_set_range)
 * Ghidra: void FUN_0005aad8(long param_1,undefined8 param_2,undefined8 param_3)
 * Stores the payload byte range (+0x20 base, +0x28 length). */
static void
txm_payload_set_range(uint64_t obj, uint64_t base, uint64_t len)
{
    *(uint64_t *)(obj + 0x20) = base;
    *(uint64_t *)(obj + 0x28) = len;
}

/* ============================================================================
 * FUN_0005aae4 @ 0x0005aae4  (est. txm_payload_type_check)
 * Ghidra: undefined8 FUN_0005aae4(undefined8 *param_1)
 * Validates the payload type tag against the object's expected type
 *   (FUN_0004507c); panics "unexpected payload type" on mismatch. */
static uint64_t
txm_payload_type_check(uint64_t *obj)
{
    uint32_t t = 0;
    if ((int)txm_env_query() == 0) {      /* FUN_0005abf4 */
        if (txm_get_property_oid(obj + 0xe, &t) != 0) {   /* FUN_0004507c */
            uint64_t e = txm_errno_lookup();
            txm_panic_fmt("%s Img4DecodeGetPayloadType %d");
            if (e > 0x6b)
                txm_panic_fmt("panic: error not set to valid po");
            return e;
        }
        if (*(uint32_t *)obj[1] == t) {
            return 0;
        }
        uint32_t s = (t & 0xff00ff00) >> 8 | (t & 0xff00ff) << 8;
        s = s >> 0x10 | s << 0x10;
        /* FUN_0002ee48(&swap,&s,4,5) */
        txm_panic_fmt("%s unexpected payload type: act");
        return 0x4f;
    }
    return 0;
}

/* ============================================================================
 * FUN_0005abf4 @ 0x0005abf4  (est. txm_payload_decode_init)
 * Ghidra: undefined8 FUN_0005abf4(undefined8 *param_1)
 * Decodes the payload body (FUN_00057960) into the object; promotes the
 *   method table from DAT_0001d528 to DAT_0001d540 on success. */
static uint64_t
txm_payload_decode_init(uint64_t *obj)
{
    if (*(int16_t *)(obj + 0xb) != 0) {
        uint64_t base = obj[6];
        if (base + obj[7] < base)
            txm_panic_bounds(0x19);
        int r = txm_decode_payload_if_mode(base, obj[7], (uint64_t)(obj + 0xe));  /* FUN_00057960 */
        if (r != 0) {
            uint64_t e = txm_errno_lookup();
            txm_panic_fmt("%s Img4DecodeInitAsPayload %d");
            if (e < 0x6c)
                return e;
            txm_panic_fmt("panic: error not set to valid po");
        }
        obj[0xd] = (uint64_t)(obj + 0xe);
        if (obj[4] == 0x1d528) {
            obj[4] = 0x1d540;
            return 0;
        }
    }
    return 0;
}

/* ============================================================================
 * FUN_0005accc @ 0x0005accc  (est. txm_env_query_thunk)
 * Ghidra: void thunk_FUN_0005abf4(void) — thunk to payload decode init. */
static void
txm_env_query_thunk(void)
{
    (void)txm_env_query();
}

/* ============================================================================
 * FUN_0005acd4 @ 0x0005acd4  (est. txm_digest_import_set)
 * Ghidra: void FUN_0005acd4(long param_1)
 * Imports a digest through the object's method-table +0x20 hook. */
static void
txm_digest_import_set(uint64_t obj, uint64_t key, uint64_t *out)
{
    (*(uint64_t (**)(void))(*(uint64_t *)(obj + 0x20)))();
}

/* ============================================================================
 * FUN_0005ace8 @ 0x0005ace8  (est. txm_digest_import_dispatch)
 * Ghidra: void FUN_0005ace8(long param_1,undefined8 param_2)
 * Dispatches digest import through the method table (+0x20 + 8). */
static void
txm_digest_import_dispatch(uint64_t obj, uint64_t arg)
{
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(obj + 0x20) + 8)))(obj, arg, *(uint64_t *)(obj + 0x28));
}

/* ============================================================================
 * FUN_0005acfc @ 0x0005acfc  (est. txm_digest_import_copy)
 * Ghidra: void FUN_0005acfc(long param_1,undefined8 param_2)
 * Copies the imported digest into param_2 via FUN_000522d8. */
static void
txm_digest_import_copy(uint64_t obj, uint64_t out)
{
    txm_img4_copy_manifest(out, *(uint64_t *)(*(uint64_t *)(obj + 0x68) + 8),
                           *(uint64_t *)(*(uint64_t *)(obj + 0x68) + 0x10));
}

/* ============================================================================
 * FUN_0005ad14 @ 0x0005ad14  (est. txm_manifest_restore_release)
 * Ghidra: void FUN_0005ad14(ulong *param_1)
 * Releases a manifest restore-info record: tears down the payload scratch
 *   (FUN_000523a0/5244c), clears the active flag, invokes the method-table
 *   destructor (+0x20+0x10) and clears the pointer. */
static void
txm_manifest_restore_release(uint64_t *rec)
{
    uint64_t l = *rec;
    if (l != 0) {
        uint64_t local = 0;
        if (*(int16_t *)(l + 0x58) != 0)
            local = l + 0x30;
        if (*(uint64_t *)(l + 0x60) != 0)
            txm_img4_teardown(*(uint64_t *)(l + 0x60), &local);   /* FUN_000523a0 */
        /* FUN_0005244c(&local) */
        *(int16_t *)(l + 0x58) = 0;
        if (l + 0x238 <= l)
            txm_panic_bounds(0x19);
        ((void (*)(uint64_t, uint64_t))(*(uint64_t *)(*(uint64_t *)(l + 0x20) + 0x10)))(l, *(uint64_t *)(l + 0x28));
        *rec = 0;
    }
}

/* ============================================================================
 * FUN_0005ada8 @ 0x0005ada8  (est. txm_payload_digest_compute)
 * Ghidra: void FUN_0005ada8(undefined8 *param_1,long param_2,undefined8 param_3)
 * Computes the payload digest: allocates the decode implementation via
 *   DAT_0000d7c8 (FUN_00057ed0/FUN_00056e00), extracts the payload digest
 *   (FUN_00061880) and writes it into param_3. Panics
 *   "Img4DecodeCopyPayloadDige" on failure. */
static void
txm_payload_digest_compute(uint64_t *rec, uint64_t impl, uint64_t out)
{
    uint64_t saved = txm_canary;
    uint64_t obj = rec[0];
    uint64_t *d = 0;
    uint64_t digest[0x20] = {0};
    uint64_t lvl = txm_env_level(0xd7c8);
    if (lvl < 2)
        lvl = 1;
    uint64_t *dec;
    if (lvl == 1) {
        dec = (uint64_t *)(0);
    } else if (lvl == 2) {
        dec = (uint64_t *)txm_impl_vtable_dispatch(obj, 0xd7c8, (uint64_t *)&dec);
        if (dec == 0)
            dec = (uint64_t *)(0);
    } else {
        txm_panic_fmt("panic: unreachable case %s 0x");
    }
    uint64_t chip = txm_decode_impl_dispatch_result(impl, obj, (uint64_t)dec);
    if (chip == 0)
        txm_panic_fmt("panic: no decode implementation a");
    uint64_t len = **(uint64_t **)(chip + 0x20);
    if (len > 0x40)
        txm_panic_bounds(0x19);
    uint64_t rc = txm_decode_copy_payload_digest(rec[0xd], digest, len);  /* FUN_00061880 */
    if ((int)rc == 0) {
        txm_digest_release(obj, 0xd7c8, (uint64_t *)&d);
        txm_digest_set_bytes(out, digest, len);
        if (txm_canary != saved)
            txm_stack_check();
        return;
    }
    txm_panic_fmt("panic: Img4DecodeCopyPayloadDige");
}

/* ============================================================================
 * FUN_0005afc0 @ 0x0005afc0  (est. txm_payload_digest_get_v)
 * Ghidra: void FUN_0005afc0(long param_1,undefined8 param_2)
 * Variant of txm_payload_digest_get (same body, different PAC site). */
static void
txm_payload_digest_get_v(uint64_t obj, uint64_t out)
{
    if (*(int16_t *)(obj + 0x58) == 0) {
        txm_optional_not_set();
        return;
    }
    uint64_t base = *(uint64_t *)(obj + 0x30);
    if (base + *(int64_t *)(obj + 0x38) < base)
        txm_panic_bounds(0x19);
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5b004);
    txm_img4_copy_manifest(out, base, *(uint64_t *)(obj + 0x38));
}

/* ============================================================================
 * FUN_0005b014 @ 0x0005b014  (est. txm_payload_get_raw)
 * Ghidra: void FUN_0005b014(long param_1,undefined8 param_2)
 * Copies the raw payload bytes into param_2 via FUN_000522d8, obtaining them
 *   through FUN_00045034; panics "Img4DecodeGetPayload %d". */
static void
txm_payload_get_raw(uint64_t obj, uint64_t out)
{
    uint64_t a = 0, b = 0;
    int r = txm_get_property_data(*(uint64_t *)(obj + 0x68), &a);   /* FUN_00045034 */
    if (r == 0) {
        txm_img4_copy_manifest(out, a, b);
        return;
    }
    txm_panic_fmt("panic: Img4DecodeGetPayload %d");
}

/* ============================================================================
 * FUN_0005b074 @ 0x0005b074  (est. txm_property_set_by_tag)
 * Ghidra: ulong FUN_0005b074(int *param_1,int param_2)
 * Finds the property set matching a tag by iterating the registry table
 *   (DAT_0000dbc8, two variants selected by param_2); returns the set whose
 *   +0x18 tag equals param_1's tag, else 0. */
static uint64_t
txm_property_set_by_tag(int *tag, int kind)
{
    uint64_t table[3] = {0xdbc8, 0xdbd0, 0xdbd8};
    uint64_t (*keep)(uint64_t) = txm_iter_not_manifest;    /* FUN_0005666c */
    if ((kind != 0) && ((keep = table[0]), kind == 1))
        keep = txm_iter_not_payload;                       /* FUN_00056680 */
    for (;;) {
        uint64_t e = txm_iterator_next(table);
        if (e == 0)
            return 0;
        if ((txm_iter_not_manifest(e) == 0) || (txm_iter_not_payload(e) == 0) || (*(int *)(e + 0x18) == *tag))
            break;
    }
    if (e < e + 0x68)
        return e;
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_0005b134 @ 0x0005b134  (est. txm_property_match)
 * Ghidra: bool FUN_0005b134(long param_1,long param_2)
 * Returns true when two property sets are the same object, linked (via +8),
 *   or share the same tag (+0x18). */
static bool
txm_property_match(uint64_t a, uint64_t b)
{
    if (b == 0)
        return false;
    if ((a != b) && (*(uint64_t *)(a + 8) != b) && (*(uint64_t *)(b + 8) != a))
        return *(int *)(b + 0x18) == *(int *)(a + 0x18);
    return true;
}

/* ============================================================================
 * FUN_0005b180 @ 0x0005b180  (est. txm_property_available)
 * Ghidra: bool FUN_0005b180(long param_1,undefined8 param_2)
 * Returns true when property param_1 is available within property set param_2:
 *   either it matches the active set, or it is an entitlement/property-set
 *   that validates against the override table (FUN_00056e10). */
static bool
txm_property_available(uint64_t prop, uint64_t set)
{
    uint64_t def = txm_property_set_default(set);
    if ((def == 0) ||
        ((((prop != def && (*(uint64_t *)(prop + 8) != def)) && (*(uint64_t *)(def + 8) != prop))
          && (*(int *)(def + 0x18) != *(int *)(prop + 0x18))))) {
        if ((*(uint64_t *)(prop + 0x10) == 0x22) || (*(uint64_t *)(prop + 0x30) == 0x1d5f8))
            return false;
        return txm_property_override_validate(set, prop) != 0;   /* FUN_00056e10 */
    }
    return true;
}

/* ============================================================================
 * FUN_0005b224 @ 0x0005b224  (est. txm_enforce_bool_constraint)
 * Ghidra: uint FUN_0005b224(long param_1,undefined8 param_2,byte *param_3,byte *param_4)
 * Enforces a boolean property constraint: compares the required value
 *   (param_3) against the object's value (param_4) per the constraint operator
 *   (param_1+0x30, one of 8 operators). Logs
 *   "enforcing %s %s %s 0x%x %s" on violation. */
static uint32_t
txm_enforce_bool_constraint(uint64_t prop, uint64_t obj, uint8_t *req, uint8_t *val)
{
    uint8_t r = *req, v = *val;
    uint64_t op = **(uint64_t **)(prop + 0x30);
    uint32_t res;
    bool violated;
    if (op < 4) {
        if (op < 2) {
            if (op == 0) {
                res = (v ^ r) & 1;
                violated = ((v ^ r) & 1) != 0;
            } else if (op == 1) {
                violated = (v & 1) <= (r & 1);
                res = (uint32_t)violated;
                if (!violated) return res;
                res = -(uint32_t)((v & 1) <= (r & 1));
                if (res == 0) return 0;
            } else {
                txm_panic_fmt("panic: unreachable case %s 0x");
            }
        } else {
            if (op == 2) {
                res = -(uint32_t)((v & 1) < (r & 1));
                if (res == 0) return 0;
            } else if (op == 3) {
                violated = (r & 1) <= (v & 1);
                res = (uint32_t)violated;
                if (!violated) return res;
            } else {
                txm_panic_fmt("panic: unreachable case %s 0x");
            }
        }
    } else {
        if (op > 5) {
            if (op == 6)
                return 0;
            if (op == 8)
                txm_panic_fmt("panic: property is not constrain");
            txm_panic_fmt("panic: unreachable case %s 0x");
        }
        if (op == 4) {
            violated = (r & 1) < (v & 1);
            res = (uint32_t)violated;
            if (!violated) return res;
        } else if (op == 5) {
            res = ((v ^ r) ^ 0xffffffff) & 1;
            if (res == 0) return 0;
        } else {
            txm_panic_fmt("panic: unreachable case %s 0x");
        }
    }
    int sc = *(int *)(prop + 0x38);
    if (sc < 2) {
        if ((sc != 0) && (sc != 1))
            txm_panic_fmt("panic: unreachable case %s 0x");
    } else if ((1 < sc - 2U) && (sc != 6))
        txm_panic_fmt("panic: unreachable case %s 0x");
    txm_panic_fmt("enforcing %s %s %s 0x%x %s");
    return res;
}

/* ============================================================================
 * FUN_0005b430 @ 0x0005b430  (est. txm_enforce_uint32_constraint)
 * Ghidra: uint FUN_0005b430(long param_1,undefined8 param_2,uint *param_3,uint *param_4)
 * Enforces a uint32 property constraint (operator at param_1+0x30). */
static uint32_t
txm_enforce_uint32_constraint(uint64_t prop, uint64_t obj, uint32_t *req, uint32_t *val)
{
    uint32_t r = *req, v = *val;
    uint64_t op = **(uint64_t **)(prop + 0x30);
    uint32_t res;
    bool violated;
    if (op < 4) {
        if (op < 2) {
            if (op == 0) {
                violated = r != v;
                goto cmp;
            }
            if (op == 1) {
                violated = v <= r;
                res = -(uint32_t)violated;
                if (res == 0) return 0;
            } else {
                txm_panic_fmt("panic: unreachable case %s 0x");
            }
        } else {
            if (op == 2) {
                violated = v < r;
                res = -(uint32_t)violated;
                if (res == 0) return 0;
            } else if (op == 3) {
                violated = r <= v;
                goto cmp;
            } else {
                txm_panic_fmt("panic: unreachable case %s 0x");
            }
        }
    } else {
        if (op > 5) {
            if (op == 6)
                return 0;
            if (op == 8)
                txm_panic_fmt("panic: property is not constrain");
            txm_panic_fmt("panic: unreachable case %s 0x");
        }
        if (op == 4) {
            violated = r < v;
            goto cmp;
        }
        if (op == 5) {
            violated = r == v;
            goto cmp;
        }
        txm_panic_fmt("panic: unreachable case %s 0x");
    }
cmp:
    res = (uint32_t)violated;
    if (!violated)
        return res;
    int sc = *(int *)(prop + 0x38);
    if (sc < 2) {
        if ((sc != 0) && (sc != 1))
            txm_panic_fmt("panic: unreachable case %s 0x");
    } else if ((1 < sc - 2U) && (sc != 6))
        txm_panic_fmt("panic: unreachable case %s 0x");
    txm_panic_fmt("enforcing %s %s %s 0x%x %s");
    return res;
}

/* ============================================================================
 * FUN_0005b610 @ 0x0005b610  (est. txm_enforce_uint64_constraint)
 * Ghidra: uint FUN_0005b610(long param_1,undefined8 param_2,ulong *param_3,ulong *param_4)
 * Enforces a uint64 property constraint. */
static uint32_t
txm_enforce_uint64_constraint(uint64_t prop, uint64_t obj, uint64_t *req, uint64_t *val)
{
    uint64_t r = *req, v = *val;
    uint64_t op = **(uint64_t **)(prop + 0x30);
    uint32_t res;
    bool violated;
    if (op < 4) {
        if (op < 2) {
            if (op == 0) {
                violated = r != v;
                goto cmp;
            }
            if (op == 1) {
                violated = v <= r;
                res = -(uint32_t)violated;
                if (res == 0) return 0;
            } else {
                txm_panic_fmt("panic: unreachable case %s 0x");
            }
        } else {
            if (op == 2) {
                violated = v < r;
                res = -(uint32_t)violated;
                if (res == 0) return 0;
            } else if (op == 3) {
                violated = r <= v;
                goto cmp;
            } else {
                txm_panic_fmt("panic: unreachable case %s 0x");
            }
        }
    } else {
        if (op > 5) {
            if (op == 6)
                return 0;
            if (op == 8)
                txm_panic_fmt("panic: property is not constrain");
            txm_panic_fmt("panic: unreachable case %s 0x");
        }
        if (op == 4) {
            violated = r < v;
            goto cmp;
        }
        if (op == 5) {
            violated = r == v;
            goto cmp;
        }
        txm_panic_fmt("panic: unreachable case %s 0x");
    }
cmp:
    res = (uint32_t)violated;
    if (!violated)
        return res;
    int sc = *(int *)(prop + 0x38);
    if (sc < 2) {
        if ((sc != 0) && (sc != 1))
            txm_panic_fmt("panic: unreachable case %s 0x");
    } else if ((1 < sc - 2U) && (sc != 6))
        txm_panic_fmt("panic: unreachable case %s 0x");
    txm_panic_fmt("enforcing %s %s %s 0x%llx %s");
    return res;
}

/* ============================================================================
 * FUN_0005b7f0 @ 0x0005b7f0  (est. txm_enforce_digest_constraint)
 * Ghidra: ulong FUN_0005b7f0(long param_1,undefined8 param_2,long param_3,long param_4)
 * Enforces a digest-length + content constraint between two digests
 *   (param_3, param_4) per the operator at param_1+0x30. Logs
 *   "enforcing length %s %s %s" / "enforcing %s %s %s %s %s". */
static uint64_t
txm_enforce_digest_constraint(uint64_t prop, uint64_t obj, uint64_t a, uint64_t b)
{
    uint64_t saved = txm_canary;
    uint64_t d1[0x20] = {0}, d2[0x20] = {0};
    txm_digest_copy_get(a, d1);
    txm_digest_copy_get(b, d2);
    uint64_t eq = txm_digest_equal(a, b);              /* FUN_00057c58 */
    uint64_t op = **(uint64_t **)(prop + 0x30);
    if (op < 5) {
        if (op != 0) {
            if (op - 1U < 4)
                txm_panic_fmt("panic: non_sensical property dig");
            goto nxt;
        }
        if (*(uint64_t *)(a + 0x48) == *(uint64_t *)(b + 0x48)) goto equal;
        /* fallthrough -> violation */
        goto viol;
    } else {
        if (op != 5) {
            if (op != 6) {
                if (op == 8)
                    txm_panic_fmt("panic: property is not constrain");
                goto nxt;
            }
            eq = 0;
            goto out;
        }
        eq = (uint64_t)((int)eq == 0);
        if (*(uint64_t *)(a + 0x48) == *(uint64_t *)(b + 0x48)) goto viol;
    }
equal:
    /* lengths match; enforce content */
    eq = (uint64_t)((int)eq == 0);
viol:
    {
        int sc = *(int *)(prop + 0x38);
        if (sc < 2) {
            if ((sc != 0) && (sc != 1))
                goto nxt;
        } else if ((1 < sc - 2U) && (sc != 6)) goto nxt;
        txm_panic_fmt("enforcing length %s %s %s %s %s");
        if (eq != 0) {
            sc = *(int *)(prop + 0x38);
            if (sc < 2) {
                if ((sc != 0) && (sc != 1)) goto nxt;
            } else if ((1 < sc - 2U) && (sc != 6)) goto nxt;
            txm_panic_fmt("enforcing %s %s %s %s %s");
        }
    }
out:
    if (txm_canary != saved)
        txm_stack_check();
    return eq;
nxt:
    txm_panic_fmt("panic: unreachable case %s 0x");
    return eq;
}

/* ============================================================================
 * FUN_0005bb1c @ 0x0005bb1c  (est. txm_enforce_digest64_constraint)
 * Ghidra: int FUN_0005bb1c(long param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Enforces an anti-replay-odometer-style 64-byte digest constraint: compares
 *   the two digest lengths (via FUN_0005d42c) per the operator and logs on
 *   violation. */
static int
txm_enforce_digest64_constraint(uint64_t prop, uint64_t obj, uint64_t a, uint64_t b)
{
    txm_strnlen(a, 0);
    txm_strnlen(b, 0);
    uint64_t op = **(uint64_t **)(prop + 0x30);
    int r;
    bool want;
    uint64_t target;
    if (op < 3) {
        if (op == 0) { want = false; r = 1; }
        else if (op == 1) { want = false; r = -1; target = 2; }
        else { want = true; r = -1; }
    } else if (op < 5) {
        if (op == 3) { want = false; target = 1; r = 1; }
        else { r = 1; want = true; target = 1; }
    } else if (op == 5) {
        want = false; r = 1; target = 3;
    } else if (op == 6) {
        r = 0; want = false; target = 0;
    } else {
        txm_panic_fmt("panic: illegal property definition");
    }
    uint64_t cmp = txm_odometer_compare(a, b);   /* FUN_0005d42c */
    bool ok = false;
    if (cmp == 0)
        ok = want;
    if (cmp == target)
        ok = true;
    int res = 0;
    if (!ok)
        res = r;
    if (res != 0) {
        int sc = *(int *)(prop + 0x38);
        if (sc < 2) {
            if ((sc != 0) && (sc != 1))
                txm_panic_fmt("panic: unreachable case %s 0x");
        } else if ((1 < sc - 2U) && (sc != 6))
            txm_panic_fmt("panic: unreachable case %s 0x");
        txm_panic_fmt("enforcing %s %s %s %s %s");
    }
    return res;
}

/* ============================================================================
 * FUN_0005bd78 @ 0x0005bd78  (est. txm_entangle_nonce)
 * Ghidra: void FUN_0005bd78(undefined8 param_1,long param_2,long param_3,undefined8 param_4)
 * Entangles a nonce with the chip entropy: resolves the entropy source
 *   (FUN_00058f24), hashes it with the manifest digest (FUN_00038288/
 *   FUN_000385b8) and stores the result into param_4. */
static void
txm_entangle_nonce(uint64_t obj, uint64_t src, uint64_t manifest, uint64_t out)
{
    uint64_t saved = txm_canary;
    uint64_t d[0x20] = {0};
    if (src == 0)
        src = txm_vtable_dispatch_80(obj, 0);
    int has = (*(uint64_t *)(src + 0xd0) == 0) ? 1 : 0;
    if (*(uint64_t *)(src + 0xb0) != 0)
        has = 0;
    if (*(uint64_t *)(src + 0xb8) != 0)
        has = 0;
    uint64_t *ent = (uint64_t *)txm_property_entropy_resolve(obj, src, has);  /* FUN_00058f24 */
    /* FUN_0002d240(local) */
    uint64_t n = ent[0];
    if (n > 0x40)
        txm_panic_fmt("panic: buffer not large enough f");
    txm_sha256(ent, d);                       /* FUN_00038288 */
    txm_sha_update_data(ent, d, *(uint64_t *)(manifest + 0x10), manifest);  /* FUN_000385b8 */
    ((void (*)(uint64_t *, uint64_t *, uint64_t *))ent[7])(ent, d, d);
    if (n > 0x40)
        txm_panic_bounds(0x19);
    txm_digest_set_bytes(out, d);             /* FUN_00057b58 */
    if (txm_canary == saved)
        return;
    txm_stack_check();
}

/* ============================================================================
 * FUN_0005bef0 @ 0x0005bef0  (est. txm_nonce_entangle)
 * Ghidra: undefined8 FUN_0005bef0(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4,undefined8 p5)
 * Entangles a nonce via FUN_0005bd78 when the +0x98 vtable hook returns 0;
 *   logs "failed to entangle nonce %d" otherwise. */
static uint64_t
txm_nonce_entangle(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t out)
{
    uint64_t saved = txm_canary;
    uint64_t nonce[0x20] = {0};
    uint64_t rc = txm_vtable_dispatch_98(a);   /* FUN_00058fa0 */
    if ((uint32_t)rc == 0) {
        txm_entangle_nonce(a, b, nonce, out);  /* FUN_0005bd78 */
    } else {
        txm_panic_fmt("failed to entangle nonce %d");
        if (rc > 0x6b)
            txm_panic_fmt("panic: error not set to valid po");
    }
    if (txm_canary == saved)
        return rc;
    txm_stack_check();
    return rc;
}

/* ============================================================================
 * FUN_0005bfb4 @ 0x0005bfb4  (est. txm_restore_info_bool)
 * Ghidra: byte FUN_0005bfb4(byte *param_1,long param_2)
 * Reads a restore-info bool at param_1 + param_2+8 (offset validated against
 *   0x3d0 bound). */
static uint8_t
txm_restore_info_bool(uint8_t *obj, uint64_t prop)
{
    if (*(int64_t *)(prop + 8) < 0)
        txm_panic_fmt("panic: invalid offset %lld");   /* FUN_00050d70 */
    uint8_t *p = obj + *(int64_t *)(prop + 8);
    if (p < obj + 0x3d0 && obj <= p)
        return *p & 1;
    txm_panic_bounds(0x19);
}

/* ============================================================================
 * FUN_0005c00c @ 0x0005c00c  (est. txm_odometer_chip_query)
 * Ghidra: ulong FUN_0005c00c(undefined8 *param_1)
 * Queries the chip entropy (via +0x88 hook); a 0x2d "not present" result is
 *   tolerated when the restore flag (+0x38) is clear, else an error. Logs
 *   "odometer %s failed to query chip". */
static uint64_t
txm_odometer_chip_query(uint64_t *obj)
{
    uint64_t prop = obj[2];
    uint64_t rc = txm_vtable_dispatch_88(obj[0], prop);   /* FUN_00058f80 */
    uint32_t e = (uint32_t)rc;
    if (e != 0) {
        if (e == 0x2d) {
            if (*(int16_t *)(obj + 7) == 0) {
                e = 0x2d;
                if (*(int16_t *)(obj + 0x1d) != 0)
                    e = 0;
                rc = (uint64_t)e;
            } else {
                rc = 0;
            }
        } else {
            uint64_t n = obj[0];
            txm_optional_not_set();
            txm_optional_not_set();
            txm_panic_fmt("odometer %s failed to query ch");
            if (e > 0x6b)
                txm_panic_fmt("panic: error not set to valid po");
        }
    }
    return rc;
}

/* ============================================================================
 * FUN_0005c0cc @ 0x0005c0cc  (est. txm_odometer_query_nonce)
 * Ghidra: undefined8 FUN_0005c0cc(undefined8 *param_1,undefined8 param_2,int param_3,undefined8 param_4)
 * Queries the odometer nonce: if the restore flag is set, copies the saved
 *   nonce (FUN_0005a73c); else queries via the +0x90 vtable hook (or with a
 *   NULL type if param_3 == -1). */
static uint64_t
txm_odometer_query_nonce(uint64_t *obj, uint64_t ctx, int type, uint64_t out)
{
    if (*(int16_t *)(obj + 7) != 0) {
        txm_nonce_copy_set(out, obj + 4);      /* FUN_0005a73c */
        return 0;
    }
    if (type != -1) {
        uint64_t lr = (uint64_t)__builtin_return_address(0);
        if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
            txm_breakpoint(0xc471, 0x5c11c);
        return txm_vtable_dispatch_90(obj[0], obj[2]);   /* FUN_00058f90 */
    }
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5c130);
    return txm_vtable_dispatch_90(obj[0], 0);
}

/* ============================================================================
 * FUN_0005c134 @ 0x0005c134  (est. txm_odometer_restore_query)
 * Ghidra: undefined8 FUN_0005c134(undefined8 *param_1,undefined8 param_2,undefined8 param_3)
 * Queries the restore-info nonce (FUN_00045208); validates length <= 0x10 and
 *   stores it into param_3. Logs "odometer %s restore_info has no" /
 *   "failed to query restore_info". */
static uint64_t
txm_odometer_restore_query(uint64_t *obj, uint64_t ctx, uint64_t out)
{
    uint64_t a = 0, b = 0;
    uint64_t rc = txm_img4_query_property(ctx, *(uint32_t *)(*(uint64_t *)(obj[2] + 0x60) + 0x18), &a, &b);  /* FUN_00045208 */
    if ((int)rc == 1) {
        txm_panic_fmt("odometer %s restore_info has no");
        return 2;
    }
    if ((int)rc == 0) {
        if (b < 0x11) {
            txm_nonce_set(out, a);       /* FUN_0005a6e4 */
            return 0;
        }
        return 0x54;
    }
    txm_panic_fmt("odometer %s failed to query re");
    rc = txm_errno_lookup(rc);
    if (rc > 0x6b)
        txm_panic_fmt("panic: error not set to valid po");
    return rc;
}

/* ============================================================================
 * FUN_0005c230 @ 0x0005c230  (est. txm_restore_constraint)
 * Ghidra: ulong FUN_0005c230(byte *param_1,long param_2,long param_3,ulong param_4)
 * Enforces a restore/odometer constraint on a property (param_3): queries the
 *   property (bool/uint32/uint64/digest/digest64) and compares against the
 *   expected value (param_4) via the constraint enforcers. Logs
 *   "odometer %s %s failed to query" / "constraint viol". */
static uint64_t
txm_restore_constraint(uint8_t *obj, uint64_t ctx, uint64_t prop, uint64_t expect)
{
    uint64_t saved = txm_canary;
    uint32_t tag = *(uint32_t *)(ctx + 0x18);
    uint64_t name = *(uint64_t *)obj;
    uint64_t key = *(uint64_t *)(obj + 0x10);
    uint64_t d[0x20] = {0};
    uint64_t vtype = **(uint64_t **)(prop + 0x28);
    uint64_t rc;
    if (vtype < 2) {
        if (vtype == 0) {
            rc = txm_property_bool_query(name, key, prop, &d);
            if ((int)rc == 0) {
                if (expect + 1 <= expect)
                    txm_panic_bounds(0x19);
                rc = txm_enforce_bool_constraint(prop, name, expect, &d);
            }
        } else if (vtype == 1) {
            rc = txm_property_uint32_query(name, key, prop, &d);
            if ((int)rc == 0) {
                if (expect + 4 <= expect)
                    txm_panic_bounds(0x19);
                rc = txm_enforce_uint32_constraint(prop, name, expect, &d);
            }
        } else {
            txm_panic_fmt("panic: unreachable case %s 0x");
        }
    } else if (vtype == 2) {
        rc = txm_property_uint64_query(name, key, prop, &d);
        if ((int)rc == 0) {
            if (expect + 8 <= expect)
                txm_panic_bounds(0x19);
            rc = txm_enforce_uint64_constraint(prop, name, expect, &d);
        }
    } else if (vtype == 3) {
        rc = txm_property_digest_query(name, key, prop, &d);
        if ((int)rc == 0) {
            if (expect + 0x50 <= expect)
                txm_panic_bounds(0x19);
            rc = txm_enforce_digest_constraint(prop, name, expect, &d);
        }
    } else if (vtype == 4) {
        uint64_t end = (uint64_t)obj + 0x3d0;
        uint8_t *p1 = (uint8_t *)obj + 0x3c8;
        uint8_t *p2 = (uint8_t *)obj + 0x3c9;
        uint8_t *p3 = (uint8_t *)obj + 0x3cc;
        if (((end <= (uint64_t)p1) || ((uint64_t)p2 < (uint64_t)obj)) ||
            ((end <= (uint64_t)p2) || ((uint64_t)p3 < (uint64_t)obj)) ||
            ((end <= (uint64_t)p3) || (key + 0x110 <= key)))
            txm_panic_bounds(0x19);
        uint8_t b1 = *p1, b2 = *p2, b3 = *p3;
        uint64_t saved2 = *(uint64_t *)(key + 0x18);
        rc = txm_property_digest64_query(name, key, prop, &d);
        if ((int)rc == 0) {
            if (expect + 0x68 <= expect)
                txm_panic_bounds(0x19);
            uint64_t (*enf)(uint64_t, uint64_t, uint64_t, uint64_t) = txm_enforce_digest64_constraint;  /* FUN_0005c5bc */
            if (((uint8_t)(((b2 ^ 0xff) & 1) + (b1 & 1)) != 0 || (b3 & 1) != 0) || saved2 == 0)
                enf = txm_enforce_digest64_constraint2;    /* FUN_0005c5d0 */
            rc = enf(prop, name, expect, &d);
        }
    } else {
        txm_panic_fmt("panic: unreachable case %s 0x");
    }
    if (rc != 0) {
        txm_panic_fmt("odometer %s %s constraint viol");
        rc = (uint64_t)tag;
    }
    if (rc > 0x6b)
        txm_panic_fmt("panic: error not set to valid po");
    if (txm_canary != saved)
        txm_stack_check();
    return rc;
}

/* ============================================================================
 * FUN_0005c5bc @ 0x0005c5bc  (est. txm_enforce_digest64_constraint2)
 * Ghidra: void FUN_0005c5bc(undefined8 *param_1,undefined8 param_2)
 * Constraint enforcer thunk for the restore path. */
static void
txm_enforce_digest64_constraint2(uint64_t *obj, uint64_t prop)
{
    txm_enforce_digest64_constraint(prop, obj[0]);
}

/* ============================================================================
 * FUN_0005c5d0 @ 0x0005c5d0  (est. txm_enforce_digest64_constraint_v)
 * Ghidra: undefined8 FUN_0005c5d0(undefined8 *param_1,undefined8 param_2,long param_3,long param_4)
 * Enforces a digest64 constraint and additionally requires equal current
 *   odometer values (param_3+100 == param_4+100). */
static uint64_t
txm_enforce_digest64_constraint_v(uint64_t *obj, uint64_t prop, uint64_t a, uint64_t b)
{
    uint64_t rc = txm_enforce_digest64_constraint(prop, obj[0]);
    if (((int)rc == 0) || (*(int *)(a + 100) != *(int *)(b + 100)))
        rc = 0;
    return rc;
}

/* ============================================================================
 * FUN_0005c61c @ 0x0005c61c  (est. txm_policy_init)
 * Ghidra: void FUN_0005c61c(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Initializes an anti-replay policy object: stores the name/impl/context,
 *   initializes error code (-1) and zeroes the odometer state (0x370 bytes). */
static uint64_t
txm_policy_init(uint64_t *policy, uint64_t name, uint64_t impl, uint64_t ctx)
{
    policy[0] = name;
    policy[1] = impl;
    policy[2] = ctx;
    *(uint32_t *)(policy + 3) = 0xffffffff;
    uint64_t *p = policy + 4;
    for (int i = 0; i < 0x6a; i++)
        p[i] = 0;
    *(uint32_t *)(policy + 0x6d) = 0xffffffff;
    *(uint32_t *)(policy + 0x79) = 0;
    *(int16_t *)((char *)policy + 0x3cc) = 0;
}

/* ============================================================================
 * FUN_0005c6d4 @ 0x0005c6d4  (est. txm_policy_prepare)
 * Ghidra: undefined8 FUN_0005c6d4(undefined8 *param_1)
 * Prepares the anti-replay policy by querying the six odometer properties
 *   (table at DAT_0001d678) into the policy object via FUN_0005861c. Logs
 *   "odometer %s failed to query od" on failure. */
static uint64_t
txm_policy_prepare(uint64_t *policy)
{
    uint64_t rc = 0;
    uint64_t i = 0;
    for (;;) {
        uint64_t *desc = *(uint64_t **)(0x1d678 + i);
        uint64_t off = desc[1];
        if ((int64_t)off < 0)
            txm_panic_fmt("panic: invalid offset %lld");
        uint64_t *dst = (uint64_t *)((char *)policy + off);
        uint64_t prop = txm_property_override_lookup(policy[2], *(uint64_t *)(0x1d678 + i), 0);  /* FUN_00056d88 */
        if ((dst != 0) && (policy + 0x7a <= dst || dst < policy))
            txm_panic_bounds(0x19);
        rc = txm_property_bool_query(policy[0], policy[2], prop, (uint8_t *)dst);  /* FUN_0005861c */
        if ((uint32_t)rc != 0) {
            txm_panic_fmt("odometer %s failed to query od");
            if ((uint32_t)rc < 0x6c)
                return rc;
            txm_panic_fmt("panic: error not set to valid po");
        }
        i += 8;
        if (i == 0x30)
            break;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005c7e0 @ 0x0005c7e0  (est. txm_identifier_import_16)
 * Ghidra: void FUN_0005c7e0(long param_1,undefined8 *param_2)
 * Copies a 16-byte identifier record (param_2, 10 words) into the object at
 *   param_1+0x98..+0xe0 and sets the present flag (+0xe8 = 1). */
static void
txm_identifier_import_16(uint64_t obj, uint64_t *src)
{
    *(uint64_t *)(obj + 0xa0) = src[1];
    *(uint64_t *)(obj + 0x98) = src[0];
    *(uint64_t *)(obj + 0xe0) = src[9];
    *(uint64_t *)(obj + 0xd8) = src[8];
    *(uint64_t *)(obj + 0xd0) = src[7];
    *(uint64_t *)(obj + 0xc8) = src[6];
    *(uint64_t *)(obj + 0xc0) = src[5];
    *(uint64_t *)(obj + 0xb8) = src[4];
    *(uint64_t *)(obj + 0xb0) = src[3];
    *(uint64_t *)(obj + 0xa8) = src[2];
    *(int16_t *)(obj + 0xe8) = 1;
}

/* ============================================================================
 * FUN_0005c810 @ 0x0005c810  (est. txm_flag_manifest_present)
 * Ghidra: void FUN_0005c810(long param_1) — sets byte +0x1b9. */
static void
txm_flag_manifest_present(uint64_t obj)
{
    *(uint8_t *)(obj + 0x1b9) = 1;
}

/* ============================================================================
 * FUN_0005c820 @ 0x0005c820  (est. txm_flag_manifest_hash_present)
 * Ghidra: void FUN_0005c820(long param_1) — sets byte +0x1ba. */
static void
txm_flag_manifest_hash_present(uint64_t obj)
{
    *(uint8_t *)(obj + 0x1ba) = 1;
}

/* ============================================================================
 * FUN_0005c830 @ 0x0005c830  (est. txm_manifest_hash_import)
 * Ghidra: void FUN_0005c830(long param_1,undefined8 *param_2)
 * Copies a manifest-hash record (param_2) into the object at
 *   param_1+0x1c0..+0x208 and sets the present flag (+0x210). */
static void
txm_manifest_hash_import(uint64_t obj, uint64_t *src)
{
    *(uint64_t *)(obj + 0x1c8) = src[1];
    *(uint64_t *)(obj + 0x1c0) = src[0];
    *(uint64_t *)(obj + 0x1f8) = src[7];
    *(uint64_t *)(obj + 0x1f0) = src[6];
    *(uint64_t *)(obj + 0x208) = src[9];
    *(uint64_t *)(obj + 0x200) = src[8];
    *(uint64_t *)(obj + 0x1d8) = src[3];
    *(uint64_t *)(obj + 0x1d0) = src[2];
    *(uint64_t *)(obj + 0x1e8) = src[5];
    *(uint64_t *)(obj + 0x1e0) = src[4];
    *(int16_t *)(obj + 0x210) = 1;
}

/* ============================================================================
 * FUN_0005c858 @ 0x0005c858  (est. txm_flag_odometer_present)
 * Ghidra: void FUN_0005c858(long param_1,undefined1 param_2) — stores byte at
 *   +0x3c8. */
static void
txm_flag_odometer_present(uint64_t obj, uint8_t v)
{
    *(uint8_t *)(obj + 0x3c8) = v;
}

/* ============================================================================
 * FUN_0005c864 @ 0x0005c864  (est. txm_property_impose_env)
 * Ghidra: undefined8 FUN_0005c864(long param_1,undefined8 param_2,undefined8 param_3)
 * Imposes the environment properties (table at DAT_0001d6a8, 0x50 bytes) on
 *   an object, dispatching each through its method (+2). */
static uint64_t
txm_property_impose_env(uint64_t obj, uint64_t set, uint64_t key)
{
    uint64_t i = 0;
    for (;;) {
        uint64_t *ent = *(uint64_t **)(0x1d6a8 + i);
        uint64_t a = ent[0], b = ent[1];
        uint64_t prop;
        if (a == 0) {
            if ((int64_t)b < 0) {
                prop = 0;
            } else {
                uint64_t *base = *(uint64_t **)(obj + 0x10);
                uint64_t *p = (uint64_t *)((char *)base + b);
                if (base + 0x22 <= p || p < base)
                    txm_panic_bounds(0x19);
                prop = *p;
            }
        } else if ((int64_t)b >= 0) {
            txm_panic_illegal_odometer_consumption();    /* FUN_0005d228 */
        } else {
            prop = a;
        }
        uint64_t m = txm_property_match(set, prop);      /* FUN_0005b134 */
        if (((m & 1) != 0) || (a == 0 && ((int64_t)b < 0))) {
            if (((uint64_t (*)(uint64_t *, uint64_t, uint64_t, uint64_t))ent[2])(ent, obj, set, key) == 0)
                return 0;
        }
        i += 8;
        if (i == 0x50)
            return 1;
    }
}

/* ============================================================================
 * FUN_0005c944 @ 0x0005c944  (est. txm_policy_replay_check)
 * Ghidra: undefined8 FUN_0005c944(undefined8 *param_1)
 * Anti-replay replay check: when chip entropy is present (FUN_0005c00c == 0),
 *   validates the nonce policy against the boot-manifest policy table
 *   (DAT_000704e0, 8 entries), then against the boot-chain table
 *   (DAT_00070520, 5 entries). Returns 0 on pass, mapped error codes; maps a
 *   0x1f (missing) result to 0x46 when the manifest flag is set. */
static uint64_t
txm_policy_replay_check(uint64_t *policy)
{
    int chip = (int)txm_odometer_chip_query(policy);      /* FUN_0005c00c */
    uint64_t rc;
    if (chip == 0) {
        uint64_t p1 = txm_policy_table_find(policy, 0x704e0, 8);   /* FUN_0005cab8 */
        rc = txm_policy_table_validate(p1, policy);               /* FUN_00052a88 */
        if ((int)rc != 0)
            goto fail;
    }
    {
        uint64_t p2 = txm_policy_table_find(policy, 0x70520, 5);
        rc = txm_policy_table_validate(p2, policy);
        if ((int)rc != 0) goto fail;
    }
    if (txm_policy_table_present(0x1af08, policy) != 0) {   /* FUN_00052a78 */
        return 0;
    }
    rc = txm_policy_table_validate(0x1af08, policy);
    if ((int)rc == 0)
        return rc;
    txm_optional_not_set();
fail:
    txm_optional_not_set();
    txm_panic_fmt("odometer %s %s boot_chain_inte");
    if ((rc == 0x1f) && ((*(uint8_t *)((char *)policy + 0x1b9) & 1) != 0)) {
        rc = 0x46;
    } else if (rc > 0x6b) {
        txm_panic_fmt("panic: error not set to valid po");
    }
    return rc;
}

/* ============================================================================
 * FUN_0005cab8 @ 0x0005cab8  (est. txm_policy_table_find)
 * Ghidra: long FUN_0005cab8(undefined8 param_1,long *param_2,long param_3)
 * Finds the first policy-table entry (param_2, param_3 entries) that is
 *   present in the policy object (FUN_00052a78); panics via FUN_0005d240
 *   if none match. */
static uint64_t
txm_policy_table_find(uint64_t policy, uint64_t *table, uint64_t n)
{
    uint64_t ent;
    for (;;) {
        ent = *table;
        if (txm_policy_table_present(ent, policy) == 0)   /* FUN_00052a78 */
            return ent;
        n--;
        table++;
        if (n == 0)
            break;
    }
    txm_panic_no_anti_replay_policy();                    /* FUN_0005d240 */
    for (;;) { ; }
}

/* ============================================================================
 * FUN_0005cb10 @ 0x0005cb10  (est. txm_odometer_restore_digest)
 * Ghidra: void FUN_0005cb10(undefined8 param_1,undefined8 *param_2,long param_3,undefined8 param_4)
 * Restores the odometer digest property into the object (param_2+0x8..+0x12)
 *   via FUN_00045364. */
static void
txm_odometer_restore_digest(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src)
{
    uint64_t saved = txm_canary;
    uint64_t a = 0;
    uint32_t n = 0;
    uint64_t d[0x20] = {0};
    if (txm_img4_get_data(src, *(uint32_t *)(prop + 0x18), &a, &n) == 0) {   /* FUN_00045364 */
        txm_digest_set_bytes(d, a, n);
        rec[0xd] = d[6];
        rec[0xc] = d[5];
        rec[0xf] = d[7];
        rec[0xe] = d[4];
        rec[0x11] = d[3];
        rec[0x10] = d[2];
        rec[9] = d[1];
        rec[8] = d[0];
        rec[0xb] = d[0];
        rec[10] = d[0];
        *(int16_t *)(rec + 0x12) = 1;
    } else {
        txm_panic_fmt("odometer %s Img4DecodeGetPrope");
    }
    if (txm_canary != saved)
        txm_stack_check();
}

/* ============================================================================
 * FUN_0005cc00 @ 0x0005cc00  (est. txm_odometer_restore_uint32)
 * Ghidra: undefined8 FUN_0005cc00(undefined8 param_1,undefined8 *param_2,long param_3,undefined8 param_4)
 * Restores the odometer uint32 property into the object (param_2+3). */
static uint64_t
txm_odometer_restore_uint32(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src)
{
    uint32_t v = 0;
    uint64_t rc = txm_decode_get_int(src, *(uint32_t *)(prop + 0x18), &v);   /* FUN_00061a80 */
    if ((int)rc == 0) {
        *(uint32_t *)(rec + 3) = v;
    } else {
        txm_panic_fmt("odometer %s Img4DecodeGetPrope");
        rc = 0xffffffff;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005cc80 @ 0x0005cc80  (est. txm_restore_info_impose)
 * Ghidra: undefined8 FUN_0005cc80(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4)
 * Imposes a restore-info constraint (FUN_0005cccc) into rec+0x2f8, setting
 *   the restore flag (+0x360). */
static uint64_t
txm_restore_info_impose(uint64_t obj, uint64_t rec, uint64_t prop, uint64_t src)
{
    uint64_t rc = txm_restore_info_query(rec, prop, src, rec + 0x2f8);   /* FUN_0005cccc */
    if ((int)rc == 0) {
        *(int16_t *)(rec + 0x360) = 1;
    } else {
        rc = 0xffffffff;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005cccc @ 0x0005cccc  (est. txm_restore_info_query)
 * Ghidra: undefined8 FUN_0005cccc(undefined8 *param_1,long param_2,undefined8 param_3,ulong param_4)
 * Queries a restore-info property (param_2) from src (param_3) and writes the
 *   value into param_4, dispatching by property type. Logs
 *   "odometer %s Img4DecodeGetPrope" on failure. */
static uint64_t
txm_restore_info_query(uint64_t *obj, uint64_t prop, uint64_t src, uint64_t out)
{
    uint32_t tag = *(uint32_t *)(prop + 0x18);
    uint64_t a = 0;
    uint32_t n = 0;
    uint64_t vtype = **(uint64_t **)(prop + 0x28);
    uint64_t rc;
    if (vtype < 2) {
        if (vtype == 0) {
            rc = txm_decode_get_bool(src, tag, out);
            if ((int)rc == 0)
                return rc;
            txm_optional_not_set();
            txm_panic_fmt("odometer %s Img4DecodeGetPrope");
            return rc;
        }
        if (vtype != 1) {
            txm_panic_fmt("panic: unreachable case %s 0x");
        }
        rc = txm_decode_get_int(src, tag, out);
        if ((int)rc == 0)
            return rc;
        txm_optional_not_set();
        txm_panic_fmt("odometer %s Img4DecodeGetPrope");
    } else {
        if (vtype != 2) {
            if (vtype == 3) {
                rc = txm_img4_get_data(src, tag, &a, &n);
                if ((int)rc != 0) {
                    txm_optional_not_set();
                    txm_panic_fmt("odometer %s Img4DecodeGetPrope");
                    return rc;
                }
                if (out + 0x50 <= out)
                    txm_panic_bounds(0x19);
                txm_digest_set_bytes(out, a, n);
            } else {
                if (vtype != 4)
                    txm_panic_fmt("panic: unreachable case %s 0x");
                rc = txm_img4_get_data(src, tag, &a, &n);
                if ((int)rc != 0) {
                    txm_optional_not_set();
                    txm_panic_fmt("odometer %s Img4DecodeGetPrope");
                    return rc;
                }
                if (out + 0x68 <= out)
                    txm_panic_bounds(0x19);
                txm_digest64_import(out, a, n);    /* FUN_0005d258 */
            }
            return 0;
        }
        rc = txm_decode_get_uint64(src, tag, out);
        if ((int)rc == 0)
            return rc;
        txm_optional_not_set();
        txm_panic_fmt("odometer %s Img4DecodeGetPrope");
    }
    return rc;
}

/* ============================================================================
 * FUN_0005ceac @ 0x0005ceac  (est. txm_odometer_restore_type)
 * Ghidra: undefined8 FUN_0005ceac(undefined8 param_1,undefined8 *param_2,long param_3,undefined8 param_4)
 * Restores the odometer type property into the object (param_2+0x6d). */
static uint64_t
txm_odometer_restore_type(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src)
{
    uint32_t v = 0;
    uint64_t rc = txm_decode_get_int(src, *(uint32_t *)(prop + 0x18), &v);
    if ((int)rc == 0) {
        *(uint32_t *)(rec + 0x6d) = v;
    } else {
        txm_panic_fmt("odometer %s Img4DecodeGetPrope");
        rc = 0xffffffff;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005cf2c @ 0x0005cf2c  (est. txm_odometer_restore_digest2)
 * Ghidra: void FUN_0005cf2c(undefined8 param_1,undefined8 *param_2,long param_3,undefined8 param_4)
 * Restores the second odometer digest into the object (param_2+0x6e..+0x78). */
static void
txm_odometer_restore_digest2(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src)
{
    uint64_t saved = txm_canary;
    uint64_t a = 0;
    uint32_t n = 0;
    uint64_t d[0x20] = {0};
    if (txm_img4_get_data(src, *(uint32_t *)(prop + 0x18), &a, &n) == 0) {
        txm_digest_set_bytes(d, a, n);
        rec[0x73] = d[6];
        rec[0x72] = d[5];
        rec[0x75] = d[7];
        rec[0x74] = d[4];
        rec[0x77] = d[3];
        rec[0x76] = d[2];
        rec[0x6f] = d[1];
        rec[0x6e] = d[0];
        rec[0x71] = d[0];
        rec[0x70] = d[0];
        *(int16_t *)(rec + 0x78) = 1;
    } else {
        txm_panic_fmt("odometer %s Img4DecodeGetPrope");
    }
    if (txm_canary != saved)
        txm_stack_check();
}

/* ============================================================================
 * FUN_0005d01c @ 0x0005d01c  (est. txm_odometer_restore_digest3)
 * Ghidra: undefined8 FUN_0005d01c(undefined8 param_1,undefined8 *param_2,long param_3,undefined8 param_4)
 * Restores a third odometer digest into the object (param_2+0x1e). */
static uint64_t
txm_odometer_restore_digest3(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src)
{
    uint64_t a = 0;
    uint32_t n = 0;
    uint64_t rc = txm_img4_get_data(src, *(uint32_t *)(prop + 0x18), &a, &n);
    if ((int)rc == 0) {
        txm_digest_set_bytes(rec + 0x1e, a, n);
        *(int16_t *)(rec + 0x28) = 1;
        rc = 0;
    } else {
        txm_panic_fmt("odometer %s Img4DecodeGetPrope");
        rc = 0xffffffff;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005d0b8 @ 0x0005d0b8  (est. txm_odometer_restore_bool)
 * Ghidra: undefined8 FUN_0005d0b8(undefined8 param_1,undefined8 *param_2,long param_3,undefined8 param_4)
 * Restores the odometer bool property into the object (param_2+0x37). */
static uint64_t
txm_odometer_restore_bool(uint64_t obj, uint64_t *rec, uint64_t prop, uint64_t src)
{
    uint8_t v = 0;
    uint64_t rc = txm_decode_get_bool(src, *(uint32_t *)(prop + 0x18), &v);
    if ((int)rc == 0) {
        *(uint8_t *)(rec + 0x37) = v & 1;
    } else {
        txm_panic_fmt("odometer %s Img4DecodeGetPrope");
        rc = 0xffffffff;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005d13c @ 0x0005d13c  (est. txm_restore_info_impose2)
 * Ghidra: undefined8 FUN_0005d13c(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4)
 * Imposes a restore-info constraint into rec+0x148, setting +0x1b0. */
static uint64_t
txm_restore_info_impose2(uint64_t obj, uint64_t rec, uint64_t prop, uint64_t src)
{
    uint64_t rc = txm_restore_info_query(rec, prop, src, rec + 0x148);
    if ((int)rc == 0) {
        *(int16_t *)(rec + 0x1b0) = 1;
    } else {
        rc = 0xffffffff;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005d188 @ 0x0005d188  (est. txm_restore_info_batch)
 * Ghidra: undefined8 FUN_0005d188(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4)
 * Restores the batch of restore-info properties: finds the first property set
 *   that matches param_3 (FUN_0005b134) among the object's +0x10 table
 *   (+0xf0 entries), then imposes it into rec+0x218. */
static uint64_t
txm_restore_info_batch(uint64_t obj, uint64_t rec, uint64_t prop, uint64_t src)
{
    uint64_t i = 0;
    uint64_t base = *(uint64_t *)(rec + 0x10);
    for (;;) {
        if (txm_property_match(prop, *(uint64_t *)(base + 0xf0 + i * 8)) != 0) {
            uint64_t d = rec + i * 0x70;
            uint64_t rc = txm_restore_info_query(rec, prop, src, d + 0x218);
            if ((int)rc != 0)
                return 0xffffffff;
            *(int16_t *)(d + 0x280) = 1;
            return rc;
        }
        i = 1;
        if (i == 0)
            break;
    }
    return 0xffffffff;
}

/* ============================================================================
 * FUN_0005d228 @ 0x0005d228  (est. txm_panic_illegal_odometer_consumption)
 * Ghidra: void FUN_0005d228(void) — noreturn panic. */
static void
txm_panic_illegal_odometer_consumption(void)
{
    txm_panic_fmt("panic: illegal odometer consumpt");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_0005d240 @ 0x0005d240  (est. txm_panic_no_anti_replay_policy)
 * Ghidra: void FUN_0005d240(void) — noreturn panic. */
static void
txm_panic_no_anti_replay_policy(void)
{
    txm_panic_fmt("panic: no anti_replay policy sel");   /* FUN_00050d70 */
}

/* ============================================================================
 * FUN_0005d258 @ 0x0005d258  (est. txm_digest64_import)
 * Ghidra: long FUN_0005d258(long param_1)
 * Builds the anti-replay nonce/odometer structure: initializes the byte
 *   string (FUN_0005789c), writes the "fade2ded" magic, copies the default
 *   min-max table (DAT_0000dbe0), parses the boot-manifest nonce values
 *   (FUN_00053070 + FUN_0005d3b8) and finalizes with FUN_0002d990. */
static uint64_t
txm_digest64_import(uint64_t obj, uint64_t a, uint32_t n)
{
    uint64_t saved = txm_canary;
    uint64_t d[0x20] = {0};
    /* FUN_0005789c(obj, ...) */
    *(uint32_t *)(obj + 100) = 0xfade2ded;
    uint64_t i = 0x14;
    uint32_t *src = (uint32_t *)0xdbe0;
    do {
        *(uint32_t *)(obj + i * 4) = *src;
        i++;
        src++;
    } while (i != 0x19);
    uint64_t h = txm_hash_bytes(obj);
    txm_format_ident(d, h, 0x40, 0x40);
    uint64_t *it = &d;
    uint64_t *e = txm_digest_oid(it, 0x61f6);   /* FUN_00053070 */
    if (it != 0) {
        *(uint32_t *)(obj + 100) = txm_odometer_minmax(e, 0, 0);   /* FUN_0005d3b8 */
    }
    i = 0;
    for (;;) {
        uint64_t l = txm_digest_oid(e, 0x61f8);
        if (l == 0)
            break;
        *(uint32_t *)(obj + i + 0x50) = txm_odometer_minmax(l, *(uint32_t *)(0xdbe0 + i), *(uint32_t *)(0xdbf4 + i));
        i += 4;
        if (i == 0x14)
            break;
    }
    if (txm_strtoul(obj, "0_0_0_0_0_0") == 0)   /* FUN_0002d990 */
        *(uint32_t *)(obj + 0x50) = 0;
    if (txm_canary == saved)
        return obj;
    txm_stack_check();
    return obj;
}

/* ============================================================================
 * FUN_0005d3b8 @ 0x0005d3b8  (est. txm_odometer_minmax)
 * Ghidra: uint FUN_0005d3b8(undefined8 param_1,uint param_2,uint param_3)
 * Clamps an odometer value between min (param_2) and max (param_3): when
 *   min <= max, applies the parsed value (FUN_00052fe4) within the bounds;
 *   otherwise compares against the current odometer (FUN_0005d524),
 *   returning 0 equal / 1 less / 2 greater / 3 type mismatch. */
static uint32_t
txm_odometer_minmax(uint64_t src, uint32_t min, uint32_t max)
{
    if (min <= max) {
        uint32_t v = txm_parse_uint(src, 0, 10);   /* FUN_00052fe4 */
        if ((char *)0 != 0) { }
        if (v <= min)
            v = min;
        if (v <= max || max == 0)
            min = v;
        return min;
    }
    /* compare against current odometer (FUN_0005d524 panics if invalid) */
    uint64_t *cur = txm_odometer_current();   /* FUN_0005d524 */
    if (*(int *)(cur + 0x50) != 0) {
        if (*(int *)(cur + 100) != *(int *)(cur + 100))
            return 3;
        uint64_t i = 0;
        do {
            uint32_t a = *(uint32_t *)(cur + 0x50 + i);
            uint32_t b = *(uint32_t *)(cur + 0x50 + i);
            if (b < a)
                return 1;
            if (a < b)
                return 2;
            i += 4;
        } while (i != 0x14);
    }
    return 0;
}

/* ============================================================================
 * FUN_0005d42c @ 0x0005d42c  (est. txm_odometer_compare)
 * Ghidra: undefined8 FUN_0005d42c(long param_1,long param_2)
 * Compares two anti-replay odometer records word by word: returns 0 equal,
 *   1 (param_1 newer), 2 (param_2 newer), 3 (type mismatch). */
static uint64_t
txm_odometer_compare(uint64_t a, uint64_t b)
{
    if (*(int *)(a + 0x50) != 0) {
        if (*(int *)(a + 100) != *(int *)(b + 100))
            return 3;
        uint64_t i = 0;
        do {
            uint32_t va = *(uint32_t *)(a + 0x50 + i);
            uint32_t vb = *(uint32_t *)(b + 0x50 + i);
            if (vb < va)
                return 1;
            if (va < vb)
                return 2;
            i += 4;
        } while (i != 0x14);
    }
    return 0;
}

/* ============================================================================
 * FUN_0005d498 @ 0x0005d498  (est. txm_digest64_copy_set)
 * Ghidra: void FUN_0005d498(undefined8 *param_1,undefined8 *param_2)
 * Copies a 13-word (0x68-byte) digest record from param_2 into param_1. */
static void
txm_digest64_copy_set(uint64_t *dst, uint64_t *src)
{
    dst[3] = src[3];
    dst[2] = src[2];
    dst[5] = src[5];
    dst[4] = src[4];
    dst[1] = src[1];
    dst[0] = src[0];
    dst[0xc] = src[0xc];
    dst[9] = src[9];
    dst[8] = src[8];
    dst[0xb] = src[0xb];
    dst[10] = src[10];
    dst[7] = src[7];
    dst[6] = src[6];
}

/* ============================================================================
 * FUN_0005d4c8 @ 0x0005d4c8  (est. txm_hex_cstr_length)
 * Ghidra: long FUN_0005d4c8(undefined8 param_1,long param_2)
 * Formats param_1 as a 0x40-char hex string into param_2 and returns its
 *   length (up to 0x40). */
static uint64_t
txm_hex_cstr_length(uint64_t src, uint64_t out)
{
    txm_format_ident(out, src, 0x40, 0xffffffffffffffff);
    uint64_t n = 0;
    for (;;) {
        if (n == 0x40)
            txm_panic_bounds(0x19);
        if (*(char *)(out + n) == '\0')
            break;
        n++;
    }
    return out;
}

/* ============================================================================
 * FUN_0005d524 @ 0x0005d524  (est. txm_odometer_current)
 * Ghidra: void FUN_0005d524(void) — panics "invalid min_max min %u" (dead-end
 *   helper for the min-max comparison path). */
static uint64_t *
txm_odometer_current(void)
{
    txm_panic_call("panic: invalid min_max min %u");   /* FUN_00029784 */
    return 0;
}

/* ============================================================================
 * FUN_0005d550 @ 0x0005d550  (est. txm_dict_next_value)
 * Ghidra: undefined8 FUN_0005d550(long param_1,undefined8 *param_2,long *param_3,...)
 * Advances a DER plist dictionary iterator (param_5) to the next key/value
 *   pair: parses the key (FUN_00037584/FUN_000374a0) and returns the value
 *   span in param_3/param_4. Logs "%s %s" on parse failure. */
static uint64_t
txm_dict_next_value(uint64_t obj, uint64_t *key, uint64_t *span, uint64_t *span2, uint64_t *it)
{
    uint64_t start = it[0], end = it[1];
    uint64_t k = 0, len = 0;
    uint64_t ok = txm_dict_has_more(it, &k);   /* FUN_00037584 */
    if ((ok & 1) == 0) {
        /* FUN_000374a0(it,&len) */
        if ((txm_dict_len(it, &len) & 1) != 0) {
            uint64_t v = *it;
            if (len <= (uint64_t)(it[1] - v)) {
                if (key != 0)
                    *key = k;
                uint64_t v2 = v + len;
                if (span != 0) {
                    span[0] = start;
                    span[1] = v2;
                }
                if (span2 != 0) {
                    span2[0] = v;
                    span2[1] = v2;
                }
                it[0] = v2;
                it[1] = end;
                return 1;
            }
        }
    }
    if (*(uint64_t *)(obj + 0x18) != 0)
        ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    return 0;
}

/* ============================================================================
 * FUN_0005d664 @ 0x0005d664  (est. txm_parse_decimal)
 * Ghidra: undefined8 FUN_0005d664(long param_1,ulong *param_2,undefined8 param_3)
 * Parses a decimal integer (FUN_00037304, tag 2) into *param_2. */
static uint64_t
txm_parse_decimal(uint64_t obj, uint64_t *out, uint64_t span)
{
    char *p = 0, *e = 0;
    if ((txm_dict_find_key(span, 2, &p) & 1) == 0) {
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
        return 0;
    }
    if ((uint64_t)(e - p) < 9) {
        uint64_t v = 0;
        char *q = p;
        for (; q < e; q++) {
            if ((q == p) && (0x7fffffff < (uint32_t)(uint8_t)*q))
                v = 0xffffffffffffffff;
            if (q < p)
                txm_breakpoint(0x5519, 0x5d76c);
            v = (uint64_t)(uint8_t)*q | v << 8;
        }
        if (out != 0)
            *out = v;
        return 1;
    }
    if (*(uint64_t *)(obj + 0x18) != 0)
        ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    return 0;
}

/* ============================================================================
 * FUN_0005d76c @ 0x0005d76c  (est. txm_parse_bool)
 * Ghidra: undefined8 FUN_0005d76c(long param_1,undefined8 param_2)
 * Parses a single-byte bool value (FUN_00037304, tag 1); returns 1 if the
 *   span length is exactly 1. */
static uint64_t
txm_parse_bool(uint64_t obj, uint64_t span)
{
    char *p = 0, *e = 0;
    uint64_t ok = txm_dict_find_key(span, 1, &p);   /* FUN_00037304 */
    if ((ok & 1) == 0) {
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
        return 0;
    }
    if (e - p == 1)
        return 1;
    if (*(uint64_t *)(obj + 0x18) != 0)
        ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    return 0;
}

/* ============================================================================
 * FUN_0005d80c @ 0x0005d80c  (est. txm_parse_12byte)
 * Ghidra: ulong FUN_0005d80c(long param_1,long *param_2,undefined8 param_3)
 * Parses a 0xc-byte (12-byte) value span (FUN_00037304) into param_2. */
static uint64_t
txm_parse_12byte(uint64_t obj, uint64_t *out, uint64_t span)
{
    char *p = 0, *e = 0;
    uint64_t ok = txm_dict_find_key(span, 0xc, &p);
    if ((ok & 1) == 0) {
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    } else {
        out[0] = (uint64_t)p;
        out[1] = e - p;
    }
    return ok;
}

/* ============================================================================
 * FUN_0005d8a4 @ 0x0005d8a4  (est. txm_parse_4byte)
 * Ghidra: ulong FUN_0005d8a4(long param_1,long *param_2,undefined8 param_3)
 * Parses a 4-byte value span (FUN_00037304) into param_2. */
static uint64_t
txm_parse_4byte(uint64_t obj, uint64_t *out, uint64_t span)
{
    char *p = 0, *e = 0;
    uint64_t ok = txm_dict_find_key(span, 4, &p);
    if ((ok & 1) == 0) {
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    } else {
        out[0] = (uint64_t)p;
        out[1] = e - p;
    }
    return ok;
}

/* ============================================================================
 * FUN_0005d93c @ 0x0005d93c  (est. txm_parse_18byte)
 * Ghidra: ulong FUN_0005d93c(long param_1,long *param_2,undefined8 param_3)
 * Parses an 0x12-byte value span. */
static uint64_t
txm_parse_18byte(uint64_t obj, uint64_t *out, uint64_t span)
{
    char *p = 0, *e = 0;
    uint64_t ok = txm_dict_find_key(span, 0x12, &p);
    if ((ok & 1) == 0) {
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    } else {
        out[0] = (uint64_t)p;
        out[1] = e - p;
    }
    return ok;
}

/* ============================================================================
 * FUN_0005d9d4 @ 0x0005d9d4  (est. txm_parse_23byte)
 * Ghidra: ulong FUN_0005d9d4(long param_1,long *param_2,undefined8 param_3)
 * Parses an 0x17-byte value span. */
static uint64_t
txm_parse_23byte(uint64_t obj, uint64_t *out, uint64_t span)
{
    char *p = 0, *e = 0;
    uint64_t ok = txm_dict_find_key(span, 0x17, &p);
    if ((ok & 1) == 0) {
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    } else {
        out[0] = (uint64_t)p;
        out[1] = e - p;
    }
    return ok;
}

/* ============================================================================
 * FUN_0005da6c @ 0x0005da6c  (est. txm_parse_entitlement)
 * Ghidra: undefined8 FUN_0005da6c(long param_1,long *param_2,undefined8 param_3)
 * Parses an entitlements blob value (FUN_00037304, tags 0x10/0x11). */
static uint64_t
txm_parse_entitlement(uint64_t obj, uint64_t *out, uint64_t span)
{
    char *p = 0, *e = 0;
    uint64_t ok = txm_dict_find_key(span, 0x6000000000000010, &p);
    if (((ok & 1) == 0) &&
        (ok = txm_dict_find_key(span, 0x2000000000000011, &p), (ok & 1) == 0)) {
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
        return 0;
    }
    out[0] = (uint64_t)p;
    out[1] = e - p;
    return 1;
}

/* ============================================================================
 * FUN_0005db20 @ 0x0005db20  (est. txm_dict_parse)
 * Ghidra: undefined8 FUN_0005db20(ulong *param_1,undefined8 param_2)
 * Recursive DER plist dictionary parser (depth-limited by the counter at
 *   param_1+0x14): iterates key/value pairs, dispatching by key length
 *   (1/2/4/0xc/0x12/0x17/0x10/0x11) to the appropriate value parser, and
 *   recursively parses nested dictionaries. Returns 1 on success; logs
 *   "%s %s" through the object's +0x18 error hook on any parse failure.
 * Confidence: medium. */
static uint64_t
txm_dict_parse(uint64_t *iter, uint64_t span)
{
    uint64_t obj = *iter;
    if (0xc < *(int *)((char *)iter + 0x14)) {
        if (*(uint64_t *)(obj + 0x18) == 0)
            return 0;
        if (obj + 0x40 <= obj)
            txm_breakpoint(0x5519, 0x5e080);
        ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
        return 0;
    }
    /* local_d0/0xc8/0xd8: dictionary iterator state */
    uint64_t key = 0, keylen = 0, itstart = 0;
    if (obj + 0x40 <= obj)
        txm_breakpoint(0x5519, 0x5e080);
    uint64_t ok = txm_dict_next_value(obj, &key, &itstart, 0, span);
    if ((ok & 1) == 0) {
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
        return 0;
    }
    if (key == iter[1]) {
        /* key matches the expected key (param_1[1]); parse its value */
        uint64_t val = 0, vlen = 0;
        uint64_t p = 0, e = 0;
        uint64_t got = txm_dict_find_key(&itstart, key, &p);   /* FUN_00037304 */
        if (got == 0) {
            if (*(uint64_t *)(obj + 0x18) != 0)
                ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
            return 0;
        }
        uint64_t prev = 0, prevlen = 0;
        while (p < e) {
            uint64_t ks = 0, vs = 0;
            uint64_t ok2 = txm_dict_next(&p, &ks);     /* FUN_00037570 */
            if ((ok2 & 1) == 0) {
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            uint64_t ksp = 0, kslen = 0;
            uint64_t rc = txm_parse_12byte(obj, &ksp, &vs);    /* FUN_0005d80c */
            if ((rc == 0) || (kslen == 0)) {
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            uint64_t keydesc = vs, valdesc = vs;
            uint64_t m = txm_dict_has_more(&keydesc, &valdesc);   /* FUN_00037584 */
            if ((m & 1) == 0) {
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            m = txm_dict_len(&keydesc, &valdesc);      /* FUN_000374a0 */
            if ((m & 1) == 0) {
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            if (keydesc + valdesc != p) {
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            uint64_t c = txm_strncmp(ks, 0, kslen);
            if (c != 0) {
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            if (((prev != 0) && ((iter[2] & 1) != 0)) && (prevlen != 0)) {
                /* duplicate-key check */
                uint64_t a = prevlen <= kslen ? prevlen : kslen;
                if (txm_strncmp(prev, ks, a) == 0) {
                    if (*(uint64_t *)(obj + 0x18) != 0)
                        ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                    return 0;
                }
            }
            /* depth-guarded recursion for the value span */
            *(int *)((char *)iter + 0x14) = *(int *)((char *)iter + 0x14) + 1;
            uint64_t sub = txm_dict_parse(iter, vs);
            *(int *)((char *)iter + 0x14) = *(int *)((char *)iter + 0x14) - 1;
            if ((sub & 1) == 0) {
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            prev = ks;
            prevlen = kslen;
        }
        if (itstart == itstart) { /* consumed all entries */
            return 1;
        }
        if (*(uint64_t *)(obj + 0x18) != 0)
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
        return 0;
    }
    /* key length dispatch: parse the value by its key length */
    uint64_t klen = keylen;
    uint64_t rc2;
    if ((int64_t)klen < 0x12) {
        if (3 < (int64_t)klen) {
            if (klen == 4) {
                if ((iter[3] & 1) != 0) {
                    uint64_t v = 0;
                    rc2 = txm_parse_4byte(obj, &v, &itstart);   /* FUN_0005d8a4 */
                    goto merged;
                }
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            if (klen == 0xc) {
                uint64_t v = 0;
                rc2 = txm_parse_12byte(obj, &v, &itstart);
                if ((int)rc2 == 0)
                    return rc2;
                if (txm_strncmp(v, 0, 0) == 0)
                    return 1;
                if (*(uint64_t *)(obj + 0x18) != 0)
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                return 0;
            }
            goto err;
        }
        if (klen == 1) {
            rc2 = txm_parse_bool(obj, &itstart);   /* FUN_0005d76c */
            goto merged;
        }
        if (klen != 2)
            goto err;
        uint64_t v = 0;
        rc2 = txm_parse_decimal(obj, &v, &itstart);   /* FUN_0005d664 */
        goto merged;
    } else if ((int64_t)klen < 0x2000000000000010) {
        if (klen == 0x12) {
            if ((*(uint8_t *)((char *)iter + 0x19) & 1) != 0) {
                uint64_t v = 0;
                rc2 = txm_parse_18byte(obj, &v, &itstart);   /* FUN_0005d93c */
                goto merged;
            }
            if (*(uint64_t *)(obj + 0x18) != 0)
                ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
            return 0;
        }
        if (klen == 0x17) {
            if ((*(uint8_t *)((char *)iter + 0x1a) & 1) != 0) {
                uint64_t v = 0;
                rc2 = txm_parse_23byte(obj, &v, &itstart);   /* FUN_0005d9d4 */
                goto merged;
            }
            if (*(uint64_t *)(obj + 0x18) != 0)
                ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
            return 0;
        }
        goto err;
    } else {
        if (klen == 0x2000000000000010) {
            rc2 = txm_dict_parse_collection(iter, &itstart);   /* FUN_0005e080 */
            goto merged;
        }
        if ((klen != 0x2000000000000011) && (klen != 0x6000000000000010)) {
            goto err;
        }
        if ((*(uint8_t *)((char *)iter + 0x1b) & 1) == 0) {
            if (*(uint64_t *)(obj + 0x18) != 0)
                ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
            return 0;
        }
        uint64_t v = 0;
        rc2 = txm_parse_entitlement(obj, &v, &itstart);   /* FUN_0005da6c */
    }
merged:
    if ((rc2 & 1) == 0)
        return 0;
    return 1;
err:
    if (*(uint64_t *)(obj + 0x18) != 0)
        ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    return 0;
}

/* ============================================================================
 * FUN_0005e080 @ 0x0005e080  (est. txm_dict_parse_collection)
 * Ghidra: undefined8 FUN_0005e080(ulong *param_1,undefined8 param_2)
 * Parses a nested collection: recursively parses each element span
 *   (FUN_0005db20) until the collection is exhausted (FUN_00037570). */
static uint64_t
txm_dict_parse_collection(uint64_t *iter, uint64_t span)
{
    uint64_t obj = *iter;
    uint64_t p = 0, e = 0;
    uint64_t ok = txm_dict_next(span, &p);     /* FUN_00037570 */
    if (ok == 0) {
        if (*(uint64_t *)(obj + 0x18) != 0) {
            if (obj + 0x40 <= obj)
                txm_breakpoint(0x5519, 0x5e168);
            ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
        }
        return 0;
    }
    for (;;) {
        if (e <= p)
            return 1;
        *(int *)((char *)iter + 0x14) = *(int *)((char *)iter + 0x14) + 1;
        uint64_t r = txm_dict_parse(iter, p);
        *(int *)((char *)iter + 0x14) = *(int *)((char *)iter + 0x14) - 1;
        if ((r & 1) == 0)
            break;
        p = e;
    }
    if (*(uint64_t *)(obj + 0x18) != 0) {
        if (obj + 0x40 <= obj)
            txm_breakpoint(0x5519, 0x5e168);
        ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
    }
    return 0;
}

/* ============================================================================
 * FUN_0005e168 @ 0x0005e168  (est. txm_entitlements_dict_init)
 * Ghidra: undefined8 FUN_0005e168(ulong param_1,long *param_2,ulong *param_3)
 * Initializes a DER entitlements-dictionary iterator (param_3) from a data
 *   span (param_2 = {count, data, len}); sets the type header (0x101/0x100 for
 *   count 2/other), copies the span bounds and returns the header table
 *   (DAT_0001db00 / DAT_0001db08). */
static uint64_t
txm_entitlements_dict_init(uint64_t obj, uint64_t *span, uint64_t *iter)
{
    if ((*span == 0) || (span[1] == 0) || (span[2] == 0))
        return *(uint64_t *)(0x1db08);
    iter[5] = 0; iter[4] = 0; iter[7] = 0; iter[6] = 0;
    iter[1] = 0; iter[0] = 0; iter[3] = 0; iter[2] = 0;
    *(uint8_t *)(iter + 7) = 0;
    uint64_t data = span[2], len = span[2], count = span[1];
    if (*span == 2) {
        if (data < count)
            txm_breakpoint(0x5519, 0x5e374);
        iter[0] = obj;
        iter[1] = 0;
        uint64_t t = *(uint64_t *)(0xdc30);
        iter[3] = *(uint64_t *)(0xdc38);
        iter[2] = t;
        *(uint16_t *)(iter + 4) = 0x101;
        *(uint32_t *)((char *)iter + 0x22) = 0;
        *(uint16_t *)((char *)iter + 0x26) = 0;
        iter[6] = len;
        iter[5] = count;
        uint64_t start = 0, e = 0;
        /* FUN_0005d550(obj, 0, 0, &start, &local) */
        if (txm_dict_next_value(obj, 0, 0, &start, &e) == 0) {
            if (*(uint64_t *)(obj + 0x18) != 0) {
                if (obj + 0x40 <= obj)
                    txm_breakpoint(0x5519, 0x5e374);
                ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
            }
        } else if (start < e) {
            if (txm_dict_next_value(obj, 0, 0, 0, &start) == 0) {
                if (*(uint64_t *)(obj + 0x18) != 0) {
                    if (obj + 0x40 <= obj)
                        txm_breakpoint(0x5519, 0x5e374);
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(obj + 0x18)))(obj, "%s %s");
                }
            }
        }
        iter[1] = 0;
        iter[0] = obj;
        iter[5] = start;
        iter[4] = 0;
        iter[6] = e;
    } else {
        if (data < count)
            txm_breakpoint(0x5519, 0x5e374);
        iter[0] = obj;
        iter[1] = 0;
        uint64_t t = *(uint64_t *)(0xdc20);
        iter[3] = *(uint64_t *)(0xdc28);
        iter[2] = t;
        *(uint16_t *)(iter + 4) = 0x100;
        *(uint32_t *)((char *)iter + 0x22) = 0;
        *(uint16_t *)((char *)iter + 0x26) = 0;
        iter[5] = count;
        iter[6] = data;
    }
    return *(uint64_t *)(0x1db00);
}

/* ============================================================================
 * FUN_0005e374 @ 0x0005e374  (est. txm_ce_subset)\n * Ghidra: undefined8 FUN_0005e374(char *param_1,char *param_2)
 * CoreEntitlements subset check: verifies that every key of entitlements
 *   blob param_1 is present (and equal) in entitlements blob param_2. The
 *   blobs are DER plist objects (key type 0x2000000000000011 /
 *   0x6000000000000010). Returns 0 equal/subset, 6/9/10/0xb on mismatch. */
static uint64_t
txm_ce_subset(uint64_t a, uint64_t b)
{
    if ((a == 0) || (b == 0))
        return 0xb;
    if ((*(uint8_t *)b == 0x01) && (*(uint8_t *)a == 0)) {
        uint64_t count = 0;
        if (*(uint64_t *)(a + 0x18) == 0x2000000000000011 ||
            *(uint64_t *)(a + 0x18) == 0x6000000000000010) {
            if (*(uint64_t *)(b + 0x18) == 0x2000000000000011 ||
                *(uint64_t *)(b + 0x18) == 0x6000000000000010) {
                uint64_t rc = txm_dict_count(a + 8, &count);    /* FUN_0005f1d0 */
                if ((int)rc == 0) {
                    if (count == 0)
                        return 0;
                    return txm_dict_apply(a + 8, txm_ce_subset_key, b + 8);   /* FUN_0005ef74 */
                }
            } else {
                return 9;
            }
        } else {
            return 10;
        }
        return rc;
    }
    return 6;
}

/* ============================================================================
 * FUN_0005e454 @ 0x0005e454  (est. txm_ce_subset_key)
 * Ghidra: undefined8 FUN_0005e454(long param_1,long param_2)
 * CoreEntitlements subset callback: validates that a single key (param_1) of
 *   the first blob matches the corresponding key in the second blob (param_2);
 *   data keys (0xc) are string-compared, nested dictionaries recurse via
 *   FUN_0005e540. Logs "CoreEntitlements subset %s %s" on failure. */
static uint64_t
txm_ce_subset_key(uint64_t a, uint64_t b)
{
    uint64_t key = 0, val = 0;
    if (*(uint64_t *)(a + 0x10) == 0xc) {
        key = *(uint64_t *)(a + 0x18);
        val = *(uint64_t *)(a + 0x20);
    }
    uint64_t rc = txm_ce_key_lookup(*(uint64_t *)(b + 8), &key, &val);   /* FUN_0005f5a4 */
    if ((int)rc == 0) {
        uint64_t la = txm_strnlen(0x6b55);   /* DAT_00006b55 */
        uint64_t lb = 0;
        if ((la != 0) && (val == 0xc)) {
            uint64_t n = la <= lb ? la : lb;
            if ((txm_strncmp(0x6b55, val, n) == 0) && (la == lb))
                return 0;
        }
        rc = txm_ce_dict_subset(a + 0x30, &val);   /* FUN_0005e540 */
        if ((int)rc == 0)
            return rc;
    }
    txm_ce_log("CoreEntitlements subset %s %s");   /* FUN_00025c6c */
    return rc;
}

/* ============================================================================
 * FUN_0005e540 @ 0x0005e540  (est. txm_ce_dict_subset)
 * Ghidra: ulong FUN_0005e540(long param_1,long param_2)
 * CoreEntitlements recursive dictionary subset comparison. Dispatches by
 *   value type (bool/uint32/uint64/data/dict/array); returns 0 on subset
 *   match, 8/9/0xc on mismatch. */
static uint64_t
txm_ce_dict_subset(uint64_t a, uint64_t b)
{
    uint8_t v = 0;
    uint64_t val = 0;
    uint64_t atype = *(uint64_t *)(a + 0x10);
    if (atype < 0xc) {
        if (atype == 0x6000000000000010) {
            /* array/dict subset via recursive walk */
            if (*(uint64_t *)(a + 0x10) == 0x2000000000000011 ||
                *(uint64_t *)(a + 0x10) == 0x6000000000000010) {
                if (*(uint64_t *)(b + 0x10) == 0x2000000000000011 ||
                    *(uint64_t *)(b + 0x10) == 0x6000000000000010) {
                    uint64_t count = 0;
                    uint64_t rc = txm_dict_count(a, &count);
                    if ((int)rc == 0) {
                        if (count == 0)
                            return 0;
                        return txm_dict_apply(a, txm_ce_subset_key, b);
                    }
                } else {
                    return 9;
                }
            } else {
                return 10;
            }
            return 0;
        }
        if (atype != 1) {
            if (atype != 2)
                return 0xc;
            /* uint32: use a 4-byte string compare */
            (void)txm_decode_int(a + 0x18, &val);
            if (*(uint64_t *)(b + 0x10) == 2) {
                uint64_t bv = 0;
                (void)txm_decode_int(b + 0x18, &bv);
                if (val != bv)
                    return 8;
                return 0;
            }
            uint64_t rc = txm_ce_key_lookup(b, txm_ce_key_uint32, &val);
            if ((int)rc != 0)
                return rc;
            return 0;
        }
        /* bool */
        uint64_t rc = txm_ce_bool_get(a, &v);        /* FUN_0005f768 */
        if ((int)rc != 0)
            return rc;
        uint64_t bv = 0;
        rc = txm_ce_bool_get(b, &bv);
        if (((v ^ (uint8_t)bv) & 1) == 0)
            return 0;
        return 8;
    } else {
        if (atype != 0xc) {
            if (atype == 0x2000000000000010) {
                if (*(uint64_t *)(b + 0x10) != 0x2000000000000010)
                    return 9;
                uint64_t count = 0;
                uint64_t rc = txm_dict_count(a, &count);
                if ((int)rc != 0)
                    return rc;
                if (count != 0)
                    return txm_dict_apply(a, txm_ce_key_array, b);
                return 0;
            }
            if (atype != 0x2000000000000011)
                return 0xc;
            /* recurse into dict type */
            if (*(uint64_t *)(a + 0x10) == 0x2000000000000011 ||
                *(uint64_t *)(a + 0x10) == 0x6000000000000010) {
                if (*(uint64_t *)(b + 0x10) == 0x2000000000000011 ||
                    *(uint64_t *)(b + 0x10) == 0x6000000000000010) {
                    uint64_t count = 0;
                    uint64_t rc = txm_dict_count(a, &count);
                    if ((int)rc == 0) {
                        if (count == 0)
                            return 0;
                        return txm_dict_apply(a, txm_ce_subset_key, b);
                    }
                } else {
                    return 9;
                }
            } else {
                return 10;
            }
            return 0;
        }
        /* data (0xc) */
        uint64_t adata = *(uint64_t *)(a + 0x18), alen = *(uint64_t *)(a + 0x20);
        if (*(uint64_t *)(b + 0x10) == 0xc) {
            uint64_t rc = txm_ce_data_cmp(b, adata, alen, 1);   /* FUN_0005f690 */
            return rc;
        }
        /* string/uint compare against lookup */
        uint64_t bv = 0;
        uint64_t rc = txm_ce_key_lookup(b, txm_ce_key_uint32, &bv);
        return 0;
    }
}

/* ============================================================================
 * FUN_0005e7b8 @ 0x0005e7b8  (est. txm_ce_array_subset)
 * Ghidra: undefined8 FUN_0005e7b8(int *param_1,long param_2)
 * CoreEntitlements array subset callback: iterates the array elements and
 *   validates each against the subset (via FUN_0005e540). Returns 0 on
 *   subset match, 5/8/0xd on mismatch. */
static uint64_t
txm_ce_array_subset(int *a, uint64_t b)
{
    uint64_t data = *(uint64_t *)(b + 8);
    uint64_t count[7] = {0};
    if (*a == 2) {
        return 5;
    }
    uint64_t rc = txm_dict_count(data, count);   /* FUN_0005f1d0 */
    uint64_t total = count[0];
    if ((int)rc == 0) {
        if (count[0] != 0) {
            int matched = 0;
            uint64_t i = 0;
            for (;;) {
                uint64_t elem[7] = {0};
                rc = txm_dict_elem(data, i, elem + 1);   /* FUN_0005f360 */
                if ((int)rc != 0)
                    return rc;
                int kind;
                switch (elem[3]) {
                case 0x2000000000000011: case 0x6000000000000010: kind = 1; break;
                case 2: kind = 3; break;
                case 1: return 5;
                case 4: kind = 6; break;
                case 0xc: kind = 4; break;
                case 0x12: kind = 7; break;
                case 0x17: kind = 8; break;
                case 0x2000000000000010: return 5;
                default: goto skip;
                }
                rc = txm_ce_dict_subset(a + 2, elem + 1);
                if ((int)rc == 0)
                    return rc;
skip:
                i++;
                if (total == i)
                    break;
            }
        }
        rc = 8;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005e960 @ 0x0005e960  (est. txm_range_normalize)\n * Ghidra: undefined1 [16] FUN_0005e960(ulong param_1,long param_2,uint param_3)
 * Normalizes a {base,len} range against a 0x400000000000-boundary tag: adjusts
 *   the end address into the tagged space and bounds-checks the span, then
 *   DER-decodes it (FUN_00044178). Returns a 16-byte {len,data} pair. */
static uint64_t *
txm_range_normalize(uint64_t base, uint64_t len, uint32_t extra)
{
    static uint64_t out[2];
    uint64_t end = base + len;
    if (((base ^ end) & 0xffc0000000000000) != 0)
        end = (end & 0xffffffffffff) | 0xc8a2000000000000;
    uint64_t start = base + extra;
    if (end < start || start < base)
        txm_breakpoint(0x5519, 0x5e9a0);
    uint64_t span = len - (uint64_t)extra;
    uint64_t d[4] = {start, span, 0, 0};
    /* FUN_00044178(&d, &local) */
    out[0] = d[2];
    out[1] = d[3];
    return out;
}

/* ============================================================================
 * FUN_0005e9c8 @ 0x0005e9c8  (est. txm_entitlements_parse)\n * Ghidra: uint FUN_0005e9c8(long param_1,undefined8 *param_2)
 * Parses a DER entitlements blob (param_1): walks the dictionary collecting
 *   key/value entries (FUN_0005ea8c) into a count in param_2; rejects blobs
 *   with < 3 entries (code 0x12 unless a nonce-flag is set) or with the
 *   nonce-skip bit. Returns 0 on success. */
static uint32_t
txm_entitlements_parse(uint64_t blob, uint64_t *out)
{
    if (blob == 0)
        return 0xb;
    uint64_t base = blob + 8;
    uint64_t count = 0, key = 0, val = 0;
    uint32_t rc = txm_dict_apply(base, txm_ce_key_entitlement, &base);   /* FUN_0005ef74 */
    if ((rc != 0) && (rc != 0x12)) {
        if (rc != 0xd) {
            return rc;
        }
        rc = 0;
        count = 0;
    }
    if (count < 3 || rc == 0x12) {
        rc = 0xffffff05;
        if ((*(uint8_t *)(blob + 0x80) & 1) == 0)
            rc = 0x12;
    } else {
        rc = 0;
        if (out != 0)
            *out = key;
    }
    return rc & 0xffff;
}

/* ============================================================================
 * FUN_0005ea8c @ 0x0005ea8c  (est. txm_ce_key_entitlement)\n * Ghidra: undefined8 FUN_0005ea8c(ulong *param_1,ulong *param_2)
 * Entitlement-collection callback: appends a {key,val} pair to the output
 *   buffer (param_2+1), growing the count (param_2+2). Returns 0 on success,
 *   3 on overflow. */
static uint64_t
txm_ce_key_entitlement(uint64_t *a, uint64_t *ctx)
{
    uint64_t *out = (uint64_t *)ctx[1];
    uint64_t base = *(uint64_t *)*out;
    uint64_t koff = a[0] - base;
    if (base <= a[0]) {
        if (koff >> 0x20 != 0)
            return 0x12;
        uint64_t voff = a[6] - base;
        if (base <= a[6]) {
            if (voff >> 0x20 != 0)
                return 0x12;
            if (out[3] != 0) {
                if ((uint64_t)out[4] <= ctx[0])
                    return 3;
                uint32_t *p = (uint32_t *)(out[3] + ctx[0] * 8);
                p[0] = (uint32_t)koff;
                p[1] = (uint32_t)voff;
            }
            uint64_t n = out[2];
            out[2] = n + 8;
            if (n < 0xfffffffffffffff8) {
                out[1] = out[1] + 1;
                return 0;
            }
        }
    }
    return 3;
}

/* ============================================================================
 * FUN_0005eb18 @ 0x0005eb18  (est. txm_ce_alloc_valid)\n * Ghidra: undefined4 FUN_0005eb18(long param_1)
 * Returns 0 when the entitlements object has a backing store (param_1+0x30),
 *   0xf when absent, 0xb for a NULL object. */
static uint32_t
txm_ce_alloc_valid(uint64_t obj)
{
    if (obj != 0) {
        if (*(uint64_t *)(obj + 0x30) != 0)
            return 0;
        return 0xf;
    }
    return 0xb;
}

/* ============================================================================
 * FUN_0005eb3c @ 0x0005eb3c  (est. txm_ce_alloc_sort)\n * Ghidra: undefined8 FUN_0005eb3c(long param_1)
 * Sorts the parsed entitlements key/value array: allocates the entry buffer
 *   (FUN_00024f14), walks the dictionary collecting pairs (FUN_0005ea8c),
 *   then bubble-sorts by key using txm_range_normalize comparisons. Stores
 *   the buffer at param_1+0x30 and count at +0x38. */
static uint64_t
txm_ce_alloc_sort(uint64_t obj)
{
    uint64_t count = 0;
    if (obj == 0)
        return 0xb;
    uint64_t rc = txm_entitlements_parse(obj, &count);
    uint64_t n = count;
    if ((int)rc == 0) {
        uint64_t *buf = (uint64_t *)txm_alloc(count);   /* FUN_00024f14 */
        if (buf == 0) {
            return 0xe;
        }
        uint64_t d[3] = {obj + 8, 0, 0};
        uint64_t ctx[2] = {(uint64_t)buf, n >> 3};
        uint64_t r = txm_dict_apply(d[0], txm_ce_key_entitlement, d);   /* FUN_0005ef74 */
        if (r == 0) {
            if (7 < n) {
                /* bubble-sort the n/8 entries by key */
                for (uint64_t pass = 0; pass < n/8; pass++) {
                    bool swapped = false;
                    for (uint64_t i = 0; i < n/8 - 1; i++) {
                        uint64_t *pa = buf + i, *pb = buf + i + 1;
                        uint64_t ka = txm_range_normalize(*(uint64_t *)(obj + 8), *(uint64_t *)(obj + 0x10), *pa)[0];
                        uint64_t kb = txm_range_normalize(*(uint64_t *)(obj + 8), *(uint64_t *)(obj + 0x10), *pb)[0];
                        if (txm_memcmp(ka, kb, 0) > 0) {
                            uint64_t t = *pa; *pa = *pb; *pb = t;
                            swapped = true;
                        }
                    }
                    if (!swapped)
                        break;
                }
            }
        } else {
            txm_free(buf, count);
            buf = 0;
            n = 0;
        }
        rc = 0;
        *(uint64_t *)(obj + 0x30) = (uint64_t)buf;
        *(uint64_t *)(obj + 0x38) = n;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005ed14 @ 0x0005ed14  (est. txm_ce_alloc_free)\n * Ghidra: undefined8 FUN_0005ed14(long param_1)
 * Frees the sorted entitlements entry buffer (param_1+0x30) and clears it. */
static uint64_t
txm_ce_alloc_free(uint64_t obj)
{
    if (obj != 0) {
        if (*(uint64_t *)(obj + 0x30) == 0) {
            return 0xf;
        }
        txm_free(*(uint64_t *)(obj + 0x30), *(uint64_t *)(obj + 0x38) << 3);
        *(uint64_t *)(obj + 0x30) = 0;
        *(uint64_t *)(obj + 0x38) = 0;
        return 0;
    }
    return 0xb;
}

/* ============================================================================
 * FUN_0005ed6c @ 0x0005ed6c  (est. txm_dict_apply)\n * Ghidra: uint FUN_0005ed6c(long param_1,code *param_2,undefined8 param_3)
 * Applies a callback (param_2) to every key/value pair of a DER plist
 *   dictionary (param_1): iterates via FUN_000446f4/FUN_00044724, classifies
 *   each key length into a type code (1..9), and invokes the callback with
 *   {type, value-span}. Returns 0 on success, 0xd if the dictionary was
 *   empty, 10/2 on malformed input. */
static uint32_t
txm_dict_apply(uint64_t dict, uint64_t cb, uint64_t ctx)
{
    uint64_t st[7] = {0};
    uint8_t matched = 0;
    uint64_t seen = 0;
    st[6] = ctx;
    if (txm_dictionary_iter_reset() != 0)   /* FUN_0002986c */
        return 2;
    if ((*(uint64_t *)(dict + 0x10) + 0xdffffffffffffff0U < 2) ||
        (*(uint64_t *)(dict + 0x10) == 0x6000000000000010)) {
        txm_der_dict_iter(dict + 0x18, st);   /* FUN_000446f4 */
        uint32_t rc = 1;
        uint64_t first;
        while (txm_der_dict_next(st, st + 2) == 0) {   /* FUN_00044724 */
            first = st[0];
            uint64_t vspan[5] = {st[0], st[0] - first, st[2], st[3], st[4]};
            uint32_t type;
            switch (st[2]) {
            case 0x2000000000000011: case 0x6000000000000010: type = 1; break;
            case 2: type = 3; break;
            case 4: type = 6; break;
            case 0xc: type = 4; break;
            case 1: type = 5; break;
            case 0x12: type = 7; break;
            case 0x17: type = 8; break;
            case 0x2000000000000010: type = 2; break;
            default: type = 0; break;
            }
            if (type != 0)
                vspan[0] = (uint64_t)type;
            uint32_t r = ((uint32_t (*)(uint64_t *, uint64_t *))cb)(&vspan, st + 5);
            if ((r != 0) || ((matched & 1) != 0))
                return r;
            matched = 1;
            seen = st[5] + 1;
        }
        if (seen != 0)
            return 0;
        return 0xd;
    }
    return 10;
}

/* ============================================================================
 * FUN_0005ef74 @ 0x0005ef74  (est. txm_dict_apply_dict)\n * Ghidra: undefined8 FUN_0005ef74(long param_1,undefined8 param_2,undefined8 param_3)
 * Applies a callback to a dictionary-typed value (param_1, type 0x11/0x10);
 *   returns 10 if the value is not a dictionary. */
static uint64_t
txm_dict_apply_dict(uint64_t dict, uint64_t cb, uint64_t ctx)
{
    if (*(uint64_t *)(dict + 0x10) == 0x2000000000000011 ||
        *(uint64_t *)(dict + 0x10) == 0x6000000000000010) {
        uint64_t c[2] = {ctx, cb};
        return txm_dict_apply(dict, txm_ce_key_dict_wrap, c);   /* FUN_0005efe0 */
    }
    return 10;
}

/* ============================================================================
 * FUN_0005efe0 @ 0x0005efe0  (est. txm_ce_key_dict_wrap)\n * Ghidra: uint FUN_0005efe0(int *param_1,undefined8 *param_2)
 * Wraps a dict_apply callback: decodes the nested dictionary, classifies its
 *   single key, and forwards to the wrapped callback (param_2[1]) with the
 *   parsed {type, value} pair. */
static uint32_t
txm_ce_key_dict_wrap(int *a, uint64_t *ctx)
{
    if (*a != 2) {
        return 0xc;
    }
    uint64_t st[9] = {0};
    txm_der_dict_iter(a + 8, st);   /* FUN_000446f4 */
    uint64_t first = st[0];
    uint32_t rc = txm_der_dict_next(st, st + 5);   /* FUN_00044724 */
    if (rc == 0) {
        uint64_t vspan[5] = {st[0], st[0] - first, st[5], st[6], st[7]};
        if (txm_der_dict_next(st, st + 2) == 0) {
            uint64_t sub[5] = {st[0], st[0] - st[0], st[2], st[3], st[4]};
            uint32_t type;
            switch (st[2]) {
            case 0x2000000000000011: case 0x6000000000000010: type = 1; break;
            case 2: type = 3; break;
            case 4: type = 6; break;
            case 0xc: type = 4; break;
            case 1: type = 5; break;
            case 0x12: type = 7; break;
            case 0x17: type = 8; break;
            case 0x2000000000000010: type = 2; break;
            default: type = 0; break;
            }
            if (type != 0)
                vspan[0] = (uint64_t)type;
            uint64_t cb = ctx[1];
            uint32_t r = ((uint32_t (*)(uint64_t *, uint64_t *))cb)(&vspan, ctx);
            *((uint8_t *)ctx + 0x10) = 1;
            return r;
        }
    }
    uint32_t e = rc;
    if (rc > 7)
        e = 0xffffff17;
    return e & 0xffff;
}

/* ============================================================================
 * FUN_0005f1d0 @ 0x0005f1d0  (est. txm_dict_count)\n * Ghidra: undefined8 FUN_0005f1d0(undefined8 param_1,undefined8 *param_2)
 * Counts the entries in a DER dictionary via FUN_0005ed6c; treats an empty
 *   dictionary (0xd) as count 0. */
static uint64_t
txm_dict_count(uint64_t dict, uint64_t *out)
{
    uint64_t n = 0;
    uint64_t rc = txm_dict_apply(dict, txm_ce_key_count, &n);   /* FUN_0005ed6c + FUN_0005f238 */
    if ((int)rc == 0xd) {
        n = 0;
    } else if ((int)rc != 0) {
        return rc;
    }
    *out = n;
    return 0;
}

/* ============================================================================
 * FUN_0005f238 @ 0x0005f238  (est. txm_ce_key_count)\n * Ghidra: undefined8 FUN_0005f238(undefined8 param_1,long param_2)
 * Counting callback: increments the counter at param_2+8. */
static uint64_t
txm_ce_key_count(uint64_t a, uint64_t ctx)
{
    (*(uint64_t **)(ctx + 8))[0] = (*(uint64_t **)(ctx + 8))[0] + 1;
    return 0;
}

/* ============================================================================
 * FUN_0005f254 @ 0x0005f254  (est. txm_ce_key_lookup2)\n * Ghidra: undefined8 FUN_0005f254(long param_1,undefined8 *param_2)
 * CoreEntitlements key lookup callback for nested dictionaries: searches the
 *   nested dict (param_1+0x30) for the expected key (param_2). */
static uint64_t
txm_ce_key_lookup2(uint64_t a, uint64_t *ctx)
{
    uint64_t key = 0, val = 0;
    if (*(uint64_t *)(a + 0x10) == 0xc) {
        key = *(uint64_t *)(a + 0x18);
        val = *(uint64_t *)(a + 0x20);
    }
    uint64_t want = ctx[0];
    uint64_t rc = txm_dict_apply(ctx[1], txm_ce_key_lookup_cb, &want);   /* FUN_0005ef74 */
    if ((int)rc == 0) {
        if (*(int *)(a + 0x28) == 1) {
            rc = txm_dict_apply_dict(a + 0x30, txm_ce_key_lookup2, a + 0x30);
            if (((int)rc != 0xd) && ((int)rc != 0))
                return rc;
        }
        rc = 0;
    }
    return rc;
}

/* ============================================================================
 * FUN_0005f2fc @ 0x0005f2fc  (est. txm_ce_key_lookup_cb)\n * Ghidra: undefined4 FUN_0005f2fc(long param_1,ulong *param_2)
 * Lookup callback: returns 0 when the current key matches the sought key. */
static uint32_t
txm_ce_key_lookup_cb(uint64_t a, uint64_t *ctx)
{
    if (*(uint64_t *)ctx[1] < ctx[0]) {
        if (*(uint64_t *)(a + 0x10) == 0xc) {
            return txm_ce_data_cmp((uint64_t *)ctx[1] + 1, *(uint64_t *)(a + 0x18), *(uint64_t *)(a + 0x20)) == 0 ? 0 : 4;   /* FUN_0005f8d0 */
        }
        return 0;
    }
    return 0;
}

/* ============================================================================
 * FUN_0005f338 @ 0x0005f338  (est. txm_ce_key_lookup_cb_direct)\n * Ghidra: undefined4 FUN_0005f338(long param_1)
 * Direct key-compare callback (FUN_0005f8d0 on the key at param_1+8). */
static uint32_t
txm_ce_key_lookup_cb_direct(uint64_t a)
{
    if (txm_ce_data_cmp(a + 8, 0, 0) != 0)   /* FUN_0005f8d0 */
        return 0;
    return 4;
}

/* ============================================================================
 * FUN_0005f360 @ 0x0005f360  (est. txm_dict_elem)\n * Ghidra: undefined8 FUN_0005f360(long param_1,undefined8 param_2,undefined8 *param_3)
 * Reads the element at index param_2 of an array-typed value (param_1),
 *   dispatching by element type; returns 0 and writes {type,data,len} into
 *   param_3. */
static uint64_t
txm_dict_elem(uint64_t arr, uint64_t idx, uint64_t *out)
{
    uint64_t out2[5] = {0};
    uint64_t atype = *(uint64_t *)(arr + 0x10);
    if ((int64_t)atype < 0x2000000000000010) {
        if ((atype > 0x17 || (1ULL << (atype & 0x3f) & 0x841016ULL) == 0) && atype != 0xa000000000000010)
            return 6;
    } else {
        if (atype == 0x2000000000000010) {
            uint64_t st = idx;
            uint64_t rc = txm_dict_apply(arr, txm_ce_key_array_elem, &st);   /* FUN_0005ed6c + FUN_0005f468 */
            if ((int)rc != 0)
                return rc;
            if ((out2[0] & 1) == 0)
                return 7;
            if (out == 0)
                return 0;
            out[1] = out2[1];
            out[0] = out2[0];
            out[3] = out2[3];
            out[2] = out2[2];
            out[4] = out2[4];
            return 0;
        }
        if ((atype != 0x6000000000000010) && (atype != 0x2000000000000011))
            return 6;
    }
    return 10;
}

/* ============================================================================
 * FUN_0005f468 @ 0x0005f468  (est. txm_ce_key_array_elem)\n * Ghidra: undefined8 FUN_0005f468(long param_1,long *param_2)
 * Array-element extraction callback: when the current index matches the
 *   sought index (param_2+1), copies the element span into the output buffer
 *   (param_2+8) and sets the matched flag. */
static uint64_t
txm_ce_key_array_elem(uint64_t a, uint64_t *ctx)
{
    uint8_t *dst = (uint8_t *)ctx[1];
    if (*(uint64_t *)(dst + 8) == ctx[0]) {
        *dst = 1;
        *(uint64_t *)(dst + 0x18) = *(uint64_t *)(a + 0x10);
        *(uint64_t *)(dst + 0x10) = *(uint64_t *)(a + 8);
        *(uint64_t *)(dst + 0x28) = *(uint64_t *)(a + 0x20);
        *(uint64_t *)(dst + 0x20) = *(uint64_t *)(a + 0x18);
    } else if ((*dst & 1) == 0) {
        return 0;
    }
    *(uint8_t *)(ctx + 2) = 1;
    return 0;
}

/* ============================================================================
 * FUN_0005f4b4 @ 0x0005f4b4  (est. txm_ce_type_code)\n * Ghidra: undefined8 FUN_0005f4b4(long param_1,undefined4 *param_2)
 * Maps an img4 value type (param_1+0x10) to a CoreEntitlements type code
 *   (1..9); returns 6 on an unknown type. */
static uint64_t
txm_ce_type_code(uint64_t a, uint32_t *out)
{
    uint64_t t = *(uint64_t *)(a + 0x10);
    uint32_t code;
    switch (t) {
    case 0x2000000000000011: case 0x6000000000000010: code = 1; break;
    case 2: code = 3; break;
    case 4: code = 6; break;
    case 0xc: code = 4; break;
    case 1: code = 5; break;
    case 0x12: code = 7; break;
    case 0x17: code = 8; break;
    case 0x2000000000000010: code = 2; break;
    default: return 6;
    }
    if (out != 0)
        *out = code;
    return 0;
}

/* ============================================================================
 * FUN_0005f5a4 @ 0x0005f5a4  (est. txm_ce_key_lookup)\n * Ghidra: undefined8 FUN_0005f5a4(undefined8 param_1,undefined8 param_2,undefined8 *param_3)
 * CoreEntitlements key lookup: applies FUN_0005f628 over a dictionary value
 *   (param_1), returning the matched {type,data,len} in param_3. */
static uint64_t
txm_ce_key_lookup(uint64_t dict, uint64_t key, uint64_t *out)
{
    uint64_t st[5] = {0};
    uint64_t key2 = key;
    uint64_t rc = txm_dict_apply_dict(dict, txm_ce_key_lookup_cb2, &st);   /* FUN_0005ef74 + FUN_0005f628 */
    if ((int)rc == 0) {
        if ((st[0] & 1) == 0) {
            rc = 7;
        } else {
            rc = 0;
            if (out != 0) {
                out[1] = st[1];
                out[0] = st[0];
                out[3] = st[3];
                out[2] = st[2];
                out[4] = st[4];
            }
        }
    }
    return rc;
}

/* ============================================================================
 * FUN_0005f628 @ 0x0005f628  (est. txm_ce_key_lookup_cb2)\n * Ghidra: undefined8 FUN_0005f628(long param_1,long param_2)
 * Key-lookup callback: when the sought key (param_2+1) matches the current
 *   key, copies the value span into the output buffer (param_2+8) and sets
 *   the matched flag. */
static uint64_t
txm_ce_key_lookup_cb2(uint64_t a, uint64_t ctx)
{
    uint8_t *dst = *(uint8_t **)(ctx + 8);
    int m = txm_ce_data_cmp(a, *(uint64_t **)(dst + 0x30), (*(uint64_t **)(dst + 0x30))[1], 0);   /* FUN_0005f690 */
    if (m == 0) {
        *dst = 1;
        *(uint64_t *)(dst + 0x28) = *(uint64_t *)(a + 0x50);
        *(uint64_t *)(dst + 0x20) = *(uint64_t *)(a + 0x48);
        *(uint64_t *)(dst + 0x18) = *(uint64_t *)(a + 0x40);
        *(uint64_t *)(dst + 0x10) = *(uint64_t *)(a + 0x38);
        *(uint64_t *)(dst + 8) = *(uint64_t *)(a + 0x30);
        *(uint8_t *)(ctx + 0x10) = 1;
    }
    return 0;
}

/* ============================================================================
 * FUN_0005f690 @ 0x0005f690  (est. txm_ce_data_cmp)\n * Ghidra: undefined4 FUN_0005f690(long param_1,undefined8 param_2,ulong param_3,int param_4)
 * Compares a data value (param_1, data at +0x18 len +0x20) against a byte
 *   span (param_2, param_3), optionally trimming a trailing '*' wildcard
 *   (param_4). Returns 0 on match, 8 on mismatch, 9/0xb on malformed. */
static uint32_t
txm_ce_data_cmp(uint64_t a, uint64_t data, uint64_t len, int wildcard)
{
    if (len == 0)
        return 0xb;
    if (*(uint64_t *)(a + 0x10) == 0xc) {
        char *p = *(char **)(a + 0x18);
        uint64_t alen = *(uint64_t *)(a + 0x20);
        uint64_t clen = len;
        if (wildcard != 0) {
            char *end = p + alen;
            if ((((uint64_t)p ^ (uint64_t)end) & 0xffc0000000000000) != 0)
                end = (char *)(((uint64_t)end & 0xffffffffffff) | 0xc8a2000000000000);
            char *last = p + alen - 1;
            if (end <= last || last < p)
                txm_breakpoint(0x5519, 0x5f750);
            if (*last == '*') {
                if (alen == 0)
                    txm_breakpoint(0x5519, 0x5f750);
                clen = alen - 1;
                alen = alen - 1;
                if (len < alen)
                    return 8;
            }
        }
        uint64_t n = clen <= alen ? clen : alen;
        if ((txm_memcmp(data, p, n) == 0) && (clen == alen))
            return 0;
        return 8;
    }
    return 9;
}

/* ============================================================================
 * FUN_0005f750 @ 0x0005f750  (est. txm_ce_key_copy)\n * Ghidra: undefined8 FUN_0005f750(undefined8 *param_1,undefined8 *param_2)
 * Copies a {key,val} span pair into param_2. */
static uint64_t
txm_ce_key_copy(uint64_t *a, uint64_t *out)
{
    if (out != 0) {
        uint64_t v = a[1];
        out[0] = a[0];
        out[1] = v;
    }
    return 0;
}

/* ============================================================================
 * FUN_0005f768 @ 0x0005f768  (est. txm_ce_bool_get)\n * Ghidra: undefined8 FUN_0005f768(long param_1,byte *param_2)
 * Reads a CoreEntitlements bool value (param_1, type 1); treats a raw 0x01
 *   as true. Returns 0. */
static uint64_t
txm_ce_bool_get(uint64_t a, uint8_t *out)
{
    uint8_t v = 0;
    if (*(uint64_t *)(a + 0x10) == 1) {
        int r = 0;   /* FUN_0004443c(a+0x18, &v) */
        if (((r != 0) && (*(uint64_t *)(a + 0x20) == 1)) && (**(char **)(a + 0x18) == 0x01))
            v = 1;
        *out = v & 1;
        return 0;
    }
    return 9;
}

/* ============================================================================
 * FUN_0005f7ec @ 0x0005f7ec  (est. txm_ce_data_get)\n * Ghidra: undefined8 FUN_0005f7ec(long param_1,undefined8 *param_2)
 * Reads a CoreEntitlements data value (param_1, type 0xc) into param_2. */
static uint64_t
txm_ce_data_get(uint64_t a, uint64_t *out)
{
    if (*(uint64_t *)(a + 0x10) != 0xc)
        return 9;
    if (out != 0) {
        uint64_t v = *(uint64_t *)(a + 0x20);
        out[0] = *(uint64_t *)(a + 0x18);
        out[1] = v;
        return 0;
    }
    return 0;
}

/* ============================================================================
 * FUN_0005f824 @ 0x0005f824  (est. txm_ce_bool_equal)\n * Ghidra: int FUN_0005f824(undefined8 param_1,byte param_2)
 * Compares a CoreEntitlements bool against an expected value. */
static int
txm_ce_bool_equal(uint64_t a, uint8_t expect)
{
    uint8_t v = 0;
    int rc = txm_ce_bool_get(a, &v);
    int r = 8;
    if (((expect ^ v) & 1) == 0)
        r = 0;
    if (rc != 0)
        r = rc;
    return r;
}

/* ============================================================================
 * FUN_0005f874 @ 0x0005f874  (est. txm_ce_data_equal)\n * Ghidra: undefined4 FUN_0005f874(long param_1,long param_2)
 * Compares a data value against a byte span via FUN_0005f8d0. */
static uint32_t
txm_ce_data_equal(uint64_t a, uint64_t span)
{
    if (*(uint64_t *)(span + 8) == 0)
        return 0xb;
    if (*(uint64_t *)(a + 0x10) == 4) {
        if (txm_ce_data_cmp_alt(span, *(uint64_t *)(a + 0x18), *(uint64_t *)(a + 0x20)) != 0)   /* FUN_0005f8d0 */
            return 8;
        return 0;
    }
    return 9;
}

/* ============================================================================
 * FUN_0005f8d0 @ 0x0005f8d0  (est. txm_ce_data_cmp_alt)\n * Ghidra: ulong FUN_0005f8d0(undefined8 *param_1,undefined8 param_2,ulong param_3)
 * Byte-span compare: matches if the prefix is equal and the spans are the
 *   same length (param_1[1] vs param_3). Returns 0 match, -1/1 mismatch. */
static uint64_t
txm_ce_data_cmp_alt(uint64_t *a, uint64_t data, uint64_t len)
{
    uint64_t n = a[1] <= len ? a[1] : len;
    uint64_t r = txm_memcmp(a[0], data, n);
    if ((int)r == 0) {
        uint32_t c = (a[1] < len) ? 1 : 0xffffffff;
        if (a[1] != len)
            r = (uint64_t)c;
        else
            r = 0;
    }
    return r;
}

/* ============================================================================
 * FUN_0005f91c @ 0x0005f91c  (est. txm_ce_key_apply)\n * Ghidra: undefined8 FUN_0005f91c(int *param_1,long param_2)
 * CoreEntitlements key-apply callback: validates the current key type and
 *   value against the expected type; sets the matched flag. */
static uint64_t
txm_ce_key_apply(int *a, uint64_t ctx)
{
    int *dst = *(int **)(ctx + 8);
    int type = *dst;
    if (type == *a) {
        if (type == 6) {
            uint32_t rc = txm_ce_data_equal(a + 2, *(uint64_t *)(dst + 2));
            if (rc != 0)
                return rc;
        } else if (type == 4) {
            uint32_t rc = txm_ce_data_cmp(a + 2, *(uint64_t **)(dst + 2)[0], *(uint64_t **)(dst + 2)[1], (*(uint8_t *)(dst + 4) & 1) != 0);
            if (rc != 0)
                return rc;
        } else if (type == 3) {
            uint64_t d = *(uint64_t *)(dst + 2);
            uint64_t bv = 0;
            if ((*(uint64_t *)(a + 6) != 2) || (txm_decode_int(a + 8, &bv), d != bv))
                return 0;
        } else {
            return 6;
        }
        *(uint8_t *)((char *)dst + 0x11) = 1;
        *(uint8_t *)(ctx + 0x10) = 1;
        return 0;
    }
    return 0;
}

/* ============================================================================
 * FUN_0005fa0c @ 0x0005fa0c  (est. txm_ce_dict_match)\n * Ghidra: ulong FUN_0005fa0c(long param_1,undefined8 param_2)
 * CoreEntitlements dictionary match: applies FUN_0005f91c over the dictionary
 *   (param_1); a direct data comparison (type 4) is handled inline. */
static uint64_t
txm_ce_dict_match(uint64_t a, uint64_t b)
{
    uint64_t st[5] = {0};
    uint64_t ctx[2] = {0, b};
    if (*(uint64_t *)(a + 0x10) != 4) {
        uint64_t rc = txm_dict_apply(a, txm_ce_key_apply, ctx);   /* FUN_0005ed6c + FUN_0005f91c */
        if ((int)rc == 0) {
            uint32_t r = ((st[0] & 0x100) == 0) ? 8 : 0;
            return (uint64_t)r;
        }
        return rc;
    }
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5fa5c);
    return txm_ce_data_equal(a, b);   /* FUN_0005f874 */
}

/* ============================================================================
 * FUN_0005fa9c @ 0x0005fa9c  (est. txm_ce_cstr_match)\n * Ghidra: void FUN_0005fa9c(undefined8 param_1,undefined8 param_2)
 * CoreEntitlements string match: wraps a C string into a span and matches via
 *   FUN_0005fae0. */
static void
txm_ce_cstr_match(uint64_t a, uint64_t s)
{
    uint64_t span[2];
    span[1] = txm_strnlen(s, 0);
    span[0] = s;
    txm_ce_span_match(a, &span);   /* FUN_0005fae0 */
}

/* ============================================================================
 * FUN_0005fae0 @ 0x0005fae0  (est. txm_ce_span_match)\n * Ghidra: ulong FUN_0005fae0(long param_1,undefined8 *param_2)
 * CoreEntitlements span match: compares a data value (param_1, type 0xc)
 *   against the span (param_2). */
static uint64_t
txm_ce_span_match(uint64_t a, uint64_t *span)
{
    uint64_t data = span[0];
    if (*(uint64_t *)(a + 0x10) != 0xc) {
        uint64_t len = span[1];
        uint64_t st[5] = {0};
        uint64_t ctx[2] = {0, 0};
        uint64_t rc = txm_dict_apply(a, txm_ce_key_apply, ctx);   /* FUN_0005ed6c + FUN_0005f91c */
        uint32_t r = ((st[0] & 0x100) == 0) ? 8 : 0;
        if (rc != 0)
            r = rc;
        return (uint64_t)r;
    }
    uint64_t lr = (uint64_t)__builtin_return_address(0);
    if ((((lr ^ lr << 1) >> 0x3e) & 1) != 0)
        txm_breakpoint(0xc471, 0x5fb0c);
    return txm_ce_data_cmp(a, data, span[1], 0);   /* FUN_0005f690 */
}

/* ============================================================================
 * FUN_0005fb88 @ 0x0005fb88  (est. txm_entitlements_blob_parse)
 * Ghidra: uint FUN_0005fb88(ulong param_1,uint param_2,undefined1 *param_3,ulong param_4,ulong param_5)
 * Parses an entitlements blob (param_3, length param_4+param_5) against the
 *   process entitlements context (param_1): DER-decodes the blob (type
 *   selected by param_2), validates the "< ?xm" magic (0x6d783f3c), and
 *   imposes the entitlements policy (FUN_0005db20 / FUN_0005e168). Returns a
 *   CoreEntitlements error code (0 on success, 0xffxx on policy mismatch).
 * Confidence: medium (magic 0x6d783f3c = \"<?xm\" XML-plist header). */
static uint32_t
txm_entitlements_blob_parse(uint64_t ctx, uint32_t type, uint8_t *blob, uint64_t a, uint64_t b)
{
    uint32_t rc = 0xb;
    if (((ctx == 0) || (blob == 0)) || (a == 0) || (b == 0))
        goto out;
    if ((a & 0x8000000000000000ULL) && (b & 0x8000000000000000ULL)) {
        rc = 3;
        goto out;
    }
    uint64_t st[0x20] = {0};
    uint64_t span[2] = {a, b};
    if (txm_der_decode_item(&span, &st) != 0) {   /* FUN_00044178 */
        rc = 0xc0;
        goto out;
    }
    /* decode the blob as a CoreEntitlements object */
    uint64_t dict = 0, v = 0;
    rc = txm_ce_decode_object(&st, &dict);       /* FUN_00060230 */
    if (rc != 0)
        goto out;
    if ((int)dict == 0) {
        /* non-dictionary path */
        if (type < 5) {
            /* parse the identifier keys (FUN_0006037c) */
            uint64_t id = 0;
            rc = txm_ce_parse_identifier(&v, &id, type);   /* FUN_0006037c */
            if ((rc != 0) && (rc != 0xcf))
                goto out;
        }
        /* validate the "<?xm" magic when present */
        if ((b < 5) || (txm_memcmp(a, 0x6d783f3c, 5) != 0)) {
            uint64_t span2[2] = {a, a + b};
            uint64_t inner = 0;
            uint64_t ok = txm_dict_find_key(&span2, 0x2000000000000011, &inner);   /* FUN_00037304 */
            if ((ok & 1) == 0) {
                if (*(uint64_t *)(ctx + 0x18) != 0) {
                    ((void (*)(uint64_t, const char *))(*(uint64_t *)(ctx + 0x18)))(ctx, "%s %s");
                    goto out;
                }
            } else {
                uint64_t ent[5] = {0, 0, 0, ctx, 0};
                uint64_t s2[2] = {a, a + b};
                rc = txm_dict_parse(&ent, &s2);   /* FUN_0005db20 */
                /* (status in ent[0]: 0 = success) */
                if (rc == 0) {
                    uint64_t span3[2] = {a, a + b};
                    uint64_t impl = 0x1da90;
                    if (txm_entitlements_dict_init(ctx, &span3, blob + 0x40) == 0x1da90) {   /* FUN_0005e168 */
                        blob[0x80] = 1;
                        rc = 0;
                        goto out;
                    }
                    if (impl == 0x1daa0) {
                        rc = 0xff00;
                        goto out;
                    }
                    switch (impl) {
                    case 0x1dab0: rc = 0xff01; break;
                    case 0x1dac0: rc = 0xff02; break;
                    case 0x1dad0: rc = 0xff03; break;
                    case 0x1dae0: rc = 0xff04; break;
                    default: rc = 0xffffff05; if (impl != 0x1daf0) rc = 0xffffff06; break;
                    }
                    goto out;
                }
            }
        } else {
            if (*(uint64_t *)(ctx + 0x18) != 0)
                ((void (*)(uint64_t, const char *))(*(uint64_t *)(ctx + 0x18)))(ctx, "%s %s");
            rc = 0xff00;
            goto out;
        }
    } else {
        /* dictionary path (type >= 5) */
        rc = 0xb;
    }
out:
    return rc & 0xffff;
}
