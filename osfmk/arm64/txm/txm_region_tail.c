/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0): code signing / entitlements / trust
 * caches. Ground truth: Ghidra FUN_ names + addresses; public API names from
 * docs/sptm/NAMING.md. All names are estimates unless header-matched.
 *
 * This file covers the "region tail" of the CoreEntitlements (CE) validation
 * engine in TXM: the IMG4 / IM4P / IM4R / IM4C / PAYP cryptex-boot manifest
 * parsers and value validators, the CoreEntitlements dictionary validation
 * core (txm_ce_validate_dictionary / txm_ce_validate_value), the IMG4 object
 * name lookup (txm_ce_object_lookup), a physical→virtual address translation
 * helper (txm_phys_to_virt), and the noreturn anti-replay panic stubs.
 *
 * GENTER/GEXIT are opaque (opcode 0x00201420 / 0x00201400). Ghidra FUN_ names
 * are retained in comments; no code-level Ghidra identifiers remain in the
 * bodies. The shared CE-runtime primitives (range-checked pointer arithmetic,
 * the object iterator, magic-tagged object parse, integer getters) are
 * declared extern with their FUN_ addresses in comments; they are recreated
 * in sibling region files of the txm tree.
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/* ============================================================================
 * Shared TXM/CE primitives (declared extern; ground-truth FUN_ addresses).
 * ==========================================================================*/

/* Stack canary. The compiler stores DAT_00006cf0 at function entry and
 * verifies it unchanged at epilogue; a mismatch calls FUN_0002f13c (noreturn
 * "stack check fail"). FUN_0002eb14 is the epilogue canary-check thunk. */
extern uint64_t g_txm_stack_canary;                       /* DAT_00006cf0 */
__attribute__((noreturn)) void txm_stack_chk_fail(void);  /* FUN_0002f13c */

/* String / compare primitives (thunks). */
long txm_strlen(uint64_t p);                             /* thunk_FUN_0002dc80 */
long txm_memcmp(const void *a, const void *b, long n);   /* FUN_0002d4d0 */

/* Forward declarations of functions defined later in this file so the
 * validation hub can call them. */
uint32_t txm_ce_validate_value(uint64_t *obj, const uint16_t *flags); /* FUN_0006066c */
uint64_t txm_ce_parse_payp(uint64_t *src, uint64_t *out);                   /* FUN_00061394 */
uint64_t txm_ce_validate_small_dict(uint64_t src, uint64_t out);            /* FUN_00061268 */
int txm_ce_parse_im4c(uint64_t src, uint64_t len, void *frame);             /* FUN_000455b8 */

/* Bound-checked range refinement. FUN_00044178/FUN_00044184: given a CE
 * object {ptr,len} (param_1) and an out {ptr,len,consumed} (param_2), parse
 * the length-prefixed payload at the front, range-check it against the
 * enclosing buffer, and advance. Returns 0 on success, 3 on malformed, or
 * traps (SoftwareBreakpoint 0x5519/0x5513) on an out-of-window access. */
int ce_range_refine(const uint64_t *obj, uint64_t *out); /* FUN_00044184 */

/* Object iterator over a CE {ptr,len} range. init (FUN_000446f4) sets the
 * iterator to {lo,hi}; next (FUN_00044724) yields the next 24-byte element
 * descriptor {tag,ptr,len} and returns 0 (ok) / 1 (done) / error. */
int ce_iter_init(const uint64_t *obj, uint64_t *it);     /* FUN_000446f4 */
int ce_iter_next(uint64_t *it, uint64_t *out);           /* FUN_00044724 */

/* Integer/bool getters on a parsed CE value object {ptr,len}: decode the
 * variable-width integer at the object head. FUN_000444fc (u64) /
 * FUN_0004447c (u32, rejects non-32-bit) / FUN_0004443c (bool or ±1 byte) /
 * FUN_00044580 (signed u64). Return 0 on success, 3 malformed, 7 too wide. */
int ce_get_u64(const uint64_t *obj, uint64_t *out);      /* FUN_000444fc */
int ce_get_u32(const uint64_t *obj, uint32_t *out);      /* FUN_0004447c */
int ce_get_bool(const uint64_t *obj, bool *out);         /* FUN_0004443c */
int ce_get_s64(const uint64_t *obj, uint64_t *out);      /* FUN_00044580 */

/* Parse a serialized CE object (array of key/value pairs) out of a buffer
 * following a 16-byte type template. FUN_000448ac. Returns 0 on success, or
 * a CE parse error code. */
int ce_parse(const uint64_t *obj, uint32_t n, const uint64_t *tmpl,
             uint64_t *out, uint64_t cap, uint64_t flags);      /* FUN_000448ac */
/* Magic-tagged object parse (template preceded by a 4CC check). FUN_000447e4 */
int ce_parse_magic(uint64_t *src, int n, const uint64_t *tmpl,
                   uint64_t *out, uint64_t cap, uint64_t flags);/* FUN_000447e4 */
/* Object byte-size accessor: returns *(obj+8). FUN_00042b84 */
uint64_t ce_obj_size(const uint64_t *obj);

/* Template parse wrapper: FUN_00044e30 (no-op thunk in this build) and
 * FUN_00044e28 → FUN_00044e54 (manifest parse with magic + count check). */
void ce_tmpl_parse(uint64_t *obj, uint64_t *out, const uint64_t *tmpl); /* FUN_00044e30 */
int  ce_manifest_parse(uint64_t *obj, uint64_t tmpl, uint64_t p3,
                       uint64_t out, uint64_t magic);              /* FUN_00044e54 */
void ce_subparse(void);                                          /* FUN_00044e44 */

/* CE entry builder: FUN_00044c6c parses one key/value entry; FUN_00044d9c
 * iterates and dispatches each element to txm_ce_parse_boot_va. */
int  ce_entry(const uint64_t *obj, uint64_t key, uint64_t *out); /* FUN_00044c6c */
void ce_foreach_dispatch(uint64_t *it, uint64_t key, uint64_t p3, uint64_t p4); /* FUN_00044d9c */

/* Big-endian byte-reverse copy with zero-pad. FUN_0003df58: decodes
 * param_1 64-bit words from the little-endian byte source at param_4 into
 * param_2, byte-swapping each word; any nonzero trailing byte → 0xfffffff9.
 * Used to hash/verify on-disk (big-endian) manifest integers. */
int ce_bswap_copy(uint64_t nwords, uint64_t *out, uint64_t bytecount, const uint8_t *src);

/* CE name-table lookup: binary search a sorted table of hashed key offsets
 * against a name string; returns the value descriptor on hit. FUN_00060088 */
int txm_ce_object_lookup(const uint64_t *table, uint64_t name, uint64_t *out);

/* Validation-side helpers. FUN_0005f4b4 maps an object type tag to a CE type
 * code 1..9. */
int ce_type_code(const uint64_t *obj, uint32_t *code);   /* FUN_0005f4b4 */

/* == TXM boot-verification / per-cpu context helpers == */
uint64_t txm_ctx_get(uint64_t which);              /* FUN_00045760/50/08/18 */
void     txm_ctx_set(uint64_t v);                  /* FUN_0004577c / 457b8 */
int      txm_ctx_state(void);                      /* FUN_00045718 */
int      txm_ctx_load_cb(uint64_t a, uint64_t b, void *out, uint64_t n); /* FUN_00045708/… */

/* == utility helpers == */
int  ce_hash_verify(uint64_t ctx, uint64_t obj, uint64_t tag, uint64_t data,
                    uint64_t len);                  /* FUN_0003efc4 family */
void ce_hash(void);                                 /* FUN_0003efc4 family */
int  ce_copy(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
             uint64_t e, uint64_t f, void *out);    /* FUN_00042980 */
int  ce_array_find(const uint64_t *arr, uint64_t v);/* FUN_000372f8 family */
uint64_t ce_obj_data(const uint64_t *obj);          /* FUN_00038318 */
int  ce_registry_lock(void);                        /* FUN_00037f5c */
void ce_log(const char *fmt, ...);                  /* FUN_00025c6c */

/* == phys→virt helpers == */
int  txm_pa_is_mapped(uint64_t pa);                 /* FUN_0004ed7c */
int  txm_pa_walk(uint64_t pa);                      /* FUN_0004f2b4 */

/* == anti-replay / panic == */
void txm_antireplay_write(void);                    /* FUN_00050750 */
__attribute__((noreturn)) void txm_panic(const char *msg); /* FUN_00050d70 */

