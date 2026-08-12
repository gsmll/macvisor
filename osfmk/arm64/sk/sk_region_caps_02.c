/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string-matched.
 *
 * Slice 02: 0x85890-0x8d1c4 — the InternalExclaveLauncher component-graph
 * (DER) resource/cap allocator and the cL4 syscall/entry wrappers that drive
 * it. The low part (0x85890-0x87180) is the seL4-style syscall entry + vtable
 * dispatch machinery; the high part (0x87700-0x8d1c4) parses component-graph
 * resource type strings ("type", "Resource", "All") and allocates the
 * corresponding capability tree, ending in a set of seL4 CNode/CTE slot
 * lookup + copy helpers. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ *
 * Shared base types.
 * ------------------------------------------------------------------ */
typedef uint64_t word_t;
typedef uint64_t cptr_t;      /* capability pointer (badge | CNode slot) */
typedef uint64_t cap_t;       /* capability word */
typedef uint64_t cl4_result_pair_t __attribute__((__aligned__(16)));

typedef struct cl4_ret16 {
    uint64_t lo;
    uint64_t hi;
} cl4_ret16_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers (declared extern with one-line notes; bodies
 * live in the range worker that owns them). Ground truth = Ghidra names.
 * ------------------------------------------------------------------ */

/* ---- generic kernel support ---- */
extern int            FUN_0006e6dc(void);                 /* current-state/context check (nonzero = have thread) */
extern cl4_ret16_t    FUN_0006b2ec(void);                  /* fetch {x0,x8} working pair (kernel reg snapshot) */
extern void           FUN_0006e7c0(const void *src, void *dst); /* memcpy 0x28-byte node entry */
extern void           FUN_0006a4c0(const void *obj, word_t a);   /* object deref / keepalive */
extern void           FUN_000651bc(word_t a, ...);         /* syscall epilogue: return or fall into 0x11d7e8 panic */
extern void           FUN_0011d7e8(word_t a, ...) __attribute__((noreturn)); /* kernel panic tail */

/* ---- locks / critical sections ---- */
extern void           FUN_0036993c(void *a, void *b, word_t c, word_t d); /* lock global result (0x65fa88,0x65f980) */
extern void           FUN_0036986c(void);                  /* unlock global result */
extern void           FUN_0036a9d4(void *a, void *b);      /* lock (0x64f1f8,0x64e1c0) */
extern void           FUN_0036a1a0(void *a, ...);          /* enter section (arg block, count, flags) */
extern void           FUN_0036a20c(void *a, ...);          /* leave section */
extern void           FUN_0036b6ac(word_t a, ...);                  /* teardown / finalize context */
extern void           FUN_000026e8(const void *obj);       /* unlock / leave critical region */
extern void           FUN_00002688(void);                  /* lock */
extern void           FUN_00002804(void *obj);             /* unlock */
extern void           FUN_00002834(void);                  /* lock */
extern void           FUN_00077770(void *lock);            /* acquire lock at address */
extern void           FUN_00077724(void *lock);            /* acquire lock at address (variant) */

/* ---- refcount / allocation ---- */
extern void           FUN_0036b118(void *obj);             /* release ref */
extern void          *thunk_FUN_0036b270(void *obj);       /* retain ref (returns obj) */
extern void           FUN_003a25d4(void *obj);             /* release ref */
extern word_t         FUN_003a261c(void *obj);             /* release ref */
extern word_t         FUN_0036a940(word_t descr, size_t size, unsigned tag); /* alloc object of size w/ tag */
extern word_t         FUN_0036a9a0(word_t descr, word_t stack); /* alloc+ctor object */
extern void           FUN_0036b588(void *obj);             /* publish / retain obj */
extern word_t         FUN_00002534(word_t name, word_t meta);/* object type/class descriptor */
extern word_t         FUN_00121598(void);                  /* current-node handle fetch */
extern word_t         FUN_00121468(void);
extern word_t         FUN_001214c4(void);
extern word_t         FUN_00121510(void);
extern word_t         FUN_00121540(void);
extern word_t         FUN_001215e0(void);
extern word_t         FUN_00121610(void);
extern word_t         FUN_00121640(void);
extern word_t         FUN_00121498(void);
extern word_t         FUN_00121588(void);
extern word_t         FUN_003a261c__dup(void);

/* ---- DER component-graph node list helpers ---- */
extern void           FUN_0007b208(void);
extern void           FUN_0007b1f0(void);
extern void           FUN_0007b220(void);
extern void           FUN_0007b324(word_t n);
extern void           FUN_0007b3e4(word_t n);
extern void           FUN_0007b3fc(word_t n);
extern void           FUN_0007bf4c(word_t n, word_t v);
extern void           FUN_00077070(void *dst, void *src);  /* append node entry */
extern void           FUN_000770e8(word_t);                /* node method helper */
extern word_t         FUN_00073498(word_t, word_t, word_t, word_t);
extern void           FUN_00080edc(void *obj);
extern void           FUN_00080ef4(void);
extern void           FUN_000824a4(word_t, word_t, word_t);
extern void           FUN_00084100(void *node);
extern void           FUN_00084c9c(word_t);
extern void           FUN_0008e3b0(void *node);            /* reset node list */
extern void           FUN_0008e3a4(void *node, void *scratch); /* begin node list */

/* ---- string / integer parsing (InternalExclaveLauncher util range) ---- */
extern void           FUN_00084000(void);
extern void           FUN_000840c8(void);
extern void           FUN_000840f4(void);
extern cl4_ret16_t    FUN_002a9ba8(word_t lo, word_t hi);  /* string length/ptr decode */
extern cl4_ret16_t    FUN_000ab1fc(word_t lo, word_t hi);  /* make cL4 string object */
extern cl4_ret16_t    FUN_000ab678(void);
extern cl4_ret16_t    FUN_0008e488(word_t lo, word_t hi);  /* string deref */
extern word_t         FUN_0008dfe0(void);                  /* current string/len fetch */
extern cl4_ret16_t    FUN_0008df28(void);
extern word_t         FUN_0008df38(void);
extern cl4_ret16_t    FUN_0008df68(void);
extern cl4_ret16_t    FUN_0008df78(void);
extern cl4_ret16_t    FUN_0008dfac(void);
extern cl4_ret16_t    FUN_0008de50(void *dst);
extern void           FUN_0008de50__(void);
extern cl4_ret16_t    FUN_0008de50(void *dst);

/* ---- cL4 logging / diagnostic helpers (FUN_0008e000-500) ---- */
extern void           FUN_0008e02c(void);
extern void           FUN_0008e048(void);
extern void           FUN_0008e058(void *a);
extern cl4_ret16_t    FUN_0008e070(word_t);
extern void           FUN_0008e088(void);
extern void           FUN_0008e0a0(void);
extern word_t         FUN_0008e0d4(void);
extern void           FUN_0008e0e8(void);
extern void           FUN_0008e0f4(void);
extern void           FUN_0008e100(void);
extern void           FUN_0008e10c(void);
extern void           FUN_0008e118(void);
extern void           FUN_0008e140(void);
extern void           FUN_0008e154(word_t lo, word_t hi, ...);
extern void           FUN_0008e160(void);
extern void           FUN_0008e170(word_t n);
extern void           FUN_0008e180(void);
extern void           FUN_0008e190(void);
extern word_t         FUN_0008e1a0(void);
extern void           FUN_0008e1b0(void);
extern void           FUN_0008e1c8(void);
extern void           FUN_0008e1d4(void);
extern void           FUN_0008e1e0(word_t tag, ...);
extern void           FUN_0008e1ec(void);
extern void           FUN_0008e1f8(word_t v);
extern void           FUN_0008e204(void);
extern void           FUN_0008e210(void);
extern void           FUN_0008e22c(void);
extern void           FUN_0008e248(void);
extern void           FUN_0008e254(void);
extern void           FUN_0008e260(void);
extern void           FUN_0008e270(void);
extern void           FUN_0008e280(void);
extern cl4_ret16_t    FUN_0008e290(word_t p, word_t n);
extern void           FUN_0008e2a0(void);
extern void           FUN_0008e2b0(void);
extern void           FUN_0008e2c0(void);
extern void           FUN_0008e2d0(void);
extern void           FUN_0008e2ec(const char *msg);
extern word_t         FUN_0008e304(const char *msg);
extern void           FUN_0008e31c(void);
extern void           FUN_0008e328(void);
extern void           FUN_0008e334(void);
extern void           FUN_0008e340(void);
extern void           FUN_0008e34c(void);
extern word_t         FUN_0008e358(void);
extern void           FUN_0008e370(void);
extern void           FUN_0008e37c(void);
extern void           FUN_0008e388(void);
extern word_t         FUN_0008e394(word_t lo, word_t hi);
extern void           FUN_0008e3c0(void);
extern void           FUN_0008e3ec(void);
extern void           FUN_0008e420(void);
extern void           FUN_0008e42c(void);
extern void           FUN_0008e438(void);
extern void           FUN_0008e444(void);
extern word_t         FUN_0008e450(void);
extern void           FUN_0008e45c(void);
extern word_t         FUN_0008e468(void);
extern void           FUN_0008e474(void);
extern void           FUN_0008e4a0(word_t n);
extern void           FUN_0008e4b4(void);
extern void           FUN_0008e4c0(void);
extern void           FUN_0008e4cc(void);
extern void           FUN_0008e4d8(void);
extern cl4_ret16_t    FUN_0008e4ec(void);
extern void           FUN_0008e500(word_t a, ...);
extern cl4_ret16_t    FUN_0008e518(void);
extern word_t         FUN_0008e530(void);
extern void           FUN_0008e544(word_t a, ...);

/* ---- DER object cap / endpoint helpers ---- */
extern cl4_ret16_t    FUN_0006ae9c(word_t lo, word_t hi);  /* lookup cap by name in node */
extern void           FUN_0008da6c(word_t);                /* dispatch obj method ptr */
extern cl4_ret16_t    FUN_0008dae4(void *a, word_t b, void *c);
extern void           FUN_0008db28(word_t);
extern void           FUN_0008dacc(word_t);
extern void           FUN_0008db58(void *src, void *dst);  /* copy node */
extern void           FUN_0008db90(void *node);            /* finalize node */
extern void           FUN_0008dbc0(void *node);            /* release node */
extern void           FUN_0008deb0(void *src, void *dst);
extern void           FUN_0008df14(const char *msg);       /* build fatal-msg string */
extern void           FUN_0008dfbc(void);
extern void           FUN_0008dfd0(void);
extern void           FUN_0008dff4(void);
extern void           FUN_0008df14__(void);

/* ---- fatal/panic ---- */
extern void           FUN_001afa84(const char *file, word_t a, word_t b, ...) __attribute__((noreturn)); /* fatal error */
extern void           FUN_002a4ab4(word_t code);           /* begin log entry */
extern void           thunk_FUN_002acbb8(word_t lo, word_t hi, ...); /* append log payload */
extern void           FUN_00205844(void *str, void *out, void *a, void *b, void *c); /* stringize for log */
extern void           FUN_0026b434(word_t obj, ...);
extern void           FUN_002591b4(word_t) __attribute__((noreturn));
extern word_t         FUN_00027724(word_t);
extern word_t         FUN_00027754(word_t);
extern void           SoftwareBreakpoint(word_t, word_t) __attribute__((noreturn));

/* ---- misc system ---- */
extern word_t         FUN_0006ce60(void);
extern word_t         FUN_0006cec8(word_t);extern word_t         FUN_0006cf0c(word_t);
extern word_t         FUN_0006cfe4(void);
extern word_t         FUN_0006d150(word_t);
extern word_t         FUN_0006d45c(void);
extern void           FUN_0006d4b4(void);
extern word_t         FUN_0006d4f0(void);
extern word_t         FUN_0006d4fc(void);
extern word_t         FUN_0006d508(void);
extern word_t         FUN_0006d514(void);
extern word_t         FUN_0006d520(void);
extern word_t         FUN_0006d240(word_t, word_t);
extern word_t         FUN_0006d698(void);
extern word_t         FUN_0006d6b8(void);
extern void           FUN_0006cf50(word_t);
extern word_t         FUN_0006ce80(word_t);
extern word_t         FUN_0006d240__(void);
extern word_t         FUN_0005526c(void);
extern word_t         FUN_00053568(word_t);
extern word_t         FUN_00054354(void) __attribute__((noreturn));
extern void           FUN_00055874(word_t, word_t, word_t);
extern word_t         FUN_00034f70(void);
extern void           FUN_0003beec(word_t, word_t, word_t, word_t);
extern word_t         FUN_00050654(word_t, word_t);
extern word_t         FUN_00050838(word_t*, word_t*, word_t*);
extern word_t         FUN_0004fe80(void);
extern void           FUN_00075ea4(word_t, word_t, word_t, word_t, word_t);
extern void           FUN_000f6dec(word_t, word_t, word_t, word_t);
extern void           FUN_000f6d10(word_t);
extern void           FUN_000f73e8(word_t, word_t, word_t, word_t, word_t, word_t);
extern word_t         FUN_000f76bc(word_t);
extern void           FUN_000fac98(void);
extern void           FUN_000fd198(word_t, word_t, word_t, word_t);
extern word_t         FUN_000fd854(word_t);
extern word_t         FUN_000e1f64(word_t);
extern word_t         FUN_000e18a0(word_t, word_t, word_t, word_t);
extern void           FUN_000e58cc(void);
extern word_t         FUN_000e5c4c(word_t);
extern void           FUN_000e7614(void *a, word_t b);
extern void           FUN_000e79d8(word_t);
extern word_t         FUN_000e8528(word_t);
extern word_t         FUN_000e884c(word_t);
extern word_t         FUN_000a9b10(word_t);
extern word_t         FUN_000a9b5c(word_t);
extern void           FUN_000a92a4(void);
extern void           FUN_000a8cbc(void);
extern word_t         FUN_000aaeac(void *a);
extern cl4_ret16_t    FUN_000a1558(void);
extern void           FUN_000ab36c(void);
extern word_t         FUN_000ab3e4(void);
extern word_t         FUN_000ab488(void);
extern word_t         FUN_000ab618(void);
extern word_t         FUN_000ab71c(void);
extern word_t         FUN_000ab8d8(word_t);
extern cl4_ret16_t    FUN_000ab1fc(word_t, word_t);
extern cl4_ret16_t    FUN_000ba594(word_t, word_t, word_t, word_t, word_t);
extern word_t         FUN_000baf14(word_t, word_t, word_t, word_t, word_t, word_t, word_t);
extern word_t         FUN_000bd174(word_t);
extern void           FUN_000bd7b8(word_t, word_t, word_t, word_t);
extern word_t         FUN_000bde60(word_t);
extern cl4_ret16_t    FUN_000b02dc(word_t, word_t);
extern cl4_ret16_t    thunk_FUN_000b02dc(word_t a, word_t b, ...);
extern word_t         FUN_000b03cc(void);
extern word_t         FUN_002a0cf8(word_t, word_t, word_t, word_t, word_t);
extern void           FUN_001000b8(word_t);
extern void           FUN_001004f0(void);
extern word_t         FUN_00101f08(word_t);
extern word_t         FUN_0010196c(void *a, word_t b, word_t c, word_t d);
extern void           FUN_00117cc4(void *dst, const void *src, size_t n); /* struct copy */
extern cl4_ret16_t    FUN_00151974(void);
extern void           FUN_00151a6c(void *, void *, const char *, word_t, word_t, word_t, word_t, word_t);
extern void           FUN_00157024(word_t, word_t, word_t, word_t, word_t);
extern void           FUN_00157308(word_t);
extern word_t         FUN_00167a6c(word_t);
extern word_t         FUN_000dda68(word_t);
extern void           FUN_000dd414(word_t, word_t, word_t, word_t, word_t, word_t, word_t);
extern word_t         FUN_0001a1c8(word_t a, ...);
extern void           FUN_0008db90__(void);
extern void           FUN_000f6dec__(void);

/* External global state referenced by this region. */
extern unsigned char  DAT_006add10;      /* 'verbose' debug flag (0/1) */
extern word_t         _DAT_004baeb0;     /* kernel object type word */
extern word_t         uRam00000000004baeb8;
extern word_t         _DAT_004c0f00;     /* component-graph node type word */
extern word_t         uRam00000000004c0f08;
extern unsigned long  uRam000000000064f1c8;
extern unsigned long  uRam000000000064f1d0;

/* Additional out-of-slice helpers used in bodies. */
void thunk_FUN_00114330(void);
word_t FUN_0008d43c(void);
word_t FUN_001f0130(void *a, void *b, void *c, void *d);
void FUN_0036b2d0(void *a, word_t b);
void FUN_001bac44(void *a, word_t b, word_t c);
void FUN_004b23d8(word_t);
word_t FUN_0006b79c(void);
word_t FUN_0008db28__dispatch(word_t a, word_t b);

/* In-slice helpers referenced by their Ghidra FUN_ name (defined below as
 * English-named functions). Extern aliases let bodies call them directly. */
void *FUN_0008684c(void);
cl4_ret16_t FUN_000867fc(void);
void FUN_000867b4(void);
void FUN_000867a8(void *a, ...);
void FUN_0008676c(word_t val, ...);
void FUN_00086794(void);
void FUN_00086834(void);
cl4_ret16_t FUN_0008647c(word_t a, word_t obj, word_t c, void *d, word_t *e);
void FUN_0008649c(word_t a, word_t obj, word_t c, word_t d);
void FUN_000864c4(word_t a, word_t obj, word_t c, word_t d, word_t e);
void FUN_000864f0(word_t a, word_t obj, word_t c);
long FUN_0008644c(unsigned long p);
unsigned long FUN_00085b68(unsigned long w);
void FUN_00085db4(void);
void FUN_00085890(word_t a, word_t b);

/* ---- forward declarations of in-slice functions (defined below) ---- */
void cL4_syscall_commit_result(word_t arg1, word_t arg2);
static unsigned long cL4_field16(unsigned long w);
void cL4_syscall_ep_2(long badge, word_t arg2);
void cL4_syscall_ep_3(long badge, word_t arg2, word_t arg3);
void cL4_ipc_send_5(word_t arg1, word_t arg2, unsigned char kind,
                    unsigned int flags, unsigned char opt);
word_t cL4_ipc_send_6_entry(word_t a1, word_t a2, word_t a3, word_t a4,
                            word_t a5, word_t a6);
void cL4_ipc_send_6(word_t arg1, word_t arg2, word_t arg3, unsigned char kind,
                    unsigned int flags, unsigned char opt);
void cL4_cap_invoke_4(long cap, word_t arg2);
void cL4_invoke_ep_0(void);
void cL4_init_postcheck(void);
void cL4_cap_invoke_5(unsigned char kind, word_t arg2, word_t arg3);
void cL4_invoke_ep_1(void);
void cL4_invoke_generic(word_t a, word_t b,
                        void (*handler)(word_t, word_t, word_t*, word_t*));
