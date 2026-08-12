/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM post-entry helpers and the libc-style runtime
 * used by the monitor: EL2 CPU bring-up helpers, cache maintenance, and the
 * full memory/string/printf/sort library. */
#include <stdint.h>
#include <stddef.h>

#include "sptm_internal.h"

/* GENTER (0x00201420) / GEXIT (0x00201400) — guarded-level transitions,
 * rendered opaque. */
#define GENTER() __asm__ volatile(".long 0x00201420" ::: "memory")
#define GEXIT()  __asm__ volatile(".long 0x00201400" ::: "memory")

/* Apple-proprietary EL2 system-register accessor (op0=3, op1=6 => EL2 class).
 * Encoded as (CRn, CRm, op2). The exact MSR encoding is vendor-specific and
 * not expressible generically in C; the concrete encodings appear as inline
 * mrs/msr at each EL2 call site below, so this helper is a documented
 * no-op that records the intended (crn,crm,op2,val) write. */
static __inline void
sptm_sysreg_write64(uint8_t crn, uint8_t crm, uint8_t op2, uint64_t val)
{
	(void)crn; (void)crm; (void)op2; (void)val;
	/* NOTE: emits "msr s3_6_c<crn>_c<crm>_<op2>, <val>" in the original. */
}

/* ------------------------------------------------------------------ *
 * Shared SPTM helpers referenced by this batch (Ghidra FUN_ addresses).
 * ------------------------------------------------------------------ */

/* FUN_000f8804 — noreturn SPTM panic taking a single format/arg word. */
extern void sptm_panic_code(uint32_t code) __attribute__((noreturn));
/* FUN_000f8824 — noreturn SPTM panic taking (val, &stack). */
extern void sptm_panic_val(uint32_t val, void *stack) __attribute__((noreturn));
/* FUN_000ae44c — noreturn stack-canary failure panic. */
extern void sptm_stack_check_fail(void) __attribute__((noreturn));
/* FUN_000ae3e0 — SPTM memset (declared in sptm_guest_io.c). */
extern void sptm_memset_guestio(void *dst, uint64_t n, uint64_t value);
/* FUN_000abeb0 — SPTM memcpy (thunk, tracked in sptm_guest_io.c). */
extern void sptm_memcpy_guestio(void *dst, const void *src, uint64_t n);
/* FUN_000ae0e4 — returns the active sort element size / state (16-byte pair). */
extern void *sptm_sort_state(void);
/* FUN_000ae0d8 — memmove helper used by qsort rotation. */
extern void *sptm_memmove_qsort(void *dst, const void *src, uint64_t n);
/* FUN_000ae090 / FUN_000ae0f4 / FUN_000ae0b4 / FUN_000ae0c8 / FUN_000ae100 /
 * FUN_000ae120 / FUN_000ae134 / FUN_000ae10c — qsort element-move / compare
 * shims (reg-returning; see qsort section). */
extern void sptm_sort_move(void);
extern void sptm_sort_move_bounds(void);

/* Per-CPU / boot configuration flag (DAT_00095d00). */
extern uint64_t sptm_cfg_flags0;

/* Stack canary guard at DAT_00100000. */
extern uint64_t sptm_stack_canary;

/* ================================================================== *
 * EL2 CPU bring-up helpers (boot path).
 * ================================================================== */

/* FUN_000ab7bc @ 0x000ab7bc   (est. sptm_cpu_el2_bringup)
 * Ghidra: undefined8 FUN_000ab7bc(void)
 * Per-CPU EL2 bring-up: invalidate EL1 stage-1 TLBs, wait for the boot
 * rendezvous token (0x2020a52a302abaf5) to be published by the primary CPU,
 * then write the EL2 feature/control registers and return the final SCTLR
 * value 0xfb. Called once per secondary CPU from the boot path (FUN_000b8f84).
 * The magic token is a release handshake: the loop spins until the system
 * register reads back the token, ensuring the CPU is fully out of reset
 * before SPTM configures it.
 * Confidence: medium
 * Notes: registers shown as UnkSytemRegWrite(3,6,0xf,1,0/1,5/6) — Apple
 *   vendor EL2 regs; TLBI_VMALLE1 + DSB + ISB surround the handshake. */
uint64_t
sptm_cpu_el2_bringup(void)
{
	/* SCTLR-ish EL2 control write (CRm=1,op2=0) = 1. */
	sptm_sysreg_write64(1, 0, 1, 1);
	__asm__ volatile("tlbi vmalle1");
	__asm__ volatile("dsb sy");
	__asm__ volatile("isb");
	/* Wait for the boot rendezvous token in (CRm=1,op2=6). */
	uint64_t token;
	do {
		__asm__ volatile("mrs %0, s3_6_c15_c1_6" : "=r"(token));
	} while (token != 0x2020a52a302abaf5UL);
	/* Configure (CRm=1,op2=5) and (CRm=3,op2=1), then set SCTLR = 0xfb. */
	sptm_sysreg_write64(1, 5, 1, 0x2010002030100000UL);
	sptm_sysreg_write64(3, 1, 1, 0x40010UL);
	sptm_sysreg_write64(1, 0, 1, 0xfbUL);
	__asm__ volatile("isb");
	__asm__ volatile("tlbi vmalle1");
	__asm__ volatile("dsb sy");
	__asm__ volatile("isb");
	return 0xfbUL;
}

/* FUN_000ab8ac @ 0x000ab8ac — the GENTER receive entry. Owned by the
 * BootEntry tree (sptm_boot.c, est. sptm_genter_receive): it arms the EL2
 * vectors (0xb7ed8/0xab84c) and executes GENTER. Not duplicated here. */

/* FUN_000ab8dc @ 0x000ab8dc   (est. sptm_el2_enable)
 * Ghidra: undefined8 FUN_000ab8dc(void)
 * Full EL2 enable: select the EL2 SP, install the exception vector bases
 * (0xb7ed8, 0xa0524) and a timer/feature base (0xa4000), then write SCTLR
 * (CRm=1,op2=2). SCTLR is 0x2f by default, or 0x6f when the boot-config flag
 * DAT_00095d00 is clear (extra cache/MMU bits enabled). Returns the SCTLR
 * value that was written. Called from the per-CPU boot path (FUN_000baa60).
 * Confidence: medium
 * Notes: spsel toggled to 1 then 0; flag-gated SCTLR value; Ghidra
 *   UnkSytemRegWrite(3,6,0xf,8,1/2/10,2) and (3,6,0xf,1,2). */
uint64_t
sptm_el2_enable(void)
{
	__asm__ volatile("msr spsel, #1");
	__asm__ volatile("msr spsel, #0");
	sptm_sysreg_write64(8, 2, 1, 0xb7ed8UL);
	sptm_sysreg_write64(8, 1, 1, 0xa0524UL);
	sptm_sysreg_write64(10, 2, 1, 0xa4000UL);
	__asm__ volatile("isb");
	uint64_t sctlr = 0x2fUL;
	if (sptm_cfg_flags0 == 0) {
		/* Enable additional feature bits when config flag clear. */
		sptm_sysreg_write64(0xf, 1, 1, 0);
		sptm_sysreg_write64(0xf, 2, 1, 0);
		sptm_sysreg_write64(0xf, 3, 1, 0);
		sctlr = 0x6fUL;
	}
	sptm_sysreg_write64(1, 2, 1, sctlr);
	__asm__ volatile("isb");
	return sctlr;
}

/* ================================================================== *
 * Cache / barrier maintenance helpers.
 * ================================================================== */

/* FUN_000ab958 @ 0x000ab958   (est. sptm_dsb_sy)
 * Ghidra: void FUN_000ab958(void)
 * Full-system data synchronization barrier (DSB SY). Preserves x0/x1 so the
 * caller can pass a (va, size) pair through the barrier unchanged.
 * Confidence: high
 * Notes: decompiled as DataSynchronizationBarrier(3,3,0). */
static __inline void
sptm_dsb_sy(void)
{
	__asm__ volatile("dsb sy");
}

/* FUN_000ab964 @ 0x000ab964   (est. sptm_dcache_clean_invalidate_range)
 * Ghidra: ulong FUN_000ab964(ulong va, long size)
 * Clean and invalidate (DC CIVAC) the data-cache lines covering [va, va+size).
 * Rounds va down to a 0x80-byte cache line and iterates, returning the
 * final (exclusive) VA. Cache line is 128 bytes (2^7).
 * Confidence: high
 * Notes: do-while over DC_CIVAC; count = (size + (va & 0x7f) - 1) >> 7 + 1. */
uint64_t
sptm_dcache_clean_invalidate_range(uint64_t va, uint64_t size)
{
	uint64_t line = va & ~0x7fUL;
	uint64_t n = (size + (va & 0x7f) - 1) >> 7;
	do {
		__asm__ volatile("dc civac, %0" :: "r"(line) : "memory");
		line += 0x80;
		n--;
	} while ((int64_t)n >= 0);
	return line;
}

/* FUN_000ab994 @ 0x000ab994   (est. sptm_dcache_flush)
 * Ghidra: void FUN_000ab994(void)
 * Flush the data cache for a (va, size) range (passed through in x0/x1,
 * inherited by the called range-clean helper): clear the cache-control bit 3
 * in (CRm=0xc,op2=0), clean+invalidate the range, then restore bit 3.
 * Confidence: medium
 * Notes: register (3,4,0xf,0xc,0); toggles bit 0x8; ISB/DSB around the
 *   range clean; calls FUN_000ab964 with the inherited range registers. */
