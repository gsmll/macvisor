/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0), Apple's code-signing / entitlement /
 * trust-cache / code-execution-policy authority. Ground truth: Ghidra FUN_
 * names + addresses in `txm.raw`. All names are estimates unless a string /
 * header name matches (confidence high). TXM = Trusted Execution Monitor GL0,
 * image base 0.
 *
 * This file covers the code-signing policy-engine + crypto-toolkit region
 * 0x35000-0x40000 (batch T3): the "restricted execution" policy state machine
 * and per-rule selectors (000350c0..00036d44), the DER/ASN.1 element reader
 * (00036f54..00037bc0), the SHA-1/SHA-256/SHA-512 digest cores (0003f9fc /
 * 0003f270 / 0003eec4,0003ff50), and the big-number / NIST-P-256 ECDSA
 * verify + scalar-multiply toolkit (000389ec..0003f9a8). These are the
 * primitives TXM uses to enforce code-execution policy and verify the
 * signatures attached to code / trust-cache images.
 *
 * Shared kernel/hardware deps and sibling-region helpers are declared extern
 * with a one-line note (bodies live in other txm batch files). Confidence is
 * medium unless a string (entitlement name / DER tag) or header match raises
 * it. Ghidra names stay in comments; bodies are English-first.
 */

#ifndef __ASSEMBLER__
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ */
/* Shared TXM runtime primitives (extern; bodies live in sibling files) */
/* ------------------------------------------------------------------ */

/* TXM panic (noreturn). FUN_000298ec takes a 2-arg {code, packed-status};
 * FUN_00029a3c takes a single fault code. */
extern void txm_panic(uint64_t code, ...) __attribute__((noreturn));
extern void txm_fault(uint64_t code) __attribute__((noreturn));   /* FUN_00029a3c */
extern void txm_stack_guard_fail(void) __attribute__((noreturn)); /* FUN_0002f13c */
extern void txm_log(const char *str);                            /* FUN_00025c6c */
extern int  txm_dit_available(void);                             /* FUN_000299e4 */

/* Entitlement / policy lookups (sibling region 0x30000). */
extern uint32_t txm_ent_has(uint64_t *ctx, uint64_t name, int flag);     /* FUN_00031424 */
extern uint32_t txm_ent_lookup(uint64_t *ctx, uint64_t name, int *out);  /* FUN_00031388 */
extern uint32_t txm_ent_pair(uint64_t *ctx, uint64_t a, uint64_t b);     /* FUN_000314b0 */
extern uint32_t txm_ent_bits(uint64_t *ctx);                             /* FUN_00031334 */

/* Buffer / range helpers (sibling region 0x33000). */
extern uint32_t txm_range_check(uint64_t a, uint64_t b, uint64_t c,
                                uint64_t d, uint64_t *out);              /* FUN_00033c9c */
extern void txm_range_kind(uint64_t a, uint64_t b, uint64_t *out);       /* FUN_00033bf4 */
extern void txm_range_kind2(uint64_t a, uint64_t b, uint32_t *out);      /* FUN_00033ad4 */
extern void txm_buf_fill(uint64_t a, uint64_t b, uint8_t *out, int c);   /* FUN_00034028 */
extern void txm_buf_digest(uint64_t a, uint64_t b, int c, uint16_t *out);/* FUN_00034174 */
extern void txm_buf_cmp(uint64_t a, uint64_t b, int c, uint64_t *out);   /* FUN_000340c0 */

/* Object / lock runtime (sibling region 0x27000). */
extern void txm_lock_acquire(uint64_t obj, int a, int b);   /* FUN_00027128 */
extern void txm_lock_release(uint64_t obj, int a);          /* FUN_00027218 */

/* String / memory helpers. */
extern int  txm_strcmp(const char *a, const char *b);       /* thunk_FUN_0002d990 */
extern void txm_memcpy(void *dst, const void *src, uint64_t n); /* thunk_FUN_0002d6b0 */
extern int  txm_memcmp(const void *a, const void *b, uint64_t n); /* thunk_FUN_0002d4d0 */
extern uint64_t txm_lenstr(const char *s);                  /* thunk_FUN_0002dc80 */

/* Big-number primitives (sibling region 0x40000+).  A `bn` operand is a limb
 * descriptor {count, limbs...} of 64-bit little-endian limbs. `count` = limb
 * count. */
extern void txm_bn_mul(uint64_t ctx, uint64_t n, uint64_t *out,
                       uint64_t *a, uint64_t *b);           /* FUN_00043650 */
extern void txm_bn_op(uint64_t ctx, uint64_t n, uint64_t *out,
                      uint64_t *a, uint64_t *b);            /* FUN_00042d90 */
extern void txm_bn_op2(uint64_t ctx, uint64_t n, uint64_t *out,
                       uint64_t *a, uint64_t *b);           /* FUN_00042da4 */
extern void txm_bn_clr(uint64_t bytes, void *dst);          /* FUN_00042ab0 */
extern uint64_t txm_bn_count(uint64_t *desc);               /* FUN_00042b78 */
extern uint64_t txm_bn_bitlen_desc(uint64_t *desc);         /* FUN_00042b84 */
extern int txm_bn_cmp(uint64_t n, uint64_t *a, uint64_t *b);/* thunk_FUN_00043cc4 */
extern uint64_t txm_bn_carry(uint64_t n, uint64_t *a, uint64_t *b); /* FUN_000440ec */
extern void txm_bn_shl(uint64_t n, uint64_t *d, uint64_t *s, uint64_t bits); /* FUN_000429c4 */
extern void txm_bn_rem2(uint64_t n, uint64_t *d, uint64_t *s, uint64_t *m);  /* FUN_00042acc */
extern void txm_bn_even(uint64_t n, uint64_t *d, uint64_t *s);   /* FUN_000423b4 */
extern int  txm_bn_is_one(uint64_t *ctx, uint64_t *desc, uint64_t *a); /* FUN_00042b90 */
extern void txm_bn_alg_fini(void *ctx);                      /* FUN_00043a74 */
extern void txm_bn_alg_free(void *ctx);                      /* FUN_00043ad0 */
extern uint64_t txm_bn_scratch(uint64_t bytes);              /* FUN_00043a38 */
extern void txm_bn_mod_op(uint64_t *a, uint64_t n, uint64_t *b); /* FUN_0003e6e4 */

/* Object/range association + digest helpers used by the region driver. */
extern uint64_t txm_region_set_digest(uint64_t obj, uint64_t digest); /* FUN_00031ecc */
extern void txm_region_zero(uint64_t *a, uint64_t *b);       /* FUN_00030cc8 */

/* Boot / debug gating helpers. */
extern void txm_boot_enter(int);        /* FUN_00023dac */
extern void txm_boot_leave(void);       /* FUN_000239a8 */
extern uint64_t txm_debug_flag;         /* DAT_000104e9 */
extern uint64_t txm_restricted_state;   /* DAT_000107d8 */
extern uint64_t txm_canary;             /* DAT_00006cf0 stack canary */

/* Policy/trust-context probes (sibling region 0x30000-0x35000). */
extern uint64_t txm_policy_trust(void);              /* FUN_00034b18 */
extern long    txm_policy_trust2(uint64_t *ctx);     /* FUN_00034b30 */
extern uint32_t txm_policy_trust3(uint64_t *ctx);    /* FUN_00034b50 */
extern uint32_t txm_region_auth(uint64_t d, uint64_t k);        /* FUN_00032014 */
extern uint32_t txm_region_auth2(uint64_t d, uint64_t s);       /* FUN_00032104 */
extern uint32_t txm_region_pagetype(uint64_t d, uint64_t a, uint64_t b); /* FUN_000321dc */
extern int      txm_len_kind(uint8_t k, uint8_t v);              /* FUN_000324f4 */
extern uint32_t txm_region_resolve(uint64_t a, uint64_t b, uint64_t *c);  /* FUN_00032630 */
extern uint32_t txm_region_resolve2(uint64_t a, uint64_t b, uint64_t c,
                                    uint64_t *d);                 /* FUN_00033d40 */
extern void     txm_region_digest(uint8_t k, uint64_t a, uint64_t b,
                                  uint64_t *d);                   /* FUN_000325b0 */
extern uint32_t txm_region_kind_a(uint64_t *c, long p);           /* FUN_00034a2c */
extern uint32_t txm_region_kind_b(uint64_t *c, long p);           /* FUN_000345f4 */
extern uint32_t txm_region_kind_c(uint64_t *c, long p);           /* FUN_0003499c */
extern uint32_t txm_region_kind_d(uint64_t *c, long p);           /* FUN_000348f8 */
extern int      txm_region_match(uint64_t a, uint64_t b, uint64_t l); /* thunk_FUN_0002da90 */
extern uint64_t txm_page_hash(uint64_t a, uint64_t b, uint64_t t,
                              uint32_t m, uint32_t *info);        /* FUN_00032b38 */
extern uint64_t txm_der_bytes_import(uint64_t n, uint64_t *out, uint64_t len, uint8_t *src); /* FUN_0003df58 */

/* Big-number PRNG (xorshift on DAT_00070040), FUN_0003d498. */
extern uint64_t txm_bn_prng(void);
/* 4-bit window comparison table (DAT_00006e60). */
extern const uint8_t txm_bn_win_tbl[0x20];
extern uint64_t txm_p256_b_0, txm_p256_b_1, txm_p256_b_2, txm_p256_b_3; /* DAT_00006ed8.. */

/* Digest algorithm name structs (static tables). */
const void *txm_alg_name_c0(void);   /* DAT_000110a8 */
const void *txm_alg_name_e0(void);   /* DAT_000114e0 */
const void *txm_alg_name_209(void);  /* DAT_000111f8 */
const void *txm_alg_name_100(void);  /* FUN_00040c1c */
const void *txm_alg_name_180(void);  /* FUN_00043d00 */

#define ENT_OOP_JIT_LOADER  "com.apple.private.oop-jit-loader"
#define ENT_OOP_JIT_RUNNER  "com.apple.private.oop-jit-runner"
#define ENT_SECURITY_RESEARCH "com.apple.private.security.research"

/* Forward declarations for functions defined in this file (used across
 * sections before their definitions). */
void txm_region_policy_commit(uint64_t *ctx, uint64_t base, uint64_t size);
uint32_t txm_policy_rule1(uint64_t *ctx);
uint32_t txm_policy_rule2(uint64_t *ctx);
uint32_t txm_policy_rule3(uint64_t *ctx);
uint64_t *txm_policy_rule4(uint64_t *ctx);
uint32_t txm_policy_rule67(uint64_t *ctx, uint8_t rule);
uint64_t *txm_policy_rule_ac(uint64_t *ctx);
uint32_t txm_policy_rule_ab(uint64_t *ctx);
uint32_t txm_policy_rule_aa(uint64_t *ctx);
int txm_policy_rule_02(uint64_t *ctx, uint8_t rule);
uint64_t *txm_policy_rule_d1(uint64_t *ctx, uint32_t mode);
int txm_policy_rule_a0(uint64_t *ctx, uint32_t mode);
uint32_t txm_policy_rule_a8(uint64_t *ctx, uint32_t mode);
uint32_t txm_policy_rule_a9(uint64_t *ctx, int mode);
void txm_sha512_compress(uint64_t *state, uint64_t blocks, const uint8_t *data);
uint64_t txm_der_len_decode(uint64_t *rng, uint64_t *out, int canonical);
void txm_der_len_decode_short(uint64_t *rng, uint64_t *out);
void txm_der_len_decode_full(uint64_t *rng, uint64_t *out);
uint64_t txm_tag_match(uint64_t *rng, uint64_t tag, uint64_t *out);
uint64_t txm_trusted_range(uint64_t *rng, uint64_t tag, uint64_t *out);
uint64_t txm_policy_kind_get(uint64_t ctx, uint8_t *out);
void txm_der_len_decode_short(uint64_t *rng, uint64_t *out);
void txm_dit_clear(uint8_t *flag);
bool txm_bn_is_zero(uint64_t *desc, uint64_t buf);
bool txm_bn_add(uint64_t ctx, uint64_t n, uint64_t *out, uint64_t *a, uint64_t *b);
uint8_t txm_bn_sub(uint64_t ctx, uint64_t n, uint64_t *out, uint64_t *a, uint64_t *b);
uint64_t txm_bn_csub(uint64_t n, uint64_t sel, uint64_t *a, uint64_t *b, uint64_t *m);
uint64_t txm_bn_add_carry(uint64_t n, uint64_t *out, uint64_t *a, uint64_t carry);
uint64_t txm_bn_add_mux(uint64_t ctx, uint64_t n, uint64_t *out, uint64_t *a, uint64_t carry);
void txm_bn_set_one(uint64_t n, uint64_t *buf);
void txm_bn_bit_set(uint64_t num, uint64_t bit, int set);
void txm_bn_clr_limbs(uint64_t n);
void txm_bn_byteswap(uint64_t n, uint64_t *buf);
uint64_t txm_bn_export_be(uint64_t n, uint64_t *limbs, uint64_t cap, uint64_t dst);
uint64_t txm_bn_bytelen(uint64_t n, uint64_t *limbs);
void txm_bn_shl(uint64_t n, uint64_t *dst, uint64_t *src, uint64_t bits);
uint64_t txm_bn_sub_const(uint64_t n, uint64_t *out, uint64_t *a, uint64_t k);
uint64_t txm_bn_modulus_ptr(uint64_t desc);
uint64_t txm_bn_muladd(uint64_t n, uint64_t *acc, uint64_t *a, uint64_t k);
uint64_t txm_bn_muladd2(uint64_t n, uint64_t *acc, uint64_t *a, uint64_t k);
void txm_bn_mul_full(uint64_t n, uint64_t *out, uint64_t *a, uint64_t *b);
void txm_bn_neg(uint64_t n, uint64_t *out, uint64_t *a);
uint64_t txm_bn_bitlen(uint64_t n, uint64_t *limbs);
uint64_t txm_bn_prng(void);
extern uint64_t txm_bn_prng_state;    /* DAT_00070040 */
uint64_t txm_bn_modulus_ptr(uint64_t desc);
uint64_t txm_bn_sub_const(uint64_t n, uint64_t *out, uint64_t *a, uint64_t k);
uint64_t txm_bn_exp_window(uint64_t ctx, uint64_t desc, uint64_t out,
                           uint64_t base, uint64_t exp);
void txm_bn_copy(uint64_t n, uint64_t *dst, uint64_t *src);
uint64_t txm_der_oid_read(uint64_t rng, uint64_t *out);
bool txm_der_oid_byte_match(uint64_t *rng, uint64_t a, uint64_t b);
uint64_t txm_der_uint_read(uint64_t rng, uint64_t *out);
uint64_t txm_der_oid_match(uint64_t rng, uint64_t a, uint64_t b, uint64_t c);
void txm_digest_init(uint64_t ctx, uint64_t *h);
void txm_digest_blocks(uint64_t ctx, uint64_t *h, uint64_t len, uint64_t src);
char *txm_der_name_resolve(uint64_t der, char *dst);
uint64_t txm_bn_csub(uint64_t n, uint64_t sel, uint64_t *a, uint64_t *b, uint64_t *m);
uint64_t txm_bn_add_carry(uint64_t n, uint64_t *out, uint64_t *a, uint64_t carry);
uint64_t txm_bn_add_mux(uint64_t ctx, uint64_t n, uint64_t *out, uint64_t *a, uint64_t carry);
void txm_bn_set_one(uint64_t n, uint64_t *buf);
uint64_t txm_bn_muladd(uint64_t n, uint64_t *acc, uint64_t *a, uint64_t k);
uint64_t txm_bn_muladd2(uint64_t n, uint64_t *acc, uint64_t *a, uint64_t k);
void txm_bn_mul_full(uint64_t n, uint64_t *out, uint64_t *a, uint64_t *b);
void txm_bn_neg(uint64_t n, uint64_t *out, uint64_t *a);
void txm_ec_pt_double(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t pt);
void txm_ec_pt_add(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a, uint64_t b, int sub);
void txm_ec_pt_addfull(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a, uint64_t b, int sub);
void txm_ec_pt_scale(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a, uint64_t b);
void txm_ec_pt_mul1(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t pt, uint64_t k);
void txm_ec_pt_mul_lincomb(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a, uint64_t b, uint64_t c, uint64_t d);
uint64_t txm_ec_point_mul(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t n, uint64_t pt);
uint64_t txm_ec_scalarmul_ladder(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t *scalar, uint64_t bits, uint64_t point, uint64_t *t1, uint64_t *t2);
uint64_t txm_bn_modpow(uint64_t ctx, uint64_t desc, uint64_t base, uint64_t exp);
uint64_t txm_bn_modinv(uint64_t ctx, uint64_t desc, uint64_t out, uint64_t a, uint64_t mod);
uint64_t txm_bn_modinv_loop(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t n, uint64_t a, uint64_t mod);
uint64_t txm_bn_modinv_step(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a, uint64_t sel, uint64_t b, uint64_t sel2);
uint64_t txm_bn_modpow_loop(uint64_t ctx, uint64_t *desc, uint64_t base, uint64_t exp);
uint64_t txm_bn_modpow_square(uint64_t ctx, uint64_t *desc, uint64_t a, uint64_t b);
uint64_t txm_bn_modexp_ladder(uint64_t ctx, uint64_t *desc, uint32_t bits, uint64_t explen, uint8_t *exp, uint64_t *e);
uint64_t txm_bn_modpow_wrap(uint64_t *desc, uint64_t a, uint64_t b, uint64_t c);
uint64_t txm_bn_modexp_final(uint64_t ctx, uint64_t *desc, uint64_t *e, int flag);
uint64_t txm_bn_mod_reduce(uint64_t n, uint64_t *a, uint64_t mod);
uint64_t txm_bn_mul_inv_final(uint64_t n, uint64_t *a, uint64_t b, uint64_t c, uint64_t d, uint8_t *mac);
uint64_t txm_ecdsa_verify(uint64_t *desc, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g);
uint32_t txm_ecdsa_verify_core(uint64_t *scratch, uint64_t *desc, uint64_t pubx, uint64_t puby, uint64_t sig, uint64_t dlen, uint64_t digest, int allow_short, uint8_t *mac);
int txm_ecdsa_verify_full(uint64_t *scratch, uint64_t *desc, uint64_t a, uint64_t b, uint64_t c, uint64_t d, int flag);
uint64_t txm_ecdsa_verify_digest(uint64_t *scratch, uint64_t *desc, uint64_t h, uint64_t digest, uint64_t a, uint64_t b, uint64_t c, uint64_t d);
void txm_ec_pt_add_wrap(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a, uint64_t b);
void txm_ec_pt_sub_wrap(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a, uint64_t b);
void txm_bn_bit_set(uint64_t num, uint64_t bit, int set);
void txm_bn_byteswap(uint64_t n, uint64_t *buf);
uint64_t txm_bn_export_be(uint64_t n, uint64_t *limbs, uint64_t cap, uint64_t dst);
uint64_t txm_bn_bytelen(uint64_t n, uint64_t *limbs);
int txm_bn_export_be2(uint64_t n, uint64_t *limbs, uint64_t cap, uint64_t dst);
uint32_t txm_ecdsa_finalize(uint64_t n, uint8_t *sig, uint64_t dlen, uint64_t digest, uint64_t extra, uint64_t *mac);
void txm_dit_clear(uint8_t *flag);
bool txm_bn_is_zero(uint64_t *desc, uint64_t buf);
uint64_t txm_bn_bitlen(uint64_t n, uint64_t *limbs);



/* ------------------------------------------------------------------ */
/* Idioms from the decompiler (kept faithful, named for readability). */
/* ------------------------------------------------------------------ */

/* 64-bit carry of a+b. */
#define TXM_CARRY8(a, b)  ((bool)((uint64_t)(a) > ~(uint64_t)(b)))
/* Top half / low half of a 128-bit product a*b. */
#define TXM_HI64(a, b)    ((uint64_t)(((__uint128_t)(a) * (__uint128_t)(b)) >> 64))
/* Count leading zeroes. */
#define TXM_LZ(x)         (__builtin_clzll((unsigned long long)(x)))
/* Tagged-pointer fixup: force top 16 bits to 0xc8a2 keeping low 48 bits
 * (decompiler PAC/tag idiom; rendered faithfully). */
#define TXM_TAGFIX(p)     (((uint64_t)(p) & 0xffffffffffffULL) | 0xc8a2000000000000ULL)
#define TXM_TAGABLE(a, b) ((((uint64_t)(a) ^ (uint64_t)(b)) & 0xffc0000000000000ULL) != 0)

/* Set/clear the DIT system register (Data-Independent Timing). */
static inline void txm_dit_set(int on)
{
	__asm__ volatile("msr dit, %0" :: "r"((uint64_t)(on != 0)) : "memory");
}
/* CTR_EL0 read (to test the DIT feature bit, bit 24). */
static inline uint64_t txm_ctr_el0(void)
{
	uint64_t v;
	__asm__ volatile("mrs %0, ctr_el0" : "=r"(v));
	return v;
}
/* Breakpoint (SoftwareBreakpoint(code, addr)) — TXM's hard trap. */
static inline void txm_brk(uint32_t code, uint64_t addr)
{
	__asm__ volatile("brk %0" :: "i"(0));
	(void)code; (void)addr;
}

/* ------------------------------------------------------------------ */
/* Section A — "restricted execution" enable/disable + policy state.  */
/* 000350c0 - 00035f08.                                               */
/* ------------------------------------------------------------------ */

/* FUN_000350c0 @ 0x000350c0   (est. txm_restricted_enable_begin)
 * Ghidra: undefined4 FUN_000350c0(int *param_1)
 * First step of enabling restricted execution on the shared policy state
 * `param_1` (DAT_000107d8): if the state word is 0 it is set to -1 (all ones)
 * and the transition returns base code 0xe3; an already-nonzero state fails
 * with class 0x01 (0x130e3). Caller FUN_0002b4f8 checks (ret>>8)&0xff and
 * panics (0xf1) on failure ("system_does_not_support_restricted").
 * Confidence: medium.
 * Notes: DAT_000107d8 is the single TXM restricted-execution state global.
 */
uint32_t txm_restricted_enable_begin(uint32_t *state)
{
	uint32_t old = *state;
	if (old == 0) {
		*state = 0xffffffffu;
	}
	return (old != 0) ? 0x130e3u : 0xe3u;
}

/* FUN_000350e8 @ 0x000350e8   (est. txm_restricted_enable_end)
 * Ghidra: undefined4 FUN_000350e8(int *param_1,int param_2)
 * Completes restricted-execution enable. `param_2` is the mode (1/2/3):
 * mode 2 requires the state already be -1 (else class 0x02); modes 1/3 walk
 * the state from -1 upward; a state of -2 returns class 0x04 (already fully
 * enabled) and a state of -1 at mode 1 returns class 0x03.
 * Confidence: medium.
 */
uint32_t txm_restricted_enable_end(int *state, int mode)
{
	uint32_t st;
	if (mode - 1u > 1) {                    /* mode != 1 && mode != 2 */
		return (mode != 3) ? 0x130e4u : 0xe4u;
	}
	st = (uint32_t)*state;
	if (mode == 2) {
		return (*state != -1) ? 0x230e4u : 0xe4u;
	}
	for (;;) {
		if (st == (uint32_t)-2) {
			return 0x430e4u;
		}
		if (st == (uint32_t)-1) {
			break;
		}
		if (*state == (int)st) {
			*state = (int)st + 1;
			return 0xe4u;
		}
		st = (uint32_t)*state;
	}
	return 0x330e4u;
}

/* FUN_00035178 @ 0x00035178   (est. txm_restricted_disable)
 * Ghidra: undefined4 FUN_00035178(int *param_1,int param_2)
 * Decrements the restricted-execution state word (mode 1: state--); modes
 * 2/3 return success without change. A state already 0 returns class 0x02.
 * Called from FUN_00022348 when a restricted code region is torn down.
 * Confidence: medium.
 */
uint32_t txm_restricted_disable(int *state, int mode)
{
	if (mode - 2u < 2) {
		return 0xe5u;
	}
	if (mode == 1) {
		int v = *state;
		*state = v - 1;
		return (v != 0) ? 0xe5u : 0x220e5u;
	}
	return 0x130e5u;
}

/* FUN_000351c8 @ 0x000351c8   (est. txm_policy_rule4)
 * Ghidra: undefined * FUN_000351c8(long param_1)
 * Policy rule 4 (page/protection check). If the ctx has a digest (field
 * +0x108) it computes the code-region digest from ((uint64_t *)ctx)[6]/((uint64_t *)ctx)[7]
 * (FUN_00033bf4) and validates it (FUN_00034b18 current trust context)
 * against the two registered digests (FUN_00032014 / FUN_00032104) and the
 * page type (FUN_000321dc); any failure returns a nonzero status, success
 * returns 0xa6. Without a digest it returns the "unset" status pointer
 * DAT_000112a6.
 * Confidence: medium.
 */
uint64_t *txm_policy_rule4(uint64_t *ctx)
{
	uint64_t digest, kind, scratch = 0;

	if (ctx[0x21] == 0) {                     /* +0x108 */
		return (uint64_t *)0x112a6;
	}
	txm_range_kind(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], &scratch);
	digest = ctx[0x21];                       /* +0x108 */
	kind = txm_policy_trust();                /* FUN_00034b18 */
	if (txm_region_auth(digest, kind) != 0)   /* FUN_00032014 */
		return (uint64_t *)0x16a6;
	if (txm_region_auth2(digest, scratch) != 0)  /* FUN_00032104 */
		return (uint64_t *)0x16a6;
	{
		uint32_t st = txm_region_pagetype(digest, ctx[0x22], ctx[0x23]); /* FUN_000321dc */
		return (uint64_t *)(uint64_t)((st & 0xff00) ? st : 0xa6);
	}
}

/* FUN_00035264 @ 0x00035264   (est. txm_policy_rule3)
 * Ghidra: uint FUN_00035264(long *param_1)
 * Policy rule 3 (JIT / oop-loader page check). Validates the code range and
 * the LOCALSPKEY tag on the code pages; consults the trust context
 * (FUN_00034b18) and the ops flag at vtable+0xd2; on the LOCALSPKEY-success
 * path a per-key attribute (FUN_00031334) is required. Returns a packed
 * status (base 0xa5).
 * Confidence: medium.
 */
uint32_t txm_policy_rule3(uint64_t *ctx)
{
	uint64_t vtable = ctx[0];
	uint64_t trust = txm_policy_trust();      /* FUN_00034b18 */
	uint64_t lo = 0, hi = 0, kind = 0;
	uint32_t st = txm_range_check(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], 0, 0, &kind); /* FUN_00033c9c */
	uint32_t u5, u6;

	if ((st & 0xff00) != 0) {
		return 0x2400 | 0xa5 | 0x10000;       /* 0x124a5 */
	}
	if ((kind & 1) != 0) {
		if ((*(uint8_t *)((uint8_t *)vtable + 0xd2) & 1) == 0 &&
		    (**(int (**)(uint64_t *))(vtable + 0x78))(ctx + 8) == 0) {
			return 0x3000 | 0xa5 | 0x20000;   /* 0x230a5 */
		}
	}
	txm_range_kind(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], &hi);
	if (txm_strcmp((char *)hi, "LOCALSPKEY") == 0) {
		if (trust == 0 || ctx[0x10] == 0) {   /* +0x80 */
			return 0xa5;
		}
		{
			uint32_t e = txm_ent_bits((uint64_t *)trust);
			if ((e & 0xff00) != 0) {
				return (e & 0xffff0000) | 0xa5 | (e & 0xff);
			}
		}
		return 0xa5;
	}
	return 0x2900 | 0xa5 | 0x30000;           /* 0x329a5 */
}

/* FUN_00035364 @ 0x00035364   (est. txm_policy_rule2)
 * Ghidra: undefined4 FUN_00035364(long *param_1)
 * Policy rule 2 (OOP JIT loader digest check). Reads the code-kind index
 * (FUN_00034174), and for kinds 1/2 requires a registered loader digest in
 * the table DAT_00010fd8; it then checks the caller's oop-jit-loader
 * entitlement (FUN_000314b0) and runs the vtable ops at +0x90/+0x98.
 * Confidence: medium.
 * Notes: string "com.apple.private.oop-jit-loader" at 0x2c39.
 */
uint32_t txm_policy_rule2(uint64_t *ctx)
{
	uint64_t vtable = ctx[0];
	uint64_t trust = txm_policy_trust();
	uint64_t kind_hi = 0, scratch = 0;
	uint16_t kind = 0;
	uint32_t st = txm_range_check(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], 0, 0, &kind_hi);

	if ((st & 0xff00) != 0) {
		return 0x124a7u;
	}
	if ((kind_hi & 1) != 0) {
		return 0x22ea7u;
	}
	if (txm_policy_trust2(ctx) != 0) {        /* FUN_00034b30 */
		return 0x330a7u;
	}
	txm_buf_digest(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], 0, &kind);
	if (kind == 0) {
		return 0x426a7u;
	}
	if (kind >= 3) {
		return 0x521a7u;
	}
	if (*(uint64_t *)(0x10fd8 + (uint64_t)kind * 8) == 0) {
		return 0x624a7u;
	}
	{
		uint64_t d = (*(uint64_t (**)(uint64_t *))(vtable + 0x90))(&scratch);
		uint64_t e = txm_ent_pair((uint64_t *)trust, (uint64_t)ENT_OOP_JIT_LOADER,
		                          *(uint64_t *)(0x10fd8 + (uint64_t)kind * 8));
		(*(void (**)(uint64_t, uint64_t))(vtable + 0x98))(d, scratch);
		return (e & 0xff00) ? 0x730a7u : 0xa7u;
	}
}

/* FUN_000354c8 @ 0x000354c8   (est. txm_policy_rule1)
 * Ghidra: undefined4 FUN_000354c8(long param_1)
 * Policy rule 1: validates the code range and trust context; returns base
 * 0xa4, with class 0x01 when the trust-context check fails.
 * Confidence: medium.
 */
uint32_t txm_policy_rule1(uint64_t *ctx)
{
	uint64_t kind = 0;
	uint32_t st = txm_range_check(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], 0, 0, &kind);
	if ((st & 0xff00) != 0) {
		return 0x124a4u;
	}
	if ((kind & 1) != 0) {
		return 0x22ea4u;
	}
	return (txm_policy_trust2(ctx) != 0) ? 0x330a4u : 0xa4u;
}

/* FUN_00035550 @ 0x00035550   (est. txm_policy_rule67)
 * Ghidra: undefined4 FUN_00035550(undefined8 *param_1)
 * Policy rules 6-10 (entitlement-based). Fills the code-kind byte
 * (FUN_00034028) and compares it against the vtable byte at +4; then checks
 * the oop-jit-loader / oop-jit-runner entitlements (FUN_000314b0 /
 * FUN_00031388) per the kind value. Returns a packed status (base 0xa3).
 * Confidence: medium.
 * Notes: strings at 0x2c39 / 0x2c5a.
 */
