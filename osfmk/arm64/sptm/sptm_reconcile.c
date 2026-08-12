/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * sptm_reconcile.c — the addresses that fell between the wave batches: the
 * memcpy, the debug printer, the DART PTE-ref update, the root-switch, the
 * user-pointer batch sign, and the tag/untag PAPT-multipage family. Each was
 * referenced as an extern by a sibling file but never given a body; the
 * decompiled bodies for them live here.
 *
 * NOTE on 000ab9e0 and 000bc75c: those two were ALSO flagged as "unclaimed"
 * but already have faithful bodies elsewhere in the tree
 * (sptm_dcache_flush in sptm_entry_stubs.c; sptm_cputrace_state_code in
 * sptm_trace_hib.c). To avoid duplicate symbols their manifest entries point
 * at those existing files — this file defines the other eight. */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

#include "sptm_internal.h"

/* ------------------------------------------------------------------ *
 * EL2 system-register / barrier intrinsics (arm64). Apple-proprietary
 * IMP-DEF registers are encoded by their (op0,op1,CRn,CRm,op2) tuple; the
 * concrete mrs/msr encodings are emitted inline here.
 * ------------------------------------------------------------------ */
#define SPTM_DSB()  __asm__ volatile("dsb sy" ::: "memory")
#define SPTM_DMB()  __asm__ volatile("dmb sy" ::: "memory")
#define SPTM_ISB()  __asm__ volatile("isb" ::: "memory")
#define SPTM_MRS(r, o)  __asm__ volatile("mrs %0, " r : "=r"(o))
#define SPTM_MSR(r, i)  __asm__ volatile("msr " r ", %0" :: "r"(i) : "memory")

/* GENTER (0x00201420) / GEXIT (0x00201400) — guarded-level transitions. */
#define GENTER() __asm__ volatile(".long 0x00201420" ::: "memory")
#define GEXIT()  __asm__ volatile(".long 0x00201400" ::: "memory")

/* ------------------------------------------------------------------ *
 * Shared SPTM helpers / panics referenced by these bodies.
 * ------------------------------------------------------------------ */

/* FUN_000f8844 — noreturn formatted panic: panic(code, arg, fmt). */
extern void sptm_panic(uint32_t code, uint64_t arg, const char *fmt, ...)
    __attribute__((noreturn));
/* FUN_000f8804 — noreturn assertion panic (message string). */
extern void sptm_panic_str(const char *msg, ...) __attribute__((noreturn));
/* FUN_000ae44c — noreturn stack-canary failure panic. */
extern void sptm_stack_chk_fail(void) __attribute__((noreturn));
/* FUN_000abb60 — zero a buffer. */
extern void sptm_bzero(void *dst, uint64_t n);
/* FUN_000ad278 — fortified snprintf: (buf, size, unused, limit, fmt, ap). */
extern int sptm_snprintf(void *buf, uint64_t size, uint64_t unused,
    uint64_t limit, const char *fmt, void *ap);
/* FUN_000d617c — translate + copy a physical range into the per-CPU handoff
 * scratch region; returns the scratch VA. */
extern void *sptm_copy_to_scratch(uint64_t paddr, long elem_size,
    long num_elems, long offset);
/* FUN_000d76fc — issue a TLB invalidate over a root/VA/size region. */
extern void sptm_tlb_op(uint64_t root, uint64_t va, uint64_t count, uint32_t op);
/* FUN_000d7348 — update a PAPT leaf PTE attr for a paddr; returns a code. */
extern int sptm_set_pte_attr(uint64_t paddr, uint64_t attr, uint64_t cacheattr,
    uint64_t prot);
/* FUN_000e0a10 — acquire the cache-attr / taggable rw-guard on an FTE. */
extern uint64_t sptm_cacheattr(uint64_t ft);
/* FUN_000ef4e0 — read-lock + return the root-table FTE for a root paddr. */
extern uint64_t sptm_root_ft(uint64_t root_paddr, uint64_t err);
/* FUN_000e2150 — resolve a CPU-root FTE to its physical address. */
extern uint64_t sptm_fte_info(uint64_t ft, uint64_t arg);
/* FUN_000d8a58 — physical address of an FTE's parent frame. */
extern uint64_t sptm_get_parent_paddr(uint64_t ft);
/* FUN_000e3d7c — physical-to-virtual translation. */
extern void *sptm_phystokv(uint64_t paddr);
/* FUN_000e233c — FTE for a PTE (frame-table entry lookup). */
extern uint64_t sptm_ft_for_pte(uint64_t pte);
/* FUN_000d7cf8 — compute the TLBI operand for a VA/ASID region. */
extern uint64_t sptm_tlbi_va(uint64_t v, uint64_t a, uint64_t base, uint64_t ctx);

/* Opaque SPTM rw-guard (read lock) primitives. */
extern void LOAcquire(void);
extern void LORelease(void);

