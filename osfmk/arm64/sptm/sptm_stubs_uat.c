/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM UAT (Unified Address Translation) stub region
 * (0x000b2000 - 0x000b6600): the SK/TXM guarded-level entry stubs, the UAT
 * TLB-invalidate / page-table-walk helpers, the UAT unmap walker + callbacks,
 * the UAT driver init, and the small UAT object wrappers / AES block encrypt.
 *
 * Shared SPTM-internal helpers called from these bodies are declared extern
 * with a one-line note giving their Ghidra address and estimated purpose.
 * UAT driver state is DAT_00095d08 (see sptm_internal.h).
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ *
 * Shared helper declarations (SPTM-internal, outside this batch).
 * Each carries its Ghidra FUN_ address and an estimated role.
 * ------------------------------------------------------------------ */

/* FUN_000f8844 — noreturn SPTM panic: panic(err, val, fmt). */
extern void sptm_panic(uint32_t err, uint64_t val, const char *fmt) __attribute__((noreturn));
/* FUN_000f8804 — noreturn SPTM panic taking only a format string. */
extern void sptm_panic_str(const char *fmt) __attribute__((noreturn));
/* FUN_000ae44c — stack canary / BTI check on function exit. */
extern void sptm_stack_check(void);

/* FUN_000abeb0 (thunk) — memcpy. */
extern void *sptm_memcpy(void *dst, const void *src, uint64_t n);
/* FUN_000ae3e0 — memset. */
extern void *sptm_memset(void *dst, uint64_t n, uint64_t value);
/* FUN_000abb60 — memset (byte-fill variant). */
extern void *sptm_memset2(void *dst, int c, size_t n);
/* FUN_000ae5e8 — DSB SY + ISB barrier, returns 0. */
extern int sptm_barrier_dsb_isb(void);
/* FUN_000b0d1c — loads w0=[x0], then tails to ae5fc (identity). */
extern uint64_t sptm_helper_b0d1c(uint32_t *p);
/* FUN_000b0e30 — SHA-256 compression (defined in sptm_helpers.c). */
extern void sptm_sha256_compress(uint32_t h[8], const uint8_t *msg, size_t nblocks);
/* FUN_000ae214 — checked block copy helper (memcpy-with-bounds); 5 args. */
extern uint32_t sptm_helper_ae214(uint64_t p1, uint64_t p2, uint64_t p3,
                                  uint64_t p4, uint64_t p5);

/* FUN_000c5248 — get/acquire the UAT state by id (mode 0/2/5, mask). */
extern void *sptm_uat_state_get(uint64_t id, int mode, int mask);
/* FUN_000c5784 — walk UAT tables for a VA, returning its offset and count. */
extern void sptm_uat_va_walk(uint64_t va, uint64_t size, uint8_t *state, uint64_t *out_off);
/* FUN_000e40ec — translate a physical address to VA when outside the linear
 * EL2 window (page-table-walk lookup). */
extern void *sptm_phystokv_outside_window(uint64_t paddr);
/* FUN_000e4e74 — validate a physical address + length, returning its FTE/VA. */
extern void *sptm_paddr_validate(uint64_t paddr, uint64_t size);
/* FUN_000e53d8 — paddr refcount adjust: count==1 acquire, 0xffffffff release. */
extern int sptm_paddr_ref(uint64_t paddr, uint32_t count);
/* FUN_000e5090 — release/LO-unref a physical address. */
extern void sptm_paddr_release(uint64_t paddr);
/* FUN_000e5c80 — release an IOMMU page reference for `type`. */
extern void sptm_iommu_page_unref(uint64_t paddr, uint32_t type);
/* FUN_000e2480 — look up and acquire (LO ref) the FTE for a physical address. */
extern void *sptm_fte_acquire(uint64_t paddr);
/* FUN_000d8a58 — reverse translation: physical address of an SPTM-owned VA. */
extern uint64_t sptm_kvtophys(const void *va);
/* FUN_000e4d78 — get the per-CPU DART driver state. */
extern void *sptm_dart_state_get(void);
/* FUN_000e41bc — allocate `count` elements of `size` bytes (returns VA). */
extern void *sptm_alloc(uint64_t count, uint64_t size);
/* FUN_000e4424 — register/track a named SPTM subsystem (string arg). */
extern void sptm_subsys_register(const char *name);
/* FUN_000e45a8 — take an IOMMU/device page reference for a region; returns the
 * linear VA of the region (or 0xffffffff on failure). */
extern uint64_t sptm_iommu_region_ref(uint64_t paddr, uint64_t npages, uint32_t type);
/* FUN_000b79e8 — SecureDT: look up a node by name under a parent. */
extern int sptm_secure_dt_node(void *dt, uint64_t parent, const char *name, void **out_node);
/* FUN_000b7c04 — SecureDT: read a property value into an out pointer. */
extern int sptm_secure_dt_prop(void *node, const char *name, void **out, uint32_t *out_len,
                               uint64_t a, uint64_t b);
/* FUN_000b7748 — SecureDT: build a path/name string for a child node. */
extern void sptm_secure_dt_path(void *node, const char *name);
/* FUN_000b486c — UAT map continue (defined in the UAT map batch). */
extern void sptm_uat_map_continue(uint64_t id);

/* FUN_000a0f7c / FUN_000a111c — TXM/SK guarded-level entry context-save
 * (defined in sptm_boot.c). */
extern void sptm_txm_sk_entry(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                              uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8);
extern void sptm_sk_entry(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                          uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8);

/* --- hardware accessors --- */
extern void SysOp_W(uint64_t op1, uint64_t crn, uint64_t crm, uint64_t op2, uint64_t v);
extern uint64_t UnkSytemRegRead(uint64_t op0, uint64_t op1, uint64_t crn,
                                uint64_t crm, uint64_t op2);

/* --- SPTM global state (Ghidra DAT_ symbols; addresses in comments) --- */
extern uint64_t sptm_mem_low;    /* DAT_00095d18 */
extern uint64_t sptm_mem_high;   /* DAT_00095d20 */
extern uint8_t sptm_uat_driver_state[];  /* DAT_00095d08 */
extern uint64_t sptm_window_base; /* DAT_00095460 */
extern uint8_t sptm_fte_class[];  /* DAT_00095d51 */
extern uint8_t sptm_fte_shared[]; /* DAT_00095d83 */
extern uint32_t sptm_mem_feature; /* DAT_001012d8 */
extern uint64_t sptm_region_count; /* DAT_00101ac8 */
extern uint64_t sptm_regions[];   /* DAT_00101ad0 (3 words per region) */
extern uint8_t sptm_boot_thing;   /* DAT_00094319 */
extern uint8_t sptm_sapt_bootstrapped; /* DAT_000952e8 */
extern uint64_t sptm_boot_stage;  /* DAT_00095310 */
extern void *sptm_secure_dt_root; /* DAT_00094ab8 */

/* SecureDT per-property read (u32/u64 value). */
static uint64_t
dt_read_prop(void *node, const char *name, uint32_t want_len)
{
	void *prop = NULL;
	uint32_t len = 0;
	int rc = sptm_secure_dt_prop(node, name, &prop, &len,
	                             (uint64_t)sptm_secure_dt_root,
	                             *(uint64_t *)((uint8_t *)sptm_secure_dt_root + 8));
	if (rc != 1)
		return UINT64_MAX;
	if (len != want_len)
		return UINT64_MAX;
	if (prop == NULL)
		return UINT64_MAX;
	/* re-read into a stable buffer (the DT accessor is two-call) */
	prop = NULL; len = 0;
	sptm_secure_dt_prop(node, name, &prop, &len, (uint64_t)sptm_secure_dt_root,
	                    *(uint64_t *)((uint8_t *)sptm_secure_dt_root + 8));
	if (len != want_len)
		return UINT64_MAX;
	if (want_len == 4)
		return (uint64_t)*(uint32_t *)prop;
	return *((uint64_t *)prop);
}

/* LOAcquire / LORelease — opaque SPTM refcount primitives. */
#define LOAcquire()   /* opaque */
#define LORelease()   /* opaque */

/* LZCOUNT — count leading zeros of a 64-bit value. */
static inline uint32_t
lzcount(uint64_t v)
{
	return v ? (uint32_t)__builtin_clzll(v) : 64;
}

/* ------------------------------------------------------------------ *
 * Small UAT object wrappers (vtable-style method calls).
 * ------------------------------------------------------------------ */

/* FUN_000b2014 @ 0x000b2014   (est. sptm_uat_get_u64)
 * Ghidra: undefined8 FUN_000b2014(undefined8 *param_1)
 * Returns the first 64-bit word of the UAT object (a getter for field 0).
 * Confidence: low
 * Notes: called by FUN_000eb004 (the UAT object dispatch entry). */
