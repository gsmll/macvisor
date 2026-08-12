/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 194: 0x439d74-0x44ca2c. All names are estimates unless string/header
 * matched. Uses seL4/cL4 vocabulary.
 *
 * This region is the kernel's container/object library: growable element
 * vectors (element size 0x50) guarded by a token/allocator layer, a
 * delimited serialization/parse state machine (ASCII delimiters '=', ':',
 * '[', ']', '}', '\' with the 0xe1... token tag), and acquire/commit/release
 * plumbing around every mutation. The decompiler models most functions as
 * `void FUN(void)` because arguments and results ride in registers
 * (unaff_x19/unaff_x20 = C++ `this`; results in x8/x9/x1) rather than as
 * formal parameters. We model the container `this` as the first parameter
 * `thisp` and the multi-word register result as a trailing out-pointer where
 * the register use is unambiguous; Ghidra FUN_ names are kept in comments.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;

/* 16-byte register-pair result (lo in x0/x8, hi in x1/x9). */
typedef struct sk_pair {
    word_t lo;
    word_t hi;
} sk_pair_t;

/* Parser/state machine context. The decompiler models the two state
 * registers (unaff_x20 = current char/word, unaff_x19 = token tag) as
 * implicit; we carry them as fields so the reconstructions compile. */
typedef struct sk_parser {
    word_t cur;    /* unaff_x20: current character / key word */
    word_t tag;    /* unaff_x19: token tag (e.g. 0xe1..) */
} sk_parser_t;

#define SK_TAG_DELIM  0xe100000000000000ull

typedef uint8_t byte;

void sk_noop(void);

/* Shared globals referenced by this slice (decompiler _DAT symbols). */
extern word_t _DAT_005a18a0, _DAT_005a18a8, _DAT_005a1870, _DAT_005a1878;
extern word_t _DAT_005a1890, _DAT_005a1898, _DAT_004c2450, _DAT_004c2458;
extern word_t _DAT_00594e41, _DAT_004c554e, _DAT_00504355, _DAT_005a35c0, _DAT_005a35f8;
extern word_t _DAT_005a1880, _DAT_005a1888;
extern word_t DAT_004be900, DAT_004e824c;
extern word_t DAT_00657778, DAT_00657788, DAT_004c05b0, DAT_004baeb0, DAT_004baeb8;
extern word_t DAT_006577e0;
extern word_t DAT_005a19a0, DAT_0064e7d8, DAT_005a35c8;
extern word_t thunk_FUN_0036b270(word_t);
extern sk_pair_t thunk_FUN_002acbb8();
extern sk_pair_t FUN_001bc440();
extern sk_pair_t FUN_0044bdc8();
extern sk_pair_t FUN_00463f94();
extern sk_pair_t FUN_00464140();
extern sk_pair_t FUN_00463e04();
extern word_t (*DAT_00658cf0)(word_t);      /* token format vtable */
extern sk_pair_t thunk_FUN_002b74c0();
extern word_t   thunk_FUN_0024d9ac(word_t);
extern word_t   thunk_FUN_0045027c();

#define CL4_FATAL() __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* ------------------------------------------------------------------ *
 * Out-of-slice helpers (bodies reconstructed by their owning workers).
 * Signatures reflect observed register use at call sites.
 * ------------------------------------------------------------------ */
extern word_t sk_ref_release(word_t);          /* FUN_0036b118 cL4 ref release */
extern word_t sk_ref_retain(word_t);           /* FUN_0036b270 retain->obj */
extern void   sk_token_release(word_t);        /* FUN_003a25d4 token release */
extern word_t sk_alloc_probe(word_t);          /* FUN_003a261c probe (bit0) */
extern word_t sk_obj_alloc(word_t);            /* FUN_0036a940 object alloc */
extern void   sk_memcpy(word_t, word_t, word_t);   /* FUN_00117cc4 memcpy */
extern void   sk_rwlock_op(word_t, word_t);    /* FUN_001ee018 rw-lock op */
extern void   sk_fault_builder(int);           /* FUN_002a4ab4 fault builder */
extern void   sk_debug_print(word_t, word_t);  /* thunk_FUN_002acbb8 debug print */
extern sk_pair_t sk_pair_fn(word_t, word_t, word_t, word_t); /* FUN_0029fa0c */
extern sk_pair_t sk_state_pair(void);          /* FUN_002b3f40 state pair */
extern sk_pair_t sk_token_acquire(void);       /* FUN_002b439c token pair */
extern long   sk_scan_count(void);             /* FUN_002b4120 scan count */
extern word_t sk_state_acquire(word_t, word_t);/* FUN_002a0cf8 state check */
extern word_t sk_vec_cap_probe(void);          /* FUN_0006b42c cap probe */
extern void   sk_vec_state_op(void);           /* FUN_0006b3f4 */
extern void   sk_vec_grow_hint(void);          /* FUN_0006b6a0 */
extern void   sk_vec_helper(void);             /* FUN_0006b674 */
extern word_t sk_vec_grow7(word_t, word_t, word_t, word_t, word_t,
                           word_t, word_t);    /* FUN_0045636c grow+callbacks */
extern word_t sk_elem_cb_a(word_t);            /* FUN_00072178 elem callback */
extern word_t sk_elem_cb_b(word_t);            /* FUN_00455fe4 elem callback */
extern word_t sk_elem_cb_c(word_t);            /* FUN_0045694c elem callback */
extern void   sk_vec_settle(void);             /* FUN_00084180 */
extern void   sk_lock_enter(void);             /* FUN_00084220 */
extern void   sk_lock_done(word_t, word_t, word_t); /* FUN_00084234 */
extern word_t sk_vec_range_get(word_t);        /* FUN_0008409c */
extern void   sk_vec_grow_a(void);             /* FUN_0008e500 */
extern void   sk_vec_grow_b(void);             /* FUN_0008e518 */
extern word_t sk_parser_byte(word_t);          /* FUN_00086840 byte probe */
extern word_t sk_obj_claim(word_t);            /* FUN_0001a1c8 obj claim */
extern word_t sk_typeinfo(word_t);             /* FUN_00027724 typeinfo */
extern void   sk_parse_advance(void);          /* FUN_00350518 */
extern void   sk_parse_restore(void);          /* FUN_00350bfc */
extern void   sk_parse_enter(void);            /* FUN_003512c0 */
extern void   sk_parse_consume(void);          /* FUN_00351790 */
extern void   sk_parse_step(void);             /* FUN_003524b0 */
extern sk_pair_t sk_parse_pair(void);          /* FUN_00351db4 */
extern void   sk_parse_pair_apply(void);       /* FUN_00351e08 */
extern void   sk_parse_leave(word_t);          /* FUN_003544c8 */
extern word_t sk_parse_save(void);             /* FUN_00354744 */
extern word_t sk_empty_range(void);            /* FUN_004663ac empty range */
extern void   sk_alloc_enter(void);            /* FUN_00465540 */
extern void   sk_alloc_reenter(void);          /* FUN_004657d0 */
extern word_t sk_state_pair2(void);            /* FUN_0042f7d4 pair result */
extern void   FUN_00464d5c(void);              /* empty-range init */
extern void   FUN_004368c0(void);              /* container probe */
extern void   FUN_004640c4(void);              /* container commit */
extern void   FUN_004649fc(void);              /* frame save */
extern void   FUN_00465288(void);              /* frame init */
extern void   FUN_004644dc(void);              /* loop step */
extern void   sk_commit2(void);                /* FUN_00463bc8 */
extern word_t sk_acquire2(void);               /* FUN_0042f670 state (bit0) */
extern void   sk_advance_to(word_t);           /* FUN_00462b80 advance-to-delim */
extern word_t sk_state_ok(void);               /* FUN_002a0cf8 state check (bit0) */
extern void   sk_parse_step2(int);             /* FUN_0043152c */
extern word_t sk_state_push(word_t, word_t);   /* FUN_0042ec68 state acquire */

/* Parser/container micro-ops referenced across the slice (FUN_ addresses). */
extern void   sk_token_begin(void);            /* FUN_00462788 */
extern void   sk_token_consume(void);          /* FUN_00462aac */
extern void   sk_token_settle(void);           /* FUN_004628c4 */
extern void   sk_token_settle2(word_t, word_t);/* FUN_00462b00 */
extern void   sk_token_enter(void);            /* FUN_00462870 */
extern void   sk_record_init(void);            /* FUN_00463c0c */
extern void   sk_record_fill(word_t *);        /* FUN_00462a48 */
extern void   sk_record_append_alt(word_t *);  /* FUN_00461430 */
extern void   sk_buf_discard(word_t);          /* FUN_00462710 */
extern void   sk_parse_advance2(void);         /* FUN_004635c8 */
extern void   sk_parse_consume2(void);         /* FUN_00462f24 */
extern void   sk_parse_adv3(void);             /* FUN_003511a8 */
extern void   sk_parse_adv4(void);             /* FUN_00351aec */
extern void   sk_parse_adv5(void);             /* FUN_00351a5c */
extern void   sk_parse_adv6(void);             /* FUN_00351a44 */
extern void   sk_parse_p7(void);               /* FUN_00355d90 */
extern void   sk_parse_p8(void);               /* FUN_00351c7c */
extern void   sk_parse_p9(void);               /* FUN_00351f28 */
extern sk_pair_t sk_parse_pa(void);            /* FUN_00350aa0 */
extern void   sk_parse_pb(void);               /* FUN_003504c4 */
extern void   sk_parse_pc(word_t, word_t, int, int, int); /* FUN_004339a8 */
extern void   sk_parse_pd(void);               /* FUN_00356b5c */
extern void   sk_parse_pe(word_t);             /* FUN_00462adc */
extern void   sk_parse_pf(word_t, word_t, int);/* FUN_00463540 */
extern word_t sk_parse_pg(void);               /* FUN_00462d88 */
extern void   sk_parse_ph(word_t);             /* FUN_00462a08 */
extern word_t sk_parse_pi(void);               /* FUN_0046635c */
extern void   sk_parse_pj(void);               /* FUN_004644dc */
extern void   sk_parse_pk(void);               /* FUN_00465ddc */
extern void   sk_parse_pl(void);               /* FUN_00463514 */
extern void   sk_parse_pm(void);               /* FUN_0046282c */
extern void   sk_parse_pn(void);               /* FUN_00462f3c */
extern void   sk_parse_po(void);               /* FUN_00461a60 */
extern void   sk_parse_pp(void);               /* FUN_00461aa8 */
extern void   sk_parse_pq(word_t *);           /* FUN_00462ec68 */
extern void   sk_parse_pr(word_t *);           /* FUN_0042fc4c */
extern void   sk_parse_ps(word_t *, int);      /* FUN_00430d08 */
extern void   sk_parse_pt(word_t *);           /* FUN_00464b20 */
extern word_t sk_elem_fetch(void);             /* FUN_0046322c */
extern word_t sk_elem_alloc2(word_t, word_t *);/* FUN_0036a9a0 */
extern word_t sk_elem_alloc(word_t);           /* FUN_00466074 */
extern void   sk_elem_store(word_t);           /* FUN_0036b588 */
extern void   sk_list_op2(void);               /* FUN_00455db8 */
extern void   sk_lock_acquire(word_t, word_t); /* FUN_00462af0 */
extern void   sk_lock_release(void);           /* FUN_0036b6ac */
extern void   sk_res_claim(word_t);            /* FUN_00002834 */
extern void   sk_res_claim2(word_t);           /* FUN_00002850 */
extern void   sk_obj_store(word_t, word_t);    /* FUN_00430040 */
extern void   sk_internal_reset(word_t);       /* FUN_00100e34 */
extern void   sk_trace_reset(word_t);          /* FUN_00356588 */
extern word_t sk_claim_obj(word_t);            /* FUN_0001a1c8 */
extern void   sk_claim_release(word_t);        /* FUN_000778b4 */
extern void   sk_claim_init(word_t);           /* FUN_0036b6ac */

/* Large-function helper batch (FUN_ addresses). */
extern sk_pair_t sk_frame_save(void);          /* FUN_00464b04 */
extern void   FUN_000a6f68(void);              /* script-string probe */
extern void   FUN_00354ca8(word_t, word_t);    /* range check */
extern void   FUN_004659bc(void);              /* parser step */
extern void   FUN_00465da4(void);              /* parser apply */
extern void   FUN_003510b8(void);              /* parser advance */
extern sk_pair_t FUN_002b3b50(void);           /* pair advance */
extern void   FUN_003504ac(void);              /* parser settle */
extern void   FUN_00462b54(void);              /* vector enter */
extern void   FUN_003505e8(void);              /* vector step */
extern word_t FUN_003511cc();              /* vector step */
extern void   FUN_0046418c(void);              /* vec store */
extern void   FUN_00465160(word_t);             /* vec store */
extern void   FUN_003508fc(void);              /* parse apply */
extern void   FUN_0042fe0c(void);              /* parse helper */
extern void   FUN_00352840(word_t);            /* parse helper */
extern word_t FUN_002a3e64();              /* scan helper */
extern void   FUN_00351a50(void);              /* consume helper */
extern void   FUN_00462974(word_t);            /* buf discard */
extern word_t FUN_00466468();   /* was word_t(void) */
extern void   FUN_00464000(void);              /* vec grow */
extern void   FUN_004634f4(word_t);            /* range check */
extern void   FUN_00465890(void);              /* loop probe */
extern void   FUN_00463878(void);              /* commit */
extern void   FUN_003514e8(void);              /* parse reject */
extern void   FUN_00351d18(void);              /* parse finalise */
extern void   FUN_004628f4(void);              /* token apply */
extern void   FUN_0046389c(void);              /* trace */
extern sk_pair_t FUN_0046589c();              /* trace */
extern void   FUN_00464d74(word_t);            /* vec count bump */
extern word_t FUN_00462ba8();   /* was word_t(void) */
extern word_t FUN_00350878();            /* settle */
extern void   FUN_00464ae8(word_t);            /* frame leave */
extern void   FUN_00463648(void);              /* record enter */
extern sk_pair_t FUN_00463444(word_t *);       /* record pair */
extern word_t FUN_0042f584();  /* state push */
extern void   FUN_00351b38(word_t);            /* parse token */
extern void   FUN_000abad0(void);              /* parse helper */
extern void   FUN_00350b3c(void);              /* parse advance */
extern sk_pair_t FUN_00350af4(void);           /* pair advance */
extern void   FUN_00462a5c(void);              /* token consume */
extern void   FUN_004655a8(void);              /* frame helper */
extern word_t FUN_00463014();            /* unknown-group printf */
extern void   FUN_00463290(void);              /* obj probe */
extern word_t FUN_00461cb8();          /* obj store */
extern void   FUN_00461a10(word_t *);          /* result classify */
extern void   FUN_00459024(word_t *, word_t *);/* elem fetch */
extern void   FUN_0045904c(word_t *);          /* elem store */
extern void   FUN_00464e70(word_t *);          /* elem next */
extern void   FUN_00463f4c(word_t, word_t *);  /* elem commit */
extern void   FUN_00462e44(void);              /* vec grow hint */
extern void   FUN_00352480(word_t, word_t);    /* vec grow */
extern word_t FUN_00462f6c();   /* was word_t(void) */
extern void   FUN_00465d48(void);              /* result ok */
extern void   FUN_00463fac(void);              /* parse end */
extern void   FUN_0042ffec(void);              /* parse helper */
extern void   FUN_0035292c(void);              /* parse helper */
extern void   FUN_004627f4(void);              /* token fetch */
extern void   FUN_00462d48(word_t *);          /* record begin */
extern void   FUN_0041653c(void);              /* record mid */
extern void   FUN_00461a9c(word_t *);          /* record end */
extern void   FUN_00463970(void);              /* elem check */
extern void   FUN_0046527c(void);              /* elem check */
extern void   FUN_00462f5c(void);              /* elem guard */
extern void   FUN_00462b2c(void);              /* elem guard */
extern void   FUN_00461a60(word_t *);          /* result empty */
extern void   FUN_00461a38(word_t *);          /* result merge */
extern void   FUN_00461a24(word_t *);          /* result copy */
extern void   FUN_00461a4c(word_t *);          /* result copy */
extern void   FUN_00461ac4(word_t *);          /* result copy */
extern void   FUN_00461ad8(word_t *);          /* result copy */
extern void   FUN_00461ab0(void);              /* result init */
extern void   FUN_004618f4(word_t *);          /* result clear */
extern void   FUN_00461820(word_t *);          /* result clear */
extern void   FUN_004619c4(word_t *);          /* result finalise */
extern void   FUN_00462eac(word_t *);          /* record commit */
extern void   FUN_00458bc4(word_t *, word_t);  /* region fetch */
extern void   FUN_00458c50(word_t *, char *);  /* region store */
extern void   FUN_00458c60(word_t *);          /* region fetch */
extern void   FUN_00461a90(char *);            /* region finalise */
extern void   FUN_00461a24(word_t *);          /* result copy */
extern void   FUN_00464adc(word_t *);          /* frame init */
extern void   FUN_00464f84(word_t *, word_t *);/* frame fill */
extern void   FUN_00462884(word_t);            /* lock acquire */
extern void   FUN_00464a8c(void);              /* frame save */
extern void   FUN_00464ab8(void);              /* frame save */
extern void   FUN_004636e8(word_t *);          /* state fetch */
extern void   FUN_00464e64(void);              /* frame step */
extern void   FUN_00351744(word_t);            /* parse enter */
extern void   FUN_00462988(void);              /* token fetch */
extern void   FUN_00464948(void);              /* frame save */
extern void   FUN_004652e4(void);              /* frame check */
extern void   FUN_00462d98(void);              /* parse enter */
extern void   FUN_00463534(word_t);            /* parse probe */
extern void   FUN_0042f890(void);              /* parse helper */
extern void   FUN_00437eec(word_t *, int, int);/* state build */
extern void   FUN_003535a8(void);              /* parse advance */
extern void   FUN_00463668(void);              /* state settle */
extern void   FUN_00435ecc(word_t *);          /* obj build */
extern void   FUN_004619c4(word_t *);          /* result finalise */
extern void   FUN_00461a24(word_t *);          /* result copy */
extern void   FUN_00463dbc(void);              /* loop enter */
extern void   FUN_003524a4(void);              /* parse advance */
extern void   FUN_00462a5c(void);              /* token consume */
extern void   FUN_00461a38(word_t *);          /* result merge */
extern void   FUN_00463e10(void);              /* parse end */
extern void   FUN_00458bc4(word_t *, word_t);  /* region fetch */
extern void   FUN_004642a8(void);              /* frame helper */
extern void   FUN_004642e8(word_t);            /* frame helper */
extern void   FUN_00464268(void);              /* frame helper */
extern void   FUN_00462d48(word_t *);          /* record begin */
extern sk_pair_t FUN_0041e21c(word_t, word_t); /* obj lookup */
extern sk_pair_t thunk_pair(void);             /* thunk_FUN_002b74c0 */
extern sk_pair_t FUN_00465920(void);           /* pair fetch */
extern sk_pair_t FUN_00437d54(void);           /* pair fetch */
extern word_t   FUN_0045636c();                /* vec grow (unspecified) */
extern sk_pair_t FUN_00350a04();            /* parse enter */
extern void     FUN_00464b20(word_t *);        /* frame init */
extern void     FUN_00462710(word_t);          /* buf discard */
extern word_t   FUN_0006b3f4();                 /* vec state op */
extern word_t   FUN_0008e500();                 /* exit */
extern sk_pair_t FUN_0008e518();
extern word_t FUN_0015e4f8();   /* was word_t() */
extern sk_pair_t FUN_004339a8(void);           /* state build pair */
extern word_t FUN_000dbed0();              /* vec grow */

/* Shared in-slice mutators (defined below / cross-referenced). */
extern void   sk_parse_begin(void);            /* FUN_00462d0c */
extern void   sk_parse_commit(void);           /* FUN_00463bc8 */
extern word_t sk_acquire_state(word_t, word_t);/* FUN_0042f670 (bit0) */
extern word_t sk_acquire_probe(word_t);        /* FUN_0042ec68 */
extern void   sk_parse_helper(void);           /* FUN_0042fd4c */
extern uint32_t sk_delim_probe(sk_parser_t *, word_t *); /* FUN_0043a300 */

extern word_t FUN_00002534();   /* was word_t() */
extern word_t FUN_000026e8();   /* was word_t() */
extern word_t FUN_00027754();   /* was word_t() */
extern word_t FUN_000277b8();   /* was word_t() */
extern word_t FUN_00068e14();   /* was word_t() */
extern word_t FUN_00069770();   /* was word_t() */
extern word_t FUN_00069970();   /* was word_t() */
extern word_t FUN_0006a374();   /* was word_t() */
extern word_t FUN_0006a4c0();   /* was word_t() */
extern word_t FUN_0006b42c();   /* was word_t() */
extern word_t FUN_0006b674();   /* was word_t() */
extern word_t FUN_0006b6a0();   /* was word_t() */
extern word_t FUN_00072178();   /* was word_t() */
extern word_t FUN_00077894();   /* was word_t() */
extern word_t FUN_000778b4();   /* was word_t() */
extern word_t FUN_0007c028();   /* was word_t() */
extern word_t FUN_0007c1a4();   /* was word_t() */
extern word_t FUN_0007c1c4();   /* was word_t() */
extern word_t FUN_0008409c();   /* was word_t() */
extern word_t FUN_00084174();   /* was word_t() */
extern word_t FUN_00084180();   /* was word_t() */
extern sk_pair_t FUN_00084220();   /* was word_t() */
extern word_t FUN_00084234();   /* was word_t() */
extern word_t FUN_0009461c();   /* was word_t() */
extern word_t FUN_0009e218();   /* was word_t() */
extern word_t FUN_000a6bb8();   /* was word_t() */
extern word_t FUN_000a6f88();   /* was word_t() */
extern word_t FUN_000a6fe0();   /* was word_t() */
extern word_t FUN_000aa4ec();   /* was word_t() */
extern word_t FUN_000b2260();   /* was word_t() */
extern word_t FUN_000b430c();   /* was word_t() */
extern word_t FUN_000b4390();   /* was word_t() */
extern word_t FUN_000b43d0();   /* was word_t() */
extern word_t FUN_000b43e8();   /* was word_t() */
extern word_t FUN_000b4528();   /* was word_t() */
extern word_t FUN_000b4594();   /* was word_t() */
extern word_t FUN_000b45b0();   /* was word_t() */
extern word_t FUN_000dbbe0();   /* was word_t() */
extern word_t FUN_000dbc98();   /* was word_t() */
extern word_t FUN_000dbd0c();   /* was word_t() */
extern word_t FUN_000e72b0();   /* was word_t() */
extern word_t FUN_000e72d4();   /* was word_t() */
extern word_t FUN_000f4ae8();   /* was word_t() */
extern word_t FUN_00100c04();   /* was word_t() */
extern word_t FUN_00100e34();   /* was word_t() */
extern word_t FUN_00100efc();   /* was word_t() */
extern word_t FUN_00117cc4();   /* was word_t() */
extern word_t FUN_0014ae44();   /* was word_t() */
extern word_t FUN_0016749c();   /* was word_t() */
extern word_t FUN_001a6a8c();   /* was word_t() */
extern word_t FUN_001a84f4();   /* was word_t() */
extern word_t FUN_001a8564();   /* was word_t() */
extern word_t FUN_001ae8a8();   /* was word_t() */
extern word_t FUN_001b1780();   /* was word_t() */
extern word_t FUN_001b9084();   /* was word_t() */
extern sk_pair_t FUN_001bc440();   /* was word_t() */
extern word_t FUN_001ee018();   /* was word_t() */
extern word_t FUN_00205844();   /* was word_t() */
extern word_t FUN_002298d4();   /* was word_t() */
extern word_t FUN_0022d2f4();   /* was word_t() */
extern word_t FUN_0024917c();   /* was word_t() */
extern word_t FUN_0024d9ac();   /* was word_t() */
extern word_t FUN_002a4ab4();   /* was word_t() */
extern sk_pair_t FUN_002aca00();   /* was word_t() */
extern sk_pair_t FUN_002acbb8();   /* was word_t() */
extern word_t FUN_002b74c0();   /* was word_t() */
extern word_t FUN_002bc2dc();   /* was word_t() */
extern word_t FUN_002bd724();   /* was word_t() */
extern word_t FUN_002bd8f0();   /* was word_t() */
extern word_t FUN_002bd9ac();   /* was word_t() */
extern word_t FUN_002bd9cc();   /* was word_t() */
extern word_t FUN_002bdc7c();   /* was word_t() */
extern word_t FUN_00310e08();   /* was word_t() */
extern word_t FUN_0031945c();   /* was word_t() */
extern word_t FUN_0031afcc();   /* was word_t() */
extern word_t FUN_0031b164();   /* was word_t() */
extern word_t FUN_0031e030();   /* was word_t() */
extern word_t FUN_0034ab10();   /* was word_t() */
extern word_t FUN_0034be0c();   /* was word_t() */
extern word_t FUN_0034d868();   /* was word_t() */
extern word_t FUN_0034e1ec();   /* was word_t() */
extern word_t FUN_0034ecc8();   /* was word_t() */
extern word_t FUN_0034fe80();   /* was word_t() */
extern word_t FUN_00350470();   /* was word_t() */
extern word_t FUN_003504a0();   /* was word_t() */
extern word_t FUN_003504c4();   /* was word_t() */
extern word_t FUN_003504d0();   /* was word_t() */
extern word_t FUN_00350560();   /* was word_t() */
extern word_t FUN_003505c4();   /* was word_t() */
extern word_t FUN_00350618();   /* was word_t() */
extern word_t FUN_00350624();   /* was word_t() */
extern word_t FUN_0035063c();   /* was word_t() */
extern word_t FUN_00350738();   /* was word_t() */
extern word_t FUN_003507bc();   /* was word_t() */
extern word_t FUN_003507e0();   /* was word_t() */
extern word_t FUN_00350914();   /* was word_t() */
extern word_t FUN_00350944();   /* was word_t() */
extern word_t FUN_00350968();   /* was word_t() */
extern word_t FUN_00350980();   /* was word_t() */
extern word_t FUN_0035098c();   /* was word_t() */
extern word_t FUN_00350998();   /* was word_t() */
extern word_t FUN_003509bc();   /* was word_t() */
extern word_t FUN_003509c8();   /* was word_t() */
extern word_t FUN_003509ec();   /* was word_t() */
extern word_t FUN_00350a28();   /* was word_t() */
extern word_t FUN_00350b18();   /* was word_t() */
extern word_t FUN_00350b90();   /* was word_t() */
extern word_t FUN_00350c2c();   /* was word_t() */
extern word_t FUN_00350c38();   /* was word_t() */
extern word_t FUN_00351100();   /* was word_t() */
extern word_t FUN_003511d8();   /* was word_t() */
extern word_t FUN_003511f0();   /* was word_t() */
extern word_t FUN_00351238();   /* was word_t() */
extern word_t FUN_00351274();   /* was word_t() */
extern word_t FUN_00351354();   /* was word_t() */
extern word_t FUN_003516d8();   /* was word_t() */
extern sk_pair_t FUN_00351714();
extern word_t FUN_003517c0();   /* was word_t() */
extern word_t FUN_0035187c();   /* was word_t() */
extern word_t FUN_0035199c();   /* was word_t() */
extern word_t FUN_003519a8();   /* was word_t() */
extern word_t FUN_00351b78();   /* was word_t() */
extern word_t FUN_00351cd0();   /* was word_t() */
extern word_t FUN_00351d30();   /* was word_t() */
extern word_t FUN_00351da8();   /* was word_t() */
extern word_t FUN_00351e20();   /* was word_t() */
extern word_t FUN_00352c4c();   /* was word_t() */
extern word_t FUN_00352c80();   /* was word_t() */
extern word_t FUN_003534e0();   /* was word_t() */
extern word_t FUN_00353a78();   /* was word_t() */
extern word_t FUN_00353abc();   /* was word_t() */
extern word_t FUN_00353c30();   /* was word_t() */
extern word_t FUN_00354410();   /* was word_t() */
extern word_t FUN_00354828();   /* was word_t() */
extern word_t FUN_00355538();   /* was word_t() */
extern word_t FUN_00355a58();   /* was word_t() */
extern word_t FUN_003562d4();   /* was word_t() */
extern word_t FUN_00356328();   /* was word_t() */
extern word_t FUN_00356c6c();   /* was word_t() */
extern word_t FUN_00359018();   /* was word_t() */
extern word_t FUN_0035aba4();   /* was word_t() */
extern word_t FUN_00365b6c();   /* was word_t() */
extern sk_pair_t FUN_0036993c();   /* was word_t() */
extern word_t FUN_0036b340();   /* was word_t() */
extern word_t FUN_00377824();   /* was word_t() */
extern word_t FUN_00377bec();   /* was word_t() */
extern word_t FUN_003a25e0();   /* was word_t() */
extern sk_pair_t FUN_003f8224();   /* was word_t() */
extern word_t FUN_004080b0();   /* was word_t() */
extern word_t FUN_0040feac();   /* was word_t() */
extern word_t FUN_0040ff40();   /* was word_t() */
extern word_t FUN_004107e4();   /* was word_t() */
extern word_t FUN_004108a0();   /* was word_t() */
extern sk_pair_t FUN_00411a54();   /* was word_t() */
extern word_t FUN_00411bbc();   /* was word_t() */
extern word_t FUN_00411bfc();   /* was word_t() */
extern word_t FUN_00411c8c();   /* was word_t() */
extern word_t FUN_00411cc4();   /* was word_t() */
extern word_t FUN_00412694();   /* was word_t() */
extern word_t FUN_00412d5c();   /* was word_t() */
extern sk_pair_t FUN_0044c918();   /* was word_t() */
extern word_t FUN_00414644();   /* was word_t() */
extern word_t FUN_0041465c();   /* was word_t() */
extern word_t FUN_004176ec();   /* was word_t() */
extern word_t FUN_00417998();   /* was word_t() */
extern word_t FUN_00419d98();   /* was word_t() */
extern word_t FUN_00419f24();   /* was word_t() */
extern word_t FUN_0041b088();   /* was word_t() */
extern word_t FUN_0041c1d8();   /* was word_t() */
extern word_t FUN_0041ca38();   /* was word_t() */
extern word_t FUN_00429430();   /* was word_t() */
extern word_t FUN_00429984();   /* was word_t() */
extern sk_pair_t FUN_0042c060(); /* was word_t() */
extern word_t FUN_0042c11c();   /* was word_t() */
extern word_t FUN_0042c5a4();   /* was word_t() */
extern word_t FUN_0042dc90();   /* was word_t() */
extern word_t FUN_0042e930();   /* was word_t() */
extern word_t FUN_0042ed6c();   /* was word_t() */
extern sk_pair_t FUN_0042f020();   /* was word_t() */
extern word_t FUN_0042f1f0();   /* was word_t() */
extern word_t FUN_0042f514();   /* was word_t() */
extern word_t FUN_0042ffac();   /* was word_t() */
extern word_t FUN_004301e0();   /* was word_t() */
extern word_t FUN_004303c4();   /* was word_t() */
extern word_t FUN_00430bf4();   /* was word_t() */
extern word_t FUN_0043152c();   /* was word_t() */
extern word_t FUN_004323ac();   /* was word_t() */
extern word_t FUN_004327c4();   /* was word_t() */
extern word_t FUN_00432c48();   /* was word_t() */
extern word_t FUN_00432ed4();   /* was word_t() */
extern word_t FUN_00433938();   /* was word_t() */
extern sk_pair_t FUN_0042fc4c();
extern word_t FUN_004340b0();   /* was word_t() */
extern word_t FUN_004345a4();   /* was word_t() */
extern word_t FUN_00434af4();   /* was word_t() */
extern sk_pair_t FUN_00434054();
extern sk_pair_t FUN_00435110();
extern word_t FUN_004372d4();   /* was word_t() */
extern word_t FUN_004379bc();   /* was word_t() */
extern word_t FUN_00438328();   /* was word_t() */
extern word_t FUN_00438f54();   /* was word_t() */
extern word_t FUN_00439348();   /* was word_t() */
extern word_t FUN_0043942c();   /* was word_t() */
extern word_t FUN_00439530();   /* was word_t() */
extern word_t FUN_004395fc();   /* was word_t() */
extern word_t FUN_00439a5c();   /* was word_t() */
extern word_t FUN_00439d74();   /* was word_t() */
extern word_t FUN_0043a478();   /* was word_t() */
extern word_t FUN_0043a538();   /* was word_t() */
extern word_t FUN_0043b5dc();   /* was word_t() */
extern word_t FUN_0043bd90();   /* was word_t() */
extern word_t FUN_0043c4d4();   /* was word_t() */
extern word_t FUN_0043c58c();   /* was word_t() */
extern word_t FUN_0043c8f8();   /* was word_t() */
extern word_t FUN_0043cd98();   /* was word_t() */
extern word_t FUN_0043d490();   /* was word_t() */
extern word_t FUN_0043e334();   /* was word_t() */
extern word_t FUN_0043ed70();   /* was word_t() */
extern word_t FUN_0043f454();   /* was word_t() */
extern word_t FUN_0043f4ec();   /* was word_t() */
extern word_t FUN_0043f634();   /* was word_t() */
extern word_t FUN_0043f770();   /* was word_t() */
extern word_t FUN_0043fd04();   /* was word_t() */
extern word_t FUN_00440820();   /* was word_t() */
extern word_t FUN_00440ce8();   /* was word_t() */
extern word_t FUN_00440fb0();   /* was word_t() */
extern word_t FUN_00441034();   /* was word_t() */
extern word_t FUN_0044136c();   /* was word_t() */
extern word_t FUN_00441688();   /* was word_t() */
extern word_t FUN_00441b40();   /* was word_t() */
extern word_t FUN_00441ff8();   /* was word_t() */
extern word_t FUN_004421ac();   /* was word_t() */
extern word_t FUN_004452a8();   /* was word_t() */
extern word_t FUN_00445518();   /* was word_t() */
extern word_t FUN_00445588();   /* was word_t() */
extern word_t FUN_004455f8();   /* was word_t() */
extern word_t FUN_00445724();   /* was word_t() */
extern word_t FUN_0044587c();   /* was word_t() */
extern sk_pair_t FUN_004458b0();   /* was word_t() */
extern word_t FUN_00445e64();   /* was word_t() */
extern word_t FUN_00445eec();   /* was word_t() */
extern word_t FUN_00446028();   /* was word_t() */
extern word_t FUN_004460cc();   /* was word_t() */
extern word_t FUN_004461bc();   /* was word_t() */
extern word_t FUN_0044632c();   /* was word_t() */
extern word_t FUN_00446b64();   /* was word_t() */
extern word_t FUN_00446bd4();   /* was word_t() */
extern word_t FUN_00447144();   /* was word_t() */
extern word_t FUN_0044791c();   /* was word_t() */
extern word_t FUN_00448298();   /* was word_t() */
extern word_t FUN_00448758();   /* was word_t() */
extern word_t FUN_00448934();   /* was word_t() */
extern word_t FUN_00448aac();   /* was word_t() */
extern word_t FUN_00448c1c();   /* was word_t() */
extern word_t FUN_00448cc8();   /* was word_t() */
extern word_t FUN_00448d28();   /* was word_t() */
extern word_t FUN_00448d7c();   /* was word_t() */
extern word_t FUN_00448dd8();   /* was word_t() */
extern word_t FUN_00448e6c();   /* was word_t() */
extern word_t FUN_00448f1c();   /* was word_t() */
extern word_t FUN_00448fd0();   /* was word_t() */
extern word_t FUN_00449034();   /* was word_t() */
extern word_t FUN_0044911c();   /* was word_t() */
extern word_t FUN_004491c4();   /* was word_t() */
extern word_t FUN_00449238();   /* was word_t() */
extern word_t FUN_0044929c();   /* was word_t() */
extern word_t FUN_00449320();   /* was word_t() */
extern word_t FUN_0044938c();   /* was word_t() */
extern word_t FUN_004493ec();   /* was word_t() */
extern word_t FUN_00449444();   /* was word_t() */
extern word_t FUN_0044948c();   /* was word_t() */
extern word_t FUN_00449808();   /* was word_t() */
extern word_t FUN_00449acc();   /* was word_t() */
extern word_t FUN_00449d70();   /* was word_t() */
extern word_t FUN_0044a128();   /* was word_t() */
extern word_t FUN_0044a420();   /* was word_t() */
extern word_t FUN_0044a73c();   /* was word_t() */
extern word_t FUN_0044a9a0();   /* was word_t() */
extern word_t FUN_0044ab14();   /* was word_t() */
extern word_t FUN_0044abb0();   /* was word_t() */
extern word_t FUN_0044ac3c();   /* was word_t() */
extern word_t FUN_0044ac7c();   /* was word_t() */
extern word_t FUN_0044ad60();   /* was word_t() */
extern word_t FUN_0044ad98();   /* was word_t() */
extern word_t FUN_0044ae38();   /* was word_t() */
extern word_t FUN_0044ae70();   /* was word_t() */
extern word_t FUN_0044af28();   /* was word_t() */
extern word_t FUN_0044afa0();   /* was word_t() */
extern word_t FUN_0044afa4();   /* was word_t() */
extern word_t FUN_0044afc8();   /* was word_t() */
extern word_t FUN_0044b000();   /* was word_t() */
extern word_t FUN_0044b088();   /* was word_t() */
extern word_t FUN_0044b0c4();   /* was word_t() */
extern word_t FUN_0044b0f0();   /* was word_t() */
extern word_t FUN_0044b200();   /* was word_t() */
extern word_t FUN_0044b23c();   /* was word_t() */
extern word_t FUN_0044b324();   /* was word_t() */
extern word_t FUN_0044b35c();   /* was word_t() */
extern word_t FUN_0044b478();   /* was word_t() */
extern word_t FUN_0044b4b4();   /* was word_t() */
extern word_t FUN_0044b4ec();   /* was word_t() */
extern word_t FUN_0044b80c();   /* was word_t() */
extern word_t FUN_0044b844();   /* was word_t() */
extern word_t FUN_0044b894();   /* was word_t() */
extern word_t FUN_0044b8d0();   /* was word_t() */
extern word_t FUN_0044bac4();   /* was word_t() */
extern word_t FUN_0044bcdc();   /* was word_t() */
extern word_t FUN_0044bd08();   /* was word_t() */
extern word_t FUN_0044bd44();   /* was word_t() */
extern sk_pair_t FUN_0044bdc8();
extern sk_pair_t FUN_00463f94();
extern sk_pair_t FUN_00464140();
extern sk_pair_t FUN_00463e04();   /* was word_t() */
extern word_t FUN_0044be8c();   /* was word_t() */
extern word_t FUN_0044bec4();   /* was word_t() */
extern word_t FUN_0044bfc0();   /* was word_t() */
extern word_t FUN_0044bff0();   /* was word_t() */
extern word_t FUN_0044c3d0();   /* was word_t() */
extern word_t FUN_0044c40c();   /* was word_t() */
extern word_t FUN_0044c444();   /* was word_t() */
extern word_t FUN_0044c4d4();   /* was word_t() */
extern word_t FUN_0044c50c();   /* was word_t() */
extern word_t FUN_0044c5d8();   /* was word_t() */
extern word_t FUN_0044c8e8();   /* was word_t() */
extern sk_pair_t FUN_0046589c();   /* was word_t() */
extern word_t FUN_0044c9c4();   /* was word_t() */
extern word_t FUN_0044ca08();   /* was word_t() */
extern word_t FUN_0044ca2c();   /* was word_t() */
extern sk_pair_t FUN_0044e55c();   /* was word_t() */
extern word_t FUN_0045027c();   /* was word_t() */
extern word_t FUN_00455d8c();   /* was word_t() */
extern word_t FUN_00455fe4();   /* was word_t() */
extern word_t FUN_00456238();   /* was word_t() */
extern word_t FUN_004564e4();   /* was word_t() */
extern word_t FUN_0045659c();   /* was word_t() */
extern word_t FUN_004567d8();   /* was word_t() */
extern word_t FUN_0045694c();   /* was word_t() */
extern word_t FUN_00456cd8();   /* was word_t() */
extern word_t FUN_004588cc();   /* was word_t() */
extern word_t FUN_004589bc();   /* was word_t() */
extern word_t FUN_004589e8();   /* was word_t() */
extern word_t FUN_004589f8();   /* was word_t() */
extern word_t FUN_00458a20();   /* was word_t() */
extern word_t FUN_00458a30();   /* was word_t() */
extern word_t FUN_00458a90();   /* was word_t() */
extern word_t FUN_00458aa0();   /* was word_t() */
extern word_t FUN_00458ac8();   /* was word_t() */
extern word_t FUN_00458af8();   /* was word_t() */
extern word_t FUN_00458b14();   /* was word_t() */
extern word_t FUN_00458c98();   /* was word_t() */
extern word_t FUN_00458d04();   /* was word_t() */
extern word_t FUN_00458d10();   /* was word_t() */
extern word_t FUN_00458d30();   /* was word_t() */
extern word_t FUN_00458d40();   /* was word_t() */
extern word_t FUN_00458e28();   /* was word_t() */
extern word_t FUN_00458e50();   /* was word_t() */
extern word_t FUN_00459034();   /* was word_t() */
extern word_t FUN_00459074();   /* was word_t() */
extern word_t FUN_0045908c();   /* was word_t() */
extern word_t FUN_00460d50();   /* was word_t() */
extern word_t FUN_00460dcc();   /* was word_t() */
extern word_t FUN_00460e68();   /* was word_t() */
extern word_t FUN_0046128c();   /* was word_t() */
extern word_t FUN_004614cc();   /* was word_t() */
extern word_t FUN_00461590();   /* was word_t() */
extern word_t FUN_004616d4();   /* was word_t() */
extern word_t FUN_00461708();   /* was word_t() */
extern word_t FUN_00461738();   /* was word_t() */
extern word_t FUN_00461768();   /* was word_t() */
extern word_t FUN_00461798();   /* was word_t() */
extern word_t FUN_004617c4();   /* was word_t() */
extern word_t FUN_004617d4();   /* was word_t() */
extern word_t FUN_004617f0();   /* was word_t() */
extern word_t FUN_00461854();   /* was word_t() */
extern word_t FUN_004618bc();   /* was word_t() */
extern word_t FUN_004618dc();   /* was word_t() */
extern word_t FUN_00461924();   /* was word_t() */
extern word_t FUN_0046195c();   /* was word_t() */
extern word_t FUN_00461994();   /* was word_t() */
extern word_t FUN_004619fc();   /* was word_t() */
extern word_t FUN_00461b00();   /* was word_t() */
extern word_t FUN_00461b14();   /* was word_t() */
extern word_t FUN_00461b28();   /* was word_t() */
extern word_t FUN_00461b3c();   /* was word_t() */
extern word_t FUN_00461b50();   /* was word_t() */
extern word_t FUN_00461b78();   /* was word_t() */
extern word_t FUN_00461bd4();   /* was word_t() */
extern word_t FUN_00462728();   /* was word_t() */
extern word_t FUN_00462740();   /* was word_t() */
extern word_t FUN_00462770();   /* was word_t() */
extern word_t FUN_004627a0();   /* was word_t() */
extern word_t FUN_004627b8();   /* was word_t() */
extern word_t FUN_00462810();   /* was word_t() */
extern word_t FUN_00462898();   /* was word_t() */
extern word_t FUN_004628d8();   /* was word_t() */
extern word_t FUN_00462908();   /* was word_t() */
extern word_t FUN_0046295c();   /* was word_t() */
extern word_t FUN_004629b4();   /* was word_t() */
extern word_t FUN_004629cc();   /* was word_t() */
extern word_t FUN_004629e0();   /* was word_t() */
extern word_t FUN_00462a34();   /* was word_t() */
extern word_t FUN_00462a84();   /* was word_t() */
extern word_t FUN_00462a98();   /* was word_t() */
extern word_t FUN_00462abc();   /* was word_t() */
extern word_t FUN_00462b40();   /* was word_t() */
extern word_t FUN_00462cb0();   /* was word_t() */
extern word_t FUN_00462cd4();   /* was word_t() */
extern word_t FUN_00462e9c();   /* was word_t() */
extern word_t FUN_00462ee8();   /* was word_t() */
extern word_t FUN_00462f0c();   /* was word_t() */
extern word_t FUN_00462f4c();   /* was word_t() */
extern word_t FUN_00462f8c();   /* was word_t() */
extern word_t FUN_00462fd4();   /* was word_t() */
extern word_t FUN_004630b0();   /* was word_t() */
extern word_t FUN_004630c4();   /* was word_t() */
extern word_t FUN_00463144();   /* was word_t() */
extern sk_pair_t FUN_00463194();
extern word_t FUN_004631a8();   /* was word_t() */
extern word_t FUN_004631fc();   /* was word_t() */
extern word_t FUN_00463210();   /* was word_t() */
extern word_t FUN_00463268();   /* was word_t() */
extern word_t FUN_004632a4();   /* was word_t() */
extern sk_pair_t FUN_004632e0();   /* was word_t() */
extern word_t FUN_004632f4();   /* was word_t() */
extern word_t FUN_004633e0();   /* was word_t() */
extern sk_pair_t FUN_004634d4();   /* was word_t() */
extern word_t FUN_00463520();   /* was word_t() */
extern word_t FUN_004635a4();   /* was word_t() */
extern word_t FUN_004635d4();   /* was word_t() */
extern word_t FUN_004635e0();   /* was word_t() */
extern word_t FUN_00463658();   /* was word_t() */
extern word_t FUN_004636a0();   /* was word_t() */
extern word_t FUN_004636b0();   /* was word_t() */
extern word_t FUN_004636cc();   /* was word_t() */
extern word_t FUN_004636f8();   /* was word_t() */
extern word_t FUN_00463708();   /* was word_t() */
extern word_t FUN_0046373c();   /* was word_t() */
extern word_t FUN_00463778();   /* was word_t() */
extern word_t FUN_004637b4();   /* was word_t() */
extern word_t FUN_004637c8();   /* was word_t() */
extern word_t FUN_004637f0();   /* was word_t() */
extern word_t FUN_00463824();   /* was word_t() */
extern word_t FUN_00463830();   /* was word_t() */
extern word_t FUN_00463844();   /* was word_t() */
extern word_t FUN_00463864();   /* was word_t() */
extern word_t FUN_004638a8();   /* was word_t() */
extern word_t FUN_004638c0();   /* was word_t() */
extern word_t FUN_0046397c();   /* was word_t() */
extern word_t FUN_004639b0();   /* was word_t() */
extern word_t FUN_004639c8();   /* was word_t() */
extern word_t FUN_004639d8();   /* was word_t() */
extern word_t FUN_004639e4();   /* was word_t() */
extern word_t FUN_004639fc();   /* was word_t() */
extern word_t FUN_00463a58();   /* was word_t() */
extern word_t FUN_00463a68();   /* was word_t() */
extern word_t FUN_00463a78();   /* was word_t() */
extern word_t FUN_00463ab8();   /* was word_t() */
extern word_t FUN_00463cc8();   /* was word_t() */
extern word_t FUN_00463dd4();   /* was word_t() */
extern word_t FUN_00463de0();   /* was word_t() */
extern word_t FUN_00463df8();   /* was word_t() */
extern sk_pair_t FUN_00413b68();   /* was word_t() */
extern word_t FUN_00463f64();   /* was word_t() */
extern sk_pair_t FUN_00463f94();
extern word_t FUN_00463fb8();   /* was word_t() */
extern word_t FUN_00463fd0();   /* was word_t() */
extern word_t FUN_00463fe8();   /* was word_t() */
extern word_t FUN_0046400c();   /* was word_t() */
extern word_t FUN_00464040();   /* was word_t() */
extern word_t FUN_004640a4();   /* was word_t() */
extern word_t FUN_004640f0();   /* was word_t() */
extern word_t FUN_00464134();   /* was word_t() */
extern sk_pair_t FUN_003512c0();
extern word_t FUN_0046414c();   /* was word_t() */
extern word_t FUN_00464234();   /* was word_t() */
extern word_t FUN_00464248();   /* was word_t() */
extern word_t FUN_004642f8();   /* was word_t() */
extern word_t FUN_00464378();   /* was word_t() */
extern word_t FUN_00464388();   /* was word_t() */
extern word_t FUN_004643a0();   /* was word_t() */
extern word_t FUN_004643cc();   /* was word_t() */
extern word_t FUN_004644c0();   /* was word_t() */
extern word_t FUN_004644f8();   /* was word_t() */
extern word_t FUN_00464520();   /* was word_t() */
extern word_t FUN_00464538();   /* was word_t() */
extern word_t FUN_00464568();   /* was word_t() */
extern word_t FUN_00464588();   /* was word_t() */
extern word_t FUN_004645ec();   /* was word_t() */
extern word_t FUN_00464608();   /* was word_t() */
extern word_t FUN_004647c0();   /* was word_t() */
extern word_t FUN_004647f4();   /* was word_t() */
extern word_t FUN_00464804();   /* was word_t() */
extern word_t FUN_004648a0();   /* was word_t() */
extern word_t FUN_004649cc();   /* was word_t() */
extern word_t FUN_00464a08();   /* was word_t() */
extern word_t FUN_00464a38();   /* was word_t() */
extern word_t FUN_00464a74();   /* was word_t() */
extern word_t FUN_00464a98();   /* was word_t() */
extern word_t FUN_00464ce4();   /* was word_t() */
extern word_t FUN_00464cf4();   /* was word_t() */
extern word_t FUN_00464d18();   /* was word_t() */
extern word_t FUN_00464d44();   /* was word_t() */
extern word_t FUN_00464d50();   /* was word_t() */
extern word_t FUN_00464d80();   /* was word_t() */
extern word_t FUN_00464dc0();   /* was word_t() */
extern word_t FUN_00464e1c();   /* was word_t() */
extern word_t FUN_00464e40();   /* was word_t() */
extern word_t FUN_00464e7c();   /* was word_t() */
extern word_t FUN_00464e88();   /* was word_t() */
extern word_t FUN_00464eb0();   /* was word_t() */
extern word_t FUN_00464ed0();   /* was word_t() */
extern word_t FUN_00464ee4();   /* was word_t() */
extern word_t FUN_00464f24();   /* was word_t() */
extern word_t FUN_00464f4c();   /* was word_t() */
extern word_t FUN_00465010();   /* was word_t() */
extern word_t FUN_00465038();   /* was word_t() */
extern word_t FUN_00465054();   /* was word_t() */
extern word_t FUN_00465088();   /* was word_t() */
extern word_t FUN_004650c8();   /* was word_t() */
extern word_t FUN_0046511c();   /* was word_t() */
extern word_t FUN_00465128();   /* was word_t() */
extern word_t FUN_00465150();   /* was word_t() */
extern word_t FUN_00465170();   /* was word_t() */
extern word_t FUN_00465198();   /* was word_t() */
extern word_t FUN_004651a8();   /* was word_t() */
extern word_t FUN_004651b8();   /* was word_t() */
extern word_t FUN_00465294();   /* was word_t() */
extern word_t FUN_004652ac();   /* was word_t() */
extern word_t FUN_00465304();   /* was word_t() */
extern word_t FUN_00465314();   /* was word_t() */
extern word_t FUN_00465320();   /* was word_t() */
extern word_t FUN_00465330();   /* was word_t() */
extern word_t FUN_00465350();   /* was word_t() */
extern word_t FUN_00465360();   /* was word_t() */
extern word_t FUN_00465370();   /* was word_t() */
extern word_t FUN_00465390();   /* was word_t() */
extern word_t FUN_004653b0();   /* was word_t() */
extern word_t FUN_004653dc();   /* was word_t() */
extern word_t FUN_004653fc();   /* was word_t() */
extern word_t FUN_00465438();   /* was word_t() */
extern word_t FUN_00465448();   /* was word_t() */
extern word_t FUN_004654a8();   /* was word_t() */
extern word_t FUN_00465508();   /* was word_t() */
extern word_t FUN_00465524();   /* was word_t() */
extern word_t FUN_00465578();   /* was word_t() */
extern word_t FUN_004655c0();   /* was word_t() */
extern word_t FUN_004655d8();   /* was word_t() */
extern word_t FUN_004655f0();   /* was word_t() */
extern word_t FUN_00465680();   /* was word_t() */
extern word_t FUN_004656bc();   /* was word_t() */
extern word_t FUN_004656f8();   /* was word_t() */
extern word_t FUN_00465764();   /* was word_t() */
extern sk_pair_t FUN_00465788();
extern word_t FUN_004657ac();   /* was word_t() */
extern word_t FUN_004657b8();   /* was word_t() */
extern word_t FUN_00465800();   /* was word_t() */
extern word_t FUN_0046580c();   /* was word_t() */
extern word_t FUN_00465884();   /* was word_t() */
extern word_t FUN_004658c0();   /* was word_t() */
extern word_t FUN_00465908();   /* was word_t() */
extern word_t FUN_0046592c();   /* was word_t() */
extern word_t FUN_00465944();   /* was word_t() */
extern word_t FUN_00465974();   /* was word_t() */
extern word_t FUN_004659a4();   /* was word_t() */
extern word_t FUN_004659c8();   /* was word_t() */
extern word_t FUN_004659d4();   /* was word_t() */
extern word_t FUN_00465a70();   /* was word_t() */
extern word_t FUN_00465ad0();   /* was word_t() */
extern word_t FUN_00465af4();   /* was word_t() */
extern word_t FUN_00465b04();   /* was word_t() */
extern word_t FUN_00465b38();   /* was word_t() */
extern word_t FUN_00465b80();   /* was word_t() */
extern word_t FUN_00465ba0();   /* was word_t() */
extern word_t FUN_00465c00();   /* was word_t() */
extern word_t FUN_00465c44();   /* was word_t() */
extern word_t FUN_00465c50();   /* was word_t() */
extern word_t FUN_00465c68();   /* was word_t() */
extern word_t FUN_00465c74();   /* was word_t() */
extern word_t FUN_00465c80();   /* was word_t() */
extern word_t FUN_00465c8c();   /* was word_t() */
extern word_t FUN_00465cac();   /* was word_t() */
extern word_t FUN_00465d84();   /* was word_t() */
extern word_t FUN_00465d98();   /* was word_t() */
extern word_t FUN_00465dd0();   /* was word_t() */
extern word_t FUN_00465e04();   /* was word_t() */
extern word_t FUN_00465e2c();   /* was word_t() */
extern word_t FUN_00465e40();   /* was word_t() */
extern word_t FUN_00465e4c();   /* was word_t() */
extern word_t FUN_00465ed4();   /* was word_t() */
extern word_t FUN_00465f00();   /* was word_t() */
extern word_t FUN_00465f14();   /* was word_t() */
extern word_t FUN_00465f9c();   /* was word_t() */
extern word_t FUN_00465fa8();   /* was word_t() */
extern word_t FUN_00465fc8();   /* was word_t() */
extern word_t FUN_00465fd4();   /* was word_t() */
extern word_t FUN_00465ff4();   /* was word_t() */
extern word_t FUN_00466014();   /* was word_t() */
extern word_t FUN_00466054();   /* was word_t() */
extern word_t FUN_004660a0();   /* was word_t() */
extern word_t FUN_004660c0();   /* was word_t() */
extern word_t FUN_004660e0();   /* was word_t() */
extern word_t FUN_00466104();   /* was word_t() */
extern word_t FUN_00466124();   /* was word_t() */
extern word_t FUN_00466130();   /* was word_t() */
extern word_t FUN_00466148();   /* was word_t() */
extern word_t FUN_00466168();   /* was word_t() */
extern word_t FUN_00466190();   /* was word_t() */
extern word_t FUN_00466214();   /* was word_t() */
extern word_t FUN_00466244();   /* was word_t() */
extern word_t FUN_00466290();   /* was word_t() */
extern word_t FUN_00466300();   /* was word_t() */
extern word_t FUN_00466314();   /* was word_t() */
extern word_t FUN_00466348();   /* was word_t() */
extern word_t FUN_00466388();   /* was word_t() */
extern word_t FUN_004663ec();   /* was word_t() */
extern word_t FUN_00466408();   /* was word_t() */
extern word_t FUN_004664d0();   /* was word_t() */
extern word_t FUN_00466540();   /* was word_t() */
extern word_t FUN_00466594();   /* was word_t() */
extern word_t FUN_004665d0();   /* was word_t() */
extern word_t FUN_004665dc();   /* was word_t() */
extern word_t FUN_004665f4();   /* was word_t() */
extern word_t FUN_00466600();   /* was word_t() */
extern word_t FUN_0046660c();   /* was word_t() */
extern word_t FUN_00466618();   /* was word_t() */
extern word_t FUN_00466678();   /* was word_t() */
extern word_t FUN_004666a8();   /* was word_t() */
extern word_t FUN_004666e4();   /* was word_t() */
extern word_t FUN_004666f8();   /* was word_t() */
extern word_t FUN_0064e030();   /* was word_t() */
extern word_t FUN_0067f9a0();   /* was word_t() */

/* Unspecified-arg helper externs (K&R () form) so every call
 * site compiles; return types per observed register use. */
extern word_t FUN_0001a1c8();   /* was word_t() */
extern word_t FUN_00027724();   /* was word_t() */
extern word_t FUN_00086840();   /* was word_t() */
extern sk_pair_t FUN_0029fa0c();
extern word_t FUN_002a0cf8();   /* was word_t() */
extern sk_pair_t FUN_002b3b50();
extern sk_pair_t FUN_002b3f40();
extern word_t FUN_002b4120();   /* was word_t() */
extern sk_pair_t FUN_002b439c();
extern sk_pair_t FUN_00350aa0();
extern sk_pair_t FUN_00350af4();
extern sk_pair_t FUN_00351db4();
extern word_t FUN_00354744();   /* was word_t() */
extern word_t FUN_0036a940();   /* was word_t() */
extern word_t FUN_0036a9a0();   /* was word_t() */
extern word_t FUN_0036b118();   /* was word_t() */
extern word_t FUN_0036b270();   /* was word_t() */
extern word_t FUN_003a25d4();   /* was word_t() */
extern word_t FUN_003a261c();   /* was word_t() */
extern sk_pair_t FUN_0041e21c();
extern word_t FUN_0042f670();   /* was word_t() */
extern word_t FUN_0042f7d4();   /* was word_t() */
extern sk_pair_t FUN_004339a8();
extern sk_pair_t FUN_00437d54();
extern word_t FUN_0043a300();   /* was word_t() */
extern word_t FUN_00462ba8();   /* was word_t() */
extern word_t FUN_00462f6c();   /* was word_t() */
extern word_t FUN_00462fd4c();
extern word_t FUN_0046322c();   /* was word_t() */
extern sk_pair_t FUN_00463444();
extern sk_pair_t FUN_00464b04();
extern sk_pair_t FUN_00465920();
extern word_t FUN_00466074();   /* was word_t() */
extern word_t FUN_0046635c();   /* was word_t() */
extern word_t FUN_004663ac();   /* was word_t() */
extern word_t FUN_00466468();   /* was word_t() */
extern void   FUN_00002834();
extern void   FUN_00002850();
extern void   FUN_000a6f68();
extern void   FUN_000abad0();
extern word_t FUN_000dbed0();
extern word_t FUN_0015e4f8();   /* was word_t() */
extern word_t FUN_002a3e64();
extern void   FUN_003504ac();
extern void   FUN_00350518();
extern void   FUN_003505e8();
extern word_t FUN_00350878();
extern void   FUN_003508fc();
extern sk_pair_t FUN_00350a04();
extern void   FUN_00350b3c();
extern void   FUN_00350bfc();
extern void   FUN_003510b8();
extern void   FUN_003511a8();
extern word_t FUN_003511cc();
extern sk_pair_t FUN_003512c0();
extern void   FUN_003514e8();
extern void   FUN_00351744();
extern void   FUN_00351790();
extern void   FUN_00351a44();
extern void   FUN_00351a50();
extern void   FUN_00351a5c();
extern void   FUN_00351aec();
extern void   FUN_00351b38();
extern void   FUN_00351c7c();
extern void   FUN_00351d18();
extern void   FUN_00351e08();
extern void   FUN_00351f28();
extern void   FUN_00352480();
extern void   FUN_003524a4();
extern void   FUN_003524b0();
extern void   FUN_00352840();
extern void   FUN_0035292c();
extern void   FUN_003535a8();
extern void   FUN_003544c8();
extern void   FUN_00354ca8();
extern void   FUN_00355d90();
extern void   FUN_00356b5c();
extern void   FUN_0036b588();
extern void   FUN_0036b6ac();
extern void   FUN_0041653c();
extern void   FUN_0042ec68();
extern word_t FUN_0042f584();
extern sk_pair_t FUN_0042fc4c();
extern word_t FUN_0042fd4c();
extern void   FUN_0042fe0c();
extern void   FUN_0042ffec();
extern void   FUN_00430040();
extern void   FUN_00430d08();
extern void   FUN_00435ecc();
extern void   FUN_004368c0();
extern void   FUN_00437eec();
extern void   FUN_00455db8();
extern void   FUN_00458bc4();
extern void   FUN_00458c50();
extern void   FUN_00458c60();
extern void   FUN_00459024();
extern void   FUN_0045904c();
extern void   FUN_00461430();
extern void   FUN_00461820();
extern void   FUN_004618f4();
extern void   FUN_004619c4();
extern void   FUN_00461a10();
extern void   FUN_00461a24();
extern void   FUN_00461a38();
extern void   FUN_00461a4c();
extern void   FUN_00461a60();
extern void   FUN_00461a90();
extern void   FUN_00461a9c();
extern void   FUN_00461aa8();
extern void   FUN_00461ab0();
extern void   FUN_00461ac4();
extern void   FUN_00461ad8();
extern word_t FUN_00461cb8();
extern void   FUN_00462710();
extern void   FUN_00462788();
extern void   FUN_004627f4();
extern void   FUN_0046282c();
extern void   FUN_00462870();
extern void   FUN_00462884();
extern void   FUN_004628c4();
extern void   FUN_004628f4();
extern void   FUN_00462988();
extern void   FUN_00462a08();
extern void   FUN_00462a48();
extern void   FUN_00462a5c();
extern void   FUN_00462aac();
extern void   FUN_00462adc();
extern void   FUN_00462af0();
extern void   FUN_00462b2c();
extern void   FUN_00462b54();
extern void   FUN_00462b80();
extern void   FUN_00462d0c();
extern void   FUN_00462d48();
extern void   FUN_00462d98();
extern void   FUN_00462e44();
extern void   FUN_00462eac();
extern void   FUN_00462f24();
extern void   FUN_00462f3c();
extern void   FUN_00462f5c();
extern void   FUN_00462f890();
extern word_t FUN_00463014();
extern void   FUN_00463290();
extern void   FUN_004634f4();
extern void   FUN_00463514();
extern void   FUN_00463534();
extern void   FUN_00463540();
extern void   FUN_004635c8();
extern void   FUN_004635f0();
extern void   FUN_00463648();
extern void   FUN_00463668();
extern void   FUN_004636e8();
extern void   FUN_00463878();
extern void   FUN_0046389c();
extern void   FUN_00463970();
extern void   FUN_00463988();
extern void   FUN_00463bc8();
extern void   FUN_00463c0c();
extern void   FUN_00463dbc();
extern void   FUN_00463f4c();
extern void   FUN_00463fac();
extern void   FUN_00464000();
extern void   FUN_004640c4();
extern void   FUN_0046418c();
extern void   FUN_00464268();
extern void   FUN_004642a8();
extern void   FUN_004642e8();
extern void   FUN_004644dc();
extern void   FUN_00464918();
extern void   FUN_00464948();
extern void   FUN_004649fc();
extern void   FUN_00464a8c();
extern void   FUN_00464ab8();
extern void   FUN_00464adc();
extern void   FUN_00464ae8();
extern void   FUN_00464b20();
extern void   FUN_00464d5c();
extern void   FUN_00464d74();
extern void   FUN_00464e34();
extern void   FUN_00464e64();
extern void   FUN_00464e70();
extern void   FUN_00464f84();
extern void   FUN_00465160();
extern void   FUN_0046527c();
extern void   FUN_00465288();
extern void   FUN_004652e4();
extern void   FUN_00465540();
extern void   FUN_004655a8();
extern void   FUN_004657d0();
extern void   FUN_00465890();
extern sk_pair_t FUN_0046589c();
extern void   FUN_004659bc();
extern void   FUN_00465d48();
extern void   FUN_00465da4();
extern void   FUN_00465ddc();

extern word_t FUN_004578dc();
extern word_t FUN_00457994();
extern word_t FUN_00462a1c();
extern word_t FUN_00462b00();
extern word_t FUN_00462b6c();
extern word_t FUN_00462c04();
extern word_t FUN_00462d88();
extern word_t FUN_00463890();
extern word_t FUN_00463f74();

/* ================================================================== *
 * Slice 194 functions
 * ================================================================== */

/* FUN_0043a300 @ 0x43a300  (est. sk_delim_probe)
 * Delimiter probe for the parser tokenizer. Reads a token descriptor
 * (4 words) and asks sk_pair_fn whether the token is a structural
 * delimiter (lo^hi < 0x4000). Otherwise it compares the current
 * character (thisp->cur, register x20) plus the 0xe1... token tag
 * (register x19) against the ASCII delimiters '=', ':', '[', ']',
 * '}', '\' — returning 1 if the current char is one of them. Any
 * non-matching state advances the parser one delimiter at a time via
 * sk_acquire_state. Releases the token on the way out.
 * Confidence: medium
 * Notes: delimiter set 0x3d/0x3a/0x5b/0x5d/0x7d/0x5c; tag constant
 * 0xe100000000000000; helper chain FUN_00462788/FUN_002b439c/
 * FUN_00351e08 */
uint32_t sk_delim_probe(sk_parser_t *p, word_t *desc)
{
    word_t token = desc[1];
    sk_pair_t pr = sk_pair_fn(desc[2], desc[3], desc[0], token);
    uint32_t r = 1;
    if ((pr.lo ^ pr.hi) >= 0x4000) {
        sk_parse_begin();          /* FUN_00462788 */
        sk_token_acquire();        /* FUN_002b439c */
        sk_parse_pair_apply();     /* FUN_00351e08 */
        sk_token_release(token);
        /* current char/tag against '=' */
        if (!(p->cur == '=' && p->tag == SK_TAG_DELIM)) {
            sk_advance_to('='); /* FUN_00462b80 */
            if (!(sk_state_ok() & 1) &&
                !(p->cur == ':' && p->tag == SK_TAG_DELIM)) {
                sk_advance_to(':');   /* FUN_00462b80 */
                if (!(sk_state_ok() & 1) &&
                    !(p->cur == '[' && p->tag == SK_TAG_DELIM)) {
                    sk_advance_to('[');
                    if (!(sk_state_ok() & 1) &&
                        !(p->cur == ']' && p->tag == SK_TAG_DELIM)) {
                        sk_advance_to(']');
                        if (!(sk_state_ok() & 1) &&
                            !(p->cur == '}' && p->tag == SK_TAG_DELIM)) {
                            sk_advance_to('}');
                            if (!(sk_state_ok() & 1) &&
                                !(p->cur == '\\' && p->tag == SK_TAG_DELIM)) {
                                sk_advance_to('\\');
                                r = sk_state_ok() & 1;
                            }
                        }
                    }
                }
            }
        }
    }
    sk_token_release(token);
    return r & 1;
}

/* FUN_0043a478 @ 0x43a478  (est. sk_parse_range_capture)
 * Capture the current parse range into a 5-word descriptor. If the
 * parser is not inside a delimited token (sk_acquire_state with the
 * 0x2b/0xe1 opener fails) it falls back to the plain range path
 * FUN_004663ac. On success it peels the current token (sk_parse_pair
 * via FUN_00351db4) and records a signed negative span when the token
 * is forward of the base, together with the running count. Result is
 * written as 5 words: base, tag/type, start, end, and a byte flag.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x43a534/.538) on underflow; span
 * negation via FUN_00351db4 pair */
void sk_parse_range_capture(sk_parser_t *p, word_t *out)
{
    word_t start = *(word_t *)(p + 0x10);
    word_t end = start;
    word_t base, tag, flag;
    sk_pair_t span;

    if ((sk_acquire_state(0x2b, SK_TAG_DELIM) & 1) == 0) {
        sk_parse_helper();            /* FUN_00463de0 */
        if ((sk_acquire_state(0x2b, SK_TAG_DELIM) & 1) == 0) {
            /* not inside a token: report empty range */
            base = sk_empty_range();
            flag = 1;
            end = start;
            goto out5;
        }
        sk_parse_step2(1);            /* FUN_0043152c */
        span = sk_parse_pair();       /* FUN_00351db4 */
        if (span.lo != 0) {
            if ((long)span.lo < 0)    /* SBORROW8 */
                CL4_FATAL();          /* SoftwareBreakpoint(1,0x43a538) */
            span.hi = 0;
            span.lo = -(long)span.lo;
        }
    } else {
        sk_parse_step2(1);            /* FUN_0043152c */
        span = sk_parse_pair();       /* FUN_00351db4 */
        if (span.lo == 0) {
            base = sk_empty_range();
            end = start;
            flag = 1;
            goto out5;
        }
    }
    base = span.lo;
    end = *(word_t *)(p + 0x10);
    if (end >> 0xe < start >> 0xe)
        CL4_FATAL();                  /* SoftwareBreakpoint(1,0x43a534) */
    flag = 0;
    start = span.hi & 0xff;
out5:
    out[0] = base;
    out[1] = start;
    out[2] = end;
    out[3] = end;
    *(uint8_t *)(out + 4) = flag;
}



/* FUN_0043c4d4 @ 0x43c4d4  (est. sk_capture_parse_range)
 * Capture the current parser span into an 8-word descriptor written to
 * `out` (the x8 result buffer): start count, the count seen after the
 * '[' opener probe, the stack pair, the count after the inner probe,
 * the token tag, and the pair state. Unwinds the parser save frame.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x43c588/.58c) on size shrink; helpers
 * FUN_004368c0/FUN_004640c4/FUN_0042f7d4; opener token 0x5b '[' */
void sk_capture_parse_range(word_t *out, word_t thisp)
{
    word_t save = sk_parse_save();                 /* FUN_00354744 */
    word_t start = *(word_t *)(thisp + 0x10);
    word_t cnt2 = start, cnt3 = start, st0 = 0, st1 = 0, w6 = 0, w7 = 0;

    if ((sk_acquire_state(0x5b, SK_TAG_DELIM) & 1) == 0) {
        start = 0;
        st0 = 0; st1 = 0;
        FUN_00464d5c();                            /* empty-range helper */
        w6 = 0; w7 = 0;
    } else {
        cnt2 = *(word_t *)(thisp + 0x10);
        if (cnt2 >> 0xe < start >> 0xe) CL4_FATAL();   /* 0x43c588 */
        w7 = SK_TAG_DELIM;
        FUN_004368c0();
        cnt3 = *(word_t *)(thisp + 0x10);
        if (cnt3 >> 0xe < cnt2 >> 0xe) CL4_FATAL();    /* 0x43c58c */
        FUN_004640c4();
        w6 = sk_state_pair2();                       /* FUN_0042f7d4 -> pair */
    }
    out[0] = start;
    out[1] = cnt2;
    out[2] = st0;
    out[3] = st1;
    out[4] = cnt2;
    out[5] = cnt3;
    out[6] = w6;
    out[7] = w7;
    sk_parse_leave(save);                            /* FUN_003544c8 */
}


/* FUN_0043bd90 @ 0x43bd90  (est. sk_parse_entry_vector)
 * Parse a sequence of ',' / '}' terminated entries out of thisp and
 * append each into the 0x50-byte element vector at thisp+0x50,
 * growing the backing buffer when the element count reaches the
 * capacity field (thisp+0x18>>1). On the '}' terminator it settles
 * the logical size and commits. Emits a 0x99-byte result descriptor
 * through `out`. Every logical-size shrink is guarded by
 * SoftwareBreakpoint(1,0x43c4c4..d4).
 * Confidence: low
 * Notes: delimiters 0x2c ',' and 0x7d '}'; tag 0xe1..; thunk_FUN_
 * 002b74c0 pair; element stride 0x50; buffer words thisp+0x50 */
void sk_parse_entry_vector(word_t *out, word_t thisp)
{
    sk_pair_t frame = sk_frame_save();              /* frame save */
    word_t start, cnt, cap, cap_hi, s0, lo, hi, buf, c;
    sk_pair_t tk, s, p0;

    sk_parse_begin();                             /* parse begin */
    FUN_000a6f68();                             /* script-string probe */
    word_t res_a = _DAT_005a18a0, res_b = _DAT_005a18a8;
    word_t vecbuf = 0;

    for (;;) {
        start = *(word_t *)(thisp + 0x10);
        FUN_00354ca8(start, *(word_t *)(thisp + 0x18));
        sk_pair_fn(0, 0, 0, 0);
        FUN_004659bc();
        sk_parse_consume();                         /* consume opener */
        p0 = thunk_pair();                      /* thunk_FUN_002b74c0 */
        FUN_00465da4();
        sk_token_release(0);
        lo = p0.lo;
        /* scan to ',' or '}' */
        while (lo >> 0xe != p0.lo >> 0xe) {
            FUN_003510b8();
            FUN_00354ca8(0, 0);
            tk = sk_token_acquire();
            lo = tk.lo; hi = tk.hi;
            if (lo == 0x2c && hi == 0xe100000000000000ull) { sk_token_release(hi); break; }
            sk_parse_pf(lo, hi, 0x2c);
            word_t ok = sk_state_ok();
            if ((ok & 1) != 0 || (lo == 0x7d && hi == 0xe100000000000000ull)) {
                sk_token_release(hi); break;
            }
            sk_parse_pf(lo, hi, 0x7d);
            ok = sk_state_ok();
            sk_token_release(hi);
            if ((ok & 1) != 0) break;
            FUN_003510b8();
            FUN_00354ca8(0, 0);
            lo = FUN_002b3b50().lo;
        }
        if (lo >> 0xe < p0.lo >> 0xe) CL4_FATAL();   /* 0x43c4c8 */
        FUN_003504ac();
        tk = thunk_pair();
        lo = tk.lo; hi = tk.hi;
        sk_token_release(vecbuf);
        if ((lo ^ hi) < 0x4000) {
            /* end of entries */
            sk_token_release(lo);
            if (*(byte *)(thisp + 0x58) == 1) {
                word_t d[7];
                d[0]=1; d[1]=0xd00000000000001cull; d[2]=0;
                d[3]=start; d[4]=start; d[5]=0xf; d[6]=0x24;
                sk_record_append_alt(d);
            } else {
                FUN_00462b54();
                FUN_004578dc(lo, (word_t)(uintptr_t)sk_elem_cb_a);
                FUN_003505e8(); FUN_003511cc();
                FUN_00457994(0,0,0,0,0);
                buf = *(word_t *)(thisp + 0x50);
                FUN_0046418c(); FUN_00465160(0);
                *(word_t *)(thisp + 0x50) = buf;
            }
            goto done;
        }
        /* append entry into vector */
        FUN_003508fc();
        sk_scan_count();
        FUN_0042fe0c();
        FUN_00352840(lo);
        FUN_002a3e64();
        FUN_00351a50();
        sk_token_release(0);
        cnt = *(word_t *)(thisp + 0x10);
        if (cnt >> 0xe < start >> 0xe) CL4_FATAL();   /* 0x43c4cc */
        buf = vecbuf;
        if ((sk_alloc_probe(vecbuf) & 1) == 0) {
            FUN_00462974(*(word_t *)(vecbuf + 0x10));
            buf = FUN_00466468();               /* grow alloc */
        }
        c = *(word_t *)(buf + 0x10);
        if (*(word_t *)(buf + 0x18) >> 1 <= c) {
            sk_vec_cap_probe();
            FUN_00464000();
            buf = FUN_00466468();
        }
        *(word_t *)(buf + 0x10) = c + 1;
        *(word_t *)(buf + (c*4+4)*8) = lo;
        *(word_t *)(buf + (c*4+5)*8) = thisp;
        *(word_t *)(buf + (c*4+6)*8) = start;
        *(word_t *)(buf + (c*4+7)*8) = cnt;
        vecbuf = buf;
        /* settle logical size against '}' / ',' */
        cnt = *(word_t *)(thisp + 0x10);
        cap = *(word_t *)(thisp + 0x18);
        FUN_004634f4(cnt);
        sk_pair_fn(0, 0, 0, 0);
        FUN_00351a50();
        sk_token_release(0);
        FUN_00465890();
        FUN_004634f4(cnt);
        sk_pair_fn(0, 0, 0, 0);
        if (sk_parse_pg() != 0) {
            sk_token_begin();
            tk = sk_token_acquire();
            hi = tk.hi;
            sk_token_release(0);
            if (!(tk.lo == 0x7d && hi == 0xe100000000000000ull)) {
                FUN_003514e8();
                sk_parse_pf(0, 0, 0x7d);
                sk_state_ok();
                FUN_00351d18();
                sk_token_release(0);
                if ((lo & 1) != 0) goto settle;
            }
            FUN_004634f4(cnt);
            sk_pair_fn(0, 0, 0, 0);
            sk_token_enter();
            sk_token_settle2(cnt, 1);
            s = sk_state_pair();
            s0 = s.lo;
            sk_token_release(0);
            cap_hi = cap >> 0xe;
            if ((s.hi & 0xff) == 1) break;
            if (!(s0 >> 0xe <= cap_hi)) CL4_FATAL();  /* 0x43c4d0 */
            *(word_t *)(thisp + 0x10) = s0;
            *(word_t *)(thisp + 0x18) = cap;
            continue;
        }
        sk_token_release(0);
settle:
        /* descriptor kind 3 */
        FUN_004628f4();
        FUN_0046389c();
        FUN_0046589c();
        sk_debug_print(0, 0);
        sk_parse_pl();
        sk_debug_print(0, 0);
        {
            word_t d[7];
            d[0]=1; d[1]=res_b; d[2]=res_a; d[3]=0; d[4]=0; d[5]=3;
            d[6]= *(byte *)(thisp + 0x58);
            d[3]=cnt; d[4]=cnt;
            if (*(byte *)(thisp + 0x58) == 1) {
                sk_record_append_alt(d);
            } else {
                FUN_00462b54();
                FUN_004578dc(lo, (word_t)(uintptr_t)sk_elem_cb_a);
                FUN_003505e8(); FUN_003511cc();
                FUN_00457994(0,0,0,0,0);
                buf = *(word_t *)(thisp + 0x50);
                FUN_0046418c(); FUN_00465160(0);
                *(word_t *)(thisp + 0x50) = buf;
            }
        }
    }
    /* loop exit: settle final element */
    {
        word_t d[7];
        d[0]=0; d[1]=0xd000000000000022ull; d[2]=0;
        d[3]=start; d[4]=start; d[5]=*(byte *)(thisp + 0x58);
        sk_record_fill(d);
        if (*(byte *)(thisp + 0x58) == 1) {
            sk_record_append_alt(d);
        } else {
            FUN_00462b54();
            FUN_004578dc((word_t)d, (word_t)(uintptr_t)sk_elem_cb_a);
            buf = *(word_t *)(thisp + 0x50);
            c = *(word_t *)(buf + 0x10);
            FUN_00457994(c, 0, (word_t)(uintptr_t)sk_elem_cb_a, 0, 0);
            FUN_00464d74(c + 1);
            FUN_00465160(buf + c * 0x50);
        }
        FUN_004634f4(start);
        sk_pair_fn(0, 0, 0, 0);
        if (FUN_00462ba8() > 0) {
            FUN_004634f4(start);
            sk_pair_fn(0, 0, 0, 0);
            sk_token_enter();
            FUN_00350878(start);
            sk_token_settle2(0, 0);
            s = sk_state_pair();
            s0 = s.lo;
            sk_token_release(0);
            if ((s.hi & 0xff) != 1) {
                if (!(s0 >> 0xe <= cap_hi)) CL4_FATAL();  /* 0x43c4d4 */
                *(word_t *)(thisp + 0x10) = s0;
                *(word_t *)(thisp + 0x18) = cap;
            }
        }
    }
done:
    sk_parse_pp();                          /* emit 0x99 descriptor */
    FUN_00464ae8(frame.lo);                        /* frame leave */
}

/* FUN_0043cd98 @ 0x43cd98  (est. sk_parse_specacc_section)
 * Parse a SPECACC / LIAF tagged section out of thisp and build a
 * 7-word result written to `out`: mode flag, start count, end count,
 * a 16-byte state pair and two scalar fields. When a ':' opener
 * yields a non-empty value the source elements (0x50-byte stride,
 * starting at thisp+0x50) are copied into the element factory with
 * per-element grow; otherwise a 0x1/0x3 error descriptor is emitted.
 * SoftwareBreakpoint(1,0x43d48c/.490) guards size shrinks.
 * Confidence: low
 * Notes: mode tags 0x545045434341 'SPECACC' / 0x4c494146 'LIAF';
 * lock token 0x2a28; ':' opener 0x3a; result via out (unaff_x19) */
void sk_parse_specacc_section(word_t *out, word_t thisp, word_t flags,
                              word_t r26, word_t r27)
{
    FUN_0008e518();                             /* entry */
    word_t frame_a[20], frame_b[20];
    word_t local_68, local_118, local_110, mode;
    word_t res0 = 0, res1 = 0, res2 = 0, start = 0, end = 0;
    sk_pair_t state = { 0, 0 };

    FUN_004649fc();
    FUN_00464adc(frame_a);
    FUN_00464adc(frame_b);
    FUN_00464f84(frame_a, &local_68);
    sk_token_enter();                            /* FUN_00462870 */
    FUN_00462884(0x2a28);                        /* lock acquire */
    FUN_0015e4f8();
    sk_parse_pd();                               /* FUN_00356b5c */
    sk_token_release(0);

    if ((flags & 1) == 0) {
        res0 = 0; res1 = 0; res2 = 0;
        FUN_00464948();
    } else {
        FUN_00464a8c();
        sk_rwlock_op(0, 0);
        sk_parse_helper();                       /* FUN_0042fd4c */
        start = *(word_t *)(thisp + 0x10);
        FUN_00351744(start);
        sk_pair_fn(0, 0, 0, 0);
        FUN_00462988();
        if ((r26 & 1) == 0) {
            FUN_00351744(start);
            sk_pair_fn(0, 0, 0, 0);
            sk_token_enter();
            sk_lock_acquire(0x4c494146, 0xe400000000000000ull); /* 'LIAF' */
            FUN_0015e4f8();
            sk_parse_pd();
            sk_token_release(0);
            sk_rwlock_op(0x4c494146, 0xe400000000000000ull);
            sk_parse_helper();
            mode = 1;
        } else {
            sk_lock_acquire(0x545045434341, 0xe600000000000000ull); /* 'SPECACC' */
            FUN_0015e4f8();
            FUN_00464e64();
            sk_rwlock_op(0x545045434341, 0xe600000000000000ull);
            sk_parse_helper();
            mode = 0;
        }
        end = *(word_t *)(thisp + 0x10);
        if (end >> 0xe < start >> 0xe) CL4_FATAL();   /* 0x43d48c */
        FUN_00463534(0x3a);                      /* probe ':' */
        if ((sk_acquire2() & 1) == 0) {
            res1 = 0;
            state.lo = 0; state.hi = 0;
            res2 = 0;
        } else {
            sk_internal_reset(0);                /* FUN_00100e34 */
            res2 = 1;
            res1 = 0;
            state = FUN_004339a8();
        }
        res0 = state.lo;
        sk_parse_pn();                           /* FUN_00462f3c */
        if ((sk_acquire2() & 1) == 0) {
            word_t c2 = *(word_t *)(thisp + 0x10);
            FUN_004627f4();
            local_68 = r27;                      /* x8 result */
            sk_internal_reset(0);
            sk_debug_print(0, 0);
            sk_parse_pl();                       /* FUN_00463514 */
            sk_debug_print(0, 0);
            word_t d[6];
            d[0]=1; d[1]=local_68; d[2]=_DAT_005a1870; d[3]=_DAT_005a1878;
            d[4]=c2; d[5]=c2;
            FUN_004642a8();
            sk_record_append_alt(d);
        }
        if (state.hi == 0 || (sk_token_release(0), state.hi != 1)) {
            FUN_0045904c(frame_b);
            goto emit;
        }
    }
    /* copy source elements into the element factory */
    FUN_00350a04();
    word_t n = end;
    word_t val = res0;
    FUN_00461ab0();
    word_t u7 = *(word_t *)(thisp + 0x50);
    FUN_00464b20(&local_68);
    sk_ref_retain(u7);
    FUN_0045904c(&local_68);
    word_t cur = u7;
    local_118 = thisp;
    local_110 = *(byte *)(thisp + 0x58);
    if (local_110 == 1) {
        cur = sk_ref_release(cur);
    } else {
        sk_pair_t p = FUN_0041e21c(*(word_t *)(local_118 + 0x10), u7);
        cur = p.lo;
        if (n == val >> 1) {
            cur = sk_ref_release(cur);
        } else {
            if ((long)(val >> 1) <= (long)n) CL4_FATAL();  /* 0x43d490 */
            sk_ref_retain(u7);
            long remain = (long)(val >> 1) - (long)n;
            word_t src = p.hi + n * 0x50;
            word_t buf = local_118;
            while (1) {
                word_t dst = src;
                if (*(byte *)dst == 0) {
                    FUN_00459024((word_t *)dst, frame_a);
                    if ((sk_alloc_probe(buf) & 1) == 0) {
                        FUN_00462710(*(word_t *)(buf + 0x10));
                        FUN_0006b3f4();
                        buf = FUN_0045636c();
                    }
                    word_t c = *(word_t *)(buf + 0x10);
                    if (*(word_t *)(buf + 0x18) >> 1 <= c) {
                        sk_vec_cap_probe();
                        FUN_000dbed0();
                        buf = FUN_0045636c();
                    }
                    *(word_t *)(buf + 0x10) = c + 1;
                    sk_memcpy(buf + c * 0x50 + 0x20, dst, 0x49);
                    local_118 = buf;
                }
                if (remain == 0) break;
                remain--;
                src += 0x50;
            }
            sk_ref_release(u7);
            cur = sk_ref_release(p.lo);
        }
    }
    FUN_00463f4c(cur, frame_b);
    sk_memcpy(0, 0, 0);
    state.lo = res0;
    state.hi = 1;
emit:
    out[0] = mode;
    out[1] = start;
    out[2] = end;
    out[3] = state.lo;
    out[4] = state.hi;
    out[5] = res2;
    out[6] = res1;
    FUN_0008e500();                             /* exit */
}


/* FUN_0043e334 @ 0x43e334  (est. sk_parse_group_selector)
 * Parse a group/selector token sequence out of thisp and classify it
 * into one of the known script kinds (FLRC / RC / FLRCYNA / NAE / FL /
 * NUC / HE_TIMIL / METONYTYP / JIOT / FTU / UCP / ...). Each recognised
 * tag advances the parser via FUN_00462af0 + token checks and assigns a
 * kind index (0..7) plus a mode bit in `mode`. Unrecognised input falls
 * back to the element-factory path. Emits a 6-word result through
 * `out`. SoftwareBreakpoint(1,0x43e6b4/.ab0) guards size shrinks.
 * Confidence: low
 * Notes: token tags 0x464c5243 'FLRC', 0x5243 'RC', 0x464c5243594e41
 * 'FLRCYNA', 0x54494a5f4f4e 'JIOT', 0x465455 'FTU', 0x5954504d4554
 * 454f4e 'METONYTYP'; mode bits 0x8/0x6/0xa/0x2; result via out */
void sk_parse_group_selector(word_t *out, word_t *thisp, word_t flags)
{
    word_t r[10];
    word_t start, kind, mode, t1, k0, k1, k2, c2, buf, c, ix, r6;
    word_t frame[24], frame2[24], local1[24], strbuf[8];
    byte local_c8;

    FUN_0008e518();
    FUN_004649fc();
    start = *(word_t *)(thisp + 2);
    FUN_00464adc(r);
    FUN_00464b20(frame);
    FUN_00462d98();
    FUN_0029fa0c();
    FUN_004630c4();
    FUN_004614cc(r, local1);
    FUN_00464a8c();
    FUN_004636a0(0, 0, r[0]);
    FUN_0015e4f8();
    FUN_00466678();
    kind = 0; mode = 0; r6 = 0; start = 0;

    if ((r[0] & 1) == 0) goto copy_factory;
    FUN_00464a8c();
    FUN_001ee018();
    FUN_0042fd4c();
    k0 = thisp[0]; k1 = thisp[1]; k2 = thisp[2];
    FUN_00351b38(k2);
    FUN_0029fa0c();
    FUN_00462aac();
    FUN_00350518();
    FUN_00462af0();
    t1 = FUN_0015e4f8();
    FUN_003a25d4(k1);
    if ((t1 & 1) == 0) {
        FUN_00351b38(k2);
        FUN_0029fa0c();
        FUN_00462870();
        FUN_00350518();
        FUN_00462af0();
        t1 = FUN_0015e4f8();
        FUN_003a25d4(k0);
        if ((t1 & 1) != 0) {
            FUN_00350518();
            FUN_001ee018();
            mode = 0x8000000000000000ull;
            kind = 1;
            goto emit;
        }
        k1 = thisp[1];
        FUN_00463194();
        FUN_004629cc();
        FUN_00462af0(0x464c5243, 0xe400000000000000ull);   /* FLRC */
        FUN_0015e4f8();
        FUN_00464e7c();
        if ((flags & 1) != 0) { FUN_001ee018(0x464c5243, 0xe400000000000000ull); mode = 0x6000000000000000ull; kind = 2; goto emit; }
        FUN_00463194();
        FUN_004629cc();
        FUN_00462884(0x5243);                              /* RC */
        FUN_0015e4f8();
        FUN_00464e7c();
        if ((flags & 1) != 0) { FUN_001ee018(0x5243, 0xe200000000000000ull); kind = 0; mode = 0x6000000000000000ull; goto emit; }
        FUN_00463194();
        FUN_00462aac();
        t1 = FUN_0046580c();
        FUN_00462af0(t1, 0xe700000000000000ull);
        t1 = FUN_0015e4f8();
        FUN_003a25d4(flags);
        if ((t1 & 1) != 0) { FUN_001ee018(0x464c5243594e41, 0xe700000000000000ull); mode = 0x6000000000000000ull; kind = 3; goto emit; }
        FUN_00463194();
        FUN_004629cc();
        FUN_00462af0(_DAT_00594e41, 0xe300000000000000ull);
        FUN_0015e4f8();
        FUN_00464e7c();
        if ((flags & 1) != 0) { FUN_001ee018(_DAT_00594e41, 0xe300000000000000ull); mode = 0x6000000000000000ull; kind = 4; goto emit; }
        FUN_00463194();
        FUN_004629cc();
        FUN_00462884(0x464c);                              /* FL */
        FUN_0015e4f8();
        FUN_00464e7c();
        if ((flags & 1) != 0) { FUN_001ee018(0x464c, 0xe200000000000000ull); mode = 0x6000000000000000ull; kind = 1; goto emit; }
        FUN_00463194();
        FUN_00462870();
        FUN_00462af0(_DAT_004c554e, 0xe300000000000000ull);
        FUN_0015e4f8();
        FUN_00465314();
        if ((t1 & 1) != 0) { FUN_001ee018(_DAT_004c554e, 0xe300000000000000ull); mode = 0x6000000000000000ull; kind = 5; goto emit; }
        /* second selector group */
        FUN_00465974();
        word_t g0 = thisp[0], g1 = thisp[1], g2 = thisp[2], g3 = thisp[3];
        FUN_000dbd0c();
        FUN_0029fa0c();
        FUN_00462aac();
        FUN_00350914();
        FUN_00462af0();
        t1 = FUN_0015e4f8();
        FUN_003a25d4(g1);
        if ((t1 & 1) == 0) {
            FUN_000dbd0c();
            FUN_004665dc();
            FUN_00462870();
            FUN_00462af0(0x45485f54494d494c, 0xea00000000005041ull); /* HE_TIMIL */
            t1 = FUN_0015e4f8();
            FUN_003a25d4(t1);
            if ((t1 & 1) == 0) {
                FUN_00465974();
                FUN_000dbd0c();
                FUN_004665dc();
                FUN_00462870();
                FUN_00350914();
                FUN_00462af0();
                t1 = FUN_0015e4f8();
                FUN_003a25d4(t1);
                if ((t1 & 1) == 0) {
                    FUN_000dbd0c();
                    FUN_004665dc();
                    FUN_00462870();
                    FUN_00462af0(0xd000000000000010, 0x80000000005e0150);
                    t1 = FUN_0015e4f8();
                    FUN_003a25d4(t1);
                    if ((t1 & 1) != 0) { FUN_001ee018(0xd000000000000010, 0x80000000005e0150); mode = 0xa000000000000000ull; kind = 1; goto emit; }
                    FUN_000dbd0c();
                    FUN_004665dc();
                    FUN_00462870();
                    FUN_00462af0(0x5954504d4554454full, 0xe800000000000000ull); /* METONYTYP */
                    t1 = FUN_0015e4f8();
                    FUN_003a25d4(t1);
                    if ((t1 & 1) == 0) {
                        FUN_000dbd0c();
                        FUN_0029fa0c(g0, g1, g0, g1);
                        FUN_00462a5c();
                        FUN_00350914();
                        FUN_00462af0();
                        t1 = FUN_0015e4f8();
                        FUN_003a25d4(g1);
                        if ((t1 & 1) != 0) { FUN_00350914(); FUN_001ee018(); mode = 0xa000000000000000ull; kind = 2; goto emit; }
                        FUN_00353a78(g2, g3);
                        FUN_0029fa0c();
                        FUN_00462a5c();
                        FUN_00462af0(0xd000000000000011, 0x80000000005e0130);
                        t1 = FUN_0015e4f8();
                        FUN_003a25d4(g1);
                        if ((t1 & 1) != 0) { FUN_001ee018(0xd000000000000011, 0x80000000005e0130); mode = 0xa000000000000000ull; kind = 3; goto emit; }
                        FUN_00353a78(g2, g3);
                        FUN_0029fa0c();
                        FUN_00462988();
                        FUN_00462af0(0x54494a5f4f4e, 0xe600000000000000ull); /* JIOT */
                        FUN_0015e4f8();
                        FUN_00464e64();
                        FUN_00353a78(g2, g3);
                        FUN_0029fa0c();
                        FUN_004629cc();
                        FUN_00351274();
                        FUN_00462af0();
                        FUN_0015e4f8();
                        FUN_00464e7c();
                        FUN_00353a78(g2, g3);
                        FUN_0029fa0c();
                        FUN_00462a5c();
                        FUN_00462af0(0x465455, 0xe300000000000000ull); /* FTU */
                        t1 = FUN_0015e4f8();
                        FUN_003a25d4(0xec00000054504f5full);
                        if ((t1 & 1) == 0) {
                            FUN_00353a78(g2, g3);
                            FUN_0029fa0c();
                            FUN_00462870();
                            FUN_00462af0(_DAT_00504355, 0xe300000000000000ull);
                            FUN_0015e4f8();
                            FUN_00465314();
                            FUN_001ee018(_DAT_00504355, 0xe300000000000000ull);
                            mode = 0xa000000000000000ull;
                            kind = 7;
                        } else {
                            FUN_001ee018(0x465455, 0xe300000000000000ull);
                            mode = 0xa000000000000000ull;
                            kind = 6;
                        }
                    } else {
                        FUN_001ee018(0x5954504d4554454full, 0xe800000000000000ull);
                        kind = 0; mode = 0xa000000000000000ull;
                    }
                    goto emit;
                }
                FUN_00350914();
                FUN_001ee018();
                FUN_0042fd4c();
                FUN_00463bc8();
                if ((FUN_0042f670() & 1) == 0) {
                    c2 = thisp[2];
                    FUN_0046282c();
                    local1[0] = 1; local1[1] = _DAT_005a1880; local1[2] = 0;
                    local1[3] = c2; local1[4] = c2;
                    FUN_00465508(_DAT_005a1880);
                    FUN_00461430(local1);
                }
                FUN_00464134();
                FUN_0043152c();
                FUN_00465350();
                mode = 0x4000000000000000ull;
            } else {
                FUN_001ee018(0x45485f54494d494c, 0xea00000000005041ull);
                FUN_0042fd4c();
                FUN_00463bc8();
                if ((FUN_0042f670() & 1) == 0) {
                    c2 = thisp[2];
                    FUN_0046282c();
                    FUN_004642e8(_DAT_005a1880);
                    local1[0] = 1; local1[1] = _DAT_005a1880; local1[2] = _DAT_005a1888;
                    local1[3] = c2; local1[4] = c2;
                    FUN_00464268();
                    FUN_00461430(local1);
                }
                FUN_00464134();
                FUN_0043152c();
                FUN_00465350();
                mode = 0x2000000000000000ull;
            }
        } else {
            FUN_00350914();
            FUN_001ee018();
            FUN_0042fd4c();
            FUN_00463bc8();
            if ((FUN_0042f670() & 1) == 0) {
                c2 = thisp[2];
                FUN_0046282c();
                local1[0] = 1; local1[1] = _DAT_005a1880; local1[2] = _DAT_005a1888;
                local1[3] = c2; local1[4] = c2; local1[5] = 3;
                FUN_0042ec68(local1);
                FUN_00461430(local1);
            }
            FUN_00464134();
            FUN_0043152c();
            FUN_00465350();
            mode = 0;
        }
        if (mode >> 1 == 0xffffffff) goto copy_factory;
    } else {
        FUN_00350518();
        FUN_001ee018();
        kind = 0;
        mode = 0x8000000000000000ull;
    }
emit:
    FUN_0042fd4c();
    goto emit2;
copy_factory:
    FUN_00464b20(local1);
    word_t u9 = thisp[10];
    FUN_0036b270(u9);
    FUN_0045904c(local1);
    byte f = *(byte *)((char *)thisp + 0x18);
    if (f != 1) {
        FUN_0046527c();
        FUN_00463970();
        if (f != 1) {
            FUN_00462f5c();
            if (f == 0) CL4_FATAL();           /* 0x43eb6c */
            FUN_00463f74();
            FUN_0036b270();
            FUN_00462b2c();
            buf = local_c8;
            while (1) {
                FUN_00464e70(strbuf);
                if (strbuf[0] == 0) {
                    FUN_00459024(strbuf, frame2);
                    if ((FUN_003a261c(buf) & 1) == 0) {
                        FUN_00462710(*(word_t *)(buf + 0x10));
                        FUN_00462974(0);
                        buf = FUN_0045636c();
                    }
                    FUN_00462e44();
                    if (f) {
                        c = FUN_0006b42c();
                        FUN_00352480(c, start);
                        buf = FUN_0045636c();
                    }
                    ix = FUN_00462f6c();
                    FUN_00117cc4(ix, (word_t)strbuf, 0x49);
                    r[9] = buf;
                }
                if (r6 == 0) break;
                FUN_004639d8();
            }
            FUN_0036b118(u9);
        }
    }
    FUN_0036b118(0);
    FUN_00463f4c(FUN_0036b118(0), frame);
    FUN_00117cc4();
    kind = 0; mode = 0; start = 0;
    r6 = 0x1fffffffe;
emit2:
    FUN_0045904c(frame);
    if (thisp[2] >> 0xe < k2 >> 0xe) CL4_FATAL();   /* 0x43eab0 */
    FUN_00462f3c();
    if ((FUN_0042f670() & 1) == 0) {
        c2 = thisp[2];
        FUN_0046282c();
        FUN_00100e34();
        FUN_002acbb8();
        FUN_00463514();
        FUN_002acbb8();
        local1[0] = 1; local1[1] = _DAT_005a1870; local1[2] = 0;
        local1[3] = c2; local1[4] = c2;
        FUN_00465508(_DAT_005a1870);
        FUN_00461430(local1);
    }
    word_t r5 = thisp[2];
    if (r5 >> 0xe < mode >> 0xe) CL4_FATAL();       /* 0x43e6b4 */
    out[0] = kind;
    out[1] = mode;
    out[2] = 0;
    out[3] = 0;
    out[4] = 0;
    out[5] = r5;
    FUN_0008e500();
}


/* FUN_0043f4ec @ 0x43f4ec  (est. sk_collect_selector_groups)
 * Repeatedly classify a selector via sk_parse_group_selector and append
 * each 6-word result (0x30-byte stride) into the growable vector at
 * `vec`, growing when the count reaches capacity. Stops when the
 * selector reports the terminal marker (mode>>1 == 0xffffffff). If no
 * entry was collected the vector is released and nulled.
 * Confidence: medium
 * Notes: element stride 0x30; FUN_000b45b0 closes the collection */
word_t sk_collect_selector_groups(word_t vec, word_t thisp, word_t flags)
{
    word_t entry = FUN_000b4594();
    word_t sel[6];
    FUN_000a6fe0();
    while (1) {
        sk_parse_group_selector(sel, (word_t *)thisp, flags);
        if (sel[1] >> 1 == 0xffffffff) break;
        if ((FUN_003a261c(vec) & 1) == 0) {
            FUN_0006b3f4(*(word_t *)(vec + 0x10));
            vec = FUN_0045636c();
        }
        word_t n = *(word_t *)(vec + 0x10);
        if (*(word_t *)(vec + 0x18) >> 1 <= n) {
            FUN_0006b42c();
            FUN_000dbc98();
            vec = FUN_0045636c();
        }
        *(word_t *)(vec + 0x10) = n + 1;
        word_t base = vec + n * 0x30;
        *(word_t *)(base + 0x20) = sel[0];
        *(word_t *)(base + 0x28) = sel[1];
        *(word_t *)(base + 0x38) = sel[3];
        *(word_t *)(base + 0x30) = sel[2];
        *(word_t *)(base + 0x48) = sel[5];
        *(word_t *)(base + 0x40) = sel[4];
    }
    if (*(long *)(vec + 0x10) == 0) {
        FUN_0036b118(vec);
        vec = 0;
    }
    FUN_000b45b0(vec, entry);
    return vec;
}

/* FUN_0044b35c @ 0x44b35c  (est. sk_callout_format)
 * Format an Oniguruma-style callout diagnostic (string
 * s_oniguruma_callout_of_contents___005dd7a0) into a 16-byte pair
 * returned by value. Emits the contents string, an optional '[' class
 * suffix from thisp+0x50 when the flag at +0x58 is set, and the
 * callout type byte from +0x80.
 * Confidence: low
 * Notes: error kind 0xd00000000000001f; '[' token 0x5b; helpers
 * FUN_00463fe8/FUN_00463df8/FUN_00462728/FUN_00205844 */
sk_pair_t sk_callout_format(word_t thisp)
{
    word_t lo = 0, hi = 0xe000000000000000ull;
    FUN_002a4ab4(0x22);
    FUN_003a25d4(hi);
    lo = 0xd00000000000001full;
    hi = FUN_00086840();
    FUN_002acbb8(*(word_t *)(thisp + 0x10), *(word_t *)(thisp + 0x18));
    FUN_00463878();
    FUN_002acbb8();
    if (*(long *)(thisp + 0x58) != 0) {
        word_t c = 0x5b, ct = 0xe100000000000000ull;
        FUN_002acbb8(*(word_t *)(thisp + 0x50));
        FUN_004640c4();
        FUN_002acbb8();
        FUN_002acbb8(c, ct);
        FUN_003a25d4(ct);
    }
    word_t c2 = 0, ct2 = 0xe000000000000000ull;
    FUN_00463fe8();
    word_t p = FUN_002acbb8();
    byte c3 = *(byte *)(thisp + 0x80);
    FUN_00463df8(p, 0, 0x683da8);
    FUN_00462728();
    FUN_00205844(&c3, &c2);
    FUN_002acbb8(c2, ct2);
    FUN_003a25d4(ct2);
    sk_pair_t r = { lo, hi };
    return r;
}

/* FUN_0044a9a0 @ 0x44a9a0  (est. sk_token_build_long)
 * Build a token with a long argument value. Invokes the token-format
 * machinery FUN_00365b6c; on the failure branch zeroes the 5-word
 * token and emits an error token; on success reads the argument
 * through FUN_004107e4, retains it, and returns the value or 0.
 * Confidence: low
 * Notes: vtable calls (*DAT_00658cf0) and indirect (*pcVar5);
 * format string 0x682e08 */
long sk_token_build_long(word_t param1)
{
    word_t local70[6];
    word_t x8r, x9r, x12r, x12r2, x16r, x8r2;
    FUN_000a6f88();
    DAT_00658cf0(*(word_t *)(x8r + 0x40));
    FUN_0034ab10();
    DAT_00658cf0(0);
    long len = (x9r - x12r) - x12r2;
    word_t fn = *(word_t *)(x16r + 0x10);
    FUN_00350624(len);
    ((void (*)(void))fn)();
    word_t u3 = FUN_00466540();
    int i2 = FUN_00365b6c(local70, len, param1, u3, 6);
    long result = 0;
    if (i2 == 0) {
        local70[4] = 0; local70[1] = 0; local70[0] = 0; local70[3] = 0; local70[2] = 0;
        FUN_00466168();
        FUN_00461cb8(local70);
        word_t p = FUN_003509bc();
        ((void (*)(word_t, word_t, word_t))fn)(p, 0, param1);
        i2 = FUN_00365b6c(local70, x9r - x12r, param1, 0x682e08, 6);
        word_t u1 = local70[0];
        if (i2 != 0) {
            long v = FUN_004107e4(local70[0]);
            FUN_0036b118(u1 & 0xfffffffffffffff);
            if (v != 0) return v;
        }
        result = 0;
    } else {
        FUN_0034e1ec(local70);
        FUN_003507e0(FUN_00458ac8(local70[4]));
        result = ((long (*)(void))x8r2)();
        FUN_000026e8(local70);
    }
    return result;
}

/* FUN_00448aac @ 0x448aac  (est. sk_emit_group_sep)
 * Emit a group separator for a parsed token stream. In char mode
 * prints a '[' opener (FUN_00466014 + thunk) and scans the token
 * range; otherwise FUN_00466314 scans without opening bracket. Each
 * element is visited through callback `cb`.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x448c18/.1c) on size shrink */
void sk_emit_group_sep(word_t p1, byte mode, word_t cb, word_t p4,
                       word_t p5, word_t p6, word_t p7, word_t p8,
                       word_t x22, word_t x23, word_t x27)
{
    FUN_00354828(p7, p8);
    sk_pair_t p = FUN_0029fa0c();
    if (mode == 1) {
        if (p.hi >> 0xe < p.lo >> 0xe) CL4_FATAL();   /* 0x448c1c */
        FUN_00466014();
        thunk_FUN_002b74c0();
        FUN_004630b0();
        FUN_003a25d4(p4);
    } else {
        FUN_00466314();
        FUN_0042c060();
        FUN_004630b0();
    }
    word_t v = x22;
    word_t v2 = x23 >> 0xe;
    while (v >> 0xe != x23 >> 0xe) {
        FUN_0034be0c(v);
        FUN_002b439c();
        ((void (*)(void))cb)();
        FUN_00464e7c();
        v2 = v >> 0xe;
        if ((x27 & 1) == 0) break;
        FUN_0034be0c(v);
        v = FUN_002b3b50().lo;
    }
    if (v2 < x22 >> 0xe) CL4_FATAL();                /* 0x448c18 */
    FUN_00462e9c();
    p = thunk_FUN_002b74c0();
    word_t u2 = p.lo;
    FUN_00465088();
    FUN_003a25d4();
    if ((u2 ^ p.hi) < 0x4000) {
        FUN_003a25d4(p4);
        u2 = 0;
        FUN_00464d5c();
    }
    FUN_003505c4(u2);
}

/* FUN_0043f634 @ 0x43f634  (est. sk_close_group)
 * Close a parsed group: look up the last selector group (via
 * sk_collect_selector_groups) and copy the closing byte into
 * thisp+0x48, then validate the opener/closer against the 'balance'
 * table. A mismatched closer emits the
 * s_closing_____does_not_balance_any_005dfb40 diagnostic.
 * Confidence: low
 * Notes: error kind 0xd000000000000030; balance strings 0x5e03e0 */
void sk_close_group(word_t thisp, word_t x23)
{
    word_t grp;
    FUN_004666f8();
    grp = FUN_0043f4ec();
    if (grp != 0) {
        long n = *(long *)(grp + 0x10) + 1;
        word_t *slot = (word_t *)(grp + *(long *)(grp + 0x10) * 0x30 + 0x20);
        do {
            n--;
            if (n == 0) goto done;
            slot -= 6;
        } while (*(slot + 1) >> 0x3d != 3);
        *(char *)(thisp + 0x48) = (char)*slot;
    }
done:
    FUN_0043f770();
    FUN_004659c8();
    FUN_004651b8();
    byte ok = (thisp ^ x23) == 0x4000;
    if (0x3fff < (thisp ^ x23)) {
        FUN_00462f3c();
        FUN_0042ffec();
        FUN_0035292c();
        word_t d[4];
        if (ok) {
            FUN_0042f584(0xd00000000000001full, 0x80000000005e03e0,
                         *(word_t *)(thisp + 0x10), *(word_t *)(thisp + 0x10));
        } else {
            d[0] = 1;
            d[1] = 0xd000000000000030ull;
            d[2] = FUN_00086840();
            d[3] = 10;
        }
        FUN_0042ec68();
        FUN_00461430(d);
    }
    FUN_0036b270(*(word_t *)(thisp + 0x50));
    FUN_00350968(FUN_0043f770());
    FUN_004666e4();
}

/* FUN_00448934 @ 0x448934  (est. sk_emit_range_token)
 * Emit a range/interval token for a parsed stream (like
 * sk_emit_group_sep but with an extra thunk_FUN_0024d9ac element
 * conversion and trailing FUN_00351d30). Each element is visited and
 * passed through FUN_0024917c.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x448aa8/.ac) on shrink */
void sk_emit_range_token(word_t x22, word_t x23, word_t x3, word_t x4,
                         word_t x5, word_t x6, word_t w1)
{
    FUN_00351e20();
    sk_pair_t p = FUN_0029fa0c(x4, x5);
    if ((w1 & 0xff) == 1) {
        if (p.hi >> 0xe < p.lo >> 0xe) CL4_FATAL();   /* 0x448aac */
        FUN_00466014();
        thunk_FUN_002b74c0();
        FUN_004630b0();
        FUN_003a25d4(x3);
    } else {
        FUN_00466314();
        FUN_0042c060();
        FUN_004630b0();
    }
    word_t v = x22;
    word_t v2 = x23 >> 0xe;
    while (v >> 0xe != x23 >> 0xe) {
        FUN_0034be0c(v);
        p = FUN_002b439c();
        word_t xe = thunk_FUN_0024d9ac(x6);
        FUN_0024917c(xe, &p.lo);
        FUN_003a25d4(p.hi);
        FUN_0036b118(xe);
        v2 = v >> 0xe;
        if ((x3 & 1) == 0) break;
        FUN_0034be0c(v);
        v = FUN_002b3b50().lo;
    }
    if (v2 < x22 >> 0xe) CL4_FATAL();                /* 0x448aa8 */
    FUN_00462e9c();
    p = thunk_FUN_002b74c0();
    word_t u2 = p.lo;
    FUN_00465088();
    FUN_003a25d4();
    if ((u2 ^ p.hi) >> 0xe == 0) {
        FUN_003a25d4(x3);
        u2 = 0;
        FUN_00464d5c();
    }
    FUN_003505c4(u2);
    FUN_00351d30();
}

/* FUN_00448758 @ 0x448758  (est. sk_scan_group_body)
 * Scan a '{'-delimited group body between two token ranges and return
 * the surviving range pair. In char mode the opener is the thunk;
 * otherwise the FUN_0042c060 path. Iterates FUN_002b439c elements
 * until a '{' (0x7b) with the 0xe1 tag is found.
 * SoftwareBreakpoint(1,0x448930/.34) guards the shrink check.
 * Confidence: low
 * Notes: '{' token 0x7b; tag 0xe1; FUN_002a0cf8 state check */
sk_pair_t sk_scan_group_body(word_t p1, byte mode, word_t p3, word_t p4,
                             word_t p5, word_t p6)
{
    sk_pair_t r = FUN_0029fa0c(p5, p6);
    word_t hi = r.hi, lo = r.lo;
    if (mode == 1) {
        if (hi >> 0xe < lo >> 0xe) CL4_FATAL();      /* 0x448934 */
        r = thunk_FUN_002b74c0();
        FUN_003a25d4(p4);
    } else {
        r = FUN_0042c060(p1, lo, hi, p3, p4);
        r.lo = p3;
        r.hi = hi;
    }
    word_t c = r.hi, b = r.lo, e = r.hi, a = r.lo;
    word_t cur = a, last = a;
    while (cur >> 0xe != c >> 0xe) {
        sk_pair_t q = FUN_002b439c();
        word_t qh = q.hi;
        if (q.lo == 0x7b && qh == 0xe100000000000000ull) {
            FUN_003a25d4(qh);
        } else {
            word_t ok = FUN_002a0cf8(q.lo, qh, 0x7b, 0xe100000000000000ull, 0);
            FUN_003a25d4(qh);
            last = cur >> 0xe;
            if ((ok & 1) == 0) break;
        }
        cur = FUN_002b3b50().lo;
    }
    if (a >> 0xe <= last) {
        r = thunk_FUN_002b74c0();
        FUN_003a25d4(b);
        if ((r.lo ^ r.hi) >> 0xe == 0) {
            FUN_003a25d4(c);
            r.lo = 0; r.hi = 0;
        }
        return r;
    }
    CL4_FATAL();                                     /* 0x448930 */
}

/* FUN_0044bac4 @ 0x44bac4  (est. sk_format_open_paren)
 * Format a group/quantifier opening marker into a 16-byte pair based
 * on the object kind (thisp[5]>>0x3d). Kinds 3/4 emit specific
 * '...' / 'z...' label words; other kinds emit the '=>'/'::' style
 * openers via FUN_00465448. Returns the label pair by value.
 * Confidence: low
 * Notes: label words like 0x6f4d724f6f72657a ('zeroOrMo' reversed) */
sk_pair_t sk_format_open_paren(word_t *thisp, word_t x8, word_t x16,
                               word_t x13, word_t x11, word_t x1)
{
    word_t kind = thisp[5];
    byte is4 = kind >> 0x3d == 4;
    word_t lo = 0, hi = 0;
    switch (kind >> 0x3d) {
    case 3:
        FUN_004636cc();
        word_t u4 = FUN_00465170();
        if (!is4) {
            FUN_00462740();
            FUN_00027724(x16);
            u4 = FUN_00462a84();
            word_t plo = ((word_t (*)(word_t, word_t))x8)(u4, x16);
            hi = x16;
            u4 = plo;
        }
        FUN_002acbb8(u4, hi);
        FUN_003a25d4(hi);
        FUN_002acbb8(0x2e2e2e, 0xe300000000000000ull);
        if ((kind & 0xff) != 1) {
            FUN_000f4ae8();
            FUN_00027724(x16);
            FUN_0046295c();
            ((void (*)(void))x8)();
            FUN_00352c80();
        }
        goto out;
    case 4:
        FUN_004640f0(thisp[0]);
        byte zero = is4 && x13 == 0;
        if (zero) {
            hi = 0xea00000000006572ull;
            lo = 0x6f4d724f6f72657aull;
        } else {
            FUN_00465f00();
            lo = 0x726f4d724f656e6full;
            if (!zero || kind != x11) lo = 0x6e4f724f6f72657aull;
            hi = 0xe900000000000065ull;
        }
        goto out2;
    default:
        break;
    }
    FUN_00465448();
    if (is4) {
        FUN_00464a98();
        hi = 0xe90000000000003eull;
    } else {
        FUN_000f4ae8();
        FUN_00027724(x16);
        FUN_0046295c();
        ((void (*)(void))x8)();
        hi = x1;
    }
out:
    FUN_002acbb8();
    FUN_003a25d4(hi);
    FUN_00463e10();
    FUN_002acbb8();
out2:
    sk_pair_t r = { lo, hi };
    return r;
}

/* FUN_004452a8 @ 0x452a8  (est. sk_char_class_parse)
 * Parse a character-class definition into a 0xb0-byte descriptor.
 * Switches on the class kind (FUN_00458d04): handles 'subtraction' /
 * 'invalid bound' diagnostics, negative/positive ranges, and
 * disjunction cases; emits the appropriate error or range descriptor
 * through the x8 result buffer.
 * Confidence: low
 * Notes: error strings s_subtraction_with_____is_unsuppor_005dfbe0,
 * s_invalid_bound_for_character_clas_005dfc20 */
void sk_char_class_parse(word_t p1, word_t p2, word_t p3,
                         word_t x8, word_t x30, word_t x1, word_t x2)
{
    word_t stack_a[47], stack_b[24], stack_c[24];
    word_t lo = 0, hi = 0, c = 0;
    FUN_0008e518();
    FUN_004654a8(stack_a);
    word_t kind = FUN_00458d04(stack_a);
    switch (kind) {
    default:
        FUN_00458d10(stack_a);
        FUN_00419d98();
        if ((x1 & 1) == 0) {
            c = 1;
            hi = FUN_00086840();
            lo = 0xd000000000000035ull;
        } else {
            c = 1;
            hi = FUN_00086840();
            lo = 0xd000000000000027ull;
        }
        break;
    case 1:
    case 5:
        FUN_00458d10(stack_a);
        c = *(word_t *)(p3 + 0x10);
        lo = 0x6c20646573726150ull;
        hi = 0xec00000072657461ull;
        goto push;
    case 2:
        FUN_00458d10(stack_a);
        FUN_00117cc4((word_t)stack_b, FUN_00458d10(stack_a), 0xb0);
        FUN_0001a1c8(stack_b);
        FUN_004654a8(&lo);
        FUN_00458d10(&lo);
        FUN_004589e8(x2, stack_c);
        FUN_00117cc4((word_t)stack_c, (word_t)stack_b, 0xb0);
        goto emit;
    case 3:
        FUN_00458d10(stack_a);
        FUN_00419d98();
        FUN_003535a8();
        lo = 0;
        hi = 0xe000000000000000ull;
        FUN_002a4ab4(0x1d);
        FUN_003a25d4(hi);
        lo = 0xd00000000000001aull;
        hi = 0x80000000005e04e0;
        FUN_00462cb0();
        FUN_002acbb8(0xd00000000000001bull, x8 | 0x8000000000000000);
        c = 1;
        break;
    case 4:
        FUN_00458d10(stack_a);
        c = *(word_t *)(p3 + 0x10);
        lo = 0xd000000000000021ull;
        hi = 0x80000000005e04b0;
push:
        FUN_0042f584(&lo, lo, hi, c, c);
    }
    FUN_0042ec68(&lo);
    FUN_00461430(&lo);
    FUN_00461820(stack_b);
emit:
    FUN_00117cc4(x8, (word_t)stack_b, 0xb0);
    FUN_0008e500(0);
}

/* FUN_0044b8d0 @ 0x44b8d0  (est. sk_format_close_paren)
 * Format a group/quantifier closing marker into a 16-byte pair based
 * on the object kind (thisp[5]>>0x3d). Kinds 1/3/4 emit specific
 * '},'/'...'/'*+-?' label words; default emits the '=>' style via
 * FUN_00465448. Returns the label pair by value.
 * Confidence: low
 * Notes: label words 0x7d2c ('},'), 0x2a/0x2b/0x3f ('*','+','?') */
sk_pair_t sk_format_close_paren(word_t *thisp, word_t x8, word_t x16,
                                word_t x13, word_t x11, word_t x1)
{
    word_t kind = thisp[5];
    byte is4 = kind >> 0x3d == 4;
    word_t lo = 0, hi = 0;
    word_t q = 0;
    switch (kind >> 0x3d) {
    case 1:
        FUN_00465448();
        if (is4) FUN_004636b0();
        else { FUN_000f4ae8(); FUN_00027724(x16); FUN_0046295c(); ((void (*)(void))x8)(); hi = x1; }
        FUN_00466618();
        FUN_003a25d4(hi);
        lo = 0x7d2c; hi = 0xe200000000000000ull;
        goto out2;
    case 2:
        break;
    case 3:
        FUN_004636cc();
        word_t u4 = FUN_00465170();
        if (!is4) {
            FUN_00462740();
            FUN_00027724(x16);
            u4 = FUN_00462a84();
            word_t plo = ((word_t (*)(word_t, word_t))x8)(u4, x16);
            hi = x16;
            u4 = plo;
        }
        FUN_002acbb8(u4, hi);
        FUN_003a25d4(hi);
        FUN_0046589c();
        FUN_002acbb8();
        if ((kind & 0xff) != 1) {
            FUN_000f4ae8();
            FUN_00027724(x16);
            FUN_0046295c();
            ((void (*)(void))x8)();
            FUN_00352c80();
        }
        goto out;
    case 4:
        FUN_004640f0(thisp[0]);
        byte zero = is4 && x13 == 0;
        if (zero) {
            lo = 0x2a; hi = 0xe100000000000000ull;      /* '*' */
        } else {
            FUN_00465f00();
            lo = 0x2b;                                  /* '+' */
            if (!zero || kind != x11) lo = 0x3f;        /* '?' */
            hi = 0xe100000000000000ull;
        }
        goto out2;
    default:
        break;
    }
    FUN_00465448();
    if (is4) FUN_004636b0();
    else { FUN_000f4ae8(); FUN_00027724(x16); FUN_0046295c(); ((void (*)(void))x8)(); hi = x1; }
out:
    FUN_002acbb8();
    FUN_003a25d4(hi);
    FUN_00463878();
out2:
    FUN_002acbb8(q, 0);
    sk_pair_t r = { lo, hi };
    return r;
}

/* FUN_00440fb0 @ 0x440fb0  (est. sk_sync_region_flags)
 * Adjust the region flag word at param_2+0x40 based on the two
 * branches of param_1. If the first branch is not type 1 and the
 * "needs-update" bit (0x80) is set, clear it; scan param_1+0x18's
 * element list for a '\x03' marker and if found set bit 0x80. Then
 * scan param_1+0x38's list; if a '\x03' marker is found and bit 0x80
 * is set, clear it.
 * Confidence: high (structural)
 * Notes: element stride 0x18, first byte is the type marker */
void sk_sync_region_flags(word_t param1, word_t param2)
{
    if (*(char *)(param1 + 0x10) != 1 &&
        ((*(word_t *)(param2 + 0x40) >> 7) & 1) != 0)
        *(word_t *)(param2 + 0x40) &= 0xffffffffffffff7full;
    long n = *(long *)(*(long *)(param1 + 0x18) + 0x10) + 1;
    char *p = (char *)(*(long *)(param1 + 0x18) + 0x20);
    for (;;) {
        n--;
        if (n == 0) break;
        if (*p == 3) { *(word_t *)(param2 + 0x40) |= 0x80; break; }
        p += 0x18;
    }
    n = *(long *)(*(long *)(param1 + 0x38) + 0x10) + 1;
    p = (char *)(*(long *)(param1 + 0x38) + 0x20);
    for (;;) {
        n--;
        if (n == 0) return;
        if (*p == 3) {
            if ((*(word_t *)(param2 + 0x40) >> 7) & 1)
                *(word_t *)(param2 + 0x40) &= 0xffffffffffffff7full;
            return;
        }
        p += 0x18;
    }
}


/* FUN_00441034 @ 0x441034  (est. sk_parse_range_region)
 * Parse one range/region record (0x68-byte descriptor) out of the
 * current token stream at thisp. Reads the record header words, bumps
 * the record counter at thisp+0x28, and fills the output descriptor.
 * Region kind 2 (both branches present) syncs flags via
 * sk_sync_region_flags and probes the '\x03' set-marker; when both
 * branch-type bits clear it folds the value through
 * FUN_004108a0/FUN_0006a4c0. SoftwareBreakpoint guards the counter
 * and count checks.
 * Confidence: low
 * Notes: header words a0/a1/a2/a3/a7/a10; 0x68-byte output; region
 * kind byte at +0x11 */
void sk_parse_range_region(word_t thisp, word_t x30)
{
    word_t local_150[16], local_148, local_138, uStack_130, stack_b[16];
    word_t x8_ret, x9_ret, u9, u6, cnt, a0, a1, a3, a7, flag0, d0, d1, d3, d7;
    byte a2, a10, d2;

    sk_pair_t entry = FUN_0008e518();
    word_t *src = (word_t *)entry.hi;
    if ((long)(*(long *)(thisp + 0x28)) == 0x7fffffffffffffff) CL4_FATAL(); /* carry */
    a0 = src[0];
    a1 = src[1];
    a2 = *(char *)(src + 2);
    a3 = src[3];
    a7 = src[7];
    a10 = *(char *)(src + 10);
    *(long *)(thisp + 0x28) += 1;
    if (a10 == 0 || (a10 == 1 && a1 != 0)) {
        FUN_0036b270(a1);
        FUN_00350998(local_150);
        FUN_000b2260();
        FUN_003a25d4(local_148);
    }
    flag0 = *(word_t *)(thisp + 0x40);
    if (a10 == 2) {
        d0 = a0; d1 = a1; d2 = a2; d3 = a3; d7 = a7;
        sk_sync_region_flags((word_t)&d0, thisp);
        if (a2 != 1 && (*(word_t *)(thisp + 0x40) & 3) != 0)
            *(word_t *)(thisp + 0x40) &= 0xfffffffffffffffcull;
        long n = *(long *)(a3 + 0x10) + 1;
        byte *q = (byte *)(a3 + 0x20);
        for (;;) {
            n--;
            if (n == 0) break;
            if ((*q & 0xfe) == 6) { *(word_t *)(thisp + 0x40) |= 3; break; }
            q += 0x18;
        }
        n = *(long *)(a7 + 0x10) + 1;
        q = (byte *)(a7 + 0x20);
        for (;;) {
            n--;
            if (n == 0) break;
            if ((*q & 0xfe) == 6) {
                if ((*(word_t *)(thisp + 0x40) & 3) != 0)
                    *(word_t *)(thisp + 0x40) &= 0xfffffffffffffffcull;
                break;
            }
            q += 0x18;
        }
    }
    byte both = 0;
    if ((~flag0 & 3) == 0) both = ((~*(word_t *)(thisp + 0x40) & 3) != 0);
    u6 = FUN_0043f770();
    FUN_00100e34();
    if ((FUN_0042f670() & 1) == 0) {
        word_t c2 = *(word_t *)(thisp + 0x10);
        FUN_004627f4();
        local_150[0] = x8_ret; local_148 = x9_ret;
        FUN_00100e34();
        FUN_002acbb8();
        FUN_00463514();
        FUN_002acbb8();
        word_t d[6];
        d[0]=1; d[1]=local_150[0]; d[2]=local_148; d[3]=c2; d[4]=c2; d[5]=3;
        FUN_0042ec68(d);
        FUN_00461430(d);
    }
    cnt = *(word_t *)(thisp + 0x10);
    if (cnt >> 0xe < entry.lo >> 0xe) CL4_FATAL();       /* 0x44136c */
    if (both && (*(byte *)(thisp + 0x40) >> 6 & 1) != 0) {
        FUN_004108a0(local_150, u6);
        FUN_0006a4c0(local_150, local_138);
        u9 = FUN_00458e50(uStack_130);
        FUN_00350944(u9);
        sk_pair_t p = ((sk_pair_t (*)(void))x8_ret)();
        FUN_000026e8(local_150);
        FUN_003511cc(p.lo, p.hi);
        FUN_0029fa0c();
        FUN_0042f1f0();
        FUN_000b4528();
    }
    FUN_00117cc4((word_t)local_150, (word_t)src, 0x68);
    *(word_t *)(thisp + 0x40) = flag0;
    FUN_004637b4();
    FUN_0045908c(src, stack_b);
    FUN_00117cc4(x8_ret, (word_t)local_150, 0x68);
    *(word_t *)(x8_ret + 0x68) = u6;
    *(word_t *)(x8_ret + 0x70) = entry.lo;
    *(word_t *)(x8_ret + 0x78) = cnt;
    FUN_0008e500(x30);
}

/* FUN_0044136c @ 0x44136c  (est. sk_parse_absent_or_pair)
 * Parse an absent-tag or expression-pair node. When the flag byte is
 * non-zero, resolve the two branches via FUN_0043f770 (releasing and
 * retaining the ref pair, 2-element fast path). Otherwise validate the
 * opening token and fall through to the same "absent" analysis.
 * Writes an 8-word result to param_1.
 * SoftwareBreakpoint(1,0x44167c..688) guards the count checks.
 * Confidence: low
 * Notes: error kind 0x34; ')' token 0x29; result written to param_1 */
void sk_parse_absent_or_pair(word_t *param1, byte param2, word_t param3,
                             word_t param4, word_t thisp, word_t x24)
{
    word_t local_118, local_110, local_100_lo, local_100_hi;
    word_t local_168, local_160, stack_c8[16];
    word_t x8_ret, x9_ret, x1_ret, u9, u3 = 0, u8 = 0, x28 = 0, x25 = 0, v4 = 0;

    FUN_00117cc4((word_t)stack_c8, 0, 0);
    FUN_0042fc4c();
    if (x1_ret == 0) {
        u3 = FUN_0043f770();
        if (u3 >> 0x3c == 0) {
            word_t l5 = *(word_t *)(u3 + 0x10);
            word_t l7 = *(word_t *)(l5 + 0x10);
            if (l7 == 0) CL4_FATAL();               /* 0x441680 */
            word_t l6 = *(word_t *)(u3 + 0x18);
            if (*(word_t *)(l6 + 0x10) == 0) CL4_FATAL(); /* 0x441684 */
            if (l7 == 1) CL4_FATAL();               /* 0x441688 */
            x28 = *(word_t *)(l6 + 0x20);
            x25 = *(word_t *)(l6 + 0x28);
            v4 = *(word_t *)(l5 + 0x20);
            u8 = *(word_t *)(l5 + 0x28);
            if (l7 == 2) {
                FUN_0036b270(u8 & 0xfffffffffffffff);
                FUN_0036b270(v4 & 0xfffffffffffffff);
                FUN_0036b118(u3);
                u8 |= 2;
                u3 = v4;
            } else {
                FUN_004108a0(&local_118, u3);
                FUN_0006a4c0(&local_118);
                word_t fn = FUN_00458e50(local_100_hi);
                FUN_0036b270(u8 & 0xfffffffffffffff);
                FUN_0036b270(v4 & 0xfffffffffffffff);
                sk_pair_t p = ((sk_pair_t (*)(word_t, word_t))fn)(local_100_lo, local_100_hi);
                FUN_000026e8(&local_118);
                local_118 = 0;
                local_110 = 0xe000000000000000ull;
                FUN_002a4ab4(0x34);
                FUN_004643cc();
                FUN_002acbb8(0xd000000000000032ull);
                local_168 = l7;
                u9 = FUN_00462abc(0x6720e0);
                ((word_t (*)(word_t, word_t))x8_ret)(u9, 0x6720e0);
                FUN_002acbb8();
                FUN_003a25d4(x1_ret);
                local_100_lo = p.lo; local_100_hi = p.hi;
                FUN_0042ec68(&local_118);
                FUN_00461430(&local_118);
                FUN_0036b118(u3);
                u8 |= 2;
                u3 = v4;
            }
        } else {
            FUN_004655f0();
            u8 = 4;
        }
    } else {
        sk_pair_t p = FUN_00465920();
        if (param2 != 0 && p.hi == 0xe100000000000000ull) {
            FUN_003a25d4(0);
        } else {
            FUN_00463540(p.lo, 0, 0x29);
            FUN_002a0cf8();
            FUN_00465c68();
            if ((x24 & 1) == 0) {
                u3 = FUN_0043f770();
                if (u3 >> 0x3c == 0) {
                    word_t l5 = *(word_t *)(u3 + 0x10);
                    word_t l7 = *(word_t *)(l5 + 0x10);
                    if (l7 == 0) CL4_FATAL();
                    word_t l6 = *(word_t *)(u3 + 0x18);
                    if (*(word_t *)(l6 + 0x10) == 0) CL4_FATAL();
                    if (l7 == 1) CL4_FATAL();
                    x28 = *(word_t *)(l6 + 0x20);
                    x25 = *(word_t *)(l6 + 0x28);
                    v4 = *(word_t *)(l5 + 0x20);
                    u8 = *(word_t *)(l5 + 0x28);
                    if (l7 == 2) {
                        FUN_0036b270(u8 & 0xfffffffffffffff);
                        FUN_0036b270(v4 & 0xfffffffffffffff);
                        FUN_0036b118(u3);
                        u8 |= 2;
                        u3 = v4;
                    } else {
                        FUN_004108a0(&local_118, u3);
                        FUN_0006a4c0(&local_118);
                        word_t fn = FUN_00458e50(local_100_hi);
                        FUN_0036b270(u8 & 0xfffffffffffffff);
                        FUN_0036b270(v4 & 0xfffffffffffffff);
                        sk_pair_t p2 = ((sk_pair_t (*)(word_t, word_t))fn)(local_100_lo, local_100_hi);
                        FUN_000026e8(&local_118);
                        local_118 = 0;
                        local_110 = 0xe000000000000000ull;
                        FUN_002a4ab4(0x34);
                        FUN_004643cc();
                        FUN_002acbb8(0xd000000000000032ull);
                        local_168 = l7;
                        u9 = FUN_00462abc(0x6720e0);
                        ((word_t (*)(word_t, word_t))x8_ret)(u9, 0x6720e0);
                        FUN_002acbb8();
                        FUN_003a25d4(x1_ret);
                        local_100_lo = p2.lo; local_100_hi = p2.hi;
                        FUN_0042ec68(&local_118);
                        FUN_00461430(&local_118);
                        FUN_0036b118(u3);
                        u8 |= 2;
                        u3 = v4;
                    }
                } else {
                    FUN_004655f0();
                    u8 = 4;
                }
            }
        }
        if (p.hi != 0xe100000000000000ull || param2 == 0) {
            /* fall through to shared absent analysis */
            FUN_004655f0();
        }
    }
    FUN_00100e34();
    if ((FUN_0042f670() & 1) == 0) {
        word_t c2 = *(word_t *)(thisp + 0x10);
        FUN_004627f4();
        local_168 = x8_ret; local_160 = x9_ret;
        FUN_00100e34();
        FUN_002acbb8();
        FUN_00463514();
        FUN_002acbb8();
        word_t d[6];
        d[0]=1; d[1]=local_168; d[2]=local_160; d[3]=c2; d[4]=c2; d[5]=3;
        FUN_0042ec68(&local_168);
        FUN_00461430(&local_168);
    }
    word_t cnt = *(word_t *)(thisp + 0x10);
    if (param3 >> 0xe <= cnt >> 0xe) {
        param1[0] = param3;
        param1[1] = param4;
        param1[2] = u3;
        param1[3] = x28;
        param1[4] = x25;
        param1[5] = u8;
        param1[6] = param3;
        param1[7] = cnt;
        return;
    }
    CL4_FATAL();                                     /* 0x44167c */
}

/* Shared tail: finalise a ref-list (growable 0x10-element vector) and
 * emit the surrounding '(' value ',' ... ')' callout. Used by the
 * pair-list formatter family (0044a128/0044a420/0044948c/00449808/
 * 00449acc). Returns the final 16-byte pair by value. */
static sk_pair_t sk_ref_list_emit(word_t list, sk_pair_t value)
{
    for (;;) {
        if (*(long *)(list + 0x10) == 0) {
            FUN_0036b118(list);
            return value;
        }
        if (*(long *)(list + 0x10) == 1) {
            word_t u = value.lo & 0xffffffffffff;
            if ((value.hi & 0x2000000000000000) != 0) u = value.hi >> 0x38 & 0xf;
            if (u == 0) {
                FUN_003a25d4(value.hi);
                if (*(long *)(list + 0x10) == 0) CL4_FATAL();
                value.lo = *(word_t *)(list + 0x20);
                value.hi = *(word_t *)(list + 0x28);
                thunk_FUN_0036b270(value.hi);
                continue;
            }
        }
        thunk_FUN_002acbb8(0x28, 0xe100000000000000ull);   /* '(' */
        word_t t1 = FUN_00002534((word_t)&FUN_0064e030, (word_t)&DAT_004be900);
        word_t t2 = FUN_00460d50(0x64e038, (word_t)&FUN_0064e030, (word_t)&DAT_004be900,
                                 (word_t)&DAT_004e824c);
        sk_pair_t r = FUN_001bc440(0x2c, 0xe100000000000000ull, t1, t2); /* ',' */
        FUN_0036b118(list);
        thunk_FUN_002acbb8(r.lo, r.hi);
        FUN_003a25d4(r.hi);
        thunk_FUN_002acbb8(0x29, 0xe100000000000000ull);   /* ')' */
        return value;
    }
}

/* FUN_0044948c @ 0x44948c  (est. sk_flatten_ref_list)
 * Recursively flatten a reference tree (param_1) into a growable
 * 0x10-element ref-list, then emit the '(' ... ')' callout via
 * sk_ref_list_emit. When the node has no direct value (FUN_004107e4
 * returns 0) it is expanded through the FUN_004108a0/FUN_0006a4c0
 * machinery. Returns the final pair by value.
 * Confidence: medium
 * Notes: growable list seed DAT_00657778; grow fn FUN_0045659c */
sk_pair_t sk_flatten_ref_list(word_t param1)
{
    sk_pair_t result;
    word_t list = (word_t)&DAT_00657778;
    if (FUN_004107e4() == 0) {
        word_t local_88[16], local_70, uStack_68;
        FUN_004108a0(local_88, param1);
        FUN_0006a4c0(local_88, local_70);
        word_t u4 = FUN_00027754(uStack_68);
        word_t fn = FUN_000a6bb8();
        result = ((sk_pair_t (*)(word_t, word_t))fn)(local_70, u4);
        FUN_000026e8(local_88);
        return result;
    }
    word_t l2 = FUN_004107e4();
    word_t n = *(word_t *)(l2 + 0x10);
    word_t i = 0;
    for (;;) {
        if (n == i) break;
        if (*(word_t *)(l2 + 0x10) <= i) CL4_FATAL();     /* 0x449804 */
        word_t v = *(word_t *)(l2 + i * 8 + 0x20);
        if (v >> 0x3c != 6) {
            FUN_0036b270(v & 0xfffffffffffffff);
            sk_pair_t sub = sk_flatten_ref_list(v);
            word_t hi = sub.hi;
            FUN_0036b118(v & 0xfffffffffffffff);
            v = sub.lo & 0xffffffffffff;
            if ((hi & 0x2000000000000000) != 0) v = hi >> 0x38 & 0xf;
            if (v != 0) {
                if ((FUN_003a261c(list) & 1) == 0)
                    list = FUN_0045659c(0, *(long *)(list + 0x10) + 1, 1, list,
                                        0x64e110, (word_t)&DAT_004c05b0,
                                        (word_t)FUN_00069970, (word_t)FUN_00069770);
                word_t c = *(word_t *)(list + 0x10);
                if (*(word_t *)(list + 0x18) >> 1 <= c)
                    list = FUN_0045659c(1 < *(word_t *)(list + 0x18), c + 1, 1, list,
                                        0x64e110, (word_t)&DAT_004c05b0,
                                        (word_t)FUN_00069970, (word_t)FUN_00069770);
                i++;
                *(word_t *)(list + 0x10) = c + 1;
                *(sk_pair_t *)(list + c * 0x10 + 0x20) = sub;
                continue;
            }
            FUN_003a25d4(hi);
        }
        i++;
    }
    FUN_0036b118(l2);
    {
        word_t local_88[16], local_70, uStack_68;
        FUN_004108a0(local_88, param1);
        FUN_0006a4c0(local_88, local_70);
        word_t u4 = FUN_00027754(uStack_68);
        word_t fn = FUN_000a6bb8();
        result = ((sk_pair_t (*)(word_t, word_t))fn)(local_70, u4);
        FUN_000026e8(local_88);
    }
    return sk_ref_list_emit(list, result);
}

/* FUN_0044a128 @ 0x44a128  (est. sk_format_callout_value)
 * Format a callout argument value: build the value object (type tag
 * 0x6579c8), and when its ref-kind is not 6 flatten it through
 * sk_flatten_ref_list and append the pair to the shared ref-list,
 * then emit the '(' ... ')' callout. Returns the final pair.
 * Confidence: medium
 * Notes: object build FUN_00002534/FUN_0036a9a0; ref-list grow
 * FUN_0045659c */
sk_pair_t sk_format_callout_value(word_t thisp)
{
    word_t local_a0[16], auStack_90[40], local_68;
    word_t t = FUN_00002534(0x6579c8, (word_t)&DAT_005a19a0);
    word_t obj = FUN_0036a9a0(t, auStack_90);
    *(word_t *)(obj + 0x18) = DAT_004baeb8;
    *(word_t *)(obj + 0x10) = DAT_004baeb0;
    local_68 = *(word_t *)(thisp + 0x68);
    *(word_t *)(obj + 0x20) = local_68;
    FUN_00460dcc(&local_68, local_a0);
    word_t list = (word_t)&DAT_00657778;
    word_t v = *(word_t *)(obj + 0x20);
    sk_pair_t out = { 0, 0 };
    if (v >> 0x3c != 6) {
        FUN_0036b270(v & 0xfffffffffffffff);
        sk_pair_t p = sk_flatten_ref_list(v);
        word_t hi = p.hi;
        FUN_0036b118(v & 0xfffffffffffffff);
        v = p.lo & 0xffffffffffff;
        if ((hi & 0x2000000000000000) != 0) v = hi >> 0x38 & 0xf;
        if (v == 0) {
            FUN_003a25d4(hi);
        } else {
            if ((FUN_003a261c(list) & 1) == 0)
                list = FUN_0045659c(0, DAT_00657788 + 1, 1, list, 0x64e110,
                                    (word_t)&DAT_004c05b0, (word_t)FUN_00069970,
                                    (word_t)FUN_00069770);
            word_t c = *(word_t *)(list + 0x10);
            if (*(word_t *)(list + 0x18) >> 1 <= c)
                list = FUN_0045659c(1 < *(word_t *)(list + 0x18), c + 1, 1, list,
                                    0x64e110, (word_t)&DAT_004c05b0,
                                    (word_t)FUN_00069970, (word_t)FUN_00069770);
            *(word_t *)(list + 0x10) = c + 1;
            *(sk_pair_t *)(list + c * 0x10 + 0x20) = p;
        }
    }
    FUN_0036b588(obj);
    FUN_00455d8c();
    FUN_0036b6ac(FUN_00455d8c(), 0x20, 7);
    sk_pair_t tail = FUN_0044bdc8();
    return sk_ref_list_emit(list, tail);
}

/* FUN_0044a420 @ 0x44a420  (est. sk_format_callout_group)
 * Like sk_format_callout_value but with the group-prefix token
 * 0x5f70756f7267 ('group_') appended, emitted via FUN_0044b4ec.
 * Returns the final pair by value.
 * Confidence: medium
 * Notes: group token 0x5f70756f7267 */
sk_pair_t sk_format_callout_group(word_t thisp)
{
    word_t local_a0[16], auStack_90[40], local_68, x1_ret;
    word_t t = FUN_00002534(0x6579c8, (word_t)&DAT_005a19a0);
    word_t obj = FUN_0036a9a0(t, auStack_90);
    *(word_t *)(obj + 0x18) = DAT_004baeb8;
    *(word_t *)(obj + 0x10) = DAT_004baeb0;
    local_68 = *(word_t *)(thisp + 0x68);
    *(word_t *)(obj + 0x20) = local_68;
    FUN_00460dcc(&local_68, local_a0);
    word_t list = (word_t)&DAT_00657778;
    word_t v = *(word_t *)(obj + 0x20);
    if (v >> 0x3c != 6) {
        FUN_0036b270(v & 0xfffffffffffffff);
        sk_pair_t p = sk_flatten_ref_list(v);
        word_t hi = p.hi;
        FUN_0036b118(v & 0xfffffffffffffff);
        v = p.lo & 0xffffffffffff;
        if ((hi & 0x2000000000000000) != 0) v = hi >> 0x38 & 0xf;
        if (v == 0) {
            FUN_003a25d4(hi);
        } else {
            if ((FUN_003a261c(list) & 1) == 0)
                list = FUN_0045659c(0, DAT_00657788 + 1, 1, list, 0x64e110,
                                    (word_t)&DAT_004c05b0, (word_t)FUN_00069970,
                                    (word_t)FUN_00069770);
            word_t c = *(word_t *)(list + 0x10);
            if (*(word_t *)(list + 0x18) >> 1 <= c)
                list = FUN_0045659c(1 < *(word_t *)(list + 0x18), c + 1, 1, list,
                                    0x64e110, (word_t)&DAT_004c05b0,
                                    (word_t)FUN_00069970, (word_t)FUN_00069770);
            *(word_t *)(list + 0x10) = c + 1;
            *(sk_pair_t *)(list + c * 0x10 + 0x20) = p;
        }
    }
    FUN_0036b588(obj);
    FUN_00455d8c();
    FUN_0036b6ac(FUN_00455d8c(), 0x20, 7);
    local_a0[0] = 0x5f70756f7267;                 /* 'group_' */
    local_a0[1] = 0xe600000000000000ull;
    FUN_0044b4ec();
    FUN_002acbb8();
    FUN_003a25d4(x1_ret);
    sk_pair_t tail = { local_a0[0], local_a0[1] };
    return sk_ref_list_emit(list, tail);
}

/* FUN_0044a73c @ 0x44a73c  (est. sk_iterate_callout_args)
 * Iterate a callout's argument list (from sk_token_build_long),
 * flattening each non-empty entry into the shared ref-list; then emit
 * the callout tail. Guards index bounds with SoftwareBreakpoint.
 * Confidence: medium
 * Notes: bounds checks 0x44a99c; ref-kind 6 is a leaf */
void sk_iterate_callout_args(void)
{
    word_t x27_ret, x26_ret, x8_ret;
    FUN_00351e20();
    FUN_003509ec();
    long l1 = sk_token_build_long(0);
    if (l1 == 0) {
        word_t fn = FUN_000a6bb8();
        FUN_00100efc();
        FUN_00351d30();
        ((void (*)(void))fn)();
        return;
    }
    word_t i = 0;
    word_t n = *(word_t *)(l1 + 0x10);
    word_t list = (word_t)&DAT_00657778;
    FUN_000a6fe0();
    while (n != i) {
        if (*(word_t *)(l1 + 0x10) <= i) CL4_FATAL();     /* 0x44a99c */
        word_t v = *(word_t *)(l1 + i * 8 + 0x20);
        if (v >> 0x3c == 6) {
            i++;
            continue;
        }
        FUN_0036b270(v & 0xfffffffffffffff);
        sk_pair_t p = sk_flatten_ref_list(v);
        FUN_00355a58();
        FUN_0036b118(v & 0xfffffffffffffff);
        v = x27_ret & 0xffffffffffff;
        if ((x26_ret & 0x2000000000000000) != 0) v = x26_ret >> 0x38 & 0xf;
        if (v == 0) {
            FUN_003a25d4();
            i++;
            continue;
        }
        if ((FUN_003a261c(list) & 1) == 0) {
            FUN_0006b3f4(*(word_t *)(list + 0x10));
            list = FUN_00465b80();
        }
        word_t c = *(word_t *)(list + 0x10);
        word_t nc = c + 1;
        if (*(word_t *)(list + 0x18) >> 1 <= c) {
            FUN_00465ed4();
            FUN_00465f14();
            list = FUN_00465b80();
            nc = x8_ret;
        }
        i++;
        *(long *)(list + 0x10) = nc;
        word_t base = list + c * 0x10;
        *(word_t *)(base + 0x20) = x27_ret;
        *(word_t *)(base + 0x28) = x26_ret;
    }
    FUN_0036b118(l1);
    FUN_000a6bb8();
    FUN_00100efc();
    sk_pair_t tail = ((sk_pair_t (*)(void))x8_ret)();
    sk_ref_list_emit(list, tail);
    FUN_00351d30(FUN_000b43d0());
}

/* FUN_00449808 @ 0x449808  (est. sk_flatten_ref_list_owned)
 * Flatten a reference tree (param_1) into the shared ref-list
 * (skipping 6-kind leaves) and emit the callout tail with the
 * FUN_00411a54 result as the value. Returns the final pair.
 * Confidence: medium
 * Notes: bounds check 0x449ac8 */
sk_pair_t sk_flatten_ref_list_owned(word_t param1)
{
    word_t n = *(word_t *)(param1 + 0x10);
    FUN_0036b270();
    word_t i = 0;
    word_t list = (word_t)&DAT_00657778;
    while (n != i) {
        if (n <= i) CL4_FATAL();                  /* 0x449ac8 */
        word_t v = *(word_t *)(param1 + i * 8 + 0x20);
        if (v >> 0x3c == 6) {
            i++;
            continue;
        }
        FUN_0036b270(v & 0xfffffffffffffff);
        sk_pair_t sub = sk_flatten_ref_list(v);
        word_t hi = sub.hi;
        FUN_0036b118(v & 0xfffffffffffffff);
        v = sub.lo & 0xffffffffffff;
        if ((hi & 0x2000000000000000) != 0) v = hi >> 0x38 & 0xf;
        if (v == 0) {
            FUN_003a25d4(hi);
            i++;
            continue;
        }
        if ((FUN_003a261c(list) & 1) == 0)
            list = FUN_0045659c(0, *(long *)(list + 0x10) + 1, 1, list, 0x64e110,
                                (word_t)&DAT_004c05b0, (word_t)FUN_00069970,
                                (word_t)FUN_00069770);
        word_t c = *(word_t *)(list + 0x10);
        if (*(word_t *)(list + 0x18) >> 1 <= c)
            list = FUN_0045659c(1 < *(word_t *)(list + 0x18), c + 1, 1, list,
                                0x64e110, (word_t)&DAT_004c05b0,
                                (word_t)FUN_00069970, (word_t)FUN_00069770);
        i++;
        *(word_t *)(list + 0x10) = c + 1;
        *(sk_pair_t *)(list + c * 0x10 + 0x20) = sub;
    }
    FUN_0036b118(param1);
    sk_pair_t val = FUN_00411a54(param1);
    return sk_ref_list_emit(list, val);
}

/* FUN_00449acc @ 0x449acc  (est. sk_flatten_ref_list_tail)
 * Flatten a reference tree (param_1) into the shared ref-list and
 * emit the callout tail, returning the surviving pair directly.
 * Confidence: medium
 * Notes: bounds check 0x449d70 */
sk_pair_t sk_flatten_ref_list_tail(word_t param1)
{
    word_t n = *(word_t *)(param1 + 0x10);
    FUN_0036b270();
    word_t i = 0;
    word_t list = (word_t)&DAT_00657778;
    for (;;) {
        if (n == i) {
            FUN_0036b118(param1);
            return sk_ref_list_emit(list, (sk_pair_t){0, 0xe000000000000000ull});
        }
        if (n <= i) CL4_FATAL();                  /* 0x449d70 */
        word_t v = *(word_t *)(param1 + i * 8 + 0x20);
        if (v >> 0x3c == 6) {
            i++;
            continue;
        }
        FUN_0036b270(v & 0xfffffffffffffff);
        sk_pair_t sub = sk_flatten_ref_list(v);
        word_t hi = sub.hi;
        FUN_0036b118(v & 0xfffffffffffffff);
        v = sub.lo & 0xffffffffffff;
        if ((hi & 0x2000000000000000) != 0) v = hi >> 0x38 & 0xf;
        if (v == 0) {
            FUN_003a25d4(hi);
            i++;
            continue;
        }
        if ((FUN_003a261c(list) & 1) == 0)
            list = FUN_0045659c(0, *(long *)(list + 0x10) + 1, 1, list, 0x64e110,
                                (word_t)&DAT_004c05b0, (word_t)FUN_00069970,
                                (word_t)FUN_00069770);
        word_t c = *(word_t *)(list + 0x10);
        if (*(word_t *)(list + 0x18) >> 1 <= c)
            list = FUN_0045659c(1 < *(word_t *)(list + 0x18), c + 1, 1, list,
                                0x64e110, (word_t)&DAT_004c05b0,
                                (word_t)FUN_00069970, (word_t)FUN_00069770);
        i++;
        *(word_t *)(list + 0x10) = c + 1;
        *(sk_pair_t *)(list + c * 0x10 + 0x20) = sub;
    }
}

/* FUN_00440ce8 @ 0x440ce8  (est. sk_parse_condition_branches)
 * Parse a 2-branch condition node. Resolves the branch value via
 * FUN_0043f770; the 2-element fast path retains and releases the two
 * branches; otherwise it runs the FUN_004108a0 machinery and emits the
 * s_expected_2_branches_in_condition_005dfe30 diagnostic. Builds a
 * 0x90-byte descriptor (plus tag words) into a freshly allocated
 * object and returns it. SoftwareBreakpoint(1,0x440fa4..fb0) guards
 * the branch-count checks.
 * Confidence: low
 * Notes: error kind 0x29; object tag 0x3; out written via unaff_x19 */
word_t sk_parse_condition_branches(word_t thisp, word_t x21, word_t x19)
{
    word_t local_198[16], x8_ret, x1_ret, u8, u9, local_180, uStack_178;
    FUN_0008409c();
    word_t u2 = FUN_0043f770();
    word_t u10 = 0, u11 = 0, u4, u3, v9 = 0;
    if (u2 >> 0x3c == 0) {
        word_t l5 = *(word_t *)(u2 + 0x18);
        if (*(word_t *)(l5 + 0x10) == 0) CL4_FATAL();   /* 0x440fa8 */
        word_t l7 = *(word_t *)(u2 + 0x10);
        word_t n = *(word_t *)(l7 + 0x10);
        if (n == 0) CL4_FATAL();                        /* 0x440fac */
        if (n == 1) CL4_FATAL();                        /* 0x440fb0 */
        u10 = *(word_t *)(l5 + 0x20);
        u11 = *(word_t *)(l5 + 0x28);
        u4 = *(word_t *)(l7 + 0x20);
        u3 = *(word_t *)(l7 + 0x28);
        if (n == 2) {
            FUN_0036b270(u3 & 0xfffffffffffffff);
            FUN_0036b270(u4 & 0xfffffffffffffff);
            FUN_0036b118(u2);
            v9 = 0;
            u2 = u4;
        } else {
            word_t local_198[16], local_180, uStack_178;
            FUN_004108a0(local_198, u2);
            FUN_0006a4c0(local_198, local_180);
            word_t fn = FUN_00458e50(uStack_178);
            FUN_0036b270(u3 & 0xfffffffffffffff);
            FUN_0036b270(u4 & 0xfffffffffffffff);
            FUN_000dbd0c();
            ((void (*)(void))fn)();
            FUN_000778b4();
            FUN_000026e8(local_198);
            local_198[0] = 0;
            local_198[1] = 0xe000000000000000ull;
            FUN_002a4ab4(0x2b);
            FUN_003a25d4(local_198[1]);
            FUN_00086840();
            local_198[0] = 0xd000000000000029ull;
            word_t d[2]; d[0] = n;
            FUN_004638c0();
            FUN_00462abc();
            ((void (*)(word_t, word_t))x8_ret)(u8, fn);
            FUN_002acbb8();
            FUN_003a25d4(x1_ret);
            FUN_004642e8(local_198[0]);
            word_t d2[5];
            d2[0]=local_180; d2[1]=uStack_178; d2[2]=0; d2[3]=0; d2[4]=n;
            FUN_0042ec68(d2);
            FUN_00461430(d2);
            FUN_0036b118(u2);
            v9 = 0;
            u2 = u4;
        }
    } else {
        FUN_00002834(0x685b78);
        u3 = FUN_0036a940();
        u10 = 0; u11 = 0;
        u4 = *(word_t *)(thisp + 0x10);
        *(word_t *)(u3 + 0x10) = u4;
        *(word_t *)(u3 + 0x18) = u4;
        u3 |= 0xb000000000000000ull;
        v9 = 1;
    }
    FUN_00100e34();
    if ((FUN_0042f670() & 1) == 0) {
        u4 = *(word_t *)(thisp + 0x10);
        FUN_004627f4();
        local_198[0] = x8_ret;
        FUN_00100e34();
        FUN_002acbb8();
        FUN_00463514();
        FUN_002acbb8();
        FUN_00465304(local_198[0]);
        word_t d[2]; d[0]=u4; d[1]=u4;
        FUN_00465908(_DAT_005a1870);
        FUN_0042ec68();
        FUN_00461430(0);
    }
    FUN_00466124(0x685d08);
    u4 = FUN_0036a940();
    u3 = *(word_t *)(thisp + 0x10);
    if (x21 >> 0xe <= u3 >> 0xe) {
        *(word_t *)(u4 + 0x10) = x21;
        *(word_t *)(u4 + 0x18) = u3;
        FUN_00117cc4(u4 + 0x20, x19, 0x90);
        *(word_t *)(u4 + 0xb0) = u2;
        *(word_t *)(u4 + 0xb8) = u10;
        *(word_t *)(u4 + 0xc0) = u11;
        *(byte *)(u4 + 200) = v9;
        *(word_t *)(u4 + 0xd0) = u3;
        FUN_00458c98(x19, &local_198);
        return u4 | 0x3000000000000000ull;
    }
    CL4_FATAL();                                     /* 0x440fa4 */
}

/* FUN_00440820 @ 0x440820  (est. sk_parse_expression)
 * Parse an expression node. Dispatches on the region kind: for kind 2
 * it classifies the sub-kind (through FUN_0043ed70 / FUN_00440fb0 /
 * FUN_00441688) and builds the corresponding object; other kinds map
 * to the 'normal' / 'last' / 'backtrack' factories. Scans the branch
 * element lists for the 6-kind set marker to set the thisp+0x40 flag
 * word. Emits the s_extended_syntax_may_not_be_disab_005dfa00
 * diagnostic when extended syntax is disabled mid-scan.
 * Confidence: low
 * Notes: error kinds 0x36/0x4b; extended-syntax strings 0x5dfa00/50 */
word_t sk_parse_expression(word_t thisp)
{
    word_t local_270[22], auStack_5b0[22], auStack_1c0[22], auStack_320[22];
    word_t auStack_3d0[22], auStack_660[22], auStack_e8[22], auStack_438[22];
    word_t auStack_520[22], auStack_4b8[22], auStack_3d0b[22];
    word_t local_4d0, local_3e8, uStack_3d8, local_3e0, uStack_4c0, local_4c8;
    word_t uStack_268, uStack_258, uStack_248, local_250, local_260, uStack_238;
    word_t local_240, uStack_298, local_2a0, uStack_440, local_448;
    word_t u12 = *(word_t *)(thisp + 0x10);
    FUN_00438328(auStack_5b0);
    FUN_00117cc4((word_t)auStack_1c0, (word_t)auStack_5b0, 0x90);
    int kind = FUN_00461bd4(auStack_1c0);
    word_t result;
    if (kind == 1) {
        FUN_00438f54(auStack_520);
        if ((~local_4d0 & 0xff) == 0) {
            word_t k2 = FUN_00439348();
            if (k2 == 2) {
                FUN_004372d4(auStack_438);
                if ((~local_3e8 & 0xff) == 0) {
                    word_t k3 = FUN_0043942c();
                    byte is2 = k3 == 2;
                    if (is2) {
                        FUN_0043ed70(auStack_3d0);
                        FUN_00117cc4((word_t)auStack_320, (word_t)auStack_3d0, 0xb0);
                        FUN_00464918(auStack_320);
                        if (is2) {
                            result = 0xf000000000000007ull;
                        } else {
                            FUN_00117cc4((word_t)&local_270, (word_t)auStack_320, 0xb0);
                            FUN_00117cc4((word_t)auStack_e8, (word_t)auStack_320, 0x99);
                            int r = FUN_00458af8(auStack_e8);
                            if (r == 0xd) {
                                word_t b = FUN_00465b04(auStack_e8);
                                word_t b16 = *(word_t *)(b + 0x10);
                                word_t b18 = *(word_t *)(b + 0x18);
                                word_t b28 = *(word_t *)(b + 0x28);
                                word_t b20 = *(word_t *)(b + 0x20);
                                word_t b30 = *(word_t *)(b + 0x30);
                                word_t b38 = *(word_t *)(b + 0x38);
                                FUN_00117cc4((word_t)auStack_660, (word_t)auStack_3d0, 0xb0);
                                FUN_004589e8(auStack_660, local_270);
                                FUN_00440fb0();
                                word_t f = *(word_t *)(thisp + 0x40);
                                if (((f >> 6) & 1) == 0) {
                                    if ((f & 3) != 0 && *(char *)b16 != 1) {
                                        f &= 0xffffffffffffffbcull;
                                        *(word_t *)(thisp + 0x40) = f;
                                    }
                                    long n = *(long *)(b18 + 0x10) + 1;
                                    byte *q = (byte *)(b18 + 0x20);
                                    for (;;) {
                                        n--;
                                        if (n == 0) break;
                                        if ((*q & 0xfe) == 6) { f |= 3; *(word_t *)(thisp + 0x40) = f; break; }
                                        q += 0x18;
                                    }
                                    n = *(long *)(b38 + 0x10) + 1;
                                    q = (byte *)(b38 + 0x20);
                                    for (;;) {
                                        n--;
                                        if (n == 0) break;
                                        if ((*q & 0xfe) == 6) {
                                            if ((f & 3) != 0) *(word_t *)(thisp + 0x40) = f & 0xfffffffffffffffcull;
                                            break;
                                        }
                                        q += 0x18;
                                    }
                                } else {
                                    long n = *(long *)(b38 + 0x10) + 1;
                                    byte *q = (byte *)(b38 + 0x20);
                                    for (;;) {
                                        n--;
                                        if (n == 0) {
                                            if (*(char *)b16 == 1) break;
                                            FUN_00086840();
                                            result = 0xe;
                                            goto err;
                                        }
                                        if ((*q & 0xfe) == 6) { result = 0xd; goto err; }
                                        q += 0x18;
                                    }
                                }
                                FUN_00464804();
                                FUN_00350968(&b18);
                                FUN_00461cb8();
                                FUN_00350968(&b38);
                                FUN_00461cb8();
err:
                                FUN_00466290(result);
                                FUN_0042ec68();
                                FUN_00461430();
                            }
                            FUN_00466104(0x685c90);
                            result = FUN_0036a940();
                            FUN_00117cc4(result + 0x10, (word_t)&local_270, 0xb0);
                            result |= 0x8000000000000000ull;
                        }
                    } else {
                        FUN_00002850(0x685cb8);
                        result = FUN_0036a940();
                        FUN_00350878(&local_270, k3);
                        FUN_00441688();
                        *(word_t *)(result + 0x18) = uStack_268;
                        *(word_t *)(result + 0x10) = local_270[0];
                        *(word_t *)(result + 0x28) = uStack_258;
                        *(word_t *)(result + 0x20) = local_260;
                        *(word_t *)(result + 0x38) = uStack_248;
                        *(word_t *)(result + 0x30) = local_250;
                        result |= 0x9000000000000000ull;
                    }
                } else {
                    FUN_00117cc4((word_t)auStack_320, (word_t)auStack_438, 0x50);
                    word_t d[3]; d[0]=local_3e8; d[1]=uStack_3d8; d[2]=local_3e0;
                    FUN_00465884((word_t)&FUN_0067f9a0);
                    result = FUN_0036a940();
                    FUN_00441034(&local_270, u12, auStack_320);
                    FUN_00466148();
                    FUN_00461cb8(auStack_438);
                    FUN_00117cc4(result + 0x10, (word_t)&local_270, 0x80);
                    result |= 0x2000000000000000ull;
                }
            } else {
                FUN_00465128(0x685ce0);
                result = FUN_0036a940();
                FUN_003511d8(&local_270, k2);
                FUN_0044136c();
                *(word_t *)(result + 0x18) = uStack_268;
                *(word_t *)(result + 0x10) = local_270[0];
                *(word_t *)(result + 0x28) = uStack_258;
                *(word_t *)(result + 0x20) = local_260;
                *(word_t *)(result + 0x38) = uStack_248;
                *(word_t *)(result + 0x30) = local_250;
                *(word_t *)(result + 0x48) = uStack_238;
                *(word_t *)(result + 0x40) = local_240;
                result |= 0xa000000000000000ull;
            }
        } else {
            FUN_00117cc4((word_t)local_270, (word_t)auStack_520, 0x50);
            word_t d[3]; d[0]=local_4d0; d[1]=uStack_4c0; d[2]=local_4c8;
            FUN_00441034(auStack_4b8, local_4c8, local_270);
            FUN_00466148();
            FUN_00461cb8(auStack_520);
            FUN_00117cc4((word_t)auStack_660, (word_t)auStack_4b8, 0x80);
            FUN_00461590(auStack_660);
            uStack_298 = uStack_440;
            local_2a0 = local_448;
            FUN_00117cc4((word_t)auStack_320, (word_t)auStack_660, 0x80);
            FUN_00117cc4((word_t)&local_270, (word_t)auStack_320, 0x90);
            result = sk_parse_condition_branches(u12, (word_t)&local_270, 0);
            FUN_00458e28(&local_270);
        }
    } else {
        FUN_00117cc4((word_t)&local_270, (word_t)auStack_1c0, 0x90);
        result = sk_parse_condition_branches(u12, (word_t)&local_270, 0);
        FUN_00461cb8(auStack_5b0);
    }
    return result;
}

/* FUN_00441ff8 @ 0x441ff8  (est. sk_parse_char_class_body)
 * Parse the body of a custom character class. Either consumes a
 * ']'-terminated token range or dispatches to the sub-kind parsers
 * (FUN_0043ed70 / FUN_00441688) and folds the result into a 0x178-byte
 * class descriptor. SoftwareBreakpoint guards the size checks.
 * Confidence: low
 * Notes: ']' token 0x5d */
void sk_parse_char_class_body(word_t p1, word_t p2, word_t p3, word_t p4)
{
    byte cy_flag = 0, zr_flag = 0;
    word_t x22;
    word_t auStack_218[22], auStack_278[22], auStack_4a0[47], auStack_1b8[47];
    word_t local_328[8], local_618[22], uStack_608, local_600, local_5f8, uStack_5f0;
    word_t local_320, uStack_318, local_310, local_308, uStack_300;
    sk_pair_t p;
    FUN_004649fc();
    FUN_00465288();
    FUN_00351a5c();
    FUN_003a25d4(p4);
    FUN_004644dc();
    if (cy_flag) {
        FUN_00464b20(auStack_218);
        p = FUN_0042fc4c();
        word_t hi = p.hi;
        if (hi == 0) {
            goto parse_subkind;
        }
        if (p.lo == 0x5d && hi == 0xe100000000000000ull) {
            FUN_003a25d4(hi);
        } else {
            p3 = 0x5d;
            FUN_00463540(p.lo, hi);
            FUN_002a0cf8();
            FUN_00356b5c();
            FUN_003a25d4();
            if ((x22 & 1) == 0) goto parse_subkind;
        }
    }
    goto empty;
parse_subkind:
    FUN_00464b20(auStack_278);
    FUN_00439530();
    FUN_0046511c();
    if (zr_flag) {
        word_t k = FUN_0043942c();
        byte is2 = k == 2;
        if (is2) {
            p = FUN_00434054();
            if (p.hi == 0) {
                p = FUN_00435110();
                if (p.hi == 0) {
                    FUN_0043ed70(local_328);
                    FUN_00464918(local_328);
                    if (is2) goto empty;
                    FUN_00117cc4((word_t)local_618, (word_t)local_328, 0xb0);
                    FUN_00461708(local_618);
                } else {
                    uStack_608 = p3;
                    local_600 = p4;
                    local_618[0] = p.lo; local_618[1] = p.hi;
                    FUN_00461738(local_618);
                }
            } else {
                uStack_608 = p3;
                local_600 = p4;
                local_618[0] = p.lo; local_618[1] = p.hi;
                FUN_00461768(local_618);
            }
        } else {
            FUN_00441688(local_328);
            local_618[0] = local_328[0];
            uStack_608 = uStack_318;
            local_618[1] = local_320;
            local_600 = local_310;
            uStack_5f0 = uStack_300;
            local_5f8 = local_308;
            FUN_00461798(local_618);
        }
        p = FUN_00465788();
        FUN_00117cc4(p.lo, p.hi, 0x178);
        FUN_0001a1c8(auStack_4a0);
        FUN_00117cc4((word_t)auStack_1b8, (word_t)auStack_4a0, 0x178);
        goto emit;
    }
empty:
    FUN_00461854(auStack_1b8);
emit:
    FUN_00117cc4();
}

/* FUN_00441688 @ 0x441688  (est. sk_parse_custom_class_ops)
 * Parse a custom character class's operator sequence ('&&'/'||'/'~~'
 * combined with ',' and per-class fallbacks). Builds the parsed class
 * object, appends each resolved sub-class into the output vector
 * (0x178-byte stride) and finally emits the result descriptor.
 * SoftwareBreakpoint(1,0x441b2c..b30) guards the count checks.
 * Confidence: low
 * Notes: operator tokens 0x2626 '&&', 0x7e7e '~~', 0x2d2d '--';
 * result kind 0x24; vector at thisp+0x50 */
void sk_parse_custom_class_ops(word_t p1, word_t p2, word_t p3, word_t x30)
{
    word_t local_110, local_288, local_280, local_278, local_270, local_268;
    word_t x8_ret, x1_ret, local_b8, local_a0, local_b0, x8_ret_out[6];
    byte zr_flag = 0;
    word_t local_290, local_2b8, local_58[8], local_108[8];
    word_t uStack_28, local_20, uStack_18, local_10, uStack_48, uStack_38, local_30;
    word_t uVar2, uVar3, local_260, local_250, uStack_258, uStack_248, local_240;
    word_t thisp = p1;
    word_t x21;
    byte uVar1 = *(byte *)(thisp + 0x20);
    *(byte *)(thisp + 0x20) = 1;
    FUN_000a6f68();
    word_t local_110b = x8_ret;
    FUN_00441b40(&local_110b);
    word_t l10 = *(word_t *)(local_110b + 0x10);
    word_t l11 = 0x20;
    for (;;) {
        word_t l12 = local_110b;
        if (l10 == 0) {
            /* no elements: error descriptor */
            word_t d[6];
            d[0]=1; d[1]=0xd000000000000027; d[2]=0x80000000005dfc30;
            d[3]=0x80000000005dfc30; d[4]=7; d[5]=0x24;
            FUN_0042ec68(d);
            FUN_00461430(d);
            uVar2 = DAT_004baeb8;
            uVar3 = DAT_004baeb0;
            for (;;) {
                word_t u14 = *(word_t *)(thisp + 0x10);
                FUN_00117cc4((word_t)&local_b8, 0, 0);
                word_t u7 = FUN_00439530();
                l11 = 0x2d2d;
                switch (u7) {
                case 1: l11 = 0x2626; break;
                case 2: l11 = 0x7e7e; break;
                case 3:
                    FUN_004640c4();
                    if ((FUN_0042f670() & 1) == 0) {
                        u14 = *(word_t *)(thisp + 0x10);
                        FUN_004628f4();
                        local_288 = x8_ret;
                        FUN_0046389c();
                        local_280 = x8_ret;
                        FUN_004640c4();
                        FUN_002acbb8();
                        FUN_00463514();
                        FUN_002acbb8();
                        word_t d2[6];
                        d2[0]=1; d2[1]=local_288; d2[2]=local_280; d2[3]=u14; d2[4]=u14; d2[5]=3;
                        FUN_0042ec68(d2);
                        FUN_00461430(d2);
                    }
                    u14 = *(word_t *)(thisp + 0x10);
                    if (x1_ret >> 0xe <= u14 >> 0xe) {
                        *(byte *)(thisp + 0x20) = uVar1;
                        x8_ret_out[0] = x8_ret;
                        x8_ret_out[1] = x1_ret;
                        x8_ret_out[2] = p3;
                        x8_ret_out[3] = l12;
                        x8_ret_out[4] = x1_ret;
                        x8_ret_out[5] = u14;
                        FUN_0008e500(x30);
                        return;
                    }
                    CL4_FATAL();                         /* 0x441b30 */
                }
                FUN_0029fa0c(u14, local_a0, local_b8, local_b0);
                FUN_00462a98();
                FUN_00462884(l11);
                word_t u8 = FUN_0015e4f8();
                FUN_003a25d4(x21);
                if ((u8 & 1) == 0) {
                    local_280 = 0xe200000000000000ull;
                    local_288 = l11;
                    FUN_004627b8();
                    FUN_00464d50(&local_288);
                    sk_pair_t q = FUN_002aca00();
                    x21 = q.lo;
                    FUN_004628f4();
                    local_288 = x8_ret;
                    FUN_0046389c();
                    local_280 = x8_ret;
                    FUN_002acbb8();
                    FUN_00463514();
                    FUN_002acbb8();
                    word_t d3[6];
                    d3[0]=1; d3[1]=local_288; d3[2]=local_280; d3[3]=u14; d3[4]=u14; d3[5]=3;
                    FUN_0042ec68(d3);
                    FUN_00461430(d3);
                } else {
                    FUN_001ee018(l11, 0xe200000000000000ull);
                    FUN_003a25d4(0xe200000000000000ull);
                    FUN_0042fd4c(FUN_001ee018(l11, 0xe200000000000000ull));
                }
                word_t u13 = *(word_t *)(thisp + 0x10);
                word_t u8b = u13 >> 0xe;
                byte same = u8b == u14 >> 0xe;
                if (u8b < u14 >> 0xe) CL4_FATAL();       /* 0x441b2c */
                FUN_000a6f68();
                local_290 = x8_ret;
                FUN_00441b40(&local_290);
                l11 = 0x20;
                for (l10 = *(word_t *)(local_290 + 0x10); l10 != 0; l10--) {
                    FUN_00117cc4((word_t)&local_288, local_290 + l11, 0x178);
                    FUN_004652ac(&local_288);
                    if (!same) goto out;
                    l11 += 0x178;
                }
                local_288 = 1;
                local_280 = -0x2fffffffffffffd9ull;
                local_278 = local_2b8;
                local_260 = 7;
                local_250 = 0;
                uStack_248 = 0;
                uStack_258 = 0;
                local_240 = 0x24;
                local_270 = x1_ret;
                local_268 = p3;
                if (*(char *)(thisp + 0x58) == 1) {
                    FUN_00461430(&local_288);
                } else {
                    FUN_00463fd0();
                    FUN_004578dc(x21, (word_t)FUN_00072178, (word_t)FUN_0045694c, (word_t)FUN_0045636c);
                    word_t lv = *(word_t *)(*(word_t *)(thisp + 0x50) + 0x10);
                    FUN_00457994(lv, x21, (word_t)FUN_00072178, (word_t)FUN_0045694c, (word_t)FUN_0045636c);
                    word_t lvb = *(word_t *)(thisp + 0x50);
                    FUN_00464d74(lv + 1);
                    FUN_004647f4(lvb + lv * 0x178);
                    *(word_t *)(thisp + 0x50) = lvb;
                }
out:
                FUN_00002534(0x657b20, (word_t)&DAT_005a35c8);
                word_t l11b = FUN_0036a940(FUN_00002534(0x657b20, (word_t)&DAT_005a35c8), 0x198, 7);
                *(word_t *)(l11b + 0x18) = uVar2;
                *(word_t *)(l11b + 0x10) = uVar3;
                local_280 = u7;
                local_268 = local_290;
                local_288 = l12;
                local_278 = u14;
                local_270 = u13;
                FUN_004616d4(&local_288);
                FUN_00117cc4(l11b + 0x20, (word_t)&local_288, 0x178);
                l12 = l11b;
            }
        }
        FUN_00117cc4((word_t)&local_288, local_110b + l11, 0x178);
        FUN_004652ac(&local_288);
        if (!zr_flag) {
            FUN_00086840();
            local_2b8 = x8_ret;
            uVar2 = DAT_004baeb8;
            uVar3 = DAT_004baeb0;
            continue;
        }
        l11 += 0x178;
        l10--;
    }
}

/* FUN_00441b40 @ 0x441b40  (est. sk_parse_custom_class)
 * Parse a custom character-class element sequence into a 0x178-byte
 * class descriptor, dispatching on the sub-kind (2 => nested
 * FUN_0043ed70 / per-element paths; else FUN_00441688). Appends each
 * resolved descriptor into the vector at *unaff_x21 (0x178 stride).
 * SoftwareBreakpoint(1,0x441fdc..ff8) guards the count checks.
 * Confidence: low
 * Notes: operator tokens 0x2d2d/0x7e7e/0x2626; ']' token 0x5d; result
 * written through unaff_x21 */
void sk_parse_custom_class(word_t p1, word_t p2, word_t p3, word_t p4)
{
    word_t local_498[16], local_320[16], uStack_488, local_480;
    word_t local_318, local_198[8], uStack_188, local_190, auStack_b8[22];
    word_t u5, x9_ret, x1_ret, u9;
    word_t *x21;
    word_t local_478, uStack_470, auStack_310[47], auStack_168[22];
    word_t uStack_488b, local_180, uStack_170, local_178;
    word_t thisp = p1;
    word_t x19, x28, x22;
    FUN_0008e518();
    FUN_00464a38();
    word_t u4 = *(word_t *)(x19 + 8);
    word_t u11 = *(word_t *)(x19 + 0x18);
    sk_pair_t p = FUN_00463194();
    word_t u6 = p.hi;
    FUN_003a25d4(p4);
    while ((p.lo ^ u6) >> 0xe != 0) {
        p.lo = x28;
        p.hi = u6;
        FUN_00463194();
        u6 = p4;
        FUN_004635c8();
        if (x9_ret == 0) {
            FUN_003a25d4(p4);
        } else {
            FUN_00462788();
            p = FUN_002b439c();
            word_t hi = p.hi;
            FUN_003a25d4(p4);
            if (p.lo == 0x5d && hi == 0xe100000000000000ull) {
                FUN_003a25d4(hi);
                break;
            }
            p3 = 0;
            FUN_00463540(p.lo, hi);
            FUN_002a0cf8();
            FUN_00464e7c();
            if ((p4 & 1) != 0) break;
        }
        x28 = p.lo;
        FUN_00463194();
        FUN_004629cc();
        FUN_00462884(0x2d2d);
        FUN_0015e4f8();
        FUN_00464e7c();
        if ((p4 & 1) != 0) break;
        FUN_00463194();
        FUN_004629cc();
        FUN_00462884(0x7e7e);
        FUN_0015e4f8();
        FUN_00464e7c();
        if ((p4 & 1) != 0) break;
        FUN_00463194();
        FUN_00462870();
        FUN_00462884(0x2626);
        FUN_0015e4f8();
        FUN_00465314();
        if ((u4 & 1) != 0) break;
        u4 = FUN_0043942c();
        byte gt1 = 1 < u4;
        byte is2 = u4 == 2;
        if (is2) {
            u4 = *(word_t *)(x19 + 0x10);
            FUN_004340b0(local_320);
            if (local_318 == 0) {
                u4 = *(word_t *)(x19 + 0x10);
                FUN_00434af4(local_498);
                if (local_498[1] == 0) {
                    word_t u9 = u6;
                    if ((*(byte *)(x19 + 0x40) & 1) != 0) {
                        word_t u5 = FUN_00466600();
                        u4 = FUN_00463864();
                        FUN_0029fa0c();
                        FUN_004659bc();
                        if (!gt1) CL4_FATAL();            /* 0x441ff4 */
                        FUN_00462f24();
                        thunk_FUN_002b74c0();
                        FUN_003534e0();
                        word_t u7 = u6;
                        FUN_003a25d4(x28);
                        u9 = p.hi >> 0xe;
                        x28 = u11;
                        while (x28 >> 0xe != u9) {
                            FUN_00350b3c();
                            FUN_00353c30();
                            p = FUN_002b439c();
                            local_498[0] = p.lo; local_498[1] = p.hi;
                            FUN_0024917c(&local_320, local_498);
                            FUN_003a25d4(p.hi);
                            u9 = x28 >> 0xe;
                            if ((local_320[0] & 1) == 0) break;
                            FUN_00350b3c();
                            FUN_00353c30();
                            x28 = FUN_002b3b50().lo;
                        }
                        byte eq = u9 == u11 >> 0xe;
                        if (u9 < u11 >> 0xe) CL4_FATAL(); /* 0x441ff8 */
                        FUN_00351cd0(u11, x28);
                        u11 = thunk_FUN_002b74c0().lo;
                        FUN_00465da4();
                        u9 = u7;
                        FUN_003a25d4(u6);
                        FUN_0036b118(u5);
                        if ((u11 ^ p3) >> 0xe != 0) {
                            FUN_00352c4c(u11);
                            FUN_002b4120();
                            FUN_0042fe0c();
                            p = FUN_00350a04();
                            u11 = u7;
                            FUN_002a3e64(p.lo, p.hi, x28);
                            FUN_00354410();
                            FUN_003a25d4(u7);
                            u9 = *(word_t *)(x19 + 0x10);
                            if (u9 >> 0xe < u4 >> 0xe) CL4_FATAL(); /* 0x441fdc */
                            goto store;
                        }
                        FUN_003a25d4(u7);
                    }
                    FUN_0043ed70(auStack_168);
                    FUN_00117cc4((word_t)auStack_b8, (word_t)auStack_168, 0xb0);
                    FUN_00464918(auStack_b8);
                    if (is2) break;
                    FUN_00117cc4((word_t)local_498, (word_t)auStack_b8, 0xb0);
                    FUN_00461708(local_498);
                    u6 = u9;
                } else {
                    u9 = *(word_t *)(x19 + 0x10);
                    u11 = u6;
                    word_t hi = local_498[1];
                    u6 = local_498[0];
                    if (u9 >> 0xe < u4 >> 0xe) CL4_FATAL(); /* 0x441ff0 */
store:
                    local_498[0] = u6;
                    local_498[1] = hi;
                    uStack_488 = u4;
                    local_480 = u9;
                    FUN_00461738(local_498);
                    u6 = u11;
                }
            } else {
                if (*(word_t *)(x19 + 0x10) >> 0xe < u4 >> 0xe) CL4_FATAL(); /* 0x441fec */
                local_498[0] = local_320[0];
                local_498[1] = local_318;
                uStack_488 = u4;
                local_480 = *(word_t *)(x19 + 0x10);
                FUN_00461768(local_498);
            }
        } else {
            FUN_00441688(local_198);
            local_498[0] = local_198[0];
            uStack_488 = uStack_188;
            local_498[1] = local_190;
            local_480 = local_180;
            uStack_470 = uStack_170;
            local_478 = local_178;
            FUN_00461798(local_498);
        }
        FUN_00117cc4((word_t)auStack_310, (word_t)local_498, 0x178);
        word_t u9 = *x21;
        word_t probe = FUN_003a261c(u9);
        p4 = u6;
        u4 = u9;
        if ((probe & 1) == 0) {
            FUN_00463fb8(*(word_t *)(u9 + 0x10));
            FUN_0006b3f4();
            u4 = FUN_0045636c();
            p4 = u9;
        }
        u11 = *(word_t *)(u4 + 0x10);
        if (*(word_t *)(u4 + 0x18) >> 1 <= u11) {
            u5 = FUN_0006b42c();
            FUN_00351c7c(u5, u11 + 1);
            u4 = FUN_0045636c();
        }
        *(word_t *)(u4 + 0x10) = u11 + 1;
        p3 = 0;
        FUN_00117cc4(u4 + u11 * 0x178 + 0x20, (word_t)auStack_310, 0x178);
        *x21 = u4;
        FUN_00353abc();
        FUN_004421ac();
        u4 = *(word_t *)(x19 + 8);
        u11 = *(word_t *)(x19 + 0x18);
        p = FUN_00463194();
        u6 = p.hi;
        FUN_003a25d4(p4);
    }
    FUN_0008e500(x1_ret);
}

/* FUN_0043f454 @ 0x43f454  (est. sk_check_group_open)
 * Validate that the current token is a group-opening pair (kind
 * matching '\r\n' 0xa0d with tag 0xe2). Returns 1 when the opener is
 * valid, 0 otherwise, and 1 when a balanced-group fallback matches.
 * SoftwareBreakpoint(1,0x43f4e8/.ec) guards.
 * Confidence: low
 * Notes: opener token 0xa0d (CRLF), tag 0xe200000000000000 */
word_t sk_check_group_open(void)
{
    word_t x20_cur, x19_tag;
    FUN_003504d0();
    long k = FUN_0042c5a4();
    byte is2 = k == 2;
    if (1 < k) {
        FUN_0007c1c4();
        FUN_001ae8a8();
        word_t v = FUN_0034ecc8();
        if (is2) CL4_FATAL();                      /* 0x43f4e8 */
        if ((v & 0xffffff80) == 0 &&
            !(x20_cur == 0xa0d && x19_tag == 0xe200000000000000ull)) {
            FUN_0007c1c4();
            v = FUN_00465ba0();
            if ((v & 1) == 0) {
                FUN_0007c1c4();
                v = FUN_002bdc7c();
                if ((v & 1) == 0) {
                    FUN_0007c1c4();
                    FUN_0016749c();
                    FUN_0034ecc8();
                    if (!is2) {
                        FUN_002bd724();
                        FUN_0046511c();
                        return 0;
                    }
                    CL4_FATAL();                   /* 0x43f4ec */
                }
            }
        }
    }
    return 0;
}

/* FUN_0043f770 @ 0x43f770  (est. sk_resolve_group_value)
 * Resolve the current group/absent node into a value object. Bumps the
 * nesting counter at thisp+0x38 (guarded against overflow). For shallow
 * nesting (<0x40) either returns the singleton leaf or parses a '|'
 * separated pair group, appending each side into growable lists; deep
 * nesting emits the s_group_is_too_deeply_nested_005df750 diagnostic.
 * SoftwareBreakpoint(1,0x43fcac..d00) guards the counter checks.
 * Confidence: low
 * Notes: '|' token 0x7c; deep-nest string 0x5df750; error kind 0x24 */
word_t sk_resolve_group_value(word_t thisp, word_t x22)
{
    word_t x20_cur, x19_tag, x9_ret, x3, x8_ret, x8_ret2, is1, vec, lv7, lv10;
    word_t v3 = FUN_00466408();
    long nest = *(long *)(thisp + 0x38);
    long n1 = nest + 1;
    if ((long)nest == 0x7fffffffffffffff) CL4_FATAL();  /* 0x43fcf0 */
    *(long *)(thisp + 0x38) = n1;
    word_t start = *(word_t *)(thisp + 0x10);
    word_t result;
    if (n1 < 0x40) {
        FUN_0046400c();
        FUN_0029fa0c(start);
        FUN_00351a5c();
        FUN_003a25d4(0);
        if ((thisp ^ x22) >> 0xe == 0) {
            FUN_00002834(0x685b78);
            result = FUN_0036a940();
            *(word_t *)(result + 0x10) = start;
            *(word_t *)(result + 0x18) = start;
            if (n1 == 0) CL4_FATAL();               /* 0x43fcf8 */
            result |= 0xb000000000000000ull;
        } else {
            FUN_004639fc();
            FUN_00359018();
            word_t obj = FUN_0036a940();
            *(word_t *)(obj + 0x18) = DAT_004baeb8;
            *(word_t *)(obj + 0x10) = DAT_004baeb0;
            *(word_t *)(obj + 0x20) = FUN_0043fd04();
            start = *(word_t *)(thisp + 0x10);
            if ((FUN_0042f670(0x7c, 0xe100000000000000ull) & 1) != 0) { /* '|' */
                FUN_004653b0();
                FUN_00466244();
                /* append left side into growable list at x22 */
                word_t lv = *(word_t *)(thisp + 0x10);
                if (lv >> 0xe < start >> 0xe) CL4_FATAL();   /* 0x43fce8 */
                if ((FUN_003a261c(x22) & 1) == 0) {
                    FUN_00462974(*(word_t *)(x22 + 0x10));
                    x22 = FUN_00466594();
                }
                word_t c = *(word_t *)(x22 + 0x10);
                if (*(word_t *)(x22 + 0x18) >> 1 <= c) {
                    FUN_0006b42c();
                    FUN_00352480(FUN_0006b42c(), c + 1);
                    x22 = FUN_00466594();
                }
                *(word_t *)(x22 + 0x10) = c + 1;
                word_t base = x22 + c * 0x10;
                *(word_t *)(base + 0x20) = start;
                *(word_t *)(base + 0x28) = lv;
                word_t side = FUN_0043fd04();
                start = *(word_t *)(obj + 0x10);
                if (*(word_t *)(obj + 0x18) >> 1 <= start) {
                    FUN_0006b42c();
                    obj = FUN_00464cf4(FUN_0006b42c(), start + 1);
                }
                *(word_t *)(obj + 0x10) = start + 1;
                *(long *)(obj + start * 8 + 0x20) = side;
                word_t u12 = *(word_t *)(thisp + 0x10);
                word_t u4 = *(word_t *)(thisp + 0x18);
                FUN_004632a4();
                FUN_0029fa0c();
                FUN_004635c8();
                if (x9_ret != 0) {
                    FUN_00462788();
                    FUN_002b439c();
                    FUN_00354410();
                    FUN_003a25d4(0);
                    word_t hi = lv10;
                    if (lv7 == 0x7c && hi == 0xe100000000000000ull) {
                        FUN_003a25d4(hi);
                    } else {
                        sk_pair_t q = FUN_00351714();
                        FUN_00463540(q.lo, q.hi, 0x7c);
                        FUN_002a0cf8();
                        FUN_00465314();
                        if ((x3 & 1) == 0) goto right_missing;
                    }
                    FUN_004632a4();
                    FUN_0029fa0c();
                    FUN_00462a5c();
                    FUN_00462b00(u12, 1, u4);
                    sk_pair_t s = FUN_002b3f40();
                    word_t s0 = s.lo;
                    FUN_003a25d4(0);
                    byte is1 = (s.hi & 0xff) == 1;
                    if (is1) goto emit_pair;
                    if (u4 >> 0xe < s0 >> 0xe) CL4_FATAL(); /* 0x43fcec */
                    *(word_t *)(thisp + 0x10) = s0;
                    *(word_t *)(thisp + 0x18) = u4;
                    goto commit;
                }
                FUN_003a25d4(0);
right_missing:
                ; /* fall through to collapse */
            }
            FUN_00466244();
            /* collapse: single side -> return it, else build pair object */
            long cnt = *(long *)(obj + 0x10);
            if (cnt == 1) {
                FUN_0036b118(x22);
                if (*(long *)(obj + 0x10) == 0) CL4_FATAL(); /* 0x43fcfc */
                word_t v = *(word_t *)(obj + 0x20);
                FUN_0036b270(v & 0xfffffffffffffff);
                FUN_0036b118(obj);
                n1 = *(long *)(thisp + 0x38) - 1;
                if (*(long *)(thisp + 0x38) == 0) CL4_FATAL();  /* 0x43fcac */
                result = v;
            } else {
                FUN_00002834(0x685ba0);
                result = FUN_0036a940();
                if (cnt == 0) CL4_FATAL();         /* 0x43fd00 */
                if (*(long *)(x22 + 0x10) != cnt - 1) CL4_FATAL(); /* 0x43fd04 */
                *(long *)(result + 0x10) = obj;
                *(word_t *)(result + 0x18) = x22;
                n1 = *(long *)(thisp + 0x38) - 1;
                if (*(long *)(thisp + 0x38) == 0) CL4_FATAL();  /* 0x43fce4 */
                result |= 0xb000000000000000ull;
            }
        }
    } else {
        /* too deeply nested */
        word_t d[6];
        d[0]=1; d[1]=0xd000000000000024ull; d[2]=0; d[3]=start; d[4]=start; d[5]=0x24;
        FUN_00463014();
        FUN_0042ec68();
        FUN_00461430(d);
        *(byte *)(thisp + 0x58) = 1;
        FUN_00002834(0x685b78);
        result = FUN_0036a940();
        *(word_t *)(result + 0x10) = start;
        *(word_t *)(result + 0x18) = start;
        result |= 0xb000000000000000ull;
    }
commit:
    *(long *)(thisp + 0x38) = n1;
    FUN_004663ec(result, v3);
    return result;
emit_pair:
    /* emit the '|' pair record */
    FUN_00464608();
    word_t d[6];
    d[0]=0; d[1]=x8_ret; d[2]=0xed0000203a454c42ull; d[3]=start; d[4]=start;
    FUN_002acbb8(0xd000000000000015, x8_ret2 | 0x8000000000000000);
    FUN_00462a48(d);
    FUN_00463890();
    if (is1) {
        FUN_00461430(d);
    } else {
        word_t vec = *(word_t *)(thisp + 0x50);
        FUN_00459024(d, d);
        if ((FUN_003a261c(vec) & 1) == 0) {
            FUN_00462710(*(word_t *)(vec + 0x10));
            FUN_0006b3f4();
            vec = FUN_0045636c();
        }
        word_t c = *(word_t *)(vec + 0x10);
        if (*(word_t *)(vec + 0x18) >> 1 <= c) {
            FUN_0006b42c();
            FUN_00351c7c(FUN_0006b42c(), c + 1);
            vec = FUN_0045636c();
        }
        *(word_t *)(vec + 0x10) = c + 1;
        FUN_00117cc4(vec + c * 0x50 + 0x20, (word_t)d, 0x49);
        *(word_t *)(thisp + 0x50) = vec;
    }
    FUN_004632a4();
    FUN_0029fa0c();
    FUN_00351790();
    FUN_002b4120();
    FUN_003519a8();
    FUN_003a25d4();
    if (0 < (long)vec) {
        FUN_004632a4();
        FUN_0029fa0c();
        FUN_00462a5c();
        sk_pair_t q = FUN_003512c0();
        FUN_00462b00(q.lo, q.hi, start);
        sk_pair_t s = FUN_002b3f40();
        word_t s0 = s.lo;
        FUN_003a25d4(0);
        if ((s.hi & 0xff) != 1) {
            if (start >> 0xe < s0 >> 0xe) CL4_FATAL();     /* 0x43fcf4 */
            *(word_t *)(thisp + 0x10) = s0;
            *(word_t *)(thisp + 0x18) = start;
        }
    }
    goto commit_after;
commit_after:
    *(long *)(thisp + 0x38) = n1;
    FUN_004663ec(result, v3);
    return result;
}

/* FUN_0044ac3c @ 0x44ac3c  (est. sk_emit_group_prefix)
 * Fetch a 16-byte pair from FUN_00463f94 and copy 0x90 bytes through
 * it, then call FUN_00411bbc. */
void sk_emit_group_prefix(void)
{
    sk_pair_t p = FUN_00463f94();
    FUN_00117cc4(p.lo, p.hi, 0x90);
    FUN_00411bbc();
}

/* FUN_0044ac7c @ 0x44ac7c  (est. sk_format_group_value)
 * Format a group value marker into a 16-byte pair. Emits '=>' (0x3d3e)
 * style labels; when the flag at thisp+8 is set, use the 0x3e kind via
 * FUN_00462abc. Confidence: low
 * Notes: label 0xe90000000000003e */
sk_pair_t sk_format_group_value(word_t thisp)
{
    word_t x8_ret, x16_ret;
    word_t lo = 0xe90000000000003eull, hi = 0;
    FUN_004636cc();
    if (*(char *)(thisp + 8) != 1) {
        lo = FUN_00462abc(0x6720e0);
        sk_pair_t p = ((sk_pair_t (*)(word_t, word_t))x8_ret)(lo, 0x6720e0);
        lo = p.lo;
        hi = p.hi;
    }
    FUN_004649cc();
    FUN_002acbb8();
    if (*(char *)(thisp + 0x28) != 1) {
        FUN_000f4ae8();
        FUN_00027724(x16_ret);
        FUN_0046295c();
        ((void (*)(void))x8_ret)();
        FUN_00352c80();
    }
    FUN_00084180();
    FUN_002acbb8();
    FUN_003a25d4();
    sk_pair_t r = { lo, hi };
    return r;
}

/* FUN_0044ad60 @ 0x44ad60  (est. sk_emit_group_prefix_small)
 * Fetch a 0x50-byte descriptor via FUN_00463f94 and forward it to
 * sk_format_group_value. */
void sk_emit_group_prefix_small(void)
{
    sk_pair_t p = FUN_00463f94();
    FUN_00117cc4(p.lo, p.hi, 0x50);
    sk_format_group_value(0);
}

/* FUN_0044ad98 @ 0x44ad98  (est. sk_format_revision)
 * Format a 'REVISION' marker (token 0x4e4f4953524556) with a '=>' or
 * '=' separator based on the byte at unaff_x19. Returns the pair.
 * Confidence: low
 * Notes: token 0x4e4f4953524556 'REVISION' */
sk_pair_t sk_format_revision(void)
{
    char *unaff_x19 = (char *)0; word_t x8_ret;
    FUN_004644f8();
    FUN_002acbb8(0x4e4f4953524556ull, 0xe700000000000000ull);
    word_t lo = 0x3d3e;
    if (*unaff_x19 != 1) lo = 0x3d;
    word_t hi = 0xe200000000000000ull;
    if (*unaff_x19 != 1) hi = 0xe100000000000000ull;
    FUN_002acbb8(lo, hi);
    FUN_003a25d4(hi);
    FUN_0044ac7c();
    FUN_00465294();
    FUN_003a25d4((word_t)(unaff_x19 + 0x18));
    sk_pair_t r = { x8_ret, 0 };
    return r;
}

/* FUN_0044ae38 @ 0x44ae38  (est. sk_emit_revision)
 * Fetch a 0x68-byte descriptor via FUN_00464140 and forward to
 * sk_format_revision. */
void sk_emit_revision(void)
{
    sk_pair_t p = FUN_00464140();
    FUN_00117cc4(p.lo, p.hi, 0x68);
    sk_format_revision();
}

/* FUN_0044ae70 @ 0x44ae70  (est. sk_format_end_group)
 * Format an end-of-group marker. Emits the '=>'/'::' style label; when
 * the +0x30 flag is set uses the 0x3e kind; otherwise the label from
 * thisp+0x28. Returns the pair by value.
 * Confidence: low
 * Notes: label 0xe90000000000003e */
sk_pair_t sk_format_end_group(word_t thisp)
{
    word_t x8_ret, x16_ret, x1_ret, x30_ret;
    word_t lo = 0, hi = 0xe000000000000000ull;
    sk_pair_t p = FUN_004632e0();
    FUN_00463df8(p.lo, p.hi, 0x6833c8);
    FUN_00462728();
    FUN_00205844(&lo, &lo);
    word_t lo2 = lo;
    word_t hi2 = hi;
    if (*(char *)(thisp + 0x48) != 1) {
        word_t v;
        if (*(char *)(thisp + 0x30) == 1) {
            v = 0xe90000000000003eull;
            FUN_00464a98();
        } else {
            lo = *(word_t *)(thisp + 0x28);
            FUN_000f4ae8();
            FUN_00462abc(x16_ret);
            ((void (*)(void))x8_ret)();
            v = x1_ret;
        }
        FUN_00465c74();
        FUN_003a25d4(v);
        lo = lo2;
        hi = hi2;
    }
    sk_pair_t r = { lo, hi };
    return r;
}

/* FUN_0044af28 @ 0x44af28  (est. sk_emit_group_close)
 * Emit a group-close marker: either the 0x3e label (via FUN_00464a98)
 * or the folded label via FUN_000f4ae8/FUN_00027724. */
void sk_emit_group_close(void)
{
    word_t x8_ret, x16_ret, x30_ret; byte zr_flag = 0;
    sk_pair_t p = FUN_00351db4();
    if (zr_flag) {
        FUN_00464a98(p.lo, 0xe90000000000003eull, x30_ret);
        return;
    }
    FUN_000f4ae8();
    FUN_00027724(x16_ret);
    FUN_0046295c();
    ((void (*)(void))x8_ret)();
}

/* FUN_0044afa0 @ 0x44afa0  (est. sk_emit_group_close_ff)
 * Forward the current 4-word descriptor to sk_emit_group_close. */
void sk_emit_group_close_ff(word_t *thisp)
{
    (void)thisp;
    sk_emit_group_close();
}

/* FUN_0044afa4 @ 0x44afa4  (est. sk_emit_group_close_ff2)
 * Identical to sk_emit_group_close_ff. */
void sk_emit_group_close_ff2(word_t *thisp)
{
    (void)thisp;
    sk_emit_group_close();
}

/* FUN_0044afc8 @ 0x44afc8  (est. sk_emit_group_suffix)
 * Fetch a 0x99-byte descriptor via FUN_00463f94 and call FUN_00411bfc. */
void sk_emit_group_suffix(void)
{
    sk_pair_t p = FUN_00463f94();
    FUN_00117cc4(p.lo, p.hi, 0x99);
    FUN_00411bfc();
}

/* FUN_004421ac @ 0x4421ac  (est. sk_parse_custom_class_main)
 * Main custom-character-class parser. Walks the class's element
 * sequence, dispatching each parsed element kind (cases 0..5) to its
 * append/merge routine, growing the output vectors (0x178-byte stride)
 * as needed. Handles the '|'-alternation, quantifier, and nested-class
 * sub-cases, and folds sub-descriptors through sk_parse_char_class_body
 * / sk_char_class_parse. SoftwareBreakpoint guards all size-shrink and
 * index-bound checks (0x4451f4..5268).
 * Confidence: low
 * Notes: 3000+ line decompile; dominant control-flow hub for the
 * custom-class feature; element kinds routed by FUN_00463144 switch */
void sk_parse_custom_class_main(void)
{
    word_t *thisp = 0; word_t pcVar18 = 0, x8_ret = 0, x1_ret = 0, u8_flag = 0, iVar9 = 0;
    word_t x23 = 0, x22 = 0, x12_hi = 0, x33_hi = 0, x30_ret = 0;
    word_t stack_b[47], stack_c[47], stack_d[22], stack_f[22];
    word_t local_ab8[47], local_8c8[16];
    byte zr_flag = 0, cy_flag = 0;
    FUN_0008e518();
    word_t pc = (*DAT_00658cf0)(0);
    word_t obj = *(word_t *)pc;
    word_t count = *(word_t *)(obj + 2);
    if (count != 0) {
        /* walk the class element table, dispatching each element kind */
        word_t *slot = (word_t *)(obj + (count - 1) * 0x2f - 0x2b);
        for (;;) {
            if ((*(word_t *)(thisp + 4) & 1) != 0) break;
            FUN_0046400c();
            FUN_0029fa0c(slot);
            FUN_00462870();
            FUN_004635e0();
            FUN_00462af0();
            FUN_0015e4f8();
            FUN_000b4528();
            if ((count & 1) == 0) break;
            FUN_004635e0();
            FUN_001ee018();
            FUN_0042fd4c();
            /* nested element loop with kind dispatch */
            for (;;) {
                sk_pair_t tokp = FUN_002aca00(); word_t tok = tokp.lo;
                FUN_004648a0();
                FUN_00351714();
                FUN_0029fa0c();
                FUN_00465198();
                FUN_00465ff4();
                if (x8_ret == 0) {
                    /* append element into thisp+0x50 vector */
                    word_t d[7];
                    d[0]=0; d[1]=0; d[2]=0; d[3]=tok; d[4]=count; d[5]=3;
                    FUN_0042dc90();
                    FUN_00465038();
                    if (zr_flag) {
                        FUN_004644c0();
                        FUN_00461430();
                    } else {
                        word_t vec = thisp[10];
                        if ((FUN_004665d0() & 1) == 0) {
                            FUN_00462710(vec + 0x10);
                            FUN_0006b3f4();
                            vec = FUN_0045636c();
                        }
                        FUN_00463a78();
                        if (cy_flag) {
                            FUN_0006b42c();
                            FUN_004636f8();
                            vec = FUN_0045636c();
                        }
                        *(word_t *)(vec + 16) = count;
                        sk_pair_t q = FUN_004634d4(vec + x22 * 10);
                        FUN_00117cc4(q.lo, q.hi, 0x49);
                        thisp[10] = vec;
                    }
                } else {
                    /* resolve via FUN_00462af0 and continue */
                    FUN_00351714(FUN_003a25d4(count));
                    FUN_0029fa0c();
                    FUN_00462870();
                    FUN_00100e34();
                    FUN_00462af0();
                    FUN_0015e4f8();
                    FUN_000b4528();
                    if ((count & 1) != 0) {
                        FUN_00100e34();
                        FUN_001ee018();
                        FUN_0042fd4c();
                        break;
                    }
                }
                FUN_00463864();
                FUN_0029fa0c();
                if (FUN_00462d88() == 0) break;
                FUN_00462788();
                FUN_002b439c();
                FUN_00463f74();
                FUN_003a25d4();
                FUN_004635a4();
                FUN_00462a08();
                FUN_003524b0();
                FUN_004628c4();
                sk_pair_t s = FUN_002b3f40();
                FUN_00464ce4();
                /* dispatch on the element kind byte */
                word_t kind = x23;
                if (kind == 1) {
                    /* alternation / quantifier element */
                    FUN_00463864();
                    FUN_0029fa0c();
                    FUN_00463144();
                    if (u8_flag) goto element_done;
                    FUN_00462788();
                    FUN_002b439c();
                    FUN_0035aba4();
                    FUN_003a25d4(0);
                    if (tok == 0x0a && s.hi == 0xe100000000000000ull) {
                        FUN_003a25d4(s.hi);
                    } else {
                        FUN_00100efc();
                        FUN_00463540(0, 0, 10);
                        FUN_002a0cf8();
                        FUN_00465578();
                        if ((count & 1) == 0) goto element_done;
                    }
                    /* commit thisp+0x50 element with kind marker */
                    FUN_00350518(0, 0, thisp[0]);
                    FUN_0029fa0c();
                    FUN_00462a98();
                    FUN_00462a1c(thisp[2]);
                    FUN_002b3f40();
                    FUN_00463f64();
                    if (iVar9 == 1) {
                        FUN_00464378();
                        FUN_0001a1c8();
                        FUN_00463dd4();
                        word_t vec = thisp[2];
                        FUN_00462c04();
                        FUN_00463890();
                        if (!u8_flag) {
                            /* grow vector and memcpy 0x49-byte element */
                            FUN_004627a0();
                            FUN_004578dc(0, (word_t)FUN_00072178, (word_t)FUN_0045694c,
                                          (word_t)FUN_0045636c);
                            FUN_00462cd4();
                            FUN_004640a4();
                            FUN_00462908();
                            FUN_00117cc4(0, 0, 0x49);
                        }
                        FUN_00350518(0, 0, thisp[0]);
                        FUN_0029fa0c();
                        FUN_00462ba8();
                        FUN_00356328();
                        FUN_003a25d4();
                    } else {
                        FUN_00464588();
                        if (!iVar9) CL4_FATAL();
                    }
                } else if (kind == 3) {
                    /* group element: build the fold object */
                    FUN_0046322c();
                    FUN_00465128();
                    FUN_0036a940();
                    word_t g = FUN_00466348();
                    *(word_t *)(g + 0x20) = x8_ret;
                    *(word_t *)(g + 0x28) = 0xe100000000000000ull;
                    *(word_t *)(g + 0x30) = 10;
                    *(word_t *)(g + 0x38) = 0xe100000000000000ull;
                    *(word_t *)(g + 0x40) = 0xa0d;
                    *(word_t *)(g + 0x48) = 0xe200000000000000ull;
                    FUN_00430040();
                    FUN_004666a8();
                    FUN_00455db8();
                    FUN_00002834();
                    FUN_0036b6ac();
                } else if (kind == 4) {
                    /* continuation element */
                    FUN_00463864();
                    FUN_0029fa0c();
                    FUN_00463144();
                    if (!u8_flag) goto element_done;
                    FUN_00462788();
                    FUN_002b439c();
                    FUN_000b43e8();
                    FUN_003a25d4(0);
                    FUN_000b4390();
                    FUN_002bd9cc();
                    FUN_00351a44();
                    FUN_003a25d4();
                    if ((count & 1) != 0) {
                        FUN_00464e1c();
                        FUN_0042fd4c();
                        goto next;
                    }
                } else if (kind == 5) {
                    FUN_00463864();
                    FUN_0029fa0c();
                    FUN_00463144();
                    if (!u8_flag) goto element_done;
                    FUN_00462788();
                    FUN_002b439c();
                    FUN_0035aba4();
                    FUN_003a25d4(0);
                    if (tok == 0 && s.hi == 0xe100000000000000ull) {
                        FUN_003a25d4(s.hi);
                    } else {
                        FUN_00100efc();
                        FUN_00463540(0, 0, 0);
                        FUN_002a0cf8();
                        FUN_00465578();
                        if ((count & 1) == 0) goto element_done;
                    }
                    FUN_00350518(0, 0, thisp[0]);
                    FUN_0029fa0c();
                    FUN_00462a98();
                    FUN_00462a1c(thisp[2]);
                    FUN_002b3f40();
                    FUN_00463f64();
                    if (iVar9 == 1) {
                        FUN_004639c8();
                        FUN_0042f584(thisp[2], 0, x8_ret | 0x8000000000000000, thisp[2],
                                     thisp[2]);
                        FUN_00463890();
                        if (!u8_flag) {
                            FUN_004627a0();
                            FUN_004578dc(0, (word_t)FUN_00072178, (word_t)FUN_0045694c,
                                          (word_t)FUN_0045636c);
                            FUN_00462cd4();
                            FUN_004640a4();
                            word_t vec = thisp[10];
                            *(word_t *)(vec + 0x10) = s.lo + 1;
                            FUN_00117cc4(vec + (s.lo * 10 + 4) * 8, 0, 0x49);
                        }
                        FUN_00350518(0, 0, thisp[0]);
                        FUN_0029fa0c();
                        FUN_00462ba8();
                        FUN_00356328();
                        FUN_003a25d4();
                    } else {
                        FUN_00464588();
                        if (!iVar9) CL4_FATAL();
                    }
                }
element_done:
                thisp[2] = count;
                thisp[3] = s.hi;
next:
                if (x12_hi >> 0xe <= x33_hi >> 0xe) goto outer_next;
                CL4_FATAL();                          /* 0x44521c */
            }
        }
        /* fold nested class descriptors into the output vector */
        FUN_00441ff8(stack_b);
        FUN_00117cc4((word_t)stack_c, (word_t)stack_b, 0x178);
        int r = FUN_004617d4(stack_c);
        if (r != 1) {
            FUN_00117cc4((word_t)&local_ab8, (word_t)stack_c, 0x178);
            FUN_00458d30(&local_ab8, &local_8c8);
            FUN_00462fd4();
            FUN_004578dc(pcVar18, (word_t)FUN_00456cd8, (word_t)FUN_004567d8,
                         (word_t)FUN_0045636c);
            word_t lv = *(word_t *)(*(word_t *)pc + 0x10);
            FUN_00462b6c(lv);
            FUN_00457994();
            word_t outv = *(word_t *)pc;
            *(word_t *)(outv + 0x10) = lv + 1;
            FUN_00117cc4(outv + lv * 0x178 + 0x20, (word_t)&local_ab8, 0x178);
            /* parse the class via sk_char_class_parse and emit */
            FUN_00465764();
            FUN_004452a8(0, 1);
            FUN_00465764();
            FUN_00458d40();
            FUN_00117cc4((word_t)stack_d, (word_t)stack_f, 0xb0);
            FUN_00464918(stack_d);
        }
    }
outer_next:
    FUN_0008e500(x1_ret);
}

/* FUN_00445518 @ 0x445518  (est. sk_ref_range_slice)
 * Slice a sub-range out of a reference collection. Given the base
 * (param_2) and a negative offset, removes -param_1 leading elements
 * via FUN_003f8224 and returns the surviving (base, base+0x20) pair.
 * SoftwareBreakpoint(1,0x445580..588) guards the count bounds.
 * Confidence: medium */
sk_pair_t sk_ref_range_slice(word_t param1, word_t param2)
{
    if ((long)param1 < 0) CL4_FATAL();           /* 0x445580 */
    word_t n = *(word_t *)(param2 + 0x10);
    sk_pair_t r = FUN_003f8224(n, -(long)param1, 0, param2);
    word_t v = 0;
    if ((r.hi & 0xff) != 1) v = r.lo;
    if (v <= n) {
        if (-1 < (long)v) {
            sk_pair_t out = { param2, param2 + 0x20 };
            return out;
        }
        CL4_FATAL();                             /* 0x445588 */
    }
    CL4_FATAL();                                 /* 0x445584 */
}

/* FUN_00445588 @ 0x445588  (est. sk_ref_range_shrink)
 * Shrink a reference collection by -param_1 leading elements, using
 * FUN_0046128c. Guards the count bounds with SoftwareBreakpoint.
 * Confidence: medium */
void sk_ref_range_shrink(word_t param1)
{
    word_t *unaff_x20 = (word_t *)0;
    if (param1 == 0) return;
    if ((long)param1 < 0) CL4_FATAL();           /* 0x4455f0 */
    word_t n = *(word_t *)(*unaff_x20 + 0x10);
    sk_pair_t r = FUN_003f8224(n, -(long)param1, 0);
    if ((r.hi & 0xff) == 1) CL4_FATAL();         /* 0x4455f8 */
    if (r.lo <= n) {
        FUN_0046128c(r.lo, n);
        return;
    }
    CL4_FATAL();                                 /* 0x4455f4 */
}

/* FUN_004455f8 @ 0x4455f8  (est. sk_format_ref_pair)
 * Format a reference pair (param_1, param_2) through FUN_0022d2f4,
 * closing with sk_close_group and emitting via sk_format_ref_append.
 * Returns the final pair.
 * Confidence: medium
 * Notes: format strings 0x66e240 / 0x66e0d8 */
sk_pair_t sk_format_ref_pair(word_t param1, word_t param2, word_t param3)
{
    
    word_t local_b0[16], local_a0, uStack_98, local_90, local_88, local_78, uStack_70;
    word_t uVar1 = 0x66e240, uVar2 = 0x66e0d8;
    local_b0[0] = param1; local_b0[1] = param2;
    thunk_FUN_0036b270(param2);
    FUN_0022d2f4(local_b0, 0x6753a0, 0x66e240);
    sk_noop();
    local_a0 = 0xf;
    local_90 = 0;
    local_88 = 0;
    local_78 = 0;
    uStack_98 = uVar2;
    uStack_70 = param3;
    FUN_0043f634();
    FUN_0045904c(local_b0);
    sk_pair_t r = FUN_004458b0(0, 0, uVar1, (uint32_t)uVar2 & 1);
    FUN_0036b118(uVar1);
    return r;
}

/* FUN_00445724 @ 0x445724  (est. sk_emit_group_ref_pair)
 * Emit a group reference pair: acquire the lock, run the token-format
 * machinery, build the reference via FUN_0022d2f4, close the group
 * with sk_close_group, and release the lock. */
void sk_emit_group_ref_pair(void)
{
    word_t x8_ret, x8_ret2, x12_ret, x9_ret, x3_ret, x19_ret;
    word_t local_60[16], local_50, uStack_48, local_40, local_38, local_28;
    FUN_00084220();
    FUN_00356c6c();
    FUN_0007c028();
    (*DAT_00658cf0)(*(word_t *)(x8_ret + 0x40));
    FUN_000aa4ec();
    ((void (*)(word_t))(*((word_t **)x12_ret + 2)))(x9_ret - x8_ret2);
    word_t u1 = FUN_0031e030(x3_ret);
    FUN_00027754(x3_ret);
    FUN_00027754();
    word_t u2 = FUN_00027754();
    word_t pe = FUN_00100efc();
    FUN_0022d2f4(pe, 0, u1);
    FUN_0044587c();
    FUN_000a6f68();
    local_50 = 0xf;
    local_40 = 0;
    local_38 = 0;
    local_28 = 0;
    uStack_48 = u2;
    FUN_0043f634();
    FUN_00351a50();
    FUN_0045904c(local_60);
    pe = FUN_0009461c();
    FUN_004458b0(pe, 0, u1);
    FUN_003535a8();
    FUN_0036b118(u1);
    FUN_0036b118(x19_ret & 0xfffffffffffffff);
    FUN_0036b118(local_60[0]);
    FUN_0034d868();
    FUN_00084234();
}

void sk_noop(void);

/* FUN_0044587c @ 0x44587c  (est. sk_noop)
 * No-op stub (empty function body in the decompile). Present as a
 * named slot in the option/format dispatch table.
 * Confidence: high (exact) */
void sk_noop(void)
{
}

/* FUN_00445e64 @ 0x445e64  (est. sk_emit_ref_pair_opt)
 * Emit a reference pair with option handling: forward to
 * sk_emit_group_ref_pair, then apply the option and release refs. */
void sk_emit_ref_pair_opt(word_t p1, word_t p2, word_t p3)
{
    word_t x21_ret, x20_ret; (void)p1; (void)p2;
    FUN_00445724();
    FUN_00351e08();
    FUN_0040ff40(p3, 0);
    if (x21_ret != 0) {
        FUN_0036b118(p3);
        FUN_0036b118(x20_ret & 0xfffffffffffffff);
        FUN_0036b118();
    }
    FUN_0007c1c4();
}

/* FUN_00445eec @ 0x445eec  (est. sk_emit_quantifier)
 * Emit a quantifier token. Resolves the '{' / '=' / 'C' style based
 * on the token kind and argument count, then emits via
 * sk_format_ref_pair / FUN_0042f020.
 * Confidence: low
 * Notes: tokens 0x3d '=', 0x43 'C' */
void sk_emit_quantifier(void)
{
    word_t x8_ret, x8_ret2, x12_ret, x9_ret, x3_ret, x1_ret; uint32_t u1;
    sk_pair_t p;
    word_t u2 = FUN_00350a28();
    FUN_0007c028(u2, u2);
    (*DAT_00658cf0)(*(word_t *)(x8_ret + 0x40));
    FUN_000aa4ec();
    ((void (*)(word_t))(*((word_t **)x12_ret + 2)))(x9_ret - x8_ret2);
    u1 = FUN_0031e030();
    FUN_00027754();
    FUN_00027754();
    word_t l3 = FUN_00027754();
    FUN_000b43d0();
    FUN_0022d2f4();
    FUN_0042c11c();
    FUN_00351e08();
    p.lo = FUN_003a25d4(x1_ret); p.hi = 0;
    word_t v;
    if ((u1 & 0xff) == 1) {
        v = 0x3d;
    } else {
        if (0 < l3) {
            FUN_0007c1c4();
            p = FUN_0042f020();
            if ((p.lo & 1) != 0) {
                v = 0x43;
                goto emit;
            }
        }
        v = 0;
    }
emit:
    FUN_0007c1c4(p.lo, p.hi, v);
    FUN_004455f8();
    FUN_00350b90();
    FUN_003a25d4();
    FUN_00462ee8();
}

/* FUN_00446028 @ 0x46028  (est. sk_emit_capture_group)
 * Emit a capture-group prefix using the token-format machinery and
 * the capture-name lookup. Guards the recursion counter.
 * Confidence: low
 * Notes: FUN_0045027c is a thunk */
void sk_emit_capture_group(word_t x30)
{
    
    FUN_00084220();
    word_t l2 = FUN_00350980();
    word_t l3 = thunk_FUN_0045027c();
    FUN_003511d8(0xff);
    word_t u4 = FUN_00377824();
    FUN_00464f4c();
    FUN_000b4390();
    FUN_003516d8();
    word_t u5 = FUN_00377bec();
    word_t l6 = FUN_00310e08(0, u4, u5);
    FUN_00077894(l2 + *(int *)(l6 + 0x24));
    l2 = thunk_FUN_0045027c();
    if (l3 <= l2) {
        FUN_00084234(l3, l2, x30);
        return;
    }
    CL4_FATAL();                                 /* 0x4460cc */
}

/* FUN_004460cc @ 0x460cc  (est. sk_emit_named_group)
 * Emit a named capture-group prefix via the token machinery, folding
 * the group name through FUN_000277b8/FUN_0031afcc. */
void sk_emit_named_group(word_t p1, word_t p2, word_t p3)
{
    word_t x8_ret, x8_ret2, x9_ret, x9_ret2, x12_ret, x16_ret, x30_ret;
    FUN_00084220();
    word_t u1 = p3;
    FUN_003509ec();
    FUN_004633e0();
    u1 = FUN_00377824(0, u1);
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658cf0)(0);
    word_t l2 = 0 - x8_ret2;
    FUN_000277b8(p3);
    FUN_00084180(l2);
    ((void (*)(void))x9_ret)();
    FUN_0031afcc(p3);
    FUN_00077894(x8_ret, l2);
    ((void (*)(void))x9_ret2)();
    ((void (*)(word_t, word_t))(*((word_t **)x16_ret + 1)))(l2, u1);
    FUN_00084234(x30_ret);
}

