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

/* ---- Shared kernel / Swift-runtime externs (ground truth FUN_ addresses). ---- */

/* Basic kernel helpers. */
extern void   sk_memcpy_w(word_t d, word_t s, word_t n);          /* FUN_00117cc4 */

/* Swift runtime primitives (called directly). */
extern word_t sk_swift_release(word_t obj);                       /* FUN_0036b118 */
extern word_t sk_swift_retain(word_t obj);                        /* FUN_0036b270 */
extern word_t sk_swift_array_alloc(word_t a, word_t b, word_t c); /* FUN_0036a940 */
extern word_t sk_swift_array_withcap(word_t a, word_t b, word_t c,
                                     word_t d, word_t e);         /* FUN_0036a1a0 */
extern void   sk_swift_array_destroy(word_t a);                   /* FUN_0036a20c */
extern word_t sk_swift_buffer_unique(word_t buf);                 /* FUN_003a261c */
extern void   sk_swift_release_masked(word_t v);                  /* FUN_003a25d4 */
extern void   sk_swift_memmove_log(word_t a, word_t b, word_t c,
                                   word_t d);                     /* FUN_0035b67c */
extern word_t sk_swift_array_init(word_t a, word_t b, word_t c,
                                  word_t d, word_t e, word_t f, word_t g);
                                                                  /* FUN_00365b6c */

/* Swift String / metadata helpers. */
extern word_t sk_str_convert(word_t a, word_t b, word_t c);       /* FUN_00377824 */
extern word_t sk_str_convert2(word_t a, word_t b, word_t c);      /* FUN_00377bec */
extern word_t sk_metaclass_get(void);                             /* FUN_000027e8 */
extern word_t sk_metaclass_field(word_t a, word_t b);             /* FUN_00002828 */
extern word_t sk_metaclass_chk(word_t a);                         /* FUN_000026e8 */
extern word_t sk_string_cache(word_t a, word_t b);                /* FUN_00002534 */
extern word_t sk_vt_lookup(word_t a);                             /* FUN_00027724 */
extern word_t sk_identity_hash(word_t a, word_t b);               /* FUN_0001c294 */
extern word_t sk_identity(word_t a);                              /* FUN_0001a1c8 */
extern word_t sk_runtime_roundup(word_t a, word_t b);             /* FUN_0014aedc */
extern word_t sk_runtime_roundup2(word_t a, word_t b, word_t c);  /* FUN_0014af94 */
extern word_t sk_runtime_add(word_t a, word_t b);                 /* FUN_0014aea4 */
extern word_t sk_runtime_align(word_t a, word_t b, word_t c);     /* FUN_0014afe0 */
extern word_t sk_arith(word_t a, word_t b);                       /* FUN_0007eb2c */
extern word_t sk_arr_init3(word_t a, word_t b, word_t c, word_t d); /* FUN_0019ea20 */
extern word_t sk_closure_enter(word_t a, word_t b);               /* FUN_0006e7c0 */
extern word_t sk_copy2(word_t a, word_t b);                       /* FUN_0006a4c0 */
extern word_t sk_copy3(word_t a, word_t b);                       /* FUN_0006df24 */
extern word_t sk_scoped_enter(word_t a, word_t b);                /* FUN_001a84f4 */
extern void   sk_scoped_exit(void);                               /* FUN_001a8564 */
extern word_t sk_bind(word_t a, word_t b);                        /* thunk_FUN_002298d4 */
extern word_t sk_str_append(word_t a, word_t b);                  /* thunk_FUN_002acbb8 */
extern word_t sk_fault_builder(word_t a);                         /* FUN_002a4ab4 */
extern word_t sk_assert_prep(void);                               /* FUN_00002818 */
extern void   sk_assert_fatal(word_t a, word_t b, word_t c) __attribute__((noreturn));
                                                                  /* FUN_001afa84 */
extern void   sk_fatal_str(word_t a) __attribute__((noreturn));   /* FUN_0007bfdc */
extern word_t sk_misc(word_t a, word_t b);                        /* FUN_000ec8f8 */
extern void   sk_nop_word(void);                                  /* FUN_0036b6ac */

