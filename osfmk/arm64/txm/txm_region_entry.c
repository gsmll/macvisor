/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0), Apple's code-signing / entitlement /
 * trust-cache / code-execution-policy authority. Ground truth: Ghidra FUN_
 * names + addresses in `txm.raw`. All names are estimates unless a string /
 * header name matches (confidence high). TXM = Trusted Execution Monitor GL0,
 * image base 0.
 *
 * This file covers the entry / code-signing-verification region
 * 0x20000-0x2a000 (batch T1): boot entry (`__text`), the page-enforcement /
 * executable-mapping authority (FUN_0002089c family), the code-region
 * association + execution-check helpers (00023254/0002316c/00022b10), the
 * entitlement / code-signing policy selectors (00023384/00023574), the
 * secure-channel init (000236f0), and the trust-cache load/unload machinery
 * (00026350/0002670c/00025ec4/0002623c).
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
 * FUN_000298ec / FUN_000f8804 in txm.raw; noreturn, variadic. */
extern void txm_panic(uint64_t code, ...) __attribute__((noreturn));

/* TXM formatted trace/log writer (serial + CTRR template). */
extern void txm_log(const char *fmt, ...);

/* TXM formatted output (snprintf into a fixed buffer), used by the panic/log
 * paths; FUN_000ad278-equivalent. */
extern void txm_format(uint64_t *out, ...);

/* SHA-2 update primitive used by trust-cache / hash paths. */
extern void txm_sha_update(uint64_t *state, uint64_t len, const void *data);

/* Device-tree property lookup: returns the DT node property value. */
extern const void *txm_dt_get_property(const char *path, const char *name,
                                       uint64_t *len);

/* CoreEntitlements entitlements-dictionary validation. */
extern int txm_ce_validate(uint64_t *ctx, uint64_t flags);

/* Profile / UUID helpers (boot entry family). */
extern uint64_t txm_profile_load(uint64_t profile_arg, uint64_t *profile_out);   /* FUN_00031fe8 */
extern int txm_profile_uuid_get(uint64_t profile, uint64_t max, void *out);       /* FUN_00060088 */
extern int txm_uuid_parse(const char *str, char *out, uint64_t *len);             /* FUN_0005f7ec */
extern int txm_uuid_compare(const void *a, uint64_t b);                           /* thunk_FUN_0002d990 */
extern uint8_t txm_hex_nibble(uint8_t c);                                         /* FUN_0002ddc0 */
extern void txm_stack_guard_fail(int matched);                                    /* FUN_0002f13c */
extern uint64_t uuid_len;                                                         /* parsed UUID length */

/* TXM object/lock runtime (FUN_00027128 acquire, FUN_00027218 release,
 * FUN_00027448 alloc, FUN_00027720 refcount, FUN_00027378 obj-from-handle).
 * TXM objects are byte-addressed opaque handles (Ghidra `long`), so object
 * offsets below are byte offsets and fields are dereferenced via casts. */
typedef uint64_t txm_obj_t;
typedef struct { uint64_t lo, hi; } txm_u128_t;extern int txm_lock_acquire(txm_obj_t obj, int arg1, int arg2);   /* FUN_00027128 */
extern void txm_lock_release(txm_obj_t obj, int arg1);             /* FUN_00027218 */
extern txm_obj_t txm_obj_alloc(void);                              /* FUN_00027448 */
extern void txm_obj_ref(txm_obj_t *obj, int count, int flags);     /* FUN_00027720 */
extern txm_obj_t txm_obj_from_handle(uint64_t handle);             /* FUN_00027378 */

/* BOOT-args / debug / profile bootstrap state (DAT_000107e0 etc.). */
extern uint64_t txm_boot_args;                                        /* DAT_000107e0 */
extern uint64_t txm_boot_state;                                       /* DAT_000104f2 */
extern uint64_t txm_debug_state;                                      /* DAT_000104e9 */
extern uint64_t txm_page_state;                                       /* DAT_0001074e */

/* Packed TXM status word helpers. A status is a 32-bit value where a nonzero
 * byte-1 selects an error class (0x20=..., 0x21=...); 0 means success. */
#define TXM_STATUS_CLASS(s) ((uint32_t)((s) >> 8) & 0xff)
#define TXM_STATUS_ERROR    (4u)

/* SCVerifySignature for developer authorization (FUN_00023c50). */
extern int txm_scverify_signature(uint64_t sig, uint64_t profile,
                                  uint64_t arg3);                    /* FUN_00023c50 */

/* Boot-profile loaders (FUN_00031fa0 / FUN_00031fcc). */
extern uint64_t txm_profile_load_raw(uint64_t profile_arg,
                                     uint64_t *profile_out);         /* FUN_00031fa0 */
extern uint64_t txm_profile_load_alt(uint64_t profile_arg,
                                     uint64_t *profile_out);         /* FUN_00031fcc */

/* Profile parse/validate (FUN_00031b70 / FUN_00031cb0 / FUN_00031e34). */
extern uint64_t txm_profile_parse(uint64_t *ctx, txm_obj_t obj,
                                  uint64_t src);                     /* FUN_00031b70 */
extern uint64_t txm_profile_init(txm_obj_t obj);                     /* FUN_00031cb0 */
extern uint64_t txm_profile_validate_data(txm_obj_t obj, uint64_t arg); /* FUN_00031e34 */

/* Region associate / disassociate (FUN_0003611c / FUN_000361a0). */
extern uint64_t txm_region_parse(txm_obj_t obj, txm_obj_t other);    /* FUN_0003611c */
extern uint64_t txm_region_lookup(txm_obj_t obj, uint64_t *out);     /* FUN_000361a0 */

/* Buffer-range helpers (FUN_0002c5a4 / FUN_0002c76c). */
extern void txm_buf_begin(uint64_t *out, const void *in,
                          uint64_t a, uint64_t b);                   /* FUN_0002c5a4 */
extern void txm_buf_end(uint64_t *buf, uint64_t tag);                /* FUN_0002c76c */

/* ------------------------------------------------------------------ */
/* Globals referenced by this region (addresses from Ghidra) */
/* ------------------------------------------------------------------ */
extern uint64_t txm_canary;               /* DAT_00006cf0 stack canary */
extern uint64_t txm_context_table;        /* per-CPU TXM context */
extern uint64_t txm_association_table;    /* 0x10000 boot profile/UUID table */
extern uint64_t txm_trust_cache_array;    /* DAT_00010590 TC array root */
extern uint64_t txm_debug_mode;           /* DAT_00070fa8 debug-mode state */
extern uint64_t txm_code_limits;          /* DAT_00071034 code-limits state */

/* FUN_000298ec / FUN_00029730 / FUN_00029a3c panic variants. */
#define txm_panic_msg(c)        txm_panic(c)
#define txm_panic_assert(c)     txm_panic(c)

/* BUFFER / RANGE / CONTEXT helpers (small wrappers over TXM runtime).
 * These abstract the TXM object layout so bodies stay English-first. */
extern uint64_t txm_link_limit;                       /* DAT_000107f0 */
extern uint64_t txm_profile_ctx;                      /* DAT_00010678 */
extern uint64_t profile_region;                       /* scratch region tag */
extern int txm_entry_init_is_matched(uint64_t profile); /* association-match flag */
extern void LOAcquire(void);                          /* atomic refcount lock */
extern void LORelease(void);                          /* atomic refcount unlock */

static inline uint64_t txm_status_pack(uint64_t s)
{
	/* Spread a 32-bit status into the 64-bit TXM status word:
	 * [0:8]=byte0, [32:40]=byte0, [40:48]=byte1, [48:64]=bytes2-3. */
	return ((s & 0xff) << 0x20) | ((s >> 8 & 0xff) << 0x28) | ((s >> 0x10) << 0x30);
}

static inline void txm_profile_set_range(txm_obj_t obj, uint64_t a, uint64_t b, uint64_t c)
{
	*(uint64_t *)(obj + 0)      = a;
	*(uint64_t *)(obj + 0x8)    = b;
	*(uint64_t *)(obj + 0x10)   = c;
}

static inline void txm_range_get(txm_obj_t obj, uint64_t *size, uint64_t *addr)
{
	*size = *(uint64_t *)(obj + 0x8);
	*addr = *(uint64_t *)(obj + 0x0);
}

static inline void txm_obj_teardown(txm_obj_t *obj)
{
	txm_obj_ref(obj, 1, 0);
}

/* ------------------------------------------------------------------ */
/* TXM interval red-black tree (code-region / association tracking).
 * Node layout (byte offsets): +0x28 key(start), +0x30 end, +0x38 left,
 * +0x40 right, +0x48 parent-with-color(bit0=red). Each node is 0x50 bytes.
 * The 0x50-wraparound guards throughout are pointer-overflow panics (0x19).
 * FUN_00020ed4 = link/rotate helper; FUN_00020f48 = insert-fixup;
 * FUN_00021434 = erase; FUN_00021bd8 = erase-node; FUN_00021ddc = insert. */
typedef uint64_t txm_rb_node_t;
#define RB_KEY(n)   (*(uint64_t *)((n) + 0x28))
#define RB_END(n)   (*(uint64_t *)((n) + 0x30))
#define RB_LEFT(n)  (*(uint64_t *)((n) + 0x38))
#define RB_RIGHT(n) (*(uint64_t *)((n) + 0x40))
#define RB_PAR(n)   (*(uint64_t *)((n) + 0x48))   /* low bit = red */
#define RB_NEXT(n)  ((n) + 0x50)
#define RB_IS_RED(n)  ((RB_PAR(n) & 1) != 0)
#define RB_SET_RED(n)    do { RB_PAR(n) = (RB_PAR(n) & ~1ULL) | 1; } while (0)
#define RB_SET_BLACK(n)  do { RB_PAR(n) &= ~1ULL; } while (0)
#define RB_COPY_COLOR(dst, src) \
	do { RB_PAR(dst) = (RB_PAR(dst) & ~1ULL) | (RB_PAR(src) & 1); } while (0)

/* ASID table / allocation / page-state globals. */
extern uint64_t txm_asid_table;              /* DAT_000104f8 */
extern uint64_t txm_asid_count;              /* DAT_000104f4 */
extern uint64_t txm_page_state_hi;           /* DAT_000104ea */
extern void txm_alloc_zone(uint64_t *out, uint64_t size, uint32_t tag);  /* FUN_000269b4 */
extern uint64_t base_size;                   /* allocated-size output */
extern uint64_t txm_boot_page_state;         /* DAT_000107f4 */

/* FUN_0002c908 region-type query; FUN_00021f08 / FUN_00021f64 range-node
 * helpers; FUN_00022a38 entitlement check; FUN_000221a8 object lookup. */
extern int  txm_region_type(uint64_t a, uint64_t b);                /* FUN_0002c908 */
extern txm_obj_t txm_slot_lookup(uint32_t id, uint64_t b, uint64_t c); /* FUN_000221a8 */
extern txm_rb_node_t txm_rb_find_overlap(txm_obj_t root_slot, uint64_t start, uint64_t end); /* FUN_00021f08 */
extern uint64_t txm_rb_node_to_obj(txm_rb_node_t n, uint64_t *out, uint64_t flag); /* FUN_00021f64 */
extern int txm_entitlement_check(txm_obj_t obj, uint64_t key, uint64_t flag); /* FUN_00022a38 */
extern void txm_ce_dict_init(txm_obj_t obj, uint64_t *out, uint64_t a, uint64_t b); /* FUN_00036480 */
extern uint64_t txm_ce_dict_size(uint64_t d1, uint64_t d2, uint32_t *out); /* FUN_0003407c */
extern uint64_t txm_ce_get_indexed(uint64_t d1, uint64_t d2, uint64_t idx, uint64_t va); /* FUN_00034204 */
extern void txm_range_arm(uint64_t *out, uint64_t a, uint64_t b);   /* FUN_0002c9a4 */

/* Slot-table accessors (FUN_00022050 / 000220ec / 0002214c). */
extern uint64_t txm_slot_table_base(uint16_t *desc, uint32_t expected); /* FUN_00022050 */
extern uint64_t txm_slot_reserve(uint32_t slot);                    /* FUN_000220ec */
extern uint64_t txm_slot_release(uint32_t slot);                    /* FUN_0002214c */
extern uint64_t txm_slot_create(uint16_t id, uint64_t b, uint64_t *out); /* FUN_00022274 */
extern uint64_t txm_slot_destroy(txm_obj_t obj);                    /* FUN_00022348 */
extern uint64_t txm_obj_new(void);                                  /* FUN_000281ec */
extern uint64_t txm_region_new(void);                               /* FUN_00027d78 */

/* Object teardown / release / current-obj / node-finalize helpers. */
extern uint64_t txm_obj_get_current(void);                          /* FUN_0002811c */
extern void txm_obj_teardown2(txm_obj_t *obj);                      /* FUN_000284a0 */
extern void txm_obj_release(txm_obj_t *obj);                        /* FUN_00027ab0 */
extern void txm_node_finalize(txm_obj_t *node);                     /* FUN_00027f44 */
extern void txm_slot_release_teardown(txm_obj_t *obj);              /* FUN_000283b8 */
extern void txm_stack_guard_check(void);                            /* FUN_0002f13c-ish */
extern uint64_t txm_profile_assoc_check(uint64_t handle, uint8_t b); /* FUN_00035178 */
extern uint64_t txm_profile_handle;                                 /* DAT_000107d8 */
extern uint64_t txm_region_slot_table;                              /* &DAT_000706c0 */

/* Region-association / entitlement / code-execution helpers. */
extern uint64_t txm_context_id_get(void);                           /* FUN_0002c834 */
extern void txm_obj_ref_drop(txm_obj_t *obj, int a, int b);         /* FUN_00028028 */
extern uint64_t txm_ce_get_entitlement(txm_obj_t dict, uint64_t *out); /* FUN_00036724 */
extern uint64_t txm_ce_get_bool(txm_obj_t dict, uint64_t key);      /* FUN_00036770 */
extern uint64_t txm_ce_get_arg(txm_obj_t dict, uint64_t key, uint64_t arg); /* FUN_000367c8 */
extern uint64_t txm_amfi_can_exec_cdhash(txm_obj_t d1, txm_obj_t d2); /* FUN_00036d44 */
extern uint64_t txm_verify_cdhash(uint32_t packed);                 /* FUN_000230fc */
extern uint64_t txm_region_authorize(uint64_t flag);                /* FUN_00023050 */
extern uint8_t txm_security_ok(uint64_t id);                        /* FUN_00023cc4 */
extern void txm_ce_parse_header(txm_obj_t dict, uint64_t dict2, uint64_t *a, uint64_t *b, uint64_t *c); /* FUN_00033c9c */
extern void txm_ce_get_info(txm_obj_t dict, uint64_t *a);           /* FUN_00033b88 */
extern void txm_ce_get_len(txm_obj_t dict, uint64_t *a);            /* FUN_00033b14 */
extern void txm_ce_field(txm_obj_t d, uint8_t *flag);               /* FUN_000361e0 */
extern void txm_ce_bind(txm_obj_t d, uint64_t *a);                  /* FUN_000361f8 */

/* Code-signing policy / secure-channel / profile helpers. */
extern uint64_t txm_profile_authorize(uint64_t handle, uint64_t flag); /* FUN_000350e8 */
extern uint8_t txm_exec_probe(void);                              /* FUN_00023fac */
extern uint64_t txm_platform_feature(void);                         /* FUN_0002a354 */
extern uint64_t txm_platform_flag(void);                            /* FUN_0002a434 */
extern int  txm_sep_present(void);                                  /* FUN_00029f28 */
extern uint64_t txm_setup_shared_page(void);                        /* FUN_0002f88c */
extern void txm_sc_bootstrap_a(void);                               /* FUN_00023840 */
extern void txm_sc_bootstrap_b(int mode);                           /* FUN_00023878 */
extern void txm_sc_bootstrap_c(void);                               /* FUN_000238ec */

