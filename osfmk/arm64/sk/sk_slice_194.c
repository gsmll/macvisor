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

/* Shared globals referenced by this slice (decompiler _DAT symbols). */
extern word_t _DAT_005a18a0, _DAT_005a18a8, _DAT_005a1870, _DAT_005a1878;
extern word_t _DAT_005a1890, _DAT_005a1898, _DAT_004c2450, _DAT_004c2458;
extern word_t _DAT_00594e41, _DAT_004c554e, _DAT_00504355, _DAT_005a35c0, _DAT_005a35f8;
extern word_t _DAT_005a1880, _DAT_005a1888;

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
extern void   FUN_004578dc(word_t, word_t);    /* vector grow+cb */
extern void   FUN_003505e8(void);              /* vector step */
extern void   FUN_003511cc(void);              /* vector step */
extern void   FUN_00457994(word_t, ...);       /* vector settle */
extern void   FUN_0046418c(void);              /* vec store */
extern void   FUN_00465160(word_t);             /* vec store */
extern void   FUN_003508fc(void);              /* parse apply */
extern void   FUN_0042fe0c(void);              /* parse helper */
extern void   FUN_00352840(word_t);            /* parse helper */
extern void   FUN_002a3e64(void);              /* scan helper */
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
extern void   FUN_0046589c(void);              /* trace */
extern void   FUN_00464d74(word_t);            /* vec count bump */
extern word_t FUN_00462ba8();   /* was word_t(void) */
extern void   FUN_00350878(word_t);            /* settle */
extern void   FUN_00464ae8(word_t);            /* frame leave */
extern void   FUN_00463648(void);              /* record enter */
extern sk_pair_t FUN_00463444(word_t *);       /* record pair */
extern void   FUN_0042f584(word_t, word_t, word_t, word_t); /* state push */
extern void   FUN_00351b38(word_t);            /* parse token */
extern void   FUN_000abad0(void);              /* parse helper */
extern void   FUN_00350b3c(void);              /* parse advance */
extern sk_pair_t FUN_00350af4(void);           /* pair advance */
extern void   FUN_00462a5c(void);              /* token consume */
extern void   FUN_004655a8(void);              /* frame helper */
extern void   FUN_00463014(word_t);            /* unknown-group printf */
extern void   FUN_00463290(void);              /* obj probe */
extern void   FUN_00461cb8(word_t *);          /* obj store */
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
extern void   FUN_00463f74(void);              /* elem guard */
extern void   FUN_00462b2c(void);              /* elem guard */
extern void   FUN_00463f74(void);              /* elem guard */
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
extern void     FUN_00350a04(void);            /* parse enter */
extern void     FUN_00464b20(word_t *);        /* frame init */
extern void     FUN_00462710(word_t);          /* buf discard */
extern void     FUN_0006b3f4(void);            /* vec state op */
extern void     FUN_0008e500(void);            /* exit */
extern void     FUN_0008e518(void);            /* entry */
extern word_t FUN_0015e4f8();   /* was word_t() */
extern sk_pair_t FUN_004339a8(void);           /* state build pair */
extern void   FUN_000dbed0(void);              /* vec grow */

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
extern word_t FUN_00084220();   /* was word_t() */
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
extern word_t FUN_001bc440();   /* was word_t() */
extern word_t FUN_001ee018();   /* was word_t() */
extern word_t FUN_00205844();   /* was word_t() */
extern word_t FUN_002298d4();   /* was word_t() */
extern word_t FUN_0022d2f4();   /* was word_t() */
extern word_t FUN_0024917c();   /* was word_t() */
extern word_t FUN_0024d9ac();   /* was word_t() */
extern word_t FUN_002a4ab4();   /* was word_t() */
extern word_t FUN_002aca00();   /* was word_t() */
extern word_t FUN_002acbb8();   /* was word_t() */
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
extern word_t FUN_00351714();   /* was word_t() */
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
extern word_t FUN_0036993c();   /* was word_t() */
extern word_t FUN_0036b340();   /* was word_t() */
extern word_t FUN_00377824();   /* was word_t() */
extern word_t FUN_00377bec();   /* was word_t() */
extern word_t FUN_003a25e0();   /* was word_t() */
extern word_t FUN_003f8224();   /* was word_t() */
extern word_t FUN_004080b0();   /* was word_t() */
extern word_t FUN_0040feac();   /* was word_t() */
extern word_t FUN_0040ff40();   /* was word_t() */
extern word_t FUN_004107e4();   /* was word_t() */
extern word_t FUN_004108a0();   /* was word_t() */
extern word_t FUN_00411a54();   /* was word_t() */
extern word_t FUN_00411bbc();   /* was word_t() */
extern word_t FUN_00411bfc();   /* was word_t() */
extern word_t FUN_00411c8c();   /* was word_t() */
extern word_t FUN_00411cc4();   /* was word_t() */
extern word_t FUN_00412694();   /* was word_t() */
extern word_t FUN_00412d5c();   /* was word_t() */
extern word_t FUN_00413b68();   /* was word_t() */
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
extern word_t FUN_0042c060();   /* was word_t() */
extern word_t FUN_0042c11c();   /* was word_t() */
extern word_t FUN_0042c5a4();   /* was word_t() */
extern word_t FUN_0042dc90();   /* was word_t() */
extern word_t FUN_0042e930();   /* was word_t() */
extern word_t FUN_0042ed6c();   /* was word_t() */
extern word_t FUN_0042f020();   /* was word_t() */
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
extern word_t FUN_00434054();   /* was word_t() */
extern word_t FUN_004340b0();   /* was word_t() */
extern word_t FUN_004345a4();   /* was word_t() */
extern word_t FUN_00434af4();   /* was word_t() */
extern word_t FUN_00435110();   /* was word_t() */
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
extern word_t FUN_004458b0();   /* was word_t() */
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
extern word_t FUN_0044bdc8();   /* was word_t() */
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
extern word_t FUN_0044c918();   /* was word_t() */
extern word_t FUN_0044c9c4();   /* was word_t() */
extern word_t FUN_0044ca08();   /* was word_t() */
extern word_t FUN_0044ca2c();   /* was word_t() */
extern word_t FUN_0044e55c();   /* was word_t() */
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
extern word_t FUN_00462a1c();   /* was word_t() */
extern word_t FUN_00462a34();   /* was word_t() */
extern word_t FUN_00462a84();   /* was word_t() */
extern word_t FUN_00462a98();   /* was word_t() */
extern word_t FUN_00462abc();   /* was word_t() */
extern word_t FUN_00462b40();   /* was word_t() */
extern word_t FUN_00462b6c();   /* was word_t() */
extern word_t FUN_00462c04();   /* was word_t() */
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
extern word_t FUN_00463194();   /* was word_t() */
extern word_t FUN_004631a8();   /* was word_t() */
extern word_t FUN_004631fc();   /* was word_t() */
extern word_t FUN_00463210();   /* was word_t() */
extern word_t FUN_00463268();   /* was word_t() */
extern word_t FUN_004632a4();   /* was word_t() */
extern word_t FUN_004632e0();   /* was word_t() */
extern word_t FUN_004632f4();   /* was word_t() */
extern word_t FUN_004633e0();   /* was word_t() */
extern word_t FUN_004634d4();   /* was word_t() */
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
extern word_t FUN_00463890();   /* was word_t() */
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
extern word_t FUN_00463e04();   /* was word_t() */
extern word_t FUN_00463f64();   /* was word_t() */
extern word_t FUN_00463f94();   /* was word_t() */
extern word_t FUN_00463fb8();   /* was word_t() */
extern word_t FUN_00463fd0();   /* was word_t() */
extern word_t FUN_00463fe8();   /* was word_t() */
extern word_t FUN_0046400c();   /* was word_t() */
extern word_t FUN_00464040();   /* was word_t() */
extern word_t FUN_004640a4();   /* was word_t() */
extern word_t FUN_004640f0();   /* was word_t() */
extern word_t FUN_00464134();   /* was word_t() */
extern word_t FUN_00464140();   /* was word_t() */
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
extern word_t FUN_00465788();   /* was word_t() */
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
extern word_t FUN_00462d88();   /* was word_t() */
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
extern void   FUN_000dbed0();
extern word_t FUN_0015e4f8();   /* was word_t() */
extern void   FUN_002a3e64();
extern void   FUN_003504ac();
extern void   FUN_00350518();
extern void   FUN_003505e8();
extern void   FUN_00350878();
extern void   FUN_003508fc();
extern void   FUN_00350a04();
extern void   FUN_00350b3c();
extern void   FUN_00350bfc();
extern void   FUN_003510b8();
extern void   FUN_003511a8();
extern void   FUN_003511cc();
extern void   FUN_003512c0();
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
extern void   FUN_0042f584();
extern void   FUN_0042fc4c();
extern void   FUN_0042fd4c();
extern void   FUN_0042fe0c();
extern void   FUN_0042ffec();
extern void   FUN_00430040();
extern void   FUN_00430d08();
extern void   FUN_00435ecc();
extern void   FUN_004368c0();
extern void   FUN_00437eec();
extern void   FUN_00455db8();
extern void   FUN_004578dc();
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
extern void   FUN_00461cb8();
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
extern void   FUN_00462b00();
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
extern void   FUN_00463014();
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
extern void   FUN_00463f74();
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
extern void   FUN_0046589c();
extern void   FUN_004659bc();
extern void   FUN_00465d48();
extern void   FUN_00465da4();
extern void   FUN_00465ddc();

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
