/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1),
 * "cL4 (679.100.61)". Ground truth: Ghidra FUN_ names + addresses in program
 * cl4_kernel.raw. All names are estimates unless a string/header matches.
 *
 * Slice 15: 0xdbbc0-0xdd9e4 — the XRT (XNU Runtime) boot-services layer:
 * capability allocation/free, CNode access, physical-memory-manager (PMM)
 * reference, untyped/IRQ/page-table cap retrieval, DART, and the boot-time
 * init/log helper methods. Functions returning a 16-byte value are the
 * classic cL4 XRT result struct {data, status}. Confidence is medium unless
 * a string matches (high). */

#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------------------ *
 * XRT boot-services types
 * ------------------------------------------------------------------ */

/* The 16-byte XRT method result: `data` (low word) and `status` (high word).
 * Returned by-value in x0/x1. Non-zero status indicates an error/fault. */
typedef struct xrt_result {
    uint64_t data;
    uint64_t status;
} xrt_result_t;

/* Boot context object. Many XRT methods operate on a per-call context whose
 * pointer is carried in a callee-saved register (x19/x20) by the ABI; the
 * decompiler reports it as unaff_x19/unaff_x20. Fields at the offsets the
 * binary reads/writes. */
typedef struct xrt_ctx {
    uint64_t vtable;            /* +0x00 object vtable */
    uint64_t tag;               /* +0x08 */
    uint64_t d0;                /* +0x10 */
    uint64_t d1;                /* +0x18 */
    uint64_t d2;                /* +0x20 */
    uint64_t d3;                /* +0x28 */
    uint64_t d4;                /* +0x30 */
    uint64_t d5;                /* +0x38 */
    uint64_t d6;                /* +0x40 */
    uint64_t d7;                /* +0x48 */
    uint64_t d8;                /* +0x50 */
    uint64_t d9;                /* +0x58 */
    uint64_t d10;               /* +0x60 */
    uint64_t d11;               /* +0x68 */
    uint64_t d12;               /* +0x70 */
    uint64_t d13;               /* +0x78 */
    uint64_t d14;               /* +0x80 */
    uint8_t  unused;            /* +0x88 */
    uint8_t  mode;              /* +0x90 */
} xrt_ctx_t;

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4/XRT helper declarations (their bodies are owned by the
 * range worker that owns each address; declared extern with a one-line note).
 * ------------------------------------------------------------------ */

/* FUN_0036a940 @ 0x36a940 — emit a log/print of a string (ptr,len,kind);
 * returns a status/result word. */
extern uint64_t xrt_log(void *msg, unsigned long len, int kind);
/* FUN_0036a1a0 @ 0x36a1a0 — copy `size` bytes from src to dst (dst,src,size,0). */
extern void xrt_copy(void *dst, const void *src, unsigned long size, int flags);
/* FUN_0036b118 @ 0x36b118 — drop a reference on an object (release). */
extern void xrt_release(void *obj);
/* FUN_0036b270 @ 0x36b270 — take a reference on an object (retain). */
extern void xrt_retain(void *obj);
/* FUN_0036b6ac @ 0x36b6ac — common tail: clean up / return from an XRT method. */
extern void xrt_tail(void);
/* FUN_0036b6f4 @ 0x36b6f4 — common epilogue used on error paths. */
extern void xrt_epilogue(void);
/* FUN_0036a804 @ 0x36a804 — allocate `size` bytes (with tag); returns pointer. */
extern void *xrt_alloc(unsigned long size, unsigned long tag);
/* FUN_0036a9d4 @ 0x36a9d4 — resolve/retain an object by (handle, class). */
extern void *xrt_lookup(unsigned long handle, unsigned long klass);
/* FUN_002a4ab4 @ 0x2a4ab4 — log an XRT event by code. */
extern void xrt_event_log(unsigned long code);
/* FUN_003a25d4 @ 0x3a25d4 — print/log a raw 64-bit word. */
extern void xrt_print_word(uint64_t word);
/* FUN_00027724 @ 0x27724 — fetch a function pointer from the boot symbol table
 * at the given address (address, 0x671df8). */
extern void *xrt_getfn(uint64_t addr);
/* thunk_FUN_002acbb8 @ 0x2acbb8 — printf-like formatter used by XRT logging. */
extern void xrt_printf(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g, uint64_t h);
/* FUN_00034f70 @ 0x34f70 — return the PMM/init-state object, or 0 if not
 * yet initialized. */
extern void *xrt_pmm_state(void);
/* FUN_00085374 @ 0x85374 — panic with a (msg,len,kind,code) triple. noreturn. */
extern void xrt_panic(void *msg, unsigned long len, int kind, unsigned long code);
/* FUN_001afa84 @ 0x1afa84 — noreturn fault/panic trampoline. */
extern void xrt_fatal(void);
/* FUN_0011d7e8 @ 0x11d7e8 — noreturn stack-canary failure handler. */
extern void xrt_canary_fail(uint64_t arg);
/* FUN_0006a4c0 @ 0x6a4c0 — helper; empty-ish boot hook. */
extern void xrt_boot_hook(void);
/* FUN_00002718 @ 0x2718 — register/copy a string slot (dst, src+0x10). */
extern void xrt_str_slot(void *dst, const void *src);
/* FUN_000b0888 @ 0xb0888 — store a value into a context slot. */
extern void xrt_set_slot(unsigned long a, void *slot, void *val);
/* FUN_00081e34 @ 0x81e34 — helper used after setting a slot. */
extern void xrt_slot_after(void);
/* FUN_0000276c @ 0x276c — copy a boot data block (dst, src, table). */
extern void xrt_copy_block(void *dst, void *src, void *table);
/* thunk_FUN_00084110 @ 0x84110 — boot-time hook. */
extern void xrt_boot_hook2(void);
/* FUN_000fdb98 @ 0xfdb98 — finalize/commit a result struct. */
extern void xrt_commit(void *res);
/* FUN_0006e7c0 @ 0x6e7c0 — parse/init a boot data descriptor into res. */
extern void xrt_parse_boot(void *arg, void *res);
/* FUN_001003e8 @ 0x1003e8 — return a boot class/symbol handle. */
extern unsigned long xrt_class(unsigned long which);
/* FUN_000ff914 @ 0xff914 — allocate/register a buffer of `size` with res. */
extern unsigned long xrt_buf_alloc(unsigned long size, void *res);
/* FUN_00086440 @ 0x86440 — return a global registry/table handle. */
extern unsigned long xrt_registry(unsigned long which);
/* FUN_00086590 @ 0x86590 — return an allocator handle. */
extern unsigned long xrt_allocator(unsigned long which);
/* FUN_00085a54 @ 0x85a54 — create/resolve a named object (res,size,klass,...). */
extern unsigned long xrt_named(void *res, unsigned long size, unsigned long klass, unsigned long flags, unsigned long x);
/* FUN_000fbbfc @ 0xfbbfc — finalize a boot descriptor. */
extern void xrt_finalize(void);
/* FUN_000026e8 @ 0x26e8 — release/teardown a boot data object. */
extern void xrt_teardown(void *obj);
/* FUN_000a91ec @ 0xa91ec — internal helper. */
extern void xrt_helper_a91ec(void);
/* FUN_0004ba64 @ 0x4ba64 — return an object's {fn,ctx} result word. */
extern xrt_result_t xrt_obj_result(uint64_t obj);
/* FUN_0004ba18 @ 0x4ba18 — return the dispatch {fn,ctx} pair for an object. */
extern xrt_result_t xrt_dispatch(void);
/* FUN_00151974 @ 0x151974 — boot phase transition (advance init phase). */
extern void xrt_phase_1(void);
/* FUN_00151a6c @ 0x151a6c — boot phase transition (advance init phase). */
extern void xrt_phase_2(void);
/* FUN_00157308 @ 0x157308 — string length / size check on a name. */
extern unsigned long xrt_strlen_check(unsigned long s);
/* FUN_000fdd78 @ 0xfdd78 — initialize a stack/scope struct. */
extern void xrt_scope_init(void *s);
/* FUN_000a9ae8 @ 0xa9ae8 — classify a scope; returns a kind code (1=special). */
extern int xrt_scope_kind(void *s);
/* FUN_000aa3ac @ 0xaa3ac — log/emit an error string. */
extern void xrt_err_str(void);
/* FUN_00117cc4 @ 0x117cc4 — copy a boot block (dst, src, size). */
extern void xrt_block_copy(void *dst, const void *src, unsigned long size);
/* FUN_0006d580 @ 0x6d580 — resolve a resource by (a,b); 0 if absent. */
extern void *xrt_resolve(void *a, void *b);
/* FUN_001000b8 @ 0x1000b8 — lookup helper. */
extern void xrt_lookup_1000(void);
/* FUN_000fe3b4 @ 0xfe3b4 — materialize/return an object handle. */
extern unsigned long xrt_materialize(unsigned long res);
/* FUN_0006d5c8 @ 0x6d5c8 — resolve a second resource by (a,b). */
extern void *xrt_resolve2(void *a, void *b);
/* FUN_0006d610 @ 0x6d610 — commit/register two resource ids. */
extern void xrt_commit2(unsigned int a, unsigned int b);
/* FUN_001e9c00 @ 0x1e9c00 — format an XRT value into a buffer. */
extern void xrt_fmt(void *buf);
/* FUN_0001e790 @ 0x1e790 — helper before value formatting. */
extern void xrt_fmt_pre(void);
/* FUN_000bde98 @ 0xbde98 — format a raw value. */
extern void xrt_fmt_raw(void);
/* FUN_000a00c4 @ 0xa00c4 — helper. */
extern void xrt_helper_a00c4(void);
/* FUN_001afa84 (see xrt_fatal) */

