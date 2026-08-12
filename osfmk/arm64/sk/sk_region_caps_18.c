/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 18: 0x80000-0x100000 caps region (exclave-launcher bring-up: the
 * InternalExclaveLauncher Mach-O loader, VAS-extension page-table builder,
 * CNode allocation and device-tree memory setup).
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

typedef unsigned long ulong;

/* ------------------------------------------------------------------ *
 * Out-of-slice cL4 helper declarations (declared extern with a one-line
 * note; bodies reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_0036a940 @ 0x36a940 — allocate zeroed memory of `size` bytes (tag 7).
 * Used throughout the launcher to size table objects (count*elsize+0x20). */
extern unsigned long cL4_alloc_tag7(unsigned long size);
/* FUN_0036b118 @ 0x36b118 — release/dereference a kernel object or table. */
extern void cL4_release_ref(void *obj);
/* FUN_0036b270 @ 0x36b270 — acquire/retain a reference on an object. */
extern void cL4_retain_ref(void *obj);
/* FUN_0036b6f4 @ 0x36b6f4 — error-path unwind: drop pending refs / roll back. */
extern void cL4_unwind(void);
/* FUN_0036b6ac @ 0x36b6ac — unlock / release an object lock. */
extern void cL4_unlock_obj(void);
/* FUN_0036b21c @ 0x36b21c — release object(s) held in a frame. */
extern void cL4_release_frame(void);
/* FUN_000026e8 @ 0x26e8 — scope exit: drop a held reference / TCB scope. */
extern void cL4_scope_exit(void *scope);
/* FUN_000027e8 @ 0x27e8 — scope enter (guard). */
extern void cL4_scope_enter(void);
/* FUN_00002834 @ 0x2834 — scope enter variant (with a tag; decompiler
 * sometimes drops it). */
extern void cL4_scope_enter_tag(unsigned long tag);
/* FUN_000e46b4 @ 0xe46b4 (thunk 0x126e8) — clear/zero-initialize a table. */
extern void cL4_table_clear(void);
/* FUN_000e4674 @ 0xe4674 — invoke the object at a vtable slot. */
extern void cL4_vtable_invoke(void);
/* FUN_000777d4 @ 0x777d4 — release/dispatch helper used by launcher ops. */
extern void cL4_op_release(void);
/* FUN_00077770 @ 0x77770 — deregister/release a tagged object. */
extern void cL4_deregister(void *tag);
/* FUN_000836a4 @ 0x836a4 — lookup/resolve an object from a table by key. */
extern unsigned long cL4_table_lookup(void *table, long key);
/* FUN_0006e7c0 @ 0x6e7c0 — capture the current execution context/scope. */
extern void cL4_capture(void *out);
/* FUN_00077024 @ 0x77024 — begin a context/iteration capture. */
extern unsigned long cL4_iter_begin(void *out);
/* FUN_00077070 @ 0x77070 — advance an iteration / collect a result pair. */
extern void cL4_iter_pair(void *a, void *b);
/* FUN_0006a4c0 @ 0x6a4c0 — invoke with (context, value) pair. */
extern void cL4_invoke_pair(void *ctx, unsigned long v);
/* FUN_00365b6c @ 0x365b6c — compare two strings/type names; 0 when equal. */
extern long cL4_str_eq(unsigned long *out, unsigned long *in, unsigned long a, unsigned long b, int n);
/* FUN_0036a9d4 @ 0x36a9d4 — resolve/allocate a name-to-object mapping. */
extern unsigned long cL4_name_resolve(unsigned long base, unsigned long name);
/* FUN_0036a940 @ 0x36a940 — (see above) generic allocation helper. */
/* FUN_00002534 @ 0x2534 — load a string/type descriptor (addr, dat). */
extern unsigned long cL4_type_desc(unsigned long addr, unsigned long dat);
/* FUN_001404e0 @ 0x1404e0 — return a static launcher string constant. */
extern unsigned long cL4_str_a(void);
/* FUN_00141948 @ 0x141948 — return a static launcher string constant. */
extern unsigned long cL4_str_b(void);
/* FUN_000a6fe0 @ 0xa6fe0 — panic on invalid (zero) size argument. */
extern void cL4_panic_bad_size(void);
/* FUN_0008e328 @ 0x8e328 — launcher dispatch-prep helper. */
extern void cL4_dispatch_prep(void);
/* FUN_0036a9d4 @ 0x36a9d4 — (see above). */
/* FUN_00377824 @ 0x377824 — query root table geometry (rows/cols). */
extern unsigned long cL4_geom_rows(void *t, unsigned long a, unsigned long b, unsigned long *x, unsigned long *y);
/* FUN_00377bec @ 0x377bec — query root table geometry variant. */
extern unsigned long cL4_geom_cols(unsigned long a, unsigned long b, unsigned long r, unsigned long *x, void *y);
/* FUN_0014aedc @ 0x14aedc — page-table slot count for geometry. */
extern unsigned long cL4_pt_slots(unsigned long a, unsigned long b);
/* FUN_0014aea4 @ 0x14aea4 — page-table per-level stride
 * (decompiler sometimes drops an arg — variadic). */
extern unsigned long cL4_pt_stride(unsigned long a, ...);
/* FUN_0007eb2c @ 0x7eb2c — total page-table bytes for geometry. */
extern unsigned long cL4_pt_bytes(unsigned long a, unsigned long b);
/* FUN_0014aedc @ 0x14aedc — see above. */
/* FUN_0014aea4 @ 0x14aea4 — see above. */
/* FUN_00149ba0 @ 0x149ba0 — PT init count helper. */
extern void cL4_pt_init(void *x);
/* FUN_0014935c @ 0x14935c — PT entry count helper. */
extern unsigned long cL4_pt_count(void);
/* FUN_00117d14 @ 0x117d14 — install a PT/region descriptor at a VA range. */
extern void cL4_pt_install(unsigned long base, unsigned long off, long len);
/* FUN_000f7fe0 @ 0xf7fe0 — allocator: next free frame size. */
extern unsigned long cL4_phys_next(void);
/* FUN_000f7ff8 @ 0xf7ff8 — allocator: commit a frame range. */
extern void cL4_phys_commit(unsigned long a, unsigned long b);
/* FUN_000f81d4 @ 0xf81d4 — allocator: reserve frames for a region. */
extern unsigned long cL4_phys_reserve(unsigned long a);
/* FUN_000f8dc8 @ 0xf8dc8 — allocator: region allocator query. */
extern unsigned long cL4_phys_alloc_region(void);
/* FUN_000ff914 @ 0xff914 — allocate a physical region of `size`. */
extern unsigned long cL4_phys_alloc_region_sz(unsigned long size, void *ctx, void *tag);
/* FUN_000fd334 @ 0xfd334 — map a physical region to a VA. */
extern unsigned long cL4_phys_map(unsigned long a, unsigned long b, unsigned long size, long v);
/* FUN_000fd854 @ 0xfd854 — map frame/region variant. */
extern unsigned long cL4_phys_map2(unsigned long a, unsigned long b);
/* FUN_001000b8 @ 0x1000b8 — VA region allocator query. */
extern unsigned long cL4_va_alloc(void);
/* FUN_001003e8 @ 0x1003e8 — VA region allocator query. */
extern unsigned long cL4_va_alloc2(void);
/* FUN_00085a54 @ 0x85a54 — allocate an object descriptor (type tag). */
extern void *cL4_obj_desc(void *ctx, unsigned long size, unsigned long type, unsigned long flags, unsigned long x, void *tag);
/* FUN_00086440 @ 0x86440 — PT descriptor base query. */
extern unsigned long cL4_pt_desc_base(void);
/* FUN_00086590 @ 0x86590 — PT descriptor alloc query. */
extern unsigned long cL4_pt_desc_alloc(void);
/* FUN_00034f70 @ 0x34f70 — phys allocator: allocate one frame. */
extern unsigned long cL4_phys_frame_alloc(void);
/* FUN_000fb9c4 @ 0xfb9c4 — map one allocated frame. */
extern void cL4_phys_frame_map(void);
/* FUN_00100484 @ 0x100484 — VA commit for a mapped frame. */
extern void cL4_va_frame_commit(void);
/* FUN_004b23d8 @ 0x4b23d8 — phys allocator: register an allocated frame. */
extern void cL4_phys_frame_register(unsigned long f);
/* FUN_0006b79c @ 0x6b79c — device-tree: memory size query. */
extern unsigned long cL4_dt_mem_size(void);
/* FUN_0006cf50 @ 0x6cf50 — device-tree: untyped region list. */
extern unsigned long cL4_dt_untyped(void);
/* FUN_0006d024 @ 0x6d024 — device-tree: reserved region size. */
extern unsigned long cL4_dt_reserved(unsigned long r);
/* FUN_0006b7ac @ 0x6b7ac — device-tree: free region base. */
extern unsigned long cL4_dt_free_base(void);
/* FUN_000aa3ac @ 0xaa3ac — emit an error frame (returns the frame). */
extern unsigned long *cL4_error_frame(void);
/* FUN_0036986c @ 0x36986c — propagate a stored error frame. */
extern void cL4_propagate_error(void);
/* FUN_002a4ab4 @ 0x2a4ab4 — begin a formatted (printf-style) log frame. */
extern void cL4_log_begin(unsigned long tag);
/* FUN_003a25d4 @ 0x3a25d4 — log a value into the format frame
 * (decompiler sometimes drops the arg — variadic). */
extern void cL4_log_val(unsigned long v, ...);
/* thunk_FUN_002acbb8 @ 0x2acbb8 — log a (tag,value) pair into the frame
 * (decompiler sometimes drops the args — variadic). */