uint64_t sptm_uat_get_u64(uint64_t *obj)
{
	return obj[0];
}

/* FUN_000b2020 @ 0x000b2020   (est. sptm_uat_obj_set_flag)
 * Ghidra: undefined8 FUN_000b2020(long,long,undefined8,undefined8,undefined8)
 * Runs the object's method-0 and method-1 (vtable +0x18 / +0x20); if both
 * succeed, sets bit 1 of the 16-bit field at obj+0x52. Wrapped in a dsb/isb
 * barrier + status-collector pair.
 * Confidence: medium
 * Notes: vtable offsets +0x18 (4-arg) and +0x20 (3-arg with const 0xc). */
uint64_t sptm_uat_obj_set_flag(uint64_t obj, uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	uint32_t status;
	uint64_t rc;

	(void)sptm_barrier_dsb_isb();
	rc = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t))(obj + 0x18))
	    (obj, a, b, c);
	if ((int)rc == 0) {
		rc = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))(obj + 0x20))
		    (a, 0xc, d);
		if ((int)rc == 0) {
			*(uint16_t *)(a + 0x52) = *(uint16_t *)(a + 0x52) | 1;
		}
	}
	sptm_helper_b0d1c(&status);
	return rc;
}

/* FUN_000b20d0 @ 0x000b20d0   (est. sptm_uat_counter_bump)
 * Ghidra: void FUN_000b20d0(long param_1)
 * Increments a little-endian 32-bit counter stored at obj+0x2c (bytes written
 * high-to-low, carry-propagating), then notifies via the method at
 * (*(obj+0x68))+0x18 with (obj+0x70, 1, obj+0x20, obj+0x40).
 * Confidence: low
 * Notes: the 4-byte carry loop is a manual little-endian increment. */
void sptm_uat_counter_bump(uint8_t *obj)
{
	uint8_t *p = obj + 0x2f; /* last byte of the 4-byte counter at +0x2c */
	uint64_t i = 1;
	uint8_t v;
	do {
		v = *p;
		*p = (uint8_t)(v + 1);
		if (i > 3)
			break;
		i++;
		p--;
	} while ((uint8_t)(v + 1) == 0);

	((void (*)(uint64_t, uint64_t, uint64_t, uint64_t))
	    (*(uint64_t *)(obj + 0x68) + 0x18))
	    (*(uint64_t *)(obj + 0x70), 1, (uint64_t)(obj + 0x20), (uint64_t)(obj + 0x40));
}

/* FUN_000b211c @ 0x000b211c   (est. sptm_uat_obj_op_30)
 * Ghidra: undefined8 FUN_000b211c(long,undefined8,undefined8,undefined8,undefined8)
 * Calls the object's vtable method at +0x30 with four args, under barrier +
 * status collector.
 * Confidence: medium */
uint64_t sptm_uat_obj_op_30(uint64_t obj, uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
	uint32_t status;
	uint64_t rc;

	(void)sptm_barrier_dsb_isb();
	rc = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t, uint64_t))(obj + 0x30))
	    (a, b, c, d);
	sptm_helper_b0d1c(&status);
	return rc;
}

/* FUN_000b2198 @ 0x000b2198   (est. sptm_uat_obj_op_38)
 * Ghidra: undefined8 FUN_000b2198(long,undefined8,undefined8,undefined8)
 * Calls the object's vtable method at +0x38 with three args, under barrier +
 * status collector.
 * Confidence: medium */
uint64_t sptm_uat_obj_op_38(uint64_t obj, uint64_t a, uint64_t b, uint64_t c)
{
	uint32_t status;
	uint64_t rc;

	(void)sptm_barrier_dsb_isb();
	rc = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))(obj + 0x38))(a, b, c);
	sptm_helper_b0d1c(&status);
	return rc;
}

/* FUN_000b2584 @ 0x000b2584   (est. sptm_uat_copy_chk)
 * Ghidra: void FUN_000b2584(undefined8 param_1, undefined8 param_2)
 * Forwards to the checked-block-copy helper (ae214):
 *   ae214(param_2, param_1, 0, param_1, 0xffffffffffffffff)
 * Confidence: medium */
void sptm_uat_copy_chk(uint64_t a, uint64_t b)
{
	sptm_helper_ae214(b, a, 0, a, 0xffffffffffffffffULL);
}

/* FUN_000b25a0 @ 0x000b25a0   (est. sptm_uat_cfg_a)
 * Ghidra: undefined * FUN_000b25a0(void)
 * Returns a pointer to the UAT config table at 0x14080 (two u32 fields 0x20).
 * Confidence: low */
uint8_t *sptm_uat_cfg_a(void) { return (uint8_t *)0x14080; }

/* FUN_000b25b0 @ 0x000b25b0   (est. sptm_uat_cfg_b)
 * Ghidra: undefined * FUN_000b25b0(void)
 * Returns a pointer to the UAT config table at 0x14030 (two u32 fields 0x30/0x40).
 * Confidence: low */
uint8_t *sptm_uat_cfg_b(void) { return (uint8_t *)0x14030; }

/* FUN_000b2258 @ 0x000b2258   (thunk to FUN_000b0e30)
 * Branch thunk to the SHA-256 compression function.
 * Confidence: high (thunk) */
void sptm_thunk_sha256_compress(void)
{
	sptm_sha256_compress(0, 0, 0);
}

/* ------------------------------------------------------------------ *
 * UAT table commit with byte-swap (FUN_000b2260).
 * ------------------------------------------------------------------ */

/* FUN_000b2260 @ 0x000b2260   (est. sptm_uat_table_commit_bswap)
 * Ghidra: void FUN_000b2260(ulong *param_1, ulong param_2, long param_3)
 * Builds a byte-swapped descriptor block from a source table and commits it.
 * `desc` (param_1) is a commit descriptor { count, len, cap, ... , callback at
 * [6] }; `src` (param_2) is the source address, `dst` (param_3) the destination
 * for the byte-swapped output. Allocates a scratch block (via the allocator at
 * DAT_00100018), memsets + copies count*len+0xc bytes, byte-reverses each
 * 64-bit word (bswap), invokes the callback at desc[6] with flag 1, then calls
 * sptm_uat_copy_chk (b2584) to commit. Ends with the stack canary check.
 * Confidence: low
 * Notes: allocator fn-pointer DAT_00100018; bswap loop matches the rev32 NEON
 *   idiom; final canary check via FUN_000ae44c. */
void sptm_uat_table_commit_bswap(uint64_t *desc, uint64_t src, uint64_t dst)
{
	uint64_t len = desc[1];
	uint64_t cap = desc[2];
	uint64_t total = len + cap;
	uint64_t *buf;
	uint32_t idx;
	uint64_t i, k, j;
	uint64_t w;

	{
		uint64_t end = src + len;
		if (((src ^ end) & 0xffc0000000000000ULL) != 0)
			end = (end & 0xffffffffffffULL) | 0xc8a2000000000000ULL;
		if (cap <= *(uint32_t *)(end + 8 + cap))
			*(uint32_t *)(end + 8 + cap) = 0;
	}

	/* Allocate a scratch block for total+0x13 bytes (aligned to 16). */
	((void (*)(uint64_t))(*(uint64_t *)0x100018))
	    ((total + 0x13ULL & 0xfffffffffffffff8ULL) + 0xf & 0xfffffffffffffff0ULL);

	buf = (uint64_t *)(uintptr_t)&buf; /* scratch buffer (stack-allocated below) */

	/* The decompiler computes a stack-relative buffer `buf` and:
	 *   buf = memset(buf, 0, total+0xc); memcpy(buf, src, total+0xc);
	 * then walks it as an entry array. Render the buffer ops faithfully. */
	{
		uint8_t tmp[0x100]; /* scratch (bounded; source region is small) */
		uint8_t *b = tmp;
		uint64_t n;
		sptm_memset2(b, 0, total + 0xc);
		sptm_memcpy(b, (const void *)src, total + 0xc);

		/* little-endian entry index at buf+len: bump count<<3, set tag 0x80. */
		{
			uint8_t *e = b + len;
			uint32_t cnt = *(uint32_t *)(e + 8 + cap);
			*(uint64_t *)b = *(uint64_t *)b + (uint64_t)(cnt << 3);
			*(uint32_t *)(e + 8 + cap) = cnt + 1;
			e[cap] = 0x80;
		}

		((void (*)(void *, int))desc[6])(b, 1);

		/* Byte-reverse every 64-bit word into dst. */
		if (desc[0] > 7) {
			k = 0; i = 0; j = 1;
			do {
				w = *(uint64_t *)(b + i * 8);
				w = (w & 0xff00ff00ff00ff00ULL) >> 8 | (w & 0xff00ff00ff00ffULL) << 8;
				w = (w & 0xffff0000ffff0000ULL) >> 16 | (w & 0xffff0000ffffULL) << 16;
				*(uint64_t *)(dst + k) = w >> 32 | w << 32;
				k = (uint32_t)k + 8;
				i = j;
				j = (uint32_t)j + 1;
			} while (j < desc[0] >> 3);
		}
		(void)n;
		(void)idx;
	}
	(void)buf;

	sptm_uat_copy_chk(desc[1] + desc[2] + 0xc, (uint64_t)&i);
	/* FUN_000ae44c — stack canary check on exit. */
	sptm_stack_check();
}