/* Secure-channel / secure-boot globals. */
extern uint64_t txm_sc_page_base;      /* DAT_00010518 */
extern uint64_t txm_sc_page_size;      /* DAT_00010520 */
extern uint64_t txm_sc_page_extra;     /* DAT_00010528 */
extern uint8_t  txm_sc_ready;          /* DAT_00071030 */
extern uint8_t  txm_sc_cap;            /* DAT_00071031 */
extern uint8_t  txm_sc_flag;           /* DAT_00071032 */
extern uint8_t  txm_sc_sep;            /* DAT_00071038 */
extern uint8_t  txm_boot_flag;         /* DAT_000104f0 */
extern uint8_t  txm_page_er_flag;      /* DAT_000107f5 */
extern uint8_t  txm_ent_lo_flag;       /* DAT_000104ed */
extern uint64_t page_size_word;        /* alloc size out */
extern uint64_t page_extra_word;       /* alloc extra out */

/* Secure-channel / developer-mode helpers (FUN_0002f5a0/5e0/620/660/6a0/368/454). */
extern uint64_t txm_sc_step(int arg);  /* FUN_0002f5a0 */
extern uint64_t txm_sc_config(uint64_t arg); /* FUN_0002f5e0 */
extern uint64_t txm_sc_devmode(int on);  /* FUN_0002f620 */
extern uint64_t txm_sc_handle(int is_reset); /* FUN_0002f660 */
extern uint64_t txm_sc_ent(int ent);    /* FUN_0002f6a0 */
extern uint64_t txm_scrd_read(uint64_t *out); /* FUN_0002f368 */
extern uint64_t txm_scrd_context(uint64_t *out); /* FUN_0002f454 */

/* Secure-channel state globals. */
extern uint8_t  txm_sc_lockdown;       /* DAT_00071033 */
extern uint64_t txm_scrd;              /* DAT_0007103c */
extern uint8_t  txm_lockdown_mode;     /* DAT_00071035 */
extern uint8_t  txm_demo_mode;         /* DAT_00071036 */
extern uint8_t  txm_dev_mode_flag;     /* DAT_000107f6 */

/* Secure-channel verify/enter/exit + build-info helpers. */
extern uint64_t txm_sc_verify(uint64_t a, uint64_t *b, uint64_t c);  /* FUN_0002f1b0 */
extern uint64_t txm_sc_enter_impl(uint64_t *ab);                     /* FUN_0002f220 */
extern uint64_t txm_sc_exit_impl(uint64_t a, uint8_t *flag);         /* FUN_0002f3c8 */
extern void txm_early_boot(uint64_t a);                              /* FUN_0002940c */
extern void txm_sys_write(uint64_t slot, const void *data, uint64_t n); /* FUN_0004f2dc */
extern uint64_t txm_build_version(void);                             /* FUN_00029714 */
extern void txm_return_exit(uint64_t ctx);                           /* FUN_0002ab70 */

/* Build-info / lockdown globals. */
extern uint64_t txm_allowed_id_list;     /* DAT_000100b8 */
extern uint64_t txm_match_flag;          /* DAT_000107f8 */
extern uint64_t txm_boot_e8;             /* DAT_000104e8 */
extern uint64_t txm_ctx_return;          /* DAT_00010588 */
extern uint8_t  txm_build_cfg0;          /* DAT_00070ecc */
extern uint8_t  txm_build_cfg1;          /* DAT_00070ecd */
extern uint8_t  txm_build_cfg2;          /* DAT_00070ece */
extern uint8_t  txm_lockdown_entered;    /* DAT_00010661 */
extern uint8_t  txm_lockdown_flag;       /* DAT_00010667 */
extern uint8_t  txm_lockdown_armed;      /* DAT_000107f7 */
extern uint64_t build_variant_id;        /* &DAT_0002d03c */
extern uint64_t platform_id;             /* &DAT_0002ced0 */

/* Policy / profile / trust-cache helpers. */
extern uint64_t txm_platform_code_only(void);                       /* FUN_0002a004 */
extern uint64_t txm_setup_extra(void);                              /* FUN_0002a894 */
extern uint64_t txm_ce_legacy_init(uint64_t ctx, int type, uint64_t *a, uint64_t *b, uint64_t max); /* FUN_00031280 */
extern uint64_t txm_feature_byte(void);                             /* FUN_0002a630 */
extern uint64_t txm_alloc_zone2(void);                              /* FUN_000278e4 */
extern int  txm_range_valid(uint64_t p);                            /* FUN_00028594 */
extern uint64_t txm_range_pull(uint64_t p, uint64_t *out, uint64_t *flag); /* FUN_000285d0 */
extern uint64_t txm_dict_parse(uint64_t ctx, uint64_t *dst, uint64_t a, uint64_t b); /* FUN_00035acc */
extern uint64_t txm_dict_finish(txm_obj_t d, uint64_t arg);         /* FUN_00036078 */
extern void txm_buf_err(uint64_t *buf, uint64_t tag);               /* FUN_00028e20 */
extern void txm_obj_ref2(txm_obj_t *obj, int a, int b);             /* FUN_00027bb4 */
extern int  txm_dict_empty(txm_obj_t d, uint64_t *out);             /* FUN_000362c4 */
extern uint64_t txm_dict_get_ent(txm_obj_t d, uint64_t *out);       /* FUN_000362ec */
extern uint64_t txm_ent_validate(txm_obj_t d, uint64_t *out);       /* FUN_00035bf0 */
extern uint64_t txm_ent_validate2(txm_obj_t d, uint64_t flag);      /* FUN_00035df4 */
extern uint64_t txm_ent_validate3(txm_obj_t d);                     /* FUN_00035f08 */
extern int  txm_ent_check(uint64_t x);                              /* FUN_0005eb18 */
extern int  txm_ent_match(uint64_t x);                              /* FUN_0005ed14 */
extern uint64_t txm_tc_field(uint64_t dict, uint32_t tag, uint64_t *out, int *n); /* FUN_0003653c */
extern uint64_t txm_tc_build(uint64_t dict, char *a, char *b);      /* FUN_00036824 */
extern uint64_t txm_tc_count(uint64_t dict, int *n);                /* FUN_00036424 */
extern uint64_t txm_dict_get_str(txm_obj_t d, uint64_t *out);       /* FUN_00033b88 */

/* Policy / trust-cache globals. */
extern uint8_t  txm_policy_sel;         /* DAT_00010800 */
extern uint8_t  txm_probe_flag;         /* DAT_00010678+6 profile byte6 */
extern uint8_t  txm_feature_flag;       /* DAT_0007103c-ish */

/* FUN_0002081c page-enforcement comm-page / debug policy helper. */
extern uint64_t txm_page_policy_comm(void);                         /* FUN_0002081c */

/* External module loader / TC parse externs. */
extern void txm_tc_parse_module(uint64_t profile);                  /* FUN_00031e34-ish */
extern uint64_t txm_boot_page_state;                                /* DAT_000107f4 */

/* FUN_00020000 @ 0x00020000   (est. txm_entry_init / __text)
 * Ghidra: void __text(undefined8 profile_arg)
 * TXM boot entry. Loads the active TXM profile (FUN_00031fe8), extracts its
 * UUID as a string (FUN_00060088), parses that string into a 16-byte UUID
 * (FUN_0005f7ec), and looks the UUID up against the boot profile / association
 * table at 0x10000 (16-byte UUID entries, stepping 8 bytes up to 0xb0) via a
 * compare helper. A missing/unparsable/odd-length UUID panics (codes 0x7d5,
 * 0x7f2, 0x80f); a non-matching profile sets the association-match flag false
 * for later policy decisions. A malformed hex character while decoding the UUID
 * string panics with a buffer-overrun guard (0x19).
 * Confidence: high (matches the documented __text entry; profile-UUID panics)
 * Notes: stack canary DAT_00006cf0 checked on return (mismatch -> stack-guard
 *   panic FUN_0002f13c). UUID table base 0x10000, stride 8, cap 0xb0.
 */
void txm_entry_init(uint64_t profile_arg)
{
	uint64_t profile;               /* loaded profile descriptor (local_68) */
	char uuid_str[0x24];            /* ASCII UUID string from the profile   */
	char parsed_uuid[0x24];         /* UUID string being decoded            */
	char decoded_uuid[0x24];        /* binary-decoded UUID                  */
	uint64_t result, idx, off;
	int matched = 0;
	uint64_t guard = txm_canary;    /* DAT_00006cf0 */

	for (idx = 0; idx < 0x24; idx++) {
		uuid_str[idx] = 0;
		parsed_uuid[idx] = 0;
		decoded_uuid[idx] = 0;
	}

	/* Load the TXM profile; the top byte of the status is a failure code. */
	result = txm_profile_load(profile_arg, &profile);
	if (((result >> 8) & 0xff) != 0) {
		txm_panic(0xf1 | (result & 0xffff0000) | (result & 0xff) |
		          (((result >> 8) & 0xff) << 8));
	}

	/* Extract the profile's UUID string. */
	if (txm_profile_uuid_get(profile, 2000, uuid_str) != 0) {
		txm_panic(0x7d5);            /* "profile does not have a UUID" */
	}

	/* Parse the UUID string into parsed_uuid (length returned via uuid_len).
	 * On success the length must be the canonical 36 ("standard length"). */
	if (txm_uuid_parse(uuid_str, parsed_uuid, &uuid_len) == 0 &&
	    uuid_len == 0x24) {
		/* Decode each byte of the parsed UUID to its hex nibble value. */
		for (idx = 0; idx < 0x24; idx++) {
			decoded_uuid[idx] = (char)txm_hex_nibble((uint8_t)parsed_uuid[idx]);
		}
		/* Look the decoded UUID up in the boot association table at 0x10000
		 * (16-byte UUID entries; the compare walks them in 8-byte steps). */
		for (off = 0; ; off += 8) {
			if (txm_uuid_compare(decoded_uuid,
			                     *(uint64_t *)(0x10000 + off)) == 0) {
				matched = 1;         /* association found */
				break;
			}
			if (off == 0xb0) {
				break;               /* table exhausted, no match */
			}
		}
	} else if (txm_uuid_parse(uuid_str, parsed_uuid, &uuid_len) != 0) {
		txm_panic(0x7f2);            /* "profile UUID is not a string" */
	} else {
		txm_panic(0x80f);            /* "profile does not have a standard
		                                length UUID" */
	}

	if (txm_canary != guard) {
		txm_stack_guard_fail(matched);
	}
}

/* FUN_00020178 @ 0x00020178   (est. txm_boot_signature_authorize)
 * Ghidra: byte FUN_00020178(undefined8 boot_profile, undefined8 signature)
 * Boot-time authorization gate. Only when the boot state (DAT_000104f2) is 1
 * or 2 does it consult the profile: it loads the boot profile, and if the
 * profile requests developer/debug authorization (status byte bit 2) and the
 * boot profile did NOT match the association table (txm_entry_init's match
 * flag), it loads the alternate profile and SC-verifies `signature` against it
 * (FUN_00023c50). A failed verify denies (returns 0); any successful path
 * returns 1. This is the developer-auth boundary for allowing a non-matching
 * boot profile.
 * Confidence: medium (roles inferred from callees + boot-state gate)
 * Notes: DAT_000104e9 debug flag must be set to panic on the verify path.
 */
uint8_t txm_boot_signature_authorize(uint64_t boot_profile, uint64_t signature)
{
	uint64_t status, prof;
	uint64_t boot_state = txm_boot_state;          /* DAT_000104f2 */
	uint8_t allow = 1;
	uint64_t flags;

	if (boot_state - 1 < 2) {                      /* state 1 or 2 */
		status = txm_profile_load_raw(boot_profile, &flags);
		if (TXM_STATUS_CLASS(status) != 0) {
			txm_panic(status);
		}
		/* Profile asks for debug authorization (bit 2) and the boot profile
		 * was not an association-table match. */
		if (((flags >> 2) & 1) && (txm_entry_init_is_matched(boot_profile) & 1) == 0) {
			status = txm_profile_load_alt(boot_profile, &prof);
			if (TXM_STATUS_CLASS(status) != 0) {
				txm_panic(status);
			}
			if (txm_scverify_signature(signature, prof, 0) != 0) {
				if ((txm_debug_state & 1) == 0) {
					txm_panic(0x19);
				}
				allow = txm_page_state;            /* DAT_0001074e */
			}
		}
	}
	return allow & 1;
}

/* FUN_00020248 @ 0x00020248   (est. txm_profile_load_from_buffer)
 * Ghidra: ulong FUN_00020248(undefined8 *buf, long *obj_out)
 * Allocates a TXM profile object, records the caller-supplied buffer range
 * {*buf, buf[1], buf[2]}, and parses the profile's entitlements/embedded
 * dictionaries (FUN_00031b70, falling back to FUN_00031cb0 on the not-loaded
 * class). On success the object is returned via *obj_out. Errors are packed
 * status words (0x20/0x21 classes panic 0xf1). Also bounds-checks the buffer
 * range (buf[1] < buf[2] panics).
 * Confidence: medium (roles inferred)
 * Notes: status-word packing; DAT_00010678 is the profile-context global.
 */
uint64_t txm_profile_load_from_buffer(uint64_t *buf, uint64_t *obj_out)
{
	uint64_t status;
	txm_obj_t obj = txm_obj_alloc();

	if (obj == 0) {
		return 7;
	}

	txm_lock_acquire(obj, 1, 0);

	/* Record the buffer range {start, size, end} into the profile's region. */
	txm_profile_set_range(obj, buf[0], buf[1], buf[2]);
	txm_buf_begin(&profile_region, buf, 0x29, 0x3b);

	if ((txm_debug_state & 1) == 0) {
		txm_panic(0x19);
	}
	if ((uint64_t)buf[1] < (uint64_t)buf[2]) {
		txm_panic(0x19);
	}

	status = txm_profile_parse(&txm_profile_ctx, obj + 0x18, buf[0]);
	if (TXM_STATUS_CLASS(status) != 0x30) {
		if (TXM_STATUS_CLASS(status) != 0) {
			txm_panic(status);
		}
		status = txm_profile_init(obj + 0x18);
		if (TXM_STATUS_CLASS(status) != 0) {
			txm_panic(status);
		}
	}

	txm_lock_release(obj, 1);

	if (TXM_STATUS_CLASS(status) == 0) {
		if (obj_out != NULL) {
			*obj_out = obj;
		}
	} else {
		/* Error path: re-arm the buffer end tag and drop a reference. */
		txm_profile_set_range(obj, buf[0], buf[1], buf[2]);
		txm_buf_end(&profile_region, 0x3b);
		txm_obj_ref(&obj, 3, 4);
	}

	return txm_status_pack(status);
}

/* FUN_00020400 @ 0x00020400   (est. txm_profile_validate)
 * Ghidra: ulong FUN_00020400(long obj, undefined8 arg)
 * Validates a profile object's entitlements/embedded data against `arg`:
 * acquire, run the per-profile validator (FUN_00031e34) over obj+0x18,
 * release, and return the packed status. 0x20/0x21 classes panic 0xf1.
 * Confidence: medium
 */
uint64_t txm_profile_validate(txm_obj_t obj, uint64_t arg)
{
	uint64_t status, packed;
	uint32_t cls;

	txm_lock_acquire(obj, 1, 0);
	status = txm_profile_validate_data(obj + 0x18, arg);
	txm_lock_release(obj, 1);

	cls = TXM_STATUS_CLASS(status);
	if ((status & 0xff00) == 0) {
		packed = 0;
	} else {
		if (cls == 0x20) {
			txm_panic((uint32_t)status & 0xffff00ff | 0x2000);
		}
		if (cls == 0x21) {
			txm_panic(((uint32_t)status & 0xffff0000) | ((uint32_t)status & 0xff) | 0x2100);
		}
		packed = 4;
	}
	return packed | ((status >> 0x10) << 0x30) |
	       (((status >> 8) & 0xff) << 0x28) | ((status & 0xff) << 0x20);
}

