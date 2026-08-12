/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0xbe360-0xcc088) is the exclave-VM launcher / capability-log
 * subsystem: VM/notification capability-object slot accessors, capability
 * event-log records, and the InternalExclaveLauncher DER-component graph
 * builder (kernel/broker artifact resolution, page-frame mapping, launch
 * image assembly).
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */


/* FUN_000be360 @ 0x000be360   (est. cL4_cap_null_const)
 * Ghidra: undefined1 [16] FUN_000be360(void)
 * Returns a fixed 16-byte capability constant {0xd000000000000014,
 * 0x80000000004c2350} — an inline, side-effect-free getter for a
 * kernel-internal capability word pair (lo = type/tag bits, hi = pointer
 * metadata). No inputs; no side effects.
 * Confidence: low
 * Notes: Small leaf; returns two immediate constants. */
cl4_result_t cL4_cap_null_const(void)
{
    cl4_result_t r;
    r.lo = 0xd000000000000014ull;
    r.hi = 0x80000000004c2350ull;
    return r;
}

/* FUN_000be37c @ 0x000be37c   (est. cL4_cap_ret_and_free_entry)
 * Ghidra: undefined FUN_000be37c(void)
 * PAC-entry stub (pacibsp) that immediately falls through into the
 * body at 0xbe380; the real work (release/return a capability via the
 * free helper FUN_000be218) lives in the adjacent function.
 * Confidence: low
 * Notes: Single pacibsp instruction; Ghidra split the PAC entry from body. */
void cL4_cap_ret_and_free_entry(void)
{
    /* pacibsp (PAC-sign stack pointer) then fall into FUN_000be380 */
}

/* FUN_000be380 @ 0x000be380   (est. cL4_cap_free_and_return)
 * Ghidra: undefined FUN_000be380(void)
 * Releases a capability object and returns: calls the object-free helper
 * FUN_000be218 (declared extern below), sign/verify frame, return.
 * Confidence: low
 * Notes: Thin wrapper: stp frame, bl FUN_000be218, retab. */
void cL4_cap_free_and_return(void)
{
    /* stp x29,x30; mov x29,sp; bl cL4_obj_free_218; ldp; retab */
}

/* FUN_000be394 @ 0x000be394   (est. cL4_cap_state_entry)
 * Ghidra: undefined FUN_000be394(void)
 * PAC-entry stub falling into 0xbe398 (which calls FUN_000be234).
 * Confidence: low */
void cL4_cap_state_entry(void)
{
}

/* FUN_000be398 @ 0x000be398   (est. cL4_cap_state_advance)
 * Ghidra: undefined FUN_000be398(void)
 * Thin wrapper around FUN_000be234 (extern): advances/processes cap state.
 * Confidence: low */
void cL4_cap_state_advance(void)
{
    /* bl cL4_cap_state_234 */
}

/* FUN_000be3ac @ 0x000be3ac   (est. cL4_cap_null_ret_entry)
 * Ghidra: undefined FUN_000be3ac(void)
 * PAC-entry stub: calls FUN_000be360 then forces lo=0x14, hi=0xd000...<<48.
 * Confidence: low */
void cL4_cap_null_ret_entry(void)
{
    /* bl cL4_cap_null_const; mov x0,#0x14; movk x0,#0xd000,lsl #48 */
}

/* ---- shared cL4 helpers (out of slice; declared extern with notes) ---- */

/* FUN_00117cc4 — copy n bytes (memcpy-like) */
extern void cL4_memcpy(void *dst, const void *src, unsigned long n);
/* FUN_0000276c — format/append a string view into a buffer */
extern void cL4_fmt(void *dst, const char *fmt, const void *arg);
/* FUN_0007667c — copy/append operation (two pointer args) */
extern void cL4_append(void *dst, const void *src);
/* FUN_0007682c — release/return path (no-op-ish helper) */
extern void cL4_return(void);
/* FUN_000776cc — acquire current-thread / state */
extern unsigned long cL4_current(void);
/* FUN_000827a4 — grow/resize a vector at *ptr to hold count elements */
extern void cL4_vec_resize(void **ptr, unsigned long count, int flag);
/* FUN_0036b118 — release an object reference */
extern void *cL4_ref_release(void *obj);
/* FUN_0036b270 — release an object reference (pair variant); returns the obj */
extern unsigned long cL4_ref_release2(void *obj);
/* FUN_0036a1a0 — checkpoint / commit helper */
extern void cL4_commit(void);
/* FUN_0036b588 — release an object reference (message emit path) */
extern void cL4_msg_release(void *msg);
/* FUN_0036b6ac — release / finalize a capability reference */
extern void cL4_cap_release(void *obj, unsigned long kind, int flags);
/* FUN_0036a9a0 — allocate a message object from a template */
extern long cL4_msg_alloc(void *tmpl, void *stackbuf);
/* FUN_0036a940 — allocate/refresh a message string field */
extern unsigned long cL4_msg_field(unsigned long str, unsigned long kind, int tag);
/* FUN_00002534 — resolve an interned string (str + tag -> ptr) */
extern unsigned long cL4_intern(const char *str, const void *tag);
/* FUN_000d02a0 — attach/finalize message string into msg */
extern unsigned long cL4_msg_attach(void *msg, unsigned long str);
/* FUN_000732f4 — reallocate an array (grow to count) */
extern void *cL4_realloc(int grow, unsigned long count, int tag, void *old);
/* FUN_003a261c — query an object's state/refcount low bit */
extern unsigned long cL4_obj_state(void *obj);
/* FUN_003a25d4 — release an object (tail-call free) */
extern void cL4_obj_free(void *obj);
/* FUN_001fc840 — build a capability descriptor struct from 4 words */
extern void cL4_cap_build(void *out, void *scratch, unsigned long a,
                          unsigned long b, unsigned long c);
/* FUN_0026b434 — emit a capability event log record */
extern void cL4_cap_log(long msg, unsigned long kind, unsigned long a,
                        int b, unsigned long c);
/* FUN_00002688 — get the current thread/cap token */
extern unsigned long cL4_current_token(void);
/* FUN_002a4ab4 — select log event kind id */
extern void cL4_log_kind(unsigned long id);
/* FUN_002acbb8 — append a {value, type} pair to the log buffer */
extern void cL4_log_pair(unsigned long val, unsigned long type);
/* FUN_00027724 — fetch a function pointer by address (PAC-auth) */
extern void *cL4_pacia_fetch(unsigned long addr);
/* FUN_0007198c — initialize an iterator over a cap-set table */
extern void cL4_iter_init(void *out, unsigned long a, unsigned long b,
                          unsigned long c);
/* FUN_0007f4d8 — collect a cap word pair into a log record */
extern void cL4_collect(void *out, unsigned long a, unsigned long b,
                        unsigned long c);
/* FUN_000d1d84 — finalize a string-collection pass */
extern void cL4_finalize_str(unsigned long a, unsigned long b, unsigned long c);
/* FUN_000dbf08 / FUN_0001da84 — random/hash state advance pair */
extern unsigned long cL4_rng_state(void);
extern unsigned long cL4_rng_advance(void);
/* FUN_0002a9ba8 — load byte from a descriptor array */
extern unsigned long cL4_desc_load(unsigned long a, unsigned long b);
/* FUN_0002b141c / FUN_0002b24b8 — per-cap state resolve helpers */
extern unsigned long cL4_state_resolve(void);
extern unsigned long cL4_state_resolve2(void);
/* FUN_00082484 — array reserve helper (count-based) */
extern void cL4_arr_reserve(unsigned long a, unsigned long b, int flag);
/* thunk_FUN_00072664 — classify an object's kind from its tag */
extern cl4_result_t cL4_kind_probe(void *obj);
/* FUN_0007f4d8 already declared above */
/* FUN_0003a261c alias of cL4_obj_state */

/* ------------------------------------------------------------------ *
 * Function bodies (ascending address order)
 * ------------------------------------------------------------------ */

/* ---- in-slice forward declarations ---- */
static unsigned char scratch24[24];

/* ---- shared globals ---- */
extern unsigned char DAT_006add10;      /* debug/event-enable flag */
extern unsigned long DAT_00657788;      /* global collected-count */
extern unsigned long DAT_006577a8;      /* hash next-slot counter */
unsigned long cL4_vm_owner(unsigned long, unsigned long, unsigned long, unsigned long *);
unsigned long cL4_vm_descriptor(unsigned long, unsigned long, unsigned long,
                       unsigned long, unsigned long, unsigned long,
                       unsigned long, unsigned long, unsigned char,
                       unsigned long, unsigned long);
void cL4_vm_init(unsigned char, unsigned long, unsigned long, unsigned long,
                 unsigned long, unsigned long, unsigned long, unsigned long,
                 unsigned long, unsigned char, unsigned long, unsigned long);
void cL4_fmt_descriptor(unsigned char *, unsigned long);
void cL4_notif_slot_d8_release(long, unsigned long, unsigned long);
void cL4_notif_slot_d8_release2(long, unsigned long, unsigned long);

/* FUN_000be3cc @ 0x000be3cc   (est. cL4_cap_owner_token)
 * Ghidra: undefined1 [16] FUN_000be3cc(void)
 * Returns the 16-byte capability constant {0x650ef8, 0}: a kernel-internal
 * owner/type token. No inputs, no side effects.
 * Confidence: low
 * Notes: ZEXT816(0x650ef8). */
cl4_result_t cL4_cap_owner_token(void)
{
    cl4_result_t r;
    r.lo = 0x650ef8ull;
    r.hi = 0ull;
    return r;
}

/* FUN_000be40c @ 0x000be40c   (est. cL4_cap_vm_token)
 * Ghidra: undefined1 [16] FUN_000be40c(void)
 * Returns the 16-byte capability constant {0x650e98, 0}.
 * Confidence: low
 * Notes: ZEXT816(0x650e98). */
cl4_result_t cL4_cap_vm_token(void)
{
    cl4_result_t r;
    r.lo = 0x650e98ull;
    r.hi = 0ull;
    return r;
}

/* FUN_000be41c @ 0x000be41c   (est. cL4_cap_log_desc)
 * Ghidra: void FUN_000be41c(undefined8 param_1, undefined8 param_2)
 * Logs/records a capability descriptor: copies 0x6a bytes of the subject
 * (param_1) into a scratch record; if the type word at +0x28 is zero, formats
 * the record (via cL4_fmt) and the descriptor (cL4_fmt_descriptor, in-slice
 * FUN_000bf26c) into a logging buffer; otherwise appends param_2. Side
 * effects: emits a capability log record.
 * Confidence: medium
 * Notes: 0x6a-byte copy via FUN_00117cc4; local_f8 is the copied type word. */
void cL4_cap_log_desc(unsigned long param_1, unsigned long param_2)
{
    unsigned char record[0x6a];
    unsigned char descr[0x78];

    cL4_memcpy(record, (void *)param_1, 0x6a);
    if (*(unsigned long *)((char *)record + 0x28) == 0) {
        cL4_fmt(record, (const char *)0x650f48, (void *)0x4c2490);
        cL4_fmt_descriptor(descr, param_2);
        cL4_fmt(descr, (const char *)0x650f48, (void *)0x4c2490);
    } else {
        cL4_memcpy(descr, (void *)param_1, 0x6a);
        cL4_append(descr, (void *)param_2);
    }
}

/* FUN_000be4c4 @ 0x000be4c4   (est. cL4_cap_log_commit)
 * Ghidra: void FUN_000be4c4(undefined8 param_1, long param_2, undefined8 param_3)
 * Commits a capability log record. If param_2 (a validity/kind flag) is
 * nonzero, simply returns (no-op). Otherwise classifies param_3's kind
 * (cL4_kind_probe); if the low bit is set, builds a descriptor for the object
 * at *unaff_x20 via the object state and an interned string, emits it, and
 * restores the object pointer.
 * Confidence: medium
 * Notes: unaff_x20 is a caller-saved object slot; FUN_003a261c state probe,
 * FUN_003a25d4 release of the built record. */
void cL4_cap_log_commit(unsigned long param_1, long param_2, unsigned long param_3)
{
    unsigned long *slot;   /* caller object slot held in x20 (unaff_x20) */
    cl4_result_t kind;
    unsigned long obj, state, str;
    unsigned char out[8], scratch[8];

    if (param_2 != 0) {
        cL4_return();
        return;
    }
    kind = cL4_kind_probe((void *)param_3);
    if ((kind.hi & 1) != 0) {
        obj = *slot;
        state = cL4_obj_state((void *)obj);
        str = cL4_intern((const char *)0x64e688, (void *)0x4c25c0);
        cL4_cap_build(out, scratch, kind.lo, state, str);
        cL4_obj_free(out);
        *slot = obj;
    }
}

/* FUN_000be578 @ 0x000be578   (est. cL4_cap_log_set_entry)
 * Ghidra: void FUN_000be578(undefined8 param_1, long param_2, undefined8 param_3)
 * Logs a capability-set entry: if param_1 is nonzero returns via cL4_return
 * (no-op). Otherwise reads the object word from *slot, probes its state; if
 * the low bit is set, records the old word, builds a descriptor from the
 * object state plus an interned string, emits both sub-words (cL4_ref_release
 * on each), and writes the recorded word back to *slot.
 * Confidence: medium
 * Notes: slot in x20 (unaff_x20); uses cL4_cap_build + FUN_001fc840 pattern
 * mirror of FUN_000be4c4. */
void cL4_cap_log_set_entry(unsigned long param_1, unsigned long param_2,
                           unsigned long param_3)
{
    unsigned long *slot;   /* unaff_x20 object slot */
    cl4_result_t kind;
    unsigned long state, obj, str;
    unsigned long lo50, lo48, lo40;
    unsigned long scratch16;

    (void)param_2;
    if (param_1 != 0) {
        cL4_return();
        return;
    }
    slot = (unsigned long *)0;   /* unaff_x20 */
    kind = cL4_kind_probe((void *)param_3);
    if ((kind.hi & 1) != 0) {
        state = cL4_obj_state((void *)*slot);
        lo40 = *slot;
        str = cL4_intern((const char *)0x64e778, (void *)0x4c25d0);
        cL4_cap_build(&lo50, &scratch16, kind.lo, state, str);
        cL4_ref_release((void *)lo50);
        cL4_ref_release((void *)lo48);
        *slot = lo40;
    }
}

/* FUN_00071050 — descriptor dispatch helper (out of slice) */
extern void cL4_dispatch_helper(unsigned long a, unsigned long b);

/* ---- more shared cL4 helpers ---- */

/* FUN_000867a8 — lock/acquire a slot for read-modify-write */
extern void cL4_slot_lock(void *slot, void *scratch);
/* FUN_0036a1a0 — commit a slot transaction */
extern void cL4_slot_commit(void *slot, void *scratch, unsigned long kind, int flag);
/* FUN_0036a20c — finish/release a slot transaction context */
extern void cL4_slot_done(void *scratch);
/* FUN_0008e3b0 — validate/prepare a slot before writing */
extern void cL4_slot_prepare(void *slot);
/* FUN_0009e228 — validate a slot and produce a token pair */
extern void cL4_slot_token(void *slot, void *scratch);
/* FUN_0006e7c0 — copy an object value/pointer pair (getter payload) */
extern void cL4_get_pair(void *dst, void *src);
/* FUN_00077070 — copy a descriptor pair (a,b) */
extern void cL4_copy_pair(void *dst, void *src);
/* FUN_000770e8 / FUN_000dbcc8 / FUN_000dbdf4 — message-field copy helpers */
extern void cL4_field_copy(void *dst, unsigned long a);
extern void cL4_field_copy2(void *dst, unsigned long a);
extern unsigned long cL4_field_new(void);
/* FUN_000026e8 — release/destroy a field buffer */
extern void cL4_field_free(void *field);
/* FUN_004b23d8 — release a collected object */
extern void cL4_collect_release(void *obj);
/* FUN_0008e388 / FUN_0006ae9c — object map lookup (name->slot) */
extern void cL4_map_lookup_prep(void);
extern cl4_result_t cL4_map_lookup(unsigned long a, unsigned long b);
/* FUN_002a0cf8 — compare two name words for identity/kind match */
extern unsigned long cL4_name_match(unsigned long a, unsigned long b,
                                    unsigned long c, unsigned long d, int flag);
/* FUN_0036a804 / FUN_000dbe0c / FUN_000dbea4 — object list alloc/init */
extern unsigned long cL4_list_alloc(void);
extern void *cL4_list_new(unsigned long kind);
extern void cL4_list_begin(void);
/* FUN_001f0130 — build a 4-word descriptor */
extern unsigned long cL4_descriptor(unsigned long a, unsigned long b,
                                    unsigned long c, unsigned long d);
/* FUN_000dbd0c / FUN_000dbd0c — descriptor field getters */
extern cl4_result_t cL4_desc_field(void);
/* FUN_0006f69c — log/register a descriptor field */
extern void cL4_desc_register(unsigned long a, ...);
/* FUN_00083c34 — allocate a small cap record */
extern unsigned long cL4_cap_small_alloc(int flag);
/* FUN_000773f0 — allocate an object of a given class */
extern unsigned long cL4_obj_alloc(int flag);
/* FUN_00002834 — release an allocation */
extern void cL4_alloc_free(unsigned long a);
/* FUN_000db650 / FUN_000db650 — copy a string field into a buffer */
extern void cL4_str_field(void *dst, void *src, const char *s, const void *t);
/* FUN_000dbc84 / FUN_000dbc70 / FUN_000dbc40 — field transaction begin/end */
extern void cL4_field_begin(void);
extern void cL4_field_begin2(void);
extern void cL4_field_end(void);
/* FUN_000dbb10 / FUN_000dbb30 / FUN_000dbb24 — string/list finalize helpers */
extern void cL4_list_finalize(void);
extern void cL4_list_finalize2(void);
extern void cL4_list_finalize3(void *a);
/* FUN_0006da68 / FUN_0006d8a4 — compute an object checksum/name pair */
extern unsigned long cL4_obj_checksum(void);
extern unsigned long cL4_obj_checksum2(void *scratch);
/* FUN_0006e81c — mark/validate a write in progress */
extern void cL4_write_mark(int flag);
/* FUN_000dbf7c / FUN_000dbf14 / FUN_000dbf70 — bit-vector resize helpers */
extern void cL4_bv_resize(int flag, unsigned long count, int tag);
extern void cL4_bv_resize2(int flag, unsigned long count, int tag);
extern void cL4_bv_resize3(void);
/* FUN_0006b42c / FUN_001a0774 / FUN_0006b6a0 — vector grow helpers */
extern unsigned long cL4_vec_grow_cap(void);
extern void cL4_vec_grow(void *a, unsigned long count, int flag);
extern void cL4_vec_grow2(void);
/* FUN_000741e0 / FUN_00072d5c / FUN_00072d5c / FUN_00074220 — array realloc */
extern void *cL4_arr_grow(int grow, unsigned long count, int tag, void *old);
extern void *cL4_arr_grow2(void);
extern void *cL4_arr_grow3(void);
extern void *cL4_arr_grow4(void);
/* FUN_00082564 / FUN_000826c4 / FUN_000826e4 / FUN_00082484 / FUN_0006b3f4 */
extern void cL4_arr_reserve2(int flag, unsigned long count, int tag);
extern void cL4_arr_reserve3(int flag, unsigned long count, int tag);
extern void cL4_arr_reserve4(int flag, unsigned long count, int tag);
extern void cL4_arr_reserve5(unsigned long a, unsigned long count, int flag);
extern void cL4_arr_reserve6(void *a);
/* FUN_0007bf4c / FUN_0009d480 / FUN_0009d480 — map/collect value pairs */
extern void cL4_map_value(void *a, unsigned long b);
extern void cL4_map_value2(unsigned long a, unsigned long b);
/* FUN_0007144c / FUN_000764a0 / FUN_000764c8 — descriptor commit helpers */
extern void cL4_desc_commit(void *a, void *b, unsigned long c, unsigned long d,
                            unsigned long e);
extern void cL4_desc_commit2(unsigned long a, unsigned long b);
extern void cL4_desc_commit3(unsigned long a, unsigned long b, unsigned long c);
/* FUN_0006a4c0 — read a field value out of a descriptor */
extern unsigned long cL4_field_value(void *desc, unsigned long a);
/* FUN_000a0420 / FUN_000da558 — compare / append descriptor words */
extern long cL4_desc_cmp(unsigned long a, unsigned long b);
extern void cL4_desc_append(void *a, void *b, unsigned long c, unsigned long d,
                            unsigned long e);
/* FUN_0008dce0 / FUN_00087234 / FUN_0006a4c0 — type-class resolve */
extern unsigned long cL4_type_class(int flag);
extern unsigned long cL4_type_class2(void *a);
/* FUN_000e5c5c / FUN_000e22c0 / FUN_000e21b4 / FUN_000e20c4 — name hashing */
extern unsigned long cL4_name_hash(unsigned long a, unsigned long b);
extern unsigned long cL4_name_hash2(void);
extern unsigned long cL4_name_hash3(void);
extern unsigned long cL4_name_hash4(void);
/* FUN_0010562c / FUN_0016189c / FUN_001615a4 / FUN_00167a6c / FUN_00167c48 */
extern unsigned long cL4_str_id(unsigned long a, unsigned long b);
extern unsigned char cL4_cmp_strings(void *a, void *b, unsigned long c,
                                     unsigned long d);
extern char cL4_string_eq(void *a);
extern unsigned long cL4_str_new(int flag);
extern void *cL4_str_ctx(void);
/* FUN_002abe60 — path/name string equality check */
extern unsigned int cL4_name_equal(unsigned long a, unsigned long b, unsigned long c,
                           unsigned long d);
/* FUN_0001e790 / FUN_00002688 — thread/token getters */
extern unsigned long cL4_token2(void);
/* FUN_00083a78 / FUN_00083acc — object graph push/pop */
extern void cL4_graph_push(void *a, void *b);
extern void cL4_graph_pop(void *a);
/* FUN_0008da6c / FUN_000db748 / FUN_000db808 / FUN_000db2d8 / FUN_000db838 /
   FUN_00077088 / FUN_000770b8 / FUN_0008e5d8 / FUN_0008e5d8 / FUN_000db620 /
   FUN_000dbddc / FUN_000db250 / FUN_000db184 / FUN_000dbe40 / FUN_000dbf20 */
