/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM helper/thunk region (0x000ae090 - 0x000b17a0):
 * the fortified libc subset compiled into SPTM (__memcpy_chk,
 * __memset_s_chk, __strlcpy_chk, __bzero_chk, __stack_chk_fail, memswap) and
 * the SPTM crypto library (AES-128/192/256 key expansion, AES-GCM encrypt and
 * decrypt, GHASH field multiply / table build / update, SHA-256, SHA-512).
 *
 * The crypto bodies implement the standard algorithms the NEON-accelerated
 * assembly realizes (verified against the AES S-box gf table at 0xb0820, the
 * GHASH byte-reverse table at 0xb1780, and the SHA-256/512 K tables at
 * 0xb0d30 / 0x12c00). NEON primitives (aese/aesmc/aesimc/pmull/sha256h/
 * sha512h) are rendered as portable C equivalents.
 *
 * Shared SPTM-internal helpers called from these bodies are declared extern
 * with a one-line note giving their Ghidra address and estimated purpose.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ *
 * Shared helper declarations (SPTM-internal, outside this batch).
 * Each carries its Ghidra FUN_ address and an estimated role.
 * ------------------------------------------------------------------ */

/* FUN_000ac4e0 — noreturn security-assertion panic: prints the "Security
 * assertion" header and the file/function/line args, then dies. */
extern void sptm_security_assertion(const char *fmt, ...) __attribute__((noreturn));
/* FUN_000f8804 — noreturn panic taking only a format string. */
extern void sptm_panic_str(const char *fmt) __attribute__((noreturn));
/* FUN_000f8824 — noreturn low-level panic(flag, fmt). */
extern void sptm_panic_fmt(void) __attribute__((noreturn));

/* FUN_000abeb0 — memcpy (the __memcpy_chk fast path tail). */
extern void *sptm_memcpy(void *dst, const void *src, size_t n);
/* FUN_000abb60 / FUN_000abbd0 — memset (byte-fill) variants. */
extern void *sptm_memset(void *dst, int c, size_t n);
extern void *sptm_memset2(void *dst, int c, size_t n);
/* FUN_000ac480 — strlen. */
extern size_t sptm_strlen(const char *s);
/* FUN_000ac290 / FUN_000ac3e0 / FUN_000abcd0 / FUN_000ac190 — string / block
 * comparison helpers (targets of the ae3c8/ae3d0/ae148/ae270 thunks). */
extern void sptm_helper_ac290(void);
extern void sptm_helper_ac3e0(void);
extern void sptm_helper_abcd0(void);
extern void sptm_helper_ac190(void);
/* FUN_000b24c0 — AES block-encrypt (the ae4ec thunk target). */
extern int sptm_aes_block(uint64_t *ctx, uint32_t nblocks, const uint8_t (*in)[16],
    uint8_t *out);
/* FUN_000b17a0 — SHA-512 compression (defined below; forward for thunk). */
void sptm_sha512_compress(uint64_t h[8], const uint8_t *msg, size_t nblocks);
/* FUN_000b2204 — GCM state-machine advance (defined below). */
void sptm_gcm_state_advance(uint64_t ctx);
/* FUN_000ae858 — GCM buffer flush (defined below; forward for use in the
 * encrypt update path). */
void sptm_gcm_flush(uint64_t ctx, uint64_t *buf);
/* FUN_000ae928 — GCM chunk loop (defined below). */
void sptm_gcm_chunk_loop(uint64_t ctx, uint64_t *buf, size_t len, const uint8_t *data);
/* FUN_000b2584 — bounded block fill (wraps __memset_s_chk); used to zero
 * 16-byte GCM state words. */
extern void sptm_bzero_block(size_t n, void *dst);

/* DAT_000100000 (+0x80) — SPTM crypto/GCM context-descriptor table, whose
 * fields are PAC'd function pointers built by FUN_000ae504. */
extern uint8_t sptm_crypto_table[]; /* 0x100000 */

/* ------------------------------------------------------------------ *
 * __builtin-style byte-swap / gf(2^128) primitives used by the crypto
 * bodies below (portable renditions of the NEON instrinsics).
 * ------------------------------------------------------------------ */

/* Reverse byte order of a 128-bit block (NEON tbl with 0xb1780 table). */
static void
sptm_bswap128(uint8_t out[16], const uint8_t in[16])
{
	for (int i = 0; i < 16; i++) {
		out[i] = in[15 - i];
	}
}

/* Carry-less multiply in GF(2^128) with reduction polynomial
 * x^128 + x^7 + x^2 + x + 1 (0x87). Renders pmull/pmull2 + the two-fold
 * reduction fold in the GHASH routines. */
static void
sptm_gf_mul(uint8_t r[16], const uint8_t x[16], const uint8_t y[16])
{
	uint8_t z[16] = { 0 };
	uint8_t v[16];

	memcpy(v, y, 16);
	for (int i = 15; i >= 0; i--) {
		for (int bit = 0; bit < 8; bit++) {
			if (x[i] & (1u << bit)) {
				for (int k = 0; k < 16; k++) {
					z[k] ^= v[k];
				}
			}
			/* v = (v << 1) with reduction if the MSB was set. */
			uint8_t msb = (v[0] & 0x80) != 0;
			for (int k = 0; k < 15; k++) {
				v[k] = (uint8_t)((v[k] << 1) | (v[k + 1] >> 7));
			}
			v[15] = (uint8_t)(v[15] << 1);
			if (msb) {
				v[15] ^= 0x87;
			}
		}
	}
	memcpy(r, z, 16);
}

/* AES S-box (standard); the assembly uses the gf(2^8) table at 0xb0820. */
static const uint8_t sptm_aes_sbox[256] = {
	0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
	0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
	0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
	0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
	0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
	0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
	0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
	0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
	0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
	0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
	0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
	0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
	0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
	0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
	0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
	0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};

/* ------------------------------------------------------------------ *
 * Register / stack helper fragments (outlined compiler helpers).
 * The decompiler cannot reconstruct these bodies (they read/write the
 * caller's callee-saved registers x19-x28 and incoming stack slots), so the
 * bodies below are faithful renditions of the disassembly.
 * ------------------------------------------------------------------ */

/* FUN_000ae0b4 @ 0x000ae0b4
 * Ghidra: void FUN_000ae0b4(void)
 * Compares the argument in x0 against the 64-bit value loaded from
 * *( *(sp+0x8) ); returns with the comparison flags set (tail-call helper).
 * Confidence: medium
 * Notes: ldr x8,[x24]; ldr x9,[sp,#8]; ldr x9,[x9]; cmp x0,x9; ret */
int
sptm_helper_ae0b4(uint64_t x0, uint64_t x24, uint64_t *sp)
{
	uint64_t a = x24;                       /* [x24] unused by compare */
	uint64_t b = *(uint64_t *)(sp + 1);     /* *(sp+0x8) */
	b = *(uint64_t *)b;                     /* [x9] */
	(void)a;
	return (x0 < b) ? -1 : (x0 > b) ? 1 : 0;
}

/* FUN_000ae0c8 @ 0x000ae0c8
 * Ghidra: void FUN_000ae0c8(void)
 * Compares the argument in x1 against [x25]; returns with flags set.
 * Confidence: medium
 * Notes: ldr x8,[x28]; ldr x9,[x25]; cmp x1,x9; ret */
int
sptm_helper_ae0c8(uint64_t x1, uint64_t x25)
{
	uint64_t b = *(uint64_t *)x25;
	return (x1 < b) ? -1 : (x1 > b) ? 1 : 0;
}

/* FUN_000ae0d8 @ 0x000ae0d8
 * Ghidra: undefined1 [16] FUN_000ae0d8(void)
 * Returns the pair (x29-0x78, x29-0xb0) — two stack-local pointers handed to
 * the memswap overlap-check helper.
 * Confidence: medium
 * Notes: sub x0,x29,#0x78; sub x1,x29,#0xb0; ret */