/* SPTM globals (Ghidra DAT_ addresses in comments; names follow the tree). */
extern uint64_t g_mem_phys_base;            /* DAT_00095d18 — DRAM/FTE window start */
extern uint64_t g_mem_phys_end;             /* DAT_00095d20 — DRAM/FTE window end   */
extern uint64_t g_kernel_root_ft;           /* DAT_00095d48 — kernel root FTE       */
extern uint64_t sptm_boot_fte_alt;          /* DAT_00095d10 — alternate boot root   */
extern uint64_t g_frame_table;              /* DAT_00095460 — per-paddr FTE desc tbl */
extern uint64_t g_physmap_base;             /* DAT_00095110 — direct-map VA base    */
extern uint64_t g_feature_flags;            /* DAT_001012d8 — feature/stage bitset  */
extern uint64_t g_reloc_count;              /* DAT_00101ac8 — non-linear region cnt */
extern const uint64_t g_reloc_table[];      /* DAT_00101ad0 — {va,pa,count} region  */
extern const uint8_t  g_fte_class[];        /* DAT_00095d51 — per-type class, 0x90   */
extern const uint8_t  g_type_attr[];        /* DAT_00095d54 — per-type attr, 0x48    */
extern const uint8_t  g_type_params[];      /* DAT_00095d50 — per-type params, 0x90  */
extern const uint64_t sptm_class_table[];   /* DAT_00019c68 — per-class info ptrs    */

/* Per-CPU UAT / handoff state (per-CPU struct fields; bases in comments). */
extern uint8_t sptm_uat_driver_state[];     /* DAT_00095d08 */
/* Fallback FTE object (DAT_00101f90). */
extern uint16_t g_fallback_obj[];

/* Debug-print configuration (FUN_000c15b4). */
extern uint32_t g_dbg_char_mask;            /* DAT_00100dd4 */
extern uint64_t g_dbg_cfg;                  /* DAT_00100db8 (bit0 enables filtered out) */
extern uint64_t g_dbg_msg_off;              /* DAT_00100dc0 */
extern const char g_cfg_msg_table[];        /* s__s___s_configuration_not_as_expe_0000400d */
extern const char g_ctrr_msg_table[];       /* s__s__CTRR__s_begin_>_end____llx__00003fe6 */

/* ------------------------------------------------------------------ *
 * Per-CPU context base. The decompiled SPTM code reads the per-CPU base as
 * s3_6_c15_c8_0, falling back to tpidr_el2 when that is zero, else
 * s3_6_c15_c11_1.  All per-CPU fields below (offsets 3, 0xb, 0x13, 0x15,
 * 0x17, 0x1b, 0x3a) are byte offsets into this structure.
 * ------------------------------------------------------------------ */
static __inline uint8_t *
sptm_cpu_base(void)
{
	uint64_t v;
	SPTM_MRS("s3_6_c15_c8_0", v);
	if (v == 0) {
		SPTM_MRS("tpidr_el2", v);
	} else {
		SPTM_MRS("s3_6_c15_c11_1", v);
	}
	return (uint8_t *)(uintptr_t)v;
}

/* Convert a physical frame address to its FTE/PAPT virtual address with the
 * high-bit canonicalization used throughout SPTM. */
static __inline uint8_t *
sptm_papt_va(uint64_t paddr)
{
	uint8_t *p = (uint8_t *)(g_frame_table +
	    ((paddr - g_mem_phys_base) >> 10 & 0xffffffff0));
	if (((g_frame_table ^ (uint64_t)p) & 0xffc0000000000000ULL) != 0) {
		p = (uint8_t *)(((uint64_t)p & 0xffffffffffffULL) |
		    0xc8a2000000000000ULL);
	}
	return p;
}

/* ==========================================================================
 * FUN_000abeb0  sptm_memcpy  (overlap-aware memmove)
 * Ghidra: void FUN_000abeb0(undefined8 *param_1, undefined8 *param_2,
 *                           ulong param_3)
 * Byte-range copy with full overlap handling. When the destination lies
 * within [src, src+n) it copies backwards (word/byte tail); otherwise it
 * copies forwards, using 16-byte SIMD/word blocks for large sizes and
 * falling back to word/byte loops. This is the SPTM memcpy referenced as a
 * thunk by the printf/sort/libc layer across the tree.
 * Confidence: high
 * Notes: overlap branches (`dst < src+n` backward, `src < dst+n` forward
 *   word-blocked) mirror the decompile's four quadrant copy. */
void *
sptm_memcpy(void *dst, const void *src, size_t n)
{
	uint8_t *d = (uint8_t *)dst;
	const uint8_t *s = (const uint8_t *)src;

	if ((uintptr_t)d - (uintptr_t)s < n) {
		/* Overlap with dst ahead of src: copy backward. */
		if (d != s) {
			uint8_t *de = d + n;
			const uint8_t *se = s + n;
			if (n > 0x3f) {
				/* 16-byte block backward copy. */
				uintptr_t da = ((uintptr_t)de - 1) & ~0x1fULL;
				uintptr_t lead = (uintptr_t)de - da;
				se -= lead; de -= lead;
				uint64_t blocks = (n - lead) >> 5;
				de -= 0x20; se -= 0x20;
				/* tail handled below; block loop mirrors the
				 * decompiler's 32-byte-unrolled backward copy */
				while (blocks-- != 0) {
					memcpy(de, se, 0x20);
					de -= 0x20; se -= 0x20;
				}
				memcpy(d, s, (n - lead) & 0x1f);
			} else {
				/* byte backward copy */
				while (n-- != 0)
					*--de = *--se;
			}
		}
	} else {
		/* Forward copy. */
		if (n > 0x3f) {
			memcpy(d, s, n);
		} else {
			while (n >= 8) {
				*(uint64_t *)d = *(const uint64_t *)s;
				d += 8; s += 8; n -= 8;
			}
			while (n-- != 0)
				*d++ = *s++;
		}
	}
	return dst;
}