/* Boot-time data addresses (constants only). */
#define XRT_ADDR_677830 0x677830ull
#define XRT_ADDR_671df8 0x671df8ull
#define XRT_ADDR_671298 0x671298ull
#define XRT_ADDR_6776f0 0x6776f0ull

/* Stack canary sentinel used across this region. */
#define XRT_CANARY 0xd17a4fb44b02d2aull  /* -0x2c8502b44bfffed6 */

/* ------------------------------------------------------------------ *
 * Forward declarations (used by wrappers defined before their bodies).
 * ------------------------------------------------------------------ */

void xrt_teardown_dc840(void);
xrt_result_t xrt_init_log(void);
void xrt_build_obj(uint64_t *param_1);
void xrt_build_obj2(uint64_t *param_1);
xrt_result_t xrt_bootlog(void);
void xrt_bootlog_inner(void);
void xrt_copy_ctx(uint64_t *param_1);
void xrt_check_dc7f4(void);
void xrt_physalloc_init(void *arg);
void xrt_conclave_init(uint64_t asid, long mode);
void xrt_generic_init(void);
void xrt_pt_dart_init(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f);
void xrt_fatal_dce40(void);

/* ------------------------------------------------------------------ *
 * Trivial stubs (empty bodies; many XRT methods are reserved/no-op).
 * ------------------------------------------------------------------ */

/* FUN_000dbbc0 @ 0xdbbc0 — reserved XRT method; no-op. */
void xrt_dummy_dbbc0(void) { return; }

/* FUN_000dbbd0 @ 0xdbbd0 — reserved XRT method; no-op. */
void xrt_dummy_dbbd0(void) { return; }

/* FUN_000dbbe0 @ 0xdbbe0 — reserved XRT method returning success (0). */
uint64_t xrt_ok_dbbe0(void) { return 0; }

/* FUN_000dbc40 @ 0xdbc40 — reserved XRT method; no-op. */
void xrt_dummy_dbc40(void) { return; }

/* FUN_000dbc70 @ 0xdbc70 — reserved XRT method; no-op. */
void xrt_dummy_dbc70(void) { return; }

/* FUN_000dbc84 @ 0xdbc84 — reserved XRT method; no-op. */
void xrt_dummy_dbc84(void) { return; }

/* FUN_000dbc98 @ 0xdbc98 — reserved XRT method; no-op. */
void xrt_dummy_dbc98(void) { return; }

/* FUN_000dbce0 @ 0xdbce0 — reserved XRT method; no-op. */
void xrt_dummy_dbce0(void) { return; }

/* FUN_000dbcec @ 0xdbcec — reserved XRT method; no-op. */
void xrt_dummy_dbcec(void) { return; }

/* FUN_000dbd0c @ 0xdbd0c — reserved XRT method; no-op. */
void xrt_dummy_dbd0c(void) { return; }

/* FUN_000dbd18 @ 0xdbd18 — reserved XRT method; no-op. */
void xrt_dummy_dbd18(void) { return; }

/* FUN_000dbd60 @ 0xdbd60 — reserved XRT method; no-op. */
void xrt_dummy_dbd60(void) { return; }

/* FUN_000dbdac @ 0xdbdac — reserved XRT method; no-op. */
void xrt_dummy_dbdac(void) { return; }

/* FUN_000dbdbc @ 0xdbdbc — reserved XRT method; no-op. */
void xrt_dummy_dbdbc(void) { return; }

/* FUN_000dbdcc @ 0xdbdcc — reserved XRT method; no-op. */
void xrt_dummy_dbdcc(void) { return; }

/* FUN_000dbde8 @ 0xdbde8 — reserved XRT method; no-op. */
void xrt_dummy_dbde8(void) { return; }

/* FUN_000dbdf4 @ 0xdbdf4 — reserved XRT method; no-op. */
void xrt_dummy_dbdf4(void) { return; }

/* FUN_000dbe00 @ 0xdbe00 — reserved XRT method; no-op. */
void xrt_dummy_dbe00(void) { return; }

/* FUN_000dbe70 @ 0xdbe70 — reserved XRT method; no-op. */
void xrt_dummy_dbe70(void) { return; }

/* FUN_000dbea4 @ 0xdbea4 — reserved XRT method; no-op. */
void xrt_dummy_dbea4(void) { return; }

/* FUN_000dbec4 @ 0xdbec4 — reserved XRT method; no-op. */
void xrt_dummy_dbec4(void) { return; }

/* FUN_000dbed0 @ 0xdbed0 — reserved XRT method; no-op. */
void xrt_dummy_dbed0(void) { return; }

/* FUN_000dbee8 @ 0xdbee8 — reserved XRT method; no-op. */
void xrt_dummy_dbee8(void) { return; }

/* FUN_000dbefc @ 0xdbefc — reserved XRT method; no-op. */
void xrt_dummy_dbefc(void) { return; }

/* FUN_000dbf08 @ 0xdbf08 — reserved XRT method; no-op. */
void xrt_dummy_dbf08(void) { return; }

/* FUN_000dbf14 @ 0xdbf14 — reserved XRT method; no-op. */
void xrt_dummy_dbf14(void) { return; }

/* FUN_000dbf20 @ 0xdbf20 — reserved XRT method; no-op. */
void xrt_dummy_dbf20(void) { return; }

/* FUN_000dbf48 @ 0xdbf48 — reserved XRT method; no-op. */
void xrt_dummy_dbf48(void) { return; }

/* FUN_000dc5d4 @ 0xdc5d4 — reserved XRT method; no-op.
 * Confidence: high (verified: decompile is an empty body). */
void xrt_dummy_dc5d4(void) { return; }

/* FUN_000dce18 @ 0xdce18 — reserved XRT method; no-op. */
void xrt_dummy_dce18(void) { return; }

/* FUN_000dce2c @ 0xdce2c — reserved XRT method; no-op. */
void xrt_dummy_dce2c(void) { return; }

/* FUN_000dce50 @ 0xdce50 — reserved XRT method; no-op. */
void xrt_dummy_dce50(void) { return; }

