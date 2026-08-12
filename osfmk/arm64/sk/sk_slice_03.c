/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 03: 0x1a2f4-0x20c88.
 * This slice is the Tightbeam binary-serialization subsystem: the
 * ComponentInitData (component configuration payload) reader/validator, the
 * TransportBuffer (contiguous byte-slice with position tracking), the
 * ForwardingConnection glue, and the low-level tagged-data encode/decode
 * primitives (TYPEDATA/INITDATA/COMPDATA/ENDPDATA/CLNTDATA records).
 * Register-argument functions (x20 "self", x21 "flag") model those args as
 * explicit leading parameters; Ghidra's unaff_x20/x21 are noted in comments. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (extern with a one-line note;
 * bodies reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_001afa84 @ 0x1afa84 — noreturn fatal-error reporter (msg, kind, flags,
 * status-hi, status-lo, module-name, module-kind, module-flags, line, 0). */
extern void cL4_fatal_1afa84(void *msg, uint64_t kind, uint64_t flags, ...) __attribute__((noreturn));
/* FUN_0011d7e8 @ 0x11d7e8 — noreturn stack-canary-check panic on mismatch. */
extern void cL4_canary_panic_11d7e8(void) __attribute__((noreturn));
/* SoftwareBreakpoint(1, addr) — invariant-violation trap. */
extern void cL4_breakpoint(uint64_t addr) __attribute__((noreturn));
/* FUN_00117d14 @ 0x117d14 — byte copy (memmove): (dst, src, len). */
extern void cL4_memmove_117d14(void *dst, const void *src, uint64_t len);
/* FUN_00117cc4 @ 0x117cc4 — byte copy (memcpy): (dst, src, len). */
extern void cL4_memcpy_117cc4(void *dst, const void *src, uint64_t len);
/* thunk_FUN_00115080 @ 0x115080 — returns a byte length/offset (query). */
extern long cL4_len_query_115080(void);
/* FUN_001e9c78 @ 0x1e9c78 — release/commit a (base,size) memory range. */
extern void cL4_mem_release_1e9c78(uint64_t base, uint64_t size);
/* thunk_FUN_0036b270 @ 0x36b270 — retain (increment refcount of) obj. */
extern void cL4_retain_36b270(uint64_t obj);
/* FUN_0036b118 @ 0x36b118 — release (decrement refcount of) obj. */
extern void cL4_release_36b118(uint64_t obj);
/* FUN_0036a1a0 @ 0x36a1a0 — context/stack-frame setup (ctx, frame, k, a). */
extern void cL4_ctx_setup_36a1a0(uint64_t ctx, void *frame, uint64_t k, uint64_t a);
/* FUN_0036b8b0 @ 0x36b8b0 — context op returning a value/pointer. */
extern uint64_t cL4_ctx_get_36b8b0(uint64_t ctx);
/* FUN_0036b834 @ 0x36b834 — context op (ctx, val). */
extern void cL4_ctx_set_36b834(uint64_t ctx, uint64_t val);
/* FUN_0036b7f8 @ 0x36b7f8 — context init (ctx, val). */
extern void cL4_ctx_init_36b7f8(uint64_t ctx, uint64_t val);
/* FUN_0036b6ac @ 0x36b6ac — context cleanup. */
extern void cL4_ctx_done_36b6ac(void);
/* FUN_0036b21c @ 0x36b21c — context teardown. */
extern void cL4_ctx_destroy_36b21c(void);
/* FUN_0036b8c0 @ 0x36b8c0 — context op (void). */
extern void cL4_ctx_void_36b8c0(uint64_t ctx);
/* FUN_0036a908 @ 0x36a908 — allocate a sized object (size, tag). */
extern void *cL4_alloc_36a908(uint64_t size, uint64_t tag);
/* FUN_0036a940 @ 0x36a940 — allocate object (type/size/tag/kind). */
extern void *cL4_alloc_36a940(void);
/* FUN_003698b0 @ 0x3698b0 — log/error reporter (local, str, kind, ...). */
extern void cL4_log_3698b0(void *local, uint64_t str, uint64_t kind, ...);
/* FUN_003a25d4 @ 0x3a25d4 — log a value/word. */
extern void cL4_log_val_3a25d4(uint64_t v);
/* FUN_003a261c @ 0x3a261c — query; low bit of result is a flag. */
extern uint64_t cL4_query_3a261c(uint64_t obj);
/* FUN_002b24b8 @ 0x2b24b8 — resolve the byte size of a tagged value. */
extern uint64_t cL4_size_resolve_2b24b8(uint64_t tag, uint64_t word);
/* FUN_0001a1dc @ 0x1a1dc — copy tagged data bytes into a destination. */
extern long cL4_tagdata_copy_1a1dc(void *dst, void *dst_end, uint64_t tag, uint64_t word);
/* FUN_00376820 @ 0x376820 — allocate/initialize a module (type-addr, id). */
extern uint64_t cL4_mod_init_376820(uint64_t type, uint64_t id);
/* FUN_00015388 @ 0x15388 — build an error/exception value (code, a, b). */
extern uint64_t cL4_err_15388(uint64_t code, uint64_t a, uint64_t b);
/* FUN_0001532c @ 0x1532c — build an error/exception value (code, a). */
extern uint64_t cL4_err_1532c(uint64_t code, uint64_t a);
/* FUN_00017b88 @ 0x17b88 — async task dispatch (a, b, engine). */
extern uint64_t cL4_task_run_17b88(uint64_t a, uint64_t b, uint64_t engine);
/* FUN_00017b7c @ 0x17b7c — async task dispatch (a, b, engine). */
extern uint64_t cL4_task_run_17b7c(uint64_t a, uint64_t b, uint64_t engine);
/* FUN_00017a08 @ 0x17a08 — async task dispatch (a, b, c, engine). */
extern uint64_t cL4_task_run_17a08(uint64_t a, uint64_t b, uint64_t c, uint64_t engine);
/* FUN_00017bd4 @ 0x17bd4 — cancel/abort a pending task. */
extern void cL4_task_abort_17bd4(void);
/* FUN_000259c0 @ 0x259c0 — serialize/hash a tag pair into a buffer. */
extern void cL4_tag_hash_259c0(void *out, uint64_t v);
/* FUN_0004b520 @ 0x4b520 — set up a task-engine request (desc-stack). */
extern uint64_t cL4_engine_setup_4b520(void *desc);
/* FUN_0004b664 @ 0x4b664 — tear down a task-engine request. */
extern void cL4_engine_done_4b664(uint64_t engine);
/* FUN_002a4ab4 @ 0x2a4ab4 — log a kind word. */
extern void cL4_log_kind_2a4ab4(uint64_t kind);
/* thunk_FUN_002acbb8 @ 0x2acbb8 — log a message (variadic pair stream). */
extern void cL4_log_msg_2acbb8(uint64_t a, ...);
/* FUN_001ba7d4 @ 0x1ba7d4 — log with a module (kind, mod-ptr). */
extern void cL4_log_mod_1ba7d4(uint64_t kind, uint64_t mod);
/* FUN_00205844 @ 0x205844 — error reporter (local, payload, str, a, b). */
extern void cL4_log_err_205844(void *local, uint64_t payload, uint64_t str, uint64_t a, uint64_t b);
/* FUN_0029fa0c @ 0x29fa0c — memory/page-table op (a, b, c). */
extern void cL4_mem_op_29fa0c(uint64_t a, uint64_t b, uint64_t c);
/* FUN_00294cb4 @ 0x294cb4 — byte copy of a validated region (src, len). */
extern uint64_t cL4_copy_294cb4(void *src, uint64_t len);
/* FUN_002a9ba8 @ 0x2a9ba8 — resolve a size pair {ptr,size}. */
extern uint64_t cL4_pair_resolve_2a9ba8(uint64_t tag, uint64_t word);
/* FUN_002b5ba0 @ 0x2b5ba0 — resolve a tagged value. */
extern void cL4_resolve_2b5ba0(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e);
/* FUN_002b141c @ 0x2b141c — advance/normalize a page pointer. */
extern uint64_t cL4_page_advance_2b141c(uint64_t ptr, uint64_t a, uint64_t b);
/* FUN_002b15d0 @ 0x2b15d0 — page-tree length query (a, b, c). */
extern long cL4_pagetree_len_2b15d0(uint64_t a, uint64_t b, uint64_t c);
/* FUN_002a4614 @ 0x2a4614 — page-tree op (a, b). */
extern uint64_t cL4_pagetree_op_2a4614(uint64_t a, uint64_t b);
/* thunk_FUN_001b1ff0 @ 0x1b1ff0 — page-tree op variant. */
extern uint64_t cL4_pagetree_op_1b1ff0(uint64_t a);
/* FUN_0024917c @ 0x24917c — combine/hash two values into a result pair. */
extern void cL4_hash_pair_24917c(void *out, void *in);
/* thunk_FUN_0024d9ac @ 0x24d9ac — acquire a lock/ref (returns handle). */
extern uint64_t cL4_lock_2d9ac(uint64_t target);
/* FUN_00002534 @ 0x2534 — allocate an object from a type descriptor. */
extern void *cL4_type_alloc_2534(void *type, void *meta);
/* thunk_FUN_000126e8 @ 0x126e8 — allocator query returning size/handle. */
extern long cL4_alloc_query_126e8(void);
/* FUN_0035dc24 @ 0x35dc24 — wrap a value with a type/ownership label. */
extern void cL4_wrap_35dc24(void *out, void *val, void *label);
/* FUN_0035d334 @ 0x35d334 — unwrap a labeled value. */
extern void cL4_unwrap_35d334(void *val, void *label);
/* thunk_FUN_00012568 @ 0x12568 — object finalize/deinit. */
extern void cL4_finalize_12568(void *obj);
/* FUN_00020d0c @ 0x20d0c — TransportBuffer state write (a, b, c, d). */
extern void FUN_00020d0c(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
/* FUN_00020d20 @ 0x20d20 — TransportBuffer entry helper. */
extern void FUN_00020d20(void);
/* FUN_00023f74 @ 0x23f74 — scoped-record dispatch (tag, a, b, cb, frame, kind, meta). */
extern void FUN_00023f74(uint64_t tag, uint64_t a, uint64_t b, uint64_t cb,
                         void *frame, uint64_t kind, uint64_t meta);
/* FUN_00310d34 @ 0x310d34 — object/module release op (a, b). */
extern void FUN_00310d34(uint64_t a, uint64_t *b);
extern uint64_t UINT_006775b0;                     /* _UINT_006775b0 release sentinel */
/* Null singleton buffer object (DAT_00657778): the empty-array base. */
extern uint64_t DAT_00657778;
extern uint64_t DAT_00657788;
/* FUN_0001deb0 @ 0x1deb0 — store cL4_array_grow result at x20 (in-slice). */
/* FUN_0001ef60 / FUN_0001ef64 @ 0x1ef60/0x1ef64 — record callbacks (in-slice). */
/* FUN_002e2d24 @ 0x2e2d24 — TransportBuffer write (msg, src, end, a, b). */
extern void FUN_002e2d24(uint64_t msg, void *src, void *end, uint64_t a, uint64_t b);
/* thunk_FUN_002298d4 @ 0x2298d4 — forward a byte/word (dispatch helper). */
extern void FUN_002298d4(uint64_t a, uint64_t b);
/* FUN_001a84f4 @ 0x1a84f4 — context frame setup (frame, flags). */
extern void FUN_001a84f4(void *frame, uint64_t flags);
/* FUN_001a8564 @ 0x1a8564 — context frame teardown. */
extern void FUN_001a8564(void);
/* FUN_0036a804 @ 0x36a804 — allocate an object (size, tag). */
extern uint64_t FUN_0036a804(uint64_t size, uint64_t tag);
/* FUN_00015708 @ 0x15708 — register/install a closure (in-slice pair setup). */
extern void FUN_00015708(void);
/* FUN_0001a1c8 @ 0x1a1c8 — closure/entry (in-slice); address taken as a fn ptr. */
extern uint64_t FUN_0001a1c8(void);
/* FUN_00019aac @ 0x19aac — build an error/exception (kind). */
extern uint64_t FUN_00019aac(uint64_t kind);
extern uint64_t FUN_0065a550;   /* log label anchor DAT at 0x65a550 */
/* Out-of-range alloc/module-init helpers (FUN_ names as used in call sites). */
extern uint64_t FUN_0036a940(void);
extern uint64_t FUN_00376820(uint64_t type, uint64_t id);
/* FUN_-named aliases for out-of-range helpers used directly in call sites. */
extern uint64_t FUN_00015388(uint64_t code, uint64_t a, uint64_t b);
extern uint64_t FUN_0001532c(uint64_t code, uint64_t a);
extern uint64_t FUN_00017b88(uint64_t a, uint64_t b, uint64_t engine);
extern uint64_t FUN_00017b7c(uint64_t a, uint64_t b, uint64_t engine);
extern uint64_t FUN_00017a08(uint64_t a, uint64_t b, uint64_t c, uint64_t engine);
extern void FUN_00017bd4(void);
extern uint64_t FUN_0004b520(void *desc);
extern void FUN_0004b664(uint64_t engine);
extern void FUN_0029fa0c(uint64_t a, uint64_t b, uint64_t c);
extern void FUN_003698b0(void *local, uint64_t str, uint64_t kind, ...);

/* Module name strings referenced by the fatal-error reporter. */
extern const char cL4_s_Tightbeam_ComponentInitData[];   /* s_Tightbeam_ComponentInitData_swif_005ac9c0 */
extern const char cL4_s_Fatal_error[];                   /* s_Fatal_error_005accd0 */
extern const char cL4_s_Tightbeam_TransportBuffer[];     /* s_Tightbeam_TransportBuffer_swift_005accb0 */
extern const char cL4_s_Tightbeam_ForwardingConnection[];/* s_Tightbeam_ForwardingConnection_s_005acc20 */
extern const char cL4_s_TransportBuffer_has_insufficient[];  /* s_..._005acd50 */
extern const char cL4_s_TransportBuffer_was_already_forg[];  /* s_..._005acd20 */
extern const char cL4_s_TransportBuffer_position_is_out[];   /* s_..._005acd80 */
extern const char cL4_s_TransportBuffer_has_illegal_rese[];  /* s_..._005acdb0 */
extern const char cL4_s_TransportBuffer_has_illegal_data[];  /* s_..._005acde0 */
extern const char cL4_s_TransportBuffer_has_illegal_raw_d[]; /* s_..._005ace10 */

/* Globals written by module-init singletons. */
extern uint64_t cL4_mod_677880;   /* DAT_0064c0f8 (ComponentInitData module) */
extern uint64_t cL4_mod_677790;   /* DAT_0064c100 (TransportBuffer module) */

/* Tagged-data record magic values (read big-endian as ASCII). */
#define TB_TAG_TYPEDATA  0x5459504544415441ull  /* "TYPEDATA" */
#define TB_TAG_INITDATA  0x494e495444415441ull  /* "INITDATA" */
#define TB_TAG_COMPDATA  0x434f4d5044415441ull  /* "COMPDATA" */
#define TB_TAG_ENDPDATA  0x454e445044415441ull  /* "ENDPDATA" */
#define TB_TAG_CLNTDATA  0x434c4e5444415441ull  /* "CLNTDATA" */

/* ------------------------------------------------------------------ *
 * Forward declarations of in-slice functions called out of order.
 * (Definitions appear in address order below.)
 * ------------------------------------------------------------------ */
static uint64_t FUN_0001a760(void *self);
static void FUN_0001ef60(uint64_t a, uint64_t b, uint64_t *self);
static void FUN_0001ef64(uint64_t a, uint64_t b, uint64_t *self);
static void FUN_000208a8(uint64_t tb, uint64_t one, void *entry, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h);
static long FUN_0001a4f0(uint64_t *dst, uint64_t dst_end, uint64_t tag, uint64_t word);
static long FUN_0001a838(uint64_t *dst, uint64_t dst_end, void *self, uint64_t flag);
static long FUN_0001afb4(uint64_t tag, uint64_t word, uint64_t a, uint64_t b);
static long FUN_0001b02c(uint64_t *dst, uint64_t dst_end, uint64_t tag, uint64_t word,
                         uint64_t a, uint64_t b, uint64_t flag);
static long FUN_0001dfb4(void *a);
static long FUN_0001b370(uint64_t a, uint64_t b);
static void FUN_0001db00(uint64_t pos, uint64_t val, uint64_t end, uint64_t base, uint64_t lim,
                         uint64_t *out_lo, uint64_t *out_hi);
static void *FUN_0001db94(long n);
static void *FUN_0001dc08(long n, long m);
static void *FUN_0001dc8c(long n, long m);
static void *FUN_0001dde4(uint64_t flags, uint64_t n, uint64_t grow, void *buf);
static void *FUN_0001dd14(uint64_t flags, uint64_t n, uint64_t grow, void *buf);
static long FUN_0001d7a0(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
static long FUN_0001d888(uint64_t *out, uint8_t *dst, long n, uint64_t src,
                         uint64_t s1, uint64_t s2, uint64_t s3);
static uint64_t FUN_0001da84(uint64_t p, uint64_t a, uint64_t b);
static long FUN_0001bd08(uint64_t base, uint64_t lim);
static void FUN_0001bea0(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
static void FUN_0001c4cc(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
static void FUN_0001c668(uint64_t a, uint64_t b);
static void FUN_0001c81c(uint64_t idx, uint64_t base, uint64_t lim, uint64_t cnt);
static void FUN_0001c038(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
static void FUN_0001bfa4(uint64_t a, uint64_t b);
static void FUN_0001cfc8(uint64_t a, uint64_t b);
static void FUN_0001d328(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
static void FUN_0001e3e0(uint64_t *buf, uint64_t lim);
static void FUN_0001e12c(uint64_t *buf, uint64_t lim);
static uint64_t FUN_0001e694(uint64_t *buf, uint64_t len);
static uint64_t FUN_0001eec8(uint64_t a, uint64_t b);
static void FUN_0001ef00(uint64_t a);
static uint64_t FUN_0001f834(uint64_t a, uint64_t b, uint64_t c, uint64_t obj);
static uint64_t FUN_0001fde8(uint64_t obj);
static uint64_t FUN_0001fd9c(uint64_t a);
static void FUN_0001fd28(uint64_t a);
static uint64_t FUN_0001f0f0(uint64_t *obj, uint64_t flags);
static void FUN_0001f38c(uint64_t engine, uint64_t a, uint64_t b, uint64_t c);
static void FUN_0001f1d0(uint64_t a, uint8_t b, uint64_t c, uint8_t d, void *self);
static void FUN_0001f670(uint64_t a, uint8_t b, uint64_t c, uint8_t d, uint64_t e, void *self);
static void FUN_0001fa18(uint64_t a, uint8_t b, uint64_t c, uint8_t d, uint64_t e, uint64_t f,
                         void *self);
static uint64_t FUN_0001f978(void);
static uint64_t FUN_0001f97c(void);
static void FUN_0001fee8(uint64_t tag, uint64_t *out_lo, uint64_t *out_hi);
static uint64_t FUN_0001df60(void);
static void FUN_0001d4f4(uint64_t a, uint64_t b, uint64_t c);
static void FUN_0001d540(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                         uint64_t *out_lo, uint64_t *out_hi);
static uint64_t FUN_0001d648(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
static void FUN_0001deb0(uint64_t flags, uint64_t n, uint64_t grow, void **target);
static uint64_t FUN_0001e790(void);
static uint64_t FUN_0001e694(uint64_t *buf, uint64_t len);
static void FUN_0001e3e0(uint64_t *buf, uint64_t lim);
static void FUN_0001e12c(uint64_t *buf, uint64_t lim);
static uint64_t FUN_0001fd9c(uint64_t a);
static uint64_t FUN_0001fde8(uint64_t obj);
static uint64_t FUN_0001a760(void *self);
static void FUN_0001ef60(uint64_t a, uint64_t b, uint64_t *self);
static void FUN_0001ef64(uint64_t a, uint64_t b, uint64_t *self);
static void FUN_000208a8(uint64_t tb, uint64_t one, void *entry, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h);
static void FUN_0001adec(uint64_t *pair, uint64_t a, uint64_t b, uint64_t meta, uint64_t c,
                         void *d, uint64_t flag, uint64_t *out);
static void FUN_0001aeec(uint64_t a, uint64_t b, uint64_t c, uint64_t meta, uint64_t d, void *e,
                         uint64_t flag);

/* ------------------------------------------------------------------ *
 * Low-level tagged-data primitives (Tightbeam record encode/decode).
 * ------------------------------------------------------------------ */

/* FUN_0001a2f4 @ 0x1a2f4   (est. cL4_tagdata_validate_copy)
 * Ghidra: void FUN_0001a2f4(long,long,long,long,long)
 * Validates the source range [src,src_end) and destination capacity, then
 * copies len bytes from dst to src via cL4_memmove_117d14. Traps on negative
 * lengths, an empty/overlapping range, or a destination smaller than size.
 * Confidence: medium
 * Notes: param_1=dst, param_2=len, param_3=src, param_4=src_end, param_5=size. */
static void FUN_0001a2f4(uint64_t dst, uint64_t len, uint64_t src, uint64_t src_end, uint64_t size)
{
    uint64_t span;

    if ((int64_t)size < 0) {
        cL4_breakpoint(0x1a348);
    }
    span = (src != 0) ? (src_end - src) : 0;
    if (span < size) {
        cL4_breakpoint(0x1a34c);
    }
    if (size == 0) {
        if (src == 0) return;
    } else if (src == 0) {
        cL4_breakpoint(0x1a320);
    }
    if (len <= size) {
        if (dst == 0) return;
        if ((int64_t)len < 0) {
            cL4_breakpoint(0x1a354);
        }
        cL4_memmove_117d14((void *)src, (void *)dst, len);
        return;
    }
    cL4_breakpoint(0x1a350);
}

/* FUN_0001a354 @ 0x1a354   (est. cL4_pair_query_len)
 * Ghidra: undefined1[16] FUN_0001a354(undefined8)
 * Queries a byte length via cL4_len_query_115080; returns {ptr,len} on
 * success, else traps.
 * Confidence: low
 * Notes: 16-byte aggregate return {lo=ptr, hi=len}. */
static void FUN_0001a354(uint64_t ptr, uint64_t *out_lo, uint64_t *out_hi)
{
    long len;

    len = cL4_len_query_115080();
    if (len >= 0) {
        *out_lo = ptr;
        *out_hi = (uint64_t)len;
        return;
    }
    cL4_breakpoint(0x1a388);
}

/* FUN_0001a3dc / FUN_0001a3e0 @ 0x1a3dc / 0x1a3e0   (est. cL4_buf_release / cL4_buf_release2)
 * Ghidra: void FUN_0001a3dc(long,long)   (identical pair)
 * Releases a (base,size) range via cL4_mem_release_1e9c78. Null base is
 * normalized to size 0; a negative size traps.
 * Confidence: low */
static void FUN_0001a3dc(uint64_t base, uint64_t size)
{
    if (base == 0) size = 0;
    else if ((int64_t)size < 0) cL4_breakpoint(0x1a3f4);
    cL4_mem_release_1e9c78(base, size);
}
static void FUN_0001a3e0(uint64_t base, uint64_t size)
{
    if (base == 0) size = 0;
    else if ((int64_t)size < 0) cL4_breakpoint(0x1a3f4);
    cL4_mem_release_1e9c78(base, size);
}

/* FUN_0001a404 / FUN_0001a408 @ 0x1a404 / 0x1a408   (est. cL4_buf_release_pair / pair2)
 * Ghidra: void FUN_0001a404(void)   (identical pair)
 * Reads a {base,size} pair from the object in x20 and releases it via
 * cL4_mem_release_1e9c78; a negative size traps.
 * Confidence: low */
static void FUN_0001a404(uint64_t *pair)
{
    if (pair[0] == 0) {
        cL4_mem_release_1e9c78(0, 0);
    } else {
        if ((int64_t)pair[1] < 0) cL4_breakpoint(0x1a424);
        cL4_mem_release_1e9c78(pair[0], pair[1]);
    }
}
static void FUN_0001a408(uint64_t *pair)
{
    if (pair[0] == 0) {
        cL4_mem_release_1e9c78(0, 0);
    } else {
        if ((int64_t)pair[1] < 0) cL4_breakpoint(0x1a424);
        cL4_mem_release_1e9c78(pair[0], pair[1]);
    }
}

/* FUN_0001a448 @ 0x1a448   (est. cL4_pair_retain)
 * Ghidra: undefined1[16] FUN_0001a448(undefined8,undefined8)
 * Retains arg2 and returns {arg1, arg2}.
 * Confidence: low */
static void FUN_0001a448(uint64_t a, uint64_t b, uint64_t *out_lo, uint64_t *out_hi)
{
    cL4_retain_36b270(b);
    *out_lo = a;
    *out_hi = b;
}

/* FUN_0001a47c @ 0x1a47c   (est. cL4_tag_check)
 * Ghidra: ulong FUN_0001a47c(ulong,ulong)
 * Resolves the 48-bit size of the tagged word (masking a 4-bit field when the
 * type bit is set). If nonzero returns tag unchanged; else logs the word and
 * returns 1 (invalid-tag sentinel).
 * Confidence: medium
 * Notes: DAT_00659b58/0x6598d8 are log message anchors. */
static uint64_t FUN_0001a47c(uint64_t tag, uint64_t word)
{
    uint64_t size;

    size = tag & 0xffffffffffff;
    if ((word & 0x2000000000000000) != 0) {
        size = (word >> 0x38) & 0xf;
    }
    if (size != 0) return tag;
    cL4_log_val_3a25d4(word);
    cL4_log_3698b0((void *)1, 0x659b58, 0x6598d8);
    return 1;
}

/* FUN_0001a4f0 @ 0x1a4f0   (est. cL4_typedata_write)
 * Ghidra: long FUN_0001a4f0(undefined8*,long,ulong,ulong)
 * Emits a "TYPEDATA" record into the destination: computes the payload size
 * from (tag,word), validates room, writes the magic + 16-byte size, then
 * copies the payload. Returns total bytes written; on failure logs and returns 0.
 * Confidence: medium */
static long FUN_0001a4f0(uint64_t *dst, uint64_t dst_end, uint64_t tag, uint64_t word)
{
    uint64_t size, total, avail;

    if (((word >> 0x3c) & 1) == 0) {
        size = tag & 0xffffffffffff;
        if ((word & 0x2000000000000000) != 0) size = (word >> 0x38) & 0xf;
    } else {
        size = cL4_size_resolve_2b24b8(tag, word);
    }
    if (size + 0x10 < size) cL4_breakpoint(0x1a614);   /* SCARRY8 */
    total = size + 0x10;
    if (dst != 0) {
        avail = dst_end - (uint64_t)dst;
        if (total <= avail) {
            if ((int64_t)total < 0) cL4_breakpoint(0x1a620);
            if (avail > 0xf) {
                dst[0] = TB_TAG_TYPEDATA;
                dst[1] = total;
                cL4_tagdata_copy_1a1dc((void *)(dst + 2), (void *)(dst + 2 + size), tag, word);
                return (long)total;
            }
            cL4_breakpoint(0x1a61c);
        }
    } else if (total < 1) {
        if ((int64_t)total < 0) cL4_breakpoint(0x1a620);
        cL4_breakpoint(0x1a61c);
    }
    cL4_log_3698b0((void *)0, 0x659b58, 0x6598d8, word);
    return 0;
}

/* FUN_0001a648 @ 0x1a648   (est. cL4_pair_peek)
 * Ghidra: undefined1[16] FUN_0001a648(void)
 * Loads the 16-byte pair at self+0x10, retaining its second word, and returns it.
 * Confidence: low */
static void FUN_0001a648(void *self, uint64_t *out_lo, uint64_t *out_hi)
{
    uint64_t *p = (uint64_t *)self;
    cL4_retain_36b270(p[3]);
    *out_lo = p[2];
    *out_hi = p[3];
}

/* FUN_0001a72c @ 0x1a72c   (est. cL4_header_pack)
 * Ghidra: void FUN_0001a72c(undefined1*,undefined8,undefined2,undefined8,...)
 * Packs a 40-byte record header: the 64-bit word split into byte/short lanes
 * at offsets 0..7, a 16-bit field at offset 8, and 64-bit words at 0x10/0x18/0x20.
 * Confidence: low */
static void FUN_0001a72c(uint8_t *hdr, uint64_t w, uint16_t s, uint64_t a, uint64_t b, uint64_t c)
{
    hdr[0] = (uint8_t)w;
    hdr[1] = (uint8_t)(w >> 8);
    hdr[2] = (uint8_t)(w >> 16);
    *(uint16_t *)(hdr + 4) = (uint16_t)(w >> 32);
    *(uint16_t *)(hdr + 6) = (uint16_t)(w >> 48);
    *(uint16_t *)(hdr + 8) = s;
    *(uint64_t *)(hdr + 0x10) = a;
    *(uint64_t *)(hdr + 0x18) = b;
    *(uint64_t *)(hdr + 0x20) = c;
}

/* FUN_0001a760 @ 0x1a760   (est. cL4_clntdata_size)
 * Ghidra: long FUN_0001a760(void)
 * Computes the total byte size of a "CLNTDATA" record described by self:
 * a 0x25-byte fixed header plus the resolved payload size plus the summed
 * 0x10+size of each sub-record in the entry array at [meta+0x28].
 * Confidence: medium */
static uint64_t FUN_0001a760(void *self)
{
    uint64_t *s = (uint64_t *)self;
    uint64_t size, total, entry, *arr, i;

    size = s[3];                                  /* +0x18 */
    if (size == 0) {
        total = 0x25;
    } else {
        if (((size >> 0x3c) & 1) == 0) {
            total = s[2] & 0xffffffffffff;        /* +0x10 */
            if ((size & 0x2000000000000000) != 0) total = (size >> 0x38) & 0xf;
        } else {
            total = cL4_size_resolve_2b24b8(s[2], size);
        }
        if (total + 0x25 < total) cL4_breakpoint(0x1a838);
        total += 0x25;
    }
    entry = 0;
    arr = (uint64_t *)(*(uint64_t *)(s[4]) + 0x28);   /* s[4]=+0x20 meta */
    i = *(uint64_t *)(*(uint64_t *)(s[4]) + 0x10) + 1;
    for (;;) {
        i--;
        if (i == 0) {
            if (total + entry < total) cL4_breakpoint(0x1a828);
            return total + entry;
        }
        size = arr[1];
        if (((size >> 0x3c) & 1) == 0) {
            total = arr[0] & 0xffffffffffff;
            if ((size & 0x2000000000000000) != 0) total = (size >> 0x38) & 0xf;
        } else {
            total = cL4_size_resolve_2b24b8(arr[0], size);
        }
        if (total + 0x10 < total) break;          /* SCARRY8 */
        arr += 2;
        entry += total + 0x10;
        (void)entry;
    }
    cL4_breakpoint(0x1a808);
}

/* FUN_0001a838 @ 0x1a838   (est. cL4_clntdata_write)
 * Ghidra: ulong FUN_0001a838(undefined8*,long)
 * Serializes a "CLNTDATA" record: computes the record size (cL4_clntdata_size),
 * validates destination room, writes the 0x434c4e5444415441 magic + header
 * fields, then emits each sub-record in the entry array. Returns the header
 * size on success (0 on a too-small destination). Traps on invariant breaches.
 * Confidence: medium */
static long FUN_0001a838(uint64_t *dst, uint64_t dst_end, void *self, uint64_t flag)
{
    uint64_t *s = (uint64_t *)self;
    uint64_t recsize = FUN_0001a760(self);
    uint64_t avail;
    uint64_t size, sz2, total;
    uint8_t *p;
    uint64_t h1, h2, h3;
    uint64_t meta, cnt;
    uint64_t *arr;
    uint64_t u;

    if (dst == 0) {
        if ((int64_t)recsize > 0) goto no_room;
    } else if ((uint64_t)(dst_end - (uint64_t)dst) < recsize) {
        goto no_room;
    }
    size = s[2];                                   /* +0x10 */
    sz2 = s[3];                                    /* +0x18 */
    if (sz2 == 0) {
        total = 0;
    } else if (((sz2 >> 0x3c) & 1) == 0) {
        total = size & 0xffffffffffff;
        if ((sz2 & 0x2000000000000000) != 0) total = (sz2 >> 0x38) & 0xf;
    } else {
        total = cL4_size_resolve_2b24b8(size, sz2);
    }
    p = (uint8_t *)(dst ? dst : (uint64_t *)0);
    if ((int64_t)(total | recsize) < 0) cL4_breakpoint(0x1aac4);
    if (dst == 0 || (uint64_t)(dst_end - (uint64_t)dst) < 0x25) cL4_breakpoint(0x1aac8);
    h1 = *(uint8_t *)((uint8_t *)s + 2);
    h2 = *(uint16_t *)((uint8_t *)s + 4);
    h3 = *(uint16_t *)((uint8_t *)s + 6);
    meta = s[4];                                   /* +0x20 */
    cnt = *(uint64_t *)(meta + 0x10);
    *(uint64_t *)p = TB_TAG_CLNTDATA;
    *(uint64_t *)(p + 8) = recsize;
    *(uint8_t *)(p + 0x10) = h1;
    *(uint16_t *)(p + 0x11) = h2;
    *(uint16_t *)(p + 0x13) = h3;
    *(uint64_t *)(p + 0x15) = total;
    *(uint64_t *)(p + 0x1d) = cnt;
    avail = (dst != 0) ? (dst_end - (uint64_t)dst) : 0;
    if ((int64_t)avail < 0x25) cL4_breakpoint(0x1aacc);
    if (sz2 == 0) {
        total = 0x25;
        goto done;
    }
    {
        uint64_t body = 0;
        if (dst != 0) body = (uint64_t)dst + 0x25;
        if (avail == 0x25) {
            if (body != 0) goto L_has_body;
            u = 0;
        } else {
            if (body == 0) cL4_breakpoint(0x1ab00);
L_has_body:
            u = body + avail - 0x25;
        }
        {
            long r = cL4_tagdata_copy_1a1dc((void *)body, (void *)u, size, sz2);
            if (r < 0) cL4_breakpoint(0x1aaf0);
            FUN_0001db00(0x25, (uint64_t)r, avail, (uint64_t)dst, dst_end, &u, &u);
            /* folded pair {ptr,size} from db00; recompute written size */
        }
    }
done:
    if (cnt != 0) {
        arr = (uint64_t *)(meta + 0x28);
        u = total;
        for (;;) {
            uint64_t out_lo, out_hi, body, n2;
            uint64_t tag = arr[0], word = arr[1];
            body = (dst != 0) ? (u + (uint64_t)dst) : 0;
            if ((int64_t)(avail - u) < 0) cL4_breakpoint(0x1aab8);
            n2 = (avail == u) ? 0 : (body + (avail - u));
            cL4_retain_36b270(word);
            out_lo = (uint64_t)cL4_tagdata_copy_1a1dc((void *)body, (void *)n2, tag, word);
            out_hi = 0;
            cL4_log_val_3a25d4(word);
            if (flag != 0) return out_lo & 0xff;
            FUN_0001db00(u, out_lo, avail, (uint64_t)dst, dst_end, &out_lo, &out_hi);
            if ((int64_t)avail < (int64_t)out_lo) cL4_breakpoint(0x1aabc);
            if ((int64_t)out_lo < (int64_t)u) cL4_breakpoint(0x1aac0);
            arr += 2;
            cnt--;
            u = out_lo;
            if (cnt == 0) break;
        }
    }
    return (long)recsize;

no_room:
    cL4_log_3698b0((void *)0, 0x659b58, 0x6598d8);
    return 0;
}

/* FUN_0001ab00 @ 0x1ab00   (est. cL4_range_validate)
 * Ghidra: void FUN_0001ab00(long,long,long)
 * Validates that [base,lim) covers a record of size (param_1+param_2...)
 * Returns the {ptr,size} pair of the validated region via cL4_range_pair (db00).
 * Traps if the span exceeds the buffer or is negative.
 * Confidence: medium */
static void FUN_0001ab00(long size, uint64_t base, uint64_t lim, uint64_t *out_lo, uint64_t *out_hi)
{
    long span;
    uint64_t lo, hi;

    if (size < 0) cL4_breakpoint(0x1ab7c);
    span = (base != 0) ? (long)(lim - base) : 0;
    FUN_0001db00(0, (uint64_t)size, (uint64_t)span, base, lim, &lo, &hi);
    if ((hi & 0xff) != 1) lo = hi;                 /* pair status bit */
    if ((long)lo <= span) {
        if ((int64_t)lo >= 0) { *out_lo = lo; *out_hi = span; return; }
        cL4_breakpoint(0x1ab84);
    }
    cL4_breakpoint(0x1ab80);
}

/* FUN_0001ab94 @ 0x1ab94   (est. cL4_array_alloc)
 * Ghidra: undefined1[16] FUN_0001ab94(undefined8,undefined8,long)
 * Allocates a growable array of n elements: when n>0, allocates a backing
 * buffer (FUN_0001db94), stores the count at +0x10, and zero-fills the element
 * storage via thunk_FUN_00114330. Returns {arg1, arg2}.
 * Confidence: medium */
static void FUN_0001ab94(uint64_t a, uint64_t b, long n, uint64_t *out_lo, uint64_t *out_hi)
{
    uint64_t *buf;

    if (n < 0) cL4_breakpoint(0x1ac14);
    if (n != 0) {
        buf = (uint64_t *)FUN_0001db94(n);
        buf[2] = (uint64_t)n;                      /* +0x10 */
        cL4_ctx_init_36b7f8((uint64_t)(buf + 4), (uint64_t)n); /* zero-fill +0x20 */
    }
    *out_lo = a;
    *out_hi = b;
}

/* FUN_0001ac14 @ 0x1ac14   (est. cL4_component_record_finalize)
 * Ghidra: void FUN_0001ac14(undefined8,undefined8,long,undefined8,undefined8)
 * Finalizes a ComponentInitData record: reads the type vtable from meta-8,
 * revalidates/compacts the object at self+0x18 via FUN_0001dd00 when the query
 * bit is clear, runs the record callback FUN_0001adec over the {ptr,count}
 * pair, then asserts the pair was consumed unchanged and releases the module.
 * Confidence: low
 * Notes: SUB_f9400262d53bd073 is an opaque Swift-runtime call. */
static void FUN_0001ac14(uint64_t a, uint64_t b, uint64_t meta, uint64_t c, uint64_t d, void *self,
                         uint64_t flag)
{
    uint64_t vtab = *(uint64_t *)(meta - 8);
    uint64_t obj, cnt, pair[2];
    void (*cb)(void *);

    cL4_ctx_setup_36a1a0(*(uint64_t *)(vtab + 0x40), 0, 0, 0);
    obj = *(uint64_t *)((uint8_t *)self + 0x18);
    if ((cL4_query_3a261c(obj) & 1) == 0) {
        obj = (uint64_t)FUN_0001dd14(0, *(uint64_t *)(obj + 0x10), 0, (void *)obj);
        *(uint64_t *)((uint8_t *)self + 0x18) = obj;
    }
    cnt = *(uint64_t *)(obj + 0x10);
    pair[0] = obj + 0x20;
    pair[1] = cnt;
    FUN_0001adec(pair, a, b, meta, c, (void *)d, flag, 0);
    if (flag == 0) {
        if (pair[0] == 0) cL4_breakpoint(0x1adec);
        if (obj + 0x20 != pair[0]) cL4_breakpoint(0x1ade0);
        if (cnt != pair[1]) cL4_breakpoint(0x1ade4);
        FUN_00310d34(0, &UINT_006775b0);
    } else {
        cb = *(void **)(vtab + 0x20);
        cb(0);
        if (pair[0] == 0) cL4_breakpoint(0x1ade8);
        if (obj + 0x20 != pair[0]) cL4_breakpoint(0x1add8);
        if (cnt != pair[1]) cL4_breakpoint(0x1addc);
        FUN_00310d34(0, &UINT_006775b0);
        cb((void *)d);
    }
}

/* FUN_0001adec @ 0x1adec   (est. cL4_component_record_run)
 * Ghidra: void FUN_0001adec(undefined8,undefined8,undefined8,long,undefined8,undefined8)
 * Runs a record operation: captures a value pair from the object, calls
 * FUN_00023f74 with the record callback FUN_0001ef60, and if the x21 flag is
 * set invokes the record's +0x20 vtable slot on the final arg.
 * Confidence: low
 * Notes: SUB_f9400262d53bd073 opaque; FUN_00023f74 dispatches a scoped op. */
static void FUN_0001adec(uint64_t *pair, uint64_t a, uint64_t b, uint64_t meta, uint64_t c,
                         void *d, uint64_t flag, uint64_t *out)
{
    uint64_t vtab = *(uint64_t *)(meta - 8);
    uint64_t p0, p1, cb;

    cL4_ctx_setup_36a1a0(0, 0, 0, 0);
    p0 = pair[0];
    p1 = pair[1];
    cb = (uint64_t)(uintptr_t)FUN_0001ef60;
    FUN_00023f74(0, p0, p1, cb, (void *)0, 0x67b148, meta);
    if (flag != 0) {
        ((void (*)(void *, void *, uint64_t))*(void **)(vtab + 0x20))(d, (void *)0, meta);
    }
}

/* FUN_0001aeec @ 0x1aeec   (est. cL4_record_forward)
 * Ghidra: void FUN_0001aeec(undefined8,undefined8,undefined8,long,undefined8,undefined8)
 * Reads the type vtable from param_4-8, runs an opaque value transform on
 * param_2, and if the x21 flag is set invokes the vtable's +0x20 slot on the
 * final arg.
 * Confidence: low
 * Notes: SUB_f9400262d53bd073 opaque. */
static void FUN_0001aeec(uint64_t a, uint64_t b, uint64_t c, uint64_t meta, uint64_t d, void *e,
                         uint64_t flag)
{
    uint64_t vtab = *(uint64_t *)(meta - 8);

    cL4_ctx_setup_36a1a0(b, 0, 0, 0);
    if (flag != 0) {
        ((void (*)(void *, void *, uint64_t))*(void **)(vtab + 0x20))(e, (void *)0, meta);
    }
}

/* FUN_0001afb4 @ 0x1afb4   (est. cL4_component_size)
 * Ghidra: long FUN_0001afb4(ulong,ulong,undefined8,long)
 * Computes the total byte size of a "COMPDATA" record: 0x30-byte header plus
 * the resolved payload size (param_1/param_2) plus the extra size from
 * FUN_0001dfb4(param_3) plus the +0x10 field of param_4.
 * Confidence: medium */
static long FUN_0001afb4(uint64_t tag, uint64_t word, uint64_t a, uint64_t b)
{
    uint64_t size;
    long base, extra;

    if (((word >> 0x3c) & 1) == 0) {
        size = tag & 0xffffffffffff;
        if ((word & 0x2000000000000000) != 0) size = (word >> 0x38) & 0xf;
    } else {
        size = cL4_size_resolve_2b24b8(tag, word);
    }
    if (size + 0x30 < size) cL4_breakpoint(0x1b024);
    base = (long)(size + 0x30);
    extra = FUN_0001dfb4((void *)a);
    if ((uint64_t)(size + 0x30) + (uint64_t)extra < (uint64_t)(size + 0x30)) cL4_breakpoint(0x1b028);
    base += extra;
    if ((uint64_t)base + *(uint64_t *)(b + 0x10) >= (uint64_t)base) {
        return base + *(uint64_t *)(b + 0x10);
    }
    cL4_breakpoint(0x1b02c);
}

/* FUN_0001b02c @ 0x1b02c   (est. cL4_component_write)
 * Ghidra: ulong FUN_0001b02c(undefined8*,long,ulong,ulong,long,long)
 * Serializes a "COMPDATA" record into the destination: header (0x30 bytes) +
 * payload + per-field sub-records + trailing metadata copy. Returns the header
 * size on success, 0 on a too-small destination. Traps on invariant breaches.
 * Confidence: medium */
static long FUN_0001b02c(uint64_t *dst, uint64_t dst_end, uint64_t tag, uint64_t word,
                         uint64_t a, uint64_t b, uint64_t flag)
{
    uint64_t recsize = (uint64_t)FUN_0001afb4(tag, word, a, b);
    uint64_t avail, size, total, cnt, meta;
    uint8_t *p;
    uint64_t *arr;
    uint64_t u;
    long base;

    if (dst == 0) {
        if ((int64_t)recsize > 0) goto no_room;
    } else if ((uint64_t)(dst_end - (uint64_t)dst) < recsize) {
        goto no_room;
    }
    size = FUN_0001dfb4((void *)a);
    if (((word >> 0x3c) & 1) == 0) {
        total = tag & 0xffffffffffff;
        if ((word & 0x2000000000000000) != 0) total = (word >> 0x38) & 0xf;
    } else {
        total = cL4_size_resolve_2b24b8(tag, word);
    }
    if ((int64_t)(size | recsize | total) < 0) cL4_breakpoint(0x1b338);
    if (dst == 0 || (uint64_t)(dst_end - (uint64_t)dst) < 0x30) cL4_breakpoint(0x1b33c);
    meta = *(uint64_t *)(a + 0x10);
    cnt = *(uint64_t *)(b + 0x10);
    p = (uint8_t *)dst;
    *(uint64_t *)p = TB_TAG_COMPDATA;
    *(uint64_t *)(p + 8) = recsize;
    *(uint64_t *)(p + 0x10) = total;
    *(uint64_t *)(p + 0x18) = size;
    *(uint64_t *)(p + 0x20) = meta;
    *(uint64_t *)(p + 0x28) = cnt;
    avail = (dst != 0) ? (dst_end - (uint64_t)dst) : 0;
    if ((int64_t)avail < 0x30) cL4_breakpoint(0x1b340);
    u = 0;
    {
        uint64_t body = (dst != 0) ? ((uint64_t)dst + 0x30) : 0;
        uint64_t n2;
        if (avail == 0x30) {
            n2 = 0;
        } else {
            if (body == 0) cL4_breakpoint(0x1b35c);
            n2 = body + avail - 0x30;
        }
        base = cL4_tagdata_copy_1a1dc((void *)body, (void *)n2, tag, word);
        if (base < 0) cL4_breakpoint(0x1b344);
        FUN_0001db00(0x30, (uint64_t)base, avail, (uint64_t)dst, dst_end, &u, &u);
        if (avail < u) cL4_breakpoint(0x1b348);
        if ((int64_t)u < 0x30) cL4_breakpoint(0x1b34c);
    }
    if (meta != 0) {
        arr = (uint64_t *)(a + 0x20);
        for (;;) {
            uint64_t out_lo, out_hi, body, n2;
            uint64_t ftag = arr[0], fword = arr[1];
            body = (dst != 0) ? (u + (uint64_t)dst) : 0;
            if ((int64_t)(avail - u) < 0) cL4_breakpoint(0x1b304);
            n2 = (avail == u) ? 0 : (body + (avail - u));
            cL4_retain_36b270(fword);
            out_lo = (uint64_t)FUN_0001a838((uint64_t *)body, n2, (void *)0, 0);
            out_hi = 0;
            cL4_log_val_3a25d4(fword);
            if (flag != 0) return out_lo & 0xff;
            FUN_0001db00(u, out_lo, avail, (uint64_t)dst, dst_end, &out_lo, &out_hi);
            if (avail < out_lo) cL4_breakpoint(0x1b308);
            if ((int64_t)out_lo < (int64_t)u) cL4_breakpoint(0x1b30c);
            arr += 5;
            meta--;
            u = out_lo;
            if (meta == 0) break;
        }
    }
    {
        uint64_t body = (dst != 0) ? (u + (uint64_t)dst) : 0;
        if ((int64_t)(avail - u) < 0) cL4_breakpoint(0x1b350);
        if (avail != u && body == 0) cL4_breakpoint(0x1b360);
        if (cnt <= avail - u) {
            cL4_memmove_117d14((void *)body, (void *)(b + 0x20), cnt);
            return (long)recsize;
        }
        cL4_breakpoint(0x1b354);
    }

no_room:
    cL4_log_3698b0((void *)0, 0x659b58, 0x6598d8);
    return 0;
}

/* FUN_0001b360 @ 0x1b360   (est. cL4_noop)
 * Ghidra: void FUN_0001b360(void)
 * Empty function — a no-op placeholder.
 * Confidence: low */
static void FUN_0001b360(void) { }

/* FUN_0001b370 @ 0x1b370   (est. cL4_component_metadata_size)
 * Ghidra: long FUN_0001b370(long,long)
 * Computes the byte size of a record's metadata region: a 0x20-byte base plus
 * the summed sizes of two metadata tables (param_1 and param_2). Each table's
 * entries are hashed through cL4_hash_pair_24917c and the resulting values
 * accumulated into a growable vector, then summed. Traps on overflow.
 * Confidence: medium
 * Notes: lock targets PTR_LAB_004bb590 / DAT_004bb5b8; empty vector is the
 * DAT_00657778 singleton. */
static long FUN_0001b370(uint64_t a, uint64_t b)
{
    uint64_t handle;
    uint64_t i, sum, val;
    uint64_t vec[64];
    uint64_t nvec;
    uint64_t *p;

    handle = cL4_lock_2d9ac(0x4bb590);
    nvec = 0;
    i = *(uint64_t *)(b + 0x10);
    if (i != 0) {
        p = (uint64_t *)(b + 0x30);
        do {
            uint64_t in[2], out[2];
            in[0] = p[-2];
            in[1] = p[-1];
            cL4_hash_pair_24917c(out, in);
            vec[nvec++] = out[0];
            p += 3;
            i--;
        } while (i != 0);
    }
    cL4_release_36b118(handle);
    sum = 0;
    for (i = 0; i < nvec; i++) {
        if (sum + vec[i] < sum) cL4_breakpoint(0x1b614);
        sum += vec[i];
    }
    cL4_release_36b118(0x657778);
    if (sum + 0x20 < sum) cL4_breakpoint(0x1b61c);

    handle = cL4_lock_2d9ac(0x4bb5b8);
    nvec = 0;
    i = *(uint64_t *)(a + 0x10);
    if (i != 0) {
        p = (uint64_t *)(a + 0x38);
        do {
            uint64_t in[2], out[2];
            in[0] = p[-3];
            in[1] = p[-1];
            cL4_hash_pair_24917c(out, in);
            vec[nvec++] = out[0];
            p += 4;
            i--;
        } while (i != 0);
    }
    cL4_release_36b118(handle);
    val = 0;
    for (i = 0; i < nvec; i++) {
        if (val + vec[i] < val) cL4_breakpoint(0x1b618);
        val += vec[i];
    }
    cL4_release_36b118(0x657778);
    if ((uint64_t)(sum + 0x20) + val < (uint64_t)(sum + 0x20)) cL4_breakpoint(0x1b620);
    return (long)(sum + 0x20 + val);
}
/* FUN_0001b620 @ 0x1b620   (est. cL4_initdata_write)
 * Ghidra: undefined8 FUN_0001b620(undefined8*,long,long,long)
 * Serializes an "INITDATA" record (magic 0x494e495444415441): computes the
 * metadata size (FUN_0001b370), validates destination room, writes the header
 * with the two table counts, then emits the per-field sub-records from both
 * tables. Returns the record's resolved size on success, 0 if too small.
 * Confidence: medium
 * Notes: per-entry record size is 0x19 bytes; comp-data fields 5 words. */
static uint64_t FUN_0001b620(uint64_t *dst, uint64_t dst_end, uint64_t a, uint64_t b)
{
    uint64_t recsize = (uint64_t)FUN_0001b370(a, b);
    uint64_t avail, meta_cnt, comp_cnt, u, v;
    uint8_t *p;
    uint64_t *arr;
    uint64_t i;
    uint64_t body, n2;

    if (dst != 0) {
        avail = dst_end - (uint64_t)dst;
        if (recsize <= avail) {
            if ((int64_t)recsize < 0) cL4_breakpoint(0x1b970);
            if (avail > 0x1f) {
                meta_cnt = *(uint64_t *)(b + 0x10);
                comp_cnt = *(uint64_t *)(a + 0x10);
                dst[0] = TB_TAG_INITDATA;
                dst[1] = recsize;
                dst[2] = meta_cnt;
                dst[3] = comp_cnt;
                if (meta_cnt == 0) {
                    u = 0x20;
                } else {
                    uint64_t off = 0;
                    i = 0;
                    arr = (uint64_t *)(b + 0x30);
                    u = 0;
                    do {
                        body = (uint64_t)dst + off + 0x20;
                        /* per-entry: 0x19-byte record into remaining space */
                        p = (uint8_t *)body;
                        *(uint64_t *)p = TB_TAG_ENDPDATA;
                        *(uint64_t *)(p + 8) = arr[1];       /* tag word */
                        *(uint64_t *)(p + 0x10) = arr[0];
                        *(uint8_t *)(p + 0x18) = *(uint8_t *)((uint8_t *)arr + 0x10);
                        off += 0x19;
                        arr += 3;
                        meta_cnt--;
                    } while (meta_cnt != 0);
                    u = off + 0x20;
                }
                if (comp_cnt == 0) {
                    return u;
                }
                arr = (uint64_t *)(a + 0x38);
                for (;;) {
                    uint64_t ftag, fword, f2, f3, f4, out_lo, out_hi;
                    body = u + (uint64_t)dst;
                    n2 = (avail == u) ? 0 : (body + (avail - u));
                    ftag = arr[0]; fword = arr[1]; f2 = arr[2]; f3 = arr[3]; f4 = arr[4];
                    cL4_retain_36b270(fword);
                    cL4_retain_36b270(f3);
                    cL4_retain_36b270(f4);
                    out_lo = (uint64_t)FUN_0001b02c((uint64_t *)body, n2, ftag, fword, f2, f3, 0);
                    out_hi = 0;
                    cL4_release_36b118(f4);
                    cL4_release_36b118(f3);
                    cL4_log_val_3a25d4(fword);
                    FUN_0001db00(u, out_lo, avail, (uint64_t)dst, dst_end, &out_lo, &out_hi);
                    if (avail < out_lo) cL4_breakpoint(0x1b958);
                    if ((int64_t)out_lo < (int64_t)u) cL4_breakpoint(0x1b95c);
                    arr += 5;
                    comp_cnt--;
                    u = out_lo;
                    if (comp_cnt == 0) break;
                }
                return u;
            }
            cL4_breakpoint(0x1b96c);
        } else if ((int64_t)recsize < 0) {
            cL4_breakpoint(0x1b96c);
        }
    } else if (recsize > 0) {
        cL4_breakpoint(0x1b96c);
    }
    cL4_log_3698b0((void *)0, 0x659b58, 0x6598d8);
    return 0;
}

/* FUN_0001b998 @ 0x1b998   (est. cL4_fatal_comp_init_1ae)
 * Ghidra: void FUN_0001b998(void)
 * Noreturn fatal-error reporter for the ComponentInitData module at line 0x1ae.
 * Confidence: medium */
static void FUN_0001b998(void)
{
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                     0x80000000005ac9f0, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x1ae, 0);
}

/* FUN_0001ba10 @ 0x1ba10   (est. cL4_identity3)
 * Ghidra: undefined8 FUN_0001ba10(undefined8,undefined8,undefined8)
 * Returns the third argument unchanged.
 * Confidence: low */
static uint64_t FUN_0001ba10(uint64_t a, uint64_t b, uint64_t c)
{
    return c;
}

/* FUN_0001ba18 @ 0x1ba18   (est. cL4_comp_initdata_consume)
 * Ghidra: void FUN_0001ba18(long,undefined8,long,long)
 * Iteratively consumes `count` sub-records from the source range, validating
 * each is a well-formed record (FUN_0001e12c) and that the running position
 * advances within bounds. On exhaustion logs the count and traps with a fatal
 * error (module ComponentInitData, line 0x1e8).
 * Confidence: low
 * Notes: 0x1ba7d4 + 0x677880 is a module-scoped log; cL4_log_msg_2acbb8 emits. */
static void FUN_0001ba18(uint64_t dst, uint64_t tag, uint64_t base, uint64_t lim)
{
    uint64_t count = lim;
    uint64_t pos_lo, pos_hi, out_lo, out_hi;

    FUN_0001ab00(0, base, lim, &pos_lo, &pos_hi);
    if ((int64_t)lim > 0) {
        uint64_t i = 0;
        if (base != 0) i = lim - base;
        do {
            uint64_t lvar, avail, lo, hi, size;
            if ((int64_t)pos_lo < 0) cL4_breakpoint(0x1bb60);
            if (base == 0) {
                if ((int64_t)pos_hi > 0) cL4_breakpoint(0x1bb94);
                lvar = 0;
            } else {
                if (lim - base < pos_hi) cL4_breakpoint(0x1bb84);
                lvar = pos_lo + base;
            }
            avail = pos_hi - pos_lo;
            if ((int64_t)avail < 0) cL4_breakpoint(0x1bb64);
            if (avail == 0) {
                if (lvar != 0) goto L_has;
                FUN_0001e12c((uint64_t *)0, 0);
            } else {
                if (lvar == 0) cL4_breakpoint(0x1bb98);
L_has:
                FUN_0001e12c((uint64_t *)lvar, lvar + avail);
            }
            lo = 0; hi = 0;
            if (dst == 0) return;
            /* validate the record header then advance */
            if (lvar == 0 || (avail < 0x10)) {
                cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                                 0x80000000005ac9f0, (void *)cL4_s_Tightbeam_ComponentInitData,
                                 0x21, 2, 0x1ae, 0);
            }
            size = *(uint64_t *)(lvar + 8);
            if ((int64_t)size < 0) cL4_breakpoint(0x1bb68);
            if ((int64_t)i < (int64_t)pos_lo) cL4_breakpoint(0x1bb6c);
            if ((int64_t)pos_hi < 0) cL4_breakpoint(0x1bb70);
            if (i < pos_hi) cL4_breakpoint(0x1bb74);
            if (pos_hi < pos_lo) cL4_breakpoint(0x1bb78);
            out_lo = pos_hi;
            if (size <= avail) {
                out_lo = pos_lo + size;
                if (out_lo < pos_lo) cL4_breakpoint(0x1bb88);
                if ((int64_t)out_lo < 0) cL4_breakpoint(0x1bb8c);
                if (i < out_lo) cL4_breakpoint(0x1bb90);
                if (pos_hi < out_lo) cL4_breakpoint(0x1bb7c);
            }
            if (out_lo < pos_lo) cL4_breakpoint(0x1bb80);
            dst--;
            lim--;
            pos_lo = out_lo;
        } while (lim != 0);
    }
    cL4_log_kind_2a4ab4(0x21);
    cL4_log_val_3a25d4(0xe000000000000000);
    cL4_log_mod_1ba7d4(0x677880, FUN_0001df60());
    cL4_log_msg_2acbb8(0);
    cL4_log_val_3a25d4(0);
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000001f,
                     0x80000000005ac9d0, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x1e8, 0);
}

/* FUN_0001bcac @ 0x1bcac   (est. cL4_fatal_comp_init_206)
 * Ghidra: void FUN_0001bcac(void)
 * Noreturn fatal-error reporter for the ComponentInitData module at line 0x206.
 * Confidence: medium */
static void FUN_0001bcac(void)
{
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                     0x80000000005ac9f0, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x206, 0);
}

/* FUN_0001bd08 @ 0x1bd08   (est. cL4_record_validate)
 * Ghidra: long FUN_0001bd08(long,long)
 * Validates that the range [base,lim) holds a well-formed record header: the
 * length must exceed 0x24 and the record's +0x15 length field must be
 * non-negative; otherwise traps fatally (ComponentInitData line 0x206).
 * Confidence: low */
static long FUN_0001bd08(uint64_t base, uint64_t lim)
{
    if (base != 0 && (lim - base) > 0x24) {
        if (*(int64_t *)(base + 0x15) >= 0) return 0;
        cL4_breakpoint(0x1bd28);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                     0x80000000005ac9f0, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x206, 0);
}

/* FUN_0001bd84 @ 0x1bd84   (est. cL4_record_range)
 * Ghidra: undefined1[16] FUN_0001bd84(undefined8,long,undefined8,long)
 * Validates a record and returns the {base,count} pair of the validated
 * region: when the record is empty returns {0,0}, else validates via
 * FUN_0001bd08 and returns the sub-range. Traps on invariant breaches.
 * Confidence: low */
static void FUN_0001bd84(uint64_t base, uint64_t lim, uint64_t c, uint64_t lim2,
                         uint64_t *out_lo, uint64_t *out_hi)
{
    long n = FUN_0001bd08(base, lim);
    uint64_t lo, hi;

    if (n < 1) {
        *out_lo = 0;
        *out_hi = 0;
        return;
    }
    FUN_0001ab00(0x25, base, lim, &lo, &hi);
    n = FUN_0001bd08(base, lim);
    if (n < 0) cL4_breakpoint(0x1be8c);
    FUN_0001db00(lo, (uint64_t)n, hi, lim, lim2, &lo, &hi);
    n = (long)hi;
    if ((hi & 0xff) != 1) n = (long)lo;
    if ((uint64_t)n < lo) cL4_breakpoint(0x1be90);
    if (hi < (uint64_t)n) cL4_breakpoint(0x1be94);
    if ((int64_t)lo < 0) cL4_breakpoint(0x1be98);
    if (lim == 0) {
        if (n > 0) cL4_breakpoint(0x1bea0);
        lo = 0;
    } else {
        if (lim2 - lim < (uint64_t)n) cL4_breakpoint(0x1be9c);
        lo = lim + lo;
    }
    n -= (long)lo;
    if (n < 0) cL4_breakpoint(0x1be68);
    if (n == 0) {
        if (lo == 0) n = 0;
    } else if (lo == 0) {
        cL4_breakpoint(0x1be40);
    }
    *out_lo = lo;
    *out_hi = (uint64_t)n;
}

/* FUN_0001bea0 @ 0x1bea0   (est. cL4_record_validate2)
 * Ghidra: void FUN_0001bea0(undefined8,long,undefined8,long)
 * Validates a record range and its position advance, trapping on breaches.
 * Confidence: low */
static void FUN_0001bea0(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t lo, hi, o1, o2;

    FUN_0001ab00(0x25, a, b, &lo, &hi);
    if (FUN_0001bd08(a, b) < 0) cL4_breakpoint(0x1bf8c);
    FUN_0001db00(lo, (uint64_t)FUN_0001bd08(a, b), hi, b, d, &o1, &o2);
    if (hi < o2) cL4_breakpoint(0x1bf90);
    if (o2 < lo) cL4_breakpoint(0x1bf94);
    if ((int64_t)o2 < 0) cL4_breakpoint(0x1bf98);
    if (b == 0) {
        if ((int64_t)hi > 0) cL4_breakpoint(0x1bfa0);
    } else {
        if (d - b < hi) cL4_breakpoint(0x1bf9c);
    }
    if (hi - o2 < 0) cL4_breakpoint(0x1bf88);
    if (hi != o2 && o1 == 0) cL4_breakpoint(0x1bfa4);
}

/* FUN_0001bfa4 @ 0x1bfa4   (est. cL4_record_validate3)
 * Ghidra: void FUN_0001bfa4(long,long)
 * Validates a record whose +0x1d length field is checked; on success runs the
 * downstream validator FUN_0001bea0; else traps fatally.
 * Confidence: low */
static void FUN_0001bfa4(uint64_t a, uint64_t b)
{
    if (a != 0 && (b - a) > 0x24) {
        if (*(int64_t *)(a + 0x1d) >= 0) {
            FUN_0001bea0(a, b, 0, 0);
            return;
        }
        cL4_breakpoint(0x1bfec);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                     0x80000000005ac9f0, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x206, 0);
}

/* FUN_0001c038 @ 0x1c038   (est. cL4_comp_field_consume)
 * Ghidra: void FUN_0001c038(long,undefined8,long,long)
 * Consumes `count` component fields from the source range, validating each via
 * FUN_0001e3e0 and advancing the running position. On exhaustion logs and
 * traps fatally (ComponentInitData, line 0x261).
 * Confidence: low */
static void FUN_0001c038(uint64_t dst, uint64_t tag, uint64_t base, uint64_t lim)
{
    uint64_t count = lim;
    uint64_t pos_lo, pos_hi;

    FUN_0001ab00(0, base, lim, &pos_lo, &pos_hi);
    if ((int64_t)lim > 0) {
        uint64_t i = (base != 0) ? (lim - base) : 0;
        do {
            uint64_t lvar, avail;
            if ((int64_t)pos_lo < 0) cL4_breakpoint(0x1c180);
            if (base == 0) {
                if ((int64_t)pos_hi > 0) cL4_breakpoint(0x1c1b4);
                lvar = 0;
            } else {
                if (lim - base < pos_hi) cL4_breakpoint(0x1c1a4);
                lvar = pos_lo + base;
            }
            avail = pos_hi - pos_lo;
            if ((int64_t)avail < 0) cL4_breakpoint(0x1c184);
            if (avail == 0) {
                if (lvar != 0) goto L_h;
                FUN_0001e3e0((uint64_t *)0, 0);
            } else {
                if (lvar == 0) cL4_breakpoint(0x1c1b8);
L_h:
                FUN_0001e3e0((uint64_t *)lvar, lvar + avail);
            }
            if (dst == 0) return;
            if (lvar == 0 || (avail < 0x25)) {
                cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                                 0x80000000005ac9f0, (void *)cL4_s_Tightbeam_ComponentInitData,
                                 0x21, 2, 0x206, 0);
            }
            {
                uint64_t size = *(uint64_t *)(lvar + 8);
                uint64_t o1;
                if ((int64_t)size < 0) cL4_breakpoint(0x1c188);
                if ((int64_t)i < (int64_t)pos_lo) cL4_breakpoint(0x1c18c);
                if ((int64_t)pos_hi < 0) cL4_breakpoint(0x1c190);
                if (i < pos_hi) cL4_breakpoint(0x1c194);
                if (pos_hi < pos_lo) cL4_breakpoint(0x1c198);
                o1 = pos_hi;
                if (size <= avail) {
                    o1 = pos_lo + size;
                    if (o1 < pos_lo) cL4_breakpoint(0x1c1a8);
                    if ((int64_t)o1 < 0) cL4_breakpoint(0x1c1ac);
                    if (i < o1) cL4_breakpoint(0x1c1b0);
                    if (pos_hi < o1) cL4_breakpoint(0x1c19c);
                }
                if (o1 < pos_lo) cL4_breakpoint(0x1c1a0);
                dst--;
                lim--;
                pos_lo = o1;
            }
        } while (lim != 0);
    }
    cL4_log_kind_2a4ab4(0x1e);
    cL4_log_val_3a25d4(0xe000000000000000);
    cL4_log_mod_1ba7d4(0x677880, FUN_0001df60());
    cL4_log_msg_2acbb8(0);
    cL4_log_val_3a25d4(0);
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000001c,
                     0x80000000005aca20, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x261, 0);
}

/* FUN_0001c294 @ 0x1c294   (est. cL4_cmp_char)
 * Ghidra: bool FUN_0001c294(char,char)
 * Returns whether the two characters are equal.
 * Confidence: low */
static bool FUN_0001c294(char a, char b)
{
    return a == b;
}

/* FUN_0001c2a4 @ 0x1c2a4   (est. cL4_fwd_byte)
 * Ghidra: void FUN_0001c2a4(undefined8,undefined1)
 * Forwards the byte argument through the dispatch helper FUN_002298d4.
 * Confidence: low */
static void FUN_0001c2a4(uint64_t a, uint8_t b)
{
    FUN_002298d4(b, 0);
}

/* FUN_0001c2e8 @ 0x1c2e8   (est. cL4_fwd_val)
 * Ghidra: void FUN_0001c2e8(undefined8)
 * Forwards the value in x20 and arg through the dispatch helper FUN_002298d4.
 * Confidence: low */
static void FUN_0001c2e8(uint64_t a, uint64_t *self)
{
    FUN_002298d4(a, *self);
}

/* FUN_0001c330 @ 0x1c330   (est. cL4_record_validate4)
 * Ghidra: void FUN_0001c330(long,long)
 * Validates a record whose +0x10 length field must be non-negative when the
 * range exceeds 0x2f; else traps fatally (ComponentInitData line 0x288).
 * Confidence: low */
static void FUN_0001c330(uint64_t a, uint64_t b)
{
    if (a != 0 && (b - a) > 0x2f) {
        if (*(int64_t *)(a + 0x10) >= 0) return;
        cL4_breakpoint(0x1c350);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002e,
                     0x80000000005aca40, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x288, 0);
}

/* FUN_0001c3c8 @ 0x1c3c8   (est. cL4_record_validate_cb)
 * Ghidra: void FUN_0001c3c8(undefined8,long,undefined8,code*)
 * Validates a record by running the caller-supplied callback (param_4) over
 * the range, then checks the resulting position advance. Traps on breaches.
 * Confidence: low */
static void FUN_0001c3c8(uint64_t a, uint64_t b, uint64_t c, uint64_t (*cb)(uint64_t, uint64_t))
{
    uint64_t lo, hi, o1, o2;
    long r;

    FUN_0001ab00(c, a, b, &lo, &hi);
    r = cb(a, b);
    if (r < 0) cL4_breakpoint(0x1c4b4);
    FUN_0001db00(lo, (uint64_t)r, hi, b, (uint64_t)cb, &o1, &o2);
    if (o2 < lo) cL4_breakpoint(0x1c4b8);
    if (hi < o2) cL4_breakpoint(0x1c4bc);
    if ((int64_t)lo < 0) cL4_breakpoint(0x1c4c0);
    if (b == 0) {
        if ((int64_t)o2 > 0) cL4_breakpoint(0x1c4c8);
    } else {
        if ((uint64_t)cb - b < o2) cL4_breakpoint(0x1c4c4);
    }
    if ((int64_t)(o2 - lo) < 0) cL4_breakpoint(0x1c4b0);
    if (o2 != lo && o1 == 0) cL4_breakpoint(0x1c4cc);
}

/* FUN_0001c4cc @ 0x1c4cc   (est. cL4_comp_validate2)
 * Ghidra: void FUN_0001c4cc(long,long,undefined8,long)
 * Validates a "COMPDATA"-style record (min 0x30 bytes) with two sub-ranges
 * (fields at +0x10 and +0x18), ensuring each advances within the buffer.
 * Traps on invariant breaches.
 * Confidence: low */
static void FUN_0001c4cc(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t lo, hi, o1, o2, o3;

    FUN_0001ab00(0x30, a, b, &lo, &hi);
    if (a == 0 || (b - a) < 0x30) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002e,
                         0x80000000005aca40, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x288, 0);
    }
    if (*(int64_t *)(a + 0x10) < 0) cL4_breakpoint(0x1c5f8);
    FUN_0001db00(lo, *(uint64_t *)(a + 0x10), hi, b, d, &o1, &o2);
    if (hi < o2) cL4_breakpoint(0x1c5fc);
    if (o2 < lo) cL4_breakpoint(0x1c600);
    if (*(int64_t *)(a + 0x18) < 0) cL4_breakpoint(0x1c604);
    FUN_0001db00(o2, *(uint64_t *)(a + 0x18), hi, b, d, &o1, &o3);
    if (o3 < o2) cL4_breakpoint(0x1c608);
    if (hi < o3) cL4_breakpoint(0x1c60c);
    if ((int64_t)o2 < 0) cL4_breakpoint(0x1c610);
    if (b == 0) {
        if ((int64_t)o3 > 0) cL4_breakpoint(0x1c618);
    } else {
        if (d - b < o3) cL4_breakpoint(0x1c614);
    }
    if (o3 - o2 < 0) cL4_breakpoint(0x1c5f4);
    if (o3 != o2 && o1 == 0) cL4_breakpoint(0x1c61c);
}