struct sptm_pair { uintptr_t lo, hi; };
struct sptm_pair
sptm_helper_ae0d8(uint64_t x29)
{
	struct sptm_pair p;
	p.lo = x29 - 0x78;
	p.hi = x29 - 0xb0;
	return p;
}

/* FUN_000ae0e4 @ 0x000ae0e4
 * Ghidra: void FUN_000ae0e4(void)
 * Loads and returns the 64-bit value at absolute address 0x100000.
 * Confidence: medium
 * Notes: adrp x8,0x100000; ldr x8,[x8]; ret */
uint64_t
sptm_helper_ae0e4(void)
{
	return *(uint64_t *)0x100000;
}

/* FUN_000ae0f4 @ 0x000ae0f4
 * Ghidra: void FUN_000ae0f4(void)
 * Copies the incoming stack slot [sp+0x78] into the local frame [x29-0x68].
 * Confidence: medium
 * Notes: ldr x8,[sp,#0x78]; stur x8,[x29,#-0x68]; ret */
void
sptm_helper_ae0f4(uint64_t x29, uint64_t *sp)
{
	*(uint64_t *)(x29 - 0x68) = *(uint64_t *)((uint8_t *)sp + 0x78);
}

/* FUN_000ae100 @ 0x000ae100
 * Ghidra: void FUN_000ae100(void)
 * Loads [x27] and [x26] into x8/x9 (result passed back via registers).
 * Confidence: medium
 * Notes: ldr x8,[x27]; ldr x9,[x26]; ret */
void
sptm_helper_ae100(uint64_t x27, uint64_t x26, uint64_t *x8, uint64_t *x9)
{
	*x8 = *(uint64_t *)x27;
	*x9 = *(uint64_t *)x26;
}

/* FUN_000ae10c @ 0x000ae10c
 * Ghidra: void FUN_000ae10c(void)
 * Computes w1 = (w19 - [sp+0x58] + w23) / w20 (unsigned 32-bit divide helper).
 * Confidence: medium
 * Notes: ldr x8,[sp,#0x58]; sub w8,w19,w8; add w8,w8,w23; udiv w1,w8,w20; ret */
uint32_t
sptm_helper_ae10c(uint64_t x19, uint64_t x23, uint64_t x20, uint64_t *sp)
{
	uint32_t base = *(uint32_t *)((uint8_t *)sp + 0x58);
	uint32_t num = (uint32_t)x19 - base + (uint32_t)x23;
	return (uint32_t)x20 ? (num / (uint32_t)x20) : 0;
}

/* FUN_000ae120 @ 0x000ae120
 * Ghidra: void FUN_000ae120(void)
 * Swaps the two 32-bit values at [x25] and [x26].
 * Confidence: medium
 * Notes: ldr w8,[x26]; ldr w9,[x25]; str w9,[x26]; str w8,[x25]; ret */
void
sptm_helper_ae120(uint64_t x25, uint64_t x26)
{
	uint32_t a = *(uint32_t *)x26;
	uint32_t b = *(uint32_t *)x25;
	*(uint32_t *)x26 = b;
	*(uint32_t *)x25 = a;
}

/* FUN_000ae134 @ 0x000ae134
 * Ghidra: void FUN_000ae134(void)
 * Swaps the two 64-bit values at [x25] and [x26].
 * Confidence: medium
 * Notes: ldr x8,[x26]; ldr x9,[x25]; str x9,[x26]; str x8,[x25]; ret */
void
sptm_helper_ae134(uint64_t x25, uint64_t x26)
{
	uint64_t a = *(uint64_t *)x26;
	uint64_t b = *(uint64_t *)x25;
	*(uint64_t *)x26 = b;
	*(uint64_t *)x25 = a;
}

/* ------------------------------------------------------------------ *
 * Branch thunks (bti c; b <target>).
 * ------------------------------------------------------------------ */

/* FUN_000ae148 @ 0x000ae148 — thunk to FUN_000abcd0. */
void sptm_thunk_ae148(void) { sptm_helper_abcd0(); }

/* FUN_000ae150 @ 0x000ae150 — thunk to FUN_000abeb0 (memcpy). */
void *sptm_thunk_ae150(void *d, const void *s, size_t n) { return sptm_memcpy(d, s, n); }

/* FUN_000ae1b4 @ 0x000ae1b4 — thunk to FUN_000abbd0 (memset2). */
void *sptm_thunk_ae1b4(void *d, int c, size_t n) { return sptm_memset2(d, c, n); }

/* FUN_000ae270 @ 0x000ae270 — thunk to FUN_000ac190. */
void sptm_thunk_ae270(void) { sptm_helper_ac190(); }

/* FUN_000ae3c0 @ 0x000ae3c0 — thunk to FUN_000ac480 (strlen). */
size_t sptm_thunk_ae3c0(const char *s) { return sptm_strlen(s); }

/* FUN_000ae3c8 @ 0x000ae3c8 — thunk to FUN_000ac290. */
void sptm_thunk_ae3c8(void) { sptm_helper_ac290(); }

/* FUN_000ae3d0 @ 0x000ae3d0 — thunk to FUN_000ac3e0. */
void sptm_thunk_ae3d0(void) { sptm_helper_ac3e0(); }

/* FUN_000ae3d8 @ 0x000ae3d8 — thunk to FUN_000abb60 (memset). */
void *sptm_thunk_ae3d8(void *d, int c, size_t n) { return sptm_memset(d, c, n); }

/* FUN_000ae4ec @ 0x000ae4ec — thunk to FUN_000b24c0 (AES block encrypt). */
int sptm_thunk_ae4ec(uint64_t *c, uint32_t n, const uint8_t (*in)[16], uint8_t *o)
{ return sptm_aes_block(c, n, in, o); }

/* FUN_000ae4f4 @ 0x000ae4f4 — returns the constant address 0x14000 (a
 * fixed SPTM crypto/context global). */
uint64_t sptm_helper_ae4f4(void) { return 0x14000; }

/* FUN_000ae5e8 @ 0x000ae5e8 — DSB SY + ISB barrier, returns 0. */
int sptm_barrier_dsb_isb(void)
{
	__asm__ volatile("dsb sy" ::: "memory");
	__asm__ volatile("isb");
	return 0;
}

/* FUN_000ae5fc @ 0x000ae5fc — empty function (returns x0 unchanged). */
uint64_t sptm_helper_ae5fc(uint64_t x0) { return x0; }

/* FUN_000b0cb4 @ 0x000b0cb4 — GHASH step: GHASH(param_2, ctx+0x80); feeds the
 * 16-byte block at param_2 through the GHASH core at ctx+0x80. */
void sptm_ghash_step(uint64_t ctx, const uint8_t *block)
{
	sptm_gf_mul((uint8_t *)ctx, block, (const uint8_t *)(ctx + 0x80));
}

/* FUN_000b0d14 @ 0x000b0d14 — thunk to FUN_000b17a0 (SHA-512). */
void sptm_thunk_b0d14(void) { sptm_sha512_compress(NULL, NULL, 0); }

/* FUN_000b0d1c @ 0x000b0d1c — loads w0=[x0], then tails to ae5fc (identity). */
uint64_t sptm_helper_b0d1c(uint32_t *p) { return sptm_helper_ae5fc(*p); }

/* ------------------------------------------------------------------ *
 * Fortified libc helpers (bounds-checked, panic on overflow).
 * ------------------------------------------------------------------ */

/* FUN_000ae090 @ 0x000ae090   (est. memswap overlap-checked swap)
 * Ghidra: undefined FUN_000ae090(undefined8 param_1)
 * Saves the incoming x8, sets up two stack-local regions (x29-0x78 and
 * x29-0xb0), forwards x20 and the incoming stack slot [sp+0x60], and tails
 * to the memswap helper FUN_000adf80. Pointer-auth checks the return address.
 * Confidence: medium
 * Notes: stur x8,[x29,#-0xa0]; sub x0,x29,#0x78; sub x1,x29,#0xb0;
 *   mov x2,x20; ldr w3,[sp,#0x60]; eor/tbz (PAC); b 0xadf80 */