void cL4_invoke_vtbl_e0(void);
void cL4_invoke_vtbl_e0b(void);
void cL4_finalize(void);
void cL4_finalize_b(void);
void cL4_cap_invoke_1(word_t arg1);
cl4_ret16_t cL4_check_state(void);
void cL4_fatal_vas(void);
cl4_ret16_t cL4_handler_obj_init(cl4_ret16_t *rec);
void cL4_handler_run(void);
void cL4_handler_run_b(void);
void cL4_handler_run_c(void);
void cL4_invoke_obj_method(word_t obj);
void cL4_vtbl_call_90(void);
void cL4_vtbl_call_e0(void);
void cL4_set_global_f1c8(void);
void cL4_set_global_f1d0(void);
void cL4_indirect_jump_8(word_t a, word_t tgt, word_t c);
void cL4_indirect_call(word_t a, word_t *tbl);
void cL4_lock_f1f8(void);
long cL4_decode_method_ptr(unsigned long p);
cl4_ret16_t cL4_vtbl_ipc(word_t a, word_t obj, word_t c, void *d, word_t *e);
void cL4_vtbl_invoke(word_t a, word_t obj, word_t c, word_t d);
void cL4_vtbl_invoke5(word_t a, word_t obj, word_t c, word_t d, word_t e);
void cL4_vtbl_invoke1(word_t a, word_t obj, word_t c);
void cL4_lock_f250(void);
void cL4_lock_f2b8(void);
void cL4_check_then_init(void);
void cL4_build_arg_block(word_t val);
void cL4_build_arg_block_empty(void);
void cL4_noop_a(void);
void cL4_noop_b(void);
void cL4_fatal_bad_arg(word_t arg);
void cL4_noop_c(void);
cl4_ret16_t cL4_method_thunk_fetch(void);
void cL4_dispatch_cur(void);
void cL4_noop_d(void);
void *cL4_syscall_anchor(void);
void cL4_noop_e(void);
void cL4_obj_method_58(word_t *a, word_t *b);
void cL4_node_method_58(void);
void cL4_node_replace(word_t val);
cl4_ret16_t cL4_node_pair_30(word_t val);
void cL4_obj_method_70(word_t *a, word_t *b);
void cL4_node18_method_70(void);
void cL4_node18_replace(word_t val);
cl4_ret16_t cL4_node18_pair(word_t val);
void cL4_obj_method_88(word_t *a, word_t *b);
void cL4_node20_method(void);
void cL4_node20_replace(word_t val);
cl4_ret16_t cL4_node20_pair(word_t val);
void cL4_edge_push(word_t edge, word_t dst);
void cL4_dump_edges(unsigned int flags, word_t param2);
void cL4_node_release3(void);
void FUN_0008bfec(void *out, word_t a, word_t size, word_t b, word_t obj);
void cL4_node_destroy_a(void);
void cL4_node_destroy_b(void);
void cL4_node_init3(void);
void cL4_node_init3_b(void);
void cL4_node_init3_c(void);
word_t cL4_alloc_init_node(word_t param1);
void cL4_node_ctor(word_t param1);
void cL4_node_teardown(void);
void cL4_node_destroy_c(void);
void cL4_node_destroy_d(void);
word_t cL4_parse_int_with_caps(word_t cap);
void getOrAllocateComponentResourceCapFromEdge(word_t a, word_t b, word_t c);
word_t getOrAllocateCapFromEdge(word_t *edge);
word_t cL4_resolve_named_cap(word_t *param1, word_t param2);
cl4_ret16_t cL4_lookup_current_comp(word_t a, word_t b);
void cL4_component_alloc_resource(word_t *param1, word_t *param2);
word_t cL4_lookup_resource_idx(void);
void cL4_component_state_check(void);
void cL4_log_components(word_t a, word_t b, word_t c, word_t d, word_t e,
                        word_t list, word_t *dispatch);
void cL4_build_phys_info(word_t out);
word_t cL4_enum_nodes(word_t (*probe)(word_t));
void cL4_dump_node_debug(word_t a, word_t b);
void cL4_dump_node_named(word_t a, word_t b, word_t c);
void cL4_log_memory_usage(void);
void cL4_log_resource_type(word_t a, char kind);
cl4_ret16_t cL4_build_comp_record(void);
void cL4_alloc_untyped_resources(word_t a, word_t b, word_t c);
cl4_ret16_t cL4_diag_intro(void);
cl4_ret16_t cL4_diag_intro_b(void);
cl4_ret16_t cL4_diag_intro_c(void);
void cL4_parse_component_str(word_t a, word_t b, unsigned char *digits, word_t limit);
void cL4_parse_resource_pair(word_t a, word_t b, word_t c, word_t d);
void cL4_device_tree_check(void);
void cL4_parse_resource_arg(word_t a, word_t *param2);
void cL4_build_device_info(word_t a, word_t b, word_t *param3);
void cL4_build_dev_range(word_t *out, word_t a, word_t size, word_t b, word_t obj);
void cL4_emit_metal_name(word_t a, word_t b, word_t c, word_t *param4);
void cL4_dispatch_resource_type(void);
cl4_ret16_t cL4_log_share_status(char a, char b);
void cL4_snapshot_node(cl4_ret16_t *out);
void cL4_snapshot_release(void);
word_t cL4_snapshot_emit(void);
void cL4_record_emit3(word_t a, word_t b, word_t c);
void cL4_parse_string_int(unsigned long *out, unsigned long *in, word_t ctx_a, word_t ctx_b);
word_t cL4_and64(word_t a, word_t b);
unsigned int cL4_and32(unsigned int a, unsigned int b);
void cL4_and_byte(unsigned char *out, unsigned char *in);
long cL4_record_build(long *out, word_t dst, word_t n);
void cL4_emit_bitarray_32(word_t a, word_t b, long n, word_t table);
void cL4_emit_bitarray_64(word_t a, word_t b, long n, word_t table);
void cL4_emit_bitarray_caps(word_t a, word_t b, long n);
void cL4_emit_bitarray_pairs(word_t a, word_t b, long n);
long cL4_merge_node_lists(long *out, word_t srcA, long n, word_t srcB);
void cL4_syscall_dispatch(void *anchor, word_t cap, word_t kind, word_t a2, word_t a3);
void cL4_dispatch_endpoint(word_t lo, word_t hi, void *handler);

/* ================================================================== *
 * 0x85890 — 0x86700 : syscall entry + vtable dispatch wrappers
 * ================================================================== */

/* FUN_00085890 @ 0x85890   (est. cL4_syscall_commit_result)
 * Ghidra: void FUN_00085890(undefined8 param_1, undefined8 param_2)
 * Commits the (param_1,param_2) syscall result pair to the shared result
 * buffer under a global lock. If the current-context check (FUN_0006e6dc)
 * says a result is pending, packs an error code (low) and a 16-bit status
 * field (FUN_00085b68 of the args) into the result struct, then unlocks.
 * Confidence: medium
 * Notes: lock/unlock pair FUN_0036993c/FUN_0036986c around globals
 *   0x65fa88/0x65f980; *extraout_x1 = error word. */
void cL4_syscall_commit_result(word_t arg1, word_t arg2)
{
    int have_result = FUN_0006e6dc();
    if (have_result != 0) {
        unsigned short status = (unsigned short)(arg1 >> 16); /* 16-bit field */
        FUN_0036993c((void *)0x65fa88, (void *)0x65f980, 0, 0);
        *(int *)(uintptr_t)0x65fa88 = have_result;                 /* error word */
        *(unsigned short *)(uintptr_t)(0x65fa88 + 8) = status;
        FUN_0036986c();
    }
}

/* FUN_00085b68 @ 0x85b68   (est. cL4_field16)
 * Ghidra: ulong FUN_00085b68(ulong param_1)
 * Extract bits [31:16] of the word. Trivial field extractor.
 * Confidence: high */
static unsigned long cL4_field16(unsigned long w) { return (w >> 16) & 0xffffu; }

/* FUN_00085928 @ 0x85928   (est. cL4_syscall_ep_2)
 * Ghidra: void FUN_00085928(long param_1, undefined8 param_2)
 * seL4-style syscall entry: if the capability pointer is valid (>=0) take
 * the kernel lock and tail-call the syscall dispatcher (FUN_0008684c anchor)
 * with (kind=0x11, cap, arg2). A negative badge hits a breakpoint (panic).
 * Confidence: medium
 * Notes: tail call via extraout_x9; kind constant 0x11 (notification/IPC). */
void cL4_syscall_ep_2(long badge, word_t arg2)
{
    if (badge >= 0) {
        FUN_0036a9d4((void *)0x64f1f8, (void *)0x64e1c0);
        cL4_syscall_dispatch(FUN_0008684c(), (word_t)badge, 0x11, arg2, 0);
        return;
    }
    SoftwareBreakpoint(1, 0x859b8);   /* negative badge: invalid cap */
}

/* FUN_000859b8 @ 0x859b8   (est. cL4_syscall_ep_3)
 * Ghidra: void FUN_000859b8(long param_1, undefined8 param_2, undefined8 param_3)
 * As cL4_syscall_ep_2 but with three payload words (badge, arg2, arg3).
 * Confidence: medium */
void cL4_syscall_ep_3(long badge, word_t arg2, word_t arg3)
{
    if (badge >= 0) {
        FUN_0036a9d4((void *)0x64f1f8, (void *)0x64e1c0);
        cL4_syscall_dispatch(FUN_0008684c(), (word_t)badge, 0x11, arg2, arg3);
        return;
    }
    SoftwareBreakpoint(1, 0x85a54);   /* invalid badge */
}

/* FUN_00085a54 @ 0x85a54   (est. cL4_ipc_send_5)
 * Ghidra: void FUN_00085a54(undefined8,undefined8,undefined1,uint,undefined1)
 * Full IPC-send entry: validates args, builds a message-register block, calls
 * the per-object IPC handler (FUN_0008647c), commits the result, then runs
 * the syscall epilogue (which may panic). The final-flag is set at x20+0x21.
 * Confidence: low
 * Notes: message args 0x11/kind, FUN_0006b2ec/FUN_0006e7c0 build the MR;
 *   tail dispatch via extraout_x8; epilogue FUN_000651bc -> 0x11d7e8 panic. */
void cL4_ipc_send_5(word_t arg1, word_t arg2, unsigned char kind,
                    unsigned int flags, unsigned char opt)
{
    unsigned char mr_kind = kind;
    unsigned char mr_opt  = opt;
    cl4_ret16_t mr = FUN_0006b2ec();
    word_t mr_hi = mr.hi;
    word_t mr_lo = 0;
    unsigned int  mr_flags = 0;
    word_t *slot = (word_t *)(uintptr_t)(0x10);
    slot[0] = 0;
    slot[1] = 0;
    word_t saved = /* extraout_x8 */ 0;
    FUN_0006e7c0((void *)mr.lo, (void *)(uintptr_t)0x28);
    *(unsigned char *)(uintptr_t)0x20 = opt;
    FUN_000867fc();
    word_t pair = 0; /* (*extraout_x8_00)() */
    FUN_0036a1a0(slot, (void *)(uintptr_t)0, 0x21, 0);
    cl4_ret16_t r = cL4_vtbl_ipc(0, pair, flags & ~1u, (void *)&mr_kind, slot);
    FUN_0036a20c((void *)(uintptr_t)0);
    *(unsigned char *)(uintptr_t)0x21 = 1;
    cL4_syscall_commit_result(r.lo, r.hi);
    if (0 /* unaff_x21 */ != 0) { FUN_0036b118((void *)0); }
    FUN_000026e8((void *)arg1);
    FUN_000651bc(saved);
    if (0 /* in_ZR */) return;
    FUN_0011d7e8(0);   /* does not return */
}

/* FUN_00085b70 @ 0x85b70   (est. cL4_ipc_send_6_entry)
 * Ghidra: undefined8 FUN_00085b70(6 args)
 * Entry stub: grabs a caller-context token, then forwards all six arguments
 * to FUN_00085bf0. Returns the token.
 * Confidence: low */
word_t cL4_ipc_send_6_entry(word_t a1, word_t a2, word_t a3, word_t a4,
                            word_t a5, word_t a6)
{
    FUN_000867b4();
    word_t token = FUN_0006ce60();
    cL4_ipc_send_6(a1, a2, a3, a4, a5, a6);
    return token;
}

/* FUN_00085bf0 @ 0x85bf0   (est. cL4_ipc_send_6)
 * Ghidra: void FUN_00085bf0(undefined8,undefined8,undefined8,undefined1,uint,undefined1)
 * Six-argument IPC send: like FUN_00085a54 but passes `flags|1` to the IPC
 * handler and carries a third payload word.
 * Confidence: low
 * Notes: mirror of 0x85a54 with param_5|1 and an extra word (uStack_80). */
void cL4_ipc_send_6(word_t arg1, word_t arg2, word_t arg3, unsigned char kind,
                    unsigned int flags, unsigned char opt)
{
    unsigned char mr_kind = kind;
    unsigned char mr_opt  = opt;
    cl4_ret16_t mr = FUN_0006b2ec();
    word_t mr_hi = mr.hi;
    unsigned int mr_flags = 0;
    word_t *slot = (word_t *)(uintptr_t)0x10;
    slot[0] = 0;
    slot[1] = 0;
    *(unsigned char *)(uintptr_t)0x20 = opt;
    word_t extra = arg3;
    word_t saved = 0;
    FUN_0006e7c0((void *)mr.lo, (void *)(uintptr_t)0x28);
    FUN_000867fc();
    word_t pair = 0;
    FUN_0036a1a0(slot, (void *)(uintptr_t)0, 0x21, 0);
    cl4_ret16_t r = cL4_vtbl_ipc(0, pair, flags | 1u, (void *)&mr_kind, slot);
    FUN_0036a20c((void *)(uintptr_t)0);
    *(unsigned char *)(uintptr_t)0x21 = 1;
    cL4_syscall_commit_result(r.lo, r.hi);
    if (0 != 0) { FUN_0036b118((void *)0); }
    FUN_000026e8((void *)arg1);
    FUN_000651bc(saved);
    if (0) return;
    FUN_0011d7e8(0);
}

/* FUN_00085d00 @ 0x85d00   (est. cL4_cap_invoke_4)
 * Ghidra: void FUN_00085d00(long param_1, undefined8 param_2)
 * Capability invoke: build the arg block, then call the per-cap invoke handler
 * FUN_0008649c with (block0, block1, cap, arg2). Invalid cap -> breakpoint.
 * Confidence: medium */
void cL4_cap_invoke_4(long cap, word_t arg2)
{
    unsigned char blk[24];
    FUN_000867a8((void *)(uintptr_t)0x10, blk);
    FUN_0036a1a0((void *)0);
    if (cap >= 0) {
        cL4_vtbl_invoke(*(word_t *)(uintptr_t)0x10, *(word_t *)(uintptr_t)0x18,
                        (word_t)cap, arg2);
        cL4_syscall_commit_result(0, 0);
        return;
    }
    SoftwareBreakpoint(1, 0x85d68);   /* negative badge */
}

/* FUN_00085d68 @ 0x85d68   (est. cL4_invoke_ep_0)
 * Ghidra: void FUN_00085d68(void)
 * Invoke on an endpoint object: fetch the kernel reg pair and dispatch to
 * the LAB_000864b0 endpoint handler; then epilogue.
 * Confidence: low */
void cL4_invoke_ep_0(void)
{
    cl4_ret16_t p = FUN_0006b2ec();
    cL4_dispatch_endpoint(p.lo, p.hi, (void *)0x864b0);
    FUN_000651bc(0);
    if (0) return;
    FUN_0011d7e8(0);
}

/* FUN_00085db4 @ 0x85db4   (est. cL4_init_postcheck)
 * Ghidra: void FUN_00085db4(void)
 * Post-initialization re-check: run the epilogue twice; if it passed the
 * first time, run the arg/init helpers (FUN_0008676c, FUN_00086834) and
 * epilogue again.
 * Confidence: low */
void cL4_init_postcheck(void)
{
    FUN_0006b2ec();
    FUN_000651bc(0);
    if (!0) { FUN_0011d7e8(0); }
    FUN_0006b2ec();
    FUN_0008676c(0);
    FUN_00086834();
    FUN_000651bc(0);
    if (0) return;
    FUN_0011d7e8(0);
}

/* FUN_00085e24 @ 0x85e24   (est. cL4_cap_invoke_5)
 * Ghidra: void FUN_00085e24(undefined1,undefined8,undefined8)
 * Capability invoke with three payload words (kind + two args) via
 * FUN_000864c4 handler.
 * Confidence: medium */
void cL4_cap_invoke_5(unsigned char kind, word_t arg2, word_t arg3)
{
    unsigned char blk[24];
    FUN_000867a8((void *)(uintptr_t)0x10, blk);
    FUN_0036a1a0((void *)0);
    cL4_vtbl_invoke5(*(word_t *)(uintptr_t)0x10, *(word_t *)(uintptr_t)0x18,
                     kind, arg2, arg3);
    cL4_syscall_commit_result(0, 0);
}

/* FUN_00085e8c @ 0x85e8c   (est. cL4_invoke_ep_1)
 * Ghidra: void FUN_00085e8c(void)
 * Second endpoint invoke path: dispatch to the LAB_000864dc endpoint
 * handler, then epilogue.
 * Confidence: low */
void cL4_invoke_ep_1(void)
{
    cl4_ret16_t p = FUN_0006b2ec();
    cL4_dispatch_endpoint(p.lo, p.hi, (void *)0x864dc);
    FUN_000651bc(0);
    if (0) return;
    FUN_0011d7e8(0);
}

/* FUN_00085ed8 @ 0x85ed8   (est. cL4_invoke_generic)
 * Ghidra: void FUN_00085ed8(undefined8,undefined8,code *param_3)
 * Generic invoke dispatcher: pulls the reg pair, validates both words are
 * non-negative, builds the arg block, then calls the supplied handler with
 * (block0, block1, &lo, &hi) which fills the result words. After the call,
 * re-validates and runs the epilogue.
 * Confidence: low
 * Notes: handler pointer (param_3) is a function; result carried via local_48/50. */
void cL4_invoke_generic(word_t a, word_t b, void (*handler)(word_t, word_t, word_t*, word_t*))
{
    cl4_ret16_t p = FUN_0006b2ec();
    word_t lo = p.hi;
    word_t hi = p.lo;
    if (hi < 0) { SoftwareBreakpoint(1, 0x85f70); }
    if (lo < 0) { SoftwareBreakpoint(1, 0x85f74); }
    word_t saved = 0;
    unsigned char blk[24];
    FUN_000867a8((void *)(uintptr_t)0x10, blk);
    FUN_0036a1a0((void *)0);
    handler(*(word_t *)(uintptr_t)0x10, *(word_t *)(uintptr_t)0x18, &hi, &lo);
    cL4_syscall_commit_result(0, 0);
    if (0 /* x21 */ == 0) {
        if (hi < 0) { SoftwareBreakpoint(1, 0x85f78); }
        if (lo < 0) { SoftwareBreakpoint(1, 0x85f7c); }
    }
    FUN_000651bc(saved);
    if (!0) { FUN_0011d7e8(0); }
}

/* FUN_00085f80 @ 0x85f80   (est. cL4_invoke_vtbl_e0)
 * Ghidra: void FUN_00085f80(void)
 * Invoke the +0xe0 method of the object's vtable (via x20->[0] object);
 * if it reports an error the code either breakpoints (negative) or calls
 * the thunk_FUN_00114330 error path.
 * Confidence: low */
void cL4_invoke_vtbl_e0(void)
{
    cl4_ret16_t r = (*(cl4_ret16_t (**)(void))(**(word_t **)(uintptr_t)0 + 0xe0))();
    if (r.lo != 0) {
        if (r.hi < 0) { SoftwareBreakpoint(1, 0x85fcc); }
        if (r.hi != 0) { thunk_FUN_00114330(); return; }
    }
}

/* FUN_00085f84 @ 0x85f84   (est. cL4_invoke_vtbl_e0b)
 * Ghidra: void FUN_00085f84(void)
 * Identical to FUN_00085f80 (second copy of the +0xe0 vtable invoke).
 * Confidence: low */
void cL4_invoke_vtbl_e0b(void)
{
    cl4_ret16_t r = (*(cl4_ret16_t (**)(void))(**(word_t **)(uintptr_t)0 + 0xe0))();
    if (r.lo != 0) {
        if (r.hi < 0) { SoftwareBreakpoint(1, 0x85fcc); }
        if (r.hi != 0) { thunk_FUN_00114330(); return; }
    }
}

/* FUN_00085fcc @ 0x85fcc   (est. cL4_finalize)
 * Ghidra: void FUN_00085fcc(void)
 * Finalize the syscall context: fetch reg pair, run the arg-parse and
 * dispatch helpers, then epilogue.
 * Confidence: low */
void cL4_finalize(void)
{
    FUN_0006b2ec();
    FUN_00086794();
    FUN_00086834();
    FUN_000651bc(0, 0, 0, 0, 0);
    if (0) return;
    FUN_0011d7e8(0);
}

/* FUN_0008601c @ 0x8601c   (est. cL4_finalize_b)
 * Ghidra: void FUN_0008601c(void)
 * Finalize variant: same helpers, inverted epilogue branch. Two unreachable
 * blocks were pruned (0x8606c/0x86070).
 * Confidence: low */
void cL4_finalize_b(void)
{
    FUN_0006b2ec();
    FUN_00086794();
    FUN_00086834();
    FUN_000651bc(0);
    if (!0) { FUN_0011d7e8(0); }
}

/* FUN_00086078 @ 0x86078   (est. cL4_cap_invoke_1)
 * Ghidra: void FUN_00086078(undefined8 param_1)
 * Cap invoke with a single payload via FUN_000864f0 handler.
 * Confidence: medium */
void cL4_cap_invoke_1(word_t arg1)
{
    unsigned char blk[24];
    FUN_000867a8((void *)(uintptr_t)0x10, blk);
    FUN_0036a1a0((void *)0);
    cL4_vtbl_invoke1(*(word_t *)(uintptr_t)0x10, *(word_t *)(uintptr_t)0x18, arg1);
    cL4_syscall_commit_result(0, 0);
}