/* FUN_0001c668 @ 0x1c668   (est. cL4_record_validate5)
 * Ghidra: void FUN_0001c668(long,long)
 * Validates a record whose +0x20 field is checked; on success runs the
 * downstream validator FUN_0001c4cc; else traps fatally.
 * Confidence: low */
static void FUN_0001c668(uint64_t a, uint64_t b)
{
    if (a != 0 && (b - a) > 0x2f) {
        if (*(int64_t *)(a + 0x20) >= 0) {
            FUN_0001c4cc(a, b, 0, 0);
            return;
        }
        cL4_breakpoint(0x1c6b0);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002e,
                     0x80000000005aca40, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x288, 0);
}

/* FUN_0001c6fc @ 0x1c6fc   (est. cL4_comp_range)
 * Ghidra: undefined1[16] FUN_0001c6fc(long,long,undefined8,long)
 * Validates a "COMPDATA" record and returns the {base,count} pair of the
 * covered region, including the record's +0x18 sub-range. Traps on breaches.
 * Confidence: low */
static void FUN_0001c6fc(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                         uint64_t *out_lo, uint64_t *out_hi)
{
    uint64_t base_size, lo, hi, sub;

    FUN_0001c330(a, b);
    base_size = *(uint64_t *)(a + 0x10);
    if (base_size + 0x30 < base_size) cL4_breakpoint(0x1c7b8);
    if (a == 0 || (b - a) < 0x30) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002e,
                         0x80000000005aca40, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x288, 0);
    }
    sub = *(uint64_t *)(a + 0x18);
    if ((int64_t)sub < 0) cL4_breakpoint(0x1c7bc);
    if (base_size + 0x30 + sub < base_size + 0x30) cL4_breakpoint(0x1c7c0);
    FUN_0001ab00(base_size + 0x30 + sub, a, b, &lo, &hi);
    if ((int64_t)lo < 0) cL4_breakpoint(0x1c7c4);
    if (b == 0) {
        if ((int64_t)hi > 0) cL4_breakpoint(0x1c7cc);
        b = 0;
    } else {
        if (d - b < hi) cL4_breakpoint(0x1c7c8);
        b = b + lo;
    }
    hi -= lo;
    if ((int64_t)hi < 0) cL4_breakpoint(0x1c7b4);
    if (hi == 0) {
        if (b == 0) { hi = 0; goto done; }
    } else if (b == 0) {
        cL4_breakpoint(0x1c7d0);
    }
    hi = b + hi;
