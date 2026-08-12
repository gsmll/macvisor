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

/* 16-byte {lo, hi} register-pair return type (matches sk_internal.h). */
typedef struct cl4_result { uint64_t lo; uint64_t hi; } cl4_result_t;

/* Ghidra's CONCATn helpers — concatenate the low bytes of two words into a
 * wider value. Only the widths used below are defined. */
#define CONCAT71(hi, lo) (((uint64_t)(hi) << 8) | ((uint64_t)(lo) & 0xff))
#define CONCAT17(hi, lo) (((uint64_t)(hi) << 56) | ((uint64_t)(lo) & 0xffffffffffffff))

/* ------------------------------------------------------------------ *
 * Pseudo-register / ghost-artifact declarations.
 *
 * The decompiler left many values in registers or as unnamed stack slots
 * that are not parameterizable in C. Each body below references these as
 * file-scope externs (the Ghidra register/slot they came from is in the
 * function comment). This block exists solely so each body reads cleanly
 * under -fsyntax-only; a real build would bind them to the actual register
 * state or restructure the body.
 * ------------------------------------------------------------------ */
extern unsigned long reg_x1, reg_x6, reg_x8, reg_x9, reg_x10;
extern unsigned long reg_x16, reg_x19, reg_x22, reg_x23, reg_x24, reg_x25;
extern unsigned long reg_buf;
extern long *receiver;              /* unaff_x20 (self / receiver) */
extern unsigned long parent_obj;    /* unaff_x19 */
extern unsigned long task_ctx;      /* param_4 of exclave_region_load */
extern long *dest;                   /* x20 of exclave_bundle_load tail */
extern unsigned long fail_reg;      /* unaff_x21 (success/failure selector) */
extern int desc_build_ok;
extern unsigned long desc_d0, desc_d1, desc_d2, desc_d3, desc_d4, desc_d5;
extern unsigned long desc_d6, desc_d7, desc_fail;
extern unsigned long local_frame, local_frame2, local_rec;
extern unsigned long local_48, local_68, local_80, local_a0, local_c0, local_e0;
extern unsigned long local_140[9];
extern unsigned long stack_frame;
extern unsigned long stack_b0, stack_b8, stack_c0, stack_c8, stack_d0, stack_d8;
extern unsigned long uStack_6f, uStack_70, uStack_77, uStack_78, uStack_88;
extern unsigned long uStack_90, uStack_98, uStack_af, uStack_b0, uStack_b7;
extern unsigned long uStack_b8, uStack_c8, uStack_d0, uStack_d8;
extern unsigned long seg_out, out_list, item, pair, k0, k1, v, next, nj, p;
extern unsigned long have_saned;
extern unsigned long thunk_72664();
extern void (*masked_vtbl)(unsigned long);
extern void (*g_assign_fn)(unsigned long, unsigned long);
extern void (*g_assign_fn2)(unsigned long, unsigned long);
extern void (*g_method_fn)(void);
extern void (*g_append_fn)(unsigned long, unsigned long);
extern unsigned long method_id_6f910, method_id_719c8, method_id_71bbc, method_id_71f40;
extern void (*cb_8d0f8)(void);
extern void (*cb_8d350)(void);

/* Ghidra data addresses (tables / type descriptors / string constants). */
extern unsigned long DAT_004c1908, DAT_004c1920, DAT_004c1930, DAT_004c1938;
extern unsigned long DAT_004c1940, DAT_004bbc30, DAT_004bf1a0;
extern unsigned long DAT_0064c260, DAT_0064e840, DAT_00657778;
extern unsigned long LAB_000f6488;

/* String constants referenced by the launcher. */
extern const char s_Fatal_error_005accd0[];
extern const char s_InternalExclaveLauncher_Macho_sw_005c2000[];
extern const char s_InternalExclaveLauncher_StorageI_005c1ce0[];
extern const char s_InternalExclaveLauncher_VASExten_005c03a0[];
extern const char s_InternalExclaveLauncher_Stacksho_005c2150[];
extern const char s_StorageInterface_could_not_find_u_005c2050[];
extern const char s_Swift_NativeDictionary_swift_005be800[];
extern const char s__AppleInternal_Library_BuildRoot_005c1d70[];
extern const char s_calculateBundleSize_____failed_t_005c1e90[];
extern const char s_could_not_parse_segment64_comman_005c1f10[];
extern const char s_missing_base_address_for_name_005c2190[];
extern const char s_no_DER_artefact__005c1e70[];
extern const char s_readBundle_bundle_bootinfo___005c1d50[];
extern const char s_Can_t_find_kernel_header_005c1ef0[];
extern const char s_Could_not_find_segment64_command_005c1f40[];

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * Declared variadic (unsigned long (...)) so any faithful call site binds
 * regardless of the exact arity the owner reconstructs; the real signature
 * lives in the owning slice file.
 * ------------------------------------------------------------------ */
extern unsigned long cL4_obj_alloc();
extern unsigned long cL4_block_alloc();
extern unsigned long cL4_obj_retain();
extern unsigned long cL4_obj_release();
extern unsigned long cL4_block_alloc_fixed();
extern unsigned long cL4_alloc_fixed();
extern unsigned long cL4_small_alloc();
extern unsigned long cL4_macho_alloc();
extern unsigned long cL4_result_build();
extern unsigned long cL4_ctx_fetch();
extern unsigned long cL4_ctx_fetch_alt();
extern unsigned long cL4_ctx_handle();
extern unsigned long cL4_ctx_handle_alt();
extern unsigned long cL4_frame_push();
extern unsigned long cL4_frame_pop();
extern unsigned long cL4_table_lookup();
extern long cL4_record_lookup();
extern unsigned long cL4_set_error();
extern unsigned long cL4_err_log();
extern unsigned long cL4_fault_unwind();
extern unsigned long cL4_fatal_error();
extern long cL4_path_resolve();
extern unsigned long cL4_path_resolve_key();
extern unsigned long cL4_result_wrap();
extern unsigned long cL4_exclave_desc_build();
void cL4_frame_advance();
extern unsigned long cL4_frame_prep();
extern unsigned long cL4_msg_copy();
extern unsigned long cL4_msg_finish();
extern unsigned long cL4_bind();
extern unsigned long cL4_buf_alloc();
extern unsigned long cL4_vtbl();
extern unsigned long cL4_self();
extern unsigned long cL4_load_fault();
extern long cL4_region_by_magic();
extern unsigned long cL4_region_bounds();
extern unsigned long cL4_region_size();
extern unsigned long cL4_va();
extern unsigned long cL4_va_base();
extern unsigned long cL4_geom_a();
extern unsigned long cL4_geom_b();
extern unsigned long cL4_geom_c();
extern unsigned long cL4_geom_d();
extern unsigned long cL4_page_alloc();
extern unsigned long cL4_page_store();
extern unsigned long cL4_log_begin();
extern unsigned long cL4_log_msg();
extern unsigned long cL4_page_release();
extern unsigned long cL4_page_teardown();
extern unsigned long cL4_inspect2();
extern unsigned long cL4_bcopy();
extern unsigned long cL4_segment_record();
extern unsigned long cL4_registry();
extern unsigned long cL4_der_build();
extern unsigned long cL4_der_verify();
extern unsigned long cL4_log_str();
extern unsigned long cL4_unwind();
extern unsigned long cL4_list_reserve();
extern unsigned long cL4_list_bump();
extern unsigned long cL4_range_construct();
extern unsigned long cL4_array_head();
extern unsigned long cL4_array_ensure();
extern unsigned long cL4_array_elem();
extern unsigned long cL4_array_teardown();
extern unsigned long cL4_elem_reserve();
extern unsigned long cL4_error_tag();
extern unsigned long cL4_hash_pair();
extern unsigned long cL4_dict_probe();
extern unsigned long cL4_dict_fault();
extern unsigned long cL4_bit_clear();
void cL4_assert_le1();
void cL4_assert_le2();
extern unsigned long cL4_obj_base();
extern unsigned long cL4_obj_data();
extern unsigned long cL4_map_pages();
extern unsigned long cL4_reg_entry();
extern unsigned long cL4_dict_seed();
extern unsigned long cL4_dict_init();
extern unsigned long cL4_dict_bind();
extern unsigned long cL4_dict_insert();
extern unsigned long cL4_image_tbl();
extern unsigned long cL4_key_lookup();
extern unsigned long cL4_key_lookup2();
extern unsigned long cL4_dict_value_store();
extern unsigned long cL4_dict_remove();
extern unsigned long cL4_frame_pin();
extern unsigned long cL4_macho_cmd_a();
extern unsigned long cL4_macho_cmd_b();
extern unsigned long cL4_macho_cmd_c();
extern unsigned long cL4_exclave_ctx();
extern unsigned long cL4_exclave_bind();
extern unsigned long cL4_macho_walk();
extern unsigned long cL4_macho_magic();
extern unsigned long cL4_seg_transport();
extern unsigned long cL4_seg_transport_end();
extern unsigned long cL4_seg_enter();
extern unsigned long cL4_seg_leave();
extern unsigned long cL4_region_validate();
extern unsigned long cL4_tls_setup();
extern unsigned long cL4_tls_block();
extern unsigned long cL4_tls_teardown();
extern unsigned long cL4_region_teardown_a();
extern unsigned long cL4_region_teardown_b();
extern unsigned long cL4_error_ctx();
extern unsigned long cL4_swift_fault();
extern unsigned long cL4_metadata();
extern unsigned long cL4_free();

/* In-slice functions referenced before their definitions: exact forward
 * declarations (matching the bodies below). */
long exclave_load_entry(long frame, long out);
void exclave_init(unsigned long obj);
void exclave_region_load(unsigned long *component, unsigned long *table, unsigned long a,
                         long task_ctx, unsigned long b, unsigned long c);
void exclave_segment_build(unsigned long *out, unsigned long *in, unsigned long a,
                           unsigned long b, unsigned long c, unsigned long d,
                           unsigned long e, unsigned long f);
unsigned long cL4_table_iterate(unsigned long table, unsigned long pre, unsigned long post);
unsigned long exclave_err_word(void);
unsigned long cL4_fatal_tuple(void);
const char *cL4_fatal_prefix(void);
void exclave_dict_init(unsigned long obj);
unsigned long exclave_map_resolve(void);
long exclave_stackshot_build(unsigned long a, unsigned long b, unsigned long c, long d, unsigned long e);
void exclave_stackshot_free(void);
unsigned long cL4_type_desc(void);
void exclave_support_data(unsigned long a, unsigned long *b, unsigned int c);
void exclave_obj_drop(void);
void exclave_dict_drop(void);
void cL4_noop_1();
void cL4_noop_2();
void cL4_noop_3();
void cL4_noop_4();
void cL4_noop_5();
void cL4_noop_6();
void cL4_noop_7();
void cL4_noop_8();
void cL4_noop_9();
void cL4_noop_10();
void cL4_noop_11();
void cL4_noop_12();
void cL4_noop_13();
void cL4_noop_14();
void cL4_noop_15();
void cL4_noop_16();
void cL4_noop_17();
void cL4_noop_barrier();
unsigned long cL4_extent(unsigned long obj);
cl4_result_t cL4_extent_of(unsigned long obj); /* FUN_000e250c out-of-slice: min-extent over obj's list; pair (lo=extent, hi=flag) */
void cL4_record_write(unsigned long dst, unsigned long idx, ...);
void cL4_record_copy(void);
void exclave_msg_copy(unsigned long src);
void cL4_assert_capacity(void);
unsigned long cL4_err_code(void);
unsigned long cL4_slot_fetch(unsigned long idx);
unsigned long cL4_type_desc2(void);
unsigned long exclave_kind_bits(unsigned long *p);
unsigned long cL4_assign(unsigned long a, unsigned long b);
unsigned long cL4_assign2(unsigned long a, unsigned long b);
unsigned long cL4_method_call(unsigned long a);
unsigned long cL4_array_append(unsigned long a, unsigned long b);
unsigned long cL4_vtbl_call(unsigned long a, unsigned long b);
void exclave_err_dispatch(unsigned long a, unsigned long b);
unsigned long cL4_msg_ref(void);
void cL4_retain_pair(unsigned long a, unsigned long b);
unsigned long exclave_extent_a(unsigned long p);
unsigned long exclave_extent_b(unsigned long p);
unsigned long exclave_extent_c(unsigned long p);
unsigned long exclave_extent_d(unsigned long p);
unsigned long exclave_extent_e(unsigned long p);
unsigned long exclave_extent_f(unsigned long p);
unsigned long exclave_extent_g(unsigned long p);
unsigned long exclave_extent_h(unsigned long p);
unsigned long exclave_extent_i(unsigned long p);
unsigned long exclave_extent_j(unsigned long p);
void exclave_release_or_return(unsigned long a, long b, unsigned long c, unsigned long d);


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
    unsigned long thread = cL4_obj_retain(load_ctx);
    exclave_load_entry(thread, sized);
}

/* FUN_000a6960 @ 0x000a6960   (est. exclave_load_entry)
 * Ghidra: long FUN_000a6960(long param_1,long param_2)
 * Core exclave load entry: pushes the current load frame, looks up the
 * Mach-O record by id, and on success allocates a 0x28-byte result block
 * that records the loaded image; on failure allocates a 0x18-byte block
 * carrying the error. Stores the result word and the caller's payload in
 * *param_2 and returns param_2.
 * Confidence: medium
 * Notes: Mach-O string 0x5c2000; fatal-error path on lookup failure; table
 *   DAT_004c1920. */
long exclave_load_entry(long frame, long out)
{
    unsigned long ctx = cL4_ctx_fetch();
    unsigned long local_frame[3];
    unsigned long lookup_out;
    unsigned long rec;
    unsigned long result;
    local_frame[0] = frame;
    cL4_frame_push(local_frame, &rec);
    unsigned long tbl = cL4_table_lookup(0x6502a8, &DAT_004c1920);
    int rc = cL4_record_lookup(&lookup_out, &rec, tbl, ctx, 6);
    if (rc == 0) {
        /* First lookup failed — try the alternate per-cpu context. */
        cL4_frame_push(local_frame, &rec);
        unsigned long ctx2 = cL4_ctx_fetch_alt();
        unsigned long rc2 = cL4_record_lookup(&lookup_out, &rec, tbl, ctx2, 6);
        if ((rc2 & 1) == 0) {
            /* Both lookups failed: fatal "Macho.sw" error. */
            cL4_set_error(0x16);
            cL4_err_log(0xd000000000000014, 0x80000000005c2010);
            cL4_fault_unwind(local_frame, &rec, tbl, 0x6756a8, 0x66e1b8);
            cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0,
                            0xe000000000000000,
                            s_InternalExclaveLauncher_Macho_sw_005c2000, 0x23, 2, 0xd9, 0);
        }
        unsigned long blk = cL4_macho_alloc();
        blk = cL4_block_alloc(blk, 0x28, 7);
        result = cL4_result_build(lookup_out, blk);
        result |= 0x8000000000000000;
    } else {
        unsigned long blk = cL4_small_alloc();
        blk = cL4_block_alloc(blk, 0x18, 7);
        *(unsigned long *)(blk + 0x10) = lookup_out;
        result = blk;
    }
    *(unsigned long *)(out + 0x18) = result;
    *(unsigned long *)(out + 0x10) = *(unsigned long *)(frame + 0x10);
    cL4_frame_pop(local_frame);
    return out;
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
    (*(void (**)(unsigned long))&masked_vtbl)((*(long *)(parent + 0x40)) + 0xf & 0xfffffffffffffff0);
    unsigned long ctx = cL4_obj_alloc();
    (**(void (**)(void *, unsigned long, long))(parent + 0x10))(&local_frame, a, node);
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

/* FUN_000a3ce0 @ 0x000a3ce0   (est. exclave_obj_release_and_teardown)
 * Ghidra: void FUN_000a3ce0(void)
 * Releases the object at x20+0x10 and then runs the shared teardown
 * barrier. Identical to 0xa3ce4; a paired release/teardown thunk.
 * Confidence: medium
 * Notes: release at 0x36b118, teardown at 0x36b6ac. */
void exclave_obj_release_and_teardown(void)
{
    cL4_obj_release(*(unsigned long *)(receiver + 0x10));
    cL4_block_alloc_fixed(0, 0, 0);   /* teardown barrier */
}