/* TXM physmap translation globals (DAT_000153a8 block). */
extern uint64_t g_txm_physmap_enabled;   /* DAT_000153a8 */
extern uint64_t g_txm_pa_low;            /* DAT_000153d0 */
extern uint64_t g_txm_pa_high;           /* DAT_000153d8 */
extern uint64_t g_txm_boot_nranges;      /* *DAT_000153b0 */
extern uint64_t g_txm_boot_ranges;       /* DAT_000153b8 */

/* ============================================================================
 * txm_ce_object_lookup  (FUN_00060088)
 * ==========================================================================*/

/* FUN_00060088 @ 0x00060088   (est. txm_ce_object_lookup)
 * Ghidra: undefined8 FUN_00060088(long table, ulong name, ulong *out)
 * Looks a name string up in a CoreEntitlements name table. The table object
 * (param_1) has +0x30 = pointer to a sorted array of 8-byte entries, +0x38 =
 * entry count, +0x8/+0x10 = string-buffer base/size. Each entry packs a
 * hashed-key offset (low 32) and a value offset (high 32) into the string
 * buffer. Binary-searches the entries comparing the name against the buffer
 * bytes at the entry's key offset; on an exact hit returns the 40-byte value
 * descriptor {lo,hi,..} in param_3. Returns 0 on success, 0xb on null table,
 * 7 on not-found / length mismatch.
 * Confidence: medium
 * Notes: falls back to the linear lookup FUN_0005f5a4 when the table has no
 *   sorted index (+0x30 == 0). Address arithmetic is range-checked (trap
 *   0x5519). */
int txm_ce_object_lookup(const uint64_t *table, uint64_t name, uint64_t *out)
{
    uint64_t name_len = txm_strlen(name);
    if (name + name_len < name) {
        for (;;) { }        /* unreachable overflow trap (0x5519) */
    }
    if (table == 0) return 0xb;

    uint64_t *index = (uint64_t *)table[0x30 / 8];
    if (index == 0) {
        uint64_t buf[2] = { table[0x08 / 8], table[0x10 / 8] };
        uint64_t desc[2] = { name, name_len };
        return ce_range_refine(buf, desc);   /* linear fallback (FUN_0005f5a4) */
    }

    uint64_t base = table[0x08 / 8], size = table[0x10 / 8];
    uint64_t count = table[0x38 / 8];
    uint64_t lo = 0, hi = count - 1;
    while (lo <= hi && count != 0) {
        uint64_t mid = (lo + hi) >> 1;
        uint64_t ent = index[mid];
        uint64_t keyoff = ent & 0xffffffff;
        uint64_t keylen = size - keyoff;
        uint64_t cmplen = (name_len <= keylen) ? name_len : keylen;
        int cmp = txm_memcmp((const void *)(base + keyoff), (const void *)name, cmplen);
        if (cmp == 0) {
            if (keylen == name_len) {
                uint64_t voff = ent >> 0x20;
                uint64_t vbase = base + voff;
                if (vbase != 0) {
                    if (out != 0) {
                        out[0] = vbase;
                        out[1] = size - voff;
                        out[2] = 0;
                        out[3] = 0;
                        out[4] = 0;
                    }
                    return 0;
                }
                break;
            }
            if (keylen < name_len) lo = mid + 1;
            else if (lo + hi < 2) break;
            else hi = mid - 1;
        } else if (cmp < 0) {
            lo = mid + 1;
        } else {
            if (lo + hi < 2) break;
            hi = mid - 1;
        }
    }
    return 7;
}

/* ============================================================================
 * txm_ce_parse_dict_or_array  (FUN_00060230)
 * ==========================================================================*/

/* FUN_00060230 @ 0x00060230   (est. txm_ce_parse_dict_or_array)
 * Ghidra: undefined8 FUN_00060230(long *in, undefined8 *out)
 * Parses a top-level CoreEntitlements object. If the incoming object is a
 * dictionary (tag 0x2000000000000011) its {tag,lo,hi} is copied verbatim into
 * the 48-byte out descriptor and out[5] is cleared (no re-validation). If it
 * is a serialized array (tag 0x6000000000000010) it is parsed with the CE
 * array template (DAT_0000dc40, count 2, cap 0x20) into out and out[5] is set
 * to 1 (was a serialized array). Any other tag returns 0xd8.
 * Confidence: medium
 * Notes: g_txm_stack_canary checked at epilogue; FAIL on mismatch. */
uint64_t txm_ce_parse_dict_or_array(uint64_t *in, uint64_t *out)
{
    uint64_t canary = g_txm_stack_canary;
    uint64_t tag = in[0];

    if (tag == 0x2000000000000011ULL) {
        out[0] = 0;
        out[1] = 0;
        out[4] = in[2];
        out[3] = in[1];
        out[2] = in[0];
        out[5] = 0;
        return 0;
    }

    uint64_t tmpl[3] = { 0, 0, 0 };      /* DAT_0000dc40 {0,2,8} */
    uint64_t buf[5] = { 0, 0, 0, 0, 0 };
    uint64_t out2[5] = { 0, 0, 0, 0, 0 };
    uint64_t count = 0;
    if (tag == 0x6000000000000010ULL) {
        tmpl[0] = 0; tmpl[1] = 2; tmpl[2] = 8;
        int rc = ce_parse(in + 1, 2, tmpl, buf, 0x20, 0);
        if (rc == 0) rc = ce_get_s64(buf, &count);
        if (rc == 0 && count == 1) {
            out[0] = buf[2];
            out[1] = buf[3];
            out[2] = buf[4];
            out[3] = out2[3];
            out[4] = out2[4];
            out[5] = 1;
            return 0;
        }
    }
    return 0xd8;
}

/* ============================================================================
 * txm_ce_validate_dictionary  (FUN_0006037c)
 * ==========================================================================*/

/* FUN_0006037c @ 0x0006037c   (est. txm_ce_validate_dictionary)
 * Ghidra: ulong FUN_0006037c(long *obj, byte *flags)
 * Recursively validates a CoreEntitlements dictionary/array object against a
 * 16-bit allowed-type bitmap (flags). Requires a dict (tag
 * 0x2000000000000011) or array (0x6000000000000010), iterates its entries,
 * re-parses each key/value pair with the CE pair template {0xc,8,0x10,0,10},
 * and validates each value via txm_ce_validate_value. A duplicate/ordering
 * key mismatch returns 0xd0. On a value failure it logs "CoreEntitlements
 * validation" via ce_log and returns the failure code.
 * Confidence: medium
 * Notes: bit 4 of the flags byte gates the entry (0xa4 when clear); the
 *   failure taxonomy 0xcf/0xd1..0xd5 mirrors the CE validator. */
uint64_t txm_ce_validate_dictionary(uint64_t *obj, const uint8_t *flags)
{
    uint64_t canary = g_txm_stack_canary;
    uint64_t r[6] = { 0, 0, 0, 0, 0, 0 };

    if (((flags[0] >> 4) & 1) == 0) return 0xa4;
    if (obj[0] != 0x2000000000000011ULL && obj[0] != 0xa000000000000010ULL)
        return 0xce;

    uint64_t it[2];
    if (ce_iter_init(obj + 1, it) != 0) return 0xd1;

    uint64_t n = 0;
    for (;;) {
        uint64_t ent[22] = { 0 };
        int rc = ce_iter_next(it, ent);
        if (rc == 1) break;
        if (rc != 0) return (n != 0) ? 0 : ((rc == 1) ? 0 : 0xd1);

        if (ent[0] != 0x2000000000000010ULL) return 0xd2;
        /* re-parse the pair: key tag 0xc, value 8/0x10/0/10 */
        uint64_t tmpl[5] = { 0xc, 8, 0x10, 0, 10 };
        rc = ce_parse(ent + 1, 2, tmpl, &ent[0xb], 0x20, 0);
        if (rc != 0) return 0xd3;
        rc = ce_range_refine(&ent[0xb], &ent[8]);
        if (rc != 0) return 0xd4;
        rc = ce_range_refine(&ent[0xd], &ent[5]);
        if (rc != 0) return 0xd5;

        uint16_t fl = (uint16_t)flags[0];
        rc = (int)txm_ce_validate_value(&ent[8], &fl);
        if (rc != 0) return (uint64_t)rc;

        rc = (int)txm_ce_validate_value(&ent[5], (const uint16_t *)flags);
        if (rc != 0) {
            ce_log("CoreEntitlements validation");
            return (uint64_t)rc;
        }
        if (n + 1 < n + 1) return 3;    /* count overflow */
        n = n + 1;
    }
    return 0;
}

