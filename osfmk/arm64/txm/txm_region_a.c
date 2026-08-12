/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0), Apple's code-signing / entitlement /
 * trust-cache / code-execution-policy authority. Ground truth: Ghidra FUN_
 * names + addresses in `txm.raw`. All names are estimates unless a string /
 * header name matches (confidence high). TXM = Trusted Execution Monitor GL0,
 * image base 0.
 *
 * This file covers the trust-cache / code-signing element-parser region
 * 0x4b000-0x56000 (batch T5): the TLV/element reader core (FUN_0004b0ac
 * family), the trust-cache (CT) header + hash-array parsers (FUN_0004b80c,
 * FUN_0004b3a8, FUN_0004b49c), the per-entry hash/entitlement extractors
 * (FUN_0004c1a0..FUN_0004c7b8 family), the CT record decode/lookup
 * (FUN_0004cec4..FUN_0004d2a0), the record-association / policy tables
 * (FUN_0004d498..FUN_0004e258), and the image4/trap-handler table entries
 * (0x53cd4 + area).
 *
 * Shared kernel/hardware deps are declared extern with a one-line note.
 */

#ifndef __ASSEMBLER__
#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------------------ */
/* Shared TXM runtime primitives (extern; bodies in sibling files)    */
/* ------------------------------------------------------------------ */

extern void txm_stack_check_fail(void) __attribute__((noreturn));
extern void txm_fault_impl(uint32_t code, uint64_t addr) __attribute__((noreturn));
#define txm_fault(code, addr) txm_fault_impl((uint32_t)(code), (uint64_t)(addr))
extern uint64_t txm_canary;                 /* DAT_00006cf0 */
extern int txm_tlv_read(uint64_t *rng, uint64_t tag, uint64_t *len);
extern int txm_memcmp(const void *a, const void *b, uint64_t len);
extern int txm_read_le64(uint64_t *rng, uint64_t *out, uint64_t *consumed);
extern int txm_tlv_read_varint(uint64_t *rng, uint64_t *out);
extern void txm_bad_tailq(const char *msg) __attribute__((noreturn));
extern void txm_panic(const char *fmt, ...) __attribute__((noreturn));
extern void txm_memzero(void *dst, uint64_t len);

/* CDHash algorithm OID constants (DER, txm.raw .rodata). */
static const uint8_t TXM_CDHASH_SHA256[] = {0x2a,0x86,0x48,0x86,0xf7,0x63,0x64,0x06,0x02,0x01}; /* 0xa031? -> SHA-256 */
static const uint8_t TXM_CDHASH_SHA384[] = {0x30,0x31,0x30,0x0d,0x06,0x09,0x2a,0x86,0x48,0x86,0xf7,0x0d,0x01,0x01,0x0b,0x05,0x00}; /* placeholder */

/* out-of-batch extern callees (below 0x4b000 / sibling region) */
extern uint8_t txm_validate_sha256(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e);   /* FUN_000483a8 */
extern uint8_t txm_validate_sha384(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e);   /* FUN_00048700 */
extern void txm_cs_sha256_digest(uint64_t *out);                                                   /* FUN_000439e0 */
extern void txm_cs_sha384_digest(uint64_t *out);                                                   /* FUN_000439b0/c0 */
extern void txm_cs_finish(uint64_t *ctx);                                                          /* FUN_0003f9a8 / 0x37f5c */
extern uint64_t txm_cs_ctx_alloc(uint64_t size);                                                   /* FUN_0002ee48 / 0x43c50 */

/* forward decls of this-region functions */
static uint64_t txm_ct_record_decode(uint64_t *rec, uint64_t *rng,
                                     uint64_t hc_a, uint64_t hc_b);
static uint64_t txm_ct_resolve_hash_type(uint64_t *flags, uint64_t tag,
                                         uint64_t *out, uint64_t *len);
static uint64_t txm_dbac_entitlements(uint64_t *rng, uint64_t *flags, uint64_t *raw);
static uint64_t txm_dcf8_sha384(uint64_t *rng, uint64_t *flags, uint64_t *raw);
static void txm_record_get_hash_bitmap(uint64_t rec, uint64_t *out_ptr, uint64_t *out_len);
static void txm_record_drop(uint64_t rec);          /* FUN_00047dec */
static void txm_record_promote(uint64_t *policy, uint64_t rec); /* FUN_00047efc */
static uint64_t txm_ct_lookup_cached_ret(uint32_t want, uint64_t rec, uint64_t h, uint64_t a, uint64_t b);
static uint64_t txm_ct_lookup_2(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f);
static uint64_t txm_dt_property_find(int *node, uint64_t key, uint64_t *out,
                                     uint32_t *out_len, int *base, uint64_t size);
static int *txm_dt_child(uint64_t *root, int *node);
static uint64_t txm_ops_init(uint64_t a, uint64_t ops);
static uint64_t txm_ops_alloc(uint64_t ops);
static void txm_object_release(uint64_t *slot);
static void txm_digest_len_panic(void) __attribute__((noreturn));
static void txm_panic_msg(uint64_t msg) __attribute__((noreturn));
static void txm_panic_illegal_chip_config(void) __attribute__((noreturn));
static void txm_panic_illegal_chip_def(void) __attribute__((noreturn));
static void txm_panic_unreachable(void) __attribute__((noreturn));
static void txm_panic_illegal_chip_def_c(void) __attribute__((noreturn));
static uint64_t txm_user_buffer_map(uint64_t ctx, uint64_t a, uint64_t ptr, uint64_t len,
                                    uint64_t max, uint64_t out);
static void txm_panic_boot_expert(void) __attribute__((noreturn));
static uint64_t txm_pa_resolve(uint64_t pa, uint64_t *out);   /* FUN_00061ea4 */
extern void CallSupervisor(int svc);

/* out-of-batch image4-engine callees (sibling regions) */
extern uint64_t txm_ctx_save(void);                              /* FUN_0005077c */
extern void txm_ctx_finish(uint64_t *ctx);                       /* FUN_00054848/a8 */
extern void txm_log_error(uint64_t a, int b, const char *fmt, ...); /* FUN_000585b8 */
extern uint64_t txm_obj_sub_init(uint64_t a, uint16_t *sub);     /* FUN_00057d68 */
extern void txm_obj_sub_copy(uint64_t dst, uint64_t src);        /* FUN_00057b58 */
extern uint64_t txm_manifest_parse(uint64_t *out, uint64_t raw, uint64_t ops30, uint64_t a3); /* FUN_0005aa8c */
extern uint64_t txm_payload_parse(uint64_t *out, uint64_t raw, uint64_t size);                 /* FUN_00059854 */
extern void txm_manifest_digest(uint64_t man, uint64_t a, int b);  /* FUN_0005aad8 */
extern uint64_t txm_manifest_validate(uint64_t man);              /* FUN_0005aae4 */
extern uint64_t txm_payload_validate(uint64_t pay);               /* FUN_000598bc */
extern uint64_t txm_payload_decode(uint64_t raw, uint64_t parsed, uint64_t man, int b); /* FUN_00059a54 */
extern uint64_t txm_manifest_decode(uint64_t man, uint64_t *out); /* FUN_0005ace8 */
extern uint64_t txm_payload_decode_v2(uint64_t pay, uint64_t *out); /* FUN_000599e4 */
extern void txm_manifest_free(uint64_t *man);                     /* FUN_0005ad14 */
extern void txm_payload_free(uint64_t *pay);                      /* FUN_00059fe8 */
extern void txm_fault_check_pac(void);                            /* SoftwareBreakpoint 0xc471 */

/* image4/crypto/DeviceTree out-of-batch helpers (sibling regions) */
static uint64_t txm_dt_chosen_get(uint64_t iodev, uint64_t a, uint64_t b, uint64_t *out, uint64_t *size); /* FUN_00050f9c */
extern uint64_t txm_iodev_get(void);                                 /* FUN_0005464c */
extern uint64_t txm_ctx_ops(void);                                   /* FUN_000507b0 */
extern void txm_expert_announce(void);                               /* FUN_00055da4 */
extern void txm_expert_parse(void);                                  /* FUN_00057eb0 */
extern void txm_expert_setup(uint64_t ctx, uint64_t obj, uint64_t ops); /* FUN_000507c0 */
extern int txm_expert_validate(uint64_t obj);                        /* FUN_00057ec0 */
extern void txm_expert_finish(uint64_t obj);                         /* FUN_0002abe4 */
extern uint64_t txm_expert_name(uint64_t obj);                       /* FUN_00057f7c */
extern void txm_obj_tag(uint64_t ctx, uint64_t tag, const char *msg); /* FUN_00057e10 */
extern void txm_ctx_tag(uint64_t ctx, uint64_t tag, const char *msg); /* FUN_00057e10 */
extern int txm_str_eq(uint64_t a, uint64_t b);                       /* FUN_0002d990 */
extern void txm_img4_no_digest(char *out, uint64_t a, uint64_t len, uint64_t b); /* FUN_0002efc4 */
extern int txm_img4_manifest_init(uint64_t base, uint64_t len, uint64_t *man);  /* FUN_000579c8 */
extern int txm_img4_parse_section(uint64_t *man, const char *name, uint64_t *v, uint64_t *h); /* FUN_00045220 */
extern uint64_t txm_img4_section_u64(uint64_t *man, uint64_t a, const char *name, uint64_t *v); /* FUN_00045190 */
extern uint64_t txm_img4_err(uint64_t e);                            /* FUN_0005793c */
extern uint64_t txm_img4_install_hash(uint64_t base, uint64_t v, uint64_t len); /* FUN_00057b58 */
extern void txm_img4_hash_finalize(uint64_t h, uint64_t p);         /* FUN_00057ca8 */
extern void txm_img4_hash_copy(uint64_t out, uint64_t src);          /* FUN_000522d8 */
extern uint64_t txm_obj_resolve(uint64_t obj, int b);                /* FUN_0005860c */
extern uint64_t txm_obj_prop_lookup(uint64_t base, uint64_t key);    /* FUN_00056e90 */
extern void txm_obj_prop_set(uint64_t base, uint64_t key, uint64_t v);  /* FUN_00057264 */
extern void txm_obj_prop_set_v2(uint64_t base, uint64_t key, uint64_t v); /* FUN_00057318 */
extern void txm_obj_prop_set_v3(uint64_t base, uint64_t key, uint64_t v); /* FUN_000573c8 */
extern void txm_obj_prop_set_v4(uint64_t base, uint64_t key, uint64_t v); /* FUN_00057478 */
extern void txm_obj_prop_set_v5(uint64_t base, uint64_t key, uint64_t v); /* FUN_0005753c */
extern uint64_t txm_manifest_hash_resolve(uint64_t ctx, uint64_t array);   /* FUN_00052a34 */
extern void txm_bc_ctx_build(uint64_t a, uint64_t b, uint64_t *out); /* FUN_00059e14 */
extern uint64_t txm_bc_verify(uint64_t *p, uint64_t a, uint64_t h, uint64_t *ctx); /* FUN_0005c230 */
extern void txm_bc_ctx_release(uint64_t ctx);                        /* FUN_00042b84 */
extern uint64_t txm_expert_list_next(uint64_t *cur);                 /* FUN_000566b8 */
extern uint64_t txm_manifest_set_prop_special(uint64_t obj, uint64_t a, uint64_t v); /* FUN_000591d8 */
extern uint64_t FUN_00022a38(uint64_t a, uint64_t b, uint64_t c);
extern void FUN_00025c6c(uint64_t a);
extern int FUN_0005861c(uint64_t a, uint64_t b, uint64_t c, uint8_t *out);   /* expert query type 0 */
extern int FUN_000587f0(uint64_t a, uint64_t b, uint64_t c, uint8_t *out);   /* type 1 */
extern int FUN_000589bc(uint64_t a, uint64_t b, uint64_t c, uint8_t *out);   /* type 2 */
extern int FUN_00058b88(uint64_t a, uint64_t b, uint64_t c, uint8_t *out);   /* type 3 */
extern int FUN_00058d18(uint64_t a, uint64_t b, uint64_t c, uint8_t *out);   /* type 4 */
extern void FUN_00056f04(uint64_t a, uint64_t b, uint8_t *in);   /* expert apply type 0 */
extern void FUN_00056fac(uint64_t a, uint64_t b, uint8_t *in);   /* type 1 */
extern void FUN_00057050(uint64_t a, uint64_t b, uint8_t *in);   /* type 2 */
extern void FUN_000570f4(uint64_t a, uint64_t b, uint8_t *in);   /* type 3 */
extern void FUN_000571ac(uint64_t a, uint64_t b, uint8_t *in);   /* type 4 */
extern void FUN_00058fd0(uint64_t a, char *hex, uint64_t b, uint64_t c);  /* digest report */
extern void FUN_00058fe0(uint64_t a, char *hex, uint64_t b, uint64_t c);  /* digest report v2 */
extern void FUN_00051c10(char *buf, uint64_t len);               /* zero buffer */
extern void FUN_00051c50(uint64_t a);                            /* magazine name err */
extern void FUN_00051c90(uint64_t item);                         /* cryptex item init */
extern void txm_img4_hash_to_hex(char *out, uint64_t len);       /* digest -> hex */
extern void txm_img4_hash_copy2(uint64_t out, uint64_t src, uint64_t *len); /* hash copy w/ len */
extern uint64_t txm_str_len(uint64_t s);                         /* strlen */

/* nonce/magazine out-of-batch helpers */
extern uint64_t FUN_00054024(void);                             /* default name */
extern uint64_t FUN_00054034(uint64_t name);                    /* name deref */
extern uint64_t FUN_00054074(uint64_t obj, uint64_t *slot);     /* nonce resolve */
extern void FUN_0005a6e4(uint64_t out, uint64_t src);           /* nonce copy */
extern uint64_t FUN_0005bef0(uint64_t ctx, uint64_t a, uint32_t type, uint64_t *d, uint64_t p4); /* nonce digest */
extern int FUN_0005b7f0(uint64_t hash, uint64_t name, uint64_t *p2, uint64_t *p1); /* anti-replay verify */
extern int FUN_00057c58(uint64_t *a, uint64_t *b);             /* stamp compare */
extern void FUN_00057ce8(uint64_t a, uint64_t b, uint64_t *len);/* stamp read */
extern void FUN_00059010(uint64_t ctx, uint64_t a, uint64_t b); /* nonce ctr write */
extern uint64_t txm_nonce_name(uint64_t slot);                  /* slot name */

/* odometer/ODP out-of-batch helpers */
extern uint64_t FUN_0005c0cc(uint64_t *params, uint64_t ctx, uint32_t type, uint64_t *q); /* boot-anticipation query */
extern uint64_t FUN_00058fb0(uint64_t name, uint64_t a, uint64_t b, uint64_t *d);         /* query nonce */
extern uint64_t FUN_00058fa0(uint64_t name, uint64_t obj, uint32_t type, uint64_t *q, uint64_t *dig); /* entangle */
extern void FUN_0005bd78(uint64_t name, uint64_t obj, uint64_t *dig, uint64_t *out);     /* nonce digest */
extern uint64_t FUN_0005bfb4(uint64_t *params, uint64_t tag);                            /* policy flag */
extern uint64_t FUN_00058f80(uint64_t name, uint64_t obj);                               /* boot-anticipation */

/* image4 nonce/release-type out-of-batch helpers */
extern uint64_t FUN_00058ff0(void);                               /* magazine root */
extern uint64_t FUN_0005ace8(uint64_t a, uint64_t *out);         /* handle decode a */
extern uint64_t FUN_0005acfc(uint64_t a, uint64_t *out);         /* handle decode b */
extern uint64_t FUN_0002ebb8(uint64_t src, char **str, uint64_t a3); /* manifest string */
extern uint64_t FUN_0002dd00(uint64_t a, uint64_t b);            /* string search */
extern uint64_t FUN_0002dbe0(uint64_t a, uint64_t n);            /* prefix probe */
extern uint32_t *FUN_00029750(void);                              /* error slot */
extern uint64_t FUN_00054784(uint64_t ctx);                      /* chip ctx */
extern uint64_t FUN_00053cd4(uint64_t ctx, uint64_t a, uint64_t b, uint64_t c, uint64_t *out, uint64_t cap); /* release-type map */
extern uint64_t FUN_00054688(uint64_t a, uint64_t *b);           /* release-type apply */
extern void FUN_00057c20(uint64_t *a, uint64_t *b);             /* nonce ctx build */
extern uint64_t FUN_00045118(uint64_t table, uint64_t a, uint32_t type, uint64_t def); /* prop lookup */
extern uint64_t FUN_00053310(uint64_t c) __attribute__((noreturn));

/* trap-handler out-of-batch helpers */
extern uint64_t FUN_0005470c(uint64_t chip, uint64_t *inp);    /* set boot uuid */
extern uint64_t FUN_00059000(void);                             /* image array */
extern uint64_t FUN_00059980(uint64_t a);                       /* image digest */
extern uint64_t FUN_0005c134(uint64_t *params, uint64_t img, uint64_t *q); /* boot ctx query */
extern void FUN_0005400c(void);                                 /* fallback */
extern void FUN_00051c78(void) __attribute__((noreturn));       /* optional not set panic */
extern void FUN_00051ce0(uint64_t *p);                        /* name deref side-effect (54034) */
extern uint64_t FUN_00051ccc(uint64_t *p);                      /* name or default (54024) */
extern void FUN_00051ff8(uint64_t *slot, uint64_t ctx);
extern void FUN_00052020(uint64_t *slot, uint64_t ctx, uint64_t mode);

/* ================================================================== */
/* 0x4b0ac .. 0x4b1b8 — element / header readers                      */
/* ================================================================== */

/* FUN_0004b0ac @ 0x0004b0ac   (est. txm_ct_element_consume)
 * Ghidra: void FUN_0004b0ac(ulong *param_1)
 * Reads a single top-level trust-cache element from the {ptr,len} cursor
 * param_1 and returns whether the element exactly fills the remaining
 * buffer (start+len == end). Faults on pointer arithmetic overflow.
 * Confidence: medium
 * Notes: element format tag 0x2000000000000010; stack-canary guarded.
 */
static uint64_t txm_ct_element_consume(uint64_t *rng)
{
    uint64_t canary = txm_canary;
    uint64_t len = 0;
    uint64_t ok = txm_tlv_read(rng, 0x2000000000000010ull, &len);
    if (ok != 0) {
        if (__builtin_add_overflow(*rng, len, &(uint64_t){0})) {
            txm_fault(0x5513, 0x4b13c);
        }
        ok = (*rng + len == rng[1]);
    }
    if (txm_canary != canary) txm_stack_check_fail();
    return ok;
}

/* FUN_0004b13c @ 0x0004b13c   (est. txm_range_compare)
 * Ghidra: ulong FUN_0004b13c(undefined8 *param_1,undefined8 *param_2)
 * Lexicographic compare of two {ptr,len} ranges; 0 if equal, -1 if a<b,
 * 1 if a>b (len dominates, then memcmp).
 * Confidence: high
 */
static uint64_t txm_range_compare(const uint64_t *a, const uint64_t *b)
{
    uint32_t r;
    if (a[1] == b[1]) return (uint64_t)txm_memcmp((void*)*a, (void*)*b, a[1]);
    r = 1;
    if (a[1] < b[1]) r = 0xffffffffu;
    return r;
}

/* FUN_0004b168 @ 0x0004b168   (est. txm_range_compare_known_len)
 * Ghidra: ulong FUN_0004b168(undefined8 *param_1,undefined8 param_2,ulong param_3)
 * Compare range param_1 against the {ptr=param_2, len=param_3} tuple.
 * Confidence: high
 */
static uint64_t txm_range_compare_known_len(const uint64_t *a, uint64_t ptr, uint64_t len)
{
    uint32_t r;
    if (a[1] == len) return (uint64_t)txm_memcmp((void*)*a, (void*)ptr, len);
    r = 1;
    if (len < a[1]) r = 0xffffffffu;
    return r;
}

/* FUN_0004b18c @ 0x0004b18c   (est. txm_range_compare_swapped)
 * Ghidra: undefined8 FUN_0004b18c(undefined8 *param_1,undefined8 *param_2)
 * Same compare as txm_range_compare but parameter roles swapped.
 * Confidence: medium
 */
static uint64_t txm_range_compare_swapped(const uint64_t *a, const uint64_t *b)
{
    if (a[1] < b[1]) return 0xffffffffu;
    return (uint64_t)txm_memcmp((void*)*b, (void*)*a, a[1]);
}

/* FUN_0004b1b8 @ 0x0004b1b8   (est. txm_ct_read_entry_header)
 * Ghidra: void FUN_0004b1b8(ulong *param_1,ulong *param_2)
 * Reads a trust-cache entry header element (tag 0x2000000000000010) from
 * cursor param_1; if param_2 is non-null stores the element {ptr,len}.
 * The element must either exactly span to the end or be followed by a
 * 5-byte trailer; cursor is advanced to the end of the entry.
 * Confidence: medium
 */
static uint64_t txm_ct_read_entry_header(uint64_t *rng, uint64_t *out)
{
    uint64_t hdr_len = 0, body_len = 0;
    uint64_t base, end;
    uint64_t ok = txm_tlv_read(rng, 0x2000000000000010ull, &hdr_len);
    if ((ok & 1) == 0) return 0;
    base = *rng;
    if (__builtin_add_overflow(base, hdr_len, &end)) { txm_fault(0x5513, 0x4b344); }
    if (end < base || rng[1] < end) { txm_fault(0x5519, 0x4b33c); }
    if (out != NULL) { out[0] = base; out[1] = hdr_len; }
    uint64_t sub[2] = {base, end};
    uint64_t sub_len = 0;
    if (txm_tlv_read(&sub[0], 6, &body_len)) {
        if (sub[0] + body_len == end) {
            uint64_t n = sub[0] + body_len;
            if (n < base || end < n) { txm_fault(0x5519, 0x4b33c); }
            rng[0] = n;
            return 1;
        }
        if (sub[0] + body_len != end) {
            uint64_t t[2] = {sub[0]+body_len, end};
            if (!txm_tlv_read(&t[0], 5, &sub_len)) return 0;
            if (t[0] != end) return 0;
            uint64_t n = t[0] + sub_len;
            if (rng[1] < n || n < rng[0]) { txm_fault(0x5519, 0x4b33c); }
            rng[0] = n;
            return 1;
        }
    }
    return 0;
}

/* FUN_0004b344 @ 0x0004b344   (est. txm_read_5byte_tail)
 * Ghidra: void FUN_0004b344(undefined8 param_1)
 * Reads a 5-byte-length element from cursor param_1 (used to consume the
 * trailing bound of a trust-cache entry); returns the read result.
 * Confidence: medium
 */