/* FUN_000860c8 @ 0x860c8   (est. cL4_check_state)
 * Ghidra: void FUN_000860c8(void)
 * Validate the current syscall state: run arg-parse + dispatch, then verify
 * the returned count word (local_40) is sane (>=0 and, if nonzero, has a
 * matching data word local_48). Epilogue.
 * Confidence: low */
cl4_ret16_t cL4_check_state(void)
{
    word_t data = 0, count = 0, saved = 0;
    FUN_0006b2ec();
    FUN_0008676c(0);
    FUN_00086834();
    if (count < 0) { SoftwareBreakpoint(1, 0x86114); }
    if (count != 0 && data == 0) { SoftwareBreakpoint(1, 0x86118); }
    FUN_000651bc(saved);
    if (0) return (cl4_ret16_t){0,0};
    FUN_0011d7e8(0);
    return (cl4_ret16_t){0,0};
}

/* FUN_0008611c @ 0x8611c   (est. cL4_fatal_vas)
 * Ghidra: void FUN_0008611c(void)
 * Raise a fatal InternalExclaveLauncher VASExtension error.
 * Confidence: high
 * Notes: s_Fatal_error_005accd0, s_InternalExclaveLauncher_VASExten_005c03a0,
 *   error words 0xd000000000000030/0x80000000005c04f0, codes 0xb/2/0x2a/0x1a9. */
void cL4_fatal_vas(void)
{
    FUN_001afa84("Fatal error", 0xb, 2, 0xd000000000000030ull, 0x80000000005c04f0ull,
                 "InternalExclaveLauncher/VASExten...", 0x2a, 2, 0x1a9, 0);
}

/* FUN_00086178 @ 0x86178   (est. cL4_handler_obj_init)
 * Ghidra: undefined1 [16] FUN_00086178(undefined1 (*param_1) [16])
 * Build a handler-object record: store the current context word into
 * param_1[1], then run the state check and return {lo=FUN_000861c0, hi=param_1}.
 * Confidence: low */
cl4_ret16_t cL4_handler_obj_init(cl4_ret16_t *rec)
{
    rec->hi = (word_t)(uintptr_t)0 /* unaff_x20 */;
    cl4_ret16_t c = cL4_check_state();
    rec->lo = c.lo;
    return (cl4_ret16_t){ .hi = (word_t)rec, .lo = (word_t)(uintptr_t)cL4_handler_run };
}

/* FUN_000861c0 @ 0x861c0   (est. cL4_handler_run)
 * Ghidra: void FUN_000861c0(void)
 * Handler run: first fatal-assert (FUN_0008611c), then compute the sum of the
 * two count words (validating the odd case), and run the epilogue.
 * Confidence: low */
void cL4_handler_run(void)
{
    word_t w58 = 0, w50 = 0, saved = 0;
    cL4_fatal_vas();
    FUN_0006b2ec();
    FUN_0008676c(0);
    FUN_00086834();
    if (w50 < 0) { SoftwareBreakpoint(1, 0x86230); }
    long sum;
    if (w50 == 0) {
        if (w58 == 0) { sum = 0; }
        else { sum = w50 + w58; }
    } else if (w58 == 0) {
        SoftwareBreakpoint(1, 0x86204);
        sum = 0;
    } else {
        sum = w50 + w58;
    }
    FUN_000651bc(saved, w58, sum);
    if (0) return;
    FUN_0011d7e8(0);
}

/* FUN_000861c4 @ 0x861c4   (est. cL4_handler_run_b)
 * Ghidra: void FUN_000861c4(void)
 * Identical to FUN_000861c0 (second copy).
 * Confidence: low */
void cL4_handler_run_b(void)
{
    word_t w58 = 0, w50 = 0, saved = 0;
    cL4_fatal_vas();
    FUN_0006b2ec();
    FUN_0008676c(0);
    FUN_00086834();
    if (w50 < 0) { SoftwareBreakpoint(1, 0x86230); }
    long sum;
    if (w50 == 0) {
        if (w58 == 0) { sum = 0; }
        else { sum = w50 + w58; }
    } else if (w58 == 0) {
        SoftwareBreakpoint(1, 0x86204);
        sum = 0;
    } else {
        sum = w50 + w58;
    }
    FUN_000651bc(saved, w58, sum);
    if (0) return;
    FUN_0011d7e8(0);
}

/* FUN_000861d0 @ 0x861d0   (est. cL4_handler_run_c)
 * Ghidra: void FUN_000861d0(void)
 * Third copy of the sum-check handler (without the leading fatal assert).
 * Confidence: low */
void cL4_handler_run_c(void)
{
    word_t data = 0, count = 0, saved = 0;
    FUN_0006b2ec();
    FUN_0008676c(0);
    FUN_00086834();
    if (count < 0) { SoftwareBreakpoint(1, 0x86230); }
    long sum;
    if (count == 0) {
        if (data == 0) { sum = 0; }
        else { sum = count + data; }
    } else if (data == 0) {
        SoftwareBreakpoint(1, 0x86204);
        sum = 0;
    } else {
        sum = count + data;
    }
    FUN_000651bc(saved, data, sum);
    if (0) return;
    FUN_0011d7e8(0);
}

/* FUN_00086234 @ 0x86234   (est. cL4_invoke_obj_method)
 * Ghidra: void FUN_00086234(long param_1)
 * Invoke a method on object param_1: read its vtable words at +0x18/+0x20,
 * decode the method pointer (FUN_0008644c), call it, then run the invoke
 * handler FUN_0003beec with the two result words and the arg block.
 * Confidence: low */
void cL4_invoke_obj_method(word_t obj)
{
    word_t v0 = *(word_t *)(obj + 0x18);
    word_t v1 = *(word_t *)(obj + 0x20);
    FUN_0006a4c0((void *)obj, v0);
    void (*fn)(void) = (void (*)(void))cL4_decode_method_ptr(v1);
    cl4_ret16_t r = ((cl4_ret16_t (*)(word_t, word_t))fn)(v0, v1);
    unsigned char blk[24];
    FUN_000867a8((void *)(uintptr_t)0x10, blk);
    FUN_0036a1a0((void *)0);
    FUN_0003beec(r.lo, r.hi, *(word_t *)(uintptr_t)0x10, *(word_t *)(uintptr_t)0x18);
    cL4_syscall_commit_result(0, 0);
}

/* FUN_000862cc @ 0x862cc   (est. cL4_vtbl_call_90)
 * Ghidra: void FUN_000862cc(void)
 * Tail-call the object's +0x90 vtable method.
 * Confidence: low */
void cL4_vtbl_call_90(void)
{
    (**(void (**)(void))(*(word_t *)(uintptr_t)0 + 0x90))();
}

/* FUN_00086308 @ 0x86308   (est. cL4_vtbl_call_e0)
 * Ghidra: void FUN_00086308(void)
 * Tail-call the object's +0xe0 vtable method.
 * Confidence: low */
void cL4_vtbl_call_e0(void)
{
    (**(void (**)(void))(*(word_t *)(uintptr_t)0 + 0xe0))();
}

/* FUN_00086368 @ 0x86368   (est. cL4_set_global_f1c8)
 * Ghidra: void FUN_00086368(void)
 * Write a constant 8-byte pattern into global 0x64f1c8 (boot strapping).
 * Confidence: low
 * Notes: uRam000000000064f1c8 = 0x340001c8b40001a1; unreachable block at 0x8637c. */
void cL4_set_global_f1c8(void)
{
    uRam000000000064f1c8 = 0x340001c8b40001a1ull;
}

/* FUN_000863bc @ 0x863bc   (est. cL4_set_global_f1d0)
 * Ghidra: void FUN_000863bc(void)
 * Write a constant 8-byte pattern into global 0x64f1d0.
 * Confidence: low
 * Notes: uRam000000000064f1d0 = 0xd280000194004852; unreachable block at 0x863d0. */
void cL4_set_global_f1d0(void)
{
    uRam000000000064f1d0 = 0xd280000194004852ull;
}

/* FUN_00086410 @ 0x86410   (est. cL4_indirect_jump_8)
 * Ghidra: void FUN_00086410(undefined8 param_1, long param_2, undefined8 param_3)
 * Indirect jump: if the target word is nonzero, call the function pointer at
 * param_2+8 with (param_1, param_3); else fatal (FUN_00054354).
 * Confidence: medium
 * Notes: jump table at 0x86420 too many branches (treated as call). */
void cL4_indirect_jump_8(word_t a, word_t tgt, word_t c)
{
    if (tgt != 0) {
        (**(void (**)(word_t, word_t))(tgt + 8))(a, c);
        return;
    }
    FUN_00054354();   /* noreturn */
}

/* FUN_00086434 @ 0x86434   (est. cL4_indirect_call)
 * Ghidra: void FUN_00086434(undefined8 param_1, undefined8 *param_2)
 * Indirect call through *param_2 (the method table head).
 * Confidence: low
 * Notes: indirect jump at 0x8643c too many branches. */
void cL4_indirect_call(word_t a, word_t *tbl)
{
    (*(void (**)(void))*tbl)();
}

/* FUN_00086440 @ 0x86440   (est. cL4_lock_f1f8)
 * Ghidra: void FUN_00086440(void)
 * Acquire the lock at global 0x64f1f8.
 * Confidence: high */
void cL4_lock_f1f8(void) { FUN_00077770((void *)0x64f1f8); }

/* FUN_0008644c @ 0x8644c   (est. cL4_decode_method_ptr)
 * Ghidra: long FUN_0008644c(ulong param_1)
 * Decode a method/relocation pointer: if bit0 set, dereference the tagged
 * pointer; then return the target = word+4 plus the signed int at word+4.
 * (Classic ARM64 image-relative method thunk decoding.)
 * Confidence: high */
long cL4_decode_method_ptr(unsigned long p)
{
    if ((p & 1) != 0) { p = *(unsigned long *)(p & ~1ull); }
    return (long)(p + 4) + (long)*(int *)(p + 4);
}

/* FUN_0008647c @ 0x8647c   (est. cL4_vtbl_ipc)
 * Ghidra: void FUN_0008647c(undefined8,long,undefined8,undefined8,undefined8)
 * Dispatch to the object's +0x30 vtable method with (a, c, d, e, 0, 0).
 * Confidence: medium
 * Notes: indirect jump at 0x86498 too many branches. */
cl4_ret16_t cL4_vtbl_ipc(word_t a, word_t obj, word_t c, void *d, word_t *e)
{
    cl4_ret16_t r;
    void (*fn)(word_t, word_t, void*, word_t*, word_t, word_t) =
        (void (*)(word_t, word_t, void*, word_t*, word_t, word_t))(*(word_t *)(obj + 0x30));
    fn(a, c, d, (word_t*)e, 0, 0);
    r.lo = r.hi = 0;
    return r;
}

/* FUN_0008649c @ 0x8649c   (est. cL4_vtbl_invoke)
 * Ghidra: void FUN_0008649c(undefined8,long,undefined8,undefined8)
 * Dispatch to the object's +0x28 vtable method with (a, c, d).
 * Confidence: medium */
void cL4_vtbl_invoke(word_t a, word_t obj, word_t c, word_t d)
{
    (**(void (**)(word_t, word_t, word_t))(obj + 0x28))(a, c, d);
}

/* FUN_000864c4 @ 0x864c4   (est. cL4_vtbl_invoke5)
 * Ghidra: void FUN_000864c4(undefined8,long,undefined8,undefined8,undefined8)
 * Dispatch to the object's +0x50 vtable method with (a, c, d, e).
 * Confidence: medium */
void cL4_vtbl_invoke5(word_t a, word_t obj, word_t c, word_t d, word_t e)
{
    (**(void (**)(word_t, word_t, word_t, word_t))(obj + 0x50))(a, c, d, e);
}

/* FUN_000864f0 @ 0x864f0   (est. cL4_vtbl_invoke1)
 * Ghidra: void FUN_000864f0(undefined8,long,undefined8)
 * Dispatch to the object's +0x10 vtable method with (a, c).
 * Confidence: medium */
void cL4_vtbl_invoke1(word_t a, word_t obj, word_t c)
{
    (**(void (**)(word_t, word_t))(obj + 0x10))(a, c);
}

/* FUN_00086584 @ 0x86584   (est. cL4_lock_f250)
 * Ghidra: void FUN_00086584(void)
 * Acquire the lock at global 0x64f250.
 * Confidence: high */
void cL4_lock_f250(void) { FUN_00077770((void *)0x64f250); }

/* FUN_00086590 @ 0x86590   (est. cL4_lock_f2b8)
 * Ghidra: void FUN_00086590(void)
 * Acquire the lock at global 0x64f2b8.
 * Confidence: high */
void cL4_lock_f2b8(void) { FUN_00077770((void *)0x64f2b8); }

/* ================================================================== *
 * 0x86700 — 0x87180 : arg-block helpers + IPC method pairs
 * ================================================================== */

/* FUN_00086734 @ 0x86734   (est. cL4_check_then_init)
 * Ghidra: void FUN_00086734(void)
 * Epilogue check; if it passes, run the post-check (FUN_00085db4), else panic.
 * Confidence: low */
void cL4_check_then_init(void)
{
    FUN_0006b2ec();
    FUN_000651bc(0);
    if (0) { cL4_init_postcheck(); return; }
    FUN_0011d7e8(0);
}

/* FUN_0008676c @ 0x8676c   (est. cL4_build_arg_block)
 * Ghidra: void FUN_0008676c(undefined8 param_1)
 * Build a syscall argument block at x20+0x10: store the incoming value word,
 * initialize the 5-word record (kind=0x11, rest 0) and enter the section.
 * Confidence: low */
void cL4_build_arg_block(word_t val)
{
    word_t *blk = (word_t *)(uintptr_t)0x10;
    blk[0] = 0x11;   /* kind */
    blk[1] = 0;
    blk[2] = 0;
    blk[3] = 0;
    blk[4] = 0;
    FUN_0036a1a0((void *)(uintptr_t)0x10, (void *)(uintptr_t)0x20, 0, 0);
}

/* FUN_00086794 @ 0x86794   (est. cL4_build_arg_block_empty)
 * Ghidra: void FUN_00086794(void)
 * Enter the section for an empty argument block at x20+0x10.
 * Confidence: low */
void cL4_build_arg_block_empty(void)
{
    FUN_0036a1a0((void *)(uintptr_t)0x10, (void *)(uintptr_t)0x20, 0, 0);
}

/* FUN_000867a8 @ 0x867a8   (est. cL4_noop_a)
 * Ghidra: void FUN_000867a8(void) — empty body.
 * Confidence: high */
void cL4_noop_a(void) { }

/* FUN_000867b4 @ 0x867b4   (est. cL4_noop_b)
 * Ghidra: void FUN_000867b4(void) — empty body.
 * Confidence: high */
void cL4_noop_b(void) { }

/* FUN_000867c4 @ 0x867c4   (est. cL4_fatal_bad_arg)
 * Ghidra: void FUN_000867c4(undefined8 param_1)
 * Raise a fatal InternalExclaveLauncher VASExtension error carrying the
 * incoming arg word.
 * Confidence: high */
void cL4_fatal_bad_arg(word_t arg)
{
    FUN_001afa84("Fatal error", 0xb, 2, 0, 0,
                 "InternalExclaveLauncher/VASExten...", 0x2a, 2, arg);
}

/* FUN_000867ec @ 0x867ec   (est. cL4_noop_c)
 * Ghidra: void FUN_000867ec(void) — empty body.
 * Confidence: high */
void cL4_noop_c(void) { }

/* FUN_000867fc @ 0x867fc   (est. cL4_method_thunk_fetch)
 * Ghidra: undefined1 [16] FUN_000867fc(void)
 * Fetch the method words at x22+0x18/+0x20, decode the +0x20 method pointer,
 * and return the 16-byte pair {lo,hi} built from the fetched words.
 * Confidence: low */
cl4_ret16_t cL4_method_thunk_fetch(void)
{
    word_t w20 = *(word_t *)(uintptr_t)0x20;
    cl4_ret16_t fetched = *(cl4_ret16_t *)(uintptr_t)0x18;
    FUN_0006a4c0((void *)0, 0);
    cL4_decode_method_ptr(w20);
    return fetched;
}

/* FUN_00086834 @ 0x86834   (est. cL4_dispatch_cur)
 * Ghidra: void FUN_00086834(void)
 * Invoke the indirect method stored in the current arg block (x20+0x18)
 * on the object at x20+0x10.
 * Confidence: medium */
void cL4_dispatch_cur(void)
{
    cL4_indirect_jump_8(*(word_t *)(uintptr_t)0x10, *(word_t *)(uintptr_t)0x18, 0);
}

/* FUN_00086840 @ 0x86840   (est. cL4_noop_d)
 * Ghidra: void FUN_00086840(void) — empty body.
 * Confidence: high */
void cL4_noop_d(void) { }

/* FUN_0008684c @ 0x8684c   (est. cL4_syscall_anchor)
 * Ghidra: undefined1 * FUN_0008684c(void)
 * Return the address of the stack slot at +8 — the syscall anchor/scratch
 * pointer used by the dispatch tail-calls.
 * Confidence: low */
void *cL4_syscall_anchor(void) { return (void *)(uintptr_t)8; }

/* FUN_00086860 @ 0x86860   (est. cL4_noop_e)
 * Ghidra: void FUN_00086860(void) — empty body.
 * Confidence: high */
void cL4_noop_e(void) { }

/* FUN_00086874 @ 0x86874   (est. cL4_obj_method_58)
 * Ghidra: void FUN_00086874(undefined8 *param_1, undefined8 *param_2)
 * Call the object's +0x58 vtable method, retaining *param_1 first.
 * Confidence: low */
void cL4_obj_method_58(word_t *a, word_t *b)
{
    void (*fn)(void) = (void (*)(void))(*(word_t *)(*(word_t *)*b + 0x58));
    thunk_FUN_0036b270((void *)*a);
    fn();
}

/* FUN_000868c8 @ 0x868c8   (est. cL4_node_method_58)
 * Ghidra: void FUN_000868c8(void)
 * Reset the node at x20+0x10 (FUN_00084100) and retain it.
 * Confidence: low */
void cL4_node_method_58(void)
{
    FUN_00084100((void *)(uintptr_t)0x10);
    thunk_FUN_0036b270((void *)(*(word_t *)(uintptr_t)0x10));
}

/* FUN_000868f4 @ 0x868f4   (est. cL4_node_replace)
 * Ghidra: void FUN_000868f4(undefined8 param_1)
 * Replace the node at x20+0x10: reset, stash the old value, install param_1,
 * release the old.
 * Confidence: low */
void cL4_node_replace(word_t val)
{
    FUN_0008e3b0((void *)(uintptr_t)0x10);
    word_t old = *(word_t *)(uintptr_t)0x10;
    *(word_t *)(uintptr_t)0x10 = val;
    FUN_0036b118((void *)old);
}

/* FUN_00086930 @ 0x86930   (est. cL4_node_pair_30)
 * Ghidra: undefined1 [16] FUN_00086930(undefined8 param_1)
 * Begin a node at x20+0x10 with value param_1; return {lo=&DAT_0007bf58, hi=node}.
 * Confidence: low */
cl4_ret16_t cL4_node_pair_30(word_t val)
{
    FUN_0008e3a4((void *)(uintptr_t)0x10, (void*)val);
    return (cl4_ret16_t){ .hi = (word_t)(uintptr_t)0x10, .lo = (word_t)(uintptr_t)0x7bf58 };
}

/* FUN_00086978 @ 0x86978   (est. cL4_obj_method_70)
 * Ghidra: void FUN_00086978(undefined8 *param_1, undefined8 *param_2)
 * Call the object's +0x70 vtable method, retaining *param_1.
 * Confidence: low */
void cL4_obj_method_70(word_t *a, word_t *b)
{
    void (*fn)(void) = (void (*)(void))(*(word_t *)(*(word_t *)*b + 0x70));
    thunk_FUN_0036b270((void *)*a);
    fn();
}

/* FUN_000869cc @ 0x869cc   (est. cL4_node18_method_70)
 * Ghidra: void FUN_000869cc(void)
 * Reset the node at x20+0x18 and retain it.
 * Confidence: low */
void cL4_node18_method_70(void)
{
    FUN_00084100((void *)(uintptr_t)0x18);
    thunk_FUN_0036b270((void *)(*(word_t *)(uintptr_t)0x18));
}

/* FUN_000869f8 @ 0x869f8   (est. cL4_node18_replace)
 * Ghidra: void FUN_000869f8(undefined8 param_1)
 * Replace the node at x20+0x18 with param_1, releasing the old value.
 * Confidence: low */
void cL4_node18_replace(word_t val)
{
    FUN_0008e3b0((void *)(uintptr_t)0x18);
    word_t old = *(word_t *)(uintptr_t)0x18;
    *(word_t *)(uintptr_t)0x18 = val;
    FUN_0036b118((void *)old);
}