/* Swift stored-property accessor state-machine helpers (near-region). */
extern word_t sk_acc_read(word_t off);                            /* FUN_0007c004 */
extern void   sk_acc_write_pre(void);                             /* FUN_0007bfac */
extern void   sk_acc_write_post(void);                            /* FUN_0007bff0 */
extern void   sk_acc_modify(void);                                /* FUN_0007bfc8 */
extern void   sk_acc_finish(void);                                /* FUN_0007c0a0 */
extern void   sk_acc_finish2(void);                               /* FUN_0007c158 */
extern word_t sk_acc_get(word_t a);                               /* FUN_0007c0b8 */
extern word_t sk_acc_ctx(void);                                   /* FUN_0007c0c4 */
extern void   sk_acc_ctx2(void);                                  /* FUN_0007c0ac */
extern word_t sk_acc_w2(word_t a, word_t b, word_t c, word_t d);  /* FUN_0007c0d4 */
extern word_t sk_acc_w3(word_t a, word_t b);                      /* FUN_0007c0e0 */
extern void   sk_acc_w4(void);                                    /* FUN_0007c0ec */
extern word_t sk_acc_w5(word_t a, word_t b);                      /* FUN_0007c0f8 */
extern word_t sk_acc_w6(void);                                    /* FUN_0007c018 */
extern void   sk_acc_w7(void);                                    /* FUN_0007c028 */
extern void   sk_acc_w8(void);                                    /* FUN_0007c038 */
extern word_t sk_acc_w9(void);                                    /* FUN_0007c070 */
extern word_t sk_acc_w10(void);                                   /* FUN_0007c088 */
extern void   sk_acc_w11(void);                                   /* FUN_0007c128 */
extern word_t sk_acc_w12(word_t a);                               /* FUN_0007c140 */
extern word_t sk_acc_w13(void);                                   /* FUN_0007c14c */
extern void   sk_acc_w14(void);                                   /* FUN_0007c164 */
extern word_t sk_acc_w15(void);                                   /* FUN_0007c178 */
extern void   sk_acc_w16(void);                                   /* FUN_0007c18c */
extern void   sk_acc_w17(void);                                   /* FUN_0007c198 */
extern word_t sk_acc_w18(void);                                   /* FUN_0007c1a4 */
extern word_t sk_acc_w19(void);                                   /* FUN_0007c1c4 */
extern word_t sk_acc_w20(void);                                   /* FUN_0007c1d0 */

/* CNode-entry buffer grow/resize helpers (copy-on-write). */
extern word_t sk_cnode_buf_append(word_t buf);                    /* FUN_0007b2c8 */
extern word_t sk_cnode_buf_reserve(word_t buf, word_t fn);        /* FUN_0007b4a4 */
extern word_t sk_cnode_buf_reserve2(word_t buf);                  /* FUN_0007b4e8 */
extern word_t sk_cnode_align(word_t a, word_t b, word_t c);       /* FUN_0007b33c */
extern word_t sk_cnode_fn(word_t a);                              /* FUN_0007b354 */
extern word_t sk_cnode_fn2(word_t a);                             /* FUN_0007b384 */
extern word_t sk_cnode_fn3(void);                                 /* FUN_0007b3b4 */

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
 * Notes: self extent held in unaff_x20/unaff_x21 (Swift array buffer header). */
void sk_cnode_buf_alloc(word_t param_1)
{
    extern word_t unaff_x20, unaff_x21;
    (void)unaff_x20; (void)unaff_x21;
    sk_swift_array_alloc(param_1, (word_t)&unaff_x20 + (word_t)&unaff_x21 + 0x20, 7);
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
    extern long unaff_x19;
    *(word_t *)(unaff_x19 + 0x10) = 0;
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
    extern word_t *unaff_x20;
    sk_swift_buffer_unique(*unaff_x20);
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
    extern word_t *unaff_x20;
    sk_swift_buffer_unique(*unaff_x20);
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
    extern word_t unaff_x20;
    word_t local;
    sk_scoped_enter((word_t)&local, *(word_t *)(unaff_x20 + 0x28));
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
    extern word_t *unaff_x20;
    sk_swift_buffer_unique(*unaff_x20);
    return;
}

/* FUN_000778d4 @ 0x000778d4   (est. sk_cnode_dispatch_1)
 * Ghidra: void FUN_000778d4(void)  — calls FUN_00070674(1, w19, 0) (region
 *   dispatch helper); single-byte argument carried in unaff_w19.
 * Confidence: low
 * Notes: args dropped by the decompiler. */