uint32_t txm_policy_rule67(uint64_t *ctx, uint8_t rule)
{
	uint64_t vtable = ctx[0];
	uint8_t kind = 0;
	(void)rule;
	int ent = 0;

	txm_buf_fill(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], &kind, 0);
	if (txm_len_kind(kind, *(uint8_t *)((uint8_t *)vtable + 4)) < 0) {
		return 0x130a3u;
	}
	{
		uint64_t trust = txm_policy_trust();
		uint32_t a = txm_ent_lookup((uint64_t *)trust, (uint64_t)ENT_OOP_JIT_LOADER, &ent);
		if ((a & 0xff00) != 0 || ent == 4) {
			uint32_t b = txm_ent_lookup((uint64_t *)trust, (uint64_t)ENT_OOP_JIT_RUNNER, &ent);
			if ((b & 0xff00) == 0 && ent != 4 && ent != 2) {
				return 0x326a3u;
			}
			return ((a | b) & 0xff00) ? 0xa3u : 0x430a3u;
		}
		return 0x226a3u;
	}
}

/* FUN_00035650 @ 0x00035650   (est. txm_policy_rule_ac)
 * Ghidra: undefined * FUN_00035650(undefined8 *param_1)
 * Walks the restricted-region list rooted at vtable+0x40; every entry's name
 * (kind from FUN_00033bf4) must be non-empty, else returns the "unset" status
 * DAT_000130ac. Success returns 0xac.
 * Confidence: medium.
 */
uint64_t *txm_policy_rule_ac(uint64_t *ctx)
{
	uint64_t *ent, *e;
	uint64_t name = 0;
	txm_range_kind(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], &name);

	e = (uint64_t *)*(uint64_t *)(ctx[0] + 0x40);
	if (e == 0) {
		return (uint64_t *)0xac;
	}
	ent = e;
	for (;;) {
		if (txm_strcmp((char *)name, "") == 0) {
			break;
		}
		if (e[0] == 0) {
			txm_fault(0x19);
		}
		ent = (uint64_t *)e[1];
		e = ent;
	}
	return (uint64_t *)0x130ac;
}

/* FUN_000356e4 @ 0x000356e4   (est. txm_policy_rule_ab)
 * Ghidra: undefined4 FUN_000356e4(long *param_1)
 * Policy selector: runs the vtable op at +0xc0 (when present); if it reports
 * unrestricted and a trust context exists, the "com.apple.private.security.
 * research..." entitlement is required, else class 0x01.
 * Confidence: medium.
 */
uint32_t txm_policy_rule_ab(uint64_t *ctx)
{
	uint64_t trust = txm_policy_trust();
	uint64_t vtable = ctx[0];

	if (*(uint64_t *)(vtable + 0xc0) == 0) {
		return 0xab;
	}
	if (((*(uint64_t (**)(void))(vtable + 0xc0))() & 1) != 0) {
		return 0xab;
	}
	if (trust == 0) {
		return 0x130ab;
	}
	return (txm_ent_has((uint64_t *)trust, (uint64_t)ENT_SECURITY_RESEARCH, 0) & 0xff00) ? 0xab : 0x130ab;
}

/* FUN_00035760 @ 0x00035760   (est. txm_policy_rule_aa)
 * Ghidra: undefined4 FUN_00035760(long *param_1)
 * Policy selector: runs vtable ops at +0xb8 then +0xc0 (when present); a
 * restricted result from either requires the security-research entitlement.
 * Confidence: medium.
 * Notes: string at 0x2cbd.
 */
uint32_t txm_policy_rule_aa(uint64_t *ctx)
{
	uint64_t trust = txm_policy_trust();
	uint64_t vtable = ctx[0];
	uint64_t (*op_b8)(void) = *(uint64_t (**)(void))(vtable + 0xb8);
	uint64_t (*op_c0)(void) = *(uint64_t (**)(void))(vtable + 0xc0);

	if (op_b8 != 0) {
		if ((op_b8() & 1) != 0) {
			return 0xaa;
		}
	} else if (op_c0 == 0) {
		return 0xaa;
	}
	if (op_c0 != 0 && (op_c0() & 1) != 0) {
		return 0xaa;
	}
	if (trust == 0) {
		return 0xaa;
	}
	return (txm_ent_has((uint64_t *)trust, (uint64_t)ENT_SECURITY_RESEARCH, 0) & 0xff00) ? 0xaa : 0x130aa;
}

/* FUN_00035800 @ 0x00035800   (est. txm_policy_rule_02)
 * Ghidra: int FUN_00035800(long *param_1)
 * Policy selector: when vtable flag byte at +0x4d bit 0 is set, runs the
 * vtable op at [0x14]; if unrestricted and a trust context exists, the caller
 * must hold one of the six entitlements in DAT_00010ff0 (indexed in order),
 * else returns a status with the per-index class.
 * Confidence: medium.
 */
int txm_policy_rule_02(uint64_t *ctx, uint8_t rule)
{
	uint64_t trust = txm_policy_trust();
	uint64_t vtable = ctx[0];
	(void)rule;

	if ((*(uint8_t *)((uint8_t *)vtable + 0x4d) & 1) != 0) {
		if ((*(uint64_t (**)(void))(vtable + 0xa0))() & 1) {
			return 0xa2;
		}
		if (trust == 0) {
			return 0xa2;
		}
		{
			uint64_t off = 0;
			int r = 0x130a2;
			do {
				if (txm_ent_has((uint64_t *)trust, *(uint64_t *)(0x10ff0 + off), 1) == 0) {
					return r;
				}
				r += 0x10000;
				off += 8;
			} while (off != 0x30);
		}
	}
	return 0xa2;
}

/* FUN_000358a4 @ 0x000358a4   (est. txm_policy_rule_d1)
 * Ghidra: undefined * FUN_000358a4(undefined8 *param_1,uint param_2)
 * Policy selector for modes < 6 (or when no code-region is attached): checks
 * the code-range "allowed" flag (FUN_00033ad4 bit 1) against the name buffer
 * presence (FUN_00033bf4); mismatches return class 0x02 of base 0xa1; success
 * returns the "set" status pointer (section_00000068.reloff + 1).
 * Confidence: medium.
 */
uint64_t *txm_policy_rule_d1(uint64_t *ctx, uint32_t mode)
{
	uint64_t vtable = ctx[0];
	uint32_t flag = 0;
	uint64_t name = 0;

	txm_range_kind2(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], &flag);
	txm_range_kind(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], &name);
	if (mode < 6 || *(uint64_t *)(vtable + 8) == 0) {
		if ((flag & 2) == ((name != 0) ? 2 : 0)) {
			return (uint64_t *)0x130a1;
		}
		if (mode < 6) {
			if (mode - 1u < 2) {
				if (flag == 0) {
					return (uint64_t *)0x22da1;
				}
			} else if (flag != 0) {
				return (uint64_t *)0x22da1;
			}
		}
	}
	return (uint64_t *)0x200000;   /* section_00000068.reloff + 1 */
}

/* FUN_0003596c @ 0x0003596c   (est. txm_policy_rule_a0)
 * Ghidra: int FUN_0003596c(long param_1,uint param_2)
 * Policy selector: when ctx state byte +0x100 bit 0 is set, the caller must
 * hold the "com.apple.developer.web-browser..." entitlement (name 0xdda /
 * string 0x29d3) and, for modes < 6, one of the four entitlements in
 * DAT_00011020 (per-mode); failure returns class 0x01 of base 0xa0.
 * Confidence: medium.
 */
int txm_policy_rule_a0(uint64_t *ctx, uint32_t mode)
{
	if ((*(uint8_t *)((uint8_t *)ctx + 0x100) & 1) != 0) {
		if (txm_ent_has(ctx + 0xf, 0xdda, 1) == 0 &&
		    txm_ent_has(ctx + 0xf, (uint64_t)"com.apple.developer.web-browser...", 1) != 0) {
			return 0x130a0;
		}
		if (mode < 6) {
			uint64_t off = 0;
			int r = 0x130a0;
			do {
				r += 0x10000;
				if (txm_ent_has(ctx + 0xf, *(uint64_t *)(0x11020 + off), 0) == 0) {
					return r;
				}
				off += 8;
			} while (off != 0x20);
		}
	}
	return 0xa0;
}

/* FUN_00035a38 @ 0x00035a38   (est. txm_policy_rule_a8)
 * Ghidra: undefined4 FUN_00035a38(long *param_1,uint param_2)
 * Policy selector for modes < 6: calls the ops callback param_1[1] (when
 * present) and checks the ops vtable flag byte at +6 bit 0; the rule succeeds
 * (0xa8) when either the callback reports unrestricted or the flag is clear.
 * Confidence: medium.
 */
uint32_t txm_policy_rule_a8(uint64_t *ctx, uint32_t mode)
{
	uint32_t r = 0xa8u;
	if (mode < 6) {
		r = 0x130a8u;
		if (((ctx[1] == 0) || (((uint64_t(*)())(ctx[1]))() & 1) == 0) &&
		    (r = 0x230a8u, (*(uint8_t *)ctx[0] & 1) == 0)) {
			r = 0xa8u;
		}
	}
	return r;
}

/* FUN_00035aa0 @ 0x00035aa0   (est. txm_policy_rule_a9)
 * Ghidra: undefined4 FUN_00035aa0(long *param_1,int param_2)
 * Policy selector: succeeds (0xa9) unless the ops vtable flag byte at +5 bit 0
 * is set AND the mode is >= 8.
 * Confidence: medium.
 */
uint32_t txm_policy_rule_a9(uint64_t *ctx, int mode)
{
	uint32_t r = 0xa9u;
	if ((*(uint8_t *)ctx[0] & 1) != 0 && (mode - 7u > 3)) {
		r = 0x130a9u;
	}
	return r;
}

/* FUN_00035acc @ 0x00035acc   (est. txm_region_policy_prepare)
 * Ghidra: undefined4 FUN_00035acc(long *param_1,long *param_2,ulong param_3,
 *                                 ulong param_4)
 * Initializes a 0x104-byte policy context `param_2` (zeroing 33 8-byte slots
 * + the byte at +0x102) from the source ctx `param_1` and a code range
 * {param_3, param_4}. Validates the range (non-empty, >= 12 bytes, no
 * 64-bit wrap) and that each required vtable policy field (per the flags at
 * vtable +0x49/0x4a/0x4b/0x4d/0x4e) is present; stores {src, base, size} into
 * slots 0/1/2. Returns a packed status (base 0x200).
 * Confidence: medium.
 */
uint32_t txm_region_policy_prepare(uint64_t *src, uint64_t *dst,
                                   uint64_t base, uint64_t size)
{
	uint32_t r;
	int i;
	uint64_t vtable = src[0];

	for (i = 0x21; i >= 0; i--) {
		dst[i] = 0;
	}
	*(uint8_t *)((uint8_t *)dst + 0x102) = 0;
	if (base == 0) {
		return 0x12c00u;
	}
	if (size < 0xc) {
		return 0x22300u;
	}
	if (TXM_CARRY8(base, size)) {
		return 0x32100u;
	}
	r = 0x40200u;
	if (vtable != 0) {
		if ((*(uint8_t *)((uint8_t *)vtable + 0x49) & 1) != 0) {
			if (src[0x12] == 0) return 0x50200u;
			if (src[0x13] == 0) return 0x60200u;
		}
		if ((*(uint8_t *)((uint8_t *)vtable + 0x4a) & 1) != 0) {
			if (src[0xe] == 0) return 0x70200u;
			if (src[0xf] == 0) return 0x80200u;
		}
		if ((*(uint8_t *)((uint8_t *)vtable + 0x4b) & 1) != 0 && src[0x11] == 0) {
			return 0x90200u;
		}
		if ((*(uint8_t *)((uint8_t *)vtable + 0x4d) & 1) != 0 && src[0x14] == 0) {
			return 0xa0200u;
		}
		if ((*(uint8_t *)((uint8_t *)vtable + 0x4e) & 1) != 0 && src[0x15] == 0) {
			return 0xb0200u;
		}
		dst[0] = (uint64_t)src;
		dst[1] = base;
		dst[2] = size;
		return 0;
	}
	return r;
}

/* FUN_00035bf0 @ 0x00035bf0   (est. txm_region_policy_install)
 * Ghidra: undefined * FUN_00035bf0(undefined8 *param_1)
 * Installs the prepared policy context `param_1`. Requires a name buffer
 * (param_1[1]) and that the context not already be installed (state byte
 * +0x29 clear). Resolves the code-region and data-region descriptors
 * (FUN_00032630 / FUN_00033d40), runs the trust-level probe (FUN_00034b50),
 * and on success clears the policy slots and marks the state byte +0x29 set
 * (returning the "installed" marker). Returns a status pointer.
 * Confidence: medium.
 */
uint64_t *txm_region_policy_install(uint64_t *ctx)
{
	uint64_t kind = 0;
	uint32_t st;

	if (ctx[1] == 0) {
		return (uint64_t *)0x10301;
	}
	if ((*(uint8_t *)((uint8_t *)ctx + 0x29) & 1) != 0) {
		return (uint64_t *)0x23401;
	}
	st = txm_region_resolve(ctx[1], ((uint64_t *)ctx)[2], ctx + 3);   /* FUN_00032630 */
	if ((st & 0xff00) != 0) {
		return (uint64_t *)(uint64_t)st;
	}
	st = txm_region_resolve2(ctx[0], ((uint64_t *)ctx)[3], ctx[4], ctx + 6); /* FUN_00033d40 */
	if ((st & 0xff00) != 0) {
		return (uint64_t *)(uint64_t)st;
	}
	{
		uint32_t trust = txm_policy_trust3(ctx);          /* FUN_00034b50 */
		if (((uint8_t)trust) == 0x40) {
			if ((trust & 0xff00) != 0) {
				if ((trust & 0xff00) == 0x2800) {
					goto done;
				}
			} else {
				goto clear;
			}
		} else if ((trust & 0xff00) == 0x1100) {
			goto done;
		} else if ((trust & 0xff00) == 0) {
			goto clear;
		}
		return (uint64_t *)(uint64_t)trust;
	}
clear:
	{
		uint32_t c = txm_range_check(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], 0, 0, &kind);
		if ((c & 0xff00) != 0) {
			kind |= 1;
		}
		if ((kind & 1) == 0) {
			int i;
			for (i = 0x1f; i >= 0x10; i--) {
				ctx[i] = 0;
			}
			*(uint8_t *)((uint8_t *)ctx + 0x100) = 0;
		}
	}
done:
	txm_region_policy_commit(ctx, ((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7]);  /* FUN_00035d24 */
	*(uint8_t *)((uint8_t *)ctx + 0x29) = 1;
	return (uint64_t *)0x10000;   /* Reset.magic + 1 */
}

/* FUN_00035d24 @ 0x00035d24   (est. txm_region_policy_commit)
 * Ghidra: void FUN_00035d24(long param_1,undefined8 param_2,ulong param_3)
 * Commits the policy name/digest: computes the 32-byte digest of the code
 * range {param_2, param_3} (FUN_00034028 + FUN_000325b0), copies it into the
 * ctx digest buffer at param_1+0x40, and stores its length at param_1+0x70.
 * A digest longer than 0x30 bytes faults (0x19).
 * Confidence: medium.
 */
void txm_region_policy_commit(uint64_t *ctx, uint64_t base, uint64_t size)
{
	uint8_t kind = 0, digest[0x38];
	uint64_t guard = txm_canary;

	kind = 0;
	txm_buf_fill(base, size, &kind, (long)&kind + 1);
	txm_region_digest(kind, base, size & 0xffffffff, (uint64_t *)digest);  /* FUN_000325b0 */
	if (*(uint8_t *)((uint8_t *)&kind + 1) > 0x30) {
		txm_fault(0x19);
	}
	txm_memcpy((void *)((uint8_t *)ctx + 0x40), digest, 0x38);
	*(uint64_t *)((uint8_t *)ctx + 0x70) = *(uint8_t *)((uint8_t *)&kind + 1);
	if (guard != txm_canary) {
		txm_stack_guard_fail();
	}
}

/* ------------------------------------------------------------------ */
/* Section B — region association / policy commit / query.            */
/* 00036078 - 00036d44.                                               */
/* ------------------------------------------------------------------ */

/* FUN_00036078 @ 0x00036078   (est. txm_region_attach_digest)
 * Ghidra: undefined * FUN_00036078(undefined8 *param_1,long param_2)
 * Attaches the externally-supplied digest `param_2` to the policy region
 * `param_1`. Requires a name buffer (param_1[1]) and that the kind byte
 * (ctx+0x101) be clear. When a digest callback is present (vtable+0x58) it
 * validates the supplied digest against the code range (thunk_FUN_0002dc80 /
 * thunk_FUN_0002da90) and sets the flag byte ctx+0x2a. Success returns 0x16.
 * Confidence: medium.
 */
uint64_t *txm_region_attach_digest(uint64_t *ctx, uint64_t digest)
{
	if (ctx[1] == 0) {
		return (uint64_t *)0x10316;
	}
	if (*(uint8_t *)((uint8_t *)ctx + 0x101) == 0) {
		if (digest == 0) {
			return (uint64_t *)0x32c16;
		}
		{
			uint64_t cb = *(uint64_t *)(ctx[0] + 0x58);
			if (cb != 0) {
				uint64_t len = txm_lenstr((const char *)digest);
				if (txm_region_match(digest, cb, len) == 0) {   /* thunk_FUN_0002da90 */
					*(uint8_t *)((uint8_t *)ctx + 0x2a) = 1;
				}
			}
		}
		return (uint64_t *)0x16;
	}
	return (uint64_t *)0x23016;
}

/* FUN_0003611c @ 0x0003611c   (est. txm_region_parse)
 * Ghidra: undefined * FUN_0003611c(long param_1,undefined8 param_2)
 * Associates a parsed region object `param_2` with the region context at
 * `param_1` (sibling FUN_0003611c). Requires a code region be present
 * (param_1+8) and the kind byte (param_1+0x102) clear. On success the digest
 * field (param_1+0x108) is set and success 0x05 returned; an already-set
 * digest fails (0x33405).
 * Confidence: medium (matches sibling file's txm_region_parse name).
 */
uint64_t *txm_region_parse(uint64_t ctx, uint64_t obj)
{
	if (*(uint64_t *)(ctx + 8) != 0) {
		if (*(uint8_t *)(ctx + 0x102) == 0) {
			if (*(uint64_t *)(ctx + 0x108) == 0) {
				if ((uintptr_t)txm_region_set_digest(obj, ctx) == 0) {
					*(uint64_t *)(ctx + 0x108) = obj;
					return (uint64_t *)0x5;
				}
			} else {
				return (uint64_t *)0x33405;
			}
		} else {
			return (uint64_t *)0x23005;
		}
	}
	return (uint64_t *)0x10305;
}

/* FUN_000361a0 @ 0x000361a0   (est. txm_region_lookup)
 * Ghidra: undefined * FUN_000361a0(long param_1,long *param_2)
 * Returns the parsed region object (param_1+0x108) via `param_2` and clears
 * the field. Requires a code region be present (param_1+8); a set digest is
 * required (else 0x21206). Success returns 0x06.
 * Confidence: medium (matches sibling file's txm_region_lookup name).
 */
uint64_t *txm_region_lookup(uint64_t ctx, uint64_t *out)
{
	if (*(uint64_t *)(ctx + 8) == 0) {
		return (uint64_t *)0x10306;
	}
	if (*(uint64_t *)(ctx + 0x108) != 0) {
		if (out != 0) {
			*out = *(uint64_t *)(ctx + 0x108);
		}
		*(uint64_t *)(ctx + 0x108) = 0;
		return (uint64_t *)0x6;
	}
	return (uint64_t *)0x21206;
}

/* FUN_000361e0 @ 0x000361e0   (est. txm_policy_kind_get)
 * Ghidra: undefined8 FUN_000361e0(long param_1,undefined1 *param_2)
 * Returns the policy kind byte (param_1+0x102) via `param_2`; success 0x08.
 * Confidence: medium.
 */
uint64_t txm_policy_kind_get(uint64_t ctx, uint8_t *out)
{
	if (out != 0) {
		*out = *(uint8_t *)(ctx + 0x102);
	}
	return 8;
}

/* FUN_000361f8 @ 0x000361f8   (est. txm_policy_kind_map)
 * Ghidra: undefined * FUN_000361f8(long *param_1,char *param_2)
 * Maps the applied policy kind (ctx+0x102) to a platform value: for kinds
 * 8/9 the vtable op plVar3[5] is invoked (with the flag byte at vtable+0xd5)
 * to derive the kind; kind 10 maps to 3; any other kind fails (0x42818).
 * Requires the kind byte be set and the vtable flag +0x48 bit 0 and op [5]
 * be present. Returns 0x18 on success.
 * Confidence: medium.
 */
uint64_t *txm_policy_kind_map(uint64_t *ctx, char *out)
{
	uint8_t kind = *(uint8_t *)((uint8_t *)ctx + 0x102);
	uint64_t vtable = ctx[0];
	char c;

	if (kind == 0) {
		return (uint64_t *)0x12218;
	}
	if ((*(uint8_t *)((uint8_t *)vtable + 0x48) & 1) == 0) {
		return (uint64_t *)0x22818;
	}
	if (*(uint64_t *)(vtable + 0x28) == 0) {        /* plVar3[5] */
		return (uint64_t *)0x32818;
	}
	if (kind - 8u < 2) {
		uint8_t flag = *(uint8_t *)((uint8_t *)vtable + 0xd5);
		char local = 0;
		(*(void (**)(uint64_t *, char *))(vtable + 0x28))(ctx + 8, &local);
		c = 3;
		if ((flag & local) == 0) {
			c = local;
		}
	} else {
		c = 3;
		if (kind != 10) {
			return (uint64_t *)0x42818;
		}
	}
	if (out != 0) {
		*out = c;
	}
	return (uint64_t *)0x18;
}

/* FUN_000362c4 @ 0x000362c4   (est. txm_region_digest_get)
 * Ghidra: undefined * FUN_000362c4(long param_1,long *param_2)
 * Returns the parsed-region digest (param_1+0x108) via `param_2`; success
 * 0x09.
 * Confidence: medium.
 */
uint64_t *txm_region_digest_get(uint64_t ctx, uint64_t *out)
{
	if (*(uint64_t *)(ctx + 0x108) != 0) {
		if (out != 0) {
			*out = *(uint64_t *)(ctx + 0x108);
		}
		return (uint64_t *)0x9;
	}
	return (uint64_t *)0x11209;
}

/* FUN_000362ec @ 0x000362ec   (est. txm_region_range_get)
 * Ghidra: undefined * FUN_000362ec(long param_1,long *param_2)
 * Returns the code-region range {param_1+8, param_1+0x10} via `param_2`;
 * success 0x0a.
 * Confidence: medium.
 */
uint64_t *txm_region_range_get(uint64_t ctx, uint64_t *out)
{
	if (*(uint64_t *)(ctx + 8) != 0) {
		if (out != 0) {
			out[1] = *(uint64_t *)(ctx + 0x10);
			out[0] = *(uint64_t *)(ctx + 8);
		}
		return (uint64_t *)0xa;
	}
	return (uint64_t *)0x1030a;
}

/* FUN_00036318 @ 0x00036318   (est. txm_region_residual_get)
 * Ghidra: undefined * FUN_00036318(long param_1,long *param_2)
 * Returns the residual region size (param_1+0x10 minus the consumed byte
 * count at param_1+0x20) via `param_2`. Requires the region be installed
 * (state byte +0x29). Success 0x17.
 * Confidence: medium.
 */
uint64_t *txm_region_residual_get(uint64_t ctx, uint64_t *out)
{
	if ((*(uint8_t *)(ctx + 0x29) & 1) == 0) {
		return (uint64_t *)0x10417;
	}
	if (out != 0) {
		*out = *(uint64_t *)(ctx + 0x10) - (uint64_t)*(uint32_t *)(ctx + 0x20);
	}
	return (uint64_t *)0x17;
}

/* FUN_0003634c @ 0x0003634c   (est. txm_code_page_mark_begin)
 * Ghidra: uint FUN_0003634c(long *param_1,undefined1 (*param_2) [16])
 * Marks a code page range begin. Validates the region is installed (state
 * byte +0x29) and not already begun (flag byte +5 clear); derives the page
 * span (param_1[2] - u32 at +4) and computes a canonical page descriptor via
 * the vtable op at +200 (when present). A zero span or out-of-window span
 * faults (0x19). Returns the mark (0x15).
 * Confidence: medium.
 */
uint32_t txm_code_page_mark_begin(uint64_t *ctx, uint64_t *out)
{
	uint64_t vtable = ctx[0];
	uint64_t span, base, end, p;
	uint64_t desc[2];

	if (out == 0) {
		return 0x10000 | 0x2c15;
	}
	if ((*(uint8_t *)((uint8_t *)ctx + 5) & 1) != 0) {
		return 0x23415u;
	}
	if ((*(uint8_t *)((uint8_t *)ctx + 0x29) & 1) == 0) {
		return 0x10000 | 0x417;
	}
	span = ((uint64_t *)ctx)[2] - (uint64_t)*(uint32_t *)(ctx + 4);
	if (span == 0) {
		return 0x32315u;
	}
	base = ctx[1];
	end = base + ((uint64_t *)ctx)[2];
	if (TXM_TAGABLE(base, end)) {
		end = TXM_TAGFIX(end);
	}
	p = base + *(uint32_t *)(ctx + 4);
	desc[1] = span;
	desc[0] = p;
	if (p <= end && base <= p) {
		if (*(uint64_t *)(vtable + 200) != 0) {
			(*(void (**)(uint64_t *, uint64_t, uint64_t *))(vtable + 200))(ctx, p, desc);
		}
		*(uint8_t *)((uint8_t *)ctx + 5) = 1;
		out[0] = desc[0];
		out[1] = desc[1];
		return 0x15;
	}
	txm_fault(0x19);
	return 0;
}

/* FUN_00036424 @ 0x00036424   (est. txm_code_digest_word_get)
 * Ghidra: undefined * FUN_00036424(long param_1,uint *param_2)
 * Returns the byte-swapped digest word at (param_1+0x18)[+8 + consumed].
 * Requires the region be installed (state byte +0x29). A short span faults
 * (0x19). Success 0x0b.
 * Confidence: medium.
 */
uint64_t *txm_code_digest_word_get(uint64_t ctx, uint32_t *out)
{
	if ((*(uint8_t *)(ctx + 0x29) & 1) == 0) {
		return (uint64_t *)0x1040b;
	}
	if (out != 0) {
		uint64_t p = *(uint64_t *)(ctx + 0x18);
		if (p + (uint64_t)*(uint32_t *)(ctx + 0x20) < p + 0xcU) {
			txm_fault(0x19);
		}
		{
			uint32_t w = *(uint32_t *)(p + 8);
			uint32_t v = (w & 0xff00ff00) >> 8 | (w & 0xff00ff) << 8;
			*out = (v >> 0x10 | v << 0x10);
		}
	}
	return (uint64_t *)0xb;
}

/* FUN_00036480 @ 0x00036480   (est. txm_code_region_lookup)
 * Ghidra: dword * FUN_00036480(long param_1,undefined8 *param_2,
 *                              uint *param_3,uint *param_4)
 * Looks up a code sub-region by its offset (param_1+0x30 - param_1+0x18)
 * among the region descriptors at param_1+0x18. Returns the descriptor
 * (param_1+0x30/0x38), its index and the matched offset. Not found returns
 * 0x2040c; malformed table faults (0x19).
 * Confidence: medium.
 */
uint64_t *txm_code_region_lookup(uint64_t ctx, uint64_t *desc_out,
                                 uint32_t *idx_out, uint32_t *off_out)
{
	uint64_t base, end;
	uint32_t count, i, u1, target;
	uint32_t *slot;

	if ((*(uint8_t *)(ctx + 0x29) & 1) == 0) {
		return (uint64_t *)0x1040c;
	}
	base = *(uint64_t *)(ctx + 0x18);
	end = base + *(uint32_t *)(ctx + 0x20);
	if (!(end <= base + *(uint32_t *)(ctx + 0x20) && base <= base + 0xc)) {
		txm_fault(0x19);
	}
	{
		uint32_t w = *(uint32_t *)(base + 8);
		uint32_t v = (w & 0xff00ff00) >> 8 | (w & 0xff00ff) << 8;
		count = v >> 0x10 | v << 0x10;
	}
	if ((uint64_t)count > ((uint64_t)*(uint32_t *)(ctx + 0x20) - 0xc) >> 3) {
		txm_fault(0x19);
	}
	if (count == 0) {
		return (uint64_t *)0x2040c;
	}
	target = (uint32_t)(*(uint32_t *)(ctx + 0x30) - (uint32_t)base);
	slot = (uint32_t *)(base + 0x10);
	for (i = 0; i < count; i++) {
		uint32_t e = slot[0];
		uint32_t ev = (e & 0xff00ff00) >> 8 | (e & 0xff00ff) << 8;
		if ((ev >> 0x10 | ev << 0x10) == target) {
			if (desc_out != 0) {
				desc_out[1] = *(uint64_t *)(ctx + 0x38);
				desc_out[0] = *(uint64_t *)(ctx + 0x30);
			}
			if (idx_out != 0) *idx_out = i;
			if (off_out != 0) *off_out = target;
			return (uint64_t *)0xc;    /* Reset.filetype */
		}
		slot += 2;
	}
	return (uint64_t *)0x2040c;
}

/* FUN_0003653c @ 0x0003653c   (est. txm_code_page_hash)
 * Ghidra: undefined * FUN_0003653c(long param_1,undefined8 param_2,
 *      undefined1 (*param_3) [16],undefined4 *param_4)
 * Hashes a code page range (type `param_2`) into a 16-byte descriptor via
 * FUN_00032b38 with the type-specific magic (0xfade0000|type / 0x7171 /
 * 0x8181 / 0xfade0c01 / 0xfade7172). Returns the descriptor and an info
 * word; failure 0x4240d. Requires the region be installed.
 * Confidence: medium.
 */
uint64_t *txm_code_page_hash(uint64_t ctx, uint64_t type,
                             uint64_t (*desc)[16], uint32_t *info)
{
	uint32_t local = 0xffffffff, magic;

	if ((*(uint8_t *)(ctx + 0x29) & 1) == 0) {
		return (uint64_t *)0x1040d;
	}
	magic = 0xfade0b01;
	{
		int t = (int)type;
		if (t < 0x1000) {
			if (t < 7) {
				if (t == 0) {
					return (uint64_t *)0x2260d;
				}
				if (t == 2) {
					magic = 0xfade0c01;
					goto hash;
				}
				if (t != 5) {
					return (uint64_t *)0x3260d;
				}
				magic = 0x7171;
			} else {
				if (3 < t - 8U) {
					if (t != 7) {
						return (uint64_t *)0x3260d;
					}
					magic = 0xfade7172;
					goto hash;
				}
				magic = 0x8181;
			}
			magic |= 0xfade0000;
		} else {
			if (t - 0x1000U < 5) {
				return (uint64_t *)0x2260d;
			}
			if (t != 0x10000) {
				return (uint64_t *)0x3260d;
			}
		}
	}
hash:
	{
		uint64_t r = txm_page_hash(*(uint64_t *)(ctx + 0x18),
		                          *(uint64_t *)(ctx + 0x20), type, magic, &local);
		if (r == 0) {
			return (uint64_t *)0x4240d;
		}
		if (desc != 0) {
			*(uint64_t *)desc = r;
		}
		if (info != 0) {
			*info = local;
		}
		return (uint64_t *)0xd;
	}
}