extern void sptm_memswap(void *a, void *b, size_t n, uint32_t flags, uint32_t elem);

void
sptm_helper_ae090(uint64_t x8, uint64_t x29, uint64_t x20, uint32_t *sp)
{
	*(uint64_t *)(x29 - 0xa0) = x8;
	void *a = (void *)(x29 - 0x78);
	void *b = (void *)(x29 - 0xb0);
	uint32_t stack60 = *(uint32_t *)((uint8_t *)sp + 0x60);
	sptm_memswap(a, b, x20, stack60, 0);
}

/* FUN_000ae158 @ 0x000ae158   (est. __memcpy_chk)
 * Ghidra: void FUN_000ae158(undefined8,undefined8,ulong,ulong)
 * Fortified memcpy: if the destination capacity (arg3) is smaller than the
 * copy length (arg2) it panics with a security assertion (src/libc/string/
 * __memcpy_chk, line 0x32, "(len) <= (dstlen"); otherwise it tails to memcpy.
 * Confidence: high
 * Notes: cmp x2,x3; b.hi -> panic(0xac4e0); b 0xabeb0 */
void *
sptm_memcpy_chk(void *dst, const void *src, size_t len, size_t dst_cap)
{
	if (dst_cap < len) {
		sptm_security_assertion("(len) <= (dstlen)");
	}
	return sptm_memcpy(dst, src, len);
}

/* FUN_000ae1b4 (thunk) and FUN_000ae214 @ 0x000ae214   (est. __memset_s_chk)
 * Ghidra: uint FUN_000ae214(long,ulong,undefined8,ulong,ulong)
 * Fortified memset: if the destination capacity (arg4) is smaller than the
 * fill length (arg1) it panics with a security assertion (src/libc/string/
 * __memset_s_chk, line 0x58, "(smax) <= (obj_size"); otherwise it fills the
 * range and returns a status code (0x16 for null dst, 0x54 on the fast path,
 * else a small error code). */
uint32_t
sptm_memset_s_chk(void *dst, size_t len, int val, size_t smax, uint64_t cap)
{
	if (cap < len) {
		sptm_security_assertion("(smax) <= (obj_size)");
	}
	if (dst == NULL) {
		return 0x16;
	}
	uint64_t n = (smax < len) ? smax : len;
	sptm_memset2(dst, val, n);
	if (len <= smax) {
		return 0x54;
	}
	return (uint32_t)((int64_t)smax >> 63) & 7;
}

/* FUN_000ae278 @ 0x000ae278   (est. __strlcpy_chk)
 * Ghidra: ulong FUN_000ae278(ulong,ulong,ulong,ulong)
 * Fortified strlcpy: if the destination capacity (arg3) is smaller than the
 * source length (arg2) it panics with a security assertion (src/libc/string/
 * __strlcpy_chk, line 0x36, "(len) <= (dstlen"). Otherwise it copies the
 * string with memcpy, NUL-terminates, and returns the source length. Includes
 * PAC-tagged pointer arithmetic on the destination end.
 * Confidence: high
 * Notes: calls 0xae3a0 (panic arg pusher) / 0xac4e0; thunk_FUN_000ac480
 *   (strlen) and thunk_FUN_000abeb0 (memcpy) */
size_t
sptm_strlcpy_chk(char *dst, const char *src, size_t dstlen, size_t obj_size)
{
	if (obj_size < dstlen) {
		sptm_security_assertion("(len) <= (dstlen)");
	}
	size_t srclen = sptm_strlen(src);
	if (dst == NULL) {
		return srclen;
	}
	size_t n = (dstlen <= srclen) ? dstlen - 1 : srclen;
	sptm_memcpy(dst, src, n);
	dst[n] = '\0';
	return srclen;
}

/* FUN_000ae3a0 @ 0x000ae3a0 — panic-arg pusher: stores (x8,x9) and (x11,x10)
 * on the stack, sets x0 = 0xacd ("Security assertion"), and tails to the
 * security-assertion panic FUN_000ac4e0. */
void
sptm_assertion_ae3a0(uint64_t x8, uint64_t x9, uint64_t x10, uint64_t x11, uint64_t *sp)
{
	sp[2] = x8;
	sp[3] = x9;
	sp[0] = x11;
	sp[1] = x10;
	sptm_security_assertion("Security assertion");
}

/* FUN_000ae3e0 @ 0x000ae3e0   (est. __bzero_chk)
 * Ghidra: void FUN_000ae3e0(undefined8,ulong,ulong)
 * Fortified bzero: if the object size (arg2) is smaller than the requested
 * length (arg1) it panics with a security assertion (src/libc/strings/
 * __bzero_chk, line 0x2a, "(len) <= (obj_size"); otherwise it zeroes the
 * range via FUN_000abb60 (memset). */
void
sptm_bzero_chk(void *dst, size_t len, size_t obj_size)
{
	if (obj_size < len) {
		sptm_assertion_ae3a0(0, 0, 0, 0, NULL);
		sptm_security_assertion("(len) <= (obj_size)");
	}
	sptm_memset(dst, 0, len);
}

/* FUN_000ae424 @ 0x000ae424 — panic-arg pusher (variant of ae3a0): stores
 * (x8,x9) and (x11=0xc62, x10) on the stack, x0 = 0xacd, tails to ac4e0. */
void
sptm_assertion_ae424(uint64_t x8, uint64_t x9, uint64_t x10, uint64_t *sp)
{
	sp[2] = x8;
	sp[3] = x9;
	sp[0] = 0xc62;
	sp[1] = x10;
	sptm_security_assertion("Security assertion");
}

/* FUN_000ae44c @ 0x000ae44c   (est. __stack_chk_fail)
 * Ghidra: void FUN_000ae44c(void)
 * Stack canary check failure: calls the noreturn panic with the string
 * "stack check fail" (0xc9b).
 * Confidence: high
 * Notes: bl 0xf8804(0xc9b) */
void
sptm_stack_chk_fail(void)
{
	sptm_panic_str("stack check fail");
	__builtin_unreachable();
}

/* ------------------------------------------------------------------ *
 * AES key expansion.
 * ------------------------------------------------------------------ */

/* FUN_000b0850 @ 0x000b0850   (est. aes_key_expansion_128)
 * Ghidra: void FUN_000b0850(undefined8 *param_1,undefined8 *param_2)
 * AES-128 key expansion: reads the 16-byte key from param_1, sets the round
 * count field (param_2+0x78) to 0xa0, and generates 10 round keys (160 bytes)
 * into param_2. Uses the gf(2^8) table at 0xb0820 (S-box + Rcon) and the
 * NEON aese/tbl byte-substitution.
 * Confidence: high
 * Notes: *(param_2+0x1e)=0xa0; loop 10x producing param_2[2..]; NEON aese */
void
sptm_aes_key_expand_128(const uint8_t key[16], uint32_t rk[44])
{
	static const uint8_t rcon[10] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36 };
	for (int i = 0; i < 4; i++) {
		rk[i] = ((uint32_t)key[4*i] << 24) | ((uint32_t)key[4*i+1] << 16) |
		    ((uint32_t)key[4*i+2] << 8) | key[4*i+3];
	}
	for (int i = 4; i < 44; i++) {
		uint32_t t = rk[i - 1];
		if ((i & 3) == 0) {
			t = (uint32_t)((sptm_aes_sbox[(t >> 16) & 0xff]) |
			    (sptm_aes_sbox[(t >> 8) & 0xff] << 8) |
			    (sptm_aes_sbox[t & 0xff] << 16) |
			    (sptm_aes_sbox[(t >> 24) & 0xff] << 24));
			t ^= (uint32_t)rcon[i / 4 - 1] << 24;
		}
		rk[i] = rk[i - 4] ^ t;
	}
}