/* FUN_000dce60 @ 0xdce60 — reserved XRT method; no-op. */
void xrt_dummy_dce60(void) { return; }

/* ------------------------------------------------------------------ *
 * XRT result-returning helpers.
 * ------------------------------------------------------------------ */

/* FUN_000dbbec @ 0xdbbec — return the standard XRT "Fatal error" result:
 * {msg="Fatal error" (0x5accd0), status=0xb}. */
xrt_result_t xrt_fatal_error(void)
{
    xrt_result_t r;
    r.data   = (uint64_t)"Fatal error";   /* s_Fatal_error_005accd0 */
    r.status = 0xb;
    return r;
}

/* FUN_000dbc2c @ 0xdbc2c — return the "XRT launcher boot data not
 * initialized" result: {msg="initializeXrtLauncherBootData" (0x5c37b0),
 * status=0x29}. */
xrt_result_t xrt_bootdata_notinit(void)
{
    xrt_result_t r;
    r.data   = (uint64_t)"initializeXrtLauncherBootData";  /* s_..._005c37b0 */
    r.status = 0x29;
    return r;
}

/* FUN_000dbca4 @ 0xdbca4 — return an opaque 16-byte constant result
 * {0x5f544c5541465f5f, 0xef43455f41544144} — a fault/canary word pair
 * (DAT literal). */
xrt_result_t xrt_fault_literal(void)
{
    xrt_result_t r;
    r.data   = 0x5f544c5541465f5full;   /* literal "__FAULT_..." */
    r.status = 0xef43455f41544144ull;   /* literal "...DATA_EC." */
    return r;
}

/* FUN_000dbc18 @ 0xdbc18 — return an error result tagged with the context
 * object (x19) in the high word: {status=0xd000000000000013,
 * data=ctx|0x8000000000000000}. */
xrt_result_t xrt_err_tagged_13(uint64_t ctx)
{
    xrt_result_t r;
    r.status = 0xd000000000000013ull;
    r.data   = ctx | 0x8000000000000000ull;
    return r;
}

/* FUN_000dbd9c @ 0xdbd9c — return an error result tagged with the context
 * object (x19): {status=0xd000000000000010, data=ctx|0x8000000000000000}. */
xrt_result_t xrt_err_tagged_10(uint64_t ctx)
{
    xrt_result_t r;
    r.status = 0xd000000000000010ull;
    r.data   = ctx | 0x8000000000000000ull;
    return r;
}

/* FUN_000dbe90 @ 0xdbe90 — build a 16-byte result from a partial value:
 * data = (param_1 & 0xffffffffffff) | 0x614d000000000000 ("Ma".. prefix),
 * status = 0xeb000000004f6863. Used to tag an object with a two-part literal. */
xrt_result_t xrt_tag_pair(uint64_t val)
{
    xrt_result_t r;
    r.data   = (val & 0xffffffffffffull) | 0x614d000000000000ull;
    r.status = 0xeb000000004f6863ull;
    return r;
}

/* FUN_000dbf34 @ 0xdbf34 — return the "getBootCNode() not implemented"
 * result: {msg="getBootCNode()" (0x5c30e2), status=0xe}. */
xrt_result_t xrt_need_boot_cnode(void)
{
    xrt_result_t r;
    r.data   = (uint64_t)"getBootCNode()";  /* s_getBootCNode___005c30e2 */
    r.status = 0xe;
    return r;
}

/* FUN_000dc500 @ 0xdc500 — return an error result {msg=0x4c2680,
 * status=0xd000000000000012}. */
xrt_result_t xrt_err_dc500(void)
{
    xrt_result_t r;
    r.data   = 0x80000000004c2680ull;
    r.status = 0xd000000000000012ull;
    return r;
}

/* FUN_000dc5c4 @ 0xdc5c4 — return a result carrying the object/class handle
 * 0x651160: {data=0x651160, status=0}. */
xrt_result_t xrt_handle_dc5c4(void)
{
    xrt_result_t r;
    r.data   = 0x651160;
    r.status = 0;
    return r;
}

/* FUN_000dcde4 @ 0xdcde4 — return a result carrying the object/class handle
 * 0x651230: {data=0x651230, status=0}. */
xrt_result_t xrt_handle_dcde4(void)
{
    xrt_result_t r;
    r.data   = 0x651230;
    r.status = 0;
    return r;
}

/* FUN_000dcdf4 @ 0xdcdf4 — return the standard "Fatal error" result
 * (identical to xrt_fatal_error / FUN_000dbbec). */
xrt_result_t xrt_fatal_error2(void)
{
    xrt_result_t r;
    r.data   = (uint64_t)"Fatal error";   /* s_Fatal_error_005accd0 */
    r.status = 0xb;
    return r;
}

/* ------------------------------------------------------------------ *
 * XRT dispatch / vtable thunks (indirect calls through method tables).
 * ------------------------------------------------------------------ */

/* FUN_000dc6e8 @ 0xdc6e8 — dispatch through the object vtable at +0x28:
 * call (ctx->vtable+0x28)(self, -1, 7, obj, &argblock). */
void xrt_dispatch_28(xrt_result_t dispatch, uint64_t obj, uint64_t *args)
{
    uint64_t fn  = dispatch.status;
    uint64_t ctx = dispatch.data;
    uint64_t local[3];
    local[0] = args[0];
    local[1] = args[1];
    local[2] = args[2];
    ((void (*)(uint64_t, uint64_t, uint64_t, uint64_t, void *))
        (*(void **)(fn + 0x28)))(ctx, 0xffffffffffffffffull, 7, obj, &local);
    return;
}

/* FUN_000dcd1c @ 0xdcd1c — dispatch through the object vtable at +0x28 with
 * a fixed three-word argument block {DAT_004c27a8, uRam_004c27b0, 0}. */
void xrt_dispatch_28_fixed(uint64_t obj)
{
    xrt_result_t dispatch = xrt_dispatch();
    uint64_t local[3];
    local[0] = 0x4c27a8;      /* _DAT_004c27a8 */
    local[1] = 0x4c27b0;      /* uRam_00000000004c27b0 */
    local[2] = 0;
    ((void (*)(uint64_t, uint64_t, uint64_t, uint64_t, void *))
        (*(void **)(dispatch.status + 0x28)))(dispatch.data, 0xffffffffffffffffull, 7, obj, &local);
    return;
}

/* FUN_000dcd78 @ 0xdcd78 — dispatch through the object vtable at +0x10:
 * call (ctx->vtable+0x10)(self, arg). */
void xrt_dispatch_10(uint64_t arg)
{
    xrt_result_t dispatch = xrt_dispatch();
    ((void (*)(uint64_t, uint64_t))
        (*(void **)(dispatch.status + 0x10)))(dispatch.data, arg);
    return;
}

/* FUN_000dcdac @ 0xdcdac — indirect call through a function pointer stored at
 * *param_2: (*param_2)(param_1, param_3, param_4). */
void xrt_call_ptr(uint64_t a, void **fnslot, uint64_t c, uint64_t d)
{
    ((void (*)(uint64_t, uint64_t, uint64_t))(*fnslot))(a, c, d);
    return;
}

/* FUN_000dcdc0 @ 0xdcdc0 — indirect call through vtable slot +0x18:
 * (*(param_2+0x18))(param_1, param_3, param_4). */
void xrt_call_vt18(uint64_t a, uint64_t vt, uint64_t c, uint64_t d)
{
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(void **)(vt + 0x18)))(a, c, d);
    return;
}

/* FUN_000dcdd4 @ 0xdcdd4 — indirect call through vtable slot +0x10:
 * (*(param_2+0x10))(param_1, param_3). */
void xrt_call_vt10(uint64_t a, uint64_t vt, uint64_t c)
{
    ((void (*)(uint64_t, uint64_t))(*(void **)(vt + 0x10)))(a, c);
    return;
}

