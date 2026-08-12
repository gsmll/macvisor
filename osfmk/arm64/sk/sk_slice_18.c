/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SK18 slice (0x000776c0-0x0007b324): the Swift implementation of the
 * InternalExclaveLauncher CNodeAllocator (CNode.swift + CNodeAllocator.swift).
 * This is the capability-node (CNode) allocator that the internal Exclave
 * launcher uses to build the capability nodes handed to a new exclave. It is
 * pure Swift (compiled witness/accessor code), so most of the region is:
 *   - stored-property getter/setter/modify-with-copy/retain witnesses for the
 *     CNodeAllocator class fields (offsets 0x50..0x98),
 *   - CNode-entry constructors that build 0x38-byte CNodeEntry descriptors,
 *   - the copy-on-write growable-array append/resize used for the cnode
 *     entry buffer,
 *   - the core allocObjectAndCap / append-with-relocation logic, and
 *   - Swift-runtime string/array helpers called through indirect vtables.
 *
 * Ground-truth strings (from the binary) that anchor this region:
 *   0x004c0803 "CNodeAllocator", 0x004c07d8 "CNodeEntry",
 *   0x005bfc70 "InternalExclaveLauncher/CNode.swift",
 *   0x005bfce0 "CNodeAllocator: allocObjectAndCap is called with wrong
 *               object type",
 *   0x005bfd30 "CNodeAllocator failed to allocate generic entry in a
 *               predictable way",
 *   0x005bfca0 "Cannot give relocated cap when filling ...",
 *   0x005bfee0 "CNodeAllocator is corrupted",
 *   0x005bff00 "CNodeAllocator could not move CNode cap into CNode",
 *   0x005c16a0 "InternalExclaveLauncher/CNodeAllocator.swift",
 *   0x005c16d0 "[CNodeAllocator] could not find space cap".
 *
 * Swift ABI: heap allocations, vtable dispatch and overflow-checked
 * arithmetic are rendered faithfully but the high-level Swift semantics
 * cannot be fully recovered; confidence is medium for the accessor/iterator
 * block and low for the heavy Swift-ABI functions.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;

#define SK18_FATAL(addr) __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* ---- Shared kernel / Swift-runtime externs (ground truth FUN_ addresses). ----
 * Arity is deliberately flexible (variadic) because the Swift ABI uses
 * unaff-register / tail-merging conventions that Ghidra renders with varying
 * argument counts; the bodies call these with the counts shown in each
 * decompile. */

extern word_t sk_memcpy_w(word_t, ...);                       /* FUN_00117cc4 */
extern word_t sk_swift_release(word_t, ...);                  /* FUN_0036b118 */
extern word_t sk_swift_retain(word_t, ...);                   /* FUN_0036b270 */
extern word_t sk_swift_array_alloc(word_t, ...);              /* FUN_0036a940 */
extern word_t sk_swift_array_withcap(word_t, ...);            /* FUN_0036a1a0 */
extern void   sk_swift_array_destroy(word_t, ...);            /* FUN_0036a20c */
extern word_t sk_swift_buffer_unique(word_t, ...);            /* FUN_003a261c */
extern void   sk_swift_release_masked(word_t, ...);           /* FUN_003a25d4 */
extern void   sk_swift_memmove_log(word_t, ...);              /* FUN_0035b67c */
extern word_t sk_swift_array_init(word_t, ...);               /* FUN_00365b6c */
extern word_t sk_str_convert(word_t, ...);                    /* FUN_00377824 */
extern word_t sk_str_convert2(word_t, ...);                   /* FUN_00377bec */
extern word_t sk_metaclass_get(void);                         /* FUN_000027e8 */
extern word_t sk_metaclass_field(word_t, ...);                /* FUN_00002828 */
extern word_t sk_metaclass_chk(word_t, ...);                  /* FUN_000026e8 */
extern word_t sk_string_cache(word_t, ...);                   /* FUN_00002534 */
extern word_t sk_vt_lookup(word_t, ...);                      /* FUN_00027724 */
extern word_t sk_identity_hash(word_t, ...);                  /* FUN_0001c294 */
extern word_t sk_identity(word_t, ...);                       /* FUN_0001a1c8 */
extern word_t sk_runtime_roundup(word_t, ...);                /* FUN_0014aedc */
extern word_t sk_runtime_roundup2(word_t, ...);               /* FUN_0014af94 */
extern word_t sk_runtime_add(word_t, ...);                    /* FUN_0014aea4 */
extern word_t sk_runtime_align(word_t, ...);                  /* FUN_0014afe0 */
extern word_t sk_arith(word_t, ...);                          /* FUN_0007eb2c */
extern word_t sk_arr_init3(word_t, ...);                      /* FUN_0019ea20 */
extern word_t sk_closure_enter(word_t, ...);                  /* FUN_0006e7c0 */
extern word_t sk_copy2(word_t, ...);                          /* FUN_0006a4c0 */
extern word_t sk_copy3(word_t, ...);                          /* FUN_0006df24 */
extern word_t sk_scoped_enter(word_t, ...);                   /* FUN_001a84f4 */
extern void   sk_scoped_exit(void);                           /* FUN_001a8564 */
extern word_t sk_bind(word_t, ...);                           /* thunk_FUN_002298d4 */
extern word_t sk_str_append(word_t, ...);                     /* thunk_FUN_002acbb8 */
extern word_t sk_fault_builder(word_t, ...);                  /* FUN_002a4ab4 */
extern word_t sk_assert_prep(void);                           /* FUN_00002818 */
extern void   sk_assert_fatal(word_t, ...) __attribute__((noreturn)); /* FUN_001afa84 */
extern void   sk_fatal_str(word_t, ...) __attribute__((noreturn));    /* FUN_0007bfdc */
extern word_t sk_misc(word_t, ...);                           /* FUN_000ec8f8 */
extern void   sk_nop_word(void);                              /* FUN_0036b6ac */

/* Swift stored-property accessor state-machine helpers (near-region). */
extern word_t sk_acc_read(word_t, ...);                       /* FUN_0007c004 */
extern void   sk_acc_write_pre(void);                         /* FUN_0007bfac */
extern void   sk_acc_write_post(void);                        /* FUN_0007bff0 */
extern void   sk_acc_modify(void);                            /* FUN_0007bfc8 */
extern void   sk_acc_finish(void);                            /* FUN_0007c0a0 */
extern void   sk_acc_finish2(void);                           /* FUN_0007c158 */
extern word_t sk_acc_get(word_t, ...);                        /* FUN_0007c0b8 */
extern word_t sk_acc_ctx(void);                               /* FUN_0007c0c4 */
extern void   sk_acc_ctx2(void);                              /* FUN_0007c0ac */
extern word_t sk_acc_w2(word_t, ...);                         /* FUN_0007c0d4 */
extern word_t sk_acc_w3(word_t, ...);                         /* FUN_0007c0e0 */
extern void   sk_acc_w4(void);                                /* FUN_0007c0ec */
extern word_t sk_acc_w5(word_t, ...);                         /* FUN_0007c0f8 */
extern word_t sk_acc_w6(void);                                /* FUN_0007c018 */
extern void   sk_acc_w7(void);                                /* FUN_0007c028 */
extern void   sk_acc_w8(void);                                /* FUN_0007c038 */
extern word_t sk_acc_w9(void);                                /* FUN_0007c070 */
extern word_t sk_acc_w10(void);                               /* FUN_0007c088 */
extern void   sk_acc_w11(void);                               /* FUN_0007c128 */
extern word_t sk_acc_w12(word_t, ...);                        /* FUN_0007c140 */
extern word_t sk_acc_w13(void);                               /* FUN_0007c14c */
extern void   sk_acc_w14(void);                               /* FUN_0007c164 */
extern word_t sk_acc_w15(void);                               /* FUN_0007c178 */
extern void   sk_acc_w16(void);                               /* FUN_0007c18c */
extern void   sk_acc_w17(void);                               /* FUN_0007c198 */
extern word_t sk_acc_w18(void);                               /* FUN_0007c1a4 */
extern word_t sk_acc_w19(void);                               /* FUN_0007c1c4 */
extern word_t sk_acc_w20(void);                               /* FUN_0007c1d0 */

/* CNode-entry buffer grow/resize helpers (copy-on-write). */
extern word_t sk_cnode_buf_append(word_t, ...);               /* FUN_0007b2c8 */
extern word_t sk_cnode_buf_reserve(word_t, ...);              /* FUN_0007b4a4 */
extern word_t sk_cnode_buf_reserve2(word_t, ...);             /* FUN_0007b4e8 */
extern word_t sk_cnode_align(word_t, ...);                    /* FUN_0007b33c */
extern word_t sk_cnode_fn(word_t, ...);                       /* FUN_0007b354 */
extern word_t sk_cnode_fn2(word_t, ...);                      /* FUN_0007b384 */
extern word_t sk_cnode_fn3(void);                             /* FUN_0007b3b4 */

/* Swift String / misc helpers used by the init path. */
extern word_t sk_string_end_index(word_t, ...);               /* FUN_00078fec */
extern word_t sk_f6d88(word_t, ...);                          /* FUN_000f6d88 */
extern word_t sk_cnode_resize_cb(word_t, ...);                /* FUN_00072d5c */
extern word_t thunk_sk_cnode_probe(word_t, word_t);           /* thunk_FUN_0000456c */

/* Register-held "self"/context pointers (Ghidra sk_reg_x19/x20/x21/x22/w19):
 * these are the arm64e callee-saved registers that carry the Swift self /
 * accessor-context value. Represented as scalar words; dereferenced with
 * explicit casts. */
extern word_t sk_reg_x19;
extern word_t sk_reg_x20;
extern word_t sk_reg_x21;
extern word_t sk_reg_x22;
extern word_t sk_reg_w19;

/* =====================================================================
 * CNodeAllocator class stored-property accessor witnesses.
 * (offsets are field offsets resolved via the class metadata)
 * ===================================================================== */

/* FUN_000776c0 @ 0x000776c0   (est. sk_cnode_prop_witness_0)
 * Ghidra: void FUN_000776c0(void)  — empty witness thunk (returns immediately).
 * Confidence: medium
 * Notes: A Swift protocol/conformance empty accessor; no body. */
void sk_cnode_w0(void) { return; }

/* FUN_000776cc @ 0x000776cc   (est. sk_cnode_prop_witness_1)
 * Ghidra: void FUN_000776cc(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w1(void) { return; }

/* FUN_000776d8 @ 0x000776d8   (est. sk_cnode_prop_witness_2)
 * Ghidra: void FUN_000776d8(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w2(void) { return; }

/* FUN_000776e4 @ 0x000776e4   (est. sk_cnode_prop_witness_3)
 * Ghidra: void FUN_000776e4(void)  — forwards to sk_swift_memmove_log().
 * Confidence: medium
 * Notes: Ghidra drops the args (unaff registers). */
void sk_cnode_w3(void) { sk_swift_memmove_log(0,0,0,0); return; }

/* FUN_000776f8 @ 0x000776f8   (est. sk_cnode_buf_alloc)
 * Ghidra: void FUN_000776f8(undefined8 param_1)  — allocates an array buffer
 *   of self-sized element storage via sk_swift_array_alloc(elt, size+0x20, 7).
 * Confidence: medium
 * Notes: self extent held in sk_reg_x20/sk_reg_x21 (Swift array buffer header). */
void sk_cnode_buf_alloc(word_t param_1)
{
    extern word_t sk_reg_x20, sk_reg_x21;
    (void)sk_reg_x20; (void)sk_reg_x21;
    sk_swift_array_alloc(param_1, (word_t)&sk_reg_x20 + (word_t)&sk_reg_x21 + 0x20, 7);
    return;
}

/* FUN_00077708 @ 0x00077708   (est. sk_cnode_prop_witness_4)
 * Ghidra: void FUN_00077708(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w4(void) { return; }

/* FUN_00077718 @ 0x00077718   (est. sk_cnode_buffer_unset)
 * Ghidra: void FUN_00077718(void)  — clears self[0x10]=0 then releases the
 *   object referenced by self (Swift buffer detach).
 * Confidence: medium */
void sk_cnode_buffer_unset(void)
{
        *(word_t *)(sk_reg_x19 + 0x10) = 0;
    sk_swift_release(0);
    return;
}