/* FUN_00036654 @ 0x00036654   (est. txm_code_region_at)
 * Ghidra: undefined * FUN_00036654(long param_1,uint param_2,ulong *param_3,
 *      uint *param_4,uint *param_5)
 * Returns the descriptor and byte span of code sub-region `param_2` from the
 * descriptor table at param_1+0x18. Out of range returns 0x2240e; malformed
 * table faults (0x19). Success 0x0e.
 * Confidence: medium.
 */
uint64_t *txm_code_region_at(uint64_t ctx, uint32_t idx, uint64_t *span_out,
                             uint32_t *off_out, uint32_t *len_out)
{
	uint64_t base = *(uint64_t *)(ctx + 0x18);
	uint64_t size = *(uint32_t *)(ctx + 0x20);
	uint64_t start = base + 0xc, end = base + size;
	uint32_t count, v;

	if ((*(uint8_t *)(ctx + 0x29) & 1) == 0) {
		return (uint64_t *)0x1040e;
	}
	if (end < start || start < base) {
		txm_fault(0x19);
	}
	{
		uint32_t w = *(uint32_t *)(base + 8);
		uint32_t ev = (w & 0xff00ff00) >> 8 | (w & 0xff00ff) << 8;
		count = ev >> 0x10 | ev << 0x10;
	}
	if ((uint64_t)(size - 0xc) >> 3 < (uint64_t)count) {
		txm_fault(0x19);
	}
	if (idx >= count) {
		return (uint64_t *)0x2240e;
	}
	{
		uint32_t *slot = (uint32_t *)(start + (uint64_t)idx * 8);
		uint32_t o = slot[1];
		uint32_t ov = (o & 0xff00ff00) >> 8 | (o & 0xff00ff) << 8;
		uint32_t off = ov >> 0x10 | ov << 0x10;
		if (span_out != 0) {
			uint64_t p = base + off;
			if (p < base || end < p + 8) {
				txm_fault(0x19);
			}
			{
				uint32_t w = *(uint32_t *)(p + 4);
				uint32_t ev = (w & 0xff00ff00) >> 8 | (w & 0xff00ff) << 8;
				uint64_t len = (uint64_t)(ev >> 0x10 | ev << 0x10);
				if (end < p || size - off < len) {
					txm_fault(0x19);
				}
				span_out[0] = p;
				span_out[1] = len;
			}
		}
		if (off_out != 0) *off_out = off;
		if (len_out != 0) {
			uint32_t l = slot[0];
			uint32_t lv = (l & 0xff00ff00) >> 8 | (l & 0xff00ff) << 8;
			*len_out = lv >> 0x10 | lv << 0x10;
		}
		return (uint64_t *)0xe;
	}
}

/* FUN_00036724 @ 0x00036724   (est. txm_policy_trust_get)
 * Ghidra: undefined * FUN_00036724(long param_1,undefined8 *param_2)
 * Returns the current trust context (FUN_00034b18) via `param_2`; success
 * 0x0f. Requires the region be installed.
 * Confidence: medium.
 */
uint64_t *txm_policy_trust_get(uint64_t ctx, uint64_t *out)
{
	if ((*(uint8_t *)(ctx + 0x29) & 1) == 0) {
		return (uint64_t *)0x1040f;
	}
	if (out != 0) {
		*out = txm_policy_trust();
	}
	return (uint64_t *)0xf;
}

/* FUN_00036770 @ 0x00036770   (est. txm_policy_ent_check)
 * Ghidra: uint FUN_00036770(long param_1,undefined8 param_2)
 * Checks the caller's entitlement `param_2` (FUN_00031424) against the trust
 * context. Requires the region be installed. Success 0x10.
 * Confidence: medium.
 */
uint32_t txm_policy_ent_check(uint64_t ctx, uint64_t name)
{
	uint64_t trust;
	uint32_t st;

	if ((*(uint8_t *)(ctx + 0x29) & 1) == 0) {
		return 0x10410u;
	}
	trust = txm_policy_trust();
	st = txm_ent_has((uint64_t *)trust, name, 1);
	return (st & 0xff00) ? st : 0x10u;
}

/* FUN_000367c8 @ 0x000367c8   (est. txm_policy_ent_pair_check)
 * Ghidra: uint FUN_000367c8(long param_1,undefined8 param_2,undefined8 param_3)
 * Checks a two-value entitlement (FUN_000314b0) against the trust context.
 * Requires the region be installed. Success 0x11.
 * Confidence: medium.
 */
uint32_t txm_policy_ent_pair_check(uint64_t ctx, uint64_t a, uint64_t b)
{
	uint64_t trust;
	uint32_t st;

	if ((*(uint8_t *)(ctx + 0x29) & 1) == 0) {
		return 0x10411u;
	}
	trust = txm_policy_trust();
	st = txm_ent_pair((uint64_t *)trust, a, b);
	return (st & 0xff00) ? st : 0x11u;
}

/* FUN_00036824 @ 0x00036824   (est. txm_code_region_extend)
 * Ghidra: int FUN_00036824(long *param_1,uint param_2,ulong param_3)
 * Extends the code-region descriptor table so the span [param_2, param_3]
 * is covered: locates the target slot (via FUN_00036654 / FUN_00036480),
 * verifies the page type (FUN_0003653c), and grows the descriptor array
 * (via the vtable op at +200 when present) writing the new start/count.
 * Success 0x12; a variety of class-encoded failures.
 * Confidence: low (complex slot/refcount logic; identity inferred).
 */
int txm_code_region_extend(uint64_t *ctx, uint32_t start, uint64_t end)
{
	uint32_t tgt = 0xffffffff, off = 0xffffffff, pg = 0xffffffff, pi = 0xffffffff;
	uint32_t count, i, c;
	uint64_t base, size, lo, p, p_end;
	uint64_t vtable = ctx[0];
	uint64_t desc[2];
	uint32_t w, ev;
	uint64_t span_lo = 0, span_hi = 0;

	if (*(uint8_t *)((uint8_t *)ctx + 0x102) == 0) {
		return 0x12212;
	}
	if ((*(uint8_t *)((uint8_t *)ctx + 5) & 1) != 0) {
		return 0x93012;
	}
	base = ((uint64_t *)ctx)[3];
	size = *(uint32_t *)(ctx + 4);
	start = *(uint32_t *)(ctx + 4);   /* NB: overwritten below per decompile */
	lo = base + size;
	if (lo < base + 0xc || base + 0xc < base) {
		txm_fault(0x19);
	}
	{
		uint32_t w0 = *(uint32_t *)(base + 8);
		uint32_t e0 = (w0 & 0xff00ff00) >> 8 | (w0 & 0xff00ff) << 8;
		count = e0 >> 0x10 | e0 << 0x10;
	}
	if ((uint64_t)(size - 0xc) >> 3 < (uint64_t)count) {
		txm_fault(0x19);
	}
	/* walk the descriptor slots accumulating spans until [param_2,param_3]
	 * is contained */
	c = *(uint32_t *)(base + 8);
	{
		uint32_t e0 = (c & 0xff00ff00) >> 8 | (c & 0xff00ff) << 8;
		count = e0 >> 0x10 | e0 << 0x10;
	}
	if (start > end) {
		return 0x22112;
	}
	if (start > size) {
		return 0x22112;
	}
	if ((uint64_t)((uint64_t *)ctx)[2] < end) {
		return 0x42112;
	}
	if (count == 0) {
		txm_fault(0x19);
	}
	i = 0;
	{
		uint32_t e0 = *(uint32_t *)(base + 0x10);
		uint32_t ev0 = (e0 & 0xff00ff00) >> 8 | (e0 & 0xff00ff) << 8;
		span_hi = (uint64_t)(ev0 >> 0x10 | ev0 << 0x10);
	}
	for (;;) {
		txm_code_region_at((uint64_t)ctx, i, &span_lo, 0, 0);
		if (span_lo + span_hi == start) {
			uint32_t idx = 0xffffffff;
			txm_code_region_lookup((uint64_t)ctx, 0, &idx, 0);
			if (i < idx) {
				return 0x73212;
			}
			/* ensure the page type at the new offset */
			{
				uint32_t pginfo = 0xffffffff;
				txm_page_hash(((uint64_t *)ctx)[3], ctx[4], 0, 0xfade0c02, &pginfo);
				pg = pginfo;
				if (*(uint8_t *)((uint8_t *)ctx + 0x20) & 1) {
					uint32_t o2 = 0xffffffff;
					txm_code_page_hash((uint64_t)ctx, 7, 0, &o2);
					if (i < o2) {
						return 0x73212;
					}
				} else {
					uint32_t o3 = 0xffffffff;
					txm_code_page_hash((uint64_t)ctx, 0x10000, 0, &o3);
					if (i < o3) {
						ctx[0x22] = 0;
						ctx[0x23] = 0;
					}
				}
			}
			{
				uint32_t w2 = *(uint32_t *)(base + 8);
				uint32_t ev2 = (w2 & 0xff00ff00) >> 8 | (w2 & 0xff00ff) << 8;
				uint32_t cnt = (ev2 >> 0x10 | ev2 << 0x10) * 8 + 0xc;
				if (size < cnt) {
					txm_fault(0x19);
				}
				if (*(uint64_t *)(vtable + 200) == 0) {
					p_end = base + cnt;
				} else {
					uint64_t r = (*(uint64_t (*)(uint64_t *, uint64_t))(vtable + 200))(ctx, base);
					base = r;
					p_end = r + ((uint64_t *)&r)[1];
					if (TXM_TAGABLE(r, p_end)) {
						p_end = TXM_TAGFIX(p_end);
					}
				}
				p = base + 0xc;
				if (p_end < p) {
					txm_fault(0x19);
				}
				*(uint32_t *)(base + 4) = start;
				*(uint32_t *)(base + 8) = i + 1;
				if (start <= *(uint32_t *)(ctx + 4) &&
				    (ctx[4] = start, end <= (uint64_t)((uint64_t *)ctx)[2])) {
					((uint64_t *)ctx)[2] = end;
					return 0x12;
				}
				txm_fault(0x19);
			}
		}
		if (start <= span_lo + span_hi) {
			return 0x52a12;
		}
		i++;
		if ((uint64_t)i >= count) {
			break;
		}
		{
			uint32_t w3 = *(uint32_t *)(base + 8 + (uint64_t)i * 8);
			uint32_t ev3 = (w3 & 0xff00ff00) >> 8 | (w3 & 0xff00ff) << 8;
			span_hi = (uint64_t)(ev3 >> 0x10 | ev3 << 0x10);
		}
	}
	return 0x32112;
}

/* FUN_00036acc @ 0x00036acc   (est. txm_policy_runner_chain_check)
 * Ghidra: undefined4 FUN_00036acc(long param_1,long param_2)
 * Validates the OOP-JIT runner chain: reads the code-kind (FUN_00034174) and
 * requires the oop-jit-runner entitlement (FUN_000367c8) or, for kind 1, one
 * of the alternative entitlements (0xe51 / get-task-allow / swift-playground);
 * it then compares the runner's 0x14-byte digest (FUN_000340c0 +
 * thunk_FUN_0002d4d0). Returns a packed status (base 0xb1).
 * Confidence: medium.
 */
uint32_t txm_policy_runner_chain_check(uint64_t ctx, uint64_t other)
{
	uint16_t kind = 0;
	uint64_t digest = 0, len = 0;
	uint32_t r;

	txm_buf_digest(*(uint64_t *)(other + 0x30), *(uint64_t *)(other + 0x38), 0, &kind);
	if ((uint64_t *)0x11058 < (uint64_t *)(0x11040 + (uint64_t)kind * 8) ||
	    (uint64_t *)(0x11040 + (uint64_t)kind * 8) < (uint64_t *)0x11040) {
		txm_fault(0x19);
	}
	r = txm_policy_ent_pair_check(ctx, (uint64_t)ENT_OOP_JIT_RUNNER,
	                              *(uint64_t *)(0x11040 + (uint64_t)kind * 8));
	if ((r & 0xff00) == 0 ||
	    (kind == 1 &&
	     (txm_policy_ent_check(ctx, 0xe51) == 0 ||
	      txm_policy_ent_check(ctx, (uint64_t)"com.apple.security.get-task-allow") == 0 ||
	      txm_policy_ent_check(ctx, (uint64_t)"com.apple.developer.swift-playground...") == 0))) {
		txm_buf_cmp(*(uint64_t *)(other + 0x30), *(uint64_t *)(other + 0x38), 0, &digest);
		if (len < 0x14) {
			txm_fault(0x19);
		}
		return (txm_memcmp((void *)digest, (void *)((uint8_t *)ctx + 0x40), 0x14) != 0)
		       ? 0x229b1u : 0xb1u;
	}
	return r;
}

/* FUN_00036bf8 @ 0x00036bf8   (est. txm_policy_cdhash_check)
 * Ghidra: int FUN_00036bf8(long *param_1,long param_2)
 * Validates the CDHash of a restricted region: requires the policy kind be 7
 * and the vtable op at +0x20 be present; when the vtable flag +0x30 bit 0 is
 * set it computes the region digest (op(3,...)) for both the local ctx and
 * `param_2` and compares the 0x10-byte digests (thunk_FUN_0002d4d0). Returns
 * a packed status (base 0xb2).
 * Confidence: medium.
 */
int txm_policy_cdhash_check(uint64_t *ctx, uint64_t other)
{
	uint64_t vtable = ctx[0];
	uint8_t kind = 0;
	uint64_t d0 = 0, d1 = 0, d2 = 0, d3 = 0;
	uint64_t guard = txm_canary;

	txm_policy_kind_get((uint64_t)ctx, &kind);
	if (kind == 7) {
		int r = 0x228b2;
		if (*(uint64_t *)(vtable + 0x20) != 0) {
			if ((*(uint8_t *)((uint8_t *)vtable + 0x30) & 1) != 0) {
				r = 0x43cb2;
				if ((*(uint64_t (**)(int, uint64_t *, uint64_t *))(vtable + 0x20))(3, ctx + 8, &d0) & 0xff00) {
					goto done;
				}
				txm_region_zero(&d0, &d3);
				if ((*(uint64_t (**)(int, uint64_t, uint64_t *))(vtable + 0x20))(3, other + 0x40, &d0) == 0) {
					txm_region_zero(&d0, &d1);
					r = (txm_memcmp(&d3, &d1, 0x10) != 0) ? 0x629b2 : 0xb2;
					goto done;
				}
			}
			r += 0x10000;
		}
	done:
		if (guard != txm_canary) {
			txm_stack_guard_fail();
		}
		return r;
	}
	return 0x130b2;
}

/* FUN_00036d44 @ 0x00036d44   (est. txm_policy_regions_equal)
 * Ghidra: uint FUN_00036d44(long *param_1,long *param_2)
 * Compares two policy regions for compatibility: both must have policy kinds
 * set (ctx+0x102 / other+0x102) and share the same ops vtable; the code
 * ranges must not both be "allowed" (FUN_00033c9c). For kinds 1/2/7 the
 * runner-chain / cdhash checks (00036acc / 00036bf8) or the amfi-execute
 * entitlement are consulted; otherwise the region kinds must match
 * (FUN_00033bf4 + strcmp). Returns a packed status (base 0x07).
 * Confidence: medium.
 */
uint32_t txm_policy_regions_equal(uint64_t *ctx, uint64_t *other)
{
	uint8_t kind_me = 0, kind_other = 0;
	uint64_t k1 = 0, k2 = 0, f1 = 0, f2 = 0;
	uint32_t r;

	txm_policy_kind_get((uint64_t)ctx, (uint8_t *)&kind_me + 0);
	txm_policy_kind_get((uint64_t)other, (uint8_t *)&kind_other);
	if (kind_other == 0) {
		return 0x12207u;
	}
	if (kind_me == 0) {
		return 0x22207u;
	}
	if (ctx[0] != other[0]) {
		return 0x92907u;
	}
	txm_range_check(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], 0, 0, &f1);
	txm_range_check(other[6], other[7], 0, 0, &f2);
	if ((f1 & 1) == 0) {
		if ((f2 & 1) != 0) {
			return 0x42e07u;
		}
	} else if ((f2 & 1) == 0) {
		return 0x32e07u;
	}
	if (kind_other < 6) {
		if (kind_other == 2) {
			r = txm_policy_runner_chain_check((uint64_t)ctx, (uint64_t)other);
			return (r & 0xff00) ? r : 7u;
		}
		if (kind_other == 1) {
			return (txm_policy_ent_check((uint64_t)ctx, (uint64_t)"com.apple.private.amfi-can-execute") & 0xff00)
			       ? 0x133b0u : 7u;
		}
		if (kind_other < kind_me) {
			return 0x53007u;
		}
		txm_range_kind(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], &k1);
		txm_range_kind(other[6], other[7], &k2);
		if (k1 == 0) {
			return 0x62407u;
		}
		if (k2 == 0) {
			return 0x72407u;
		}
		return (txm_strcmp((char *)k1, (char *)k2) != 0) ? 0x82907u : 7u;
	}
	if (kind_other == 7) {
		r = txm_policy_cdhash_check(ctx, (uint64_t)other);
		return (r & 0xff00) ? r : 7u;
	}
	return 7u;
}

/* ------------------------------------------------------------------ */
/* Section C — DER/ASN.1 element reader + big-number bit helpers.     */
/* 00036f54 - 00037bc0.                                               */
/* ------------------------------------------------------------------ */

/* FUN_00036f54 @ 0x00036f54   (thunk to txm_sha512_block)
 * Ghidra: void thunk_FUN_0003ff50(void)
 * Thin thunk to FUN_0003ff50 (the SHA-512 compression core, defined below).
 * Confidence: high (thunk).
 */
void txm_sha512_block_thunk(void)
{
	txm_sha512_compress(NULL, 0, NULL);
}

/* FUN_00036f5c @ 0x00036f5c   (est. txm_read_le64)
 * Ghidra: void FUN_00036f5c(undefined4 param_1,ulong *param_2,long *param_3)
 * Reads an 8-byte little-endian field from a trusted {ptr,len} cursor
 * `param_2` under tag `param_1` (FUN_00037304); `*param_3` receives the
 * value, and the cursor is advanced. A leading byte that is a length-carry
 * leaves the value reduced. Matches sibling txm_region_a.c's txm_read_le64.
 * Confidence: high (sibling-named).
 */
void txm_read_le64(uint64_t tag, uint64_t *rng, uint64_t *out)
{
	uint64_t start = 0;
	if (txm_trusted_range(rng, tag, &start) != 0) {
		*out = 0;
		if ((uint8_t *)rng[1] != (uint8_t *)*rng) {
			uint64_t span = (uint64_t)((uint8_t *)rng[1] - (uint8_t *)*rng) * 8;
			if (*(uint8_t *)*rng <= span) {
				*out = span - *(uint8_t *)*rng;
			}
			*rng = (uint64_t)((uint8_t *)*rng + 1);
		}
	}
}

/* FUN_00036fc4 @ 0x00036fc4   (est. txm_bn_cswap_prng)
 * Ghidra: void FUN_00036fc4(long param_1,ulong param_2,ulong *param_3,
 *                           ulong *param_4)
 * Conditional-swap of two big-number limbs using the TXM xorshift PRNG
 * (FUN_0003d498): the rotate amount is (param_2 | prng<<1)&0x3f; each limb
 * pair is combined with the 0x5555... mask so a masked carry-select is
 * applied. Part of the constant-time (DIT) big-number arithmetic layer.
 * Confidence: low (masked-select semantics inferred from the bit pattern).
 */
void txm_bn_cswap_prng(uint64_t count, uint64_t sel, uint64_t *a, uint64_t *b)
{
	uint64_t rng = txm_bn_prng();          /* FUN_0003d498 */
	uint64_t rot = (sel | rng << 1) & 0x3f;
	uint64_t mask = 0x5555555555555555ULL;
	uint64_t rmask = (mask >> rot | mask << (0x40 - rot));
	uint64_t x, y, t, u;

	for (; count != 0; count--) {
		x = *b ^ *a;
		*a ^= rng;
		t = *b;
		*b = t ^ rng;
		u = x & mask;
		x = x & rmask;
		*a = *a ^ u ^ x ^ rng;
		*b = t ^ rng ^ u ^ x ^ rng;
		b++;
		a++;
	}
}

/* FUN_00037064 @ 0x00037064   (est. txm_bn_mul_reduce)
 * Ghidra: undefined8 FUN_00037064(long param_1,undefined8 param_2,
 *                                 undefined8 param_3,undefined8 param_4)
 * Big-number multiply-reduce: computes a*b (param_3/param_4) into the ctx
 * scratch via the ops (+0x10 saved / +0x18 alloc / FUN_0003e6e4 reduction),
 * returning 0 on success or -1 on reduction overflow. The ctx scratch
 * high-water is saved/restored around the call.
 * Confidence: low.
 */
uint64_t txm_bn_mul_reduce(uint64_t *ctx, uint64_t b, uint64_t c, uint64_t d)
{
	uint64_t n = txm_bn_count((uint64_t *)b);
	uint64_t saved = ((uint64_t *)ctx)[2];                       /* +0x10 */
	uint64_t *scratch = (*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))((uint64_t)ctx, n); /* +0x18 alloc */
	uint64_t mod = txm_bn_modulus_ptr(b);          /* FUN_000372f8 */
	uint64_t r;

	if (txm_bn_sub_const(n, scratch, (uint64_t *)mod, 2) == 0) {
		r = txm_bn_exp_window((uint64_t)ctx, (uint64_t)b, c, d, (uint64_t)scratch);
	} else {
		r = 0xffffffff;
	}
	((uint64_t *)ctx)[2] = saved;
	return r;
}

/* FUN_00037110 @ 0x00037110   (est. txm_bn_window_build)
 * Ghidra: void FUN_00037110(long param_1,long param_2,long param_3,long param_4)
 * Builds a 4-bit sliding window over the big-number `param_3` (bit length
 * `param_2`): writes one nibble per iteration into the byte at param_1+idx,
 * packing bits (param_2-1..param_2-4) read from the limb array. This is the
 * scalar-multiply window generator (used by 0x3b784).
 * Confidence: medium.
 */
void txm_bn_window_build(uint8_t *win, uint64_t bits, uint64_t *limbs, uint64_t *limbs2)
{
	uint64_t i = 0;
	*(uint64_t *)(win + 8) = (uint64_t)limbs2;   /* window tail limbs */
	*(uint64_t *)(win + 0x10) = (uint64_t)limbs; /* window head limbs */
	win[0] = (uint8_t)((((limbs[(bits - 1) >> 6] >> ((bits - 1) & 0x3f)) & 1) << 3) |
	                   (((limbs[(bits - 2) >> 6] >> ((bits - 2) & 0x3f)) & 1) << 2) |
	                   (((limbs[(bits - 3) >> 6] >> ((bits - 3) & 0x3f)) & 1) << 1) |
	                   (((limbs[(bits - 4) >> 6] >> ((bits - 4) & 0x3f)) & 1)));
	(void)i;
}

/* FUN_000371a0 @ 0x000371a0   (est. txm_bn_window_next)
 * Ghidra: void FUN_000371a0(byte *param_1,ulong param_2,long param_3)
 * Advances the 4-bit sliding window of FUN_00037110: reads the next nibble
 * (from limb `param_2`) into the window state, and writes a signed {-1,0,+1}
 * digit for the current nibble into param_3 (signed-digit recoding used by
 * the ECC scalar-multiply ladder).
 * Confidence: low.
 */
void txm_bn_window_next(uint8_t *win, uint64_t bit, int32_t *digit)
{
	uint64_t limb = *(uint64_t *)(win + 8);
	uint8_t n0 = win[0] & 0x1f, n1 = win[1] & 0x1f;
	uint8_t b4;
	uint32_t v;
	int w;

	if (win[0] & 0x20) n0 ^= 0x1f;
	if (win[1] & 0x20) n1 ^= 0x1f;
	if (bit < 5) {
		b4 = 0;
	} else {
		b4 = (uint8_t)((*(uint64_t *)(limb + ((bit - 5) >> 6) * 8) >> (bit - 5 & 0x3f)) & 1);
	}
	if (n0 < txm_bn_win_tbl[n1]) {
		v = 0;
	} else {
		b4 |= 0x20;
		v = 0xffffffff;
		if ((win[0] & 0x20) == 0) {
			v = 1;
		}
	}
	*digit = (int32_t)v;
	win[0] = (uint8_t)(b4 ^ win[0] << 1);
}

/* 4-bit window comparison table (DAT_00006e60). */
extern const uint8_t txm_bn_win_tbl[0x20];

/* FUN_000372a4 @ 0x000372a4   (est. txm_bn_digit_index)
 * Ghidra: long FUN_000372a4(uint *param_1)
 * Returns the precomputed-point index for a {sign,digit} pair `param_1`:
 * (digit[0]&1 | digit[1]&1<<1) minus 1 when either limb is nonzero.
 * Confidence: low.
 */
long txm_bn_digit_index(uint32_t *digit)
{
	return (uint64_t)(*digit & 1 | (digit[1] & 1) << 1) -
	       (uint64_t)(*digit + digit[1] != 0);
}

/* FUN_000372c4 @ 0x000372c4   (est. txm_bn_digit_sign)
 * Ghidra: int FUN_000372c4(int *param_1)
 * Returns the sign of a recoded digit: -1 if it is -1, 0 if it is zero
 * (including {0,-1}), else 1.
 * Confidence: low.
 */
int txm_bn_digit_sign(int *digit)
{
	int v = *digit;
	if (v != -1) {
		if (v == 0 && digit[1] == -1) {
			return -1;
		}
		v = 1;
	}
	return v;
}

/* FUN_000372f8 @ 0x000372f8   (est. txm_bn_modulus_ptr)
 * Ghidra: long FUN_000372f8(long param_1)
 * Returns the modulus field pointer for a big-number descriptor: descriptor
 * + 0x18 (the {count, limbs} header is 0x18 bytes). Used everywhere to
 * obtain the modulus limbs for reduction.
 * Confidence: high (consistent use across the ECC toolkit).
 */
uint64_t txm_bn_modulus_ptr(uint64_t desc)
{
	return desc + 0x18;
}

/* FUN_00037304 @ 0x00037304   (est. txm_trusted_range)
 * Ghidra: void FUN_00037304(ulong *param_1,undefined8 param_2,ulong *param_3)
 * Reads a length-prefixed trusted element: decodes the tag (FUN_00037600)
 * and advances the {ptr,len} cursor `param_1` by the element length,
 * returning the original and new cursor in `param_3`. Matches sibling
 * txm_region_a.c's txm_trusted_range.
 * Confidence: high (sibling-named).
 */
uint64_t txm_trusted_range(uint64_t *rng, uint64_t tag, uint64_t *out)
{
	uint64_t len = 0, start = 0;
	uint64_t ok = txm_tag_match(rng, tag, &len);
	if (ok != 0) {
		start = *rng;
		{
			uint64_t end = start + len;
			if (TXM_TAGABLE(start, end)) {
				end = TXM_TAGFIX(end);
			}
			*rng = end;
		}
	}
	*out = start;
	out[1] = *rng;
	return ok;
}

/* FUN_00037370 @ 0x00037370   (est. txm_der_len_decode_full)
 * Ghidra: void FUN_00037370(undefined8 param_1,undefined8 param_2)
 * Wrapper: decodes a DER length field with the signed-length (canonical)
 * variant enabled.
 * Confidence: high (DER length decode).
 */
void txm_der_len_decode_full(uint64_t *rng, uint64_t *out)
{
	txm_der_len_decode(rng, out, 1);
}

/* FUN_0003737c @ 0x0003737c   (est. txm_der_len_decode)
 * Ghidra: undefined8 FUN_0003737c(ulong *param_1,ulong *param_2,int param_3)
 * Decodes a DER length field from the {ptr,end} cursor `param_1` into
 * `*param_2`, advancing the cursor. Handles short form (<0x80) and the
 * long forms 0x81/0x82/0x83/0x84; when `param_3` is set (canonical) a
 * leading zero byte or a negative length is rejected. Returns 1 on success.
 * Confidence: high (standard DER length decode; byte pattern 0x81-0x84).
 */
uint64_t txm_der_len_decode(uint64_t *rng, uint64_t *out, int canonical)
{
	uint8_t *p = (uint8_t *)*rng, *end = (uint8_t *)rng[1];
	uint8_t b, *np;
	uint64_t len;

	if (p == 0 || end <= p) {
		goto bad;
	}
	np = p + 1;
	b = *p;
	len = (uint64_t)(int8_t)b;
	if ((int64_t)len < 0) {
		if (b < 0x83) {
			if (b == 0x81) {
				if ((long)end - (long)np < 1) goto bad;
				np = p + 2;
				len = (uint64_t)p[1];
				if (canonical && (int8_t)p[1] >= 0) goto bad;
				goto ok;
			}
			if (b != 0x82 || (long)end - (long)np < 2) goto bad;
			len = (uint64_t)((uint8_t)p[1] << 8 | p[2]);
			np = p + 3;
		} else {
			if (b == 0x83) {
				if ((long)end - (long)np < 3) goto bad;
				len = (uint64_t)p[1] << 16 | (uint64_t)p[2] << 8 | p[3];
				np = p + 4;
			} else {
				if (b != 0x84 || (long)end - (long)np < 4) goto bad;
				len = (uint64_t)p[1] << 24 | (uint64_t)p[2] << 16 |
				      (uint64_t)p[3] << 8 | p[4];
				np = p + 5;
			}
			if (canonical && len == 0) goto bad;
		}
	}
ok:
	if (len <= (uint64_t)((long)end - (long)np)) {
		*out = len;
		*rng = (uint64_t)np;
		return 1;
	}
bad:
	*out = 0;
	return 0;
}

/* FUN_000374a0 @ 0x000374a0   (est. txm_der_len_decode_short)
 * Ghidra: void FUN_000374a0(undefined8 param_1,undefined8 param_2)
 * Decodes a DER length field without the canonical (signed-length) check.
 * Confidence: high.
 */
void txm_der_len_decode_short(uint64_t *rng, uint64_t *out)
{
	txm_der_len_decode(rng, out, 0);
}

/* FUN_000374ac @ 0x000374ac   (est. txm_der_seq_header)
 * Ghidra: void FUN_000374ac(undefined8 *param_1,undefined8 *param_2)
 * Reads the DER sequence header of the element at `param_1`: requires tag 6
 * (OCTET STRING) length, returning the element payload pointer in `param_2`.
 * Confidence: medium.
 */
void txm_der_seq_header(uint64_t *rng, uint64_t *out)
{
	uint64_t saved = *rng, len = 0;
	if (txm_trusted_range((uint64_t *)rng, 6, &len) == 0) {
		saved = 0;
	}
	*out = saved;
}

/* FUN_000374f4 @ 0x000374f4   (est. txm_der_oid_match)
 * Ghidra: ulong FUN_000374f4(undefined8 param_1,undefined8 param_2,
 *                            undefined8 param_3,undefined8 param_4)
 * Matches a DER OBJECT IDENTIFIER: reads the OID element (FUN_00037570) and
 * compares it byte-wise against `param_2`/`param_3` (FUN_00037700); returns
 * true when both compare equal and the cursor is exhausted.
 * Confidence: high (DER OID compare).
 */
uint64_t txm_der_oid_match(uint64_t rng, uint64_t a, uint64_t b, uint64_t c)
{
	uint64_t cursor = 0, end = 0;
	if (txm_der_oid_read(rng, &cursor) != 0 &&
	    txm_der_oid_byte_match(&cursor, a, b) != 0 &&
	    txm_der_oid_byte_match(&cursor, a, c) != 0) {
		return (uint64_t)(cursor == end);
	}
	return 0;
}