/* FUN_004461bc @ 0x461bc  (est. sk_format_capture_ref)
 * Format a capture-group reference token. Builds the token buffer via
 * FUN_00365b6c; on failure emits an error token, on success emits the
 * group-ref formatter. Returns the built pair via x8.
 * Confidence: low */
void sk_format_capture_ref(word_t p1, word_t p2, word_t p3)
{
    word_t x30_ret;
    word_t auStack_28[10], auStack_30[8];
    word_t x8_ret, x8_ret2, x12_ret, x13_ret;
    sk_pair_t p;
    word_t u2;
    FUN_0008e518();
    FUN_003509ec();
    FUN_0007c028();
    (*DAT_00658cf0)(*(word_t *)(x8_ret + 0x40));
    (*DAT_00658cf0)(0);
    word_t fn = *(word_t *)(x12_ret + 0x10);
    FUN_00351274();
    ((void (*)(void))fn)();
    FUN_00464234();
    u2 = FUN_00002534();
    int i1 = FUN_00365b6c(auStack_28, 0 - (x8_ret2 + 0xf & 0xfffffffffffffff0) - x13_ret,
                          p3, u2, 0xe);
    if (i1 == 0) {
        FUN_00350518();
        word_t pe = 0;
        ((void (*)(word_t, word_t, word_t))fn)(pe, 0, p3);
        FUN_00350968(0);
        FUN_00459074();
        FUN_00463a58();
        p = FUN_0036993c();
        u2 = p.lo;
        FUN_00077894(p.hi, 0 - (x8_ret2 + 0xf & 0xfffffffffffffff0));
        FUN_00448dd8();
    } else {
        FUN_000026e8(auStack_28);
        FUN_0009461c();
        FUN_0035187c();
        sk_pair_t p = FUN_0036993c();
        u2 = p.lo;
        ((void (*)(word_t))fn)(p.hi);
    }
    FUN_0008e500(u2, x30_ret);
}