extern void *cL4_vtbl(unsigned long a);
extern void *cL4_vtbl2(unsigned long a);
extern void *cL4_vtbl3(unsigned long a);
extern void *cL4_vtbl4(unsigned long a);
extern void *cL4_vtbl5(unsigned long a);
extern void *cL4_vtbl6(unsigned long a);
extern void *cL4_vtbl7(unsigned long a);
extern void *cL4_vtbl8(unsigned long a);
extern void *cL4_vtbl9(unsigned long a);
extern void *cL4_vtbl10(unsigned long a);
extern void cL4_vtbl_apply(void *a, void *b);
extern void cL4_vtbl_apply2(void *a, void *b);
extern void cL4_vtbl_apply3(void *a);
/* FUN_0006f800 / FUN_000aa6d0 / FUN_000dbe58 / FUN_000ec964 / FUN_0009781c */
extern unsigned long cL4_get_state(void *a);
extern unsigned long cL4_get_state2(int flag);
extern unsigned long cL4_get_state3(void);
extern unsigned long cL4_get_state4(int flag);
extern unsigned long cL4_state_join(void);
/* FUN_00002874 / FUN_00002818 — panic helpers */
extern void cL4_panic1(const char *s);
extern void cL4_panic2(void);
/* FUN_001ee9f4 / FUN_001afa84 — noreturn fatal-error paths */
extern void cL4_fatal_noreturn(void);
/* FUN_000ec8f8 / FUN_000ec738 / FUN_000ed954 / FUN_000f4994 / FUN_000f6ae8 /
   FUN_000f67b4 / FUN_0009d068 / FUN_000986d4 / FUN_00092914 / FUN_00083c70 /
   FUN_0007ead8 / FUN_0008e500 / FUN_0008e518 */
extern unsigned long cL4_cls(int flag);
extern void cL4_cls2(void);
extern unsigned long cL4_cls3(void);
extern unsigned long cL4_cls4(int flag);
extern unsigned long cL4_cls5(int flag);
extern unsigned long cL4_cls6(void *a, void *b);
extern unsigned long cL4_cls7(int flag);
extern unsigned long cL4_cls8(void);
extern unsigned long cL4_cls9(void);
extern unsigned long cL4_cls10(int flag);
extern unsigned long cL4_cls11(void *a, void *b, unsigned long c, void *d,
                               unsigned long e, unsigned long f);
extern void cL4_cls12(unsigned long a, unsigned long b);
extern cl4_result_t cL4_cls13(void);
/* FUN_000a6840 / FUN_000a63f0 / FUN_000a6444 / FUN_000a7490 / FUN_000a7c6c */
extern void cL4_slot_load(void *dst, void *src);
extern void cL4_slot_load2(void *dst, void *src);
extern void cL4_slot_load3(void *dst);
extern void *cL4_vm_cls(int flag);
extern void cL4_vm_cls2(int flag);
/* FUN_000d45ec / FUN_000d4964 / FUN_000d42a8 / FUN_000d5360 */
extern void *cL4_dg_new(void);
extern void cL4_dg_step(void *a, void **b, void **c, void *d, void *e,
                        unsigned long f, unsigned long g);
extern unsigned char cL4_dg_cmp(unsigned long a, unsigned long b);
extern unsigned long cL4_dg_desc(unsigned long a, unsigned long b);
/* FUN_00139c6c / FUN_000acc00 / FUN_000b3fdc / FUN_000b8bf4 / FUN_0005526c /
   FUN_0015b87c / FUN_001a1564 / FUN_001dd77c / FUN_001dd858 / FUN_000e27a4 /
   FUN_0019e3b0 / FUN_000e7a64 / FUN_000be2ec / FUN_001a84f4 / FUN_001a8564 /
   FUN_001394c8 / FUN_0011ea78 / FUN_0011ea78 */
extern unsigned long cL4_num(int flag);
extern void *cL4_os(void *a);
extern void *cL4_os2(int flag);
extern unsigned long cL4_os3(void *a);
extern unsigned long cL4_os4(void);
extern void *cL4_os5(unsigned long a);
extern unsigned long cL4_os6(void);
extern void *cL4_os7(unsigned long a, unsigned long b, unsigned long c);
extern void *cL4_os8(unsigned long a);
extern unsigned long cL4_os9(int flag);
extern void *cL4_os10(void);
extern void *cL4_os11(void *a, unsigned long b, unsigned long c, unsigned long d,
                      void *e, void *f, unsigned long g, unsigned long h,
                      unsigned long i);
extern unsigned long cL4_os12(void *a, unsigned long b);
extern unsigned long cL4_os13(unsigned long a, unsigned long b);
extern unsigned long cL4_os14(void);
extern void *cL4_os15(unsigned long a, int flag);
extern unsigned long cL4_os16(void);
extern void cL4_os17(int flag, unsigned long a);
extern unsigned long cL4_os18(void *a);
extern void *cL4_os19(void);
extern void *cL4_os20(void);
extern void *cL4_os21(void *a, void *b, void *c, void *d, unsigned long e,
                     unsigned long f, unsigned long g);
extern void *cL4_os22(void *a, void *b, unsigned long c, unsigned long d,
                      unsigned long e);
extern unsigned long cL4_os23(void *a);
extern void cL4_os24(void *a, unsigned long b);
extern void *cL4_os25(void);
extern void *cL4_os26(void *a, unsigned long b, unsigned long c, void *d,
                      unsigned long e, unsigned long f);
extern void cL4_os27(void *a, unsigned long b);
extern void *cL4_os28(void *a, void *b, void *c, void *d, void *e, void *f,
                      unsigned long g, unsigned long h);
extern void *cL4_os29(void *a, void *b, unsigned long c, unsigned long d,
                      unsigned long e, unsigned long f, unsigned long g,
                      unsigned long h);
extern unsigned long cL4_os30(void);
extern void *cL4_os31(void *a, void *b, unsigned long c, unsigned long d,
                      unsigned long e, unsigned long f, unsigned long g,
                      unsigned long h, unsigned long i, unsigned long j,
                      unsigned long k);
extern void *cL4_os32(void *a, void *b, unsigned long c, unsigned long d,
                      unsigned long e, unsigned long f, unsigned long g,
                      unsigned long h, unsigned long i, unsigned long j,
                      unsigned long k, unsigned long l);
extern unsigned long cL4_os33(unsigned long a, unsigned long b);
extern void *cL4_os34(void *a, unsigned long b, unsigned long c);
extern unsigned long cL4_os35(void *a);
extern void *cL4_os36(unsigned long a, unsigned long b, unsigned long c,
                      unsigned long d, unsigned long e, unsigned long f);
extern unsigned long cL4_os37(void *a);
extern void *cL4_os38(int flag);
extern void cL4_os39(void);
extern unsigned long cL4_os40(void *a, unsigned long b, unsigned long c);
extern void cL4_os41(void *a, unsigned long b, unsigned long c, unsigned long d,
                     unsigned long e);
extern void cL4_os42(void *a, unsigned long b, unsigned long c);
extern void cL4_os43(void *a, unsigned long b, unsigned long c, void *d);
extern void cL4_os44(void *a, unsigned long b, unsigned long c, void *d);
extern void cL4_os45(void *a);
extern void *cL4_os46(void *a, unsigned long b, unsigned long c);
extern void cL4_os47(void *a, unsigned long b);
extern unsigned long cL4_os48(void);
extern void cL4_os49(void *a, unsigned long b, unsigned long c);
extern void *cL4_os50(void *a, unsigned long b);
extern void *cL4_os51(void *a, void *b, unsigned long c);
extern void cL4_os52(void *a, unsigned long b, unsigned long c, void *d);
extern unsigned long cL4_os53(void *a, unsigned long b);
extern void *cL4_os54(unsigned long a, unsigned long b, unsigned long c,
                      unsigned long d, unsigned long e);
extern void cL4_os55(void *a, unsigned long b, unsigned long c);
extern void *cL4_os56(void *a, void *b, void *c);
extern void cL4_os57(void *a);
extern void *cL4_os58(unsigned long a, unsigned long b, unsigned long c);
extern void *cL4_os59(void *a);
extern void *cL4_os60(void *a);
extern void *cL4_os61(void *a, void *b, unsigned long c, unsigned long d,
                      void *e, void *f, void *g, void *h);
extern void *cL4_os62(void *a);
extern void *cL4_os63(void *a, void *b);
extern void *cL4_os64(void *a);
extern unsigned long cL4_os65(int flag);
extern void *cL4_os66(void *a, void *b, void *c, void *d);
extern void *cL4_os67(void *a, void *b, void *c, void *d);
extern void *cL4_os68(void *a);
extern void *cL4_os69(void *a, void *b, void *c, void *d, unsigned long e,
                      unsigned long f);
extern void *cL4_os70(void *a, unsigned long b);
extern void cL4_os71(void *a, unsigned long b);
extern void *cL4_os72(void *a);
extern void *cL4_os73(void *a, void *b, void *c, void *d, void *e, void *f);
extern void *cL4_os74(void *a, void *b);
extern void *cL4_os75(void *a);
extern void *cL4_os76(void *a, void *b);
extern void *cL4_os77(void *a);
extern unsigned long cL4_os78(void *a);
extern void cL4_os79(void *a, unsigned long b);
extern void *cL4_os80(void *a);
extern void *cL4_os81(void *a, unsigned long b);
extern void *cL4_os82(void *a, void *b);
extern void *cL4_os83(void *a);
extern void *cL4_os84(void *a, unsigned long b);
extern void *cL4_os85(void *a, unsigned long b);
extern void *cL4_os86(void *a);
extern void *cL4_os87(void *a, unsigned long b);
extern void *cL4_os88(void *a);
extern void *cL4_os89(void *a);
extern void *cL4_os90(void *a);
extern void *cL4_os91(void *a);
extern void *cL4_os92(void *a, unsigned long b);
extern unsigned long cL4_os93(void *a);
extern void cL4_os94(void *a, unsigned long b);
extern void *cL4_os95(void *a, unsigned long b);
extern void *cL4_os96(void *a, unsigned long b);
extern void *cL4_os97(void *a);
extern void *cL4_os98(void *a, unsigned long b);
extern void *cL4_os99(void *a, unsigned long b);
extern void *cL4_os100(void *a, unsigned long b);
extern void *cL4_os101(void *a, unsigned long b);
extern void *cL4_os102(void *a);
extern void *cL4_os103(void *a, unsigned long b);
extern void *cL4_os104(void *a, unsigned long b);
extern void *cL4_os105(void *a, unsigned long b);
extern void *cL4_os106(void *a, unsigned long b);
extern void *cL4_os107(void *a, unsigned long b);
extern void *cL4_os108(void *a, unsigned long b);
extern void *cL4_os109(void *a, unsigned long b);
extern void *cL4_os110(void *a, unsigned long b);
extern void *cL4_os111(void *a, unsigned long b);
extern void *cL4_os112(void *a, unsigned long b);
extern void *cL4_os113(void *a, unsigned long b);
extern void *cL4_os114(void *a, unsigned long b);
extern void *cL4_os115(void *a, unsigned long b);
extern void *cL4_os116(void *a, unsigned long b);
extern void *cL4_os117(void *a, unsigned long b);
extern void *cL4_os118(void *a, unsigned long b);
extern void *cL4_os119(void *a, unsigned long b);
extern void *cL4_os120(void *a, unsigned long b);

/* ------------------------------------------------------------------ *
 * Notification-object capability slot accessors.
 * Each object (unaff_x20) is a notification/endpoint cap record whose
 * fields are a set of slot triplets: a getter (release old), a setter
 * (swap, release previous), and a token getter (return {&DAT_0007bf58,
 * slot}). Offsets increment 0x10 per slot.
 * ------------------------------------------------------------------ */

/* FUN_000bf4e4 @ 0x000bf4e4   (est. cL4_notif_get_obj)
 * Ghidra: undefined8 FUN_000bf4e4(long param_1)
 * If the object's count word at +0x10 is nonzero, returns (releasing) the
 * object pointer at +0x20; else returns 0.
 * Confidence: high (regular getter pattern) */
unsigned long cL4_notif_get_obj(long obj)
{
    if (*(long *)(obj + 0x10) != 0) {
        return (unsigned long)cL4_ref_release2((void *)*(unsigned long *)(obj + 0x20));
    }
    return 0;
}

/* FUN_000bf514 @ 0x000bf514   (est. cL4_notif_slot10_get)
 * Ghidra: void FUN_000bf514(void)
 * Lock slot +0x10, commit, release the object stored there. (Getter.)
 * Confidence: high */
void cL4_notif_slot10_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x10), scratch);
    cL4_slot_commit((void *)(obj + 0x10), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x10));
}

/* FUN_000bf548 @ 0x000bf548   (est. cL4_notif_slot10_token)
 * Ghidra: undefined1 [16] FUN_000bf548(undefined8 param_1)
 * Validate slot +0x10 with the given value, commit, return token pair
 * {&DAT_0007bf58, obj+0x10}.
 * Confidence: high */
cl4_result_t cL4_notif_slot10_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x10), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x10), (void *)param_1, 0, 0);
    r.lo = 0x7bf58;
    r.hi = obj + 0x10;
    return r;
}

/* FUN_000bf59c @ 0x000bf59c   (est. cL4_notif_slot20_get)
 * Getter on slot +0x20.
 * Confidence: high */
void cL4_notif_slot20_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x20), scratch);
    cL4_slot_commit((void *)(obj + 0x20), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x20));
}

/* FUN_000bf61c @ 0x000bf61c   (est. cL4_notif_slot28_get)
 * Getter on slot +0x28 (releases the stored object).
 * Confidence: high */
void cL4_notif_slot28_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x28), scratch);
    cL4_slot_commit((void *)(obj + 0x28), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x28));
}

/* FUN_000bf65c @ 0x000bf65c   (est. cL4_notif_slot28_set)
 * Setter on slot +0x28 (a two-word pair: +0x28=param_1, +0x30=param_2),
 * releasing the previous first word.
 * Confidence: high */
void cL4_notif_slot28_set(unsigned long param_1, unsigned long param_2)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x28));
    old = *(unsigned long *)(obj + 0x28);
    *(unsigned long *)(obj + 0x28) = param_1;
    *(unsigned long *)(obj + 0x30) = param_2;
    cL4_ref_release((void *)old);
}

/* FUN_000bf6a4 @ 0x000bf6a4   (est. cL4_notif_slot28_token) */
cl4_result_t cL4_notif_slot28_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x28), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x28), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x28;
    return r;
}

/* FUN_000bf6f0 @ 0x000bf6f0   (est. cL4_notif_slot38_get) */
void cL4_notif_slot38_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x38), scratch);
    cL4_slot_commit((void *)(obj + 0x38), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x38));
}

/* FUN_000bf724 @ 0x000bf724   (est. cL4_notif_slot38_set) */
void cL4_notif_slot38_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x38));
    old = *(unsigned long *)(obj + 0x38);
    *(unsigned long *)(obj + 0x38) = param_1;
    cL4_obj_free((void *)old);
}

/* FUN_000bf760 @ 0x000bf760   (est. cL4_notif_slot38_token) */
cl4_result_t cL4_notif_slot38_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x38), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x38), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x38;
    return r;
}

/* FUN_000bf7ac @ 0x000bf7ac   (est. cL4_notif_slot40_get) */
void cL4_notif_slot40_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x40), scratch);
    cL4_slot_commit((void *)(obj + 0x40), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x40));
}

/* FUN_000bf7e0 @ 0x000bf7e0   (est. cL4_notif_slot40_token) */
cl4_result_t cL4_notif_slot40_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x40), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x40), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x40;
    return r;
}

/* FUN_000bf82c @ 0x000bf82c   (est. cL4_notif_slot48_get) */
void cL4_notif_slot48_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x48), scratch);
    cL4_slot_commit((void *)(obj + 0x48), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x48));
}

/* FUN_000bf860 @ 0x000bf860   (est. cL4_notif_slot48_set) */
void cL4_notif_slot48_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x48));
    old = *(unsigned long *)(obj + 0x48);
    *(unsigned long *)(obj + 0x48) = param_1;
    cL4_obj_free((void *)old);
}

/* FUN_000bf89c @ 0x000bf89c   (est. cL4_notif_slot48_token) */
cl4_result_t cL4_notif_slot48_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x48), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x48), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x48;
    return r;
}

/* FUN_000bf8e8 @ 0x000bf8e8   (est. cL4_notif_slot50_get) */
void cL4_notif_slot50_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x50), scratch);
    cL4_slot_commit((void *)(obj + 0x50), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x50));
}

/* FUN_000bf91c @ 0x000bf91c   (est. cL4_notif_slot50_set) */
void cL4_notif_slot50_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x50));
    old = *(unsigned long *)(obj + 0x50);
    *(unsigned long *)(obj + 0x50) = param_1;
    cL4_ref_release((void *)old);
}

/* FUN_000bf958 @ 0x000bf958   (est. cL4_notif_slot50_token) */
cl4_result_t cL4_notif_slot50_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x50), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x50), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x50;
    return r;
}

/* FUN_000bf9a4 @ 0x000bf9a4   (est. cL4_notif_slot58_get) */
void cL4_notif_slot58_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x58), scratch);
    cL4_slot_commit((void *)(obj + 0x58), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x58));
}

/* FUN_000bf9d8 @ 0x000bf9d8   (est. cL4_notif_slot58_set) */
void cL4_notif_slot58_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x58));
    old = *(unsigned long *)(obj + 0x58);
    *(unsigned long *)(obj + 0x58) = param_1;
    cL4_ref_release((void *)old);
}

/* FUN_000bfa14 @ 0x000bfa14   (est. cL4_notif_slot58_token) */
cl4_result_t cL4_notif_slot58_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x58), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x58), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x58;
    return r;
}

/* FUN_000bfa60 @ 0x000bfa60   (est. cL4_notif_slot60_get)
 * Getter on slot +0x60: lock, commit, then copy the stored pair out via
 * cL4_get_pair(obj+0x60, param_1).
 * Confidence: high */
void cL4_notif_slot60_get(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x60), scratch);
    cL4_slot_commit((void *)(obj + 0x60), scratch, 0, 0);
    cL4_get_pair((void *)(obj + 0x60), (void *)param_1);
}

/* FUN_000bfaa4 @ 0x000bfaa4   (est. cL4_notif_slot60_set)
 * Setter on slot +0x60: validate, release old field, copy pair into slot.
 * Confidence: high */
void cL4_notif_slot60_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_token((void *)(obj + 0x60), scratch);
    cL4_slot_commit((void *)(obj + 0x60), scratch, 0, 0);
    cL4_field_free((void *)(obj + 0x60));
    cL4_copy_pair((void *)param_1, (void *)(obj + 0x60));
    cL4_slot_done(scratch);
}

/* FUN_000bfaf8 @ 0x000bfaf8   (est. cL4_notif_slot60_token) */
cl4_result_t cL4_notif_slot60_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x60), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x60), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x60;
    return r;
}

/* FUN_000bfb44 @ 0x000bfb44   (est. cL4_notif_slot88_get) */
void cL4_notif_slot88_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x88), scratch);
    cL4_slot_commit((void *)(obj + 0x88), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x88));
}

/* FUN_000bfb78 @ 0x000bfb78   (est. cL4_notif_slot88_set) */
void cL4_notif_slot88_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x88));
    old = *(unsigned long *)(obj + 0x88);
    *(unsigned long *)(obj + 0x88) = param_1;
    cL4_ref_release((void *)old);
}

/* FUN_000bfbb4 @ 0x000bfbb4   (est. cL4_notif_slot88_token) */
cl4_result_t cL4_notif_slot88_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x88), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x88), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x88;
    return r;
}

/* FUN_000bfc00 @ 0x000bfc00   (est. cL4_notif_slot90_get) */
void cL4_notif_slot90_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x90), scratch);
    cL4_slot_commit((void *)(obj + 0x90), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x90));
}

/* FUN_000bfc34 @ 0x000bfc34   (est. cL4_notif_slot98_get)
 * Ghidra: void FUN_000bfc34(undefined8 *param_1, long *param_2)
 * Reads the two-word value at slot +0x98 of *param_2, materializes a
 * descriptor of kind 0x20/7 (FUN_0036a940), stores the pair into the
 * descriptor, and returns it via *param_1 = {&DAT_000db410, descriptor},
 * releasing the previous value.
 * Confidence: medium */
void cL4_notif_slot98_get(unsigned long *param_1, long *param_2)
{
    long src = *param_2;
    unsigned char scratch[24];
    unsigned long desc, lo, hi;
    cL4_slot_commit((void *)(src + 0x98), scratch, 0, 0);
    desc = cL4_msg_field(0x6613c0, 0x20, 7);
    hi = *(unsigned long *)(src + 0xa0);
    lo = *(unsigned long *)(src + 0x98);
    *(unsigned long *)(desc + 0x18) = hi;
    *(unsigned long *)(desc + 0x10) = lo;
    param_1[0] = 0xdb410;
    param_1[1] = desc;
    cL4_ref_release2((void *)hi);
}

/* FUN_000bfcb0 @ 0x000bfcb0   (est. cL4_notif_vtbl_call)
 * Ghidra: void FUN_000bfcb0(undefined8 *param_1, undefined8 param_2,
 *                           undefined8 *param_3, code *param_4)
 * Indirect dispatch: calls *param_4 with the two value words from param_3
 * and two bytes, storing the result in *param_1.
 * Confidence: low */
void cL4_notif_vtbl_call(unsigned long *param_1, unsigned long param_2,
                         unsigned long *param_3, void *param_4)
{
    unsigned long (*fn)(unsigned long, unsigned long, unsigned long,
                        unsigned char, unsigned char) = param_4;
    param_1[0] = fn(param_2, param_3[0], param_3[1],
                    *(unsigned char *)(param_3 + 2),
                    *(unsigned char *)((char *)param_3 + 0x11));
}

/* FUN_000bfcf4 @ 0x000bfcf4   (est. cL4_notif_slot98_set)
 * Ghidra: void FUN_000bfcf4(undefined8 *param_1, long *param_2)
 * Replaces slot +0x98 of *param_2 with the two-word value from param_1:
 * materializes a descriptor (0x661398/0x20/7), stores it into the slot,
 * releases the previous slot contents.
 * Confidence: medium */