/* FUN_00086a34 @ 0x86a34   (est. cL4_node18_pair)
 * Ghidra: undefined1 [16] FUN_00086a34(undefined8 param_1)
 * Begin a node at x20+0x18 with value param_1; return {lo=&LAB_0006f910, hi=node}.
 * Confidence: low */
cl4_ret16_t cL4_node18_pair(word_t val)
{
    FUN_0008e3a4((void *)(uintptr_t)0x18, (void*)val);
    return (cl4_ret16_t){ .hi = (word_t)(uintptr_t)0x18, .lo = (word_t)(uintptr_t)0x6f910 };
}

/* FUN_00086a7c @ 0x86a7c   (est. cL4_obj_method_88)
 * Ghidra: void FUN_00086a7c(undefined8 *param_1, undefined8 *param_2)
 * Call the object's +0x88 vtable method, retaining *param_1.
 * Confidence: low */
void cL4_obj_method_88(word_t *a, word_t *b)
{
    void (*fn)(void) = (void (*)(void))(*(word_t *)(*(word_t *)*b + 0x88));
    thunk_FUN_0036b270((void *)*a);
    fn();
}

/* FUN_00086ad0 @ 0x86ad0   (est. cL4_node20_method)
 * Ghidra: void FUN_00086ad0(void)
 * Reset the node at x20+0x20 and retain it.
 * Confidence: low */
void cL4_node20_method(void)
{
    FUN_00084100((void *)(uintptr_t)0x20);
    thunk_FUN_0036b270((void *)(*(word_t *)(uintptr_t)0x20));
}

/* FUN_00086afc @ 0x86afc   (est. cL4_node20_replace)
 * Ghidra: void FUN_00086afc(undefined8 param_1)
 * Replace the node at x20+0x20 with param_1, releasing the old value.
 * Confidence: low */
void cL4_node20_replace(word_t val)
{
    FUN_0008e3b0((void *)(uintptr_t)0x20);
    word_t old = *(word_t *)(uintptr_t)0x20;
    *(word_t *)(uintptr_t)0x20 = val;
    FUN_0036b118((void *)old);
}

/* FUN_00086b38 @ 0x86b38   (est. cL4_node20_pair)
 * Ghidra: undefined1 [16] FUN_00086b38(undefined8 param_1)
 * Begin a node at x20+0x20 with value param_1; return {lo=&DAT_0007bf58, hi=node}.
 * Confidence: low */
cl4_ret16_t cL4_node20_pair(word_t val)
{
    FUN_0008e3a4((void *)(uintptr_t)0x20, (void*)val);
    return (cl4_ret16_t){ .hi = (word_t)(uintptr_t)0x20, .lo = (word_t)(uintptr_t)0x7bf58 };
}

/* FUN_00086b80 @ 0x86b80   (est. cL4_edge_push)
 * Ghidra: void FUN_00086b80(undefined8 param_1, undefined8 param_2)
 * Push an (edge,dst) pair onto the current node's edge list: grow the edge
 * array at +0x10 by one 16-byte element, store the two words at the new
 * slot, retain param_1, and finalize the list.
 * Confidence: low
 * Notes: node struct with count at +0x10, elements 0x10 bytes at +0x20. */
void cL4_edge_push(word_t edge, word_t dst)
{
    cl4_ret16_t node = (**(cl4_ret16_t (**)(void *))(*(word_t *)(uintptr_t)0 + 0x90))((void*)(uintptr_t)0);
    FUN_0007b208();
    word_t count = *(word_t *)(*((word_t*)(uintptr_t)node.hi) + 0x10);
    FUN_0007b3e4(count);
    word_t base = *((word_t*)(uintptr_t)node.hi);
    *(word_t *)(base + 0x10) = count + 1;
    word_t slot = base + count * 0x10;
    *(word_t *)(slot + 0x20) = edge;
    *(word_t *)(slot + 0x28) = dst;
    thunk_FUN_0036b270((void *)edge);
    (*(void (**)(void*, word_t))node.lo)((void*)(uintptr_t)0, 0);
}

/* FUN_00086c2c @ 0x86c2c   (est. cL4_dump_edges)
 * Ghidra: void FUN_00086c2c(uint param_1, long param_2)
 * Walk and dump the edge list of the current node. If the edge bit is clear
 * (param_1&1==0) each edge cap is copied via the +0x18/+0x20 method pair and
 * re-published into a fresh node; if set, each edge is resolved to a named
 * cap (FUN_0008dae4) and, on failure, a fatal "add" error is raised. The
 * collected result node is then appended into a working list (via FUN_00077070)
 * and the param_1&1==0 tail appends each cap word. Finally a summary is pushed
 * through the +0x68/+0x60/+0x78/+0x88 vtable methods.
 * Confidence: low
 * Notes: huge multi-branch routine; edges node count at +0x10; error words
 *   0xd000000000000015/0x80000000005c0560 ("add"); unreachable blocks pruned. */
void cL4_dump_edges(unsigned int flags, word_t param2)
{
    /* Fetch the current node's edge list via the +0x80 vtable method. */
    word_t node = (**(word_t (**)(void))(*(word_t *)(uintptr_t)0 + 0x80))();
    word_t n = *(word_t *)(node + 0x10);
    void *result = (void *)0x657778;
    if (n == 0) {
        FUN_0036b118((void *)node);
        result = (void *)0x657778;
    } else {
        FUN_000824a4(0, n, 0);
        word_t i = 0;
        word_t *src = (word_t *)(node + 0x28);
        result = (void *)0x657778;
        do {
            if (*(word_t *)(node + 0x10) <= i) { SoftwareBreakpoint(1, 0x87098); }
            word_t *ep = (word_t *)src[-1];
            word_t ep_v0 = *src;
            word_t ep0 = *ep;
            (void)ep0;
            if ((flags & 1) == 0) {
                /* Copy the edge cap via the object's +0x18/+0x20 method pair
                 * and re-publish it into the fresh result node (FUN_0008db28). */
                word_t m0 = *(word_t *)(param2 + 0x18);
                word_t m1 = *(word_t *)(param2 + 0x20);
                FUN_0006a4c0((void *)param2, m0);
                cL4_decode_method_ptr(m1);
                thunk_FUN_0036b270((void *)ep);
                FUN_0008db28(ep_v0);   /* publish edge (register-indirect in source) */
            } else {
                /* Resolve the edge to a named cap; on failure raise a fatal
                 * "add" diagnostic. */
                cl4_ret16_t got = FUN_0008dae4(ep, ep_v0, (void *)0x607494);
                if (got.lo == 0) {
                    thunk_FUN_0036b270((void *)ep);
                    FUN_002a4ab4(0x17);
                    thunk_FUN_002acbb8(0xd000000000000015ull, 0x80000000005c0560ull);
                    word_t ep2 = *ep;
                    word_t obj = (word_t)(uintptr_t)ep;
                    word_t nm = FUN_00027754(ep_v0);
                    FUN_001bac44(&obj, ep2, nm);
                    FUN_0008df14((const char *)0);
                    FUN_0008dfbc();
                    FUN_001afa84(0, 0, 0);   /* noreturn */
                }
                word_t key = got.lo;
                word_t m0 = *(word_t *)(param2 + 0x18);
                word_t m1 = *(word_t *)(param2 + 0x20);
                FUN_0006a4c0((void *)param2, m0);
                cL4_decode_method_ptr(m1);
                FUN_0036b2d0((void *)ep, 2);
                FUN_0008db28(got.hi);   /* publish resolved edge */
                FUN_0036b118((void *)key);
            }
            FUN_0036b118((void *)0);
            FUN_0036b118((void *)ep);
            /* append the (lo,hi) result pair into the growing result node */
            word_t cnt = *(word_t *)(result + 0x10);
            if (*(word_t *)(result + 0x18) >> 1 <= cnt) {
                FUN_000824a4(1 < *(word_t *)(result + 0x18), cnt + 1, 1);
            }
            i = i + 1;
            *(word_t *)(result + 0x10) = cnt + 1;
            FUN_00077070(&(word_t){0}, (void *)(result + cnt * 0x28 + 0x20));
            src += 2;
        } while (n != i);
        word_t nn = *(word_t *)(node + 0x10);
        FUN_0036b118((void *)node);
        if (n != nn) { SoftwareBreakpoint(1, 0x86e88); }
    }
    /* Push the result through the +0x78/+0x68/+0x60/+0x88 vtable methods. */
    (**(void (**)(void *))(*(word_t *)(uintptr_t)0 + 0x78))((void *)(uintptr_t)0);
    FUN_00080edc(result);
    (**(void (**)(void *, word_t))(*(word_t *)(uintptr_t)0 + 0x78))((void *)(uintptr_t)0, 0);
    word_t list = (**(word_t (**)(void))(*(word_t *)(uintptr_t)0 + 0x68))();
    word_t cnt = *(word_t *)(list + 0x10);
    if (cnt != 0) {
        word_t src = list + 0x20;
        do {
            FUN_0006e7c0((void *)src, (void *)(uintptr_t)0);
            FUN_00077070((void *)(uintptr_t)0, (void *)(uintptr_t)0);
            word_t v1 = (word_t)(uintptr_t)0, v0 = 0;
            FUN_0006a4c0((void *)0, v0);
            word_t v = FUN_0008db28__dispatch(v0, v1);
            if (((v ^ ~0ull) & 0xf000000000000007ull) != 0) {
                word_t arr = (**(word_t (**)(void *))(*(word_t *)(uintptr_t)0 + 0x60))((void *)(uintptr_t)0);
                word_t base = *(word_t *)(arr);
                word_t c0 = FUN_003a261c((void *)base);
                if ((c0 & 1) == 0) { base = FUN_00073498(0, *(word_t *)(base + 0x10) + 1, 1, base); }
                word_t cc = *(word_t *)(base + 0x10);
                if (*(word_t *)(base + 0x18) >> 1 <= cc) {
                    base = FUN_00073498(1 < *(word_t *)(base + 0x18), cc + 1, 1, base);
                }
                *(word_t *)(base + 0x10) = cc + 1;
                *(word_t *)(base + cc * 8 + 0x20) = v;
                (*(void (**)(void *, void *, word_t))arr)((void *)(uintptr_t)0, (void *)(uintptr_t)0, 0);
                FUN_0008dacc(v);
            }
            FUN_000026e8((void *)(uintptr_t)0);
            src += 0x28;
            cnt -= 1;
        } while (cnt != 0);
    }
    FUN_0036b118((void *)list);
    if ((flags & 1) == 0) {
        (**(void (**)(void *))(*(word_t *)(uintptr_t)0 + 0x88))((void *)0x657778);
    }
}

/* ================================================================== *
 * 0x87150 — 0x87600 : node lifecycle + integer parsing
 * ================================================================== */

/* FUN_00087150 @ 0x87150   (est. cL4_node_release3)
 * Ghidra: void FUN_00087150(void)
 * Release the three node values at x20+0x10/+0x18/+0x20.
 * Confidence: high */
void cL4_node_release3(void)
{
    FUN_0036b118((void *)(*(word_t *)(uintptr_t)0x10));
    FUN_0036b118((void *)(*(word_t *)(uintptr_t)0x18));
    FUN_0036b118((void *)(*(word_t *)(uintptr_t)0x20));
}

/* FUN_00087180 @ 0x87180   (est. cL4_node_destroy_a)
 * Ghidra: void FUN_00087180(void)
 * Release the three node values then run the teardown (FUN_0036b6ac).
 * Confidence: high */
void cL4_node_destroy_a(void) { cL4_node_release3(); FUN_0036b6ac(0); }

/* FUN_00087184 @ 0x87184   (est. cL4_node_destroy_b)
 * Ghidra: void FUN_00087184(void)
 * Same as cL4_node_destroy_a (second copy).
 * Confidence: high */
void cL4_node_destroy_b(void) { cL4_node_release3(); FUN_0036b6ac(0); }

/* FUN_000871a8 @ 0x871a8   (est. cL4_node_init3)
 * Ghidra: void FUN_000871a8(void)
 * Fetch a context object and point its three node slots (+0x10/18/20) at the
 * empty-node sentinel 0x657778.
 * Confidence: high */
void cL4_node_init3(void)
{
    word_t ctx = FUN_0006ce60();
    *(word_t *)(ctx + 0x10) = 0x657778;
    *(word_t *)(ctx + 0x18) = 0x657778;
    *(word_t *)(ctx + 0x20) = 0x657778;
}

/* FUN_000871ac @ 0x871ac   (est. cL4_node_init3_b)
 * Ghidra: void FUN_000871ac(void)
 * Same as cL4_node_init3 (second copy).
 * Confidence: high */
void cL4_node_init3_b(void)
{
    word_t ctx = FUN_0006ce60();
    *(word_t *)(ctx + 0x10) = 0x657778;
    *(word_t *)(ctx + 0x18) = 0x657778;
    *(word_t *)(ctx + 0x20) = 0x657778;
}

/* FUN_000871dc @ 0x871dc   (est. cL4_node_init3_c)
 * Ghidra: void FUN_000871dc(void)
 * Point the current node's three slots at the empty-node sentinel.
 * Confidence: high */
void cL4_node_init3_c(void)
{
    *(word_t *)(uintptr_t)0x10 = 0x657778;
    *(word_t *)(uintptr_t)0x18 = 0x657778;
    *(word_t *)(uintptr_t)0x20 = 0x657778;
}

/* FUN_000871f4 @ 0x871f4   (est. cL4_alloc_init_node)
 * Ghidra: undefined8 FUN_000871f4(undefined8 param_1)
 * Allocate a context object (FUN_0036a940 token) and initialize its node
 * from param_1 via FUN_00087234; return the token.
 * Confidence: low */
word_t cL4_alloc_init_node(word_t param1)
{
    word_t token = FUN_0006ce60();
    cL4_node_ctor(param1);
    return token;
}

/* FUN_00087234 @ 0x87234   (est. cL4_node_ctor)
 * Ghidra: void FUN_00087234(undefined8 param_1)
 * Construct a DER component node: create the node record via
 * FUN_001f0130(&0x657778, 0x667910, 0x677830, 0x667880), store it at
 * x20+0x10, set +0x40 to the empty sentinel, and append param_1 to the node
 * at x20+0x18.
 * Confidence: low */
void cL4_node_ctor(word_t param1)
{
    word_t node = FUN_001f0130((void *)0x657778, (void *)0x667910, (void *)0x677830, (void *)0x667880);
    *(word_t *)(uintptr_t)0x10 = node;
    *(word_t *)(uintptr_t)0x40 = 0x657778;
    FUN_00077070((void *)param1, (void *)(uintptr_t)0x18);
}

/* FUN_000872a8 @ 0x872a8   (est. cL4_node_teardown)
 * Ghidra: void FUN_000872a8(void)
 * Tear down the current node: enter a section on the list at x20+0x40, walk
 * each element calling its method (FUN_000770e8), release it (FUN_004b23d8),
 * release the node record, and finalize the arg block at x20+0x18.
 * Confidence: low */
void cL4_node_teardown(void)
{
    unsigned char blk[24], blk2[24];
    FUN_0036a1a0((void *)(uintptr_t)0x40, blk, 0, 0);
    word_t list = *(word_t *)(uintptr_t)0x40;
    word_t n = *(word_t *)(list + 0x10);
    if (n != 0) {
        thunk_FUN_0036b270((void *)list);
        word_t off = 0x20;
        do {
            word_t elem = *(word_t *)(list + off);
            FUN_0006e7c0((void *)(uintptr_t)0x18, blk2);
            word_t v0 = (word_t)(uintptr_t)0, v1 = 0;
            FUN_0006a4c0(blk2, v1);
            (**(void (**)(word_t, word_t, word_t))(*(word_t *)(0) + 0x30))(elem, v1, v0);
            FUN_000026e8(blk2);
            FUN_004b23d8(elem);
            off += 8;
            n -= 1;
        } while (n != 0);
        FUN_0036b118((void *)list);
    }
    FUN_003a25d4((void *)(*(word_t *)(uintptr_t)0x10));
    FUN_000026e8((void *)(uintptr_t)0x18);
    FUN_0036b118((void *)(*(word_t *)(uintptr_t)0x40));
}

/* FUN_00087398 @ 0x87398   (est. cL4_node_destroy_c)
 * Ghidra: void FUN_00087398(void)
 * Tear down the node then run the context teardown.
 * Confidence: low */
void cL4_node_destroy_c(void) { cL4_node_teardown(); FUN_0036b6ac(0); }

/* FUN_0008739c @ 0x8739c   (est. cL4_node_destroy_d)
 * Ghidra: void FUN_0008739c(void)
 * Same as cL4_node_destroy_c (second copy).
 * Confidence: low */
void cL4_node_destroy_d(void) { cL4_node_teardown(); FUN_0036b6ac(0); }

/* FUN_000873c0 @ 0x873c0   (est. cL4_parse_int_with_caps)
 * Ghidra: void FUN_000873c0(undefined8 param_1)
 * Parse an integer from a capability-encoded string: resolve the cap to its
 * string payload, decode sign/base (decimal/hex), and validate against the
 * caller's limit (param_4). On overflow or malformed digits it fatals with
 * "getOrAllocateComponentResourceCapFromEdge" context errors. A successful
 * parse builds an error via FUN_000fd198 (returning error 0/1 sentinel).
 * The decompiled body leaves the parsed value in x0 (void signature but the
 * value is consumed by callers).
 * Confidence: low
 * Notes: heavy inline decimal/hex digit loop; error words 0xd000000000000017/
 *   0x80000000005c08d0, 0xd00000000000001c/0x80000000005c08d0; FATAL via
 *   0x876b8 on parse error (auVar25 low-byte != 1). */
word_t cL4_parse_int_with_caps(word_t cap)
{
    word_t *node = (word_t *)FUN_00121598();
    word_t s0 = node[0];
    word_t s1 = node[1];
    FUN_0008e328();
    word_t node2 = (**(word_t (**)(void))(0 + 0xa0))();
    if (*(word_t *)(node2 + 0x10) == 0) { SoftwareBreakpoint(1, 0x876fc); }
    cl4_ret16_t got = FUN_0006ae9c(s0, s1);
    if ((got.hi & 1) == 0) { SoftwareBreakpoint(1, 0x876fc); }
    word_t *pair = (word_t *)(*(word_t *)(node2 + 0x38) + got.lo * 0x10);
    word_t v0 = pair[0];
    word_t v1 = pair[1];
    thunk_FUN_0036b270((void *)v1);
    FUN_003a25d4((void *)s1);
    FUN_003a25d4((void *)node2);
    FUN_0008e488(0, v0 & 0xffffffffffffull);
    /* ... faithful decimal/hex digit accumulation (see decompile) ... */
    FUN_003a25d4((void *)v1);
    SoftwareBreakpoint(1, 0x876b8);   /* parse-error path in this region */
}

/* ================================================================== *
 * 0x87700 — 0x8d1c4 : DER component-graph cap allocator
 * ================================================================== */

/* FUN_00087704 @ 0x87704   (est. getOrAllocateComponentResourceCapFromEdge)
 * Ghidra: void FUN_00087704(undefined8,undefined8,undefined8)
 * Allocate (or look up) a component-resource cap from a graph edge: retain
 * both payload words, log a "getOrAllocateComponentResourceCapFromEdge"
 * progress/error line, and on the failing branch raise a fatal error word
 * (0xd000000000000017/0x80000000005c08d0).
 * Confidence: medium
 * Notes: strings s_getOrAllocateComponentResourceCa_005c0910 (+0x20) and
 *   s_..._005c08d0; FATAL on error via FUN_001004f0. */
void getOrAllocateComponentResourceCapFromEdge(word_t a, word_t b, word_t c)
{
    thunk_FUN_0036b270((void *)b);
    thunk_FUN_0036b270((void *)c);
    FUN_0008e1e0(0x70);
    FUN_0008e154(0xd000000000000017ull, 0x80000000005c08d0ull);
    FUN_000fac98();
    if (0 /* x21 */ == 0) {
        FUN_0008e1e0(0);   /* "...ResourceCapFromEdge(edge:)" tail */
        FUN_0008e154(0xd00000000000001cull, (word_t)(0) | 0x8000000000000000ull);
        FUN_001004f0();
    }
}