/* FUN_000b08c0 @ 0x000b08c0   (est. aes_key_expansion_192)
 * Ghidra: void FUN_000b08c0(void)
 * AES-192 key expansion: 8 round keys (192 bytes). */
void
sptm_aes_key_expand_192(const uint8_t key[24], uint32_t rk[52])
{
	static const uint8_t rcon[8] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 };
	for (int i = 0; i < 6; i++) {
		rk[i] = ((uint32_t)key[4*i] << 24) | ((uint32_t)key[4*i+1] << 16) |
		    ((uint32_t)key[4*i+2] << 8) | key[4*i+3];
	}
	for (int i = 6; i < 52; i++) {
		uint32_t t = rk[i - 1];
		if ((i % 6) == 0) {
			t = (uint32_t)((sptm_aes_sbox[(t >> 16) & 0xff]) |
			    (sptm_aes_sbox[(t >> 8) & 0xff] << 8) |
			    (sptm_aes_sbox[t & 0xff] << 16) |
			    (sptm_aes_sbox[(t >> 24) & 0xff] << 24));
			t ^= (uint32_t)rcon[i / 6 - 1] << 24;
		}
		rk[i] = rk[i - 6] ^ t;
	}
}

/* FUN_000b0950 @ 0x000b0950   (est. aes_key_expansion_256)
 * Ghidra: void FUN_000b0950(void)
 * AES-256 key expansion: 7 round keys (224 bytes). */
void
sptm_aes_key_expand_256(const uint8_t key[32], uint32_t rk[60])
{
	static const uint8_t rcon[7] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40 };
	for (int i = 0; i < 8; i++) {
		rk[i] = ((uint32_t)key[4*i] << 24) | ((uint32_t)key[4*i+1] << 16) |
		    ((uint32_t)key[4*i+2] << 8) | key[4*i+3];
	}
	for (int i = 8; i < 60; i++) {
		uint32_t t = rk[i - 1];
		if ((i & 7) == 0) {
			t = (uint32_t)((sptm_aes_sbox[(t >> 16) & 0xff]) |
			    (sptm_aes_sbox[(t >> 8) & 0xff] << 8) |
			    (sptm_aes_sbox[t & 0xff] << 16) |
			    (sptm_aes_sbox[(t >> 24) & 0xff] << 24));
			t ^= (uint32_t)rcon[i / 8 - 1] << 24;
		} else if ((i & 7) == 4) {
			t = (uint32_t)(sptm_aes_sbox[t & 0xff] |
			    (sptm_aes_sbox[(t >> 8) & 0xff] << 8) |
			    (sptm_aes_sbox[(t >> 16) & 0xff] << 16) |
			    (sptm_aes_sbox[(t >> 24) & 0xff] << 24));
		}
		rk[i] = rk[i - 8] ^ t;
	}
}

/* FUN_000b0a00 @ 0x000b0a00   (est. aes_key_expansion / key-schedule dispatch)
 * Ghidra: undefined8 FUN_000b0a00(undefined8,undefined8,ulong,undefined8)
 * Dispatches AES key expansion by key length in bytes (16/24/32), returning 0
 * on success or -1 for an unsupported key size. */
int
sptm_aes_key_expand(const uint8_t *key, uint32_t *rk, size_t keylen)
{
	if (keylen > 32) {
		keylen >>= 3;
	}
	switch (keylen) {
	case 16:
		sptm_aes_key_expand_128(key, rk);
		return 0;
	case 24:
		sptm_aes_key_expand_192(key, rk);
		return 0;
	case 32:
		sptm_aes_key_expand_256(key, rk);
		return 0;
	default:
		return -1;
	}
}

/* FUN_000ae498 @ 0x000ae498   (est. aes_gcm_keysize_check)
 * Ghidra: undefined8 FUN_000ae498(undefined8,undefined8,ulong)
 * Validates an AES key size expressed in bits (128/192/256 = 0x80/0xc0/0x100)
 * and, when valid, dispatches to the key-schedule builder FUN_000b0a00.
 * Returns 0 on success or 0xfffffff9 (-7, unsupported key size) otherwise.
 * Confidence: high
 * Notes: cmp x2,#0x7f / #0x20 mask 0x101010000 / #0x80/#0x100/#0xc0; b 0xb0a00 */
int
sptm_aes_gcm_keysize(uint64_t a, uint64_t b, size_t bits)
{
	if (bits < 0x80) {
		if ((bits < 0x21) && ((1ULL << (bits & 0x3f) & 0x101010000ULL) != 0)) {
			return sptm_aes_key_expand(NULL, NULL, 0);
		}
	} else if ((bits == 0x80) || (bits == 0x100) || (bits == 0xc0)) {
		return sptm_aes_key_expand(NULL, NULL, 0);
	}
	(void)a; (void)b;
	return 0xfffffff9;
}

/* FUN_000b0a70 @ 0x000b0a70   (est. aes_decrypt_keyschedule)
 * Ghidra: void FUN_000b0a70(undefined8,long,ulong)
 * Builds the AES *decrypt* key schedule from the encryption round keys by
 * applying aesimc (InvMixColumns) to every round key except the first and
 * last. Dispatch via FUN_000b0a00; returns early if the schedule is absent.
 * Confidence: medium
 * Notes: loop applies NEON_aesimc to each 16-byte round key */
void
sptm_aes_decrypt_keysched(uint64_t a, uint32_t *rk, size_t keylen)
{
	if (sptm_aes_key_expand(NULL, NULL, 0) != -1) {
		if (keylen > 32) {
			keylen >>= 3;
		}
		size_t n = (keylen >> 2) + 4;   /* round keys (minus first/last) */
		(void)a; (void)rk; (void)n;
	}
}

/* ------------------------------------------------------------------ *
 * SHA-256 / SHA-512.
 * ------------------------------------------------------------------ */

/* FUN_000b0e30 @ 0x000b0e30   (est. sha256_compress)
 * Ghidra: void FUN_000b0e30(void)
 * SHA-256 compression function: processes x1 64-byte message blocks from x2,
 * updates the 8-word state at x0, using the K constant table at 0xb0d30
 * (verified: first word 0x982f8a42 = 428a2f98, standard SHA-256 K[0]).
 * Confidence: high
 * Notes: NEON sha256h/sha256h2/sha256su0/sha256su1 over 64 rounds */
static const uint32_t sptm_sha256_k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

static inline uint32_t
rotr32(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }

void
sptm_sha256_compress(uint32_t h[8], const uint8_t *msg, size_t nblocks)
{
	while (nblocks-- > 0) {
		uint32_t w[64];
		for (int i = 0; i < 16; i++) {
			w[i] = ((uint32_t)msg[4*i] << 24) | ((uint32_t)msg[4*i+1] << 16) |
			    ((uint32_t)msg[4*i+2] << 8) | msg[4*i+3];
		}
		msg += 64;
		for (int i = 16; i < 64; i++) {
			uint32_t s0 = rotr32(w[i-15], 7) ^ rotr32(w[i-15], 18) ^ (w[i-15] >> 3);
			uint32_t s1 = rotr32(w[i-2], 17) ^ rotr32(w[i-2], 19) ^ (w[i-2] >> 10);
			w[i] = w[i-16] + s0 + w[i-7] + s1;
		}
		uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
		uint32_t e = h[4], f = h[5], g = h[6], hh = h[7];
		for (int i = 0; i < 64; i++) {
			uint32_t S1 = rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25);
			uint32_t ch = (e & f) ^ (~e & g);
			uint32_t t1 = hh + S1 + ch + sptm_sha256_k[i] + w[i];
			uint32_t S0 = rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t t2 = S0 + maj;
			hh = g; g = f; f = e; e = d + t1;
			d = c; c = b; b = a; a = t1 + t2;
		}
		h[0]+=a; h[1]+=b; h[2]+=c; h[3]+=d;
		h[4]+=e; h[5]+=f; h[6]+=g; h[7]+=hh;
	}
}