extern void cL4_log_pair(unsigned long a, ...);
/* FUN_00027724 @ 0x27724 — log a header/location string. */
extern void *cL4_log_str(unsigned long a);
/* FUN_001afa84 @ 0x1afa84 — noreturn fatal-error printer (format, len, ...). */
extern void cL4_fatal(const char *fmt, unsigned long len, int x, ...);
/* FUN_00294bdc @ 0x294bdc — panic-print with a string argument. */
extern void cL4_panic_str(const char *s, unsigned long n, int x);
/* FUN_001ebfb0 @ 0x1ebfb0 — log a hex field into the frame. */
extern void cL4_log_hex(void *buf, unsigned long n, int x, unsigned long a, unsigned long b);
/* FUN_001e790 @ 0x1e790 — log an address/pointer field. */
extern void cL4_log_ptr(void);
/* FUN_000e710c @ 0xe710c — write the launcher magic/guard word. */
extern void cL4_launcher_magic(void);
/* FUN_000e46a4 @ 0xe46a4 — return a fixed (frame,16) log tag. */
extern void cL4_log_tag16(void);
/* FUN_000e72b0 @ 0xe72b0 — no-op marker. */
extern void cL4_noop(void);
/* FUN_0006a4c0 @ 0x6a4c0 — see above. */
/* FUN_00077118 @ 0x77118 — object dispatch: resolve vtable for a key. */
extern void *cL4_obj_dispatch(unsigned long key);
/* FUN_0026b434 @ 0x26b434 — misc internal initializer. */
extern void cL4_internal_init(void);
/* FUN_001dd858 @ 0x1dd858 — invoke release on a referenced object. */
extern void cL4_invoke_release(unsigned long obj);
/* FUN_0036a940 @ 0x36a940 — (see above). */
/* FUN_0036b6ac @ 0x36b6ac — (see above). */
/* FUN_003a25d4 @ 0x3a25d4 — (see above). */
/* FUN_0036b21c @ 0x36b21c — (see above). */
/* FUN_00205844 @ 0x205844 — log a compound field (name, ...). */
extern void cL4_log_field(void *a, void *b, unsigned long c, unsigned long d, unsigned long e);
/* FUN_000e72d4 @ 0xe72d4 — log terminator pair. */
extern void cL4_log_term(void);
/* FUN_000e7288 @ 0xe7288 — log "frame: " label. */
extern void cL4_log_framelabel(void);
/* FUN_000e72bc @ 0xe72bc — log a label with 0x prefix. */
extern void cL4_log_label(unsigned long v);
/* FUN_000e72e0 @ 0xe72e0 — log a section label. */
extern void cL4_log_section(unsigned long v);
/* FUN_000b430c @ 0xb430c — dispatch a type-name printer. */
extern void cL4_type_printer(unsigned long v);
/* FUN_000e710c @ 0xe710c — (see above). */
/* FUN_0036a940 @ 0x36a940 — (see above). */
/* FUN_000fdb98 @ 0xfdb98 — register/install a built descriptor. */
extern void cL4_desc_install(void *d);
/* FUN_00157308 @ 0x157308 — PT entry kind validation (returns kind). */
extern unsigned long cL4_pt_kind(unsigned long v);
/* FUN_0009d398 @ 0x9d398 — PT entry: write level descriptor. */
extern void cL4_pt_wr_level(void *e, unsigned long v);
/* FUN_0009d3a8 @ 0x9d3a8 — PT entry: next marker. */
extern void cL4_pt_marker(void);
/* FUN_0009d3b8 @ 0x9d3b8 — PT entry: clear marker. */
extern void cL4_pt_clear(void);
/* FUN_0009d3c8 @ 0x9d3c8 — PT entry: set address field. */
extern void cL4_pt_set_addr(void *e, unsigned long v);
/* FUN_0009d3d8 @ 0x9d3d8 — PT entry: set flags byte. */
extern void cL4_pt_set_flags(void *e, unsigned long v);
/* FUN_0009d3e8 @ 0x9d3e8 — PT entry: set second descriptor. */
extern void cL4_pt_set_desc2(void *e, unsigned long v);
/* FUN_0009d3f0 @ 0x9d3f0 — PT entry: set third descriptor. */
extern void cL4_pt_set_desc3(void *e, unsigned long v);
/* FUN_0009d370 @ 0x9d370 — PT entry: set kind field. */
extern void cL4_pt_set_kind(void *e, unsigned long v);
/* FUN_0009d378 @ 0x9d378 — PT entry: clear kind marker. */
extern void cL4_pt_clr_kind(void);
/* FUN_0009d380 @ 0x9d380 — PT entry: set level bit. */
extern void cL4_pt_set_level(void *e, unsigned long v);
/* FUN_0005597c @ 0x5597c — PT entry: set depth/count. */
extern void cL4_pt_set_depth(void *e, unsigned long v);
/* FUN_0009d360 @ 0x9d360 — PT entry: set total-size field. */
extern void cL4_pt_set_size(void *e, unsigned long v);
/* FUN_0001c294 @ 0x1c294 — check a flag bit in a word (returns 0/1). */
extern unsigned long cL4_flag_bit(unsigned long v, int shift);
/* FUN_0036a940 @ 0x36a940 — (see above). */
/* FUN_0036a9d4 @ 0x36a9d4 — (see above). */
/* FUN_0006a4c0 @ 0x6a4c0 — (see above). */
/* FUN_0036993c @ 0x36993c — log/attach a named field. */
extern void cL4_log_named(unsigned long a, unsigned long b, int c, int d);
/* FUN_0036b270 @ 0x36b270 — (see above). */
/* FUN_000826a4 @ 0x826a4 — grow a table to a new capacity. */
extern void cL4_table_grow(bool keep, unsigned long cap, int tag);
/* FUN_000826e4 @ 0x826e4 — grow variant. */
extern void cL4_table_grow2(void);
/* FUN_00082484 @ 0x82484 — table op helper. */
extern void cL4_table_op(void);
/* FUN_00082784 @ 0x82784 — table op helper 2. */
extern void cL4_table_op2(void);
/* FUN_00082764 @ 0x82764 — table op helper 3. */
extern void cL4_table_op3(void);
/* FUN_000826a4 @ 0x826a4 — (see above). */
/* FUN_000e55a8 @ 0xe55a8 — push a (pair) entry onto a collector stack. */
extern void cL4_collect_push(void);

/* Global: the launcher root table descriptor. */
extern unsigned long cL4_launcher_root;  /* _DAT_00657778 */

/* FUN_000e2fc4 @ 0xe2fc4 — finish/commit a Mach-O section record. */
extern void FUN_000e2fc4(unsigned long r);
/* FUN_000db6e8 @ 0xdb6e8 — resolve an object dispatch entry; returns a
 * function pointer that is called with (obj, arg). */
extern unsigned long (*FUN_000db6e8(unsigned long arg))(long, unsigned long);

/* --- In-slice forward declarations (mutually-referencing functions) --- */
void FUN_000e37ec(long rec, unsigned long p2);
void FUN_000e3ce8(long count, void (*elem_op)(unsigned long, long, int));
long FUN_000e3eb4(long count, unsigned long name, unsigned long dat);
void FUN_000e4694(long size, long elemsz);
void FUN_000e4a7c(unsigned long *out);
void FUN_000e4a94(long obj, long *factory);
cl4_result_t FUN_000e4bf4(void);
unsigned long *FUN_000e4d48(unsigned long p1, unsigned long p2, long p3, long p4, unsigned long p5, unsigned long p6);
void FUN_000e4d00(void);
void FUN_000e4d24(void);
void FUN_000e5294(unsigned long *out, unsigned long p2);
cl4_result_t FUN_000e5328(void);
void FUN_000e5508(void);
void FUN_000e55fc(unsigned long *out);
void FUN_000e5614(long obj, long *factory, unsigned long flag);
cl4_result_t FUN_000e57bc(void);
void FUN_000e58cc(void);
void FUN_000e58a8(void);
void FUN_000e5afc(unsigned long *out, unsigned long flag);
cl4_result_t FUN_000e5b98(void);
void FUN_000e5ae0(unsigned long p1);
void FUN_000e5ac4(unsigned long p1);
void FUN_000e62a8(void);
void FUN_000e6538(long frame, unsigned long p2, unsigned long p3, unsigned long p4);
cl4_result_t FUN_000e6b88(void);
unsigned long FUN_000e6a9c(void);
void FUN_000e710c(void);
cl4_result_t FUN_000e7264(void);
void FUN_000e72b0(void);
void FUN_000e72bc(unsigned long v);
void FUN_000e72d4(void);
void FUN_000e72e0(unsigned long v);
void FUN_000e734c(unsigned long *out);
void FUN_000e7360(unsigned long p1, long *factory);
cl4_result_t FUN_000e74cc(void);
void FUN_000e75cc(void);
void FUN_000e75f0(void);
void FUN_000e7614(long region, unsigned long size);
void FUN_000e77e0(unsigned long *out, unsigned long p2);
cl4_result_t FUN_000e7874(void);
void FUN_000e795c(void);
void FUN_000e7960(void);
cl4_result_t FUN_000e46a4(void);
void FUN_000e46b4(void);
void FUN_000e46d8(void);
void FUN_000e46ec(void);
long FUN_000e40c0(ulong p);
long FUN_000e40f0(ulong p);
long FUN_000e4120(ulong p);
long FUN_000e4150(ulong p);
long FUN_000e6138(ulong p);
unsigned long FUN_000e4700(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5, unsigned long p6);
unsigned long *FUN_000e4788(long arr);
unsigned long FUN_000e55bc(void);
cl4_result_t FUN_000e5c4c(void);
cl4_result_t FUN_000e54b8(void);
cl4_result_t FUN_000e54c8(void);
long FUN_000e4180(unsigned long p1, long out, long obj, unsigned long p4);

/* ------------------------------------------------------------------ *
 * Small leaf helpers (in-slice).
 * ------------------------------------------------------------------ */

/* FUN_000e4674 @ 0xe4674 — invoke a captured context pair. */
void FUN_000e4674(void)
{
    cL4_invoke_pair(0, 0);  /* FUN_0006a4c0 */
}

/* FUN_000e46a4 @ 0xe46a4 — return fixed log tag (frame, 16). */
cl4_result_t FUN_000e46a4(void)
{
    cl4_result_t r;
    r.hi = 0x10;
    r.lo = (uintptr_t)0x8;  /* &stack_0x8 — a small inline value */
    return r;
}

/* FUN_000e46b4 @ 0xe46b4 — clear the current table. */
void FUN_000e46b4(void)
{
    cL4_table_clear();  /* thunk_FUN_000126e8 */
}

/* FUN_000e46d0 @ 0xe46d0 — no-op marker. */
void FUN_000e46d0(void)
{
    return;
}

/* FUN_000e46d8 @ 0xe46d8 — release the object referenced by *frame+0x10. */
void FUN_000e46d8(void)
{
    cL4_invoke_release(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x18 + 0x10));
}

/* FUN_000e46ec @ 0xe46ec — table op on the empty list. */
void FUN_000e46ec(void)
{
    cL4_table_op();  /* FUN_00082484 */
}

/* ------------------------------------------------------------------ *
 * Tagged list-index helpers: given an (optionally tagged) head pointer,
 * untag it and compute the address of the element at `off` plus the
 * signed 32-bit delta stored there — the standard cL4 intrusive-list
 * "next/end" computation.  Each helper uses a different offset (the
 * field differs per list object type).
 * ------------------------------------------------------------------ */

/* FUN_000e40c0 @ 0xe40c0 — list index at offset 0x14. */
long FUN_000e40c0(ulong p)
{
    if (p & 1) p = *(ulong *)(p & ~1ull);
    return (long)(p + 0x14) + (long)*(int *)(p + 0x14);
}

/* FUN_000e40f0 @ 0xe40f0 — list index at offset 0x8. */
long FUN_000e40f0(ulong p)
{
    if (p & 1) p = *(ulong *)(p & ~1ull);
    return (long)(p + 8) + (long)*(int *)(p + 8);
}

/* FUN_000e4120 @ 0xe4120 — list index at offset 0x10. */
long FUN_000e4120(ulong p)
{
    if (p & 1) p = *(ulong *)(p & ~1ull);
    return (long)(p + 0x10) + (long)*(int *)(p + 0x10);
}

/* FUN_000e4150 @ 0xe4150 — list index at offset 0xc. */
long FUN_000e4150(ulong p)
{
    if (p & 1) p = *(ulong *)(p & ~1ull);
    return (long)(p + 0xc) + (long)*(int *)(p + 0xc);
}

/* FUN_000e6138 @ 0xe6138 — list index at offset 0x20. */
long FUN_000e6138(ulong p)
{
    if (p & 1) p = *(ulong *)(p & ~1ull);
    return (long)(p + 0x20) + (long)*(int *)(p + 0x20);
}

/* ------------------------------------------------------------------ *
 * Launcher object-record builders.  Each allocates a table object, fills
 * its descriptor fields via a captured context, and stores {descriptor,
 * type-name, vtable} triple into the caller's frame.
 * ------------------------------------------------------------------ */