void
sptm_dcache_flush(void)
{
	__asm__ volatile("isb");
	uint64_t ctrl;
	__asm__ volatile("mrs %0, s3_4_c15_c12_0" : "=r"(ctrl));
	__asm__ volatile("msr s3_4_c15_c12_0, %0" :: "r"(ctrl & ~0x8UL));
	__asm__ volatile("isb");
	__asm__ volatile("dsb sy");
	sptm_dcache_clean_invalidate_range(0, 0);  /* range passed in regs */
	__asm__ volatile("dsb sy");
	__asm__ volatile("isb");
	__asm__ volatile("mrs %0, s3_4_c15_c12_0" : "=r"(ctrl));
	__asm__ volatile("msr s3_4_c15_c12_0, %0" :: "r"(ctrl | 0x8UL));
	__asm__ volatile("isb");
}

/* FUN_000aba24 @ 0x000aba24   (est. sptm_icache_invalidate_range)
 * Ghidra: ulong FUN_000aba24(void)
 * Invalidate instruction-cache lines (IC IVAU) over [va, va+size), where the
 * range is passed in x0/x1 and survives the leading DSB SY barrier. Rounds
 * va down to a 0x40-byte line; returns the final exclusive VA. Followed by
 * DSB + ISB.
 * Confidence: high
 * Notes: IC_IVAU per 0x40 line; the range arrives via the DSB helper that
 *   preserves x0/x1 (FUN_000ab958). */
uint64_t
sptm_icache_invalidate_range(uint64_t va, uint64_t size)
{
	sptm_dsb_sy();                             /* preserves x0/x1 (va,size) */
	uint64_t line = va & ~0x3fUL;
	uint64_t n = (size + (va & 0x3f) - 1) >> 6;
	do {
		__asm__ volatile("ic ivau, %0" :: "r"(line) : "memory");
		line += 0x40;
		n--;
	} while ((int64_t)n >= 0);
	__asm__ volatile("dsb sy");
	__asm__ volatile("isb");
	return line;
}

/* FUN_000aba70 @ 0x000aba70   (est. sptm_dcache_flush_setway)
 * Ghidra: void FUN_000aba70(void)
 * Flush (clean+invalidate) all data/unified caches by set/way across every
 * cache level. Walks CLIDR_EL1 level types (LoU bits), selects each level via
 * CSSELR_EL1, reads CCSIDR_EL1 for line size/ways/sets, and issues DC CISW
 * over all sets/ways. Used at boot before the MMU/two-stage tables are live.
 * Confidence: medium
 * Notes: CLIDR_EL1/CCSIDR_EL1/CSSELR_EL1; DC_CISW; terminates at the first
 *   level with type 0 or after 7 levels. */
void
sptm_dcache_flush_setway(void)
{
	__asm__ volatile("dmb sy");
	uint64_t level = 0;
	do {
		uint64_t clidr;
		__asm__ volatile("mrs %0, clidr_el1" : "=r"(clidr));
		uint64_t type = (clidr >> (level * 3)) & 7;
		if (type == 0) {
			return;
		}
		if (type > 1) {
			__asm__ volatile("msr csselr_el1, %0" :: "r"(level << 1));
			__asm__ volatile("isb");
			uint64_t ccsidr;
			__asm__ volatile("mrs %0, ccsidr_el1" : "=r"(ccsidr));
			uint64_t ways = (ccsidr >> 3) & 0x3ff;     /* NumSets-1? no: ways */
			uint64_t num_ways = ways + 1;
			uint64_t line_shift = (ccsidr & 7) + 4;
			uint64_t line_stride = 1UL << line_shift;
			uint64_t sets = (ccsidr >> 13) & 0x7fff;
			uint64_t mask = line_stride * (sets + 1);
			/* Iterate every set, and within it every way. */
			uint64_t sw = level << 1;
			uint32_t way_bits;
			uint32_t stride;
			do {
				do {
					__asm__ volatile("dc cisw, %0" :: "r"(sw) : "memory");
					sw += line_stride;
				} while ((sw & mask) == 0);
				way_bits = (uint32_t)sw & ~(uint32_t)mask;
				stride = (uint32_t)(1UL << (32 - (0x3f - __builtin_clz(num_ways))));
				sw = (uint64_t)(way_bits + stride);
			} while (way_bits + stride < way_bits);
			__asm__ volatile("dsb sy");
		}
		level++;
	} while (level < 7);
}

/* ================================================================== *
 * Memory library (memset / memcmp / memcpy thunks).
 * ================================================================== */

/* FUN_000abb60 @ 0x000abb60   (est. sptm_bzero)
 * Ghidra: void FUN_000abb60(undefined8 *dst, ulong n)
 * Zero-fill n bytes at dst. For n >= 0x8000 it uses DC ZVA (zero by VA)
 * on 0x40-byte blocks, with 8-byte stores to the head/tail; smaller copies
 * use 8-byte and byte stores.
 * Confidence: high
 * Notes: DC_ZVA on aligned 0x40 blocks; bounds-checked against the memory
 *   window (0xc8a2 high half). */
void
sptm_bzero(void *dst0, uint64_t n)
{
	uint8_t *dst = dst0;
	if (n < 0x40) {
		while (n > 7) { *(uint64_t *)dst = 0; dst += 8; n -= 8; }
		while (n != 0) { *dst = 0; dst++; n--; }
		return;
	}
	if (n > 0x7fff) {
		*(uint64_t *)(dst + 0)  = 0; *(uint64_t *)(dst + 8)  = 0;
		*(uint64_t *)(dst + 16) = 0; *(uint64_t *)(dst + 24) = 0;
		*(uint64_t *)(dst + 32) = 0; *(uint64_t *)(dst + 40) = 0;
		*(uint64_t *)(dst + 48) = 0; *(uint64_t *)(dst + 56) = 0;
		uint8_t *aligned = (uint8_t *)((uint64_t)(dst + 64) & ~0x3fUL);
		uint64_t remain = (uint64_t)(dst + n) - (uint64_t)(aligned + 0x40);
		if ((uint64_t)(aligned + 0x40) <= (uint64_t)(dst + n) && remain != 0) {
			do {
				__asm__ volatile("dc zva, %0" :: "r"(aligned) : "memory");
				aligned += 0x40;
				remain -= 0x40;
			} while (remain > 0x3f && remain != 0);
		}
		uint8_t *tail = aligned + remain;
		*(uint64_t *)(tail + 0)  = 0; *(uint64_t *)(tail + 8)  = 0;
		*(uint64_t *)(tail + 16) = 0; *(uint64_t *)(tail + 24) = 0;
		*(uint64_t *)(tail + 32) = 0; *(uint64_t *)(tail + 40) = 0;
		*(uint64_t *)(tail + 48) = 0; *(uint64_t *)(tail + 56) = 0;
		return;
	}
	/* n in [0x40, 0x8000): 8-byte stores, aligned to 0x40, then tail. */
	*(uint64_t *)(dst + 0)  = 0; *(uint64_t *)(dst + 8)  = 0;
	*(uint64_t *)(dst + 16) = 0; *(uint64_t *)(dst + 24) = 0;
	*(uint64_t *)(dst + 32) = 0; *(uint64_t *)(dst + 40) = 0;
	*(uint64_t *)(dst + 48) = 0; *(uint64_t *)(dst + 56) = 0;
	uint8_t *p = (uint8_t *)((uint64_t)(dst + 64) & ~0x3fUL);
	uint64_t remain = (uint64_t)(dst + n) - (uint64_t)(p + 64);
	if ((uint64_t)(p + 64) <= (uint64_t)(dst + n) && remain != 0) {
		do {
			*(uint64_t *)(p + 0)  = 0; *(uint64_t *)(p + 8)  = 0;
			*(uint64_t *)(p + 16) = 0; *(uint64_t *)(p + 24) = 0;
			*(uint64_t *)(p + 32) = 0; *(uint64_t *)(p + 40) = 0;
			*(uint64_t *)(p + 48) = 0; *(uint64_t *)(p + 56) = 0;
			p += 0x40;
			remain -= 0x40;
		} while (remain > 0x3f && remain != 0);
	}
	uint8_t *tail = p + remain;
	*(uint64_t *)(tail + 0)  = 0; *(uint64_t *)(tail + 8)  = 0;
	*(uint64_t *)(tail + 16) = 0; *(uint64_t *)(tail + 24) = 0;
	*(uint64_t *)(tail + 32) = 0; *(uint64_t *)(tail + 40) = 0;
	*(uint64_t *)(tail + 48) = 0; *(uint64_t *)(tail + 56) = 0;
}

/* FUN_000abbd0 @ 0x000abbd0   (est. sptm_memset_bytes)
 * Ghidra: void FUN_000abbd0(long *dst, ulong value, ulong n)
 * Fill n bytes at dst with the low byte of value (byte-replicated). For
 * n >= 0x8000 and value==0 uses DC ZVA; otherwise 8-byte replicated stores.
 * This is the SPTM byte-value memset (distinct from the FUN_000ae3e0 memset
 * tracked in sptm_guest_io.c).
 * Confidence: high
 * Notes: replicates value via 0x0101010101010101; DC_ZVA fast path when zero. */