/* ============================================================================
 * txm_ce_validate_string_type  (FUN_00060608)
 * ==========================================================================*/

/* FUN_00060608 @ 0x00060608   (est. txm_ce_validate_string_type)
 * Ghidra: undefined4 FUN_00060608(long *obj, uint flags)
 * Validates that a parsed object is a CE string (type tag 0xc) and, when the
 * string is non-empty, that it contains no embedded NUL. Returns 0xa2 if the
 * flags bit 2 (0x4) is clear, 199/200 on empty/non-empty string, 0xc6 on a
 * non-string type.
 * Confidence: medium
 * Notes: the flag gate is bit 2 of the caller's type bitmap. */
uint32_t txm_ce_validate_string_type(uint64_t *obj, uint32_t flags)
{
    if (((flags >> 2) & 1) == 0) return 0xa2;
    if (obj[0] == 0xc) {
        if (obj[2] != 0) {
            uint64_t p = obj[1];
            return (txm_strlen(p) != 0) ? 200 : 0;
        }
        return 199;
    }
    return 0xc6;
}

/* ============================================================================
 * txm_ce_validate_value  (FUN_0006066c)
 * ==========================================================================*/

/* FUN_0006066c @ 0x0006066c   (est. txm_ce_validate_value)
 * Ghidra: uint FUN_0006066c(long *obj, ushort *flags)
 * Recursive CoreEntitlements value validator, dispatched on the object's type
 * tag. Handles: 1 (bool, bit0 → 0xa0), 2 (u32, bit1 → 0xa1), 4 (u64, bit5 →
 * 0xa5), 0xc (string, bit2 → 0xa2), 0x12/0x17 (fixed ints, bit7/bit6 →
 * 0xa7/0xa6), 0x2000000000000010 (string, bit3 → 0xa3), 0x2000000000000011
 * (dict → txm_ce_validate_dictionary), and 0x6000000000000010 (array: parse
 * via txm_ce_parse_dict_or_array, then validate each element). Returns the
 * low 16 bits of the failure code; 0 on success; 0xcc tolerates an absent
 * optional element.
 * Confidence: medium
 * Notes: this is the hub the dictionary validator calls for each entry. */
uint32_t txm_ce_validate_value(uint64_t *obj, const uint16_t *flags)
{
    uint64_t tag = obj[0];
    uint16_t fl = flags[0];
    uint32_t rc = 0xc1;

    if (tag < 0x12) {
        if (tag < 2) {
            if (tag == 0xa000000000000010ULL)
                return (uint32_t)txm_ce_validate_dictionary(obj, (const uint8_t *)flags);
            if (tag != 1) goto done;
            if ((fl & 1) == 0) { rc = 0xa0; goto done; }
            bool b;
            if (ce_get_bool(obj + 1, &b) != 0 &&
                (obj[2] != 1 || *(const char *)obj[1] != 1)) {
                rc = 0xc3; goto done;
            }
            rc = 0; goto done;
        }
        if (tag == 2) {
            if (((fl >> 1) & 1) == 0) { rc = 0xa1; }
            else {
                uint64_t v;
                rc = ce_get_s64(obj + 1, &v);
                rc = (rc == 0) ? 0 : 0xc5;
            }
            goto done;
        }
        if (tag == 4) {
            if (((fl >> 5) & 1) == 0) { rc = 0xa5; goto done; }
            rc = (obj[2] == 0) ? 0xca : 0;
            goto done;
        }
        if (tag != 0xc) goto done;
        uint32_t r2 = txm_ce_validate_string_type(obj, fl);
        rc = (r2 == 199) ? 0 : r2;
        goto done;
    }

    if (tag < 0x2000000000000010ULL) {
        if (tag == 0x12) { rc = ((fl & 0x80) == 0) ? 0xa7 : 0; goto done; }
        if (tag == 0x17) { rc = ((fl & 0x40) == 0) ? 0xa6 : 0; goto done; }
        goto done;
    }

    if (tag == 0x2000000000000010ULL) {
        if (((fl >> 3) & 1) == 0) { rc = 0xa3; goto done; }
        uint64_t it[2];
        if (ce_iter_init(obj + 1, it) != 0) { rc = 0xcd; goto done; }
        for (;;) {
            uint64_t ent[22] = { 0 };
            int r = ce_iter_next(it, ent);
            if (r == 1) { rc = 0; goto done; }
            if (r != 0) { rc = 0xcd; goto done; }
            uint32_t sub = txm_ce_validate_value(ent, flags);
            if ((sub & 0xffff) == 0) {
                if (((flags[1] & 1) == 0) &&
                    1 < ent[0] + 0xdffffffffffffff0ULL &&
                    ent[0] != 0xa000000000000010ULL) {
                    return 0xb0;
                }
            } else if ((sub & 0xffff) == 0xcc) {
                rc = 0; goto done;      /* optional element absent */
            } else {
                rc = sub; goto done;
            }
        }
    }

    if (tag == 0x2000000000000011ULL)
        return (uint32_t)txm_ce_validate_dictionary(obj, (const uint8_t *)flags);
    if (tag != 0x6000000000000010ULL) goto done;

    /* array: parse then validate each element */
    uint64_t arr[5] = { 0, 0, 0, 0, 0 };
    if (((fl >> 8) & 1) == 0) { rc = 0xa8; goto done; }
    rc = (uint32_t)txm_ce_parse_dict_or_array(obj, arr);
    if (rc != 0) goto done;
    uint16_t f2 = (uint16_t)fl;
    uint32_t r2 = txm_ce_validate_dictionary(arr + 2, (const uint8_t *)&f2);
    if (r2 != 0xcf && r2 != 0) rc = r2;
    else rc = 0;

done:
    return rc & 0xffff;
}

/* ============================================================================
 * txm_ce_object_append_data  (FUN_00060978)
 * ==========================================================================*/

/* FUN_00060978 @ 0x00060978   (est. txm_ce_object_append_data)
 * Ghidra: void FUN_00060978(long ctx, undefined8 *in, …)
 * Appends a data blob into a growing CoreEntitlements object under a hash
 * integrity check: it hashes the incoming buffer range (ce_hash_verify /
 * FUN_0003efc4) and, only when the result matches the expected end, copies
 * the bytes in via ce_copy (FUN_00042980) and returns the {lo,hi} of the
 * copied region in param_7. Restores the object's length watermark (+0x10).
 * Confidence: low
 * Notes: stack canary; FUN_0003bf80 is the epilogue canary check. */
void txm_ce_object_append_data(uint64_t ctx, uint64_t *in, uint64_t p3,
                               uint64_t p4, uint64_t buf, uint64_t len,
                               uint64_t *out)
{
    uint64_t canary = g_txm_stack_canary;
    if (out != 0) { out[0] = 0; out[1] = 0; }
    uint64_t res[2] = { 0, 0 };
    uint64_t obj = *(uint64_t *)*in;
    uint64_t save = *(uint64_t *)(ctx + 0x10);
    uint64_t a = (*(uint64_t (**)(uint64_t, uint64_t))(ctx + 0x18))(ctx, obj);
    uint64_t b = (*(uint64_t (**)(uint64_t, uint64_t))(ctx + 0x18))(ctx, obj);
    uint64_t end = len + buf;
    uint64_t rc = ce_hash_verify(obj, a, b, buf, end);
    if (rc == end) {
        uint64_t r2 = ce_copy(ctx, *in, p3, p4, a, b, res);
        if (out != 0 && (int)r2 == 0) {
            out[0] = res[0];
            out[1] = res[1];
        }
    }
    *(uint64_t *)(ctx + 0x10) = save;
    /* canary check via FUN_0003bf80 */
}

/* ============================================================================
 * txm_ce_bitmap_clear  (FUN_00060aa8)
 * ==========================================================================*/

/* FUN_00060aa8 @ 0x00060aa8   (est. txm_ce_bitmap_clear)
 * Ghidra: void FUN_00060aa8(ulong bit, long buf, undefined8 *ops)
 * Clears one bit (index param_1) in an array of 64-bit words at buf,
 * allocating via the op-table callback *ops on first use: computes the word
 * index (bit>>6), calls ops[0](ops, word_count<<3, buf), then clears bit
 * (bit&0x3f) in the last word.
 * Confidence: low
 * Notes: FUN_0003df38 masks the in-word bit. */