/* FUN_00077724 @ 0x00077724   (est. sk_cnode_prop_witness_5)
 * Ghidra: void FUN_00077724(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w5(void) { return; }

/* FUN_00077744 @ 0x00077744   (est. sk_cnode_prop_witness_6)
 * Ghidra: void FUN_00077744(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w6(void) { return; }

/* FUN_00077764 @ 0x00077764   (est. sk_cnode_prop_witness_7)
 * Ghidra: void FUN_00077764(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w7(void) { return; }

/* FUN_00077770 @ 0x00077770   (est. sk_cnode_prop_witness_8)
 * Ghidra: void FUN_00077770(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w8(void) { return; }

/* FUN_00077778 @ 0x00077778   (est. sk_cnode_prop_witness_9)
 * Ghidra: void FUN_00077778(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w9(void) { return; }

/* FUN_00077794 @ 0x00077794   (est. sk_cnode_buf_unique)
 * Ghidra: void FUN_00077794(void)  — Swift copy-on-write uniqueness check on
 *   *self via sk_swift_buffer_unique().
 * Confidence: medium */
void sk_cnode_buf_unique(void)
{
        sk_swift_buffer_unique(*(word_t *)sk_reg_x20);
    return;
}

/* FUN_000777b4 @ 0x000777b4   (est. sk_cnode_prop_witness_10)
 * Ghidra: void FUN_000777b4(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w10(void) { return; }

/* FUN_000777c4 @ 0x000777c4   (est. sk_cnode_prop_witness_11)
 * Ghidra: void FUN_000777c4(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w11(void) { return; }

/* FUN_000777d4 @ 0x000777d4   (est. sk_cnode_prop_witness_12)
 * Ghidra: void FUN_000777d4(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w12(void) { return; }

/* FUN_000777e4 @ 0x000777e4   (est. sk_cnode_buf_unique2)
 * Ghidra: void FUN_000777e4(void)  — Swift COW uniqueness check on *self.
 * Confidence: medium */
void sk_cnode_buf_unique2(void)
{
        sk_swift_buffer_unique(*(word_t *)sk_reg_x20);
    return;
}

/* FUN_00077800 @ 0x00077800   (est. sk_cnode_prop_witness_13)
 * Ghidra: void FUN_00077800(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w13(void) { return; }

/* FUN_0007780c @ 0x0007780c   (est. sk_cnode_empty_buffer)
 * Ghidra: undefined * FUN_0007780c(void)  — returns the fixed empty-vector
 *   sentinel DAT_00657778 (Swift empty array storage).
 * Confidence: medium
 * Notes: Ghidra constant &DAT_00657778. */
word_t sk_cnode_empty_buffer(void) { return 0x657778; }

/* FUN_00077824 @ 0x00077824   (est. sk_cnode_prop_witness_14)
 * Ghidra: void FUN_00077824(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w14(void) { return; }

/* FUN_0007783c @ 0x0007783c   (est. sk_cnode_prop_witness_15)
 * Ghidra: void FUN_0007783c(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w15(void) { return; }

/* FUN_00077848 @ 0x00077848   (est. sk_cnode_scoped_enter)
 * Ghidra: void FUN_00077848(void)  — scoped accessor enter: enters the
 *   accessor scope storing self[0x28] as the accessor context.
 * Confidence: medium
 * Notes: sk_scoped_enter(&stack, *(self+0x28)). */
void sk_cnode_scoped_enter(void)
{
        word_t local;
    sk_scoped_enter((word_t)&local, *(word_t *)(sk_reg_x20 + 0x28));
    return;
}

/* FUN_00077860 @ 0x00077860   (est. sk_cnode_element_copy)
 * Ghidra: void FUN_00077860(long param_1,undefined8 param_2,undefined8 param_3,
 *                           undefined8 param_4)  — copies param_1*8 bytes from
 *   src(param_3) to dst(param_4) (Swift array element buffer copy).
 * Confidence: medium */
void sk_cnode_element_copy(word_t count, word_t a2, word_t src, word_t dst)
{
    (void)a2;
    sk_memcpy_w(dst, src, count << 3);
    return;
}

/* FUN_00077870 @ 0x00077870   (est. sk_cnode_prop_witness_16)
 * Ghidra: void FUN_00077870(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w16(void) { return; }

/* FUN_0007787c @ 0x0007787c   (est. sk_cnode_prop_witness_17)
 * Ghidra: void FUN_0007787c(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w17(void) { return; }

/* FUN_00077888 @ 0x00077888   (est. sk_cnode_prop_witness_18)
 * Ghidra: void FUN_00077888(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w18(void) { return; }

/* FUN_00077894 @ 0x00077894   (est. sk_cnode_prop_witness_19)
 * Ghidra: void FUN_00077894(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w19(void) { return; }

/* FUN_000778a0 @ 0x000778a0   (est. sk_cnode_type_name_0)
 * Ghidra: undefined8 FUN_000778a0(void)  — returns a type-metadata / name
 *   descriptor constant 0x677830.
 * Confidence: medium
 * Notes: Ghidra literal 0x677830 (Swift demangled type name pointer). */
word_t sk_cnode_type_name_0(void) { return 0x677830; }

/* FUN_000778b4 @ 0x000778b4   (est. sk_cnode_prop_witness_20)
 * Ghidra: void FUN_000778b4(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w20(void) { return; }

/* FUN_000778c0 @ 0x000778c0   (est. sk_cnode_buf_unique3)
 * Ghidra: void FUN_000778c0(void)  — Swift COW uniqueness check on *self.
 * Confidence: medium */
void sk_cnode_buf_unique3(void)
{
        sk_swift_buffer_unique(*(word_t *)sk_reg_x20);
    return;
}

/* FUN_000778d4 @ 0x000778d4   (est. sk_cnode_dispatch_1)
 * Ghidra: void FUN_000778d4(void)  — calls FUN_00070674(1, w19, 0) (region
 *   dispatch helper); single-byte argument carried in sk_reg_w19.
 * Confidence: low
 * Notes: args dropped by the decompiler. */
void sk_cnode_dispatch_1(void)
{
        (void)sk_reg_w19;
    sk_identity(0); /* placeholder for FUN_00070674(1, w19, 0) */
    return;
}

/* FUN_000778e8 @ 0x000778e8   (est. sk_cnode_dispatch_2)
 * Ghidra: void FUN_000778e8(void)  — forwards to FUN_000725c8().
 * Confidence: low */
void sk_cnode_dispatch_2(void) { sk_identity(0); return; }

/* FUN_000778fc @ 0x000778fc   (est. sk_cnode_string_ctor)
 * Ghidra: void FUN_000778fc(void)  — constructs a Swift string from the type
 *   name metadata: sk_string_cache(FUN_0064e030, &DAT_004be900).
 * Confidence: medium
 * Notes: Ghidra args FUN_0064e030 (function ptr) / DAT_004be900. */
void sk_cnode_string_ctor(void) { sk_string_cache(0x64e030, 0x4be900); return; }

/* FUN_00077910 @ 0x00077910   (est. sk_cnode_prop_witness_21)
 * Ghidra: void FUN_00077910(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w21(void) { return; }

/* FUN_0007791c @ 0x0007791c   (est. sk_cnode_prop_witness_22)
 * Ghidra: void FUN_0007791c(void)  — empty witness thunk.
 * Confidence: medium */
void sk_cnode_w22(void) { return; }

/* FUN_00077928 @ 0x00077928   (est. sk_cnode_dispatch_3)
 * Ghidra: void FUN_00077928(void)  — forwards to FUN_0006ae9c().
 * Confidence: low */
void sk_cnode_dispatch_3(void) { sk_identity(0); return; }

/* FUN_00077934 @ 0x00077934   (est. sk_cnode_span_copy_1)
 * Ghidra: undefined8 FUN_00077934(void)  — returns self[0x28] after copying
 *   the array element buffer: sk_copy2(self+8, self[0x20]).
 * Confidence: medium */
word_t sk_cnode_span_copy_1(void)
{
        word_t u;
    u = *(word_t *)(sk_reg_x22 + 0x28);
    sk_copy2(sk_reg_x22 + 8, *(word_t *)(sk_reg_x22 + 0x20));
    return u;
}

/* FUN_00077960 @ 0x00077960   (est. sk_cnode_span_copy_2)
 * Ghidra: undefined8 FUN_00077960(void)  — same shape as 77934 for a
 *   different stored property (self[0x28] after copying buffer).
 * Confidence: medium */
word_t sk_cnode_span_copy_2(void)
{
        word_t u;
    u = *(word_t *)(sk_reg_x20 + 0x28);
    sk_copy2(sk_reg_x20 + 8, *(word_t *)(sk_reg_x20 + 0x20));
    return u;
}

/* FUN_0007798c @ 0x0007798c   (est. sk_cnode_identity_scope)
 * Ghidra: undefined8 FUN_0007798c(undefined8 param_1)  — enters a Swift
 *   identity scope (sk_identity_hash(0)) and returns param_1 unchanged.
 * Confidence: medium
 * Notes: FUN_00310d34(0) + FUN_0001a1c8(). */
word_t sk_cnode_identity_scope(word_t param_1, word_t a2)
{
    (void)a2;
    sk_identity(0);
    return param_1;
}

/* FUN_00077a90 @ 0x00077a90   (est. sk_cnode_self_deref)
 * Ghidra: undefined8 FUN_00077a90(void)  — returns *self (Swift value load).
 * Confidence: medium */
word_t sk_cnode_self_deref(void)
{
        return *(word_t *)sk_reg_x20;
}

/* FUN_00077b58 @ 0x00077b58   (est. sk_cnode_bind_field)
 * Ghidra: void FUN_00077b58(undefined8 param_1)  — binds param_1 against
 *   *self via sk_bind(param_1, *self) (Swift closure bind).
 * Confidence: medium */
void sk_cnode_bind_field(word_t param_1)
{
        sk_bind(param_1, *(word_t *)sk_reg_x20);
    return;
}

/* FUN_00077b84 @ 0x00077b84   (est. sk_cnode_scoped_bind)
 * Ghidra: void FUN_00077b84(void)  — scoped bind: enter scope, bind *self,
 *   exit scope.
 * Confidence: medium */
void sk_cnode_scoped_bind(void)
{
        word_t local[9];   /* 72-byte scope frame */
    sk_scoped_enter((word_t)local, 0);
    sk_bind(*(word_t *)sk_reg_x20, 0);
    sk_scoped_exit();
    return;
}

/* FUN_00077bd0 @ 0x00077bd0   (est. sk_cnode_scoped_bind2)
 * Ghidra: void FUN_00077bd0(void)  — enter scope, bind the scoped value via
 *   sk_cnode_bind_field, exit scope.
 * Confidence: medium */
void sk_cnode_scoped_bind2(void)
{
    word_t local[9];   /* 72-byte scope frame */
    sk_scoped_enter((word_t)local, 0);
    sk_cnode_bind_field((word_t)local);
    sk_scoped_exit();
    return;
}

/* FUN_00077c10 @ 0x00077c10   (est. sk_cnode_find_by_id)
 * Ghidra: undefined8 FUN_00077c10(long param_1,long param_2)  — linear search
 *   over a 0x40-stride entry table: returns the "value" field of the entry
 *   whose 8-byte key field matches param_1 and whose flag byte is clear and
 *   whose tag passes sk_identity_hash(flag,3) (present+valid check).
 * Confidence: medium
 * Notes: entry layout { -0x18: value, +0x8: key, +0x20: flag byte } at 0x40
 *   stride; count at param_2+0x10, first entry at param_2+0x38. */
word_t sk_cnode_find_by_id(word_t key, word_t tbl)
{
    long count;
    word_t value;
    word_t *p;
    word_t v;
    count = *(long *)(tbl + 0x10);
    if (count != 0) {
        p = (word_t *)(tbl + 0x38);
        do {
            if (p[0x20] == 0 && *(long *)(p + 8) == (long)key) {
                value = *(word_t *)(p - 0x18);
                v = sk_identity_hash(*p, 3);
                if ((v & 1) != 0) return value;
            }
            p = p + 0x40;
            count = count - 1;
        } while (count != 0);
    }
    return 0;
}

/* FUN_00077c88 @ 0x00077c88   (est. sk_cnode_prop_set_retain)
 * Ghidra: void FUN_00077c88(undefined8 param_1)  — releases self[0x10] then
 *   stores param_1 into self[0x10] (Swift property setter with release).
 * Confidence: medium */
void sk_cnode_prop_set_retain(word_t param_1)
{
        sk_swift_release(*(word_t *)(sk_reg_x20 + 0x10));
    *(word_t *)(sk_reg_x20 + 0x10) = param_1;
    return;
}

/* FUN_00077d64 @ 0x00077d64   (est. sk_cnode_prop_retain_get_0x50)
 * Ghidra: void FUN_00077d64(void)  — Swift retain-getter for the stored
 *   property at metadata offset 0x50: resolve offset, load self[off], retain.
 * Confidence: medium */