/* FUN_000877e0 @ 0x877e0   (est. getOrAllocateCapFromEdge)
 * Ghidra: undefined8 FUN_000877e0(long *param_1)
 * The main "getOrAllocateCapFromEdge" routine. Verifies the edge kind is
 * 0x05 else fatal "Could not set ID on endpoint". Fetches the kernel thread
 * node and the component node, iterates the edge cap list, and either finds
 * an existing matching cap (returning it) or allocates a fresh one by
 * walking the parent's edge list and splicing it in. On any missing state it
 * breakpoints (panic).
 * Confidence: low
 * Notes: strings s_getOrAllocateCapFromEdge_edge___005c0d30 and
 *   s_InternalExclaveLauncher/.../prng.swift; error words 0xd000000000000020/
 *   0x80000000005c0ce0, 0xd00000000000002a/...; breaks at 0x87a64. */
word_t getOrAllocateCapFromEdge(word_t *edge)
{
    word_t err_lo = 0;
    void (*kind_fn)(void) = (void (*)(void))(*(word_t *)(*edge + 0x88));
    unsigned char kind = ((unsigned char (*)(void))kind_fn)();
    if (kind != 0x05) {
        word_t err_hi = 0xe000000000000000ull;
        FUN_002a4ab4(0x22);
        thunk_FUN_002acbb8(0xd000000000000020ull, 0x80000000005c0ce0ull);
        unsigned char k2 = ((unsigned char (*)(void))kind_fn)();
        FUN_00205844(&k2, &err_lo, (void*)0x6645c0, (void*)0x6756a8, (void*)0x66e1b8);
        (void)err_hi;
        FUN_0008df14((const char *)0);
        FUN_0008dfbc();
        FUN_001afa84(0,0,0);   /* noreturn */
    }
    (**(void (**)(void))(*(word_t *)(*edge + 0x70)))();
    FUN_0008e474();
    FUN_0008e1e0(0);
    FUN_0008e154(0xd00000000000002aull, (word_t)(0) | 0x8000000000000000ull);
    cl4_ret16_t thr = FUN_000a1558();
    word_t thr_hi = thr.hi;
    FUN_0036b118((void *)edge);
    word_t kt = FUN_00121498();
    word_t u7 = *(word_t *)(kt + 8);
    void (*m110)(void) = (void (*)(void))(*(word_t *)(*edge + 0x110));
    thunk_FUN_0036b270((void *)u7);
    FUN_0008e2c0();
    cl4_ret16_t comp = ((cl4_ret16_t (*)(void))m110)();
    word_t comp_hi = comp.hi;
    FUN_003a25d4((void *)u7);
    FUN_0036a1a0((void *)(uintptr_t)0x10, &err_lo, 0, 0);
    word_t node = *(word_t *)(uintptr_t)0x10;
    word_t edge_cap = 0;
    if (*(word_t *)(node + 0x10) != 0) {
        thunk_FUN_0036b270((void *)node);
        cl4_ret16_t e = FUN_0008e4ec();
        FUN_003a25d4((void *)node);
        if ((e.hi & 1) != 0) { edge_cap = 0; }
    }
    if (edge_cap != 0) {
        /* splice a fresh cap into the parent edge list (FUN_0007b1f0/0x7b324) */
        cl4_ret16_t scratch;
        FUN_0008e3a4((void *)(uintptr_t)0x40, &scratch);
        FUN_0007b1f0();
        word_t cnt = *(word_t *)(*(word_t *)(uintptr_t)0x40 + 0x10);
        FUN_0007b324(cnt);
        word_t base = *(word_t *)(uintptr_t)0x40;
        *(word_t *)(base + 0x10) = cnt + 1;
        *(word_t *)(base + cnt * 8 + 0x20) = edge_cap;
        *(word_t *)(uintptr_t)0x40 = base;
        FUN_0036a20c(&scratch);
    }
    word_t w0 = *(word_t *)(uintptr_t)0x30;
    word_t w1 = *(word_t *)(uintptr_t)0x38;
    FUN_0006a4c0((void *)(uintptr_t)0x18, w0);
    FUN_000f6dec(edge_cap, w0, w1, 0);
    cl4_ret16_t s2;
    FUN_0008e3a4((void *)(uintptr_t)0x10, &s2);
    FUN_00075ea4(edge_cap, thr.lo, thr_hi, comp.lo, comp_hi);
    FUN_0036a20c(&s2);
    /* re-scan the cap list for the freshly allocated cap */
    word_t node2 = *(word_t *)(uintptr_t)0x10;
    if (*(word_t *)(node2 + 0x10) != 0) {
        thunk_FUN_0036b270((void *)node2);
        cl4_ret16_t f = FUN_0008e4ec();
        if ((f.hi & 1) != 0) {
            word_t cap = *(word_t *)(*(word_t *)(node2 + 0x38) + f.lo * 8);
            FUN_003a25d4((void *)thr_hi);
            FUN_003a25d4((void *)node2);
            FUN_003a25d4((void *)comp_hi);
            return cap;
        }
        FUN_003a25d4((void *)thr_hi);
        thr_hi = (word_t)node2;
    }
    FUN_003a25d4((void *)thr_hi);
    FUN_003a25d4((void *)comp_hi);
    SoftwareBreakpoint(1, 0x87a64);   /* no cap found */
}

/* FUN_00087b20 @ 0x87b20   (est. cL4_resolve_named_cap)
 * Ghidra: undefined8 FUN_00087b20(long *param_1, long param_2)
 * Resolve a named component capability from a string identifier. Fetches the
 * kernel node, logs progress, compares the identifier against the canonical
 * component name (FUN_00121640). On mismatch or error it raises a fatal
 * "DER" diagnostic; on success returns the resolved cap value.
 * Confidence: low
 * Notes: strings s__AppleInternal_Library_BuildRoot_005c0610;
 *   error words 0xd000000000000035/0x80000000005c0be0, 0xd000000000000041/
 *   0x80000000005c0c90, 0xd000000000000034/0x80000000005c0c50, 0xd00000000000001a/
 *   0x80000000005c0bc0, 0xd000000000000025/0x80000000005c0b60; FATAL at 0x88088. */
word_t cL4_resolve_named_cap(word_t *param1, word_t param2)
{
    (**(void (**)(void))(*(word_t *)(*param1 + 0x58)))();
    FUN_0008e154(0xd000000000000025ull, 0x80000000005c0b60ull, "BuildRoot");
    cl4_ret16_t a = FUN_000a1558();
    word_t a_hi = a.hi;
    FUN_0036b118((void *)0);
    FUN_0008e328();
    (**(void (**)(void))(0 + 0x70))();
    FUN_0008e474();
    FUN_0008e154(0xd00000000000002aull, (word_t)(0) | 0x8000000000000000ull, "BuildRoot");
    cl4_ret16_t b = FUN_000a1558();
    word_t b_hi = b.hi;
    word_t b_lo = b.lo;
    FUN_0036b118((void *)param1);
    word_t kt = FUN_00121468();
    word_t u1 = *(word_t *)(kt + 8);
    thunk_FUN_0036b270((void *)u1);
    FUN_0008e388();
    cl4_ret16_t c = FUN_000ab1fc(0, 0);
    word_t c_hi = c.hi;
    FUN_003a25d4((void *)u1);
    word_t kt2 = FUN_00121540();
    u1 = *(word_t *)(kt2 + 8);
    thunk_FUN_0036b270((void *)u1);
    FUN_0008e388();
    cL4_lookup_current_comp(0,0);
    FUN_003a25d4((void *)u1);
    word_t kt3 = FUN_00121510();
    u1 = *(word_t *)(kt3 + 8);
    thunk_FUN_0036b270((void *)u1);
    FUN_0008e388();
    cl4_ret16_t d = cL4_lookup_current_comp(0,0);
    FUN_003a25d4((void *)u1);
    FUN_0008e058((void *)(*param1 + 0x110));
    /* canonical-name comparison + fatal on mismatch */
    word_t canon = FUN_00121640();
    word_t match;
    if (b.lo == canon) { match = 1; }
    else { match = FUN_002a0cf8(b_lo, b_hi, *(word_t *)canon, *(word_t *)(canon + 8), 0); }
    if ((match & 1) != 0) {
        FUN_003a25d4((void *)a_hi);
        FUN_003a25d4((void *)b_hi);
        FUN_003a25d4((void *)c_hi);
        return d.lo;
    }
    if (param2 != 0) {
        FUN_001000b8(0);
        return FUN_000fd854(param2);
    }
    word_t v = cL4_parse_int_with_caps((word_t)param1);
    if (0 /* x21 */ != 0) {
        FUN_003a25d4((void *)b_hi);
        FUN_003a25d4((void *)c_hi);
        FUN_003a25d4((void *)a_hi);
        return 0;
    }
    return v;
}

/* FUN_0008809c @ 0x8809c   (est. cL4_lookup_current_comp)
 * Ghidra: undefined1 [16] FUN_0008809c(undefined8,undefined8)
 * Look up the current component record via the object's +0x110 method; if
 * found, copy it (FUN_0008c8b4) and release. Returns {lo=record, hi=found?}.
 * Confidence: low */
cl4_ret16_t cL4_lookup_current_comp(word_t a, word_t b)
{
    word_t rec = 0;
    cl4_ret16_t got = (**(cl4_ret16_t (**)(void))(*(word_t *)(uintptr_t)0 + 0x110))();
    word_t hi = got.hi;
    if (hi == 0) {
        rec = 0;
    } else {
        cL4_parse_string_int(&rec, (unsigned long *)&got, a, b);
        FUN_003a25d4((void *)hi);
    }
    return (cl4_ret16_t){ .hi = (word_t)(hi == 0), .lo = rec };
}

/* FUN_00088134 @ 0x88134   (est. cL4_component_alloc_resource)
 * Ghidra: void FUN_00088134(long *param_1, long *param_2)
 * Allocate a component resource: fetch the current component and its
 * untyped/MTE info, resolve the resource-type string, then build the
 * appropriate cap (via FUN_000877e0 / FUN_00087b20) and push it through the
 * caller's dispatch method (+0x98). Handles both the fresh-alloc and
 * existing-cap paths and reports memory/MTE diagnostics.
 * Confidence: low
 * Notes: strings s_Untyped_with_no_permissions_005c05a0,
 *   s_MTE_untyped_info_is_NULL_005c0710; error words 0xd00000000000003b/
 *   0x80000000005c0770; FATAL at 0x886f4/0x886ac. */
void cL4_component_alloc_resource(word_t *param1, word_t *param2)
{
    void (*m108)(void) = (void (*)(void))(*(word_t *)(*param1 + 0x108));
    word_t comp = ((word_t (*)(void))m108)();
    word_t *node = (word_t *)FUN_00121468();
    word_t n0 = node[0];
    word_t n1 = node[1];
    void (*m110)(void) = (void (*)(void))(*(word_t *)(*param1 + 0x110));
    thunk_FUN_0036b270((void *)n1);
    ((void (*)(word_t, word_t))m110)(n0, n1);
    FUN_003a25d4((void *)n1);
    word_t idx = cL4_lookup_resource_idx();
    if (idx != 0) { idx = FUN_00050654(idx, comp); }
    word_t kt = FUN_001215e0();
    word_t u = *(word_t *)(kt + 8);
    thunk_FUN_0036b270((void *)u);
    FUN_0008e2c0();
    ((void (*)(void))m110)();
    FUN_003a25d4((void *)u);
    word_t kind = 0;
    if (0 /* extraout_x1_00 */ == 0) {
        word_t kt2 = FUN_00121610();
        u = *(word_t *)(kt2 + 8);
        thunk_FUN_0036b270((void *)u);
        FUN_0008e2c0();
        ((void (*)(void))m110)();
        FUN_003a25d4((void *)u);
        if (0 /* extraout_x1_01 */ != 0) {
            kind = 2;
        } else {
            kind = 0;
        }
    } else {
        kind = 1;
    }
    if (idx != 0) {
        ((void (*)(void))m108)();
        word_t p = FUN_0008e358();
        cL4_resolve_named_cap(&p, idx);
        FUN_0008e210();
        word_t q = FUN_000a9b10(0);
        FUN_0036a940((word_t)q, 0x131, 7);
        FUN_0008e118();
        FUN_000a8cbc();
        goto done;
    }
    /* untyped-with-no-permissions path */
    word_t untyped = 0;
    /* ... faithful resource-type string parse + cap alloc (see decompile) ... */
done:
    (**(void (**)(word_t, word_t))(*(word_t *)(*param2 + 0x98)))(0, 0x660820);
    FUN_0008e3ec();
}

/* FUN_00088734 @ 0x88734   (est. cL4_lookup_resource_idx)
 * Ghidra: void FUN_00088734(void)
 * Look up the resource index: probe the current context (FUN_0004fe80) and,
 * if present, fetch a value via FUN_00050838; otherwise return 0. Uses a
 * stack-canary-style check on local_18 to catch corruption (panic 0x11d7e8).
 * Confidence: low */
word_t cL4_lookup_resource_idx(void)
{
    word_t out = 0;
    word_t a = 0, b = 0, c = 0;
    if (FUN_0004fe80() != 0) {
        if (FUN_00050838(&a, &b, &c) == 0) { out = c; }
    }
    return out;
}

/* FUN_000887b0 @ 0x887b0   (est. cL4_component_state_check)
 * Ghidra: void FUN_000887b0(void)
 * Validate the component graph state against a "diqri" string key: parse
 * the key as a signed/unsigned integer with an optional sign, and on parse
 * error raise a fatal diagnostic. Used as a precondition for later alloc.
 * Confidence: low
 * Notes: FUN_000ab1fc(0x64695f717269,...) builds "iqid_"-prefixed key; FATAL
 *   at 0x88a7c. */
void cL4_component_state_check(void)
{
    unsigned char blk[40];
    FUN_0006e7c0((void *)(uintptr_t)0x18, blk);
    cl4_ret16_t key = FUN_000ab1fc(0x64695f717269ull, 0xe600000000000000ull);
    word_t key_hi = key.hi;
    FUN_0008e488(key.lo, key.lo & 0xffffffffffffull);
    word_t len = 0;
    /* faithful signed/unsigned digit parse (see decompile) */
    FUN_003a25d4((void *)key_hi);
    if (0 /* parse-ok */) {
        FUN_000e79d8(0);
        FUN_00002834();
        FUN_0036a940((word_t)0, 0, 0);
        FUN_000e7614(blk, 0);
        FUN_0008e1a0();
        (**(void (**)(void))(0 + 0x98))();
        FUN_0008e1d4();
        (**(void (**)(void))(0 + 0x98))();
        FUN_0008e3ec();
        return;
    }
    SoftwareBreakpoint(1, 0x88a7c);   /* parse failed */
}

/* FUN_00088abc @ 0x88abc   (est. cL4_log_components)
 * Ghidra: void FUN_00088abc(undefined8,undefined8,undefined8,undefined8,undefined8,long,long*)
 * Log a batch of component (name,arg) pairs: build two log records from the
 * first two pairs, then iterate a list of 32-bit component ids (param_6+0x38)
 * emitting a line per id, then log a trailer. Each record is pushed through
 * the caller's +0x98 dispatch method.
 * Confidence: low */
void cL4_log_components(word_t a, word_t b, word_t c, word_t d, word_t e,
                        word_t list, word_t *dispatch)
{
    FUN_000f6d10(0);
    FUN_00002834();
    word_t rec = FUN_0006ce60();
    *(word_t *)(rec + 0x10) = b;
    *(word_t *)(rec + 0x18) = c;
    void (*m98)(void) = (void (*)(void))(*(word_t *)(*dispatch + 0x98));
    FUN_0008e1d4();
    ((void (*)(void))m98)();
    FUN_0036b118((void *)rec);
    FUN_00084c9c(0);
    FUN_00002834();
    rec = FUN_0006ce60();
    *(word_t *)(rec + 0x10) = d;
    *(word_t *)(rec + 0x18) = e;
    ((void (*)(word_t*, word_t))m98)((word_t*)rec, 0x65f960);
    FUN_0036b118((void *)rec);
    unsigned int *ids = (unsigned int *)(list + 0x38);
    for (word_t i = *(word_t *)(list + 0x10); i != 0; i -= 1) {
        unsigned int id = *ids;
        unsigned char blk[24];
        FUN_0006e7c0((void *)(uintptr_t)0x18, blk);
        word_t opt = FUN_000ab3e4();
        word_t v = FUN_00101f08(0);
        v = FUN_0036a940((word_t)v, 0x48, 7);
        v = FUN_0010196c(blk, id, opt & 1, v);
        FUN_0008e1d4();
        ((void (*)(void))m98)();
        FUN_0036b118((void *)v);
        ids += 8;
    }
    word_t v2 = FUN_000e884c(0);
    FUN_0036a940((word_t)v2, 0x18, 7);
    v2 = FUN_000e8528(0);
    thunk_FUN_0036b270((void *)v2);
    FUN_0008e02c();
    ((void (*)(void))m98)();
    FUN_0036b118((void *)v2);
    FUN_0036b118((void *)v2);
}

/* FUN_00088ca8 @ 0x88ca8   (est. cL4_build_phys_info)
 * Ghidra: void FUN_00088ca8(undefined8 param_1)
 * Build the physical-memory info block for the component: gather the managed
 * phys base / ranges via FUN_0006cfXX helpers, enumerate the node entries
 * (FUN_00088ee0), validate the counts, and copy the 0x60-byte struct into
 * param_1. Panics on malformed "Managed_Phys_Base_is" state.
 * Confidence: low
 * Notes: s_Managed_Phys_Base_is_005c0ae0; SoftwareBreakpoint sites 0x88e90-0x88ea0. */
void cL4_build_phys_info(word_t out)
{
    word_t u2 = FUN_0006cfe4();
    FUN_0006d4b4();
    word_t v = FUN_0006d45c();
    if (v < 0) { SoftwareBreakpoint(1, 0x88e90); }
    v = FUN_0006d150(u2);
    word_t u4 = FUN_0006ce60();
    FUN_0006ce60();
    word_t u5 = cL4_enum_nodes((word_t (*)(word_t))FUN_0006ce80);
    if (v < 0) { SoftwareBreakpoint(1, 0x88e94); }
    word_t mode = FUN_0005526c();
    word_t u7, u11, l6;
    if (mode == 2) {
        u7 = FUN_0008df38();
        u11 = 0;
        l6 = 0;
    } else {
        l6 = FUN_0006cec8(0x11);
        if (l6 == 0) {
            FUN_001afa84("Managed_Phys_Base_is", 0xb, 2,
                         0xd00000000000003cull, 0x8000000000000000ull, 0, 0x2d, 2, 0x1a0, 0);
        }
        u7 = cL4_enum_nodes((word_t (*)(word_t))FUN_0006cec8);
        u11 = u2;
        l6 = v;
    }
    word_t u8 = FUN_0006cf0c(0x11);
    word_t e0, d0, c8;
    if (u8 == 0) {
        e0 = FUN_0008df38();
        d0 = 0;
        c8 = 0;
    } else {
        e0 = cL4_enum_nodes((word_t (*)(word_t))FUN_0006cf0c);
        d0 = u2;
        c8 = v;
    }
    word_t blk[12];
    blk[0] = u5; blk[1] = u4; blk[2] = u2; blk[3] = v;
    blk[4] = u7; blk[5] = u11; blk[6] = l6; blk[7] = e0;
    blk[8] = d0; blk[9] = c8; blk[10] = 0; blk[11] = 0;
    unsigned char b2[0x60];
    FUN_00117cc4(b2, blk, 0x60);
    word_t token = FUN_00167a6c(0);
    FUN_0008deb0(blk, (void*)(uintptr_t)0);
    cL4_dump_node_debug(token, (word_t)(uintptr_t)b2);
    cl4_ret16_t got = cL4_build_comp_record();
    word_t hi = got.hi, lo = got.lo;
    word_t n = *(word_t *)(lo + 0x10);
    word_t delta = n - hi;
    if (delta != 0) {
        if (n < hi) { SoftwareBreakpoint(1, 0x88e98); }
        if (hi < 0) { SoftwareBreakpoint(1, 0x88e9c); }
        if (n == 0) { SoftwareBreakpoint(1, 0x88ea0); }
        unsigned char s[24];
        FUN_0008e3a4((void *)(uintptr_t)0x40, s);
        word_t *p = (word_t *)(lo + hi * 0x20);
        do {
            p += 4;
            thunk_FUN_0036b270((void *)*p);
            FUN_00080ef4();
            delta -= 1;
        } while (delta != 0);
        FUN_0036a20c(s);
    }
    FUN_0036b118((void *)lo);
    FUN_00117cc4((void *)out, blk, 0x60);
}

/* FUN_00088ee0 @ 0x88ee0   (est. cL4_enum_nodes)
 * Ghidra: long FUN_00088ee0(code *param_1)
 * Enumerate all nodes by calling param_1(i) for i in [0,0x1a); for each
 * non-null node, hash/record it in a bitfield at node+0x38 (setting bit i),
 * growing the bitfield as needed. Returns the node containing the bitfield.
 * Confidence: low
 * Notes: bound 0x1a (26) nodes; bitfield base node+0x38. */