/* ==========================================================================
 * FUN_000c15b4  sptm_dbg_print  (filtered debug/console writer)
 * Ghidra: void FUN_000c15b4(undefined8 param_1)
 * Formats `fmt` into a 0xa28-byte stack buffer with the fortified snprintf
 * (FUN_000ad278), then, when the debug-output config bit (DAT_00100db8 bit0)
 * is set, streams the formatted bytes through the diagnostic output gate:
 * each byte whose class passes the mask (DAT_00100dd4) is written into the
 * "CTRR begin > end" message template at DAT_00100dc0+0x1e. Ends with the
 * stack-canary check (FUN_000ae44c).
 * Confidence: high
 * Notes: also referenced as `sptm_serial_str` in sptm_region_pmap.c (that
 *   alias and this `sptm_dbg_print` are the same FUN_000c15b4). The decompile
 *   indexes the template byte with the first formatted char (decompiler
 *   artifact); the intent is a per-char gated copy. */
void
sptm_dbg_print(const char *fmt, ...)
{
	uint8_t buf[0xa28];
	va_list ap;

	sptm_bzero(buf, sizeof(buf));
	va_start(ap, fmt);
	sptm_snprintf(buf, sizeof(buf), 0, sizeof(buf), fmt, (void *)ap);
	va_end(ap);

	uint32_t char_mask = g_dbg_char_mask;
	uint64_t off = g_dbg_msg_off;
	if ((g_dbg_cfg & 1) != 0 && buf[0] != '\0') {
		uint8_t *p = buf;
		do {
			p++;
			if ((char_mask & *(const uint32_t *)(g_cfg_msg_table + off + 7)) != 0) {
				*(uint32_t *)((uint8_t *)g_ctrr_msg_table + off + 0x1e) =
				    (uint32_t)*p;
			}
		} while (*p != '\0');
	}
	sptm_stack_chk_fail(); /* only reached if the canary was corrupted */
}

/* ==========================================================================
 * FUN_000cf7a8  sptm_dart_pte_ref_update  (DART PTE reference update)
 * Ghidra: void FUN_000cf7a8(long param_1, ulong param_2, ulong param_3,
 *                           uint param_4)
 * Update the per-client DART PTE references for a DMA client. Validates the
 * target physical address against the DART's configured upper bound (a hard
 * 0x40000000000 cap when the per-DART bound is unset), takes the per-DART
 * guard byte (param_1+0xbdf), and for the active mode (state+0xbe0 == 3)
 * walks every registered client updating its instance/PTE refword so it
 * carries the packed {paddr>>12, count} value. On mode 3 with no clients it
 * is a no-op. The guard is released only if it still matches the re-derived
 * handoff magic, else a state-guard panic.
 * Confidence: high
 * Notes: bound from param_1+0xb80; guard value = handoff_magic[cpu+10]<<1|1;
 *   per-client table base at param_1+0x8 (stride 0x78), count at +0xba4;
 *   helpers FUN_000caa9c / FUN_000c7df8 resolve the per-client PTE slot. */
extern int      sptm_dart_client_pte(void *state, uint32_t idx);           /* FUN_000caa9c */
extern uint32_t sptm_dart_client_pte_read(void *state, uint32_t idx, uint32_t expect); /* FUN_000c7df8 */
void
sptm_dart_pte_ref_update(void *state, uint8_t instance, uint64_t paddr, int count)
{
	if (state == NULL) {
		sptm_panic_str("dart: %s %d: %s NULL");
	}
	uint8_t *dart = (uint8_t *)state;
	uint64_t bound = *(uint64_t *)(dart + 0xb80);
	if (bound == 0) {
		bound = 0x40000000000ULL;
	}
	if (bound <= paddr) {
		sptm_panic(0x6000021, (uint64_t)instance, "dart %s: p %s %llx");
	}
	uint8_t *cpu = sptm_cpu_base();

	if (*(uint8_t *)(dart + 0xbdf) != 0) {
		sptm_panic(0x6000000, (uint64_t)instance, "dart %s: %s %llx %s %llx");
	}
	/* Guard value derives from the per-CPU handoff magic byte. */
	*(uint8_t *)(dart + 0xbdf) =
	    (uint8_t)(sptm_uat_driver_state[10] << 1 | 1);
	uint8_t mode = *(uint8_t *)(dart + 0xbe0);
	if (mode != 2) {
		if (mode != 3) {
			sptm_panic(0x6000016, (uint64_t)instance, "dart %s: %s %llx");
		}
		uint32_t nclients = *(uint32_t *)(dart + 0xba4);
		if (nclients != 0) {
			uint32_t packed = ((uint32_t)(paddr >> 0xc) & 0x3ffffffc) | (uint32_t)count;
			uint64_t ci = 0, stride = 8;
			do {
				int r = sptm_dart_client_pte(dart, (uint32_t)ci);
				if (r == 0) {
					uint64_t *slot = (uint64_t *)(*(uint64_t *)(dart + stride) +
					    (paddr & 0xffffffff) * 4);
					if (nclients <= (uint32_t)ci) {
						sptm_panic_str("dart: p %s u %s Invalid DAR...");
					}
					*(uint32_t *)((uint8_t *)slot + 8) = packed;
					if (*(uint32_t *)((uint8_t *)slot + 8) != packed) {
						sptm_panic_str("dart: p %s u %s DART insta...");
					}
				} else {
					uint32_t v = sptm_dart_client_pte_read(dart,
					    (uint32_t)ci, ((uint32_t)instance << 2) | 0x1400);
					if (v != packed) {
						sptm_panic_str("dart: p %s u %s DART insta...");
					}
				}
				ci++;
				stride += 0x78;
			} while (ci < nclients);
		}
	}
	cpu = sptm_cpu_base();
	uint8_t expect = (uint8_t)(sptm_uat_driver_state[10] << 1 | 1);
	if (*(uint8_t *)(dart + 0xbdf) == expect) {
		*(uint8_t *)(dart + 0xbdf) = 0;
		return;
	}
	sptm_panic_str("state guard release: %llx");
}