void sk_cnode_prop_retain_get_0x50(void)
{
        word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x50);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(sk_reg_x20 + off));
    return;
}

/* FUN_00077da4 @ 0x00077da4   (est. sk_cnode_prop_modify_0x50)
 * Ghidra: void FUN_00077da4(void)  — Swift modify-with-copy for the property
 *   at 0x50 (write-pre, modify, finish2).
 * Confidence: medium */
void sk_cnode_prop_modify_0x50(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish2();
    return;
}

/* FUN_00077de8 @ 0x00077de8   (est. sk_cnode_prop_modify2_0x50)
 * Ghidra: void FUN_00077de8(void)  — Swift modify-with-copy (finish variant).
 * Confidence: medium */
void sk_cnode_prop_modify2_0x50(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_00077e38 @ 0x00077e38   (est. sk_cnode_prop_get_0x58)
 * Ghidra: undefined8 FUN_00077e38(void)  — Swift getter for property at
 *   metadata offset 0x58: return self[off].
 * Confidence: medium */
word_t sk_cnode_prop_get_0x58(void)
{
        word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x58);
    sk_acc_read(0);
    return *(word_t *)(sk_reg_x20 + off);
}

/* FUN_00077e74 @ 0x00077e74   (est. sk_cnode_prop_set_0x58)
 * Ghidra: void FUN_00077e74(void)  — Swift setter for property at 0x58:
 *   self[off] = newValue (w19).
 * Confidence: medium */
void sk_cnode_prop_set_0x58(word_t newValue)
{
        word_t mc, off;
    sk_acc_write_pre();
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x58);
    sk_acc_write_post();
    *(word_t *)(sk_reg_x20 + off) = newValue;
    return;
}

/* FUN_00077eb8 @ 0x00077eb8   (est. sk_cnode_prop_modify_0x58)
 * Ghidra: void FUN_00077eb8(void)  — Swift modify-with-copy for 0x58.
 * Confidence: medium */
void sk_cnode_prop_modify_0x58(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_00077f08 @ 0x00077f08   (est. sk_cnode_prop_get_0x60)
 * Ghidra: undefined8 FUN_00077f08(void)  — Swift getter for property at 0x60.
 * Confidence: medium */
word_t sk_cnode_prop_get_0x60(void)
{
        word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x60);
    sk_acc_read(0);
    return *(word_t *)(sk_reg_x20 + off);
}

/* FUN_00077f44 @ 0x00077f44   (est. sk_cnode_prop_set_0x60)
 * Ghidra: void FUN_00077f44(void)  — Swift setter for property at 0x60.
 * Confidence: medium */
void sk_cnode_prop_set_0x60(word_t newValue)
{
        word_t mc, off;
    sk_acc_write_pre();
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x60);
    sk_acc_write_post();
    *(word_t *)(sk_reg_x20 + off) = newValue;
    return;
}

/* FUN_00077f88 @ 0x00077f88   (est. sk_cnode_prop_modify_0x60)
 * Ghidra: void FUN_00077f88(void)  — Swift modify-with-copy for 0x60.
 * Confidence: medium */
void sk_cnode_prop_modify_0x60(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_00077fd8 @ 0x00077fd8   (est. sk_cnode_closure_invoke_0xf0)
 * Ghidra: void FUN_00077fd8(undefined8 *param_1,undefined8 *param_2)  — loads
 *   closure vtable slot +0xf0 from param_2's metadata, retains *param_1, then
 *   invokes the closure.
 * Confidence: medium */
void sk_cnode_closure_invoke_0xf0(word_t *param_1, word_t *param_2)
{
    void (*fn)(void) = *(void (**)(void))(*(long *)*param_2 + 0xf0);
    sk_swift_retain(*param_1);
    fn();
    return;
}

/* FUN_0007802c @ 0x0007802c   (est. sk_cnode_prop_retain_get_0x68)
 * Ghidra: void FUN_0007802c(void)  — Swift retain-getter for property at 0x68.
 * Confidence: medium */
void sk_cnode_prop_retain_get_0x68(void)
{
        word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x68);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(sk_reg_x20 + off));
    return;
}

/* FUN_0007806c @ 0x0007806c   (est. sk_cnode_prop_modify_0x68)
 * Ghidra: void FUN_0007806c(void)  — Swift modify-with-copy for 0x68 (finish2).
 * Confidence: medium */
void sk_cnode_prop_modify_0x68(void)
{
    sk_acc_write_pre();
    sk_acc_write_post();
    sk_acc_finish2();
    return;
}

/* FUN_000780b0 @ 0x000780b0   (est. sk_cnode_prop_modify2_0x68)
 * Ghidra: void FUN_000780b0(void)  — Swift modify-with-copy for 0x68 (finish).
 * Confidence: medium */
void sk_cnode_prop_modify2_0x68(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_00078100 @ 0x00078100   (est. sk_cnode_closure_invoke_0x108)
 * Ghidra: void FUN_00078100(undefined8 param_1,undefined8 *param_2)  —
 *   materialize param_1 into a 40-byte closure box, then invoke the closure
 *   vtable slot +0x108 from param_2's metadata with the box.
 * Confidence: medium */
void sk_cnode_closure_invoke_0x108(word_t param_1, word_t *param_2)
{
    word_t box[5];   /* 40-byte closure capture box */
    sk_closure_enter(param_1, (word_t)box);
    (*(void (**)(word_t))(*(long *)*param_2 + 0x108))((word_t)box);
    return;
}

/* FUN_0007815c @ 0x0007815c   (est. sk_cnode_prop_box_write_0x70)
 * Ghidra: void FUN_0007815c(undefined8 param_1)  — materialize self[0x70]
 *   into a 24-byte box, then copy param_1 into it (Swift @boxed property).
 * Confidence: medium */
void sk_cnode_prop_box_write_0x70(word_t param_1)
{
        word_t mc, off;
    word_t box[3];   /* 24-byte box */
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x70);
    sk_metaclass_field(sk_reg_x20 + off, (word_t)box);
    sk_closure_enter(sk_reg_x20 + off, param_1);
    return;
}

/* FUN_000781b4 @ 0x000781b4   (est. sk_cnode_prop_reset_0x70)
 * Ghidra: void FUN_000781b4(void)  — Swift modify-with-copy for the boxed
 *   property at 0x70: build an empty array with capacity 0x21, invoke the
 *   modify, then destroy the temp.
 * Confidence: medium */
void sk_cnode_prop_reset_0x70(void)
{
        word_t mc, off;
    word_t box[3];   /* 24-byte temp */
    sk_acc_write_pre();
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x70);
    sk_swift_array_withcap(sk_reg_x20 + off, (word_t)box, 0x21, 0, 0);
    sk_metaclass_chk(sk_reg_x20 + off);
    sk_identity(0);                       /* FUN_00077070 */
    sk_swift_array_destroy((word_t)box);
    return;
}

/* FUN_00078220 @ 0x00078220   (est. sk_cnode_prop_modify_0x70)
 * Ghidra: void FUN_00078220(void)  — Swift modify-with-copy for 0x70 (finish).
 * Confidence: medium */
void sk_cnode_prop_modify_0x70(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_00078270 @ 0x00078270   (est. sk_cnode_closure_invoke_0x120)
 * Ghidra: void FUN_00078270(undefined8 *param_1,undefined8 *param_2)  —
 *   invoke closure vtable slot +0x120 with (*param_1, param_1[1] as byte).
 * Confidence: medium */
void sk_cnode_closure_invoke_0x120(word_t *param_1, word_t *param_2)
{
    (*(void (**)(word_t, word_t))(*(long *)*param_2 + 0x120))(*param_1,
        *(word_t *)(param_1 + 1));
    return;
}

/* FUN_000782c0 @ 0x000782c0   (est. sk_cnode_prop_box_read_0x78)
 * Ghidra: undefined1 [16] FUN_000782c0(void)  — materialize self[0x78] (a
 *   9-byte value) into a 24-byte box and return it as a 16-byte register pair
 *   (9 bytes of payload + zero padding).
 * Confidence: medium */
word_t sk_cnode_prop_box_read_0x78(word_t *out /*[2]*/)
{
        word_t mc, off, p;
    word_t box[3];   /* 24-byte box */
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x78);
    p = sk_reg_x20 + off;
    sk_metaclass_field(p, (word_t)box);
    out[1] = 0;
    out[0] = *(word_t *)p;
    return out[0];
}

/* FUN_0007830c @ 0x0007830c   (est. sk_cnode_prop_box_write_0x78)
 * Ghidra: void FUN_0007830c(undefined8 param_1,undefined1 param_2)  —
 *   materialize self[0x78] then store the 9-byte value (param_1 + param_2).
 * Confidence: medium */
void sk_cnode_prop_box_write_0x78(word_t param_1, word_t param_2)
{
        word_t mc, off, p;
    word_t box[3];   /* 24-byte box */
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x78);
    p = sk_reg_x20 + off;
    sk_acc_w3(p, (word_t)box);
    *(word_t *)p = param_1;
    *(word_t *)(p + 8) = param_2;
    return;
}

/* FUN_00078368 @ 0x00078368   (est. sk_cnode_prop_modify_0x78)
 * Ghidra: void FUN_00078368(void)  — Swift modify-with-copy for 0x78 (finish).
 * Confidence: medium */
void sk_cnode_prop_modify_0x78(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_000783b8 @ 0x000783b8   (est. sk_cnode_closure_invoke_0x138)
 * Ghidra: void FUN_000783b8(undefined8 *param_1,undefined8 *param_2)  —
 *   retain *param_1 then invoke closure vtable slot +0x138.
 * Confidence: medium */
void sk_cnode_closure_invoke_0x138(word_t *param_1, word_t *param_2)
{
    void (*fn)(void) = *(void (**)(void))(*(long *)*param_2 + 0x138);
    sk_swift_retain(*param_1);
    fn();
    return;
}

/* FUN_00078414 @ 0x00078414   (est. sk_cnode_prop_retain_get_0x80)
 * Ghidra: void FUN_00078414(void)  — Swift retain-getter for property at 0x80.
 * Confidence: medium */
void sk_cnode_prop_retain_get_0x80(void)
{
        word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x80);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(sk_reg_x20 + off));
    return;
}

/* FUN_00078454 @ 0x00078454   (est. sk_cnode_prop_modify_0x80)
 * Ghidra: void FUN_00078454(void)  — Swift modify-with-copy for 0x80 (finish2).
 * Confidence: medium */
void sk_cnode_prop_modify_0x80(void)
{
    sk_acc_write_pre();
    sk_acc_write_post();
    sk_acc_finish2();
    return;
}

/* FUN_00078498 @ 0x00078498   (est. sk_cnode_prop_modify2_0x80)
 * Ghidra: void FUN_00078498(void)  — Swift modify-with-copy for 0x80 (finish).
 * Confidence: medium */
void sk_cnode_prop_modify2_0x80(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_000784e8 @ 0x000784e8   (est. sk_cnode_closure_invoke_0x150)
 * Ghidra: void FUN_000784e8(undefined8 *param_1,undefined8 *param_2)  —
 *   retain *param_1 then invoke closure vtable slot +0x150.
 * Confidence: medium */
void sk_cnode_closure_invoke_0x150(word_t *param_1, word_t *param_2)
{
    void (*fn)(void) = *(void (**)(void))(*(long *)*param_2 + 0x150);
    sk_swift_retain(*param_1);
    fn();
    return;
}

/* FUN_00078544 @ 0x00078544   (est. sk_cnode_prop_retain_get_0x88)
 * Ghidra: void FUN_00078544(void)  — Swift retain-getter for property at 0x88.
 * Confidence: medium */
void sk_cnode_prop_retain_get_0x88(void)
{
        word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x88);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(sk_reg_x20 + off));
    return;
}

/* FUN_00078584 @ 0x00078584   (est. sk_cnode_prop_modify_0x88)
 * Ghidra: void FUN_00078584(void)  — Swift modify-with-copy for 0x88 (finish2).
 * Confidence: medium */
void sk_cnode_prop_modify_0x88(void)
{
    sk_acc_write_pre();
    sk_acc_write_post();
    sk_acc_finish2();
    return;
}

/* FUN_000785c8 @ 0x000785c8   (est. sk_cnode_prop_modify2_0x88)
 * Ghidra: void FUN_000785c8(void)  — Swift modify-with-copy for 0x88 (finish).
 * Confidence: medium */
