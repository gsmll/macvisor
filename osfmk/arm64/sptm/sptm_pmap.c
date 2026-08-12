/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file reconstructs the SPTM page-table engine (the "pmap" core): the
 * functions that manage the secure frame table (FTE), enforce the frame-type
 * transition rules, and walk/modify the guarded page tables. The frame-type
 * rule enforcement in sptm_retype()/sptm_map_page() is the security core of
 * the whole monitor — every transition is checked against per-type parameter
 * tables before any PTE is touched.
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "sptm_internal.h"  /* GENTER/GEXIT, sptm_call_regs_t, sptm_paddr_t */

/* Frame types (values from docs/sptm/headers/sptm_common.h). */
typedef uint8_t sptm_frame_type_t;
enum {
	SPTM_XNU_CODE            = 0x06,
	SPTM_XNU_CODE_DBG_RW     = 0x07,
	SPTM_KERNEL_ROOT_TABLE   = 0x08,
	XNU_USER_JIT             = 0x10,
	XNU_USER_TPRO            = 0x11,
	XNU_USER_ROOT_TABLE      = 0x12,
	XNU_SHARED_ROOT_TABLE    = 0x13,
	XNU_PAGE_TABLE           = 0x14,
	XNU_PAGE_TABLE_SHARED    = 0x15,
	XNU_PAGE_TABLE_COMMPAGE  = 0x17,
	XNU_COMMPAGE_RX          = 0x1f,
	XNU_STAGE2_ROOT_TABLE    = 0x21,
	XNU_SUBPAGE_USER_ROOT_TABLES = 0x28,
	FRAME_TYPE_INVALID       = 0x41,
};

/* sptm_retype_params_t — retype parameters packed in one register (from
 * sptm_common.h). */
typedef union sptm_retype_params {
	struct {
		uint8_t  attr_idx;
		uint8_t  flags;
		uint16_t asid_or_vmid;
		uint32_t pad;
	} fields;
	uint64_t raw;
} sptm_retype_params_t;

typedef uint64_t sptm_pte_t;
typedef uint64_t sptm_tte_t;
typedef uint32_t sptm_return_t;
typedef uint8_t  sptm_pt_level_t;
typedef uint8_t  sptm_map_flags_t;
typedef uint16_t sptm_asid_t;

/* SPTM API return codes (values from sptm_xnu.h). */
enum {
	SPTM_SUCCESS             = 0,
	SPTM_MAP_VALID           = 1,
	SPTM_MAP_FLUSH_PENDING   = 2,
	SPTM_MAP_CODESIGN_ERROR  = 3,
	SPTM_UNMAP_FLUSH_PENDING = 4,
	SPTM_UPDATE_DELAYED_TLBI = 5,
	SPTM_MAP_PADDR_CONFLICT  = 6,
	SPTM_TABLE_NOT_PRESENT   = 7,
	SPTM_TABLE_ALREADY_PRESENT = 8,
};
#define SPTM_MAP_PAGE_NO_OUTPUT 0x01

/* ============================================================================
 * Frame table entry (FTE). The SPTM maintains one 16-byte entry per physical
 * frame. It carries the refcount, the frame type, and per-type flag fields.
 * Base of the frame table: DAT_00095460.
 * ========================================================================== */
typedef union sptm_frame_table_entry {
	struct {
		uint8_t  b[16];
	} bytes;
	struct {
		uint16_t refcnt;        /* +0x00 rw-guard refcount (LOAcquire/LORelease) */
		uint8_t  type;          /* +0x02 frame type */
		uint8_t  flags_a;       /* +0x03 */
		uint32_t word4;         /* +0x04; low byte=byte4, byte6=ctx-id low (puVar[3]) */
		uint16_t sub_refcnt;    /* +0x08 (puVar[4]); byte9 separate */
		uint16_t parent_flags;  /* +0x0a (puVar[5]); bit15 = nested */
		uint16_t attr_idx;      /* +0x0c (puVar[6]) page-table attribute index */
		uint16_t flags_e;       /* +0x0e (puVar[7]) */
	} f;
} sptm_frame_table_entry_t;

/* Convenience: byte at FTE offset +4 is puVar[2]; +6 is puVar[3]; etc. */
#define FTE_B4(ft)      ((uint8_t)((ft)->f.word4))
#define FTE_B5(ft)      ((uint8_t)((ft)->f.word4 >> 8))
#define FTE_B6(ft)      ((uint8_t)((ft)->f.word4 >> 16))   /* puVar[3] low byte */
#define FTE_B7(ft)      ((uint8_t)((ft)->f.word4 >> 24))
#define FTE_B8(ft)      ((uint8_t)((ft)->f.sub_refcnt))    /* puVar[4] low byte */
#define FTE_B10(ft)     ((uint8_t)((ft)->f.parent_flags))  /* puVar[5] low byte */
#define FTE_B12(ft)     ((uint8_t)((ft)->f.attr_idx))      /* puVar[6] low byte */
#define FTE_B14(ft)     ((uint8_t)((ft)->f.flags_e))       /* puVar[7] low byte */

/* 128-bit helper for the frame-type transition bitmasks. */
typedef struct sptm_wide {
	uint64_t lo;
	uint64_t hi;
} sptm_wide_t;

/* A 16-byte return convention matching the decompiler's {x0, x1} pairs. */
typedef struct sptm_ret2 {
	uint64_t lo;    /* value / pointer */
	uint64_t hi;    /* error code */
} sptm_ret2_t;

typedef struct sptm_region_slot sptm_region_slot_t;  /* defined below */

/* ============================================================================
 * SPTM globals (image base 0). Ghidra DAT_ bases in comments.
 * ========================================================================== */
extern sptm_frame_table_entry_t *g_frame_table;      /* DAT_00095460 phys frame table */
extern uint64_t g_sptm_first_phys;                   /* DAT_00095d18 */
extern uint64_t g_sptm_last_phys;                    /* DAT_00095d20 */
extern uint64_t g_dram_lo;                           /* DAT_00095d28 */
extern uint64_t g_dram_hi;                           /* DAT_00095d30 */
extern uint64_t g_kernel_root_ft;                    /* DAT_00095d48 kernel root FTE */
extern uint64_t g_physmap_base;                      /* DAT_00095110 */
extern uint32_t g_feature_flags;                     /* DAT_001012d8 bit8=physmap_ranges */
extern uint64_t g_n_physmap_ranges;                  /* DAT_00101ac8 */
extern uint64_t g_physmap_ranges[];                  /* DAT_00101ad0 {paddr,vaddr,uint count}* */
extern uint64_t g_cpu_pt_attr[];                     /* DAT_00019c68 per-cpu pt-attr table */
extern uint64_t g_uat_state;                         /* DAT_00095d08 UAT context table */
extern uint32_t g_surt_feat;                         /* DAT_00095d38 */
extern uint32_t g_surt_max_asid;                     /* DAT_00095d3c */
extern uint64_t g_bootstrap_stage;                   /* DAT_00095310 */
extern uint64_t g_dram_base;                         /* DAT_000952f8 */
extern uint64_t g_dram_end;                          /* DAT_00095300 */
extern uint8_t *g_sapt;                              /* DAT_000952e8 SAPT perm table */
extern uint64_t g_sapt_present;                      /* DAT_000952e8 base presence flag */
extern uint8_t  g_bootstrap_stage_flag;              /* DAT_00096921 */
extern uint64_t g_asid_bitmap[];                     /* DAT_00102080 */
extern uint8_t  g_shared_region_state[];             /* DAT_00104148 stride 0x20 */
extern uint64_t g_shared_region_papt[];              /* DAT_00104150 stride 4 */
extern uint64_t g_shared_region_size[];              /* DAT_00104158 stride 0x20 */
extern sptm_frame_table_entry_t g_invalid_ft;        /* DAT_00101f90 fallback FTE */
extern uint64_t g_ttba1_ctxid_bmp;                   /* s_ttba1_entry string region */

/* Per-frame-type parameter table, stride 0x90, base DAT_00095d50. */
typedef struct sptm_type_params {
	uint8_t  cache_attr;       /* +0x00 */
	uint8_t  type_class;       /* +0x01 */
	uint8_t  _pad0[4];         /* +0x02..+0x05 */
	uint16_t attr;             /* +0x06 */
	uint8_t  _pad1[0x2a];      /* +0x08..+0x31 */
	uint8_t  flags;            /* +0x31 (DAT_00095d81) */
	uint8_t  flags2;           /* +0x32 (DAT_00095d82) */
	uint8_t  flags3;           /* +0x33 (DAT_00095d83) */
	uint8_t  flags4;           /* +0x34 (DAT_00095d84) */
	uint8_t  _pad2[3];
	uint64_t ft_update;        /* +0x38 fn ptr (DAT_00095d88) */
	uint64_t _pad3;
	uint64_t trans_lo;         /* +0x50 (DAT_00095da0) 128-bit transition mask */
	uint64_t trans_hi;         /* +0x58 (DAT_00095da8) */
	uint16_t preserve;         /* +0x60 (DAT_00095db0) FTE-field preserve mask */
	uint8_t  _pad4[6];
	uint64_t ft_retype;        /* +0x68 fn ptr (DAT_00095db8) */
	uint64_t ft_pre;           /* +0x70 fn ptr (DAT_00095dc0) */
} sptm_type_params_t;
extern sptm_type_params_t g_type_params[];           /* DAT_00095d50 stride 0x90 */

/* Per-frame-type attribute word table, stride 0x48, base DAT_00095d54. */
typedef struct sptm_type_attr {
	uint32_t flags;            /* +0x00 */
} sptm_type_attr_t;
extern sptm_type_attr_t g_type_attr[];               /* DAT_00095d54 stride 0x48 */

/* Page-table geometry descriptor. */
typedef struct sptm_pt_geom {
	uint64_t rsvd[7];          /* +0x00..+0x37 */
	uint64_t level_stride[4];  /* +0x38, indexed level*0x38 */
	uint64_t page_size;        /* +0x48 */
	uint64_t level_shift;      /* +0x50 */
	uint64_t rsvd2[2];         /* +0x58,+0x60 */
	uint64_t tte_mask;         /* +0x68? */
} sptm_pt_geom_t;

/* ============================================================================
 * Helper functions (owned by other trees; declared extern). The Ghidra FUN_
 * address is in each note. FULL-AUDIT: these get bodies in their own trees.
 * ========================================================================== */
extern void           LOAcquire(void);                 /* read-lock an FTE */
extern void           LORelease(void);                 /* read-unlock an FTE */
extern sptm_ret2_t    sptm_get_current_root(uint64_t root_paddr);  /* FUN_000eefd4 */
extern sptm_ret2_t    sptm_ft_for_paddr(uint64_t paddr);/* FUN_000e2480 {ft,err} */
extern sptm_ret2_t    sptm_ft_dynamic(uint64_t paddr); /* FUN_000e3d7c {ft,err} */
extern sptm_ret2_t    sptm_phys_to_virt(uint64_t paddr);            /* FUN_000e40ec {va,err} */
extern sptm_frame_table_entry_t *sptm_ft_for_pte(uint64_t pte);     /* FUN_000e233c */
extern sptm_frame_table_entry_t *sptm_walk(sptm_frame_table_entry_t *root, uint64_t va,
		uint32_t level, uint32_t mode, uint64_t **papt_out);         /* FUN_000e276c */
extern sptm_ret2_t    sptm_root_ft(uint64_t root_paddr);            /* FUN_000ef4e0 */
extern sptm_ret2_t    sptm_shared_ft(uint64_t va);                  /* FUN_000ef8c8 */
extern sptm_ret2_t    sptm_surt_ft(void);                          /* FUN_000f175c */
extern void __attribute__((noreturn)) sptm_shared_mismatch(void);  /* FUN_000e260c */
extern sptm_ret2_t    sptm_root_attr(sptm_frame_table_entry_t *root);  /* FUN_000f0584 */
extern sptm_ret2_t    sptm_parse_region(uint64_t a, uint64_t b, uint64_t max, 
		sptm_frame_table_entry_t *root, uint64_t *count_out);        /* FUN_000f2304 */
extern sptm_ret2_t    sptm_parse_region2(uint64_t a, uint64_t b, uint64_t mask,
		sptm_frame_table_entry_t *root, uint64_t *count_out);        /* FUN_000f4d60 */
extern sptm_ret2_t    sptm_cacheattr(sptm_frame_table_entry_t *ft); /* FUN_000e0a10 */
extern int            sptm_set_pte_attr(uint64_t paddr, uint64_t attr,
		uint64_t cacheattr, uint64_t prot);                          /* FUN_000d7348 */
extern void           sptm_write_pte(sptm_frame_table_entry_t *leaf,
		sptm_frame_table_entry_t *data, uint64_t old_pte, uint64_t new_pte); /* FUN_000e2e2c */
extern void           sptm_clear_pte(sptm_frame_table_entry_t *leaf,
		sptm_frame_table_entry_t *data, uint64_t mode);              /* FUN_000e2c18 */
extern void           sptm_release_table_pair(sptm_frame_table_entry_t *leaf,
		sptm_frame_table_entry_t *data);                             /* FUN_000e3394 */
extern sptm_ret2_t    sptm_tlb_root(sptm_frame_table_entry_t *root);/* FUN_000e2150 */
extern void           sptm_tlb_op(sptm_frame_table_entry_t *root, uint64_t va,
		uint64_t count, uint32_t op);                                /* FUN_000d76fc */
extern uint64_t       sptm_get_parent_paddr(sptm_frame_table_entry_t *ft); /* FUN_000d8a58 */
extern void           sptm_ref_release(uint64_t ref, void *p, uint64_t a, uint64_t b); /* FUN_000ae3e0 */
extern void           sptm_ref_release2(uint64_t ref, void *p, uint64_t a, uint64_t b);/* FUN_000e1acc */
extern sptm_ret2_t    sptm_user_map(uint64_t ctx, uint64_t u11, bool need_iommu,
		uint64_t flags, uint64_t va, uint64_t err);                  /* FUN_000b2638 */
extern void           sptm_asid_bind(uint64_t percpu, uint64_t asid);/* FUN_000b2650 */
extern void           sptm_shared_bind(uint64_t percpu, uint64_t root_va,
		uint64_t id, uint64_t papt, uint64_t size);                  /* FUN_000b2698 */
extern void           sptm_copyin_handoff(uint64_t dst, uint64_t src, uint64_t n,
		uint64_t handoff_base);                                      /* FUN_000d617c */
extern void           DataSynchronizationBarrier(uint64_t a, uint64_t b, uint64_t c);
extern void           DataMemoryBarrier(uint64_t a, uint64_t b);
extern void           InstructionSynchronizationBarrier(void);
extern void           SysOp_W(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t v);
extern uint64_t       sptm_cpu_state_base(void);                     /* UnkSytemRegRead(3,6,0xf,0xb,1) */
extern uint64_t       sptm_cpu_state_alt(void);                      /* tpidr_el2 */
extern void __attribute__((noreturn)) sptm_violation(uint64_t id, uint64_t arg,
		const char *fmt);                                            /* FUN_000f8844 */
extern void __attribute__((noreturn)) sptm_assert_fail(const char *msg); /* FUN_000f8804 */
extern uint64_t       sptm_soft_violation(uint64_t id, uint64_t arg, const char *fmt); /* FUN_000d6124 */

/* ============================================================================
 * Local helpers.
 * ========================================================================== */

/* Physical -> virtual (physmap). Matches the shared idiom: if physmap ranges
 * are enabled scan DAT_00101ad0, else linear physmap, else sptm_phys_to_virt. */
