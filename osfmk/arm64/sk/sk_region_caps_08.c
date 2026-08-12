/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * Slice 08: caps region 0xa3a84 - 0xa8c44.
 * SeL4/cL4 vocabulary is used for naming: cap, CNode, TCB, IPC, vspace,
 * notification, endpoint, sched. Confidence is medium unless a string
 * matches. This region is the exclave image-loading / Mach-O parsing /
 * internal-exclave-launcher subsystem.
 */

#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_000e4078 — allocate/fetch a fresh object block of the given kind. */
extern unsigned long cL4_obj_alloc(void);
/* FUN_0036a940 — zero-init / size-fix an allocated block (ptr, size, tag). */
extern unsigned long cL4_block_alloc(unsigned long p, unsigned long size, unsigned long tag);
/* FUN_0036b270 — resolve/fetch the thread context for a cap pointer. */
extern unsigned long cL4_thread_resolve(unsigned long cap);
/* FUN_000e4534 — allocate a small 0x18-byte block (error path). */
extern unsigned long cL4_small_alloc(void);
/* FUN_000e4540 — allocate a 0x28-byte block (macho load result). */
extern unsigned long cL4_macho_alloc(void);
/* FUN_000e2fc4 — build/commit a result descriptor from a source and block. */
extern unsigned long cL4_result_build(unsigned long src, unsigned long blk);
/* FUN_001404e0 — fetch a per-cpu / current-context global. */
extern unsigned long cL4_ctx_fetch(void);
/* FUN_0006e7c0 — push a value onto a local region/stack frame (list head). */
extern void cL4_frame_push(unsigned long *frame, unsigned long *out);
/* FUN_00002534 — lookup/validate a pointer from a table (ptr, tbl). */
extern unsigned long cL4_table_lookup(unsigned long base, unsigned long tbl);
/* FUN_00365b6c — validate/lookup a record by id (out, frame, tbl, key, len). */
extern long cL4_record_lookup(unsigned long *out, unsigned long *frame, unsigned long tbl, unsigned long key, int len);
/* FUN_00141948 — fetch alternate per-cpu context. */
extern unsigned long cL4_ctx_fetch_alt(void);
/* FUN_002a4ab4 — set an error/preemption flag (kind). */
extern void cL4_set_error(unsigned long kind);
/* thunk_FUN_002acbb8 — log/emit an internal error tuple. */
extern void cL4_err_log(unsigned long a, unsigned long b);
/* FUN_00205844 — longjmp/unwind to a fault handler (frame, out, tbl, a, b). */
extern void cL4_fault_unwind(unsigned long *frame, unsigned long *out, unsigned long tbl, unsigned long a, unsigned long b);
/* FUN_001afa84 — print a fatal error message (fmt, len, kind, ...). */
extern void cL4_fatal_error(const char *fmt, int len, unsigned long kind, ...);
/* FUN_000026e8 — pop/unwind a local frame. */
extern void cL4_frame_pop(unsigned long *frame);
/* FUN_00377824 — walk/resolve an object path (kind, id, parent, keyA, keyB). */
extern long cL4_path_resolve(unsigned long kind, unsigned long id, unsigned long parent, unsigned long *keyA, unsigned long *keyB);
/* FUN_00377bec — resolve a secondary lookup key for the path walk. */
extern unsigned long cL4_path_resolve_key(unsigned long id, unsigned long parent, long node, unsigned long *keyA, unsigned long *keyB);
/* FUN_000e3f7c — wrap/build a result value from parts (frame, ctx, node, key). */
extern unsigned long cL4_result_wrap(unsigned long *frame, unsigned long ctx, long node, unsigned long key);
/* FUN_000a3864 — build a loaded-exclave descriptor into *out (out of slice). */
extern void cL4_exclave_desc_build(unsigned long *out, unsigned long a, unsigned long b, long node, unsigned long id, unsigned long key);
/* FUN_0036b230 — fetch vtable/parent pointer. */
extern unsigned long cL4_vtbl_fetch(unsigned long node);
/* FUN_000a4f80 — objc-style msgSend trampoline helper (out of slice). */
extern unsigned long cL4_msgSend(unsigned long self, unsigned long sel, ...);

/* Global: current thread / TCB pointer (_DAT_006c0380). */
extern unsigned long cL4_current_thread;  /* _DAT_006c0380 */

/* Exclave-launcher key/lookup tables (Ghidra DAT_00608478 / DAT_00608644 and
 * their secondary keys LAB_00608488/00608480/0060865c/0060864c). */
extern unsigned long exclave_key_tbl_a;  /* DAT_00608478 */
extern unsigned long exclave_key_tbl_b;  /* DAT_00608488 */
extern unsigned long exclave_key_tbl_c;  /* DAT_00608480 */
extern unsigned long exclave_key_tbl_d;  /* DAT_00608644 */
extern unsigned long exclave_key_tbl_e;  /* LAB_0060865c */
extern unsigned long exclave_key_tbl_f;  /* LAB_0060864c */