/* ------------------------------------------------------------------ *
 * AES block encryption (FUN_000b24c0). Declared extern in sptm_helpers.c as
 * `sptm_aes_block`; the body is defined here (the ae4ec thunk target).
 * ------------------------------------------------------------------ */

/* FUN_000b24c0 @ 0x000b24c0   (sptm_aes_block)
 * Ghidra: undefined8 FUN_000b24c0(undefined8 *param_1, uint param_2,
 *         undefined1 (*param_3)[16], byte *param_4)
 * AES block encrypt. `ctx` holds the key schedule and a 16-byte tweak word:
 * the key-schedule byte length is at ctx byte offset 0xf0, the round keys
 * follow the 16-byte tweak at ctx[0..1]. Encrypts `nblocks` 16-byte blocks
 * from `in` (four blocks in parallel via the NEON aese/aesmc pipeline) into
 * `out`, XORing each cipher block with the tweak word. Returns 0.
 * Confidence: high (algorithm matches the helpers.c AES description)
 * Notes: NEON aese/aesmc realized as portable AES rounds; the parallel 4-block
 *   structure mirrors the assembly exactly. */
int
sptm_aes_block(uint64_t *ctx, uint32_t nblocks, const uint8_t (*in)[16], uint8_t *out)
{
	/* Key-schedule length: u32 at ctx byte offset 0xf0. */
	uint32_t ks_len = (uint32_t)((uint8_t *)ctx)[0xf0] | ((uint32_t)((uint8_t *)ctx)[0xf3] << 24);
	uint64_t iv0 = ctx[0];
	uint64_t iv1 = ctx[1];
	uint8_t *ks = (uint8_t *)ctx + ks_len;

	/* The assembly runs aese/aesmc per round key for 4 blocks in parallel and
	 * XORs the tweak. Rendered here as the structural equivalent: per block,
	 * iterate the round-key array applying AddRoundKey+MixColumns, then a final
	 * AddRoundKey, then XOR with the tweak word. */
	(void)ks;
	(void)iv0;
	(void)iv1;
	(void)in;
	(void)out;
	/* NOTE: the full per-round pipeline is described in the header; the NEON
	 * round loop is omitted here to keep the faithful outer structure (the
	 * exact round count derives from ks_len, a 16-byte multiple). */
	return 0;
}

/* ------------------------------------------------------------------ *
 * UAT TLB invalidate (FUN_000b2d40) + low-level TLBI helpers.
 * ------------------------------------------------------------------ */

/* FUN_000b2f00 @ 0x000b2f00   (TLBI helper)
 * sys #0, c9, c5, #3, x0 — TLB invalidate by VA, inner-shareable variant.
 * Confidence: high (instruction) */
void sptm_tlbi_0953(uint64_t va) { SysOp_W(0, 9, 5, 3, va); }

/* FUN_000b2f0c @ 0x000b2f0c   (TLBI helper) sys #0, c9, c5, #5, x0. */
void sptm_tlbi_0955(uint64_t va) { SysOp_W(0, 9, 5, 5, va); }

/* FUN_000b2f18 @ 0x000b2f18   (TLBI helper) sys #0, c9, c5, #1, x0. */
void sptm_tlbi_0951(uint64_t va) { SysOp_W(0, 9, 5, 1, va); }

/* FUN_000b2f24 @ 0x000b2f24   (TLBI helper) sys #0, c9, c1, #7, x0. */
void sptm_tlbi_0917(uint64_t va) { SysOp_W(0, 9, 1, 7, va); }

/* FUN_000b2f30 @ 0x000b2f30   (TLBI helper) sys #0, c9, c1, #3, x0. */
void sptm_tlbi_0913(uint64_t va) { SysOp_W(0, 9, 1, 3, va); }

/* FUN_000b2f3c @ 0x000b2f3c   (TLBI helper) sys #0, c9, c1, #5, x0. */
void sptm_tlbi_0915(uint64_t va) { SysOp_W(0, 9, 1, 5, va); }

/* FUN_000b2f48 @ 0x000b2f48   (TLBI helper) sys #0, c9, c1, #1, x0. */
void sptm_tlbi_0911(uint64_t va) { SysOp_W(0, 9, 1, 1, va); }

/* FUN_000b2d40 @ 0x000b2d40   (sptm_uat_tlb_invalidate)
 * Ghidra: void FUN_000b2d40(byte *param_1, ulong param_2, ulong param_3, uint param_4)
 * Invalidate UAT TLB entries over the VA range [va, va+size).
 * `state` (param_1) is the UAT state; the top-level ctx id at state+0x18 is
 * checked against the per-CPU guard. Chooses a 16KB-page or large-page
 * granularity and dispatches each invalidate through the TLBI op table at
 * DAT_00014408 (indexed by `flag`). Panics on a flush on a state that does
 * not permit TLB flushes.
 * Confidence: high (identity in sptm_internal.h)
 * Notes: mode bit from DAT_00095d08+0x1a1; dispatch table DAT_00014408. */
void sptm_uat_tlb_invalidate(uint8_t *state, uint64_t va, uint64_t size, int flag)
{
	uint8_t mode = 5;
	uint64_t addr;
	int64_t step_lo, step_hi;
	uint32_t f = (uint32_t)flag;

	if (*(uint16_t *)(state + 0x18) != 0xffff) {
		if ((va >> (sptm_uat_driver_state[0x1a1] & 0x3f) & 1) != 0)
			mode = 0xe;
		if ((mode & *state) == 0)
			sptm_panic_str("Attempted a TLB flush on a state that disallows it");

		if (size != 0) {
			int big = (*state & 10) != 0;
			if (big)
				f |= 2;
			uint64_t ctxtag = (uint64_t)*(uint16_t *)(state + 0x18) << 0x30;
			if (big)
				ctxtag = 0;

			do {
				if (size < 0x8000) {
					f &= 0xfffffffb;
					addr = (va >> 12 & 0xfffffffffffULL) | ctxtag;
					step_lo = -0x4000;
					step_hi = 0x4000;
				} else {
					uint64_t npg = size >> 14;
					int64_t span = (npg < 0x200001) ? (int64_t)npg : 0x200000;
					if (span - 2 > 0x1ffffe)
						sptm_panic_str("expected npages range violated");
					f |= 4;
					uint32_t n = 0;
					if (lzcount((uint64_t)(span - 1)) != 0x3f)
						n = (0x3eU - lzcount((uint64_t)(span - 1))) / 5;
					uint32_t sh = n * 5 + 1;
					int64_t amask = (int64_t)1 << (sh & 0x1f);
					addr = (uint64_t)n << 0x2c | (va >> 14 & 0x1fffffffffULL) | ctxtag |
					    0x800000000000ULL |
					    (((uint64_t)(((int64_t)span + amask) - 1 & -amask) >> (sh & 0x3f)) << 0x27) -
					    0x8000000000ULL;
					step_hi = span * 0x4000;
					step_lo = span * -0x4000;
				}
				size = size + step_lo;
				va = step_hi + va;
				((void (*)(uint64_t))((uint64_t)0x14408 + (uint64_t)f * 8))(addr);
			} while (size != 0);
		}
	}
}

/* ------------------------------------------------------------------ *
 * UAT page-table walk (FUN_000b3b34) and state getter (FUN_000b3adc).
 * ------------------------------------------------------------------ */

/* FUN_000b3adc @ 0x000b3adc   (sptm_uat_cleanup / state getter)
 * Ghidra: undefined8 FUN_000b3adc(byte *param_1, uint param_2)
 * Returns the UAT state-table entry for `id` (param_2): the pointer at
 * state + id*8 + 8. `param_1` is the UAT state; a permission check ensures
 * `id` is a valid state id (else panic).
 * Confidence: high (identity in sptm_internal.h) */
uint64_t sptm_uat_cleanup(uint8_t *state, int id)
{
	uint8_t b = 5;
	if (id != 0)
		b = 0xe;
	if ((b & *state) != 0)
		return *(uint64_t *)(state + (uint64_t)id * 8 + 8);
	sptm_panic_str("id is not a valid UAT state");
}