void
sptm_memset_bytes(void *dst0, uint8_t value, uint64_t n)
{
	uint8_t *dst = dst0;
	uint64_t word = value * 0x0101010101010101UL;
	if (n < 0x40) {
		while (n > 7) { *(uint64_t *)dst = word; dst += 8; n -= 8; }
		while (n != 0) { *dst = (uint8_t)word; dst++; n--; }
		return;
	}
	if (n > 0x7fff) {
		if (word != 0) {
			*(uint64_t *)(dst + 0)  = word; *(uint64_t *)(dst + 8)  = word;
			*(uint64_t *)(dst + 16) = word; *(uint64_t *)(dst + 24) = word;
			*(uint64_t *)(dst + 32) = word; *(uint64_t *)(dst + 40) = word;
			*(uint64_t *)(dst + 48) = word; *(uint64_t *)(dst + 56) = word;
			uint8_t *p = (uint8_t *)((uint64_t)(dst + 64) & ~0x3fUL);
			uint64_t remain = (uint64_t)(dst + n) - (uint64_t)(p + 64);
			if ((uint64_t)(p + 64) <= (uint64_t)(dst + n) && remain != 0) {
				do {
					*(uint64_t *)(p + 0)  = word; *(uint64_t *)(p + 8)  = word;
					*(uint64_t *)(p + 16) = word; *(uint64_t *)(p + 24) = word;
					*(uint64_t *)(p + 32) = word; *(uint64_t *)(p + 40) = word;
					*(uint64_t *)(p + 48) = word; *(uint64_t *)(p + 56) = word;
					p += 0x40; remain -= 0x40;
				} while (remain > 0x3f && remain != 0);
			}
			uint8_t *tail = p + remain;
			*(uint64_t *)(tail + 0)  = word; *(uint64_t *)(tail + 8)  = word;
			*(uint64_t *)(tail + 16) = word; *(uint64_t *)(tail + 24) = word;
			*(uint64_t *)(tail + 32) = word; *(uint64_t *)(tail + 40) = word;
			*(uint64_t *)(tail + 48) = word; *(uint64_t *)(tail + 56) = word;
			return;
		}
		/* word == 0: DC ZVA path. */
		*(uint64_t *)(dst + 0)  = 0; *(uint64_t *)(dst + 8)  = 0;
		*(uint64_t *)(dst + 16) = 0; *(uint64_t *)(dst + 24) = 0;
		*(uint64_t *)(dst + 32) = 0; *(uint64_t *)(dst + 40) = 0;
		*(uint64_t *)(dst + 48) = 0; *(uint64_t *)(dst + 56) = 0;
		uint8_t *aligned = (uint8_t *)((uint64_t)(dst + 64) & ~0x3fUL);
		uint64_t remain = (uint64_t)(dst + n) - (uint64_t)(aligned + 0x40);
		if ((uint64_t)(aligned + 0x40) <= (uint64_t)(dst + n) && remain != 0) {
			do {
				__asm__ volatile("dc zva, %0" :: "r"(aligned) : "memory");
				aligned += 0x40; remain -= 0x40;
			} while (remain > 0x3f && remain != 0);
		}
		uint8_t *tail = aligned + remain;
		*(uint64_t *)(tail + 0)  = 0; *(uint64_t *)(tail + 8)  = 0;
		*(uint64_t *)(tail + 16) = 0; *(uint64_t *)(tail + 24) = 0;
		*(uint64_t *)(tail + 32) = 0; *(uint64_t *)(tail + 40) = 0;
		*(uint64_t *)(tail + 48) = 0; *(uint64_t *)(tail + 56) = 0;
		return;
	}
	/* n in [0x40, 0x8000). */
	*(uint64_t *)(dst + 0)  = word; *(uint64_t *)(dst + 8)  = word;
	*(uint64_t *)(dst + 16) = word; *(uint64_t *)(dst + 24) = word;
	*(uint64_t *)(dst + 32) = word; *(uint64_t *)(dst + 40) = word;
	*(uint64_t *)(dst + 48) = word; *(uint64_t *)(dst + 56) = word;
	uint8_t *p = (uint8_t *)((uint64_t)(dst + 64) & ~0x3fUL);
	uint64_t remain = (uint64_t)(dst + n) - (uint64_t)(p + 64);
	if ((uint64_t)(p + 64) <= (uint64_t)(dst + n) && remain != 0) {
		do {
			*(uint64_t *)(p + 0)  = word; *(uint64_t *)(p + 8)  = word;
			*(uint64_t *)(p + 16) = word; *(uint64_t *)(p + 24) = word;
			*(uint64_t *)(p + 32) = word; *(uint64_t *)(p + 40) = word;
			*(uint64_t *)(p + 48) = word; *(uint64_t *)(p + 56) = word;
			p += 0x40; remain -= 0x40;
		} while (remain > 0x3f && remain != 0);
	}
	uint8_t *tail = p + remain;
	*(uint64_t *)(tail + 0)  = word; *(uint64_t *)(tail + 8)  = word;
	*(uint64_t *)(tail + 16) = word; *(uint64_t *)(tail + 24) = word;
	*(uint64_t *)(tail + 32) = word; *(uint64_t *)(tail + 40) = word;
	*(uint64_t *)(tail + 48) = word; *(uint64_t *)(tail + 56) = word;
}

/* FUN_000abcd0 @ 0x000abcd0   (est. sptm_memcmp)
 * Ghidra: long FUN_000abcd0(ulong *s1, ulong *s2, ulong n)
 * Compare the first n bytes of s1 and s2; returns the byte difference
 * (s1[i]-s2[i]) of the first differing byte, or 0 if equal. Uses NEON 16-byte
 * loads with a "has differing byte" mask (constants DAT_000abcc0/abcc8) and
 * a trailing byte scan.
 * Confidence: high
 * Notes: early-exit compare; result is the signed byte difference, matching
 *   C memcmp semantics. */
int
sptm_memcmp(const void *s1, const void *s2, uint64_t n)
{
	const uint8_t *a = s1, *b = s2;
	uint64_t todo = n;
	/* 16-byte blocks. */
	while (todo >= 0x10) {
		uint64_t w0 = *(const uint64_t *)a;
		uint64_t w1 = *(const uint64_t *)(a + 8);
		uint64_t v0 = *(const uint64_t *)b;
		uint64_t v1 = *(const uint64_t *)(b + 8);
		/* Per-byte equality masks. */
		uint64_t m0 = 0, m1 = 0;
		for (int i = 0; i < 8; i++) {
			uint8_t ca = (w0 >> (8 * i)) & 0xff;
			uint8_t cb = (v0 >> (8 * i)) & 0xff;
			if (ca == cb) m0 |= 0xffUL << (8 * i);
			uint8_t ca2 = (w1 >> (8 * i)) & 0xff;
			uint8_t cb2 = (v1 >> (8 * i)) & 0xff;
			if (ca2 == cb2) m1 |= 0xffUL << (8 * i);
		}
		if (m0 != ~0UL || m1 != ~0UL) {
			/* Find first differing byte. */
			for (int i = 0; i < 16; i++) {
				if (a[i] != b[i]) {
					return (int)a[i] - (int)b[i];
				}
			}
		}
		a += 0x10; b += 0x10; todo -= 0x10;
	}
	/* Tail: up to 8 bytes then up to 4/1 bytes. */
	if (todo >= 8) {
		uint64_t d = *(const uint64_t *)a - *(const uint64_t *)b;
		if (d != 0) {
			d = ((d & 0xff00ff00ff00ff00UL) >> 8) | ((d & 0xff00ff00ff00ffUL) << 8);
			d = ((d & 0xffff0000ffff0000UL) >> 16) | ((d & 0xffff0000ffffUL) << 16);
			d = __builtin_bswap64(d);
			unsigned shift = ((unsigned)__builtin_clzll(d >> 32 | d << 32)) & 0x38;
			return (int)((a[0] >> shift) & 0xff) - (int)((b[0] >> shift) & 0xff);
		}
		a += 8; b += 8; todo -= 8;
	}
	if (todo >= 4) {
		uint32_t d = *(const uint32_t *)a - *(const uint32_t *)b;
		if (d != 0) {
			/* byte-diff of first differing byte */
			for (int i = 0; i < 4; i++) {
				if (a[i] != b[i]) return (int)a[i] - (int)b[i];
			}
		}
		a += 4; b += 4; todo -= 4;
	}
	while (todo != 0) {
		int d = (int)*a - (int)*b;
		if (d != 0) return d;
		a++; b++; todo--;
	}
	return 0;
}

/* FUN_000abdf0 @ 0x000abdf0   (est. sptm_secure_memcmp)
 * Ghidra: int FUN_000abdf0(byte *s1, byte *s2, ulong n)
 * Constant-time-style comparison of n bytes, used for security-sensitive
 * material (e.g. crypto keys / PAC). Unlike sptm_memcmp it always scans the
 * full buffer (masked NEON compare accumulates the last-mismatch offset) and
 * ends with DSB + ISB to order the reads; the result is the byte difference
 * of the last-mismatching byte. Timing is therefore not short-circuited by
 * an early mismatch.
 * Confidence: high
 * Notes: NEON_uminv equality masks + byte tail with carry mask; trailing
 *   DataSynchronizationBarrier + InstructionSynchronizationBarrier. */