/* FUN_000204a8 @ 0x000204a8   (est. txm_code_region_validate)
 * Ghidra: undefined8 FUN_000204a8(long obj, ulong *range_out)
 * Validates a code-region buffer range and, when it is 16 KiB aligned and
 * non-empty, re-arms the buffer tag, drops a reference, and returns
 * {size, addr} in *range_out. Refuses (returns 0xb) while the object is busy
 * (*(obj+0x14)!=0). Misaligned/overflowing ranges panic (0x40-0x43, 0xc0).
 * Confidence: medium
 */
uint64_t txm_code_region_validate(txm_obj_t obj, uint64_t *range_out)
{
	uint64_t size, addr, aligned_end;
	uint64_t range_triplet[3];

	txm_lock_acquire(obj, 1, 0);
	if (*(int *)(obj + 0x14) != 0) {
		txm_lock_release(obj, 1);
		return 0xb;                              /* busy */
	}

	txm_range_get(obj + 0x18, &size, &addr);
	aligned_end = (addr + 0x3fff) & ~0x3fffUL;

	if (aligned_end < addr) {
		txm_panic(0x43);
	} else if (size == 0) {
		txm_panic(0x40);
	} else if (aligned_end == 0) {
		txm_panic(0x41);
	} else if (size + aligned_end < aligned_end) {   /* CARRY8 overflow */
		txm_panic(0x42);
	} else if ((size & 0x3fff) == 0) {
		txm_obj_ref(&obj, 2, 5);
		txm_lock_release(obj, 1);
		txm_obj_teardown(&obj);
		txm_buf_end(range_triplet, 0x3b);
		if (range_out == NULL) {
			return 0;
		}
		range_out[1] = addr;
		range_out[0] = size;
		return 0;
	} else {
		txm_panic(0xc0);
	}
	return 0;                                     /* unreachable (panic) */
}

/* FUN_000205c0 @ 0x000205c0   (est. txm_region_associate)
 * Ghidra: ulong FUN_000205c0(long obj, long other)
 * Associates two TXM objects (a code region with its owning profile): acquires
 * both, parses/links them (FUN_0003611c), increments the other's link count
 * (*+0x14), panics 0x4e on overflow past DAT_000107f0, then releases both.
 * Confidence: medium
 */
uint64_t txm_region_associate(txm_obj_t obj, txm_obj_t other)
{
	uint64_t status, packed;
	uint32_t cls;
	uint32_t count;

	txm_lock_acquire(obj, 1, 0);
	txm_lock_acquire(other, 0, 0);

	status = txm_region_parse(obj + 0x28, other + 0x18);
	cls = TXM_STATUS_CLASS(status);
	if (cls == 0) {
		count = *(uint32_t *)(other + 0x14);
		*(uint32_t *)(other + 0x14) = count + 1;
		if (count >= ~txm_link_limit) {           /* DAT_000107f0 */
			txm_panic(0x4e, 0);
		}
	}

	txm_lock_release(other, 0);
	txm_lock_release(obj, 1);

	if (cls != 0) {
		if (cls == 0x20) {
			txm_panic(((uint32_t)status & 0xffff00ff) | 0x2000);
		} else {
			if (cls != 0x21) {
				packed = 4;
				goto out;
			}
			txm_panic(((uint32_t)status & 0xffff00ff) | 0x2100);
		}
	}
	packed = 0;
out:
	return packed | ((status >> 0x10) << 0x30) |
	       ((uint64_t)(cls & 0xff) << 0x28) | ((status & 0xff) << 0x20);
}

/* FUN_000206dc @ 0x000206dc   (est. txm_region_disassociate)
 * Ghidra: ulong FUN_000206dc(long obj)
 * Disassociates the object from its linked region: acquire, look up the linked
 * object (FUN_000361a0), release, then decrement the linked object's link count
 * under an atomic lock, panicking 0x4f on underflow (count would go negative).
 * Confidence: medium
 * Notes: LOAcquire/LORelease are the atomic refcount lock ops.
 */
uint64_t txm_region_disassociate(txm_obj_t obj)
{
	uint64_t status, packed;
	uint32_t cls;
	uint32_t count;
	txm_obj_t linked = 0;
	int i;

	txm_lock_acquire(obj, 1, 0);
	status = txm_region_lookup(obj + 0x28, &linked);
	txm_lock_release(obj, 1);

	cls = TXM_STATUS_CLASS(status);
	if ((status & 0xff00) == 0) {
		txm_obj_t l = txm_obj_from_handle(linked - 0x18);
		txm_lock_acquire(l, 0, 0);
		LOAcquire();
		i = *(int *)(l + 0x14);
		*(int *)(l + 0x14) = i - 1;
		LORelease();
		if (i == 0) {
			txm_panic(0x4f, 0);                   /* link underflow */
		}
		txm_lock_release(l, 0);
		status = 0;
	} else {
		if (cls == 0x20) {
			txm_panic(((uint32_t)status & 0xffff00ff) | 0x2000);
		}
		if (cls == 0x21) {
			txm_panic(((uint32_t)status & 0xffff0000) | ((uint32_t)status & 0xff) | 0x2100);
		}
		status = ((status >> 0x10) << 0x30) |
		         ((uint64_t)(cls & 0xff) << 0x28) | ((status & 0xff) << 0x20) | 4;
	}
	return status;
}

/* FUN_000207e4 @ 0x000207e4   (est. txm_boot_args_init)
 * Ghidra: void FUN_000207e4(long arg)
 * Records the boot-args string pointer from the boot profile (+0x58) into the
 * single-slot DAT_000107e0 global. Refuses a second init ("attempted to
 * initialize boot-args again", panic 0xb8f).
 * Confidence: high (matches string 0xb8f "attempted to initialize boot-args
 *   again")
 */
void txm_boot_args_init(uint64_t profile)
{
	if (txm_boot_args == 0) {
		txm_boot_args = *(uint64_t *)(profile + 0x58);
		return;
	}
	txm_panic(0xb8f);
}

/* FUN_0002081c @ 0x0002081c   (est. txm_comm_page_allowed)
 * Ghidra: undefined8 FUN_0002081c(void)
 * Comm-page executable-mapping policy. Returns 0 (allow) when the current
 * region type is the comm page (0x1f) AND the profile (+0x50) permits it;
 * returns 0x23 if the profile forbids it, 0x94 if the region is not the comm
 * page. Panics 0x19 when the debug state (DAT_000104e9) is not set, and 0x95
 * when DAT_000104ea is set. Logs "allowing executable comm-page mapping".
 * Confidence: high (matches string 0xbb7 "allowing executable comm-page
 *   mapping")
 */
uint64_t txm_comm_page_allowed(void)
{
	uint64_t ctx = txm_profile_ctx;               /* DAT_00010678 */
	uint64_t err;

	if ((txm_debug_state & 1) == 0) {
		txm_panic(0x19);
	}

	if (txm_region_type(0, 0) == 0x1f) {          /* comm page */
		if ((*(uint8_t *)(ctx + 0x50) & 1) == 0) {
			return 0x23;                          /* profile forbids comm page */
		}
		if (txm_page_state_hi & 1) {              /* DAT_000104ea */
			txm_panic(0x95);
		}
		txm_log("allowing executable comm-page mapping");   /* 0xbb7 */
		return 0;
	}
	return 0x94;                                  /* not a comm-page region */
}

/* FUN_0002089c @ 0x0002089c   (est. txm_page_enforcement)
 * Ghidra: ulong FUN_0002089c(uint prot, uint flags, ... region, ulong *count)
 * The executable-mapping / page-enforcement authority (THE core of TXM's
 * code-signing policy). Given a code address `param_1`, protection bits
 * `param_2`, region base/end `param_3/param_4` and a page-count pointer
 * `param_5`, it decides whether an executable (or writable-debug) mapping is
 * permitted:
 *  - comm page (region type 0x1f): delegate to txm_comm_page_allowed.
 *  - zero address: allowed unless flags bit 1-2 (0x1e denied).
 *  - region type 0x10 (mapped object): the object at +0x50 must cover the
 *    requested address [ +0x28, +0x30 ).
 *  - region type 0xf (executable): requires the association object's code
 *    limit to cover the range; writable-debug mappings need
 *    com.apple.private.cs.debugger (0xc79) or the region's debug flag;
 *    unassociated/executable-only mappings are rejected (0x1e) unless the
 *    association chain validates.
 *  - region type 0xe (association): follows the linked object; verifies
 *    page-entry count against the DER dictionary, rejecting if the count
 *    overflows (panic 0x93) or the range exceeds limits (panic 0x92).
 * The result packs {count(32), low(16), error(16)}; error 0x1e/0x21/0x22
 * deny, others are logged via "page enforcement failed" (0xbdd).
 * Confidence: high (page-enforcement core; strings 0xbdd/0xc41/0xc1d/0xc97)
 * Notes: writes derived page-entry counts when validating association chains;
 *   gate DAT_000107f4 controls whether non-error results are reported.
 */
uint64_t txm_page_enforcement(uint32_t prot, uint32_t flags,
                              uint64_t region_base, uint64_t region_end,
                              uint64_t *count)
{
	int rtype = txm_region_type(region_base, region_end);
	uint64_t err = 0, hi, lo, range_word;
	txm_obj_t obj, assoc;
	txm_rb_node_t rn;
	uint32_t u16 = 0, pagecnt = 0;

	if (rtype == 0x1f) {                          /* comm page */
		return txm_comm_page_allowed();
	}

	if ((prot & 0xffff0000) == 0 && (prot & 0xffff) == 0) {
		/* Zero code address: only writable-debug flags (bit 1-2) deny. */
		err = (flags & 6) ? 0x1e : 0;
		return err;
	}

	obj = txm_slot_lookup(prot, 0xffff, 0);

	if (rtype == 0x10) {                          /* mapped object */
		assoc = *(txm_obj_t *)(obj + 0x50);
		if (assoc == 0) {
			err = 0x21;                           /* no association */
		} else if (*(uint64_t *)(assoc + 0x28) <= *count &&
		           *count < *(uint64_t *)(assoc + 0x30)) {
			err = 0;                              /* covered by association */
		} else {
			err = 0x22;                           /* outside association */
		}
		goto enforce_done;
	}

	if (rtype == 0xf) {                           /* executable region */
		rn = txm_rb_find_overlap(obj + 0x28, region_base, region_base + 0x4000);
		if ((flags >> 2) & 1) {                   /* executable only */
			if (rn != 0 && (*(int8_t *)(rn + 0x12) < 0)) {
				err = 0;
			} else {
				txm_log("disallowed executable debug mapping");  /* 0xc1d */
				err = 0x1e;
			}
		} else {
			if (((flags & 0xff) >> 1) & 1) {      /* writable debug */
				if ((txm_code_limits & 1) == 0) {
					txm_log("disallowed writable debug mapping due to developer mode");  /* 0xc41 */
					err = 0x1c;
				} else {
					err = txm_entitlement_check(obj, 0xc79, 0);  /* cs.debugger */
					if ((err & 1) == 0 && (*(uint8_t *)(obj + 0x30) & 1) == 0) {
						txm_log("disallowed writable debug mapping due to address space");  /* 0xc97 */
						err = 0x1e;
					} else {
						err = 0;
					}
				}
			} else {
				err = 0;
			}
		}
		goto enforce_done;
	}

	if (rtype != 0xe) {
		txm_panic(0x90);                          /* unknown region type */
	}

	/* Association region (0xe): follow the linked code object. */
	{
		uint64_t range_word, range_end_word, dict_out = 0, dict = 0, dict2 = 0;
		uint32_t dictsize = 0;
		txm_rb_node_t rn2;
		int self;

		if (*(uint16_t *)(obj + 0x24) == 1 || *(uint64_t *)(obj + 0x48) == 0) {
			rn = obj;
			self = 1;
		} else {
			rn2 = txm_rb_find_overlap(obj + 0x28, region_base, region_base + 0x4000);
			if (rn2 == 0 || (*(uint8_t *)(rn2 + 0x12) & 0x7f) != 1) {
				rn = obj;
				self = 1;
			} else {
				obj = *(uint64_t *)(rn2 + 0x18);
				self = 0;
				txm_lock_acquire(obj, 0, 0);
			}
		}

		if (((flags >> 1) & 1) == 0) {
			err = 0;
		} else if ((((flags & 0xff) >> 2) & 1) == 0 ||
		           (*(uint8_t *)(obj + 0x18) & 1) != 0) {
			err = 0;
		} else {
			/* Debug mapping: validate the association chain's page-entry
			 * count against the embedded DER dictionary. */
			rn2 = txm_rb_find_overlap(obj + 0x28, region_base, region_base + 0x4000);
			if (rn2 == 0) {
				pagecnt = 0;
				err = 0x20;
			} else {
				uint64_t st = txm_rb_node_to_obj(rn2, &dict_out, 0);
				pagecnt = (uint32_t)(st >> 0x10);
				if ((st & 0xffff) == 0) {
					txm_ce_dict_init(dict_out + 0x28, &dict, 0, 0);
					txm_ce_dict_size(dict, dict2, &dictsize);
					if (0x4000 < dictsize) {
						txm_panic(0x91);
					}
					uint64_t base = *count - *(uint64_t *)(rn2 + 0x28);
					if (*(uint64_t *)(rn2 + 0x18) + base < base) {
						txm_panic(0x92);
					}
					u16 = dictsize ? (0x4000 / dictsize) : 0;
					hi = dictsize ? (*(uint64_t *)(rn2 + 0x18) + base) / dictsize : 0;
					if (~u16 <= hi) {
						txm_panic(0x93);
					}
					u16 += (uint32_t)hi;
					txm_range_arm(&range_word, region_base, region_end);
					uint64_t va = range_word;
					range_end_word = range_word + 0x4000;
					if (((range_word ^ range_end_word) & 0xffc0000000000000) != 0) {
						range_end_word = range_end_word & 0xffffffffffff | 0xc8a2000000000000;
					}
					if ((uint32_t)hi < u16) {
						uint64_t step = dictsize;
						do {
							uint64_t r = txm_ce_get_indexed(dict, dict2, hi, va);
							uint32_t cls = (uint32_t)((r & 0xffffffff) >> 8) & 0xff;
							if ((r & 0xff00) != 0) {
								if (cls == 0x20) txm_panic(((uint32_t)r & 0xffff00ff) | 0x2000);
								if (cls == 0x21) txm_panic(((uint32_t)r & 0xffff0000) | ((uint32_t)r & 0xff) | 0x2100);
								pagecnt = 0;
								err = 4;
								goto done;
							}
							pagecnt = cls;
							va += step;
							hi++;
						} while ((uint32_t)hi < u16);
						err = 0;
					} else {
						err = 0;
					}
				} else {
					pagecnt = 0;
					err = 0x1f;
				}
			}
		done:
			if (dict_out != 0) {
				txm_lock_release(dict_out, 0);
			}
		}
		if (!self) {
			txm_lock_release(obj, 0);
		}
	}

enforce_done:
	/* Common tail: gate whether the error/counts are reported. The result is
	 * suppressed unless this is a normal 0x1e denial, a success, or the
	 * boot page state (DAT_000107f4) is clear. */
	{
		uint64_t e = err & 0xffff;
		int report = !((e != 0x1e) && (e != 0) && txm_boot_page_state);
		uint64_t r_err = report ? e : 0;
		uint64_t r_u16 = report ? (uint64_t)(u16 & 0xffff) : 0;
		uint64_t r_cnt = report ? (uint64_t)pagecnt : 0;
		if (r_err) {
			txm_log("page enforcement failed ...");   /* 0xbdd */
		}
		return (r_cnt << 0x20) | (r_u16 << 0x10) | r_err;
	}
}