void sk_cnode_dispatch_1(void)
{
    extern word_t unaff_w19;
    (void)unaff_w19;
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
    extern word_t unaff_x22;
    word_t u;
    u = *(word_t *)(unaff_x22 + 0x28);
    sk_copy2(unaff_x22 + 8, *(word_t *)(unaff_x22 + 0x20));
    return u;
}

/* FUN_00077960 @ 0x00077960   (est. sk_cnode_span_copy_2)
 * Ghidra: undefined8 FUN_00077960(void)  — same shape as 77934 for a
 *   different stored property (self[0x28] after copying buffer).
 * Confidence: medium */
word_t sk_cnode_span_copy_2(void)
{
    extern word_t unaff_x20;
    word_t u;
    u = *(word_t *)(unaff_x20 + 0x28);
    sk_copy2(unaff_x20 + 8, *(word_t *)(unaff_x20 + 0x20));
    return u;
}

/* FUN_0007798c @ 0x0007798c   (est. sk_cnode_identity_scope)
 * Ghidra: undefined8 FUN_0007798c(undefined8 param_1)  — enters a Swift
 *   identity scope (sk_identity_hash(0)) and returns param_1 unchanged.
 * Confidence: medium
 * Notes: FUN_00310d34(0) + FUN_0001a1c8(). */
word_t sk_cnode_identity_scope(word_t param_1)
{
    sk_identity(0);
    return param_1;
}

/* FUN_00077a90 @ 0x00077a90   (est. sk_cnode_self_deref)
 * Ghidra: undefined8 FUN_00077a90(void)  — returns *self (Swift value load).
 * Confidence: medium */
word_t sk_cnode_self_deref(void)
{
    extern word_t *unaff_x20;
    return *unaff_x20;
}

/* FUN_00077b58 @ 0x00077b58   (est. sk_cnode_bind_field)
 * Ghidra: void FUN_00077b58(undefined8 param_1)  — binds param_1 against
 *   *self via sk_bind(param_1, *self) (Swift closure bind).
 * Confidence: medium */
void sk_cnode_bind_field(word_t param_1)
{
    extern word_t *unaff_x20;
    sk_bind(param_1, *unaff_x20);
    return;
}

/* FUN_00077b84 @ 0x00077b84   (est. sk_cnode_scoped_bind)
 * Ghidra: void FUN_00077b84(void)  — scoped bind: enter scope, bind *self,
 *   exit scope.
 * Confidence: medium */
void sk_cnode_scoped_bind(void)
{
    extern word_t *unaff_x20;
    word_t local[9];   /* 72-byte scope frame */
    sk_scoped_enter((word_t)local, 0);
    sk_bind(*unaff_x20, 0);
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
    extern word_t unaff_x20;
    sk_swift_release(*(word_t *)(unaff_x20 + 0x10));
    *(word_t *)(unaff_x20 + 0x10) = param_1;
    return;
}

/* FUN_00077d64 @ 0x00077d64   (est. sk_cnode_prop_retain_get_0x50)
 * Ghidra: void FUN_00077d64(void)  — Swift retain-getter for the stored
 *   property at metadata offset 0x50: resolve offset, load self[off], retain.
 * Confidence: medium */
void sk_cnode_prop_retain_get_0x50(void)
{
    extern word_t unaff_x20;
    word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x50);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(unaff_x20 + off));
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
    extern word_t unaff_x20;
    word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x58);
    sk_acc_read(0);
    return *(word_t *)(unaff_x20 + off);
}

/* FUN_00077e74 @ 0x00077e74   (est. sk_cnode_prop_set_0x58)
 * Ghidra: void FUN_00077e74(void)  — Swift setter for property at 0x58:
 *   self[off] = newValue (w19).
 * Confidence: medium */
void sk_cnode_prop_set_0x58(word_t newValue)
{
    extern word_t unaff_x20;
    word_t mc, off;
    sk_acc_write_pre();
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x58);
    sk_acc_write_post();
    *(word_t *)(unaff_x20 + off) = newValue;
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
    extern word_t unaff_x20;
    word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x60);
    sk_acc_read(0);
    return *(word_t *)(unaff_x20 + off);
}

/* FUN_00077f44 @ 0x00077f44   (est. sk_cnode_prop_set_0x60)
 * Ghidra: void FUN_00077f44(void)  — Swift setter for property at 0x60.
 * Confidence: medium */