/* FUN_00446b64 @ 0x446b64  (est. sk_emit_conditional_error)
 * Emit a conditional-group diagnostic when the value cannot be
 * resolved: builds the 'expected ...' error token via FUN_0035063c
 * and commits it. */
void sk_emit_conditional_error(void)
{
    word_t thisp = 0, x9_ret;
    word_t auStack_80[10];
    FUN_0008409c();
    word_t v = FUN_0040feac(*(word_t *)(thisp + 0x10), 0);
    if ((v & 1) == 0) {
        FUN_00464248();
        FUN_0035063c(auStack_80, 0xd00000000000001e, x9_ret | 0x8000000000000000);
        FUN_0042f584();
        FUN_0042ec68(auStack_80);
        FUN_00461430(auStack_80);
    }
}

/* FUN_004458b0 @ 0x4458b0  (est. sk_format_group_options)
 * Emit the group-option / newline-mode specifier. Iterates the option
 * list, formatting each newline-matching-mode entry (kinds 3/4/5 and
 * the default 'newline_sequence' path) into a growable descriptor
 * vector, then emits the closing ref-set and returns.
 * Confidence: low
 * Notes: strings s_newline_sequence_matching_mode_005e0190 and
 * s_newline_matching_mode_005e01b0; option element stride 0x30 */