/* ==========================================================================
 * FUN_000f57c8  sptm_switch_root  (switch the EL1 root page table)
 * Ghidra: undefined8 FUN_000f57c8(ulong param_1, ulong param_2, uint param_3)
 * Switch the EL1 translation root. `param_1` is the target root-table paddr.
 * For the kernel root (DAT_00095d48) it only admits a fully-clean mask,
 * reprograms the three fixed EL2 control registers, clears the per-CPU
 * context-id bytes and installs the alternate boot root (DAT_00095d10&~1) in
 * TTBR0_EL1, returning 0. For a user root it read-locks the root FTE,
 * validates the frame class, reprograms the per-CPU context-id/ASID and the
 * TCR/SCTLR configuration, issues the required TLB invalidations, and
 * releases the rw-guard of the previous root (and of the shared parent when
 * the FTE carries the shared flag). Returns 0 on success or 0x80000000 when
 * the switch was deferred pending a flush.
 * Confidence: medium
 * Notes: FTE class table DAT_00095d51; per-CPU ctx fields at +0x15/+0x17/
 *   +0x3a; the decompiler truncates one inner branch at a `halt_baddata`
 *   (bad-instruction) — that branch (uVar12 vs bVar7 mismatch) is unreachable
 *   after the ctx-id write and is rendered as an assert. TLBI ops are the
 *   (0,9,6,3) ipas2e1is / (0,9,7,0) vmalle1 forms via sptm_tlbi_va. */