static uint64_t
sptm_paddr_to_vaddr(uint64_t paddr)
{
	uint64_t n;
	const uint64_t *r;

	if (((g_feature_flags >> 8) & 1) == 0) {
		return (paddr - g_sptm_first_phys) + g_physmap_base;
	}
	n = g_n_physmap_ranges;
	r = g_physmap_ranges;
	while (n--) {
		uint64_t rp = r[0];
		if (rp <= paddr && paddr < rp + (uint64_t)(uint32_t)r[2] * 0x4000) {
			return (paddr - rp) + r[1];
		}
		r += 3;
	}
	return sptm_phys_to_virt(paddr).lo;
}

/* Frame-table entry for a physical address (direct index). */
static inline sptm_frame_table_entry_t *
sptm_ft_index(uint64_t paddr)
{
	return (sptm_frame_table_entry_t *)((uint8_t *)g_frame_table +
		(((paddr - g_sptm_first_phys) >> 10) & ~0xfULL));
}

/* Validate a virtual address against a root FTE's geometry (FUN_000ef1f8).
 * Panics (via sptm_violation) if the VA is out of range for the geometry. */
static sptm_ret2_t
sptm_validate_va(uint64_t va, sptm_frame_table_entry_t *root, uint32_t level)
{
	sptm_pt_geom_t *geom = (sptm_pt_geom_t *)g_cpu_pt_attr[FTE_B12(root)];
	uint64_t page_size = geom->page_size;
	uint64_t max_va;

	if (g_type_params[FTE_B4(root)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	if ((page_size - 1) & va) {
		sptm_violation(7, (uint64_t)root, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (level == 3) {
		max_va = geom->rsvd[6];            /* plVar4[0xc] */
	} else {
		uint32_t n_entries = (page_size != 0) ? (uint32_t)(0x4000 / page_size) : 0;
		uint64_t *lvl = (uint64_t *)((uint8_t *)geom + 0x38 + (uint64_t)level * 0x38);
		uint64_t mask = *(uint64_t *)((uint8_t *)lvl + 0x18);
		uint64_t shift = *(uint64_t *)((uint8_t *)lvl + 0x10);
		max_va = geom->rsvd[6];
		if (((uint32_t)(n_entries - 1) &
		     (uint32_t)((max_va & va & mask) >> (shift & 0x3f))) != 0) {
			sptm_violation(7, (uint64_t)root, "%s %s %s %d %s %llx %s %s %llx");
		}
	}
	if (FTE_B4(root) == 8 /* SPTM_KERNEL_ROOT_TABLE */) {
		if ((uint64_t)(-max_va - 2) < va) {
			return (sptm_ret2_t){ va, 0 };
		}
	} else if (va < max_va + 1) {
		return (sptm_ret2_t){ va, 0 };
	}
	sptm_violation(7, (uint64_t)root, "%s %s %s %d %s %llx %s %s %llx");
}

/* 128-bit shift-right of a transition bitmask by n bits. */
static uint64_t
sptm_trans_shift(const sptm_type_params_t *tp, uint64_t n)
{
	uint64_t lo = tp->trans_lo;
	uint64_t hi = tp->trans_hi;
	if (n >= 64) {
		return hi >> (n & 0x3f);
	}
	return (hi << 1) << ((~n) & 0x3f) | lo >> (n & 0x3f);
}

/* 128-bit shift-right of the "wide" transition bitmask (DAT_00095d90/d98). */
static uint64_t
sptm_wide_shift(const sptm_type_params_t *tp, uint64_t n)
{
	uint64_t lo = *(uint64_t *)((uint8_t *)tp + 0x40);   /* DAT_00095d90 */
	uint64_t hi = *(uint64_t *)((uint8_t *)tp + 0x48);   /* DAT_00095d98 */
	if (n >= 64) {
		return hi >> (n & 0x3f);
	}
	return (hi << 1) << ((~n) & 0x3f) | lo >> (n & 0x3f);
}

/* Common per-type FTE flag field preservation: write the byte only when the
 * type's "preserve" bitmask (DAT_00095db0) has the corresponding bit set. */
static uint8_t
sptm_preserve_byte(const sptm_type_params_t *tp, uint8_t newval, unsigned bit)
{
	return ((tp->preserve >> bit) & 1) ? newval : 0;
}

/* Per-CPU trace-counter string regions (string symbols reused as counters). */
extern uint8_t s_ttba1_entry[];        /* "ttba1_entry" */
extern uint8_t s_valid_ctx[];          /* "Valid context ID but the TTB..." */
extern uint8_t s_uat_remove[];         /* "sptm_uat_remove_ctx_id" */
extern uint64_t g_sapt_perm_fn_table[];/* DAT_00015d78 per-stage perm callbacks */
extern uint8_t  g_perm_allow_table[];  /* DAT_00013438 perm-allowed bitset (stride 2) */
extern uint8_t  g_perm_deny_table[];   /* DAT_00013458 perm-denied bitset (stride 2) */
extern uint64_t g_perm_delay_table[];  /* DAT_00013608 per-perm flags (stride 8) */
extern void sptm_tlb_flush1(uint64_t va, uint64_t size);   /* FUN_000aba24 */

/* The region/disjoint-op update callbacks (owned by the update paths). */
extern int  sptm_update_preflight(sptm_region_slot_t *, uint64_t, uint64_t, uint32_t, uint64_t *);
extern void sptm_update_finalize(sptm_region_slot_t *, uint64_t, uint64_t, uint32_t);
extern sptm_return_t sptm_disjoint_op(sptm_paddr_t, sptm_paddr_t, unsigned int, uint32_t,
		int (*)(sptm_region_slot_t *, uint64_t, uint64_t, uint32_t, uint64_t *),
		void (*)(sptm_region_slot_t *, uint64_t, uint64_t, uint32_t));

/* ============================================================================
 * sptm_retype — FUN_000ed6b4
 *
 * Ghidra: void FUN_000ed6b4(ulong paddr, ulong current_type, ulong new_type,
 *                           undefined8 retype_params)
 *
 * The heart of the SPTM type system: transitions a single physical frame from
 * [current_type] to [new_type]. The frame must be unreferenced (refcount 0).
 * The transition is validated against the per-type parameter tables (the
 * 128-bit transition bitmask, per-type class checks, and the per-type
 * pre/retype callbacks) BEFORE any state is committed. On any violation the
 * monitor panics — this operation cannot fail gracefully (per the SDK header).
 *
 * Security: this is where frame-type confusion is prevented. A frame may only
 * move along an edge present in its source type's transition bitmask; the
 * current-type-class checks (e.g. "CPU pages may only become CPU pages") and
 * the UAT context-id teardown enforce that retyping a live CPU/user-root page
 * cannot leave stale context IDs in the UAT.
 * Confidence: high (SDK header name + full decompile)
 */
void
sptm_retype(sptm_paddr_t paddr, sptm_frame_type_t current_type,
            sptm_frame_type_t new_type, sptm_retype_params_t retype_params)
{
	uint64_t cpu;
	sptm_frame_table_entry_t *fte;
	uint16_t rc;
	uint8_t ft_type;
	uint64_t new_type_v = new_type & 0xff;
	bool cpu_taggable;
	uint8_t out[2];
	uint64_t t;

	/* paddr must be page-aligned and within the managed DRAM window. */
	if (((paddr & 0x3fff) != 0 || paddr < g_sptm_first_phys) || g_sptm_last_phys <= paddr) {
		sptm_violation(6, current_type, "%s %s %s %d %s %llx %s %s %llx");
	}
	/* both types must be within the valid type-id range (<= 0x41). */
	if ((0x41 < (current_type & 0xff)) || (0x41 < (new_type_v))) {
		sptm_violation(9, current_type, "%s %s %s %d %s %llx %s %s %llx");
	}

	cpu = sptm_cpu_state_base();
	*(uint64_t *)(s_ttba1_entry + cpu + 5) += 1;

	/* Locate the FTE. */
	if (paddr < g_sptm_first_phys || g_sptm_last_phys <= paddr) {
		sptm_ret2_t r = sptm_ft_dynamic(paddr);
		fte = r.lo ? (sptm_frame_table_entry_t *)r.lo : &g_invalid_ft;
	} else {
		fte = sptm_ft_index(paddr);
	}

	/* The frame must be unreferenced; claim it. */
	rc = fte->f.refcnt;
	if (rc == 0) {
		fte->f.refcnt = 1;
	}
	if (rc != 0) {
		sptm_violation(0x3e, current_type, "%s %s %s %d %s %llx %s %s %llx");
	}

	ft_type = fte->f.type;

	/* If a source type is requested, the per-CPU attribute byte must match the
	 * current type's cache-attribute entry. */
	if ((current_type & 0xff) != 0) {
		cpu = sptm_cpu_state_base();
		if (*(char *)(cpu + 0xa30) != (char)g_type_params[ft_type].cache_attr) {
			sptm_violation(0x40, current_type, "%s %s %s %d %s %llx %s %s %llx");
		}
	}
	/* The current FTE type must equal the requested current_type. */
	if (ft_type != (current_type & 0xff)) {
		sptm_violation(0x42, current_type, "%s %s %s %d %s %llx %s %s %llx");
	}

	/* The new_type must be a valid transition edge of the current type
	 * (128-bit transition bitmask). */
	t = sptm_wide_shift(&g_type_params[ft_type], new_type_v);
	if ((t & 1) == 0) {
		sptm_violation(0x17, current_type, "%s %s %s %d %s %llx %s %s %llx");
	}

	/* If the source is not a "leaf data" class (class != 6) the frame must
	 * already be referenced before we proceed. */
	if ((g_type_params[current_type & 0xff].type_class != 6) && (fte->f.refcnt == 0)) {
		sptm_assert_fail("Frame expected to have been a ");
	}

	/* Flag check: if the current type forbids (flags&3) and the FTE byte-6
	 * "in use" bit is set, the transition is illegal. */
	{
		uint8_t inuse;
		if (((g_type_params[current_type & 0xff].flags >> 2) & 1) == 0) {
			inuse = (FTE_B6(fte) >> 1) & 1;
		} else {
			inuse = 1;
		}
		if (((g_type_params[current_type & 0xff].flags & 3) != 0) && (inuse != 0)) {
			sptm_violation(0x18, current_type, "%s %s %s %d %s %llx %s %s %llx");
		}
	}

	/* Per-type pre-transition callback. */
	((void (*)(sptm_frame_table_entry_t *, uint64_t))g_type_params[ft_type].ft_pre)(fte, new_type_v);

	/* UAT context-ID teardown: retyping away a CPU/user-root page that still
	 * holds a context ID must invalidate that ASID in the UAT. */
	if ((g_uat_state != 0) && ((*(uint8_t *)(g_uat_state + 0x80) & 1) != 0) &&
	    (g_type_params[current_type & 0xff].type_class == 3)) {
		if ((fte->f.refcnt & 1) == 0) {
			sptm_assert_fail("FTE %p should be held exclus");
		}
		if (g_type_params[(uint8_t)fte->f.type].type_class != 3) {
			sptm_assert_fail("Only CPU pages may need a GM");
		}
		uint16_t ctx = fte->f.word4 >> 16;   /* puVar15[3] = UAT ctx id */
		if ((ctx & 0xc000) != 0) {
			if (ctx < 0xc000) {
				uint64_t cid = (ctx >> 8) & 0x3f;
				if (((ctx & 0xc000) == 0x4000) &&
				    (*(uint8_t *)(g_uat_state + cid * 2 + 0x83) != (ctx & 0xff))) {
					cpu = sptm_cpu_state_base();
					*(uint64_t *)(s_valid_ctx + cpu + 6) += 1;
				} else {
					*(uint8_t *)(g_uat_state + cid * 2 + 0x82) += 1;
					DataSynchronizationBarrier(0, 2, 0);
					SysOp_W(0, 9, 1, 2, cid << 0x30);
					DataSynchronizationBarrier(0, 3, 1);
					*(uint8_t *)(g_uat_state + cid * 2 + 0x83) += 1;
					cpu = sptm_cpu_state_base();
					*(uint64_t *)(s_uat_remove + cpu + 1) += 1;
				}
			} else if (((ctx & 0x3f00) == 0) &&
			           (*(uint8_t *)(g_uat_state + 0x103) != (ctx & 0xff))) {
				cpu = sptm_cpu_state_base();
				*(uint64_t *)(s_valid_ctx + cpu + 0xe) += 1;
			} else {
				uint64_t i;
				for (i = 0x82; i != 0x102; i += 2) {
					*(char *)(g_uat_state + i) += 1;
				}
				*(char *)(g_uat_state + 0x102) += 1;
				DataSynchronizationBarrier(0, 2, 0);
				SysOp_W(4, 9, 1, 4, 0);
				DataSynchronizationBarrier(0, 3, 1);
				for (i = 0x83; i != 0x103; i += 2) {
					*(char *)(g_uat_state + i) += 1;
				}
				*(char *)(g_uat_state + 0x103) += 1;
				cpu = sptm_cpu_state_base();
				*(uint64_t *)(s_uat_remove + cpu + 9) += 1;
			}
		}
	}

	/* CPU-page taggability: a taggable CPU page may only transition to another
	 * taggable CPU page. */
	if ((g_type_params[ft_type].type_class == 3) &&
	    (g_type_attr[ft_type].flags != 0) &&
	    (g_type_params[ft_type].cache_attr == 1) &&
	    (((FTE_B4(fte) >> 2) & 1) != 0)) {
		if ((g_type_params[new_type_v].type_class != 3) ||
		    (g_type_attr[new_type_v].flags == 0) ||
		    (g_type_params[new_type_v].cache_attr != 1)) {
			sptm_violation(0x38, 0, "%s %s %s %d %s %llx %s %s %llx");
		}
		cpu_taggable = true;
	} else {
		cpu_taggable = false;
	}

	/* Preserve type-specific FTE flag fields per the current type's mask;
	 * otherwise zero them. */
	{
		uint8_t *fb = fte->bytes.b;
		fb[4]  = sptm_preserve_byte(&g_type_params[ft_type], fb[4],  4);
		fb[5]  = sptm_preserve_byte(&g_type_params[ft_type], fb[5],  5);
		fb[6]  = sptm_preserve_byte(&g_type_params[ft_type], fb[6],  6);
		fb[7]  = sptm_preserve_byte(&g_type_params[ft_type], fb[7],  7);
		fb[8]  = sptm_preserve_byte(&g_type_params[ft_type], fb[8],  8);
		fb[9]  = sptm_preserve_byte(&g_type_params[ft_type], fb[9],  9);
		fb[10] = sptm_preserve_byte(&g_type_params[ft_type], fb[10], 10);
		fb[11] = sptm_preserve_byte(&g_type_params[ft_type], fb[11], 11);
		fb[12] = sptm_preserve_byte(&g_type_params[ft_type], fb[12], 12);
		fb[13] = sptm_preserve_byte(&g_type_params[ft_type], fb[13], 13);
		fb[14] = sptm_preserve_byte(&g_type_params[ft_type], fb[14], 14);
		fb[15] = sptm_preserve_byte(&g_type_params[ft_type], fb[15], 15);
	}

	/* Per-type retype callback produces the cache attribute (and prot byte). */
	memset(out, 0, sizeof(out));
	((void (*)(sptm_frame_table_entry_t *, uint64_t, uint64_t, uint8_t *))g_type_params[new_type_v].ft_retype)
		(fte, new_type_v, (uint64_t)retype_params.raw, out);
	if (cpu_taggable) {
		if (out[0] != 0) {
			sptm_assert_fail("Unsupported cacheattr index ");
		}
		out[0] = 4;
	}
	fte->f.type = (uint8_t)new_type;
	sptm_set_pte_attr(paddr, g_type_params[new_type_v].attr, out[0],
	                  ((out[1] & 1) << 6) | 3);

	/* Table types (attr flags & 0x2020) need a TLB flush of the page. */
	if ((g_type_attr[new_type_v].flags & 0x2020) != 0) {
		sptm_tlb_flush1(sptm_paddr_to_vaddr(paddr), 0x4000);
	}

	/* Update the SAPT permission bits for DRAM frames. */
	if (g_uat_state != 0) {
		if (((g_feature_flags >> 0xb) & 1) == 0) {
			sptm_assert_fail("Expected bootstrap stages no");
		}
		uint64_t (*perm_fn)(uint64_t, uint64_t) =
			(uint64_t (*)(uint64_t, uint64_t))g_sapt_perm_fn_table[g_bootstrap_stage * 0x28];
		if (perm_fn != NULL) {
			uint64_t perm = perm_fn(new_type_v, paddr);
			if (perm > 3) {
				sptm_assert_fail("Invalid permission specified ");
			}
			if ((paddr < g_dram_base) || (g_dram_end <= paddr)) {
				sptm_assert_fail("Address 0x%llx not within DR");
			}
			uint64_t idx = (paddr - g_dram_base) >> 0x10;
			uint64_t shift = (paddr - g_dram_base) >> 0xd & 6;
			uint64_t cur = g_sapt[idx];
			while ((cur >> shift & 3) != perm) {
				uint8_t *p = &g_sapt[idx];
				uint8_t old = *p;
				if (old == (uint8_t)cur) {
					*p = ((uint8_t)cur & ~(uint8_t)(3 << shift)) | (uint8_t)(perm << shift);
				}
				bool did = (old == (uint8_t)cur);
				cur = old;
				if (did) {
					if (g_sapt == 0) {
						sptm_assert_fail("SAPT not bootstrapped ");
					}
					DataSynchronizationBarrier(0, 3, 1);
					/* paddr==0 case: decompiler hit bad-instruction data here;
					 * control flow truncated (halt). */
					break;
				}
			}
		}
	}

	/* Table types: per-type "update" callback on the (physmap) virtual address. */
	if ((g_type_attr[new_type_v].flags & 0x2020) != 0) {
		((void (*)(sptm_frame_table_entry_t *, uint64_t))g_type_params[new_type_v].ft_update)
			(fte, sptm_paddr_to_vaddr(paddr));
	}

	/* Re-tag: a taggable CPU page gets its taggable flag (byte4 bit2) set. */
	if (cpu_taggable) {
		uint8_t t2 = fte->f.type;
		if ((g_type_params[t2].type_class != 3) ||
		    (g_type_attr[t2].flags == 0) ||
		    (g_type_params[t2].cache_attr != 1)) {
			sptm_assert_fail("Type %u is not xnu taggable ");
		}
		fte->f.word4 |= 4;
	}

	/* Release the claim. */
	fte->f.refcnt = 0;
	fte->f.type = 0;
}

/* ============================================================================
 * sptm_map_page — FUN_000ee278
 *
 * Ghidra: undefined8 FUN_000ee278(undefined8 root_paddr, undefined8 vaddr,
 *                                 ulong new_pte, byte flags)
 *
 * Installs or updates a single leaf PTE in the page table rooted at the
 * current root. This is the primary kernel entry point for mapping a page.
 *
 * Security: the mapping is vetted BEFORE any PTE is written — the leaf table's
 * type must permit the data frame's type (frame-type transition rule via
 * g_type_params[leaf].trans_*), the requested permission bits must be allowed
 * for the data frame type, and W+X / NXS combinations are rejected. On any
 * violation the monitor panics; only non-security bit-state conditions return
 * an error code.
 * Confidence: high (SDK header name + full decompile)
 */
sptm_return_t
sptm_map_page(sptm_paddr_t root_pt_paddr, sptm_vaddr_t vaddr,
              sptm_pte_t new_pte, sptm_map_flags_t flags)
{
	sptm_frame_table_entry_t *root, *leaf, *data_ft;
	sptm_frame_table_entry_t *out_ft = NULL;
	sptm_ret2_t r;
	uint64_t *papt;
	uint64_t pa, cur, merged, t;
	uint8_t b2, b3;
	uint64_t perm_idx, v5, result = 0, extra_x1 = 0;
	uint32_t attrs;
	uint16_t rc, sub_rc;
	uint64_t cpu;

	if (1 < flags) {
		sptm_violation(0x10, vaddr, "%s %s %s %d %s %llx");
	}
	root = (sptm_frame_table_entry_t *)sptm_get_current_root(root_pt_paddr).lo;
	r = sptm_validate_va(vaddr, root, 3);
	extra_x1 = r.hi;

	if (g_type_params[FTE_B4(root)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	if (r.lo < *(uint64_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x58)) {
		sptm_violation(7, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
	}

	/* Validate the new PTE encoding. */
	if (((~new_pte & 3) != 0) || ((new_pte >> 0x34 & 1) != 0) ||
	    ((new_pte & 0xf38b000000000000ULL) != 0)) {
		sptm_violation(0x22, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
	}
	pa = new_pte & 0xfffffffff000ULL;
	if (((*(uint64_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x48) - 1 | 0xfc0000000000ULL) & pa) != 0) {
		sptm_violation(6, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
	}

	papt = NULL;
	leaf = sptm_walk(root, r.lo, 3, 0, &papt);
	if (leaf == NULL) {
		result = SPTM_TABLE_NOT_PRESENT;   /* uVar9 = 7 */
		goto release_root;
	}

	/* Validate the target physical address' frame type. */
	r = sptm_ft_for_paddr(pa);
	extra_x1 = r.hi;
	data_ft = (sptm_frame_table_entry_t *)r.lo;
	if ((pa < g_dram_hi && g_dram_lo <= pa) || (data_ft->f.type != 0)) {
		if (data_ft->f.type == 0x27 /* XNU_RESTRICTED_IO_TELEMETRY */) {
			result = 0xff000002;
			sptm_soft_violation(result, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
			extra_x1 = result;
			goto release_root;
		}
	} else {
		result = 0xff000000;
		sptm_soft_violation(result, extra_x1, "%s %s %s %llx");
		extra_x1 = result;
		goto release_root;
	}

	attrs = new_pte & 0x1c;
	if (attrs == 0x10) {
		/* CPU-page mapping: data frame must be a taggable CPU page. */
		r = sptm_cacheattr(data_ft);
		extra_x1 = data_ft->f.type;
		uint64_t dt = data_ft->f.type;
		if ((g_type_params[dt].type_class != 3) ||
		    (g_type_attr[dt].flags == 0) ||
		    (g_type_params[dt].cache_attr != 1 || (((FTE_B4(data_ft) >> 2) & 1) == 0))) {
			sptm_violation(0x37, r.hi, "%s %s %s %d %s %llx %s %s %llx");
		}
	} else {
		extra_x1 = 0;
	}
	uint64_t out_ft_v = extra_x1;
	(void)out_ft_v;

	b2 = data_ft->f.type;
	extra_x1 = b2;
	if (g_type_attr[b2].flags == 0) {
		sptm_violation(0x41, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
	}

	/* Frame-type rule: the leaf table's type must permit mapping this data type. */
	t = sptm_trans_shift(&g_type_params[FTE_B4(leaf)], b2);
	if ((t & 1) == 0) {
		sptm_violation(0x28, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
	}

	/* Permission check. */
	b3 = FTE_B4(root);
	uint64_t perm = new_pte >> 0x35 & 3;
	perm_idx = (new_pte >> 4 & 0xc) | perm;
	v5 = perm_idx;
	if (b3 != XNU_STAGE2_ROOT_TABLE) {
		if (((g_type_attr[b2].flags >> perm_idx) & 1) == 0) {
			sptm_violation(0x24, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
		}
		if (((b3 != SPTM_KERNEL_ROOT_TABLE) && (b3 != XNU_SHARED_ROOT_TABLE)) &&
		    (((new_pte >> 0xb) & 1) == 0) && (FTE_B4(leaf) != XNU_PAGE_TABLE_COMMPAGE)) {
			sptm_violation(0x22, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
		}
		if ((b3 != SPTM_KERNEL_ROOT_TABLE) && ((v5 & 7) == 3)) {
			sptm_violation(0x24, extra_x1, "%s %s %s %d %s %llx %s %s %llx");
		}
	}

	cur = *papt;
	uint64_t old_pte = 0;
	uint32_t old_low = 0;
	if ((g_type_params[(uint8_t)b2].flags2 & 1) == 0) {
		/* ---- non-IOMMU path: merge/update the leaf PTE ---- */
		for (;;) {
			uint64_t old = cur;
			uint32_t low = old & 3;
			old_pte = old;
			old_low = low;
			if (old == new_pte) {
				result = SPTM_MAP_VALID;
				cur = old;
				goto after_write;
			}
			if ((low != 3) && (((old >> 7) & 1) != 0)) {
				result = SPTM_MAP_FLUSH_PENDING;
				cur = old;
				goto after_write;
			}
			merged = new_pte;
			if (low == 3) {
				if ((old & 0xfffffffff000ULL) != pa) {
					result = SPTM_MAP_PADDR_CONFLICT;
					cur = old;
					goto after_write;
				}
				if (b3 != XNU_STAGE2_ROOT_TABLE) {
					uint64_t old_perm = (old >> 4 & 0xc) | (old >> 0x35 & 3);
				if ((old_perm != perm_idx) &&
				    ((1 << perm_idx & (uint32_t)(*(uint16_t *)((uint16_t *)&g_perm_allow_table + old_perm))) == 0) &&
				    ((1 << perm_idx & (uint32_t)(*(uint16_t *)((uint16_t *)&g_perm_deny_table + old_perm))) == 0)) {
						sptm_violation(0x19, result, "%s %s %s %d %s %llx %s %s %llx");
					}
				}
				merged = (old & 0xf39fffffffffff3fULL) | (new_pte & 0xc600000000000c0ULL);
			}
			uint64_t wnx = merged & 0x80;
			if (b3 != XNU_STAGE2_ROOT_TABLE) {
				wnx = 1ULL << ((merged >> 4 & 0xc) | (merged >> 0x35 & 3)) & 0x2a8;
			}
			uint64_t m = merged;
			if (wnx != 0) {
				m = merged & 0xf7ffffffffffffffULL;
			}
			if ((merged & 0x800000000000000ULL) != 0) {
				merged = m;
			}
			cur = *papt;
			if (*papt == old) {
				break;
			}
		}
		*papt = merged;
		if (old_low == 3) {
			if (b3 == XNU_STAGE2_ROOT_TABLE) {
				if ((old_pte & 0x803) == 3) {
					sptm_assert_fail("FNXS is expected to be set");
				}
				DataSynchronizationBarrier(2, 2, 0);
				uint64_t tf = sptm_tlb_root(root).lo;
				sptm_tlb_op((sptm_frame_table_entry_t *)tf, r.lo, 1, 5);
				sptm_write_pte(leaf, data_ft, old_pte, merged);
				DataSynchronizationBarrier(2, 3, 1);
			} else {
				DataSynchronizationBarrier(2, 2, 0);
				uint64_t tf = sptm_tlb_root(root).lo;
				uint64_t op = 5;
				if ((old_pte & 0x14) == 0x14) {
					op = 1;
				}
				sptm_tlb_op((sptm_frame_table_entry_t *)tf, r.lo, 1, op);
				sptm_write_pte(leaf, data_ft, old_pte, merged);
				if ((old_pte & 0x14) != 0x14) {
					DataSynchronizationBarrier(2, 3, 1);
				} else {
					DataSynchronizationBarrier(2, 3, 0);
				}
			}
			InstructionSynchronizationBarrier();
			result = SPTM_MAP_VALID;
			cur = old_pte;
			goto after_write;
		}
		DataMemoryBarrier(2, 3);
		InstructionSynchronizationBarrier();
		sptm_write_pte(leaf, data_ft, old_pte, merged);
		if (attrs == 0x10) {
			/* Bump the data frame's mapping refcount (uint at +4). */
			if (g_type_params[FTE_B4(out_ft)].type_class != 4) {
				sptm_assert_fail("Type %d class of FTE %p %d");
			}
			uint32_t n = data_ft->f.word4;
			data_ft->f.word4 = n + 1;
			if (0xfffffff4 < n) {
				sptm_assert_fail("refcnt overflow rc=%d p old v %d");
			}
			result = SPTM_SUCCESS;
			goto release_cpu;
		}
		result = SPTM_SUCCESS;
	} else {
		/* ---- IOMMU path ---- */
		uint16_t u11;
		if (b2 == XNU_COMMPAGE_RX) {
			u11 = 0;
		} else if (b3 == XNU_USER_TPRO) {
			if (g_type_params[b3].type_class != 1) {
				sptm_assert_fail("Type %d class of FTE %p %d");
			}
			u11 = FTE_B8(root);
		} else {
			if (g_type_params[b3].type_class != 1) {
				sptm_assert_fail("Type %d class of FTE %p %d");
			}
			u11 = root->f.sub_refcnt;
		}
		uint64_t u15;
		if (v5 - 3 < 0xd) {
			u15 = g_perm_delay_table[v5 - 3];
			if (v5 > 7) {
				goto perm_tail;
			}
		} else {
			u15 = 0;
			if (v5 < 8) {
				/* fallthrough to perm check */
				if ((1 << perm_idx & 0xa8U) == 0) {
					goto perm_tail;
				}
			} else {
perm_tail:
				u15 = new_pte >> 0x3a & 2;
			}
		}
		uint64_t cf = 4;
		if (((new_pte >> 4 & 4) | perm) != 5) {
			cf = 0;
		}
		cpu = sptm_cpu_state_base();
		r = sptm_user_map(*(uint64_t *)(cpu + 0xa58), u11, b2 == XNU_COMMPAGE_RX || b3 == XNU_USER_TPRO,
		                  u15 | (new_pte >> 0x3a & 2) | cf, pa, r.lo);
		result = r.hi;
		if (r.lo == 0) {
			goto release_after_iommu_fail;
		}
		result = SPTM_MAP_CODESIGN_ERROR;
		cur = *papt;
		goto after_write;
	}

after_write:
	/* Release data-frame refcount for CPU-page mappings. */
	if (attrs == 0x10) {
release_cpu:
		sub_rc = data_ft->f.sub_refcnt;
		data_ft->f.sub_refcnt = sub_rc - 2;
		LORelease();
		if (sub_rc == 0 || (sub_rc & 1) != 0) {
			sptm_assert_fail("rw_guard_release_shared");
		}
	}
	/* Release the data frame. */
	if (g_type_params[FTE_B4(data_ft)].type_class != 6) {
		if ((g_type_params[FTE_B4(data_ft)].flags3 & 1) == 0) {
			data_ft->f.refcnt = 0;
			data_ft->f.type = 0;
		} else {
			sub_rc = data_ft->f.refcnt;
			data_ft->f.refcnt = sub_rc - 2;
			LORelease();
			if (sub_rc == 0 || (sub_rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
	}
	if (leaf != root) {
		sub_rc = leaf->f.refcnt;
		leaf->f.refcnt = sub_rc - 2;
		LORelease();
		if (sub_rc == 0 || (sub_rc & 1) != 0) {
			sptm_assert_fail("rw_guard_release_shared");
		}
	}
release_after_iommu_fail:
	goto release_root;

release_root:
	rc = root->f.refcnt;
	root->f.refcnt = rc - 2;
	LORelease();
	bool ok = (rc & 1) == 0;
	if (((char)FTE_B4(root) == XNU_USER_TPRO) || ((char)FTE_B4(root) != XNU_USER_ROOT_TABLE)) {
		if (ok && rc != 0) {
			return (sptm_return_t)result;
		}
	} else if (ok && rc != 0) {
		if (g_type_params[FTE_B4(root)].type_class != 1) {
			sptm_assert_fail("Type %d class of FTE %p %d");
		}
		if ((root->f.parent_flags >> 7) & 1) {
			uint64_t pp = sptm_get_parent_paddr(root);
			sptm_frame_table_entry_t *pf;
			if (pp < g_sptm_first_phys || g_sptm_last_phys <= pp) {
				pf = &g_invalid_ft;
			} else {
				pf = sptm_ft_index(pp);
			}
			rc = pf->f.refcnt;
			pf->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
		return (sptm_return_t)result;
	}
	sptm_assert_fail("rw_guard_release_shared");
}

/* ============================================================================
 * sptm_map_table — FUN_000efa78
 *
 * Ghidra: undefined8 FUN_000efa78(undefined8 root_paddr, undefined8 vaddr,
 *                                 byte target_level, ulong new_tte)
 *
 * Installs a page-table page at [target_level] for [vaddr]. The new table page
 * must be a freshly-retyped page table (type class 2) already typed at level
 * [target_level]+1 (byte4 == level+1); the parent table type must permit the
 * transition. Installs one TTE per geometry page into the parent table.
 * Confidence: high (SDK header name + full decompile)
 */
sptm_return_t
sptm_map_table(sptm_paddr_t root_pt_paddr, sptm_vaddr_t vaddr,
               sptm_pt_level_t target_level, sptm_tte_t new_tte)
{
	sptm_frame_table_entry_t *root, *parent_ft, *data_ft, *tmp;
	sptm_ret2_t r;
	uint64_t *papt;
	uint64_t tte_pa, bit_lo, bit_hi;
	uint64_t page_size;
	uint16_t rc;
	uint8_t b4, b5;
	uint64_t err, result = 0;

	root = (sptm_frame_table_entry_t *)sptm_get_current_root(root_pt_paddr).lo;
	if (g_type_params[FTE_B4(root)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	if ((2 < target_level) ||
	    (target_level < *(uint8_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x38))) {
		sptm_violation(1, 0, "%s %s %s %d %s %llx %s %s %llx");
	}
	r = sptm_validate_va(vaddr, root, target_level);
	err = r.hi;
	if ((~new_tte & 3) != 0) {
		sptm_violation(0x23, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (g_type_params[FTE_B4(root)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	tte_pa = new_tte & 0xfffffffff000ULL;
	if (((*(uint64_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x48) - 1 | 0xfc0000000000ULL) & tte_pa) != 0) {
		sptm_violation(6, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (((new_tte & 0x3000) != 0) || ((new_tte & 0x7ff000000000fdcULL) != 0)) {
		sptm_violation(0x23, err, "%s %s %s %d %s %llx %s %s %llx");
	}

	papt = NULL;
	r = (sptm_ret2_t){ (uint64_t)sptm_walk(root, r.lo, target_level, 1, &papt), err };
	parent_ft = (sptm_frame_table_entry_t *)r.lo;
	if (parent_ft == NULL) {
		sptm_violation(0x23, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}

	/* Locate the new table's FTE and claim it. */
	if (tte_pa < g_sptm_first_phys || g_sptm_last_phys <= tte_pa) {
		sptm_ret2_t dr = sptm_ft_dynamic(tte_pa);
		data_ft = dr.lo ? (sptm_frame_table_entry_t *)dr.lo : &g_invalid_ft;
	} else {
		data_ft = sptm_ft_index(tte_pa);
	}
	LOAcquire();
	rc = data_ft->f.refcnt;
	data_ft->f.refcnt = rc + 2;
	if ((0xffe9 < rc) || ((rc & 1) != 0)) {
		sptm_violation(0x3d, err, "%s %s %s %llx");
	}
	b4 = data_ft->f.type;
	if (b4 == XNU_PAGE_TABLE_COMMPAGE) {
		/* Commpage tables may be shared across geometries. */
		sptm_ret2_t ra = sptm_root_attr(root);
		sptm_pt_geom_t *geom = (sptm_pt_geom_t *)g_cpu_pt_attr[*(uint8_t *)(ra.lo + 8)];
		uint64_t entries = geom->page_size ? 0x4000 / geom->page_size : 0;
		uint64_t off = -(entries * *(uint64_t *)((uint8_t *)&geom->level_stride + target_level * 0x38));
		sptm_ret2_t ra2 = sptm_root_attr(root);
		uint16_t fl = *(uint16_t *)(ra2.lo + 6);
		bool big = (fl & 0x20) != 0;
		uint64_t lo = big ? 0x2000000 : 0x40000000;
		uint64_t hi = big ? 0xfe000000 : 0xfc0000000ULL;
		uint64_t t = hi & off;
		if ((fl & 4) != 0) {
			lo = 0x200000;
			t = off & 0x7fffffe00000ULL;
		}
		uint64_t va = r.lo & off;
		if ((va < t) || (t + lo < *(uint64_t *)((uint8_t *)&geom->level_stride + target_level * 0x38) + va)) {
			sptm_violation(0x4f, err, "%s %s %s %d %s %llx %s %s %llx");
		}
		b5 = data_ft->f.type;
	} else {
		if (data_ft->f.refcnt != 2) {
			sptm_violation(0x3e, err, "%s %s %s %llx");
		}
		data_ft->f.refcnt = 1;
		b5 = b4;
	}
	/* New table must be page-table class (2). */
	if (g_type_params[b5].type_class != 2) {
		sptm_violation(0x28, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	/* Transition check: both root and parent types must permit the new table
	 * type (128-bit transition mask). */
	{
		uint64_t bit = 1ULL << (b5 & 0x3f);
		bit_lo = 0; bit_hi = bit;
		if ((b5 & 0x40) == 0) {
			bit_lo = bit; bit_hi = 0;
		}
		bool r_ok = ((g_type_params[FTE_B4(root)].trans_lo & bit_lo) != 0) ||
		            ((g_type_params[FTE_B4(root)].trans_hi & bit_hi) != 0);
		bool p_ok = ((g_type_params[FTE_B4(parent_ft)].trans_lo & bit_lo) != 0) ||
		            ((g_type_params[FTE_B4(parent_ft)].trans_hi & bit_hi) != 0);
		if (!r_ok || !p_ok) {
			sptm_violation(0x28, err, "%s %s %s %d %s %llx %s %s %llx");
		}
	}
	if ((char)FTE_B4(data_ft) != (char)(target_level + 1)) {
		sptm_violation(1, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	DataMemoryBarrier(2, 2);
	if ((char)data_ft->f.type == XNU_PAGE_TABLE_COMMPAGE) {
		sptm_clear_pte(parent_ft, data_ft, 0);
	} else {
		if (data_ft->f.sub_refcnt != 0) {
			sptm_violation(0x4e, err, "%s %s %s %d %s %llx %s %s %llx");
		}
		if (data_ft->f.word4 >> 16 != 0) {   /* puVar[3] (offset 6) */
			sptm_violation(0x19, err, "%s %s %s %llx");
		}
		data_ft->f.word4 = (data_ft->f.word4 & 0xffff) | (1 << 16);
		if (g_type_params[FTE_B4(parent_ft)].type_class == 1) {
			rc = data_ft->f.word4 >> 16;
			uint16_t n = (uint16_t)((data_ft->f.word4 >> 16) + 1);
			data_ft->f.word4 = (data_ft->f.word4 & 0xffff) | ((uint32_t)n << 16);
			if (0x812 < rc) {
				sptm_assert_fail("refcnt overflow rc=%d p old v %d");
			}
		} else {
			if (g_type_params[FTE_B4(parent_ft)].type_class != 2) {
				sptm_assert_fail("Type %d class of FTE %p %d");
			}
			rc = data_ft->f.sub_refcnt;
			data_ft->f.sub_refcnt = rc + 1;
			if (0x808 < rc) {
				sptm_assert_fail("refcnt overflow rc=%d p old v %d");
			}
		}
	}
	if (b4 != XNU_PAGE_TABLE_COMMPAGE) {
		data_ft->f.refcnt = 2;
		data_ft->f.type = 0;
	}
	if (g_type_params[FTE_B4(root)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	/* Install the sub-table TTEs into the parent table. */
	page_size = *(uint64_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x48);
	{
		uint64_t i = 0;
		uint64_t n_entries = page_size ? 0x4000 / page_size : 0;
		for (i = 0; i < n_entries; i++) {
			uint64_t *slot = &papt[i];
			if (*slot != 0) {
				if (i != 0) {
					sptm_violation(0x19, err, "%s %s %s %d %s %llx %s %s %llx");
				}
				sptm_release_table_pair(parent_ft, data_ft);
				result = SPTM_TABLE_ALREADY_PRESENT;
				goto release;
			}
			*slot = new_tte;
			new_tte += page_size;
		}
	}
	result = SPTM_SUCCESS;

release:
	rc = data_ft->f.refcnt;
	data_ft->f.refcnt = rc - 2;
	LORelease();
	if (rc != 0 && (rc & 1) == 0) {
		if (parent_ft != root) {
			rc = parent_ft->f.refcnt;
			parent_ft->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
		rc = root->f.refcnt;
		root->f.refcnt = rc - 2;
		LORelease();
		bool ok = (rc & 1) == 0;
		if (((char)FTE_B4(root) == XNU_USER_TPRO) || ((char)FTE_B4(root) != XNU_USER_ROOT_TABLE)) {
			if (ok && rc != 0) {
				return (sptm_return_t)result;
			}
		} else if (ok && rc != 0) {
			if (g_type_params[FTE_B4(root)].type_class != 1) {
				sptm_assert_fail("Type %d class of FTE %p %d");
			}
			if ((root->f.parent_flags >> 7) & 1) {
				uint64_t pp = sptm_get_parent_paddr(root);
				tmp = (pp < g_sptm_first_phys || g_sptm_last_phys <= pp)
					? &g_invalid_ft : sptm_ft_index(pp);
				rc = tmp->f.refcnt;
				tmp->f.refcnt = rc - 2;
				LORelease();
				if (rc == 0 || (rc & 1) != 0) {
					sptm_assert_fail("rw_guard_release_shared");
				}
			}
			return (sptm_return_t)result;
		}
	}
	sptm_assert_fail("rw_guard_release_shared");
}

/* ============================================================================
 * sptm_unmap_table — FUN_000f05e4
 *
 * Ghidra: void FUN_000f05e4(undefined8 root_paddr, undefined8 vaddr,
 *                           byte target_level)
 *
 * Removes a page-table page at [target_level] for [vaddr]: clears every TTE in
 * the parent table that points at the table, issues TLBIs, and releases the
 * table frame. A user root table (XNU_USER_ROOT_TABLE) may not unmap a shared
 * page table (XNU_PAGE_TABLE_SHARED).
 * Confidence: high (SDK header name + full decompile)
 */
sptm_return_t
sptm_unmap_table(sptm_paddr_t root_pt_paddr, sptm_vaddr_t vaddr, sptm_pt_level_t target_level)
{
	sptm_frame_table_entry_t *root, *leaf_ft, *data_ft, *tmp;
	sptm_ret2_t r;
	uint64_t *papt;
	uint64_t va, tte, bit_lo, bit_hi, bit;
	uint64_t page_size, entries, n, count;
	uint16_t rc;
	uint8_t b3;
	uint64_t err;

	root = (sptm_frame_table_entry_t *)sptm_get_current_root(root_pt_paddr).lo;
	if (g_type_params[FTE_B4(root)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	if ((2 < target_level) ||
	    (target_level < *(uint8_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x38))) {
		sptm_violation(1, 0, "%s %s %s %d %s %llx %s %s %llx");
	}
	r = sptm_validate_va(vaddr, root, target_level);
	va = r.lo;
	err = r.hi;

	/* The kernel root table may not be unmapped. */
	r = sptm_tlb_root(root);
	if (r.lo == (uint64_t)g_kernel_root_ft) {
		sptm_violation(0, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (target_level < 2) {
		if (root->f.refcnt != 2) {
			sptm_violation(0x3e, err, "%s %s %s %llx");
		}
		root->f.refcnt = 1;
	}

	papt = NULL;
	leaf_ft = sptm_walk(root, va, target_level, 1, &papt);
	if (leaf_ft == NULL) {
		sptm_violation(0x23, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	tte = *papt;
	if ((~tte & 3) != 0) {
		sptm_violation(0x23, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	r = sptm_ft_for_paddr(tte & 0xfffffffff000ULL);
	err = r.hi;
	data_ft = (sptm_frame_table_entry_t *)r.lo;
	b3 = data_ft->f.type;

	if ((FTE_B4(root) == XNU_USER_ROOT_TABLE) && (b3 == XNU_PAGE_TABLE_SHARED)) {
		sptm_violation(0, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	/* Transition check: both the root and the parent leaf table must permit
	 * the data table type. */
	bit = 1ULL << (b3 & 0x3f);
	bit_hi = bit; bit_lo = 0;
	if ((b3 & 0x40) == 0) {
		bit_hi = 0; bit_lo = bit;
	}
	{
		bool r_ok = ((g_type_params[FTE_B4(root)].trans_lo & bit_lo) != 0) ||
		            ((g_type_params[FTE_B4(root)].trans_hi & bit_hi) != 0);
		bool p_ok = ((g_type_params[FTE_B4(leaf_ft)].trans_lo & bit_lo) != 0) ||
		            ((g_type_params[FTE_B4(leaf_ft)].trans_hi & bit_hi) != 0);
		if (!r_ok || !p_ok) {
			sptm_assert_fail("incompatible page table type");
		}
	}

	if (g_type_params[FTE_B4(root)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	{
		sptm_pt_geom_t *geom = (sptm_pt_geom_t *)g_cpu_pt_attr[FTE_B12(root)];
		page_size = geom->page_size;
		entries = page_size ? 0x4000 / page_size : 0;
		uint64_t *slot = papt + entries;
		uint64_t expect = (tte - page_size) + 0x4000;
		uint64_t i;
		uint64_t level_stride = *(uint64_t *)((uint8_t *)&geom->level_stride + target_level * 0x38);
		if (page_size < (uint64_t)0x4001) {
			/* 4K/16K geometry: clear every TTE pointing at the table. */
			for (i = 0; i < entries; i++) {
				slot--;
				if (*slot != expect) {
					sptm_violation(0x1d, err, "%s %s %s %d %s %llx %s %s %llx");
				}
				*slot = 0;
				expect -= page_size;
			}
			DataSynchronizationBarrier(2, 2, 0);
			if (target_level == 2) {
				va &= ~(*(uint64_t *)((uint8_t *)&geom->level_stride + target_level * 0x38 + 8));
				count = (level_stride * entries >> (geom->level_shift & 0x3f)) & 0xffffffff;
				n = 1;
			} else {
				count = 1;
				n = entries;
			}
			while (n--) {
				uint64_t tf = sptm_tlb_root(root).lo;
				sptm_tlb_op((sptm_frame_table_entry_t *)tf, va, count, 4);
				va += level_stride;
			}
		} else if (target_level == 2) {
			DataSynchronizationBarrier(2, 2, 0);
			va &= ~(*(uint64_t *)((uint8_t *)&geom->level_stride + target_level * 0x38 + 8));
			count = (level_stride * entries >> (geom->level_shift & 0x3f)) & 0xffffffff;
			n = 1;
			while (n--) {
				uint64_t tf = sptm_tlb_root(root).lo;
				sptm_tlb_op((sptm_frame_table_entry_t *)tf, va, count, 4);
				va += level_stride;
			}
		}
	}
	DataSynchronizationBarrier(2, 3, 1);
	InstructionSynchronizationBarrier();
	sptm_release_table_pair(leaf_ft, data_ft);

	/* Release data_ft, leaf_ft, root. */
	if (g_type_params[FTE_B4(data_ft)].type_class != 6) {
		if ((g_type_params[FTE_B4(data_ft)].flags3 & 1) == 0) {
			data_ft->f.refcnt = 0;
			data_ft->f.type = 0;
		} else {
			rc = data_ft->f.refcnt;
			data_ft->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
	}
	if (leaf_ft != root) {
		rc = leaf_ft->f.refcnt;
		leaf_ft->f.refcnt = rc - 2;
		LORelease();
		if (rc == 0 || (rc & 1) != 0) {
			sptm_assert_fail("rw_guard_release_shared");
		}
	}
	if (target_level < 2) {
		root->f.refcnt = 2;
		root->f.type = 0;
	}
	rc = root->f.refcnt;
	root->f.refcnt = rc - 2;
	LORelease();
	bool ok = (rc & 1) == 0;
	if (((char)FTE_B4(root) == XNU_USER_TPRO) || ((char)FTE_B4(root) != XNU_USER_ROOT_TABLE)) {
		if (ok && rc != 0) {
			return SPTM_SUCCESS;
		}
	} else if (ok && rc != 0) {
		if (g_type_params[FTE_B4(root)].type_class != 1) {
			sptm_assert_fail("Type %d class of FTE %p %d");
		}
		if ((root->f.parent_flags >> 7) & 1) {
			uint64_t pp = sptm_get_parent_paddr(root);
			tmp = (pp < g_sptm_first_phys || g_sptm_last_phys <= pp)
				? &g_invalid_ft : sptm_ft_index(pp);
			rc = tmp->f.refcnt;
			tmp->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
		return SPTM_SUCCESS;
	}
	sptm_assert_fail("rw_guard_release_shared");
}

/* ============================================================================
 * sptm_surt_alloc — FUN_000f1290
 *
 * Ghidra: void FUN_000f1290(undefined8 surt_frame, uint surt_index,
 *                           byte attr_idx, uint flags, ushort asid)
 *
 * Allocates one subpage user root table (SURT) from a
 * XNU_SUBPAGE_USER_ROOT_TABLES frame. Each SURT is an 0x80-byte slot inside
 * the frame; it is initialized as an XNU_USER_ROOT_TABLE (type 0x12), given
 * its ASID (marked busy in the ASID bitmap) and bound to the caller's
 * address-space context.
 * Confidence: high (SDK header name + full decompile)
 */
void
sptm_surt_alloc(sptm_paddr_t surt_frame, uint8_t surt_index, uint8_t attr_idx,
                uint8_t flags, sptm_asid_t asid)
{
	(void)surt_frame;
	sptm_frame_table_entry_t *ft;
	sptm_ret2_t r;
	uint64_t vaddr, paddr;
	uint16_t u;
	uint8_t old_ref;
	uint64_t cpu, bm, bit;
	uint16_t rc;

	r = sptm_surt_ft();
	ft = (sptm_frame_table_entry_t *)r.lo;
	if ((surt_index >> 7) & 1) {
		sptm_violation(0x66, r.hi, "%s %s %s %llx");
	}
	/* Recover the SURT frame's physical address from its FTE pointer. */
	paddr = g_sptm_first_phys + ((((uint8_t *)ft - (uint8_t *)g_frame_table) * 0x400) & 0x3fffffffc000ULL);
	vaddr = sptm_paddr_to_vaddr(paddr) + (int8_t)surt_index * 0x80;

	if (*(uint16_t *)(vaddr + 0x40) != 0) {
		sptm_violation(0x3e, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	*(uint16_t *)(vaddr + 0x40) = 1;
	if ((*(uint8_t *)(vaddr + 0x50) & 1) != 0) {
		sptm_violation(0x68, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	*(uint8_t *)(vaddr + 0x50) = 1;
	*(uint8_t *)(vaddr + 0x42) = XNU_USER_ROOT_TABLE;
	if (g_type_params[FTE_B4(ft)].type_class != 7) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	old_ref = FTE_B4(ft);
	ft->f.word4 = (ft->f.word4 & 0xffffff00) | (uint8_t)(FTE_B4(ft) + 1);
	sptm_ref_release(((uint64_t)(uint32_t)((uint64_t)&ft->f.word4 >> 32)) << 32 | old_ref,
	                 (void *)vaddr, 0x40, 0x40);

	if ((1 < attr_idx) || ((attr_idx == 1) && ((g_surt_feat & 1) == 0))) {
		sptm_violation(2, 0, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (attr_idx != 0) {
		sptm_violation(2, 0, "%s %s %s %llx");
	}
	u = flags & 0xffff;
	if (((0x1ff < u) || (((u ^ 0xffffffff) & 0x24) == 0)) || ((u >> 7) & 1)) {
		sptm_violation(0x10, 0, "%s %s %s %llx");
	}
	if ((asid == 0) || (g_surt_max_asid <= asid)) {
		sptm_violation(4, 0, "%s %s %s %d %s %llx %s %s %llx");
	}
	bit = 1ULL << (asid & 0x3f);
	bm = g_asid_bitmap[asid >> 6];
	g_asid_bitmap[asid >> 6] = bm | bit;
	if ((bm & bit) != 0) {
		sptm_violation(0x4b, 0, "%s %s %s %d %s %llx %s %s %llx");
	}
	*(uint16_t *)(vaddr + 0x44) = asid;
	*(uint16_t *)(vaddr + 0x4a) = flags | 0x80;
	*(uint8_t *)(vaddr + 0x48) = 0xff;
	*(uint8_t *)(vaddr + 0x4c) = 0;
	*(uint16_t *)(vaddr + 0x46) = 0;
	cpu = sptm_cpu_state_base();
	sptm_asid_bind(*(uint64_t *)(cpu + 0xa58), asid);
	*(uint16_t *)(vaddr + 0x40) = 0;

	rc = ft->f.refcnt;
	ft->f.refcnt = rc - 2;
	LORelease();
	if (rc != 0 && (rc & 1) == 0) {
		return;
	}
	sptm_assert_fail("rw_guard_release_shared");
}

/* ============================================================================
 * sptm_surt_free — FUN_000f1910
 *
 * Ghidra: void FUN_000f1910(undefined8 surt_frame, uint surt_index)
 *
 * Frees one subpage user root table slot back into its
 * XNU_SUBPAGE_USER_ROOT_TABLES frame. Note: the ASID is not released here (the
 * ASID bitmap is only cleared when the whole SURT frame is destroyed).
 * Confidence: high (SDK header name + full decompile)
 */
void
sptm_surt_free(sptm_paddr_t surt_frame, uint8_t surt_index)
{
	(void)surt_frame;
	sptm_frame_table_entry_t *ft;
	sptm_ret2_t r;
	uint64_t vaddr, paddr;
	uint8_t old_ref;
	uint16_t rc;

	r = sptm_surt_ft();
	ft = (sptm_frame_table_entry_t *)r.lo;
	if ((surt_index >> 7) & 1) {
		sptm_violation(0x66, r.hi, "%s %s %s %llx");
	}
	paddr = g_sptm_first_phys + ((((uint8_t *)ft - (uint8_t *)g_frame_table) * 0x400) & 0x3fffffffc000ULL);
	vaddr = sptm_paddr_to_vaddr(paddr) + (int8_t)surt_index * 0x80;

	if (*(uint16_t *)(vaddr + 0x40) != 0) {
		sptm_violation(0x3e, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	*(uint16_t *)(vaddr + 0x40) = 1;
	if ((*(uint8_t *)(vaddr + 0x50) & 1) == 0) {
		sptm_violation(0x69, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	*(uint8_t *)(vaddr + 0x50) = 0;
	if (g_type_params[FTE_B4(ft)].type_class != 7) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	old_ref = FTE_B4(ft);
	ft->f.word4 = (ft->f.word4 & 0xffffff00) | (uint8_t)(FTE_B4(ft) - 1);
	sptm_ref_release2(((uint64_t)(uint32_t)((uint64_t)&ft->f.word4 >> 32)) << 32 | old_ref,
	                  (void *)vaddr, 1, 0);
	*(uint16_t *)(vaddr + 0x40) = 0;
	*(uint16_t *)(vaddr + 0x42) = 0;

	rc = ft->f.refcnt;
	ft->f.refcnt = rc - 2;
	LORelease();
	if (rc != 0 && (rc & 1) == 0) {
		return;
	}
	sptm_assert_fail("rw_guard_release_shared");
}

/* ============================================================================
 * sptm_leaf_table_condemn_op — FUN_000f0d50 (est. sptm_condemn_leaf_table)
 *
 * Ghidra: undefined8 FUN_000f0d50(undefined8 root_paddr, undefined8 vaddr,
 *                                 uint condemn)
 *
 * Condemns (or un-condemns) a leaf page table under a user or stage-2 root:
 * sets/clears the "condemned" bit (bit 2) on every TTE in the parent table
 * that points at the table. A user root table must point only at an
 * XNU_PAGE_TABLE (0x14) frame. Condemning prevents new references to the table
 * (sptm_map_page returns SPTM_TABLE_NOT_PRESENT for condemned tables).
 * Confidence: high (SDK header name + full decompile)
 */
sptm_return_t
sptm_leaf_table_condemn_op(sptm_paddr_t root_pt_paddr, sptm_vaddr_t vaddr, bool condemn)
{
	sptm_frame_table_entry_t *root, *leaf_ft, *data_ft = NULL, *tmp;
	sptm_ret2_t r;
	uint64_t *papt;
	uint64_t tte, page_size, entries, i, expect, pat;
	uint64_t err = 0;
	uint16_t rc;

	root = (sptm_frame_table_entry_t *)sptm_get_current_root(root_pt_paddr).lo;
	if ((FTE_B4(root) != XNU_USER_ROOT_TABLE) && (FTE_B4(root) != XNU_STAGE2_ROOT_TABLE)) {
		sptm_violation(0, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	r = sptm_validate_va(vaddr, root, 2);
	err = r.hi;

	papt = NULL;
	leaf_ft = sptm_walk(root, r.lo, 2, 1, &papt);
	if (leaf_ft == NULL) {
		sptm_violation(0x23, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	tte = *papt;
	uint64_t want = condemn ? 3 : 7;
	if ((tte & 7) == want) {
		r = sptm_ft_for_paddr(tte & 0xfffffffff000ULL);
		err = r.hi;
		data_ft = (sptm_frame_table_entry_t *)r.lo;
		if ((FTE_B4(root) == XNU_USER_ROOT_TABLE) && (data_ft->f.type != XNU_PAGE_TABLE)) {
			sptm_violation(0, err, "%s %s %s %d %s %llx %s %s %llx");
		}
		if (g_type_params[FTE_B4(root)].type_class != 1) {
			sptm_assert_fail("Type %d class of FTE %p %d");
		}
		page_size = *(uint64_t *)(g_cpu_pt_attr[FTE_B12(root)] + 0x48);
		if (page_size < 0x4001) {
			entries = page_size ? 0x4000 / page_size : 0;
			pat = (tte & 0xfffffffffffffffbULL) | (condemn ? 4 : 0);
			expect = tte;
			for (i = 0; i < entries; i++) {
				if (papt[i] != expect) {
					if (!condemn) {
						sptm_violation(0x21, err, "%s %s %s %d %s %llx %s %s %llx");
					}
					if (i == 0) {
						err = SPTM_TABLE_NOT_PRESENT;
					} else {
						do {
							*papt &= 0xfffffffffffffffbULL;
							papt++;
							err = SPTM_TABLE_NOT_PRESENT;
							i--;
						} while (i != 0);
					}
					goto release;
				}
				papt[i] = pat;
				expect += page_size;
				pat += page_size;
			}
		}
		err = 0;
	} else {
		if ((condemn & 1) == 0) {
			sptm_violation(0x21, err, "%s %s %s %d %s %llx %s %s %llx");
		}
		err = SPTM_TABLE_NOT_PRESENT;
	}

release:
	/* Release data_ft (only set in the condemn branch), leaf_ft, root. */
	if (data_ft != NULL) {
		if (g_type_params[FTE_B4(data_ft)].type_class != 6) {
			if ((g_type_params[FTE_B4(data_ft)].flags3 & 1) == 0) {
				data_ft->f.refcnt = 0;
				data_ft->f.type = 0;
			} else {
				rc = data_ft->f.refcnt;
				data_ft->f.refcnt = rc - 2;
				LORelease();
				if (rc == 0 || (rc & 1) != 0) {
					sptm_assert_fail("rw_guard_release_shared");
				}
			}
		}
	}
	if (leaf_ft != root) {
		rc = leaf_ft->f.refcnt;
		leaf_ft->f.refcnt = rc - 2;
		LORelease();
		if (rc == 0 || (rc & 1) != 0) {
			sptm_assert_fail("rw_guard_release_shared");
		}
	}
	rc = root->f.refcnt;
	root->f.refcnt = rc - 2;
	LORelease();
	bool ok = (rc & 1) == 0;
	if (((char)FTE_B4(root) == XNU_USER_TPRO) || ((char)FTE_B4(root) != XNU_USER_ROOT_TABLE)) {
		if (ok && rc != 0) {
			return (sptm_return_t)err;
		}
	} else if (ok && rc != 0) {
		if (g_type_params[FTE_B4(root)].type_class != 1) {
			sptm_assert_fail("Type %d class of FTE %p %d");
		}
		if ((root->f.parent_flags >> 7) & 1) {
			uint64_t pp = sptm_get_parent_paddr(root);
			tmp = (pp < g_sptm_first_phys || g_sptm_last_phys <= pp)
				? &g_invalid_ft : sptm_ft_index(pp);
			rc = tmp->f.refcnt;
			tmp->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
		return (sptm_return_t)err;
	}
	sptm_assert_fail("rw_guard_release_shared");
}

/* Per-mapping slot descriptor in the per-CPU handoff scratch region. */
struct sptm_region_slot {
	sptm_frame_table_entry_t *leaf_ft;   /* +0x00 */
	sptm_frame_table_entry_t *data_ft;   /* +0x08 */
	sptm_frame_table_entry_t *release_ft;/* +0x10 */
	uint64_t *papt;                      /* +0x18 */
	uint64_t new_pte;                    /* +0x20 */
	uint8_t  tlb;                        /* +0x28 */
};

/* Per-CPU handoff scratch region base (string symbol used as per-cpu base). */
extern uint8_t s_uat_handoff[];          /* "uat_instance->handoff_region->po..." */

static uint8_t *
sptm_handoff_region(void)
{
	uint64_t cpu = sptm_cpu_state_base();
	return *(uint8_t **)(s_uat_handoff + cpu + 0x1b);
}

/* ============================================================================
 * sptm_region_op — FUN_000f1b78
 *
 * Ghidra: undefined4 FUN_000f1b78(undefined8 root_paddr, undefined8 vaddr,
 *                    undefined8 num_mappings, long new_ptes, ulong options,
 *                    code *preflight, code *finalize)
 *
 * The generic contiguous-region mapping engine. Walks the leaf table for a
 * contiguous VA range, and for each page runs the caller's [preflight] (which
 * validates and merges the new PTE) then, after barriers/TLBIs, the caller's
 * [finalize] (which commits the PTE and updates refcounts). Shared by
 * sptm_update_region() and the unmap/update region paths.
 *
 * Security: the region must not cross a twig-table boundary (checked against
 * the geometry mask at +0x88); the preflight is the enforcement point for the
 * per-mapping frame-type/permission rules. A stage-2 (0x21) root requires NXS.
 * Confidence: high (full decompile)
 */
sptm_return_t
sptm_region_op(sptm_paddr_t root_pt_paddr, sptm_vaddr_t vaddr,
               unsigned int num_mappings, uint64_t new_ptes, uint32_t options,
               int (*preflight)(sptm_region_slot_t *, uint64_t, uint64_t, uint32_t, uint64_t *),
               void (*finalize)(sptm_region_slot_t *, uint64_t, uint64_t, uint32_t))
{
	sptm_frame_table_entry_t *root, *leaf_ft, *data_ft, *rel, *tmp;
	sptm_ret2_t r;
	uint8_t *handoff;
	uint64_t count, va;
	uint64_t *papt;
	uint16_t rc;
	uint8_t root_type;
	uint32_t tlb_op = 5;
	uint32_t needs_tlbi = 0;
	sptm_return_t result;
	bool ok;

	if (preflight == NULL || finalize == NULL) {
		sptm_assert_fail("preflight or finalize mappin");
	}
	root = (sptm_frame_table_entry_t *)sptm_get_current_root(root_pt_paddr).lo;
	root_type = FTE_B4(root);
	papt = NULL;
	r = sptm_parse_region(vaddr, num_mappings, 0x40, root, &count);
	va = r.lo;

	if (g_type_params[root_type].type_class == 1) {
		sptm_pt_geom_t *geom = (sptm_pt_geom_t *)g_cpu_pt_attr[FTE_B12(root)];
		uint64_t page_size = geom->page_size;
		if (((count * page_size + (va - page_size)) ^ va) &
		    *(uint64_t *)((uint8_t *)&geom->rsvd[0] + 0x88)) {
			sptm_violation(0x27, r.hi, "%s %s %s %d %s %llx %s %s %llx");
		}
		handoff = sptm_handoff_region();
		uint64_t *cur_ptes = (uint64_t *)(handoff + 0x200);
		uint64_t *pte_vals = (uint64_t *)handoff;
		uint8_t *slots = handoff + 0x400;

		leaf_ft = sptm_walk(root, va, 3, 1, &papt);
		if (leaf_ft == NULL) {
			sptm_ref_release((uint64_t)handoff, NULL, count << 3, 0x200);
			needs_tlbi = 0;
			goto release_root;
		}

		if (new_ptes != 0) {
			sptm_copyin_handoff(new_ptes, 8, count, 0x200);
		}
		needs_tlbi = 0;
		uint64_t i;
		for (i = 0; i < count; i++) {
			uint64_t new_pte = (new_ptes != 0) ? cur_ptes[i] : 0;
			sptm_region_slot_t *slot = (sptm_region_slot_t *)(slots + i * 0x30);
			slot->leaf_ft = NULL;
			slot->data_ft = leaf_ft;
			slot->release_ft = NULL;
			pte_vals[i] = *papt;
			uint64_t *slot_out = (uint64_t *)((uint8_t *)slot + 0x20);
			slot_out[0] = 0;
			slot_out[1] = 0;
			for (;;) {
				rel = slot->leaf_ft;
				if (rel != NULL) {
					if (g_type_params[FTE_B4(rel)].type_class != 6) {
						if ((g_type_params[FTE_B4(rel)].flags3 & 1) == 0) {
							rel->f.refcnt = 0;
							rel->f.type = 0;
						} else {
							rc = rel->f.refcnt;
							rel->f.refcnt = rc - 2;
							LORelease();
							if (rc == 0 || (rc & 1) != 0) {
								sptm_assert_fail("rw_guard_release_shared");
							}
						}
					}
					slot->leaf_ft = NULL;
				}
				uint64_t cur = pte_vals[i];
				if ((~cur & 3) == 0) {
					r = sptm_ft_for_paddr(cur & 0xfffffffff000ULL);
					slot->leaf_ft = (sptm_frame_table_entry_t *)r.lo;
					if (g_type_attr[FTE_B4(slot->leaf_ft)].flags == 0) {
						sptm_violation(0x41, r.hi, "%s %s %s %d %s %llx %s %s %llx");
					}
					cur = pte_vals[i];
				}
				int st = preflight(slot, cur, new_pte, options, (uint64_t *)slot_out);
				if (st == 0) {
					break;
				}
				if (*papt == pte_vals[i]) {
					break;
				}
				pte_vals[i] = *papt;
				rel = slot->release_ft;
				if (rel != NULL) {
					rc = rel->f.refcnt;
					rel->f.refcnt = rc - 2;
					LORelease();
					if (rc == 0 || (rc & 1) != 0) {
						sptm_assert_fail("rw_guard_release_shared");
					}
					slot->release_ft = NULL;
				}
			}
			*papt = slot_out[0];
			uint8_t tlb;
			if (((options >> 8) & 1) == 0) {
				tlb = slot->tlb;
			} else if ((slot->leaf_ft == NULL) ||
			           ((g_type_params[FTE_B4(slot->leaf_ft)].flags4 & 1) != 0)) {
				tlb = slot->tlb;
			} else {
				options &= 0xfffffeff;
				tlb = slot->tlb;
			}
			if (tlb != 0) {
				uint64_t cur = pte_vals[i];
				if (root_type == XNU_STAGE2_ROOT_TABLE) {
					if ((cur & 0x803) == 3) {
						sptm_assert_fail("FNXS is expected to be set");
					}
					needs_tlbi = 1;
				} else {
					if ((~cur & 0x14) == 0) {
						tlb_op &= 0xfffffffb;
						if ((~slot_out[0] & 0x14) != 0) {
							options &= 0xfffffeff;
						}
					}
					needs_tlbi = 1;
				}
			}
			slot->papt = papt;
			papt++;
		}
		if (((options & 0x100) == 0) && needs_tlbi) {
			DataSynchronizationBarrier(2, 2, 0);
			uint64_t tf = sptm_tlb_root(root).lo;
			sptm_tlb_op((sptm_frame_table_entry_t *)tf, va, count, tlb_op);
			if ((tlb_op >> 2) == 0) {
				DataSynchronizationBarrier(2, 3, 0);
			} else {
				DataSynchronizationBarrier(2, 3, 1);
			}
			InstructionSynchronizationBarrier();
		}
		/* Finalize pass. */
		uint64_t idx = 0;
		uint64_t it = 1;
		bool more;
		do {
			sptm_region_slot_t *slot = (sptm_region_slot_t *)(slots + idx * 0x30);
			data_ft = slot->leaf_ft;
			uint64_t cur = pte_vals[idx];
			if (((cur & 3) == 3) && data_ft != NULL) {
				finalize(slot, cur, slot->new_pte, options);
				if (g_type_params[FTE_B4(data_ft)].type_class != 6) {
					if ((g_type_params[FTE_B4(data_ft)].flags3 & 1) == 0) {
						data_ft->f.refcnt = 0;
						data_ft->f.type = 0;
					} else {
						rc = data_ft->f.refcnt;
						data_ft->f.refcnt = rc - 2;
						LORelease();
						if (rc == 0 || (rc & 1) != 0) {
							sptm_assert_fail("rw_guard_release_shared");
						}
					}
				}
			} else {
				if (((cur & 3) == 3) || data_ft != NULL) {
					sptm_assert_fail("Page FTE does not match the v");
				}
				if (cur != 0) {
					finalize(slot, cur, slot->new_pte, options);
				}
			}
			more = it < count;
			idx = it;
			it++;
		} while (more);

		if (leaf_ft != root) {
			rc = leaf_ft->f.refcnt;
			leaf_ft->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
	} else {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}

release_root:
	rc = root->f.refcnt;
	root->f.refcnt = rc - 2;
	LORelease();
	ok = (rc & 1) == 0;
	if (((char)root_type == XNU_USER_TPRO) || ((char)root_type != XNU_USER_ROOT_TABLE)) {
		if (ok && rc != 0) {
			result = 5;
			if ((needs_tlbi & ((options & 0x100) >> 8)) == 0) {
				result = 0;
			}
			return result;
		}
	} else if (ok && rc != 0) {
		if (g_type_params[root_type].type_class == 1) {
			if ((root->f.parent_flags >> 7) & 1) {
				uint64_t pp = sptm_get_parent_paddr(root);
				tmp = (pp < g_sptm_first_phys || g_sptm_last_phys <= pp)
					? &g_invalid_ft : sptm_ft_index(pp);
				rc = tmp->f.refcnt;
				tmp->f.refcnt = rc - 2;
				LORelease();
				if (rc == 0 || (rc & 1) != 0) {
					sptm_assert_fail("rw_guard_release_shared");
				}
			}
			result = 5;
			if ((needs_tlbi & ((options & 0x100) >> 8)) == 0) {
				result = 0;
			}
			return result;
		}
		goto type_class_panic;
	}
	sptm_assert_fail("rw_guard_release_shared");
type_class_panic:
	sptm_assert_fail("Type %d class of FTE %p %d");
}

/* ============================================================================
 * sptm_update_region — FUN_000f3034
 *
 * Ghidra: void FUN_000f3034(undefined8 a, undefined8 vaddr, undefined8 b,
 *                           ulong pte_templates_pa, uint num_mappings)
 *
 * Validates that a contiguous-region update has a nonzero page count and that
 * the PTE-template array lives in managed DRAM, then dispatches to
 * sptm_region_op() with the update preflight/finalize callbacks.
 * Confidence: high (SDK header name + full decompile)
 */
sptm_return_t
sptm_update_region(sptm_paddr_t root_pt_paddr, sptm_vaddr_t start_vaddr,
                   unsigned int num_mappings, sptm_paddr_t pte_templates_pa)
{
	if ((num_mappings & 0x3f) == 0) {
		sptm_violation(0xe, start_vaddr, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (g_sptm_first_phys <= pte_templates_pa && pte_templates_pa < g_sptm_last_phys) {
		return sptm_region_op(root_pt_paddr, start_vaddr, num_mappings, pte_templates_pa,
		                      0, sptm_update_preflight, sptm_update_finalize);
	}
	sptm_violation(6, start_vaddr, "%s %s %s %d %s %llx %s %s %llx");
}

/* ============================================================================
 * sptm_update_disjoint — FUN_000f38c8
 *
 * Ghidra: void FUN_000f38c8(undefined8 a, undefined8 b, undefined8 c,
 *                           uint num_mappings)
 *
 * Validates that a disjoint update has a nonzero page count, then dispatches
 * to sptm_disjoint_op().
 * Confidence: high (SDK header name + full decompile)
 */
sptm_return_t
sptm_update_disjoint(sptm_paddr_t paddr, sptm_paddr_t disjoint_ops_pa,
                     unsigned int num_mappings, uint32_t options)
{
	if ((num_mappings & 0x3f) != 0) {
		return sptm_disjoint_op(paddr, disjoint_ops_pa, num_mappings, options,
		                        sptm_update_preflight, sptm_update_finalize);
	}
	sptm_violation(0xe, disjoint_ops_pa, "%s %s %s %d %s %llx %s %s %llx");
}

/* ============================================================================
 * A single disjoint mapping update (from sptm_xnu.h). */
typedef struct sptm_disjoint_op {
	sptm_paddr_t root_pt_paddr;   /* +0x00 */
	sptm_vaddr_t vaddr;           /* +0x08 */
	sptm_pte_t   pte_template;    /* +0x10 */
} sptm_disjoint_op_t;

/* An sptm_update_disjoint_multipage entry (paddr header + op list). */
typedef struct sptm_multipage_op {
	uint64_t paddr;               /* +0x00 target physical page */
	uint64_t papt;                /* +0x08 papt/attr template */
	uint32_t flags;               /* +0x10 */
	uint32_t num_disjoint;        /* +0x14 number of following disjoint ops */
} sptm_multipage_op_t;

/* ============================================================================
 * sptm_disjoint_op — FUN_000f3144
 *
 * Ghidra: undefined4 FUN_000f3144(ulong paddr, ulong ops_pa, uint num_mappings,
 *                                 ulong options, code *preflight, code *finalize)
 *
 * The disjoint (non-contiguous, multi-address-space) mapping engine. Consumes
 * an array of sptm_disjoint_op_t entries ({root, vaddr, pte}) copied into the
 * per-CPU handoff scratch region, and for each runs the caller's [preflight] /
 * [finalize] callbacks, issuing per-op TLBIs. Returns
 * SPTM_UPDATE_DELAYED_TLBI (5) if a TLBI is deferred to the caller.
 * Confidence: high (full decompile)
 */
sptm_return_t
sptm_disjoint_op(sptm_paddr_t paddr, sptm_paddr_t ops_pa, unsigned int num_mappings,
                 uint32_t options,
                 int (*preflight)(sptm_region_slot_t *, uint64_t, uint64_t, uint32_t, uint64_t *),
                 void (*finalize)(sptm_region_slot_t *, uint64_t, uint64_t, uint32_t))
{
	sptm_frame_table_entry_t *paddr_ft, *leaf_ft, *rel, *tmp;
	sptm_ret2_t r;
	uint8_t *handoff;
	uint64_t i;
	uint16_t rc;
	uint32_t needs_tlbi = 0, tlb_op = 5, result;
	bool nxs_ok = true;

	if (preflight == NULL || finalize == NULL) {
		sptm_assert_fail("preflight or finalize mappin");
	}
	if (num_mappings - 0x41 < 0xffffffc0) {
		sptm_violation(10, ops_pa, "%s %s %s %d %s %llx %s %s %llx");
	}
	if ((((paddr & 0x3fff) != 0) || (paddr < g_sptm_first_phys || g_sptm_last_phys <= paddr)) ||
	    (ops_pa < g_sptm_first_phys) || (g_sptm_last_phys <= ops_pa)) {
		sptm_violation(6, ops_pa, "%s %s %s %d %s %llx %s %s %llx");
	}

	handoff = sptm_handoff_region();
	/* Copy the disjoint-op table (0x18 bytes each) into the scratch region. */
	sptm_copyin_handoff(ops_pa, 0x18, num_mappings, 0x200);

	r = sptm_ft_for_paddr(paddr);
	paddr_ft = (sptm_frame_table_entry_t *)r.lo;
	if (g_type_attr[FTE_B4(paddr_ft)].flags == 0) {
		sptm_violation(0x41, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	uint8_t *op_table = handoff + 0x40;   /* sptm_disjoint_op_t * */
	uint64_t *pte_vals = (uint64_t *)handoff;
	uint8_t *slots = handoff + 0x100;

	if ((((options >> 8) & 1) != 0) && ((g_type_params[FTE_B4(paddr_ft)].flags4 & 1) == 0)) {
		options &= 0xfffffeff;
	}

	for (i = 0; i < num_mappings; i++) {
		sptm_disjoint_op_t *op = (sptm_disjoint_op_t *)(op_table + i * 0x18);
		sptm_frame_table_entry_t *op_root = (sptm_frame_table_entry_t *)
			sptm_get_current_root(op->root_pt_paddr).lo;
		r = sptm_validate_va(op->vaddr, op_root, 3);

		sptm_region_slot_t *slot = (sptm_region_slot_t *)(slots + i * 0x30);
		slot->leaf_ft = paddr_ft;
		slot->release_ft = NULL;
		uint64_t *papt = NULL;
		leaf_ft = sptm_walk(op_root, r.lo, 3, 1, &papt);
		slot->data_ft = leaf_ft;
		slot->papt = papt;
		if (leaf_ft != NULL) {
			uint64_t cur = *papt;
			pte_vals[i] = cur;
			uint64_t *slot_out = &slot->new_pte;
			slot_out[0] = 0;
			rel = slot->release_ft;
			for (;;) {
				if (rel != NULL) {
					rc = rel->f.refcnt;
					rel->f.refcnt = rc - 2;
					LORelease();
					if (rc == 0 || (rc & 1) != 0) {
						sptm_assert_fail("rw_guard_release_shared");
					}
					slot->release_ft = NULL;
					cur = pte_vals[i];
				}
				if ((((~cur & 3) == 0) && (paddr != (cur & 0xffffffffc000ULL))) ||
				    (preflight(slot, cur, op->pte_template, options, slot_out) == 0)) {
					break;
				}
				cur = *papt;
				if (cur == pte_vals[i]) {
					slot_out[0] = cur;
					*papt = slot_out[0];
					break;
				}
				pte_vals[i] = cur;
				rel = slot->release_ft;
			}
			*papt = slot_out[0];
			if (slot->tlb != 0) {
				needs_tlbi |= slot->tlb;
				if (FTE_B4(op_root) == XNU_STAGE2_ROOT_TABLE) {
					if ((pte_vals[i] & 0x803) == 3) {
						sptm_assert_fail("FNXS is expected to be set");
					}
				} else if ((~pte_vals[i] & 0x14) == 0) {
					if ((~slot_out[0] & 0x14) != 0) {
						options &= 0xfffffeff;
					}
				}
			}
		} else {
			pte_vals[i] = 0;
		}
	}

	if ((((options >> 8) & 1) == 0) && (needs_tlbi != 0)) {
		DataSynchronizationBarrier(2, 2, 0);
		uint64_t j = num_mappings;
		uint64_t *pv = pte_vals;
		uint8_t *opb = op_table;
		uint8_t *tb = slots + 5;   /* slot->tlb byte (offset 0x28 = +5 qwords) */
		do {
			sptm_disjoint_op_t *op = (sptm_disjoint_op_t *)opb;
			sptm_frame_table_entry_t *ot = sptm_ft_for_pte(op->root_pt_paddr);
			if (*tb != 0) {
				if (FTE_B4(ot) == XNU_STAGE2_ROOT_TABLE) {
					if ((*pv & 0x803) == 3) {
						sptm_assert_fail("FNXS is expected to be set");
					}
					tlb_op = 5;
				} else {
					bool is_wx = (*pv & 0x14) == 0x14;
					nxs_ok = nxs_ok && is_wx;
					tlb_op = 5;
					if (is_wx) {
						tlb_op = 1;
					}
				}
				sptm_tlb_op(ot, op->vaddr, 1, tlb_op);
			}
			pv++;
			opb += 0x18;
			j--;
			tb += 6 * 8;
		} while (j != 0);
		if ((needs_tlbi >> 1 & 1) != 0) {
			if (nxs_ok) {
				DataSynchronizationBarrier(2, 3, 1);
			} else {
				DataSynchronizationBarrier(2, 3, 0);
			}
			InstructionSynchronizationBarrier();
		}
	}

	/* Release pass: per-op data frame, leaf, root. */
	for (i = 0; i < num_mappings; i++) {
		sptm_disjoint_op_t *op = (sptm_disjoint_op_t *)(op_table + i * 0x18);
		sptm_frame_table_entry_t *op_root = (sptm_frame_table_entry_t *)
			sptm_get_current_root(op->root_pt_paddr).lo;
		sptm_region_slot_t *slot = (sptm_region_slot_t *)(slots + i * 0x30);
		uint64_t cur = pte_vals[i];
		leaf_ft = slot->data_ft;
		if (((~cur & 3) == 0) && (paddr == (cur & 0xffffffffc000ULL))) {
			if (slot->papt != NULL) {
				finalize(slot, cur, slot->new_pte, options);
			}
		}
		if (leaf_ft != NULL) {
			rc = leaf_ft->f.refcnt;
			leaf_ft->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
		rc = op_root->f.refcnt;
		op_root->f.refcnt = rc - 2;
		LORelease();
		bool ok2 = (rc & 1) == 0;
		if (((char)FTE_B4(op_root) == XNU_USER_TPRO) || ((char)FTE_B4(op_root) != XNU_USER_ROOT_TABLE)) {
			if (!ok2 || rc == 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		} else if (!ok2 || rc == 0) {
			sptm_assert_fail("rw_guard_release_shared");
		} else {
			if (g_type_params[FTE_B4(op_root)].type_class != 1) {
				sptm_assert_fail("Type %d class of FTE %p %d");
			}
			if ((op_root->f.parent_flags >> 7) & 1) {
				uint64_t pp = sptm_get_parent_paddr(op_root);
				tmp = (pp < g_sptm_first_phys || g_sptm_last_phys <= pp)
					? &g_invalid_ft : sptm_ft_index(pp);
				rc = tmp->f.refcnt;
				tmp->f.refcnt = rc - 2;
				LORelease();
				if (rc == 0 || (rc & 1) != 0) {
					sptm_assert_fail("rw_guard_release_shared");
				}
			}
		}
	}

	/* Release the paddr frame. */
	if (g_type_params[FTE_B4(paddr_ft)].type_class != 6) {
		if ((g_type_params[FTE_B4(paddr_ft)].flags3 & 1) == 0) {
			paddr_ft->f.refcnt = 0;
			paddr_ft->f.type = 0;
		} else {
			rc = paddr_ft->f.refcnt;
			paddr_ft->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
	}
	result = 5;
	if (((needs_tlbi != 0) & ((options >> 8) & 1)) == 0) {
		result = 0;
	}
	return (sptm_return_t)result;
}

/* ============================================================================
 * sptm_update_disjoint_multipage — FUN_000f3998
 *
 * Ghidra: undefined4 FUN_000f3998(ulong multipage_ops_pa, ulong num_entries)
 *
 * Updates mappings that may span multiple physical pages. Consumes an array of
 * sptm_update_disjoint_multipage_op_t entries (a paddr header + disjoint ops).
 * For each entry it validates the target paddr, updates the PAPT mapping via
 * sptm_set_pte_attr(), and dispatches the disjoint ops to sptm_disjoint_op().
 * Returns SPTM_UPDATE_DELAYED_TLBI (5) if any sub-op deferred a TLBI.
 * Confidence: high (SDK header name + full decompile)
 */
sptm_return_t
sptm_update_disjoint_multipage(sptm_paddr_t multipage_ops_pa, size_t num_entries)
{
	sptm_frame_table_entry_t *ft;
	sptm_ret2_t r;
	uint64_t entries = (uint64_t)num_entries;
	uint64_t va, err = entries;
	uint64_t i = 0;
	uint16_t rc;
	sptm_return_t result = 0;
	bool need_tlbi = false;

	if (multipage_ops_pa < g_sptm_first_phys || g_sptm_last_phys <= multipage_ops_pa) {
		sptm_violation(6, err, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (entries - 0x41 < 0xffffffffffffffc0ULL) {
		sptm_violation(10, entries, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (0x4000 < (multipage_ops_pa & 0x3fff) + entries * 0x18) {
		sptm_violation(0x61, entries, "%s %s %s %d %s %llx %s %s %llx");
	}
	va = sptm_paddr_to_vaddr(multipage_ops_pa);

	for (;;) {
		sptm_multipage_op_t *op = (sptm_multipage_op_t *)(va + i * 0x18);
		uint64_t op_paddr = op->paddr;
		uint64_t op_papt = op->papt;
		uint32_t flags = *(uint32_t *)((uint8_t *)op + 0x14);
		if (((flags >> 9) & 1) == 0) {
			/* Real (non-header) disjoint op: update the PAPT entry. */
			if (((op_paddr & 0x3fff) != 0) || (op_paddr < g_sptm_first_phys) ||
			    (g_sptm_last_phys <= op_paddr)) {
				sptm_violation(6, err, "%s %s %s %d %s %llx %s %s %llx");
			}
			r = sptm_ft_for_paddr(op_paddr);
			ft = (sptm_frame_table_entry_t *)r.lo;
			uint64_t ftype = ft->f.type;
			if (g_type_attr[ftype].flags == 0) {
				sptm_violation(0x41, r.hi, "%s %s %s %d %s %llx %s %s %llx");
			}
			if ((flags >> 5) & 1) {
				if ((g_type_params[ftype].type_class == 3) &&
				    (g_type_params[ftype].cache_attr == 1)) {
					if ((uint32_t)((op_papt & 0x1c) != 0x10) == ((FTE_B4(ft) >> 2) & 1)) {
						sptm_violation(0x1c, r.hi, "%s %s %s %d %s %llx %s %s %llx");
					}
				} else if ((op_papt & 0x1c) == 0x10) {
					sptm_violation(0x1c, r.hi, "%s %s %s %d %s %llx %s %s %llx");
				}
			}
			uint32_t opts = flags & 0x130;
			if ((0xff < opts) && ((g_type_params[ftype].flags4 & 1) == 0)) {
				opts = 0;
			}
			int st = sptm_set_pte_attr(op_paddr, 0xff, (op_papt >> 2) & 7,
			                           ((opts >> 1) & 0x80) | ((flags & 0x20) >> 4));
			if (g_type_params[ftype].type_class != 6) {
				if ((g_type_params[ftype].flags3 & 1) == 0) {
					ft->f.refcnt = 0;
					ft->f.type = 0;
				} else {
					rc = ft->f.refcnt;
					ft->f.refcnt = rc - 2;
					LORelease();
					if (rc == 0 || (rc & 1) != 0) {
						sptm_assert_fail("rw_guard_release_shared");
					}
				}
			}
			need_tlbi = need_tlbi || (st == 5);
		}
		/* Advance by this entry's stride (1 + n_disjoint_ops). */
		uint64_t next = i + 1;
		if (op->num_disjoint != 0) {
			next = i + 1 + op->num_disjoint;
			if (entries < next) {
				sptm_violation(10, err, "%s %s %s %d %s %llx %s %s %llx");
			}
			if ((flags & 0x3f) == 0) {
				sptm_violation(0xe, multipage_ops_pa + i * 0x18, "%s %s %s %d %s %llx %s %s %llx");
			}
			sptm_return_t sr = sptm_disjoint_op(op_paddr, va + i * 0x18, op->num_disjoint,
			                                    0, sptm_update_preflight, sptm_update_finalize);
			need_tlbi = need_tlbi || (sr == 5);
		}
		if (entries <= next) {
			result = 5;
			if (!need_tlbi) {
				result = 0;
			}
			return result;
		}
		i = next;
	}
}

/* ============================================================================
 * sptm_configure_shared_region — FUN_000f3f60
 *
 * Ghidra: void FUN_000f3f60(undefined8 shared_root_pt_paddr,
 *                           undefined8 start_vaddr, undefined8 page_count)
 *
 * Configures the VA range a shared root table will back. The shared root FTE
 * is claimed, the region is parsed against the shared-root geometry, and the
 * region bounds are recorded in the global shared-region table
 * (g_shared_region_papt / g_shared_region_size) with the state machine
 * 1 -> 2 -> 3 (unconfigured -> configuring -> configured). Must be called once
 * before sptm_set_shared_region()/sptm_nest_region()/sptm_unnest_region().
 * Confidence: high (SDK header name + full decompile)
 */
void
sptm_configure_shared_region(sptm_paddr_t shared_root_pt_paddr, sptm_vaddr_t start_vaddr,
                             unsigned int page_count)
{
	sptm_frame_table_entry_t *ft;
	sptm_ret2_t r;
	uint64_t count = 0;
	uint8_t id;
	uint64_t idx, page_size;

	r = sptm_shared_ft(shared_root_pt_paddr);
	ft = (sptm_frame_table_entry_t *)r.lo;
	if (ft->f.refcnt != 2) {
		sptm_violation(0x3e, r.hi, "%s %s %s %llx");
	}
	ft->f.refcnt = 1;
	if (g_type_params[FTE_B4(ft)].type_class == 1) {
		sptm_pt_geom_t *geom = (sptm_pt_geom_t *)g_cpu_pt_attr[FTE_B12(ft)];
		page_size = *(uint64_t *)((uint8_t *)geom + 0x48);
		r = sptm_parse_region(start_vaddr, page_count,
		                      0x1000000000ULL >> (geom->level_shift & 0x3f) & 0xffffffff,
		                      ft, &count);
		if (g_type_params[FTE_B4(ft)].type_class == 1) {
			id = FTE_B4(ft);
			if (id == 0xff) {
				sptm_assert_fail("Unexpected shared region ID");
			}
			idx = id * 0x20;
			if ((int8_t)g_shared_region_state[idx] == -1) {
				sptm_assert_fail("Unexpected shared region sta");
			}
			page_size = *(uint64_t *)((uint8_t *)geom + 0x48);
			if (g_shared_region_state[idx] != 1) {
				sptm_violation(0x48, r.hi, "%s %s %s %d %s %llx %s %s %llx");
			}
			g_shared_region_state[idx] = 2;
			g_shared_region_papt[id * 4] = r.lo;
			g_shared_region_size[idx] = count * page_size;
			if (g_shared_region_state[idx] == 2) {
				g_shared_region_state[idx] = 3;
				ft->f.refcnt = 0;
				ft->f.type = 0;
				return;
			}
			sptm_assert_fail("Unexpected failure while att");
		}
	}
	sptm_assert_fail("Type %d class of FTE %p %d");
}

/* ============================================================================
 * sptm_set_shared_region — FUN_000f4188
 *
 * Ghidra: void FUN_000f4188(undefined8 user_root_pt_paddr,
 *                           undefined8 shared_root_pt_paddr)
 *
 * Associates a user root table with a previously-configured shared root table:
 * binds the shared region into the user address space and bumps the shared
 * root's refcount. Both roots must share the same page-table attribute index;
 * the shared region must be configured (state 3) and the user root must not
 * already reference one.
 * Confidence: high (SDK header name + full decompile)
 */
void
sptm_set_shared_region(sptm_paddr_t user_root_pt_paddr, sptm_paddr_t shared_root_pt_paddr)
{
	sptm_frame_table_entry_t *user_ft, *shared_ft, *tmp;
	sptm_ret2_t r;
	uint8_t id;
	uint64_t cpu;
	uint16_t rc;

	r = sptm_root_ft(user_root_pt_paddr);
	user_ft = (sptm_frame_table_entry_t *)r.lo;
	if (user_ft->f.refcnt != 2) {
		sptm_violation(0x3e, r.hi, "%s %s %s %llx");
	}
	user_ft->f.refcnt = 1;
	r = sptm_shared_ft(shared_root_pt_paddr);
	shared_ft = (sptm_frame_table_entry_t *)r.lo;
	if ((g_type_params[FTE_B4(user_ft)].type_class == 1) &&
	    (g_type_params[FTE_B4(shared_ft)].type_class == 1)) {
		if ((int8_t)FTE_B12(user_ft) != (int8_t)FTE_B12(shared_ft)) {
			sptm_violation(0x3c, r.hi, "%s %s %s %d %s %llx %s %s %llx");
		}
		id = FTE_B4(shared_ft);
		if (id == 0xff) {
			sptm_assert_fail("Unexpected shared region ID");
		}
		if (g_shared_region_state[id * 0x20] != 3) {
			sptm_violation(0x4a, r.hi, "%s %s %s %d %s %llx %s %s %llx");
		}
		if ((int8_t)FTE_B4(user_ft) != -1) {
			sptm_violation(0x3b, r.hi, "%s %s %s %llx");
		}
		user_ft->f.word4 = (user_ft->f.word4 & 0xffffff00) | id;
		if (g_type_params[FTE_B4(user_ft)].type_class == 1) {
			cpu = sptm_cpu_state_base();
			sptm_shared_bind(*(uint64_t *)(cpu + 0xa58), user_ft->f.word4, id,
			                 g_shared_region_papt[id * 4], g_shared_region_size[id * 0x20]);
			if (g_type_params[FTE_B4(shared_ft)].type_class == 1) {
				rc = shared_ft->f.sub_refcnt;
				shared_ft->f.sub_refcnt = rc + 1;
				if (0xfff4 < rc) {
					sptm_violation(0x46, 0, "%s %s %s %d %s %llx %s %s %llx");
				}
				rc = shared_ft->f.refcnt;
				shared_ft->f.refcnt = rc - 2;
				LORelease();
				if (rc != 0 && (rc & 1) == 0) {
					user_ft->f.refcnt = 2;
					user_ft->f.type = 0;
					rc = user_ft->f.refcnt;
					user_ft->f.refcnt = rc - 2;
					LORelease();
					if (rc != 0 && (rc & 1) == 0) {
						if (g_type_params[FTE_B4(user_ft)].type_class == 1) {
							if ((user_ft->f.parent_flags >> 7) & 1) {
								uint64_t pp = sptm_get_parent_paddr(user_ft);
								tmp = (pp < g_sptm_first_phys || g_sptm_last_phys <= pp)
									? &g_invalid_ft : sptm_ft_index(pp);
								rc = tmp->f.refcnt;
								tmp->f.refcnt = rc - 2;
								LORelease();
								if (rc == 0 || (rc & 1) != 0) {
									sptm_assert_fail("rw_guard_release_shared");
								}
							}
							return;
						}
						goto panic;
					}
				}
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
	}
panic:
	sptm_assert_fail("Type %d class of FTE %p %d");
}

/* ============================================================================
 * sptm_nest_region — FUN_000f458c
 *
 * Ghidra: void FUN_000f458c(undefined8 user_root, undefined8 shared_root,
 *                           undefined8 start_vaddr, undefined8 page_count)
 *
 * Nests a VA range of a configured shared root table into a user address
 * space: for each entry in the shared root's table it validates the shared
 * table is XNU_PAGE_TABLE_SHARED (0x15) and installs the shared PTE into the
 * user root's page table.
 * Confidence: high (SDK header name + full decompile)
 */
void
sptm_nest_region(sptm_paddr_t user_root_pt_paddr, sptm_paddr_t shared_root_pt_paddr,
                 sptm_vaddr_t start_vaddr, unsigned int page_count)
{
	sptm_frame_table_entry_t *user_ft, *shared_ft, *shared_leaf, *user_leaf, *data_ft, *tmp;
	sptm_ret2_t r;
	uint64_t *shared_papt, *user_papt;
	uint64_t count = 0, va, size, page_size, n;
	uint8_t id;
	uint16_t rc;

	user_ft = (sptm_frame_table_entry_t *)sptm_root_ft(user_root_pt_paddr).lo;
	r = sptm_shared_ft(shared_root_pt_paddr);
	shared_ft = (sptm_frame_table_entry_t *)r.lo;
	if (g_type_params[FTE_B4(shared_ft)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	id = FTE_B4(shared_ft);
	if (g_type_params[FTE_B4(user_ft)].type_class != 1) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	if (id != FTE_B4(user_ft)) {
		sptm_violation(0x49, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	shared_papt = NULL;
	sptm_pt_geom_t *sgeom = (sptm_pt_geom_t *)g_cpu_pt_attr[FTE_B12(shared_ft)];
	r = sptm_parse_region2(start_vaddr, page_count,
	                       *(uint64_t *)((uint8_t *)sgeom + 0x38) >> (sgeom->level_shift & 0x3f),
	                       shared_ft, &count);
	va = r.lo;
	shared_leaf = sptm_walk(shared_ft, va, 2, 1, &shared_papt);
	if (shared_leaf == NULL) {
		sptm_violation(0x23, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (id == 0xff) {
		sptm_assert_fail("Unexpected shared region ID");
	}
	page_size = *(uint64_t *)(g_cpu_pt_attr[FTE_B12(user_ft)] + 0x48);
	size = count * page_size;
	if ((va < g_shared_region_papt[id * 4]) ||
	    (g_shared_region_size[id * 0x20] + g_shared_region_papt[id * 4] < size + va)) {
		sptm_violation(8, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	user_papt = NULL;
	user_leaf = sptm_walk(user_ft, va, 2, 1, &user_papt);
	if (user_leaf == NULL) {
		sptm_violation(0x23, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	{
		sptm_pt_geom_t *ugeom = (sptm_pt_geom_t *)g_cpu_pt_attr[FTE_B12(user_ft)];
		uint64_t lvl = ugeom->rsvd[6];   /* level mask */
		uint64_t a = *(uint64_t *)((uint8_t *)ugeom + 0x80);
		uint64_t b = *(uint64_t *)((uint8_t *)ugeom + 0x88);
		n = (int64_t)(((lvl & b & ((va - page_size) + size)) >> (a & 0x3f)) -
		              ((b & lvl & va) >> (a & 0x3f)));
	}
	if (n != (uint64_t)-1) {
		uint64_t idx = n + 1;
		uint64_t *sp = shared_papt;
		uint64_t *up = user_papt;
		while (idx--) {
			uint64_t sp_pte = *sp;
			if ((~sp_pte & 3) != 0) {
				sptm_violation(0x1a, 0, "%s %s %s %d %s %llx %s %s %llx");
			}
			r = sptm_ft_for_paddr(sp_pte & 0xfffffffff000ULL);
			data_ft = (sptm_frame_table_entry_t *)r.lo;
			if ((*sp & 0xfffffffff000ULL) != (sp_pte & 0xfffffffff000ULL)) {
				sptm_violation(0x53, r.hi, "%s %s %s %d %s %llx %s %s %llx");
			}
			if (data_ft->f.type != XNU_PAGE_TABLE_SHARED) {
				sptm_violation(0x28, r.hi, "%s %s %s %d %s %llx %s %s %llx");
			}
			if (g_bootstrap_stage_flag != 2) {
				sptm_assert_fail("Type %d class of FTE %p %d");
			}
			if ((FTE_B4(data_ft) != 3) ||
			    ((g_type_params[FTE_B4(user_leaf)].attr >> 5) & 1) == 0) {
				sptm_violation(0x28, r.hi, "%s %s %s %d %s %llx %s %s %llx");
			}
			if (*up != 0) {
				sptm_violation(0x1a, 0, "%s %s %s %d %s %llx %s %s %llx");
			}
			*up = sp_pte;
			sptm_clear_pte(user_leaf, data_ft, 0);
			if (g_type_params[FTE_B4(data_ft)].type_class != 6) {
				if ((g_type_params[FTE_B4(data_ft)].flags3 & 1) == 0) {
					data_ft->f.refcnt = 0;
					data_ft->f.type = 0;
				} else {
					rc = data_ft->f.refcnt;
					data_ft->f.refcnt = rc - 2;
					LORelease();
					if (rc == 0 || (rc & 1) != 0) {
						sptm_assert_fail("rw_guard_release_shared");
					}
				}
			}
			sp++;
			up++;
		}
	}
	DataMemoryBarrier(2, 3);
	InstructionSynchronizationBarrier();

	if (shared_leaf != shared_ft) {
		rc = shared_leaf->f.refcnt;
		shared_leaf->f.refcnt = rc - 2;
		LORelease();
		if (rc == 0 || (rc & 1) != 0) {
			sptm_assert_fail("rw_guard_release_shared");
		}
	}
	rc = shared_ft->f.refcnt;
	shared_ft->f.refcnt = rc - 2;
	LORelease();
	if (rc != 0 && (rc & 1) == 0) {
		if (user_leaf != user_ft) {
			rc = user_leaf->f.refcnt;
			user_leaf->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
		rc = user_ft->f.refcnt;
		user_ft->f.refcnt = rc - 2;
		LORelease();
		if (rc != 0 && (rc & 1) == 0) {
			if (g_type_params[FTE_B4(user_ft)].type_class == 1) {
				if ((user_ft->f.parent_flags >> 7) & 1) {
					uint64_t pp = sptm_get_parent_paddr(user_ft);
					tmp = (pp < g_sptm_first_phys || g_sptm_last_phys <= pp)
						? &g_invalid_ft : sptm_ft_index(pp);
					rc = tmp->f.refcnt;
					tmp->f.refcnt = rc - 2;
					LORelease();
					if (rc == 0 || (rc & 1) != 0) {
						sptm_assert_fail("rw_guard_release_shared");
					}
				}
				return;
			}
			goto npanic;
		}
	}
	sptm_assert_fail("rw_guard_release_shared");
npanic:
	sptm_assert_fail("Type %d class of FTE %p %d");
}

/* ============================================================================
 * sptm_unnest_region — FUN_000f4eec
 *
 * Ghidra: void FUN_000f4eec(undefined8 user_root, undefined8 shared_root,
 *                           undefined8 start_vaddr, undefined8 page_count)
 *
 * Removes a previously-nested shared region from a user address space: clears
 * the shared PTEs from the user root's page table and flushes the TLB. The
 * user and shared roots must reference the same configured shared region.
 * Confidence: high (SDK header name + full decompile)
 */
void
sptm_unnest_region(sptm_paddr_t user_root_pt_paddr, sptm_paddr_t shared_root_pt_paddr,
                   sptm_vaddr_t start_vaddr, unsigned int page_count)
{
	sptm_frame_table_entry_t *user_ft, *shared_ft, *shared_leaf, *user_leaf, *data_ft, *tmp;
	sptm_ret2_t r;
	uint64_t *shared_papt, *user_papt;
	uint64_t count = 0, va, size, page_size;
	uint8_t id, user_attr;
	uint16_t rc;
	uint64_t n, i = 0;

	user_ft = (sptm_frame_table_entry_t *)sptm_root_ft(user_root_pt_paddr).lo;
	shared_ft = (sptm_frame_table_entry_t *)sptm_shared_ft(shared_root_pt_paddr).lo;
	if ((g_type_params[FTE_B4(shared_ft)].type_class != 1) ||
	    (g_type_params[FTE_B4(user_ft)].type_class != 1)) {
		sptm_assert_fail("Type %d class of FTE %p %d");
	}
	user_attr = FTE_B12(user_ft);
	shared_papt = NULL;
	sptm_pt_geom_t *sgeom = (sptm_pt_geom_t *)g_cpu_pt_attr[FTE_B12(shared_ft)];
	r = sptm_parse_region2(start_vaddr, page_count,
	                       *(uint64_t *)((uint8_t *)sgeom + 0x38) >> (sgeom->level_shift & 0x3f),
	                       shared_ft, &count);
	va = r.lo;
	shared_leaf = sptm_walk(shared_ft, va, 2, 1, &shared_papt);
	if (shared_leaf == NULL) {
		sptm_violation(0x23, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	id = FTE_B4(shared_ft);
	if (id != FTE_B4(user_ft)) {
		sptm_violation(0x49, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	if (id == 0xff) {
		sptm_assert_fail("Unexpected shared region ID");
	}
	page_size = *(uint64_t *)(g_cpu_pt_attr[user_attr * 8] + 0x48);
	size = count * page_size;
	if ((va < g_shared_region_papt[id * 4]) ||
	    (g_shared_region_size[id * 0x20] + g_shared_region_papt[id * 4] < size + va)) {
		sptm_violation(8, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	user_papt = NULL;
	user_leaf = sptm_walk(user_ft, va, 2, 1, &user_papt);
	if (user_leaf == NULL) {
		sptm_violation(0x23, r.hi, "%s %s %s %d %s %llx %s %s %llx");
	}
	{
		sptm_pt_geom_t *ugeom = (sptm_pt_geom_t *)g_cpu_pt_attr[FTE_B12(shared_ft)];
		uint64_t lvl = ugeom->rsvd[6];
		uint64_t a = *(uint64_t *)((uint8_t *)ugeom + 0x80);
		uint64_t b = *(uint64_t *)((uint8_t *)ugeom + 0x88);
		n = (int64_t)(((lvl & b & ((va - page_size) + size)) >> (a & 0x3f)) -
		              ((b & lvl & va) >> (a & 0x3f))) + 1;
	}
	uint8_t *handoff = sptm_handoff_region();
	uint64_t *collected = (uint64_t *)handoff;
	uint64_t ncol = 0;
	uint64_t *up = user_papt;
	for (uint64_t k = 0; k < n; k++) {
		uint64_t pte = *up;
		if ((~pte & 3) == 0) {
			r = sptm_ft_for_paddr(pte & 0xfffffffff000ULL);
			data_ft = (sptm_frame_table_entry_t *)r.lo;
			if (data_ft->f.type == XNU_PAGE_TABLE_SHARED) {
				if (*up != pte) {
					sptm_violation(0x1b, r.hi, "%s %s %s %d %s %llx %s %s %llx");
				}
				*up = 0;
				collected[ncol++] = pte & 0xfffffffff000ULL;
			} else {
				sptm_shared_mismatch();
			}
		}
		up++;
	}
	DataSynchronizationBarrier(2, 2, 0);
	uint64_t tf = sptm_tlb_root(user_ft).lo;
	sptm_tlb_op((sptm_frame_table_entry_t *)tf,
	            va & ~(*(uint64_t *)((uint8_t *)sgeom + 0x78)),
	            (page_size >> 3 & 0x1fffffff) * n, 4);
	DataSynchronizationBarrier(2, 3, 1);
	InstructionSynchronizationBarrier();
	for (i = 0; i < ncol; i++) {
		uint64_t pp = collected[i];
		sptm_frame_table_entry_t *df;
		if (pp < g_sptm_first_phys || g_sptm_last_phys <= pp) {
			df = &g_invalid_ft;
		} else {
			df = sptm_ft_index(pp);
		}
		sptm_clear_pte(user_leaf, df, 1);
		if (g_type_params[FTE_B4(df)].type_class != 6) {
			if ((g_type_params[FTE_B4(df)].flags3 & 1) == 0) {
				df->f.refcnt = 0;
				df->f.type = 0;
			} else {
				rc = df->f.refcnt;
				df->f.refcnt = rc - 2;
				LORelease();
				if (rc == 0 || (rc & 1) != 0) {
					sptm_assert_fail("rw_guard_release_shared");
				}
			}
		}
	}
	if (shared_leaf != shared_ft) {
		rc = shared_leaf->f.refcnt;
		shared_leaf->f.refcnt = rc - 2;
		LORelease();
		if (rc == 0 || (rc & 1) != 0) {
			sptm_assert_fail("rw_guard_release_shared");
		}
	}
	rc = shared_ft->f.refcnt;
	shared_ft->f.refcnt = rc - 2;
	LORelease();
	if (rc != 0 && (rc & 1) == 0) {
		if (user_leaf != user_ft) {
			rc = user_leaf->f.refcnt;
			user_leaf->f.refcnt = rc - 2;
			LORelease();
			if (rc == 0 || (rc & 1) != 0) {
				sptm_assert_fail("rw_guard_release_shared");
			}
		}
		rc = user_ft->f.refcnt;
		user_ft->f.refcnt = rc - 2;
		LORelease();
		if (rc != 0 && (rc & 1) == 0) {
			if (g_type_params[FTE_B4(user_ft)].type_class == 1) {
				if ((user_ft->f.parent_flags >> 7) & 1) {
					uint64_t pp = sptm_get_parent_paddr(user_ft);
					tmp = (pp < g_sptm_first_phys || g_sptm_last_phys <= pp)
						? &g_invalid_ft : sptm_ft_index(pp);
					rc = tmp->f.refcnt;
					tmp->f.refcnt = rc - 2;
					LORelease();
					if (rc == 0 || (rc & 1) != 0) {
						sptm_assert_fail("rw_guard_release_shared");
					}
				}
				return;
			}
			goto upanic;
		}
	}
	sptm_assert_fail("rw_guard_release_shared");
upanic:
	sptm_assert_fail("Type %d class of FTE %p %d");
}