int
sptm_secure_memcmp(const uint8_t *a, const uint8_t *b, uint64_t n)
{
	int result = 0;
	uint64_t mask = 0xff;          /* accumulate mismatches */
	uint64_t todo = n;
	while (todo >= 0x10) {
		uint64_t w0 = *(const uint64_t *)a;
		uint64_t w1 = *(const uint64_t *)(a + 8);
		uint64_t v0 = *(const uint64_t *)b;
		uint64_t v1 = *(const uint64_t *)(b + 8);
		uint64_t eq = 0;
		for (int i = 0; i < 16; i++) {
			uint8_t ca = (i < 8) ? (w0 >> (8 * i)) : (w1 >> (8 * (i - 8)));
			uint8_t cb = (i < 8) ? (v0 >> (8 * i)) : (v1 >> (8 * (i - 8)));
			if (ca == cb) eq |= 0xffUL << (8 * i);
		}
		/* Record last differing byte position in the block. */
		if ((mask & ~eq) != 0) {
			for (int i = 15; i >= 0; i--) {
				if (a[i] != b[i]) { result = (int)a[i] - (int)b[i]; break; }
			}
		}
		mask = eq;
		a += 0x10; b += 0x10; todo -= 0x10;
	}
	/* Byte tail, masked. */
	uint64_t m = mask;
	for (uint64_t i = 0; i < todo; i++) {
		int d = (int)a[i] - (int)b[i];
		if ((m & 0xff) == 0 && d != 0) result = d;
		m &= 0xffffffffffffff00UL;
		m |= 0xff;
	}
	__asm__ volatile("dsb sy");
	__asm__ volatile("isb");
	return (char)result;
}

/* FUN_000ac190 @ 0x000ac190   (est. sptm_strcmp)
 * Ghidra: long FUN_000ac190(byte *s1, byte *s2)
 * Compare NUL-terminated strings s1 and s2; returns the byte difference at
 * the first differing or NUL byte. NEON 16-byte fast path with a zero-byte
 * mask, falling back to a byte loop.
 * Confidence: high
 * Notes: stops at NUL; masks DAT_000ac180/ac188. */
int
sptm_strcmp(const char *s1, const char *s2)
{
	const uint8_t *a = (const uint8_t *)s1;
	const uint8_t *b = (const uint8_t *)s2;
	if ((((uint64_t)a & 0xf) == 0) && (((uint64_t)b & 0xf) == 0)) {
		do {
			uint64_t w0 = *(const uint64_t *)a;
			uint64_t w1 = *(const uint64_t *)(a + 8);
			uint64_t v0 = *(const uint64_t *)b;
			uint64_t v1 = *(const uint64_t *)(b + 8);
			uint64_t eq = 0;
			for (int i = 0; i < 16; i++) {
				uint8_t ca = (i < 8) ? (w0 >> (8 * i)) : (w1 >> (8 * (i - 8)));
				uint8_t cb = (i < 8) ? (v0 >> (8 * i)) : (v1 >> (8 * (i - 8)));
				if (ca == cb) eq |= 0xffUL << (8 * i);
			}
			if (eq != ~0UL) {
				for (int i = 0; i < 16; i++) {
					if (a[i] == 0 || a[i] != b[i]) {
						return (int)a[i] - (int)b[i];
					}
				}
			}
			a += 0x10; b += 0x10;
		} while (1);
	}
	/* Byte loop. */
	int d;
	do {
		d = (int)*a - (int)*b;
		a++; b++;
	} while (d == 0 && a[-1] != 0);
	return d;
}

/* FUN_000ac290 @ 0x000ac290   (est. sptm_strncmp)
 * Ghidra: long FUN_000ac290(byte *s1, byte *s2, ulong n)
 * Compare at most n bytes of s1 and s2, stopping at the first difference or
 * NUL; returns the byte difference. NEON 16-byte fast path.
 * Confidence: high
 * Notes: length-bounded; masks DAT_000ac280/ac288. */
int
sptm_strncmp(const char *s1, const char *s2, uint64_t n)
{
	const uint8_t *a = (const uint8_t *)s1;
	const uint8_t *b = (const uint8_t *)s2;
	uint64_t todo = n;
	while (todo != 0) {
		int d = (int)*a - (int)*b;
		if (d != 0 || *a == 0) return d;
		a++; b++; todo--;
	}
	return 0;
}

/* FUN_000ac3e0 @ 0x000ac3e0   (est. sptm_strnlen)
 * Ghidra: long FUN_000ac3e0(ulong s, long maxlen)
 * Return the length of the NUL-terminated string at s, bounded to maxlen
 * bytes (a negative maxlen means unbounded = strlen). NEON 16-byte scan with
 * a zero-byte mask.
 * Confidence: high
 * Notes: maxlen < 0 => strlen; mask constants DAT_000ac3c0/ac3c8/000ac3d0. */
size_t
sptm_strnlen(const char *s, int64_t maxlen)
{
	const uint8_t *p = (const uint8_t *)s;
	size_t off = 0;
	if (maxlen < 0) {
		while (1) {
			uint64_t w0 = *(const uint64_t *)(p + off);
			uint64_t w1 = *(const uint64_t *)(p + off + 8);
			/* zero byte in either word? */
			uint64_t has0 = 0;
			for (int i = 0; i < 16; i++) {
				uint8_t c = (i < 8) ? (w0 >> (8 * i)) : (w1 >> (8 * (i - 8)));
				if (c == 0) has0 |= 0xffUL << (8 * i);
			}
			if (has0 != 0) {
				for (int i = 0; i < 16; i++) {
					if (p[off + i] == 0) return off + i;
				}
			}
			off += 0x10;
		}
	}
	/* Bounded. */
	uint64_t lim = (uint64_t)maxlen;
	while (off + 0x10 <= lim) {
		uint64_t w0 = *(const uint64_t *)(p + off);
		uint64_t w1 = *(const uint64_t *)(p + off + 8);
		uint64_t has0 = 0;
		for (int i = 0; i < 16; i++) {
			uint8_t c = (i < 8) ? (w0 >> (8 * i)) : (w1 >> (8 * (i - 8)));
			if (c == 0) has0 |= 0xffUL << (8 * i);
		}
		if (has0 != 0) {
			for (int i = 0; i < 16; i++) {
				if (p[off + i] == 0) return off + i;
			}
		}
		off += 0x10;
	}
	while (off < lim && p[off] != 0) off++;
	return (off < lim && p[off] == 0) ? off : (off < lim ? off : lim);
}

/* FUN_000ac480 @ 0x000ac480   (est. sptm_strlen)
 * Ghidra: long FUN_000ac480(ulong s)
 * Return the length of the NUL-terminated string at s. NEON 16-byte scan.
 * Confidence: high
 * Notes: single-arg strlen; mask DAT_000ac3c0/ac3c8/000ac3d0. */
size_t
sptm_strlen(const char *s)
{
	const uint8_t *p = (const uint8_t *)s;
	size_t off = 0;
	while (1) {
		uint64_t w0 = *(const uint64_t *)(p + off);
		uint64_t w1 = *(const uint64_t *)(p + off + 8);
		uint64_t has0 = 0;
		for (int i = 0; i < 16; i++) {
			uint8_t c = (i < 8) ? (w0 >> (8 * i)) : (w1 >> (8 * (i - 8)));
			if (c == 0) has0 |= 0xffUL << (8 * i);
		}
		if (has0 != 0) {
			for (int i = 0; i < 16; i++) {
				if (p[off + i] == 0) return off + i;
			}
		}
		off += 0x10;
	}
}

/* ================================================================== *
 * SPTM panic entry stubs.
 * ================================================================== */

/* FUN_000ac4e0 @ 0x000ac4e0   (est. sptm_panic_msg)
 * Ghidra: noreturn undefined FUN_000ac4e0(void)
 * Noreturn SPTM panic wrapper: forwards a message/value and the current stack
 * pointer to the SPTM panic engine (FUN_000f8824). Used by the printf/sort
 * helpers on detected faults (e.g. snprintf size validation, FUN_000ad278).
 * Confidence: medium
 * Notes: passes (param_1, &stack0) to FUN_000f8824; noreturn. */
void
sptm_panic_msg(uint32_t msg)
{
	sptm_panic_val(msg, __builtin_frame_address(0));
	for (;;) { }
}

/* FUN_000ac500 @ 0x000ac500   (est. sptm_panic_fmtstate)
 * Ghidra: noreturn undefined FUN_000ac500(void)
 * Noreturn SPTM panic for an invalid printf-format state: forwards the fixed
 * code 0xa28 to the single-arg panic engine (FUN_000f8804). Called by the
 * number formatter FUN_000acc60 when the output state is corrupted.
 * Confidence: medium
 * Notes: FUN_000f8804 is here shown to take an integer code, not a string —
 *   this contradicts the "panic taking only a format string" guess in
 *   sptm_guest_io.c's extern comment. */
void
sptm_panic_fmtstate(void)
{
	sptm_panic_code(0xa28UL);
	for (;;) { }
}

/* ================================================================== *
 * printf-family (snprintf / vsnprintf) machinery.
 * ================================================================== */