done:
    *out_lo = b;
    *out_hi = hi;
}

/* FUN_0001c81c @ 0x1c81c   (est. cL4_comp_array_consume)
 * Ghidra: void FUN_0001c81c(long,undefined8,long,long)
 * Consumes `count` "COMPDATA" records from the source range, validating each
 * magic/size via FUN_0001db00 and enforcing the advancing position. Logs and
 * traps fatally (ComponentInitData) on malformed or mis-sized records.
 * Confidence: low
 * Notes: 0x65a100/0x659908 log anchors; FUN_00205844 + 0x6756a8/0x66e1b8 report. */
static void FUN_0001c81c(uint64_t idx, uint64_t base, uint64_t lim, uint64_t cnt)
{
    uint64_t count = cnt;
    uint64_t pos_lo, pos_hi;

    FUN_0001ab00(0, base, lim, &pos_lo, &pos_hi);
    if ((int64_t)cnt > 0) {
        uint64_t rem = base;
        do {
            uint64_t avail;
            if ((int64_t)pos_lo < 0) cL4_breakpoint(0x1c9cc);
            if (base == 0) {
                if ((int64_t)pos_hi > 0) cL4_breakpoint(0x1c9e4);
                rem = 0;
            } else {
                if (lim - base < pos_hi) cL4_breakpoint(0x1c9e0);
                rem = pos_lo + base;
            }
            avail = pos_hi - pos_lo;
            if ((int64_t)avail < 0) cL4_breakpoint(0x1c9d0);
            if (pos_hi == pos_lo) {
                cL4_log_3698b0((void *)0, 0x65a100, 0x659908);
                cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000013,
                                 0x80000000005aca90, (void *)cL4_s_Tightbeam_ComponentInitData,
                                 0x21, 2, 0x2e5, 0);
            }
            if (rem == 0) cL4_breakpoint(0x1c9e8);
            if (avail < 0x30) {
                cL4_log_3698b0((void *)0, 0x65a100, 0x659908);
                cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000013,
                                 0x80000000005aca90, (void *)cL4_s_Tightbeam_ComponentInitData,
                                 0x21, 2, 0x2e5, 0);
            }
            if (*(uint64_t *)rem != TB_TAG_COMPDATA) {
                cL4_log_3698b0((void *)1, 0x65a100, 0x659908);
                cL4_log_kind_2a4ab4(0x15);
                cL4_log_msg_2acbb8(0xd000000000000013, 0x80000000005aca90);
                cL4_log_err_205844((void *)0, 0xe000000000000000, 0x65a100,
                                   0x6756a8, 0x66e1b8);
                cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000013,
                                 0x80000000005aca90, (void *)cL4_s_Tightbeam_ComponentInitData,
                                 0x21, 2, 0x2e5, 0);
            }
            {
                uint64_t rec = *(uint64_t *)(rem + 8);
                uint64_t o1, o2;
                if ((int64_t)rec < 0) cL4_breakpoint(0x1c9d4);
                if (avail < rec) {
                    cL4_log_3698b0((void *)2, 0x65a100, 0x659908);
                    cL4_log_kind_2a4ab4(0x15);
                    cL4_log_msg_2acbb8(0xd000000000000013, 0x80000000005aca90);
                    cL4_log_err_205844((void *)0, 0xe000000000000000, 0x65a100,
                                       0x6756a8, 0x66e1b8);
                    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2,
                                     0xd000000000000013, 0x80000000005aca90,
                                     (void *)cL4_s_Tightbeam_ComponentInitData,
                                     0x21, 2, 0x2e5, 0);
                }
                if (idx == 0) return;
                if (rec < 0x30) {
                    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2,
                                     0xd00000000000002e, 0x80000000005aca40,
                                     (void *)cL4_s_Tightbeam_ComponentInitData,
                                     0x21, 2, 0x288, 0);
                }
                FUN_0001db00(pos_lo, rec, pos_hi, base, lim, &o1, &o2);
                if (pos_hi < o2) cL4_breakpoint(0x1c9d8);
                if (o2 < pos_lo) cL4_breakpoint(0x1c9dc);
                idx--;
                cnt--;
                pos_lo = o2;
            }
        } while (cnt != 0);
    }
    cL4_log_kind_2a4ab4(0x13);
    cL4_log_mod_1ba7d4(0x677880, FUN_0001df60());
    cL4_log_msg_2acbb8(0xd000000000000011, 0x80000000005aca70);
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xe000000000000000,
                     0x80000000005aca70, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x2e8, 0);
}