/* FUN_000dcb3c @ 0xdcb3c — call vtable slot +0x68 on the context object. */
void xrt_vt_68(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* context carried in callee-saved x20 */
    ((void (*)(void))(*(void **)(ctx->vtable + 0x68)))();
    return;
}

/* FUN_000dcb78 @ 0xdcb78 — call vtable slot +0x60 on the context object. */
void xrt_vt_60(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(void))(*(void **)(ctx->vtable + 0x60)))();
    return;
}

/* FUN_000dcbb4 @ 0xdcbb4 — call vtable slot +0x80 on the context object. */
void xrt_vt_80(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(void))(*(void **)(ctx->vtable + 0x80)))();
    return;
}

/* FUN_000dcbf0 @ 0xdcbf0 — call vtable slot +0x90 on the context object. */
void xrt_vt_90(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(void))(*(void **)(ctx->vtable + 0x90)))();
    return;
}

/* FUN_000dcc2c @ 0xdcc2c — call vtable slot +0x70 on the context object. */
void xrt_vt_70(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(void))(*(void **)(ctx->vtable + 0x70)))();
    return;
}

/* FUN_000dcc68 @ 0xdcc68 — call vtable slot +0x78 on the context object. */
void xrt_vt_78(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(void))(*(void **)(ctx->vtable + 0x78)))();
    return;
}

/* FUN_000dcca4 @ 0xdcca4 — call vtable slot +0x58 on the context object. */
void xrt_vt_58(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(void))(*(void **)(ctx->vtable + 0x58)))();
    return;
}

/* FUN_000dcce0 @ 0xdcce0 — call vtable slot +0x88 on the context object. */
void xrt_vt_88(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(void))(*(void **)(ctx->vtable + 0x88)))();
    return;
}

/* FUN_000dc940 @ 0xdc940 — call vtable slot +0x60 with two args + 0. */
void xrt_vt_60_2(uint64_t a, uint64_t b)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(void **)(ctx->vtable + 0x60)))(a, b, 0);
    return;
}

/* FUN_000dc944 @ 0xdc944 — call vtable slot +0x60 with two args + 0
 * (duplicate of xrt_vt_60_2). */
void xrt_vt_60_2b(uint64_t a, uint64_t b)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;
    ((void (*)(uint64_t, uint64_t, uint64_t))(*(void **)(ctx->vtable + 0x60)))(a, b, 0);
    return;
}

/* ------------------------------------------------------------------ *
 * Boot init / context-store helpers.
 * ------------------------------------------------------------------ */

/* FUN_000dbcf8 @ 0xdbcf8 — store a string handle into context slot +0x270 and
 * register its +0x10 offset into slot +0x328 (context in x19). */
void xrt_store_str(uint64_t str, uint64_t ctx)
{
    *(uint64_t *)(ctx + 0x270) = str;
    xrt_str_slot((void *)(ctx + 0x328), (const void *)(str + 0x10));
    return;
}

/* FUN_000dbd24 @ 0xdbd24 — write two stack slots (0 and status
 * 0xe000000000000000) into the caller's frame at -0x118/-0x110. */
void xrt_set_d_0(void)
{
    uint64_t *slot = (uint64_t *)0;   /* caller frame at unaff_x29-0x118 */
    slot[0] = 0;
    slot[1] = 0xe000000000000000ull;
    return;
}

/* FUN_000dbd40 @ 0xdbd40 — write two stack slots (0 and status
 * 0xe000000000000000) into the caller's frame and log event 0x1e. */
void xrt_set_d_0e(void)
{
    uint64_t *slot = (uint64_t *)0;   /* caller frame at unaff_x29-0x120 */
    slot[0] = 0;
    slot[1] = 0xe000000000000000ull;
    xrt_event_log(0x1e);
    return;
}

/* FUN_000dbd7c @ 0xdbd7c — store a value into context slot +0x270 via the
 * set-slot helper (context in x19). */
void xrt_set_slot_270(uint64_t val, uint64_t ctx)
{
    xrt_set_slot(1, (void *)(ctx + 0x270), (void *)val);
    return;
}

/* FUN_000dbddc @ 0xdbddc — copy 0x20 bytes between two buffers (XRT copy). */
void xrt_copy_20(void *dst, void *src)
{
    xrt_copy(dst, src, 0x20, 0);
    return;
}

/* FUN_000dbe0c @ 0xdbe0c — log a message string (len 0x18, kind 7). */
void xrt_log_18(void *msg)
{
    xrt_log(msg, 0x18, 7);
    return;
}

/* FUN_000dbe18 @ 0xdbe18 — store a value (x20) into context slot +0x270
 * (context in x19) then run the after-store hook. */
void xrt_store_270_then(uint64_t val, uint64_t ctx)
{
    *(uint64_t *)(ctx + 0x270) = val;
    xrt_slot_after();
    return;
}

/* FUN_000dbe30 @ 0xdbe30 — print a log line {0x203a20, 0xe300000000000000}. */
void xrt_log_dbe30(void)
{
    xrt_printf(0x203a20, 0xe300000000000000ull, 0, 0, 0, 0, 0, 0);
    return;
}

/* FUN_000dbe40 @ 0xdbe40 — copy a boot data block from 0x650f48 with table
 * DAT_004c2490 into the caller frame. */
void xrt_copy_block_dbe40(void)
{
    uint64_t dst = (uint64_t)0;   /* &stack0x00000070 (unaff) */
    xrt_copy_block((void *)dst, (void *)0x650f48, (void *)0x4c2490);
    return;
}

/* FUN_000dbe58 @ 0xdbe58 — log a message string (len 0x10, kind 7). */
void xrt_log_10(void *msg)
{
    xrt_log(msg, 0x10, 7);
    return;
}

/* FUN_000dbe64 @ 0xdbe64 — drop a reference (release) on the object. */
void xrt_release_dbe64(void)
{
    xrt_release((void *)0);
    return;
}

/* FUN_000dbe7c @ 0xdbe7c — store a value (x23) into caller frame slot
 * (in_stack_000000c0 + 0x10). */
void xrt_store_frame_c0(uint64_t val)
{
    uint64_t *slot = (uint64_t *)0;   /* in_stack_000000c0 + 0x10 */
    *slot = val;
    return;
}

/* FUN_000dbeb0 @ 0xdbeb0 — store two values into caller frame slots
 * (-0x118/-0x110): {in_x9, param_1}. */
void xrt_store_frame_b0(uint64_t a, uint64_t b)
{
    uint64_t *slot = (uint64_t *)0;   /* unaff_x29-0x118 */
    slot[0] = a;
    slot[1] = b;
    return;
}

/* FUN_000dbedc @ 0xdbedc — return the caller-frame slot at -0x120. */
uint64_t xrt_get_frame_120(void)
{
    return *(volatile uint64_t *)0;   /* unaff_x29-0x120 */
}

/* FUN_000dbf5c @ 0xdbf5c — boot-time hook (calls thunk_FUN_00084110). */
void xrt_boot_hook_dbf5c(void)
{
    xrt_boot_hook2();
    return;
}

/* FUN_000dbf70 @ 0xdbf70 — drop a reference on the caller-frame slot at
 * -0x160. */
void xrt_release_frame_160(void)
{
    xrt_release((void *)0);   /* *(unaff_x29-0x160) */
    return;
}

/* FUN_000dbf7c @ 0xdbf7c — log a message string (len 0x28, kind 7). */
void xrt_log_28(void *msg)
{
    xrt_log(msg, 0x28, 7);
    return;
}

/* FUN_000dbc54 @ 0xdbc54 — boot hook. */
void xrt_hook_dbc54(void) { xrt_boot_hook(); return; }

/* FUN_000dbcc8 @ 0xdbcc8 — boot hook (duplicate). */
void xrt_hook_dbcc8(void) { xrt_boot_hook(); return; }

/* FUN_000dbd8c @ 0xdbd8c — return the boot symbol-table address 0x677830. */
uint64_t xrt_sym_677830(void) { return 0x677830; }