/* FUN_000e3440 @ 0xe3440 — build a launcher version record: resolve the
 * kernel count field (tagged/untagged), look up the matching descriptor,
 * and store {descriptor, type-name, string} triple into *out. */
void FUN_000e3440(unsigned long *out)
{
    ulong cnt = *(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18);
    unsigned long d;
    unsigned long s;
    if ((long)cnt < 0) {
        cnt &= 0x7fffffffffffffff;
        d = cL4_str_b();           /* FUN_00141948 */
        s = 0x665098;
    } else {
        d = cL4_str_a();           /* FUN_001404e0 */
        s = 0x664f58;
    }
    unsigned long v = cL4_alloc_tag7(*(unsigned long *)(cnt + 0x10));
    out[3] = d;
    out[4] = s;
    out[0] = v;
}

/* FUN_000e34c4 @ 0xe34c4 — build a launcher record of the 0x40-kind;
 * dispatches through vtable+0x48, runs table op 0x40f0, releases. */
cl4_result_t FUN_000e34c4(void)
{
    cl4_result_t r = {0, 0};
    cL4_scope_enter();
    cL4_vtable_invoke();          /* (**(code**)(x16+0x48))(frame) */
    FUN_000e4674();
    FUN_000e40c0(0);              /* arg dropped by decompiler */
    cL4_op_release();             /* FUN_000777d4 */
    r.lo = (unsigned long)cL4_op_release;  /* (*extraout_x8)() — callee result */
    cL4_scope_exit(0);
    return r;
}

/* FUN_000e3540 @ 0xe3540 — build a launcher record of the 0x40f0-kind. */
cl4_result_t FUN_000e3540(void)
{
    cl4_result_t r = {0, 0};
    cL4_scope_enter();
    cL4_vtable_invoke();
    FUN_000e4674();
    FUN_000e40f0(0);
    cL4_op_release();
    r.lo = (unsigned long)cL4_op_release;
    cL4_scope_exit(0);
    return r;
}

/* FUN_000e362c @ 0xe362c — build a launcher record of the 0x4150-kind;
 * if the result is negative, trap with a software breakpoint. */
long FUN_000e362c(void)
{
    long r;
    cL4_scope_enter();
    cL4_vtable_invoke();
    FUN_000e4674();
    FUN_000e4150(0);
    cL4_op_release();
    r = (long)(cl4_result_t){0, 0}.lo;
    if (r >= 0) {
        cL4_scope_exit(0);
        return r;
    }
    __builtin_trap();  /* SoftwareBreakpoint(1, 0xe36a8) */
}

/* FUN_000e36c0 @ 0xe36c0 — run a launcher callback over a resolved object,
 * passing its descriptor to `fn`; releases on the way out. */
unsigned long FUN_000e36c0(long obj, void (*fn)(void *))
{
    long t = *(long *)(obj + 0x18);
    unsigned long v = cL4_table_lookup((void *)obj, t);
    cL4_release_ref(*(void **)(*(long *)(t - 8) + 0x40));
    fn((void *)v);
    cL4_scope_exit((void *)obj);
    return v;
}

/* FUN_000e37a0 @ 0xe37a0 — scope-tag enter then build a record; wraps
 * FUN_000e37ec. */
unsigned long FUN_000e37a0(unsigned long p1, unsigned long p2)
{
    unsigned long r;
    cL4_scope_enter_tag(0);
    r = cL4_alloc_tag7(0);
    FUN_000e37ec(p1, p2);
    return r;
}

/* FUN_000e37ec @ 0xe37ec — write {type-name, count} into the record and
 * resolve the table descriptor. */
void FUN_000e37ec(long rec, unsigned long p2)
{
    unsigned long cnt = *(ulong *)(rec + 0x18);
    *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x10) = p2;
    cL4_retain_ref((void *)(cnt & 0x7fffffffffffffff));
    cL4_release_ref((void *)rec);
    *(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18) = cnt;
}

/* FUN_000e3834 @ 0xe3834 — resolve a table entry keyed by the launcher's
 * count, dispatching through the +0x88 (tagged) or +0x50 (untagged) slot;
 * releases the count reference before returning. */
unsigned long FUN_000e3834(unsigned long key)
{
    ulong cnt = *(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18);
    unsigned long r;
    cL4_dispatch_prep();
    if ((long)cnt < 0) {
        cnt &= 0x7fffffffffffffff;
        cL4_retain_ref((void *)cnt);
        r = ((unsigned long (*)(unsigned long))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x88)))(key);
    } else {
        cL4_retain_ref((void *)cnt);
        r = ((unsigned long (*)(unsigned long))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x50)))(key);
    }
    cL4_release_ref((void *)cnt);
    return r;
}

/* FUN_000e38f0 @ 0xe38f0 — dispatch a launcher record keyed by the count:
 * tagged count -> vtable+0x90 slot; untagged -> vtable+0x48 slot; retains
 * the count around the dispatch and releases it after. */
unsigned long FUN_000e38f0(void)
{
    ulong cnt = *(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18);
    unsigned long r;
    cL4_scope_enter();
    if ((long)cnt < 0) {
        cL4_retain_ref((void *)(cnt & 0x7fffffffffffffff));
        r = ((unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x90)))();
        cL4_release_ref((void *)(cnt & 0x7fffffffffffffff));
    } else {
        cL4_retain_ref((void *)cnt);
        r = ((unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x48)))();
        cL4_release_ref((void *)cnt);
    }
    return r;
}

/* FUN_000e39a8 @ 0xe39a8 — build a launcher record with a series of
 * labeled fields (addr, size, flags) resolved from the object dispatch
 * table; returns the completed {lo,hi} pair. */
cl4_result_t FUN_000e39a8(void)
{
    cl4_result_t r = {0, 0xe000000000000000ull};
    cL4_log_begin(0x46);
    cL4_log_pair(0xd000000000000017ull, 0x80000000005c4490ull);
    cL4_vtable_invoke();                 /* (**(code**)(*x20+0x50))() */
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x4174726976203b22ull, 0xee0078303a726464ull); /* "; vit", "ddr:0x.." */
    cL4_log_ptr();
    FUN_000e46a4();
    cL4_log_hex(0, 0, 0, 0, 0);          /* FUN_001ebfb0 */
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x657a69736d76203bull, 0xeb0000000078303aull); /* "; vm size:0x.." */
    r.lo = (unsigned long)(*(void **)(0x58));  /* (**(code**)(*x20+0x58))() */
    FUN_000e46a4();
    cL4_log_hex(0, 0, 0, 0, 0);
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x73656d617266203bull, 0xed0000203a706143ull); /* "; frame", "Cap: .." */
    cL4_vtable_invoke();                 /* (**(code**)(*x20+0x48))(&frame) */
    cL4_invoke_pair((void *)&r.lo, r.lo);
    FUN_000e4150(0);
    cL4_scope_exit(&r.lo);
    cL4_log_pair(0x7dull, 0xe100000000000000ull);
    return r;
}

/* ------------------------------------------------------------------ *
 * Table-allocation constructors: each reserves a count*elsize+0x20 sized
 * table object and sets its capacity metadata.
 * ------------------------------------------------------------------ */

/* FUN_000e3c04 @ 0xe3c04 — release the launcher's tagged count reference. */
void FUN_000e3c04(void)
{
    cL4_release_ref((void *)(*(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18) & 0x7fffffffffffffff));
}

/* FUN_000e3c08 @ 0xe3c08 — same as 0xe3c04 (separate thunk). */
void FUN_000e3c08(void)
{
    cL4_release_ref((void *)(*(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18) & 0x7fffffffffffffff));
}

/* FUN_000e3c28 @ 0xe3c28 — release the tagged count and unlock the object. */
void FUN_000e3c28(void)
{
    cL4_release_ref((void *)(*(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18) & 0x7fffffffffffffff));
    cL4_scope_enter_tag(0);
    cL4_unlock_obj();
}

/* FUN_000e3c2c @ 0xe3c2c — same as 0xe3c28 (separate thunk). */
void FUN_000e3c2c(void)
{
    cL4_release_ref((void *)(*(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18) & 0x7fffffffffffffff));
    cL4_scope_enter_tag(0);
    cL4_unlock_obj();
}

/* FUN_000e3c54 @ 0xe3c54 — scope-enter then dispatch through vtable+0x90. */
void FUN_000e3c54(void)
{
    cL4_scope_enter();
    ((void (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x90)))();
}

/* FUN_000e3ca0 @ 0xe3ca0 — build a table with element size from 0x82484. */
void FUN_000e3ca0(unsigned long p1)
{
    FUN_000e3ce8(p1, (void (*)(unsigned long, long, int))cL4_table_op);
}

/* FUN_000e3cb8 @ 0xe3cb8 — build a table with element size from 0x826e4. */
void FUN_000e3cb8(unsigned long p1)
{
    FUN_000e3ce8(p1, (void (*)(unsigned long, long, int))cL4_table_grow2);
}

/* FUN_000e3cd0 @ 0xe3cd0 — build a table with element size from 0x82784. */
void FUN_000e3cd0(unsigned long p1)
{
    FUN_000e3ce8(p1, (void (*)(unsigned long, long, int))cL4_table_op2);
}

/* FUN_000e3ce8 @ 0xe3ce8 — common table-constructor: ensure the requested
 * count fits in the launcher table (doubling as needed), then dispatch the
 * element-op through the caller's jumptable. */
void FUN_000e3ce8(long count, void (*elem_op)(unsigned long, long, int))
{
    long tab = (long)cL4_launcher_root;
    unsigned long used = cL4_alloc_tag7(tab);
    cL4_retain_ref((void *)tab);
    if (used != 0 && count <= (long)(*(ulong *)(tab + 0x18) >> 1)) {
        return;
    }
    long cap = *(long *)(tab + 0x10);
    if (*(long *)(tab + 0x10) <= count) {
        cap = count;
    }
    elem_op(used, cap, 0);  /* UNRECOVERED_JUMPTABLE — indirect dispatch */
}

/* FUN_000e3d6c @ 0xe3d6c — allocate a table of count*0x10+0x20 entries. */
long FUN_000e3d6c(long count)
{
    if (count < 1) {
        cL4_panic_bad_size();
    } else {
        cL4_alloc_tag7(cL4_type_desc(0x64e110, 0x4c05b0));
        cL4_alloc_tag7(count * 0x10 + 0x20);
        FUN_000e46b4();
        FUN_000e4694(0, 0);
    }
    return count;
}

/* FUN_000e3dd0 @ 0xe3dd0 — allocate a table of count*0x40+0x20 entries. */
long FUN_000e3dd0(long count)
{
    if (count < 1) {
        cL4_panic_bad_size();
    } else {
        cL4_alloc_tag7(cL4_type_desc(0x64e760, 0x4c05b8));
        cL4_alloc_tag7(count << 6 | 0x20);
        FUN_000e46b4();
        FUN_000e4694(0, 0);
    }
    return count;
}

/* FUN_000e3e34 @ 0xe3e34 — allocate a table of count*0x48+0x20 entries and
 * set its length/capacity metadata. */