/* FUN_0001cba4 @ 0x1cba4   (est. cL4_ctx_forward8)
 * Ghidra: void FUN_0001cba4(undefined1)
 * Sets up a context frame, forwards the byte through FUN_002298d4, tears down.
 * Confidence: low */
static void FUN_0001cba4(uint8_t a)
{
    void *frame = 0;
    FUN_001a84f4(frame, 0);
    FUN_002298d4(a, 0);
    FUN_001a8564();
}

/* FUN_0001cbec / FUN_0001cc34 @ 0x1cbec / 0x1cc34   (est. cL4_ctx_forward8_v)
 * Ghidra: void FUN_0001cbec(void)   (identical pair)
 * Reads the byte at x20, sets up a context frame, forwards it, tears down.
 * Confidence: low */
static void FUN_0001cbec(uint8_t *self)
{
    void *frame = 0;
    FUN_001a84f4(frame, 0);
    FUN_002298d4(*self, 0);
    FUN_001a8564();
}
static void FUN_0001cc34(uint8_t *self)
{
    void *frame = 0;
    FUN_001a84f4(frame, 0);
    FUN_002298d4(*self, 0);
    FUN_001a8564();
}

/* FUN_0001ccec / FUN_0001ccf0 @ 0x1ccec / 0x1ccf0   (est. cL4_validate_flag / flag2)
 * Ghidra: undefined1[16] FUN_0001ccec(void)   (identical pair)
 * Runs the record validator FUN_0001e694 and returns {err, 1}: when the x21
 * flag is clear the result is propagated as-is.
 * Confidence: low */