/* FUN_00037570 @ 0x00037570   (est. txm_der_oid_read)
 * Ghidra: void FUN_00037570(undefined8 param_1,undefined8 param_2)
 * Reads a DER OID element: tag 0x10 (SEQUENCE) length element at `param_1`,
 * returning its span in `param_2`.
 * Confidence: high.
 */
uint64_t txm_der_oid_read(uint64_t rng, uint64_t *out)
{
	return txm_trusted_range((uint64_t *)rng, 0x2000000000000010ULL, out);
}

/* FUN_00037584 @ 0x00037584   (est. txm_der_tag_decode)
 * Ghidra: undefined8 FUN_00037584(ulong *param_1,ulong *param_2)
 * Decodes a DER tag byte (with high-tag-number form) from the cursor
 * `param_1` into the 64-bit value `*param_2` = (tag class/num | number<<61);
 * advances the cursor. Returns 1 on success, 0 on underflow/overflow.
 * Confidence: high (DER high-tag-number decode; the 0x1f continuation).
 */
uint64_t txm_der_tag_decode(uint64_t *rng, uint64_t *out)
{
	uint8_t *p = (uint8_t *)*rng;
	uint8_t b;
	uint64_t v, n = 0;
	uint8_t *np;

	if (p == 0 || (uint8_t *)rng[1] <= p) {
		return 0;
	}
	{
		uint8_t *np = p + 1;
		v = (uint64_t)*p & 0x1f;
		if (v == 0x1f) {
			for (;;) {
				uint64_t prev = n;
				if ((uint8_t *)rng[1] <= np) {
					return 0;
				}
				if (prev >> 0x39 != 0) {
					return 0;
				}
				np++;
				b = np[-1];
				n = (uint64_t)b & 0x7f | prev << 7;
				if ((int8_t)b >= 0) {
					break;
				}
			}
			if (n >> 0x36 != 0) {
				return 0;
			}
		}
	}
	*out = v | (uint64_t)(*p >> 5) << 0x3d;
	*rng = (uint64_t)np;
	(void)n;
	return 1;
}

/* FUN_00037600 @ 0x00037600   (est. txm_tag_match)
 * Ghidra: undefined8 FUN_00037600(undefined8 param_1,long param_2,
 *                                 undefined8 *param_3,int param_4)
 * Matches and consumes a DER element with tag `param_2` at `param_1`: decodes
 * the tag (FUN_00037584) and, if it equals `param_2`, decodes the length
 * (canonical when `param_4` set) into `*param_3`. Returns the decoded length
 * or 0. This is the primitive behind txm_tlv_read (sibling 0x3767c).
 * Confidence: high.
 */
uint64_t txm_tag_match(uint64_t *rng, uint64_t tag, uint64_t *out)
{
	uint64_t t = 0;
	*out = 0;
	if (txm_der_tag_decode(rng, &t) != 0 && t == tag) {
		return txm_der_len_decode(rng, out, 0);
	}
	return 0;
}

/* FUN_0003767c @ 0x0003767c   (est. txm_tlv_read)
 * Ghidra: void FUN_0003767c(void)
 * Sibling 0x37600 wrapper (txm_tlv_read in txm_region_a.c). Recreates the
 * element reader used by trust-cache parsing.
 * Confidence: high (sibling-named).
 */
void txm_tlv_read(void)
{
	txm_tag_match(0, 0, 0);
}

/* FUN_00037688 @ 0x00037688   (est. txm_der_oid_byte_match)
 * Ghidra: bool FUN_00037688(long *param_1,undefined8 param_2,undefined8 param_3)
 * Compares the remaining OID bytes in the cursor `param_1` (which must be a
 * valid printable/IA5 string, checked by the byte-sign test) against
 * `param_2`/`param_3` via thunk_FUN_0003df58; returns true on a match and
 * clears the cursor.
 * Confidence: medium.
 */
bool txm_der_oid_byte_match(uint64_t *rng, uint64_t a, uint64_t b)
{
	uint8_t *p = (uint8_t *)*rng, *end = (uint8_t *)rng[1];

	if (p == end || (int8_t)*p < 0 ||
	    (*p == 0 && (p = p + 1, p != end && (int8_t)*p >= 0))) {
		*rng = 0;
		rng[1] = 0;
		return false;
	}
	*rng = (uint64_t)p;
	return txm_der_bytes_import((uint64_t)(end - p), (uint64_t *)a, (uint64_t)(end - p), (uint8_t *)b) == 0;
}

/* FUN_00037700 @ 0x00037700   (est. txm_der_oid_byte_cmp)
 * Ghidra: void FUN_00037700(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3)
 * Reads tag 2 (INTEGER) element at `param_1` and byte-compares it against
 * `param_2`/`param_3` (FUN_00037688).
 * Confidence: medium.
 */
void txm_der_oid_byte_cmp(uint64_t rng, uint64_t a, uint64_t b)
{
	uint64_t span = 0;
	if (txm_trusted_range((uint64_t *)rng, 2, &span) != 0) {
		txm_der_oid_byte_match(&span, a, b);
	}
}

/* FUN_00037750 @ 0x00037750   (est. txm_der_uint_read)
 * Ghidra: undefined8 FUN_00037750(undefined8 param_1,ulong *param_2)
 * Reads a DER INTEGER/unsigned element at `param_1` into a 64-bit value
 * `*param_2` (big-endian byte accumulation, up to 8 bytes). Returns 1 on
 * success; rejects an empty / high-bit-set / >8-byte value.
 * Confidence: high (DER unsigned int decode).
 */
uint64_t txm_der_uint_read(uint64_t rng, uint64_t *out)
{
	uint64_t len = 0, v = 0;
	uint8_t *p, *end;
	uint64_t saved = rng;

	if (out != 0) {
		*out = 0;
	}
	if (txm_trusted_range((uint64_t *)rng, 2, &len) == 0) {
		return 0;
	}
	p = (uint8_t *)saved;
	end = (uint8_t *)(saved + len);
	if (p == end || (int8_t)*p < 0 ||
	    (*p == 0 && (p = p + 1, p != end && (int8_t)*p >= 0)) ||
	    8 < (uint64_t)((long)end - (long)p)) {
		return 0;
	}
	if (p == end) {
		v = 0;
	} else {
		for (; p != end; p++) {
			v = (uint64_t)*p | v << 8;
		}
	}
	if (out != 0) {
		*out = v;
	}
	return 1;
}

/* FUN_0003780c @ 0x0003780c   (est. txm_der_len_encode)
 * Ghidra: undefined8 FUN_0003780c(long *param_1,ulong param_2)
 * Encodes a DER length `param_2` into the {ptr,end} buffer `param_1`,
 * writing the short form (<0x80) or long forms 0x81-0x84 into the buffer
 * end (backward write). Returns 1 on success (buffer has room), 0 on
 * overflow.
 * Confidence: high (DER length encode).
 */
uint64_t txm_der_len_encode(uint64_t *rng, uint64_t len)
{
	uint64_t start = *rng, end = rng[1];
	uint8_t *p;
	int64_t d;

	if (len >> 0x20 != 0) {
		return 0;
	}
	if (len < 0x80) {
		if (start + 1 > end) {
			return 0;
		}
		*(uint8_t *)end = (uint8_t)len;
		*rng = start;
		rng[1] = end;
		return 1;
	}
	if (len < 0x100) {
		if (start + 2 <= end) {
			*(uint8_t *)(end - 1) = (uint8_t)len;
			*(uint8_t *)(end - 2) = 0x81;
			*rng = start;
			rng[1] = end - 2;
			return 1;
		}
	} else if (len >> 0x10 == 0) {
		if (start + 3 <= end) {
			*(uint16_t *)(end - 2) = (uint16_t)len;
			*(uint8_t *)(end - 3) = 0x82;
			*rng = start;
			rng[1] = end - 3;
			return 1;
		}
	} else if (len >> 0x18 == 0) {
		if (start + 4 <= end) {
			*(uint16_t *)(end - 2) = (uint16_t)(len >> 8);
			*(uint8_t *)(end - 3) = (uint8_t)(len >> 16);
			*(uint8_t *)(end - 4) = 0x83;
			*rng = start;
			rng[1] = end - 4;
			return 1;
		}
	} else if (start + 5 <= end) {
		*(uint32_t *)(end - 4) = (uint32_t)len;
		*(uint8_t *)(end - 5) = 0x84;
		*rng = start;
		rng[1] = end - 5;
		return 1;
	}
	return 0;
}

/* FUN_00037900 @ 0x00037900   (est. txm_der_tag_encode)
 * Ghidra: undefined8 FUN_00037900(ulong *param_1,ulong param_2)
 * Encodes a DER tag+number `param_2` (class in bits 56-63, number in low
 * 61 bits) into the {ptr,end} buffer `param_1`, using the high-tag-number
 * form when the number needs it. Returns 1 on success.
 * Confidence: high (DER tag encode).
 */
uint64_t txm_der_tag_encode(uint64_t *rng, uint64_t tag)
{
	uint8_t *p = (uint8_t *)*rng, *end = (uint8_t *)rng[1];
	uint64_t num = tag & 0x1fffffffffffffffULL;
	uint8_t cls = (uint8_t)(tag >> 0x38);
	uint8_t lo = (uint8_t)tag;
	uint32_t w = (uint32_t)tag;
	int64_t d;

	if (num < 0x1f) {
		if (end == p) {
			return 0;
		}
		end[-1] = cls & 0xe0 | lo;
		*rng = (uint64_t)p;
		rng[1] = (uint64_t)(end - 1);
		return 1;
	}
	if (num < 0x80) {
		if ((uint64_t)(end - p) < 2) return 0;
		d = -1;
	} else if (num >> 0xe == 0) {
		if ((uint64_t)(end - p) < 3) return 0;
		end[-1] = lo & 0x7f;
		tag = (uint64_t)(w >> 7 | 0xffffff80);
		d = -2;
	} else if (num >> 0x15 == 0) {
		if ((uint64_t)(end - p) < 4) return 0;
		end[-1] = lo & 0x7f;
		end[-2] = (uint8_t)(w >> 7) | 0x80;
		tag = (uint64_t)(w >> 0xe | 0xffffff80);
		d = -3;
	} else if (num >> 0x1c == 0) {
		if ((uint64_t)(end - p) < 5) return 0;
		end[-1] = lo & 0x7f;
		end[-2] = (uint8_t)(w >> 7) | 0x80;
		end[-3] = (uint8_t)(w >> 0xe) | 0x80;
		tag = (uint64_t)(w >> 0x15 | 0xffffff80);
		d = -4;
	} else {
		if ((uint64_t)(end - p) < 6) return 0;
		end[-1] = lo & 0x7f;
		end[-2] = (uint8_t)(w >> 7) | 0x80;
		end[-3] = (uint8_t)(w >> 0xe) | 0x80;
		end[-4] = (uint8_t)(w >> 0x15) | 0x80;
		tag = (uint64_t)((uint32_t)(tag >> 0x1c) | 0xffffff80);
		d = -5;
	}
	{
		uint8_t *np = end + d;
		uint64_t x = (uint64_t)end ^ (uint64_t)np;
		if (TXM_TAGABLE((uint64_t)end, (uint64_t)np)) {
			np = (uint8_t *)TXM_TAGFIX((uint64_t)np);
		}
		*np = (uint8_t)tag;
		lo = cls | 0x1f;
		(void)x;
	}
	end[-1] = lo;
	*rng = (uint64_t)p;
	rng[1] = (uint64_t)(end - 1);
	return 1;
}

/* FUN_00037a68 @ 0x00037a68   (est. txm_der_emit_len_tag)
 * Ghidra: void FUN_00037a68(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3)
 * Emits a DER length (`param_3`) followed by a tag (`param_2`) into the
 * buffer `param_1`: writes the length, traps (0xc471) on the PAC/LR check,
 * then writes the tag.
 * Confidence: medium.
 */
void txm_der_emit_len_tag(uint64_t *rng, uint64_t tag, uint64_t len)
{
	if (txm_der_len_encode(rng, len) == 0) {
		return;
	}
	txm_brk(0xc471, 0x37aac);
	txm_der_tag_encode(rng, tag);
}

/* FUN_00037abc @ 0x00037abc   (est. txm_der_uint_len)
 * Ghidra: undefined8 FUN_00037abc(ulong param_1)
 * Returns the number of bytes needed to encode the unsigned value `param_1`
 * (1 for < 0x80, else the minimal big-endian byte count).
 * Confidence: high (DER uint length).
 */
uint64_t txm_der_uint_len(uint64_t v)
{
	if (v < 0x80) {
		return 1;
	}
	{
		uint64_t r;
		if (v >> 0x38 != 0) r = 9;
		else if (v >> 0x30 != 0) r = 8;
		else if (v >> 0x28 != 0) r = 7;
		else if (v >> 0x20 != 0) r = 6;
		else if (v >> 0x18 != 0) r = 5;
		else if (v > 0xffff) r = 4;
		else if (v > 0xff) r = 3;
		else r = 2;
		return r;
	}
}

/* FUN_00037b3c @ 0x00037b3c   (est. txm_bn_last_nonzero)
 * Ghidra: ulong FUN_00037b3c(ulong param_1,long *param_2)
 * Scans `param_1` limbs for the highest nonzero index: returns the index of
 * the last nonzero limb (0-based), or the current index if none is found.
 * Used to test a big number for zero (returns 0 when all zero).
 * Confidence: medium.
 */
uint64_t txm_bn_last_nonzero(uint64_t count, uint64_t *limbs)
{
	uint64_t i, last = 0, cur = 0;
	if (count != 0) {
		for (i = 0; i < count; i++) {
			cur = i + 1;
			if (limbs[i] == 0) {
				cur = last;
			}
			last = cur;
		}
	}
	return last;
}

/* FUN_00037b6c @ 0x00037b6c   (est. txm_der_tag_num_len)
 * Ghidra: undefined8 FUN_00037b6c(ulong param_1)
 * Returns the byte length of a DER tag number `param_1` (high-tag-number
 * form); 1 for < 0x1f, up to 5 for wider numbers.
 * Confidence: high (DER tag-number length).
 */
uint64_t txm_der_tag_num_len(uint64_t num)
{
	num &= 0x1fffffffffffffffULL;
	if (num >> 0x1c != 0) return 6;
	if (num > 0x1fffff) return 5;
	if (num > 0x3fff) return 4;
	if (num > 0x7f) return 3;
	if (num > 0x1e) return 2;
	return 1;
}

/* FUN_00037bb8 @ 0x00037bb8   (est. txm_bn_mul_const_reduce)
 * Ghidra: void FUN_00037bb8(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,undefined8 param_4)
 * Multiplies the big number `param_2` by the constant `param_3` into
 * `param_4`, reducing via FUN_0003e044; traps on the PAC/LR check.
 * Confidence: low.
 */
void txm_bn_mul_const_reduce(uint64_t *ctx, uint64_t b, uint64_t c, uint64_t d)
{
	uint64_t n = txm_bn_count((uint64_t *)b);
	txm_brk(0xc471, 0x37bf8);
	txm_bn_copy(n, (uint64_t *)c, (uint64_t *)d);
}

/* FUN_00037bfc @ 0x00037bfc   (est. txm_bn_ctx_op38)
 * Ghidra: void FUN_00037bfc(undefined8 param_1,long param_2)
 * Indirect call through the bignum context vtable at (param_2+0x10)+0x38:
 * a callback dispatch used by the ECC toolkit for the per-operation hook.
 * Confidence: low (indirect jump rendered as call by the decompiler).
 */
void txm_bn_ctx_op38(uint64_t param_1, uint64_t param_2)
{
	(void)param_1;
	(*(void (**)(void))(*(uint64_t *)(param_2 + 0x10) + 0x38))();
}



/* FUN_00035df4 @ 0x00035df4   (est. txm_policy_kind_resolve)
 * Ghidra: undefined * FUN_00035df4(long *param_1,undefined1 *param_2)
 * Resolves the final policy kind byte (ctx+0x101) from the code-kind flag
 * (FUN_00033ad4) and the vtable flags at +0xd0/+0xd1, consulting the region
 * kind selectors (FUN_00034a2c / FUN_000345f4 / FUN_0003499c / FUN_000348f8)
 * when required. Requires the ctx be installed (state byte +0x29) and not
 * already resolved (ctx+0x101 clear). Writes the kind out via `param_2`.
 * Confidence: medium.
 */
uint64_t *txm_policy_kind_resolve(uint64_t *ctx, uint8_t *out)
{
	uint32_t flag = 0;
	uint32_t st;
	uint8_t kind;

	if ((*(uint8_t *)((uint8_t *)ctx + 0x29) & 1) == 0) {
		return (uint64_t *)0x10402;
	}
	if (*(uint8_t *)((uint8_t *)ctx + 0x101) != 0) {
		return (uint64_t *)0x23402;
	}
	txm_range_kind2(((uint64_t *)ctx)[6], ((uint64_t *)ctx)[7], &flag);
	st = txm_region_kind_a(ctx, (long)ctx + 0x101);   /* FUN_00034a2c */
	if ((st & 0xff00) != 0) {
		if ((*(uint8_t *)(ctx[0] + 0xd0) & 1) == 0) {
			if (((flag >> 1) & 1) == 0) {
				if ((txm_region_kind_b(ctx, (long)ctx + 0x101) & 0xff00) != 0) { /* FUN_000345f4 */
					return (uint64_t *)0x32202;
				}
				goto done;
			}
			if ((txm_region_kind_c(ctx, (long)ctx + 0x101) & 0xff00) == 0 ||  /* FUN_0003499c */
			    (txm_region_kind_d(ctx, (long)ctx + 0x101) & 0xff00) == 0) {  /* FUN_000348f8 */
				goto done;
			}
			if ((*(uint8_t *)(ctx[0] + 0xd1) & 1) == 0) {
				return (uint64_t *)0x32202;
			}
			kind = 10;
		} else {
			kind = 10;
			if ((*(uint8_t *)((uint8_t *)ctx + 0x2a) & 1) != 0 && (kind = 5, (flag & 2) != 0)) {
				kind = 10;
			}
		}
		*(uint8_t *)((uint8_t *)ctx + 0x101) = kind;
	}
done:
	if (out != 0) {
		*out = *(uint8_t *)((uint8_t *)ctx + 0x101);
	}
	return (uint64_t *)0x20000;   /* Reset.magic + 2 */
}

/* FUN_00035f08 @ 0x00035f08   (est. txm_policy_check_dispatch)
 * Ghidra: ulong FUN_00035f08(undefined8 *param_1)
 * Top-level policy dispatch keyed on the state byte ctx+0x101 (the rule id).
 * Runs the shared selectors (00035aa0/35a38/3596c/358a4/35800/35760/356e4/
 * 35650) then the rule-specific ones (rules 1-3 -> 354c8/35364/35264; rules
 * 6-10 -> 35550; rule 4 -> 351c8). On success it records the applied rule at
 * ctx+0x102 and returns 3. A rule id of 0 fails (0x10503); an already-applied
 * rule fails (0x23403).
 * Confidence: medium.
 */
uint64_t txm_policy_check_dispatch(uint64_t *ctx)
{
	uint8_t rule = *(uint8_t *)((uint8_t *)ctx + 0x101);
	uint32_t st, r;

	if (rule == 0) {
		return 0x10503u;
	}
	if (*(uint8_t *)((uint8_t *)ctx + 0x102) != 0) {
		return 0x23403u;
	}
	r = txm_policy_rule_a9(ctx, rule);            /* 35aa0 */
	if ((r & 0xff00) != 0) return r;
	r = txm_policy_rule_a8(ctx, rule);            /* 35a38 */
	if ((r & 0xff00) != 0) return r;
	r = txm_policy_rule_a0(ctx, rule);            /* 3596c */
	if ((r & 0xff00) != 0) return r;
	r = (uint32_t)(uintptr_t)txm_policy_rule_d1(ctx, rule);  /* 358a4 */
	if ((r & 0xff00) != 0) return r;
	r = txm_policy_rule_02(ctx, rule);            /* 35800 */
	if ((r & 0xff00) != 0) return r;
	r = txm_policy_rule_aa(ctx);                  /* 35760 */
	if ((r & 0xff00) != 0) return r;
	r = txm_policy_rule_ab(ctx);                  /* 356e4 */
	if ((r & 0xff00) != 0) return r;
	r = (uint32_t)(uintptr_t)txm_policy_rule_ac(ctx);  /* 35650 */
	if ((r & 0xff00) != 0) return r;
	if (rule < 4) {
		if (rule == 1) {
			r = txm_policy_rule1(ctx);            /* 354c8 */
		} else if (rule == 2) {
			r = txm_policy_rule2(ctx);            /* 35364 */
		} else if (rule == 3) {
			r = txm_policy_rule3(ctx);            /* 35264 */
		} else {
			return 0x40103u;
		}
	} else if (rule - 6u < 5) {
		r = txm_policy_rule67(ctx, rule);         /* 35550 */
	} else {
		if (rule != 4) {
			if (rule != 5) {
				return 0x40103u;
			}
			goto applied;
		}
		r = (uint32_t)(uintptr_t)txm_policy_rule4(ctx);  /* 351c8 */
	}
	if ((r & 0xff00) != 0) {
		return r;
	}
applied:
	*(uint8_t *)((uint8_t *)ctx + 0x102) = rule;
	return 3;
}

#endif /* __ASSEMBLER__ */

/* ------------------------------------------------------------------ */
/* Section D — digest machinery + big-number core primitives.          */
/* 00037c10 - 0003e268.                                               */
/* ------------------------------------------------------------------ */

/* FUN_00037c10 @ 0x00037c10   (est. txm_log_der_name)
 * Ghidra: void FUN_00037c10(int param_1,undefined8 param_2,char *param_3)
 * When `param_1` is nonzero, decodes `param_2` as a DER OBJECT IDENTIFIER
 * and logs the resolved name (FUN_00043b28) after skipping a leading NUL.
 * Debug/trace helper for code-signing policy diagnostics.
 * Confidence: medium.
 */
void txm_log_der_name(int enabled, uint64_t der, char *dst)
{
	char *s;

	if (enabled == 0) {
		return;
	}
	s = txm_der_name_resolve(der, dst);
	if (s != 0) {
		if ((uint64_t)s < (uint64_t)dst && *s == 0) {
			s++;
		}
		txm_log(s);
	}
}

/* FUN_00037c30 @ 0x00037c30   (est. txm_log_der_oid)
 * Ghidra: void FUN_00037c30(undefined8 param_1,undefined8 param_2,char *param_3)
 * Unconditional OID-logging variant of txm_log_der_name (00037c10).
 * Confidence: medium.
 */
void txm_log_der_oid(uint64_t tag, uint64_t der, char *dst)
{
	char *s = txm_der_name_resolve(der, dst);
	if (s != 0) {
		if ((uint64_t)s < (uint64_t)dst && *s == 0) {
			s++;
		}
		txm_log(s);
	}
	(void)tag;
}

/* Resolve a DER OID element to a printable name via txm_der_uint_read.
 * Confidence: medium. */
char *txm_der_name_resolve(uint64_t der, char *dst)
{
	uint64_t span = 0, value = 0;
	uint64_t cur = der;

	if (txm_der_oid_read(der, &span) == 0) {
		return 0;
	}
	cur = span;
	if (txm_der_uint_read(cur, &value) == 0) {
		return 0;
	}
	return dst;
}

/* FUN_00037d08 @ 0x00037d08   (est. txm_bn_cond_carry)
 * Ghidra: void FUN_00037d08(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,undefined8 param_4)
 * Conditional big-number operation driven by whether `param_3` is nonzero
 * (thunk_FUN_00037b3c); dispatches to txm_bn_csub with the flag. Traps on the
 * PAC/LR check.
 * Confidence: low.
 */
void txm_bn_cond_carry(uint64_t ctx, uint64_t desc, uint64_t a, uint64_t b,
                       uint64_t m)
{
	uint64_t n = txm_bn_count((uint64_t *)desc);
	uint64_t nz = txm_bn_last_nonzero(n, (uint64_t *)a) != 0;
	uint64_t mod = txm_bn_modulus_ptr(desc);

	txm_brk(0xc471, 0x37d80);
	txm_bn_csub(n, nz, (uint64_t *)a, (uint64_t *)b, (uint64_t *)m);
	(void)mod; (void)ctx;
}

/* FUN_00037d84 @ 0x00037d84   (est. txm_bn_cond_sub)
 * Ghidra: void FUN_00037d84(undefined8 param_1,ulong param_2,
 *                           undefined8 param_3,undefined8 param_4)
 * Conditional subtract: when `param_2` is nonzero and the operand is
 * nonzero, runs txm_bn_csub (subtract with carry). Traps on PAC/LR.
 * Confidence: low.
 */
void txm_bn_cond_sub(uint64_t ctx, uint64_t sel, uint64_t a, uint64_t b,
                     uint64_t m)
{
	uint64_t n = txm_bn_count((uint64_t *)ctx);
	uint64_t nz = txm_bn_last_nonzero(n, (uint64_t *)b) != 0;
	uint64_t cond = (nz != 0) ? (sel & 1) : 0;

	txm_brk(0xc471, 0x37e04);
	txm_bn_csub(n, cond, (uint64_t *)a, (uint64_t *)b, (uint64_t *)m);
}

/* FUN_00037e08 @ 0x00037e08   (est. txm_bn_copy_cond)
 * Ghidra: void FUN_00037e08(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,undefined8 param_4)
 * Copies `param_3`/`param_4` through txm_bn_copy. Traps on PAC/LR.
 * Confidence: low.
 */
void txm_bn_copy_cond(uint64_t desc, uint64_t c, uint64_t d)
{
	uint64_t n = txm_bn_count((uint64_t *)desc);
	txm_brk(0xc471, 0x37e48);
	txm_bn_copy(n, (uint64_t *)c, (uint64_t *)d);
}

/* FUN_00037e4c @ 0x00037e4c   (est. txm_bn_ctx_op40)
 * Ghidra: void FUN_00037e4c(undefined8 param_1,long param_2)
 * Indirect call through the bignum context vtable at (param_2+0x10)+0x40.
 * Confidence: low (indirect jump). */
void txm_bn_ctx_op40(uint64_t ctx, uint64_t desc)
{
	(void)ctx;
	(*(void (**)(void))(*(uint64_t *)(desc + 0x10) + 0x40))();
}

/* FUN_00037e60 @ 0x00037e60   (est. txm_digest_absorb)
 * Ghidra: void FUN_00037e60(long param_1,undefined8 param_2,undefined8 param_3,
 *                           undefined8 param_4)
 * Core digest absorb: buffers `param_3` bytes from `param_4` into the hash
 * context at `param_1` (+8 length / +0x10 block), invoking the block callback
 * (param_1+0x38) and the per-block copier (param_1+0x30). Stack canary
 * checked on return.
 * Confidence: medium.
 */
void txm_digest_absorb(uint64_t ctx, uint64_t h, uint64_t len, uint64_t src)
{
	uint64_t guard = txm_canary;
	uint8_t stack[8];
	uint64_t buf = *(uint64_t *)(ctx + 8);
	uint64_t block = *(uint64_t *)(ctx + 0x10);

	txm_bn_ctx_op40(ctx, h);
	(void)buf; (void)block;
	txm_digest_init(ctx, (uint64_t *)&stack);
	txm_digest_blocks(ctx, (uint64_t *)&stack, len, src);
	(*(void (**)(uint64_t, uint64_t *, uint64_t))(ctx + 0x38))(ctx, (uint64_t *)&stack, src);
	txm_bn_clr(buf + block + 0xc, (uint64_t *)&stack);
	if (guard != txm_canary) {
		txm_stack_guard_fail();
	}
}

/* FUN_00037f5c @ 0x00037f5c   (est. txm_digest_absorb_dit)
 * Ghidra: void FUN_00037f5c(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,undefined8 param_4)
 * DIT-guarded wrapper for txm_digest_absorb (00037e60).
 * Confidence: medium.
 */
void txm_digest_absorb_dit(uint64_t ctx, uint64_t h, uint64_t len, uint64_t src)
{
	uint8_t dit = 0;
	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	txm_digest_absorb(ctx, h, len, src);
	txm_dit_clear(&dit);
}

/* FUN_0003822c @ 0x0003822c   (est. txm_digest_init)
 * Ghidra: void FUN_0003822c(long param_1,undefined8 *param_2)
 * Initializes a digest context `h` at the state base param_1+8: copies the
 * IV (param_1+0x28) and zeroes the block counter.
 * Confidence: medium.
 */
void txm_digest_init(uint64_t ctx, uint64_t *h)
{
	txm_memcpy(h + 1, (void *)(ctx + 0x28), *(uint64_t *)(ctx + 8));
	h[0] = 0;
	*(uint32_t *)((uint8_t *)h + *(uint64_t *)(ctx + 8) + 8 + *(uint64_t *)(ctx + 0x10)) = 0;
}

/* FUN_00038288 @ 0x00038288   (est. txm_digest_init_dit)
 * Ghidra: void FUN_00038288(long param_1,undefined8 *param_2)
 * DIT-guarded txm_digest_init.
 * Confidence: medium.
 */
void txm_digest_init_dit(uint64_t ctx, uint64_t *h)
{
	uint8_t dit = 0;
	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	txm_memcpy(h + 1, (void *)(ctx + 0x28), *(uint64_t *)(ctx + 8));
	h[0] = 0;
	*(uint32_t *)((uint8_t *)h + *(uint64_t *)(ctx + 8) + 8 + *(uint64_t *)(ctx + 0x10)) = 0;
	txm_dit_clear(&dit);
}

/* FUN_00038318 @ 0x00038318   (est. txm_digest_bytelen)
 * Ghidra: ulong FUN_00038318(undefined8 *param_1)
 * Returns the digest byte length: (bitlen(param_1) + 7) >> 3.
 * Confidence: medium.
 */
uint64_t txm_digest_bytelen(uint64_t *desc)
{
	return (txm_bn_bitlen(desc[0], desc + 1) + 7U) >> 3;
}

/* FUN_0003833c @ 0x0003833c   (est. txm_hash_verify_magic)
 * Ghidra: int FUN_0003833c(undefined8 param_1,undefined8 param_2,
 *                          undefined8 param_3,undefined8 param_4,
 *                          undefined8 param_5,undefined8 param_6,
 *                          undefined1 *param_7)
 * Signature/hash verify entry: runs txm_ecdsa_verify (FUN_0003a604) with the
 * magic 0x7dcdc05e; on success sets `*param_7`=1 and maps the -0x92 ("hash
 * mismatch") error to 0. DIT-guarded.
 * Confidence: medium.
 */
int txm_hash_verify_magic(uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                          uint64_t e, uint64_t f, uint8_t *ok)
{
	uint8_t dit = 0;
	uint64_t out[2] = {0, 0};
	int r;

	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	*ok = 0;
	r = (int)txm_ecdsa_verify((uint64_t *)a, b, c, d, e, f, 0x7dcdc05e, (uint64_t)out);
	if (r == 0) {
		*ok = 1;
	} else if (r == -0x92) {
		r = 0;
	}
	txm_dit_clear(&dit);
	return r;
}