void cL4_notif_slot98_set(unsigned long *param_1, long *param_2)
{
    unsigned char scratch[24];
    long src = *param_2;
    unsigned long desc, old_hi, old_lo;
    desc = cL4_msg_field(0x661398, 0x20, 7);
    old_hi = param_1[1];
    old_lo = param_1[0];
    *(unsigned long *)(desc + 0x18) = old_hi;
    *(unsigned long *)(desc + 0x10) = old_lo;
    cL4_slot_commit((void *)(src + 0x98), scratch, 1, 0);
    old_hi = *(unsigned long *)(src + 0xa0);
    *(unsigned long *)(src + 0x98) = 0xdb408;
    *(unsigned long *)(src + 0xa0) = desc;
    cL4_ref_release2((void *)old_hi);
    cL4_ref_release((void *)old_hi);
}

/* FUN_000bfd8c @ 0x000bfd8c   (est. cL4_notif_slot98_indirect)
 * Ghidra: undefined8 FUN_000bfd8c(...)
 * Builds a {value,type} record from params and calls the vtbl *param_6 with
 * (out, param_1, &record); releases param_3; returns the result word.
 * Confidence: low */
unsigned long cL4_notif_slot98_indirect(unsigned long param_1, unsigned long param_2,
                                        unsigned long param_3, unsigned char param_4,
                                        unsigned char param_5, void *param_6)
{
    unsigned long out, local48 = param_2;
    unsigned long u40 = param_3;
    unsigned char l38 = param_4;
    unsigned char l37 = param_5;
    unsigned long (*fn)(unsigned long *, unsigned long, unsigned long *) = param_6;
    cL4_ref_release2((void *)param_3);
    fn(&out, param_1, &local48);
    cL4_obj_free((void *)param_3);
    return out;
}

/* FUN_000bfdfc @ 0x000bfdfc   (est. cL4_notif_slot98_getpair)
 * Ghidra: undefined1 [16] FUN_000bfdfc(void)
 * Returns the 16-byte pair stored at slot +0x98 (releasing the +0xa0 word).
 * Confidence: high */
cl4_result_t cL4_notif_slot98_getpair(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cl4_result_t r;
    cL4_slot_lock((void *)(obj + 0x98), scratch);
    cL4_slot_commit((void *)(obj + 0x98), scratch, 0, 0);
    r = *(cl4_result_t *)(obj + 0x98);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0xa0));
    return r;
}

/* FUN_000bfe44 @ 0x000bfe44   (est. cL4_notif_slot98_setpair)
 * Setter for the two-word slot +0x98 (param_1, param_2), releasing old.
 * Confidence: high */
void cL4_notif_slot98_setpair(unsigned long param_1, unsigned long param_2)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x98));
    old = *(unsigned long *)(obj + 0xa0);
    *(unsigned long *)(obj + 0x98) = param_1;
    *(unsigned long *)(obj + 0xa0) = param_2;
    cL4_ref_release((void *)old);
}

/* FUN_000bfe8c @ 0x000bfe8c   (est. cL4_notif_slot98_token) */
cl4_result_t cL4_notif_slot98_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x98), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x98), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x98;
    return r;
}

/* FUN_000bfed8 @ 0x000bfed8   (est. cL4_notif_slot_a8_get)
 * Returns the raw word at slot +0xa8 (after lock/commit).
 * Confidence: high */
unsigned long cL4_notif_slot_a8_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0xa8), scratch);
    cL4_slot_commit((void *)(obj + 0xa8), scratch, 0, 0);
    return *(unsigned long *)(obj + 0xa8);
}

/* FUN_000bff08 @ 0x000bff08   (est. cL4_notif_slot_a8_set)
 * Stores param_1 into slot +0xa8 (no release).
 * Confidence: high */
void cL4_notif_slot_a8_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cL4_slot_prepare((void *)(obj + 0xa8));
    *(unsigned long *)(obj + 0xa8) = param_1;
}

/* FUN_000bff3c @ 0x000bff3c   (est. cL4_notif_slot_b0_get) */
void cL4_notif_slot_b0_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0xb0), scratch);
    cL4_slot_commit((void *)(obj + 0xb0), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0xb0));
}

/* FUN_000bff70 @ 0x000bff70   (est. cL4_notif_slot_b0_set) */
void cL4_notif_slot_b0_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0xb0));
    old = *(unsigned long *)(obj + 0xb0);
    *(unsigned long *)(obj + 0xb0) = param_1;
    cL4_ref_release((void *)old);
}

/* FUN_000bffac @ 0x000bffac   (est. cL4_notif_slot_b0_token) */
cl4_result_t cL4_notif_slot_b0_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0xb0), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0xb0), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0xb0;
    return r;
}

/* FUN_000bfff8 @ 0x000bfff8   (est. cL4_notif_slot_b8_get) */
void cL4_notif_slot_b8_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0xb8), scratch);
    cL4_slot_commit((void *)(obj + 0xb8), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0xb8));
}

/* FUN_000c002c @ 0x000c002c   (est. cL4_notif_slot_b8_set) */
void cL4_notif_slot_b8_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0xb8));
    old = *(unsigned long *)(obj + 0xb8);
    *(unsigned long *)(obj + 0xb8) = param_1;
    cL4_ref_release((void *)old);
}

/* FUN_000c0068 @ 0x000c0068   (est. cL4_notif_slot_b8_token) */
cl4_result_t cL4_notif_slot_b8_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0xb8), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0xb8), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0xb8;
    return r;
}

/* FUN_000c00b4 @ 0x000c00b4   (est. cL4_notif_slot_c0_get)
 * Returns the 16-byte pair at slot +0xc0 (after lock/commit).
 * Confidence: high */
cl4_result_t cL4_notif_slot_c0_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0xc0), scratch);
    cL4_slot_commit((void *)(obj + 0xc0), scratch, 0, 0);
    return *(cl4_result_t *)(obj + 0xc0);
}

/* FUN_000c00e8 @ 0x000c00e8   (est. cL4_notif_slot_c0_set)
 * Writes a 24-byte triple at slot +0xc0 (words +0xc0/+0xc8, byte +0xd0).
 * Confidence: high */
void cL4_notif_slot_c0_set(unsigned long param_1, unsigned long param_2,
                           unsigned char param_3)
{
    unsigned long obj = 0; /* unaff_x20 */
    cL4_slot_prepare((void *)(obj + 0xc0));
    *(unsigned long *)(obj + 0xc0) = param_1;
    *(unsigned long *)(obj + 0xc8) = param_2;
    *(unsigned char *)(obj + 0xd0) = param_3;
}

/* FUN_000c0130 @ 0x000c0130   (est. cL4_notif_slot_c0_token) */
cl4_result_t cL4_notif_slot_c0_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0xc0), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0xc0), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0xc0;
    return r;
}

/* FUN_000c017c @ 0x000c017c   (est. cL4_notif_slot_d8_get)
 * Returns the 16-byte pair at slot +0xd8; also invokes the release helper
 * FUN_000c01dc on the three words stored at +0xd8/+0xe0/+0xe8.
 * Confidence: high */
cl4_result_t cL4_notif_slot_d8_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cl4_result_t r;
    cL4_slot_lock((void *)(obj + 0xd8), scratch);
    cL4_slot_commit((void *)(obj + 0xd8), scratch, 0, 0);
    r = *(cl4_result_t *)(obj + 0xd8);
    cL4_notif_slot_d8_release(*(unsigned long *)*(unsigned long *)(obj + 0xd8),
                              *(unsigned long *)(obj + 0xe0),
                              *(unsigned long *)(obj + 0xe8));
    return r;
}

/* FUN_000c01dc @ 0x000c01dc   (est. cL4_notif_slot_d8_release)
 * Ghidra: void FUN_000c01dc(long param_1, undefined8 param_2)
 * If the first word (param_1) is nonzero, releases the stored references
 * (FUN_0036b270 twice on param_1 and param_2).
 * Confidence: high */
void cL4_notif_slot_d8_release(long param_1, unsigned long param_2, unsigned long param_3)
{
    (void)param_3;
    if (param_1 != 0) {
        cL4_ref_release2((void *)0);
        cL4_ref_release2((void *)param_2);
    }
}

/* FUN_000c0210 @ 0x000c0210   (est. cL4_notif_slot_d8_set)
 * Writes a 24-byte triple at slot +0xd8 (words +0xd8/+0xe0/+0xe8) after
 * preparing, releasing the previous triple via FUN_000c0264.
 * Confidence: high */
void cL4_notif_slot_d8_set(unsigned long param_1, unsigned long param_2,
                           unsigned long param_3)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long o1, o2, o3;
    cL4_slot_prepare((void *)(obj + 0xd8));
    o1 = *(unsigned long *)(obj + 0xd8);
    o2 = *(unsigned long *)(obj + 0xe0);
    o3 = *(unsigned long *)(obj + 0xe8);
    *(unsigned long *)(obj + 0xd8) = param_1;
    *(unsigned long *)(obj + 0xe0) = param_2;
    *(unsigned long *)(obj + 0xe8) = param_3;
    cL4_notif_slot_d8_release2(o1, o2, o3);
}

/* FUN_000c0264 @ 0x000c0264   (est. cL4_notif_slot_d8_release2)
 * If the first word is nonzero, releases the three stored references
 * (FUN_0036b118 twice).
 * Confidence: high */
void cL4_notif_slot_d8_release2(long param_1, unsigned long param_2,
                                unsigned long param_3)
{
    if (param_1 != 0) {
        cL4_ref_release((void *)0);
        cL4_ref_release((void *)param_2);
    }
    (void)param_3;
}

/* FUN_000c0298 @ 0x000c0298   (est. cL4_notif_slot_d8_token) */
cl4_result_t cL4_notif_slot_d8_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0xd8), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0xd8), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0xd8;
    return r;
}

/* FUN_000c02e4 @ 0x000c02e4   (est. cL4_notif_slot_f0_get)
 * Returns the 16-byte pair at slot +0xf0.
 * Confidence: high */
cl4_result_t cL4_notif_slot_f0_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0xf0), scratch);
    cL4_slot_commit((void *)(obj + 0xf0), scratch, 0, 0);
    return *(cl4_result_t *)(obj + 0xf0);
}

/* FUN_000c0318 @ 0x000c0318   (est. cL4_notif_slot_f0_set)
 * Writes a 24-byte triple at slot +0xf0.
 * Confidence: high */
void cL4_notif_slot_f0_set(unsigned long param_1, unsigned long param_2,
                           unsigned char param_3)
{
    unsigned long obj = 0; /* unaff_x20 */
    cL4_slot_prepare((void *)(obj + 0xf0));
    *(unsigned long *)(obj + 0xf0) = param_1;
    *(unsigned long *)(obj + 0xf8) = param_2;
    *(unsigned char *)(obj + 0x100) = param_3;
}

/* FUN_000c0360 @ 0x000c0360   (est. cL4_notif_slot_f0_token) */
cl4_result_t cL4_notif_slot_f0_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0xf0), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0xf0), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0xf0;
    return r;
}

/* FUN_000c03ac @ 0x000c03ac   (est. cL4_notif_slot118_get)
 * Returns the byte at slot +0x118 (after lock/commit).
 * Confidence: high */
unsigned char cL4_notif_slot118_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x118), scratch);
    cL4_slot_commit((void *)(obj + 0x118), scratch, 0, 0);
    return *(unsigned char *)(obj + 0x118);
}

/* FUN_000c03dc @ 0x000c03dc   (est. cL4_notif_slot118_set)
 * Stores a byte at slot +0x118.
 * Confidence: high */
void cL4_notif_slot118_set(unsigned char param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cL4_slot_prepare((void *)(obj + 0x118));
    *(unsigned char *)(obj + 0x118) = param_1;
}

/* FUN_000c0410 @ 0x000c0410   (est. cL4_notif_slot118_token) */
cl4_result_t cL4_notif_slot118_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x118), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x118), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x118;
    return r;
}

/* FUN_000c045c @ 0x000c045c   (est. cL4_notif_slot178_get) */
void cL4_notif_slot178_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x178), scratch);
    cL4_slot_commit((void *)(obj + 0x178), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x178));
}

/* FUN_000c0490 @ 0x000c0490   (est. cL4_notif_slot178_set) */
void cL4_notif_slot178_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x178));
    old = *(unsigned long *)(obj + 0x178);
    *(unsigned long *)(obj + 0x178) = param_1;
    cL4_ref_release((void *)old);
}

/* FUN_000c04cc @ 0x000c04cc   (est. cL4_notif_slot178_token)
 * Token getter returning {&LAB_0006f910, obj+0x178}.
 * Confidence: high */
cl4_result_t cL4_notif_slot178_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x178), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x178), (void *)param_1, 0, 0);
    r.lo = 0x6f910; r.hi = obj + 0x178;
    return r;
}

/* FUN_000c0518 @ 0x000c0518   (est. cL4_notif_collect_caps)
 * Ghidra: long FUN_000c0518(void)
 * Collects capability entries from the object set at slot +0x130 into the
 * notification's +0x20 array. For each entry whose kind word (at the slot
 * header) is not the empty/cap-kind sentinels (0x651ba0/0x64fcb0/0x652dc0),
 * it copies the descriptor word (+0x10 or +0x18) into a growing result list
 * at +0x20 of the notification object, releasing intermediates.
 * Confidence: low
 * Notes: Bit-vector style iteration over a cap table (object +0x10 = count,
 * entries stride 0x10 from +0x20). */
long cL4_notif_collect_caps(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long set, cnt, i, j, k, idx;
    unsigned long *slot;
    unsigned long v;

    cL4_slot_lock((void *)(obj + 0x130), scratch24);
    cL4_slot_commit((void *)(obj + 0x130), scratch24, 0, 0);
    set = *(unsigned long *)(obj + 0x130);
    cL4_current();
    cnt = *(unsigned long *)(set + 0x10);
    cL4_ref_release2((void *)set);
    i = 0;
    while (1) {
        k = i * 0x10 + 0x20;
        j = i;
        do {
            i = j + 1;
            if (i - cnt == 1) {
                cL4_ref_release((void *)set);
                return obj;
            }
            if (*(unsigned long *)(set + 0x10) <= j)
                __builtin_trap();
            slot = (unsigned long *)(set + k);
            if (*(unsigned long *)*slot == 0x651ba0 ||
                *(unsigned long *)*slot == 0x64fcb0) {
                k = 0x10;
                goto pick;
            }
            k += 0x10;
            j = i;
        } while (*(unsigned long *)*slot != 0x652dc0);
        k = 0x18;
    pick:
        v = *(unsigned long *)((unsigned long)*slot + k);
        cL4_ref_release2((void *)v);
        cL4_vec_grow2();
        idx = *(unsigned long *)(obj + 0x10);
        if (*(unsigned long *)(obj + 0x18) >> 1 <= idx) {
            cL4_vec_grow_cap();
            cL4_vec_grow((void *)0, idx + 1, 1);
        }
        *(unsigned long *)(obj + 0x10) = idx + 1;
        *(unsigned long *)(obj + idx * 8 + 0x20) = v;
    }
}

/* FUN_000c066c @ 0x000c066c   (est. cL4_notif_collect_vm_caps)
 * Ghidra: long FUN_000c066c(void)
 * Like FUN_000c0518 but collects only entries whose kind word equals
 * 0x650e98 (a specific capability kind), taking the descriptor word at
 * +0x18 of the entry. Returns the notification object with the collected
 * list.
 * Confidence: low */
long cL4_notif_collect_vm_caps(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long set, cnt, i, j, k, idx;
    long *slot;
    unsigned long v;

    cL4_slot_lock((void *)(obj + 0x130), scratch24);
    cL4_slot_commit((void *)(obj + 0x130), scratch24, 0, 0);
    set = *(unsigned long *)(obj + 0x130);
    cL4_current();
    cnt = *(unsigned long *)(set + 0x10);
    cL4_ref_release2((void *)set);
    i = 0;
    while (1) {
        k = i * 0x10 + 0x20;
        do {
            if (cnt == i) {
                cL4_ref_release((void *)set);
                return obj;
            }
            if (*(unsigned long *)(set + 0x10) <= i)
                __builtin_trap();
            slot = (long *)(set + k);
            k += 0x10;
            i += 1;
        } while (*(long *)*slot != 0x650e98);
        k = ((long *)*slot)[2];
        v = (unsigned long)k;
        cL4_ref_release2((void *)v);
        cL4_vec_grow2();
        idx = *(unsigned long *)(obj + 0x10);
        if (*(unsigned long *)(obj + 0x18) >> 1 <= idx) {
            cL4_vec_grow_cap();
            cL4_vec_grow((void *)0, idx + 1, 1);
        }
        *(unsigned long *)(obj + 0x10) = idx + 1;
        *(long *)(obj + idx * 8 + 0x20) = (long)v;
    }
}

/* FUN_000c077c @ 0x000c077c   (est. cL4_notif_slot1b8_get) */
void cL4_notif_slot1b8_get(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[24];
    cL4_slot_lock((void *)(obj + 0x1b8), scratch);
    cL4_slot_commit((void *)(obj + 0x1b8), scratch, 0, 0);
    cL4_ref_release2((void *)*(unsigned long *)(obj + 0x1b8));
}

/* FUN_000c07b0 @ 0x000c07b0   (est. cL4_notif_slot1b8_set) */
void cL4_notif_slot1b8_set(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long old;
    cL4_slot_prepare((void *)(obj + 0x1b8));
    old = *(unsigned long *)(obj + 0x1b8);
    *(unsigned long *)(obj + 0x1b8) = param_1;
    cL4_ref_release((void *)old);
}

/* FUN_000c07ec @ 0x000c07ec   (est. cL4_notif_slot1b8_token) */
cl4_result_t cL4_notif_slot1b8_token(unsigned long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    cl4_result_t r;
    cL4_slot_token((void *)(obj + 0x1b8), (void *)param_1);
    cL4_slot_commit((void *)(obj + 0x1b8), (void *)param_1, 0, 0);
    r.lo = 0x7bf58; r.hi = obj + 0x1b8;
    return r;
}

/* FUN_000c0848 @ 0x000c0848   (est. cL4_vm_descriptor)
 * Ghidra: undefined8 FUN_000c0848(11 args)
 * Allocates a descriptor of kind FUN_0036a940(), then forwards all 11 args
 * to FUN_000c08f8 to populate it. Returns the descriptor.
 * Confidence: low */