static void FUN_0001ccec(uint64_t *out_lo, uint64_t *out_hi, uint64_t flag)
{
    uint64_t v = FUN_0001e694((uint64_t *)0, 0);
    uint64_t lo = v & 0xff;
    uint64_t hi = 1;
    if (flag == 0) {
        lo = v;
        hi = v;
    }
    *out_lo = lo;
    *out_hi = hi;
}
static void FUN_0001ccf0(uint64_t *out_lo, uint64_t *out_hi, uint64_t flag)
{
    uint64_t v = FUN_0001e694((uint64_t *)0, 0);
    uint64_t lo = v & 0xff;
    uint64_t hi = 1;
    if (flag == 0) {
        lo = v;
        hi = v;
    }
    *out_lo = lo;
    *out_hi = hi;
}

/* FUN_0001cd1c @ 0x1cd1c   (est. cL4_init_validate)
 * Ghidra: void FUN_0001cd1c(long,long,undefined8,long)
 * Validates an "INITDATA" record (min 0x20 bytes): the +0x10 count field is
 * multiplied by 0x19 (per-entry stride), the resulting byte range is checked
 * against the buffer, and position advance is validated. Traps on breaches.
 * Confidence: low */
static void FUN_0001cd1c(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t lo, hi, o1, o2, cnt, bytes;

    FUN_0001ab00(0x20, a, b, &lo, &hi);
    if (a == 0 || (b - a) < 0x20) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002e,
                         0x80000000005aca40, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x318, 0);
    }
    cnt = *(uint64_t *)(a + 0x10);
    if ((int64_t)cnt < 0) cL4_breakpoint(0x1ce44);
    bytes = cnt * 0x19;
    if ((int64_t)bytes < 0) cL4_breakpoint(0x1ce4c);
    FUN_0001db00(lo, bytes, hi, b, d, &o1, &o2);
    if (o2 < lo) cL4_breakpoint(0x1ce50);
    if (hi < o2) cL4_breakpoint(0x1ce54);
    if ((int64_t)lo < 0) cL4_breakpoint(0x1ce58);
    if (b == 0) {
        if ((int64_t)o2 > 0) cL4_breakpoint(0x1ce60);
    } else {
        if (d - b < o2) cL4_breakpoint(0x1ce5c);
    }
    if (o2 - lo < 0) cL4_breakpoint(0x1ce40);
    if (o2 != lo && o1 == 0) cL4_breakpoint(0x1ce64);
}

/* FUN_0001ced0 @ 0x1ced0   (est. cL4_fatal_init_318)
 * Ghidra: void FUN_0001ced0(void)
 * Noreturn fatal-error reporter for the ComponentInitData module at line 0x318.
 * Confidence: medium */
static void FUN_0001ced0(void)
{
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002e,
                     0x80000000005aca40, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x318, 0);
}

/* FUN_0001cf2c @ 0x1cf2c   (est. cL4_comp_count_size)
 * Ghidra: long FUN_0001cf2c(undefined8,undefined8,long)
 * Sums the byte sizes of `count` consecutive records, validating each via
 * FUN_0001c81c/FUN_0001c668. Returns the total size. Traps on overflow.
 * Confidence: low */
static long FUN_0001cf2c(uint64_t a, uint64_t b, uint64_t count)
{
    uint64_t total = 0;
    uint64_t i = 0;
    uint64_t rem = count;

    FUN_0001cfc8(a, b);
    if (count == 0) return 0;
    do {
        uint64_t lo, hi;
        FUN_0001cfc8(a, b);
        /* 16-byte {lo,hi} folded; hi holds size */
        FUN_0001c81c(i, a, b, rem);
        FUN_0001c668(a, b);
        if (total + hi < total) cL4_breakpoint(0x1cfc8);
        total += hi;
        i++;
        rem = hi;
    } while (count != i);
    return (long)total;
}

/* FUN_0001cfc8 @ 0x1cfc8   (est. cL4_init_validate2)
 * Ghidra: void FUN_0001cfc8(long,long)
 * Validates a record whose +0x18 field is checked; on success runs the
 * downstream validator FUN_0001d328; else traps fatally.
 * Confidence: low */
static void FUN_0001cfc8(uint64_t a, uint64_t b)
{
    if (a != 0 && (b - a) > 0x1f) {
        if (*(int64_t *)(a + 0x18) >= 0) {
            FUN_0001d328(a, b, 0, 0);
            return;
        }
        cL4_breakpoint(0x1d010);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002e,
                     0x80000000005aca40, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x318, 0);
}

/* FUN_0001d05c @ 0x1d05c   (est. cL4_comp_field_count_size)
 * Ghidra: long FUN_0001d05c(undefined8,undefined8,ulong)
 * Sums the byte sizes of a nested array of records: for each of `count`
 * top-level records validates and walks its component fields via
 * FUN_0001c038/FUN_0001bfa4. Returns the total size. Traps on overflow/illegal.
 * Confidence: low */
static long FUN_0001d05c(uint64_t a, uint64_t b, uint64_t count)
{
    uint64_t total = 0;
    uint64_t i = 0;
    uint64_t rem = count;

    FUN_0001cfc8(a, b);
    if (count == 0) return 0;
    do {
        uint64_t lo, hi, sub, s1, s2;
        if (i == (count & (uint64_t)((int64_t)count >> 0x3f ^ -1ull))) cL4_breakpoint(0x1d194);
        FUN_0001cfc8(a, b);
        /* folded {lo,hi} */
        FUN_0001c81c(i, a, b, rem);
        FUN_0001c668(a, b);
        rem = hi;
        if (rem != 0) {
            uint64_t j = 0;
            total = 0;
            do {
                FUN_0001cfc8(a, b);
                FUN_0001c81c(i, a, b, rem);
                FUN_0001cfc8(a, b);
                sub = 0;
                FUN_0001c038(j, a, b, rem);
                FUN_0001bfa4(a, b);
                if (total + sub < total) cL4_breakpoint(0x1d190);
                total += sub;
                j++;
            } while (rem != j);
        }
        i++;
    } while (i != count);
    return (long)total;
}

/* FUN_0001d194 @ 0x1d194   (est. cL4_init_element_get)
 * Ghidra: undefined1[16] FUN_0001d194(long,undefined8,undefined8)
 * Returns the {tag,word} pair of the index-th element of an "INITDATA"
 * record's entry table (each entry 0x19 bytes, tag field at +0, word at +8).
 * Traps if the index is out of range or the entry magic is not ENDPDATA.
 * Confidence: low */
static void FUN_0001d194(uint64_t idx, uint64_t a, uint64_t b, uint64_t *out_lo, uint64_t *out_hi)
{
    uint64_t lo, hi, base;

    FUN_0001cd1c(a, b, 0, 0);
    /* folded {lo,hi} — hi = count, lo = base */
    if ((int64_t)idx < 0 || hi <= idx) cL4_breakpoint(0x1d27c);
    base = lo;
    if (*(uint64_t *)(base + idx * 0x19) != TB_TAG_ENDPDATA) {
        cL4_log_kind_2a4ab4(0x21);
        cL4_log_val_3a25d4(0xe000000000000000);
        cL4_log_mod_1ba7d4(0x677790, FUN_0001e790());
        cL4_log_msg_2acbb8(0);
        cL4_log_val_3a25d4(0);
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000001f,
                         0x80000000005acad0, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x340, 0);
    }
    FUN_0001cd1c(a, b, 0, 0);
    if (idx < hi) {
        *out_lo = *(uint64_t *)(base + idx * 0x19 + 8);
        *out_hi = *(uint64_t *)(base + idx * 0x19 + 0x10);
        return;
    }
    cL4_breakpoint(0x1d280);
}

/* FUN_0001d328 @ 0x1d328   (est. cL4_init_validate3)
 * Ghidra: void FUN_0001d328(long,long,undefined8,long)
 * Validates an "INITDATA" record (min 0x20 bytes): the +0x10 count field times
 * the 0x19-byte stride must fit in the buffer, and position advance checked.
 * Traps on breaches.
 * Confidence: low */
static void FUN_0001d328(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t lo, hi, o1, o2, cnt, bytes;

    FUN_0001ab00(0x20, a, b, &lo, &hi);
    if (a == 0 || (b - a) < 0x20) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002e,
                         0x80000000005aca40, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x318, 0);
    }
    cnt = *(uint64_t *)(a + 0x10);
    if ((int64_t)cnt < 0) cL4_breakpoint(0x1d434);
    bytes = cnt * 0x19;
    if ((int64_t)bytes < 0) cL4_breakpoint(0x1d43c);
    FUN_0001db00(lo, bytes, hi, b, d, &o1, &o2);
    if (hi < o2) cL4_breakpoint(0x1d440);
    if (o2 < lo) cL4_breakpoint(0x1d444);
    if ((int64_t)o2 < 0) cL4_breakpoint(0x1d448);
    if (b == 0) {
        if ((int64_t)hi > 0) cL4_breakpoint(0x1d450);
    } else {
        if (d - b < hi) cL4_breakpoint(0x1d44c);
    }
    if (hi - o2 < 0) cL4_breakpoint(0x1d430);
    if (hi != o2 && o1 == 0) cL4_breakpoint(0x1d454);
}

/* FUN_0001d4a0 @ 0x1d4a0   (est. cL4_mem_op_and_copy)
 * Ghidra: undefined1[16] FUN_0001d4a0(undefined8,undefined8,undefined8,undefined8)
 * Runs a memory/page-table op (FUN_0001d4f4) then a byte copy (FUN_0001d540),
 * logging arg4. Returns the copy's {ptr,size} pair.
 * Confidence: low */
static void FUN_0001d4a0(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                        uint64_t *out_lo, uint64_t *out_hi)
{
    FUN_0001d4f4(0xf, a, b);
    cL4_log_val_3a25d4(d);
    FUN_0001d540(c, a, b, d, out_lo, out_hi);
}

/* FUN_0001d4f4 @ 0x1d4f4   (est. cL4_mem_op_page)
 * Ghidra: void FUN_0001d4f4(ulong,ulong,ulong)
 * Performs a page-granule memory op: validates the requested size against the
 * resolved 48-bit page size, chooses a 7- or 0xb-byte attribute lane based on
 * the permission bit, and calls FUN_0029fa0c. Traps if the size exceeds the
 * resolved page capacity (param_1>>0xe <= size<<2).
 * Confidence: low */
static void FUN_0001d4f4(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t size;
    uint64_t attr;
    uint64_t perm;

    size = b & 0xffffffffffff;
    if ((c & 0x2000000000000000) != 0) size = (c >> 0x38) & 0xf;
    if ((a >> 0xe) <= (size << 2)) {
        perm = (b >> 0x3b) & 1;
        if ((c & 0x1000000000000000) == 0) perm = 1;
        attr = 7;
        if (perm == 0) attr = 0xb;
        FUN_0029fa0c(a, attr | (size << 0x10), b);
        return;
    }
    cL4_breakpoint(0x1d540);
}

/* FUN_0001d540 @ 0x1d540   (est. cL4_copy_region)
 * Ghidra: undefined8 FUN_0001d540(ulong,ulong,ulong,ulong)
 * Copies a validated byte region: resolves the region {ptr,size} from the
 * (tag,word) pair, computes the byte range, and copies it via FUN_00294cb4.
 * Handles the direct, indirect (page-tree), and embedded forms.
 * Confidence: low */
static void FUN_0001d540(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                         uint64_t *out_lo, uint64_t *out_hi)
{
    uint64_t lo, hi, base, size;

    if (((d >> 0x3c) & 1) == 0) {
        a >>= 0x10;
        b >>= 0x10;
        if (((d >> 0x3d) & 1) == 0) {
            if (((c >> 0x3c) & 1) == 0) {
                /* resolve pair {ptr,size} */
                lo = cL4_pair_resolve_2a9ba8(c, d) & 0xffffffffffff;
                if ((c & 0xffffffffffff) < b) cL4_breakpoint(0x1d638);
            } else {
                lo = (d & 0xfffffffffffffff) + 0x20;
                if ((c & 0xffffffffffff) < b) cL4_breakpoint(0x1d638);
            }
            base = (lo != 0) ? (lo + a) : 0;
            size = b - a;
            if ((int64_t)size < 0) cL4_breakpoint(0x1d640);
            if (size != 0 && base == 0) cL4_breakpoint(0x1d648);
            *out_lo = cL4_copy_294cb4((void *)base, size);
            *out_hi = 0;
            return;
        }
        /* embedded form: local pair {c, d&mask} */
        base = (c) + a;
        size = b - a;
        if ((d >> 0x38 & 0xf) < b) cL4_breakpoint(0x1d63c);
        if ((int64_t)size < 0) cL4_breakpoint(0x1d644);
        *out_lo = cL4_copy_294cb4((void *)base, size);
        *out_hi = 0;
        return;
    }
    /* page-tree form */
    lo = FUN_0001d648(0, 0, 0, 0);
    *out_lo = cL4_copy_294cb4((void *)(lo + 0x20), *(uint64_t *)(lo + 0x10));
    cL4_release_36b118(lo);
    *out_hi = 0;
}

/* FUN_0001d648 @ 0x1d648   (est. cL4_pagetree_read)
 * Ghidra: undefined* FUN_0001d648(undefined8,undefined8,undefined8,undefined8)
 * Reads a page-tree representation: computes its byte length (FUN_0001d7a0),
 * allocates a buffer (FUN_0001dc8c), fills it via FUN_0001d888, and returns
 * the buffer. Traps on invariant breaches in the fill.
 * Confidence: low */
static uint64_t FUN_0001d648(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    long len = FUN_0001d7a0(a, b, c, d);
    uint64_t *buf;
    uint64_t out[5];
    long r;

    if (len == 0) return 0x657778;              /* DAT_00657778 empty */
    buf = (uint64_t *)FUN_0001dc8c(len, 0);
    if (len < 0) cL4_breakpoint(0x1d710);
    r = FUN_0001d888(out, (uint8_t *)((uint8_t *)buf + 0x20), len, a, b, c, d);
    if (r != len) cL4_breakpoint(0x1d6e8);
    return (uint64_t)buf;
}

/* FUN_0001d7a0 @ 0x1d7a0   (est. cL4_pagetree_len)
 * Ghidra: long FUN_0001d7a0(ulong,ulong,ulong,ulong)
 * Computes the byte length of a page-tree value: normalizes any 4-byte/
 * pointer-lane fields (FUN_0001da84), then either computes the difference of
 * two page offsets or, for the memory-backed form, queries the tree length
 * (FUN_002b15d0). Traps if a page offset exceeds the resolved size.
 * Confidence: low */
static long FUN_0001d7a0(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t lane, size;

    lane = (c >> 0x3b) & 1;
    if ((d & 0x1000000000000000) == 0) lane = 1;
    if ((a & 0xc) == (4ull << lane)) a = FUN_0001da84(a, c, d);
    if ((b & 0xc) == (4ull << lane)) b = FUN_0001da84(b, c, d);
    if (((d >> 0x3c) & 1) != 0) {
        size = c & 0xffffffffffff;
        if ((d & 0x2000000000000000) != 0) size = (d >> 0x38) & 0xf;
        if ((a >> 0x10) <= size) {
            if ((b >> 0x10) <= size) {
                return cL4_pagetree_len_2b15d0(a, b, c);
            }
            cL4_breakpoint(0x1d888);
        }
        cL4_breakpoint(0x1d884);
    }
    return (long)((b >> 0x10) - (a >> 0x10));
}

/* FUN_0001d888 @ 0x1d888   (est. cL4_pagetree_fill)
 * Ghidra: long FUN_0001d888(undefined8*,undefined1*,long,undefined*,ulong,...)
 * Fills a destination buffer with the bytes of a page-tree value, reading each
 * page granule and copying its bytes. Writes the five-word descriptor to *out.
 * Returns the number of bytes filled (0 if dst is null). Traps on breach.
 * Confidence: low */
static long FUN_0001d888(uint64_t *out, uint8_t *dst, long n, uint64_t src,
                         uint64_t s1, uint64_t s2, uint64_t s3)
{
    uint64_t page = src;
    uint64_t lane, lane_size, page_off;
    long filled;

    if (dst == 0) {
        *out = src; out[1] = s1; out[2] = s2; out[3] = s3; out[4] = page;
        return 0;
    }
    if (n < 0) cL4_breakpoint(0x1da84);
    filled = n;
    if (n == 0) goto store;
    if ((src >> 0xe) == (s1 >> 0xe)) {
        /* single page */
        lane = (s2 >> 0x3b) & 1;
        if ((s3 & 0x1000000000000000) == 0) lane = 1;
        lane_size = 4ull << lane;
        page_off = s2 & 0xffffffffffff;
        if ((s3 & 0x2000000000000000) != 0) page_off = (s3 >> 0x38) & 0xf;
        for (; n != 0; n--) {
            uint64_t p = page;
            uint64_t val;
            if ((page & 0xc) == lane_size) p = FUN_0001da84(page, s2, s3);
            if ((p >> 0xe) < (src >> 0xe) || (s1 >> 0xe) <= (p >> 0xe)) cL4_breakpoint(0x1da7c);
            val = *(uint8_t *)(((s3 & 0xfffffffffffffff) + 0x20) + (p >> 0x10));
            *dst = (uint8_t)val;
            page = FUN_0001da84(page, s2, s3);
            dst++;
        }
        filled = 0;
        goto store;
    }
    /* multi-page walk */
    lane = (s2 >> 0x3b) & 1;
    if ((s3 & 0x1000000000000000) == 0) lane = 1;
    lane_size = 4ull << lane;
    {
        long left = n;
        uint64_t p = page;
        while (left != 0) {
            uint64_t q = p;
            uint8_t val;
            if ((p & 0xc) == lane_size) q = FUN_0001da84(p, s2, s3);
            if ((q >> 0xe) < (src >> 0xe) || (s1 >> 0xe) <= (q >> 0xe)) cL4_breakpoint(0x1da7c);
            val = *(uint8_t *)(((s3 & 0xfffffffffffffff) + 0x20) + (q >> 0x10));
            *dst = val;
            if (lane_size <= (p >> 0x10)) cL4_breakpoint(0x1da80);
            p = FUN_0001da84(p, s2, s3);
            dst++;
            left--;
            if (left == 0 || (s1 >> 0xe) == (p >> 0xe)) break;
        }
        filled = n - left;
    }
store:
    *out = src; out[1] = s1; out[2] = s2; out[3] = s3; out[4] = page;
    return filled;
}