/* FUN_00020e24 @ 0x00020e24   (est. txm_asid_table_init)
 * Ghidra: void FUN_00020e24(long desc)
 * Initializes the ASID bitmap table: allocates 8 bytes per ASID (count
 * from desc+0xc, rounded up to 16K), stores the base (DAT_000104f8) and
 * count (DAT_000104f4). Refuses a second init ("attempted to initialize ASID
 * table again", panic 0xcce); a 0 count panics 0x13, an oversized count 0x14,
 * an allocation-size wrap 0x43.
 * Confidence: high (string 0xcce "attempted to initialize ASID table again")
 */
void txm_asid_table_init(uint64_t desc)
{
	uint32_t count = *(uint32_t *)(desc + 0xc);
	uint64_t size, base;

	if (txm_asid_table != 0) {
		txm_panic(0xcce);                         /* re-init */
	}
	if (count == 0) {
		txm_panic(0x13);
	}
	if (count < 0x10000) {
		size = (uint64_t)(count * 8 + 0x3fff) & 0xfc000;
		if ((uint64_t)count << 3 <= size) {
			txm_alloc_zone(&base, size, 0x2e);
			if ((uint64_t)count <= base_size >> 3) {
				txm_asid_table = base;            /* DAT_000104f8 */
				txm_asid_count = count;           /* DAT_000104f4 */
				return;
			}
			txm_panic(0x19);
		}
		txm_panic(0x43);
	}
	txm_panic(0x14);
}

/* FUN_00020ed4 @ 0x00020ed4   (est. txm_rb_link)
 * Ghidra: ulong FUN_00020ed4(long node, ulong parent)
 * Red-black tree link helper: sets `node`'s parent pointer (+0x48), folding
 * the color bit into the parent field. Used by every rotation/relink in the
 * interval tree. Panics 0x19 on pointer-wraparound of the node bounds.
 * Confidence: high (classic rbtree parent-link primitive)
 */
uint64_t txm_rb_link(txm_rb_node_t node, uint64_t parent)
{
	uint64_t old = RB_PAR(node);

	RB_PAR(node) = parent;
	if ((old & 1) == 0) {
		if (parent == 0) {
			return 0;                             /* node becomes root */
		}
	} else {
		if (parent == 0) {
			old = 0;
		} else {
			old = parent & ~1ULL;
		}
		if (old + 0x50 <= old) txm_panic(0x19);
		parent = old | 1;
		if (old + 0x51 <= parent) txm_panic(0x19);
		RB_PAR(node) = parent;
	}
	parent &= ~1ULL;
	if (parent < parent + 0x50) {
		return parent;
	}
	txm_panic(0x19);
}

/* FUN_00020f48 @ 0x00020f48   (est. txm_rb_insert_fixup)
 * Ghidra: void FUN_00020f48(ulong *root, ulong node)
 * Red-black tree insert-fixup (rebalance) over the interval tree rooted at
 * *root after inserting `node`. Standard RB rotations (left/right, uncle
 * color, recolor to root, root blackened) with the parent+color at +0x48 and
 * left/right at +0x38/+0x40. Panics 0x19 on any structural wrap.
 * Confidence: high (canonical RB-tree fixup)
 */
void txm_rb_insert_fixup(txm_rb_node_t *root, txm_rb_node_t node)
{
	txm_rb_node_t parent, gparent, uncle, tmp;

	while ((parent = RB_PAR(node), (parent & 1) != 0) &&
	       RB_PAR(parent & ~1ULL) != 0) {
		gparent = RB_PAR(parent & ~1ULL) & ~1ULL;
		if (parent & ~1ULL) {
			if ((parent & ~1ULL) == RB_LEFT(gparent)) {
				uncle = RB_RIGHT(gparent);
				if (RB_IS_RED(uncle)) {
					RB_SET_BLACK(parent & ~1ULL);
					RB_SET_BLACK(uncle);
					RB_SET_RED(gparent);
					node = gparent;
					continue;
				}
				if (node == RB_RIGHT(parent & ~1ULL)) {
					node = parent & ~1ULL;
					/* rotate-left at node */
					tmp = RB_RIGHT(node);
					RB_RIGHT(node) = RB_LEFT(tmp);
					if (RB_LEFT(tmp)) RB_PAR(RB_LEFT(tmp)) = node;
					RB_PAR(tmp) = RB_PAR(node);
					RB_PAR(node) = tmp;
					RB_LEFT(tmp) = node;
					if (RB_PAR(tmp) == 0) *root = tmp;
					else if (node == RB_LEFT(RB_PAR(tmp)))
						RB_LEFT(RB_PAR(tmp)) = tmp;
					else RB_RIGHT(RB_PAR(tmp)) = tmp;
					parent = node;
				}
				/* rotate-right at gparent */
				RB_SET_BLACK(parent & ~1ULL);
				RB_SET_RED(gparent);
				tmp = RB_LEFT(gparent);
				RB_LEFT(gparent) = RB_RIGHT(tmp);
				if (RB_RIGHT(tmp)) RB_PAR(RB_RIGHT(tmp)) = gparent;
				RB_PAR(tmp) = RB_PAR(gparent);
				RB_PAR(gparent) = tmp;
				RB_RIGHT(tmp) = gparent;
				if (RB_PAR(tmp) == 0) *root = tmp;
				else if (gparent == RB_LEFT(RB_PAR(tmp)))
					RB_LEFT(RB_PAR(tmp)) = tmp;
				else RB_RIGHT(RB_PAR(tmp)) = tmp;
			} else {
				uncle = RB_LEFT(gparent);
				if (RB_IS_RED(uncle)) {
					RB_SET_BLACK(parent & ~1ULL);
					RB_SET_BLACK(uncle);
					RB_SET_RED(gparent);
					node = gparent;
					continue;
				}
				if (node == RB_LEFT(parent & ~1ULL)) {
					node = parent & ~1ULL;
					/* rotate-right at node */
					tmp = RB_LEFT(node);
					RB_LEFT(node) = RB_RIGHT(tmp);
					if (RB_RIGHT(tmp)) RB_PAR(RB_RIGHT(tmp)) = node;
					RB_PAR(tmp) = RB_PAR(node);
					RB_PAR(node) = tmp;
					RB_RIGHT(tmp) = node;
					if (RB_PAR(tmp) == 0) *root = tmp;
					else if (node == RB_LEFT(RB_PAR(tmp)))
						RB_LEFT(RB_PAR(tmp)) = tmp;
					else RB_RIGHT(RB_PAR(tmp)) = tmp;
					parent = node;
				}
				/* rotate-left at gparent */
				RB_SET_BLACK(parent & ~1ULL);
				RB_SET_RED(gparent);
				tmp = RB_RIGHT(gparent);
				RB_RIGHT(gparent) = RB_LEFT(tmp);
				if (RB_LEFT(tmp)) RB_PAR(RB_LEFT(tmp)) = gparent;
				RB_PAR(tmp) = RB_PAR(gparent);
				RB_PAR(gparent) = tmp;
				RB_LEFT(tmp) = gparent;
				if (RB_PAR(tmp) == 0) *root = tmp;
				else if (gparent == RB_LEFT(RB_PAR(tmp)))
					RB_LEFT(RB_PAR(tmp)) = tmp;
				else RB_RIGHT(RB_PAR(tmp)) = tmp;
			}
		}
	}
	RB_SET_BLACK(*root);
}

/* FUN_00021434 @ 0x00021434   (est. txm_rb_erase)
 * Ghidra: void FUN_00021434(ulong *root, ulong node, ulong parent)
 * Red-black tree erase (rebalance) for the interval tree, invoked after a node
 * is unlinked. Re-colors and rotates to restore black-height; the augmented
 * value bookkeeping is the standard rb_erase_augmented form. Panics 0x19 on
 * structural wrap. Faithful to the decompile's rotate/color structure.
 * Confidence: high (canonical RB erase)
 */
void txm_rb_erase(txm_rb_node_t *root, txm_rb_node_t node, txm_rb_node_t parent)
{
	txm_rb_node_t other, tmp, child;

	do {
		if (parent == *root) {
			if (node == 0) {
				RB_SET_BLACK(*root);
				return;
			}
			node = RB_PAR(*root);
			RB_SET_BLACK(*root);
			return;
		}
		other = node;
		if (RB_LEFT(parent) == node) {
			child = RB_RIGHT(parent);
			if (RB_IS_RED(child)) {
				RB_SET_BLACK(child);
				RB_SET_RED(parent);
				/* rotate-left at parent */
				tmp = child;
				RB_RIGHT(parent) = RB_LEFT(tmp);
				if (RB_LEFT(tmp)) RB_PAR(RB_LEFT(tmp)) = parent;
				RB_PAR(tmp) = RB_PAR(parent);
				RB_PAR(parent) = tmp;
				RB_LEFT(tmp) = parent;
				if (RB_PAR(tmp) == 0) *root = tmp;
				else if (parent == RB_LEFT(RB_PAR(tmp)))
					RB_LEFT(RB_PAR(tmp)) = tmp;
				else RB_RIGHT(RB_PAR(tmp)) = tmp;
				child = RB_RIGHT(parent);
			}
			if (!RB_IS_RED(RB_LEFT(child)) && !RB_IS_RED(RB_RIGHT(child))) {
				RB_SET_RED(child);
				node = parent;
				parent = RB_PAR(parent) & ~1ULL;
			} else {
				if (!RB_IS_RED(RB_RIGHT(child))) {
					RB_SET_BLACK(RB_LEFT(child));
					RB_SET_RED(child);
					/* rotate-right at child */
					tmp = RB_LEFT(child);
					RB_LEFT(child) = RB_RIGHT(tmp);
					if (RB_RIGHT(tmp)) RB_PAR(RB_RIGHT(tmp)) = child;
					RB_PAR(tmp) = RB_PAR(child);
					RB_PAR(child) = tmp;
					RB_RIGHT(tmp) = child;
					if (RB_PAR(tmp) == 0) *root = tmp;
					else if (child == RB_LEFT(RB_PAR(tmp)))
						RB_LEFT(RB_PAR(tmp)) = tmp;
					else RB_RIGHT(RB_PAR(tmp)) = tmp;
					child = tmp;
				}
				RB_COPY_COLOR(child, parent);
				RB_SET_BLACK(parent);
				RB_SET_BLACK(RB_RIGHT(child));
				/* rotate-left at parent */
				tmp = RB_RIGHT(parent);
				RB_RIGHT(parent) = RB_LEFT(tmp);
				if (RB_LEFT(tmp)) RB_PAR(RB_LEFT(tmp)) = parent;
				RB_PAR(tmp) = RB_PAR(parent);
				RB_PAR(parent) = tmp;
				RB_LEFT(tmp) = parent;
				if (RB_PAR(tmp) == 0) *root = tmp;
				else if (parent == RB_LEFT(RB_PAR(tmp)))
					RB_LEFT(RB_PAR(tmp)) = tmp;
				else RB_RIGHT(RB_PAR(tmp)) = tmp;
				break;
			}
		} else {
			child = RB_LEFT(parent);
			if (RB_IS_RED(child)) {
				RB_SET_BLACK(child);
				RB_SET_RED(parent);
				/* rotate-right at parent */
				tmp = child;
				RB_LEFT(parent) = RB_RIGHT(tmp);
				if (RB_RIGHT(tmp)) RB_PAR(RB_RIGHT(tmp)) = parent;
				RB_PAR(tmp) = RB_PAR(parent);
				RB_PAR(parent) = tmp;
				RB_RIGHT(tmp) = parent;
				if (RB_PAR(tmp) == 0) *root = tmp;
				else if (parent == RB_LEFT(RB_PAR(tmp)))
					RB_LEFT(RB_PAR(tmp)) = tmp;
				else RB_RIGHT(RB_PAR(tmp)) = tmp;
				child = RB_LEFT(parent);
			}
			if (!RB_IS_RED(RB_LEFT(child)) && !RB_IS_RED(RB_RIGHT(child))) {
				RB_SET_RED(child);
				node = parent;
				parent = RB_PAR(parent) & ~1ULL;
			} else {
				if (!RB_IS_RED(RB_LEFT(child))) {
					RB_SET_BLACK(RB_RIGHT(child));
					RB_SET_RED(child);
					/* rotate-left at child */
					tmp = RB_RIGHT(child);
					RB_RIGHT(child) = RB_LEFT(tmp);
					if (RB_LEFT(tmp)) RB_PAR(RB_LEFT(tmp)) = child;
					RB_PAR(tmp) = RB_PAR(child);
					RB_PAR(child) = tmp;
					RB_LEFT(tmp) = child;
					if (RB_PAR(tmp) == 0) *root = tmp;
					else if (child == RB_LEFT(RB_PAR(tmp)))
						RB_LEFT(RB_PAR(tmp)) = tmp;
					else RB_RIGHT(RB_PAR(tmp)) = tmp;
					child = tmp;
				}
				RB_COPY_COLOR(child, parent);
				RB_SET_BLACK(parent);
				RB_SET_BLACK(RB_LEFT(child));
				/* rotate-right at parent */
				tmp = RB_LEFT(parent);
				RB_LEFT(parent) = RB_RIGHT(tmp);
				if (RB_RIGHT(tmp)) RB_PAR(RB_RIGHT(tmp)) = parent;
				RB_PAR(tmp) = RB_PAR(parent);
				RB_PAR(parent) = tmp;
				RB_RIGHT(tmp) = parent;
				if (RB_PAR(tmp) == 0) *root = tmp;
				else if (parent == RB_LEFT(RB_PAR(tmp)))
					RB_LEFT(RB_PAR(tmp)) = tmp;
				else RB_RIGHT(RB_PAR(tmp)) = tmp;
				break;
			}
		}
	} while (!RB_IS_RED(node) || RB_PAR(parent) != 0);
	if (RB_IS_RED(node)) {
		RB_SET_BLACK(node);
	} else {
		RB_SET_BLACK(*root);
	}
}

/* FUN_00021bd8 @ 0x00021bd8   (est. txm_rb_erase_node)
 * Ghidra: ulong FUN_00021bd8(ulong *root, ulong node)
 * Red-black tree node deletion: unlinks `node` from the interval tree,
 * splicing its children and rebalancing via txm_rb_erase. Returns the removed
 * node. Panics 0x19 on structural wrap.
 * Confidence: high (canonical RB erase-node)
 */
uint64_t txm_rb_erase_node(txm_rb_node_t *root, txm_rb_node_t node)
{
	txm_rb_node_t child = RB_RIGHT(node), parent = RB_LEFT(node);
	txm_rb_node_t repl, next;

	if (parent == 0 || child == 0) {
		next = RB_PAR(node);
		if (next == 0) {
			child = 0;
		} else {
			child = next & ~1ULL;
		}
		uint64_t ok = child + 0x50;
		if (parent != 0) {
			txm_rb_link(parent, child);
		}
		if (child == 0) {
			*root = parent;
		} else if (RB_LEFT(child) == node) {
			RB_LEFT(child) = parent;
		} else {
			RB_RIGHT(child) = parent;
		}
		if ((next & 1) == 0) {
			txm_rb_erase(root, child, parent);
		}
		return node;
	}

	/* node has two children: find the in-order successor. */
	next = child;
	while (RB_LEFT(child) != 0) {
		next = child;
		child = RB_LEFT(child);
	}
	parent = child;
	child = RB_RIGHT(child);
	if (child != 0) {
		txm_rb_link(child, parent);
	}
	/* splice successor's contents into node's position. */
	RB_PAR(parent) = RB_PAR(node);
	RB_LEFT(parent) = RB_LEFT(node);
	RB_RIGHT(parent) = RB_RIGHT(node);
	if (node == 0 || RB_PAR(node) == 0) {
		*root = parent;
	} else {
		uint64_t p = RB_PAR(node) & ~1ULL;
		if (RB_LEFT(p) == node) {
			RB_LEFT(p) = parent;
		} else {
			RB_RIGHT(p) = parent;
		}
	}
	uint64_t rp = RB_PAR(node) & ~1ULL;
	txm_rb_link(RB_LEFT(node), parent);
	if (RB_RIGHT(node) != 0) {
		txm_rb_link(RB_RIGHT(node), parent);
	}
	if ((RB_PAR(node) & 1) == 0) {
		txm_rb_erase(root, rp, parent);
	}
	return node;
}