word_t cL4_enum_nodes(word_t (*probe)(word_t))
{
    word_t node = FUN_0008df38();
    word_t i = 0;
    do {
        word_t v = probe(i);
        if (v != 0) {
            word_t cnt = *(word_t *)(node + 0x10);
            word_t slot = 0;
            if (cnt == 0) {
                /* grow + record bit i */
                if (*(word_t *)(node + 0x38) == 0) {
                    word_t bit = 1ull << (i & 0x3f);
                    *(word_t *)(*(word_t *)(node + 0x38) + slot * 8) = bit;
                }
            } else {
                word_t bit = 1ull << (i & 0x3f);
                word_t existing = *(word_t *)(*(word_t *)(node + 0x38) + slot * 8);
                *(word_t *)(*(word_t *)(node + 0x38) + slot * 8) = existing | bit;
            }
            *(word_t *)(node + 0x10) = 0;
        }
        i += 1;
        if (i == 0x1a) return node;
    } while (1);
}

/* FUN_00089070 @ 0x89070   (est. cL4_dump_node_debug)
 * Ghidra: void FUN_00089070(undefined8 param_1, undefined8 param_2)
 * If the verbose debug flag (DAT_006add10) is set, build a debug log line
 * "ALL UNTYPE..." describing the 0x60-byte node at param_2 and push it to the
 * console; otherwise just release the node (FUN_0008dbc0).
 * Confidence: medium
 * Notes: string words 0x59544e55204c4c41/0xef203a2053444550 ("ALL UNTY..."). */
void cL4_dump_node_debug(word_t a, word_t b)
{
    if (DAT_006add10 == 0x01) {
        word_t desc = FUN_00002534((word_t)0x64c040, (word_t)0x4bbf40);
        word_t obj = FUN_0036a9a0((word_t)desc, 0);
        word_t w0 = _DAT_004baeb0;
        *(word_t *)(obj + 0x18) = uRam00000000004baeb8;
        *(word_t *)(obj + 0x10) = w0;
        word_t lo = 0, hi = 0xe000000000000000ull;
        FUN_002a4ab4(0x11);
        thunk_FUN_002acbb8(0x59544e55204c4c41ull, 0xef203a2053444550ull);
        FUN_00117cc4(&lo, (void *)b, 0x60);
        FUN_00205844(&lo, &hi, (void*)0x65fbf0, (void*)0x6756a8, (void*)0x66e1b8);
        *(word_t *)(obj + 0x38) = 0x6753a0;
        *(word_t *)(obj + 0x20) = hi;
        *(word_t *)(obj + 0x28) = (word_t)(uintptr_t)0;
        FUN_0026b434(obj, 0x20, 0xe100000000000000ull, 10, 0xe100000000000000ull);
        FUN_0036b588((void *)obj);
        FUN_00002688();
        FUN_0036b6ac(0, 0x20, 7);
        FUN_0008dbc0((void *)b);
        return;
    }
    FUN_0008dbc0((void *)b);
}

/* FUN_000891d0 @ 0x891d0   (est. cL4_dump_node_named)
 * Ghidra: void FUN_000891d0(undefined8,undefined8,undefined8)
 * Verbose variant of the node dump: emit a log line carrying param_2 with a
 * name suffix (via FUN_000ab618) when the debug flag is set, then release
 * param_3.
 * Confidence: medium
 * Notes: error words 0xd000000000000034/0x80000000005c0b20. */
void cL4_dump_node_named(word_t a, word_t b, word_t c)
{
    if (DAT_006add10 == 0x01) {
        word_t desc = FUN_00002534((word_t)0x64c040, (word_t)0x4bbf40);
        word_t obj = FUN_0036a9a0((word_t)desc, 0);
        word_t w0 = _DAT_004baeb0;
        *(word_t *)(obj + 0x18) = uRam00000000004baeb8;
        *(word_t *)(obj + 0x10) = w0;
        word_t lo = 0, hi = 0xe000000000000000ull;
        FUN_002a4ab4(0x39);
        thunk_FUN_002acbb8(0xd000000000000034ull, 0x80000000005c0b20ull);
        word_t s = b;
        FUN_00205844(&s, &lo, (void*)0x666940, (void*)0x6756a8, (void*)0x66e1b8);
        thunk_FUN_002acbb8(0x20, 0xe100000000000000ull);
        word_t v = FUN_000ab618();
        FUN_00205844(&s, &lo, (void*)0x660c50, (void*)0x6756a8, (void*)0x66e1b8);
        *(word_t *)(obj + 0x38) = 0x6753a0;
        *(word_t *)(obj + 0x20) = lo;
        *(word_t *)(obj + 0x28) = hi;
        FUN_0026b434(obj, 0x20, 0xe100000000000000ull, 10, 0xe100000000000000ull);
        FUN_0036b588((void *)obj);
        FUN_00002688();
        FUN_0036b6ac(0, 0x20, 7);
        FUN_0036b118((void *)c);
        return;
    }
    FUN_0036b118((void *)c);
}

/* FUN_0008936c @ 0x8936c   (est. cL4_log_memory_usage)
 * Ghidra: void FUN_0008936c(void)
 * Verbose memory-usage log: emit a multi-line "used memory" accounting block
 * (two descriptor lines + a summary) when the debug flag is set.
 * Confidence: medium
 * Notes: string words 0x6753a0/0xd000000000000015/0x80000000005c0ac0; lines
 *   FUN_00027724(0x671848). */
void cL4_log_memory_usage(void)
{
    if (DAT_006add10 == 0x01) {
        word_t desc = FUN_00002534((word_t)0x64c040, (word_t)0x4bbf40);
        word_t obj = FUN_0036a9a0((word_t)desc, 0);
        word_t w0 = _DAT_004baeb0;
        *(word_t *)(obj + 0x18) = uRam00000000004baeb8;
        *(word_t *)(obj + 0x10) = w0;
        FUN_002a4ab4(0x1a);
        FUN_003a25d4((void *)0xe000000000000000ull);
        void (*emit)(word_t, word_t) = (void (*)(word_t, word_t))FUN_00027724(0x671848);
        emit(0x677790, 0x671848);
        thunk_FUN_002acbb8(0,0);
        FUN_003a25d4((void*)0);
        thunk_FUN_002acbb8(0x20, 0xe100000000000000ull);
        emit(0x677790, 0x671848);
        thunk_FUN_002acbb8(0,0);
        FUN_003a25d4((void*)0);
        *(word_t *)(obj + 0x38) = 0x6753a0;
        *(word_t *)(obj + 0x20) = 0xd000000000000015ull;
        *(word_t *)(obj + 0x28) = 0x80000000005c0ac0ull;
        FUN_0026b434(obj, 0x20, 0xe100000000000000ull, 10, 0xe100000000000000ull);
        FUN_0036b588((void *)obj);
        FUN_00002688();
        FUN_0036b6ac(0, 0x20, 7);
    }
}

/* FUN_00089504 @ 0x89504   (est. cL4_log_resource_type)
 * Ghidra: void FUN_00089504(undefined8 param_1, char param_2)
 * Verbose log of a resource-type name: param_2 selects the display string
 * (0="Shar ing", 1="Release n", else "All"), emitted with a status word.
 * Confidence: medium
 * Notes: little-endian string words 0x676e6972616853/0xe700000000000000 ("Shar",
 *   0=on), 0x6e697361656c6552/0xe900000000000067 ("Release"), 0x6c6c41/0xe3... ("All");
 *   error words 0xd000000000000015/0x80000000005c0970, 0xd000000000000037/0x80000000005c0990. */
void cL4_log_resource_type(word_t a, char kind)
{
    if (DAT_006add10 == 0x01) {
        word_t desc = FUN_00002534((word_t)0x64c040, (word_t)0x4bbf40);
        word_t obj = FUN_0036a9a0((word_t)desc, 0);
        word_t w0 = _DAT_004baeb0;
        *(word_t *)(obj + 0x18) = uRam00000000004baeb8;
        *(word_t *)(obj + 0x10) = w0;
        FUN_002a4ab4(0x4e);
        thunk_FUN_002acbb8(0xd000000000000015ull, 0x80000000005c0970ull);
        word_t s_lo, s_hi;
        if (kind == 0) { s_lo = 0xe700000000000000ull; s_hi = 0x676e6972616853ull; }
        else if (kind == 1) { s_lo = 0xe900000000000067ull; s_hi = 0x6e697361656c6552ull; }
        else { s_lo = 0xe300000000000000ull; s_hi = 0x6c6c41ull; }
        thunk_FUN_002acbb8(s_hi, s_lo);
        FUN_003a25d4((void *)s_lo);
        thunk_FUN_002acbb8(0xd000000000000037ull, 0x80000000005c0990ull);
        *(word_t *)(obj + 0x38) = 0x6753a0;
        *(word_t *)(obj + 0x20) = 0;
        *(word_t *)(obj + 0x28) = 0xe000000000000000ull;
        FUN_0026b434(obj, 0x20, 0xe100000000000000ull, 10, 0xe100000000000000ull);
        FUN_0036b588((void *)obj);
        FUN_00002688();
        FUN_0036b6ac(0, 0x20, 7);
    }
}

/* FUN_00089684 @ 0x89684   (est. cL4_build_comp_record)
 * Ghidra: undefined1 [16] FUN_00089684(void)
 * Build a fresh component-graph node record: allocate a 0x80-byte object,
 * copy the 12 words of the current node (x20[0..11]) into the record at the
 * standard offsets, and deep-copy the three node lists (FUN_0008db58). Returns
 * {lo=record, hi=0}.
 * Confidence: medium
 * Notes: node type words _DAT_004c0f00/uRam...4c0f08; three FUN_0008db58 copies. */
cl4_ret16_t cL4_build_comp_record(void)
{
    word_t desc = FUN_00002534((word_t)0x64f5a8, (word_t)0x4c0ff0);
    word_t rec = FUN_0036a940((word_t)desc, 0x80, 7);
    word_t w0 = _DAT_004c0f00;
    word_t s0 = *(word_t *)(uintptr_t)0x10;
    word_t s1 = *(word_t *)(uintptr_t)0x18;
    word_t s2 = *(word_t *)(uintptr_t)0x20;
    *(word_t *)(rec + 0x18) = uRam00000000004c0f08;
    *(word_t *)(rec + 0x10) = w0;
    *(word_t *)(rec + 0x28) = s0;
    *(word_t *)(rec + 0x20) = s1;
    word_t s8 = *(word_t *)(uintptr_t)0x48;
    word_t s9 = *(word_t *)(uintptr_t)0x40;
    word_t sa = *(word_t *)(uintptr_t)0x58;
    word_t sb = *(word_t *)(uintptr_t)0x50;
    *(word_t *)(rec + 0x68) = s9;
    *(word_t *)(rec + 0x60) = s8;
    *(word_t *)(rec + 0x78) = sa;
    *(word_t *)(rec + 0x70) = sb;
    word_t s4 = *(word_t *)(uintptr_t)0x28;
    word_t s5 = *(word_t *)(uintptr_t)0x20;
    word_t s6 = *(word_t *)(uintptr_t)0x38;
    word_t s7 = *(word_t *)(uintptr_t)0x30;
    *(word_t *)(rec + 0x38) = s4;
    *(word_t *)(rec + 0x30) = s5;
    *(word_t *)(rec + 0x48) = s6;
    *(word_t *)(rec + 0x40) = s7;
    *(word_t *)(rec + 0x58) = s2;
    *(word_t *)(rec + 0x50) = s2;
    FUN_0008db58((void *)&s1, (void *)(uintptr_t)0);
    FUN_0008db58((void *)&s7, (void *)(uintptr_t)0);
    FUN_0008db58((void *)&s8, (void *)(uintptr_t)0);
    return (cl4_ret16_t){ .lo = rec, .hi = 0 };
}

/* FUN_0008972c @ 0x8972c   (est. cL4_alloc_untyped_resources)
 * Ghidra: void FUN_0008972c(undefined8,undefined8,long)
 * Allocate the untyped resource ranges for a component: verify untyped has
 * permissions, gather phys-info (FUN_00088ca8), then walk the component's
 * edge lists (word-level at local_190 and 16-byte entries at local_170/150)
 * publishing each edge and MTE-untyped entry via the +0x1d8 vtable method,
 * then compute and validate the used-memory totals (must be 1 MiB aligned,
 * else fatal "DERComponentGraph used memory is..."). Ends by writing the
 * summary record via FUN_0008e500.
 * Confidence: low
 * Notes: strings s_Untyped_with_no_permissions_005c05a0,
 *   s_DERComponentGraph_used_memory_is_005c05c0, s_MTE_untyped_info_is_NULL_005c0710;
 *   error words 0x642073692045544d/0xef64656c62617369 ("MTE is ... disabled");
 *   bitset walks use bit-reversal; FATAL at 0x8a0c4. */
void cL4_alloc_untyped_resources(word_t a, word_t b, word_t c)
{
    cl4_ret16_t au = FUN_0008e518();
    word_t perm = FUN_000ab488();
    FUN_000ab618();
    cl4_ret16_t res = FUN_000ab678();
    word_t res_lo = res.lo;
    if ((res.hi & 0xff) == 1) {
        FUN_0008e2ec("Untyped with no permissions");
        FUN_0008df14((const char *)0);
        goto fatal;
    }
    word_t v = FUN_0006d45c();
    if (v < 0) { SoftwareBreakpoint(1, 0x8a008); }
    word_t u6 = FUN_00167a6c(0);
    thunk_FUN_0036b270((void *)au.lo);
    cL4_dump_node_named(u6, res_lo, au.lo);
    word_t u7 = FUN_0006cfe4();
    FUN_0006d150(0);
    FUN_0006cf50(u7);
    cL4_build_phys_info(0);
    if ((perm & 0xff) == 1) {
        thunk_FUN_0036b270((void*)0);
        FUN_0008dbc0((void*)0);
        word_t v8 = FUN_000ab71c();
        FUN_00157308(3);
        FUN_0008e544(c, *(word_t *)(c + 0x18));
        word_t *node = (word_t *)((word_t (*)(void))0)();
        word_t w = FUN_000ab8d8(v8);
        (**(void (**)(void *, word_t, word_t, word_t, word_t, word_t))(*node + 0x1d8))
            ((void*)0, 0, 0, w, 1, res_lo);
        FUN_0036b118((void *)node);
        word_t u8 = FUN_0001a1c8(0, 0x667160, 0x665f60, 0x667088, 0x665cd8);
        FUN_0008db90((void*)0);
        word_t v9 = FUN_0001a1c8(0);
        FUN_00157024(v9, res_lo, u8, 0x665f60, 0x665cd8);
        goto summary;
    }
    /* walk edge lists and MTE untyped entries (bitset scans), then totals */
    word_t mem_lo = 0, mem_hi = 0, total = 0;
    word_t sum = FUN_0006d240(0, 0) + mem_hi;
    cL4_log_memory_usage();
    word_t delta = total - mem_hi;
    if (delta < 0) { SoftwareBreakpoint(1, 0x8a010); }
    if ((delta & 0xfffff) != 0) {
        FUN_0008e2ec("DERComponentGraph used memory is");
        FUN_0008df14((const char *)0);
        goto fatal;
    }
    word_t mode = FUN_0005526c();
    word_t u14 = mem_hi;
    if (mode != 2) { u14 = delta; }
    word_t l12 = FUN_0006d698();
    word_t l5 = FUN_0006d6b8();
    if (l5 < 0) { SoftwareBreakpoint(1, 0x8a018); }
    if (l5 == 0) {
        FUN_0008db90((void*)0);
        if (l12 != 0) { l5 = l12; }
        else { l5 = 0; }
    } else {
        if (l12 == 0) { SoftwareBreakpoint(1, 0x8a01c); }
        FUN_0008db90((void*)0);
        l5 = l12 + l5;
    }
summary:
    /* write the summary record */
    FUN_0008e500(0);
    return;
fatal:
    FUN_0008dfbc();
    FUN_001afa84(0, 0, 0);   /* "used memory" / "no permissions" fatal */
}

/* FUN_0008a11c @ 0x8a11c   (est. cL4_diag_intro)
 * Ghidra: undefined1 [16] FUN_0008a11c(void)
 * Emit a diagnostic line "int mp..." (0x...6d70206f746e6920) with a status
 * word and return the error pair {lo=0xd000000000000027, hi=0x80000000005c0a30}.
 * Confidence: medium */
cl4_ret16_t cL4_diag_intro(void)
{
    FUN_002a4ab4(0x32);
    FUN_003a25d4((void *)0xe000000000000000ull);
    void (*emit)(word_t, word_t) = (void (*)(word_t, word_t))FUN_00027724(0x671848);
    emit(0x677790, 0x671848);
    thunk_FUN_002acbb8(0,0);
    FUN_003a25d4((void*)0);
    thunk_FUN_002acbb8(0x6d70206f746e6920ull, 0xe90000000000006dull);
    return (cl4_ret16_t){ .lo = 0xd000000000000027ull, .hi = 0x80000000005c0a30ull };
}

/* FUN_0008a1f0 @ 0x8a1f0   (est. cL4_diag_intro_b)
 * Ghidra: undefined1 [16] FUN_0008a1f0(void)
 * Diagnostic variant with error word 0xd00000000000002a/0x80000000005c0a60;
 * returns {lo=0xe000000000000000<<64}.
 * Confidence: medium */
cl4_ret16_t cL4_diag_intro_b(void)
{
    FUN_002a4ab4(0x35);
    thunk_FUN_002acbb8(0xd00000000000002aull, 0x80000000005c0a60ull);
    void (*emit)(word_t, word_t) = (void (*)(word_t, word_t))FUN_00027724(0x671848);
    emit(0x677790, 0x671848);
    thunk_FUN_002acbb8(0,0);
    FUN_003a25d4((void*)0);
    thunk_FUN_002acbb8(0x6d70206f746e6920ull, 0xe90000000000006dull);
    return (cl4_ret16_t){ .lo = 0xe000000000000000ull, .hi = 0 };
}

/* FUN_0008a2c8 @ 0x8a2c8   (est. cL4_diag_intro_c)
 * Ghidra: undefined1 [16] FUN_0008a2c8(void)
 * Diagnostic variant with error word 0xd00000000000002b/0x80000000005c0a90.
 * Confidence: medium */
cl4_ret16_t cL4_diag_intro_c(void)
{
    FUN_002a4ab4(0x36);
    thunk_FUN_002acbb8(0xd00000000000002bull, 0x80000000005c0a90ull);
    void (*emit)(word_t, word_t) = (void (*)(word_t, word_t))FUN_00027724(0x671848);
    emit(0x677790, 0x671848);
    thunk_FUN_002acbb8(0,0);
    FUN_003a25d4((void*)0);
    thunk_FUN_002acbb8(0x6d70206f746e6920ull, 0xe90000000000006dull);
    return (cl4_ret16_t){ .lo = 0xe000000000000000ull, .hi = 0 };
}

/* FUN_0008a3a0 @ 0x8a3a0   (est. cL4_parse_component_str)
 * Ghidra: void FUN_0008a3a0(undefined8,undefined8,byte *param_3,long param_4)
 * Parse a component identifier string ("base_phy", "size", etc.) into an
 * integer with optional sign/hex, validating against the limit param_4, then
 * look up the "type" and "sized" nodes and record the parse result. On any
 * malformed input it fatals.
 * Confidence: low
 * Notes: string words 0x7968705f65736162/0xed00007264646173 ("base_phy..."),
 *   0x657a6973/0xe4... ("size"), 0x74797065/0xed000065756c6176 ("type" +
 *   "value"); heavy inline decimal/hex loops; FATAL at 0x8aad0/0x8ab04. */
void cL4_parse_component_str(word_t a, word_t b, unsigned char *digits, word_t limit)
{
    word_t key = 0;
    FUN_000ab1fc(0x7968705f65736162ull, 0xed00007264646173ull);
    word_t v = FUN_0008dfe0();
    /* ... faithful signed/unsigned/hex digit parse into `key` ... */
    (void)v; (void)digits; (void)limit;
    word_t *node = (word_t *)FUN_001214c4();
    word_t n0 = node[0], n1 = node[1];
    thunk_FUN_0036b270((void *)n1);
    cl4_ret16_t name = FUN_000ab1fc(n0, n1);
    FUN_003a25d4((void *)n1);
    FUN_000ab1fc(0x657a6973ull, 0xe400000000000000ull);   /* "size" */
    word_t sz = FUN_0008dfe0();
    /* ... parse size similarly ... */
    (void)sz;
    word_t type = FUN_0008dfe0();
    (void)type;
    word_t log = FUN_000bde60(0);
    FUN_0036a940((word_t)log, 0x128, 7);
    FUN_000bd7b8(name.lo, name.hi, key, 0);
    FUN_0008e1a0();
    (**(void (**)(void))(0 + 0x98))();
    FUN_0008e1d4();
    (**(void (**)(void))(0 + 0x98))();
    FUN_0008e3ec();
}