/* FUN_0001da84 @ 0x1da84   (est. cL4_page_normalize)
 * Ghidra: ulong FUN_0001da84(ulong,ulong,ulong)
 * Normalizes a page-tree pointer into a concrete address: resolves the page
 * base (4-byte or pointer-lane form), combines it with the pointer's 2-bit
 * sub-offset, and returns a pointer with the lane tag set (4 or 8).
 * Confidence: low */
static uint64_t FUN_0001da84(uint64_t p, uint64_t a, uint64_t b)
{
    uint64_t lane, base, out;

    lane = (p >> 0xe) & 3;
    if (((b >> 0x3c) & 1) == 0 || ((a >> 0x3b) & 1) != 0) {
        base = cL4_pagetree_op_2a4614(0xf, p >> 0x10);
        out = (base + (lane << 0x10)) & 0xffffffffffff0000;
        if (lane == 0) out = (base & 0xfffffffffffffffc) | (p & 3);
        out |= 4;
    } else {
        base = cL4_pagetree_op_1b1ff0(0xf);
        out = (base + (lane << 0x10)) & 0xffffffffffff0000;
        if (lane == 0) out = (base & 0xfffffffffffffffc) | (p & 3);
        out |= 8;
    }
    return out;
}

/* FUN_0001db00 @ 0x1db00   (est. cL4_range_pair)
 * Ghidra: undefined1[16] FUN_0001db00(long,ulong,ulong,long,long)
 * Computes the {base,count} pair of a validated sub-range: given the current
 * position (param_1), the record's declared length (param_2), the buffer
 * end (param_3), and the buffer base/limit (param_4/param_5), returns the
 * new position; or {0, 1<<40} if the record lies outside the buffer.
 * Traps on invariant breaches.
 * Confidence: medium */
static void FUN_0001db00(uint64_t pos, uint64_t val, uint64_t end, uint64_t base, uint64_t lim,
                         uint64_t *out_lo, uint64_t *out_hi)
{
    uint64_t avail = (base != 0) ? (lim - base) : 0;

    if ((int64_t)pos < 0) cL4_breakpoint(0x1db7c);
    if ((int64_t)avail < (int64_t)pos) cL4_breakpoint(0x1db80);
    if ((int64_t)end < 0) cL4_breakpoint(0x1db84);
    if (avail < end) cL4_breakpoint(0x1db88);
    end -= pos;
    if ((int64_t)val < 1) {
        if ((int64_t)end < 1 && (int64_t)val < (int64_t)end) goto out_of_range;
    } else if ((int64_t)end >= 0 && end < val) {
        goto out_of_range;
    }
    if (pos + val < pos) cL4_breakpoint(0x1db8c);      /* SCARRY8 */
    if ((int64_t)(pos + val) < 0) cL4_breakpoint(0x1db90);
    if (avail < pos + val) cL4_breakpoint(0x1db94);
    *out_lo = pos + val;
    *out_hi = 0;
    return;
out_of_range:
    *out_lo = 0;
    *out_hi = 1ull << 40;   /* ZEXT816(1) << 0x40 marker */
}

/* FUN_0001db94 @ 0x1db94   (est. cL4_buffer_alloc)
 * Ghidra: undefined* FUN_0001db94(long)
 * Allocates a growable byte buffer of capacity n (plus 0x20-byte header) from
 * the type descriptor at s___cstring_0064c108, returning the buffer with the
 * header fields set. Returns the DAT_00657778 empty singleton when n<=0.
 * Confidence: low */
static void *FUN_0001db94(long n)
{
    void *type = 0;                 /* s___cstring_0064c108 */
    void *meta = (void *)0x4be910;
    void *obj;
    uint64_t *buf;
    long h;

    if (n > 0) {
        obj = cL4_type_alloc_2534(type, meta);
        buf = (uint64_t *)FUN_0036a940();       /* FUN_0036a940(obj, n+0x20, 7) */
        h = cL4_alloc_query_126e8();
        buf[2] = 0;                              /* +0x10 */
        buf[3] = (uint64_t)(h * 2 - 0x40);       /* +0x18 */
        return buf;
    }
    return (void *)0x657778;                     /* DAT_00657778 */
}

/* FUN_0001dc08 @ 0x1dc08   (est. cL4_array_buffer_alloc)
 * Ghidra: undefined* FUN_0001dc08(long,long)
 * Allocates a growable array buffer of capacity max(n,m) elements (8 bytes
 * each) plus header, from the descriptor at s___cstring_0064c108+8. Stores the
 * initial count (n) at +0x10. Returns the empty singleton when capacity is 0.
 * Confidence: low */
static void *FUN_0001dc08(long n, long m)
{
    void *type = 0;                 /* s___cstring_0064c108 + 8 */
    void *meta = (void *)0x4c0740;
    uint64_t *buf;
    long h, cap;

    if (m <= n) m = n;
    if (m == 0) return (void *)0x657778;         /* DAT_00657778 */
    buf = (uint64_t *)FUN_0036a940();            /* FUN_0036a940(type, m*8+0x20, 7) */
    h = cL4_alloc_query_126e8();
    cap = (h - 0x19 > 0x1f) ? (h - 0x20) : (h - 0x19);
    buf[2] = (uint64_t)n;                        /* +0x10 */
    buf[3] = (uint64_t)((cap >> 3) << 1);        /* +0x18 */
    return buf;
}

/* FUN_0001dc8c @ 0x1dc8c   (est. cL4_buffer_alloc_n)
 * Ghidra: undefined* FUN_0001dc8c(long,long)
 * Allocates a growable byte buffer of capacity max(n,m) plus header, from the
 * descriptor at s___cstring_0064c108. Stores the initial count (n) at +0x10.
 * Returns the empty singleton when capacity is 0.
 * Confidence: low */
static void *FUN_0001dc8c(long n, long m)
{
    void *type = 0;                 /* s___cstring_0064c108 */
    void *meta = (void *)0x4be910;
    uint64_t *buf;
    long h;

    if (m <= n) m = n;
    if (m == 0) return (void *)0x657778;         /* DAT_00657778 */
    buf = (uint64_t *)FUN_0036a940();            /* FUN_0036a940(type, m+0x20, 7) */
    h = cL4_alloc_query_126e8();
    buf[2] = (uint64_t)n;                        /* +0x10 */
    buf[3] = (uint64_t)(h * 2 - 0x40);           /* +0x18 */
    return buf;
}

/* FUN_0001dd00 @ 0x1dd00   (est. cL4_array_grow0)
 * Ghidra: void FUN_0001dd00(long)
 * Grows the array buffer at obj to hold obj[2] elements via FUN_0001dde4.
 * Confidence: low */
static void FUN_0001dd00(uint64_t obj)
{
    FUN_0001dde4(0, *(uint64_t *)(obj + 0x10), 0, (void *)obj);
}

/* FUN_0001dd14 @ 0x1dd14   (est. cL4_array_grow1)
 * Ghidra: long FUN_0001dd14(ulong,ulong,ulong,long)
 * Grows an array buffer to hold at least n elements (8 bytes each): allocates
 * a new buffer (FUN_0001dc08), copies the old elements (memcpy/memmove), and
 * releases the old buffer. Returns the new buffer. Handles the grow-by-half
 * policy when the grow flag is set.
 * Confidence: medium */
static void *FUN_0001dd14(uint64_t flags, uint64_t n, uint64_t grow, void *buf)
{
    uint64_t *b = (uint64_t *)buf;
    uint64_t cap = n;
    uint64_t cnt = b[2];                          /* +0x10 */
    void *newbuf;
    uint64_t *nb;
    uint64_t body_old, body_new;

    if ((grow & 1) != 0) {
        cap = b[3] >> 1;                          /* +0x18 >> 1 */
        if ((int64_t)cap < (int64_t)n) {
            if ((int64_t)(cap + 0x4000000000000000) < 0) cL4_breakpoint(0x1dde0);
            cap = b[3] & 0xfffffffffffffffe;
            if ((int64_t)cap <= (int64_t)n) cap = n;
        }
    }
    newbuf = FUN_0001dc08((long)cnt, (long)cap);
    nb = (uint64_t *)newbuf;
    body_old = (uint64_t)b + 0x20;
    body_new = (uint64_t)nb + 0x20;
    if ((flags & 1) == 0) {
        if (body_old < body_new + cnt * 8 && body_new < body_old + cnt * 8) cL4_breakpoint(0x1dde4);
        cL4_memcpy_117cc4((void *)body_new, (void *)body_old, cnt * 8);
    } else {
        if (newbuf != buf || body_old + cnt * 8 <= body_new) {
            cL4_memmove_117d14((void *)body_new, (void *)body_old, cnt * 8);
        }
        nb[2] = 0;                                /* +0x10 */
    }
    cL4_release_36b118((uint64_t)buf);
    return newbuf;
}

/* FUN_0001dde4 @ 0x1dde4   (est. cL4_bytearray_grow)
 * Ghidra: long FUN_0001dde4(ulong,ulong,ulong,long)
 * Grows a byte array buffer to hold at least n bytes (1 byte each): allocates
 * a new buffer (FUN_0001dc8c), copies the old bytes, and releases the old.
 * Returns the new buffer. Handles the grow-by-half policy.
 * Confidence: medium */
static void *FUN_0001dde4(uint64_t flags, uint64_t n, uint64_t grow, void *buf)
{
    uint64_t *b = (uint64_t *)buf;
    uint64_t cap = n;
    uint64_t cnt = b[2];                          /* +0x10 */
    void *newbuf;
    uint64_t *nb;
    uint64_t body_old, body_new;

    if ((grow & 1) != 0) {
        cap = b[3] >> 1;
        if ((int64_t)cap < (int64_t)n) {
            if ((int64_t)(cap + 0x4000000000000000) < 0) cL4_breakpoint(0x1deac);
            cap = b[3] & 0xfffffffffffffffe;
            if ((int64_t)cap <= (int64_t)n) cap = n;
        }
    }
    newbuf = FUN_0001dc8c((long)cnt, (long)cap);
    nb = (uint64_t *)newbuf;
    body_old = (uint64_t)b + 0x20;
    body_new = (uint64_t)nb + 0x20;
    if ((flags & 1) == 0) {
        if (body_old < body_new + cnt && body_new < body_old + cnt) cL4_breakpoint(0x1deb0);
        cL4_memcpy_117cc4((void *)body_new, (void *)body_old, cnt);
    } else {
        if (newbuf != buf || body_old + cnt <= body_new) {
            cL4_memmove_117d14((void *)body_new, (void *)body_old, cnt);
        }
        nb[2] = 0;
    }
    cL4_release_36b118((uint64_t)buf);
    return newbuf;
}

/* FUN_0001deb0 @ 0x1deb0   (est. cL4_array_grow_store)
 * Ghidra: void FUN_0001deb0(void)
 * Stores the result of FUN_0001dd14 into the 8-byte slot at x20.
 * Confidence: low */
static void FUN_0001deb0(uint64_t flags, uint64_t n, uint64_t grow, void **target)
{
    *target = FUN_0001dd14(flags, n, grow, *target);
}

/* FUN_0001df2c @ 0x1df2c   (est. cL4_comp_size_store)
 * Ghidra: void FUN_0001df2c(undefined8*,undefined8*)
 * Computes the "COMPDATA" size from the {tag,word,a,b} words at param_2 and
 * stores it into *param_1.
 * Confidence: low */
static void FUN_0001df2c(uint64_t *out, uint64_t *in)
{
    *out = (uint64_t)FUN_0001afb4(in[0], in[1], in[2], in[3]);
}

/* FUN_0001df60 @ 0x1df60   (est. cL4_mod_component_init_data)
 * Ghidra: void FUN_0001df60(void)
 * Lazily initializes the ComponentInitData module singleton (DAT_0064c0f8)
 * from the type at DAT_004edbe8 with id 0x677880.
 * Confidence: low */
static uint64_t FUN_0001df60(void)
{
    if (cL4_mod_677880 != 0) return cL4_mod_677880;
    cL4_mod_677880 = FUN_00376820(0x4edbe8, 0x677880);
    return cL4_mod_677880;
}

/* FUN_0001dfb4 @ 0x1dfb4   (est. cL4_comp_fields_size)
 * Ghidra: long FUN_0001dfb4(long)
 * Computes the total byte size of a record's field table: builds a vector of
 * hashed field values (cL4_hash_pair_24917c over the 5-word entries at +0x20),
 * then sums the vector. Returns the total.
 * Confidence: low */
static long FUN_0001dfb4(void *a)
{
    uint64_t *obj = (uint64_t *)a;
    uint64_t i, total, vec[64], nvec;
    uint64_t *p;
    uint64_t handle;

    handle = cL4_lock_2d9ac(0x4bb860);
    nvec = 0;
    i = obj[2];                                   /* +0x10 */
    if (i != 0) {
        p = (uint64_t *)((uint8_t *)obj + 0x20);
        do {
            uint64_t in[2], out[2];
            in[0] = p[0]; in[1] = p[1];
            FUN_0001eec8((uint64_t)p, (uint64_t)in);
            cL4_hash_pair_24917c(out, in);
            FUN_0001ef00((uint64_t)p);
            vec[nvec++] = out[0];
            p += 5;
            i--;
        } while (i != 0);
    }
    cL4_release_36b118(handle);
    total = 0;
    for (i = 0; i < nvec; i++) {
        if (total + vec[i] < total) cL4_breakpoint(0x1e12c);
        total += vec[i];
    }
    cL4_release_36b118(0x657778);
    return (long)total;
}

/* FUN_0001e12c @ 0x1e12c   (est. cL4_typedata_validate)
 * Ghidra: void FUN_0001e12c(long*,long)
 * Validates a "TYPEDATA" record: the buffer must be non-null with >= 0x10
 * bytes, the magic must match, and the declared size must fit. On any failure
 * logs and traps fatally (ComponentInitData).
 * Confidence: medium */
static void FUN_0001e12c(uint64_t *buf, uint64_t lim)
{
    uint64_t size;

    if (buf == 0 || (lim - (uint64_t)buf) < 0x10) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000037,
                         0x80000000005acba0, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x19b, 0);
    }
    if (buf[0] != TB_TAG_TYPEDATA) {
        cL4_log_kind_2a4ab4(0x29);
        cL4_log_val_3a25d4(0xe000000000000000);
        cL4_log_mod_1ba7d4(0x677790, FUN_0001e790());
        cL4_log_msg_2acbb8(0);
        cL4_log_val_3a25d4(0);
        cL4_log_msg_2acbb8(0x746365707865202c, 0xec000000203a6465);
        cL4_log_mod_1ba7d4(0x677790, FUN_0001e790());
        cL4_log_msg_2acbb8(0);
        cL4_log_val_3a25d4(0);
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000019,
                         0x80000000005acbe0, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x19f, 0);
    }
    size = buf[1];
    if ((int64_t)size < 0) cL4_breakpoint(0x1e1a4);
    if (size <= (lim - (uint64_t)buf)) return;
    cL4_log_kind_2a4ab4(0x3f);
    cL4_log_msg_2acbb8(0xd000000000000023, 0x80000000005acb50);
    cL4_log_mod_1ba7d4(0x677790, FUN_0001e790());
    cL4_log_msg_2acbb8(0);
    cL4_log_val_3a25d4(0);
    cL4_log_msg_2acbb8(0x202c736574796220, 0xe800000000000000);
    cL4_log_mod_1ba7d4(0x677880, FUN_0001df60());
    cL4_log_msg_2acbb8(0);
    cL4_log_val_3a25d4(0);
    cL4_log_msg_2acbb8(0xd000000000000010, 0x80000000005acb80);
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xe000000000000000,
                     0x80000000005acb80, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x1a2, 0);
}

/* FUN_0001e3e0 @ 0x1e3e0   (est. cL4_clntdata_validate)
 * Ghidra: void FUN_0001e3e0(long*,long)
 * Validates a "CLNTDATA" record: the buffer must be non-null with >= 0x25
 * bytes, the magic must match, and the declared size must fit. On failure logs
 * and traps fatally (ComponentInitData).
 * Confidence: medium */
static void FUN_0001e3e0(uint64_t *buf, uint64_t lim)
{
    uint64_t size;

    if (buf == 0 || (lim - (uint64_t)buf) < 0x25) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000033,
                         0x80000000005acaf0, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x1f2, 0);
    }
    if (buf[0] != TB_TAG_CLNTDATA) {
        cL4_log_kind_2a4ab4(0x2b);
        cL4_log_val_3a25d4(0xe000000000000000);
        cL4_log_mod_1ba7d4(0x677790, FUN_0001e790());
        cL4_log_msg_2acbb8(0);
        cL4_log_val_3a25d4(0);
        cL4_log_msg_2acbb8(0x746365707865202c, 0xec000000203a6465);
        cL4_log_mod_1ba7d4(0x677790, FUN_0001e790());
        cL4_log_msg_2acbb8(0);
        cL4_log_val_3a25d4(0);
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000001b,
                         0x80000000005acb30, (void *)cL4_s_Tightbeam_ComponentInitData,
                         0x21, 2, 0x1f6, 0);
    }
    size = buf[1];
    if ((int64_t)size < 0) cL4_breakpoint(0x1e458);
    if (size <= (lim - (uint64_t)buf)) return;
    cL4_log_kind_2a4ab4(0x3f);
    cL4_log_msg_2acbb8(0xd000000000000023, 0x80000000005acb50);
    cL4_log_mod_1ba7d4(0x677790, FUN_0001e790());
    cL4_log_msg_2acbb8(0);
    cL4_log_val_3a25d4(0);
    cL4_log_msg_2acbb8(0x202c736574796220, 0xe800000000000000);
    cL4_log_mod_1ba7d4(0x677880, FUN_0001df60());
    cL4_log_msg_2acbb8(0);
    cL4_log_val_3a25d4(0);
    cL4_log_msg_2acbb8(0xd000000000000010, 0x80000000005acb80);
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xe000000000000000,
                     0x80000000005acb80, (void *)cL4_s_Tightbeam_ComponentInitData,
                     0x21, 2, 0x1fa, 0);
}

/* FUN_0001e694 @ 0x1e694   (est. cL4_record_validate6)
 * Ghidra: long* FUN_0001e694(long*,ulong)
 * Validates a record header: the length must be >= 0x20, the buffer non-null,
 * and the magic must be INITDATA. Returns the validated buffer pointer, or a
 * tagged error pointer (buf+1 / buf+2) on mismatch. Traps if length is negative.
 * Confidence: low */