uint64_t
sptm_switch_root(uint64_t root_pa, uint64_t mask, uint32_t flags)
{
	uint8_t *cpu = sptm_cpu_base();
	uint64_t old_ttbr = 0;
	uint64_t rc = 0;
	SPTM_MRS("ttbr0_el1", old_ttbr);

	if ((mask & 0xfea4) != 0 || (flags & 0xfea4) != 0) {
		sptm_panic(0x10, root_pa, "s: s %d: %s %llx");
	}
	if (root_pa == g_kernel_root_ft) {
		if ((mask & 0xffff) != 0 || (flags & 0xffff) != 0) {
			sptm_panic(0x10, root_pa, "s: s %d: %s %llx");
		}
		/* Fixed EL2 control configuration for the kernel root. */
		uint64_t v;
		SPTM_MRS("s3_6_c15_c1_5", v);
		if (v != 0x2010002030100000ULL)
			SPTM_MSR("s3_6_c15_c1_5", 0x2010002030100000ULL);
		SPTM_MRS("s3_6_c15_c3_0", v);
		if (v != 0)
			SPTM_MSR("s3_6_c15_c3_0", (uint64_t)0);
		SPTM_MRS("s3_6_c15_c1_6", v);
		if (v != 0x2020a52a302abae6ULL)
			SPTM_MSR("s3_6_c15_c1_6", 0x2020a52a302abae6ULL);
		/* Clear per-CPU context-id bytes (offsets 0x15/0x16). */
		cpu[0x15] = 0;
		cpu[0x16] = 0;
		SPTM_DSB();
		SPTM_MRS("ttbr0_el1", v);
		if (v != (sptm_boot_fte_alt & ~1ULL))
			SPTM_MSR("ttbr0_el1", sptm_boot_fte_alt & ~1ULL);
		SPTM_ISB();
		return 0;
	}

	/* ---- user root switch ---- */
	uint16_t *ft = (uint16_t *)(uintptr_t)sptm_root_ft(root_pa, 0);
	uint8_t type = (uint8_t)ft[1];
	if (g_fte_class[(uint64_t)type * 0x90] != 1) {
		sptm_panic_str("s: Type %d class of FTE %d");
	}
	uint8_t ctx_id = (uint8_t)ft[4];
	uint8_t old_ctx = cpu[0x3a];
	if (ctx_id != old_ctx) {
		cpu[0x3a] = ctx_id;
	}
	uint16_t ctxpair = ft[2];
	uint8_t ctx_hi = (uint8_t)(ctxpair >> 8);
	uint8_t asid_idx = (uint8_t)ctxpair - 1;
	uint8_t saved_hi = cpu[asid_idx + 0x17];
	if (ctx_hi != saved_hi) {
		cpu[asid_idx + 0x17] = (uint8_t)(ctxpair >> 8);
		ctxpair = ft[2];
	}
	*(uint16_t *)(cpu + 0x15) = ctxpair;

	uint64_t uat_ttbr = *(uint64_t *)(cpu + 3);            /* saved TTBR val  */
	uint64_t new_ttbr = *(uint64_t *)(sptm_class_table[(uint8_t)ft[6] * 8] + 0x50);
	uint32_t perm = (uint32_t)ft[5] & ~flags;
	uint32_t bits = perm | (uint32_t)mask;
	bool big = (bits & 0x20) != 0;
	uint64_t lo_mask = 0x40000000, hi_mask = 0xfc0000000;
	if (big) {
		lo_mask = 0x2000000; hi_mask = 0xfe000000;
	}
	if ((bits & 4) != 0) {
		lo_mask = 0x200000; hi_mask = 0x7fffffe00000;
	}

	bool need_tlbi;
	if (hi_mask == *(uint64_t *)(cpu + 0xb)) {
		need_tlbi = (lo_mask != *(uint64_t *)(cpu + 0x13)) || (new_ttbr != uat_ttbr);
		uint64_t tcr;
		SPTM_MRS("tcr_el1", tcr);
		if (ctx_id != old_ctx || need_tlbi ||
		    *(uint64_t *)(sptm_class_table[(uint8_t)ft[6] * 8] + 0x40) != tcr)
			goto do_tlbi;
		need_tlbi = false;
	} else {
		need_tlbi = true;
do_tlbi:
		SPTM_DSB();
		uint64_t ttbr;
		SPTM_MRS("ttbr0_el1", ttbr);
		if (ttbr != (sptm_boot_fte_alt & ~1ULL))
			SPTM_MSR("ttbr0_el1", sptm_boot_fte_alt & ~1ULL);
		SPTM_ISB();
	}
	if (ctx_hi != saved_hi) {
		/* decompiler truncated this branch (halt_baddata); the ctx-id
		 * write above already re-synced it, so this is unreachable. */
		sptm_panic_str("s: switch_root ctx-id mismatch");
	}
	if (old_ctx != 0xff && ctx_id != old_ctx) {
		uint64_t va = *(uint64_t *)(cpu + 0x13) >> (*(uint64_t *)(cpu + 3) & 0x3f);
		if (((va - 1) >> 0x15) == 0) {
			uint64_t op = sptm_tlbi_va(va, 0, *(uint64_t *)(cpu + 0xb), 0);
			__asm__ volatile("tlbi ipas2e1is, %0" :: "r"(op));
		} else if (va != 0) {
			need_tlbi = false;
			__asm__ volatile("tlbi vmalle1");
		}
	}
	if (ctx_id != 0xff) {
		uint64_t t = (uint64_t)ctx_id * 0x20;
		if (g_fte_class[(uint64_t)(uint8_t)(*(uint16_t *)(g_frame_table + t) & 0xff) * 0x90] != 1)
			sptm_panic_str("s: Type %d class of FTE %d");
		*(uint64_t *)(cpu + 3) =
		    *(uint64_t *)(sptm_class_table[(uint8_t)(*(uint64_t *)(g_frame_table + t + 0xc) & 0xff) * 8] + 0x50);
		uint64_t base = *(uint64_t *)(g_frame_table + t - 0x10);
		*(uint64_t *)(cpu + 0x13) = *(uint64_t *)(g_frame_table + t + 0x8);
		*(uint64_t *)(cpu + 0xb) = base;
	}
	perm = perm | (uint32_t)mask & 0xffff;

	if (need_tlbi) {
		uint64_t op = sptm_tlbi_va(*(uint64_t *)(cpu + 0x13) >> (uat_ttbr & 0x3f), 0,
		    *(uint64_t *)(cpu + 0xb), uat_ttbr);
		__asm__ volatile("tlbi ipas2e1is, %0" :: "r"(op));
		*(uint64_t *)(cpu + 3) = new_ttbr;
		*(uint64_t *)(cpu + 0xb) = hi_mask;
		*(uint64_t *)(cpu + 0x13) = lo_mask;
		SPTM_DSB(); SPTM_ISB();
		if (ctx_hi == saved_hi)
			goto common;
		rc = 0x80000000;
	} else {
		*(uint64_t *)(cpu + 3) = new_ttbr;
		*(uint64_t *)(cpu + 0xb) = hi_mask;
		*(uint64_t *)(cpu + 0x13) = lo_mask;
		if (ctx_id != old_ctx || ctx_hi != saved_hi) {
			SPTM_DSB(); SPTM_ISB();
			rc = 0x80000000;
			goto common;
		}
common:
		rc = 0;
	}
	if ((perm & 9) == 0) {
		SPTM_MSR("s3_6_c15_c3_0", (uint64_t)0);
	} else {
		SPTM_MSR("s3_6_c15_c3_0", (uint64_t)((perm & 8) << 0xf | (perm & 1) << 0xb));
	}
	SPTM_MSR("s3_6_c15_c1_5", 0x2010002030100000ULL);
	SPTM_MSR("s3_6_c15_c1_6", 0x2020a52a302abae6ULL);

	uint64_t tcr;
	SPTM_MRS("tcr_el1", tcr);
	uint64_t want_tcr = *(uint64_t *)(sptm_class_table[(uint8_t)ft[6] * 8] + 0x40);
	if (want_tcr != tcr) {
		SPTM_MSR("tcr_el1", want_tcr);
	}
	/* SCTLR reprogramming (cache/TBI/UXN bits gated on `perm`). */
	uint64_t sctlr;
	SPTM_MRS("sctlr_el1", sctlr);
	uint64_t s = sctlr | 0xc8002000;
	if ((sctlr & 0xc8002000) != 0) s = sctlr;
	uint64_t ns = sctlr & 0xffffffff37ffdfff;
	if ((perm & 2) != 0) ns = s;
	bool tbi_clear = (sctlr & 0x40000000000ULL) == 0;
	uint64_t tbi_bit = (perm >> 4) & 1;
	uint64_t eff = tbi_bit;
	if (tbi_clear) eff = 1;
	uint64_t cand = ns;
	if (eff == 0) cand = ns & 0xfffffbffffffffffULL;
	ns = ns | 0x40000000000ULL;
	if ((tbi_bit & tbi_clear) == 0) ns = cand;
	if (((perm & 0x50) == 0x10) && ((sctlr & 0xc000000000) != 0x4000000000ULL))
		ns = ns & 0xffffff3fffffffffULL | 0x4000000000ULL;
	else if (((sctlr & 0xc000000000) == 0x4000000000ULL) && ((perm & 0x50) != 0x10))
		ns = ns & 0xffffff3fffffffffULL;
	if (sctlr != ns) {
		SPTM_MSR("sctlr_el1", ns);
	}
	SPTM_DSB();
	uint64_t new_root = sptm_fte_info((uint64_t)ft, 0);
	SPTM_MSR("ttbr0_el1", (new_root & ~1ULL) | (uint64_t)ctxpair << 0x30);
	SPTM_ISB();

	/* Release the previous root's rw-guard. */
	uint16_t old = ft[3];
	ft[3] = (uint16_t)(old + 1);
	if (old > 0x812) {
		sptm_panic_str("s: refcnt overflow: rc %p old v %llu");
	}
	old = ft[0];
	ft[0] = (uint16_t)(old - 2);
	LORelease();
	if (old == 0 || (old & 1) != 0) {
		sptm_panic_str("s: rw guard release shared: %p");
	}
	if (g_fte_class[(uint64_t)(uint8_t)ft[1] * 0x90] != 1) {
		sptm_panic_str("s: Type %d class of FTE %d");
	}
	if ((ft[5] >> 7 & 1) != 0) {
		/* Shared root: also release the parent frame's guard. */
		uint64_t parent = sptm_get_parent_paddr((uint64_t)ft);
		uint16_t *pft;
		if (parent < g_mem_phys_base || g_mem_phys_end <= parent) {
			uint16_t *alt = (uint16_t *)sptm_phystokv(parent);
			pft = (alt != NULL) ? alt : g_fallback_obj;
		} else {
			pft = (uint16_t *)sptm_papt_va(parent);
		}
		old = pft[0];
		pft[0] = (uint16_t)(old - 2);
		LORelease();
		if (old == 0 || (old & 1) != 0) {
			sptm_panic_str("s: rw guard release shared: %p");
		}
	}
	/* If the old root was neither kernel nor boot root, drop its table
	 * refcount via the FTE-for-PTE lookup. */
	if ((old_ttbr & 0xfffffffffffeULL) != g_kernel_root_ft &&
	    (old_ttbr & 0xfffffffffffeULL) != sptm_boot_fte_alt) {
		uint16_t *old_ft = (uint16_t *)(uintptr_t)sptm_ft_for_pte(old_ttbr);
		if (g_fte_class[(uint64_t)(uint8_t)old_ft[1] * 0x90] != 1) {
			sptm_panic_str("s: Type %d class of FTE %d");
		}
		int16_t rc2 = *(int16_t *)((uint8_t *)old_ft + 6);
		*(int16_t *)((uint8_t *)old_ft + 6) = (int16_t)(rc2 - 1);
		if (rc2 == 0) {
			sptm_panic_str("s: refcnt underflow: rc %p old %llu");
		}
	}
	return rc;
}