sk_pair_t sk_format_group_options(word_t p1, word_t p2, word_t p3, byte p4)
{
    word_t local_108[16], local_f8, local_f0, local_e8, local_d0, local_c8;
    word_t local_b8, local_b0, lStack_a8, local_a0, lStack_98, local_90, lStack_88;
    word_t local_80, uStack_78, local_70;
    word_t thisp = 0, x21, x22, x20, x8_ret, x8_ret2;
    byte unaff_w24;
    word_t uVar5 = p3;
    local_f0 = p4;
    FUN_0035098c();
    local_108[0] = FUN_00466244();
    local_f8 = uVar5;
    FUN_0036b270(local_108[1]);
    FUN_0036b270(p3);
    FUN_0036b270(x21 & 0xfffffffffffffff);
    local_e8 = FUN_0041ca38();
    word_t src = x22;
    if (x20 != 0) src = x20;
    word_t n = *(word_t *)(src + 0x10);
    if (n == 0) {
        FUN_00356328();
        FUN_0036b270();
        FUN_0036b118(src);
    } else {
        FUN_00086840();
        FUN_00086840();
        FUN_0036b270();
        word_t list = (word_t)&DAT_00657778;
        word_t *slot = (word_t *)(src + 0x48);
        do {
            word_t v7 = *(slot - 2);
            word_t kind = *(slot - 1) >> 0x3d;
            byte is5 = *(slot - 1) >> 0x3d == 5;
            switch (*(slot - 1) >> 0x3d) {
            case 3:
                FUN_00464ed0();
                FUN_003a25d4(local_c8);
                FUN_00463824();
                FUN_004635d4(0, 0x80000000005df890);
                FUN_002acbb8();
                FUN_004639e4();
                FUN_00465680();
                if (!is5) {
                    if ((FUN_003a261c(list) & 1) == 0) {
                        FUN_00462710(*(word_t *)(list + 0x10));
                        FUN_0006b3f4();
                        list = FUN_0045636c();
                    }
                    word_t c = *(word_t *)(list + 0x10);
                    if (*(word_t *)(list + 0x18) >> 1 > c) {
                        *(long *)(list + 0x10) = c + 1;
                        FUN_00465150(list + c * 0x50);
                        x22 = list;
                        break;
                    }
                    word_t g = FUN_0006b42c();
                    list = FUN_00464cf4(g, c + 1);
                    *(long *)(list + 0x10) = c + 1;
                    FUN_00465150(list + c * 0x50);
                    x22 = list;
                } else {
                    FUN_00461430(&local_b8);
                }
                break;
            case 4:
                FUN_00464ed0();
                FUN_003a25d4(local_c8);
                FUN_00463824();
                FUN_004635d4(0, 0x80000000005df890);
                FUN_002acbb8();
                FUN_004639e4();
                break;
            case 5:
                /* newline-sequence mode */
                break;
            default:
                FUN_00464ed0();
                FUN_003a25d4(local_c8);
                FUN_00463824();
                FUN_004635d4(0, 0x80000000005df890);
                FUN_002acbb8();
                FUN_004639e4();
            }
            FUN_00465680();
            if (is5) {
                FUN_00461430(&local_b8);
            } else {
                if ((FUN_003a261c(list) & 1) == 0) {
                    FUN_00462710(*(word_t *)(list + 0x10));
                    FUN_0006b3f4();
                    list = FUN_0045636c();
                }
                word_t c = *(word_t *)(list + 0x10);
                if (*(word_t *)(list + 0x18) >> 1 <= c) {
                    word_t g = FUN_0006b42c();
                    list = FUN_00464cf4(g, c + 1);
                }
                *(long *)(list + 0x10) = c + 1;
                FUN_00465150(list + c * 0x50);
                x22 = list;
            }
            n--;
            slot += 6;
        } while (n != 0);
        FUN_0036b118(src);
        x21 = local_e8;
    }
    word_t clist = (word_t)&DAT_006577e0;
    word_t n2 = *(word_t *)(x21 + 0x10);
    if (n2 != 0) {
        word_t *sl = (word_t *)(x21 + 0x20);
        FUN_00463824();
        do {
            word_t v8 = sl[1];
            if (v8 != 0) {
                FUN_003a25e0(v8, 3);
                FUN_00077894(&local_d0);
                FUN_000b2260();
                FUN_003a25d4(local_c8);
                if ((FUN_000b2260() & 1) == 0) {
                    FUN_004647c0();
                    word_t d[6];
                    d[0]=1; d[1]=x8_ret; d[2]=0; d[3]=sl[4]; d[4]=sl[5];
                    d[5]=sl[0]; 
                    FUN_002acbb8();
                    FUN_002acbb8(x8_ret2 - 0xb, 0x80000000005df7f0);
                    d[0]=1; d[5]=0x21;
                    FUN_0042ec68(local_108, &local_b8);
                    FUN_00461430(&local_b8);
                } else {
                    FUN_003a25d4(v8);
                }
            }
            sl += 7;
            FUN_003a25d4(v8);
            n2--;
        } while (n2 != 0);
    }
    FUN_003a25d4(clist);
    word_t u5 = local_108[0];
    FUN_0036b270(local_108[0] & 0xfffffffffffffff);
    FUN_0044632c(u5);
    FUN_0036b118(u5 & 0xfffffffffffffff);
    if (local_f0 == 1) {
        FUN_0036b270(local_108[1]);
        FUN_0036b270(local_f8);
        FUN_0036b270(u5 & 0xfffffffffffffff);
    } else {
        FUN_0036b270(local_108[1]);
        FUN_0036b270(local_f8);
        FUN_0036b270(x22);
        FUN_0036b270(u5 & 0xfffffffffffffff);
        FUN_0042ed6c(x22);
    }
    FUN_0036b118(x22);
    FUN_0036b118(local_e8);
    FUN_0036b118(local_f8);
    FUN_0036b118(local_108[1]);
    FUN_0036b118(u5 & 0xfffffffffffffff);
    FUN_003507e0();
    sk_pair_t out = {0,0};
    return out;
}