long FUN_000e3e34(long count)
{
    if (count < 1) {
        cL4_panic_bad_size();
    } else {
        cL4_alloc_tag7(cL4_type_desc(0x64e758, 0x4c2e90));
        cL4_alloc_tag7(count * 0x48 + 0x20);
        FUN_000e46b4();
        *(unsigned long *)(count + 0x10) = 0;
        *(long *)(count + 0x18) = (count / 0x48) << 1;
    }
    return count;
}

/* FUN_000e3ea0 @ 0xe3ea0 — allocate a count*8+0x20 pointer table. */
void FUN_000e3ea0(unsigned long p1)
{
    FUN_000e3eb4(p1, 0x64e6d8, 0x4c2e80);
}

/* FUN_000e3eb4 @ 0xe3eb4 — common pointer-table constructor. */
long FUN_000e3eb4(long count, unsigned long name, unsigned long dat)
{
    if (count < 1) {
        cL4_panic_bad_size();
    } else {
        cL4_alloc_tag7(cL4_type_desc(name, dat));
        cL4_alloc_tag7(count * 8 + 0x20);
        FUN_000e46b4();
        FUN_000e4694(0, 0);
    }
    return count;
}

/* FUN_000e3f10 @ 0xe3f10 — allocate a table of count*0x28+0x20 entries. */
long FUN_000e3f10(long count)
{
    if (count < 1) {
        cL4_panic_bad_size();
    } else {
        cL4_alloc_tag7(cL4_type_desc(0x64e770, 0x4c2ea0));
        cL4_alloc_tag7(count * 0x28 + 0x20);
        FUN_000e46b4();
        *(unsigned long *)(count + 0x10) = 0;
        *(long *)(count + 0x18) = (count / 0x28) << 1;
    }
    return count;
}

/* FUN_000e3f7c @ 0xe3f7c — build a record by resolving a table entry and
 * running FUN_000e4180 over it; releases references in both paths. */
unsigned long FUN_000e3f7c(unsigned long p1, unsigned long p2, long obj, unsigned long p4)
{
    long t = *(long *)(obj - 8);
    cL4_release_ref(*(void **)(t + 0x40));
    cL4_scope_enter_tag(0x651838);
    unsigned long v = cL4_alloc_tag7(0);
    v = FUN_000e4180(v, v, obj, p4);
    ((void (*)(unsigned long, long))(*(void **)(t + 8)))(p1, obj);
    return v;
}

/* FUN_000e4078 @ 0xe4078 — deregister the 0x651838 table. */
void FUN_000e4078(void)
{
    cL4_deregister((void *)0x651838);
}

/* FUN_000e4084 @ 0xe4084 — release a launcher record's refs (type, values). */
void FUN_000e4084(void)
{
    cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x10));
    cL4_log_val(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20));
    cL4_log_val(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x40));
    cL4_release_frame();
}

/* FUN_000e4088 @ 0xe4088 — same as 0xe4084 (separate thunk). */
void FUN_000e4088(void)
{
    cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x10));
    cL4_log_val(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20));
    cL4_log_val(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x40));
    cL4_release_frame();
}

/* FUN_000e4180 @ 0xe4180 — resolve a (frame, type) pair into a launcher
 * record; on failure logs a fatal Mach-O loader error and panics. */
long FUN_000e4180(unsigned long p1, long out, long obj, unsigned long p4)
{
    unsigned long result;
    unsigned long rec;

    cL4_capture((void *)((uintptr_t)__builtin_frame_address(0) - 0x68));
    ((void (*)(unsigned long, unsigned long, long))(*(void **)(*(long *)(obj - 8) + 0x20)))(0, p1, obj);
    cL4_invoke_pair((void *)((uintptr_t)__builtin_frame_address(0) - 0x68), 0);
    unsigned long a = cL4_type_desc(0x6502a8, 0x4c1920);
    unsigned long b = cL4_str_a();
    long i = cL4_str_eq((unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x98),
                        (unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90), a, b, 6);
    if (i == 0) {
        cL4_invoke_pair((void *)((uintptr_t)__builtin_frame_address(0) - 0x68), 0);
        b = cL4_str_b();
        result = cL4_str_eq((unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x98),
                            (unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90), a, b, 6);
        if ((result & 1) == 0) {
            cl4_result_t er = {0, 0xe000000000000000ull};
            cL4_log_begin(0x16);
            cL4_log_pair(0xd000000000000014ull, 0x80000000005c2010ull);
            cL4_log_field(0, &er, a, 0x6756a8, 0x66e1b8);  /* FUN_00205844 */
            cL4_fatal("Fatal error", 0xb, 2, er.lo, er.hi,
                      "InternalExclaveLauncher Macho.swift", 0x23, 2, 0xd9, 0);
        }
        rec = cL4_alloc_tag7(0x651788);
        FUN_000e2fc4(result);
        rec |= 0x8000000000000000ull;
    } else {
        rec = cL4_alloc_tag7(0x651718);
        *(unsigned long *)(rec + 0x10) = result;
    }
    *(ulong *)(out + 0x18) = rec;
    *(unsigned long *)(out + 0x10) = FUN_000db6e8(p4)(obj, p4);  /* FUN_000db6e8 */
    cL4_scope_exit(0);
    return out;
}

/* FUN_000e4534 @ 0xe4534 — deregister the 0x651718 table. */
void FUN_000e4534(void)
{
    cL4_deregister((void *)0x651718);
}

/* FUN_000e4540 @ 0xe4540 — deregister the 0x651788 table. */
void FUN_000e4540(void)
{
    cL4_deregister((void *)0x651788);
}

/* FUN_000e4614 @ 0xe4614 — resolve a type descriptor and dispatch it. */
unsigned long FUN_000e4614(unsigned long p1)
{
    long d = cL4_type_desc(0x6518d0, 0x4c2e88);
    ((void (*)(unsigned long, long))(*(void **)(*(long *)(d - 8) + 8)))(p1, d);
    return p1;
}

/* FUN_000e4694 @ 0xe4694 — set a table's length metadata (cap = cnt<<1). */
void FUN_000e4694(long size, long elemsz)
{
    long cap = 0;
    if (elemsz != 0) {
        cap = size / elemsz;
    }
    *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x10) = 0;
    *(long *)((uintptr_t)__builtin_frame_address(0) + 0x18) = cap << 1;
}

/* FUN_000e4700 @ 0xe4700 — build a VAS-extension record (wrapper for
 * FUN_000e4d48); allocates a result slot then fills it. */
unsigned long FUN_000e4700(unsigned long p1, unsigned long p2, unsigned long p3,
                           unsigned long p4, unsigned long p5, unsigned long p6)
{
    unsigned long r = cL4_alloc_tag7(0);
    FUN_000e4d48(p1, p2, p3, p4, p5, p6);
    return r;
}

/* FUN_000e4788 @ 0xe4788 — build a collector list from the entries of an
 * array; for each entry captures a (name,desc) pair and appends it to the
 * launcher root list, growing the list as needed. (medium; fixed: the
 * FUN_0006e7c0 capture now passes both (arr, out) args per decompile.) */
unsigned long *FUN_000e4788(long arr)
{
    unsigned long *list = (unsigned long *)&cL4_launcher_root;
    long n = *(long *)(arr + 0x10);
    if (n != 0) {
        unsigned long *cur = (unsigned long *)&cL4_launcher_root;
        cL4_table_grow(0, n, 0);
        arr += 0x20;
        do {
            /* FUN_0006e7c0(arr, out): capture the current array slot into
             * the frame. The shared extern is declared 1-arg; call the real
             * 2-arg function with both decompile args. */
            ((void (*)(long, void *))cL4_capture)(arr,
                (void *)((uintptr_t)__builtin_frame_address(0) - 0xb8));
            cL4_iter_pair((void *)((uintptr_t)__builtin_frame_address(0) - 0xb8),
                          (void *)((uintptr_t)__builtin_frame_address(0) - 0xe0));
            unsigned long a = cL4_type_desc(0x64e740, 0x4c0590);
            unsigned long b = cL4_type_desc(0x64e8b8, 0x4c0710);
            cL4_str_eq((unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90),
                       (unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0xe0), a, b, 7);
            unsigned long used = *(ulong *)(list + 0x10);
            if (*(ulong *)(list + 0x18) >> 1 <= used) {
                cL4_table_grow(1 < *(ulong *)(list + 0x18), used + 1, 1);
            }
            *(ulong *)(list + 0x10) = used + 1;
            cL4_iter_pair((void *)((uintptr_t)__builtin_frame_address(0) - 0x90),
                          (void *)((char *)list + used * 0x28 + 0x20));
            arr += 0x28;
            n--;
        } while (n != 0);
    }
    return list;
}

/* ------------------------------------------------------------------ *
 * Collector loops.
 * ------------------------------------------------------------------ */

/* FUN_000e48c4 @ 0xe48c4 — collect entries of an array (0x6519c0/0x64e718
 * type pair) into the launcher list until the list is full. */
unsigned long *FUN_000e48c4(long arr)
{
    unsigned long *list = (unsigned long *)&cL4_launcher_root;
    if (*(long *)(arr + 0x10) != 0) {
        unsigned long x = 0;
        cL4_table_op3();
        do {
            cL4_collect_push();
            cL4_retain_ref((void *)x);
            x = cL4_type_desc(0x6519c0, 0x4c2f58);
            cL4_type_desc(0x64e718, 0x4c2f60);
            cL4_log_term();
            cL4_log_val(0);
            cL4_table_op2();
            list = (unsigned long *)cL4_launcher_root;
        } while (0);
    }
    return list;
}

/* FUN_000e49a0 @ 0xe49a0 — collect entries of an array (0x6519b8/0x64e700
 * type pair) into the launcher list. */
unsigned long *FUN_000e49a0(long arr)
{
    unsigned long *list = (unsigned long *)&cL4_launcher_root;
    if (*(long *)(arr + 0x10) != 0) {
        unsigned long x = 0;
        cL4_table_op3();
        do {
            cL4_collect_push();
            cL4_retain_ref((void *)x);
            x = cL4_type_desc(0x6519b8, 0x4c2f48);
            cL4_type_desc(0x64e700, 0x4c0550);
            cL4_log_term();
            cL4_log_val(0);
            cL4_table_op2();
            list = (unsigned long *)cL4_launcher_root;
        } while (0);
    }
    return list;
}

/* FUN_000e4a7c @ 0xe4a7c — copy the record's {addr, size, flags} triple
 * out of the launcher frame into *param_1. */
void FUN_000e4a7c(unsigned long *out)
{
    unsigned long flags = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20);
    unsigned long obj = *(long *)((uintptr_t)__builtin_frame_address(0) + 0x10);
    out[1] = *(unsigned long *)(obj + 0x28);
    out[0] = *(unsigned long *)(obj + 0x20);
    out[2] = flags;
}

/* FUN_000e4a94 @ 0xe4a94 — build a launcher record by invoking the object
 * factory (vtable+0x1b8) with a fresh descriptor of size 8; stores the
 * produced {lo..hi} descriptor fields and installs it. */