void sk_cnode_prop_modify2_0x88(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_00078618 @ 0x00078618   (est. sk_cnode_closure_invoke_0x168)
 * Ghidra: void FUN_00078618(undefined8 *param_1,undefined8 *param_2)  —
 *   retain *param_1 then invoke closure vtable slot +0x168.
 * Confidence: medium */
void sk_cnode_closure_invoke_0x168(word_t *param_1, word_t *param_2)
{
    void (*fn)(void) = *(void (**)(void))(*(long *)*param_2 + 0x168);
    sk_swift_retain(*param_1);
    fn();
    return;
}

/* FUN_00078674 @ 0x00078674   (est. sk_cnode_prop_retain_get_0x90)
 * Ghidra: void FUN_00078674(void)  — Swift retain-getter for property at 0x90.
 * Confidence: medium */
void sk_cnode_prop_retain_get_0x90(void)
{
        word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x90);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(sk_reg_x20 + off));
    return;
}

/* FUN_000786b4 @ 0x000786b4   (est. sk_cnode_prop_modify_0x90)
 * Ghidra: void FUN_000786b4(void)  — Swift modify-with-copy for 0x90 (finish2).
 * Confidence: medium */
void sk_cnode_prop_modify_0x90(void)
{
    sk_acc_write_pre();
    sk_acc_write_post();
    sk_acc_finish2();
    return;
}

/* FUN_000786f8 @ 0x000786f8   (est. sk_cnode_prop_modify2_0x90)
 * Ghidra: void FUN_000786f8(void)  — Swift modify-with-copy for 0x90 (finish).
 * Confidence: medium */
void sk_cnode_prop_modify2_0x90(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_00078748 @ 0x00078748   (est. sk_cnode_prop_get_0x98)
 * Ghidra: undefined8 FUN_00078748(void)  — Swift getter for property at 0x98.
 * Confidence: medium */
word_t sk_cnode_prop_get_0x98(void)
{
        word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x98);
    sk_acc_read(0);
    return *(word_t *)(sk_reg_x20 + off);
}

/* FUN_00078784 @ 0x00078784   (est. sk_cnode_prop_set_0x98)
 * Ghidra: void FUN_00078784(void)  — Swift setter for property at 0x98.
 * Confidence: medium */
void sk_cnode_prop_set_0x98(word_t newValue)
{
        word_t mc, off;
    sk_acc_write_pre();
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x98);
    sk_acc_write_post();
    *(word_t *)(sk_reg_x20 + off) = newValue;
    return;
}

/* FUN_000787c8 @ 0x000787c8   (est. sk_cnode_prop_modify_0x98)
 * Ghidra: void FUN_000787c8(void)  — Swift modify-with-copy for 0x98 (finish).
 * Confidence: medium */
void sk_cnode_prop_modify_0x98(void)
{
    sk_acc_write_pre();
    sk_acc_modify();
    sk_acc_finish();
    return;
}

/* FUN_00078818 @ 0x00078818   (est. sk_cnode_alloc_and_init)
 * Ghidra: undefined8 FUN_00078818(undefined8,undefined8,undefined8,undefined8)
 *   — allocates a Swift array buffer then calls the big initializer
 *   FUN_00078880 with the four arguments; returns the buffer pointer.
 * Confidence: medium */
void sk_cnode_allocator_init(word_t param_1, word_t param_2, word_t param_3,
                             word_t param_4);   /* FUN_00078880 */

word_t sk_cnode_alloc_and_init(word_t a, word_t b, word_t c, word_t d)
{
    word_t buf;
    buf = sk_swift_array_alloc(0, 0, 0);
    sk_cnode_allocator_init(a, b, c, d);
    return buf;
}

/* FUN_00078880 @ 0x00078880   (est. sk_cnode_allocator_init)
 * Ghidra: void FUN_00078880(undefined8,long,undefined8,undefined8)  — the
 *   CNodeAllocator designated initializer (Swift init(asid:physAllocator:
 *   virtBase:virtEnd:tag:asanEnabled:rootSpaceId:shadowCNodeAllocator:
 *   faultDataECMode:)). Zeroes/initializes every stored property of the class
 *   (offsets 0x48,0x50,0x58,0x60,0x68,0x70,0x78,0x80,0x88,0x90,0x98), builds a
 *   0x38-byte CNodeEntry for the given object type, records it in the cnode
 *   table, allocates a 0x60-byte generic-entry descriptor, and stores the
 *   "space cap" + fault-data fields. Traps (SoftwareBreakpoint 0x78ec4) if an
 *   alignment/round-up check fails.
 * Confidence: low
 * Notes: PAC-authorized indirect calls through SUB_90000010f9008430; string
 *   refs DAT_00606a9c, DAT_0064e868, DAT_004c06c0, DAT_004baeb0/4baeb8,
 *   DAT_00665ba0; a helper entry built via FUN_0007b178/FUN_0007b1c0
 *   (Swift String endIndex helpers). */
void sk_cnode_allocator_init(word_t param_1, word_t param_2, word_t param_3,
                             word_t param_4)
{
    word_t *self;
    word_t u8;
    word_t u3, u5, u7;
    word_t l9, l10, l11, l12;
    word_t l13;
    word_t *pu;
    word_t aux16[2];        /* 16-byte register pair */
    word_t stack130[2];     /* 8-byte */
    word_t box80[4];        /* 32-byte */
    word_t box98[3];        /* 24-byte */
    word_t boxb8[4];        /* 32-byte */
    word_t f8, f0, e8, e0, d8, d0, c8, c0, v;

    self = (word_t *)sk_reg_x20;
    u8 = *(word_t *)(*(word_t *)self + 0x40);     /* physAllocator */
    l13 = *(word_t *)(*(word_t *)self + 0x38);    /* asid */
    f0 = param_3;
    c8 = param_4;
    u3 = sk_acc_w5(0, 0);
    d8 = sk_str_convert(u3, u8, l13);
    sk_acc_w7();
    /* v = class metadata / accessor context via the PAC code pointer. */
    l12 = (word_t)((word_t)stack130 - ((word_t)sk_identity(0) & 0xfffffffffffffff0));
    l9 = *(word_t *)(*(word_t *)self + 0x58);
    *(word_t *)((word_t)self + l9) = 0;              /* faultDataECMode */
    sk_acc_get(0);
    *(word_t *)((word_t)self + *(word_t *)(sk_identity(0) + 0x60)) = 0;
    sk_acc_get(0);
    pu = (word_t *)((word_t)self + *(word_t *)(sk_identity(0) + 0x78));
    *pu = 0; *(word_t *)(pu + 1) = 1;                /* 9-byte tag/flag value */
    sk_acc_get(0);
    l10 = *(word_t *)(sk_identity(0) + 0x88);
    *(word_t *)((word_t)self + l10) = 0x657778;      /* empty vector sentinel */
    sk_acc_get(0);
    *(word_t *)((word_t)self + *(word_t *)(sk_identity(0) + 0x90)) = u3;
    sk_acc_get(0);
    l11 = *(word_t *)(sk_identity(0) + 0x98);
    *(word_t *)((word_t)self + l11) = 0;
    sk_acc_get(0);
    v = *(word_t *)(sk_identity(0) + 0x48);
    f8 = *(word_t *)(l13 - 8);          /* Swift isa metadata */
    (*(void (**)(word_t, word_t, word_t))(f8 + 0x10))((word_t)self + v, param_1, l13);
    sk_acc_w3((word_t)self + l9, (word_t)box80);
    *(word_t *)((word_t)self + l9) = 1;
    sk_acc_get(0);
    e8 = param_2;
    sk_closure_enter(param_2, (word_t)self + *(word_t *)(sk_identity(0) + 0x70));
    sk_acc_w3((word_t)self + l11, (word_t)box98);
    *(word_t *)((word_t)self + l11) = c8;
    /* u5 = FUN_00078fec(u8): Swift String.count-style helper */
    l12 = (word_t)((word_t)stack130 - ((word_t)sk_identity(0) & 0xfffffffffffffff0));
    c8 = param_1;
    u5 = sk_string_end_index(u8);
    u3 = sk_acc_w6();
    u3 = sk_str_convert2(u3, u8, l13, 0x606a9c);
    sk_acc_w2(0, 0, 0, 0);
    d0 = sk_str_convert2(u8, l13, u3, 0x606a9c);
    v = u3;
    l9 = sk_runtime_roundup(u3, 0);
    if (-1 < (long)l9) {
        sk_acc_w14();
        u3 = d8;
        u5 = sk_str_convert2(u8, l13, d8);
        e0 = u8;
        u7 = sk_cnode_fn2(0);
        /* build the CNode entry value; append it to the table (0x88 buffer). */
        u3 = (word_t)self + l10;
        sk_swift_array_withcap(u3, (word_t)boxb8, 0x21, 0, 0);
        sk_cnode_buf_append((word_t)sk_cnode_resize_cb);
        l11 = *(word_t *)(*(word_t *)((word_t)self + l10) + 0x10);
        sk_cnode_buf_reserve(l11, (word_t)sk_cnode_resize_cb);
        l9 = *(word_t *)((word_t)self + l10);
        *(word_t *)(l9 + 0x10) = l11 + 1;
        *(word_t *)(l9 + l11 * 8 + 0x20) = u7;
        *(word_t *)((word_t)self + l10) = l9;
        sk_swift_array_destroy((word_t)boxb8);
        /* Build the 0x38-byte CNodeEntry descriptor from the "virtual"
         * parameters (physAllocator, virt base/end, tag, asan). */
        l10 = e8;
        u3 = *(word_t *)(e8 + 0x18);
        u8 = *(word_t *)(e8 + 0x20);
        u7 = sk_copy2(e8, u3);
        d8 = sk_f6d88(u7, u3, u8, u7);
        u3 = u7;   /* local_120 */
        sk_metaclass_get();
        (*(void (**)(word_t, word_t))(sk_identity(0) + 0x90))(0, u7);
        u8 = v;
        sk_acc_w15();
        v = sk_identity(0);           /* auVar14 low */
        c0 = sk_identity_hash(0);
        u7 = sk_identity_hash(u7, 0x665ca8, u8, 0x665ba0, d0);
        l9 = v;
        u7 = sk_cnode_align(0xff, v, e0);
        u7 = sk_identity_hash(0, u7);
        u7 = sk_swift_array_alloc(u7, 0x38, 7);
        l11 = sk_identity_hash(u7, 1);
        *(word_t *)(l11 + 0x20) = v;
        *(word_t *)(l11 + 0x30) = u3;
        u3 = sk_cnode_identity_scope(l11, u7);
        *(word_t *)((word_t)self + *(word_t *)(*(word_t *)self + 0x68)) = u3;
        u3 = sk_string_cache(0x64e868, 0x4c06c0);
        l11 = sk_swift_array_alloc(u3, 0x60, 7);
        *(word_t *)(l11 + 0x18) = *(word_t *)0x4baeb8;
        *(word_t *)(l11 + 0x10) = *(word_t *)0x4baeb0;
        u3 = sk_runtime_roundup(u8, d0);
        (*(void (**)(word_t, word_t))(f8 + 8))(c8, l9);
        *(word_t *)(l11 + 0x20) = v;
        *(word_t *)(l11 + 0x28) = 0;
        *(word_t *)(l11 + 0x30) = d8;
        *(word_t *)(l11 + 0x38) = 0;
        *(word_t *)(l11 + 0x40) = 0;
        *(word_t *)(l11 + 0x48) = u3;
        *(word_t *)(l11 + 0x50) = 0;
        *(word_t *)(l11 + 0x58) = 0;
        *(word_t *)((word_t)self + *(word_t *)(*(word_t *)self + 0x50)) = l11;
        *(word_t *)((word_t)self + *(word_t *)(*(word_t *)self + 0x80)) = f0;
        l9 = *(word_t *)(*(word_t *)self + 0x60);
        sk_acc_w3((word_t)self + l9, (word_t)boxb8);
        *(word_t *)((word_t)self + l9) = 1;
        sk_metaclass_chk(l10);
        return;
    }
    SK18_FATAL(0x78ec4);
}

/* =====================================================================
 * Swift String / CNode-entry helpers.
 * ===================================================================== */

/* FUN_00078fec @ 0x00078fec   (est. sk_string_end_index)
 * Ghidra: long FUN_00078fec(ulong param_1)  — Swift String._endIndex helper:
 *   dereferences the tagged/indirect string pointer (low bit set => indirect
 *   via *(p & ~1)) and returns p + 0x24 + *(int*)(p+0x24) (base + count).
 * Confidence: medium
 * Notes: String object layout: count int at +0x24. */