/* FUN_00446bd4 @ 0x446bd4  (est. sk_emit_group_sequence)
 * Emit a group's element sequence. Iterates the two element lists
 * (at auVar14+0x18 and +0x38), formatting each element kind (case
 * values 1/8/d/e/f/10/11 and the default path) into a 0x50-byte
 * record appended to the output vector at thisp+0x28. Guards via the
 * token helpers. SoftwareBreakpoint guards.
 * Confidence: low
 * Notes: two near-identical loops over the two lists; element record
 * stride 0x50 */
void sk_emit_group_sequence(void)
{
    word_t auVar14[16];
    word_t thisp = 0, x8_ret, x8_ret2, x9_ret, x10_ret, x11_ret;
    word_t lVar11, lVar12, uVar9, uVar10, uVar8, uVar7, uVar6;
    word_t in_stack_00000050, in_stack_00000070, in_stack_00000078;
    word_t in_stack_00000080, in_stack_00000088, in_stack_00000090, in_stack_00000098;
    byte bVar4;
    FUN_00465540();
    word_t l12 = *(word_t *)(*(word_t *)(auVar14[0] + 0x18) + 0x10);
    if (l12 != 0) {
        FUN_00464f24();
        FUN_00464040();
        FUN_00463cc8();
        FUN_00464040();
        word_t *slot = (word_t *)(x8_ret + 0x30);
        FUN_00463824();
        do {
            word_t a = *(slot - 2);
            word_t b = *(slot - 1);
            word_t c = *slot;
            slot += 3;
            byte kind = a;
            byte is13 = kind == 0x13;
            switch (kind) {
            case 1:
            case 8:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
                FUN_004631fc();
                FUN_003a25d4(in_stack_00000050);
                FUN_00463824();
                FUN_004635d4(uVar8, x9_ret - 0x20 | 0x8000000000000000);
                FUN_002acbb8();
                FUN_0046373c();
                in_stack_00000080 = x8_ret2;
                in_stack_00000088 = uVar7;
                break;
            default:
                break;
            }
            in_stack_00000050 = in_stack_00000088;
            in_stack_00000090 = 0;
            in_stack_00000098 = 0;
            in_stack_00000070 = b;
            in_stack_00000078 = c;
            FUN_00465e2c();
            if (is13) {
                FUN_00461430(0);
            } else {
                word_t buf = *(word_t *)(thisp + 0x28);
                if ((FUN_003a261c(buf) & 1) == 0) {
                    FUN_00462710(*(word_t *)(buf + 0x10));
                    FUN_0006b3f4();
                    buf = FUN_0045636c();
                }
                word_t cnt = *(word_t *)(buf + 0x10);
                if (*(word_t *)(buf + 0x18) >> 1 <= cnt) {
                    uVar10 = FUN_0006b42c();
                    FUN_00351c7c(uVar10, cnt + 1);
                    buf = FUN_0045636c();
                }
                *(word_t *)(buf + 0x10) = cnt + 1;
                FUN_004647f4(buf + cnt * 0x50);
                *(word_t *)(thisp + 0x28) = buf;
            }
            l12--;
        } while (l12 != 0);
    }
    l12 = *(word_t *)(*(word_t *)(auVar14[0] + 0x38) + 0x10);
    if (l12 != 0) {
        FUN_00464f24();
        FUN_00464040();
        FUN_00463cc8();
        FUN_00464040();
        word_t *slot = (word_t *)(x8_ret + 0x30);
        FUN_00463824();
        do {
            byte kind = *(slot - 2);
            word_t b = *(slot - 1);
            word_t c = *slot;
            slot += 3;
            byte is13 = kind == 0x13;
            byte gt12 = 0x12 < kind;
            switch (kind) {
            case 1:
            case 8:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x10:
            case 0x11:
                FUN_004631fc();
                FUN_003a25d4(in_stack_00000050);
                FUN_00463824();
                FUN_004635d4(uVar8, x9_ret - 0x20 | 0x8000000000000000);
                FUN_002acbb8();
                FUN_0046373c();
                in_stack_00000080 = x8_ret2;
                in_stack_00000088 = uVar7;
                break;
            default:
                break;
            }
            in_stack_00000050 = in_stack_00000088;
            in_stack_00000090 = 0;
            in_stack_00000098 = 0;
            in_stack_00000070 = b;
            in_stack_00000078 = c;
            FUN_00465e2c();
            if (is13) {
                FUN_00461430(0);
            } else {
                word_t buf = *(word_t *)(thisp + 0x28);
                if ((FUN_003a261c(buf) & 1) == 0) {
                    FUN_00462710(*(word_t *)(buf + 0x10));
                    FUN_0006b3f4();
                    buf = FUN_0045636c();
                }
                word_t cnt = *(word_t *)(buf + 0x10);
                FUN_00465d98(*(word_t *)(buf + 0x18));
                if (gt12) {
                    FUN_0006b42c();
                    FUN_004636f8();
                    buf = FUN_0045636c();
                }
                *(word_t *)(buf + 0x10) = c;
                FUN_004647f4(buf + cnt * 0x50);
                *(word_t *)(thisp + 0x28) = buf;
            }
            l12--;
        } while (l12 != 0);
    }
    FUN_00465524(auVar14[1]);
}