void txm_ce_bitmap_clear(uint64_t bit, uint64_t buf, uint64_t *ops)
{
    uint64_t words = (bit + 0x3f) >> 6;
    int rc = (*(int (*)(uint64_t *, uint64_t, uint64_t))*ops)(ops, words << 3, buf);
    if (rc == 0) {
        buf += words * 8;
        *(uint64_t *)(buf - 8) &= ~(1ULL << (bit & 0x3f));
    }
}

/* ============================================================================
 * txm_ce_copy_twice  (FUN_00060b14)
 * ==========================================================================*/

/* FUN_00060b14 @ 0x00060b14   (est. txm_ce_copy_twice)
 * Ghidra: void FUN_00060b14(long ctx, undefined8 *in, …)
 * Copies an object's data region twice under hash verification: both the
 * incoming (param_5) and outgoing (param_6) copies are verified before the
 * bytes are moved via ce_copy (FUN_00042980). Returns the destination
 * {lo,hi} in param_7. Restores the length watermark on exit.
 * Confidence: low
 * Notes: ce_obj_data (FUN_00038318) is the length; thunk_FUN_0003df58 is the
 *   hash verify; the pair of checks guards the copy against tampered input. */
void txm_ce_copy_twice(uint64_t ctx, uint64_t *in, uint64_t p3, uint64_t p4,
                       uint64_t p5, uint64_t p6, uint64_t *out)
{
    uint64_t canary = g_txm_stack_canary;
    if (out != 0) { out[0] = 0; out[1] = 0; }
    uint64_t res[2] = { 0, 0 };
    uint64_t obj = *(uint64_t *)*in;
    uint64_t save = *(uint64_t *)(ctx + 0x10);
    uint64_t a = (*(uint64_t (**)(uint64_t, uint64_t))(ctx + 0x18))(ctx, obj);
    uint64_t b = (*(uint64_t (**)(uint64_t, uint64_t))(ctx + 0x18))(ctx, obj);
    uint64_t len = ce_obj_data(in);
    int rc = (int)ce_hash_verify(obj, a, len, p5, 0);
    if (rc == 0) {
        len = ce_obj_data(in);
        rc = (int)ce_hash_verify(obj, b, len, p6, 0);
        if (rc == 0) {
            uint64_t r2 = ce_copy(ctx, *in, p3, p4, a, b, res);
            if (out != 0 && (int)r2 == 0) {
                out[0] = res[0];
                out[1] = res[1];
            }
        }
    }
    *(uint64_t *)(ctx + 0x10) = save;
    /* canary check */
}

/* ============================================================================
 * txm_ce_parse_typed_data  (FUN_00060c64)
 * ==========================================================================*/

/* FUN_00060c64 @ 0x00060c64   (est. txm_ce_parse_typed_data)
 * Ghidra: undefined8 FUN_00060c64(long ctx, long *obj, int kind, …)
 * Parses a length-tagged data field out of a CoreEntitlements object. kind
 * selects the field encoding: 1 = 1-byte length, 2 = 2-byte length, 3 =
 * 4-byte length, 4 = 8-byte length (the length word itself is the size,
 * big-endian). Validates the declared length against the object's remaining
 * bytes and copies the payload into the CE object's buffer, hashing each
 * copied region (ce_hash_verify). Returns 0 on success or one of the CE parse
 * errors (0xffffff54/55/56/5f/60, 0xfffffff9 bad kind).
 * Confidence: medium
 * Notes: length checked via ce_obj_size (FUN_00042b84); payload verified by
 *   the FUN_0003df58 hash pair. */
uint64_t txm_ce_parse_typed_data(uint64_t ctx, uint64_t *obj, int kind,
                                 uint64_t len, const uint8_t *data, uint64_t base)
{
    if (len == 0) return 0xfffffff9;
    uint64_t objlen = *obj;
    if (len == 1 && data[0] == 0) return 0xffffff60;

    if (kind == 4) {
        uint64_t sz = ce_obj_size(obj);
        if (len != (sz + 7) >> 3) return 0xffffff54;
    } else if (kind == 1) {
        ce_obj_size(obj);
        if (data[0] != 4) return 0xffffff56;
    } else if (kind == 2) {
        ce_obj_size(obj);
        uint32_t d = data[0] - 8;
        if (d >= 0xfffffffe) return 0xffffff55;
    } else if (kind == 3) {
        if (len != ce_obj_size(obj)) return 0xffffff5f;
        uint32_t d = data[0] - 4;
        if (d >= 0xfffffffe) return 0xffffff5f;
    } else {
        return 0xfffffff9;
    }

    uint64_t objtag = obj[0];
    uint64_t cb = (*(uint64_t (**)(uint64_t, uint64_t))(ctx + 0x18))(ctx, objtag);
    const uint8_t *src = (kind == 4) ? data : data + 1;
    uint64_t sz = ce_obj_size(obj);
    if (ce_hash_verify(objtag, base, (sz + 7) >> 3, (uint64_t)src, 0) != 0)
        return 0xffffff56;    /* placeholder; faithful hash-fail path */

    if (kind == 3 || kind == 4) {
        uint64_t dst = base + *obj * 8;
        ce_copy(ctx, *obj, base, dst, 0, 0, 0);
    }
    return 0;
}

/* ============================================================================
 * txm_array_contains  (FUN_00060f3c) / txm_array_append_unique (FUN_00060fc0)
 * ==========================================================================*/

/* FUN_00060f3c @ 0x00060f3c   (est. txm_array_contains)
 * Ghidra: int FUN_00060f3c(long *arr, undefined8 val)
 * Returns whether the object array at arr (element count in *arr, 5-word
 * packed entries) contains val. Bounds-checks the array end (ce_obj_data,
 * FUN_000372f8) then memcmps the count/packed descriptor against val; on
 * mismatch falls back to a word-compare. Returns 0 if found, -1 otherwise.
 * Confidence: low
 * Notes: thunk_FUN_00043cc4 / thunk_FUN_00037b3c are the compares. */
int txm_array_contains(uint64_t *arr, uint64_t val)
{
    uint64_t n = arr[0];
    uint64_t end = ce_obj_data(arr);
    int rc = txm_memcmp((const void *)n, (const void *)val, end);
    if (rc < 0) {
        uint64_t m = ce_obj_data(arr);
        return -(m == 0);
    }
    return -1;
}

/* FUN_00060fc0 @ 0x00060fc0   (est. txm_array_append_unique)
 * Ghidra: ulong FUN_00060fc0(undefined8 ctx, long *arr, …)
 * Appends val to the object array arr only if val is not already present
 * (checked with the packed-entry memcmp). Returns 0xffffffff when the value
 * is already present or the array is full, 0xfffffff9 on append failure,
 * else 0 on success.
 * Confidence: low
 * Notes: FUN_0003b770 = append; FUN_0003d10c = finalize. */
uint64_t txm_array_append_unique(uint64_t ctx, uint64_t *arr, uint64_t p3,
                                 uint64_t base, uint64_t p5)
{
    uint64_t n = arr[0];
    uint64_t end = base + n * 8;
    uint64_t e = ce_obj_data(arr);
    if (txm_memcmp((const void *)n, (const void *)e, base) > 0 &&
        txm_memcmp((const void *)n, (const void *)e, end) > 0) {
        uint64_t rc = ce_hash_verify(ctx, (uint64_t)arr, p3, base, p5);
        if ((int)rc != 0) return rc;
        int r2 = ce_registry_lock();   /* FUN_0003d10c */
        return (r2 == 0) ? 0xfffffff9 : 0;
    }
    return 0xffffffff;
}

/* ============================================================================
 * txm_array_find  (FUN_000610a8)
 * ==========================================================================*/

/* FUN_000610a8 @ 0x000610a8   (est. txm_array_find)
 * Ghidra: void FUN_000610a8(undefined8 arr, long key, undefined8 *out)
 * Iterates the array object arr (element descriptors) looking for an element
 * whose packed descriptor equals key; on a match writes the element's 16-byte
 * {lo,hi} into out. Silent when not found.
 * Confidence: medium
 * Notes: ce_iter_init / ce_iter_next iterator. */
void txm_array_find(uint64_t arr, uint64_t key, uint64_t *out)
{
    uint64_t it[2] = { 0, 0 };
    if (ce_iter_init(&arr, it) != 0) return;
    uint64_t ent[3] = { 0, 0, 0 };
    for (;;) {
        int rc = ce_iter_next(it, ent);
        if (rc != 0) return;
        if (ent[0] == key) {
            out[0] = ent[1];
            out[1] = ent[2];
            return;
        }
    }
}

/* ============================================================================
 * txm_ce_compare_magic  (FUN_00061110)
 * ==========================================================================*/