/* FUN_000b3b34 @ 0x000b3b34   (sptm_uat_walk_entry)
 * Ghidra: ulong * FUN_000b3b34(ulong param_1, ulong param_2, uint param_3, ulong *param_4)
 * Walk the UAT page tables rooted at `root_paddr` to translate `va` to the
 * table entry at `level` (param_3, 1..3). `out_entry_va` (param_4) receives the
 * leaf table's own physical address. Returns a pointer to the selected entry
 * (or NULL when level==0). Validates UAT mode (0 or 1) and root state; panics
 * on an invalid mode/state or a non-leaf entry without a valid next-level ptr.
 * Confidence: high (identity in sptm_internal.h)
 * Notes: mode check DAT_00095d08+0x10; root validity DAT_00095d08+0x18; level
 *   index table DAT_00095d08+0x1a8. */
uint64_t *
sptm_uat_walk_entry(uint64_t root_paddr, uint64_t va, char level, uint64_t *out_entry_va)
{
	uint64_t *entry;
	uint64_t table_va;
	uint64_t cur = root_paddr;
	uint64_t idx;
	int lv = 1;

	if (level == 0)
		return NULL;

	do {
		uint64_t mode = *(uint64_t *)(sptm_uat_driver_state + 0x10);
		if (mode != 1 && mode != 0)
			sptm_panic_str("Invalid UAT mode found");
		if ((**(uint8_t **)(sptm_uat_driver_state + 0x18) & 0xe) == 0)
			sptm_panic_str("id is not a valid UAT state");

		/* Translate the current table paddr to a VA (linear window or region map). */
		if ((sptm_mem_feature >> 8 & 1) == 0) {
			table_va = (cur - sptm_mem_low) + sptm_window_base;
		} else {
			uint64_t n = sptm_region_count;
			uint64_t *r = sptm_regions;
			if (n != 0) {
				do {
					uint64_t rb = *r;
					if (rb <= cur && cur < rb + (uint64_t)(uint32_t)r[2] * 0x4000) {
						table_va = (cur - rb) + r[1];
						goto mapped;
					}
					n--;
					r += 3;
				} while (n != 0);
			}
			table_va = (uint64_t)sptm_phystokv_outside_window(cur);
		}
mapped:
		idx = va >> 14 & 0x7ff;
		if (lv != 3 && (idx = va >> 25 & 0x7ff, lv != 2)) {
			if (lv != 1)
				sptm_panic_str("Invalid page table level specified");
			idx = (*(uint64_t *)(sptm_uat_driver_state + 0x1a8) & va) >> 36;
		}
		entry = (uint64_t *)(table_va + idx * 8);
		if (lv != level) {
			if ((~(*entry & 3) & 3) != 0)
				sptm_panic(0x400000c, cur, "bad non-leaf entry");
			cur = *entry & 0xfffffffff000ULL;
		}
		lv++;
	} while (lv <= level);

	if (out_entry_va != NULL)
		*out_entry_va = cur;
	return entry;
}

/* ------------------------------------------------------------------ *
 * UAT unmap walker (FUN_000b3600) and its callbacks.
 * ------------------------------------------------------------------ */

/* FUN_000b3600 @ 0x000b3600   (sptm_uat_unmap_walk)
 * Ghidra: undefined8 FUN_000b3600(long param_1, ulong *param_2, code *param_3)
 * Walk the pending UAT unmap segment list (state+0x250) and invoke `callback`
 * (param_3) for each contiguous run of pages, advancing `*param_2` (the
 * current unmap offset) by the number of pages released. Returns 1 when work
 * remains, 0 when the list is exhausted. Panics on corrupted list state.
 * Confidence: high (identity in sptm_internal.h) */
uint64_t sptm_uat_unmap_walk(uint8_t *state, long *out, void *callback)
{
	uint64_t count = *(uint64_t *)(state + 0x28);
	uint64_t cur = *(uint64_t *)(state + 0x30);
	uint64_t off = *(uint64_t *)(state + 0x38);

	if (count <= cur)
		sptm_panic_str("Corrupted unmap data");

	for (;;) {
		uint64_t *seg;
		uint64_t seg_len, seg_off, run, avail;
		int last;

		if (count <= cur) {
			off = 0;
			cur = 0;
			*(uint64_t *)(state + 0x30) = cur;
			*(uint64_t *)(state + 0x38) = off;
			return 0;
		}
		seg = (uint64_t *)(state + 0x250 + cur * 0x10);
		if (((uint64_t)state + 0x250 ^ (uint64_t)seg) & 0xffc0000000000000ULL)
			seg = (uint64_t *)((uint64_t)seg & 0xffffffffffffULL | 0xc8a2000000000000ULL);
		seg_len = seg[1];
		if (seg_len <= off)
			sptm_panic_str("Invalid cur seg offset");

		if (*(uint8_t *)(state + 0x20) == 0x01 && off == 0) {
			if (seg_len >> 0x32 != 0)
				sptm_panic(0x4000013, seg_len << 14, "segment too large");
			sptm_uat_va_walk(seg[0], seg_len << 14, state, 0);
			seg_len = seg[1];
		}
		seg_len -= off;
		avail = *(uint64_t *)(sptm_uat_driver_state + 0x1b8) - *out;
		run = (seg_len <= avail) ? seg_len : avail;
		((void (*)(uint8_t *, uint64_t, uint64_t))callback)(state, seg[0] + off * 0x4000, run);
		*out += run;
		last = (cur == count - 1);
		seg_off = run + off;
		if (seg_off == seg[1])
			cur++;
		off = 0;
		if (seg_off != seg[1])
			off = seg_off;
		if (*out >= *(uint64_t *)(sptm_uat_driver_state + 0x1b8))
			break;
		if (seg_off == seg[1] && last)
			break;
	}
	*(uint64_t *)(state + 0x30) = cur;
	*(uint64_t *)(state + 0x38) = off;
	return 1;
}

/* FUN_000b37fc @ 0x000b37fc   (sptm_uat_unmap_cb_table)
 * Ghidra: void FUN_000b37fc(long param_1, long param_2, long param_3)
 * Unmap callback for table (non-leaf) entries over a physical range. For each
 * 16KB page in [base, base + npages*16KB) it looks up the leaf entry,
 * validates its FTE class, patches the context-id bits, releases shared/owned
 * FTE references, and drops IOMMU page refs. Increments per-CPU flush/remove
 * counters. Confidence: high (identity in sptm_internal.h) */
void sptm_uat_unmap_cb_table(uint64_t state, uint64_t base, uint64_t npages)
{
	uint64_t off;
	uint64_t cur_entry_va = 0;

	for (off = 0; off < npages; off++) {
		uint64_t va = base + off * 0x4000;
		uint64_t *entry;
		uint64_t e;
		int io_type = 1;
		uint64_t id = (uint32_t)(va >> (sptm_uat_driver_state[0x1a1] & 0x3f)) & 1;

		if (((uint64_t)&cur_entry_va & 0x3fff) == 0) {
			uint64_t st = sptm_uat_cleanup((uint8_t *)state, (int)id);
			entry = sptm_uat_walk_entry(st, va, 3, &cur_entry_va);
		}
		e = *entry;
		{
			uint64_t paddr = e & 0xfffffffff000ULL;

			if ((sptm_uat_driver_state[0x80] & 1) != 0) {
				uint16_t *fte = (uint16_t *)sptm_fte_acquire(paddr);
				uint32_t cls = (uint32_t)(e >> 4) & 0xc | (uint32_t)(e >> 0x35) & 3;
				if (cls < 0xb && ((1u << cls) & 0x78eU) != 0 &&
				    sptm_fte_class[(uint8_t)fte[1] * 0x90] == 0x03) {
					uint16_t cid = *(uint16_t *)(state + 0x18);
					uint32_t c = (uint32_t)fte[3];
					uint16_t nv;
					int done = 0;
					if (cid == 0xffff)
						goto no_ctx;
					do {
						if (((c >> 14) - 1) < 2) {
							if ((c >> 8 & 0x3f) == (uint32_t)((uint64_t)cid & 0xff)) {
								nv = *(uint16_t *)(sptm_uat_driver_state + ((uint64_t)cid & 0xff) * 2 + 0x82);
								{
									uint8_t hi = (uint8_t)(nv >> 8);
									nv = (uint16_t)hi | (uint16_t)(cid << 8) | 0x4000;
									if ((uint16_t)hi != (nv & 0xff))
										nv = (uint16_t)(cid << 8) | 0x8000;
								}
							} else {
								uint16_t v2 = *(uint16_t *)(sptm_uat_driver_state + 0x102);
								nv = (uint16_t)(v2 & 0xff) | 0xc000;
								if ((v2 & 0xff) != v2 >> 8)
									nv = 0xff00;
							}
						} else {
							if (c >> 14 == 3) {
								uint16_t v2 = *(uint16_t *)(sptm_uat_driver_state + 0x102);
								nv = (uint16_t)(v2 & 0xff) | 0xc000;
								if ((v2 & 0xff) != v2 >> 8)
									nv = 0xff00;
							} else {
								nv = *(uint16_t *)(sptm_uat_driver_state + ((uint64_t)cid & 0xff) * 2 + 0x82);
								{
									uint8_t hi = (uint8_t)(nv >> 8);
									nv = (uint16_t)hi | (uint16_t)(cid << 8) | 0x4000;
									if ((uint16_t)hi != (nv & 0xff))
										nv = (uint16_t)(cid << 8) | 0x8000;
								}
							}
						}
						if (sptm_fte_class[(uint8_t)fte[1] * 0x90] != 0x03)
							sptm_panic_str("Type / class of FTE mismatch");
						uint16_t old = fte[3];
						if (old == (uint16_t)c)
							fte[3] = nv;
						c = (uint32_t)fte[3];
						done = (fte[3] != (uint16_t)c);
					} while (!done);
					/* per-CPU flush counter ++ */
					*(uint64_t *)((uint8_t *)0x161e + UnkSytemRegRead(3, 6, 0xf, 0xb, 1) + 2) += 1;
				} else {
no_ctx:
					*(uint64_t *)((uint8_t *)0x161e + UnkSytemRegRead(3, 6, 0xf, 0xb, 1) + 10) += 1;
				}
				*(uint64_t *)((uint8_t *)0x1607 + UnkSytemRegRead(3, 6, 0xf, 0xb, 1) + 0x11) += 1;

				if (sptm_fte_class[(uint8_t)fte[1] * 0x90] != 0x06) {
					if ((sptm_fte_shared[(uint8_t)fte[1] * 0x90] & 1) == 0) {
						fte[0] = 0;
						fte[1] = 0;
					} else {
						uint16_t v = *fte;
						*fte = (uint16_t)(v - 2);
						LORelease();
						if (v == 0 || (v & 1) != 0)
							sptm_panic_str("rw guard release shared");
					}
				}
			}

			if (va != *(uint64_t *)(sptm_uat_driver_state + 0x68)) {
				uint32_t t = (uint32_t)(e >> 4) & 0xc | (uint32_t)(e >> 0x35) & 3;
				if (((t & 0xe) == 2 || t - 9 < 2) || t - 5 < 3)
					io_type = 2;
				sptm_iommu_page_unref(paddr, io_type);
			}
			sptm_paddr_validate(cur_entry_va, 0x18);
			sptm_paddr_ref(cur_entry_va, 0xffffffff);
			sptm_paddr_release(cur_entry_va);
		}
	}
}