/* FUN_0044632c @ 0x44632c  (est. sk_dump_regex_tree)
 * Recursively dump a regex AST node into the human-readable format.
 * Dispatches on the node kind (default/1..10): prints 'branch reset
 * group', 'non-atomic lookahead', 'conditional', 'interpolation',
 * 'unsupported expression', 'script run', 'lookbehind' diagnostics,
 * recursively dumps child nodes, and folds range/quantifier nodes.
 * Confidence: low
 * Notes: strings s_branch_reset_group_005e0210, s_non_atomic_
 * lookahead_005e01f0, s_conditional_005a18f0, s_interpolation_
 * 005a18e0, s_expression_is_not_quantifiable_005df770,
 * s_script_run_005a1900, s_lookbehind_005a1910 */
void sk_dump_regex_tree(void)
{
    word_t x8_ret, x9_ret;
    word_t local_368, local_360, local_358, uStack_350, local_348, local_340;
    word_t uStack_338, local_330, local_320, local_300, local_2f8, uStack_2f0;
    word_t local_1f0, local_1e8, local_1e0, local_1d8, local_1d0, local_1c8;
    word_t uStack_1c0, local_1b8, local_1b0, local_1a8, local_1a0, local_188;
    word_t local_70[16], local_60, uStack_58, local_50, uStack_48, local_40;
    word_t uStack_38, local_30, local_28, uStack_20, local_18, uStack_10, local_8;
    word_t local_78[8];
    word_t uVar13;
    sk_pair_t auVar16 = FUN_00084220();
    local_70[0] = 0; local_70[1] = 0;
    uVar13 = auVar16.lo;
    switch (uVar13 >> 0x3c) {
    default:
    case 1:
        /* recursively dump the child list */
        {
            word_t l12 = *(word_t *)((uVar13 & 0xfffffffffffffff) + 0x10);
            word_t n = *(word_t *)(l12 + 0x10);
            local_70[0] = 0; local_70[1] = 0;
            if (n != 0) {
                FUN_0036b270(l12);
                word_t off = 0x20;
                do {
                    word_t child = *(word_t *)(l12 + off);
                    FUN_0036b270(child & 0xfffffffffffffff);
                    FUN_00466388();
                    sk_dump_regex_tree();
                    FUN_0036b118(child & 0xfffffffffffffff);
                    off += 8;
                    n--;
                } while (n != 0);
            }
            FUN_00084234(l12, auVar16.hi);
            FUN_0036b118();
            return;
        }
    case 2:
        FUN_00117cc4((word_t)&local_1f0, (uVar13 & 0xfffffffffffffff) + 0x10, 0x80);
        FUN_00465788();
        FUN_00458a90();
        /* dispatch on the node type byte */
        if (local_1a0 == 1) {
            /* branch reset group */
            word_t pc = (word_t)"branch reset group";
            FUN_004638a8();
            FUN_003a25d4(local_360);
            FUN_00463824();
            local_340 = x8_ret - 0xb;
            goto emit_tag;
        }
        if (local_1a0 == 2) {
            FUN_00446bd4(&local_368);
            break;
        }
        if (local_1a0 == 3) {
            /* non-atomic lookahead / lookbehind / script run / unsupported */
            if (local_1f0 == 6) {
                local_368 = 0;
                local_360 = 0xe000000000000000ull;
                FUN_002a4ab4(0x1d);
                FUN_003a25d4(local_360);
                local_368 = 0xd000000000000014;
                local_360 = 0x80000000005e01d0;
                FUN_004629e0();
                FUN_004635d4();
                FUN_002acbb8();
                FUN_00463268();
                local_340 = 0xd000000000000014;
                uStack_338 = 0x80000000005e01d0;
                local_320 = 0x1d;
            } else {
                FUN_004638a8();
                FUN_003a25d4(local_360);
                local_368 = 0x7220747069726373;
                local_360 = 0xea00000000006e75;
                FUN_004629e0();
                FUN_004635d4();
                FUN_002acbb8();
                FUN_00463268();
                local_340 = 0; uStack_338 = 0;
                local_320 = 0;
            }
emit_tag:
            uStack_338 = local_340 | 0x8000000000000000;
            local_320 = 0;
            FUN_0042ec68(&local_368);
            FUN_00461430(&local_368);
            break;
        }
        /* unsupported quantifiable expression */
        FUN_004108a0(&local_1f0, local_300);
        FUN_0006a4c0(&local_1f0, local_1d8);
        FUN_00351a44();
        FUN_00458e50();
        FUN_000b4390();
        ((void (*)(void))x8_ret)();
        FUN_00350b90();
        FUN_000026e8(&local_1f0);
        local_1f0 = 1;
        FUN_00462a34((word_t)"expression is not quantifiable");
        local_1e8 = x9_ret + 3;
        local_1d0 = local_1d8;
        local_1c8 = 0x13;
        uStack_1c0 = 0;
        local_1b8 = 0;
        local_1b0 = 0;
        local_1a8 = 0x24;
        local_1d8 = uVar13 & 0xfffffffffffffff;
        FUN_0042ec68(&local_1f0);
        FUN_00461430(&local_1f0);
        break;
    case 3:
        FUN_00464538();
        FUN_003a25d4(local_1e8);
        local_1f0 = 0x6f697469646e6f63;
        local_1e8 = 0xeb000000006c616e;
        FUN_004629e0();
        FUN_004635d4();
        FUN_002acbb8();
        FUN_004639b0();
        local_1c8 = 0; uStack_1c0 = 0;
        goto emit_block;
    case 7:
        FUN_00464538();
        FUN_003a25d4(local_1e8);
        FUN_00465054();
        local_1e8 = x9_ret & 0xffffffff | 0xed00006e00000000;
        local_1f0 = x8_ret;
        FUN_004629e0();
        FUN_004635d4();
        FUN_002acbb8();
        FUN_004639b0();
        local_1c8 = 0; uStack_1c0 = 0;
        goto emit_block;
    case 10:
        FUN_00464538();
        FUN_003a25d4(local_1e8);
        local_1f0 = 0x6620746e65736261;
        local_1e8 = 0xef6e6f6974636e75;
        FUN_004629e0();
        FUN_004635d4();
        FUN_002acbb8();
        FUN_004639b0();
        local_1c8 = 0; uStack_1c0 = 0;
emit_block:
        local_1b8 = 0;
        local_1b0 = 0;
        local_1a8 = 0;
        FUN_0042ec68(&local_1f0);
        FUN_00461430(&local_1f0);
        break;
    case 8:
        FUN_00117cc4((word_t)&local_1f0, (uVar13 & 0xfffffffffffffff) + 0x10, 0xb0);
        FUN_00465788();
        FUN_004589e8();
        FUN_0044791c(&local_1f0, 0);
        FUN_004589f8(&local_1f0);
        break;
    case 9:
        {
            word_t l12 = *(word_t *)((uVar13 & 0xfffffffffffffff) + 0x28);
            word_t n = *(word_t *)(l12 + 0x10);
            local_70[0] = 0; local_70[1] = 0;
            if (n != 0) {
                FUN_0036b270(l12);
                word_t off = 0x20;
                do {
                    FUN_00117cc4((word_t)&local_1f0, l12 + off, 0x178);
                    FUN_00465788();
                    FUN_00458d30();
                    FUN_00448298(&local_1f0);
                    FUN_00458d40(&local_1f0);
                    off += 0x178;
                    n--;
                } while (n != 0);
                FUN_0036b118(l12);
            }
            break;
        }
    case 4:
    case 5:
    case 6:
    case 0xb:
        break;
    }
    FUN_00084234(auVar16.hi);
}