static uint64_t FUN_0001e694(uint64_t *buf, uint64_t len)
{
    uint64_t *p = buf;

    if ((int64_t)len < 0) cL4_breakpoint(0x1e78c);
    if (len < 0x20) {
        cL4_log_3698b0((void *)0, 0x65a210, 0x659938);
        return 0;
    }
    if (p == 0) cL4_breakpoint(0x1e790);
    if (p[0] != TB_TAG_INITDATA) {
        cL4_log_3698b0((void *)1, 0x65a210, 0x659938);
        return (uint64_t)((uint8_t *)p + 1);
    }
    if (len != p[1]) {
        cL4_log_3698b0((void *)2, 0x65a210, 0x659938);
        return (uint64_t)((uint8_t *)p + 2);
    }
    return (uint64_t)p;
}

/* FUN_0001e790 @ 0x1e790   (est. cL4_mod_transport_buffer)
 * Ghidra: void FUN_0001e790(void)
 * Lazily initializes the TransportBuffer module singleton (DAT_0064c100) from
 * the type at DAT_004ed758 with id 0x677790.
 * Confidence: low */
static uint64_t FUN_0001e790(void)
{
    if (cL4_mod_677790 != 0) return cL4_mod_677790;
    cL4_mod_677790 = FUN_00376820(0x4ed758, 0x677790);
    return cL4_mod_677790;
}

/* FUN_0001eec8 @ 0x1eec8   (est. cL4_wrap_label)
 * Ghidra: undefined8 FUN_0001eec8(undefined8,undefined8)
 * Wraps arg1 with the label at LAB_00659c50 via cL4_wrap_35dc24, returning arg2.
 * Confidence: low */
static uint64_t FUN_0001eec8(uint64_t a, uint64_t b)
{
    cL4_wrap_35dc24((void *)b, (void *)a, (void *)0x659c50);
    return b;
}

/* FUN_0001ef00 @ 0x1ef00   (est. cL4_unwrap_label)
 * Ghidra: undefined8 FUN_0001ef00(undefined8)
 * Unwraps arg1's label via cL4_unwrap_35d334, returning arg1.
 * Confidence: low */
static void FUN_0001ef00(uint64_t a)
{
    cL4_unwrap_35d334((void *)a, (void *)0x659c50);
}

/* FUN_0001ef34 @ 0x1ef34   (est. cL4_clntdata_size_store)
 * Ghidra: void FUN_0001ef34(undefined8*)
 * Stores the result of FUN_0001a760 into *param_1.
 * Confidence: low */
static void FUN_0001ef34(uint64_t *out)
{
    *out = FUN_0001a760(0);
}

/* FUN_0001ef60 / FUN_0001ef64 @ 0x1ef60 / 0x1ef64   (est. cL4_record_cb / cb2)
 * Ghidra: void FUN_0001ef60(undefined8,undefined8)   (identical pair)
 * Record callback: forwards the given args and the object's +0x10..+0x28
 * fields through FUN_0001aeec.
 * Confidence: low */
static void FUN_0001ef60(uint64_t a, uint64_t b, uint64_t *self)
{
    FUN_0001aeec(a, self[4], self[5], self[2], self[3], (void *)b, 0);
}
static void FUN_0001ef64(uint64_t a, uint64_t b, uint64_t *self)
{
    FUN_0001aeec(a, self[4], self[5], self[2], self[3], (void *)b, 0);
}

/* FUN_0001efd4 @ 0x1efd4   (est. cL4_ctx_frame_teardown)
 * Ghidra: void FUN_0001efd4(void)
 * Tears down the context frame at self+0x18.
 * Confidence: low */
static void FUN_0001efd4(void *self)
{
    void *frame = 0;
    cL4_ctx_setup_36a1a0((uint64_t)((uint8_t *)self + 0x18), frame, 0, 0);
    cL4_ctx_void_36b8c0((uint64_t)((uint8_t *)self + 0x18));
}

/* FUN_0001f010 @ 0x1f010   (est. cL4_ctx_attach)
 * Ghidra: void FUN_0001f010(undefined8,undefined8)
 * Attaches a context frame at self+0x18: stores param_2 at +0x20, sets the
 * frame's +0x18 to param_1 (retaining it).
 * Confidence: low */
static void FUN_0001f010(uint64_t a, uint64_t b, void *self)
{
    uint64_t *s = (uint64_t *)self;
    void *frame = 0;
    cL4_ctx_setup_36a1a0((uint64_t)((uint8_t *)self + 0x18), frame, 1, 0);
    s[4] = b;                                    /* +0x20 */
    cL4_ctx_set_36b834((uint64_t)((uint8_t *)self + 0x18), a);
    cL4_release_36b118(a);
}

/* FUN_0001f070 @ 0x1f070   (est. cL4_closure_alloc)
 * Ghidra: undefined1[16] FUN_0001f070(long*)
 * Allocates a closure object (0x30 bytes, tag 0x1f57) backed by self's context,
 * returns {entry, &closure+0x18}. The closure holds the context getter/setter.
 * Confidence: low */
static void FUN_0001f070(uint64_t *out, void *self)
{
    uint64_t *s = (uint64_t *)self;
    uint64_t obj = (uint64_t)cL4_alloc_36a908(0x30, 0x1f57);
    uint64_t ctxv;

    *out = obj;
    *(uint64_t *)(obj + 0x28) = (uint64_t)self;
    cL4_ctx_setup_36a1a0((uint64_t)((uint8_t *)self + 0x18), (void *)obj, 0x21, 0);
    ctxv = cL4_ctx_get_36b8b0((uint64_t)((uint8_t *)self + 0x18));
    *(uint64_t *)(obj + 0x18) = ctxv;
    *(uint64_t *)(obj + 0x20) = s[4];
    out[1] = obj + 0x18;
    out[0] = (uint64_t)(uintptr_t)FUN_0001f0f0;
}

/* FUN_0001f0f0 @ 0x1f0f0   (est. cL4_closure_release)
 * Ghidra: void FUN_0001f0f0(long*,ulong)
 * Releases a closure: detaches its context, releases retained objects
 * according to the flags, and finalizes the object.
 * Confidence: low */
static uint64_t FUN_0001f0f0(uint64_t *obj, uint64_t flags)
{
    uint64_t v = obj[0];
    uint64_t ctx = *(uint64_t *)(v + 0x18);
    uint64_t owner = *(uint64_t *)(v + 0x28);
    void *frame = 0;

    *(uint64_t *)(owner + 0x20) = *(uint64_t *)(v + 0x20);
    cL4_ctx_set_36b834(owner + 0x18, ctx);
    if ((flags & 1) == 0) {
        cL4_ctx_setup_36a1a0(v, frame, 0, 0);
        cL4_release_36b118(ctx);
    } else {
        cL4_release_36b118(*(uint64_t *)(v + 0x18));
        cL4_ctx_setup_36a1a0(v, frame, 0, 0);
    }
    cL4_finalize_12568((void *)v);
    return 0;
}

/* FUN_0001f168 @ 0x1f168   (est. cL4_task_alloc_run)
 * Ghidra: undefined8 FUN_0001f168(undefined8,undefined8,undefined8,undefined8)
 * Allocates an object then runs the task initializer FUN_0001f1d0 with the
 * given args; returns the allocated object.
 * Confidence: low */
static uint64_t FUN_0001f168(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    uint64_t obj = (uint64_t)cL4_alloc_36a940();
    FUN_0001f1d0(a, (uint8_t)b, c, (uint8_t)d, (void *)obj);
    return obj;
}

/* FUN_0001f1d0 @ 0x1f1d0   (est. cL4_task_init)
 * Ghidra: void FUN_0001f1d0(undefined8,byte,undefined8,byte)
 * Initializes an async task object: zeroes the +0x10/+0x20 slots, inits the
 * context at +0x18, converts the two (kind,flag) pairs into error values via
 * FUN_00015388/FUN_0001532c, sets up a task engine (FUN_0004b520), runs the
 * task (FUN_00017b88), and stores the result at +0x10.
 * Confidence: low */
static void FUN_0001f1d0(uint64_t a, uint8_t b, uint64_t c, uint8_t d, void *self)
{
    uint64_t *s = (uint64_t *)self;
    uint64_t e1, e2, engine, res;

    s[2] = 0;                                    /* +0x10 */
    s[4] = 0;                                    /* +0x20 */
    cL4_ctx_init_36b7f8((uint64_t)((uint8_t *)self + 0x18), 0);
    if (b < 2) {
        e1 = (b == 0) ? 3 : 0xd;
        e2 = 0;
    } else if (b == 2) {
        e2 = 1;
        e1 = 3;
    } else if (b == 3) {
        e2 = 8;
        e1 = 3;
    } else {
        e1 = FUN_0001532c(1, 0);
    }
    if (d < 2) {
        uint64_t e3 = (d == 0) ? 3 : 0xd;
        e2 = FUN_00015388(e3, c, 0);
    } else if (d == 2) {
        e2 = FUN_00015388(3, c, 1);
    } else if (d == 3) {
        e2 = FUN_00015388(3, c, 8);
    } else {
        e2 = FUN_0001532c(1, 0);
    }
    engine = FUN_0004b520(0);
    cL4_retain_36b270(0);
    cL4_release_36b118((uint64_t)self);
    res = FUN_00017b88(e1, e2, engine);
    FUN_0004b664(engine);
    s[2] = res;
}

/* FUN_0001f38c @ 0x1f38c   (est. cL4_task_cb)
 * Ghidra: uint FUN_0001f38c(long,undefined8,undefined8,undefined8)
 * Task callback: calls the +0x20 vtable slot, retaining the +0x28 object
 * around the call, and returns the low bit of the result.
 * Confidence: low */
static void FUN_0001f38c(uint64_t engine, uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t obj = *(uint64_t *)(engine + 0x28);
    uint64_t (*cb)(uint64_t, uint64_t, uint64_t) = (uint64_t (*)(uint64_t,uint64_t,uint64_t))*(uint64_t **)(engine + 0x20);
    uint64_t r;

    cL4_retain_36b270(obj);
    r = cb(a, b, c);
    cL4_release_36b118(obj);
    /* return r & 1 folded into caller */
}

/* FUN_0001f414 @ 0x1f414   (est. cL4_task_alloc2)
 * Ghidra: long FUN_0001f414(undefined8,undefined8)
 * Allocates a task object, initializes its context and engine, runs the task
 * via FUN_00017b7c, stores the result at +0x10, and returns the object.
 * Confidence: low */
static uint64_t FUN_0001f414(uint64_t a, uint64_t b)
{
    uint64_t obj = (uint64_t)cL4_alloc_36a940();
    uint64_t *s = (uint64_t *)obj;
    uint64_t engine, res;

    s[2] = 0;
    s[4] = 0;
    cL4_ctx_init_36b7f8((uint64_t)((uint8_t *)obj + 0x18), 0);
    engine = FUN_0004b520(0);
    cL4_retain_36b270(obj);
    cL4_release_36b118(obj);
    res = FUN_00017b7c(a, b, engine);
    FUN_0004b664(engine);
    s[2] = res;
    return obj;
}

/* FUN_0001f514 @ 0x1f514   (est. cL4_task_init2)
 * Ghidra: void FUN_0001f514(undefined8,undefined8)
 * Initializes an async task object with the task callback FUN_0001f38c and
 * runs it via FUN_00017b7c, storing the result at +0x10.
 * Confidence: low */
static void FUN_0001f514(uint64_t a, uint64_t b, void *self)
{
    uint64_t *s = (uint64_t *)self;
    uint64_t engine, res;

    s[2] = 0;
    s[4] = 0;
    cL4_ctx_init_36b7f8((uint64_t)((uint8_t *)self + 0x18), 0);
    engine = FUN_0004b520(0);
    cL4_retain_36b270(0);
    cL4_release_36b118((uint64_t)self);
    res = FUN_00017b7c(a, b, engine);
    FUN_0004b664(engine);
    s[2] = res;
}

/* FUN_0001f600 @ 0x1f600   (est. cL4_task_alloc_run3)
 * Ghidra: undefined8 FUN_0001f600(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Allocates an object and runs the task initializer FUN_0001f670 with the
 * given args; returns the allocated object.
 * Confidence: low */
static uint64_t FUN_0001f600(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
    uint64_t obj = (uint64_t)cL4_alloc_36a940();
    FUN_0001f670(a, (uint8_t)b, c, (uint8_t)d, e, (void *)obj);
    return obj;
}

/* FUN_0001f670 @ 0x1f670   (est. cL4_task_init3)
 * Ghidra: void FUN_0001f670(undefined8,byte,undefined8,byte,undefined8)
 * Initializes an async task object with a 3-argument task (FUN_00017a08) and
 * the callback FUN_0001f38c, storing the result at +0x10.
 * Confidence: low */
static void FUN_0001f670(uint64_t a, uint8_t b, uint64_t c, uint8_t d, uint64_t e, void *self)
{
    uint64_t *s = (uint64_t *)self;
    uint64_t e1, e2, engine, res;

    s[2] = 0;
    s[4] = 0;
    cL4_ctx_init_36b7f8((uint64_t)((uint8_t *)self + 0x18), 0);
    if (b < 2) {
        e1 = (b == 0) ? 3 : 0xd;
        e2 = 0;
    } else if (b == 2) {
        e2 = 1;
        e1 = 3;
    } else if (b == 3) {
        e2 = 8;
        e1 = 3;
    } else {
        e1 = FUN_0001532c(1, 0);
    }
    if (d < 2) {
        uint64_t e3 = (d == 0) ? 3 : 0xd;
        e2 = FUN_00015388(e3, c, 0);
    } else if (d == 2) {
        e2 = FUN_00015388(3, c, 1);
    } else if (d == 3) {
        e2 = FUN_00015388(3, c, 8);
    } else {
        e2 = FUN_0001532c(1, 0);
    }
    engine = FUN_0004b520(0);
    cL4_retain_36b270(0);
    cL4_release_36b118((uint64_t)self);
    res = FUN_00017a08(e1, e2, e, engine);
    FUN_0004b664(engine);
    s[2] = res;
}

/* FUN_0001f834 @ 0x1f834   (est. cL4_forwarding_send)
 * Ghidra: uint FUN_0001f834(undefined8,undefined8,undefined8,ulong)
 * Sends a message over a ForwardingConnection: enters the context at obj+0x18,
 * resolves the send entry (FUN_0001fde8), builds the message descriptor
 * (hash + flags + transport-buffer state), and calls the entry. Returns the
 * low bit of the result. Traps fatally if the context is null.
 * Confidence: low */
static uint64_t FUN_0001f834(uint64_t a, uint64_t b, uint64_t c, uint64_t obj)
{
    void *frame = 0;
    uint64_t entry, cb, msg, res, slot;
    uint8_t hashbuf[8];
    uint64_t desc[6];

    cL4_ctx_setup_36a1a0(obj + 0x18, frame, 0, 0);
    slot = cL4_ctx_get_36b8b0(obj + 0x18);
    if (slot == 0) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000051,
                         0x80000000005acc30, (void *)cL4_s_Tightbeam_ForwardingConnection,
                         0x24, 2, 0x54, 0);
    }
    msg = *(uint64_t *)(obj + 0x20);
    cL4_tag_hash_259c0(hashbuf, b);
    desc[1] = FUN_0001fd9c(0);
    desc[0] = obj | 0x6000000000000000;
    desc[2] = hashbuf[0] & 1;
    entry = FUN_0001fde8(msg);
    cb = *(uint64_t *)slot;
    cL4_retain_36b270(obj);
    res = ((uint64_t (*)(uint64_t, void *, uint64_t, uint64_t))entry)(cb, &desc[0], cb, msg);
    cL4_release_36b118(slot);
    return res & 1;
}

/* FUN_0001f978 / FUN_0001f97c @ 0x1f978 / 0x1f97c   (est. cL4_forwarding_send2 / send3)
 * Ghidra: uint FUN_0001f978(void)   (identical pair)
 * Returns the low bit of the ForwardingConnection send (FUN_0001f834).
 * Confidence: low */
static uint64_t FUN_0001f978(void)
{
    return FUN_0001f834(0, 0, 0, 0) & 1;
}
static uint64_t FUN_0001f97c(void)
{
    return FUN_0001f834(0, 0, 0, 0) & 1;
}

/* FUN_0001f998 @ 0x1f998   (est. cL4_task_alloc_run4)
 * Ghidra: undefined8 FUN_0001f998(undefined8,...)
 * Allocates an object and runs the task initializer FUN_0001fa18 with the
 * given args; returns the allocated object.
 * Confidence: low */
static uint64_t FUN_0001f998(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    uint64_t obj = (uint64_t)cL4_alloc_36a940();
    FUN_0001fa18(a, (uint8_t)b, c, (uint8_t)d, e, f, (void *)obj);
    return obj;
}

/* FUN_0001fa18 @ 0x1fa18   (est. cL4_task_init4)
 * Ghidra: void FUN_0001fa18(undefined8,byte,undefined8,byte,undefined8,undefined8)
 * Initializes an async task object with a context-bearing callback closure and
 * runs it via FUN_00017b88, storing the result at +0x10.
 * Confidence: low */
static void FUN_0001fa18(uint64_t a, uint8_t b, uint64_t c, uint8_t d, uint64_t e, uint64_t f,
                         void *self)
{
    uint64_t *s = (uint64_t *)self;
    uint64_t e1, e2, engine, res, ctx;

    s[2] = 0;
    s[4] = 0;
    cL4_ctx_init_36b7f8((uint64_t)((uint8_t *)self + 0x18), 0);
    if (b < 2) {
        e1 = (b == 0) ? 3 : 0xd;
        e2 = 0;
    } else if (b == 2) {
        e2 = 1;
        e1 = 3;
    } else if (b == 3) {
        e2 = 8;
        e1 = 3;
    } else {
        e1 = FUN_0001532c(1, 0);
    }
    if (d < 2) {
        uint64_t e3 = (d == 0) ? 3 : 0xd;
        e2 = FUN_00015388(e3, c, 0);
    } else if (d == 2) {
        e2 = FUN_00015388(3, c, 1);
    } else if (d == 3) {
        e2 = FUN_00015388(3, c, 8);
    } else {
        e2 = FUN_0001532c(1, 0);
    }
    ctx = (uint64_t)cL4_alloc_36a940();          /* 0x28-byte closure object */
    *(uint64_t *)(ctx + 0x10) = (uint64_t)self;
    *(uint64_t *)(ctx + 0x18) = e;
    *(uint64_t *)(ctx + 0x20) = f;
    engine = FUN_0004b520(0);
    cL4_retain_36b270(0);
    cL4_retain_36b270(f);
    cL4_release_36b118(ctx);
    res = FUN_00017b88(e1, e2, engine);
    cL4_release_36b118(f);
    FUN_0004b664(engine);
    s[2] = res;
}

/* FUN_0001fc10 @ 0x1fc10   (est. cL4_forwarding_send_cb)
 * Ghidra: uint FUN_0001fc10(undefined8,undefined8,undefined8,ulong,code*)
 * Sends a message via the caller-supplied entry function (param_5), building
 * the message descriptor and returning the low bit of the result.
 * Confidence: low */
static uint64_t FUN_0001fc10(uint64_t a, uint64_t b, uint64_t c, uint64_t obj,
                             uint64_t (*fn)(uint64_t, void *))
{
    uint8_t hashbuf[8];
    uint64_t desc[6];
    uint64_t res;

    cL4_tag_hash_259c0(hashbuf, b);
    desc[1] = FUN_0001fd9c(0);
    desc[0] = obj | 0x6000000000000000;
    desc[2] = hashbuf[0] & 1;
    cL4_retain_36b270(obj);
    res = fn(obj, &desc[0]);
    return res & 1;
}