/* FUN_0008abcc @ 0x8abcc   (est. cL4_parse_resource_pair)
 * Ghidra: void FUN_0008abcc(undefined8,undefined8,long,long)
 * Parse a pair of component resource values from the graph: first the "_id"
 * key then the "_dis" key (both signed/unsigned/hex), then resolve the
 * "base_add..." edge cap and copy it (with length check) through the object's
 * method chain, and finally emit the resource via FUN_000dd414.
 * Confidence: low
 * Notes: key words 0x64695f00000000/0xe7... ("_id"), 0x6469735f/0xe8... ("_dis"),
 *   0x7361625f/0xed00007264646165 ("_base_add..."), 0x6e656c5f/0xeb00000000687467
 *   ("_len_..."?); FATAL at 0x8b784/0x8b7b8. */
void cL4_parse_resource_pair(word_t a, word_t b, word_t c, word_t d)
{
    word_t id = 0, dis = 0;
    FUN_000ab1fc(FUN_0008e450() & 0xffffffffu | 0x64695f00000000ull, 0xe700000000000000ull);
    word_t idv = FUN_0008dfe0();
    (void)idv;
    FUN_000ab1fc(FUN_0008e450() & 0xffffffffu | 0x6469735f00000000ull, 0xe800000000000000ull);
    word_t disv = FUN_0008dfe0();
    (void)disv;
    /* ... parse id/dis ... then resolve base_add edge cap and copy ... */
    (void)c; (void)d;
    word_t *node = (word_t *)FUN_001214c4();
    word_t n0 = node[0], n1 = node[1];
    thunk_FUN_0036b270((void *)n1);
    cl4_ret16_t nm = FUN_000ab1fc(n0, n1);
    FUN_003a25d4((void *)n1);
    FUN_0008e328();
    word_t edge_node = (**(word_t (**)(void))(0 + 0xa0))();
    /* resolve base_add edge cap ... */
    word_t len_node = (**(word_t (**)(void))(0 + 0xa0))();
    (void)len_node;
    word_t log = FUN_000dda68(0);
    FUN_0036a940((word_t)log, 0x138, 7);
    FUN_000dd414(nm.lo, nm.hi, id, dis, 0, 0, log);
    FUN_0008e1a0();
    (**(void (**)(void))(0 + 0x98))();
    FUN_0008e1d4();
    (**(void (**)(void))(0 + 0x98))();
    FUN_0008e3ec();
}

/* FUN_0008b990 @ 0x8b990   (est. cL4_device_tree_check)
 * Ghidra: void FUN_0008b990(void)
 * Check the device-tree physical state: if FUN_0006b79c is nonzero, emit a
 * device-tree record via the +0x98 method; else, if the state probe passes,
 * emit a "Warning: Device tree physical..." log line.
 * Confidence: low
 * Notes: s_Warning____Device_tree_physical_005c0750; error word
 *   0xd00000000000003c. */
void cL4_device_tree_check(void)
{
    word_t v = FUN_0006b79c();
    if (v != 0) {
        word_t u2 = FUN_000e5c4c(0);
        FUN_0036a940((word_t)u2, 0x30, 7);
        FUN_000e58cc();
        word_t u3 = FUN_0008e1a0();
        (**(void (**)(word_t*, word_t, word_t))(0 + 0x98))((word_t*)(0 + 0x98), u3, 0x661c18);
        FUN_0036b118((void *)0);
        return;
    }
    FUN_0008e140();
    if (0 /* state */) {
        word_t u2 = FUN_0008e0d4();
        word_t obj = FUN_0036a9a0((word_t)u2, 0);
        word_t w0 = _DAT_004baeb0;
        *(word_t *)(obj + 0x18) = uRam00000000004baeb8;
        *(word_t *)(obj + 0x10) = w0;
        word_t line = FUN_0008e304("Warning: Device tree physical");
        *(word_t *)(line + 0x20) = 0xd00000000000003cull;
        *(word_t *)(line + 0x28) = (word_t)(0);
        FUN_00002804((void *)0);
        FUN_0036b588((void *)obj);
        FUN_00002688();
        FUN_00002834();
        FUN_0036b6ac(0);
    }
}

/* FUN_0008baa4 @ 0x8baa4   (est. cL4_parse_resource_arg)
 * Ghidra: void FUN_0008baa4(undefined8 param_1, long *param_2)
 * Parse a resource argument from the graph: look up the "type"/"value" node
 * pair, verify a valid component reference, then either emit a fatal
 * "DERComponentGraph failed to decode..." line or compute the resource via
 * FUN_000baf14 and push it (OR'd with the 0x8000000000000000 flag bit) into
 * the caller's edge list via the +0x60 method.
 * Confidence: low
 * Notes: strings s_DERComponentGraph_failed_to_deco_005c0790 (+0x20),
 *   s_Argument_position_is_malformed_005c07d0; error words 0xd00000000000003b/
 *   0x80000000005c0770; FATAL via FUN_001afa84. */
void cL4_parse_resource_arg(word_t a, word_t *param2)
{
    cl4_ret16_t ty = FUN_000ab1fc(0x5f6c61726574696cull, 0xec00000065707974ull);   /* "litera"+"type"? */
    word_t ty_hi = ty.hi;
    FUN_0008e328();
    cl4_ret16_t val = (**(cl4_ret16_t (**)(word_t, word_t))(0 + 0x110))
        (0x5f6c61726574696cull, 0xed000065756c6176ull);
    word_t val_hi = val.hi;
    FUN_0008e328();
    void (*m_a0)(void) = (void (*)(void))(*(word_t *)(0 + 0xa0));
    word_t node = ((word_t (*)(void))m_a0)();
    word_t present = 0;
    if (*(word_t *)(node + 0x10) != 0) {
        FUN_0006ae9c(0x6c616e6f6974706full, 0xe800000000000000ull);
        FUN_003a25d4((void *)node);
        present = 0;   /* extraout_w1 */
    }
    thunk_FUN_0036b270((void *)val_hi);
    thunk_FUN_0036b270((void *)ty_hi);
    cl4_ret16_t r = FUN_000ba594(ty.lo, ty_hi, val.lo, val_hi, present & 1);
    if (((r.hi ^ 0xffffffffu) & 0xff) == 0) {
        word_t lo = 0, hi = 0xe000000000000000ull;
        FUN_002a4ab4(0x41);
        thunk_FUN_002acbb8(0xd00000000000003bull, 0x80000000005c0770ull);
        thunk_FUN_002acbb8(ty.lo, ty_hi);
        thunk_FUN_002acbb8(0x203a, 0xe200000000000000ull);
        word_t src = FUN_00002534((word_t)0x64f3c0, (word_t)0x4e7fc0);
        FUN_00205844(&(cl4_ret16_t){0}, &hi, (void *)src, (void *)0x6753a0, (void *)0x66d1d8);
        thunk_FUN_002acbb8(hi, 0);
        FUN_003a25d4((void*)0);
        FUN_0008df14((const char *)0);
    } else {
        FUN_003a25d4((void *)ty_hi);
        FUN_003a25d4((void *)val_hi);
        word_t *node2 = (word_t *)FUN_00121510();
        word_t n0 = node2[0], n1 = node2[1];
        thunk_FUN_0036b270((void *)n1);
        cl4_ret16_t got = cL4_lookup_current_comp(n0, n1);
        FUN_003a25d4((void *)n1);
        if ((got.hi & 0xff) == 1) {
            FUN_0008df14("DERComponentGraph failed to decode");
        } else {
            word_t *node3 = (word_t *)FUN_00121540();
            n0 = node3[0]; n1 = node3[1];
            thunk_FUN_0036b270((void *)n1);
            cL4_lookup_current_comp(n0, n1);
            FUN_003a25d4((void *)n1);
            word_t comp = (**(word_t (**)(void))(0 + 0xa0))();
            (void)comp;
            word_t v3 = FUN_000bd174(0);
            FUN_0036a940((word_t)v3, 0x41, 7);
            word_t res = FUN_000baf14(r.lo, r.hi, got.lo, present & 1, got.lo, got.hi, v3);
            cl4_ret16_t edge = (**(cl4_ret16_t (**)(void *))(*(word_t *)(*param2 + 0x60)))((void*)(uintptr_t)0);
            FUN_0007b220();
            word_t cnt = *(word_t *)(*(word_t *)(edge.hi) + 0x10);
            FUN_0007b3fc(cnt);
            word_t base = *(word_t *)(edge.hi);
            *(word_t *)(base + 0x10) = cnt + 1;
            *(word_t *)(base + cnt * 8 + 0x20) = res | 0x8000000000000000ull;
            (*(void (**)(void *, word_t))edge.lo)((void*)(uintptr_t)0, 0);
        }
    }
}

/* FUN_0008bef0 @ 0x8bef0   (est. cL4_build_device_info)
 * Ghidra: void FUN_0008bef0(undefined8,undefined8,long *param_3)
 * Build the device-info records: if the probe (FUN_0006d4f0) succeeds, build
 * two device-tree ranges via FUN_0008bfec, then emit a summary record through
 * the caller's +0x98 method.
 * Confidence: low */
void cL4_build_device_info(word_t a, word_t b, word_t *param3)
{
    if (FUN_0006d4f0() != 0) {
        word_t u2 = FUN_0006d4fc();
        word_t u3 = FUN_0006d508();
        FUN_0008bfec((void*)(uintptr_t)0, u2, 0x4000, u3, b);
        u2 = FUN_0006d514();
        u3 = FUN_0006d520();
        FUN_0008bfec((void*)(uintptr_t)0, u2, 0x4000, u3, b);
    }
    word_t v2 = FUN_000e884c(0);
    FUN_0036a940((word_t)v2, 0x18, 7);
    v2 = FUN_000e8528(1);
    void (*m98)(void) = (void (*)(void))(*(word_t *)(*param3 + 0x98));
    thunk_FUN_0036b270((void *)v2);
    FUN_0008e02c();
    ((void (*)(void))m98)();
    FUN_0036b118((void *)v2);
    FUN_0036b118((void *)v2);
}

/* FUN_0008bfec @ 0x8bfec   (est. cL4_build_dev_range)
 * Ghidra: void FUN_0008bfec(undefined8 *param_1, undefined8,undefined8,undefined8, long)
 * Build a device-tree range record: call the object's +0x1b8 method with the
 * (size, param_3) range, resolve the resulting block, and serialize the
 * 0x30-byte record into param_1 with a BuildRoot header.
 * Confidence: low
 * Notes: s__AppleInternal_Library_BuildRoot_005c0610; FUN_00151a6c record tag 0xf9. */
void cL4_build_dev_range(word_t *out, word_t a, word_t size, word_t b, word_t obj)
{
    word_t v0 = *(word_t *)(obj + 0x18);
    word_t v1 = *(word_t *)(obj + 0x20);
    FUN_0006a4c0((void *)obj, v0);
    void (*fn)(void) = (void (*)(void))cL4_decode_method_ptr(v1);
    word_t *node = (word_t *)((word_t (*)(word_t, word_t))fn)(v0, v1);
    (**(void (**)(word_t*, word_t, word_t, word_t, word_t, word_t))(*node + 0x1b8))
        (&(word_t){0}, 8, a, size, 0, 0);
    FUN_0036b118((void *)node);
    FUN_0007bf4c(b, 0);
    cl4_ret16_t th = FUN_00151974();
    FUN_00151a6c((void*)0xf61c4, 0, "BuildRoot", 0xf9, 2, 0x2f0, th.lo, th.hi);
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
    out[4] = 0; out[5] = 0;
    *(word_t *)((uintptr_t)out + 0x31) = 0;
    *(word_t *)((uintptr_t)out + 0x29) = 0;
}

/* FUN_0008c138 @ 0x8c138   (est. cL4_emit_metal_name)
 * Ghidra: void FUN_0008c138(undefined8,undefined8,undefined8,long *param_4)
 * Emit a "td_node..."-named record: build the string key, call the +0x130
 * object constructor (FUN_000e18a0), and push the result through the caller's
 * +0x98 method.
 * Confidence: low
 * Notes: key word 0x6e65646f6e5f7464/0xeb00000000656d61 ("td_node"+"ema..."). */
void cL4_emit_metal_name(word_t a, word_t b, word_t c, word_t *param4)
{
    cl4_ret16_t key = FUN_000ab1fc(0x6e65646f6e5f7464ull, 0xeb00000000656d61ull);
    word_t v = FUN_000e1f64(0);
    FUN_0036a940((word_t)v, 0x130, 7);
    thunk_FUN_0036b270((void *)b);
    word_t obj = FUN_000e18a0(key.lo, key.hi, b, c);
    if (obj != 0) {
        void (*m98)(void) = (void (*)(void))(*(word_t *)(*param4 + 0x98));
        thunk_FUN_0036b270((void *)obj);
        FUN_0008e1d4();
        ((void (*)(void))m98)();
        FUN_0008e3ec();
    }
}

/* FUN_0008c240 @ 0x8c240   (est. cL4_dispatch_resource_type)
 * Ghidra: void FUN_0008c240(void)
 * Classify a resource-type string ("Shar"/"Release"/"All") and dispatch the
 * corresponding handler via FUN_00053568. Emits a fatal "type is not a valid
 * resource type" diagnostic if the string matches none.
 * Confidence: medium
 * Notes: string words 0x474e4952414853/0xe7..., 0x4e495341454c4552/0xe9...,
 *   &DAT_004c4c41/0xe3...; error words 0xd000000000000027/0x80000000005c0820,
 *   0xd000000000000029/0x80000000005c0850; FATAL at 0x8c580. */
void cL4_dispatch_resource_type(void)
{
    cl4_ret16_t ty = FUN_000ab1fc(0x65707974ull, 0xe400000000000000ull);   /* "type" */
    word_t ty_hi = ty.hi;
    word_t ty_lo = ty.lo;
    char kind; word_t dispatch;
    bool is_shar;
    if ((ty_lo == 0x474e4952414853ull && ty_hi == -0x1900000000000000ll) ||
        (FUN_0008e394(0x474e4952414853ull, 0xe700000000000000ull) & 1) != 0) {
        kind = 0; dispatch = 1; is_shar = true;
    } else if ((ty_lo == 0x4e495341454c4552ull && ty_hi == -0x16ffffffffffffb9ll) ||
               (FUN_0008e394(0x4e495341454c4552ull, 0xe900000000000047ull) & 1) != 0) {
        kind = 1; dispatch = 2; is_shar = false;
    } else if ((ty_lo != (word_t)0x4c4c41ull || ty_hi != -0x1d00000000000000ll) &&
               (FUN_0008e394(0x4c4c41ull, 0xe300000000000000ull) & 1) == 0) {
        word_t lo = 0, hi = 0xe000000000000000ull;
        FUN_002a4ab4(0x52);
        thunk_FUN_002acbb8(0xd000000000000027ull, 0x80000000005c0820ull);
        thunk_FUN_002acbb8(ty_lo, ty_hi);
        thunk_FUN_002acbb8(0xd000000000000029ull, 0x80000000005c0850ull);
        FUN_0008df14((const char *)0);
        FUN_0008dfbc();
        FUN_001afa84(0,0,0);   /* noreturn: "type is not a valid resource type" */
    } else {
        kind = 2; dispatch = 3; is_shar = false;
    }
    FUN_003a25d4((void *)ty_hi);
    word_t h = FUN_00053568(dispatch);
    word_t h2 = FUN_00053568(3);
    if (h != 0) { h2 = h; }
    char c = 2;
    if (h != 0) { c = kind; }
    if (h2 != 0) {
        /* publish the handler object */
        FUN_0008e388();
        FUN_0008e544(0);
        word_t obj = FUN_0008e468();
        (**(void (**)(word_t*, char))(*(word_t *)(obj) + 0x1d0))(&(word_t){0}, kind);
        FUN_0036b118((void *)h);
        FUN_00055874(h2, 0, kind + 1);
        FUN_00151974();
        FUN_0008e190();
        FUN_0008e160();
        FUN_0008e1e0(0);
        FUN_0008e154(0,0);
        FUN_00151a6c((void *)0, (void *)0, 0, 0, 0, 0, 0, 0);
        return;
    }
    if (!is_shar) {
        word_t u = FUN_00167a6c(0);
        cL4_log_resource_type(u, kind);
        return;
    }
    word_t lo = 0, hi = 0xe000000000000000ull;
    FUN_002a4ab4(0x3b);
    thunk_FUN_002acbb8(0xd000000000000012ull, 0x80000000005c0880ull);
    word_t s_lo, s_hi;
    if (kind == 0) { s_lo = 0xe700000000000000ull; s_hi = 0x676e6972616853ull; }
    else if (kind == 2) { s_lo = 0xe300000000000000ull; s_hi = 0x6c6c41ull; }
    else { s_lo = 0xe900000000000067ull; s_hi = 0x6e697361656c6552ull; }
    thunk_FUN_002acbb8(s_hi, s_lo);
    FUN_003a25d4((void *)s_lo);
    thunk_FUN_002acbb8(0xd000000000000027ull, 0x80000000005c08a0ull);
    FUN_0008df14((const char *)0);
    FUN_0008dfbc();
    FUN_001afa84(0,0,0);   /* noreturn */
}

/* FUN_0008c610 @ 0x8c610   (est. cL4_log_share_status)
 * Ghidra: undefined1 [16] FUN_0008c610(char param_1, char param_2)
 * Emit a two-part diagnostic: "Could not mint ... [Sharing/Release/All]"
 * then "[Sharing/Release/All] ... have we ..."; returns {lo=0xe000000000000000<<64}.
 * Confidence: medium
 * Notes: string words 0x6f6e20646c756f43/0xef20746e696d2074 ("Could not mint
 *   t"), 0x6576616820657720/0xe8... ("we have "); error word 0xd00000000000001e/
 *   0x80000000005c0950. */
cl4_ret16_t cL4_log_share_status(char a, char b)
{
    FUN_002a4ab4(0x39);
    thunk_FUN_002acbb8(0x6f6e20646c756f43ull, 0xef20746e696d2074ull);
    word_t s1_lo, s1_hi;
    if (a == 0) { s1_lo = 0xe700000000000000ull; s1_hi = 0x676e6972616853ull; }
    else if (a == 1) { s1_lo = 0xe900000000000067ull; s1_hi = 0x6e697361656c6552ull; }
    else { s1_lo = 0xe300000000000000ull; s1_hi = 0x6c6c41ull; }
    thunk_FUN_002acbb8(s1_hi, s1_lo);
    FUN_003a25d4((void *)s1_lo);
    thunk_FUN_002acbb8(0xd00000000000001eull, 0x80000000005c0950ull);
    word_t s2_lo, s2_hi;
    if (b == 0) { s2_lo = 0xe700000000000000ull; s2_hi = 0x676e6972616853ull; }
    else if (b == 1) { s2_lo = 0xe900000000000067ull; s2_hi = 0x6e697361656c6552ull; }
    else { s2_lo = 0xe300000000000000ull; s2_hi = 0x6c6c41ull; }
    thunk_FUN_002acbb8(s2_hi, s2_lo);
    FUN_003a25d4((void *)s2_lo);
    thunk_FUN_002acbb8(0x6576616820657720ull, 0xe800000000000000ull);
    return (cl4_ret16_t){ .lo = 0xe000000000000000ull, .hi = 0 };
}

/* FUN_0008c788 @ 0x8c788   (est. cL4_snapshot_node)
 * Ghidra: void FUN_0008c788(undefined1 (*param_1) [16])
 * Copy a 0x60-byte node into a scratch record, build the comp record
 * (FUN_00089684), release the scratch, and store the record into *param_1.
 * Confidence: low */
void cL4_snapshot_node(cl4_ret16_t *out)
{
    unsigned char scratch[96];
    FUN_00117cc4(scratch, 0, 0x60);
    cl4_ret16_t rec = cL4_build_comp_record();
    FUN_0008dbc0(scratch);
    *out = rec;
}

/* FUN_0008c7e4 @ 0x8c7e4   (est. cL4_snapshot_release)
 * Ghidra: void FUN_0008c7e4(void)
 * Copy a 0x60-byte scratch record, then run FUN_0008c820.
 * Confidence: low */