/* FUN_000a3ce4 @ 0x000a3ce4   (est. exclave_obj_release_and_teardown2)
 * Ghidra: void FUN_000a3ce4(void)
 * Same shape as 0xa3ce0 — releases the object at x20+0x10 and runs the
 * teardown barrier. Appears to be an alternate entry used by a different
 * call site.
 * Confidence: medium */
void exclave_obj_release_and_teardown2(void)
{
    cL4_obj_release(*(unsigned long *)(receiver + 0x10));
    cL4_block_alloc_fixed(0, 0, 0);
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
    (**(void (**)(void))(*(long *)*receiver + 0x98))();
}

/* FUN_000a3d50 @ 0x000a3d50   (est. exclave_obj_extent64)
 * Ghidra: undefined1 [16] FUN_000a3d50(void)
 * Computes a 16-byte extent descriptor: copies 24 bytes from x20+0x18 into
 * a stack frame, runs the barrier, then returns the 16-byte value read back
 * from x20+0x18 as the object's extent.
 * Confidence: low
 * Notes: uses 0x867a8 frame prep + 0x36a1a0 copy. */
void exclave_obj_extent64(void *out)
{
    unsigned long frame[3];
    cL4_frame_prep(0, frame);
    cL4_msg_copy(0, frame, 0x21, 0);
    __builtin_memcpy(out, (void *)(receiver + 0x18), 16);
}

/* FUN_000a3d84 @ 0x000a3d84   (est. exclave_obj_fields_set)
 * Ghidra: void FUN_000a3d84(undefined8 param_1,undefined8 param_2,undefined1 param_3)
 * Stores three fields into the object at x20+0x18: the base/start (param_1),
 * the extent (param_2), and a one-byte kind/flags (param_3). No return.
 * Confidence: low
 * Notes: fields at x20+0x18/0x20/0x28. */
void exclave_obj_fields_set(unsigned long start, unsigned long extent, unsigned char kind)
{
    *(unsigned long *)(receiver + 0x18) = start;
    *(unsigned long *)(receiver + 0x20) = extent;
    *(unsigned char *)(receiver + 0x28) = kind;
}

/* FUN_000a3dcc @ 0x000a3dcc   (est. exclave_obj_extent_pair)
 * Ghidra: undefined1 [16] FUN_000a3dcc(void)
 * Builds a 16-byte {method-id, obj+0x18} extent pair: calls the no-op barrier
 * at 0xa6f08 and returns {&LAB_0006f910, x20+0x18}.
 * Confidence: low
 * Notes: LAB_0006f910 method id. */
void exclave_obj_extent_pair(unsigned long *lo, unsigned long *hi)
{
    cL4_noop_3();
    *hi = (unsigned long)receiver + 0x18;
    *lo = (unsigned long)&method_id_6f910;
}

/* FUN_000a3e08 @ 0x000a3e08   (est. exclave_alloc_init)
 * Ghidra: undefined8 FUN_000a3e08(void)
 * Allocates a block (default size/tag) and calls the initializer at
 * 0xa3e40, returning the allocated block pointer.
 * Confidence: low */
unsigned long exclave_alloc_init(void)
{
    unsigned long blk = cL4_block_alloc(0, 0, 7);
    exclave_init(blk);
    return blk;
}

/* FUN_000a3e40 @ 0x000a3e40   (est. exclave_init)
 * Ghidra: void FUN_000a3e40(void)
 * Initializes an exclave object at x20: zeroes the two extent fields,
 * records the parent object (x19) in +0x10, sets kind=1, fetches the
 * context handle and stores a registry token at +0x30.
 * Confidence: medium */
void exclave_init(unsigned long obj)
{
    cL4_noop_2();
    *(unsigned long *)(obj + 0x18) = 0;
    *(unsigned long *)(obj + 0x20) = 0;
    *(unsigned long *)(obj + 0x10) = parent_obj;
    *(unsigned char *)(obj + 0x28) = 1;
    cL4_ctx_handle_alt();
    unsigned long tok = cL4_reg_entry(0, 0, 0, 0);
    *(unsigned long *)(obj + 0x30) = tok;
}

/* FUN_000a3ea8 @ 0x000a3ea8   (est. exclave_bundle_load)
 * Ghidra: void FUN_000a3ea8(long *param_1, undefined8 param_2, undefined8 param_3,
 *        undefined8 param_4)
 * The main exclave bundle loader. Given a descriptor table (param_1) and the
 * current task context, it:
 *  1. enumerates the bundle's components (vtable +0x88 method), collecting
 *     those that match the TEXT magic 0x11000529b94c7909 into a list,
 *  2. for each collected component, recursively loads it via 0xa46cc,
 *  3. queries the container for its storage size (vtable +0xd0),
 *  4. allocates a page range large enough (0x1800-page-granular),
 *  5. maps each page, storing it in a frame table,
 *  6. resolves the kernel component from the storage interface,
 *  7. verifies a bundle header, computes the load window,
 *   walks the mapped pages, and finally hands the result to the
 *     destination (x20 +0x70).
 * On any missing component it fails fatally ("InternalExclaveLauncher").
 * Confidence: high
 * Notes: very large function; many SoftwareBreakpoint invariants; string
 *   refs 0x5c1ce0/0x5c1d10/0x5c1d50/0x5c1d70/0x5c2000. */
void exclave_bundle_load(unsigned long *table, unsigned long a, unsigned long b, unsigned long c)
{
    void (*method)(void) = *(void (**)(void))(*table + 0x88);
    long root = ((long (*)(void))method)();
    unsigned long count = 0;
    unsigned long list = (unsigned long)&DAT_00657778;
    unsigned long n = *(unsigned long *)(root + 0x10);
    while (n != count) {
        if (*(unsigned long *)(root + 0x10) <= count)
            __builtin_trap();       /* SW breakpoint 0xa4554 */
        cL4_frame_advance();
        void (*m2)(void) = *(void (**)(void))(reg_x16 + 0x78);
        cL4_obj_retain(0);
        unsigned long v = ((unsigned long (*)(void))m2)();
        unsigned long frame[8];
        cL4_frame_prep(0x6509b8, frame);
        cL4_msg_copy(0, frame, 0, 0);
        if (v < 0x11000529b94c790a) {
            cL4_obj_release(0);
            count++;
        } else {
            cL4_list_reserve();
            unsigned long len = *(unsigned long *)(list + 0x10);
            cL4_list_bump(len);
            *(unsigned long *)(list + 0x10) = len + 1;
            *(unsigned long *)(list + len * 8 + 0x20) = reg_x22;
            count++;
        }
    }
    cL4_obj_release(root);
    n = *(unsigned long *)(list + 0x10);
    for (count = 0; n != count; count++) {
        if (*(unsigned long *)(list + 0x10) <= count)
            __builtin_trap();       /* 0xa4558 */
        unsigned long comp = *(unsigned long *)(list + count * 8 + 0x20);
        cL4_obj_retain(comp);
        exclave_region_load(&comp, table, a, task_ctx, b, c);
        if (fail_reg != 0) {
            cL4_obj_release(comp);
            cL4_obj_release(list);
            return;
        }
        cL4_obj_release(comp);
    }
    cL4_obj_release(list);

    /* Query the container's storage capacity (vtable +0xd0). */
    void (*capmethod)(void) = *(void (**)(void))(*table + 0xd0);
    long storage = ((long (*)(unsigned long))capmethod)((unsigned long)table & 0xffffffffffff | 0x6ae1000000000000);
    storage = *(long *)(storage + 0x10);
    cL4_obj_release(0);
    if (storage != 0) {
        storage = ((long (*)(void))capmethod)();
        unsigned long total = 0;
        unsigned long k = *(unsigned long *)(storage + 0x10);
        unsigned long i = 0;
        while (k != i) {
            if (*(unsigned long *)(storage + 0x10) <= i)
                __builtin_trap();   /* 0xa455c */
            unsigned long item = *(unsigned long *)(storage + i * 8 + 0x20);
            cL4_self();
            void (*m3)(void) = *(void (**)(void))(reg_x16 + 0xa0);
            cL4_obj_retain(item);
            unsigned long sz = ((unsigned long (*)(void))m3)();
            cL4_obj_release(item);
            unsigned long carry = __builtin_add_overflow(total, sz, &total);
            i++;
            if (carry)
                __builtin_trap();   /* 0xa410c */
        }
        cL4_obj_release(storage);
        if ((long)total < 0)
            __builtin_trap();       /* 0xa4568 */
        unsigned long window = total + 0x3fff;
        if (__builtin_add_overflow(total, 0x3fff, &window))
            __builtin_trap();       /* 0xa456c */
        unsigned long obj = cL4_obj_base();
        unsigned long desc = cL4_bind(obj, 0x64e1c0);
        unsigned long data = cL4_obj_data();
        cL4_block_alloc(data, 0x50, 7);
        cL4_map_pages(&desc, window & 0xffffffffffffc000, 0x11, 0x1800, 0);
        if (fail_reg != 0)
            cL4_fatal_error(0, 0, 0, 0, 0, s_InternalExclaveLauncher_StorageI_005c1ce0, 0, 0, 0, 0);

        unsigned long npages = window >> 0xe;
        (**(void (**)(void))(*table + 0x108))();
        storage = ((long (*)(void))capmethod)();
        unsigned long pg = 0;
        cL4_noop_1();
        unsigned long frame_tbl = reg_x8;
        unsigned long ft_n = *(unsigned long *)(frame_tbl + 0x10);
        while (ft_n != pg) {
            if (*(unsigned long *)(storage + 0x10) <= pg)
                __builtin_trap();   /* 0xa4560 */
            cL4_frame_advance();
            void (*m4)(void) = *(void (**)(void))(reg_x16 + 0x78);
            cL4_obj_retain(window);
            long v2 = ((long (*)(void))m4)();
            cL4_frame_prep(0x6509b8, &desc);
            cL4_msg_copy(0, &desc, 0, 0);
            if (v2 == 0x11000529b94c7909) {
                cL4_list_reserve();
                unsigned long len = *(unsigned long *)(reg_x8 + 0x10);
                cL4_list_bump(len);
                *(unsigned long *)(reg_x8 + 0x10) = len + 1;
                *(unsigned long *)(reg_x8 + len * 8 + 0x20) = window;
                pg++;
                frame_tbl = reg_x8;
            } else {
                cL4_obj_release(window);
                pg++;
            }
        }
        cL4_obj_release(storage);
        if (*(long *)(frame_tbl + 0x10) == 0) {
            cL4_obj_release(frame_tbl);
            __builtin_trap();       /* 0xa4598 */
        }
        long *kern = *(long **)(frame_tbl + 0x20);
        cL4_obj_retain(kern);
        cL4_obj_release(frame_tbl);
        long kdesc = (**(long (**)(void))(*kern + 0x90))();
        if ((*(long *)(kdesc + 0x10) == 0) ||
            (cL4_err_log(0xd000000000000010, 0x80000000005c1d10), (reg_x1 & 1) == 0)) {
            cL4_error_tag(kdesc);
            __builtin_trap();       /* 0xa4588 */
        }
        cL4_noop_1();
        unsigned long v0 = *(unsigned long *)reg_x8;
        unsigned long v1 = ((unsigned long *)reg_x8)[1];
        unsigned long v2 = ((unsigned long *)reg_x8)[2];
        unsigned long v3 = ((unsigned long *)reg_x8)[3];
        cL4_obj_retain(v0);
        cL4_error_tag(kdesc);
        unsigned long va = cL4_va_base(v0, v1, v2, v3);
        cL4_obj_release(v0);
        storage = ((long (*)(void))capmethod)();
        if (*(long *)(storage + 0x10) == 0) {
            cL4_obj_release(storage);
            __builtin_trap();       /* 0xa45a4 */
        }
        long *kern2 = *(long **)(storage + 0x20);
        cL4_obj_retain(kern2);
        cL4_obj_release(storage);
        unsigned long kern_end = (**(unsigned long (**)(void))(*kern2 + 0x88))();
        cL4_obj_release(kern2);
        unsigned long base = cL4_geom_d();
        if ((long)va < 0)
            __builtin_trap();       /* 0xa4570 */
        if (kern_end < va)
            __builtin_trap();       /* 0xa4574 */
        unsigned long end = base + (kern_end - va);
        if (__builtin_add_overflow(base, kern_end - va, &end))
            __builtin_trap();       /* 0xa4578 */

        unsigned long off = 0;
        for (; npages != 0; npages--) {
            unsigned long page = cL4_page_alloc();
            if (page == 0) {
                cL4_set_error(0x1e);
                cL4_error_tag(0xe000000000000000);
                cL4_noop_2();
                cL4_log_msg(s_readBundle_bundle_bootinfo___005c1d50, 0x1c, 2, 0, 0, 0, 0, 0);
                cL4_err_log();
                cL4_error_tag(reg_x1);
                cL4_err_log(0x203a20, 0xe300000000000000);
                cL4_noop_14();
                ((void (*)(unsigned long, unsigned long))cL4_swift_fault(reg_x16))(0x677830, reg_x1);
                cL4_err_log();
                cL4_error_tag(reg_x1);
                cL4_unwind();
                cL4_fatal_error(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            }
            if (__builtin_add_overflow(end, off, &reg_x8))
                __builtin_trap();   /* 0xa4564 */
            unsigned long va2 = cL4_va(end + off);
            unsigned long base2 = cL4_va_base();
            cL4_page_store(base2, va2, page);
            cL4_log_begin();
            cL4_noop_6(&LAB_000f6488, 0, s__AppleInternal_Library_BuildRoot_005c1d70);
            cL4_log_msg();
            long ctl = (**(long (**)(long))(*table + 0x100))((long)table + 0x100);
            if (ctl == 0)
                __builtin_trap();   /* 0xa457c */
            cL4_noop_barrier();
            (**(void (**)(unsigned long, unsigned long))(reg_x16 + 0x90))(off, page);
            cL4_obj_release(table);
            cL4_page_release(page);
            cL4_page_teardown(page);
            off += 0x4000;
        }
        cL4_obj_release(kern);
    }
    void (*fin)(void) = *(void (**)(void))(*table + 0x100);
    if (((long (*)(void))fin)() != 0) {
        cL4_noop_barrier();
        unsigned long pair[2] = {(**(unsigned long (**)(void))(reg_x16 + 0xe0))(),
                                 (**(unsigned long (**)(void))(reg_x16 + 0xe4))()};
        cL4_obj_release(table);
        (**(void (**)(unsigned long, unsigned long, int))(*dest + 0x70))(pair[0], pair[1], 0);
        return;
    }
    __builtin_trap();               /* 0xa458c */
}

/* FUN_000a46cc @ 0x000a46cc   (est. exclave_region_load)
 * Ghidra: void FUN_000a46cc(undefined8 *param_1,long *param_2,undefined8 param_3,
 *        long param_4, undefined8 param_5,undefined8 param_6)
 * Loads one exclave region: resolves its bounds from the container
 * (magic __TEXT), allocates page storage, maps each 0x4000-byte segment via
 * the storage-interface vtable, parses the region's Mach-O header, collects
 * its kernel components, then if the storage interface exposes an exclave
 * context (magic __SANED/__BLADED) builds a context binding and returns it.
 * Falls back to a fatal "StorageInterface could not find..." error.
 * Confidence: high (verified vs decompile+disasm, VB2 sweep; pair-return calls fixed)
 * Notes: magics 0x545845545f5f (__TEXT), 0x4e454e4153415f5f/0xed000044454c4241
 *   (__SANED/__BLADED); string refs 0x5c2030/0x5c03b0/0x5c03a0/0x5c1ce0/0x5c2050. */
void exclave_region_load(unsigned long *component, unsigned long *table, unsigned long a,
                         long task_ctx, unsigned long b, unsigned long c)
{
    unsigned long *node = (unsigned long *)*component;
    unsigned long size = cL4_region_bounds(table, node, 0x545845545f5f, 0xe600000000000000);
    unsigned long base = cL4_va_base();
    if (base == 0) {
        /* unknown region type */
        cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0xd000000000000036,
                        (unsigned long)"unknown region type" | 0x8000000000000000,
                        s_InternalExclaveLauncher_StorageI_005c1ce0, 0x2e, 2, 0x133, 0);
    }
    long sz = cL4_region_by_magic(node, 0x545845545f5f, 0xe600000000000000);
    if ((long)sz < 0)
        __builtin_trap();           /* 0xa4da4 */
    unsigned long obj = cL4_obj_base();
    unsigned long desc = cL4_bind(obj, 0x64e1c0);
    unsigned long data = cL4_obj_data();
    cL4_block_alloc(data, 0x50, 7);
    long *pages = (long *)cL4_map_pages(&desc, sz, 0x11, 0x1800, 0x10);
    if (fail_reg != 0)
        __builtin_trap();           /* 0xa4da8 */
    unsigned long off = 0;
    for (unsigned long np = (unsigned long)sz >> 0xe; np != 0; np--) {
        if (__builtin_add_overflow(size, off, &reg_x8))
            __builtin_trap();       /* 0xa4d9c */
        unsigned long vaddr = cL4_va(size + off);
        unsigned long page = cL4_page_alloc();
        if (page == 0) {
            cL4_set_error(0x1e);
            cL4_error_tag(0xe000000000000000);
            cL4_log_msg(s_readBundle_bundle_bootinfo___005c1d50, 0x1c, 2, 0, 0, 0, 0, 0);
            cL4_err_log();
            cL4_error_tag(reg_x1);
            cL4_err_log(0x203a20, 0xe300000000000000);
            ((void (*)(unsigned long, unsigned long))cL4_swift_fault(0x671df8))(0x677830, 0x671df8);
            cL4_err_log();
            cL4_error_tag(reg_x1);
            cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0xd000000000000017,
                            (unsigned long)"VASExten..." | 0x8000000000000000,
                            s_InternalExclaveLauncher_VASExten_005c03a0, 0x2a, 2, 0x6f, 0);
        }
        cL4_page_store(base, vaddr, page);
        unsigned long lr = cL4_log_begin();
        unsigned long lr_hi = reg_x1;
        cL4_log_msg(&LAB_000f6488, 0, s__AppleInternal_Library_BuildRoot_005c1d70, 0xfa, 2, 0x145, lr, lr_hi);
        (**(void (**)(unsigned long, unsigned long))(*pages + 0x90))(off, page);
        cL4_page_release(page);
        cL4_page_teardown(page);
        off += 0x4000;
    }
    cl4_result_t range_res = (**(cl4_result_t (**)(void))(*pages + 0xe0))();
    unsigned long lo = range_res.lo, hi = range_res.hi;
    if ((long)hi < 0)
        __builtin_trap();           /* 0xa4da8 */
    unsigned long range_end;
    if (hi == 0) {
        if (lo != 0) range_end = lo;
        else range_end = 0;
    } else {
        if (lo == 0)
            __builtin_trap();       /* 0xa48c4 */
        range_end = lo + hi;
    }
    unsigned long hdr[3];
    cL4_range_construct(hdr, lo, range_end, 0);
    unsigned long hdr2[6];
    __builtin_memcpy(hdr2, &local_frame, 0x50);
    cL4_array_head(&local_frame);
    long count = *(long *)(local_frame + 0x10);
    if (count != 0) {
        cL4_array_append(local_frame, local_frame2);
        local_frame2 = (unsigned long)&DAT_00657778;
        cL4_array_ensure(0, count, 0);
        long *p = (long *)(local_frame + 0x48);
        long rem = count;
        do {
            cL4_bcopy(reg_buf, p, 0x48);
            unsigned long elem = cL4_array_elem();
            unsigned long n = *(unsigned long *)(local_frame + 0x10);
            if (*(unsigned long *)(local_frame + 0x18) >> 1 <= n)
                cL4_array_ensure(1 < *(unsigned long *)(local_frame + 0x18), n + 1, 1);
            *(unsigned long *)(local_frame + 0x10) = n + 1;
            *(void **)(local_frame + n * 0x10 + 0x20) = (void *)elem;
            p += 0x70 / 8;
            rem--;
        } while (rem != 0);
        long final_count = *(long *)(local_frame + 0x10);
        cL4_array_teardown(&local_frame);
        if (count != final_count)
            __builtin_trap();       /* 0xa4dac */
    }
    unsigned long *elems = (unsigned long *)&DAT_00657778;
    unsigned long en = *(unsigned long *)(local_frame + 0x10);
    if (en == 0) {
        cL4_obj_release(local_frame);
        cL4_array_teardown(&local_frame);
    } else {
        unsigned long out_list = (unsigned long)&DAT_00657778;
        cL4_elem_reserve(en);
        unsigned long i = 0;
        unsigned long *slot = (unsigned long *)(local_frame + 0x28);
        do {
            if (*(unsigned long *)(local_frame + 0x10) <= i)
                __builtin_trap();   /* 0xa4da0 */
            unsigned long elem = slot[-1];
            unsigned long e0 = *slot;
            unsigned long e1 = e0;
            cL4_obj_retain(e1);
            exclave_segment_build(&seg_out, &elem, local_frame, (unsigned long)table, (unsigned long)node, a, b, c);
            i++;
            cL4_error_tag(e1);
            unsigned long v = seg_out;
            cL4_list_reserve();
            unsigned long len = *(unsigned long *)(out_list + 0x10);
            cL4_list_bump(len);
            *(unsigned long *)(out_list + 0x10) = len + 1;
            *(unsigned long *)(out_list + len * 8 + 0x20) = v;
            slot += 2;
        } while (en != i);
        if (en != *(unsigned long *)(local_frame + 0x10))
            __builtin_trap();       /* 0xa4db0 */
        cL4_obj_retain(out_list);
        cL4_obj_release(local_frame);
        cL4_array_teardown(&local_frame);
        cL4_obj_release(out_list);
    }
    cL4_msg_copy(task_ctx + 0x10, &local_frame, 0x21, 0);
    cL4_obj_retain(pages);
    cL4_msg_finish(&local_frame);
    cL4_obj_release(&local_frame);

    long si = (**(long (**)(void))(*node + 0x90))();
    if (*(long *)(si + 0x10) == 0) {
        cL4_error_tag(si);
        cL4_obj_release(0);
        return;
    }
    cL4_obj_retain(si);
    unsigned long mag_lo = cL4_hash_pair(0x4e454e4153415f5f, 0xed000044454c4241);
    unsigned long mag_hi = reg_x1;
    if ((mag_hi & 1) == 0) {
        cL4_error_tag(si, 2);
        cL4_obj_release(0);
        return;
    }
    long owner = *(long *)(*(long *)(si + 0x38) + mag_lo * 0x20);
    cL4_obj_retain(owner);
    cL4_error_tag(si, 2);
    if (owner == 0) {
        cL4_obj_release(0);
        return;
    }
    cL4_obj_release(owner);
    if ((**(unsigned long (**)(void))(*table + 0xa0))() & 1) {
        void (*ctxfn)(void) = *(void (**)(void))(*node + 0xd8);
        cl4_result_t ctxpair = ((cl4_result_t (*)(unsigned long))ctxfn)((unsigned long)node & 0xffffffffffff | 0x6ae1000000000000);
        cL4_macho_walk(&local_frame);
        unsigned long cmd = cL4_macho_cmd_a();
        unsigned long magic = cL4_macho_magic();
        unsigned long ctx = cL4_ctx_handle_alt();
        ctx = cL4_block_alloc(ctx, 0x48, 7);
        unsigned long c1 = cL4_exclave_ctx(ctxpair.lo, ctxpair.hi, elems, cmd, magic, have_saned, ctx);
        cL4_obj_retain(0);
        cl4_result_t epair = ((cl4_result_t (*)(void))ctxfn)();
        cL4_msg_copy(task_ctx + 0x30, &local_frame, 0x21, 0);
        unsigned long bind = cL4_exclave_bind(c1, epair.lo, epair.hi);
        cL4_msg_finish(&local_frame);
        cL4_obj_release(pages);
        cL4_error_tag(epair.hi);
        cL4_obj_release(c1);
        cL4_obj_release(bind);
        return;
    }
    cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0xd00000000000001a,
                    (unsigned long)(s_StorageInterface_could_not_find_u_005c2050 + 0x20) | 0x8000000000000000,
                    s_InternalExclaveLauncher_StorageI_005c1ce0, 0x2e, 2, 0x16d, 0);
}