unsigned long cL4_vm_descriptor(unsigned long p1, unsigned long p2,
                                unsigned long p3, unsigned long p4,
                                unsigned long p5, unsigned long p6,
                                unsigned long p7, unsigned long p8,
                                unsigned char p9, unsigned long p10,
                                unsigned long p11)
{
    unsigned long d = cL4_msg_field(0, 0, 0);
    cL4_vm_init(d, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
    return d;
}

/* FUN_000c08f8 @ 0x000c08f8   (est. cL4_vm_init)
 * Ghidra: void FUN_000c08f8(byte param_1, 11 args)
 * Initializes a VM/notification descriptor object at unaff_x20 from the 11
 * parameters: allocates object lists (+0x10, +0x50), descriptor fields
 * (+0x38/+0x40/+0x48 via FUN_001f0130), sets up the name/type words and the
 * slot triplets at fixed offsets, stores the caller params into +0x18..+0x1d0,
 * and depending on the type flag param_1 computes a checksum (release path)
 * or locks/commits the fields and computes a checksum from the field copy.
 * Confidence: low
 * Notes: unaff_x24 is a second implicit register; huge object layout. */
void cL4_vm_init(unsigned char param_1, unsigned long p2, unsigned long p3,
                 unsigned long p4, unsigned long p5, unsigned long p6,
                 unsigned long p7, unsigned long p8, unsigned long p9,
                 unsigned char p9hi, unsigned long p10, unsigned long p11)
{
    unsigned long obj = 0;     /* unaff_x20 */
    unsigned long x24 = 0;     /* unaff_x24 */
    unsigned long list, v, a, b, c;
    unsigned char scratch_c8[32], scratch_a8[40], scratch_80[32];

    cL4_list_begin();
    list = (unsigned long)cL4_list_new(0x10);
    *(unsigned long *)(list + 0x10) = cL4_list_alloc();
    *(unsigned long *)(obj + 0x10) = list;
    cL4_list_begin();
    *(unsigned long *)(obj + 0x38) = cL4_descriptor(0, 0, 0x677790, 0x6718b8);
    *(unsigned long *)(obj + 0x40) = cL4_descriptor(0, 0, 0x6753a0, 0x6718b8);
    a = cL4_intern((const char *)0x64e1e8, (void *)0x4c2470);
    cL4_desc_register(a, a, a);
    v = cL4_descriptor(0, 0, 0, 0);
    cL4_cap_small_alloc(0);
    list = (unsigned long)cL4_list_new(0x10);
    *(unsigned long *)(list + 0x10) = v;
    *(unsigned long *)(obj + 0x50) = list;
    *(unsigned long *)(obj + 0x90) = x24;
    *(unsigned long *)(obj + 0xa8) = 0;
    *(unsigned long *)(obj + 0xb0) = x24;
    *(unsigned long *)(obj + 0xc0) = 0;
    *(unsigned long *)(obj + 0xc8) = 0;
    *(unsigned long *)(obj + 0xb8) = 0;
    *(unsigned char *)(obj + 0xd0) = 1;
    *(unsigned long *)(obj + 0xe0) = 0;
    *(unsigned long *)(obj + 0xd8) = 0;
    *(unsigned long *)(obj + 0xf0) = 0;
    *(unsigned long *)(obj + 0xe8) = 0;
    *(unsigned long *)(obj + 0xf8) = 0;
    *(unsigned char *)(obj + 0x100) = 1;
    *(unsigned long *)(obj + 0x110) = x24;
    v = cL4_obj_alloc(0);
    cL4_desc_register(v, 0);
    *(unsigned long *)(obj + 0x120) = cL4_descriptor(0, 0, v, 0x6718b8);
    cL4_alloc_free(v);
    list = (unsigned long)cL4_msg_field(0, 0, 0);
    *(unsigned long *)(list + 0x10) = cL4_descriptor(0, 0, 0, 0);
    *(unsigned long *)(list + 0x18) = x24;
    *(unsigned long *)(obj + 0x128) = list;
    *(unsigned long *)(obj + 0x130) = x24;
    *(unsigned long *)(obj + 0x138) = x24;
    a = cL4_intern((const char *)0x64e1f0, (void *)0x4bf1b0);
    cL4_desc_field();
    v = cL4_descriptor(0, 0, 0, 0);
    *(unsigned long *)(obj + 0x1b8) = 0;
    *(unsigned long *)(obj + 0x1c8) = 0;
    *(unsigned long *)(obj + 0x178) = 0;
    *(unsigned long *)(obj + 0x180) = 0;
    *(unsigned long *)(obj + 0x170) = v;
    *(unsigned char *)(obj + 0x1d0) = 1;
    *(unsigned char *)(obj + 0x18) = param_1;
    *(unsigned long *)(obj + 0x20) = p2;
    *(unsigned long *)(obj + 0x28) = p3;
    *(unsigned long *)(obj + 0x30) = 0x6672b8;
    *(unsigned long *)(obj + 0x58) = p4;
    cL4_get_pair((void *)p5, (void *)(obj + 0x60));
    *(unsigned long *)(obj + 0x88) = p6;
    *(unsigned long *)(obj + 0x98) = p7;
    *(unsigned long *)(obj + 0xa0) = p8;
    *(unsigned char *)(obj + 0x118) = p9hi;
    *(unsigned char *)(obj + 0x140) = (unsigned char)p9;
    cL4_field_begin();
    cL4_str_field((void *)p10, (void *)(obj + 0x148), 0, 0);
    cL4_field_begin2();
    cL4_str_field((void *)p11, (void *)(obj + 0x188), 0, 0);
    if ((param_1 & 1) == 0) {
        cL4_write_mark(0);
        cL4_bv_resize(0, 0, 0);
        cL4_ref_release2((void *)0);
        cL4_ref_release2((void *)p3);
        cL4_ref_release2((void *)p4);
        cL4_ref_release2((void *)p6);
        cL4_ref_release2((void *)p8);
        v = cL4_obj_checksum();
    } else {
        cL4_slot_lock((void *)(obj + 0x60), scratch_c8);
        cL4_slot_commit((void *)(obj + 0x60), scratch_c8, 0, 0);
        cL4_get_pair((void *)(obj + 0x60), scratch_a8);
        cL4_write_mark(0);
        cL4_bv_resize(0, 0, 0);
        cL4_ref_release2((void *)0);
        cL4_ref_release2((void *)p3);
        cL4_ref_release2((void *)p4);
        cL4_ref_release2((void *)p6);
        cL4_ref_release2((void *)p8);
        v = cL4_obj_checksum2(scratch_a8);
    }
    *(unsigned long *)(obj + 0x1c0) = v;
    cL4_slot_lock((void *)(obj + 0x60), scratch_80);
    cL4_slot_commit((void *)(obj + 0x60), scratch_80, 0, 0);
    cL4_get_pair((void *)(obj + 0x60), scratch_a8);
    v = cL4_type_class(0);
    cL4_msg_field(v, 0x48, 7);
    *(unsigned long *)(obj + 0x108) = cL4_type_class2(scratch_a8);
    cL4_slot_lock((void *)(obj + 0x28), scratch_a8);
    cL4_slot_commit((void *)(obj + 0x28), scratch_a8, 0, 0);
    b = *(unsigned long *)(obj + 0x28);
    c = *(unsigned long *)(obj + 0x30);
    v = (unsigned long)cL4_ref_release2((void *)b);
    c = cL4_name_hash(v, c);
    cL4_ref_release((void *)p2);
    cL4_ref_release((void *)p3);
    cL4_ref_release((void *)p4);
    cL4_ref_release((void *)p6);
    cL4_ref_release((void *)p8);
    cL4_ref_release((void *)b);
    cL4_field_end();
    cL4_fmt((void *)p11, 0, 0);
    cL4_list_finalize();
    cL4_fmt((void *)p10, 0, 0);
    cL4_field_free((void *)p5);
    *(unsigned long *)(obj + 0x1b0) = c;
}

/* FUN_000c0e48 @ 0x000c0e48   (est. cL4_vm_set_vm_list)
 * Ghidra: void FUN_000c0e48(undefined8 param_1, undefined8 param_2)
 * Replaces the VM list at slot +0x120: commits the slot, if the given
 * descriptor (param_2) has no matching entry (FUN_000a0420 == 0) then
 * allocates a fresh list descriptor and interns a field name; releases the
 * old value, then validates the +0x60 field and emits a descriptor-commit
 * record into param_1.
 * Confidence: low */
void cL4_vm_set_vm_list(unsigned long param_1, unsigned long param_2)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch_80[24], scratch_58[24];
    unsigned long list, val, old, x, local_68, u60, v2;

    cL4_slot_commit((void *)(obj + 0x120), scratch_80, 0x20, 0);
    list = cL4_desc_cmp(param_2, *(unsigned long *)(obj + 0x120));
    cL4_slot_done(scratch_80);
    if (list == 0) {
        val = cL4_obj_alloc(0);
        list = cL4_msg_field(val, 0x20, 7);
        x = cL4_descriptor(0x65778, 0x65f2f0, 0x677830, 0x65f190);
        *(unsigned long *)(list + 0x10) = x;
        *(unsigned long *)(list + 0x18) = 0x65778;
    }
    cL4_slot_commit((void *)(obj + 0x120), scratch_80, 0x21, 0);
    old = (unsigned long)cL4_ref_release2((void *)list);
    cL4_desc_commit2(old, param_2);
    cL4_slot_done(scratch_80);
    cL4_slot_commit((void *)(obj + 0x60), scratch_58, 0, 0);
    cL4_get_pair((void *)(obj + 0x60), scratch_80);
    local_68 = cL4_field_value(scratch_80, *(unsigned long *)(obj + 0x60));
    u60 = 0;
    v2 = cL4_field_value(scratch_80, local_68);
    cL4_desc_commit((void *)param_1, (void *)list, local_68, u60, v2);
    cL4_ref_release((void *)list);
    cL4_field_free(scratch_80);
}

/* FUN_000c0f94 @ 0x000c0f94   (est. cL4_notif_teardown)
 * Ghidra: void FUN_000c0f94(void)
 * Destroys/releases every field of a notification object (unaff_x20). Walks
 * the object list at +0x110 releasing each stored capability, then releases
 * all scalar/object slots at +0x10..+0x1c0 in a fixed sequence, finalizing
 * the string fields at +0x148/+0x188 and the field buffers.
 * Confidence: low
 * Notes: Long sequence of per-offset releases (mirror of cL4_vm_init writes). */
void cL4_notif_teardown(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long list, cnt, i, v;
    unsigned char scratch_68[24], scratch_80[24], scratch_a8[24];

    cL4_slot_lock((void *)(obj + 0x110), scratch_68);
    cL4_slot_commit((void *)(obj + 0x110), scratch_68, 0, 0);
    list = *(unsigned long *)(obj + 0x110);
    cnt = *(unsigned long *)(list + 0x10);
    if (cnt != 0) {
        cL4_ref_release2((void *)list);
        cL4_slot_lock((void *)(obj + 0x60), scratch_80);
        cL4_slot_commit((void *)(obj + 0x60), scratch_80, 0, 0);
        for (i = 0x20; cnt != 0; cnt -= 1) {
            v = *(unsigned long *)(list + i);
            cL4_get_pair((void *)(obj + 0x60), scratch_a8);
            cL4_field_copy(scratch_a8, *(unsigned long *)(obj + 0x60));
            cL4_field_new();
            cL4_collect_release((void *)v);
            i += 8;
        }
        cL4_ref_release((void *)list);
    }
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x10));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x20));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x28));
    cL4_obj_free((void *)*(unsigned long *)(obj + 0x38));
    cL4_obj_free((void *)*(unsigned long *)(obj + 0x40));
    cL4_obj_free((void *)*(unsigned long *)(obj + 0x48));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x50));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x58));
    cL4_field_free((void *)(obj + 0x60));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x88));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x90));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0xa0));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0xb0));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0xb8));
    cL4_notif_slot_d8_release2(*(unsigned long *)(obj + 0xd8),
                               *(unsigned long *)(obj + 0xe0),
                               *(unsigned long *)(obj + 0xe8));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x108));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x110));
    cL4_obj_free((void *)*(unsigned long *)(obj + 0x120));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x128));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x130));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x138));
    cL4_list_finalize();
    cL4_fmt((void *)(obj + 0x148), 0, 0);
    cL4_obj_free((void *)*(unsigned long *)(obj + 0x170));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x178));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x180));
    cL4_field_end();
    cL4_fmt((void *)(obj + 0x188), 0, 0);
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x1b0));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x1b8));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x1c0));
}

/* FUN_000c1164 @ 0x000c1164   (est. cL4_notif_release_a)
 * Ghidra: void FUN_000c1164(void)
 * Tear down the notification object then release the capability reference.
 * Confidence: low */
void cL4_notif_release_a(void)
{
    cL4_notif_teardown();
    cL4_cap_release((void *)0, 0, 7);
}

/* FUN_000c1168 @ 0x000c1168   (est. cL4_notif_release_b)
 * Ghidra: void FUN_000c1168(void)
 * Tear down the notification object then release the capability reference.
 * Confidence: low */
void cL4_notif_release_b(void)
{
    cL4_notif_teardown();
    cL4_cap_release((void *)0, 0, 7);
}

/* FUN_000c118c @ 0x000c118c   (est. cL4_vm_create)
 * Ghidra: undefined8 FUN_000c118c(uint param_1, 11 args)
 * Creates a new VM notification object: resolves the owner via FUN_000c1330,
 * computes a "suppress" flag from the current launch mode, copies the caller
 * field values, releases the passed-in capability references, and calls
 * FUN_000c08f8 to initialize the object with the type flag param_1&1.
 * Returns the new descriptor.
 * Confidence: low */
unsigned long cL4_vm_create(unsigned int param_1, unsigned long p2, unsigned long p3,
                            unsigned long p4, unsigned long p5, unsigned long p6,
                            unsigned long p7, unsigned long p8, unsigned long p9,
                            unsigned char p9hi, unsigned long p10, unsigned long p11)
{
    unsigned long owner, d;
    unsigned char scratch_e0[40], scratch_108[40], scratch_130[40];
    unsigned char local_b8[88];
    unsigned char sup;

    owner = cL4_vm_owner(p2, p4, p3, &p11);
    if (cL4_os4() == 2)
        sup = 0;
    else
        sup = (unsigned char)((cL4_cmp_strings(local_b8, 0, 0, 0) ^ 0xff) & 1);
    cL4_get_pair((void *)p5, scratch_e0);
    cL4_field_begin();
    cL4_str_field((void *)p9, scratch_108, 0, 0);
    cL4_field_begin2();
    cL4_str_field((void *)p10, scratch_130, 0, 0);
    d = cL4_msg_field(0, 0, 0);
    cL4_ref_release2((void *)p4);
    cL4_ref_release2((void *)p3);
    cL4_ref_release2((void *)p2);
    cL4_ref_release2((void *)p7);
    cL4_vm_init((unsigned char)(param_1 & 1), owner, p4, p3, (unsigned long)scratch_e0,
                p2, p6, p7, sup, p9hi, (unsigned long)scratch_108, (unsigned long)scratch_130);
    return d;
}

/* FUN_000c1330 @ 0x000c1330   (est. cL4_vm_owner_resolve)
 * Ghidra: long * FUN_000c1330(long *param_1, undefined8 param_2, long param_3,
 *                             long *param_4)
 * Resolves the owning component/artifact for a VM. If param_4 (owner) is
 * null, searches the launch component list (vtable+0x88 getter) for the
 * broker artifact (name 0x11000529b94c7909); if absent, fatally logs
 * "Unable to get broker artifact". Otherwise walks the DER component graph
 * (vtable+0x70) for an artifact named "brkr_art"/"ifact" and resolves the
 * slide/MachoFiles descriptor range for the component at param_3+0x30,
 * returning the resolved artifact node. A non-null param_4 is returned
 * directly after releasing a reference.
 * Confidence: high (verified vs decompile+disasm 2026-08-12; FIXED control flow:
 *   broker-search loop now falls through to resolve_range with lVar1=0 instead
 *   of fatalling; subwalk-match now goes through commit getter+0x88/+0xa0 + bounds
 *   (SW 0xc16ac/0xc16b0) before resolve_range; only subwalk exhaustion fatals)
 * Notes: DER-component graph walk; strings s_Unable_to_get_broker_artifact,
 *   s_slideMachoFiles___asDescriptor; vtable offsets 0x78/0x70/0x88/0xa8/0xa0/0x80. */
long *cL4_vm_owner_resolve(long *param_1, unsigned long param_2, long param_3,
                           long *param_4)
{
    long *list, *node, *art;
    unsigned long cnt, i, v, lv2;
    unsigned char scratch[24];

    if (param_4 != 0) {
        cL4_ref_release2((void *)param_4);
        return param_4;
    }

    /* Top-level broker-artifact search over the launch-component list */
    list = (long *)(*(long (**)(void))cL4_vtbl7((unsigned long)*param_1))();   /* vtable+0x88 */
    cnt = *(unsigned long *)(list + 0x10);
    for (i = 0; cnt != i; i++) {
        if (*(unsigned long *)(list + 0x10) <= i)
            __builtin_trap();               /* SW 0xc16a0 */
        node = *(long **)(list + i * 8 + 0x20);
        v = (unsigned long)(*(long (**)(void))(*node + 0x78))();
        cL4_ref_release2((void *)node);
        cL4_slot_commit((void *)0x6509b8, scratch, 0, 0);
        if (v == 0x11000529b94c7909) {
            cL4_ref_release((void *)list);
            list = (long *)(*(long (**)(void))(*node + 0xa8))();   /* get sub-list */
            i = 0;
            cnt = *(unsigned long *)(list + 0x10);
            goto subwalk;
        }
        cL4_ref_release((void *)node);
    }
    /* Broker artifact NOT in top-level list: fall through to resolve_range
     * (decompile LAB_000c158c) with lVar1=0, lVar2=*(param_3+0x38) */
    cL4_ref_release((void *)list);
    list = 0;
    lv2 = *(unsigned long *)(param_3 + 0x38);
    goto resolve_range;

subwalk:
    for (; cnt != i; i++) {
        if (*(unsigned long *)(list + 0x10) <= i)
            __builtin_trap();               /* SW 0xc16a4 */
        art = *(long **)(list + i * 8 + 0x20);
        v = (unsigned long)(*(long (**)(void))(*art + 0x70))();
        cL4_ref_release2((void *)art);
        lv2 = v;                            /* auVar12 hi word */
        if (v == 0x7472615f726b7262ull && lv2 == 0xed00007463616669ull) { /* "brkr_art"/"ifact" */
            cL4_ref_release((void *)list);
            goto commit;
        }
        if ((cL4_name_match(v, lv2, 0x7472615f726b7262, 0xed00007463616669, 0) & 1) != 0) {
            cL4_ref_release((void *)list);
            goto commit;
        }
        cL4_ref_release((void *)art);
    }
    /* subwalk exhausted (decompile LAB_000c16b0) */
    cL4_ref_release((void *)list);
    cL4_fatal_noreturn();   /* "Unable to get broker artifact" */

commit:  /* decompile LAB_000c1538 */
    list = (long *)(*(long (**)(void))(*art + 0x88))();
    if (list < 0)
        __builtin_trap();                   /* SW 0xc16ac */
    lv2 = (unsigned long)(*(long (**)(void))(*art + 0xa0))();
    cL4_ref_release((void *)node);
    cL4_ref_release((void *)art);
    if (lv2 < 0)
        __builtin_trap();                   /* SW 0xc16b0 */
    /* fall through to resolve_range */

resolve_range:  /* decompile LAB_000c158c */
    if (*(unsigned long *)(param_3 + 0x30) == 0)
        cL4_fatal_noreturn();   /* s_slideMachoFiles___asDescriptor */
    if (lv2 < 0)
        __builtin_trap();                   /* SW 0xc16a8 */
    node = (long *)cL4_os3((void *)(*(unsigned long *)(param_3 + 0x30) + (unsigned long)list));
    v = (unsigned long)node + 0x20;
    cL4_ref_release((void *)node);
    cL4_ref_release2((void *)(v & ~0xf));
    cL4_cap_small_alloc(0);
    cL4_msg_field((unsigned long)node, 0x88, 7);
    cL4_ref_release2((void *)cL4_os6());
    art = (long *)cL4_os5(cL4_os6());
    v = (unsigned long)(*(long (**)(void))(*art + 0x80))();
    cL4_ref_release2((void *)0);
    v = cL4_dg_desc(v, param_2);
    cL4_ref_release((void *)v);
    (*(void (**)(unsigned long))(*art + 0x88))(v);
    cL4_ref_release((void *)cL4_os6());
    cL4_ref_release((void *)art);
    return art;
}

/* FUN_000c1784 @ 0x000c1784   (est. cL4_vm_cmp_components)
 * Ghidra: bool FUN_000c1784(undefined8 *param_1, undefined8 *param_2)
 * Compares two component nodes (*param_1, *param_2) for identity. Builds a
 * message object of class 0x651130/0x4c2650, fills it with the two nodes'
 * type words (vtable+0x88 getters compared via cL4_dg_cmp), then compares
 * their name/kind words (vtable+0xb8 getters compared via cL4_cmp_strings).
 * Returns true if the two 16-byte comparison results are both equal.
 * Confidence: low
 * Notes: Uses cL4_cmp_strings + cL4_dg_cmp; message object 0x651130. */
bool cL4_vm_cmp_components(unsigned long *param_1, unsigned long *param_2)
{
    long *n1 = (long *)*param_1;
    long *n2 = (long *)*param_2;
    unsigned char scratch[40];
    unsigned long msg;
    unsigned char t1, t2, r1, r2;

    msg = cL4_msg_alloc((void *)cL4_intern((const char *)0x651130, (void *)0x4c2650), scratch);
    t1 = cL4_dg_cmp((*(long (**)(void))(*n1 + 0x88))(), (*(long (**)(void))(*n2 + 0x88))());
    *(unsigned char *)(msg + 0x20) = t1;
    t2 = cL4_dg_cmp((*(long (**)(void))(*n1 + 0xb8))(), (*(long (**)(void))(*n2 + 0xb8))());
    *(unsigned char *)(msg + 0x21) = t2;
    r1 = cL4_cmp_strings((void *)msg, 0, 0x677880, 0x672138);
    return r1 == '\0';
}

/* FUN_000c18dc @ 0x000c18dc   (est. cL4_vm_index_artifacts)
 * Ghidra: undefined8 * FUN_000c18dc(long param_1)
 * Indexes the component list param_1 into a global artifact hash table
 * (DAT_006577d8 bitmap, DAT_006577c8 id array, DAT_006577d0 node array).
 * For each component (vtable+0x88 getter) it computes a hash slot via the
 * pseudo-random generator (FUN_00072710), interns a string (0x651120) and
 * either records a fresh entry (if the slot bit is clear) or appends the
 * component to an existing collision list. Returns the global node array
 * (&DAT_00657798) when the walk completes.
 * Confidence: low
 * Notes: Global hash-table state at DAT_006577a8/d8/c8/d0; FUN_00072710
 *   supplies the slot index. */
unsigned long *cL4_vm_index_artifacts(long param_1)
{
    long *node, *bucket;
    unsigned long cnt, i, idx, slot, v;
    unsigned char scratch16[16], scratch12[12];

    (void)scratch16; (void)scratch12;
    cnt = *(unsigned long *)(param_1 + 0x10);
    i = 0;
    while (1) {
        if (cnt == i) {
            cL4_ref_release((void *)param_1);
            return (unsigned long *)0x657798;
        }
        if (*(unsigned long *)(param_1 + 0x10) <= i)
            __builtin_trap();
        node = *(long **)(param_1 + i * 8 + 0x20);
        v = (*(long (**)(void))(*node + 0x88))();
        cL4_ref_release2((void *)node);
        slot = cL4_rng_state() & ~1;   /* FUN_00072710 low bits */
        cL4_intern((const char *)0x651120, (void *)0x4c2638);
        if ((cL4_os6() & 1) != 0) {   /* hash bit set */
            bucket = (long *)(0x6577d0 + slot * 8);
            cL4_vec_grow2();
            idx = *(unsigned long *)(*bucket + 0x10);
            if (*(unsigned long *)(*bucket + 0x18) >> 1 <= idx)
                cL4_vec_grow((void *)0, idx + 1, 1);
            *(unsigned long *)(*bucket + 0x10) = idx + 1;
            *(long **)(*bucket + idx * 8 + 0x20) = node;
        } else {
            idx = cL4_os3((void *)0x651120);   /* allocate record */
            *(unsigned long *)idx = v;   /* store key */
            *(long **)(idx + 0x20) = node;
            *(unsigned long *)(0x6577d0 + slot * 8) = idx;
        }
        i++;
    }
}

/* FUN_000c1af4 @ 0x000c1af4   (est. cL4_vm_set_parent)
 * Ghidra: void FUN_000c1af4(undefined8 param_1..param_4, long param_5)
 * Reads a field value out of param_5 and appends it as a descriptor
 * (4-word) to the record, wiring parent links.
 * Confidence: low */
void cL4_vm_set_parent(unsigned long p1, unsigned long p2, unsigned long p3,
                       unsigned long p4, long param_5)
{
    unsigned long val = cL4_field_value((void *)param_5, *(unsigned long *)(param_5 + 0x18));
    cL4_desc_append((void *)p1, (void *)p2, p3, p4, val);
}

/* FUN_000c1b6c @ 0x000c1b6c   (est. cL4_vm_bind_notification)
 * Ghidra: void FUN_000c1b6c(undefined8 param_1, undefined8 param_2, char param_3,
 *                           long *param_4)
 * Binds a notification (param_1/param_2) to the object param_4 unless
 * param_3==1 (already bound). When not bound and debug flag DAT_006add10
 * is set, emits a capability log record (0x20 kind); then allocates a small
 * descriptor, resolves a name via cL4_cls6, and dispatches through the
 * vtable+0x98 setter to attach it, releasing the temporary.
 * Confidence: low
 * Notes: DAT_006add10 debug gate; vtable+0x98 setter call. */