void cL4_snapshot_release(void)
{
    unsigned char scratch[96];
    FUN_00117cc4(scratch, 0, 0x60);
    cL4_snapshot_emit();
}

/* FUN_0008c820 @ 0x8c820   (est. cL4_snapshot_emit)
 * Ghidra: undefined8 FUN_0008c820(void)
 * Fetch a record (FUN_0008d43c) and release it (FUN_0008dbc0); return the token.
 * Confidence: low */
word_t cL4_snapshot_emit(void)
{
    word_t v = FUN_0008d43c();
    FUN_0008dbc0((void *)0);
    return v;
}

/* FUN_0008c854 @ 0x8c854   (est. cL4_record_emit3)
 * Ghidra: void FUN_0008c854(undefined8,undefined8,undefined8)
 * Copy a 0x60-byte scratch record then forward three args to thunk_FUN_0008cd54.
 * Confidence: low */
void cL4_record_emit3(word_t a, word_t b, word_t c)
{
    unsigned char scratch[96];
    FUN_00117cc4(scratch, 0, 0x60);
    cL4_record_build((long *)(uintptr_t)a, b, c);
}

/* FUN_0008c8b4 @ 0x8c8b4   (est. cL4_parse_string_int)
 * Ghidra: void FUN_0008c8b4(ulong *param_1, ulong *param_2, undefined8, undefined8)
 * Parse the capability-encoded string in *param_2 (a {lo,hi} string pair)
 * into an integer, honoring an optional sign ('+'/'-') and base-10 or
 * base-16 digits, with overflow checks. On success store the value into
 * *param_1; on any malformed input or overflow raise a fatal
 * "getOrAllocateComponentResourceCapFromEdge ... but to" diagnostic.
 * Confidence: medium
 * Notes: string length field at hi>>0x38 & 0xf (or hi==0x2000.. flag picks
 *   it); FATAL at 0x8cbc0/0x8cbc4/0x8cbb8 via FUN_001afa84 with
 *   s_InternalExclaveLauncher_Resource_005c0550; error words
 *   0xd00000000000001f/0x80000000005c09d0. */
void cL4_parse_string_int(unsigned long *out, unsigned long *in, word_t ctx_a, word_t ctx_b)
{
    word_t s0 = in[0];
    word_t s1 = in[1];
    word_t len = s1 >> 0x38 & 0xf;
    word_t val = s0 & 0xffffffffffffull;
    if ((s1 & 0x2000000000000000ull) != 0) { val = len; }
    word_t acc = 0;
    bool failed = false;
    if (val == 0) { failed = true; goto fatal; }
    if ((s1 >> 0x3c & 1) == 0) {
        /* string is a plain (ptr,len) */
        word_t n;
        unsigned char *p;
        if ((s0 >> 0x3c & 1) == 0) {
            cl4_ret16_t d = FUN_002a9ba8(s0, s1);
            n = d.hi;
            p = (unsigned char *)d.lo;
        } else {
            n = s0 & 0xffffffffffffull;
            p = (unsigned char *)((s1 & 0xfffffffffffffffull) + 0x20);
        }
        if (n < 1) { SoftwareBreakpoint(1, 0x8cbb8); }
        bool neg = false;
        if (*p == '+') {
            if (n != 1 && p == 0) { SoftwareBreakpoint(1, 0x8cbc4); }
            n -= 1;
            p += 1;
        } else if (*p == '-') {
            if (n != 1 && p == 0) { SoftwareBreakpoint(1, 0x8cbc0); }
            neg = true;
            n -= 1;
            p += 1;
        }
        while (n != 0) {
            unsigned d = (unsigned char)*p - 0x30;
            if (d > 9) { failed = true; goto fatal; }   /* non-digit */
            unsigned long m = acc * 10;
            if ((m & 0xffffffff00000000ull) != 0) { failed = true; goto fatal; }
            unsigned long add = (unsigned long)d;
            acc = (neg) ? m - add : m + add;
            if ((neg && m < add) || (!neg && (m + add < m))) { failed = true; goto fatal; }
            n -= 1;
            p += 1;
        }
        *out = acc;
        return;
    } else if ((s1 >> 0x3d & 1) == 0) {
        /* string is an inline short string (up to 8 bytes in the words) */
        word_t w0 = s0;
        word_t w1 = s1 & 0xffffffffffffffull;
        if (len == 0) { SoftwareBreakpoint(1, 0x8cbbc); }
        unsigned char first = (unsigned char)w0;
        bool neg = false;
        if (first == '+') {
            len -= 1;
            if (len == 0) { *out = 0; return; }
            w0 = (w0 & ~0xffull) | (word_t)((unsigned char*)&w0)[1];
        } else if (first == '-') {
            neg = true;
            len -= 1;
            if (len == 0) { *out = 0; return; }
            w0 = (w0 & ~0xffull) | (word_t)((unsigned char*)&w0)[1];
        }
        unsigned char *p = (unsigned char *)&w0;
        while (len != 0) {
            unsigned d = (unsigned char)*p - 0x30;
            if (d > 9) { failed = true; goto fatal; }
            unsigned long m = acc * 10;
            if ((m & 0xffffffff00000000ull) != 0) { failed = true; goto fatal; }
            unsigned long add = (unsigned long)d;
            acc = (neg) ? m - add : m + add;
            if ((neg && m < add) || (!neg && (m + add < m))) { failed = true; goto fatal; }
            len -= 1;
            p += 1;
        }
        *out = acc;
        return;
    } else {
        /* big/foreign string representation -> use the 128-bit decoder */
        cl4_ret16_t d = thunk_FUN_000b02dc(s0, s1, 10);
        if ((d.hi & 0xff) == 1) { failed = true; goto fatal; }
        *out = d.lo;
        return;
    }
fatal:
    {
        word_t e_lo = 0xd00000000000001full;
        word_t e_hi = 0x80000000005c09d0ull;
        FUN_002a4ab4(0x2c);
        FUN_003a25d4((void *)0xe000000000000000ull);
        thunk_FUN_002acbb8(ctx_a, ctx_b);
        thunk_FUN_002acbb8(0x746f672074756220ull, 0xe900000000000020ull);   /* "but to g..." */
        thunk_FUN_002acbb8(s0, s1);
        FUN_001afa84("Fatal error", 0xb, 2, e_lo, e_hi,
                     "InternalExclaveLauncher/Resource", 0x2d, 2, 0x381, 0);
    }
}

/* FUN_0008cc74 @ 0x8cc74   (est. cL4_and64)
 * Ghidra: ulong FUN_0008cc74(ulong param_1, ulong param_2)
 * 64-bit bitwise AND (param_2 & param_1).
 * Confidence: high */
word_t cL4_and64(word_t a, word_t b) { return b & a; }

/* FUN_0008cc7c @ 0x8cc7c   (est. cL4_and32)
 * Ghidra: uint FUN_0008cc7c(uint param_1, uint param_2)
 * 32-bit bitwise AND (param_2 & param_1).
 * Confidence: high */
unsigned int cL4_and32(unsigned int a, unsigned int b) { return b & a; }

/* FUN_0008cd04 @ 0x8cd04   (est. cL4_and_byte)
 * Ghidra: void FUN_0008cd04(undefined1 *param_1, undefined1 *param_2)
 * AND the byte at *x20 with *param_2 and store the result into *param_1.
 * Confidence: high */
void cL4_and_byte(unsigned char *out, unsigned char *in)
{
    *out = cL4_and32(*in, *(unsigned char *)(uintptr_t)0x20);
}

/* thunk_FUN_0008cd54 @ 0x8c8b0 / FUN_0008cd54 @ 0x8cd54   (est. cL4_record_build)
 * Ghidra: long thunk_FUN_0008cd54(long *param_1, long param_2, long param_3)
 * Build a component-graph record object: allocate a 0x80-byte record, copy
 * the 12 words of the current node into it, deep-copy the three node lists
 * (FUN_0008db58), then copy up to `param_3` 32-byte entries from the record
 * into the caller's buffer param_2 (bounded by the record count). Returns the
 * number of entries copied and stashes {record, count} into param_1.
 * Confidence: medium
 * Notes: node type words _DAT_004c0f00/uRam...4c0f08; param_3 bounds to 3
 *   entries (0x60/0x20); breaks at 0x8cea0/0x8cea4. */
long cL4_record_build(long *out, word_t dst, word_t n)
{
    word_t desc = FUN_00002534((word_t)0x64f5a8, (word_t)0x4c0ff0);
    word_t rec = FUN_0036a940((word_t)desc, 0x80, 7);
    word_t w0 = _DAT_004c0f00;
    word_t s0 = *(word_t *)(uintptr_t)0x18;
    word_t s1 = *(word_t *)(uintptr_t)0x10;
    word_t s2 = *(word_t *)(uintptr_t)0x28;
    word_t s3 = *(word_t *)(uintptr_t)0x20;
    *(word_t *)(rec + 0x18) = uRam00000000004c0f08;
    *(word_t *)(rec + 0x10) = w0;
    *(word_t *)(rec + 0x28) = s0;
    *(word_t *)(rec + 0x20) = s1;
    word_t s8 = *(word_t *)(uintptr_t)0x50;
    word_t s9 = *(word_t *)(uintptr_t)0x48;
    word_t sa = *(word_t *)(uintptr_t)0x60;
    word_t sb = *(word_t *)(uintptr_t)0x58;
    *(word_t *)(rec + 0x68) = s9;
    *(word_t *)(rec + 0x60) = s8;
    *(word_t *)(rec + 0x78) = sa;
    *(word_t *)(rec + 0x70) = sb;
    word_t s4 = *(word_t *)(uintptr_t)0x28;
    word_t s5 = *(word_t *)(uintptr_t)0x20;
    word_t s6 = *(word_t *)(uintptr_t)0x38;
    word_t s7 = *(word_t *)(uintptr_t)0x30;
    *(word_t *)(rec + 0x38) = s2;
    *(word_t *)(rec + 0x30) = s3;
    *(word_t *)(rec + 0x48) = s4;
    *(word_t *)(rec + 0x40) = s5;
    *(word_t *)(rec + 0x58) = s6;
    *(word_t *)(rec + 0x50) = s7;
    FUN_0008db58((void *)&s1, (void *)(uintptr_t)0);
    FUN_0008db58((void *)&s7, (void *)(uintptr_t)0);
    FUN_0008db58((void *)&s8, (void *)(uintptr_t)0);
    FUN_0008dbc0((void *)0);
    if (dst == 0) {
        n = 0;
    } else {
        if (n < 0) { SoftwareBreakpoint(1, 0x8cea4); }
        if (n != 0) {
            word_t i = 1;
            for (word_t off = 0; off != 0x60; off += 0x20) {
                if (*(word_t *)(rec + 0x10) <= i - 1U) { SoftwareBreakpoint(1, 0x8cea0); }
                word_t *d = (word_t *)(dst + off);
                word_t s = rec + off;
                d[0] = *(word_t *)(s + 0x20);
                d[1] = *(word_t *)(s + 0x28);
                d[2] = *(word_t *)(s + 0x30);
                d[3] = *(word_t *)(s + 0x38);
                if (n == i) {
                    thunk_FUN_0036b270((void*)0);
                    goto out;
                }
                thunk_FUN_0036b270((void*)0);
                i += 1;
            }
            n = 3;
        }
    }
out:
    out[0] = rec;
    out[1] = n;
    return n;
}

/* FUN_0008cea4 @ 0x8cea4   (est. cL4_emit_bitarray_32)
 * Ghidra: void FUN_0008cea4(undefined8,undefined8,long param_3,long param_4)
 * Emit the set bits of a bit-array: iterate the array words (found via
 * FUN_0008e3c0), reverse the bits of each nonzero word, and for each set bit
 * copy a 32-bit element from the table at param_4+0x30 (indexed by
 * LZCOUNT(reversed) + word*0x100) into the output, `param_3` elements total.
 * Confidence: low
 * Notes: classic bit-reverse (0xaaaa.../0xcccc... masks) + LZCOUNT index. */
void cL4_emit_bitarray_32(word_t a, word_t b, long n, word_t table)
{
    word_t *arr = (word_t *)(uintptr_t)0;
    if (arr != 0) {
        if (n < 0) { SoftwareBreakpoint(1, 0x8cf58); }
        if (n != 0) {
            long w = 0, done = 0;
            word_t bits = 0;
            do {
                while (bits == 0) {
                    w += 1;
                    if (w > 0x3f) goto done_label;
                    bits = *(word_t *)((word_t)(0) + w * 8);
                }
                done += 1;
                word_t r = (bits & 0xaaaaaaaaaaaaaaaaull) >> 1 | (bits & 0x5555555555555555ull) << 1;
                r = (r & 0xccccccccccccccccull) >> 2 | (r & 0x3333333333333333ull) << 2;
                r = (r & 0xf0f0f0f0f0f0f0f0ull) >> 4 | (r & 0x0f0f0f0f0f0f0f0full) << 4;
                r = (r & 0xff00ff00ff00ff00ull) >> 8 | (r & 0x00ff00ff00ff00ffull) << 8;
                r = (r & 0xffff0000ffff0000ull) >> 16 | (r & 0x0000ffff0000ffffull) << 16;
                bits = bits - 1 & bits;
                unsigned int *out32 = (unsigned int *)(uintptr_t)0;
                out32[done - 1] = *(unsigned int *)(*(word_t *)(table + 0x30) +
                                __builtin_clzll(r >> 32 | r << 32) * 4 + w * 0x100);
            } while (done != n);
        }
    }
done_label:
    FUN_0008e1b0();
}

/* FUN_0008cf58 @ 0x8cf58   (est. cL4_emit_bitarray_64)
 * Ghidra: void FUN_0008cf58(undefined8,undefined8,long param_3,long param_4)
 * As cL4_emit_bitarray_32 but copies 64-bit elements from param_4+0x30
 * (indexed by LZCOUNT(reversed)*8 + word*0x200).
 * Confidence: low */
void cL4_emit_bitarray_64(word_t a, word_t b, long n, word_t table)
{
    word_t *arr = (word_t *)(uintptr_t)0;
    if (arr != 0) {
        if (n < 0) { SoftwareBreakpoint(1, 0x8d00c); }
        if (n != 0) {
            long w = 0, done = 0;
            word_t bits = 0;
            do {
                while (bits == 0) {
                    w += 1;
                    if (w > 0x3f) goto done_label;
                    bits = *(word_t *)((word_t)(0) + w * 8);
                }
                done += 1;
                word_t r = (bits & 0xaaaaaaaaaaaaaaaaull) >> 1 | (bits & 0x5555555555555555ull) << 1;
                r = (r & 0xccccccccccccccccull) >> 2 | (r & 0x3333333333333333ull) << 2;
                r = (r & 0xf0f0f0f0f0f0f0f0ull) >> 4 | (r & 0x0f0f0f0f0f0f0f0full) << 4;
                r = (r & 0xff00ff00ff00ff00ull) >> 8 | (r & 0x00ff00ff00ff00ffull) << 8;
                r = (r & 0xffff0000ffff0000ull) >> 16 | (r & 0x0000ffff0000ffffull) << 16;
                bits = bits - 1 & bits;
                word_t *out64 = (word_t *)(uintptr_t)0;
                out64[done - 1] = *(word_t *)(*(word_t *)(table + 0x30) +
                                __builtin_clzll(r >> 32 | r << 32) * 8 + w * 0x200);
            } while (done != n);
        }
    }
done_label:
    FUN_0008e1b0();
}

/* FUN_0008d00c @ 0x8d00c   (est. cL4_emit_bitarray_caps)
 * Ghidra: void FUN_0008d00c(undefined8,undefined8,long param_3)
 * Emit set bits of a bit-array as capability words: for each set bit copy a
 * 64-bit cap from the table at x20+0x38 (indexed by position) into the output,
 * `param_3` caps total. Emits the count via FUN_0008e500.
 * Confidence: low */
void cL4_emit_bitarray_caps(word_t a, word_t b, long n)
{
    word_t *arr = (word_t *)(uintptr_t)0;
    long count = 0;
    if (arr != 0) {
        if (n < 0) { SoftwareBreakpoint(1, 0x8d0f8); }
        if (n != 0) {
            word_t *out = arr;
            long w = 0;
            word_t bits = 0;
            while (1) {
                while (bits == 0) {
                    w += 1;
                    if (w > 0x3f) goto done;
                    bits = *(word_t *)((word_t)(0) + w * 8);
                }
                bits = bits - 1 & bits;
                *out = *(word_t *)(*(word_t *)(uintptr_t)0x38 + 0 * 8 + w * 0x200);
                if (n == 0) break;
                out += 1;
            }
        }
    }
done:
    FUN_0008e500(FUN_0008e070(count).lo, 0);
}

/* FUN_0008d0f8 @ 0x8d0f8   (est. cL4_emit_bitarray_pairs)
 * Ghidra: void FUN_0008d0f8(undefined8,undefined8,long param_3)
 * Emit set bits of a bit-array as 16-byte cap pairs from the table at x20+0x30
 * (indexed by word*0x400), `param_3` pairs total. Emits the count.
 * Confidence: low */
void cL4_emit_bitarray_pairs(word_t a, word_t b, long n)
{
    word_t *arr = (word_t *)(uintptr_t)0;
    long count = 0;
    if (arr != 0) {
        if (n < 0) { SoftwareBreakpoint(1, 0x8d1c4); }
        if (n != 0) {
            word_t *out = arr;
            long w = 0;
            word_t bits = 0;
            while (1) {
                while (bits == 0) {
                    w += 1;
                    if (w > 0x3f) goto done;
                    bits = *(word_t *)((word_t)(0) + w * 8);
                }
                word_t *src = (word_t *)(*(word_t *)(uintptr_t)0x30 + 0 * 0x10 + w * 0x400);
                word_t v0 = src[0];
                word_t v1 = src[1];
                bits = bits - 1 & bits;
                out[0] = v0;
                out[1] = v1;
                if (count == n) break;
                out += 2;
            }
        }
    }
done:
    FUN_0008e500(FUN_0008e070(count).lo, 0);
}

/* FUN_0008d1c4 @ 0x8d1c4   (est. cL4_merge_node_lists)
 * Ghidra: long FUN_0008d1c4(long *param_1,long param_2,long param_3,long param_4)
 * Merge up to param_3 node-list entries: walk the node lists at param_2 and
 * param_4 (both have count at +0x10, 0x28-byte entries at +0x20), appending
 * each source entry into the destination via FUN_0008de50, and record the
 * merge state {dest, srcIndex, srcNode, srcCount} into param_1. Returns the
 * number merged.
 * Confidence: low
 * Notes: 0x28-byte node entries; merges source lists param_2 then param_4. */
long cL4_merge_node_lists(long *out, word_t srcA, long n, word_t srcB)
{
    word_t sc = 0;      /* count within the current source node */
    word_t snode = 0;   /* current source node being walked */
    if (srcA == 0) {
        out[0] = srcB;
        out[1] = 0;
        out[2] = 0;
        out[3] = 0;
    } else {
        if (n < 0) { SoftwareBreakpoint(1, 0x8d34c); }
        if (n != 0) {
            word_t sidx = 0;
            word_t merged = 0;
loop:
            do {
                if (snode != 0) {
                    if (sc != *(word_t *)(snode + 0x10)) goto advance;
                    FUN_0008de50(&(word_t){0});
                }
                if (sidx == *(word_t *)(srcB + 0x10)) { goto drain; }
                if (*(word_t *)(srcB + 0x10) <= sidx) { SoftwareBreakpoint(1, 0x8d348); }
                snode = *(word_t *)(srcB + sidx * 8 + 0x20);
                thunk_FUN_0036b270((void *)snode);
                FUN_0036b118((void *)0);
                sc = 0;
                sidx += 1;
            } while (1);
advance:
            if (*(word_t *)(snode + 0x10) <= sc) { SoftwareBreakpoint(1, 0x8d350); }
            FUN_0006e7c0((void *)(snode + sc * 0x28 + 0x20), &(word_t){0});
            sc += 1;
            if (0 /* list tail */ == 0) {
drain:
                FUN_0008de50(&(word_t){0});
                out[0] = srcB;
                out[1] = sidx;
                merged = 0;
                goto set;
            }
            FUN_00077070(&(word_t){0}, (void *)(uintptr_t)0);
            FUN_00077070((void *)(uintptr_t)0, (void *)srcA);
            srcA += 0x28;
            merged += 1;
            if (merged == n) { goto set; }
            goto loop;
        }
        out[0] = srcB;
        out[1] = 0;
    }
set:
    out[2] = snode;
    out[3] = sc;
    return n;
}