/* FUN_000dc1f8 @ 0xdc1f8 — wrapper calling FUN_000dc130 (boot init log). */
void xrt_init_log_wrap(void) { xrt_init_log(); return; }

/* FUN_000dc51c @ 0xdc51c — internal helper + tail. */
void xrt_help_dc51c(void) { xrt_helper_a91ec(); xrt_tail(); return; }

/* FUN_000dc520 @ 0xdc520 — internal helper + tail (duplicate). */
void xrt_help_dc520(void) { xrt_helper_a91ec(); xrt_tail(); return; }

/* FUN_000dc544 @ 0xdc544 — wrapper calling FUN_000dc46c (build object). */
void xrt_build_dc544(void) { xrt_build_obj((void *)0); return; }

/* FUN_000dc548 @ 0xdc548 — wrapper calling FUN_000dc46c (build object). */
void xrt_build_dc548(void) { xrt_build_obj((void *)0); return; }

/* FUN_000dc55c @ 0xdc55c — log event via FUN_000dc500 and return status
 * 0xd000000000000012. */
uint64_t xrt_err_12_dc55c(void)
{
    xrt_err_dc500();
    return 0xd000000000000012ull;
}

/* FUN_000dc560 @ 0xdc560 — duplicate of xrt_err_12_dc55c. */
uint64_t xrt_err_12_dc560(void)
{
    xrt_err_dc500();
    return 0xd000000000000012ull;
}

/* FUN_000dd3cc @ 0xdd3cc — wrapper calling FUN_000dcf1c (copy context). */
void xrt_copy_ctx_dd3cc(void) { xrt_copy_ctx((void *)0); return; }

/* FUN_000dd3f0 @ 0xdd3f0 — wrapper calling FUN_000dd20c (boot log). */
void xrt_bootlog_dd3f0(void) { xrt_bootlog(); return; }

/* FUN_000dd9e4 @ 0xdd9e4 — wrapper calling FUN_000dd6c8 (build object 2). */
void xrt_build2_dd9e4(void) { xrt_build_obj2((void *)0); return; }

/* FUN_000dd9bc @ 0xdd9bc — internal helper + tail. */
void xrt_help_dd9bc(void) { xrt_helper_a00c4(); xrt_tail(); return; }

/* FUN_000dd9c0 @ 0xdd9c0 — internal helper + tail (duplicate). */
void xrt_help_dd9c0(void) { xrt_helper_a00c4(); xrt_tail(); return; }

/* FUN_000dc840 @ 0xdc840 — run the teardown/check (FUN_000dc7f4), the no-op
 * FUN_000dce50, then tail. */
void xrt_teardown_dc840(void)
{
    xrt_check_dc7f4();
    xrt_dummy_dce50();
    xrt_tail();
    return;
}

/* FUN_000dc844 @ 0xdc844 — duplicate of xrt_teardown_dc840. */
void xrt_teardown_dc844(void)
{
    xrt_check_dc7f4();
    xrt_dummy_dce50();
    xrt_tail();
    return;
}

/* FUN_000dd3a0 @ 0xdd3a0 — release the context slot +0x10 then tail. */
void xrt_release_ctx10(void)
{
    xrt_release((void *)0);   /* *(unaff_x20+0x10) */
    xrt_tail();
    return;
}

/* FUN_000dd3a4 @ 0xdd3a4 — duplicate of xrt_release_ctx10. */
void xrt_release_ctx10b(void)
{
    xrt_release((void *)0);
    xrt_tail();
    return;
}

/* ------------------------------------------------------------------ *
 * Larger XRT boot-services methods.
 * ------------------------------------------------------------------ */

/* FUN_000dbf88 @ 0xdbf88 — return a log/error result from FUN_0036a940 while
 * running the physical-allocator init (FUN_000dc21c) on `arg`. */
uint64_t xrt_bf88(void *arg)
{
    uint64_t res;
    res = xrt_log((void *)0, 0, 0);   /* FUN_0036a940() result */
    xrt_physalloc_init(arg);
    return res;
}

/* FUN_000dbfd8 @ 0xdbfd8 — build an XRT capability result object: store the
 * source object into context +0x10, fetch a function pointer from the source
 * vtable, call it to materialize a 0x4000-byte capability descriptor, and if
 * successful (x21==0) copy the descriptor into the context block
 * (+0x18..+0x49) and commit it; otherwise release everything and run the
 * error epilogue. `param_2` is the PMM/registry object whose vtable slot
 * +0x1b8 supplies the materializer. */
void xrt_build_cap(void *src, void **pmm)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    void *srcobj;
    uint64_t uVar1;
    void *matfn;
    uint64_t local[3];
    uint8_t  body[0x30];
    uint8_t  b2[8];

    ctx->d0 = (uint64_t)src;
    srcobj = *(void **)(*(uint64_t *)((uint64_t)src + 0x10) + 0x40);
    matfn = *(void **)(*(uint64_t *)(uint64_t)pmm + 0x1b8);
    xrt_retain((void *)0);   /* FUN_0036b270() */
    ((void (*)(void *, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))
        matfn)(&local, 8, (uint64_t)srcobj, 0x4000, 0, 0);
    if (/* unaff_x21 == 0 */ 1) {
        *(uint64_t *)((uint8_t *)&ctx->d1) = local[0];
        *(uint64_t *)((uint8_t *)&ctx->d1 + 8) = local[1];
        *(uint64_t *)((uint8_t *)&ctx->d2) = local[0];
        /* context +0x18..+0x49 filled from the descriptor words */
        uint64_t *d = (uint64_t *)&ctx->d1;
        uint64_t *s = (uint64_t *)&local;
        for (int i = 0; i < 4; i++) d[i] = s[i];
        ctx->d5 = 0;   /* +0x40 CONCAT from local words */
        ctx->d4 = 0;
        uVar1 = *(uint64_t *)(*(uint64_t *)((uint64_t)ctx->d0) + 0x10);
        xrt_retain((void *)uVar1);
        xrt_commit(&local);
        xrt_release((void *)uVar1);
        xrt_release(src);
        xrt_release(pmm);
    } else {
        xrt_release(src);
        xrt_release(pmm);
        xrt_release((void *)ctx->d0);
        xrt_epilogue();
    }
    return;
}

/* FUN_000dc130 @ 0xdc130 — boot init/log sequence: log event 0x1d, print a
 * word, fetch and invoke a boot function, print an error pair
 * {0x29, 0xe100000000000000}, and return the error result
 * {msg=0x5c3c10, status=0xd00000000000002a}. */
xrt_result_t xrt_init_log(void)
{
    void *fn;
    xrt_result_t r;

    xrt_event_log(0x1d);
    xrt_print_word(0xe000000000000000ull);
    fn = xrt_getfn(XRT_ADDR_671df8);
    ((void (*)(uint64_t, uint64_t))fn)(XRT_ADDR_677830, XRT_ADDR_671df8);
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x29, 0xe100000000000000ull, 0, 0, 0, 0, 0, 0);
    r.data   = 0x80000000005c3c10;
    r.status = 0xd00000000000002aull;
    return r;
}

/* FUN_000dc21c @ 0xdc21c — physical-allocator boot init. Parses the boot data
 * descriptor for `arg`, allocates a 0x4000-byte buffer, builds the phys
 * allocator object and registers it; panics "init(physAllocator" (0x5c3c60,
 * len 0x14, kind 2, code 0x32) if the PMM state is absent; on success runs
 * the /AppleInternal/Library/BuildRoot (0x5c3cb0) registration path via
 * FUN_000dc5d4. */