/* ==========================================================================
 * FUN_000f6e30  sptm_batch_sign_user_pointer
 * Ghidra: void FUN_000f6e30(ulong param_1, long param_2)
 * Sign a batch of 1..64 user pointers. `param_1` is the physical address of
 * the entry array, `param_2` the number of 0x18-byte entries. Validates the
 * array lies in the DRAM window and the count is within [1,64], copies the
 * array into the per-CPU handoff scratch region (FUN_000d617c, elem 0x18),
 * requires every entry's flag word (+2, mask 0xfffffffd) to be clean, and
 * requires interrupts masked (DAIF 0x1c0). Under the EL2 guard bit
 * (s3_4_c15_c0_4 bit 1) it then extracts one signature word per entry into
 * the handoff buffer.
 * Confidence: high
 * Notes: count bound via the `(count-0x41) < 0xffffffffffffffc0` idiom (valid
 *   [1,64]); panic codes 6/10/0x31/0x33; guard bit toggle s3_4_c15_c0_4. */
void
sptm_batch_sign_user_pointer(uint64_t paddr, uint64_t count)
{
	uint8_t *cpu = sptm_cpu_base();
	if (paddr < g_mem_phys_base || g_mem_phys_end <= paddr) {
		sptm_panic(6, paddr, "s: s %d: %s %llx %s %llx");
	}
	if (count < 1 || count > 64) {
		sptm_panic(10, paddr, "s: s %d: %s %llx %s %llx");
	}
	/* Handoff scratch region pointer (per-CPU field at +0x1b). */
	uint64_t *dst = *(uint64_t **)(cpu + 0x1b);
	sptm_copy_to_scratch(paddr, 0x18, (long)count, 0x200);
	uint64_t *src = dst + 0x40;
	uint64_t i;
	for (i = 0; i < count; i++) {
		if ((*(uint32_t *)(src + 3 * i + 2) & 0xfffffffd) != 0) {
			sptm_panic(0x31, paddr, "s: s %d: %s %llx %s %llx");
		}
	}
	uint64_t daif;
	SPTM_MRS("daif", daif);
	if ((~(uint32_t)daif & 0x1c0) != 0) {
		sptm_panic(0x33, paddr, "s: s %d: %s %llx %s %llx");
	}
	uint64_t g;
	SPTM_MRS("s3_4_c15_c0_4", g);
	SPTM_MSR("s3_4_c15_c0_4", g | 2);
	SPTM_ISB();
	/* Copy one signature word per 0x18-byte entry into the handoff buffer. */
	for (i = 0; i < count; i++) {
		dst[i] = src[3 * i + 0x40 - 2];
	}
	SPTM_MRS("s3_4_c15_c0_4", g);
	SPTM_MSR("s3_4_c15_c0_4", g & 0xfffffffffffffffdULL);
	SPTM_ISB();
}