/* FUN_000a4f80 @ 0x000a4f80   (est. exclave_segment_build)
 * Ghidra: void FUN_000a4f80(undefined8 *param_1,undefined8 *param_2,undefined8 param_3,
 *        undefined8 param_4, undefined8 param_5, undefined8 param_6, undefined8 param_7,
 *        undefined8 param_8)
 * Builds one exclave segment descriptor: inspects the two-word record at
 * param_2; if its kind byte != 1, copies 0x48 bytes into a record and calls
 * cL4_segment_record to produce the descriptor stored at *param_1. If kind
 * is 1, it is an invalid "mach" record and the load fails fatally.
 * Confidence: medium
 * Notes: fatal string 0x5c2090/0x5c1ce0, "mach" bytes 0x6863616d206e6920. */
void exclave_segment_build(unsigned long *out, unsigned long *in, unsigned long a,
                           unsigned long b, unsigned long c, unsigned long d, unsigned long e,
                           unsigned long f)
{
    unsigned long w0 = in[0];
    unsigned long w1 = in[1];
    unsigned char frame[9];
    cL4_inspect2(frame, w0, w1);
    if (frame[0] != 1) {
        unsigned long rec[6];
        cL4_bcopy((unsigned long)rec, (void *)frame, 0x48);
        unsigned long r = cL4_segment_record(a, b, rec, w0, w1, d, e, f);
        *out = r;
        return;
    }
    cL4_set_error(0x34);
    cL4_err_log(0xd000000000000029, 0x80000000005c2090);
    cL4_err_log(w0, w1);
    cL4_err_log(0x6863616d206e6920, 0xe90000000000006f);
    cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0, 0xe000000000000000,
                    s_InternalExclaveLauncher_StorageI_005c1ce0, 0x2e, 2, 0x15c, 0);
}

/* FUN_000a50e8 @ 0x000a50e8   (est. exclave_der_verify_flow)
 * Ghidra: undefined8 FUN_000a50e8(void)
 * Verifies a DER artefact for the current exclave: prepares a frame, builds
 * a DER record from the object, runs the verifier; if no DER artefact is
 * present it fails fatally ("no DER artefact"). Otherwise returns the
 * verified result.
 * Confidence: medium
 * Notes: string 0x5c1e70 "no DER artefact". */