/* FUN_00021ddc @ 0x00021ddc   (est. txm_rb_insert)
 * Ghidra: long FUN_00021ddc(long *root, long node)
 * Interval-tree insert for a code region: walks the tree comparing the new
 * node's key/end (param_2+0x28 / +0x30) against each node; if the interval
 * overlaps or touches an existing node it returns that node WITHOUT inserting
 * (collision). Otherwise it links the node as a leaf and rebalances with
 * txm_rb_insert_fixup, returning 0. This is the code-region conflict detector.
 * Confidence: high (canonical RB interval insert)
 */
long txm_rb_insert(txm_rb_node_t *root, txm_rb_node_t node)
{
	txm_rb_node_t cur = *root, parent = 0;
	int go_left = 0;

	while (cur != 0) {
		parent = cur;
		if (RB_KEY(node) < RB_KEY(cur) &&
		    RB_END(node) <= RB_KEY(cur)) {
			go_left = 1;
			cur = RB_LEFT(cur);
		} else {
			if (RB_KEY(node) < RB_END(cur)) {
				return cur;               /* overlap with existing region */
			}
			if (RB_END(node) <= RB_END(cur)) {
				return cur;               /* contained/equal */
			}
			go_left = 0;
			cur = RB_RIGHT(cur);
		}
	}

	txm_rb_link(node, parent);
	RB_LEFT(node) = 0;
	RB_RIGHT(node) = 0;

	if (parent == 0) {
		*root = node;
	} else if (go_left) {
		RB_LEFT(parent) = node;
	} else {
		RB_RIGHT(parent) = node;
	}
	txm_rb_insert_fixup(root, node);
	return 0;
}

/* FUN_00021f08 @ 0x00021f08   (est. txm_rb_find_overlap)
 * Ghidra: void FUN_00021f08(long *root, long query)
 * Walks the code-region interval tree rooted at *root looking for the first
 * node whose [start+0x28, end+0x30) interval overlaps or touches the query
 * range. Returns the overlapping node (Ghidra shows void but callers consume
 * the return). Used by page enforcement to locate the association covering a
 * requested range.
 * Confidence: high (interval-tree search)
 */
txm_rb_node_t txm_rb_find_overlap(txm_obj_t root_slot, uint64_t start, uint64_t end)
{
	txm_rb_node_t node = *(txm_rb_node_t *)root_slot;

	while (node != 0) {
		if (start < RB_KEY(node) && end <= RB_KEY(node)) {
			node = RB_LEFT(node);
		} else if (start < RB_END(node)) {
			return node;                  /* overlaps */
		} else if (end <= RB_END(node)) {
			return node;                  /* contained */
		} else {
			node = RB_RIGHT(node);
		}
	}
	return 0;
}

/* FUN_00021f64 @ 0x00021f64   (est. txm_rb_node_to_obj)
 * Ghidra: undefined8 FUN_00021f64(long node, ulong *obj_out, undefined8 flag)
 * Resolves an interval-tree node to its backing TXM object: acquires the node,
 * requires it be "live" (+0x12 & 0x7f == 0), reads the object handle at +0x20
 * (panic 0x84 if null), acquires the object, and returns it via *obj_out with
 * status 0. Non-live nodes yield status 1; error statuses 0xf/0x10/0x11.
 * Confidence: high (object-lookup helper)
 */
uint64_t txm_rb_node_to_obj(txm_rb_node_t node, uint64_t *obj_out, uint64_t flag)
{
	uint64_t obj = 0;
	int acquired;

	if (node == 0) {
		return 0xf;
	}
	txm_lock_acquire(node, 0, 0);
	if ((*(uint8_t *)(node + 0x12) & 0x7f) == 0) {
		obj = *(uint64_t *)(node + 0x20);
		if (obj == 0) {
			txm_panic(0x84);
		}
		if (obj + 0x148 <= obj) {
			txm_panic(0x19);
		}
		acquired = txm_lock_acquire(obj, flag, 1) ^ 1;
	} else {
		obj = 0;
		acquired = 1;
	}
	txm_lock_release(node, 0);
	if (obj != 0 && (acquired & 1) == 0) {
		if (obj_out == 0) {
			if (obj + 0x148 <= obj) {
				txm_panic(0x19);
			}
			txm_lock_release(obj, flag);
			return 0;
		}
		if (obj + 0x148 <= obj) {
			txm_panic(0x19);
		}
		*obj_out = obj;
		return 0;
	}
	return 0x10;
}

/* FUN_00022050 @ 0x00022050   (est. txm_slot_table_base)
 * Ghidra: undefined * FUN_00022050(ushort *desc, uint expected)
 * Resolves a {slot index (*desc), table id (desc[1])} descriptor into the base
 * pointer of the per-table slot array. Table id 0 selects the ASID/context
 * table (DAT_000104f8), table id 1 the region table (&DAT_000706c0); id 0
 * rejects slot index 0 (0x85). A mismatched/unknown table id panics
 * (0x60/0x61/0x62).
 * Confidence: medium (role inferred from the two table bases)
 */
uint64_t txm_slot_table_base(uint16_t *desc, uint32_t expected)
{
	uint32_t id = desc[1];

	if (expected != 0xffff && expected != desc[1]) {
		txm_panic(0x60);
	}
	if (id == 1) {
		if (*desc < 0xff) {
			return (uint64_t)&txm_region_slot_table;   /* &DAT_000706c0 */
		}
	} else if (id != 0) {
		txm_panic(0x61);
	} else {
		if (*desc < txm_asid_count) {
			if (*desc != 0) {
				return txm_asid_table;                 /* DAT_000104f8 */
			}
			txm_panic(0x85);                           /* slot 0 forbidden */
		}
	}
	txm_panic(0x62);
}

/* FUN_000220ec @ 0x000220ec   (est. txm_slot_reserve)
 * Ghidra: undefined8 FUN_000220ec(undefined4 slot)
 * Reserves an object slot by writing the sentinel -2 into it. A non-empty slot
 * panics 0x63 (99). Returns 0.
 * Confidence: medium
 */
uint64_t txm_slot_reserve(uint32_t slot)
{
	uint16_t desc[2] = { (uint16_t)slot, 0 };
	uint64_t base = txm_slot_table_base(desc, 0);
	uint64_t *entry = (uint64_t *)(base + (uint16_t)slot * 8);

	if (*entry != 0) {
		txm_panic(99);
	}
	*entry = -2;
	return 0;
}

/* FUN_0002214c @ 0x0002214c   (est. txm_slot_release)
 * Ghidra: undefined8 FUN_0002214c(undefined4 slot)
 * Releases an object slot: requires the sentinel -3 (being destroyed) and
 * clears it to 0. A slot not in the -3 state panics 100.
 * Confidence: medium
 */
uint64_t txm_slot_release(uint32_t slot)
{
	uint16_t desc[2] = { (uint16_t)slot, 0 };
	uint64_t base = txm_slot_table_base(desc, 0xffff);
	uint64_t *entry = (uint64_t *)(base + (uint16_t)slot * 8);

	if (*entry != -3) {
		txm_panic(100);
	}
	*entry = 0;
	return 0;
}

/* FUN_000221a8 @ 0x000221a8   (est. txm_slot_lookup)
 * Ghidra: ulong FUN_000221a8(uint id, undefined8 b, undefined8 c)
 * Looks up the object installed in slot `id` and validates its identity
 * against the slot id: the object's +0x22 must equal id's low 16 bits and
 * +0x24 its high 16 bits (else panics 0x8c/0x8d). Empty/-2/-3 slots panic
 * 0x65/0x66/0x67. Acquires the object (FUN_0002811c) before returning it.
 * Confidence: high (object-table lookup; panics are explicit)
 */
uint64_t txm_slot_lookup(uint32_t id, uint64_t b, uint64_t c)
{
	uint16_t desc[2] = { (uint16_t)id, 0 };
	uint64_t base = txm_slot_table_base(desc, 0);
	uint64_t entry = *(uint64_t *)(base + (uint16_t)id * 8);

	if (entry == -3) {
		txm_panic(0x67);
	} else if (entry == -2) {
		txm_panic(0x66);
	} else if (entry == 0) {
		txm_panic(0x65);
	}
	{
		uint64_t obj = txm_obj_get_current();
		txm_lock_acquire(obj, c, 0);
		if ((uint16_t)*(uint16_t *)(obj + 0x22) == (id & 0xffff)) {
			if ((uint16_t)*(uint16_t *)(obj + 0x24) == (id >> 0x10)) {
				if (obj < obj + 0x70) {
					return obj;
				}
				txm_panic(0x19);
			}
			txm_panic(0x8d);
		}
		txm_panic(0x8c);
	}
}

/* FUN_00022274 @ 0x00022274   (est. txm_slot_create)
 * Ghidra: undefined8 FUN_00022274(ushort id, undefined8 b, long *obj_out)
 * Creates a new object in slot `id`: allocates a fresh object (FUN_000281ec)
 * and a region (FUN_00027d78), acquires the object, sets its id (+0x22), zeroes
 * +0x18, links the region at +0x38, stores the object into the (reserved) slot
 * (requires the -2 sentinel, panic 0x68), and releases. Returns the object via
 * *obj_out; 7 on allocation failure.
 * Confidence: high (object-table create)
 */
uint64_t txm_slot_create(uint16_t id, uint64_t b, uint64_t *obj_out)
{
	uint16_t desc[2] = { id, 0 };
	uint64_t base = txm_slot_table_base(desc, 0);
	uint64_t obj = txm_obj_new();
	uint64_t region;

	if (obj == 0) {
		return 7;
	}
	region = txm_region_new();
	if (region != 0) {
		txm_lock_acquire(obj, 1, 0);
		*(uint32_t *)(obj + 0x22) = (uint32_t)id;
		*(uint64_t *)(obj + 0x18) = 0;
		*(uint64_t *)(obj + 0x38) = region;
		{
			uint64_t *entry = (uint64_t *)(base + (uint16_t)id * 8);
			if (*entry != -2) {
				txm_panic(0x68);
			}
			*entry = obj;
		}
		txm_lock_release(obj, 1);
		if (obj_out == 0) {
			return 0;
		}
		*obj_out = obj;
		return 0;
	}
	txm_obj_ref(&obj, 3, 4);
	return 7;
}

/* FUN_00022348 @ 0x00022348   (est. txm_slot_destroy)
 * Ghidra: undefined8 FUN_00022348(long obj)
 * Destroys the object in its slot: unlinks the slot entry (set -3), tears the
 * object down (FUN_000284a0), drops the region reference (+0x48, panic 0x4f on
 * underflow), removes every interval-tree node in the object's tree (+0x28)
 * dropping each node's backing object reference (panic 0x4f on underflow), and
 * optionally revalidates the profile association (FUN_00035178) before
 * releasing the slot (FUN_000283b8). Errors panic 0x69/0x6a/0x6b.
 * Confidence: medium (teardown path inferred)
 */
uint64_t txm_slot_destroy(txm_obj_t obj)
{
	uint16_t desc[2] = { (uint16_t)*(uint32_t *)(obj + 0x22), 0 };
	uint64_t base = txm_slot_table_base(desc, 0xffff);
	uint64_t *entry = (uint64_t *)(base + (uint16_t)desc[0] * 8);
	uint64_t node, sub, ref;
	int cnt;

	if (*entry != obj) {
		txm_panic(0x69);
	}
	*entry = -3;
	txm_obj_ref(&obj, 3, 5);

	if (*(int *)(obj + 0x68) == 0) {
		if (*(uint64_t *)(obj + 0x48) == 0) {
			if (*(uint64_t *)(obj + 0x38) == 0) {
				txm_panic(0x6b);           /* no region to drop */
			}
			txm_obj_ref((uint64_t *)(obj + 0x38), 3, 4);
		} else {
			sub = *(uint64_t *)(*(uint64_t *)(obj + 0x48) + 0x18);
			txm_lock_acquire(sub, 0, 0);
			LOAcquire();
			cnt = *(int *)(sub + 0x68);
			*(int *)(sub + 0x68) = cnt - 1;
			LORelease();
			if (cnt == 0) {
				txm_panic(0x4f);           /* refcount underflow */
			}
			if (sub + 0x70 <= sub) {
				txm_panic(0x19);
			}
			txm_lock_release(sub, 0);
		}
		/* Remove every interval-tree node and drop each backing ref. */
		{
			uint64_t *rootp = (uint64_t *)(obj + 0x28);
			node = *rootp;
			while (node != 0) {
				txm_rb_erase_node(rootp, node);
				sub = node;
				txm_obj_teardown2(&sub);
				if ((*(uint8_t *)(sub + 0x12) & 0x7f) == 0) {
					ref = *(uint64_t *)(sub + 0x20);
					int acq = txm_lock_acquire(ref, 0, 1);
					LOAcquire();
					cnt = *(int *)(ref + 0x14);
					*(int *)(ref + 0x14) = cnt - 1;
					LORelease();
					if (cnt == 0) {
						txm_panic(0x4f);   /* refcount underflow */
					}
					if (acq == 0) {
						if (cnt == 1) {
							txm_obj_release(&ref);
						}
					} else {
						txm_lock_release(ref, 0);
					}
				}
				txm_node_finalize(&sub);
				rootp = (uint64_t *)(obj + 0x28);
				node = *rootp;
			}
		}
		/* Revalidate the profile association when this is the last region. */
		if ((uint16_t)(desc[0] >> 0x10) == 0 && *(uint64_t *)(obj + 0x40) != 0) {
			if ((txm_debug_state & 1) == 0) {
				txm_panic(0x19);
			}
			if ((*(uint8_t *)(txm_profile_ctx + 0x48) & 1) != 0) {
				uint64_t r = txm_profile_assoc_check(txm_profile_handle,
				                                     *(uint8_t *)(obj + 0x20));
				uint32_t cls = (uint32_t)(r >> 8) & 0xff;
				if (cls != 0) {
					if (cls == 0x20) txm_panic(((uint32_t)r & 0xffff00ff) | 0x2000);
					else if (cls == 0x21) txm_panic(((uint32_t)r & 0xffff0000) | ((uint32_t)r & 0xff) | 0x2100);
					txm_panic(0xf1, r);
				}
			}
		}
		txm_slot_release_teardown(&obj);
		return 0;
	}
	txm_panic(0x6a);
}

/* FUN_00022568 @ 0x00022568   (est. txm_region_rename)
 * Ghidra: undefined8 FUN_00022568(undefined4 from_slot, undefined4 to_slot)
 * Moves an object between slots: looks up the object in `from_slot` (table 0),
 * requires it be empty of associations (no region at +0x48/+0x28/+0x18), clears
 * the source slot, re-ids the object (+0x22 = to_slot), and installs it into the
 * (empty) target slot (table 1). Panics 0x6c/0x6d/0x6e/0x6f/0x7a on invalid state.
 * Confidence: high (slot-move with explicit state checks)
 */