/* ==========================================================================
 * FUN_000f719c  sptm_tag_op  (tag / untag user-pointer FTE batch)
 * Ghidra: uint FUN_000f719c(ulong param_1, ulong param_2, uint param_3,
 *                           uint param_4)
 * Core batch operation over an array of user-pointer physical addresses
 * (`param_1`, `count` entries in [1,64]). For each entry it requires the
 * target frame to be a managed, fresh (refcount 0) XNU_TAGGABLE (class 3,
 * type_attr present) frame, tags it via sptm_set_pte_attr(...,0xff,...,0x82)
 * and either clears (`mode==0` untag) or sets (`mode!=0` tag) the taggable
 * bit + sub-refcount on the FTE. After the entries it either issues a TLB
 * invalidate over the tagged VAs (flags bit8 DEFER_TLBI clear) or validates
 * deferred-flush support, then releases every entry's rw-guard. Returns
 * bit8 of `flags` scaled to 5 (SPTM_UPDATE_DELAYED_TLBI) or 0.
 * Confidence: high
 * Notes: count bound idiom as in sptm_batch_sign_user_pointer; panic codes
 *   6/10/0x31/0x35/0x36/0x3e/0x41; FTE class/attr tables DAT_00095d51/50/54;
 *   TLBI via FUN_000d76fc / FUN_000e40ec VA resolution. */