word_t sk_string_end_index(word_t p, ...)
{
    if ((p & 1) != 0)
        p = *(word_t *)(p & 0xfffffffffffffffeull);
    return (p + 0x24) + (word_t)(long)*(int *)(p + 0x24);
}

/* FUN_00079038 @ 0x00079038   (est. sk_cnode_entry_pack_closure)
 * Ghidra: undefined8 FUN_00079038(undefined8,undefined8)  — packs a CNode
 *   entry pair via two closure-witness invocations (from the class metadata
 *   +0x10 and a code* adapter), then appends the result to the self entry
 *   buffer by calling the +400 vtable slot; returns the packed entry.
 * Confidence: low
 * Notes: string/type refs DAT_00606a9c, LAB_00606ad4, DAT_00606fd4,
 *   LAB_00606fe4; PAC call through SUB_90000010f9008430; helpers
 *   FUN_0007b354/FUN_0007b384 (closure adapters), FUN_000ec8f8,
 *   FUN_0006df24, FUN_00365b6c, FUN_0006e7c0. */
word_t sk_cnode_entry_pack_closure(word_t param_1, word_t param_2)
{
        word_t self, u1, u2, u3, u5;
    word_t e16, e16b;
    word_t local90, local98, locala8, localb0;
    word_t lVar6, lVar7, lVar8;
    word_t box88[5];   /* 40-byte closure box */
    void (*fn)(word_t, word_t, word_t);
    /* lVar8/lVar6/lVar7 are stack-frame offsets produced by the PAC stack
     * probe (extraout_x8 chain); reconstructed as distinct locals. */
    lVar8 = (word_t)&localb0;
    lVar6 = lVar8;
    lVar7 = lVar6;

    self = *(word_t *)(sk_reg_x20 + 0x38);
    u1 = *(word_t *)(sk_reg_x20 + 0x40);
    local98 = param_2;
    u2 = sk_str_convert(0, u1, self, 0x606a9c, 0x606ad4);
    sk_acc_w7();
    e16 = sk_acc_w18();
    e16b = sk_acc_w19();
    (*(void (**)(word_t))(0x90000010f9008430ull))(sk_identity(0));
    u3 = sk_str_convert2(u1, self, u2, 0x606a9c, 0x606ab4);
    locala8 = sk_str_convert(0, u3, u2, 0x606fd4, 0x606fe4);
    sk_acc_w19();
    (*(void (**)(word_t))(0x90000010f9008430ull))(0);
    sk_acc_w7();
    (*(void (**)(word_t))(0x90000010f9008430ull))(*(word_t *)(sk_identity(0) + 0x40));
    localb0 = param_1;
    (*(void (**)(word_t, word_t, word_t))(e16b + 0x10))(lVar7, param_1, self);
    sk_closure_enter(local98, (word_t)box88);
    fn = (void (*)(word_t, word_t, word_t))sk_cnode_fn(u1);
    fn(lVar7, self, u1);
    fn = (void (*)(word_t, word_t, word_t))sk_cnode_fn2(u3);
    fn(lVar6, u2, u3);
    (*(void (**)(word_t, word_t))(e16 + 8))(lVar7, u2);
    u2 = sk_misc(0);
    sk_swift_array_init((word_t)&local90, lVar6, locala8, u2, 7, 0, 0);
    u5 = sk_copy3(u1, u1);
    u5 = (*(word_t (**)(word_t, word_t, word_t, word_t, word_t))(
          sk_reg_x20 + 400))(sk_reg_x20 + 400, lVar7, (word_t)box88, local90, u5);
    sk_metaclass_chk(local98);
    (*(void (**)(word_t, word_t))(e16b + 8))(localb0, u1);
    return u5;
}

/* FUN_000792d8 @ 0x000792d8   (est. sk_cnode_allocator_deinit)
 * Ghidra: long * FUN_000792d8(undefined8 param_1)  — the CNodeAllocator
 *   deinit: iterates the cnode entry table (0x40-stride) releasing each entry
 *   via a closure adapter, then releases every retained stored property
 *   (0x50,0x68,0x80,0x88,0x90 and the 0x70 box). Returns self.
 * Confidence: low
 * Notes: helper FUN_00078fec (string endIndex), FUN_000770e8 (closure
 *   adapter), FUN_0007b3b4, FUN_0007c164/FUN_0007c0ec (accessor ctx), and
 *   FUN_00377824/FUN_00377bec (string convert). */
word_t *sk_cnode_entry_teardown(word_t param_1)
{
        word_t self = sk_reg_x20;
    word_t u7, u1, u2, u8;
    word_t base, meta, d0, d8, f8, e8, e0, c8;
    word_t idx, count, slot;
    word_t local130, local120, local_frame;
    word_t box80[4], box98[3], boxc0[3], boxa8[2];
    void (*fn)(word_t, ...);
    void (*fn2)(word_t, ...);

    base = *(word_t *)self;
    u7 = *(word_t *)(base + 0x38);
    meta = *(word_t *)(base + 0x40);
    /* entry descriptor via string-convert helpers */
    d0 = sk_acc_w5(param_1, *(word_t *)(base + 0x40));
    d8 = sk_str_convert(sk_acc_w5(0, 0), d0, u7);
    sk_acc_w7();
    sk_acc_w19();
    (*(void (**)(word_t))(0x90000010f9008430ull))(0);
    sk_acc_w7();
    sk_acc_w19();
    (*(void (**)(word_t))(0x90000010f9008430ull))(0);
    idx = *(word_t *)(base + 0x88);
    sk_metaclass_field((word_t)self + idx, (word_t)box80);
    c8 = *(word_t *)((word_t)self + idx);
    base = *(word_t *)(c8 + 0x10);       /* count */
    local130 = sk_acc_w18();
    if (base != 0) {
        e8 = *(word_t *)(*(word_t *)self + 0x70);
        e0 = *(word_t *)(*(word_t *)self + 0x48);
        local120 = (word_t)self & 0xffffffffffffull | 0x6ae1000000000000ull;
        f8 = sk_string_end_index(d0);
        sk_acc_w14();
        f8 = sk_str_convert2(d0, u7, d8);
        u8 = sk_cnode_fn3();
        sk_swift_retain(c8);
        sk_metaclass_field((word_t)self + e8, (word_t)box98);
        count = 0x20;
        slot = 0;
        do {
            u8 = *(word_t *)(c8 + count);       /* entry payload */
            sk_closure_enter((word_t)self + e8, (word_t)boxc0);
            u2 = boxa8[1];
            u1 = boxa8[0];
            sk_copy2((word_t)boxc0, u1);
            fn = (void (*)(word_t, ...))sk_identity_hash(u2);
            fn(u8, u1, u2);
            sk_metaclass_chk((word_t)boxc0);
            (*(void (**)(word_t, word_t, word_t))local130)(local_frame, (word_t)self + e0, u7);
            fn2 = (void (*)(word_t, ...))f8;
            fn2(local_frame, u7, d0);
            (*(void (**)(word_t, word_t))local130)(local_frame, u7);
            fn2 = (void (*)(word_t, ...))u8;
            fn2(u8, d8, f8);
            (*(void (**)(word_t, word_t))local130)(local_frame, d8);
            count = count + 8;
            base = base - 1;
            slot = slot + 1;
        } while (base != 0);
        sk_swift_release(c8);
    }
    /* release every retained stored property */
    sk_acc_w4();
    sk_swift_release(*(word_t *)((word_t)self + *(word_t *)(sk_identity(0) + 0x48)));
    sk_acc_w4();
    sk_swift_release(*(word_t *)((word_t)self + *(word_t *)(sk_identity(0) + 0x50)));
    sk_acc_w4();
    sk_swift_release(*(word_t *)((word_t)self + *(word_t *)(sk_identity(0) + 0x68)));
    sk_acc_w4();
    sk_metaclass_chk((word_t)self + *(word_t *)(sk_identity(0) + 0x70));
    sk_acc_w4();
    sk_swift_release(*(word_t *)((word_t)self + *(word_t *)(sk_identity(0) + 0x80)));
    sk_swift_release(*(word_t *)((word_t)self + idx));
    sk_acc_w4();
    sk_swift_release(*(word_t *)((word_t)self + *(word_t *)(sk_identity(0) + 0x90)));
    return (word_t *)self;
}

/* FUN_00079678 @ 0x00079678   (est. sk_cnode_dispatch_a)
 * Ghidra: void FUN_00079678(void)  — calls sk_cnode_entry_lookup (792d8)
 *   then a no-op (FUN_0036b6ac).
 * Confidence: low */
void sk_cnode_dispatch_a(void)
{
    sk_cnode_entry_teardown(0);
    sk_nop_word();
    return;
}

/* FUN_0007967c @ 0x0007967c   (est. sk_cnode_dispatch_b)
 * Ghidra: void FUN_0007967c(void)  — same shape as 79678.
 * Confidence: low */
void sk_cnode_dispatch_b(void)
{
    sk_cnode_entry_teardown(0);
    sk_nop_word();
    return;
}

/* =====================================================================
 * CNode-entry buffer capacity / append logic (Swift stdlib-style).
 * ===================================================================== */

/* FUN_000796b0 @ 0x000796b0   (est. sk_cnode_capacity_roundup)
 * Ghidra: ulong FUN_000796b0(void)  — computes the rounded-up capacity for
 *   the cnode entry buffer: reads current count, adds the growth, and applies
 *   alignment/round-up with overflow traps (SoftwareBreakpoint at 0x79828..).
 * Confidence: low
 * Notes: uses sk_identity_hash as stand-ins for Swift runtime helpers
 *   (FUN_0014af94, FUN_0007eb2c, FUN_0014aedc); every checked multiply/add
 *   traps on overflow. */
word_t sk_cnode_capacity_roundup(void)
{
    word_t n, growth, stride, r, count, q, elem;
    word_t acc;
    acc = sk_acc_ctx();
    growth = (*(word_t (**)(word_t))(acc + 0xa0))(0);
    n = *(word_t *)(growth + 0x10);
    sk_swift_release(0);
    growth = (*(word_t (**)(word_t))sk_reg_x20 + 0x178)((word_t)sk_reg_x20 + 0x178);
    if ((long)growth < 0) SK18_FATAL(0x79828);
    count = n + growth;
    if (count < n) SK18_FATAL(0x7982c);
    r = sk_identity(0);         /* FUN_0007c018 -> metadata */
    r = sk_str_convert(r, 0, 0);
    sk_acc_w4();
    r = sk_str_convert2(0, 0, r);
    sk_acc_w19();
    stride = sk_runtime_roundup(0, 0);
    if ((long)stride < 0) SK18_FATAL(0x79830);
    count = count * stride;
    if ((word_t)((__int128)(long long)count * (__int128)(long long)stride >> 64) !=
        (word_t)((long)count >> 0x3f)) {
        SK18_FATAL(0x79834);
    }
    stride = sk_runtime_roundup2(1, r, r);
    if ((long)stride < 0) SK18_FATAL(0x79838);
    if (count + (stride - 1) < count) SK18_FATAL(0x7983c);
    if (stride == 0) SK18_FATAL(0x79840);
    elem = (stride != 0) ? (count + stride - 1) / stride : 0;
    if (n + elem >= n) {
        sk_acc_w19();
        stride = sk_identity_hash(0, 0);   /* FUN_0007eb2c */
        if ((long)stride < 0) SK18_FATAL(0x79848);
        count = (n + elem) * stride;
        if ((word_t)((__int128)(long long)(n + elem) * (__int128)(long long)stride >> 64) !=
            (word_t)((long)count >> 0x3f)) {
            SK18_FATAL(0x7984c);
        }
        sk_acc_w19();
        stride = sk_runtime_roundup(0, 0);
        if ((long)stride < 0) SK18_FATAL(0x79850);
        if (count + (stride - 1) >= count) {
            q = (count + stride - 1) & ~(word_t)(stride - 1);
            if ((long)q < 0) SK18_FATAL(0x79858);
            sk_acc_w19();
            elem = sk_runtime_roundup(0, 0);
            if (elem != 0) {
                return (elem != 0) ? q / elem : 0;
            }
            SK18_FATAL(0x7985c);
        }
        SK18_FATAL(0x79854);
    }
    SK18_FATAL(0x79844);
}

/* FUN_0007985c @ 0x0007985c   (est. sk_cnode_buffer_append_all)
 * Ghidra: void FUN_0007985c(ulong param_1)  — appends every "unset" entry
 *   from the source cnode table into the self buffer, re-encoding each
 *   entry's payload with the given value (param_1) when its flag byte is 0
 *   and its tag passes the validity check. This is the "relocate caps into a
 *   fresh CNode" bulk path.
 * Confidence: low
 * Notes: iterates the table at 0x40 stride (payload at +0x18, flag at +0x20);
 *   copy-on-write via sk_cnode_buf_reserve2 / sk_swift_buffer_unique; string
 *   refs DAT_00606a9c, DAT_00606ac4; helper FUN_0014aea4. */