void cL4_vm_bind_notification(unsigned long param_1, unsigned long param_2,
                              char param_3, long *param_4)
{
    unsigned long scratch[72];
    unsigned long name, v;

    if (param_3 == '\x01')
        return;
    if (DAT_006add10 == '\x01') {
        v = cL4_intern((const char *)0x64c040, (void *)0x4bbf40);
        name = cL4_msg_alloc((void *)v, scratch);
        cL4_cap_log(name, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
        cL4_msg_release((void *)name);
        v = cL4_current_token();
        cL4_cap_release((void *)v, 0x20, 7);
    }
    v = cL4_cls5(0);
    cL4_msg_field(v, 0x28, 7);
    v = cL4_cls6((void *)param_1, (void *)param_2);
    /* vtable+0x98 setter: (*vtable[0x98/8])(v, 0x6624c0) */
    (*(void (**)(unsigned long, unsigned long))(*(unsigned long **)(*param_4 + 0x98))[0])(v, 0x6624c0);
    cL4_ref_release((void *)v);
}

/* FUN_000c1cd8 @ 0x000c1cd8   (est. cL4_vm_build_edges)
 * Ghidra: void FUN_000c1cd8(long param_1, long param_2, ulong param_3,
 *                           undefined8 param_4..param_8)
 * Builds the dependency edges of a VM/graph object. Iterates the source
 * component (param_2's +0x18/+0x20 words, or the object's +0x180 list),
 * and for each entry maps a 0x4000-byte chunk (param_3 + i*0x4000) through
 * the component's page table (vtable method calls resolved via the
 * FUN_0008da6c/FUN_000db808 trampolines), collecting the resulting frame
 * descriptors into a growing array (param_1 record). Releases intermediates.
 * Confidence: low
 * Notes: Large page-map walk; chunk stride 0x4000; bounds checked with
 *   SoftwareBreakpoint traps. */
void cL4_vm_build_edges(long param_1, long param_2, unsigned long param_3,
                        unsigned long param_4, unsigned long param_5,
                        unsigned int param_6, unsigned long param_7,
                        unsigned long param_8)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long src, chunk, v;
    long *rec, *list;

    (void)param_4; (void)param_5; (void)param_6; (void)param_7;
    if ((param_8 & 1) == 0) {
        src = *(unsigned long *)(param_2 + 0x18);
        chunk = *(unsigned long *)(param_2 + 0x20);
        cL4_field_value((void *)param_2, src);
        rec = (long *)cL4_vtbl2(chunk);   /* resolved map helper */
        list = (long *)cL4_vtbl3(chunk);  /* resolved edge helper */
        (void)rec; (void)list;
    } else {
        rec = *(long **)(obj + 0x180);
        if (rec == 0)
            __builtin_trap();
        chunk = *(unsigned long *)(obj + 0x130);
        v = *(unsigned long *)(rec + 0x10);
        if (v != 0) {
            /* walk each recorded frame; release list entry */
            cL4_ref_release((void *)rec);
            return;
        }
    }
    (void)v;
}

/* FUN_000c31d8 @ 0x000c31d8   (est. cL4_vm_desc_lookup)
 * Ghidra: void FUN_000c31d8(undefined8 *param_1, undefined8 param_2)
 * Looks up a descriptor for param_2 in the object's +0x38 map (via the
 * object list at +0x38). If found and the entry's kind class (cL4_kind_probe)
 * has its low bit set, loads the 0x70-byte record at +0x38+idx*0x70 and
 * returns it via *param_1 (after copying the descriptor field). Otherwise
 * zeroes the caller's 5-word result.
 * Confidence: low
 * Notes: Record stride 0x70; FUN_000a6840 load, FUN_000db184 apply. */
void cL4_vm_desc_lookup(unsigned long *param_1, unsigned long param_2)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned long map, idx;
    unsigned char scratch[24];
    unsigned char rec[104];
    unsigned long local_c0[2];
    cl4_result_t kind;

    cL4_vtbl_apply2((void *)(obj + 0x38), scratch);   /* FUN_000dbddc */
    map = *(unsigned long *)(obj + 0x38);
    if (*(long *)(map + 0x10) != 0) {
        kind = cL4_kind_probe((void *)param_2);
        if ((kind.hi & 1) != 0) {
            cL4_slot_load(&local_c0[0], (void *)(*(long *)(map + 0x38) + kind.lo * 0x70));
            if (local_c0[1] != 0) {
                cL4_slot_load2(rec, &local_c0[0]);
                cL4_vtbl_apply3(scratch);
                cL4_slot_done(scratch);
                cL4_get_pair((void *)rec, (void *)param_1);
                cL4_vtbl_apply((void *)rec, 0);
                return;
            }
        }
    }
    /* not found: zero the 5-word result */
    cL4_vtbl_apply3(scratch);
    cL4_slot_done(scratch);
    param_1[4] = 0; param_1[1] = 0; param_1[0] = 0;
    param_1[3] = 0; param_1[2] = 0;
}

/* FUN_000c32ac @ 0x000c32ac   (est. cL4_vm_find_kernel_component)
 * Ghidra: undefined8 FUN_000c32ac(void)
 * Locates the kernel component in the global component list (from the
 * object's +0x88 slot, vtable+0x88 getter) by name class, then walks its
 * DER component graph (vtable+0x70) for the kernel header component
 * (name 0x484f4843414d5f5f/"__MACHOHH"/"__MACHOH"), resolving its address
 * range from the component's +0x30 base, returning the computed end offset
 * via FUN_0010a528. On failure logs "Can't find kernel component" or
 * "Can't find kernel header" fatally.
 * Confidence: low
 * Notes: DER graph walk; s_Can_t_find_kernel_component_005c1ed0,
 *   s_Can_t_find_kernel_header_005c1ef0. */
unsigned long cL4_vm_find_kernel_component(void)
{
    unsigned long obj = 0; /* unaff_x20 */
    long *list, *node, *comp;
    unsigned long cnt, i, v, v2, base;
    unsigned char scratch[24];
    unsigned char local_f8[80], scratch_a8[72];

    cL4_slot_commit((void *)(obj + 0x88), scratch, 0, 0);
    list = *(long **)(obj + 0x88);
    v = (*(long (**)(void))(*list + 0x88))();
    cL4_ref_release((void *)list);
    cnt = *(unsigned long *)(v + 0x10);
    for (i = 0; cnt != i; i++) {
        if (*(unsigned long *)(v + 0x10) <= i)
            __builtin_trap();
        node = *(long **)(v + i * 8 + 0x20);
        v2 = (unsigned long)(*(long (**)(void))(*node + 0x78))();
        cL4_ref_release2((void *)node);
        cL4_slot_commit((void *)0x6509b0, scratch, 0, 0);
        if (v2 == 0xd000055868200013ull) {   /* kernel component kind */
            cL4_ref_release((void *)v);
            comp = (long *)(*(long (**)(void))(*node + 0xa8))();
            i = 0;
            cnt = *(unsigned long *)(comp + 0x10);
            goto subwalk;
        }
        cL4_ref_release((void *)node);
    }
    cL4_ref_release((void *)v);
    cL4_fatal_noreturn();   /* "Can't find kernel component" */

subwalk:
    for (; cnt != i; i++) {
        if (*(unsigned long *)(comp + 0x10) <= i)
            __builtin_trap();
        node = *(long **)(comp + i * 8 + 0x20);
        v = (unsigned long)(*(long (**)(void))(*node + 0x70))();
        cL4_ref_release2((void *)node);
        if (v == 0x484f4843414d5f5full && cL4_os37((void *)node) == 0xef434c5245444145ull) {
            cL4_ref_release((void *)comp);
            cL4_obj_free((void *)cL4_os37((void *)node));
            goto resolve;
        }
        if ((cL4_name_match(v, cL4_os37((void *)node), 0x484f4843414d5f5f,
                            0xef434c5245444145, 0) & 1) != 0) {
            cL4_ref_release((void *)comp);
            goto resolve;
        }
        cL4_ref_release((void *)node);
    }
    cL4_ref_release((void *)comp);
    cL4_fatal_noreturn();   /* "Can't find kernel header" */

resolve:
    cL4_slot_commit((void *)(obj + 0x58), scratch, 0, 0);
    base = *(unsigned long *)(*(unsigned long *)(obj + 0x58) + 0x30);
    if (base == 0)
        __builtin_trap();
    v = (*(long (**)(void))(*node + 0x88))();
    if ((long)v >= 0) {
        v2 = (*(long (**)(void))(*node + 0xa0))();
        if ((long)v2 >= 0) {
            base += v;
            cL4_os43((void *)local_f8, base, base + v2, 0);
            cL4_os44(scratch_a8, 0, 0, 0);
            cL4_ref_release((void *)node);
            cL4_ref_release((void *)comp);
            return (unsigned long)cL4_os46(0, 0, 0);
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/* FUN_000c36a4 @ 0x000c36a4   (est. cL4_vm_launch_setup)
 * Ghidra: void FUN_000c36a4(void)
 * Performs the full launch setup of an exclave VM: initializes the launch
 * context (FUN_0008e518), resolves the VM descriptor (+0xd8), and walks the
 * component/artifact tables building the launch image:
 *   - maps the VM's component list into page frames (0x4000 chunks) via the
 *     object's vtable methods, emitting AppleInternal build log markers
 *     (FUN_00151a6c with the BuildRoot source path) per chunk;
 *   - iterates the +0x180 component list, mapping each component's bytes
 *     through its pte set and recording frame descriptors;
 *   - walks the +0x110 artifact set, resolving each artifact's range via the
 *     +0x170 object map and storing resolved component pointers.
 * On any allocation failure it logs a fatal error and traps. Completes by
 * releasing all temporary lists and returning through FUN_0008e500.
 * Confidence: low
 * Notes: Huge launch-path function; per-chunk logging via FUN_00151a6c with
 *   source path s__AppleInternal_Library_BuildRoot_005c3120; many bounds
 *   checks with SoftwareBreakpoint. */
void cL4_vm_launch_setup(void)
{
    unsigned long obj = 0;   /* unaff_x20 */
    unsigned long x24 = 0;   /* unaff_x24 */
    unsigned long ctx, l1, map, cnt, i, chunk, frame, v;
    long *list, *node;
    unsigned char scratch[72], scratch2[24], scratch3[24];
    unsigned long local_48;

    ctx = cL4_cls13().hi;
    cL4_vm_desc_lookup(&local_48, 0);
    if (local_48 == 0)
        __builtin_trap();
    cL4_copy_pair((void *)&local_48, scratch3);
    cL4_slot_lock((void *)(obj + 0xd8), scratch2);
    cL4_slot_commit((void *)(obj + 0xd8), scratch2, 0, 0);
    list = (long *)*(unsigned long *)(obj + 0xd8);
    if (list == 0)
        __builtin_trap();
    l1 = *(unsigned long *)(obj + 0xe8);
    cL4_ref_release2((void *)list);
    /* map first chunk */
    cL4_field_copy(scratch3, l1);
    chunk = *(unsigned long *)(*(unsigned long *)(obj + 0x1b0) + 0x10);
    cL4_field_copy2(scratch3, l1);
    v = (*(long (**)(void))cL4_vtbl6(l1))();   /* FUN_000db748 map */
    if (v == 0) { cL4_vtbl_apply3(scratch); }
    cL4_vm_set_vm_list((unsigned long)&local_48, ctx);
    cL4_field_copy2(scratch3, l1);
    v = (*(long (**)(void))cL4_vtbl6(l1))();   /* re-map */
    cL4_vtbl_apply3(scratch);
    cL4_ref_release((void *)list);

    /* walk the +0x180 component list mapping chunks */
    list = (long *)*(unsigned long *)(obj + 0x180);
    if (list == 0)
        __builtin_trap();
    frame = 0;
    cnt = *(unsigned long *)(list + 0x10);
    if (cnt == 0) {
        /* no list: single mapping pass */
        cL4_vtbl_apply3(scratch);
        chunk = (unsigned long)cL4_arr_grow4();
        /* ... (page-frame walk elided: faithful to decompile loop) ... */
    } else {
        /* per-component frame map */
        for (i = 0; i < cnt; i++) {
            node = *(long **)(list + i * 8 + 0x20);
            v = (unsigned long)cL4_field_value((void *)node, 0);
            cL4_ref_release((void *)node);
            frame += v;
        }
    }
    cL4_ref_release((void *)list);
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x178));
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x180));
    cL4_ref_release((void *)node);
    cL4_field_free(scratch3);
    (void)map; (void)x24;
}

/* FUN_000c411c @ 0x000c411c   (est. cL4_vm_log_event)
 * Ghidra: undefined1 [16] FUN_000c411c(void)
 * Emits a capability event log record ("-> " separated): selects kind 0x42,
 * appends a {cap,type} pair, fetches and prints the log class name
 * (0x671df8), and returns the empty 16-byte constant 0xe000000000000000<<64.
 * Confidence: low
 * Notes: cL4_log_kind(0x42); FUN_00027724(0x671df8) class fetch. */
cl4_result_t cL4_vm_log_event(void)
{
    cl4_result_t r;
    void *(*fn)(unsigned long, unsigned long);

    cL4_log_kind(0x42);
    cL4_log_pair(0xd00000000000003a, 0x80000000005c3810);
    fn = cL4_pacia_fetch(0x671df8);
    fn(0x677830, 0x671df8);
    cL4_log_pair(0, 0);
    cL4_obj_free((void *)0);
    cL4_log_pair(0x203e2d20, 0xe400000000000000);
    fn(0x677830, 0x671df8);
    cL4_log_pair(0, 0);
    cL4_obj_free((void *)0);
    r.lo = 0xe000000000000000ull;
    r.hi = 0;
    return r;
}

/* FUN_000c422c @ 0x000c422c   (est. cL4_vm_resolve_range)
 * Ghidra: undefined8 FUN_000c422c(undefined8 param_1, long param_2)
 * Resolves a 0x4000-sized range for the object at param_2: looks up the
 * range descriptor, maps 0x4000 bytes, builds a log message (0x64e6b0) with
 * the param_2 component words, invokes cL4_vm_build_edges with a range tag,
 * releases the message, and returns the mapped base.
 * Confidence: low */
unsigned long cL4_vm_resolve_range(unsigned long param_1, long param_2)
{
    unsigned char scratch_90[24], scratch_68[24], scratch_c8[56];
    unsigned long local_78, local_50, u48, v, msg;

    cL4_vm_desc_lookup(scratch_90, 0);
    if (local_78 != 0) {
        cL4_copy_pair(scratch_90, scratch_68);
        local_50 = cL4_field_value(scratch_68, 0);
        v = (*(long (**)(void))cL4_vtbl6(u48))();   /* map 0x4000 */
        msg = cL4_msg_alloc((void *)cL4_intern((const char *)0x64e6b0, (void *)0x4c0500), scratch_c8);
        cL4_msg_field(0, 0x20, 7);
        cL4_vm_build_edges(msg, (unsigned long)scratch_68, v, 2, 0, 2, 0, 1);
        cL4_msg_release((void *)msg);
        cL4_field_free(scratch_68);
        return v;
    }
    __builtin_trap();
}

/* FUN_000c4364 @ 0x000c4364   (est. cL4_vm_resolve_exec)
 * Ghidra: undefined8 FUN_000c4364(undefined8 param_1, uint param_2)
 * Resolves an executable range: looks up the range descriptor, validates the
 * writable/exec flag (param_2&1), maps 0x4000 bytes, queries the object's
 * +0x1c0 method (vtable+0x68) for the exec flag, builds a log message
 * (0x64e6b0) and invokes cL4_vm_build_edges with the appropriate tag (2/3),
 * releasing the message and field buffers. On flag mismatch logs a fatal
 * error.
 * Confidence: low */
unsigned long cL4_vm_resolve_exec(unsigned long param_1, unsigned int param_2)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch_90[24], scratch_68[24], scratch_c8[56];
    unsigned long local_78, local_50, u48, v, v3, msg, *pl7;

    cL4_vm_desc_lookup(scratch_90, 0);
    if (local_78 == 0)
        __builtin_trap();
    cL4_copy_pair(scratch_90, scratch_68);
    if (((param_2 & 1) != 0) && ((*(unsigned char *)(obj + 0x18) & 1) == 0))
        cL4_fatal_noreturn();   /* exec-not-writable mismatch */
    local_50 = cL4_field_value(scratch_68, 0);
    v = (*(long (**)(void))cL4_vtbl6(u48))();   /* map 0x4000 */
    pl7 = *(long **)(obj + 0x1c0);
    v3 = (*(long (**)(unsigned long))(*pl7 + 0x68))(param_2 & 1);
    msg = cL4_msg_alloc((void *)cL4_intern((const char *)0x64e6b0, (void *)0x4c0500), scratch_c8);
    cL4_msg_field(0, 0x20, 7);
    cL4_get_pair(scratch_68, scratch_90);
    cL4_vm_build_edges(msg, (unsigned long)scratch_90, v, 3, 0, 2, v3, 0);
    cL4_msg_release((void *)msg);
    cL4_field_free(scratch_90);
    cL4_field_free(scratch_68);
    return v;
}

/* FUN_000c4534 @ 0x000c4534   (est. cL4_vm_is_usr_binary)
 * Ghidra: uint FUN_000c4534(long param_1)
 * Returns 1 if the object param_1 is a userland (usr/dyl) binary path: copies
 * the path field into a buffer, and if it is empty returns 1, otherwise
 * compares against the "/usr/dyl" prefix (0x62696c2f7273752f) and returns the
 * low bit of the match.
 * Confidence: low
 * Notes: Path prefix "/usr/dyl"; FUN_000db650/FUN_0000276c copy. */
unsigned int cL4_vm_is_usr_binary(long param_1)
{
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch_58[24];
    unsigned long local_40;

    cL4_str_field((void *)(obj + 0x148), scratch_58, (const char *)0x64c058, (void *)0x4c2480);
    cL4_fmt(scratch_58, (const char *)0x64c058, (void *)0x4c2480);
    if (local_40 == 0)
        return 1;
    return cL4_name_equal(0x62696c2f7273752full, 0xed0000646c79642full,
                          *(unsigned long *)(param_1 + 8),
                          *(unsigned long *)(param_1 + 0x10)) & 1;
}

/* FUN_000c45d4 @ 0x000c45d4   (est. cL4_vm_collect_segments)
 * Ghidra: undefined * FUN_000c45d4(long param_1, ulong param_2, ulong param_3)
 * Collects and materializes the VM's segment/region list for launch. Computes
 * the number of 0x4000-page frames needed for the given address range
 * (param_2..param_3), then iterates the component list at param_1+0x20:
 *   - for each component, walks its vtable+0x50 method to gather page/edge
 *     capabilities (name "PAGEZER"/"__PAGEZERO"), collecting them;
 *   - materializes each frame's descriptor record into the result list
 *     (stride 0x48), tracking the byte offset/size and release pairs.
 * Returns the collected list; emits fatal errors on range overflow.
 * Confidence: low
 * Notes: Writes read-only data at 0x651138/0x651140 (PAC keys); huge
 *   page-walk; strings via DER component names; stride 0x48 records. */
unsigned long *cL4_vm_collect_segments(long param_1, unsigned long param_2,
                                       unsigned long param_3)
{
    unsigned long rng = param_3 - param_2;
    unsigned long *result, *comp, *node;
    unsigned long cnt, i, j, size, offset, slot, v;
    unsigned char scratch[128];
    unsigned long local_b0[2], local_f0[2], local_240[2];

    if (param_3 < param_2)
        __builtin_trap();
    cL4_slot_commit((void *)0x6ad9a0, scratch, 0, 0);
    cL4_str_field((void *)0x6ad9a0, &local_b0[0], (const char *)0x64c038, (void *)0x4c1020);
    if (local_b0[1] == 0)
        __builtin_trap();
    size = cL4_field_value(&local_b0[0], 0);
    v = (*(long (**)(void))cL4_vtbl8(size))();   /* map class */
    cL4_field_free(&local_b0[0]);
    if (rng == 0)
        __builtin_trap();
    offset = 0;
    /* frame count = (puVar10 - rem*chunk) rounded to 0x4000 */
    slot = 0;
    i = 0;
    /* iterate components building frames */
    comp = (unsigned long *)(param_1 + 0x20);
    cnt = *(unsigned long *)(param_1 + 0x10);
    result = (unsigned long *)0x65778;
    for (j = 0; j < cnt; j++) {
        node = comp;
        size = node[1];
        v = *node;
        cL4_slot_load(&local_240[0], node);
        cL4_ref_release2((void *)size);
        cL4_ref_release2((void *)*(unsigned long *)(node + 2));
        /* gather PAGEZER entries */
        for (i = 0; i < *(unsigned long *)(v + 0x10); i++) {
            unsigned long *e = *(unsigned long **)(v + 0x20 + i * 8);
            slot = (unsigned long)(*(long (**)(void))(*e + 0x50))();
            cL4_ref_release2((void *)e);
            if (slot == 0x455a454741505f5full)
                cL4_ref_release((void *)e);
            else {
                cL4_name_match(slot, 0, 0x455a454741505f5f, 0xea00000000004f52, 0);
                cL4_ref_release((void *)e);
                cL4_ref_release((void *)e);
            }
        }
        /* materialize frame record */
        size = cL4_os18((void *)0);
        offset += size;
    }
    cL4_ref_release((void *)0x65778);
    cL4_ref_release((void *)0x65778);
    return result;
}

/* FUN_000c4e54 @ 0x000c4e54   (est. cL4_vm_walk_edges)
 * Ghidra: void FUN_000c4e54(void)
 * Walks the VM's capability/edge graph to build a set of reachable
 * component frames. Iterates the object's +0x20 capability bitmap (bit
 * vector at +0x38), and for each set bit resolves the corresponding
 * component (vtable+0x80 getter), walks its +0xa0 edge list collecting
 * edge capabilities (kind '\\x05'), validating single-destination edges
 * ("Expected edge to have only one d..."), and accumulating the resolved
 * frames into the global collected set. Returns a descriptor with the
 * collected result count.
 * Confidence: low
 * Notes: Bit-vector LZCOUNT iteration; edge-kind 0x05; global DAT_00657788
 *   collection counter; fatal on multi-destination edge. */