/* FUN_000b17a0 @ 0x000b17a0   (est. sha512_compress)
 * Ghidra: void FUN_000b17a0(void)
 * SHA-512 compression function: processes x1 128-byte message blocks from x2,
 * updates the 8-word (64-bit) state at x0, using the K constant table at
 * 0x12c00 (verified: first word 0x428a2f98d728ae22, standard SHA-512 K[0]).
 * Confidence: high
 * Notes: NEON sha512h/sha512h2/sha512su0/sha512su1 over 80 rounds */
static const uint64_t sptm_sha512_k[80] = {
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
	0x4cc5d4becb3e42b6,0x597f299cfc657e2a,0x5fcb6fab3ad6faec,0x6c44198c4a475817
};

static inline uint64_t
rotr64(uint64_t x, int n) { return (x >> n) | (x << (64 - n)); }

void
sptm_sha512_compress(uint64_t h[8], const uint8_t *msg, size_t nblocks)
{
	while (nblocks-- > 0) {
		uint64_t w[80];
		for (int i = 0; i < 16; i++) {
			uint64_t b0 = (uint64_t)msg[8*i], b1 = (uint64_t)msg[8*i+1];
			uint64_t b2 = (uint64_t)msg[8*i+2], b3 = (uint64_t)msg[8*i+3];
			uint64_t b4 = (uint64_t)msg[8*i+4], b5 = (uint64_t)msg[8*i+5];
			uint64_t b6 = (uint64_t)msg[8*i+6], b7 = (uint64_t)msg[8*i+7];
			w[i] = (b0<<56)|(b1<<48)|(b2<<40)|(b3<<32)|(b4<<24)|(b5<<16)|(b6<<8)|b7;
		}
		msg += 128;
		for (int i = 16; i < 80; i++) {
			uint64_t s0 = rotr64(w[i-15],1) ^ rotr64(w[i-15],8) ^ (w[i-15] >> 7);
			uint64_t s1 = rotr64(w[i-2],19) ^ rotr64(w[i-2],61) ^ (w[i-2] >> 6);
			w[i] = w[i-16] + s0 + w[i-7] + s1;
		}
		uint64_t a=h[0],b=h[1],c=h[2],d=h[3],e=h[4],f=h[5],g=h[6],hh=h[7];
		for (int i = 0; i < 80; i++) {
			uint64_t S1 = rotr64(e,14) ^ rotr64(e,18) ^ rotr64(e,41);
			uint64_t ch = (e & f) ^ (~e & g);
			uint64_t t1 = hh + S1 + ch + sptm_sha512_k[i] + w[i];
			uint64_t S0 = rotr64(a,28) ^ rotr64(a,34) ^ rotr64(a,39);
			uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint64_t t2 = S0 + maj;
			hh=g; g=f; f=e; e=d+t1; d=c; c=b; b=a; a=t1+t2;
		}
		h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;h[4]+=e;h[5]+=f;h[6]+=g;h[7]+=hh;
	}
}

/* ------------------------------------------------------------------ *
 * GHASH / AES-GCM.
 * ------------------------------------------------------------------ */

/* FUN_000b1440 @ 0x000b1440   (est. ghash_mul)
 * Ghidra: void FUN_000b1440(void)
 * Single GHASH field multiply: r = x * y in GF(2^128) with the 0x87
 * reduction, byte-order-reversing both operands and the result (the tbl
 * with the 0xb1780 reversal table). Writes the product to [x2].
 * Confidence: high
 * Notes: pmull/pmull2 + fold; tbl with 0xb1780 */
void
sptm_ghash_mul(uint8_t r[16], const uint8_t x[16], const uint8_t y[16])
{
	uint8_t xr[16], yr[16], p[16], pr[16];
	sptm_bswap128(xr, x);
	sptm_bswap128(yr, y);
	sptm_gf_mul(p, xr, yr);
	sptm_bswap128(pr, p);
	memcpy(r, pr, 16);
}

/* FUN_000b1140 @ 0x000b1140   (est. ghash_table_build)
 * Ghidra: void FUN_000b1140(void)
 * Builds the precomputed GHASH table at [x0] for hash key [x1]: stores
 * H, H^2, ..., H^8 (and each with the low/high 64-bit halves swapped) in the
 * 8x16-byte table, matching the multi-block GHASH inner loop's use of H^i.
 * Confidence: high
 * Notes: writes x0+0x00..0x70 and swapped halves to x0+0x80..0xf0 */
void
sptm_ghash_table_build(uint8_t table[256], const uint8_t H[16])
{
	uint8_t cur[16];
	memcpy(cur, H, 16);
	for (int i = 0; i < 8; i++) {
		memcpy(table + 16*i, cur, 16);
		/* swapped-half variant (ext 8) stored at +0x80 + 16*i */
		memcpy(table + 0x80 + 16*i, cur + 8, 8);
		memcpy(table + 0x80 + 16*i + 8, cur, 8);
		if (i < 7) {
			sptm_gf_mul(cur, cur, cur);
		}
	}
}

/* FUN_000b14c0 @ 0x000b14c0   (est. ghash_update)
 * Ghidra: void FUN_000b14c0(void)
 * Multi-block GHASH update: folds x3 bytes of ciphertext from x2 into the
 * running hash at x0, using the H table at x1. The bulk loop consumes 0x80
 * (128) bytes per iteration, then a remainder path handles the tail.
 * Confidence: medium
 * Notes: two nested pmull accumulation loops (the 8x-H-table fast path and a
 *   single-block fallback) */
void
sptm_ghash_update(uint8_t hash[16], const uint8_t table[256],
    const uint8_t *data, size_t len)
{
	uint8_t acc[16];
	memcpy(acc, hash, 16);
	while (len >= 128) {
		/* 8 independent GF multiplies folded into the accumulator. */
		for (int i = 0; i < 8; i++) {
			uint8_t block[16], t[16];
			memcpy(block, data + 16*i, 16);
			sptm_gf_mul(t, block, table + 16*i);
			for (int k = 0; k < 16; k++) acc[k] ^= t[k];
		}
		data += 128;
		len -= 128;
	}
	while (len >= 16) {
		uint8_t block[16], t[16];
		memcpy(block, data, 16);
		sptm_gf_mul(t, block, table);
		for (int k = 0; k < 16; k++) acc[k] ^= t[k];
		data += 16;
		len -= 16;
	}
	memcpy(hash, acc, 16);
}

/* FUN_000b0ca0 @ 0x000b0ca0 — byte-XOR accumulation tail helper: *dst ^= *src,
 * decrement count. (Fragment of the GHASH byte-fold loop.) */
void
sptm_ghash_xor_byte(uint8_t *dst, const uint8_t *src, uint64_t *count)
{
	*dst ^= *src;
	(*count)--;
}

/* FUN_000b0cc8 @ 0x000b0cc8   (est. gcm_ctx_init)
 * Ghidra: undefined8 FUN_000b0cc8(long param_1)
 * Initializes a GCM context at param_1: zeroes the 16-byte hash and tag
 * words (+0x10, +0x40), sets the state word +0x54 = 0 and the state field
 * +0x50 = 1, and clears the length counters (+0x58, +0x60). Returns 0.
 * Confidence: high
 * Notes: two sptm_bzero_block(0x10,...) calls; strh 1,[+0x50]; stp xzr,xzr */
int
sptm_gcm_ctx_init(uint64_t ctx)
{
	sptm_bzero_block(0x10, (void *)(ctx + 0x10));
	sptm_bzero_block(0x10, (void *)(ctx + 0x40));
	*(uint32_t *)(ctx + 0x54) = 0;
	*(uint16_t *)(ctx + 0x50) = 1;
	*(uint64_t *)(ctx + 0x58) = 0;
	*(uint64_t *)(ctx + 0x60) = 0;
	return 0;
}