void FUN_000e4a94(long obj, long *factory)
{
    long cnt = *(long *)(obj + 0x10);
    if (cnt < 0) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0xe4bf4) */
    }
    unsigned long v = *(unsigned long *)(*(long *)(obj + 0x18) + 0x40);
    void (*make)(void *, unsigned long, unsigned long, long, int, int) =
        *(void **)(*factory + 0x1b8);
    cL4_retain_ref(0);
    make((void *)((uintptr_t)__builtin_frame_address(0) - 0x90), 8, v, cnt, 0, 0);
    if (0 == 0) {  /* unaff_x21 == 0 (success path) */
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x78);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x18) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x30) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x88);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x28) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x80);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x40) = (unsigned long)(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x99));
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x38) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x38);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x49) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x49);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x41) = (unsigned long)(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x41));
        unsigned long o2 = *(unsigned long *)(*(long *)((uintptr_t)__builtin_frame_address(0) + 0x10) + 0x18);
        cL4_retain_ref((void *)o2);
        cL4_desc_install((void *)((uintptr_t)__builtin_frame_address(0) - 0x90));
        cL4_release_ref((void *)o2);
        cL4_release_ref((void *)obj);
        cL4_release_ref(factory);
    } else {
        cL4_release_ref((void *)obj);
        cL4_release_ref(factory);
        cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x10));
        cL4_unwind();
    }
}

/* FUN_000e4bf4 @ 0xe4bf4 — produce a "Brokered c-node index: ..." error
 * frame (fatal path helper). */
cl4_result_t FUN_000e4bf4(void)
{
    cl4_result_t r;
    cL4_log_begin(0x1d);
    cL4_log_val(0xe000000000000000ull);
    cL4_log_str(0);
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x2065646f6e63202cull, 0xef203a7865646e69ull); /* ", cnode", "index: .." */
    cL4_log_str(0x671df8);
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x29ull, 0xe100000000000000ull);
    r.hi = 0xe900000000000028ull;
    r.lo = 0x646572656b6f7242ull;  /* "Brokered" */
    return r;
}

/* FUN_000e4d00 @ 0xe4d00 — copy record triple (thunk of 0xe4a7c). */
void FUN_000e4d00(void)
{
    FUN_000e4a7c(0);
}

/* FUN_000e4d24 @ 0xe4d24 — Brokered c-node error (thunk of 0xe4bf4). */
void FUN_000e4d24(void)
{
    FUN_000e4bf4();
}

/* FUN_000e4d48 @ 0xe4d48 — VAS-extension builder: allocate a physical
 * region of (param_5/2 - param_4) size plus a 16K alignment pad, install
 * a page-table descriptor, and map `lVar6` frames in 16K steps; on any
 * frame-allocation failure logs a fatal phys-allocator error and panics. */
unsigned long *FUN_000e4d48(unsigned long p1, unsigned long p2, long p3, long p4,
                            unsigned long p5, unsigned long p6)
{
    unsigned long *frame = (unsigned long *)cL4_launcher_root;
    unsigned long r = (unsigned long)FUN_000e4788(p6);
    cL4_release_ref((void *)p6);
    unsigned long reg = cL4_phys_alloc_region();
    cL4_alloc_tag7(reg);
    r = cL4_phys_reserve(r);
    if (0 == 0) {  /* unaff_x21 == 0 (success) */
        long l6 = (long)(p5 >> 1) - p4;
        if (__builtin_sub_overflow((long)(p5 >> 1), p4, &l6)) {
            __builtin_trap();  /* SBORROW */
        }
        unsigned long next = cL4_phys_next();
        if (__builtin_add_overflow(l6, (long)next, &(long){0})) {
            __builtin_trap();  /* SCARRY */
        }
        unsigned long total = (unsigned long)(l6 + (long)next) + 0x3fff;
        unsigned long aligned = total & 0xffffffffffffc000ull;
        frame[2] = aligned;
        if ((long)total < 0) {
            __builtin_trap();
        }
        cL4_capture((void *)p1);
        unsigned long va = cL4_va_alloc2();
        cL4_alloc_tag7(va);
        va = cL4_phys_alloc_region_sz(aligned, (void *)p1, (void *)va);
        frame[3] = va;
        unsigned long n = frame[2];
        unsigned long d = cL4_pt_desc_base();
        cl4_result_t dr = {cL4_name_resolve(d, 0x64e1c0), 0x65f998};
        unsigned long dt = cL4_pt_desc_alloc();
        cL4_alloc_tag7(dt);
        unsigned long *desc = cL4_obj_desc(&dr, n, 0x11, 0x1808, 0, (void *)dt);
        unsigned long cap = frame[2];
        unsigned long off = 0;
        for (unsigned long i = 0; cap / 0x4000 != i; i++) {
            unsigned long f = cL4_phys_frame_alloc();
            if (f == 0) {
                cl4_result_t er = {0, 0xe000000000000000ull};
                cL4_log_begin(0x1e);
                cL4_log_val(er.hi);
                er.lo = 0xd000000000000017ull;
                er.hi = 0x80000000005c03b0ull;
                cL4_panic_str("init_physAllocator graphData del", 0x31, 2);
                cL4_log_pair(0);
                cL4_log_val(0);
                cL4_log_pair(0x203a20ull, 0xe300000000000000ull);
                cL4_log_str(0x671df8);
                cL4_log_pair(0);
                cL4_log_val(0);
                cL4_fatal("Fatal error", 0xb, 2, er.lo, er.hi,
                          "InternalExclaveLauncher VASExtension.swift", 0x2a, 2, 0x6f, 0);
            }
            cL4_retain_ref(0);
            FUN_000e5508();  /* args dropped by decompiler */
            cL4_phys_frame_map();
            ((void (*)(unsigned long, unsigned long))(*(void **)(*desc + 0x90)))(off, f);
            FUN_000e5508();  /* args dropped by decompiler */
            cL4_va_frame_commit();
            cL4_phys_frame_register(f);
            off += 0x4000;
        }
        if (l6 < 0) {
            __builtin_trap();
        }
        unsigned long base = ((unsigned long (*)(void))(*(void **)(*desc + 0xe0)))();
        if (base == 0) {
            __builtin_trap();
        }
        cL4_pt_install(base, p3 + p4, l6);
        base = ((unsigned long (*)(void))(*(void **)(*desc + 0xe0)))();
        if (base == 0) {
            __builtin_trap();
        }
        unsigned long end = cL4_phys_next();
        if ((long)end < 0) {
            __builtin_trap();
        }
        cL4_phys_commit(base + l6, base + l6 + end);
        cL4_scope_exit((void *)p1);
        cL4_release_ref((void *)p2);
        cL4_release_ref(desc);
        frame[4] = (unsigned long)l6;
        l6 = (long)cL4_phys_next();
        cL4_release_ref((void *)r);
        if (l6 < 0) {
            __builtin_trap();
        }
        frame[5] = (unsigned long)l6;
    } else {
        cL4_scope_exit((void *)p1);
        cL4_release_ref((void *)p2);
        cL4_unwind();
    }
    return frame;
}

/* FUN_000e5294 @ 0xe5294 — build a device-tree region record; fills
 * {type-name, vtable, descriptor} triple via FUN_000e4a94. */
void FUN_000e5294(unsigned long *out, unsigned long p2)
{
    cl4_result_t name = FUN_000e54b8();      /* {0x651968, 0} */
    cL4_alloc_tag7(0x51);
    cL4_retain_ref(0);
    cL4_retain_ref((void *)p2);
    FUN_000e4a94(0, 0);
    if (0 == 0) {
        out[3] = name.lo;
        out[4] = 0x661bc8;
        out[0] = 0;  /* residual value in x0 from 0xe4a94 (void) */
    }
}

/* FUN_000e5328 @ 0xe5328 — produce a VAS-extension error frame. */
cl4_result_t FUN_000e5328(void)
{
    cl4_result_t r;
    cL4_log_begin(0x31);
    cL4_log_val(0xe000000000000000ull);
    cL4_log_str(0x671848);
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0xd000000000000010ull, 0x80000000005c4680ull);
    cL4_log_str(0x671848);
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x29ull, 0xe100000000000000ull);
    r.hi = 0x80000000005c4660ull;
    r.lo = 0xd00000000000001cull;
    return r;
}

/* FUN_000e5448 @ 0xe5448 — release a VAS record's ref and unlock. */
void FUN_000e5448(void)
{
    cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x18));
    cL4_unlock_obj();
}

/* FUN_000e544c @ 0xe544c — same as 0xe5448 (separate thunk). */
void FUN_000e544c(void)
{
    cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x18));
    cL4_unlock_obj();
}

/* FUN_000e5474 @ 0xe5474 — device-tree region record (thunk of 0xe5294). */
void FUN_000e5474(void)
{
    FUN_000e5294(0, 0);
}

/* FUN_000e5478 @ 0xe5478 — device-tree region record (thunk of 0xe5294). */
void FUN_000e5478(void)
{
    FUN_000e5294(0, 0);
}

/* FUN_000e548c @ 0xe548c — VAS-extension error (thunk of 0xe5328). */
void FUN_000e548c(void)
{
    FUN_000e5328();
}

/* FUN_000e54b8 @ 0xe54b8 — return a fixed type descriptor pointer. */
cl4_result_t FUN_000e54b8(void)
{
    cl4_result_t r;
    r.lo = 0x651968;
    r.hi = 0;
    return r;
}

/* FUN_000e54c8 @ 0xe54c8 — return a fixed type descriptor pointer. */
cl4_result_t FUN_000e54c8(void)
{
    cl4_result_t r;
    r.lo = 0x6518f0;
    r.hi = 0;
    return r;
}

/* FUN_000e5508 @ 0xe5508 — no-op marker. */
void FUN_000e5508(void)
{
    return;
}

/* FUN_000e5530 @ 0xe5530 — return 0 (empty collector state). */
unsigned long FUN_000e5530(void)
{
    return 0;
}

/* FUN_000e554c @ 0xe554c — append a 16-byte {lo,hi} entry to a collector
 * table at slot x27, recording the current x25 key. */
void FUN_000e554c(cl4_result_t entry)
{
    *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x10) = 0;
    unsigned long *slot = (unsigned long *)((uintptr_t)__builtin_frame_address(0) + (0) * 0x10);
    slot[2] = entry.hi;
    slot[3] = entry.lo;
}

/* FUN_000e5564 @ 0xe5564 — return the entry currently on the stack. */
cl4_result_t FUN_000e5564(void)
{
    cl4_result_t r;
    r.lo = 0;
    r.hi = 0;
    return r;
}

/* FUN_000e557c @ 0xe557c — compare the two top-of-stack strings. */
void FUN_000e557c(void)
{
    cL4_str_eq((unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20),
               (unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x10), 0, 0, 0);
}

/* FUN_000e5594 @ 0xe5594 — no-op marker. */
void FUN_000e5594(void)
{
    return;
}

/* FUN_000e55a8 @ 0xe55a8 — push the collector's current key pair and
 * retain the key. */
void FUN_000e55a8(void)
{
    unsigned long *k = (unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x10);
    unsigned long key = *k;
    unsigned long prev = *(k - 1);
    cL4_retain_ref((void *)prev);
}

/* FUN_000e55bc @ 0xe55bc — build a device-tree region record (wrapper for
 * FUN_000e58cc). */
unsigned long FUN_000e55bc(void)
{
    unsigned long r = cL4_alloc_tag7(0);
    FUN_000e58cc();
    return r;
}

/* FUN_000e55fc @ 0xe55fc — copy a VAS record's {addr, size, flags} triple
 * (variant reading +0x18/+0x20). */
void FUN_000e55fc(unsigned long *out)
{
    unsigned long flags = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20);
    unsigned long obj = *(long *)((uintptr_t)__builtin_frame_address(0) + 0x10);
    out[1] = *(unsigned long *)(obj + 0x20);
    out[0] = *(unsigned long *)(obj + 0x18);
    out[2] = flags;
}