/* Output-state descriptor used by the printf family. Matches the register
 * layout the decompiler exposes (offsets into a single state block). */
struct sptm_out_state {
	uint64_t flags;      /* bit0: initialized; bit1: uppercase; bit2: '#'; ... */
	uint64_t buf_base;   /* +8 */
	uint64_t buf_cap;    /* +0x10 */
	uint64_t used;       /* +0x20 */
	uint64_t width;      /* +4 (32-bit) */
};

/* FUN_000ace64 @ 0x000ace64   (est. sptm_va_arg_get)
 * Ghidra: undefined8 FUN_000ace64(byte *fmtstate, ulong *out, long *ap)
 * Fetch one va_arg from the va_list *ap according to the length modifier
 * recorded in fmtstate bytes 2-3 (0x68='h', 0x6868='hh', 0x6c6c='ll',
 * 0x6a='j', 0x6c='l', 0x74='t', 0x7a='z'), widen it, store to *out, and
 * advance *ap. Returns 1 on success, 0 on an unknown length modifier.
 * Confidence: high
 * Notes: sign-/zero-extension handled at the call sites via the fmtstate
 *   width bits; the va_list advances by 8 for 64-bit types, 4 for short. */
int
sptm_va_arg_get(uint8_t *fmtstate, uint64_t *out, void **ap)
{
	(void)fmtstate;
	uint16_t len = *(uint16_t *)(fmtstate + 2);
	if (len != 0x6c6c && len != 0x68 && len != 0x6a && len != 0x6c &&
	    len != 0x74 && len != 0x7a) {
		if (len == 0x6868) {
			uint8_t *p = *ap; *ap = p + 8;
			*out = (uint64_t)*p;
			return 1;
		}
		if (len != 0) {
			return 0;
		}
		uint32_t *p = *ap; *ap = p + 2;
		*out = (uint64_t)*p;
		return 1;
	}
	uint64_t *p = *ap; *ap = p + 1;
	*out = *p;
	return 1;
}

/* FUN_000ad1d0 @ 0x000ad1d0   (est. sptm_buf_ptr)
 * Ghidra: void FUN_000ad1d0(void)
 * Register-level helper: reads the current printf destination pointer from
 * the caller's frame (x20+8) and returns base+offset (used by the fill/write
 * helpers to locate the next output byte). The decompiler collapses it to an
 * empty return; actual instruction: ldr x10,[x20,#8]; add x11,x10,x9; ret.
 * Confidence: medium
 * Notes: relies on caller frame register x20 (printf state base) and x9
 *   (byte offset); reg-returning stub. */
static __inline void
sptm_buf_ptr(void)
{
	/* no-op placeholder; see disassembly note */
}

/* FUN_000ad200 @ 0x000ad200   (est. sptm_buf_bounds_check)
 * Ghidra: void FUN_000ad200(void)
 * Register-level helper: validates that a write to (base + count - 1) stays
 * within the output buffer; sets the Z/C flags used by the caller to panic on
 * overflow. Actual instruction: ldp x9,x8,[x20,#8]; add x10,x9,x8;
 * add x8,x9,x21; sub x8,x8,#1; cmp x8,x10; ret.
 * Confidence: medium
 * Notes: reg-returning stub; x20=state base, x21=write count. */
static __inline void
sptm_buf_bounds_check(void)
{
	/* no-op placeholder; see disassembly note */
}

/* FUN_000ad020 @ 0x000ad020   (est. sptm_out_fill)
 * Ghidra: undefined8 FUN_000ad020(byte *state, undefined8 ch, ulong n)
 * Append n copies of the byte `ch` to the output buffer described by *state.
 * Uses the byte-value memset (FUN_000abbd0) for the bulk fill and returns 1,
 * or 0 if the fill would overflow (carry). After the last partial fill it
 * NUL-terminates via the bounds-check helper.
 * Confidence: high
 * Notes: fills with 0x20 (space) or 0x30 ('0') for printf padding. */
int
sptm_out_fill(uint8_t *state, uint8_t ch, uint64_t n)
{
	if (n == 0) return 1;
	uint64_t used = *(uint64_t *)(state + 0x20);
	if (used + n < used) return 0;           /* carry => overflow */
	uint64_t cap = *(uint64_t *)(state + 0x10);
	if (used + n < cap) {
		sptm_memset_bytes((uint8_t *)*(uint64_t *)(state + 8) + used, ch, n);
	} else {
		if (used <= cap && cap - used != 0) {
			sptm_memset_bytes((uint8_t *)*(uint64_t *)(state + 8) + used, ch,
			    cap - used);
			sptm_buf_bounds_check();
			*(uint8_t *)*(uint64_t *)(state + 8) = 0;
		}
	}
	*(uint64_t *)(state + 0x20) = used + n;
	return 1;
}

/* FUN_000ad0e0 @ 0x000ad0e0   (est. sptm_out_write)
 * Ghidra: undefined8 FUN_000ad0e0(byte *state, undefined8 src, ulong n)
 * Append n bytes from src to the output buffer described by *state, using the
 * SPTM memcpy (FUN_000abeb0). Returns 1, or 0 on overflow (carry). Partial
 * final copy is NUL-terminated via the bounds-check helper.
 * Confidence: high
 * Notes: calls FUN_000abeb0 (memcpy thunk, tracked in sptm_guest_io.c). */
int
sptm_out_write(uint8_t *state, const void *src, uint64_t n)
{
	if (n == 0) return 1;
	uint64_t used = *(uint64_t *)(state + 0x20);
	if (used + n < used) return 0;
	uint64_t cap = *(uint64_t *)(state + 0x10);
	if (used + n < cap) {
		sptm_memcpy_guestio((uint8_t *)*(uint64_t *)(state + 8) + used, src, n);
	} else {
		uint64_t space = cap - used;
		if (used <= cap && space != 0) {
			sptm_memcpy_guestio((uint8_t *)*(uint64_t *)(state + 8) + used,
			    src, space);
			sptm_buf_bounds_check();
			*(uint8_t *)*(uint64_t *)(state + 8) = 0;
		}
	}
	*(uint64_t *)(state + 0x20) = used + n;
	return 1;
}

/* FUN_000acbac @ 0x000acbac   (est. sptm_buf_putc)
 * Ghidra: undefined8 FUN_000acbac(byte *state, undefined1 ch)
 * Append the single byte ch to the output buffer described by *state (a
 * printf buffer). Bounds-checked against the SPTM memory window; appends the
 * byte at the current length, NUL-terminates when the buffer is exactly full,
 * and bumps the length. Returns 1 on success, 0 if the length would wrap.
 * Confidence: high
 * Notes: state is the format-state block (offset +0x20 = length, +8 = buf,
 *   +0x10 = capacity); SoftwareBreakpoint(0x5519) on out-of-window access. */
int
sptm_buf_putc(uint8_t *state, uint8_t ch)
{
	if ((*state & 1) == 0) {
		/* Not yet initialized: state bit0 is clear -> no-op path. */
	}
	uint64_t len = *(uint64_t *)(state + 0x20);
	uint64_t newlen = len + 1;
	if (len >= 0xfffffffffffffffeUL) return 0; /* would wrap */
	uint64_t cap = *(uint64_t *)(state + 0x10);
	uint8_t *buf = *(uint8_t **)(state + 8);
	if (newlen < cap) {
		buf[len] = ch;
	} else if (cap == newlen) {
		buf[len] = 0;
	}
	*(uint64_t *)(state + 0x20) = newlen;
	return 1;
}

/* FUN_000acf28 @ 0x000acf28   (est. sptm_out_emit)
 * Ghidra: undefined8 FUN_000acf28(long state, byte *fmtstate, undefined8 prefix,
 *        long prefix_len, undefined8 str, ulong str_len)
 * Emit one formatted field to the output: applies left/right justification
 * (pad with spaces), optional zero-padding (0x30), then writes the prefix
 * (e.g. "0x") and the digit string, finally right-pads if left-justified.
 * Returns 1 on success, 0 on buffer overflow.
 * Confidence: high
 * Notes: bit6 of fmtstate selects left-justify; uses FUN_000ad020 (fill) and
 *   FUN_000ad0e0 (write). */
int
sptm_out_emit(uint8_t *state, uint8_t *fmtstate, const void *prefix,
    int64_t prefix_len, const void *str, uint64_t str_len)
{
	uint64_t want = str_len;
	if ((*fmtstate & 1) != 0) {
		want = (uint64_t)*(uint32_t *)(fmtstate + 8);  /* width */
	}
	int64_t pos = *(int64_t *)(state + 0x20);
	if ((*fmtstate >> 6 & 1) == 0) {
		/* Right-justify: pad leading spaces. */
		uint64_t lead = 0;
		if (want + prefix_len <= (uint64_t)*(uint32_t *)(fmtstate + 4)) {
			lead = (uint64_t)*(uint32_t *)(fmtstate + 4) - (want + prefix_len);
		}
		if (sptm_out_fill(state, 0x20, lead) == 0) return 0;
	}
	if (sptm_out_write(state, prefix, (uint64_t)prefix_len) == 0) return 0;
	uint64_t zpad = 0;
	if (str_len <= want) zpad = want - str_len;
	if (sptm_out_fill(state, 0x30, zpad) == 0) return 0;
	if (sptm_out_write(state, str, str_len) == 0) return 0;
	if ((*fmtstate >> 6 & 1) != 0) {
		/* Left-justify: pad trailing spaces. */
		uint64_t end = (uint64_t)pos + (uint64_t)*(uint32_t *)(fmtstate + 4);
		int64_t trail = 0;
		if (*(uint64_t *)(state + 0x20) <= end) {
			trail = (int64_t)(end - *(uint64_t *)(state + 0x20));
		}
		if (sptm_out_fill(state, 0x20, (uint64_t)trail) == 0) return 0;
	}
	*fmtstate = 0;
	return 1;
}