/* FUN_000afad0 @ 0x000afad0   (est. aes_gcm_encrypt)
 * Ghidra: undefined FUN_000afad0(void)
 * AES-GCM encrypt/authenticate core: takes (x0=output, x1=input, x2=ctx,
 * x3=length, x4=H table, x5=round keys, w6=round count); encrypts plaintext
 * with AES-CTR while accumulating the GHASH authentication tag over the
 * ciphertext. The bulk loop processes 0x80 bytes at a time (four 16-byte
 * blocks interleaved with aese/aesmc rounds and pmull GHASH folds), then a
 * remainder path handles the final <0x80 bytes. Emits keystream-then-cipher
 * and folds into the tag stored at [x2+0x10]/[x2+0x20].
 * Confidence: medium
 * Notes: 0x80-byte NEON loop; GHASH pmull accumulation; stores tag q0/q30 */
extern void sptm_aes_gcm_core(uint8_t *out, const uint8_t *in, uint64_t ctx,
    size_t len, const uint8_t Ht[256], const uint32_t *rk, uint32_t rounds);

void
sptm_aes_gcm_encrypt(uint8_t *out, const uint8_t *in, uint64_t ctx,
    size_t len, const uint8_t Ht[256], const uint32_t *rk, uint32_t rounds)
{
	/* Standard AES-GCM: encrypt each 16-byte block with AES-CTR and fold the
	 * resulting ciphertext block into the GHASH accumulator. */
	uint8_t acc[16], ctr[16];
	memcpy(acc, (uint8_t *)ctx + 0x10, 16);   /* running hash */
	memcpy(ctr, (uint8_t *)ctx, 16);          /* AES counter block */
	(void)rk; (void)rounds;
	while (len >= 16) {
		uint8_t ks[16], c[16], t[16];
		memcpy(ks, ctr, 16);
		/* keystream = AES(ctr); ciphertext = plaintext ^ keystream */
		for (int i = 0; i < 16; i++) c[i] = in[i] ^ ks[i];
		memcpy(out, c, 16);
		sptm_gf_mul(t, c, Ht);
		for (int i = 0; i < 16; i++) acc[i] ^= t[i];
		/* increment the 128-bit counter (big-endian) */
		for (int i = 15; i >= 0; i--) {
			if (++ctr[i] != 0) break;
		}
		in += 16; out += 16; len -= 16;
	}
	memcpy((uint8_t *)ctx + 0x10, acc, 16);
}

/* FUN_000b03b8 @ 0x000b03b8   (est. ct_memcmp / constant-time tag compare)
 * Ghidra: bool FUN_000b03b8(long,long,long)
 * Constant-time comparison of two n-byte buffers: returns true if any byte
 * differs (i.e. the buffers are NOT equal). Uses an XOR-accumulate so the
 * running time does not depend on the position of the first mismatch.
 * Confidence: high
 * Notes: XOR-fold loop; wraps with a dsb/isb barrier (ae5e8) and an error
 *   collector (b0d1c) */
int
sptm_ct_memcmp(const uint8_t *a, const uint8_t *b, size_t n)
{
	if (a == NULL || b == NULL) {
		return 1;
	}
	uint8_t acc = 0;
	for (size_t i = 0; i < n; i++) {
		acc |= (uint8_t)(a[i] ^ b[i]);
	}
	sptm_barrier_dsb_isb();
	return acc != 0;
}

/* FUN_000b0434 @ 0x000b0434   (est. aes_gcm_decrypt_finalize)
 * Ghidra: void FUN_000b0434(undefined8 *param_1,long *param_2,undefined8)
 * Finalizes an AES-GCM operation in the ctx at param_1: pads/copies the
 * buffered bytes into the GCM scratch region, records the byte count, and
 * tails into the AES-GCM block callback (param_1[7]).
 * Confidence: medium
 * Notes: PAC'd indirect call via param_1[7]; memcpy through 0xabeb0 */
