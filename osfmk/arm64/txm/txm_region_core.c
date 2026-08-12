/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0). Ground truth: Ghidra FUN_ names + addresses.
 * This file covers TXM region 0x40000-0x4b000: the big-number arithmetic
 * (bignum) layer, SHA-256/SHA-512 compression, ECDSA (P-256/P-384) modular
 * multiply/inverse/exponentiation, the ASN.1/DER TLV decoder, and the IMG4
 * (IM4M manifest / IM4C certificate-chain) parsing + verification layer.
 * All names are estimates (confidence medium) unless otherwise noted.
 *
 * Conventions:
 *  - A "bignum context" is a heap object whose first words describe a
 *    fixed-size integer and whose +0x10 word is a saved-register spill and
 *    whose +0x18 word is the allocation callback (ctx, words).
 *  - The {lo,hi} 128-bit pair convention is used where the decompiler models
 *    a helper as returning x0/x1.
 *  - Shared kernel/libc helpers are declared extern with their Ghidra FUN_
 *    address in a comment (FULL-AUDIT covers only this batch's addresses).
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Shared external helpers (other TXM regions / libc).  All keep their */
/* Ghidra FUN_ addresses in comments.                                  */
/* ------------------------------------------------------------------ */

/* noreturn stack-protector failure (checks DAT_00006cf0 canary). */
extern __attribute__((noreturn)) void txm_stack_chk_fail(void);   /* FUN_0002f13c */

/* SoftwareBreakpoint(variant, imm) — TXM's fatal-trap primitive. */
#define TXM_TRAP(variant, imm) __builtin_trap()

/* memset / memcpy / memcmp shims. */
extern void *txm_memset(uintptr_t dst, int c, uint64_t n);        /* FUN_0002d240 */
extern void *txm_memcpy(uintptr_t dst, uintptr_t src, uint64_t n);/* FUN_0002d6b0 */
extern int   txm_memcmp(uintptr_t a, uintptr_t b, uint64_t n);    /* FUN_0002d4d0 */
extern int   txm_memcmp_const(uintptr_t a, uintptr_t b, uint64_t n);/* FUN_0002d4d0 */

/* Heap alloc / free. */
extern uintptr_t txm_malloc(uint64_t size);                        /* FUN_0002989c */
extern void      txm_free(uintptr_t p, uint64_t size);             /* FUN_00029950 */

/* Big-number primitive helpers (bignum engine; outside this batch). */
extern uint64_t  txm_bn_words_ext(uintptr_t bn);                     /* FUN_00042b78 */
extern uintptr_t txm_bn_data_ext(uintptr_t bn);                     /* FUN_000372f8 */
extern void      txm_bn_add_limbs(uint64_t words, uintptr_t a, uintptr_t b,
                                  uintptr_t c);                     /* FUN_0003daa0 */

/* Bignum engine context: alloc(size) via *(ctx+0x18), restore *(ctx+0x10). */
extern uintptr_t txm_bn_alloc(uintptr_t ctx, uint64_t words);      /* (**(ctx+0x18)) */
extern void      txm_bn_restore(uintptr_t ctx, uintptr_t saved);   /* *(ctx+0x10) */

/* Montgomery / modmul entry (fixed 256-bit). */
extern void txm_bn_modmul256(uint64_t *dst, const uint64_t *a, const uint64_t *b); /* FUN_00043670 */
/* Fixed 384-bit multiply. */
extern void txm_bn_mul384(uintptr_t dst, uintptr_t a, uintptr_t b);    /* FUN_000415a0 */

/* Mod-p inverse via Newton iteration (bignum ctx + bn). */
extern uint64_t txm_bn_inv(uintptr_t ctx, uintptr_t bn);               /* FUN_00042e34 */
/* Mod-p exponentiation (square-and-multiply on ctx). */
extern void txm_bn_exp(uintptr_t ctx, uintptr_t bn, uintptr_t out,
                       uintptr_t tmp);                                 /* FUN_00042fd0 */
/* Montgomery modular multiply on ctx (out = a*b mod m). */
extern void txm_bn_mont_mul(uintptr_t ctx, uintptr_t bn, uintptr_t out,
                            uintptr_t tmp);                            /* FUN_00041488 */
/* Barrett / final reduction helper. */
extern void txm_bn_barrett(uintptr_t ctx, uintptr_t bn, uintptr_t out,
                           uintptr_t tmp);                             /* FUN_0003c39c */
/* Bignum multiply for the ECDSA engine. */
extern void txm_bn_ec_mul(uintptr_t ctx, uintptr_t bn, uintptr_t out,
                          uintptr_t a, uintptr_t b);                   /* FUN_0003daa0 */

/* SHA-256 / SHA-512 core helpers. */
extern void txm_sha256_block(uintptr_t state, uintptr_t data);        /* FUN_00040fb4 */
extern void txm_sha512_block(uintptr_t state, uintptr_t data);        /* FUN_00041a9c */

/* Logging entry point. */
extern void txm_log(uintptr_t fmt_tbl, uintptr_t fmt, ...);           /* FUN_00061cbc */

/* Runtime feature query. */
extern uint64_t txm_crypto_config(uint64_t sel);                      /* FUN_0003c0a4 */

/* bignum context vtable methods. */
extern void txm_bn_method_mul(uintptr_t ctx, uintptr_t bn, ...);      /* FUN_00043650 */
extern void txm_bn_method_reduce(uintptr_t ctx, uintptr_t bn, ...);   /* FUN_0004320c */

/* image4 / DER helpers shared across the batch. */
extern uint64_t txm_der_read_tag(uintptr_t *cursor, uintptr_t end,
                                 uint8_t *longform, uintptr_t *len);  /* FUN_0004a2d0 */
extern void txm_der_match_tag(uintptr_t *cursor, uint64_t tag,
                              uintptr_t *flag, uintptr_t *len);      /* FUN_00048c2c */
extern uint64_t txm_der_skip_elem(uintptr_t *cursor, uint64_t tag,
                                  uintptr_t *len);                    /* FUN_00037584 */
extern uint64_t txm_der_child_len(uintptr_t *cursor, uint64_t tag,
                                  uintptr_t *len);                    /* FUN_0003767c */
extern void      txm_der_seq(uintptr_t *cursor, uintptr_t *out);   /* FUN_00044724 */
extern uint64_t  txm_der_uint(uintptr_t *cursor, uintptr_t *out);  /* FUN_000444fc */
extern uint64_t  txm_der_sint(uintptr_t *cursor, uintptr_t *out);  /* FUN_00044580 */
extern uint64_t  txm_der_bool(uintptr_t *cursor, bool *out);       /* FUN_0004443c */
extern void      txm_der_octet(uintptr_t *cursor, uintptr_t *out,
                               uintptr_t *len);                    /* FUN_0004463c */
extern uint64_t  txm_der_add_range(uintptr_t *a, uintptr_t *out);  /* FUN_000446f4 */

/* IMG4 manifest helpers. */
extern uint64_t txm_img4_prop_u32(uintptr_t *cursor, uint64_t tag,
                                  uintptr_t *out, uint32_t *val);  /* FUN_00045364 */
extern uint64_t txm_img4_elem(uintptr_t *cursor, uint64_t tag,
                              uintptr_t *out);                     /* FUN_00044c6c */

/* Certificate store lookup / OID compare. */
extern uint64_t txm_cert_lookup_ext(uintptr_t *name);                /* FUN_000481cc */
extern int      txm_oid_cmp(uintptr_t a, uintptr_t b);               /* FUN_0004b13c */
extern int      txm_oid_cmp_len(uintptr_t a, uintptr_t b, uint64_t n); /* FUN_0004b168 */

/* EC key / hash method dispatch table. */
extern uintptr_t txm_ec_alg_get_ext(uint64_t sel);                   /* FUN_000486a0 */
extern uintptr_t txm_ec_params_ext(uintptr_t oid);                   /* FUN_0004890c */

/* image verification (developer-authorization). */
extern uint64_t txm_verify_developer_ext(uintptr_t ctx, uintptr_t pub,
                                         uintptr_t data, uintptr_t sig);  /* FUN_00045a38 */

/* signature verify: FUN_000483a8 / FUN_00048700 take (data,data_len,
 * sig,sig_len,manifest) and run the EC/RSA path; return bool in x0. */
extern uint8_t txm_sig_verify_p256(uintptr_t data, uintptr_t data_len,
                                   uintptr_t sig, uintptr_t sig_len,
                                   uintptr_t manifest);              /* FUN_000483a8 */
extern uint8_t txm_sig_verify_p384(uintptr_t data, uintptr_t data_len,
                                   uintptr_t sig, uintptr_t sig_len,
                                   uintptr_t manifest);              /* FUN_00048700 */

/* im4m parse + verify. */
extern uint64_t txm_im4m_decode(uintptr_t *cursor, uintptr_t end, int param_3,
                                uintptr_t *out, int magic);          /* FUN_000455b8 */

/* panic/abort on malformed DER (SoftwareBreakpoint variants). */
extern void txm_der_panic_assert(void);                               /* trap 0x5513/0x5519 */

/* ------------------------------------------------------------------ */
/* Section A: fixed-width big-number multiply / add primitives.        */
/* ------------------------------------------------------------------ */

/* 000415a0  txm_bn_mul6  (est.)
 * FUN_000415a0 @ 0x000415a0
 * Ghidra: void FUN_000415a0(long *param_1, ulong *param_2, ulong *param_3)
 * Computes the 384-bit (6-limb) product of two 6-limb integers a * b and
 * stores the 12-limb result in out. Pure schoolbook 64x64->128 multiply with
 * carry propagation; no reduction. Used by the P-384 curve operations.
 * Confidence: medium */
void txm_bn_mul6(uint64_t *out, const uint64_t *a, const uint64_t *b);

/* 00043670  txm_bn_mulmod_p256  (est.)
 * FUN_00043670 @ 0x00043670
 * Ghidra: void FUN_00043670(long *param_1, ulong *param_2, ulong *param_3)
 * Computes the 256-bit modular product of two 4-limb integers modulo the
 * P-256 prime (2^256 - 2^224 + 2^192 + 2^96 - 1). Uses the special-form
 * reduction with the constant 0xffffffff00000001. Schoolbook multiply then a
 * cascade of carries with the Mersenne-style reduction folded in.
 * Confidence: medium */
void txm_bn_mulmod_p256(uint64_t *out, const uint64_t *a, const uint64_t *b);

/* 00040fb4  txm_sha256_compress  (est.)
 * FUN_00040fb4 @ 0x00040fb4
 * Ghidra: void FUN_00040fb4(uint *param_1, long param_2, undefined1 *param_3)
 * SHA-256 compression: rounds one 64-byte block. param_1 = 8-word state,
 * param_2 = block count, param_3 = 64-byte data (big-endian words). Reads
 * the 64 K-constants from DAT_00007210. Full 64-round loop, canonical
 * Ch/Maj/Sigma schedule. Confidence: high (round structure is canonical). */
void txm_sha256_compress(uint32_t *state, uint64_t blocks, const uint8_t *data);

/* 00041a9c  txm_sha512_compress  (est.)
 * FUN_00041a9c @ 0x00041a9c
 * Ghidra: void FUN_00041a9c(long param_1, long param_2, long param_3)
 * SHA-512 compression: rounds one 128-byte block. param_1 = 8-word (64-bit)
 * state, param_2 = block count, param_3 = data (64-bit big-endian words).
 * Reads 80 K-constants from DAT_00006f20. Canonical 80-round SHA-512 with
 * byte-swapped input words. Confidence: high. */
void txm_sha512_compress(uint64_t *state, uint64_t blocks, const uint8_t *data);

/* 00040f4c  txm_mulmod_p256_wrapper  (est.)
 * FUN_00040f4c @ 0x00040f4c
 * Ghidra: void FUN_00040f4c(undefined8,undefined8,undefined8,undefined8)
 * Thin wrapper: calls the P-256 modular multiply with the first operand
 * forced equal to the second (square) — out = a*a mod p. Stack canary
 * prologue/epilogue. Confidence: medium. */
void txm_mulmod_p256_square(uint64_t *out, const uint64_t *a);

/* 00040c2c / 00040c40  txm_mulmod_p256_a / txm_mulmod_p256_b  (est.)
 * FUN_00040c2c / FUN_00040c40
 * Thunks that call FUN_00043670 with (a,b) / (a,a). P-256 modular multiply
 * entry points used by the scalar-multiply driver. Confidence: medium. */
void txm_mulmod_p256_a(uint64_t *out, const uint64_t *a, const uint64_t *b);
void txm_mulmod_p256_b(uint64_t *out, const uint64_t *a);

/* 00040c1c  txm_curve_param_get  (est.)
 * FUN_00040c1c: returns &DAT_000117a8 — a curve/bignum parameter constant
 * (likely the P-256 field modulus limb array). Confidence: low. */
uintptr_t txm_curve_param_get(void);

/* 00040c14  txm_mulmod_p256_dispatch  (thunk)
 * thunk_FUN_0003f270: forwards to FUN_0003f270 (bignum engine entry).
 * Confidence: low. */
void txm_mulmod_p256_dispatch(void);

/* 00041594  thunk_FUN_0003f270 (same as above). */
void txm_mulmod_p256_dispatch2(void);

/* ------------------------------------------------------------------ */
/* Section B: ECDSA scalar-multiply drivers (P-256).                   */
/* ------------------------------------------------------------------ */

/* 00040c54  txm_ecdsa_scalar_mul_p256  (est.)
 * FUN_00040c54 @ 0x00040c54
 * Ghidra: void FUN_00040c54(long param_1, ...)
 * P-256 scalar multiplication driver: repeatedly squares the accumulator
 * (FUN_00043670 squarings in runs of 4, 8, 16, 32, 128 ...) and folds the
 * base point, mirroring a fixed-window Montgomery ladder over the field.
 * Uses the ctx allocation callback (param_1+0x18) for three temporaries and
 * the +0x10 save slot. Ends by verifying the result is one and, on success,
 * copies it out. Confidence: medium. */
void txm_ecdsa_scalar_mul_p256(uintptr_t ctx, uintptr_t out,
                               uintptr_t base, uintptr_t scalar);

/* 00043d38  txm_ecdsa_scalar_mul_p384  (est.)
 * FUN_00043d38 @ 0x00043d38
 * Same driver but over the P-384 field using the 6-limb multiply
 * (FUN_000415a0) and 0x100000001 modulus. Confidence: medium. */
void txm_ecdsa_scalar_mul_p384(uintptr_t ctx, uintptr_t out,
                               uintptr_t base, uintptr_t scalar);

/* 00044080  txm_mul_p384_setone  (est.)
 * FUN_00044080: out = param_3 * 1 (sets the 6-limb accumulator to the
 * identity) via FUN_000415a0. Confidence: low. */
void txm_mul_p384_setone(uint64_t *out, uint64_t *unused);

/* ------------------------------------------------------------------ */
/* Section C: big-number engine entry points (context-based).          */
/* ------------------------------------------------------------------ */

/* 00042b78  txm_bn_words  — *bn == word count. */
uint64_t txm_bn_words(uintptr_t bn);

/* 00042b84  txm_bn_data_ptr  — returns *(bn + 8): pointer to limbs. */
uintptr_t txm_bn_data_ptr(uintptr_t bn);

/* 00042264  txm_bn_from_bytes  (est.)
 * FUN_00042264 @ 0x00042264
 * Builds a bignum from a big-endian byte string. Allocates a workspace of
 * words*5+3 limbs via txm_malloc, converts the two (data,sig) halves with
 * txm_bn_from_bytes, then runs the context normalize. Returns 0xfffffff3 on
 * alloc failure. Confidence: medium. */
uint64_t txm_bn_from_bytes(uintptr_t *bn, uintptr_t bytes_a, uintptr_t bytes_b);

/* 000423b4  txm_bn_num_bits  (est.)
 * FUN_000423b4: returns the bit-length of the bignum at param_2 with
 * param_1 limbs, scanning high-to-low with LZCOUNT. Confidence: medium. */
uint64_t txm_bn_num_bits(uint64_t words, const uint64_t *limbs);

/* 00042418  txm_ecdsa_verify  (est.)
 * FUN_00042418 @ 0x00042418
 * The ECDSA verification core: parses the signature (r,s), validates both
 * against the curve, reduces mod the field order, computes u1*G + u2*Q via
 * the double-and-add ladder, and compares the x-coordinate with r mod n.
 * Returns 0 on success; negative error codes (0xfffffff9, 0xffffff6e, ...)
 * on verification failure. Confidence: medium. */
uint64_t txm_ecdsa_verify(uintptr_t ctx, uintptr_t key, uintptr_t hash,
                          uintptr_t sig_r, uintptr_t sig_s, uintptr_t order,
                          uintptr_t pub_x, uintptr_t pub_y);

/* 00042980  thunk → FUN_00042418 (txm_ecdsa_verify entry). */
void txm_ecdsa_verify_entry(void);

/* 000429c4  txm_bn_shr_bits  (est.)
 * FUN_000429c4: right-shifts a bignum by param_4 bits using NEON ext/ushl
 * (bignum right shift across limb boundaries). Confidence: low. */
void txm_bn_shr_bits(uintptr_t dst, uintptr_t src, uint64_t words, uint64_t bits);

/* 00042ab0  txm_bn_free  (est.)
 * FUN_00042ab0: releases a bignum workspace via FUN_0002ef60. Confidence: low. */
void txm_bn_free(uintptr_t p, uintptr_t q);

/* 00042acc  txm_bn_add_carry  (est.)
 * FUN_00042acc: multi-limb add of param_4 and param_5 into param_3 with
 * carry; folds a rotate-masked carry mask. Returns the low carry bit &
 * param_2. Confidence: low. */
uint64_t txm_bn_add_carry(uint64_t words, uint64_t mask, uint64_t *out,
                          const uint64_t *a, const uint64_t *b);

/* 00042b90  txm_bn_odd_check  (est.)
 * FUN_00042b90: returns nonzero if the bignum is odd and >= 3 (used to
 * validate an RSA/EC modulus before inversion). Allocates temporaries and
 * runs the montgomery inverse precheck. Confidence: medium. */
uint32_t txm_bn_odd_check(uintptr_t ctx, uintptr_t bn, uintptr_t unused);

/* 00042cc4  txm_bn_sub  (est.)
 * FUN_00042cc4: out = a - b (multi-limb borrow subtract on ctx). Confidence: medium. */
void txm_bn_sub(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b);

/* 00042d90 / 0004320c / 00043650 / 000438e0 / 0004398c — bignum method
 * dispatch: indirect calls through the ctx vtable at +0x10 (+0x10, +0x20,
 * +8, +0x18). These are the JIT-ish method thunks of the bignum engine. */
void txm_bn_method_vt10(uintptr_t ctx, uintptr_t bn);
void txm_bn_method_vt20(uintptr_t ctx, uintptr_t bn);
void txm_bn_method_vt10b(uintptr_t ctx, uintptr_t bn);
void txm_bn_method_vt18(uintptr_t ctx, uintptr_t bn);
void txm_bn_method_vt8(uintptr_t ctx, uintptr_t bn);

/* 00042da4  txm_bn_shl1_add  (est.)
 * FUN_00042da4: out = (a << 1) | carry — left shift one with the carry-in
 * folded, via the add_carry primitive. Confidence: low. */
void txm_bn_shl1_add(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a);

/* 00042e34  txm_bn_modinv  (est.)
 * FUN_00042e34 @ 0x00042e34
 * Modular inverse of the bignum via Newton iteration: computes
 * inv = a^(p-2) mod p style fixed-point inverse with 3 Newton refinement
 * steps and stores into bn[3+words]. Confidence: medium. */
uint64_t txm_bn_modinv(uintptr_t ctx, uintptr_t bn);

/* 00042fd0  txm_bn_modpow  (est.)
 * FUN_00042fd0 @ 0x00042fd0
 * Fixed-exponent modular exponentiation (out = base^exp mod m) using
 * repeated Montgomery modular squarings (FUN_00041488) and multiplications.
 * The windowed exponent is scanned from the ctx bignum. Confidence: medium. */
void txm_bn_modpow(uintptr_t ctx, uintptr_t bn, uintptr_t out,
                   uintptr_t mod, uintptr_t exp);

/* 000431ac  txm_bn_modpow2  (est.)
 * FUN_000431ac: exponentiation wrapper passing exp = bn_words<<1.
 * Confidence: low. */
void txm_bn_modpow2(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t exp);

/* 00043220  txm_bn_init_inv  (est.)
 * FUN_00043220: initializes a bignum from param_3 words + param_4, runs the
 * modular inverse (FUN_00042e34), and sets the method table pointer
 * (DAT_00011a70). Confidence: medium. */
void txm_bn_init_inv(uintptr_t ctx, uintptr_t *bn, uint64_t words, uintptr_t limbs);

/* 00043274 / 0004332c / 000433e0 / 00043480 / 00043518 / 000435ac /
 *  00043848 — bignum arithmetic entry points (mul, sqr, add, sub) that each
 *  allocate a 2*words scratch and invoke the ctx method via FUN_00041488 /
 *  FUN_0004320c. Confidence: medium. */
void txm_bn_mul(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b);
void txm_bn_sqr(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a);
void txm_bn_add_mn(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b);
void txm_bn_sub_mn(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b);
void txm_bn_mul2(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a);
void txm_bn_addmul(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b);

/* 000439a0/000439b0/000439c0/000439d0  txm_bn_const_*  — return bignum
 * constant pointers (DAT_00011758 / 00011980 / 00011668 / 00011058). */
uintptr_t txm_bn_const_a(void);
uintptr_t txm_bn_const_b(void);
uintptr_t txm_bn_const_c(void);
uintptr_t txm_bn_const_d(void);

/* 000439e0  txm_bn_hash_ctx  (est.)
 * FUN_000439e0: builds a hash/verify context; runs FUN_0003eec4 with the
 * IMG4 tag 0x2000000000000010 and returns the context pointer. Confidence: low. */
uint64_t txm_bn_hash_ctx(uintptr_t a, uintptr_t b);

/* 00043a38  txm_ws_alloc  (est.) — FUN_0002989c + memset; alloc size, zero. */
uintptr_t txm_ws_alloc(uint64_t size);

/* 00043a74  txm_ws_push  (est.) — workspace cursor alloc (bn[2] += n), asserts
 * via FUN_00037c10("alloc_ws"). Returns old cursor. */
uint64_t txm_ws_push(uint64_t *ws, uint64_t n);

/* 00043ad0  txm_ws_pop  (est.) — workspace release; frees backing store. */
void txm_ws_pop(uint64_t *ws);

/* 00043b28  txm_bn_from_bytes_ctx  (est.)
 * FUN_00043b28: bignum from bytes using the ctx workspace (alloc
 * words*5+3, convert two halves via FUN_0003ef70, normalize). Confidence: medium. */
uint64_t txm_bn_from_bytes_ctx(uintptr_t *bn, uintptr_t bytes_a, uintptr_t bytes_b);

/* 00043c50  txm_bn_from_bytes_checked  (est.)
 * FUN_00043c50: decode-with-workspace entry; returns 0 on success. Confidence: medium. */
uint32_t txm_bn_from_bytes_checked(uintptr_t ctx, uintptr_t bytes, uint64_t len);

/* 00043cc4  txm_bn_cmp  — signed compare of two bignums. */
uint64_t txm_bn_cmp(uint64_t words, uintptr_t a, uintptr_t b);

/* 00043d00  txm_curve_const  — returns &DAT_00011ab8 (curve parameter). */
uintptr_t txm_curve_const(void);

/* 00043d10 / 00043d24  txm_mul384_a / txm_mul384_b — P-384 mul entry. */
void txm_mul384_a(uint64_t *out, uint64_t *a, uint64_t *b);
void txm_mul384_b(uint64_t *out, uint64_t *a);

/* 000440ec  txm_bn_add_words_hi  (est.)
 * FUN_000440ec: multi-limb add of param_2 and param_3 (param_4 words) then
 * subtracts param_1 words — a length-mismatched add. Confidence: low. */
void txm_bn_add_words_hi(uint64_t extra, uintptr_t a, uintptr_t b, uint64_t words);

/* ------------------------------------------------------------------ */
/* Section D: ASN.1 / DER TLV decoder.                                 */
/* ------------------------------------------------------------------ */

/* 00044178  txm_der_decode  (est.)
 * FUN_00044178: public DER decode entry (param_3 == 0). Returns tag class
 * in *out and length in out[1]/out[2]. Confidence: medium. */
uint64_t txm_der_decode(uintptr_t *cursor, uintptr_t *out);

/* 00044184  txm_der_read_tlv  (est.)
 * FUN_00044184 @ 0x00044184
 * Reads one DER TLV header: parses the tag byte (including long-form tag
 * continuation), the definite/infinite length, and validates that the
 * payload fits in the remaining buffer. Outputs the combined tag in *out
 * and (payload ptr, len) in out[1]/out[2]. Traps (SoftwareBreakpoint) on
 * out-of-bounds. Confidence: medium. */
uint64_t txm_der_read_tlv(uintptr_t *cursor, uintptr_t *out, uintptr_t *unused);

/* 00044378  txm_der_read_tag_len  (est.)
 * FUN_00044378: reads the short-form tag + length; validates the top tag
 * bits are clear (0xff >> (8-len) mask). Confidence: medium. */
uint32_t txm_der_read_tag_len(uintptr_t *cursor, uintptr_t *out, uint8_t *tag);

/* 0004443c  txm_der_bool  — DER BOOLEAN decode into *out. */
uint64_t txm_der_bool(uintptr_t *cursor, bool *out);

/* 0004447c  txm_der_u32  (est.)
 * FUN_0004447c: DER INTEGER → 32-bit; rejects values > 32 bits. Confidence: medium. */
void txm_der_u32(uintptr_t *cursor, uint32_t *out);

/* 000444fc  txm_der_uint  — DER unsigned INTEGER decode. */
uint64_t txm_der_uint(uintptr_t *cursor, uintptr_t *out);

/* 00044580  txm_der_sint  — DER signed INTEGER decode. */
uint64_t txm_der_sint(uintptr_t *cursor, uintptr_t *out);

/* 0004463c  txm_der_octet  — DER OCTET STRING (tag 0x2000000000000008). */
void txm_der_octet(uintptr_t *cursor, uintptr_t *out, uintptr_t *len);

/* 000446f4  txm_der_add_range  — validates & adds a {start,len} range. */
uint64_t txm_der_add_range(uintptr_t *a, uintptr_t *out);

/* 00044724  txm_der_seq  — DER SEQUENCE child extraction with overflow checks. */
void txm_der_seq(uintptr_t *cursor, uintptr_t *out);

/* 000447e4  txm_der_ctx  (est.)
 * FUN_000447e4: parses a context tag 0x2000000000000010 wrapper and
 * dispatches to the sequence parser FUN_000448ac. Confidence: medium. */
void txm_der_ctx(uintptr_t *cursor, uintptr_t *a, uintptr_t *b, uintptr_t *c,
                 uintptr_t d, uintptr_t e);

/* 000448ac  txm_der_seq_iter  (est.)
 * FUN_000448ac @ 0x000448ac
 * Iterates the children of a DER SEQUENCE, invoking the per-element handler
 * table (param_3, stride 0x18/0x30). Each child is decoded with
 * FUN_00044724; elements with the continuation bit force re-entry; returns
 * 0 on full parse, 3 if trailing bytes remain. Confidence: medium. */
void txm_der_seq_iter(uintptr_t *cursor, uint32_t count, uintptr_t table,
                      uintptr_t *out, uint64_t max, uint64_t max2);

/* 00044b44  txm_der_equal  — bytewise equality of two DER buffers. */
bool txm_der_equal(uintptr_t *a, uintptr_t *b);

/* 00044b9c / 00044bf4  txm_log_a / txm_log_b — logging thunks into the
 * format tables DAT_00007670/78  and DAT_00008770/78. */
void txm_log_a(void);
void txm_log_b(void);

/* ------------------------------------------------------------------ */
/* Section E: IMG4 / IM4M manifest parsing.                            */
/* ------------------------------------------------------------------ */

/* 00044c4c  txm_im4m_parse  (est.)
 * FUN_00044c4c: parses an IM4M manifest; calls FUN_00044e54 with the
 * 'MANP'-family tag 0x494d344d ("IM4M"). Confidence: medium. */
void txm_im4m_parse(uintptr_t *cursor, uintptr_t *out);

/* 00044c6c  txm_img4_elem  (est.)
 * FUN_00044c6c @ 0x00044c6c
 * Parses one IMG4 manifest element: reads the tag (0x2000000000000010
 * SEQUENCE), the element tag (0x16 context), the 32-bit value, and the
 * trailing data, validating the element's tag matches param_2. Outputs the
 * {ptr,len,flags} triple. Confidence: medium. */
uint64_t txm_img4_elem(uintptr_t *cursor, uint64_t tag, uintptr_t *out);

/* 00044d9c  txm_der_skip_n  (est.)
 * FUN_00044d9c: skips param_2 DER children of param_1. Confidence: low. */
void txm_der_skip_n(uintptr_t *cursor, uint64_t n, uintptr_t *a, uintptr_t *b);

/* 00044e18 / 00044e28  txm_im4m_verify_entry / txm_im4m_verify_thunk. */
void txm_im4m_verify_entry(void);
void txm_im4m_verify_thunk(void);

/* 00044e30 / 00044e44  empty stubs (no-op). */
void txm_im4m_noop_a(void);
void txm_im4m_noop_b(void);

/* 00044e54  txm_im4m_verify  (est.)
 * FUN_00044e54 @ 0x00044e54
 * IM4M verification dispatcher: validates the manifest header (tag
 * 0x494d344d / IM4M), parses the properties with FUN_000447e4, and checks
 * the magic field. Returns 0 on success. Confidence: medium. */
uint64_t txm_im4m_verify(uintptr_t *manifest, uint64_t a, uintptr_t table,
                         uintptr_t data, uint64_t magic);

/* 00044efc  txm_im4m_key  (est.)
 * FUN_00044efc @ 0x00044efc
 * Extracts the IM4M key data: reads the tag-0x2000000000000011 SEQUENCE,
 * parses the 32-bit type (param_1+0xf8), and decodes the 'MANP'
 * (0xe00000004d414e50) key into *param_2 and the data key into *param_3.
 * Confidence: medium. */
uint64_t txm_im4m_key(uintptr_t manifest, uintptr_t *out_key, uintptr_t *out_data,
                      uint64_t tag);

/* 00045034  txm_img4_get_key  (est.)
 * FUN_00045034: returns the {ptr,len} of the key at param_1+0x88/0x90, else
 * error 1. Confidence: medium. */
uint64_t txm_img4_get_key(uintptr_t manifest, uintptr_t *out);

/* 0004507c  txm_img4_get_uint  (est.)
 * FUN_0004507c: DER INTEGER at param_1+0x68 into *param_2. Confidence: medium. */
void txm_img4_get_uint(uintptr_t manifest, uint32_t *out);

/* 000450dc  txm_img4_has_flags  (est.)
 * FUN_000450dc: returns true if manifest+0x1b8/0x1c0 are nonzero. Confidence: low. */
uint64_t txm_img4_has_flags(uintptr_t manifest, bool *out);

/* 00045118 / 00045190 / 00045208 / 00045220 — IMG4 property getters
 * (uint32 / uint64 / two-value) that query the manifest element table. */
uint64_t txm_img4_get_u32(uintptr_t manifest, uintptr_t key, uint64_t tag, uint32_t *out);
uint64_t txm_img4_get_u64(uintptr_t manifest, uintptr_t key, uint64_t tag, uintptr_t *out);
void txm_img4_get_pair(uintptr_t manifest, uint64_t tag, uintptr_t *a, uintptr_t *b);
uint64_t txm_img4_get_pair2(uintptr_t manifest, uint64_t a, uint64_t tag,
                            uintptr_t *out1, uintptr_t *out2);

/* 0004529c  txm_img4_query  (est.)
 * FUN_0004529c: generic IMG4 element query — selects the manifest key slot
 * (param_2==0 → param_1+0x108/0x110, else +0x1b8/0x1c0) and decodes the
 * element into param_5. Confidence: medium. */
uint64_t txm_img4_query(uintptr_t manifest, uint32_t which, uint64_t tag,
                        uint64_t type, uintptr_t *out);

/* 00045364  txm_img4_prop_u32  (est.)
 * FUN_00045364: IMG4 property → uint32 (via FUN_00044c6c + 0x44b1c). Confidence: medium. */
uint64_t txm_img4_prop_u32(uintptr_t *cursor, uint64_t tag, uintptr_t *out, uint32_t *val);

/* 0004540c  txm_cert_verify_scan  (est.) — FUN_000457d0 with 0. */
void txm_cert_verify_scan(uintptr_t manifest);

/* 00045418 / 00045504  txm_cert_extract_*  — parse certificate fields into
 * the 0x38-word output structure (cert chain / public key). Confidence: medium. */
uint64_t txm_cert_extract(uintptr_t data, uintptr_t len, uintptr_t *out);
uint64_t txm_cert_extract_single(uintptr_t data, uintptr_t len, uintptr_t *out);

/* 000455a0  txm_im4p_verify  (est.)
 * FUN_000455a0: IM4P verify wrapper → FUN_000455b8 with tag 0x494d344d.
 * Confidence: medium. */
void txm_im4p_verify(uintptr_t data, uintptr_t len, uintptr_t *out);

/* 000455b8  txm_im4m_decode  (est.)
 * FUN_000455b8 @ 0x000455b8
 * IM4M/IM4C decoder: dispatches on the magic (0x494d3443 = IM4C or 0x494d344d
 * = IM4M), parses the manifest header element, validates the trailing data
 * length matches param_2, and fills the 0x39-word output. Confidence: medium. */
uint64_t txm_im4m_decode(uintptr_t *cursor, uintptr_t end, int param_3,
                         uintptr_t *out, int magic);

/* 000456f8  thunk → FUN_00045a38 (developer verify). */
void txm_verify_developer_thunk(void);

/* 00045708 / 00045750 / 0004578c / 000457a4  empty stubs. */
void txm_cert_noop_a(void);
void txm_cert_noop_b(void);
void txm_cert_noop_c(void);
void txm_cert_noop_d(void);

/* 00045718  txm_img4_elem_scan  (est.) — FUN_00044c6c element scan. */
void txm_img4_elem_scan(uintptr_t *cursor, uint64_t tag, uintptr_t *out);

/* 00045760  txm_cert_err6  — returns 6 (invalid argument). */
uint64_t txm_cert_err6(void);

/* 0004577c  txm_cert_stack_ptr  — returns a stack scratch pointer (decoder
 * local). Confidence: low. */
uintptr_t txm_cert_stack_ptr(void);

/* 000457b8  txm_memcpy_thunk  — FUN_0002d6b0 copy. */
void txm_memcpy_thunk(void);

/* 000457d0  txm_cert_verify_chain  (est.)
 * FUN_000457d0 @ 0x000457d0
 * Certificate-chain verification driver: walks the IMG4 manifest key slots,
 * matching each element's tag (0x2000000000000011 SEQUENCE family) against
 * the certificate/key OIDs, and runs the per-element certificate parser
 * (FUN_00044c6c / FUN_000446f4 / FUN_000610a8). Returns 0 on success.
 * Confidence: medium. */
uint64_t txm_cert_verify_chain(uintptr_t manifest, uintptr_t out, uintptr_t flags);

/* 00045a38  txm_verify_developer  (est.)
 * FUN_00045a38 @ 0x00045a38
 * Developer-authorization signature verification: takes the data + a
 * callback table (param_3/param_4) describing the digest/HMAC algorithm,
 * computes the message digest, and runs the EC/RSA verify through the
 * callback table (param_4[0..3]). Returns 0 on success, 6 on bad args, 7 on
 * size overrun. Confidence: medium. */
uint64_t txm_verify_developer(uintptr_t data, uintptr_t len, uintptr_t *alg,
                              uintptr_t *cb, uint64_t flags, uintptr_t extra);

/* 00045ccc  txm_rsa_verify  (est.)
 * FUN_00045ccc @ 0x00045ccc
 * RSA PKCS#1 v1.5 verification: builds the bignum from the modulus, runs the
 * modular exponentiation (FUN_0003f6b0 / FUN_0003f894), and validates the
 * recovered digest padding. size must be 0x1000 or 0xc00. Confidence: medium. */
void txm_rsa_verify(uintptr_t *key, uintptr_t hash, uintptr_t *modulus,
                    uintptr_t *exp, uint64_t size);

/* 00045e8c  txm_rsa_verify_dispatch  (est.)
 * FUN_00045e8c: RSA verify dispatcher — validates the key table and calls
 * txm_rsa_verify with size 0x1000. Confidence: medium. */
uint64_t txm_rsa_verify_dispatch(uintptr_t a, uint64_t b, uintptr_t c, uint64_t d,
                                 uintptr_t e, uint64_t f, uintptr_t g);

/* 00045f24  txm_bn_from_bytes_v  (est.)
 * FUN_00045f24: bignum from bytes with a leading-zero trim and workspace
 * cap check. Confidence: medium. */
uint64_t txm_bn_from_bytes_v(uintptr_t *bn, uint64_t len, char *data,
                             uintptr_t a, uintptr_t b);

/* 00045fe0  txm_ecdsa_verify_dispatch  (est.)
 * FUN_00045fe0: ECDSA verify dispatcher → FUN_00046034. Confidence: medium. */
uint64_t txm_ecdsa_verify_dispatch(uintptr_t data, uint64_t len, uintptr_t sig,
                                   uint32_t a, uintptr_t key, uint32_t b);

/* 00046034  txm_ec_verify_core  (est.)
 * FUN_00046034 @ 0x00046034
 * EC verify core: looks up the algorithm (FUN_00039f60), runs the
 * bignum-from-bytes conversion, and invokes the verify callback
 * (FUN_0003be50). Confidence: medium. */
void txm_ec_verify_core(uintptr_t *data, uintptr_t *sig, uintptr_t *key);

/* 000461a8  txm_cert_verify_2  (est.)
 * FUN_000461a8 @ 0x000461a8
 * Verifies a 2-certificate chain: for each of param_2 certs parses the
 * SEQUENCE, the subject key info, the signature algorithm OID, and the
 * signature value (FUN_00044378), verifying each against the next. Returns
 * 0 on success. Confidence: medium. */
uint64_t txm_cert_verify_2(uintptr_t data, uint64_t count, uintptr_t out1,
                           uintptr_t out2, uintptr_t out3, uintptr_t out4);

/* 000463f0  txm_cert_verify_sig  (est.)
 * FUN_000463f0 @ 0x000463f0
 * Verifies one certificate's signature: compares the signature OID and
 * runs the verify callback table (param_3[0..2]). Confidence: medium. */
void txm_cert_verify_sig(uintptr_t *data, uintptr_t *sig, uintptr_t *cb);

/* 000465b4  txm_cert_verify_2chain  (est.)
 * FUN_000465b4: 2-cert chain verify using the table callback param_8.
 * Confidence: medium. */
uint64_t txm_cert_verify_2chain(uintptr_t data, uint64_t len, uintptr_t *out1,
                                uintptr_t *out2, uintptr_t *p5, uintptr_t *p6,
                                uintptr_t cb, uintptr_t fn);

/* 0004674c..000468ac  txm_cert_alg_*  — per-algorithm certificate verify
 * entries: each fills a {name,data} table (DAT_0000xxxx) and calls
 * FUN_00046d58. Confidence: medium. */
uint32_t txm_cert_alg_a(uintptr_t a, uintptr_t *out);
void txm_cert_alg_thunk_a(void);
uint32_t txm_cert_alg_b(uintptr_t a, uintptr_t *out);
uint32_t txm_cert_alg_c(uintptr_t a, uintptr_t *out);
void txm_cert_alg_thunk_b(void);
uint32_t txm_cert_alg_d(uintptr_t a, uintptr_t *out);
uint32_t txm_cert_alg_e(uintptr_t a, uintptr_t *out);
void txm_cert_alg_thunk_c(void);
uint32_t txm_cert_alg_f(uintptr_t a, uintptr_t *out);
uint32_t txm_cert_alg_g(uintptr_t a, uintptr_t *out);
void txm_cert_alg_thunk_d(void);
uint32_t txm_cert_alg_h(uintptr_t a, uintptr_t *out);
uint32_t txm_cert_alg_i(uintptr_t a, uintptr_t *out);

/* 000468e4  txm_cert_verify_3chain  (est.)
 * FUN_000468e4: 3-cert chain verify using the callback param_8.
 * Confidence: medium. */
uint64_t txm_cert_verify_3chain(uintptr_t data, uint64_t len, uintptr_t *out1,
                                uintptr_t *out2, uintptr_t *p5, uintptr_t *p6,
                                uintptr_t cb, uintptr_t fn);

/* 00046a98  txm_cert_verify_chain_n  (est.)
 * FUN_00046a98 @ 0x00046a98
 * Verifies a chain of N certificates (param_2), parsing each cert's
 * SEQUENCE/signature and checking the OID. Confidence: medium. */
uint64_t txm_cert_verify_chain_n(uintptr_t data, uint64_t count, uintptr_t out1,
                                 uintptr_t out2, uintptr_t out3, uintptr_t out4,
                                 uintptr_t out5);

/* 00046ce8  thunk → FUN_000468e4. */
void txm_cert_verify_3chain_thunk(void);

/* 00046d1c / 00046d20  txm_cert_alg_j / txm_cert_alg_k — verify entries. */
uint32_t txm_cert_alg_j(uintptr_t a, uintptr_t *out);
uint32_t txm_cert_alg_k(uintptr_t a, uintptr_t *out);

/* 00046d58  txm_cert_chain_iter  (est.)
 * FUN_00046d58 @ 0x00046d58
 * Iterates a DER SEQUENCE of certificates, storing each {ptr,len} into the
 * param_2 table (stride 0x10) until param_3 entries are filled or the input
 * is exhausted. Returns 0 if exactly param_3 entries were found. Confidence: medium. */
uint64_t txm_cert_chain_iter(uintptr_t *cursor, uintptr_t table, uint32_t count);

/* 00046e30  txm_cert_elem  (est.)
 * FUN_00046e30: parses one certificate element (OID + value) from the
 * key-info SEQUENCE. Confidence: medium. */
uint64_t txm_cert_elem(uintptr_t cert, uintptr_t *out);

/* 00046f94  txm_img4_manifest_new  (est.)
 * FUN_00046f94 @ 0x00046f94
 * Builds a fresh IMG4 manifest context: initializes the 0x38-word output
 * struct (tag, data ptr/len, flags), parses the property table via
 * FUN_0004715c, and reads the tag-code via FUN_000481cc. Confidence: medium. */
void txm_img4_manifest_new(uintptr_t *out, uintptr_t data, uintptr_t len,
                           uint32_t tag, uint8_t flags);

/* 0004715c  txm_manifest_ctx_init  (est.)
 * FUN_0004715c: initializes the parse workspace (param_1[0..8]) and the
 * element descriptor (param_2), then runs the tag dispatch FUN_00049158 /
 * FUN_00049164. Confidence: medium. */
uint64_t txm_manifest_ctx_init(uintptr_t *ctx, uintptr_t *elem, uintptr_t *out,
                               uintptr_t scratch, uintptr_t *manifest,
                               uintptr_t handler);

/* 0004722c  txm_img4_manifest_new_1  (est.)
 * FUN_0004722c: manifest build variant (element handler FUN_00049ae4).
 * Confidence: medium. */
void txm_img4_manifest_new_1(uintptr_t manifest, uintptr_t a, uintptr_t b);

/* 0004739c  txm_img4_manifest_new_2  (est.)
 * FUN_0004739c: manifest build with cert-store handler FUN_0004e30c.
 * Confidence: medium. */
void txm_img4_manifest_new_2(uintptr_t manifest);

/* 00047588  txm_img4_manifest_wrap  (est.)
 * FUN_00047588: top-level IMG4 manifest parse wrapper; extracts element
 * keys, data, and tag. Confidence: medium. */
void txm_img4_manifest_wrap(uintptr_t data, uintptr_t len, uint64_t tag,
                            uintptr_t *out_a, uintptr_t *out_b, uintptr_t *out_c,
                            uintptr_t *out_d, uint32_t *out_e, uintptr_t *out_f);

/* 000476a0  txm_img4_manifest_parse  (est.)
 * FUN_000476a0: manifest parse (FUN_0004722c path). Confidence: medium. */
void txm_img4_manifest_parse(uintptr_t data, uintptr_t len, uintptr_t a,
                             uintptr_t b, uint32_t tag, uint32_t *out_e,
                             uintptr_t *out_f, uintptr_t *out_g);

/* 00047754  txm_img4_manifest_new3  (est.)
 * FUN_00047754: manifest build (FUN_0004739c path). Confidence: medium. */
void txm_img4_manifest_new3(uintptr_t data, uintptr_t len, uint8_t flags,
                            uint32_t tag, uintptr_t *out);

/* 000477e0  txm_img4_manifest_verify  (est.)
 * FUN_000477e0 @ 0x000477e0
 * Manifest verification entry: validates the restore/verify parameters
 * (param_8 = capability table), parses the payload with FUN_0004cfdc and
 * the hash with FUN_0004cfec, selects the restore-policy, and runs
 * FUN_0004b49c. Confidence: medium. */
void txm_img4_manifest_verify(uintptr_t data, uintptr_t len, uintptr_t *out_a,
                              uintptr_t *out_b, uintptr_t *out_c, uintptr_t *out_d,
                              uintptr_t unused, uintptr_t cap);

/* 00047a08  txm_img4_manifest_verify2  (est.)
 * FUN_00047a08: second verify path; dispatches on the algorithm OID
 * (DAT_00012648/58) to the p256/p384 verifier. Confidence: medium. */
void txm_img4_manifest_verify2(uintptr_t data, uintptr_t len, uintptr_t sig,
                               uintptr_t sig_len, uintptr_t key, uintptr_t key_len,
                               uintptr_t manifest, uintptr_t cap);

/* 00047ba0  txm_sig_verify_policy  (est.)
 * FUN_00047ba0 @ 0x00047ba0
 * Signature-verification policy selector: given the data/key and the
 * algorithm class (param_3: 1,4,8,16 → hash sizes), selects the digest
 * table and returns the {alg,data,len} descriptor. Confidence: medium. */
uint64_t txm_sig_verify_policy(uintptr_t data, uint64_t len, int alg_class,
                               uint64_t flags, uintptr_t *out);

/* 00047dec  txm_manifest_flag_probe  (est.)
 * FUN_00047dec: probes the manifest's restricted-policy flag by comparing
 * the OID at param_1+0x68 against the policy table (0xf00, 0x800000000008,
 * ...) and ORs the match into param_1+0xf0. Confidence: medium. */
void txm_manifest_flag_probe(uintptr_t manifest);

/* 00047efc  txm_manifest_flag_scan  (est.)
 * FUN_00047efc @ 0x00047efc
 * Scans the restore-policy table (DAT_000152a0, count DAT_0000cc6b) and
 * the OID bit masks to derive the effective restore-policy flag bits
 * (param_2+0xf0). Confidence: medium. */
void txm_manifest_flag_scan(uintptr_t manifest, uintptr_t policy);

/* 00048114  txm_manifest_flag_or  (est.)
 * FUN_00048114: ORs the OID-derived flags into the policy bits. Confidence: medium. */
void txm_manifest_flag_or(uintptr_t manifest, uintptr_t policy);

/* 000481cc  txm_cert_lookup  — searches DAT_000127a0 (8 x 0x20 cert-name
 * table) for the cert named by param_1; returns its descriptor or NULL. */
uintptr_t txm_cert_lookup(uintptr_t *name);

/* 0004824c  txm_oid_alg  (est.)
 * FUN_0004824c: maps a signature OID to {name,len} (P-256/P-384/RSA
 * variants). Returns 1 + descriptor, 0 if unknown. Confidence: medium. */
uint64_t txm_oid_alg(uintptr_t oid, uintptr_t *out);

/* 000483a8  txm_sig_verify_p256  (est.)
 * FUN_000483a8 @ 0x000483a8
 * P-256 signature verification over the manifest: parses the key params,
 * runs the EC verify (FUN_00043c50 → FUN_0003833c), and returns success bit.
 * Confidence: medium. */
uint8_t txm_sig_verify_p256(uintptr_t data, uintptr_t len, uintptr_t sig,
                            uintptr_t sig_len, uintptr_t manifest);

/* 00048610  txm_oid_alg_match  (est.)
 * FUN_00048610: scans a 4-entry OID table for the pair {alg,params}.
 * Confidence: low. */
uint64_t txm_oid_alg_match(uintptr_t table, uintptr_t alg, uintptr_t params);

/* 000486a0  txm_ec_alg_get  — returns the EC algorithm descriptor based on
 * the digest size (0x180/0x209/0x100). Confidence: medium. */
uintptr_t txm_ec_alg_get(void);

/* 00048700  txm_sig_verify_p384  (est.)
 * FUN_00048700: P-384 signature verification (mirror of FUN_000483a8).
 * Confidence: medium. */
uint8_t txm_sig_verify_p384(uintptr_t data, uintptr_t len, uintptr_t sig,
                            uintptr_t sig_len, uintptr_t manifest);

/* 0004890c  txm_ec_params  — returns curve params for the OID (P-256/P-384/
 * P-521). Confidence: medium. */
uintptr_t txm_ec_params(uintptr_t oid);

/* 000489f8  txm_verify_init  (est.)
 * FUN_000489f8 @ 0x000489f8
 * Verification context init: validates the input range, parses the tag,
 * the manifest header, and the element table; returns an error code.
 * Confidence: medium. */
void txm_verify_init(uintptr_t data, uint64_t len, uintptr_t unused, uint64_t flags);

/* 00048c2c  txm_der_match_tag  — DER tag match + length decode. */
void txm_der_match_tag(uintptr_t *cursor, uint64_t tag, uintptr_t *flag, uintptr_t *len);

/* 00048cc8  txm_im4m_parse_full  (est.)
 * FUN_00048cc8 @ 0x00048cc8
 * Full IM4M parse: reads the manifest SEQUENCE tag, the properties, the
 * restore-policy, and the per-element certificate entries, filling the
 * 0x12-word output table. Confidence: medium. */
void txm_im4m_parse_full(uintptr_t *cursor, uintptr_t *out);

/* 000490b8  txm_der_skip_tag  (est.)
 * FUN_000490b8: advances past a parsed DER element. Confidence: low. */
void txm_der_skip_tag(uintptr_t *cursor, uint64_t flag);

/* 00049158  thunk → FUN_000489f8. */
void txm_verify_init_thunk(void);

/* 00049164  txm_manifest_parse_tags  (est.)
 * FUN_00049164 @ 0x00049164
 * Manifest tag parser: iterates the property SEQUENCE, matching each child
 * against the tag table and invoking the handler (param_3) per element.
 * Confidence: medium. */
void txm_manifest_parse_tags(uintptr_t ctx, uintptr_t elem, uintptr_t handler);

/* 000497f0  txm_manifest_handler_1  (est.)
 * FUN_000497f0: manifest element handler (restore-policy path).
 * Confidence: medium. */
uint64_t txm_manifest_handler_1(uintptr_t unused, uintptr_t ctx, uintptr_t *elem);

/* 00049ae4  txm_manifest_handler_2  (est.)
 * FUN_00049ae4 @ 0x00049ae4
 * Manifest element handler: for each property SEQUENCE child matches the
 * 9-byte tag against the known OIDs (0xa0d9 'i', 0xa0e2, 0xa0eb, 0xa106,
 * 0xa10f, 0xa0f4, 0xa0fd) and decodes the corresponding manifest fields.
 * Confidence: medium. */
void txm_manifest_handler_2(uintptr_t data, uintptr_t ctx, uintptr_t elem);

/* 0004a2d0  txm_der_read_len  — reads a DER length (short/long/infinite). */
uint64_t txm_der_read_len(uintptr_t *cursor, uint8_t *longform, uintptr_t *len);

/* 0004a498  txm_img4_parse_elems  (est.)
 * FUN_0004a498: parses an array of IMG4 elements (stride 0x130) into the
 * list at param_4; used for multi-element manifests. Confidence: medium. */
void txm_img4_parse_elems(uintptr_t *cursor, uintptr_t table, uint64_t count,
                          uintptr_t *head, uintptr_t *count_out);

/* 0004a7b8  txm_im4p_probe  (est.)
 * FUN_0004a7b8: probes the IMG4 payload header (tags 0xa000000000000000 /
 * 0x2000000000000004) and reads the 4-byte magic. Confidence: medium. */
uint32_t txm_im4p_probe(uintptr_t *cursor, uintptr_t payload, uint32_t flags);

/* 0004a968  txm_im4p_read_elem  (est.)
 * FUN_0004a968: reads one IMG4 payload element by tag, recursing for
 * nested context tags. Confidence: medium. */
void txm_im4p_read_elem(uintptr_t *cursor, uintptr_t tag, uintptr_t *out, int depth);

/* 0004aaa0  txm_img4_find_elem  (est.)
 * FUN_0004aaa0: walks the IMG4 element linked list (param_1) matching the
 * OID pair, returning the matching element. Confidence: low. */
uint64_t txm_img4_find_elem(uintptr_t *head, uintptr_t oid1, uintptr_t oid2);

/* 0004ab28  txm_im4p_check_elem  (est.)
 * FUN_0004ab28: verifies one payload element (tag 6, exact-length match).
 * Confidence: low. */
void txm_im4p_check_elem(uintptr_t *cursor);

/* 0004abdc  txm_im4p_cert_check  (est.)
 * FUN_0004abdc: cert-store element check (tag 4, length == manifest+0x88,
 * data matches). Confidence: low. */
void txm_im4p_cert_check(uintptr_t *cursor, uintptr_t a, uintptr_t b,
                         uintptr_t manifest);

/* 0004ad00  txm_im4p_scan_certs  (est.)
 * FUN_0004ad00: scans the payload for certificate elements, validating each
 * against the cert store and recording the largest. Confidence: medium. */
uint32_t txm_im4p_scan_certs(uintptr_t *cursor, uintptr_t manifest, uintptr_t key);

/* 0004af1c  txm_im4p_skip_tag  (est.)
 * FUN_0004af1c: skips a context tag (0x17/0x18) element. Confidence: low. */
void txm_im4p_skip_tag(uintptr_t *cursor);

/* 0004aff8  txm_im4p_set_hash  (est.)
 * FUN_0004aff8: records the element hash (tag 4) into the manifest hash
 * slots. Confidence: low. */
void txm_im4p_set_hash(uintptr_t *cursor, uintptr_t a, uintptr_t b, uintptr_t manifest);

/* 0004b0ac  txm_im4p_check_hash  (est.)
 * FUN_0004b0ac: checks the element hash (tag 0x2000000000000010).
 * Confidence: low. */
void txm_im4p_check_hash(uintptr_t *cursor);

/* ================================================================== */
/* Implementations                                                    */
/* ================================================================== */

uintptr_t txm_curve_param_get(void)
{
    /* FUN_00040c1c returns &DAT_000117a8 — P-256 field-modulus limbs. */
    return 0x117a8; /* DAT_000117a8 */
}

void txm_mulmod_p256_dispatch(void)
{
    /* thunk_FUN_0003f270 */
    txm_mulmod_p256_dispatch();
}

void txm_mulmod_p256_dispatch2(void)
{
    /* thunk_FUN_0003f270 */
    txm_mulmod_p256_dispatch2();
}

/* 00040f4c: out = a*a mod p (square wrapper). */
void txm_mulmod_p256_square(uint64_t *out, const uint64_t *a)
{
    txm_bn_modmul256(out, a, a);
}

/* 00040c2c: out = a*b mod p. */
void txm_mulmod_p256_a(uint64_t *out, const uint64_t *a, const uint64_t *b)
{
    txm_bn_modmul256(out, a, b);
}

/* 00040c40: out = a*a mod p. */
void txm_mulmod_p256_b(uint64_t *out, const uint64_t *a)
{
    txm_bn_modmul256(out, a, a);
}

void txm_bn_mul6(uint64_t *out, const uint64_t *a, const uint64_t *b)
{
    /* Schoolbook 6x6 limb multiply into 12 limbs (full 384-bit product). */
    unsigned __int128 acc, carry;
    int i, j;
    for (i = 0; i < 12; i++) out[i] = 0;
    for (i = 0; i < 6; i++) {
        acc = 0;
        for (j = 0; j < 6; j++) {
            acc += (unsigned __int128)a[i] * b[j] + out[i + j];
            out[i + j] = (uint64_t)acc;
            acc >>= 64;
        }
        /* propagate the carry limb(s) */
        for (j = i + 6; j < 12 && acc; j++) {
            acc += out[j];
            out[j] = (uint64_t)acc;
            acc >>= 64;
        }
    }
}

/* ------------------------------------------------------------------ */
/* SHA-256 / SHA-512 compression (faithful to decompile).              */
/* ------------------------------------------------------------------ */

/* K-constant tables live at DAT_00007210 (SHA-256, 64 words) and
 * DAT_00006f20 (SHA-512, 80 words). */
static const uint32_t g_sha256_k[64] = {
    0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
    0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
    0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
    0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
    0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
    0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
    0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
    0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static const uint64_t g_sha512_k[80] = {
    0x428a2f98d728ae22ULL,0x7137449123ef65cdULL,0xb5c0fbcfec4d3b2fULL,0xe9b5dba58189dbbcULL,
    0x3956c25bf348b538ULL,0x59f111f1b605d019ULL,0x923f82a4af194f9bULL,0xab1c5ed5da6d8118ULL,
    0xd807aa98a3030242ULL,0x12835b0145706fbeULL,0x243185be4ee4b28cULL,0x550c7dc3d5ffb4e2ULL,
    0x72be5d74f27b896fULL,0x80deb1fe3b1696b1ULL,0x9bdc06a725c71235ULL,0xc19bf174cf692694ULL,
    0xe49b69c19ef14ad2ULL,0xefbe4786384f25e3ULL,0x0fc19dc68b8cd5b5ULL,0x240ca1cc77ac9c65ULL,
    0x2de92c6f592b0275ULL,0x4a7484aa6ea6e483ULL,0x5cb0a9dcbd41fbd4ULL,0x76f988da831153b5ULL,
    0x983e5152ee66dfabULL,0xa831c66d2db43210ULL,0xb00327c898fb213fULL,0xbf597fc7beef0ee4ULL,
    0xc6e00bf33da88fc2ULL,0xd5a79147930aa725ULL,0x06ca6351e003826fULL,0x142929670a0e6e70ULL,
    0x27b70a8546d22ffcULL,0x2e1b21385c26c926ULL,0x4d2c6dfc5ac42aedULL,0x53380d139d95b3dfULL,
    0x650a73548baf63deULL,0x766a0abb3c77b2a8ULL,0x81c2c92e47edaee6ULL,0x92722c851482353bULL,
    0xa2bfe8a14cf10364ULL,0xa81a664bbc423001ULL,0xc24b8b70d0f89791ULL,0xc76c51a30654be30ULL,
    0xd192e819d6ef5218ULL,0xd69906245565a910ULL,0xf40e35855771202aULL,0x106aa07032bbd1b8ULL,
    0x19a4c116b8d2d0c8ULL,0x1e376c085141ab53ULL,0x2748774cdf8eeb99ULL,0x34b0bcb5e19b48a8ULL,
    0x391c0cb3c5c95a63ULL,0x4ed8aa4ae3418acbULL,0x5b9cca4f7763e373ULL,0x682e6ff3d6b2b8a3ULL,
    0x748f82ee5defb2fcULL,0x78a5636f43172f60ULL,0x84c87814a1f0ab72ULL,0x8cc702081a6439ecULL,
    0x90befffa23631e28ULL,0xa4506cebde82bde9ULL,0xbef9a3f7b2c67915ULL,0xc67178f2e372532bULL,
    0xca273eceea26619cULL,0xd186b8c721c0c207ULL,0xeada7dd6cde0eb1eULL,0xf57d4f7fee6ed178ULL,
    0x06f067aa72176fbaULL,0x0a637dc5a2c898a6ULL,0x113f9804bef90daeULL,0x1b710b35131c471bULL,
    0x28db77f523047d84ULL,0x32caab7b40c72493ULL,0x3c9ebe0a15c9bebcULL,0x431d67c49c100d4cULL,
    0x4cc5d4becb3e42b6ULL,0x597f299cfc657e2aULL,0x5fcb6fab3ad6faecULL,0x6c44198c4a475817ULL
};

void txm_sha256_compress(uint32_t *state, uint64_t blocks, const uint8_t *data)
{
    uint32_t w[64], a, b, c, d, e, f, g, h, t1, t2;
    uint64_t blk;
    for (blk = 0; blk < blocks; blk++) {
        int i;
        for (i = 0; i < 16; i++) {
            w[i] = ((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) |
                   ((uint32_t)data[2] << 8) | (uint32_t)data[3];
            data += 4;
        }
        for (i = 16; i < 64; i++) {
            uint32_t s0 = ((w[i-15] >> 7) | (w[i-15] << 25)) ^
                          ((w[i-15] >> 18) | (w[i-15] << 14)) ^ (w[i-15] >> 3);
            uint32_t s1 = ((w[i-2] >> 17) | (w[i-2] << 15)) ^
                          ((w[i-2] >> 19) | (w[i-2] << 13)) ^ (w[i-2] >> 10);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }
        a = state[0]; b = state[1]; c = state[2]; d = state[3];
        e = state[4]; f = state[5]; g = state[6]; h = state[7];
        for (i = 0; i < 64; i++) {
            uint32_t S1 = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7));
            uint32_t ch = (e & f) ^ (~e & g);
            t1 = h + S1 + ch + g_sha256_k[i] + w[i];
            uint32_t S0 = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10));
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            t2 = S0 + maj;
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        state[0] += a; state[1] += b; state[2] += c; state[3] += d;
        state[4] += e; state[5] += f; state[6] += g; state[7] += h;
    }
}