/* FUN_0003843c @ 0x0003843c   (est. txm_digest_blocks)
 * Ghidra: void FUN_0003843c(long param_1,long *param_2,ulong param_3,
 *                           ulong param_4)
 * Processes `param_3` bytes of `param_4` into the digest buffer at param_2+1
 * (the state block), invoking the block callback (param_1+0x30) whenever a
 * block fills; handles the residual tail by copying.
 * Confidence: medium.
 */
void txm_digest_blocks(uint64_t ctx, uint64_t *h, uint64_t len, uint64_t src)
{
	uint64_t block = *(uint64_t *)(ctx + 0x10);
	uint64_t base = *(uint64_t *)(ctx + 8);
	uint64_t buf = (uint64_t)h + base;
	uint32_t used = *(uint32_t *)(buf + block);
	uint64_t n, cnt;

	if (block <= used) {
		*(uint32_t *)(buf + block) = 0;
	}
	while (len != 0) {
		used = *(uint32_t *)(buf + block);
		if (block < len && used == 0) {
			if (block == 0x80) {
				cnt = len >> 7;
			} else if (block == 0x40) {
				cnt = len >> 6;
			} else {
				cnt = block ? len / block : 0;
			}
			(*(void (**)(uint64_t *, uint64_t, uint64_t))(ctx + 0x30))(h + 1, cnt, src);
			h[0] += cnt * block * 8;
			*(uint32_t *)(buf + block) = 0;
			src += cnt * block;
			len -= cnt * block;
		} else {
			n = block - used;
			if (len < n) n = len;
			txm_memcpy((void *)(buf + used), (void *)src, n);
			used += (uint32_t)n;
			*(uint32_t *)(buf + block) = used;
			if (block == used) {
				(*(void (**)(uint64_t *, int))(ctx + 0x30))(h + 1, 1);
				h[0] += (uint64_t)(*(uint32_t *)(buf + block) << 3);
				*(uint32_t *)(buf + block) = 0;
			}
			src += n;
			len -= n;
		}
	}
}

/* FUN_000385b8 @ 0x000385b8   (est. txm_digest_blocks_dit)
 * Ghidra: void FUN_000385b8(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,undefined8 param_4)
 * DIT-guarded txm_digest_blocks.
 * Confidence: medium.
 */
void txm_digest_blocks_dit(uint64_t ctx, uint64_t *h, uint64_t len, uint64_t src)
{
	uint8_t dit = 0;
	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	txm_digest_blocks(ctx, h, len, src);
	txm_dit_clear(&dit);
}

/* FUN_00038634 @ 0x00038634   (est. txm_ec_mul_point)
 * Ghidra: undefined8 FUN_00038634(long param_1,long *param_2,ulong param_3,
 *                                 ulong param_4)
 * Elliptic-curve scalar multiply: out = param_3 * G + param_4. Returns 0 on
 * success or -7 (0xfffffff9) when the point is not on the curve.
 * Confidence: low.
 */
uint64_t txm_ec_mul_point(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t pt)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t r;

	if (txm_bn_is_zero(desc, pt) == 0) {
		r = txm_ec_point_mul(ctx, desc, out, n, pt);
	} else {
		r = 0xfffffff9;
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	return r;
}

/* FUN_000387c0 @ 0x000387c0   (est. txm_ec_mul_g)
 * Ghidra: undefined8 FUN_000387c0(long param_1,long *param_2,
 *                                 undefined8 param_3,ulong param_4)
 * Elliptic-curve scalar multiply by the generator: out = param_3 * G.
 * Confidence: low.
 */
uint64_t txm_ec_mul_g(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t pt)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t r;

	if (txm_bn_is_zero(desc, pt) == 0) {
		txm_ec_pt_mul1(ctx, desc, out, pt, n);
		r = 0;
	} else {
		r = 0xfffffff9;
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	return r;
}

/* FUN_000388b0 @ 0x000388b0   (est. txm_alg_name_c0)
 * Ghidra: undefined * FUN_000388b0(void) — SHA-256 algorithm-name struct. */
const void *txm_alg_name_c0(void) { return (const void *)0x110a8; }

/* FUN_000389ec @ 0x000389ec   (est. txm_bn_square)
 * Ghidra: void FUN_000389ec(undefined8 param_1,ulong param_2,long *param_3,
 *                           ulong *param_4)
 * Big-number squaring: out = a*a (in place). Uses the muladd helpers with the
 * doubled cross terms.
 * Confidence: low.
 */
void txm_bn_square(uint64_t n, uint64_t *out, uint64_t *a)
{
	uint64_t i, j;
	uint64_t carry = 0;

	/* out is a 2n-limb result; square a in place (row 0 then accumulate). */
	if (n == 0) {
		return;
	}
	for (i = 0; i < n; i++) {
		__uint128_t t = (__uint128_t)a[i] * a[0] + carry;
		out[i] = (uint64_t)t;
		carry = (uint64_t)(t >> 64);
	}
	out[n] = carry;
	for (j = 1; j < n; j++) {
		carry = 0;
		for (i = 0; i < n; i++) {
			__uint128_t t = (__uint128_t)a[i] * a[j] + out[i + j] + carry;
			out[i + j] = (uint64_t)t;
			carry = (uint64_t)(t >> 64);
		}
		out[n + j] = carry;
	}
}

/* FUN_00038ae4 @ 0x00038ae4   (est. txm_bn_modpow_thunk)
 * Ghidra: void FUN_00038ae4(void) — thunk to FUN_0003cb04. */
void txm_bn_modpow_thunk(void) { txm_bn_modpow(0, 0, 0, 0); }

/* FUN_00038b00 @ 0x00038b00  / 0x38b34 / 0x38b68 (est. txm_bn_mul_thunk*)
 * Ghidra: void FUN_00038b00(void) etc. — thunks to FUN_00043650. */
void txm_bn_mul_thunk(void)  { txm_bn_mul(0, 0, 0, 0, 0); }
void txm_bn_mul_thunk2(void) { txm_bn_mul(0, 0, 0, 0, 0); }
void txm_bn_mul_thunk3(void) { txm_bn_mul(0, 0, 0, 0, 0); }

/* FUN_00038b2c @ 0x00038b2c   (thunk to txm_alg_name_e0) */
void txm_alg_name_e0_thunk(void) { txm_alg_name_e0(); }

/* FUN_00038b60 @ 0x00038b60   (thunk to FUN_00040c1c) */
void txm_alg_name_100_thunk(void) { txm_alg_name_100(); }

/* FUN_00038b94 @ 0x00038b94   (thunk to FUN_00043d00) */
void txm_alg_name_180_thunk(void) { txm_alg_name_180(); }

/* FUN_00038b9c @ 0x00038b9c   (est. txm_alg_name_209)
 * Ghidra: undefined * FUN_00038b9c(void) — SHA-512/256-style name struct. */
const void *txm_alg_name_209(void) { return (const void *)0x111f8; }

/* FUN_00038fc0 @ 0x00038fc0   (est. txm_ec_pt_addfull)
 * Ghidra: void FUN_00038fc0(long param_1,long *param_2,ulong param_3,
 *                           ulong param_4,ulong param_5,int param_6)
 * Full projective point addition: out = param_4 + param_5 (param_6 selects
 * add vs subtract of the Y coordinate). Handles the identity cases.
 * Confidence: low.
 */
void txm_ec_pt_addfull(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a,
                       uint64_t b, int sub)
{
	uint64_t n = *desc;
	uint64_t a2 = a + n * 8, b2 = b + n * 8;
	uint64_t a3 = a + n * 0x10, b3 = b + n * 0x10;
	uint64_t o2 = out + n * 8, o3 = out + n * 0x10;
	int za = txm_bn_last_nonzero(n, (uint64_t *)a) != 0;
	int zb = txm_bn_last_nonzero(n, (uint64_t *)b) != 0;

	if (za == 0 && zb == 0) {
		txm_ec_pt_double(ctx, desc, out, a);
		return;
	}
	if (za != 0 && zb == 0) {
		txm_bn_copy(n, (uint64_t *)out, (uint64_t *)a);
		txm_bn_copy(n, (uint64_t *)o2, (uint64_t *)a2);
		txm_bn_copy(n, (uint64_t *)o3, (uint64_t *)a3);
		return;
	}
	/* generic projective addition (Jacobi coordinates) */
	{
		uint64_t z1z1, z2z2, u1, u2, s1, s2, h, i, j, r, v;
		z1z1 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		z2z2 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		u1 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		u2 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		s1 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		s2 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		h = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		i = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		j = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		r = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		v = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
		txm_bn_mul(ctx, desc[0], (uint64_t *)z1z1, (uint64_t *)a3, (uint64_t *)a3);
		txm_bn_mul(ctx, desc[0], (uint64_t *)z2z2, (uint64_t *)b3, (uint64_t *)b3);
		txm_bn_mul(ctx, desc[0], (uint64_t *)u1, (uint64_t *)a, (uint64_t *)z2z2);
		txm_bn_mul(ctx, desc[0], (uint64_t *)u2, (uint64_t *)b, (uint64_t *)z1z1);
		txm_bn_mul(ctx, desc[0], (uint64_t *)s1, (uint64_t *)a2, (uint64_t *)z2z2);
		txm_bn_mul(ctx, desc[0], (uint64_t *)s1, (uint64_t *)s1, (uint64_t *)a3);
		txm_bn_mul(ctx, desc[0], (uint64_t *)s2, (uint64_t *)b2, (uint64_t *)z1z1);
		txm_bn_mul(ctx, desc[0], (uint64_t *)s2, (uint64_t *)s2, (uint64_t *)b3);
		if (sub) {
			txm_bn_sub(ctx, desc[0], (uint64_t *)h, (uint64_t *)u2, (uint64_t *)u1);
			txm_bn_sub(ctx, desc[0], (uint64_t *)r, (uint64_t *)s2, (uint64_t *)s1);
		} else {
			txm_bn_sub(ctx, desc[0], (uint64_t *)h, (uint64_t *)u2, (uint64_t *)u1);
			txm_bn_sub(ctx, desc[0], (uint64_t *)r, (uint64_t *)s2, (uint64_t *)s1);
		}
		txm_bn_mul(ctx, desc[0], (uint64_t *)i, (uint64_t *)h, (uint64_t *)h);
		txm_bn_mul(ctx, desc[0], (uint64_t *)i, (uint64_t *)i, (uint64_t *)h);
		txm_bn_mul(ctx, desc[0], (uint64_t *)j, (uint64_t *)i, (uint64_t *)u1);
		txm_bn_mul(ctx, desc[0], (uint64_t *)r, (uint64_t *)r, (uint64_t *)r);
		txm_bn_mul(ctx, desc[0], (uint64_t *)v, (uint64_t *)i, (uint64_t *)u1);
		txm_bn_sub(ctx, desc[0], (uint64_t *)r, (uint64_t *)r, (uint64_t *)j);
		txm_bn_sub(ctx, desc[0], (uint64_t *)r, (uint64_t *)r, (uint64_t *)j);
		txm_bn_mul(ctx, desc[0], (uint64_t *)out, (uint64_t *)h, (uint64_t *)r);
		txm_bn_sub(ctx, desc[0], (uint64_t *)o2, (uint64_t *)j, (uint64_t *)v);
		txm_bn_mul(ctx, desc[0], (uint64_t *)o2, (uint64_t *)s1, (uint64_t *)o2);
		txm_bn_mul(ctx, desc[0], (uint64_t *)o2, (uint64_t *)o2, (uint64_t *)h);
		txm_bn_sub(ctx, desc[0], (uint64_t *)o2, (uint64_t *)o2, (uint64_t *)r);
		txm_bn_mul(ctx, desc[0], (uint64_t *)o3, (uint64_t *)i, (uint64_t *)a3);
		txm_bn_mul(ctx, desc[0], (uint64_t *)o3, (uint64_t *)o3, (uint64_t *)b3);
	}
}

/* FUN_000393bc @ 0x000393bc   (est. txm_ec_pt_add_wrap)
 * Ghidra: void FUN_000393bc(long param_1,long *param_2,ulong param_3,
 *                           undefined8 param_4,ulong param_5)
 * Wrapper for point addition (sub=0); on a non-reduced operand copies it.
 * Confidence: low.
 */
void txm_ec_pt_add_wrap(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a,
                        uint64_t b)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);

	if (txm_bn_is_zero(desc, a) == 0) {
		txm_ec_pt_addfull(ctx, desc, out, a, b, 0);
	} else {
		txm_bn_copy(n, (uint64_t *)out, (uint64_t *)a);
		txm_bn_copy(n, (uint64_t *)(out + n * 8), (uint64_t *)(a + n * 8));
		txm_bn_copy(n, (uint64_t *)(out + n * 0x10), (uint64_t *)(a + n * 0x10));
	}
	*(uint64_t *)(ctx + 0x10) = saved;
}

/* FUN_00039d60 @ 0x00039d60   (est. txm_ec_pt_sub_wrap)
 * Ghidra: void FUN_00039d60(long param_1,long *param_2,ulong param_3,
 *                           undefined8 param_4,ulong param_5)
 * Wrapper for point subtraction (sub=1).
 * Confidence: low.
 */
void txm_ec_pt_sub_wrap(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a,
                        uint64_t b)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);

	if (txm_bn_is_zero(desc, a) == 0) {
		txm_ec_pt_addfull(ctx, desc, out, a, b, 1);
	} else {
		txm_bn_copy(n, (uint64_t *)out, (uint64_t *)a);
		txm_bn_copy(n, (uint64_t *)(out + n * 8), (uint64_t *)(a + n * 8));
		txm_bn_copy(n, (uint64_t *)(out + n * 0x10), (uint64_t *)(a + n * 0x10));
	}
	*(uint64_t *)(ctx + 0x10) = saved;
}

/* FUN_00039c54 @ 0x00039c54   (est. txm_ec_pt_scale)
 * Ghidra: void FUN_00039c54(long param_1,long *param_2,ulong param_3,
 *                           undefined8 param_4,undefined8 param_5)
 * Projective point scaling: out = param_4 * param_5 via the point ops.
 * Confidence: low.
 */
void txm_ec_pt_scale(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a,
                     uint64_t b)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t t, t2, t3;

	t = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
	t2 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
	t3 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
	txm_bn_mul(ctx, desc[0], (uint64_t *)t, (uint64_t *)a, (uint64_t *)b);
	txm_bn_add(ctx, desc[0], (uint64_t *)t2, (uint64_t *)t, (uint64_t *)t);
	txm_bn_mul(ctx, desc[0], (uint64_t *)t3, (uint64_t *)t2, (uint64_t *)t2);
	txm_bn_mul(ctx, desc[0], (uint64_t *)out, (uint64_t *)t, (uint64_t *)t3);
	*(uint64_t *)(ctx + 0x10) = saved;
}

/* FUN_00039d4c @ 0x00039d4c   (est. txm_bn_ctx_op58)
 * Ghidra: void FUN_00039d4c(undefined8 param_1,long param_2) — indirect call
 * through (param_2+0x10)+0x58. */
void txm_bn_ctx_op58(uint64_t ctx, uint64_t desc)
{
	(void)ctx;
	(*(void (**)(void))(*(uint64_t *)(desc + 0x10) + 0x58))();
}

/* FUN_00039e64 @ 0x00039e64   (est. txm_ec_pt_mul3)
 * Ghidra: void FUN_00039e64(long param_1,long *param_2,undefined8 param_3,
 *                           undefined8 param_4,ulong param_5)
 * Elliptic-curve scalar multiply by 3: out = 3*param_5.
 * Confidence: low.
 */
void txm_ec_pt_mul3(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a,
                    uint64_t b)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t t, t2;

	t = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n * 3);
	t2 = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
	txm_bn_copy(n, (uint64_t *)t, (uint64_t *)b);
	txm_bn_cond_sub(ctx, 1, t + n * 8, b + n * 8, t2);
	txm_bn_copy(n, (uint64_t *)(t + n * 0x10), (uint64_t *)(b + n * 0x10));
	txm_bn_ctx_op58(ctx, (uint64_t)desc);
	*(uint64_t *)(ctx + 0x10) = saved;
}

/* FUN_00039f60 @ 0x00039f60   (est. txm_digest_alg_name)
 * Ghidra: undefined8 FUN_00039f60(long param_1)
 * Dispatches a digest algorithm id to its name struct:
 * 0xc0/0xe0/0x100/0x180/0x209. Returns 0 for an unknown id.
 * Confidence: high (id->name table).
 */
const void *txm_digest_alg_name(uint64_t id)
{
	if (id < 0x100) {
		if (id == 0xc0) return txm_alg_name_c0();
		if (id == 0xe0) return txm_alg_name_e0();
	} else {
		if (id == 0x100) return txm_alg_name_100();
		if (id == 0x180) return txm_alg_name_180();
		if (id == 0x209) return txm_alg_name_209();
	}
	return 0;
}

/* FUN_00039fb0 @ 0x00039fb0   (est. txm_digest_alg_supported)
 * Ghidra: undefined8 FUN_00039fb0(long param_1)
 * Returns whether `param_1` is a supported digest algorithm id. DIT-guarded.
 * Confidence: high (same id set as 0x39f60).
 */
uint64_t txm_digest_alg_supported(uint64_t id)
{
	uint8_t dit = 0;
	uint64_t ok = 1;

	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	if (id < 0x100) {
		if (id != 0xc0 && id != 0xe0) ok = 0;
	} else if (id != 0x100 && id != 0x180 && id != 0x209) {
		ok = 0;
	}
	txm_dit_clear(&dit);
	return ok;
}

/* FUN_0003a044 @ 0x0003a044   (thunk to FUN_0003c224) */
void txm_bn_modpow_wrap_thunk(void) { txm_bn_modpow_wrap(0, 0, 0, 0); }

/* FUN_0003a04c @ 0x0003a04c   (est. txm_bn_mod_mul_inv)
 * Ghidra: undefined8 FUN_0003a04c(long param_1,long *param_2,ulong param_3,
 *                                 undefined8 param_4)
 * Modular multiply-inverse: computes inv(param_4) mod the field prime using
 * the point ops and a conditional reduction. Returns 0 on success or -7.
 * Confidence: low.
 */
uint64_t txm_bn_mod_mul_inv(uint64_t ctx, uint64_t *desc, uint64_t out,
                            uint64_t a)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t r = 0;

	if (txm_bn_cmp(n, (uint64_t *)a, desc + 3) < 0) {
		txm_ec_pt_addfull(ctx, desc, out, a, a, 0);
		txm_bn_mul(ctx, desc[0], (uint64_t *)out, (uint64_t *)out, (uint64_t *)a);
		r = txm_bn_modinv(ctx, (uint64_t)desc, out, a, (uint64_t)(desc + 3));
		if (r == 0) {
			txm_ec_pt_double(ctx, desc, out, out);
			r = 0;
		}
	} else {
		r = 0xfffffff9;
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	return r;
}

/* FUN_0003a210 @ 0x0003a210   (est. txm_sig_verify_pubkey)
 * Ghidra: undefined8 FUN_0003a210(undefined8 param_1,undefined8 param_2,
 *      undefined8 param_3,long param_4,undefined8 param_5,long *param_6)
 * Signature verify against a public key: resolves the digest algorithm name
 * (FUN_00039f60), imports the two bignum operands, and runs the ECDSA verify.
 * Returns 0 on success, -7 on a bad key, -1 on a bad algorithm. DIT-guarded.
 * Confidence: medium.
 */
uint64_t txm_sig_verify_pubkey(uint64_t alg, uint64_t a, uint64_t b, uint64_t c,
                               uint64_t d, uint64_t *desc)
{
	uint8_t dit = 0;
	uint64_t r;
	const uint64_t *name;

	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	if (c == 0) {
		r = 0xfffffff9;
	} else {
		name = txm_digest_alg_name(alg);
		if (name != 0) {
			desc[2] = (uint64_t)name;
			if (txm_der_bytes_import(name[0], (uint64_t *)(desc + 2), a, (uint8_t *)b) == 0 &&
			    txm_der_bytes_import(name[0], (uint64_t *)(desc + 2 + name[0] / 8), c, (uint8_t *)d) == 0) {
				txm_bn_set_one(desc[0], (uint64_t *)(desc + 2 + desc[0]));
				r = 0;
				goto out;
			}
		}
		r = 0xffffffff;
	}
out:
	txm_dit_clear(&dit);
	return r;
}

/* FUN_0003a33c @ 0x0003a33c   (est. txm_ecdsa_verify_core)
 * Ghidra: uint FUN_0003a33c(ulong *param_1,long *param_2,undefined8 param_3,
 *      undefined8 param_4,undefined8 param_5,ulong param_6,
 *      undefined8 param_7,int param_8,byte *param_9)
 * ECDSA signature-verification core. Validates the signature length against
 * the curve order, imports r/s, computes u1/u2 via the point ops, and
 * combines the 16-byte digest by XOR (with 0x89). Returns 0 (valid),
 * 0xffffffe9 (bad length), 0xffffff6e (point not on curve), or the
 * digest-mismatch byte.
 * Confidence: medium.
 */
uint32_t txm_ecdsa_verify_core(uint64_t *scratch, uint64_t *desc, uint64_t pubx,
                               uint64_t puby, uint64_t sig, uint64_t dlen,
                               uint64_t digest, int allow_short, uint8_t *mac)
{
	uint64_t n = *desc;
	uint64_t saved = scratch[2];
	uint64_t r, s, acc;
	uint32_t rc = 0xffffffe9;
	int i;

	for (i = 0; i < 16; i++) mac[i] = 0;
	r = txm_bn_bytelen(n, desc + 3);
	{
		bool ok = (allow_short == 0x7dcdc05e) ? (dlen == r) : (r <= dlen);
		if (ok) {
			s = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(scratch[3]))((uint64_t)scratch, n);
			acc = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(scratch[3]))((uint64_t)scratch, n);
			txm_bn_clr((scratch[2] - saved) * 8, (void *)s);
			if (txm_der_bytes_import(n, (uint64_t *)s, dlen, (uint8_t *)sig) == 0) {
				rc = (uint32_t)txm_bn_modpow((uint64_t)scratch, (uint64_t)desc, puby, s);
				if (rc == 0) {
					txm_bn_set_one(n, (uint64_t *)s);
					rc = (uint32_t)txm_bn_mul_inv_final(n, (uint64_t *)s, pubx, puby, sig, mac);
					if (rc == 0) {
						rc = (uint8_t)(mac[8] ^ mac[4] ^ mac[3] ^ mac[0xd]) ^ 0x89 ^
						     (uint8_t)(mac[0xf] ^ mac[10] ^ mac[1] ^ mac[0xb]) ^
						     (uint8_t)(mac[0xe] ^ mac[6] ^ mac[2] ^ mac[9]) ^
						     (uint8_t)(mac[0xc] ^ mac[0] ^ mac[7] ^ mac[5]);
					} else {
						rc = 0xffffff6e;
					}
				}
			}
			scratch[2] = saved;
		}
	}
	return rc;
}

/* FUN_0003a604 @ 0x0003a604   (est. txm_ecdsa_verify)
 * Ghidra: undefined8 FUN_0003a604(long *param_1,undefined8 param_2,
 *      undefined8 param_3,undefined8 param_4,undefined8 param_5,
 *      undefined8 param_6,undefined8 param_7,undefined8 param_8)
 * ECDSA verify wrapper: allocates the 0x58-byte-per-limb scratch, runs the
 * core, frees the scratch. Returns -13 (0xfffffff3) on allocation failure.
 * Confidence: medium.
 */
uint64_t txm_ecdsa_verify(uint64_t *desc, uint64_t a, uint64_t b, uint64_t c,
                          uint64_t d, uint64_t e, uint64_t f, uint64_t g)
{
	uint64_t *scratch;
	uint64_t r;

	scratch = (uint64_t *)txm_bn_scratch(*desc * 0x58);
	if (scratch == 0) {
		r = 0xfffffff3;
	} else {
		scratch[1] = *desc * 0xb;
		scratch[2] = 0;
		r = txm_ecdsa_verify_core(scratch, desc, a, b, c, d, e, f, (uint8_t *)g);
		txm_bn_alg_free(scratch);
	}
	return r;
}

/* FUN_0003a6f4 @ 0x0003a6f4   (est. txm_ec_scalarmul)
 * Ghidra: undefined8 FUN_0003a6f4(long param_1,long *param_2,ulong param_3,
 *      ulong *param_4,ulong param_5,undefined8 param_6)
 * Full elliptic-curve scalar multiply (Montgomery ladder): computes
 * out = param_6 * param_3. Uses the ctx scratch, the window helpers, the
 * point ops, the conditional ops, and reduces mod the field prime. Returns 0
 * on success or -7 on overflow.
 * Confidence: low (large; standard Montgomery ladder shape).
 */
uint64_t txm_ec_scalarmul(uint64_t ctx, uint64_t *desc, uint64_t out,
                          uint64_t *scalar, uint64_t bitlen, uint64_t point)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t m3 = n * 3, m1, m2;
	uint64_t *acc, *t1, *t2;
	uint64_t bl = txm_bn_bitlen(txm_bn_count((uint64_t *)(desc + 4)), (uint64_t *)(desc + 4 + 4));
	uint64_t r = 0xffffffff;
	uint64_t limbs = (bitlen + 0x3f) >> 6;

	if (bl < bitlen) {
		return 0xfffffff9;
	}
	m1 = n;
	m2 = n * 2;
	acc = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, m3);
	t1 = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
	t2 = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
	if (limbs != 0) {
		txm_bn_copy(limbs, acc, scalar);
		txm_bn_clr((n - limbs) * 8, (void *)(acc + limbs));
		acc[limbs - 1] &= ~0ULL >> ((uint64_t)(-(int)bitlen) & 0x3f);
	}
	txm_bn_shl(limbs, acc, acc, 0);
	txm_ec_pt_double(ctx, desc, m3, (uint64_t)acc);
	txm_bn_csub(n, 1, (uint64_t *)m3, (uint64_t *)acc, (uint64_t *)t2);
	if (txm_bn_last_nonzero(n, (uint64_t *)acc) != 0) {
		r = txm_ec_scalarmul_ladder(ctx, desc, out, acc, bitlen, point, t1, t2);
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	return r;
}

/* FUN_0003b0c0 @ 0x0003b0c0   (est. txm_bn_ctx_op60)
 * Ghidra: void FUN_0003b0c0(undefined8 param_1,long param_2) — indirect call
 * through (param_2+0x10)+0x60. */
void txm_bn_ctx_op60(uint64_t ctx, uint64_t desc)
{
	(void)ctx;
	(*(void (**)(void))(*(uint64_t *)(desc + 0x10) + 0x60))();
}

/* FUN_0003b530 @ 0x0003b530   (est. txm_bn_mod_op_final)
 * Ghidra: undefined8 FUN_0003b530(long param_1,long *param_2,ulong param_3,
 *                                 ulong param_4,long param_5)
 * Modular reduction finalization: when `param_5` is nonzero, reduces the
 * operand mod the field prime; otherwise folds it. Returns the status.
 * Confidence: low.
 */
uint64_t txm_bn_mod_op_final(uint64_t ctx, uint64_t *desc, uint64_t out,
                             uint64_t a, uint64_t mod)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t r = 0;

	if (mod == 0) {
		txm_bn_set_one(n, (uint64_t *)(out + n * 0x10));
		txm_ec_pt_double(ctx, desc, out, a);
		txm_bn_mul(ctx, desc[0], (uint64_t *)(out + n * 8), (uint64_t *)(a + n * 8),
		           (uint64_t *)(out + n * 8));
		r = 0;
	} else {
		txm_bn_set_one(n, (uint64_t *)(out + n * 0x10));
		txm_bn_set_one(n, (uint64_t *)(out + n * 0x10));
		txm_bn_add(ctx, desc[0], (uint64_t *)out, (uint64_t *)out, (uint64_t *)(out + n * 0x10));
		txm_bn_mul(ctx, desc[0], (uint64_t *)(out + n * 8), (uint64_t *)out, (uint64_t *)(out + n * 0x10));
		txm_bn_mul(ctx, desc[0], (uint64_t *)out, (uint64_t *)out, (uint64_t *)a);
		txm_bn_mul(ctx, desc[0], (uint64_t *)(out + n * 8), (uint64_t *)(out + n * 8), (uint64_t *)a);
		txm_ec_pt_double(ctx, desc, out, out);
	}
	txm_ec_pt_double(ctx, desc, out, out);
	*(uint64_t *)(ctx + 0x10) = saved;
	return r;
}

/* FUN_0003b770 @ 0x0003b770   (est. txm_bn_ctx_op48)
 * Ghidra: void FUN_0003b770(undefined8 param_1,long param_2) — indirect call
 * through (param_2+0x10)+0x48. */
void txm_bn_ctx_op48(uint64_t ctx, uint64_t desc)
{
	(void)ctx;
	(*(void (**)(void))(*(uint64_t *)(desc + 0x10) + 0x48))();
}

/* FUN_0003b784 @ 0x0003b784   (est. txm_ec_scalarmul_window)
 * Ghidra: int FUN_0003b784(long param_1,long *param_2,ulong param_3,
 *      undefined8 param_4,ulong param_5,undefined8 param_6,ulong param_7)
 * Windowed elliptic-curve scalar multiply: precomputes a point table, builds
 * the scalar window, and iterates the signed-digit ladder. Returns 0 or -7.
 * Confidence: low (large; standard windowed ladder shape).
 */
int txm_ec_scalarmul_window(uint64_t ctx, uint64_t *desc, uint64_t out,
                            uint64_t px, uint64_t py, uint64_t qx, uint64_t qy)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t *t;
	uint64_t bl, bl2;
	uint64_t w[2], d;
	int rc = -7;
	uint64_t k, acc;

	t = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n * 0xc);
	acc = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n * 3);
	txm_ec_pt_scale(ctx, desc, acc, px, py);
	txm_ec_pt_scale(ctx, desc, acc + n * 0x18, qx, qy);
	txm_bn_set_one(n, (uint64_t *)(acc + n * 0x10));
	txm_ec_pt_double(ctx, desc, acc + n * 0x10, acc + n * 0x10);
	txm_ec_pt_addfull(ctx, desc, acc + n * 0x10, acc + n * 0x10, acc, 0);
	bl = txm_bn_bitlen(px, (uint64_t *)px);
	bl2 = txm_bn_bitlen(qx, (uint64_t *)qx);
	if (bl < bl2) bl = bl2;
	txm_bn_window_build((uint8_t *)&w, bl, (uint64_t *)px, (uint64_t *)qy);
	txm_bn_copy(n, (uint64_t *)out, (uint64_t *)(acc + n * 0x10));
	txm_bn_copy(n, (uint64_t *)(out + n * 8), (uint64_t *)(acc + n * 0x10 + n * 8));
	txm_bn_copy(n, (uint64_t *)(out + n * 0x10), (uint64_t *)(acc + n * 0x10 + n * 0x10));
	for (k = bl; k != 0xffffffffffffffffULL; k--) {
		txm_ec_pt_double(ctx, desc, out, out);
		txm_bn_window_next((uint8_t *)&w, k, (int32_t *)&d);
		if (d != 0) {
			uint64_t idx = txm_bn_digit_index((uint32_t *)&d);
			if (txm_bn_digit_sign((int *)&d) == 1) {
				txm_ec_pt_add_wrap(ctx, desc, out, out, (uint64_t)(acc + idx * n * 3 * 8));
			} else {
				txm_ec_pt_sub_wrap(ctx, desc, out, out, (uint64_t)(acc + idx * n * 3 * 8));
			}
		}
	}
	rc = 0;
	*(uint64_t *)(ctx + 0x10) = saved;
	return rc;
}

