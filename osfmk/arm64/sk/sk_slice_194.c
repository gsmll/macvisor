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
extern void   sk_commit2(void);                /* FUN_00463bc8 */
extern word_t sk_acquire2(void);               /* FUN_0042f670 state (bit0) */
extern void   sk_advance_to(word_t, word_t);   /* FUN_00462b80 advance-to-delim */
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

/* Shared in-slice mutators (defined below / cross-referenced). */
extern void   sk_parse_begin(void);            /* FUN_00462d0c */
extern void   sk_parse_commit(void);           /* FUN_00463bc8 */
extern word_t sk_acquire_state(word_t, word_t);/* FUN_0042f670 (bit0) */
extern word_t sk_acquire_probe(word_t);        /* FUN_0042ec68 */
extern void   sk_parse_helper(void);           /* FUN_0042fd4c */
extern uint   sk_delim_probe(word_t *);        /* FUN_0043a300 (in-slice) */

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
uint sk_delim_probe(sk_parser_t *p, word_t *desc)
{
    word_t token = desc[1];
    sk_pair_t pr = sk_pair_fn(desc[2], desc[3], desc[0], token);
    uint r = 1;
    if ((pr.lo ^ pr.hi) >= 0x4000) {
        sk_parse_begin();          /* FUN_00462788 */
        sk_token_acquire();        /* FUN_002b439c */
        sk_parse_pair_apply();     /* FUN_00351e08 */
        sk_token_release(token);
        /* current char/tag against '=' */
        if (!(p->cur == '=' && p->tag == SK_TAG_DELIM)) {
            sk_advance_to(p, '='); /* FUN_00462b80 */
            if (!(sk_state_ok(p) & 1) &&
                !(p->cur == ':' && p->tag == SK_TAG_DELIM)) {
                sk_advance_to(p, ':');   /* FUN_00462b80 */
                if (!(sk_state_ok(p) & 1) &&
                    !(p->cur == '[' && p->tag == SK_TAG_DELIM)) {
                    sk_advance_to(p, '[');
                    if (!(sk_state_ok(p) & 1) &&
                        !(p->cur == ']' && p->tag == SK_TAG_DELIM)) {
                        sk_advance_to(p, ']');
                        if (!(sk_state_ok(p) & 1) &&
                            !(p->cur == '}' && p->tag == SK_TAG_DELIM)) {
                            sk_advance_to(p, '}');
                            if (!(sk_state_ok(p) & 1) &&
                                !(p->cur == '\\' && p->tag == SK_TAG_DELIM)) {
                                sk_advance_to(p, '\\');
                                r = sk_state_ok(p) & 1;
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
            base = FUN_004663ac();
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
            base = FUN_004663ac();
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
    *(byte *)(out + 4) = flag;
}