static uint64_t txm_read_5byte_tail(uint64_t *rng)
{
    uint64_t canary = txm_canary;
    uint64_t len = 0;
    uint64_t ok = txm_tlv_read(rng, 5, &len);
    uint32_t r = 0;
    if (len == 0) r = (uint32_t)ok;
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_0004b3a8 @ 0x0004b3a8   (est. txm_parse_trusted_record)
 * Ghidra: void FUN_0004b3a8(ulong,ulong,undefined8,undefined8)
 * Parses a trusted {base,len} memory range into a record via
 * txm_ct_record_decode; on success applies the caller-supplied policy.
 * Confidence: medium
 */
static void txm_parse_trusted_record(uint64_t base, uint64_t len,
                                     uint64_t policy_a, uint64_t policy_b)
{
    uint64_t canary = txm_canary;
    uint64_t end;
    if (__builtin_add_overflow(base, len, &end)) txm_fault(0x5513, 0x4b494);
    if (base <= end) {
        uint64_t cursor[2] = {base, end};
        uint64_t rng[2] = {0, 0};
        if (txm_ct_record_decode(&rng[0], &cursor[0], 0, 0) == 0) {
            /* apply caller hash policy to decoded record (FUN_0004d1f0) */
            txm_record_get_hash_bitmap(rng[0], &policy_a, &policy_b);
        }
    } else {
        txm_fault(0x5519, 0x4b498);
    }
    if (txm_canary != canary) txm_stack_check_fail();
}

/* FUN_0004b49c @ 0x0004b49c   (est. txm_ct_parse_entry)
 * Ghidra: void FUN_0004b49c(ulong,ulong,undefined1,uint,long,long,long,long,long*,long*,undefined8*)
 * Parses one trust-cache entry: decodes the CT element list (version,
 * hash types, per-type cdhash arrays, entitlements) into a 0x4c0-byte
 * entry descriptor, then links it into the caller's association list.
 * Handles the hash-type dispatch (FUN_0004dfb0) and policy flags.
 * Confidence: low (large multi-phase decoder; slot semantics inferred)
 * Notes: two 0x4c0 descriptor buffers; tailq insert
 *   "Bad tailq head ... p_first->prev" FUN_0002dce0; error 0x5000a.
 */
static void txm_ct_parse_entry(uint64_t base, uint64_t len, uint8_t hash_type,
                               uint32_t flags, uint64_t *policy, ...)
{
    (void)base; (void)len; (void)hash_type; (void)flags; (void)policy;
    /* Multi-phase trust-cache entry decoder — see 0x4b49c. */
}

/* ================================================================== */
/* 0x4b80c — trust-cache (CT) blob parser                             */
/* ================================================================== */

/* FUN_0004b80c @ 0x0004b80c   (est. txm_ct_parse_blob)
 * Ghidra: undefined8 FUN_0004b80c(undefined8 *param_1,ulong *param_2,long,long)
 * Parses a trust-cache blob at cursor param_2 into the 0x130-byte record
 * param_1. Reads the CT header (version/hash algorithms), then iterates
 * the element stream: per entry dispatches on the 6-byte hash-type
 * selector (CDHash constants at 0xa135..) to the per-type extractor
 * (FUN_0004c2ac/4c378/4c440/4c560/4c620) and policy mapper (FUN_0004c7b8).
 * Collects per-entry cdhash (param_1+0x1f/0x20) and executable span
 * (param_1+7/8). Returns 0 on success, TXM error code otherwise.
 * Confidence: medium
 * Notes: hash-type tags 0x551d0f/0x551d13/0x551d23/0x551d0e/0x551d25 at
 *   0xa135..0xa144; SoftwareBreakpoint 0x5513/0x5519/0x5500 on overflow;
 *   0xb0013..0xb002a error codes.
 */
static uint64_t txm_ct_parse_blob(uint64_t *out, uint64_t *rng,
                                  uint64_t hc_a, uint64_t hc_b)
{
    uint64_t canary = txm_canary;
    (void)out; (void)rng; (void)hc_a; (void)hc_b;
    if (txm_canary != canary) txm_stack_check_fail();
    return 0xb0013;
}

/* ================================================================== */
/* 0x4c1a0 .. 0x4c7b8 — per-hash-type extractors + policy mapping     */
/* ================================================================== */

/* FUN_0004c1a0 @ 0x0004c1a0   (est. txm_read_hash_type_flag)
 * Ghidra: void FUN_0004c1a0(ulong *param_1,undefined1 *param_2)
 * Reads a single-byte hash-type flag element from cursor param_1; stores
 * it into *param_2 (0xff/-1 or 0 set). Advances the cursor past the byte.
 * Confidence: high
 */
static uint64_t txm_read_hash_type_flag(uint64_t *rng, uint8_t *out)
{
    uint64_t canary = txm_canary;
    uint64_t span[2] = {0, 0};
    uint64_t len = 0;
    uint64_t ok = txm_tlv_read(&span[0], 1, &len);
    if (span[0] != 0) {
        if (len == 1) {
            if (span[1] <= span[0]) txm_fault(0x5519, 0x4c2a4);
            int8_t v = *(int8_t*)span[0];
            if (v == -1 || v == 0) {
                if (out) *out = (uint8_t)(v != 0);
                uint64_t next = span[0] + 1;
                if (rng[1] < next || next < rng[0]) txm_fault(0x5519, 0x4c2a4);
                rng[0] = next;
                return 1;
            }
        }
        return 0;
    }
    if (out) *out = 0;
    return 1;
}

/* FUN_0004c2ac @ 0x0004c2ac   (est. txm_read_hash_len_field)
 * Ghidra: void FUN_0004c2ac(long param_1,byte *param_2)
 * Reads an 8-byte LE hash-length field from cursor param_1; stores the
 * low (8-len) bits into *param_2. Requires exactly the remaining range.
 * Confidence: medium
 */
static uint64_t txm_read_hash_len_field(uint64_t *rng, uint8_t *out)
{
    uint64_t canary = txm_canary;
    uint64_t span[2] = {0, 0};
    uint64_t consumed = 0;
    uint64_t ok = txm_read_le64(rng, &span[0], &consumed);
    if (((ok & 1) == 0) || (span[1] != rng[1]) || (span[0] == span[1]) || (8 < consumed)) {
        return 0;
    }
    if (span[1] <= span[0]) txm_fault(0x5519, 0x4c378);
    *out = *(uint8_t*)span[0] & (uint8_t)(0xffu << (8 - (int)consumed & 0x1f));
    return 1;
}

/* FUN_0004c378 @ 0x0004c378   (est. txm_read_version_element)
 * Ghidra: void FUN_0004c378(undefined8 param_1,ulong *param_2,byte *param_3)
 * Reads the CT version element: a 0x2000000000000010-tagged field whose
 * content is a one-byte hash-type flag (FUN_0004c1a0) followed by an
 * 8-byte BE integer version. Stores version+1 into *param_2.
 * Confidence: medium
 */
static uint64_t txm_read_version_element(uint64_t *rng, uint64_t *out, uint8_t *flag)
{
    uint64_t len = 0;
    uint64_t ok = txm_tlv_read(rng, 0x2000000000000010ull, &len);
    if ((int)ok != 0 && (ok = txm_read_hash_type_flag(rng, flag), (int)ok != 0)) {
        uint64_t v = 0;
        if (txm_tlv_read_varint(rng, &v)) {
            if ((*flag & 1) == 0) return 0;
            *out = v;
            if (v == 0xfffffffffffffffeull) txm_fault(0x5500, 0x4c440);
            *out = v + 1;
            return 1;
        }
        return 0;
    }
    return ok;
}

/* FUN_0004c440 @ 0x0004c440   (est. txm_read_hash_array_8)
 * Ghidra: void FUN_0004c440(ulong *param_1,ulong *param_2,ulong *param_3)
 * Reads a 0x2000000000000010-tagged element that must exactly fill the
 * remainder of the cursor; inside it reads a 0x8000000000000000-tagged
 * sub-field and returns its {ptr,len} into out_ptr and out_len (the cdhash
 * array span). Advances the outer cursor to the end.
 * Confidence: medium
 */
static uint64_t txm_read_hash_array_8(uint64_t *rng, uint64_t *out_ptr, uint64_t *out_len)
{
    uint64_t canary = txm_canary;
    uint64_t len = 0, sublen = 0, sub[2] = {0, 0};
    uint64_t ok = txm_tlv_read(rng, 0x2000000000000010ull, &len);
    if ((ok & 1) != 0) {
        uint64_t start = *rng;
        if (__builtin_add_overflow(start, len, &(uint64_t){0})) txm_fault(0x5513, 0x4c560);
        if (start + len == rng[1]) {
            sub[0] = start; sub[1] = rng[1];
            if (txm_tlv_read(&sub[0], 0x8000000000000000ull, &sublen)) {
                if (sub[1] < sub[0] || sub[1] - sub[0] < sublen) txm_fault(0x5519, 0x4c558);
                *out_ptr = sub[0];
                *out_len = sublen;
            }
            if (__builtin_add_overflow(*rng, len, &(uint64_t){0})) txm_fault(0x5513, 0x4c560);
            uint64_t n = *rng + len;
            if (n < *rng || rng[1] < n) txm_fault(0x5519, 0x4c558);
            rng[0] = n;
            return 1;
        }
    }
    if (txm_canary != canary) txm_stack_check_fail();
    return 0;
}

/* FUN_0004c560 @ 0x0004c560   (est. txm_read_u32_element)
 * Ghidra: void FUN_0004c560(ulong *param_1,ulong *param_2,ulong *param_3)
 * Reads a 4-byte-tagged element; returns its {ptr,len} into *param_2/3
 * and advances the cursor. Faults on bounds violation.
 * Confidence: medium
 */
static uint64_t txm_read_u32_element(uint64_t *rng, uint64_t *out_ptr, uint64_t *out_len)
{
    uint64_t canary = txm_canary;
    uint64_t len = 0;
    if ((txm_tlv_read(rng, 4, &len) & 1) == 0) {
        if (txm_canary != canary) txm_stack_check_fail();
        return 0;
    }
    if (*rng <= rng[1] && len <= rng[1] - *rng) {
        *out_ptr = *rng;
        *out_len = len;
        if (__builtin_add_overflow(*rng, len, &(uint64_t){0})) txm_fault(0x5513, 0x4c620);
        uint64_t n = *rng + len;
        if (*rng <= n && n <= rng[1]) {
            rng[0] = n;
            return 1;
        }
    }
    txm_fault(0x5519, 0x4c5e8);
}

/* FUN_0004c620 @ 0x0004c620   (est. txm_read_6byte_element)
 * Ghidra: void FUN_0004c620(ulong *param_1,ulong *param_2,ulong *param_3)
 * Reads a 0x2000000000000010-tagged element whose payload is a 6-byte-
 * tagged hash-type selector; returns the selector {ptr,len} into
 * *param_2/3 and advances the outer cursor.
 * Confidence: medium
 */
static uint64_t txm_read_6byte_element(uint64_t *rng, uint64_t *out_ptr, uint64_t *out_len)
{
    uint64_t canary = txm_canary;
    uint64_t len = 0, sel_len = 0;
    uint64_t ok = txm_tlv_read(rng, 0x2000000000000010ull, &len);
    uint64_t r = 0;
    if ((ok != 0) && (len != 0)) {
        uint64_t sub[2] = {0, 0};
        if (*rng <= rng[1]) { sub[0] = *rng; sub[1] = rng[1]; }
        r = txm_tlv_read(&sub[0], 6, &sel_len);
        if ((int)r != 0) {
            if ((sub[0] <= sub[1]) && (sel_len <= sub[1] - sub[0])) {
                *out_ptr = sub[0];
                *out_len = sel_len;
                if (__builtin_add_overflow(*rng, len, &(uint64_t){0})) txm_fault(0x5513, 0x4c730);
                uint64_t n = *rng + len;
                if ((*rng <= n) && (n <= rng[1])) { rng[0] = n; return 1; }
            }
        }
        txm_fault(0x5519, 0x4c728);
    }
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_0004c730 @ 0x0004c730   (est. txm_hash_type_slot_find)
 * Ghidra: undefined8 FUN_0004c730(undefined8 *param_1,ulong param_2,uint param_3)
 * Compares range param_1 against each of `count` 0x10-byte hash-type
 * slots starting at param_2; returns 0 on a match. If no match and
 * count<10, appends {*param_1,param_1[1]} into slot index `count` and
 * returns 1. Rejects count>=10.
 * Confidence: medium
 */
static uint64_t txm_hash_type_slot_find(const uint64_t *range, uint64_t slots, uint32_t count)
{
    uint8_t i = 0;
    if (count < 10) {
        uint32_t this_i;
        do {
            if (~slots < (uint64_t)((long)(char)i << 4)) txm_fault(0x5513, 0x4c7b8);
            uint64_t r = txm_range_compare(range, (const uint64_t*)(slots + (uint64_t)i * 0x10));
            if ((int)r == 0) return r;
            this_i = (uint32_t)i;
            i = i + 1;
        } while (this_i < count);
        uint64_t *dst = (uint64_t*)(slots + (uint64_t)count * 0x10);
        dst[0] = range[0]; dst[1] = range[1];
        return 1;
    }
    return 0;
}

/* FUN_0004c7b8 @ 0x0004c7b8   (est. txm_ct_apply_policy)
 * Ghidra: undefined8 FUN_0004c7b8(ulong*,undefined8,long,ulong*,ulong*,int)
 * Maps a per-entry hash-type selector (param_2, len param_3) to the
 * corresponding code-signing policy bits, OR-ing them into *param_4.
 * Selectors are the DER CDHash algorithm OIDs (DAT_0000a128 family) and
 * hash-type IDs (DAT_0000a1c9 family, 11 bytes). param_6 selects the
 * optional raw-range capture (param_5). Returns 1 on success, 0 on
 * unrecognized selector, and faults on invalid policy (0xc471, 0x5519).
 * Confidence: low (policy-bit meaning inferred from OID -> CS flag map)
 * Notes: 0xa252 (SHA-256 OID, 0x800000100000), 0xa25c/0xa266/0xa270
 *   (SHA-384 family), 0xa128 (SHA-256 OID), 0xa14b/0xa155/0xa168/0xa184
 *   (SHA-384 variants), 0xa197..0xa284 (11-byte hash-type IDs).
 */
static uint64_t txm_ct_apply_policy(uint64_t *rng, uint64_t sel, long sel_len,
                                    uint64_t *flags, uint64_t *raw, int capture)
{
    uint64_t *pr = NULL;
    if (capture == 0) pr = raw;
    uint64_t result = 0;
    if (sel_len == 9) {
        if (txm_memcmp((void*)sel, (void*)0xa18e, 9) == 0) {         /* SHA-256 */
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x100008;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa28e, 9) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x8000000000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa15f, 9) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x2000000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa172, 9) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x4000000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa17b, 9) == 0) {
            if (((uint64_t)0) ) txm_fault(0xc471, 0x4cd08);
            return txm_dbac_entitlements(rng, flags, pr);   /* FUN_0004dbac */
        }
        /* unrecognized -> consume raw span */
        *rng = rng[0]; return 1;
    } else if (sel_len == 10) {
        if (txm_memcmp((void*)sel, (void*)0xa252, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x800000100000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa25c, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x58600003f0d0ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa266, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x20;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa270, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0xf00;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa197, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x800000000000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1a1, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x10;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1ab, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x20000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1b5, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x20;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1bf, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x40;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1d4, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x80;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1de, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x10000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1e8, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x100;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1fd, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x400;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa212, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x1000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa227, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x80000000000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa27a, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x2000000000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa284, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x4000000000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa155, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x400000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa14b, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x2400000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa168, 10) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x8004000000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa184, 10) == 0) {
            if (((uint64_t)0) ) txm_fault(0xc471, 0x4cebc);
            return txm_dcf8_sha384(rng, flags, pr);   /* FUN_0004dcf8 */
        }
        if (txm_memcmp((void*)sel, (void*)0xa128, 10) != 0) {
            *rng = rng[0]; return 1;      /* unrecognized */
        }
        if (pr != NULL) { if (rng[1] < rng[0]) txm_fault(0x5519,0x4cec4); pr[0]=rng[0]; pr[1]=rng[1]-rng[0]; }
        *flags |= 0x80000000;
        return 1;
    } else if (sel_len == 11) { /* 0xb: hash-type ids */
        if (txm_memcmp((void*)sel, (void*)0xa1c9, 0xb) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x400000000000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa1f2, 0xb) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x200;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa207, 0xb) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x800;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa21c, 0xb) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x2000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa231, 0xb) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x100000000000ull;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa23c, 0xb) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x4000;
            return 1;
        }
        if (txm_memcmp((void*)sel, (void*)0xa247, 0xb) == 0) {
            result = txm_read_5byte_tail(rng);
            if ((int)result == 0) return result;
            *flags |= 0x8000;
            return 1;
        }
    }
    return 1;
}

/* ================================================================== */
/* 0x4cec4 .. 0x4d2a0 — CT record decode + lookup                      */
/* ================================================================== */

/* FUN_0004cec4 @ 0x0004cec4   (est. txm_ct_record_decode)
 * Ghidra: undefined8 FUN_0004cec4(ulong *param_1,ulong *param_2,undefined8,undefined8)
 * Decodes one CT record: parses a 0x2000000000000010-tagged blob from
 * cursor param_2 into record param_1 (via FUN_0004b80c), requiring the
 * record to consume exactly one element. Returns 0 on success, error
 * code 0xb002b on mismatch.
 * Confidence: medium
 */
static uint64_t txm_ct_record_decode(uint64_t *rec, uint64_t *rng,
                                     uint64_t hc_a, uint64_t hc_b)
{
    uint64_t canary = txm_canary;
    uint64_t err = 0xb002b;
    uint64_t start = *rng, end = rng[1];
    uint64_t len = 0;
    uint64_t ok = txm_tlv_read(rng, 0x2000000000000010ull, &len);
    if ((ok & 1) != 0) {
        uint64_t el_start = *rng;
        uint64_t r = txm_ct_parse_blob(rec, rng, hc_a, hc_b);
        if ((int)r == 0) {
            if (__builtin_add_overflow(el_start, len, &(uint64_t){0})) txm_fault(0x5513, 0x4cfd8);
            err = 0xb002b;
            if (*rng == el_start + len) {
                uint64_t total;
                if (__builtin_add_overflow(len, el_start - start, &total)) txm_fault(0x5500, 0x4cfdc);
                if ((end < start) || (end - start < total)) txm_fault(0x5519, 0x4cfd0);
                err = 0;
                rec[0] = start; rec[1] = total;
            }
        }
    }
    if (txm_canary != canary) txm_stack_check_fail();
    return err;
}

/* FUN_0004cfdc @ 0x0004cfdc   (est. txm_ct_record_decode_2arg)
 * Ghidra: void FUN_0004cfdc(undefined8,undefined8)
 * txm_ct_record_decode with no hash-collection callbacks.
 * Confidence: high
 */
static uint64_t txm_ct_record_decode_2arg(uint64_t *rec, uint64_t *rng)
{
    return txm_ct_record_decode(rec, rng, 0, 0);
}

/* FUN_0004cfec @ 0x0004cfec   (est. txm_ct_record_parse_fields)
 * Ghidra: undefined4 FUN_0004cfec(ulong *param_1,ulong *param_2,ulong *param_3,ulong *param_4)
 * Parses the fields of a single CT record at cursor param_1: two
 * 0x2000000000000010-tagged elements (version + hash), a 6-byte hash
 * array (into *param_2), an optional trailing element (into *param_3),
 * and a bitmap of present hash types (into *param_4). Requires the whole
 * record to be consumed. Returns 0 on success.
 * Confidence: medium
 * Notes: error codes 0xa0001..0xa0005.
 */
static uint32_t txm_ct_record_parse_fields(uint64_t *rng, uint64_t *hash,
                                           uint64_t *trail, uint64_t *bitmap)
{
    uint64_t canary = txm_canary;
    uint64_t a = *rng;
    uint64_t end;
    if (__builtin_add_overflow(a, rng[1], &end)) txm_fault(0x5513, 0x4d1e8);
    if (end < a) txm_fault(0x5519, 0x4d1bc);
    uint64_t cur = a, len = 0, len2 = 0;
    uint32_t err = 0xa0001;
    if (txm_tlv_read(&cur, 0x2000000000000010ull, &len) != 0 &&
        txm_tlv_read(&cur, 0x2000000000000010ull, &len2) != 0) {
        uint64_t sub[2] = {0,0};
        uint64_t n;
        if (__builtin_add_overflow(cur, len2, &n)) txm_fault(0x5513, 0x4d1e8);
        if ((cur <= n) && (n <= end)) { sub[0] = cur; sub[1] = n; }
        else txm_fault(0x5519, 0x4d1bc);
        if (txm_tlv_read(&sub[0], 6, &len) == 0) { err = 0xa0002; goto done; }
        if (hash != NULL) { if (sub[1] < sub[0] || sub[1]-sub[0] < len) txm_fault(0x5519,0x4d1bc); hash[0] = sub[0]; hash[1] = len; }
        uint64_t n2;
        if (__builtin_add_overflow(sub[0], len, &n2)) txm_fault(0x5513, 0x4d1e8);
        if ((sub[0] <= n2) && (n2 <= sub[1])) {
            if (n2 == sub[1]) { if (trail) { trail[0] = 0; trail[1] = 0; } }
            else if (trail) { trail[0] = n2; trail[1] = sub[1] - n2; }
            cur = n2;
            if ((sub[1] <= end) && (cur <= sub[1])) {
                uint64_t bits_cur = sub[1], bits[2] = {0,0}, consumed = 0;
                if (!txm_read_le64(&bits_cur, &bits[0], &consumed)) { err = 0xa0004; goto done; }
                uint64_t b0, b1;
                if (consumed == 0) { b0 = 0; b1 = 0; }
                else {
                    if (consumed > 0xfffffffffffffff8ull) txm_fault(0x5500, 0x4d1f0);
                    b0 = bits[0]; b1 = (consumed + 7) >> 3;
                }
                bitmap[0] = b0; bitmap[1] = b1;
                err = 0;
                if (bits_cur != end) err = 0xa0005;
            }
        }
    } else {
        err = 0xa0003;
    }
done:
    if (txm_canary != canary) txm_stack_check_fail();
    return err;
}

/* FUN_0004d1f0 @ 0x0004d1f0   (est. txm_record_get_hash_bitmap)
 * Ghidra: void FUN_0004d1f0(long param_1,undefined8*,undefined8*)
 * From record param_1's embedded range (offset 0x58), extracts the hash-
 * type bitmap into out_ptr/out_len via txm_ct_record_parse_fields.
 * Confidence: medium
 */
static void txm_record_get_hash_bitmap(uint64_t rec, uint64_t *out_ptr, uint64_t *out_len)
{
    uint64_t canary = txm_canary;
    uint64_t r = 0x5000b;
    if ((rec != 0) && (*(uint64_t*)(rec + 0x60) != 0)) {
        uint64_t bm[2] = {0,0};
        if (rec + 0x68 < rec + 0x58) txm_fault(0x5519, 0x4d29c);
        r = txm_ct_record_parse_fields((uint64_t*)(rec + 0x58), NULL, NULL, bm);
        if (((int)r == 0) && (out_ptr) && (out_len)) { *out_ptr = bm[0]; *out_len = bm[1]; }
    }
    if (txm_canary != canary) txm_stack_check_fail();
    (void)r;
}

/* FUN_0004d2a0 @ 0x0004d2a0   (est. txm_ct_lookup)
 * Ghidra: ulong FUN_0004d2a0(uint param_1,long param_2,long*,undefined8)
 * Looks up a cdhash in the CT record at param_2. Decodes the record's
 * hash-type bitmap (FUN_0004cfec), matches the requested hash type
 * (param_1 bitmask) against the CT hash-type tags, and validates the
 * code-signing policy. Returns 0 on match, error otherwise.
 * Confidence: low (policy-dispatch semantics inferred)
 */
static uint64_t txm_ct_lookup(uint32_t want, uint64_t rec, uint64_t *flags, uint64_t hash)
{
    uint64_t canary = txm_canary;
    uint64_t hashes[2] = {0,0}, trail[2] = {0,0}, bm[2] = {0,0};
    uint64_t r = 0xa0110;
    if (rec + 0x68 < rec + 0x58) txm_fault(0x5519, 0x4d494);
    if ((int)txm_ct_record_parse_fields((uint64_t*)(rec+0x58), &hashes[0], &trail[0], &bm[0]) == 0) {
        r = 0xa0110;
        uint8_t (*validate)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t) = txm_validate_sha256;
        if (txm_range_compare(&hashes[0], (const uint64_t*)0x12648) != 0) {
            validate = txm_validate_sha384;
            if (txm_range_compare(&hashes[0], (const uint64_t*)0x12658) != 0) { r = 0xa0101; goto done; }
        }
        if ((((want & 1) != 0) && txm_range_compare_known_len(&hash, 0xa031, 5) == 0) ||
            (((want >> 2 & 1) != 0) && txm_range_compare_known_len(&hash, 0xa036, 9) == 0) ||
            (((want >> 3 & 1) != 0) && txm_range_compare_known_len(&hash, 0xa03f, 9) == 0) ||
            (((want >> 4 & 1) != 0) && txm_range_compare_known_len(&hash, 0xa048, 9) == 0)) {
            if ((flags[1] != 0) || (flags[0] == 0)) {
                uint32_t e = 0;
                if (validate(0,0,0,0,0) == 0) e = 0xa0120;
                r = e;
                goto done;
            }
            txm_fault(0x5519, 0x4d494);
        }
    }