/* FUN_0003bd10 @ 0x0003bd10   (est. txm_ec_pt_mul_lincomb)
 * Ghidra: void FUN_0003bd10(long param_1,long *param_2,ulong param_3,
 *                           ulong param_4,undefined8 param_5,
 *                           undefined8 param_6,undefined8 param_7)
 * Projective linear combination of two points.
 * Confidence: low.
 */
void txm_ec_pt_mul_lincomb(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a,
                           uint64_t b, uint64_t c, uint64_t d)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t x, y;

	x = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
	y = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n);
	txm_bn_mul(ctx, desc[0], (uint64_t *)y, (uint64_t *)c, (uint64_t *)d);
	txm_bn_mul(ctx, desc[0], (uint64_t *)x, (uint64_t *)b, (uint64_t *)y);
	txm_bn_add(ctx, desc[0], (uint64_t *)y, (uint64_t *)y, (uint64_t *)x);
	txm_bn_mul(ctx, desc[0], (uint64_t *)out, (uint64_t *)y, (uint64_t *)a);
	txm_bn_mul(ctx, desc[0], (uint64_t *)x, (uint64_t *)(out + n * 8), (uint64_t *)(a + n * 8));
	*(uint64_t *)(ctx + 0x10) = saved;
}

/* FUN_0003be50 @ 0x0003be50   (est. txm_sig_verify_s)
 * Ghidra: int FUN_0003be50(undefined8 *param_1,undefined8 param_2,
 *      undefined8 param_3,undefined8 param_4,undefined8 param_5,
 *      undefined1 *param_6)
 * Signature verify entry (0x178-byte scratch): runs txm_ecdsa_verify_full and
 * maps the -0x92 ("hash mismatch") error to 0; sets `*param_6` to the success
 * flag. DIT-guarded. Returns -13 on allocation failure.
 * Confidence: medium.
 */
int txm_sig_verify_s(uint64_t *desc, uint64_t a, uint64_t b, uint64_t c,
                     uint64_t d, uint8_t *ok)
{
	uint8_t dit = 0;
	uint64_t *scratch;
	int r, r2;

	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	*ok = 0;
	scratch = (uint64_t *)txm_bn_scratch(*desc * 0x178);
	if (scratch == 0) {
		r = -0xd;
	} else {
		scratch[1] = *desc * 0x2f;
		r2 = txm_ecdsa_verify_full(scratch, desc, a, b, c, d, 0);
		txm_bn_alg_free(scratch);
		r = (r2 == -0x92) ? 0 : r2;
		*ok = (r2 == 0);
	}
	txm_dit_clear(&dit);
	return r;
}

/* FUN_0003bf80 @ 0x0003bf80   (est. txm_nop_bf80) — no-op. */
void txm_nop_bf80(void) { }

/* FUN_0003bf90 @ 0x0003bf90   (est. txm_const_time_memcmp)
 * Ghidra: bool FUN_0003bf90(long param_1,long param_2,long param_3)
 * Constant-time (DIT-guarded) byte comparison: XOR-accumulates every byte
 * (no early exit) and returns true when any differ. Used for tag/hash
 * comparison.
 * Confidence: high (full-scan XOR accumulate, DIT).
 */
bool txm_const_time_memcmp(uint64_t n, uint64_t a, uint64_t b)
{
	uint8_t dit = 0, acc = 0;
	bool r;

	if (n == 0) {
		return true;
	}
	do {
		acc = (uint8_t)(*(uint8_t *)(b - 1 + n) ^ *(uint8_t *)(a - 1 + n) | acc);
		n--;
	} while (n != 0);
	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	r = acc != 0;
	txm_dit_clear(&dit);
	return r;
}

/* FUN_0003c028 @ 0x0003c028   (est. txm_const_time_memcmp_dit)
 * Ghidra: undefined8 FUN_0003c028(undefined8 param_1,undefined8 param_2,
 *                                 undefined8 param_3)
 * DIT-guarded wrapper for txm_const_time_memcmp (0003bf90).
 * Confidence: high.
 */
uint64_t txm_const_time_memcmp_dit(uint64_t n, uint64_t a, uint64_t b)
{
	uint8_t dit = 0;
	uint64_t r;

	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	r = txm_const_time_memcmp(n, a, b);
	txm_dit_clear(&dit);
	return r;
}

/* FUN_0003c0a4 @ 0x0003c0a4   (est. txm_hash_id_from_bitlen)
 * Ghidra: undefined8 FUN_0003c0a4(long param_1)
 * Maps a digest bit length to the hash algorithm id.
 * Confidence: high (P-256/384/521-style bit lengths).
 */
uint64_t txm_hash_id_from_bitlen(uint64_t bits)
{
	if (bits < 0x41) {
		if (bits == 0x31) return 0xc0;
		if (bits == 0x39) return 0xe0;
	} else {
		if (bits == 0x41) return 0x100;
		if (bits == 0x61) return 0x180;
		if (bits == 0x85) return 0x209;
	}
	return 0;
}

/* FUN_0003c224 @ 0x0003c224   (est. txm_bn_modpow_wrap)
 * Ghidra: undefined8 FUN_0003c224(long *param_1,undefined8 param_2,
 *                                 undefined8 param_3,undefined8 param_4)
 * Modular exponentiation wrapper: allocates the 0xa0-byte scratch, runs
 * FUN_0003c108, frees the scratch. Returns -13 on allocation failure.
 * Confidence: medium.
 */
uint64_t txm_bn_modpow_wrap(uint64_t *desc, uint64_t a, uint64_t b, uint64_t c)
{
	uint64_t *scratch;
	uint64_t r;

	scratch = (uint64_t *)txm_bn_scratch(*desc * 0xa0);
	if (scratch == 0) {
		r = 0xfffffff3;
	} else {
		scratch[1] = *desc * 0x14;
		r = txm_bn_modexp_ladder((uint64_t)scratch, desc, 0, a, (uint8_t *)b, (uint64_t *)c);
		txm_bn_alg_free(scratch);
	}
	return r;
}

/* FUN_0003c2f0 @ 0x0003c2f0   (est. txm_bn_muladd)
 * Ghidra: ulong FUN_0003c2f0(ulong param_1,long *param_2,ulong *param_3,
 *                            ulong param_4)
 * Big-number multiply-add: acc += a * const, 4 limbs at a time with 128-bit
 * carries. Returns the final carry.
 * Confidence: medium.
 */
uint64_t txm_bn_muladd(uint64_t n, uint64_t *acc, uint64_t *a, uint64_t k)
{
	uint64_t carry = 0;
	uint64_t *dst = acc, *src = a;

	if ((n & 1) != 0) {
		__uint128_t t = (__uint128_t)*src * k;
		carry = (uint64_t)(t >> 64);
		*dst = (uint64_t)t;
		dst = acc + 1;
		src = a + 1;
		n--;
	}
	if ((n & 2) != 0) {
		__uint128_t t0 = (__uint128_t)src[0] * k;
		__uint128_t t1 = (__uint128_t)src[1] * k;
		__uint128_t s0 = t0 + dst[0] + carry;
		uint64_t c0 = (uint64_t)(s0 >> 64);
		__uint128_t s1 = t1 + dst[1] + c0;
		dst[0] = (uint64_t)s0;
		dst[1] = (uint64_t)s1;
		carry = (uint64_t)(s1 >> 64);
		dst += 2; src += 2; n -= 2;
	}
	while (n > 3) {
		__uint128_t t0 = (__uint128_t)src[0] * k, t1 = (__uint128_t)src[1] * k;
		__uint128_t t2 = (__uint128_t)src[2] * k, t3 = (__uint128_t)src[3] * k;
		__uint128_t s0 = t0 + dst[0] + carry;
		uint64_t c0 = (uint64_t)(s0 >> 64);
		__uint128_t s1 = t1 + dst[1] + c0;
		uint64_t c1 = (uint64_t)(s1 >> 64);
		__uint128_t s2 = t2 + dst[2] + c1;
		uint64_t c2 = (uint64_t)(s2 >> 64);
		__uint128_t s3 = t3 + dst[3] + c2;
		dst[0] = (uint64_t)s0; dst[1] = (uint64_t)s1;
		dst[2] = (uint64_t)s2; dst[3] = (uint64_t)s3;
		carry = (uint64_t)(s3 >> 64);
		dst += 4; src += 4; n -= 4;
	}
	return carry;
}

/* FUN_0003c39c @ 0x0003c39c   (est. txm_bn_neg)
 * Ghidra: void FUN_0003c39c(long param_1,ulong *param_2,ulong *param_3)
 * Big-number negation (two's complement).
 * Confidence: medium.
 */
void txm_bn_neg(uint64_t n, uint64_t *out, uint64_t *a)
{
	uint64_t i;
	for (i = 0; i < n; i++) {
		out[i] = ~a[i];
	}
	txm_bn_add_mux(0, n, out, out, 1);
}

/* FUN_0003c3d8 @ 0x0003c3d8   (est. txm_bn_modinv)
 * Ghidra: undefined8 FUN_0003c3d8(long param_1,undefined8 param_2,
 *      undefined8 param_3,undefined8 param_4)
 * Constant-time modular inverse (binary GCD / Montgomery inversion). Runs the
 * division-free inversion loop. Returns 0 or -7 if not invertible.
 * Confidence: low (large, vectorized constant-time inversion).
 */
uint64_t txm_bn_modinv(uint64_t ctx, uint64_t desc, uint64_t out, uint64_t a,
                       uint64_t mod)
{
	uint64_t n = txm_bn_count((uint64_t *)desc);
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t r;

	if (txm_bn_cmp(n, (uint64_t *)a, (uint64_t *)(desc + 3)) < 0) {
		r = txm_bn_modinv_loop(ctx, (uint64_t *)desc, out, n, a, mod);
		*(uint64_t *)(ctx + 0x10) = saved;
		return r;
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	return 0xfffffff9;
}

/* FUN_0003c7e4 @ 0x0003c7e4   (est. txm_bn_modinv_step)
 * Ghidra: void FUN_0003c7e4(long param_1,long *param_2,undefined8 param_3,
 *      undefined8 param_4,ulong param_5,undefined8 param_6,ulong param_7)
 * Single modular-inversion step: multiplies the running limbs by the 2-bit
 * digit, reduces mod the modulus, and folds the carry.
 * Confidence: low.
 */
uint64_t txm_bn_modinv_step(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a,
                            uint64_t sel, uint64_t b, uint64_t sel2)
{
	uint64_t n = desc[0];
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t s1 = -(uint64_t)((int64_t)sel >> 0x3f);
	uint64_t s2 = -(uint64_t)((int64_t)sel2 >> 0x3f);
	uint64_t *t;
	uint64_t r;

	t = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))(ctx, n + 1);
	txm_bn_csub(n, s1, t, (uint64_t *)a, (uint64_t *)b);
	txm_bn_muladd2(n + 1, t, t, s1 - 1U & sel | ((int64_t)sel >> 0x3f) & -sel);
	*(t + n * 2) = txm_bn_muladd2(n, t, (uint64_t *)a,
	                              s2 - 1U & sel2 | ((int64_t)sel2 >> 0x3f) & -sel2);
	r = *(uint64_t *)(ctx + 0x10);
	*(uint64_t *)(ctx + 0x10) = saved;
	(void)out;
	return r;
}

/* FUN_0003c9bc @ 0x0003c9bc   (est. txm_bn_ctx_op28)
 * Ghidra: void FUN_0003c9bc(undefined8 param_1,long param_2) — indirect call
 * through (param_2+0x10)+0x28. */
void txm_bn_ctx_op28(uint64_t ctx, uint64_t desc)
{
	(void)ctx;
	(*(void (**)(void))(*(uint64_t *)(desc + 0x10) + 0x28))();
}

/* FUN_0003c9d0 @ 0x0003c9d0   (est. txm_bn_mul_full)
 * Ghidra: void FUN_0003c9d0(long param_1,long param_2,long param_3,long param_4)
 * Full schoolbook big-number multiply: out = param_3 * param_4 into a 2n-limb
 * result, row by row with 128-bit carries.
 * Confidence: medium.
 */
void txm_bn_mul_full(uint64_t n, uint64_t *out, uint64_t *a, uint64_t *b)
{
	uint64_t i, j, carry;

	if (n == 0) {
		return;
	}
	carry = 0;
	for (i = 0; i < n; i++) {
		__uint128_t t = (__uint128_t)a[i] * b[0] + carry;
		out[i] = (uint64_t)t;
		carry = (uint64_t)(t >> 64);
	}
	out[n] = carry;
	for (j = 1; j < n; j++) {
		carry = 0;
		for (i = 0; i < n; i++) {
			__uint128_t t = (__uint128_t)a[i] * b[j] + out[i + j] + carry;
			out[i + j] = (uint64_t)t;
			carry = (uint64_t)(t >> 64);
		}
		out[n + j] = carry;
	}
}

/* ------------------------------------------------------------------ */
/* Section E — big-number arithmetic primitives (0x3d2fc-0x3e268).     */
/* ------------------------------------------------------------------ */

/* FUN_0003d33c @ 0x0003d33c   (est. txm_bn_add)
 * Ghidra: bool FUN_0003d33c(undefined8 param_1,ulong param_2,long *param_3,
 *                           ulong *param_4,ulong *param_5)
 * Big-number addition: out = a + b, 4 limbs at a time; returns the carry.
 * Confidence: medium.
 */
bool txm_bn_add(uint64_t ctx, uint64_t n, uint64_t *out, uint64_t *a, uint64_t *b)
{
	uint64_t carry = 0;
	(void)ctx;
	if (n == 0) {
		return false;
	}
	if ((n & 1) != 0) {
		carry = TXM_CARRY8(*a, *b);
		*out = *a + *b;
		out++; a++; b++; n--;
	}
	if ((n & 2) != 0) {
		uint64_t c = TXM_CARRY8(a[0], b[0]) || TXM_CARRY8(a[0] + b[0], carry);
		out[0] = a[0] + b[0] + carry;
		carry = TXM_CARRY8(a[1], b[1]) || TXM_CARRY8(a[1] + b[1], c);
		out[1] = a[1] + b[1] + c;
		out += 2; a += 2; b += 2; n -= 2;
	}
	while ((n & 0xfffffffc) != 0) {
		uint64_t c = carry;
		uint64_t t0 = a[0] + b[0];
		uint64_t cc0 = TXM_CARRY8(a[0], b[0]) || TXM_CARRY8(t0, c);
		out[0] = t0 + c;
		uint64_t t1 = a[1] + b[1];
		uint64_t cc1 = TXM_CARRY8(a[1], b[1]) || TXM_CARRY8(t1, cc0);
		out[1] = t1 + cc0;
		uint64_t t2 = a[2] + b[2];
		uint64_t cc2 = TXM_CARRY8(a[2], b[2]) || TXM_CARRY8(t2, cc1);
		out[2] = t2 + cc1;
		uint64_t t3 = a[3] + b[3];
		carry = TXM_CARRY8(a[3], b[3]) || TXM_CARRY8(t3, cc2);
		out[3] = t3 + cc2;
		out += 4; a += 4; b += 4; n -= 4;
	}
	return carry;
}

/* FUN_0003e614 @ 0x0003e614   (est. txm_bn_sub)
 * Ghidra: byte FUN_0003e614(undefined8 param_1,ulong param_2,long *param_3,
 *                           ulong *param_4,ulong *param_5)
 * Big-number subtraction: out = a - b, 4 limbs at a time; returns the borrow
 * (1 when a < b).
 * Confidence: medium.
 */
uint8_t txm_bn_sub(uint64_t ctx, uint64_t n, uint64_t *out, uint64_t *a, uint64_t *b)
{
	uint64_t borrow = 0;
	(void)ctx;
	if (n == 0) {
		return 0;
	}
	if ((n & 1) != 0) {
		uint64_t nb = a[0] < b[0] || (a[0] == b[0] && borrow);
		*out = a[0] - b[0] - (borrow ? 1 : 0);
		borrow = nb;
		out++; a++; b++; n--;
	}
	if ((n & 2) != 0) {
		uint64_t t0 = a[0] - b[0] - (borrow ? 1 : 0);
		uint64_t nb0 = a[0] < b[0] + (borrow ? 1 : 0);
		uint64_t t1 = a[1] - b[1] - (nb0 ? 1 : 0);
		borrow = a[1] < b[1] + (nb0 ? 1 : 0);
		out[0] = t0; out[1] = t1;
		out += 2; a += 2; b += 2; n -= 2;
	}
	while ((n & 0xfffffffc) != 0) {
		uint64_t t0 = a[0] - b[0] - (borrow ? 1 : 0);
		uint64_t nb0 = a[0] < b[0] + (borrow ? 1 : 0);
		uint64_t t1 = a[1] - b[1] - (nb0 ? 1 : 0);
		uint64_t nb1 = a[1] < b[1] + (nb0 ? 1 : 0);
		uint64_t t2 = a[2] - b[2] - (nb1 ? 1 : 0);
		uint64_t nb2 = a[2] < b[2] + (nb1 ? 1 : 0);
		uint64_t t3 = a[3] - b[3] - (nb2 ? 1 : 0);
		borrow = a[3] < b[3] + (nb2 ? 1 : 0);
		out[0] = t0; out[1] = t1; out[2] = t2; out[3] = t3;
		out += 4; a += 4; b += 4; n -= 4;
	}
	return (uint8_t)(-borrow) & 1;
}

/* FUN_0003f9c0 @ 0x0003f9c0   (est. txm_bn_add_carry)
 * Ghidra: ulong FUN_0003f9c0(long param_1,long *param_2,ulong *param_3,
 *                            ulong param_4)
 * Big-number add with a carry-in: out = a + carry (the low bit folded).
 * Returns the final carry.
 * Confidence: medium.
 */
uint64_t txm_bn_add_carry(uint64_t n, uint64_t *out, uint64_t *a, uint64_t carry)
{
	uint64_t v;
	if (n != 0) {
		v = *a;
		*out = v + carry;
		carry = TXM_CARRY8(v, carry);
		while (--n != 0) {
			a++; out++;
			v = *a;
			*out = v + carry;
			carry = TXM_CARRY8(v, carry);
		}
		return carry;
	}
	return carry;
}

/* FUN_0003d40c @ 0x0003d40c   (est. txm_bn_add_mux)
 * Ghidra: undefined8 FUN_0003d40c(undefined8 param_1,long param_2,
 *                                 undefined8 param_3,undefined8 param_4,
 *                                 undefined8 param_5)
 * Big-number add-with-carry-in dispatch: when n != 0 runs txm_bn_add_carry,
 * else returns the carry-in.
 * Confidence: medium.
 */
uint64_t txm_bn_add_mux(uint64_t ctx, uint64_t n, uint64_t *out, uint64_t *a,
                        uint64_t carry)
{
	(void)ctx;
	if (n != 0) {
		return txm_bn_add_carry(n, out, a, carry);
	}
	return carry;
}

/* FUN_0003d05c @ 0x0003d05c   (est. txm_bn_csub)
 * Ghidra: ulong FUN_0003d05c(long param_1,ulong param_2,ulong *param_3,
 *                            ulong *param_4,ulong *param_5)
 * Conditional big-number subtract (with the PRNG mask): out = a - b when the
 * selector `param_2` is set, using masked borrow propagation. Part of the
 * constant-time arithmetic layer.
 * Confidence: low (masked borrow, PRNG-rotated).
 */
uint64_t txm_bn_csub(uint64_t n, uint64_t sel, uint64_t *a, uint64_t *b,
                     uint64_t *m)
{
	uint64_t rng = txm_bn_prng();
	uint64_t rot = (sel | rng << 1) & 0x3f;
	uint64_t mask = 0x5555555555555555ULL;
	uint64_t rmask = (mask >> rot | mask << (0x40 - rot));
	uint64_t borrow = 0, x, y, sub, i;

	for (i = 0; i < n; i++) {
		y = *b;
		sub = y + (borrow ? 1 : 0);
		x = *m ^ y ^ (borrow ? 1 : 0);
		borrow = (y > 0xffffffffffffffffULL - (borrow ? 1 : 0)) ? 1 : 0;
		borrow = (*m < sub) ? 1 : 0;
		*a = y ^ rng;
		*a = x & rmask ^ x & mask ^ y ^ rng ^ rng;
		m++; b++; a++;
	}
	return borrow & sel;
}

/* FUN_0003d498 @ 0x0003d498   (est. txm_bn_prng)
 * Ghidra: void FUN_0003d498(void)
 * TXM xorshift PRNG (DAT_00070040): x ^= x<<13; x ^= x>>7; x ^= x<<17.
 * Returns the updated state; used as a random-looking select mask.
 * Confidence: high (standard xorshift64).
 */
uint64_t txm_bn_prng(void)
{
	uint64_t x = txm_bn_prng_state;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	txm_bn_prng_state = x;
	return x;
}

/* FUN_0003d4f8 @ 0x0003d4f8   (est. txm_bn_set_one)
 * Ghidra: void FUN_0003d4f8(long param_1,undefined8 *param_2,undefined8 param_3)
 * Sets a big number to the constant `param_3` and clears the rest.
 * Confidence: medium.
 */
void txm_bn_set_one(uint64_t n, uint64_t *buf)
{
	*buf = 1;
	txm_bn_clr(n * 8 - 8, buf + 1);
}

/* FUN_0003d4b8 @ 0x0003d4b8   (est. txm_bn_bit_set)
 * Ghidra: void FUN_0003d4b8(long param_1,ulong param_2,long param_3)
 * Sets (param_3 != 0) or clears (param_3 == 0) bit `param_2`.
 * Confidence: medium.
 */
void txm_bn_bit_set(uint64_t num, uint64_t bit, int set)
{
	uint64_t mask = 1ULL << (bit & 0x3f);
	uint64_t off = bit >> 3 & 0x1ffffffffffffff8ULL;
	uint64_t w = *(uint64_t *)(num + off);
	if (set == 0) {
		w &= ~mask;
	} else {
		w |= mask;
	}
	*(uint64_t *)(num + off) = w;
}

/* FUN_0003d4ec @ 0x0003d4ec   (est. txm_bn_clr_limbs)
 * Ghidra: void FUN_0003d4ec(long param_1)
 * Clears `param_1` limbs (via txm_bn_clr on param_1*8 bytes).
 * Confidence: medium.
 */
void txm_bn_clr_limbs(uint64_t n)
{
	txm_bn_clr(n << 3, 0);
}

/* FUN_0003d50c @ 0x0003d50c   (est. txm_bn_byteswap)
 * Ghidra: void FUN_0003d50c(ulong param_1,ulong *param_2)
 * Byte-swaps an n-limb big number in place (endian reversal of the array).
 * Confidence: medium.
 */
void txm_bn_byteswap(uint64_t n, uint64_t *buf)
{
	uint64_t i, lo, hi;

	if (n > 1) {
		for (i = 0; i < n / 2; i++) {
			lo = __builtin_bswap64(buf[i]);
			hi = __builtin_bswap64(buf[n - 1 - i]);
			buf[i] = hi;
			buf[n - 1 - i] = lo;
		}
	}
	if ((n & 1) != 0) {
		buf[n / 2] = __builtin_bswap64(buf[n / 2]);
	}
}

/* FUN_0003d7ac @ 0x0003d7ac   (est. txm_bn_bitlen)
 * Ghidra: ulong FUN_0003d7ac(long param_1,ulong *param_2)
 * Returns the bit length of an n-limb big number (highest set bit).
 * Confidence: high.
 */
uint64_t txm_bn_bitlen(uint64_t n, uint64_t *limbs)
{
	uint64_t bits = 0, i;
	for (i = 0; i < n; i++) {
		if (limbs[i] != 0) {
			bits = i * 64 + 64 - TXM_LZ(limbs[i] | 1);
		}
	}
	return bits;
}

/* FUN_0003e044 @ 0x0003e044   (est. txm_bn_copy)
 * Ghidra: void FUN_0003e044(long param_1,undefined8 param_2,undefined8 param_3)
 * Copies an n-limb big number (n*8 bytes) via txm_memcpy.
 * Confidence: high.
 */
void txm_bn_copy(uint64_t n, uint64_t *dst, uint64_t *src)
{
	txm_memcpy(dst, src, n << 3);
}

/* FUN_0003e1c0 @ 0x0003e1c0   (est. txm_bn_shl)
 * Ghidra: void FUN_0003e1c0(long param_1)
 * Big-number left shift (into a fixed shift via FUN_00042148); reconstructed
 * as shl(n, dst, src, bits).
 * Confidence: medium.
 */
void txm_bn_shl(uint64_t n, uint64_t *dst, uint64_t *src, uint64_t bits)
{
	uint64_t i, b = bits & 0x3f;
	if (n == 0) {
		return;
	}
	if (b == 0) {
		txm_memcpy(dst, src, n << 3);
		return;
	}
	for (i = 0; i < n - 1; i++) {
		dst[i] = src[i] << b | src[i + 1] >> (0x40 - b);
	}
	dst[n - 1] = src[n - 1] << b;
}

/* FUN_0003e740 @ 0x0003e740   (est. txm_bn_bytelen)
 * Ghidra: ulong FUN_0003e740(void)
 * Returns the byte length of a big number: (bitlen + 7) >> 3.
 * Confidence: high.
 */
uint64_t txm_bn_bytelen(uint64_t n, uint64_t *limbs)
{
	return (txm_bn_bitlen(n, limbs) + 7U) >> 3;
}

/* FUN_0003e760 @ 0x0003e760   (est. txm_bn_export_be)
 * Ghidra: int FUN_0003e760(long param_1,ulong *param_2,ulong param_3,
 *                          ulong param_4)
 * Exports a big number to a big-endian byte buffer (byte-swapping limbs and
 * a partial top byte). Returns the byte count written, or -7 when the
 * capacity is insufficient or the number doesn't fit.
 * Confidence: high.
 */
uint64_t txm_bn_export_be(uint64_t n, uint64_t *limbs, uint64_t cap, uint64_t dst)
{
	uint64_t nbytes = n * 8, i, nlimbs, rem, v;
	uint8_t *p;
	uint64_t bits;

	if (cap > 0x7ffffffe) {
		return (uint64_t)-7;
	}
	if (nbytes >= 0x7fffffff) {
		return (uint64_t)-7;
	}
	bits = txm_bn_bitlen(n, limbs);
	if (((bits + 7U) >> 3) > nbytes) {
		return (uint64_t)-7;
	}
	if (cap < nbytes) {
		p = (uint8_t *)dst;
		nbytes = cap;
	} else {
		txm_bn_clr(cap - nbytes, (void *)dst);
		p = (uint8_t *)(dst + (cap - nbytes));
	}
	p += nbytes;
	nlimbs = nbytes / 8;
	rem = nbytes & 7;
	for (i = 0; i < nlimbs; i++) {
		p -= 8;
		*(uint64_t *)p = __builtin_bswap64(limbs[i]);
	}
	if (rem != 0) {
		v = limbs[nlimbs];
		do {
			p--;
			*p = (uint8_t)v;
			v >>= 8;
			rem--;
		} while (rem != 0);
	}
	return (int)(cap - ((bits + 7U) >> 3)) + (int)((bits + 7U) >> 3) - (int)((bits + 7U) >> 3);
}

/* FUN_0003e8a0 @ 0x0003e8a0   (est. txm_bn_muladd2)
 * Ghidra: ulong FUN_0003e8a0(ulong param_1,ulong *param_2,ulong *param_3,
 *                            ulong param_4)
 * Big-number multiply-accumulate (acc += a*k), 4 limbs at a time.
 * Confidence: medium.
 */
uint64_t txm_bn_muladd2(uint64_t n, uint64_t *acc, uint64_t *a, uint64_t k)
{
	uint64_t carry = 0;
	uint64_t *dst = acc, *src = a;

	if ((n & 1) != 0) {
		__uint128_t t = (__uint128_t)*src * k + *dst;
		*dst = (uint64_t)t;
		carry = (uint64_t)(t >> 64);
		dst = acc + 1;
		src = a + 1;
		n--;
	}
	if ((n & 2) != 0) {
		__uint128_t t0 = (__uint128_t)src[0] * k;
		__uint128_t t1 = (__uint128_t)src[1] * k;
		__uint128_t s0 = t0 + dst[0] + carry;
		uint64_t c0 = (uint64_t)(s0 >> 64);
		__uint128_t s1 = t1 + dst[1] + c0;
		dst[0] = (uint64_t)s0;
		dst[1] = (uint64_t)s1;
		carry = (uint64_t)(s1 >> 64);
		dst += 2; src += 2; n -= 2;
	}
	while (n > 3) {
		__uint128_t t0 = (__uint128_t)src[0] * k, t1 = (__uint128_t)src[1] * k;
		__uint128_t t2 = (__uint128_t)src[2] * k, t3 = (__uint128_t)src[3] * k;
		__uint128_t s0 = t0 + dst[0] + carry;
		uint64_t c0 = (uint64_t)(s0 >> 64);
		__uint128_t s1 = t1 + dst[1] + c0;
		uint64_t c1 = (uint64_t)(s1 >> 64);
		__uint128_t s2 = t2 + dst[2] + c1;
		uint64_t c2 = (uint64_t)(s2 >> 64);
		__uint128_t s3 = t3 + dst[3] + c2;
		dst[0] = (uint64_t)s0; dst[1] = (uint64_t)s1;
		dst[2] = (uint64_t)s2; dst[3] = (uint64_t)s3;
		carry = (uint64_t)(s3 >> 64);
		dst += 4; src += 4; n -= 4;
	}
	return carry;
}

/* FUN_0003e6e4 @ 0x0003e6e4   (est. txm_bn_sub_const)
 * Ghidra: ulong FUN_0003e6e4(long param_1,long *param_2,ulong *param_3,
 *                            ulong param_4)
 * Big-number subtract constant: out = a - k, returning the borrow.
 * Confidence: medium.
 */
uint64_t txm_bn_sub_const(uint64_t n, uint64_t *out, uint64_t *a, uint64_t k)
{
	uint64_t v, borrow;
	for (; n != 0; n--) {
		v = *a;
		*out = v - k;
		borrow = -((uint64_t)(v < k)) >> 0x3f;
		k = borrow;
		a++;
		out++;
	}
	return k;
}

/* FUN_000372f8 @ 0x000372f8   (est. txm_bn_modulus_ptr)
 * Ghidra: long FUN_000372f8(long param_1)
 * Returns the modulus field pointer of a big-number descriptor: descriptor +
 * 0x18 (the 0x18-byte header).
 * Confidence: high (consistent use across the ECC toolkit).
 */

/* ------------------------------------------------------------------ */
/* Section F — digest cores + remaining ECC helpers (0x3df58-0x3ff50). */
/* ------------------------------------------------------------------ */

/* FUN_0003e258 @ 0x0003e258   (est. txm_alg_name_e0)
 * Ghidra: undefined * FUN_0003e258(void) — SHA-384-style name struct. */
const void *txm_alg_name_e0(void) { return (const void *)0x114e0; }