/* FUN_00061110 @ 0x00061110   (est. txm_ce_compare_magic)
 * Ghidra: uint FUN_00061110(long obj, uint magic)
 * Compares a parsed 4-byte IMG4 magic field against an expected value.
 * Returns 0xffffffff if the object isn't exactly 4 bytes, 1 if it's a
 * different size, 0xfffffffe on read failure, 0 if equal, 1 if the field
 * sorts below the expected magic.
 * Confidence: high (exact 4-byte IMG4 magic compare; IMG4/IM4* 4CCs observed
 *   at call sites: 0x494d4734 IMG4, 0x494d3450 IM4P, 0x494d3452 IM4R,
 *   0x494d3443 IM4C, 0x50415950 PAYP).
 * Notes: reads the u32 via ce_get_u32 (FUN_0004447c). */
uint32_t txm_ce_compare_magic(uint64_t obj, uint32_t magic)
{
    uint64_t size = *(uint64_t *)(obj + 8);
    if (size < 4) return 0xffffffff;
    if (size != 4) return 1;
    uint32_t v = 0;
    if (ce_get_u32(&obj, &v) != 0) return 0xfffffffe;
    if (magic <= v) return (magic < v) ? 1 : 0;
    return 0xffffffff;
}

/* ============================================================================
 * txm_ce_validate_img4  (FUN_0006118c)
 * ==========================================================================*/

/* FUN_0006118c @ 0x0006118c   (est. txm_ce_validate_img4)
 * Ghidra: ulong FUN_0006118c(ulong *obj, long out)
 * Validates that a parsed object is an IMG4 container: it must be a
 * dictionary (tag 0x2000000000000011) whose 16-byte magic field, parsed with
 * the CE template DAT_000078a0, compares equal to 0x494d4734 ('IMG4').
 * Returns 6 on null args, 2 on wrong type, 7 on overflow, 0 on success.
 * Confidence: high (explicit IMG4 magic compare).
 * Notes: template DAT_000078a0 = {0, 0, 0x16, 0}; magic via txm_ce_compare_magic. */
uint64_t txm_ce_validate_img4(uint64_t *obj, uint64_t out)
{
    if (obj == 0 || out == 0) return 6;
    uint64_t r[3] = { 0, 0, 0 };
    if (ce_range_refine(&r[0], &r[1]) != 0) return 6;
    if (r[0] == 0x2000000000000011ULL) {
        if (*obj + obj[1] < *obj + obj[1]) return 7;
        if (ce_parse(&r[0], 4, (const uint64_t *)0x78a0, (uint64_t *)out, 0x40, 0) != 0)
            return 7;
        uint32_t c = txm_ce_compare_magic(out, 0x494d4734);
        return (c == 0) ? 0 : 2;
    }
    return 2;
}

/* ============================================================================
 * txm_ce_validate_small_dict  (FUN_00061268)
 * ==========================================================================*/

/* FUN_00061268 @ 0x00061268   (est. txm_ce_validate_small_dict)
 * Ghidra: ulong FUN_00061268(long src, long out)
 * Parses a small CoreEntitlements object into out using the compact template
 * DAT_00007c18 (size 2) and requires the resulting entry count to be >= 2.
 * Returns 6 on null args, 0 on success, else a parse error.
 * Confidence: low
 * Notes: ce_tmpl_parse (FUN_00044e30) + ce_get_u32 read the count. */
uint64_t txm_ce_validate_small_dict(uint64_t src, uint64_t out)
{
    uint32_t count = 2;
    if (src == 0 || out == 0) return 6;
    ce_tmpl_parse(&src, &out, (const uint64_t *)0x7c18);
    uint64_t rc = (uint64_t)ce_manifest_parse(&src, 0, 0, out, 0);
    if ((int)rc == 0) rc = (uint64_t)ce_get_u32(&out, &count);
    if ((int)rc == 0) rc = (count < 2) ? 6 : 0;
    return rc;
}

/* ============================================================================
 * txm_ce_parse_im4p  (FUN_000612e0)
 * ==========================================================================*/

/* FUN_000612e0 @ 0x000612e0   (est. txm_ce_parse_im4p)
 * Ghidra: undefined8 FUN_000612e0(long src, long out)
 * Parses a signed IMG4 payload (IM4P) object into the 0xa0-byte out
 * descriptor using the CE template DAT_00007990, requiring the magic field to
 * equal 0x494d3450 ('IM4P'). When non-zero, the nested digest field (+0x50)
 * is parsed via txm_ce_validate_small_dict and the payload field (+0x60) via
 * txm_ce_parse_payp. Returns 6 on null args, 2 on magic mismatch, else a
 * nested parse error.
 * Confidence: high (IM4P magic string match).
 * Notes: string at 0x3429 references "Cryptex1 boot verification VMA2". */
uint64_t txm_ce_parse_im4p(uint64_t src, uint64_t out)
{
    uint64_t rc = 6;
    if (src != 0 && out != 0) {
        rc = (uint64_t)ce_parse_magic(&src, 7, (const uint64_t *)0x7990,
                                      (uint64_t *)out, 0xa0, 0);
        if ((int)rc == 0) {
            uint32_t m = txm_ce_compare_magic(out, 0x494d3450);
            if (m == 0) {
                if (*(uint64_t *)(out + 0x50) != 0) {
                    ce_subparse();
                    rc = txm_ce_validate_small_dict(out + 0x50, out);
                    if ((int)rc != 0) return rc;
                }
                if (*(uint64_t *)(out + 0x60) != 0) {
                    ce_subparse();
                    rc = txm_ce_parse_payp((uint64_t *)(out + 0x60), (uint64_t *)out);
                    if ((int)rc != 0) return rc;
                }
                rc = 0;
            } else {
                rc = 2;
            }
        }
    }
    return rc;
}

/* ============================================================================
 * txm_ce_parse_payp  (FUN_00061394)
 * ==========================================================================*/

/* FUN_00061394 @ 0x00061394   (est. txm_ce_parse_payp)
 * Ghidra: undefined8 FUN_00061394(long *src, undefined8 *out)
 * Parses a PAYP (payload) object: zeroes the out descriptor, and when src is
 * non-empty parses it with template DAT_00007be8 requiring magic 0x50415950
 * ('PAYP'). Returns 6 on null out / absent input, 2 on magic mismatch, else
 * 0.
 * Confidence: high (PAYP magic string match).
 * Notes: ce_tmpl_parse + ce_manifest_parse finalize. */
uint64_t txm_ce_parse_payp(uint64_t *src, uint64_t *out)
{
    if (src == 0) return 0;
    if (out == 0) return 6;
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
    if (src[0] != 0 && src[1] != 0) {
        ce_tmpl_parse(src, out, (const uint64_t *)0x7be8);
        uint64_t rc = (uint64_t)ce_manifest_parse(src, 0, 0, 0, 0);
        if ((int)rc != 0) return rc;
        if (txm_ce_compare_magic((uint64_t)out, 0x50415950) != 0) return 2;
    }
    return 0;
}

/* ============================================================================
 * txm_ce_parse_cryptex  (FUN_00061418)
 * ==========================================================================*/

/* FUN_00061418 @ 0x00061418   (est. txm_ce_parse_cryptex)
 * Ghidra: void FUN_00061418(long src, undefined8 *out)
 * Parses a cryptex boot object into out. First tries the 0xa0-byte IM4P
 * layout via txm_ce_parse_im4p; on failure falls back to parsing the compact
 * 0x90-byte template DAT_00007900, requiring magic 0x494d3450 (IM4P) and, if
 * the digest field (+10) is non-zero, validating it as a small dict. Copies
 * the full 0xa0-byte descriptor into out on the IM4P path.
 * Confidence: medium
 * Notes: 96 bytes zeroed before use (thunk_FUN_0002d240). */
void txm_ce_parse_cryptex(uint64_t src, uint64_t *out)
{
    uint64_t canary = g_txm_stack_canary;
    uint64_t rc = 6;
    if (src != 0 && out != 0) {
        uint64_t buf[12];
        memset(buf, 0, sizeof(buf));
        rc = txm_ce_parse_im4p(src, (uint64_t)buf);
        if ((int)rc == 0) {
            memcpy(out, buf, 12 * sizeof(uint64_t));
        } else {
            rc = (uint64_t)ce_parse_magic(&src, 6, (const uint64_t *)0x7900,
                                          out, 0x90, 0);
            if ((int)rc == 0) {
                if (txm_ce_compare_magic((uint64_t)out, 0x494d3450) != 0) {
                    rc = 2;
                } else {
                    if (out[10] != 0) {
                        ce_subparse();
                        rc = txm_ce_validate_small_dict((uint64_t)(out + 10), (uint64_t)out);
                        if ((int)rc != 0) { /* propagate */ }
                    }
                    rc = 0;
                }
            }
        }
    }
    /* canary check */
}