/* FUN_000e5614 @ 0xe5614 — build a launcher record from an object factory
 * (vtable+0x1b8), then dispatch the produced descriptor through the
 * mapped region's +0x70 (unmapped) or +0x68 (mapped) slot per `flag`. */
void FUN_000e5614(long obj, long *factory, unsigned long flag)
{
    unsigned long v1 = *(unsigned long *)(obj + 0x18);
    unsigned long v2 = *(unsigned long *)(obj + 0x20);
    void (*make)(void *, unsigned long, unsigned long, unsigned long, unsigned long, int) =
        *(void **)(*factory + 0x1b8);
    cL4_retain_ref(0);
    make((void *)((uintptr_t)__builtin_frame_address(0) - 0xa0), 8, v1, v2, 0xffffffffffffffffull, 0);
    if (0 == 0) {
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x68);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x18) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0xa0);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x30) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x78);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x28) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x70);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x40) = (unsigned long)(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0xa0 + 0x38));
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x38) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0xa0 + 0x38);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x49) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0xa0 + 0x49);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x41) = (unsigned long)(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0xa0 + 0x41));
        long *map = *(long **)(*(long *)((uintptr_t)__builtin_frame_address(0) + 0x10) + 0x10);
        void (*dispatch)(void *) = (flag & 1) == 0
            ? *(void **)(*map + 0x70)   /* unmapped path */
            : *(void **)(*map + 0x68);  /* mapped path */
        cL4_retain_ref(map);
        dispatch((void *)((uintptr_t)__builtin_frame_address(0) - 0xa0));
        cL4_release_ref(map);
        cL4_release_ref(factory);
        cL4_release_ref((void *)obj);
    } else {
        cL4_release_ref((void *)obj);
        cL4_release_ref(factory);
        cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x10));
        cL4_unwind();
    }
}

/* FUN_000e57bc @ 0xe57bc — produce a VAS error frame. */
cl4_result_t FUN_000e57bc(void)
{
    cl4_result_t r;
    cL4_log_begin(0x1d);
    cL4_log_val(0xe000000000000000ull);
    cL4_log_str(0x671df8);
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x29ull, 0xe100000000000000ull);
    r.hi = 0x80000000005c46a0ull;
    r.lo = 0xd00000000000002aull;
    return r;
}

/* FUN_000e5884 @ 0xe5884 — copy VAS triple (thunk of 0xe55fc). */
void FUN_000e5884(void)
{
    FUN_000e55fc(0);
}

/* FUN_000e58a8 @ 0xe58a8 — VAS error frame (thunk of 0xe57bc). */
void FUN_000e58a8(void)
{
    FUN_000e57bc();
}

/* FUN_000e58cc @ 0xe58cc — device-tree memory setup: query total memory
 * and untyped regions; if the device tree is missing or an untyped region
 * is empty, log the corresponding error and build an error frame.
 * (medium; fixed: error paths now store the {code,value,1} triple into the
 * error frame — code 0xd00000000000002a for total==0 vs 0 for untyped/base —
 * before propagating; base!=0/x21!=0 path unwinds via FUN_0036b6f4.) */
void FUN_000e58cc(void)
{
    long total = (long)cL4_dt_mem_size();
    *(long *)((uintptr_t)__builtin_frame_address(0) + 0x18) = total;
    unsigned long code, value;
    if (total == 0) {
        value = 0x80000000005c46d0ull;
        code = 0xd00000000000002aull;
    } else {
        long untyped = (long)cL4_dt_untyped();
        if (untyped == 0) {
            cL4_log_begin(0x43);
            cL4_log_pair(0xd000000000000041ull, (unsigned long)"Missing device tree: could not f..." | 0x8000000000000000ull);
            cL4_log_str(0x671848);
            cL4_log_pair(0);
            cL4_log_val(0);
        } else {
            unsigned long total2 = *(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18);
            unsigned long reserved = cL4_dt_reserved(total2);
            if (total2 < reserved) {
                __builtin_trap();  /* SoftwareBreakpoint(1, 0xe5ac0) */
            }
            *(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x28) = total2 - reserved;
            long base = (long)cL4_dt_free_base();
            if (base < 0) {
                __builtin_trap();  /* SoftwareBreakpoint(1, 0xe5ac4) */
            }
            *(long *)((uintptr_t)__builtin_frame_address(0) + 0x20) = base;
            if (base != 0) {
                unsigned long size = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x28);
                unsigned long va = cL4_va_alloc();
                va = cL4_phys_map(va, untyped, size, base);
                if (0 == 0) {  /* unaff_x21 == 0 (success) */
                    *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x10) = va;
                    return;
                }
                cL4_unwind();  /* FUN_0036b6f4 (LAB_000e5a88): error-path unwind */
                return;
            }
            cL4_log_begin(0x3a);
            cL4_log_pair(0xd000000000000038ull, (unsigned long)"Missing device tree: Empty untyped" | 0x8000000000000000ull);
            cL4_log_str(0x671848);
            cL4_log_pair(0);
            cL4_log_val(0);
        }
        code = 0;
        value = 0xe000000000000000ull;
    }
    /* Shared error tail (total==0 / untyped==0 / base==0): store the
     * {code, value, 1} triple into the error frame, then propagate it
     * (FUN_0036986c). */
    unsigned long *ef = cL4_error_frame();
    ef[0] = code;
    ef[1] = value;
    *((unsigned char *)ef + 2) = 1;
    cL4_propagate_error();
}

/* FUN_000e5ac4 @ 0xe5ac4 — build a mapped region record (flag=1). */
void FUN_000e5ac4(unsigned long p1)
{
    FUN_000e5afc((unsigned long *)p1, 1);
}

/* FUN_000e5ae0 @ 0xe5ae0 — build an unmapped region record (flag=0). */
void FUN_000e5ae0(unsigned long p1)
{
    FUN_000e5afc((unsigned long *)p1, 0);
}

/* FUN_000e5afc @ 0xe5afc — common region-record constructor; fills
 * {type-name, vtable, descriptor} via FUN_000e5614. */
void FUN_000e5afc(unsigned long *out, unsigned long flag)
{
    unsigned long r = cL4_alloc_tag7(0x651a58);
    cL4_retain_ref(0);
    cL4_retain_ref((void *)flag);
    FUN_000e5614(0, 0, 0);
    if (0 == 0) {
        out[3] = 0x651a58;
        out[4] = 0x661bf8;
        out[0] = 0;  /* residual value in x0 from 0xe5614 (void) */
    }
}

/* FUN_000e5b98 @ 0xe5b98 — produce a region error frame. */
cl4_result_t FUN_000e5b98(void)
{
    cl4_result_t r;
    r.hi = 0x80000000004c2f50ull;
    r.lo = 0xd000000000000012ull;
    return r;
}

/* FUN_000e5bb4 @ 0xe5bb4 — unmapped region record (thunk of 0xe5ae0). */
void FUN_000e5bb4(void)
{
    FUN_000e5ae0(0);
}

/* FUN_000e5bb8 @ 0xe5bb8 — unmapped region record (thunk of 0xe5ae0). */
void FUN_000e5bb8(void)
{
    FUN_000e5ae0(0);
}

/* FUN_000e5bcc @ 0xe5bcc — mapped region record (thunk of 0xe5ac4). */
void FUN_000e5bcc(void)
{
    FUN_000e5ac4(0);
}

/* FUN_000e5bd0 @ 0xe5bd0 — mapped region record (thunk of 0xe5ac4). */
void FUN_000e5bd0(void)
{
    FUN_000e5ac4(0);
}

/* FUN_000e5be4 @ 0xe5be4 — region error code (calls 0xe5b98). */
unsigned long FUN_000e5be4(void)
{
    FUN_000e5b98();
    return 0xd000000000000012ull;
}

/* FUN_000e5be8 @ 0xe5be8 — region error code (calls 0xe5b98). */
unsigned long FUN_000e5be8(void)
{
    FUN_000e5b98();
    return 0xd000000000000012ull;
}

/* FUN_000e5c4c @ 0xe5c4c — return a fixed type descriptor pointer. */
cl4_result_t FUN_000e5c4c(void)
{
    cl4_result_t r;
    r.lo = 0x6519e0;
    r.hi = 0;
    return r;
}

/* FUN_000e5c5c @ 0xe5c5c — return a fixed page-table geometry word; the
 * constant encodes the PT entry layout. */
unsigned long FUN_000e5c5c(void)
{
    cL4_retain_ref((void *)0x350001009400ad38ull);
    return 0x350001009400ad38ull;
}

/* FUN_000e6230 @ 0xe6230 — no-op marker. */
void FUN_000e6230(void)
{
    return;
}

/* FUN_000e6260 @ 0xe6260 — fill a launcher record's {name, v1, v2} fields
 * and run the internal initializer. */
void FUN_000e6260(void)
{
    unsigned long *fr = (unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x38);
    fr[0] = 0x6753a0;                     /* +0x38 */
    *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20) = 0;
    *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x28) = 0;
    cL4_internal_init();
}

/* FUN_000e628c @ 0xe628c — store {lo,hi} pair into a record. */
void FUN_000e628c(long rec)
{
    *(unsigned long *)(rec + 0x18) = 0;
    *(unsigned long *)(rec + 0x10) = 0;
}

/* FUN_000e62a8 @ 0xe62a8 — log " mpidr " label. */
void FUN_000e62a8(void)
{
    cL4_log_pair(0x20726469706d20ull, 0xe700000000000000ull);
}

/* FUN_000e62c4 @ 0xe62c4 — log a hex field for the frame. */
void FUN_000e62c4(unsigned long p1)
{
    cL4_log_hex((void *)((uintptr_t)__builtin_frame_address(0) + 0x48), 0x10, 0, 0x677790, p1);
}

/* FUN_000e62e0 @ 0xe62e0 — return a fixed address constant. */
unsigned long FUN_000e62e0(void)
{
    return 0x677880;
}

/* FUN_000e62f8 @ 0xe62f8 — log terminator. */
void FUN_000e62f8(void)
{
    cL4_log_pair(0);
}

/* FUN_000e6304 @ 0xe6304 — init-endpoint verification: compare the root
 * table's slot geometry against the page-table capacity; when the PT is
 * under-committed vs the endpoint requirement, log "Calling Init Endpoint"
 * and invoke the init endpoint (or fatal). */