unsigned long exclave_der_verify_flow(void)
{
    unsigned long frame[3];
    cL4_frame_prep(0, frame);
    cL4_msg_copy(0, frame, 0, 0);
    unsigned long obj = *(unsigned long *)(receiver + 0x30);
    unsigned long v = cL4_obj_retain(obj);
    unsigned long der = cL4_table_iterate(v, (unsigned long)&method_id_71bbc, (unsigned long)cL4_der_build);
    cL4_error_tag(obj);
    unsigned long block = cL4_registry();
    unsigned long kind = 7;
    cL4_block_alloc(block, 0x18);
    unsigned long r = cL4_der_build(v);
    cL4_vtbl();
    unsigned long pair[2] = {(**(unsigned long (**)(void))(reg_x16 + 0x68))(),
                             (**(unsigned long (**)(void))(reg_x16 + 0x6c))()};
    unsigned long h = pair[1];
    if ((kind & 0xff) == 1) {
        cL4_log_str(s_no_DER_artefact__005c1e70);
        cL4_noop_3();
        cL4_unwind();
        cL4_fatal_error(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    unsigned long blk = cL4_block_alloc(0x650118, 0x29, 7);
    unsigned long vv = cL4_obj_retain(v);
    cL4_der_verify(vv, pair[0], h, 0);
    if (fail_reg == 0) {
        cL4_noop_barrier();
        h = (**(unsigned long (**)(void))(reg_x16 + 0x98))();
        cL4_obj_release(v);
        v = blk;
    }
    cL4_obj_release(v);
    return h;
}

/* FUN_000a5274 @ 0x000a5274   (est. exclave_obj_drop)
 * Ghidra: void FUN_000a5274(void)
 * Releases two object references stored at x20+0x10 and x20+0x30 (the
 * payload and the registry token). Used by object teardown.
 * Confidence: low */
void exclave_obj_drop(void)
{
    cL4_obj_release(*(unsigned long *)(receiver + 0x10));
    cL4_error_tag(*(unsigned long *)(receiver + 0x30));
}

/* FUN_000a529c @ 0x000a529c   (est. exclave_obj_dealloc_a)
 * Ghidra: void FUN_000a529c(void)
 * Drops the two object references then runs the teardown barrier.
 * Confidence: low */
void exclave_obj_dealloc_a(void)
{
    exclave_obj_drop();
    cL4_block_alloc_fixed(0, 0, 0);
}

/* FUN_000a52a0 @ 0x000a52a0   (est. exclave_obj_dealloc_b)
 * Ghidra: void FUN_000a52a0(void)
 * Same as 0xa529c — drops references and runs teardown. Alternate entry.
 * Confidence: low */
void exclave_obj_dealloc_b(void)
{
    exclave_obj_drop();
    cL4_block_alloc_fixed(0, 0, 0);
}

/* FUN_000a52c4 @ 0x000a52c4   (est. exclave_obj_methodA8)
 * Ghidra: void FUN_000a52c4(void)
 * Calls the vtable method at offset 0xa8 on the object in x20. Receiver-only
 * call.
 * Confidence: low */
void exclave_obj_methodA8(void)
{
    (**(void (**)(void))(*(long *)*receiver + 0xa8))();
}

/* FUN_000a5300 @ 0x000a5300   (est. exclave_calc_bundle_size)
 * Ghidra: long FUN_000a5300(void)
 * Computes the total exclave bundle size: enumerates the component table,
 * collects TEXT-magic entries, and once all are gathered computes the
 * adjusted bundle byte size from the region geometry (page-rounded) minus
 * the container/overhead delta between DATA and TEXT extents.
 * Confidence: medium
 * Notes: "calculateBundleSize... failed" string 0x5c1e90. */
long exclave_calc_bundle_size(void)
{
    long idx = 0;
    cL4_noop_4();
    unsigned long table = reg_x8;
    unsigned long n = *(unsigned long *)(table + 0x10);
    do {
        long rem = (long)n - idx;
        unsigned long *slot = (unsigned long *)(table + 0x20 + idx * 8);
        for (;;) {
            if (rem == 0) {
                cL4_noop_5(s_calculateBundleSize_____failed_t_005c1e90);
                cL4_noop_6(0xd000000000000034, reg_x8 | 0x8000000000000000);
                unsigned long u = cL4_load_fault();
                cL4_obj_release(reg_x19);
                idx = 0;
                /* second pass over the table */
                rem = (long)n - idx;
                slot = (unsigned long *)(table + 0x20 + idx * 8);
                for (;;) {
                    if (rem == 0) {
                        cL4_noop_6(0xd000000000000034, reg_x8 | 0x8000000000000000,
                                   s__AppleInternal_Library_BuildRoot_005c1d70);
                        unsigned long v = cL4_load_fault();
                        cL4_obj_release(reg_x19);
                        unsigned long g_c = cL4_geom_c();
                        long g_d = cL4_geom_d();
                        if (__builtin_add_overflow(g_d, 0x3fff, &reg_x8))
                            __builtin_trap();   /* 0xa5624 */
                        if ((long)(g_d + 0x3fff) < 0)
                            __builtin_trap();   /* 0xa5628 */
                        unsigned long win = (g_d + 0x3fff) & 0x7fffffffffffc000;
                        unsigned long end = g_c + win;
                        if (__builtin_add_overflow(g_c, win, &end))
                            __builtin_trap();   /* 0xa562c */
                        unsigned long g_a = cL4_geom_a();
                        unsigned long textsz = cL4_region_by_magic(u, 0x545845545f5f, 0xe600000000000000);
                        if (g_a < textsz)
                            __builtin_trap();   /* 0xa5630 */
                        unsigned long g_b = cL4_geom_b();
                        unsigned long g_a2 = cL4_geom_a();
                        if (g_b < g_a2)
                            __builtin_trap();   /* 0xa5634 */
                        unsigned long dsz = cL4_region_size(v, 0x415441445f5f, 0xe600000000000000);
                        unsigned long tsz = cL4_region_size(v, 0x545845545f5f, 0xe600000000000000);
                        cL4_obj_release(u);
                        cL4_obj_release(v);
                        if (dsz < tsz)
                            __builtin_trap();   /* 0xa5638 */
                        unsigned long delta = (g_b - g_a2) - (dsz - tsz);
                        if (g_b - g_a2 < dsz - tsz)
                            __builtin_trap();   /* 0xa563c */
                        unsigned long base = end - (g_a - textsz);
                        if (g_a - textsz <= end) {
                            if (delta <= base)
                                return base - delta;
                            __builtin_trap();   /* 0xa5644 */
                        }
                        __builtin_trap();       /* 0xa5640 */
                    }
                    idx++;
                    unsigned long item = *slot;
                    cL4_vtbl();
                    void (*m)(void) = *(void (**)(void))(reg_x16 + 0x78);
                    cL4_obj_retain(item);
                    long v2 = ((long (*)(void))m)();
                    cL4_frame_prep(0x6509b8, &stack_frame);
                    cL4_msg_copy(0, &stack_frame, 0, 0);
                    if (v2 == 0x11000529b94c7909) break;
                    cL4_obj_release(item);
                    rem--;
                    slot++;
                }
                cL4_list_reserve();
                long len = *(long *)(reg_x19 + 0x10);
                cL4_list_bump(len);
                *(long *)(reg_x19 + 0x10) = len + 1;
                *(unsigned long *)(reg_x19 + len * 8 + 0x20) = item;
            }
            idx++;
            unsigned long *p = (unsigned long *)*slot;
            void (*m2)(void) = *(void (**)(void))(*p + 0x78);
            cL4_obj_retain(p);
            long v3 = ((long (*)(void))m2)();
            cL4_frame_prep(0x6509b0, &stack_frame);
            cL4_msg_copy(0, &stack_frame, 0, 0);
            if (v3 == 0xd0000650fd802013) break;
            cL4_obj_release(p);
            rem--;
            slot++;
        }
        cL4_list_reserve();
        long len = *(long *)(reg_x19 + 0x10);
        cL4_list_bump(len);
        *(long *)(reg_x19 + 0x10) = len + 1;
        *(long **)(reg_x19 + len * 8 + 0x20) = (long *)p;
    } while (1);
}

/* FUN_000a5650 @ 0x000a5650   (est. exclave_find_kernel)
 * Ghidra: undefined8 FUN_000a5650(long param_1,long param_2)
 * Locates the kernel component of an exclave bundle: scans the component
 * table for the kernel magic __MACHOH (0x484f4843414d5f5f), then walks the
 * image's segment64 commands to find the __TEXT segment; returns the
 * computed base address (local_d0) of the kernel text.
 * Confidence: high
 * Notes: verified 2026-08-12. magics 0x484f4843414d5f5f (__MACHOH),
 *   0x545845545f5f (__TEXT); strings "Can't find kernel component"/
 *   "Can't find kernel header"/"Could not find segment64 command"/
 *   "could not parse segment64 comman". Fixed: the two component/segment
 *   magic probes were calling their vtable method twice (or dropping the hi
 *   word) instead of capturing the 16-byte return once; now use cl4_result_t.
 *   Decompile was partially mangled (unreachable blocks, extraout regs). */
unsigned long exclave_find_kernel(unsigned long components, unsigned long image)
{
    unsigned long list = (unsigned long)&DAT_00657778;
    unsigned long n = *(unsigned long *)(components + 0x10);
    unsigned long base_d0 = 0;
    unsigned long i = 0;
    /* collect kernel components */
    while (n != i) {
        if (*(unsigned long *)(components + 0x10) <= i)
            __builtin_trap();       /* 0xa5ad0 */
        long *comp = *(long **)(components + i * 8 + 0x20);
        cl4_result_t (*m)(void) = *(cl4_result_t (**)(void))(*comp + 0x70);
        cL4_obj_retain(comp);
        cl4_result_t magic_pair = m();
        long magic_lo = (long)magic_pair.lo, magic_hi = (long)magic_pair.hi;
        if (magic_lo == 0x484f4843414d5f5f && magic_hi == -0x10bcb3adbabbbebb) {
            cL4_error_tag(magic_hi);
            /* accept */
            cL4_list_reserve();
            unsigned long len = *(unsigned long *)(list + 0x10);
            cL4_list_bump(len);
            *(unsigned long *)(list + 0x10) = len + 1;
            *(long **)(list + len * 8 + 0x20) = comp;
            i++;
        } else {
            unsigned long m = cL4_hash_pair(magic_lo, magic_hi, 0x484f4843414d5f5f, 0xef434c5245444145, 0);
            cL4_error_tag(magic_hi);
            if ((m & 1) != 0) {
                cL4_list_reserve();
                unsigned long len = *(unsigned long *)(list + 0x10);
                cL4_list_bump(len);
                *(unsigned long *)(list + 0x10) = len + 1;
                *(long **)(list + len * 8 + 0x20) = comp;
                i++;
            } else {
                cL4_obj_release(comp);
                i++;
            }
        }
    }
    cL4_obj_release(components);
    if (*(long *)(list + 0x10) == 0) {
        cL4_noop_5(s_Can_t_find_kernel_header_005c1ef0);
        cL4_noop_6(0xd000000000000018, reg_x8 | 0x8000000000000000);
        unsigned long k = cL4_load_fault();
        cL4_obj_release(list);
        /* fall into segment walk below */
    }
    unsigned long header = *(unsigned long *)(image + 0x30);
    if (header == 0)
        __builtin_trap();           /* 0xa5adc */
    cL4_vtbl();
    unsigned long fileoff = (**(unsigned long (**)(void))(reg_x16 + 0x88))();
    if ((long)fileoff < 0)
        __builtin_trap();           /* 0xa5ad4 */
    unsigned long filesize = (**(unsigned long (**)(void))(*((long *)list) + 0xa0))();
    if ((long)filesize < 0)
        __builtin_trap();           /* 0xa5ad8 */
    unsigned long start = header + fileoff;
    unsigned long end = start + filesize;
    unsigned long cmds[4];
    cL4_range_construct(cmds, start, end, 0);
    cL4_array_head(&local_frame);
    unsigned long seg = local_frame;
    unsigned long cmd_off = 0x20;
    unsigned long j = 0;
    unsigned long cmdn = *(unsigned long *)(local_frame + 0x10);
    for (;;) {
        if (cmdn == j) {
            cL4_log_str(s_Could_not_find_segment64_command_005c1f40);
            cL4_noop_3();
            cL4_unwind();
            cL4_fatal_error(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        }
        if (*(unsigned long *)(seg + 0x10) <= j)
            __builtin_trap();       /* 0xa5acc */
        unsigned long *cmd = (unsigned long *)(seg + cmd_off);
        unsigned long c0 = cmd[0], c1 = cmd[1], c2 = cmd[2], c3 = cmd[3], c4 = cmd[4];
        unsigned long is_text = cL4_macho_cmd_b(c0 & 0xffffffffff, 0x100000000);
        if ((is_text & 1) != 0) {
            unsigned long sc[9];
            cL4_macho_cmd_c(sc, &c0);
            cL4_bcopy((unsigned long)&local_frame, sc, 0x144);
            int rc = (int)exclave_kind_bits(&local_frame);
            if (rc != 0) {
                cL4_log_str(s_could_not_parse_segment64_comman_005c1f10);
                cL4_noop_3();
                cL4_unwind();
                cL4_fatal_error(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            }
            unsigned long l = cL4_der_build(&local_frame);
            cL4_bcopy((unsigned long)&stack_frame, l + 0x28, 0x48);
            cl4_result_t e = ((cl4_result_t (*)(void))cL4_array_elem)();
            unsigned long e0 = e.lo, e1 = e.hi;
            if (e0 == 0x545845545f5f && e1 == -0x1a00000000000000) {
                cL4_obj_release(list);
                cL4_obj_release(seg);
                cL4_error_tag(e1);
                cL4_obj_release(0);
                return base_d0;
            }
            unsigned long m2 = cL4_hash_pair(e0, e1, 0x545845545f5f, 0xe600000000000000, 0);
            cL4_error_tag(e1);
            if ((m2 & 1) != 0) {
                cL4_obj_release(list);
                cL4_obj_release(seg);
                cL4_obj_release(0);
                return base_d0;
            }
        }
        cmd_off += 0x28;
        j++;
    }
}

/* FUN_000a5b60 @ 0x000a5b60   (est. exclave_table_iter_simple)
 * Ghidra: void FUN_000a5b60(long param_1)
 * Simple table iteration: if the table is empty, returns immediately via
 * the no-op barrier. Otherwise runs the pre and post callbacks over the
 * entries, stopping when the end marker is reached; panics if the count
 * diverges.
 * Confidence: low
 * Notes: single callback pair (0x719f0, 0x8cea4) inlined. */
void exclave_table_iter_simple(unsigned long table)
{
    long count = *(long *)(table + 0x10);
    if (count == 0) {
        cL4_noop_4();
        return;
    }
    cL4_table_iterate(count, 0, 0);
    cL4_noop_6();
    cL4_unwind();
    if (local_48 == 0) {
        cL4_noop_3();
        long i = reg_x8;
        do {
            long next = i + 1;
            if (__builtin_add_overflow(i, 1, &next))
                __builtin_trap();   /* 0xa5c1c */
            if (reg_x10 <= next) {
                cL4_obj_retain(table);
                cL4_obj_release(local_68);
                if (reg_x23 == count)
                    return;
                __builtin_trap();   /* 0xa5bf8 */
            }
            i++;
        } while (*(long *)(reg_x9 + next * 8) == 0);
    }
    cL4_obj_retain(table);
    cL4_obj_release(local_68);
    __builtin_trap();               /* 0xa5bdc */
}

/* FUN_000a5c1c @ 0x000a5c1c   (est. exclave_iter_a)
 * Ghidra: void FUN_000a5c1c(undefined8 param_1)
 * Generic table iteration wrapper binding callbacks (0x719c8, 0x8d0f8).
 * Confidence: low */
void exclave_iter_a(unsigned long table)
{
    cL4_table_iterate(table, (unsigned long)&method_id_719c8, (unsigned long)cb_8d0f8);
}

/* FUN_000a5c48 @ 0x000a5c48   (est. exclave_iter_b)
 * Ghidra: void FUN_000a5c48(undefined8 param_1)
 * Generic table iteration wrapper binding callbacks (0x71f40, 0x8d350).
 * Confidence: low */
void exclave_iter_b(unsigned long table)
{
    cL4_table_iterate(table, (unsigned long)&method_id_71f40, (unsigned long)cb_8d350);
}

/* FUN_000a5c74 @ 0x000a5c74   (est. cL4_table_iterate)
 * Ghidra: void FUN_000a5c74(long param_1,code *param_2,code *param_3)
 * Iterates a table (param_1) invoking a pre-callback on each entry count
 * and a post-callback after; if the count is zero returns immediately.
 * Panics if the iteration count does not match the initial count.
 * Confidence: medium
 * Notes: generic iterator; callbacks param_2/param_3. */
unsigned long cL4_table_iterate(unsigned long table, unsigned long pre, unsigned long post)
{
    long count = *(long *)(table + 0x10);
    if (count == 0) {
        cL4_noop_4();
        return 0;
    }
    ((void (*)(unsigned long, void *))pre)((unsigned long)count, 0);
    cL4_noop_6();
    ((void (*)(void))post)();
    if (local_48 == 0) {
        cL4_noop_3();
        long i = reg_x8;
        do {
            long next = i + 1;
            if (__builtin_add_overflow(i, 1, &next))
                __builtin_trap();   /* 0xa5d40 */
            if (reg_x10 <= next) {
                cL4_obj_retain(table);
                cL4_obj_release(local_68);
                if (reg_x23 == count)
                    return 0;
                __builtin_trap();   /* 0xa5d1c */
            }
            i++;
        } while (*(long *)(reg_x9 + next * 8) == 0);
    }
    cL4_obj_retain(table);
    cL4_obj_release(local_68);
    __builtin_trap();               /* 0xa5d00 */
    return 0;
}

/* FUN_000a5d40 @ 0x000a5d40   (est. exclave_extent_a)
 * Ghidra: long FUN_000a5d40(ulong param_1)
 * If the low bit of param_1 is set, dereferences the tagged pointer to
 * obtain the base; returns (base+0x18) plus the signed 32-bit length stored
 * at base+0x18. Computes an exclave extent end.
 * Confidence: high
 * Notes: tagged-pointer deref; standard "value+length" extent idiom. */
unsigned long exclave_extent_a(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0x18) + (unsigned long)*(int *)(p + 0x18);
}

/* FUN_000a5d70 @ 0x000a5d70   (est. exclave_extent_b)
 * Ghidra: long FUN_000a5d70(ulong param_1)
 * Same tagged-extent idiom but reads the length from base+0x14.
 * Confidence: high */
unsigned long exclave_extent_b(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0x14) + (unsigned long)*(int *)(p + 0x14);
}

/* FUN_000a649c @ 0x000a649c   (est. exclave_extent_c)
 * Ghidra: long FUN_000a649c(ulong param_1)
 * Tagged-extent idiom reading the length from base+0x14.
 * Confidence: high */
unsigned long exclave_extent_c(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0x14) + (unsigned long)*(int *)(p + 0x14);
}

/* FUN_000a6894 @ 0x000a6894   (est. exclave_extent_d)
 * Ghidra: long FUN_000a6894(ulong param_1)
 * Tagged-extent idiom reading the length from base+0x14.
 * Confidence: high */
unsigned long exclave_extent_d(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0x14) + (unsigned long)*(int *)(p + 0x14);
}

/* FUN_000a68c4 @ 0x000a68c4   (est. exclave_extent_e)
 * Ghidra: long FUN_000a68c4(ulong param_1)
 * Tagged-extent idiom reading the length from base+0x10.
 * Confidence: high */
unsigned long exclave_extent_e(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0x10) + (unsigned long)*(int *)(p + 0x10);
}

/* FUN_000a68f4 @ 0x000a68f4   (est. exclave_extent_f)
 * Ghidra: long FUN_000a68f4(ulong param_1)
 * Tagged-extent idiom reading the length from base+8.
 * Confidence: high */
unsigned long exclave_extent_f(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 8) + (unsigned long)*(int *)(p + 8);
}

/* FUN_000a6b64 @ 0x000a6b64   (est. exclave_extent_g)
 * Ghidra: long FUN_000a6b64(ulong param_1)
 * Tagged-extent idiom reading the length from base+0x1c.
 * Confidence: high */
unsigned long exclave_extent_g(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0x1c) + (unsigned long)*(int *)(p + 0x1c);
}

/* FUN_000a6bb8 @ 0x000a6bb8   (est. exclave_extent_h)
 * Ghidra: long FUN_000a6bb8(ulong param_1)
 * Tagged-extent idiom reading the length from base+0xc.
 * Confidence: high */
unsigned long exclave_extent_h(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0xc) + (unsigned long)*(int *)(p + 0xc);
}

/* FUN_000a6be8 @ 0x000a6be8   (est. exclave_extent_i)
 * Ghidra: long FUN_000a6be8(ulong param_1)
 * Tagged-extent idiom reading the length from base+0x10.
 * Confidence: high */
unsigned long exclave_extent_i(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0x10) + (unsigned long)*(int *)(p + 0x10);
}

/* FUN_000a6c18 @ 0x000a6c18   (est. exclave_extent_j)
 * Ghidra: long FUN_000a6c18(ulong param_1)
 * Tagged-extent idiom reading the length from base+0x14.
 * Confidence: high */
unsigned long exclave_extent_j(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (unsigned long)(p + 0x14) + (unsigned long)*(int *)(p + 0x14);
}

/* FUN_000a5da0 @ 0x000a5da0   (est. exclave_dict_insert_record)
 * Ghidra: void FUN_000a5da0(long param_1,uint param_2,long *param_3)
 * Inserts a set of 0x50-byte records from param_1 into a Swift-style
 * dictionary (param_3). For each record it copies 0x49 bytes, hashes the
 * key pair, probes the hash table (open addressing), and on a free slot
 * writes the key (0x10-byte) and value (0x40-byte) and sets the occupancy
 * bit. On a full/conflicting slot it fails fatally via the Swift
 * NativeDictionary error path (string 0x5be800).
 * Confidence: medium
 * Notes: string s_Swift_NativeDictionary_swift_005be800; table DAT_004c1938. */