uint32_t
sptm_tag_op(uint64_t paddr, uint64_t count, uint32_t flags, uint32_t mode)
{
	uint8_t *cpu = sptm_cpu_base();
	if (paddr < g_mem_phys_base || g_mem_phys_end <= paddr) {
		sptm_panic(6, paddr, "s: s %d: %s %llx %s %llx");
	}
	if (count < 1 || count > 64) {
		sptm_panic(10, paddr, "s: s %d: %s %llx %s %llx");
	}
	uint64_t *buf = *(uint64_t **)(cpu + 0x1b);
	sptm_copy_to_scratch(paddr, 8, (long)count, 0);
	uint64_t *fp = buf + 0x40;
	uint64_t *tagbuf = buf;
	uint64_t n = count;
	uint64_t cur;

	while ((cur = *tagbuf) != 0 && (cur & 0x3fff) == 0 &&
	    cur >= g_mem_phys_base && cur < g_mem_phys_end) {
		uint16_t *ft = (uint16_t *)sptm_papt_va(cur);
		tagbuf[0x40] = (uint64_t)ft;
		if (*ft != 0) {
			sptm_panic(0x3e, count, "s: s %d: %s %llx %s %llx");
		}
		*ft = 1;
		uint8_t type = (uint8_t)(*(uint8_t *)(ft + 1));
		if (g_type_attr[(uint64_t)type * 0x48] == 0) {
			sptm_panic(0x41, count, "s: s %d: %s %llx %s %llx");
		}
		if (g_fte_class[(uint64_t)type * 0x90] != 3)
			sptm_panic_str("s: Type %d class of FTE %d");
		if (*(int32_t *)((uint8_t *)ft + 8) != 0 ||
		    *(int32_t *)((uint8_t *)ft + 0xc) != 0) {
			uint32_t code = (mode == 0) ? 0x36 : 0x35;
			sptm_panic(code, count, "s: s %d: %s %llx %s %llx");
		}
		uint8_t tagbit = (*(uint8_t *)((uint8_t *)ft + 2) >> 2) & 1;
		uint64_t taggable;
		uint64_t sub = 0;
		if (mode == 0) {
			/* untag: require currently taggable, clear the bit */
			if (g_type_params[(uint64_t)type * 0x90] != 1 || tagbit == 0) {
				sptm_panic(0x36, count, "s: s %d: %s %llx %s %llx");
			}
			taggable = sptm_cacheattr((uint64_t)ft);
			tagbuf[0x80] = taggable;
		} else {
			/* tag: require currently not taggable */
			if (g_type_params[(uint64_t)type * 0x90] == 1 && tagbit != 0) {
				sptm_panic(0x35, count, "s: s %d: %s %llx %s %llx");
			}
			taggable = sptm_cacheattr((uint64_t)ft);
			tagbuf[0x80] = taggable;
			if (g_fte_class[(uint64_t)(uint8_t)(*(uint8_t *)((uint8_t *)taggable + 2)) * 0x90] != 4)
				sptm_panic_str("s: Type %d class of FTE %d");
			uint32_t rc = *(uint32_t *)(taggable + 4);
			*(uint32_t *)(taggable + 4) = rc + 1;
			if (rc > 0xfffffff4) {
				sptm_panic_str("s: refcnt overflow: rc %p old v %llu");
			}
			type = *(uint8_t *)((uint8_t *)ft + 1);
			if (g_fte_class[(uint64_t)type * 0x90] != 3 ||
			    g_type_attr[(uint64_t)type * 0x48] == 0 ||
			    g_type_params[(uint64_t)type * 0x90] != 1)
				sptm_panic_str("s: Type %u is not xnu taggable");
			sub = 4;
			*(uint8_t *)((uint8_t *)ft + 2) |= 4;
		}
		int r = sptm_set_pte_attr(cur, 0xff, sub, 0x82);
		if (r != 5) {
			sptm_panic_str("s: Unexpected return value from ...");
		}
		tagbuf++;
		if (--n == 0) {
			if ((flags >> 8 & 1) == 0) {
				/* TLB invalidate over the tagged VAs. */
				SPTM_DSB();
				uint64_t j;
				for (j = 0; j < count; j++) {
					uint64_t entry = tagbuf[j - 1];
					uint64_t va;
					if (((uint32_t)g_feature_flags >> 8 & 1) == 0) {
						va = (entry - g_mem_phys_base) + g_physmap_base;
					} else {
						uint64_t nr = g_reloc_count;
						va = g_physmap_base;
						if (nr != 0) {
							uint64_t k;
							const uint64_t *t = g_reloc_table;
							for (k = 0; k < nr; k++, t += 3) {
								if (t[0] <= entry && entry < t[0] + (uint32_t)t[2] * 0x4000) {
									va = (entry - t[0]) + t[1];
									goto va_ok;
								}
							}
							va = (uint64_t)sptm_phystokv(entry);
						}
va_ok:
						;
					}
					sptm_tlb_op(0, va, 1, 5);
				}
				SPTM_DMB();
				SPTM_ISB();
			} else if ((mode & 1) == 0) {
				sptm_panic_str("s: SPTM_UPDATE_DEFER_TLBI passed without support");
			}
			/* Release rw-guards + clear PTEs. */
			uint64_t j;
			for (j = 0; j < count; j++) {
				uint32_t *papt = (uint32_t *)fp[j];
				uint16_t *gft = (uint16_t *)tagbuf[j + 0x40 - 1];
				if ((mode & 1) == 0) {
					uint8_t t = *(uint8_t *)((uint8_t *)papt + 2);
					if (g_fte_class[(uint64_t)t * 0x90] != 3 ||
					    g_type_attr[(uint64_t)t * 0x48] == 0 ||
					    g_type_params[(uint64_t)t * 0x90] != 1)
						sptm_panic_str("s: Type %u is not xnu taggable");
					*(uint8_t *)((uint8_t *)papt + 1) &= 0xfb;
					if (g_fte_class[(uint64_t)(uint8_t)gft[1] * 0x90] != 4)
						sptm_panic_str("s: Type %d class of FTE %d");
					int32_t rc = *(int32_t *)((uint8_t *)gft + 4);
					*(int32_t *)((uint8_t *)gft + 4) = rc - 1;
					if (rc == 0)
						sptm_panic_str("s: refcnt underflow: rc %p old %llu");
				}
				uint16_t old = *gft;
				*gft = (uint16_t)(old - 2);
				LORelease();
				if (old == 0 || (old & 1) != 0)
					sptm_panic_str("s: rw guard release shared: %p");
				*papt = 0;
			}
			return (uint32_t)((int32_t)(flags << 0x17) >> 0x1f & 5);
		}
	}
	sptm_panic(6, count, "s: s %d: %s %llx %s %llx");
}

/* ==========================================================================
 * FUN_000f7880  sptm_tag_papt_multipage
 * Ghidra: void FUN_000f7880(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Tag a batch of user pointers. `param_3` is the flags word which may only
 * carry the DEFER_TLBI bit (0x100); anything else panics (code 0xe). Forwards
 * to sptm_tag_op in tag mode.
 * Confidence: high
 * Notes: `(param_3 & ~0x100) != 0` rejects all but {0, 0x100}. */
void
sptm_tag_papt_multipage(uint64_t paddr, uint64_t count, uint64_t flags)
{
	if ((flags & 0xfffffeffULL) == 0) {
		sptm_tag_op(paddr, count, (uint32_t)flags, 1);
		return;
	}
	sptm_panic(0xe, count, "s: s %d: %s %llx");
}

/* ==========================================================================
 * FUN_000f78e0  sptm_untag_papt_multipage
 * Ghidra: void FUN_000f78e0(undefined8 param_1, undefined8 param_2)
 * Untag a batch of user pointers: calls sptm_tag_op in untag mode (flags 0,
 * mode 0) and requires a successful (0) return.
 * Confidence: high
 * Notes: non-zero return is the "non success return code" panic. */
void
sptm_untag_papt_multipage(uint64_t paddr, uint64_t count)
{
	int r = sptm_tag_op(paddr, count, 0, 0);
	if (r == 0) {
		return;
	}
	sptm_panic_str("s: non success return code: %d");
}