void xrt_physalloc_init(void *arg)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    uint64_t uVar1, uVar2, uVar3;
    void *res[3];
    void *l60, *l58;

    xrt_parse_boot(arg, res);
    uVar1 = xrt_class(0);
    xrt_log((void *)uVar1, 0x52, 7);
    uVar1 = xrt_buf_alloc(0x4000, res);
    if (/* unaff_x21 == 0 */ 1) {
        ctx->d0 = uVar1;
        uVar1 = xrt_registry(0);
        res[0] = xrt_lookup(uVar1, 0x64e1c0);
        l58 = (void *)0x65f998;
        l60 = (void *)uVar1;
        uVar1 = xrt_allocator(0);
        xrt_log((void *)uVar1, 0x50, 7);
        uVar1 = xrt_named(res, 0x4000, 0x11, 0x1808, 0);
        uVar2 = (uint64_t)xrt_pmm_state();
        if (uVar2 == 0) {
            xrt_panic((void *)"init(physAllocator", 0x14, 2, 0x32);
        }
        xrt_retain((void *)0);
        xrt_dummy_dc5d4();
        xrt_finalize();
        xrt_teardown(arg);
        xrt_release((void *)uVar1);
        xrt_release((void *)ctx->d0);
    } else {
        xrt_teardown(arg);
    }
    xrt_epilogue();
    return;
}

/* FUN_000dc46c @ 0xdc46c — build a boot object: log class 0x6511c8 (len 0x51,
 * kind 7), retain two objects, call FUN_000dbfd8 to build a cap, and on
 * success store the object registry pointers into param_1
 * {param_1[0]=result, param_1[3]=0x6511c8, param_1[4]=0x6614c0}. */
void xrt_build_obj(uint64_t *param_1)
{
    uint64_t uVar1;

    xrt_log((void *)0x6511c8, 0x51, 7);
    xrt_retain((void *)0);
    xrt_retain((void *)0);   /* FUN_0036b270(param_2) */
    uVar1 = (uint64_t)xrt_build_cap;   /* FUN_000dbfd8() */
    if (/* unaff_x21 == 0 */ 1) {
        param_1[3] = 0x6511c8;
        param_1[4] = 0x6614c0;
        param_1[0] = uVar1;
    }
    return;
}

/* FUN_000dc5ec @ 0xdc5ec — wrapper: run the no-op FUN_000dce50, capture a
 * log result, then run the conclaveId-asid init (FUN_000dc634). */
uint64_t xrt_5ec(uint64_t a, uint64_t b)
{
    uint64_t res;
    xrt_dummy_dce50();
    res = xrt_log((void *)0, 0, 0);
    xrt_conclave_init(a, b);
    return res;
}

/* FUN_000dc634 @ 0xdc634 — conclaveId:asid boot init. Panics
 * "init(conclaveId:asid" (0x5c3e00, len 0x16, kind 2, code 0x14) if the PMM
 * state is absent; otherwise stores the state into context +0x10, and if
 * param_2 >= 0 initializes the ASID (param_1 & 0xffff) via FUN_000dc6e8,
 * advances two boot phases, and materializes the object result into context
 * +0x18. If param_2 < 0 it faults (SoftwareBreakpoint 0xdc6e8). */
void xrt_conclave_init(uint64_t asid, long mode)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    void *state;
    xrt_result_t r;
    uint64_t local[3];

    state = xrt_pmm_state();
    if (state == 0) {
        xrt_panic((void *)"init(conclaveId:asid", 0x16, 2, 0x14);
    }
    ctx->d0 = (uint64_t)state;
    if (mode >= 0) {
        local[0] = asid & 0xffff;
        local[1] = 1;
        local[2] = (uint64_t)mode;
        xrt_dispatch_28(xrt_dispatch(), (uint64_t)state, local);
        xrt_phase_1();
        xrt_dummy_dce2c();
        xrt_dummy_dce18();
        xrt_phase_2();
        r = xrt_obj_result((uint64_t)ctx->d0);
        *(xrt_result_t *)((uint8_t *)&ctx->d1) = r;   /* +0x18 */
        return;
    }
    /* mode < 0: fault */
    __builtin_trap();   /* SoftwareBreakpoint(1, 0xdc6e8) */
}

/* FUN_000dc744 @ 0xdc744 — wrapper: run the no-op FUN_000dce50, capture a log
 * result, then run the generic init (FUN_000dc774). */
uint64_t xrt_744(void)
{
    uint64_t res;
    xrt_dummy_dce50();
    res = xrt_log((void *)0, 0, 0);
    xrt_generic_init();
    return res;
}

/* FUN_000dc774 @ 0xdc774 — generic XRT init. Panics "init()" (0x5c3f20,
 * len 6, kind 2, code 0x29) if the PMM state is absent; otherwise stores the
 * state into context +0x10, runs the per-object init (FUN_000dcd1c), advances
 * two boot phases, and materializes the object result into context +0x18. */
void xrt_generic_init(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    void *state;
    xrt_result_t r;

    state = xrt_pmm_state();
    if (state == 0) {
        xrt_panic((void *)"init()", 6, 2, 0x29);
    }
    ctx->d0 = (uint64_t)state;
    xrt_dispatch_28_fixed((uint64_t)state);
    xrt_phase_1();
    xrt_dummy_dce2c();
    xrt_dummy_dce18();
    xrt_phase_2();
    r = xrt_obj_result((uint64_t)ctx->d0);
    *(xrt_result_t *)((uint8_t *)&ctx->d1) = r;   /* +0x18 */
    return;
}

/* FUN_000dc7f4 @ 0xdc7f4 — teardown/check: resolve the context object via
 * FUN_000dcd78; if absent, destroy it (FUN_004b23d8) and return; otherwise
 * run the teardown chain (FUN_000dce60, FUN_000dcdf4, FUN_000dce40) which
 * faults. */
void xrt_check_dc7f4(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    void *obj;

    obj = (void *)0;   /* result of FUN_000dcd78(*(ctx+0x10)) */
    if (obj == 0) {
        /* FUN_004b23d8: destroy the object */
        xrt_release((void *)0);
        return;
    }
    xrt_dummy_dce60();
    xrt_fatal_error2();
    xrt_fatal_dce40();   /* FUN_000dce40 -> FUN_001afa84, noreturn */
    __builtin_trap();   /* SoftwareBreakpoint(1, 0xdc840) */
}

/* FUN_000dc860 @ 0xdc860 — free a capability. Validates the name length
 * (faults if > 0xff), resolves the cap via FUN_000dcdac with kind 2 (or 0 if
 * param_3&1 == 0), frees the 8-byte capability word via FUN_0036a804, and
 * returns the freed cap value. On resolution failure it panics with
 * "Could not free cap" (0x5c3f70). */
uint64_t xrt_cap_free(uint64_t a, uint64_t name, uint64_t flags)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    uint64_t uVar7, uVar1, len, res;
    uint64_t *cap;
    int kind;

    uVar7 = (uint64_t)&ctx->d1;   /* +0x18 */
    uVar1 = (uint64_t)&ctx->d2;   /* +0x20 */
    len = xrt_strlen_check(name);
    if (len > 0xff) {
        __builtin_trap();   /* SoftwareBreakpoint(1, 0xdc91c) */
    }
    kind = 2;
    if ((flags & 1) == 0) {
        kind = 0;
    }
    res = (uint64_t)xrt_call_ptr;   /* FUN_000dcdac(uVar7,uVar1,len,a,kind) */
    if (res == 0) {
        cap = (uint64_t *)xrt_alloc(8, 0xffffffffffffffffull);
        xrt_call_vt18(uVar7, uVar1, a, (uint64_t)cap);   /* FUN_000dcdc0 */
        uVar7 = *cap;
        xrt_release(cap);
        return uVar7;
    }
    xrt_fatal_error2();   /* s_Could_not_free_cap_005c3f70 */
    xrt_fatal_dce40();
    __builtin_trap();   /* SoftwareBreakpoint(1, 0xdc940) */
}

/* FUN_000dc974 @ 0xdc974 — resolve and release a resource: call
 * FUN_000dcdd4 on the context slots +0x18/+0x20 with the resource handle; if
 * it succeeds, return; otherwise run the teardown chain and fault. */