void sk_cnode_prop_set_0x60(word_t newValue)
{
    extern word_t unaff_x20;
    word_t mc, off;
    sk_acc_write_pre();
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x60);
    sk_acc_write_post();
    *(word_t *)(unaff_x20 + off) = newValue;
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
    extern word_t unaff_x20;
    word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x68);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(unaff_x20 + off));
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
    extern word_t unaff_x20;
    word_t mc, off;
    word_t box[3];   /* 24-byte box */
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x70);
    sk_metaclass_field(unaff_x20 + off, (word_t)box);
    sk_closure_enter(unaff_x20 + off, param_1);
    return;
}

/* FUN_000781b4 @ 0x000781b4   (est. sk_cnode_prop_reset_0x70)
 * Ghidra: void FUN_000781b4(void)  — Swift modify-with-copy for the boxed
 *   property at 0x70: build an empty array with capacity 0x21, invoke the
 *   modify, then destroy the temp.
 * Confidence: medium */
void sk_cnode_prop_reset_0x70(void)
{
    extern word_t unaff_x20;
    word_t mc, off;
    word_t box[3];   /* 24-byte temp */
    sk_acc_write_pre();
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x70);
    sk_swift_array_withcap(unaff_x20 + off, (word_t)box, 0x21, 0, 0);
    sk_metaclass_chk(unaff_x20 + off);
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
    extern word_t unaff_x20;
    word_t mc, off, p;
    word_t box[3];   /* 24-byte box */
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x78);
    p = unaff_x20 + off;
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
    extern word_t unaff_x20;
    word_t mc, off, p;
    word_t box[3];   /* 24-byte box */
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x78);
    p = unaff_x20 + off;
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
    extern word_t unaff_x20;
    word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x80);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(unaff_x20 + off));
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
    extern word_t unaff_x20;
    word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x88);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(unaff_x20 + off));
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
    extern word_t unaff_x20;
    word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x90);
    sk_acc_read(0);
    sk_swift_retain(*(word_t *)(unaff_x20 + off));
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
    extern word_t unaff_x20;
    word_t mc, off;
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x98);
    sk_acc_read(0);
    return *(word_t *)(unaff_x20 + off);
}

/* FUN_00078784 @ 0x00078784   (est. sk_cnode_prop_set_0x98)
 * Ghidra: void FUN_00078784(void)  — Swift setter for property at 0x98.
 * Confidence: medium */
void sk_cnode_prop_set_0x98(word_t newValue)
{
    extern word_t unaff_x20;
    word_t mc, off;
    sk_acc_write_pre();
    mc = sk_metaclass_get();
    off = *(word_t *)(mc + 0x98);
    sk_acc_write_post();
    *(word_t *)(unaff_x20 + off) = newValue;
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
word_t sk_cnode_alloc_and_init(word_t a, word_t b, word_t c, word_t d)
{
    word_t buf;
    buf = sk_swift_array_alloc(0, 0, 0);
    sk_cnode_init(a, b, c, d);
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
    extern word_t *unaff_x20;
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

    self = unaff_x20;
    u8 = *(word_t *)(*self + 0x40);     /* physAllocator */
    l13 = *(word_t *)(*self + 0x38);    /* asid */
    f0 = param_3;
    c8 = param_4;
    u3 = sk_acc_w5(0, 0);
    d8 = sk_str_convert(u3, u8, l13);
    sk_acc_w7();
    /* v = class metadata / accessor context via the PAC code pointer. */
    l12 = (word_t)((word_t)stack130 - ((word_t)sk_identity(0) & 0xfffffffffffffff0));
    l9 = *(word_t *)(*self + 0x58);
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
    d0 = sk_str_convert2b(u8, l13, u3, 0x606a9c);
    v = u3;
    l9 = sk_runtime_roundup(u3, 0);
    if (-1 < (long)l9) {
        sk_acc_w14();
        u3 = d8;
        u5 = sk_str_convert2b(u8, l13, d8);
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
        d8 = sk_identity_hash(u7, u3, u8, u7);
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
        *(word_t *)((word_t)self + *(word_t *)(*self + 0x68)) = u3;
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
        *(word_t *)((word_t)self + *(word_t *)(*self + 0x50)) = l11;
        *(word_t *)((word_t)self + *(word_t *)(*self + 0x80)) = f0;
        l9 = *(word_t *)(*self + 0x60);
        sk_acc_w3((word_t)self + l9, (word_t)boxb8);
        *(word_t *)((word_t)self + l9) = 1;
        sk_metaclass_chk(l10);
        return;
    }
    SK18_FATAL(0x78ec4);
}