void FUN_000e6304(void)
{
    unsigned long rows = cL4_geom_rows(0, *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x40),
                                       *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x38),
                                       (unsigned long *)&(unsigned long){0x606a9c}, (unsigned long *)&(unsigned long){0x606ac4});
    unsigned long cols = cL4_geom_cols(rows, 0, 0, (unsigned long *)&(unsigned long){0x606a9c}, (void *)0x606aa4);
    unsigned long slots = cL4_pt_slots(rows, cols);
    unsigned long bytes = cL4_pt_bytes(rows, cols);
    if (bytes == 0) {
        __builtin_trap();
    }
    unsigned long count = (*(unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0xd0)))();
    if (slots < bytes) {
        __builtin_trap();
    }
    unsigned long per = slots / bytes;
    unsigned long have = (*(unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x178)))();
    if (per < have) {
        __builtin_trap();
    }
    unsigned long rem = per ? count / per : 0;
    if (per - have <= count - rem * per || count == rem * per) {
        have = (*(unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x178)))();
        if (0xfffffffffffffffe < have) {
            __builtin_trap();
        }
        for (long i = (long)have + 2; (i -= 1) != 0;) {
            ((void (*)(void *))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x1c0)))(0);
        }
    }
    unsigned long c2 = (*(unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0xd0)))();
    unsigned long h2 = (*(unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x178)))();
    if (h2 <= per) {
        unsigned long per2 = per ? c2 / per : 0;
        if (per - h2 <= c2 - per2 * per) {
            cL4_retain_ref((void *)0x350001009400ad38ull);  /* FUN_000e5c5c */
            cL4_log_pair(0xd00000000000002aull, (unsigned long)"Calling Init Endpoint" | 0x8000000000000000ull);  /* FUN_000e7264 */
            cL4_fatal(0, 0, 0);
        }
        return;
    }
    __builtin_trap();
}

/* FUN_000e6538 @ 0xe6538 — VAS page-table builder: walk the launcher's PT
 * geometry, install level descriptors for each 0x4000-aligned frame, and
 * dispatch each entry's kind (PTE) through the per-kind writer helpers;
 * fills the caller's frame with the completed mapping. */
void FUN_000e6538(long frame, unsigned long p2, unsigned long p3, unsigned long p4)
{
    unsigned long a = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x40);
    unsigned long b = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x38);
    unsigned long v17 = cL4_geom_rows(0, a, b, (unsigned long *)&(unsigned long){0x606a9c}, (unsigned long *)&(unsigned long){0x606ac4});
    a = cL4_geom_cols(a, b, v17, (unsigned long *)&(unsigned long){0x606a9c}, (void *)0x606aa4);
    unsigned long stride = cL4_pt_stride(v17);
    unsigned long count = (*(unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0xd0)))();
    cL4_pt_init(0);
    unsigned long rows = cL4_pt_count();
    if (__builtin_add_overflow(count, rows, &(unsigned long){0})) {
        __builtin_trap();
    }
    if (count + rows == 0) {
        __builtin_trap();
    }
    unsigned long rows2 = cL4_pt_count();
    if (rows2 == 0) {
        __builtin_trap();
    }
    unsigned long nrows = (count + rows - 1) / rows2;
    unsigned long depth = 1;
    unsigned long off = 0x58;
    unsigned long lvar34 = 0;   /* decompile lVar34: += 0x1ff per outer iter */
    long ld0 = 0;               /* decompile local_d0: += -0x1ff per outer iter */
    unsigned long i = 0;
    do {
        if (i == nrows) {
            return;
        }
        if (frame == 0) {
            __builtin_trap();
        }
        unsigned long stride2 = cL4_pt_stride(v17, a);
        unsigned long *pl = (unsigned long *)(frame + i * stride2);
        unsigned long inext = i + 1;
        long rlen;
        if (i == nrows - 1) {
            rlen = -1;
        } else {
            rlen = (long)(p3 + stride * inext);
        }
        unsigned long lim = (*(unsigned long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0xd0)))();
        unsigned long lim2 = cL4_pt_count();
        unsigned long want = inext * lim2;
        unsigned long total = lim <= want ? lim : want;
        unsigned long expected = i * 0x1ff;
        if (total < expected) {
            __builtin_trap();
        }
        if (i == 0x80402010080403) {   /* decompile: SoftwareBreakpoint(1,0xe6a60) debug canary */
            __builtin_trap();
        }
        pl[0] = total + i * (unsigned long)-0x1ff;
        pl[1] = (unsigned long)rlen;
        pl[2] = 0;
        pl[3] = 0;
        if (total < expected) {
            __builtin_trap();
        }
        if (expected != total) {
            /* sub-mapping loop: fill the row's 0x1ff slots */
            unsigned long base = (unsigned long)pl + 0x20;
            unsigned long soff = off;
            unsigned long limit = lim <= lim2 * depth ? lim : lim2 * depth;
            unsigned long k = 0;
            do {
                unsigned long idx = lvar34 + k;  /* decompile uVar22 = lVar34 + uVar19 */
                if (total <= idx) {
                    __builtin_trap();
                }
                if (0x3fffffffffffffe < k) {
                    __builtin_trap();
                }
                unsigned long *entry = (unsigned long *)((long)pl + 0x20 + k * 0x20);
                if ((long)entry == 0) {
                    __builtin_trap();
                }
                unsigned long kb = cL4_pt_bytes(v17, a);
                if (__builtin_add_overflow(idx * kb, p4, &(unsigned long){0})) {
                    __builtin_trap();
                }
                long row = (*(long (*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0xa0)))();
                if (*(ulong *)(row + 0x10) <= idx) {
                    __builtin_trap();
                }
                unsigned char *src = (unsigned char *)(row + soff);
                unsigned long w1 = *(ulong *)(src - 0x28);
                unsigned long w2 = *(unsigned long *)(src - 0x20);
                unsigned long w3 = *(unsigned long *)(src - 0x18);
                unsigned long w4 = *(unsigned long *)(src - 0x10);
                unsigned long w5 = *(unsigned long *)(src - 8);
                unsigned char kind = *src;
                cL4_release_ref(0);
                switch (kind) {
                default: {
                    cL4_pt_wr_level(entry, w3);
                    cL4_noop();
                    cL4_pt_marker();
                    unsigned long fb = cL4_flag_bit(w2, 8);
                    if (fb & 1) {
                        cL4_noop();
                        cL4_pt_clear();
                        cL4_pt_set_addr(entry, w4);
                        cL4_pt_set_flags(entry, (unsigned int)w5 & 0xff);
                    }
                    unsigned long kk = cL4_pt_kind(w2);
                    if (0xff < kk) {
                        __builtin_trap();
                    }
                    cL4_pt_set_kind(entry, kk);
                    break;
                }
                case 1:
                    cL4_pt_wr_level(entry, 0);
                    cL4_noop();
                    cL4_pt_marker();
                    cL4_noop();
                    cL4_pt_clear();
                    cL4_pt_set_addr(entry, w2);
                    cL4_pt_set_flags(entry, (unsigned int)w3 & 0xff);
                    cL4_pt_set_desc2(entry, w4);
                    unsigned long kk1 = cL4_pt_kind(8);
                    if (0xff < kk1) {
                        __builtin_trap();
                    }
                    cL4_pt_set_kind(entry, kk1);
                    cL4_pt_set_desc3(entry, w5);
                    goto label_done;
                case 2:
                    cL4_noop();
                    cL4_pt_clr_kind();
                    cL4_pt_set_level(entry, (unsigned int)w2 & 1);
                    unsigned long kk2 = cL4_pt_kind(0x10);
                    if (0xff < kk2) {
                        __builtin_trap();
                    }
                    cL4_pt_set_kind(entry, kk2);
                    break;
                case 3: {
                    unsigned long kk3 = cL4_pt_kind(0xb);
                    if (0xff < kk3) {
                        __builtin_trap();
                    }
                    cL4_pt_set_kind(entry, kk3);
                    cL4_pt_set_depth(entry, (w1 & 0xff) + 1);
                    goto label_done;
                }
                case 4:
                    /* fallthrough: kind stays 0 */
                    break;
                }
                cL4_pt_set_kind(entry, 0);
            label_done:
                cL4_pt_set_size(entry, idx * kb + p4);
                k++;
                soff += 0x40;
            } while ((unsigned long)(limit + ld0) != k);
        }
        i = i + 1;
        depth = depth + 1;
        off += 0x7fc0;
        lvar34 = lvar34 + 0x1ff;
        ld0 = ld0 + -0x1ff;
    } while (true);
}

/* FUN_000e6a9c @ 0xe6a9c — scan the CNode-allocation table for a free cap
 * of the requested kind; on exhaustion logs a CNodeAll fatal error. */
unsigned long FUN_000e6a9c(void)
{
    long *t = (*(long *(*)(void))(*(void **)((uintptr_t)__builtin_frame_address(0) + 0xa0)))();
    unsigned long n = *(ulong *)(t + 0x10);
    unsigned long i = 0;
    unsigned long *slots = (unsigned long *)(t + 0x30);
    while (true) {
        if (n == i) {
            cL4_retain_ref((void *)0x350001009400ad38ull);
            cL4_log_pair(0xd00000000000002aull, ((unsigned long)(uintptr_t)"InternalExclaveLauncher CNodeAll..." + 0x10) | 0x8000000000000000ull);
            cL4_fatal(0, 0, 0);
        }
        if (*(ulong *)(t + 0x10) <= i) {
            break;
        }
        if (*(char *)(slots + 5) == '\0') {
            unsigned long v = *slots;
            unsigned long kind = cL4_flag_bit(*(unsigned char *)(slots + 1), 6);
            if (kind & 1) {
                cL4_release_ref(t);
                return v;
            }
        }
        slots += 8;
        i++;
    }
    __builtin_trap();
}

/* FUN_000e6b88 @ 0xe6b88 — format a capability description string from a
 * cap entry's kind; prints type-specific fields (address, size, cpuId,
 * cpuBoot, permission, frame) and returns the formatted {lo,hi} pair. */