void sk_cnode_buffer_append_all(word_t value)
{
    word_t acc, tbl, count, i, n, payload;
    word_t *slot;
    word_t (*getter)(word_t, ...);
    acc = sk_acc_ctx();
    (*(void (**)(word_t, word_t))(acc + 0x120))(0, 0);
    tbl = *(word_t *)sk_reg_x20;
    getter = (word_t (*)(word_t, ...))(*(word_t *)(tbl + 0xa0));
    n = getter(0);
    count = *(word_t *)(n + 0x10);
    sk_swift_release(0);
    i = 0;
    if (count != 0) {
        slot = (word_t *)(n + 0x58);
        do {
            n = (word_t)getter((word_t)(tbl + 0xa0) & 0xffffffffffffull | 0xeb6d000000000000ull);
            if (*(word_t *)(n + 0x10) <= i) SK18_FATAL(0x79a80);
            payload = n + 0x58;
            /* entry: payload fields + flag byte at +0x58 */
            n = *(word_t *)(payload - 0x28);
            acc = *(word_t *)(payload - 0x20);
            tbl = *(word_t *)(payload - 0x10);
            count = *(word_t *)(payload - 8);
            sk_swift_release(0);
            if (*(char *)payload == 0 && (sk_identity_hash(acc, 0) & 1) != 0) {
                /* COW-resize the target buffer and write the entry */
                word_t *box[2];
                (*(void (**)(word_t, ...))((*(word_t *)sk_reg_x20) + 0xb0))((word_t)box);
                tbl = *(word_t *)box[1];
                acc = sk_swift_buffer_unique(tbl);
                *(word_t *)box[1] = tbl;
                if ((acc & 1) == 0) {
                    tbl = sk_cnode_buf_reserve2(tbl);
                    *(word_t *)box[1] = tbl;
                }
                if (*(word_t *)(tbl + 0x10) <= i) SK18_FATAL(0x79a84);
                slot = (word_t *)(tbl + 0x58);
                *(word_t *)(slot - 0x28) = n;
                *(word_t *)(slot - 0x20) = acc;
                *(word_t *)(slot - 0x18) = value;
                *(word_t *)(slot - 0x10) = tbl;
                *(word_t *)(slot - 8) = count;
                *slot = 0;
                (*(void (**)(word_t, word_t, word_t))(box[0]))((word_t)box, (word_t)box, 0);
                acc = *(word_t *)(sk_identity(0) + 0x38);
                tbl = *(word_t *)(sk_identity(0) + 0x40);
                n = sk_str_convert(0, tbl, acc, 0x606a9c, 0x606ac4);
                sk_acc_w4();
                n = sk_str_convert2(0, 0, 0, 0);
                acc = sk_runtime_add(n, 0);
                if (value + acc < value) SK18_FATAL(0x79a88);
                value = value + acc;
            }
            i = i + 1;
            slot = slot + 0x40;
        } while (count != i);
    }
    return;
}

/* FUN_00079a88 @ 0x00079a88   (est. sk_cnode_entry_offset_by_id)
 * Ghidra: long FUN_00079a88(long param_1)  — returns the byte offset of the
 *   CNode entry whose key field equals param_1 (index * stride), computed
 *   with Swift overflow-checked multiply/add. Traps (0x79bb8) if the id is
 *   not found, and traps (0x79bac/0x79bb0) on size overflow.
 * Confidence: low
 * Notes: string ref s_InternalExclaveLauncher_CNode_sw_005bfc70 (0x5bfc70);
 *   helpers FUN_0007c178, FUN_0007eb2c, FUN_00377824/FUN_00377bec. */
word_t sk_cnode_entry_offset_by_id(word_t id)
{
    word_t ctx, tbl, idx, i, stride, n, base;
    word_t hi;
    ctx = sk_acc_ctx();
    hi = (*(word_t (**)(word_t))(ctx + 0x118))(0);
    if ((hi & 0xff) == 1) {
        sk_fatal_str(0x5bfc70 + 0x10);   /* "InternalExclaveLauncher/CNode.swift" */
        sk_assert_prep();
        sk_assert_fatal(0, 0, 0);
    }
    sk_acc_w15();
    tbl = (*(word_t (**)(word_t))(sk_identity(0) + 0xa0))(0);
    idx = 0;
    i = 0x20;
    for (;;) {
        if (*(word_t *)(tbl + 0x10) == idx) {
            sk_swift_release(0);
            SK18_FATAL(0x79bb8);
        }
        if (*(word_t *)(tbl + i) == id) break;
        idx = idx + 1;
        i = i + 0x40;
    }
    sk_swift_release(0);
    n = *(word_t *)(sk_identity(0) + 0x38);
    base = *(word_t *)(sk_identity(0) + 0x40);
    n = sk_acc_w6();
    n = sk_str_convert(n, base, n);
    sk_acc_w4();
    n = sk_str_convert2(base, n, n);
    stride = sk_arith(n, n);
    hi = idx * stride;
    if ((word_t)((__int128)(long long)idx * (long long)stride >> 64) != 0) {
        SK18_FATAL(0x79bac);
    }
    base = n;   /* base value from metadata */
    if (base + hi < base) SK18_FATAL(0x79bb0);
    return base + hi;
}

/* FUN_00079bf0 @ 0x00079bf0   (est. sk_cnode_entry_append_one)
 * Ghidra: void FUN_00079bf0(void)  — appends a single CNode entry: takes the
 *   accessor context, bumps the buffer count (COW via sk_cnode_buf_append),
 *   computes the destination slot, writes the 7 payload words + flag byte,
 *   then updates the count. Traps (0x7a0e4/0x7a0f0/0x7a0f8) on overflow.
 * Confidence: low
 * Notes: entry fields at +0x20..+0x58 within a 0x40-stride slot; helpers
 *   FUN_0007c140/FUN_0007c0ac/FUN_0007c0c4 (accessor ctx). */
void sk_cnode_entry_append_one(void)
{
    word_t *self;
    word_t u1, u3, u4, u7, u11, u12, u13, u16;
    word_t slot, count, stride;
    word_t lo, hi;
    void (*trap)(void) __attribute__((noreturn));
    word_t *box[2];

    sk_acc_ctx();
    u3 = (*(word_t (**)(void))(sk_identity(0) + 0xb8))();
    sk_metaclass_chk(0);
    u16 = *(word_t *)(sk_identity(0) + 0x38);
    if ((u16 & 0xfffffffffffffffeull) < (u16 & 0xfffffffffffffffeull)) {
        /* COW: reserve + append path */
        self = (word_t *)sk_reg_x20;
        u1 = *(word_t *)((word_t)self + *(word_t *)(*(word_t *)self + 0x38));
        (*(void (**)(word_t))(0x90000010f9008430ull))(0);
        u3 = sk_str_convert(0, 0, 0);
        u4 = sk_acc_w19();
        u7 = sk_runtime_add(u1, u3);
        u13 = sk_arith(u3, u7);
        if (u13 == 0) SK18_FATAL(0x7a0f0);
        if (u7 < u13) SK18_FATAL(0x7a0e4);
        stride = (u13 != 0) ? u7 / u13 : 0;
        count = (stride != 0) ? u1 / stride : 0;
        if ((long)count < 0) SK18_FATAL(0x7a0f0);
        u1 = (word_t)sk_reg_x20;
        slot = (word_t)self + count * 0x40;
        /* write entry fields */
        *(word_t *)(slot + 0x20) = u11;
        *(word_t *)(slot + 0x28) = u4;
        *(word_t *)(slot + 0x30) = u7;
        *(word_t *)(slot + 0x38) = 0;
        *(word_t *)(slot + 0x40) = u1 + u3 * u13;
        *(word_t *)(slot + 0x48) = u12;
        *(word_t *)(slot + 0x50) = 0;
        *(word_t *)(slot + 0x58) = 0;
        sk_acc_w12(0);
        (*(void (**)(word_t))(0x90000010f9008430ull))(0);
        sk_swift_release((word_t)self);
        return;
    }
    (void)u16;
    /* not reached in the COW-free fast path */
    SK18_FATAL(0x7a0f0);
}

/* =====================================================================
 * CNodeEntry constructors (build a packed 0x38-byte CNodeEntry).
 * ===================================================================== */

/* FUN_0007a718 / 7abe0 forward decls (defined below) + closure callbacks. */
void sk_cnode_entry_build(word_t *out, word_t *p);        /* FUN_0007a718 */
void sk_cnode_entry_last(word_t *out, word_t param_2);     /* FUN_0007abe0 */
void sk_cnode_build_cb_a(word_t a, word_t b, word_t c);   /* FUN_0007b524 */
void sk_cnode_build_cb_b(word_t a, word_t b, word_t c);   /* FUN_0007b544 */

/* Ghidra byte-concatenation shorthands for the packed entry tail. */
#define CONCAT71(h, l) (((word_t)(h) << 8) | ((word_t)(l) & 0xff))
#define CONCAT17(h, l) (((word_t)(h) & 0xff) | ((word_t)(l) << 8))

/* Packs the 7-word CNodeEntry output produced by sk_cnode_entry_build. */
static void sk_cnode_entry_pack(word_t *out, word_t w0, word_t w1, word_t w2,
                                word_t w3, word_t w4, word_t hi, word_t tail0,
                                word_t tail1)
{
    out[0] = w0;
    out[1] = w1;
    out[2] = w2;
    out[3] = w3;
    out[4] = w4;
    out[5] = hi;
    *(word_t *)((char *)out + 0x29) = tail0;   /* CONCAT17(uStack_70,uStack_77) */
    *(word_t *)((char *)out + 0x31) = tail1;   /* uStack_6f */
}

/* FUN_0007a120 @ 0x0007a120   (est. sk_cnode_entry_ctor_witness_a)
 * Ghidra: void FUN_0007a120(void)  — a Swift witness initializer: reads a
 *   value via the class metadata (+0x130), runs the modify/teardown sequence
 *   (FUN_0007c198/18c/128), invokes a stored closure, releases the value.
 * Confidence: low */
void sk_cnode_entry_ctor_witness_a(void)
{
    word_t u;
    sk_metaclass_get();
    u = (*(word_t (**)(void))(sk_identity(0) + 0x130))();
    sk_acc_w17();
    sk_acc_w16();
    sk_acc_w11();
    (*(void (**)(void))(sk_identity(0) + 0x0))();
    sk_swift_release(u);
    sk_acc_w8();
    return;
}

/* FUN_0007a1fc @ 0x0007a1fc   (est. sk_cnode_entry_ctor_0)
 * Ghidra: void FUN_0007a1fc(undefined8*,undefined8,undefined8,ulong,undefined8,
 *                           undefined8,ulong)  — CNodeEntry constructor (kind
 *   0): builds the 6-word parameter tuple [a3, a4&0xff, a5, a6, a7&0xff] +
 *   kind=0, materializes the entry via sk_cnode_entry_build, packs into out.
 * Confidence: medium */
void sk_cnode_entry_ctor_0(word_t *out, word_t a2, word_t a3, word_t a4,
                           word_t a5, word_t a6, word_t a7)
{
    word_t p[6];
    word_t r[7];
    (void)a2;
    p[0] = a3; p[1] = a4 & 0xff; p[2] = a5; p[3] = a6; p[4] = a7 & 0xff; p[5] = 0;
    sk_cnode_entry_build(r, p);
    sk_cnode_entry_pack(out, r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[6]);
    return;
}

/* FUN_0007a274 @ 0x0007a274   (est. sk_cnode_entry_ctor_empty_4)
 * Ghidra: void FUN_0007a274(undefined8 *param_1)  — CNodeEntry constructor
 *   with all-zero payload and kind=4.
 * Confidence: medium */
void sk_cnode_entry_ctor_empty_4(word_t *out)
{
    word_t p[6];
    word_t r[7];
    p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 4;
    sk_cnode_entry_build(r, p);
    sk_cnode_entry_pack(out, r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[6]);
    return;
}

/* FUN_0007a3dc @ 0x0007a3dc   (est. sk_cnode_entry_ctor_2)
 * Ghidra: void FUN_0007a3dc(undefined8*,undefined8,undefined8,ulong)  —
 *   CNodeEntry constructor (kind 2): tuple [a3, a4&1, 0, 0, 0].
 * Confidence: medium */