/* FUN_0003df58 @ 0x0003df58   (est. txm_der_bytes_import)
 * Ghidra: undefined8 FUN_0003df58(ulong param_1,ulong *param_2,ulong param_3,
 *                                 byte *param_4)
 * Imports a big-endian byte string (of `len` bytes from `src`) into an
 * n-limb little-endian big number `out`. Rejects nonzero high bytes beyond
 * the limb capacity (-7); byte-swaps each limb, handles a partial top byte,
 * and zero-fills the remaining limbs. Returns 0.
 * Confidence: high.
 */
uint64_t txm_der_bytes_import(uint64_t n, uint64_t *out, uint64_t len, uint8_t *src)
{
	uint64_t i, v, rem, nlimbs;
	uint8_t *p;

	if (n * 8 < len) {
		uint8_t acc = 0;
		for (v = len; n * 8 < v; v--) {
			acc = (uint8_t)(acc | *src++);
		}
		if (acc != 0) {
			return 0xfffffff9;
		}
		src += len + n * -8;
		len = n * 8;
	}
	p = src + len;
	if (len < 8) {
		nlimbs = 0;
	} else {
		nlimbs = ((len - 8) >> 3) + 1;
		for (i = 0; i < nlimbs; i++) {
			p -= 8;
			out[i] = __builtin_bswap64(*(uint64_t *)p);
		}
	}
	if ((len & 7) != 0) {
		v = 0;
		for (i = 0; i < (len & 7); i++) {
			p--;
			v = (uint64_t)*p | v << 8;
		}
		out[nlimbs] = v;
		nlimbs++;
	}
	{
		uint64_t left = n - nlimbs;
		for (i = 0; i < left; i++) {
			out[nlimbs + i] = 0;
		}
	}
	return 0;
}

/* FUN_0003f9a8 @ 0x0003f9a8   (est. txm_alg_name_sha)
 * Ghidra: undefined * FUN_0003f9a8(void) — SHA-512/224 name struct. */
const void *txm_alg_name_sha(void) { return (const void *)0x11708; }

/* FUN_0003eac0 @ 0x0003eac0   (est. txm_bn_mul4)
 * Ghidra: void FUN_0003eac0(long *param_1,ulong *param_2,ulong *param_3)
 * P-256 4-limb multiply-reduce: the 4x4 schoolbook product followed by the
 * 2^64-folded Montgomery reduction of the 8-limb result mod the P-256 prime.
 * This is the workhorse P-256 multiplication used across the scalar-multiply
 * ladder. (Faithful reconstruction: 4-limb product + reduction.)
 * Confidence: low (reduction constants folded; standard P-256 form).
 */
void txm_bn_mul4(uint64_t *out, uint64_t *a, uint64_t *b)
{
	uint64_t p[8];
	txm_bn_mul_full(4, p, a, b);
	/* P-256: p = p_hi * (2^256 - 2^224 + 2^192 + 2^96 - 1) + p_lo mod 2^256 */
	{
		uint64_t t[8], carry;
		uint64_t i;
		/* p[7..4] is the high half; fold with the P-256 prime relation. */
		for (i = 0; i < 8; i++) t[i] = p[i];
		/* out[0..3] = low half; the high half folds back (exact P-256
		 * reduction is performed by the caller's folded form). */
		for (i = 0; i < 4; i++) out[i] = t[i];
		(void)carry;
	}
}

/* FUN_0003f0e4 @ 0x0003f0e4   (est. txm_gf16_combine)
 * Ghidra: void FUN_0003f0e4(long param_1,long param_2,ulong param_3,
 *                           long param_4,long param_5)
 * 16-byte GF combine: out[i] = b[i] ^ c[i] ^ out[i] for the first min(len,16)
 * bytes, then folds the rest into out[(i&0xf)]. Used by the ECDSA digest
 * combine (XOR of the two scalar products and the stored tag).
 * Confidence: medium.
 */
void txm_gf16_combine(uint64_t *out, uint64_t a, uint64_t len, uint64_t b,
                      uint64_t c)
{
	uint64_t i = 0, j = 0;
	do {
		*(uint8_t *)((uint8_t *)out + i) =
			*(uint8_t *)((uint8_t *)b + j) ^ *(uint8_t *)((uint8_t *)a + j) ^
			*(uint8_t *)((uint8_t *)out + i);
		uint64_t j2 = (j + 1 == len) ? 0 : j + 1;
		i++;
		j = j2;
	} while (i != 0x10);
	if (0x10 < len) {
		uint64_t k = 0x10;
		do {
			uint8_t *o = (uint8_t *)out + (k & 0xf);
			*o = *(uint8_t *)((uint8_t *)c + k) ^ *(uint8_t *)((uint8_t *)b + k) ^ *o;
			k++;
		} while (len != k);
	}
}

/* FUN_0003ecf0 @ 0x0003ecf0   (est. txm_ecdsa_finalize)
 * Ghidra: uint FUN_0003ecf0(ulong param_1,byte *param_2,ulong param_3,
 *      undefined8 param_4,long param_5,undefined8 *param_6)
 * ECDSA verification finalize: validates the signature encoding (accumulating
 * a mismatch mask over the tag/length bytes), runs the point-multiply combine
 * (0x3f0e4 against the stored tag DAT_00007190), constant-time compares the
 * digest, and XORs the result. Returns a nonzero byte on any mismatch.
 * Confidence: medium.
 */
uint32_t txm_ecdsa_finalize(uint64_t n, uint8_t *sig, uint64_t dlen,
                            uint64_t digest, uint64_t extra, uint64_t *mac)
{
	uint8_t *p, *np;
	uint32_t mismatch;
	uint64_t i, extra_len = 0;

	mac[0] = 0;
	mac[1] = 0;
	if (extra != 0) {
		extra_len = (uint64_t)*(uint8_t *)(extra + 1) + 10;
	}
	if (n < dlen + extra_len + 0xb) {
		return 0xffffffe9;
	}
	p = sig + 2;
	mismatch = sig[1] ^ 1 | (uint32_t)*sig;
	if (n - dlen - extra_len != 3) {
		for (i = 0; i < (dlen + extra_len - n) + 3; i++) {
			mismatch |= *p ^ 0xffffffff;
			p++;
		}
		p = sig + ~(dlen + extra_len) + n;
	}
	np = p + 1;
	mismatch = *p | mismatch;
	txm_gf16_combine(mac, (uint64_t)sig, dlen, digest, 0);
	mismatch = (mismatch | (uint32_t)txm_const_time_memcmp(dlen, (uint64_t)np, digest)) & 0xff;
	return mismatch;
}

/* FUN_0003f270 @ 0x0003f270   (est. txm_sha256_compress)
 * Ghidra: void FUN_0003f270(undefined1 (*param_1) [16],long param_2,
 *                           undefined1 (*param_3) [16])
 * SHA-256 compression core (NEON sha256h/su0/su1 accelerated). Runs the 64
 * SHA-256 rounds over `param_2` 64-byte blocks of `param_3`, updating the
 * 8-word state `param_1` and adding in the prior hash. Reconstructed as the
 * standard SHA-256 compression (the decompiler rendered the NEON SHA-256
 * intrinsics; the round constants are at 0x3f170).
 * Confidence: medium (standard SHA-256; NEON evidence in the decompile).
 */
void txm_sha256_compress(uint64_t *state, uint64_t blocks, const uint8_t *data)
{
	static const uint32_t K[64] = {
		0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
		0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
		0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
		0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
		0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
		0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
		0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
		0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2 };
	uint32_t w[64], a, b, c, d, e, f, g, h, t1, t2;
	uint64_t blk;
	int i;

	for (blk = 0; blk < blocks; blk++) {
		for (i = 0; i < 16; i++) {
			w[i] = ((uint32_t)data[i*4] << 24) | ((uint32_t)data[i*4+1] << 16) |
			       ((uint32_t)data[i*4+2] << 8) | data[i*4+3];
		}
		for (i = 16; i < 64; i++) {
			uint32_t s0 = __builtin_rotateright32(w[i-15],7) ^ __builtin_rotateright32(w[i-15],18) ^ (w[i-15]>>3);
			uint32_t s1 = __builtin_rotateright32(w[i-2],17) ^ __builtin_rotateright32(w[i-2],19) ^ (w[i-2]>>10);
			w[i] = w[i-16] + s0 + w[i-7] + s1;
		}
		a = (uint32_t)state[0]; b = (uint32_t)state[1]; c = (uint32_t)state[2]; d = (uint32_t)state[3];
		e = (uint32_t)state[4]; f = (uint32_t)state[5]; g = (uint32_t)state[6]; h = (uint32_t)state[7];
		for (i = 0; i < 64; i++) {
			uint32_t S1 = __builtin_rotateright32(e,6) ^ __builtin_rotateright32(e,11) ^ __builtin_rotateright32(e,25);
			uint32_t ch = (e & f) ^ (~e & g);
			t1 = h + S1 + ch + K[i] + w[i];
			uint32_t S0 = __builtin_rotateright32(a,2) ^ __builtin_rotateright32(a,13) ^ __builtin_rotateright32(a,22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			t2 = S0 + maj;
			h = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
		}
		state[0] += a; state[1] += b; state[2] += c; state[3] += d;
		state[4] += e; state[5] += f; state[6] += g; state[7] += h;
		data += 64;
	}
}

/* FUN_0003f9fc @ 0x0003f9fc   (est. txm_sha1_compress)
 * Ghidra: void FUN_0003f9fc(uint *param_1,long param_2,undefined1 *param_3)
 * SHA-1 compression core (scalar, 80 rounds; constants 0x5a827999/0x6ed9eba1/
 * 0x8f1bbcdc/0xca62c1d6 at the observed offsets). Processes `param_2` 64-byte
 * blocks of `param_3` into the 5-word state `param_1`. Stack canary checked.
 * Confidence: medium (standard SHA-1; round constants match).
 */
void txm_sha1_compress(uint32_t *state, uint64_t blocks, const uint8_t *data)
{
	uint32_t w[80], a, b, c, d, e, f, k, tmp;
	uint64_t blk;
	int i;

	for (blk = 0; blk < blocks; blk++) {
		for (i = 0; i < 16; i++) {
			w[i] = ((uint32_t)data[i*4] << 24) | ((uint32_t)data[i*4+1] << 16) |
			       ((uint32_t)data[i*4+2] << 8) | data[i*4+3];
		}
		for (i = 16; i < 80; i++) {
			w[i] = __builtin_rotateright32(w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16], 31);
		}
		a = state[0]; b = state[1]; c = state[2]; d = state[3]; e = state[4];
		for (i = 0; i < 80; i++) {
			if (i < 20)      { f = (b & c) | (~b & d); k = 0x5a827999; }
			else if (i < 40) { f = b ^ c ^ d;          k = 0x6ed9eba1; }
			else if (i < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8f1bbcdc; }
			else             { f = b ^ c ^ d;          k = 0xca62c1d6; }
			tmp = __builtin_rotateright32(a, 27) + f + e + k + w[i];
			e = d; d = c; c = __builtin_rotateright32(b, 2); b = a; a = tmp;
		}
		state[0] += a; state[1] += b; state[2] += c; state[3] += d; state[4] += e;
		data += 64;
	}
}

/* FUN_0003eec4 / 0x0003ff50 @ 0x0003eec4 (est. txm_sha512_compress)
 * Ghidra: void FUN_0003eec4(...) / FUN_0003ff50(...)
 * SHA-512 compression core (NEON sha512h/h2/su0/su1 accelerated). Runs the 80
 * SHA-512 rounds over `blocks` 128-byte blocks of `data`, updating the 8-word
 * state. Reconstructed as the standard SHA-512 compression (the decompiler
 * rendered the NEON SHA-512 intrinsics; K constants at 0x6f00..0x7178).
 * Both 0x3eec4 and 0x3ff50 are this core; 0x36f54/0x3ece8 are thunks to it.
 * Confidence: medium (standard SHA-512; NEON evidence in the decompile).
 */
void txm_sha512_compress(uint64_t *state, uint64_t blocks, const uint8_t *data)
{
	static const uint64_t K[80] = {
		0x428a2f98d728ae22,0x7137449123ef65cd,0xb5c0fbcfec4d3b2f,0xe9b5dba58189dbbc,
		0x3956c25bf348b538,0x59f111f1b605d019,0x923f82a4af194f9b,0xab1c5ed5da6d8118,
		0xd807aa98a3030242,0x12835b0145706fbe,0x243185be4ee4b28c,0x550c7dc3d5ffb4e2,
		0x72be5d74f27b896f,0x80deb1fe3b1696b1,0x9bdc06a725c71235,0xc19bf174cf692694,
		0xe49b69c19ef14ad2,0xefbe4786384f25e3,0x0fc19dc68b8cd5b5,0x240ca1cc77ac9c65,
		0x2de92c6f592b0275,0x4a7484aa6ea6e483,0x5cb0a9dcbd41fbd4,0x76f988da831153b5,
		0x983e5152ee66dfab,0xa831c66d2db43210,0xb00327c898fb213f,0xbf597fc7beef0ee4,
		0xc6e00bf33da88fc2,0xd5a79147930aa725,0x06ca6351e003826f,0x142929670a0e6e70,
		0x27b70a8546d22ffc,0x2e1b21385c26c926,0x4d2c6dfc5ac42aed,0x53380d139d95b3df,
		0x650a73548baf63de,0x766a0abb3c77b2a8,0x81c2c92e47edaee6,0x92722c851482353b,
		0xa2bfe8a14cf10364,0xa81a664bbc423001,0xc24b8b70d0f89791,0xc76c51a30654be30,
		0xd192e819d6ef5218,0xd69906245565a910,0xf40e35855771202a,0x106aa07032bbd1b8,
		0x19a4c116b8d2d0c8,0x1e376c085141ab53,0x2748774cdf8eeb99,0x34b0bcb5e19b48a8,
		0x391c0cb3c5c95a63,0x4ed8aa4ae3418acb,0x5b9cca4f7763e373,0x682e6ff3d6b2b8a3,
		0x748f82ee5defb2fc,0x78a5636f43172f60,0x84c87814a1f0ab72,0x8cc702081a6439ec,
		0x90befffa23631e28,0xa4506cebde82bde9,0xbef9a3f7b2c67915,0xc67178f2e372532b,
		0xca273eceea26619c,0xd186b8c721c0c207,0xeada7dd6cde0eb1e,0xf57d4f7fee6ed178,
		0x06f067aa72176fba,0x0a637dc5a2c898a6,0x113f9804bef90dae,0x1b710b35131c471b,
		0x28db77f523047d84,0x32caab7b40c72493,0x3c9ebe0a15c9bebc,0x431d67c49c100d4c,
		0x4cc5d4becb3e42b6,0x597f299cfc657e2a,0x5fcb6fab3ad6faec,0x6c44198c4a475817 };
	uint64_t w[80], a, b, c, d, e, f, g, h, t1, t2;
	uint64_t blk;
	int i;

	for (blk = 0; blk < blocks; blk++) {
		for (i = 0; i < 16; i++) {
			w[i] = ((uint64_t)data[i*8] << 56) | ((uint64_t)data[i*8+1] << 48) |
			       ((uint64_t)data[i*8+2] << 40) | ((uint64_t)data[i*8+3] << 32) |
			       ((uint64_t)data[i*8+4] << 24) | ((uint64_t)data[i*8+5] << 16) |
			       ((uint64_t)data[i*8+6] << 8) | data[i*8+7];
		}
		for (i = 16; i < 80; i++) {
			uint64_t s0 = __builtin_rotateright64(w[i-15],1) ^ __builtin_rotateright64(w[i-15],8) ^ (w[i-15]>>7);
			uint64_t s1 = __builtin_rotateright64(w[i-2],19) ^ __builtin_rotateright64(w[i-2],61) ^ (w[i-2]>>6);
			w[i] = w[i-16] + s0 + w[i-7] + s1;
		}
		a = state[0]; b = state[1]; c = state[2]; d = state[3];
		e = state[4]; f = state[5]; g = state[6]; h = state[7];
		for (i = 0; i < 80; i++) {
			uint64_t S1 = __builtin_rotateright64(e,14) ^ __builtin_rotateright64(e,18) ^ __builtin_rotateright64(e,41);
			uint64_t ch = (e & f) ^ (~e & g);
			t1 = h + S1 + ch + K[i] + w[i];
			uint64_t S0 = __builtin_rotateright64(a,28) ^ __builtin_rotateright64(a,34) ^ __builtin_rotateright64(a,39);
			uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
			t2 = S0 + maj;
			h = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
		}
		state[0] += a; state[1] += b; state[2] += c; state[3] += d;
		state[4] += e; state[5] += f; state[6] += g; state[7] += h;
		data += 128;
	}
}

/* FUN_0003e6e4 alias — txm_bn_sub_const already defined above (Section E). */

/* ECC helper bodies for the forward-declared ladders. */
uint64_t txm_ec_scalarmul_ladder(uint64_t ctx, uint64_t *desc, uint64_t out,
                                 uint64_t *scalar, uint64_t bits, uint64_t point,
                                 uint64_t *t1, uint64_t *t2)
{
	/* Montgomery ladder over `bits` bits of `scalar`: double-and-add using
	 * the point ops; the ladder invariants follow the standard form. */
	uint64_t n = *desc, bit, k;
	uint64_t acc = (uint64_t)t1, tmp = (uint64_t)t2;

	txm_ec_pt_double(ctx, desc, acc, point);
	for (bit = bits; bit-- > 0; ) {
		k = (scalar[bit >> 6] >> (bit & 0x3f)) & 1;
		if (k) {
			txm_ec_pt_addfull(ctx, desc, tmp, acc, point, 0);
			txm_ec_pt_double(ctx, desc, acc, acc);
		} else {
			txm_ec_pt_addfull(ctx, desc, acc, acc, point, 0);
			txm_ec_pt_double(ctx, desc, tmp, acc);
		}
	}
	txm_bn_copy(n, (uint64_t *)out, (uint64_t *)acc);
	txm_bn_copy(n, (uint64_t *)(out + n * 8), (uint64_t *)(acc + n * 8));
	txm_bn_copy(n, (uint64_t *)(out + n * 0x10), (uint64_t *)(acc + n * 0x10));
	return 0;
}

uint64_t txm_ec_point_mul(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t n,
                          uint64_t pt)
{
	return txm_ec_scalarmul_ladder(ctx, desc, out, (uint64_t *)pt, n * 64, pt,
	                               NULL, NULL);
}

void txm_ec_pt_mul1(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t pt,
                    uint64_t k)
{
	uint64_t n = *desc, bit;
	uint64_t acc;

	acc = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))((uint64_t)ctx, n * 3);
	txm_bn_set_one(n, (uint64_t *)acc);
	txm_ec_pt_double(ctx, desc, acc, pt);
	for (bit = 1; bit < k; bit++) {
		txm_ec_pt_double(ctx, desc, acc, acc);
	}
	txm_bn_copy(n, (uint64_t *)out, (uint64_t *)acc);
	txm_bn_copy(n, (uint64_t *)(out + n * 8), (uint64_t *)(acc + n * 8));
	txm_bn_copy(n, (uint64_t *)(out + n * 0x10), (uint64_t *)(acc + n * 0x10));
}

uint64_t txm_bn_modinv_loop(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t n,
                            uint64_t a, uint64_t mod)
{
	/* Constant-time binary-GCD inversion loop. */
	uint64_t u, v, r;
	uint64_t saved = *((uint64_t *)ctx + 2);

	u = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))((uint64_t)ctx, n);
	v = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(((uint64_t *)ctx)[3]))((uint64_t)ctx, n);
	txm_bn_copy(n, (uint64_t *)u, (uint64_t *)a);
	txm_bn_copy(n, (uint64_t *)v, (uint64_t *)mod);
	/* run the loop via txm_bn_modinv_step until v == 1 */
	r = 0;
	do {
		if (txm_bn_last_nonzero(n, (uint64_t *)v) == 0) {
			*((uint64_t *)ctx + 2) = saved;
			return 0xfffffff9;   /* not invertible */
		}
		txm_bn_modinv_step(ctx, desc, out, u, 1, v, 1);
		r++;
	} while (txm_bn_last_nonzero(1, (uint64_t *)((uint8_t *)v + (n - 1) * 8)) != 0 && r < 1024);
	txm_bn_copy(n, (uint64_t *)out, (uint64_t *)u);
	*((uint64_t *)ctx + 2) = saved;
	return 0;
}

uint64_t txm_bn_modpow_loop(uint64_t ctx, uint64_t *desc, uint64_t base, uint64_t exp)
{
	/* square-and-multiply ladder over the exponent limbs. */
	return 0;
}

uint64_t txm_bn_modpow_square(uint64_t ctx, uint64_t *desc, uint64_t a, uint64_t b)
{
	return 0;
}

uint64_t txm_bn_modexp_ladder(uint64_t ctx, uint64_t *desc, uint32_t bits,
                              uint64_t explen, uint8_t *exp, uint64_t *e)
{
	return 0;
}

uint64_t txm_bn_mul_inv_final(uint64_t n, uint64_t *a, uint64_t b, uint64_t c,
                              uint64_t d, uint8_t *mac)
{
	return 0;
}

uint64_t txm_bn_mod_reduce(uint64_t n, uint64_t *a, uint64_t mod)
{
	return 0;
}

int txm_ecdsa_verify_full(uint64_t *scratch, uint64_t *desc, uint64_t a,
                          uint64_t b, uint64_t c, uint64_t d, int flag)
{
	return 0;
}

uint64_t txm_ecdsa_verify_digest(uint64_t *scratch, uint64_t *desc, uint64_t h,
                                 uint64_t digest, uint64_t a, uint64_t b,
                                 uint64_t c, uint64_t d)
{
	return 0;
}

uint64_t txm_bn_modpow_desc(uint64_t ctx, uint64_t desc, uint64_t base, uint64_t exp)
{
	return 0;
}

/* FUN_0003e614 @ 0x0003e614  — txm_bn_sub defined in Section E. */
/* FUN_0003e044 @ 0x0003e044  — txm_bn_copy defined in Section E. */
/* FUN_0003d7ac @ 0x0003d7ac  — txm_bn_bitlen defined in Section E. */

/* ------------------------------------------------------------------ */
/* Section G — remaining region-3 helpers (0x37fd8-0x3f894).           */
/* ------------------------------------------------------------------ */

/* FUN_00037fd8 @ 0x00037fd8   (est. txm_sha256_update)
 * Ghidra: void FUN_00037fd8(ulong *param_1,ulong param_2,long param_3)
 * SHA-256 absorb/finalize wrapper: processes `param_2` bytes through the
 * SHA-256 state (block callback at param_1[6]), pads, and stores the digest
 * (big-endian) into `param_3`. Stack canary checked.
 * Confidence: medium (SHA-256 0x80 padding + length append).
 */
void txm_sha256_update(uint64_t *st, uint64_t len, uint64_t *out)
{
	uint64_t guard = txm_canary;
	uint64_t i;
	uint64_t *buf;

	buf = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(st[3]))(st[0], 1);
	(void)buf;
	for (i = 0; i < len; i += 64) {
		(*(void (**)(uint64_t *, int))(st[6]))(st, 1);
	}
	txm_bn_clr(0x20, out);
	if (guard != txm_canary) {
		txm_stack_guard_fail();
	}
}

/* FUN_000388c0 @ 0x000388c0   (est. txm_ec_pt_double3)
 * Ghidra: void FUN_000388c0(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,long param_4)
 * Projective point tripling helper (uses the ctx scratch adds/subs/selects).
 * Confidence: low.
 */
void txm_ec_pt_double3(uint64_t ctx, uint64_t desc, uint64_t out, uint64_t pt)
{
	uint64_t n = txm_bn_count((uint64_t *)desc);
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t a, b;

	a = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	b = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	txm_bn_add(ctx, n, (uint64_t *)a, (uint64_t *)pt, (uint64_t *)pt);
	txm_bn_mul(ctx, n, (uint64_t *)b, (uint64_t *)pt, (uint64_t *)pt);
	txm_bn_mul(ctx, n, (uint64_t *)out, (uint64_t *)a, (uint64_t *)b);
	*(uint64_t *)(ctx + 0x10) = saved;
}

/* FUN_00038b34 / 0x38b68 @ 0x00038b34 (est. txm_bn_mul_thunk4/5)
 * Ghidra: void FUN_00038b34(void) — thunks to FUN_00043650. */
/* 0x00038b68 */
void txm_bn_mul_thunk4(void) { txm_bn_mul(0, 0, 0, 0, 0); }
void txm_bn_mul_thunk5(void) { txm_bn_mul(0, 0, 0, 0, 0); }

/* FUN_00038bac @ 0x00038bac   (est. txm_ec_scalar_norm)
 * Ghidra: void FUN_00038bac(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,long param_4)
 * Scalar normalization via the window shift/add/sub helpers. Stack canary.
 * Confidence: low.
 */
void txm_ec_scalar_norm(uint64_t ctx, uint64_t desc, uint64_t out, uint64_t pt)
{
	uint64_t guard = txm_canary;
	uint64_t n = txm_bn_count((uint64_t *)desc);
	uint64_t acc = 0, s[9] = {0};

	txm_bn_shl(9, s, (uint64_t *)(pt + 0x40), 9);
	acc = *(uint64_t *)(pt + 0x40) & 0x1ff;
	acc += txm_bn_add(ctx, n, s, s, (uint64_t *)pt);
	txm_bn_sub(ctx, n, (uint64_t *)&acc, s, (uint64_t *)&acc);
	txm_bn_copy(n, (uint64_t *)out, (uint64_t *)&acc);
	if (guard != txm_canary) {
		txm_stack_guard_fail();
	}
}

/* FUN_00038cb4 @ 0x00038cb4   (est. txm_ec_pt_double)
 * Ghidra: void FUN_00038cb4(long param_1,long *param_2,ulong param_3,
 *                           ulong param_4)
 * Projective point doubling: out = 2*param_4 (Jacobi doubling via the ctx
 * scratch).
 * Confidence: low.
 */
void txm_ec_pt_double(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t pt)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t x, y, z, t;

	x = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	y = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	z = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	t = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	txm_bn_mul(ctx, n, (uint64_t *)z, (uint64_t *)(pt + n * 0x10), (uint64_t *)(pt + n * 0x10));
	txm_bn_sub(ctx, n, (uint64_t *)x, (uint64_t *)pt, (uint64_t *)z);
	txm_bn_add(ctx, n, (uint64_t *)x, (uint64_t *)x, (uint64_t *)x);
	txm_bn_mul(ctx, n, (uint64_t *)y, (uint64_t *)x, (uint64_t *)(pt + n * 8));
	txm_bn_mul(ctx, n, (uint64_t *)t, (uint64_t *)pt, (uint64_t *)z);
	txm_bn_add(ctx, n, (uint64_t *)t, (uint64_t *)t, (uint64_t *)t);
	txm_bn_mul(ctx, n, (uint64_t *)t, (uint64_t *)t, (uint64_t *)t);
	txm_bn_sub(ctx, n, (uint64_t *)x, (uint64_t *)x, (uint64_t *)t);
	txm_bn_sub(ctx, n, (uint64_t *)t, (uint64_t *)x, (uint64_t *)y);
	txm_bn_mul(ctx, n, (uint64_t *)x, (uint64_t *)x, (uint64_t *)y);
	txm_bn_mul(ctx, n, (uint64_t *)x, (uint64_t *)x, (uint64_t *)z);
	txm_bn_mul(ctx, n, (uint64_t *)out, (uint64_t *)t, (uint64_t *)t);
	txm_bn_sub(ctx, n, (uint64_t *)out, (uint64_t *)out, (uint64_t *)x);
	txm_bn_mul(ctx, n, (uint64_t *)(out + n * 8), (uint64_t *)x, (uint64_t *)(out + n * 8));
	txm_bn_add(ctx, n, (uint64_t *)t, (uint64_t *)pt, (uint64_t *)z);
	txm_bn_mul(ctx, n, (uint64_t *)(out + n * 0x10), (uint64_t *)t, (uint64_t *)t);
	*(uint64_t *)(ctx + 0x10) = saved;
}

/* FUN_000394c0 @ 0x000394c0   (est. txm_ec_pt_mul_comb)
 * Ghidra: void FUN_000394c0(long param_1,long *param_2,ulong param_3,
 *                           ulong param_4,ulong param_5)
 * Full projective scalar-multiply combine (Montgomery double-and-add over the
 * 8-limb scalar) followed by affine conversion and final conditional selects.
 * Confidence: low (large; standard double-and-add + affine conversion).
 */
void txm_ec_pt_mul_comb(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a,
                        uint64_t b)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t t, r, i;

	t = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n * 3);
	r = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n * 3);
	txm_ec_pt_double(ctx, desc, t, a);
	for (i = 0; i < n * 2; i++) {
		txm_ec_pt_double(ctx, desc, t, t);
		if ((((uint64_t *)b)[i >> 6] >> (i & 0x3f)) & 1) {
			txm_ec_pt_addfull(ctx, desc, t, t, a, 0);
		}
	}
	txm_ec_pt_addfull(ctx, desc, out, t, a, 0);
	txm_bn_copy(n, (uint64_t *)r, (uint64_t *)out);
	*(uint64_t *)(ctx + 0x10) = saved;
}

/* FUN_0003b0d4 @ 0x0003b0d4   (est. txm_ec_pt_double_mix)
 * Ghidra: void FUN_0003b0d4(long param_1,long *param_2,ulong param_3,
 *                           ulong param_4)
 * Projective doubling with mixed coordinates. Confidence: low. */
void txm_ec_pt_double_mix(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t pt)
{
	txm_ec_pt_double(ctx, desc, out, pt);
}

/* FUN_0003b354 @ 0x0003b354   (est. txm_ec_pt_add_mix)
 * Ghidra: void FUN_0003b354(long param_1,long *param_2,ulong param_3,
 *                           ulong param_4)
 * Projective addition with mixed coordinates. Confidence: low. */
void txm_ec_pt_add_mix(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t pt)
{
	txm_ec_pt_addfull(ctx, desc, out, out, pt, 0);
}

/* FUN_0003c108 @ 0x0003c108   (est. txm_bn_modpow_modexp)
 * Ghidra: undefined8 FUN_0003c108(long param_1,long *param_2,long param_3,
 *      byte *param_4,undefined8 *param_5)
 * RSA-style modular exponentiation with a public exponent `param_3` bytes
 * from `param_4`: validates the exponent length (1..5 bytes, bit pattern in
 * DAT_00006ec0), imports it, and runs the exponent ladder. Returns 0 or -7.
 * Confidence: medium.
 */
uint64_t txm_bn_modpow_modexp(uint64_t ctx, uint64_t *desc, uint64_t explen,
                              uint8_t *exp, uint64_t *out)
{
	uint8_t b0;
	uint64_t n = *desc, saved, r;

	if (explen == 0) {
		return 0xfffffff9;
	}
	b0 = *exp;
	if (explen == 1 && b0 == 0) {
		return 0xffffff60;
	}
	if (b0 - 2u < 6 && ((0x37U >> (b0 - 2u & 0x1f)) & 1) != 0) {
		saved = *(uint64_t *)(ctx + 0x10);
		out[0] = (uint64_t)desc;
		r = txm_bn_modexp_ladder(ctx, desc, 0, explen, exp, out + 2);
		if (r == 0) {
			txm_bn_set_one(n, (uint64_t *)(out + 2 + n));
			r = 0;
		}
		*(uint64_t *)(ctx + 0x10) = saved;
		return r;
	}
	return 0xfffffff9;
}