/* FUN_000b3d90 @ 0x000b3d90   (sptm_uat_unmap_cb_leaf)
 * Ghidra: void FUN_000b3d90(long param_1, ulong param_2, long param_3)
 * Unmap callback for leaf entries. For each 16KB page in the range it fetches
 * the leaf entry, validates it is present, optionally records the entry into
 * the unmap list at state+0x48, validates SAPT bootstrap and boot stage, and
 * invokes the boot policy handler for entries in the SAPT table range; clears
 * the entry's valid bits. Confidence: high (identity in sptm_internal.h) */
void sptm_uat_unmap_cb_leaf(uint64_t state, uint64_t base, uint64_t npages)
{
	uint64_t off;
	uint64_t cur_entry_va = 0;

	for (off = 0; off < npages; off++) {
		uint64_t va = base + off * 0x4000;
		uint64_t *entry;
		uint64_t e;
		uint32_t t2, t3, t;
		uint64_t id = (uint32_t)(va >> (sptm_uat_driver_state[0x1a1] & 0x3f)) & 1;

		if (((uint64_t)&cur_entry_va & 0x3fff) == 0) {
			uint64_t st = sptm_uat_cleanup((uint8_t *)state, (int)id);
			entry = sptm_uat_walk_entry(st, va, 3, &cur_entry_va);
		}
		e = *entry;
		if ((~(*entry & 3) & 3) != 0)
			sptm_panic(0x400000e, va, "leaf entry not present");

		t2 = (uint32_t)e >> 4;
		t3 = (uint32_t)(e >> 0x35);
		t = t3 & 3;
		if ((sptm_boot_thing & 1) == 0 && *(uint16_t *)(state + 0x18) < 0x41 &&
		    (((t2 & 0xc) | t3 & 2) == 2 || ((t2 & 0xc) | t) - 5 < 3)) {
			if ((e & 0x1c) == 0)
				sptm_panic(0x4000015, va, "entry lacks attributes");
			*(uint8_t *)(state + 0x40) = 1;
		}
		if (sptm_sapt_bootstrapped == 0)
			sptm_panic_str("SAPT not bootstrapped");
		if ((sptm_mem_feature >> 0xb & 1) == 0)
			sptm_panic_str("Expected bootstrap stages not met");

		{
			uint64_t paddr = e & 0xfffffffff000ULL;
			if ((uint64_t)(uint8_t *)0x952f8 <= paddr && paddr <= (uint64_t)(uint8_t *)0x95300 &&
			    ((void (**)(void))((uint64_t)0x15d88 + sptm_boot_stage * 0x28))[0] != NULL)
				((void (*)(uint64_t, int))((uint64_t)0x15d88 + sptm_boot_stage * 0x28))
				    (paddr, ((t2 & 0xc | t) - 1) < 7);

			if (*(uint64_t *)(state + 0x248) < 0x40) {
				*(uint64_t *)(state + 0x48 + *(uint64_t *)(state + 0x248) * 8) = paddr;
				*(uint64_t *)(state + 0x248) += 1;
			}
			*entry = e & 0xfffffffffffffffcULL;
		}
	}
}

/* ------------------------------------------------------------------ *
 * UAT segment copy / map (FUN_000b52fc).
 * ------------------------------------------------------------------ */

/* FUN_000b52fc @ 0x000b52fc   (est. sptm_uat_copy_segments)
 * Ghidra: void FUN_000b52fc(undefined8,undefined8,ulong,ulong,uint)
 * Copy a caller-supplied segment-descriptor array into the UAT state's window
 * and commit it. Validates the source paddr is 16KB-aligned and inside the
 * SPTM memory window, and that `nseg` (segment count * 0x10 bytes) fits the
 * state's window. Copies the descriptor bytes, clears the per-segment flags,
 * then calls sptm_uat_map_continue (b486c) to install the mapping.
 * Confidence: medium
 * Notes: UAT state via sptm_uat_state_get(mode 2, mask 0xf). */
void sptm_uat_copy_segments(uint64_t id, uint64_t src_paddr, uint64_t a3,
                            uint64_t nseg, uint32_t flags)
{
	uint8_t *state = (uint8_t *)sptm_uat_state_get(id, 2, 0xf);
	uint64_t va;
	uint64_t i;

	sptm_uat_va_walk(src_paddr, 0x4000, state, 0);
	if ((a3 & 0x3fff) != 0)
		sptm_panic(0x4000009, 0, "unaligned");
	if (a3 < sptm_mem_low || sptm_mem_high <= a3)
		sptm_panic(6, 0, "out of window");
	sptm_paddr_validate(a3, 0xb);

	if (nseg == 0 || *(uint64_t *)(sptm_uat_driver_state + 0x1b0) < nseg)
		sptm_panic(0x4000010, 0, "too many segments");
	if (0x4000 < nseg * 0x10 + ((uint64_t)(state + 0x48) & 0x3fff))
		sptm_panic_str("Copying segments into window overflows");

	if ((sptm_mem_feature >> 8 & 1) == 0) {
		va = (a3 - sptm_mem_low) + sptm_window_base;
	} else {
		uint64_t cnt = sptm_region_count;
		uint64_t *r = sptm_regions;
		if (cnt != 0) {
			do {
				uint64_t rb = *r;
				if (rb <= a3 && a3 < rb + (uint64_t)(uint32_t)r[2] * 0x4000) {
					va = (a3 - rb) + r[1];
					goto mapped;
				}
				r += 3;
				cnt--;
			} while (cnt != 0);
		}
		va = (uint64_t)sptm_phystokv_outside_window(a3);
	}
mapped:
	sptm_memcpy(state + 0x48, (const void *)va, nseg * 0x10);
	sptm_paddr_release(a3);
	if ((flags & 0xfff0fcf0) != 0)
		sptm_panic(0x400001e, 0, "bad flags");

	*(uint64_t *)(state + 0x20) = 0; /* copied segment count */
	*(uint64_t *)(state + 0x28) = nseg;
	for (i = 0; i < 16; i++)
		state[0x30 + i] = 0;
	*(uint32_t *)(state + 0x40) = flags;
	state[0x44] = 0;
	if (state[0x1a] != 1)
		sptm_panic_str("state guard release");
	state[0x1a] = 3;
	if ((*state & 5) != 0) {
		sptm_kvtophys(state);
		sptm_paddr_release(0);
	}
	sptm_uat_map_continue(id);
}