cl4_result_t FUN_000e6b88(void)
{
    unsigned long *c = (unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x10);
    unsigned long v8 = c[2];
    unsigned long v3 = c[3];
    unsigned long v1 = c[4];
    unsigned long v2 = c[5];
    unsigned long v9 = c[6];
    unsigned long v5;
    unsigned long v7;
    switch ((char)c[7]) {
    default: {
        cL4_type_printer(0x6c73207974706d45ull);  /* "Empty sl..." */
        cL4_log_begin(0x5e);
        cL4_log_section((unsigned long)"__supportedTypes__" | 0x8000000000000000ull);
        cL4_log_ptr();
        FUN_000e46a4();
        cL4_log_hex(0, 0, 0, 0, 0);
        cL4_log_pair(0);
        cL4_log_val(0);
        cL4_log_label(0x646173796870202cull);  /* ", physad" */
        cL4_log_ptr();
        FUN_000e46a4();
        cL4_log_hex(0, 0, 0, 0, 0);
        cL4_log_pair(0);
        cL4_log_val(0);
        cL4_log_pair(0x3a65707974202cull, 0xe700000000000000ull);  /* ", type:" */
        cL4_log_field(0, 0, 0x6671f0, 0x6756a8, 0x66e1b8);
        cL4_log_pair(0x6e697070616d202cull, 0xec00000078303a67ull);  /* ", mappin", "g:0x.." */
        cL4_log_ptr();
        FUN_000e46a4();
        cL4_log_hex(0, 0, 0, 0, 0);
        cL4_log_pair(0);
        cL4_log_val(0);
        cL4_log_pair(0x3a657a6973202cull, 0xe700000000000000ull);  /* ", size:" */
        cL4_log_ptr();
        FUN_000e46a4();
        cL4_log_hex(0, 0, 0, 0, 0);
        cL4_log_term();
        cL4_log_val(0);
        cL4_log_framelabel();
        cL4_log_field(0, 0, 0x665a00, 0x6756a8, 0x66e1b8);
        v5 = 0x7d20ull;   /* " }" */
        v7 = 0xe200000000000000ull;
        break;
    }
    case '\x01': {
        cL4_type_printer(0x6c73207974706d45ull);
        cL4_log_begin(0x58);
        cL4_log_section((unsigned long)"CnodeEntry<Cpu> cap_0x..." | 0x8000000000000000ull);
        cL4_log_ptr();
        FUN_000e46a4();
        cL4_log_hex(0, 0, 0, 0, 0);
        cL4_log_term();
        cL4_log_val(0);
        cL4_log_label(0x644165736162202cull);  /* ", baseAd" */
        cL4_log_ptr();
        FUN_000e46a4();
        cL4_log_hex(0, 0, 0, 0, 0);
        cL4_log_pair(0);
        cL4_log_val(0);
        cL4_log_pair(0xd000000000000011ull, 0x80000000005c47d0ull);
        cL4_log_str(0x671848);
        cL4_log_term();
        cL4_log_val(0x677790);
        cL4_log_framelabel();
        cL4_log_field(0, 0, 0x665a00, 0x6756a8, 0x66e1b8);
        cL4_log_pair(0x206d726570202cull, 0xe700000000000000ull);  /* ", perm " */
        cL4_log_ptr();
        cL4_log_field(0, 0, 0x666940, 0x6756a8, 0x66e1b8);
        v5 = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x70);
        v7 = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x68);
        return (cl4_result_t){v5, v7};
    }
    case '\x02': {
        cL4_type_printer(0x6c73207974706d45ull);
        cL4_log_begin(0x31);
        cL4_log_val(0);
        cL4_log_field(0, 0, 0xd000000000000016ull, 0x80000000005c4790ull, 0);
        cL4_log_ptr();
        FUN_000e46a4();
        cL4_log_hex(0, 0, 0, 0, 0);
        cL4_log_term();
        cL4_log_val(0);
        cL4_log_pair(0x3a6449757063202cull, 0xea00000000007830ull);  /* ", cpuId:" */
        cL4_log_ptr();
        FUN_000e46a4();
        cL4_log_hex(0, 0, 0, 0, 0);
        cL4_log_term();
        cL4_log_val(0);
        cL4_log_pair(0x6f6f42757063202cull, 0xea00000000003a74ull);  /* ", cpuBoo" */
        bool b = ((unsigned char)v3 & 1) == 0;
        v5 = 0x65757274ull;   /* "true" */
        v7 = 0xe400000000000000ull;
        if (b) {
            v5 = 0x65736c6166ull;  /* "false" */
            v7 = 0xe500000000000000ull;
        }
        cL4_log_pair(v5, v7);
        cL4_log_val(v7);
        v5 = 0x7dull;
        break;
    }
    case '\x03': {
        cL4_log_pair(0x6562754361746144ull, 0xe90000000000003cull);  /* "DataCube", " <.." */
        if ((v8 & 0xff) == 0) {
            v5 = 0xe700000000000000ull;
            v7 = 0x676e6972616853ull;  /* "Sharing" */
        } else {
            v5 = 0xe900000000000067ull;
            v7 = 0x6e697361656c6552ull;  /* "Releasin" */
            if (((unsigned int)v8 & 0xff) != 1) {
                v5 = 0xe300000000000000ull;
                v7 = 0x6c6c41ull;  /* "All" */
            }
        }
        cL4_log_pair(v7, v5);
        cL4_log_val(v5);
        v5 = 0x3eull;
        break;
    }
    case '\x04':
        v5 = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x70);
        v7 = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x68);
        return (cl4_result_t){v5, v7};
    }
    cL4_log_pair(v5, 0xe100000000000000ull);
    return (cl4_result_t){*(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x70),
                          *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x68)};
}

/* FUN_000e7264 @ 0xe7264 — return the "Fatal error" frame. */
cl4_result_t FUN_000e7264(void)
{
    cl4_result_t r;
    r.hi = 0xb;
    r.lo = (unsigned long)"Fatal error";
    return r;
}

/* FUN_000e7288 @ 0xe7288 — log " frame:ailed" label fragment. */
void FUN_000e7288(void)
{
    cL4_log_pair(0x74656d617266202cull, 0xef3a6469656c6261ull);  /* ", frame", "ailed:.." */
}

/* FUN_000e72b0 @ 0xe72b0 — no-op marker. */
void FUN_000e72b0(void)
{
    return;
}

/* FUN_000e72bc @ 0xe72bc — log a label with 0x prefix. */
void FUN_000e72bc(unsigned long v)
{
    cL4_log_pair(v, 0xed000078303a7264ull);  /* "ddr:0x.." */
}

/* FUN_000e72d4 @ 0xe72d4 — log terminator pair. */
void FUN_000e72d4(void)
{
    cL4_log_pair(0);
}

/* FUN_000e72e0 @ 0xe72e0 — log a section label. */
void FUN_000e72e0(unsigned long v)
{
    cL4_log_pair(0xd00000000000001aull, v | 0x8000000000000000ull);
}

/* FUN_000e734c @ 0xe734c — copy a record's {addr, size} pair out. */
void FUN_000e734c(unsigned long *out)
{
    unsigned long flags = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20);
    unsigned long obj = *(long *)((uintptr_t)__builtin_frame_address(0) + 0x10);
    out[0] = *(unsigned long *)(obj + 0x18);
    out[1] = flags;
}

/* FUN_000e7360 @ 0xe7360 — build a launcher record via the object factory
 * (vtable+0x1b8) with descriptor size 0xc; installs the produced fields. */
void FUN_000e7360(unsigned long p1, long *factory)
{
    void (*make)(void *, unsigned long, unsigned long, unsigned long, unsigned long, int) =
        *(void **)(*factory + 0x1b8);
    cL4_retain_ref(0);
    make((void *)((uintptr_t)__builtin_frame_address(0) - 0x90), 0xc, 0, 0, 0, 0);
    if (0 == 0) {
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x20) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x78);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x18) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x30) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x88);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x28) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x80);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x40) = (unsigned long)(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x38));
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x38) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x38);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x49) = *(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x49);
        *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x41) = (unsigned long)(*(unsigned long *)((uintptr_t)__builtin_frame_address(0) - 0x90 + 0x41));
        long *map = *(long **)(*(long *)((uintptr_t)__builtin_frame_address(0) + 0x10) + 0x10);
        void (*dispatch)(void *) = *(void **)(*map + 0x70);
        cL4_retain_ref(map);
        dispatch((void *)((uintptr_t)__builtin_frame_address(0) - 0x90));
        cL4_release_ref(map);
        cL4_release_ref((void *)p1);
        cL4_release_ref(factory);
    } else {
        cL4_release_ref((void *)p1);
        cL4_release_ref(factory);
        cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x10));
        cL4_unwind();
    }
}

/* FUN_000e74cc @ 0xe74cc — produce a "Brokered c-node index" error frame
 * (variant that first runs 0xe79e8 prep and 0xe7874). */
cl4_result_t FUN_000e74cc(void)
{
    cl4_result_t r;
    cL4_dispatch_prep();  /* FUN_000e79e8 */
    cL4_log_begin(0x1d);
    cL4_log_val(0);
    FUN_000e7874();
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x2065646f6e63202cull, 0xef203a7865646e69ull);
    cL4_log_str(0x671df8);
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x29ull, 0xe100000000000000ull);
    r.hi = 0xe900000000000028ull;
    r.lo = 0x646572656b6f7242ull;
    return r;
}

/* FUN_000e75cc @ 0xe75cc — copy record pair (thunk of 0xe734c). */
void FUN_000e75cc(void)
{
    FUN_000e734c(0);
}

/* FUN_000e75f0 @ 0xe75f0 — Brokered c-node error (thunk of 0xe74cc). */
void FUN_000e75f0(void)
{
    FUN_000e74cc();
}

/* FUN_000e7614 @ 0xe7614 — map a VAS region: validate the region size
 * fits 16 bits, resolve the frame descriptor, and install the mapping;
 * on failure builds a VAS error frame. */
void FUN_000e7614(long region, unsigned long size)
{
    *(ulong *)((uintptr_t)__builtin_frame_address(0) + 0x18) = size;
    unsigned long v4 = *(unsigned long *)(region + 0x18);
    unsigned long v1 = *(unsigned long *)(region + 0x20);
    cL4_invoke_pair((void *)region, v4);
    if (size >> 0x10 != 0) {
        __builtin_trap();  /* SoftwareBreakpoint(1, 0xe77e0) */
    }
    unsigned long frame = (unsigned long)cL4_obj_dispatch(v1);
    unsigned long result = ((unsigned long (*)(unsigned long, unsigned long, unsigned long))(frame))(size, v4, v1);
    if (result == 0) {
        cL4_log_begin(0x1c);
        cL4_log_val(0xe000000000000000ull);
        cL4_log_str(0x671848);
        cL4_log_pair(0);
        cL4_log_val(0);
        cL4_log_named(0x662d28, 0x662a78, 0, 0);
        unsigned long *ef = (unsigned long *)0;  /* returned frame ptr (extraout_x1_00) */
        ef[0] = 0xd00000000000001aull;
        ef[1] = 0x80000000005c4810ull;
        *(unsigned char *)(ef + 2) = 1;
        cL4_propagate_error();
    } else {
        unsigned long va = cL4_va_alloc();
        va = cL4_phys_map2(result, va);
        if (0 == 0) {
            *(unsigned long *)((uintptr_t)__builtin_frame_address(0) + 0x10) = va;
            goto done;
        }
    }
    cL4_unwind();
done:
    cL4_scope_exit((void *)region);
}

/* FUN_000e77e0 @ 0xe77e0 — build a mapped VAS region record; fills
 * {type-name, vtable, descriptor} via FUN_000e7360. */
void FUN_000e77e0(unsigned long *out, unsigned long p2)
{
    unsigned long r = cL4_alloc_tag7(0x651b38);
    cL4_retain_ref(0);
    cL4_retain_ref((void *)p2);
    FUN_000e7360(0, 0);
    if (0 == 0) {
        out[3] = 0x651b38;
        out[4] = 0x661db8;
        out[0] = 0;  /* residual value in x0 from 0xe7360 (void) */
    }
}

/* FUN_000e7874 @ 0xe7874 — produce a VAS error frame. */
cl4_result_t FUN_000e7874(void)
{
    cl4_result_t r;
    cL4_dispatch_prep();  /* FUN_000e79e8 */
    cL4_log_begin(0x18);
    cL4_log_val(0);
    cL4_log_str(0x671848);
    cL4_log_pair(0);
    cL4_log_val(0);
    cL4_log_pair(0x29ull, 0xe100000000000000ull);
    r.hi = 0x80000000005c4830ull;
    r.lo = 0xd000000000000015ull;
    return r;
}

/* FUN_000e7930 @ 0xe7930 — release a VAS record's ref and unlock. */
void FUN_000e7930(void)
{
    cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x10));
    cL4_unlock_obj();
}

/* FUN_000e7934 @ 0xe7934 — same as 0xe7930 (separate thunk). */
void FUN_000e7934(void)
{
    cL4_release_ref(*(void **)((uintptr_t)__builtin_frame_address(0) + 0x10));
    cL4_unlock_obj();
}

/* FUN_000e795c @ 0xe795c — mapped VAS region record (thunk of 0xe77e0). */
void FUN_000e795c(void)
{
    FUN_000e77e0(0, 0);
}

/* FUN_000e7960 @ 0xe7960 — mapped VAS region record (thunk of 0xe77e0). */
void FUN_000e7960(void)
{
    FUN_000e77e0(0, 0);
}