uint64_t txm_region_rename(uint32_t from_slot, uint32_t to_slot)
{
	uint16_t desc_from[2] = { (uint16_t)from_slot, 0 };
	uint16_t desc_to[2] = { (uint16_t)to_slot, 1 };
	uint64_t base_from = txm_slot_table_base(desc_from, 0);
	uint64_t base_to = txm_slot_table_base(desc_to, 1);
	uint64_t obj = txm_slot_lookup(from_slot, 0, 1);

	if (*(uint64_t *)(obj + 0x48) == 0) {
		if (*(uint64_t *)(obj + 0x28) == 0) {
			if (*(uint64_t *)(obj + 0x18) == 0) {
				uint64_t *src = (uint64_t *)(base_from + (uint16_t)from_slot * 8);
				if (*src == obj) {
					*src = 0;
					*(uint32_t *)(obj + 0x22) = to_slot;
					uint64_t *dst = (uint64_t *)(base_to + (uint16_t)to_slot * 8);
					if (*dst == 0) {
						*dst = obj;
						if (obj + 0x70 <= obj) {
							txm_panic(0x19);
						}
						txm_lock_release(obj, 1);
						return 0;
					}
					txm_panic(0x6f);       /* target slot occupied */
				}
				txm_panic(0x6e);           /* source slot mismatch */
			}
			txm_panic(0x7a);               /* object has +0x18 */
		}
		txm_panic(0x6d);                   /* object has region +0x28 */
	}
	txm_panic(0x6c);                       /* object has association +0x48 */
}

/* FUN_00022660 @ 0x00022660   (est. txm_region_set_range)
 * Ghidra: undefined8 FUN_00022660(long obj, ulong start, ulong size)
 * Sets a code object's executable range [start, start+size) at +0x58/+0x60.
 * Both bounds must be 16 KiB aligned and non-empty; overflow panics 0x42. Only
 * permitted on a "free" object (+0x24==1 and +0x60==0), else panic 0x87.
 * Confidence: high (range-setter with alignment/overflow checks)
 */
uint64_t txm_region_set_range(uint64_t obj, uint64_t start, uint64_t size)
{
	if (((start & 0x3fff) == 0) && ((size & 0x3fff) == 0)) {
		if (start == 0) {
			txm_panic(0x40);
		}
		if (size == 0) {
			txm_panic(0x41);
		}
		if (start + size < start) {         /* CARRY8 overflow */
			txm_panic(0x42);
		}
		txm_lock_acquire(obj, 1, 0);
		if (*(uint16_t *)(obj + 0x24) == 1 && *(uint64_t *)(obj + 0x60) == 0) {
			*(uint64_t *)(obj + 0x58) = start;
			*(uint64_t *)(obj + 0x60) = start + size;
			txm_lock_release(obj, 1);
			return 0;
		}
		txm_panic(0x87);
	}
	txm_panic(0x86);
}

/* FUN_0002270c @ 0x0002270c   (est. txm_region_attach)
 * Ghidra: undefined8 FUN_0002270c(undefined4 obj_slot, undefined4 assoc_slot,
 *                                 ulong start, ulong size)
 * Attaches a code-association node to `obj_slot` for the range
 * [start, start+size), referencing `assoc_slot`. Validates alignment, that the
 * range lies within the association's range (+0x58/+0x60; panics 0x88/0x89),
 * increments the association's link count (panic 0x4e overflow), creates the
 * interval node (insert; overlap panic 0x75) and links it into the object's
 * tree. Panics 0x70/0x71/0x74 on bad state.
 * Confidence: high (association-install with range checks)
 */
uint64_t txm_region_attach(uint32_t obj_slot, uint32_t assoc_slot,
                           uint64_t start, uint64_t size)
{
	uint64_t end = start + size;
	uint64_t assoc, obj, node;
	uint32_t cnt;

	if ((start & 0x3fff) != 0) {
		txm_panic(0x70);
	}
	if ((size & 0x3fff) != 0) {
		txm_panic(0x71);
	}
	if (start == 0) {
		txm_panic(0x40);
	}
	if (size == 0) {
		txm_panic(0x41);
	}
	if (end < start) {                      /* CARRY8 */
		txm_panic(0x42);
	}

	assoc = txm_slot_lookup(assoc_slot, 1, 0);
	if (start < *(uint64_t *)(assoc + 0x58)) {
		txm_panic(0x88);                     /* below association range */
	}
	if (*(uint64_t *)(assoc + 0x60) < end) {
		txm_panic(0x89);                     /* above association range */
	}
	cnt = *(uint32_t *)(assoc + 0x68);
	*(uint32_t *)(assoc + 0x68) = cnt + 1;
	if (cnt >= ~txm_link_limit) {
		txm_panic(0x4e);                     /* link overflow */
	}
	if (assoc + 0x70 <= assoc) {
		txm_panic(0x19);
	}
	txm_lock_release(assoc, 0);

	obj = txm_slot_lookup(obj_slot, 0, 1);
	if (*(uint64_t *)(obj + 0x48) == 0) {
		node = *(uint64_t *)(obj + 0x38);
		*(uint8_t *)(node + 0x12) = (*(uint8_t *)(node + 0x12) & 0x80) | 1;
		*(uint64_t *)(node + 0x28) = *(uint64_t *)(assoc + 0x58);
		*(uint64_t *)(node + 0x30) = *(uint64_t *)(assoc + 0x60);
		*(uint64_t *)(node + 0x18) = assoc;
		if (obj + 0x70 <= obj || node + 0x50 <= node) {
			txm_panic(0x19);
		}
		if (txm_rb_insert((txm_rb_node_t *)(obj + 0x28), node) == 0) {
			*(uint64_t *)(obj + 0x48) = node;
			*(uint64_t *)(obj + 0x38) = 0;
			txm_lock_release(obj, 1);
			return 0;
		}
		txm_panic(0x75);                     /* interval overlap */
	}
	txm_panic(0x74);                         /* object already associated */
}

/* FUN_0002289c @ 0x0002289c   (est. txm_obj_get_assoc)
 * Ghidra: long FUN_0002289c(undefined8 *assoc_out)
 * Returns the current context's object (slot lookup via the context id) and,
 * if it has an association node (+0x40), resolves that node to its backing
 * object and returns it via *assoc_out (panic 0x82 on failure). Returns the
 * primary object, or 0 if no context is active.
 * Confidence: medium
 */
long txm_obj_get_assoc(uint64_t *assoc_out)
{
	uint32_t id = txm_context_id_get();       /* FUN_0002c834 */
	uint64_t obj, node, assoc = 0;

	if ((id & 0xffff) == 0) {
		return 0;
	}
	obj = txm_slot_lookup(id, 0, 0);
	node = *(uint64_t *)(obj + 0x40);
	if (txm_rb_node_to_obj(node, &assoc, 0) != 0) {
		txm_panic(0x82);
	}
	if (assoc_out == 0) {
		txm_lock_release(assoc, 0);
	} else {
		*assoc_out = assoc;
	}
	return obj;
}

/* FUN_0002292c @ 0x0002292c   (est. txm_release_pair)
 * Ghidra: void FUN_0002292c(undefined8 a, long b)
 * Releases two objects (a and b) after a lookup, with a stack-guard check
 * before the second release. Used to balance acquire/release around
 * entitlement lookups.
 * Confidence: medium
 */
void txm_release_pair(uint64_t a, uint64_t b)
{
	if (b != 0) {
		txm_lock_release(b, 0);
	}
	txm_stack_guard_check();
	txm_lock_release(a, 0);
}

/* FUN_00022974 @ 0x00022974   (est. txm_entitlement_lookup)
 * Ghidra: undefined8 FUN_00022974(long obj)
 * Looks up an entitlement/string value from the current or associated object's
 * entitlements dictionary: resolves the object's association (or the current
 * context's), reads the entry via FUN_00036724, and returns it (0 on failure).
 * Requires obj+0x10 to be non-empty (panic 0x38).
 * Confidence: medium
 */
uint64_t txm_entitlement_lookup(uint64_t obj)
{
	uint64_t assoc = 0, out = 0;
	uint64_t r;

	if (obj == 0) {
		if (txm_obj_get_assoc(&assoc) == 0) {
			return 0;
		}
		r = txm_ce_get_entitlement(assoc + 0x28, &out);
		txm_release_pair(0, assoc);
	} else {
		if (*(char *)(obj + 0x10) == '\0') {
			txm_panic(0x38);
		}
		if (txm_rb_node_to_obj(*(uint64_t *)(obj + 0x40), &assoc, 0) != 0) {
			return 0;
		}
		r = txm_ce_get_entitlement(assoc + 0x28, &out);
		txm_lock_release(assoc, 0);
	}
	if ((r & 0xff00) != 0) {
		out = 0;
	}
	return out;
}

/* FUN_00022a38 @ 0x00022a38   (est. txm_entitlement_check)
 * Ghidra: bool FUN_00022a38(long obj, undefined8 key, long arg)
 * Entitlement boolean check: resolves the current/associated object's
 * entitlements dictionary and tests `key` (optionally with an argument). Used
 * for com.apple.private.cs.debugger etc. Returns true iff the entry exists
 * and is truthy. Panics 0x38 if obj+0x10 empty.
 * Confidence: high (entitlement gate used by page enforcement)
 */
int txm_entitlement_check(uint64_t obj, uint64_t key, uint64_t arg)
{
	uint64_t assoc = 0, r;

	if (obj == 0) {
		if (txm_obj_get_assoc(&assoc) == 0) {
			return 0;
		}
	} else {
		if (*(char *)(obj + 0x10) == '\0') {
			txm_panic(0x38);
		}
		if (txm_rb_node_to_obj(*(uint64_t *)(obj + 0x40), &assoc, 0) != 0) {
			return 0;
		}
	}
	if (arg == 0) {
		r = txm_ce_get_bool(assoc + 0x28, key);
	} else {
		r = txm_ce_get_arg(assoc + 0x28, key, arg);
	}
	if (obj == 0) {
		txm_release_pair(0, assoc);
	} else {
		txm_lock_release(assoc, 0);
	}
	return (r & 0xff00) == 0;
}

/* FUN_00022b10 @ 0x00022b10   (est. txm_exec_debug_mapping_check)
 * Ghidra: ulong FUN_00022b10(long obj, long assoc, ulong start, ulong size,
 *                            ulong base)
 * Executable debug-mapping check (OAH/runtime entitlement gate). Validates the
 * requested range [start, start+size) against `base` and the association's
 * code-limit; for legacy (<6) dictionaries it requires the association to span
 * the whole range (else logs 0xd39 "association spans outside of code limit",
 * error 0x24); for modern dictionaries it verifies size/base match the
 * dictionary (0x12/0x13), admits OAH/runtime_arm_internal identifiers (0xcf7/
 * 0xd1a), enforces the object's debug bit, and for a JIT-debug object validates
 * the CD-hash chain (FUN_00036d44 + FUN_000230fc) or falls back to region
 * authorization (FUN_00023050). On success installs a new interval node and
 * increments the association link count (panic 0x4e on overflow). Returns
 * packed {low16 err, ...}; error 0x17 on interval overlap.
 * Confidence: high (executable debug-mapping gate; strings 0xd39/0xd65/0xd95,
 *   entitlements 0xcf7/0xd1a)
 */
uint64_t txm_exec_debug_mapping_check(uint64_t obj, uint64_t assoc,
                                      uint64_t start, uint64_t size,
                                      uint64_t base)
{
	uint64_t end = start + size;
	uint64_t node, r, r2, assoc2 = 0, limit;
	uint32_t cnt, word, low, hi;
	int ver, i, err = 0;
	uint8_t flag = 0;
	uint64_t d_size = 0, d_base = 0, d_ident = 0, d_code = 0;
	uint64_t d_dict = 0;
	int oah = 0;

	if ((start & 0x3fff) != 0) txm_panic(0x76);
	if ((size & 0x3fff) != 0) txm_panic(0x77);
	if ((base & 0x3fff) != 0) txm_panic(0x78);
	if (start == 0) txm_panic(0x40);
	if (size == 0) txm_panic(0x41);
	if (end < start) txm_panic(0x42);

	node = txm_region_new();
	if (node == 0) {
		return 7;
	}
	txm_lock_acquire(node, 1, 0);
	txm_lock_acquire(assoc, 0, 0);
	txm_lock_acquire(obj, 1, 0);

	if ((*(uint8_t *)(obj + 0x18) & 1) != 0) {
		txm_panic(0x25);
	}

	txm_ce_field(assoc + 0x28, &flag);
	if (flag == 0) {
		txm_panic(0xc);
	}
	txm_ce_dict_init(assoc + 0x28, &d_dict, 0, 0);
	txm_ce_parse_header(d_dict, 0, &d_base, &d_size, &d_ident);
	txm_ce_get_info(d_dict, &d_code);

	if (flag < 6) {
		if (base + size < base) {
			txm_panic(0x79);
		}
		txm_ce_get_len(d_dict, &limit);
		if (limit < base + size) {
			txm_log("association spans outside of code limit");   /* 0xd39 */
			err = 0x24;
			goto out;
		}
		ver = 0;
	} else {
		if (size != d_size) {
			err = 0x12;
			goto out;
		}
		if (base != d_base) {
			err = 0x13;
			goto out;
		}
		if (txm_uuid_compare((const void *)d_ident, 0xcf7) == 0 ||
		    txm_uuid_compare((const void *)d_ident, 0xd1a) == 0) {
			oah = 1;                          /* OAH / runtime_arm_internal */
		}
		ver = 1;
	}

	if (*(uint16_t *)(obj + 0x24) == 1) {
		if (flag < 6) txm_panic(0x7b);
		if ((*(uint8_t *)(obj + 0x18) & 2) != 0) txm_panic(0x7c);
		if (start < *(uint64_t *)(obj + 0x58)) txm_panic(0x8a);
		if (*(uint64_t *)(obj + 0x60) < end) txm_panic(0x8b);
		/* allowed */
		err = 0;
		goto install;
	} else if (oah) {
		/* OAH runtime: allowed for JIT */
		err = 0;
		goto install;
	} else if ((*(uint8_t *)(obj + 0x18) & 2) == 0) {
		/* Non-JIT: validate CD-hash chain. */
		if (txm_rb_node_to_obj(*(uint64_t *)(obj + 0x40), &assoc2, 0) != 0) {
			err = 0;
			goto out;
		}
		r = txm_amfi_can_exec_cdhash(assoc2 + 0x28, assoc + 0x28);
		low = (uint32_t)(r >> 8) & 0xff;
		hi = (uint32_t)(r >> 0x10) & 0xffff;
		word = (uint32_t)r & 0xff;
		/* ok */
		txm_lock_release(assoc2, 0);
		r2 = txm_verify_cdhash(((low & 0xff) << 8) | (hi << 0x10) | (word & 0xff));
		i = (int)(r2 >> 0x10);
		assoc2 = r2 >> 0x20;
		if ((r2 & 0xffff) != 0) {
			err = (int)(r2 & 0xffff);
			goto out;
		}
		err = 0;
		goto install;
	} else {
		/* JIT-debug object. */
		assoc2 = *(uint64_t *)(obj + 0x40);
		if (assoc2 != 0) {
			txm_lock_acquire(assoc2, 0, 0);
			if (*(uint64_t *)(assoc2 + 0x28) == start &&
			    *(uint64_t *)(assoc2 + 0x30) == end) {
				oah = *(uint64_t *)(assoc2 + 0x18) == base;
			} else {
				oah = 0;
			}
			txm_lock_release(assoc2, 0);
			/* region-authorize fallback */
			r = txm_region_authorize(*(uint8_t *)(obj + 0x20));
			i = (int)(r >> 0x10);
			if ((r & 0xffff) != 0) {
				txm_log("denying executable debug mapping");   /* 0xd65 */
				assoc2 = r >> 0x20;
				err = (int)(r & 0xffff);
				goto out;
			}
			assoc2 = r >> 0x20;
			err = 1;
			goto install;
		}
		txm_ce_bind(assoc + 0x28, (uint64_t *)(obj + 0x20));
		r = txm_region_authorize(*(uint8_t *)(obj + 0x20));
		i = (int)(r >> 0x10);
		if ((r & 0xffff) != 0) {
			txm_log("denying executable debug mapping");   /* 0xd65 */
			assoc2 = r >> 0x20;
			err = (int)(r & 0xffff);
			goto out;
		}
		if ((txm_security_ok(d_code) & 1) == 0) {
			txm_log("disallowed executable debug mapping");   /* 0xd95 */
			assoc2 = r >> 0x20;
			err = 0x2a;
			goto out;
		}
		assoc2 = r >> 0x20;
		err = 1;
		goto install;
	}

install:
	*(uint8_t *)(node + 0x12) = *(uint8_t *)(node + 0x12) & 0x80;
	*(uint64_t *)(node + 0x28) = start;
	*(uint64_t *)(node + 0x30) = end;
	*(uint64_t *)(node + 0x18) = base;
	*(uint64_t *)(node + 0x20) = assoc;
	if (txm_rb_insert((txm_rb_node_t *)(obj + 0x28), node) == 0) {
		cnt = *(uint32_t *)(assoc + 0x14);
		*(uint32_t *)(assoc + 0x14) = cnt + 1;
		if (cnt >= ~txm_link_limit) {
			txm_panic(0x4e);                 /* link overflow */
		}
		if (err != 0) {
			err = 0;
			*(uint64_t *)(obj + 0x40) = node;
		}
	} else {
		err = 0x17;                          /* interval overlap */
	}

out:
	txm_lock_release(obj, 1);
	txm_lock_release(assoc, 0);
	txm_lock_release(node, 1);
	if ((err & 0xffff) != 0) {
		txm_obj_ref_drop(&node, 3, 4);
	}
	return (uint64_t)(uint32_t)(i << 0x10) | (assoc2 << 0x20) | (err & 0xffff);
}