void cL4_vm_walk_edges(void)
{
    unsigned long obj = 0;   /* unaff_x20 */
    unsigned long cnt, i, j, v, bits, bit, k, frame;
    long *list, *node, *edge;
    unsigned char scratch[24];
    unsigned long local_68;

    local_68 = cL4_descriptor(0x65778, 0x6753a0,
                              cL4_intern((const char *)0x64e1e8, (void *)0x4c2470), 0x66dfb8);
    cL4_slot_commit((void *)(obj + 0x20), scratch, 0, 0);
    list = *(long **)(obj + 0x20);
    v = (*(long (**)(void))(*list + 0x80))();
    cL4_ref_release((void *)list);
    cnt = (*(long (**)(void))(*list + 0x88))();
    cL4_ref_release((void *)list);
    i = 0;
    bits = 1ull << ((*(unsigned char *)(cnt + 0x20)) & 0x3f);
    v = ~0ull;
    if ((*(unsigned char *)(cnt + 0x20) & 0x3f) < 6)
        v = ~(-1L << (bits & 0x3f));
    v &= *(unsigned long *)(cnt + 0x38);
    while (1) {
        while (v == 0) {
            i += 1;
            if ((long)((bits + 0x3f) >> 6) <= i) {
                cL4_ref_release((void *)cnt);
                frame = cL4_cap_small_alloc(0);
                frame = cL4_msg_field(frame, 0x18, 7);
                *(unsigned long *)(frame + 0x10) = local_68;
                return;
            }
            v = ((unsigned long *)(cnt + 0x38))[i];
        }
        bit = /* LZCOUNT of reversed bits + i<<6 */ i * 64;
        frame = *(unsigned long *)(*(unsigned long *)(cnt + 0x30) + bit * 8);
        v &= v - 1;
        list = *(long **)(obj + 0x20);
        j = (*(long (**)(void))(*list + 0x80))();
        cL4_ref_release((void *)list);
        k = (*(long (**)(void))(*list + 0xa0))();
        cL4_ref_release((void *)list);
        /* walk k's edge list, collect edge caps */
        for (j = 0; j < *(unsigned long *)(k + 0x10); j++) {
            edge = *(long **)(k + 0x20 + j * 8);
            if ((*(char (**)(void))(*edge + 0x88))() == '\x05') {
                long *dest = (long *)(*(long (**)(void))(*edge + 0x70))();
                if (*(long *)(dest + 0x10) != 1)
                    cL4_fatal_noreturn();   /* multi-dest edge */
                /* record single destination */
                DAT_00657788++;
                cL4_ref_release((void *)edge);
            } else {
                cL4_ref_release((void *)edge);
            }
        }
        cL4_ref_release((void *)k);
        cL4_ref_release((void *)frame);
        cL4_ref_release((void *)cnt);
    }
}

/* FUN_000c544c @ 0x000c544c   (est. cL4_vm_build_launch_image)
 * Ghidra: void FUN_000c544c(void)
 * Builds the full launch image for the exclave: 
 *   1. Acquires the launch context (FUN_0008e518, FUN_000a021c) and emits
 *      a "badge/pinpped" mapping log marker (DAT_006ad9c8).
 *   2. Collects the VM descriptor via cL4_vm_walk_edges into slot +0x50 and
 *      logs the collect result.
 *   3. Walks the object's +0x20 capability bitmap resolving each component's
 *      edge/frame set (vtable+0x80/+0xa0 getters, vtable+0x88 kind probe),
 *      collecting per-component name/size records.
 *   4. For each named artifact, computes the component checksum (cL4_os6 via
 *      0x6ae9c map lookup), validates the type/kind bits, and stores the
 *      resolved component reference into the frame list.
 *   5. Emits per-component AppleInternal build log markers and finalizes the
 *      frame list at the end of the walk.
 * Confidence: low
 * Notes: Huge (0x2cd0-byte) graph-builder; per-component logging via
 *   FUN_00151a6c with s__AppleInternal_Library_BuildRoot; many bounds traps. */
void cL4_vm_build_launch_image(void)
{
    unsigned long obj = 0;   /* unaff_x20 */
    unsigned long ctx, v, i, cnt, bits, bit, k, frame, w;
    long *list, *node, *edge;
    unsigned char scratch[72];

    ctx = cL4_cls13().hi;
    cL4_vm_walk_edges();
    cL4_slot_commit((void *)(obj + 0x50), scratch, 0, 0);
    list = *(long **)(obj + 0x50);
    cL4_ref_release((void *)list);
    /* walk +0x20 bitmap */
    list = *(long **)(obj + 0x20);
    v = (*(long (**)(void))(*list + 0xa0))();
    cL4_ref_release((void *)list);
    cnt = *(unsigned long *)(v + 0x10);
    if (cnt != 0) {
        i = 0;
        do {
            if (*(unsigned long *)(v + 0x10) <= i)
                __builtin_trap();
            node = *(long **)(v + 0x20 + i * 8);
            if ((*(char (**)(void))(*node + 0x88))() == '\0') {
                /* component kind 0: resolve its edges */
                edge = (long *)(*(long (**)(void))(*node + 0xa0))();
                if (*(long *)(edge + 0x10) == 0)
                    __builtin_trap();
                w = cL4_map_lookup(0, 0).lo;   /* 0x6ae9c name lookup */
                cL4_ref_release((void *)edge);
                if (w == 0)
                    cL4_ref_release((void *)node);
                else {
                    k = *(unsigned long *)(edge + 0x38);
                    bits = *(unsigned long *)(edge + 0x30);
                    cL4_ref_release2((void *)bits);
                    cL4_ref_release((void *)edge);
                    /* store resolved component */
                    cL4_ref_release((void *)node);
                    frame = (unsigned long)cL4_arr_grow4();
                    cL4_ref_release((void *)frame);
                }
            } else {
                cL4_ref_release((void *)node);
            }
            i++;
        } while (cnt != i);
    }
    cL4_ref_release((void *)v);
    cL4_ref_release((void *)*(unsigned long *)(obj + 0x50));
    (void)ctx; (void)bit;
}

/* FUN_000c811c @ 0x000c811c   (est. cL4_vm_has_mmpx_component)
 * Ghidra: bool FUN_000c811c(void)
 * Returns true if the object list (in_x3) contains a component whose name
 * matches the "mmpx_elx"/"avex" pair (0x6c6378655f6d6d70). Iterates the list
 * comparing each entry's vtable+0x58 name pair; stops at the first match
 * (returns true) or when the list is exhausted (returns false).
 * Confidence: low */
bool cL4_vm_has_mmpx_component(void)
{
    unsigned long in_x3 = 0;   /* implicit register */
    long *list, *node;
    unsigned long cnt, i, v;
    bool have;

    cnt = *(unsigned long *)(in_x3 + 0x10);
    i = 0;
    while (1) {
        have = cnt != 0;
        cnt -= 1;
        if (!have)
            return false;
        node = *(long **)(in_x3 + 0x20 + i * 8);
        v = (unsigned long)(*(long (**)(void))(*node + 0x58))();
        cL4_ref_release2((void *)node);
        if (v == 0x6c6378655f6d6d70ull) {
            cL4_ref_release((void *)node);
            cL4_obj_free((void *)(v & 1));
            return true;
        }
        if ((cL4_name_match(v, 0, 0x6c6378655f6d6d70, 0xeb00000000657661, 0) & 1) != 0)
            return have;
        cL4_ref_release((void *)node);
        cL4_obj_free((void *)0);
        i++;
    }
}

/* FUN_000c8208 @ 0x000c8208   (est. cL4_vm_cmp_component_node)
 * Ghidra: void FUN_000c8208(undefined8 *param_1, undefined8 *param_2, long *param_3)
 * Compares two component nodes and records the result into *param_1. Reads the
 * 0x40-byte node descriptor from param_2, then walks param_3's component map
 * (via 0x6ae9c lookup) comparing name/kind pairs; if the node is found it
 * decrements the source counter and re-checks; sets the result flag bit
 * accordingly. Copies the descriptor fields and finalizes via cL4_slot_load.
 * Confidence: high */
void cL4_vm_cmp_component_node(unsigned long *param_1, unsigned long *param_2,
                               long *param_3)
{
    unsigned char scratch[64];
    unsigned long local_a0[2], v, w, u2, idx, res, map;
    cl4_result_t hit;

    v = *param_2;
    w = param_2[2];
    map = *param_3;
    res = 0;
    if (*(long *)(map + 0x10) != 0) {
        cL4_ref_release2((void *)map);
        hit = cL4_map_lookup(w, param_2[3]);
        cL4_obj_free((void *)map);
        if ((hit.hi & 1) != 0) {
            map = *param_3;
            if (*(long *)(map + 0x10) == 0)
                __builtin_trap();   /* SoftwareBreakpoint 0xc8384 */
            cL4_ref_release2((void *)map);
            hit = cL4_map_lookup(w, param_2[3]);
            if ((hit.hi & 1) == 0) {
                cL4_obj_free((void *)map);
                __builtin_trap();   /* SoftwareBreakpoint 0xc8394 */
            }
            idx = *(unsigned long *)(*(unsigned long *)(map + 0x38) + hit.lo * 8);
            cL4_obj_free((void *)map);
            if (idx == 0)
                __builtin_trap();   /* SoftwareBreakpoint 0xc8388 */
            cL4_os27((void *)(idx - 1), w);
            map = *param_3;
            if (*(long *)(map + 0x10) != 0) {
                cL4_ref_release2((void *)map);
                hit = cL4_map_lookup(w, param_2[3]);
                if ((hit.hi & 1) == 0)
                    cL4_obj_free((void *)map);
                else {
                    idx = *(unsigned long *)(*(unsigned long *)(map + 0x38) + hit.lo * 8);
                    cL4_obj_free((void *)map);
                    if (idx == 0) {
                        res = 1;
                        goto done;   /* skip the res=0 reset (LAB_000c8328) */
                    }
                }
            }
        }
        res = 0;
    }
done:
    param_1[0] = v;
    param_1[2] = param_2[2];
    param_1[1] = param_2[1];
    param_1[4] = param_2[4];
    param_1[3] = param_2[3];
    param_1[6] = param_2[6];
    param_1[5] = param_2[5];
    *(unsigned long *)((char *)param_1 + 0x31) = *(unsigned long *)((char *)param_2 + 0x31);
    *(unsigned long *)((char *)param_1 + 0x39) = *(unsigned long *)((char *)param_2 + 0x39);
    *(unsigned char *)((char *)param_1 + 0x41) = (unsigned char)res;
    cL4_slot_load2(scratch, &local_a0[0]);
}

/* FUN_000c8394 @ 0x000c8394   (est. cL4_vm_all_edges_kind)
 * Ghidra: bool FUN_000c8394(long param_1, uint param_2)
 * Returns true if all edges in the list param_1 have the given kind bit
 * (param_2&1): iterates the list, queries each entry's vtable+0xe0 method,
 * and breaks early when a non-matching edge is found.
 * Confidence: low */
bool cL4_vm_all_edges_kind(long param_1, unsigned int param_2)
{
    long *node;
    unsigned long cnt, i;
    unsigned int k;

    cnt = *(unsigned long *)(param_1 + 0x10);
    i = 0;
    do {
        if (cnt == 0)
            break;
        node = *(long **)(param_1 + 0x20 + i * 8);
        k = (*(unsigned int (**)(void))(*node + 0xe0))();
        cL4_ref_release((void *)node);
        cnt -= 1;
        i++;
    } while ((param_2 & 1) == (k & 1));
    return cnt == 0;
}

/* FUN_000c842c @ 0x000c842c   (est. cL4_vm_has_edge)
 * Ghidra: bool FUN_000c842c(long param_1, undefined8 param_2, undefined8 param_3)
 * Returns true if the list param_1 contains an edge whose name pair matches
 * (param_2, param_3). Iterates the list comparing each entry's vtable+0x108
 * name; stops at the first match.
 * Confidence: low */
bool cL4_vm_has_edge(long param_1, unsigned long param_2, unsigned long param_3)
{
    long *node;
    unsigned long cnt, i, v;
    cl4_result_t target;

    target.lo = param_2; target.hi = param_3;
    cnt = *(unsigned long *)(param_1 + 0x10);
    for (i = 0; cnt != 0; cnt--, i++) {
        node = *(long **)(param_1 + 0x20 + i * 8);
        cL4_ref_release2((void *)node);
        v = (unsigned long)(*(long (**)(void))(*node + 0x108))();
        if (v == target.hi) {
            cL4_ref_release((void *)node);
            cL4_obj_free((void *)v);
        } else {
            if ((cL4_name_match(0, v, param_2, param_3, 0) & 1) == 0)
                break;
            cL4_ref_release((void *)node);
            cL4_obj_free((void *)v);
        }
    }
    cL4_obj_free((void *)param_3);
    return cnt == 0;
}

/* FUN_000c8734 @ 0x000c8734   (est. cL4_vm_resolve_edges_dfs)
 * Ghidra: undefined * FUN_000c8734(long param_1, undefined8 param_2,
 *                                  undefined8 param_3)
 * Depth-first resolution of a VM's edge set. Iterates the component list
 * param_1; for each entry whose edge bitmap has a set bit, resolves the
 * destination component and records it into the working list (local_68,
 * local_58), recursing via cL4_dg_step until the list is exhausted. On
 * completion releases all temporaries and returns the resolved frame list.
 * Confidence: low
 * Notes: Uses DAT_006577e0/d8 global worklists; FUN_000d4964 step + FUN_000d45ec
 *   completion; bit-vector scan with FUN_001394c8. */
unsigned long *cL4_vm_resolve_edges_dfs(long param_1, unsigned long param_2,
                                        unsigned long param_3)
{
    unsigned char scratch_d0[72], scratch_88[24];
    unsigned long *local_70 = (unsigned long *)0x6577e0;
    unsigned long *local_68 = (unsigned long *)0x6577e0;
    unsigned long *result = (unsigned long *)0x65778;
    unsigned long cnt, i, bit;
    long *node;

    cnt = *(unsigned long *)(param_1 + 0x10);
    cL4_ref_release2((void *)param_2);
    cL4_ref_release2((void *)param_3);
    cL4_slot_commit(&local_68, scratch_88, 0, 0);
    i = 0;
    while (1) {
        if (i == cnt) {
            cL4_slot_commit(&result, scratch_d0, 0, 0);
            result = local_68;
            cL4_ref_release2((void *)result);
            result = (unsigned long *)(uintptr_t)cL4_dg_new();
            cL4_obj_free((void *)local_70);
            local_68 = result;
            cL4_obj_free((void *)param_3);
            cL4_ref_release((void *)param_2);
            cL4_ref_release((void *)result);
            cL4_obj_free((void *)local_68);
            return result;
        }
        if (cnt <= i)
            __builtin_trap();
        node = *(long **)(param_1 + 0x20 + i * 8);
        if (local_68[2] == 0) {
            /* empty slot: record */
            cL4_ref_release2((void *)node);
            cL4_ref_release2((void *)param_2);
            cL4_ref_release2((void *)param_3);
            cL4_dg_step(node, &local_68, &local_70, (void *)param_1, &result,
                        param_2, param_3);
            cL4_ref_release((void *)node);
            i = 0;
        } else {
            i++;
            /* scan bitmap for a reachable bit and recurse */
            bit = 0;
            cL4_dg_step(node, &local_68, &local_70, (void *)param_1, &result,
                        param_2, param_3);
            cL4_ref_release((void *)node);
        }
    }
}

/* FUN_000c89d0 @ 0x000c89d0   (est. cL4_vm_register_component)
 * Ghidra: void FUN_000c89d0(long param_1, undefined8 param_2..param_10, long *param_11)
 * Registers a new component into the VM's component list. Searches param_1's
 * entries for a slot already marked bound ('\\x01'); if found, logs a
 * "rebind" event (cL4_vm_log_event with param_7/8). Otherwise resolves the
 * component's parent/exec context, allocates a fresh component record, wires
 * it into the object's +0x180 list, and appends the 0x42-byte component
 * descriptor into param_11's record array, releasing temporaries.
 * Confidence: low
 * Notes: Large; FUN_0009d068/FUN_000f4994 record classes (0x109/0x128);
 *   registers into param_11 with stride 0x40; debug logging of bindings. */
void cL4_vm_register_component(long param_1, unsigned long p2, unsigned long p3,
                               unsigned long p4, unsigned long p5, unsigned long p6,
                               unsigned long p7, unsigned long p8, unsigned long p9,
                               unsigned long p10, long *param_11)
{
    unsigned long obj = 0;   /* unaff_x20 */
    unsigned long cnt, i, v, w;
    long *node, *rec;
    unsigned char scratch_100[24], scratch_b8[24], scratch_1a0[24];
    unsigned long local_170, local_90[3], local_a0, u98, local_e8;
    long *l9;

    cnt = *(unsigned long *)(param_1 + 0x10);
    for (i = 1; i < cnt; i++)
        if (*(unsigned char *)(param_1 + i * 0x48) == '\x01')
            goto found_bound;
    /* not bound: resolve +0x180 context */
    cL4_field_begin();
    cL4_str_field((void *)(obj + 0x148), scratch_100, 0, 0);
    if (local_e8 == 0) {
        cL4_list_finalize();
        cL4_fmt(scratch_100, 0, 0);
        if (*(long *)(obj + 0x180) == 0) {
            v = cL4_get_state2(0);
            w = cL4_get_state3();
            v = cL4_state_join();
            rec = (long *)cL4_get_state3();
            cL4_get_pair((void *)p2, &local_170);
            v = cL4_cls9();   /* resolve */
            w = *(unsigned long *)(obj + 0x180);
            *(unsigned long *)(obj + 0x180) = v;
            cL4_ref_release((void *)w);
        }
        cL4_get_pair((void *)p2, &local_170);
        v = cL4_cls10(0);   /* allocate record 0x109 */
        cL4_msg_field(v, 0x109, 7);
        cL4_ref_release2((void *)p8);
        cL4_ref_release2((void *)v);
        cL4_os49((void *)p5, (unsigned long)&local_170, 0);
        local_90[0] = cL4_cls8();
        u98 = 0x660448;
        local_a0 = v;
    } else {
        /* bound path: allocate record via cls, append descriptor */
        cL4_copy_pair(scratch_100, &local_170);
        cL4_vm_desc_lookup(scratch_100, p5);
        cL4_list_finalize();
        cL4_fmt(scratch_100, 0, 0);
        if (local_e8 != 0)
            cL4_fatal_noreturn();   /* DERComponentGraph something wrong */
        v = cL4_cls(0);
        rec = (long *)cL4_msg_alloc((void *)v, scratch_b8);
        v = cL4_list_alloc();
        *(unsigned long *)(rec + 0x10) = v;
        w = cL4_field_value(&local_170, 0);
        cL4_vm_build_edges((unsigned long)rec, (unsigned long)&local_170, p5, 0, 0, 0, 0, 0);
        l9 = (long *)cL4_os9(0);
        cL4_ref_release((void *)v);
        cL4_get_pair((void *)(l9 + 3), scratch_100);
        if (*(long *)(obj + 0x180) == 0) {
            cL4_get_state2(0);
            v = cL4_state_join();
            cL4_get_pair(scratch_100, local_90);
            cL4_ref_release((void *)v);
        }
        v = *(unsigned long *)(l9 + 2);
        cL4_slot_lock((void *)(v + 0x90), scratch_1a0);
        cL4_slot_commit((void *)(v + 0x90), scratch_1a0, 0, 0);
        if (*(long *)(v + 0x90) == 0)
            __builtin_trap();
        cL4_get_pair(scratch_100, local_90);
        v = *(unsigned long *)(obj + 0x180);
        v = cL4_cls4(0);   /* allocate record 0x128 */
        cL4_msg_field(v, 0x128, 7);
        cL4_ref_release2((void *)p8);
        cL4_ref_release2((void *)v);
        cL4_os50(local_90, (unsigned long)l9);
        local_90[0] = cL4_cls3();
        u98 = 0x662168;
        local_a0 = v;
        cL4_msg_release((void *)rec);
        cL4_ref_release((void *)l9);
        cL4_field_free(scratch_100);
        cL4_field_free(&local_170);
    }
    cL4_get_pair(local_90, scratch_b8);
    cL4_field_value(scratch_b8, local_a0);
    cL4_bv_resize3();
    node = param_11;
    if (cnt != 0) {
        cL4_arr_reserve2(0, cnt, 0);
        for (i = 0; i < cnt; i++) {
            cL4_memcpy(&local_170, (void *)(param_1 + 0x20 + i * 0x48), 0x42);
            cL4_graph_push(&local_170, scratch_100);
            if ((long *)((unsigned long)param_11[3] >> 1) <= (long *)param_11[2])
                cL4_vec_grow2();
            param_11[2]++;
            *(unsigned long *)((char *)param_11 + (unsigned long)param_11[2] * 0x40 + 0x51) = 0;
            cL4_os51((void *)0, 0, 0);
        }
        cL4_bv_resize3();
    }
    return;

found_bound:
    v = cL4_str_new(0);
    cL4_ref_release2((void *)p8);
    cL4_ref_release2((void *)p7);
    cL4_ref_release2((void *)p8);
}

/* FUN_000c900c @ 0x000c900c   (est. cL4_vm_build_image)
 * Ghidra: undefined1 [16] FUN_000c900c(void)
 * Builds the exclave launch image: 
 *   1. Acquires the launch context and emits a "get dist"/"dist list" log
 *      marker via DAT_006ad9c8.
 *   2. Collects the VM frame list into slot +0xb0 (cL4_vm_walk_edges) and
 *      resolves the launch frame base (DAT_006add08).
 *   3. Maps each 0x4000 frame through the +0x60 field vtable methods,
 *      storing resolved component pointers into a growing list (unaff_x24),
 *      emitting per-frame AppleInternal build log markers.
 *   4. Walks the +0x170 artifact set resolving each artifact's range and
 *      storing the resolved frame into the result list.
 *   5. Releases temporaries and returns the {list, base} 16-byte pair.
 * Confidence: low
 * Notes: Huge (0x648-byte) build function; per-frame logging via
 *   FUN_00151a6c; bounds traps at many points. */
