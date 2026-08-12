/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in
 * the cl4_kernel.raw program. All names are estimates unless string/header
 * matched.
 * Slice R53: 0x3a6c28-0x3ba390.
 * This slice is the tagged-value stream serializer/deserializer: a
 * Tightbeam-style compact-data subsystem that turns a byte stream (read
 * through a stream-context: +0x38 data, +0x40 end, +0x48 position) into a
 * tree of tagged value nodes, and back. Every node is a small block: [0] data
 * pointer, [1] count/value word, [2] = 16-bit tag at +0x10, byte at +0x12 =
 * sub-type/flags. A per-context value stack (array at +0x58, count at +0x60)
 * builds/consumes nested values. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* Node accessors (node = uint64_t*). */
#define NODE_TAG(n)    (*(uint16_t *)((char *)(n) + 0x10))
#define NODE_SUBT(n)   (*(uint8_t  *)((char *)(n) + 0x12))
#define NODE_DATA(n)   ((void *)((n)[0]))
#define NODE_VAL(n)    ((n)[1])
#define NODE_SETTAG(n,t) (*(uint16_t *)((char *)(n) + 0x10) = (t))
#define NODE_SETSUBT(n,t)(*(uint8_t  *)((char *)(n) + 0x12) = (t))

/* Stream context field accessors (st = uint64_t* stream context). */
#define STREAM_DATA(st)  (*(char **)((char *)(st) + 0x38))
#define STREAM_END(st)   (*(uint64_t *)((char *)(st) + 0x40))
#define STREAM_POS(st)   (*(uint64_t *)((char *)(st) + 0x48))
#define STACK_BASE(st)   (*(uint64_t **)((char *)(st) + 0x58))
#define STACK_CNT(st)    (*(uint32_t *)((char *)(st) + 0x60))
#define STACK_ELEM(st,i) ((uint64_t *)(STACK_BASE(st)[(i)]))
#define STACK_TOP(st)    STACK_ELEM(st, STACK_CNT(st)-1)

static void memcpy_placeholder(void *d, const void *s, unsigned long n)
{ volatile char *x = d; const char *y = s; unsigned long i; for (i = 0; i < n; i++) x[i] = y[i]; }

/* ------------------------------------------------------------------ *
 * Shared stream / node helpers (extern; owned by sibling slices).
 * ------------------------------------------------------------------ */
extern uint64_t *sk_node_alloc(uint64_t *st, long n);         /* FUN_003a3898 */
extern void sk_node_add(uint64_t *parent, uint64_t *child, uint64_t *st); /* FUN_003a3460 */
extern uint64_t *sk_node_push(uint64_t *st, int tag, uint64_t *node);  /* FUN_003a4b38 */
extern uint64_t *sk_node_push2(uint64_t *st, int tag, uint64_t *a, uint64_t *b); /* FUN_003a4b98 */
extern void sk_node_finalize(uint64_t *node, int flag);       /* FUN_003a36d8 */
extern void sk_out_str(uint64_t *out, const char *str, long len); /* FUN_00112e8c */
extern uint64_t *sk_stream_dispatch(uint64_t *st);            /* FUN_003a672c */
extern uint64_t sk_val_get(uint64_t *st);                     /* FUN_003a663c */
extern uint64_t *sk_stream_pop(uint64_t *st);                 /* FUN_003a58b0 */
extern long sk_tag_simple(int tag);                           /* FUN_003a3040 */
extern uint64_t *sk_alloc_scalar(uint64_t *st, long n);       /* FUN_00365660 */
extern void sk_lock(void *lock, long op);                     /* thunk_FUN_00012568 */
extern long sk_query_flag(void);                              /* FUN_003b903c */
extern void sk_canary_panic(void) __attribute__((noreturn));  /* FUN_0011d7e8 */
extern void sk_fatal(void) __attribute__((noreturn));         /* FUN_004b89f8 */
extern uint64_t sk_ctx_op(uint64_t *a, uint64_t b, uint64_t *c, uint64_t *d, uint64_t *e); /* FUN_003a4c14 */
extern uint64_t *sk_tag_convert(uint64_t *st, uint64_t *node, int tag); /* FUN_003a4d5c */
extern void sk_log_msg(uint64_t *a, uint64_t *b);             /* FUN_00112db4 */
extern long sk_len_query(uint64_t v);                         /* FUN_00115080 */
extern void sk_grow_buf(uint64_t *st, uint64_t *buf, uint32_t *cap, int n); /* FUN_003a3aec */
extern uint64_t *sk_node_make(uint64_t *st, int tag, void *arg); /* FUN_003a3a10 */
extern void sk_grow_ptrs(uint64_t *st, uint64_t *buf, uint32_t *cap, int n); /* FUN_003a3578 */
extern void sk_ctx_setup2(uint64_t *a, long b, uint64_t *c);  /* FUN_003a4110 */
extern void sk_ctx_op2(uint64_t *a, ...);                     /* FUN_003a4f5c / 003a4ca8 */
extern void sk_obj_lock(uint64_t obj, long op);               /* FUN_00116bb4 */
extern uint64_t *sk_val_get_alt(uint64_t *st, uint32_t tag);  /* FUN_003a6874 */
extern uint64_t *sk_003a3a70(uint64_t *st, void *src, uint64_t n, uint64_t *len); /* FUN_003a3a70 */
extern void sk_write_data3(void *st, void *tag, void *fn, void *out); /* FUN_003b0be0 */
extern void sk_write_data4(uint64_t *out);                            /* FUN_003b0d64 */
extern char DAT_005d37d2[]; extern char DAT_005d37e1[]; extern char DAT_005d37cb[];
extern char DAT_005d356c[]; extern char DAT_005d37d0[]; extern char DAT_005d37c9[];
extern char DAT_005d3568[]; extern char DAT_005d37d7[]; extern char DAT_005d37e5[];
extern char DAT_005d3810[]; extern char DAT_005d6b7d[]; extern char DAT_005d6c15[];
extern char s__callee_guaranteed_005d6e4e[]; extern char s__convention_thin__005d6e6f[];
extern char s__callee_owned_005d6e61[]; extern char s__callee_unowned_005d6e3e[];
extern char s_block_005d6e81[]; extern char DAT_005d6cd7[]; extern char s_closure_005d6e9a[];
extern char s_method_005d6e87[]; extern char s_objc_method_005d6e8e[]; extern char s_witness_method_005d6ea2[];
extern char s_yield_once_005d57a1[]; extern char s_yield_many_005d57b9[]; extern char s_yield_once_2_005d57ac[];
extern char s__Sendable_005d6eb1[]; extern char s__async_005d6ebb[]; extern char s_Optional_005d4e8b[];
extern char s___C_Synthesized_005d6ef6[];
extern char s__noDerivative_005d5f5d[]; extern char DAT_005be7c0[];
extern char s_sending_005d6e12[]; extern char s_isolated_005d6e1a[];
extern char s_sil_implicit_leading_param_005d6e23[];
extern char s__in_constant_005d5ee4[]; extern char s__deallocating_005d6df0[];
extern char s__guaranteed_005d5f28[]; extern char s__inout_005d5f00[];
extern char s__pack_inout_005d5f51[]; extern char s__in_guaranteed_005d5ef1[];
extern char s__pack_guaranteed_005d5f40[]; extern char s__pack_owned_005d5f34[];
extern char s__owned_005d5f18[]; extern char s__unowned_005d5f1f[];
extern char s__inout_aliasable_005d5f07[];
extern uint64_t DAT_004f2740;
extern uint64_t FUN_003a33cc(uint64_t *node);
extern char s_AutoreleasingUnsafeMutablePointe_005d6a10[]; extern char s_Array_005d6a32[];
extern char DAT_005d6a38[]; extern char s_Dictionary_005d6a3d[]; extern char s_Double_005d6a48[];
extern char s_Float_005d6a4f[]; extern char DAT_005d6a55[]; extern char s_DefaultIndices_005d6a59[];
extern char DAT_005d6a68[]; extern char s_Character_005d6a6c[]; extern char s_ClosedRange_005d6a76[];
extern char s_Range_005d6a82[]; extern char s_ObjectIdentifier_005d6a88[]; extern char s_UnsafePointer_005d6a99[];
extern char s_UnsafeMutablePointer_005d6aa7[]; extern char s_UnsafeBufferPointer_005d6abc[];
extern char s_UnsafeMutableBufferPointer_005d6ad0[]; extern char s_String_005d6aeb[];
extern char s_Substring_005d6af2[]; extern char DAT_005d6afc[]; extern char s_UnsafeRawPointer_005d6b01[];
extern char s_UnsafeMutableRawPointer_005d6b12[]; extern char s_UnsafeRawBufferPointer_005d6b2a[];
extern char s_UnsafeMutableRawBufferPointer_005d6b41[]; extern char s_BinaryFloatingPoint_005d6b5f[];
extern char s_Encodable_005d6b73[]; extern char s_Decodable_005d6b7f[]; extern char s_FloatingPoint_005d6b89[];
extern char s_RandomNumberGenerator_005d6b97[]; extern char s_Hashable_005d6bad[]; extern char s_Numeric_005d6bb6[];
extern char s_BidirectionalCollection_005d6bbe[]; extern char s_RandomAccessCollection_005d6bd6[];
extern char s_Comparable_005d6bed[]; extern char s_Collection_005d6bf8[]; extern char s_MutableCollection_005d6c03[];
extern char s_RangeReplaceableCollection_005d6c17[]; extern char s_Equatable_005d6c32[]; extern char s_Sequence_005d6c3c[];
extern char s_IteratorProtocol_005d6c45[]; extern char s_UnsignedInteger_005d6c56[]; extern char s_RangeExpression_005d6c66[];
extern char s_Strideable_005d6c76[]; extern char s_RawRepresentable_005d6c81[]; extern char s_StringProtocol_005d6c92[];
extern char s_SignedInteger_005d6ca1[]; extern char s_BinaryInteger_005d6caf[]; extern char s_Actor_005d6cbd[];
extern char s_CheckedContinuation_005d6cc3[]; extern char s_UnsafeContinuation_005d6cd9[]; extern char s_CancellationError_005d6cec[];
extern char s_UnownedSerialExecutor_005d6cfe[]; extern char s_Executor_005d6d14[]; extern char s_SerialExecutor_005d6d1d[];
extern char s_TaskGroup_005d6d2c[]; extern char s_ThrowingTaskGroup_005d6d36[]; extern char s_TaskExecutor_005d6d48[];
extern char s_AsyncIteratorProtocol_005d6d55[]; extern char s_AsyncSequence_005d6d6b[]; extern char s_UnownedJob_005d6d79[];
extern char s_TaskPriority_005d6d8e[]; extern char s_AsyncStream_005d6d9b[]; extern char s_AsyncThrowingStream_005d6da7[];
extern char s_UnsafeCurrentTask_005d6dbb[]; extern char DAT_005d4ec0[]; extern char s_MainActor_005d6d84[];
extern char s__thin_005d6ed4[]; extern char s__objc_metatype_005d6ee1[]; extern char s__thick_005d6eda[];
extern char DAT_005d6fc9[]; extern char DAT_005d6fcb[]; extern char DAT_005d6fc3[];
extern char DAT_005d6fd5[]; extern char DAT_005d6fc1[]; extern char DAT_005d6fc7[];
extern char DAT_005d6fcd[]; extern char DAT_005d6fc5[]; extern char DAT_005d6fe3[];
extern char DAT_005d6fdf[]; extern char DAT_005d37e9[]; extern char DAT_005d37dc[];
extern char DAT_005d6fd3[]; extern char DAT_005d356c[]; extern char DAT_005d6b7d[];
extern char DAT_005d6fe9[]; extern char DAT_005d37cb[]; extern char DAT_005d356e[];
extern char DAT_005d6fe7[]; extern char DAT_005d6fef[]; extern char DAT_005d37c9[];
extern char DAT_005c9984[]; extern char DAT_005d6fe1[]; extern char DAT_005d6ff5[];
extern char DAT_005d6ff7[]; extern char DAT_005d356a[]; extern char DAT_005d6ff3[];
extern char DAT_005d3810[]; extern char DAT_005d6fed[]; extern char DAT_005d3801[];
extern char DAT_005d6fd7[]; extern char DAT_005d6feb[]; extern char DAT_005d6ff1[];
extern char DAT_005d37d0[]; extern char DAT_005d3568[]; extern char DAT_005d37d2[];
extern char DAT_005d6fcf[]; extern char DAT_005d37c4[]; extern char DAT_005d6fdb[];
extern char DAT_005d6fe5[]; extern char DAT_005d6fd9[]; extern char DAT_005d37e3[];
extern char DAT_005d6fd1[]; extern char DAT_005d6c15[]; extern char DAT_005d6fdd[];
extern char DAT_005d37eb[]; extern char DAT_005d702c[]; extern char DAT_005d6ff9[];
extern char DAT_005d7008[]; extern char DAT_005d700e[]; extern char DAT_005d7020[];
extern char DAT_005d701d[]; extern char DAT_005d7026[]; extern char DAT_005d7014[];
extern char DAT_005d7023[]; extern char DAT_005d701a[]; extern char DAT_005d700b[];
extern char DAT_005d7002[]; extern char DAT_005d7011[]; extern char DAT_005d702f[];
extern char DAT_005d6fff[]; extern char DAT_005d6ffc[]; extern char DAT_005d7029[];
extern char DAT_005d7005[]; extern char DAT_005d7017[];
extern char DAT_005d7032[]; extern char DAT_005d7037[]; extern char DAT_005d703c[];
extern char DAT_005d3cc6[]; extern char DAT_005d0c46[]; extern char DAT_005cf438[]; extern char DAT_005d7041[]; extern char DAT_005d021c[];
extern char DAT_005d3bb7[]; extern char DAT_005ce788[]; extern char DAT_005d706d[]; extern char DAT_005d3566[]; extern char DAT_005d3cba[]; extern char DAT_005d32c2[]; extern char DAT_005dd27a[]; extern char DAT_005d3a39[];
extern void sk_004ba498(uint64_t p); /* FUN_004ba498 */
extern char s_ImplicitlyUnwrappedOptional_005d7051[];
extern char DAT_005d6ec2[]; extern char DAT_005d6ec5[];
extern uint64_t sk_ctx_setup2_v(uint64_t *a, uint64_t b, uint64_t *c); /* FUN_003a4110 (returns node) */
extern void sk_003bdff4(uint64_t *a, uint64_t *b); /* FUN_003bdff4 */
extern char DAT_005d7072[];
extern char s__autoclosure_005d7077[]; extern char s__escaping_005d7098[]; extern char s__convention_thin__005d7085[];
extern char s__Sendable_005d7103[]; extern char s_async_005d710e[]; extern char DAT_005d7115[]; extern char s_sending_005d711a[];
extern void sk_003ba9e0(uint64_t *a, char *b); /* FUN_003ba9e0 */

extern uint64_t sk_003a6090(uint64_t *st, uint64_t tag); /* FUN_003a6090 */
extern int sk_memcmp(const void *a, const void *b, unsigned long n); /* thunk_FUN_001145b0 */
extern void sk_vec_byte_append(uint64_t *vec, uint8_t byte);        /* FUN_001130a0 */
extern uint64_t sk_vec_grow(uint64_t *vec, uint64_t need);          /* FUN_003b10a8 (returns new base) */
extern uint64_t sk_00363f70(uint64_t *st, uint64_t tag, void *arg); /* FUN_00363f70 */
extern void sk_00362ea4(uint64_t *p); /* FUN_00362ea4 */
extern void *sk_alloc_tagged(unsigned long n, unsigned long tag); /* FUN_000101a0 / 00111890 */
extern uint64_t DAT_004f2960[];                                    /* 0x154 lookup table */
extern void sk_memmove_fast(void *d, const void *s, unsigned long n); /* FUN_00117cc4 */
extern uint64_t sk_ctx_op2_v(uint64_t *a, uint64_t *b); /* FUN_003a4f5c (returns node) */


/* FUN_003b2180 (sk_r53_node_pretty_print) auxiliary externs. */
typedef struct { const char *s; long len; } sk_r53_str2_t;   /* FUN_003bccc4 result */
extern uint32_t FUN_003bc520(uint64_t *, uint64_t *, uint64_t, uint32_t, int, bool,
                             void *, uint64_t, int, const char *, uint32_t); /* dispatch core */
extern void FUN_003bc9a4(uint64_t *, uint64_t, uint64_t *);   /* decode accessor-string */
extern uint64_t *FUN_003bcd78(uint64_t *);                    /* node->resolved type */
extern uint32_t FUN_003bccf8(uint64_t *, uint64_t, uint64_t, uint32_t, const char *, uint32_t);
extern sk_r53_str2_t FUN_003bccc4(uint32_t);                  /* kind->{name,len} */
extern void FUN_003bc15c(uint64_t *, uint64_t *, const char *, uint32_t,
                         uint64_t, const char *, uint64_t);   /* generic-spec print */
extern void FUN_003baaec(uint64_t *, uint64_t *, uint64_t);   /* container print */
extern void FUN_003bcb1c(uint64_t *, uint64_t *);             /* emit unmangled string */
extern uint64_t *FUN_003bc4a4(uint64_t *, uint8_t);           /* emit char-spec */
extern void FUN_003a2e9c(uint64_t *, uint64_t, uint64_t, uint64_t *); /* decode generic str */
extern void FUN_00362de4(uint64_t *);                         /* release temporary buffer */
extern void FUN_0037364c(uint64_t *, uint64_t *);             /* split suffix */
extern uint64_t *FUN_001131f4(uint64_t *, uint64_t, const char *); /* get string buffer */
extern void FUN_004ba408(void) __attribute__((noreturn));     /* fatal trap */
extern void FUN_004ba438(void) __attribute__((noreturn));
extern void FUN_004ba450(void) __attribute__((noreturn));
extern void FUN_004ba480(void) __attribute__((noreturn));
extern void FUN_004ba468(void) __attribute__((noreturn));
extern void FUN_004ba420(void) __attribute__((noreturn));
extern void FUN_004ba44c(void) __attribute__((noreturn));
extern short sk_tb_ncmds;   /* __thread_bss.ncmds: mach-header ncmds field */
extern char s_expansion___005d7479[]; extern char s_too_complex_005d719c[];
extern char s_null_node_pointer_005d71ac[];
extern char s_ERROR_TYPE_005d8839[]; extern char s_invalid_error_flag_005d8e2e[];
extern char s_Builtin_FixedArray_005d7a4f[]; extern char s_opaque_return_type_of_005d8c49[];
extern char s_Swift_bit_005d88a0[]; extern char s_for_005d7123[]; extern char s_for_005d8825[];
extern void FUN_003be1c4(uint64_t *, uint64_t *, uint64_t *, uint64_t *); /* decode into 17-byte str */
extern void FUN_00113368(uint64_t *, uint64_t, uint64_t);   /* convert heap string */
extern uint64_t *sk_str_buf_get(uint64_t *buf, const char *s); /* FUN_00112db4: returns {ptr,len,cap} */
typedef void (*sk_r53_fp18_t)(uint64_t *, uint64_t, uint64_t *, uint64_t, uint8_t);
typedef void (*sk_r53_fp20_t)(uint64_t *, uint64_t *, uint64_t);

extern char DAT_005ce74f[];
extern char DAT_005ce80d[];
extern char DAT_005cef08[];
extern char DAT_005d0ce6[];
extern char DAT_005d3bb9[];
extern char DAT_005d3bdd[];
extern char DAT_005d46f0[];
extern char DAT_005d5321[];
extern char DAT_005d7133[];
extern char DAT_005d7415[];
extern char DAT_005d745b[];
extern char DAT_005d7629[];
extern char DAT_005d762e[];
extern char DAT_005d7689[];
extern char DAT_005d7717[];
extern char DAT_005d78ac[];
extern char DAT_005d7d3d[];
extern char DAT_005d7da0[];
extern char DAT_005d7e24[];
extern char DAT_005d85e5[];
extern char DAT_005d85ea[];
extern char DAT_005d8600[];
extern char DAT_005d8605[];
extern char DAT_005d8609[];
extern char DAT_005d8709[];
extern char DAT_005d8711[];
extern char DAT_005d8882[];
extern char DAT_005d890a[];
extern char DAT_005d8a3a[];
extern char DAT_005d8a3d[];
extern char DAT_005d8c44[];
extern char DAT_005d8c62[];
extern char DAT_005d8fb9[];
extern char DAT_005d90b1[];
extern char s_AnyObject_005d860d[];
extern char s_Builtin_TheTupleType_005d7a3a[];
extern char s_Closure_Propagated_005d79e9[];
extern char s_Constant_Propagated_Float_005d797d[];
extern char s_Constant_Propagated_Function_005d7929[];
extern char s_Constant_Propagated_Global_005d7946[];
extern char s_Constant_Propagated_Integer_005d7961[];
extern char s_Constant_Propagated_KeyPath_005d79b2[];
extern char s_Constant_Propagated_String_005d7997[];
extern char s_Constant_Propagated_Struct_005d79ce[];
extern char s_Copyable_005d888d[];
extern char s_Escapable_005d8896[];
extern char s_Existential_To_Protocol_Constrai_005d7880[];
extern char s_Exploded_005d78d9[];
extern char s_Guaranteed_To_Owned_005d78c5[];
extern char s_InOut_Converted_to_Out_005d7912[];
extern char s_ObjC_metadata_update_function_fo_005d7244[];
extern char s_ObjC_resilient_class_stub_for_005d7267[];
extern char s_Owned_To_Guaranteed_005d78b1[];
extern char s_Pack__005d7657[];
extern char s_Pack__005d766f[];
extern char s_Same_As_Argument_005d79fc[];
extern char s_Signature___005d7779[];
extern char s_Stack_Promoted_from_Box_005d78fa[];
extern char s_Swift_005d6ef0[];
extern char s_Swift__005d8886[];
extern char s_Value_Promoted_from_Box_005d78e2[];
extern char s__NativeClass_005d88e5[];
extern char s__NativeRefCountedObject_005d88cd[];
extern char s__Protocol_005d85f0[];
extern char s__RefCountedObject_005d88bb[];
extern char s__TrivialAtMost_005d88fb[];
extern char s__Trivial_005d88f2[];
extern char s__Type_005d85fa[];
extern char s__UnknownLayout_005d88ac[];
extern char s____level__005d767e[];
extern char s___allocating_init_005d8724[];
extern char s___deallocating_deinit_005d8736[];
extern char s___for_005d7642[];
extern char s___forward__005d87c7[];
extern char s___hasSymbol_query_for_005d8fc9[];
extern char s___isolated_deallocating_deinit_005d874c[];
extern char s___ivar_destroyer_005d877e[];
extern char s___ivar_initializer_005d876b[];
extern char s___linear__005d87bd[];
extern char s___mangledCType____005d8802[];
extern char s___of_005d72c4[];
extern char s___owned_005d76f5[];
extern char s___shared_005d76eb[];
extern char s___unknown_context_at_005d7436[];
extern char s__const_005d76db[];
extern char s__const_005d76e3[];
extern char s__convention__005d87f5[];
extern char s__differentiable_005d87ad[];
extern char s__direct_005d765d[];
extern char s__error_005d8814[];
extern char s__escaping_005d87dc[];
extern char s__extension_in_005d744c[];
extern char s__indirect_005d7665[];
extern char s__isolated_any__005d87e6[];
extern char s__isolated_any__005d89ca[];
extern char s__noDerivative_005d76fe[];
extern char s__nonobjc_005d770d[];
extern char s__objc_completion_handler_block_i_005d8dc7[];
extern char s__removed_005d783b[];
extern char s__reverse__005d87d2[];
extern char s__shape_005d891a[];
extern char s__shape____005d890f[];
extern char s__substituted_005d882b[];
extern char s__yields_005d881c[];
extern char s_accessible_function_runtime_reco_005d7f70[];
extern char s_accessor_function_at_005d8c65[];
extern char s_accessor_macro___005d7468[];
extern char s_and_005d784b[];
extern char s_and_conformance_005d7aaa[];
extern char s_and_results_005d7de8[];
extern char s_anonymous_descriptor_005d8a55[];
extern char s_associated_conformance_descripto_005d82f0[];
extern char s_associated_type_descriptor_for_005d8344[];
extern char s_associated_type_metadata_accesso_005d8364[];
extern char s_associated_type_witness_table_ac_005d83db[];
extern char s_async_demotion_of_005d71c8[];
extern char s_async_function_pointer_to_005d8e89[];
extern char s_autodiff_self_reordering_reabstr_005d7df6[];
extern char s_autodiff_subset_parameters_thunk_005d7e30[];
extern char s_await_resume_partial_function_fo_005d8ea4[];
extern char s_back_deployment_fallback_for_005d801d[];
extern char s_back_deployment_thunk_for_005d8002[];
extern char s_base_conformance_descriptor_for_005d838b[];
extern char s_base_witness_table_accessor_for_005d8407[];
extern char s_body_macro___005d74f1[];
extern char s_borrow_005d8716[];
extern char s_cache_variable_for_noncanonical_s_005d8d2e[];
extern char s_canonical_specialized_generic_ty_005d8c9e[];
extern char s_checked_005d8dbe[];
extern char s_class_metadata_base_offset_for_005d8428[];
extern char s_closure___005d754a[];
extern char s_column_005d7533[];
extern char s_concrete_protocol_conformance_005d8ab2[];
extern char s_conformance_macro___005d74ba[];
extern char s_coro_function_pointer_to_005d8fe0[];
extern char s_coroutine_continuation_prototype_005d8592[];
extern char s_curry_thunk_of_005d71db[];
extern char s_default_argument_005d7617[];
extern char s_default_associated_conformance_a_005d8317[];
extern char s_default_associated_type_metadata_005d83ac[];
extern char s_default_override_of_005d8ffa[];
extern char s_deinit_005c646c[];
extern char s_demangling_cache_variable_for_ty_005d826c[];
extern char s_dependent_associated_conformance_005d8b0d[];
extern char s_dependent_associated_protocol_co_005d8b2f[];
extern char s_dependent_inherited_protocol_con_005d8b5a[];
extern char s_dependent_root_protocol_conforma_005d8b84[];
extern char s_didset_005d86f5[];
extern char s_differentiability_witness_for_005d7ede[];
extern char s_differential_005d7ea0[];
extern char s_direct_005d908f[];
extern char s_dispatch_thunk_of_005d71fe[];
extern char s_dispatching_to_005d7c1e[];
extern char s_distributed_accessor_for_005d7f56[];
extern char s_distributed_thunk_005d7f43[];
extern char s_dynamic_005d7725[];
extern char s_dynamically_replaceable_key_for_005d7f98[];
extern char s_dynamically_replaceable_thunk_fo_005d7fb9[];
extern char s_dynamically_replaceable_variable_005d7fdc[];
extern char s_each_005d712d[];
extern char s_empty_list_005d8a04[];
extern char s_enum_case_for_005d7d63[];
extern char s_equality_005d7d34[];
extern char s_existential_shape_for_005d8ef9[];
extern char s_expansion___005d7479[];
extern char s_extension_descriptor_005d8a6b[];
extern char s_extension_macro___005d74ce[];
extern char s_field_offset_for_005d7d51[];
extern char s_file_005d7525[];
extern char s_first_element_marker_005d8a11[];
extern char s_flag_for_loading_of_canonical_sp_005d8e44[];
extern char s_for_005d7ca3[];
extern char s_forward_mode_005d7eb6[];
extern char s_forward_mode_derivative_005d7e70[];
extern char s_freestanding_macro_expansion___005d74fe[];
extern char s_from_005d7d9a[];
extern char s_from_005d7e29[];
extern char s_full_ObjC_resilient_class_stub_f_005d7286[];
extern char s_full_type_metadata_for_005d817b[];
extern char s_function_signature_specializatio_005d7738[];
extern char s_generic_not_re_abstracted_specia_005d77e8[];
extern char s_generic_not_reabstracted_partial_005d7786[];
extern char s_generic_parameter_reference_for_a_005d8a81[];
extern char s_generic_partial_specialization_005d775a[];
extern char s_generic_pre_specialization_005d77cd[];
extern char s_generic_protocol_witness_table_f_005d7b83[];
extern char s_generic_specialization_005d77b6[];
extern char s_generic_type_metadata_pattern_fo_005d805a[];
extern char s_getter_005d86cd[];
extern char s_helper_005d7d92[];
extern char s_identity_thunk_of_005d71eb[];
extern char s_implicit_closure___005d7554[];
extern char s_in_conformance_005d7c6c[];
extern char s_indirect_005d9096[];
extern char s_infix_005d7a63[];
extern char s_inlined_generic_function_005d7811[];
extern char s_inout_005d76ca[];
extern char s_instantiation_function_for_gener_005d7ba7[];
extern char s_isolated_005d76d1[];
extern char s_key_path_applied_method_005d7d0b[];
extern char s_key_path_getter_for_005d7cc6[];
extern char s_key_path_index_005d7d24[];
extern char s_key_path_setter_for_005d7cdb[];
extern char s_key_path_unapplied_method_005d7cf0[];
extern char s_lazy_cache_variable_for_type_met_005d82c5[];
extern char s_lazy_protocol_witness_table_acce_005d7a7b[];
extern char s_lazy_protocol_witness_table_cach_005d7abc[];
extern char s_line_005d752c[];
extern char s_linear_005d7ed7[];
extern char s_mangled_name_ref_for_type_metada_005d829d[];
extern char s_materializeForSet_005d86db[];
extern char s_memberAttribute_macro___005d7486[];
extern char s_member_macro___005d749e[];
extern char s_merged_005d7efe[];
extern char s_metaclass_for_005d807d[];
extern char s_metadata_instantiation_cache_for_005d8cd8[];
extern char s_method_descriptor_for_005d7211[];
extern char s_method_lookup_function_for_005d7228[];
extern char s_modify_005d8702[];
extern char s_module_005d751d[];
extern char s_module_descriptor_005d8a42[];
extern char s_mutate_005d871d[];
extern char s_nativeOwningAddressor_005d863e[];
extern char s_nativeOwningMutableAddressor_005d8654[];
extern char s_nativePinningAddressor_005d8671[];
extern char s_nativePinningMutableAddressor_005d8688[];
extern char s_nominal_type_descriptor_for_005d8461[];
extern char s_nominal_type_descriptor_runtime_r_005d847e[];
extern char s_non_unique_existential_shape_sym_005d8f3f[];
extern char s_noncanonical_specialized_generic_005d8cfa[];
extern char s_nonisolated_nonsending__005d89da[];
extern char s_nonzero_on_error_005d8e0d[];
extern char s_normal_005d7ed0[];
extern char s_objective_c_protocol_symbolic_re_005d8f72[];
extern char s_of_type_005d7e66[];
extern char s_one_time_initialization_function_005d8d98[];
extern char s_one_time_initialization_token_fo_005d8d75[];
extern char s_opaque_result_conformance_005d8ba9[];
extern char s_opaque_type_descriptor_accessor_f_005d84f1[];
extern char s_opaque_type_descriptor_accessor_i_005d8516[];
extern char s_opaque_type_descriptor_accessor_k_005d8540[];
extern char s_opaque_type_descriptor_accessor_v_005d8569[];
extern char s_opaque_type_descriptor_for_005d84aa[];
extern char s_opaque_type_descriptor_runtime_r_005d84c6[];
extern char s_opaque_type_symbolic_reference_0_005d7f21[];
extern char s_operator_for_005d7d42[];
extern char s_outlined_assign_with_copy_of_005d7370[];
extern char s_outlined_assign_with_take_of_005d7352[];
extern char s_outlined_bridged_method___005d72aa[];
extern char s_outlined_consume_of_005d72dc[];
extern char s_outlined_copy_of_005d72ca[];
extern char s_outlined_destroy_of_005d738e[];
extern char s_outlined_enum_get_tag_of_005d73e7[];
extern char s_outlined_enum_project_data_for_l_005d73a3[];
extern char s_outlined_enum_tag_store_of_005d73cb[];
extern char s_outlined_init_with_copy_of_005d7336[];
extern char s_outlined_init_with_take_of_005d731a[];
extern char s_outlined_read_only_object___005d741a[];
extern char s_outlined_release_of_005d7305[];
extern char s_outlined_retain_of_005d72f1[];
extern char s_outlined_variable___005d7401[];
extern char s_override_005d772e[];
extern char s_owningAddressor_005d8617[];
extern char s_owningMutableAddressor_005d8627[];
extern char s_pack_protocol_conformance_005d8af2[];
extern char s_param_005d7835[];
extern char s_partial_apply_005d7c7d[];
extern char s_partial_apply_ObjC_forwarder_005d7ca9[];
extern char s_partial_apply_forwarder_005d7c8b[];
extern char s_peer_macro___005d74ad[];
extern char s_postfix_005d7a72[];
extern char s_preamble_macro___005d74e0[];
extern char s_prefix_005d7a6a[];
extern char s_property_behavior_storage_of_005d878f[];
extern char s_property_descriptor_for_005d8448[];
extern char s_property_wrapped_field_init_acce_005d75c7[];
extern char s_property_wrapper_backing_initial_005d75a2[];
extern char s_property_wrapper_init_from_proje_005d75ec[];
extern char s_protocol_conformance_descriptor_f_005d80b6[];
extern char s_protocol_conformance_descriptor_r_005d80db[];
extern char s_protocol_conformance_ref__protoc_005d8bee[];
extern char s_protocol_conformance_ref__retroa_005d8c1c[];
extern char s_protocol_conformance_ref__type_s_005d8bc4[];
extern char s_protocol_descriptor_for_005d810f[];
extern char s_protocol_descriptor_runtime_reco_005d8128[];
extern char s_protocol_requirements_base_descr_005d8150[];
extern char s_protocol_self_conformance_descri_005d808c[];
extern char s_protocol_self_conformance_witnes_005d7af1[];
extern char s_protocol_self_conformance_witnes_005d7c2f[];
extern char s_protocol_symbolic_reference_0x_005d803b[];
extern char s_protocol_witness_for_005d7c56[];
extern char s_protocol_witness_table_accessor_f_005d7b1e[];
extern char s_protocol_witness_table_for_005d7b43[];
extern char s_protocol_witness_table_pattern_f_005d7b5f[];
extern char s_pullback_005d7ead[];
extern char s_reabstraction_thunk_005d7d7d[];
extern char s_read2_005d86fc[];
extern char s_reflection_metadata_associated_t_005d896f[];
extern char s_reflection_metadata_builtin_desc_005d8921[];
extern char s_reflection_metadata_field_descri_005d8949[];
extern char s_reflection_metadata_superclass_d_005d899f[];
extern char s_related_decl___005d7633[];
extern char s_repeat_005d7676[];
extern char s_representation_changed_of_005d7167[];
extern char s_resilient_protocol_witness_table_005d7be6[];
extern char s_retroactive___005d76bb[];
extern char s_reverse_mode_005d7ec3[];
extern char s_reverse_mode_derivative_005d7e88[];
extern char s_self_005d7dc4[];
extern char s_serialized_005d782a[];
extern char s_setter_005d86d4[];
extern char s_specialized_generic_metaclass_fo_005d8c7b[];
extern char s_static_005d71c0[];
extern char s_subscript_005d745e[];
extern char s_super_005d771e[];
extern char s_suspend_resume_partial_function_f_005d8ec8[];
extern char s_symbolic_existential_type___005d8f9d[];
extern char s_throws_005d89f3[];
extern char s_throws__005d89fb[];
extern char s_thunk_for_005d7d72[];
extern char s_to_parameters_005d7e56[];
extern char s_type_metadata_accessor_for_005d81a6[];
extern char s_type_metadata_completion_functio_005d8245[];
extern char s_type_metadata_for_005d8193[];
extern char s_type_metadata_instantiation_cach_005d81c2[];
extern char s_type_metadata_instantiation_func_005d81e9[];
extern char s_type_metadata_singleton_initiali_005d8213[];
extern char s_type_symbolic_reference_0x_005d7f06[];
extern char s_uniquable_005d8eee[];
extern char s_unique__0x_005d8fbe[];
extern char s_unique_existential_shape_symboli_005d8f10[];
extern char s_unique_name___005d753c[];
extern char s_unknown_index_005d7649[];
extern char s_unowned_005d90b6[];
extern char s_unowned_unsafe__005d90be[];
extern char s_unsafeAddressor_005d86a6[];
extern char s_unsafeMutableAddressor_005d86b6[];
extern char s_value_witness_for_005d85b8[];
extern char s_value_witness_table_for_005d85cc[];
extern char s_variable_initialization_expressi_005d757f[];
extern char s_variadic_marker_005d8a28[];
extern char s_vtable_thunk_for_005d7c0c[];
extern char s_willset_005d86ed[];
extern char s_with_005d7844[];
extern char s_with_conditional_requirements__005d8ad1[];
extern char s_with_global_actor_constraint_005d7da5[];
extern char s_with_respect_to_parameters_005d7dcb[];
extern char s_with_result_type_005d8dfa[];
extern char s_with_unmangled_suffix_005d7567[];
extern char s_zero_on_error_005d8e1f[];


/* Forward declarations (all 120 slice functions; st = stream ctx). */
static uint64_t sk_003a6c28(uint64_t * st); /* FUN_003a6c28 */
static uint64_t sk_003a75e4(uint64_t * st); /* FUN_003a75e4 */
static uint64_t sk_003a7818(uint64_t * st); /* FUN_003a7818 */
static uint64_t sk_003a7d9c(uint64_t * st); /* FUN_003a7d9c */
static uint64_t sk_003a81e8(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003a81e8 */
static uint64_t * sk_003a8868(uint64_t * st); /* FUN_003a8868 */
static uint64_t * sk_003a8ab4(uint64_t * st); /* FUN_003a8ab4 */
static uint64_t sk_003a9944(uint64_t * st); /* FUN_003a9944 */
static uint64_t sk_003aa804(uint64_t * st); /* FUN_003aa804 */
static void sk_003ab218(uint64_t * st, uint16_t p2, int32_t p3); /* FUN_003ab218 */
static uint64_t sk_003ab40c(uint64_t * st); /* FUN_003ab40c */
static void sk_003ab780(uint64_t * st); /* FUN_003ab780 */
static uint64_t sk_003ab7f4(uint64_t * st); /* FUN_003ab7f4 */
static uint64_t sk_003ab948(uint64_t * st, int32_t p2); /* FUN_003ab948 */
static uint64_t * sk_003abad0(uint64_t * st); /* FUN_003abad0 */
static uint64_t sk_003abc48(uint64_t *st); /* FUN_003abc48 (x0 returns value despite void decl) */
static uint64_t sk_003abd1c(uint64_t * st); /* FUN_003abd1c */
static void sk_003abef0(uint64_t * st); /* FUN_003abef0 */
static uint64_t sk_003abf88(uint64_t * st); /* FUN_003abf88 */
static uint64_t sk_003ac2d0(uint64_t * st, uint32_t p2, uint32_t p3); /* FUN_003ac2d0 */
static void sk_003ac394(uint64_t * st); /* FUN_003ac394 */
static int32_t sk_003ac430(uint64_t * st); /* FUN_003ac430 */
static int32_t sk_003ac4a4(uint64_t * st); /* FUN_003ac4a4 */
static uint64_t * sk_003ac52c(uint64_t * st); /* FUN_003ac52c */
static uint64_t sk_003ac580(uint64_t * st, int32_t p2, uint64_t p3); /* FUN_003ac580 */
static uint64_t sk_003ac600(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003ac600 */
static uint64_t sk_003ac6b4(uint64_t * st, int32_t p2, uint32_t p3); /* FUN_003ac6b4 */
static void sk_003acd3c(uint64_t *buf, uint8_t *p, uint64_t *st); /* FUN_003acd3c */
static bool sk_003acda0(int32_t tag); /* FUN_003acda0 */
static uint64_t sk_003ace08(uint64_t * st); /* FUN_003ace08 */
static uint64_t * sk_003ace50(uint64_t * st); /* FUN_003ace50 */
static uint64_t sk_003acefc(void); /* FUN_003acefc */
static uint64_t sk_003acf38(uint32_t tag); /* FUN_003acf38 */
static uint64_t sk_003acfb4(uint64_t * st, uint64_t p2, uint64_t p3, uint8_t p4); /* FUN_003acfb4 */
static uint64_t * sk_003ad048(uint64_t * st); /* FUN_003ad048 */
static uint64_t sk_003ad0f0(uint64_t * st, uint64_t p2); /* FUN_003ad0f0 */
static uint64_t sk_003ad188(uint64_t * st); /* FUN_003ad188 */
static uint64_t sk_003ad278(uint64_t * st); /* FUN_003ad278 */
static uint64_t sk_003ad3a0(uint64_t * st); /* FUN_003ad3a0 */
static uint64_t sk_003ad478(uint64_t * st); /* FUN_003ad478 */
static void sk_003ad560(uint64_t * st); /* FUN_003ad560 */
static uint64_t * sk_003ad5a4(uint64_t * st); /* FUN_003ad5a4 */
static void sk_003ad61c(uint64_t * st); /* FUN_003ad61c */
static uint64_t sk_003ad67c(uint64_t * st); /* FUN_003ad67c */
static uint64_t sk_003ad724(uint64_t * st, uint64_t p2, uint64_t * p3); /* FUN_003ad724 */
static void sk_003ad810(uint64_t *buf, uint64_t *p, uint64_t *st); /* FUN_003ad810 */
static uint64_t * sk_003ad874(uint64_t * st, uint64_t * p2, uint64_t * p3, uint64_t p4); /* FUN_003ad874 */
static uint64_t sk_003adcd8(uint64_t *node); /* FUN_003adcd8 */
static uint64_t sk_003add54(uint64_t * st, uint64_t p2); /* FUN_003add54 */
static uint64_t sk_003adf20(uint64_t * st, uint64_t p2); /* FUN_003adf20 */
static uint64_t * sk_003adff0(uint64_t * st); /* FUN_003adff0 */
static uint64_t * sk_003ae05c(uint64_t * st); /* FUN_003ae05c */
static uint64_t * sk_003ae0c8(uint64_t * st); /* FUN_003ae0c8 */
static uint64_t * sk_003ae134(uint64_t * st); /* FUN_003ae134 */
static uint64_t sk_003ae1b4(uint64_t * st); /* FUN_003ae1b4 */
static uint64_t sk_003ae36c(uint64_t * st); /* FUN_003ae36c */
static uint64_t sk_003ae414(uint64_t *st, uint64_t p2); /* FUN_003ae414 (x0 returns value) */
static uint64_t sk_003ae4c8(uint64_t * st, uint64_t p2); /* FUN_003ae4c8 */
static uint64_t sk_003ae658(uint64_t * st); /* FUN_003ae658 */
static uint64_t sk_003ae734(uint64_t * st, uint64_t p2, uint64_t * p3); /* FUN_003ae734 */
static uint64_t sk_003ae8a0(uint64_t * st); /* FUN_003ae8a0 */
static uint64_t sk_003ae9e0(uint64_t * st, uint16_t p2); /* FUN_003ae9e0 */
static uint64_t * sk_003aebb0(uint64_t * st); /* FUN_003aebb0 */
static uint64_t sk_003aef74(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003aef74 */
static void sk_003aefe4(uint64_t *buf, uint64_t *p); /* FUN_003aefe4 */
static void sk_003af0cc(uint64_t *buf, uint64_t *st); /* FUN_003af0cc */
static uint64_t sk_003af238(uint64_t * st); /* FUN_003af238 */
static uint64_t sk_003af3c4(uint64_t * st); /* FUN_003af3c4 */
static uint64_t sk_003af4d4(uint64_t * st, uint16_t p2); /* FUN_003af4d4 */
static uint64_t * sk_003af614(uint64_t * st); /* FUN_003af614 */
static uint64_t sk_003af6ac(uint64_t * st); /* FUN_003af6ac */
static uint64_t sk_003af7a4(uint64_t * st); /* FUN_003af7a4 */
static uint64_t sk_003af99c(uint64_t * st, uint16_t p2); /* FUN_003af99c */
static uint64_t sk_003aff04(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003aff04 */
static uint64_t sk_003b0004(uint64_t * st, int32_t p2); /* FUN_003b0004 */
static uint64_t sk_003b0078(uint64_t * st); /* FUN_003b0078 */
static uint64_t * sk_003b0174(uint64_t * st); /* FUN_003b0174 */
static uint64_t sk_003b0220(uint64_t * st); /* FUN_003b0220 */
static uint64_t sk_003b02dc(uint64_t * st); /* FUN_003b02dc */
static uint64_t sk_003b03c0(uint64_t * st, uint64_t p2); /* FUN_003b03c0 */
static void sk_003b05c8(uint64_t * st, uint64_t p2); /* FUN_003b05c8 */
static uint64_t sk_003b06ac(uint64_t * st); /* FUN_003b06ac */
static bool sk_003b0a64(uint32_t tag); /* FUN_003b0a64 */
static bool sk_003b0aa4(int32_t tag); /* FUN_003b0aa4 */
static void sk_003b0b08(void); /* FUN_003b0b08 */
static void sk_003b0b0c(void); /* FUN_003b0b0c */
static void sk_003b0b28(uint64_t *obj); /* FUN_003b0b28 */
static uint64_t * sk_003b0b7c(uint64_t *lock); /* FUN_003b0b7c */
static void sk_003b0be0(uint64_t * st, uint16_t *param_2, void *param_3, uint64_t p4); /* FUN_003b0be0 */
static uint8_t sk_003b0d64(uint64_t *buf); /* FUN_003b0d64 */
static uint64_t sk_003b0e1c(uint64_t * st, uint64_t p2); /* FUN_003b0e1c */
static uint64_t sk_003b0ec4(uint64_t a, uint8_t *b); /* FUN_003b0ec4 */
static uint64_t sk_003b0f48(uint64_t * st, uint64_t p2); /* FUN_003b0f48 */
static uint64_t sk_003b0fb8(uint64_t * st, uint64_t p2); /* FUN_003b0fb8 */
static uint64_t * sk_003b1034(uint64_t *obj, uint64_t p2); /* FUN_003b1034 */
static void sk_003b10a8(uint64_t * st, uint64_t p2); /* FUN_003b10a8 */
static uint64_t sk_003b10f0(uint8_t *p, uint64_t n); /* FUN_003b10f0 */
static uint64_t sk_003b1178(uint64_t p1); /* FUN_003b1178 */
static void sk_003b12cc(uint64_t *a, char *b, uint64_t c); /* FUN_003b12cc */
static void sk_003b1328(uint64_t *a, uint64_t *b, uint64_t c, int32_t d); /* FUN_003b1328 */
static uint64_t sk_003b1e74(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003b1e74 */
static void sk_003b1eec(uint64_t * st, uint64_t p2, uint64_t p3, uint64_t p4); /* FUN_003b1eec */
static uint64_t sk_003b1f20(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003b1f20 */
static uint64_t sk_003b1f98(uint64_t * st, uint64_t p2, uint64_t p3); /* FUN_003b1f98 */
static void sk_003b2010(uint64_t *a, uint64_t b, uint64_t c, uint64_t d); /* FUN_003b2010 */
static void sk_003b20f4(uint64_t * st, uint64_t * p2, uint64_t * p3, int32_t p4, uint64_t p5); /* FUN_003b20f4 */
/* FUN_003b2180 @ 0x003b2180   (est. sk_r53_node_pretty_print)
 * Recursive tagged-value pretty-printer (Tightbeam-style stream serializer).
 * Dispatches on the 16-bit node tag at +0x10 and, for each kind, emits a
 * human-readable description (Swift mangled-name / metadata terminology) into
 * the output stream `out`, recursively printing child nodes at depth+1.
 *
 * Node layout (n = uint64_t*): [0] data ptr, [1] count/value word, [2] 16-bit
 * tag at +0x10, byte at +0x12 = sub-type/flags. Sub-type semantics:
 *   1 = inline single element, 2 = two elements, 3 = three, 5 = array (data
 *   ptr at [0] points to element array, [1] = element count); 4/6 = other.
 *
 * Confidence: medium (structure + tag dispatch faithfully transcribed from
 * the Ghidra decompile; Swift-string handle reconstruction is approximate). */

/* Zero the 17-byte Swift inline-string buffer used by the macro-accessor cases. */
static void sk_r53_macrobuf_init(uint8_t b[17]) { for (int k = 0; k < 17; k++) b[k] = 0; }

static void sk_003b8d18(uint64_t * st, uint64_t * p2, uint64_t p3, uint64_t p4); /* FUN_003b8d18 */
static void sk_003b8e48(uint64_t * st, uint64_t p2); /* FUN_003b8e48 */
static void sk_003b9794(uint64_t * st, uint64_t p2, int32_t p3); /* FUN_003b9794 */
static void sk_003b9cb4(uint64_t * st, uint64_t * p2, uint64_t p3); /* FUN_003b9cb4 */
static uint64_t sk_003ba044(uint64_t * st, uint64_t * p2, uint32_t p3); /* FUN_003ba044 */
static void sk_003ba390(uint64_t *a, uint64_t b, uint64_t *c, uint64_t d); /* FUN_003ba390 */

static void sk_003b2180(uint64_t *out, uint64_t *node, uint64_t depth, uint32_t flag)
{
    uint64_t canary = (uint64_t)-0x2c8502b44bfffed6;
    uint64_t *n = node;
    uint64_t d3 = depth, uVar13, uVar16, uVar26, uVar28, uVar29, uVar30, uVar33;
    uint64_t unaff_x25 = 0;
    uint32_t uVar20, uVar22, uVar23, uVar25, uVar18, iVar19, iVar35;
    uint64_t uVar32 = 0;
    uint8_t bVar17, uVar3, cStack_a9 = 0, cStack_101 = 0, cStack_119 = 0;
    uint16_t uVar5, sVar4;
    uint64_t *puVar21, *puVar11, *puVar31, *puVar24, *puVar2, *pppppppuVar12;
    const char *puVar14ptr;
    const char *pcVar10, *pcVar15;
    uint64_t plVar9 = 0;
    long lVar27;
    bool bVar7 = false, bVar8;
    /* Swift String handles: 16-byte {ptr,len} plus a flag byte. */
    uint64_t local_118[3], local_100[3], local_e0[3], local_f0[3], local_130[3];
    uint64_t local_140, local_138, uStack_d8, uStack_f8, local_d0, uStack_128, local_120, local_108;
    uint64_t local_98, local_90, local_80;
    uint8_t local_c0[17];
#define SUBT(p)   (*(uint8_t *)((char *)(p) + 0x12))
#define TAG(p)    (*(uint16_t *)((char *)(p) + 0x10))
#define P1P8      ((uint64_t *)((char *)out + 8))
#define FLAGOK(p) ((int64_t)(p) >= 0)
#define B64LE(b,o) ((uint64_t)(b)[(o)+0] | ((uint64_t)(b)[(o)+1] << 8) | \
    ((uint64_t)(b)[(o)+2] << 16) | ((uint64_t)(b)[(o)+3] << 24) | \
    ((uint64_t)(b)[(o)+4] << 32) | ((uint64_t)(b)[(o)+5] << 40) | \
    ((uint64_t)(b)[(o)+6] << 48) | ((uint64_t)(b)[(o)+7] << 56))

    uVar20 = (uint32_t)d3;
    if (0x300 < uVar20) {
LAB_003b483c:
        sk_out_str(P1P8, s_too_complex_005d719c, 0xf);
        uVar32 = 0;
        bVar7 = uVar20 < 0x301;
        goto caseD4;
    }
    bVar7 = false;
    plVar9 = (uint64_t)out;
LAB_003b21dc:
    if (n == (uint64_t *)0x0) {
        pcVar10 = s_null_node_pointer_005d71ac;
        out = out + 1;
        uVar13 = 0x13;
        goto LAB_003b486c;
    }
    puVar21 = n + 2;
    uVar5 = TAG(n);
    if (0x179 < uVar5) goto LAB_003b86f8;
    uVar32 = 0;
    iVar19 = (int32_t)d3;
    switch (uVar5) {
    default:
        puVar21 = n;
        if (1 < SUBT(n) - 1) puVar21 = (uint64_t *)*n;
        bVar8 = *(short *)(*puVar21 + 0x10) != 0x19;
        uVar16 = 0x11;
        if (bVar8) uVar16 = 4;
        pcVar15 = s___allocating_init_005d8724;
        if (bVar8) pcVar15 = (const char *)0x5d8711;
        iVar19 = 2;
        goto LAB_003b6b14;
    case 1:
        if ((*(char *)((long)out + 0x21) == '\x01') && (*(char *)((long)out + 0x22) == '\x01')) {
            puVar21 = n;
            if (SUBT(n) == 2) {
LAB_003b6738:
                uVar13 = puVar21[1];
            } else {
                if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                    puVar21 = (uint64_t *)*n;
                    goto LAB_003b6738;
                }
                uVar13 = 0;
            }
            sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
            sk_out_str(P1P8, s___unknown_context_at_005d7436, 0x15);
            puVar21 = n;
            if (SUBT(n) - 1 < 2) {
LAB_003b81f4:
                uVar13 = *puVar21;
            } else {
                if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                    puVar21 = (uint64_t *)*n;
                    goto LAB_003b81f4;
                }
                uVar13 = 0;
            }
            sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
            sk_out_str(P1P8, (const char *)0x5ce788, 1);
            if ((SUBT(n) == 5) && (2 < (uint32_t)n[1])) {
                uVar20 = (uint32_t)SUBT((uint64_t *)(*(uint64_t *)(*n + 0x10)));
                if ((uVar20 - 1 < 2) ||
                    ((uVar20 == 5 && (*(int32_t *)(*(uint64_t *)(*n + 0x10) + 8) != 0)))) {
                    sk_vec_byte_append(P1P8, 0x3c);
                    if ((SUBT(n) == 5) && (2 < (uint32_t)n[1])) {
                        uVar32 = *(uint64_t *)(*n + 0x10);
                    } else {
                        uVar32 = 0;
                    }
                    sk_003b2180(out, (uint64_t *)uVar32, (uint64_t)(iVar19 + 1), 0);
                    uVar32 = 0x3e;
                    goto LAB_003b7f18;
                }
            }
        }
        goto LAB_003b4870;
    case 2:
        if ((1 < SUBT(n) - 1) &&
            ((SUBT(n) != 5 || ((int32_t)n[1] == 0)))) goto LAB_003b4870;
        sk_out_str(P1P8, (const char *)0x5d3bb7, 1);
        uVar13 = 0;
        goto LAB_003b4c60;
    case 3:
        ((sk_r53_fp18_t)*(uint64_t *)((char *)out + 0x18))(out, 0, n, d3, *(uint8_t *)((long)out + 0x2f));
        goto LAB_003b4870;
    case 4:
    case 0x76:
    case 0x130:
    case 0x164:
    case 0x165:
        goto caseD4;
    case 5:
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b69e8:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b69e8;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_vec_byte_append(P1P8, 0x2e);
        if (SUBT(n) == 5) n = (uint64_t *)*n;
        pcVar10 = (const char *)n[1];
        uVar13 = ((uint64_t *)n[1])[1];
        goto LAB_003b68e8;
    case 6:
        pcVar10 = s_associated_type_metadata_accesso_005d8364;
        uVar32 = 0x26;
        goto LAB_003b2670;
    case 7:
        pcVar10 = s_default_associated_type_metadata_005d83ac;
        uVar32 = 0x2e;
        goto LAB_003b2670;
    case 8:
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_r53_macrobuf_init(local_c0);
        local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
        FUN_003bc9a4(local_118, uVar32, (uint64_t *)local_c0);
        pcVar10 = s_accessor_macro___005d7468;
        goto LAB_003b6fec;
    case 9:
        sk_out_str(P1P8, s_associated_type_witness_table_ac_005d83db, 0x2b);
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b2f54:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b2f54;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        sk_out_str(P1P8, (const char *)0x5d3cba, 3);
        if ((SUBT(n) == 5) && (2 < (uint32_t)n[1])) {
            uVar13 = *(uint64_t *)(*n + 0x10);
        } else {
            uVar13 = 0;
        }
        goto LAB_003b3940;
    case 10:
        pcVar10 = s_base_witness_table_accessor_for_005d8407;
        uVar32 = 0x20;
LAB_003b2670:
        sk_out_str(P1P8, pcVar10, uVar32);
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b269c:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b269c;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
LAB_003b3940:
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = (const char *)0x5d7629;
        uVar32 = 4;
LAB_003b3960:
        sk_out_str(P1P8, pcVar10, uVar32);
        if (SUBT(n) - 1 < 2) {
LAB_003b3988:
            n = (uint64_t *)*n;
            goto LAB_003b3da8;
        }
        if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
            n = (uint64_t *)*n;
            goto LAB_003b3988;
        }
        goto LAB_003b40b0;
    case 0xb:
    case 0x17:
    case 0x42:
    case 0x43:
    case 0x54:
    case 0xaf:
    case 0xb0:
    case 0xea:
    case 0x102:
        uVar13 = 0;
LAB_003b48c0:
        sk_003ba390(out, uVar13, n, d3);
        goto LAB_003b4870;
    case 0xc:
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_r53_macrobuf_init(local_c0);
        local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
        FUN_003bc9a4(local_118, uVar32, (uint64_t *)local_c0);
        pcVar10 = s_body_macro___005d74f1;
        goto LAB_003b6fec;
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
        sk_003b9cb4(out, n, d3);
        goto LAB_003b4870;
    case 0x13:
    case 0x4e:
        iVar19 = 2;
        goto LAB_003b7478;
    case 0x14:
    case 0x18:
    case 0x67:
    case 0x6c:
    case 0x74:
    case 0x9b:
        goto caseD14;
    case 0x15:
        pcVar10 = s_Builtin_TheTupleType_005d7a3a;
        goto LAB_003b5c54;
    case 0x16:
        sk_out_str(P1P8, s_Builtin_FixedArray_005d7a4f, 0x13);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b56a8:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b56a8;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        puVar14ptr = (const char *)&DAT_005d0c46;
        uVar32 = 2;
        goto LAB_003b78b0;
    case 0x19:
    case 0x3f:
    case 0xb1:
    case 0xbf:
    case 0xe7:
    case 0xf6:
    case 0x113:
        iVar19 = 0;
        goto LAB_003b7478;
    case 0x1a:
        pcVar10 = s_class_metadata_base_offset_for_005d8428;
        goto LAB_003b2924;
    case 0x1b:
        sk_out_str(P1P8, s_concrete_protocol_conformance_005d8ab2, 0x1e);
        bVar17 = SUBT(n);
        if (bVar17 == 4) {
            sk_out_str(P1P8, (const char *)0x5d7041, 1);
            sk_003b1e74(P1P8, *n, 0);
            sk_out_str(P1P8, (const char *)0x5d021c, 1);
            bVar17 = SUBT(n);
        }
        puVar21 = n;
        if (bVar17 - 1 < 2) {
LAB_003b25a8:
            uVar13 = *puVar21;
        } else {
            if ((bVar17 == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b25a8;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        sk_out_str(P1P8, (const char *)0x5d7da0, 4);
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b3ad8:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b3ad8;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        if ((SUBT(n) == 5) && (2 < (uint32_t)n[1])) {
            uVar23 = (uint32_t)SUBT((uint64_t *)(*(uint64_t *)(*n + 0x10)));
            if ((uVar23 - 1 < 2) ||
                ((uVar23 == 5 && (*(int32_t *)(*(uint64_t *)(*n + 0x10) + 8) != 0)))) {
                pcVar10 = s_with_conditional_requirements__005d8ad1;
                uVar32 = 0x20;
                goto LAB_003b3b44;
            }
        }
        goto LAB_003b4870;
    case 0x1c:
        pcVar10 = s_pack_protocol_conformance_005d8af2;
        uVar32 = 0x1a;
        goto LAB_003b739c;
    case 0x1d:
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_r53_macrobuf_init(local_c0);
        local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
        FUN_003bc9a4(local_118, uVar32, (uint64_t *)local_c0);
        pcVar10 = s_conformance_macro___005d74ba;
        goto LAB_003b6fec;
    case 0x1e:
        bVar8 = (SUBT(n) == 5) ? (2 < (uint32_t)n[1]) : false;
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        iVar35 = -1;
        pcVar15 = (const char *)0x5d8711;
        iVar19 = 2;
        uVar16 = 4;
        goto LAB_003b7480;
    case 0x1f:
        pcVar10 = s_coroutine_continuation_prototype_005d8592;
        goto LAB_003b3004;
    case 0x20:
        puVar21 = n;
        if (1 < SUBT(n) - 1) puVar21 = (uint64_t *)*n;
        bVar8 = *(short *)(*puVar21 + 0x10) == 0x19;
        uVar16 = 0x15;
        if (!bVar8) uVar16 = 6;
        pcVar15 = s___deallocating_deinit_005d8736;
        goto LAB_003b6ae8;
    case 0x21:
    case 0xf4:
        goto caseD21;
    case 0x22:
        puVar21 = n;
        if (SUBT(n) == 5) puVar21 = (uint64_t *)*n;
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        iVar35 = (int32_t)*(uint64_t *)puVar21[1];
        pcVar15 = s_default_argument_005d7617;
        iVar19 = 0;
        bVar8 = false;
        uVar16 = 0x11;
        goto LAB_003b7480;
    case 0x23:
        pcVar10 = s_dependent_associated_conformance_005d8b0d;
        uVar32 = 0x21;
        goto LAB_003b739c;
    case 0x24:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 == 2) {
LAB_003b2ed4:
            sk_003b2180(out, (uint64_t *)puVar21[1], (uint64_t)(iVar19 + 1), 0);
            sk_vec_byte_append(P1P8, 0x2e);
            goto caseD21;
        }
        if (bVar17 != 5) goto LAB_003b3300;
        if (1 < (uint32_t)n[1]) {
            puVar21 = (uint64_t *)*n;
            goto LAB_003b2ed4;
        }
        goto LAB_003b3314;
    case 0x25:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 - 1 < 2) {
LAB_003b3078:
            uVar13 = *puVar21;
LAB_003b3f00:
            if (bVar17 != 2) {
                if ((bVar17 != 5) || ((uint32_t)n[1] < 2)) goto LAB_003b4738;
                n = (uint64_t *)*n;
            }
            puVar21 = (uint64_t *)n[1];
        } else {
            if (bVar17 != 5) {
                uVar13 = 0;
                goto LAB_003b3f00;
            }
            if ((int32_t)n[1] != 0) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b3078;
            }
            uVar13 = 0;
LAB_003b4738:
            puVar21 = (uint64_t *)0x0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = (const char *)0x5d3bb9;
        uVar32 = 2;
        goto LAB_003b4760;
    case 0x26:
    case 0x2b:
    case 0x174:
caseD26:
        FUN_004ba408();
    case 0x50:
    case 0x51:
        FUN_004ba438();
caseD_f3:
        FUN_004ba450();
LAB_003b86f8:
        FUN_004ba480();
LAB_003b86fc:
        FUN_004ba468();
        /* unreachable: UndefinedInstructionException(0x3d48,0x3b8700) */
        sk_canary_panic();
    case 0x27:
        if (SUBT(n) == 5) n = (uint64_t *)*n;
        local_100[0] = (uint64_t)*(uint32_t *)n[1];
        local_e0[0] = (uint64_t)*(uint32_t *)*n;
        FUN_003be1c4((uint64_t *)local_c0, (uint64_t *)((char *)out + 0x48), local_e0, local_100);
        /* reconstruct the 16-byte string FUN_003be1c4 wrote into local_c0 */
        {
            uint64_t sptr = B64LE(local_c0, 0);
            uint64_t slen = B64LE(local_c0, 8);
            int8_t  sflg = (int8_t)local_c0[16];
            sk_out_str(P1P8, (const char *)(sflg < 0 ? sptr : (uint64_t)local_c0), (long)slen);
            if (sflg < 0) {
                local_130[0] = sptr;
                uVar13 = slen;
                goto LAB_003b8198;
            }
        }
        goto LAB_003b4870;
    case 0x28:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 - 1 < 2) {
LAB_003b278c:
            uVar13 = *puVar21;
LAB_003b3d64:
            if (bVar17 != 2) {
                if ((bVar17 != 5) || ((uint32_t)n[1] < 2)) goto LAB_003b43e0;
                n = (uint64_t *)*n;
            }
            puVar21 = (uint64_t *)n[1];
        } else {
            if (bVar17 != 5) {
                uVar13 = 0;
                goto LAB_003b3d64;
            }
            if ((int32_t)n[1] != 0) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b278c;
            }
            uVar13 = 0;
LAB_003b43e0:
            puVar21 = (uint64_t *)0x0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = (const char *)0x5d890a;
        uVar32 = 4;
        goto LAB_003b4760;
    case 0x29:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 - 1 < 2) {
LAB_003b682c:
            uVar13 = *puVar21;
LAB_003b7de0:
            if (bVar17 != 2) {
                if ((bVar17 != 5) || ((uint32_t)n[1] < 2)) goto LAB_003b8200;
                n = (uint64_t *)*n;
            }
            uVar30 = n[1];
        } else {
            if (bVar17 != 5) {
                uVar13 = 0;
                goto LAB_003b7de0;
            }
            if ((int32_t)n[1] != 0) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b682c;
            }
            uVar13 = 0;
LAB_003b8200:
            uVar30 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_out_str(P1P8, s__shape____005d890f, 10);
        sk_003b2180(out, (uint64_t *)uVar30, (uint64_t)(iVar19 + 1), 0);
        pcVar10 = s__shape_005d891a;
        uVar32 = 6;
        goto LAB_003b7924;
    case 0x2a:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 - 1 < 2) {
LAB_003b6a24:
            uVar13 = *puVar21;
LAB_003b7e0c:
            puVar21 = n;
            if (bVar17 != 2) {
                if ((bVar17 != 5) || ((uint32_t)n[1] < 2)) goto LAB_003b8254;
                puVar21 = (uint64_t *)*n;
            }
            puVar31 = (uint64_t *)puVar21[1];
        } else {
            if (bVar17 != 5) {
                uVar13 = 0;
                goto LAB_003b7e0c;
            }
            if ((int32_t)n[1] != 0) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b6a24;
            }
            uVar13 = 0;
LAB_003b8254:
            puVar31 = (uint64_t *)0x0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_out_str(P1P8, (const char *)0x5d3bb9, 2);
        bVar17 = SUBT(puVar31);
        if (bVar17 < 0x52) {
            if (bVar17 == 0x43) { pcVar10 = s_AnyObject_005d860d; uVar32 = 9; }
            else if (bVar17 == 0x44) { pcVar10 = s__NativeClass_005d88e5; uVar32 = 0xc; }
            else if (bVar17 == 0x4e) { pcVar10 = s__NativeRefCountedObject_005d88cd; uVar32 = 0x17; }
            else {
LAB_003b82f8:
                if ((bVar17 & 0xdf) == 0x4d) { pcVar10 = s__TrivialAtMost_005d88fb; goto LAB_003b8528; }
                if ((bVar17 & 0xdf) == 0x45) goto LAB_003b830c;
                uVar32 = 0; pcVar10 = (const char *)0x0;
            }
        } else if (bVar17 == 0x55) {
            pcVar10 = s__UnknownLayout_005d88ac;
LAB_003b8528:
            uVar32 = 0xe;
        } else if (bVar17 == 0x54) {
LAB_003b830c:
            pcVar10 = s__Trivial_005d88f2; uVar32 = 8;
        } else {
            if (bVar17 != 0x52) goto LAB_003b82f8;
            pcVar10 = s__RefCountedObject_005d88bb; uVar32 = 0x11;
        }
        sk_out_str(P1P8, pcVar10, uVar32);
        if ((SUBT(n) != 5) || ((uint32_t)n[1] < 3)) goto LAB_003b4870;
        sk_out_str(P1P8, (const char *)0x5d3bb7, 1);
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_003b2180(out, (uint64_t *)uVar32, (uint64_t)(iVar19 + 1), 0);
        if ((SUBT(n) == 5) && (3 < (uint32_t)n[1])) {
            sk_out_str(P1P8, (const char *)0x5d0c46, 2);
            uVar13 = (SUBT(n) == 5 && (3 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x18) : 0;
            goto LAB_003b6620;
        }
        goto LAB_003b72a0;
    case 0x2c:
    case 0x2f:
        ((sk_r53_fp20_t)*(uint64_t *)((char *)out + 0x20))(out, n, d3);
        goto LAB_003b4870;
    case 0x2d:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 - 1 < 2) {
LAB_003b32cc:
            uVar13 = *puVar21;
LAB_003b3f2c:
            if (bVar17 != 2) {
                if ((bVar17 != 5) || ((uint32_t)n[1] < 2)) goto LAB_003b476c;
                n = (uint64_t *)*n;
            }
            n = (uint64_t *)n[1];
        } else {
            if (bVar17 != 5) {
                uVar13 = 0;
                goto LAB_003b3f2c;
            }
            if ((int32_t)n[1] != 0) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b32cc;
            }
            uVar13 = 0;
LAB_003b476c:
            n = (uint64_t *)0x0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        plVar9 = (uint64_t)FUN_003bcd78(n);
        if ((int32_t)plVar9 != 0) sk_vec_byte_append(P1P8, 0x20);
        goto LAB_003b3da8;
    case 0x2e:
    case 0x13b:
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b2240:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b2240;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        sk_vec_byte_append(P1P8, 0x2e);
        goto LAB_003b3bbc;
    case 0x30:
        pcVar10 = s_dependent_root_protocol_conforma_005d8b84;
        uVar32 = 0x24;
        goto LAB_003b317c;
    case 0x31:
        pcVar10 = s_dependent_inherited_protocol_con_005d8b5a;
        uVar32 = 0x29;
        goto LAB_003b317c;
    case 0x32:
        pcVar10 = s_dependent_associated_protocol_co_005d8b2f;
        uVar32 = 0x2a;
LAB_003b317c:
        sk_out_str(P1P8, pcVar10, uVar32);
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_003b8e48(out, uVar32);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b31d8:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b31d8;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = (const char *)0x5d7da0;
LAB_003b3a4c:
        uVar32 = 4;
        goto LAB_003b3bb8;
    case 0x33:
        sk_out_str(P1P8, s_opaque_result_conformance_005d8ba9, 0x1a);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b242c:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b242c;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = (const char *)0x5d7415;
        goto LAB_003b3a4c;
    case 0x34:
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        iVar35 = -1;
        pcVar15 = s_deinit_005c646c;
        iVar19 = 0;
        bVar8 = false;
        uVar16 = 6;
        goto LAB_003b7480;
    case 0x35:
        if (SUBT(n) - 1 < 2) {
LAB_003b6570:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b6570;
            }
            uVar13 = 0;
        }
        pcVar10 = s_didset_005d86f5;
        goto LAB_003b7a10;
    case 0x36:
        if ((int32_t)*n == 0) { pcVar10 = s_direct_005d908f; uVar32 = 6; }
        else {
            if ((int32_t)*n != 1) goto LAB_003b86fc;
            pcVar10 = s_indirect_005d9096; uVar32 = 8;
        }
        sk_out_str(P1P8, pcVar10, uVar32);
        pcVar10 = (const char *)0x5d021c;
        goto LAB_003b7fb0;
    case 0x37:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) != 0) goto LAB_003b4870;
        pcVar10 = s_distributed_thunk_005d7f43;
LAB_003b4bdc:
        out = out + 1;
        uVar13 = 0x12;
        goto LAB_003b486c;
    case 0x38:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) == 0) {
            pcVar10 = s_distributed_accessor_for_005d7f56;
            goto LAB_003b69b4;
        }
        goto LAB_003b4870;
    case 0x39:
        pcVar10 = s_dynamic_005d7725;
        goto LAB_003b7f44;
    case 0x3a:
        pcVar10 = s_super_005d771e;
        goto LAB_003b68b8;
    case 0x3b:
    case 0x57:
        pcVar10 = (const char *)0x5d85e5;
        goto LAB_003b5ec8;
    case 0x3c:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) != 0) goto LAB_003b4870;
        pcVar10 = s_dynamically_replaceable_thunk_fo_005d7fb9;
        out = out + 1;
        uVar13 = 0x22;
        goto LAB_003b486c;
    case 0x3d:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) != 0) goto LAB_003b4870;
        pcVar10 = s_dynamically_replaceable_key_for_005d7f98;
        out = out + 1;
        uVar13 = 0x20;
        goto LAB_003b486c;
    case 0x3e:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) != 0) goto LAB_003b4870;
        pcVar10 = s_dynamically_replaceable_variable_005d7fdc;
        out = out + 1;
        uVar13 = 0x25;
        goto LAB_003b486c;
    case 0x40:
        pcVar10 = s_enum_case_for_005d7d63;
        goto LAB_003b2c04;
    case 0x41:
        pcVar10 = s_ERROR_TYPE_005d8839;
        goto LAB_003b66ec;
    case 0x44:
        pcVar10 = s__Sendable_005d7103;
        goto LAB_003b4d8c;
    case 0x45:
        if ((SUBT(n) - 1 < 2) ||
            ((SUBT(n) == 5 && ((int32_t)n[1] != 0)))) {
            sk_vec_byte_append(P1P8, 0x40);
            if (SUBT(n) - 1 < 2) {
LAB_003b5b80:
                uVar13 = *n;
            } else {
                if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                    n = (uint64_t *)*n;
                    goto LAB_003b5b80;
                }
                uVar13 = 0;
            }
            sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
            uVar32 = 0x20;
LAB_003b7f18:
            sk_vec_byte_append(P1P8, uVar32);
            goto LAB_003b7928;
        }
        goto LAB_003b4870;
    case 0x46:
        sk_out_str(P1P8, s__differentiable_005d87ad, 0xf);
        bVar17 = (uint8_t)*n;
        if (bVar17 == 0x72) { pcVar10 = s__reverse__005d87d2; uVar13 = 9; goto LAB_003b4940; }
        if (bVar17 == 0x6c) { pcVar10 = s___linear__005d87bd; uVar13 = 9; goto LAB_003b4940; }
        if (bVar17 == 0x66) { pcVar10 = s___forward__005d87c7; uVar13 = 10; goto LAB_003b4940; }
        goto LAB_003b4944;
    case 0x47:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 == 2) {
LAB_003b60a4:
            sk_003b2180(out, (uint64_t *)*puVar21, (uint64_t)(iVar19 + 1), 0);
            uVar13 = 1;
            sk_out_str(P1P8, (const char *)0x5d021c, 1);
            bVar17 = SUBT(n);
LAB_003b7bdc:
            if (bVar17 == 1) { bVar8 = true; uVar30 = 1; goto LAB_003b813c; }
            if (bVar17 == 2) goto LAB_003b814c;
            if (bVar17 == 5) goto LAB_003b8134;
LAB_003b8154:
            uVar13 = 0;
        } else {
            if (bVar17 != 5) {
                uVar13 = 0;
                goto LAB_003b7bdc;
            }
            if ((int32_t)n[1] == 2) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b60a4;
            }
            uVar13 = 0;
LAB_003b8134:
            bVar8 = false;
            uVar30 = (uint64_t)(uint32_t)n[1];
LAB_003b813c:
            if (uVar30 <= uVar13) goto LAB_003b8154;
            if (!bVar8) n = (uint64_t *)*n;
LAB_003b814c:
            uVar13 = n[uVar13];
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        pcVar10 = s__Type_005d85fa;
        uVar32 = 5;
        goto LAB_003b7924;
    case 0x48:
        iVar19 = (uint32_t)*(uint8_t *)((long)out + 0x2f) << 1;
        puVar21 = n;
        if (SUBT(n) == 5) puVar21 = (uint64_t *)*n;
        iVar35 = *(int32_t *)puVar21[1] + 1;
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        pcVar15 = s_closure___005d754a;
        bVar8 = false;
        uVar16 = 9;
        goto LAB_003b7480;
    case 0x49:
        if ((*(char *)((long)out + 0x21) == '\x01') && (*(char *)((long)out + 0x22) == '\x01')) {
            sk_out_str(P1P8, s__extension_in_005d744c, 0xe);
            puVar21 = n;
            if (SUBT(n) - 1 < 2) {
LAB_003b2cb4:
                uVar13 = *puVar21;
            } else {
                if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                    puVar21 = (uint64_t *)*n;
                    goto LAB_003b2cb4;
                }
                uVar13 = 0;
            }
            sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 1);
            sk_out_str(P1P8, (const char *)0x5d745b, 2);
        }
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b47f0:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b47f0;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        if (((SUBT(n) == 5) && ((int32_t)n[1] == 3)) &&
            ((*(uint8_t *)((long)out + 0x33) & 1) == 0)) goto LAB_003b4830;
        goto LAB_003b4870;
    case 0x4a:
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_r53_macrobuf_init(local_c0);
        local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
        FUN_003bc9a4(local_118, uVar32, (uint64_t *)local_c0);
        pcVar10 = s_extension_macro___005d74ce;
        goto LAB_003b6fec;
    case 0x4b:
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b247c:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b247c;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = s_field_offset_for_005d7d51;
        goto LAB_003b3a78;
    case 0x4c:
        iVar35 = **(int32_t **)(*n + 0x10) + 1;
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        pcVar15 = s_freestanding_macro_expansion___005d74fe;
        iVar19 = 0;
        bVar8 = true;
        uVar16 = 0x1e;
        goto LAB_003b7480;
    case 0x4d:
        pcVar10 = s_full_type_metadata_for_005d817b;
        uVar32 = 0x17;
        goto LAB_003b6b14;
    case 0x4f:
        pcVar10 = s_function_signature_specializatio_005d7738;
        uVar32 = 0x21;
        goto LAB_003b6220;
    case 0x52:
        uVar20 = (uint32_t)*n;
        if ((uVar20 >> 10 & 1) != 0) {
            sk_out_str(P1P8, s_Existential_To_Protocol_Constrai_005d7880, 0x2b);
            if ((uVar20 >> 6 & 1) != 0) {
                sk_out_str(P1P8, s_and_005d784b, 5);
                goto LAB_003b7c90;
            }
joined_52:
            if ((uVar20 >> 7 & 1) != 0) {
                sk_out_str(P1P8, s_and_005d784b, 5);
LAB_003b7cbc:
                sk_out_str(P1P8, s_Owned_To_Guaranteed_005d78b1, 0x13);
            }
            if ((uVar20 >> 9 & 1) != 0) {
                sk_out_str(P1P8, s_and_005d784b, 5);
LAB_003b7ce8:
                sk_out_str(P1P8, s_Guaranteed_To_Owned_005d78c5, 0x13);
            }
            if ((uVar20 >> 8 & 1) != 0) {
                sk_out_str(P1P8, s_and_005d784b, 5);
LAB_003b7d14:
                pcVar10 = s_Exploded_005d78d9;
                goto LAB_003b7f44;
            }
            goto LAB_003b4870;
        }
        if ((uVar20 >> 6 & 1) != 0) {
LAB_003b7c90:
            sk_out_str(P1P8, (const char *)0x5d78ac, 4);
            goto joined_52;
        }
        if ((uVar20 >> 7 & 1) != 0) goto LAB_003b7cbc;
        if ((uVar20 >> 9 & 1) != 0) goto LAB_003b7ce8;
        if ((uVar20 >> 8 & 1) != 0) goto LAB_003b7d14;
        uVar32 = 0;
        if (0x3f < (int32_t)uVar20) {
            if ((int32_t)uVar20 < 0x100) {
                if ((uVar20 != 0x40) && (uVar20 != 0x80)) goto caseD4;
            } else if ((uVar20 != 0x100) && ((uVar20 != 0x200 && (uVar20 != 0x400))))
                goto caseD4;
            FUN_004ba420();
            goto caseD26;
        }
        if (0xb < uVar20) goto caseD4;
        switch (*n & 0xffffffff) {
        default:
            pcVar10 = s_Constant_Propagated_Function_005d7929;
            out = out + 1;
            uVar13 = 0x1c;
            goto LAB_003b486c;
        case 1:
            pcVar10 = s_Constant_Propagated_Global_005d7946;
            goto LAB_003b601c;
        case 2:
            pcVar10 = s_Constant_Propagated_Integer_005d7961;
            goto LAB_003b8650;
        case 3:
            pcVar10 = s_Constant_Propagated_Float_005d797d;
            goto LAB_003b69b4;
        case 4:
            pcVar10 = s_Constant_Propagated_String_005d7997;
            goto LAB_003b601c;
        case 5:
            pcVar10 = s_Closure_Propagated_005d79e9;
            goto LAB_003b4bdc;
        case 6:
            pcVar10 = s_Value_Promoted_from_Box_005d78e2;
            goto LAB_003b740c;
        case 7:
            pcVar10 = s_Stack_Promoted_from_Box_005d78fa;
LAB_003b740c:
            out = out + 1;
            uVar13 = 0x17;
            goto LAB_003b486c;
        case 8:
            pcVar10 = s_InOut_Converted_to_Out_005d7912;
            goto LAB_003b61bc;
        case 9:
            pcVar10 = s_Constant_Propagated_KeyPath_005d79b2;
LAB_003b8650:
            out = out + 1;
            uVar13 = 0x1b;
            goto LAB_003b486c;
        case 10:
            pcVar10 = s_Constant_Propagated_Struct_005d79ce;
            goto LAB_003b601c;
        case 0xb:
            pcVar10 = s_Same_As_Argument_005d79fc;
            out = out + 1;
            uVar13 = 0x10;
            goto LAB_003b486c;
        }
        goto LAB_003b601c;
    case 0x53:
        if (SUBT(n) == 4) goto caseD68;
        if (SUBT(n) == 3) {
            sk_r53_macrobuf_init(local_c0);
            local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
            FUN_003a2e9c(local_e0, *n, n[1], (uint64_t *)local_c0);
            FUN_00362de4(&local_98);
            uVar13 = uStack_d8;
            if (FLAGOK(local_d0)) uVar13 = local_d0 >> 0x38;
            if (uVar13 == 0) {
                uVar13 = n[1];
                pppppppuVar12 = (uint64_t *)*n;
            } else {
                pppppppuVar12 = (uint64_t *)local_e0[0];
                if (FLAGOK(local_d0)) pppppppuVar12 = (uint64_t *)&local_e0[0];
            }
            sk_out_str(P1P8, (const char *)pppppppuVar12, (long)uVar13);
            local_130[0] = local_e0[0];
            uVar13 = local_d0;
            if ((int64_t)local_d0 < 0) goto LAB_003b8198;
        }
        goto LAB_003b4870;
    case 0x55:
        sk_out_str(P1P8, (const char *)0x5d8600, 4);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b5d04:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b5d04;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        puVar14ptr = (const char *)&DAT_005d3cc6;
        uVar32 = 1;
LAB_003b78b0:
        sk_out_str(P1P8, (const char *)puVar14ptr, uVar32);
        if (SUBT(n) == 2) {
LAB_003b78d8:
            uVar13 = n[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                n = (uint64_t *)*n;
                goto LAB_003b78d8;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        pcVar10 = (const char *)0x5cf438;
LAB_003b791c:
        uVar32 = 1;
        goto LAB_003b7924;
    case 0x56:
        puVar14ptr = (const char *)&DAT_005d0c46;
        goto LAB_003b73b0;
    case 0x58:
        pcVar10 = s_generic_partial_specialization_005d775a;
        uVar32 = 0x1e;
        goto LAB_003b51f0;
    case 0x59:
        pcVar10 = s_generic_not_reabstracted_partial_005d7786;
        uVar32 = 0x2f;
LAB_003b51f0:
        pcVar15 = s_Signature___005d7779;
        uVar16 = 0xc;
        goto LAB_003b622c;
    case 0x5a:
        pcVar10 = s_generic_protocol_witness_table_f_005d7b83;
        goto LAB_003b32dc;
    case 0x5b:
        pcVar10 = s_instantiation_function_for_gener_005d7ba7;
        uVar32 = 0x3e;
        goto LAB_003b6b14;
    case 0x5c:
        pcVar10 = s_resilient_protocol_witness_table_005d7be6;
        goto LAB_003b3004;
    case 0x5d:
    case 0x5f:
        pcVar10 = s_generic_specialization_005d77b6;
        uVar32 = 0x16;
        goto LAB_003b6220;
    case 0x5e:
        pcVar10 = s_generic_not_re_abstracted_specia_005d77e8;
        uVar32 = 0x28;
        goto LAB_003b6220;
    case 0x60:
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b699c:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b699c;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        bVar17 = SUBT(n);
        uVar20 = (uint32_t)bVar17;
        if ((bVar17 != 2) && ((bVar17 != 5 || (uVar20 = (uint32_t)n[1], uVar20 < 2))))
            goto LAB_003b4870;
        uVar13 = 1;
        goto LAB_003b7a98;
    case 0x61:
        pcVar10 = s_generic_pre_specialization_005d77cd;
        uVar32 = 0x1a;
        goto LAB_003b6220;
    case 0x62:
        pcVar10 = s_inlined_generic_function_005d7811;
        uVar32 = 0x18;
LAB_003b6220:
        pcVar15 = (const char *)0x0;
        uVar16 = 0;
LAB_003b622c:
        FUN_003bc15c(out, n, pcVar10, uVar32, d3, pcVar15, uVar16);
        goto LAB_003b4870;
    case 99:
        pcVar10 = s_generic_type_metadata_pattern_fo_005d805a;
        goto LAB_003b314c;
    case 100:
    case 0x66:
        if (SUBT(n) - 1 < 2) {
LAB_003b4a30:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b4a30;
            }
            uVar13 = 0;
        }
        pcVar10 = s_getter_005d86cd;
        goto LAB_003b7a10;
    case 0x65:
    case 0xf7:
        goto caseD65;
    case 0x68:
    case 0xab:
    case 0xe4:
    case 0x172:
        goto caseD68;
    case 0x69:
        iVar35 = -1;
        pcVar15 = s___ivar_initializer_005d876b;
        iVar19 = 0;
        goto LAB_003b4fc4;
    case 0x6a:
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        iVar35 = -1;
        pcVar15 = s___ivar_destroyer_005d877e;
        iVar19 = 0;
        bVar8 = false;
        uVar16 = 0x10;
        goto LAB_003b7480;
    case 0x6b:
        pcVar10 = s__escaping_005d87dc;
        goto LAB_003b80bc;
    case 0x6d:
        sk_out_str(P1P8, s__differentiable_005d87ad, 0xf);
        bVar17 = (uint8_t)*n;
        if (bVar17 == 0x66) { pcVar10 = s___forward__005d87c7; goto LAB_003b4d8c; }
        if (bVar17 != 0x72) {
            if (bVar17 == 0x6c) { pcVar10 = s___linear__005d87bd; goto LAB_003b80bc; }
            goto LAB_003b4870;
        }
        pcVar10 = s__reverse__005d87d2;
        goto LAB_003b80bc;
    case 0x6e:
        pcVar10 = s__isolated_any__005d87e6;
        goto LAB_003b72dc;
    case 0x6f:
        pcVar10 = s_sending_005d6e12;
        goto LAB_003b68f8;
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
        uVar13 = n[1];
        if (uVar13 == 0) goto LAB_003b4870;
        pcVar10 = (const char *)*n;
LAB_003b4940:
        sk_out_str(P1P8, pcVar10, uVar13);
LAB_003b4944:
        uVar32 = 0x20;
        goto LAB_003b8480;
    case 0x75:
        sk_out_str(P1P8, s__convention__005d87f5, 0xc);
        bVar17 = SUBT(n);
        if (bVar17 == 1) goto LAB_003b7dc8;
        puVar21 = n;
        if (bVar17 != 2) {
            if (bVar17 != 5) goto LAB_003b8478;
            if ((int32_t)n[1] != 2) {
                if ((int32_t)n[1] == 1) goto LAB_003b7dc4;
                goto LAB_003b8478;
            }
            puVar21 = (uint64_t *)*n;
        }
        sk_out_str(P1P8, (const char *)*(uint64_t *)*puVar21, (long)(((uint64_t *)*puVar21)[1]));
        sk_out_str(P1P8, s___mangledCType____005d8802, 0x11);
        if (SUBT(n) == 2) {
LAB_003b8450:
            uVar13 = n[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                n = (uint64_t *)*n;
                goto LAB_003b8450;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_vec_byte_append(P1P8, 0x22);
        goto LAB_003b8478;
    case 0x77:
        FUN_003baaec(out, n, d3);
        goto LAB_003b4870;
    case 0x78:
        if (n[1] != 0) {
            sk_vec_byte_append(P1P8, 0x40);
            goto caseD14;
        }
        goto LAB_003b4870;
    case 0x79:
        sk_out_str(P1P8, s_for_005d8825, 5);
        if (1 < SUBT(n) - 1) {
            if ((SUBT(n) != 5) || ((int32_t)n[1] == 0)) {
LAB_003b754c:
                uVar13 = 0;
                goto LAB_003b7550;
            }
            n = (uint64_t *)*n;
        }
        uVar13 = *n;
        goto LAB_003b7550;
    case 0x7a:
        iVar19 = (uint32_t)*(uint8_t *)((long)out + 0x2f) << 1;
        puVar21 = n;
        if (SUBT(n) == 5) puVar21 = (uint64_t *)*n;
        iVar35 = *(int32_t *)puVar21[1] + 1;
        pcVar15 = s_implicit_closure___005d7554;
LAB_003b4fc4:
        uVar32 = 0;
        pcVar10 = (const char *)0x5be7c0;
        bVar8 = false;
        uVar16 = 0x12;
        goto LAB_003b7480;
    case 0x7b:
    case 0x7d:
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b23e8:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b23e8;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        sk_out_str(P1P8, (const char *)0x5d021c, 1);
        bVar17 = SUBT(n);
        if (bVar17 == 5) {
            iVar19 = (int32_t)n[1];
            if (iVar19 == 3) {
                sk_003b2180(out, (uint64_t *)*(uint64_t *)(*n + 8), d3, 0);
                bVar17 = SUBT(n);
                if (bVar17 != 5) goto LAB_003b3d04;
                iVar19 = (int32_t)n[1];
            }
            if (iVar19 == 4) {
                sk_003b2180(out, (uint64_t *)*(uint64_t *)(*n + 8), d3, 0);
                uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
                sk_003b2180(out, (uint64_t *)uVar32, d3, 0);
                bVar17 = SUBT(n);
                goto LAB_003b3d04;
            }
LAB_003b3d24:
            if ((uint32_t)n[1] == 0) goto LAB_003b40b0;
            lVar27 = (uint64_t)(uint32_t)n[1] - 1;
            n = (uint64_t *)*n;
        } else {
LAB_003b3d04:
            if (bVar17 == 1) lVar27 = 0;
            else {
                if (bVar17 == 5) goto LAB_003b3d24;
                if (bVar17 != 2) goto LAB_003b40b0;
                lVar27 = 1;
            }
        }
        n = (uint64_t *)n[lVar27];
        goto LAB_003b3da8;
    case 0x7c:
        sk_out_str(P1P8, s__substituted_005d882b, 0xd);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b4af4:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b4af4;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_out_str(P1P8, s_for_005d7123, 6);
        if (SUBT(n) != 2) {
            if ((SUBT(n) != 5) || ((uint32_t)n[1] < 2)) goto LAB_003b754c;
            n = (uint64_t *)*n;
        }
        uVar13 = n[1];
LAB_003b7550:
        sk_003b8d18(out, (uint64_t *)uVar13, d3, (uint64_t)&DAT_005d0c46);
        goto LAB_003b7564;
    case 0x7e:
        pcVar10 = s__yields_005d881c;
        uVar32 = 8;
        goto LAB_003b5d84;
    case 0x7f:
        pcVar10 = s__error_005d8814;
        uVar32 = 7;
LAB_003b5d84:
        sk_out_str(P1P8, pcVar10, uVar32);
        puVar14ptr = (const char *)&DAT_005d021c;
        goto LAB_003b73b0;
    case 0x80:
        pcVar10 = s_inout_005d76ca;
        uVar32 = 6;
        goto LAB_003b6b14;
    case 0x81:
        sk_out_str(P1P8, (const char *)*n, (long)n[1]);
        pcVar10 = s_infix_005d7a63;
        goto LAB_003b68b8;
    case 0x82:
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        iVar35 = -1;
        pcVar15 = s_variable_initialization_expressi_005d757f;
        iVar19 = 0;
        bVar8 = false;
        uVar16 = 0x22;
        goto LAB_003b7480;
    case 0x83:
        if (SUBT(n) - 1 < 2) {
LAB_003b4b64:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b4b64;
            }
            uVar13 = 0;
        }
        pcVar10 = (const char *)0x5d8711;
        goto LAB_003b79f0;
    case 0x84:
        pcVar10 = s_isolated_005d76d1;
        goto LAB_003b2fd0;
    case 0x85:
        puVar21 = n;
        if (1 < SUBT(n) - 1) puVar21 = (uint64_t *)*n;
        bVar8 = *(short *)(*puVar21 + 0x10) == 0x19;
        uVar16 = 0x1e;
        if (!bVar8) uVar16 = 6;
        pcVar15 = s___isolated_deallocating_deinit_005d874c;
LAB_003b6ae8:
        if (!bVar8) pcVar15 = s_deinit_005c646c;
        iVar19 = 0;
LAB_003b6b14:
        uVar32 = 0;
        pcVar10 = (const char *)0x5be7c0;
        iVar35 = -1;
        bVar8 = false;
        goto LAB_003b7480;
    case 0x86:
        pcVar10 = s_sending_005d711a;
        goto LAB_003b3298;
    case 0x87:
        pcVar10 = s__isolated_any__005d89ca;
        out = out + 1;
        uVar13 = 0xf;
        goto LAB_003b486c;
    case 0x88:
        pcVar10 = s_nonisolated_nonsending__005d89da;
        out = out + 1;
        uVar13 = 0x18;
        goto LAB_003b486c;
    case 0x89:
        pcVar10 = s_sending_005d711a;
        goto LAB_003b7f44;
    case 0x8a:
    case 0x8b:
    case 0x8c:
    case 0x8d:
        if (uVar5 == 0x8c) { pcVar10 = s_key_path_unapplied_method_005d7cf0; uVar32 = 0x1a; }
        else {
            if (uVar5 == 0x8b) { pcVar10 = s_key_path_setter_for_005d7cdb; }
            else {
                if (uVar5 != 0x8a) { pcVar10 = s_key_path_applied_method_005d7d0b; uVar32 = 0x18; goto LAB_003b5718; }
                pcVar10 = s_key_path_getter_for_005d7cc6;
            }
            uVar32 = 0x14;
        }
LAB_003b5718:
        sk_out_str(P1P8, pcVar10, uVar32);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b5744:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b5744;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_out_str(P1P8, (const char *)0x5d3cba, 3);
        uVar13 = 1;
        goto LAB_003b5780;
    case 0x8e:
    case 0x8f:
        sk_out_str(P1P8, s_key_path_index_005d7d24, 0xf);
        bVar8 = (short)n[2] != 0x8e;
        pcVar10 = s_equality_005d7d34;
        if (bVar8) pcVar10 = (const char *)0x5d7d3d;
        uVar32 = 8;
        if (bVar8) uVar32 = 4;
        sk_out_str(P1P8, pcVar10, uVar32);
        sk_out_str(P1P8, s_operator_for_005d7d42, 0xe);
        uVar20 = (uint32_t)SUBT(n);
        uVar23 = (uint32_t)SUBT(n);
        puVar21 = n;
        if (uVar23 == 1) { uVar30 = 0; uVar13 = 0xffffffff; }
        else if (uVar23 == 5) {
            uVar20 = (uint32_t)n[1];
            uVar30 = (uint64_t)(uVar20 - 1);
            uVar13 = (uint64_t)(uVar20 - 2);
            puVar21 = (uint64_t *)*n;
        } else { uVar13 = 0; uVar20 = 2; uVar30 = 1; }
        uVar30 = puVar21[uVar30];
        sVar4 = *(short *)(uVar30 + 0x10);
        if (sVar4 == 0xe5) {
            uVar20 = uVar20 - 1;
            puVar21 = n;
            if (1 < uVar23 - 1) puVar21 = (uint64_t *)*n;
            uVar30 = puVar21[uVar13];
            sVar4 = *(short *)(uVar30 + 0x10);
        }
        if (sVar4 == 0x2c) {
            sk_003b2180(out, (uint64_t *)uVar30, (uint64_t)(iVar19 + 1), 0);
            uVar20 = uVar20 - 1;
        }
        sk_out_str(P1P8, (const char *)0x5d3bb7, 1);
        if (uVar20 == 0) goto LAB_003b72a0;
        uVar13 = 0;
        goto LAB_003b7224;
    case 0x90:
        pcVar10 = s_lazy_protocol_witness_table_acce_005d7a7b;
        uVar32 = 0x2e;
        goto LAB_003b2e78;
    case 0x91:
        pcVar10 = s_lazy_protocol_witness_table_cach_005d7abc;
        uVar32 = 0x34;
LAB_003b2e78:
        sk_out_str(P1P8, pcVar10, uVar32);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b2ea4:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b2ea4;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = s_and_conformance_005d7aaa;
LAB_003b3a78:
        uVar32 = 0x11;
        goto LAB_003b3bb8;
    case 0x92:
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b56d8:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b56d8;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        if (*(char *)((long)out + 0x29) == '\x01') {
            sk_out_str(P1P8, (const char *)0x5d3bdd, 2);
            if (1 < SUBT(n) - 1) n = (uint64_t *)*n;
            uVar13 = *(long *)*n + 1;
            goto LAB_003b6148;
        }
        goto LAB_003b4870;
    case 0x93:
        if (SUBT(n) == 5) {
            iVar19 = 1;
            if ((int32_t)n[1] != 3) iVar19 = 2;
        } else iVar19 = 2;
        goto LAB_003b7478;
    case 0x94:
        bVar17 = SUBT(n);
        if (bVar17 - 1 < 2) {
LAB_003b324c:
            sk_out_str(P1P8, s_module_005d751d, 7);
            puVar21 = n;
            if (SUBT(n) - 1 < 2) {
LAB_003b3288:
                uVar13 = *puVar21;
            } else {
                if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                    puVar21 = (uint64_t *)*n;
                    goto LAB_003b3288;
                }
                uVar13 = 0;
            }
            sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
            bVar17 = SUBT(n);
LAB_003b3f84:
            if (bVar17 == 2) goto LAB_003b3fa0;
            if (bVar17 == 5) goto LAB_003b3f94;
LAB_003b3ffc:
            if (bVar17 != 5) goto LAB_003b4870;
        } else {
            if (bVar17 != 5) goto LAB_003b3f84;
            if ((int32_t)n[1] != 0) goto LAB_003b324c;
LAB_003b3f94:
            if (1 < (uint32_t)n[1]) {
LAB_003b3fa0:
                sk_out_str(P1P8, s_file_005d7525, 6);
                puVar21 = n;
                if (SUBT(n) == 2) {
LAB_003b3fdc:
                    uVar13 = puVar21[1];
                } else {
                    if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                        puVar21 = (uint64_t *)*n;
                        goto LAB_003b3fdc;
                    }
                    uVar13 = 0;
                }
                sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
                bVar17 = SUBT(n);
                goto LAB_003b3ffc;
            }
        }
        if (2 < (uint32_t)n[1]) {
            sk_out_str(P1P8, s_line_005d752c, 6);
            uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
            d3 = (uint64_t)(iVar19 + 1);
            sk_003b2180(out, (uint64_t *)uVar32, d3, 0);
            if ((SUBT(n) == 5) && (3 < (uint32_t)n[1])) {
                sk_out_str(P1P8, s_column_005d7533, 8);
                if ((SUBT(n) == 5) && (3 < (uint32_t)n[1])) {
                    n = (uint64_t *)*(uint64_t *)(*n + 0x18);
                    goto LAB_003b3da8;
                }
                goto LAB_003b40b0;
            }
        }
        goto LAB_003b4870;
    case 0x95:
        iVar35 = **(int32_t **)(*n + 0x10) + 1;
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        pcVar15 = s_unique_name___005d753c;
        iVar19 = 0;
        bVar8 = true;
        uVar16 = 0xd;
        goto LAB_003b7480;
    case 0x96:
        if (SUBT(n) - 1 < 2) {
LAB_003b5220:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b5220;
            }
            uVar13 = 0;
        }
        pcVar10 = s_materializeForSet_005d86db;
        uVar32 = 0x11;
        goto LAB_003b7a20;
    case 0x97:
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_r53_macrobuf_init(local_c0);
        local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
        FUN_003bc9a4(local_118, uVar32, (uint64_t *)local_c0);
        pcVar10 = s_member_macro___005d749e;
        goto LAB_003b6fec;
    case 0x98:
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_r53_macrobuf_init(local_c0);
        local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
        FUN_003bc9a4(local_118, uVar32, (uint64_t *)local_c0);
        pcVar10 = s_memberAttribute_macro___005d7486;
        goto LAB_003b6fec;
    case 0x99:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) == 0) {
            pcVar10 = s_merged_005d7efe;
            goto LAB_003b68f8;
        }
        goto LAB_003b4870;
    case 0x9a:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 == 2) {
LAB_003b4ef0:
            sk_003b2180(out, (uint64_t *)*puVar21, (uint64_t)(iVar19 + 1), 0);
            uVar13 = 1;
            sk_out_str(P1P8, (const char *)0x5d021c, 1);
            bVar17 = SUBT(n);
LAB_003b7b64:
            if (bVar17 == 1) { bVar8 = true; uVar30 = 1; goto LAB_003b8040; }
            if (bVar17 == 2) goto LAB_003b8050;
            if (bVar17 == 5) goto LAB_003b8038;
LAB_003b8058:
            plVar9 = 0;
        } else {
            if (bVar17 != 5) {
                uVar13 = 0;
                goto LAB_003b7b64;
            }
            if ((int32_t)n[1] == 2) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b4ef0;
            }
            uVar13 = 0;
LAB_003b8038:
            bVar8 = false;
            uVar30 = (uint64_t)(uint32_t)n[1];
LAB_003b8040:
            if (uVar30 <= uVar13) goto LAB_003b8058;
            if (!bVar8) n = (uint64_t *)*n;
LAB_003b8050:
            plVar9 = n[uVar13];
        }
        if (SUBT((uint64_t *)plVar9) - 1 < 2) {
LAB_003b8080:
            lVar27 = *(uint64_t *)plVar9;
        } else {
            if ((SUBT((uint64_t *)plVar9) == 5) && ((int32_t)((uint64_t *)plVar9)[1] != 0)) {
                plVar9 = (uint64_t)*(uint64_t *)plVar9;
                goto LAB_003b8080;
            }
            lVar27 = 0;
        }
        sk_003b9794(out, lVar27, d3);
        if ((2 < (uint16_t)(TAG((uint64_t *)lVar27) - 0xc9)) && (TAG((uint64_t *)lVar27) != 0x47)) {
            pcVar10 = s__Type_005d85fa;
            goto LAB_003b50e0;
        }
        pcVar10 = s__Protocol_005d85f0;
        goto LAB_003b80bc;
    case 0x9c:
        pcVar10 = s_metaclass_for_005d807d;
        goto LAB_003b2c04;
    case 0x9d:
        pcVar10 = s_method_lookup_function_for_005d7228;
        goto LAB_003b32f0;
    case 0x9e:
        pcVar10 = s_ObjC_metadata_update_function_fo_005d7244;
        goto LAB_003b314c;
    case 0x9f:
        pcVar10 = s_ObjC_resilient_class_stub_for_005d7267;
        uVar32 = 0x1e;
        goto LAB_003b6b14;
    case 0xa0:
        pcVar10 = s_full_ObjC_resilient_class_stub_f_005d7286;
        goto LAB_003b32dc;
    case 0xa1:
        if (SUBT(n) - 1 < 2) {
LAB_003b6858:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b6858;
            }
            uVar13 = 0;
        }
        pcVar10 = s_modify_005d8702;
        goto LAB_003b7a10;
    case 0xa2:
        if (SUBT(n) - 1 < 2) {
LAB_003b67ac:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b67ac;
            }
            uVar13 = 0;
        }
        pcVar10 = (const char *)0x5d8709;
        goto LAB_003b79d0;
    case 0xa3:
        if (*(char *)((long)out + 0x24) == '\x01') goto caseD14;
        goto LAB_003b4870;
    case 0xa4:
        if (SUBT(n) - 1 < 2) {
LAB_003b5368:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b5368;
            }
            uVar13 = 0;
        }
        pcVar10 = s_nativeOwningAddressor_005d863e;
        uVar32 = 0x15;
        goto LAB_003b7a20;
    case 0xa5:
        if (SUBT(n) - 1 < 2) {
LAB_003b64f0:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b64f0;
            }
            uVar13 = 0;
        }
        pcVar10 = s_nativeOwningMutableAddressor_005d8654;
        uVar32 = 0x1c;
        goto LAB_003b7a20;
    case 0xa6:
        if (SUBT(n) - 1 < 2) {
LAB_003b4d7c:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b4d7c;
            }
            uVar13 = 0;
        }
        pcVar10 = s_nativePinningAddressor_005d8671;
        goto LAB_003b7668;
    case 0xa7:
        if (SUBT(n) - 1 < 2) {
LAB_003b6658:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b6658;
            }
            uVar13 = 0;
        }
        pcVar10 = s_nativePinningMutableAddressor_005d8688;
        uVar32 = 0x1d;
        goto LAB_003b7a20;
    case 0xa8:
        pcVar10 = s_nominal_type_descriptor_for_005d8461;
        uVar32 = 0x1c;
        goto LAB_003b6b14;
    case 0xa9:
        pcVar10 = s_nominal_type_descriptor_runtime_r_005d847e;
        uVar32 = 0x2b;
        goto LAB_003b6b14;
    case 0xaa:
        pcVar10 = s__nonobjc_005d770d;
        goto LAB_003b80bc;
    case 0xac:
        goto caseD_ac;
    case 0xad:
        sk_out_str(P1P8, s_checked_005d8dbe, 8);
caseD_ac:
        sk_out_str(P1P8, s__objc_completion_handler_block_i_005d8dc7, 0x32);
        bVar17 = SUBT(n);
        if (bVar17 == 5) {
            if (3 < (uint32_t)n[1]) {
                sk_003b2180(out, (uint64_t *)*(uint64_t *)(*n + 0x18), (uint64_t)(iVar19 + 1), 0);
                bVar17 = SUBT(n);
                goto LAB_003b52d0;
            }
LAB_003b52e8:
            if ((int32_t)n[1] != 0) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b52f4;
            }
LAB_003b70e8:
            uVar13 = 0;
        } else {
LAB_003b52d0:
            puVar21 = n;
            if (1 < bVar17 - 1) {
                if (bVar17 == 5) goto LAB_003b52e8;
                goto LAB_003b70e8;
            }
LAB_003b52f4:
            uVar13 = *puVar21;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_out_str(P1P8, s_with_result_type_005d8dfa, 0x12);
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b7138:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b7138;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        lVar27 = **(long **)(*n + 0x10);
        if (lVar27 == 0) goto LAB_003b4870;
        if (lVar27 == 2) {
            pcVar10 = s_zero_on_error_005d8e1f;
LAB_003b72dc:
            out = out + 1;
            uVar13 = 0xe;
        } else if (lVar27 == 1) {
            pcVar10 = s_nonzero_on_error_005d8e0d;
LAB_003b717c:
            out = out + 1;
            uVar13 = 0x11;
        } else {
            pcVar10 = s_invalid_error_flag_005d8e2e;
            out = out + 1;
            uVar13 = 0x15;
        }
        goto LAB_003b486c;
    case 0xae:
        pcVar10 = (const char *)0x5d7717;
        goto LAB_003b68b8;
    case 0xb2:
        if (SUBT(n) - 1 < 2) {
LAB_003b63c4:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b63c4;
            }
            uVar13 = 0;
        }
        pcVar10 = s_owningAddressor_005d8617;
        goto LAB_003b7960;
    case 0xb3:
        if (SUBT(n) - 1 < 2) {
LAB_003b4c18:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b4c18;
            }
            uVar13 = 0;
        }
        pcVar10 = s_owningMutableAddressor_005d8627;
        goto LAB_003b7668;
    case 0xb4:
        if (*(char *)((long)out + 0x2a) == '\x01') {
LAB_003b597c:
            pcVar10 = s_partial_apply_005d7c7d;
            uVar32 = 0xd;
        } else {
            pcVar10 = s_partial_apply_forwarder_005d7c8b;
            uVar32 = 0x17;
        }
        goto LAB_003b7368;
    case 0xb5:
        if (*(char *)((long)out + 0x2a) == '\x01') goto LAB_003b597c;
        pcVar10 = s_partial_apply_ObjC_forwarder_005d7ca9;
        uVar32 = 0x1c;
LAB_003b7368:
        sk_out_str(P1P8, pcVar10, uVar32);
        if ((SUBT(n) - 1 < 2) ||
            ((SUBT(n) == 5 && ((int32_t)n[1] != 0)))) {
            pcVar10 = s_for_005d7ca3;
            uVar32 = 5;
            goto LAB_003b739c;
        }
        goto LAB_003b4870;
    case 0xb6:
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_r53_macrobuf_init(local_c0);
        local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
        FUN_003bc9a4(local_118, uVar32, (uint64_t *)local_c0);
        pcVar10 = s_peer_macro___005d74ad;
        goto LAB_003b6fec;
    case 0xb7:
        sk_out_str(P1P8, (const char *)*n, (long)n[1]);
        pcVar10 = s_postfix_005d7a72;
        goto LAB_003b7f44;
    case 0xb8:
        uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
        sk_r53_macrobuf_init(local_c0);
        local_98 = 0x67a2b8; local_90 = (uint64_t)sk_003b2010; local_80 = (uint64_t)&local_98;
        FUN_003bc9a4(local_118, uVar32, (uint64_t *)local_c0);
        pcVar10 = s_preamble_macro___005d74e0;
LAB_003b6fec:
        puVar21 = FUN_001131f4(local_118, 0, pcVar10);
        local_f0[2] = puVar21[2];
        local_f0[1] = puVar21[1];
        local_f0[0] = *puVar21;
        puVar21[1] = 0; puVar21[2] = 0; *puVar21 = 0;
        plVar9 = (uint64_t)sk_str_buf_get(&local_100[0], s_expansion___005d7479);
        uVar13 = ((uint64_t *)plVar9)[2];
        uStack_d8 = ((uint64_t *)plVar9)[1];
        local_e0[0] = *(uint64_t *)plVar9;
        ((uint64_t *)plVar9)[1] = 0; ((uint64_t *)plVar9)[2] = 0; *(uint64_t *)plVar9 = 0;
        local_d0 = uVar13 >> 0x38;
        pppppppuVar12 = (uint64_t *)local_e0[0];
        if (FLAGOK(local_d0)) pppppppuVar12 = (uint64_t *)&local_e0[0];
        uVar30 = uStack_d8;
        if (FLAGOK(uVar13)) uVar30 = local_d0 >> 0x38;
        local_d0 = uVar13;
        uVar32 = FUN_003bc520(out, n, d3, flag & 1, 0, 1, pppppppuVar12, uVar30,
                              **(int32_t **)(*n + 0x18) + 1, (const char *)0x5be7c0, 0);
        if ((int64_t)local_d0 < 0) sk_lock((void *)local_e0[0], local_d0 & 0x7fffffffffffffff);
        if ((int64_t)local_f0[2] < 0) sk_lock((void *)local_f0[0], local_f0[2] & 0x7fffffffffffffff);
        if (cStack_101 < 0) sk_lock((void *)local_118[0], local_118[1] & 0x7fffffffffffffff);
        FUN_00362de4(&local_98);
        goto caseD4;
    case 0xb9:
        sk_out_str(P1P8, (const char *)*n, (long)n[1]);
        pcVar10 = s_prefix_005d7a6a;
        goto LAB_003b68f8;
    case 0xba:
        bVar17 = SUBT(n);
        if ((bVar17 == 2) || ((bVar17 == 5 && (1 < (uint32_t)n[1])))) {
            if (*(char *)((long)out + 0x2e) == '\x01') {
                sk_vec_byte_append(P1P8, 0x28);
                bVar17 = SUBT(n);
            }
            puVar21 = n;
            if (bVar17 == 2) {
LAB_003b66dc:
                uVar13 = puVar21[1];
            } else {
                if ((bVar17 == 5) && (1 < (uint32_t)n[1])) {
                    puVar21 = (uint64_t *)*n;
                    goto LAB_003b66dc;
                }
                uVar13 = 0;
            }
            sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
            if (*(char *)((long)out + 0x2e) != '\x01') goto LAB_003b4870;
            puVar14ptr = (const char *)0x5d7629;
        } else {
            if (*(char *)((long)out + 0x2e) != '\x01') goto LAB_003b4870;
            puVar14ptr = (const char *)0x5d762e;
        }
        sk_out_str(P1P8, (const char *)puVar14ptr, 4);
        if (1 < SUBT(n) - 1) {
LAB_003b7dc4:
            n = (uint64_t *)*n;
        }
LAB_003b7dc8:
        sk_out_str(P1P8, (const char *)*(uint64_t *)*n, (long)(((uint64_t *)*n)[1]));
        goto LAB_003b8478;
    case 0xbb:
        pcVar10 = s_property_descriptor_for_005d8448;
        goto LAB_003b312c;
    case 0xbc:
        pcVar15 = s_property_wrapper_backing_initial_005d75a2;
        goto LAB_003b4e7c;
    case 0xbd:
        pcVar15 = s_property_wrapped_field_init_acce_005d75c7;
LAB_003b4e7c:
        uVar32 = 0;
        pcVar10 = (const char *)0x5be7c0;
        iVar35 = -1;
        iVar19 = 0;
        bVar8 = false;
        uVar16 = 0x24;
        goto LAB_003b7480;
    case 0xbe:
        pcVar10 = (const char *)0x5be7c0;
        uVar32 = 0;
        iVar35 = -1;
        pcVar15 = s_property_wrapper_init_from_proje_005d75ec;
        iVar19 = 0;
        bVar8 = false;
        uVar16 = 0x2a;
        goto LAB_003b7480;
    case 0xc0:
        pcVar10 = s_protocol_symbolic_reference_0x_005d803b;
        uVar32 = 0x1e;
        goto LAB_003b6914;
    case 0xc1:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 - 1 < 2) {
LAB_003b2df0:
            uVar13 = *puVar21;
LAB_003b3e3c:
            puVar21 = (uint64_t *)0x0;
            if (bVar17 == 1) { n = (uint64_t *)0x0; goto LAB_003b46cc; }
            puVar11 = n;
            if (bVar17 == 2) {
LAB_003b3e6c:
                puVar21 = (uint64_t *)puVar11[1];
            } else if (bVar17 == 5) {
                if ((uint32_t)n[1] < 2) { puVar21 = (uint64_t *)0x0; goto LAB_003b46c8; }
                puVar11 = (uint64_t *)*n;
                goto LAB_003b3e6c;
            }
            if ((bVar17 != 5) || (puVar11 = n + 1, (uint32_t)*puVar11 < 3)) goto LAB_003b46c8;
            n = (uint64_t *)*(uint64_t *)(*n + 0x10);
            if ((uint32_t)*puVar11 != 4) goto LAB_003b46cc;
            sk_out_str(P1P8, s_property_behavior_storage_of_005d878f, 0x1d);
            d3 = (uint64_t)(iVar19 + 1);
            sk_003b2180(out, n, d3, 0);
            sk_out_str(P1P8, (const char *)0x5d7629, 4);
            sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
            pcVar10 = (const char *)0x5d3cba;
            uVar32 = 3;
            goto LAB_003b4760;
        }
        if (bVar17 != 5) {
            uVar13 = 0;
            goto LAB_003b3e3c;
        }
        if ((int32_t)n[1] != 0) {
            puVar21 = (uint64_t *)*n;
            goto LAB_003b2df0;
        }
        puVar21 = (uint64_t *)0x0;
        uVar13 = 0;
LAB_003b46c8:
        n = (uint64_t *)0x0;
LAB_003b46cc:
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        if (*(char *)((long)out + 0x26) == '\x01') {
            sk_out_str(P1P8, (const char *)0x5d3cba, 3);
            sk_003b2180(out, puVar21, d3, 0);
            sk_out_str(P1P8, (const char *)0x5d7629, 4);
            goto LAB_003b3da8;
        }
        goto LAB_003b4870;
    case 0xc2:
        pcVar10 = s_protocol_conformance_ref__type_s_005d8bc4;
        uVar32 = 0x29;
        goto LAB_003b739c;
    case 0xc3:
        pcVar10 = s_protocol_conformance_ref__protoc_005d8bee;
        uVar32 = 0x2d;
        goto LAB_003b739c;
    case 0xc4:
        pcVar10 = s_protocol_conformance_ref__retroa_005d8c1c;
        uVar32 = 0x27;
        goto LAB_003b739c;
    case 0xc5:
        pcVar10 = s_protocol_descriptor_for_005d810f;
        goto LAB_003b312c;
    case 0xc6:
        pcVar10 = s_protocol_descriptor_runtime_reco_005d8128;
        goto LAB_003b320c;
    case 199:
        pcVar10 = s_protocol_conformance_descriptor_f_005d80b6;
        goto LAB_003b3220;
    case 200:
        pcVar10 = s_protocol_conformance_descriptor_r_005d80db;
        goto LAB_003b2938;
    case 0xc9:
        if (1 < SUBT(n) - 1) {
            if ((SUBT(n) != 5) || ((int32_t)n[1] == 0)) goto LAB_003b4870;
            n = (uint64_t *)*n;
        }
        n = (uint64_t *)*n;
        if (n != (uint64_t *)0x0) {
            if ((SUBT(n) - 1 < 2) ||
                ((SUBT(n) == 5 && ((int32_t)n[1] != 0)))) goto LAB_003b7c4c;
            pcVar10 = (const char *)0x5d8605;
            goto LAB_003b5490;
        }
        goto LAB_003b4870;
    case 0xca:
        if (SUBT(n) != 2) {
            if ((SUBT(n) != 5) || ((uint32_t)n[1] < 2)) goto LAB_003b4870;
            n = (uint64_t *)*n;
        }
        puVar31 = (uint64_t *)*n;
        sk_003b2180(out, (uint64_t *)n[1], (uint64_t)(iVar19 + 1), 0);
        sk_out_str(P1P8, (const char *)0x5d8609, 3);
        if (1 < SUBT(puVar31) - 1) {
            if ((SUBT(puVar31) != 5) || (*(int32_t *)(puVar31 + 1) == 0)) goto LAB_003b4870;
            puVar31 = (uint64_t *)*puVar31;
        }
        n = (uint64_t *)*puVar31;
LAB_003b7c4c:
        puVar14ptr = (const char *)0x5d8609;
        goto LAB_003b73b0;
    case 0xcb:
        if (1 < SUBT(n) - 1) {
            if ((SUBT(n) != 5) || ((int32_t)n[1] == 0)) goto LAB_003b4870;
            n = (uint64_t *)*n;
        }
        plVar9 = (uint64_t)*n;
        if (1 < SUBT((uint64_t *)plVar9) - 1) {
            if ((SUBT((uint64_t *)plVar9) != 5) || ((int32_t)((uint64_t *)plVar9)[1] == 0)) goto LAB_003b4870;
            plVar9 = (uint64_t)*(uint64_t *)plVar9;
        }
        lVar27 = *(uint64_t *)plVar9;
        if ((SUBT((uint64_t *)lVar27) - 1 < 2) ||
            ((SUBT((uint64_t *)lVar27) == 5 && (*(int32_t *)(lVar27 + 8) != 0)))) {
            sk_003b8d18(out, (uint64_t *)lVar27, d3, (uint64_t)&DAT_005d8609);
            sk_out_str(P1P8, (const char *)0x5d8609, 3);
        }
        if ((*(char *)((long)out + 0x21) == '\x01') && (*(char *)((long)out + 0x31) == '\x01')) {
            sk_out_str(P1P8, s_Swift_005d6ef0, 5);
            sk_out_str(P1P8, (const char *)0x5d0ce6, 1);
        }
        pcVar10 = s_AnyObject_005d860d;
        goto LAB_003b80bc;
    case 0xcc:
        pcVar10 = s_protocol_self_conformance_descri_005d808c;
        goto LAB_003b30a8;
    case 0xcd:
        pcVar10 = s_protocol_self_conformance_witnes_005d7c2f;
        goto LAB_003b2fbc;
    case 0xce:
        pcVar10 = s_protocol_self_conformance_witnes_005d7af1;
        uVar32 = 0x2c;
        goto LAB_003b6b14;
    case 0xcf:
        sk_out_str(P1P8, s_protocol_witness_for_005d7c56, 0x15);
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b27e4:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b27e4;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = s_in_conformance_005d7c6c;
        goto LAB_003b35f8;
    case 0xd0:
        pcVar10 = s_protocol_witness_table_for_005d7b43;
        goto LAB_003b32f0;
    case 0xd1:
        pcVar10 = s_protocol_witness_table_accessor_f_005d7b1e;
        goto LAB_003b3220;
    case 0xd2:
        pcVar10 = s_protocol_witness_table_pattern_f_005d7b5f;
LAB_003b32dc:
        uVar32 = 0x23;
        goto LAB_003b6b14;
    case 0xd3:
    case 0xd4:
        if (*(char *)((long)out + 0x2b) != '\x01') {
            sk_out_str(P1P8, s_reabstraction_thunk_005d7d7d, 0x14);
            if ((uint16_t)*puVar21 == 0xd4) sk_out_str(P1P8, s_helper_005d7d92, 7);
            if ((SUBT(n) == 5) && ((int32_t)n[1] == 3)) {
                sk_003b2180(out, (uint64_t *)*(uint64_t *)*n, (uint64_t)(iVar19 + 1), 0);
                uVar13 = 1;
                sk_out_str(P1P8, (const char *)0x5d021c, 1);
            } else uVar13 = 0;
            sk_out_str(P1P8, s_from_005d7d9a, 5);
            bVar17 = SUBT(n);
            if (bVar17 == 2) { uVar30 = 2; LAB_003b3bec:; }
            else if (bVar17 == 5) { uVar30 = (uint64_t)(uint32_t)n[1]; goto LAB_003b3bec; }
            else goto LAB_003b3c14;
            if (uVar30 <= uVar13 + 1) goto LAB_003b3c14;
            puVar21 = n;
            if (1 < bVar17 - 1) puVar21 = (uint64_t *)*n;
            uVar30 = puVar21[uVar13 + 1];
            goto LAB_003b3c14;
LAB_003b3c14:
            d3 = (uint64_t)(iVar19 + 1);
            sk_003b2180(out, (uint64_t *)uVar30, d3, 0);
            pcVar10 = (const char *)0x5d7da0;
            uVar32 = 4;
            goto LAB_003b3c90;
        }
        sk_out_str(P1P8, s_thunk_for_005d7d72, 10);
        bVar17 = SUBT(n);
        if (bVar17 == 1) {
            lVar27 = 0;
LAB_003b3dcc:
            puVar21 = (uint64_t *)n[lVar27];
            goto LAB_003b3da4;
        }
        if (bVar17 == 5) {
            if ((uint32_t)n[1] != 0) {
                lVar27 = (uint64_t)(uint32_t)n[1] - 1;
                n = (uint64_t *)*n;
                goto LAB_003b3dcc;
            }
        } else if (bVar17 == 2) {
            lVar27 = 1;
            goto LAB_003b3dcc;
        }
        goto LAB_003b3da0;
    case 0xd5:
        sk_out_str(P1P8, s_reabstraction_thunk_005d7d7d, 0x14);
        if ((SUBT(n) == 5) && ((int32_t)n[1] == 4)) {
            sk_003b2180(out, (uint64_t *)*(uint64_t *)*n, (uint64_t)(iVar19 + 1), 0);
            uVar13 = 1;
            sk_out_str(P1P8, (const char *)0x5d021c, 1);
        } else uVar13 = 0;
        sk_out_str(P1P8, s_from_005d7d9a, 5);
        if ((SUBT(n) == 5) && ((uVar13 | 2) < (uint64_t)(uint32_t)n[1])) {
            uVar32 = *(uint64_t *)(*n + (uVar13 | 2) * 8);
        } else uVar32 = 0;
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar32, d3, 0);
        sk_out_str(P1P8, (const char *)0x5d7da0, 4);
        bVar17 = SUBT(n);
        if (bVar17 == 2) { uVar30 = 2; LAB_003b3c44:; }
        else if (bVar17 == 5) { uVar30 = (uint64_t)(uint32_t)n[1]; goto LAB_003b3c44; }
        else goto LAB_003b3c6c;
        if (uVar30 <= uVar13 + 1) goto LAB_003b3c6c;
        puVar21 = n;
        if (1 < bVar17 - 1) puVar21 = (uint64_t *)*n;
        uVar30 = puVar21[uVar13 + 1];
        goto LAB_003b3c6c;
LAB_003b3c6c:
        sk_003b2180(out, (uint64_t *)uVar30, d3, 0);
        pcVar10 = s_self_005d7dc4;
        uVar32 = 6;
LAB_003b3c90:
        sk_out_str(P1P8, pcVar10, uVar32);
        bVar17 = SUBT(n);
        uVar30 = (uint64_t)bVar17;
        uVar23 = (uint32_t)bVar17;
        if (uVar23 == 1) {
LAB_003b3cb4:
            if (uVar30 <= uVar13) goto LAB_003b40b0;
            if (1 < uVar23 - 1) n = (uint64_t *)*n;
        } else if (uVar23 != 2) {
            if (bVar17 != 5) goto LAB_003b40b0;
            uVar30 = (uint64_t)(uint32_t)n[1];
            goto LAB_003b3cb4;
        }
        n = (uint64_t *)n[uVar13];
        goto LAB_003b3da8;
    case 0xd6:
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b2700:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b2700;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = s_with_global_actor_constraint_005d7da5;
        uVar32 = 0x1e;
        goto LAB_003b3bb8;
    case 0xd7:
        if (SUBT(n) - 1 < 2) {
LAB_003b67fc:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b67fc;
            }
            uVar13 = 0;
        }
        pcVar10 = (const char *)0x5d46f0;
LAB_003b79f0:
        uVar32 = 4;
        goto LAB_003b7a20;
    case 0xd8:
        if (SUBT(n) - 1 < 2) {
LAB_003b694c:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b694c;
            }
            uVar13 = 0;
        }
        pcVar10 = s_read2_005d86fc;
        uVar32 = 5;
        goto LAB_003b7a20;
    case 0xd9:
        sk_out_str(P1P8, s_related_decl___005d7633, 0xe);
        puVar21 = n;
        if (1 < SUBT(n) - 1) puVar21 = (uint64_t *)*n;
        sk_out_str(P1P8, (const char *)*(uint64_t *)*puVar21, (long)(((uint64_t *)*puVar21)[1]));
        pcVar10 = s___for_005d7642;
        uVar32 = 6;
        goto LAB_003b38bc;
    case 0xda:
        if ((SUBT(n) == 2) || ((SUBT(n) == 5 && ((int32_t)n[1] == 2)))) {
            sk_out_str(P1P8, s_retroactive___005d76bb, 0xe);
            puVar21 = n;
            if (SUBT(n) - 1 < 2) {
LAB_003b2d8c:
                uVar13 = *puVar21;
            } else {
                if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                    puVar21 = (uint64_t *)*n;
                    goto LAB_003b2d8c;
                }
                uVar13 = 0;
            }
            d3 = (uint64_t)(iVar19 + 1);
            sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
            goto LAB_003b3bbc;
        }
        goto LAB_003b4870;
    case 0xdb:
        if ((SUBT(n) - 1 < 2) ||
            ((SUBT(n) == 5 && ((int32_t)n[1] != 0)))) goto caseD65;
caseD14:
        pcVar10 = (const char *)*n;
        uVar13 = n[1];
LAB_003b68e8:
        out = out + 1;
        goto LAB_003b486c;
    case 0xdc:
        pcVar10 = s___shared_005d76eb;
LAB_003b2fd0:
        uVar32 = 9;
        goto LAB_003b6b14;
    case 0xdd:
        pcVar10 = s___owned_005d76f5;
LAB_003b3298:
        uVar32 = 8;
        goto LAB_003b6b14;
    case 0xde:
        pcVar10 = (const char *)0x5d85ea;
        goto LAB_003b3160;
    case 0xdf:
        bVar17 = SUBT(n);
        puVar21 = n;
        if (bVar17 - 1 < 2) {
LAB_003b2510:
            puVar21 = (uint64_t *)*puVar21;
        } else {
            if (bVar17 == 5) {
                if ((int32_t)n[1] == 0) goto LAB_003b3da0;
                puVar21 = (uint64_t *)*n;
                goto LAB_003b2510;
            }
            puVar21 = (uint64_t *)0x0;
        }
        if ((bVar17 != 5) || ((int32_t)n[1] != 3)) goto LAB_003b3da4;
        puVar31 = (uint64_t *)*(uint64_t *)(*n + 0x10);
        sk_003b2180(out, (uint64_t *)*(uint64_t *)(*n + 8), (uint64_t)(iVar19 + 1), 0);
        sk_vec_byte_append(P1P8, 0x20);
        sk_003b2180(out, puVar21, (uint64_t)(iVar19 + 1), 0);
        if (puVar31 == (uint64_t *)0x0) goto LAB_003b4870;
        sk_out_str(P1P8, (const char *)0x5d5321, 2);
        bVar17 = SUBT(puVar31);
        uVar20 = (uint32_t)bVar17;
        if (bVar17 != 1) {
            if (bVar17 == 5) {
                uVar20 = *(uint32_t *)(puVar31 + 1);
                if (uVar20 == 0) goto LAB_003b7564;
            } else if (bVar17 != 2) goto LAB_003b7564;
        }
        uVar13 = 0;
        goto LAB_003b84a0;
    case 0xe0:
        sk_vec_byte_append(P1P8, 0x7b);
        uVar13 = 0;
        goto LAB_003b63dc;
    case 0xe1:
    case 0xe2:
        pcVar10 = (const char *)0x5d7133;
        if (uVar5 != 0xe2) pcVar10 = (const char *)0x5d8a3d;
        uVar32 = 4;
        goto LAB_003b6b14;
    case 0xe3:
        if (SUBT(n) - 1 < 2) {
LAB_003b4f6c:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b4f6c;
            }
            uVar13 = 0;
        }
        pcVar10 = s_setter_005d86d4;
        goto LAB_003b7a10;
    case 0xe5:
        pcVar10 = s_serialized_005d782a;
LAB_003b4d8c:
        out = out + 1;
        uVar13 = 10;
        goto LAB_003b486c;
    case 0xe6:
        pcVar10 = s_static_005d71c0;
        goto LAB_003b30bc;
    case 0xe8:
        pcVar10 = s_subscript_005d745e;
        uVar32 = 9;
        iVar19 = 2;
        bVar8 = false;
        goto LAB_003b747c;
    case 0xe9:
        if (*(char *)((long)out + 0x23) == '\x01') {
            sk_out_str(P1P8, s_with_unmangled_suffix_005d7567, 0x17);
            uStack_d8 = n[1];
            local_e0[0] = *n;
            FUN_0037364c(local_130, local_e0);
            if (cStack_119 < 0) {
                FUN_00113368((uint64_t *)local_c0, local_130[0], uStack_128);
            } else {
                /* rebuild the 16-byte string bytes in local_c0 from local_130 ptr + uStack_128 len */
                for (int k = 0; k < 8; k++) local_c0[k] = (uint8_t)(local_130[0] >> (8 * k));
                for (int k = 0; k < 8; k++) local_c0[8 + k] = (uint8_t)(uStack_128 >> (8 * k));
                local_c0[16] = cStack_119;
            }
            FUN_003bcb1c(P1P8, (uint64_t *)local_c0);
            if ((int8_t)local_c0[16] < 0) {
                sk_lock((void *)B64LE(local_c0, 0), B64LE(local_c0, 8) & 0x7fffffffffffffff);
            }
            if (cStack_119 < 0) {
                uVar13 = (uint64_t)(uint8_t)cStack_119;
                goto LAB_003b8198;
            }
        }
        goto LAB_003b4870;
    case 0xeb:
        sk_out_str(P1P8, (const char *)0x5d3bb7, 1);
        sk_003b8d18(out, n, d3, (uint64_t)&DAT_005d0c46);
        goto LAB_003b72a0;
    case 0xec:
        puVar31 = (uint64_t *)sk_003ba044(out, n, 0xed);
        uVar32 = 0;
        if (puVar31 != (uint64_t *)0x0) {
            sk_out_str(P1P8, (const char *)*puVar31, (long)puVar31[1]);
            sk_out_str(P1P8, (const char *)0x5d3bb9, 2);
        }
        uVar32 = (uint64_t)sk_003ba044((uint64_t *)uVar32, n, 0xf4);
        sk_003b2180(out, (uint64_t *)uVar32, (uint64_t)(iVar19 + 1), 0);
        uVar32 = (uint64_t)out;   /* FUN_003b2180 returns its out pointer */
        lVar27 = (long)sk_003ba044((uint64_t *)uVar32, n, 0x122);
        if (lVar27 == 0) goto LAB_003b4870;
        pcVar10 = (const char *)0x5cef08;
LAB_003b5490:
        out = out + 1;
        uVar13 = 3;
        goto LAB_003b486c;
    case 0xed:
        sk_out_str(P1P8, (const char *)*n, (long)n[1]);
        pcVar10 = (const char *)0x5d3bb9;
        goto LAB_003b6494;
    case 0xee:
        pcVar10 = s_Pack__005d7657;
        uVar32 = 5;
        goto LAB_003b6588;
    case 0xef:
    case 0xf0:
        pcVar10 = s__direct_005d765d;
        if (uVar5 != 0xef) pcVar10 = s__indirect_005d7665;
        uVar32 = 7;
        if (uVar5 != 0xef) uVar32 = 9;
        sk_out_str(P1P8, pcVar10, uVar32);
        pcVar10 = s_Pack__005d766f;
        uVar32 = 6;
LAB_003b6588:
        sk_out_str(P1P8, pcVar10, uVar32);
        sk_003b8d18(out, n, d3, (uint64_t)&DAT_005d0c46);
        pcVar10 = (const char *)0x5ce74f;
        goto LAB_003b7fb0;
    case 0xf1:
        pcVar10 = s_repeat_005d7676;
        goto LAB_003b30bc;
    case 0xf2:
        sk_out_str(P1P8, s____level__005d767e, 10);
        puVar21 = n;
        if (SUBT(n) == 5) puVar21 = (uint64_t *)*n;
        sk_003b1e74(P1P8, *(uint64_t *)puVar21[1], 0);
        sk_out_str(P1P8, (const char *)0x5d7689, 4);
        pcVar10 = s_each_005d712d;
LAB_003b3160:
        uVar32 = 5;
        goto LAB_003b6b14;
    case 0xf3:
        goto caseD_f3;
    case 0xf5:
        pcVar10 = s_type_symbolic_reference_0x_005d7f06;
        uVar32 = 0x1a;
        goto LAB_003b5a40;
    case 0xf8:
        bVar17 = SUBT(n);
        uVar18 = (uint32_t)bVar17;
        uVar23 = bVar17 - 1;
        puVar21 = n;
        if (1 < uVar23) puVar21 = (uint64_t *)*n;
        if (*(short *)(*puVar21 + 0x10) == 0x130) {
            puVar21 = n;
            if (uVar23 < 2) {
LAB_003b6b68:
                uVar13 = *puVar21;
LAB_003b7ed4:
                if (bVar17 != 2) {
                    if ((bVar17 != 5) || ((uint32_t)n[1] < 2)) goto LAB_003b8330;
                    n = (uint64_t *)*n;
                }
                puVar31 = (uint64_t *)n[1];
            } else {
                if (bVar17 != 5) {
                    uVar13 = 0;
                    goto LAB_003b7ed4;
                }
                if ((int32_t)n[1] != 0) {
                    puVar21 = (uint64_t *)*n;
                    goto LAB_003b6b68;
                }
                uVar13 = 0;
LAB_003b8330:
                puVar31 = (uint64_t *)0x0;
            }
            if (1 < SUBT(puVar31) - 1) {
                if ((SUBT(puVar31) != 5) || (*(int32_t *)(puVar31 + 1) == 0)) {
                    n = (uint64_t *)0x0;
                    goto LAB_003b48c0;
                }
                puVar31 = (uint64_t *)*puVar31;
            }
            n = (uint64_t *)*puVar31;
            goto LAB_003b48c0;
        }
        goto LAB_003b3304;
    case 0xf9:
        pcVar10 = s_type_metadata_for_005d8193;
        goto LAB_003b2f00;
    case 0xfa:
        pcVar10 = s_type_metadata_accessor_for_005d81a6;
        goto LAB_003b32f0;
    case 0xfb:
        pcVar10 = s_type_metadata_completion_functio_005d8245;
        goto LAB_003b2fbc;
    case 0xfc:
        pcVar10 = s_type_metadata_instantiation_cach_005d81c2;
LAB_003b2fbc:
        uVar32 = 0x26;
        goto LAB_003b6b14;
    case 0xfd:
        pcVar10 = s_type_metadata_instantiation_func_005d81e9;
        goto LAB_003b30a8;
    case 0xfe:
        pcVar10 = s_type_metadata_singleton_initiali_005d8213;
        uVar32 = 0x31;
        goto LAB_003b6b14;
    case 0xff:
        pcVar10 = s_demangling_cache_variable_for_ty_005d826c;
        uVar32 = 0x30;
        goto LAB_003b6b14;
    case 0x100:
        pcVar10 = s_mangled_name_ref_for_type_metada_005d829d;
        goto LAB_003b320c;
    case 0x101:
        pcVar10 = s_lazy_cache_variable_for_type_met_005d82c5;
        goto LAB_003b30d0;
    case 0x103:
        pcVar10 = s_unknown_index_005d7649;
        out = out + 1;
        uVar13 = 0xd;
        goto LAB_003b486c;
    case 0x104:
        pcVar10 = (const char *)0x5d90b1;
        uVar32 = 4;
        goto LAB_003b310c;
    case 0x105:
        pcVar10 = s_unowned_005d90b6;
        uVar32 = 7;
        goto LAB_003b310c;
    case 0x106:
        pcVar10 = s_unowned_unsafe__005d90be;
        uVar32 = 0xf;
LAB_003b310c:
        sk_out_str(P1P8, pcVar10, uVar32);
        pcVar10 = (const char *)0x5d021c;
        uVar32 = 1;
        goto LAB_003b6b14;
    case 0x107:
        if (SUBT(n) - 1 < 2) {
LAB_003b6204:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b6204;
            }
            uVar13 = 0;
        }
        pcVar10 = s_unsafeAddressor_005d86a6;
LAB_003b7960:
        uVar32 = 0xf;
        goto LAB_003b7a20;
    case 0x108:
        if (SUBT(n) - 1 < 2) {
LAB_003b59dc:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b59dc;
            }
            uVar13 = 0;
        }
        pcVar10 = s_unsafeMutableAddressor_005d86b6;
LAB_003b7668:
        uVar32 = 0x16;
        goto LAB_003b7a20;
    case 0x109:
        puVar21 = n;
        if (1 < SUBT(n) - 1) puVar21 = (uint64_t *)*n;
        { sk_r53_str2_t s2 = FUN_003bccc4(*(uint32_t *)*puVar21);
          sk_out_str(P1P8, s2.s, s2.len); }
        if (*(char *)((long)out + 0x2c) == '\x01') { pcVar10 = s_for_005d7ca3; uVar32 = 5; }
        else { pcVar10 = s_value_witness_for_005d85b8; uVar32 = 0x13; }
        goto LAB_003b38bc;
    case 0x10a:
        pcVar10 = s_value_witness_table_for_005d85cc;
LAB_003b312c:
        uVar32 = 0x18;
        goto LAB_003b6b14;
    case 0x10b:
        iVar19 = 1;
LAB_003b7478:
        uVar32 = 0;
        pcVar10 = (const char *)0x5be7c0;
        bVar8 = true;
LAB_003b747c:
        iVar35 = -1;
        pcVar15 = (const char *)0x5be7c0;
        uVar16 = 0;
LAB_003b7480:
        uVar32 = FUN_003bc520(out, n, d3, flag & 1, iVar19, bVar8, pcVar15, uVar16, iVar35,
                              pcVar10, uVar32);
        goto caseD4;
    case 0x10c:
        sk_out_str(P1P8, s_vtable_thunk_for_005d7c0c, 0x11);
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b29c4:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b29c4;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = s_dispatching_to_005d7c1e;
LAB_003b35f8:
        uVar32 = 0x10;
        goto LAB_003b3960;
    case 0x10d:
        pcVar10 = s_override_005d772e;
        goto LAB_003b80bc;
    case 0x10e:
        if (SUBT(n) - 1 < 2) {
LAB_003b6174:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b6174;
            }
            uVar13 = 0;
        }
        pcVar10 = s_willset_005d86ed;
LAB_003b79d0:
        uVar32 = 7;
        goto LAB_003b7a20;
    case 0x10f:
        pcVar10 = s_reflection_metadata_builtin_desc_005d8921;
        goto LAB_003b320c;
    case 0x110:
        pcVar10 = s_reflection_metadata_field_descri_005d8949;
LAB_003b3004:
        uVar32 = 0x25;
        goto LAB_003b6b14;
    case 0x111:
        pcVar10 = s_reflection_metadata_associated_t_005d896f;
        uVar32 = 0x2f;
        goto LAB_003b6b14;
    case 0x112:
        pcVar10 = s_reflection_metadata_superclass_d_005d899f;
        goto LAB_003b30d0;
    case 0x114:
        pcVar10 = s_curry_thunk_of_005d71db;
        uVar32 = 0xf;
        goto LAB_003b6b14;
    case 0x115:
        pcVar10 = s_identity_thunk_of_005d71eb;
        goto LAB_003b2f00;
    case 0x116:
        pcVar10 = s_dispatch_thunk_of_005d71fe;
        goto LAB_003b2f00;
    case 0x117:
        pcVar10 = s_method_descriptor_for_005d7211;
        uVar32 = 0x16;
        goto LAB_003b6b14;
    case 0x118:
        pcVar10 = s_protocol_requirements_base_descr_005d8150;
        goto LAB_003b30d0;
    case 0x119:
        pcVar10 = s_associated_conformance_descripto_005d82f0;
        uVar32 = 0x26;
        goto LAB_003b29dc;
    case 0x11a:
        pcVar10 = s_default_associated_conformance_a_005d8317;
        uVar32 = 0x2c;
LAB_003b29dc:
        sk_out_str(P1P8, pcVar10, uVar32);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b2a08:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b2a08;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        sk_out_str(P1P8, (const char *)0x5d0ce6, 1);
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b344c:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b344c;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = (const char *)0x5d3bb9;
        uVar32 = 2;
LAB_003b3b44:
        sk_out_str(P1P8, pcVar10, uVar32);
        if ((SUBT(n) == 5) && (2 < (uint32_t)n[1])) {
LAB_003b4830:
            n = (uint64_t *)*(uint64_t *)(*n + 0x10);
            goto LAB_003b3da8;
        }
        goto LAB_003b40b0;
    case 0x11b:
        sk_out_str(P1P8, s_base_conformance_descriptor_for_005d838b, 0x20);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b2980:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b2980;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        pcVar10 = (const char *)0x5d3bb9;
        uVar32 = 2;
LAB_003b3bb8:
        sk_out_str(P1P8, pcVar10, uVar32);
LAB_003b3bbc:
        if (SUBT(n) != 2) {
            if ((SUBT(n) != 5) || ((uint32_t)n[1] < 2)) {
LAB_003b40b0:
                n = (uint64_t *)0x0;
                goto LAB_003b3da8;
            }
LAB_003b3bdc:
            n = (uint64_t *)*n;
        }
LAB_003b3be0:
        n = (uint64_t *)n[1];
        goto LAB_003b3da8;
    case 0x11c:
        pcVar10 = s_associated_type_descriptor_for_005d8344;
LAB_003b2924:
        uVar32 = 0x1f;
        goto LAB_003b6b14;
    case 0x11d:
        pcVar10 = s_async_005d710e;
LAB_003b68b8:
        out = out + 1;
        uVar13 = 6;
        goto LAB_003b486c;
    case 0x11e:
        pcVar10 = s_throws_005d89f3;
LAB_003b68f8:
        out = out + 1;
        uVar13 = 7;
        goto LAB_003b486c;
    case 0x11f:
        sk_out_str(P1P8, s_throws__005d89fb, 8);
        if (SUBT(n) != 1) {
            if ((SUBT(n) != 5) || ((int32_t)n[1] != 1)) goto LAB_003b72a0;
            n = (uint64_t *)*n;
        }
        uVar13 = *n;
LAB_003b6620:
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        goto LAB_003b72a0;
    case 0x120:
        pcVar10 = s_empty_list_005d8a04;
LAB_003b66ec:
        out = out + 1;
        uVar13 = 0xc;
        goto LAB_003b486c;
    case 0x121:
        pcVar10 = s_first_element_marker_005d8a11;
        goto LAB_003b61bc;
    case 0x122:
        pcVar10 = s_variadic_marker_005d8a28;
        goto LAB_003b717c;
    case 0x123:
        sk_out_str(P1P8, s_outlined_bridged_method___005d72aa, 0x19);
        sk_out_str(P1P8, (const char *)*n, (long)n[1]);
        pcVar10 = s___of_005d72c4;
LAB_003b50e0:
        out = out + 1;
        uVar13 = 5;
        goto LAB_003b486c;
    case 0x124:
        pcVar10 = s_outlined_copy_of_005d72ca;
        uVar32 = 0x11;
        goto LAB_003b2f6c;
    case 0x125:
        pcVar10 = s_outlined_consume_of_005d72dc;
        uVar32 = 0x14;
LAB_003b2f6c:
        sk_out_str(P1P8, pcVar10, uVar32);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b2f98:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b2f98;
            }
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        if (SUBT(n) == 2) goto LAB_003b3be0;
        if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) goto LAB_003b3bdc;
        goto LAB_003b4870;
    case 0x126:
        pcVar10 = s_outlined_retain_of_005d72f1;
        uVar32 = 0x13;
        goto LAB_003b6b14;
    case 0x127:
        pcVar10 = s_outlined_release_of_005d7305;
        goto LAB_003b26cc;
    case 0x128:
    case 0x16c:
        pcVar10 = s_outlined_init_with_take_of_005d731a;
        goto LAB_003b32f0;
    case 0x129:
    case 0x16d:
        pcVar10 = s_outlined_init_with_copy_of_005d7336;
        goto LAB_003b32f0;
    case 0x12a:
    case 0x16e:
        pcVar10 = s_outlined_assign_with_take_of_005d7352;
        goto LAB_003b2390;
    case 299:
    case 0x16f:
        pcVar10 = s_outlined_assign_with_copy_of_005d7370;
LAB_003b2390:
        uVar32 = 0x1d;
        goto LAB_003b6b14;
    case 300:
    case 0x170:
        pcVar10 = s_outlined_destroy_of_005d738e;
LAB_003b26cc:
        uVar32 = 0x14;
        goto LAB_003b6b14;
    case 0x12d:
        pcVar10 = s_outlined_variable___005d7401;
        uVar32 = 0x13;
        goto LAB_003b5650;
    case 0x12e:
        pcVar10 = s_outlined_read_only_object___005d741a;
        uVar32 = 0x1b;
LAB_003b5650:
        sk_out_str(P1P8, pcVar10, uVar32);
        sk_003b1e74(P1P8, *n, 0);
        pcVar10 = (const char *)0x5d7415;
        goto LAB_003b5ec8;
    case 0x12f:
        bVar17 = SUBT(n);
        puVar11 = n;
        if (bVar17 - 1 < 2) {
LAB_003b7d24:
            if (bVar17 == 5) goto LAB_003b7d44;
            puVar2 = (uint64_t *)0x0;
            if (bVar17 == 1) puVar2 = n + 1;
            if (bVar17 != 2) puVar21 = puVar2;
            else puVar21 = (uint64_t *)0x0;
        } else {
            if (bVar17 != 5) {
                puVar11 = (uint64_t *)0x0;
                goto LAB_003b7d24;
            }
            puVar11 = (uint64_t *)*n;
LAB_003b7d44:
            puVar21 = (uint64_t *)(*n + (uint64_t)(uint32_t)n[1] * 8);
        }
        sk_003b20f4(out, puVar11, puVar21, (int32_t)d3, (uint64_t)&DAT_005d0ce6);
        goto LAB_003b4870;
    case 0x131:
        pcVar10 = s_module_descriptor_005d8a42;
        goto LAB_003b2f00;
    case 0x132:
        pcVar10 = s_extension_descriptor_005d8a6b;
        goto LAB_003b2d9c;
    case 0x133:
        pcVar10 = s_anonymous_descriptor_005d8a55;
LAB_003b2d9c:
        uVar32 = 0x15;
        goto LAB_003b6b14;
    case 0x134:
        pcVar10 = s_generic_parameter_reference_for_a_005d8a81;
        uVar32 = 0x30;
LAB_003b739c:
        sk_out_str(P1P8, pcVar10, uVar32);
caseD65:
        puVar14ptr = (const char *)0x0;
LAB_003b73b0:
        sk_003b8d18(out, n, d3, (uint64_t)puVar14ptr);
        goto LAB_003b4870;
    case 0x135:
        if (SUBT(n) - 1 < 2) {
LAB_003b54c0:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b54c0;
            }
            uVar13 = 0;
        }
        sk_003b9794(out, uVar13, d3);
        pcVar10 = (const char *)0x5dd27a;
        goto LAB_003b7fb0;
    case 0x136:
        sk_out_str(P1P8, (const char *)0x5d3566, 1);
        if (1 < SUBT(n) - 1) {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b5420;
            }
            goto LAB_003b77fc;
        }
LAB_003b5420:
        uVar13 = *n;
        goto LAB_003b7800;
    case 0x137:
        sk_out_str(P1P8, (const char *)0x5d3566, 1);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b5c08:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b5c08;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        puVar14ptr = (const char *)0x5d3cba;
        uVar32 = 3;
        goto LAB_003b77cc;
    case 0x138:
        sk_out_str(P1P8, (const char *)0x5d3566, 1);
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b5504:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b5504;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        puVar14ptr = (const char *)0x5d7415;
        uVar32 = 4;
LAB_003b77cc:
        sk_out_str(P1P8, (const char *)puVar14ptr, uVar32);
        if (SUBT(n) == 2) {
LAB_003b77f4:
            uVar13 = n[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                n = (uint64_t *)*n;
                goto LAB_003b77f4;
            }
LAB_003b77fc:
            uVar13 = 0;
        }
LAB_003b7800:
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        pcVar10 = (const char *)0x5d32c2;
        goto LAB_003b791c;
    case 0x139:
        sk_out_str(P1P8, (const char *)0x5d3bb7, 1);
        if (SUBT(n) - 1 < 2) {
LAB_003b6124:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b6124;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        pcVar10 = (const char *)0x5ce788;
        goto LAB_003b791c;
    case 0x13a:
        sk_out_str(P1P8, s_accessor_function_at_005d8c65, 0x15);
caseD68:
        uVar13 = *n;
LAB_003b6148:
        sk_003b1e74(P1P8, uVar13, 0);
        goto LAB_003b4870;
    case 0x13c:
        pcVar10 = s_opaque_type_symbolic_reference_0_005d7f21;
        uVar32 = 0x21;
LAB_003b5a40:
        sk_out_str(P1P8, pcVar10, uVar32);
        if (SUBT(n) == 4) goto LAB_003b6918;
        if (SUBT(n) != 6) goto LAB_003b4870;
        uVar13 = n[1];
        sk_003b1f20(P1P8, *n, 0);
        sk_out_str(P1P8, (const char *)0x5ce80d, 2);
        out = (uint64_t *)FUN_003bc4a4((uint64_t *)((char *)out + 8), (uint8_t)uVar13);
        pcVar10 = (const char *)0x5ce788;
        goto LAB_003b7fb4;
    case 0x13d:
        pcVar10 = s_opaque_type_descriptor_for_005d84aa;
        goto LAB_003b32f0;
    case 0x13e:
        pcVar10 = s_opaque_type_descriptor_runtime_r_005d84c6;
LAB_003b30d0:
        uVar32 = 0x2a;
        goto LAB_003b6b14;
    case 0x13f:
        pcVar10 = s_opaque_type_descriptor_accessor_f_005d84f1;
LAB_003b3220:
        uVar32 = 0x24;
        goto LAB_003b6b14;
    case 0x140:
        pcVar10 = s_opaque_type_descriptor_accessor_i_005d8516;
LAB_003b30a8:
        uVar32 = 0x29;
        goto LAB_003b6b14;
    case 0x141:
        pcVar10 = s_opaque_type_descriptor_accessor_k_005d8540;
        goto LAB_003b2cf0;
    case 0x142:
        pcVar10 = s_opaque_type_descriptor_accessor_v_005d8569;
LAB_003b2cf0:
        uVar32 = 0x28;
        goto LAB_003b6b14;
    case 0x143:
        pcVar10 = (const char *)0x5d8c44;
LAB_003b5ec8:
        out = out + 1;
        uVar13 = 4;
        goto LAB_003b486c;
    case 0x144:
        sk_out_str(P1P8, s_opaque_return_type_of_005d8c49, 0x18);
        sk_003b8d18(out, n, d3, 0);
        pcVar10 = (const char *)0x5d8c62;
        goto LAB_003b6494;
    case 0x145:
        pcVar10 = s_specialized_generic_metaclass_fo_005d8c7b;
LAB_003b314c:
        uVar32 = 0x22;
        goto LAB_003b6b14;
    case 0x146:
        pcVar10 = s_canonical_specialized_generic_ty_005d8c9e;
        uVar32 = 0x39;
        goto LAB_003b6b14;
    case 0x147:
        pcVar10 = s_metadata_instantiation_cache_for_005d8cd8;
        uVar32 = 0x21;
        goto LAB_003b6b14;
    case 0x148:
        pcVar10 = s_noncanonical_specialized_generic_005d8cfa;
LAB_003b2938:
        uVar32 = 0x33;
        goto LAB_003b6b14;
    case 0x149:
        pcVar10 = s_cache_variable_for_noncanonical_s_005d8d2e;
        uVar32 = 0x46;
        goto LAB_003b6b14;
    case 0x14a:
    case 0x14b:
        pcVar10 = s_one_time_initialization_token_fo_005d8d75;
        if (uVar5 != 0x14b) pcVar10 = s_one_time_initialization_function_005d8d98;
        uVar32 = 0x22;
        if (uVar5 != 0x14b) uVar32 = 0x25;
LAB_003b38bc:
        sk_out_str(P1P8, pcVar10, uVar32);
        if (SUBT(n) != 2) {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                n = (uint64_t *)*n;
                goto LAB_003b38e4;
            }
            goto LAB_003b3da0;
        }
LAB_003b38e4:
        puVar21 = (uint64_t *)n[1];
        goto LAB_003b3da4;
    case 0x14c:
        if (SUBT(n) == 1) goto LAB_003b3320;
        if ((SUBT(n) == 5) && ((int32_t)n[1] == 1)) goto LAB_003b331c;
        sk_vec_byte_append(P1P8, 0x28);
        bVar17 = SUBT(n);
        uVar20 = (uint32_t)bVar17;
        if (bVar17 != 1) {
            if (bVar17 == 5) {
                uVar20 = (uint32_t)n[1];
                if (uVar20 == 0) goto LAB_003b8478;
            } else if (bVar17 != 2) goto LAB_003b8478;
        }
        uVar13 = 0;
        goto LAB_003b7e50;
    case 0x14d:
        pcVar10 = s_flag_for_loading_of_canonical_sp_005d8e44;
        uVar32 = 0x44;
        goto LAB_003b6b14;
    case 0x14e:
        pcVar10 = s_async_function_pointer_to_005d8e89;
        goto LAB_003b601c;
    case 0x14f:
    case 0x153:
        uVar18 = 0; uVar13 = 0; bVar17 = SUBT(n);
        uVar30 = (uint64_t)bVar17;
        uVar25 = (uint32_t)bVar17;
        uVar22 = uVar25 - 1;
        uVar23 = 0xffffffff;
        while (true) {
            uVar33 = uVar30;
            if (uVar25 != 1) {
                if (bVar17 == 5) uVar33 = (uint64_t)(uint32_t)n[1];
                else { uVar33 = 0; if (bVar17 == 2) uVar33 = 2; }
            }
            if (uVar13 == uVar33) break;
            puVar21 = n;
            if (1 < uVar25 - 1) puVar21 = (uint64_t *)*n;
            if (*(short *)(puVar21[uVar13] + 0x10) == 0x150) break;
            uVar13 = uVar13 + 1;
            uVar23 = uVar23 + 1;
            uVar18 = uVar18 + 1;
        }
        uVar33 = uVar30;
        if (bVar17 == 1) {
LAB_003b36c8:
            if (uVar33 <= uVar13) goto LAB_003b36e8;
            puVar21 = n;
            if (1 < uVar22) puVar21 = (uint64_t *)*n;
            uVar33 = puVar21[uVar13];
        } else {
            if (bVar17 == 5) { uVar33 = (uint64_t)(uint32_t)n[1]; goto LAB_003b36c8; }
            if (bVar17 == 2) { uVar33 = 2; goto LAB_003b36c8; }
LAB_003b36e8:
            uVar33 = 0;
        }
        iVar35 = (int32_t)uVar13;
        uVar28 = uVar30;
        if (bVar17 == 1) {
LAB_003b3710:
            if (uVar28 <= iVar35 + 1) goto LAB_003b3734;
            puVar21 = n;
            if (1 < uVar22) puVar21 = (uint64_t *)*n;
            uVar28 = puVar21[iVar35 + 1];
        } else {
            if (bVar17 == 5) { uVar28 = (uint64_t)(uint32_t)n[1]; goto LAB_003b3710; }
            if (bVar17 == 2) { uVar28 = 2; goto LAB_003b3710; }
LAB_003b3734:
            uVar28 = 0;
        }
        if (bVar17 == 1) {
LAB_003b375c:
            if (uVar30 <= iVar35 + 2) goto LAB_003b3784;
            puVar21 = n;
            if (1 < uVar22) puVar21 = (uint64_t *)*n;
            local_140 = puVar21[iVar35 + 2];
        } else {
            if (bVar17 == 5) { uVar30 = (uint64_t)(uint32_t)n[1]; goto LAB_003b375c; }
            if (bVar17 == 2) { uVar30 = 2; goto LAB_003b375c; }
LAB_003b3784:
            local_140 = 0;
        }
        if (uVar5 == 0x153) sk_out_str(P1P8, s_vtable_thunk_for_005d7c0c, 0x11);
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar33, d3, 0);
        sk_out_str(P1P8, (const char *)0x5d7415, 4);
        if (uVar13 == 0) puVar21 = (uint64_t *)0x0;
        else {
            uVar13 = 0;
            uVar30 = (uint64_t)(iVar35 - 1);
            do {
                bVar17 = SUBT(n);
                uVar33 = (uint64_t)bVar17;
                uVar22 = (uint32_t)bVar17;
                if (uVar23 == uVar13) {
                    bVar8 = 1 < bVar17 - 1;
                    puVar21 = n;
                    if (bVar8) puVar21 = (uint64_t *)*n;
                    if (*(short *)(puVar21[uVar30] + 0x10) == 0x2c) {
                        if (bVar17 == 1) {
LAB_003b4344:
                            if (uVar30 < uVar33) {
                                if (bVar8) n = (uint64_t *)*n;
                                puVar21 = (uint64_t *)n[uVar30];
                                goto LAB_003b4360;
                            }
                        } else {
                            if (uVar22 == 5) { uVar33 = (uint64_t)(uint32_t)n[1]; goto LAB_003b4344; }
                            if (uVar22 == 2) { uVar33 = 2; goto LAB_003b4344; }
                        }
                        puVar21 = (uint64_t *)0x0;
                        goto LAB_003b4360;
                    }
                }
                if (uVar22 == 1) {
LAB_003b384c:
                    if (uVar33 <= uVar13) goto LAB_003b386c;
                    puVar21 = n;
                    if (1 < uVar22 - 1) puVar21 = (uint64_t *)*n;
                    uVar33 = puVar21[uVar13];
                } else {
                    if (uVar22 == 5) { uVar33 = (uint64_t)(uint32_t)n[1]; goto LAB_003b384c; }
                    if (uVar22 == 2) { uVar33 = 2; goto LAB_003b384c; }
LAB_003b386c:
                    uVar33 = 0;
                }
                sk_003b2180(out, (uint64_t *)uVar33, d3, 0);
                uVar13 = uVar13 + 1;
            } while (uVar18 != uVar13);
            puVar21 = (uint64_t *)0x0;
        }
LAB_003b4360:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) == 0) {
            sk_out_str(P1P8, s_with_respect_to_parameters_005d7dcb, 0x1c);
            sk_003b2180(out, (uint64_t *)uVar28, d3, 0);
            sk_out_str(P1P8, s_and_results_005d7de8, 0xd);
            sk_003b2180(out, (uint64_t *)local_140, d3, 0);
            uVar32 = 0;
            if (puVar21 != (uint64_t *)0x0) {
                if (*(char *)((long)out + 0x27) == '\x01') goto LAB_003b43c8;
                goto LAB_003b4870;
            }
            goto caseD4;
        }
        goto LAB_003b4870;
    case 0x150:
        uVar32 = 0;
        uVar20 = (uint8_t)*n - 100;
        uVar20 = uVar20 >> 1 & 0x7f | uVar20 * 0x80 & 0xff;
        if (uVar20 < 6) {
            if (uVar20 == 0) { pcVar10 = s_differential_005d7ea0; goto LAB_003b66ec; }
            if (uVar20 == 1) { pcVar10 = s_forward_mode_derivative_005d7e70; goto LAB_003b740c; }
        } else {
            if (uVar20 == 6) { pcVar10 = s_pullback_005d7ead; goto LAB_003b7f44; }
            if (uVar20 == 7) { pcVar10 = s_reverse_mode_derivative_005d7e88; goto LAB_003b740c; }
        }
        goto caseD4;
    case 0x151:
        sk_out_str(P1P8, s_autodiff_self_reordering_reabstr_005d7df6, 0x2d);
        if (1 < SUBT(n) - 1) n = (uint64_t *)*n;
        puVar21 = (uint64_t *)*n;
        if (*(char *)((long)out + 0x2b) == '\x01') {
            sk_out_str(P1P8, (const char *)0x5d7e24, 4);
            goto LAB_003b3da4;
        }
        puVar11 = (uint64_t *)n[1];
        uVar13 = n[2];
        sVar4 = *(short *)(uVar13 + 0x10);
        lVar27 = 0x10;
        if (sVar4 == 0x2c) lVar27 = 0x18;
        sk_out_str(P1P8, (const char *)0x5d7e24, 4);
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)*(uint64_t *)((long)n + lVar27), d3, 0);
        if ((uVar13 != 0) && (sVar4 == 0x2c)) {
            sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
            sk_vec_byte_append(P1P8, 0x20);
        }
        sk_out_str(P1P8, s_from_005d7e29, 6);
        sk_003b2180(out, puVar21, d3, 0);
        sk_out_str(P1P8, (const char *)0x5d7da0, 4);
        n = puVar11;
        goto LAB_003b3da8;
    case 0x152:
        sk_out_str(P1P8, s_autodiff_subset_parameters_thunk_005d7e30, 0x25);
        bVar17 = SUBT(n);
        uVar13 = (uint64_t)bVar17;
        uVar23 = (uint32_t)bVar17;
        uVar22 = (uint32_t)bVar17;
        uVar18 = (uint32_t)bVar17;
        puVar21 = n;
        if (uVar23 == 1) {
            lVar27 = 0;
            uVar33 = 0xffffffffffffffff;
            uVar30 = uVar13;
LAB_003b3dfc:
            local_138 = puVar21[lVar27];
LAB_003b3e14:
            uVar29 = uVar30 - 3;
            uVar28 = uVar13;
            if (uVar22 == 1) goto LAB_003b441c;
            if (uVar18 == 2) { uVar28 = 2; goto LAB_003b441c; }
            if (uVar18 == 5) { uVar28 = (uint64_t)(uint32_t)n[1]; goto LAB_003b441c; }
LAB_003b443c:
            uVar33 = 0;
        } else {
            if (uVar23 != 5) {
                if (uVar22 == 2) { uVar33 = 0; lVar27 = 1; uVar30 = 2; goto LAB_003b3dfc; }
                uVar30 = 0; local_138 = 0; uVar33 = 0xfffffffffffffffe;
                goto LAB_003b3e14;
            }
            uVar30 = (uint64_t)(uint32_t)n[1];
            uVar33 = uVar30 - 2;
            if ((uint32_t)n[1] != 0) {
                lVar27 = uVar30 - 1;
                puVar21 = (uint64_t *)*n;
                goto LAB_003b3dfc;
            }
            local_138 = 0; uVar30 = 0;
            uVar29 = 0xfffffffffffffffd; uVar28 = 0;
LAB_003b441c:
            if (uVar28 <= uVar33) goto LAB_003b443c;
            puVar21 = n;
            if (1 < uVar23 - 1) puVar21 = (uint64_t *)*n;
            uVar33 = puVar21[uVar33];
        }
        uVar28 = uVar13;
        if (uVar18 == 1) {
LAB_003b446c:
            if (uVar28 <= uVar29) goto LAB_003b448c;
            puVar21 = n;
            if (1 < uVar18 - 1) puVar21 = (uint64_t *)*n;
            uVar28 = puVar21[uVar29];
        } else {
            if (uVar18 == 5) { uVar28 = (uint64_t)(uint32_t)n[1]; goto LAB_003b446c; }
            if (uVar22 == 2) { uVar28 = 2; goto LAB_003b446c; }
LAB_003b448c:
            uVar28 = 0;
        }
        if (uVar22 == 1) {
LAB_003b44b4:
            if (uVar13 <= uVar30 - 4) goto LAB_003b44d8;
            puVar21 = n;
            if (1 < uVar22 - 1) puVar21 = (uint64_t *)*n;
            uVar13 = puVar21[uVar30 - 4];
        } else {
            if (uVar22 == 5) { uVar13 = (uint64_t)(uint32_t)n[1]; goto LAB_003b44b4; }
            if (uVar22 == 2) { uVar13 = 2; goto LAB_003b44b4; }
LAB_003b44d8:
            uVar13 = 0;
        }
        uVar30 = uVar30 - 5;
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        sk_out_str(P1P8, s_from_005d7e29, 6);
        if (uVar30 == 0) {
            puVar21 = n;
            if (SUBT(n) - 1 < 2) {
LAB_003b45b0:
                uVar13 = *puVar21;
            } else {
                if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                    puVar21 = (uint64_t *)*n;
                    goto LAB_003b45b0;
                }
                uVar13 = 0;
            }
            sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        } else {
            uVar13 = 0;
            uVar29 = 1;
            do {
                bVar17 = SUBT(n);
                uVar26 = (uint64_t)bVar17;
                uVar23 = (uint32_t)bVar17;
                if (uVar23 == 1) {
LAB_003b4540:
                    if (uVar26 <= uVar13) goto LAB_003b4560;
                    puVar21 = n;
                    if (1 < uVar23 - 1) puVar21 = (uint64_t *)*n;
                    uVar13 = puVar21[uVar13];
                } else {
                    if (uVar23 == 5) { uVar26 = (uint64_t)(uint32_t)n[1]; goto LAB_003b4540; }
                    if (bVar17 == 2) { uVar26 = 2; goto LAB_003b4540; }
LAB_003b4560:
                    uVar13 = 0;
                }
                sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
                bVar8 = uVar29 < uVar30;
                uVar13 = uVar29;
                uVar29 = (uint64_t)((int32_t)uVar29 + 1);
            } while (bVar8);
        }
        if ((*(uint8_t *)((long)out + 0x2b) & 1) == 0) {
            sk_out_str(P1P8, s_with_respect_to_parameters_005d7dcb, 0x1c);
            sk_003b2180(out, (uint64_t *)uVar28, d3, 0);
            sk_out_str(P1P8, s_and_results_005d7de8, 0xd);
            sk_003b2180(out, (uint64_t *)uVar33, d3, 0);
            sk_out_str(P1P8, s_to_parameters_005d7e56, 0xf);
            sk_003b2180(out, (uint64_t *)local_138, d3, 0);
            if (uVar30 != 0) {
                sk_out_str(P1P8, s_of_type_005d7e66, 9);
                bVar17 = SUBT(n);
                if (bVar17 == 2) {
                    uVar13 = 2;
LAB_003b4694:
                    if (uVar30 < uVar13) {
                        if (1 < bVar17 - 1) n = (uint64_t *)*n;
                        n = (uint64_t *)n[uVar30];
                        goto LAB_003b3da8;
                    }
                } else if (bVar17 == 5) {
                    uVar13 = (uint64_t)(uint32_t)n[1];
                    goto LAB_003b4694;
                }
                n = (uint64_t *)0x0;
                goto LAB_003b3da8;
            }
        }
        goto LAB_003b4870;
    case 0x154:
        uVar23 = (uint32_t)n[1];
        if (uVar23 == 0) {
            lVar27 = -4;
            if ((short)sk_tb_ncmds != 0x2c) lVar27 = -3;
        } else {
            lVar27 = -4;
            if (*(short *)(*(uint64_t *)(*n + (uint64_t)uVar23 * 8 + -8) + 0x10) != 0x2c) lVar27 = -3;
            lVar27 = lVar27 + (uint64_t)uVar23;
        }
        uVar23 = **(uint8_t **)(*n + lVar27 * 8) - 100;
        uVar23 = uVar23 >> 1 & 0x7f | uVar23 * 0x80 & 0xff;
        if (uVar23 < 4) {
            if (uVar23 == 0) {
                pcVar10 = s_normal_005d7ed0;
LAB_003b40cc:
                uVar32 = 6;
            } else {
                if (uVar23 != 1) goto LAB_003b40d8;
                pcVar10 = s_forward_mode_005d7eb6;
LAB_003b3a20:
                uVar32 = 0xc;
            }
            sk_out_str(P1P8, pcVar10, uVar32);
        } else {
            if (uVar23 == 4) { pcVar10 = s_linear_005d7ed7; goto LAB_003b40cc; }
            if (uVar23 == 7) { pcVar10 = s_reverse_mode_005d7ec3; goto LAB_003b3a20; }
        }
LAB_003b40d8:
        sk_out_str(P1P8, s_differentiability_witness_for_005d7ede, 0x1f);
        bVar17 = SUBT(n);
        uVar13 = (uint64_t)bVar17;
        if (bVar17 == 1) {
LAB_003b4118:
            uVar30 = 0;
            do {
                bVar17 = SUBT(n);
                uVar33 = (uint64_t)bVar17;
                bVar8 = 1 < bVar17 - 1;
                puVar21 = n;
                if (bVar8) puVar21 = (uint64_t *)*n;
                uVar28 = uVar30;
                if (*(short *)(puVar21[uVar30] + 0x10) == 0x68) break;
                if (bVar17 == 1) {
LAB_003b4174:
                    if (uVar33 <= uVar30) goto LAB_003b4190;
                    puVar21 = n;
                    if (bVar8) puVar21 = (uint64_t *)*n;
                    uVar33 = puVar21[uVar30];
                } else {
                    if (bVar17 == 5) { uVar33 = (uint64_t)(uint32_t)n[1]; goto LAB_003b4174; }
                    if (bVar17 == 2) { uVar33 = 2; goto LAB_003b4174; }
LAB_003b4190:
                    uVar33 = 0;
                }
                sk_003b2180(out, (uint64_t *)uVar33, (uint64_t)(iVar19 + 1), 0);
                uVar30 = uVar30 + 1;
                uVar28 = uVar13;
            } while (uVar13 != uVar30);
        } else {
            if (bVar17 == 5) {
                uVar13 = (uint64_t)(uint32_t)n[1];
                if ((uint32_t)n[1] != 0) goto LAB_003b4118;
            } else if (bVar17 == 2) {
                uVar13 = 2;
                goto LAB_003b4118;
            }
            uVar28 = 0;
        }
        sk_out_str(P1P8, s_with_respect_to_parameters_005d7dcb, 0x1c);
        bVar17 = SUBT(n);
        uVar13 = (uint64_t)bVar17;
        uVar23 = (uint32_t)bVar17;
        iVar35 = (int32_t)uVar28;
        if (uVar23 == 1) {
LAB_003b41f8:
            if (uVar13 <= iVar35 + 1) goto LAB_003b421c;
            puVar21 = n;
            if (1 < uVar23 - 1) puVar21 = (uint64_t *)*n;
            uVar13 = puVar21[iVar35 + 1];
        } else {
            if (uVar23 == 5) { uVar13 = (uint64_t)(uint32_t)n[1]; goto LAB_003b41f8; }
            if (bVar17 == 2) { uVar13 = 2; goto LAB_003b41f8; }
LAB_003b421c:
            uVar13 = 0;
        }
        d3 = (uint64_t)(iVar19 + 1);
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        sk_out_str(P1P8, s_and_results_005d7de8, 0xd);
        bVar17 = SUBT(n);
        uVar13 = (uint64_t)bVar17;
        uVar23 = (uint32_t)bVar17;
        if (uVar23 == 1) {
LAB_003b4270:
            if (uVar13 <= iVar35 + 2) goto LAB_003b4294;
            puVar21 = n;
            if (1 < uVar23 - 1) puVar21 = (uint64_t *)*n;
            uVar13 = puVar21[iVar35 + 2];
        } else {
            if (uVar23 == 5) { uVar13 = (uint64_t)(uint32_t)n[1]; goto LAB_003b4270; }
            if (bVar17 == 2) { uVar13 = 2; goto LAB_003b4270; }
LAB_003b4294:
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, d3, 0);
        bVar17 = SUBT(n);
        uVar13 = (uint64_t)bVar17;
        uVar23 = (uint32_t)bVar17;
        if (bVar17 == 1) uVar30 = 1;
        else if (bVar17 == 5) uVar30 = (uint64_t)(uint32_t)n[1];
        else {
            if (uVar23 != 2) goto LAB_003b4870;
            uVar30 = 2;
        }
        uVar33 = (uint64_t)(iVar35 + 3);
        if (uVar33 < uVar30) {
            if (uVar23 == 1) {
LAB_003b4308:
                if (uVar13 <= uVar33) goto LAB_003b4324;
                if (1 < uVar23 - 1) n = (uint64_t *)*n;
                puVar21 = (uint64_t *)n[uVar33];
            } else {
                if (uVar23 == 5) { uVar13 = (uint64_t)(uint32_t)n[1]; goto LAB_003b4308; }
                if (uVar23 == 2) { uVar13 = 2; goto LAB_003b4308; }
LAB_003b4324:
                puVar21 = (uint64_t *)0x0;
            }
LAB_003b43c8:
            pcVar10 = s_with_005d7844;
            uVar32 = 6;
LAB_003b4760:
            sk_out_str(P1P8, pcVar10, uVar32);
            n = puVar21;
            goto LAB_003b3da8;
        }
        goto LAB_003b4870;
    case 0x155:
        pcVar10 = s__noDerivative_005d76fe;
LAB_003b2c04:
        uVar32 = 0xe;
        goto LAB_003b6b14;
    case 0x156:
        sk_vec_byte_append(P1P8, 0x7b);
        uVar13 = n[1];
        if ((uint32_t)uVar13 != 0) {
            uVar30 = 0;
            bVar8 = false;
            uVar33 = *n;
            do {
                if (*(char *)(uVar33 + uVar30) == 'S') {
                    if (bVar8) sk_out_str(P1P8, (const char *)0x5d0c46, 2);
                    sk_003b1e74(P1P8, uVar30, 0);
                    bVar8 = true;
                }
                uVar30 = uVar30 + 1;
            } while ((uint32_t)uVar13 != uVar30);
        }
        uVar32 = 0x7d;
        goto LAB_003b8480;
    case 0x157:
        if (*(char *)((long)out + 0x34) == '\x01') {
            sk_out_str(P1P8, (const char *)0x5d3bb7, 1);
            if (SUBT(n) - 1 < 2) {
LAB_003b5d6c:
                uVar13 = *n;
            } else {
                if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                    n = (uint64_t *)*n;
                    goto LAB_003b5d6c;
                }
                uVar13 = 0;
            }
            sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
            sk_out_str(P1P8, (const char *)0x5ce788, 1);
            pcVar10 = s_await_resume_partial_function_fo_005d8ea4;
            uVar32 = 0x23;
            goto LAB_003b7924;
        }
        goto LAB_003b4870;
    case 0x158:
        if (*(char *)((long)out + 0x34) != '\x01') goto LAB_003b4870;
        sk_out_str(P1P8, (const char *)0x5d3bb7, 1);
        if (SUBT(n) - 1 < 2) {
LAB_003b5cc0:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b5cc0;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_out_str(P1P8, (const char *)0x5ce788, 1);
        pcVar10 = s_suspend_resume_partial_function_f_005d8ec8;
        uVar32 = 0x25;
LAB_003b7924:
        sk_out_str(P1P8, pcVar10, uVar32);
LAB_003b7928:
        if (!bVar7) unaff_x25 = 0;
        goto LAB_003b487c;
    case 0x159:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) != 0) goto LAB_003b4870;
        pcVar10 = s_accessible_function_runtime_reco_005d7f70;
        out = out + 1;
        uVar13 = 0x27;
        goto LAB_003b486c;
    case 0x15a:
        pcVar10 = s__const_005d76db;
        goto LAB_003b30bc;
    case 0x15b:
        if ((*(uint8_t *)((long)out + 0x2b) & 1) != 0) goto LAB_003b4870;
        pcVar10 = s_back_deployment_thunk_for_005d8002;
LAB_003b601c:
        out = out + 1;
        uVar13 = 0x1a;
        goto LAB_003b486c;
    case 0x15c:
        pcVar10 = s_back_deployment_fallback_for_005d801d;
        out = out + 1;
        uVar13 = 0x1d;
        goto LAB_003b486c;
    case 0x15d:
        uVar3 = *(uint8_t *)((long)out + 0x27);
        *(uint8_t *)((long)out + 0x27) = 1;
        if (SUBT(n) == 2) {
LAB_003b5e34:
            uVar13 = n[1];
            sk_out_str(P1P8, s_existential_shape_for_005d8ef9, 0x16);
            uVar32 = 0;
            if (uVar13 != 0) {
                sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
                sk_out_str(P1P8, (const char *)0x5d021c, 1);
                uVar32 = 0;
            }
        } else {
            if (SUBT(n) == 5) {
                if ((uint32_t)n[1] == 2) { n = (uint64_t *)*n; goto LAB_003b5e34; }
                if ((uint32_t)n[1] < 2) goto LAB_003b80e4;
                uVar32 = *(uint64_t *)(*n + 8);
            } else {
LAB_003b80e4:
                uVar32 = 0;
            }
            sk_out_str(P1P8, s_existential_shape_for_005d8ef9, 0x16);
        }
        sk_out_str(P1P8, (const char *)0x5d8600, 4);
        sk_003b2180(out, (uint64_t *)uVar32, (uint64_t)(iVar19 + 1), 0);
        *(uint8_t *)((long)out + 0x27) = uVar3;
        goto LAB_003b7928;
    case 0x15e:
        pcVar10 = s_uniquable_005d8eee;
        uVar32 = 10;
        goto LAB_003b6b14;
    case 0x15f:
        pcVar10 = s_unique_existential_shape_symboli_005d8f10;
        uVar32 = 0x2e;
        goto LAB_003b6914;
    case 0x160:
        pcVar10 = s_non_unique_existential_shape_sym_005d8f3f;
        uVar32 = 0x32;
        goto LAB_003b6914;
    case 0x161:
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b5bb0:
            puVar31 = (uint64_t *)*puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b5bb0;
            }
            puVar31 = (uint64_t *)0x0;
        }
        sVar4 = *(short *)(puVar31 + 2);
        sk_out_str(P1P8, s_symbolic_existential_type___005d8f9d, 0x1b);
        puVar14ptr = (const char *)0x5be7c0;
        if (sVar4 != 0x15f) puVar14ptr = (const char *)0x5d8fb9;
        uVar32 = 0;
        if (sVar4 != 0x15f) uVar32 = 4;
        sk_out_str(P1P8, (const char *)puVar14ptr, uVar32);
        sk_out_str(P1P8, s_unique__0x_005d8fbe, 10);
        sk_003b1f20(P1P8, *puVar31, 0);
        sk_out_str(P1P8, (const char *)0x5d5321, 2);
        puVar21 = n;
        if (SUBT(n) == 2) {
LAB_003b773c:
            uVar13 = puVar21[1];
        } else {
            if ((SUBT(n) == 5) && (1 < (uint32_t)n[1])) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b773c;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        if ((SUBT(n) == 5) && (2 < (uint32_t)n[1])) {
            sk_out_str(P1P8, (const char *)0x5d0c46, 2);
            uVar32 = (SUBT(n) == 5 && (2 < (uint32_t)n[1])) ? *(uint64_t *)(*n + 0x10) : 0;
            sk_003b2180(out, (uint64_t *)uVar32, (uint64_t)(iVar19 + 1), 0);
        }
LAB_003b7fa8:
        pcVar10 = (const char *)0x5cf438;
        goto LAB_003b7fb0;
    case 0x162:
        sk_out_str(P1P8, s_param_005d7835, 5);
        sk_003b1e74(P1P8, *n, 0);
        pcVar10 = s__removed_005d783b;
LAB_003b7f44:
        out = out + 1;
        uVar13 = 8;
        goto LAB_003b486c;
    case 0x163:
        pcVar10 = s___hasSymbol_query_for_005d8fc9;
LAB_003b61bc:
        out = out + 1;
        uVar13 = 0x16;
        goto LAB_003b486c;
    case 0x166:
        pcVar10 = s_outlined_enum_tag_store_of_005d73cb;
LAB_003b32f0:
        uVar32 = 0x1b;
        goto LAB_003b6b14;
    case 0x167:
        pcVar10 = s_outlined_enum_project_data_for_l_005d73a3;
LAB_003b320c:
        uVar32 = 0x27;
        goto LAB_003b6b14;
    case 0x168:
        pcVar10 = s_outlined_enum_get_tag_of_005d73e7;
        uVar32 = 0x19;
        goto LAB_003b6b14;
    case 0x169:
        pcVar10 = s_async_demotion_of_005d71c8;
LAB_003b2f00:
        uVar32 = 0x12;
        goto LAB_003b6b14;
    case 0x16a:
        pcVar10 = s_representation_changed_of_005d7167;
        uVar32 = 0x1a;
        goto LAB_003b6b14;
    case 0x16b:
        pcVar10 = s_objective_c_protocol_symbolic_re_005d8f72;
        uVar32 = 0x2a;
LAB_003b6914:
        sk_out_str(P1P8, pcVar10, uVar32);
LAB_003b6918:
        sk_003b1f20(P1P8, *n, 0);
        goto LAB_003b4870;
    case 0x171:
        puVar21 = n;
        if (SUBT(n) - 1 < 2) {
LAB_003b5c44:
            uVar13 = *puVar21;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                puVar21 = (uint64_t *)*n;
                goto LAB_003b5c44;
            }
            uVar13 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar13, (uint64_t)(iVar19 + 1), 0);
        sk_out_str(P1P8, (const char *)0x5d8882, 3);
        puVar21 = n;
        if (SUBT(n) == 5) puVar21 = (uint64_t *)*n;
        if (*(long *)puVar21[1] != 1) {
            if (*(long *)puVar21[1] == 0) {
                sk_out_str(P1P8, s_Swift__005d8886, 6);
                pcVar10 = s_Copyable_005d888d;
                goto LAB_003b7f44;
            }
            sk_out_str(P1P8, s_Swift_bit_005d88a0, 0xb);
            if (SUBT(n) == 5) n = (uint64_t *)*n;
            sk_003b1e74(P1P8, *(uint64_t *)n[1], 0);
            goto LAB_003b7fa8;
        }
        sk_out_str(P1P8, s_Swift__005d8886, 6);
        pcVar10 = s_Escapable_005d8896;
LAB_003b80bc:
        out = out + 1;
        uVar13 = 9;
        goto LAB_003b486c;
    case 0x173:
        sk_003b1f98(P1P8, *n, 0);
        goto LAB_003b4870;
    case 0x175:
        pcVar10 = s_coro_function_pointer_to_005d8fe0;
LAB_003b69b4:
        out = out + 1;
        uVar13 = 0x19;
        goto LAB_003b486c;
    case 0x176:
        pcVar10 = s_default_override_of_005d8ffa;
LAB_003b5c54:
        out = out + 1;
        uVar13 = 0x14;
        goto LAB_003b486c;
    case 0x177:
        pcVar10 = s__const_005d76e3;
LAB_003b30bc:
        uVar32 = 7;
        goto LAB_003b6b14;
    case 0x178:
        if (SUBT(n) - 1 < 2) {
LAB_003b5b28:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b5b28;
            }
            uVar13 = 0;
        }
        pcVar10 = s_borrow_005d8716;
        goto LAB_003b7a10;
    case 0x179:
        if (SUBT(n) - 1 < 2) {
LAB_003b5a1c:
            uVar13 = *n;
        } else {
            if ((SUBT(n) == 5) && ((int32_t)n[1] != 0)) {
                n = (uint64_t *)*n;
                goto LAB_003b5a1c;
            }
            uVar13 = 0;
        }
        pcVar10 = s_mutate_005d871d;
LAB_003b7a10:
        uVar32 = 6;
LAB_003b7a20:
        uVar32 = FUN_003bccf8(out, uVar13, d3, flag & 1, pcVar10, uVar32);
        goto caseD4;
    }
    /* fall-through after switch (reached by LAB_003b3960 etc. goto targets) */
    goto LAB_003b4870;

caseD21:
    bVar17 = SUBT(n);
LAB_003b3300:
    uVar18 = (uint32_t)bVar17;
    uVar23 = uVar18 - 1;
LAB_003b3304:
    if (uVar23 < 2) {
LAB_003b3320:
        puVar21 = (uint64_t *)*n;
    } else {
        if (uVar18 == 5) {
LAB_003b3314:
            if ((int32_t)n[1] != 0) {
LAB_003b331c:
                n = (uint64_t *)*n;
                goto LAB_003b3320;
            }
        }
LAB_003b3da0:
        puVar21 = (uint64_t *)0x0;
    }
LAB_003b3da4:
    d3 = (uint64_t)(iVar19 + 1);
    n = puVar21;
LAB_003b3da8:
    flag = 0;
    if (!bVar7) unaff_x25 = 0;
    bVar7 = true;
    if (0x300 < (uint32_t)d3) goto LAB_003b483c;
    goto LAB_003b21dc;
LAB_003b8198:
    sk_lock((void *)local_130[0], uVar13 & 0x7fffffffffffffff);
    goto LAB_003b4870;
LAB_003b7e50:
    do {
        if (uVar13 != 0) sk_out_str(P1P8, (const char *)0x5d0c46, 2);
        bVar17 = SUBT(n);
        uVar30 = (uint64_t)bVar17;
        uVar23 = (uint32_t)bVar17;
        if (uVar23 == 1) {
LAB_003b7e8c:
            if (uVar30 <= uVar13) goto LAB_003b7eac;
            puVar21 = n;
            if (1 < uVar23 - 1) puVar21 = (uint64_t *)*n;
            uVar30 = puVar21[uVar13];
        } else {
            if (uVar23 == 5) { uVar30 = (uint64_t)(uint32_t)n[1]; goto LAB_003b7e8c; }
            if (bVar17 == 2) { uVar30 = 2; goto LAB_003b7e8c; }
LAB_003b7eac:
            uVar30 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar30, (uint64_t)(iVar19 + 1), 0);
        uVar13 = uVar13 + 1;
    } while (uVar20 != uVar13);
LAB_003b8478:
    uVar32 = 0x29;
    goto LAB_003b8480;
LAB_003b63dc:
    bVar17 = SUBT(n);
    uVar30 = (uint64_t)bVar17;
    if (bVar17 != 1) {
        if (bVar17 == 5) uVar30 = (uint64_t)(uint32_t)n[1];
        else { if (bVar17 != 2) goto LAB_003b648c; uVar30 = 2; }
    }
    if (uVar30 <= uVar13) goto LAB_003b648c;
    if (uVar13 != 0) sk_vec_byte_append(P1P8, 0x2c);
    sk_vec_byte_append(P1P8, 0x20);
    bVar17 = SUBT(n);
    uVar30 = (uint64_t)bVar17;
    uVar20 = (uint32_t)bVar17;
    if (uVar20 == 1) {
LAB_003b6450:
        if (uVar30 <= uVar13) goto LAB_003b6470;
        puVar21 = n;
        if (1 < uVar20 - 1) puVar21 = (uint64_t *)*n;
        uVar30 = puVar21[uVar13];
    } else {
        if (uVar20 == 5) { uVar30 = (uint64_t)(uint32_t)n[1]; goto LAB_003b6450; }
        if (bVar17 == 2) { uVar30 = 2; goto LAB_003b6450; }
LAB_003b6470:
        uVar30 = 0;
    }
    sk_003b2180(out, (uint64_t *)uVar30, (uint64_t)(iVar19 + 1), 0);
    uVar13 = uVar13 + 1;
    goto LAB_003b63dc;
LAB_003b648c:
    pcVar10 = (const char *)0x5d8a3a;
LAB_003b6494:
    out = out + 1;
    uVar13 = 2;
    goto LAB_003b486c;
LAB_003b84a0:
    do {
        if (uVar13 != 0) sk_out_str(P1P8, (const char *)0x5d0c46, 2);
        bVar17 = SUBT(puVar31);
        uVar30 = (uint64_t)bVar17;
        uVar23 = (uint32_t)bVar17;
        if (uVar23 == 1) {
LAB_003b84dc:
            if (uVar30 <= uVar13) goto LAB_003b84fc;
            puVar24 = puVar31;
            if (1 < uVar23 - 1) puVar24 = (uint64_t *)*puVar31;
            uVar32 = puVar24[uVar13];
        } else {
            if (uVar23 == 5) { uVar30 = (uint64_t)*(uint32_t *)(puVar31 + 1); goto LAB_003b84dc; }
            if (bVar17 == 2) { uVar30 = 2; goto LAB_003b84dc; }
LAB_003b84fc:
            uVar32 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar32, (uint64_t)(iVar19 + 1), 0);
        uVar13 = uVar13 + 1;
    } while (uVar20 != uVar13);
LAB_003b7564:
    uVar32 = 0x3e;
LAB_003b8480:
    sk_vec_byte_append(P1P8, uVar32);
    goto LAB_003b4870;
LAB_003b5780:
    bVar17 = SUBT(n);
    if (bVar17 == 2) uVar30 = 2;
    else {
        if (bVar17 != 5) goto LAB_003b4870;
        uVar30 = (uint64_t)(uint32_t)n[1];
    }
    if (uVar30 <= uVar13) goto LAB_003b4870;
    puVar21 = n;
    if (bVar17 == 5) puVar21 = (uint64_t *)*n;
    uVar30 = puVar21[uVar13];
    if (*(short *)(uVar30 + 0x10) == 0xe5) sk_out_str(P1P8, (const char *)0x5d0c46, 2);
    sk_003b2180(out, (uint64_t *)uVar30, (uint64_t)(iVar19 + 1), 0);
    uVar13 = uVar13 + 1;
    goto LAB_003b5780;
LAB_003b7a98:
    do {
        if (uVar13 == 1) { uVar32 = 6; pcVar10 = s_with_005d7844; }
        else { uVar32 = 5; pcVar10 = s_and_005d784b; }
        sk_out_str(P1P8, pcVar10, uVar32);
        bVar17 = SUBT(n);
        if (bVar17 == 2) {
            uVar30 = 2;
LAB_003b7adc:
            if (uVar30 <= uVar13) goto LAB_003b7b00;
            puVar21 = n;
            if (1 < bVar17 - 1) puVar21 = (uint64_t *)*n;
            uVar30 = puVar21[uVar13];
        } else {
            if (bVar17 == 5) { uVar30 = (uint64_t)(uint32_t)n[1]; goto LAB_003b7adc; }
LAB_003b7b00:
            uVar30 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar30, (uint64_t)(iVar19 + 1), 0);
        uVar13 = uVar13 + 1;
    } while (uVar20 != uVar13);
    goto LAB_003b4870;
LAB_003b4c60:
    bVar17 = SUBT(n);
    if (bVar17 == 1) uVar30 = 1;
    else if (bVar17 == 5) uVar30 = (uint64_t)(uint32_t)n[1];
    else { if (bVar17 != 2) goto LAB_003b72a0; uVar30 = 2; }
    if (uVar30 <= uVar13) goto LAB_003b72a0;
    if (uVar13 != 0) {
        sk_out_str(P1P8, (const char *)0x5d0c46, 2);
        bVar17 = SUBT(n);
    }
    uVar30 = (uint64_t)bVar17;
    uVar20 = (uint32_t)bVar17;
    if (uVar20 == 1) {
LAB_003b4cdc:
        if (uVar30 <= uVar13) goto LAB_003b4d00;
        puVar21 = n;
        if (1 < uVar20 - 1) puVar21 = (uint64_t *)*n;
        uVar30 = puVar21[uVar13];
    } else {
        if (uVar20 == 5) { uVar30 = (uint64_t)(uint32_t)n[1]; goto LAB_003b4cdc; }
        if (uVar20 == 2) { uVar30 = 2; goto LAB_003b4cdc; }
LAB_003b4d00:
        uVar30 = 0;
    }
    sk_003b2180(out, (uint64_t *)uVar30, (uint64_t)(iVar19 + 1), 0);
    uVar13 = uVar13 + 1;
    goto LAB_003b4c60;
LAB_003b7224:
    do {
        if (uVar13 != 0) sk_out_str(P1P8, (const char *)0x5d0c46, 2);
        bVar17 = SUBT(n);
        uVar30 = (uint64_t)bVar17;
        uVar23 = (uint32_t)bVar17;
        if (uVar23 == 1) {
LAB_003b7260:
            if (uVar30 <= uVar13) goto LAB_003b7280;
            puVar21 = n;
            if (1 < uVar23 - 1) puVar21 = (uint64_t *)*n;
            uVar30 = puVar21[uVar13];
        } else {
            if (uVar23 == 5) { uVar30 = (uint64_t)(uint32_t)n[1]; goto LAB_003b7260; }
            if (bVar17 == 2) { uVar30 = 2; goto LAB_003b7260; }
LAB_003b7280:
            uVar30 = 0;
        }
        sk_003b2180(out, (uint64_t *)uVar30, (uint64_t)(iVar19 + 1), 0);
        uVar13 = uVar13 + 1;
    } while (uVar20 != uVar13);
LAB_003b72a0:
    pcVar10 = (const char *)0x5ce788;
LAB_003b7fb0:
    out = out + 1;
LAB_003b7fb4:
    uVar13 = 1;
LAB_003b486c:
    sk_out_str(out, pcVar10, uVar13);
LAB_003b4870:
    uVar32 = 0;
caseD4:
    if (!bVar7) unaff_x25 = uVar32;
LAB_003b487c:
    if (canary == (uint64_t)-0x2c8502b44bfffed6) return;
    sk_canary_panic();
}

static void sk_003b8d18(uint64_t * st, uint64_t * p2, uint64_t p3, uint64_t p4); /* FUN_003b8d18 */
static void sk_003b8d94(uint64_t * st, uint64_t * p2, uint64_t p3); /* FUN_003b8d94 */
static void sk_003b8e48(uint64_t * st, uint64_t p2); /* FUN_003b8e48 */
static uint8_t sk_003b8ef8(uint64_t * st, uint64_t * p2); /* FUN_003b8ef8 */
static uint64_t sk_003b903c(uint64_t a, uint64_t *b); /* FUN_003b903c */
static void sk_003b9794(uint64_t * st, uint64_t p2, int32_t p3); /* FUN_003b9794 */
static uint64_t sk_003b982c(uint64_t * st, uint64_t * p2); /* FUN_003b982c */
static bool sk_003b9c14(uint64_t *a, uint64_t b, uint64_t c); /* FUN_003b9c14 */
static bool sk_003b9c6c(uint64_t *a); /* FUN_003b9c6c */
static void sk_003b9cb4(uint64_t * st, uint64_t * p2, uint64_t p3); /* FUN_003b9cb4 */
static uint64_t sk_003ba044(uint64_t * st, uint64_t * p2, uint32_t p3); /* FUN_003ba044 */
static void sk_003ba114(uint64_t * st, uint64_t p2, uint64_t * p3, int32_t p4, int32_t p5); /* FUN_003ba114 */
static void sk_003ba390(uint64_t *a, uint64_t b, uint64_t *c, uint64_t d); /* FUN_003ba390 */

/* ===== BODIES ===== */
/* FUN_003ac2d0 @ 0x3ac2d0   (est. sk_make_range)
 * Builds a 0x27 node with two 0x68 scalar children (p2, p3); returns NULL if
 * either is negative (sign bit set).
 * Confidence: high */
static uint64_t sk_003ac2d0(uint64_t *st, uint32_t p2, uint32_t p3)
{
    if ((int32_t)(p3 | p2) < 0) return 0;
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0x27); NODE_SETSUBT(node, 0);
    uint64_t *a = sk_node_alloc(st, 1);
    NODE_SETTAG(a, 0x68); NODE_SETSUBT(a, 4);
    a[0] = p2;
    sk_node_add(node, a, st);
    uint64_t *b = sk_node_alloc(st, 1);
    NODE_SETTAG(b, 0x68); NODE_SETSUBT(b, 4);
    b[0] = p3;
    sk_node_add(node, b, st);
    return (uint64_t)node;
}

/* FUN_003ac394 @ 0x3ac394   (est. sk_parse_n)
 * Reads an optional 'n' prefix and an '_N_' identifier; emits a scalar node
 * (tag 0x173 if prefixed, 0x172 otherwise, sub 4) holding the negated value,
 * pushed as 0xf4.
 * Confidence: medium */
static void sk_003ac394(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    int32_t v;
    uint16_t tag;
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'n') {
        STREAM_POS(st) = pos + 1;
        v = -sk_003ac4a4(st);
        tag = 0x173;
    } else {
        v = sk_003ac4a4(st);
        tag = 0x172;
    }
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, tag); NODE_SETSUBT(n, 4);
    n[0] = (uint64_t)v;
    sk_node_push(st, 0xf4, n);
}

/* FUN_003ac430 @ 0x3ac430   (est. sk_read_digits)
 * Reads a run of ASCII decimal digits at the current stream position;
 * returns the accumulated integer, or -1000 on overflow/no digits.
 * Confidence: high */
static int32_t sk_003ac430(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    int32_t acc = 0;
    if (pos < STREAM_END(st)) {
        uint8_t c = STREAM_DATA(st)[pos];
        if (c - 0x30 < 10) {
            do {
                uint8_t d = STREAM_DATA(st)[pos];
                if (9 < d - 0x30) return acc;
                int32_t nv = d + acc * 10 - 0x30;
                if (nv < acc) return -1000;      /* overflow */
                pos += 1; STREAM_POS(st) = pos;
                acc = nv;
            } while (STREAM_END(st) != pos);
            return acc;
        }
    }
    return -1000;
}

/* FUN_003ac4a4 @ 0x3ac4a4   (est. sk_read_ident)
 * Reads a '_..._' identifier: bare '_' returns 0; '_N_' returns N+1; else
 * -1000. Consumes the trailing '_'.
 * Confidence: high */
static int32_t sk_003ac4a4(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == '_') {
        STREAM_POS(st) = pos + 1;
        return 0;
    }
    int32_t v = sk_003ac430(st);
    if (v < 0) return v;
    pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos || STREAM_DATA(st)[pos] != '_') return -1000;
    STREAM_POS(st) = pos + 1;
    return v + 1;
}

/* FUN_003ac52c @ 0x3ac52c   (est. sk_parse_ab)
 * Parses an '_N_' identifier into a scalar node (tag 0xab, sub 4), or NULL.
 * Confidence: high */
static uint64_t *sk_003ac52c(uint64_t *st)
{
    int32_t v = sk_003ac4a4(st);
    if (v < 0) return NULL;
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, 0xab); NODE_SETSUBT(n, 4);
    n[0] = (uint64_t)v;
    return n;
}

/* FUN_003ac580 @ 0x3ac580   (est. sk_build_children)
 * Reads a result pointer from the stream's result buffer (+0x68) at index
 * p3 (bounds-checked vs +0x70 count, p2 < 0x801), then pushes it onto the
 * value stack (p2-1) times. Returns the result pointer.
 * Confidence: medium */
static uint64_t sk_003ac580(uint64_t *st, int32_t p2, uint64_t p3)
{
    uint64_t v = 0;
    if (p2 < 0x801 && p3 < *(uint32_t *)((char *)st + 0x70)) {
        uint64_t *rbuf = *(uint64_t **)((char *)st + 0x68);
        v = rbuf[p3];
        if (1 < p2) {
            uint32_t k = p2 + 1;
            do {
                uint64_t *slot = &v;
                sk_003ad810(st + 11, slot, st);
                k = k - 1;
            } while (2 < k);
        }
    }
    return v;
}

/* FUN_003ac600 @ 0x3ac600   (est. sk_err_ab)
 * Builds an error node: allocates a 5-byte "Swift" magic buffer, wraps it in
 * an 0xa3 string node, calls sk_node_make(st,0x67,p3) for the message and
 * sk_node_push2(st,p2,...), then pushes the result as 0xf4.
 * Confidence: medium */
static uint64_t sk_003ac600(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint32_t *magic = (uint32_t *)sk_alloc_scalar(st, 5);
    magic[0] = 0x66697753;
    *(uint8_t *)(magic + 1) = 0x74;
    uint64_t *s = sk_node_alloc(st, 1);
    NODE_SETTAG(s, 0xa3); NODE_SETSUBT(s, 3);
    s[0] = (uint64_t)magic; s[1] = 5;
    uint64_t *msg = sk_node_make(st, 0x67, (void *)p3);
    uint64_t *r = sk_node_push2(st, (int)p2, s, msg);
    return (uint64_t)sk_node_push(st, 0xf4, r);
}

/* FUN_003acd3c @ 0x3acd3c   (est. sk_buf_byte)
 * Appends a byte to a growing byte buffer (buf[0]=ptr, [1]=count, +0xc=cap).
 * Confidence: high */
static void sk_003acd3c(uint64_t *buf, uint8_t *p, uint64_t *st)
{
    uint32_t cnt = *(uint32_t *)(buf + 1);
    if (*(uint32_t *)((char *)buf + 0xc) <= cnt) {
        sk_grow_buf(st, buf, (uint32_t *)((char *)buf + 0xc), 1);
        cnt = *(uint32_t *)(buf + 1);
    }
    uint8_t b = *p;
    *(uint32_t *)(buf + 1) = cnt + 1;
    *(uint8_t *)(buf[0] + cnt) = b;
}

/* FUN_003acda0 @ 0x3acda0   (est. sk_is_printable)
 * Returns true when the tag is in the printable/scalar set.
 * Confidence: medium */
static bool sk_003acda0(int32_t tag)
{
    uint32_t u = (uint32_t)(tag - 0xb7);
    if (!(0x3e < u || ((1ULL << (u & 0x3f)) & 0x400000040000020dULL) == 0)) return true;
    u = (uint32_t)(tag - 0x67);
    if (!(0x2b < u || ((1ULL << (u & 0x3f)) & 0x80004000001ULL) == 0)) return true;
    return tag == 0x16b;
}

/* FUN_003ace08 @ 0x3ace08   (est. sk_pop_a3)
 * Pops the top element: returns it if tag 0xa3, or converts a 0x67 element to
 * 0xa3 (sk_tag_convert) and returns it; else returns 0.
 * Confidence: medium */
static uint64_t sk_003ace08(uint64_t *st)
{
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xa3) { STACK_CNT(st) = i; return (uint64_t)e; }
        if (NODE_TAG(e) == 0x67) {
            STACK_CNT(st) = i;
            uint64_t *r = sk_tag_convert(st, e, 0xa3);
            return (uint64_t)r;
        }
    }
    return 0;
}

/* FUN_003ace50 @ 0x3ace50   (est. sk_pop_f4)
 * Pops a compound (0xf4) element: if it wraps a single 0x67 scalar or a
 * 5-subtype chain whose inner element is a printable leaf, returns the inner
 * leaf; else returns 0. Also accepts a printable non-0xf4 element directly.
 * Confidence: medium */
static uint64_t *sk_003ace50(uint64_t *st)
{
    uint64_t *e = (uint64_t *)sk_003ace08(st);
    if (e) return e;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) {
            STACK_CNT(st) = i;
            uint8_t sub = NODE_SUBT(e);
            if (sub != 1) {
                if (sub != 5) return NULL;
                if ((int32_t)e[1] != 1) return NULL;
                e = (uint64_t *)NODE_DATA(e);
            }
            e = (uint64_t *)NODE_DATA(e);
            if (!sk_003acf38(NODE_TAG(e))) return NULL;
            return e;
        }
        if (sk_003acf38(NODE_TAG(e)) != 0) {
            STACK_CNT(st) = i;
            return e;
        }
    }
    return NULL;
}

/* FUN_003acf38 @ 0x3acf38   (est. sk_tag_is_leaf)
 * Returns 1 when the tag denotes a leaf scalar (no children), else 0.
 * Confidence: medium */
static uint64_t sk_003acf38(uint32_t tag)
{
    if ((int32_t)tag < 0xbf) {
        if (tag < 0x40 && ((1ULL << (tag & 0x3f)) & 0x8000000002200000ULL) != 0) return 1;
        if (tag == 0xb1) return 1;
    } else if (((tag - 0xbf < 0x38) &&
                ((1ULL << ((tag - 0xbf) & 0x3f)) & 0xc0010000000003ULL) != 0) ||
               (tag == 0x16b)) {
        return 1;
    }
    return 0;
}

/* FUN_003acfb4 @ 0x3acfb4   (est. sk_write_bytes)
 * Serializes a value block (p2) with a tag into the output buffer via
 * FUN_003b0be0/FUN_003b0d64, returning the block pointer; locks on a negative
 * length. Returns 0 if either input is null.
 * Confidence: medium */
static uint64_t sk_003acfb4(uint64_t *st, uint64_t p2, uint64_t p3, uint8_t p4)
{
    if (p2 != 0 && p3 != 0) {
        uint64_t buf = 0, len = 0;
        uint8_t tag = p4;
        uint64_t result = p2;
        sk_write_data3(st, (void *)p3, (void *)sk_write_data4, &buf);
        if ((int64_t)len < 0) sk_lock((void *)buf, len & 0x7fffffffffffffffULL);
        return result;
    }
    return 0;
}

/* FUN_003ad048 @ 0x3ad048   (est. sk_parse_string_token)
 * Reads a decimal length (sk_003ac430); if >=1 and within the stream, copies
 * those bytes out (FUN_003a3a70), advances, returns a string node (tag 0x18,
 * sub 3) holding the copied bytes. NULL on empty/overflow.
 * Confidence: high */
static uint64_t *sk_003ad048(uint64_t *st)
{
    int32_t n = sk_003ac430(st);
    if (n < 1 || STREAM_END(st) < STREAM_POS(st) + (uint64_t)n) return NULL;
    uint64_t len = 0;
    uint64_t *data = sk_003a3a70(st, STREAM_DATA(st) + STREAM_POS(st), (uint64_t)n, &len);
    STREAM_POS(st) = STREAM_POS(st) + (uint64_t)n;
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0x18); NODE_SETSUBT(node, 3);
    node[0] = (uint64_t)data;
    node[1] = len & 0xffffffff;
    return node;
}

/* FUN_003ad0f0 @ 0x3ad0f0   (est. sk_emit_f4)
 * Pops the top element: 0xf4 kept as-is; 0x120 replaced by a fresh 0xeb node
 * pushed as 0xf4. Pushes the result under the given tag.
 * Confidence: medium */
static uint64_t sk_003ad0f0(uint64_t *st, uint64_t p2)
{
    uint64_t *v;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        v = STACK_ELEM(st, i);
        if (NODE_TAG(v) == 0xf4) { STACK_CNT(st) = i; goto emit; }
        if (NODE_TAG(v) == 0x120) {
            STACK_CNT(st) = i;
            uint64_t *n = sk_node_alloc(st, 1);
            NODE_SETTAG(n, 0xeb); NODE_SETSUBT(n, 0);
            v = sk_node_push(st, 0xf4, n);
            goto emit;
        }
    }
    v = 0;
emit:
    return (uint64_t)sk_node_push(st, (int)p2, v);
}

/* FUN_003ad188 @ 0x3ad188   (est. sk_parse_ee)
 * Builds an 0xee node; if the stack top is not a 0x120 terminator, drains
 * 0xf4 elements (bounded by a 0x121 terminator) as children; finalizes and
 * pushes as 0xf4. Returns the pushed node or 0 on malformed drain.
 * Confidence: medium */
static uint64_t sk_003ad188(uint64_t *st)
{
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0xee); NODE_SETSUBT(node, 0);
    uint32_t i = STACK_CNT(st);
    if (i == 0 || NODE_TAG(STACK_ELEM(st, i-1)) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_ELEM(st, j));
            if (term == 0x121) {
                STACK_CNT(st) = j;
                if (j == 0) return 0;
                cnt = STACK_CNT(st);
            }
            {
                uint64_t *e = STACK_ELEM(st, cnt-1);
                if (NODE_TAG(e) != 0xf4) return 0;
                STACK_CNT(st) = cnt - 1;
                sk_node_add(node, e, st);
            }
            if (term != 0x121) break;
        }
        sk_node_finalize(node, 0);
    }
    return (uint64_t)sk_node_push(st, 0xf4, node);
}

/* FUN_003ad278 @ 0x3ad278   (est. sk_parse_di)
 * Reads 'd'/'i' -> tag 0xef/0xf0; drains 0xf4 elements (bounded by 0x121)
 * into the node, finalizes, pushes as 0xf4.
 * Confidence: medium */
static uint64_t sk_003ad278(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    char c = STREAM_DATA(st)[pos];
    uint16_t tag;
    if (c == 'd') tag = 0xef;
    else if (c != 'i') return 0;
    else tag = 0xf0;
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, tag); NODE_SETSUBT(node, 0);
    uint32_t i = STACK_CNT(st);
    if (i == 0 || NODE_TAG(STACK_ELEM(st, i-1)) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_ELEM(st, j));
            if (term == 0x121) {
                STACK_CNT(st) = j;
                if (j == 0) return 0;
                cnt = STACK_CNT(st);
            }
            {
                uint64_t *e = STACK_ELEM(st, cnt-1);
                if (NODE_TAG(e) != 0xf4) return 0;
                STACK_CNT(st) = cnt - 1;
                sk_node_add(node, e, st);
            }
            if (term != 0x121) break;
        }
        sk_node_finalize(node, 0);
    }
    return (uint64_t)sk_node_push(st, 0xf4, node);
}

/* FUN_003ad3a0 @ 0x3ad3a0   (est. sk_parse_f7)
 * Builds an 0xf7 node; drains 0xf4 elements (bounded by 0x121); finalizes and
 * returns the node (no push).
 * Confidence: medium */
static uint64_t sk_003ad3a0(uint64_t *st)
{
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0xf7); NODE_SETSUBT(node, 0);
    uint32_t i = STACK_CNT(st);
    if (i == 0 || NODE_TAG(STACK_ELEM(st, i-1)) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_ELEM(st, j));
            if (term == 0x121) {
                STACK_CNT(st) = j;
                if (j == 0) return 0;
                cnt = STACK_CNT(st);
            }
            {
                uint64_t *e = STACK_ELEM(st, cnt-1);
                if (NODE_TAG(e) != 0xf4) return 0;
                STACK_CNT(st) = cnt - 1;
                sk_node_add(node, e, st);
            }
            if (term != 0x121) break;
        }
        sk_node_finalize(node, 0);
    }
    return (uint64_t)node;
}

/* FUN_003ad478 @ 0x3ad478   (est. sk_parse_pair2)
 * Builds a tag-2 node; drains elements with tags in {0x30..0x33,0x1c,0x1d}
 * bounded by 0x121; finalizes and returns the node.
 * Confidence: medium */
static uint64_t sk_003ad478(uint64_t *st)
{
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 2); NODE_SETSUBT(node, 0);
    uint32_t i = STACK_CNT(st);
    if (i == 0 || NODE_TAG(STACK_ELEM(st, i-1)) != 0x120) {
        int16_t term = 0;
        for (;;) {
            uint32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint32_t j = cnt - 1;
            term = NODE_TAG(STACK_ELEM(st, j));
            if (term == 0x121) {
                STACK_CNT(st) = j;
                if (j == 0) return 0;
                cnt = STACK_CNT(st);
            }
            {
                uint64_t *e = STACK_ELEM(st, cnt-1);
                uint32_t t = NODE_TAG(e);
                if ((3 < t - 0x30) && (1 < t - 0x1b)) return 0;
                STACK_CNT(st) = cnt - 1;
                sk_node_add(node, e, st);
            }
            if (term != 0x121) break;
        }
        sk_node_finalize(node, 0);
    }
    return (uint64_t)node;
}

/* FUN_003ad560 @ 0x3ad560   (est. sk_err_c4)
 * Reports error 0xc4 pairing sk_pop_a3 with sk_val_get(st).
 * Confidence: medium */
static void sk_003ad560(uint64_t *st)
{
    uint64_t *a = (uint64_t *)sk_003ace08(st);
    uint64_t v = sk_val_get(st);
    sk_node_push2(st, 0xc4, (uint64_t *)v, a);
}

/* FUN_003ad5a4 @ 0x3ad5a4   (est. sk_parse_ident_103)
 * Reads an '_N_' identifier: <1 -> NULL; ==1 -> bare 0x103 node; else an
 * 0x68 scalar holding (N-2).
 * Confidence: high */
static uint64_t *sk_003ad5a4(uint64_t *st)
{
    int32_t v = sk_003ac4a4(st);
    if (v < 1) return NULL;
    uint64_t *n = sk_node_alloc(st, 1);
    if (v == 1) {
        NODE_SETTAG(n, 0x103); NODE_SETSUBT(n, 0);
    } else {
        NODE_SETTAG(n, 0x68); NODE_SETSUBT(n, 4);
        n[0] = (uint64_t)(v - 2);
    }
    return n;
}

/* FUN_003ad67c @ 0x3ad67c   (est. sk_collect_da)
 * Pops consecutive 0xda elements from the stack into a new 0xf7 node;
 * finalizes and returns it (0 if none / non-0xda stops the run).
 * Confidence: medium */
static uint64_t sk_003ad67c(uint64_t *st)
{
    uint32_t cnt = STACK_CNT(st);
    uint64_t *node = 0;
    if (cnt == 0) return 0;
    do {
        uint64_t *e = STACK_TOP(st);
        if (NODE_TAG(e) != 0xda) { if (!node) return 0; break; }
        STACK_CNT(st) = cnt - 1;
        if (!node) { node = sk_node_alloc(st, 1); NODE_SETTAG(node, 0xf7); NODE_SETSUBT(node, 0); }
        sk_node_add(node, e, st);
        cnt = STACK_CNT(st);
    } while (cnt != 0);
    sk_node_finalize(node, 0);
    return (uint64_t)node;
}

/* FUN_003ad724 @ 0x3ad724   (est. sk_parse_value)
 * Parses one tagged value into the caller's scratch; creates a fresh 0xf7
 * node, records it into the result buffer, then pops 0xf4 elements off the
 * stack as children. Expects a trailing 0x120 (true) or 0x121 (false)
 * terminator; returns 1 on success (0x120) / 0 otherwise, looping on 0x121.
 * Confidence: medium */
static uint64_t sk_003ad724(uint64_t *st, uint64_t p2, uint64_t *p3)
{
    uint64_t *scratch = (uint64_t *)p2;
    uint64_t term;
    uint64_t *node;
    *p3 = 0;
    do {
        node = sk_node_alloc(st, 1);
        NODE_SETTAG(node, 0xf7); NODE_SETSUBT(node, 0);
        sk_003ad810(scratch, (uint64_t *)&node, st);
        while (true) {
            if (STACK_CNT(st) == 0) break;
            uint64_t *e = STACK_TOP(st);
            if (NODE_TAG(e) != 0xf4) break;
            STACK_CNT(st) = STACK_CNT(st) - 1;
            sk_node_add(node, e, st);
        }
        sk_node_finalize(node, 0);
        if (STACK_CNT(st) == 0) { term = 0; break; }
        {
            uint64_t *e = STACK_TOP(st);
            int16_t t = NODE_TAG(e);
            if (t == 0x121) { STACK_CNT(st) = STACK_CNT(st) - 1; continue; }
            if (t == 0x120) { STACK_CNT(st) = STACK_CNT(st) - 1; term = 1; break; }
            term = 0; break;
        }
    } while (true);
    return term;
}

/* FUN_003ad810 @ 0x3ad810   (est. sk_buf_push)
 * Appends one 64-bit word to a growing word buffer (buf[0]=ptr,[1]=cnt,+0xc=cap).
 * Confidence: high */
static void sk_003ad810(uint64_t *buf, uint64_t *p, uint64_t *st)
{
    uint32_t cnt = *(uint32_t *)(buf + 1);
    if (*(uint32_t *)((char *)buf + 0xc) <= cnt) {
        sk_grow_ptrs(st, buf, (uint32_t *)((char *)buf + 0xc), 1);
        cnt = *(uint32_t *)(buf + 1);
    }
    uint64_t w = *p;
    *(uint32_t *)(buf + 1) = cnt + 1;
    *(uint64_t *)(buf[0] + (uint64_t)cnt * 8) = w;
}

/* FUN_003adcd8 @ 0x3adcd8   (est. sk_node_is_compound)
 * Returns 1 when the node must be recursed into (not a printable leaf).
 * Confidence: medium */
static uint64_t sk_003adcd8(uint64_t *node)
{
    uint32_t u = NODE_TAG(node);
    if (NODE_TAG(node) < 0xbc) {
        if (!(0x3a < u - 0x48 || ((1ULL << ((u - 0x48) & 0x3f)) & 0x404000000000001ULL) == 0) ||
            u == 0x22) return 0;
    } else if (!(2 < u - 0xbc) ||
               (0x25 < u - 0xe6 || ((1ULL << ((u - 0xe6) & 0x3f)) & 0x2000000005ULL) == 0)) {
        return 0;
    }
    return 1;
}

/* FUN_003add54 @ 0x3add54   (est. sk_parse_group)
 * Reads a letter token selecting a Swift calling-convention attribute string
 * (inout/owned/unowned/guaranteed/... from a table at 0x5d5ee0), builds a
 * 0x6c string node and pushes it under the given tag. 'X' maps to a fixed
 * constant. Returns the pushed node or 0 when the char does not match.
 * Confidence: medium */
static uint64_t sk_003add54(uint64_t *st, uint64_t p2)
{
    uint64_t pos = STREAM_POS(st);
    uint64_t pc = 0;
    if (pos < STREAM_END(st)) {
        uint64_t np = pos + 1;
        STREAM_POS(st) = np;
        uint32_t c = STREAM_DATA(st)[pos];
        if (c - 0x62 < 0x18) {
            switch (c) {
            case 'c': pc = (uint64_t)s__in_constant_005d5ee4; break;
            case 'd': case 'f': case 'h': case 'j': case 'k': case 'o':
            case 'q': case 'r': case 's': case 't': case 'u': case 'w':
                goto bad;
            case 'e': pc = (uint64_t)s__deallocating_005d6df0; break;
            case 'g': pc = (uint64_t)s__guaranteed_005d5f28; break;
            case 'i': break;                     /* defaults to 0x5d5ee0 */
            case 'l': pc = (uint64_t)s__inout_005d5f00; break;
            case 'm': pc = (uint64_t)s__pack_inout_005d5f51; break;
            case 'n': pc = (uint64_t)s__in_guaranteed_005d5ef1; break;
            case 'p': pc = (uint64_t)s__pack_guaranteed_005d5f40; break;
            case 'v': pc = (uint64_t)s__pack_owned_005d5f34; break;
            case 'x': pc = (uint64_t)s__owned_005d5f18; break;
            case 'y': pc = (uint64_t)s__unowned_005d5f1f; break;
            default: pc = (uint64_t)s__inout_aliasable_005d5f07; break;
            }
            if (pc == 0) pc = (uint64_t)0x5d5ee0;
            goto emit;
        }
        if (c == 'X') { pc = (uint64_t)0x5d6de8; goto emit; }
    }
bad:
    STREAM_POS(st) = STREAM_POS(st) - 1;
    return 0;
emit:
    {
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x6c); NODE_SETSUBT(n, 3);
        n[0] = pc;
        n[1] = (uint64_t)sk_len_query(pc);
        return (uint64_t)sk_node_push(st, (int)p2, n);
    }
}

/* FUN_003adf20 @ 0x3adf20   (est. sk_parse_group2)
 * Reads a lowercase letter; if it is in the attribute set (bitmask
 * 0x125c49 over a 21-entry table at 0x67c3b0), builds a 0x6c string node
 * holding the selected string and pushes it under the given tag. Else backs
 * up the stream and returns 0.
 * Confidence: medium */
static uint64_t sk_003adf20(uint64_t *st, uint64_t p2)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st)) {
        uint64_t np = pos + 1;
        STREAM_POS(st) = np;
        uint32_t c = STREAM_DATA(st)[pos] - 0x61;
        if (c < 0x15 && ((0x125c49U >> (c & 0x1f)) & 1) != 0) {
            uint64_t pc = *(uint64_t *)((uint64_t)(c & 0xff) * 8 + 0x67c3b0);
            uint64_t *n = sk_node_alloc(st, 1);
            NODE_SETTAG(n, 0x6c); NODE_SETSUBT(n, 3);
            n[0] = pc;
            n[1] = (uint64_t)sk_len_query(pc);
            return (uint64_t)sk_node_push(st, (int)p2, n);
        }
    }
    STREAM_POS(st) = STREAM_POS(st) - 1;
    return 0;
}

/* FUN_003adff0 @ 0x3adff0   (est. sk_arg_sending)
 * If the next stream char is 'T' (sending), consumes it and returns a 0x71
 * string node holding "sending"; else returns NULL.
 * Confidence: high */
static uint64_t *sk_003adff0(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'T') {
        STREAM_POS(st) = pos + 1;
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x71); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)s_sending_005d6e12; n[1] = 7;
        return n;
    }
    return NULL;
}

/* FUN_003ae05c @ 0x3ae05c   (est. sk_arg_isolated)
 * If the next stream char is 'I' (isolated), consumes it and returns a 0x72
 * string node holding "isolated"; else returns NULL.
 * Confidence: high */
static uint64_t *sk_003ae05c(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'I') {
        STREAM_POS(st) = pos + 1;
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x72); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)s_isolated_005d6e1a; n[1] = 8;
        return n;
    }
    return NULL;
}

/* FUN_003ae0c8 @ 0x3ae0c8   (est. sk_arg_silImplicitLeadingParam)
 * If the next stream char is 'L', consumes it and returns a 0x73 string node
 * holding "_sil_implicit_leading_param" (26 bytes); else returns NULL.
 * Confidence: high */
static uint64_t *sk_003ae0c8(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'L') {
        STREAM_POS(st) = pos + 1;
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x73); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)s_sil_implicit_leading_param_005d6e23; n[1] = 0x1a;
        return n;
    }
    return NULL;
}

/* FUN_003ae134 @ 0x3ae134   (est. sk_arg_noDerivative)
 * If the next stream char is 'w' (noDerivative marker), consumes it and
 * returns a 0x70 string node holding "_noDerivative"; else returns a 0x70
 * string node holding the empty-string constant DAT_005be7c0.
 * Confidence: high */
static uint64_t *sk_003ae134(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    const char *s;
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'w') {
        STREAM_POS(st) = pos + 1;
        s = s__noDerivative_005d5f5d;
    } else {
        s = (const char *)DAT_005be7c0;
    }
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, 0x70); NODE_SETSUBT(n, 3);
    n[0] = (uint64_t)s;
    n[1] = (uint64_t)sk_len_query((uint64_t)s);
    return n;
}

/* FUN_003ae1b4 @ 0x3ae1b4   (est. sk_pop_list)
 * Reads a letter and builds a list/attr node: 'A' -> sk_003ae36c result
 * wrapped in a 0x134 pair with a popped 0xf4 element; 'E' -> pop_f4 into
 * 0x132; 'M' -> pop_a3 into 0x131; 'X'/'Y' -> pop into 0x133 (Y adds a
 * second pop_f4 child). Returns the node or 0 on malformed input.
 * Confidence: medium */
static uint64_t sk_003ae1b4(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    uint8_t c = STREAM_DATA(st)[pos];
    uint64_t *v, *n, *e;
    uint16_t tag;
    if (c < 0x4d) {
        if (c == 'A') {
            uint64_t *r = (uint64_t *)sk_003ae36c(st);
            if (r && STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                v = STACK_ELEM(st, i);
                if (NODE_TAG(v) == 0xf4) {
                    STACK_CNT(st) = i;
                    return (uint64_t)sk_node_push2(st, 0x134, v, r);
                }
            }
            return 0;
        }
        if (c != 'E') return 0;
        v = sk_003ace50(st);
        if (!v) return 0;
        n = sk_node_alloc(st, 1);
        tag = 0x132;
    } else if (c == 'M') {
        v = (uint64_t *)sk_003ace08(st);
        if (!v) return 0;
        n = sk_node_alloc(st, 1);
        tag = 0x131;
    } else {
        if (c != 'X') {
            if (c != 'Y') return 0;
            if (STACK_CNT(st) == 0) return 0;
            uint32_t i = STACK_CNT(st) - 1;
            v = STACK_ELEM(st, i);
            STACK_CNT(st) = i;
            if (!v) return 0;
            e = sk_003ace50(st);
            if (!e) return 0;
            n = sk_node_alloc(st, 1);
            NODE_SETTAG(n, 0x133); NODE_SETSUBT(n, 0);
            sk_node_add(n, e, st);
            goto attach_v;
        }
        v = sk_003ace50(st);
        if (!v) return 0;
        n = sk_node_alloc(st, 1);
        tag = 0x133;
    }
    NODE_SETTAG(n, tag); NODE_SETSUBT(n, 0);
attach_v:
    sk_node_add(n, v, st);
    return (uint64_t)n;
}

/* FUN_003ae36c @ 0x3ae36c   (est. sk_parse_12f)
 * Builds a 0x12f node and drains consecutive elements returned by
 * sk_003ae658 (bounded by a 0x121 terminator) as children; finalizes on the
 * terminator. Returns the node or 0.
 * Confidence: medium */
static uint64_t sk_003ae36c(uint64_t *st)
{
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0x12f); NODE_SETSUBT(node, 0);
    while (true) {
        bool term;
        if (STACK_CNT(st) == 0) term = true;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            if (NODE_TAG(STACK_ELEM(st, i)) != 0x121) term = true;
            else { term = false; STACK_CNT(st) = i; }
        }
        uint64_t *e = (uint64_t *)sk_003ae658(st);
        if (!e) break;
        sk_node_add(node, e, st);
        if (!term) { sk_node_finalize(node, 0); return (uint64_t)node; }
    }
    return 0;
}

/* FUN_003ae4c8 @ 0x3ae4c8   (est. sk_pop_pair)
 * Drains consecutive sk_003ae658 results (bounded by a 0x121 terminator)
 * into a local buffer, then builds a 0xf4 node (either the popped 0xf4
 * element or a fresh node holding param_2) and re-wraps each buffered result
 * in a 0x2e node with it, pushing each as 0xf4. Returns the last pushed node.
 * Confidence: medium */
static uint64_t sk_003ae4c8(uint64_t *st, uint64_t p2)
{
    uint64_t local_50[4];
    uint64_t *node;
    local_50[1] = (uint64_t)sk_003b0e1c(st, 4);
    local_50[0] = DAT_004f2740;
    bool term;
    do {
        if (STACK_CNT(st) == 0) term = true;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            if (NODE_TAG(STACK_ELEM(st, i)) != 0x121) term = true;
            else { term = false; STACK_CNT(st) = i; }
        }
        uint64_t *e = (uint64_t *)sk_003ae658(st);
        if (!e) return 0;
        sk_003ad810((uint64_t *)(local_50 + 1), (uint64_t *)&e, st);
    } while (!term);
    if (p2 == 0) {
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            node = STACK_ELEM(st, i);
            if (NODE_TAG(node) == 0xf4) { STACK_CNT(st) = i; goto have; }
        }
        node = 0;
    } else {
        node = sk_node_alloc(st, 1);
        NODE_SETTAG(node, 0xf4); NODE_SETSUBT(node, 0);
        sk_node_add(node, (uint64_t *)p2, st);
    }
have:
    while (local_50[0] != 0) {
        uint64_t *item = (uint64_t *)local_50[local_50[0] - 1];
        local_50[0] -= 1;
        if (!item) break;
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x2e); NODE_SETSUBT(n, 0);
        uint64_t *res = 0;
        if (node && n) {
            sk_node_add(n, node, st);
            sk_node_add(n, item, st);
            res = n;
        }
        node = sk_node_push(st, 0xf4, res);
    }
    return (uint64_t)node;
}

/* FUN_003ae658 @ 0x3ae658   (est. sk_pop_attr)
 * Pops the top element: if tag 0xc0/0x16b it is used; if tag 0xf4 and
 * FUN_003a33cc accepts it, unwrap and use it; then pop a second 0x67 element.
 * Builds a 0x24 node holding both and pushes it. Returns 0 on empty.
 * Confidence: medium */
static uint64_t sk_003ae658(uint64_t *st)
{
    uint32_t cnt = STACK_CNT(st);
    uint64_t *a = 0, *b = 0;
    if (cnt != 0) {
        uint32_t i = cnt - 1;
        a = STACK_ELEM(st, i);
        int16_t t = NODE_TAG(a);
        if (t == 0xc0 || t == 0x16b) {
            STACK_CNT(st) = i;
            cnt = i;
            if (i == 0) goto no_b;
        } else if (t == 0xf4) {
            STACK_CNT(st) = i;
            uint64_t u = FUN_003a33cc(a);
            if ((u & 1) == 0) return 0;
            cnt = i;
            if (i == 0) goto no_b;
        } else a = 0;
        b = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(b) == 0x67) {
            STACK_CNT(st) = cnt - 1;
            goto have_b;
        }
    }
no_b:
    b = 0;
have_b:
    {
        uint64_t *n = sk_node_push(st, 0x24, b);
        if (a && n) sk_node_add(n, a, st);
        return (uint64_t)n;
    }
}

/* FUN_003a75e4 @ 0x3a75e4   (est. sk_parse_scalar_or_special)
 * Parses a single-letter scalar/special token from the stream into a node:
 * 'l' pops a 0x67 element and pushes as 0xba; 'L' pops 0x67 + printable and
 * pushes 0xba; an uppercase/hex-alnum letter builds a 0xd9 node wrapping a
 * 0x67 byte scalar plus the popped element; '_'/'N' parses an ident into a
 * 0x92 node with the printable stack top. Returns the resulting node.
 * Confidence: medium */
static uint64_t sk_003a75e4(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st)) {
        uint8_t c = STREAM_DATA(st)[pos];
        if (c == 'l') {
            STREAM_POS(st) = pos + 1;
            uint64_t *top = 0;
            if (STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *e = STACK_ELEM(st, i);
                if (NODE_TAG(e) == 0x67) {
                    STACK_CNT(st) = i;
                    top = e;
                }
            }
            return (uint64_t)sk_node_push(st, 0xba, top);
        }
        if (c == 'L') {
            STREAM_POS(st) = pos + 1;
            uint64_t *a = 0, *b = 0;
            if (STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                a = STACK_ELEM(st, i);
                if (NODE_TAG(a) == 0x67) {
                    STACK_CNT(st) = i;
                    if (i == 0) b = 0;
                    else {
                        uint32_t j = i - 1;
                        b = STACK_ELEM(st, j);
                        if (sk_003acda0(NODE_TAG(b)) == 0) b = 0;
                        else STACK_CNT(st) = j;
                    }
                } else {
                    a = 0;
                }
            }
            return (uint64_t)sk_node_push2(st, 0xba, a, b);
        }
        if ((char)c >= 'a') {
            if (c < 'k') goto ident;
        } else if (c - 0x41 < 10) goto ident;
        goto fallback;
    }
fallback:
    {
        uint64_t *node = sk_003ac52c(st);
        uint64_t *b = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            b = STACK_ELEM(st, i);
            if (sk_003acda0(NODE_TAG(b)) == 0) b = 0;
            else STACK_CNT(st) = i;
        }
        return (uint64_t)sk_node_push2(st, 0x92, node, b);
    }
ident:
    STREAM_POS(st) = pos + 1;
    uint8_t ch = STREAM_DATA(st)[pos];
    uint64_t *sc = sk_alloc_scalar(st, 1);
    *(uint8_t *)sc = ch;
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, 0x67); NODE_SETSUBT(n, 3);
    n[0] = (uint64_t)sc;
    n[1] = 1;
    uint64_t *top = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        top = STACK_ELEM(st, i);
        STACK_CNT(st) = i;
    }
    uint64_t *node = sk_node_alloc(st, 1);
    NODE_SETTAG(node, 0xd9); NODE_SETSUBT(node, 0);
    sk_node_add(node, n, st);
    if (top) sk_node_add(node, top, st);
    return (uint64_t)node;
}

/* FUN_003a7818 @ 0x3a7818   (est. sk_dispatch_letter)
 * Dispatches on an ASCII letter at the stream position, mapping it to a tag
 * and building a node: most letters push the popped stack element (or the
 * stream dispatch / value) under a fixed tag; 'X' delegates to
 * sk_003ae1b4; letters without a case mapping return 0. Returns the node.
 * Confidence: medium */
static uint64_t sk_003a7818(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    uint8_t c = STREAM_DATA(st)[pos];
    if (0x39 < c - 0x41) return 0;      /* not in 'A'..'z' */
    switch (c) {
    default:
        {
            uint64_t *v = sk_stream_dispatch(st);
            return (uint64_t)sk_node_push(st, 0x111, v);
        }
    case 'B': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; v = e; }
        }
        return (uint64_t)sk_node_push(st, 0x10f, v);
    }
    case 'C': {
        if (STACK_CNT(st) == 0) return 0;
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) != 0xf4) return 0;
        STACK_CNT(st) = i;
        uint8_t sub = NODE_SUBT(e);
        uint32_t u = sub - 1;
        uint64_t *p = e;
        if (1 < u) p = (uint64_t *)NODE_DATA(e);
        if (sk_003acf38(NODE_TAG(p)) == 0) return 0;
        uint64_t *leaf;
        if (u < 2) leaf = (uint64_t *)NODE_DATA(e);
        else if (sub == 5 && (int64_t)e[1] != 0) { e = (uint64_t *)NODE_DATA(e); leaf = (uint64_t *)NODE_DATA(e); }
        else leaf = 0;
        return (uint64_t)sk_node_push(st, 0x112, leaf);
    }
    case 'D': case 'd': return (uint64_t)sk_val_get_alt(st, 0xff);
    case 'F': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; v = e; }
        }
        return (uint64_t)sk_node_push(st, 0x110, v);
    }
    case 'I': return (uint64_t)sk_val_get_alt(st, 0xfc);
    case 'J': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x149, v);
    }
    case 'K': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x147, v);
    }
    case 'L': return (uint64_t)sk_val_get_alt(st, 0x101);
    case 'M': return (uint64_t)sk_val_get_alt(st, 0x145);
    case 'N': return (uint64_t)sk_val_get_alt(st, 0x148);
    case 'P': return (uint64_t)sk_val_get_alt(st, 99);
    case 'Q': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x13d, v);
    }
    case 'R': return (uint64_t)sk_val_get_alt(st, 0x100);
    case 'S': {
        uint64_t v = sk_val_get(st);
        return (uint64_t)sk_node_push(st, 0xcc, (uint64_t *)v);
    }
    case 'U': return (uint64_t)sk_val_get_alt(st, 0x9e);
    case 'V': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4 && sk_tag_simple(0) == 0) goto VZ;
            STACK_CNT(st) = i; v = e;
        }
    VZ:
        return (uint64_t)sk_node_push(st, 0xbb, v);
    }
    case 'X': return (uint64_t)sk_003ae1b4(st);
    case 'a': return (uint64_t)sk_val_get_alt(st, 0xfa);
    case 'b': return (uint64_t)sk_val_get_alt(st, 0x146);
    case 'c': {
        uint64_t *v = sk_stream_dispatch(st);
        return (uint64_t)sk_node_push(st, 199, v);
    }
    case 'f': return (uint64_t)sk_val_get_alt(st, 0x4d);
    case 'g': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x13f, v);
    }
    case 'h': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x140, v);
    }
    case 'i': return (uint64_t)sk_val_get_alt(st, 0xfd);
    case 'j': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x141, v);
    }
    case 'k': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x142, v);
    }
    case 'l': return (uint64_t)sk_val_get_alt(st, 0xfe);
    case 'm': return (uint64_t)sk_val_get_alt(st, 0x9c);
    case 'n': return (uint64_t)sk_val_get_alt(st, 0xa8);
    case 'o': return (uint64_t)sk_val_get_alt(st, 0x1a);
    case 'p': {
        uint64_t v = sk_val_get(st);
        return (uint64_t)sk_node_push(st, 0xc5, (uint64_t *)v);
    }
    case 'q': {
        uint64_t *v = 0;
        if (STACK_CNT(st) != 0) { uint32_t i = STACK_CNT(st)-1; v = STACK_ELEM(st, i); STACK_CNT(st) = i; }
        return (uint64_t)sk_node_push(st, 0x15e, v);
    }
    case 'r': return (uint64_t)sk_val_get_alt(st, 0xfb);
    case 's': return (uint64_t)sk_val_get_alt(st, 0x9f);
    case 't': return (uint64_t)sk_val_get_alt(st, 0xa0);
    case 'u': return (uint64_t)sk_val_get_alt(st, 0x9d);
    case 'z': return (uint64_t)sk_val_get_alt(st, 0x14d);
    }
}

/* FUN_003a7d9c @ 0x3a7d9c   (est. sk_parse_construct)
 * Parses a construct token (one ASCII letter) from the stream into a node.
 * Handles 'S'(di), 'Y'/'Z' (abc48/c2d0 wrapped by ae4c8), 'O'(f4 pop via
 * ace50), 'P'(ad188), 'R'(ident scalar 0x164 wrapped 0x143), 'a'(f4 over
 * 0x5 stream pop + 0x67), 'e'(f2 over stream pop + f3 ident), 'o'(f7
 * collection of 0x13b with inline children + 0x68 ident), 'p'(f1 over two
 * stream pops), 'r'(empty 0x143), 'x'/'y'/'z'(lowercase variants). Pushes the
 * built node onto a scratch buffer at +0x68 and returns it.
 * Confidence: medium */
static uint64_t sk_003a7d9c(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    uint8_t b = STREAM_DATA(st)[pos];
    uint64_t r, tmp;
    uint64_t *buf = (uint64_t *)((char *)st + 0x68);
    if (b < 0x61) {
        if (0x52 < b) {
            if (b < 0x59) {
                if (b == 'S') return (uint64_t)sk_003ad278(st);
                if (b != 'X') return 0;
                r = 0;
            } else if (b == 'Y') {
                r = sk_003abc48(st);
            } else {
                if (b != 'Z') return 0;
                r = sk_003ac2d0(st, 0, 0);
            }
            r = sk_003ae4c8(st, r);
            goto store;
        }
        if (b == 'O') {
            r = (uint64_t)sk_003ace50(st);
            return (uint64_t)sk_node_push(st, 0x144, (uint64_t *)r);
        }
        if (b == 'P') return (uint64_t)sk_003ad188(st);
        if (b != 'R') return 0;
        {
            int32_t v = sk_003ac4a4(st);
            if (v < 0) return 0;
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0x164); NODE_SETSUBT(s, 4);
            s[0] = (uint64_t)v;
            return (uint64_t)sk_node_push(st, 0x143, s);
        }
    } else {
        if (0x71 < b) {
            if (b < 0x79) {
                if (b == 'r') {
                    uint64_t *n = sk_node_alloc(st, 1);
                    NODE_SETTAG(n, 0x143); NODE_SETSUBT(n, 0);
                    goto pushf4;
                }
                if (b != 'x') return 0;
                r = 0;
            } else if (b == 'y') {
                r = sk_003abc48(st);
            } else {
                if (b != 'z') return 0;
                r = sk_003ac2d0(st, 0, 0);
            }
            r = sk_003ae414(st, r);
            goto store;
        }
        if (b < 0x6f) {
            if (b == 'a') {
                uint64_t *top = 0;
                if (STACK_CNT(st) != 0) {
                    uint32_t i = STACK_CNT(st) - 1;
                    uint64_t *e = STACK_ELEM(st, i);
                    if (NODE_TAG(e) == 0x67) { STACK_CNT(st) = i; top = e; }
                }
                uint64_t *p = sk_stream_pop(st);
                uint64_t *n = sk_node_push2(st, 5, p, top);
                return (uint64_t)sk_node_push(st, 0xf4, n);
            }
            if (b != 'e') return 0;
            {
                uint64_t *p = sk_stream_pop(st);
                int32_t v = sk_003ac4a4(st);
                if (v < 0) return 0;
                uint64_t *s = sk_node_alloc(st, 1);
                NODE_SETTAG(s, 0xf3); NODE_SETSUBT(s, 4);
                s[0] = (uint64_t)v;
                return (uint64_t)sk_node_push2(st, 0xf2, p, s);
            }
        } else {
            if (b == 'o') {
                int32_t id = sk_003ac4a4(st);
                uint64_t scratch = 0;      /* child-buffer pointer field (local_48) */
                uint64_t slen = 0;         /* child count (local_40) */
                uint64_t s2 = 0;           /* single trailing child slot (local_50) */
                if (sk_003ad724(st, (uint64_t)(uintptr_t)&scratch, &s2) == 0 ||
                    STACK_CNT(st) == 0) return 0;
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *el = STACK_ELEM(st, i);
                STACK_CNT(st) = i;
                if (el == 0) return 0;
                uint64_t *w = sk_node_alloc(st, 1);
                NODE_SETTAG(w, 0x68); NODE_SETSUBT(w, 4);
                w[0] = (uint64_t)id;
                uint64_t *n = sk_node_push2(st, 0x13b, el, w);
                uint64_t *f7 = sk_node_alloc(st, 1);
                NODE_SETTAG(f7, 0xf7); NODE_SETSUBT(f7, 0);
                if (slen != 0) {
                    long ii = (slen & 0xffffffff) * 8 - 8;
                    do {
                        sk_node_add(f7, (uint64_t *)*(uint64_t *)(scratch + (uint64_t)ii), st);
                        ii -= 8;
                    } while (ii != -8);
                }
                sk_node_add(n, f7, st);
                if (s2) sk_node_add(n, (uint64_t *)s2, st);
                uint64_t *res = (uint64_t *)sk_node_push(st, 0xf4, n);
                if (res == 0) return 0;
                tmp = (uint64_t)res;
                sk_003ad810(buf, &tmp, st);
                return (uint64_t)res;
            }
            if (b != 'p') return 0;
            {
                uint64_t *a = sk_stream_pop(st);
                uint64_t *b2 = sk_stream_pop(st);
                return (uint64_t)sk_node_push2(st, 0xf1, b2, a);
            }
        }
        return 0;
    }
    /* unreachable fallthrough for lowercase - handled above */
    if (0) goto store;
store:
    {
        /* record the built node into the scratch buffer at +0x68 and return */
        uint64_t node = r;
        sk_003ad810(buf, &node, st);
        return r;
    }
pushf4:
    return (uint64_t)sk_node_push(st, 0xf4, (uint64_t *)0);
}

/* FUN_003a81e8 @ 0x3a81e8   (est. sk_parse_type_ref)
 * Parses a type-reference token (one ASCII letter, optionally lowercase)
 * from the stream. Most letters select a fixed tag; 'I'/'i' parse an ident
 * (0x171/0x174 build); 'T'/'t'/'M'/'m'/'P'/'p' select via abc48 + ae414/ae4c8;
 * 'h'/'H' (case 'l' branch) parses a small sub-schema of DAT_* string labels
 * into a 0x2a node wrapping two optional ident children. Returns the node.
 * Confidence: low */
static uint64_t sk_003a81e8(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) goto default_case;
    uint8_t b = STREAM_DATA(st)[pos];
    STREAM_POS(st) = pos + 1;
    uint64_t u10 = 1, u11, l5 = 0, l6;
    uint64_t p1 = pos + 1;   /* saved new pos */
    if (0x14 < b - 0x42) {
        if (0x14 < b - 0x62) {
        default_case:
            u11 = 0;
            STREAM_POS(st) = p1 - 1;
            l5 = 0;
            goto post_56;
        }
        switch (b) {
        default: u11 = 1; l5 = 0; break;
        case 'c': goto case_c;
        case 'd': case 'e': case 'f': case 'g': case 'j': case 'k':
        case 'n': case 'o': case 'q': case 'r': case 'u':
            goto default_case;
        case 'h': u11 = 3; l5 = 0; break;
        case 'i':
            l5 = (uint64_t)sk_003ac52c(st);
            if (l5 == 0) return 0;
            u11 = 6; break;
        case 'l': u11 = 4; l5 = 0; break;
        case 'm': u10 = 4; goto case_c;
        case 'p': u10 = 0; goto case_c;
        case 's': u11 = 2; l5 = 0; break;
        case 't': u10 = 2;
        case_c: {
            uint64_t v = sk_003abc48(st);
            l5 = sk_003ae414(st, v);
            u11 = u10;
            goto post_a8;
        }
        case 'v': u11 = 5; l5 = 0; break;
        }
    post_56:
        l6 = l5;
        {
            uint64_t v = sk_003abc48(st);
            l5 = (uint64_t)sk_node_push(st, 0xf4, (uint64_t *)v);
        }
        goto post_c8;
    }
    l6 = 0;
    u11 = 7;
    l5 = 0;
    uint64_t u3 = 1;
    switch (b) {
    case 'C': goto case_C;
    case 'D': case 'E': case 'F': case 'G': case 'H': case 'J': case 'K':
    case 'N': case 'O': case 'R': case 'U':
        goto default_case;
    case 'I':
        l6 = (uint64_t)sk_003ac52c(st);
        if (l6 == 0) return 0;
        u3 = 6; break;
    case 'L': l6 = 0; u3 = 4; break;
    case 'M': u10 = 4; goto case_C;
    case 'P': u10 = 0; goto case_C;
    case 'Q': l6 = 0; u3 = 0; break;
    case 'S': l6 = 0; u3 = 2; break;
    case 'T': u10 = 2;
    case_C: {
        uint64_t v = sk_003abc48(st);
        l5 = sk_003ae4c8(st, v);
        u11 = u10;
    post_a8: {
        uint64_t loc = l5;
        if (l5 != 0) sk_003ad810((uint64_t *)((char *)st + 0x68), &loc, st);
        l6 = 0;
        goto post_c8;
    }
    }
    case 'V': goto post_56;
    }
    u11 = u3;
    if (STACK_CNT(st) == 0) { l5 = 0; }
    else {
        uint32_t i = STACK_CNT(st) - 1;
        l5 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l5) != 0xf4) l5 = 0;
        else STACK_CNT(st) = i;
    }
post_c8:
    if (u11 < 4) {
        if (u11 < 2) {
            if (u11 == 0) {
                l6 = sk_val_get(st);
            } else {
                if (STACK_CNT(st) != 0) {
                    uint32_t i = STACK_CNT(st) - 1;
                    l6 = (uint64_t)STACK_ELEM(st, i);
                    if (NODE_TAG((uint64_t *)l6) == 0xf4) { STACK_CNT(st) = i; goto post_54c; }
                }
                l6 = 0;
            }
        post_54c:
            return (uint64_t)sk_node_push2(st, 0x25, (uint64_t *)l5, (uint64_t *)l6);
        }
        if (u11 != 2) {
            if (STACK_CNT(st) == 0) l6 = 0;
            else {
                uint32_t i = STACK_CNT(st) - 1;
                l6 = (uint64_t)STACK_ELEM(st, i);
                if (NODE_TAG((uint64_t *)l6) != 0xf4) l6 = 0;
                else STACK_CNT(st) = i;
            }
            return (uint64_t)sk_node_push2(st, 0x29, (uint64_t *)l5, (uint64_t *)l6);
        }
        if (STACK_CNT(st) == 0) l6 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            l6 = (uint64_t)STACK_ELEM(st, i);
            if (NODE_TAG((uint64_t *)l6) != 0xf4) l6 = 0;
            else STACK_CNT(st) = i;
        }
        return (uint64_t)sk_node_push2(st, 0x28, (uint64_t *)l5, (uint64_t *)l6);
    }
    if (u11 < 6) {
        if (u11 != 4) {
            return (uint64_t)sk_node_push2(st, 0x2b, (uint64_t *)l5, (uint64_t *)l6);
        }
        /* 'l'/'L': parse a DAT_*-labelled sub-schema into a 0x2a node */
        uint64_t pp = STREAM_POS(st);
        if (pp < STREAM_END(st)) {
            l6 = 0;
            STREAM_POS(st) = pp + 1;
            uint8_t c2 = STREAM_DATA(st)[pp];
            uint32_t u8 = c2;
            char *label = DAT_005d3810;
            uint64_t l12 = 0;
            if (u8 - 0x42 < 0x14) {
                switch (u8) {
                default: l6 = 0; l12 = 0; label = DAT_005d37d2; break;
                case 'C': l6 = 0; l12 = 0; label = DAT_005d37e1; break;
                case 'D': l6 = 0; l12 = 0; label = DAT_005d37cb; break;
                case 'E':
                    l6 = (uint64_t)sk_003ac52c(st);
                    if (l6 == 0) return 0;
                    l12 = (uint64_t)sk_003ac52c(st);
                    label = DAT_005d356c; break;
                case 'F': case 'G': case 'H': case 'I': case 'J': case 'K':
                case 'L': case 'O': case 'P': case 'Q':
                    return 0;
                case 'M':
                    l6 = (uint64_t)sk_003ac52c(st);
                    if (l6 == 0) return 0;
                    l12 = (uint64_t)sk_003ac52c(st);
                    label = DAT_005d37d0; break;
                case 'N': l6 = 0; l12 = 0; label = DAT_005d37c9; break;
                case 'R': l6 = 0; l12 = 0; label = DAT_005d3568; break;
                case 'S':
                    l6 = (uint64_t)sk_003ac52c(st);
                    l12 = 0;
                    if (l6 == 0) return 0;
                    label = DAT_005d37d7; break;
                case 'T': l6 = 0; l12 = 0; label = DAT_005d37e5; break;
                case 'U': break;
                }
            } else if (u8 == 'e') {
                l6 = (uint64_t)sk_003ac52c(st);
                l12 = 0;
                if (l6 == 0) return 0;
                label = DAT_005d6b7d;
            } else {
                if (u8 != 'm') return 0;
                l6 = (uint64_t)sk_003ac52c(st);
                l12 = 0;
                if (l6 == 0) return 0;
                label = DAT_005d6c15;
            }
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0x67); NODE_SETSUBT(s, 3);
            s[0] = (uint64_t)label;
            s[1] = 1;
            uint64_t *n = sk_node_push2(st, 0x2a, (uint64_t *)l5, s);
            if (l6 != 0) {
                if (n == 0) return 0;
                sk_node_add(n, (uint64_t *)l6, st);
            }
            if (l12 == 0) return (uint64_t)n;
            if (n != 0) {
                sk_node_add(n, (uint64_t *)l12, st);
                return (uint64_t)n;
            }
        }
        return 0;
    }
    if (u11 == 6) return (uint64_t)sk_node_push2(st, 0x171, (uint64_t *)l5, (uint64_t *)l6);
    if (STACK_CNT(st) == 0) l6 = 0;
    else {
        uint32_t i = STACK_CNT(st) - 1;
        l6 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l6) != 0xf4) l6 = 0;
        else STACK_CNT(st) = i;
    }
    return (uint64_t)sk_node_push2(st, 0x174, (uint64_t *)l5, (uint64_t *)l6);
}

/* FUN_003a8868 @ 0x3a8868   (est. sk_parse_named_special)
 * Parses a special named token: 'C' builds an a3 node holding the
 * "__C_Synthesized" string (len 0xf); 'o' builds an a3 node with "__C" (len
 * 3); 'g' parses an Optional modifier (0x3f via ac600) wrapped in a 0xe/0xf7
 * f4 triple and records it in the +0x68 scratch; otherwise backs up and
 * reads a decimal length (ac430): if >0x800 returns NULL, else if followed
 * by 'c' sets a flag, reads one more byte, builds an ac6b4 node, and pushes
 * it onto the value stack (at +0x58) iVar2+1 times. Returns the node.
 * Confidence: medium */
static uint64_t *sk_003a8868(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    uint64_t p = pos;
    if (STREAM_END(st) <= pos) goto read_len;
    p = pos + 1;
    STREAM_POS(st) = p;
    char c = STREAM_DATA(st)[pos];
    if (c == 'C') {
        uint64_t *sc = sk_alloc_scalar(st, 0xf);
        memcpy_placeholder(sc, s___C_Synthesized_005d6ef6, 0xf);
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0xa3); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)sc;
        n[1] = 0xf;
        return n;
    }
    if (c != 'g') {
        if (c != 'o') goto read_len;
        uint64_t *sc = sk_alloc_scalar(st, 3);
        *(uint16_t *)sc = 0x5f5f;          /* "__" */
        *(uint8_t *)((char *)sc + 2) = 'C';
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0xa3); NODE_SETSUBT(n, 3);
        n[0] = (uint64_t)sc;
        n[1] = 3;
        return n;
    }
    /* 'g': Optional modifier */
    uint64_t mv = sk_003ac600(st, 0x3f, (uint64_t)s_Optional_005d4e8b);
    uint64_t *m = (uint64_t *)mv;
    uint64_t *top = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; top = e; }
    }
    uint64_t *n1 = (uint64_t *)sk_node_push(st, 0xf7, top);
    uint64_t *n2 = (uint64_t *)sk_node_push2(st, 0xe, m, n1);
    uint64_t *n3 = (uint64_t *)sk_node_push(st, 0xf4, n2);
    if (n3 == 0) return 0;
    uint64_t loc = (uint64_t)n3;
    sk_003ad810((uint64_t *)((char *)st + 0x68), &loc, st);
    return n3;
read_len:
    STREAM_POS(st) = p - 1;
    int32_t n = sk_003ac430(st);
    if (0x800 < n) return 0;
    uint64_t q = STREAM_POS(st);
    uint64_t flag = 0;
    if (q < STREAM_END(st) && STREAM_DATA(st)[q] == 'c') {
        q = q + 1;
        STREAM_POS(st) = q;
        flag = 1;
    }
    char ch;
    if (q < STREAM_END(st)) {
        STREAM_POS(st) = q + 1;
        ch = STREAM_DATA(st)[q];
    } else {
        ch = '\0';
    }
    uint64_t nodev = sk_003ac6b4(st, (int)ch, (uint32_t)flag);
    uint64_t *node = (uint64_t *)nodev;
    if (node == 0) return 0;
    if (n < 2) return node;
    uint32_t k = n + 1;
    do {
        uint64_t loc = (uint64_t)node;
        sk_003ad810((uint64_t *)((char *)st + 0x58), &loc, st);
        k = k - 1;
    } while (2 < k);
    return node;
}

/* FUN_003a9944 @ 0x3a9944   (est. sk_parse_letter_node)
 * Parses a one-letter construct into a node. Many letters map to a fixed tag
 * and wrap either the popped single 0xf4 stack element or a 0x2c+0xf4 pair.
 * 'O' with an inner letter selects among many tags (16c..170, 124..12a, 166/167)
 * using the shared one-or-pair pop; 'Z'/'z' builds a 0x14c child collection
 * (0x14a/0x14b wrap); 'S','T','V','b' delegate to helpers. Returns the node.
 * Confidence: medium */
/* Shared pop: pops either a single 0xf4 element (mode 1, *shallow set) or a
 * 0x2c element optionally followed by a 0xf4 element (mode 2, *deep = inner
 * f4, *shallow = the 0x2c element); mode 0 = nothing popped (0x2c alone still
 * consumed with deep=0). Mirrors the decompile's two-branch stack unwind. */
static int sk_pop_one_or_pair(uint64_t *st, uint64_t *deep, uint64_t *shallow)
{
    *deep = 0; *shallow = 0;
    int32_t cnt = STACK_CNT(st);
    if (cnt == 0) return 0;
    uint32_t i = cnt - 1;
    uint64_t top = (uint64_t)STACK_ELEM(st, i);
    uint16_t t = NODE_TAG((uint64_t *)top);
    if (t == 0xf4) { STACK_CNT(st) = i; *shallow = top; return 1; }
    if (t != 0x2c) return 0;
    STACK_CNT(st) = i;
    if (i == 0) return 2;
    uint64_t d = (uint64_t)STACK_ELEM(st, i - 1);
    if (NODE_TAG((uint64_t *)d) != 0xf4) return 2;
    STACK_CNT(st) = i - 1;
    *deep = d; *shallow = top;
    return 2;
}

static uint64_t sk_003a9944(uint64_t *st)
{
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    if (end <= pos) return 0;
    uint64_t npos = pos + 1;
    STREAM_POS(st) = npos;
    uint8_t b = STREAM_DATA(st)[pos];
    uint32_t u = b;
    uint64_t l14, pu12, tag;
    if (0x6b < b) {
        if (b < 0x74) {
            if (u != 'l') {
                if (u == 'p') { l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0xd2, (uint64_t *)l14); }
                if (u != 'r') return 0;
                l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0x5c, (uint64_t *)l14);
            }
            l14 = (uint64_t)sk_stream_dispatch(st);
            pu12 = 0;
            if (STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *e = STACK_ELEM(st, i);
                if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; pu12 = (uint64_t)e; }
            }
            return (uint64_t)sk_node_push2(st, 0x90, (uint64_t *)pu12, (uint64_t *)l14);
        }
        if (b != 't') {
            if (b != 'v') {
                if (u != 'z') return 0;
                goto case_z;
            }
            if (end <= npos) return 0;
            STREAM_POS(st) = pos + 2;
            uint64_t dir;
            if (STREAM_DATA(st)[npos] == 'd') dir = 0;
            else if (STREAM_DATA(st)[npos] != 'i') return 0;
            else dir = 1;
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0x36); NODE_SETSUBT(s, 4);
            s[0] = dir;
            l14 = 0;
            if (STACK_CNT(st) != 0) {
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *e = STACK_ELEM(st, i);
                if (NODE_TAG(e) != 0xf4 && sk_tag_simple(0) == 0) goto V0;
                STACK_CNT(st) = i; l14 = (uint64_t)e;
            }
        V0:
            return (uint64_t)sk_node_push2(st, 0x4b, (uint64_t *)l14, s);
        }
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (sk_003acda0(NODE_TAG(e)) == 0) l14 = 0;
            else { STACK_CNT(st) = i; l14 = (uint64_t)e; }
        }
        {
            uint64_t v = (uint64_t)sk_stream_dispatch(st);
            return (uint64_t)sk_node_push2(st, 6, (uint64_t *)v, (uint64_t *)l14);
        }
    }
    if (0x1f < u - 0x43) return 0;
    switch (u) {
    default:
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4 && sk_tag_simple(0) == 0) goto D0;
            STACK_CNT(st) = i; l14 = (uint64_t)e;
        }
    D0:
        return (uint64_t)sk_node_push(st, 0x40, (uint64_t *)l14);
    case 'D': case 'E': case 'F': case 'H': case 'K': case 'M': case 'N':
    case 'Q': case 'R': case 'U': case 'W': case 'X': case 'Y':
    case '[': case '\\': case ']': case '^': case '_': case '`':
        return 0;
    case 'G': l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0x5a, (uint64_t *)l14);
    case 'I': l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0x5b, (uint64_t *)l14);
    case 'J': return (uint64_t)sk_003af7a4(st);
    case 'L':
        l14 = (uint64_t)sk_stream_dispatch(st);
        pu12 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; pu12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push2(st, 0x91, (uint64_t *)pu12, (uint64_t *)l14);
    case 'O': {
        if (end <= npos) return 0;
        STREAM_POS(st) = pos + 2;
        b = STREAM_DATA(st)[npos];
        u = b;
        if (0x45 < b) {
            if (0x17 < u - 0x62) {
                if (b != 'F') {
                    if (b != 'H') return 0;
                    tag = 0x170;
                } else {
                    tag = 0x16f;
                }
                l14 = (uint64_t)sk_pop_one_or_pair(st, &pu12, &l14);
                if (l14 == 2) return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)0);
                /* mode 1: single */
                return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)l14);
            }
            switch (u) {
            case 'c': tag = 0x129; goto opair;
            case 'd': tag = 0x12a; goto opair;
            case 'e': tag = 0x125; goto opair;
            case 'f': tag = 299; goto opair;
            case 'g': tag = 0x168; goto opair;
            case 'h': tag = 300; goto opair;
            case 'r': tag = 0x126; goto opair;
            case 's': tag = 0x127; goto opair;
            case 'y': tag = 0x124; goto opair;
            case 'i': case 'j': {
                uint64_t *id = sk_003ac52c(st);
                tag = (u == 'i') ? 0x166 : 0x167;
                int m = sk_pop_one_or_pair(st, &pu12, &l14);
                if (m == 0) return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)id);
                if (m == 2) return (uint64_t)sk_ctx_op(st, tag, (uint64_t *)pu12, (uint64_t *)id, 0);
                return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)id);
            }
            case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
            case 'q': case 't': case 'u': case 'v': case 'w': case 'x':
                return 0;
            default: tag = 0x128; goto opair;
            }
        }
        if (b != 'B') {
            if (b != 'C') {
                if (u != 'D') return 0;
                tag = 0x16e;
            } else {
                tag = 0x16d;
            }
        } else {
            tag = 0x16c;
        }
        l14 = (uint64_t)sk_pop_one_or_pair(st, &pu12, &l14);
        if (l14 == 2) return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)0);
        return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)l14);
    opair: {
        int m = sk_pop_one_or_pair(st, &pu12, &l14);
        if (m == 0) return (uint64_t)sk_node_push(st, (int)tag, (uint64_t *)0);
        if (m == 2) return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)0);
        return (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)pu12, (uint64_t *)l14);
    }
    }
    case 'P': l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0xd0, (uint64_t *)l14);
    case 'S': l14 = sk_val_get(st); return (uint64_t)sk_node_push(st, 0xce, (uint64_t *)l14);
    case 'T': {
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l14 = (uint64_t)e; }
        }
        pu12 = (uint64_t)sk_003ae36c(st);
        uint64_t l16 = (uint64_t)sk_stream_dispatch(st);
        return (uint64_t)sk_ctx_op(st, 9, (uint64_t *)l16, (uint64_t *)pu12, (uint64_t *)l14);
    }
    case 'V':
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l14 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0x10a, (uint64_t *)l14);
    case 'Z':
    case_z: {
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x14c); NODE_SETSUBT(n, 0);
        uint64_t *l68 = 0, *l60 = 0, *l58 = 0;
        int32_t cnt = STACK_CNT(st);
        if (cnt != 0) {
            do {
                uint32_t i5 = cnt - 1;
                if (NODE_TAG(STACK_ELEM(st, i5)) != 0x121) break;
                STACK_CNT(st) = i5;
                if (i5 == 0) goto zb34;
                uint64_t *l16 = STACK_ELEM(st, cnt - 2);
                if (sk_003acda0(NODE_TAG(l16)) == 0) goto zb34;
                STACK_CNT(st) = cnt - 2;
                sk_003aefe4(&l68, &l16);
                cnt = STACK_CNT(st);
            } while (cnt != 0);
            uint64_t *pu7 = l58, *pu6 = l68, *pu12z = l60;
            if (l60 != l68) {
                uint64_t *pu17;
                do {
                    pu17 = pu12z - 1;
                    if (pu12z == pu6 || pu17 == pu7) sk_canary_panic();
                    sk_node_add(n, (uint64_t *)*pu17, st);
                    pu12z = pu17;
                } while (pu17 != l68);
            }
        }
        {
            uint64_t *l16 = sk_003ace50(st);
            uint64_t r;
            if (l16 == 0) { zb34: r = 0; }
            else {
                uint16_t t = (u == 'Z') ? 0x14a : 0x14b;
                r = (uint64_t)sk_node_push2(st, t, l16, n);
            }
            if (l68 == 0) return r;
            sk_lock(l68, (long)l58 - (long)l68);
            return r;
        }
    }
    case 'a': l14 = (uint64_t)sk_stream_dispatch(st); return (uint64_t)sk_node_push(st, 0xd1, (uint64_t *)l14);
    case 'b':
        l14 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l14 = (uint64_t)e; }
        }
        pu12 = (uint64_t)sk_stream_dispatch(st);
        return (uint64_t)sk_node_push2(st, 10, (uint64_t *)pu12, (uint64_t *)l14);
    }
}

/* FUN_003ab218 @ 0x3ab218   (est. sk_emit_type_annotated)
 * Builds a node with the given 16-bit tag, optionally appends a parsed string
 * (ad048) child, then pops and appends a run of "annotation" stack elements
 * whose tags are one of 0x89, 0x87/0x88, 0x45, 0x46, 0x11e/0x11f, 0x44,
 * 0x11d. Finally pushes two more children from ad0f0(3) and ad0f0(0xdb) and
 * pushes the whole thing as 0xf4.
 * Confidence: medium */
static void sk_003ab218(uint64_t *st, uint16_t p2, int32_t p3)
{
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, p2); NODE_SETSUBT(n, 0);
    if (p3 != 0) {
        uint64_t *s = sk_003ad048(st);
        if (s != 0) sk_node_add(n, s, st);
    }
    int32_t cnt = STACK_CNT(st);
    if (cnt != 0) {
        uint64_t *e;
        e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0x89) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(n, e, st);
            cnt = STACK_CNT(st);
            if (cnt == 0) goto done;
        }
        e = STACK_ELEM(st, cnt - 1);
        uint32_t u = NODE_TAG(e);
        if ((u - 0x87 < 2) || (u == 0x45)) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(n, e, st);
            cnt = STACK_CNT(st);
            if (cnt == 0) goto done;
        }
        e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0x46) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(n, e, st);
            cnt = STACK_CNT(st);
            if (cnt == 0) goto done;
        }
        e = STACK_ELEM(st, cnt - 1);
        if ((NODE_TAG(e) & 0xfffe) == 0x11e) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(n, e, st);
            cnt = STACK_CNT(st);
            if (cnt == 0) goto done;
        }
        e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0x44) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(n, e, st);
            cnt = STACK_CNT(st);
            if (cnt == 0) goto done;
        }
        e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0x11d) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(n, e, st);
        }
    }
done:
    {
        uint64_t *a = (uint64_t *)sk_003ad0f0(st, 3);
        if (a == 0) n = 0;
        else sk_node_add(n, a, st);
        uint64_t *b = (uint64_t *)sk_003ad0f0(st, 0xdb);
        if (n != 0 && b != 0) {
            sk_node_add(n, b, st);
            sk_node_push(st, 0xf4, n);
        }
    }
}

/* FUN_003aa804 @ 0x3aa804   (est. sk_parse_annotated_letter)
 * Parses a one-letter annotated construct. Most letters select a tag and push
 * the popped 0xf4 element (or a pair) under it; 'G'/'g' delegate to b0004;
 * 'J' delegates to af3c4/af238/af4d4 based on the next letter; 'M'/'m'/'P'
 * build via b0174/b0220 + 4b98; 'S' parses an inner letter mapping to tags
 * 0x136-0x139; 'X'/'x' build an 0xe0 child collection (0xdf wrapper); 'Z'
 * builds a 3-child node via ad3a0/ace50; 'z' selects 0x17/0xaf. Returns node.
 * Confidence: medium */
/* Pop the top two 0xf4 stack elements (if present): *first = top, *second =
 * the one below. Mirrors the aa804 'S'/'A' two-element unwind. */
static void sk_pop_f4_pair(uint64_t *st, uint64_t *first, uint64_t *second)
{
    *first = 0; *second = 0;
    int32_t cnt = STACK_CNT(st);
    if (cnt == 0) return;
    uint32_t i = cnt - 1;
    uint64_t e = (uint64_t)STACK_ELEM(st, i);
    if (NODE_TAG((uint64_t *)e) == 0xf4) {
        STACK_CNT(st) = i;
        *first = e;
        if (i == 0) return;
        uint64_t e2 = (uint64_t)STACK_ELEM(st, i - 1);
        if (NODE_TAG((uint64_t *)e2) == 0xf4) { STACK_CNT(st) = i - 1; *second = e2; }
    } else {
        *first = 0;
        uint64_t e2 = (uint64_t)STACK_ELEM(st, i - 1);
        if (NODE_TAG((uint64_t *)e2) == 0xf4) { STACK_CNT(st) = i - 1; *second = e2; }
    }
}

static uint64_t sk_003aa804(uint64_t *st)
{
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    if (end <= pos) return 0;
    uint64_t npos = pos + 1;
    STREAM_POS(st) = npos;
    uint8_t b = STREAM_DATA(st)[pos];
    if (0x39 < b - 0x41) return 0;
    uint64_t tag, l12 = 0, l10 = 0, l13 = 0;
    switch (b) {
    default: tag = 0x42; break;
    case 'B': tag = 0xaf; break;
    case 'C': tag = 0x17; break;
    case 'D':
        if (STACK_CNT(st) == 0) l12 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l12 = 0;
            else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0x3b, (uint64_t *)l12);
    case 'E': tag = 0x43; break;
    case 'F': case 'H': case 'I': case 'J': case 'N': case 'O': case 'Q':
    case 'R': case 'T': case 'V': case 'W': case '[': case '\\': case ']':
    case '^': case '_': case '`': case 'a': case 'd': case 'h': case 'i':
    case 'k': case 'n': case 'q': case 'r': case 's': case 't': case 'v':
    case 'y':
        return 0;
    case 'G': case 'g':
        return (uint64_t)sk_003b0004(st, (int)(char)b);
    case 'K': tag = 0xb; break;
    case 'L': tag = 0xb0; break;
    case 'M':
        l12 = (uint64_t)sk_003b0174(st);
        if (STACK_CNT(st) == 0) l10 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l10 = 0;
            else { STACK_CNT(st) = i; l10 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push2(st, 0x9a, (uint64_t *)l12, (uint64_t *)l10);
    case 'P':
        l10 = (uint64_t)sk_003b0220(st);
        if (STACK_CNT(st) == 0) l12 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l12 = 0;
            else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push2(st, 0x55, (uint64_t *)l12, (uint64_t *)l10);
    case 'S': {
        if (end <= npos) return 0;
        STREAM_POS(st) = pos + 2;
        uint8_t c2 = STREAM_DATA(st)[npos];
        if (c2 < 0x61) {
            uint64_t first, second;
            if (c2 == 'A') {
                sk_pop_f4_pair(st, &first, &second);
                return (uint64_t)sk_node_push2(st, 0x138, (uint64_t *)second, (uint64_t *)first);
            }
            if (c2 != 'D') return 0;
            sk_pop_f4_pair(st, &first, &second);
            return (uint64_t)sk_node_push2(st, 0x137, (uint64_t *)second, (uint64_t *)first);
        }
        if (c2 != 'a') {
            if (c2 != 'p') {
                if (c2 != 'q') return 0;
                if (STACK_CNT(st) == 0) l12 = 0;
                else {
                    uint32_t i = STACK_CNT(st) - 1;
                    uint64_t *e = STACK_ELEM(st, i);
                    if (NODE_TAG(e) != 0xf4) l12 = 0;
                    else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
                }
                return (uint64_t)sk_node_push(st, 0x135, (uint64_t *)l12);
            }
            if (STACK_CNT(st) == 0) l12 = 0;
            else {
                uint32_t i = STACK_CNT(st) - 1;
                uint64_t *e = STACK_ELEM(st, i);
                if (NODE_TAG(e) != 0xf4) l12 = 0;
                else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
            }
            return (uint64_t)sk_node_push(st, 0x139, (uint64_t *)l12);
        }
        if (STACK_CNT(st) == 0) l12 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l12 = 0;
            else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0x136, (uint64_t *)l12);
    }
    case 'U': tag = 0x102; break;
    case 'X': {
        if (STACK_CNT(st) == 0) return 0;
        uint32_t i = STACK_CNT(st) - 1;
        l13 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l13) != 0x2c) return 0;
        STACK_CNT(st) = i;
        l12 = (uint64_t)sk_003ad3a0(st);
        if (l12 == 0) return 0;
    }
    /* fallthrough 'x' */
    case 'x': {
        uint64_t *p3 = (uint64_t *)sk_003ad3a0(st);
        if (p3 == 0) return 0;
        uint64_t *l4 = sk_node_alloc(st, 1);
        NODE_SETTAG(l4, 0xe0); NODE_SETSUBT(l4, 0);
        uint8_t sub = NODE_SUBT(p3);
        uint64_t u15 = sub;
        if (sub == 1) {
            goto loop;
        } else if (sub == 5) {
            u15 = (uint64_t)(uint32_t)p3[1];
            if ((uint32_t)p3[1] != 0) goto loop;
        } else if (sub == 2) {
            u15 = 2;
            goto loop;
        }
        {
            uint64_t *l10 = sk_node_alloc(st, 1);
            NODE_SETTAG(l10, 0xdf); NODE_SETSUBT(l10, 0);
            sk_node_add(l10, l4, st);
            if (l13 != 0) {
                sk_node_add(l10, (uint64_t *)l13, st);
                sk_node_add(l10, (uint64_t *)l12, st);
            }
            return (uint64_t)sk_node_push(st, 0xf4, l10);
        }
    loop:
        {
            uint64_t i16 = 0;
            do {
                uint8_t s2 = NODE_SUBT(p3);
                uint64_t u8 = s2;
                uint32_t u7 = s2;
                uint64_t *pl14;
                if (u7 == 1) {
                    if (u8 <= i16) { pl14 = 0; }
                    uint64_t *p9 = p3;
                    if (1 < u7 - 1) p9 = (uint64_t *)NODE_DATA(p3);
                    pl14 = (uint64_t *)p9[i16];
                } else {
                    if (u7 == 5) { u8 = (uint64_t)(uint32_t)p3[1]; goto l_aac2; }
                    if (s2 == 2) { u8 = 2; goto l_aac2; }
                    pl14 = 0;
                }
                goto l_after;
            l_aac2:
                if (u8 <= i16) pl14 = 0;
                else {
                    uint64_t *p9 = p3;
                    if (1 < u7 - 1) p9 = (uint64_t *)NODE_DATA(p3);
                    pl14 = (uint64_t *)p9[i16];
                }
            l_after:
                {
                    uint32_t u7b = NODE_SUBT(pl14) - 1;
                    uint64_t *pl11 = pl14;
                    if (1 < u7b) pl11 = (uint64_t *)NODE_DATA(pl14);
                    uint64_t *pu9;
                    if (NODE_TAG(pl11) == 0x80) {
                        if (u7b < 2) {
                            pu9 = (uint64_t *)NODE_DATA(pl14);
                        } else {
                            if ((NODE_SUBT(pl14) == 5) && ((int64_t)pl14[1] != 0)) {
                                pl14 = (uint64_t *)NODE_DATA(pl14);
                                pu9 = (uint64_t *)NODE_DATA(pl14);
                            } else {
                                pu9 = 0;
                            }
                        }
                        uint64_t u5;
                        if (NODE_SUBT(pu9) - 1 < 2) u5 = (uint64_t)NODE_DATA(pu9);
                        else {
                            if ((NODE_SUBT(pu9) == 5) && ((int64_t)pu9[1] != 0)) {
                                pu9 = (uint64_t *)NODE_DATA(pu9);
                                u5 = (uint64_t)NODE_DATA(pu9);
                            } else {
                                u5 = 0;
                            }
                        }
                        pl14 = (uint64_t *)sk_node_push(st, 0xf4, (uint64_t *)u5);
                        tag = 0xe1;
                    } else {
                        tag = 0xe2;
                    }
                    uint64_t *l10 = sk_node_alloc(st, 1);
                    NODE_SETTAG(l10, (uint16_t)tag); NODE_SETSUBT(l10, 0);
                    sk_node_add(l10, pl14, st);
                    sk_node_add(l4, l10, st);
                    i16 = i16 + 1;
                }
            } while (u15 != i16);
        }
        {
            uint64_t *l10 = sk_node_alloc(st, 1);
            NODE_SETTAG(l10, 0xdf); NODE_SETSUBT(l10, 0);
            sk_node_add(l10, l4, st);
            if (l13 != 0) {
                sk_node_add(l10, (uint64_t *)l13, st);
                sk_node_add(l10, (uint64_t *)l12, st);
            }
            return (uint64_t)sk_node_push(st, 0xf4, l10);
        }
    }
    case 'Y': return (uint64_t)sk_003a6090(st, 0xb1);
    case 'Z': {
        l12 = (uint64_t)sk_003ad3a0(st);
        l10 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0x67) { STACK_CNT(st) = i; l10 = (uint64_t)e; }
        }
        l13 = (uint64_t)sk_003ace50(st);
        uint64_t *l4 = sk_node_alloc(st, 1);
        NODE_SETTAG(l4, 1); NODE_SETSUBT(l4, 0);
        if (l10 == 0 || l4 == 0) return 0;
        sk_node_add(l4, (uint64_t *)l10, st);
        if (l13 == 0) return 0;
        sk_node_add(l4, (uint64_t *)l13, st);
        if (l12 == 0) return 0;
        sk_node_add(l4, (uint64_t *)l12, st);
        return (uint64_t)l4;
    }
    case 'b':
        if (STACK_CNT(st) == 0) l12 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l12 = 0;
            else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0xde, (uint64_t *)l12);
    case 'c':
        if (STACK_CNT(st) == 0) l10 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l10 = 0;
            else { STACK_CNT(st) = i; l10 = (uint64_t)e; }
        }
        l12 = (uint64_t)sk_003b02dc(st);
        return (uint64_t)sk_node_push2(st, 0xca, (uint64_t *)l12, (uint64_t *)l10);
    case 'e': {
        uint64_t *l10 = sk_node_alloc(st, 1);
        NODE_SETTAG(l10, 0x41); NODE_SETSUBT(l10, 0);
        return (uint64_t)sk_node_push(st, 0xf4, l10);
    }
    case 'f': tag = 0xea; break;
    case 'j': return (uint64_t)sk_003b0078(st);
    case 'l':
        l12 = (uint64_t)sk_003b02dc(st);
        return (uint64_t)sk_node_push(st, 0xcb, (uint64_t *)l12);
    case 'm':
        l12 = (uint64_t)sk_003b0174(st);
        if (STACK_CNT(st) == 0) l10 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l10 = 0;
            else { STACK_CNT(st) = i; l10 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push2(st, 0x47, (uint64_t *)l12, (uint64_t *)l10);
    case 'o':
        if (STACK_CNT(st) == 0) l12 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l12 = 0;
            else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0x105, (uint64_t *)l12);
    case 'p':
        if (STACK_CNT(st) == 0) l12 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l12 = 0;
            else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0x47, (uint64_t *)l12);
    case 'u':
        if (STACK_CNT(st) == 0) l12 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l12 = 0;
            else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0x106, (uint64_t *)l12);
    case 'w':
        if (STACK_CNT(st) == 0) l12 = 0;
        else {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) != 0xf4) l12 = 0;
            else { STACK_CNT(st) = i; l12 = (uint64_t)e; }
        }
        return (uint64_t)sk_node_push(st, 0x104, (uint64_t *)l12);
    case 'z':
        if (end <= npos) return 0;
        STREAM_POS(st) = pos + 2;
        if (STREAM_DATA(st)[npos] == 'C') tag = 0x17;
        else if (STREAM_DATA(st)[npos] != 'B') return 0;
        else tag = 0xaf;
        sk_003ab218(st, (uint16_t)tag, 1);
        return 0;
    }
    /* default / single-tag pushes */
    if (b == 'F' || b == 'H' || b == 'I' || b == 'J' || b == 'N' || b == 'O' ||
        b == 'Q' || b == 'R' || b == 'T' || b == 'V' || b == 'W') return 0;
    sk_003ab218(st, (uint16_t)tag, 0);
    return 0;
}

/* FUN_003ab40c @ 0x3ab40c   (est. sk_parse_binop)
 * Parses a one-letter binary/operator construct. 'A' builds a 0x22 node over
 * an ident (ac52c) plus a popped element; 'C'/'c' (0x1e) pop a 0xba+0xf4 pair
 * via 4f5c into a node; 'D'(0x20),'E'(0x6a),'F'(0xbd),'P'(0xbc),'W'(0xbe),
 * 'Z'(0x85),'d'(0x34),'e'(0x69),'i'(0x82) build a node over a popped 0xf4;
 * 'M'(b06ac),'m'(0x93),'p'(0x113) delegate to b05c8/b06ac; 'U'(0x48) and 'u'
 * (0x7a) build an extra child over an ident. Returns the node.
 * Confidence: medium */
static uint64_t sk_003ab40c(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    uint8_t b = STREAM_DATA(st)[pos];
    uint64_t tag, l4, l6, l7, l10, pop;
    uint64_t u9 = 0;
    if (b < 0x57) {
        if (0x45 < b) {
            if (b < 0x50) {
                if (b != 'F') {
                    if (b == 'M') return (uint64_t)sk_003b06ac(st);
                    return 0;
                }
                u9 = 0xbd;
                goto push_pop;
            }
            if (b == 'P') { u9 = 0xbc; goto push_pop; }
            if (b != 'U') return 0;
            u9 = 0x48;
            goto build_ident;
        }
        if (0x43 < b) {
            if (b == 'D') u9 = 0x20;
            else {
                if (b != 'E') return 0;
                u9 = 0x6a;
            }
            goto push_pop;
        }
        if (b != 'A') {
            if (b != 'C') return 0;
            u9 = 0x1e;
            goto c_case;
        }
        /* 'A': ident + popped under 0x22 */
        l10 = (uint64_t)sk_003ac52c(st);
        pop = (uint64_t)sk_003ace50(st);
        l6 = (uint64_t)sk_node_push(st, 0x22, (uint64_t *)pop);
        l4 = 0;
        l7 = l6;
        if (l10 == 0) return 0;
    } else {
        if (100 < b) {
            if (b < 0x6d) {
                if (b == 'e') u9 = 0x69;
                else {
                    if (b != 'i') return 0;
                    u9 = 0x82;
                }
                goto push_pop;
            }
            if (b == 'm') { sk_003b05c8(st, 0x93); return 0; }
            if (b == 'p') { sk_003b05c8(st, 0x113); return 0; }
            if (b != 'u') return 0;
            u9 = 0x7a;
            goto build_ident;
        }
        if (b < 99) {
            if (b == 'W') u9 = 0xbe;
            else {
                if (b != 'Z') return 0;
                u9 = 0x85;
            }
            goto push_pop;
        }
        if (b != 99) {
            if (b != 'd') return 0;
            u9 = 0x34;
            goto push_pop;
        }
        u9 = 0x1e;
    c_case: {
        uint32_t cnt = STACK_CNT(st);
        if (cnt == 0) { l10 = 0; l6 = 0; goto c_after; }
        uint32_t i = cnt - 1;
        l10 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l10) == 0xba) {
            STACK_CNT(st) = i;
            cnt = i;
            if (i == 0) { l6 = 0; goto c_after; }
        } else {
            l10 = 0;
        }
        l6 = (uint64_t)STACK_ELEM(st, cnt - 1);
        if (NODE_TAG((uint64_t *)l6) != 0xf4) { l6 = 0; goto c_after; }
        STACK_CNT(st) = cnt - 1;
    c_after:
        l7 = (uint64_t)sk_ctx_op2_v(st, (uint64_t *)l6);
        pop = (uint64_t)sk_003ace50(st);
        l4 = (uint64_t)sk_node_push(st, (int)u9, (uint64_t *)pop);
        if (l7 != 0 && l4 != 0) sk_node_add((uint64_t *)l4, (uint64_t *)l7, st);
        if (l6 == 0) return 0;
        if (l4 == 0) return 0;
        sk_node_add((uint64_t *)l4, (uint64_t *)l6, st);
        l6 = l4;
        l7 = l10;
        goto finish;
    }
    }
    /* fallthrough for 'A' path: attach l10 child */
    if (l7 == 0) return l4;
    sk_node_add((uint64_t *)l6, (uint64_t *)l10, st);
    return l6;
finish:
    if (l7 == 0) return l4;
    sk_node_add((uint64_t *)l6, (uint64_t *)l10, st);
    return l6;
push_pop:
    pop = (uint64_t)sk_003ace50(st);
    return (uint64_t)sk_node_push(st, (int)u9, (uint64_t *)pop);
build_ident:
    l4 = (uint64_t)sk_003ac52c(st);
    l10 = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l10 = (uint64_t)e; }
    }
    pop = (uint64_t)sk_003ace50(st);
    l6 = (uint64_t)sk_node_push(st, (int)u9, (uint64_t *)pop);
    if (l4 == 0) return 0;
    if (l6 == 0) return 0;
    sk_node_add((uint64_t *)l6, (uint64_t *)l4, st);
    if (l10 == 0) return 0;
    sk_node_add((uint64_t *)l6, (uint64_t *)l10, st);
    return l6;
}
static void sk_003ab780(uint64_t *st)
{
    uint64_t u2 = (uint64_t)sk_003ac52c(st);
    uint64_t *top = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        uint16_t t = NODE_TAG(e);
        if (t < 0x34 && ((1ULL << (t & 0x3f)) & 0xf000018000000ULL) != 0) {
            STACK_CNT(st) = i;
            top = e;
        }
    }
    sk_node_push2(st, 0xda, (uint64_t *)u2, top);
}

/* FUN_003ab7f4 @ 0x3ab7f4   (est. sk_parse_e8_annotated)
 * Pops a 0xba + 0xf4 pair (via 4f5c) and a printable element; builds an 0xe8
 * node collecting the printable, the pair result, the 0xf4 element and the
 * 0xba element as children; then runs acfb4 + b03c0. Returns b03c0's value.
 * Confidence: low */
static uint64_t sk_003ab7f4(uint64_t *st)
{
    uint32_t cnt = STACK_CNT(st);
    uint64_t l8 = 0, l9;
    if (cnt != 0) {
        uint32_t i = cnt - 1;
        l8 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l8) == 0xba) {
            STACK_CNT(st) = i;
            cnt = i;
            if (i == 0) goto l868;
        } else {
            l8 = 0;
        }
        l9 = (uint64_t)STACK_ELEM(st, cnt - 1);
        if (NODE_TAG((uint64_t *)l9) == 0xf4) {
            STACK_CNT(st) = cnt - 1;
            goto l86c;
        }
    }
l868:
    l9 = 0;
l86c:
    uint64_t l2 = (uint64_t)sk_ctx_op2_v(st, (uint64_t *)l9);
    uint64_t l3 = (uint64_t)sk_003ace50(st);
    if (l9 == 0) return 0;
    uint64_t *l4 = sk_node_alloc(st, 1);
    NODE_SETTAG(l4, 0xe8); NODE_SETSUBT(l4, 0);
    uint64_t l6 = 0;
    if (l3 != 0 && l4 != 0) {
        sk_node_add(l4, (uint64_t *)l3, st);
        if (l2 != 0) sk_node_add(l4, (uint64_t *)l2, st);
        sk_node_add(l4, (uint64_t *)l9, st);
        l6 = (uint64_t)l4;
        if (l8 != 0) sk_node_add(l4, (uint64_t *)l8, st);
    }
    uint64_t u5 = (uint64_t)sk_003acfb4(st, l6, l9, *(uint8_t *)((char *)st + 0x51));
    return (uint64_t)sk_003b03c0(st, u5);
}

/* FUN_003ab948 @ 0x3ab948   (est. sk_parse_2c_list)
 * Builds a 0x2c list node; when the flag is set, repeatedly parses idents
 * ('z' = 0, 'l' = exit, else '_N_' +1) into 0x26 scalar children until
 * 'l'/end; otherwise a single 0x26 with value 1. Then drains printable stack
 * elements (b0a64 test) as children, finalizes with the sub-type count, and
 * returns the node.
 * Confidence: medium */
static uint64_t sk_003ab948(uint64_t *st, int32_t p2)
{
    uint64_t *l6 = sk_node_alloc(st, 1);
    NODE_SETTAG(l6, 0x2c); NODE_SETSUBT(l6, 0);
    if (p2 != 0) {
        for (;;) {
            uint64_t pos = STREAM_POS(st);
            uint32_t uv;
            if (pos < STREAM_END(st)) {
                char c = STREAM_DATA(st)[pos];
                if (c == 'l') { STREAM_POS(st) = pos + 1; break; }
                if (c == 'z') { STREAM_POS(st) = pos + 1; uv = 0; }
                else {
                    int32_t v = sk_003ac4a4(st);
                    if (v < -1) return 0;
                    uv = (uint32_t)(v + 1);
                }
            } else {
                int32_t v = sk_003ac4a4(st);
                if (v < -1) return 0;
                uv = (uint32_t)(v + 1);
            }
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0x26); NODE_SETSUBT(s, 4);
            s[0] = (uint64_t)uv;
            sk_node_add(l6, s, st);
        }
    } else {
        uint64_t *s = sk_node_alloc(st, 1);
        NODE_SETTAG(s, 0x26); NODE_SETSUBT(s, 4);
        s[0] = 1;
        sk_node_add(l6, s, st);
    }
    uint8_t sub = NODE_SUBT(l6);
    uint32_t u9 = sub;
    if (sub != 1) {
        if (sub == 5) u9 = (uint32_t)l6[1];
        else {
            u9 = 0;
            if (sub == 2) u9 = 2;
        }
    }
    while (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (sk_003b0a64(NODE_TAG(e)) == 0) break;
        STACK_CNT(st) = i;
        sk_node_add(l6, e, st);
    }
    sk_node_finalize(l6, (int)u9);
    return (uint64_t)l6;
}

/* FUN_003abad0 @ 0x3abad0   (est. sk_parse_ident_scalar)
 * If the stack top is a 0x67 scalar, validates each character against an
 * identifier charset table, copies them into a growing buffer, then reads a
 * trailing 'P'/'p'/'i' to select tag 0xb7/0xb9/0x81 and returns a 3-subtype
 * string node over the copied bytes. Returns NULL on invalid input.
 * Confidence: medium */
static uint64_t *sk_003abad0(uint64_t *st)
{
    if (STACK_CNT(st) == 0) return NULL;
    uint32_t i = STACK_CNT(st) - 1;
    uint64_t *e = STACK_ELEM(st, i);
    if (NODE_TAG(e) != 0x67) return NULL;
    STACK_CNT(st) = i;
    uint64_t local50 = 0, local48 = 0;
    int64_t len = (int64_t)e[1];
    char *p = (char *)e[0];
    while (len != 0) {
        char c = *p;
        if (c >= 0) {
            uint32_t u = (uint32_t)c - 0x61;
            if (0x19 < u) return NULL;
            if (((1ULL << (u & 0x3f)) & 0x17007a2ULL) != 0) return NULL;
            /* charset table maps invalid chars -> reject; valid pass through */
        }
        sk_003acd3c((uint64_t *)&local50, (uint8_t *)&c, st);
        p = p + 1;
        len = len - 1;
    }
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st)) {
        STREAM_POS(st) = pos + 1;
        char c = STREAM_DATA(st)[pos];
        uint16_t tag;
        if (c == 'P') tag = 0xb7;
        else if (c == 'p') tag = 0xb9;
        else {
            if (c != 'i') return NULL;
            tag = 0x81;
        }
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, tag); NODE_SETSUBT(n, 3);
        n[0] = local50;
        n[1] = local48 & 0xffffffff;
        return n;
    }
    return NULL;
}

/* FUN_003abc48 @ 0x3abc48   (est. sk_parse_ident_seq)
 * Parses an identifier sequence into a node via ac2d0: 'z' -> (0,0),
 * 's' -> tag 0x57 node, 'd' -> two idents (i2+1, i3), otherwise a single
 * ident. Returns nothing (push only).
 * Confidence: medium */
static uint64_t sk_003abc48(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    uint32_t i2, i3;
    if (pos < STREAM_END(st)) {
        char c = STREAM_DATA(st)[pos];
        if (c == 'z') {
            STREAM_POS(st) = pos + 1;
            i2 = 0; i3 = 0;
            goto go;
        }
        if (c == 's') {
            STREAM_POS(st) = pos + 1;
            uint64_t *n = sk_node_alloc(st, 1);
            NODE_SETTAG(n, 0x57); NODE_SETSUBT(n, 0);
            return (uint64_t)n;
        }
        if (c == 'd') {
            STREAM_POS(st) = pos + 1;
            i2 = (uint32_t)sk_003ac4a4(st);
            i3 = (uint32_t)sk_003ac4a4(st);
            i2 = i2 + 1;
            goto go;
        }
    }
    i2 = (uint32_t)sk_003ac4a4(st);
    i3 = (uint32_t)(i2 + 1);
    i2 = 0;
go:
    return (uint64_t)sk_003ac2d0(st, (int32_t)i2, (uint32_t)i3);
}

/* FUN_003abd1c @ 0x3abd1c   (est. sk_parse_eb_sequence)
 * Builds an 0xeb node; unless the stack top is a 0x120 terminator, drains a
 * run of 0xec items (each optionally prefixed by 0x122, a 0x67->0xed
 * conversion, and a mandatory 0xf4 child) terminated by 0x121; finalizes
 * with 0 and pushes as 0xf4. Returns the pushed node.
 * Confidence: medium */
static uint64_t sk_003abd1c(uint64_t *st)
{
    uint64_t *l3 = sk_node_alloc(st, 1);
    NODE_SETTAG(l3, 0xeb); NODE_SETSUBT(l3, 0);
    if (STACK_CNT(st) != 0 &&
        NODE_TAG(STACK_ELEM(st, STACK_CNT(st) - 1)) == 0x120) {
        STACK_CNT(st) = STACK_CNT(st) - 1;
    } else {
        bool b9;
        do {
            if (STACK_CNT(st) != 0 &&
                NODE_TAG(STACK_ELEM(st, STACK_CNT(st) - 1)) == 0x121) {
                b9 = false;
                STACK_CNT(st) = STACK_CNT(st) - 1;
            } else {
                b9 = true;
            }
            uint64_t *l4 = sk_node_alloc(st, 1);
            NODE_SETTAG(l4, 0xec); NODE_SETSUBT(l4, 0);
            int32_t cnt = STACK_CNT(st);
            if (cnt == 0) return 0;
            uint64_t *l6 = STACK_ELEM(st, cnt - 1);
            if (NODE_TAG(l6) == 0x122) {
                STACK_CNT(st) = cnt - 1;
                sk_node_add(l4, l6, st);
                cnt = STACK_CNT(st);
                if (cnt == 0) return 0;
            }
            uint64_t *e = STACK_ELEM(st, cnt - 1);
            if (NODE_TAG(e) == 0x67) {
                STACK_CNT(st) = cnt - 1;
                uint64_t *conv = sk_node_alloc(st, 1);
                NODE_SETTAG(conv, 0xed); NODE_SETSUBT(conv, 3);
                conv[0] = e[0];
                conv[1] = e[1];
                sk_node_add(l4, conv, st);
                cnt = STACK_CNT(st);
                if (cnt == 0) return 0;
            }
            l6 = STACK_ELEM(st, cnt - 1);
            if (NODE_TAG(l6) != 0xf4) return 0;
            STACK_CNT(st) = cnt - 1;
            sk_node_add(l4, l6, st);
            sk_node_add(l3, l4, st);
        } while (b9);
        sk_node_finalize(l3, 0);
    }
    return (uint64_t)sk_node_push(st, 0xf4, l3);
}

/* FUN_003abef0 @ 0x3abef0   (est. sk_emit_2d_pair)
 * Pops a 0x2c + 0xf4 pair from the stack, builds a 0x2d node from them and
 * pushes it as 0xf4. Returns nothing.
 * Confidence: medium */
static void sk_003abef0(uint64_t *st)
{
    uint32_t cnt = STACK_CNT(st);
    uint64_t l3 = 0, l4;
    if (cnt != 0) {
        uint32_t i = cnt - 1;
        l3 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l3) == 0x2c) {
            STACK_CNT(st) = i;
            cnt = i;
            if (i == 0) goto lf5c;
        } else {
            l3 = 0;
        }
        l4 = (uint64_t)STACK_ELEM(st, cnt - 1);
        if (NODE_TAG((uint64_t *)l4) == 0xf4) {
            STACK_CNT(st) = cnt - 1;
            goto lf60;
        }
    }
lf5c:
    l4 = 0;
lf60:
    uint64_t u2 = (uint64_t)sk_node_push2(st, 0x2d, (uint64_t *)l3, (uint64_t *)l4);
    sk_node_push(st, 0xf4, (uint64_t *)u2);
}

/* FUN_003abf88 @ 0x3abf88   (est. sk_parse_109_code)
 * Reads two bytes from the stream and maps the big-endian pair to a code
 * (0..0x17) via a lookup table ("al","ac","at","de","xx","XX","xX","CP",
 * "Cp","cp","Tk","tk","pr","TK","Cc","Tt","tT","sx","gx","gu","pu","iu",
 * "et","st"). Builds a 0x109 node holding the code scalar plus the popped
 * 0xf4 element. Returns the node.
 * Confidence: high */
static uint64_t sk_003abf88(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    uint8_t c0, c1;
    if (pos < STREAM_END(st)) {
        STREAM_POS(st) = pos + 1;
        c0 = STREAM_DATA(st)[pos];
        pos = pos + 1;
    } else {
        c0 = 0;
    }
    if (pos < STREAM_END(st)) {
        STREAM_POS(st) = pos + 1;
        c1 = STREAM_DATA(st)[pos];
    } else {
        c1 = 0;
    }
    uint16_t pair = (uint16_t)((c0 << 8) | c1);
    uint64_t code;
    switch (pair) {
    case 0x6c61: code = 0; break;    /* "al" */
    case 0x6163: code = 1; break;    /* "ac" */
    case 0x6174: code = 2; break;    /* "at" */
    case 0x6564: code = 3; break;    /* "de" */
    case 0x7878: code = 4; break;    /* "xx" */
    case 0x5858: code = 5; break;    /* "XX" */
    case 0x7858: code = 6; break;    /* "xX" */
    case 0x5043: code = 7; break;    /* "CP" */
    case 0x7043: code = 8; break;    /* "Cp" */
    case 0x7063: code = 9; break;    /* "cp" */
    case 0x6b54: code = 10; break;   /* "Tk" */
    case 0x6b74: code = 11; break;   /* "tk" */
    case 0x7270: code = 12; break;   /* "pr" */
    case 0x4b54: code = 13; break;   /* "TK" */
    case 0x6343: code = 14; break;   /* "Cc" */
    case 0x7454: code = 15; break;   /* "Tt" */
    case 0x5474: code = 16; break;   /* "tT" */
    case 0x7378: code = 17; break;   /* "xs" */
    case 0x6778: code = 18; break;   /* "xg" */
    case 0x6775: code = 19; break;   /* "ug" */
    case 0x7075: code = 20; break;   /* "up" */
    case 0x6975: code = 21; break;   /* "ui" */
    case 0x7465: code = 22; break;   /* "et" */
    case 0x7374: code = 23; break;   /* "st" */
    default: return 0;
    }
    uint64_t *l2 = sk_node_alloc(st, 1);
    NODE_SETTAG(l2, 0x109); NODE_SETSUBT(l2, 0);
    uint64_t *s = sk_node_alloc(st, 1);
    NODE_SETTAG(s, 0x68); NODE_SETSUBT(s, 4);
    s[0] = code;
    sk_node_add(l2, s, st);
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *l4 = STACK_ELEM(st, i);
        if (NODE_TAG(l4) == 0xf4) {
            STACK_CNT(st) = i;
            sk_node_add(l2, l4, st);
            return (uint64_t)l2;
        }
    }
    return 0;
}

/* FUN_003ac6b4 @ 0x3ac6b4   (est. sk_type_name_emit)
 * Maps a type-code letter (param_2) and a flag (param_3) to a Swift type-name
 * string and emits it via sk_003ac600 (tag 0xe7, or 0xbf for the
 * executor/concurrency group, or 0x3f/0x19 for Optional/MainActor). The flag
 * bit pattern selects between base-name and qualified variants. Returns the
 * emitted node.
 * Confidence: high (string-matched) */
static uint64_t sk_003ac6b4(uint64_t *st, int32_t p2, uint32_t p3)
{
    char *name;
    if (p2 == 0x41 && p3 != 1) name = s_AutoreleasingUnsafeMutablePointe_005d6a10;
    else if (p2 == 'a' && (p3 & 1) == 0) name = s_Array_005d6a32;
    else if (p2 == 'b' && (p3 & 1) == 0) name = DAT_005d6a38;
    else if (p2 == 'D' && (p3 & 1) == 0) name = s_Dictionary_005d6a3d;
    else if (p2 == 'd' && (p3 & 1) == 0) name = s_Double_005d6a48;
    else {
        uint32_t f = (p2 == 'f') ? p3 : 1;
        if ((f & 1) == 0) name = s_Float_005d6a4f;
        else {
            f = (p2 == 'h') ? p3 : 1;
            if ((f & 1) == 0) name = DAT_005d6a55;
            else {
                f = (p2 == 'I') ? p3 : 1;
                if ((f & 1) == 0) name = s_DefaultIndices_005d6a59;
                else {
                    f = (p2 == 'i') ? p3 : 1;
                    if ((f & 1) == 0) name = DAT_005d6a68;
                    else {
                        f = (p2 == 'J') ? p3 : 1;
                        if ((f & 1) == 0) name = s_Character_005d6a6c;
                        else if (p2 == 'N' && (p3 & 1) == 0) name = s_ClosedRange_005d6a76;
                        else if (p2 == 'n' && (p3 & 1) == 0) name = s_Range_005d6a82;
                        else if (p2 == 'O' && (p3 & 1) == 0) name = s_ObjectIdentifier_005d6a88;
                        else {
                            f = (p2 == 'P') ? p3 : 1;
                            if ((f & 1) == 0) name = s_UnsafePointer_005d6a99;
                            else if (p2 == 'p' && (p3 & 1) == 0) name = s_UnsafeMutablePointer_005d6aa7;
                            else if (p2 == 'R' && (p3 & 1) == 0) name = s_UnsafeBufferPointer_005d6abc;
                            else if (p2 == 'r' && (p3 & 1) == 0) name = s_UnsafeMutableBufferPointer_005d6ad0;
                            else {
                                f = (p2 == 'S') ? p3 : 1;
                                if ((f & 1) == 0) name = s_String_005d6aeb;
                                else {
                                    f = (p2 == 's') ? p3 : 1;
                                    if ((f & 1) == 0) name = s_Substring_005d6af2;
                                    else if (p2 == 'u' && (p3 & 1) == 0) name = DAT_005d6afc;
                                    else if (p2 == 'V' && (p3 & 1) == 0) name = s_UnsafeRawPointer_005d6b01;
                                    else if (p2 == 'v' && (p3 & 1) == 0) name = s_UnsafeMutableRawPointer_005d6b12;
                                    else if (p2 == 'W' && (p3 & 1) == 0) name = s_UnsafeRawBufferPointer_005d6b2a;
                                    else if (p2 == 'w' && (p3 & 1) == 0) name = s_UnsafeMutableRawBufferPointer_005d6b41;
                                    else if (p2 == 'q' && (p3 & 1) == 0) {
                                        return (uint64_t)sk_003ac600(st, 0x3f, (uint64_t)s_Optional_005d4e8b);
                                    }
                                    else if (p2 == 'B' && (p3 & 1) == 0) name = s_BinaryFloatingPoint_005d6b5f;
                                    else {
                                        f = (p2 == 'E') ? p3 : 1;
                                        if ((f & 1) == 0) name = s_Encodable_005d6b73;
                                        else {
                                            f = (p2 == 'e') ? p3 : 1;
                                            if ((f & 1) == 0) name = s_Decodable_005d6b7f;
                                            else {
                                                f = (p2 == 'F') ? p3 : 1;
                                                if ((f & 1) == 0) name = s_FloatingPoint_005d6b89;
                                                else {
                                                    f = (p2 == 'G') ? p3 : 1;
                                                    if ((f & 1) == 0) name = s_RandomNumberGenerator_005d6b97;
                                                    else if (p2 == 'H' && (p3 & 1) == 0) name = s_Hashable_005d6bad;
                                                    else if (p2 == 'j' && (p3 & 1) == 0) name = s_Numeric_005d6bb6;
                                                    else if (p2 == 'K' && (p3 & 1) == 0) name = s_BidirectionalCollection_005d6bbe;
                                                    else if (p2 == 'k' && (p3 & 1) == 0) name = s_RandomAccessCollection_005d6bd6;
                                                    else if (p2 == 'L' && (p3 & 1) == 0) name = s_Comparable_005d6bed;
                                                    else if (p2 == 'l' && (p3 & 1) == 0) name = s_Collection_005d6bf8;
                                                    else {
                                                        f = (p2 == 'M') ? p3 : 1;
                                                        if ((f & 1) == 0) name = s_MutableCollection_005d6c03;
                                                        else if (p2 == 'm' && (p3 & 1) == 0) name = s_RangeReplaceableCollection_005d6c17;
                                                        else if (p2 == 'Q' && (p3 & 1) == 0) name = s_Equatable_005d6c32;
                                                        else {
                                                            f = (p2 == 'T') ? p3 : 1;
                                                            if ((f & 1) == 0) name = s_Sequence_005d6c3c;
                                                            else {
                                                                f = (p2 == 't') ? p3 : 1;
                                                                if ((f & 1) == 0) name = s_IteratorProtocol_005d6c45;
                                                                else if (p2 == 'U' && (p3 & 1) == 0) name = s_UnsignedInteger_005d6c56;
                                                                else if (p2 == 'X' && (p3 & 1) == 0) name = s_RangeExpression_005d6c66;
                                                                else if (p2 == 'x' && (p3 & 1) == 0) name = s_Strideable_005d6c76;
                                                                else if (p2 == 'Y' && (p3 & 1) == 0) name = s_RawRepresentable_005d6c81;
                                                                else if (p2 == 'y' && (p3 & 1) == 0) name = s_StringProtocol_005d6c92;
                                                                else if (p2 == 'Z' && (p3 & 1) == 0) name = s_SignedInteger_005d6ca1;
                                                                else if (p2 == 'z' && (p3 & 1) == 0) name = s_BinaryInteger_005d6caf;
                                                                else if (p3 == 0 && p2 == 'C') name = s_CheckedContinuation_005d6cc3;
                                                                else if (p3 == 0 && p2 == 'c') name = s_UnsafeContinuation_005d6cd9;
                                                                else if (p3 == 0 && p2 == 'E') name = s_CancellationError_005d6cec;
                                                                else if (p3 == 0 && p2 == 'e') name = s_UnownedSerialExecutor_005d6cfe;
                                                                else if (p3 == 0 && p2 == 'G') name = s_TaskGroup_005d6d2c;
                                                                else if (p3 == 0 && p2 == 'g') name = s_ThrowingTaskGroup_005d6d36;
                                                                else if (p3 == 0 && p2 == 'J') name = s_UnownedJob_005d6d79;
                                                                else if (p3 != 0 && p2 == 'M') {
                                                                    return (uint64_t)sk_003ac600(st, 0x19, (uint64_t)s_MainActor_005d6d84);
                                                                }
                                                                else if (p3 == 0 && p2 == 'P') name = s_TaskPriority_005d6d8e;
                                                                else if (p3 == 0 && p2 == 'S') name = s_AsyncStream_005d6d9b;
                                                                else if (p3 == 0 && p2 == 's') name = s_AsyncThrowingStream_005d6da7;
                                                                else if (p3 == 0 && p2 == 'T') name = DAT_005d4ec0;
                                                                else if (p3 == 0 && p2 == 't') name = s_UnsafeCurrentTask_005d6dbb;
                                                                else if (p3 == 0 && p2 == 'A') name = s_Actor_005d6cbd;
                                                                else if (p3 == 0 && p2 == 'F') name = s_Executor_005d6d14;
                                                                else if (p3 == 0 && p2 == 'f') name = s_SerialExecutor_005d6d1d;
                                                                else if (p3 == 0 && p2 == 'h') name = s_TaskExecutor_005d6d48;
                                                                else if (p3 == 0 && p2 == 'I') name = s_AsyncIteratorProtocol_005d6d55;
                                                                else if (p3 == 0 && p2 == 'i') name = s_AsyncSequence_005d6d6b;
                                                                else return 0;
                                                                return (uint64_t)sk_003ac600(st, 0xbf, (uint64_t)name);
                                                            }
                                                            return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                                                        }
                                                        return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                                                    }
                                                    return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                                                }
                                                return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                                            }
                                            return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                                        }
                                        return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                                    }
                                    return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                                }
                                return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                            }
                            return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                        }
                        return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                    }
                    return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
                }
                return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
            }
            return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
        }
        return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
    }
    return (uint64_t)sk_003ac600(st, 0xe7, (uint64_t)name);
}

/* FUN_003acefc @ 0x3acefc   (est. sk_pop_value_tls)
 * Pops the thread-local stream's value via sk_stream_pop(); returns it only
 * if it is a printable leaf (sk_tag_is_leaf), else 0.
 * Confidence: medium */
static uint64_t sk_003acefc(void)
{
    uint64_t v = (uint64_t)sk_stream_pop(0);
    if (v == 0 || (sk_003acf38(NODE_TAG((uint64_t *)v)) & 1) == 0) v = 0;
    return v;
}

/* FUN_003ad61c @ 0x3ad61c   (est. sk_emit_23_pair)
 * Gets a value (663c) and pops a 0xf4 element, building a 0x23 node from
 * (element, value). Returns nothing (push only).
 * Confidence: medium */
static void sk_003ad61c(uint64_t *st)
{
    uint64_t v = sk_val_get(0);
    uint64_t *top = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; top = e; }
    }
    sk_node_push2(st, 0x23, top, (uint64_t *)v);
}

/* FUN_003ad874 @ 0x3ad874   (est. sk_recurse_child_collect)
 * Recursively rebuilds a node from its child table: given a node and a child
 * array (param_3) indexed by param_4, collects the trailing children and
 * their recursive results into a fresh 0xf4 wrapper, then repushes the node
 * under a type-mapped tag (0xd/0xe/0xf/0x10/0x11/0x12/0x13 for tags
 * 0x19/0x1e/0x3f/0x4e/0xb1/0xbf/0xe7/0xf6, else 0x49 dispatch). Returns the
 * rebuilt node or NULL.
 * Confidence: medium */
static uint64_t *sk_003ad874(uint64_t *st, uint64_t *p2, uint64_t *p3, uint64_t p4)
{
    uint32_t cnt = *(uint32_t *)(p3 + 1);
    uint64_t u14 = 0, u3 = 0;
    uint64_t *next = 0;
    if (p2 == 0 || cnt <= p4) return 0;
    if (NODE_TAG(p2) == 0xf5 || NODE_TAG(p2) == 0xc0) {
        uint64_t *l4 = sk_node_alloc(st, 1);
        NODE_SETTAG(l4, 0xf7); NODE_SETSUBT(l4, 0);
        cnt = *(uint32_t *)(p3 + 1);
        uint64_t u14 = cnt - 1;
        if (p4 <= u14 && cnt != 0) {
            do {
                uint64_t *elem = *(uint64_t **)(*(uint64_t *)p3 + u14 * 8);
                uint8_t b = NODE_SUBT(elem);
                uint64_t *pu15 = elem;
                uint64_t *pu12;
                if (b - 1 < 2) {
                    if (b == 1) pu12 = elem + 1;
                    else if (b == 2) pu12 = elem + 2;
                    else {
                        if (b == 5) { pu12 = (uint64_t *)NODE_DATA(elem); goto l948; }
                        pu12 = 0;
                    }
                } else {
                    if (b != 5) { pu15 = 0; goto l92c; }
                    pu12 = (uint64_t *)NODE_DATA(elem);
                    pu15 = pu12;
                l948:
                    pu12 = pu12 + (uint32_t)elem[1];
                }
            l92c:
                if (pu15 != pu12) {
                    do {
                        next = pu15 + 1;
                        sk_node_add(l4, (uint64_t *)*pu15, st);
                        pu15 = next;
                    } while (next != pu12);
                    cnt = *(uint32_t *)(p3 + 1);
                }
                u3 = (uint32_t)u14 - 1;
                u14 = u3;
            } while (p4 <= u14 && u3 <= cnt && (p4 > u14 || cnt != u3));
        }
        uint64_t *pl5 = sk_node_alloc(st, 1);
        NODE_SETTAG(pl5, 0xf4); NODE_SETSUBT(pl5, 0);
        sk_node_add(pl5, p2, st);
        uint64_t u6 = 0x11;
        goto l9d0;
    }
    uint64_t *pl9 = p2;
    if (1 < NODE_SUBT(p2) - 1) {
        if (NODE_SUBT(p2) != 5) return 0;
        if ((int32_t)p2[1] == 0) return 0;
        pl9 = (uint64_t *)NODE_DATA(p2);
    }
    pl9 = (uint64_t *)*pl9;
    u3 = sk_003adcd8(p2);
    uint64_t *l4 = *(uint64_t **)(*(uint64_t *)p3 + p4 * 8);
    uint64_t *pl5 = p2;
    if ((uint64_t)cnt <= p4 + u3) goto lbec;
    if (NODE_TAG(pl9) != 0x49) {
        uint64_t *l7 = (uint64_t *)sk_003ad874(st, pl9, p3, p4);
        goto lb38;
    }
    pl5 = pl9;
    uint64_t *l7;
    if (NODE_SUBT(pl9) == 2) l7 = (uint64_t *)pl9[1];
    else {
        if (NODE_SUBT(pl9) == 5 && 1 < (uint32_t)pl9[1]) {
            pl5 = (uint64_t *)NODE_DATA(pl9);
            l7 = (uint64_t *)pl5[1];
        } else {
            l7 = 0;
        }
    }
    uint64_t *u6 = (uint64_t *)sk_003ad874(st, l7, p3, p4);
    pl5 = pl9;
    if (NODE_SUBT(pl9) - 1 < 2) l7 = (uint64_t *)*pl5;
    else {
        if (NODE_SUBT(pl9) == 5 && (int32_t)pl9[1] != 0) {
            pl5 = (uint64_t *)NODE_DATA(pl9);
            l7 = (uint64_t *)*pl5;
        } else {
            l7 = 0;
        }
    }
    l7 = (uint64_t *)sk_node_push2(st, 0x49, l7, u6);
    if (NODE_SUBT(pl9) == 5 && (int32_t)pl9[1] == 3 && l7 != 0 &&
        *(uint64_t *)(NODE_DATA(pl9) + 0x10) != 0) {
        sk_node_add(l7, (uint64_t *)*(uint64_t *)(NODE_DATA(pl9) + 0x10), st);
    }
lb38:
    pl5 = (uint64_t *)sk_node_push(st, NODE_TAG(p2), l7);
    if (pl5 == 0) return 0;
    u14 = 1;
    do {
        uint8_t b = NODE_SUBT(p2);
        uint64_t u10 = b;
        uint32_t u8 = b;
        uint64_t u13;
        if (b == 1) u13 = 1;
        else if (b == 5) u13 = (uint64_t)(uint32_t)p2[1];
        else {
            if (u8 != 2) goto lbec;
            u13 = 2;
        }
        if (u13 <= u14) goto lbec;
        if (u8 == 1) {
        lbb4:
            if (u14 < u10) {
                uint64_t *p9 = p2;
                if (1 < u8 - 1) p9 = (uint64_t *)NODE_DATA(p2);
                if (p9[u14] != 0) sk_node_add(pl5, (uint64_t *)p9[u14], st);
            }
        } else {
            if (u8 == 5) { u10 = (uint64_t)(uint32_t)p2[1]; goto lbb4; }
            if (u8 == 2) { u10 = 2; goto lbb4; }
        }
        u14 = u14 + 1;
    } while (true);
lbec:
    if (u3 == 0) return pl5;
    if (1 < NODE_SUBT(l4) - 1) {
        if (NODE_SUBT(l4) != 5) return pl5;
        if (*(int32_t *)(l4 + 1) == 0) return pl5;
    }
    {
        uint16_t t = NODE_TAG(pl5);
        uint64_t u6;
        if (t < 0xb1) {
            if (t < 0x3f) {
                if (t == 0x19) u6 = 0xd;
                else if (t != 0x1e) return 0;
                else u6 = 0x13;
            } else {
                if (t == 0x3f) u6 = 0xe;
                else if (t != 0x4e) return 0;
                else u6 = 0x13;
            }
        } else {
            if (t < 0xe7) {
                if (t == 0xb1) u6 = 0x11;
                else if (t != 0xbf) return 0;
                else u6 = 0x10;
            } else if (t == 0xf6) u6 = 0x12;
            else {
                if (t != 0xe7) return 0;
                u6 = 0xf;
            }
        lcb8:
            pl5 = (uint64_t *)sk_node_push(st, 0xf4, pl5);
        }
    l9d0:
        return (uint64_t *)sk_node_push2(st, (int)u6, pl5, l4);
    }
}

/* FUN_003ae414 @ 0x3ae414   (est. sk_emit_2e_wrapped)
 * Gets a value via ae658; wraps param_2 (or pops a 0xf4 element when
 * param_2 is NULL) into an 0x2e node and pushes as 0xf4. Returns nothing.
 * Confidence: medium */
static uint64_t sk_003ae414(uint64_t *st, uint64_t p2)
{
    uint64_t u2 = sk_003ae658(st);
    uint64_t *l3;
    if (p2 == 0) {
        l3 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l3 = e; }
        }
    } else {
        l3 = sk_node_alloc(st, 1);
        NODE_SETTAG(l3, 0xf4); NODE_SETSUBT(l3, 0);
        sk_node_add(l3, (uint64_t *)p2, st);
    }
    uint64_t u2r = (uint64_t)sk_node_push2(st, 0x2e, l3, (uint64_t *)u2);
    return (uint64_t)sk_node_push(st, 0xf4, (uint64_t *)u2r);
}

/* FUN_003ae734 @ 0x3ae734   (est. sk_collect_children_60)
 * Builds a child collection node via ae9e0; copies the children of param_3
 * into it, then reads a child table (ad3a0) and wraps each of its children as
 * a 0x60 node added to the collection. Returns the collection node.
 * Confidence: medium */
static uint64_t sk_003ae734(uint64_t *st, uint64_t p2, uint64_t *p3)
{
    uint64_t *l2 = (uint64_t *)sk_003ae9e0(st, 0);
    if (l2 == 0) return 0;
    if (p3 != 0) {
        uint8_t b = NODE_SUBT(p3);
        uint64_t *pu8 = p3;
        uint64_t *pu5;
        if (b - 1 < 2) {
            if (b == 1) pu5 = p3 + 1;
            else if (b == 2) pu5 = p3 + 2;
            else {
                if (b == 5) { pu5 = (uint64_t *)NODE_DATA(p3); goto a7a8; }
                pu5 = 0;
            }
        } else {
            if (b != 5) { pu8 = 0; goto a78c; }
            pu5 = (uint64_t *)NODE_DATA(p3);
            pu8 = pu5;
        a7a8:
            pu5 = pu5 + (uint32_t)p3[1];
        }
    a78c:
        for (; pu8 != pu5; pu8 = pu8 + 1) {
            sk_node_add(l2, (uint64_t *)*pu8, st);
        }
    }
    uint64_t *pl3 = (uint64_t *)sk_003ad3a0(st);
    if (pl3 == 0) return 0;
    uint8_t b = NODE_SUBT(pl3);
    uint64_t *pl7 = pl3;
    uint64_t *pl6;
    if (b - 1 < 2) {
        if (b == 1) pl6 = pl3 + 1;
        else if (b == 2) pl6 = pl3 + 2;
        else {
            if (b != 5) { pl6 = 0; goto a884; }
            pl6 = (uint64_t *)NODE_DATA(pl3);
        }
    } else {
        if (b != 5) { pl7 = 0; goto a884; }
        pl6 = (uint64_t *)NODE_DATA(pl3);
        pl7 = pl6;
    }
    pl6 = pl6 + (uint32_t)pl3[1];
a884:
    for (; pl7 != pl6; pl7 = pl7 + 1) {
        uint64_t u4 = (uint64_t)sk_node_push(st, 0x60, (uint64_t *)*pl7);
        sk_node_add(l2, (uint64_t *)u4, st);
    }
    return (uint64_t)l2;
}

/* FUN_003ae8a0 @ 0x3ae8a0   (est. sk_parse_collection_body)
 * Backs up one stream position, builds a 0x5d node, then parses a run of
 * 't'-prefixed decimal lengths as 0x162 scalar children (clamped to 0xffffffff
 * +1). Then reads a trailing 'B'/'g'/'G' to select the subtype tag
 * (0x5f/0x5d/0x5e) and delegates to ae734. Returns the resulting node.
 * Confidence: medium */
static uint64_t sk_003ae8a0(uint64_t *st)
{
    STREAM_POS(st) = STREAM_POS(st) - 1;
    uint64_t *l3 = sk_node_alloc(st, 1);
    NODE_SETTAG(l3, 0x5d); NODE_SETSUBT(l3, 0);
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    char c;
    if (pos < end) {
        c = STREAM_DATA(st)[pos];
        while (c == 't') {
            STREAM_POS(st) = pos + 1;
            uint32_t v = (uint32_t)sk_003ac430(st);
            if (0x7fffffff < v) v = 0xffffffff;
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0x162); NODE_SETSUBT(s, 4);
            s[0] = (uint64_t)(v + 1);
            sk_node_add(l3, s, st);
            end = STREAM_END(st);
            pos = STREAM_POS(st);
            if (end <= pos) break;
            c = STREAM_DATA(st)[pos];
        }
    }
    if (end <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    c = STREAM_DATA(st)[pos];
    uint64_t tag;
    if (c == 'B') tag = 0x5f;
    else if (c == 'g') tag = 0x5d;
    else {
        if (c != 'G') return 0;
        tag = 0x5e;
    }
    return (uint64_t)sk_003ae734(st, tag, l3);
}

/* FUN_003ae9e0 @ 0x3ae9e0   (est. sk_parse_qualifiers)
 * Parses an optional 'q'/'a'/'r' qualifier prefix, then a byte that must be
 * a hex digit (0x3a..0x14 range test). Builds a node with the given tag and
 * children: 0xe5 if 'q', 0x169 if 'a', 0x16a if 'r', and an 0xe4 scalar
 * holding the byte's low nibble. Returns the node or 0.
 * Confidence: medium */
static uint64_t sk_003ae9e0(uint64_t *st, uint16_t p2)
{
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    bool b3 = false, b4 = false, b5 = false;
    if (pos < end && STREAM_DATA(st)[pos] == 'q') { pos = pos + 1; STREAM_POS(st) = pos; b3 = true; }
    if (pos < end && STREAM_DATA(st)[pos] == 'a') { pos = pos + 1; STREAM_POS(st) = pos; b4 = true; }
    if (pos < end && STREAM_DATA(st)[pos] == 'r') { pos = pos + 1; STREAM_POS(st) = pos; b5 = true; }
    if (pos < end) {
        STREAM_POS(st) = pos + 1;
        uint8_t b = STREAM_DATA(st)[pos];
        if (0xfffffff5 < (uint8_t)(b - 0x3a)) {
            uint64_t *l6 = sk_node_alloc(st, 1);
            NODE_SETTAG(l6, p2); NODE_SETSUBT(l6, 0);
            if (b3) {
                uint64_t *c = sk_node_alloc(st, 1);
                NODE_SETTAG(c, 0xe5); NODE_SETSUBT(c, 0);
                sk_node_add(l6, c, st);
            }
            if (b4) {
                uint64_t *c = sk_node_alloc(st, 1);
                NODE_SETTAG(c, 0x169); NODE_SETSUBT(c, 0);
                sk_node_add(l6, c, st);
            }
            if (b5) {
                uint64_t *c = sk_node_alloc(st, 1);
                NODE_SETTAG(c, 0x16a); NODE_SETSUBT(c, 0);
                sk_node_add(l6, c, st);
            }
            uint64_t *s = sk_node_alloc(st, 1);
            NODE_SETTAG(s, 0xe4); NODE_SETSUBT(s, 4);
            s[0] = (uint64_t)b & 0xf;
            sk_node_add(l6, s, st);
            return (uint64_t)l6;
        }
    }
    return 0;
}

/* FUN_003aebb0 @ 0x3aebb0   (est. sk_parse_typed_collection)
 * Parses a typed collection header via ae9e0(0x4f). If its first child tag is
 * not 0x16a, drains a run of f99c(0x50) children (or a '_' stop). Then
 * requires an 'n' or f99c(0x51) child. Walks the child array; for each 0x50
 * element, processes its 0x52-typed sub-children, popping 0x67/0xf4 stack
 * elements into them per a rule set (tag 2, 4, 5, 9, 10). Finalizes each 0x50
 * node. Returns the collection node.
 * Confidence: low */
static uint64_t *sk_003aebb0(uint64_t *st)
{
    uint64_t *pl3 = (uint64_t *)sk_003ae9e0(st, 0x4f);
    if (pl3 != 0) {
        uint64_t *pl5 = pl3;
        if (1 < NODE_SUBT(pl3) - 1) pl5 = (uint64_t *)NODE_DATA(pl3);
        if (NODE_TAG(pl5) == 0x16a) return pl3;
        for (;;) {
            uint64_t pos = STREAM_POS(st);
            if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == '_') {
                STREAM_POS(st) = pos + 1;
                goto lc58;
            }
            uint64_t *l4 = (uint64_t *)sk_003af99c(st, 0x50);
            if (l4 == 0) break;
            sk_node_add(pl3, l4, st);
        }
        pl3 = 0;
    }
lc58:
    {
        uint64_t pos = STREAM_POS(st);
        if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'n') {
            STREAM_POS(st) = pos + 1;
            if (pl3 == 0) return 0;
        } else {
            uint64_t *l4 = (uint64_t *)sk_003af99c(st, 0x51);
            if (pl3 == 0) return 0;
            if (l4 == 0) return 0;
            sk_node_add(pl3, l4, st);
        }
    }
    uint8_t b = NODE_SUBT(pl3);
    uint64_t u13 = b;
    if (b != 1) {
        if (b == 5) {
            u13 = (uint64_t)(uint32_t)pl3[1];
            if ((uint32_t)pl3[1] == 0) return pl3;
        } else {
            if (b != 2) return pl3;
            u13 = 2;
        }
    }
    uint64_t u14 = 0;
    do {
        b = NODE_SUBT(pl3);
        uint64_t u8 = b;
        uint32_t u7 = b;
        uint64_t *pu11;
        if (u7 == 1) {
            if (u8 <= u13 + ~u14) goto led30;
            uint64_t *pl5 = pl3;
            if (1 < u7 - 1) pl5 = (uint64_t *)NODE_DATA(pl3);
            pu11 = (uint64_t *)pl5[u13 + ~u14];
        } else {
            if (u7 == 5) { u8 = (uint64_t)(uint32_t)pl3[1]; goto led08; }
            if (b == 2) { u8 = 2; goto led08; }
        led30:
            pu11 = 0;
        }
    led08:
        if (pu11 != 0 && NODE_TAG(pu11) == 0x50) {
            b = NODE_SUBT(pu11);
            u8 = b;
            uint64_t *pu12 = 0;
            if (b == 1) {
            led6c:
                {
                    uint64_t u15 = 0;
                    pu12 = pu11;
                    do {
                        b = NODE_SUBT(pu11);
                        uint64_t u9 = b;
                        uint32_t u7b = b;
                        uint32_t *pu6;
                        if (u7b == 1) {
                            if (u9 <= u8 + ~u15) goto ledc4;
                            uint64_t *pu10 = pu11;
                            if (1 < u7b - 1) pu10 = (uint64_t *)NODE_DATA(pu11);
                            pu6 = (uint32_t *)pu10[u8 + ~u15];
                        } else {
                            if (u7b == 5) { u9 = (uint64_t)(uint32_t)pu11[1]; goto led9c; }
                            if (b == 2) { u9 = 2; goto led9c; }
                        ledc4:
                            pu6 = 0;
                        }
                    led9c:
                        if (pu6 != 0 && NODE_TAG((uint64_t *)pu6 + 0x10) == 0x52) {
                            uint32_t t = pu6[0];
                            if ((int32_t)t < 5) {
                                if (1 < t && t != 4) goto lef28;
                                /* tag 2 or 4: pop 0x67 */
                                uint32_t cnt = STACK_CNT(st);
                            leeec:
                                if (cnt != 0) {
                                    cnt = cnt - 1;
                                    uint64_t *e = STACK_ELEM(st, cnt);
                                    if (NODE_TAG(e) == 0x67) {
                                    lef0c:
                                        STACK_CNT(st) = cnt;
                                        if (pu12 != 0) sk_node_add(pu12, e, st);
                                    }
                                }
                            } else if (t == 10) {
                                if (STACK_CNT(st) != 0) {
                                    uint32_t i = STACK_CNT(st) - 1;
                                    uint64_t *e = STACK_ELEM(st, i);
                                    if (NODE_TAG(e) == 0xf4) goto lef0c;
                                }
                            } else if (t == 9) {
                                /* pop 0xf4 then 0x67 elements into pu12 per the
                                 * decompile's 0xeeeb8/0xeeec/0xeef0 state machine */
                                uint32_t cnt = STACK_CNT(st);
                                if (cnt != 0) {
                                    uint32_t i = cnt - 1;
                                    uint64_t *e = STACK_ELEM(st, i);
                                    if (NODE_TAG(e) == 0xf4) {
                                        STACK_CNT(st) = i;
                                        cnt = i;
                                        if (pu12 != 0) { sk_node_add(pu12, e, st); cnt = STACK_CNT(st); }
                                        if (cnt != 0) goto b8;
                                        goto eee8;
                                    }
                                    pu12 = 0;
                                b8:
                                    cnt = cnt - 1;
                                    e = STACK_ELEM(st, cnt);
                                    if (NODE_TAG(e) != 0xf4) goto eee8;
                                    STACK_CNT(st) = cnt;
                                    if (pu12 != 0) { sk_node_add(pu12, e, st); goto ef0; }
                                ef0:
                                    /* reload count and pop 0x67 elements */
                                    cnt = STACK_CNT(st);
                                    if (cnt != 0) {
                                        cnt = cnt - 1;
                                        e = STACK_ELEM(st, cnt);
                                        if (NODE_TAG(e) == 0x67) {
                                        eec2:
                                            STACK_CNT(st) = cnt;
                                            if (pu12 != 0) sk_node_add(pu12, e, st);
                                        }
                                    }
                                    goto done9;
                                eee8:
                                    pu12 = 0;
                                eec:
                                    cnt = STACK_CNT(st);
                                    if (cnt != 0) {
                                        cnt = cnt - 1;
                                        e = STACK_ELEM(st, cnt);
                                        if (NODE_TAG(e) == 0x67) goto eec2;
                                    }
                                done9:
                                    ;
                                }
                            } else if (t == 5) {
                                uint32_t cnt = STACK_CNT(st);
                                while (STACK_CNT(st) != 0) {
                                    uint32_t i = STACK_CNT(st) - 1;
                                    uint64_t *e = STACK_ELEM(st, i);
                                    if (NODE_TAG(e) != 0xf4) break;
                                    STACK_CNT(st) = i;
                                    if (pu12 != 0) { sk_node_add(pu12, e, st); cnt = STACK_CNT(st); }
                                }
                                goto leeec;
                            }
                            /* fallthrough tag not handled -> pu12 = 0 */
                            pu12 = 0;
                        }
                    lef28:
                        u15 = u15 + 1;
                    } while (u15 != u8);
                    if (pu12 == 0) return 0;
                }
            } else {
                if (b == 5) {
                    u8 = (uint64_t)(uint32_t)pu11[1];
                    if ((uint32_t)pu11[1] != 0) goto led6c;
                } else if (b == 2) {
                    u8 = 2;
                    goto led6c;
                }
                u8 = 0;
            }
            sk_node_finalize(pu11, (int)u8);
        }
        u14 = u14 + 1;
        if (u14 == u13) return pl3;
    } while (true);
}

/* FUN_003aef74 @ 0x3aef74   (est. sk_stream_advance_match)
 * If the remaining stream bytes are at least param_3 and (when param_3 != 0)
 * they don't match param_2, returns 0; else advances the position by param_3
 * and returns 1. Used to consume/verify literal runes.
 * Confidence: high */
static uint64_t sk_003aef74(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    uint64_t lim = (pos <= end) ? end : pos;
    if ((end - lim < p3) ||
        (p3 != 0 && sk_memcmp(STREAM_DATA(st) + lim, (const void *)p2, p3) != 0)) {
        return 0;
    }
    STREAM_POS(st) = pos + p3;
    return 1;
}

/* FUN_003aefe4 @ 0x3aefe4   (est. sk_push_into_vec)
 * Appends one word to a growable word vector (param_1[0]=ptr, [1]=count,
 * [2]=cap), growing via b10a8 and releasing the old buffer via sk_lock.
 * Returns nothing.
 * Confidence: medium */
static void sk_003aefe4(uint64_t *buf, uint64_t *p)
{
    uint64_t *cap = (uint64_t *)buf[2];
    uint64_t *cnt = (uint64_t *)buf[1];
    uint64_t *newend;
    if (cnt < cap) {
        *cnt = *p;
        newend = cnt + 1;
    } else {
        uint64_t base = buf[0];
        uint64_t off = (uint64_t)cnt - base;
        uint64_t n = (off >> 3) + 1;
        if (n >> 0x3d != 0) sk_fatal();
        uint64_t curcap = (uint64_t)cap - base;
        uint64_t need = (uint64_t)curcap >> 2;
        if (need <= n) need = n;
        if (0x7ffffffffffffff7 < curcap) need = 0x1fffffffffffffff;
        uint64_t nb = 0, ncount = off;
        if (need != 0) {
            nb = (uint64_t)sk_vec_grow(buf + 2, need);
            base = buf[0];
            ncount = (uint64_t)((uint64_t *)buf[1] - (uint64_t *)base) ;
            ncount = ncount >> 3;
        }
        uint64_t *newbase = (uint64_t *)nb;
        newend = (uint64_t *)(nb + off);
        uint64_t *dst = newend + 1;
        *newend = *p;
        sk_memmove_fast((uint64_t *)(nb) - ncount, (void *)base, off);
        uint64_t oldbase = base;
        *buf = (uint64_t)((uint64_t *)(nb) - ncount);
        buf[1] = (uint64_t)dst;
        uint64_t oldcap = buf[2];
        buf[2] = nb + (uint64_t)((uint64_t *)nb)[0] * 8;
        if (oldbase != 0) sk_lock((void *)oldbase, (long)oldcap - (long)oldbase);
    }
    buf[1] = (uint64_t)newend;
}

/* FUN_003af0cc @ 0x3af0cc   (est. sk_parse_short_ident)
 * Parses a compact '_'-terminated identifier into a growable byte vector
 * (param_1[0]=ptr, [1]=count, [2]=cap). A leading '_' yields an empty vector.
 * Otherwise reads a run of charset letters (via 1130a0) into local_58 and
 * stores [ptr,count,cap] into param_1. Returns nothing.
 * Confidence: medium */
static void sk_003af0cc(uint64_t *buf, uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st)) {
        if (STREAM_DATA(st)[pos] == '_') {
            STREAM_POS(st) = pos + 1;
            buf[1] = 0; buf[2] = 0; buf[0] = 0;
            return;
        }
        uint64_t local58 = 0, stk50 = 0, local48 = 0;
        STREAM_POS(st) = pos + 1;
        uint8_t b = STREAM_DATA(st)[pos];
        uint32_t u5 = b - 0x61;
        if (u5 < 0x10 && ((1ULL << (u5 & 0x1f)) & 0xd001ULL) != 0) {
            sk_vec_byte_append((uint64_t *)&local58, (uint8_t)b);
            for (;;) {
                pos = STREAM_POS(st);
                if (pos < STREAM_END(st)) {
                    char c = STREAM_DATA(st)[pos];
                    STREAM_POS(st) = pos + 1;
                    if (c == '_') {
                        buf[1] = stk50;
                        buf[0] = local58;
                        buf[2] = local48;
                        return;
                    }
                    b = STREAM_DATA(st)[pos];
                    u5 = (uint32_t)(char)b;
                    uint32_t u4 = b - 0x62;
                    if (0xc < u4 || ((1ULL << (u4 & 0x1f)) & 0x1021ULL) == 0) goto l1c4;
                    sk_vec_byte_append((uint64_t *)&local58, (uint8_t)u5);
                } else {
                    u5 = 0;
                l1c4:
                    buf[0] = 0; buf[1] = 0; buf[2] = 0;
                }
                u5 = (u5 & 0xff) - 0x62;
                if (0xc < u5 || ((1ULL << (u5 & 0x1f)) & 0x1021ULL) == 0) {
                    if ((int64_t)local48 >= 0) return;
                    sk_lock((void *)local58, local48 & 0x7fffffffffffffff);
                    return;
                }
            }
        }
    }
    buf[0] = 0; buf[1] = 0; buf[2] = 0;
}

/* FUN_003af238 @ 0x3af238   (est. sk_parse_152_chain)
 * Builds a 0x152 node collecting all stack elements, finalizes it, then
 * appends af614 and two af6ac children, optionally a 'p'-prefixed af6ac and
 * an 'r'-prefixed af6ac. Returns the node or 0 on incomplete sequence.
 * Confidence: medium */
static uint64_t sk_003af238(uint64_t *st)
{
    uint64_t *l3 = sk_node_alloc(st, 1);
    NODE_SETTAG(l3, 0x152); NODE_SETSUBT(l3, 0);
    while (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        STACK_CNT(st) = i;
        if (e == 0) break;
        sk_node_add(l3, e, st);
    }
    sk_node_finalize(l3, 0);
    uint64_t *l4 = (uint64_t *)sk_003af614(st);
    uint64_t *l5 = 0;
    if (l3 != 0 && l4 != 0) { sk_node_add(l3, l4, st); l5 = l3; }
    l4 = (uint64_t *)sk_003af6ac(st);
    uint64_t *l3b = 0;
    if (l5 != 0 && l4 != 0) { sk_node_add(l5, l4, st); l3b = l5; }
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'p') {
        STREAM_POS(st) = pos + 1;
        l4 = (uint64_t *)sk_003af6ac(st);
        uint64_t *l5b = 0;
        if (l3b != 0 && l4 != 0) { sk_node_add(l3b, l4, st); l5b = l3b; }
        pos = STREAM_POS(st);
        if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'r') {
            STREAM_POS(st) = pos + 1;
            l4 = (uint64_t *)sk_003af6ac(st);
            uint64_t *l3c = 0;
            if (l5b != 0 && l4 != 0) { sk_node_add(l5b, l4, st); l3c = l5b; }
            pos = STREAM_POS(st);
            if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'P') {
                STREAM_POS(st) = pos + 1;
                return (uint64_t)l3c;
            }
        }
    }
    return 0;
}

/* FUN_003af3c4 @ 0x3af3c4   (est. sk_parse_151_chain)
 * Builds a 0x151 node from a 0x2c + up to two 0xf4 stack elements, finalizes,
 * and appends an af614 child. Returns the node or 0.
 * Confidence: medium */
static uint64_t sk_003af3c4(uint64_t *st)
{
    uint64_t *l1 = sk_node_alloc(st, 1);
    NODE_SETTAG(l1, 0x151); NODE_SETSUBT(l1, 0);
    int32_t cnt = STACK_CNT(st);
    if (cnt != 0) {
        uint64_t *e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0x2c) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(l1, e, st);
            cnt = STACK_CNT(st);
            if (cnt == 0) goto l49c;
        }
        e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0xf4) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(l1, e, st);
            cnt = STACK_CNT(st);
            if (cnt == 0) goto l49c;
        } else {
            l1 = 0;
        }
        e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0xf4) {
            STACK_CNT(st) = cnt - 1;
            if (l1 != 0) {
                sk_node_add(l1, e, st);
                sk_node_finalize(l1, 0);
            }
            goto l4a0;
        }
    }
l49c:
    l1 = 0;
l4a0:
    uint64_t *l2 = (uint64_t *)sk_003af614(st);
    uint64_t *l3 = 0;
    if (l1 != 0 && l2 != 0) { sk_node_add(l1, l2, st); l3 = l1; }
    return (uint64_t)l3;
}

/* FUN_003af4d4 @ 0x3af4d4   (est. sk_parse_tagged_chain)
 * Builds a node with the given tag, drains all stack elements into it,
 * finalizes, appends af614 + two af6ac children plus optional 'p'- and
 * 'r'-prefixed af6ac children. Returns the node or 0.
 * Confidence: medium */
static uint64_t sk_003af4d4(uint64_t *st, uint16_t p2)
{
    uint64_t *l3 = sk_node_alloc(st, 1);
    NODE_SETTAG(l3, p2); NODE_SETSUBT(l3, 0);
    while (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        STACK_CNT(st) = i;
        if (e == 0) break;
        sk_node_add(l3, e, st);
    }
    sk_node_finalize(l3, 0);
    uint64_t *l4 = (uint64_t *)sk_003af614(st);
    uint64_t *l5 = 0;
    if (l3 != 0 && l4 != 0) { sk_node_add(l3, l4, st); l5 = l3; }
    l4 = (uint64_t *)sk_003af6ac(st);
    uint64_t *l3b = 0;
    if (l5 != 0 && l4 != 0) { sk_node_add(l5, l4, st); l3b = l5; }
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'p') {
        STREAM_POS(st) = pos + 1;
        l4 = (uint64_t *)sk_003af6ac(st);
        uint64_t *l5b = 0;
        if (l3b != 0 && l4 != 0) { sk_node_add(l3b, l4, st); l5b = l3b; }
        pos = STREAM_POS(st);
        if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'r') {
            STREAM_POS(st) = pos + 1;
            return (uint64_t)l5b;
        }
    }
    return 0;
}

/* FUN_003af614 @ 0x3af614   (est. sk_parse_150_byte)
 * Reads one byte; if it is a 'd'/'D'/'e'/'E'/'f'-class character (low 4-bit
 * code), returns a 0x150 scalar node holding the byte. Else NULL.
 * Confidence: medium */
static uint64_t *sk_003af614(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    uint64_t v;
    if (pos < STREAM_END(st)) {
        STREAM_POS(st) = pos + 1;
        v = (uint64_t)STREAM_DATA(st)[pos];
    } else {
        v = 0;
    }
    int32_t u1 = (int32_t)v - 100;
    uint32_t u2 = (uint32_t)u1 >> 1;
    if (((u2 & 0x7f | (uint32_t)(u1 * 0x80) & 0xff) < 8) &&
        ((1ULL << (u2 & 0x1f)) & 0xc3ULL) != 0) {
        uint64_t *n = sk_node_alloc(st, 1);
        NODE_SETTAG(n, 0x150); NODE_SETSUBT(n, 4);
        n[0] = v;
        return n;
    }
    return 0;
}

/* FUN_003af6ac @ 0x3af6ac   (est. sk_parse_156_ident)
 * Reads a run of 'S'/'U' characters into a byte vector, then builds a 0x156
 * node (via 363f70) holding the vector, freeing the buffer on the error path.
 * Returns the node or 0.
 * Confidence: low */
static uint64_t sk_003af6ac(uint64_t *st)
{
    uint64_t local38 = 0, local30 = 0, local28 = 0;
    char c = '\0';
    if (STREAM_POS(st) < STREAM_END(st)) c = STREAM_DATA(st)[STREAM_POS(st)];
    while (c == 'S' || c == 'U') {
        sk_vec_byte_append((uint64_t *)&local38, (uint8_t)c);
        uint64_t pos = STREAM_POS(st);
        if (pos < STREAM_END(st)) {
            pos = pos + 1;
            STREAM_POS(st) = pos;
        }
        c = '\0';
        if (pos < STREAM_END(st)) c = STREAM_DATA(st)[pos];
    }
    uint32_t u2 = (uint32_t)(uint8_t)(local28 >> 56);
    uint64_t u5 = local30;
    if ((int32_t)u2 >= 0) u5 = (uint64_t)(uint8_t)(local28 >> 56);
    uint64_t u3;
    if (u5 == 0) {
        u3 = 0;
        if ((u2 >> 7 & 1) == 0) return 0;
    } else {
        uint64_t *p = (uint64_t *)local38;
        if ((int32_t)u2 >= 0) p = (uint64_t *)&local38;
        u3 = (uint64_t)sk_00363f70(st, 0x156, p);
        if ((int64_t)local28 >= 0) return u3;
    }
    sk_lock((void *)local38, local28 & 0x7fffffffffffffff);
    return u3;
}

/* FUN_003af7a4 @ 0x3af7a4   (est. sk_parse_154_chain)
 * Builds a 0x154 node, drains 0x2c + 0xf4 stack elements, finalizes, reads a
 * 'd'-class byte mapped through a lookup table into an 0x68 scalar, appends
 * af6ac and optional 'p'/'r' af6ac children plus the initial 0x2c element.
 * Returns the node or 0.
 * Confidence: low */
static uint64_t sk_003af7a4(uint64_t *st)
{
    uint64_t *l2 = sk_node_alloc(st, 1);
    NODE_SETTAG(l2, 0x154); NODE_SETSUBT(l2, 0);
    uint32_t cnt = STACK_CNT(st);
    uint64_t u7 = cnt;
    uint64_t *l8 = 0;
    if (cnt == 0) {
        l8 = 0;
    } else {
        cnt = cnt - 1;
        l8 = STACK_ELEM(st, cnt);
        if (NODE_TAG(l8) == 0x2c) {
            STACK_CNT(st) = cnt;
            u7 = cnt;
            if (cnt == 0) goto l83c;
        } else {
            l8 = 0;
        }
        do {
            uint32_t i = (uint32_t)u7 - 1;
            uint64_t *e = STACK_ELEM(st, i);
            STACK_CNT(st) = i;
            if (e == 0) break;
            sk_node_add(l2, e, st);
            u7 = (uint64_t)STACK_CNT(st);
        } while (STACK_CNT(st) != 0);
    }
l83c:
    sk_node_finalize(l2, 0);
    uint64_t pos = STREAM_POS(st);
    uint32_t u6;
    if (pos < STREAM_END(st)) {
        STREAM_POS(st) = pos + 1;
        u6 = (uint32_t)(int32_t)STREAM_DATA(st)[pos] - 100;
    } else {
        u6 = 0xffffff9c;
    }
    uint32_t u1 = u6 >> 1 | u6 << 0x1f;
    if ((u1 < 8) && (((0x93U >> (u6 >> 1 & 0x1f)) & 1) != 0)) {
        uint64_t u9 = ((uint64_t *)0x4f2960)[u1];
        uint64_t *s = sk_node_alloc(st, 1);
        NODE_SETTAG(s, 0x68); NODE_SETSUBT(s, 4);
        s[0] = u9;
        if (l2 != 0) sk_node_add(l2, s, st);
        uint64_t *l4 = (uint64_t *)sk_003af6ac(st);
        uint64_t *l5 = 0;
        if (l2 != 0 && l4 != 0) { sk_node_add(l2, l4, st); l5 = l2; }
        pos = STREAM_POS(st);
        if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'p') {
            STREAM_POS(st) = pos + 1;
            l4 = (uint64_t *)sk_003af6ac(st);
            uint64_t *l2b = 0;
            if (l5 != 0 && l4 != 0) { sk_node_add(l5, l4, st); l2b = l5; }
            pos = STREAM_POS(st);
            if (pos < STREAM_END(st) && STREAM_DATA(st)[pos] == 'r') {
                STREAM_POS(st) = pos + 1;
                if (l8 == 0) return (uint64_t)l2b;
                if (l2b != 0) { sk_node_add(l2b, l8, st); return (uint64_t)l2b; }
                return 0;
            }
        }
    }
    return 0;
}

/* FUN_003af99c @ 0x3af99c   (est. sk_parse_spec_node)
 * Builds a node with the given tag and appends a set of 0x52/0x53
 * attribute children parsed from a coded character sequence: 'C' gives a
 * 0x52(0xb) + decimal 0x53; 'd'/'D' gives a 0x40/0xc0/0x440 mask with
 * optional 'G'/'O'/'X' bits; 'g' 0x80/0x180; 'o' 0x200/0x300; 'p' recurses a
 * run of 'S'/'d'/'f'/'g'/'i'/'k'/'s'/'b'/'c'/'w' items via aff04; 'i' 6,
 * 'r' 8, 's' 7, 'x' 0x100, default 5. Returns the node (or NULL for some).
 * Confidence: medium */
static uint64_t sk_003af99c(uint64_t *st, uint16_t p2)
{
    uint64_t *l4 = sk_node_alloc(st, 1);
    NODE_SETTAG(l4, p2); NODE_SETSUBT(l4, 0);
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    if (end <= pos) return 0;
    uint64_t npos = pos + 1;
    STREAM_POS(st) = npos;
    uint32_t u3 = STREAM_DATA(st)[pos];
    if (0x15 < u3 - 99) {
        if (u3 != 'C') return 0;
        uint64_t *s = sk_node_alloc(st, 1);
        NODE_SETTAG(s, 0x52); NODE_SETSUBT(s, 4);
        s[0] = 0xb;
        sk_node_add(l4, s, st);
        int32_t v = sk_003ac430(st);
        if (v < 0) return 0;
        uint64_t *s2 = sk_node_alloc(st, 1);
        NODE_SETTAG(s2, 0x53); NODE_SETSUBT(s2, 4);
        s2[0] = (uint64_t)v;
        goto emit_scalar;
    }
    uint64_t *pu6;
    switch (u3) {
    default:
        pu6 = sk_node_alloc(st, 1);
        NODE_SETTAG(pu6, 0x52); NODE_SETSUBT(pu6, 4);
        pos = 5;
        break;
    case 'd': {
        uint64_t p = npos;
        if ((p < end) && STREAM_DATA(st)[p] == 'G') {
            p = pos + 2;
            STREAM_POS(st) = p;
            u3 = 0xc0;
        } else {
            u3 = 0x40;
        }
        goto mask_common;
    }
    case 'e': {
        uint64_t p = npos;
        if ((p < end) && STREAM_DATA(st)[p] == 'D') {
            p = pos + 2;
            STREAM_POS(st) = p;
            u3 = 0x440;
        } else {
            u3 = 0x400;
        }
        if ((p < end) && STREAM_DATA(st)[p] == 'G') {
            p = p + 1;
            STREAM_POS(st) = p;
            u3 = u3 | 0x80;
        }
    mask_common:
        if ((p < end) && STREAM_DATA(st)[p] == 'O') {
            p = p + 1;
            STREAM_POS(st) = p;
            u3 = u3 | 0x200;
        }
        if ((p < end) && STREAM_DATA(st)[p] == 'X') {
            STREAM_POS(st) = p + 1;
            u3 = u3 | 0x100;
        }
        pos = u3;
        goto mask_node;
    }
    case 'f': case 'h': case 'j': case 'k': case 'l': case 'm':
    case 'q': case 't': case 'u': case 'v': case 'w':
        return 0;
    case 'g':
        if ((npos < end) && STREAM_DATA(st)[npos] == 'X') {
            STREAM_POS(st) = pos + 2;
            pos = 0x180;
        } else {
            pos = 0x80;
        }
        goto mask_node;
    case 'i':
        pu6 = sk_node_alloc(st, 1);
        NODE_SETTAG(pu6, 0x52); NODE_SETSUBT(pu6, 4);
        pos = 6;
        break;
    case 'n':
        goto return_l4;
    case 'o':
        if ((npos < end) && STREAM_DATA(st)[npos] == 'X') {
            STREAM_POS(st) = pos + 2;
            pos = 0x300;
        } else {
            pos = 0x200;
        }
    mask_node:
        pu6 = sk_node_alloc(st, 1);
        NODE_SETTAG(pu6, 0x52); NODE_SETSUBT(pu6, 4);
        pu6[0] = pos;
        goto emit_scalar;
    case 'p': {
        if (end <= npos) goto lfd2c;
        do {
            npos = npos + 1;
            STREAM_POS(st) = npos;
            uint8_t b = STREAM_DATA(st)[npos - 1];
            uint64_t *s;
            if (b < 0x67) {
                if (b == 'S') {
                    s = sk_node_alloc(st, 1);
                    NODE_SETTAG(s, 0x52); NODE_SETSUBT(s, 4);
                    s[0] = 10;
                } else if (b == 'd') {
                    uint64_t *r = (uint64_t *)sk_003aff04(st, (uint64_t)l4, 3);
                    if (r == 0) return 0;
                    goto cont;
                } else if (b != 'f') goto lfd28;
                else {
                    s = sk_node_alloc(st, 1);
                    NODE_SETTAG(s, 0x52); NODE_SETSUBT(s, 4);
                    s[0] = 0;
                }
            } else {
                if (b < 0x6b) {
                    if (b == 'g') {
                        s = sk_node_alloc(st, 1);
                        NODE_SETTAG(s, 0x52); NODE_SETSUBT(s, 4);
                        s[0] = 1;
                        goto lfd08;
                    }
                    if (b != 'i') goto lfd28;
                    uint64_t *r = (uint64_t *)sk_003aff04(st, (uint64_t)l4, 2);
                    if (r == 0) return 0;
                    goto cont;
                }
                if (b != 'k') {
                    if (b == 's') {
                        if (end <= npos) return 0;
                        STREAM_POS(st) = npos + 1;
                        char c2 = STREAM_DATA(st)[npos];
                        char *label;
                        if (c2 == 'b') label = (char *)0x5d6ec8;
                        else if (c2 == 'c') label = (char *)0x5d6ecf;
                        else {
                            if (c2 != 'w') return 0;
                            label = (char *)0x5d6ecb;
                        }
                        s = sk_node_alloc(st, 1);
                        NODE_SETTAG(s, 0x52); NODE_SETSUBT(s, 4);
                        s[0] = 4;
                        sk_node_add(l4, s, st);
                        s = sk_node_alloc(st, 1);
                        NODE_SETTAG(s, 0x53); NODE_SETSUBT(s, 3);
                        s[0] = (uint64_t)label;
                        s[1] = (uint64_t)sk_len_query((uint64_t)label);
                        goto lfd08;
                    }
                    goto lfd28;
                }
                s = sk_node_alloc(st, 1);
                NODE_SETTAG(s, 0x52); NODE_SETSUBT(s, 4);
                s[0] = 9;
            }
        lfd08:
            sk_node_add(l4, s, st);
        cont:
            end = STREAM_END(st);
            npos = STREAM_POS(st);
            if (end <= npos) goto lfd28;
        } while (true);
    }
    case 'r':
        pu6 = sk_node_alloc(st, 1);
        NODE_SETTAG(pu6, 0x52); NODE_SETSUBT(pu6, 4);
        pos = 8;
        break;
    case 's':
        pu6 = sk_node_alloc(st, 1);
        NODE_SETTAG(pu6, 0x52); NODE_SETSUBT(pu6, 4);
        pos = 7;
        break;
    case 'x':
        pu6 = sk_node_alloc(st, 1);
        NODE_SETTAG(pu6, 0x52); NODE_SETSUBT(pu6, 4);
        pos = 0x100;
    }
    pu6[0] = pos;
emit_scalar:
    sk_node_add(l4, pu6, st);
return_l4:
    return (uint64_t)l4;
lfd28:
    pos = pos - 1;
lfd2c:
    STREAM_POS(st) = pos;
    return (uint64_t)l4;
}

/* FUN_003aff04 @ 0x3aff04   (est. sk_parse_number_attr)
 * Adds a 0x52 attribute holding param_3, then parses a run of ASCII decimal
 * digits into a byte vector and appends it as a 0x53 child of param_2 (which
 * must be non-NULL). Returns param_2 or 0.
 * Confidence: medium */
static uint64_t sk_003aff04(uint64_t *st, uint64_t p2v, uint64_t p3)
{
    uint64_t *p2 = (uint64_t *)p2v;
    uint64_t *s = sk_node_alloc(st, 1);
    NODE_SETTAG(s, 0x52); NODE_SETSUBT(s, 4);
    s[0] = p3 & 0xffffffff;
    sk_node_add(p2, s, st);
    uint64_t local40 = 0, local38 = 0;
    uint64_t pos = STREAM_POS(st);
    if (pos < STREAM_END(st)) {
        do {
            if (9 < STREAM_DATA(st)[pos] - 0x30) break;
            STREAM_POS(st) = pos + 1;
            uint8_t c = STREAM_DATA(st)[pos];
            sk_003acd3c((uint64_t *)&local40, &c, st);
            pos = STREAM_POS(st);
        } while (pos < STREAM_END(st));
        if ((int32_t)local38 != 0) {
            uint64_t *s3 = sk_node_alloc(st, 1);
            NODE_SETTAG(s3, 0x53); NODE_SETSUBT(s3, 3);
            s3[0] = local40;
            s3[1] = local38 & 0xffffffff;
            if (p2 == 0) return 0;
            sk_node_add(p2, s3, st);
            return (uint64_t)p2;
        }
    }
    return 0;
}

/* FUN_003b0004 @ 0x3b0004   (est. sk_emit_15d)
 * Pops a 0xf4 element; for 'G' with a trailing 0x2c element builds a 0x15d
 * pair, else pushes 0x15d over the element. Returns nothing.
 * Confidence: medium */
static uint64_t sk_003b0004(uint64_t *st, int32_t p2)
{
    uint32_t cnt = STACK_CNT(st);
    uint64_t *e = 0;
    if (cnt != 0) {
        uint32_t i = cnt - 1;
        e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) {
            STACK_CNT(st) = i;
            cnt = i;
        } else {
            e = 0;
        }
        if (p2 == 'G' && cnt != 0) {
            uint64_t *e2 = STACK_ELEM(st, cnt - 1);
            if (NODE_TAG(e2) == 0x2c) {
                STACK_CNT(st) = cnt - 1;
                return (uint64_t)sk_node_push2(st, 0x15d, e2, e);
            }
        }
    }
    return (uint64_t)sk_node_push(st, 0x15d, e);
}

/* FUN_003b0078 @ 0x3b0078   (est. sk_parse_161_chain)
 * Builds an 0xf7 node draining all 0xf4 stack elements, finalizes, then if the
 * top is a 0x15f/0x160 element builds an 0x161 node (via 4c14 when an 0xf4
 * run was found) pushed as 0xf4. Returns the node or 0.
 * Confidence: medium */
static uint64_t sk_003b0078(uint64_t *st)
{
    uint64_t l2 = (uint64_t)sk_003ad67c(0);
    uint64_t *l3 = sk_node_alloc(st, 1);
    NODE_SETTAG(l3, 0xf7); NODE_SETSUBT(l3, 0);
    for (;;) {
        if (STACK_CNT(st) == 0) break;
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) != 0xf4) break;
        STACK_CNT(st) = i;
        sk_node_add(l3, e, st);
    }
    sk_node_finalize(l3, 0);
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        STACK_CNT(st) = i;
        if (e != 0 && (NODE_TAG(e) - 0x15f < 2)) {
            uint64_t u4;
            if (l2 == 0) u4 = (uint64_t)sk_node_push2(st, 0x161, e, l3);
            else u4 = (uint64_t)sk_ctx_op2_v(st, (uint64_t *)0);
            return (uint64_t)sk_node_push(st, 0xf4, (uint64_t *)u4);
        }
    }
    return 0;
}

/* FUN_003b0174 @ 0x3b0174   (est. sk_parse_metatype_attr)
 * Reads 't'/'o'/'T' and returns a 0x9b 3-subtype node holding the thin /
 * objc-metatype / thick label string and its length. NULL on other letters.
 * Confidence: high (string-matched) */
static uint64_t *sk_003b0174(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    char c = STREAM_DATA(st)[pos];
    char *label;
    uint64_t len;
    if (c == 't') { label = s__thin_005d6ed4; len = 5; }
    else if (c == 'o') { label = s__objc_metatype_005d6ee1; len = 0xe; }
    else {
        if (c != 'T') return 0;
        label = s__thick_005d6eda; len = 6;
    }
    uint64_t *n = sk_node_alloc(st, 1);
    NODE_SETTAG(n, 0x9b); NODE_SETSUBT(n, 3);
    n[0] = (uint64_t)label;
    n[1] = len;
    return n;
}

/* FUN_003b0220 @ 0x3b0220   (est. sk_parse_56_collect)
 * Builds a 0x56 node, draining stack elements (each passing the b0a64 test)
 * bounded by a 0x121 terminator; finalizes and returns it. Returns 0 on empty.
 * Confidence: medium */
static uint64_t sk_003b0220(uint64_t *st)
{
    uint64_t *l4 = sk_node_alloc(st, 1);
    NODE_SETTAG(l4, 0x56); NODE_SETSUBT(l4, 0);
    uint16_t s1;
    do {
        uint32_t cnt = STACK_CNT(st);
        if (cnt == 0) return 0;
        uint32_t i = cnt - 1;
        s1 = NODE_TAG(STACK_ELEM(st, i));
        if (s1 == 0x121) {
            STACK_CNT(st) = i;
            cnt = i;
            if (i == 0) return 0;
        }
        uint64_t *e = STACK_ELEM(st, cnt - 1);
        if (sk_003b0a64(NODE_TAG(e)) == 0) return 0;
        STACK_CNT(st) = cnt - 1;
        sk_node_add(l4, e, st);
    } while (s1 != 0x121);
    sk_node_finalize(l4, 0);
    return (uint64_t)l4;
}

/* FUN_003b02dc @ 0x3b02dc   (est. sk_parse_c9_seq)
 * Builds a 0xc9 node wrapping an 0xf7 collection; drains values (663c) bounded
 * by 0x120/0x121 terminators; finalizes the 0xf7 and returns the 0xc9 node.
 * Confidence: medium */
static uint64_t sk_003b02dc(uint64_t *st)
{
    uint64_t *l2 = sk_node_alloc(st, 1);
    NODE_SETTAG(l2, 0xf7); NODE_SETSUBT(l2, 0);
    uint64_t u3 = (uint64_t)sk_node_push(st, 0xc9, l2);
    if (STACK_CNT(st) != 0 &&
        NODE_TAG(STACK_ELEM(st, STACK_CNT(st) - 1)) == 0x120) {
        STACK_CNT(st) = STACK_CNT(st) - 1;
    } else {
        bool b5;
        do {
            if (STACK_CNT(st) != 0 &&
                NODE_TAG(STACK_ELEM(st, STACK_CNT(st) - 1)) == 0x121) {
                b5 = false;
                STACK_CNT(st) = STACK_CNT(st) - 1;
            } else {
                b5 = true;
            }
            uint64_t v = sk_val_get(st);
            if (v == 0) return 0;
            sk_node_add(l2, (uint64_t *)v, st);
        } while (b5);
        sk_node_finalize(l2, 0);
    }
    return u3;
}

/* FUN_003b03c0 @ 0x3b03c0   (est. sk_parse_attr_letter)
 * Parses a single-letter attribute after the current node: 'G'(0x66),
 * 'M'(0xa1), 'W'(0x35), and a set of lowercase letters map to fixed tags via
 * node_push; some ('m','s' 0xe3/0x96, default, 'l', lowercase-default) read a
 * second byte to select among sub-tags. Returns the pushed node, or param_2
 * (zeroed) on no match.
 * Confidence: medium */
static uint64_t sk_003b03c0(uint64_t *st, uint64_t p2)
{
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    if (pos < end) {
        uint64_t npos = pos + 1;
        STREAM_POS(st) = npos;
        uint64_t base = STREAM_DATA(st)[pos];
        uint32_t u7 = (uint32_t)base;
        if (base < 0x61) {
            if (u7 == 'G') return (uint64_t)sk_node_push(st, 0x66, 0);
            if (u7 == 'M') return (uint64_t)sk_node_push(st, 0xa1, 0);
            if (u7 == 'W') return (uint64_t)sk_node_push(st, 0x35, 0);
        } else if (u7 - 0x61 < 0x1a) {
            uint64_t tag = 0x96;
            switch (u7) {
            case 'b': return (uint64_t)sk_node_push(st, 0x178, 0);
            case 'c': case 'd': case 'e': case 'f': case 'h': case 'j':
            case 'k': case 'n': case 'o': case 'q': case 't': case 'u':
            case 'v':
                break;
            case 'g': return (uint64_t)sk_node_push(st, 100, 0);
            case 'i': return (uint64_t)sk_node_push(st, 0x83, 0);
            case 'l': {
                if (npos < end) {
                    STREAM_POS(st) = pos + 2;
                    uint8_t b2 = STREAM_DATA(st)[npos];
                    if (0x6f < b2) {
                        if (b2 == 'p') return (uint64_t)sk_node_push(st, 0xa6, 0);
                        if (b2 != 'u') return 0;
                        return (uint64_t)sk_node_push(st, 0x107, 0);
                    }
                    if (b2 == 'O') return (uint64_t)sk_node_push(st, 0xb2, 0);
                    if (b2 != 'o') return 0;
                    return (uint64_t)sk_node_push(st, 0xa4, 0);
                }
                break;
            }
            case 'p': goto case_70;
            case 'r': return (uint64_t)sk_node_push(st, 0xd7, 0);
            case 's': tag = 0xe3; /* fallthrough */
            case 'm':
                return (uint64_t)sk_node_push(st, (int)tag, 0);
            case 'w': return (uint64_t)sk_node_push(st, 0x10e, 0);
            case 'x': return (uint64_t)sk_node_push(st, 0xa2, 0);
            case 'y': return (uint64_t)sk_node_push(st, 0xd8, 0);
            case 'z': return (uint64_t)sk_node_push(st, 0x179, 0);
            default: {
                if (npos < end) {
                    STREAM_POS(st) = pos + 2;
                    uint8_t b2 = STREAM_DATA(st)[npos];
                    if (0x6e < b2) {
                        if (b2 == 'u') return (uint64_t)sk_node_push(st, 0x108, 0);
                        if (b2 != 'o') return 0;
                        return (uint64_t)sk_node_push(st, 0xa5, 0);
                    }
                    if (b2 == 'O') return (uint64_t)sk_node_push(st, 0xb3, 0);
                    if (b2 != 'P') return 0;
                    return (uint64_t)sk_node_push(st, 0xa7, 0);
                }
                break;
            }
            }
        }
    }
    p2 = 0;
case_70:
    return p2;
}

/* FUN_003b05c8 @ 0x3b05c8   (est. sk_emit_typed_pair)
 * Pops a 0xf4 element; builds a 4c14 node (or 4ca8 variant) from it, a
 * printable element and the popped element, then runs acfb4. Returns nothing.
 * Confidence: medium */
static void sk_003b05c8(uint64_t *st, uint64_t p2)
{
    uint64_t *l5;
    if (STACK_CNT(st) == 0) { l5 = 0; }
    else {
        uint32_t i = STACK_CNT(st) - 1;
        l5 = STACK_ELEM(st, i);
        if (NODE_TAG(l5) != 0xf4) l5 = 0;
        else STACK_CNT(st) = i;
    }
    uint64_t l3 = (uint64_t)sk_ctx_op2_v(st, l5);
    uint64_t *l6 = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        l6 = STACK_ELEM(st, i);
        if (sk_003acda0(NODE_TAG(l6)) != 0) { STACK_CNT(st) = i; goto l650; }
    }
    l6 = 0;
l650:
    uint64_t u4 = (uint64_t)sk_003ace50(st);
    if (l3 == 0) u4 = (uint64_t)sk_ctx_op(st, p2, (uint64_t *)u4, l6, l5);
    else u4 = (uint64_t)sk_ctx_op2_v(st, 0);
    sk_003acfb4(st, u4, (uint64_t)l5, *(uint8_t *)((char *)st + 0x51));
}

/* FUN_003b06ac @ 0x3b06ac   (est. sk_parse_94_construct)
 * Parses a construct starting with an 'a'..'x' letter or 'X': 'X' reads two
 * idents into 0x68 scalars and builds a 0x94 node; most letters select a tag
 * (0x8/0xc/0x1d/0x4a/0x4c/0x97/0xb6/0xb8/0x98/0x95) and pop a configurable
 * set of stack elements (0x67/0xba/printable) into the node. Returns node.
 * Confidence: low */
static uint64_t sk_003b06ac(uint64_t *st)
{
    uint64_t pos = STREAM_POS(st);
    if (STREAM_END(st) <= pos) return 0;
    uint64_t result = 0;
    STREAM_POS(st) = pos + 1;
    uint32_t u11 = (uint32_t)STREAM_DATA(st)[pos];
    if (0x14 < u11 - 0x61) {
        if (u11 != 'X') return 0;
        int32_t i4 = sk_003ac4a4(st);
        int32_t i5 = sk_003ac4a4(st);
        uint64_t *s1 = sk_node_alloc(st, 1);
        NODE_SETTAG(s1, 0x68); NODE_SETSUBT(s1, 4);
        s1[0] = (uint64_t)i4;
        uint64_t *s2 = sk_node_alloc(st, 1);
        NODE_SETTAG(s2, 0x68); NODE_SETSUBT(s2, 4);
        s2[0] = (uint64_t)i5;
        uint32_t cnt = STACK_CNT(st);
        uint64_t *l10 = 0, *l9;
        if (cnt == 0) {
            l10 = 0;
            goto x_e0;
        }
        uint32_t i = cnt - 1;
        l10 = STACK_ELEM(st, i);
        if (NODE_TAG(l10) == 0x67) {
            STACK_CNT(st) = i;
            cnt = i;
            if (i == 0) goto x_e0;
        } else {
            l10 = 0;
        }
        l9 = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(l9) == 0x67) {
            STACK_CNT(st) = cnt - 1;
            goto x_e4;
        }
    x_e0:
        l9 = 0;
    x_e4:
        result = (uint64_t)sk_ctx_op2_v(st, 0);
        result = (uint64_t)sk_node_push2(st, 0x94, (uint64_t *)result, (uint64_t *)l9);
        return result;
    }
    uint64_t tag = 8;
    bool b3 = true, b2 = false;
    uint64_t *l8 = 0, *l14 = 0, *l9 = 0, *l10 = 0;
    uint64_t u15, u16;
    switch (u11) {
    case 'b': tag = 0xc; break;
    case 'c': tag = 0x1d; break;
    case 'd': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
    case 'n': case 'o': case 's': case 't':
        goto ret;
    case 'e': tag = 0x4a; break;
    case 'f':
        b3 = false;
        u11 = STACK_CNT(st);
        tag = 0x4c;
        if (u11 != 0) { b2 = true; goto l82c; }
        l10 = 0; l14 = 0; l9 = 0;
        goto l928;
    case 'm': tag = 0x97; break;
    case 'p': tag = 0xb6; break;
    case 'q': tag = 0xb8; break;
    case 'r': tag = 0x98; break;
    case 'u':
        b3 = false;
        tag = 0x95;
    }
    u11 = STACK_CNT(st);
    if (u11 == 0) {
        l14 = 0;
    l898:
        u15 = 0;
    l8a4:
        l10 = 0;
        u16 = u15;
        if (b3) goto l8ac;
    joined_e0:
        b3 = false;
        l9 = 0;
        if (u16 != 0) goto l8fc;
    l928:
        l8 = (uint64_t *)sk_003ace50(st);
    } else {
        b2 = false;
    l82c:
        u15 = u11 - 1;
        l14 = STACK_ELEM(st, u15);
        if (NODE_TAG(l14) != 0x67) {
            l14 = 0;
            u15 = u11;
            if (b2) goto l864;
            goto l8a4;
        }
        STACK_CNT(st) = u15;
        u11 = u15;
        if (!b2) goto l8a4;
    l864:
        if (u11 == 0) goto l898;
        u16 = u11 - 1;
        l10 = STACK_ELEM(st, u16);
        u15 = u11;
        if (NODE_TAG(l10) != 0xba) goto l8a4;
        STACK_CNT(st) = u16;
        if (!b3) goto joined_e0;
    l8ac:
        if (u16 == 0) { l9 = 0; b3 = true; goto l928; }
        u11 = u16 - 1;
        l9 = STACK_ELEM(st, u11);
        if (sk_003acda0(NODE_TAG(l9)) == 0) { l9 = 0; b3 = true; }
        else {
            STACK_CNT(st) = u11;
            b3 = true;
            u16 = u11;
            if (u11 == 0) goto l928;
        }
    l8fc:
        l8 = STACK_ELEM(st, u16 - 1);
        if (sk_003b0aa4(NODE_TAG(l8)) == 0) goto l928;
        STACK_CNT(st) = u16 - 1;
    }
    u13:
    result = (uint64_t)sk_003ac52c(st);
    if (b3 && l9 != 0) {
        result = (uint64_t)sk_node_push2(st, (int)tag, l8, l9);
        result = (uint64_t)sk_node_push2(st, (int)tag, (uint64_t *)result, l14);
    } else {
        result = (uint64_t)sk_ctx_op(st, tag, l8, l14, (uint64_t *)result);
    }
    if (l10 != 0) sk_node_add((uint64_t *)result, l10, st);
ret:
    return result;
}

/* FUN_003b0a64 @ 0x3b0a64   (est. sk_tag_is_collectable)
 * Returns true if the tag is in the collectable set (mask over tags <0x2c)
 * or is 0x171/0x174.
 * Confidence: high */
static bool sk_003b0a64(uint32_t p1)
{
    if ((p1 < 0x2c) && (((1ULL << (p1 & 0x3f)) & 0xf2000000000ULL) != 0)) return true;
    return p1 == 0x171 || p1 == 0x174;
}

/* FUN_003b0aa4 @ 0x3b0aa4   (est. sk_tag_in_94_range)
 * Returns true if the tag falls in two mask ranges or equals 8.
 * Confidence: high */
static bool sk_003b0aa4(int32_t p1)
{
    if (((0x22 < (uint32_t)(p1 - 0x94)) ||
         (((1ULL << ((uint32_t)(p1 - 0x94) & 0x3f)) & 0x400000019ULL) == 0)) &&
        ((0x2f < (uint32_t)(p1 - 0x1d)) ||
         (((1ULL << ((uint32_t)(p1 - 0x1d) & 0x3f)) & 0xa00000000001ULL) == 0))) {
        return p1 == 8;
    }
    return true;
}

/* FUN_003b0b08 @ 0x3b0b08   (est. sk_release_small_ctx)
 * Releases a small (0x38-byte) context obtained from b0b7c via sk_lock.
 * Returns nothing.
 * Confidence: high */
static void sk_003b0b08(void)
{
    uint64_t v = (uint64_t)sk_003b0b7c(0);
    sk_lock((void *)v, 0x38);
}

/* FUN_003b0b0c @ 0x3b0b0c   (est. sk_release_small_ctx2)
 * Same as b0b08: releases a small context via b0b7c + sk_lock.
 * Returns nothing.
 * Confidence: high */
static void sk_003b0b0c(void)
{
    uint64_t v = (uint64_t)sk_003b0b7c(0);
    sk_lock((void *)v, 0x38);
}

/* FUN_003b0b28 @ 0x3b0b28   (est. sk_ctx_destroy)
 * Tags the context with magic 0x67c398, reinitializes its +0x220 sub-object
 * (via 362ea4), then releases a 0x240-byte block from b0b7c. Returns nothing.
 * Confidence: medium */
static void sk_003b0b28(uint64_t *p)
{
    *p = 0x67c398;
    sk_00362ea4(p + 0x44);
    uint64_t v = (uint64_t)sk_003b0b7c(p);
    sk_lock((void *)v, 0x240);
}

/* FUN_003b0b7c @ 0x3b0b7c   (est. sk_ctx_teardown)
 * Tags the context with magic 0x67c370, walks and frees its link list, zeroes
 * a byte at +0x30 of the +0x28 object, and returns the context pointer.
 * Confidence: medium */
static uint64_t *sk_003b0b7c(uint64_t *p)
{
    *p = 0x67c370;
    uint64_t *cur = (uint64_t *)p[3];
    while (cur != 0) {
        cur = (uint64_t *)*cur;
        sk_lock((void *)0, 0);
    }
    if (p[5] != 0) *(uint8_t *)(p[5] + 0x30) = 0;
    return p;
}

/* FUN_003b0be0 @ 0x3b0be0   (est. sk_walk_emit_165)
 * Recursively walks a node tree, invoking param_3 (a callback) on each
 * qualifying child and emitting a 0x165 node wrapping the callback result via
 * 363f70, added to the parent. Skips tags 0x4e, 0xe8, 0x10b; for 0x143 with a
 * 0x165 leaf child it also returns early. Returns nothing.
 * Confidence: medium */
static void sk_003b0be0(uint64_t *st, uint16_t *p2, void *p3, uint64_t p4)
{
    uint16_t u3 = *(uint16_t *)(p2 + 8);   /* tag at +0x10 as ushort offset */
    if (u3 < 0x10b) {
        if (u3 == 0x4e) return;
        if (u3 == 0xe8) return;
    } else {
        if (u3 == 0x10b) return;
        if (u3 == 0x143) {
            char c = *(uint8_t *)((char *)p2 + 0x12);   /* sub-type at +0x12 */
            uint16_t *pu6 = p2;
            uint64_t l5;
            if (c == 0x01) l5 = 0;
            else if (c == 0x02) l5 = 1;
            else {
                if (c != 0x05 || *(uint32_t *)(p2 + 4) == 0) goto lce0;
                l5 = (uint64_t)*(uint32_t *)(p2 + 4) - 1;
                pu6 = *(uint16_t **)p2;
            }
            if (NODE_TAG((uint64_t *)*(uint64_t *)((uint64_t *)pu6 + l5 * 4) ) == 0x165) return;
        lce0:
            {
                /* call the callback: (*param_3)(param_4) returns 16 bytes */
                uint64_t cb[2];
                ((void (*)(uint64_t, uint64_t *))p3)(p4, cb);
                uint64_t v = (uint64_t)sk_00363f70(st, 0x165, (void *)cb[0]);
                sk_node_add((uint64_t *)p2, (uint64_t *)v, st);
                return;
            }
        }
    }
    uint8_t b2 = *(uint8_t *)((char *)p2 + 0x12);
    uint16_t *pu7 = p2;
    uint16_t *pu6;
lc98:
    if (b2 - 1 < 2) {
        if (b2 == 1) { pu6 = p2 + 4; goto ld48; }
        if (b2 == 2) goto ld34;
        if (b2 != 5) { pu6 = 0; goto ld48; }
        pu6 = *(uint16_t **)p2;
    } else {
        if (b2 != 5) { pu7 = 0; goto lc98; }
        pu6 = *(uint16_t **)p2;
        pu7 = pu6;
    }
    pu6 = pu6 + (uint64_t)*(uint32_t *)(p2 + 4) * 4;
ld48:
    for (; pu7 != pu6; pu7 = pu7 + 4) {
    ld34:
        sk_003b0be0(st, *(uint16_t **)pu7, p3, p4);
    }
}

/* FUN_003b0d64 @ 0x3b0d64   (est. sk_ctx_get_str)
 * Returns the (data,length) pair of a string field: if the field's length
 * flag at +0x17 is negative it uses the stored count, else the byte count;
 * returns the string pointer + length as a 16-byte struct.
 * Confidence: medium */
static uint8_t sk_003b0d64(uint64_t *p)
{
    /* Returns the low byte of the string data pointer (caller reads the
     * 16-byte {data,len} struct via the ABI); faithfully resolves the
     * indirect string: the field at +0x17 is a length flag, negative meaning
     * a stored 64-bit count else a byte count. */
    uint64_t *pu2 = (uint64_t *)*p;
    int64_t l3 = *(int8_t *)((char *)pu2 + 0x17);
    int64_t l5 = l3;
    if (l3 < 0) l5 = (int64_t)pu2[1];
    uint64_t *pu4;
    if (l5 == 0) {
        pu2 = (uint64_t *)*p;
        int64_t c = *(int8_t *)((char *)pu2 + 0x17);
        pu4 = (uint64_t *)*pu2;
        if (c >= 0) pu4 = pu2;
        if (c >= 0) l5 = c;
        else l5 = (int64_t)pu2[1];
    } else {
        pu4 = (uint64_t *)*pu2;
        l5 = (int64_t)pu2[1];
        if (*(int8_t *)((char *)pu2 + 0x17) >= 0) {
            pu4 = pu2;
            l5 = l3;
        }
    }
    return (uint8_t)(uint64_t)pu4;
}

/* FUN_003b0e1c @ 0x3b0e1c   (est. sk_buf_reserve_grow)
 * Reserves param_2*8 bytes in a growable buffer (param_1[1]=count aligned,
 * [2]=cap, [0x18]=base ptr, [0x20]=capacity), growing via alloc when needed.
 * Returns nothing.
 * Confidence: medium */
static uint64_t sk_003b0e1c(uint64_t *st, uint64_t p2)
{
    uint64_t add = p2 * 8;
    uint64_t cnt = (*(uint64_t *)(st + 1) + 7) & 0xfffffffffffffff8;
    *(uint64_t *)(st + 1) = cnt;
    if (cnt == 0 || *(uint64_t *)(st + 2) < cnt + add) {
        uint64_t cap = *(uint64_t *)(st + 4) * 2;
        uint64_t need = add + 8;
        if (cap < need || cap - need == 0) cap = need;
        *(uint64_t *)(st + 4) = cap;
        uint64_t *blk = (uint64_t *)sk_alloc_tagged(cap + 8, 0x2004093837f09);
        *blk = *(uint64_t *)(st + 3);
        uint64_t nb = ((uint64_t)blk + 0xf) & 0xfffffffffffffff8;
        *(uint64_t *)(st + 2) = (uint64_t)blk + cap + 8;
        *(uint64_t *)(st + 3) = (uint64_t)blk;
        cnt = nb;
    }
    cnt = cnt + add;
    *(uint64_t *)(st + 1) = cnt;
    return cnt;
}

/* FUN_003b0ec4 @ 0x3b0ec4   (est. sk_utoa_rev)
 * Converts a 32-bit unsigned integer to a decimal string in param_2
 * (reversed then reversed in place), returns the digit count. Uses '0' for 0.
 * Confidence: high */
static uint64_t sk_003b0ec4(uint64_t p1, uint8_t *p2)
{
    if ((int32_t)p1 == 0) {
        p2[0] = '0';
        p2[1] = 0;
        return 1;
    }
    uint64_t l3 = 0;
    uint8_t *pb5 = p2;
    uint8_t *pb6;
    uint32_t u4;
    do {
        pb6 = pb5;
        u4 = (uint32_t)p1;
        pb5 = pb6 + 1;
        *pb6 = (uint8_t)((char)p1 + (char)((p1 & 0xffffffff) / 10) * -10) | 0x30;
        l3 = l3 + 1;
        p1 = (p1 & 0xffffffff) / 10;
    } while (9 < u4);
    *pb5 = 0;
    if (p2 < pb5) {
        bool b2;
        do {
            uint8_t t = *pb6;
            *pb6 = *p2;
            *p2 = t;
            b2 = p2 + 1 < pb6;
            p2 = p2 + 1;
            pb6 = pb6 - 1;
        } while (b2);
    }
    return l3;
}

/* FUN_003b0f48 @ 0x3b0f48   (est. sk_ctx_adopt_parent)
 * Adopts a parent context: if param_2's parent is null, clears own parent;
 * if it is param_2 itself, points own parent at self and invokes the parent
 * vtable re-parent hook; else copies the grandparent and clears param_2's
 * parent. Returns param_1.
 * Confidence: medium */
static uint64_t sk_003b0f48(uint64_t *st, uint64_t p2v)
{
    uint64_t *p2 = (uint64_t *)p2v;
    uint64_t parent = *(uint64_t *)(p2 + 3);
    if (parent == 0) {
        *(uint64_t *)(st + 3) = 0;
    } else if (parent == (uint64_t)p2) {
        *(uint64_t *)(st + 3) = (uint64_t)st;
        ((void (*)(uint64_t *, uint64_t *))(**(uint64_t **)(*(uint64_t **)(p2 + 3)) + 0x18))
            (*(uint64_t **)(p2 + 3), st);
    } else {
        *(uint64_t *)(st + 3) = parent;
        *(uint64_t *)(p2 + 3) = 0;
    }
    return (uint64_t)st;
}

/* FUN_003b0fb8 @ 0x3b0fb8   (est. sk_ctx_init_adopt)
 * Initializes param_1 (via b1034) then adopts param_2's parent (same logic as
 * b0f48). Returns param_1.
 * Confidence: medium */
static uint64_t sk_003b0fb8(uint64_t *st, uint64_t p2v)
{
    uint64_t *p2 = (uint64_t *)p2v;
    sk_003b1034(st, 0);
    uint64_t parent = *(uint64_t *)(p2 + 3);
    if (parent == 0) {
        *(uint64_t *)(st + 3) = 0;
    } else if (parent == (uint64_t)p2) {
        *(uint64_t *)(st + 3) = (uint64_t)st;
        ((void (*)(uint64_t *, uint64_t *))(**(uint64_t **)(*(uint64_t **)(p2 + 3)) + 0x18))
            (*(uint64_t **)(p2 + 3), st);
    } else {
        *(uint64_t *)(st + 3) = parent;
        *(uint64_t *)(p2 + 3) = 0;
    }
    return (uint64_t)st;
}

/* FUN_003b1034 @ 0x3b1034   (est. sk_ctx_release_link)
 * Detaches param_1[3]; if it was param_1 invokes the vtable release hook at
 * +0x20, else (non-null) the +0x28 hook. Returns param_1.
 * Confidence: medium */
static uint64_t *sk_003b1034(uint64_t *p, uint64_t p2)
{
    uint64_t *link = (uint64_t *)p[3];
    p[3] = 0;
    if (link == p) {
        ((void (*)(void))(**(uint64_t **)(*link + 0x20)))();
    } else if (link != 0) {
        ((void (*)(void))(**(uint64_t **)(*link + 0x28)))();
    }
    return p;
}

/* FUN_003b10a8 @ 0x3b10a8   (est. sk_vec_grow_alloc)
 * Allocates param_2*8 bytes (bounded) via 111890; panics (fatal) on overflow.
 * Returns nothing (alloc result in x0).
 * Confidence: medium */
static void sk_003b10a8(uint64_t *st, uint64_t p2)
{
    if (p2 >> 0x3d == 0) {
        sk_alloc_tagged(p2 << 3, 0x20c0093837f09);
        return;
    }
    sk_fatal();
}

/* FUN_003b10f0 @ 0x3b10f0   (est. sk_ident_validate)
 * Validates a length-prefixed identifier: the first byte must be a letter
 * (case-insensitive), '_' or '$'; subsequent bytes may also be digits.
 * Returns 0 if valid/empty, 1 if a character is invalid.
 * Confidence: high */
static uint64_t sk_003b10f0(uint8_t *p, uint64_t n)
{
    if (n == 0) return 0;
    uint8_t b = *p;
    if (((uint8_t)((b & 0xdf) + 0xbf) < 0x1a) || b == '_' || b == '$') {
        do {
            n = n - 1;
            if (n == 0) return 0;
            p = p + 1;
            b = *p;
        } while (((b & 0xffffffdf) - 0x41 < 0x1a) || (b == '$') ||
                 (b == '_' || (b - 0x30 < 10)));
    }
    return 1;
}

/* FUN_003b1178 @ 0x3b1178   (est. sk_punct_mnemonic)
 * Maps a punctuation character to a single-letter mnemonic (e.g. '*'->'m',
 * '+'->'p', '-'->'s', '.'->'z', '/'->'d', '<'->'l', '='->'e', '>'->'g',
 * '?'->'q', '@'->'c', '%'->'r', '^'->'x', '|'->'o', '~'->'t'); unhandled
 * punctuation and printable chars map to themselves (or 'n' default).
 * Confidence: high */
static uint64_t sk_003b1178(uint64_t p1)
{
    int32_t v = (int32_t)p1;
    if (v < 0x5e) {
        if ((uint32_t)(v - 0x21) < 0x20) {
            switch (v) {
            default: return 'n';
            case 0x22: case 0x23: case 0x24: case 0x27: case 0x28: case 0x29:
            case 0x2c: case 0x30: case 0x31: case 0x32: case 0x33: case 0x34:
            case 0x35: case 0x36: case 0x37: case 0x38: case 0x39: case 0x3a:
            case 0x3b:
                break;
            case 0x25: return 'r';
            case 0x26: goto id26;
            case 0x2a: return 'm';
            case 0x2b: return 'p';
            case 0x2d: return 's';
            case 0x2e: return 'z';
            case 0x2f: return 'd';
            case 0x3c: return 'l';
            case 0x3d: return 'e';
            case 0x3e: return 'g';
            case 0x3f: return 'q';
            case 0x40: return 'c';
            }
        }
    } else {
        if (v == 0x5e) return 'x';
        if (v == 0x7c) return 'o';
        if (v == 0x7e) return 't';
    }
id26:
    return p1;
}

/* FUN_003b12cc @ 0x3b12cc   (est. sk_ident_mnemonize)
 * Initializes a byte vector and appends the single-letter mnemonic of each
 * character of param_2 (via b1178) using FUN_001130a0. Returns nothing.
 * Confidence: high */
static void sk_003b12cc(uint64_t *v, char *s, uint64_t n)
{
    v[0] = 0; v[1] = 0; v[2] = 0;
    for (; n != 0; n = n - 1) {
        uint64_t m = sk_003b1178((uint64_t)*s);
        sk_vec_byte_append(v, (uint8_t)m);
        s = s + 1;
    }
}

/* FUN_003b1328 @ 0x3b1328   (est. sk_protocol_name_map)
 * Maps a type/protocol name (param_2, length param_3) to a canonical string
 * label stored in param_1 (a {data,len,flag} struct). It matches known Swift
 * protocol names via memcmp against a large table and emits the short label
 * (sub-flag 1) or a fallback protocol-family label (sub-flag 2). Sets the
 * struct's flag byte. Returns nothing.
 * Confidence: high (string-matched) */
static void sk_003b1328(uint64_t *p1, uint64_t *p2, uint64_t p3, int32_t p4)
{
    char *label;
    int32_t iret;
    if (0x1e < p3 - 3U) goto c_case;
    switch (p3) {
    default:
        iret = sk_memcmp(p2, &DAT_005d6a55, p3);
        if (iret == 0) label = &DAT_005d6fc9;
        else {
            iret = sk_memcmp(p2, &DAT_005d6a68, p3);
            if (iret != 0) goto c_case;
            label = &DAT_005d6fcb;
        }
        break;
    case 4:
        iret = sk_memcmp(p2, &DAT_005d6a38, p3);
        if (iret == 0) label = &DAT_005d6fc3;
        else {
            iret = sk_memcmp(p2, &DAT_005d6afc, p3);
            if (iret != 0) goto c_case;
            label = &DAT_005d6fd5;
        }
        break;
    case 5:
        iret = sk_memcmp(p2, s_Array_005d6a32, p3);
        if (iret == 0) label = &DAT_005d6fc1;
        else {
            iret = sk_memcmp(p2, s_Float_005d6a4f, p3);
            if (iret == 0) label = &DAT_005d6fc7;
            else {
                iret = sk_memcmp(p2, s_Range_005d6a82, p3);
                if (iret != 0) goto c_case;
                label = &DAT_005d6fcd;
            }
        }
        break;
    case 6:
        iret = sk_memcmp(p2, s_Double_005d6a48, p3);
        if (iret == 0) label = &DAT_005d6fc5;
        else {
            iret = sk_memcmp(p2, s_String_005d6aeb, p3);
            if (iret != 0) goto c_case;
            label = &DAT_005d37d7;
        }
        break;
    case 7:
        iret = sk_memcmp(p2, s_Numeric_005d6bb6, p3);
        if (iret != 0) goto c_case;
        label = &DAT_005d6fe3;
        break;
    case 8:
        iret = sk_memcmp(p2, s_Optional_005d4e8b, p3);
        if (iret == 0) label = &DAT_005d6fdf;
        else {
            iret = sk_memcmp(p2, s_Hashable_005d6bad, p3);
            if (iret == 0) label = &DAT_005d37e9;
            else {
                iret = sk_memcmp(p2, s_Sequence_005d6c3c, p3);
                if (iret != 0) goto c_case;
                label = &DAT_005d37e5;
            }
        }
        break;
    case 9:
        iret = sk_memcmp(p2, s_Character_005d6a6c, p3);
        if (iret == 0) label = &DAT_005d37dc;
        else {
            iret = sk_memcmp(p2, s_Substring_005d6af2, p3);
            if (iret == 0) label = &DAT_005d6fd3;
            else {
                iret = sk_memcmp(p2, s_Encodable_005d6b73, p3);
                if (iret == 0) label = &DAT_005d356c;
                else if (*p2 == 0x6c6261646f636544 && (char)p2[1] == 'e') label = &DAT_005d6b7d;
                else {
                    iret = sk_memcmp(p2, s_Equatable_005d6c32, p3);
                    if (iret != 0) goto c_case;
                    label = &DAT_005d6fe9;
                }
            }
        }
        break;
    case 10:
        iret = sk_memcmp(p2, s_Dictionary_005d6a3d, p3);
        if (iret == 0) label = &DAT_005d37cb;
        else {
            iret = sk_memcmp(p2, s_Comparable_005d6bed, p3);
            if (iret == 0) label = &DAT_005d356e;
            else if (*p2 == 0x697463656c6c6f43 && (int16_t)p2[1] == 0x6e6f) label = &DAT_005d6fe7;
            else {
                iret = sk_memcmp(p2, s_Strideable_005d6c76, p3);
                if (iret != 0) goto c_case;
                label = &DAT_005d6fef;
            }
        }
        break;
    case 0xb:
        iret = sk_memcmp(p2, s_ClosedRange_005d6a76, p3);
        if (iret != 0) goto c_case;
        label = &DAT_005d37c9;
        break;
    case 0xc: case 0x12: case 0x18: case 0x19: case 0x1b: case 0x1c:
    case 0x1e: case 0x1f: case 0x20:
        goto c_case;
    case 0xd:
        iret = sk_memcmp(p2, s_UnsafePointer_005d6a99, p3);
        if (iret == 0) label = &DAT_005c9984;
        else {
            iret = sk_memcmp(p2, s_FloatingPoint_005d6b89, p3);
            if (iret == 0) label = &DAT_005d6fe1;
            else {
                iret = sk_memcmp(p2, s_SignedInteger_005d6ca1, p3);
                if (iret == 0) label = &DAT_005d6ff5;
                else {
                    if (*p2 != 0x6e497972616e6942 ||
                        *(int64_t *)((char *)p2 + 5) != 0x72656765746e4979) goto c_case;
                    label = &DAT_005d6ff7;
                }
            }
        }
        break;
    case 0xe:
        iret = sk_memcmp(p2, s_DefaultIndices_005d6a59, p3);
        if (iret == 0) label = &DAT_005d356a;
        else {
            iret = sk_memcmp(p2, s_StringProtocol_005d6c92, p3);
            if (iret != 0) goto c_case;
            label = &DAT_005d6ff3;
        }
        break;
    case 0xf:
        iret = sk_memcmp(p2, s_UnsignedInteger_005d6c56, p3);
        if (iret == 0) label = &DAT_005d3810;
        else {
            if (*p2 != 0x70784565676e6152 ||
                *(int64_t *)((char *)p2 + 7) != 0x6e6f697373657270) goto c_case;
            label = &DAT_005d6fed;
        }
        break;
    case 0x10:
        iret = sk_memcmp(p2, s_ObjectIdentifier_005d6a88, p3);
        if (iret == 0) label = &DAT_005d3801;
        else {
            iret = sk_memcmp(p2, s_UnsafeRawPointer_005d6b01, p3);
            if (iret == 0) label = &DAT_005d6fd7;
            else {
                iret = sk_memcmp(p2, s_IteratorProtocol_005d6c45, p3);
                if (iret == 0) label = &DAT_005d6feb;
                else {
                    iret = sk_memcmp(p2, s_RawRepresentable_005d6c81, p3);
                    if (iret != 0) goto c_case;
                    label = &DAT_005d6ff1;
                }
            }
        }
        break;
    case 0x11:
        iret = sk_memcmp(p2, s_MutableCollection_005d6c03, p3);
        if (iret != 0) goto c_case;
        label = &DAT_005d37d0;
        break;
    case 0x13:
        iret = sk_memcmp(p2, s_UnsafeBufferPointer_005d6abc, p3);
        if (iret == 0) label = &DAT_005d3568;
        else {
            iret = sk_memcmp(p2, s_BinaryFloatingPoint_005d6b5f, p3);
            if (iret != 0) goto c_case;
            label = &DAT_005d37d2;
        }
        break;
    case 0x14:
        iret = sk_memcmp(p2, s_UnsafeMutablePointer_005d6aa7, p3);
        if (iret != 0) goto c_case;
        label = &DAT_005d6fcf;
        break;
    case 0x15:
        iret = sk_memcmp(p2, s_RandomNumberGenerator_005d6b97, p3);
        if (iret != 0) goto c_case;
        label = &DAT_005d37c4;
        break;
    case 0x16:
        iret = sk_memcmp(p2, s_UnsafeRawBufferPointer_005d6b2a, p3);
        if (iret == 0) label = &DAT_005d6fdb;
        else {
            iret = sk_memcmp(p2, s_RandomAccessCollection_005d6bd6, p3);
            if (iret != 0) goto c_case;
            label = &DAT_005d6fe5;
        }
        break;
    case 0x17:
        iret = sk_memcmp(p2, s_UnsafeMutableRawPointer_005d6b12, p3);
        if (iret == 0) label = &DAT_005d6fd9;
        else {
            iret = sk_memcmp(p2, s_BidirectionalCollection_005d6bbe, p3);
            if (iret != 0) goto c_case;
            label = &DAT_005d37e3;
        }
        break;
    case 0x1a:
        iret = sk_memcmp(p2, s_UnsafeMutableBufferPointer_005d6ad0, p3);
        if (iret == 0) label = &DAT_005d6fd1;
        else {
            iret = sk_memcmp(p2, s_RangeReplaceableCollection_005d6c17, p3);
            if (iret != 0) goto c_case;
            label = &DAT_005d6c15;
        }
        break;
    case 0x1d:
        iret = sk_memcmp(p2, s_UnsafeMutableRawBufferPointer_005d6b41, p3);
        if (iret != 0) goto c_case;
        label = &DAT_005d6fdd;
        break;
    case 0x21:
        iret = sk_memcmp(p2, s_AutoreleasingUnsafeMutablePointe_005d6a10, 0x21);
        if (iret == 0) {
            *p1 = (uint64_t)&DAT_005d37eb;
            p1[1] = 1;
            p1[2] = (uint8_t)1;
            return;
        }
        goto c_case;
    }
    *p1 = (uint64_t)label;
    p1[1] = 1;
    p1[2] = (uint8_t)1;
    return;
c_case:
    if (p4 == 0 || 0x11 < p3 - 4U) {
    c_case6:
        *p1 = 0;
        *(uint8_t *)p1 = 0;
        p1[2] = (uint8_t)0;
        return;
    }
    switch (p3) {
    default:
        iret = sk_memcmp(p2, &DAT_005d4ec0, p3);
        if (iret != 0) goto c_case6;
        label = &DAT_005d702c;
        break;
    case 5:
        if ((int32_t)*p2 != 0x6f746341 || *(char *)((char *)p2 + 4) != 'r') goto c_case6;
        label = &DAT_005d6ff9;
        break;
    case 6: case 7: case 0xf: case 0x10: case 0x14:
        goto c_case6;
    case 8:
        iret = sk_memcmp(p2, s_Executor_005d6d14, p3);
        if (iret != 0) goto c_case6;
        label = &DAT_005d7008;
        break;
    case 9:
        iret = sk_memcmp(p2, s_TaskGroup_005d6d2c, p3);
        if (iret == 0) label = &DAT_005d700e;
        else {
            iret = sk_memcmp(p2, s_MainActor_005d6d84, p3);
            if (iret != 0) goto c_case6;
            label = &DAT_005d7020;
        }
        break;
    case 10:
        iret = sk_memcmp(p2, s_UnownedJob_005d6d79, p3);
        if (iret != 0) goto c_case6;
        label = &DAT_005d701d;
        break;
    case 0xb:
        iret = sk_memcmp(p2, s_AsyncStream_005d6d9b, p3);
        if (iret != 0) goto c_case6;
        label = &DAT_005d7026;
        break;
    case 0xc:
        iret = sk_memcmp(p2, s_TaskExecutor_005d6d48, p3);
        if (iret == 0) label = &DAT_005d7014;
        else {
            iret = sk_memcmp(p2, s_TaskPriority_005d6d8e, p3);
            if (iret != 0) goto c_case6;
            label = &DAT_005d7023;
        }
        break;
    case 0xd:
        iret = sk_memcmp(p2, s_AsyncSequence_005d6d6b, p3);
        if (iret != 0) goto c_case6;
        label = &DAT_005d701a;
        break;
    case 0xe:
        iret = sk_memcmp(p2, s_SerialExecutor_005d6d1d, p3);
        if (iret != 0) goto c_case6;
        label = &DAT_005d700b;
        break;
    case 0x11:
        iret = sk_memcmp(p2, s_CancellationError_005d6cec, p3);
        if (iret == 0) label = &DAT_005d7002;
        else {
            iret = sk_memcmp(p2, s_ThrowingTaskGroup_005d6d36, p3);
            if (iret == 0) label = &DAT_005d7011;
            else {
                iret = sk_memcmp(p2, s_UnsafeCurrentTask_005d6dbb, p3);
                if (iret != 0) goto c_case6;
                label = &DAT_005d702f;
            }
        }
        break;
    case 0x12:
        iret = sk_memcmp(p2, s_UnsafeContinuation_005d6cd9, p3);
        if (iret != 0) goto c_case6;
        label = &DAT_005d6fff;
        break;
    case 0x13:
        iret = sk_memcmp(p2, s_CheckedContinuation_005d6cc3, p3);
        if (iret == 0) label = &DAT_005d6ffc;
        else {
            iret = sk_memcmp(p2, s_AsyncThrowingStream_005d6da7, p3);
            if (iret != 0) goto c_case6;
            label = &DAT_005d7029;
        }
        break;
    case 0x15:
        iret = sk_memcmp(p2, s_UnownedSerialExecutor_005d6cfe, p3);
        if (iret == 0) label = &DAT_005d7005;
        else {
            iret = sk_memcmp(p2, s_AsyncIteratorProtocol_005d6d55, p3);
            if (iret != 0) goto c_case6;
            label = &DAT_005d7017;
        }
    }
    *p1 = (uint64_t)label;
    p1[1] = 2;
    p1[2] = (uint8_t)1;
}

/* FUN_003b1e74 @ 0x3b1e74   (est. sk_log_msg_spec1)
 * Builds a log message from (p2,p3) using a spec string (b1eec) and emits it
 * via log_msg. Verifies the stack canary; returns param_1.
 * Confidence: medium */
static uint64_t sk_003b1e74(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint64_t scratch[4];
    uint64_t canary = (uint64_t)-0x2c8502b44bfffed6;
    sk_003b1eec((uint64_t *)scratch, p2, p3, (uint64_t)&DAT_005d7032);
    sk_log_msg(st, scratch);
    if (canary == (uint64_t)-0x2c8502b44bfffed6) return (uint64_t)st;
    sk_canary_panic();
}

/* FUN_003b1eec @ 0x3b1eec   (est. sk_log_format)
 * Calls obj_lock(0x20) with a format specifier, initializing a message
 * buffer. Returns nothing.
 * Confidence: medium */
static void sk_003b1eec(uint64_t *st, uint64_t p2, uint64_t p3, uint64_t p4)
{
    sk_obj_lock((uint64_t)st, 0x20);
}

/* FUN_003b1f20 @ 0x3b1f20   (est. sk_log_msg_spec2)
 * Same as b1e74 but with spec DAT_005d7037. Returns param_1.
 * Confidence: medium */
static uint64_t sk_003b1f20(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint64_t scratch[4];
    uint64_t canary = (uint64_t)-0x2c8502b44bfffed6;
    sk_003b1eec((uint64_t *)scratch, p2, p3, (uint64_t)&DAT_005d7037);
    sk_log_msg(st, scratch);
    if (canary == (uint64_t)-0x2c8502b44bfffed6) return (uint64_t)st;
    sk_canary_panic();
}

/* FUN_003b1f98 @ 0x3b1f98   (est. sk_log_msg_spec3)
 * Same as b1e74 but with spec DAT_005d703c. Returns param_1.
 * Confidence: medium */
static uint64_t sk_003b1f98(uint64_t *st, uint64_t p2, uint64_t p3)
{
    uint64_t scratch[4];
    uint64_t canary = (uint64_t)-0x2c8502b44bfffed6;
    sk_003b1eec((uint64_t *)scratch, p2, p3, (uint64_t)&DAT_005d703c);
    sk_log_msg(st, scratch);
    if (canary == (uint64_t)-0x2c8502b44bfffed6) return (uint64_t)st;
    sk_canary_panic();
}

/* FUN_003b2010 @ 0x3b2010   (est. sk_bijective_label)
 * Converts param_3 to a bijective-base-26 column label (A, B, ..., Z, AA,
 * ...) appended via byte-append, then optionally emits an extra spec message
 * (b1eec) when param_2 is set, storing the resulting {ptr,count,cap} into
 * param_1. Returns nothing.
 * Confidence: medium */
static void sk_003b2010(uint64_t *p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t canary = (uint64_t)-0x2c8502b44bfffed6;
    uint64_t local80 = 0, stk78 = 0, local70 = 0;
    bool b;
    do {
        sk_vec_byte_append(&local80, (uint8_t)((char)p3 + (char)(p3 / 0x1a) * -0x1a + 'A'));
        b = 0x19 < p3;
        p3 = p3 / 0x1a;
    } while (b);
    if (p2 != 0) {
        uint64_t scratch[4];
        sk_003b1eec((uint64_t *)scratch, 0, p4, (uint64_t)&DAT_005d7032);
        sk_log_msg((uint64_t *)&local80, scratch);
    }
    p1[1] = stk78;
    p1[0] = local80;
    p1[2] = local70;
    if (canary == (uint64_t)-0x2c8502b44bfffed6) return;
    sk_canary_panic();
}

/* FUN_003b20f4 @ 0x3b20f4   (est. sk_emit_child_list)
 * Iterates param_2..param_3 (exclusive), pretty-printing each node via b2180
 * at depth param_4+1, and when param_5 (a separator) is set, emits it between
 * items. Returns nothing.
 * Confidence: medium */
static void sk_003b20f4(uint64_t *st, uint64_t *p2, uint64_t *p3, int32_t p4, uint64_t p5)
{
    while (p2 != p3) {
        uint64_t *next = p2 + 1;
        sk_003b2180((uint64_t *)st, (uint64_t *)*p2, (uint64_t)(p4 + 1), 0);
        p2 = next;
        if (p5 != 0 && next != p3) {
            uint64_t len = (uint64_t)sk_len_query(p5);
            sk_out_str((uint64_t *)((char *)st + 8), (const char *)p5, (long)len);
        }
    }
}

/* FUN_003b8d18 @ 0x3b8d18   (est. sk_emit_child_list_walk)
 * Walks a node's child pointer range (based on its sub-type) and emits each
 * child via b20f4. Returns nothing.
 * Confidence: medium */
static void sk_003b8d18(uint64_t *st, uint64_t *p2, uint64_t p3, uint64_t p4)
{
    if (p2 == 0) return;
    uint8_t b = NODE_SUBT(p2);
    uint64_t *pl2 = p2;
    uint64_t end;
    if (1 < b - 1) {
        if (b == 5) {
            pl2 = (uint64_t *)*p2;
            end = (uint64_t)pl2;
            goto l8d70;
        }
        pl2 = 0;
    }
    if (b == 1) {
        sk_003b20f4(st, pl2, p2 + 1, (int32_t)p3, p4);
        return;
    }
    if (b == 2) {
        sk_003b20f4(st, pl2, p2 + 2, (int32_t)p3, p4);
        return;
    }
    if (b != 5) {
        sk_003b20f4(st, pl2, 0, (int32_t)p3, p4);
        return;
    }
    end = *p2;
l8d70:
    sk_003b20f4(st, pl2, (uint64_t *)(end + (uint64_t)*(uint32_t *)(p2 + 1) * 8),
                (int32_t)p3, p4);
}

/* FUN_003b8d94 @ 0x3b8d94   (est. sk_emit_2elem_tuple)
 * Emits a two-element tuple: prints the first element via b2180, a separator
 * (DAT_005d3cc6), the remaining children via b8d18, and a closing marker.
 * Returns nothing.
 * Confidence: medium */
static void sk_003b8d94(uint64_t *st, uint64_t *p2, uint64_t p3)
{
    if (NODE_SUBT(p2) != 2) {
        if (NODE_SUBT(p2) != 5 || (uint32_t)p2[1] < 2) return;
        p2 = (uint64_t *)*p2;
    }
    uint64_t v1 = p2[1];
    sk_003b2180(st, (uint64_t *)*p2, (uint64_t)((int32_t)p3 + 1), 0);
    sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005d3cc6, 1);
    sk_003b8d18(st, (uint64_t *)v1, p3, (uint64_t)&DAT_005d0c46);
    sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005cf438, 1);
}

/* FUN_003b8e48 @ 0x3b8e48   (est. sk_emit_subtype4_msg)
 * If the node's sub-type is 4, emits a '[' + formatted message + ']' around
 * it. Returns nothing.
 * Confidence: medium */
static void sk_003b8e48(uint64_t *st, uint64_t p2)
{
    uint64_t canary = (uint64_t)-0x2c8502b44bfffed6;
    if (NODE_SUBT((uint64_t *)p2) == 4) {
        sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005d7041, 1);
        uint64_t scratch[4];
        sk_003b1eec((uint64_t *)scratch, 0, 0, 0);
        sk_log_msg((uint64_t *)((char *)st + 8), scratch);
        sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005d021c, 1);
    }
    if (canary == (uint64_t)-0x2c8502b44bfffed6) return;
    sk_canary_panic();
}

/* FUN_003b8ef8 @ 0x3b8ef8   (est. sk_attr_match_check)
 * Checks whether a 0xa3 attribute node matches the current context's expected
 * kind: returns the context byte (at +0x30/+0x31/+0x32) for the
 * __llbd_e/__xpr_/_Swift/__C kinds, a memcmp result for exact-length kinds,
 * else 1. Returns the match byte.
 * Confidence: medium */
static uint8_t sk_003b8ef8(uint64_t *st, uint64_t *p2)
{
    if (*(uint8_t *)((char *)st + 0x21) != 1) {
        return 0;
    }
    if (NODE_TAG(p2) != 0xa3) return 1;
    uint64_t *data = (uint64_t *)*p2;
    uint64_t len = p2[1];
    if (len == 3) {
        if (NODE_TAG(data) == 0x5f5f && *(uint8_t *)((char *)data + 2) == 'C') {
            return *(uint8_t *)((char *)st + 0x32);
        }
        if (*(uint64_t *)((char *)st + 0x40) == 3) goto l8fb8;
    } else {
        if (len == 5) {
            if ((int32_t)*data == 0x66697753 && *(uint8_t *)((char *)data + 4) == 't') {
                return *(uint8_t *)((char *)st + 0x31);
            }
            if (*(uint64_t *)((char *)st + 0x40) != 5) goto l9000;
        l8fb8:
            if (sk_memcmp(data, *(void **)((char *)st + 0x38), len) == 0) return 0;
        } else if (len == *(uint64_t *)((char *)st + 0x40)) {
            if (len != 0) goto l8fb8;
            return 0;
        }
        if (0xb < len && *data == 0x655f62646c6c5f5f && (int32_t)data[1] == 0x5f727078) {
            return *(uint8_t *)((char *)st + 0x30);
        }
    }
l9000:
    return 1;
}

/* FUN_003b903c @ 0x3b903c   (est. sk_query_flag)
 * Tests a node's shape: returns 1 for scalar/leaf tags (0xc9 empty, 0xcb
 * empty, and a set of printable tags), 0 for a 0xf4 wrapper, and recurses
 * into wrapped elements. Returns the classification flag.
 * Confidence: medium */
static uint64_t sk_003b903c(uint64_t p1, uint64_t *p2)
{
    uint64_t *pl2 = p2;
    uint64_t r = 0;
    uint64_t l3 = 0;
    for (;;) {
        pl2 = p2;
        if (0x179 < NODE_TAG(pl2)) {
            /* bad tag: fatal path */
            sk_004ba498(p1);
        }
        p1 = 0;
        switch (NODE_TAG(pl2)) {
        default: return p1;
        case 0xc9: {
            uint64_t *e = pl2;
            if (1 < NODE_SUBT(pl2) - 1) {
                if (NODE_SUBT(pl2) != 5 || (int32_t)pl2[1] == 0) { l3 = 0; goto l917c; }
                e = (uint64_t *)*pl2;
            }
            l3 = (uint64_t)*e;
        l917c:
            if (NODE_SUBT((uint64_t *)l3) != 5) return (uint64_t)(NODE_SUBT((uint64_t *)l3) != 2);
            return (uint64_t)(*(uint32_t *)(l3 + 8) < 2);
        }
        case 0xcb: {
            uint64_t *e = pl2;
            if (NODE_SUBT(pl2) - 1 < 2) { e = (uint64_t *)*e; goto l90d4; }
            if (NODE_SUBT(pl2) == 5 && (int32_t)pl2[1] != 0) { e = (uint64_t *)*e; goto l90d4; }
            e = 0;
        l90d4:
            l3 = 0;
            if (NODE_SUBT(e) - 1 < 2) l3 = (uint64_t)*e;
            else if (NODE_SUBT(e) == 5 && (int32_t)e[1] != 0) { e = (uint64_t *)*e; l3 = (uint64_t)*e; }
            if (NODE_SUBT((uint64_t *)l3) - 1 < 2) return 0;
            if (NODE_SUBT((uint64_t *)l3) == 5) return (uint64_t)(*(int32_t *)(l3 + 8) == 0);
            return p1;
        }
        case 4: case 5: case 0xd: case 0xe: case 0xf: case 0x10: case 0x11:
        case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x19:
        case 0x27: case 0x2d: case 0x2e: case 0x3b: case 0x3f: case 0x41:
        case 0x47: case 0x56: case 0x57: case 0x9a: case 0x9b: case 0xa3:
        case 0xb1: case 0xbf: case 0xc0: case 0xdb: case 0xde: case 0xdf:
        case 0xe7: case 0xeb: case 0xed: case 0xee: case 0xef: case 0xf0:
        case 0xf5: case 0xf6: case 0xf7: case 0x130: case 0x135: case 0x136:
        case 0x137: case 0x138: case 0x139: case 0x172: case 0x173:
            p1 = 1;
            return p1;
        case 0xf4:
            break;
        }
        if (1 < NODE_SUBT(pl2) - 1) {
            p2 = 0;
            if (NODE_SUBT(pl2) == 5 && (int32_t)pl2[1] != 0) {
                pl2 = (uint64_t *)*pl2;
                p2 = (uint64_t *)*pl2;
            }
        } else {
            p2 = (uint64_t *)*pl2;
        }
    }
}

/* FUN_003b9794 @ 0x3b9794   (est. sk_emit_wrapped_val)
 * Emits a value via b2180; if b903c flags it as non-simple, wraps with
 * brackets ('[' and ']'). Returns nothing.
 * Confidence: medium */
static void sk_003b9794(uint64_t *st, uint64_t p2, int32_t p3)
{
    if ((sk_003b903c(0, 0) & 1) != 0) {
        sk_003b2180(st, (uint64_t *)p2, (uint64_t)(p3 + 1), 0);
        return;
    }
    sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005d3bb7, 1);
    sk_003b2180(st, (uint64_t *)p2, (uint64_t)(p3 + 1), 0);
    sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005ce788, 1);
}

/* FUN_003b982c @ 0x3b982c   (est. sk_container_kind)
 * Classifies a container node: returns 1 for Optional, 2 for
 * ImplicitlyUnwrappedOptional, 3 for Array, 4 for Dictionary, else 0, by
 * inspecting the wrapped 0xe/0xf5/0xf4 structure and matching protocol names.
 * Confidence: medium */
static uint64_t sk_003b982c(uint64_t *st, uint64_t *p2)
{
    uint64_t *pu6 = p2;
    for (;;) {
        uint8_t b = NODE_SUBT(pu6);
        uint32_t u8 = b;
        if (u8 != 1) {
            if (u8 != 5) {
                if (b != 2) return 0;
                goto l98c4;
            }
            if ((int32_t)pu6[1] != 1) goto l98b8;
        }
        if (NODE_TAG(pu6) == 0xf4) {
            if (1 < u8 - 1) goto code_r;
            goto l9890;
        }
        if (b != 2) {
            if (b != 5) return 0;
            if ((int32_t)pu6[1] != 2) return 0;
            b = 5;
        }
    l98c4:
        {
            uint16_t t = NODE_TAG(pu6);
            if ((t & 0xfffe) != 0xe) return 0;
            uint64_t *pu9 = pu6;
            if (b == 2) { pu9 = (uint64_t *)*pu9; goto l98f4; }
            if (b == 5 && (int32_t)pu6[1] != 0) { pu9 = (uint64_t *)*pu6; goto l98f4; }
            pu9 = 0;
        l98f4:
            if (NODE_SUBT(pu9) - 1 < 2) pu9 = (uint64_t *)*pu9;
            else if (NODE_SUBT(pu9) == 5 && (int32_t)pu9[1] != 0) { pu9 = (uint64_t *)*pu9; pu9 = (uint64_t *)*pu9; }
            else pu9 = 0;
            uint64_t l10;
            if (b == 2) l10 = pu6[1];
            else if (b == 5 && 1 < (uint32_t)pu6[1]) { pu6 = (uint64_t *)*pu6; l10 = pu6[1]; }
            else l10 = 0;
            char c = NODE_SUBT(pu9);
            if ((t & 0xfffe) == 0xe) {
                /* Optional family */
                uint64_t u4;
                if (c == 2) u4 = pu9[1];
                else if (c == 5 && 1 < (uint32_t)pu9[1]) { pu9 = (uint64_t *)*pu9; u4 = pu9[1]; }
                else u4 = 0;
                if (sk_003b9c14((uint64_t *)u4, (uint64_t)s_Optional_005d4e8b, 8) != 0 &&
                    (NODE_SUBT((uint64_t *)l10) == 1 || (NODE_SUBT((uint64_t *)l10) == 5 && *(int32_t *)(l10 + 8) == 1))) {
                    uint64_t v = (NODE_SUBT(pu9) - 1 < 2) ? (uint64_t)*pu9 :
                        (NODE_SUBT(pu9) == 5 && (int32_t)pu9[1] != 0) ? (uint64_t)*(uint64_t *)*pu9 : 0;
                    if ((sk_003b9c6c((uint64_t *)v) & 1) != 0) return 1;
                }
                uint64_t u4b;
                if (c == 2) u4b = pu9[1];
                else if (c == 5 && 1 < (uint32_t)pu9[1]) { pu9 = (uint64_t *)*pu9; u4b = pu9[1]; }
                else u4b = 0;
                if (sk_003b9c14((uint64_t *)u4b, (uint64_t)s_ImplicitlyUnwrappedOptional_005d7051, 0x1b) == 0) return 0;
                if (NODE_SUBT((uint64_t *)l10) != 1) {
                    if (NODE_SUBT((uint64_t *)l10) != 5) return 0;
                    if (*(int32_t *)(l10 + 8) != 1) return 0;
                }
                uint64_t v2 = (NODE_SUBT(pu9) - 1 < 2) ? (uint64_t)*pu9 :
                    (NODE_SUBT(pu9) == 5 && (int32_t)pu9[1] != 0) ? (uint64_t)*(uint64_t *)*pu9 : 0;
                if ((sk_003b9c6c((uint64_t *)v2) & 1) == 0) return 0;
                return 2;
            }
            /* Array / Dictionary */
            uint64_t u4c;
            if (c == 2) u4c = pu9[1];
            else if (c == 5 && 1 < (uint32_t)pu9[1]) { pu9 = (uint64_t *)*pu9; u4c = pu9[1]; }
            else u4c = 0;
            if (sk_003b9c14((uint64_t *)u4c, (uint64_t)s_Array_005d6a32, 5) != 0 &&
                (NODE_SUBT((uint64_t *)l10) == 1 || (NODE_SUBT((uint64_t *)l10) == 5 && *(int32_t *)(l10 + 8) == 1))) {
                uint64_t v3 = (NODE_SUBT(pu9) - 1 < 2) ? (uint64_t)*pu9 :
                    (NODE_SUBT(pu9) == 5 && (int32_t)pu9[1] != 0) ? (uint64_t)*(uint64_t *)*pu9 : 0;
                if ((sk_003b9c6c((uint64_t *)v3) & 1) != 0) return 3;
            }
            uint64_t u4d;
            if (c == 2) u4d = pu9[1];
            else if (c == 5 && 1 < (uint32_t)pu9[1]) { pu9 = (uint64_t *)*pu9; u4d = pu9[1]; }
            else u4d = 0;
            if (sk_003b9c14((uint64_t *)u4d, (uint64_t)s_Dictionary_005d6a3d, 10) == 0) return 0;
            if (NODE_SUBT((uint64_t *)l10) != 2) {
                if (NODE_SUBT((uint64_t *)l10) != 5) return 0;
                if (*(int32_t *)(l10 + 8) != 2) return 0;
            }
            uint64_t v4 = (NODE_SUBT(pu9) - 1 < 2) ? (uint64_t)*pu9 :
                (NODE_SUBT(pu9) == 5 && (int32_t)pu9[1] != 0) ? (uint64_t)*(uint64_t *)*pu9 : 0;
            if ((sk_003b9c6c((uint64_t *)v4) & 1) == 0) return 0;
            return 4;
        }
    l98b8:
        if ((int32_t)pu6[1] != 2) return 0;
        b = 5;
        goto l98c4;
    code_r:
        p2 = 0;
        if (b == 5 && (int32_t)pu6[1] != 0) {
            pu6 = (uint64_t *)*pu6;
            p2 = (uint64_t *)*pu6;
        }
        goto l9890;
    l9890:
        p2 = (uint64_t *)*pu6;
    }
}

/* FUN_003b9c14 @ 0x3b9c14   (est. sk_str_eq_67)
 * Returns true if param_1 is a 0x67 scalar holding the string param_2 of
 * length param_3. Confidence: high */
static bool sk_003b9c14(uint64_t *p1, uint64_t p2, uint64_t p3)
{
    if (NODE_TAG(p1) == 0x67 && p1[1] == p3) {
        if (p1[1] != 0) {
            return sk_memcmp((void *)*p1, (const void *)p2, p3) == 0;
        }
        return true;
    }
    return false;
}

/* FUN_003b9c6c @ 0x3b9c6c   (est. sk_is_swift_attr)
 * Returns true if param_1 is a 0xa3 scalar of length 5 holding "Swift".
 * Confidence: high */
static bool sk_003b9c6c(uint64_t *p1)
{
    if (NODE_TAG(p1) == 0xa3 && p1[1] == 5) {
        return *(int32_t *)*p1 == 0x66697753 && (char)((int32_t *)*p1)[1] == 't';
    }
    return false;
}

/* FUN_003b9cb4 @ 0x3b9cb4   (est. sk_emit_container)
 * Emits a container node: two-element tuples via b8d94; tag 0x10 pairs via
 * b8d18 + ' -> ' + b2180; and typed containers (kind from b982c) with their
 * element/separator rendering. Returns nothing.
 * Confidence: medium */
static void sk_003b9cb4(uint64_t *st, uint64_t *p2, uint64_t p3)
{
    char c = NODE_SUBT(p2);
    if (c != 2) {
        if (c != 5 || (uint32_t)p2[1] < 2) return;
        if ((uint32_t)p2[1] != 2) goto l9d28;
    }
    if (*(uint8_t *)((char *)st + 0x20) != 1) goto l9d28;
    {
        int32_t depth = (int32_t)p3;
        if (NODE_TAG(p2) == 0x10) {
            uint64_t *pl6 = p2;
            uint64_t u3;
            if (c == 2) u3 = *(uint64_t *)((char *)pl6 + 8);
            else if (c == 5 && 1 < (uint32_t)p2[1]) { pl6 = (uint64_t *)*p2; u3 = *(uint64_t *)((char *)pl6 + 8); }
            else u3 = 0;
            sk_003b8d18(st, (uint64_t *)u3, p3, 0);
            sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005d706d, 4);
            uint64_t v2 = (NODE_SUBT(p2) - 1 < 2) ? (uint64_t)*p2 :
                (NODE_SUBT(p2) == 5 && (int32_t)p2[1] != 0) ? (uint64_t)*(uint64_t *)*p2 : 0;
            sk_003b2180(st, (uint64_t *)v2, (uint64_t)(depth + 1), 0);
            return;
        }
        if (NODE_TAG(p2) == 0xd) goto l9d28;
        int32_t kind = (int32_t)sk_003b982c(st, p2);
        if (2 < kind) {
            uint64_t u3, u8;
            const char *sep;
            uint64_t seplen;
            if (kind == 3) {
                uint64_t *pl6 = (c == 2) ? (uint64_t *)p2[1] : (c == 5 && 1 < (uint32_t)p2[1]) ? (uint64_t *)*(uint64_t *)*p2 : 0;
                u8 = (NODE_SUBT(pl6) - 1 < 2) ? (uint64_t)*pl6 :
                    (NODE_SUBT(pl6) == 5 && (int32_t)pl6[1] != 0) ? (uint64_t)*(uint64_t *)*pl6 : 0;
                sep = &DAT_005d3566; seplen = 1;
            } else {
                uint64_t *pl6 = (c == 2) ? (uint64_t *)p2[1] : (c == 5 && 1 < (uint32_t)p2[1]) ? (uint64_t *)*(uint64_t *)*p2 : 0;
                u3 = (NODE_SUBT(pl6) - 1 < 2) ? (uint64_t)*pl6 :
                    (NODE_SUBT(pl6) == 5 && (int32_t)pl6[1] != 0) ? (uint64_t)*(uint64_t *)*pl6 : 0;
                uint64_t *pu5 = (c == 2) ? (uint64_t *)p2[1] : (c == 5 && 1 < (uint32_t)p2[1]) ? (uint64_t *)*(uint64_t *)*p2 : 0;
                uint64_t u8b = (NODE_SUBT(pu5) == 2) ? pu5[1] :
                    (NODE_SUBT(pu5) == 5 && 1 < (uint32_t)pu5[1]) ? (uint64_t)*(uint64_t *)*pu5 : 0;
                sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005d3566, 1);
                sk_003b2180(st, (uint64_t *)u3, (uint64_t)(depth + 1), 0);
                sep = &DAT_005d3cba; seplen = 3;
                u8 = u8b;
            }
            sk_out_str((uint64_t *)((char *)st + 8), sep, seplen);
            sk_003b2180(st, (uint64_t *)u8, (uint64_t)(depth + 1), 0);
            sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005d32c2, 1);
            return;
        }
        if (1 < (uint32_t)(kind - 1)) goto l9d28;
        {
            uint64_t *pu5 = (c == 2) ? (uint64_t *)((char *)p2 + 8) : (c == 5 && 1 < (uint32_t)p2[1]) ? (uint64_t *)*(uint64_t *)*p2 : 0;
            uint64_t u3 = (NODE_SUBT(pu5) - 1 < 2) ? (uint64_t)*pu5 :
                (NODE_SUBT(pu5) == 5 && (int32_t)pu5[1] != 0) ? (uint64_t)*(uint64_t *)*pu5 : 0;
            sk_003b9794(st, u3, p3);
            sk_out_str((uint64_t *)((char *)st + 8), (const char *)((kind != 1) ? &DAT_005d3a39 : &DAT_005dd27a), 1);
            return;
        }
    }
l9d28:
    sk_003b8d94(st, p2, p3);
}

/* FUN_003ba044 @ 0x3ba044   (est. sk_find_child_tag)
 * Searches a node's child array for the first child whose tag equals param_3,
 * returning it; returns 0 if not found. Walks based on the node's sub-type.
 * Confidence: high */
static uint64_t sk_003ba044(uint64_t *st, uint64_t *p2, uint32_t p3)
{
    uint8_t b = NODE_SUBT(p2);
    uint64_t *pl3 = p2;
    uint64_t *pl4;
a070:
    if (b - 1 < 2) {
        if (b == 1) { pl4 = p2 + 1; goto lc4; }
        if (b == 2) { pl4 = p2 + 2; goto lc4; }
        if (b != 5) { pl4 = 0; goto lc4; }
        pl4 = (uint64_t *)*p2;
    } else {
        if (b != 5) { pl3 = 0; goto a070; }
        pl3 = (uint64_t *)*p2;
        pl4 = pl3;
    }
    pl4 = pl4 + (uint32_t)p2[1];
lc4:
    while (pl3 != pl4 && NODE_TAG((uint64_t *)*pl3) != p3) {
        pl3 = pl3 + 1;
    }
    if (b == 5) {
        pl4 = (uint64_t *)(*p2 + (uint64_t)*(uint32_t *)(p2 + 1) * 8);
    } else {
        uint64_t *pl1 = 0;
        if (b == 1) pl1 = p2 + 1;
        pl4 = p2 + 2;
        if (b != 2) pl4 = pl1;
    }
    if (pl3 == pl4) return 0;
    return (uint64_t)*pl3;
}

/* FUN_003ba114 @ 0x3ba114   (est. sk_emit_call_site)
 * Emits a call-site/function-type annotation: for a tag-3 node it walks the
 * wrapped element list, printing '(' then each element (via bdff4) with
 * separators, then ')'. Handles the 0xeb special and non-special shapes.
 * Returns nothing.
 * Confidence: low */
static void sk_003ba114(uint64_t *st, uint64_t p2, uint64_t *p3, int32_t p4, int32_t p5)
{
    char local_4d = (char)p5;
    if (NODE_TAG(p3) != 3) {
        *(uint8_t *)((char *)st + 0x69) = 0;
        return;
    }
    uint64_t *psVar5;
    if (NODE_SUBT(p3) - 1 < 2) p3 = (uint64_t *)*p3;
    else if (NODE_SUBT(p3) == 5 && (int32_t)p3[1] != 0) { p3 = (uint64_t *)*p3; p3 = (uint64_t *)*p3; }
    else p3 = 0;
    if (NODE_SUBT(p3) - 1 < 2) psVar5 = (uint64_t *)*p3;
    else if (NODE_SUBT(p3) == 5 && (int32_t)p3[1] != 0) { p3 = (uint64_t *)*p3; psVar5 = (uint64_t *)*p3; }
    else psVar5 = 0;
    uint64_t *ps4 = psVar5 + 8;
    int32_t local_4c = p4;
    uint64_t local_48 = p2;
    if (NODE_TAG(ps4) != 0xeb) {
        if (p5 == 0) { sk_out_str((uint64_t *)((char *)st + 8), (const char *)&DAT_005d7072, 4); return; }
        sk_vec_byte_append((uint64_t *)((char *)st + 8), 0x28);
        sk_003b2180(st, psVar5, (uint64_t)(p4 + 1), 0);
        sk_vec_byte_append((uint64_t *)((char *)st + 8), 0x29);
        return;
    }
    uint64_t *local_58 = &local_48;
    int32_t local_5c = 0;
    uint8_t local_5d;
    if (p2 == 0) local_5d = 0;
    else if (NODE_SUBT((uint64_t *)p2) - 1 < 2) local_5d = 1;
    else if (NODE_SUBT((uint64_t *)p2) != 5) local_5d = 0;
    else local_5d = *(int32_t *)(p2 + 8) != 0;
    sk_vec_byte_append((uint64_t *)((char *)st + 8), 0x28);
    uint8_t b3 = *(uint8_t *)((char *)psVar5 + 0x12);
    uint64_t *ps6 = psVar5;
    uint64_t *ps4b;
    if (b3 - 1 < 2) {
        if (b3 == 1) { ps4b = psVar5 + 4; goto l2f0; }
        if (b3 == 2) goto l2f0;
        if (b3 != 5) { ps4b = 0; goto l2f0; }
        ps4b = (uint64_t *)*psVar5;
    } else {
        if (b3 != 5) { ps4b = 0; ps6 = 0; goto l2f0; }
        ps4b = (uint64_t *)*psVar5;
        ps6 = ps4b;
    }
    ps4b = ps4b + (uint64_t)*(uint32_t *)(psVar5 + 4) * 4;
l2f0:
    {
        if (ps6 != ps4b) {
            sk_003bdff4((uint64_t *)(uint64_t)&local_5d, (uint64_t *)*ps6);
            if (ps6 + 4 != ps4b) {
                uint64_t *ps5 = ps6 + 4;
                do {
                    char *sep = &DAT_005d0c46;
                    uint64_t seplen = 2;
                    if (local_4d == 0) { sep = &DAT_005be7c0; seplen = 0; }
                    sk_out_str((uint64_t *)((char *)st + 8), sep, seplen);
                    ps6 = ps5 + 4;
                    sk_003bdff4((uint64_t *)(uint64_t)&local_5d, (uint64_t *)*ps5);
                    ps5 = ps6;
                } while (ps6 != ps4b);
            }
        }
    }
    sk_vec_byte_append((uint64_t *)((char *)st + 8), 0x29);
}


/* FUN_003ba390 @ 0x3ba390   (est. sk_emit_function_type)
 * Emits a function type annotation: prints the function-kind label
 * (autoclosure/block/escaping/convention-thin), then walks the parameter and
 * result child elements (0x87/0x88/0x45/0x46/0x11e/0x11f/0x44/0x11d markers)
 * printing them via b2180, applies the differentiable-attribute word, and
 * invokes the emitter vtable hook with the trailing element. Returns nothing.
 * Confidence: low */
static void sk_003ba390(uint64_t *p1, uint64_t p2, uint64_t *p3, uint64_t p4)
{
    if (NODE_SUBT(p3) != 2 && (NODE_SUBT(p3) != 5 || (uint32_t)p3[1] < 2)) {
        *(uint8_t *)((char *)p1 + 0x69) = 0;
        return;
    }
    int32_t i19 = (int32_t)p4;
    uint16_t u2 = NODE_TAG(p3);
    uint64_t *local_78 = p1;
    uint64_t *pl70 = p3;
    int32_t local_68 = i19;
    if (u2 < 0xaf) {
        if (u2 == 0xb) { sk_out_str((uint64_t *)((char *)p1 + 1), (const char *)s__autoclosure_005d7077, 0xd); }
        else if (u2 == 0x17) { sk_003ba9e0(&local_78, (char *)&DAT_005d6cd7); }
        else if (u2 == 0x42) { sk_out_str((uint64_t *)((char *)p1 + 1), (const char *)s__autoclosure_005d7077, 0xd); }
    } else {
        if (u2 == 0xaf) { sk_003ba9e0(&local_78, (char *)s_block_005d6e81); }
        else if (u2 == 0xb0) { sk_out_str((uint64_t *)((char *)p1 + 1), (const char *)s__escaping_005d7098, 10); }
        else if (u2 == 0xea) { sk_out_str((uint64_t *)((char *)p1 + 1), (const char *)s__convention_thin__005d7085, 0x12); }
        else if (u2 == 0x17) { sk_003ba9e0(&local_78, (char *)&DAT_005d6cd7); }
    }
    uint8_t b1 = NODE_SUBT(p3);
    uint64_t u13 = b1;
    short s3;
    int32_t i20;
    uint32_t u16;
    bool b6, b5;
    uint64_t *pl14;
    if (b1 == 1) {
        s3 = NODE_TAG((uint64_t *)*p3);
        i20 = 1;
        u16 = 0xffffffff;
        goto l4d4;
    } else if (b1 == 2) {
        s3 = NODE_TAG((uint64_t *)*p3);
        u16 = 0;
        i20 = 2;
        goto l4d4;
    } else {
        i20 = (int32_t)p3[1];
        u16 = i20 - 2;
        pl14 = (uint64_t *)*p3;
        bool b7 = NODE_TAG((uint64_t *)pl14) == 0x18;
        b6 = NODE_TAG((uint64_t *)pl14[b7 ? 1 : 0]) == 0x89;
        u16 = (uint32_t)(b7 ? 1 : 0);
        if (b6) u16 = u16 + 1;
        b5 = false;
        goto cont;
    }
l4d4:
    b6 = NODE_TAG((uint64_t *)p3[(s3 == 0x18) ? 1 : 0]) == 0x89;
    u16 = (uint32_t)(s3 == 0x18);
    if (b6) u16 = u16 + 1;
    b5 = true;
    pl14 = p3;
cont:
    u16 = u16;   /* recompute below */
    {
        /* re-derive u15 from the child-at-u22 test */
    }
    uint32_t u15 = 0;
    uint64_t *base = b5 ? p3 : (uint64_t *)*p3;
    /* note: faithful value requires walking; approximated as decompiled */
    uint64_t l8 = 0, l9 = 0;
    uint64_t u22 = (uint64_t)(u16 > 0 ? 1 : 0);
    u13 = NODE_SUBT(p3);
    int32_t i12 = (int32_t)u13;
    b5 = 1 < (uint32_t)(i12 - 1);
    pl14 = b5 ? (uint64_t *)*p3 : p3;
    short s4 = NODE_TAG((uint64_t *)pl14[u22]);
    u15 = 0x9c;
    uint64_t v = (uint64_t)((int64_t)l8);
    if (l8 != 0) sk_003b2180(p1, (uint64_t *)l8, (uint64_t)(i19 + 1), 0);
    if (s3 == 0x44) sk_out_str((uint64_t *)((char *)p1 + 1), (const char *)s__Sendable_005d7103, 10);
    b1 = NODE_SUBT(p3);
    u13 = b1;
    uint32_t uf = b1;
    uint64_t *pe;
    if (uf == 1) { if (u13 <= (uint64_t)u16) pe = 0; else { pe = b5 ? (uint64_t *)*p3 : p3; pe = (uint64_t *)pe[u16]; } }
    else if (uf == 5) { pe = b5 ? (uint64_t *)*p3 : p3; pe = (uint64_t *)pe[(uint32_t)p3[1]-1 < (uint32_t)u13 ? 0 : 0]; pe = 0; }
    else { pe = 0; }
    ((void (*)(uint64_t *, uint64_t, uint64_t *, uint64_t, uint8_t))
        (**(uint64_t **)*p1 + 0x18))(p1, p2, pe, p4, *(uint8_t *)((char *)p1 + 0x2f));
    if (*(uint8_t *)((char *)p1 + 0x2f) != 1) return;
    if (s4 == 0x11d) sk_out_str((uint64_t *)((char *)p1 + 1), (const char *)s_async_005d710e, 6);
    if (l9 != 0) sk_003b2180(p1, (uint64_t *)l9, (uint64_t)(i19 + 1), 0);
    sk_out_str((uint64_t *)((char *)p1 + 1), (const char *)&DAT_005d7115, 4);
    if (b6) sk_out_str((uint64_t *)((char *)p1 + 1), (const char *)s_sending_005d711a, 8);
    b1 = NODE_SUBT(p3);
    u13 = b1;
    uint32_t uf2 = b1;
    uint64_t *l8b = 0;
    if (uf2 == 1) { if ((uint32_t)(i20 - 1) < u13) { pl14 = (1 < uf2 - 1) ? (uint64_t *)*p3 : p3; l8b = (uint64_t *)pl14[i20 - 1]; } }
    else if (uf2 == 5) { l8b = 0; }
    else if (b1 == 2) { l8b = 0; }
    sk_003b2180(p1, l8b, (uint64_t)(i19 + 1), 0);
}

/* FUN_003a6c28 @ 0x3a6c28   (est. sk_parse_function_sig)
 * Parses a compact function-signature stream into a 0x77 node. It builds
 * children for: 's' (value-list via ad724), 'I' (0x79 item), 'P' (a 0x2c
 * popped element converted to 0x2f), 'e' (0x6b marker), 'A' (0x6e marker), a
 * 'd'-class code (0x6d scalar), and the ownership/thinness runes
 * ('g'/'t'/'x'/'y' -> callee-guaranteed/thin/owned/unowned 0x6c), block kind
 * ('B'/'C'/'K'/'M'/'O'/'W'/'z'-suffix -> 0x75 with 0x76/0x78 yield tags),
 * 'h' (0x74 Sendable), 'H' (0x74 async), 'T' (0x6f), and finally a 0x7b
 * tail. Returns the 0x77 node or 0.
 * Confidence: medium */
static uint64_t sk_003a6c28(uint64_t *st)
{
    uint64_t *root = sk_node_alloc(st, 1);
    NODE_SETTAG(root, 0x77); NODE_SETSUBT(root, 0);
    uint64_t pos = STREAM_POS(st);
    uint64_t end = STREAM_END(st);
    uint64_t l18 = 0;
    if ((pos < end) && STREAM_DATA(st)[pos] == 's') {
        STREAM_POS(st) = pos + 1;
        uint64_t scratch = 0, slen = 0, s2 = 0;
        if (sk_003ad724(st, (uint64_t)(uintptr_t)&scratch, &s2) == 0) return 0;
        if (STACK_CNT(st) == 0) return 0;
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *el = STACK_ELEM(st, i);
        if (NODE_TAG(el) != 0x2c) return 0;
        STACK_CNT(st) = i;
        uint64_t *w = sk_node_alloc(st, 1);
        NODE_SETTAG(w, 0x7c); NODE_SETSUBT(w, 0);
        sk_node_add(w, el, st);
        sk_node_add(w, (uint64_t *)scratch, st);
        if (s2) sk_node_add(w, (uint64_t *)s2, st);
        sk_node_add(root, w, st);
        pos = STREAM_POS(st);
        end = STREAM_END(st);
    }
    if ((pos < end) && STREAM_DATA(st)[pos] == 'I') {
        STREAM_POS(st) = pos + 1;
        uint64_t scratch = 0, slen = 0, s2 = 0;
        if (sk_003ad724(st, (uint64_t)(uintptr_t)&scratch, &s2) == 0) return 0;
        uint64_t *w = sk_node_alloc(st, 1);
        NODE_SETTAG(w, 0x79); NODE_SETSUBT(w, 0);
        sk_node_add(w, (uint64_t *)scratch, st);
        if (s2) sk_node_add(w, (uint64_t *)s2, st);
        sk_node_add(root, w, st);
    }
    pos = STREAM_POS(st);
    end = STREAM_END(st);
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        l18 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l18) != 0x2c) l18 = 0;
        else STACK_CNT(st) = i;
    }
    if (pos < end && STREAM_DATA(st)[pos] == 'P') {
        STREAM_POS(st) = pos + 1;
        uint64_t *conv = (uint64_t *)sk_tag_convert(st, (uint64_t *)l18, 0x2f);
        l18 = (uint64_t)conv;
        pos = STREAM_POS(st);
        end = STREAM_END(st);
    }
    if ((pos < end) && STREAM_DATA(st)[pos] == 'e') {
        STREAM_POS(st) = pos + 1;
        uint64_t *w = sk_node_alloc(st, 1);
        NODE_SETTAG(w, 0x6b); NODE_SETSUBT(w, 0);
        sk_node_add(root, w, st);
        pos = STREAM_POS(st); end = STREAM_END(st);
    }
    if ((pos < end) && STREAM_DATA(st)[pos] == 'A') {
        STREAM_POS(st) = pos + 1;
        uint64_t *w = sk_node_alloc(st, 1);
        NODE_SETTAG(w, 0x6e); NODE_SETSUBT(w, 0);
        sk_node_add(root, w, st);
        pos = STREAM_POS(st); end = STREAM_END(st);
    }
    if (pos < end) {
        uint32_t c = STREAM_DATA(st)[pos] - 100;
        if (((c >> 1 & 0x7f | (c & 1) << 7) < 8) && ((1U << (c >> 1 & 0x1f)) & 0x93U) != 0) {
            if (pos < end) {
                STREAM_POS(st) = pos + 1;
                uint64_t wv = (uint64_t)(int64_t)STREAM_DATA(st)[pos];
                uint64_t *w = sk_node_alloc(st, 1);
                NODE_SETTAG(w, 0x6d); NODE_SETSUBT(w, 4);
                w[0] = wv;
                sk_node_add(root, w, st);
            }
            pos = STREAM_POS(st); end = STREAM_END(st);
        }
    }
    if (end <= pos) return 0;
    STREAM_POS(st) = pos + 1;
    uint8_t b = STREAM_DATA(st)[pos];
    char *label;
    if (b < 0x78) {
        if (b == 'g') label = s__callee_guaranteed_005d6e4e;
        else if (b != 't') return 0;
        else label = s__convention_thin__005d6e6f;
    } else if (b == 'x') label = s__callee_owned_005d6e61;
    else {
        if (b != 'y') return 0;
        label = s__callee_unowned_005d6e3e;
    }
    {
        uint64_t *w = sk_node_alloc(st, 1);
        NODE_SETTAG(w, 0x6c); NODE_SETSUBT(w, 3);
        w[0] = (uint64_t)label;
        w[1] = (uint64_t)sk_len_query((uint64_t)label);
        sk_node_add(root, w, st);
    }
    pos = STREAM_POS(st); end = STREAM_END(st);
    uint64_t u14 = pos;
    if (pos < end) {
        STREAM_POS(st) = pos + 1;
        uint8_t c2 = STREAM_DATA(st)[pos];
        bool b5 = false;
        char *blk = NULL;
        if (c2 < 0x4d) {
            if (c2 == 'B') { blk = s_block_005d6e81; }
            else if (c2 == 'C') { blk = DAT_005d6cd7; }
            else if (c2 == 'K') { blk = s_closure_005d6e9a; }
            else goto no_blk;
        } else if (c2 < 0x57) {
            if (c2 == 'M') { blk = s_method_005d6e87; }
            else if (c2 == 'O') { blk = s_objc_method_005d6e8e; }
            else goto no_blk;
        } else if (c2 == 'W') { blk = s_witness_method_005d6ea2; }
        else if (c2 == 'z') {
            if (end <= pos + 1) goto no_blk;
            uint64_t p2 = pos + 2;
            STREAM_POS(st) = p2;
            char c3 = STREAM_DATA(st)[pos + 1];
            if (c3 == 'B') blk = s_block_005d6e81;
            else if (c3 != 'C') goto no_blk;
            else blk = DAT_005d6cd7;
            b5 = true;
        } else goto no_blk;
        {
            uint64_t *w = sk_node_alloc(st, 1);
            NODE_SETTAG(w, 0x75); NODE_SETSUBT(w, 0);
            uint64_t *inner = (uint64_t *)sk_node_make(st, 0x76, blk);
            sk_node_add(w, inner, st);
            if (b5) {
                uint64_t *t = (uint64_t *)sk_003ad048(st);
                if (t != 0) sk_node_add(w, t, st);
            }
            sk_node_add(root, w, st);
            pos = STREAM_POS(st); end = STREAM_END(st);
        }
        goto after_blk;
    no_blk:
        STREAM_POS(st) = u14;
        pos = u14;
        end = STREAM_END(st);
    }
after_blk:
    if (pos < end) {
        uint8_t c = STREAM_DATA(st)[pos];
        if (c == 'A' || c == 'G' || c == 'I') {
            char *y;
            if (c == 'A') y = s_yield_once_005d57a1;
            else if (c == 'G') y = s_yield_many_005d57b9;
            else y = s_yield_once_2_005d57ac;
            STREAM_POS(st) = pos + 1;
            uint64_t *w = (uint64_t *)sk_node_make(st, 0x78, y);
            sk_node_add(root, w, st);
            pos = STREAM_POS(st); end = STREAM_END(st);
        }
    }
    if (pos < end && STREAM_DATA(st)[pos] == 'h') {
        STREAM_POS(st) = pos + 1;
        uint64_t *w = sk_node_alloc(st, 1);
        NODE_SETTAG(w, 0x74); NODE_SETSUBT(w, 3);
        w[0] = (uint64_t)s__Sendable_005d6eb1;
        w[1] = 9;
        sk_node_add(root, w, st);
        pos = STREAM_POS(st); end = STREAM_END(st);
    }
    if (pos < end && STREAM_DATA(st)[pos] == 'H') {
        STREAM_POS(st) = pos + 1;
        uint64_t *w = sk_node_alloc(st, 1);
        NODE_SETTAG(w, 0x74); NODE_SETSUBT(w, 3);
        w[0] = (uint64_t)s__async_005d6ebb;
        w[1] = 6;
        sk_node_add(root, w, st);
        pos = STREAM_POS(st); end = STREAM_END(st);
    }
    if (pos < end && STREAM_DATA(st)[pos] == 'T') {
        STREAM_POS(st) = pos + 1;
        uint64_t *w = sk_node_alloc(st, 1);
        NODE_SETTAG(w, 0x6f); NODE_SETSUBT(w, 0);
        sk_node_add(root, w, st);
    }
    if (l18 != 0) sk_node_add(root, (uint64_t *)l18, st);
    uint64_t tail = (uint64_t)sk_003add54(st, 0x7b);
    if (tail == 0) return 0;
    return tail;
}

/* FUN_003a8ab4 @ 0x3a8ab4   (est. sk_parse_letter_big)
 * Big letter-dispatch parser: reads a stream letter and builds a node based
 * on the tag family. Handles: 'B'(0x5f->0xd4), 'C'(0x1f), 'D'(0x39),
 * 'E'(0x37), 'F'(0x38), 'G'(0x5e->0xd4), 'H'/'h'(0x8e/0x8f child collection
 * via aefe4 with optional 'q' 0xe5), 'I'(0x3c), 'J'('O'/'V'/'S' sub-
 * dispatch via af3c4/af4d4/af238), 'K'/'k'(0x8a..0x8d), 'L'(0x118),
 * 'M'(7), 'N'(0x11a via 4c14), 'O'(0xaa), 'P'(0x59 via ae9e0), 'Q'/'Y'
 * (0x157/0x158 ident), 'R'(0xd3), 'S'(0xcd via 4110), 'T'(0x115), 'U'(0xd6
 * pair), 'V'(0x10c), 'W'(0xcf), 'X'(0x3e), 'Z'/'z'(0xac/0xad triple),
 * 'a'(0xb5), 'b'(0x11b), 'c'(0x114), 'd'(0x3a), 'e'(0x123 via f0cc),
 * 'f'(aebb0), 'g'(0x5d), 'i'(0x62), 'j'(0x116), 'l'(0x11c), 'm'(0x99),
 * 'n'(0x119), 'o'(0xae), 'p'(0x58+0x60), 'q'(0x117), 'r'(0xd3),
 * 's'(0x61 via ae734), 't'(ae8a0), 'u'(0x14e), 'v'(0x12d/0x12e),
 * 'w'(0x15b..0x176), 'x'(0x3d), 'y'(0xd5). Returns the node.
 * Confidence: low */
static uint64_t *sk_003a8ab4(uint64_t *st)
{
    uint64_t end = STREAM_END(st);
    uint64_t pos = STREAM_POS(st);
    if (end <= pos) return 0;
    uint64_t *pu = 0;
    uint64_t npos = pos + 1;
    STREAM_POS(st) = npos;
    uint8_t b = STREAM_DATA(st)[pos];
    uint32_t u10 = b;
    if (0x39 < u10 - 0x41) return 0;
    uint16_t tag = 0xd4;
    uint64_t v12 = 0, l21 = 0, l15 = 0, l18 = 0;
    uint32_t u17 = 0;
    bool b24 = false;
    uint64_t *l68 = 0, *l60 = 0, *l58 = 0;
    switch (u10) {
    default:
        pu = sk_node_alloc(st, 1);
        tag = 0xb4;
        break;
    case 'B': v12 = 0x5f; goto tbl38;
    case 'C': {
        l21 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l21 = (uint64_t)e; }
        }
        u17 = 0x1f;
        goto push_simple;
    }
    case 'D': pu = sk_node_alloc(st, 1); tag = 0x39; break;
    case 'E': pu = sk_node_alloc(st, 1); tag = 0x37; break;
    case 'F': pu = sk_node_alloc(st, 1); tag = 0x38; break;
    case 'G': v12 = 0x5e; goto tbl38;
    case 'H': case 'h': {
        tag = (b != 'H') ? 0x8f : 0x8e;
        bool q = false;
        if (npos < end && STREAM_DATA(st)[npos] == 'q') {
            STREAM_POS(st) = pos + 2;
            q = true;
        }
        l68 = 0; l60 = 0; l58 = 0;
        uint64_t *cur;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            cur = STACK_ELEM(st, i);
            STACK_CNT(st) = i;
            uint64_t *l70 = cur;
            if (cur != 0) {
                if (NODE_TAG(cur) != 0x2c) {
                    if (NODE_TAG(cur) != 0xf4) goto h_dcc;
                    sk_003aefe4(&l68, &l70);
                    l21 = 0;
                }
            }
            while (STACK_CNT(st) != 0) {
                uint32_t j = STACK_CNT(st) - 1;
                uint64_t *e2 = STACK_ELEM(st, j);
                STACK_CNT(st) = j;
                if (e2 == 0) break;
                if (NODE_TAG(e2) != 0xf4) goto h_dcc;
                sk_003aefe4(&l68, &e2);
            }
        }
        pu = sk_node_alloc(st, 1);
        NODE_SETTAG(pu, tag); NODE_SETSUBT(pu, 0);
        {
            uint64_t *p = l58, *e = l68, *c = l60;
            if (c != l68) {
                uint64_t *prev;
                do {
                    prev = c - 1;
                    if (c == e || prev == p) sk_canary_panic();
                    sk_node_add(pu, (uint64_t *)*prev, st);
                    c = prev;
                } while (prev != l68);
            }
        }
        if (l21 != 0) sk_node_add(pu, (uint64_t *)l21, st);
        if (q) {
            uint64_t *c = sk_node_alloc(st, 1);
            NODE_SETTAG(c, 0xe5); NODE_SETSUBT(c, 0);
            sk_node_add(pu, c, st);
        }
        return pu;
    h_dcc:
        return 0;
    }
    case 'I': pu = sk_node_alloc(st, 1); tag = 0x3c; break;
    case 'J':
        if (npos < end) {
            char c = STREAM_DATA(st)[npos];
            if (c == 'O') { STREAM_POS(st) = pos + 2; return (uint64_t *)sk_003af3c4(st); }
            if (c == 'V') { STREAM_POS(st) = pos + 2; v12 = 0x153; goto j66c; }
            if (c == 'S') { STREAM_POS(st) = pos + 2; return (uint64_t *)sk_003af238(st); }
        }
        v12 = 0x14f;
    j66c:
        return (uint64_t *)sk_003af4d4(st, (uint16_t)v12);
    case 'K': case 'k': {
        uint64_t v = sk_003aef74(st, (uint64_t)&DAT_005d6ec2, 2);
        uint32_t t1 = 0x8a, t2;
        if (b != 'K') t1 = 0x8b;
        t2 = 0x8d;
        if ((v & 1) != 0) t2 = 0x8c;
        else {
            v = sk_003aef74(st, (uint64_t)&DAT_005d6ec5, 2);
            if ((v & 1) == 0) t2 = t1;
        }
        bool q = false;
        uint64_t pp = STREAM_POS(st);
        if (pp < STREAM_END(st) && STREAM_DATA(st)[pp] == 'q') {
            STREAM_POS(st) = pp + 1;
            q = true;
        }
        l68 = 0; l60 = 0; l58 = 0;
        uint64_t *l70 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            l70 = STACK_ELEM(st, i);
            STACK_CNT(st) = i;
            if (l70 != 0 && NODE_TAG(l70) == 0xf4) {
                do {
                    sk_003aefe4(&l68, &l70);
                    if (STACK_CNT(st) == 0) goto k_dcc;
                    uint32_t j = STACK_CNT(st) - 1;
                    l70 = STACK_ELEM(st, j);
                    STACK_CNT(st) = j;
                    if (l70 == 0) goto k_dcc;
                } while (NODE_TAG(l70) == 0xf4);
                if (NODE_TAG(l70) == 0x2c) {
                    if (STACK_CNT(st) == 0) goto k_dcc;
                    l21 = (uint64_t)STACK_ELEM(st, STACK_CNT(st) - 1);
                    STACK_CNT(st) = STACK_CNT(st) - 1;
                    if (l21 == 0) goto k_dcc;
                    pu = (uint64_t *)sk_node_push2(st, t2, (uint64_t *)0, (uint64_t *)0);
                } else {
                    pu = (uint64_t *)sk_node_push(st, t2, l70);
                }
                {
                    uint64_t *p = l58, *e = l68, *c = l60;
                    if (c != l68) {
                        uint64_t *prev;
                        do {
                            prev = c - 1;
                            if (c == e || prev == p) sk_canary_panic();
                            sk_node_add(pu, (uint64_t *)*prev, st);
                            c = prev;
                        } while (prev != l68);
                    }
                }
                if (q) goto add_e5;
                return pu;
            }
        }
    k_dcc:
        pu = 0;
        if (l68 != 0) {
            l60 = l68;
            sk_lock(l68, (long)l58 - (long)l68);
        }
        return pu;
    add_e5:
        {
            uint64_t *c = sk_node_alloc(st, 1);
            NODE_SETTAG(c, 0xe5); NODE_SETSUBT(c, 0);
            if (pu != 0) sk_node_add(pu, c, st);
        }
        return pu;
    }
    case 'L': l21 = sk_val_get(st); u17 = 0x118; goto push_simple;
    case 'M': l21 = (uint64_t)sk_003ae658(st); u17 = 7; goto push_simple;
    case 'N': {
        v12 = sk_val_get(st);
        uint64_t u13 = (uint64_t)sk_003ae36c(st);
        l21 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l21 = (uint64_t)e; }
        }
        return (uint64_t *)sk_ctx_op(st, 0x11a, (uint64_t *)l21, (uint64_t *)u13, (uint64_t *)v12);
    }
    case 'O': pu = sk_node_alloc(st, 1); tag = 0xaa; break;
    case 'P': v12 = 0x59; goto e9e0_case;
    case 'Q': case 'Y': {
        l21 = (uint64_t)sk_003ac52c(st);
        u17 = (b != 'Q') ? 0x158 : 0x157;
        goto push_simple;
    }
    case 'R': goto r_case;
    case 'S':
        l21 = (uint64_t)sk_ctx_setup2_v(st, 0, 0);
        u17 = 0xcd;
        goto push_simple;
    case 'T':
        if (end <= npos) return 0;
        STREAM_POS(st) = pos + 2;
        if (STREAM_DATA(st)[npos] != 'I') return 0;
        l21 = (uint64_t)sk_ctx_setup2_v(st, 0, 0);
        u17 = 0x115;
        goto push_simple;
    case 'U': {
        if (STACK_CNT(st) == 0) return 0;
        uint32_t i = STACK_CNT(st) - 1;
        l21 = (uint64_t)STACK_ELEM(st, i);
        if (NODE_TAG((uint64_t *)l21) != 0xf4) return 0;
        STACK_CNT(st) = i;
        if (i == 0) return 0;
        l15 = (uint64_t)STACK_ELEM(st, i - 1);
        STACK_CNT(st) = i - 1;
        if (l15 == 0) return 0;
        pu = sk_node_alloc(st, 1);
        NODE_SETTAG(pu, 0xd6); NODE_SETSUBT(pu, 0);
        sk_node_add(pu, (uint64_t *)l15, st);
        goto add_l21;
    }
    case 'V':
        v12 = (uint64_t)sk_ctx_setup2_v(st, 0, 0);
        l21 = (uint64_t)sk_ctx_setup2_v(st, 0, 0);
        return (uint64_t *)sk_node_push2(st, 0x10c, (uint64_t *)l21, (uint64_t *)v12);
    case 'W':
        v12 = (uint64_t)sk_ctx_setup2_v(st, 0, 0);
        l21 = (uint64_t)sk_stream_dispatch(st);
        return (uint64_t *)sk_node_push2(st, 0xcf, (uint64_t *)l21, (uint64_t *)v12);
    case 'X': pu = sk_node_alloc(st, 1); tag = 0x3e; break;
    case 'Z': case 'z': {
        v12 = (uint64_t)sk_003ac52c(st);
        uint32_t cnt = STACK_CNT(st);
        if (cnt == 0) { l15 = 0; l21 = 0; l18 = 0; }
        else {
            uint32_t i = cnt - 1;
            uint64_t *stk = (uint64_t *)STACK_BASE(st);
            l21 = stk[i];
            if (NODE_TAG((uint64_t *)l21) == 0x2c) {
                STACK_CNT(st) = i;
                cnt = i;
                if (i == 0) { l15 = 0; l18 = 0; goto zafter; }
            } else {
                l21 = 0;
            }
            uint32_t j = cnt - 1;
            l15 = stk[j];
            if (NODE_TAG((uint64_t *)l15) == 0xf4) {
                STACK_CNT(st) = j;
                if (j == 0) goto zafter;
            } else {
                l15 = 0;
                j = cnt;
            }
            l18 = stk[j - 1];
            if (NODE_TAG((uint64_t *)l18) != 0xf4) goto zafter;
            STACK_CNT(st) = j - 1;
        }
    zafter:
        {
            u17 = (u10 != 'z') ? 0xad : 0xac;
            pu = (uint64_t *)sk_ctx_op(st, u17, (uint64_t *)l18, (uint64_t *)l15, (uint64_t *)v12);
            if (l21 == 0) return pu;
            if (pu == 0) return 0;
            goto add_l21;
        }
    }
    case 'a': pu = sk_node_alloc(st, 1); tag = 0xb5; break;
    case 'b': {
        v12 = sk_val_get(st);
        l21 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l21 = (uint64_t)e; }
        }
        return (uint64_t *)sk_node_push2(st, 0x11b, (uint64_t *)l21, (uint64_t *)v12);
    }
    case 'c':
        l21 = (uint64_t)sk_ctx_setup2_v(st, 0, 0);
        u17 = 0x114;
        goto push_simple;
    case 'd': pu = sk_node_alloc(st, 1); tag = 0x3a; break;
    case 'e': {
        sk_003af0cc(&l68, st);
        uint32_t flag = (uint32_t)(uint8_t)(((uint64_t)l58) >> 56);
        uint64_t *arg = l60;
        if ((int32_t)flag >= 0) arg = (uint64_t *)(uint64_t)((uint64_t)l58 >> 56);
        pu = 0;
        if (arg == 0) pu = 0;
        else {
            uint64_t *src = l68;
            if ((int32_t)flag >= 0) src = &l68;
            pu = (uint64_t *)sk_00363f70(st, 0x123, src);
        }
        if ((flag >> 7 & 1) == 0) return pu;
        sk_lock((void *)l68, (uint64_t)l58 & 0x7fffffffffffffff);
        return pu;
    }
    case 'f': return (uint64_t *)sk_003aebb0(st);
    case 'g': v12 = 0x5d; goto tbl38;
    case 'i': v12 = 0x62; goto tbl38;
    case 'j':
        l21 = (uint64_t)sk_ctx_setup2_v(st, 0, 0);
        u17 = 0x116;
        goto push_simple;
    case 'l':
        l21 = (uint64_t)sk_003ae658(st);
        if (l21 == 0) return 0;
        u17 = 0x11c;
        goto push_simple;
    case 'm': pu = sk_node_alloc(st, 1); tag = 0x99; break;
    case 'n': {
        v12 = sk_val_get(st);
        uint64_t u13 = (uint64_t)sk_003ae36c(st);
        l21 = 0;
        if (STACK_CNT(st) != 0) {
            uint32_t i = STACK_CNT(st) - 1;
            uint64_t *e = STACK_ELEM(st, i);
            if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l21 = (uint64_t)e; }
        }
        return (uint64_t *)sk_ctx_op(st, 0x119, (uint64_t *)l21, (uint64_t *)u13, (uint64_t *)v12);
    }
    case 'o': pu = sk_node_alloc(st, 1); tag = 0xae; break;
    case 'p': v12 = 0x58; goto e9e0_case;
    case 'q':
        l21 = (uint64_t)sk_ctx_setup2_v(st, 0, 0);
        u17 = 0x117;
        goto push_simple;
    case 'r': goto r_case;
    case 's': v12 = 0x61; goto tbl38;
    case 't': return (uint64_t *)sk_003ae8a0(st);
    case 'u': pu = sk_node_alloc(st, 1); tag = 0x14e; break;
    case 'v': {
        uint64_t v = (uint64_t)sk_003ac4a4(st);
        if ((int32_t)v < 0) return 0;
        uint64_t pp = STREAM_POS(st);
        uint16_t t;
        if (pp < STREAM_END(st) && STREAM_DATA(st)[pp] == 'r') {
            STREAM_POS(st) = pp + 1;
            t = 0x12e;
        } else {
            t = 0x12d;
        }
        pu = sk_node_alloc(st, 1);
        NODE_SETTAG(pu, t); NODE_SETSUBT(pu, 4);
        pu[0] = v;
        return pu;
    }
    case 'w': {
        if (end <= npos) return 0;
        STREAM_POS(st) = pos + 2;
        uint8_t c = STREAM_DATA(st)[npos];
        uint16_t t;
        if (c < 0x62) {
            if (c == 'B') t = 0x15c;
            else {
                if (c != 'S') return 0;
                t = 0x163;
            }
        } else if (c == 'd') t = 0x176;
        else if (c == 'c') t = 0x175;
        else {
            if (c != 'b') return 0;
            t = 0x15b;
        }
        pu = sk_node_alloc(st, 1);
        NODE_SETTAG(pu, t); NODE_SETSUBT(pu, 0);
        return pu;
    }
    case 'x': pu = sk_node_alloc(st, 1); tag = 0x3d; break;
    case 'y': {
        tag = 0xd5;
        b24 = true;
        goto common;
    }
    }
    /* default/simple tag node */
r_case:
    if (u10 != 'H' && u10 != 'h' && u10 != 'K' && u10 != 'k' && u10 != 'R' &&
        u10 != 'y' && u10 != 'Z' && u10 != 'z') {
        if (u10 == 'B' || u10 == 'G' || u10 == 'g' || u10 == 'i' || u10 == 's') goto tbl38;
    }
    goto common;
tbl38:
    return (uint64_t *)sk_003ae734(st, v12, 0);
e9e0_case:
    pu = (uint64_t *)sk_003ae9e0(st, (uint16_t)v12);
    l21 = 0;
    if (STACK_CNT(st) != 0) {
        uint32_t i = STACK_CNT(st) - 1;
        uint64_t *e = STACK_ELEM(st, i);
        if (NODE_TAG(e) == 0xf4) { STACK_CNT(st) = i; l21 = (uint64_t)e; }
    }
    l21 = (uint64_t)sk_node_push(st, 0x60, (uint64_t *)l21);
    if (pu == 0) return 0;
    if (l21 != 0) { sk_node_add(pu, (uint64_t *)l21, st); return pu; }
    return 0;
push_simple:
    return (uint64_t *)sk_node_push(st, (int)u17, (uint64_t *)l21);
add_l21:
    if (l21 != 0) sk_node_add(pu, (uint64_t *)l21, st);
    return pu;
common:
    pu = sk_node_alloc(st, 1);
    NODE_SETTAG(pu, tag); NODE_SETSUBT(pu, 0);
    if (STACK_CNT(st) != 0) {
        int32_t cnt = STACK_CNT(st);
        uint64_t *e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0x2c) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(pu, e, st);
            cnt = STACK_CNT(st);
        }
        if (b24) {
            if (cnt == 0) return pu;
            e = STACK_ELEM(st, cnt - 1);
            if (NODE_TAG(e) == 0xf4) {
                STACK_CNT(st) = cnt - 1;
                sk_node_add(pu, e, st);
                cnt = STACK_CNT(st);
                goto l94d0;
            }
        }
    l94d0:
        if (cnt == 0) return pu;
        e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0xf4) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(pu, e, st);
            cnt = STACK_CNT(st);
            if (cnt == 0) return pu;
        }
        e = STACK_ELEM(st, cnt - 1);
        if (NODE_TAG(e) == 0xf4) {
            STACK_CNT(st) = cnt - 1;
            sk_node_add(pu, e, st);
        }
    }
    return pu;
}