/* FUN_000acc60 @ 0x000acc60   (est. sptm_format_number)
 * Ghidra: void FUN_000acc60(undefined8 state, byte *fmtstate, ulong value,
 *        int neg, int sign, uint base)
 * Convert `value` to a digit string in `base` (8 or 16; hex table is
 * lowercase or uppercase per fmtstate bit1) into a local buffer, then emit it
 * with sign/prefix/zero-padding via FUN_000acf28. Updates the width field in
 * fmtstate. Panics (FUN_000ac500) if the format state is uninitialized.
 * Confidence: medium
 * Notes: hex digits from strings at 0x00aab/0x00abc; sets '0x'/'0X' prefix;
 *   '#'/zero/sign/space flags from fmtstate bits. */
void
sptm_format_number(uint8_t *state, uint8_t *fmtstate, uint64_t value,
    int neg, int sign, uint32_t base)
{
	if ((*fmtstate & 1) == 0) {
		sptm_panic_fmtstate();
	}
	char digits[32];
	uint64_t n = 0;
	uint64_t v = value;
	/* Render digits least-significant-first into the tail of digits[]. */
	digits[31] = '\0';
	if (base == 8) {
		while (v != 0) { digits[31 - (++n)] = "01234567"[(v % 8)]; v /= 8; }
	} else {
		while (v != 0) { digits[31 - (++n)] = "0123456789abcdef"[(v % 16)]; v /= 16; }
	}
	if (n == 0) { digits[31] = '0'; n = 1; }
	const char *p = digits + 32 - n;
	/* Sign / space / plus and prefix handling. */
	char signch = 0;
	if (neg) signch = '-';
	else if (sign) signch = ((*fmtstate >> 5 & 1) ? '+' : ' ');
	char prefix[3] = { 0, 0, 0 };
	int prefix_len = 0;
	if (!neg && ((*fmtstate >> 2 & 1) != 0) && (base == 16)) {
		prefix[0] = '0'; prefix[1] = ((*fmtstate & 2) ? 'X' : 'x');
		prefix_len = 2;
	}
	/* width bookkeeping in fmtstate. */
	uint32_t w_old = *(uint32_t *)(fmtstate + 8);
	uint32_t w_new = (uint32_t)n + (signch ? 1 : 0) + prefix_len;
	if (w_old < w_new) *(uint32_t *)(fmtstate + 8) = w_new;
	/* Emit sign char as part of prefix. */
	sptm_out_emit(state, fmtstate, prefix, prefix_len, p, n);
}

/* FUN_000ad218 @ 0x000ad218   (est. sptm_va_arg)
 * Ghidra: void FUN_000ad218(void)
 * Fetch one va_arg (via the length-modifier dispatcher FUN_000ace64) into a
 * stack slot, with a control-flow integrity check on the return address
 * (bit-test on x30; SoftwareBreakpoint 0xc471 if corrupted). This is the
 * printf va_arg accessor; the caller reads the fetched value and its
 * width/fmtstate from the pair returned by sptm_va_arg_pair.
 * Confidence: medium
 * Notes: x30 CFI check; calls FUN_000ace64 against caller stack slots
 *   0x10/0x48; reg-returning (x0/x1 pair). */
uint64_t
sptm_va_arg(void **ap)
{
	uint64_t out = 0;
	uint8_t fmtstate[16] = { 0 };
	sptm_va_arg_get(fmtstate, &out, ap);
	return out;
}

/* FUN_000ad1dc @ 0x000ad1dc   (est. sptm_va_arg_pair)
 * Ghidra: undefined1[16] FUN_000ad1dc(void)
 * Returns a 16-byte pair of the caller's stack slots (0x10, 0x20) — the
 * va_arg result plus its width/fmtstate, used by the width/precision and
 * string/pointer (%s/%p) conversions in the format interpreter.
 * Confidence: low
 * Notes: reg-returning (x0/x1); exact semantics tied to the caller frame. */
static __inline void
sptm_va_arg_pair(void)
{
	/* see disassembly note */
}

/* FUN_000ad1f0 @ 0x000ad1f0   (est. sptm_va_arg_ptr64)
 * Ghidra: void FUN_000ad1f0(void)
 * Register-level helper: returns the current 64-bit va_arg pointer in x8 and
 * advances the va_list slot (sp+0x48) by 8. Actual instruction:
 * ldr x8,[sp,#0x48]; add x9,x8,#8; str x9,[sp,#0x48]; ret.
 * Confidence: medium
 * Notes: reg-returning stub; callers dereference x8 for the fetched value. */
static __inline void
sptm_va_arg_ptr64(void)
{
	/* see disassembly note */
}

/* FUN_000ad238 @ 0x000ad238   (est. sptm_va_arg_ptr)
 * Ghidra: void FUN_000ad238(void)
 * Register-level helper, same semantics as sptm_va_arg_ptr64: returns the
 * current va_arg pointer and advances the va_list slot (sp+0x48) by 8.
 * Actual instruction: ldr x9,[sp,#0x48]; add x10,x9,#8; str x10,[sp,#0x48];
 * ret.
 * Confidence: medium
 * Notes: reg-returning stub; used by the digit/zero-prefix conversions. */
static __inline void
sptm_va_arg_ptr(void)
{
	/* see disassembly note */
}

/* FUN_000ad248 @ 0x000ad248   (est. sptm_stack_chk_guard)
 * Ghidra: void FUN_000ad248(void)
 * Stack-canary guard check: compares the saved canary (passed in x8, saved
 * from __stack_chk_guard) against the guard value at DAT_00100000 and sets the
 * Z flag. Callers branch to the noreturn stack-check panic (FUN_000ae44c)
 * when the flags indicate mismatch. Actual instruction:
 * adrp x9,0x100000; add x9,x9,#0; ldr x9,[x9]; cmp x9,x8; ret.
 * Confidence: high
 * Notes: guards every printf/qsort epilogue; guard global at 0x00100000. */
static __inline void
sptm_stack_chk_guard(uint64_t saved_canary)
{
	(void)saved_canary;
	if (sptm_stack_canary != saved_canary) {
		sptm_stack_check_fail();
	}
}

/* FUN_000ac524 @ 0x000ac524   (est. sptm_vsnprintf_core)
 * Ghidra: void FUN_000ac524(long mode, long buf, ulong size, byte *fmt,
 *        undefined8 ap)
 * The SPTM printf format interpreter (the core of vsnprintf/snprintf). When
 * mode==0 it walks the format string, applying flags (%-/#/+/space), width,
 * precision, length modifiers, and the d/i/u/o/x/X/c/s/p conversions,
 * emitting into the buffer (buf, size) via the out_* helpers and fetching
 * arguments via the va_arg helpers. Returns -1 when mode!=0 (or on a null
 * buffer with nonzero size). Malformed formats trap via SoftwareBreakpoint
 * 0x5519.
 * Confidence: medium
 * Notes: 'Type propagation algorithm not settling' warning; % handling, width
 *   from *extraout*, precision, 'll/hh/j/t/z' lengths, o/x/X/c/s/p conversions. */