cl4_result_t cL4_vm_build_image(void)
{
    unsigned long obj = 0;    /* unaff_x20 */
    unsigned long x24 = 0;    /* unaff_x24 */
    unsigned long ctx, v, cnt, i, base, chunk, frame, slot;
    long *list, *node, *frame_list;
    unsigned char scratch_c0[24], scratch_d8[24], scratch_a8[72], scratch_f8[32];
    cl4_result_t r;

    cL4_vm_walk_edges();
    cL4_slot_lock((void *)0x6ad9c8, scratch_c0);
    cL4_slot_commit((void *)0x6ad9c8, scratch_c0, 0, 0);
    v = *(unsigned long *)0x6ad9c8;
    cL4_ref_release2((void *)v);
    v = cL4_cls13().hi;
    cL4_slot_lock((void *)(obj + 0xb0), scratch_d8);
    v = *(unsigned long *)(obj + 0xb0);
    *(unsigned long *)(obj + 0xb0) = v;
    cL4_ref_release((void *)v);
    cL4_slot_commit((void *)(obj + 0xb0), scratch_d8, 0, 0);
    list = (long *)*(unsigned long *)(obj + 0xb0);
    cnt = *(unsigned long *)(list + 0x10);
    if (cnt == 0) {
        cL4_vtbl_apply2((void *)list, scratch_a8);
        cL4_list_begin();
        frame = x24;
    } else {
        base = *(unsigned long *)(list + 0x10) + ((unsigned long)0x6add08 >> 0xe);
        frame = base * 0x40;
        chunk = cL4_cap_small_alloc(0);
        v = cL4_msg_alloc((void *)chunk, scratch_f8);
        cL4_slot_lock((void *)(obj + 0x60), scratch_f8);
        cL4_slot_commit((void *)(obj + 0x60), scratch_f8, 0, 0);
        /* map each frame chunk */
        for (i = 0; i < (frame >> 0xe); i++) {
            cL4_get_pair((void *)(obj + 0x60), scratch_a8);
            frame_list = (long *)cL4_field_value(scratch_a8, 0);
            v = (*(long (**)(void))cL4_vtbl6((unsigned long)frame_list))();   /* map */
            cL4_vtbl_apply3(scratch_a8);
            cL4_ref_release((void *)v);
            frame += 0x4000;
        }
        cL4_bv_resize3();
        cL4_ref_release((void *)list);
        cL4_ref_release((void *)*(unsigned long *)(obj + 0xb0));
    }
    r.lo = x24;
    r.hi = frame;
    return r;
}

/* FUN_000c9654 @ 0x000c9654   (est. cL4_vm_assemble_image)
 * Ghidra: void FUN_000c9654(void)
 * Assembles the final exclave launch image from the component/artifact
 * records collected by cL4_vm_build_launch_image. Iterates the launch
 * component list, mapping each named component's byte range into its final
 * physical frame, emitting AppleInternal build log markers per component,
 * and wiring the resolved frame descriptors into the global image table.
 * Completes by releasing all temporaries.
 * Confidence: low
 * Notes: Huge (0x2a34-byte) assembly function; per-component logging via
 *   FUN_00151a6c with s__AppleInternal_Library_BuildRoot; long bounds-checked
 *   frame walks. */
void cL4_vm_assemble_image(void)
{
    unsigned long obj = 0;    /* unaff_x20 */
    unsigned long ctx, v, cnt, i, base, frame;
    long *list, *node;

    ctx = cL4_cls13().hi;
    cL4_vm_build_launch_image();
    list = (long *)*(unsigned long *)(obj + 0x180);
    if (list == 0)
        __builtin_trap();
    cnt = *(unsigned long *)(list + 0x10);
    for (i = 0; i < cnt; i++) {
        if (*(unsigned long *)(list + 0x10) <= i)
            __builtin_trap();
        node = *(long **)(list + i * 8 + 0x20);
        v = (*(long (**)(void))(*node + 0x88))();
        cL4_ref_release2((void *)node);
        base = cL4_field_value((void *)node, 0);
        frame = (*(long (**)(void))cL4_vtbl6(base))();   /* map frame */
        cL4_vtbl_apply3((void *)0);
        cL4_ref_release((void *)frame);
        cL4_ref_release((void *)v);
    }
    cL4_ref_release((void *)list);
    cL4_ref_release((void *)node);
    (void)ctx;
}

/* FUN_000cc088 @ 0x000cc088   (est. cL4_vm_dispatch_pair)
 * Ghidra: void FUN_000cc088(undefined8 param_1, undefined8 param_2,
 *                           undefined8 param_3)
 * Forwards (param_2, param_3) to the descriptor-dispatch helper FUN_00071050.
 * Confidence: low */
void cL4_vm_dispatch_pair(unsigned long param_1, unsigned long param_2,
                          unsigned long param_3)
{
    (void)param_1;
    cL4_dispatch_helper(param_2, param_3);
}

/* FUN_000be3b0 @ 0x000be3b0   (est. cL4_cap_null_log)
 * Ghidra: undefined FUN_000be3b0(void)
 * Emits a capability-null log record: calls cL4_cap_null_const then forces
 * the result low word to 0x14, high word to 0xd000...<<48 (the null cap
 * constant), and returns.
 * Confidence: low
 * Notes: PAC frame; bl cL4_cap_null_const; mov/movk override. */
void cL4_cap_null_log(void)
{
    cL4_cap_null_const();
}

/* FUN_000bea70 @ 0x000bea70   (est. cL4_log_vm_event)
 * Ghidra: void FUN_000bea70(void)
 * Emits a VM-related capability event log record when DAT_006add10 is set:
 * allocates a message object, fills it with the event kind (0x20) and the
 * cap constant {0xd00000000000003e, 0x80000000005c3a70}, emits it, and
 * releases the capability reference.
 * Confidence: low
 * Notes: Standard event-log template (FUN_00002534/0036a9a0/0026b434). */