void sk_cnode_entry_ctor_2(word_t *out, word_t a2, word_t a3, word_t a4)
{
    word_t p[6];
    word_t r[7];
    (void)a2;
    p[0] = a3; p[1] = a4 & 1; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 2;
    sk_cnode_entry_build(r, p);
    sk_cnode_entry_pack(out, r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[6]);
    return;
}

/* FUN_0007a548 @ 0x0007a548   (est. sk_cnode_entry_ctor_3)
 * Ghidra: void FUN_0007a548(undefined8*,undefined8,ulong)  — CNodeEntry
 *   constructor (kind 3): tuple [a3&0xff, 0, 0, 0, 0].
 * Confidence: medium */
void sk_cnode_entry_ctor_3(word_t *out, word_t a2, word_t a3)
{
    word_t p[6];
    word_t r[7];
    (void)a2;
    p[0] = a3 & 0xff; p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 3;
    sk_cnode_entry_build(r, p);
    sk_cnode_entry_pack(out, r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[6]);
    return;
}

/* FUN_0007a6a0 @ 0x0007a6a0   (est. sk_cnode_entry_ctor_1)
 * Ghidra: void FUN_0007a6a0(undefined8*,undefined8,undefined8,undefined8,
 *                           undefined8,ulong,undefined8)  — CNodeEntry
 *   constructor (kind 1): tuple [a3, a4, a5, a6&0xff, a7].
 * Confidence: medium */
void sk_cnode_entry_ctor_1(word_t *out, word_t a2, word_t a3, word_t a4,
                           word_t a5, word_t a6, word_t a7)
{
    word_t p[6];
    word_t r[7];
    (void)a2;
    p[0] = a3; p[1] = a4; p[2] = a5; p[3] = a6 & 0xff; p[4] = a7; p[5] = 1;
    sk_cnode_entry_build(r, p);
    sk_cnode_entry_pack(out, r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[6]);
    return;
}

/* FUN_0007a5c4 @ 0x0007a5c4   (est. sk_cnode_entry_ctor_witness_b)
 * Ghidra: void FUN_0007a5c4(void)  — Swift witness initializer, same shape as
 *   7a120 (value via +0x130, teardown sequence, stored closure, release).
 * Confidence: low */
void sk_cnode_entry_ctor_witness_b(void)
{
    word_t u;
    sk_metaclass_get();
    u = (*(word_t (**)(void))(sk_identity(0) + 0x130))();
    sk_acc_w17();
    sk_acc_w16();
    sk_acc_w11();
    (*(void (**)(void))(sk_identity(0) + 0x0))();
    sk_swift_release(u);
    sk_acc_w8();
    return;
}

/* FUN_0007a2dc @ 0x0007a2dc   (est. sk_cnode_entry_ctor_closured_a)
 * Ghidra: void FUN_0007a2dc(undefined8 *param_1)  — CNodeEntry constructor
 *   that materializes the entry through a closure witness (FUN_0007b524)
 *   invoked via the accessor context, then packs the result into out.
 * Confidence: low */
void sk_cnode_entry_ctor_closured_a(word_t *out)
{
    word_t u, w;
    word_t box[2];
    sk_metaclass_get();
    u = (*(word_t (**)(void))(sk_identity(0) + 0x130))();
    sk_acc_w17();
    sk_acc_w16();
    (*(void (**)(word_t, word_t, word_t))(sk_identity(0) + 0x0))((word_t)&w,
        (word_t)sk_cnode_build_cb_a, (word_t)box);
    sk_swift_release(u);
    sk_cnode_entry_pack(out, w, w, w, w, w, w, w, w);
    return;
}

/* FUN_0007a454 @ 0x0007a454   (est. sk_cnode_entry_ctor_closured_b)
 * Ghidra: void FUN_0007a454(undefined8 *param_1)  — CNodeEntry constructor
 *   via closure witness FUN_0007b544, then packs into out.
 * Confidence: low */
void sk_cnode_entry_ctor_closured_b(word_t *out)
{
    word_t u, w;
    word_t box[2];
    sk_metaclass_get();
    u = (*(word_t (**)(void))(sk_identity(0) + 0x130))();
    sk_acc_w17();
    sk_acc_w16();
    (*(void (**)(word_t, word_t, word_t))(sk_identity(0) + 0x0))((word_t)&w,
        (word_t)sk_cnode_build_cb_b, (word_t)box);
    sk_swift_release(u);
    sk_cnode_entry_pack(out, w, w, w, w, w, w, w, w);
    return;
}

/* FUN_0007a718 @ 0x0007a718   (est. sk_cnode_entry_build)
 * Ghidra: void FUN_0007a718(undefined8 *param_1,undefined8 *param_2)  — the
 *   core CNodeEntry builder / "append with relocation" routine. Reads the
 *   6-word parameter tuple (param_2: 5 payload words + kind byte), validates
 *   the source and destination table element sizes (with overflow traps at
 *   0x7aa88/0x7aa8c/0x7aa90/0x7aa94/0x7aa98/0x7aa9c), computes the element
 *   stride, reserves room (calling sk_cnode_entry_append_one when full),
 *   writes the 7 payload words + flag byte into the next 0x40-stride slot,
 *   bumps the count, and returns the packed entry through param_1.
 * Confidence: low
 * Notes: heavy Swift ABI; string refs DAT_00606a9c, DAT_0065f380 (type table),
 *   0x671df8/0x6720e0 (demangled type names), 0x677830/0x677880; helpers
 *   FUN_0007c0ac/FUN_0007c0c4/FUN_0007c018 (accessor ctx), FUN_0019ea20
 *   (array init), FUN_0014aedc/FUN_0007eb2c (arith), FUN_0007b33c
 *   (alignment), FUN_002a4ab4 (fault builder), FUN_0007bfdc/FUN_001afa84
 *   (fatal paths). */
void sk_cnode_entry_build(word_t *out, word_t *p)
{
    word_t u15, u16, u17, u18, u19, u1, u2, u6, u7, u8, u9, u10, u11;
    word_t v, meta, stride, count, base, slot;
    word_t l4, l5, l12;
    word_t (*fn)(word_t, ...);
    word_t *box;

    u17 = p[1]; u16 = p[0]; u19 = p[3]; u18 = p[2]; u15 = p[4];
    u2 = *(word_t *)(p + 5);              /* kind byte */
    meta = *(word_t *)sk_reg_x20;
    fn = (word_t (*)(word_t, ...))(*(word_t *)(meta + 0xd0));
    l4 = fn(0);
    sk_metaclass_get();
    fn = (word_t (*)(word_t, ...))(*(word_t *)(sk_identity(0) + 0xa0));
    l5 = fn(0);
    l5 = *(word_t *)(l5 + 0x10);
    sk_swift_release(0);
    if (l4 != l5) {
        /* source/dest element-size mismatch -> fatal fault string */
        u11 = 0xe000000000000000ull;
        sk_fault_builder(0x21);
        sk_swift_release_masked(u11);
        u11 = 0xd00000000000001cull;
        u15 = 0x80000000005bfec0ull;
        l4 = fn(0);
        sk_vt_lookup(0x671df8);
        sk_identity_hash(0x677830, 0x671df8);
        sk_str_append(0, 0);
        sk_swift_release_masked(0);
        sk_str_append(0x3a, 0xe100000000000000ull);
        l4 = fn(0);
        l4 = *(word_t *)(l4 + 0x10);
        sk_swift_release(0);
        l4 = 0;
        sk_vt_lookup(0x6720e0);
        sk_identity_hash(0x677880, 0x6720e0);
        sk_str_append(0, 0);
        sk_swift_release_masked(0);
        sk_fatal_str(0);              /* noreturn path */
        sk_assert_fatal(0, 0xb, 2);
    }
    u11 = *(word_t *)(meta + 0x38);
    u1 = *(word_t *)(meta + 0x40);
    u6 = sk_acc_w6();
    u6 = sk_str_convert(u6, u1, u11, 0x606a9c);
    sk_acc_w4();
    u7 = sk_str_convert2(u1, u11, u6, 0x606a9c);
    u8 = sk_runtime_roundup(u6, u7);
    u9 = sk_arith(u6, u7);
    if (u9 == 0) SK18_FATAL(0x7aa88);
    u10 = fn(0);
    if (u8 < u9) SK18_FATAL(0x7aa8c);
    count = (u9 != 0) ? u8 / u9 : 0;
    u8 = (count != 0) ? u10 / count : 0;
    if ((long)u8 < 0) SK18_FATAL(0x7aa90);
    u9 = fn(0);
    if ((long)(u9 | count) < 0) SK18_FATAL(0x7aa94);
    sk_acc_ctx2();
    u10 = (*(word_t (**)(void))(sk_identity(0) + 0xb8))();
    if (u10 <= u8) {
        sk_cnode_entry_append_one();
        u9 = fn(0);
        if ((long)u9 < 0) SK18_FATAL(0x7aaa4);
    }
    l4 = sk_arith(u6, u7);
    if ((long)l4 < 0) SK18_FATAL(0x7aa98);
    u10 = (count != 0) ? u9 / count : 0;
    l5 = u9 - u10 * count;
    l12 = l5 * l4;
    if ((word_t)((__int128)(long long)l5 * (long long)l4 >> 64) !=
        (word_t)((long)l12 >> 0x3f)) SK18_FATAL(0x7aa9c);
    sk_acc_ctx2();
    u6 = (*(word_t (**)(void))(sk_identity(0) + 0xe8))();
    u11 = sk_cnode_align(0, u11, u1);
    sk_arr_init3((word_t)&base, u8, u6, u11);
    sk_swift_release(u6);
    sk_swift_release(base);
    if (base == 0) SK18_FATAL(0x7aaa8);
    l4 = fn(0);
    u11 = *(word_t *)(l4 + 0x10);
    sk_swift_release(0);
    sk_acc_ctx2();
    box = (word_t *)(*(word_t (**)(word_t))(sk_identity(0) + 0xb0))((word_t)&v);
    sk_acc_w10();
    sk_cnode_buf_append((word_t)box);
    l5 = *(word_t *)(*(word_t *)sk_reg_x20 + 0x10);
    sk_cnode_buf_reserve(l5, (word_t)box);
    l4 = *(word_t *)sk_reg_x20;
    *(word_t *)(l4 + 0x10) = l5 + 1;
    l4 = l4 + l5 * 0x40;
    *(word_t *)(l4 + 0x20) = base + l12;
    *(word_t *)(l4 + 0x28) = u11;
    *(word_t *)(l4 + 0x38) = u17;
    *(word_t *)(l4 + 0x30) = u16;
    *(word_t *)(l4 + 0x48) = u19;
    *(word_t *)(l4 + 0x40) = u18;
    *(word_t *)(l4 + 0x50) = u15;
    *(word_t *)(l4 + 0x58) = u2;
    (*(void (**)(word_t, word_t, word_t))box)((word_t)&v, (word_t)&v, 0);
    sk_acc_ctx2();
    /* epilogue: read last entry and copy it into the packed output */
    u15 = fn(0);
    sk_cnode_entry_last(out, 0);
    sk_swift_release(u15);
    if (out[7] == (word_t)-1) SK18_FATAL(0x7aaac);
    return;
}

/* FUN_0007abe0 @ 0x0007abe0   (est. sk_cnode_entry_last)
 * Ghidra: void FUN_0007abe0(undefined8 *param_1,long param_2)  — copies the
 *   last CNode entry (7 payload words + flag byte) from the buffer at param_2
 *   into the packed output param_1; empty buffer yields a zeroed entry with
 *   flag byte 0xff.
 * Confidence: medium */
void sk_cnode_entry_last(word_t *out, word_t param_2)
{
    word_t u2, u3, u4, u5, u6, u7, u8, u9;
    word_t *e;
    if (*(word_t *)(param_2 + 0x10) == 0) {
        u4 = 0; u5 = 0; u3 = 0xff; u6 = 0; u7 = 0; u8 = 0; u9 = 0; u2 = 0;
    } else {
        e = (word_t *)(param_2 + *(word_t *)(param_2 + 0x10) * 0x40);
        u5 = e[-3]; u4 = e[-4]; u7 = e[-1]; u6 = e[-2];
        u9 = e[1]; u8 = e[0]; u2 = e[2]; u3 = *(word_t *)(e + 3);
    }
    out[1] = u5; out[0] = u4; out[3] = u7; out[2] = u6;
    out[5] = u9; out[4] = u8; out[6] = u2;
    *(word_t *)(out + 7) = u3;
    return;
}