void xrt_release_res(void *handle)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    void *res;

    res = (void *)0;   /* result of FUN_000dcdd4(&ctx->d1,&ctx->d2,handle) */
    if (res == 0) {
        return;
    }
    xrt_dummy_dce60();
    xrt_fatal_error2();
    xrt_fatal_dce40();
    __builtin_trap();   /* SoftwareBreakpoint(1, 0xdc9b8) */
}

/* FUN_000dc9b8 @ 0xdc9b8 — panic helper: emits "Cannot allocate resource
 * with pm" (0x5c3f90+0x10) then faults. */
void xrt_cannot_alloc_resource(void)
{
    xrt_fatal_error2();   /* s_Cannot_allocate_resource_with_pm_005c3f90 + 0x10 */
    xrt_fatal_dce40();
    __builtin_trap();   /* SoftwareBreakpoint(1, 0xdc9f4) */
}

/* FUN_000dc9f4 @ 0xdc9f4 — panic helper: emits "getIrqCap unimplemented"
 * (0x5c3fc0) then faults. */
void xrt_get_irq_cap_unimpl(void)
{
    xrt_fatal_error2();   /* s_getIrqCap_unimplemented_005c3fc0 */
    xrt_fatal_dce40();
    __builtin_trap();   /* SoftwareBreakpoint(1, 0xdca30) */
}

/* FUN_000dca30 @ 0xdca30 — allocate an untyped cap. Calls the context
 * vtable slot +0x58 to obtain an untyped range; if it returns status==0,
 * panics with "allocUntyped unimplemented" (0x5c3fe0); otherwise resolves the
 * range via FUN_000dcdc0, advances two boot phases, and stack-canary-checks. */
void xrt_alloc_untyped(void *handle)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    xrt_result_t r;
    uint64_t local_30;
    long local_28;

    local_28 = (long)XRT_CANARY;
    local_30 = 0;
    r = ((xrt_result_t (*)(void))(*(void **)(ctx->vtable + 0x58)))();
    if (r.status == 0) {
        xrt_fatal_error2();   /* s_allocUntyped_unimplemented_005c3fe0 */
        xrt_fatal_dce40();
        __builtin_trap();   /* SoftwareBreakpoint(1, 0xdcb00) */
    }
    xrt_call_vt18(r.data, r.status, (uint64_t)handle, local_30);   /* FUN_000dcdc0 */
    xrt_phase_1();
    xrt_dummy_dce2c();
    xrt_dummy_dce18();
    xrt_phase_2();
    if (local_28 == (long)XRT_CANARY) {
        return;
    }
    xrt_canary_fail(local_30);
}

/* FUN_000dcb00 @ 0xdcb00 — panic helper: emits "Couldn't get PMM reference"
 * (0x5c4000) then faults. */
void xrt_no_pmm_ref(void)
{
    xrt_fatal_error2();   /* s_Couldn_t_get_PMM_reference_005c4000 */
    xrt_fatal_dce40();
    __builtin_trap();   /* SoftwareBreakpoint(1, 0xdcb3c) */
}

/* FUN_000dce40 @ 0xdce40 — noreturn fault trampoline (calls FUN_001afa84). */
void xrt_fatal_dce40(void)
{
    xrt_fatal();   /* FUN_001afa84, noreturn */
}

/* FUN_000dce74 @ 0xdce74 — wrapper: capture a log result, then run the
 * page-table/DART resource init (FUN_000dd414) with six arguments. */
uint64_t xrt_ce74(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    uint64_t res;
    res = xrt_log((void *)0, 0, 0);
    xrt_pt_dart_init(a, b, c, d, e, f);
    return res;
}

/* FUN_000dcf1c @ 0xdcf1c — copy the entire context object's field block
 * (from +0x28 through +0x130) plus the mode byte into a 0x24-word result
 * array. This snapshots the boot-capability descriptor for the caller.
 * `param_1` receives the 0x24 (36) 64-bit words. */
void xrt_copy_ctx(uint64_t *param_1)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    uint64_t *src;
    uint64_t extra;

    src = (uint64_t *)((uint64_t)&ctx->d2 + 8);   /* +0x28 */
    for (int i = 0; i < 0x20; i++) {
        param_1[i] = src[i];
    }
    /* +0x20/+0x21 from context +0x20 and the mode byte */
    param_1[0x20] = (uint64_t)&ctx->d2;   /* +0x20 */
    param_1[0x21] = (uint64_t)&ctx->mode; /* +0x90, or 0 if mode == -1 */
    param_1[0x22] = src[0x20];            /* +0x128 */
    param_1[0x23] = src[0x21];            /* +0x130 */
    return;
}

/* FUN_000dcfa4 @ 0xdcfa4 — build an XRT capability object from two source
 * objects: store src into context +0x10, materialize the primary descriptor
 * (kind 0xd) via the PMM vtable slot +0x1b8, then if a second object exists
 * at src+0x20 materialize its descriptor (kind 0xe) into context +0x58..; if
 * no second object, mark context mode = 0xff and zero the secondary block. */
void xrt_build_cap2(void *src, void **pmm)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    void *src2;
    void *matfn;
    uint64_t local[2];

    ctx->d0 = (uint64_t)src;
    matfn = *(void **)(*(uint64_t *)(uint64_t)pmm + 0x1b8);
    xrt_retain((void *)0);
    ((void (*)(void *, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))
        matfn)(&local, 0xd, 0, 0, 0xffffffffffffffffull, 0);
    if (/* unaff_x21 == 0 */ 1) {
        /* copy primary descriptor words into ctx +0x18..+0x40 */
        uint64_t *d = (uint64_t *)&ctx->d1;
        uint64_t *s = (uint64_t *)&local;
        for (int i = 0; i < 4; i++) d[i] = s[i];
        ctx->d5 = 0;
        ctx->d4 = 0;
        src2 = *(void **)(*(void **)((uint64_t)src + 0x18) + 0x70);
        xrt_retain(src2);
        ((void (*)(void *))src2)(&local);
        xrt_release(src2);
        src2 = *(void **)((uint64_t)src + 0x20);
        if (src2 == 0) {
            xrt_release(src);
            xrt_release(pmm);
            ctx->d7 = 0;   /* +0x58..+0x88 zeroed */
            ctx->d8 = 0;
            ctx->d9 = 0;
            ctx->d10 = 0;
            ctx->d11 = 0;
            ctx->d12 = 0;
            ctx->d13 = 0;
            ctx->mode = 0xff;
        } else {
            xrt_retain(src2);
            ((void (*)(void *, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))
                matfn)(&local, 0xe, 0, 0, 0xffffffffffffffffull, 0);
            uint64_t *d = (uint64_t *)&ctx->d7;   /* +0x58 */
            uint64_t *s = (uint64_t *)&local;
            for (int i = 0; i < 4; i++) d[i] = s[i];
            ctx->d11 = 0;
            ctx->d10 = 0;
            ((void (*)(void *))src2)(&local);
            xrt_release(src);
            xrt_release(pmm);
            xrt_release(src2);
        }
    } else {
        xrt_release(src);
        xrt_release(pmm);
        xrt_release((void *)ctx->d0);
        xrt_epilogue();
    }
    return;
}

/* FUN_000dd20c @ 0xdd20c — boot logging: prints a "Brokered, cond, index:"
 * header (0x646572656b6f7242/0xe900000000000028), runs FUN_000dd75c, prints a
 * comma/index/exception header (0x2065646f6e63202c/0xef203a7865646e69), invokes
 * a boot function, and prints a {0xd00000000000001a, 0x5c4040} error pair.
 * If the context mode byte (+0x90) is -1 returns {0xe400000000000000,
 * 0x656e6f6e}; otherwise returns the invoked function's result. Stack canary
 * checked. */