/* FUN_0044ab14 @ 0x44ab14  (est. sk_format_oniguruma_callout)
 * Format an Oniguruma-style callout marker: when a pending value
 * exists, emit it via sk_flatten_ref_list; then flush the ref-list.
 * Returns the 16-byte pair by value.
 * Confidence: medium
 * Notes: string s_oniguruma_callout_of_contents via FUN_0044c918 */
sk_pair_t sk_format_oniguruma_callout(word_t param1)
{
    sk_pair_t out = { 0, 0 };
    sk_pair_t x1_ret = FUN_00463e04();
    if (x1_ret.lo != 0) {
        sk_pair_t p = FUN_0044c918(x1_ret.lo);
        FUN_00463fe8();
        FUN_002acbb8();
        FUN_002acbb8(p.lo, p.hi);
        FUN_003a25d4(p.hi);
    }
    sk_flatten_ref_list(param1);
    FUN_000e72d4();
    FUN_003a25d4(param1);
    return out;
}

/* FUN_0044abb0 @ 0x44abb0  (est. sk_emit_callout_value)
 * Emit a callout value: expand it via the FUN_004108a0 machinery and
 * apply through the vtable callback. */
void sk_emit_callout_value(void)
{
    word_t x8_ret;
    word_t auStack_58[24], local_40;
    FUN_004108a0(auStack_58);
    FUN_0006a4c0(auStack_58, local_40);
    FUN_00356328();
    FUN_00027754();
    word_t u1 = FUN_000a6bb8();
    FUN_003504ac(u1);
    ((void (*)(void))x8_ret)();
    FUN_00351a50();
    FUN_000026e8(auStack_58);
    FUN_0009461c();
}