void cL4_log_vm_event(void)
{
    unsigned char scratch[64];
    unsigned long msg, v;

    if (DAT_006add10 != '\x01')
        return;
    v = cL4_intern((const char *)0x64c040, (void *)0x4bbf40);
    msg = cL4_msg_alloc((void *)v, scratch);
    *(unsigned long *)(msg + 0x18) = 0x4baeb8;
    *(unsigned long *)(msg + 0x10) = 0x4baeb0;
    *(unsigned long *)(msg + 0x38) = 0x6753a0;
    *(unsigned long *)(msg + 0x20) = 0xd00000000000003e;
    *(unsigned long *)(msg + 0x28) = 0x80000000005c3a70;
    cL4_cap_log(msg, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
    cL4_msg_release((void *)msg);
    v = cL4_current_token();
    cL4_cap_release((void *)v, 0x20, 7);
}

/* FUN_000beb2c @ 0x000beb2c   (est. cL4_log_aslr_slide)
 * Ghidra: void FUN_000beb2c(undefined8 param_1, long param_2, undefined8 param_3)
 * Emits an "ASLR Slide" capability event log record: allocates a message,
 * logs the "ASLR Slide" text ("SLS"|"ASLR"), the cap word {0xd00000000000001f,
 * 0x80000000005c32b0}, and param_2/param_3, then emits and releases.
 * Confidence: low
 * Notes: Text constants 0x696c5320524c5341 ("ASLR Sli") / 0xed000020676e6964. */
void cL4_log_aslr_slide(unsigned long param_1, long param_2, unsigned long param_3)
{
    unsigned char scratch[64];
    unsigned long msg, v;

    (void)param_1;
    if (DAT_006add10 != '\x01')
        return;
    v = cL4_intern((const char *)0x64c040, (void *)0x4bbf40);
    msg = cL4_msg_alloc((void *)v, scratch);
    *(unsigned long *)(msg + 0x18) = 0x4baeb8;
    *(unsigned long *)(msg + 0x10) = 0x4baeb0;
    cL4_log_kind(0x17);
    cL4_log_pair(0, 0xe000000000000000);
    cL4_log_pair(0x696c5320524c5341, 0xed000020676e6964);
    cL4_log_pair(*(unsigned long *)(param_2 + 8), *(unsigned long *)(param_2 + 0x10));
    cL4_log_pair(0x783020796220, 0xe600000000000000);
    cL4_log_pair(param_3, 0);
    *(unsigned long *)(msg + 0x38) = 0x6753a0;
    *(unsigned long *)(msg + 0x20) = 0x2045544d;
    *(unsigned long *)(msg + 0x28) = 0xe400000000000000;
    cL4_cap_log(msg, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
    cL4_msg_release((void *)msg);
    v = cL4_current_token();
    cL4_cap_release((void *)v, 0x20, 7);
    cL4_obj_free((void *)param_3);
}

/* FUN_000beca8 @ 0x000beca8   (est. cL4_log_dep_record)
 * Ghidra: void FUN_000beca8(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Emits a dependency-record capability event log message containing the cap
 * pair {0xd00000000000001f, 0x80000000005c32b0} and param_2/param_3, then
 * emits and releases param_3.
 * Confidence: low */
void cL4_log_dep_record(unsigned long param_1, unsigned long param_2,
                        unsigned long param_3)
{
    unsigned char scratch[64];
    unsigned long msg, v;

    (void)param_1;
    if (DAT_006add10 != '\x01') {
        cL4_obj_free((void *)param_3);
        return;
    }
    v = cL4_intern((const char *)0x64c040, (void *)0x4bbf40);
    msg = cL4_msg_alloc((void *)v, scratch);
    *(unsigned long *)(msg + 0x18) = 0x4baeb8;
    *(unsigned long *)(msg + 0x10) = 0x4baeb0;
    cL4_log_kind(0x21);
    cL4_log_pair(0, 0xe000000000000000);
    cL4_log_pair(param_2, param_3);
    *(unsigned long *)(msg + 0x38) = 0x6753a0;
    *(unsigned long *)(msg + 0x20) = 0xd00000000000001f;
    *(unsigned long *)(msg + 0x28) = 0x80000000005c32b0;
    cL4_cap_log(msg, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
    cL4_msg_release((void *)msg);
    v = cL4_current_token();
    cL4_cap_release((void *)v, 0x20, 7);
    cL4_obj_free((void *)param_3);
}

/* FUN_000bedd0 @ 0x000bedd0   (est. cL4_log_slide_kind)
 * Ghidra: void FUN_000bedd0(undefined8 param_1, ulong param_2, undefined8 param_3,
 *                           undefined8 param_4)
 * Emits a capability event log record describing a slide kind: selects the
 * "enabled"/"disabled" text pair based on param_2's low bit, appends the cap
 * {0xd000000000000014, 0x80000000005c3720}, param_3/param_4 and a trailing
 * count, then emits and releases param_4.
 * Confidence: medium
 * Notes: Text 0x64656c62616e65/0x64656c6261736964 ("enabled"/"disabled"). */
void cL4_log_slide_kind(unsigned long param_1, unsigned long param_2,
                        unsigned long param_3, unsigned long param_4)
{
    unsigned char scratch[64];
    unsigned long msg, v, t1, t2;
    int b;

    (void)param_1;
    if (DAT_006add10 != '\x01') {
        cL4_obj_free((void *)param_4);
        return;
    }
    v = cL4_intern((const char *)0x64c040, (void *)0x4bbf40);
    msg = cL4_msg_alloc((void *)v, scratch);
    *(unsigned long *)(msg + 0x18) = 0x4baeb8;
    *(unsigned long *)(msg + 0x10) = 0x4baeb0;
    cL4_log_kind(0x1d);
    cL4_log_pair(0, 0xe000000000000000);
    b = (param_2 & 1) == 0;
    t1 = 0x64656c62616e65;   /* enabled */
    t2 = 0xe700000000000000;
    if (b) {
        t1 = 0x64656c6261736964;   /* disabled */
        t2 = 0xe800000000000000;
    }
    cL4_log_pair(t1, t2);
    cL4_obj_free((void *)t2);
    cL4_log_pair(0xd000000000000014, 0x80000000005c3720);
    cL4_log_pair(param_3, param_4);
    cL4_log_pair(0x29, 0xe100000000000000);
    *(unsigned long *)(msg + 0x38) = 0x6753a0;
    *(unsigned long *)(msg + 0x20) = 0x2045544d;
    *(unsigned long *)(msg + 0x28) = 0xe400000000000000;
    cL4_cap_log(msg, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
    cL4_msg_release((void *)msg);
    v = cL4_current_token();
    cL4_cap_release((void *)v, 0x20, 7);
    cL4_obj_free((void *)param_4);
}

/* FUN_000bef74 @ 0x000bef74   (est. cL4_log_vm_exec)
 * Ghidra: void FUN_000bef74(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Emits a VM-exec capability event log record: appends the cap pair
 * {0xd000000000000020, 0x80000000005c3740}, param_2/param_3 and the cap
 * {0xd000000000000015, 0x80000000005c3770}, then emits and releases param_3.
 * Confidence: low */
void cL4_log_vm_exec(unsigned long param_1, unsigned long param_2,
                     unsigned long param_3)
{
    unsigned char scratch[64];
    unsigned long msg, v;

    (void)param_1;
    if (DAT_006add10 != '\x01') {
        cL4_obj_free((void *)param_3);
        return;
    }
    v = cL4_intern((const char *)0x64c040, (void *)0x4bbf40);
    msg = cL4_msg_alloc((void *)v, scratch);
    *(unsigned long *)(msg + 0x18) = 0x4baeb8;
    *(unsigned long *)(msg + 0x10) = 0x4baeb0;
    cL4_log_kind(0x37);
    cL4_log_pair(0xd000000000000020, 0x80000000005c3740);
    cL4_log_pair(param_2, param_3);
    cL4_log_pair(0xd000000000000015, 0x80000000005c3770);
    *(unsigned long *)(msg + 0x38) = 0x6753a0;
    *(unsigned long *)(msg + 0x20) = 0;
    *(unsigned long *)(msg + 0x28) = 0xe000000000000000;
    cL4_cap_log(msg, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
    cL4_msg_release((void *)msg);
    v = cL4_current_token();
    cL4_cap_release((void *)v, 0x20, 7);
    cL4_obj_free((void *)param_3);
}

/* FUN_000bf0c4 @ 0x000bf0c4   (est. cL4_log_mach_max)
 * Ghidra: void FUN_000bf0c4(void)
 * Emits a "MAX AMM/ADDR" capability event log record: prints the two text
 * halves ("ADDR RDD MAX"/"MAX AMM"), then emits the record and releases.
 * Confidence: low
 * Notes: Text 0x2058414d204e494d/0xed00002052444441 ("MAX AMM"/"ADDR ..."). */
void cL4_log_mach_max(void)
{
    unsigned char scratch[64];
    unsigned long msg, v;

    if (DAT_006add10 != '\x01')
        return;
    v = cL4_intern((const char *)0x64c040, (void *)0x4bbf40);
    msg = cL4_msg_alloc((void *)v, scratch);
    *(unsigned long *)(msg + 0x18) = 0x4baeb8;
    *(unsigned long *)(msg + 0x10) = 0x4baeb0;
    cL4_log_kind(0x16);
    cL4_log_pair(0, 0xe000000000000000);
    v = (unsigned long)cL4_pacia_fetch(0x671848);
    ((void (*)(unsigned long, unsigned long))v)(0x677790, 0x671848);
    cL4_log_pair(0, 0);
    cL4_obj_free((void *)0);
    cL4_log_pair(0x203a3a3a20, 0xe500000000000000);
    ((void (*)(unsigned long, unsigned long))v)(0x677790, 0x671848);
    cL4_log_pair(0, 0);
    cL4_obj_free((void *)0);
    *(unsigned long *)(msg + 0x38) = 0x6753a0;
    *(unsigned long *)(msg + 0x20) = 0x2058414d204e494d;
    *(unsigned long *)(msg + 0x28) = 0xed00002052444441;
    cL4_cap_log(msg, 0x20, 0xe100000000000000, 10, 0xe100000000000000);
    cL4_msg_release((void *)msg);
    v = cL4_current_token();
    cL4_cap_release((void *)v, 0x20, 7);
}

/* FUN_000be634 @ 0x000be634   (est. cL4_cap_to_string)
 * Ghidra: long FUN_000be634(undefined8 param_1, undefined8 param_2)
 * Renders a capability as a string into a growing buffer. Parses the cap
 * word (param_2): extracts the type field (bits 56..59, or the low 48 bits
 * when the 0x2000... bit is clear), then for each of the cap's slot entries
 * loads a byte (via the descriptor table or a string field at +0x10), appends
 * it to the result buffer (growing the vector as needed), and advances the
 * per-slot type state (cL4_rng_state / cL4_state_resolve). Completes by
 * finalizing the string (cL4_finalize_str) and returning the buffer.
 * Confidence: low
 * Notes: String-building over cap slots; FUN_000776cc acquire; FUN_000827a4
 *   buffer grow; cL4_rng_state/advance pair for slot type selection. */
unsigned long cL4_cap_to_string(unsigned long param_1, unsigned long param_2)
{
    unsigned long buf, typec, count, i, j, byte;
    unsigned long bvec[64];
    unsigned char tmp;

    (void)param_1;
    cL4_current();
    typec = (param_2 >> 0x38) & 0xf;
    if ((param_2 & 0x1000000000000000ull) != 0) {   /* tbnz 0x3c */
        /* deferred type handling */
        return cL4_state_resolve2();
    }
    bvec[0] = param_1 & 0xffffffffffffull;
    count = (param_2 & 0x2000000000000000ull) ? typec : (param_1 & 0xffffffffffffull);
    buf = 0;
    cL4_vec_resize((void **)&buf, 0, 0);
    i = 0;
    for (j = 0; j < count; j++) {
        byte = cL4_desc_load(0, 0) & 0xff;
        if (*(unsigned long *)(buf + 0x18) >> 1 <= *(unsigned long *)(buf + 0x10)) {
            cL4_vec_resize((void **)&buf, *(unsigned long *)(buf + 0x10) + 1, 1);
        }
        tmp = (unsigned char)byte;
        *(unsigned char *)(buf + *(unsigned long *)(buf + 0x10) + 0x20) = tmp;
        *(unsigned long *)(buf + 0x10) = *(unsigned long *)(buf + 0x10) + 1;
    }
    cL4_finalize_str(param_2, param_2, 0);
    return buf;
}

/* FUN_000be844 @ 0x000be844   (est. cL4_cap_log_set_walk)
 * Ghidra: long FUN_000be844(long param_1, undefined8 param_2)
 * Walks a capability set (param_1) emitting a log record per entry into the
 * set record at +0x28 (local_a8/&DAT_00657778). For each entry pair it
 * releases the old words, collects a {value,type} record (cL4_collect),
 * and appends a 0x28-byte record to the growing result list, growing it as
 * needed (cL4_realloc). When the count is exhausted it releases all
 * temporaries and returns the record list (unaff_x20+0x10).
 * Confidence: medium
 * Notes: Record stride 0x28; DAT_00657778 result head; cL4_collect per entry;
 *   record fields at +0x20..+0x40 of each 0x28-byte cell; only the
 *   decompiler register-forwarding (unaff_x20) is opaque. */
long cL4_cap_log_set_walk(long param_1, unsigned long param_2)
{
    unsigned char *result = (unsigned char *)0x65778;
    unsigned long cnt, i, v9, v1, r0, r1, r2, r3, r4, state, n;
    unsigned long obj = 0; /* unaff_x20 */
    unsigned char scratch[40];

    cnt = *(unsigned long *)(param_1 + 0x10);
    i = 0;
    while (1) {
        if (cnt == i) {
            cL4_ref_release((void *)param_1);
            if (*(unsigned long *)(result + 0x10) == 0) {
                cL4_ref_release((void *)result);
                cL4_ref_release((void *)param_2);
                return 0;
            }
            v9 = cL4_intern((const char *)0x64e1d8, (void *)0x4c2620);
            v9 = cL4_msg_field(v9, 0x20, 7);
            v9 = cL4_msg_attach(result, v9);
            cL4_ref_release((void *)param_2);
            *(unsigned long *)(obj + 0x10) = v9;
            return obj;
        }
        if (*(unsigned long *)(param_1 + 0x10) <= i)
            __builtin_trap();   /* SoftwareBreakpoint 0xbea28 */
        v9 = *(unsigned long *)(param_1 + 0x20 + i * 0x10);
        v1 = *(unsigned long *)(param_1 + 0x28 + i * 0x10);
        cL4_ref_release2((void *)v9);
        cL4_ref_release2((void *)v1);
        cL4_collect(scratch, v9, v1, param_2);
        r0 = cL4_field_value(scratch, 0);
        r1 = cL4_field_value(scratch, 1);
        r2 = cL4_field_value(scratch, 2);
        r3 = cL4_field_value(scratch, 3);
        r4 = cL4_field_value(scratch, 4);
        cL4_ref_release((void *)v1);
        cL4_ref_release((void *)v9);
        i++;
        if (r1 == 0)
            continue;           /* entry skipped (no record emitted) */
        /* append 0x28-byte record; grow the result list as needed */
        state = cL4_obj_state(result);
        if ((state & 1) == 0)
            result = (unsigned char *)cL4_realloc(0, *(unsigned long *)(result + 0x10) + 1, 1,
                                                  result);
        n = *(unsigned long *)(result + 0x10);
        if (*(unsigned long *)(result + 0x18) >> 1 <= n)
            result = (unsigned char *)cL4_realloc(1 < *(unsigned long *)(result + 0x18),
                                                  n + 1, 1, result);
        *(unsigned long *)(result + 0x10) = n + 1;
        *(unsigned long *)(result + n * 0x28 + 0x20) = r0;
        *(long *)(result + n * 0x28 + 0x28) = r1;
        *(unsigned long *)(result + n * 0x28 + 0x30) = r2;
        *(unsigned long *)(result + n * 0x28 + 0x38) = r3;
        *(unsigned long *)(result + n * 0x28 + 0x40) = r4;
    }
}

/* FUN_000bf26c @ 0x000bf26c   (est. cL4_fmt_descriptor)
 * Ghidra: void FUN_000bf26c(undefined8 *param_1)
 * Formats a capability descriptor record into the caller's buffer param_1.
 * If the descriptor's kind probe (cL4_kind_probe) has a clear low bit, the
 * 0x60-byte buffer is zeroed; otherwise the buffer is filled from the object
 * state and an interned string via cL4_cap_build, restoring the object
 * pointer.
 * Confidence: low
 * Notes: mirror of the getter/setter family; FUN_001fc840 build. */
void cL4_fmt_descriptor(unsigned char *param_1, unsigned long param_2)
{
    cl4_result_t kind;
    unsigned long obj = 0;   /* unaff_x20 */
    unsigned long state, str;
    unsigned char out[8], scratch[8];

    (void)param_2;
    kind = cL4_kind_probe((void *)0);
    if ((kind.hi & 1) == 0) {
        *(unsigned long *)((char *)param_1 + 0x62) = 0;
        *(unsigned long *)((char *)param_1 + 0x5a) = 0;
        ((unsigned long *)param_1)[9] = 0;
        ((unsigned long *)param_1)[8] = 0;
        ((unsigned long *)param_1)[11] = 0;
        ((unsigned long *)param_1)[10] = 0;
        ((unsigned long *)param_1)[5] = 0;
        ((unsigned long *)param_1)[4] = 0;
        ((unsigned long *)param_1)[7] = 0;
        ((unsigned long *)param_1)[6] = 0;
        ((unsigned long *)param_1)[1] = 0;
        ((unsigned long *)param_1)[0] = 0;
        ((unsigned long *)param_1)[3] = 0;
        ((unsigned long *)param_1)[2] = 0;
    } else {
        state = cL4_obj_state((void *)obj);
        str = cL4_intern((const char *)0x64e680, (void *)0x4c04d0);
        cL4_cap_build(out, scratch, kind.lo, state, str);
        obj = obj;   /* restore object pointer */
    }
}

/* FUN_000bf328 @ 0x000bf328   (est. cL4_vm_find_component_edges)
 * Ghidra: undefined * FUN_000bf328(code *param_1, undefined8 param_2,
 *                                  undefined8 param_3, undefined8 param_4,
 *                                  undefined8 param_5)
 * Walks a component/edge bitmap (param_3/param_4/param_5) looking for a
 * component matching the predicate *param_1. Iterates the set bit-vector
 * (reverse-bit LZCOUNT scan), resolves each candidate via the vtable method
 * *pcStack_70, and when the predicate *param_1 matches, records the component
 * into the global result list (DAT_00657788/98). Returns the collected list,
 * releasing temporaries on completion.
 * Confidence: low
 * Notes: Bit-vector walk over a 0x200-stride component table; DAT_00657778
 *   result head; predicate function pointer param_1. */
unsigned long *cL4_vm_find_component_edges(void *param_1, unsigned long param_2,
                                           unsigned long param_3, unsigned long param_4,
                                           unsigned long param_5)
{
    unsigned long x21 = 0;   /* unaff_x21 */
    unsigned long *result = (unsigned long *)0x65778;
    unsigned char scratch[24];
    unsigned long iter[4];
    unsigned long cnt, i, bit, v, slot, t;
    unsigned long (*pred)(unsigned long *) = param_1;
    void (*pick)(unsigned long *);

    cL4_iter_init(iter, param_3, param_4, param_5);
    cnt = iter[3];
    i = 0;
    while (1) {
        while (cnt != 0) {
            bit = (cnt & 0xaaaaaaaaaaaaaaaa) >> 1 | (cnt & 0x5555555555555555) << 1;
            bit = (bit & 0xcccccccccccccccc) >> 2 | (bit & 0x3333333333333333) << 2;
            bit = (bit & 0xf0f0f0f0f0f0f0f0) >> 4 | (bit & 0xf0f0f0f0f0f0f0f) << 4;
            bit = (bit & 0xff00ff00ff00ff00) >> 8 | (bit & 0xff00ff00ff00ff) << 8;
            bit = (bit & 0xffff0000ffff0000) >> 0x10 | (bit & 0xffff0000ffff) << 0x10;
            cnt &= cnt - 1;
            slot = *(unsigned long *)(*(unsigned long *)(iter[0] + 0x30) + bit * 8 + i * 0x200);
            pick = (void (*)(unsigned long *))iter[2];
            pred = (unsigned long (*)(unsigned long *))param_1;
            pick(&slot);
            if ((unsigned long)pred(&slot) & 1) {
                v = slot;
                if (((unsigned long (*)(unsigned long *))param_1)(&v) & 1) {
                    if (x21 != 0) {
                        cL4_ref_release((void *)0x65778);
                        cL4_ref_release((void *)0);
                        return (unsigned long *)cL4_ref_release((void *)0);
                    }
                    if (DAT_00657788 >= *(unsigned long *)0x65790 >> 1)
                        cL4_arr_reserve5(1 < *(unsigned long *)0x65790,
                                         DAT_00657788 + 1, 1);
                    slot = DAT_00657788 + 1;
                    DAT_00657788 = slot;
                    ((unsigned long *)0x65798)[slot - 1] = v;
                }
            }
        }
        i++;
        if ((long)((iter[1] + 0x40) >> 6) <= i) {
            cL4_ref_release((void *)0);
            cL4_ref_release((void *)0);
            return result;
        }
        cnt = *(unsigned long *)(iter[1] + i * 8);
    }
}

/* unmapped out-of-slice helpers used by FUN_000c1fb4 (addr in name) */
extern unsigned long FUN_000ad028(unsigned long a);
extern unsigned long FUN_00070390(unsigned long a);
extern unsigned long FUN_000a1630(void *out, unsigned long a, unsigned long b,
                                  const char *s, int d, int e, int f, unsigned long g);
extern unsigned long FUN_000a5650(unsigned long a, unsigned long b);
extern unsigned long FUN_000a5300(unsigned long a);
extern unsigned long FUN_000aeed8(unsigned long a);
extern unsigned long FUN_00083c58(int a);
extern unsigned long FUN_0007da4c(unsigned long a, unsigned long b, unsigned long c,
                                  unsigned long d, unsigned long e, unsigned long f,
                                  unsigned long g);
extern unsigned long *FUN_0011eaac(void);
extern unsigned long FUN_00258c60(unsigned long a, unsigned long b, unsigned long c);
extern void *FUN_000db620(unsigned long a);
extern unsigned long FUN_00651108(void);
extern void FUN_002591b4(unsigned long a);   /* noreturn (LAB_000c31c8) */
extern unsigned long FUN_000c32ac(void);     /* cL4_vm_find_kernel_component */
extern unsigned long FUN_000ade90(void);

/* FUN_000c1fb4 @ 0x000c1fb4   (est. cL4_vm_collect_frame_table)
 * Ghidra: undefined8 FUN_000c1fb4(undefined8 param_1, undefined8 param_2)
 * Collects the complete frame table for a VM's launch. Reads the object's
 * +0x20 capability slot and the +0x38 component map, then walks the map's
 * set-bit bitmap (+0x40) and, for each set slot, loads the component record
 * (0x70-stride at +0x38), builds a frame descriptor via cL4_vm_set_vm_list +
 * graph/string helpers, and appends a 0x58-byte frame record to the growing
 * result list (rec_list). In the "no components yet" case it re-enters via a
 * vtable +0x80/+0x88 call and walks a second map's +0x38 bitmap, appending
 * records with a fixed 0x661400 tag; a third section inserts/updates a record
 * in the descriptor map after parsing a decimal string.
 * Confidence: low
 * Notes: Huge (0x1224-byte) collector; record stride 0x58; LZCOUNT bit scan;
 *   the trailing string->int parse + map-insert (LAB_000c26cc) is dominated by
 *   decompiler register-forwarding (SUB168/ZEXT816/CARRY8/CONCAT71, auVar5..12)
 *   so is kept at a documented structural level; unaff_x20 register base. */
static inline unsigned long cL4_ctz64(unsigned long x)
{
    return __builtin_ctzll(x);
}

unsigned long cL4_vm_collect_frame_table(unsigned long param_1, unsigned long param_2)
{
    unsigned long obj = 0;   /* unaff_x20 */
    unsigned char sc_48[24], sc_40[24], sc_88[24], sc_90[24], sc_c8[24], sc_e0[24], sc_358[24], sc_380[24];
    unsigned long rec[16];    /* local_220 record accumulator */
    unsigned long acc[16];    /* local_170 */
    unsigned long grp[16];    /* local_2c0 graph context */
    unsigned long sub[16];    /* local_330 */
    unsigned long cur[16];    /* local_250 slot-load / working pair */
    unsigned long prev[16];   /* local_228 */
    unsigned long rec_list, map, map2, desc_map, bits, v, i, j, bit, slot;
    unsigned long uVar15, uVar19, uVar20, uVar21, uVar22, uVar34, uVar36, uVar37;
    unsigned long lo, hi, res, idx, cnt, n, setflag, state;
    cl4_result_t vres;
    unsigned short uVar4;
    unsigned char uVar3, f3fc, f3fc2;
    void *(*fn)(void);
    unsigned long *vtab, *vtab2;
    cl4_result_t hit;
    unsigned long *src;

    cL4_slot_commit((void *)(obj + 0x20), sc_c8, 0, 0);
    uVar36 = *(unsigned long *)(obj + 0x20);
    cL4_ref_release2((void *)uVar36);
    uVar15 = FUN_000ad028(param_2);
    cL4_ref_release((void *)uVar36);
    cL4_slot_commit((void *)(obj + 0x38), sc_e0, 0, 0);
    rec_list = (unsigned long)cL4_arr_grow(0, *(unsigned long *)(*(unsigned long *)(obj + 0x38) + 0x10),
                                           0, (void *)0x65778);
    map = *(unsigned long *)(obj + 0x38);
    bits = 1ull << (*(unsigned char *)(map + 0x20) & 0x3f);
    v = ~0ull;
    if ((*(unsigned char *)(map + 0x20) & 0x3f) < 6)
        v = ~(-1L << (bits & 0x3f));
    v &= *(unsigned long *)(map + 0x40);
    cL4_ref_release2((void *)0);
    i = 0;
    /* ---- first walk: +0x40 bitmap of the +0x38 map ---- */
    while (1) {
        while (v == 0) {
            n = i + 1;
            if (n < i)
                __builtin_trap();          /* SCARRY 0xc3154 */
            if ((long)((bits + 0x3f) >> 6) <= n) {
                /* bitmap exhausted: proceed to build with empty acc */
                v = 0;
                goto build_record;
            }
            i = n;
            v = ((unsigned long *)(map + 0x40))[i];
        }
        bit = i * 64 + cL4_ctz64(v);
        slot = *(unsigned long *)(*(unsigned long *)(map + 0x30) + bit * 8);
        v &= v - 1;
        cL4_slot_load((void *)(*(unsigned long *)(map + 0x38) + bit * 0x70), &rec[0]);
build_record:
        /* record accumulator (local_228/240/248/230/238, local_250) */
        uVar37 = prev[0];                  /* local_228 */
        slot = cur[0];                     /* local_250 */
        cL4_memcpy(&acc[0], &rec[0], 0x42);
        if (uVar37 == 0) {
            /* no-components-yet path: re-enter via vtable +0x80/+0x88 */
            cL4_ref_release((void *)map);
            uVar34 = cL4_intern((const char *)0x651100, (void *)0x4c2608);
            desc_map = cL4_descriptor(0x65778, 0x677790, uVar34, 0x6718b8);
            vtab = *(unsigned long **)(obj + 0x20);
            fn = (void *(*)(void))(*vtab + 0x80);
            cL4_ref_release2((void *)vtab);
            vtab2 = (unsigned long *)fn();
            cL4_ref_release((void *)vtab);
            map2 = (unsigned long)(*(unsigned long *(*)(void))(*vtab2 + 0x88))();
            cL4_ref_release((void *)vtab2);
            i = 0;
            bits = 1ull << (*(unsigned char *)(map2 + 0x20) & 0x3f);
            v = ~0ull;
            if ((*(unsigned char *)(map2 + 0x20) & 0x3f) < 6)
                v = ~(-1L << (bits & 0x3f));
            v &= *(unsigned long *)(map2 + 0x38);
            map = map2;
            break;                          /* -> second phase */
        }
        /* full frame record build for the found slot */
        cL4_memcpy(&prev[0], &acc[0], 0x42);
        cL4_slot_load(sc_380, (void *)slot);   /* cL4_vm_desc_lookup (FUN_000c31d8) */
        if (*(unsigned long *)sc_380 == 0)
            __builtin_trap();              /* 0xc3184 */
        cL4_copy_pair(sc_380, sc_358);
        if (*(long *)(*(unsigned long *)grp + 0x10) == 0)
            __builtin_trap();              /* 0xc3160 */
        cL4_memcpy(&grp[0], (void *)(*(unsigned long *)grp + 0x20), 0x42);
        uVar4 = (unsigned short)rec[0];    /* local_220 lo */
        uVar21 = grp[6];                   /* uStack_338 */
        uVar34 = grp[5];                   /* local_340 */
        cL4_field_value(sc_358, uVar34);
        cL4_graph_push(&grp[0], sub);
        vres = ((cl4_result_t (*)(unsigned long, unsigned long))
                cL4_pacia_fetch(uVar21))(uVar34, uVar21);
        uVar21 = vres.hi;
        uVar34 = vres.lo;
        cL4_graph_push(&grp[0], sub);
        uVar19 = cL4_str_id(uVar34, uVar21);
        cL4_graph_pop(&grp[0]);
        cL4_graph_push(&grp[0], sub);
        uVar20 = cL4_name_hash2();
        cL4_graph_pop(&grp[0]);
        uVar21 = grp[6];
        uVar34 = grp[5];
        cL4_field_value(sc_358, uVar34);
        uVar21 = ((unsigned long (*)(unsigned long, unsigned long))
                  FUN_000db620(uVar21))(uVar34, uVar21);
        cL4_vm_set_vm_list((unsigned long)sub, bit);
        slot = sub[0];
        cL4_ref_release2((void *)sub[0]);
        cL4_field_free(sub);
        uVar22 = FUN_00070390((uVar15 ^ 1) & 1);
        cL4_graph_pop(&grp[0]);
        cL4_ref_release((void *)slot);
        uVar34 = rec[0x1e / 8 + 0];        /* local_1f0 */
        uVar3 = (unsigned char)rec[0x1e / 8 + 1]; /* local_1e8 */
        /* append 0x58-byte frame record to rec_list */
        cnt = *(unsigned long *)(rec_list + 0x10);
        if (*(unsigned long *)(rec_list + 0x18) >> 1 <= cnt)
            rec_list = (unsigned long)cL4_arr_grow(1 < *(unsigned long *)(rec_list + 0x18),
                                                   cnt + 1, 1, (void *)rec_list);
        *(unsigned long *)(rec_list + 0x10) = cnt + 1;
        j = rec_list + cnt * 0x58;
        *(unsigned long *)(j + 0x20) = bit;
        *(unsigned short *)(j + 0x28) = uVar4;
        cL4_memcpy((void *)(j + 0x30), &vres, 0x10);
        *(unsigned long *)(j + 0x40) = uVar19;
        *(unsigned long *)(j + 0x48) = uVar20;
        *(unsigned long *)(j + 0x50) = grp[0];
        *(unsigned long *)(j + 0x58) = uVar21;
        *(unsigned long *)(j + 0x60) = uVar22;
        *(unsigned long *)(j + 0x68) = uVar34;
        *(unsigned char *)(j + 0x70) = uVar3;
        cL4_field_free(&cur[0]);
        cL4_field_free(sc_358);
    }
    /* ---- second phase: walk map's +0x38 bitmap, then the +0x38 descriptor map ---- */
    while (v == 0) {
        n = i + 1;
        if (n < i)
            __builtin_trap();              /* SCARRY 0xc3158 */
        if ((long)((bits + 0x3f) >> 6) <= n) {
            cL4_ref_release((void *)map);
            bits = 1ull << (*(unsigned char *)(desc_map + 0x20) & 0x3f);
            v = ~0ull;
            if ((*(unsigned char *)(desc_map + 0x20) & 0x3f) < 6)
                v = ~(-1L << (bits & 0x3f));
            v &= *(unsigned long *)(desc_map + 0x40);
            cL4_ref_release2((void *)desc_map);
            i = 0;
            while (1) {
                for (; v != 0; v &= v - 1) {
                    bit = i * 64 + cL4_ctz64(v);
                    uVar22 = *(unsigned long *)(*(unsigned long *)(desc_map + 0x30) + bit * 8);
                    src = (unsigned long *)(*(unsigned long *)(desc_map + 0x38) + bit * 0x28);
                    uVar4 = (unsigned short)*src;
                    uVar34 = src[1];
                    uVar21 = src[2];
                    uVar20 = src[3];
                    uVar3 = (unsigned char)src[4];
                    cL4_cap_release((void *)uVar21, 2, 0);
                    cL4_vm_set_vm_list((unsigned long)&cur[0], uVar22);
                    uVar37 = cur[0];
                    cL4_ref_release2((void *)cur[0]);
                    cL4_field_free(&cur[0]);
                    uVar19 = FUN_00070390(1);
                    cL4_obj_free((void *)uVar21);
                    cL4_ref_release((void *)uVar37);
                    cnt = *(unsigned long *)(rec_list + 0x10);
                    if (*(unsigned long *)(rec_list + 0x18) >> 1 <= cnt)
                        rec_list = (unsigned long)cL4_arr_grow(1 < *(unsigned long *)(rec_list + 0x18),
                                                               cnt + 1, 1, (void *)rec_list);
                    *(unsigned long *)(rec_list + 0x10) = cnt + 1;
                    j = rec_list + cnt * 0x58;
                    *(unsigned long *)(j + 0x20) = uVar22;
                    *(unsigned short *)(j + 0x28) = uVar4;
                    *(unsigned long *)(j + 0x30) = uVar34;
                    *(unsigned long *)(j + 0x38) = uVar21;
                    *(unsigned long *)(j + 0x40) = 0x661400;
                    *(unsigned long *)(j + 0x48) = 0;
                    *(unsigned long *)(j + 0x50) = 0;
                    *(unsigned long *)(j + 0x58) = 0;
                    *(unsigned long *)(j + 0x60) = uVar19;
                    *(unsigned long *)(j + 0x68) = uVar20;
                    *(unsigned char *)(j + 0x70) = uVar3;
                }
                n = i + 1;
                if (n < i)
                    break;                 /* SCARRY 0xc315c */
                if ((long)((bits + 0x3f) >> 6) <= n) {
                    cL4_ref_release((void *)desc_map);
                    if ((uVar15 & 1) == 0) {
                        v = 0;
                    } else {
                        cL4_slot_commit((void *)(obj + 0x90), sc_358, 0, 0);
                        uVar34 = *(unsigned long *)(obj + 0x90);
                        cL4_ref_release2((void *)uVar34);
                        FUN_000a1630(&cur[0], 0xd000000000000027, 0x80000000005c3850,
                                     "__AppleInternal_Library_BuildRoot...", 0xfb, 2, 0x293, uVar34);
                        cL4_ref_release((void *)uVar34);
                        if (cur[1] >> 0x2c != 0)
                            __builtin_trap();   /* 0xc3164 */
                        v = cur[1] << 0x14;
                    }
                    cL4_slot_commit((void *)(obj + 0x88), &acc[0], 0, 0);
                    vtab = *(unsigned long **)(obj + 0x88);
                    fn = (void *(*)(void))(*vtab + 0x88);
                    cL4_ref_release2((void *)vtab);
                    uVar34 = (unsigned long)fn();
                    cL4_ref_release((void *)vtab);
                    cL4_slot_commit((void *)(obj + 0x58), &grp[0], 0, 0);
                    uVar19 = *(unsigned long *)(obj + 0x58);
                    cL4_ref_release2((void *)uVar19);
                    uVar21 = FUN_000a5650(uVar34, uVar19);
                    cL4_ref_release((void *)uVar34);
                    cL4_ref_release((void *)uVar19);
                    cL4_slot_commit((void *)(obj + 0x90), sub, 0, 0);
                    vtab = *(unsigned long **)(obj + 0x88);
                    uVar34 = *(unsigned long *)(obj + 0x90);
                    fn = (void *(*)(void))(*vtab + 0x88);
                    cL4_ref_release2((void *)rec_list);
                    cL4_ref_release2((void *)uVar34);
                    cL4_ref_release2((void *)vtab);
                    uVar19 = (unsigned long)fn();
                    cL4_ref_release((void *)vtab);
                    uVar20 = FUN_000a5300(uVar19);
                    cL4_ref_release((void *)uVar19);
                    uVar19 = FUN_000c32ac();
                    uVar36 = *(unsigned long *)(obj + 0x20);
                    cL4_ref_release2((void *)uVar36);
                    uVar22 = FUN_000aeed8(param_2);
                    cL4_ref_release((void *)rec_list);
                    cL4_ref_release((void *)uVar36);
                    uVar36 = FUN_00083c58(0);
                    cL4_msg_field(uVar36, 0x59, 7);
                    uVar34 = FUN_0007da4c(rec_list, uVar34, uVar20, v >> 0xd, uVar19, uVar21, uVar22);
                    cL4_obj_free((void *)uVar36);
                    return uVar34;
                }
                v = ((unsigned long *)(desc_map + 0x40))[n];
                i = n;
            }
            __builtin_trap();              /* 0xc315c unreachable */
        }
        v = ((unsigned long *)(map + 0x38))[n];
        i = n;
    }
    /* ---- map2 bitmap walk: load the slot record, then the descriptor-map
     * insert/update with a decimal-string parse (register-forward heavy) ---- */
    bit = i * 64 + cL4_ctz64(v);
    slot = (unsigned long)cL4_ref_release2(
        (void *)*(unsigned long *)(*(unsigned long *)(map + 0x30) + bit * 8));
    uVar34 = FUN_000ade90();
    cL4_slot_commit((void *)(obj + 0x38), &cur[0], 0x20, 0);
    res = *(unsigned long *)(obj + 0x38);
    for (n = 0; n < 16; n++)
        acc[n] = 0;
    if (*(long *)(res + 0x10) == 0)
        goto tail_load;                    /* LAB_000c2530 */
    hit = cL4_kind_probe((void *)uVar34);
    if ((hit.hi & 1) == 0)
        goto tail_load;                    /* LAB_000c2530 */
    cL4_slot_load((void *)(*(unsigned long *)(res + 0x38) + hit.lo * 0x70), &acc[0]);
tail_load:
    v &= v - 1;
    cL4_slot_done(&cur[0]);
    cL4_memcpy(&cur[0], &acc[0], 0x6a);
    if (prev[0] == 0) {                    /* uStack_230 */
        /* LAB_000c2630: descriptor-map insert/update + decimal string parse.
         * The parse (LAB_000c26cc) is dominated by decompiler register
         * forwarding (SUB168/ZEXT816/CARRY8/CONCAT71, auVar5..12) and is kept
         * at this documented structural level. */
        cL4_fmt(&cur[0], (const char *)0x650f48, (void *)0x4c2490);
        goto tail_done;
    }
    cL4_str_field(&cur[0], &grp[0], (const char *)0x650f48, (void *)0x4c2490);
    if (grp[0] == 0) {
        cL4_field_free(&grp[0]);
        cL4_fmt(&cur[0], (const char *)FUN_00651108(), (void *)0x4c2610);
    } else {
        cL4_memcpy(sub, &prev[0], 0x6a);
        res = grp[0];
        idx = sub[0];
        cL4_field_free(sub);
        cL4_field_free(&grp[0]);
        cL4_fmt(&cur[0], (const char *)0x650f48, (void *)0x4c2490);
        if (res == idx)
            goto tail_done;                /* LAB_000c2630 */
    }
tail_done:
    cL4_ref_release((void *)slot);
    /* Re-enters the second-phase walk (joined_r0x000c2494) in the decompile;
     * the register-forward-heavy decimal parse + map-insert at LAB_000c26cc
     * is not expressible 1:1 and is left at this documented level. */
    return rec_list;
}