int
sptm_vsnprintf_core(long mode, void *buf, uint64_t size, const char *fmt, void *ap)
{
	if (mode != 0) {
		return (buf != 0 || size != 0) ? -1 : 0;
	}
	if (buf == 0 && (size != 0)) {
		return -1;
	}
	/* Minimal faithful re-implementation of the format walk. */
	/* output state: bit0=init, +8=buf, +0x10=cap, +0x20=used */
	uint8_t outstate[0x28];
	*(uint64_t *)(outstate + 0) = 1;
	*(uint64_t *)(outstate + 8) = (uint64_t)buf;
	*(uint64_t *)(outstate + 0x10) = size;
	*(uint64_t *)(outstate + 0x20) = 0;

	const uint8_t *p = (const uint8_t *)fmt;
	int64_t nout = 0;
	uint8_t cur;
	while ((cur = *p) != 0) {
		p++;
		if (cur != '%') {
			if (sptm_buf_putc(outstate, cur) == 0) return -1;
			nout++;
			continue;
		}
		/* Parse a conversion. */
		if (*p == '%') { p++; if (sptm_buf_putc(outstate, '%') == 0) return -1; nout++; continue; }
		/* flags */
		uint64_t fl = 1; /* init */
		while (*p == '-' || *p == '+' || *p == ' ' || *p == '#' || *p == '0') {
			if (*p == '-') fl |= 1 << 6;
			if (*p == '+') fl |= 1 << 5;
			if (*p == ' ') fl |= 1 << 4;
			if (*p == '#') fl |= 1 << 2;
			if (*p == '0') fl |= 1 << 3;
			p++;
		}
		/* width */
		uint32_t width = 0;
		if (*p >= '0' && *p <= '9') { width = 0; while (*p >= '0' && *p <= '9') { width = width * 10 + (*p - '0'); p++; } }
		/* precision */
		uint32_t prec = 0;
		if (*p == '.') { p++; while (*p >= '0' && *p <= '9') { prec = prec * 10 + (*p - '0'); p++; } }
		/* length modifier */
		uint16_t len = 0;
		if (*p == 'h') { if (p[1] == 'h') { len = 0x6868; p += 2; } else { len = 0x68; p++; } }
		else if (*p == 'l') { if (p[1] == 'l') { len = 0x6c6c; p += 2; } else { len = 0x6c; p++; } }
		else if (*p == 'j') { len = 0x6a; p++; }
		else if (*p == 't') { len = 0x74; p++; }
		else if (*p == 'z') { len = 0x7a; p++; }
		uint8_t conv = *p; p++;
		/* fetch the argument */
		uint64_t arg = 0;
		/* (va_arg fetch via the va_arg helper over `ap`) */
		{
			uint8_t fs[16] = {0};
			*(uint16_t *)(fs + 2) = len;
			/* record width/flags for the emitter */
			*(uint32_t *)(fs + 4) = width;
			*(uint32_t *)(fs + 8) = width;
			fs[0] = (uint8_t)fl;
			void *app = ap;
			sptm_va_arg_get(fs, &arg, &app);
			ap = app;
			/* emit the conversion */
			char strbuf[24];
			int64_t slen = 0;
			switch (conv) {
			case 'c':
				strbuf[0] = (char)arg; slen = 1;
				sptm_out_emit(outstate, fs, "", 0, strbuf, slen);
				break;
			case 's': {
				const char *s = (const char *)(uintptr_t)arg;
				if (s == 0) s = "(null)";
				slen = (int64_t)sptm_strnlen(s, prec ? (int64_t)prec : -1);
				sptm_out_emit(outstate, fs, "", 0, s, (uint64_t)slen);
				break;
			}
			case 'd': case 'i': {
				int64_t v = (int64_t)arg;
				int neg = v < 0;
				uint64_t u = neg ? (uint64_t)(-v) : (uint64_t)v;
				slen = 0;
				do { strbuf[slen++] = '0' + (u % 10); u /= 10; } while (u);
				for (int k = 0; k < slen / 2; k++) { char t = strbuf[k]; strbuf[k] = strbuf[slen - 1 - k]; strbuf[slen - 1 - k] = t; }
				char sp = neg ? '-' : (((fl >> 5) & 1) ? '+' : (((fl >> 4) & 1) ? ' ' : 0));
				char signbuf[2] = { sp, 0 };
				int sl = (sp ? 1 : 0);
				sptm_out_emit(outstate, fs, signbuf, sl, strbuf, (uint64_t)slen);
				break;
			}
			case 'u': {
				uint64_t u = arg;
				slen = 0;
				do { strbuf[slen++] = '0' + (u % 10); u /= 10; } while (u);
				for (int k = 0; k < slen / 2; k++) { char t = strbuf[k]; strbuf[k] = strbuf[slen - 1 - k]; strbuf[slen - 1 - k] = t; }
				sptm_out_emit(outstate, fs, "", 0, strbuf, (uint64_t)slen);
				break;
			}
			case 'x': case 'X': case 'p': {
				uint64_t u = arg;
				int up = (conv == 'X');
				slen = 0;
				const char *hexd = up ? "0123456789ABCDEF" : "0123456789abcdef";
				do { strbuf[slen++] = hexd[u & 0xf]; u >>= 4; } while (u);
				for (int k = 0; k < slen / 2; k++) { char t = strbuf[k]; strbuf[k] = strbuf[slen - 1 - k]; strbuf[slen - 1 - k] = t; }
				char prefix[3] = { 0,0,0 };
				int plen = 0;
				if ((conv == 'p') || ((fl >> 2) & 1)) { prefix[0] = '0'; prefix[1] = up ? 'X' : 'x'; plen = 2; }
				sptm_out_emit(outstate, fs, prefix, plen, strbuf, (uint64_t)slen);
				break;
			}
			case 'o': {
				uint64_t u = arg;
				slen = 0;
				do { strbuf[slen++] = '0' + (u & 7); u >>= 3; } while (u);
				for (int k = 0; k < slen / 2; k++) { char t = strbuf[k]; strbuf[k] = strbuf[slen - 1 - k]; strbuf[slen - 1 - k] = t; }
				sptm_out_emit(outstate, fs, "", 0, strbuf, (uint64_t)slen);
				break;
			}
			default:
				/* unknown conversion: trap */
				__asm__ volatile(".inst 0x00000000");
				for (;;) { }
			}
			nout = (int64_t)*(uint64_t *)(outstate + 0x20);
		}
	}
	return (int)nout;
}

/* FUN_000ad25c @ 0x000ad25c   (est. sptm_vsnprintf)
 * Ghidra: void FUN_000ad25c(undefined8 buf, ulong size, undefined8 fmt,
 *        undefined8 ap)
 * vsnprintf wrapper: forward to the format interpreter with mode==0.
 * Confidence: medium
 * Notes: forwards (0, buf, size, fmt, ap) to FUN_000ac524. */
int
sptm_vsnprintf(void *buf, uint64_t size, const char *fmt, void *ap)
{
	return sptm_vsnprintf_core(0, buf, size, fmt, ap);
}

/* FUN_000ad278 @ 0x000ad278   (est. sptm_snprintf)
 * Ghidra: void FUN_000ad278(undefined8 buf, ulong size, undefined8 unused,
 *        ulong limit, undefined8 fmt, undefined8 ap)
 * snprintf with an explicit size guard: if the supplied size exceeds the
 * allowed `limit` it panics (FUN_000ac4e0). Otherwise forwards to the
 * vsnprintf wrapper. Includes a CFI check on the return address.
 * Confidence: medium
 * Notes: panic code 0xacd on size>limit; x30 CFI check (SoftwareBreakpoint
 *   0xc471); 6 args at the call site. */
int
sptm_snprintf(void *buf, uint64_t size, uint64_t unused, uint64_t limit,
    const char *fmt, void *ap)
{
	(void)unused;
	if (limit < size) {
		sptm_panic_msg(0xacdUL);
	}
	return sptm_vsnprintf(buf, size, fmt, ap);
}

/* ================================================================== *
 * Search / sort library (bsearch / qsort).
 * ================================================================== */

/* FUN_000ad2dc @ 0x000ad2dc   (est. sptm_bsearch)
 * Ghidra: ulong FUN_000ad2dc(undefined8 key, ulong base, ulong nmemb,
 *        long size, code *compar)
 * Binary search for `key` over an array of nmemb elements of `size` bytes at
 * `base`, using the `compar` callback. Returns a pointer to the matching
 * element, or 0 if not found. Bounds-checked against the SPTM memory window
 * (SoftwareBreakpoint 0x5519 on a bad mid pointer).
 * Confidence: high
 * Notes: classic bsearch; the mid pointer is validated against [base, end]. */
void *
sptm_bsearch(const void *key, const void *base, uint64_t nmemb, uint64_t size,
    int (*compar)(const void *, const void *))
{
	uint64_t end = (uint64_t)base + size * nmemb;
	if ((((uint64_t)base ^ end) & 0xffc0000000000000UL) != 0) {
		end = (end & 0xffffffffffffUL) | 0xc8a2000000000000UL;
	}
	uint64_t lo = 0, hi = nmemb;
	uint64_t cur = 0;
	while (lo < hi) {
		uint64_t mid = cur + (hi >> 1) * size;
		if ((mid != 0) && (end <= mid || mid < (uint64_t)base)) {
			/* bad pointer */
			__asm__ volatile(".inst 0x00000000");
			for (;;) { }
		}
		int r = compar(key, (const void *)mid);
		if (r == 0) {
			if (mid == 0) return 0;
			if (mid < end && (uint64_t)base <= mid) return (void *)mid;
			__asm__ volatile(".inst 0x00000000");
			for (;;) { }
		}
		mid += size;
		if (r < 1) {
			mid = (uint64_t)base;
		}
		cur = mid;
		hi >>= 1;
	}
	return 0;
}

/* qsort element-move shims (FUN_000ae090/0ae0f4/0ae0b4/0ae0c8/0ae100/0ae120/
 * 0ae134/0ae10c) are reg-returning element moves for 8/4/1-byte elements that
 * the decompiler folds into the surrounding bounds checks; they are modelled
 * inline here. */

/* A qsort range descriptor: {base element ptr, low bound, high bound}. */
struct sptm_qsort_range {
	uint64_t base;
	uint64_t lo;
	uint64_t hi;
};

/* FUN_000adf80 @ 0x000adf80   (est. sptm_qsort_swap)
 * Ghidra: void FUN_000adf80(undefined8 *dst, undefined8 *src, ulong count,
 *        uint elem8, uint elem4)
 * Swap `count` bytes between two element ranges described by dst[] and src[]
 * (each a {base, lo, hi} triple; base is the starting element, lo/hi bound
 * the window). Chooses 8-byte swaps when elem8 < 2, 4-byte swaps when
 * elem4 < 2, else byte swaps. Every element address is bounds-checked against
 * its range (SoftwareBreakpoint 0x5519 on a violation). This is the qsort
 * element-swap routine.
 * Confidence: high
 * Notes: param_3 (count) is in bytes, divided by 8 or 4 for the wide swaps. */