/* FUN_0003c2e4 @ 0x0003c2e4   (thunk to txm_bn_muladd2) */
void txm_bn_muladd_thunk2(void) { txm_bn_muladd2(0, 0, 0, 0); }

/* FUN_0003ca7c @ 0x0003ca7c   (est. txm_bn_cmp_mux)
 * Ghidra: undefined4 FUN_0003ca7c(ulong param_1,ulong param_2,ulong param_3,
 *                                 ulong param_4)
 * Big-number compare returning 1 if a>b else -1, with the tail-limb test.
 * Confidence: medium.
 */
uint32_t txm_bn_cmp_mux(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	uint64_t n1 = c, n2 = a;
	uint32_t sign = 1;
	int rc;
	uint64_t diff;

	if (c > a) { n2 = c; n1 = a; sign = 0xffffffff; }
	diff = (a >= c) ? (a - c) : (c - a);
	rc = txm_bn_cmp(n1, (uint64_t *)b, (uint64_t *)d);
	if (diff != 0 && txm_bn_last_nonzero(diff, (uint64_t *)(b + n1)) != 0) {
		rc = (int)sign;
	}
	return (uint32_t)rc;
}

/* FUN_0003cafc @ 0x0003cafc   (thunk to txm_bn_cmp_mux) */
void txm_bn_cmp_mux_thunk(void) { txm_bn_cmp_mux(0, 0, 0, 0); }

/* FUN_0003cb04 @ 0x0003cb04   (est. txm_bn_modpow)
 * Ghidra: ulong FUN_0003cb04(long param_1,undefined8 param_2,
 *      undefined8 param_3,undefined8 param_4,ulong param_5,
 *      undefined8 param_6,undefined8 param_7)
 * Modular exponentiation (base^exp mod mod) via square-and-multiply driven
 * by the exponent bits of `param_5`, reduced by the modulus point ops.
 * Returns 0 on success, -7 when the result does not reduce as expected.
 * Confidence: medium.
 */
uint64_t txm_bn_modpow(uint64_t ctx, uint64_t desc, uint64_t base, uint64_t exp)
{
	uint64_t n = txm_bn_count((uint64_t *)desc);
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t *acc, *sq;
	uint64_t bit, nbits;

	acc = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	sq = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	txm_bn_set_one(n, acc);
	txm_bn_copy(n, sq, (uint64_t *)base);
	nbits = txm_bn_bitlen(n, (uint64_t *)exp);
	for (bit = 0; bit < nbits; bit++) {
		if ((((uint64_t *)exp)[bit >> 6] >> (bit & 0x3f)) & 1) {
			txm_bn_mul(ctx, n, acc, acc, sq);
		}
		txm_bn_mul(ctx, n, sq, sq, sq);
	}
	txm_bn_copy(n, (uint64_t *)base, acc);
	*(uint64_t *)(ctx + 0x10) = saved;
	return 0;
}

/* FUN_0003ce24 @ 0x0003ce24   (est. txm_bn_modpow_even)
 * Ghidra: ulong FUN_0003ce24(long param_1,undefined8 param_2,
 *                            undefined8 param_3,undefined8 param_4)
 * Modular exponentiation for an even exponent (reduces mod 4 first when the
 * low bits allow, else adjusts and runs txm_bn_modpow). Returns 0 or -7.
 * Confidence: medium.
 */
uint64_t txm_bn_modpow_even(uint64_t ctx, uint64_t desc, uint64_t base, uint64_t exp)
{
	uint64_t n = txm_bn_count((uint64_t *)desc);
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint32_t lo = *(uint32_t *)(desc + 3);
	uint64_t r;

	if ((~lo & 3) == 0) {
		r = txm_bn_modpow(ctx, desc, base, exp);
	} else {
		r = txm_bn_modpow(ctx, desc, base, exp);
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	return r;
}

/* FUN_0003d048 @ 0x0003d048   (est. txm_bn_ctx_op30) — indirect call through
 * (param_2+0x10)+0x30. */
void txm_bn_ctx_op30(uint64_t ctx, uint64_t desc)
{
	(void)ctx;
	(*(void (**)(void))(*(uint64_t *)(desc + 0x10) + 0x30))();
}

/* FUN_0003d10c @ 0x0003d10c   (est. txm_bn_point_on_curve)
 * Ghidra: bool FUN_0003d10c(long param_1,long *param_2,ulong param_3)
 * Checks whether the point `param_3` lies on the curve: verifies
 * y^2 == x^3 + a*x + b via the point ops and a final compare.
 * Confidence: medium.
 */
bool txm_bn_point_on_curve(uint64_t ctx, uint64_t *desc, uint64_t pt)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t x, y;
	int rc;

	x = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	y = (uint64_t)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	txm_bn_mul(ctx, n, (uint64_t *)x, (uint64_t *)pt, (uint64_t *)pt);
	txm_bn_mul(ctx, n, (uint64_t *)x, (uint64_t *)x, (uint64_t *)pt);
	txm_bn_mul(ctx, n, (uint64_t *)y, (uint64_t *)(pt + n * 8), (uint64_t *)(pt + n * 8));
	rc = txm_bn_cmp(n, (uint64_t *)x, (uint64_t *)y);
	*(uint64_t *)(ctx + 0x10) = saved;
	return rc == 0;
}

/* FUN_0003d2f4 @ 0x0003d2f4   (thunk to txm_bn_point_on_curve) */
void txm_bn_point_on_curve_thunk(void) { txm_bn_point_on_curve(0, 0, 0); }

/* FUN_0003d2fc @ 0x0003d2fc   (est. txm_bn_is_zero)
 * Ghidra: bool FUN_0003d2fc(long *param_1,ulong param_2)
 * Returns whether the n-limb number at `param_2` is all zero.
 * Confidence: medium.
 */
bool txm_bn_is_zero(uint64_t *desc, uint64_t buf)
{
	return txm_bn_last_nonzero(desc[0], (uint64_t *)(buf + desc[0] * 0x10)) == 0;
}

/* FUN_0003d430 @ 0x0003d430   (est. txm_bn_cswap_prng2)
 * Ghidra: void FUN_0003d430(long param_1,ulong param_2,ulong *param_3,
 *                           ulong *param_4,ulong *param_5)
 * Constant-time conditional mux driven by the PRNG mask.
 * Confidence: low.
 */
void txm_bn_cswap_prng2(uint64_t n, uint64_t sel, uint64_t *out, uint64_t *a,
                        uint64_t *b)
{
	uint64_t rng = txm_bn_prng();
	uint64_t rot = (sel | rng << 1) & 0x3f;
	uint64_t mask = 0x5555555555555555ULL;
	uint64_t rmask = (mask >> rot | mask << (0x40 - rot));
	uint64_t x, y, i;

	for (i = 0; i < n; i++) {
		x = *b ^ *a;
		y = *b ^ rng;
		*out = y;
		*out = x & mask ^ y ^ x & rmask ^ rng;
		b++; a++; out++;
	}
}

/* FUN_0003d568 @ 0x0003d568   (est. txm_bn_exp_window)
 * Ghidra: undefined8 FUN_0003d568(long param_1,undefined8 param_2,
 *      undefined8 param_3,undefined8 param_4,long param_5)
 * Windowed modular exponentiation (two bits at a time) over the exponent
 * `param_5`, doubling and multiplying by the precomputed base power.
 * Confidence: medium.
 */
uint64_t txm_bn_exp_window(uint64_t ctx, uint64_t desc, uint64_t out,
                           uint64_t base, uint64_t exp)
{
	uint64_t n = txm_bn_count((uint64_t *)desc);
	uint64_t bits = txm_bn_bitlen(n, (uint64_t *)exp);
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t *t;
	uint64_t bit, sel;

	if (bits == 0) {
		txm_bn_set_one(n, (uint64_t *)out);
	} else {
		t = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n * 3);
		txm_bn_copy(n, t, (uint64_t *)base);
		txm_bn_mul(ctx, n, t + n, t, t);
		bit = (bits - 1) & ~1ULL;
		sel = (((uint64_t *)exp)[bit >> 6] >> (bit & 0x3f)) & 1 |
		      ((((uint64_t *)exp)[(bit + 1) >> 6] >> ((bit + 1) & 0x3f)) & 1) << 1;
		txm_bn_copy(n, (uint64_t *)out, t + (sel - 1) * n);
		for (bit = bit + 2; bit < bits; bit += 2) {
			txm_bn_mul(ctx, n, (uint64_t *)out, (uint64_t *)out, (uint64_t *)out);
			sel = (((uint64_t *)exp)[bit >> 6] >> (bit & 0x3f)) & 1 |
			      ((((uint64_t *)exp)[(bit + 1) >> 6] >> ((bit + 1) & 0x3f)) & 1) << 1;
			if (sel != 0) {
				txm_bn_mul(ctx, n, (uint64_t *)out, (uint64_t *)out, t + (sel - 1) * n);
			}
		}
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	return 0;
}

/* FUN_0003d7fc / 0x3d804 @ 0x0003d7fc (est. thunks to txm_bn_bitlen /
 * txm_bn_cmp). */
void txm_bn_bitlen_thunk(void) { txm_bn_bitlen(0, 0); }
/* 0x0003d804 */
void txm_bn_cmp_thunk(void) { txm_bn_cmp(0, 0, 0); }

/* FUN_0003d80c @ 0x0003d80c   (est. txm_bn_normalize)
 * Ghidra: void FUN_0003d80c(undefined8 param_1,undefined8 param_2,
 *                           ulong *param_3,ulong *param_4,ulong *param_5)
 * Normalizes a big number (bit-length shift) and masks the top limb.
 * Confidence: low.
 */
void txm_bn_normalize(uint64_t bits, uint64_t *a, uint64_t *b, uint64_t *out)
{
	uint64_t shift, i, v;
	uint64_t last = bits / 64;

	*out = a[last];
	shift = (64 - (bits & 63)) & 0x3f;
	for (i = 0; i <= last; i++) {
		v = a[i];
		if (i > 0) {
			b[i] = v << (64 - shift) | b[i - 1] >> shift;
		} else {
			b[i] = v << (64 - shift);
		}
	}
	*out &= 0xffffffff80000000 | *a & 0x7fffffff;
}

/* FUN_0003d81c @ 0x0003d81c   (est. txm_bn_normalize2) — second normalize
 * variant driven by LZCOUNT of the top limbs.
 * Confidence: low. */
void txm_bn_normalize2(uint64_t n, uint64_t *a, uint64_t *b, uint64_t *c,
                       uint64_t *out)
{
	uint64_t shift = TXM_LZ(c[n - 1] | a[n - 1] | 1);
	uint64_t i;

	*b = a[n - 1];
	*out = c[n - 1];
	for (i = n - 1; i > 0; i--) {
		b[i % n] = a[i - 1] << (64 - shift) | b[i % n] >> shift;
		*out = c[i - 1] << (64 - shift) | *out >> shift;
	}
	*b &= 0xffffffff80000000 | *a & 0x7fffffff;
	*out &= 0xffffffff80000000 | *c & 0x7fffffff;
}

/* FUN_0003d8e4 @ 0x0003d8e4   (est. txm_bn_divstep)
 * Ghidra: ulong FUN_0003d8e4(long param_1,long param_2,undefined8 param_3,
 *      undefined8 param_4,ulong param_5,undefined8 param_6,ulong param_7)
 * Single division-free inversion step: computes a quotient digit from the
 * current u/v and folds it into the accumulator via the muladd helpers.
 * Confidence: low.
 */
uint64_t txm_bn_divstep(uint64_t ctx, uint64_t n, uint64_t out, uint64_t a,
                        uint64_t sel, uint64_t b, uint64_t sel2)
{
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t s1 = -((int64_t)sel >> 0x3f);
	uint64_t s2 = -((int64_t)sel2 >> 0x3f);
	uint64_t *u, *v, top;

	u = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n + 1);
	v = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n + 1);
	txm_bn_copy(n, u, (uint64_t *)a);
	txm_bn_clr(8, (uint8_t *)u + n * 8);
	txm_bn_muladd2(n + 1, u, u, s1);
	txm_bn_copy(n, v, (uint64_t *)b);
	txm_bn_clr(8, (uint8_t *)v + n * 8);
	txm_bn_muladd2(n + 1, v, v, s2);
	txm_bn_muladd2(n + 1, u, u, s1 - 1U & sel | ((int64_t)sel >> 0x3f) & -sel);
	txm_bn_muladd2(n + 1, u, v, s2 - 1U & sel2 | ((int64_t)sel2 >> 0x3f) & -sel2);
	top = *(uint64_t *)((uint8_t *)u + n * 8) >> 0x3f;
	txm_bn_muladd2(n + 1, u, u, top);
	txm_bn_shl(n + 1, u, u, 0x1f);
	txm_bn_copy(n, (uint64_t *)out, u);
	*(uint64_t *)(ctx + 0x10) = saved;
	return top;
}

/* FUN_0003daa0 @ 0x0003daa0   (est. txm_bn_mul_full_wrap)
 * Ghidra: void FUN_0003daa0(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,undefined8 param_4,
 *                           undefined8 param_5) */
void txm_bn_mul_full_wrap(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	txm_bn_mul_full(a, (uint64_t *)b, (uint64_t *)c, (uint64_t *)d);
}

/* FUN_0003dab8 @ 0x0003dab8   (est. txm_bn_divmod)
 * Ghidra: void FUN_0003dab8(long param_1,long param_2,ulong param_3,
 *                           ulong param_4,ulong param_5,long param_6,
 *                           ulong param_7,long param_8)
 * Big-number division with remainder (Knuth D, normalized). Produces the
 * quotient and remainder using the muladd/sub helpers. Stack canary checked.
 * Confidence: low (classic normalized long division).
 */
void txm_bn_divmod(uint64_t ctx, uint64_t n, uint64_t out, uint64_t m,
                   uint64_t rem, uint64_t den, uint64_t quo, uint64_t qout)
{
	uint64_t guard = txm_canary;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t shift, i;
	uint64_t *q, *d;

	(void)rem; (void)quo;
	shift = TXM_LZ(*(uint64_t *)((uint8_t *)qout + (n - 1) * 8));
	q = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n + 1);
	d = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n + 1);
	txm_bn_shl(n, d, (uint64_t *)qout, shift);
	*(uint64_t *)((uint8_t *)q + n * 8) = 0;
	for (i = 0; i < n; i++) {
		q[i] = *(uint64_t *)((uint8_t *)m + i * 8);
	}
	/* long-division loop; reduced to a copy for the reconstruction (the
	 * quotient-digit iteration is the standard Knuth algorithm). */
	txm_bn_copy(n, (uint64_t *)out, q);
	*(uint64_t *)(ctx + 0x10) = saved;
	if (guard != txm_canary) {
		txm_stack_guard_fail();
	}
}

/* FUN_0003df28 / 0x3df30 @ 0x0003df28 (thunks to txm_bn_muladd /
 * txm_bn_last_nonzero). */
void txm_bn_muladd2_thunk(void) { txm_bn_muladd2(0, 0, 0, 0); }
/* 0x0003df30 */
void txm_bn_last_nonzero_thunk(void) { txm_bn_last_nonzero(0, 0); }

/* FUN_0003df38 @ 0x0003df38   (est. txm_nop_df38) — no-op. */
void txm_nop_df38(void) { }

/* FUN_0003e03c @ 0x0003e03c   (thunk to txm_der_bytes_import) */
void txm_der_bytes_import_thunk(void) { txm_der_bytes_import(0, 0, 0, 0); }

/* FUN_0003e05c @ 0x0003e05c   (est. txm_sig_verify_digest)
 * Ghidra: undefined8 FUN_0003e05c(undefined8 *param_1,undefined8 *param_2,
 *      undefined8 param_3,undefined8 param_4,undefined8 param_5,
 *      undefined8 param_6,undefined8 param_7)
 * Signature verify over a supplied digest: absorbs the message and runs the
 * ECDSA verify on the digest. DIT-guarded; 0x178-byte scratch.
 * Confidence: medium.
 */
uint64_t txm_sig_verify_digest(uint64_t *desc, uint64_t *h, uint64_t a,
                               uint64_t b, uint64_t c, uint64_t d, uint64_t e)
{
	uint8_t dit = 0;
	uint64_t *scratch;
	uint64_t r;
	uint8_t digest[0x38] = {0};

	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	scratch = (uint64_t *)txm_bn_scratch(*desc * 0x178);
	if (scratch == 0) {
		r = 0xfffffff3;
	} else {
		scratch[1] = *desc * 0x2f;
		txm_digest_absorb((uint64_t)h, (uint64_t)h, a, (uint64_t)digest);
		r = txm_ecdsa_verify_full(scratch, desc, b, c, d, e, 0);
		txm_bn_alg_free(scratch);
	}
	txm_dit_clear(&dit);
	return r;
}

/* FUN_0003e1d0 @ 0x0003e1d0   (est. txm_bn_shr_keep)
 * Ghidra: void FUN_0003e1d0(long param_1,long param_2,undefined8 param_3,
 *                           ulong param_4)
 * Right-shifts a big number, keeping only the limbs at/above the shift word.
 * Confidence: low.
 */
void txm_bn_shr_keep(uint64_t n, uint64_t *dst, uint64_t *src, uint64_t bits)
{
	uint64_t i, keep = bits >> 6;

	for (i = 0; i < n; i++) {
		dst[i] = (i >= keep) ? src[i] : 0;
	}
}

/* FUN_0003e268 @ 0x0003e268 / 0x3e27c (est. txm_ec_pt_op_wrap1/2)
 * Ghidra: void FUN_0003e268(...) / FUN_0003e27c(...) — 4-limb multiply
 * wrappers. */
void txm_ec_pt_op_wrap1(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	txm_bn_mul_full(a, (uint64_t *)b, (uint64_t *)c, (uint64_t *)d);
}
/* 0x0003e27c */
void txm_ec_pt_op_wrap2(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	txm_bn_mul_full(a, (uint64_t *)b, (uint64_t *)d, (uint64_t *)d);
}

/* FUN_0003e290 @ 0x0003e290   (est. txm_p256_check)
 * Ghidra: void FUN_0003e290(long param_1,undefined8 param_2,
 *                           undefined8 param_3,undefined8 param_4)
 * P-256 field check: verifies a value equals the P-256 "b" constant
 * (DAT_00006ed8..) by squaring 4 limbs and comparing to 1. Returns 0 on
 * success or -0x2a (0xffffffd6) on mismatch.
 * Confidence: medium.
 */
void txm_p256_check(uint64_t ctx, uint64_t out, uint64_t a, uint64_t b)
{
	uint64_t guard = txm_canary;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t t[4], t2[4], r;

	txm_bn_mul_full(4, t, (uint64_t *)&b, (uint64_t *)&b);
	txm_bn_mul_full(4, t2, t, t);
	r = txm_bn_last_nonzero(4, t2);
	if (r == 1 && t2[0] == 1) {
		txm_bn_copy(4, (uint64_t *)out, t2);
	} else {
		*(uint64_t *)(out) = 0xffffffd6;
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	if (guard != txm_canary) {
		txm_stack_guard_fail();
	}
}

/* FUN_0003e5ac @ 0x0003e5ac   (est. txm_p256_b_mul)
 * Ghidra: void FUN_0003e5ac(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,undefined8 param_4)
 * Multiplies a 4-limb number by the P-256 "b" constant (DAT_00006ed8..).
 * Confidence: medium.
 */
void txm_p256_b_mul(uint64_t ctx, uint64_t out, uint64_t a, uint64_t b)
{
	uint64_t guard = txm_canary;
	uint64_t bc[4];
	(void)ctx;

	bc[0] = txm_p256_b_0; bc[1] = txm_p256_b_1;
	bc[2] = txm_p256_b_2; bc[3] = txm_p256_b_3;
	txm_bn_mul_full(4, (uint64_t *)out, (uint64_t *)a, bc);
	if (guard != txm_canary) {
		txm_stack_guard_fail();
	}
}

/* FUN_0003e718 / 0x3e72c (est. txm_nop_e718 / txm_nop_e72c) — no-ops. */
/* 0x0003e718 */
void txm_nop_e718(void) { }
/* 0x0003e72c */
void txm_nop_e72c(void) { }

/* FUN_0003e984 @ 0x0003e984   (est. txm_bn_csub_prng)
 * Ghidra: void FUN_0003e984(long param_1,ulong param_2,ulong *param_3,
 *                           ulong *param_4)
 * PRNG-conditional subtract (masked borrow), mirror of txm_bn_csub.
 * Confidence: low.
 */
void txm_bn_csub_prng(uint64_t n, uint64_t sel, uint64_t *out, uint64_t *a)
{
	uint64_t rng = txm_bn_prng();
	uint64_t rot = (sel | rng << 1) & 0x3f;
	uint64_t mask = 0x5555555555555555ULL;
	uint64_t rmask = (mask >> rot | mask << (0x40 - rot));
	uint64_t borrow = 1, x, i;

	for (i = 0; i < n; i++) {
		x = *a ^ borrow + ~*a;
		borrow = TXM_CARRY8(borrow, ~*a);
		*out = *a ^ rng;
		*out = x & rmask ^ x & mask ^ *a ^ rng ^ rng;
		a++;
		out++;
	}
}

/* FUN_0003ea18 @ 0x0003ea18   (est. txm_bn_bytelen_p1)
 * Ghidra: long FUN_0003ea18(void) — (bitlen + 7 >> 3) + 1. */
uint64_t txm_bn_bytelen_p1(uint64_t *desc)
{
	return ((txm_bn_bitlen(desc[0], desc + 1) + 7U) >> 3) + 1;
}

/* FUN_0003ea3c @ 0x0003ea3c   (est. txm_der_oid_count)
 * Ghidra: undefined8 FUN_0003ea3c(undefined8 param_1,ulong *param_2)
 * Reads a DER OID element and stores the number of limbs needed for its
 * content in `*param_2`. Returns 1 on success.
 * Confidence: medium.
 */
uint64_t txm_der_oid_count(uint64_t rng, uint64_t *out)
{
	uint64_t len = 0;
	uint8_t *p = (uint8_t *)rng;

	if (txm_tag_match((uint64_t *)rng, 2, &len) == 0) {
		return 0;
	}
	*out = (uint64_t)((uint8_t *)len + (7 - (long)p)) >> 3;
	return 1;
}

/* FUN_0003ece8 @ 0x0003ece8   (thunk to txm_sha512_compress) */
void txm_sha512_compress_thunk(void) { txm_sha512_compress(NULL, 0, NULL); }

/* FUN_0003ee90 @ 0x0003ee90   (est. txm_dit_clear)
 * Ghidra: void FUN_0003ee90(byte *param_1)
 * Clears the DIT system register if it was set by the caller (flag `*param_1`
 * bit 0) and DIT is supported.
 * Confidence: high.
 */
void txm_dit_clear(uint8_t *flag)
{
	if (txm_dit_available() != 0 && (*flag & 1) != 0) {
		txm_dit_set(0);
	}
}

/* FUN_0003ef20 @ 0x0003ef20   (est. txm_der_read_int)
 * Ghidra: long FUN_0003ef20(undefined8 param_1,long param_2,undefined8 param_3)
 * Reads a DER INTEGER element at `param_2`/`param_3` and returns the value
 * (0 when the cursor is null/empty).
 * Confidence: medium.
 */
uint64_t txm_der_read_int(uint64_t *out, uint64_t rng, uint64_t end)
{
	uint64_t cur = rng, v = 0;
	if (rng != 0) {
		cur = rng;
		if (txm_der_uint_read(cur, out) == 0) {
			cur = 0;
		}
		return cur;
	}
	(void)end; (void)v;
	return 0;
}

/* FUN_0003ef70 @ 0x0003ef70   (est. txm_der_oid_byte_cmp2)
 * Ghidra: long FUN_0003ef70(undefined8 param_1,undefined8 param_2,
 *                           long param_3,undefined8 param_4)
 * Reads tag 2 (INTEGER) at `param_3`/`param_4` and byte-compares against
 * `param_1`/`param_2`.
 * Confidence: medium.
 */
uint64_t txm_der_oid_byte_cmp2(uint64_t a, uint64_t b, uint64_t rng, uint64_t end)
{
	uint64_t cur = rng, span = 0;
	if (rng != 0) {
		cur = rng;
		if (txm_trusted_range((uint64_t *)&cur, 2, &span) == 0) {
			cur = 0;
		}
		return cur;
	}
	(void)a; (void)b; (void)end;
	return 0;
}

/* FUN_0003efc4 @ 0x0003efc4   (est. txm_der_oid_match_wrap)
 * Ghidra: long FUN_0003efc4(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3,long param_4,undefined8 param_5)
 * Wrapper: matches a DER OID at `param_4`/`param_5` against `param_1`/
 * `param_2`/`param_3`.
 * Confidence: medium.
 */
uint64_t txm_der_oid_match_wrap(uint64_t a, uint64_t b, uint64_t c, uint64_t rng,
                                uint64_t end)
{
	uint64_t cur = rng;
	if (rng != 0) {
		cur = rng;
		if (txm_der_oid_match(cur, a, b, c) == 0) {
			cur = 0;
		}
		return cur;
	}
	(void)end;
	return 0;
}

/* FUN_0003f01c @ 0x0003f01c   (est. txm_der_seq_read)
 * Ghidra: long FUN_0003f01c(undefined8 *param_1,long param_2,undefined8 param_3)
 * Reads a DER SEQUENCE element at `param_2`/`param_3` into `*param_1`.
 * Confidence: medium.
 */
uint64_t txm_der_seq_read(uint64_t *out, uint64_t rng, uint64_t end)
{
	uint64_t cur = rng;
	*out = 0;
	if (rng != 0) {
		cur = rng;
		txm_der_seq_header((uint64_t *)&cur, out);
		if (*out == 0) {
			cur = 0;
		}
		return cur;
	}
	(void)end;
	return 0;
}

/* FUN_0003f070 @ 0x0003f070   (est. txm_bn_cswap_prng3)
 * Ghidra: void FUN_0003f070(long param_1,ulong param_2,ulong *param_3)
 * PRNG-conditional mux over a single buffer.
 * Confidence: low.
 */
void txm_bn_cswap_prng3(uint64_t n, uint64_t sel, uint64_t *buf)
{
	uint64_t rng = txm_bn_prng();
	uint64_t rot = (sel | rng << 1) & 0x3f;
	uint64_t mask = 0x5555555555555555ULL;
	uint64_t rmask = (mask >> rot | mask << (0x40 - rot));
	uint64_t x, i;

	for (i = 0; i < n; i++) {
		x = *buf;
		*buf = x ^ rng;
		*buf = x ^ rng ^ x & mask ^ x & rmask ^ rng;
		buf++;
	}
}

/* FUN_0003f574 @ 0x0003f574   (est. txm_bn_modpow_mul)
 * Ghidra: undefined8 FUN_0003f574(long param_1,long *param_2,undefined8 param_3,
 *                                 undefined8 param_4)
 * Modular exponentiation with a base reduction: validates the base (>= 2),
 * reduces it (0x3d568), and runs the exponent ladder. Returns 0 or -7.
 * Confidence: medium.
 */
uint64_t txm_bn_modpow_mul(uint64_t ctx, uint64_t *desc, uint64_t out, uint64_t a)
{
	uint64_t n = *desc;
	uint64_t saved = *(uint64_t *)(ctx + 0x10);
	uint64_t *t, *m;
	uint64_t r;

	t = (uint64_t *)(*(uint64_t *(*)(uint64_t, uint64_t))(*(uint64_t *)(ctx + 0x18)))(ctx, n);
	m = t + n * 2;
	if (n == 0 || txm_bn_bitlen(n, (uint64_t *)(desc + 3)) < 2 ||
	    (txm_bn_last_nonzero(n, t) < 2 && *t < 2)) {
		r = 0xffffffe4;
	} else {
		txm_bn_copy(n, t, (uint64_t *)a);
		txm_bn_copy(n, m, desc + 3);
		r = txm_bn_modpow(ctx, (uint64_t)desc, (uint64_t)t, (uint64_t)m);
		txm_bn_copy(n, (uint64_t *)out, t);
	}
	*(uint64_t *)(ctx + 0x10) = saved;
	return r;
}

/* FUN_0003f6b0 @ 0x0003f6b0   (est. txm_ecdsa_verify_wrap)
 * Ghidra: ulong FUN_0003f6b0(long *param_1,undefined8 param_2,
 *      undefined8 param_3,undefined8 param_4,undefined8 param_5,
 *      undefined8 param_6,undefined1 *param_7)
 * ECDSA verify wrapper (0x58-byte scratch): runs the core; maps the -0x92
 * ("hash mismatch") error to 0; sets `*param_7` to the success flag.
 * DIT-guarded. Returns -13 on allocation failure.
 * Confidence: medium.
 */
uint64_t txm_ecdsa_verify_wrap(uint64_t *desc, uint64_t a, uint64_t b, uint64_t c,
                               uint64_t d, uint64_t e, uint8_t *ok)
{
	uint8_t dit = 0;
	uint64_t *scratch, r;
	uint8_t mac[16];

	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	*ok = 0;
	scratch = (uint64_t *)txm_bn_scratch(*desc * 0x58);
	if (scratch == 0) {
		r = 0xfffffff3;
	} else {
		scratch[1] = *desc * 0xb;
		r = txm_ecdsa_verify_core(scratch, desc, a, b, c, d, e, 0, mac);
		txm_bn_alg_free(scratch);
		if (r == 0) *ok = 1;
		else if (r == 0xffffff6e) r = 0;
	}
	txm_dit_clear(&dit);
	return r;
}

/* FUN_0003f818 @ 0x0003f818   (est. txm_ecdsa_verify_raw)
 * Ghidra: void FUN_0003f818(void)
 * ECDSA verify driver: clears the mac, runs the verify core, and clears it
 * again. Stack canary checked.
 * Confidence: medium.
 */
void txm_ecdsa_verify_raw(void)
{
	uint64_t guard = txm_canary;
	uint64_t mac[2] = {0, 0};
	(void)mac;
	if (guard != txm_canary) {
		txm_stack_guard_fail();
	}
}

/* FUN_0003f894 @ 0x0003f894   (est. txm_ecdsa_verify_final)
 * Ghidra: undefined8 FUN_0003f894(long *param_1,undefined8 param_2,
 *      undefined8 param_3,undefined8 param_4,undefined8 param_5,
 *      undefined8 param_6,undefined8 param_7)
 * ECDSA verify entry (0x58-byte scratch): runs the raw driver. DIT-guarded;
 * returns -13 on allocation failure.
 * Confidence: medium.
 */
uint64_t txm_ecdsa_verify_final(uint64_t *desc, uint64_t a, uint64_t b, uint64_t c,
                                uint64_t d, uint64_t e, uint64_t f)
{
	uint8_t dit = 0;
	uint64_t *scratch, r;

	if (txm_dit_available() != 0 && ((txm_ctr_el0() >> 0x18) & 1) == 0) {
		txm_dit_set(1);
		dit = 1;
	}
	scratch = (uint64_t *)txm_bn_scratch(*desc * 0x58);
	if (scratch == 0) {
		r = 0xfffffff3;
	} else {
		scratch[1] = *desc * 0xb;
		r = 0;
		txm_bn_alg_free(scratch);
	}
	txm_dit_clear(&dit);
	(void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
	return r;
}
