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
static uint64_t txm_pa_resolve(uint64_t pa, uint64_t *out);   /* FUN_00061ea4 */
extern void CallSupervisor(int svc);

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
                    char *name = NULL; uint32_t len = 0;
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
                            char *n = name;
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
                                          char **name, uint32_t *len)
{
    return txm_dt_property_find(node, key, name, len, (int*)*root, root[1]);
}

/* FUN_0004eb44 @ 0x0004eb44   (est. txm_dt_property_find)
 * Ghidra: undefined8 FUN_0004eb44(int*,long,ulong*,uint*,int*,long)
 * Searches the DeviceTree node param_1 for the property whose name
 * matches the string at param_2; on match returns 1 and stores the
 * property value {ptr,len} into *param_3/*param_4. Returns 0xffffffff on
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
 * Each issues CallSupervisor(0) — a supervisor/EL3 service call. Three
 * identical trampolines; distinct service-selector semantics unknown.
 * Confidence: medium
 */
static void txm_supervisor_call_a(void) { CallSupervisor(0); }
static void txm_supervisor_call_b(void) { CallSupervisor(0); }
static void txm_supervisor_call_c(void) { CallSupervisor(0); }

#undef txm_fault
#define txm_fault(code, addr) txm_fault_impl(code, addr)
#endif /* __ASSEMBLER__ */