/* FUN_0001fca8 / FUN_0001fcac @ 0x1fca8 / 0x1fcac   (est. cL4_task_destroy / destroy2)
 * Ghidra: void FUN_0001fca8(void)   (identical pair)
 * Releases the task's +0x10 and +0x20 objects and destroys its context.
 * Confidence: low */
static void FUN_0001fca8(void *self)
{
    uint64_t *s = (uint64_t *)self;
    cL4_release_36b118(s[2]);
    cL4_release_36b118(s[4]);
    cL4_ctx_destroy_36b21c();
}
static void FUN_0001fcac(void *self)
{
    uint64_t *s = (uint64_t *)self;
    cL4_release_36b118(s[2]);
    cL4_release_36b118(s[4]);
    cL4_ctx_destroy_36b21c();
}

/* FUN_0001fcf8 / FUN_0001fcfc @ 0x1fcf8 / 0x1fcfc   (est. cL4_task_cleanup / cleanup2)
 * Ghidra: void FUN_0001fcf8(void)   (identical pair)
 * If the task's +0x10 slot is non-null, aborts the pending task and runs the
 * context void op; else traps.
 * Confidence: low */
static void FUN_0001fcf8(void *self)
{
    uint64_t *s = (uint64_t *)self;
    if (s[2] != 0) {
        FUN_00017bd4();
        FUN_0001fd28((uint64_t)((uint8_t *)self + 0x18));
        return;
    }
    cL4_breakpoint(0x1fd28);
}
static void FUN_0001fcfc(void *self)
{
    uint64_t *s = (uint64_t *)self;
    if (s[2] != 0) {
        FUN_00017bd4();
        FUN_0001fd28((uint64_t)((uint8_t *)self + 0x18));
        return;
    }
    cL4_breakpoint(0x1fd28);
}

/* FUN_0001fd28 @ 0x1fd28   (est. cL4_ctx_void)
 * Ghidra: undefined8 FUN_0001fd28(undefined8)
 * Runs the context void op (FUN_0036b8c0) and returns arg1.
 * Confidence: low */
static void FUN_0001fd28(uint64_t a)
{
    cL4_ctx_void_36b8c0(a);
}

/* FUN_0001fd50 / FUN_0001fd54 @ 0x1fd50 / 0x1fd54   (est. cL4_task_cleanup3 / cleanup4)
 * Ghidra: void FUN_0001fd50(void)   (identical pair)
 * If the task's +0x10 slot is non-null, aborts, runs the context void op and
 * the context done op; else traps.
 * Confidence: low */
static void FUN_0001fd50(void *self)
{
    uint64_t *s = (uint64_t *)self;
    if (s[2] != 0) {
        FUN_00017bd4();
        FUN_0001fd28((uint64_t)((uint8_t *)self + 0x18));
        cL4_ctx_done_36b6ac();
        return;
    }
    cL4_breakpoint(0x1fd8c);
}
static void FUN_0001fd54(void *self)
{
    uint64_t *s = (uint64_t *)self;
    if (s[2] != 0) {
        FUN_00017bd4();
        FUN_0001fd28((uint64_t)((uint8_t *)self + 0x18));
        cL4_ctx_done_36b6ac();
        return;
    }
    cL4_breakpoint(0x1fd8c);
}

/* FUN_0001fd9c @ 0x1fd9c   (est. cL4_dispatch_entry)
 * Ghidra: undefined8 FUN_0001fd9c(undefined8)
 * Dispatches the global entry at DAT_0065ac38+8 (a function pointer), then
 * returns arg1.
 * Confidence: low */
static uint64_t FUN_0001fd9c(uint64_t a)
{
    extern uint64_t DAT_0065ac38;
    (*(uint64_t (**)(void))(DAT_0065ac38 + 8))();
    return a;
}

/* FUN_0001fde8 @ 0x1fde8   (est. cL4_entry_resolve)
 * Ghidra: long FUN_0001fde8(ulong)
 * Resolves an entry pointer: if the low bit is set, dereferences the
 * pointer-aligned address and adds the sign-extended 32-bit displacement.
 * Confidence: low */
static uint64_t FUN_0001fde8(uint64_t obj)
{
    if ((obj & 1) != 0) {
        obj = *(uint64_t *)(obj & 0xfffffffffffffffe);
    }
    return (uint64_t)(obj + 4) + (uint64_t)(int32_t)*(uint32_t *)(obj + 4);
}

/* FUN_0001fe3c @ 0x1fe3c   (est. cL4_tag_decode_lo)
 * Ghidra: ulong FUN_0001fe3c(void)
 * Decodes a tag via FUN_0001fee8 and masks the result to clear the byte at
 * offset 2 (0xffffffff00ffffff).
 * Confidence: low */
static uint64_t FUN_0001fe3c(void)
{
    uint64_t lo, hi;
    FUN_0001fee8(0, &lo, &hi);
    return lo & 0xffffffff00ffffff;
}

/* FUN_0001fee8 @ 0x1fee8   (est. cL4_tag_decode)
 * Ghidra: undefined1[16] FUN_0001fee8(ulong)
 * Decodes a 64-bit tag word into a {flags,size} pair based on the low byte:
 * 0x20 => inline (lo=1,hi=0x100), 0x21 => {2,0x100}, 0x23 => {0,0x100},
 * otherwise {low-byte, 0}.
 * Confidence: low */
static void FUN_0001fee8(uint64_t tag, uint64_t *out_lo, uint64_t *out_hi)
{
    uint8_t b = (uint8_t)tag & 0xff;
    uint64_t lo, hi;

    if (b == 0x20) { lo = 1; hi = 0x100; }
    else if (b == 0x21) { lo = 2; hi = 0x100; }
    else { lo = tag & 0xff; hi = 0; }
    *out_lo = (tag & 0xff00) << 8 | (tag >> 0x10) << 0x20 | lo | hi;
    *out_hi = tag >> 0x30;
}

/* ------------------------------------------------------------------ *
 * TransportBuffer (Tightbeam transport) functions.
 * ------------------------------------------------------------------ */

/* FUN_00020134 @ 0x20134   (est. cL4_transport_init)
 * Ghidra: void FUN_00020134(void)
 * Initializes a TransportBuffer from a source descriptor: reads the resolved
 * value pair, zero-fills the transport state, and runs the entry transform.
 * Traps fatally (TransportBuffer, line 0x16) if the source is empty.
 * Confidence: low
 * Notes: SUB_d65f03c0a8c14ff4 opaque; stack canary checked at exit. */
static void FUN_00020134(uint64_t *src)
{
    uint64_t vtab = *(uint64_t *)(*(uint64_t *)((uint8_t *)src + 0x0) - 8);
    uint64_t lo, hi;
    int64_t canary = -0x2c8502b44bfffed6;

    cL4_ctx_setup_36a1a0(0, 0, 0, 0);
    lo = 0; hi = 0;
    if (lo == 0) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000040,
                         0x80000000005ace20, (void *)cL4_s_Tightbeam_TransportBuffer,
                         0x1f, 2, 0x16, 0);
    }
    /* zero-fill transport state */
    {
        uint64_t *s = (uint64_t *)0;
        s[0]=s[1]=s[2]=s[3]=s[4]=s[5]=0;
    }
    cL4_ctx_setup_36a1a0(lo, 0, 0, 1);
    if (canary != -0x2c8502b44bfffed6) {
        cL4_canary_panic_11d7e8();
    }
}

/* FUN_000202c0 @ 0x202c0   (est. cL4_transport_alloc_pair)
 * Ghidra: undefined1[16] FUN_000202c0(void)
 * Allocates a 0x68-byte TransportBuffer object, installs a closure, and
 * returns {entry, obj}.
 * Confidence: low */
static void FUN_000202c0(uint64_t *out_lo, uint64_t *out_hi)
{
    uint64_t obj = FUN_0036a804(0x68, 0xffffffffffffffff);
    FUN_00015708();
    *out_lo = (uint64_t)(uintptr_t)FUN_0001a1c8;
    *out_hi = obj;
}

/* FUN_00020310 @ 0x20310   (est. cL4_transport_op)
 * Ghidra: undefined8 FUN_00020310(code*,...)
 * Runs a transport operation: if the object's state flag (byte at +3) is clear,
 * calls the caller-supplied function, and on success (result 0) commits the
 * state fields; on failure logs the error. Traps fatally if the flag is set.
 * Confidence: low */
static uint64_t FUN_00020310(uint64_t (*fn)(uint64_t, uint64_t, uint64_t),
                             uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e,
                             uint8_t *self)
{
    uint64_t v0, v1, v2, r;
    int32_t status;

    if (self[3] == 0) {
        v0 = *(uint64_t *)self;
        v1 = *(uint64_t *)(self + 8);
        v2 = *(uint64_t *)(self + 0x10);
        r = fn(d, e, v0);
        status = (int32_t)r;
        if (status == 0) {
            cL4_retain_36b270(c);
            FUN_00020d0c(v0, v1, v2, 0);
            *(uint64_t *)self = v0;
            *(uint64_t *)(self + 8) = b;
            *(uint64_t *)(self + 0x10) = c;
            self[3] = 0;
        } else {
            FUN_003698b0(&status, FUN_00019aac(0), FUN_0065a550);
        }
        return r;
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000034,
                     0x80000000005accc0, (void *)cL4_s_Tightbeam_TransportBuffer,
                     0x1f, 2, 0x4d, 0);
}

/* FUN_00020448 @ 0x20448   (est. cL4_transport_write)
 * Ghidra: void FUN_00020448(undefined8,long,long*,undefined8,...)
 * Writes `len` bytes into a TransportBuffer at the current position: validates
 * the object is not forgotten (flag>=2) and that the range fits, then calls
 * FUN_002e2d24 and advances the position. Traps fatally otherwise.
 * Confidence: low */
static void FUN_00020448(uint64_t a, uint64_t len, uint64_t *tb, uint64_t c, uint64_t d,
                         uint8_t flag, uint64_t g, uint64_t h)
{
    uint64_t pos, start;

    if (flag < 2) {
        pos = tb[2];
        if (pos + len < pos) cL4_breakpoint(0x204c8);   /* SCARRY8 */
        if (pos + len <= tb[3]) {
            if ((int64_t)len < 0) cL4_breakpoint(0x204cc);
            start = tb[0] + pos;
            FUN_002e2d24(a, (void *)start, (void *)(start + len), g, h);
            if (tb[2] + len >= tb[2]) {
                tb[2] = tb[2] + len;
                return;
            }
            cL4_breakpoint(0x204d0);
        }
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                         (uint64_t)(uintptr_t)cL4_s_TransportBuffer_has_insufficient | 0x8000000000000000,
                         (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x57, 0);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000025,
                     (uint64_t)(uintptr_t)cL4_s_TransportBuffer_was_already_forg | 0x8000000000000000,
                     (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x3b, 0);
}

/* FUN_00020560 @ 0x20560   (est. cL4_transport_seek)
 * Ghidra: void FUN_00020560(long,long,undefined8,undefined8,byte)
 * Seeks a TransportBuffer to a new position: validates the object is not
 * forgotten and the position is within the buffer, then sets +0x10. Traps
 * fatally otherwise.
 * Confidence: low */
static void FUN_00020560(uint64_t pos, uint64_t tb, uint64_t c, uint64_t d, uint8_t flag)
{
    if (flag < 2) {
        if (pos < *(uint64_t *)(tb + 0x18)) {
            *(uint64_t *)(tb + 0x10) = pos;
            return;
        }
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000029,
                         (uint64_t)(uintptr_t)cL4_s_TransportBuffer_position_is_out | 0x8000000000000000,
                         (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x67, 0);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000025,
                     (uint64_t)(uintptr_t)cL4_s_TransportBuffer_was_already_forg | 0x8000000000000000,
                     (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x3b, 0);
}

/* FUN_00020628 @ 0x20628   (est. cL4_transport_forward)
 * Ghidra: void FUN_00020628(undefined8,undefined8,undefined8,long)
 * Forwards a TransportBuffer through the entry FUN_000208a8: validates the
 * not-forgotten flag and capacity, builds a frame, and dispatches. Traps
 * fatally if forgotten or capacity exceeded.
 * Confidence: low */
static void FUN_00020628(uint64_t a, uint64_t b, uint64_t c, uint64_t tb)
{
    uint64_t vtab = *(uint64_t *)(*(uint64_t *)((uint8_t *)tb + 0) - 8);
    uint8_t flag = 0;

    cL4_ctx_setup_36a1a0(0, 0, 0, 0);
    if (flag > 1) {
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000025,
                         0x80000000005acd00, (void *)cL4_s_Tightbeam_TransportBuffer,
                         0x1f, 2, 0x3b, 0);
    }
    if (*(uint64_t *)(tb + 0x20) < *(uint64_t *)(*(uint64_t *)((uint8_t *)tb + 0) + 0x40)) {
        cL4_breakpoint(0x2078c);
    }
    FUN_000208a8(tb, 1, (void *)FUN_00020d20, 0, 0, 0, 0, 0, 0, 0, 0);
}

/* FUN_000207e0 @ 0x207e0   (est. cL4_transport_forward2)
 * Ghidra: void FUN_000207e0(void)
 * Reads the type vtable, runs an opaque value transform, and dispatches the
 * result through the vtable's +0x20 slot.
 * Confidence: low
 * Notes: SUB_d65f03c0a8c14ff4 opaque. */
static void FUN_000207e0(void)
{
    uint64_t vtab = 0;
    void (*cb)(void *, void *, uint64_t);

    cL4_ctx_setup_36a1a0(0, 0, 0, 0);
    cb = *(void **)(vtab + 0x20);
    cb(0, 0, 0);
}

/* FUN_000208a8 @ 0x208a8   (est. cL4_transport_dispatch)
 * Ghidra: void FUN_000208a8(undefined8,undefined8,code*,...)
 * Dispatches a transport operation: checks the capability/rights bits and the
 * element-size ratios of two metadata words, then calls the entry function.
 * Traps on rights/ratio breaches.
 * Confidence: low */
static void FUN_000208a8(uint64_t tb, uint64_t one, void *entry, uint64_t a, uint64_t b,
                         uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h)
{
    uint32_t lo = (uint32_t)b;
    uint32_t hi = (uint32_t)(b >> 32);
    uint64_t vtab = *(uint64_t *)(*(uint64_t *)((uint8_t *)tb + 0) - 8);
    uint64_t m1, m2, r;

    cL4_ctx_setup_36a1a0(0, 0, 0, 0);
    if ((*(uint32_t *)(*(uint64_t *)((uint8_t *)c + 0) + 0x50) & lo & 0xff) != 0) {
        cL4_breakpoint(0x209e8);
    }
    m1 = *(uint64_t *)(*(uint64_t *)((uint8_t *)c + 0) + 0x48);
    m2 = *(uint64_t *)(*(uint64_t *)((uint8_t *)d + 0) + 0x48);
    if (m2 < m1) {
        if (m2 == 0) cL4_breakpoint(0x209ec);
        r = (m2 != 0) ? (m1 / m2) : 0;
        if (m1 != r * m2) cL4_breakpoint(0x20978);
    } else {
        if (m1 == 0) cL4_breakpoint(0x209f0);
        if (m1 == -1 && m2 == (uint64_t)-0x8000000000000000) cL4_breakpoint(0x209f8);
        r = (m1 != 0) ? (m2 / m1) : 0;
        if (m2 != r * m1) cL4_breakpoint(0x209f4);
    }
    ((void (*)(uint64_t, void *))entry)(((uint64_t)hi << 32) | lo, (void *)0);
}

/* FUN_000209f8 @ 0x209f8   (est. cL4_transport_base)
 * Ghidra: undefined8 FUN_000209f8(undefined8*,undefined8,undefined8,byte)
 * Returns the TransportBuffer's base pointer, validating it is not forgotten
 * and that position <= limit. Traps fatally otherwise.
 * Confidence: low */
static void FUN_000209f8(uint64_t *tb, uint64_t b, uint64_t c, uint8_t flag)
{
    if (flag < 2) {
        if ((int64_t)tb[4] <= (int64_t)tb[3]) {
            if ((int64_t)tb[4] >= 0) return;   /* returns tb[0] */
            cL4_breakpoint(0x20a38);
        }
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                         (uint64_t)(uintptr_t)cL4_s_TransportBuffer_has_illegal_rese | 0x8000000000000000,
                         (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x7b, 0);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000025,
                     (uint64_t)(uintptr_t)cL4_s_TransportBuffer_was_already_forg | 0x8000000000000000,
                     (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x3b, 0);
}

/* FUN_00020ac8 @ 0x20ac8   (est. cL4_transport_data_ptr)
 * Ghidra: long FUN_00020ac8(long*,undefined8,undefined8,byte)
 * Returns a pointer to the TransportBuffer's current data position, validating
 * that position/limit are within bounds and not forgotten. Traps fatally.
 * Confidence: low */
static uint64_t FUN_00020ac8(uint64_t *tb, uint64_t b, uint64_t c, uint8_t flag)
{
    uint64_t pos, lim;

    if (flag < 2) {
        pos = tb[4];
        if (pos <= tb[2] && (lim = tb[3], tb[2] <= lim)) {
            if (lim < pos) cL4_breakpoint(0x20b24);
            if ((int64_t)(lim - pos) >= 0) return tb[0] + pos;
            cL4_breakpoint(0x20b28);
        }
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000027,
                         (uint64_t)(uintptr_t)cL4_s_TransportBuffer_has_illegal_data | 0x8000000000000000,
                         (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x88, 0);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000025,
                     (uint64_t)(uintptr_t)cL4_s_TransportBuffer_was_already_forg | 0x8000000000000000,
                     (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x3b, 0);
}

/* FUN_00020bb8 @ 0x20bb8   (est. cL4_transport_raw_ptr)
 * Ghidra: undefined8 FUN_00020bb8(undefined8*,undefined8,undefined8,byte)
 * Returns the TransportBuffer's raw base pointer, validating position <= limit
 * and not forgotten. Traps fatally otherwise.
 * Confidence: low */
static void FUN_00020bb8(uint64_t *tb, uint64_t b, uint64_t c, uint8_t flag)
{
    if (flag < 2) {
        if ((int64_t)tb[2] <= (int64_t)tb[3]) {
            if ((int64_t)tb[2] >= 0) return;   /* returns tb[0] */
            cL4_breakpoint(0x20bf8);
        }
        cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd00000000000002b,
                         (uint64_t)(uintptr_t)cL4_s_TransportBuffer_has_illegal_raw_d | 0x8000000000000000,
                         (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x94, 0);
    }
    cL4_fatal_1afa84((void *)cL4_s_Fatal_error, 0xb, 2, 0xd000000000000025,
                     (uint64_t)(uintptr_t)cL4_s_TransportBuffer_was_already_forg | 0x8000000000000000,
                     (void *)cL4_s_Tightbeam_TransportBuffer, 0x1f, 2, 0x3b, 0);
}

/* FUN_00020c88 @ 0x20c88   (est. cL4_transport_forget)
 * Ghidra: void FUN_00020c88(undefined8,code*,undefined8,ulong)
 * Forgets a TransportBuffer: retains arg3, runs the entry (arg2), finalizes
 * arg1, and writes the final state via FUN_00020d0c. When the low byte of arg4
 * is clear, resets the state first.
 * Confidence: low */
static void FUN_00020c88(uint64_t a, void (*fn)(uint64_t), uint64_t b, uint64_t c)
{
    if ((c & 0xff) == 0) {
        cL4_retain_36b270(b);
        fn(a);
        cL4_finalize_12568((void *)a);
        FUN_00020d0c(a, (uint64_t)fn, b, 0);
        c = 0;
    }
    FUN_00020d0c(a, (uint64_t)fn, b, c);
}