void exclave_dict_insert_record(unsigned long records, unsigned int flags, unsigned long *dict)
{
    unsigned long n = *(unsigned long *)(records + 0x10);
    unsigned long off = 0x20;
    unsigned int seed = flags;
    unsigned long i;
    for (i = 0; n != i; i++) {
        if (*(unsigned long *)(records + 0x10) <= i)
            __builtin_trap();       /* 0xa6034 */
        unsigned char rec[0x49];
        cL4_bcopy((unsigned long)rec, (void *)(records + off), 0x49);
        unsigned long key_lo = *(unsigned long *)(rec + 8);
        unsigned long key_hi = *(unsigned long *)(rec + 0x10);
        unsigned long fld0 = *(unsigned long *)(rec + 0);
        if (key_lo == 0) break;     /* empty record terminates */
        unsigned long hash = cL4_hash_pair(fld0, key_lo);
        unsigned long h = hash;
        unsigned long capacity = *(unsigned long *)(*dict + 0x10);
        unsigned long probe = (unsigned long)~hash & 1;
        if (__builtin_add_overflow(capacity, probe, &reg_x8))
            __builtin_trap();       /* 0xa6038 */
        unsigned long tbl = cL4_table_lookup(0x6502b8, &DAT_004c1938);
        unsigned long found = cL4_dict_probe(seed & 1, capacity + probe, tbl);
        if ((found & 1) != 0) {
            unsigned long h2 = cL4_hash_pair(fld0, key_lo);
            h = h2;
            if ((hash & 1) != (h2 & 1))
                cL4_dict_fault(0x6753a0);
        }
        if ((hash & 1) != 0) {
            unsigned long d = cL4_dict_init(0x672fa0, 0x66bca0, 0, 0);
            cL4_dict_bind();
            unsigned long d2 = d;
            cL4_obj_retain(d);
            unsigned long k = cL4_table_lookup(&DAT_0064c260, &DAT_004bbc30);
            unsigned long ok = cL4_record_lookup(k, &d2, k, 0x672fa0, 0);
            if ((ok & 1) == 0) {
                cL4_method_call((unsigned long)&local_rec);
                cL4_obj_release(records);
                cL4_error_tag(key_lo);
                cL4_obj_release(d2);
                return;
            }
            cL4_set_error(0x1e);
            cL4_err_log(0xd00000000000001b, 0x80000000005be800);
            cL4_fault_unwind(&fld0, &local_frame, 0x6753a0, 0x6756a8, 0x66e1b8);
            cL4_err_log(0x27, 0xe100000000000000);
            cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0, 0xe000000000000000,
                            s_Swift_NativeDictionary_swift_005be800, 0x1c, 2, 0x318, 0);
        }
        /* Insert into hash table at bucket h. */
        unsigned long base = *dict;
        unsigned long bits = *(unsigned long *)(base + 0x40);
        *(unsigned long *)(base + (h >> 6) * 8 + 0x40) =
            bits | (1UL << (h & 0x3f));
        unsigned long *key = (unsigned long *)(*(long *)(base + 0x30) + h * 0x10);
        key[0] = fld0;
        key[1] = key_lo;
        unsigned long *val = (unsigned long *)(*(long *)(base + 0x38) + h * 0x40);
        val[0] = rec[0];
        val[1] = *(unsigned long *)(rec + 8);
        val[2] = *(unsigned long *)(rec + 0x10);
        val[3] = *(unsigned long *)(rec + 0x18);
        val[4] = *(unsigned long *)(rec + 0x20);
        val[5] = *(unsigned long *)(rec + 0x28);
        val[6] = *(unsigned long *)(rec + 0x30);
        val[7] = *(unsigned long *)(rec + 0x38);
        if (__builtin_add_overflow(*(long *)(base + 0x10), 1, &reg_x8))
            __builtin_trap();       /* 0xa603c */
        *(long *)(base + 0x10) += 1;
        off += 0x50;
        seed = 1;
    }
    cL4_obj_release(records);
}

/* FUN_000a6104 @ 0x000a6104   (est. exclave_dict_insert_value)
 * Ghidra: void FUN_000a6104(long param_1,uint param_2,long *param_3)
 * Inserts a set of {key-lo, key-hi, value} triples from param_1 into a
 * dictionary (param_3) using open addressing; each entry occupies three
 * words in the source. Fails fatally on a full table via the Swift
 * NativeDictionary path.
 * Confidence: medium
 * Notes: same dict/string refs as 0xa5da0; table DAT_004c1908. */
void exclave_dict_insert_value(unsigned long records, unsigned int flags, unsigned long *dict)
{
    unsigned long i = 0;
    unsigned long n = *(unsigned long *)(records + 0x10);
    unsigned long *slot = (unsigned long *)(records + 0x30);
    for (;;) {
        if (n == i) {
            cL4_obj_release(records);
            return;
        }
        if (*(unsigned long *)(records + 0x10) <= i)
            __builtin_trap();       /* 0xa6320 */
        unsigned long k0 = slot[-2];
        unsigned long k1 = slot[-1];
        unsigned long v = *slot;
        unsigned long base = *dict;
        cL4_obj_retain(k1);
        cL4_obj_retain(v);
        unsigned long hash = cL4_hash_pair(k0, k1);
        unsigned long h = hash;
        unsigned long capacity = *(unsigned long *)(base + 0x10);
        unsigned long probe = (unsigned long)~hash & 1;
        if (__builtin_add_overflow(capacity, probe, &reg_x8))
            __builtin_trap();       /* 0xa6324 */
        unsigned long tbl = cL4_table_lookup(0x650290, &DAT_004c1908);
        unsigned long found = cL4_dict_probe(flags & 1, capacity + probe, tbl);
        if ((found & 1) != 0) {
            unsigned long h2 = cL4_hash_pair(k0, k1);
            h = h2;
            if ((hash & 1) != (h2 & 1))
                cL4_dict_fault(0x6753a0);
        }
        if ((hash & 1) != 0) break;
        unsigned long b2 = *dict;
        *(unsigned long *)(b2 + (h >> 6) * 8 + 0x40) =
            *(unsigned long *)(b2 + (h >> 6) * 8 + 0x40) | (1UL << (h & 0x3f));
        unsigned long *key = (unsigned long *)(*(long *)(b2 + 0x30) + h * 0x10);
        key[0] = k0;
        key[1] = k1;
        *(unsigned long *)(*(long *)(b2 + 0x38) + h * 8) = v;
        if (__builtin_add_overflow(*(long *)(b2 + 0x10), 1, &reg_x8))
            __builtin_trap();       /* 0xa6328 */
        *(long *)(b2 + 0x10) += 1;
        slot += 3;
        i++;
        flags = 1;
    }
    /* Full-table path. */
    unsigned long d = cL4_dict_init(0x672fa0, 0x66bca0, 0, 0);
    cL4_dict_bind();
    unsigned long d2 = d;
    cL4_obj_retain(d);
    unsigned long k = cL4_table_lookup(&DAT_0064c260, &DAT_004bbc30);
    unsigned long ok = cL4_record_lookup(k, &d2, k, 0x672fa0, 0);
    if ((ok & 1) == 0) {
        cL4_obj_release(records);
        cL4_error_tag(k1);
        cL4_obj_release(v);
        cL4_obj_release(d2);
        return;
    }
    cL4_set_error(0x1e);
    cL4_err_log(0xd00000000000001b, 0x80000000005be800);
    cL4_fault_unwind(&k0, &local_frame, 0x6753a0, 0x6756a8, 0x66e1b8);
    cL4_err_log(0x27, 0xe100000000000000);
    cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0, 0xe000000000000000,
                    s_Swift_NativeDictionary_swift_005be800, 0x1c, 2, 0x318, 0);
}

/* FUN_000a63f0 @ 0x000a63f0   (est. cL4_assign)
 * Ghidra: undefined8 FUN_000a63f0(undefined8 param_1,undefined8 param_2)
 * Indirect assignment helper: calls a global method pointer with (param_2,
 * param_1) and returns param_2. Used to store an object field.
 * Confidence: low
 * Notes: global fn ptr _DAT_72ad2dc8528d2e98. */
unsigned long cL4_assign(unsigned long a, unsigned long b)
{
    ((void (*)(unsigned long, unsigned long))&g_assign_fn)(b, a);
    return b;
}

/* FUN_000a6444 @ 0x000a6444   (est. cL4_method_call)
 * Ghidra: undefined8 FUN_000a6444(undefined8 param_1)
 * Calls a global method pointer with no arguments (besides the implicit
 * receiver) and returns param_1.
 * Confidence: low
 * Notes: global fn ptr _DAT_72ad2dc8528d2e90. */
unsigned long cL4_method_call(unsigned long a)
{
    ((void (*)(void))&g_method_fn)();
    return a;
}

/* FUN_000a6490 @ 0x000a6490   (est. exclave_metadata_get)
 * Ghidra: void FUN_000a6490(void)
 * Fetches the class/type metadata for the object at 0x650090.
 * Confidence: low */
void exclave_metadata_get(void)
{
    cL4_metadata(0x650090);
}

/* FUN_000a64d8 @ 0x000a64d8   (est. exclave_desc_parse_thunk_a)
 * Ghidra: void FUN_000a64d8(undefined8 param_1,undefined8 param_2)
 * Wrapper around exclave_desc_parse (0xa3c00) passing the object's fields
 * at x20+0x10/0x18 as the descriptor inputs.
 * Confidence: low */
void exclave_desc_parse_thunk_a(unsigned long out, unsigned long id)
{
    long _err = 0;
    exclave_desc_parse(&out, *(unsigned long *)(receiver + 0x10), *(unsigned long *)(receiver + 0x18), id, &_err);
}

/* FUN_000a64dc @ 0x000a64dc   (est. exclave_desc_parse_thunk_b)
 * Ghidra: void FUN_000a64dc(undefined8 param_1,undefined8 param_2)
 * Same wrapper as 0xa64d8; alternate entry.
 * Confidence: low */
void exclave_desc_parse_thunk_b(unsigned long out, unsigned long id)
{
    long _err = 0;
    exclave_desc_parse(&out, *(unsigned long *)(receiver + 0x10), *(unsigned long *)(receiver + 0x18), id, &_err);
}

/* FUN_000a64f8 @ 0x000a64f8   (est. exclave_kind_bits)
 * Ghidra: ulong FUN_000a64f8(ulong *param_1)
 * Returns the top 3 bits of the descriptor word — the object kind field.
 * Confidence: high
 * Notes: *param_1 >> 0x3d. */
unsigned long exclave_kind_bits(unsigned long *p)
{
    return *p >> 0x3d;
}

/* FUN_000a651c @ 0x000a651c   (est. exclave_msg_obtain)
 * Ghidra: void FUN_000a651c(undefined1 (*param_1) [16])
 * Obtains a 16-byte message value by calling the self vtable method at
 * offset 0x68 and stores it at *param_1.
 * Confidence: low */
void exclave_msg_obtain(void *out)
{
    cL4_self();
    unsigned long v = (**(unsigned long (**)(void))(reg_x16 + 0x68))();
    __builtin_memcpy(out, &v, 16);
}

/* FUN_000a6560 @ 0x000a6560   (est. exclave_flag_get)
 * Ghidra: void FUN_000a6560(byte *param_1)
 * Reads a boolean flag via the self vtable method at offset 0x80 and stores
 * its low bit at *param_1.
 * Confidence: low */
void exclave_flag_get(unsigned char *out)
{
    cL4_self();
    unsigned char b = (**(unsigned char (**)(void))(reg_x16 + 0x80))();
    *out = b & 1;
}

/* FUN_000a65a4 @ 0x000a65a4   (est. exclave_flag_set)
 * Ghidra: void FUN_000a65a4(undefined1 *param_1)
 * Passes *param_1 to the self vtable method at offset 0x88 (a setter).
 * Confidence: low */
void exclave_flag_set(unsigned char *v)
{
    cL4_self();
    (**(void (**)(unsigned char))(reg_x16 + 0x88))(*v);
}

/* FUN_000a6834 @ 0x000a6834   (est. exclave_metadata_get2)
 * Ghidra: void FUN_000a6834(void)
 * Fetches the class/type metadata for the object at 0x6501d8.
 * Confidence: low */
void exclave_metadata_get2(void)
{
    cL4_metadata(0x6501d8);
}

/* FUN_000a6840 @ 0x000a6840   (est. cL4_assign2)
 * Ghidra: undefined8 FUN_000a6840(undefined8 param_1,undefined8 param_2)
 * Indirect assignment helper calling a global method pointer with (param_2,
 * param_1); returns param_2. Variant of 0xa63f0.
 * Confidence: low
 * Notes: global fn ptr _DAT_aa2803e838002f2f. */
unsigned long cL4_assign2(unsigned long a, unsigned long b)
{
    ((void (*)(unsigned long, unsigned long))&g_assign_fn2)(b, a);
    return b;
}

/* FUN_000a6924 @ 0x000a6924   (est. exclave_bit_clear)
 * Ghidra: void FUN_000a6924(long param_1)
 * Clears a bit in the bitset at param_1+0x40, selected by the byte at
 * param_1+0x20 (masked to 6 bits).
 * Confidence: high */
void exclave_bit_clear(unsigned long obj)
{
    unsigned long bit = *(unsigned char *)(obj + 0x20) & 0x3f;
    cL4_bit_clear(obj + 0x40, ~(-1L << bit));
}

/* FUN_000a6b2c @ 0x000a6b2c   (est. exclave_begin_wrapper)
 * Ghidra: void FUN_000a6b2c(undefined8 *param_1,undefined8 *param_2)
 * Wrapper that calls exclave_load_begin (0xa3a84) with *param_2 and stores
 * the result in *param_1 on success.
 * Confidence: low */
void exclave_begin_wrapper(unsigned long *out, unsigned long *in)
{
    exclave_load_begin(*in);
    if (fail_reg == 0)
        *out = *in;
}

/* FUN_000a6b94 @ 0x000a6b94   (est. exclave_lookup_thunk_a)
 * Ghidra: void FUN_000a6b94(undefined8 param_1,undefined8 param_2)
 * Wrapper calling exclave_load_lookup (0xa3ad4) with the object fields at
 * x20+0x10..0x28.
 * Confidence: low */
void exclave_lookup_thunk_a(unsigned long out, unsigned long id)
{
    exclave_load_lookup(&out, *(unsigned long *)(receiver + 0x10), *(unsigned long *)(receiver + 0x18),
                        *(unsigned long *)(receiver + 0x20), *(unsigned long *)(receiver + 0x28), id);
}

/* FUN_000a6b98 @ 0x000a6b98   (est. exclave_lookup_thunk_b)
 * Ghidra: void FUN_000a6b98(undefined8 param_1,undefined8 param_2)
 * Same wrapper as 0xa6b94; alternate entry.
 * Confidence: low */
void exclave_lookup_thunk_b(unsigned long out, unsigned long id)
{
    exclave_load_lookup(&out, *(unsigned long *)(receiver + 0x10), *(unsigned long *)(receiver + 0x18),
                        *(unsigned long *)(receiver + 0x20), *(unsigned long *)(receiver + 0x28), id);
}

/* FUN_000a6c48 @ 0x000a6c48   (est. cL4_array_append)
 * Ghidra: undefined8 FUN_000a6c48(undefined8 param_1,undefined8 param_2)
 * Array append via a global method pointer; returns param_2.
 * Confidence: low
 * Notes: global fn ptr _DAT_910083ffa9417c0d. */
unsigned long cL4_array_append(unsigned long a, unsigned long b)
{
    ((void (*)(unsigned long, unsigned long))&g_append_fn)(b, a);
    return b;
}

/* FUN_000a6c9c @ 0x000a6c9c   (est. cL4_vtbl_call)
 * Ghidra: undefined8 FUN_000a6c9c(undefined8 param_1,undefined8 param_2)
 * Resolves a vtable from the table at DAT_0064e840/DAT_004c1930 and calls
 * its method at offset 0x10 with (param_2, param_1, node); returns param_2.
 * Confidence: low */
unsigned long cL4_vtbl_call(unsigned long a, unsigned long b)
{
    unsigned long node = cL4_table_lookup(&DAT_0064e840, &DAT_004c1930);
    (**(void (**)(unsigned long, unsigned long, unsigned long))(*(long *)(node - 8) + 0x10))(b, a, node);
    return b;
}

/* thunk_FUN_000a17f8 @ 0x000a6d04   (est. exclave_err_dispatch)
 * Ghidra: void thunk_FUN_000a17f8(undefined8 param_1,undefined8 param_2)
 * Dispatches an error: if the error frame at x6+0x10 is empty, logs the
 * "not found" string and the fatal-error tuple; if it holds one entry,
 * returns that entry retained; otherwise it logs a "out of range" style
 * error with the index and faults.
 * Confidence: medium
 * Notes: string 0x5c1f60; uses 0xa6d08 (error word), 0xa6d44 (fatal tuple). */