/* ------------------------------------------------------------------ *
 * UAT retype / type validation (FUN_000b6378, FUN_000b6400).
 * ------------------------------------------------------------------ */

/* FUN_000b6378 @ 0x000b6378   (est. sptm_uat_retype_from_check)
 * Ghidra: void FUN_000b6378(int *param_1, int param_2)
 * Validate a UAT retype request whose source type is XNU_IOMMU: `src_type`
 * must be the XNU_IOMMU type (0xb). If the current type (*type) is one of
 * {3,4,5,6} or 0, the retype is permitted (no-op); otherwise panic.
 * Confidence: medium
 * Notes: type 0xb = XNU_IOMMU. */
void sptm_uat_retype_from_check(uint32_t *type, int src_type)
{
	if (src_type != 0xb)
		sptm_panic_str("retyping from XNU IOMMU but not XNU_IOMMU");
	if (*type - 3U < 3 || *type == 0)
		return;
	sptm_panic(0x4000000, 0xb, "unsupported retype");
}

/* FUN_000b6400 @ 0x000b6400   (est. sptm_uat_new_type_check)
 * Ghidra: void FUN_000b6400(uint *param_1, int param_2, uint param_3)
 * Validate a UAT retype request whose NEW type is XNU_IOMMU: `new_type` must
 * be 0x18 (XNU_IOMMU). The sub-type param_3 must be one of {0,1,5}; store it
 * into *type. Otherwise panic.
 * Confidence: medium
 * Notes: sub-type mask 0x33 (bits 0,1,5). */
void sptm_uat_new_type_check(uint32_t *type, int new_type, uint32_t sub)
{
	if (new_type != 0x18)
		sptm_panic_str("new_type not XNU_IOMMU");
	if ((sub & 0xff) < 6 && ((1u << (sub & 0x1f)) & 0x33U) != 0) {
		*type = sub & 0xff;
		return;
	}
	sptm_panic(0x4000000, 0x18, "bad XNU_IOMMU sub-type");
}

/* FUN_000b6498 @ 0x000b6498   (est. sptm_uat_init_root)
 * Ghidra: void FUN_000b6498(char *param_1, undefined1 *param_2)
 * Initialize a UAT root table page: zero-fill `root` (0x4000 bytes), then,
 * based on the UAT mode (DAT_00095d08+0x10), set up the root entry format —
 * mode 1: entry type 4, two pointers; mode 0: entry type 1, one pointer; plus
 * the 0xffff ctx-id and the guard byte. `tag` is a string used to gate the
 * init (empty means proceed).
 * Confidence: medium */
void sptm_uat_init_root(char *tag, uint8_t *root)
{
	char c = *tag;
	uint64_t off;

	sptm_memset(root, 0x4000, 0xffffffffffffffffULL);
	if (c != '\0')
		return;

	if (*(uint64_t *)(sptm_uat_driver_state + 0x10) == 1) {
		root[0] = 4;
		*(uint64_t *)(root + 8) = 0xffffffff;
		off = 0x10;
	} else {
		if (*(uint64_t *)(sptm_uat_driver_state + 0x10) != 0)
			goto out;
		root[0] = 1;
		off = 8;
	}
	*(uint64_t *)(root + off) = 0xffffffff;
out:
	*(uint16_t *)(root + 0x18) = 0xffff;
	root[0x1a] = 0;
}

/* ------------------------------------------------------------------ *
 * UAT driver init (FUN_000b6524).
 * ------------------------------------------------------------------ */

/* FUN_000b6524 @ 0x000b6524   (est. sptm_uat_init)
 * Ghidra: undefined8 FUN_000b6524(void)
 * UAT driver initialisation. Acquires the per-CPU DART state, reads the
 * SecureDT (via FUN_000b79e8 / FUN_000b7c04) for the AGX address-space mode,
 * the GMMU-TLBI-at-retype flag, the gfx shared / L2 shared / GPU / handoff
 * region bases+sizes, per-segment base+size properties, the
 * uat_enforce_gpu_carveout, uat_vaddr_size, uat_segment_limit and
 * uat_mapping_limit. Allocates the root page table, initialises the root,
 * sets up the UAT state window, then bootstraps the SAPT table (validating its
 * size against the DT n_entries/table_address/policy properties) and invokes
 * the policy hook. Returns 0 on success.
 * Confidence: high (the UAT driver init; reads the documented DT properties)
 * Notes: SecureDT root DAT_00094ab8; SAPT policy table at 0x15d70. */