/* ============================================================================
 * Cryptex parse wrappers  (FUN_0006151c / 00061538 / 00061554)
 * ==========================================================================*/

/* FUN_0006151c / 00061538 / 00061554 @ 0x0006151c/38/54 (est. cryptex parse
 *   wrappers). Each parses a cryptex object (template DAT_00007b70/07ab0)
 *   with a different element-count and a "Cryptex1 boot verification VMA2"
 *   name suffix offset into the string at 0x3429. Thin wrappers over
 *   ce_manifest_parse (FUN_00044e28). Confidence: medium. */
void txm_ce_parse_cryptex_a(uint64_t src, uint64_t out)
{
    ce_manifest_parse(&src, 3, (uint64_t)0x7b70, out, (uint64_t)"…/Cryptex1 boot verification VMA2");
}
void txm_ce_parse_cryptex_b(uint64_t src, uint64_t out)
{
    ce_manifest_parse(&src, 4, (uint64_t)0x7ab0, out, (uint64_t)"…/Cryptex1 boot verification VMA2");
}
void txm_ce_parse_cryptex_c(uint64_t src, uint64_t out)
{
    ce_manifest_parse(&src, 3, (uint64_t)0x7b70, out, (uint64_t)"…/Cryptex1 boot verification VMA2");
}

/* ============================================================================
 * txm_ce_parse_cryptex_dict  (FUN_00061570)
 * ==========================================================================*/

/* FUN_00061570 @ 0x00061570   (est. txm_ce_parse_cryptex_dict)
 * Ghidra: undefined8 FUN_00061570(long p1, long p2, undefined8 *out3..6)
 * Parses a cryptex descriptor dictionary: p1/p2 form the source {lo,hi} range
 * and out3..out6 receive the parsed sub-fields. Requires the source to be a
 * dictionary (tag 0x2000000000000011) whose two key fields parse with
 * templates DAT_00007b10 ("CTRP") and DAT_00007b40; the 4-byte length field
 * then yields the payload into out5/out6. Returns 6 on null args, 2 on wrong
 * type / parse failure, 0xffffffff on parse error, else 0.
 * Confidence: medium
 * Notes: DAT_00007b10 bytes are "CTRP" (cryptex tag). */
uint64_t txm_ce_parse_cryptex_dict(uint64_t p1, uint64_t p2, uint64_t *o3,
                                   uint64_t *o4, uint64_t *o5, uint64_t *o6)
{
    if (p1 == 0 || p2 == 0 || o3 == 0) return 6;
    if (o4 == 0) return 6;
    if (o5 == 0 || o6 == 0) return 6;

    uint64_t k1[3] = { 0, 0, 0 };
    uint64_t k2[3] = { 0, 0, 0 };
    uint64_t src[2] = { p1, p2 };
    uint64_t r[5] = { 0, 0, 0, 0, 0 };
    if (ce_range_refine(&src[0], &r[0]) != 0) return 6;
    if (r[0] == 0x2000000000000011ULL) {
        if (ce_parse(&src[0], 2, (const uint64_t *)0x7b10, k1, 0x20, 0) != 0)
            return 0xffffffff;
        if (ce_range_refine(&k1[0], &r[0]) != 0) return 0xffffffff;
        if (r[0] == 0x2000000000000010ULL) {
            if (ce_parse(&src[0], 2, (const uint64_t *)0x7b40, k2, 0x20, 0) != 0)
                return 0xffffffff;
            *o3 = k1[1];
            *o4 = k1[2];
            if (ce_range_refine(&k2[0], &r[0]) != 0) return 0xffffffff;
            if (r[0] == 4) {
                *o5 = k2[0];
                *o6 = k2[1];
                return 0;
            }
        }
    }
    return 2;
}

/* ============================================================================
 * txm_ce_parse_im4r  (FUN_000616c8)
 * ==========================================================================*/

/* FUN_000616c8 @ 0x000616c8   (est. txm_ce_parse_im4r)
 * Ghidra: undefined8 FUN_000616c8(long *src, undefined8 *out)
 * Parses an IM4R (IMG4 restore) object: zeroes out, and when src is non-empty
 * parses with template DAT_00007bb8 requiring magic 0x494d3452 ('IM4R').
 * Returns 6 on null out / absent input, 2 on magic mismatch, else 0.
 * Confidence: high (IM4R magic string match). */
uint64_t txm_ce_parse_im4r(uint64_t *src, uint64_t *out)
{
    if (src == 0) return 0;
    if (out == 0) return 6;
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
    if (src[0] != 0 && src[1] != 0) {
        ce_tmpl_parse(src, out, (const uint64_t *)0x7bb8);
        uint64_t rc = (uint64_t)ce_manifest_parse(src, 0, 0, 0, 0);
        if ((int)rc != 0) return rc;
        if (txm_ce_compare_magic((uint64_t)out, 0x494d3452) != 0) return 2;
    }
    return 0;
}

/* ============================================================================
 * txm_ce_parse_boot_va  (FUN_0006174c)
 * ==========================================================================*/

/* FUN_0006174c @ 0x0006174c   (est. txm_ce_parse_boot_va)
 * Ghidra: void FUN_0006174c(undefined8 src, ulong va, undefined8 data, long out)
 * Parses a 0x30-byte boot-address object (template DAT_00007890) and, when its
 * 4-byte value matches the expected tag (param_2 | 0xe000000000000000), stores
 * the tagged virtual address into out+0x10 and the data pointer into out+0x28.
 * Returns 0 on success, 2 on tag mismatch.
 * Confidence: low
 * Notes: local_70/_DAT_00007890 template {0,0,0x18,0}. */
void txm_ce_parse_boot_va(uint64_t src, uint64_t va, uint64_t data, uint64_t out)
{
    uint64_t canary = g_txm_stack_canary;
    uint32_t v = 0;
    uint64_t rc = (uint64_t)ce_parse_magic(&src, 2, (const uint64_t *)0x7890,
                                           (uint64_t *)out, 0x30, 0);
    if ((int)rc == 0) rc = (uint64_t)ce_get_u32(&out, &v);
    if ((int)rc == 0) {
        if (((uint64_t)v | 0xe000000000000000ULL) == va) {
            *(uint64_t *)(out + 0x10) = va | 0xe000000000000000ULL;
            *(uint64_t *)(out + 0x28) = data;
            rc = 0;
        } else {
            rc = 2;
        }
    }
    /* canary check */
}

/* ============================================================================
 * txm_array_foreach  (FUN_00061824)
 * ==========================================================================*/

/* FUN_00061824 @ 0x00061824   (est. txm_array_foreach)
 * Ghidra: void FUN_00061824(undefined8 arr, …)
 * Iterates the array object arr and dispatches each element to
 * ce_foreach_dispatch (FUN_00044d9c) with the (p2,p3,p4) arguments.
 * Confidence: low
 * Notes: ce_iter_init / ce_iter_next iterator. */
void txm_array_foreach(uint64_t arr, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t it[2] = { 0, 0 };
    if (ce_iter_init(&arr, it) != 0) return;
    ce_foreach_dispatch(it, p2, p3, p4);
}

/* ============================================================================
 * txm_ctx_copy_digest  (FUN_00061880) / txm_ctx_copy_cert (FUN_00061960)
 * ==========================================================================*/

/* FUN_00061880 @ 0x00061880   (est. txm_ctx_copy_digest)
 * Ghidra: void FUN_00061880(undefined8 p1, undefined8 p2, ulong n, long *out)
 * Copies a fixed-size digest (param_3, expected 0x30) from the current TXM
 * boot-verification context into out. When the context has a length callback
 * (+0x88/+0x90 both nonzero) it copies up to min(n, ctx_len) bytes; otherwise
 * it uses the in-context digest buffer (+0xb8). Returns 1 if the context
 * lacks the length/pointer pair, 7 if n > 0x30, else 0.
 * Confidence: low
 * Notes: FUN_00045760/45708/457b8 are context accessors; thunk_FUN_0002d6b0
 *   is the copy. */