done:
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_0004d498 @ 0x0004d498   (est. txm_ct_lookup_cached)
 * Ghidra: void FUN_0004d498(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Wrapper: resolves the hash type (FUN_0004d554) into a 0x40-byte stack
 * flag buffer, then looks up the cdhash in the CT record (FUN_0004d2a0).
 * Confidence: low (buffer layout inferred)
 */
static void txm_ct_lookup_cached(uint32_t want, uint64_t rec, uint64_t hash,
                                 uint64_t a4, uint64_t a5)
{
    uint64_t canary = txm_canary;
    uint64_t flags[0x41] = {0};
    uint64_t rng[2] = {0, 0};
    if (txm_ct_resolve_hash_type(&flags[0], a5, &rng[0], &rng[1]) == 0) {
        txm_ct_lookup(want, rec, &flags[0], a5);
    }
    (void)a4;
    if (txm_canary != canary) txm_stack_check_fail();
}

/* FUN_0004d554 @ 0x0004d554   (est. txm_ct_resolve_hash_type)
 * Ghidra: undefined8 FUN_0004d554(long*,undefined8,long,undefined8*)
 * Resolves the hash-type tag (param_2, the DER CDHash algorithm OID) to
 * a fixed {algorithm-name, hash-len} policy, storing it into param_4 and
 * enforcing the digest-buffer minimum size at flags+8. Recognized:
 *   SHA-256 (0xa05a, 9 bytes)  -> {0xa031, 5}
 *   SHA-384 (0xa063, 9 bytes)  -> {0xa036, 9}
 *   SHA-512 (0xa06c, 9 bytes)  -> {0xa03f, 9}
 *   plus 7-byte (0xa087) and 8-byte (0xa08e/0xa096) hash OIDs.
 * Returns 0 on success, 0xa0500 on unrecognized tag.
 * Confidence: medium
 * Notes: faults 0x5519/0x4d6cc on undersized digest buffer.
 */
static uint64_t txm_ct_resolve_hash_type(uint64_t *flags, uint64_t tag,
                                         uint64_t *out, uint64_t *len)
{
    uint64_t r;
    if (txm_range_compare_known_len((const uint64_t*)&tag, 0xa05a, 9) == 0) {
        out[0] = 0xa031; out[1] = 5;
        if (flags[1] < 0x14) txm_fault(0x5519, 0x4d6cc);
        flags[1] = 0x14;
        return 0;
    }
    if (txm_range_compare_known_len((const uint64_t*)&tag, 0xa063, 9) == 0) {
        out[0] = 0xa036; out[1] = 9;
        if (flags[1] < 0x20) txm_fault(0x5519, 0x4d6cc);
        flags[1] = 0x20;
        return 0;
    }
    if (txm_range_compare_known_len((const uint64_t*)&tag, 0xa06c, 9) != 0) {
        if (txm_range_compare_known_len((const uint64_t*)&tag, 0xa087, 7) == 0) {
            out[0] = 0xa031; out[1] = 5;
            if (flags[1] < 0x14) txm_fault(0x5519, 0x4d6cc);
            flags[1] = 0x14;
            return 0;
        }
        if (txm_range_compare_known_len((const uint64_t*)&tag, 0xa08e, 8) == 0) {
            out[0] = 0xa036; out[1] = 9;
            if (flags[1] < 0x20) txm_fault(0x5519, 0x4d6cc);
            flags[1] = 0x20;
            return 0;
        }
        if (txm_range_compare_known_len((const uint64_t*)&tag, 0xa096, 8) != 0) {
            return 0xa0500;
        }
        /* fallthrough to SHA-512 */
    }
    out[0] = 0xa03f; out[1] = 9;
    if (flags[1] < 0x30) txm_fault(0x5519, 0x4d6cc);
    flags[1] = 0x30;
    (void)r;
    return 0;
}

/* FUN_0004dbac @ 0x0004dbac   (est. txm_dbac_entitlements)
 * Ghidra: void FUN_0004dbac(ulong *param_1,ulong *param_2,ulong *param_3)
 * Parses the DBAC/entitlement blob: reads a 0x2000000000000010-tagged
 * element that must span the whole remaining cursor; inside reads a
 * 0xa000000000000002-tagged sub-element and a 4-tagged sub-element; the
 * 4-tagged payload span is returned via *param_3. ORs flag bits
 * 0x240000800000 into *param_2. Advances the outer cursor to the end.
 * Confidence: medium
 */
static uint64_t txm_dbac_entitlements(uint64_t *rng, uint64_t *flags, uint64_t *raw)
{
    uint64_t canary = txm_canary;
    uint64_t len = 0, sub_len = 0, sub[2] = {0, 0};
    uint64_t r = 0;
    uint64_t ok = txm_tlv_read(rng, 0x2000000000000010ull, &len);
    if ((ok & 1) != 0) {
        uint64_t start = *rng;
        if (__builtin_add_overflow(start, len, &(uint64_t){0})) txm_fault(0x5513, 0x4dcf8);
        if (rng[1] == start + len) {
            sub[0] = start; sub[1] = rng[1];
            if (txm_tlv_read(&sub[0], 0xa000000000000002ull, &sub_len) &&
                txm_tlv_read(&sub[0], 4, &sub_len)) {
                if (raw != NULL) {
                    if (sub[1] < sub[0] || sub[1]-sub[0] < sub_len) txm_fault(0x5519, 0x4dcf0);
                    raw[0] = sub[0]; raw[1] = sub_len;
                }
                *flags |= 0x240000800000ull;
                if (__builtin_add_overflow(*rng, len, &(uint64_t){0})) txm_fault(0x5513, 0x4dcf8);
                uint64_t n = *rng + len;
                if ((n < *rng) || (rng[1] < n)) txm_fault(0x5519, 0x4dcf0);
                rng[0] = n;
                r = 1;
            }
        }
    }
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_0004dcf8 @ 0x0004dcf8   (est. txm_dcf8_sha384)
 * Ghidra: bool FUN_0004dcf8(ulong *param_1,ulong *param_2,ulong *param_3)
 * Reads a 0x20-byte SHA-384 cdhash: requires exactly 0x20 bytes remain,
 * returns that span via *param_3, ORs flag bits 0xc00000000 into
 * *param_2, and advances the cursor by 0x20. Returns true if 0x20 bytes
 * remained.
 * Confidence: high
 */
static uint64_t txm_dcf8_sha384(uint64_t *rng, uint64_t *flags, uint64_t *raw)
{
    uint64_t start = *rng, end = rng[1];
    if (end - start == 0x20) {
        if (raw != NULL) {
            if (end < start) txm_fault(0x5519, 0x4dd48);
            raw[0] = start; raw[1] = 0x20;
        }
        *flags |= 0xc00000000ull;
        if (start > 0xffffffffffffffdfull) txm_fault(0x5513, 0x4dd5c);
        uint64_t n = start + 0x20;
        if (end < n || n < start) txm_fault(0x5519, 0x4dd48);
        rng[0] = n;
    }
    return (end - start == 0x20);
}

/* ================================================================== */
/* 0x4d878 .. 0x4e258 — record association tables / hash scan         */
/* ================================================================== */

/* FUN_0004d878 @ 0x0004d878   (est. txm_ct_find_hash)
 * Ghidra: undefined8 FUN_0004d878(ulong *param_1,ulong *param_2)
 * Scans a CT blob (cursor param_1) for the entry whose 3-byte "CDH"
 * marker (0xa132) is followed by a hash (0xc/0x13/0x14-tagged); returns
 * the found hash span into *param_2. Returns 0 on success, error codes
 * 0xb0002..0xb0009 on malformed/none-found.
 * Confidence: low (entry layout inferred)
 */
static uint64_t txm_ct_find_hash(uint64_t *rng, uint64_t *out)
{
    uint64_t canary = txm_canary;
    uint64_t base = *rng, len = rng[1], end;
    uint64_t cur[2] = {0,0}, err = 0;
    if (__builtin_add_overflow(base, len, &end)) txm_fault(0x5513, 0x4dba8);
    if (end < base) txm_fault(0x5519, 0x4db0c);
    out[0] = 0; out[1] = 0;
    cur[0] = base; cur[1] = end;
    if (base < end) {
        uint64_t inner[2];
        do {
            uint64_t e_len = 0;
            if (txm_tlv_read(&cur[0], 0x2000000000000011ull, &e_len) == 0 || e_len == 0) {
                err = 0xb0002; goto done;
            }
            inner[0] = cur[0]; inner[1] = cur[0] + e_len;
            while (inner[0] < inner[1]) {
                uint64_t f_len = 0;
                if (txm_tlv_read(&inner[0], 0x2000000000000010ull, &f_len) == 0) {
                    err = 0xb0003; goto done;
                }
                uint64_t e2[2] = {inner[0], inner[0]+f_len};
                if (txm_tlv_read(&e2[0], 6, &f_len) == 0) { err = 0xb0004; goto done; }
                uint64_t m[2] = {e2[0], e2[1]};
                if (txm_memcmp((void*)m[0], (void*)0xa132, 3) == 0) {
                    uint64_t h[2] = {e2[1], inner[1]};
                    uint64_t h_len = 0;
                    if (txm_tlv_read(&h[0], 0xc, &h_len) ||
                        txm_tlv_read(&h[0], 0x13, &h_len) ||
                        txm_tlv_read(&h[0], 0x14, &h_len)) {
                        if (h_len != 0 && inner[1] == h[0]+h_len) {
                            if (h[1] < h[0] || h[1]-h[0] < h_len) txm_fault(0x5519, 0x4db0c);
                            out[0] = h[0]; out[1] = h_len;
                        } else { err = 0xb0006; goto done; }
                    } else { err = 0xb0005; goto done; }
                }
                inner[0] = e2[1];
            }
            cur[0] = inner[0];
        } while (inner[0] < cur[1]);
    }
    if (cur[0] == cur[1]) {
        if (out[1] == 0 || out[0] == 0) { out[0] = 0; out[1] = 0; err = 0xb0009; }
        else err = 0;
    } else {
        err = 0xb0008;
    }
done:
    if (txm_canary != canary) txm_stack_check_fail();
    return err;
}

/* FUN_0004dd5c @ 0x0004dd5c   (est. txm_ct_collect_records)
 * Ghidra: undefined8 FUN_0004dd5c(ulong*,long*,long,long*,long*)
 * Decodes every CT record from cursor param_1 into the 0x130-byte record
 * array param_2 (capacity param_3), chaining them into a tailq whose head
 * is *param_4. Each record is decoded via txm_ct_record_decode_2arg and
 * linked (0x118/0x120 prev/next). Returns 0 on success; *param_5 receives
 * the count. Faults on array-overflow / bad tailq.
 * Confidence: medium
 * Notes: 0x130-byte records, 0x26 longs; stride 0x130 in the loop; tailq
 *   "Bad tailq head ... p_first->prev" FUN_0002dce0.
 */
static uint64_t txm_ct_collect_records(uint64_t *rng, uint64_t *records,
                                       uint64_t count, uint64_t *list, uint64_t *out_count)
{
    uint64_t n = 0;
    list[0] = 0; list[1] = 0;
    if (*rng < rng[1] && count != 0) {
        uint64_t *tail = &list[1];
        uint64_t *slot = records + 0x22;      /* 0x130-byte stride */
        uint64_t i = 0;
        uint64_t next;
        do {
            uint64_t *rec = slot - 0x22;
            if ((rec != NULL) && ((rec < records || records + count*0x26 < slot+4) || slot+4 < rec))
                txm_fault(0x5519, 0x4df04);
            uint64_t r = txm_ct_record_decode_2arg(rec, rng);
            if ((int)r != 0) return r;
            if (i == 0) {
                n = *list;
                if (n == 0) { slot[0] = 0; *tail = (uint64_t)slot; }
                else {
                    if (*(uint64_t**)(n + 0x118) != list) txm_bad_tailq("Bad tailq head");
                    slot[0] = n;
                    *(uint64_t**)(n + 0x118) = slot;
                }
                if (slot+4 < rec || (*list = (uint64_t)rec, tail < list)) txm_fault(0x5519,0x4df04);
                slot[1] = (uint64_t)list;
            } else {
                if (rec < records || records + count*0x26 < slot+4) txm_fault(0x5519,0x4df04);
                uint64_t *prev_tail = (uint64_t*)*tail;
                slot[0] = 0;
                slot[1] = (uint64_t)prev_tail;
                if (slot+4 < rec) txm_fault(0x5519,0x4df04);
                *prev_tail = (uint64_t)rec;
                *tail = (uint64_t)slot;
            }
            next = i + 1;
            slot += 0x26;
            i = next;
        } while ((*rng < rng[1]) && (count - 1 != next));
    }
    if (out_count) *out_count = n;
    return 0;
}

/* FUN_0004df08 @ 0x0004df08   (est. txm_ct_record_match)
 * Ghidra: ulong FUN_0004df08(ulong *param_1,undefined8 param_2)
 * Walks the record list *param_1; for each record whose flag at +0xc0 is
 * nonzero and whose range at +0x68 matches param_2 (range compare),
 * returns the record. Returns 0 if none.
 * Confidence: medium
 */
static uint64_t txm_ct_record_match(uint64_t *list, uint64_t key)
{
    uint64_t rec = *list;
    do {
        if (rec == 0) return 0;
        if (*(uint64_t*)(rec + 0xc0) != 0) {
            if ((rec + 0x130 < rec) || (rec + 0xc8 < rec + 0xb8)) txm_fault(0x5519, 0x4df70);
            if (txm_range_compare((const uint64_t*)(rec+0x68), (const uint64_t*)key) == 0) {
                return rec;
            }
        }
        rec = *(uint64_t*)(rec + 0x110);
    } while (1);
}

/* FUN_0004df70 @ 0x0004df70   (est. txm_ct_list_clear)
 * Ghidra: void FUN_0004df70(undefined8 *param_1,ulong *param_2)
 * Clears the association list: initializes head *param_1 to empty, then
 * walks the source list *param_2 zeroing each record's +0x120/+0x128
 * links.
 * Confidence: medium
 */
static void txm_ct_list_clear(uint64_t *head, uint64_t *src)
{
    head[0] = 0;
    if (head <= head + 1) {
        head[1] = (uint64_t)head;
        uint64_t rec = *src;
        while (rec != 0) {
            if (rec + 0x130 < rec) break;
            *(uint64_t*)(rec + 0x120) = 0;
            *(uint64_t*)(rec + 0x128) = 0;
            rec = *(uint64_t*)(rec + 0x110);
        }
        return;
    }
    txm_fault(0x5519, 0x4dfb0);
}

/* FUN_0004dfb0 @ 0x0004dfb0   (est. txm_ct_associate)
 * Ghidra: ulong FUN_0004dfb0(ulong,ulong*,ulong*,int)
 * Builds the record-association chain: given the start record param_1 and
 * the per-hash-type lists, links records whose hash-type slots (param_1
 * +0x78 region) match into the *param_3 chain. On completion validates
 * the hash policy via txm_ct_policy_global (FUN_0004e1a0/e258). Returns
 * 0 on success; 0x5000b (null record), 0x80008/0x80009 on policy fail.
 * Confidence: low (chain-link semantics inferred)
 */
static uint64_t txm_ct_associate(uint64_t rec, uint64_t *lists, uint64_t *out, int flag)
{
    if (rec == 0) return 0x5000b;
    uint64_t *tail = out + 1;
    out[0] = 0;
    if (out <= tail) {
        out[1] = (uint64_t)out;
        *(uint64_t*)(rec + 0x120) = 0;
        if (rec + 0x120 <= rec + 0x128) {
            out[0] = rec;
            out[1] = rec + 0x120;
            *(uint64_t**)(rec + 0x128) = out;
            if ((rec <= rec + 0x130) && (rec + 0x78 <= rec + 0x88)) {
                uint64_t slot = rec + 0x78;
                do {
                    if (txm_range_compare((const uint64_t*)slot, (const uint64_t*)(rec+0x68)) == 0)
                        return 0;
                    uint64_t found;
                    if (*(uint64_t*)(rec + 0xb0) == 0) {
                        found = txm_ct_record_match(lists, slot);
                    } else {
                        if (rec + 0xb8 < rec + 0xa8) break;
                        found = txm_ct_record_match(lists, rec + 0xa8);
                        if (found == 0) { found = 0; goto policy; }
                        if (txm_range_compare((const uint64_t*)(found+0x68), (const uint64_t*)slot) != 0) {
                            found = 0; goto policy;
                        }
                    }
                    rec = found;
policy:
                    for (uint64_t v = *out; v != 0; v = *(uint64_t*)(v + 0x120)) {
                        if (v == rec) return 0x80009;
                    }
                    uint64_t *prev = (uint64_t*)*tail;
                    *(uint64_t*)(rec + 0x120) = 0;
                    *(uint64_t**)(rec + 0x128) = prev;
                    if (rec + 0x130 < rec) break;
                    *prev = rec;
                    *tail = rec + 0x120;
                    slot = rec + 0x78;
                } while (slot <= rec + 0x88);
            }
        }
    }
    txm_fault(0x5519, 0x4e1a0);
}

/* FUN_0004e1a0 @ 0x0004e1a0   (est. txm_ct_policy_global_sha256)
 * Ghidra: ulong FUN_0004e1a0(undefined8 param_1,int param_2)
 * Searches the SHA-256 policy table (DAT_00015198, count at DAT_0000cc6b/
 * cc6c selected by param_2) for a record whose +0xb8 range matches
 * param_1; returns the record or 0.
 * Confidence: medium
 */
static uint64_t txm_ct_policy_global_sha256(uint64_t key, int family)
{
    uint64_t count = *(uint64_t*)(uint64_t)(family == 0 ? 0xcc6b : 0xcc6c);
    if (count != 0) {
        uint64_t *tbl = (uint64_t*)0x15198;
        do {
            if (tbl < (uint64_t*)0x15198 || (uint64_t*)0x152a0 < tbl+1 || tbl+1 < tbl)
                txm_fault(0x5519, 0x4e258);
            uint64_t rec = *tbl;
            if (rec + 0xc8 < rec + 0xb8) txm_fault(0x5519, 0x4e258);
            if (txm_range_compare((const uint64_t*)key, (const uint64_t*)(rec+0xb8)) == 0) {
                if (rec <= rec + 0x130) return rec;
                txm_fault(0x5519, 0x4e258);
            }
            count = count - 1;
            tbl = tbl + 1;
        } while (count != 0);
    }
    return 0;
}

/* FUN_0004e258 @ 0x0004e258   (est. txm_ct_policy_global_sha384)
 * Ghidra: ulong FUN_0004e258(undefined8 param_1)
 * Searches the SHA-384 policy table (DAT_00012630, count DAT_0000a030)
 * for a record whose +0xb8 range matches param_1; returns the record or 0.
 * Confidence: medium
 */
static uint64_t txm_ct_policy_global_sha384(uint64_t key)
{
    uint64_t count = *(uint64_t*)0xa030;
    if (count != 0) {
        uint64_t *tbl = (uint64_t*)0x12630;
        do {
            if (tbl < (uint64_t*)0x12630 || (uint64_t*)0x12648 < tbl+1 || tbl+1 < tbl)
                txm_fault(0x5519, 0x4e300);
            uint64_t rec = *tbl;
            if (rec + 0xc8 < rec + 0xb8) txm_fault(0x5519, 0x4e300);
            if (txm_range_compare((const uint64_t*)key, (const uint64_t*)(rec+0xb8)) == 0) {
                if (rec <= rec + 0x130) return rec;
                txm_fault(0x5519, 0x4e300);
            }
            count = count - 1;
            tbl = tbl + 1;
        } while (count != 0);
    }
    return 0;
}

/* ================================================================== */
/* 0x4e30c .. 0x4f2f0 — record policy validate + DeviceTree + physmap */
/* ================================================================== */

/* FUN_0004e30c @ 0x0004e30c   (est. txm_ct_validate_chain)
 * Ghidra: void FUN_0004e30c(uint param_1,ulong *param_2,ulong *param_3,ulong *param_4)
 * Validates a chain of associated trust-cache records. Walks the list
 * rooted at *param_2; for each record validates its hash-type policy
 * (txm_ct_lookup_cached), enforces ordering constraints (0x90001..),
 * and cross-checks the SHA-256/SHA-384 family tags. Optionally returns
 * the AND-reduced policy flags via *param_4. Returns 0 on success.
 * Confidence: low (large multi-check validator; slot semantics inferred)
 * Notes: error codes 0x50015, 0x90001..0x9000d; calls FUN_00047dec/
 *   00047efc (out-of-batch helpers); SoftwareBreakpoint 0x5500/0x5519.
 */
static uint64_t txm_ct_validate_chain(uint32_t want, uint64_t *list,
                                      uint64_t *policy, uint64_t *out_flags)
{
    uint64_t canary = txm_canary;
    uint64_t rec = *list;
    uint64_t r = 0;
    if (((policy != NULL) && (policy[6] != 0)) && (*(uint64_t*)(policy[6] + 8) != 0)) {
        if (rec + 0xe0 < rec + 0xd0) txm_fault(0x5519, 0x4e870);
        if (txm_range_compare((const uint64_t*)(rec+0xd0), (const uint64_t*)(rec+0xd0)) != 0) {
            r = 0x50015; goto done;
        }
        rec = *list;
    }
    uint64_t n = 0, err_bits = 0, found = 0, and_flags = 0xffffffffffffffffull;
    int have_sha384 = 0;
    while (rec != 0) {
        uint64_t rec_end = rec + 0x130;
        uint64_t link = *(uint64_t*)(rec + 0x120);
        uint64_t link_end = link + 0x130;
        int skip_record = 0;
        if (link == 0) {
            if (rec_end < rec) txm_fault(0x5519, 0x4e870);
            if (txm_range_compare((const uint64_t*)(rec+0x78), (const uint64_t*)(rec+0x68)) != 0) {
                if (policy != NULL) {
                    if ((policy[2] & 1) == 0) {
                        if (policy[3] != 0) {
                            link = txm_ct_policy_global_sha384(rec + 0xa8);
                            found = (uint64_t)((link != 0) | found);
                            link_end = link + 0x130;
                            if (link != 0) { skip_record = 0; }
                            else if ((*(uint8_t*)((char*)policy + 0x13) & 1) != 0) {
                                skip_record = 1;
                            }
                        }
                    } else {
                        link = txm_ct_policy_global_sha256(rec + 0xa8,
                                *(uint8_t*)((char*)policy + 0x11) & 1);
                        found = (uint64_t)((link != 0) | found);
                        link_end = link + 0x130;
                        if (link != 0) { skip_record = 0; }
                    }
                    if (link == 0 && !(*(uint8_t*)((char*)policy+0x13)&1)) {
                        r = (uint64_t)(err_bits | 0x9000d);
                        goto done;
                    }
                }
            }
            if (link == 0) skip_record = 0;
        }
        if (rec_end < rec) txm_fault(0x5519, 0x4e870);
        if ((n != 0) && (1 < *(uint64_t*)(rec + 0x20))) {
            if ((*(uint8_t*)(rec + 0x109) & 1) == 0) { r = (uint64_t)(err_bits|0x90001); goto done; }
            if ((*(uint8_t*)(rec + 0x108) >> 2 & 1) == 0) { r = (uint64_t)(err_bits|0x90002); goto done; }
        }
        if ((*(uint64_t*)(rec + 200) != 0) && (*(uint64_t*)(rec + 200) < n)) {
            r = (uint64_t)(err_bits|0x90003); goto done;
        }
        if ((*(uint8_t*)(rec + 0x10a) & 1) != 0) { r = (uint64_t)(err_bits|0x90007); goto done; }
        if (txm_range_compare((const uint64_t*)(rec+0x28), (const uint64_t*)(rec+0x98)) != 0) {
            r = (uint64_t)(err_bits|0x90004); goto done;
        }
        if ((!skip_record) && (*(uint64_t*)(rec + 0xb0) != 0) && (*(uint64_t*)(rec + 0xa8) != 0)) {
            if ((link_end < link + 0x130) || (link + 0x130 < link) || (link + 200 < link + 0xb8))
                txm_fault(0x5519, 0x4e870);
            if (txm_range_compare((const uint64_t*)(rec+0xa8), (const uint64_t*)(rec+0xa8)) != 0) {
                r = (uint64_t)(err_bits | 0x9000a); goto done;
            }
        }
        if (((policy != NULL) && (n != 0)) && ((*(uint64_t*)(rec + 0xf0) & policy[1]) == 0)) {
            txm_record_drop(rec);                 /* FUN_00047dec */
        }
        if ((link == rec) && (*(uint64_t*)(rec + 0xf0) == 0)) {
            txm_record_promote(policy, rec);      /* FUN_00047efc */
        }
        and_flags = *(uint64_t*)(rec + 0xf0) & and_flags;
        if (((policy != NULL) && (policy[1] != 0)) && ((policy[1] & and_flags) == 0)) {
            r = (uint64_t)(err_bits|0x90005); goto done;
        }
        want = want | (uint64_t)(link == rec);
        if (!skip_record) {
            if ((link_end < link + 0x130) || (link + 0x130 < link)) txm_fault(0x5519, 0x4e870);
            r = txm_ct_lookup_cached_ret(want, link, rec + 0x10, rec + 0x28, rec + 0x38);
            if ((int)r != 0) goto done;
        }
        uint64_t next = n + 1;
        if (n > 0xfffffffffffffffeull) txm_fault(0x5500, 0x4e878);
        rec = *(uint64_t*)(rec + 0x120);
        err_bits += 0x100;
        n = next;
    }
    if (policy != NULL) {
        if (*policy != 0) {
            uint64_t expect = *policy;
            if (found) { expect = expect + 1; if (expect < 0xfffffffffffffffeull) {} }
            if (*policy != expect) { r = (uint64_t)((int)expect << 8 | 0x90006); goto done; }
        }
        if ((policy[3] != 0) && (*(uint64_t*)(policy[3] + 8) != 0)) {
            uint64_t rec2 = **(uint64_t**)(list[1] + 8);
            uint64_t re = rec2 + 0x130;
            if ((policy[2] & 1) == 0) {
                uint64_t v[2]={0,0}, t[2]={0,0}, h[2]={0,0};
                if (re < rec2 || rec2 + 0x68 < rec2 + 0x58) txm_fault(0x5519, 0x4e870);
                if (txm_ct_record_parse_fields((uint64_t*)(rec2+0x58), &v[0], &t[0], &h[0]) == 0) {
                    if (txm_range_compare(&v[0], (const uint64_t*)policy[4]) == 0 &&
                        txm_range_compare(&h[0], (const uint64_t*)policy[3]) == 0) {
                        if (txm_range_compare((const uint64_t*)policy[4], (const uint64_t*)0x12658) == 0) {
                            txm_range_compare(&t[0], (const uint64_t*)policy[5]);
                        }
                    } else {
                        r = txm_ct_lookup_2(policy[3], policy[4], policy[5], rec2+0x10, rec2+0x28, rec2+0x38);
                        if (r != 0) goto done;
                    }
                } else {
                    r = (uint64_t)((int)r << 8 | 0x90008);
                    goto done;
                }
            } else if (policy[2] & 1) {
                if (re < rec2) txm_fault(0x5519, 0x4e870);
                uint64_t off = found ? 0xa8 : 0xb8;
                uint64_t range = rec2 + off;
                uint64_t bound = found ? 200 : 0xb8;
                if (rec2 + bound < range + 0x10 || range + 0x10 < range) txm_fault(0x5519, 0x4e870);
                uint64_t rec3 = txm_ct_policy_global_sha256(range, *(uint8_t*)((char*)policy+0x11)&1);
                if (rec3 == 0) { r = (uint64_t)((int)r << 8 | 0x9000b); goto done; }
                if (!found) {
                    if (rec2+0x68 < rec2+0x58 || rec3+0x130 < rec3 || rec3+0x68 < rec3+0x58)
                        txm_fault(0x5519, 0x4e870);
                    /* compare hash ranges */
                }
                if (txm_ct_lookup_cached_ret(0x1d, rec3, 0, 0, 0) != 0) {
                    r = (uint64_t)((int)r << 8 | 0x9000c); goto done;
                }
            }
        }
    }
    r = 0;
    if (out_flags) *out_flags = and_flags;
done:
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_0004e880 @ 0x0004e880   (est. txm_dt_range_set)
 * Ghidra: void FUN_0004e880(ulong *param_1,ulong param_2,ulong param_3)
 * Stores the {ptr,size} DeviceTree range into *param_1; panics on
 * pointer-arithmetic overflow ("DeviceTree overflow ... p, size").
 * Confidence: high
 */
static void txm_dt_range_set(uint64_t *out, uint64_t ptr, uint64_t size)
{
    if (!__builtin_add_overflow(ptr, size, &(uint64_t){0})) {
        out[0] = ptr; out[1] = size;
        return;
    }
    txm_panic("DeviceTree overflow (p, size)");
}

/* FUN_0004e8b4 @ 0x0004e8b4   (est. txm_dt_path_resolve)
 * Ghidra: void FUN_0004e8b4(ulong*,int*,char*,ulong*)
 * Resolves a '/' - separated DeviceTree path (param_3) from node
 * *param_1, following child links via FUN_0004ec7c and matching each
 * path component against the node's properties (FUN_0004eb44). Returns
 * the resolved node into *param_4 (1 on success, 0xffffffff on failure).
 * Panics on out-of-range pointers ("Device tree pointer outside of data").
 * Confidence: medium
 * Notes: path components bounded to 0x3f bytes; panics at FUN_00029730.
 */
static uint64_t txm_dt_path_resolve(uint64_t *root, int *start, char *path, uint64_t *out)
{
    uint64_t canary = txm_canary;
    char comp[0x40];
    uint64_t r = 0xffffffff;
    if (root != NULL) {
        int *node = (int*)*root;
        int *cur = node;
        if (start != NULL) cur = start;
        if (cur < node || (int*)(root[1] + (uint64_t)node) < cur)
            txm_panic("Device tree pointer outside of data");
        if (*path == '/' && (path = path + 1, *path == '\0')) {
            *out = (uint64_t)cur;
            r = 1;
            goto done;
        }
        while (1) {
            int clen = 0;
            char c = *path;
            while (c != '\0') {
                if (c == '/') { path = path + 1; break; }
                if (clen == 0x3f) goto comp_end;
                comp[clen] = c;
                clen = clen + 1;
                path = path + 1;
                c = *path;
            }
comp_end:
            comp[clen] = 0;
            if (comp[0] == '\0') {
                if (*path == '\0') { *out = (uint64_t)cur; r = 1; goto done; }
            } else {
                int *next = cur + 2;
                int *base = (int*)*root;
                int *end = (int*)(root[1] + (uint64_t)base);
                if (next < base || end < next) txm_panic("Device tree pointer outside of data");
                if (cur[1] != 0) {
                    uint64_t name = 0; uint32_t len = 0;
                    int *it = NULL;
                    int i;
                    int cnt = *cur;
                    if (cnt == 0) it = NULL;
                    else {
                        do {
                            if (it + 9 < base || end < it + 9) txm_panic("Device tree pointer outside of data");
                            uint64_t v = (uint64_t)it + (uint64_t)(uint32_t)it[8];
                            if (__builtin_add_overflow((uint64_t)it, (uint64_t)(uint32_t)it[8], &(uint64_t){0}) || v > 0xffffffffffffffd7ull)
                                txm_panic("Device tree property overflow");
                            it = (int*)((v + 0x27) & ~0x3ull);
                            i = i - 1;
                        } while (i != 0);
                        if (end < it || it < base) txm_panic("Device tree pointer outside of data");
                    }
                    int found = txm_dt_property_find(it, 0x2eed, &name, &len, base, root[1]);
                    if (found == 1) {
                        uint32_t depth = 1;
                        while (1) {
                            char *pc = comp;
                            char *n = (char*)name;
                            char c2;
                            while (1) {
                                c2 = *n;
                                if (c2 != *pc) break;
                                pc = pc + 1; n = n + 1;
                                if (c2 == '\0') {
                                    cur = it;
                                    if (it == NULL) { r = 0xffffffff; goto done; }
                                    goto next_comp;
                                }
                            }
                            if ((uint32_t)cur[1] <= depth) break;
                            it = (int*)txm_dt_child(root, it);
                            depth = depth + 1;
                            found = txm_dt_property_find(it, 0x2eed, &name, &len, base, root[1]);
                        }
                    }
                }
            }
            r = 0xffffffff;
            goto done;
next_comp: ;
        }
    }
done:
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_0004eb24 @ 0x0004eb24   (est. txm_dt_property_find_wrap)
 * Ghidra: void FUN_0004eb24(undefined8*,undefined8,undefined8,undefined8,undefined8)
 * Thin wrapper around txm_dt_property_find passing the DT range from
 * *param_1.
 * Confidence: high
 */
static uint64_t txm_dt_property_find_wrap(uint64_t *root, int *node, uint64_t key,
                                          uint64_t *name, uint32_t *len)
{
    return txm_dt_property_find(node, key, name, len, (int*)*root, root[1]);
}

/* FUN_0004eb44 @ 0x0004eb44   (est. txm_dt_property_find)
 * Ghidra: undefined8 FUN_0004eb44(int*,long,ulong*,uint*,int*,long)
 * Searches the DeviceTree node param_1 for the property whose name
 * matches the string at param_2; on match returns 1 and stores the
 * property value {ptr,len} into out and out_len. Returns 0xffffffff on
 * no match. Walks the aligned property array, bounds-checked against the
 * {base,size} range (param_5, param_6).
 * Confidence: medium
 * Notes: panics "Device tree property overflow"/"pointer outside of data".
 */
static uint64_t txm_dt_property_find(int *node, uint64_t key, uint64_t *out,
                                     uint32_t *out_len, int *base, uint64_t size)
{
    if (node == NULL) return 0xffffffff;
    int *end = (int*)(size + (uint64_t)base);
    int *it = node + 2;
    if ((base <= it) && (it <= end)) {
        if (*node == 0) return 0xffffffff;
        int i = 0;
        while (((base <= it && it <= end) && (base <= it+9)) && (it+9 <= end)) {
            int *vptr = it + 9;
            uint32_t vlen = it[8];
            uint64_t v = (uint64_t)vlen;
            if ((int*)0xffffffffffffffdb < it || __builtin_add_overflow(v, (uint64_t)vptr, &(uint64_t){0}))
                txm_panic("Device tree property overflow");
            if ((int*)(v + (uint64_t)vptr) < base || end < (int*)(v + (uint64_t)vptr)) break;
            uint64_t o = 0;
            while ((char)((char*)it)[o] == *(char*)(key + o)) {
                o = o + 1;
                if (((char*)it)[o] == '\0') {
                    *out = (uint64_t)vptr;
                    *out_len = vlen;
                    return 1;
                }
            }
            if (__builtin_add_overflow((uint64_t)it, v, &(uint64_t){0}) || (uint64_t)it + v > 0xffffffffffffffd7ull)
                txm_panic("Device tree property overflow");
            it = (int*)(((uint64_t)it + v + 0x27) & ~0x3ull);
            i = i + 1;
            if (i == *node) return 0xffffffff;
        }
    }
    txm_panic("Device tree pointer outside of data");
}

/* FUN_0004ec7c @ 0x0004ec7c   (est. txm_dt_child)
 * Ghidra: int* FUN_0004ec7c(ulong *param_1,int *param_2)
 * Walks to the child node of DeviceTree node param_2: skips the node's
 * property array (param_2[1] entries) using aligned property-length
 * stepping, returning the next node pointer. Bounds-checked against the
 * DT range *param_1.
 * Confidence: medium
 */
static int *txm_dt_child(uint64_t *root, int *node)
{
    int *next = node + 2;
    int *base = (int*)*root;
    int *end = (int*)(root[1] + (uint64_t)base);
    if (base <= next && next <= end) {
        if (node == NULL || *node == 0) next = NULL;
        else {
            do {
                if (next + 9 < base || end < next + 9) txm_panic("Device tree pointer outside of data");
                uint64_t v = (uint64_t)next + (uint64_t)(uint32_t)next[8];
                if (__builtin_add_overflow((uint64_t)next, (uint64_t)(uint32_t)next[8], &(uint64_t){0}) || v > 0xffffffffffffffd7ull)
                    txm_panic("Device tree property overflow");
                next = (int*)((v + 0x27) & ~0x3ull);
                *node = *node - 1;
            } while (*node != 0);
            if (end < next || next < base) txm_panic("Device tree pointer outside of data");
            if (node[1] != 0) {
                uint32_t k = 0;
                do {
                    next = (int*)txm_dt_child(root, next);
                    k = k + 1;
                } while (k < (uint32_t)node[1]);
            }
        }
        return next;
    }
    txm_panic("Device tree pointer outside of data");
}

/* FUN_0004ed7c @ 0x0004ed7c   (est. txm_data_gone)
 * Ghidra: void FUN_0004ed7c(void)
 * Decompiler reports bad instruction data / truncated control flow at
 * this address. Assembly-level: this is a data-region guard, not a
 * callable function. Left as an annotated marker.
 * Confidence: low
 * Notes: decompiler "Bad instruction - Truncating control flow" halt.
 */
static void txm_data_gone(void)
{
    /* halt_baddata(): decompiler could not recover valid code here. */
}

/* FUN_0004edac @ 0x0004edac   (est. txm_physmap_config_load)
 * Ghidra: undefined8 FUN_0004edac(uint *param_1)
 * Loads the physical-memory-map configuration from the DT structure
 * param_1 into the global physmap state (DAT_000153b0..): region table
 * ptr/count, DRAM window, per-16KB-granule type table, and the physmap
 * base. The config version word (*param_1) gates which optional trailing
 * fields are loaded. Sets DAT_000153a8=1 (map initialized). Returns 0.
 * Confidence: medium
 * Notes: version-gated field loads (fields 2..0x36); DAT_000153a8 ready.
 */
static uint64_t txm_physmap_config_load(uint32_t *cfg)
{
    if (cfg != NULL) {
        *(uint64_t*)0x153b0 = *(uint64_t*)(cfg + 2);
        *(uint64_t*)0x153b8 = *(uint64_t*)(cfg + 4);
        *(uint64_t*)0x153c0 = *(uint64_t*)(cfg + 6);
        *(uint64_t*)0x153c8 = *(uint64_t*)(cfg + 8);
        *(uint64_t*)0x153d0 = *(uint64_t*)(cfg + 10);
        *(uint64_t*)0x153d8 = *(uint64_t*)(cfg + 0xc);
        *(uint64_t*)0x153e0 = *(uint64_t*)(cfg + 0xe);
        *(uint64_t*)0x153e8 = *(uint64_t*)(cfg + 0x10);
        *(uint64_t*)0x153f0 = *(uint64_t*)(cfg + 0x12);
        *(uint64_t*)0x153f8 = *(uint64_t*)(cfg + 0x14);
        *(uint64_t*)0x15400 = *(uint64_t*)(cfg + 0x16);
        *(uint64_t*)0x15408 = cfg[0x18];
        *(uint64_t*)0x15410 = *(uint64_t*)(cfg + 0x1a);
        *(uint64_t*)0x15418 = *(uint64_t*)(cfg + 0x1c);
        *(uint64_t*)0x15420 = *(uint64_t*)(cfg + 0x1e);
        uint32_t v = *cfg;
        if ((2 < v) && (*(uint64_t*)0x15428 = *(uint64_t*)(cfg + 0x20), v != 3) &&
            (*(uint64_t*)0x15430 = *(uint64_t*)(cfg + 0x22), 4 < v)) {
            *(uint64_t*)0x15438 = *(uint64_t*)(cfg + 0x24);
            *(uint64_t*)0x15440 = cfg[0x26];
            v = *cfg;
            if ((5 < v) && (*(uint64_t*)0x15448 = *(uint64_t*)(cfg + 0x28), v != 6) &&
                (*(uint64_t*)0x15450 = *(uint64_t*)(cfg + 0x2a), 7 < v)) {
                *(uint64_t*)0x15458 = *(uint64_t*)(cfg + 0x2c);
                *(uint64_t*)0x15460 = cfg[0x2e];
                *(uint64_t*)0x15468 = *(uint64_t*)(cfg + 0x30);
                *(uint64_t*)0x15470 = cfg[0x32];
                if ((8 < *cfg) && (*(uint64_t*)0x15478 = *(uint64_t*)(cfg + 0x34), *cfg != 9)) {
                    *(uint64_t*)0x15480 = *(uint64_t*)(cfg + 0x36);
                }
            }
        }
        *(uint64_t*)0x153a8 = 1;
        return 0;
    }
    return 2;
}

/* FUN_0004ef48 @ 0x0004ef48   (est. txm_physmap_pa_to_va)
 * Ghidra: undefined8 FUN_0004ef48(ulong param_1,long *param_2)
 * Translates the physical address param_1 to its virtual address via the
 * physmap region table (DAT_000153b8, count DAT_000153b0): for each
 * region {pa_base, va_base, 16KB-pages} whose window contains param_1,
 * computes va = va_base + (param_1 - pa_base). Returns 0 + *param_2=va,
 * 4 on no-match, 2 on null out, 1 if map uninitialized.
 * Confidence: medium
 * Notes: region entry stride 3 longs (pa, va, pages).
 */
static uint64_t txm_physmap_pa_to_va(uint64_t pa, uint64_t *out)
{
    if ((*(uint64_t*)0x153a8 & 1) == 0) return 1;
    if (out != NULL) {
        uint64_t count = *(uint64_t*)(*(uint64_t*)0x153b0);
        if (count != 0) {
            uint64_t *e = (uint64_t*)(*(uint64_t*)0x153b8 + 8);
            do {
                uint64_t base = e[-1];
                if ((base <= pa) && (pa < base + (uint64_t)(*(uint32_t*)(e + 1)) * 0x4000)) {
                    uint64_t va = *e + (pa - base);
                    if (va == 0) return 4;
                    *out = va;
                    return 0;
                }
                e = e + 3;
                count = count - 1;
            } while (count != 0);
        }
        return 4;
    }
    return 2;
}

/* FUN_0004efd4 @ 0x0004efd4   (est. txm_physmap_granule_type)
 * Ghidra: undefined8 FUN_0004efd4(ulong param_1,undefined1 *param_2)
 * Returns the physical-memory type of the 16KB granule containing pa
 * param_1 into *param_2. Within the DRAM window reads the per-granule
 * type byte from the granule table (DAT_000153e8); otherwise binary-
 * searches the external-range table (DAT_00015410, count DAT_00015408).
 * Returns 0; type 0x1a (unmapped) if not found. 1 if uninitialized,
 * 2 on null out.
 * Confidence: medium
 * Notes: binary search over 0x10-byte entries {page_hi, page_count};
 *   granule index = (pa>>0xe) & ... ; DRAM window [0x153c0,0x153c8).
 */
static uint64_t txm_physmap_granule_type(uint64_t pa, uint8_t *out)
{
    uint32_t u;
    uint8_t t;
    uint64_t e = 0;
    if ((*(uint64_t*)0x153a8 & 1) == 0) return 1;
    if (out == NULL) return 2;
    uint64_t g;
    if (pa < *(uint64_t*)0x153c0 || *(uint64_t*)0x153c8 <= pa) {
        if (*(uint64_t*)0x15408 == 0) { t = 0x1a; goto set; }
        uint32_t n = *(uint64_t*)0x15408 - 1;
        uint32_t lo = 0, mid = n >> 1;
        e = *(uint64_t*)0x15410 + (uint64_t)mid * 0x10;
        uint32_t hi = (*(uint32_t*)(e + 0xc) & 0xffffff) + *(uint32_t*)(e + 8);
        uint32_t p = (uint32_t)(pa >> 0xe);
        if (p < *(uint32_t*)(e + 8) || hi <= p) {
            uint32_t u2 = 0;
            do {
                if (u2 == n) { t = 0x1a; goto set; }
                if (hi <= p) { u2 = mid + 1; mid = n; }
                n = mid;
                mid = (n + u2) >> 1;
                e = *(uint64_t*)0x15410 + (uint64_t)mid * 0x10;
                hi = (*(uint32_t*)(e + 0xc) & 0xffffff) + *(uint32_t*)(e + 8);
            } while (p < *(uint32_t*)(e + 8) || hi <= p);
        }
    } else {
        g = *(uint64_t*)0x153e8 + ((pa - *(uint64_t*)0x153c0) >> 10 & 0x3ffffffffffff0ull);
        if (((*(uint64_t*)0x153e8 ^ g) & 0xffc0000000000000ull) != 0) {
            g = g & 0xffffffffffffull | 0xc8a2000000000000ull;
        }
        if (*(uint64_t*)0x153e8 == 0) { t = 0x1a; goto set; }
        u = *(uint8_t*)(g + 2);
        *out = (uint8_t)u;
        return 0;
    }
    u = *(uint8_t*)(e + 2);
    t = (uint8_t)u;
set:
    *out = t;
    return 0;
    (void)u;
}

/* FUN_0004f0e0 @ 0x0004f0e0   (est. txm_physmap_type_and_va)
 * Ghidra: undefined8 FUN_0004f0e0(undefined8,uint,long*)
 * Looks up the granule type of pa param_1 (via FUN_00061ea4 resolve),
 * requires it to equal the expected type param_2, then translates the
 * pa to a VA via the physmap region table. Returns 0 + *param_3=va;
 * 3 on type mismatch, 4 on no region/unresolved, 2 on null out, 1 if
 * uninitialized.
 * Confidence: medium
 */
static uint64_t txm_physmap_type_and_va(uint64_t pa, uint32_t want_type, uint64_t *out)
{
    uint64_t l;
    int i;
    uint32_t u3, u4;
    uint64_t u6;
    if ((*(uint64_t*)0x153a8 & 1) == 0) return 1;
    if (out == NULL) return 2;
    uint64_t local = 0;
    if (txm_pa_resolve(pa, &local) != 0) return 4;
    if ((*(uint64_t*)0x153a8 & 1) == 0) return 4;
    uint8_t t = 0;
    uint64_t rc = txm_physmap_granule_type(local, &t);
    (void)rc;
    if ((uint32_t)t != want_type) return 3;
    uint64_t count = *(uint64_t*)(*(uint64_t*)0x153b0);
    if (count != 0) {
        uint64_t *e = (uint64_t*)(*(uint64_t*)0x153b8 + 8);
        do {
            uint64_t base = e[-1];
            if ((base <= local) && (local < base + (uint64_t)(*(uint32_t*)(e + 1)) * 0x4000)) {
                uint64_t va = *e + (local - base);
                if (va == 0) return 4;
                *out = va;
                return 0;
            }
            e = e + 3;
            count = count - 1;
        } while (count != 0);
    }
    return 4;
}

/* FUN_0004f2b4 @ 0x0004f2b4   (est. txm_noop)
 * Ghidra: void FUN_0004f2b4(void)
 * Empty stub (no-op).
 * Confidence: high
 */
static void txm_noop(void) { return; }

/* FUN_0004f2c8 / 0004f2dc / 0004f2f0   (est. txm_supervisor_call_*)
 * Ghidra: void FUN_0004f2c8/4f2dc/4f2f0(void)
 * Each issues CallSupervisor(0) - a supervisor/EL3 service call. Three
 * identical trampolines; distinct service-selector semantics unknown.
 * Confidence: medium
 */
static void txm_supervisor_call_a(void) { CallSupervisor(0); }
static void txm_supervisor_call_b(void) { CallSupervisor(0); }
static void txm_supervisor_call_c(void) { CallSupervisor(0); }

/* ------------------------------------------------------------------ */
/* Out-of-batch / wrapper callees referenced above                     */
/* ------------------------------------------------------------------ */

/* FUN_00047dec @ 0x00047dec   (est. txm_record_drop)
 * Drops/removes a record from the active association set. Out-of-batch
 * callee of txm_ct_validate_chain (0x4e30c). Body in sibling region.
 * Confidence: low
 */
static void txm_record_drop(uint64_t rec) { (void)rec; }

/* FUN_00047efc @ 0x00047efc   (est. txm_record_promote)
 * Promotes a record into the caller's policy set. Out-of-batch callee
 * of txm_ct_validate_chain (0x4e30c). Body in sibling region.
 * Confidence: low
 */
static void txm_record_promote(uint64_t *policy, uint64_t rec) { (void)policy; (void)rec; }

/* Wrapper for FUN_0004d498 returning its integer status (used by the
 * chain validator instead of the void wrapper). */
static uint64_t txm_ct_lookup_cached_ret(uint32_t want, uint64_t rec, uint64_t h,
                                         uint64_t a, uint64_t b)
{
    (void)want; (void)rec; (void)h; (void)a; (void)b;
    return 0;
}

/* Wrapper for FUN_0004d6cc (CT lookup variant). See 0x4d6cc. */
static uint64_t txm_ct_lookup_2(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    return 0;
}

/* FUN_00061ea4 @ 0x00061ea4   (est. txm_pa_resolve)
 * Resolves a physical address into the physmap window (folds any
 * non-window VA into a canonical granule address). Out-of-batch callee
 * of txm_physmap_type_and_va (0x4f0e0). Body in sibling region.
 * Confidence: low
 */
static uint64_t txm_pa_resolve(uint64_t pa, uint64_t *out)
{
    (void)pa;
    if (out) *out = pa;
    return 0;
}

/* ================================================================== */
/* 0x4f304 .. 0x4f980 — image4 manifest/payload execution engine      */
/* ================================================================== */

/* FUN_0004f304/4f318/4f32c   (est. txm_supervisor_call_d/e/f)
 * Ghidra: void FUN_0004f304/4f318/4f32c(void)
 * CallSupervisor(0) trampolines, identical to 0x4f2c8 family.
 * Confidence: medium
 */
static void txm_supervisor_call_d(void) { CallSupervisor(0); }
static void txm_supervisor_call_e(void) { CallSupervisor(0); }
static void txm_supervisor_call_f(void) { CallSupervisor(0); }

/* FUN_0004f340 @ 0x0004f340   (est. txm_triple_store)
 * Ghidra: void FUN_0004f340(undefined8*,undefined8,undefined8,undefined8)
 * Stores three words into the 3-long output at param_1.
 * Confidence: high
 */
static void txm_triple_store(uint64_t *out, uint64_t a, uint64_t b, uint64_t c)
{
    out[0] = a; out[1] = b; out[2] = c;
}

/* FUN_0004f350 @ 0x0004f350   (est. txm_image4_init_handlers)
 * Ghidra: ulong FUN_0004f350(undefined8 *param_1)
 * Initializes an image4 handler set: iterates the {base, stride-table,
 * count} at param_1, calling each handler's init function via
 * FUN_0004f800 (vtable +0x40). On a handler init failure logs
 * "%s: %s failed to initialize image4 (%s)" and faults if the error code
 * exceeds 0x6b. Returns 0 on success.
 * Confidence: medium
 * Notes: calls FUN_000585b8 (log), FUN_0004f778 (bad-error panic).
 */
static uint64_t txm_image4_init_handlers(uint64_t *handlers)
{
    uint64_t r;
    uint64_t i;
    if (handlers[2] == 0) {
        r = 0;
        if (0x6b < (uint32_t)r) txm_fault_impl(0, 0);   /* FUN_0004f778 */
    } else {
        uint64_t count = 0;
        uint64_t base = handlers[0];
        uint64_t init = txm_ops_init(base, *(uint64_t*)(handlers[1] + count * 8));
        if ((int)init != 0) {
            txm_log_error(handlers[0], 0, "%s: %s failed to initialize image4 (%s)", 0x2f26);
            r = 0;
            if (0x6b < (uint32_t)r) txm_fault_impl(0, 0);
            return r;
        }
        count = count + 1;
        while (count < handlers[2]) {
            init = txm_ops_init(base, *(uint64_t*)(handlers[1] + count * 8));
            if ((int)init != 0) {
                txm_log_error(handlers[0], 0, "%s: %s failed to initialize image4 (%s)", 0x2f26);
                r = 0;
                if (0x6b < (uint32_t)r) txm_fault_impl(0, 0);
                return r;
            }
            count = count + 1;
        }
        r = 0;
    }
    return r;
    (void)i;
}

/* FUN_0004f408 @ 0x0004f408   (est. txm_image4_find_manifest)
 * Ghidra: ulong FUN_0004f408(long param_1,long param_2)
 * Searches the image4 manifest array (param_1: {base,count}) for a
 * manifest whose type field (+0x18) equals param_2 (and != -1); returns
 * it, or 0 if none. Faults 0x19 on overflow of the 0x70-byte entry.
 * Confidence: medium
 */
static uint64_t txm_image4_find_manifest(uint64_t arr, uint64_t type)
{
    uint64_t n = *(uint64_t*)(arr + 0x10);
    if (n != 0) {
        uint64_t *e = *(uint64_t**)(arr + 8);
        do {
            uint64_t m = *e;
            if (*(uint64_t*)(m + 0x18) != 0xffffffffffffffffull && *(uint64_t*)(m + 0x18) == type) {
                if (m < m + 0x70) return m;
                txm_fault_impl(0x19, 0);
            }
            n = n - 1;
            e = e + 1;
        } while (n != 0);
    }
    return 0;
}

/* FUN_0004f460 @ 0x0004f460   (est. txm_manifest_execute)
 * Ghidra: undefined8 FUN_0004f460(undefined8*,long,long,long)
 * Executes an image4 manifest/payload: dispatches to the manifest parser
 * (param_2+0x58 vtable) for the raw payload, parses the manifest
 * (FUN_0005aa8c) and payload (FUN_00059854), validates the manifest
 * (FUN_0005aae4) and payload parse (FUN_000598bc), decodes the payload
 * (FUN_00059a54), checks its size, invokes the activation callback
 * (param_2+0x60 vtable), and tears everything down. Returns 0 on
 * success; logs specific failure strings on each error path.
 * Confidence: medium
 * Notes: error strings at 0x2f49/2f69/2f8a/2fab/2fdc/3034; error code
 *   0x54 "decoded payload too large"; calls FUN_0004f810/4f840 (object
 *   ops) and FUN_0004f778 (bad-error panic); two 0x238/0x220-byte
 *   context buffers.
 */
static uint64_t txm_manifest_execute(uint64_t *params, uint64_t ops, uint64_t a3, uint64_t a4)
{
    uint64_t canary = txm_canary;
    uint8_t ctx_payload[0x238];
    uint8_t ctx_manifest[0x220];
    (void)ctx_payload; (void)ctx_manifest;
    uint64_t raw = *params;
    uint64_t size_arg = a3;
    if (a4 != 0) size_arg = a4;
    uint64_t parsed = (*(uint64_t(**)(uint64_t,uint64_t))(ops + 0x58))(ops, raw);
    uint64_t man = txm_manifest_parse((uint64_t*)ctx_payload, raw, ops + 0x30, a3);
    uint64_t pay = txm_payload_parse((uint64_t*)ctx_manifest, raw, size_arg);
    if (*(uint64_t*)(ops + 0x10) == 1) txm_manifest_digest(man, 0x1d510, 0);
    uint64_t r = txm_manifest_validate(man);
    uint64_t result = r;
    if ((int)r == 0) {
        r = txm_payload_validate(pay);
        if ((int)r != 0) {
            txm_log_error(raw, 0, "%s: %s failed to parse manifest (%d)", 0x2f69);
            result = r;
            goto teardown;
        }
        /* decode payload */
        uint64_t dec = txm_payload_decode(raw, (uint64_t)parsed, (*(uint64_t*)(ops + 0x10) != 1) ? man : 0, 0);
        uint64_t obj2 = 0;
        if ((int)dec == 0) {
            uint64_t obj = 0;
            if (*(uint64_t*)(ops + 0x10) < 2) {
                obj = txm_manifest_decode(man, &obj2);
            } else if (*(uint64_t*)(ops + 0x10) == 2) {
                obj = txm_payload_decode_v2(pay, &obj2);
            } else {
                obj = 0; obj2 = 0;
            }
            if (obj + 0x28 < obj + 0x28) txm_fault_impl(0x19, 0);
            if (*(uint64_t*)(ops + 0x20) < *(uint64_t*)(obj + 8)) {
                result = 0x54;
                txm_log_error(*params, 0, "%s: %s decoded payload too large (%s)", 0x2fdc);
                txm_object_release(&obj2);
                goto teardown;
            }
            if (obj + 0x28 <= obj) txm_fault_impl(0x19, 0);
            txm_ops_alloc(ops);
            uint64_t act = (*(uint64_t(**)(uint64_t,uint64_t,uint64_t))(ops + 0x60))(ops, *params, obj);
            if ((int)act != 0) {
                txm_log_error(*params, 0, "%s: %s activation failed (%d)", 0x3034);
                result = act;
                goto teardown;
            }
            txm_object_release(&obj2);
            txm_object_release(&obj2);
        } else {
            txm_log_error(*params, 0, "%s: %s failed to impose manifest for object (%s)", 0x2fab);
            result = dec;
            txm_object_release(&obj2);
            if (0x6b < (uint32_t)result) goto bad_err;
            txm_log_error(*params, 0, "%s: %s failed to execute object (%d)", 0x2f8a);
        }
    } else {
        txm_log_error(raw, 0, "%s: %s failed to parse payload (%d)", 0x2f49);
        result = r;
    }
teardown:
    txm_manifest_free(&man);
    txm_payload_free(&pay);
    if ((uint32_t)result < 0x6c) {
        if (txm_canary != canary) txm_stack_check_fail();
        return result;
    }
bad_err:
    txm_fault_impl(0, 0);   /* FUN_0004f778 */
    return 0;
}

/* FUN_0004f778 @ 0x0004f778   (est. txm_panic_bad_error)
 * Ghidra: void FUN_0004f778(void)
 * noreturn panic "panic: error not set to valid po..." (0x3b00).
 * Confidence: high
 */
static void txm_panic_bad_error(void) { txm_panic("panic: error not set to valid po..."); }

/* FUN_0004f7ac / 0004f7b0   (est. txm_trap_ctx_enter_x2)
 * Ghidra: void FUN_0004f7ac/4f7b0(void)
 * Enters the TXM trap context: FUN_0005077c (context save) with a PAC
 * check (0xc471), then FUN_00054848. Two identical entry points.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_a(void)
{
    txm_fault_check_pac();      /* 0xc471 PAC check */
    txm_ctx_finish(NULL);       /* FUN_00054848 */
}

/* FUN_0004f7d4 @ 0x0004f7d4   (est. txm_trap_ctx_enter_b)
 * Ghidra: void FUN_0004f7d4(void)
 * Same trap-context entry, passing the saved context to FUN_000548a8.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_b(void)
{
    uint64_t ctx = txm_ctx_save();      /* FUN_0005077c */
    txm_ctx_finish(&ctx);               /* FUN_000548a8 */
}

/* FUN_0004f800 @ 0x0004f800   (est. txm_ops_init)
 * Ghidra: void FUN_0004f800(undefined8 param_1,long param_2)
 * Dispatches through an ops-table: calls (*(param_2 + 0x40))() — the
 * object init vtable slot. Indirect jump (jumptable).
 * Confidence: medium
 */
static uint64_t txm_ops_init(uint64_t a, uint64_t ops)
{
    return (*(uint64_t(**)(void))(ops + 0x40))();
}

/* FUN_0004f810 @ 0x0004f810   (est. txm_ops_alloc)
 * Ghidra: long FUN_0004f810(long param_1)
 * Calls the ops-table allocation vtable slot (*(param_1+0x48))() and
 * returns param_1 (the ops table).
 * Confidence: medium
 */
static uint64_t txm_ops_alloc(uint64_t ops)
{
    (*(void(**)(void))(ops + 0x48))();
    return ops;
}

/* FUN_0004f840 @ 0x0004f840   (est. txm_object_release)
 * Ghidra: void FUN_0004f840(ulong *param_1)
 * Releases an image4 object: if *param_1 nonzero, calls its release
 * vtable slot (*(obj+0x50))() and zeroes the slot. Faults 0x19 on
 * overflow of the 0x70-byte object.
 * Confidence: medium
 */
static void txm_object_release(uint64_t *slot)
{
    uint64_t obj = *slot;
    if (obj != 0) {
        if (obj + 0x70 <= obj) txm_fault_impl(0x19, 0);
        (*(void(**)(void))(obj + 0x50))();
        *slot = 0;
    }
}

/* FUN_0004f88c @ 0x0004f88c   (est. txm_ops_dealloc)
 * Ghidra: void FUN_0004f88c(long param_1)
 * Calls the ops-table deallocation vtable slot (*(param_1+0x68))().
 * Indirect jump (jumptable).
 * Confidence: medium
 */
static void txm_ops_dealloc(uint64_t ops)
{
    (*(void(**)(void))(ops + 0x68))();
}

/* FUN_0004f89c @ 0x0004f89c   (est. txm_tuple_move)
 * Ghidra: void FUN_0004f89c(undefined8*,undefined8*)
 * Moves a 4-word tuple from param_2 to param_1, then clears param_2.
 * Confidence: high
 */
static void txm_tuple_move(uint64_t *dst, uint64_t *src)
{
    dst[1] = src[1];
    dst[0] = src[0];
    dst[3] = src[3];
    dst[2] = src[2];
    src[3] = 0;
}

/* FUN_0004f8b0 @ 0x0004f8b0   (est. txm_ops_destroy)
 * Ghidra: void FUN_0004f8b0(undefined8,long*)
 * Destroys an ops table: if *param_2 nonzero and its destructor vtable
 * slot (+0x18) is set, calls it and clears the slot. Faults 0x19 if the
 * object has data but no buffer.
 * Confidence: medium
 */
static void txm_ops_destroy(uint64_t a, uint64_t *slot)
{
    uint64_t obj = *slot;
    if ((obj != 0) && (*(uint64_t*)(obj + 0x18) != 0)) {
        if (*(uint64_t*)(obj + 0x10) == 0 && *(uint64_t*)(obj + 8) != 0) txm_fault_impl(0x19, 0);
        (*(void(**)(void))(obj + 0x18))();
        *slot = 0;
    }
    (void)a;
}

/* FUN_0004f904 @ 0x0004f904   (est. txm_manifest_obj_init)
 * Ghidra: undefined2* FUN_0004f904(undefined2*,undefined8)
 * Initializes a manifest object header: zeroes *param_1, sets the
 * version field (+0x34) to 0x30, and initializes the sub-object at
 * param_1+1 via FUN_00057d68.
 * Confidence: medium
 */
static uint16_t *txm_manifest_obj_init(uint16_t *obj, uint64_t a)
{
    *obj = 0;
    *(uint32_t*)(obj + 0x1a) = 0x30;
    txm_obj_sub_init(a, obj + 1);
    return obj;
}

/* FUN_0004f948 @ 0x0004f948   (est. txm_obj_copy_payload)
 * Ghidra: void FUN_0004f948(undefined8,long)
 * Copies a payload into an object: faults 0x19 if the destination
 * capacity (+8) exceeds 0x30, PAC-checks, then FUN_00057b58 into
 * param_2+0x10.
 * Confidence: medium
 */
static void txm_obj_copy_payload(uint64_t dst, uint64_t src)
{
    if (0x30 < *(uint64_t*)(src + 8)) txm_fault_impl(0x19, 0);
    txm_fault_check_pac();      /* 0xc471 */
    txm_obj_sub_copy(dst, src + 0x10);
}

/* FUN_0004f980 @ 0x0004f980   (est. txm_obj_copy_payload_v2)
 * Ghidra: void FUN_0004f980(undefined8,long)
 * Same payload copy, but the capacity check reads the uint at +0x34.
 * Confidence: medium
 */
static void txm_obj_copy_payload_v2(uint64_t dst, uint64_t src)
{
    if (0x30 < *(uint32_t*)(src + 0x34)) txm_fault_impl(0x19, 0);
    txm_fault_check_pac();      /* 0xc471 */
    txm_obj_sub_copy(dst, src + 2);
}

/* ================================================================== */
/* 0x4f9b8 .. 0x50b50 — image4 crypto/manifest globals + boot chain   */
/* ================================================================== */

/* FUN_0004f9b8 @ 0x0004f9b8   (est. txm_ops_slot_38)
 * Ghidra: void FUN_0004f9b8(long)
 * Indirect vtable dispatch: (*(param_1 + 0x38))().
 * Confidence: medium
 */
static void txm_ops_slot_38(uint64_t ops) { (*(void(**)(void))(ops + 0x38))(); }

/* FUN_0004f9c8 @ 0x0004f9c8   (est. txm_ops_slot_50)
 * Ghidra: void FUN_0004f9c8(long)
 * Indirect vtable dispatch: (*(param_1 + 0x50))().
 * Confidence: medium
 */
static void txm_ops_slot_50(uint64_t ops) { (*(void(**)(void))(ops + 0x50))(); }

/* FUN_0004f9d8 @ 0x0004f9d8   (est. txm_bootarg_lp_stng)
 * Ghidra: undefined8 FUN_0004f9d8(undefined8)
 * Reads the "lp_stng" boot variable from /chosen via FUN_00050f9c
 * (IODeviceTree property read); a missing property (0x13/2) or an error
 * leaves the default. Stores the result into DAT_000710d8 (boot policy
 * flag). Returns 0.
 * Confidence: medium
 * Notes: string "IODeviceTree:/chosen" 0x30d1, "lp_stng" 0x30eb.
 */
static uint64_t txm_bootarg_lp_stng(uint64_t ctx)
{
    uint64_t out = 0;
    uint64_t size = 8;
    uint64_t r = txm_dt_chosen_get(txm_iodev_get(), 0x30d1, 0x30eb, &out, &size);
    uint32_t u = (uint32_t)r;
    if (u == 0x13 || u == 2) out = 1;
    else if (u != 0) {
        txm_log_error(ctx, 0, "failed to read lp_stng (%d)", 0x30f3);
        if (u < 0x6c) return r;
        txm_fault_impl(0, 0);        /* FUN_0004f778 */
    }
    *(uint64_t*)0x710d8 = out;
    return 0;
}

/* FUN_0004fa84 / 4fa88   (est. txm_trap_ctx_enter_c/d)
 * Ghidra: void FUN_0004fa84/4fa88(void)
 * PAC-checked trap-context enter (FUN_0005077c + 0xc471 + FUN_00054848).
 * Confidence: medium
 */
static void txm_trap_ctx_enter_c(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }
static void txm_trap_ctx_enter_d(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }

/* FUN_0004faac @ 0x0004faac   (est. txm_trap_ctx_enter_e)
 * Ghidra: void FUN_0004faac(void)
 * Trap-context enter passing saved context to FUN_000548a8.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_e(void)
{
    uint64_t ctx = txm_ctx_save();
    txm_ctx_finish(&ctx);
}

/* FUN_0004fad8 @ 0x0004fad8   (est. txm_crypto_ctx_base)
 * Ghidra: undefined* FUN_0004fad8(void)
 * Returns the crypto context descriptor base (&DAT_000156a8).
 * Confidence: medium
 */
static uint64_t txm_crypto_ctx_base(void) { return 0x156a8; }

/* FUN_0004fae8 @ 0x0004fae8   (est. txm_cryptex1_manifest_decode)
 * Ghidra: undefined8 FUN_0004fae8(undefined8,undefined8,ulong*)
 * Decodes the cryptex1 manifest from the range *param_3: initializes it
 * as an image4 manifest (FUN_000579c8), parses the "hipsspih" section,
 * enforces a 0x40-byte max hash, reads the "gntsstng" integer, installs
 * the manifest hash (DAT_00071080) and the boot setting (DAT_000710d8).
 * Returns 0 on success.
 * Confidence: medium
 * Notes: strings "hipsspih" 0x1a9a8, "gntsstng" 0x1a500, "cryptex1
 *   manifest hash too large" 0x314c; DAT_00071080 manifest hash,
 *   DAT_000710d8 setting.
 */
static uint64_t txm_cryptex1_manifest_decode(uint64_t a, uint64_t ctx, uint64_t *range)
{
    uint64_t canary = txm_canary;
    uint64_t man = 0, val = 0, hash = 0;
    if (*range + range[1] < *range) txm_fault_impl(0x19, 0);
    int r = txm_img4_manifest_init(*range, range[1], &man);
    uint64_t err;
    if (r == 0) {
        r = txm_img4_parse_section(&man, "hipsspih", &val, &hash);
        if (r == 0) {
            if (0x40 < hash) { txm_log_error(ctx, 0, "cryptex1 manifest hash too large", 0x314c); err = 0x54; goto done; }
            err = txm_img4_section_u64(&man, 0x1a520, "gntsstng", &val);
            if ((int)err != 1) {
                if ((int)err != 0) {
                    err = txm_img4_err(err);
                    txm_log_error(ctx, 0, "Img4DecodeGetInteger64FromSection (%s)", 0x318c);
                    goto done;
                }
                *(uint64_t*)0x710d8 = val;
            }
            *(uint64_t*)0x71080 = txm_img4_install_hash(0x71088, val, hash);
            txm_img4_hash_finalize(*(uint64_t*)0x71080, (uint64_t)&hash + 8);
            err = 0;
            goto done;
        }
        err = txm_img4_err(r);
        txm_log_error(ctx, 0, "Img4DecodeGetDataFromSection (%d)", 0x312b);
    } else {
        err = txm_img4_err(r);
        txm_log_error(ctx, 0, "Img4DecodeInitAsManifest (%d)", 0x310e);
    }
done:
    if (0x6b < (uint32_t)err) txm_fault_impl(0, 0);
    if (txm_canary != canary) txm_stack_check_fail();
    return err;
}

/* FUN_0004fcec / 4fcf0   (est. txm_cryptex1_hash_copy)
 * Ghidra: undefined8 FUN_0004fcec/4fcf0(undefined8,undefined8)
 * Copies the cryptex1 manifest hash (DAT_00071080, at +8, 0x40 max)
 * into the output via FUN_000522d8. Returns 0, or 2 if no hash installed.
 * Confidence: medium
 */
static uint64_t txm_cryptex1_hash_copy(uint64_t a, uint64_t out)
{
    if (*(uint64_t*)0x71080 == 0) return 2;
    if (0x40 < *(uint64_t*)(*(uint64_t*)0x71080 + 0x48)) txm_fault_impl(0x19, 0);
    txm_img4_hash_copy(out, *(uint64_t*)0x71080 + 8);
    return 0;
}

/* FUN_0004fd38 @ 0x0004fd38   (est. txm_cryptex1_hash_ptr)
 * Ghidra: undefined8* FUN_0004fd38(void)
 * Returns &DAT_00071080 (the cryptex1 manifest hash slot).
 * Confidence: high
 */
static uint64_t *txm_cryptex1_hash_ptr(void) { return (uint64_t*)0x71080; }

/* FUN_0004fd48 @ 0x0004fd48   (est. txm_return_zero)
 * Ghidra: undefined8 FUN_0004fd48(void)
 * Returns 0.
 * Confidence: high
 */
static uint64_t txm_return_zero(void) { return 0; }

/* FUN_0004fd54 / 4fd58   (est. txm_trap_ctx_enter_f/g)
 * Ghidra: void FUN_0004fd54/4fd58(void)
 * PAC-checked trap-context enter.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_f(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }
static void txm_trap_ctx_enter_g(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }

/* FUN_0004fd7c @ 0x0004fd7c   (est. txm_trap_ctx_enter_h)
 * Ghidra: void FUN_0004fd7c(void)
 * Trap-context enter passing saved context.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_h(void)
{
    uint64_t ctx = txm_ctx_save();
    txm_ctx_finish(&ctx);
}

/* FUN_0004fda8 / 4fdac   (est. txm_manifest_support_table)
 * Ghidra: undefined* FUN_0004fda8/4fdac(undefined8,undefined8)
 * Selects the manifest support-table descriptor: base &DAT_00015488, or
 * &DAT_00015ab8 if the object at FUN_0005860c has a non-null +0x48.
 * Confidence: medium
 */
static uint64_t txm_manifest_support_table(uint64_t a, uint64_t b)
{
    uint64_t obj = txm_obj_resolve(b, 0);
    if (*(uint64_t*)(obj + 0x48) != 0) return 0x15ab8;
    return 0x15488;
}

/* FUN_0004fde4 @ 0x0004fde4   (est. txm_manifest_hash_install)
 * Ghidra: undefined8 FUN_0004fde4(undefined8,undefined8,long)
 * Installs the manifest hash (from param_3) into the global DAT_000710e0
 * if empty; the hash must be <= 0x800 bytes. Returns 0, 0x54 (too big),
 * or 0x25 (already set).
 * Confidence: medium
 * Notes: global DAT_000710e0 (installed), DAT_000710e8 (buffer),
 *   DAT_000718e8 (size).
 */
static uint64_t txm_manifest_hash_install(uint64_t a, uint64_t b, uint64_t src)
{
    uint64_t len = *(uint64_t*)(src + 8);
    if (*(uint64_t*)0x710e0 == 0) {
        if (len < 0x801) {
            txm_img4_hash_copy(0x710e8, src);
            if (0x800 < *(uint64_t*)0x710e8) txm_fault_impl(0x19, 0);
            *(uint64_t*)0x710e0 = 0x710e8;
            *(uint64_t*)0x718e8 = len;
            return 0;
        }
        return 0x54;
    }
    return 0x25;
}

/* FUN_0004fe84 @ 0x0004fe84   (est. txm_manifest_hash_copy_installed)
 * Ghidra: undefined8 FUN_0004fe84(undefined8,undefined8,undefined8)
 * Copies the installed manifest hash (at +0x808 of the ops table) via
 * FUN_000522d8. Returns 0.
 * Confidence: medium
 */
static uint64_t txm_manifest_hash_copy_installed(uint64_t a, uint64_t b, uint64_t out)
{
    txm_img4_hash_copy(out, a + 0x808);
    return 0;
}

/* FUN_0004feb4 @ 0x0004feb4   (est. txm_expert_record_find)
 * Ghidra: long* FUN_0004feb4(long*,long)
 * Searches the 0x18-entry expert-record table (param_1, stride 3 longs)
 * for the record matching param_2 either by id (type 3 compare) or by
 * pointer identity; returns the matching slot or NULL.
 * Confidence: medium
 */
static uint64_t *txm_expert_record_find(uint64_t *table, uint64_t key)
{
    uint64_t i = 0;
    uint64_t remaining = 0x18;
    uint64_t *e = table;
    while (1) {
        uint64_t rec = *e;
        if (rec == 0) return NULL;
        if (*(uint64_t*)(key + 0x10) == 3) {
            if (txm_str_eq(*(uint64_t*)(key + 8), *(uint64_t*)(rec + 8)) == 0) return e;
            rec = *e;
        }
        if (rec == key) break;
        i = i + 1;
        e = e + 3;
        remaining = remaining - 1;
        if (remaining == 0) return NULL;
    }
    return table + i * 3;
}

/* FUN_0004ff48 @ 0x0004ff48   (est. txm_expert_record_check)
 * Ghidra: undefined4 FUN_0004ff48(undefined8,undefined8,undefined4)
 * If the expert-record table lookup (FUN_0004feb4) finds a match, forces
 * param_3 to 0; otherwise returns param_3 unchanged.
 * Confidence: medium
 */
static uint32_t txm_expert_record_check(uint64_t a, uint64_t b, uint32_t c)
{
    if (txm_expert_record_find((uint64_t*)0, b) != NULL) c = 0;
    return c;
}

/* FUN_0004ff74 @ 0x0004ff74   (est. txm_digest_to_hex)
 * Ghidra: void FUN_0004ff74(char*,byte*,ulong)
 * Formats a binary digest (param_2, param_3 bytes) as lowercase hex into
 * the 0x81-byte buffer param_1. If param_3==0, fills param_1 with
 * 0x2f5e7b2a0e16d5ef... no - fills with the "no digest" placeholder via
 * FUN_0002efc4; else hex-encodes 2 chars/byte with the "0123456789abcdef"
 * nibble table. Panics 0x19 on out-of-bounds; FUN_000500c0 panics on
 * digest length >= 0x41.
 * Confidence: medium
 * Notes: hex table "0123456789abcdef" 0x2575; stack canary guarded.
 */
static void txm_digest_to_hex(char *out, const uint8_t *digest, uint64_t len)
{
    uint64_t canary = txm_canary;
    const char hex[] = "0123456789abcdef";
    if (len < 0x41) {
        for (int i = 0; i < 0x81; i++) out[i] = 0;
        if (len == 0) {
            if (txm_canary == canary) {
                txm_fault_check_pac();
                txm_img4_no_digest(out, 0x3531, 0x81, 0xffffffffffffffffull);
                return;
            }
        } else {
            char *p = out;
            do {
                uint8_t b = *digest;
                out[0] = hex[b >> 4];
                out[1] = hex[b & 0xf];
                out[2] = 0;
                p += 2;
                len = len - 1;
                digest = digest + 1;
            } while (len != 0);
            if (txm_canary == canary) return;
        }
    } else {
        txm_digest_len_panic();
    }
    txm_stack_check_fail();
}

/* FUN_000500c0 @ 0x000500c0   (est. txm_digest_len_panic)
 * Ghidra: void FUN_000500c0(void)
 * noreturn panic "panic: bogus digest length (%lu)" (0x3511).
 * Confidence: high
 */
static void txm_digest_len_panic(void) { txm_panic("panic: bogus digest length (%lu)"); }

/* FUN_000500f4 / 4f8   (est. txm_trap_ctx_enter_i/j)
 * Ghidra: void FUN_000500f4/4f8(void)
 * PAC-checked trap-context enter.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_i(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }
static void txm_trap_ctx_enter_j(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }

/* FUN_0005011c @ 0x0005011c   (est. txm_trap_ctx_enter_k)
 * Ghidra: void FUN_0005011c(void)
 * Trap-context enter passing saved context.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_k(void)
{
    uint64_t ctx = txm_ctx_save();
    txm_ctx_finish(&ctx);
}

/* FUN_00050148 @ 0x00050148   (est. txm_libimage4_ops)
 * Ghidra: undefined* FUN_00050148(void)
 * Returns the libimage4 ops-table descriptor (&DAT_0001d0c8).
 * Confidence: medium
 */
static uint64_t txm_libimage4_ops(void) { return 0x1d0c8; }

/* FUN_00050158 @ 0x00050158   (est. txm_libimage4_name)
 * Ghidra: char* FUN_00050158(void)
 * Boots the expert chain: sets up the image4 context, registers the
 * specialist, checks the expert parser (FUN_00057ec0) and returns the
 * libimage4 name; panics "failed to boot expert" if the parser check
 * fails.
 * Confidence: medium
 * Notes: string "libimage4" 0x3609, "panic: failed to boot expert (%d)"
 *   0x35e8, "set specialist" 0x36db.
 */
static char *txm_libimage4_name(void)
{
    uint64_t ctx = txm_ctx_ops();
    FUN_00025c6c(0x35e5);
    txm_expert_announce();
    uint64_t obj = txm_iodev_get();
    txm_expert_parse();
    uint64_t ops = txm_obj_resolve(obj, 0);
    txm_expert_setup(ctx, obj, ops);
    int r = txm_expert_validate(obj);
    if (r != 0) { txm_panic_boot_expert(); return (char*)0x3609; }
    txm_expert_finish(obj);
    txm_fault_check_pac();
    return (char*)txm_expert_name(obj);
}

/* FUN_000501fc @ 0x000501fc   (est. txm_libimage4_name_static)
 * Ghidra: char* FUN_000501fc(void)
 * Returns the constant "libimage4" name.
 * Confidence: high
 */
static char *txm_libimage4_name_static(void) { return (char*)0x3609; }

/* FUN_0005020c @ 0x0005020c   (est. txm_expert_available)
 * Ghidra: uint FUN_0005020c(long)
 * Returns whether the expert boot path is available: false unless param_1
 * is nonzero and the boot flag DAT_00010800 bit 0 is clear, in which
 * case it runs FUN_00022a38(0,param_1,0) and returns its complement.
 * Confidence: medium
 */
static uint32_t txm_expert_available(uint64_t p)
{
    uint32_t r = 0;
    if ((p != 0) && ((*(uint64_t*)0x10800 & 1) == 0)) {
        r = FUN_00022a38(0, p, 0);
        r = r ^ 1;
    }
    return r;
}

/* FUN_00050254 @ 0x00050254   (est. txm_panic_boot_expert)
 * Ghidra: void FUN_00050254(void)
 * noreturn panic "panic: failed to boot expert (%d)" (0x35e8).
 * Confidence: high
 */
static void txm_panic_boot_expert(void) { txm_panic("panic: failed to boot expert (%d)"); }

/* FUN_000502cc @ 0x000502cc   (est. txm_odometer_verify)
 * Ghidra: undefined8 FUN_000502cc(undefined8,undefined8*)
 * Verifies the boot-chain odometer: resolves the manifest hash
 * (FUN_00052a34), builds the "BC" context (FUN_00059e14), runs the
 * boot-chain integrity check (FUN_0005c230); on failure logs
 * "odometer: %s: %s boot chain integrity..." (0x364b) and releases the
 * context. Returns the check result.
 * Confidence: medium
 */
static uint64_t txm_odometer_verify(uint64_t a, uint64_t *params)
{
    uint64_t canary = txm_canary;
    uint64_t ctx = params[1], c2 = params[2];
    uint64_t hash = txm_manifest_hash_resolve(a, c2);
    uint64_t bc_ctx = 0;
    txm_bc_ctx_build(ctx, c2, &bc_ctx);
    uint64_t r = txm_bc_verify(params, a, hash, &bc_ctx);
    if ((uint32_t)r != 0) {
        uint64_t name = *params;
        txm_bc_ctx_release(params[2]);
        txm_log_error(name, 0, "odometer: %s: %s boot chain integrity (%s)", 0x364b);
        if (0x6b < (uint32_t)r) txm_fault_impl(0, 0);
    }
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_000503cc / 4d0   (est. txm_trap_ctx_enter_l/m)
 * Ghidra: void FUN_000503cc/4d0(void)
 * PAC-checked trap-context enter.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_l(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }
static void txm_trap_ctx_enter_m(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }

/* FUN_000503f4 @ 0x000503f4   (est. txm_trap_ctx_enter_n)
 * Ghidra: void FUN_000503f4(void)
 * Trap-context enter passing saved context.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_n(void)
{
    uint64_t ctx = txm_ctx_save();
    txm_ctx_finish(&ctx);
}

/* FUN_00050420 @ 0x00050420   (est. txm_obj_data_ptr)
 * Ghidra: undefined8 FUN_00050420(long)
 * Returns the object's data pointer (*(param_1 + 0x78)).
 * Confidence: high
 */
static uint64_t txm_nonce_derive(uint64_t slot, uint64_t ctx, uint64_t *data);
static uint64_t txm_obj_data_ptr(uint64_t obj) { return *(uint64_t*)(obj + 0x78); }

/* FUN_0005042c @ 0x0005042c   (est. txm_obj_data_head)
 * Ghidra: undefined8 FUN_0005042c(long)
 * Returns **((*(param_1+0x78))+0x10) - the object data list head.
 * Confidence: medium
 */
static uint64_t txm_obj_data_head(uint64_t obj)
{
    return **(uint64_t**)(*(uint64_t*)(obj + 0x78) + 0x10);
}

/* FUN_00050440 @ 0x00050440   (est. txm_noop2)
 * Ghidra: void FUN_00050440(void)
 * Empty stub.
 * Confidence: high
 */
static void txm_noop2(void) { return; }

/* FUN_00050448 @ 0x00050448   (est. txm_unsupported_4e)
 * Ghidra: undefined8 FUN_00050448(void)
 * Returns error code 0x4e (unsupported).
 * Confidence: high
 */
static uint64_t txm_unsupported_4e(void) { return 0x4e; }

/* FUN_00050454 @ 0x00050454   (est. txm_noop3)
 * Ghidra: void FUN_00050454(void)
 * Empty stub.
 * Confidence: high
 */
static void txm_noop3(void) { return; }

/* FUN_0005045c @ 0x0005045c   (est. txm_noop4)
 * Ghidra: void FUN_0005045c(void)
 * Empty stub.
 * Confidence: high
 */
static void txm_noop4(void) { return; }

/* FUN_00050464 @ 0x00050464   (est. txm_ops_release_vtbl)
 * Ghidra: void FUN_00050464(long)
 * Indirect vtable dispatch through the object: (*(**(obj+0x10)+0x30))().
 * Confidence: medium
 */
static void txm_ops_release_vtbl(uint64_t obj)
{
    (*(void(**)(void))(*(uint64_t*)*(uint64_t**)(obj + 0x10) + 0x30))();
}

/* FUN_000504a0 @ 0x000504a0   (est. txm_ops_base_ptr)
 * Ghidra: undefined8 FUN_000504a0(long)
 * Returns **(obj+0x10) - the ops-table base pointer.
 * Confidence: high
 */
static uint64_t txm_ops_base_ptr(uint64_t obj) { return **(uint64_t**)(obj + 0x10); }

/* FUN_000504b4 @ 0x000504b4   (est. txm_err_2d)
 * Ghidra: undefined8 FUN_000504b4(void)
 * Returns error code 0x2d.
 * Confidence: high
 */
static uint64_t txm_err_2d(void) { return 0x2d; }

/* FUN_000504c0..050508 (7 fns)   (est. txm_err_4e_*)
 * Ghidra: undefined8 FUN_000504c0/4cc/4d8/4e4/4f0/4fc/508(void)
 * Each returns error code 0x4e (unsupported).
 * Confidence: high
 */
static uint64_t txm_err_4e_a(void) { return 0x4e; }
static uint64_t txm_err_4e_b(void) { return 0x4e; }
static uint64_t txm_err_4e_c(void) { return 0x4e; }
static uint64_t txm_err_4e_d(void) { return 0x4e; }
static uint64_t txm_err_4e_e(void) { return 0x4e; }
static uint64_t txm_err_4e_f(void) { return 0x4e; }
static uint64_t txm_err_4e_g(void) { return 0x4e; }

/* FUN_00050514 @ 0x00050514   (est. txm_manifest_set_property)
 * Ghidra: undefined8 FUN_00050514(long,undefined8,long,undefined8)
 * Sets a manifest property: resolves the object (**(obj+0x10)), looks up
 * the property slot by key (FUN_00056e90), and stores the value via
 * FUN_00057264. The special key 0x1a248 routes to FUN_000591d8. Returns
 * 0, or 2 on unknown property.
 * Confidence: medium
 */
static uint64_t txm_manifest_set_property(uint64_t obj, uint64_t a, uint64_t key, uint64_t val)
{
    if (key != 0x1a248) {
        uint64_t base = **(uint64_t**)(obj + 0x10);
        uint64_t slot = txm_obj_prop_lookup(base, key);
        if (slot == 0) return 2;
        txm_obj_prop_set(base, key, val);
        return 0;
    }
    txm_fault_check_pac();
    return txm_manifest_set_prop_special(obj, a, val);
}

/* FUN_000505a8 @ 0x000505a8   (est. txm_manifest_set_property_v2)
 * Ghidra: undefined8 FUN_000505a8(long,undefined8,undefined8,undefined8)
 * Same property set via FUN_00057318. Returns 0, or 2 on unknown.
 * Confidence: medium
 */
static uint64_t txm_manifest_set_property_v2(uint64_t obj, uint64_t a, uint64_t key, uint64_t val)
{
    uint64_t base = **(uint64_t**)(obj + 0x10);
    uint64_t slot = txm_obj_prop_lookup(base, key);
    if (slot == 0) return 2;
    txm_obj_prop_set_v2(base, key, val);
    return 0;
}

/* FUN_00050608 @ 0x00050608   (est. txm_manifest_set_property_v3)
 * Ghidra: undefined8 FUN_00050608(long,undefined8,undefined8,undefined8)
 * Same via FUN_000573c8. Returns 0, or 2 on unknown.
 * Confidence: medium
 */
static uint64_t txm_manifest_set_property_v3(uint64_t obj, uint64_t a, uint64_t key, uint64_t val)
{
    uint64_t base = **(uint64_t**)(obj + 0x10);
    uint64_t slot = txm_obj_prop_lookup(base, key);
    if (slot == 0) return 2;
    txm_obj_prop_set_v3(base, key, val);
    return 0;
}

/* FUN_00050668 @ 0x00050668   (est. txm_manifest_set_property_v4)
 * Ghidra: undefined8 FUN_00050668(long,undefined8,undefined8,undefined8)
 * Same via FUN_00057478. Returns 0, or 2 on unknown.
 * Confidence: medium
 */
static uint64_t txm_manifest_set_property_v4(uint64_t obj, uint64_t a, uint64_t key, uint64_t val)
{
    uint64_t base = **(uint64_t**)(obj + 0x10);
    uint64_t slot = txm_obj_prop_lookup(base, key);
    if (slot == 0) return 2;
    txm_obj_prop_set_v4(base, key, val);
    return 0;
}

/* FUN_000506c8 @ 0x000506c8   (est. txm_manifest_set_property_v5)
 * Ghidra: undefined8 FUN_000506c8(long,undefined8,undefined8,undefined8)
 * Same via FUN_0005753c. Returns 0, or 2 on unknown.
 * Confidence: medium
 */
static uint64_t txm_manifest_set_property_v5(uint64_t obj, uint64_t a, uint64_t key, uint64_t val)
{
    uint64_t base = **(uint64_t**)(obj + 0x10);
    uint64_t slot = txm_obj_prop_lookup(base, key);
    if (slot == 0) return 2;
    txm_obj_prop_set_v5(base, key, val);
    return 0;
}

/* FUN_00050728 / 4f34   (est. txm_return_zero_b/c)
 * Ghidra: undefined8 FUN_00050728/4f34(void)
 * Return 0.
 * Confidence: high
 */
static uint64_t txm_return_zero_b(void) { return 0; }
static uint64_t txm_return_zero_c(void) { return 0; }

/* FUN_00050740 / 4f48   (est. txm_noop5/6)
 * Ghidra: void FUN_00050740/4f48(void)
 * Empty stubs.
 * Confidence: high
 */
static void txm_noop5(void) { return; }
static void txm_noop6(void) { return; }

/* FUN_00050750 @ 0x00050750   (est. txm_panic_should_never)
 * Ghidra: void FUN_00050750(void)
 * noreturn panic "panic: should never be called" (0x36bd).
 * Confidence: high
 */
static void txm_panic_should_never(void) { txm_panic("panic: should never be called"); }

/* FUN_0005077c @ 0x0005077c   (est. txm_ctx_current)
 * Ghidra: undefined8 FUN_0005077c(void)
 * Returns the current TXM context (DAT_00071970).
 * Confidence: high
 */
static uint64_t txm_ctx_current(void) { return *(uint64_t*)0x71970; }

/* FUN_0005078c @ 0x0005078c   (est. txm_ctx_current_or_dispatch)
 * Ghidra: undefined8 FUN_0005078c(void)
 * Returns the current context, or if the dispatch hook (DAT_00071978) is
 * set, calls it first.
 * Confidence: medium
 */
static uint64_t txm_ctx_current_or_dispatch(void)
{
    if (*(uint64_t*)0x71978 != 0) return (*(uint64_t(**)(void))0x71978)();
    return *(uint64_t*)0x71970;
}

/* FUN_000507b0 @ 0x000507b0   (est. txm_ctx_dispatch_table)
 * Ghidra: undefined* FUN_000507b0(void)
 * Returns &DAT_00019238 (the context dispatch table).
 * Confidence: medium
 */
static uint64_t txm_ctx_dispatch_table(void) { return 0x19238; }

/* FUN_000507c0 @ 0x000507c0   (est. txm_ctx_set_specialist)
 * Ghidra: void FUN_000507c0(long,undefined8,undefined8)
 * Sets the specialist context: stores the context's table pointer
 * (param_1+0x18), calls FUN_00057e10 with tag 0x67656e78 ("genx") and
 * message "set specialist", then writes param_2/param_3 into the table.
 * Confidence: medium
 */
static void txm_ctx_set_specialist(uint64_t ctx, uint64_t a, uint64_t b)
{
    uint64_t *tbl = *(uint64_t**)(ctx + 0x18);
    txm_ctx_tag(ctx, 0x67656e78, "set specialist");
    *tbl = a;
    tbl[2] = b;
}

/* FUN_0005080c @ 0x0005080c   (est. txm_expert_query_all)
 * Ghidra: void FUN_0005080c(long)
 * Queries every expert record from the expert table: iterates the
 * record list (FUN_000566b8), dispatches on each record's type
 * (FUN_0005861c/587f0/589bc/58b88/58d18) and applies the result via
 * FUN_00056f04/56fac/57050/570f4/571ac. Panics 0x19 on malformed
 * records and "unreachable case" (0x36f2) / "failed to query expert"
 * (0x3730).
 * Confidence: medium
 * Notes: per-type expert query/apply vtable; 0x3e800000000 cursor.
 */
static void txm_expert_query_all(uint64_t ctx)
{
    uint64_t canary = txm_canary;
    uint64_t list = *(uint64_t*)(ctx + 0x18);
    uint64_t base = (*(uint64_t**)(ctx + 0x10))[2];
    uint64_t cur = list + 0x20;
    uint64_t table = **(uint64_t**)(ctx + 0x10);
    uint64_t rec = txm_expert_list_next(&cur);
    while (rec != 0) {
        uint64_t type = **(uint64_t**)(rec + 0x28);
        int r;
        switch (type) {
        case 0: r = FUN_0005861c(table, base, rec, (uint8_t*)&cur); break;
        case 1: r = FUN_000587f0(table, base, rec, (uint8_t*)&cur); break;
        case 2: r = FUN_000589bc(table, base, rec, (uint8_t*)&cur); break;
        case 3: r = FUN_00058b88(table, base, rec, (uint8_t*)&cur); break;
        case 4: r = FUN_00058d18(table, base, rec, (uint8_t*)&cur); break;
        default: txm_panic("panic: unreachable case (%s)"); break;
        }
        if (r == 0) {
            type = **(uint64_t**)(rec + 0x28);
            switch (type) {
            case 0: FUN_00056f04(cur, rec, (uint8_t*)&cur); break;
            case 1: FUN_00056fac(cur, rec, (uint8_t*)&cur); break;
            case 2: FUN_00057050(cur, rec, (uint8_t*)&cur); break;
            case 3: FUN_000570f4(cur, rec, (uint8_t*)&cur); break;
            case 4: FUN_000571ac(cur, rec, (uint8_t*)&cur); break;
            default: txm_panic("panic: unreachable case (%s)"); break;
            }
        } else if (r != 2 && r != 0x13 && r != 0x2d) {
            txm_panic("panic: failed to query expert (%s)");
        }
        rec = txm_expert_list_next(&cur);
    }
    if (txm_canary != canary) txm_stack_check_fail();
}

/* FUN_00050aac / 4ab4   (est. txm_noop7/8)
 * Ghidra: void FUN_00050aac/4ab4(void)
 * Empty stubs.
 * Confidence: high
 */
static void txm_noop7(void) { return; }
static void txm_noop8(void) { return; }

/* FUN_00050abc @ 0x00050abc   (est. txm_ops_release_vtbl2)
 * Ghidra: void FUN_00050abc(long)
 * Indirect vtable dispatch through the object's second table:
 * (*(*(*(obj+0x10)+0x10)+0x30))().
 * Confidence: medium
 */
static void txm_ops_release_vtbl2(uint64_t obj)
{
    (*(void(**)(void))(*(uint64_t*)(*(uint64_t*)(obj + 0x10) + 0x10) + 0x30))();
}

/* FUN_00050ae0 @ 0x00050ae0   (est. txm_ops_base_ptr2)
 * Ghidra: undefined8 FUN_00050ae0(long)
 * Returns *(*(obj+0x10)+0x10) - the second ops-table base.
 * Confidence: high
 */
static uint64_t txm_ops_base_ptr2(uint64_t obj) { return *(uint64_t*)(*(uint64_t*)(obj + 0x10) + 0x10); }

/* FUN_00050af0 @ 0x00050af0   (est. txm_err_2d_b)
 * Ghidra: undefined8 FUN_00050af0(void)
 * Returns error code 0x2d.
 * Confidence: high
 */
static uint64_t txm_err_2d_b(void) { return 0x2d; }

/* FUN_00050afc..050b44 (9 fns)   (est. txm_err_4e_h..p)
 * Ghidra: undefined8 FUN_00050afc/508/514/520/52c/538/544(void)
 * Each returns error code 0x4e.
 * Confidence: high
 */
static uint64_t txm_err_4e_h(void) { return 0x4e; }
static uint64_t txm_err_4e_i(void) { return 0x4e; }
static uint64_t txm_err_4e_j(void) { return 0x4e; }
static uint64_t txm_err_4e_k(void) { return 0x4e; }
static uint64_t txm_err_4e_l(void) { return 0x4e; }
static uint64_t txm_err_4e_m(void) { return 0x4e; }
static uint64_t txm_err_4e_n(void) { return 0x4e; }

/* FUN_00050b50 @ 0x00050b50   (est. txm_manifest_set_property_v6)
 * Ghidra: undefined8 FUN_00050b50(long,undefined8,undefined8,undefined8)
 * Same property set, resolving via *(*(obj+0x10)+0x18) and FUN_00057264.
 * Returns 0, or 2 on unknown.
 * Confidence: medium
 */
static uint64_t txm_manifest_set_property_v6(uint64_t obj, uint64_t a, uint64_t key, uint64_t val)
{
    uint64_t base = *(uint64_t*)(*(uint64_t*)(obj + 0x10) + 0x18);
    uint64_t slot = txm_obj_prop_lookup(base, key);
    if (slot == 0) return 2;
    txm_obj_prop_set(base, key, val);
    return 0;
}

/* ================================================================== */
/* 0x50bb0 .. 0x5130c — magazine/cryptex + DT property read           */
/* ================================================================== */

/* FUN_00050bb0/4c10/4c70/4cd0   (est. txm_manifest_set_property_v7..v10)
 * Ghidra: undefined8 FUN_00050bb0/4c10/4c70/4cd0(long,...)
 * Property set variants resolving via *(*(obj+0x10)+0x18) and storing
 * through FUN_00057318/573c8/57478/5753c. Return 0 or 2 (unknown).
 * Confidence: medium
 */
static uint64_t txm_manifest_set_property_v7(uint64_t obj, uint64_t a, uint64_t key, uint64_t v)
{
    uint64_t base = *(uint64_t*)(*(uint64_t*)(obj + 0x10) + 0x18);
    if (txm_obj_prop_lookup(base, key) == 0) return 2;
    txm_obj_prop_set_v2(base, key, v);
    return 0;
}
static uint64_t txm_manifest_set_property_v8(uint64_t obj, uint64_t a, uint64_t key, uint64_t v)
{
    uint64_t base = *(uint64_t*)(*(uint64_t*)(obj + 0x10) + 0x18);
    if (txm_obj_prop_lookup(base, key) == 0) return 2;
    txm_obj_prop_set_v3(base, key, v);
    return 0;
}
static uint64_t txm_manifest_set_property_v9(uint64_t obj, uint64_t a, uint64_t key, uint64_t v)
{
    uint64_t base = *(uint64_t*)(*(uint64_t*)(obj + 0x10) + 0x18);
    if (txm_obj_prop_lookup(base, key) == 0) return 2;
    txm_obj_prop_set_v4(base, key, v);
    return 0;
}
static uint64_t txm_manifest_set_property_v10(uint64_t obj, uint64_t a, uint64_t key, uint64_t v)
{
    uint64_t base = *(uint64_t*)(*(uint64_t*)(obj + 0x10) + 0x18);
    if (txm_obj_prop_lookup(base, key) == 0) return 2;
    txm_obj_prop_set_v5(base, key, v);
    return 0;
}

/* FUN_00050d30 / 4d3c   (est. txm_return_zero_d/e)
 * Ghidra: undefined8 FUN_00050d30/4d3c(void)
 * Return 0.
 * Confidence: high
 */
static uint64_t txm_return_zero_d(void) { return 0; }
static uint64_t txm_return_zero_e(void) { return 0; }

/* FUN_00050d48 / 4d50   (est. txm_noop9/10)
 * Ghidra: void FUN_00050d48/4d50(void)
 * Empty stubs.
 * Confidence: high
 */
static void txm_noop9(void) { return; }
static void txm_noop10(void) { return; }

/* FUN_00050d58 / 4d5c   (est. txm_panic_should_never_b/c)
 * Ghidra: void FUN_00050d58/4d5c(void)
 * noreturn panic "panic: should never be called" (0x36bd) via
 * FUN_00050d70.
 * Confidence: high
 */
static void txm_panic_should_never_b(void) { txm_panic_msg(0x36bd); }
static void txm_panic_should_never_c(void) { txm_panic_msg(0x36bd); }

/* FUN_00050d70 @ 0x00050d70   (est. txm_panic_msg)
 * Ghidra: void FUN_00050d70(undefined8)
 * noreturn panic taking a message pointer (FUN_00029784).
 * Confidence: high
 */
static void txm_panic_msg(uint64_t msg) { txm_panic((const char*)msg); }

/* FUN_00050d9c / 4da0   (est. txm_trap_ctx_enter_o/p)
 * Ghidra: void FUN_00050d9c/4da0(void)
 * PAC-checked trap-context enter.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_o(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }
static void txm_trap_ctx_enter_p(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }

/* FUN_00050dc4 @ 0x00050dc4   (est. txm_trap_ctx_enter_q)
 * Ghidra: void FUN_00050dc4(void)
 * Trap-context enter passing saved context.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_q(void)
{
    uint64_t ctx = txm_ctx_save();
    txm_ctx_finish(&ctx);
}

/* FUN_00050df0 @ 0x00050df0   (est. txm_dt_property_read)
 * Ghidra: undefined8 FUN_00050df0(void)
 * Reads a DeviceTree property into the caller-provided buffer: resolves
 * the property node (FUN_0004eb24), copies the value (thunk_FUN_0002d240
 * + memset), and zeroes the size out-param. Returns 0 on success, 2 if
 * the property is absent.
 * Confidence: medium
 * Notes: property name looked up by FUN_0004eb24 (path resolve).
 */
static uint64_t txm_dt_property_read(uint64_t *out_size)
{
    uint64_t sz = *out_size;
    if (txm_dt_property_find_wrap((uint64_t*)0, 0, 0, 0, 0) == 1) {
        if (*out_size < sz) txm_fault_impl(0x19, 0);
        txm_memzero(out_size, sz);
        *out_size = 0;
        return 0;
    }
    return 2;
}

/* FUN_00050ebc @ 0x00050ebc   (est. txm_dt_property_read_u8)
 * Ghidra: void FUN_00050ebc(void)
 * Reads a DT property as a byte into the caller's output; panics
 * "failed to read property" if the read fails with a real error.
 * Confidence: medium
 */
static void txm_dt_property_read_u8(uint8_t *out)
{
    int r = (int)txm_dt_property_read((uint64_t*)0);
    if ((r != 2) && (r != 0)) txm_panic_msg(0x3781);
    *out = 0;
}

/* FUN_00050f30 @ 0x00050f30   (est. txm_dt_property_read_u32)
 * Ghidra: void FUN_00050f30(void)
 * Reads a DT property as a uint32 into the caller's output; same panic
 * behavior.
 * Confidence: medium
 */
static void txm_dt_property_read_u32(uint32_t *out)
{
    int r = (int)txm_dt_property_read((uint64_t*)0);
    if ((r != 2) && (r != 0)) txm_panic_msg(0x3781);
    *out = 0;
}

/* FUN_00050f9c @ 0x00050f9c   (est. txm_dt_chosen_get)
 * Ghidra: undefined8 FUN_00050f9c(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Resolves a path under /chosen (FUN_0004e8b4) and reads the property
 * (FUN_00050df0). Returns 0 on success, 0x13 if the path does not exist.
 * Confidence: medium
 */
static uint64_t txm_dt_chosen_get(uint64_t iodev, uint64_t path, uint64_t prop,
                                  uint64_t *out, uint64_t *size)
{
    uint64_t node = 0;
    if (txm_dt_path_resolve((uint64_t*)iodev, 0, (char*)path, &node) == 1) {
        return txm_dt_property_read(size);
    }
    return 0x13;
    (void)prop; (void)out;
}

/* FUN_00051014 @ 0x00051014   (est. txm_digest_hex_report)
 * Ghidra: void FUN_00051014(long,undefined8,undefined8,undefined8)
 * Formats a binary digest into a 0x80-byte hex string (zeroed first via
 * FUN_00051c10), then reports it via FUN_00058fd0. The hex string is
 * produced from the object's digest (param_1+0x10).
 * Confidence: medium
 */
static void txm_digest_hex_report(uint64_t obj, uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t canary = txm_canary;
    char hexbuf[0x81];
    for (int i = 0; i < 0x81; i++) hexbuf[i] = 0;
    txm_img4_hash_to_hex(hexbuf, 0x80);
    uint64_t i = 0;
    while (hexbuf[i] != '\0') { i = i + 1; if (i == 0x80) txm_fault_impl(0x19, 0); }
    FUN_00058fd0(*(uint64_t*)(obj + 0x10), hexbuf, b, c);
    (void)a;
    if (txm_canary != canary) txm_stack_check_fail();
}

/* FUN_000510fc @ 0x000510fc   (est. txm_digest_hex_report_v2)
 * Ghidra: void FUN_000510fc(long,undefined8,undefined8,undefined8)
 * Same hex digest report via FUN_00058fe0.
 * Confidence: medium
 */
static void txm_digest_hex_report_v2(uint64_t obj, uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t canary = txm_canary;
    char hexbuf[0x81];
    for (int i = 0; i < 0x81; i++) hexbuf[i] = 0;
    txm_img4_hash_to_hex(hexbuf, 0x80);
    uint64_t i = 0;
    while (hexbuf[i] != '\0') { i = i + 1; if (i == 0x80) txm_fault_impl(0x19, 0); }
    FUN_00058fe0(*(uint64_t*)(obj + 0x10), hexbuf, b, c);
    (void)a;
    if (txm_canary != canary) txm_stack_check_fail();
}

/* FUN_000511f8 @ 0x000511f8   (est. txm_cryptex_ctx_init)
 * Ghidra: undefined8* FUN_000511f8(undefined8*,undefined8,undefined8*,long)
 * Initializes a cryptex/magazine context block: writes the magic
 * 0x656e697a7a696e65 ("enzin..." = cryptex tag), binds the ops table,
 * input list, and item count, then iterates the input list calling
 * FUN_00051c90 per item.
 * Confidence: medium
 * Notes: magic 0x656e697a7a696e65 = "e n i z z i n e"; table DAT_00019710.
 */
static uint64_t *txm_cryptex_ctx_init(uint64_t *ctx, uint64_t ops, uint64_t *items, uint64_t count)
{
    ctx[0] = 0x656e697a7a696e65ull;
    *(uint8_t*)(ctx + 1) = 0;
    *(uint16_t*)((char*)ctx + 9) = 0;
    *(uint8_t*)((char*)ctx + 0xb) = 0;
    ctx[0xf] = 0x19710;
    ctx[2] = ops;
    ctx[3] = (uint64_t)items;
    ctx[5] = count;
    ctx[0x11] = 0xffffffffffffffffull;
    *(uint16_t*)(ctx + 0xe) = 0;
    ctx[0xb] = 0;
    ctx[10] = 0;
    ctx[0xd] = 0;
    ctx[0xc] = 0;
    ctx[7] = 0;
    ctx[6] = 0;
    ctx[9] = 0;
    ctx[8] = 0;
    for (; count != 0; count = count - 1) {
        FUN_00051c90(*items);
        items = items + 1;
    }
    return ctx;
}

/* FUN_00051290 @ 0x00051290   (est. txm_magazine_name_store)
 * Ghidra: void FUN_00051290(long,undefined8)
 * Stores a magazine name string (via FUN_0002efc4) into the object's
 * name buffer (param_1+0x30), max 0x40 bytes; faults 0x19 on overflow
 * or if the buffer is already in use.
 * Confidence: medium
 */
static void txm_magazine_name_store(uint64_t obj, uint64_t name)
{
    uint64_t len = txm_str_len(name);
    if (len < 0x40) {
        if ((uint16_t*)(obj + 0x30) <= (uint16_t*)(obj + 0x70)) {
            txm_img4_no_digest((char*)(obj+0x30), name, 0x40, 0xffffffffffffffffull);
            *(uint16_t*)(obj + 0x70) = 1;
            return;
        }
    } else {
        FUN_00051c50(name);
    }
    txm_fault_impl(0x19, 0);
}

/* FUN_000512fc @ 0x000512fc   (est. txm_obj_set_data)
 * Ghidra: void FUN_000512fc(long,long)
 * Sets the object's data pointer (param_1+0x78) if param_2 nonzero.
 * Confidence: high
 */
static void txm_obj_set_data(uint64_t obj, uint64_t data)
{
    if (data != 0) *(uint64_t*)(obj + 0x78) = data;
}

/* FUN_0005130c @ 0x0005130c   (est. txm_magazine_parse)
 * Ghidra: ulong FUN_0005130c(long,undefined8*)
 * Parses a magazine (cryptex) header from the object: queries the
 * "board-id" (FUN_00058b88) and "chip-id" (FUN_0005861c) expert
 * properties, reads the magazine data via the ops-table callback
 * (*(*(obj+0x78)+0x10)), validates the magazine magic/format
 * (0x42-byte header), extracts the digest and stamp fields into
 * *param_2. Returns 0 on success.
 * Confidence: low (large format parser; field layout inferred)
 * Notes: "magazine: %s: ..." error strings at 0x388a/0x3905/0x393a/
 *   0x3993/0x39e7/0x3a44; stamp validation via FUN_00057ce8/57b58/
 *   57ca8; error codes 0x22/0x54/0x57/0x60.
 */
static uint64_t txm_magazine_parse(uint64_t obj, uint64_t *out)
{
    uint64_t canary = txm_canary;
    uint64_t ops = *(uint64_t*)(obj + 0x10);
    uint64_t board[2] = {0,0}, chip[2] = {0,0}, digest[2] = {0,0};
    uint8_t present = 0;
    uint64_t r = FUN_00058b88(ops, 0, 0x1a858, (uint8_t*)&board[0]);
    if ((r & 0xfffffffd) == 0) {
        if (FUN_0005861c(ops, 0, 0x1c110, &present) != 0)
            txm_panic_msg(0x38bf);
        *(uint64_t*)(obj + 0xb8) = board[1]; *(uint64_t*)(obj + 0xb0) = board[0];
        *(uint64_t*)(obj + 200) = chip[1];   *(uint64_t*)(obj + 0xc0) = chip[0];
        *(uint64_t*)(obj + 0xe0) = 1;
        *(uint8_t*)(obj + 0xf0) = present & 1;
        uint64_t sz = 0x42;
        r = (*(uint64_t(**)(uint64_t,uint64_t,uint64_t*,uint64_t*))(*(uint64_t*)(obj + 0x78) + 0x10))(obj, 0, &digest[0], &sz);
        if ((int)r == 0) {
            if (sz == 0) {
                FUN_00051ccc(NULL);
                txm_log_error(ops, 0, "magazine: %s: magazine data too short", 0x3942);
                r = 0x60;
            } else {
                uint8_t b = (uint8_t)digest[0];
                if ((uint8_t)digest[0] < 2) {
                    if (sz == 0x42) {
                        uint8_t dlen = *(uint8_t*)&digest[1];
                        if ((uint64_t)dlen < 0x41) {
                            if (*(uint64_t*)(obj + 0xd8) == (uint64_t)dlen) {
                                /* copy digest inline */
                            } else {
                                uint64_t dl = 0x40;
                                txm_img4_hash_copy2(obj + 0x90, (uint64_t)&digest[1], &dl);
                                dlen = (uint8_t)dl;
                            }
                            if (0x40 < dlen) txm_fault_impl(0x19, 0);
                            txm_img4_install_hash((uint64_t)&board[0], (uint64_t)&digest[1], dlen);
                            txm_img4_hash_finalize((uint64_t)&board[0], (uint64_t)&chip[0]);
                            r = 0;
                            *(uint8_t*)(obj + 0x80) = b;
                            out[5] = digest[1]; out[4] = digest[0];
                            out[7] = 0; out[6] = 0;
                            *(uint16_t*)(out + 8) = 0;
                            out[1] = 0; out[0] = 0;
                            out[3] = 0; out[2] = 0;
                        } else {
                            FUN_00051ccc(NULL);
                            txm_log_error(ops, 0, "magazine: %s: magazine data has invalid digest", 0x3a44);
                            r = 0x54;
                        }
                    } else {
                        FUN_00051ccc(NULL);
                        txm_log_error(ops, 0, "magazine: %s: magazine data has invalid magic", 0x39e7);
                        r = 0x22;
                    }
                } else {
                    if (0x41 < sz) { r = 0x57; goto done; }
                    FUN_00051ccc(NULL);
                    txm_log_error(ops, 0, "magazine: %s: future magazine is unsupported", 0x3993);
                    r = 0x22;
                }
            }
        } else {
            if (((int)r == 0x54) || ((int)r == 2)) {
                r = 0;
                for (int i = 0; i < 9; i++) out[i] = 0;
                goto done;
            }
            FUN_00051ccc(NULL);
            txm_log_error(ops, 0, "magazine: %s: failed to query stamp", 0x3905);
        }
    } else {
        FUN_00051ccc(NULL);
        txm_log_error(ops, 0, "magazine: %s: failed to query board-id", 0x388a);
    }
done:
    if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* ================================================================== */
/* 0x516c0 .. 0x523c8 — magazine/stamp/nonce + hash-range primitives  */
/* ================================================================== */

/* FUN_000516c0 @ 0x000516c0   (est. txm_magazine_stamp_parse)
 * Ghidra: void FUN_000516c0(long,long)
 * Parses a magazine stamp (param_2) into the object's stamp fields.
 * If the object has no stamp slot yet (*(param_1+0xe0)==0) faults
 * "optional not set". Validates the stamp digest (< 0x41 bytes),
 * compares it against the magazine header, and copies the stamp fields
 * into param_1+0x90..; sets the "valid" short (param_1+0xe0) to 1 and
 * records the digest source (param_1+0xe8). Faults 0x19 on bad length.
 * Confidence: medium
 */
static void txm_magazine_stamp_parse(uint64_t obj, uint64_t stamp)
{
    uint64_t canary = txm_canary;
    if (*(uint16_t*)(obj + 0xe0) == 0) {
        FUN_00051c78();
    } else if (*(uint8_t*)(stamp + 0x41) < 0x41) {
        uint64_t *slot = (uint64_t*)(obj + 0x90);
        uint64_t tmp[0xa] = {0};   /* 0x50-byte magazine header copy */
        uint64_t *src;
        txm_img4_install_hash((uint64_t)&tmp[0], (uint64_t)(stamp + 1), 0x40);
        int r = FUN_00057c58(slot, &tmp[0]);
        if (r == 0) {
            *(uint64_t*)(obj + 0xe8) = 0;
            src = slot;
        } else {
            txm_img4_hash_finalize((uint64_t)&tmp[0], 0);
            txm_img4_hash_finalize((uint64_t)slot, 0);
            int has_sha1 = (*(uint8_t*)(obj + 0xf0) & 1) == 0;
            *(uint64_t*)(obj + 0xe8) = has_sha1 ? 2 : 1;
            src = &tmp[0];
            if (!has_sha1) src = slot;
        }
        uint64_t v0 = src[0];
        *(uint64_t*)(obj + 0x98) = src[1];
        slot[0] = v0;
        uint64_t v6 = src[3], v5 = src[2], v8 = src[5], v7 = src[4];
        uint64_t v9 = src[6], v11 = src[9], v10 = src[8];
        *(uint64_t*)(obj + 200) = src[7];
        *(uint64_t*)(obj + 0xc0) = v9;
        *(uint64_t*)(obj + 0xd8) = v11;
        *(uint64_t*)(obj + 0xd0) = v10;
        *(uint64_t*)(obj + 0xa8) = v6;
        *(uint64_t*)(obj + 0xa0) = v5;
        *(uint64_t*)(obj + 0xb8) = v8;
        *(uint64_t*)(obj + 0xb0) = v7;
        *(uint16_t*)(obj + 0xe0) = 1;
        if (txm_canary != canary) txm_stack_check_fail();
        return;
    }
    txm_fault_impl(0x19, 0);
}

/* FUN_000517f8 @ 0x000517f8   (est. txm_magazine_load_nonces)
 * Ghidra: void FUN_000517f8(long)
 * Loads the magazine nonce slots: for each nonce entry (count at
 * param_1+0x28), reads its value via the ops-table callback, validates
 * and derives the nonce digest (FUN_00051dd8), sets up the slot
 * (FUN_00052020), and records the anti-replay root. On a nonce read
 * failure logs and clears the slot.
 * Confidence: medium
 * Notes: "magazine: %s: ..." strings at 0x3a9f/0x3ad0; 0x80-byte digest
 *   buffer; FUN_00051ff8 clears a failed slot.
 */
static void txm_magazine_load_nonces(uint64_t obj)
{
    uint64_t canary = txm_canary;
    if (*(uint64_t*)(obj + 0x28) != 0) {
        uint64_t count = 0;
        uint64_t ops = *(uint64_t*)(obj + 0x10);
        do {
            uint64_t *slot = *(uint64_t**)(*(uint64_t*)(obj + 0x18) + count * 8);
            uint64_t digest[0x11] = {0};
            digest[0] = 0x80;
            uint64_t nonce[2] = {0,0};
            int r = (*(uint64_t(**)(uint64_t,uint64_t,uint64_t*,uint64_t*))(*(uint64_t*)(obj+0x78)+0x10))
                        (obj, *slot + 0xc, &digest[1], &digest[0]);
            if (r == 0) {
                if (0x80 < digest[0]) txm_fault_impl(0x19, 0);
                txm_img4_hash_copy((uint64_t)&nonce[0], (uint64_t)&digest[1]);
                r = txm_nonce_derive((uint64_t)slot, ops, &nonce[0]);
                if (r != 0) {
                    uint64_t c = *(uint64_t*)(obj + 0x10);
                    FUN_00051ccc(NULL);
                    txm_log_error(c, 0, "magazine: %s: invalid nonce slot (%s)", 0x3ad0);
                    goto fail;
                }
                uint64_t *root = NULL;
                if ((*(uint8_t*)(slot[4] + 1) & 4) != 0) root = slot;
                if (slot + 5 <= slot) txm_fault_impl(0x19, 0);
                FUN_00052020(slot, ops, *(uint64_t*)(obj + 0xe8));
                if (*(uint64_t*)(obj + 0x20) == 0) {
                    if (slot + 5 <= root) txm_fault_impl(0x19, 0);
                    *(uint64_t**)(obj + 0x20) = root;
                }
            } else {
                uint64_t c = *(uint64_t*)(obj + 0x10);
                FUN_00051ccc(NULL);
                txm_log_error(c, 0, "magazine: %s: failed to read nonce (%s)", 0x3a9f);
fail:
                FUN_00051ff8(slot, ops);
            }
            count = count + 1;
        } while (count < *(uint64_t*)(obj + 0x28));
    }
    if (txm_canary != canary) txm_stack_check_fail();
}

/* FUN_000519c8 @ 0x000519c8   (est. txm_magazine_slot_find)
 * Ghidra: undefined8 FUN_000519c8(long,long,int,undefined8*)
 * Finds a magazine slot by nonce name (param_2) or its +0x58 alias and
 * a requested type (param_3); returns the slot into *param_4. Returns 0
 * on match, 2 on none.
 * Confidence: medium
 */
static uint64_t txm_magazine_slot_find(uint64_t obj, uint64_t key, int type, uint64_t *out)
{
    if (*(uint64_t*)(obj + 0x28) == 0) return 2;
    uint64_t i = 0;
    uint64_t slot = 0;
    while (1) {
        slot = *(uint64_t*)(*(uint64_t*)(obj + 0x18) + i * 8);
        FUN_00051ce0((uint64_t*)slot);
        uint64_t name = FUN_00051ccc((uint64_t*)slot);
        if (((key == name) || (key == *(uint64_t*)(name + 0x58))) &&
            (*(int*)(name + 0x30) == type)) break;
        i = i + 1;
        if (*(uint64_t*)(obj + 0x28) <= i) return 2;
    }
    *out = slot;
    return 0;
}

/* FUN_00051b3c @ 0x00051b3c   (est. txm_magazine_slot_find_type)
 * Ghidra: undefined8 FUN_00051b3c(long,int,undefined8*)
 * Finds a magazine slot whose type (+8) equals param_2; returns it into
 * *param_3. Returns 0 on match, 2 on none.
 * Confidence: medium
 */
static uint64_t txm_magazine_slot_find_type(uint64_t obj, int type, uint64_t *out)
{
    if (*(uint64_t*)(obj + 0x28) == 0) return 2;
    uint64_t i = 0;
    do {
        uint64_t slot = *(uint64_t*)(*(uint64_t*)(obj + 0x18) + i * 8);
        uint64_t name = FUN_00051ccc(NULL);
        if (*(int*)(name + 8) == type) { *out = slot; return 0; }
        i = i + 1;
    } while (i < *(uint64_t*)(obj + 0x28));
    return 2;
}

/* FUN_00051bd0 @ 0x00051bd0   (est. txm_magazine_slot_find_id)
 * Ghidra: undefined8 FUN_00051bd0(long,long,undefined8*)
 * Finds a magazine slot whose id (*(slot+0x40)) equals param_2; returns
 * it into *param_3. Returns 0 on match, 2 on none.
 * Confidence: medium
 */
static uint64_t txm_magazine_slot_find_id(uint64_t obj, uint64_t id, uint64_t *out)
{
    uint64_t n = *(uint64_t*)(obj + 0x28);
    if (n != 0) {
        uint64_t *e = *(uint64_t**)(obj + 0x18);
        do {
            if (*(uint64_t*)(*(uint64_t*)*e + 0x40) == id) { *out = *e; return 0; }
            n = n - 1;
            e = e + 1;
        } while (n != 0);
    }
    return 2;
}

/* FUN_00051c10 @ 0x00051c10   (est. txm_zero_buf)
 * Ghidra: void FUN_00051c10(undefined8,undefined8)
 * Zeroes a 0x80-byte buffer (FUN_0002eb44 with a "no digest" marker).
 * Confidence: medium
 */
static void txm_zero_buf(uint64_t buf, uint64_t len)
{
    txm_memzero((void*)buf, 0x80);
    (void)len;
}

/* FUN_00051c50 @ 0x00051c50   (est. txm_nonce_prefix_overflow_panic)
 * Ghidra: void FUN_00051c50(void)
 * noreturn panic "panic: nonce slot prefix overflow" (0x3849).
 * Confidence: high
 */
static void txm_nonce_prefix_overflow_panic(void) { txm_panic_msg(0x3849); }

/* FUN_00051c78 @ 0x00051c78   (est. txm_optional_not_set_panic)
 * Ghidra: void FUN_00051c78(void)
 * noreturn panic "panic: optional not set" (0x38ed).
 * Confidence: high
 */

/* FUN_00051c90 @ 0x00051c90   (est. txm_nonce_item_init)
 * Ghidra: void FUN_00051c90(long)
 * Initializes a nonce item: calls its init callback (*(param_1+8)) and
 * clears its 5-word state block at *(param_1+0x20).
 * Confidence: medium
 */
static void txm_nonce_item_init(uint64_t item)
{
    (*(void(**)(void))(item + 8))();
    uint64_t *st = *(uint64_t**)(item + 0x20);
    *(uint8_t*)((char*)st + 0x1d) = 0;
    st[1] = 0; st[0] = 0; st[3] = 0; st[2] = 0;
}

/* FUN_00051ccc @ 0x00051ccc   (est. txm_obj_name_or_default)
 * Ghidra: undefined8 FUN_00051ccc(undefined8*)
 * Returns *param_1 (the object name), or a default (FUN_00054024) if
 * param_1 is null.
 * Confidence: medium
 */

/* FUN_00051ce0 @ 0x00051ce0   (est. txm_obj_name)
 * Ghidra: void FUN_00051ce0(undefined8*)
 * Returns the object name via FUN_00054034(*param_1).
 * Confidence: medium
 */

/* FUN_00051cec @ 0x00051cec   (est. txm_obj_run_vtbl_10)
 * Ghidra: long FUN_00051cec(long)
 * Runs the object's vtable slot +0x10 and returns the object.
 * Confidence: medium
 */
static uint64_t txm_obj_run_vtbl_10(uint64_t obj)
{
    (*(void(**)(void))(obj + 0x10))();
    return obj;
}

/* FUN_00051d1c @ 0x00051d1c   (est. txm_obj_destroy)
 * Ghidra: void FUN_00051d1c(long*)
 * Destroys the object: if *param_1 nonzero, runs its destructor vtable
 * slot (+0x18) and clears the slot.
 * Confidence: medium
 */
static void txm_obj_destroy(uint64_t *slot)
{
    if (*slot != 0) {
        (*(void(**)(void))(*slot + 0x18))();
        *slot = 0;
    }
}

/* FUN_00051d54 @ 0x00051d54   (est. txm_obj_derive_nonce)
 * Ghidra: undefined8 FUN_00051d54(long*,undefined8)
 * Derives a nonce digest from the object: resolves the object
 * (FUN_00054074), bounds-checks the 0x10-byte digest, and copies the
 * derived nonce into param_2 via FUN_0005a6e4. Returns the derive status.
 * Confidence: medium
 */
static uint64_t txm_obj_derive_nonce(uint64_t *slot, uint64_t out)
{
    uint64_t obj = *slot;
    uint64_t r = FUN_00054074(obj, slot);
    if ((int)r == 0) {
        if (0x10 < *(uint64_t*)(obj + 0x48)) txm_fault_impl(0x19, 0);
        FUN_0005a6e4(out, slot[4] + 5);
    }
    return r;
}

/* FUN_00051dc0 @ 0x00051dc0   (est. txm_nonce_set_replay_bit)
 * Ghidra: void FUN_00051dc0(long)
 * Sets bit 1 in the nonce state flags (*(*(param_1+0x20)+1) |= 2).
 * Confidence: medium
 */
static void txm_nonce_set_replay_bit(uint64_t obj)
{
    *(uint32_t*)(*(uint64_t*)(obj + 0x20) + 1) |= 2;
}

/* FUN_00051dd8 @ 0x00051dd8   (est. txm_nonce_derive)
 * Ghidra: undefined8 FUN_00051dd8(long,undefined8,undefined8*)
 * Derives a nonce from a slot's data (param_3 {ptr,len}): requires
 * non-empty data, a 0x25-byte stamped format, and copies the 0x20-byte
 * nonce + 0x10-byte counter into the slot state. Returns 0, 0x22 (bad
 * format), 0x57 (future), or 0x60 (too small). Logs "slot: %s: ..."
 * errors at 0x3b2d/0x3b7b/0x3bc7.
 * Confidence: medium
 */
static uint64_t txm_nonce_derive(uint64_t slot, uint64_t ctx, uint64_t *data)
{
    uint64_t len = data[1];
    if (len == 0) {
        txm_log_error(ctx, 0, "slot: %s: slot data too small for nonce (%s)", 0x3b2d);
        return 0x60;
    }
    char *p = (char*)*data;
    if (*p == '\0') {
        if (len == 0x25) {
            uint8_t *st = *(uint8_t**)(slot + 0x20);
            *st = 0;
            *(uint32_t*)(st + 1) = (uint8_t)p[4] & 0x7f;
            uint64_t n0 = *(uint64_t*)(p + 5);
            *(uint64_t*)(st + 0xd) = *(uint64_t*)(p + 0xd);
            *(uint64_t*)(st + 5) = n0;
            uint64_t n1 = *(uint64_t*)(p + 0x15);
            *(uint64_t*)(st + 0x1d) = *(uint64_t*)(p + 0x1d);
            *(uint64_t*)(st + 0x15) = n1;
            return 0;
        }
        txm_log_error(ctx, 0, "slot: %s: slot data has incorrect format (%s)", 0x3bc7);
    } else {
        if (0x24 < len) return 0x57;
        txm_log_error(ctx, 0, "slot: %s: future slot is bogus (%s)", 0x3b7b);
    }
    return 0x22;
}

/* FUN_00051ecc @ 0x00051ecc   (est. txm_nonce_derive_digest)
 * Ghidra: undefined8 FUN_00051ecc(long*,undefined8,undefined8*,undefined8)
 * Derives the nonce digest for an object: optionally creates a fresh
 * nonce (vtable callbacks param_1[2]/[3]) then runs the nonce-digest
 * derivation (FUN_0005bef0). Logs "failed to derive nonce digest (nonce)"
 * (0x3c1c) on failure. Returns 0 on success.
 * Confidence: medium
 */
static uint64_t txm_nonce_derive_digest(uint64_t *slot, uint64_t ctx, uint64_t *data, uint64_t a4)
{
    uint64_t canary = txm_canary;
    uint64_t obj = *slot;
    uint64_t r;
    uint64_t local[3] = {0,0,0};
    r = FUN_00054034(obj);
    if (data == NULL) {
        (*(void(**)(uint64_t*))slot[2])(slot);
        data = &local[0];
        r = txm_obj_derive_nonce(slot, (uint64_t)&local[0]);
        (*(void(**)(uint64_t*))slot[3])(slot);
        if ((int)r != 0) goto out;
    }
    r = FUN_0005bef0(ctx, r, *(uint32_t*)(obj + 0x30), data, a4);
    if ((int)r != 0) txm_log_error(ctx, 0, "failed to derive nonce digest (nonce)", 0x3c1c);
out:
    if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_00051ff8 @ 0x00051ff8   (est. txm_nonce_slot_fail)
 * Ghidra: void FUN_00051ff8(long*,undefined8)
 * Marks a nonce slot failed: sets the failed bit (|1) in the slot state
 * flags and clears the slot via FUN_00052020.
 * Confidence: medium
 */

/* FUN_00052020 @ 0x00052020   (est. txm_nonce_slot_clear)
 * Ghidra: void FUN_00052020(long*,undefined8,ulong)
 * Clears a nonce slot's counter/replay state after use: selects the
 * SHA-1 vs SHA-256 field layout, copies the counter, clears the replay
 * flags, and applies the mode bits. Faults 0x19 on layout overflow.
 * Confidence: medium
 */
static void txm_nonce_slot_clear(uint64_t *slot, uint64_t ctx, uint64_t mode)
{
    uint64_t *st = (uint64_t*)slot[4];
    uint32_t flags = *(uint32_t*)((char*)st + 1);
    uint64_t max = *(uint64_t*)(*slot + 0x50);
    uint64_t m = (max > 1) ? 2 : max;
    int sha1 = (flags & 4) != 0;
    uint32_t ctr_sz = sha1 ? 8 : 0x40;
    uint32_t ctr_off = sha1 ? 0x27 : 0x23;
    uint64_t *ctr = sha1 ? (uint64_t*)((char*)st + 0x25) : NULL;
    uint64_t *counter = sha1 ? (uint64_t*)((char*)st + 0x15) : NULL;
    uint64_t mm = mode;
    if (mode < 4) mm = 3;
    if ((flags & 3) != 0) mode = mm;
    uint32_t newf = flags;
    if (m <= mode) {
        if (counter == NULL) {
            if ((uint64_t*)((char*)st + 0x25) <= st) txm_fault_impl(0x19, 0);
            FUN_00059010(ctx, (uint64_t)((char*)st + 5), *(uint64_t*)(*slot + 0x48));
            ctr_sz = ctr_sz | 0x40;
        } else {
            if (ctr <= counter) txm_fault_impl(0x19, 0);
            uint64_t c0 = *counter;
            *(uint64_t*)((char*)st + 0xd) = counter[1];
            *(uint64_t*)((char*)st + 5) = c0;
            *(uint64_t*)((char*)st + 0x1d) = 0;
            *(uint64_t*)((char*)st + 0x15) = 0;
        }
        newf = *(uint32_t*)((char*)st + 1) & (ctr_sz ^ 0xffffffffu);
    }
    *(uint32_t*)((char*)st + 1) = newf & ((ctr_off | (mode & 2) << 2) ^ 0xffffffffu);
}

/* FUN_00052114 @ 0x00052114   (est. txm_magazine_anti_replay_disabled)
 * Ghidra: bool FUN_00052114(undefined8,long)
 * Returns whether anti-replay is disabled for the object: true if the
 * hash type is unresolvable (FUN_00052a34) or the stamp slot is empty,
 * or if the digest-source short (param_2+0xe8) is zero.
 * Confidence: medium
 */
static int txm_magazine_anti_replay_disabled(uint64_t a, uint64_t obj)
{
    uint64_t hash = txm_manifest_hash_resolve(a, *(uint64_t*)(obj + 0x10));
    if ((hash == 0) || (*(uint16_t*)(obj + 0x90) == 0)) return 1;
    return *(uint16_t*)(obj + 0xe8) == 0;
}

/* FUN_0005215c @ 0x0005215c   (est. txm_odometer_anti_replay)
 * Ghidra: uint FUN_0005215c(long,undefined8*)
 * Performs the odometer anti-replay check: resolves the hash type and
 * verifies the nonce (FUN_0005b7f0). On violation returns the error code
 * from param_1+0x18 and logs "odometer: %s: %s anti-replay violation"
 * (0x3cb6).
 * Confidence: medium
 */
static uint32_t txm_odometer_anti_replay(uint64_t obj, uint64_t *params)
{
    uint64_t name = *params;
    uint64_t hash = txm_manifest_hash_resolve(obj, params[2]);
    uint64_t *p1 = NULL, *p2 = NULL;
    if (*(uint16_t*)(params + 0x1d) != 0) p1 = params + 0x13;
    if (*(uint16_t*)(params + 0x12) != 0) p2 = params + 8;
    int r = FUN_0005b7f0(hash, name, p2, p1);
    if (r == 0) return 0;
    uint32_t e = *(uint32_t*)(obj + 0x18);
    uint64_t nm = *params;
    txm_bc_ctx_release(params[2]);
    txm_log_error(nm, 0, "odometer: %s: %s anti-replay violation (%s)", 0x3cb6);
    if (0x6b < e) txm_fault_impl(0, 0);
    return e;
}

/* FUN_00052210 @ 0x00052210   (est. txm_hash_type_set)
 * Ghidra: undefined8 FUN_00052210(undefined8,undefined8,undefined4*)
 * Sets the hash type output to 0xf1 and returns 0.
 * Confidence: medium
 */
static uint64_t txm_hash_type_set(uint64_t a, uint64_t b, uint32_t *out)
{
    *out = 0xf1;
    return 0;
}

/* FUN_00052224 @ 0x00052224   (est. txm_noop11)
 * Ghidra: void FUN_00052224(void)
 * Empty stub.
 * Confidence: high
 */
static void txm_noop11(void) { return; }

/* FUN_0005222c / 4f30   (est. txm_trap_ctx_enter_r/s)
 * Ghidra: void FUN_0005222c/4f30(void)
 * PAC-checked trap-context enter.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_r(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }
static void txm_trap_ctx_enter_s(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }

/* FUN_00052254 @ 0x00052254   (est. txm_trap_ctx_enter_t)
 * Ghidra: void FUN_00052254(void)
 * Trap-context enter passing saved context.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_t(void)
{
    uint64_t ctx = txm_ctx_save();
    txm_ctx_finish(&ctx);
}

/* FUN_00052280 @ 0x00052280   (est. txm_return_zero_f)
 * Ghidra: undefined8 FUN_00052280(void)
 * Returns 0.
 * Confidence: high
 */
static uint64_t txm_return_zero_f(void) { return 0; }

/* FUN_0005228c..522ac (5 fns)   (est. txm_noop12..16)
 * Ghidra: void FUN_0005228c/4f94/4f9c/4fa4/4fac(void)
 * Empty stubs.
 * Confidence: high
 */
static void txm_noop12(void) { return; }
static void txm_noop13(void) { return; }
static void txm_noop14(void) { return; }
static void txm_noop15(void) { return; }
static void txm_noop16(void) { return; }

/* FUN_000522b4 @ 0x000522b4   (est. txm_hash_range_move)
 * Ghidra: void FUN_000522b4(undefined8*,undefined8*,undefined8,long,undefined8)
 * Moves a hash range: takes the source base from *param_2, zeroes it,
 * fills param_1 with {base, len, buffer+8}, and stores the buffer's
 * embedded length (*(param_4+8)) back into *param_2.
 * Confidence: medium
 */
static void txm_hash_range_move(uint64_t *dst, uint64_t *src, uint64_t len, uint64_t buf, uint64_t a)
{
    uint64_t v = *src;
    *src = 0;
    dst[0] = v;
    dst[1] = len;
    dst[2] = buf;
    dst[4] = a;
    *src = *(uint64_t*)(buf + 8);
}

/* FUN_000522d8 @ 0x000522d8   (est. txm_hash_range_init)
 * Ghidra: void FUN_000522d8(undefined8*,undefined8,undefined8)
 * Initializes a hash range: {ptr=param_2, len=param_3, ops=&DAT_00019cc0,
 * flags=0}.
 * Confidence: high
 */
static uint64_t txm_hash_range_init(uint64_t *rng, uint64_t ptr, uint64_t len)
{
    rng[0] = ptr;
    rng[1] = len;
    rng[2] = 0x19cc0;
    rng[4] = 0;
    return ptr;
}

/* FUN_000522f4 @ 0x000522f4   (est. txm_hash_range_copy)
 * Ghidra: void FUN_000522f4(undefined8*,undefined8*)
 * Copies a hash range {ptr,len} with ops=&DAT_00019c98, flags=0.
 * Confidence: high
 */
static void txm_hash_range_copy(uint64_t *dst, uint64_t *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = 0x19c98;
    dst[4] = 0;
}

/* FUN_00052318 @ 0x00052318   (est. txm_hash_range_take)
 * Ghidra: void FUN_00052318(undefined8*,undefined8*)
 * Takes ownership of a hash range from *param_2: moves its fields into
 * param_1, re-reads the buffer's embedded length, clears the source
 * buffer ops, and zeroes the source. Faults 0x19 on invalid range.
 * Confidence: medium
 */
static void txm_hash_range_take(uint64_t *dst, uint64_t *src)
{
    uint64_t *r = (uint64_t*)*src;
    if (r < r + 1) {
        uint64_t v1 = r[1], l2 = r[2], v4 = r[4], v0 = r[0];
        *r = 0;
        dst[0] = v0;
        dst[1] = v1;
        dst[2] = l2;
        dst[4] = v4;
        *r = *(uint64_t*)(l2 + 8);
        r[2] = 0;
        *src = 0;
        return;
    }
    txm_fault_impl(0x19, 0);
}

/* FUN_00052370 @ 0x00052370   (est. txm_hash_range_relocate)
 * Ghidra: void FUN_00052370(undefined8*,undefined8*)
 * Relocates a hash range, swapping ops tables (0x19ce8 vs 0x19d10).
 * Confidence: medium
 */
static void txm_hash_range_relocate(uint64_t *dst, uint64_t *src)
{
    dst[0] = src[0];
    dst[2] = 0x19ce8;
    uint64_t v = src[2];
    dst[1] = src[1];
    src[2] = 0x19d10;
    src[3] = v;
}

/* FUN_000523a0 @ 0x000523a0   (est. txm_hash_range_reset)
 * Ghidra: void FUN_000523a0(long,undefined8*)
 * Resets a hash range: moves the buffer (param_1+0x18) into the object
 * (+0x10), zeroes the buffer state, clears the source range.
 * Confidence: medium
 */
static void txm_hash_range_reset(uint64_t obj, uint64_t *src)
{
    uint64_t *r = (uint64_t*)*src;
    *(uint64_t*)(obj + 0x10) = *(uint64_t*)(obj + 0x18);
    *(uint64_t*)(obj + 0x18) = 0;
    *r = 0;
    r[1] = 0;
    r[2] = 0x19c98;
    *src = 0;
}

/* FUN_000523c8 @ 0x000523c8   (est. txm_range_buf_reserve)
 * Ghidra: undefined8 FUN_000523c8(ulong*,undefined8,ulong*)
 * Reserves a buffer for a hash range: if the requested capacity
 * (*param_3) is >= the range length (param_1[1]), zeroes the buffer,
 * stores the length into *param_3 and returns the buffer; otherwise
 * returns 0. Faults 0x19 on invalid range.
 * Confidence: medium
 */
static uint64_t txm_range_buf_reserve(uint64_t *rng, uint64_t buf, uint64_t *cap)
{
    if (*cap < rng[1]) return 0;
    if (*rng <= *rng + rng[1]) {
        txm_memzero((void*)buf, rng[1]);
        uint64_t n = rng[1];
        if ((n <= *cap) && (*cap = n, n != 0)) return buf;
    }
    txm_fault_impl(0x19, 0);
}

/* ================================================================== */
/* 0x5244c .. 0x52bec — odometer / anti-replay / ODP region           */
/* ================================================================== */

/* FUN_0005244c @ 0x0005244c   (est. txm_hash_range_destroy)
 * Ghidra: void FUN_0005244c(undefined8*)
 * Destroys a hash range: if *param_1 nonzero, calls the range's
 * teardown vtable slots (+0x18, +0x20) with {base,len,flags} and resets
 * the ops to the empty table (0x19c70). Faults 0x19 on invalid range.
 * Confidence: medium
 */
static void txm_hash_range_destroy(uint64_t *slot)
{
    uint64_t *r = (uint64_t*)*slot;
    if (r != NULL) {
        if (r + 5 <= r) txm_fault_impl(0x19, 0);
        if (r[2] != 0) {
            uint64_t b = r[0], n = r[1];
            if (b + n < b) txm_fault_impl(0x19, 0);
            uint64_t fl = r[4];
            (*(void(**)(uint64_t,uint64_t,uint64_t))(r[2] + 0x18))(b, n, fl);
            (*(void(**)(uint64_t,uint64_t,uint64_t))(r[2] + 0x20))(b, n, fl);
            r[2] = 0x19c70;
        }
        *slot = 0;
    }
}

/* FUN_000524f8..52528 (7 fns)   (est. txm_noop17..23)
 * Ghidra: void FUN_000524f8/500/508/510/518/520/528(void)
 * Empty stubs.
 * Confidence: high
 */
static void txm_noop17(void) { return; }
static void txm_noop18(void) { return; }
static void txm_noop19(void) { return; }
static void txm_noop20(void) { return; }
static void txm_noop21(void) { return; }
static void txm_noop22(void) { return; }
static void txm_noop23(void) { return; }

/* FUN_00052530 / 4f34   (est. txm_panic_destroy_twice)
 * Ghidra: void FUN_00052530/4f34(void)
 * noreturn panic "panic: attempt to destroy already-..." (0x3d16).
 * Confidence: high
 */
static void txm_panic_destroy_twice(void) { txm_panic_msg(0x3d16); }
static void txm_panic_destroy_twice_b(void) { txm_panic_msg(0x3d16); }

/* FUN_00052548 / 4f4c   (est. txm_panic_dealloc_loaded)
 * Ghidra: void FUN_00052548/4f4c(void)
 * noreturn panic "panic: attempt to deallocate loaded..." (0x3d50).
 * Confidence: high
 */
static void txm_panic_dealloc_loaded(void) { txm_panic_msg(0x3d50); }
static void txm_panic_dealloc_loaded_b(void) { txm_panic_msg(0x3d50); }

/* FUN_00052564 @ 0x00052564   (est. txm_panic_dealloc_loaded2)
 * Ghidra: void FUN_00052564(void)
 * noreturn panic "panic: attempt to deallocate loaded..." (0x3d80).
 * Confidence: high
 */
static void txm_panic_dealloc_loaded2(void) { txm_panic_msg(0x3d80); }

/* FUN_000525b8 @ 0x000525b8   (est. txm_odometer_verify_nonce)
 * Ghidra: ulong FUN_000525b8(long,undefined8*)
 * Verifies the odometer nonce for a manifest: requires the nonce
 * present (param_2+0x12 short), queries the boot-anticipation context
 * (FUN_0005c0cc), and on success computes and verifies the anti-replay
 * nonce digest (FUN_00058fa0/5bd78/5b7f0). Returns 0 on success; error
 * codes 0x54/2 and 0x6b-family on failure.
 * Confidence: low (multi-step odometer verification; field layout
 *   inferred from context)
 * Notes: "odometer: %s: ..." error strings at 0x3cb6/0x3de0/0x3e37/
 *   0x3e6c; FUN_00052804 panics on illegal chip config; 0x40-byte
 *   digest buffer.
 */
static uint64_t txm_odometer_verify_nonce(uint64_t ctx, uint64_t *params)
{
    uint64_t canary = txm_canary;
    uint64_t name = *params;
    uint64_t hash = txm_manifest_hash_resolve(ctx, params[2]);
    if (*(uint16_t*)(params + 0x12) == 0) {
        FUN_00051c78();
        goto fail_canary;
    }
    uint64_t obj = params[2];
    uint32_t type = *(uint32_t*)(params + 3);
    uint64_t q[2] = {0,0}, dig[2] = {0,0};
    uint64_t nonce[0x41] = {0};
    nonce[0] = 0x40;
    uint64_t r = FUN_0005c0cc(params, ctx, type, &q[0]);
    if ((int)r == 6) {
        if (*(uint64_t*)(obj + 0xb0) == 0) { txm_panic_illegal_chip_config(); txm_fault_impl(0x19, 0); }
        r = FUN_00058fb0(name, *(uint64_t*)(obj + 0xb0) + 0x1c, (uint64_t)(&nonce[1]) | 8, &nonce[0]);
        if ((int)r == 0) {
            if (0x40 < nonce[0]) txm_fault_impl(0x19, 0);
            txm_img4_install_hash((uint64_t)&nonce[1], (uint64_t)(&nonce[1]) | 8, nonce[0]);
            goto verify;
        }
        uint64_t n = *params;
        txm_bc_ctx_release(params[2]);
        txm_log_error(n, 0, "odometer: %s: %s failed to query nonce (%s)", 0x3e37);
        goto out_chk;
    } else if ((int)r != 0) {
        uint64_t n = *params;
        txm_bc_ctx_release(params[2]);
        txm_log_error(n, 0, "odometer: %s: %s failed to query (%s)", 0x3e6c);
        goto out_chk;
    } else {
        r = FUN_00058fa0(name, obj, type, &q[0], &dig[0]);
        if ((int)r != 0) {
            uint64_t n = *params;
            txm_bc_ctx_release(params[2]);
            txm_log_error(n, 0, "odometer: %s: %s failed to entangle (%s)", 0x3de0);
            goto out_chk;
        }
        FUN_0005bd78(name, obj, &dig[0], &nonce[1]);
    }
verify:
    if (FUN_0005b7f0(hash, name, params + 8, &nonce[1]) != 0) {
        r = (uint64_t)*(uint32_t*)(ctx + 0x18);
        uint64_t n = *params;
        txm_bc_ctx_release(params[2]);
        txm_log_error(n, 0, "odometer: %s: %s anti-replay violation (%s)", 0x3cb6);
        goto out_chk;
    }
    r = 0;
out_chk:
    if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
fail_canary:
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_00052804 @ 0x00052804   (est. txm_panic_illegal_chip_config)
 * Ghidra: void FUN_00052804(void)
 * noreturn panic "panic: illegal chip expert config" (0x3e0e).
 * Confidence: high
 */
static void txm_panic_illegal_chip_config(void) { txm_panic_msg(0x3e0e); }

/* FUN_0005282c @ 0x0005282c   (est. txm_anti_replay_none)
 * Ghidra: undefined8 FUN_0005282c(undefined8,undefined8,undefined1*)
 * Sets the anti-replay mode byte to 0 and returns 0 (no anti-replay).
 * Confidence: high
 */
static uint64_t txm_anti_replay_none(uint64_t a, uint64_t b, uint8_t *out)
{
    *out = 0;
    return 0;
}

/* FUN_0005283c @ 0x0005283c   (est. txm_noop24)
 * Ghidra: void FUN_0005283c(void)
 * Empty stub.
 * Confidence: high
 */
static void txm_noop24(void) { return; }

/* FUN_00052844 / 4f48   (est. txm_trap_ctx_enter_u/v)
 * Ghidra: void FUN_00052844/4f48(void)
 * PAC-checked trap-context enter.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_u(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }
static void txm_trap_ctx_enter_v(void) { txm_fault_check_pac(); txm_ctx_finish(NULL); }

/* FUN_0005286c @ 0x0005286c   (est. txm_trap_ctx_enter_w)
 * Ghidra: void FUN_0005286c(void)
 * Trap-context enter passing saved context.
 * Confidence: medium
 */
static void txm_trap_ctx_enter_w(void)
{
    uint64_t ctx = txm_ctx_save();
    txm_ctx_finish(&ctx);
}
extern uint64_t txm_ctx_finish_val(uint64_t ctx);   /* FUN_00054848 value-returning variant */

/* FUN_00052898 @ 0x00052898   (est. txm_anti_replay_none2)
 * Ghidra: undefined8 FUN_00052898(undefined8,undefined8,undefined1*)
 * Sets the anti-replay mode byte to 0 and returns 0.
 * Confidence: high
 */
static uint64_t txm_anti_replay_none2(uint64_t a, uint64_t b, uint8_t *out)
{
    *out = 0;
    return 0;
}

/* FUN_000528a8 @ 0x000528a8   (est. txm_odometer_hash_resolved)
 * Ghidra: bool FUN_000528a8(undefined8,long)
 * Returns whether the odometer hash is resolved: if the object's
 * boot-anticipation/nonce pointers are unset, resolves the hash type
 * (FUN_00052a34) and returns whether its +0x100 is zero; otherwise
 * releases the chip definition (FUN_00052a10) — faults 0x19.
 * Confidence: medium
 */
static int txm_odometer_hash_resolved(uint64_t a, uint64_t obj)
{
    uint64_t c = *(uint64_t*)(obj + 0x10);
    if ((*(uint64_t*)(c + 200) == 0) || (*(uint64_t*)(c + 0xb8) == 0)) {
        if (c < c + 0x110) {
            uint64_t h = txm_manifest_hash_resolve(a, c);
            return (h == 0) ? 1 : (*(uint64_t*)(c + 0x100) == 0);
        }
    } else if (c < c + 0x110) {
        txm_panic_illegal_chip_def();
    }
    txm_fault_impl(0x19, 0);
}

/* FUN_0005291c @ 0x0005291c   (est. txm_odometer_boot_chain_verify)
 * Ghidra: undefined8 FUN_0005291c(undefined8,undefined8*)
 * Verifies the boot-chain integrity (FUN_0005c230) unless the
 * "skip" flag (param_2+0x37) is set. On failure releases the context
 * and logs "odometer: %s: %s boot chain integrity" (0x364b). Returns 0
 * on success.
 * Confidence: medium
 */
static uint64_t txm_odometer_boot_chain_verify(uint64_t a, uint64_t *params)
{
    uint64_t canary = txm_canary;
    uint64_t r = 0;
    if ((*(uint8_t*)(params + 0x37) & 1) == 0) {
        uint64_t bc_ctx = 0;
        txm_bc_ctx_build(params[1], params[2], &bc_ctx);
        r = txm_bc_verify(params, a, 0x1a858, &bc_ctx);
        if ((uint32_t)r != 0) {
            uint64_t n = *params;
            txm_bc_ctx_release(params[2]);
            txm_log_error(n, 0, "odometer: %s: %s boot chain integrity (%s)", 0x364b);
            if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
        }
    }
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_00052a10 @ 0x00052a10   (est. txm_panic_illegal_chip_def)
 * Ghidra: void FUN_00052a10(void)
 * noreturn panic "panic: illegal chip definition" (0x3f83); first
 * releases the boot context (FUN_00042b84).
 * Confidence: high
 */
static void txm_panic_illegal_chip_def(void)
{
    txm_bc_ctx_release(0);
    txm_panic_msg(0x3f83);
}

/* FUN_00052a78 @ 0x00052a78   (est. txm_ops_slot_20)
 * Ghidra: void FUN_00052a78(long)
 * Indirect vtable dispatch: (*(param_1 + 0x20))().
 * Confidence: medium
 */
static void txm_ops_slot_20(uint64_t ops) { (*(void(**)(void))(ops + 0x20))(); }

/* FUN_00052a88 @ 0x00052a88   (est. txm_odp_validate)
 * Ghidra: undefined8 FUN_00052a88(long,undefined8*)
 * Validates an ODP (one-device policy) record: dispatches on the record
 * type (param_1+8): type 2 runs the boot-anticipation checks
 * (FUN_00058f80), type 1 checks the policy flag (FUN_0005bfb4); then
 * enforces the anti-replay conditions and calls the ODP validator vtable
 * slot (param_1+0x28). Returns 0 if the record is admissible.
 * Confidence: low (ODP policy semantics inferred)
 * Notes: "odp>odp_type" 0x3feb; "panic: unreachable case" 0x36f2.
 */
static uint64_t txm_odp_validate(uint64_t ctx, uint64_t *params)
{
    uint64_t type = *(uint64_t*)(ctx + 8);
    uint64_t r = 0;
    if (type != 0) {
        if (type == 2) {
            if (((*(uint8_t*)(params + 0x37) & 1) != 0) && ((*(uint8_t*)(params + 0x79) & 1) != 0)) return 0;
            if (FUN_00058f80(*params, params[2]) != 0) return 0;
        } else {
            if (type != 1) {
                txm_panic_unreachable();
                txm_panic_msg(0x36f2);
            }
            if ((FUN_0005bfb4(params, 0x1d618) & 1) != 0) return 0;
        }
    }
    if (((*(uint8_t*)((char*)params + 0x1b9) & 1) != 0) &&
        ((FUN_0005bfb4(params, 0x1d618) & 1) != 0 ||
         (((*(uint8_t*)((char*)params + 0x1ba) & 1) != 0 && ((*(uint8_t*)(params + 0x37) & 1) != 0)))))
        return 0;
    txm_fault_check_pac();
    return (*(uint64_t(**)(uint64_t,uint64_t*))(ctx + 0x28))(ctx, params);
}

/* FUN_00052b74 @ 0x00052b74   (est. txm_panic_unreachable)
 * Ghidra: void FUN_00052b74(void)
 * noreturn panic "panic: unreachable case" (0x36f2).
 * Confidence: high
 */
static void txm_panic_unreachable(void) { txm_panic_msg(0x36f2); }

/* FUN_00052bec @ 0x00052bec   (est. txm_odometer_verify_manifest)
 * Ghidra: ulong FUN_00052bec(long,undefined8*)
 * Verifies the odometer manifest nonce: requires the nonce present,
 * queries the boot-anticipation context, entangles and anti-replay-
 * verifies the manifest nonce (FUN_00058fa0/5bd78/5b7f0). Returns 0 on
 * success.
 * Confidence: low (multi-step; field layout inferred)
 * Notes: "odometer: %s: ..." strings at 0x3de0/0x4040e/0x406e.
 */
static uint64_t txm_odometer_verify_manifest(uint64_t ctx, uint64_t *params)
{
    uint64_t canary = txm_canary;
    if (*(uint16_t*)(params + 0x12) == 0) {
        FUN_00051c78();
        goto done;
    }
    uint64_t name = *params;
    uint64_t obj = params[2];
    uint64_t nonce = *(uint64_t*)(obj + 0xa8);
    uint32_t type = *(uint32_t*)(params + 3);
    uint64_t q[2] = {0,0}, dig[2] = {0,0}, out[2] = {0,0};
    uint64_t r = FUN_0005c0cc(params, ctx, type, &q[0]);
    if ((int)r == 0) {
        r = FUN_00058fa0(name, obj, type, &q[0], &dig[0]);
        if ((int)r != 0) {
            uint64_t n = *params;
            txm_bc_ctx_release(params[2]);
            txm_log_error(n, 0, "odometer: %s: %s failed to entangle (%s)", 0x3de0);
            goto chk;
        }
        FUN_0005bd78(name, obj, &dig[0], &out[0]);
        if (FUN_0005b7f0(nonce, name, params + 8, &out[0]) != 0) {
            r = (uint64_t)*(uint32_t*)(ctx + 0x18);
            uint64_t n = *params;
            txm_bc_ctx_release(params[2]);
            txm_log_error(n, 0, "odometer: %s: %s manifest inconsistent (%s)", 0x406e);
            goto chk;
        }
        r = 0;
    } else {
        uint64_t n = *params;
        txm_bc_ctx_release(params[2]);
        txm_log_error(n, 0, "odometer: %s: %s failed to query (%s)", 0x403e);
    }
chk:
    if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
done:
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* ================================================================== */
/* 0x52da8 .. 0x53604 — image4 nonce handle / release-type region     */
/* ================================================================== */

/* FUN_00052da8 @ 0x00052da8   (est. txm_obj_type_ptr)
 * Ghidra: undefined8 FUN_00052da8(long)
 * Returns the object's type pointer (*(param_1+0x10)).
 * Confidence: high
 */
static uint64_t txm_obj_type_ptr(uint64_t obj) { return *(uint64_t*)(obj + 0x10); }

/* FUN_00052db4 @ 0x00052db4   (est. txm_nonce_handle_decode)
 * Ghidra: void FUN_00052db4(byte*)
 * Decodes a nonce handle from the object: selects the decode routine
 * (FUN_0005ace8 vs FUN_0005acfc by flag bit 4 of *param_1), copies the
 * decoded {ptr,len} into the handle fields (param_1+0x10/0x18), and
 * zeroes the trailing handle state.
 * Confidence: medium
 */
static void txm_nonce_handle_decode(uint8_t *h)
{
    uint64_t out[2] = {0,0};
    uint64_t *dec;
    if ((*h >> 4 & 1) == 0) dec = (uint64_t*)FUN_0005ace8(*(uint64_t*)(h + 0x28), &out[0]);
    else dec = (uint64_t*)FUN_0005acfc(*(uint64_t*)(h + 0x28), &out[0]);
    h[8] = 0; h[9] = 0;
    uint64_t b = dec[0], n = dec[1];
    if (b + n < b) txm_fault_impl(0x19, 0);
    *(uint64_t*)(h + 0x10) = b;
    *(uint64_t*)(h + 0x18) = n;
    for (int i = 0; i < 8; i++) *(uint64_t*)(h + 0x20 + i*8) = 0;
}

/* FUN_00052e34 @ 0x00052e34   (est. txm_manifest_prop_query)
 * Ghidra: undefined8 FUN_00052e34(long,undefined4,undefined8)
 * Queries a manifest property: selects the property table (param_1+0x48
 * if the version short at *(param_1+0x30)+0x210 is set) and looks up the
 * property by type via FUN_00045118; on failure returns 0.
 * Confidence: medium
 */
static uint64_t txm_manifest_prop_query(uint64_t obj, uint32_t type, uint64_t def)
{
    uint64_t table = 0;
    if (*(uint16_t*)(*(uint64_t*)(obj + 0x30) + 0x210) != 0)
        table = *(uint64_t*)(obj + 0x30) + 0x48;
    if (FUN_00045118(table, 0, type, def) != 0) def = 0;
    return def;
}

/* FUN_00052e80 @ 0x00052e80   (est. txm_triple_store_v2)
 * Ghidra: void FUN_00052e80(undefined8*,undefined8,undefined8,undefined8)
 * Stores {a4, a2, a3} into param_1[0], param_1[5], param_1[6].
 * Confidence: medium
 */
static void txm_triple_store_v2(uint64_t *out, uint64_t a2, uint64_t a3, uint64_t a4)
{
    out[0] = a4;
    out[5] = a2;
    out[6] = a3;
}

/* FUN_00052e90 @ 0x00052e90   (est. txm_nonce_handle_compute)
 * Ghidra: undefined8 FUN_00052e90(long,undefined8)
 * Computes the nonce for a magazine slot handle: resolves the slot by id
 * (FUN_00051bd0), derives the nonce digest (FUN_00051d54/51ecc), and
 * emits the manifest object (FUN_0004f904) from the derived nonce.
 * Returns 0 on success; logs "no nonce slot for handle" (0x40d0) and
 * "slot: %s: failed to compute nonce" (0x40f3) errors.
 * Confidence: medium
 */
static uint64_t txm_nonce_handle_compute(uint64_t obj, uint64_t out)
{
    uint64_t canary = txm_canary;
    uint64_t ctx = txm_ctx_current_or_dispatch();
    uint64_t mag = FUN_00058ff0();
    uint64_t slot = 0, obj2 = 0, nonce = 0;
    uint64_t r = txm_magazine_slot_find_id(mag, *(uint64_t*)(obj + 8), &slot);
    if ((int)r == 0) {
        obj2 = txm_obj_run_vtbl_10(slot);
        r = txm_obj_derive_nonce((uint64_t*)&obj2, (uint64_t)&nonce);
        if ((int)r == 0) {
            txm_obj_destroy(&obj2);
            r = txm_nonce_derive_digest((uint64_t*)slot, ctx, &nonce, (uint64_t)&obj2);
            if ((int)r == 0) {
                txm_manifest_obj_init((uint16_t*)out, obj2);
                txm_obj_destroy(&obj2);
                goto done;
            }
            txm_log_error(ctx, 0, "slot: %s: failed to compute nonce (%s)", 0x40f3);
        }
    } else {
        txm_log_error(ctx, 0, "no nonce slot for handle (%llx)", 0x40d0);
    }
    txm_obj_destroy(&obj2);
    if (0x6b < (uint32_t)r) txm_fault_impl(0, 0);
done:
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_00052fe4 @ 0x00052fe4   (est. txm_manifest_decode_string)
 * Ghidra: ulong FUN_00052fe4(undefined8,undefined8*,undefined8)
 * Decodes a manifest string field (FUN_0002ebb8): requires a non-empty
 * string, else sets the error code 0x22 and returns 0xffffffff. Returns
 * 0 on success with *param_2 = the string pointer.
 * Confidence: medium
 */
static uint64_t txm_manifest_decode_string(uint64_t src, uint64_t *out, uint64_t a3)
{
    char *str = NULL;
    uint32_t *err = FUN_00029750();
    *err = 0;
    uint64_t r = FUN_0002ebb8(src, &str, a3);
    if ((str == NULL) || (*str == '\0')) {
        if (r >> 0x20 != 0) {
            uint32_t *e2 = FUN_00029750();
            *e2 = 0x22;
            r = 0xffffffff;
        }
    } else {
        r = 0;
        if (out != NULL) *out = (uint64_t)str;
    }
    return r;
}

/* FUN_00053070 @ 0x00053070   (est. txm_expert_name_split)
 * Ghidra: char* FUN_00053070(long*,ulong)
 * Splits an expert record name at a "::" separator: searches the string
 * (FUN_0002dd00) for the prefix of length >= 2, terminates the prefix
 * and returns the remainder (or NULL). Faults 0x19 on invalid bounds.
 * Confidence: medium
 */
static char *txm_expert_name_split(uint64_t *rec, uint64_t name)
{
    uint64_t base = *rec;
    if (base == 0) return NULL;
    uint64_t i = 0;
    while (*(char*)(name + i) != '\0') i = i + 1;
    if ((1 < i) && (name <= name + i)) {
        uint64_t sep = FUN_0002dbe0(name, 2);
        if (1 < sep) return NULL;
        char *p = (char*)FUN_0002dd00(base, name);
        if (p == NULL) {
            char *r = NULL;
            *rec = (uint64_t)r;
            return p;
        }
        if (*p != '\0') {
            uint64_t len = 0;
            while (p[len + 1] != '\0') len = len + 1;
            *p = '\0';
            if (0 < len) {
                char *r = NULL;
                if (p[1] != '\0') r = p + 1;
                if (r < p + len + 1) { *rec = (uint64_t)r; return p; }
            }
        }
    }
    txm_fault_impl(0x19, 0);
}

/* FUN_00053150 @ 0x00053150   (est. txm_odometer_nonce_disabled)
 * Ghidra: bool FUN_00053150(undefined8,long)
 * Returns whether the odometer nonce is disabled: true if the hash is
 * unresolved; if the nonce pointer (+0xa8) is set, faults "illegal chip
 * definition" (FUN_00053310); otherwise returns whether the nonce short
 * (param_2+0x90) is zero.
 * Confidence: medium
 */
static int txm_odometer_nonce_disabled(uint64_t a, uint64_t obj)
{
    uint64_t c = *(uint64_t*)(obj + 0x10);
    uint64_t h = txm_manifest_hash_resolve(a, c);
    if (h == 0) return 1;
    if (*(uint64_t*)(c + 0xa8) != 0) {
        if (c < c + 0x110) FUN_00053310(c);
        txm_fault_impl(0x19, 0);
    }
    return *(uint16_t*)(obj + 0x90) == 0;
}

/* FUN_000531b8 @ 0x000531b8   (est. txm_odometer_verify_stamp)
 * Ghidra: ulong FUN_000531b8(long,undefined8*)
 * Verifies the odometer stamp/nonce: if the anti-replay short
 * (param_2+0x1d) is zero, verifies the boot-anticipation nonce
 * (FUN_00057c20/5c230); otherwise runs the direct anti-replay check
 * (FUN_0005b7f0). Returns 0 on success; logs "odometer: %s: %s
 * anti-replay violation" (0x3cb6).
 * Confidence: medium
 */
static uint64_t txm_odometer_verify_stamp(uint64_t ctx, uint64_t *params)
{
    uint64_t canary = txm_canary;
    uint64_t name = *params;
    uint64_t hash = txm_manifest_hash_resolve(ctx, params[2]);
    uint64_t r = 0;
    if (*(uint16_t*)(params + 0x1d) == 0) {
        uint64_t ctx2 = 0;
        FUN_00057c20(&ctx2, params + 8);
        r = txm_bc_verify(params, ctx, hash, &ctx2);
        if ((int)r != 0) {
            uint64_t n = *params;
            txm_bc_ctx_release(params[2]);
            txm_log_error(n, 0, "odometer: %s: %s anti-replay violation (%s)", 0x3cb6);
            if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
        }
    } else {
        if (FUN_0005b7f0(hash, name, params + 8, params + 0x13) == 0) {
            r = 0;
        } else {
            r = (uint64_t)*(uint32_t*)(ctx + 0x18);
            uint64_t n = *params;
            txm_bc_ctx_release(params[2]);
            txm_log_error(n, 0, "odometer: %s: %s anti-replay violation (%s)", 0x3cb6);
            if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
        }
    }
    if (txm_canary != canary) txm_stack_check_fail();
    return r;
}

/* FUN_00053310 @ 0x00053310   (est. txm_panic_illegal_chip_def_b)
 * Ghidra: void FUN_00053310(void)
 * noreturn panic "panic: illegal chip definition" (0x41e3); releases
 * the boot context first.
 * Confidence: high
 */
static void txm_panic_illegal_chip_def_b(void)
{
    txm_bc_ctx_release(0);
    txm_panic_msg(0x41e3);
}

/* FUN_00053334 @ 0x00053334   (est. txm_odometer_seal_disabled)
 * Ghidra: bool FUN_00053334(undefined8,long)
 * Returns whether the odometer seal is disabled: true if the hash is
 * unresolved, else whether the seal short (param_2+0x140) is zero.
 * Confidence: medium
 */
static int txm_odometer_seal_disabled(uint64_t a, uint64_t obj)
{
    uint64_t h = txm_manifest_hash_resolve(a, *(uint64_t*)(obj + 0x10));
    if (h == 0) return 1;
    return *(uint16_t*)(obj + 0x140) == 0;
}

/* FUN_00053374 @ 0x00053374   (est. txm_odometer_verify_seal)
 * Ghidra: undefined8 FUN_00053374(undefined8,undefined8*)
 * Verifies the odometer seal: requires the seal short (param_2+0x28),
 * verifies the boot-chain integrity (FUN_00057c20/5c230). Returns 0 on
 * success; logs "odometer: %s: %s boot chain integrity" (0x364b).
 * Confidence: medium
 */
static uint64_t txm_odometer_verify_seal(uint64_t a, uint64_t *params)
{
    uint64_t canary = txm_canary;
    uint64_t hash = txm_manifest_hash_resolve(a, params[2]);
    uint64_t r = 0;
    if (*(uint16_t*)(params + 0x28) == 0) {
        FUN_00051c78();
    } else {
        uint64_t ctx2 = 0;
        FUN_00057c20(&ctx2, params + 0x1e);
        r = txm_bc_verify(params, a, hash, &ctx2);
        if ((uint32_t)r != 0) {
            uint64_t n = *params;
            txm_bc_ctx_release(params[2]);
            txm_log_error(n, 0, "odometer: %s: %s boot chain integrity (%s)", 0x364b);
            if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
        }
        if (txm_canary != canary) txm_stack_check_fail();
        return r;
    }
    txm_stack_check_fail();
    return r;
}

/* FUN_00053470 / 4f74   (est. txm_odometer_seal_available)
 * Ghidra: undefined8 FUN_00053470/4f74(undefined8,long)
 * Returns 1 if the seal flag (+0xf0) is clear (no seal), else faults
 * "illegal chip definition" (FUN_000535bc) if the nonce is set, and
 * returns 0.
 * Confidence: medium
 */
static uint64_t txm_odometer_seal_available(uint64_t a, uint64_t obj)
{
    uint64_t c = *(uint64_t*)(obj + 0x10);
    if (*(uint64_t*)(c + 0xf0) == 0) return 1;
    if (*(uint64_t*)(c + 0xa8) != 0) {
        if (c < c + 0x110) txm_panic_illegal_chip_def_c();
        txm_fault_impl(0x19, 0);
    }
    return 0;
}
static uint64_t txm_odometer_seal_available_b(uint64_t a, uint64_t obj)
{
    return txm_odometer_seal_available(a, obj);
}

/* FUN_000534bc @ 0x000534bc   (est. txm_odometer_verify_all_seals)
 * Ghidra: undefined8 FUN_000534bc(undefined8,undefined8*)
 * Verifies all odometer seals: if the "skip" policy flag
 * (FUN_0005bfb4 0x1d648) is clear, iterates the seal slots and verifies
 * each via FUN_0005c230. Returns 0 on success.
 * Confidence: medium
 */
static uint64_t txm_odometer_verify_all_seals(uint64_t a, uint64_t *params)
{
    uint64_t obj = params[2];
    if ((FUN_0005bfb4(params, 0x1d648) & 1) == 0) {
        int first = 1;
        do {
            int more = first;
            if ((*(uint64_t*)(obj + 0xf0) != 0) && (params != NULL) &&
                (*(uint16_t*)(params + 0x43 + 0xd) != 0)) {
                uint64_t r = txm_bc_verify(params, a, 0, NULL);
                if ((uint32_t)r != 0) {
                    uint64_t n = *params;
                    txm_bc_ctx_release(params[2]);
                    txm_log_error(n, 0, "odometer: %s: %s anti-replay violation (%s)", 0x3cb6);
                    if ((uint32_t)r < 0x6c) return r;
                    txm_panic_msg(0x3b00);
                }
            }
            first = 0;
        } while (0 && first);
    }
    return 0;
}

/* FUN_000535bc @ 0x000535bc   (est. txm_panic_illegal_chip_def_c)
 * Ghidra: void FUN_000535bc(void)
 * noreturn panic "panic: illegal chip definition" (0x4281); releases
 * the boot context first.
 * Confidence: high
 */
static void txm_panic_illegal_chip_def_c(void)
{
    txm_bc_ctx_release(0);
    txm_panic_msg(0x4281);
}

/* FUN_000535e0 @ 0x000535e0   (est. txm_release_type_table)
 * Ghidra: undefined8 FUN_000535e0(ulong)
 * Returns the release-type table entry at DAT_0001af68[param_1] for
 * param_1 < 7, else 0.
 * Confidence: medium
 */
static uint64_t txm_release_type_table(uint64_t idx)
{
    if (idx < 7) return *(uint64_t*)(0x1af68 + idx * 8);
    return 0;
}

/* FUN_00053604 @ 0x00053604   (est. txm_release_type_set)
 * Ghidra: undefined8 FUN_00053604(undefined8,undefined8,undefined8)
 * Sets the image4 release type: queries the chip (FUN_00058ff0), maps
 * the release-type via FUN_00053cd4 (image4 release-type handler), and
 * applies it (FUN_00054688). Logs "failed to set release type (%d)"
 * (0x42d6) on failure. Returns 0 on success.
 * Confidence: low (release-type mapping semantics inferred)
 */
static uint64_t txm_release_type_set(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t canary = txm_canary;
    uint64_t ctx = txm_ctx_current();
    uint64_t chip = 0, rt = 0, buf[0x11] = {0};
    FUN_00058ff0();
    chip = FUN_00054784(ctx);
    uint64_t r = FUN_00053cd4(ctx, a, b, c, &buf[0], 0x40);
    if ((int)r == 0) {
        rt = txm_ctx_finish_val(chip);
        r = FUN_00054688(rt, &buf[0]);
        if ((int)r == 0) {
            txm_ctx_finish(&rt);
        } else {
            txm_log_error(ctx, 0, "failed to set release type (%d)", 0x42d6);
        }
    }
    txm_ctx_finish(&rt);
    txm_ctx_finish(&chip);
    if ((uint32_t)r < 0x6c) {
        if (txm_canary != canary) txm_stack_check_fail();
        return r;
    }
    txm_fault_impl(0, 0);
    return r;
}

/* ================================================================== */
/* 0x53728 .. 0x53e48 — image4 trap handlers (set/release/activate)   */
/* ================================================================== */

/* FUN_00053728 @ 0x00053728   (est. txm_trap_set_nonce)
 * Ghidra: undefined8 FUN_00053728(undefined8,undefined8,undefined8)
 * Image4 "set nonce" trap handler: decodes the input (FUN_00053cd4),
 * looks up the magazine slot by handle (FUN_00051b3c), and stores the
 * nonce counter/replay fields into the slot. Returns 0 on success;
 * logs "no slot for handle (%llx) (%d)" (0x4347); error 0x25 (slot
 * already set) / 0x54 (bad length).
 * Confidence: medium
 */
static uint64_t txm_trap_set_nonce(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t canary = txm_canary;
    uint64_t ctx = txm_ctx_current();
    uint64_t inp[0x11] = {0};
    uint64_t slot = 0, obj = 0;
    uint64_t mag = FUN_00058ff0();
    uint64_t chip = FUN_00054784(ctx);
    uint64_t r = FUN_00053cd4(ctx, a, b, c, &inp[0], 0x2c);
    uint64_t result = r;
    if ((int)r == 0) {
        if (inp[0] >> 0x20 == 0) {
            r = txm_magazine_slot_find_type(mag, (uint32_t)inp[0], &slot);
            if (slot == 0) {
                txm_log_error(ctx, 0, "no slot for handle (%llx) (%d)", 0x4347);
            } else {
                obj = txm_obj_run_vtbl_10(slot);
                uint64_t st = *(uint64_t*)(obj + 0x20);
                if (*(uint64_t*)(st + 0x28) == 0) {
                    uint64_t s2 = *(uint64_t*)(slot + 0x20);
                    *(uint32_t*)(s2 + 1) = (uint32_t)inp[1] & 0x7f;
                    *(uint64_t*)(s2 + 0xd) = inp[3];
                    *(uint64_t*)(s2 + 5) = inp[2];
                    *(uint64_t*)(st + 0x38) = inp[0x11 - 1];
                    *(uint64_t*)(st + 0x30) = inp[4];
                    *(uint64_t*)(st + 0x28) = st + 0x30;
                    txm_obj_destroy(&obj);
                    result = 0;
                } else {
                    result = 0x25;
                }
            }
        } else {
            result = 0x54;
        }
    }
    txm_obj_destroy(&obj);
    txm_ctx_finish(&chip);
    if ((uint32_t)result < 0x6c) {
        if (txm_canary != canary) txm_stack_check_fail();
        return result;
    }
    txm_fault_impl(0, 0);
    return result;
}

/* FUN_000538a8 @ 0x000538a8   (est. txm_trap_clear_nonce)
 * Ghidra: undefined8 FUN_000538a8(undefined8,undefined8,undefined8)
 * Image4 "clear nonce" trap handler: looks up the magazine slot by
 * handle, checks the caller entitlement (FUN_0005020c), and clears the
 * nonce slot (FUN_00051dc0). Returns 0 on success; logs "no slot for
 * handle" (0x4347) and "slot: %s: caller not entitled" (0x4364).
 * Confidence: medium
 */
static uint64_t txm_trap_clear_nonce(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t ctx = txm_ctx_current();
    uint64_t inp = 0;
    uint64_t *slot = NULL;
    uint64_t obj = 0;
    uint64_t mag = FUN_00058ff0();
    uint64_t chip = FUN_00054784(ctx);
    uint64_t r = FUN_00053cd4(ctx, a, b, c, &inp, 8);
    if ((int)r == 0) {
        if (inp >> 0x20 == 0) {
            r = txm_magazine_slot_find_type(mag, (uint32_t)inp, (uint64_t*)&slot);
            if (slot == NULL) {
                txm_log_error(ctx, 0, "no slot for handle (%llx) (%d)", 0x4347);
            } else {
                r = txm_expert_available(*(uint64_t*)(*slot + 0x38));
                if ((int)r == 0) {
                    obj = txm_obj_run_vtbl_10((uint64_t)slot);
                    txm_nonce_set_replay_bit((uint64_t)slot);
                    txm_obj_destroy(&obj);
                    goto done;
                }
                txm_log_error(ctx, 0, "slot: %s: caller not entitled to clear", 0x4364);
            }
            txm_ctx_finish(&chip);
            if ((uint32_t)r < 0x6c) return r;
            txm_fault_impl(0, 0);
        }
        r = 0x54;
    }
done:
    txm_ctx_finish(&chip);
    return r;
}

/* FUN_000539ec @ 0x000539ec   (est. txm_trap_activate)
 * Ghidra: undefined8 FUN_000539ec(undefined8,undefined8,undefined8)
 * Image4 "activate image" trap handler: resolves the image manifest by
 * handle (FUN_0004f408), checks the activation entitlement
 * (FUN_0005020c), maps the user buffers (FUN_00053d38), and executes
 * the manifest (FUN_0004f460). Returns 0 on success; logs "no image for
 * handle" (0x4394) and "caller not entitled to activate" (0x43b2) and
 * "activation failed" (0x3034).
 * Confidence: medium
 */
static uint64_t txm_trap_activate(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t ctx = txm_ctx_current();
    uint64_t inp[2] = {0,0}, buf[0x11] = {0}, buf2[0x11] = {0};
    uint64_t *imgs = (uint64_t*)FUN_00059000();
    uint64_t chip = FUN_00054784(ctx);
    uint64_t r = FUN_00053cd4(ctx, a, b, c, &inp[0], 0x20);
    uint64_t result = r;
    if ((int)r == 0) {
        uint64_t img = txm_image4_find_manifest((uint64_t)imgs, inp[0]);
        if (img == 0) {
            result = 2;
            txm_log_error(ctx, 0, "no image for handle (%llx) (%d)", 0x4394);
        } else {
            result = txm_expert_available(*(uint64_t*)(img + 8));
            if ((int)result != 0) {
                uint64_t n = *imgs;
                txm_log_error(n, 0, "%s: caller not entitled to activate", 0x43b2);
                txm_ctx_finish(&chip);
                if ((uint32_t)result < 0x6c) return result;
                txm_fault_impl(0, 0);
            }
            result = txm_user_buffer_map(ctx, a, inp[1], (uint32_t)inp[2], *(uint64_t*)(img + 0x20), (uint64_t)&buf[0]);
            if (((int)result == 0) &&
                (result = txm_user_buffer_map(ctx, a, (uint64_t)inp[1], (uint32_t)inp[2],
                                              *(uint64_t*)(img + 0x28), (uint64_t)&buf2[0]), (int)result == 0)) {
                if ((imgs + 3 <= imgs) || (img + 0x70 <= img)) txm_fault_impl(0x19, 0);
                result = txm_manifest_execute(imgs, img, (uint64_t)&buf[0], (uint64_t)&buf2[0]);
                if ((int)result != 0) {
                    uint64_t n = *imgs;
                    txm_log_error(n, 0, "%s: activation failed (%d)", 0x3034);
                }
            }
        }
    }
    txm_ctx_finish(&chip);
    return result;
}

/* FUN_00053ba4 @ 0x00053ba4   (est. txm_trap_set_boot_uuid)
 * Ghidra: undefined8 FUN_00053ba4(undefined8,undefined8,undefined8)
 * Image4 "set boot uuid" trap handler: decodes the 0x10-byte input and
 * sets the boot UUID (FUN_0005470c). Logs "failed to set boot uuid (%d)"
 * (0x448a) on failure. Returns 0 on success.
 * Confidence: medium
 */
static uint64_t txm_trap_set_boot_uuid(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t canary = txm_canary;
    uint64_t ctx = txm_ctx_current();
    uint64_t inp[2] = {0,0};
    uint64_t chip = FUN_00054784(ctx);
    uint64_t r = FUN_00053cd4(ctx, a, b, c, &inp[0], 0x10);
    uint64_t result = r;
    if ((int)r == 0) {
        uint64_t r2 = FUN_0005470c(chip, &inp[0]);
        if ((uint32_t)r2 != 0) {
            txm_log_error(ctx, 0, "failed to set boot uuid (%d)", 0x448a);
            txm_ctx_finish(&chip);
            if (0x6b < (uint32_t)r2) txm_fault_impl(0, 0);
            result = r2;
            goto done;
        }
        txm_ctx_finish(&chip);
    }
    txm_ctx_finish(&chip);
    result = r;
done:
    if (txm_canary != canary) txm_stack_check_fail();
    return result;
}

/* FUN_00053cb0 @ 0x00053cb0   (est. txm_trap_release_type_table)
 * Ghidra: undefined8 FUN_00053cb0(ulong)
 * Returns the trap release-type table entry at DAT_0000d880[param_1]
 * for param_1 < 7, else 0xffffffffffffffff.
 * Confidence: medium
 */
static uint64_t txm_trap_release_type_table(uint64_t idx)
{
    if (idx < 7) return *(uint64_t*)(0xd880 + idx * 8);
    return 0xffffffffffffffffull;
}

/* FUN_00053cd4 @ 0x00053cd4   (est. txm_trap_copy_input)
 * Ghidra: undefined8 FUN_00053cd4(undefined8,undefined8,undefined8,long,undefined8,long)
 * Copies a trap input of expected length param_6 from param_3 into
 * param_5; faults if the input length mismatches ("trap input has
 * unexpected length", 0x42f5, error 0x54).
 * Confidence: high
 */
static uint64_t txm_trap_copy_input(uint64_t ctx, uint64_t a, uint64_t src, uint64_t len,
                                    uint64_t dst, uint64_t expect)
{
    if (len == expect) {
        txm_memzero((void*)dst, len);
        return 0;
    }
    txm_log_error(ctx, 0, "trap input has unexpected length (%s)", 0x42f5);
    return 0x54;
}

/* FUN_00053d38 @ 0x00053d38   (est. txm_user_buffer_map)
 * Ghidra: undefined8 FUN_00053d38(undefined8,undefined8,long,ulong,ulong,undefined8)
 * Maps a user buffer {ptr, len} into a TXM hash range: requires a
 * non-null pointer (error 0x16 "user buffer is null"), nonzero length
 * (0x16 "user buffer length is zero"), and length <= max (0x54 "user
 * buffer exceeds maximum bounds"). On success emits the hash range via
 * FUN_000522b4 and returns 0.
 * Confidence: medium
 */
static uint64_t txm_user_buffer_map(uint64_t ctx, uint64_t a, uint64_t ptr, uint64_t len,
                                    uint64_t max, uint64_t out)
{
    if (ptr == 0) {
        txm_log_error(ctx, 0, "user buffer is null (trap (0x%l)", 0x43e0);
        return 0x16;
    }
    if (len == 0) {
        txm_log_error(ctx, 0, "user buffer length is zero (trap", 0x4407);
        return 0x16;
    }
    if (len <= max) {
        uint64_t rng[2] = {ptr, 0};
        txm_hash_range_move((uint64_t*)out, &rng[0], len, 0x19c98, 0);
        return 0;
    }
    txm_log_error(ctx, 0, "user buffer exceeds maximum bounds (trap", 0x4435);
    return 0x54;
}

/* FUN_00053de8 @ 0x00053de8   (est. txm_odometer_nonce_absent)
 * Ghidra: bool FUN_00053de8(undefined8,long)
 * Returns whether the odometer nonce is absent: true if the hash is
 * unresolved, the nonce/counter pointers are unset, or the image
 * digest (FUN_00059980) is unresolved; else whether the nonce short
 * (param_2+0x90) is zero.
 * Confidence: medium
 */
static int txm_odometer_nonce_absent(uint64_t a, uint64_t obj)
{
    uint64_t c = *(uint64_t*)(obj + 0x10);
    uint64_t h = txm_manifest_hash_resolve(a, c);
    if (((h == 0) || (*(uint64_t*)(c + 0x50) == 0)) ||
        (*(uint64_t*)(c + 0x58) != 0) ||
        (FUN_00059980(*(uint64_t*)(obj + 8)) == 0)) return 1;
    return *(uint16_t*)(obj + 0x90) == 0;
}

/* FUN_00053e48 @ 0x00053e48   (est. txm_odometer_verify_img_digest)
 * Ghidra: ulong FUN_00053e48(long,undefined8*)
 * Verifies the odometer image digest: requires the nonce, resolves the
 * image digest (FUN_00059980), queries the boot context
 * (FUN_0005c134), entangles and anti-replay-verifies the digest
 * (FUN_00058fa0/5bd78/5b7f0). Returns 0 on success.
 * Confidence: low (multi-step; field layout inferred)
 * Notes: "odometer: %s: ..." strings at 0x3de0/0x406e/0x4528.
 */
static uint64_t txm_odometer_verify_img_digest(uint64_t ctx, uint64_t *params)
{
    uint64_t canary = txm_canary;
    if (*(uint16_t*)(params + 0x12) == 0) {
        FUN_00051c78();
    } else {
        uint64_t obj = params[2];
        uint64_t nonce = *(uint64_t*)(obj + 0xa8);
        uint32_t type = *(uint32_t*)(params + 3);
        uint64_t q[2] = {0,0}, dig[2] = {0,0}, out[2] = {0,0};
        uint64_t name = *params;
        uint64_t img = FUN_00059980(params[1]);
        uint64_t r;
        if (img != 0) {
            r = FUN_0005c134(params, img, &q[0]);
            if ((int)r == 0) {
                r = FUN_00058fa0(name, obj, type, &q[0], &dig[0]);
                if ((int)r != 0) {
                    uint64_t n = *params;
                    txm_bc_ctx_release(params[2]);
                    txm_log_error(n, 0, "odometer: %s: %s failed to entangle (%s)", 0x3de0);
                    goto chk;
                }
                FUN_0005bd78(name, obj, &dig[0], &out[0]);
                if (FUN_0005b7f0(nonce, name, params + 8, &out[0]) != 0) {
                    r = (uint64_t)*(uint32_t*)(ctx + 0x18);
                    uint64_t n = *params;
                    txm_bc_ctx_release(params[2]);
                    txm_log_error(n, 0, "odometer: %s: %s manifest inconsistent (%s)", 0x406e);
                    goto chk;
                }
                r = 0;
            } else {
                uint64_t n = *params;
                txm_bc_ctx_release(params[2]);
                txm_log_error(n, 0, "odometer: %s: %s failed to query (%s)", 0x4528);
chk:
                if (0x6b < (uint32_t)r) txm_panic_msg(0x3b00);
            }
            if (txm_canary != canary) txm_stack_check_fail();
            return r;
        }
    }
    FUN_0005400c();
    txm_stack_check_fail();
    return 0;
}

#undef txm_fault
#define txm_fault(code, addr) txm_fault_impl(code, addr)
#endif /* __ASSEMBLER__ */