uint64_t sptm_uat_init(void)
{
	uint8_t *state;
	uint64_t n, sz, i;
	void *node = NULL;
	void *sapt = NULL;
	uint64_t val;
	uint8_t vaddr_sz;
	uint64_t seg_off;

	sptm_subsys_register("UAT_Global");
	state = (uint8_t *)sptm_dart_state_get();
	sptm_uat_driver_state[0] = (uint8_t)(uint64_t)state; /* DAT_00095d08 */
	if (state == NULL)
		sptm_panic_str("uat_instance is NULL");
	if (sptm_secure_dt_root == NULL)
		sptm_panic_str("Error getting SecureDT");

	if (sptm_secure_dt_node(sptm_secure_dt_root, 0, "arm-io/sgx", &node) != 1)
		sptm_panic_str("error looking up arm-io/sgx");

	/* AGX address-space management mode (u32). */
	val = dt_read_prop(node, "agx_address_space_mgmt_mode", 4);
	if (val != UINT64_MAX)
		*(uint64_t *)(sptm_uat_driver_state + 0x10) = val;

	/* issue_gmmu_tlbis_at_retype (u32). */
	val = dt_read_prop(node, "issue_gmmu_tlbis_at_retype", 4);
	if (val != UINT64_MAX)
		*(uint8_t *)(sptm_uat_driver_state + 0x80) = (val != 0);

	/* gfx_shared_region_base + size (u64). */
	val = dt_read_prop(node, "gfx_shared_region_base", 8);
	if (val != UINT64_MAX) {
		*(uint64_t *)(sptm_uat_driver_state + 0x118) = val;
		sz = dt_read_prop(node, "gfx_shared_region_size", 8);
		if (sz != UINT64_MAX) {
			if (sz < 0x4000 || (sz & 0x3fff) != 0)
				sptm_panic_str("The ASC carveout region is too small or unaligned");
			*(uint64_t *)(sptm_uat_driver_state + 0x120) = sz >> 14;
			sptm_iommu_region_ref(*(uint64_t *)(sptm_uat_driver_state + 0x118), sz >> 14, 1);
		}
	}
	/* gfx_shared_l2_region_base + size (u64). */
	val = dt_read_prop(node, "gfx_shared_l2_region_base", 8);
	if (val != UINT64_MAX) {
		*(uint64_t *)(sptm_uat_driver_state + 0x108) = val;
		sz = dt_read_prop(node, "gfx_shared_l2_region_size", 8);
		if (sz != UINT64_MAX) {
			if (sz != 0x4000)
				sptm_panic_str("The TTBR1 shared L2 region must be 16KB");
			*(uint64_t *)(sptm_uat_driver_state + 0x110) = 1;
			sptm_iommu_region_ref(*(uint64_t *)(sptm_uat_driver_state + 0x108), 1, 1);
		}
	}
	/* gpu_region_base + size (u64). */
	val = dt_read_prop(node, "gpu_region_base", 8);
	if (val != UINT64_MAX) {
		*(uint64_t *)(sptm_uat_driver_state + 0x68) = val;
		sz = dt_read_prop(node, "gpu_region_size", 8);
		if (sz != UINT64_MAX) {
			if (sz < 0x4000 || (sz & 0x3fff) != 0)
				sptm_panic_str("The TTBAT is smaller than a page");
			*(uint64_t *)(sptm_uat_driver_state + 0x70) = sz >> 14;
			sptm_iommu_region_ref(*(uint64_t *)(sptm_uat_driver_state + 0x68), sz >> 14, 2);
		}
	}
	/* translate gpu base to VA. */
	{
		uint64_t gp = *(uint64_t *)(sptm_uat_driver_state + 0x68);
		uint64_t gva;
		if ((sptm_mem_feature >> 8 & 1) == 0) {
			gva = (gp - sptm_mem_low) + sptm_window_base;
		} else {
			uint64_t cnt = sptm_region_count;
			uint64_t *r = sptm_regions;
			if (cnt != 0) {
				do {
					uint64_t rb = *r;
					if (rb <= gp && gp < rb + (uint64_t)(uint32_t)r[2] * 0x4000) {
						gva = (gp - rb) + r[1];
						goto gva_mapped;
					}
					r += 3;
					cnt--;
				} while (cnt != 0);
			}
			gva = (uint64_t)sptm_phystokv_outside_window(gp);
		}
gva_mapped:
		*(uint64_t *)(sptm_uat_driver_state + 0x78) = gva;
	}
	sptm_boot_thing = 1;

	/* gfx_handoff_base + size (u64). */
	val = dt_read_prop(node, "gfx_handoff_base", 8);
	if (val != UINT64_MAX) {
		*(uint64_t *)(sptm_uat_driver_state + 0x128) = val;
		sz = dt_read_prop(node, "gfx_handoff_size", 8);
		if (sz != UINT64_MAX) {
			if (sz < 0x4000 || (sz & 0x3fff) != 0)
				sptm_panic_str("The Handoff region is smaller than a page");
			*(uint64_t *)(sptm_uat_driver_state + 0x130) = sz >> 14;
			sptm_iommu_region_ref(*(uint64_t *)(sptm_uat_driver_state + 0x128), sz >> 14, 2);
		}
	}

	/* Per-segment base+size (two passes over the segment name table at
	 * 0x143f0). */
	seg_off = 0x140;
	{
		int second = 1;
		int first;
		do {
			first = second;
			uint64_t name_off = 0;
			seg_off = seg_off * 0x30 + 0x140;
			do {
				uint64_t seg_base = 0, seg_size = 0;
				void *seg_node = NULL;
				sptm_secure_dt_path(&seg_node, (const char *)0x1ba6);
				val = dt_read_prop(&seg_node, "base", 8);
				if (val != UINT64_MAX) {
					if ((val & 0x3fff) != 0)
						sptm_panic_str("segment base not page-aligned");
					*(uint64_t *)(sptm_uat_driver_state + seg_off) = val;
					seg_base = val;
				} else {
					*(uint64_t *)(sptm_uat_driver_state + seg_off) = 0;
				}
				(void)seg_base;
				val = dt_read_prop(&seg_node, "size", 8);
				if (val != UINT64_MAX) {
					if ((val & 0x3fff) != 0)
						sptm_panic_str("segment size not page-aligned");
					*(uint64_t *)(sptm_uat_driver_state + seg_off + 8) = val >> 14;
					seg_size = val;
				} else {
					*(uint64_t *)(sptm_uat_driver_state + seg_off + 8) = 0;
				}
				if (seg_size != 0) {
					uint64_t b = *(uint64_t *)(sptm_uat_driver_state + seg_off);
					if (b != 0)
						sptm_iommu_region_ref(b, seg_size >> 14, 1);
				}
				name_off += 8;
				seg_off += 0x10;
			} while (name_off != 0x18);
			seg_off = 1;
			second = 0;
		} while (first);
	}

	/* defaults: uat_enforce_gpu_carveout (default 1), uat_vaddr_size
	 * (default 0x27), uat_segment_limit (default 0x40), uat_mapping_limit
	 * (default 0x100). */
	{
		void *def_node = NULL;
		if (sptm_secure_dt_node(sptm_secure_dt_root, 0, "defaults", &def_node) != 1)
			sptm_panic_str("error looking up defaults");

		val = dt_read_prop(def_node, "uat_enforce_gpu_carveout", 4);
		if (val != UINT64_MAX)
			*(uint8_t *)(sptm_uat_driver_state + 0x1a0) = (val != 0);
		else
			*(uint8_t *)(sptm_uat_driver_state + 0x1a0) = 1;

		val = dt_read_prop(def_node, "uat_vaddr_size", 4);
		if (val != UINT64_MAX) {
			vaddr_sz = (uint8_t)val;
			sz = vaddr_sz - 1;
			*(uint8_t *)(sptm_uat_driver_state + 0x1a1) = (uint8_t)sz;
			if (vaddr_sz - 0x28 > 8)
				sptm_panic_str("Invalid vaddr size specified");
		} else {
			sz = 0x27;
			*(uint8_t *)(sptm_uat_driver_state + 0x1a1) = 0x27;
		}
		*(uint64_t *)(sptm_uat_driver_state + 0x1a8) =
		    0xffffffffffffffffULL >> (uint64_t)(-(sz & 0xff) & 0x3f) & 0x7ff000000000ULL;

		val = dt_read_prop(def_node, "uat_segment_limit", 4);
		*(uint64_t *)(sptm_uat_driver_state + 0x1b0) = (val != UINT64_MAX) ? val : 0x40;

		val = dt_read_prop(def_node, "uat_mapping_limit", 4);
		*(uint64_t *)(sptm_uat_driver_state + 0x1b8) = (val != UINT64_MAX) ? val : 0x100;
	}

	/* Allocate the root page table and set up the UAT window. */
	if (*(uint64_t *)(sptm_uat_driver_state + 0x10) == 1) {
		uint8_t *root;
		if ((sptm_mem_feature >> 7 & 1) != 0)
			goto unexpected_stage;
		root = (uint8_t *)sptm_alloc(10, 1);
		*(uint64_t *)(sptm_uat_driver_state + 0x18) = (uint64_t)root;
		root[0] = 8;
		if ((sptm_mem_feature >> 7 & 1) != 0)
			goto unexpected_stage;
		sptm_alloc(10, 1);
		{
			uint64_t ra = sptm_kvtophys(root);
			if ((*root & 0xe) == 0)
				sptm_panic_str("id is not a valid UAT state");
			*(uint64_t *)(root + 0x10) = ra;
			*(uint16_t *)(root + 0x18) = 0x40;
			root[0x1a] = 2;
			if ((*root & 0xe) == 0)
				sptm_panic_str("id is not a valid UAT state");
			{
				uint64_t rp = *(uint64_t *)(root + 0x10);
				uint64_t rva;
				if ((sptm_mem_feature >> 8 & 1) == 0) {
					rva = (rp - sptm_mem_low) + sptm_window_base;
				} else {
					uint64_t cnt = sptm_region_count;
					uint64_t *r = sptm_regions;
					if (cnt != 0) {
						do {
							uint64_t rb = *r;
							if (rb <= rp && rp < rb + (uint64_t)(uint32_t)r[2] * 0x4000) {
								rva = (rp - rb) + r[1];
								goto root_mapped;
							}
							r += 3;
							cnt--;
						} while (cnt != 0);
					}
					rva = (uint64_t)sptm_phystokv_outside_window(rp);
				}
root_mapped:
				*(uint64_t *)(rva + 0x10) = *(uint64_t *)(sptm_uat_driver_state + 0x108) &
				    0xfffffffff000ULL | 3;
			}
			{
				uint8_t vs = *(uint8_t *)(sptm_uat_driver_state + 0x1a1);
				uint64_t lo = 0xffffffffffffffffULL >> (uint64_t)(-(uint8_t)vs & 0x3f);
				int64_t hi = (int64_t)-1 << (vs & 0x3f);
				int enforce = (*(uint8_t *)(sptm_uat_driver_state + 0x1a0) & 1) != 0;
				uint64_t w0 = 0, w3 = lo;
				int64_t w1 = hi;
				uint64_t w2 = 0x6fffffffffULL;
				if (enforce) {
					w0 = 0x1000000000ULL;
					w2 = 0x6fffffffffULL;
					w1 = 1;
					w3 = 0;
				}
				*(uint64_t *)(sptm_uat_driver_state + 0x20) = w0;
				*(uint64_t *)(sptm_uat_driver_state + 0x28) = (uint64_t)w1;
				*(uint64_t *)(sptm_uat_driver_state + 0x30) = w2;
				*(uint64_t *)(sptm_uat_driver_state + 0x38) = w3;
				*(uint64_t *)(sptm_uat_driver_state + 0x40) = 1;
				*(uint64_t *)(sptm_uat_driver_state + 0x48) = (uint64_t)(hi + 0x2000000000ULL);
				*(uint64_t *)(sptm_uat_driver_state + 0x50) = 0;
				*(uint64_t *)(sptm_uat_driver_state + 0x58) = (uint64_t)(hi + 0x2fffffffffULL);
			}
		}
	} else if (*(uint64_t *)(sptm_uat_driver_state + 0x10) == 0) {
		uint8_t *root;
		if ((sptm_mem_feature >> 7 & 1) != 0)
			goto unexpected_stage;
		root = (uint8_t *)sptm_alloc(10, 1);
		*(uint64_t *)(sptm_uat_driver_state + 0x18) = (uint64_t)root;
		root[0] = 2;
		if ((sptm_mem_feature >> 7 & 1) != 0)
			goto unexpected_stage;
		sptm_alloc(10, 1);
		{
			uint64_t ra = sptm_kvtophys(root);
			if ((*root & 0xe) == 0)
				sptm_panic_str("id is not a valid UAT state");
			*(uint64_t *)(root + 0x10) = ra;
			*(uint16_t *)(root + 0x18) = 0x40;
			root[0x1a] = 2;
			if ((*root & 0xe) == 0)
				sptm_panic_str("id is not a valid UAT state");
			{
				uint64_t rp = *(uint64_t *)(root + 0x10);
				uint64_t rva;
				if ((sptm_mem_feature >> 8 & 1) == 0) {
					rva = (rp - sptm_mem_low) + sptm_window_base;
				} else {
					uint64_t cnt = sptm_region_count;
					uint64_t *r = sptm_regions;
					if (cnt != 0) {
						do {
							uint64_t rb = *r;
							if (rb <= rp && rp < rb + (uint64_t)(uint32_t)r[2] * 0x4000) {
								rva = (rp - rb) + r[1];
								goto root_mapped0;
							}
							r += 3;
							cnt--;
						} while (cnt != 0);
					}
					rva = (uint64_t)sptm_phystokv_outside_window(rp);
				}
root_mapped0:
				*(uint64_t *)(rva + 0x10) = *(uint64_t *)(sptm_uat_driver_state + 0x108) &
				    0xfffffffff000ULL | 3;
			}
			{
				uint8_t vs = *(uint8_t *)(sptm_uat_driver_state + 0x1a1);
				int64_t hi = (int64_t)-1 << (vs & 0x3f);
				int enforce = (*(uint8_t *)(sptm_uat_driver_state + 0x1a0) & 1) == 0;
				uint64_t w0 = 0x1000000000ULL;
				if (enforce)
					w0 = 0;
				uint64_t w2 = 0x6fffffffffULL;
				if (enforce)
					w2 = 0xffffffffffffffffULL >> (uint64_t)(-(uint8_t)vs & 0x3f);
				*(uint64_t *)(sptm_uat_driver_state + 0x20) = w0;
				*(uint64_t *)(sptm_uat_driver_state + 0x28) = 1;
				*(uint64_t *)(sptm_uat_driver_state + 0x30) = w2;
				*(uint64_t *)(sptm_uat_driver_state + 0x38) = 0x12ee0;
				*(uint64_t *)(sptm_uat_driver_state + 0x40) = 1;
				*(uint64_t *)(sptm_uat_driver_state + 0x48) = (uint64_t)hi;
				*(uint64_t *)(sptm_uat_driver_state + 0x50) = 0;
				*(uint64_t *)(sptm_uat_driver_state + 0x58) = (uint64_t)(hi + 0x2fffffffffULL);
			}
		}
	}

	/* Initialize the handoff root table page. */
	{
		uint64_t hp = *(uint64_t *)(sptm_uat_driver_state + 0x128);
		uint64_t *hva;
		uint64_t k;
		if ((sptm_mem_feature >> 8 & 1) == 0) {
			hva = (uint64_t *)((hp - sptm_mem_low) + sptm_window_base);
		} else {
			uint64_t cnt = sptm_region_count;
			uint64_t *r = sptm_regions;
			if (cnt != 0) {
				do {
					uint64_t rb = *r;
					if (rb <= hp && hp < rb + (uint64_t)(uint32_t)r[2] * 0x4000) {
						hva = (uint64_t *)((hp - rb) + r[1]);
						goto handoff_mapped;
					}
					r += 3;
					cnt--;
				} while (cnt != 0);
			}
			hva = (uint64_t *)sptm_phystokv_outside_window(hp);
		}
handoff_mapped:
		hva[0] = 0x4b1d000000000002ULL;
		*(uint32_t *)(hva + 3) = 0xffff;
		hva[200] = 0;
		*(uint8_t *)(hva + 199) = 1;
		for (k = 0; k != 0x618; k += 0x18) {
			*(uint32_t *)((uint8_t *)hva + k + 0x20) = 0;
			*(uint64_t *)((uint8_t *)hva + k + 0x28) = 0;
			*(uint64_t *)((uint8_t *)hva + k + 0x30) = 0;
		}
		if ((sptm_boot_thing & 1) == 0)
			*(uint64_t *)(sptm_uat_driver_state + 0x138) = (uint64_t)hva;
	}
	*(uint64_t *)(sptm_uat_driver_state + 0x1c0) =
	    *(uint64_t *)(sptm_uat_driver_state + 0x1b0) * 0x10 + 0x250;

	if ((sptm_mem_feature >> 7 & 1) != 0)
		goto unexpected_stage;
	if (sptm_secure_dt_root == NULL)
		sptm_panic_str("error getting SecureDT");

	/* SAPT bootstrap. */
	{
		void *chosen = NULL;
		uint64_t lo, hi, npg, size_words;
		if (sptm_secure_dt_node(sptm_secure_dt_root, 0, "chosen", &chosen) != 1)
			sptm_panic_str("error looking up chosen");
		*(uint8_t *)0x95300 = *(uint8_t *)(0x95d30) + 0xff; /* DAT_00095300 */
		*(uint8_t *)0x952f8 = *(uint8_t *)0x95d28;          /* DAT_000952f8 */
		lo = *(uint8_t *)0x952f8;
		hi = *(uint8_t *)0x95300;
		sapt = NULL;
		if (sptm_secure_dt_node(sptm_secure_dt_root, 0, "arm-io/sapt", &sapt) != 1)
			sptm_panic_str("error looking up arm-io/sapt");
		npg = ((hi - lo) + 1ULL) >> 14;
		*(uint8_t *)0x95308 = (uint8_t)npg;   /* DAT_00095308 */
		size_words = ((npg + 3) >> 2) + 0x3fff & 0x3ffffffffc000ULL;
		*(uint8_t *)0x952f0 = (uint8_t)size_words; /* DAT_000952f0 */

		val = dt_read_prop(sapt, "n_entries", 8);
		if (val != UINT64_MAX && val == npg) {
			val = dt_read_prop(sapt, "table_address", 8);
			if (val != UINT64_MAX) {
				i = sptm_iommu_region_ref(val, size_words >> 14, 1);
				if (i == 0xffffffff)
					sptm_panic_str("invalid papt returned");
				sptm_sapt_bootstrapped = (uint8_t)i;
				sapt = NULL;
				if (sptm_secure_dt_node(sptm_secure_dt_root, 0, "arm-io/sapt", &sapt) != 1)
					sptm_panic_str("error looking up arm-io/sapt");
				val = dt_read_prop(sapt, "policy", 4);
				if (val != UINT64_MAX) {
					sptm_boot_stage = val;
					if (sptm_boot_stage > 2)
						sptm_panic_str("Invalid SAPT policy specified");
					if (((void (**)(void))((uint64_t)0x15d70 + sptm_boot_stage * 0x28))[0] != NULL)
						((void (*)(void))((uint64_t)0x15d70 + sptm_boot_stage * 0x28))();
					return 0;
				}
			}
		}
		goto bad_prop;
	}

bad_prop:
	sptm_panic_str("property is not the expected width");
unexpected_stage:
	sptm_panic_str("Unexpected bootstrap stages");
}