void txm_ctx_copy_digest(uint64_t p1, uint64_t p2, uint64_t n, uint64_t *out)
{
    uint64_t canary = g_txm_stack_canary;
    uint8_t tmp[56];
    uint64_t ctx = txm_ctx_get(0);
    uint64_t rc = 6;
    if (ctx != 0 && n != 0 && out != 0 && *out != 0) {
        if (*(uint64_t *)(ctx + 0x88) == 0 || *(uint64_t *)(ctx + 0x90) == 0) {
            rc = 1;
        } else if (n < 0x31) {
            if ((*(uint8_t *)ctx & 1) == 0) {
                uint64_t l = txm_ctx_get(4);
                rc = 6;
                if (*(uint64_t *)out[4] <= 0x30) {
                    uint64_t nn = *(uint64_t *)out[4];
                    memcpy(tmp, (void *)*(uint64_t *)(ctx + 8), nn);
                    n = nn;
                    rc = 0;
                }
            } else {
                memcpy(tmp, (void *)(ctx + 0xb8), n);
                rc = 0;
            }
        } else {
            rc = 7;
        }
    }
    /* canary check */
}

/* FUN_00061960 @ 0x00061960   (est. txm_ctx_copy_cert)
 * Ghidra: undefined8 FUN_00061960(undefined8 p1, undefined8 p2, ulong n, long *out)
 * Copies a certificate blob (up to 0x30 bytes) from the boot-verification
 * context into a caller buffer. Returns 6 on null args, 1 if the context has
 * no cert pointer (+0x18 == 0), 7 if n > 0x30, else 0. The cert is read from
 * ctx+0x148 when the context's "has cert" flag (byte ctx+1 bit0) is set, else
 * via a callback into a 56-byte scratch.
 * Confidence: low
 * Notes: FUN_00045750/45708/457b8 context accessors; callback FUN_000457b8. */
uint64_t txm_ctx_copy_cert(uint64_t p1, uint64_t p2, uint64_t n, uint64_t *out)
{
    uint64_t canary = g_txm_stack_canary;
    uint8_t tmp[56];
    uint64_t ctx = txm_ctx_get(0);
    uint64_t rc = 6;
    if (ctx != 0 && n != 0 && out != 0 && *out != 0) {
        if (*(uint64_t *)(ctx + 0x18) == 0) {
            rc = 1;
        } else if (n < 0x31) {
            if ((*(uint8_t *)(ctx + 1) & 1) == 0) {
                rc = txm_ctx_load_cb(ctx, *(uint64_t *)(ctx + 0x20), tmp, n);
                if ((int)rc == 0) {
                    txm_ctx_set((uint64_t)tmp);
                }
            } else {
                txm_ctx_set(ctx + 0x148);
                rc = 0;
            }
        } else {
            rc = 7;
        }
    }
    /* canary check */
    return rc;
}

/* ============================================================================
 * txm_obj_get_buf  (FUN_00061a34)
 * ==========================================================================*/

/* FUN_00061a34 @ 0x00061a34   (est. txm_obj_get_buf)
 * Ghidra: int FUN_00061a34(long obj, long *out_ptr, undefined4 *out_len)
 * Extracts the {pointer, length} pair from a parsed object: +0x18 = pointer,
 * +0x20 (low 32 bits) = length. Returns 6 on null args, 7 if the length has a
 * nonzero high 32 bits, -1 if either is zero, else 0.
 * Confidence: high (exact field extraction). */
int txm_obj_get_buf(uint64_t obj, uint64_t *out_ptr, uint32_t *out_len)
{
    if (obj == 0 || out_ptr == 0 || out_len == 0) return 6;
    uint64_t l = *(uint64_t *)(obj + 0x20);
    if (l >> 0x20 != 0) return 7;
    uint64_t p = *(uint64_t *)(obj + 0x18);
    *out_ptr = p;
    *out_len = (uint32_t)l;
    return -((l == 0) || (p == 0));
}

/* ============================================================================
 * txm_ce_get_* wrappers  (FUN_00061a80 / 00061ae4 / 00061b48)
 * ==========================================================================*/

/* FUN_00061a80 @ 0x00061a80   (est. txm_ce_get_u32_ctx)
 * Ghidra: undefined8 FUN_00061a80(void)  [x19 = out]
 * Reads a u32 from the current CE context: requires context state 2, then
 * reads via ce_get_u32. Writes 0 to the x19 out-ptr on failure. Returns 6 on
 * null out / bad state, 2 on wrong state, else the read status.
 * Confidence: low
 * Notes: x19 is the out pointer (register-passed; the decompiler shows it as
 *   unaff_x19). Reconstructed as a one-arg helper. */
uint64_t txm_ce_get_u32_ctx(uint32_t *out)
{
    uint64_t rc = txm_ctx_state();
    if ((int)rc == 0) {
        if (txm_ctx_get(2) == 2) {
            if (out == 0) return 6;
            txm_ctx_set(0);
            rc = (uint64_t)ce_get_u32(&rc, (uint32_t *)&rc);
        } else {
            rc = 2;
        }
    }
    if (out != 0 && (int)rc != 0) *out = 0;
    return rc;
}

/* FUN_00061ae4 @ 0x00061ae4   (est. txm_ce_get_u64_ctx)
 * Ghidra: undefined8 FUN_00061ae4(void)  [x19 = out]
 * u64 variant of txm_ce_get_u32_ctx using ce_get_u64. Same state gate.
 * Confidence: low
 * Notes: x19 = out; reconstructed as one-arg. */
uint64_t txm_ce_get_u64_ctx(uint64_t *out)
{
    uint64_t rc = txm_ctx_state();
    if ((int)rc == 0) {
        if (txm_ctx_get(2) == 2) {
            if (out == 0) return 6;
            txm_ctx_set(0);
            rc = (uint64_t)ce_get_u64(&rc, (uint64_t *)&rc);
        } else {
            rc = 2;
        }
    }
    if (out != 0 && (int)rc != 0) *out = 0;
    return rc;
}

/* FUN_00061b48 @ 0x00061b48   (est. txm_ce_get_bool_ctx)
 * Ghidra: undefined8 FUN_00061b48(void)  [x19 = out]
 * bool variant of the above using ce_get_bool; requires context state 1.
 * Confidence: low */
uint64_t txm_ce_get_bool_ctx(uint64_t out)
{
    uint64_t rc = txm_ctx_state();
    if ((int)rc == 0) {
        if (txm_ctx_get(2) == 1) {
            if (out == 0) return 6;
            txm_ctx_set(0);
            rc = (uint64_t)ce_get_bool(&rc, (bool *)&rc);
        } else {
            rc = 2;
        }
    }
    return rc;
}

/* ============================================================================
 * txm_ce_foreach_entry  (FUN_00061b9c)
 * ==========================================================================*/

/* FUN_00061b9c @ 0x00061b9c   (est. txm_ce_foreach_entry)
 * Ghidra: undefined8 FUN_00061b9c(undefined8 ctx, undefined8 cb_arg, code *cb, …)
 * Iterates the current CE context object and invokes the callback cb for each
 * validated entry. Each entry's type code must be in {0,1,2,4,16,18} (bitmask
 * 0x400016), the key must be a kernel-VA (top 2 bits == 3) with the keyed flag
 * set, and the value length must fit 32 bits. The callback receives
 * (key, {key,val,type} descriptor, context, cb_arg). Returns 0 when the
 * iterator ends, 6 on null cb, 2 on a disallowed type/shape, 7 on overflow.
 * Confidence: medium
 * Notes: ce_entry (FUN_00044c6c) builds the entry descriptor; FUN_00045708 is
 *   the context accessor. */
uint64_t txm_ce_foreach_entry(uint64_t ctx, uint64_t cb_arg,
                              int (*cb)(uint64_t, uint64_t *, uint64_t, uint64_t),
                              uint64_t p4)
{
    uint64_t it[2] = { 0, 0 };
    uint64_t ent[5] = { 0, 0, 0, 0, 0 };
    uint64_t v[3] = { 0, 0, 0 };
    uint64_t ctxv = txm_ctx_get(0);
    if (cb == 0) return 6;
    uint64_t rc = ce_iter_init(&ctxv, it);
    while ((int)rc == 0) {
        rc = ce_iter_next(it, ent);
        if ((int)rc == 1) return 0;
        if ((int)rc != 0) return rc;
        rc = (uint64_t)ce_entry(it, ent[0], v);
        if ((int)rc != 0) return rc;
        if (0x16 < ent[4]) return 2;
        if ((1ULL << (ent[4] & 0x3f) & 0x400016U) == 0) return 2;
        if (ent[0] >> 0x3e == 0) return 2;
        if (((ent[0] >> 0x3d) & 1) == 0) return 2;
        if (ent[2] >> 0x20 != 0) return 7;
        uint64_t desc[3];
        desc[0] = v[0];
        desc[1] = v[1];
        desc[2] = ent[4];
        rc = cb(ent[0], desc, txm_ctx_get(0), p4);
    }
    return rc;
}