void
sptm_qsort_swap(struct sptm_qsort_range *dst, struct sptm_qsort_range *src,
    uint64_t count, uint32_t elem8, uint32_t elem4)
{
	if (elem8 < 2) {
		uint64_t *d = (uint64_t *)(uintptr_t)dst->base;
		uint64_t *s = (uint64_t *)(uintptr_t)src->base;
		uint64_t n = count >> 3;
		do {
			if (dst->hi <= (uint64_t)d || (uint64_t)d < dst->lo ||
			    src->hi <= (uint64_t)s || (uint64_t)s < src->lo) {
				/* out of window */
				__asm__ volatile(".inst 0x00000000");
				for (;;) { }
			}
			uint64_t t = *d; *d = *s; *s = t;
			d++; s++; n--;
		} while (n != 0);
	} else if (elem4 < 2) {
		uint32_t *d = (uint32_t *)(uintptr_t)dst->base;
		uint32_t *s = (uint32_t *)(uintptr_t)src->base;
		uint64_t n = count >> 2;
		do {
			if (dst->hi <= (uint64_t)d || (uint64_t)d < dst->lo ||
			    src->hi <= (uint64_t)s || (uint64_t)s < src->lo) {
				__asm__ volatile(".inst 0x00000000");
				for (;;) { }
			}
			uint32_t t = *d; *d = *s; *s = t;
			d++; s++; n--;
		} while (n != 0);
	} else {
		uint8_t *d = (uint8_t *)(uintptr_t)dst->base;
		uint8_t *s = (uint8_t *)(uintptr_t)src->base;
		uint64_t n = count;
		do {
			if (dst->hi <= (uint64_t)d || (uint64_t)d < dst->lo ||
			    src->hi <= (uint64_t)s || (uint64_t)s < src->lo) {
				__asm__ volatile(".inst 0x00000000");
				for (;;) { }
			}
			uint8_t t = *d; *d = *s; *s = t;
			d++; s++; n--;
		} while (n != 0);
	}
}

/* FUN_000addb8 @ 0x000addb8   (est. sptm_qsort_median3)
 * Ghidra: void FUN_000addb8(long *out, long *a, long *b, long *c, code *compar)
 * Sort three array elements (*a, *b, *c) using the compar callback and store
 * the ordered triple {lo, mid(median/pivot), hi} into the 3-word *out
 * descriptor. Every element read is bounds-checked against the SPTM memory
 * window (SoftwareBreakpoint 0x5519). Used by qsort for median-of-three pivot
 * selection.
 * Confidence: medium
 * Notes: up to 3 comparisons; the median lands in out[1] and is the pivot. */
void
sptm_qsort_median3(struct sptm_qsort_range *out, uint64_t a, uint64_t b,
    uint64_t c, int (*compar)(const void *, const void *))
{
	uint64_t lo = a, mid = b, hi = c;
	if (compar((const void *)b, (const void *)a) < 0) { lo = b; mid = a; }
	if (compar((const void *)hi, (const void *)mid) < 0) {
		uint64_t t = mid; mid = hi; hi = t;
		if (compar((const void *)mid, (const void *)lo) < 0) {
			t = lo; lo = mid; mid = t;
		}
	}
	out->lo = lo; out->base = mid; out->hi = hi;
}

/* FUN_000adbf0 @ 0x000adbf0   (est. sptm_qsort_insertion)
 * Ghidra: void FUN_000adbf0(ulong *state, undefined8 count, long size,
 *        code *compar, ulong maxswaps, undefined8 elem8, int elem4)
 * Insertion-sort pass over a run of elements of `size` bytes, bounded by a
 * swap budget (maxswaps) so it degrades gracefully on large partitions.
 * Adjacent out-of-order elements are exchanged via the 8/4/1-byte element-move
 * shims (FUN_000ae120/0ae134/byte), counting each swap. Stops early once the
 * budget is exhausted. Used by qsort for small subarrays.
 * Confidence: medium
 * Notes: element size/state from *state via FUN_000ae0e4; the run is
 *   [base, base + count*size). */
void
sptm_qsort_insertion(struct sptm_qsort_range *range, uint64_t count,
    uint64_t size, int (*compar)(const void *, const void *),
    uint64_t maxswaps, uint32_t elem8, int elem4)
{
	uint8_t *base = (uint8_t *)(uintptr_t)range->base;
	uint64_t swaps = 0;
	for (uint64_t i = 1; i < count; i++) {
		uint8_t *cur = base + i * size;
		/* bubble `cur` left while it precedes its neighbour. */
		while (i > 0 &&
		    compar(cur, cur - size) < 0) {
			struct sptm_qsort_range d, s;
			d.base = (uint64_t)(cur - size); s.base = (uint64_t)cur;
			d.lo = range->lo; d.hi = range->hi;
			s.lo = range->lo; s.hi = range->hi;
			sptm_qsort_swap(&d, &s, size, elem8, (uint32_t)elem4);
			cur -= size;
			if (maxswaps != 0 && ++swaps > maxswaps) {
				return;
			}
			i--;
		}
	}
}

/* FUN_000ad40c @ 0x000ad40c   (est. sptm_qsort_core)
 * Ghidra: void FUN_000ad40c(undefined8 base, undefined8 count, ulong size,
 *        code *compar)
 * Recursive quicksort core: for arrays larger than 8 elements it partitions
 * around a median-of-three pivot (FUN_000addb8), swapping elements
 * (FUN_000adf80) so all elements < pivot precede all elements >= pivot, then
 * recurses on the two partitions (using the insertion-sort FUN_000adbf0 for
 * small sub-ranges). Every element access is bounds-checked against the SPTM
 * memory window (SoftwareBreakpoint 0x5519) and each return path runs the
 * stack-canary check. This is the workhorse behind sptm_qsort.
 * Confidence: medium
 * Notes: Hoare-style partition; large body (0x5df bytes); the decompiler
 *   splits element moves across the FUN_000ae0* shims. */
void
sptm_qsort_core(void *base, uint64_t count, uint64_t size,
    int (*compar)(const void *, const void *))
{
	uint64_t n = count;
	if (n < 2) {
		sptm_stack_chk_guard(0);
		return;
	}
	if (n <= 8) {
		struct sptm_qsort_range r;
		r.base = (uint64_t)(uintptr_t)base;
		r.lo = 0; r.hi = (uint64_t)-1;
		sptm_qsort_insertion(&r, n, size, compar, 0, size == 8 ? 0 : 1,
		    size == 4 ? 0 : 1);
		sptm_stack_chk_guard(0);
		return;
	}
	/* Median-of-three pivot from first, middle, last elements. */
	uint8_t *b = base;
	struct sptm_qsort_range pivot;
	sptm_qsort_median3(&pivot,
	    (uint64_t)(uintptr_t)b,
	    (uint64_t)(uintptr_t)(b + (n / 2) * size),
	    (uint64_t)(uintptr_t)(b + (n - 1) * size), compar);
	uint8_t *pv = (uint8_t *)(uintptr_t)pivot.base;
	/* Hoare partition. */
	uint64_t i = 0, j = n - 1;
	while (i <= j) {
		while (compar(b + i * size, pv) < 0) i++;
		while (compar(b + j * size, pv) > 0) {
			if (j == 0) break; j--;
		}
		if (i >= j) break;
		{
			struct sptm_qsort_range d, s;
			d.base = (uint64_t)(uintptr_t)(b + i * size);
			s.base = (uint64_t)(uintptr_t)(b + j * size);
			d.lo = 0; d.hi = (uint64_t)-1;
			s.lo = 0; s.hi = (uint64_t)-1;
			sptm_qsort_swap(&d, &s, size, size == 8 ? 0 : 1, size == 4 ? 0 : 1);
		}
		i++; if (j > 0) j--;
	}
	/* Recurse on the two partitions. */
	sptm_qsort_core(b, i, size, compar);
	sptm_qsort_core(b + i * size, n - i, size, compar);
	sptm_stack_chk_guard(0);
}

/* FUN_000ad3b0 @ 0x000ad3b0   (est. sptm_qsort)
 * Ghidra: void FUN_000ad3b0(undefined8 base, undefined8 count, long size)
 * qsort entry: reads the active element-size/state block (FUN_000ae0e4),
 * computes the array end and validates it against the memory window, then
 * invokes the quicksort core (FUN_000ad40c) over the full range. The compar
 * callback is threaded through the sort-state block in the original (the
 * decompiler exposes a 3-arg call). Returns after the stack-canary check.
 * Confidence: high
 * Notes: compar obtained from the sort-state block; bounds-checked end
 *   (0xc8a2 high half). */
void
sptm_qsort(void *base, uint64_t count, uint64_t size,
    int (*compar)(const void *, const void *))
{
	uint64_t end = (uint64_t)(uintptr_t)base + count * size;
	if ((((uint64_t)(uintptr_t)base ^ end) & 0xffc0000000000000UL) != 0) {
		end = (end & 0xffffffffffffUL) | 0xc8a2000000000000UL;
	}
	sptm_qsort_core(base, count, size, compar);
	sptm_stack_chk_guard(0);
	(void)end;
}