/* FUN_0007ac24 @ 0x0007ac24   (est. sk_cnode_find_value_by_id)
 * Ghidra: undefined8 FUN_0007ac24(long param_1)  — finds the entry whose key
 *   equals param_1 in the self buffer and returns its value field (with
 *   validity tag check); releases the buffer and returns 0 if not found.
 * Confidence: medium */
word_t sk_cnode_find_value_by_id(word_t id)
{
    word_t tbl, count, i, value;
    word_t *e;
    word_t meta, off;
    sk_metaclass_get();
    tbl = (*(word_t (**)(word_t))(sk_identity(0) + 0xa0))(0);
    count = *(word_t *)(tbl + 0x10);
    value = 0;
    if (count != 0) {
        i = 0;
        e = (word_t *)(tbl + 0x38);
        do {
            if (*(word_t *)(tbl + 0x10) <= i) SK18_FATAL(0x7acd8);
            if (*(word_t *)(e + 0x20) == 0 && *(word_t *)(e + 8) == id) {
                value = *(word_t *)(e - 0x18);
                meta = sk_identity_hash(*e, 3);
                if ((meta & 1) != 0) break;
            }
            i = i + 1;
            e = e + 0x40;
        } while (count != i);
    }
    sk_swift_release(tbl);
    return value;
}

/* FUN_0007b0cc @ 0x0007b0cc   (est. sk_cnode_table_contains_id)
 * Ghidra: undefined1 [16] FUN_0007b0cc(undefined8 param_1,long param_2)  —
 *   scans the table at param_2 for an entry whose tag matches param_1
 *   (sk_identity_hash of the flag byte). Returns {index, found:0} on match or
 *   {0, found:1} when the whole table was scanned.
 * Confidence: medium */
word_t sk_cnode_table_contains_id(word_t tag, word_t tbl)
{
    word_t i, count;
    i = 0;
    count = *(word_t *)(tbl + 0x10);
    for (;;) {
        if (count == i) { i = 0; return 1; }   /* not found */
        if ((sk_identity_hash(*(word_t *)(tbl + 0x20 + i), tag) & 1) != 0)
            return i;                          /* found at index i */
        i = i + 1;
    }
}

/* FUN_0007b134 @ 0x0007b134   (est. sk_cnode_table_index_of)
 * Ghidra: undefined1 [16] FUN_0007b134(long *param_1,long param_2)  — returns
 *   the index of the entry whose key equals *param_1 in the table at param_2;
 *   returns the sentinel (1<<64) when not found.
 * Confidence: medium */
word_t sk_cnode_table_index_of(word_t *key, word_t tbl)
{
    word_t i, count;
    word_t *e;
    i = 0;
    e = (word_t *)(tbl + 0x20);
    for (;;) {
        if (*(word_t *)(tbl + 0x10) == i) return (word_t)1 << 40;  /* not found */
        if (*e == *key) break;
        i = i + 1;
        e = e + 8;
    }
    return i;
}

/* FUN_0007b178 @ 0x0007b178   (est. sk_string_end_index_b)
 * Ghidra: long FUN_0007b178(ulong param_1)  — Swift String endIndex helper
 *   for a string with count field at +0x1c.
 * Confidence: medium */
word_t sk_string_end_index_b(word_t p)
{
    if ((p & 1) != 0) p = *(word_t *)(p & 0xfffffffffffffffeull);
    return (p + 0x1c) + (word_t)(long)*(int *)(p + 0x1c);
}

/* FUN_0007b1c0 @ 0x0007b1c0   (est. sk_string_end_index_c)
 * Ghidra: long FUN_0007b1c0(ulong param_1)  — Swift String endIndex helper
 *   for a string with count field at +0x14.
 * Confidence: medium */
word_t sk_string_end_index_c(word_t p)
{
    if ((p & 1) != 0) p = *(word_t *)(p & 0xfffffffffffffffeull);
    return (p + 0x14) + (word_t)(long)*(int *)(p + 0x14);
}

/* FUN_0007acd8 @ 0x0007acd8   (est. sk_cnode_alloc_object_and_cap)
 * Ghidra: void FUN_0007acd8(undefined8*,undefined8,undefined8,uint,undefined8)
 *   — CNodeAllocator.allocObjectAndCap: validates the requested object type
 *   against the "relocated cap" table (fatal string "Cannot give relocated
 *   cap when filling..." / "allocObjectAndCap is called with wrong object
 *   type" / "failed to allocate generic entry in a predictable way"), then
 *   allocates a fresh CNode entry (COW via sk_cnode_buf_append), copies the
 *   capability value into it, and packs the resulting entry into param_1.
 * Confidence: low
 * Notes: string refs 0x5bfca0, 0x5bfce0, 0x5bfd30; helpers FUN_0007b0cc,
 *   FUN_0007b134, FUN_0007b58c, FUN_0007b5f4, FUN_00077070, FUN_00077088,
 *   thunk_FUN_0000456c; fatal via sk_fatal_str + sk_assert_fatal. */
void sk_cnode_alloc_object_and_cap(word_t *out, word_t obj, word_t a3,
                                   word_t flags, word_t a5)
{
    word_t self, tbl, idx, value, off;
    word_t found;
    word_t a5_ret;
    word_t boxf8[3], boxd0[3], boxa8[3];
    word_t u6, u7;
    word_t (*fn)(word_t, ...);
    void (*trap)(void) __attribute__((noreturn));

    self = *(word_t *)sk_reg_x20;
    found = sk_cnode_table_contains_id(obj, 0x65f380);
    if ((found & 0xff) == 1) {
        sk_fatal_str(0x5bfca0 + 0x20);    /* "Cannot give relocated cap..." */
        sk_assert_prep();
        sk_assert_fatal(0, 0, 0);
    } else {
        if ((flags & 1) == 0 || (sk_identity_hash(obj, 3) & 1) != 0) {
            thunk_sk_cnode_probe(*(word_t *)(self + 0x38), *(word_t *)(self + 0x40));
            sk_acc_w13();
            (*(void (**)(word_t, word_t, word_t, word_t, word_t))(
                sk_identity(0) + 0x1b8))((word_t)&a5_ret, obj, 0, 0, a3);
            if (sk_reg_x21 != 0) return;
            sk_acc_w13();
            (*(void (**)(word_t, ...))(
                sk_identity(0) + 0x100))((word_t)boxd0, 0, 0);
            if (sk_identity(0) != 0) {
                /* COW-reserve + append the new generic entry */
                sk_cnode_buf_append((word_t)sk_cnode_resize_cb);
                tbl = *(word_t *)(*(word_t *)sk_reg_x20 + 0x10);
                sk_cnode_buf_reserve(tbl, (word_t)sk_cnode_resize_cb);
                self = *(word_t *)sk_reg_x20;
                *(word_t *)(self + 0x10) = tbl + 1;
                *(word_t *)(self + tbl * 8 + 0x20) = value;
                (*(void (**)(word_t, ...))(boxf8[0]))((word_t)boxd0, 0);
                sk_acc_w13();
                fn = (word_t (*)(word_t, ...))(*(word_t *)(sk_identity(0) + 0xa0));
                tbl = fn(0);
                idx = sk_cnode_table_index_of((word_t *)&value, tbl);
                sk_swift_release(tbl);
                if ((idx & 0xff) == 1) {
                    sk_metaclass_chk((word_t)boxd0);
                    sk_cnode_entry_pack(out, a5_ret, boxa8[1], boxa8[0], 0, 0,
                                        (word_t)0, (word_t)0, (word_t)0);
                    return;
                }
                tbl = fn(0);
                if ((long)idx < 0) SK18_FATAL(0x7b00c);
                if (*(word_t *)(tbl + 0x10) <= idx) SK18_FATAL(0x7b010);
                tbl = tbl + idx * 0x40;
                /* re-encode the entry in place if the flag byte is set */
                if (*(word_t *)(tbl + 0x58) == 0) {
                    sk_acc_w13();
                    /* COW copy then write */
                    sk_cnode_buf_reserve2(tbl);
                    tbl = tbl + idx * 0x40;
                    *(word_t *)(tbl + 0x30) = u6;
                    *(word_t *)(tbl + 0x38) = 0;
                    *(word_t *)(tbl + 0x40) = 0;
                    *(word_t *)(tbl + 0x48) = 0;
                    *(word_t *)(tbl + 0x50) = 0;
                    *(word_t *)(tbl + 0x58) = 0;
                    sk_metaclass_chk((word_t)boxd0);
                    sk_cnode_entry_pack(out, a5_ret, boxa8[1], boxa8[0], 0, 0,
                                        (word_t)0, (word_t)0, (word_t)0);
                    return;
                }
                sk_fatal_str(0x5bfce0 + 0x30);   /* wrong object type */
            }
        } else {
            sk_fatal_str(0x5bfd30 + 0x30);       /* failed to allocate generic */
        }
        sk_assert_prep();
        sk_assert_fatal(0, 0, 0);
    }
    (void)self; (void)off; (void)u7;
}

/* FUN_0007b2c8 @ 0x0007b2c8   (est. sk_cnode_buf_append)
 * Ghidra: void FUN_0007b2c8(code *param_1)  — generic growable-buffer append
 *   with copy-on-write: if the buffer is not uniquely owned (COW), rebuild it
 *   by calling the supplied resize callback param_1(count+1, ...). Updates
 *   *self to the (possibly new) buffer.
 * Confidence: medium */
word_t sk_cnode_buf_append(word_t fn, ...)
{
    word_t buf, uniq;
    word_t (*cb)(word_t, word_t, word_t, word_t);
    buf = *(word_t *)sk_reg_x20;
    uniq = sk_swift_buffer_unique(buf);
    *(word_t *)sk_reg_x20 = buf;
    if ((uniq & 1) == 0) {
        cb = (word_t (*)(word_t, word_t, word_t, word_t))fn;
        buf = cb(0, *(word_t *)(buf + 0x10) + 1, 1, buf);
        *(word_t *)sk_reg_x20 = buf;
    }
    return buf;
}

/* FUN_0007b1f0 @ 0x0007b1f0   (est. sk_cnode_buf_append_cb_0)
 * Ghidra: void FUN_0007b1f0(void)  — append with resize callback FUN_00072d5c.
 * Confidence: low */
void sk_cnode_buf_append_cb_0(void) { sk_cnode_buf_append(0x72d5c); return; }

/* FUN_0007b208 @ 0x0007b208   (est. sk_cnode_buf_append_cb_1)  FUN_0007340c */
void sk_cnode_buf_append_cb_1(void) { sk_cnode_buf_append(0x7340c); return; }

/* FUN_0007b220 @ 0x0007b220   (est. sk_cnode_buf_append_cb_2)  FUN_00073498 */
void sk_cnode_buf_append_cb_2(void) { sk_cnode_buf_append(0x73498); return; }

/* FUN_0007b238 @ 0x0007b238   (est. sk_cnode_buf_append_cb_3)  FUN_000738b0 */
void sk_cnode_buf_append_cb_3(void) { sk_cnode_buf_append(0x738b0); return; }

/* FUN_0007b250 @ 0x0007b250   (est. sk_cnode_buf_append_cb_4)  FUN_0007393c */
void sk_cnode_buf_append_cb_4(void) { sk_cnode_buf_append(0x7393c); return; }

/* FUN_0007b268 @ 0x0007b268   (est. sk_cnode_buf_append_cb_5)  FUN_00072c0c */
void sk_cnode_buf_append_cb_5(void) { sk_cnode_buf_append(0x72c0c); return; }

/* FUN_0007b280 @ 0x0007b280   (est. sk_cnode_buf_append_cb_6)  FUN_00073380 */
void sk_cnode_buf_append_cb_6(void) { sk_cnode_buf_append(0x73380); return; }

/* FUN_0007b298 @ 0x0007b298   (est. sk_cnode_buf_append_cb_7)  FUN_00073a64 */
void sk_cnode_buf_append_cb_7(void) { sk_cnode_buf_append(0x73a64); return; }

/* FUN_0007b2b0 @ 0x0007b2b0   (est. sk_cnode_buf_append_cb_8)  FUN_0007499c */
void sk_cnode_buf_append_cb_8(void) { sk_cnode_buf_append(0x7499c); return; }

/* FUN_0007b324 @ 0x0007b324   (est. sk_cnode_buf_reserve_with_cb)
 * Ghidra: void FUN_0007b324(undefined8 param_1)  — reserves capacity for the
 *   buffer using resize callback FUN_00072d5c.
 * Confidence: medium */
void sk_cnode_buf_reserve_with_cb(word_t param_1)
{
    sk_cnode_buf_reserve(param_1, 0x72d5c);
    return;
}