void exclave_err_dispatch(unsigned long a, unsigned long b)
{
    if (*(long *)(reg_x6 + 0x10) == 0) {
        cL4_noop_8(b);
        cL4_obj_retain(0);
        exclave_err_word();
        cL4_err_log();
        cL4_noop_16();
        cL4_fatal_tuple();
        cL4_noop_11();
    } else {
        unsigned long v = *(unsigned long *)(reg_x6 + 0x20);
        if (*(long *)(reg_x6 + 0x10) == 1) {
            cL4_obj_retain(v);
            return;
        }
        cL4_noop_12();
        unsigned long r = cL4_obj_retain(v);
        cL4_noop_13(r, 0x80000000005c1f60);
        cL4_err_log();
        cL4_noop_16();
        cL4_fatal_tuple();
    }
    cL4_fatal_error(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

/* FUN_000a6d08 @ 0x000a6d08   (est. exclave_err_word)
 * Ghidra: undefined1 [16] FUN_000a6d08(void)
 * Returns the two-word error string "; found zero." used in error paths.
 * Confidence: high
 * Notes: 0x20646e756f66203b = "; found ", 0xed00002e6f72657a = "zero...". */
unsigned long exclave_err_word(void)
{
    return 0x20646e756f66203b;      /* "; found " */
}

/* FUN_000a6d2c @ 0x000a6d2c   (est. cL4_noop_15)
 * Ghidra: void FUN_000a6d2c(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_15()
{
}

/* FUN_000a6d44 @ 0x000a6d44   (est. cL4_fatal_tuple)
 * Ghidra: undefined1 [16] FUN_000a6d44(void)
 * Returns the {s_Fatal_error_005accd0, 0xb} prefix tuple for fatal errors.
 * Confidence: high */
unsigned long cL4_fatal_tuple(void)
{
    return (unsigned long)s_Fatal_error_005accd0;
}

/* FUN_000a6d58 @ 0x000a6d58   (est. cL4_fatal_prefix)
 * Ghidra: char * FUN_000a6d58(void)
 * Returns the "Fatal error" prefix string pointer.
 * Confidence: high */
const char *cL4_fatal_prefix(void)
{
    return s_Fatal_error_005accd0;
}

/* FUN_000a6d70 @ 0x000a6d70   (est. cL4_noop_14)
 * Ghidra: void FUN_000a6d70(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_14()
{
}

/* FUN_000a6d88 @ 0x000a6d88   (est. cL4_msg_ref)
 * Ghidra: undefined1 [16] FUN_000a6d88(void)
 * Returns a 16-byte value zero-extended from 0xf6308 (a message reference).
 * Confidence: low */
unsigned long cL4_msg_ref(void)
{
    return 0xf6308;
}

/* FUN_000a6dac @ 0x000a6dac   (est. cL4_record_write)
 * Ghidra: void FUN_000a6dac(void)
 * Writes a 0x40-byte record from a set of stack-supplied words into the
 * table slot at x22 + x19*0x40, along with the object header field.
 * Confidence: low
 * Notes: reads 6+ words from the caller's stack frame. */
void cL4_record_write(unsigned long dst, unsigned long idx, ...)
{
    unsigned long base = reg_x22 + idx * 0x40;
    unsigned long w0 = *(unsigned long *)(reg_x9 + 0x29);
    *(unsigned long *)(base + 0x51) = *(unsigned long *)(reg_x9 + 0x31);
    *(unsigned long *)(base + 0x49) = w0;
    *(unsigned long *)(base + 0x38) = stack_c8;
    *(unsigned long *)(base + 0x30) = stack_c0;
    *(unsigned long *)(base + 0x48) = stack_d8;
    *(unsigned long *)(base + 0x40) = stack_d0;
    *(unsigned long *)(base + 0x28) = stack_b8;
    *(unsigned long *)(base + 0x20) = stack_b0;
    *(unsigned long *)(dst + 0x10) = reg_x25;
}

/* FUN_000a6ddc @ 0x000a6ddc   (est. cL4_record_copy)
 * Ghidra: void FUN_000a6ddc(void)
 * Copies a 0x40-byte record from x24+x23 into the object at x19 and calls
 * the assign helper (0xa63f0) to store a field pair.
 * Confidence: low */
void cL4_record_copy(void)
{
    unsigned long *src = (unsigned long *)(reg_x24 + reg_x23);
    unsigned long w0 = src[0], w1 = src[1], w2 = src[2], w3 = src[3], w4 = src[4], w5 = src[5];
    unsigned long hdr = *(unsigned long *)((long)src + 0x29);
    *(unsigned long *)(reg_x19 + 0x31) = *(unsigned long *)((long)src + 0x31);
    *(unsigned long *)(reg_x19 + 0x29) = hdr;
    unsigned long pair[2] = {w0, w1};
    cL4_assign((unsigned long)pair, (unsigned long)&stack_frame);
}

/* FUN_000a6e08 @ 0x000a6e08   (est. cL4_noop_6)
 * Ghidra: void FUN_000a6e08(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_6()
{
}

/* FUN_000a6e14 @ 0x000a6e14   (est. cL4_noop_7)
 * Ghidra: void FUN_000a6e14(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_7()
{
}

/* FUN_000a6e20 @ 0x000a6e20   (est. cL4_noop_8)
 * Ghidra: void FUN_000a6e20(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_8()
{
}

/* FUN_000a6e30 @ 0x000a6e30   (est. cL4_noop_5)
 * Ghidra: void FUN_000a6e30(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_5()
{
}

/* FUN_000a6e40 @ 0x000a6e40   (est. cL4_noop_10)
 * Ghidra: void FUN_000a6e40(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_10()
{
}

/* FUN_000a6e50 @ 0x000a6e50   (est. cL4_noop_11)
 * Ghidra: void FUN_000a6e50(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_11()
{
}

/* FUN_000a6e60 @ 0x000a6e60   (est. cL4_noop_barrier)
 * Ghidra: void FUN_000a6e60(void)
 * Empty stub function used as a sequencing barrier.
 * Confidence: low */
void cL4_noop_barrier()
{
}

/* FUN_000a6e70 @ 0x000a6e70   (est. cL4_noop_13)
 * Ghidra: void FUN_000a6e70(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_13()
{
}

/* FUN_000a6e80 @ 0x000a6e80   (est. cL4_retain_pair)
 * Ghidra: void FUN_000a6e80(undefined8 param_1,undefined8 param_2)
 * Retains param_2 (storing both args to the stack first). Returns nothing.
 * Confidence: low */
void cL4_retain_pair(unsigned long a, unsigned long b)
{
    unsigned long sa = a, sb = b;
    cL4_obj_retain(b);
}

/* FUN_000a6e9c @ 0x000a6e9c   (est. cL4_extent)
 * Ghidra: undefined1 [16] FUN_000a6e9c(long param_1)
 * Returns a 16-byte {&stack+8, param_1+0x20} extent pair.
 * Confidence: low */
unsigned long cL4_extent(unsigned long obj)
{
    return (unsigned long)(obj + 0x20);
}

/* FUN_000a6eb4 @ 0x000a6eb4   (est. cL4_noop)
 * Ghidra: void FUN_000a6eb4(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop(void)
{
}

/* FUN_000a6ecc @ 0x000a6ecc   (est. cL4_noop_9)
 * Ghidra: void FUN_000a6ecc(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_9()
{
}

/* FUN_000a6ee4 @ 0x000a6ee4   (est. cL4_noop_12)
 * Ghidra: void FUN_000a6ee4(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_12()
{
}

/* FUN_000a6ef0 @ 0x000a6ef0   (est. cL4_noop_3)
 * Ghidra: void FUN_000a6ef0(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_3()
{
}

/* FUN_000a6f08 @ 0x000a6f08   (est. exclave_msg_copy)
 * Ghidra: void FUN_000a6f08(undefined8 param_1)
 * Copies param_1 into the message frame at x20+0x18 (0x21 bytes, kind 0).
 * Confidence: low */
void exclave_msg_copy(unsigned long src)
{
    cL4_msg_copy(receiver + 0x18, (void *)src, 0x21, 0);
}

/* FUN_000a6f20 @ 0x000a6f20   (est. cL4_assert_le1)
 * Ghidra: void FUN_000a6f20(ulong param_1)
 * Asserts 1 < param_1 via the bounds-assert helper.
 * Confidence: high */
void cL4_assert_le1(unsigned long v)
{
    cL4_assert_le2(1 < v);
}

/* FUN_000a6f38 @ 0x000a6f38   (est. cL4_assert_le2)
 * Ghidra: void FUN_000a6f38(ulong param_1)
 * Asserts 1 < param_1 via the second bounds-assert helper.
 * Confidence: high */
void cL4_assert_le2(unsigned long v)
{
    (void)v;
}

/* FUN_000a6f50 @ 0x000a6f50   (est. cL4_assert_capacity)
 * Ghidra: void FUN_000a6f50(void)
 * Asserts capacity >= count+1 for the table at x22.
 * Confidence: low */
void cL4_assert_capacity(void)
{
    cL4_assert_le2((unsigned long)(*(long *)(reg_x22 + 0x10) + 1));
}

/* FUN_000a6f68 @ 0x000a6f68   (est. cL4_noop_1)
 * Ghidra: void FUN_000a6f68(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_1()
{
}

/* FUN_000a6f74 @ 0x000a6f74   (est. cL4_noop_2)
 * Ghidra: void FUN_000a6f74(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_2()
{
}

/* FUN_000a6f88 @ 0x000a6f88   (est. cL4_noop_17)
 * Ghidra: void FUN_000a6f88(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_17()
{
}

/* FUN_000a6f9c @ 0x000a6f9c   (est. cL4_frame_advance)
 * Ghidra: void FUN_000a6f9c(void)
 * Empty stub function used to advance a frame cursor.
 * Confidence: low */
void cL4_frame_advance()
{
}

/* FUN_000a6fb0 @ 0x000a6fb0   (est. cL4_err_code)
 * Ghidra: undefined8 FUN_000a6fb0(void)
 * Returns a constant error code 0xd000000000000015.
 * Confidence: high */
unsigned long cL4_err_code(void)
{
    return 0xd000000000000015;
}

/* FUN_000a6fbc @ 0x000a6fbc   (est. cL4_noop_16)
 * Ghidra: void FUN_000a6fbc(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_16()
{
}

/* FUN_000a6fc8 @ 0x000a6fc8   (est. cL4_slot_fetch)
 * Ghidra: undefined8 FUN_000a6fc8(long param_1)
 * Fetches the table slot at x20+0x38 + param_1*8.
 * Confidence: high */
unsigned long cL4_slot_fetch(unsigned long idx)
{
    return *(unsigned long *)(*(long *)(receiver + 0x38) + idx * 8);
}

/* FUN_000a6fd4 @ 0x000a6fd4   (est. cL4_noop_18)
 * Ghidra: void FUN_000a6fd4(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_18()
{
}

/* FUN_000a6fe0 @ 0x000a6fe0   (est. cL4_noop_4)
 * Ghidra: void FUN_000a6fe0(void)
 * Empty stub function.
 * Confidence: low */
void cL4_noop_4()
{
}

/* FUN_000a6fec @ 0x000a6fec   (est. exclave_map_resolve)
 * Ghidra: undefined8 FUN_000a6fec(void)
 * Resolves a value from a dictionary: reads the map head at x20+0x10; if
 * the map is empty or the probe fails, returns 0; otherwise returns the
 * resolved entry's +0x10 word.
 * Confidence: medium */
unsigned long exclave_map_resolve(void)
{
    unsigned long map = *(long *)(receiver + 0x10);
    unsigned long pair[2];
    if ((*(long *)(map + 0x10) == 0) ||
        ((pair[0] = thunk_72664(), (pair[1] & 1) == 0))) {
        return 0;
    }
    return *(unsigned long *)(*(long *)(*(long *)(map + 0x38) + pair[0] * 8) + 0x10);
}

/* FUN_000a7030 @ 0x000a7030   (est. exclave_dict_set)
 * Ghidra: void FUN_000a7030(undefined8 param_1,undefined8 param_2,undefined8 param_3,
 *        undefined8 param_4, undefined8 param_5)
 * Sets a dictionary value: pins a frame, looks up the key; if present,
 * wraps a message frame and stores the (key,value) via cL4_dict_value_store;
 * otherwise faults.
 * Confidence: low */
void exclave_dict_set(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e)
{
    unsigned long frame[3];
    cL4_frame_pin((unsigned long *)(receiver + 0x10), frame);
    unsigned long r = cL4_key_lookup2(a, *(unsigned long *)(receiver + 0x10));
    if (reg_x1 == 0) {
        cL4_msg_copy(receiver + 0x10, frame, 0x21, 0);
        cL4_obj_retain(c);
        cL4_obj_retain(e);
        cL4_dict_value_store(b, c, d, e, a);
        cL4_msg_finish(frame);
        return;
    }
    exclave_release_or_return(0, 0, 0, 0);
    __builtin_trap();               /* 0xa70e4 */
}

/* FUN_000a70e4 @ 0x000a70e4   (est. exclave_dict_remove)
 * Ghidra: void FUN_000a70e4(undefined8 param_1,undefined8 param_2)
 * Removes a dictionary value: pins a frame, looks up the key; if found
 * wraps a frame and removes it via cL4_dict_remove; otherwise faults.
 * Confidence: low */
void exclave_dict_remove(unsigned long a, unsigned long b)
{
    unsigned long frame[3];
    cL4_frame_pin((unsigned long *)(receiver + 0x18), frame);
    unsigned long r = cL4_key_lookup(a, *(unsigned long *)(receiver + 0x18));
    if (r == 0) {
        cL4_msg_copy(receiver + 0x18, frame, 0x21, 0);
        cL4_dict_remove(b, a);
        cL4_msg_finish(frame);
        return;
    }
    __builtin_trap();               /* 0xa7164 */
}

/* FUN_000a7164 @ 0x000a7164   (est. exclave_dict_enumerate)
 * Ghidra: void FUN_000a7164(void)
 * Enumerates the dictionary at x20: iterates the occupancy bitset, and for
 * each set bit resolves the key/value, runs the callback (0xa75b0) to build
 * a stack-shot entry, and inserts it into a second dictionary (lVar6).
 * Confidence: medium
 * Notes: uses bit reversal (LZCOUNT) to pick occupied slots. */
void exclave_dict_enumerate(void)
{
    unsigned long seed = cL4_type_desc();
    unsigned long dict = cL4_reg_entry(&DAT_00657778, 0x677790, seed, 0x6718b8);
    unsigned long frame[3];
    cL4_frame_pin((unsigned long *)(receiver + 0x10), frame);
    unsigned long map = *(long *)(receiver + 0x10);
    unsigned long bit = 1UL << (*(unsigned char *)(map + 0x20) & 0x3f);
    unsigned long word = 0xffffffffffffffff;
    if ((*(unsigned char *)(map + 0x20) & 0x3f) < 6)
        word = ~(-1L << (bit & 0x3f));
    word &= *(unsigned long *)(map + 0x40);
    cL4_obj_retain(0);
    unsigned long frame2[3];
    cL4_frame_pin((unsigned long *)(receiver + 0x18), frame2);
    unsigned long idx = 0;
    unsigned long val;
    do {
        while (word == 0) {
            if (__builtin_add_overflow(idx, 1, &idx))
                __builtin_trap();   /* 0xa73f4 */
            if ((long)((bit + 0x3f) >> 6) <= idx) {
                cL4_obj_release(map);
                unsigned long r = cL4_block_alloc(0x6502e0, 0x18, 7);
                *(long *)(r + 0x10) = dict;
                return;
            }
            word = ((unsigned long *)(map + 0x40))[idx];
        }
        /* find lowest set bit of word (via bit-reverse + count-leading-zeros) */
        unsigned long rev = (word & 0xaaaaaaaaaaaaaaaa) >> 1 | (word & 0x5555555555555555) << 1;
        rev = (rev & 0xcccccccccccccccc) >> 2 | (rev & 0x3333333333333333) << 2;
        rev = (rev & 0xf0f0f0f0f0f0f0f0) >> 4 | (rev & 0x0f0f0f0f0f0f0f0f) << 4;
        rev = (rev & 0xff00ff00ff00ff00) >> 8 | (rev & 0x00ff00ff00ff00ff) << 8;
        rev = (rev & 0xffff0000ffff0000) >> 16 | (rev & 0x0000ffff0000ffff) << 16;
        unsigned long bucket = __builtin_clzll(rev >> 32 | rev << 32) | idx << 6;
        unsigned long key = *(unsigned long *)(*(long *)(map + 0x30) + bucket * 8);
        unsigned long *ent = (unsigned long *)(*(long *)(map + 0x38) + bucket * 0x20);
        unsigned long v0 = ent[0], v1 = ent[1], v2 = ent[2], v3 = ent[3];
        unsigned long fmap = *(long *)(receiver + 0x18);
        unsigned long fval;
        if (*(long *)(fmap + 0x10) == 0) {
            fval = 0;
        } else {
            unsigned long pr[2] = {thunk_72664(), 0};
            if ((pr[1] & 1) == 0) fval = 0;
            else fval = *(unsigned long *)(*(long *)(fmap + 0x38) + pr[0] * 8);
        }
        cL4_block_alloc(seed, 0x38, 7);
        cL4_obj_retain(v1);
        cL4_obj_retain(v3);
        unsigned long sv = exclave_stackshot_build(v0, v1, v2, v3, fval);
        unsigned long hseed = cL4_dict_seed(dict);
        unsigned long pr2[2] = {thunk_72664(key), 0};
        unsigned long h = pr2[0];
        unsigned long cap = *(long *)(dict + 0x10);
        unsigned long probe = (unsigned long)~pr2[1] & 1;
        if (__builtin_add_overflow(cap, probe, &reg_x8))
            __builtin_trap();       /* 0xa73f8 */
        unsigned long tbl = cL4_table_lookup(0x6502c0, &DAT_004c1940);
        unsigned long found = cL4_dict_probe(hseed, cap + probe, tbl);
        if ((found & 1) != 0) {
            unsigned long pr3[2] = {thunk_72664(key), 0};
            h = pr3[0];
            if ((pr2[1] & 1) != (pr3[1] & 1))
                cL4_dict_fault(0x677790);
        }
        word &= word - 1;
        if ((pr2[1] & 1) == 0) {
            cL4_dict_insert(h, key, sv, dict);
        } else {
            unsigned long old = *(unsigned long *)(*(long *)(dict + 0x38) + h * 8);
            *(unsigned long *)(*(long *)(dict + 0x38) + h * 8) = sv;
            cL4_obj_release(old);
        }
    } while (1);
}

/* FUN_000a7408 @ 0x000a7408   (est. exclave_dict_drop)
 * Ghidra: void FUN_000a7408(void)
 * Drops the two dictionary references at x20+0x10 and x20+0x18.
 * Confidence: low */
void exclave_dict_drop(void)
{
    cL4_error_tag(*(unsigned long *)(receiver + 0x10));
    cL4_error_tag(*(unsigned long *)(receiver + 0x18));
}

/* FUN_000a7430 @ 0x000a7430   (est. exclave_dict_dealloc_a)
 * Ghidra: void FUN_000a7430(void)
 * Drops the two dict references then runs teardown. Alternate entry.
 * Confidence: low */
void exclave_dict_dealloc_a(void)
{
    exclave_dict_drop();
    cL4_block_alloc_fixed(0, 0, 0);
}

/* FUN_000a7434 @ 0x000a7434   (est. exclave_dict_dealloc_b)
 * Ghidra: void FUN_000a7434(void)
 * Same as 0xa7430. Alternate entry.
 * Confidence: low */
void exclave_dict_dealloc_b(void)
{
    exclave_dict_drop();
    cL4_block_alloc_fixed(0, 0, 0);
}

/* FUN_000a7458 @ 0x000a7458   (est. exclave_dict_alloc_init)
 * Ghidra: undefined8 FUN_000a7458(void)
 * Allocates a block and initializes it via 0xa7490; returns the block.
 * Confidence: low */
unsigned long exclave_dict_alloc_init(void)
{
    unsigned long blk = cL4_block_alloc(0, 0, 7);
    exclave_dict_init(blk);
    return blk;
}

/* FUN_000a7490 @ 0x000a7490   (est. exclave_dict_init)
 * Ghidra: void FUN_000a7490(void)
 * Initializes the two dictionary slots of the object at x20: slot +0x10 is
 * bound to the table at 0x64e1e0/0x4bf1a0, and slot +0x18 to 0x676480 —
 * both through the registry entry creator.
 * Confidence: low */
void exclave_dict_init(unsigned long obj)
{
    unsigned long t = cL4_table_lookup(0x64e1e0, &DAT_004bf1a0);
    unsigned long r = cL4_reg_entry(&DAT_00657778, 0x677790, t, 0x6718b8);
    *(unsigned long *)(obj + 0x10) = r;
    unsigned long r2 = cL4_reg_entry(&DAT_00657778, 0x677790, 0x676480, 0x6718b8);
    *(unsigned long *)(obj + 0x18) = r2;
}

/* FUN_000a7524 @ 0x000a7524   (est. exclave_dict_alloc_init2)
 * Ghidra: undefined8 FUN_000a7524(void)
 * Allocates a 0x20-byte block at 0x650340 and initializes it; returns it.
 * Confidence: low */
unsigned long exclave_dict_alloc_init2(void)
{
    unsigned long blk = cL4_block_alloc(0x650340, 0x20, 7);
    exclave_dict_init(blk);
    return blk;
}

/* FUN_000a7560 @ 0x000a7560   (est. exclave_slot_drop_a)
 * Ghidra: void FUN_000a7560(void)
 * Drops the reference at x20+0x10 then runs teardown.
 * Confidence: low */
void exclave_slot_drop_a(void)
{
    cL4_error_tag(*(unsigned long *)(receiver + 0x10));
    cL4_block_alloc_fixed(0, 0, 0);
}

/* FUN_000a7564 @ 0x000a7564   (est. exclave_slot_drop_b)
 * Ghidra: void FUN_000a7564(void)
 * Same as 0xa7560. Alternate entry.
 * Confidence: low */
void exclave_slot_drop_b(void)
{
    cL4_error_tag(*(unsigned long *)(receiver + 0x10));
    cL4_block_alloc_fixed(0, 0, 0);
}

/* FUN_000a758c @ 0x000a758c   (est. exclave_map_resolve_wrapper)
 * Ghidra: void FUN_000a758c(void)
 * Thin wrapper that calls exclave_map_resolve (0xa6fec) and discards the
 * result.
 * Confidence: low */
void exclave_map_resolve_wrapper(void)
{
    exclave_map_resolve();
}

/* FUN_000a75b0 @ 0x000a75b0   (est. exclave_stackshot_build)
 * Ghidra: long FUN_000a75b0(undefined8 param_1,undefined8 param_2,undefined8 param_3,
 *        long param_4, undefined8 param_5)
 * Builds a stack-shot descriptor: computes the total byte size of the
 * image's frames (sum of each component's +0x10 word), allocates a
 * 0x30-entry frame array and a 0x40-byte header, then walks the frame
 * records, computing per-frame extents and storing them. Returns the
 * descriptor object at x20.
 * Confidence: high (verified vs decompile+disasm, VB2 sweep; FUN_000e250c callee fixed)
 * Notes: "Stacksho..." strings 0x5c2150/0x5c2190; fatal on missing base. */
long exclave_stackshot_build(unsigned long a, unsigned long b, unsigned long c, long d, unsigned long e)
{
    unsigned long tbl = cL4_image_tbl();
    cL4_error_tag(b);
    unsigned long n = *(unsigned long *)(tbl + 0x10);
    unsigned long buf = cL4_buf_alloc(n, 0xffffffffffffffff);
    *(unsigned long *)(receiver + 0x18) = buf;
    *(unsigned long *)(receiver + 0x20) = n;
    unsigned long t = *(unsigned long *)(tbl + 0x10);
    if (t != 0) {
        if (n < t) __builtin_trap();    /* 0xa7ab8 */
        cL4_bcopy(buf, 0);
    }
    if (buf == 0) {
        cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0xd00000000000001d,
                        (unsigned long)(s_InternalExclaveLauncher_Stacksho_005c2150 + 0x20) | 0x8000000000000000,
                        s_InternalExclaveLauncher_Stacksho_005c2150, 0x31, 2, 0x84, 0);
    }
    long cnt = *(long *)(d + 0x10);
    unsigned long fbuf = cL4_buf_alloc(cnt * 0x30, 0xffffffffffffffff);
    *(unsigned long *)(receiver + 0x28) = fbuf;
    *(long *)(receiver + 0x30) = cnt;
    if (cnt != 0) {
        unsigned long out_list = (unsigned long)&DAT_00657778;
        cL4_buf_alloc(0, cnt, 0);
        long i = 0;
        do {
            unsigned long frame[9];
            cL4_bcopy((unsigned long)frame, (void *)(d + 0x20 + i * 0x48), 0x42);
            long head = *(long *)(frame + 8);
            long fn = *(long *)(frame + 0x10);
            unsigned long min_val;
            if (fn == 0) {
                cL4_seg_enter(&frame, local_140);
                min_val = 0;
            } else {
                cL4_seg_enter(&frame, local_140);
                local_140[0] = (unsigned long)&DAT_00657778;
                cL4_buf_alloc(0, fn, 0);
                long *p = (long *)(head + 0x20);
                unsigned long j = *(unsigned long *)(local_140[0] + 0x10);
                do {
                    unsigned long v = *(unsigned long *)(*p + 0x10);
                    unsigned long nj = j + 1;
                    if (*(unsigned long *)(local_140[0] + 0x18) >> 1 <= j)
                        cL4_buf_alloc(1 < *(unsigned long *)(local_140[0] + 0x18), nj, 1);
                    *(unsigned long *)(local_140[0] + 0x10) = nj;
                    *(unsigned long *)(local_140[0] + j * 8 + 0x20) = v;
                    fn--;
                    p++;
                    j = nj;
                } while (fn != 0);
                unsigned long cur = *(unsigned long *)(local_140[0] + 0x20);
                unsigned long rem2 = nj - 1;
                if (rem2 != 0) {
                    unsigned long o = 0x28;
                    unsigned long m = cur;
                    do {
                        unsigned long v = *(unsigned long *)(local_140[0] + o);
                        if (m <= v) { v = m; }
                        m = v;
                        o += 8;
                        rem2--;
                    } while (rem2 != 0);
                    min_val = m;
                } else {
                    min_val = cur;
                }
            }
            cL4_obj_release(local_140[0]);
            cL4_seg_leave(&frame);
            unsigned long n2 = *(unsigned long *)(out_list + 0x10);
            if (*(unsigned long *)(out_list + 0x18) >> 1 <= n2)
                cL4_buf_alloc(1 < *(unsigned long *)(out_list + 0x18), n2 + 1, 1);
            i++;
            *(unsigned long *)(out_list + 0x10) = n2 + 1;
            *(unsigned long *)(out_list + n2 * 8 + 0x20) = min_val;
        } while (i != cnt);
        if (cnt != *(long *)(d + 0x10))
            __builtin_trap();       /* 0xa7814 */
    }
    /* second pass: build the frame entries */
    cl4_result_t extent_res = cL4_extent_of(out_list);
    unsigned long size_pair = extent_res.lo, extent_flag = extent_res.hi;
    cL4_obj_release(out_list);
    unsigned long i2 = 0;
    long c2 = *(long *)(d + 0x10);
    unsigned int last = 0xffffffff;
    do {
        unsigned long r1 = i2 * 0x30 + 0x28;
        long r2 = c2 * 0x48 - 0x28;
        unsigned long j2 = i2;
        for (;;) {
            c2--;
            if (c2 == -1) {
                long total = *(long *)(receiver + 0x28);
                if (total != 0) {
                    unsigned long fhdr = 0;
                    if ((extent_flag & 0xff) != 1)
                        fhdr = size_pair;
                    unsigned long *head2 = (unsigned long *)cL4_buf_alloc(0x40, 0xffffffffffffffff);
                    *(unsigned long **)(receiver + 0x10) = head2;
                    head2[2] = 0; head2[1] = 0;
                    head2[4] = 0; head2[3] = 0;
                    head2[6] = 0; head2[5] = 0;
                    head2[7] = 0;
                    head2[0] = buf;
                    cL4_obj_release(tbl);
                    head2[1] = n;
                    unsigned long h = *(long *)(receiver + 0x10);
                    *(unsigned long *)(h + 0x10) = c;
                    *(unsigned long *)(h + 0x18) = fhdr;
                    *(long *)(h + 0x20) = total;
                    cL4_obj_release(d);
                    *(long *)(h + 0x28) = cnt;
                    h = *(long *)(receiver + 0x10);
                    *(unsigned long *)(h + 0x38) = e;
                    *(unsigned int *)(h + 0x30) = last;
                    return (long)receiver;
                }
                cL4_fatal_error(s_Fatal_error_005accd0, 0xb, 2, 0xd000000000000026,
                                (unsigned long)(s_missing_base_address_for_name_005c2190) | 0x8000000000000000,
                                0, 0, 2, 0xa5, 0);
            }
            if (*(long *)(d + 0x10) <= c2)
                __builtin_trap();   /* 0xa7a94 */
            unsigned long frame[9];
            cL4_bcopy((unsigned long)frame, (void *)(d + r2), 0x42);
            unsigned long fw0 = *(unsigned long *)(frame + 0x10);
            unsigned long j3 = j2 + 1;
            if (__builtin_add_overflow(j2, 1, &j3))
                __builtin_trap();   /* 0xa7a98 */
            if (__builtin_sub_overflow(cnt, j2, &reg_x8))
                __builtin_trap();   /* 0xa7a9c */
            unsigned long rem3 = (cnt - j2) - 1;
            if (__builtin_sub_overflow(cnt - j2, 1, &reg_x8))
                __builtin_trap();   /* 0xa7aa0 */
            if ((long)rem3 < 0) __builtin_trap();  /* 0xa7aa4 */
            if (rem3 >> 0x10 != 0) __builtin_trap(); /* 0xa7aa8 */
            unsigned long *rec = (unsigned long *)(d + r2);
            unsigned long s0 = *(unsigned long *)(rec + 0x10);
            unsigned long s1 = *(unsigned long *)(rec + 8);
            unsigned long s2 = *(unsigned long *)(rec + 0x20);
            unsigned long s3 = *(unsigned long *)(rec + 0x18);
            unsigned long s4 = *(unsigned long *)(rec + 0x28);
            cL4_seg_enter(&frame, local_140);
            cL4_obj_retain(fw0);
            unsigned long v = cL4_der_build(s1, fw0);
            cL4_error_tag(fw0);
            unsigned long fb = *(long *)(receiver + 0x28);
            unsigned long fc = *(long *)(receiver + 0x30);
            unsigned long pair2 = cL4_der_build(v);
            cL4_obj_release(v);
            cL4_seg_enter(&frame, local_140);
            unsigned long r0 = cL4_vtbl_call(0, 0);
            cL4_seg_leave(&frame);
            cL4_seg_enter(&frame, local_140);
            unsigned long r1v = cL4_vtbl_call(0, 0);
            cL4_seg_leave(&frame);
            if (fc <= j2)
                __builtin_trap();   /* 0xa7aac */
            unsigned short *dst = (unsigned short *)(fb + r1);
            *(void **)(dst - 0x14) = (void *)pair2;
            *(unsigned long *)(dst - 0xc) = r0;
            *(unsigned long *)(dst - 8) = r1v;
            *(unsigned long *)(dst - 4) = (unsigned long)frame;
            *dst = (unsigned short)rem3;
            unsigned long go = cL4_vtbl_call(s2, s3);
            cL4_seg_leave(&frame);
            if ((go & 1) != 0) break;
            j2++;
            r1 += 0x30;
            r2 -= 0x48;
        }
        if ((long)j2 >> 0x1f != 0)
            __builtin_trap();       /* 0xa7ab0 */
        last = (unsigned int)j2;
    } while (1);
}

/* FUN_000a7ba0 @ 0x000a7ba0   (est. exclave_stackshot_free)
 * Ghidra: void FUN_000a7ba0(void)
 * Frees the three buffers of a stack-shot descriptor: the frame array at
 * x20+0x18, the entry array at x20+0x28, and the header at x20+0x10.
 * Confidence: medium */
void exclave_stackshot_free(void)
{
    if (*(long *)(receiver + 0x18) != 0)
        cL4_free(*(long *)(receiver + 0x18), 0xffffffffffffffff, 0xffffffffffffffff);
    if (*(long *)(receiver + 0x28) != 0)
        cL4_free(*(long *)(receiver + 0x28), 0xffffffffffffffff, 0xffffffffffffffff);
    cL4_free(*(unsigned long *)(receiver + 0x10), 0xffffffffffffffff, 0xffffffffffffffff);
}

/* FUN_000a7bf0 @ 0x000a7bf0   (est. exclave_stackshot_dealloc_a)
 * Ghidra: void FUN_000a7bf0(void)
 * Frees the stack-shot buffers then runs teardown. Alternate entry.
 * Confidence: low */
void exclave_stackshot_dealloc_a(void)
{
    exclave_stackshot_free();
    cL4_block_alloc_fixed(0, 0x38, 7);
}

/* FUN_000a7bf4 @ 0x000a7bf4   (est. exclave_stackshot_dealloc_b)
 * Ghidra: void FUN_000a7bf4(void)
 * Same as 0xa7bf0. Alternate entry.
 * Confidence: low */
void exclave_stackshot_dealloc_b(void)
{
    exclave_stackshot_free();
    cL4_block_alloc_fixed(0, 0x38, 7);
}

/* FUN_000a7c14 @ 0x000a7c14   (est. exclave_release_or_return)
 * Ghidra: void FUN_000a7c14(undefined8 param_1,long param_2,undefined8 param_3,
 *        undefined8 param_4)
 * If param_2 is non-zero, error-tags it and releases param_4; otherwise
 * returns. A conditional-release helper.
 * Confidence: low */
void exclave_release_or_return(unsigned long a, long b, unsigned long c, unsigned long d)
{
    if (b != 0) {
        cL4_error_tag(b);
        cL4_obj_release(d);
    }
}

/* FUN_000a7c4c @ 0x000a7c4c   (est. cL4_type_desc)
 * Ghidra: undefined1 [16] FUN_000a7c4c(void)
 * Returns a type-descriptor pointer zero-extended from 0x6503f0.
 * Confidence: high */
unsigned long cL4_type_desc(void)
{
    return 0x6503f0;
}

/* FUN_000a7c6c @ 0x000a7c6c   (est. cL4_type_desc2)
 * Ghidra: undefined1 [16] FUN_000a7c6c(void)
 * Returns a type-descriptor pointer zero-extended from 0x650340.
 * Confidence: high */
unsigned long cL4_type_desc2(void)
{
    return 0x650340;
}

/* FUN_000a7c7c @ 0x000a7c7c   (est. exclave_tls_setup_a)
 * Ghidra: void FUN_000a7c7c(void)
 * Sets up exclave thread-local storage: initializes the TLS machinery,
 * allocates a 0x131-byte TLS block, runs TLS teardown setup, and finishes
 * with the region teardown A.
 * Confidence: low */
void exclave_tls_setup_a(void)
{
    cL4_tls_setup();
    unsigned long blk = cL4_tls_block();
    cL4_block_alloc(blk, 0x131, 7);
    cL4_tls_teardown();
    cL4_region_teardown_a();
}

/* FUN_000a7cd8 @ 0x000a7cd8   (est. exclave_tls_setup_b)
 * Ghidra: void FUN_000a7cd8(void)
 * Sets up exclave TLS with a 0x18-byte block and the region teardown B.
 * Confidence: low */
void exclave_tls_setup_b(void)
{
    cL4_tls_setup();
    unsigned long blk = cL4_tls_block();
    cL4_block_alloc(blk, 0x18, 7);
    cL4_tls_teardown();
    cL4_region_teardown_b();
}

/* FUN_000a7d50 @ 0x000a7d50   (est. exclave_desc_snapshot)
 * Ghidra: void FUN_000a7d50(undefined8 *param_1)
 * Snapshots the full 0x110-byte descriptor held at x20+0x10 into *param_1,
 * calling the vtable method at offset 0x48 for the final (status) word.
 * Confidence: medium */
void exclave_desc_snapshot(unsigned long *out)
{
    unsigned long *src = (unsigned long *)(receiver + 0x10);
    unsigned long w0  = src[0x10 / 8];
    unsigned long w1  = src[0x20 / 8];
    unsigned long w2  = src[0x18 / 8];
    unsigned long w3  = src[0x30 / 8];
    unsigned long w4  = src[0x28 / 8];
    unsigned long w5  = src[0x40 / 8];
    unsigned long w6  = src[0x38 / 8];
    unsigned long w7  = src[0x50 / 8];
    unsigned long w8  = src[0x48 / 8];
    unsigned long w9  = src[0x60 / 8];
    unsigned long w10 = src[0x58 / 8];
    unsigned long w11 = src[0x70 / 8];
    unsigned long w12 = src[0x68 / 8];
    unsigned long w13 = src[0x80 / 8];
    unsigned long w14 = src[0x78 / 8];
    unsigned long w15 = src[0x90 / 8];
    unsigned long w16 = src[0x88 / 8];
    unsigned long w17 = src[0xa0 / 8];
    unsigned long w18 = src[0x98 / 8];
    unsigned long w19 = src[0xb0 / 8];
    unsigned long w20 = src[0xa8 / 8];
    unsigned long w21 = src[0xc0 / 8];
    unsigned long w22 = src[0xb8 / 8];
    unsigned long w23 = src[0xd0 / 8];
    unsigned long w24 = src[0xc8 / 8];
    unsigned long w25 = src[0xe0 / 8];
    unsigned long w26 = src[0xd8 / 8];
    unsigned long w27 = src[0xf0 / 8];
    unsigned long w28 = src[0xe8 / 8];
    unsigned long w29 = src[0x100 / 8];
    unsigned long w30 = src[0xf8 / 8];
    unsigned long w31 = src[0x110 / 8];
    unsigned long w32 = src[0x108 / 8];
    unsigned long status = (**(unsigned long (**)(void))(*receiver + 0x48))();
    out[0] = w0; out[1] = w1; out[2] = w2; out[3] = w3;
    out[4] = w4; out[5] = w5; out[6] = w6; out[7] = w7;
    out[8] = w8; out[9] = w9; out[10] = w10; out[11] = w11;
    out[12] = w12; out[13] = w13; out[14] = w14; out[15] = w15;
    out[16] = w16; out[17] = w17; out[18] = w18; out[19] = w19;
    out[20] = w20; out[21] = w21; out[22] = w22; out[23] = w23;
    out[24] = w24; out[25] = w25; out[26] = w26; out[27] = w27;
    out[28] = w28; out[29] = w29; out[30] = w30; out[31] = w31;
    out[32] = w32;
    out[33] = status;
}

/* FUN_000a7e7c @ 0x000a7e7c   (est. exclave_support_data)
 * Ghidra: void FUN_000a7e7c(long param_1,long *param_2,uint param_3)
 * Builds the exclave support data: reads the three support pointers
 * (plVar1/plVar2/plVar4) and kind byte at param_1+0x118..0x130, invokes the
 * storage-interface vtable method at offset 0x1b8 to produce the data
 * snapshot, stores it at x20+0x18..0x50, then runs the seg transport
 * callbacks and the (un)map method (0x70 or 0x68). Handles the kind-2
 * (two-phase) path specially.
 * Confidence: medium
 * Notes: uses 0xa9388/0xa93f8 seg transport; kind byte 0x130. */
void exclave_support_data(unsigned long data, unsigned long *iface, unsigned int flags)
{
    *(unsigned long *)(receiver + 0x10) = data;
    unsigned long *p1 = *(unsigned long **)(data + 0x118);
    unsigned long *p2 = *(unsigned long **)(data + 0x120);
    unsigned long *p4 = *(unsigned long **)(data + 0x128);
    unsigned char kind = *(unsigned char *)(data + 0x130);
    unsigned long *sel = p1;
    if ((kind < 2) || (sel = p4, kind != 2)) {
        void (*m)(void) = *(void (**)(void))(*iface + 0x1b8);
        cL4_seg_transport(p1, p2, p4, kind);
        cL4_obj_retain(data);
        ((void (*)(unsigned long *, int, int, int, int, int))m)(&local_a0, 1, 0, 0, 0, 0);
        if (fail_reg == 0) {
            *(unsigned long *)(receiver + 0x20) = uStack_98;
            *(unsigned long *)(receiver + 0x18) = local_a0;
            *(unsigned long *)(receiver + 0x30) = uStack_88;
            *(unsigned long *)(receiver + 0x28) = uStack_90;
            *(unsigned long *)(receiver + 0x40) = CONCAT71(uStack_77, uStack_78);
            *(unsigned long *)(receiver + 0x38) = local_80;
            *(unsigned long *)(receiver + 0x49) = uStack_6f;
            *(unsigned long *)(receiver + 0x41) = CONCAT17(uStack_70, uStack_77);
            if ((flags & 1) == 0)
                (**(void (**)(void *))(*sel + 0x70))(&local_a0);
            else
                (**(void (**)(void *))(*sel + 0x68))(&local_a0);
            cL4_seg_transport_end(p1, p2, p4, kind);
            cL4_obj_release(iface);
            cL4_obj_release(0);
            return;
        }
        cL4_obj_release(data);
        cL4_obj_release(iface);
    } else {
        if (((unsigned long)p4 & 0xfe) != 0) {
            cL4_obj_release(iface);
            *(unsigned long *)(receiver + 0x48) = 0;
            *(unsigned long *)(receiver + 0x40) = 0;
            *(unsigned long *)(receiver + 0x38) = 0;
            *(unsigned long *)(receiver + 0x30) = 0;
            *(unsigned long *)(receiver + 0x28) = 0;
            *(unsigned long *)(receiver + 0x20) = 0;
            *(unsigned long *)(receiver + 0x18) = 0;
            *(unsigned char *)(receiver + 0x50) = 0xff;
            return;
        }
        void (*m)(void) = *(void (**)(void))(*iface + 0x1b8);
        cL4_seg_transport(p1, p2, p4, 2);
        cL4_seg_transport(p1, p2, p4, 2);
        cL4_obj_retain(data);
        ((void (*)(unsigned long *, int, int, int, int, int))m)(&local_e0, 1, 0, 0, 0, 0);
        if (fail_reg == 0) {
            *(unsigned long *)(receiver + 0x20) = uStack_d8;
            *(unsigned long *)(receiver + 0x18) = local_e0;
            *(unsigned long *)(receiver + 0x30) = uStack_c8;
            *(unsigned long *)(receiver + 0x28) = uStack_d0;
            *(unsigned long *)(receiver + 0x40) = CONCAT71(uStack_b7, uStack_b8);
            *(unsigned long *)(receiver + 0x38) = local_c0;
            *(unsigned long *)(receiver + 0x49) = uStack_af;
            *(unsigned long *)(receiver + 0x41) = CONCAT17(uStack_b0, uStack_b7);
            if ((flags & 1) == 0)
                (**(void (**)(void *))(*p2 + 0x70))(&local_e0);
            else
                (**(void (**)(void *))(*p2 + 0x68))(&local_e0);
            cL4_seg_transport_end(p1, p2, p4, 2);
            cL4_obj_release(iface);
            cL4_seg_transport_end(p1, p2, p4, 2);
            cL4_obj_release(0);
            return;
        }
        cL4_obj_release(data);
        cL4_obj_release(iface);
        kind = 2;
        cL4_seg_transport_end(p1, p2, p4, 2);
    }
    cL4_seg_transport_end(p1, p2, p4, kind);
    cL4_obj_release(*(unsigned long *)(receiver + 0x10));
    cL4_block_alloc_fixed(0, 0, 0);
}

/* FUN_000a8234 @ 0x000a8234   (est. exclave_support_query)
 * Ghidra: long FUN_000a8234(undefined8 param_1,undefined8 param_2,undefined8 param_3,
 *        undefined1 param_4)
 * Queries support data: if the kind byte at x20+0x10 + 0x130 is zero,
 * returns an error code; otherwise builds a verified 0x29-byte descriptor
 * record from the segment-transport state and returns it.
 * Confidence: medium */
long exclave_support_query(unsigned long a, unsigned long b, unsigned long c, unsigned char kind)
{
    if (*(char *)(*(long *)(receiver + 0x10) + 0x130) == 0)
        return -0xffffffffffffff9;
    cL4_obj_retain(0);
    cL4_region_validate();
    cL4_seg_transport(0, 0, 0, 0);
    cL4_region_validate();
    unsigned long pair;
    exclave_support_data(0, 0, 0);
    pair = reg_x8;
    cL4_region_validate();
    cL4_seg_transport_end(0, 0, 0, 0);
    long blk = cL4_block_alloc(0x650748, 0x29, 7);
    *(unsigned long *)(blk + 0x10) = pair;
    *(unsigned long *)(blk + 0x20) = c;
    *(unsigned char *)(blk + 0x28) = kind;
    return blk;
}

/* FUN_000a82d8 @ 0x000a82d8   (est. exclave_support_access)
 * Ghidra: undefined1 [16] FUN_000a82d8(ulong param_1,ulong param_2,ulong param_3,
 *        undefined1 param_4,long *param_5)
 * Performs a segmented access on the exclave's support buffers according to
 * the access kind (param_4): 0=raw read, 1=read-with-mask, 2=write
 * (index-0 or 1), 3=flush. Each case enters/leaves the segment transport
 * and invokes the vtable method at offset 0x48. Returns a {value, result}
 * pair.
 * Confidence: medium */
unsigned long exclave_support_access(unsigned long a, unsigned long b, unsigned long c,
                                     unsigned char kind, unsigned long *iface)
{
    unsigned long r = a;
    void (*m)(void) = *(void (**)(void))(*iface + 0x48);
    switch (kind) {
    default:
        cL4_seg_transport(a, b, c, 0);
        r = ((unsigned long (*)(void))m)();
        cL4_obj_release(iface);
        cL4_obj_release(a);
        b = r;
        break;
    case 1:
        cL4_seg_transport(a, b, c, 1);
        r = ((unsigned long (*)(void))m)();
        cL4_obj_release(iface);
        cL4_obj_release(a);
        b = b & 1;
        break;
    case 2:
        if ((c & 0xff) == 0) {
            cL4_seg_transport(a, b, c, 2);
            cL4_seg_enter(b, 0);
            r = ((unsigned long (*)(void))m)();
            cL4_seg_leave(b, 0);
            cL4_obj_release(iface);
            cL4_obj_release(b);
            b = r;
        } else if (((unsigned int)c & 0xff) == 1) {
            cL4_seg_transport(a, b, c, 2);
            cL4_seg_enter(b, 1);
            r = ((unsigned long (*)(void))m)();
            cL4_seg_leave(b, 1);
            cL4_obj_release(iface);
            cL4_obj_release(b);
            b = r;
        } else {
            cL4_seg_enter(b, 2);
            cL4_obj_release(iface);
            b = 0;
        }
        break;
    case 3:
        cL4_seg_transport(a, b, c, 3);
        ((void (*)(void))m)();
        cL4_obj_release(iface);
        cL4_obj_release(c);
        break;
    }
    unsigned long out[2] = { r, b };
    return out[0];
}

/* FUN_000a8ad8 @ 0x000a8ad8   (est. exclave_support_fault)
 * Ghidra: undefined1 [16] FUN_000a8ad8(void)
 * Emits the "inexed coroke." fatal fault: sets error 0x1d, error-tags the
 * code, logs the "inexed coroke" string, invokes the vtable method at 0x48,
 * and returns the error tuple. Fatal.
 * Confidence: medium
 * Notes: "inexed coroke" bytes 0x2065646f6e63202c / 0xef203a7865646e69. */
unsigned long exclave_support_fault(void)
{
    cL4_set_error(0x1d);
    cL4_error_tag(0xe000000000000000);
    cL4_error_ctx();
    cL4_err_log();
    cL4_error_tag(reg_x1);
    cL4_err_log(0x2065646f6e63202c, 0xef203a7865646e69);
    (**(void (**)(void))(*receiver + 0x48))();
    ((void (*)(unsigned long, unsigned long))cL4_swift_fault(0x671df8))(0x677830, 0x671df8);
    cL4_err_log();
    cL4_error_tag(reg_x1);
    cL4_err_log(0x29, 0xe100000000000000);
    return 0x646572656b6f7242;      /* "Broke..." */
}

/* FUN_000a8c08 @ 0x000a8c08   (est. exclave_obj_method50)
 * Ghidra: void FUN_000a8c08(void)
 * Calls the vtable method at offset 0x50 on the object in x20. Receiver-only.
 * Confidence: low */
void exclave_obj_method50(void)
{
    (**(void (**)(void))(*(long *)*receiver + 0x50))();
}

/* FUN_000a8c44 @ 0x000a8c44   (est. exclave_obj_method60)
 * Ghidra: void FUN_000a8c44(void)
 * Calls the vtable method at offset 0x60 on the object in x20. Receiver-only.
 * Confidence: low */
void exclave_obj_method60(void)
{
    (**(void (**)(void))(*(long *)*receiver + 0x60))();
}