/* FUN_00023050 @ 0x00023050   (est. txm_region_authorize)
 * Ghidra: ulong FUN_00023050(undefined8 flag)
 * Region authorization against the active profile: when the profile (+0x48)
 * permits authorization, runs the per-profile authorizer (FUN_000350e8) over
 * the profile handle and the requested flag; returns the packed status
 * (0x20/0x21 panic 0xf1). Returns 0 when authorization is disabled.
 * Confidence: medium
 */
uint64_t txm_region_authorize(uint64_t flag)
{
	if ((txm_debug_state & 1) == 0) {
		txm_panic(0x19);
	}
	if ((*(uint8_t *)(txm_profile_ctx + 0x48) & 1) == 0) {
		return 0;
	}
	{
		uint64_t r = txm_profile_authorize(txm_profile_handle, flag);
		uint32_t cls = (uint32_t)((r >> 8) & 0xff);
		uint64_t packed;
		if ((r & 0xff00) == 0) {
			packed = 0;
		} else {
			if (cls == 0x20) txm_panic(((uint32_t)r & 0xffff00ff) | 0x2000);
			if (cls == 0x21) txm_panic(((uint32_t)r & 0xffff0000) | ((uint32_t)r & 0xff) | 0x2100);
			packed = 4;
		}
		return packed | ((r >> 0x10) << 0x30) | (((r >> 8) & 0xff) << 0x28) | ((r & 0xff) << 0x20);
	}
}

/* FUN_000230fc @ 0x000230fc   (est. txm_status_repack)
 * Ghidra: ulong FUN_000230fc(ulong status)
 * Re-packs a TXM status word, panicking 0xf1 on the 0x20/0x21 error classes.
 * Pure status normalization helper.
 * Confidence: high (trivial repack)
 */
uint64_t txm_status_repack(uint64_t status)
{
	uint32_t cls = (uint32_t)((status >> 8) & 0xff);
	uint64_t packed;

	if ((status & 0xff00) == 0) {
		packed = 0;
	} else {
		if (cls == 0x20) txm_panic(((uint32_t)status & 0xffff00ff) | 0x2000);
		if (cls == 0x21) txm_panic(((uint32_t)status & 0xffff0000) | ((uint32_t)status & 0xff) | 0x2100);
		packed = 4;
	}
	return packed | ((status >> 0x10) << 0x30) | (((status >> 8) & 0xff) << 0x28) | ((status & 0xff) << 0x20);
}

/* FUN_0002316c @ 0x0002316c   (est. txm_exec_check)
 * Ghidra: undefined8 FUN_0002316c(long obj)
 * Execution-eligibility check for a code object (selector 0x28 path). Requires
 * obj+0x10 non-empty (panic 0x38) and the debug/code-limits state
 * (DAT_00010678+0x4f, DAT_00071035). When enabled: a non-empty association
 * (0x50) is denied (0x19); a free region (+0x24==1) with no prior association
 * is admitted only if the object carries dynamic-codesigning (0xdc6) or
 * allow-jit (0xdda); an already-JIT object (+0x18 bit1) is admitted. Returns 0
 * (allowed), 0x26 (denied), 0x18/0x19.
 * Confidence: high (JIT/exec eligibility; entitlements 0xdc6/0xdda)
 */
uint64_t txm_exec_check(uint64_t obj)
{
	if ((txm_debug_state & 1) == 0) {
		txm_panic(0x19);
	}
	if (*(char *)(obj + 0x10) == '\0') {
		txm_panic(0x38);
	}
	if ((*(uint8_t *)(txm_profile_ctx + 0x4f) & 1) != 0 &&
	    (txm_code_limits & 1) == 0) {
		if (txm_exec_probe() & 1) {
			return 0x18;
		}
		if (*(uint16_t *)(obj + 0x24) == 1) {
			return 0x26;                 /* free region, no JIT */
		}
		if (*(uint64_t *)(obj + 0x50) == 0) {
			if (txm_entitlement_check(obj, 0xdc6, 0) ||
			    txm_entitlement_check(obj, 0xdda, 0)) {
				return 0;                /* dynamic-codesigning / allow-jit */
			}
			if ((*(uint8_t *)(obj + 0x18) & 2) != 0) {
				return 0;                /* JIT bit set */
			}
			return 0x26;
		}
		return 0x19;
	}
	return 0x18;
}

/* FUN_00023254 @ 0x00023254   (est. txm_code_region_associate)
 * Ghidra: ulong FUN_00023254(long obj, ulong start, ulong size)
 * Selector 0x28 handler: creates a code region for [start, start+size) on the
 * object. Validates 16K alignment (0x7d/0x7e) and non-empty/overflow bounds
 * (0x40/0x41/0x42), allocates a region node, checks execution eligibility via
 * txm_exec_check (must be 0), installs the node into the object's interval tree
 * (overlap -> 0x17), and links it at obj+0x50. Returns 0 or 7 (alloc failure).
 * Confidence: high (code-region association; selector 0x28)
 */
uint64_t txm_code_region_associate(uint64_t obj, uint64_t start, uint64_t size)
{
	uint64_t end = start + size;
	uint64_t node, st;

	if ((start & 0x3fff) != 0) txm_panic(0x7d);
	if ((size & 0x3fff) != 0) txm_panic(0x7e);
	if (start == 0) txm_panic(0x40);
	if (size == 0) txm_panic(0x41);
	if (end < start) txm_panic(0x42);          /* CARRY8 */

	node = txm_region_new();
	if (node == 0) {
		return 7;
	}
	txm_lock_acquire(node, 1, 0);
	txm_lock_acquire(obj, 1, 0);
	st = txm_exec_check(obj);
	if (st == 0) {
		*(uint8_t *)(node + 0x12) = (*(uint8_t *)(node + 0x12) & 0x80) | 2;
		*(uint64_t *)(node + 0x28) = start;
		*(uint64_t *)(node + 0x30) = end;
		if (txm_rb_insert((txm_rb_node_t *)(obj + 0x28), node) == 0) {
			st = 0;
			*(uint64_t *)(obj + 0x50) = node;
		} else {
			st = 0x17;                           /* interval overlap */
		}
	}
	txm_lock_release(obj, 1);
	txm_lock_release(node, 1);
	if ((int)st != 0) {
		txm_obj_ref_drop(&node, 3, 4);
	}
	return st & 0xffffffff;
}

/* FUN_00023384 @ 0x00023384   (est. txm_cs_debug_policy)
 * Ghidra: undefined8 FUN_00023384(long obj, ulong start, ulong size)
 * Selector 0x2a handler: code-signing / debug-mapping policy. Requires the
 * debugger entitlement (cs.debugger 0xc79) OR the page-state flag DAT_000107f5;
 * otherwise logs "disallowed non-debugger initiated debug mapping" (0xdfb) and
 * returns 0x25. It then scans the object's existing regions for any that
 * overlap/contain [start,end) and marks one (|0x80) to reject the duplicate,
 * else inserts a new 0x83-flagged node (overlap -> panic 0xd1). Sets a debug
 * marker on the object (+0x30).
 * Confidence: high (code-signing/debug-mapping policy; string 0xdfb)
 */
uint64_t txm_cs_debug_policy(uint64_t obj, uint64_t start, uint64_t size)
{
	uint64_t end = start + size;
	uint64_t node, st, scan;
	int dir;

	if ((start & 0x3fff) != 0) txm_panic(0xc4);
	if ((size & 0x3fff) != 0) txm_panic(0xc5);
	if (start == 0) txm_panic(0x40);
	if (size == 0) txm_panic(0x41);
	if (end < start) txm_panic(0x42);

	if ((txm_entitlement_check(0, 0xc79, 0) & 1) == 0 && (txm_page_er_flag & 1) == 0) {
		txm_log("disallowed non-debugger initiated debug mapping");   /* 0xdfb */
		return 0x25;
	}

	node = txm_region_new();
	if (node == 0) {
		return 7;
	}
	txm_lock_acquire(node, 1, 0);
	txm_lock_acquire(obj, 1, 0);

	if ((*(uint8_t *)(obj + 0x30) & 1) == 0) {
		txm_panic(0x1d);
	}

	/* Scan the object's regions; if one already covers [start,end), mark it
	 * and reject the duplicate. */
	for (scan = *(uint64_t *)(obj + 0x28); scan != 0; ) {
		if (start < *(uint64_t *)(scan + 0x28) && end <= *(uint64_t *)(scan + 0x28)) {
			dir = 0x38;
		} else if (start < *(uint64_t *)(scan + 0x30) || end <= *(uint64_t *)(scan + 0x30)) {
			txm_lock_acquire(scan, 1, 0);
			*(uint8_t *)(scan + 0x12) |= 0x80;
			if (scan + 0x50 <= scan) txm_panic(0x19);
			txm_lock_release(scan, 1);
			return 0;
		} else {
			dir = 0x40;
		}
		scan = *(uint64_t *)(scan + dir);
	}

	*(uint8_t *)(node + 0x12) = 0x83;
	*(uint64_t *)(node + 0x28) = start;
	*(uint64_t *)(node + 0x30) = end;
	if (txm_rb_insert((txm_rb_node_t *)(obj + 0x28), node) != 0) {
		txm_panic(0xd1);                         /* overlap */
	}
	txm_lock_release(obj, 1);
	txm_lock_release(node, 1);
	return 0;
}

/* FUN_00023574 @ 0x00023574   (est. txm_entitlement_policy)
 * Ghidra: undefined8 FUN_00023574(long obj)
 * Selector 0x29 handler: entitlement / debug-mode policy query. Requires the
 * code-limits flag (DAT_00071034). Grants the debug bit (obj+0x30=1) when the
 * profile has license-to-operate (0xe2b, gated on DAT_000104ed) OR the object
 * has get-task-allow (0xe51) OR DAT_000107f5; otherwise returns 0x1d. A
 * free-region object panics 0x81.
 * Confidence: high (entitlement query; 0xe2b/0xe51)
 */
uint64_t txm_entitlement_policy(uint64_t obj)
{
	uint8_t lto;

	if ((txm_code_limits & 1) == 0) {
		return 0x1b;
	}
	lto = txm_entitlement_check(0, 0xe2b, 0);      /* license-to-operate */
	txm_lock_acquire(obj, 0, 0);
	if (*(uint16_t *)(obj + 0x24) == 1) {
		txm_panic(0x81);
	}
	if ((((lto & txm_ent_lo_flag & 1) == 0) &&
	     (txm_entitlement_check(obj, 0xe51, 0) & 1) == 0) &&
	    (txm_page_er_flag & 1) == 0) {
		txm_lock_release(obj, 0);
		return 0x1d;
	}
	*(uint8_t *)(obj + 0x30) = 1;
	txm_lock_release(obj, 0);
	return 0;
}

/* FUN_0002364c @ 0x0002364c   (est. txm_get_associated_obj)
 * Ghidra: long FUN_0002364c(long obj, long *assoc_out)
 * Returns the object's associated code object (the association node's backing
 * object, +0x20). Resolves obj+0x40 via txm_rb_node_to_obj; returns 8 if the
 * association is empty, 0 on success (optionally via *assoc_out).
 * Confidence: medium
 */
long txm_get_associated_obj(uint64_t obj, uint64_t *assoc_out)
{
	uint64_t assoc = 0;
	uint64_t node;

	txm_lock_acquire(obj, 0, 0);
	node = *(uint64_t *)(obj + 0x40);
	if (txm_rb_node_to_obj(node, &assoc, 0) != 0) {
		txm_lock_release(obj, 0);
		return 8;
	}
	assoc = *(uint64_t *)(assoc + 0x20);
	txm_lock_release(assoc, 0);
	txm_lock_release(obj, 0);
	if (assoc == 0) {
		return 8;
	}
	if (assoc_out != 0) {
		*assoc_out = assoc;
	}
	return 0;
}

/* FUN_000236f0 @ 0x000236f0   (est. txm_secure_channel_init)
 * Ghidra: void FUN_000236f0(void)
 * Secure-channel (SecureUI) initialization. Single-init (re-init panics 0xe60
 * "attempted to initialize secure channel again"). Reads the platform feature
 * and flag (FUN_0002a354/FUN_0002a434); when the feature is absent (or the boot
 * flag DAT_000104f0 is set) it gates on SEP presence — a security-boot mode
 * without SEP panics ("security boot mode without SEP...", 0x1141) — and on
 * boot state 5/6 allocates the 16 KiB shared page (DAT_00010518/520/528),
 * marks it ready (DAT_00071030) and bootstraps (FUN_00023840/78/ec) after
 * "setup the shared page for the secure channel" (0xebb). Unsupported boot
 * states log 0xe8d "secure channel not supported on this platform".
 * Confidence: high (strings 0xe60/0xe8d/0xebb explicit)
 */
void txm_secure_channel_init(void)
{
	uint64_t feat, flag, page, r;
	int sep;

	if (txm_sc_page_base != 0) {
		txm_panic(0xe60);                          /* re-init */
	}
	txm_sc_cap = (uint8_t)txm_platform_feature();  /* FUN_0002a354 */
	flag = txm_platform_flag();                    /* FUN_0002a434 */
	txm_sc_flag = (uint8_t)flag;
	if (flag == 0 || (txm_boot_flag & 1) != 0) {
		if ((flag & txm_sc_cap) != 1) {
			sep = txm_sep_present();
			if ((txm_sc_cap & 1) == 0 && sep != 0) {
				txm_panic(0x1141);                 /* security boot without SEP */
			}
			txm_sc_sep = (uint8_t)sep;
			if (4 < txm_boot_state - 1 && txm_boot_state != 7) {
				txm_log("secure channel not supported on this platform");  /* 0xe8d */
				return;
			}
			txm_sc_ready = 1;
			txm_alloc_zone(&page, 0x4000, 0x3d);
			txm_sc_page_size = page_size_word;
			txm_sc_page_base = page;
			txm_sc_page_extra = page_extra_word;
			r = txm_setup_shared_page();
			if ((int)r == 0) {
				txm_log("setup the shared page for the secure channel");  /* 0xebb */
				flag = txm_sc_sep - 1;
				txm_sc_bootstrap_a();
				txm_sc_bootstrap_b(flag < 7);
				txm_sc_bootstrap_c();
				return;
			}
			txm_panic(0xf3, r);
		}
		txm_panic(0xd3);
	}
	txm_panic(0xd2);
}