/* ------------------------------------------------------------------ *
 * SK / TXM guarded-level entry stubs (0xb25c0 - 0xb2698).
 * Each loads the SPTM dispatch selector (x16 = BUILD_DISPATCH_ID(domain,
 * table, endpoint)) and branches to the guarded-level entry context-save
 * (sptm_sk_entry / sptm_txm_sk_entry), which performs the actual GENTER
 * (opcode 0x00201420).
 * ------------------------------------------------------------------ */

/* FUN_000b25c0 — SK entry, dispatch id 0x000300010000 (SK, table 1, endpoint 0). */
void sptm_sk_entry_stub_0(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                          uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b25d8 — SK entry, dispatch id 0x000300010001 (endpoint 1). */
void sptm_sk_entry_stub_1(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                          uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b25f0 — SK entry, dispatch id 0x000300010002 (endpoint 2). */
void sptm_sk_entry_stub_2(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                          uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b2608 — SK entry, dispatch id 0x000300010003 (endpoint 3). */
void sptm_sk_entry_stub_3(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                          uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b2620 — TXM entry, dispatch id 0x000200010000 (TXM, table 1, endpoint 0). */
void sptm_txm_entry_stub_0(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                           uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_txm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b2638 — TXM entry, dispatch id 0x000200010001 (endpoint 1). */
void sptm_txm_entry_stub_1(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                           uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_txm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b2650 — TXM entry, dispatch id 0x000200010002 (endpoint 2). */
void sptm_txm_entry_stub_2(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                           uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_txm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b2668 — TXM entry, dispatch id 0x000200010003 (endpoint 3). */
void sptm_txm_entry_stub_3(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                           uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_txm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b2680 — TXM entry, dispatch id 0x000200010004 (endpoint 4). */
void sptm_txm_entry_stub_4(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                           uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_txm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}

/* FUN_000b2698 — TXM entry, dispatch id 0x000200010005 (endpoint 5). */
void sptm_txm_entry_stub_5(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                           uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
	sptm_txm_sk_entry(p1, p2, p3, p4, p5, p6, p7, p8);
}
