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

/* ------------------------------------------------------------------ */
/* Globals referenced by this region (addresses from Ghidra) */
/* ------------------------------------------------------------------ */
extern uint64_t txm_canary;          /* DAT_00006cf0 stack canary */

#endif /* __ASSEMBLER__ */
/* __PART2__ */