/* FUN_00023840 @ 0x00023840   (est. txm_sc_setup_step1)
 * Ghidra: void FUN_00023840(void)
 * Secure-channel bootstrap step 1: if the channel is ready, arm the shared
 * page (FUN_0002f5a0); error panics 0xf3.
 * Confidence: medium
 */
void txm_sc_setup_step1(void)
{
	if ((txm_sc_ready & 1) != 0) {
		uint64_t r = txm_sc_step(0);
		if ((int)r != 0) {
			txm_panic(0xf3, r);
		}
	}
}

/* FUN_00023878 @ 0x00023878   (est. txm_sc_setup_step2)
 * Ghidra: void FUN_00023878(ulong flag)
 * Secure-channel bootstrap step 2: enables the lockdown marker (DAT_00071033)
 * when `flag` is set, configures the channel (FUN_0002f5e0), logs the SecureUI
 * state (0xf2c), and clears the lockdown marker if the flag bit 0 is clear.
 * Confidence: medium
 */
void txm_sc_setup_step2(uint64_t flag)
{
	if ((txm_sc_ready & 1) != 0) {
		if ((int)flag != 0) {
			txm_sc_lockdown = 1;
		}
		uint64_t r = txm_sc_config(flag);
		if ((int)r != 0) {
			txm_panic(0xf3, r);
		}
		txm_log("system SecureUI state: %u");    /* 0xf2c */
		if ((flag & 1) == 0) {
			txm_sc_lockdown = 0;
		}
	}
}

/* FUN_000238ec @ 0x000238ec   (est. txm_sc_setup_step3)
 * Ghidra: void FUN_000238ec(void)
 * Secure-channel bootstrap step 3: when the channel is ready, the boot flag
 * (DAT_000104f0) is set, and the platform flag (DAT_00071032) is set, records
 * the SCRD state 0x15c01 into DAT_0007103c (preserving the high bits).
 * Confidence: medium
 */
void txm_sc_setup_step3(void)
{
	if (((txm_sc_ready & 1) != 0) && (txm_boot_flag & 1) != 0 &&
	    (txm_sc_flag & 1) != 0) {
		txm_scrd = (txm_scrd & 0xfffe0000) | 0x15c01;
	}
}

/* FUN_00023930 @ 0x00023930   (est. txm_sc_report)
 * Ghidra: void FUN_00023930(void)
 * Reads and reports the SCRD magic/xART (strings 0xee8 "SecureChannel: SCRD |
 * Magic: 0x%04X" and 0xf0c "SecureChannel: SCRD | xART: %u") when the SCRD low
 * word is empty. Error panics 0xf3.
 * Confidence: high (strings 0xee8/0xf0c explicit)
 */
void txm_sc_report(void)
{
	if ((uint16_t)txm_scrd == 0) {
		uint64_t r = txm_scrd_read(&txm_scrd);
		if ((int)r != 0) {
			txm_panic(0xf3, r);
		}
		txm_log("SecureChannel: SCRD | Magic: 0x%04X");   /* 0xee8 */
		txm_log("SecureChannel: SCRD | xART: %u");        /* 0xf0c */
	}
}

/* FUN_000239a8 @ 0x000239a8   (est. txm_sc_report_handle)
 * Ghidra: void FUN_000239a8(void)
 * Reports the profile handle to the secure channel (FUN_0002f660) when ready;
 * error panics 0xf3.
 * Confidence: medium
 */
void txm_sc_report_handle(void)
{
	if ((txm_sc_ready & 1) != 0) {
		uint64_t r = txm_sc_handle(txm_profile_handle == -1);
		if ((int)r != 0) {
			txm_panic(0xf3, r);
		}
	}
}

/* FUN_000239f8 @ 0x000239f8   (est. txm_sc_report_entitlement)
 * Ghidra: void FUN_000239f8(void)
 * Reports the license-to-operate entitlement (DAT_000104ed bit0) to the secure
 * channel (FUN_0002f6a0) when ready; error panics 0xf3.
 * Confidence: medium
 */
void txm_sc_report_entitlement(void)
{
	if ((txm_sc_ready & 1) != 0) {
		uint64_t r = txm_sc_ent(txm_ent_lo_flag & 1);
		if ((int)r != 0) {
			txm_panic(0xf3, r);
		}
	}
}

/* FUN_00023a40 @ 0x00023a40   (est. txm_developer_mode)
 * Ghidra: void FUN_00023a40(long ctx)
 * Computes and stores the developer-mode state (DAT_00071034). Developer mode
 * is on when the boot flag DAT_000107f6 is set, or the profile flag
 * (DAT_00010678+0x4d) is clear, or (boot state 7) the license-to-operate
 * entitlement, or the SCRD lockdown/demo bits admit it, else based on the
 * context's developer-mode bit. Logs the mode strings (0xf46/0xf80/0xfb1/
 * 0x1019/0x104c/0xfe2) and propagates to the secure channel (FUN_0002f620).
 * Confidence: medium (developer-mode logic; string refs explicit)
 */
void txm_developer_mode(uint64_t ctx)
{
	uint64_t mode;

	if ((txm_dev_mode_flag & 1) != 0) {
		mode = 1;
	} else if ((*(uint8_t *)(txm_profile_ctx + 0x4d) & 1) == 0) {
		txm_log("developer mode forced");                    /* 0xf46 */
		mode = 1;
	} else if (txm_boot_state == 7) {
		if ((txm_ent_lo_flag & 1) == 0) {
			txm_log("developer mode disabled (no license)"); /* 0xfb1 */
		} else {
			txm_log("developer mode enabled by license");    /* 0xf80 */
		}
		mode = txm_ent_lo_flag;
	} else if ((txm_scrd & 0xffff) == 0 || (txm_scrd & 0x10000) != 0) {
		mode = 0;
		if (ctx == 0 || (txm_scrd & 0xffff) == 0) {
			/* default off */
		} else if ((*(uint8_t *)(ctx + 0xc) & 1) == 0) {
			mode = 0;
			if ((txm_sc_lockdown & 1) == 0) {
				txm_log("developer mode disabled based on %s");  /* 0x104c */
			}
		} else {
			txm_log("developer mode enabled based on %s");  /* 0x1019 */
			mode = 1;
		}
	} else {
		txm_log("developer mode lockdown");                   /* 0xfe2 */
		mode = 1;
	}

	if ((txm_sc_ready & 1) != 0) {
		uint64_t r = txm_sc_devmode((int)(mode & 1));
		if ((int)r != 0) {
			txm_panic(0xf3, r);
		}
	}
	txm_code_limits = mode & 1;         /* DAT_00071034 */
}

/* FUN_00023b50 @ 0x00023b50   (est. txm_lockdown)
 * Ghidra: undefined8 FUN_00023b50(void)
 * Lockdown/demo-mode readout: when the secure channel is ready, reads the SCRD
 * (FUN_00023930) and either (a) the SCRD is not lockdown-armed — requires no
 * SEP (panic 0x12) then developer mode, or (b) reads the lockdown context
 * (FUN_0002f454), computes developer mode from it, and records lockdown mode
 * (DAT_00071035) and demo mode (DAT_00071036), logging both (0x1080/0x10a2).
 * Returns 0 with a stack-canary check (DAT_00006cf0).
 * Confidence: high (strings 0x1080/0x10a2 explicit)
 */
uint64_t txm_lockdown(void)
{
	uint64_t guard = txm_canary;
	uint64_t ctx_buf[4] = { 0, 0, 0, 0 };

	if ((txm_sc_ready & 1) != 0) {
		txm_sc_report();
		if (((txm_scrd >> 0x10) & 1) == 0) {
			if (txm_sc_sep != 0) {
				txm_panic(0x12);
			}
			txm_developer_mode(0);
		} else {
			uint64_t r = txm_scrd_context(ctx_buf);
			if ((int)r != 0) {
				txm_panic(0xf3, r);
			}
			txm_developer_mode((uint64_t)ctx_buf);
			txm_lockdown_mode = (ctx_buf[1] != 0);
			txm_log("SecureChannel: Lockdown Mode: %u");   /* 0x1080 */
			txm_demo_mode = (ctx_buf[2] != 0);
			txm_log("SecureChannel: Demo Mode: %u");       /* 0x10a2 */
		}
	}
	if (txm_canary != guard) {
		txm_stack_guard_fail(0);
	}
	return 0;
}

/* FUN_00023c50 / 00023c98 @ 0x00023c50  (est. txm_sc_verify_signature)
 * Ghidra: undefined8 FUN_00023c50(undefined8 sig, undefined8 p1, undefined8 p2)
 * SCVerifySignature for developer authorization. When the secure channel is
 * ready, verifies the developer signature via FUN_0002f1b0; on failure logs
 * "SCVerifySignature for developer authorization: %u" (0x10c0). When the
 * channel is not ready, panics 0xf3.
 * Confidence: high (string 0x10c0 explicit)
 */
uint64_t txm_sc_verify_signature(uint64_t sig, uint64_t p1, uint64_t p2)
{
	uint64_t ab[2] = { p1, p2 };
	uint64_t r;

	if ((txm_sc_ready & 1) != 0) {
		r = txm_sc_verify(0, ab, sig);
		if ((int)r != 0) {
			txm_log("SCVerifySignature for developer authorization: %u");   /* 0x10c0 */
		}
		return r;
	}
	txm_panic(0xf3, 1);
}

/* FUN_00023cc4 @ 0x00023cc4   (est. txm_security_ok)
 * Ghidra: byte FUN_00023cc4(undefined8 id)
 * Checks whether an identifier `id` is in the allowed list (DAT_000100b8, 4
 * entries of 8 bytes). Only consulted when the channel is ready and the SCRD
 * low word is empty; if the capability bit (DAT_00071031) is clear, always
 * allowed; otherwise returns the match flag DAT_000107f8 for a matching entry
 * or 1 for none.
 * Confidence: medium
 */
uint8_t txm_security_ok(uint64_t id)
{
	uint64_t i;

	if ((txm_sc_ready & 1) != 0 && (uint16_t)txm_scrd == 0) {
		if ((txm_sc_cap & 1) == 0) {
			return 1;
		}
		for (i = 0; i < 0x20; i += 8) {
			if (txm_uuid_compare((const void *)*(uint64_t *)((uint64_t)&txm_allowed_id_list + i),
			                     id) == 0) {
				return txm_match_flag;           /* DAT_000107f8 */
			}
		}
		return 1;
	}
	return 1;
}

/* FUN_00023d64 @ 0x00023d64   (est. txm_sc_enter)
 * Ghidra: void FUN_00023d64(undefined8 p1, undefined8 p2)
 * Enters the secure channel with a two-word argument (FUN_0002f220) when ready;
 * error panics 0xf3.
 * Confidence: medium
 */
void txm_sc_enter(uint64_t p1, uint64_t p2)
{
	uint64_t ab[2] = { p1, p2 };

	if ((txm_sc_ready & 1) != 0) {
		uint64_t r = txm_sc_enter_impl(ab);
		if ((int)r != 0) {
			txm_panic(0xf3, r);
		}
	}
}

/* FUN_00023dac @ 0x00023dac   (est. txm_sc_exit)
 * Ghidra: void FUN_00023dac(undefined8 p)
 * Exits the secure channel (FUN_0002f3c8), requiring the channel be ready
 * (panic 0xf3) and the exit flag be set (panic 0x2e otherwise); errors panic
 * 0xf3.
 * Confidence: medium
 */
void txm_sc_exit(uint64_t p)
{
	uint8_t flag = 0;
	uint64_t r;

	if ((txm_sc_ready & 1) == 0) {
		txm_panic(0xf3, 1);
	}
	r = txm_sc_exit_impl(p, &flag);
	if ((int)r == 0) {
		if ((flag & 1) != 0) {
			return;
		}
		txm_panic(0x2e);
	}
	txm_panic(0xf3, r);
}

/* FUN_00023e14 @ 0x00023e14   (est. txm_build_info)
 * Ghidra: undefined1 [16] FUN_00023e14(void)
 * Build/configuration reporting: marks boot complete (DAT_000104e8), performs
 * early boot (FUN_0002940c), writes the build-variant and platform identifiers
 * (FUN_0004f2dc), prints the version (FUN_00029714) and the fusing/
 * virtualized/build-type/device-type/research-configuration strings, then
 * returns to the caller (FUN_0002ab70). Returns a 16-byte config descriptor
 * {pointer, length} derived from DAT_00070ecc/ecd/ece.
 * Confidence: medium
 */
txm_u128_t txm_build_info(void)
{
	uint64_t ptr = 0, len = 0;

	txm_boot_e8 = 1;
	txm_early_boot(0);
	txm_sys_write(0, &build_variant_id, 2);
	txm_sys_write(1, &platform_id, 1);
	txm_build_version();
	txm_log("build variant: %s");                  /* 0x1169 */
	txm_log("fusing: 0x%08X");                     /* 0x117b */
	txm_log("virtualized: %u");                    /* 0x118a */
	txm_log("build type: %u");                     /* 0x119a */
	txm_log("device type: %u");                    /* 0x11a9 */
	txm_log("research configuration: %u");         /* 0x11b9 */
	txm_log("extended research configuration: %u");/* 0x11d4 */
	txm_return_exit(txm_ctx_return);

	if ((txm_build_cfg0 & 1) != 0) {
		if ((txm_build_cfg1 & 1) != 0) {
			ptr = (uint64_t)&txm_build_cfg2;
			len = 0x61;
		}
	}
	return (txm_u128_t){ .lo = ptr, .hi = len };
}

/* FUN_00023f14 @ 0x00023f14   (est. txm_build_info_inner)
 * Ghidra: undefined1 [16] FUN_00023f14(void)
 * Returns the 16-byte build-config descriptor {pointer, length} from the build
 * configuration globals, or zero when not configured.
 * Confidence: medium
 */
txm_u128_t txm_build_info_inner(void)
{
	uint64_t ptr = 0, len = 0;

	if ((txm_build_cfg0 & 1) != 0) {
		if ((txm_build_cfg1 & 1) != 0) {
			ptr = (uint64_t)&txm_build_cfg2;
			len = 0x61;
		}
	}
	return (txm_u128_t){ .lo = ptr, .hi = len };
}

/* FUN_00023f54 @ 0x00023f54   (est. txm_lockdown_mode_enter)
 * Ghidra: void FUN_00023f54(void)
 * Enters lockdown mode for the current session: panics 0x2c if the boot flag
 * DAT_000104ea is set; clears the lockdown flag (DAT_00010667) unless armed
 * (DAT_000107f7) and resets DAT_00010661, then logs "entered lockdown mode for
 * the re..." (0x11f8).
 * Confidence: medium
 */
void txm_lockdown_mode_enter(void)
{
	if ((txm_page_state_hi & 1) != 0) {
		txm_panic(0x2c);
	}
	if ((txm_lockdown_armed & 1) == 0) {
		txm_lockdown_flag = 0;                   /* DAT_00010667 */
	}
	txm_lockdown_entered = 0;                    /* DAT_00010661 */
	txm_log("entered lockdown mode for the re...");   /* 0x11f8 */
}

#endif /* __ASSEMBLER__ */