xrt_result_t xrt_bootlog(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    void *fn;
    xrt_result_t r;

    xrt_event_log(0x39);
    xrt_printf(0x646572656b6f7242ull, 0xe900000000000028ull, 0, 0, 0, 0, 0, 0);
    xrt_bootlog_inner();   /* FUN_000dd75c */
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x2065646f6e63202cull, 0xef203a7865646e69ull, 0, 0, 0, 0, 0, 0);
    fn = xrt_getfn(XRT_ADDR_671df8);
    ((void (*)(uint64_t, uint64_t))fn)(XRT_ADDR_677830, XRT_ADDR_671df8);
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0xd00000000000001aull, 0x80000000005c4040ull, 0, 0, 0, 0, 0, 0);
    if (ctx->mode == 0xff) {
        r.data   = 0x656e6f6e;
        r.status = 0xe400000000000000ull;
        return r;
    } else {
        return ((xrt_result_t (*)(uint64_t, uint64_t))fn)(XRT_ADDR_677830, XRT_ADDR_671df8);
    }
}

/* FUN_000dd414 @ 0xdd414 — page-table / DART resource init. Scopes the stack
 * (FUN_000fdd78); if the scope kind is 1, logs the page-table error
 * {0xd00000000000001c, 0x5c4060} and returns. Otherwise stores the resource
 * ids (param_3/param_4) into context +0x10/+0x14, copies a 0x100-byte boot
 * block into context +0x28, stores param_5/param_6 into +0x128/+0x130,
 * resolves the primary/secondary resources (FUN_0006d580/FUN_0006d5c8),
 * materializes them, and on failure prints a "{dis:...di ;}" error and returns
 * {0xd000000000000014, 0x5c4080}. Stack canary checked. */
void xrt_pt_dart_init(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    unsigned char scope[0x100];
    void *p1, *p2;
    uint64_t u;
    int kind;

    xrt_scope_init(scope);
    kind = xrt_scope_kind(scope);
    if (kind == 1) {
        xrt_print_word(b);
        xrt_err_str();
        /* result {0xd00000000000001c, 0x5c4060}, kind 2 */
        *(volatile uint64_t *)0 = 0xd00000000000001cull;
        *(volatile uint64_t *)0 = 0x80000000005c4060ull;
        return;
    }
    *(int *)&ctx->d0 = (int)c;             /* +0x10 */
    *(int *)((uint8_t *)&ctx->d0 + 4) = (int)d;  /* +0x14 */
    xrt_block_copy((void *)((uint64_t)&ctx->d2 + 8), scope, 0x100);   /* +0x28 */
    *(uint64_t *)((uint8_t *)&ctx->d8) = e;    /* +0x128 (approx) */
    *(uint64_t *)((uint8_t *)&ctx->d8 + 8) = f;/* +0x130 (approx) */
    p1 = xrt_resolve((void *)c, (void *)d);
    if (p1 != 0) {
        xrt_print_word(b);
        xrt_lookup_1000();
        u = xrt_materialize((uint64_t)p1);
        if (/* unaff_x21 == 0 */ 1) {
            *(uint64_t *)&ctx->d1 = u;   /* +0x18 */
            p2 = xrt_resolve2((void *)c, (void *)d);
            if (p2 != 0) {
                u = xrt_materialize(0);
                *(uint64_t *)((uint8_t *)&ctx->d2) = u;   /* +0x20 */
                xrt_commit2(*(unsigned int *)&ctx->d0, *(unsigned int *)((uint8_t *)&ctx->d0 + 4));
                return;
            }
            *(uint64_t *)((uint8_t *)&ctx->d2) = 0;   /* +0x20 = 0 */
            return;
        }
        goto epilogue;
    }
    xrt_event_log(0x28);
    xrt_print_word(0xe000000000000000ull);
    xrt_printf(a, b, 0, 0, 0, 0, 0, 0);
    xrt_print_word(b);
    xrt_printf(0x203a6469737b20ull, 0xe700000000000000ull, 0, 0, 0, 0, 0, 0);
    {
        void *fn = xrt_getfn(XRT_ADDR_671298);
        ((void (*)(uint64_t, uint64_t))fn)(XRT_ADDR_6776f0, XRT_ADDR_671298);
    }
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x203a6469203bull, 0xe600000000000000ull, 0, 0, 0, 0, 0, 0);
    {
        void *fn = xrt_getfn(XRT_ADDR_671298);
        ((void (*)(uint64_t, uint64_t))fn)(XRT_ADDR_6776f0, XRT_ADDR_671298);
    }
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x7d, 0xe100000000000000ull, 0, 0, 0, 0, 0, 0);
    xrt_err_str();
    /* result {0xd000000000000014, 0x5c4080}, kind 1 */
    *(volatile uint64_t *)0 = 0xd000000000000014ull;
    *(volatile uint64_t *)0 = 0x80000000005c4080ull;
epilogue:
    xrt_epilogue();
    return;
}

/* FUN_000dd6c8 @ 0xdd6c8 — build a second boot object: log class 0x651370
 * (len 0x91, kind 7), retain two objects, call FUN_000dcfa4, and on success
 * store {param_1[0]=result, param_1[3]=0x651370, param_1[4]=0x661540}. */
void xrt_build_obj2(uint64_t *param_1)
{
    uint64_t uVar1;

    xrt_log((void *)0x651370, 0x91, 7);
    xrt_retain((void *)0);
    xrt_retain((void *)0);
    uVar1 = (uint64_t)xrt_build_cap2;   /* FUN_000dcfa4() */
    if (/* unaff_x21 == 0 */ 1) {
        param_1[3] = 0x651370;
        param_1[4] = 0x661540;
        param_1[0] = uVar1;
    }
    return;
}

/* FUN_000dd75c @ 0xdd75c — boot logging helper (called from FUN_000dd20c):
 * prints the "{d:...}" capability descriptor (0xd000000000000019/0x5c40a0),
 * copies the full context field block into a 0x100-byte buffer, formats and
 * prints "di: 0x...", "dis: 0x...", " vm ba:0x...", " vm si:0x..." values
 * (from context +0x128/+0x130), and stack-canary-checks. */
void xrt_bootlog_inner(void)
{
    xrt_ctx_t *ctx = (xrt_ctx_t *)0;   /* unaff_x20 context */
    uint64_t buf[0x21];
    long canary;

    canary = (long)XRT_CANARY;
    buf[0] = 0;
    buf[1] = 0xe000000000000000ull;
    xrt_event_log(0x4a);
    xrt_printf(0xd000000000000019ull, 0x80000000005c40a0ull, 0, 0, 0, 0, 0, 0);
    {
        uint64_t *src = (uint64_t *)((uint64_t)&ctx->d2);   /* +0x28 */
        for (int i = 0; i < 0x20; i++) buf[i] = src[i];
    }
    buf[0x20] = (uint64_t)&ctx->d8;   /* +0x128 (approx) */
    xrt_fmt(buf);
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x203a6469202cull, 0xe600000000000000ull, 0, 0, 0, 0, 0, 0);
    {
        void *fn = xrt_getfn(XRT_ADDR_671298);
        ((void (*)(uint64_t, uint64_t))fn)(XRT_ADDR_6776f0, XRT_ADDR_671298);
    }
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x203a646973202cull, 0xe700000000000000ull, 0, 0, 0, 0, 0, 0);
    {
        void *fn = xrt_getfn(XRT_ADDR_671298);
        ((void (*)(uint64_t, uint64_t))fn)(XRT_ADDR_6776f0, XRT_ADDR_671298);
    }
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x736162206d76202cull, 0xed00007830203a65ull, 0, 0, 0, 0, 0, 0);
    xrt_fmt_pre();
    xrt_fmt_raw();
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x7a6973206d76202cull, 0xec00000078302065ull, 0, 0, 0, 0, 0, 0);
    xrt_fmt_raw();
    xrt_printf(0, 0, 0, 0, 0, 0, 0, 0);
    xrt_print_word(0);
    xrt_printf(0x29, 0xe100000000000000ull, 0, 0, 0, 0, 0, 0);
    if (canary == (long)XRT_CANARY) {
        return;
    }
    xrt_canary_fail(0);
}