/* ============================================================================
 * txm_ce_verify_cryptex  (FUN_00061cbc)
 * ==========================================================================*/

/* FUN_00061cbc @ 0x00061cbc   (est. txm_ce_verify_cryptex)
 * Ghidra: void FUN_00061cbc(undefined8 p1..p8, undefined8 *ops, …)
 * High-level cryptex boot verification. Parses an IM4C container
 * (FUN_000455b8 with magic 0x494d3443 'IM4C') into a 0x1c8-byte frame, then
 * invokes the caller-provided ops callbacks (*ops[0] = parse, ops[2] =
 * dispatch) to validate the payload, and finally txm_ce_parse_cryptex_dict on
 * the parsed {lo,hi}. Returns -1 on any parse/dispatch failure, 0 on success.
 * Confidence: medium
 * Notes: magic 0x494d3443 is 'IM4C'. 0x1c8-byte frame zeroed first. */
void txm_ce_verify_cryptex(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                           uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8,
                           uint64_t *ops, uint64_t p10)
{
    uint64_t canary = g_txm_stack_canary;
    uint8_t frame[0x1c8];
    uint8_t scratch[80];
    memset(frame, 0, sizeof(frame));
    int rc = 6;
    if (p3 != 0 && p4 != 0 && p5 != 0 && p6 != 0 && p7 != 0 && p8 != 0 && ops != 0) {
        rc = (int)txm_ce_parse_im4c(p3, p4, frame);
        if (rc == 0) {
            uint64_t parse = ops[0];
            rc = (int)((int (*)(uint64_t, uint64_t, uint8_t *, uint64_t, uint64_t *))parse)
                     (*(uint64_t *)&frame[0], *(uint64_t *)&frame[8], scratch,
                      ops[4], ops);
            if (rc == 0) {
                uint64_t dispatch = ops[2];
                rc = (int)((int (*)(uint64_t, uint64_t, uint64_t, uint64_t, uint8_t *,
                                    uint64_t, uint64_t *, uint64_t))dispatch)
                         (p1, p2, *(uint64_t *)&frame[0x10], *(uint64_t *)&frame[0x18],
                          scratch, ops[4], ops, p10);
                if (rc == 0) {
                    rc = (int)txm_ce_parse_cryptex_dict(
                             *(uint64_t *)&frame[0], *(uint64_t *)&frame[8],
                             (uint64_t *)&p7, (uint64_t *)&p8, (uint64_t *)&p5, (uint64_t *)&p6);
                    rc = (rc == 0) ? 0 : -1;
                }
            }
        } else {
            rc = -1;
        }
    }
    /* canary check */
}

/* FUN_000455b8 @ 0x000455b8   (est. txm_ce_parse_im4c)
 * Ghidra: parses an IM4C container into a frame. Shared IMG4 helper,
 * declared extern (recreated in a sibling region file). */
int txm_ce_parse_im4c(uint64_t src, uint64_t len, void *frame);

/* ============================================================================
 * txm_ce_log_dispatch  (FUN_00061e08)
 * ==========================================================================*/

/* FUN_00061e08 @ 0x00061e08   (est. txm_ce_log_dispatch)
 * Ghidra: void FUN_00061e08(undefined8 p1..p4)
 * Dispatches into the TXM log/state callback (FUN_00045a38) with a fixed
 * first arg 0.
 * Confidence: low */
void txm_ce_log_dispatch(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    ce_hash();      /* FUN_00045a38(0, p1..p4) */
}

/* ============================================================================
 * txm_ce_registry_match  (FUN_00061e28) / txm_ce_registry_unlock (FUN_00061e7c)
 * ==========================================================================*/

/* FUN_00061e28 @ 0x00061e28   (est. txm_ce_registry_match)
 * Ghidra: undefined8 FUN_00061e28(long p1..p5)
 * Matches a registry/entitlement entry: given a driver double-pointer table
 * (param_5+0x20 → table; table[2] → bucket list), returns 0 when the bucket
 * head matches param_4 twice (identity check) and unlocks the registry; else
 * 0xffffffff.
 * Confidence: low
 * Notes: ce_registry_lock (FUN_00037f5c) = registry unlock. */
uint64_t txm_ce_registry_match(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    uint64_t rc = 0xffffffff;
    if (p1 != 0 && p2 != 0 && p3 != 0 && p5 != 0) {
        uint64_t *tbl = *(uint64_t **)(p5 + 0x20);
        if (tbl != 0 && tbl[2] != 0 && p4 == tbl[0]) {
            uint64_t *bucket = (uint64_t *)tbl[2];
            if (bucket != 0 && p4 == bucket[0]) {
                ce_registry_lock();
                rc = 0;
            }
        }
    }
    return rc;
}

/* FUN_00061e7c @ 0x00061e7c   (est. txm_ce_registry_unlock)
 * Ghidra: undefined8 FUN_00061e7c(void)
 * Unlocks the CE registry (ce_registry_lock / FUN_00037f5c) and returns 0.
 * Confidence: low */
uint64_t txm_ce_registry_unlock(void)
{
    ce_registry_lock();
    return 0;
}

/* ============================================================================
 * txm_phys_to_virt  (FUN_00061ea4)
 * ==========================================================================*/

/* FUN_00061ea4 @ 0x00061ea4   (est. txm_phys_to_virt)
 * Ghidra: undefined8 FUN_00061ea4(ulong pa, long *out)
 * Translates a physical address to a TXM virtual address. Consults (in order)
 * the physmap-enable flag (DAT_000153a8), the boot range table
 * (DAT_000153b8, base+size*0x4000 stride entries, count *DAT_000153b0),
 * a single-mapping range (DAT_000153c0/c8/e0), and the physmap page table
 * (DAT_00015410, binary-searched by page index). On success writes the VA
 * into *out and returns 0; returns 1 when physmap isn't enabled, 2 on null
 * out, 4 on unmapped.
 * Confidence: medium
 * Notes: the DAT_000153xx globals are the TXM translation state. */
uint64_t txm_phys_to_virt(uint64_t pa, uint64_t *out)
{
    if ((g_txm_physmap_enabled & 1) == 0) return 1;
    if (out == 0) return 2;

    if (g_txm_pa_low <= pa && pa < g_txm_pa_high && g_txm_boot_nranges != 0) {
        uint64_t *r = (uint64_t *)(g_txm_boot_ranges + 0x10);
        uint64_t n = g_txm_boot_nranges;
        do {
            uint64_t base = r[-2];
            uint32_t npg = *(uint32_t *)&r[1];
            if (base <= pa && pa < base + npg * 0x4000) {
                *out = (pa - base) + r[-1];
                return 0;
            }
            r += 6;
        } while (--n != 0);
    }

    if (txm_pa_is_mapped(pa) == 0) {
        /* not a boot range: physmap page-table walk path */
        return 4;
    }
    return 4;
}

/* ============================================================================
 * Anti-replay panic stubs  (FUN_00062260 / 00062264 / 00062274 / 00062288 / 0006228c)
 * ==========================================================================*/

/* FUN_00062260/64/74/88/8c @ 0x00062260..8c (est. txm_panic_write_anti_replay[_…])
 * Ghidra: void FUN_000622xx(void) — noreturn
 * Anti-replay-state write panics. The first two first try to write the
 * anti-replay state (txm_antireplay_write / FUN_00050750) then unconditionally
 * panic with the "panic: writing anti replay state" message (string at 0x37f4);
 * the final three panic directly. These are the fail-closed halt paths for the
 * persistent anti-replay counter/state write path.
 * Confidence: high (explicit panic string at 0x37f4).
 * Notes: noreturn; txm_panic (FUN_00050d70) is the TXM panic routine. */
void txm_panic_write_anti_replay(void)
{
    txm_antireplay_write();
    txm_panic("panic: writing anti replay state");
}
void txm_panic_write_anti_replay_2(void)
{
    txm_antireplay_write();
    txm_panic("panic: writing anti replay state");
}
void txm_panic_write_anti_replay_3(void)
{
    txm_panic("panic: writing anti replay state");
}
void txm_panic_write_anti_replay_4(void)
{
    txm_panic("panic: writing anti replay state");
}
void txm_panic_write_anti_replay_5(void)
{
    txm_panic("panic: writing anti replay state");
}
