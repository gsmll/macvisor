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
extern void txm_bn_mul(uint64_t *ctx, uint64_t *desc, uint64_t *out,
                       uint64_t *a, uint64_t *b);           /* FUN_00043650 */
extern void txm_bn_add(uint64_t *ctx, uint64_t *desc, uint64_t *out,
                       uint64_t *a, uint64_t *b);           /* FUN_000438e0 */
extern void txm_bn_sub(uint64_t *ctx, uint64_t *desc, uint64_t *out,
                       uint64_t *a, uint64_t *b);           /* FUN_0004398c */
extern void txm_bn_op(uint64_t *ctx, uint64_t *desc, uint64_t *out,
                      uint64_t *a, uint64_t *b);            /* FUN_00042d90 */
extern void txm_bn_op2(uint64_t *ctx, uint64_t *desc, uint64_t *out,
                       uint64_t *a, uint64_t *b);           /* FUN_00042da4 */
extern void txm_bn_clr(uint64_t bytes, void *dst);          /* FUN_00042ab0 */
extern uint64_t txm_bn_count(uint64_t *desc);               /* FUN_00042b78 */
extern uint64_t txm_bn_bitlen(uint64_t *desc);              /* FUN_00042b84 */
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
extern uint64_t txm_der_bytes_import(uint64_t n, uint64_t a, uint64_t b); /* FUN_0003df58 */

/* Big-number PRNG (xorshift on DAT_00070040), FUN_0003d498. */
extern uint64_t txm_bn_prng(void);
/* 4-bit window comparison table (DAT_00006e60). */
extern const uint8_t txm_bn_win_tbl[0x20];

/* Digest algorithm name structs (static tables). */
extern const void *txm_alg_name_c0;   /* DAT_000110a8 */
extern const void *txm_alg_name_e0;   /* DAT_000114e0 */
extern const void *txm_alg_name_209;  /* DAT_000111f8 */
extern const void *txm_alg_name_100;  /* FUN_00040c1c */
extern const void *txm_alg_name_180;  /* FUN_00043d00 */

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
int txm_policy_rule_02(uint64_t *ctx);
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
uint64_t txm_bn_prng(void);
extern uint64_t txm_bn_prng_state;    /* DAT_00070040 */
uint64_t txm_bn_modulus_ptr(uint64_t desc);
uint64_t txm_bn_sub_const(uint64_t n, uint64_t *out, uint64_t *a, uint64_t k);
uint64_t txm_bn_exp_window(uint64_t ctx, uint64_t desc, uint64_t out,
                           uint64_t base, uint64_t exp);
void txm_bn_copy(uint64_t n, uint64_t *dst, uint64_t *src);
void txm_der_oid_read(uint64_t rng, uint64_t *out);
bool txm_der_oid_byte_match(uint64_t *rng, uint64_t a, uint64_t b);
uint64_t txm_der_uint_read(uint64_t rng, uint64_t *out);
uint64_t txm_der_oid_match(uint64_t rng, uint64_t a, uint64_t b, uint64_t c);



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
 * +0x108) it computes the code-region digest from ctx[6]/ctx[7]
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
	txm_range_kind(ctx[6], ctx[7], &scratch);
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
	uint32_t st = txm_range_check(ctx[6], ctx[7], 0, 0, &kind); /* FUN_00033c9c */
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
	txm_range_kind(ctx[6], ctx[7], &hi);
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
	uint32_t st = txm_range_check(ctx[6], ctx[7], 0, 0, &kind_hi);

	if ((st & 0xff00) != 0) {
		return 0x124a7u;
	}
	if ((kind_hi & 1) != 0) {
		return 0x22ea7u;
	}
	if (txm_policy_trust2(ctx) != 0) {        /* FUN_00034b30 */
		return 0x330a7u;
	}
	txm_buf_digest(ctx[6], ctx[7], 0, &kind);
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
	uint32_t st = txm_range_check(ctx[6], ctx[7], 0, 0, &kind);
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

	txm_buf_fill(ctx[6], ctx[7], &kind, 0);
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
	txm_range_kind(ctx[6], ctx[7], &name);

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
int txm_policy_rule_02(uint64_t *ctx)
{
	uint64_t trust = txm_policy_trust();
	uint64_t vtable = ctx[0];

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

	txm_range_kind2(ctx[6], ctx[7], &flag);
	txm_range_kind(ctx[6], ctx[7], &name);
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
	st = txm_region_resolve(ctx[1], ctx[2], ctx + 3);   /* FUN_00032630 */
	if ((st & 0xff00) != 0) {
		return (uint64_t *)(uint64_t)st;
	}
	st = txm_region_resolve2(ctx[0], ctx[3], ctx[4], ctx + 6); /* FUN_00033d40 */
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
		uint32_t c = txm_range_check(ctx[6], ctx[7], 0, 0, &kind);
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
	txm_region_policy_commit(ctx, ctx[6], ctx[7]);  /* FUN_00035d24 */
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
	txm_region_digest(kind, base, size & 0xffffffff, digest);  /* FUN_000325b0 */
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
	span = ctx[2] - (uint64_t)*(uint32_t *)(ctx + 4);
	if (span == 0) {
		return 0x32315u;
	}
	base = ctx[1];
	end = base + ctx[2];
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
	base = ctx[3];
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
	if ((uint64_t)ctx[2] < end) {
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
				txm_page_hash(ctx[3], ctx[4], 0, 0xfade0c02, &pginfo);
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
				    (ctx[4] = start, end <= (uint64_t)ctx[2])) {
					ctx[2] = end;
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
	txm_range_check(ctx[6], ctx[7], 0, 0, &f1);
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
		txm_range_kind(ctx[6], ctx[7], &k1);
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
	uint64_t saved = ctx[2];                       /* +0x10 */
	uint64_t *scratch = (*(uint64_t *(*)(uint64_t *, uint64_t))(ctx[3]))(ctx, n); /* +0x18 alloc */
	uint64_t mod = txm_bn_modulus_ptr(b);          /* FUN_000372f8 */
	uint64_t r;

	if (txm_bn_sub_const(n, scratch, (uint64_t *)mod, 2) == 0) {
		r = txm_bn_exp_window((uint64_t)ctx, (uint64_t)b, c, d, (uint64_t)scratch);
	} else {
		r = 0xffffffff;
	}
	ctx[2] = saved;
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
	win[0] = (uint8_t)((((limbs[(bits - 1 >> 6)] >> (bits - 1 & 0x3f)) & 1) << 3) |
	                   (((limbs[(bits - 2 >> 6)] >> (bits - 2 & 0x3f)) & 1) << 2) |
	                   (((limbs[(bits - 3 >> 6)] >> (bits - 3 & 0x3f)) & 1) << 1) |
	                   (((limbs[(bits - 4 >> 6)] >> (bits - 4 & 0x3f)) & 1)));
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
	if (n0 < (uint8_t)(&txm_bn_win_tbl)[n1]) {
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
void txm_trusted_range(uint64_t *rng, uint64_t tag, uint64_t *out)
{
	uint64_t len = 0, start = 0;
	if (txm_tag_match((uint64_t *)rng, tag, &len) != 0) {
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
void txm_der_oid_read(uint64_t rng, uint64_t *out)
{
	txm_trusted_range((uint64_t *)rng, 0x2000000000000010ULL, out);
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
	return txm_der_bytes_import(end - p, a, b) == 0;
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
	txm_range_kind2(ctx[6], ctx[7], &flag);
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