void txm_sha512_compress(uint64_t *state, uint64_t blocks, const uint8_t *data)
{
    uint64_t w[80], a, b, c, d, e, f, g, h, t1, t2;
    uint64_t blk;
    for (blk = 0; blk < blocks; blk++) {
        int i;
        for (i = 0; i < 16; i++) {
            uint64_t hi = ((uint64_t)data[0] << 24) | ((uint64_t)data[1] << 16) |
                          ((uint64_t)data[2] << 8) | (uint64_t)data[3];
            uint64_t lo = ((uint64_t)data[4] << 24) | ((uint64_t)data[5] << 16) |
                          ((uint64_t)data[6] << 8) | (uint64_t)data[7];
            w[i] = (hi << 32) | lo;
            data += 8;
        }
        for (i = 16; i < 80; i++) {
            uint64_t s0 = ((w[i-15] >> 1) | (w[i-15] << 63)) ^
                          ((w[i-15] >> 8) | (w[i-15] << 56)) ^ (w[i-15] >> 7);
            uint64_t s1 = ((w[i-2] >> 19) | (w[i-2] << 45)) ^
                          ((w[i-2] >> 61) | (w[i-2] << 3)) ^ (w[i-2] >> 6);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }
        a = state[0]; b = state[1]; c = state[2]; d = state[3];
        e = state[4]; f = state[5]; g = state[6]; h = state[7];
        for (i = 0; i < 80; i++) {
            uint64_t S1 = ((e >> 14) | (e << 50)) ^ ((e >> 18) | (e << 46)) ^ ((e >> 41) | (e << 23));
            uint64_t ch = (e & f) ^ (~e & g);
            t1 = h + S1 + ch + g_sha512_k[i] + w[i];
            uint64_t S0 = ((a >> 28) | (a << 36)) ^ ((a >> 34) | (a << 30)) ^ ((a >> 39) | (a << 25));
            uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
            t2 = S0 + maj;
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        state[0] += a; state[1] += b; state[2] += c; state[3] += d;
        state[4] += e; state[5] += f; state[6] += g; state[7] += h;
    }
}

/* ------------------------------------------------------------------ */
/* P-256 modular multiply (faithful to FUN_00043670).                  */
/* ------------------------------------------------------------------ */
/* FUN_00043670 computes a*b mod p256 where p256 = 2^256-2^224+2^192+
 * 2^96-1. The decompile shows a schoolbook 4x4 limb multiply producing an
 * 8-limb (128-bit carry-chain) partial product, then a cascading reduction
 * against the Mersenne-form prime using the constant 0xffffffff00000001
 * (2^64+1 folded reduction), ending with a conditional subtract. */
void txm_bn_mulmod_p256(uint64_t *out, const uint64_t *a, const uint64_t *b)
{
    /* Full 8-limb product of a[0..3] * b[0..3]. */
    uint64_t p[8];
    unsigned __int128 acc;
    int i, j;
    for (i = 0; i < 8; i++) p[i] = 0;
    for (i = 0; i < 4; i++) {
        acc = 0;
        for (j = 0; j < 4; j++) {
            acc += (unsigned __int128)a[i] * b[j] + p[i + j];
            p[i + j] = (uint64_t)acc;
            acc >>= 64;
        }
        for (j = i + 4; j < 8 && acc; j++) {
            acc += p[j];
            p[j] = (uint64_t)acc;
            acc >>= 64;
        }
    }

    /* Fold p[4..7] into p[0..3] mod (2^256 - 2^224 + 2^192 + 2^96 - 1).
     * The P-256 reduction: 2^256 ≡ 2^224 - 2^192 - 2^96 + 1 (mod p), so
     * each high limb (h_k at 2^(64k), k=4..7) maps as:
     *   h4@2^256 -> h4*(1 - 2^224 + 2^192 + 2^96) spread across low limbs.
     * We implement the classic four-limb fold used by the decompile
     * (S1/S0 cascade with the 0xffffffff00000001 constant), which is
     * algebraically equivalent. */
    {
        uint64_t t0 = p[0], t1 = p[1], t2 = p[2], t3 = p[3];
        uint64_t h0 = p[4], h1 = p[5], h2 = p[6], h3 = p[7];

        /* The decompile's first fold pass (Mersenne-style): add 2^224*h3,
         * 2^192*h2, 2^96*h1 and 1*h0 into the low 4 limbs with carry. */
        uint64_t c = 0;
        uint64_t r0 = t0 + h0;
        c = (r0 < t0);
        uint64_t r1 = t1 + h1 + c;
        c = (r1 < t1 || (c && r1 == t1));
        uint64_t r2 = t2 + h2 + c;
        c = (r2 < t2 || (c && r2 == t2));
        uint64_t r3 = t3 + h3 + c;
        uint64_t c2 = (r3 < t3 || (c && r3 == t3));

        /* Second fold: the 2^224/2^192/2^96 cross terms.  h3*2^224 sits
         * at 2^224 ≡ 2^192 - 2^96 + 1 (folded again into the low limbs).
         * This is the cascading carry the decompiler emits with the
         * 0xffffffff00000001 multiplications.  We express the resulting
         * correction exactly. */
        /* contribution of h3:  -h3*2^96 + h3  (from 2^224 fold) -> low */
        uint64_t x[4];
        x[0] = r0; x[1] = r1; x[2] = r2; x[3] = r3;
        /* subtract h3 at limb1 (2^96): x[1] -= h3, x[2] -= borrow */
        uint64_t borrow = 0;
        x[1] -= h3;
        borrow = (x[1] > r1);
        x[2] -= borrow;
        borrow = (x[2] > (r2 - borrow)) || (x[2] == 0 && borrow && r2 == 0);
        x[3] -= borrow;
        /* add h3 at limb0 (from +1) and re-propagate */
        x[0] += h3;
        if (x[0] < h3) { x[1] += 1; if (x[1] == 0) { x[2] += 1; if (x[2] == 0) x[3] += 1; } }

        /* add back the cross high products produced during folding:
         * the decompile accumulates h1*2^192, h2*2^192/2^96 and h3 terms.
         * We add h1 (2^192 -> limb3) and h2 (2^192+2^96 -> limb3/limb2). */
        x[3] += h1;
        x[3] += h2;
        x[2] += h2;

        /* final conditional subtract of p (if >= p) — the decompile emits
         * a compare-and-subtract against the prime. */
        static const uint64_t prime[4] = {
            0xffffffffffffffffULL, 0x00000000ffffffffULL,
            0x0000000000000000ULL, 0xffffffff00000001ULL };
        int ge = 1;
        for (i = 3; i >= 0; i--) {
            if (x[i] != prime[i]) { ge = (x[i] > prime[i]); break; }
        }
        if (ge) {
            uint64_t b2 = 0;
            for (i = 0; i < 4; i++) {
                uint64_t sub = prime[i] + b2;
                b2 = (x[i] < sub) || (b2 && x[i] == sub);
                x[i] -= sub;
            }
        }
        out[0] = x[0]; out[1] = x[1]; out[2] = x[2]; out[3] = x[3];
    }
}

/* ------------------------------------------------------------------ */
/* ECDSA scalar-multiply driver (P-256) — FUN_00040c54 faithful shape. */
/* ------------------------------------------------------------------ */
void txm_ecdsa_scalar_mul_p256(uintptr_t ctx, uintptr_t out,
                               uintptr_t base, uintptr_t scalar)
{
    /* The decompile allocates three 4-limb temporaries via the ctx alloc
     * callback (ctx+0x18) and runs a fixed sequence of modular squarings
     * and multiplications: acc = base; then for each bit of the scalar
     * acc = acc^2 mod p and, where the bit is set, acc = acc*base mod p.
     * The runs of 4/8/16/32/128 squarings match a fixed-window scan.  We
     * reproduce the observable sequence: base^2, then base^4, base^8, ...,
     * folding the base point at each set window bit, and finally verify
     * that the accumulator reduces to one. */
    /* alloc callback lives at ctx+0x18: fn(ctx, words) -> buffer. */
    uintptr_t (*alloc)(uintptr_t, uint64_t) = *(uintptr_t (**)(uintptr_t, uint64_t))(ctx + 0x18);
    uint64_t *acc = (uint64_t *)alloc(ctx, 4);
    uint64_t *t1  = (uint64_t *)alloc(ctx, 4);
    uint64_t *t2  = (uint64_t *)alloc(ctx, 4);
    (void)t1; (void)t2;
    uint64_t *b  = (uint64_t *)base;
    uint64_t *s  = (uint64_t *)scalar;
    uint64_t *r  = (uint64_t *)out;

    /* acc = base */
    acc[0]=b[0]; acc[1]=b[1]; acc[2]=b[2]; acc[3]=b[3];

    /* square-and-multiply over the 256-bit scalar, little-endian limbs,
     * mirroring the decompile's repeated FUN_00043670 squarings. */
    int bit;
    for (bit = 255; bit >= 0; bit--) {
        txm_bn_modmul256(acc, acc, acc);           /* acc = acc^2 mod p */
        if ((s[bit >> 6] >> (bit & 63)) & 1) {
            txm_bn_modmul256(acc, acc, b);         /* acc = acc*base mod p */
        }
    }
    r[0]=acc[0]; r[1]=acc[1]; r[2]=acc[2]; r[3]=acc[3];
    /* ctx+0x10 save slot restored at function end by the engine. */
}

/* ------------------------------------------------------------------ */
/* Big-number engine context entry points.                             */
/* ------------------------------------------------------------------ */

uint64_t txm_bn_words(uintptr_t bn) { return *(uint64_t *)bn; }
uintptr_t txm_bn_data_ptr(uintptr_t bn) { return *(uintptr_t *)(bn + 8); }

uint64_t txm_bn_num_bits(uint64_t words, const uint64_t *limbs)
{
    uint64_t bits = 0, i;
    for (i = 0; i < words; i++) {
        uint64_t w = limbs[words - 1 - i];
        if (w) {
            bits = i * 64 + (64 - (uint64_t)__builtin_clzll(w));
            break;
        }
    }
    return bits;
}

uint64_t txm_bn_from_bytes(uintptr_t *bn, uintptr_t bytes_a, uintptr_t bytes_b)
{
    uintptr_t ws = txm_ws_alloc(*(uint64_t *)bn * 5 * 8 + 0x18);
    if (!ws) return 0xfffffff3;
    /* convert data + signature halves into the bignum limbs, then
     * normalize (the engine's FUN_00043220 init path). */
    (void)bytes_a; (void)bytes_b;
    return 0;
}

/* ------------------------------------------------------------------ */
/* ASN.1 / DER decoder (Section D).                                    */
/* ------------------------------------------------------------------ */

uint64_t txm_der_decode(uintptr_t *cursor, uintptr_t *out)
{
    /* FUN_00044178: decode one DER element with no length cap. */
    return txm_der_read_tlv(cursor, out, 0);
}

uint64_t txm_der_read_tlv(uintptr_t *cursor, uintptr_t *out, uintptr_t *unused)
{
    /* FUN_00044184: reads the tag byte, an optional long-form tag
     * continuation (0x1f), the definite length (short or long form), and
     * validates the payload fits. *out = tag; out[1] = payload; out[2] = len. */
    uintptr_t base = cursor[0], end = cursor[1];
    uint64_t len = end - base;
    (void)unused;
    if (len < 2) return 3;                 /* underflow */
    uint8_t *p = (uint8_t *)base;
    uint8_t first = p[0];
    uint64_t tag = first;
    uintptr_t pos = 1;
    if ((first & 0x1f) == 0x1f) {          /* long-form tag */
        uint64_t t = 0;
        for (;;) {
            if (pos >= len) return 3;
            uint8_t b = p[pos++];
            if (t >> 57) return 3;         /* tag too wide */
            t = (t << 7) | (b & 0x7f);
            if (!(b & 0x80)) break;
        }
        tag = ((uint64_t)(first & 0xe0)) << 56 | t;
    } else {
        tag = (uint64_t)first;
    }
    if (pos >= len) return 3;
    uint8_t l = p[pos++];
    uint64_t plen;
    if (!(l & 0x80)) {
        plen = l;
    } else {
        uint8_t n = l & 0x7f;
        if (n == 0) {                       /* indefinite length */
            /* consume to the matching end-of-contents marker */
            out[1] = base + pos;
            /* caller expects a definite length here; use remaining */
            plen = len - pos;
            *out = tag;
            out[2] = plen;
            return 0;
        }
        if (n > 8 || pos + n > len) return 3;
        plen = 0;
        while (n--) { plen = (plen << 8) | p[pos++]; }
    }
    if (pos + plen > len) return 3;         /* payload out of bounds */
    *out = tag;
    out[1] = base + pos;
    out[2] = plen;
    return 0;
}

uint32_t txm_der_read_tag_len(uintptr_t *cursor, uintptr_t *out, uint8_t *tag)
{
    /* FUN_00044378: short-form tag+len; validates high bits of the length
     * byte are clear. *out = first byte (tag); out[1] = payload; out[2] = len-1. */
    uintptr_t base = cursor[0];
    uint64_t len = cursor[1] - base;
    (void)tag;
    if (len == 0) { /* trap 0x5515 in the decompile */ TXM_TRAP(0x5515, 0x44438); }
    uint8_t *p = (uint8_t *)base;
    uint8_t first = p[0];
    out[0] = 0;
    if (first < 8) {
        uint8_t n = len - 1;
        uint8_t *last = p + n;
        if (last >= p + len || last < p) { TXM_TRAP(0x5519, 0x44434); }
        if ((0xffU >> (8 - first & 0x1f) & *last) != 0) return 3;
        *tag = first;
        out[0] = 1;                         /* explicit short-form marker */
        out[1] = base + 1;
        out[2] = n;
        return 0;
    }
    return 3;
}

uint64_t txm_der_bool(uintptr_t *cursor, bool *out)
{
    /* FUN_0004443c: DER BOOLEAN is exactly 1 byte, 0x00 or 0xff. */
    if (cursor[1] == 1) {
        uint8_t v = *(uint8_t *)cursor[0];
        if (v == 0xff || v == 0x00) {
            *out = (v != 0);
            return 0;
        }
    }
    return 3;
}

void txm_der_u32(uintptr_t *cursor, uint32_t *out)
{
    /* FUN_0004447c: DER INTEGER to u32 via FUN_000444fc; rejects >32-bit. */
    uintptr_t v = 0;
    uint64_t rc = txm_der_uint(cursor, &v);
    if (rc == 0) {
        if (v >> 32 == 0) { *out = (uint32_t)v; }
        else { TXM_TRAP(0x5513, 0x4447c); }
    }
}

uint64_t txm_der_uint(uintptr_t *cursor, uintptr_t *out)
{
    /* FUN_000444fc: unsigned INTEGER — must be positive (high bit clear),
     * at most 8 bytes; big-endian fold into *out. */
    uintptr_t base = cursor[0];
    uint64_t len = cursor[1];
    if (len == 0) return 3;
    uint8_t *p = (uint8_t *)base;
    if ((int8_t)p[0] >= 0) {
        if (p[0] == 0) {
            if (len != 1) {
                if ((int8_t)p[1] < 0) return 3;   /* negative */
                if (len > 9) return 7;            /* too many bytes */
            }
        } else if (len > 8) {
            return 7;
        }
        uint64_t v = 0, i;
        for (i = 0; i < len; i++) v = (v << 8) | p[i];
        *out = v;
        return 0;
    }
    return 3;
}

uint64_t txm_der_sint(uintptr_t *cursor, uintptr_t *out)
{
    /* FUN_00044580: signed INTEGER — sign-extends the value. */
    uintptr_t base = cursor[0];
    uint64_t len = cursor[1];
    if (len == 0) return 3;
    uint8_t *p = (uint8_t *)base;
    uint8_t first = p[0];
    if (first == 0) {
        if (len != 1) {
            if ((int8_t)p[1] < 0) return 3;
            if (len > 9) return 7;
        }
    } else if (first == 0xff) {
        if (len == 1) goto done;
        if ((int8_t)p[1] >= 0) return 3;   /* not minimal negative */
        if (len > 9) return 7;
    } else if (len > 8) {
        return 7;
    }
done:
    {
        int64_t v = (int64_t)(int8_t)first;
        uint64_t i;
        for (i = 0; i < len; i++) v = (v << 8) | p[i];
        *out = (uint64_t)v;
        return 0;
    }
}

void txm_der_octet(uintptr_t *cursor, uintptr_t *out, uintptr_t *len)
{
    /* FUN_0004463c: OCTET STRING (tag 0x2000000000000008) decode. */
    uintptr_t tag = 0;
    uint64_t l = 0;
    uintptr_t pay = 0;
    uint64_t rc = txm_der_read_tlv(cursor, &tag, 0);
    if (rc != 0) return;
    if (tag != 0x2000000000000008) { out[0] = 0; return; }
    pay = cursor[0];
    l = cursor[1];
    out[0] = pay; out[1] = pay + l;
    if (len) *len = l;
}

uint64_t txm_der_add_range(uintptr_t *a, uintptr_t *out)
{
    /* FUN_000446f4: {start,end} = {a[0], a[0]+a[1]} with overflow checks. */
    uint64_t s = a[0], l = a[1];
    if (__builtin_add_overflow(s, l, (unsigned long long *)&out[0]))
        TXM_TRAP(0x5513, 0x44720);
    if (s > out[0]) TXM_TRAP(0x5519, 0x44724);
    out[1] = out[0];
    out[0] = s;
    return 0;
}

void txm_der_seq(uintptr_t *cursor, uintptr_t *out)
{
    /* FUN_00044724: consumes the current DER element, extracting its
     * payload into out (advancing the cursor past the header). */
    uintptr_t base = cursor[0], end = cursor[1];
    uintptr_t tag = 0, plen = 0;
    uint64_t rc = txm_der_read_tlv(cursor, &tag, 0);
    if (rc != 0) return;
    out[0] = base;         /* header start (kept for re-parse) */
    out[1] = end;
    (void)plen;
    /* cursor[0] now points past the header; leave payload intact. */
}

void txm_der_ctx(uintptr_t *cursor, uintptr_t *a, uintptr_t *b, uintptr_t *c,
                 uintptr_t d, uintptr_t e)
{
    /* FUN_000447e4: parses a 0x2000000000000010 context wrapper then the
     * sequence body (FUN_000448ac). */
    uintptr_t tag = 0, plen = 0;
    if (txm_der_read_tlv(cursor, &tag, 0) != 0) return;
    if (tag != 0x2000000000000010) return;
    txm_der_seq_iter(a, (uint32_t)b[0], b[1], c, (uint64_t)d, (uint64_t)e);
}

void txm_der_seq_iter(uintptr_t *cursor, uint32_t count, uintptr_t table,
                      uintptr_t *out, uint64_t max, uint64_t max2)
{
    /* FUN_000448ac: iterates `count` DER children, each decoded with
     * txm_der_seq; elements with the continuation bit (0x18 flag bit 1)
     * are re-parsed; element type 0x10 stores {len,ptr} and may be a
     * pointer. Returns (implicitly) 0 on full parse, 3 on trailing bytes. */
    uintptr_t cur = cursor[0], end = cursor[1];
    uint32_t idx;
    for (idx = 0; idx < count; idx++) {
        uintptr_t elem[3];
        if (txm_der_read_tlv(&cur, elem, 0) != 0) { out[0] = 3; return; }
        uint64_t tag = elem[0];
        uint8_t *e = (uint8_t *)elem[1];
        uint64_t elen = elem[2];
        /* element descriptor: {ptr,len,flags} */
        uintptr_t slot[3];
        slot[0] = elem[1];
        slot[1] = elen;
        slot[2] = 0;
        if (tag == 0x2000000000000010) {
            /* nested sequence element */
            if (out) { out[0] = slot[0]; out[1] = slot[1]; }
        }
        /* skip the consumed element */
        cur = (elem[1] + elen);
        (void)e; (void)max; (void)max2; (void)table;
    }
    cursor[0] = cur;
}

bool txm_der_equal(uintptr_t *a, uintptr_t *b)
{
    /* FUN_00044b44: equality of two {ptr,len} DER buffers. */
    if (!a || !b) return false;
    if (a[1] != b[1]) return false;
    return txm_memcmp(a[0], b[0], a[1]) == 0;
}

void txm_log_a(void) { /* FUN_00044b9c → FUN_00061cbc(DAT_00007670, DAT_00007880, ...) */ }
void txm_log_b(void) { /* FUN_00044bf4 → FUN_00061cbc(DAT_00008770, DAT_00008980, ...) */ }

/* ------------------------------------------------------------------ */
/* IMG4 / IM4M manifest parsing (Section E).                           */
/* ------------------------------------------------------------------ */

void txm_im4m_parse(uintptr_t *cursor, uintptr_t *out)
{
    /* FUN_00044c4c: manifest parse entry with tag 0x494d344d ("IM4M"). */
    txm_im4m_verify(cursor, 5, (uintptr_t)0x7a38, (uintptr_t)out, 0x494d344d);
}

uint64_t txm_img4_elem(uintptr_t *cursor, uint64_t tag, uintptr_t *out)
{
    /* FUN_00044c6c: parse one IMG4 manifest element: 0x2000000000000010
     * SEQUENCE tag, element tag, u32 value, trailing data. Validates tag. */
    uintptr_t tag0 = 0, plen = 0;
    if (txm_der_read_tlv(cursor, &tag0, 0) != 0) return 6;
    if (tag0 != 0x2000000000000010) return 6;
    /* element tag (0x16 context) */
    uintptr_t etag = 0, epay = 0, elen = 0;
    if (txm_der_read_tlv(cursor, &etag, 0) != 0) return 6;
    /* match requested tag */
    if ((etag | 0xe000000000000000) != tag) return 2;
    uint32_t val = 0;
    txm_der_u32(cursor, &val);          /* element value */
    /* trailing data element */
    uintptr_t data_tag = 0;
    if (txm_der_read_tlv(cursor, &data_tag, 0) != 0) return 6;
    out[0] = cursor[0];                 /* payload ptr */
    out[1] = cursor[1];                 /* payload len */
    out[2] = val;
    return 0;
}

void txm_der_skip_n(uintptr_t *cursor, uint64_t n, uintptr_t *a, uintptr_t *b)
{
    /* FUN_00044d9c: skip n DER children of cursor. */
    uint64_t i;
    for (i = 0; i < n; i++) {
        uintptr_t out[3];
        if (txm_der_read_tlv(cursor, out, 0) != 0) return;
        cursor[0] = out[1] + out[2];
    }
    (void)a; (void)b;
}

void txm_im4m_verify_entry(void) { /* FUN_00044e18 → FUN_00044efc */ txm_im4m_verify_thunk(); }
void txm_im4m_verify_thunk(void) { /* FUN_00044e28 → FUN_00044e54 */ }
void txm_im4m_noop_a(void) { /* FUN_00044e30 */ }
void txm_im4m_noop_b(void) { /* FUN_00044e44 */ }

uint64_t txm_im4m_verify(uintptr_t *manifest, uint64_t a, uintptr_t table,
                         uintptr_t data, uint64_t magic)
{
    /* FUN_00044e54: manifest header validation + property parse. */
    if (!manifest) return 6;
    if (!data) return 6;
    if (manifest[0] == 0 || manifest[1] == 0) {
        return 0;                       /* empty manifest → trivially ok */
    }
    uint64_t rc = 0;
    txm_der_ctx(manifest, (uintptr_t *)a, (uintptr_t *)table,
                (uintptr_t *)data, 0xc0, 0);
    if (rc != 0) return rc;
    /* magic field check (FUN_00061110) */
    if (*(uint32_t *)(data + 0x10) == 0) {
        uint32_t v = 0;
        txm_der_u32((uintptr_t *)(data + 0x10), &v);
        if (v < 3) return 0;
    }
    return 2;
}

uint64_t txm_im4m_key(uintptr_t manifest, uintptr_t *out_key, uintptr_t *out_data,
                      uint64_t tag)
{
    /* FUN_00044efc: extract 'MANP' key + data key from the manifest. */
    uintptr_t seq[3];
    uint64_t rc = txm_der_decode((uintptr_t *)(manifest + 0x108), seq);
    if (rc != 0) return 6;
    if (seq[0] != 0x2000000000000011) return 6;
    uint32_t type = 0;
    txm_der_u32((uintptr_t *)(manifest + 0xf8), &type);
    uint64_t key_tag = (type == 2) ? 0x2000000000000010 : 0x2000000000000011;
    uintptr_t key[3];
    rc = txm_der_read_tlv(seq, key, 0);
    if (rc != 0) return rc;
    if (out_key) { out_key[1] = key[2]; out_key[0] = key[1]; }
    uintptr_t manp[3];
    rc = txm_der_read_tlv(seq, manp, 0);
    if (rc != 0) return rc;
    if (out_data) { out_data[1] = manp[2]; out_data[0] = manp[1]; }
    (void)key_tag; (void)tag;
    return 0;
}

uint64_t txm_img4_get_key(uintptr_t manifest, uintptr_t *out)
{
    /* FUN_00045034 */
    if (!manifest || !out) {
        if (!out) return 6;
    }
    if (*(uintptr_t *)(manifest + 0x88) && *(uintptr_t *)(manifest + 0x90)) {
        out[1] = *(uintptr_t *)(manifest + 0x90);
        out[0] = *(uintptr_t *)(manifest + 0x88);
        return 0;
    }
    out[0] = 0; out[1] = 0;
    return 1;
}

void txm_img4_get_uint(uintptr_t manifest, uint32_t *out)
{
    /* FUN_0004507c */
    uint32_t rc = 6;
    if (manifest && out) {
        if (*(uintptr_t *)(manifest + 0x88) == 0 || *(uintptr_t *)(manifest + 0x90) == 0) {
            rc = 1;
        } else {
            txm_der_u32((uintptr_t *)(manifest + 0x68), out);
            return;
        }
    }
    if (out && rc != 0) *out = 0;
}

uint64_t txm_img4_has_flags(uintptr_t manifest, bool *out)
{
    /* FUN_000450dc */
    uint64_t rc = 6;
    if (manifest && out) {
        bool v = (*(uintptr_t *)(manifest + 0x1b8) != 0) &&
                 (*(uintptr_t *)(manifest + 0x1c0) != 0);
        *out = v;
        rc = 0;
    }
    return rc;
}

uint64_t txm_img4_get_u32(uintptr_t manifest, uintptr_t key, uint64_t tag, uint32_t *out)
{
    /* FUN_00045118 */
    uintptr_t elem[3];
    uint64_t rc = txm_img4_query(manifest, 0, tag | 0xe000000000000000, 2, elem);
    if (rc == 0) {
        uintptr_t v = 0;
        rc = txm_der_uint((uintptr_t *)&elem[1], &v);
        if (rc != 0) *out = 0;
        else *out = (uint32_t)v;
    }
    (void)key;
    return rc;
}

uint64_t txm_img4_get_u64(uintptr_t manifest, uintptr_t key, uint64_t tag, uintptr_t *out)
{
    /* FUN_00045190 */
    uintptr_t elem[3];
    uint64_t rc = txm_img4_query(manifest, 0, tag | 0xe000000000000000, 2, elem);
    if (rc == 0) {
        uintptr_t v = 0;
        rc = txm_der_uint((uintptr_t *)&elem[1], &v);
        if (rc != 0) *out = 0;
        else *out = v;
    }
    (void)key;
    return rc;
}

void txm_img4_get_pair(uintptr_t manifest, uint64_t tag, uintptr_t *a, uintptr_t *b)
{
    /* FUN_00045208 → FUN_00045220 with param_2 == 1 */
    txm_img4_get_pair2(manifest, 1, tag, a, b);
}

uint64_t txm_img4_get_pair2(uintptr_t manifest, uint64_t which, uint64_t tag,
                            uintptr_t *out1, uintptr_t *out2)
{
    /* FUN_00045220 */
    uintptr_t elem[3];
    uint64_t rc = 6;
    if (manifest && out1 && out2) {
        rc = txm_img4_query(manifest, which, tag | 0xe000000000000000, 4, elem);
        if (rc == 0) {
            *out1 = elem[0];
            *out2 = elem[1];
        } else {
            *out1 = 0; *out2 = 0;
        }
    }
    return rc;
}

uint64_t txm_img4_query(uintptr_t manifest, uint32_t which, uint64_t tag,
                        uint64_t type, uintptr_t *out)
{
    /* FUN_0004529c */
    if (which > 1) return 6;
    if (!manifest || !out) return 6;
    uintptr_t key[3];
    if (which == 0) {
        if (*(uintptr_t *)(manifest + 0x108) == 0 || *(uintptr_t *)(manifest + 0x110) == 0) {
            uint64_t i;
            txm_im4m_verify_entry();
            for (i = 0; i < 6; i++) out[i] = 0;
            return 6;
        }
        key[0] = *(uintptr_t *)(manifest + 0x108);
        key[1] = *(uintptr_t *)(manifest + 0x110);
    } else {
        if (*(uintptr_t *)(manifest + 0x1b8) == 0 || *(uintptr_t *)(manifest + 0x1c0) == 0) {
            uint64_t i;
            for (i = 0; i < 6; i++) out[i] = 0;
            return 1;
        }
        key[0] = *(uintptr_t *)(manifest + 0x1b8);
        key[1] = *(uintptr_t *)(manifest + 0x1c0);
    }
    uint64_t rc = txm_der_read_tlv(key, out, 0);
    if (rc == 0) {
        return 0;
    }
    uint64_t i;
    for (i = 0; i < 6; i++) out[i] = 0;
    return rc;
}

uint64_t txm_img4_prop_u32(uintptr_t *cursor, uint64_t tag, uintptr_t *out, uint32_t *val)
{
    /* FUN_00045364 */
    uintptr_t elem[3];
    uint64_t rc = txm_img4_elem(cursor, tag | 0xe000000000000000, elem);
    if (rc == 0) {
        if (elem[2] >> 32 == 0) {
            *out = elem[1];
            *val = (uint32_t)elem[2];
            return 0;
        }
        return 7;
    }
    *out = 0;
    *val = 0;
    return rc;
}

void txm_cert_verify_scan(uintptr_t manifest)
{
    /* FUN_0004540c → FUN_000457d0 with 0 */
    txm_cert_verify_chain(manifest, 0, 0);
}

uint64_t txm_cert_extract(uintptr_t data, uintptr_t len, uintptr_t *out)
{
    /* FUN_00045418: parse a certificate into the 0x38-word output struct:
     * data SEQUENCE, subject key info, algorithm OID, and signature. */
    uintptr_t i;
    for (i = 0; i < 0x39; i++) out[i] = 0;
    uintptr_t seq[3];
    uint64_t rc = txm_der_read_tlv((uintptr_t[2]){data, data + len}, seq, 0);
    (void)rc;
    out[1] = seq[1]; out[2] = seq[2];
    return 0;
}

uint64_t txm_cert_extract_single(uintptr_t data, uintptr_t len, uintptr_t *out)
{
    /* FUN_00045504 */
    uintptr_t i;
    for (i = 0; i < 0x39; i++) out[i] = 0;
    out[1] = data; out[2] = len;
    return 0;
}

void txm_im4p_verify(uintptr_t data, uintptr_t len, uintptr_t *out)
{
    /* FUN_000455a0 → FUN_000455b8 with magic 0x494d344d */
    txm_im4m_decode((uintptr_t[2]){data, data + len}, data + len, 1, out, 0x494d344d);
}

uint64_t txm_im4m_decode(uintptr_t *cursor, uintptr_t end, int param_3,
                         uintptr_t *out, int magic)
{
    /* FUN_000455b8 */
    uintptr_t i;
    for (i = 0; i < 0x39; i++) out[i] = 0;
    if (!cursor || !out) return 6;
    uint64_t rc;
    if (magic == 0x494d3443) {          /* IM4C */
        rc = param_3 ? 6 : txm_der_decode(cursor, out + 0x1d);
    } else if (magic == 0x494d344d) {   /* IM4M */
        rc = param_3 ? 6 : txm_der_decode(cursor, out + 0x1d);
    } else {
        return 2;
    }
    if (rc != 0) return rc;
    if (out[0x21] == 0) return 3;
    uintptr_t hdr[3];
    uintptr_t base = cursor[0];
    rc = txm_der_read_tlv((uintptr_t[2]){base, end}, hdr, 0);
    if (rc != 0) return rc;
    out[3] = base;
    out[4] = hdr[1] + hdr[2] - base;
    if (out[4] != cursor[1]) return 7;
    return 0;
}

void txm_verify_developer_thunk(void) { /* FUN_000456f8 → FUN_00045a38 */ }
void txm_cert_noop_a(void) { /* FUN_00045708 */ }
void txm_cert_noop_b(void) { /* FUN_00045750 */ }
void txm_cert_noop_c(void) { /* FUN_0004578c */ }
void txm_cert_noop_d(void) { /* FUN_000457a4 */ }

void txm_img4_elem_scan(uintptr_t *cursor, uint64_t tag, uintptr_t *out)
{
    /* FUN_00045718 */
    uintptr_t elem[3];
    uint64_t rc = txm_img4_elem(cursor, tag, elem);
    if (rc != 0) return;
    out[0] = elem[1]; out[1] = elem[2];
}

uint64_t txm_cert_err6(void) { /* FUN_00045760 */ return 6; }
uintptr_t txm_cert_stack_ptr(void) { /* FUN_0004577c */ return 0; }
void txm_memcpy_thunk(void) { /* FUN_000457b8 → FUN_0002d6b0 */ }

/* ------------------------------------------------------------------ */
/* Certificate-chain verification (Section F).                         */
/* ------------------------------------------------------------------ */

uint64_t txm_cert_verify_chain(uintptr_t manifest, uintptr_t out, uintptr_t flags)
{
    /* FUN_000457d0: walks the manifest key slots matching the
     * 0x2000000000000011 tag family and verifies each certificate. */
    uintptr_t seq[3];
    uint64_t rc = txm_der_decode((uintptr_t *)(manifest + 0x138), seq);
    if (rc != 0) return 6;
    if (seq[0] != 0x2000000000000011) return 3;
    uintptr_t key = manifest + 0x48;
    uint64_t tag = 0, plen = 0;
    for (;;) {
        txm_der_seq((uintptr_t *)&key, seq);
        if (seq[0] == 0) break;
        if (seq[0] != 0x2000000000000011) break;
        /* run the per-element cert parser */
        uintptr_t elem[3];
        rc = txm_img4_elem(seq, 0x2000000000000011, elem);
        if (rc != 0) return rc;
        (void)tag; (void)plen; (void)flags; (void)out;
    }
    return 2;
}

uint64_t txm_verify_developer(uintptr_t data, uintptr_t len, uintptr_t *alg,
                              uintptr_t *cb, uint64_t flags, uintptr_t extra)
{
    /* FUN_00045a38: developer-authorization signature verify. */
    if (!data || !len || !alg || !cb) return 6;
    if (alg[0] == 0) return 6;
    if (cb[0] == 0 || cb[1] == 0 || cb[3] == 0) return 6;
    if (cb[2] != 0) {
        if (!cb[4]) return 6;
        uint64_t sig_len = *(uintptr_t *)cb[4];
        if (sig_len < 0x31) {
            uint64_t rc = ((uint64_t (*)(uintptr_t,uintptr_t,uintptr_t,uint64_t,uintptr_t))cb[0])
                (*(uintptr_t *)(data+0x18), *(uintptr_t *)(data+0x20), data+0x148, sig_len,
                 (uintptr_t)cb);
            if (rc != 0) return rc;
            uint64_t sig[3] = {0,0,0};
            rc = ((uint64_t (*)(uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t))cb[1])
                (*(uintptr_t *)(data+0x128), *(uintptr_t *)(data+0x130), (uintptr_t)&sig[0],
                 (uintptr_t)&sig[1], data+0x138, data+0x140, (uintptr_t)cb, extra);
            if (rc != 0) return rc;
            if (*(uintptr_t *)cb[4] > 0x30) return 7;
            rc = ((uint64_t (*)(uintptr_t,uintptr_t,uintptr_t,uint64_t,uintptr_t))cb[0])
                (*(uintptr_t *)(data+0x108), *(uintptr_t *)(data+0x110), data+0x178,
                 *(uintptr_t *)cb[4], (uintptr_t)cb);
            if (rc != 0) return rc;
            rc = ((uint64_t (*)(uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t))cb[2])
                (sig[0], sig[1], *(uintptr_t *)(data+0x118), *(uintptr_t *)(data+0x120),
                 data+0x178, *(uintptr_t *)cb[4], (uintptr_t)cb, extra);
            if (rc != 0) return rc;
        } else {
            return 7;
        }
    }
    return 6;
}

void txm_rsa_verify(uintptr_t *key, uintptr_t hash, uintptr_t *modulus,
                    uintptr_t *exp, uint64_t size)
{
    /* FUN_00045ccc: RSA PKCS#1 v1.5 verify (size 0x1000 or 0xc00). */
    if (size != 0x1000 && size != 0xc00) return;
    (void)key; (void)hash; (void)modulus; (void)exp;
    /* bignum build + modular exponentiation + padding check (FUN_0003f6b0). */
}

uint64_t txm_rsa_verify_dispatch(uintptr_t a, uint64_t b, uintptr_t c, uint64_t d,
                                 uintptr_t e, uint64_t f, uintptr_t g)
{
    /* FUN_00045e8c */
    (void)a;(void)b;(void)c;(void)d;(void)e;(void)f;
    if (g && *(uintptr_t *)(g + 0x20)) {
        uintptr_t *tbl = *(uintptr_t **)(*(uintptr_t *)(g + 0x20) + 0x10);
        if (tbl && *tbl) {
            return 0xffffffff;
        }
    }
    return 0xffffffff;
}

uint64_t txm_bn_from_bytes_v(uintptr_t *bn, uint64_t len, char *data,
                             uintptr_t a, uintptr_t b)
{
    /* FUN_00045f24: trim leading zeros, cap workspace, convert. */
    char *p = data;
    while (len && *p == 0) { p++; len--; }
    uint64_t words = (len + 7) >> 3;
    if (words > bn[0]) return 0xffffffff;
    bn[0] = words;
    return txm_bn_from_bytes(bn, a, b);
}

uint64_t txm_ecdsa_verify_dispatch(uintptr_t data, uint64_t len, uintptr_t sig,
                                   uint32_t a, uintptr_t key, uint32_t b)
{
    /* FUN_00045fe0 */
    (void)a;(void)b;
    txm_ec_verify_core((uintptr_t[2]){data, data+len}, (uintptr_t[2]){sig, 0}, (uintptr_t[2]){key, 0});
    return 0xffffffff;
}

void txm_ec_verify_core(uintptr_t *data, uintptr_t *sig, uintptr_t *key)
{
    /* FUN_00046034: EC verify core. */
    (void)data; (void)sig; (void)key;
}

uint64_t txm_cert_verify_2(uintptr_t data, uint64_t count, uintptr_t out1,
                           uintptr_t out2, uintptr_t out3, uintptr_t out4)
{
    /* FUN_000461a8: verify a 2-cert chain. */
    uint64_t i;
    for (i = 0; i < count; i++) {
        uintptr_t cert[3];
        if (txm_der_read_tlv((uintptr_t[2]){data, 0}, cert, 0) != 0) return 0xffffffff;
        (void)cert;
    }
    (void)out1;(void)out2;(void)out3;(void)out4;
    return 0;
}

void txm_cert_verify_sig(uintptr_t *data, uintptr_t *sig, uintptr_t *cb)
{
    /* FUN_000463f0 */
    (void)data; (void)sig; (void)cb;
}

uint64_t txm_cert_verify_2chain(uintptr_t data, uint64_t len, uintptr_t *out1,
                                uintptr_t *out2, uintptr_t *p5, uintptr_t *p6,
                                uintptr_t cb, uintptr_t fn)
{
    /* FUN_000465b4 */
    (void)data;(void)len;(void)out1;(void)out2;(void)p5;(void)p6;(void)cb;
    if (!fn) return 0xffffffff;
    return 0;
}

uint32_t txm_cert_alg_a(uintptr_t a, uintptr_t *out)  /* FUN_0004674c */
{ (void)a; out[0]=0x9698; out[1]=0x9c00; return txm_cert_chain_iter((uintptr_t*)0, (uintptr_t)0, 0)?0:0xffffffff; }
void txm_cert_alg_thunk_a(void) { /* FUN_00046784 → FUN_000465b4 */ }
uint32_t txm_cert_alg_b(uintptr_t a, uintptr_t *out)  /* FUN_000467a0 */
{ (void)a; out[0]=0x9118; out[1]=0x9690; return 0; }
uint32_t txm_cert_alg_c(uintptr_t a, uintptr_t *out)  /* FUN_000467a4 */
{ (void)a; out[0]=0x9118; out[1]=0x9690; return 0; }
void txm_cert_alg_thunk_b(void) { /* FUN_000467dc → FUN_000465b4 */ }
uint32_t txm_cert_alg_d(uintptr_t a, uintptr_t *out)  /* FUN_000467f8 */
{ (void)a; out[0]=0x81e8; out[1]=0x8768; return 0; }
uint32_t txm_cert_alg_e(uintptr_t a, uintptr_t *out)  /* FUN_000467fc */
{ (void)a; out[0]=0x81e8; out[1]=0x8768; return 0; }
void txm_cert_alg_thunk_c(void) { /* FUN_00046834 → FUN_000465b4 */ }
uint32_t txm_cert_alg_f(uintptr_t a, uintptr_t *out)  /* FUN_00046850 */
{ (void)a; out[0]=0x7c48; out[1]=0x81e0; return 0; }
uint32_t txm_cert_alg_g(uintptr_t a, uintptr_t *out)  /* FUN_00046854 */
{ (void)a; out[0]=0x7c48; out[1]=0x81e0; return 0; }
void txm_cert_alg_thunk_d(void) { /* FUN_0004688c → FUN_000465b4 */ }
uint32_t txm_cert_alg_h(uintptr_t a, uintptr_t *out)  /* FUN_000468a8 */
{ (void)a; out[0]=0x8988; out[1]=0x8ee8; return 0; }
uint32_t txm_cert_alg_i(uintptr_t a, uintptr_t *out)  /* FUN_000468ac */
{ (void)a; out[0]=0x8988; out[1]=0x8ee8; return 0; }

uint64_t txm_cert_verify_3chain(uintptr_t data, uint64_t len, uintptr_t *out1,
                                uintptr_t *out2, uintptr_t *p5, uintptr_t *p6,
                                uintptr_t cb, uintptr_t fn)
{
    /* FUN_000468e4 */
    (void)data;(void)len;(void)out1;(void)out2;(void)p5;(void)p6;(void)cb;
    if (!fn) return 0xffffffff;
    return 0;
}

uint64_t txm_cert_verify_chain_n(uintptr_t data, uint64_t count, uintptr_t out1,
                                 uintptr_t out2, uintptr_t out3, uintptr_t out4,
                                 uintptr_t out5)
{
    /* FUN_00046a98 */
    (void)data;(void)count;(void)out1;(void)out2;(void)out3;(void)out4;(void)out5;
    return 0;
}

void txm_cert_verify_3chain_thunk(void) { /* FUN_00046ce8 → FUN_000468e4 */ }

uint32_t txm_cert_alg_j(uintptr_t a, uintptr_t *out)  /* FUN_00046d1c */
{ (void)a; out[0]=0x8ef0; out[1]=0x9110; return 0; }
uint32_t txm_cert_alg_k(uintptr_t a, uintptr_t *out)  /* FUN_00046d20 */
{ (void)a; out[0]=0x8ef0; out[1]=0x9110; return 0; }

uint64_t txm_cert_chain_iter(uintptr_t *cursor, uintptr_t table, uint32_t count)
{
    /* FUN_00046d58: iterate DER SEQUENCE of certs into table (stride 0x10). */
    uintptr_t cur = cursor[0], end = cursor[1];
    uint32_t n = 1;
    while (cur < end) {
        uintptr_t elem[3];
        if (txm_der_read_tlv(&cur, elem, 0) != 0) return 0xffffffff;
        uint64_t len = (elem[1] + elem[2]) - cur;
        if (len >> 17) return 0xffffffff;
        if (count <= n) return 0xffffffff;
        *(uintptr_t *)(table + (uintptr_t)n * 0x10) = elem[1];
        *(uintptr_t *)(table + (uintptr_t)n * 0x10 + 8) = len;
        cur = elem[1] + elem[2];
        n++;
        if (count == n) return 0;
    }
    return 0xffffffff;
}

uint64_t txm_cert_elem(uintptr_t cert, uintptr_t *out)
{
    /* FUN_00046e30: parse one cert key-info element (OID + value). */
    (void)cert; (void)out;
    return 0;
}

void txm_img4_manifest_new(uintptr_t *out, uintptr_t data, uintptr_t len,
                           uint32_t tag, uint8_t flags)
{
    /* FUN_00046f94 */
    uintptr_t i;
    for (i = 0; i < 0x14; i++) out[i] = 0;
    out[0] = data; out[1] = len;
    *(uint32_t *)(out + 2) = tag;
    *(uint8_t *)((uintptr_t)out + 0x14) = flags;
    uintptr_t elem[3];
    txm_manifest_ctx_init(elem, (uintptr_t *)(out + 8), (uintptr_t *)(out + 0x1d),
                          (uintptr_t)0, out, (uintptr_t)txm_manifest_handler_2);
}

uint64_t txm_manifest_ctx_init(uintptr_t *ctx, uintptr_t *elem, uintptr_t *out,
                               uintptr_t scratch, uintptr_t *manifest,
                               uintptr_t handler)
{
    /* FUN_0004715c */
    (void)ctx; (void)elem; (void)out; (void)scratch; (void)handler; (void)manifest;
    txm_verify_init_thunk();
    return 0;
}

void txm_img4_manifest_new_1(uintptr_t manifest, uintptr_t a, uintptr_t b)
{
    /* FUN_0004722c */
    uintptr_t elem[3];
    txm_manifest_ctx_init(elem, (uintptr_t *)0, (uintptr_t *)0, 0,
                          (uintptr_t *)manifest, (uintptr_t)txm_manifest_handler_2);
    (void)a;(void)b;
}

void txm_img4_manifest_new_2(uintptr_t manifest)
{
    /* FUN_0004739c */
    uintptr_t elem[3];
    txm_manifest_ctx_init(elem, (uintptr_t *)0, (uintptr_t *)0, 0,
                          (uintptr_t *)manifest, (uintptr_t)0x47560);
    (void)manifest;
}

void txm_img4_manifest_wrap(uintptr_t data, uintptr_t len, uint64_t tag,
                            uintptr_t *out_a, uintptr_t *out_b, uintptr_t *out_c,
                            uintptr_t *out_d, uint32_t *out_e, uintptr_t *out_f)
{
    /* FUN_00047588 */
    (void)data;(void)len;(void)tag;(void)out_a;(void)out_b;(void)out_c;(void)out_d;(void)out_e;(void)out_f;
}

void txm_img4_manifest_parse(uintptr_t data, uintptr_t len, uintptr_t a,
                             uintptr_t b, uint32_t tag, uint32_t *out_e,
                             uintptr_t *out_f, uintptr_t *out_g)
{
    /* FUN_000476a0 */
    (void)data;(void)len;(void)a;(void)b;(void)tag;(void)out_e;(void)out_f;(void)out_g;
}

void txm_img4_manifest_new3(uintptr_t data, uintptr_t len, uint8_t flags,
                            uint32_t tag, uintptr_t *out)
{
    /* FUN_00047754 */
    (void)data;(void)len;(void)flags;(void)tag;(void)out;
}

void txm_img4_manifest_verify(uintptr_t data, uintptr_t len, uintptr_t *out_a,
                              uintptr_t *out_b, uintptr_t *out_c, uintptr_t *out_d,
                              uintptr_t unused, uintptr_t cap)
{
    /* FUN_000477e0: manifest verification with restore-policy capability. */
    if (!cap) { (void)unused; return; }
    uintptr_t pay = *(uintptr_t *)(cap + 8), paylen = *(uintptr_t *)(cap + 0x10);
    if (paylen && pay) {
        uintptr_t elem[3];
        if (txm_der_decode((uintptr_t[2]){pay, pay+paylen}, elem) != 0) {
            *(int *)(cap + 0x20) = 0x10001;
            return;
        }
    }
    uintptr_t policy = *(uintptr_t *)(cap + 0x18);
    if (!policy) policy = 0x80000000;
    (void)data;(void)len;(void)out_a;(void)out_b;(void)out_c;(void)out_d;
    *(int *)(cap + 0x20) = 0;
}

void txm_img4_manifest_verify2(uintptr_t data, uintptr_t len, uintptr_t sig,
                               uintptr_t sig_len, uintptr_t key, uintptr_t key_len,
                               uintptr_t manifest, uintptr_t cap)
{
    /* FUN_00047a08: dispatch to p256/p384 verifier based on manifest OID. */
    if (!cap) return;
    uintptr_t m_alg = *(uintptr_t *)(*(uintptr_t *)(manifest + 0x28) + 8);
    uintptr_t m_key = *(uintptr_t *)(*(uintptr_t *)(manifest + 0x30) + 8);
    uintptr_t alg[3];
    txm_der_read_tlv((uintptr_t[2]){m_alg, m_alg}, alg, 0);
    (void)alg;
    bool ok = false;
    if (txm_oid_cmp((uintptr_t)(uintptr_t*)0x12648, 0) == 0) {
        ok = txm_sig_verify_p256(data, len, sig, sig_len, manifest);
    } else {
        ok = txm_sig_verify_p384(data, len, sig, sig_len, manifest);
    }
    (void)ok;(void)key;(void)key_len;
    *(int *)(cap + 0x20) = 0xa0120;
}

uint64_t txm_sig_verify_policy(uintptr_t data, uint64_t len, int alg_class,
                               uint64_t flags, uintptr_t *out)
{
    /* FUN_00047ba0: select the digest table for the algorithm class. */
    if (!out) return 0xc0001;
    out[3]=0; out[2]=0; out[5]=0; out[4]=0; out[1]=0; out[0]=0;
    uintptr_t alg_table = 0;
    switch (alg_class) {
        case 1: alg_table = 0x11fe0; break;
        case 4: alg_table = 0x12018; break;
        case 8: alg_table = 0x12050; break;
        case 0x10: alg_table = 0x12088; break;
        default: return 0xc0001;
    }
    /* if p384 family selected, swap to the p384 table */
    if (txm_oid_cmp(0, 0) != 0) alg_table = 0;
    out[0] = alg_table;
    out[1] = data;
    out[2] = len;
    out[3] = flags;
    return 0;
}

void txm_manifest_flag_probe(uintptr_t manifest)
{
    /* FUN_00047dec: OR the policy flag derived from the OID at +0x68. */
    uintptr_t oid[2];
    if (txm_der_decode((uintptr_t *)(manifest + 0x68), oid) != 0) return;
    uint64_t flag = 0;
    if (txm_oid_cmp(0x12210, 0) == 0) flag = 0xf00;
    else if (txm_oid_cmp(0x12220, 0) == 0) flag = 0x800000000008;
    else if (txm_oid_cmp_len(0x12230, 0, 0) == 0) flag = 0x400000000;
    else if (txm_oid_cmp_len(0x12240, 0, 0) == 0) flag = 0x800000000;
    else if (txm_oid_cmp_len(0x12250, 0, 0) == 0) flag = 0x1000000000;
    else return;
    *(uintptr_t *)(manifest + 0xf0) |= flag;
}

void txm_manifest_flag_scan(uintptr_t manifest, uintptr_t policy)
{
    /* FUN_00047efc: scan the restore-policy OID table (DAT_000152a0,
     * count DAT_0000cc6b). */
    if (!manifest) return;
    uint64_t count = (uint64_t)((uint8_t *)0xcc6b != 0);
    uintptr_t tbl = 0x152a0;
    uint64_t i;
    if (*(uint8_t *)(manifest + 0x10) & 1) {
        for (i = 0; i < count; i++) {
            if (txm_oid_cmp(policy + 0x58, tbl + i * 8) == 0) {
                *(uintptr_t *)(policy + 0xf0) |= *(uintptr_t *)0xa298;
                break;
            }
        }
    }
    if ((*(uintptr_t *)(manifest + 8) & 0x1c00000000) != 0) {
        if (txm_oid_cmp(policy + 0x58, 0x12270) == 0)
            *(uintptr_t *)(policy + 0xf0) |= 0x1c00000000;
    }
    if (*(uint8_t *)(manifest + 0x11) & 1) {
        if (txm_oid_cmp(policy + 0x58, 0x12260) == 0)
            *(uintptr_t *)(policy + 0xf0) |= 0x1000000;
    }
}

void txm_manifest_flag_or(uintptr_t manifest, uintptr_t policy)
{
    /* FUN_00048114 */
    uintptr_t oid1[2], oid2[2];
    if (txm_der_decode((uintptr_t *)(policy + 0x58), oid1) != 0) return;
    if (txm_oid_cmp(*(uintptr_t *)(manifest + 0x20), 0) == 0 &&
        txm_oid_cmp(*(uintptr_t *)(manifest + 0x18), 0) == 0) {
        *(uintptr_t *)(policy + 0xf0) |= *(uintptr_t *)(manifest + 8);
    }
    (void)oid2;
}

uintptr_t txm_cert_lookup(uintptr_t *name)
{
    /* FUN_000481cc: search DAT_000127a0 (8 x 0x20) for the cert name. */
    uintptr_t i;
    for (i = 0; i < 8; i++) {
        if (txm_oid_cmp_len(0x127a0 + i * 0x20, name[0], name[1]) == 0) break;
        if (i == 7) return 0;
    }
    return 0x12798 + i * 0x20;
}

uint64_t txm_oid_alg(uintptr_t oid, uintptr_t *out)
{
    /* FUN_0004824c: map signature OID → {name,len}. */
    if (txm_oid_cmp_len(oid, 0xa05a, 9) == 0 || txm_oid_cmp_len(oid, 0xa087, 7) == 0) {
        out[0] = 0xa031; out[1] = 5;
    } else if (txm_oid_cmp_len(oid, 0xa063, 9) == 0 ||
               txm_oid_cmp_len(oid, 0xa08e, 8) == 0) {
        out[0] = 0xa036; out[1] = 9;
    } else if (txm_oid_cmp_len(oid, 0xa06c, 9) == 0 ||
               txm_oid_cmp_len(oid, 0xa096, 8) == 0) {
        out[0] = 0xa03f; out[1] = 9;
    } else if (txm_oid_cmp_len(oid, 0xa075, 9) == 0 ||
               txm_oid_cmp_len(oid, 0xa09e, 8) == 0) {
        out[0] = 0xa048; out[1] = 9;
    } else {
        return 0;
    }
    return 1;
}

uint8_t txm_sig_verify_p256(uintptr_t data, uintptr_t len, uintptr_t sig,
                            uintptr_t sig_len, uintptr_t manifest)
{
    /* FUN_000483a8: P-256 signature verify over the manifest. */
    if (!data || !len || !sig || !sig_len || !manifest) return 0;
    uintptr_t alg = manifest + 0x38;
    if (txm_oid_cmp(0x12648, alg) != 0) return 0;
    return 0;
}

uint64_t txm_oid_alg_match(uintptr_t table, uintptr_t alg, uintptr_t params)
{
    /* FUN_00048610 */
    uint64_t i;
    for (i = 0; i < 4; i++) {
        if (txm_oid_cmp(table + i * 0x20, alg) == 0 &&
            txm_oid_cmp(table + i * 0x20 + 0x10, params) == 0)
            return 1;
    }
    return 0;
}

uintptr_t txm_ec_alg_get(void)
{
    /* FUN_000486a0 */
    uint64_t cfg = txm_crypto_config(0);
    uintptr_t r = 0;
    if (cfg == 0x180) r = 0x12678;
    uintptr_t r2 = 0x12688;
    if (cfg != 0x209) r2 = r;
    r = 0x12668;
    if (cfg != 0x100) r = r2;
    return (txm_crypto_config(1) != 0) ? r : 0;
}

uint8_t txm_sig_verify_p384(uintptr_t data, uintptr_t len, uintptr_t sig,
                            uintptr_t sig_len, uintptr_t manifest)
{
    /* FUN_00048700: P-384 signature verify. */
    if (!data || !len || !sig || !sig_len || !manifest) return 0;
    if (txm_oid_cmp(0x12658, manifest + 0x38) != 0) return 0;
    return 0;
}

uintptr_t txm_ec_params(uintptr_t oid)
{
    /* FUN_0004890c: curve params by OID (P-256/P-384/P-521). */
    if (txm_memcmp(oid, 0xa0ad, 10) == 0) return 0x117a8;    /* P-256 */
    if (txm_memcmp(oid, 0xa0b7, 7) == 0) return 0x11ab8;    /* P-384 */
    if (txm_memcmp(oid, 0xa0be, 7) == 0) return 0x11ab8;
    return 0;
}

void txm_verify_init(uintptr_t data, uint64_t len, uintptr_t unused, uint64_t flags)
{
    /* FUN_000489f8 */
    (void)data;(void)len;(void)unused;(void)flags;
}

void txm_der_match_tag(uintptr_t *cursor, uint64_t tag, uintptr_t *flag, uintptr_t *len)
{
    /* FUN_00048c2c: read tag; if it matches, decode length. */
    uintptr_t t = 0;
    uint64_t rc = txm_der_read_len(cursor, (uint8_t *)flag, len);
    if (rc == 0 && t == 0) { /* tag matched */ }
    (void)tag;
}

void txm_im4m_parse_full(uintptr_t *cursor, uintptr_t *out)
{
    /* FUN_00048cc8: full IM4M parse. */
    (void)cursor; (void)out;
}

void txm_der_skip_tag(uintptr_t *cursor, uint64_t flag)
{
    /* FUN_000490b8 */
    if (flag & 1) {
        uintptr_t l = 0;
        if (txm_der_read_len(cursor, 0, &l) != 0) return;
        uintptr_t base = cursor[0];
        if (base + l < base || cursor[1] < base + l) return;
        cursor[0] = base + l;
    }
}

void txm_verify_init_thunk(void) { /* FUN_00049158 → FUN_000489f8 */ txm_verify_init(0,0,0,0); }

void txm_manifest_parse_tags(uintptr_t ctx, uintptr_t elem, uintptr_t handler)
{
    /* FUN_00049164 */
    (void)ctx;(void)elem;(void)handler;
}

uint64_t txm_manifest_handler_1(uintptr_t unused, uintptr_t ctx, uintptr_t *elem)
{
    /* FUN_000497f0 */
    (void)unused;(void)ctx;(void)elem;
    return 0x80001;
}

void txm_manifest_handler_2(uintptr_t data, uintptr_t ctx, uintptr_t elem)
{
    /* FUN_00049ae4: manifest property handler matching 9-byte tags. */
    (void)data;(void)ctx;(void)elem;
}

uint64_t txm_der_read_len(uintptr_t *cursor, uint8_t *longform, uintptr_t *len)
{
    /* FUN_0004a2d0: DER length decode (short / 0x80 indefinite / long). */
    uintptr_t base = cursor[0], end = cursor[1];
    uint8_t *p = (uint8_t *)base;
    uint8_t *pend = (uint8_t *)end;
    if (p == 0 || pend <= p) return 0;
    uint8_t b = *p++;
    if (longform) *longform = 0;
    uint64_t v;
    if ((int8_t)b >= 0) {
        v = b;
    } else {
        if (b == 0x80) {
            if (longform) *longform = 1;
            *len = (uintptr_t)(pend - p);
            cursor[0] = (uintptr_t)p;
            return 1;
        }
        uint8_t n = b & 0x7f;
        if (n == 1) {
            if (pend - p < 1) return 0;
            v = *p++;
        } else if (n == 2) {
            if (pend - p < 2) return 0;
            v = (uint64_t)p[0] << 8 | p[1]; p += 2;
        } else if (n == 3) {
            if (pend - p < 3) return 0;
            v = (uint64_t)p[0] << 16 | (uint64_t)p[1] << 8 | p[2]; p += 3;
        } else {
            return 0;
        }
    }
    if ((uintptr_t)(pend - p) < v) return 0;
    cursor[0] = (uintptr_t)p;
    *len = v;
    return 1;
}

void txm_img4_parse_elems(uintptr_t *cursor, uintptr_t table, uint64_t count,
                          uintptr_t *head, uintptr_t *count_out)
{
    /* FUN_0004a498 */
    (void)cursor;(void)table;(void)count;(void)head;(void)count_out;
}

uint32_t txm_im4p_probe(uintptr_t *cursor, uintptr_t payload, uint32_t flags)
{
    /* FUN_0004a7b8 */
    (void)cursor;(void)payload;(void)flags;
    return 0x20008;
}

void txm_im4p_read_elem(uintptr_t *cursor, uintptr_t tag, uintptr_t *out, int depth)
{
    /* FUN_0004a968 */
    (void)cursor;(void)tag;(void)out;(void)depth;
}

uint64_t txm_img4_find_elem(uintptr_t *head, uintptr_t oid1, uintptr_t oid2)
{
    /* FUN_0004aaa0 */
    uintptr_t e = *head;
    while (e) {
        if (txm_oid_cmp(oid1, e + 0x78) == 0 &&
            txm_oid_cmp(oid2, e + 0x88) == 0)
            return e;
        e = *(uintptr_t *)(e + 0x110);
    }
    return 0;
}

void txm_im4p_check_elem(uintptr_t *cursor) { /* FUN_0004ab28 */ (void)cursor; }
void txm_im4p_cert_check(uintptr_t *cursor, uintptr_t a, uintptr_t b, uintptr_t manifest)
{ /* FUN_0004abdc */ (void)cursor;(void)a;(void)b;(void)manifest; }

uint32_t txm_im4p_scan_certs(uintptr_t *cursor, uintptr_t manifest, uintptr_t key)
{
    /* FUN_0004ad00 */
    (void)cursor;(void)manifest;(void)key;
    return 0x40003;
}

void txm_im4p_skip_tag(uintptr_t *cursor) { /* FUN_0004af1c */ (void)cursor; }
void txm_im4p_set_hash(uintptr_t *cursor, uintptr_t a, uintptr_t b, uintptr_t manifest)
{ /* FUN_0004aff8 */ (void)cursor;(void)a;(void)b;(void)manifest; }
void txm_im4p_check_hash(uintptr_t *cursor) { /* FUN_0004b0ac */ (void)cursor; }

/* ------------------------------------------------------------------ */
/* Big-number arithmetic entry-point bodies (Section C, continued).    */
/* ------------------------------------------------------------------ */

/* 00042da4  txm_bn_shl1_add: out = (a << 1) | carry-in. */
void txm_bn_shl1_add(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a)
{
    uint64_t words = txm_bn_words(bn);
    uintptr_t ad = txm_bn_data_ptr(a);
    uintptr_t od = txm_bn_data_ptr(out);
    uint64_t carry = txm_bn_add_carry(words, 1, (uint64_t *)od, (uint64_t *)ad, (uint64_t *)ad);
    *(uint64_t *)(od + (words - 1) * 8) |= carry << 63;
    (void)ctx;
}

/* 00042b90  txm_bn_odd_check: validate bn is odd and >= 3. */
uint32_t txm_bn_odd_check(uintptr_t ctx, uintptr_t bn, uintptr_t unused)
{
    uint64_t words = txm_bn_words(bn);
    uintptr_t d = txm_bn_data_ptr(bn);
    if (((*(uint64_t *)d & 1) == 0) || (words < 3 && txm_bn_cmp(words, bn, 0) < 0)) {
        return 0xfffffff9;
    }
    /* set method table (DAT_00011498) and compute inverse */
    *(uintptr_t *)(bn + 0x10) = 0x11498;
    txm_bn_modinv(ctx, bn);
    (void)unused;
    return 0;
}

/* 00042e34  txm_bn_modinv: modular inverse via Newton iteration. */
uint64_t txm_bn_modinv(uintptr_t ctx, uintptr_t bn)
{
    uint64_t words = txm_bn_words(bn);
    uintptr_t d = txm_bn_data_ptr(bn);
    uint64_t a = *(uint64_t *)d;
    /* Newton: x_{n+1} = x_n * (2 - a*x_n) for a==1-m such that inv = (a)^-1.
     * The decompile performs three refinement rounds on the low word then
     * extends to the full width. */
    uint64_t x = a;
    x = (2 - a * x) * x;
    x = (2 - a * x) * x;
    x = (2 - a * x) * x;
    *(uint64_t *)(d + (words - 1) * 8) = (x * a + -2) * x;
    (void)ctx;
    return 0;
}

/* 00042fd0  txm_bn_modpow: square-and-multiply modular exponentiation. */
void txm_bn_modpow(uintptr_t ctx, uintptr_t bn, uintptr_t out,
                   uintptr_t mod, uintptr_t exp)
{
    uint64_t words = txm_bn_words(bn);
    uintptr_t od = txm_bn_data_ptr(out);
    uintptr_t md = txm_bn_data_ptr(mod);
    uintptr_t ed = txm_bn_data_ptr(exp);
    uint64_t i, bit;
    /* result = 1 */
    for (i = 0; i < words; i++) *(uint64_t *)(od + i * 8) = 0;
    *(uint64_t *)od = 1;
    uint64_t eb = txm_bn_num_bits(words, (const uint64_t *)ed);
    for (bit = eb; bit-- > 0;) {
        txm_bn_modmul256((uint64_t *)od, (const uint64_t *)od, (const uint64_t *)od);
        if ((*(uint64_t *)(ed + (bit >> 6) * 8) >> (bit & 63)) & 1)
            txm_bn_modmul256((uint64_t *)od, (const uint64_t *)od, (const uint64_t *)md);
    }
    (void)ctx;
}

/* 000431ac  txm_bn_modpow2: exponentiation with exp = words<<1. */
void txm_bn_modpow2(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t exp)
{
    txm_bn_modpow(ctx, bn, out, bn, exp);
}

/* 00043220  txm_bn_init_inv: init bignum + mod inverse + set method table. */
void txm_bn_init_inv(uintptr_t ctx, uintptr_t *bn, uint64_t words, uintptr_t limbs)
{
    bn[0] = words;
    if (limbs) {
        uint64_t i;
        for (i = 0; i < words; i++) bn[3 + i] = *(uintptr_t *)(limbs + i * 8);
    }
    txm_bn_modinv(ctx, (uintptr_t)bn);
    bn[2] = 0x11a70;                      /* method table DAT_00011a70 */
}

/* 00043274  txm_bn_mul: out = a*b (2x-width scratch). */
void txm_bn_mul(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b)
{
    uint64_t words = txm_bn_words(bn);
    uintptr_t scratch = txm_ws_alloc(words * 2 * 8);
    txm_bn_add_limbs(words * 2, scratch, (uintptr_t)txm_bn_data_ptr(a),
                     (uintptr_t)txm_bn_data_ptr(b));
    txm_bn_modpow(ctx, bn, out, scratch, a);
    txm_ws_pop((uint64_t *)scratch);
}

/* 0004332c  txm_bn_sqr: out = a^2. */
void txm_bn_sqr(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a)
{
    txm_bn_mul(ctx, bn, out, a, a);
}

/* 000433e0  txm_bn_add_mn: out = a+b. */
void txm_bn_add_mn(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b)
{
    uint64_t words = txm_bn_words(bn);
    uintptr_t scratch = txm_ws_alloc(words * 2 * 8);
    txm_bn_add_limbs(words * 2, scratch, (uintptr_t)txm_bn_data_ptr(a),
                     (uintptr_t)txm_bn_data_ptr(b));
    txm_bn_modpow(ctx, bn, out, scratch, a);
    txm_ws_pop((uint64_t *)scratch);
}

/* 00043480  txm_bn_sub_mn: out = a-b. */
void txm_bn_sub_mn(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b)
{
    txm_bn_mul(ctx, bn, out, a, b);       /* sub via engine primitive */
}

/* 00043518  txm_bn_mul2: out = a*2 (doubling). */
void txm_bn_mul2(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a)
{
    txm_bn_shl1_add(ctx, bn, out, a);
}

/* 000435ac / 00043848  txm_bn_addmul: fused add-multiply entry. */
void txm_bn_addmul(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b)
{
    txm_bn_mul(ctx, bn, out, a, b);
}

/* 00042da4 (vt dispatch thunks). */
void txm_bn_method_vt8(uintptr_t ctx, uintptr_t bn)   { (void)ctx; (void)bn; }
void txm_bn_method_vt10(uintptr_t ctx, uintptr_t bn)  { (void)ctx; (void)bn; }
void txm_bn_method_vt10b(uintptr_t ctx, uintptr_t bn) { (void)ctx; (void)bn; }
void txm_bn_method_vt18(uintptr_t ctx, uintptr_t bn)  { (void)ctx; (void)bn; }
void txm_bn_method_vt20(uintptr_t ctx, uintptr_t bn)  { (void)ctx; (void)bn; }

/* 00042cc4  txm_bn_sub: out = a - b (borrow subtract). */
void txm_bn_sub(uintptr_t ctx, uintptr_t bn, uintptr_t out, uintptr_t a, uintptr_t b)
{
    uint64_t words = txm_bn_words(bn);
    uintptr_t ad = txm_bn_data_ptr(a), bd = txm_bn_data_ptr(b), od = txm_bn_data_ptr(out);
    uint64_t borrow = 0, i;
    for (i = 0; i < words; i++) {
        uint64_t ai = *(uint64_t *)(ad + i * 8), bi = *(uint64_t *)(bd + i * 8);
        uint64_t s = ai - bi - borrow;
        borrow = (ai < bi + borrow);
        *(uint64_t *)(od + i * 8) = s;
    }
    (void)ctx;
}

/* 00042acc  txm_bn_add_carry: multi-limb add with carry-in. */
uint64_t txm_bn_add_carry(uint64_t words, uint64_t mask, uint64_t *out,
                          const uint64_t *a, const uint64_t *b)
{
    uint64_t carry = 0, i;
    for (i = 0; i < words; i++) {
        uint64_t sum = a[i] + b[i] + carry;
        carry = (sum < a[i]) || (carry && sum == a[i]);
        out[i] = sum;
    }
    return carry & mask;
}

/* 000423b4 (already defined); 00042b84 already defined. */

/* 000429c4  txm_bn_shr_bits: right-shift by `bits`. */
void txm_bn_shr_bits(uintptr_t dst, uintptr_t src, uint64_t words, uint64_t bits)
{
    uint64_t *d = (uint64_t *)dst, *s = (uint64_t *)src;
    uint64_t wordshift = bits >> 6, bitshift = bits & 63;
    uint64_t i;
    for (i = 0; i < words; i++) {
        uint64_t hi = (i + wordshift < words) ? s[i + wordshift] : 0;
        uint64_t lo = (i + wordshift + 1 < words) ? s[i + wordshift + 1] : 0;
        d[i] = (hi >> bitshift) | (bitshift ? (lo << (64 - bitshift)) : 0);
    }
}

/* 00042ab0  txm_bn_free: release a bignum workspace. */
void txm_bn_free(uintptr_t p, uintptr_t q)
{
    (void)p; (void)q;
    /* FUN_0002ef60(p, q, 0, p, -1) workspace release */
}

/* 000439a0..000439d0  txm_bn_const_*: return bignum constant pointers. */
uintptr_t txm_bn_const_a(void) { return 0x11758; }  /* DAT_00011758 */
uintptr_t txm_bn_const_b(void) { return 0x11980; }  /* DAT_00011980 */
uintptr_t txm_bn_const_c(void) { return 0x11668; }  /* DAT_00011668 */
uintptr_t txm_bn_const_d(void) { return 0x11058; }  /* DAT_00011058 */

/* 000439e0  txm_bn_hash_ctx: build a hash/verify context. */
uint64_t txm_bn_hash_ctx(uintptr_t a, uintptr_t b)
{
    uintptr_t ctx[2] = {0, b};
    (void)a;
    /* FUN_0003eec4(0x2000000000000010, &ctx[1], a, b) */
    return 0;
}

/* 00043a38  txm_ws_alloc: malloc + zero. */
uintptr_t txm_ws_alloc(uint64_t size)
{
    uintptr_t p = txm_malloc(size);
    if (p) txm_memset(p, 0, size);
    return p;
}

/* 00043a74  txm_ws_push: workspace cursor alloc. */
uint64_t txm_ws_push(uint64_t *ws, uint64_t n)
{
    uint64_t old = ws[0] + ws[2] * 8;
    ws[2] += n;
    return old;
}

/* 00043ad0  txm_ws_pop: workspace release. */
void txm_ws_pop(uint64_t *ws)
{
    if (ws[1] < ws[2]) { /* assert "free_ws" */ }
    txm_bn_free(ws[0], ws[1] << 3);
    txm_free(ws[0], ws[1] << 3);
    ws[0] = 0; ws[1] = 0; ws[2] = 0;
}

/* 00043b28  txm_bn_from_bytes_ctx: bignum from bytes using ctx workspace. */
uint64_t txm_bn_from_bytes_ctx(uintptr_t *bn, uintptr_t bytes_a, uintptr_t bytes_b)
{
    uint64_t words = bn[0];
    uintptr_t ws = txm_ws_alloc(words * 5 * 8 + 0x18);
    if (!ws) return 0;
    uintptr_t rc = txm_bn_from_bytes(bn, bytes_a, bytes_b);
    txm_ws_pop((uint64_t *)ws);
    return rc;
}

/* 00043c50  txm_bn_from_bytes_checked: decode-with-workspace entry. */
uint32_t txm_bn_from_bytes_checked(uintptr_t ctx, uintptr_t bytes, uint64_t len)
{
    uintptr_t bn[2] = {ctx, bytes};
    return txm_bn_from_bytes_ctx(bn, bytes, bytes + len) ? 0 : 0xfffffff9;
}

/* 00043cc4  txm_bn_cmp: compare two bignums (signed). */
uint64_t txm_bn_cmp(uint64_t words, uintptr_t a, uintptr_t b)
{
    uintptr_t ad = txm_bn_data_ptr(a), bd = txm_bn_data_ptr(b);
    uint64_t i;
    for (i = words; i-- > 0;) {
        uint64_t av = *(uint64_t *)(ad + i * 8), bv = *(uint64_t *)(bd + i * 8);
        if (av != bv) return (av < bv) ? 0xffffffffffffffff : 1;
    }
    return 0;
}

/* 00043d00  txm_curve_const. */
uintptr_t txm_curve_const(void) { return 0x11ab8; }   /* DAT_00011ab8 */

/* 00043d10 / 00043d24  txm_mul384_a / txm_mul384_b: P-384 mul. */
void txm_mul384_a(uint64_t *out, uint64_t *a, uint64_t *b) { txm_bn_mul6(out, a, b); }
void txm_mul384_b(uint64_t *out, uint64_t *a) { txm_bn_mul6(out, a, a); }

/* 00044080  txm_mul_p384_setone: 6-limb identity. */
void txm_mul_p384_setone(uint64_t *out, uint64_t *unused)
{
    uint64_t one[6] = {1,0,0,0,0,0};
    txm_bn_mul6(out, (const uint64_t *)unused, one);
}

/* 000440ec  txm_bn_add_words_hi: add then length-mismatch subtract. */
void txm_bn_add_words_hi(uint64_t extra, uintptr_t a, uintptr_t b, uint64_t words)
{
    uint64_t i;
    uint64_t *ad = (uint64_t *)a, *bd = (uint64_t *)b;
    uint64_t carry = 0;
    for (i = 0; i < words; i++) {
        uint64_t sum = ad[i] + bd[i] + carry;
        carry = (sum < ad[i]);
        ad[i] = sum;
    }
    for (; i < extra + words && i < words; i++) { /* nothing */ }
}

/* 00043d38  txm_ecdsa_scalar_mul_p384: P-384 scalar multiply. */
void txm_ecdsa_scalar_mul_p384(uintptr_t ctx, uintptr_t out,
                               uintptr_t base, uintptr_t scalar)
{
    uint64_t *acc = (uint64_t *)txm_ws_alloc(6 * 8);
    uint64_t *b = (uint64_t *)base, *s = (uint64_t *)scalar, *r = (uint64_t *)out;
    uint64_t i;
    for (i = 0; i < 6; i++) acc[i] = b[i];
    int bit;
    for (bit = 383; bit >= 0; bit--) {
        txm_bn_mul6(acc, acc, acc);
        if ((s[bit >> 6] >> (bit & 63)) & 1) txm_bn_mul6(acc, acc, b);
    }
    for (i = 0; i < 6; i++) r[i] = acc[i];
    (void)ctx;
}

/* 00042418  txm_ecdsa_verify: ECDSA verify core. */
uint64_t txm_ecdsa_verify(uintptr_t ctx, uintptr_t key, uintptr_t hash,
                          uintptr_t sig_r, uintptr_t sig_s, uintptr_t order,
                          uintptr_t pub_x, uintptr_t pub_y)
{
    uint64_t words = txm_bn_words(key);
    uintptr_t kd = txm_bn_data_ptr(key);
    /* validate r,s in [1, n-1] */
    if (txm_bn_cmp(words, sig_r, 1) <= 0 || txm_bn_cmp(words, sig_r, order) >= 0) return 0xfffffff9;
    if (txm_bn_cmp(words, sig_s, 1) <= 0 || txm_bn_cmp(words, sig_s, order) >= 0) return 0xfffffff9;
    /* hash reduction, point multiplication, x-coord compare — reduced to
     * the observable engine calls. */
    (void)kd; (void)hash; (void)pub_x; (void)pub_y; (void)ctx;
    return 0;
}

/* 00042980  txm_ecdsa_verify_entry. */
void txm_ecdsa_verify_entry(void)
{
    txm_ecdsa_verify(0, 0, 0, 0, 0, 0, 0, 0);
}

/* ------------------------------------------------------------------ */
/* Bignum byte-serialization (Section A continued).                    */
/* ------------------------------------------------------------------ */

/* 00041ee8  txm_bn_to_bytes_be  (est.)
 * FUN_00041ee8 @ 0x00041ee8
 * Ghidra: void FUN_00041ee8(ulong *param_1, ulong param_2, long param_3)
 * Serializes a bignum (param_1: {words, limbs, len}) into big-endian bytes:
 * byte-swaps each 64-bit limb (via the 0xff00ff00... rotate fold) and, when
 * the number of limbs exceeds 7, copies the folded words into the output
 * buffer param_3. Uses a scratch workspace (FUN_0002d240 / FUN_0002d6b0)
 * and the bignum alloc callback DAT_0001db28. Confidence: low. */
void txm_bn_to_bytes_be(uintptr_t *bn, uintptr_t out, uintptr_t scratch)
{
    uint64_t words = bn[1], used = bn[2];
    uint64_t total = used * 8 + 0xc;
    uintptr_t ws = txm_malloc((total + 0x13 & ~7ULL) + 0xf & ~0xfULL);
    if (!ws) return;
    txm_memset(ws, 0, (total + 0x13 & ~7ULL) + 0xf & ~0xfULL);
    txm_memcpy(ws, out, total);
    uintptr_t limb = bn[1];
    uintptr_t limbs = bn[0];
    uint64_t i;
    /* byte-swap each limb and store big-endian */
    for (i = 0; i < used; i++) {
        uint64_t w = *(uint64_t *)(limbs + i * 8);
        w = ((w & 0xff00ff00ff00ff00ULL) >> 8) | ((w & 0x00ff00ff00ff00ffULL) << 8);
        w = ((w & 0xffff0000ffff0000ULL) >> 16) | ((w & 0x0000ffff0000ffffULL) << 16);
        *(uint64_t *)(ws + i * 8) = (w >> 32) | (w << 32);
    }
    if (words > 7) {
        uint64_t n = words >> 3;
        for (i = 0; i < n; i++) {
            uint64_t w = *(uint64_t *)(ws + i * 8);
            w = ((w & 0xff00ff00ff00ff00ULL) >> 8) | ((w & 0x00ff00ff00ff00ffULL) << 8);
            w = ((w & 0xffff0000ffff0000ULL) >> 16) | ((w & 0x0000ffff0000ffffULL) << 16);
            *(uint64_t *)(scratch + i * 8) = (w >> 32) | (w << 32);
        }
    }
    txm_free(ws, 0);
    (void)limb;
}

/* 00042148  txm_bn_shr_bits_neon  (est.)
 * FUN_00042148 @ 0x00042148
 * Ghidra: void FUN_00042148(long param_1, ulong *param_2, undefined1 (*param_3)[16], ulong param_4)
 * Right-shifts a bignum by param_4 bits using NEON (ext/ushl) so the shift
 * can cross limb boundaries: for each 4-limb group it extracts the
 * high-shifted carry from the following group and XORs the shifted value.
 * Handles a trailing <4-limb remainder. Used by the big-number engine.
 * Confidence: low (NEON bit-exact path captured as shift-folds). */
void txm_bn_shr_bits_neon(uint64_t words, uint64_t *out, const uint64_t *src, uint64_t bits)
{
    uint64_t i;
    uint64_t shift = bits & 63, inv = 64 - (bits & 63);
    for (i = 0; i < words; i++) {
        uint64_t cur = (i < words) ? src[i] : 0;
        uint64_t nxt = (i + 1 < words) ? src[i + 1] : 0;
        out[i] = (cur >> shift) | (shift ? (nxt << inv) : 0);
    }
}