/* ------------------------------------------------------------------ *
 * Exclave image loader / Mach-O parser subsystem (region 0xa3a84-).
 * ------------------------------------------------------------------ */

/* FUN_000a3a84 @ 0x000a3a84   (est. exclave_load_begin)
 * Ghidra: void FUN_000a3a84(undefined8 param_1)
 * Starts an exclave binary load: allocates an object block, sizes it,
 * resolves the target thread context from the supplied cap, and hands the
 * resolved thread + sized block to the per-load entry point. No return
 * value; it merely wires up the load state.
 * Confidence: medium
 * Notes: delegates to the exclave launcher entry at 0xa6960. */
void exclave_load_begin(unsigned long load_ctx)
{
    unsigned long block = cL4_obj_alloc();
    unsigned long sized = cL4_block_alloc(block, 0x20, 7);
    unsigned long thread = cL4_thread_resolve(load_ctx);
    exclave_load_entry(thread, sized);
}

/* FUN_000a3ad4 @ 0x000a3ad4   (est. exclave_load_lookup)
 * Ghidra: void FUN_000a3ad4(undefined8 *param_1, undefined8 param_2,
 *        undefined8 param_3, undefined8 param_4, undefined8 param_5,
 *        undefined8 param_6)
 * Resolves an object/path by (kind, id, parent) keys, obtains the resolved
 * node, calls a vtable method (offset 0x40 aligned) on it to produce a
 * partial descriptor, then wraps the result into a 16-byte value stored at
 * *param_1. Returns the descriptor in *param_1.
 * Confidence: medium
 * Notes: indirect vtable dispatch at *(node+0x10); key tables DAT_00608478/
 *   DAT_00608488. */
void exclave_load_lookup(unsigned long *out, unsigned long a, unsigned long b,
                         unsigned long id, unsigned long c, unsigned long kind)
{
    /* Key table references: DAT_00608478 / DAT_00608488. */
    long node = cL4_path_resolve(0, kind, id, &exclave_key_tbl_a, &exclave_key_tbl_b);
    long parent = *(long *)(node - 8);
    (*(code *)&masked_vtbl)((*(long *)(parent + 0x40)) + 0xf & 0xfffffffffffffff0);
    unsigned long ctx = cL4_obj_alloc();
    (**(code **)(parent + 0x10))(&local_frame, a, node);
    unsigned long key = cL4_path_resolve_key(kind, id, node, &exclave_key_tbl_a, &exclave_key_tbl_c);
    *out = cL4_result_wrap(&local_frame, ctx, node, key);
}

/* FUN_000a3c00 @ 0x000a3c00   (est. exclave_desc_parse)
 * Ghidra: void FUN_000a3c00(undefined8 *param_1, undefined8 param_2,
 *        undefined8 param_3, undefined8 param_4, long *param_5)
 * Parses an exclave load descriptor: resolves the path node and secondary
 * key, builds the descriptor via cL4_exclave_desc_build, and stores the
 * resulting 16-byte descriptor at *param_1. On failure, *param_5 receives
 * the error code.
 * Confidence: medium
 * Notes: key tables DAT_00608644 / LAB_0060865c / LAB_0060864c. */
void exclave_desc_parse(unsigned long *out, unsigned long a, unsigned long b,
                        unsigned long id, long *err)
{
    /* Key table references: DAT_00608644 / LAB_0060865c / LAB_0060864c. */
    long node = cL4_path_resolve(0, id, b, &exclave_key_tbl_d, &exclave_key_tbl_e);
    unsigned long key = cL4_path_resolve_key(id, b, node, &exclave_key_tbl_d, &exclave_key_tbl_f);
    /* The descriptor bytes are assembled into the caller's local frame and
     * copied to *out; the success/failure selector is carried in x21. */
    if (desc_build_ok) {
        out[1] = desc_d1;
        out[0] = desc_d0;
        out[3] = desc_d3;
        out[2] = desc_d2;
        out[5] = desc_d5;
        out[4] = desc_d4;
        *(unsigned long *)((long)out + 0x31) = desc_d7;
        *(unsigned long *)((long)out + 0x29) = desc_d6;
    } else {
        *err = desc_fail;
    }
}

/* FUN_000a3d0c @ 0x000a3d0c   (est. exclave_obj_method98)
 * Ghidra: void FUN_000a3d0c(void)
 * Calls the vtable method at offset 0x98 on the object whose pointer is in
 * x20 (the current object being processed). No arguments besides the
 * receiver.
 * Confidence: low
 * Notes: receiver in unaff_x20; indirect call only. */
void exclave_obj_method98(void)
{
    (**(code **)(*(long *)*receiver + 0x98))();
}