/* FUN_0044b000 @ 0x44b000  (est. sk_format_balanced_capture)
 * Format a balanced-capture marker. Emits the 'CAPTURE balance:'
 * label (token 0x6c61632045524350 / 0xed00002074756f6c) followed by
 * the capture descriptor fields, and returns the pair.
 * Confidence: medium
 * Notes: label words 0x6c61632045524350 'CAPTURE cal' / 0xed0000 2074 756f6c */
sk_pair_t sk_format_balanced_capture(void)
{
    word_t x8_ret;
    word_t local_60, uStack_58, uStack_50, uStack_48, local_30, uStack_28;
    word_t *x19 = (word_t *)0;
    FUN_004644f8();
    local_30 = 0;
    uStack_28 = x8_ret;
    sk_pair_t p = FUN_002acbb8(0x6c61632045524350ull, 0xed00002074756f6cull);
    uStack_58 = x19[1];
    local_60 = x19[0];
    uStack_48 = x19[3];
    uStack_50 = x19[2];
    FUN_00463df8(p.lo, p.hi, 0x683b78);
    FUN_00462728();
    FUN_00205844(&local_60, &local_30);
    sk_pair_t r = { local_30, uStack_28 };
    return r;
}

/* FUN_0044b088 @ 0x44b088  (est. sk_emit_balanced_capture)
 * Emit the balanced-capture marker via sk_format_balanced_capture. */
void sk_emit_balanced_capture(void)
{
    FUN_00463778();
    sk_format_balanced_capture();
}

/* FUN_0044b0c4 @ 0x44b0c4  (est. sk_emit_quantifier_value)
 * Emit a quantifier value via FUN_004632f4/FUN_00411c8c. */
void sk_emit_quantifier_value(void)
{
    FUN_004632f4();
    FUN_00411c8c();
}

/* FUN_0044b0f0 @ 0x44b0f0  (est. sk_format_group_open_set)
 * Format a group-open set: append each 0x10-byte element of the
 * vector at x20+0x10 into the growable list at x19, then emit the
 * '{' ... '}' wrapper via FUN_001bc440. Returns the '{' pair.
 * Confidence: medium
 * Notes: '{' token 0x7b; FUN_000a6fe0; element stride 0x10 */
sk_pair_t sk_format_group_open_set(void)
{
    word_t x19 = 0, x20 = 0;
    word_t l6 = *(word_t *)(x20 + 0x10);
    word_t n = *(word_t *)(l6 + 0x10);
    FUN_000a6fe0();
    if (n != 0) {
        FUN_004651a8();
        word_t *slot = (word_t *)(l6 + 0x28);
        do {
            word_t a = *(slot - 1);
            word_t b = *slot;
            word_t cnt = *(word_t *)(x19 + 0x10);
            word_t cap = *(word_t *)(x19 + 0x18);
            thunk_FUN_0036b270(b);
            if (cap >> 1 <= cnt) {
                FUN_000dbed0(1 < cap);
                FUN_0006a374();
            }
            slot += 4;
            *(word_t *)(x19 + 0x10) = cnt + 1;
            word_t base = x19 + cnt * 0x10;
            *(word_t *)(base + 0x20) = a;
            *(word_t *)(base + 0x28) = b;
            n--;
        } while (n != 0);
    }
    FUN_00463210();
    FUN_00462898();
    sk_pair_t p = FUN_0046589c();
    FUN_001bc440(p.lo, p.hi, l6);
    FUN_000b43e8();
    FUN_0036b118(x19);
    FUN_000b4390();
    FUN_002acbb8();
    FUN_003a25d4(l6);
    FUN_00463878();
    FUN_002acbb8();
    sk_pair_t r = { 0x7b, 0xe100000000000000ull };
    return r;
}

/* FUN_0044b200 @ 0x44b200  (est. sk_emit_group_open_set)
 * Emit the group-open set via sk_format_group_open_set. */
void sk_emit_group_open_set(void)
{
    sk_format_group_open_set();
}

/* FUN_0044b23c @ 0x44b23c  (est. sk_format_named_callout)
 * Format a named Oniguruma callout: emits the
 * s_named_oniguruma_callout_005dd780 label, the callout contents, and
 * any '[' class / sub-callout suffixes. Returns the pair.
 * Confidence: medium
 * Notes: error kind 0xd000000000000018; '[' token 0x5b */
sk_pair_t sk_format_named_callout(void)
{
    word_t uStack_58, x8_ret;
    word_t *x20 = (word_t *)0;
    sk_pair_t r;
    FUN_000b430c();
    FUN_002a4ab4(0x1a);
    FUN_003a25d4(uStack_58);
    FUN_00086840();
    FUN_002acbb8(x20[0], x20[1]);
    if (x20[7] != 0) {
        FUN_00465800(0x5b, x20[6]);
        FUN_002acbb8();
        FUN_004640c4();
        FUN_002acbb8();
        FUN_002acbb8(0xd000000000000018, x8_ret);
        FUN_003a25d4(x8_ret);
    }
    if (x20[0xe] != 0) {
        sk_format_group_open_set();
        FUN_00465294();
        FUN_003a25d4();
    }
    r.lo = 0xd000000000000018;
    r.hi = x8_ret;
    return r;
}

/* FUN_0044b324 @ 0x44b324  (est. sk_emit_named_callout)
 * Emit a named callout via sk_format_named_callout. */
void sk_emit_named_callout(void)
{
    sk_pair_t p = FUN_00464140();
    FUN_00117cc4(p.lo, p.hi, 0x88);
    sk_format_named_callout();
}

/* FUN_0044b478 @ 0x44b478  (est. sk_emit_callout_class)
 * Emit a callout class via sk_callout_format. */
void sk_emit_callout_class(void)
{
    sk_pair_t p = FUN_00464140();
    FUN_00117cc4(p.lo, p.hi, 0x98);
    sk_callout_format(0);
}

/* FUN_0044b4b4 @ 0x44b4b4  (est. sk_emit_end_group_fmt)
 * Emit an end-group format via sk_format_end_group. */
void sk_emit_end_group_fmt(void)
{
    sk_pair_t p = FUN_00463f94();
    FUN_00117cc4(p.lo, p.hi, 0x60);
    sk_format_end_group(0);
}

/* FUN_0044b4ec @ 0x44b4ec  (est. sk_resolve_forward_kind)
 * Resolve a forward/backward assertion kind from the 11-word
 * descriptor at thisp. Maps the kind byte to the label ('capture' /
 * 'balanced capture' / 'nonCaptur' / 'condition' / 'nonAtomic
 * lookbehind' / 'script run' / 'atomic' / 'lookahead'/'lookbehind')
 * and returns it.
 * Confidence: medium
 * Notes: kind strings s_balanced_capture_005dd860,
 * s_changeMatchingOptions<_005dd0c0, s_negativeLookahead_005dd820,
 * s_nonAtomicLookbehind_005dd7c0 */
word_t sk_resolve_forward_kind(word_t *thisp)
{
    word_t x8_ret;
    word_t l1 = thisp[0], l6 = thisp[1], l2 = thisp[2], l7 = thisp[3];
    word_t l3 = thisp[4], l8 = thisp[5], l4 = thisp[6], l9 = thisp[7];
    word_t l5 = thisp[8], l10 = thisp[9];
    switch ((char)thisp[10]) {
    case 1:
        FUN_00466300();
        FUN_00100c04();
        FUN_002a4ab4(0x13);
        FUN_003a25d4(0);
        FUN_00086840();
        return 0xd000000000000011;
    case 2:
        FUN_00466300();
        FUN_00100c04();
        FUN_002a4ab4(0x19);
        FUN_003a25d4(0);
        FUN_00086840();
        return 0xd000000000000016;
    case 3:
        if ((l1==0 && l6==0 && l2==0 && l7==0 && l3==0 && l8==0 && l4==0 && l9==0 && l5==0 && l10==0))
            return 0x65727574706163;                /* 'capture' */
        if (l1 == 1) return 0x75747061436e6f6e;     /* 'nonCaptu' */
        if (l1 == 2) return 0x75747061436e6f6e;
        if (l1 == 3 && l2==0 && l6==0 && l7==0 && l3==0 && l8==0 && l4==0 && l9==0 && l5==0 && l10==0) {
            FUN_004658c0();
            return x8_ret;
        }
        if (l1 == 4) return 0x616568616b6f6f6c;     /* 'lookahea' */
        if (l1 == 5) {
            FUN_004643cc(0, 5, 0xe900000000000064ull);
            FUN_004658c0();
            return x8_ret - 1;
        }
        if (l1 == 6) { FUN_004658c0(); return x8_ret; }
        if (l1 == 7) { FUN_00465d84(); return x8_ret; }
        if (l1 == 8) { FUN_004658c0(); return x8_ret; }
        if (l1 == 9) {
            FUN_004643cc(0, 9, 0xe900000000000064ull);
            FUN_004658c0();
            return x8_ret | 1;
        }
        if (l1 == 10) return 0x7552747069726373;    /* 'scriptRu' */
        return 0x635363696d6f7461;                  /* 'atomicSc' */
    default:
        FUN_00465800(0x3c65727574706163);
        FUN_002acbb8();
        FUN_00463e10();
        FUN_002acbb8();
        return 0;
    }
}

/* FUN_0044b80c @ 0x44b80c  (est. sk_emit_forward_kind)
 * Emit a forward-kind marker via sk_resolve_forward_kind. */
void sk_emit_forward_kind(void)
{
    sk_pair_t p = FUN_00464140();
    FUN_00117cc4(p.lo, p.hi, 0x51);
    sk_resolve_forward_kind(0);
}

/* FUN_0044b844 @ 0x44b844  (est. sk_format_group_suffix)
 * Emit the group suffix: resolve the forward kind, then return the
 * 'group_' token pair. */
sk_pair_t sk_format_group_suffix(void)
{
    sk_resolve_forward_kind(0);
    FUN_00465294();
    FUN_003a25d4();
    sk_pair_t r = { 0x5f70756f7267, 0xe600000000000000ull };
    return r;
}

/* FUN_0044b894 @ 0x44b894  (est. sk_emit_callout_group_suffix)
 * Emit a callout group suffix via sk_format_callout_group. */
void sk_emit_callout_group_suffix(void)
{
    sk_pair_t p = FUN_00463f94();
    FUN_00117cc4(p.lo, p.hi, 0x80);
    sk_format_callout_group(0);
}

/* FUN_0044bcdc @ 0x44bcdc  (est. sk_emit_open_paren)
 * Emit an open-paren format via sk_format_open_paren. */
void sk_emit_open_paren(void)
{
    FUN_004632f4();
    sk_format_open_paren(0, 0, 0, 0, 0, 0);
}

/* FUN_0044bd08 @ 0x44bd08  (est. sk_quantifier_char)
 * Map a quantifier mode byte to the '?' / '+' / '*' marker char.
 * Confidence: high */
byte sk_quantifier_char(char mode)
{
    if (mode == 0) return 0;
    if (mode != 1) return 0x2b;   /* '+' */
    return 0x3f;                  /* '?' */
}

/* FUN_0044bd44 @ 0x44bd44  (est. sk_format_lazy_quant)
 * Format a lazy quantifier: emit the close-paren then the '?'/'+'
 * marker based on the byte at x19+0x50. Returns the pair.
 * Confidence: low
 * Notes: '?' 0x3f / '+' 0x2b */
sk_pair_t sk_format_lazy_quant(void)
{
    word_t local_40[16];
    word_t x19 = 0;
    FUN_004650c8();
    sk_format_close_paren(0, 0, 0, 0, 0, 0);
    FUN_00465944();
    FUN_002acbb8();
    FUN_003a25d4();
    char c = *(char *)(x19 + 0x50);
    byte m = 0x3f;
    if (c != 1) m = 0x2b;
    byte v = 0;
    if (c != 0) v = m;
    word_t t = 0xe000000000000000ull;
    if (c != 0) t = 0xe100000000000000ull;
    FUN_00465c74(v);
    FUN_003a25d4(t);
    return (sk_pair_t){0, 0};
}

/* FUN_0044bdc8 @ 0x44bdc8  (est. sk_format_relative_ref)
 * Format a relative/forward reference: emits the '_' marker and the
 * 'relucnat'/'possessiv'/'ageer' label based on the byte at x19+0x50.
 * Returns the pair.
 * Confidence: low
 * Notes: label words 0x6e617463756c6572 'relucnat' / 0x6973736573736f70 */
sk_pair_t sk_format_relative_ref(void)
{
    word_t local_40[16];
    word_t x19 = 0;
    FUN_004650c8();
    sk_format_open_paren(0, 0, 0, 0, 0, 0);
    FUN_00465944();
    FUN_002acbb8();
    FUN_003a25d4();
    FUN_002acbb8(0x5f, 0xe100000000000000ull);    /* '_' */
    char c = *(char *)(x19 + 0x50);
    word_t tag = 0xe900000000000074;
    word_t lo = 0x6e617463756c6572;
    if (c != 1) { tag = 0xea00000000006576; lo = 0x6973736573736f70; }
    word_t hi = 0x7265676165;
    if (c != 0) hi = lo;
    word_t t = 0xe500000000000000ull;
    if (c != 0) t = tag;
    FUN_00465c74(hi);
    FUN_003a25d4(t);
    return (sk_pair_t){0, 0};
}

/* FUN_0044be8c @ 0x44be8c  (est. sk_emit_callout_value_fmt)
 * Emit a callout value format via sk_format_callout_value. */
void sk_emit_callout_value_fmt(void)
{
    sk_pair_t p = FUN_00464140();
    FUN_00117cc4(p.lo, p.hi, 0x88);
    sk_format_callout_value(0);
}

/* FUN_0044bec4 @ 0x44bec4  (est. sk_format_custom_class)
 * Format a custom character class: emits the
 * s_customCharacterClass_inverted__005dd880 label with the 'false'/
 * 'true' inversion marker and the class descriptor.
 * Confidence: medium
 * Notes: label words 0x65757274 'true' / 0x65736c6166 'false' */
sk_pair_t sk_format_custom_class(void)
{
    word_t auStack_60[8], local_58, local_48;
    word_t x8_ret;
    char *x20 = (char *)0;
    FUN_000b430c();
    FUN_002a4ab4(0x26);
    FUN_003a25d4(local_58);
    FUN_00086840();
    word_t u1 = 0x65757274;
    if (*x20 != 1) u1 = 0x65736c6166;
    word_t u2 = 0xe400000000000000ull;
    if (*x20 != 1) u2 = 0xe500000000000000ull;
    FUN_002acbb8(u1, u2);
    FUN_003a25d4(u2);
    FUN_002acbb8(0x202c, 0xe200000000000000ull);   /* ', ' */
    FUN_00419f24(auStack_60);
    FUN_001a6a8c(local_48, 0x684390);
    FUN_0006b674();
    FUN_004589bc(auStack_60);
    FUN_003507e0();
    FUN_002acbb8();
    FUN_003a25d4(u2);
    FUN_00100e34();
    FUN_002acbb8();
    sk_pair_t r = { 0xd00000000000001f, x8_ret };
    return r;
}

/* FUN_0044bfc0 @ 0x44bfc0  (est. sk_emit_custom_class)
 * Emit a custom class via sk_format_custom_class. */
void sk_emit_custom_class(void)
{
    FUN_00463778();
    sk_format_custom_class();
}

/* FUN_0044bff0 @ 0x44bff0  (est. sk_parse_forward_assert)
 * Parse a forward/backward assertion node. Dispatches on the node
 * kind (FUN_00458d04): default and kinds 1-5 emit the assertion label
 * or fold a nested group; kind 5 additionally appends the 0x178-byte
 * sub-elements into the vector. SoftwareBreakpoint(1,0x44c3b0/.b4)
 * guards the element bounds.
 * Confidence: low
 * Notes: kind 5 element stride 0x178; ' pop' token 0x20706f */
void sk_parse_forward_assert(void)
{
    word_t x8_ret, x9_ret;
    word_t auStack_520[47], auStack_3a8[47], auStack_170[22];
    word_t local_230, lStack_228, local_220, lStack_218, local_210, lStack_208;
    word_t local_b0, uStack_a8;
    sk_pair_t uvar5 = FUN_0008e518();
    FUN_00117cc4((word_t)auStack_3a8, 0, 0);
    word_t u4 = FUN_00458d04(auStack_3a8);
    word_t *pl = (word_t *)FUN_00458d10(auStack_3a8);
    sk_pair_t result = { 0, 0xe000000000000000ull };
    switch (u4) {
    default:
        lStack_228 = pl[1]; local_230 = pl[0];
        lStack_218 = pl[3]; local_220 = pl[2];
        lStack_208 = pl[5]; local_210 = pl[4];
        result = sk_format_custom_class();
        break;
    case 1:
        FUN_00117cc4((word_t)&local_230, (word_t)pl, 0x178);
        FUN_00117cc4((word_t)&local_b0, (word_t)pl, 0xb0);
        result = FUN_00413b68();
        FUN_00463de0();
        FUN_002acbb8();
        FUN_00117cc4((word_t)auStack_520, (word_t)auStack_170, 0xb0);
        FUN_00413b68();
        FUN_000e72d4();
        FUN_003a25d4((word_t)pl);
        break;
    case 2:
        FUN_00117cc4((word_t)&local_230, (word_t)pl, 0xb0);
        result = FUN_00413b68();
        break;
    case 3:
        FUN_004657b8(pl[0], pl[1]);
        local_230 = x8_ret;
        lStack_228 = x9_ret;
        FUN_002acbb8();
        FUN_004657ac();
        FUN_002acbb8();
        result.lo = local_230; result.hi = lStack_228;
        break;
    case 4:
        break;
    case 5:
        {
            word_t l11 = pl[0];
            word_t l1 = pl[1];
            word_t l10 = pl[4];
            local_b0 = 0;
            uStack_a8 = 0xe000000000000000ull;
            FUN_002acbb8(0x20706f, 0xe300000000000000ull);   /* ' pop' */
            word_t i = 0;
            word_t n = *(word_t *)(l11 + 0x10);
            FUN_000a6fe0();
            while (n != i) {
                byte eq = i == n;
                if (n <= i) CL4_FATAL();            /* 0x44c3b0 */
                FUN_004654a8(&local_230);
                FUN_004652ac(&local_230);
                if (eq) { i++; continue; }
                FUN_00458d30(&local_230, auStack_520);
                word_t c = pl[2];
                if ((FUN_003a261c((word_t)pl) & 1) == 0) {
                    FUN_000dbbe0(0, c + 1);
                    FUN_00456238();
                }
                if ((word_t)pl[3] >> 1 <= c) {
                    FUN_00456238(1 < (word_t)pl[3], c + 1, 1);
                }
                i++;
                pl[2] = c + 1;
                FUN_00117cc4((word_t)pl + c * 0x2f * 8 + 4 * 8, (word_t)&local_230, 0x178);
            }
            FUN_001a6a8c((word_t)pl, 0x684390);
            FUN_000b43e8();
            FUN_0036b118((word_t)pl);
            FUN_000b4390();
            FUN_002acbb8();
            FUN_003a25d4(n);
            FUN_00463fe8();
            result = FUN_002acbb8();
            local_230 = (word_t)l1;
            FUN_00463df8(result.lo, result.hi, 0x6844a8);
            FUN_00462728();
            FUN_00205844(&local_230, &local_b0);
            FUN_00463fe8();
            FUN_002acbb8();
            i = 0;
            n = *(word_t *)(l10 + 0x10);
            FUN_000a6fe0();
            while (n != i) {
                byte eq = i == n;
                if (n <= i) CL4_FATAL();            /* 0x44c3b4 */
                FUN_004654a8(&local_230);
                FUN_004652ac(&local_230);
                if (eq) { i++; continue; }
                FUN_00458d30(&local_230, auStack_520);
                word_t c = pl[2];
                if ((FUN_003a261c((word_t)pl) & 1) == 0) {
                    FUN_000dbbe0(0, c + 1);
                    FUN_00456238();
                }
                if ((word_t)pl[3] >> 1 <= c) {
                    FUN_00465f14(1 < (word_t)pl[3]);
                    FUN_00456238();
                }
                i++;
                pl[2] = c + 1;
                FUN_00117cc4((word_t)pl + c * 0x2f * 8 + 4 * 8, (word_t)&local_230, 0x178);
            }
            FUN_001a6a8c((word_t)pl, 0x684390);
            FUN_000b43e8();
            FUN_0036b118((word_t)pl);
            FUN_000b4390();
            FUN_002acbb8();
            FUN_003a25d4(n);
            result.lo = local_b0; result.hi = uStack_a8;
            break;
        }
    }
    FUN_0008e500(result.lo, result.hi, uvar5.lo);
}