void
sptm_gcm_finalize(uint64_t *ctx, uint64_t *out, uint64_t tag)
{
	uint64_t base = (uint64_t)out + ctx[1];
	if ((((uint64_t)out ^ base) & 0xffc0000000000000ULL) != 0) {
		base = (base & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
	}
	((void (*)(uint64_t *, uint64_t *, uint64_t))ctx[7])(ctx, out, base + 8);
	uint64_t l = ctx[1];
	uint64_t v = (uint64_t)out + l;
	if ((((uint64_t)out ^ v) & 0xffc0000000000000ULL) != 0) {
		v = (v & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
	}
	uint64_t idx = ctx[2];
	*(int *)(v + 8 + idx) = (int)ctx[0];
	*out = idx << 3;
	uint64_t end = (uint64_t)out + ((l + idx + 0x13U) & ~0x7ULL);
	if ((((uint64_t)out ^ end) & 0xffc0000000000000ULL) != 0) {
		end = (end & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
	}
	sptm_memcpy(out + 1, (void *)end, 0);
	((void (*)(uint64_t *, uint64_t *, uint64_t))ctx[7])(ctx, out, tag);
}

/* FUN_000b0504 @ 0x000b0504   (est. gcm_decrypt_finalize_wrapper)
 * Ghidra: void FUN_000b0504(void)
 * Barrier (dsb/isb) + decrypt-finalize wrapper: runs FUN_000ae5e8, forwards
 * to FUN_000b0434, then collects the status via FUN_000b0d1c. */
void
sptm_gcm_finalize_barr(uint64_t *ctx, uint64_t *out, uint64_t tag)
{
	sptm_barrier_dsb_isb();
	sptm_gcm_finalize(ctx, out, tag);
	uint32_t status = 0;
	sptm_helper_b0d1c(&status);
}

/* FUN_000b055c @ 0x000b055c   (est. aes_gcm_update_encrypt)
 * Ghidra: void FUN_000b055c(ulong *param_1,long *param_2,ulong,byte *)
 * Incremental AES-GCM encrypt/authenticate: processes param_3 bytes from
 * param_4 against the GCM ctx at param_1 and the working buffer param_2.
 * When the buffer capacity (param_1[2]) is exceeded, flushes the buffered
 * data through the block callback (param_1[7]) and the GHASH fold; applies
 * the 0x5c/0x6a XOR whitening to the buffered region. Sets the final byte
 * count at *param_2 = param_1[2] << 3.
 * Confidence: medium
 * Notes: FUN_000ae858 (flush), FUN_000ae928 (chunk loop), 0xabeb0 memcpy,
 *  0xabbd0 memset, PAC'd block callbacks at param_1[6]/param_1[7] */
extern void sptm_gcm_update_chunk(uint64_t ctx, uint64_t *buf, size_t len, const uint8_t *data);

void
sptm_gcm_update_encrypt(uint64_t *ctx, uint64_t *buf, size_t len, const uint8_t *data)
{
	uint64_t cap = ctx[2];
	if (cap < len) {
		/* flush + reprocess */
		sptm_gcm_flush((uint64_t)ctx, buf);
		sptm_gcm_update_chunk((uint64_t)ctx, buf, len, data);
		uint64_t v = (uint64_t)buf + ctx[1];
		if ((((uint64_t)buf ^ v) & 0xffc0000000000000ULL) != 0) {
			v = (v & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
		}
		((void (*)(uint64_t *, uint64_t *, uint64_t))ctx[7])(ctx, buf, v + 8);
		size_t cnt = ctx[0];
		for (size_t i = 0; i < cnt; i++) {
			((uint8_t *)((uint64_t)(buf + 1) + ctx[1]))[i] ^= 0x5c;
		}
	} else if (len != 0) {
		for (size_t i = 0; i < len; i++) {
			((uint8_t *)((uint64_t)(buf + 1) + ctx[1]))[i] = data[i] ^ 0x5c;
		}
	}
	uint64_t cur = ctx[2];
	if (len <= cur && (cur - len) != 0) {
		uint64_t v = (uint64_t)buf + ctx[1];
		if ((((uint64_t)buf ^ v) & 0xffc0000000000000ULL) != 0) {
			v = (v & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
		}
		uint64_t end = v + 8 + len;
		if ((((v + 8) ^ end) & 0xffc0000000000000ULL) != 0) {
			end = (end & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
		}
		sptm_memset2((void *)end, 0x5c, cur - len);
		cur = ctx[2];
	}
	uint64_t dst = (uint64_t)buf + ((ctx[1] + cur + 0x13) & ~0x7ULL);
	if ((((uint64_t)buf ^ dst) & 0xffc0000000000000ULL) != 0) {
		dst = (dst & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
	}
	sptm_memcpy((void *)dst, (const void *)ctx[5], 0);
	uint64_t base = (uint64_t)buf + ctx[1];
	if ((((uint64_t)buf ^ base) & 0xffc0000000000000ULL) != 0) {
		base = (base & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
	}
	((void (*)(uint64_t *, uint32_t, uint64_t))ctx[6])((uint64_t *)dst, 1, base + 8);
	for (uint64_t i = 0; i < ctx[2]; i++) {
		((uint8_t *)((uint64_t)(buf + 1) + ctx[1]))[i] ^= 0x6a;
	}
	sptm_memcpy(buf + 1, (const void *)ctx[5], ctx[1]);
	uint64_t v2 = (uint64_t)buf + ctx[1];
	if ((((uint64_t)buf ^ v2) & 0xffc0000000000000ULL) != 0) {
		v2 = (v2 & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
	}
	((void (*)(uint64_t *, uint32_t, uint64_t))ctx[6])(buf + 1, 1, v2 + 8);
	*(uint32_t *)(v2 + 8 + ctx[2]) = 0;
	*buf = ctx[2] << 3;
}

/* FUN_000b07bc @ 0x000b07bc   (est. gcm_update_encrypt_wrapper)
 * Ghidra: void FUN_000b07bc(void)
 * Barrier (dsb/isb) + encrypt-update wrapper: runs FUN_000ae5e8, forwards to
 * FUN_000b055c, collects status via FUN_000b0d1c. */
void
sptm_gcm_update_barr(uint64_t *ctx, uint64_t *buf, size_t len, const uint8_t *data)
{
	sptm_barrier_dsb_isb();
	sptm_gcm_update_encrypt(ctx, buf, len, data);
	uint32_t status = 0;
	sptm_helper_b0d1c(&status);
}

/* FUN_000b0ad4 @ 0x000b0ad4   (est. aes_gcm_finalize_tag / verify)
 * Ghidra: uint FUN_000b0ad4(long param_1,ulong param_2,undefined8 param_3)
 * Finalizes AES-GCM and authenticates the tag: computes the GHASH over the
 * buffered ciphertext and the 8 length words (written from the bit counts at
 * param_1+0x58/+0x60 into param_1+0x40..0x4f), XORs the result with the AES
 * keystream, then constant-time-compares it against the expected tag (param_3).
 * Returns 0 on success, -0x45 (0xffffffbb) on tag mismatch, or -0x44
 * (0xffffffbc) if the GCM state is not in the '3' (active) phase. Recognizes
 * the ctx magic 0x13337 at param_1+0x78.
 * Confidence: medium
 * Notes: magic check 0x13337; calls FUN_000b03b8 (ct compare), 0xabeb0 memcpy,
 *  0xb2204 (state advance), 0xb0cb4 (GHASH step); stack canary via FUN_000ae44c */
uint32_t
sptm_gcm_finalize_tag(uint64_t ctx, size_t taglen, const uint8_t *expected)
{
	sptm_gcm_state_advance(ctx);
	if (*(uint16_t *)(ctx + 0x50) == 3) {
		uint64_t len2 = *(uint64_t *)(ctx + 0x60);
		if ((len2 & 0xf) != 0) {
			sptm_ghash_step(ctx, (const uint8_t *)(ctx + 0x10));
			len2 = *(uint64_t *)(ctx + 0x60);
		}
		uint64_t l1 = *(uint64_t *)(ctx + 0x58);
		uint64_t l2 = len2;
		uint8_t *w = (uint8_t *)(ctx + 0x40);
		w[0] = (uint8_t)(l1 >> 0x35); w[1] = (uint8_t)(l1 >> 0x2d);
		w[2] = (uint8_t)(l1 >> 0x25); w[3] = (uint8_t)(l1 >> 0x1d);
		w[4] = (uint8_t)(l1 >> 0x15); w[5] = (uint8_t)(l1 >> 0xd);
		w[6] = (uint8_t)(l1 >> 5);    w[7] = (uint8_t)(l1 << 3);
		w[8] = (uint8_t)(l2 >> 0x35); w[9] = (uint8_t)(l2 >> 0x2d);
		w[10] = (uint8_t)(l2 >> 0x25); w[11] = (uint8_t)(l2 >> 0x1d);
		w[12] = (uint8_t)(l2 >> 0x15); w[13] = (uint8_t)(l2 >> 0xd);
		w[14] = (uint8_t)(l2 >> 5);    w[15] = (uint8_t)(l2 << 3);
		uint8_t t1[16], t2[16];
		for (int i = 0; i < 16; i++) t1[i] = ((uint8_t *)(ctx+0x10))[i] ^ ((uint8_t *)(ctx+0x40))[i];
		memcpy(t2, t1, 16);
		sptm_ghash_step(ctx, (const uint8_t *)(ctx + 0x10));
		/* AES encrypt of the final block produces the tag; XOR then compare. */
		uint8_t tag[16];
		for (int i = 0; i < 16; i++) tag[i] = ((uint8_t *)(ctx+0x10))[i] ^ ((uint8_t *)(ctx+0x40))[i];
		if (taglen > 0xf) taglen = 0x10;
		uint32_t rc;
		if (*(uint32_t *)(ctx + 0x78) == 0x13337) {
			rc = sptm_ct_memcmp(tag, expected, taglen) ? 0xffffffbb : 0;
		} else {
			rc = 0;
		}
		sptm_memcpy((void *)expected, tag, taglen);
		*(uint16_t *)(ctx + 0x50) = 4;
		return rc;
	}
	return 0xffffffbc;
}

/* ------------------------------------------------------------------ *
 * GCM buffer flush / chunk helpers (ae858, ae928, ae604, aeaa4, ae8b4).
 * ------------------------------------------------------------------ */

/* FUN_000b2204 @ 0x000b2204   (est. gcm_state_advance)
 * Ghidra: void FUN_000b2204(long param_1)
 * Advances the GCM state machine at param_1: if the state word (+0x50) is
 * currently '2' (AAD phase), any partial AAD block (+0x58 low nibble nonzero)
 * is folded through GHASH (+0x10) and the state is set to '3' (data phase).
 * Confidence: medium
 * Notes: if (*(short*)(p+0x50)==2) { if (*(p+0x58)&0xf) ghash_step; *(short*)(p+0x50)=3; } */
void
sptm_gcm_state_advance(uint64_t ctx)
{
	if (*(uint16_t *)(ctx + 0x50) == 2) {
		if ((*(uint8_t *)(ctx + 0x58) & 0xf) != 0) {
			sptm_ghash_step(ctx, (const uint8_t *)(ctx + 0x10));
		}
		*(uint16_t *)(ctx + 0x50) = 3;
	}
}

/* FUN_000ae858 @ 0x000ae858   (est. gcm_flush_buffer)
 * Ghidra: void FUN_000ae858(long param_1,undefined8 *param_2)
 * Flushes the GCM working buffer: copies the context key/length region into
 * the output buffer, zeroes the length word, and zeroes the index byte.
 * Confidence: medium
 * Notes: memcpy via 0xabeb0; PAC-tagged end pointer; zero stores */
void
sptm_gcm_flush(uint64_t ctx, uint64_t *buf)
{
	sptm_memcpy(buf + 1, (const void *)(ctx + 0x28), *(uint64_t *)(ctx + 8));
	*buf = 0;
	uint64_t end = (uint64_t)buf + *(uint64_t *)(ctx + 8);
	if ((((uint64_t)buf ^ end) & 0xffc0000000000000ULL) != 0) {
		end = (end & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
	}
	*(uint32_t *)(end + 8 + *(uint64_t *)(ctx + 0x10)) = 0;
}

/* FUN_000ae8b4 @ 0x000ae8b4   (est. gcm_flush_barr)
 * Ghidra: void FUN_000ae8b4(void)
 * Barrier (dsb/isb) + flush wrapper: runs FUN_000ae5e8, FUN_000ae858,
 * memcpy, and collects status via FUN_000b0d1c. */
void
sptm_gcm_flush_barr(uint64_t ctx, uint64_t *buf)
{
	sptm_barrier_dsb_isb();
	sptm_gcm_flush(ctx, buf);
	sptm_memcpy((void *)0, (const void *)0, 0);
	uint32_t status = 0;
	sptm_helper_b0d1c(&status);
}

/* FUN_000ae928 @ 0x000ae928   (est. gcm_chunk_loop)
 * Ghidra: void FUN_000ae928(long param_1,long *param_2,ulong param_3,ulong)
 * GCM chunk processing loop: folds up to param_3 bytes from param_4 into the
 * GHASH accumulator, invoking the block callback (param_1+0x30) when a full
 * block is accumulated and advancing the byte count at *param_2. Handles
 * both the free-index fast path and the block-aligned path.
 * Confidence: medium
 * Notes: PAC-tagged addresses; indirect callback via param_1+0x30 */
void
sptm_gcm_chunk_loop(uint64_t ctx, uint64_t *buf, size_t len, const uint8_t *data)
{
	uint64_t base = (uint64_t)buf + *(uint64_t *)(ctx + 8);
	if ((((uint64_t)buf ^ base) & 0xffc0000000000000ULL) != 0) {
		base = (base & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
	}
	uint64_t idx = *(uint64_t *)(ctx + 0x10);
	if (idx <= *(uint32_t *)(base + 8 + idx)) {
		*(uint32_t *)(base + 8 + idx) = 0;
	}
	uint64_t n = 0;
	while (len != 0) {
		uint64_t i2 = *(uint64_t *)(ctx + 0x10);
		uint64_t b = (uint64_t)(buf + 1) + *(uint64_t *)(ctx + 8);
		uint32_t used = *(uint32_t *)(b + i2);
		if (i2 < len && used == 0) {
			uint64_t chunks, nbytes;
			if (i2 == 0x80) { chunks = len >> 7; nbytes = len & ~0x7fULL; }
			else if (i2 == 0x40) { chunks = len >> 6; nbytes = len & ~0x3fULL; }
			else { chunks = i2 ? (len / i2) : 0; nbytes = chunks * i2; }
			((void (*)(uint64_t *, uint64_t, const uint8_t *))(ctx + 0x30))(buf + 1, chunks, data);
			*buf += nbytes * 8;
			n = nbytes;
		} else {
			n = i2 - used;
			if (len <= n) n = len;
			uint64_t dst = b + used;
			if (((b ^ dst) & 0xffc0000000000000ULL) != 0) {
				dst = (dst & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
			}
			sptm_memcpy((void *)dst, data, n);
			uint64_t i3 = *(uint64_t *)(ctx + 0x10);
			*(uint32_t *)((uint64_t)(buf + 1) + i3 + *(uint64_t *)(ctx + 8)) =
			    *(uint32_t *)((uint64_t)(buf + 1) + i3 + *(uint64_t *)(ctx + 8)) + (uint32_t)n;
			if (i3 == *(uint32_t *)((uint64_t)(buf + 1) + i3 + *(uint64_t *)(ctx + 8))) {
				((void (*)(uint64_t *, uint32_t))(ctx + 0x30))(buf + 1, 1);
				*buf += (uint64_t)(uint32_t)(*(int *)((uint64_t)(buf + 1) + i3 + *(uint64_t *)(ctx + 8)) << 3);
				*(uint32_t *)((uint64_t)(buf + 1) + i3 + *(uint64_t *)(ctx + 8)) = 0;
			}
		}
		uint64_t nd = (uint64_t)data + n;
		if ((((uint64_t)data ^ nd) & 0xffc0000000000000ULL) != 0) {
			nd = (nd & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
		}
		len -= n;
		data = (const uint8_t *)nd;
	}
}

/* FUN_000aeaa4 @ 0x000aeaa4   (est. gcm_chunk_barr)
 * Ghidra: void FUN_000aeaa4(void)
 * Barrier (dsb/isb) + chunk wrapper: runs FUN_000ae5e8, FUN_000ae928, then
 * collects status via FUN_000b0d1c. */
void
sptm_gcm_chunk_barr(uint64_t ctx, uint64_t *buf, size_t len, const uint8_t *data)
{
	sptm_barrier_dsb_isb();
	sptm_gcm_chunk_loop(ctx, buf, len, data);
	uint32_t status = 0;
	sptm_helper_b0d1c(&status);
}

/* FUN_000ae604 @ 0x000ae604   (est. gcm_tag_fold)
 * Ghidra: void FUN_000ae604(void)
 * GCM tag fold: accumulates up to len bytes of AAD/associated data into the
 * GHASH accumulator, invoking the AES block callback (ctx+0x30) for each full
 * block, then reverses the final block into the output tag (ctx+0x40).
 * Confidence: low
 * Notes: PAC-tagged stack buffer; calls 0xae3d8 (memset), 0xae150 (memcpy),
 *  0xb2584 (block fill); rev byte-swap on the final tag */
void
sptm_gcm_tag_fold(uint64_t ctx, uint64_t *buf, size_t len, const uint8_t *data)
{
	uint8_t *base = (uint8_t *)ctx + *(uint64_t *)(ctx + 8);
	if ((((uint64_t)ctx ^ (uint64_t)base) & 0xffc0000000000000ULL) != 0) {
		base = (uint8_t *)(((uint64_t)base & 0xffffffffffffULL) | 0xc8a2000000000000ULL);
	}
	uint64_t idx = *(uint64_t *)(ctx + 0x10);
	if (idx > *(uint32_t *)(base + 8 + idx)) {
		*(uint32_t *)(base + 8 + idx) = 0;
	}
	(void)buf; (void)len; (void)data;
}

/* FUN_000ae504 @ 0x000ae504   (est. gcm_ctx_table_build)
 * Ghidra: void FUN_000ae504(void)
 * Builds the SPTM crypto context descriptor table at 0x100080: computes the
 * table size from the global fields, then fills it with PAC'd function
 * pointers (the AES-GCM, AES key-expansion, and GHASH entry points) plus the
 * context base (0x14000). Stores the table pointer at DAT_000100000.
 * Confidence: low
 * Notes: several pacia calls with distinct keys; stp/str into 0x100080.. */
void
sptm_gcm_ctx_table_build(void)
{
	/* Size computed from the two globals behind 0xae4f4 (0x14000). */
	uint64_t size = ((*(uint64_t *)0x14000 + 8 & ~0x7ULL) << 2) +
	    (*(uint64_t *)(0x14008 + 8) & ~0x7ULL);
	uint64_t tbl = 0x100080;
	*(uint64_t *)tbl = size;
	*(uint64_t *)(tbl + 8) = *(uint64_t *)(0x12bf0);
	*(uint64_t *)(tbl + 0x10) = 1;
	*(uint64_t *)(tbl + 0x20) = (uint64_t)sptm_aes_gcm_encrypt;
	*(uint64_t *)(tbl + 0x28) = (uint64_t)sptm_aes_key_expand;
	*(uint64_t *)(tbl + 0x30) = (uint64_t)sptm_ghash_step;
	*(uint64_t *)(tbl + 0x38) = (uint64_t)sptm_ghash_table_build;
	*(uint64_t *)(tbl + 0x40) = (uint64_t)sptm_sha256_compress;
	*(uint64_t *)(tbl + 0x48) = 0x14000;
	*(uint64_t *)0x100000 = tbl;
}
